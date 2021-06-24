<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  ALSA PCM device क्रम the
 *  ALSA पूर्णांकerface to cobalt PCM capture streams
 *
 *  Copyright 2014-2015 Cisco Systems, Inc. and/or its affiliates.
 *  All rights reserved.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/delay.h>

#समावेश <media/v4l2-device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "cobalt-driver.h"
#समावेश "cobalt-alsa.h"
#समावेश "cobalt-alsa-pcm.h"

अटल अचिन्हित पूर्णांक pcm_debug;
module_param(pcm_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(pcm_debug, "enable debug messages for pcm");

#घोषणा dprपूर्णांकk(fmt, arg...) \
	करो अणु \
		अगर (pcm_debug) \
			pr_info("cobalt-alsa-pcm %s: " fmt, __func__, ##arg); \
	पूर्ण जबतक (0)

अटल स्थिर काष्ठा snd_pcm_hardware snd_cobalt_hdmi_capture = अणु
	.info = SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP           |
		SNDRV_PCM_INFO_INTERLEAVED    |
		SNDRV_PCM_INFO_MMAP_VALID,

	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,

	.rates = SNDRV_PCM_RATE_48000,

	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 8,
	.buffer_bytes_max = 4 * 240 * 8 * 4,	/* 5 ms of data */
	.period_bytes_min = 1920,		/* 1 sample = 8 * 4 bytes */
	.period_bytes_max = 240 * 8 * 4,	/* 5 ms of 8 channel data */
	.periods_min = 1,
	.periods_max = 4,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware snd_cobalt_playback = अणु
	.info = SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP           |
		SNDRV_PCM_INFO_INTERLEAVED    |
		SNDRV_PCM_INFO_MMAP_VALID,

	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE | SNDRV_PCM_FMTBIT_S32_LE,

	.rates = SNDRV_PCM_RATE_48000,

	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 1,
	.channels_max = 8,
	.buffer_bytes_max = 4 * 240 * 8 * 4,	/* 5 ms of data */
	.period_bytes_min = 1920,		/* 1 sample = 8 * 4 bytes */
	.period_bytes_max = 240 * 8 * 4,	/* 5 ms of 8 channel data */
	.periods_min = 1,
	.periods_max = 4,
पूर्ण;

अटल व्योम sample_cpy(u8 *dst, स्थिर u8 *src, u32 len, bool is_s32)
अणु
	अटल स्थिर अचिन्हित map[8] = अणु 0, 1, 5, 4, 2, 3, 6, 7 पूर्ण;
	अचिन्हित idx = 0;

	जबतक (len >= (is_s32 ? 4 : 2)) अणु
		अचिन्हित offset = map[idx] * 4;
		u32 val = src[offset + 1] + (src[offset + 2] << 8) +
			 (src[offset + 3] << 16);

		अगर (is_s32) अणु
			*dst++ = 0;
			*dst++ = val & 0xff;
		पूर्ण
		*dst++ = (val >> 8) & 0xff;
		*dst++ = (val >> 16) & 0xff;
		len -= is_s32 ? 4 : 2;
		idx++;
	पूर्ण
पूर्ण

अटल व्योम cobalt_alsa_announce_pcm_data(काष्ठा snd_cobalt_card *cobsc,
					u8 *pcm_data,
					माप_प्रकार skip,
					माप_प्रकार samples)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक oldptr;
	अचिन्हित पूर्णांक stride;
	पूर्णांक length = samples;
	पूर्णांक period_elapsed = 0;
	bool is_s32;

	dprपूर्णांकk("cobalt alsa announce ptr=%p data=%p num_bytes=%zd\n", cobsc,
		pcm_data, samples);

	substream = cobsc->capture_pcm_substream;
	अगर (substream == शून्य) अणु
		dprपूर्णांकk("substream was NULL\n");
		वापस;
	पूर्ण

	runसमय = substream->runसमय;
	अगर (runसमय == शून्य) अणु
		dprपूर्णांकk("runtime was NULL\n");
		वापस;
	पूर्ण
	is_s32 = runसमय->क्रमmat == SNDRV_PCM_FORMAT_S32_LE;

	stride = runसमय->frame_bits >> 3;
	अगर (stride == 0) अणु
		dprपूर्णांकk("stride is zero\n");
		वापस;
	पूर्ण

	अगर (length == 0) अणु
		dprपूर्णांकk("%s: length was zero\n", __func__);
		वापस;
	पूर्ण

	अगर (runसमय->dma_area == शून्य) अणु
		dprपूर्णांकk("dma area was NULL - ignoring\n");
		वापस;
	पूर्ण

	oldptr = cobsc->hwptr_करोne_capture;
	अगर (oldptr + length >= runसमय->buffer_size) अणु
		अचिन्हित पूर्णांक cnt = runसमय->buffer_size - oldptr;
		अचिन्हित i;

		क्रम (i = 0; i < cnt; i++)
			sample_cpy(runसमय->dma_area + (oldptr + i) * stride,
					pcm_data + i * skip,
					stride, is_s32);
		क्रम (i = cnt; i < length; i++)
			sample_cpy(runसमय->dma_area + (i - cnt) * stride,
					pcm_data + i * skip, stride, is_s32);
	पूर्ण अन्यथा अणु
		अचिन्हित i;

		क्रम (i = 0; i < length; i++)
			sample_cpy(runसमय->dma_area + (oldptr + i) * stride,
					pcm_data + i * skip,
					stride, is_s32);
	पूर्ण
	snd_pcm_stream_lock_irqsave(substream, flags);

	cobsc->hwptr_करोne_capture += length;
	अगर (cobsc->hwptr_करोne_capture >=
	    runसमय->buffer_size)
		cobsc->hwptr_करोne_capture -=
			runसमय->buffer_size;

	cobsc->capture_transfer_करोne += length;
	अगर (cobsc->capture_transfer_करोne >=
	    runसमय->period_size) अणु
		cobsc->capture_transfer_करोne -=
			runसमय->period_size;
		period_elapsed = 1;
	पूर्ण

	snd_pcm_stream_unlock_irqrestore(substream, flags);

	अगर (period_elapsed)
		snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक alsa_fnc(काष्ठा vb2_buffer *vb, व्योम *priv)
अणु
	काष्ठा cobalt_stream *s = priv;
	अचिन्हित अक्षर *p = vb2_plane_vaddr(vb, 0);
	पूर्णांक i;

	अगर (pcm_debug) अणु
		pr_info("alsa: ");
		क्रम (i = 0; i < 8 * 4; i++) अणु
			अगर (!(i & 3))
				pr_cont(" ");
			pr_cont("%02x", p[i]);
		पूर्ण
		pr_cont("\n");
	पूर्ण
	cobalt_alsa_announce_pcm_data(s->alsa,
			vb2_plane_vaddr(vb, 0),
			8 * 4,
			vb2_get_plane_payload(vb, 0) / (8 * 4));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_pcm_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);
	काष्ठा cobalt_stream *s = cobsc->s;

	runसमय->hw = snd_cobalt_hdmi_capture;
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	cobsc->capture_pcm_substream = substream;
	runसमय->निजी_data = s;
	cobsc->alsa_record_cnt++;
	अगर (cobsc->alsa_record_cnt == 1) अणु
		पूर्णांक rc;

		rc = vb2_thपढ़ो_start(&s->q, alsa_fnc, s, s->vdev.name);
		अगर (rc) अणु
			cobsc->alsa_record_cnt--;
			वापस rc;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_pcm_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);
	काष्ठा cobalt_stream *s = cobsc->s;

	cobsc->alsa_record_cnt--;
	अगर (cobsc->alsa_record_cnt == 0)
		vb2_thपढ़ो_stop(&s->q);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);

	cobsc->hwptr_करोne_capture = 0;
	cobsc->capture_transfer_करोne = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_STOP:
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल
snd_pcm_uframes_t snd_cobalt_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_uframes_t hwptr_करोne;
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);

	hwptr_करोne = cobsc->hwptr_करोne_capture;

	वापस hwptr_करोne;
