#ifndef XINE_GLRENDERER_H
#define XINE_GLRENDERER_H

#include <xine.h>

#if (XINE_MAJOR_VERSION >= 1 && XINE_MINOR_VERSION >= 1 && XINE_SUB_VERSION >= 12)
#define HAS_RAW_OUTPUT 1
#else
#define HAS_RAW_OUTPUT 0
#endif

#if HAS_RAW_OUTPUT

#include <core/openglvideorendereriface.h>
#include "xinevideoiface.h"

namespace Xine {

class GLRenderer : public QObject, public Core::OpenGLVideoRendererIface::Object, public XineVideoIface {
public:
	class Overlay;
	GLRenderer(XineStream *stream);
	~GLRenderer();
	void *visual();
	int xineType() const {return XINE_VISUAL_TYPE_RAW;}
	Core::OpenGLVideoRendererIface *renderer();
private:
	void overdraw(QPainter *painter);
	void customEvent(QEvent *event);
	void mouseMoveEvent(const QPoint &pos);
	void mousePressEvent(const QPoint &pos, Qt::MouseButton button);
	static void cbRawOutput(void *user_data, int frame_format
			, int frame_width, int frame_height, double frame_aspect
			, void *data0, void *data1, void *data2);
	static void cbRawOverlay(void *user_data, int num_ovl, raw_overlay_t *overlays_array);
	struct Data;
	Data *d;
};

}

#endif

#endif
