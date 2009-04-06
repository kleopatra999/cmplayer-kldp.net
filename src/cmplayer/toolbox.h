#ifndef TOOLBOX_H
#define TOOLBOX_H

#include <QtGui/QDialog>
#include "designedwidgetiface.h"
class PlaylistModel;

class ToolBox : public QDialog, public DesignedWidgetIface {
	Q_OBJECT
public:
	ToolBox(PlaylistModel *model, QWidget *parent = 0);
	~ToolBox();
signals:
	void hidingRequested();
	void snapRequested();
private:
	QRect boxRect() const {return QRect(3, 3, width()-6, height() - 6);}
	void closeEvent(QCloseEvent *event);
	void paintEvent(QPaintEvent *event);
	void resizeEvent(QResizeEvent *event);
	class Frame;
	struct Data;
	Data *d;
};

#endif
