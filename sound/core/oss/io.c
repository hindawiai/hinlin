<शैली गुरु>
/*
 *  PCM I/O Plug-In Interface
 *  Copyright (c) 1999 by Jaroslav Kysela <perex@perex.cz>
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
#समावेश <sound/pcm_params.h>
#समावेश "pcm_plugin.h"

#घोषणा pcm_ग_लिखो(plug,buf,count) snd_pcm_oss_ग_लिखो3(plug,buf,count,1)
#घोषणा pcm_ग_लिखोv(plug,vec,count) snd_pcm_oss_ग_लिखोv3(plug,vec,count)
#घोषणा pcm_पढ़ो(plug,buf,count) snd_pcm_oss_पढ़ो3(plug,buf,count,1)
#घोषणा pcm_पढ़ोv(plug,vec,count) snd_pcm_oss_पढ़ोv3(plug,vec,count)

/*
 *  Basic io plugin
 */
 
अटल snd_pcm_sframes_t io_playback_transfer(काष्ठा snd_pcm_plugin *plugin,
				    स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
				    काष्ठा snd_pcm_plugin_channel *dst_channels,
				    snd_pcm_uframes_t frames)
अणु
	अगर (snd_BUG_ON(!plugin))
		वापस -ENXIO;
	अगर (snd_BUG_ON(!src_channels))
		वापस -ENXIO;
	अगर (plugin->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED) अणु
		वापस pcm_ग_लिखो(plugin->plug, src_channels->area.addr, frames);
	पूर्ण अन्यथा अणु
		पूर्णांक channel, channels = plugin->dst_क्रमmat.channels;
		व्योम **bufs = (व्योम**)plugin->extra_data;
		अगर (snd_BUG_ON(!bufs))
			वापस -ENXIO;
		क्रम (channel = 0; channel < channels; channel++) अणु
			अगर (src_channels[channel].enabled)
				bufs[channel] = src_channels[channel].area.addr;
			अन्यथा
				bufs[channel] = शून्य;
		पूर्ण
		वापस pcm_ग_लिखोv(plugin->plug, bufs, frames);
	पूर्ण
पूर्ण
 
अटल snd_pcm_sframes_t io_capture_transfer(काष्ठा snd_pcm_plugin *plugin,
				   स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
				   काष्ठा snd_pcm_plugin_channel *dst_channels,
				   snd_pcm_uframes_t frames)
अणु
	अगर (snd_BUG_ON(!plugin))
		वापस -ENXIO;
	अगर (snd_BUG_ON(!dst_channels))
		वापस -ENXIO;
	अगर (plugin->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED) अणु
		वापस pcm_पढ़ो(plugin->plug, dst_channels->area.addr, frames);
	पूर्ण अन्यथा अणु
		पूर्णांक channel, channels = plugin->dst_क्रमmat.channels;
		व्योम **bufs = (व्योम**)plugin->extra_data;
		अगर (snd_BUG_ON(!bufs))
			वापस -ENXIO;
		क्रम (channel = 0; channel < channels; channel++) अणु
			अगर (dst_channels[channel].enabled)
				bufs[channel] = dst_channels[channel].area.addr;
			अन्यथा
				bufs[channel] = शून्य;
		पूर्ण
		वापस pcm_पढ़ोv(plugin->plug, bufs, frames);
	पूर्ण
	वापस 0;
पूर्ण
 
अटल snd_pcm_sframes_t io_src_channels(काष्ठा snd_pcm_plugin *plugin,
			     snd_pcm_uframes_t frames,
			     काष्ठा snd_pcm_plugin_channel **channels)
अणु
	पूर्णांक err;
	अचिन्हित पूर्णांक channel;
	काष्ठा snd_pcm_plugin_channel *v;
	err = snd_pcm_plugin_client_channels(plugin, frames, &v);
	अगर (err < 0)
		वापस err;
	*channels = v;
	अगर (plugin->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED) अणु
		क्रम (channel = 0; channel < plugin->src_क्रमmat.channels; ++channel, ++v)
			v->wanted = 1;
	पूर्ण
	वापस frames;
पूर्ण

पूर्णांक snd_pcm_plugin_build_io(काष्ठा snd_pcm_substream *plug,
			    काष्ठा snd_pcm_hw_params *params,
			    काष्ठा snd_pcm_plugin **r_plugin)
अणु
	पूर्णांक err;
	काष्ठा snd_pcm_plugin_क्रमmat क्रमmat;
	काष्ठा snd_pcm_plugin *plugin;

	अगर (snd_BUG_ON(!r_plugin))
		वापस -ENXIO;
	*r_plugin = शून्य;
	अगर (snd_BUG_ON(!plug || !params))
		वापस -ENXIO;
	क्रमmat.क्रमmat = params_क्रमmat(params);
	क्रमmat.rate = params_rate(params);
	क्रमmat.channels = params_channels(params);
	err = snd_pcm_plugin_build(plug, "I/O io",
				   &क्रमmat, &क्रमmat,
				   माप(व्योम *) * क्रमmat.channels,
				   &plugin);
	अगर (err < 0)
		वापस err;
	plugin->access = params_access(params);
	अगर (snd_pcm_plug_stream(plug) == SNDRV_PCM_STREAM_PLAYBACK) अणु
		plugin->transfer = io_playback_transfer;
		अगर (plugin->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED)
			plugin->client_channels = io_src_channels;
	पूर्ण अन्यथा अणु
		plugin->transfer = io_capture_transfer;
	पूर्ण

	*r_plugin = plugin;
	वापस 0;
पूर्ण
