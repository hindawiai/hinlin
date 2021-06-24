<शैली गुरु>
/*
 *  PCM Plug-In shared (kernel/library) code
 *  Copyright (c) 1999 by Jaroslav Kysela <perex@perex.cz>
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
  
#अगर 0
#घोषणा PLUGIN_DEBUG
#पूर्ण_अगर

#समावेश <linux/slab.h>
#समावेश <linux/समय.स>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश "pcm_plugin.h"

#घोषणा snd_pcm_plug_first(plug) ((plug)->runसमय->oss.plugin_first)
#घोषणा snd_pcm_plug_last(plug) ((plug)->runसमय->oss.plugin_last)

/*
 *  because some cards might have rates "very close", we ignore
 *  all "resampling" requests within +-5%
 */
अटल पूर्णांक rate_match(अचिन्हित पूर्णांक src_rate, अचिन्हित पूर्णांक dst_rate)
अणु
	अचिन्हित पूर्णांक low = (src_rate * 95) / 100;
	अचिन्हित पूर्णांक high = (src_rate * 105) / 100;
	वापस dst_rate >= low && dst_rate <= high;
पूर्ण

अटल पूर्णांक snd_pcm_plugin_alloc(काष्ठा snd_pcm_plugin *plugin, snd_pcm_uframes_t frames)
अणु
	काष्ठा snd_pcm_plugin_क्रमmat *क्रमmat;
	sमाप_प्रकार width;
	माप_प्रकार size;
	अचिन्हित पूर्णांक channel;
	काष्ठा snd_pcm_plugin_channel *c;

	अगर (plugin->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		क्रमmat = &plugin->src_क्रमmat;
	पूर्ण अन्यथा अणु
		क्रमmat = &plugin->dst_क्रमmat;
	पूर्ण
	अगर ((width = snd_pcm_क्रमmat_physical_width(क्रमmat->क्रमmat)) < 0)
		वापस width;
	size = frames * क्रमmat->channels * width;
	अगर (snd_BUG_ON(size % 8))
		वापस -ENXIO;
	size /= 8;
	अगर (plugin->buf_frames < frames) अणु
		kvमुक्त(plugin->buf);
		plugin->buf = kvzalloc(size, GFP_KERNEL);
		plugin->buf_frames = frames;
	पूर्ण
	अगर (!plugin->buf) अणु
		plugin->buf_frames = 0;
		वापस -ENOMEM;
	पूर्ण
	c = plugin->buf_channels;
	अगर (plugin->access == SNDRV_PCM_ACCESS_RW_INTERLEAVED) अणु
		क्रम (channel = 0; channel < क्रमmat->channels; channel++, c++) अणु
			c->frames = frames;
			c->enabled = 1;
			c->wanted = 0;
			c->area.addr = plugin->buf;
			c->area.first = channel * width;
			c->area.step = क्रमmat->channels * width;
		पूर्ण
	पूर्ण अन्यथा अगर (plugin->access == SNDRV_PCM_ACCESS_RW_NONINTERLEAVED) अणु
		अगर (snd_BUG_ON(size % क्रमmat->channels))
			वापस -EINVAL;
		size /= क्रमmat->channels;
		क्रम (channel = 0; channel < क्रमmat->channels; channel++, c++) अणु
			c->frames = frames;
			c->enabled = 1;
			c->wanted = 0;
			c->area.addr = plugin->buf + (channel * size);
			c->area.first = 0;
			c->area.step = width;
		पूर्ण
	पूर्ण अन्यथा
		वापस -EINVAL;
	वापस 0;
पूर्ण

पूर्णांक snd_pcm_plug_alloc(काष्ठा snd_pcm_substream *plug, snd_pcm_uframes_t frames)
अणु
	पूर्णांक err;
	अगर (snd_BUG_ON(!snd_pcm_plug_first(plug)))
		वापस -ENXIO;
	अगर (snd_pcm_plug_stream(plug) == SNDRV_PCM_STREAM_PLAYBACK) अणु
		काष्ठा snd_pcm_plugin *plugin = snd_pcm_plug_first(plug);
		जबतक (plugin->next) अणु
			अगर (plugin->dst_frames)
				frames = plugin->dst_frames(plugin, frames);
			अगर ((snd_pcm_sframes_t)frames <= 0)
				वापस -ENXIO;
			plugin = plugin->next;
			err = snd_pcm_plugin_alloc(plugin, frames);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण अन्यथा अणु
		काष्ठा snd_pcm_plugin *plugin = snd_pcm_plug_last(plug);
		जबतक (plugin->prev) अणु
			अगर (plugin->src_frames)
				frames = plugin->src_frames(plugin, frames);
			अगर ((snd_pcm_sframes_t)frames <= 0)
				वापस -ENXIO;
			plugin = plugin->prev;
			err = snd_pcm_plugin_alloc(plugin, frames);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण


snd_pcm_sframes_t snd_pcm_plugin_client_channels(काष्ठा snd_pcm_plugin *plugin,
				       snd_pcm_uframes_t frames,
				       काष्ठा snd_pcm_plugin_channel **channels)
अणु
	*channels = plugin->buf_channels;
	वापस frames;
पूर्ण

पूर्णांक snd_pcm_plugin_build(काष्ठा snd_pcm_substream *plug,
			 स्थिर अक्षर *name,
			 काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			 काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
			 माप_प्रकार extra,
			 काष्ठा snd_pcm_plugin **ret)
अणु
	काष्ठा snd_pcm_plugin *plugin;
	अचिन्हित पूर्णांक channels;
	
	अगर (snd_BUG_ON(!plug))
		वापस -ENXIO;
	अगर (snd_BUG_ON(!src_क्रमmat || !dst_क्रमmat))
		वापस -ENXIO;
	plugin = kzalloc(माप(*plugin) + extra, GFP_KERNEL);
	अगर (plugin == शून्य)
		वापस -ENOMEM;
	plugin->name = name;
	plugin->plug = plug;
	plugin->stream = snd_pcm_plug_stream(plug);
	plugin->access = SNDRV_PCM_ACCESS_RW_INTERLEAVED;
	plugin->src_क्रमmat = *src_क्रमmat;
	plugin->src_width = snd_pcm_क्रमmat_physical_width(src_क्रमmat->क्रमmat);
	snd_BUG_ON(plugin->src_width <= 0);
	plugin->dst_क्रमmat = *dst_क्रमmat;
	plugin->dst_width = snd_pcm_क्रमmat_physical_width(dst_क्रमmat->क्रमmat);
	snd_BUG_ON(plugin->dst_width <= 0);
	अगर (plugin->stream == SNDRV_PCM_STREAM_PLAYBACK)
		channels = src_क्रमmat->channels;
	अन्यथा
		channels = dst_क्रमmat->channels;
	plugin->buf_channels = kसुस्मृति(channels, माप(*plugin->buf_channels), GFP_KERNEL);
	अगर (plugin->buf_channels == शून्य) अणु
		snd_pcm_plugin_मुक्त(plugin);
		वापस -ENOMEM;
	पूर्ण
	plugin->client_channels = snd_pcm_plugin_client_channels;
	*ret = plugin;
	वापस 0;
पूर्ण

पूर्णांक snd_pcm_plugin_मुक्त(काष्ठा snd_pcm_plugin *plugin)
अणु
	अगर (! plugin)
		वापस 0;
	अगर (plugin->निजी_मुक्त)
		plugin->निजी_मुक्त(plugin);
	kमुक्त(plugin->buf_channels);
	kvमुक्त(plugin->buf);
	kमुक्त(plugin);
	वापस 0;
पूर्ण

अटल snd_pcm_sframes_t calc_dst_frames(काष्ठा snd_pcm_substream *plug,
					 snd_pcm_sframes_t frames,
					 bool check_size)
अणु
	काष्ठा snd_pcm_plugin *plugin, *plugin_next;

	plugin = snd_pcm_plug_first(plug);
	जबतक (plugin && frames > 0) अणु
		plugin_next = plugin->next;
		अगर (check_size && plugin->buf_frames &&
		    frames > plugin->buf_frames)
			frames = plugin->buf_frames;
		अगर (plugin->dst_frames) अणु
			frames = plugin->dst_frames(plugin, frames);
			अगर (frames < 0)
				वापस frames;
		पूर्ण
		plugin = plugin_next;
	पूर्ण
	वापस frames;
पूर्ण

अटल snd_pcm_sframes_t calc_src_frames(काष्ठा snd_pcm_substream *plug,
					 snd_pcm_sframes_t frames,
					 bool check_size)
अणु
	काष्ठा snd_pcm_plugin *plugin, *plugin_prev;

	plugin = snd_pcm_plug_last(plug);
	जबतक (plugin && frames > 0) अणु
		plugin_prev = plugin->prev;
		अगर (plugin->src_frames) अणु
			frames = plugin->src_frames(plugin, frames);
			अगर (frames < 0)
				वापस frames;
		पूर्ण
		अगर (check_size && plugin->buf_frames &&
		    frames > plugin->buf_frames)
			frames = plugin->buf_frames;
		plugin = plugin_prev;
	पूर्ण
	वापस frames;
पूर्ण

snd_pcm_sframes_t snd_pcm_plug_client_size(काष्ठा snd_pcm_substream *plug, snd_pcm_uframes_t drv_frames)
अणु
	अगर (snd_BUG_ON(!plug))
		वापस -ENXIO;
	चयन (snd_pcm_plug_stream(plug)) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		वापस calc_src_frames(plug, drv_frames, false);
	हाल SNDRV_PCM_STREAM_CAPTURE:
		वापस calc_dst_frames(plug, drv_frames, false);
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
पूर्ण

snd_pcm_sframes_t snd_pcm_plug_slave_size(काष्ठा snd_pcm_substream *plug, snd_pcm_uframes_t clt_frames)
अणु
	अगर (snd_BUG_ON(!plug))
		वापस -ENXIO;
	चयन (snd_pcm_plug_stream(plug)) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		वापस calc_dst_frames(plug, clt_frames, false);
	हाल SNDRV_PCM_STREAM_CAPTURE:
		वापस calc_src_frames(plug, clt_frames, false);
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक snd_pcm_plug_क्रमmats(स्थिर काष्ठा snd_mask *mask,
				snd_pcm_क्रमmat_t क्रमmat)
अणु
	काष्ठा snd_mask क्रमmats = *mask;
	u64 linfmts = (SNDRV_PCM_FMTBIT_U8 | SNDRV_PCM_FMTBIT_S8 |
		       SNDRV_PCM_FMTBIT_U16_LE | SNDRV_PCM_FMTBIT_S16_LE |
		       SNDRV_PCM_FMTBIT_U16_BE | SNDRV_PCM_FMTBIT_S16_BE |
		       SNDRV_PCM_FMTBIT_U24_LE | SNDRV_PCM_FMTBIT_S24_LE |
		       SNDRV_PCM_FMTBIT_U24_BE | SNDRV_PCM_FMTBIT_S24_BE |
		       SNDRV_PCM_FMTBIT_U24_3LE | SNDRV_PCM_FMTBIT_S24_3LE |
		       SNDRV_PCM_FMTBIT_U24_3BE | SNDRV_PCM_FMTBIT_S24_3BE |
		       SNDRV_PCM_FMTBIT_U32_LE | SNDRV_PCM_FMTBIT_S32_LE |
		       SNDRV_PCM_FMTBIT_U32_BE | SNDRV_PCM_FMTBIT_S32_BE);
	snd_mask_set(&क्रमmats, (__क्रमce पूर्णांक)SNDRV_PCM_FORMAT_MU_LAW);
	
	अगर (क्रमmats.bits[0] & lower_32_bits(linfmts))
		क्रमmats.bits[0] |= lower_32_bits(linfmts);
	अगर (क्रमmats.bits[1] & upper_32_bits(linfmts))
		क्रमmats.bits[1] |= upper_32_bits(linfmts);
	वापस snd_mask_test(&क्रमmats, (__क्रमce पूर्णांक)क्रमmat);
पूर्ण

अटल स्थिर snd_pcm_क्रमmat_t preferred_क्रमmats[] = अणु
	SNDRV_PCM_FORMAT_S16_LE,
	SNDRV_PCM_FORMAT_S16_BE,
	SNDRV_PCM_FORMAT_U16_LE,
	SNDRV_PCM_FORMAT_U16_BE,
	SNDRV_PCM_FORMAT_S24_3LE,
	SNDRV_PCM_FORMAT_S24_3BE,
	SNDRV_PCM_FORMAT_U24_3LE,
	SNDRV_PCM_FORMAT_U24_3BE,
	SNDRV_PCM_FORMAT_S24_LE,
	SNDRV_PCM_FORMAT_S24_BE,
	SNDRV_PCM_FORMAT_U24_LE,
	SNDRV_PCM_FORMAT_U24_BE,
	SNDRV_PCM_FORMAT_S32_LE,
	SNDRV_PCM_FORMAT_S32_BE,
	SNDRV_PCM_FORMAT_U32_LE,
	SNDRV_PCM_FORMAT_U32_BE,
	SNDRV_PCM_FORMAT_S8,
	SNDRV_PCM_FORMAT_U8
पूर्ण;

snd_pcm_क्रमmat_t snd_pcm_plug_slave_क्रमmat(snd_pcm_क्रमmat_t क्रमmat,
					   स्थिर काष्ठा snd_mask *क्रमmat_mask)
अणु
	पूर्णांक i;

	अगर (snd_mask_test(क्रमmat_mask, (__क्रमce पूर्णांक)क्रमmat))
		वापस क्रमmat;
	अगर (!snd_pcm_plug_क्रमmats(क्रमmat_mask, क्रमmat))
		वापस (__क्रमce snd_pcm_क्रमmat_t)-EINVAL;
	अगर (snd_pcm_क्रमmat_linear(क्रमmat)) अणु
		अचिन्हित पूर्णांक width = snd_pcm_क्रमmat_width(क्रमmat);
		पूर्णांक unsignd = snd_pcm_क्रमmat_अचिन्हित(क्रमmat) > 0;
		पूर्णांक big = snd_pcm_क्रमmat_big_endian(क्रमmat) > 0;
		अचिन्हित पूर्णांक badness, best = -1;
		snd_pcm_क्रमmat_t best_क्रमmat = (__क्रमce snd_pcm_क्रमmat_t)-1;
		क्रम (i = 0; i < ARRAY_SIZE(preferred_क्रमmats); i++) अणु
			snd_pcm_क्रमmat_t f = preferred_क्रमmats[i];
			अचिन्हित पूर्णांक w;
			अगर (!snd_mask_test(क्रमmat_mask, (__क्रमce पूर्णांक)f))
				जारी;
			w = snd_pcm_क्रमmat_width(f);
			अगर (w >= width)
				badness = w - width;
			अन्यथा
				badness = width - w + 32;
			badness += snd_pcm_क्रमmat_अचिन्हित(f) != unsignd;
			badness += snd_pcm_क्रमmat_big_endian(f) != big;
			अगर (badness < best) अणु
				best_क्रमmat = f;
				best = badness;
			पूर्ण
		पूर्ण
		अगर ((__क्रमce पूर्णांक)best_क्रमmat >= 0)
			वापस best_क्रमmat;
		अन्यथा
			वापस (__क्रमce snd_pcm_क्रमmat_t)-EINVAL;
	पूर्ण अन्यथा अणु
		चयन (क्रमmat) अणु
		हाल SNDRV_PCM_FORMAT_MU_LAW:
			क्रम (i = 0; i < ARRAY_SIZE(preferred_क्रमmats); ++i) अणु
				snd_pcm_क्रमmat_t क्रमmat1 = preferred_क्रमmats[i];
				अगर (snd_mask_test(क्रमmat_mask, (__क्रमce पूर्णांक)क्रमmat1))
					वापस क्रमmat1;
			पूर्ण
			fallthrough;
		शेष:
			वापस (__क्रमce snd_pcm_क्रमmat_t)-EINVAL;
		पूर्ण
	पूर्ण
पूर्ण

पूर्णांक snd_pcm_plug_क्रमmat_plugins(काष्ठा snd_pcm_substream *plug,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_pcm_hw_params *slave_params)
अणु
	काष्ठा snd_pcm_plugin_क्रमmat पंचांगpक्रमmat;
	काष्ठा snd_pcm_plugin_क्रमmat dstक्रमmat;
	काष्ठा snd_pcm_plugin_क्रमmat srcक्रमmat;
	snd_pcm_access_t src_access, dst_access;
	काष्ठा snd_pcm_plugin *plugin = शून्य;
	पूर्णांक err;
	पूर्णांक stream = snd_pcm_plug_stream(plug);
	पूर्णांक slave_पूर्णांकerleaved = (params_channels(slave_params) == 1 ||
				 params_access(slave_params) == SNDRV_PCM_ACCESS_RW_INTERLEAVED);

	चयन (stream) अणु
	हाल SNDRV_PCM_STREAM_PLAYBACK:
		dstक्रमmat.क्रमmat = params_क्रमmat(slave_params);
		dstक्रमmat.rate = params_rate(slave_params);
		dstक्रमmat.channels = params_channels(slave_params);
		srcक्रमmat.क्रमmat = params_क्रमmat(params);
		srcक्रमmat.rate = params_rate(params);
		srcक्रमmat.channels = params_channels(params);
		src_access = SNDRV_PCM_ACCESS_RW_INTERLEAVED;
		dst_access = (slave_पूर्णांकerleaved ? SNDRV_PCM_ACCESS_RW_INTERLEAVED :
						  SNDRV_PCM_ACCESS_RW_NONINTERLEAVED);
		अवरोध;
	हाल SNDRV_PCM_STREAM_CAPTURE:
		dstक्रमmat.क्रमmat = params_क्रमmat(params);
		dstक्रमmat.rate = params_rate(params);
		dstक्रमmat.channels = params_channels(params);
		srcक्रमmat.क्रमmat = params_क्रमmat(slave_params);
		srcक्रमmat.rate = params_rate(slave_params);
		srcक्रमmat.channels = params_channels(slave_params);
		src_access = (slave_पूर्णांकerleaved ? SNDRV_PCM_ACCESS_RW_INTERLEAVED :
						  SNDRV_PCM_ACCESS_RW_NONINTERLEAVED);
		dst_access = SNDRV_PCM_ACCESS_RW_INTERLEAVED;
		अवरोध;
	शेष:
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	पंचांगpक्रमmat = srcक्रमmat;
		
	pdम_लिखो("srcformat: format=%i, rate=%i, channels=%i\n", 
		 srcक्रमmat.क्रमmat,
		 srcक्रमmat.rate,
		 srcक्रमmat.channels);
	pdम_लिखो("dstformat: format=%i, rate=%i, channels=%i\n", 
		 dstक्रमmat.क्रमmat,
		 dstक्रमmat.rate,
		 dstक्रमmat.channels);

	/* Format change (linearization) */
	अगर (! rate_match(srcक्रमmat.rate, dstक्रमmat.rate) &&
	    ! snd_pcm_क्रमmat_linear(srcक्रमmat.क्रमmat)) अणु
		अगर (srcक्रमmat.क्रमmat != SNDRV_PCM_FORMAT_MU_LAW)
			वापस -EINVAL;
		पंचांगpक्रमmat.क्रमmat = SNDRV_PCM_FORMAT_S16;
		err = snd_pcm_plugin_build_mulaw(plug,
						 &srcक्रमmat, &पंचांगpक्रमmat,
						 &plugin);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_plugin_append(plugin);
		अगर (err < 0) अणु
			snd_pcm_plugin_मुक्त(plugin);
			वापस err;
		पूर्ण
		srcक्रमmat = पंचांगpक्रमmat;
		src_access = dst_access;
	पूर्ण

	/* channels reduction */
	अगर (srcक्रमmat.channels > dstक्रमmat.channels) अणु
		पंचांगpक्रमmat.channels = dstक्रमmat.channels;
		err = snd_pcm_plugin_build_route(plug, &srcक्रमmat, &पंचांगpक्रमmat, &plugin);
		pdम_लिखो("channels reduction: src=%i, dst=%i returns %i\n", srcक्रमmat.channels, पंचांगpक्रमmat.channels, err);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_plugin_append(plugin);
		अगर (err < 0) अणु
			snd_pcm_plugin_मुक्त(plugin);
			वापस err;
		पूर्ण
		srcक्रमmat = पंचांगpक्रमmat;
		src_access = dst_access;
	पूर्ण

	/* rate resampling */
	अगर (!rate_match(srcक्रमmat.rate, dstक्रमmat.rate)) अणु
		अगर (srcक्रमmat.क्रमmat != SNDRV_PCM_FORMAT_S16) अणु
			/* convert to S16 क्रम resampling */
			पंचांगpक्रमmat.क्रमmat = SNDRV_PCM_FORMAT_S16;
			err = snd_pcm_plugin_build_linear(plug,
							  &srcक्रमmat, &पंचांगpक्रमmat,
							  &plugin);
			अगर (err < 0)
				वापस err;
			err = snd_pcm_plugin_append(plugin);
			अगर (err < 0) अणु
				snd_pcm_plugin_मुक्त(plugin);
				वापस err;
			पूर्ण
			srcक्रमmat = पंचांगpक्रमmat;
			src_access = dst_access;
		पूर्ण
		पंचांगpक्रमmat.rate = dstक्रमmat.rate;
        	err = snd_pcm_plugin_build_rate(plug,
        					&srcक्रमmat, &पंचांगpक्रमmat,
						&plugin);
		pdम_लिखो("rate down resampling: src=%i, dst=%i returns %i\n", srcक्रमmat.rate, पंचांगpक्रमmat.rate, err);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_plugin_append(plugin);
		अगर (err < 0) अणु
			snd_pcm_plugin_मुक्त(plugin);
			वापस err;
		पूर्ण
		srcक्रमmat = पंचांगpक्रमmat;
		src_access = dst_access;
        पूर्ण

	/* क्रमmat change */
	अगर (srcक्रमmat.क्रमmat != dstक्रमmat.क्रमmat) अणु
		पंचांगpक्रमmat.क्रमmat = dstक्रमmat.क्रमmat;
		अगर (srcक्रमmat.क्रमmat == SNDRV_PCM_FORMAT_MU_LAW ||
		    पंचांगpक्रमmat.क्रमmat == SNDRV_PCM_FORMAT_MU_LAW) अणु
			err = snd_pcm_plugin_build_mulaw(plug,
							 &srcक्रमmat, &पंचांगpक्रमmat,
							 &plugin);
		पूर्ण
		अन्यथा अगर (snd_pcm_क्रमmat_linear(srcक्रमmat.क्रमmat) &&
			 snd_pcm_क्रमmat_linear(पंचांगpक्रमmat.क्रमmat)) अणु
			err = snd_pcm_plugin_build_linear(plug,
							  &srcक्रमmat, &पंचांगpक्रमmat,
							  &plugin);
		पूर्ण
		अन्यथा
			वापस -EINVAL;
		pdम_लिखो("format change: src=%i, dst=%i returns %i\n", srcक्रमmat.क्रमmat, पंचांगpक्रमmat.क्रमmat, err);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_plugin_append(plugin);
		अगर (err < 0) अणु
			snd_pcm_plugin_मुक्त(plugin);
			वापस err;
		पूर्ण
		srcक्रमmat = पंचांगpक्रमmat;
		src_access = dst_access;
	पूर्ण

	/* channels extension */
	अगर (srcक्रमmat.channels < dstक्रमmat.channels) अणु
		पंचांगpक्रमmat.channels = dstक्रमmat.channels;
		err = snd_pcm_plugin_build_route(plug, &srcक्रमmat, &पंचांगpक्रमmat, &plugin);
		pdम_लिखो("channels extension: src=%i, dst=%i returns %i\n", srcक्रमmat.channels, पंचांगpक्रमmat.channels, err);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_plugin_append(plugin);
		अगर (err < 0) अणु
			snd_pcm_plugin_मुक्त(plugin);
			वापस err;
		पूर्ण
		srcक्रमmat = पंचांगpक्रमmat;
		src_access = dst_access;
	पूर्ण

	/* de-पूर्णांकerleave */
	अगर (src_access != dst_access) अणु
		err = snd_pcm_plugin_build_copy(plug,
						&srcक्रमmat,
						&पंचांगpक्रमmat,
						&plugin);
		pdम_लिखो("interleave change (copy: returns %i)\n", err);
		अगर (err < 0)
			वापस err;
		err = snd_pcm_plugin_append(plugin);
		अगर (err < 0) अणु
			snd_pcm_plugin_मुक्त(plugin);
			वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

snd_pcm_sframes_t snd_pcm_plug_client_channels_buf(काष्ठा snd_pcm_substream *plug,
					 अक्षर *buf,
					 snd_pcm_uframes_t count,
					 काष्ठा snd_pcm_plugin_channel **channels)
अणु
	काष्ठा snd_pcm_plugin *plugin;
	काष्ठा snd_pcm_plugin_channel *v;
	काष्ठा snd_pcm_plugin_क्रमmat *क्रमmat;
	पूर्णांक width, nchannels, channel;
	पूर्णांक stream = snd_pcm_plug_stream(plug);

	अगर (snd_BUG_ON(!buf))
		वापस -ENXIO;
	अगर (stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		plugin = snd_pcm_plug_first(plug);
		क्रमmat = &plugin->src_क्रमmat;
	पूर्ण अन्यथा अणु
		plugin = snd_pcm_plug_last(plug);
		क्रमmat = &plugin->dst_क्रमmat;
	पूर्ण
	v = plugin->buf_channels;
	*channels = v;
	अगर ((width = snd_pcm_क्रमmat_physical_width(क्रमmat->क्रमmat)) < 0)
		वापस width;
	nchannels = क्रमmat->channels;
	अगर (snd_BUG_ON(plugin->access != SNDRV_PCM_ACCESS_RW_INTERLEAVED &&
		       क्रमmat->channels > 1))
		वापस -ENXIO;
	क्रम (channel = 0; channel < nchannels; channel++, v++) अणु
		v->frames = count;
		v->enabled = 1;
		v->wanted = (stream == SNDRV_PCM_STREAM_CAPTURE);
		v->area.addr = buf;
		v->area.first = channel * width;
		v->area.step = nchannels * width;
	पूर्ण
	वापस count;
पूर्ण

snd_pcm_sframes_t snd_pcm_plug_ग_लिखो_transfer(काष्ठा snd_pcm_substream *plug, काष्ठा snd_pcm_plugin_channel *src_channels, snd_pcm_uframes_t size)
अणु
	काष्ठा snd_pcm_plugin *plugin, *next;
	काष्ठा snd_pcm_plugin_channel *dst_channels;
	पूर्णांक err;
	snd_pcm_sframes_t frames = size;

	plugin = snd_pcm_plug_first(plug);
	जबतक (plugin) अणु
		अगर (frames <= 0)
			वापस frames;
		अगर ((next = plugin->next) != शून्य) अणु
			snd_pcm_sframes_t frames1 = frames;
			अगर (plugin->dst_frames) अणु
				frames1 = plugin->dst_frames(plugin, frames);
				अगर (frames1 <= 0)
					वापस frames1;
			पूर्ण
			अगर ((err = next->client_channels(next, frames1, &dst_channels)) < 0) अणु
				वापस err;
			पूर्ण
			अगर (err != frames1) अणु
				frames = err;
				अगर (plugin->src_frames) अणु
					frames = plugin->src_frames(plugin, frames1);
					अगर (frames <= 0)
						वापस frames;
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा
			dst_channels = शून्य;
		pdम_लिखो("write plugin: %s, %li\n", plugin->name, frames);
		अगर ((frames = plugin->transfer(plugin, src_channels, dst_channels, frames)) < 0)
			वापस frames;
		src_channels = dst_channels;
		plugin = next;
	पूर्ण
	वापस calc_src_frames(plug, frames, true);
पूर्ण

snd_pcm_sframes_t snd_pcm_plug_पढ़ो_transfer(काष्ठा snd_pcm_substream *plug, काष्ठा snd_pcm_plugin_channel *dst_channels_final, snd_pcm_uframes_t size)
अणु
	काष्ठा snd_pcm_plugin *plugin, *next;
	काष्ठा snd_pcm_plugin_channel *src_channels, *dst_channels;
	snd_pcm_sframes_t frames = size;
	पूर्णांक err;

	frames = calc_src_frames(plug, frames, true);
	अगर (frames < 0)
		वापस frames;

	src_channels = शून्य;
	plugin = snd_pcm_plug_first(plug);
	जबतक (plugin && frames > 0) अणु
		अगर ((next = plugin->next) != शून्य) अणु
			अगर ((err = plugin->client_channels(plugin, frames, &dst_channels)) < 0) अणु
				वापस err;
			पूर्ण
			frames = err;
		पूर्ण अन्यथा अणु
			dst_channels = dst_channels_final;
		पूर्ण
		pdम_लिखो("read plugin: %s, %li\n", plugin->name, frames);
		अगर ((frames = plugin->transfer(plugin, src_channels, dst_channels, frames)) < 0)
			वापस frames;
		plugin = next;
		src_channels = dst_channels;
	पूर्ण
	वापस frames;
पूर्ण

पूर्णांक snd_pcm_area_silence(स्थिर काष्ठा snd_pcm_channel_area *dst_area, माप_प्रकार dst_offset,
			 माप_प्रकार samples, snd_pcm_क्रमmat_t क्रमmat)
अणु
	/* FIXME: sub byte resolution and odd dst_offset */
	अचिन्हित अक्षर *dst;
	अचिन्हित पूर्णांक dst_step;
	पूर्णांक width;
	स्थिर अचिन्हित अक्षर *silence;
	अगर (!dst_area->addr)
		वापस 0;
	dst = dst_area->addr + (dst_area->first + dst_area->step * dst_offset) / 8;
	width = snd_pcm_क्रमmat_physical_width(क्रमmat);
	अगर (width <= 0)
		वापस -EINVAL;
	अगर (dst_area->step == (अचिन्हित पूर्णांक) width && width >= 8)
		वापस snd_pcm_क्रमmat_set_silence(क्रमmat, dst, samples);
	silence = snd_pcm_क्रमmat_silence_64(क्रमmat);
	अगर (! silence)
		वापस -EINVAL;
	dst_step = dst_area->step / 8;
	अगर (width == 4) अणु
		/* Ima ADPCM */
		पूर्णांक dstbit = dst_area->first % 8;
		पूर्णांक dstbit_step = dst_area->step % 8;
		जबतक (samples-- > 0) अणु
			अगर (dstbit)
				*dst &= 0xf0;
			अन्यथा
				*dst &= 0x0f;
			dst += dst_step;
			dstbit += dstbit_step;
			अगर (dstbit == 8) अणु
				dst++;
				dstbit = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		width /= 8;
		जबतक (samples-- > 0) अणु
			स_नकल(dst, silence, width);
			dst += dst_step;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक snd_pcm_area_copy(स्थिर काष्ठा snd_pcm_channel_area *src_area, माप_प्रकार src_offset,
		      स्थिर काष्ठा snd_pcm_channel_area *dst_area, माप_प्रकार dst_offset,
		      माप_प्रकार samples, snd_pcm_क्रमmat_t क्रमmat)
अणु
	/* FIXME: sub byte resolution and odd dst_offset */
	अक्षर *src, *dst;
	पूर्णांक width;
	पूर्णांक src_step, dst_step;
	src = src_area->addr + (src_area->first + src_area->step * src_offset) / 8;
	अगर (!src_area->addr)
		वापस snd_pcm_area_silence(dst_area, dst_offset, samples, क्रमmat);
	dst = dst_area->addr + (dst_area->first + dst_area->step * dst_offset) / 8;
	अगर (!dst_area->addr)
		वापस 0;
	width = snd_pcm_क्रमmat_physical_width(क्रमmat);
	अगर (width <= 0)
		वापस -EINVAL;
	अगर (src_area->step == (अचिन्हित पूर्णांक) width &&
	    dst_area->step == (अचिन्हित पूर्णांक) width && width >= 8) अणु
		माप_प्रकार bytes = samples * width / 8;
		स_नकल(dst, src, bytes);
		वापस 0;
	पूर्ण
	src_step = src_area->step / 8;
	dst_step = dst_area->step / 8;
	अगर (width == 4) अणु
		/* Ima ADPCM */
		पूर्णांक srcbit = src_area->first % 8;
		पूर्णांक srcbit_step = src_area->step % 8;
		पूर्णांक dstbit = dst_area->first % 8;
		पूर्णांक dstbit_step = dst_area->step % 8;
		जबतक (samples-- > 0) अणु
			अचिन्हित अक्षर srcval;
			अगर (srcbit)
				srcval = *src & 0x0f;
			अन्यथा
				srcval = (*src & 0xf0) >> 4;
			अगर (dstbit)
				*dst = (*dst & 0xf0) | srcval;
			अन्यथा
				*dst = (*dst & 0x0f) | (srcval << 4);
			src += src_step;
			srcbit += srcbit_step;
			अगर (srcbit == 8) अणु
				src++;
				srcbit = 0;
			पूर्ण
			dst += dst_step;
			dstbit += dstbit_step;
			अगर (dstbit == 8) अणु
				dst++;
				dstbit = 0;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		width /= 8;
		जबतक (samples-- > 0) अणु
			स_नकल(dst, src, width);
			src += src_step;
			dst += dst_step;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण
