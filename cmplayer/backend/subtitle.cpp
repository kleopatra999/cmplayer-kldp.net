#include "subtitle.h"
#include <QFileInfo>

namespace Backend {

Subtitle::Subtitle(const QString &filePath)
: d(new Data) {
	d->filePath = filePath;
}

Subtitle &Subtitle::unite(const Subtitle &other) {
	if (this == &other || other.isEmpty())
		return *this;
	else if (isEmpty()) {
		QMap<qint64, QString>::operator=(other);
		return *this;
	}
	SubtitleIterator it1(*this);
	SubtitleIterator it2(other);
	qlonglong t3 = -1;
	while(it1.hasNext()) {
		qlonglong t1 = it1.next().key();
		qlonglong t2 = it1.hasNext() ? it1.peekNext().key() : -1;
		if (t3 != -1 && it2.hasPrevious())
			(*this)[t1] = it1.value() + "<br>" + it2.peekPrevious().value();
		while(it2.hasNext()) {
			t3 = it2.next().key();
			if (t2 == -1) {
				(*this)[t3] = it1.value() + "<br>" + it2.value();
			} else if (t3 >= t2) {
				it2.previous();
				break;
			} else if (t3 == t1) {
				(*this)[t1] = it1.value() + "<br>" + it2.value();
			} else if (t3 > t1)
				(*this)[t3] = it1.value() + "<br>" + it2.value();
			else if (t3 < t1)
				(*this)[t3] = it2.value();
		}
	}
	return *this;
}

QString Subtitle::name() const {
	if (d->lang.isEmpty())
		return QFileInfo(d->filePath).fileName();
	else
		return QFileInfo(d->filePath).fileName() + " (" + d->lang + ')';
}

}