पूर्ण

अटल व्योम pb_sample_cpy(u8 *dst, स्थिर u8 *src, u32 len, bool is_s32)
अणु
	अटल स्थिर अचिन्हित map[8] = अणु 0, 1, 5, 4, 2, 3, 6, 7 पूर्ण;
	अचिन्हित idx = 0;

	जबतक (len >= (is_s32 ? 4 : 2)) अणु
		अचिन्हित offset = map[idx] * 4;
		u8 *out = dst + offset;

		*out++ = 0;
		अगर (is_s32) अणु
			src++;
			*out++ = *src++;
		पूर्ण अन्यथा अणु
			*out++ = 0;
		पूर्ण
		*out++ = *src++;
		*out = *src++;
		len -= is_s32 ? 4 : 2;
		idx++;
	पूर्ण
पूर्ण

अटल व्योम cobalt_alsa_pb_pcm_data(काष्ठा snd_cobalt_card *cobsc,
					u8 *pcm_data,
					माप_प्रकार skip,
					माप_प्रकार samples)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित दीर्घ flags;
	अचिन्हित पूर्णांक pos;
	अचिन्हित पूर्णांक stride;
	bool is_s32;
	अचिन्हित i;

	dprपूर्णांकk("cobalt alsa pb ptr=%p data=%p samples=%zd\n", cobsc,
		pcm_data, samples);

	substream = cobsc->playback_pcm_substream;
	अगर (substream == शून्य) अणु
		dprपूर्णांकk("substream was NULL\n");
		वापस;
	पूर्ण

	runसमय = substream->runसमय;
	अगर (runसमय == शून्य) अणु
		dprपूर्णांकk("runtime was NULL\n");
		वापस;
	पूर्ण

	is_s32 = runसमय->क्रमmat == SNDRV_PCM_FORMAT_S32_LE;
	stride = runसमय->frame_bits >> 3;
	अगर (stride == 0) अणु
		dprपूर्णांकk("stride is zero\n");
		वापस;
	पूर्ण

	अगर (samples == 0) अणु
		dprपूर्णांकk("%s: samples was zero\n", __func__);
		वापस;
	पूर्ण

	अगर (runसमय->dma_area == शून्य) अणु
		dprपूर्णांकk("dma area was NULL - ignoring\n");
		वापस;
	पूर्ण

	pos = cobsc->pb_pos % cobsc->pb_size;
	क्रम (i = 0; i < cobsc->pb_count / (8 * 4); i++)
		pb_sample_cpy(pcm_data + i * skip,
				runसमय->dma_area + pos + i * stride,
				stride, is_s32);
	snd_pcm_stream_lock_irqsave(substream, flags);

	cobsc->pb_pos += i * stride;

	snd_pcm_stream_unlock_irqrestore(substream, flags);
	अगर (cobsc->pb_pos % cobsc->pb_count == 0)
		snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक alsa_pb_fnc(काष्ठा vb2_buffer *vb, व्योम *priv)
