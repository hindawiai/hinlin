<शैली गुरु>
/*
 *  Rate conversion Plug-In
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
#समावेश "pcm_plugin.h"

#घोषणा SHIFT	11
#घोषणा BITS	(1<<SHIFT)
#घोषणा R_MASK	(BITS-1)

/*
 *  Basic rate conversion plugin
 */

काष्ठा rate_channel अणु
	चिन्हित लघु last_S1;
	चिन्हित लघु last_S2;
पूर्ण;
 
प्रकार व्योम (*rate_f)(काष्ठा snd_pcm_plugin *plugin,
		       स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
		       काष्ठा snd_pcm_plugin_channel *dst_channels,
		       पूर्णांक src_frames, पूर्णांक dst_frames);

काष्ठा rate_priv अणु
	अचिन्हित पूर्णांक pitch;
	अचिन्हित पूर्णांक pos;
	rate_f func;
	snd_pcm_sframes_t old_src_frames, old_dst_frames;
	काष्ठा rate_channel channels[];
पूर्ण;

अटल व्योम rate_init(काष्ठा snd_pcm_plugin *plugin)
अणु
	अचिन्हित पूर्णांक channel;
	काष्ठा rate_priv *data = (काष्ठा rate_priv *)plugin->extra_data;
	data->pos = 0;
	क्रम (channel = 0; channel < plugin->src_क्रमmat.channels; channel++) अणु
		data->channels[channel].last_S1 = 0;
		data->channels[channel].last_S2 = 0;
	पूर्ण
पूर्ण

अटल व्योम resample_expand(काष्ठा snd_pcm_plugin *plugin,
			    स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			    काष्ठा snd_pcm_plugin_channel *dst_channels,
			    पूर्णांक src_frames, पूर्णांक dst_frames)
अणु
	अचिन्हित पूर्णांक pos = 0;
	चिन्हित पूर्णांक val;
	चिन्हित लघु S1, S2;
	चिन्हित लघु *src, *dst;
	अचिन्हित पूर्णांक channel;
	पूर्णांक src_step, dst_step;
	पूर्णांक src_frames1, dst_frames1;
	काष्ठा rate_priv *data = (काष्ठा rate_priv *)plugin->extra_data;
	काष्ठा rate_channel *rchannels = data->channels;
	
	क्रम (channel = 0; channel < plugin->src_क्रमmat.channels; channel++) अणु
		pos = data->pos;
		S1 = rchannels->last_S1;
		S2 = rchannels->last_S2;
		अगर (!src_channels[channel].enabled) अणु
			अगर (dst_channels[channel].wanted)
				snd_pcm_area_silence(&dst_channels[channel].area, 0, dst_frames, plugin->dst_क्रमmat.क्रमmat);
			dst_channels[channel].enabled = 0;
			जारी;
		पूर्ण
		dst_channels[channel].enabled = 1;
		src = (चिन्हित लघु *)src_channels[channel].area.addr +
			src_channels[channel].area.first / 8 / 2;
		dst = (चिन्हित लघु *)dst_channels[channel].area.addr +
			dst_channels[channel].area.first / 8 / 2;
		src_step = src_channels[channel].area.step / 8 / 2;
		dst_step = dst_channels[channel].area.step / 8 / 2;
		src_frames1 = src_frames;
		dst_frames1 = dst_frames;
		जबतक (dst_frames1-- > 0) अणु
			अगर (pos & ~R_MASK) अणु
				pos &= R_MASK;
				S1 = S2;
				अगर (src_frames1-- > 0) अणु
					S2 = *src;
					src += src_step;
				पूर्ण
			पूर्ण
			val = S1 + ((S2 - S1) * (चिन्हित पूर्णांक)pos) / BITS;
			अगर (val < -32768)
				val = -32768;
			अन्यथा अगर (val > 32767)
				val = 32767;
			*dst = val;
			dst += dst_step;
			pos += data->pitch;
		पूर्ण
		rchannels->last_S1 = S1;
		rchannels->last_S2 = S2;
		rchannels++;
	पूर्ण
	data->pos = pos;
पूर्ण

अटल व्योम resample_shrink(काष्ठा snd_pcm_plugin *plugin,
			    स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			    काष्ठा snd_pcm_plugin_channel *dst_channels,
			    पूर्णांक src_frames, पूर्णांक dst_frames)
