#include "info.h"
#include "xineengine.h"

namespace Xine {

Info::Data Info::d;

Info::Data::Data() {}

const QStringList &Info::videoRenderer() const {
	if (d.videoRenderers.isEmpty()) {
		d.videoRenderers.append("auto");
		const char *const *vos = xine_list_video_output_plugins(XineEngine::xine());
		for (int i=0; vos[i]; ++i)
			d.videoRenderers.append(vos[i]);
	}
	return d.videoRenderers;
}

const QStringList &Info::audioRenderer() const {
	if (d.audioRenderers.isEmpty()) {
		d.audioRenderers.append("auto");
		const char *const *aos = xine_list_audio_output_plugins(XineEngine::xine());
		for (int i=0; aos[i]; ++i)
			d.audioRenderers.append(aos[i]);
	}
	return d.audioRenderers;
}

}