अणु
	काष्ठा cobalt_stream *s = priv;

	अगर (s->alsa->alsa_pb_channel)
		cobalt_alsa_pb_pcm_data(s->alsa,
				vb2_plane_vaddr(vb, 0),
				8 * 4,
				vb2_get_plane_payload(vb, 0) / (8 * 4));
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_pcm_playback_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा cobalt_stream *s = cobsc->s;

	runसमय->hw = snd_cobalt_playback;
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	cobsc->playback_pcm_substream = substream;
	runसमय->निजी_data = s;
	cobsc->alsa_playback_cnt++;
	अगर (cobsc->alsa_playback_cnt == 1) अणु
		पूर्णांक rc;

		rc = vb2_thपढ़ो_start(&s->q, alsa_pb_fnc, s, s->vdev.name);
		अगर (rc) अणु
			cobsc->alsa_playback_cnt--;
			वापस rc;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_pcm_playback_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);
	काष्ठा cobalt_stream *s = cobsc->s;

	cobsc->alsa_playback_cnt--;
	अगर (cobsc->alsa_playback_cnt == 0)
		vb2_thपढ़ो_stop(&s->q);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_pcm_pb_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);

	cobsc->pb_size = snd_pcm_lib_buffer_bytes(substream);
	cobsc->pb_count = snd_pcm_lib_period_bytes(substream);
	cobsc->pb_pos = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cobalt_pcm_pb_trigger(काष्ठा snd_pcm_substream *substream,
				     पूर्णांक cmd)
