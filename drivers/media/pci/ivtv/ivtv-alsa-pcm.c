<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  ALSA PCM device क्रम the
 *  ALSA पूर्णांकerface to ivtv PCM capture streams
 *
 *  Copyright (C) 2009,2012  Andy Walls <awalls@md.metrocast.net>
 *  Copyright (C) 2009  Devin Heiपंचांगueller <dheiपंचांगueller@kernelद_असल.com>
 *
 *  Portions of this work were sponsored by ONELAN Limited क्रम the cx18 driver
 */

#समावेश "ivtv-driver.h"
#समावेश "ivtv-queue.h"
#समावेश "ivtv-streams.h"
#समावेश "ivtv-fileops.h"
#समावेश "ivtv-alsa.h"
#समावेश "ivtv-alsa-pcm.h"

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>


अटल अचिन्हित पूर्णांक pcm_debug;
module_param(pcm_debug, पूर्णांक, 0644);
MODULE_PARM_DESC(pcm_debug, "enable debug messages for pcm");

#घोषणा dprपूर्णांकk(fmt, arg...) \
	करो अणु \
		अगर (pcm_debug) \
			pr_info("ivtv-alsa-pcm %s: " fmt, __func__, ##arg); \
	पूर्ण जबतक (0)

अटल स्थिर काष्ठा snd_pcm_hardware snd_ivtv_hw_capture = अणु
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

अटल व्योम ivtv_alsa_announce_pcm_data(काष्ठा snd_ivtv_card *itvsc,
					u8 *pcm_data,
					माप_प्रकार num_bytes)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	अचिन्हित पूर्णांक oldptr;
	अचिन्हित पूर्णांक stride;
	पूर्णांक period_elapsed = 0;
	पूर्णांक length;

	dprपूर्णांकk("ivtv alsa announce ptr=%p data=%p num_bytes=%zu\n", itvsc,
		pcm_data, num_bytes);

	substream = itvsc->capture_pcm_substream;
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

	oldptr = itvsc->hwptr_करोne_capture;
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

	itvsc->hwptr_करोne_capture += length;
	अगर (itvsc->hwptr_करोne_capture >=
	    runसमय->buffer_size)
		itvsc->hwptr_करोne_capture -=
			runसमय->buffer_size;

	itvsc->capture_transfer_करोne += length;
	अगर (itvsc->capture_transfer_करोne >=
	    runसमय->period_size) अणु
		itvsc->capture_transfer_करोne -=
			runसमय->period_size;
		period_elapsed = 1;
	पूर्ण

	snd_pcm_stream_unlock(substream);

	अगर (period_elapsed)
		snd_pcm_period_elapsed(substream);
पूर्ण

अटल पूर्णांक snd_ivtv_pcm_capture_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ivtv_card *itvsc = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा v4l2_device *v4l2_dev = itvsc->v4l2_dev;
	काष्ठा ivtv *itv = to_ivtv(v4l2_dev);
	काष्ठा ivtv_stream *s;
	काष्ठा ivtv_खोलो_id item;
	पूर्णांक ret;

	/* Inकाष्ठा the CX2341[56] to start sending packets */
	snd_ivtv_lock(itvsc);

	अगर (ivtv_init_on_first_खोलो(itv)) अणु
		snd_ivtv_unlock(itvsc);
		वापस -ENXIO;
	पूर्ण

	s = &itv->streams[IVTV_ENC_STREAM_TYPE_PCM];

	v4l2_fh_init(&item.fh, &s->vdev);
	item.itv = itv;
	item.type = s->type;

	/* See अगर the stream is available */
	अगर (ivtv_claim_stream(&item, item.type)) अणु
		/* No, it's alपढ़ोy in use */
		v4l2_fh_निकास(&item.fh);
		snd_ivtv_unlock(itvsc);
		वापस -EBUSY;
	पूर्ण

	अगर (test_bit(IVTV_F_S_STREAMOFF, &s->s_flags) ||
	    test_and_set_bit(IVTV_F_S_STREAMING, &s->s_flags)) अणु
		/* We're alपढ़ोy streaming.  No additional action required */
		snd_ivtv_unlock(itvsc);
		वापस 0;
	पूर्ण


	runसमय->hw = snd_ivtv_hw_capture;
	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);
	itvsc->capture_pcm_substream = substream;
	runसमय->निजी_data = itv;

	itv->pcm_announce_callback = ivtv_alsa_announce_pcm_data;

	/* Not currently streaming, so start it up */
	set_bit(IVTV_F_S_STREAMING, &s->s_flags);
	ret = ivtv_start_v4l2_encode_stream(s);
	snd_ivtv_unlock(itvsc);

	वापस ret;
