//#include "glvideorenderer.hpp"
//#include <QtCore/QDebug>
////#include "osdrenderer.h"
//#include "colorproperty.hpp"
//#include "events.hpp"
////#include <QtGui/QMouseEvent>
////#include <QtGui/QPainter>
//#include <QtGui/QApplication>
////#include <QtCore/QDebug>
//#include "qwidgetvideosink.hpp"
//
//#include <qmath.h>
//#ifndef M_PI
//#define M_PI 3.14159265358979323846264338327950288419717
//#endif
//
//const char *const yv12ToRgb =
//    "!!ARBfp1.0"
//    "PARAM c[3] = { { 0.5, 0.0625 },"
//    "{ 1.164, 0, 1.596, 2.0179999 },"
//    "{ 1.164, -0.391, -0.81300002 } };"
//    "TEMP R0;"
//    "TEMP R1;"
//    "TEX R0.x, fragment.texcoord[0], texture[2], 2D;"
//    "ADD R1.z, R0.x, -c[0].x;"
//    "TEX R1.x, fragment.texcoord[0], texture[0], 2D;"
//    "TEX R0.x, fragment.texcoord[0], texture[1], 2D;"
//    "ADD R1.x, R1, -c[0].y;"
//    "ADD R1.y, R0.x, -c[0].x;"
//    "DP3 result.color.x, R1, c[1];"
//    "DP3 result.color.y, R1, c[2];"
//    "DP3 result.color.z, R1, c[1].xwyw;"
//    "END";
//
//const char *GLVideoRenderer::yv12ToRgb =
//	"!!ARBfp1.0"
//	"PARAM c[5] = {"
//	"	program.local[0..1],"
//	"	{ 1.164, 0, 1.596, 0.5 },"
//	"	{ 0.0625, 1.164, -0.391, -0.81300002 },"
//	"	{ 1.164, 2.0179999, 0 }"
//	"};"
//	"TEMP R0;"
//	"TEX R0.x, fragment.texcoord[0], texture[1], 2D;"
//	"ADD R0.y, R0.x, -c[2].w;"
//	"TEX R0.x, fragment.texcoord[0], texture[2], 2D;"
//	"ADD R0.x, R0, -c[2].w;"
//	"MUL R0.z, R0.y, c[0].w;"
//	"MAD R0.z, R0.x, c[0], R0;"
//	"MUL R0.w, R0.x, c[0];"
//	"MUL R0.z, R0, c[0].y;"
//	"TEX R0.x, fragment.texcoord[0], texture[0], 2D;"
//	"MAD R0.y, R0, c[0].z, R0.w;"
//	"ADD R0.x, R0, -c[3];"
//	"MUL R0.y, R0, c[0];"
//	"MUL R0.z, R0, c[1].x;"
//	"MAD R0.x, R0, c[0].y, c[0];"
//	"MUL R0.y, R0, c[1].x;"
//	"DP3 result.color.x, R0, c[2];"
//	"DP3 result.color.y, R0, c[3].yzww;"
//	"DP3 result.color.z, R0, c[4];"
//	"MOV result.color.w, c[1].y;"
//	"END";
//
//const char *GLVideoRenderer::yuy2ToRgb =
//	"!!ARBfp1.0"
//	"PARAM c[5] = { program.local[0..1],"
//	"                { 0.5, 2, 1, 0.0625 },"
//	"                { 1.164, 0, 1.596, 2.0179999 },"
//	"                { 1.164, -0.391, -0.81300002 } };"
//	"TEMP R0;"
//	"TEMP R1;"
//	"TEMP R2;"
//	"FLR R1.z, fragment.texcoord[0].x;"
//	"ADD R0.x, R1.z, c[2];"
//	"ADD R1.z, fragment.texcoord[0].x, -R1;"
//	"MUL R1.x, fragment.texcoord[0].z, R0;"
//	"MOV R1.y, fragment.texcoord[0];"
//	"TEX R0, R1, texture[0], 2D;"
//	"ADD R1.y, R0.z, -R0.x;"
//	"MUL R2.x, R1.z, R1.y;"
//	"MAD R0.x, R2, c[2].y, R0;"
//	"MOV R1.y, fragment.texcoord[0];"
//	"ADD R1.x, fragment.texcoord[0].z, R1;"
//	"TEX R1.xyw, R1, texture[0], 2D;"
//	"ADD R2.x, R1, -R0.z;"
//	"MAD R1.x, R1.z, c[2].y, -c[2].z;"
//	"MAD R0.z, R1.x, R2.x, R0;"
//	"ADD R1.xy, R1.ywzw, -R0.ywzw;"
//	"ADD R0.z, R0, -R0.x;"
//	"SGE R1.w, R1.z, c[2].x;"
//	"MAD R0.x, R1.w, R0.z, R0;"
//	"MAD R0.yz, R1.z, R1.xxyw, R0.xyww;"
//	"ADD R0.xyz, R0, -c[2].wxxw;"
//	"MUL R0.w, R0.y, c[0];"
//	"MAD R0.w, R0.z, c[0].z, R0;"
//	"MUL R0.z, R0, c[0].w;"
//	"MAD R0.y, R0, c[0].z, R0.z;"
//	"MUL R0.w, R0, c[0].y;"
//	"MUL R0.y, R0, c[0];"
//	"MUL R0.z, R0.w, c[1].x;"
//	"MAD R0.x, R0, c[0].y, c[0];"
//	"MUL R0.y, R0, c[1].x;"
//	"DP3 result.color.x, R0, c[3];"
//	"DP3 result.color.y, R0, c[4];"
//	"DP3 result.color.z, R0, c[3].xwyw;"
//	"MOV result.color.w, c[1].y;"
//	"END";
//
//struct GLVideoRenderer::Data {
//	GLuint texture[3];
//	bool hasPrograms, frameSet;
//	GLuint program[2];
//	double brightness, contrast, saturation, hue;
//	QByteArray data;
//	VideoFrame::Info frameInfo;
//	QSize videoSize;
//	QRectF imageRect;
//	GstElement *sink;
//	//	double m_vscale, m_hscale, m_vmargin, m_hmargin;
//	//	QSizeF m_visual, m_widget;
//	//	Object *m_obj;
////	QImage image;
////	QList<OsdRenderer*> osds;
//};
//
//GLVideoRenderer::GLVideoRenderer(QWidget *parent)
//: QGLWidget(makeFormat(), parent), d(new Data) {
//	setAttribute(Qt::WA_NativeWindow);
//	d->brightness = d->hue = 0.0;
//	d->contrast = d->saturation = 1.0;
//	d->frameSet = false;
//	makeCurrent();
//
//#define GET_PROC_ADDRESS(func) func = (_##func)context()->getProcAddress(QLatin1String(#func))
//	GET_PROC_ADDRESS(glProgramStringARB);
//	GET_PROC_ADDRESS(glBindProgramARB);
//	GET_PROC_ADDRESS(glDeleteProgramsARB);
//	GET_PROC_ADDRESS(glGenProgramsARB);
//	GET_PROC_ADDRESS(glActiveTexture);
//	GET_PROC_ADDRESS(glProgramLocalParameter4fARB);
//#undef GET_PROC_ADDRESS
//
//	d->hasPrograms = glProgramStringARB && glBindProgramARB && glDeleteProgramsARB;
//	d->hasPrograms = d->hasPrograms && glGenProgramsARB && glActiveTexture;
//	d->hasPrograms = d->hasPrograms && glProgramLocalParameter4fARB;
//
//	if (d->hasPrograms) {
//		glGenProgramsARB(2, d->program);
//		const char *code[] = {::yv12ToRgb, yuy2ToRgb};
//		bool error = false;
//		for(int i = 0; i < 2 && !error;  ++i) {
//			glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, d->program[i]);
//			const GLbyte *gl_src = reinterpret_cast<const GLbyte *>(code[i]);
//			glProgramStringARB(GL_FRAGMENT_PROGRAM_ARB, GL_PROGRAM_FORMAT_ASCII_ARB
//					, strlen(code[i]), gl_src);
//			if (glGetError() != GL_NO_ERROR)
//				error = true;
//		}
//		if (error) {
//			glDeleteProgramsARB(2, d->program);
//			d->hasPrograms = false;
//		}
//	}
//
//	glGenTextures(3, d->texture);
//
//	d->sink = GST_ELEMENT(g_object_new(QWidgetVideoSink::gtype(), 0));
//	reinterpret_cast<QWidgetVideoSink*>(d->sink)->sink = this;
//	gst_object_ref(GST_OBJECT(d->sink));
//	gst_object_sink(GST_OBJECT(d->sink));
//}
//
//GLVideoRenderer::~GLVideoRenderer() {
//	gst_object_unref(GST_OBJECT(d->sink));
//	makeCurrent();
//	glDeleteTextures(3, d->texture);
////	for (int i=0; i<d->osds.size(); ++i)
////		delete d->osds[i];
//
//	delete d;
//}
//
//QGLFormat GLVideoRenderer::makeFormat() {
//	QGLFormat format = QGLFormat::defaultFormat();
//	format.setSwapInterval(1);
//	return format;
//}
//
//void GLVideoRenderer::rerender() {
//
//}
//
//void GLVideoRenderer::setFrame(const VideoFrame &frame) {
//	QApplication::postEvent(this, new NewFrameEvent(frame));
//}
//
//void GLVideoRenderer::setColorProperty(const ColorProperty &prop) {
//	d->brightness = qBound(-0.5, prop.brightness()*0.5, 0.5);
//	d->contrast = qBound(0., prop.contrast() + 1., 2.);
//	d->saturation = qBound(0., prop.saturation() + 1., 2.);
//	d->hue = qBound(-M_PI, prop.hue()*M_PI, M_PI);
//	update();
//}
////
////void GLVideoRenderer::resizeEvent(QResizeEvent */*event*/) {
////	setWidgetSize(size());
////	calculate();
////}
//
//void GLVideoRenderer::updateFrameInfo(const VideoFrame::Info &info) {
//	if (d->frameInfo == info)
//		return;
//	d->frameInfo = info;
//
//	QSize size = info.size;
//	if (info.pixelAspectRatio > 1.)
//		size.rwidth() *= info.pixelAspectRatio;
//	else
//		size.rheight() /= info.pixelAspectRatio;
//	if (size != d->videoSize) {
//		d->videoSize = size;
////		m_videoRatio = ratio(m_videoSize = size);
////		m_aspectF = m_aspect > 0. ? m_aspect : m_videoRatio;
//		calculate();
//	}
//}
//
//void GLVideoRenderer::calculate() {
//	d->imageRect = QRectF(QPointF(0, 0), d->videoSize);
////	QSizeF video(aspectRatioF(), 1.0);
////	QSizeF visual = video;
////	if (cropRatio() > 0.0) {
////		visual.setWidth(cropRatio());
////		visual.setHeight(1.0);
////	}
////	visual.scale(m_widget, Qt::KeepAspectRatio);
////	video.scale(visual, Qt::KeepAspectRatioByExpanding);
////	const double x = (m_widget.width() - video.width())/2.0;
////	const double y = (m_widget.height() -video.height())/2.0;
////	setImageRect(x, y, video);
////	m_hmargin = (m_widget.width() - visual.width())/2.0;
////	m_vmargin = (m_widget.height() - visual.height())/2.0;
////	hscale() = video.width() / double(videoSize().width());
////	vscale() = video.height() / double(videoSize().height());
////	const double pixel = d->frameInfo.pixelAspectRatio;
////	if (pixel > 1.)
////		hscale() *= pixel;
////	else
////		vscale() /= pixel;
////	m_visual = visual;
//	//	for (int i=0; i<d->osds.size(); ++i)
//	//		d->osds[i]->setSize(visualSize(), widgetSize());
//}
//
//
//void GLVideoRenderer::customEvent(QEvent *event) {
//	if (event->type() != BaseEvent::NewFrame)
//		return;
//	const VideoFrame frame = static_cast<NewFrameEvent*>(event)->frame();
//	d->frameSet = !frame.isNull() && frame.info().type != VideoFrame::NoFrame;
//	const bool sizeChanged = d->frameInfo.size != frame.info().size;
//	updateFrameInfo(frame.info());
//	if (!d->frameSet)
//		return;
//	const int width = d->frameInfo.size.width();
//	const int height = d->frameInfo.size.height();
//	makeCurrent();
//	switch (d->frameInfo.type) {
//	case VideoFrame::I420:
//	case VideoFrame::YV12: {
//		const int w[3] = {width, width/2, width/2};
//		const int h[3] = {height, height/2, height/2};
//		int offset[3] = {0, w[0]*h[0]*5/4, w[0]*h[0]};
//		if (d->frameInfo.type == VideoFrame::YV12)
//			qSwap(offset[1], offset[2]);
//		for (int i=0; i<3; ++i) {
//			glBindTexture(GL_TEXTURE_2D, d->texture[i]);
//			if (sizeChanged)
//				glTexImage2D(GL_TEXTURE_2D, 0, GL_LUMINANCE, w[i], h[i], 0
//						, GL_LUMINANCE, GL_UNSIGNED_BYTE, frame.data() + offset[i]);
//			else
//				glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, w[i], h[i]
//						, GL_LUMINANCE, GL_UNSIGNED_BYTE, frame.data() + offset[i]);
//			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//			glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		}
//		break;
//	} case VideoFrame::YUY2: {
//		glBindTexture(GL_TEXTURE_2D, d->texture[0]);
//		if (sizeChanged)
//			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width/2, height, 0
//				, GL_RGBA, GL_UNSIGNED_BYTE, frame.data());
//		else
//			glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, width/2, height
//				, GL_RGBA, GL_UNSIGNED_BYTE, frame.data());
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
//		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
//		break;
//	} default:
//		d->frameSet = false;
//		break;
//	}
//	update();
//}
//
//void GLVideoRenderer::paintEvent(QPaintEvent */*event*/) {
//	QPainter painter(this);
////	painter.fillRect(rect(), Qt::black);
//	if (!d->frameSet)
//		return;
//	if (d->frameInfo.type == VideoFrame::I420 || d->frameInfo.type == VideoFrame::YV12)
//		glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, d->program[0]);
//	else if (d->frameInfo.type == VideoFrame::YUY2)
//		glBindProgramARB(GL_FRAGMENT_PROGRAM_ARB, d->program[1]);
//	else
//		return;
////	glProgramLocalParameter4fARB(GL_FRAGMENT_PROGRAM_ARB, 0.0f, d->brightness
////			, d->contrast, qCos(d->hue), qSin(d->hue));
////	glProgramLocalParameter4fARB(GL_FRAGMENT_PROGRAM_ARB, 1.0f, d->saturation
////			, 1. /*alpha */, 0. /*dummy*/, 0. /*dummy*/);
//	glEnable(GL_FRAGMENT_PROGRAM_ARB);
//
//	float tx_array[12] = {0., 0., 0., 1., 0., 0., 1., 1., 0., 0., 1., 0.};
////	float tx_array[] = { 0, 0, 1, 0, 1, 1, 0, 1};
//	d->imageRect = rect();
//	const float v_array[] = { d->imageRect.left(), d->imageRect.top(), d->imageRect.right() + 1.
//		, d->imageRect.top(), d->imageRect.right() + 1., d->imageRect.bottom() + 1.
//			, d->imageRect.left(), d->imageRect.bottom() + 1. };
//	if (d->frameInfo.type == VideoFrame::YUY2) {
//		qDebug() << "yuy2";
//		const float w = d->frameInfo.size.width() / 2;
//		const float iw = 1./w;
//		tx_array[3] = w;
//		tx_array[6] = w;
//		for (int i = 0; i < 4; ++i)
//			tx_array[3*i + 2] = iw;
//	}
//	glActiveTexture(GL_TEXTURE0);
//	glBindTexture(GL_TEXTURE_2D, d->texture[0]);
//	if (d->frameInfo.type == VideoFrame::I420 || d->frameInfo.type == VideoFrame::YV12) {
//		glActiveTexture(GL_TEXTURE1);
//		glBindTexture(GL_TEXTURE_2D, d->texture[2]);
//		glActiveTexture(GL_TEXTURE2);
//		glBindTexture(GL_TEXTURE_2D, d->texture[1]);
//		glActiveTexture(GL_TEXTURE0);
//	}
//	glVertexPointer(2, GL_FLOAT, 0, v_array);
//	glTexCoordPointer(3, GL_FLOAT, 0, tx_array);
//	glEnableClientState(GL_VERTEX_ARRAY);
//	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
//	glDrawArrays(GL_QUADS, 0, 4);
//	glDisableClientState(GL_TEXTURE_COORD_ARRAY);
//	glDisableClientState(GL_VERTEX_ARRAY);
//
//	glDisable(GL_FRAGMENT_PROGRAM_ARB);
//
////	if (vmargin() > 0.5) {
////		QRectF rect(0.0, 0.0, width(), vmargin());
////		painter.fillRect(rect, Qt::black);
////		rect.moveTop(height() - vmargin());
////		painter.fillRect(rect, Qt::black);
////	}
////	if (hmargin() > 0.5) {
////		QRectF rect(0.0, 0.0, hmargin(), height());
////		painter.fillRect(rect, Qt::black);
////		rect.moveLeft(width() - hmargin());
////		painter.fillRect(rect, Qt::black);
////	}
////	painter.fillRect(QRect(0, 0, 0, 0), Qt::white);
////	for (int i=0; i<d->osds.size(); ++i)
////		d->osds[i]->renderContents(&painter);
////	if (object())
////		object()->overdraw(&painter);
//}
//
//GstElement *GLVideoRenderer::sink() const {
//	return d->sink;
//}
//
////
////void GLVideoRenderer::rerender() {
////	calculate();
////	update();
////}
////
////AbstractOsdRenderer *GLVideoRenderer::createOsd() {
////	OsdRenderer *osd = new OsdRenderer(this);
////	d->osds.push_back(osd);
////	return osd;
////}
////
////void GLVideoRenderer::mouseMoveEvent(QMouseEvent *event) {
////	if (object())
////		object()->mouseMoveEvent(event->pos());
////	QGLWidget::mouseMoveEvent(event);
////}
////
////void GLVideoRenderer::mousePressEvent(QMouseEvent *event) {
////	if (object())
////		object()->mousePresseEvent(event->pos(), event->button());
////	QGLWidget::mousePressEvent(event);
////}
////
////}
//
//