अणु
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		अगर (cobsc->alsa_pb_channel)
			वापस -EBUSY;
		cobsc->alsa_pb_channel = true;
		वापस 0;
	हाल SNDRV_PCM_TRIGGER_STOP:
		cobsc->alsa_pb_channel = false;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल
snd_pcm_uframes_t snd_cobalt_pcm_pb_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cobalt_card *cobsc = snd_pcm_substream_chip(substream);
	माप_प्रकार ptr;

	ptr = cobsc->pb_pos;

	वापस bytes_to_frames(substream->runसमय, ptr) %
	       substream->runसमय->buffer_size;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_cobalt_pcm_capture_ops = अणु
	.खोलो		= snd_cobalt_pcm_capture_खोलो,
	.बंद		= snd_cobalt_pcm_capture_बंद,
	.prepare	= snd_cobalt_pcm_prepare,
	.trigger	= snd_cobalt_pcm_trigger,
	.poपूर्णांकer	= snd_cobalt_pcm_poपूर्णांकer,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_ops snd_cobalt_pcm_playback_ops = अणु
	.खोलो		= snd_cobalt_pcm_playback_खोलो,
	.बंद		= snd_cobalt_pcm_playback_बंद,
	.prepare	= snd_cobalt_pcm_pb_prepare,
	.trigger	= snd_cobalt_pcm_pb_trigger,
	.poपूर्णांकer	= snd_cobalt_pcm_pb_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_cobalt_pcm_create(काष्ठा snd_cobalt_card *cobsc)
अणु
	काष्ठा snd_pcm *sp;
	काष्ठा snd_card *sc = cobsc->sc;
	काष्ठा cobalt_stream *s = cobsc->s;
	काष्ठा cobalt *cobalt = s->cobalt;
	पूर्णांक ret;

	s->q.gfp_flags |= __GFP_ZERO;

	अगर (!s->is_output) अणु
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_AUDIO_IPP_RESETN_BIT(s->video_channel),
			0);
		mdelay(2);
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_AUDIO_IPP_RESETN_BIT(s->video_channel),
			1);
		mdelay(1);

		ret = snd_pcm_new(sc, "Cobalt PCM-In HDMI",
			0, /* PCM device 0, the only one क्रम this card */
			0, /* 0 playback substreams */
			1, /* 1 capture substream */
			&sp);
		अगर (ret) अणु
			cobalt_err("snd_cobalt_pcm_create() failed for input with err %d\n",
				   ret);
			जाओ err_निकास;
		पूर्ण

		snd_pcm_set_ops(sp, SNDRV_PCM_STREAM_CAPTURE,
				&snd_cobalt_pcm_capture_ops);
		snd_pcm_set_managed_buffer_all(sp, SNDRV_DMA_TYPE_VMALLOC,
					       शून्य, 0, 0);
		sp->info_flags = 0;
		sp->निजी_data = cobsc;
		strscpy(sp->name, "cobalt", माप(sp->name));
	पूर्ण अन्यथा अणु
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_AUDIO_OPP_RESETN_BIT, 0);
		mdelay(2);
		cobalt_s_bit_sysctrl(cobalt,
			COBALT_SYS_CTRL_AUDIO_OPP_RESETN_BIT, 1);
		mdelay(1);

		ret = snd_pcm_new(sc, "Cobalt PCM-Out HDMI",
			0, /* PCM device 0, the only one क्रम this card */
			1, /* 0 playback substreams */
			0, /* 1 capture substream */
			&sp);
		अगर (ret) अणु
			cobalt_err("snd_cobalt_pcm_create() failed for output with err %d\n",
				   ret);
			जाओ err_निकास;
		पूर्ण

		snd_pcm_set_ops(sp, SNDRV_PCM_STREAM_PLAYBACK,
				&snd_cobalt_pcm_playback_ops);
		snd_pcm_set_managed_buffer_all(sp, SNDRV_DMA_TYPE_VMALLOC,
					       शून्य, 0, 0);
		sp->info_flags = 0;
		sp->निजी_data = cobsc;
		strscpy(sp->name, "cobalt", माप(sp->name));
	पूर्ण

	वापस 0;

err_निकास:
	वापस ret;
पूर्ण
