#ifndef BACKEND_PLAYLIST_H
#define BACKEND_PLAYLIST_H

#include <QList>
#include "mediasource.h"

namespace Backend {

class PlayList : public QList<MediaSource> {
public:
	PlayList();
	PlayList(const PlayList &rhs);
	PlayList(const QList<MediaSource> &rhs);
	bool save(const QString &filePath) const;
	bool load(const QString &filePath);
};

}

#endif