पूर्ण

अटल पूर्णांक snd_ivtv_pcm_capture_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ivtv_card *itvsc = snd_pcm_substream_chip(substream);
	काष्ठा v4l2_device *v4l2_dev = itvsc->v4l2_dev;
	काष्ठा ivtv *itv = to_ivtv(v4l2_dev);
	काष्ठा ivtv_stream *s;

	/* Inकाष्ठा the ivtv to stop sending packets */
	snd_ivtv_lock(itvsc);
	s = &itv->streams[IVTV_ENC_STREAM_TYPE_PCM];
	ivtv_stop_v4l2_encode_stream(s, 0);
	clear_bit(IVTV_F_S_STREAMING, &s->s_flags);

	ivtv_release_stream(s);

	itv->pcm_announce_callback = शून्य;
	snd_ivtv_unlock(itvsc);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ivtv_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_ivtv_card *itvsc = snd_pcm_substream_chip(substream);

	itvsc->hwptr_करोne_capture = 0;
	itvsc->capture_transfer_करोne = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक snd_ivtv_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	वापस 0;
पूर्ण

अटल
snd_pcm_uframes_t snd_ivtv_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	अचिन्हित दीर्घ flags;
	snd_pcm_uframes_t hwptr_करोne;
	काष्ठा snd_ivtv_card *itvsc = snd_pcm_substream_chip(substream);

	spin_lock_irqsave(&itvsc->slock, flags);
	hwptr_करोne = itvsc->hwptr_करोne_capture;
	spin_unlock_irqrestore(&itvsc->slock, flags);

	वापस hwptr_करोne;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops snd_ivtv_pcm_capture_ops = अणु
	.खोलो		= snd_ivtv_pcm_capture_खोलो,
	.बंद		= snd_ivtv_pcm_capture_बंद,
	.prepare	= snd_ivtv_pcm_prepare,
	.trigger	= snd_ivtv_pcm_trigger,
	.poपूर्णांकer	= snd_ivtv_pcm_poपूर्णांकer,
पूर्ण;

पूर्णांक snd_ivtv_pcm_create(काष्ठा snd_ivtv_card *itvsc)
अणु
	काष्ठा snd_pcm *sp;
	काष्ठा snd_card *sc = itvsc->sc;
	काष्ठा v4l2_device *v4l2_dev = itvsc->v4l2_dev;
	काष्ठा ivtv *itv = to_ivtv(v4l2_dev);
	पूर्णांक ret;

	ret = snd_pcm_new(sc, "CX2341[56] PCM",
			  0, /* PCM device 0, the only one क्रम this card */
			  0, /* 0 playback substreams */
			  1, /* 1 capture substream */
			  &sp);
	अगर (ret) अणु
		IVTV_ALSA_ERR("%s: snd_ivtv_pcm_create() failed with err %d\n",
			      __func__, ret);
		जाओ err_निकास;
	पूर्ण

	spin_lock_init(&itvsc->slock);

	snd_pcm_set_ops(sp, SNDRV_PCM_STREAM_CAPTURE,
			&snd_ivtv_pcm_capture_ops);
	snd_pcm_set_managed_buffer_all(sp, SNDRV_DMA_TYPE_VMALLOC, शून्य, 0, 0);
	sp->info_flags = 0;
	sp->निजी_data = itvsc;
	strscpy(sp->name, itv->card_name, माप(sp->name));

	वापस 0;

err_निकास:
	वापस ret;
पूर्ण
