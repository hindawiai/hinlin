<शैली गुरु>
/*
 *  Mu-Law conversion Plug-In Interface
 *  Copyright (c) 1999 by Jaroslav Kysela <perex@perex.cz>
 *                        Uros Bizjak <uros@kss-loka.si>
 *
 *  Based on reference implementation by Sun Microप्रणालीs, Inc.
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

#घोषणा	SIGN_BIT	(0x80)		/* Sign bit क्रम a u-law byte. */
#घोषणा	QUANT_MASK	(0xf)		/* Quantization field mask. */
#घोषणा	NSEGS		(8)		/* Number of u-law segments. */
#घोषणा	SEG_SHIFT	(4)		/* Left shअगरt क्रम segment number. */
#घोषणा	SEG_MASK	(0x70)		/* Segment field mask. */

अटल अंतरभूत पूर्णांक val_seg(पूर्णांक val)
अणु
	पूर्णांक r = 0;
	val >>= 7;
	अगर (val & 0xf0) अणु
		val >>= 4;
		r += 4;
	पूर्ण
	अगर (val & 0x0c) अणु
		val >>= 2;
		r += 2;
	पूर्ण
	अगर (val & 0x02)
		r += 1;
	वापस r;
पूर्ण

#घोषणा	BIAS		(0x84)		/* Bias क्रम linear code. */

/*
 * linear2ulaw() - Convert a linear PCM value to u-law
 *
 * In order to simplअगरy the encoding process, the original linear magnitude
 * is biased by adding 33 which shअगरts the encoding range from (0 - 8158) to
 * (33 - 8191). The result can be seen in the following encoding table:
 *
 *	Biased Linear Input Code	Compressed Code
 *	------------------------	---------------
 *	00000001wxyza			000wxyz
 *	0000001wxyzab			001wxyz
 *	000001wxyzabc			010wxyz
 *	00001wxyzabcd			011wxyz
 *	0001wxyzabcde			100wxyz
 *	001wxyzabcdef			101wxyz
 *	01wxyzabcdefg			110wxyz
 *	1wxyzabcdefgh			111wxyz
 *
 * Each biased linear code has a leading 1 which identअगरies the segment
 * number. The value of the segment number is equal to 7 minus the number
 * of leading 0's. The quantization पूर्णांकerval is directly available as the
 * four bits wxyz.  * The trailing bits (a - h) are ignored.
 *
 * Ordinarily the complement of the resulting code word is used क्रम
 * transmission, and so the code word is complemented beक्रमe it is वापसed.
 *
 * For further inक्रमmation see John C. Bellamy's Digital Telephony, 1982,
 * John Wiley & Sons, pps 98-111 and 472-476.
 */
अटल अचिन्हित अक्षर linear2ulaw(पूर्णांक pcm_val)	/* 2's complement (16-bit range) */
अणु
	पूर्णांक mask;
	पूर्णांक seg;
	अचिन्हित अक्षर uval;

	/* Get the sign and the magnitude of the value. */
	अगर (pcm_val < 0) अणु
		pcm_val = BIAS - pcm_val;
		mask = 0x7F;
	पूर्ण अन्यथा अणु
		pcm_val += BIAS;
		mask = 0xFF;
	पूर्ण
	अगर (pcm_val > 0x7FFF)
		pcm_val = 0x7FFF;

	/* Convert the scaled magnitude to segment number. */
	seg = val_seg(pcm_val);

	/*
	 * Combine the sign, segment, quantization bits;
	 * and complement the code word.
	 */
	uval = (seg << 4) | ((pcm_val >> (seg + 3)) & 0xF);
	वापस uval ^ mask;
पूर्ण

/*
 * ulaw2linear() - Convert a u-law value to 16-bit linear PCM
 *
 * First, a biased linear code is derived from the code word. An unbiased
 * output can then be obtained by subtracting 33 from the biased code.
 *
 * Note that this function expects to be passed the complement of the
 * original code word. This is in keeping with ISDN conventions.
 */
