<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA PCM device क्रम the
 *  ALSA पूर्णांकerface to cx18 PCM capture streams
 *
 *  Copyright (C) 2009  Andy Walls <awalls@md.metrocast.net>
 *  Copyright (C) 2009  Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 *
 *  Portions of this work were sponsored by ONELAN Limited.
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>

#समावेश <media/v4l2-device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>

#समावेश "cx18-driver.h"
#समावेश "cx18-queue.h"
#समावेश "cx18-streams.h"
#समावेश "cx18-fileops.h"
#समावेश "cx18-alsa.h"
#समावेश "cx18-alsa-pcm.h"

अटल अचिन्हित पूर्णांक pcm_debug;
module_param(pcm_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(pcm_debug, "enable debug messages for pcm");

#घोषणा dprपूर्णांकk(fmt, arg...) करो अणु					\
	    अगर (pcm_debug)						\
		prपूर्णांकk(KERN_INFO "cx18-alsa-pcm %s: " fmt,		\
				  __func__, ##arg);			\
	पूर्ण जबतक (0)

अटल स्थिर काष्ठा snd_pcm_hardware snd_cx18_hw_capture = अणु
	.info = SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP           |
		SNDRV_PCM_INFO_INTERLEAVED    |
		SNDRV_PCM_INFO_MMAP_VALID,

	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,

	.rates = SNDRV_PCM_RATE_48000,

	.rate_min = 48000,
	.rate_max = 48000,
	.channels_min = 2,
	.channels_max = 2,
	.buffer_bytes_max = 62720 * 8,	/* just about the value in usbaudio.c */
	.period_bytes_min = 64,		/* 12544/2, */
	.period_bytes_max = 12544,
	.periods_min = 2,
	.periods_max = 98,		/* 12544, */
पूर्ण;

व्योम cx18_alsa_announce_pcm_data(काष्ठा snd_cx18_card *cxsc, u8 *pcm_data,
				 माप_प्रकार num_bytes)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक oldptr;
	अचिन्हित पूर्णांक stride;
	पूर्णांक period_elapsed = 0;
	पूर्णांक length;

	dprपूर्णांकk("cx18 alsa announce ptr=%p data=%p num_bytes=%zu\n", cxsc,
		pcm_data, num_bytes);

	substream = cxsc->capture_pcm_substream;
	अगर (substream == शून्य) अणु
		dprपूर्णांकk("substream was NULL\n");
		वापस;
	पूर्ण

	runसमय = substream->runसमय;
	अगर (runसमय == शून्य) अणु
		dprपूर्णांकk("runtime was NULL\n");
		वापस;
	पूर्ण

	stride = runसमय->frame_bits >> 3;
	अगर (stride == 0) अणु
		dprपूर्णांकk("stride is zero\n");
		वापस;
	पूर्ण

	length = num_bytes / stride;
	अगर (length == 0) अणु
		dprपूर्णांकk("%s: length was zero\n", __func__);
		वापस;
	पूर्ण

	अगर (runसमय->dma_area == शून्य) अणु
		dprपूर्णांकk("dma area was NULL - ignoring\n");
		वापस;
	पूर्ण

	oldptr = cxsc->hwptr_करोne_capture;
	अगर (oldptr + length >= runसमय->buffer_size) अणु
		अचिन्हित पूर्णांक cnt =
			runसमय->buffer_size - oldptr;
		स_नकल(runसमय->dma_area + oldptr * stride, pcm_data,
		       cnt * stride);
		स_नकल(runसमय->dma_area, pcm_data + cnt * stride,
		       length * stride - cnt * stride);
	पूर्ण अन्यथा अणु
		स_नकल(runसमय->dma_area + oldptr * stride, pcm_data,
		       length * stride);
	पूर्ण
	snd_pcm_stream_lock(substream);

	cxsc->hwptr_करोne_capture += length;
	अगर (cxsc->hwptr_करोne_capture >=
	    runसमय->buffer_size)
		cxsc->hwptr_करोne_capture -=
			runसमय->buffer_size;

	cxsc->capture_transfer_करोne += length;
	अगर (cxsc->capture_transfer_करोne >=
	    runसमय->period_size) अणु
		cxsc->capture_transfer_करोne -=
			runसमय->period_size;
		period_elapsed = 1;
	पूर्ण

	snd_pcm_stream_unlock(substream);

	अगर (period_elapsed)
		snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक snd_cx18_pcm_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cx18_card *cxsc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा v4l2_device *v4l2_dev = cxsc->v4l2_dev;
	काष्ठा cx18 *cx = to_cx18(v4l2_dev);
	काष्ठा cx18_stream *s;
	काष्ठा cx18_खोलो_id item;
	पूर्णांक ret;

	/* Inकाष्ठा the cx18 to start sending packets */
	snd_cx18_lock(cxsc);
	s = &cx->streams[CX18_ENC_STREAM_TYPE_PCM];

	item.cx = cx;
	item.type = s->type;
	item.खोलो_id = cx->खोलो_id++;

	/* See अगर the stream is available */
	अगर (cx18_claim_stream(&item, item.type)) अणु
		/* No, it's alपढ़ोy in use */
		snd_cx18_unlock(cxsc);
		वापस -EBUSY;
	पूर्ण

	अगर (test_bit(CX18_F_S_STREAMOFF, &s->s_flags) ||
	    test_and_set_bit(CX18_F_S_STREAMING, &s->s_flags)) अणु
		/* We're alपढ़ोy streaming.  No additional action required */
		snd_cx18_unlock(cxsc);
		वापस 0;
	पूर्ण


	runसमय->hw = snd_cx18_hw_capture;
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	cxsc->capture_pcm_substream = substream;
	runसमय->निजी_data = cx;

	cx->pcm_announce_callback = cx18_alsa_announce_pcm_data;

	/* Not currently streaming, so start it up */
	set_bit(CX18_F_S_STREAMING, &s->s_flags);
	ret = cx18_start_v4l2_encode_stream(s);
	snd_cx18_unlock(cxsc);

	वापस ret;
पूर्ण

अटल पूर्णांक snd_cx18_pcm_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cx18_card *cxsc = snd_pcm_substream_chip(substream);
	काष्ठा v4l2_device *v4l2_dev = cxsc->v4l2_dev;
	काष्ठा cx18 *cx = to_cx18(v4l2_dev);
	काष्ठा cx18_stream *s;

	/* Inकाष्ठा the cx18 to stop sending packets */
	snd_cx18_lock(cxsc);
	s = &cx->streams[CX18_ENC_STREAM_TYPE_PCM];
	cx18_stop_v4l2_encode_stream(s, 0);
	clear_bit(CX18_F_S_STREAMING, &s->s_flags);

	cx18_release_stream(s);

	cx->pcm_announce_callback = शून्य;
	snd_cx18_unlock(cxsc);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx18_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_cx18_card *cxsc = snd_pcm_substream_chip(substream);

	cxsc->hwptr_करोne_capture = 0;
	cxsc->capture_transfer_करोne = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_cx18_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	वापस 0;
पूर्ण

अटल
snd_pcm_uframes_t snd_cx18_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	snd_pcm_uframes_t hwptr_करोne;
	काष्ठा snd_cx18_card *cxsc = snd_pcm_substream_chip(substream);

	spin_lock_irqsave(&cxsc->slock, flags);
	hwptr_करोne = cxsc->hwptr_करोne_capture;
	spin_unlock_irqrestore(&cxsc->slock, flags);

	वापस hwptr_करोne;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_cx18_pcm_capture_ops = अणु
	.खोलो		= snd_cx18_pcm_capture_खोलो,
	.बंद		= snd_cx18_pcm_capture_बंद,
	.prepare	= snd_cx18_pcm_prepare,
	.trigger	= snd_cx18_pcm_trigger,
	.poपूर्णांकer	= snd_cx18_pcm_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_cx18_pcm_create(काष्ठा snd_cx18_card *cxsc)
अणु
	काष्ठा snd_pcm *sp;
	काष्ठा snd_card *sc = cxsc->sc;
	काष्ठा v4l2_device *v4l2_dev = cxsc->v4l2_dev;
	काष्ठा cx18 *cx = to_cx18(v4l2_dev);
	पूर्णांक ret;

	ret = snd_pcm_new(sc, "CX23418 PCM",
			  0, /* PCM device 0, the only one क्रम this card */
			  0, /* 0 playback substreams */
			  1, /* 1 capture substream */
			  &sp);
	अगर (ret) अणु
		CX18_ALSA_ERR("%s: snd_cx18_pcm_create() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास;
	पूर्ण

	spin_lock_init(&cxsc->slock);

	snd_pcm_set_ops(sp, SNDRV_PCM_STREAM_CAPTURE,
			&snd_cx18_pcm_capture_ops);
	snd_pcm_set_managed_buffer_all(sp, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);
	sp->info_flags = 0;
	sp->निजी_data = cxsc;
	strscpy(sp->name, cx->card_name, माप(sp->name));

	वापस 0;

err_निकास:
	वापस ret;
पूर्ण
