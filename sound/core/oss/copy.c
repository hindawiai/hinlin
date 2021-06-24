<शैली गुरु>
/*
 *  Linear conversion Plug-In
 *  Copyright (c) 2000 by Abramo Bagnara <abramo@alsa-project.org>
 *
 *
 *   This library is मुक्त software; you can redistribute it and/or modअगरy
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 2 of
 *   the License, or (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU Library General Public License क्रम more details.
 *
 *   You should have received a copy of the GNU Library General Public
 *   License aदीर्घ with this library; अगर not, ग_लिखो to the Free Software
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307 USA
 *
 */

#समावेश <linux/समय.स>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश "pcm_plugin.h"

अटल snd_pcm_sframes_t copy_transfer(काष्ठा snd_pcm_plugin *plugin,
			     स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			     काष्ठा snd_pcm_plugin_channel *dst_channels,
			     snd_pcm_uframes_t frames)
अणु
	अचिन्हित पूर्णांक channel;
	अचिन्हित पूर्णांक nchannels;

	अगर (snd_BUG_ON(!plugin || !src_channels || !dst_channels))
		वापस -ENXIO;
	अगर (frames == 0)
		वापस 0;
	nchannels = plugin->src_क्रमmat.channels;
	क्रम (channel = 0; channel < nchannels; channel++) अणु
		अगर (snd_BUG_ON(src_channels->area.first % 8 ||
			       src_channels->area.step % 8))
			वापस -ENXIO;
		अगर (snd_BUG_ON(dst_channels->area.first % 8 ||
			       dst_channels->area.step % 8))
			वापस -ENXIO;
		अगर (!src_channels->enabled) अणु
			अगर (dst_channels->wanted)
				snd_pcm_area_silence(&dst_channels->area, 0, frames, plugin->dst_क्रमmat.क्रमmat);
			dst_channels->enabled = 0;
			जारी;
		पूर्ण
		dst_channels->enabled = 1;
		snd_pcm_area_copy(&src_channels->area, 0, &dst_channels->area, 0, frames, plugin->src_क्रमmat.क्रमmat);
		src_channels++;
		dst_channels++;
	पूर्ण
	वापस frames;
पूर्ण

पूर्णांक snd_pcm_plugin_build_copy(काष्ठा snd_pcm_substream *plug,
			      काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			      काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
			      काष्ठा snd_pcm_plugin **r_plugin)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm_plugin *plugin;
	पूर्णांक width;

	अगर (snd_BUG_ON(!r_plugin))
		वापस -ENXIO;
	*r_plugin = शून्य;

	अगर (snd_BUG_ON(src_क्रमmat->क्रमmat != dst_क्रमmat->क्रमmat))
		वापस -ENXIO;
	अगर (snd_BUG_ON(src_क्रमmat->rate != dst_क्रमmat->rate))
		वापस -ENXIO;
	अगर (snd_BUG_ON(src_क्रमmat->channels != dst_क्रमmat->channels))
		वापस -ENXIO;

	width = snd_pcm_क्रमmat_physical_width(src_क्रमmat->क्रमmat);
	अगर (snd_BUG_ON(width <= 0))
		वापस -ENXIO;

	err = snd_pcm_plugin_build(plug, "copy", src_क्रमmat, dst_क्रमmat,
				   0, &plugin);
	अगर (err < 0)
		वापस err;
	plugin->transfer = copy_transfer;
	*r_plugin = plugin;
	वापस 0;
पूर्ण