अणु
	अचिन्हित पूर्णांक pos = 0;
	चिन्हित पूर्णांक val;
	चिन्हित लघु S1, S2;
	चिन्हित लघु *src, *dst;
	अचिन्हित पूर्णांक channel;
	पूर्णांक src_step, dst_step;
	पूर्णांक src_frames1, dst_frames1;
	काष्ठा rate_priv *data = (काष्ठा rate_priv *)plugin->extra_data;
	काष्ठा rate_channel *rchannels = data->channels;

	क्रम (channel = 0; channel < plugin->src_क्रमmat.channels; ++channel) अणु
		pos = data->pos;
		S1 = rchannels->last_S1;
		S2 = rchannels->last_S2;
		अगर (!src_channels[channel].enabled) अणु
			अगर (dst_channels[channel].wanted)
				snd_pcm_area_silence(&dst_channels[channel].area, 0, dst_frames, plugin->dst_क्रमmat.क्रमmat);
			dst_channels[channel].enabled = 0;
			जारी;
		पूर्ण
		dst_channels[channel].enabled = 1;
		src = (चिन्हित लघु *)src_channels[channel].area.addr +
			src_channels[channel].area.first / 8 / 2;
		dst = (चिन्हित लघु *)dst_channels[channel].area.addr +
			dst_channels[channel].area.first / 8 / 2;
		src_step = src_channels[channel].area.step / 8 / 2;
		dst_step = dst_channels[channel].area.step / 8 / 2;
		src_frames1 = src_frames;
		dst_frames1 = dst_frames;
		जबतक (dst_frames1 > 0) अणु
			S1 = S2;
			अगर (src_frames1-- > 0) अणु
				S2 = *src;
				src += src_step;
			पूर्ण
			अगर (pos & ~R_MASK) अणु
				pos &= R_MASK;
				val = S1 + ((S2 - S1) * (चिन्हित पूर्णांक)pos) / BITS;
				अगर (val < -32768)
					val = -32768;
				अन्यथा अगर (val > 32767)
					val = 32767;
				*dst = val;
				dst += dst_step;
				dst_frames1--;
			पूर्ण
			pos += data->pitch;
		पूर्ण
		rchannels->last_S1 = S1;
		rchannels->last_S2 = S2;
		rchannels++;
	पूर्ण
	data->pos = pos;
पूर्ण

अटल snd_pcm_sframes_t rate_src_frames(काष्ठा snd_pcm_plugin *plugin, snd_pcm_uframes_t frames)
अणु
	काष्ठा rate_priv *data;
	snd_pcm_sframes_t res;

	अगर (snd_BUG_ON(!plugin))
		वापस -ENXIO;
	अगर (frames == 0)
		वापस 0;
	data = (काष्ठा rate_priv *)plugin->extra_data;
	अगर (plugin->src_क्रमmat.rate < plugin->dst_क्रमmat.rate) अणु
		res = (((frames * data->pitch) + (BITS/2)) >> SHIFT);
	पूर्ण अन्यथा अणु
		res = DIV_ROUND_CLOSEST(frames << SHIFT, data->pitch);
	पूर्ण
	अगर (data->old_src_frames > 0) अणु
		snd_pcm_sframes_t frames1 = frames, res1 = data->old_dst_frames;
		जबतक (data->old_src_frames < frames1) अणु
			frames1 >>= 1;
			res1 <<= 1;
		पूर्ण
		जबतक (data->old_src_frames > frames1) अणु
			frames1 <<= 1;
			res1 >>= 1;
		पूर्ण
		अगर (data->old_src_frames == frames1)
			वापस res1;
	पूर्ण
	data->old_src_frames = frames;
	data->old_dst_frames = res;
	वापस res;
पूर्ण

अटल snd_pcm_sframes_t rate_dst_frames(काष्ठा snd_pcm_plugin *plugin, snd_pcm_uframes_t frames)
अणु
	काष्ठा rate_priv *data;
	snd_pcm_sframes_t res;

	अगर (snd_BUG_ON(!plugin))
		वापस -ENXIO;
	अगर (frames == 0)
		वापस 0;
	data = (काष्ठा rate_priv *)plugin->extra_data;
	अगर (plugin->src_क्रमmat.rate < plugin->dst_क्रमmat.rate) अणु
		res = DIV_ROUND_CLOSEST(frames << SHIFT, data->pitch);
	पूर्ण अन्यथा अणु
		res = (((frames * data->pitch) + (BITS/2)) >> SHIFT);
	पूर्ण
	अगर (data->old_dst_frames > 0) अणु
		snd_pcm_sframes_t frames1 = frames, res1 = data->old_src_frames;
		जबतक (data->old_dst_frames < frames1) अणु
			frames1 >>= 1;
			res1 <<= 1;
		पूर्ण
		जबतक (data->old_dst_frames > frames1) अणु
			frames1 <<= 1;
			res1 >>= 1;
		पूर्ण
		अगर (data->old_dst_frames == frames1)
			वापस res1;
	पूर्ण
	data->old_dst_frames = frames;
	data->old_src_frames = res;
	वापस res;
