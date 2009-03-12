#include "playengine.h"
#include "subtitle.h"
#include "osdstyle.h"
#include "abstractosdrenderer.h"
#include "subtitlerenderer.h"
#include "videorendereriface.h"
#include "info.h"
#include <QtGui/QWidget>
#include <QtGui/QPainter>
#include <QtGui/QPaintEvent>
#include <QtCore/QDebug>
#include <QtCore/QTimer>

namespace Core {

class PlayEngine::Screen : public QWidget {
public:
	Screen() {
		m_widget = 0;
		setMouseTracking(true);
		setAutoFillBackground(true);
		setAttribute(Qt::WA_PaintOnScreen);
		setAttribute(Qt::WA_OpaquePaintEvent);
	}
	~Screen() {
		if (m_widget)
			m_widget->setParent(0);
	}
	QSize sizeHint() const {
		return m_widget ? m_widget->sizeHint() : QWidget::sizeHint();
	}
	void setWidget(QWidget *widget) {
		if (m_widget != widget) {
			if ((m_widget = widget)) {
				m_widget->setParent(this);
				m_widget->move(0, 0);
				m_widget->resize(size());
				m_widget->show();
			}
		}
	}
	QWidget *widget() {return m_widget;}
private:
	void resizeEvent(QResizeEvent *event) {
		QWidget::resizeEvent(event);
		if (m_widget)
			m_widget->resize(size());
	}
	void paintEvent(QPaintEvent *event) {
		QPainter painter(this);
		painter.fillRect(event->rect(), Qt::black);
	}
	QWidget *m_widget;
};

PlayEngine::Data::Data() {
	gotInfo = muted = seekable = false;
	subVisible = true;
	prevTick = prevSubTime = -1;
	ampRate = pos = speed = 1.0;
	videoProps.append(0.0);
	videoProps.append(0.0);
	videoProps.append(0.0);
	videoProps.append(0.0);
	aspect = crop = -1.0;
	msgOsd = timeOsd = 0;
	renderer = 0;
	subRenderer = 0;
	duration = syncDelay = 0;
	volume = 100;
	state = Stopped;
	sub = new Subtitle;
	source = new MediaSource;
	msgStyle = new OsdStyle;
	subStyle = new OsdStyle;
	timeStyle = new OsdStyle;
	screen = new Screen;
	msgStyle->alignment = Qt::AlignLeft | Qt::AlignTop;
	msgStyle->scale = OsdStyle::FitToHeight;
	subStyle->alignment = Qt::AlignHCenter | Qt::AlignBottom;
	subStyle->font.setBold(true);
	timeStyle->alignment = Qt::AlignCenter;
	timeStyle->fgColor.setAlphaF(0.8);
	timeStyle->bgColor.setAlphaF(0.8);
	tracks.append("Auto Track");
	track = tracks[0];
}

PlayEngine::Data::~Data() {
	delete sub;
	delete source;
	delete msgStyle;
	delete subStyle;
	delete timeStyle;
	delete screen;
}

PlayEngine::PlayEngine(QObject *parent)
: QObject(parent), d(new Data) {}

PlayEngine::~PlayEngine() {
	if (d->subRenderer)
		delete d->subRenderer;
	delete d;
}

QWidget *PlayEngine::widget() {
	return d->screen;
}

void PlayEngine::setVideoRenderer(VideoRendererIface *renderer) {
	if (d->renderer != renderer)
		d->screen->setWidget((d->renderer = renderer) ? d->renderer->target() : 0);
}

void PlayEngine::play(int time) {
	play();
	seek(time);
}

void PlayEngine::setCurrentSource(const MediaSource &source) {
	stop();
	updateCurrentSource(source);
	emit currentSourceChanged(*d->source = source);
}

void PlayEngine::seek(int time, bool relative, bool showTimeLine, int duration) {
	if (!isSeekable() || (!isPlaying() && !isPaused()))
		return;
	if (relative)
		time += currentTime();
	time = qBound(0, time, d->duration);
	seek(time);
	if (showTimeLine)
		this->showTimeLine(time, duration);
}

void PlayEngine::showMessage(const QString &message, int duration) {
	if (duration > 0 && !message.isEmpty() && d->msgOsd)
		d->msgOsd->renderText(message, duration);
}

void PlayEngine::showTimeLine(int time, int duration) {
	if (d->timeOsd && duration > 0) {
		const double rate = double(time)/double(this->duration());
		d->timeOsd->renderTimeLine(rate, duration);
	}
}

void PlayEngine::showTimeLine(int duration) {
	showTimeLine(currentTime(), duration);
}

double PlayEngine::amplifyingRate() const {
	return d->ampRate;
}

void PlayEngine::setAmplifyingRate(double rate) {
	const double val = qBound(0., rate, 10.);
	if (qAbs((val - d->ampRate)/val) > 1.e-5) {
		d->ampRate = val;
		updateVolume();
	}
}

void PlayEngine::setVolume(int volume) {
	const int val = qBound(0, volume, 100);
	if (val != d->volume) {
		d->volume = val;
		updateVolume();
		emit volumeChanged(d->volume);
	}
}

bool PlayEngine::isMuted() const {
	return d->muted;
}

void PlayEngine::setMuted(bool muted) {
	if (d->muted != muted) {
		d->muted = muted;
		updateVolume();
		emit mutedChanged(d->muted);
	}
}

void PlayEngine::setSubtitle(const Subtitle &subtitle) {
	*d->sub = subtitle;
	d->sub->end();
	updateSubtitle(*d->sub);
}

double PlayEngine::aspectRatio() const {
	return d->aspect;
}

void PlayEngine::setAspectRatio(double ratio) {
	ratio = ratio > 0.0 ? ratio : -1.0;
	updateAspectRatio(ratio);
	d->aspect = ratio;
}

double PlayEngine::cropRatio() const {
	return d->crop;
}

void PlayEngine::setCropRatio(double ratio) {
	ratio = ratio > 0.0 ? ratio : -1.0;
	updateCropRatio(ratio);
	d->crop = ratio;
}

void PlayEngine::setSubtitleVisible(bool visible) {
	if (d->subVisible != visible) {
		updateSubtitleVisiblity(visible);
		d->subVisible = visible;
	}
}

bool PlayEngine::isSubtitleVisible() const {
	return d->subVisible;
}

void PlayEngine::setSubtitlePos(double pos) {
	pos = qBound(0.0, pos, 1.0);
	updateSubtitlePos(pos);
	d->pos = pos;
}

double PlayEngine::subtitlePos() const {
	return d->pos;
}

void PlayEngine::setSyncDelay(int delay) {
	if (d->syncDelay != delay) {
		updateSyncDelay(delay);
		emit syncDelayChanged(d->syncDelay = delay);
	}
}

void PlayEngine::setSubtitleStyle(const OsdStyle &style) {
	updateSubtitleStyle(style);
	*d->subStyle = style;
}

void PlayEngine::setMessageStyle(const OsdStyle &style) {
	updateMessageStyle(style);
	*d->msgStyle = style;
}

void PlayEngine::setTimeLineStyle(const OsdStyle &style) {
	updateTimeLineStyle(style);
	*d->timeStyle = style;
}

void PlayEngine::setSubtitleOsd(AbstractOsdRenderer *osd) {
	if (!d->subRenderer)
		d->subRenderer = new SubtitleRenderer(osd);
	else
		d->subRenderer->setRenderer(osd);
	osd->setStyle(*d->subStyle);
	connect(this, SIGNAL(tick(int)), this, SLOT(slotTick(int)));
}

void PlayEngine::setTimeLineOsd(AbstractOsdRenderer *osd) {
	d->timeOsd = osd;
	osd->setStyle(*d->timeStyle);
}

void PlayEngine::setMessageOsd(AbstractOsdRenderer *osd) {
	d->msgOsd = osd;
	osd->setStyle(*d->msgStyle);
}

void PlayEngine::slotTick(int time) {
	if (isSubtitleVisible())
		d->subRenderer->show(time);
}

void PlayEngine::updateSubtitle(const Subtitle &subtitle) {
	if (d->subRenderer) {
		d->subRenderer->setSubtitle(&subtitle);
		if (subtitle.isEmpty() || !isSubtitleVisible())
			d->subRenderer->clear();
		else
			d->subRenderer->show(currentTime());
	}
}

void PlayEngine::updateTimeLineStyle(const OsdStyle &style) {
	if (d->timeOsd)
		d->timeOsd->setStyle(style);
}

void PlayEngine::updateMessageStyle(const OsdStyle &style) {
	if (d->msgOsd)
		d->msgOsd->setStyle(style);
}

void PlayEngine::updateSubtitleStyle(const OsdStyle &style) {
	if (d->subRenderer)
		d->subRenderer->renderer()->setStyle(style);
}

void PlayEngine::updateSubtitleVisiblity(bool visible) {
	if (d->subRenderer) {
		if (visible)
			d->subRenderer->show(currentTime());
		else
			d->subRenderer->clear();
	}
}

void PlayEngine::updateSubtitlePos(double pos) {
	if (d->subRenderer)
		d->subRenderer->renderer()->setBottomMargin(1.0 - pos);
}

void PlayEngine::updateSyncDelay(int delay) {
	if (d->subRenderer) {
		d->subRenderer->setDelay(delay);
		if (isSubtitleVisible())
			d->subRenderer->show(currentTime());
	}
}

void PlayEngine::updateAspectRatio(double ratio) {
	if (d->renderer)
		d->renderer->setAspectRatio(ratio);
}

void PlayEngine::updateCropRatio(double ratio) {
	if (d->renderer)
		d->renderer->setCropRatio(ratio);
}

void PlayEngine::setState(State state) {
	if (d->state != state) {
		const State old = d->state;
		emit stateChanged(d->state = state, old);
	}
}

void PlayEngine::setDuration(int duration) {
	if (d->duration != duration)
		emit durationChanged(d->duration = duration);
}

void PlayEngine::setSeekable(bool seekable) {
	if (d->seekable != seekable)
		emit seekableChanged(d->seekable = seekable);
}

void PlayEngine::setSpeed(double speed) {
	speed = qBound(0.1, speed, 10.0);
	if (isSame(speed, 1.0))
		speed = 1.0;
	if (!isSame(d->speed, speed) > 1.0e-5) {
		updateSpeed(speed);
		emit speedChanged(d->speed = speed);
	}
}

double PlayEngine::speed() const {
	return d->speed;
}

void PlayEngine::setVideoProperty(VideoProperty prop, double value) {
	value = isSame(value, 0.0) ? 0.0 : qBound(-1.0, value, 1.0);
	if (!isSame(d->videoProps[prop], value)) {
		if (d->renderer && d->renderer->type() == OpenGL)
			PlayEngine::updateVideoProperty(prop, value);
		else
			updateVideoProperty(prop, value);
		d->videoProps[prop] = value;
	}
}

void PlayEngine::updateVideoProperty(VideoProperty prop, double value) {
	if (!d->renderer || d->renderer->type() != OpenGL)
		return;
	switch(prop) {
	case Brightness:
		updateVideoProperties(value, d->videoProps[Contrast]
				, d->videoProps[Saturation], d->videoProps[Hue]);
		break;
	case Contrast:
		updateVideoProperties(d->videoProps[Brightness], value
				, d->videoProps[Saturation], d->videoProps[Hue]);
		break;
	case Saturation:
		updateVideoProperties(d->videoProps[Brightness], d->videoProps[Contrast]
				, value, d->videoProps[Hue]);
		break;
	case Hue:
		updateVideoProperties(d->videoProps[Brightness], d->videoProps[Contrast]
				, d->videoProps[Saturation], value);
		break;
	default:
		break;
	}
}

void PlayEngine::updateVideoProperties(double b, double c, double s, double h) {
	Q_UNUSED(b);
	Q_UNUSED(c);
	Q_UNUSED(s);
	Q_UNUSED(h);
//	if (d->renderer && d->renderer->type() == OpenGL)
//		static_cast<GLRenderer*>(d->renderer)->setVideoProperties(b, c, s, h);
}

void PlayEngine::setVideoRenderer(const QString &name) {
	if (d->videoRenderer != name) {
		int time = -1;
		if (!isStopped()) {
			time = currentTime();
			stop();
		}
		if (updateVideoRenderer(name)) {
			d->videoRenderer = name;
			updateVideo();
			if (time != -1)
				play(time);
		}
	}
}

void PlayEngine::setAudioRenderer(const QString &name) {
	if (d->audioRenderer != name) {
		int time = -1;
		if (!isStopped()) {
			time = currentTime();
			stop();
		}
		if (updateAudioRenderer(name)) {
			d->audioRenderer = name;
			updateAudio();
			if (time != -1)
				play(time);
		}
	}
}

void PlayEngine::updateVideo() {
	updateAspectRatio(d->aspect);
	updateCropRatio(d->crop);
	updateVideoProperties(d->videoProps[Brightness], d->videoProps[Contrast]
			, d->videoProps[Saturation], d->videoProps[Hue]);
}
void PlayEngine::updateAudio() {
	updateVolume();
}

void PlayEngine::setTracks(const QStringList &tracks, const QString &track) {
	if (d->tracks != tracks) {
		int idx = -1;
		if (tracks.isEmpty()) {
			d->tracks.clear();
			d->tracks.append("Auto Track");
			idx = 0;
		}
		emit tracksChanged(d->tracks = tracks);
		if (!track.isEmpty())
			idx = d->tracks.indexOf(track);
		if (idx != -1)
			emit currentTrackChanged(d->track = tracks[idx]);
	}
}

void PlayEngine::setCurrentTrack(const QString &track) {
	if (d->track != track && updateCurrentTrack(track))
		emit currentTrackChanged(d->track = track);
}

void PlayEngine::setSpus(const QStringList &spus, const QString &spu) {
	if (d->spus != spus) {
		emit spusChanged(d->spus = spus);
		emit currentSpuChanged(d->spu = spu);
	}
}

void PlayEngine::setCurrentSpu(const QString &spu) {
	if (d->spu != spu && updateCurrentSpu(spu))
		emit currentSpuChanged(d->spu = spu);
}

double PlayEngine::realVolume() const {
	const double max = info().maximumAmplifyingRate();
	return qBound(0.0, volume()*0.01*amplifyingRate(), max);
}

}