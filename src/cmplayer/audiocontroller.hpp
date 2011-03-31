#ifndef AUDIOCONTROLLER_HPP
#define AUDIOCONTROLLER_HPP

#include <QtCore/QObject>

class PlayEngine;		class AudioFormat;
class AudioBuffer;		class AudioUtil;

class AudioController : public QObject {
	Q_OBJECT
public:
	AudioController(/*PlayEngine *engine*/);
	~AudioController();
	int volume() const;
	bool isMuted() const;
	void setPreAmp(double amp);
	double preAmp() const;
	bool isVolumeNormalized() const;
	bool isTempoScaled() const;
public slots:
	void setVolumeNormalized(bool norm);
	void setVolume(int volume);
	void setTempoScaled(bool scaled);
	void setMuted(bool muted);
signals:
	void volumeChanged(int volume);
	void mutedChanged(bool muted);
	void volumeNormalizedChanged(bool norm);
	void tempoScaledChanged(bool scaled);
private:
	void setUtil(AudioUtil *util);
	void prepare(const AudioFormat *format);
	AudioBuffer *process(AudioBuffer *in);
	friend class LibVLC;
	struct Data;
	Data *d;
};

#endif // AUDIOCONTROLLER_HPP