पूर्ण

अटल snd_pcm_sframes_t rate_transfer(काष्ठा snd_pcm_plugin *plugin,
			     स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			     काष्ठा snd_pcm_plugin_channel *dst_channels,
			     snd_pcm_uframes_t frames)
अणु
	snd_pcm_uframes_t dst_frames;
	काष्ठा rate_priv *data;

	अगर (snd_BUG_ON(!plugin || !src_channels || !dst_channels))
		वापस -ENXIO;
	अगर (frames == 0)
		वापस 0;
#अगर_घोषित CONFIG_SND_DEBUG
	अणु
		अचिन्हित पूर्णांक channel;
		क्रम (channel = 0; channel < plugin->src_क्रमmat.channels; channel++) अणु
			अगर (snd_BUG_ON(src_channels[channel].area.first % 8 ||
				       src_channels[channel].area.step % 8))
				वापस -ENXIO;
			अगर (snd_BUG_ON(dst_channels[channel].area.first % 8 ||
				       dst_channels[channel].area.step % 8))
				वापस -ENXIO;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	dst_frames = rate_dst_frames(plugin, frames);
	अगर (dst_frames > dst_channels[0].frames)
		dst_frames = dst_channels[0].frames;
	data = (काष्ठा rate_priv *)plugin->extra_data;
	data->func(plugin, src_channels, dst_channels, frames, dst_frames);
	वापस dst_frames;
पूर्ण

अटल पूर्णांक rate_action(काष्ठा snd_pcm_plugin *plugin,
		       क्रमागत snd_pcm_plugin_action action,
		       अचिन्हित दीर्घ udata)
अणु
	अगर (snd_BUG_ON(!plugin))
		वापस -ENXIO;
	चयन (action) अणु
	हाल INIT:
	हाल PREPARE:
		rate_init(plugin);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;	/* silenty ignore other actions */
पूर्ण

पूर्णांक snd_pcm_plugin_build_rate(काष्ठा snd_pcm_substream *plug,
			      काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			      काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
			      काष्ठा snd_pcm_plugin **r_plugin)
अणु
	पूर्णांक err;
	काष्ठा rate_priv *data;
	काष्ठा snd_pcm_plugin *plugin;

	अगर (snd_BUG_ON(!r_plugin))
		वापस -ENXIO;
	*r_plugin = शून्य;

	अगर (snd_BUG_ON(src_क्रमmat->channels != dst_क्रमmat->channels))
		वापस -ENXIO;
	अगर (snd_BUG_ON(src_क्रमmat->channels <= 0))
		वापस -ENXIO;
	अगर (snd_BUG_ON(src_क्रमmat->क्रमmat != SNDRV_PCM_FORMAT_S16))
		वापस -ENXIO;
	अगर (snd_BUG_ON(dst_क्रमmat->क्रमmat != SNDRV_PCM_FORMAT_S16))
		वापस -ENXIO;
	अगर (snd_BUG_ON(src_क्रमmat->rate == dst_क्रमmat->rate))
		वापस -ENXIO;

	err = snd_pcm_plugin_build(plug, "rate conversion",
				   src_क्रमmat, dst_क्रमmat,
				   काष्ठा_size(data, channels,
					       src_क्रमmat->channels),
				   &plugin);
	अगर (err < 0)
		वापस err;
	data = (काष्ठा rate_priv *)plugin->extra_data;
	अगर (src_क्रमmat->rate < dst_क्रमmat->rate) अणु
		data->pitch = ((src_क्रमmat->rate << SHIFT) + (dst_क्रमmat->rate >> 1)) / dst_क्रमmat->rate;
		data->func = resample_expand;
	पूर्ण अन्यथा अणु
		data->pitch = ((dst_क्रमmat->rate << SHIFT) + (src_क्रमmat->rate >> 1)) / src_क्रमmat->rate;
		data->func = resample_shrink;
	पूर्ण
	data->pos = 0;
	rate_init(plugin);
	data->old_src_frames = data->old_dst_frames = 0;
	plugin->transfer = rate_transfer;
	plugin->src_frames = rate_src_frames;
	plugin->dst_frames = rate_dst_frames;
	plugin->action = rate_action;
	*r_plugin = plugin;
	वापस 0;
पूर्ण