अटल पूर्णांक ulaw2linear(अचिन्हित अक्षर u_val)
अणु
	पूर्णांक t;

	/* Complement to obtain normal u-law value. */
	u_val = ~u_val;

	/*
	 * Extract and bias the quantization bits. Then
	 * shअगरt up by the segment number and subtract out the bias.
	 */
	t = ((u_val & QUANT_MASK) << 3) + BIAS;
	t <<= ((अचिन्हित)u_val & SEG_MASK) >> SEG_SHIFT;

	वापस ((u_val & SIGN_BIT) ? (BIAS - t) : (t - BIAS));
पूर्ण

/*
 *  Basic Mu-Law plugin
 */

प्रकार व्योम (*mulaw_f)(काष्ठा snd_pcm_plugin *plugin,
			स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			काष्ठा snd_pcm_plugin_channel *dst_channels,
			snd_pcm_uframes_t frames);

काष्ठा mulaw_priv अणु
	mulaw_f func;
	पूर्णांक cvt_endian;			/* need endian conversion? */
	अचिन्हित पूर्णांक native_ofs;	/* byte offset in native क्रमmat */
	अचिन्हित पूर्णांक copy_ofs;		/* byte offset in s16 क्रमmat */
	अचिन्हित पूर्णांक native_bytes;	/* byte size of the native क्रमmat */
	अचिन्हित पूर्णांक copy_bytes;	/* bytes to copy per conversion */
	u16 flip; /* MSB flip क्रम चिन्हितness, करोne after endian conversion */
पूर्ण;

अटल अंतरभूत व्योम cvt_s16_to_native(काष्ठा mulaw_priv *data,
				     अचिन्हित अक्षर *dst, u16 sample)
अणु
	sample ^= data->flip;
	अगर (data->cvt_endian)
		sample = swab16(sample);
	अगर (data->native_bytes > data->copy_bytes)
		स_रखो(dst, 0, data->native_bytes);
	स_नकल(dst + data->native_ofs, (अक्षर *)&sample + data->copy_ofs,
	       data->copy_bytes);
पूर्ण

अटल व्योम mulaw_decode(काष्ठा snd_pcm_plugin *plugin,
			स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			काष्ठा snd_pcm_plugin_channel *dst_channels,
			snd_pcm_uframes_t frames)
अणु
	काष्ठा mulaw_priv *data = (काष्ठा mulaw_priv *)plugin->extra_data;
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
			चिन्हित लघु sample = ulaw2linear(*src);
			cvt_s16_to_native(data, dst, sample);
			src += src_step;
			dst += dst_step;
		पूर्ण
	पूर्ण
पूर्ण

अटल अंतरभूत चिन्हित लघु cvt_native_to_s16(काष्ठा mulaw_priv *data,
					     अचिन्हित अक्षर *src)
अणु
	u16 sample = 0;
	स_नकल((अक्षर *)&sample + data->copy_ofs, src + data->native_ofs,
	       data->copy_bytes);
	अगर (data->cvt_endian)
		sample = swab16(sample);
	sample ^= data->flip;
	वापस (चिन्हित लघु)sample;
पूर्ण

अटल व्योम mulaw_encode(काष्ठा snd_pcm_plugin *plugin,
			स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			काष्ठा snd_pcm_plugin_channel *dst_channels,
			snd_pcm_uframes_t frames)
अणु
	काष्ठा mulaw_priv *data = (काष्ठा mulaw_priv *)plugin->extra_data;
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
			चिन्हित लघु sample = cvt_native_to_s16(data, src);
			*dst = linear2ulaw(sample);
			src += src_step;
			dst += dst_step;
		पूर्ण
	पूर्ण
पूर्ण

