#ifndef TEXTOSDRENDERER_HPP
#define TEXTOSDRENDERER_HPP

#include "osdrenderer.hpp"

class TextOsdRenderer : public OsdRenderer {
	Q_OBJECT
public:
	TextOsdRenderer(Qt::Alignment align = Qt::AlignTop | Qt::AlignHCenter);
	~TextOsdRenderer();
	RichString text() const;
	void showText(const RichString &text, int last = -1);
	void clear();
	void setMargin(double top, double bottom, double right, double left);
protected:
	void render(QPainter *painter);
	void areaChanged(const QRect &area);
	void styleChanged(const OsdStyle &style);
	QPoint posHint() const;
	QSize sizeHint() const;
	QRect rectHint() const;
private:
	QPoint getPos() const;
	void updateFontSize();
	struct Data;
	Data *d;
};

#endif // TEXTOSDRENDERER_HPP
