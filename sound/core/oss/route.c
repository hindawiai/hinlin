<शैली गुरु>
/*
 *  Route Plug-In
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

अटल व्योम zero_areas(काष्ठा snd_pcm_plugin_channel *dvp, पूर्णांक ndsts,
		       snd_pcm_uframes_t frames, snd_pcm_क्रमmat_t क्रमmat)
अणु
	पूर्णांक dst = 0;
	क्रम (; dst < ndsts; ++dst) अणु
		अगर (dvp->wanted)
			snd_pcm_area_silence(&dvp->area, 0, frames, क्रमmat);
		dvp->enabled = 0;
		dvp++;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम copy_area(स्थिर काष्ठा snd_pcm_plugin_channel *src_channel,
			     काष्ठा snd_pcm_plugin_channel *dst_channel,
			     snd_pcm_uframes_t frames, snd_pcm_क्रमmat_t क्रमmat)
अणु
	dst_channel->enabled = 1;
	snd_pcm_area_copy(&src_channel->area, 0, &dst_channel->area, 0, frames, क्रमmat);
पूर्ण

अटल snd_pcm_sframes_t route_transfer(काष्ठा snd_pcm_plugin *plugin,
					स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
					काष्ठा snd_pcm_plugin_channel *dst_channels,
					snd_pcm_uframes_t frames)
अणु
	पूर्णांक nsrcs, ndsts, dst;
	काष्ठा snd_pcm_plugin_channel *dvp;
	snd_pcm_क्रमmat_t क्रमmat;

	अगर (snd_BUG_ON(!plugin || !src_channels || !dst_channels))
		वापस -ENXIO;
	अगर (frames == 0)
		वापस 0;
	अगर (frames > dst_channels[0].frames)
		frames = dst_channels[0].frames;

	nsrcs = plugin->src_क्रमmat.channels;
	ndsts = plugin->dst_क्रमmat.channels;

	क्रमmat = plugin->dst_क्रमmat.क्रमmat;
	dvp = dst_channels;
	अगर (nsrcs <= 1) अणु
		/* expand to all channels */
		क्रम (dst = 0; dst < ndsts; ++dst) अणु
			copy_area(src_channels, dvp, frames, क्रमmat);
			dvp++;
		पूर्ण
		वापस frames;
	पूर्ण

	क्रम (dst = 0; dst < ndsts && dst < nsrcs; ++dst) अणु
		copy_area(src_channels, dvp, frames, क्रमmat);
		dvp++;
		src_channels++;
	पूर्ण
	अगर (dst < ndsts)
		zero_areas(dvp, ndsts - dst, frames, क्रमmat);
	वापस frames;
पूर्ण

पूर्णांक snd_pcm_plugin_build_route(काष्ठा snd_pcm_substream *plug,
			       काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			       काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
			       काष्ठा snd_pcm_plugin **r_plugin)
अणु
	काष्ठा snd_pcm_plugin *plugin;
	पूर्णांक err;

	अगर (snd_BUG_ON(!r_plugin))
		वापस -ENXIO;
	*r_plugin = शून्य;
	अगर (snd_BUG_ON(src_क्रमmat->rate != dst_क्रमmat->rate))
		वापस -ENXIO;
	अगर (snd_BUG_ON(src_क्रमmat->क्रमmat != dst_क्रमmat->क्रमmat))
		वापस -ENXIO;

	err = snd_pcm_plugin_build(plug, "route conversion",
				   src_क्रमmat, dst_क्रमmat, 0, &plugin);
	अगर (err < 0)
		वापस err;

	plugin->transfer = route_transfer;
	*r_plugin = plugin;
	वापस 0;
पूर्ण
