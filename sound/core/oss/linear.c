<शैली गुरु>
/*
 *  Linear conversion Plug-In
 *  Copyright (c) 1999 by Jaroslav Kysela <perex@perex.cz>,
 *			  Abramo Bagnara <abramo@alsa-project.org>
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

/*
 *  Basic linear conversion plugin
 */
 
काष्ठा linear_priv अणु
	पूर्णांक cvt_endian;		/* need endian conversion? */
	अचिन्हित पूर्णांक src_ofs;	/* byte offset in source क्रमmat */
	अचिन्हित पूर्णांक dst_ofs;	/* byte soffset in destination क्रमmat */
	अचिन्हित पूर्णांक copy_ofs;	/* byte offset in temporary u32 data */
	अचिन्हित पूर्णांक dst_bytes;		/* byte size of destination क्रमmat */
	अचिन्हित पूर्णांक copy_bytes;	/* bytes to copy per conversion */
	अचिन्हित पूर्णांक flip; /* MSB flip क्रम signeness, करोne after endian conv */
पूर्ण;

अटल अंतरभूत व्योम करो_convert(काष्ठा linear_priv *data,
			      अचिन्हित अक्षर *dst, अचिन्हित अक्षर *src)
अणु
	अचिन्हित पूर्णांक पंचांगp = 0;
	अचिन्हित अक्षर *p = (अचिन्हित अक्षर *)&पंचांगp;

	स_नकल(p + data->copy_ofs, src + data->src_ofs, data->copy_bytes);
	अगर (data->cvt_endian)
		पंचांगp = swab32(पंचांगp);
	पंचांगp ^= data->flip;
	स_नकल(dst, p + data->dst_ofs, data->dst_bytes);
पूर्ण

अटल व्योम convert(काष्ठा snd_pcm_plugin *plugin,
		    स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
		    काष्ठा snd_pcm_plugin_channel *dst_channels,
		    snd_pcm_uframes_t frames)
अणु
	काष्ठा linear_priv *data = (काष्ठा linear_priv *)plugin->extra_data;
	पूर्णांक channel;
	पूर्णांक nchannels = plugin->src_क्रमmat.channels;
	क्रम (channel = 0; channel < nchannels; ++channel) अणु
		अक्षर *src;
		अक्षर *dst;
		पूर्णांक src_step, dst_step;
		snd_pcm_uframes_t frames1;
		अगर (!src_channels[channel].enabled) अणु
			अगर (dst_channels[channel].wanted)
				snd_pcm_area_silence(&dst_channels[channel].area, 0, frames, plugin->dst_क्रमmat.क्रमmat);
			dst_channels[channel].enabled = 0;
			जारी;
		पूर्ण
		dst_channels[channel].enabled = 1;
		src = src_channels[channel].area.addr + src_channels[channel].area.first / 8;
		dst = dst_channels[channel].area.addr + dst_channels[channel].area.first / 8;
		src_step = src_channels[channel].area.step / 8;
		dst_step = dst_channels[channel].area.step / 8;
		frames1 = frames;
		जबतक (frames1-- > 0) अणु
			करो_convert(data, dst, src);
			src += src_step;
			dst += dst_step;
		पूर्ण
	पूर्ण
पूर्ण

अटल snd_pcm_sframes_t linear_transfer(काष्ठा snd_pcm_plugin *plugin,
			       स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			       काष्ठा snd_pcm_plugin_channel *dst_channels,
			       snd_pcm_uframes_t frames)
अणु
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
	अगर (frames > dst_channels[0].frames)
		frames = dst_channels[0].frames;
	convert(plugin, src_channels, dst_channels, frames);
	वापस frames;
पूर्ण

अटल व्योम init_data(काष्ठा linear_priv *data,
		      snd_pcm_क्रमmat_t src_क्रमmat, snd_pcm_क्रमmat_t dst_क्रमmat)
अणु
	पूर्णांक src_le, dst_le, src_bytes, dst_bytes;

	src_bytes = snd_pcm_क्रमmat_width(src_क्रमmat) / 8;
	dst_bytes = snd_pcm_क्रमmat_width(dst_क्रमmat) / 8;
	src_le = snd_pcm_क्रमmat_little_endian(src_क्रमmat) > 0;
	dst_le = snd_pcm_क्रमmat_little_endian(dst_क्रमmat) > 0;

	data->dst_bytes = dst_bytes;
	data->cvt_endian = src_le != dst_le;
	data->copy_bytes = src_bytes < dst_bytes ? src_bytes : dst_bytes;
	अगर (src_le) अणु
		data->copy_ofs = 4 - data->copy_bytes;
		data->src_ofs = src_bytes - data->copy_bytes;
	पूर्ण अन्यथा
		data->src_ofs = snd_pcm_क्रमmat_physical_width(src_क्रमmat) / 8 -
			src_bytes;
	अगर (dst_le)
		data->dst_ofs = 4 - data->dst_bytes;
	अन्यथा
		data->dst_ofs = snd_pcm_क्रमmat_physical_width(dst_क्रमmat) / 8 -
			dst_bytes;
	अगर (snd_pcm_क्रमmat_चिन्हित(src_क्रमmat) !=
	    snd_pcm_क्रमmat_चिन्हित(dst_क्रमmat)) अणु
		अगर (dst_le)
			data->flip = (__क्रमce u32)cpu_to_le32(0x80000000);
		अन्यथा
			data->flip = (__क्रमce u32)cpu_to_be32(0x80000000);
	पूर्ण
पूर्ण

पूर्णांक snd_pcm_plugin_build_linear(काष्ठा snd_pcm_substream *plug,
				काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
				काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
				काष्ठा snd_pcm_plugin **r_plugin)
अणु
	पूर्णांक err;
	काष्ठा linear_priv *data;
	काष्ठा snd_pcm_plugin *plugin;

	अगर (snd_BUG_ON(!r_plugin))
		वापस -ENXIO;
	*r_plugin = शून्य;

	अगर (snd_BUG_ON(src_क्रमmat->rate != dst_क्रमmat->rate))
		वापस -ENXIO;
	अगर (snd_BUG_ON(src_क्रमmat->channels != dst_क्रमmat->channels))
		वापस -ENXIO;
	अगर (snd_BUG_ON(!snd_pcm_क्रमmat_linear(src_क्रमmat->क्रमmat) ||
		       !snd_pcm_क्रमmat_linear(dst_क्रमmat->क्रमmat)))
		वापस -ENXIO;

	err = snd_pcm_plugin_build(plug, "linear format conversion",
				   src_क्रमmat, dst_क्रमmat,
				   माप(काष्ठा linear_priv), &plugin);
	अगर (err < 0)
		वापस err;
	data = (काष्ठा linear_priv *)plugin->extra_data;
	init_data(data, src_क्रमmat->क्रमmat, dst_क्रमmat->क्रमmat);
	plugin->transfer = linear_transfer;
	*r_plugin = plugin;
	वापस 0;
पूर्ण
