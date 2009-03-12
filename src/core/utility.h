#ifndef CORE_UTILITY_H
#define CORE_UTILITY_H

#include <QtCore/QTime>

class QSize;

namespace Core {

class Utility {
public:
	static QTime secsToTime(int secs) {
		return get()->zero.addSecs(secs);
	}
	static QTime msecsToTime(qint64 msecs) {
		return get()->zero.addMSecs(msecs);
	}
	static QString msecsToString(qint64 msecs, const QString &format = QString("hh:mm:ss")) {
		return msecsToTime(msecs).toString(format);
	}
	static QString secsToString(int secs, const QString &format = QString("hh:mm:ss")) {
		return secsToTime(secs).toString(format);
	}
	static qint64 timeToMSecs(const QTime &time) {
		return get()->zero.msecsTo(time);
	}
	static qint64 stringToMSecs(const QString &str, const QString &format = QString("hh:mm:ss")) {
		return timeToMSecs(QTime::fromString(str, format));
	}
	static const QTime &nullTime() {return get()->zero;}
	static double desktopRatio();
	static const QSize &desktopSize();
private:
	static Utility *get() {static Utility obj; return &obj;}
	Utility(): zero() {}
	const QTime zero;
};

}

#endif