अटल snd_pcm_sframes_t mulaw_transfer(काष्ठा snd_pcm_plugin *plugin,
			      स्थिर काष्ठा snd_pcm_plugin_channel *src_channels,
			      काष्ठा snd_pcm_plugin_channel *dst_channels,
			      snd_pcm_uframes_t frames)
अणु
	काष्ठा mulaw_priv *data;

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
	data = (काष्ठा mulaw_priv *)plugin->extra_data;
	data->func(plugin, src_channels, dst_channels, frames);
	वापस frames;
पूर्ण

अटल व्योम init_data(काष्ठा mulaw_priv *data, snd_pcm_क्रमmat_t क्रमmat)
अणु
#अगर_घोषित SNDRV_LITTLE_ENDIAN
	data->cvt_endian = snd_pcm_क्रमmat_big_endian(क्रमmat) > 0;
#अन्यथा
	data->cvt_endian = snd_pcm_क्रमmat_little_endian(क्रमmat) > 0;
#पूर्ण_अगर
	अगर (!snd_pcm_क्रमmat_चिन्हित(क्रमmat))
		data->flip = 0x8000;
	data->native_bytes = snd_pcm_क्रमmat_physical_width(क्रमmat) / 8;
	data->copy_bytes = data->native_bytes < 2 ? 1 : 2;
	अगर (snd_pcm_क्रमmat_little_endian(क्रमmat)) अणु
		data->native_ofs = data->native_bytes - data->copy_bytes;
		data->copy_ofs = 2 - data->copy_bytes;
	पूर्ण अन्यथा अणु
		/* S24 in 4bytes need an 1 byte offset */
		data->native_ofs = data->native_bytes -
			snd_pcm_क्रमmat_width(क्रमmat) / 8;
	पूर्ण
पूर्ण

पूर्णांक snd_pcm_plugin_build_mulaw(काष्ठा snd_pcm_substream *plug,
			       काष्ठा snd_pcm_plugin_क्रमmat *src_क्रमmat,
			       काष्ठा snd_pcm_plugin_क्रमmat *dst_क्रमmat,
			       काष्ठा snd_pcm_plugin **r_plugin)
अणु
	पूर्णांक err;
	काष्ठा mulaw_priv *data;
	काष्ठा snd_pcm_plugin *plugin;
	काष्ठा snd_pcm_plugin_क्रमmat *क्रमmat;
	mulaw_f func;

	अगर (snd_BUG_ON(!r_plugin))
		वापस -ENXIO;
	*r_plugin = शून्य;

	अगर (snd_BUG_ON(src_क्रमmat->rate != dst_क्रमmat->rate))
		वापस -ENXIO;
	अगर (snd_BUG_ON(src_क्रमmat->channels != dst_क्रमmat->channels))
		वापस -ENXIO;

	अगर (dst_क्रमmat->क्रमmat == SNDRV_PCM_FORMAT_MU_LAW) अणु
		क्रमmat = src_क्रमmat;
		func = mulaw_encode;
	पूर्ण
	अन्यथा अगर (src_क्रमmat->क्रमmat == SNDRV_PCM_FORMAT_MU_LAW) अणु
		क्रमmat = dst_क्रमmat;
		func = mulaw_decode;
	पूर्ण
	अन्यथा अणु
		snd_BUG();
		वापस -EINVAL;
	पूर्ण
	अगर (!snd_pcm_क्रमmat_linear(क्रमmat->क्रमmat))
		वापस -EINVAL;

	err = snd_pcm_plugin_build(plug, "Mu-Law<->linear conversion",
				   src_क्रमmat, dst_क्रमmat,
				   माप(काष्ठा mulaw_priv), &plugin);
	अगर (err < 0)
		वापस err;
	data = (काष्ठा mulaw_priv *)plugin->extra_data;
	data->func = func;
	init_data(data, क्रमmat->क्रमmat);
	plugin->transfer = mulaw_transfer;
	*r_plugin = plugin;
	वापस 0;
पूर्ण
