<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/*
 * u_audio.c -- पूर्णांकerface to USB gadget "ALSA sound card" utilities
 *
 * Copyright (C) 2016
 * Author: Ruslan Bilovol <ruslan.bilovol@gmail.com>
 *
 * Sound card implementation was cut-and-pasted with changes
 * from f_uac2.c and has:
 *    Copyright (C) 2011
 *    Yadwinder Singh (yadi.brar01@gmail.com)
 *    Jaswinder Singh (jaswinder.singh@linaro.org)
 */

#समावेश <linux/module.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>

#समावेश "u_audio.h"

#घोषणा BUFF_SIZE_MAX	(PAGE_SIZE * 16)
#घोषणा PRD_SIZE_MAX	PAGE_SIZE
#घोषणा MIN_PERIODS	4

/* Runसमय data params क्रम one stream */
काष्ठा uac_rtd_params अणु
	काष्ठा snd_uac_chip *uac; /* parent chip */
	bool ep_enabled; /* अगर the ep is enabled */

	काष्ठा snd_pcm_substream *ss;

	/* Ring buffer */
	sमाप_प्रकार hw_ptr;

	व्योम *rbuf;

	अचिन्हित पूर्णांक max_psize;	/* MaxPacketSize of endpoपूर्णांक */

	काष्ठा usb_request **reqs;
पूर्ण;

काष्ठा snd_uac_chip अणु
	काष्ठा g_audio *audio_dev;

	काष्ठा uac_rtd_params p_prm;
	काष्ठा uac_rtd_params c_prm;

	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;

	/* समयkeeping क्रम the playback endpoपूर्णांक */
	अचिन्हित पूर्णांक p_पूर्णांकerval;
	अचिन्हित पूर्णांक p_residue;

	/* pre-calculated values क्रम playback iso completion */
	अचिन्हित पूर्णांक p_pktsize;
	अचिन्हित पूर्णांक p_pktsize_residue;
	अचिन्हित पूर्णांक p_framesize;
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hardware uac_pcm_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED | SNDRV_PCM_INFO_BLOCK_TRANSFER
		 | SNDRV_PCM_INFO_MMAP | SNDRV_PCM_INFO_MMAP_VALID
		 | SNDRV_PCM_INFO_PAUSE | SNDRV_PCM_INFO_RESUME,
	.rates = SNDRV_PCM_RATE_CONTINUOUS,
	.periods_max = BUFF_SIZE_MAX / PRD_SIZE_MAX,
	.buffer_bytes_max = BUFF_SIZE_MAX,
	.period_bytes_max = PRD_SIZE_MAX,
	.periods_min = MIN_PERIODS,
पूर्ण;

अटल व्योम u_audio_iso_complete(काष्ठा usb_ep *ep, काष्ठा usb_request *req)
अणु
	अचिन्हित पूर्णांक pending;
	अचिन्हित पूर्णांक hw_ptr;
	पूर्णांक status = req->status;
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_pcm_runसमय *runसमय;
	काष्ठा uac_rtd_params *prm = req->context;
	काष्ठा snd_uac_chip *uac = prm->uac;

	/* i/f shutting करोwn */
	अगर (!prm->ep_enabled) अणु
		usb_ep_मुक्त_request(ep, req);
		वापस;
	पूर्ण

	अगर (req->status == -ESHUTDOWN)
		वापस;

	/*
	 * We can't really करो much about bad xfers.
	 * Afterall, the ISOCH xfers could fail legitimately.
	 */
	अगर (status)
		pr_debug("%s: iso_complete status(%d) %d/%d\n",
			__func__, status, req->actual, req->length);

	substream = prm->ss;

	/* Do nothing अगर ALSA isn't active */
	अगर (!substream)
		जाओ निकास;

	snd_pcm_stream_lock(substream);

	runसमय = substream->runसमय;
	अगर (!runसमय || !snd_pcm_running(substream)) अणु
		snd_pcm_stream_unlock(substream);
		जाओ निकास;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		/*
		 * For each IN packet, take the quotient of the current data
		 * rate and the endpoपूर्णांक's पूर्णांकerval as the base packet size.
		 * If there is a residue from this भागision, add it to the
		 * residue accumulator.
		 */
		req->length = uac->p_pktsize;
		uac->p_residue += uac->p_pktsize_residue;

		/*
		 * Whenever there are more bytes in the accumulator than we
		 * need to add one more sample frame, increase this packet's
		 * size and decrease the accumulator.
		 */
		अगर (uac->p_residue / uac->p_पूर्णांकerval >= uac->p_framesize) अणु
			req->length += uac->p_framesize;
			uac->p_residue -= uac->p_framesize *
					   uac->p_पूर्णांकerval;
		पूर्ण

		req->actual = req->length;
	पूर्ण

	hw_ptr = prm->hw_ptr;

	/* Pack USB load in ALSA ring buffer */
	pending = runसमय->dma_bytes - hw_ptr;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		अगर (unlikely(pending < req->actual)) अणु
			स_नकल(req->buf, runसमय->dma_area + hw_ptr, pending);
			स_नकल(req->buf + pending, runसमय->dma_area,
			       req->actual - pending);
		पूर्ण अन्यथा अणु
			स_नकल(req->buf, runसमय->dma_area + hw_ptr,
			       req->actual);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (unlikely(pending < req->actual)) अणु
			स_नकल(runसमय->dma_area + hw_ptr, req->buf, pending);
			स_नकल(runसमय->dma_area, req->buf + pending,
			       req->actual - pending);
		पूर्ण अन्यथा अणु
			स_नकल(runसमय->dma_area + hw_ptr, req->buf,
			       req->actual);
		पूर्ण
	पूर्ण

	/* update hw_ptr after data is copied to memory */
	prm->hw_ptr = (hw_ptr + req->actual) % runसमय->dma_bytes;
	hw_ptr = prm->hw_ptr;
	snd_pcm_stream_unlock(substream);

	अगर ((hw_ptr % snd_pcm_lib_period_bytes(substream)) < req->actual)
		snd_pcm_period_elapsed(substream);

निकास:
	अगर (usb_ep_queue(ep, req, GFP_ATOMIC))
		dev_err(uac->card->dev, "%d Error!\n", __LINE__);
पूर्ण

अटल पूर्णांक uac_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_uac_chip *uac = snd_pcm_substream_chip(substream);
	काष्ठा uac_rtd_params *prm;
	काष्ठा g_audio *audio_dev;
	काष्ठा uac_params *params;
	पूर्णांक err = 0;

	audio_dev = uac->audio_dev;
	params = &audio_dev->params;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		prm = &uac->p_prm;
	अन्यथा
		prm = &uac->c_prm;

	/* Reset */
	prm->hw_ptr = 0;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
		prm->ss = substream;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
		prm->ss = शून्य;
		अवरोध;
	शेष:
		err = -EINVAL;
	पूर्ण

	/* Clear buffer after Play stops */
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK && !prm->ss)
		स_रखो(prm->rbuf, 0, prm->max_psize * params->req_number);

	वापस err;
पूर्ण

अटल snd_pcm_uframes_t uac_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_uac_chip *uac = snd_pcm_substream_chip(substream);
	काष्ठा uac_rtd_params *prm;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		prm = &uac->p_prm;
	अन्यथा
		prm = &uac->c_prm;

	वापस bytes_to_frames(substream->runसमय, prm->hw_ptr);
पूर्ण

अटल u64 uac_sमाप_प्रकारo_fmt(पूर्णांक ssize)
अणु
	u64 ret;

	चयन (ssize) अणु
	हाल 3:
		ret = SNDRV_PCM_FMTBIT_S24_3LE;
		अवरोध;
	हाल 4:
		ret = SNDRV_PCM_FMTBIT_S32_LE;
		अवरोध;
	शेष:
		ret = SNDRV_PCM_FMTBIT_S16_LE;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक uac_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_uac_chip *uac = snd_pcm_substream_chip(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा g_audio *audio_dev;
	काष्ठा uac_params *params;
	पूर्णांक p_ssize, c_ssize;
	पूर्णांक p_srate, c_srate;
	पूर्णांक p_chmask, c_chmask;

	audio_dev = uac->audio_dev;
	params = &audio_dev->params;
	p_ssize = params->p_ssize;
	c_ssize = params->c_ssize;
	p_srate = params->p_srate;
	c_srate = params->c_srate;
	p_chmask = params->p_chmask;
	c_chmask = params->c_chmask;
	uac->p_residue = 0;

	runसमय->hw = uac_pcm_hardware;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		runसमय->hw.rate_min = p_srate;
		runसमय->hw.क्रमmats = uac_sमाप_प्रकारo_fmt(p_ssize);
		runसमय->hw.channels_min = num_channels(p_chmask);
		runसमय->hw.period_bytes_min = 2 * uac->p_prm.max_psize
						/ runसमय->hw.periods_min;
	पूर्ण अन्यथा अणु
		runसमय->hw.rate_min = c_srate;
		runसमय->hw.क्रमmats = uac_sमाप_प्रकारo_fmt(c_ssize);
		runसमय->hw.channels_min = num_channels(c_chmask);
		runसमय->hw.period_bytes_min = 2 * uac->c_prm.max_psize
						/ runसमय->hw.periods_min;
	पूर्ण

	runसमय->hw.rate_max = runसमय->hw.rate_min;
	runसमय->hw.channels_max = runसमय->hw.channels_min;

	snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय, SNDRV_PCM_HW_PARAM_PERIODS);

	वापस 0;
पूर्ण

/* ALSA cries without these function poपूर्णांकers */
अटल पूर्णांक uac_pcm_null(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_pcm_ops uac_pcm_ops = अणु
	.खोलो = uac_pcm_खोलो,
	.बंद = uac_pcm_null,
	.trigger = uac_pcm_trigger,
	.poपूर्णांकer = uac_pcm_poपूर्णांकer,
	.prepare = uac_pcm_null,
पूर्ण;

अटल अंतरभूत व्योम मुक्त_ep(काष्ठा uac_rtd_params *prm, काष्ठा usb_ep *ep)
अणु
	काष्ठा snd_uac_chip *uac = prm->uac;
	काष्ठा g_audio *audio_dev;
	काष्ठा uac_params *params;
	पूर्णांक i;

	अगर (!prm->ep_enabled)
		वापस;

	prm->ep_enabled = false;

	audio_dev = uac->audio_dev;
	params = &audio_dev->params;

	क्रम (i = 0; i < params->req_number; i++) अणु
		अगर (prm->reqs[i]) अणु
			अगर (usb_ep_dequeue(ep, prm->reqs[i]))
				usb_ep_मुक्त_request(ep, prm->reqs[i]);
			/*
			 * If usb_ep_dequeue() cannot successfully dequeue the
			 * request, the request will be मुक्तd by the completion
			 * callback.
			 */

			prm->reqs[i] = शून्य;
		पूर्ण
	पूर्ण

	अगर (usb_ep_disable(ep))
		dev_err(uac->card->dev, "%s:%d Error!\n", __func__, __LINE__);
पूर्ण


पूर्णांक u_audio_start_capture(काष्ठा g_audio *audio_dev)
अणु
	काष्ठा snd_uac_chip *uac = audio_dev->uac;
	काष्ठा usb_gadget *gadget = audio_dev->gadget;
	काष्ठा device *dev = &gadget->dev;
	काष्ठा usb_request *req;
	काष्ठा usb_ep *ep;
	काष्ठा uac_rtd_params *prm;
	काष्ठा uac_params *params = &audio_dev->params;
	पूर्णांक req_len, i;

	ep = audio_dev->out_ep;
	prm = &uac->c_prm;
	config_ep_by_speed(gadget, &audio_dev->func, ep);
	req_len = ep->maxpacket;

	prm->ep_enabled = true;
	usb_ep_enable(ep);

	क्रम (i = 0; i < params->req_number; i++) अणु
		अगर (!prm->reqs[i]) अणु
			req = usb_ep_alloc_request(ep, GFP_ATOMIC);
			अगर (req == शून्य)
				वापस -ENOMEM;

			prm->reqs[i] = req;

			req->zero = 0;
			req->context = prm;
			req->length = req_len;
			req->complete = u_audio_iso_complete;
			req->buf = prm->rbuf + i * ep->maxpacket;
		पूर्ण

		अगर (usb_ep_queue(ep, prm->reqs[i], GFP_ATOMIC))
			dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(u_audio_start_capture);

व्योम u_audio_stop_capture(काष्ठा g_audio *audio_dev)
अणु
	काष्ठा snd_uac_chip *uac = audio_dev->uac;

	मुक्त_ep(&uac->c_prm, audio_dev->out_ep);
पूर्ण
EXPORT_SYMBOL_GPL(u_audio_stop_capture);

पूर्णांक u_audio_start_playback(काष्ठा g_audio *audio_dev)
अणु
	काष्ठा snd_uac_chip *uac = audio_dev->uac;
	काष्ठा usb_gadget *gadget = audio_dev->gadget;
	काष्ठा device *dev = &gadget->dev;
	काष्ठा usb_request *req;
	काष्ठा usb_ep *ep;
	काष्ठा uac_rtd_params *prm;
	काष्ठा uac_params *params = &audio_dev->params;
	अचिन्हित पूर्णांक factor;
	स्थिर काष्ठा usb_endpoपूर्णांक_descriptor *ep_desc;
	पूर्णांक req_len, i;

	ep = audio_dev->in_ep;
	prm = &uac->p_prm;
	config_ep_by_speed(gadget, &audio_dev->func, ep);

	ep_desc = ep->desc;

	/* pre-calculate the playback endpoपूर्णांक's पूर्णांकerval */
	अगर (gadget->speed == USB_SPEED_FULL)
		factor = 1000;
	अन्यथा
		factor = 8000;

	/* pre-compute some values क्रम iso_complete() */
	uac->p_framesize = params->p_ssize *
			    num_channels(params->p_chmask);
	uac->p_पूर्णांकerval = factor / (1 << (ep_desc->bInterval - 1));
	uac->p_pktsize = min_t(अचिन्हित पूर्णांक,
				uac->p_framesize *
					(params->p_srate / uac->p_पूर्णांकerval),
				ep->maxpacket);

	अगर (uac->p_pktsize < ep->maxpacket)
		uac->p_pktsize_residue = uac->p_framesize *
			(params->p_srate % uac->p_पूर्णांकerval);
	अन्यथा
		uac->p_pktsize_residue = 0;

	req_len = uac->p_pktsize;
	uac->p_residue = 0;

	prm->ep_enabled = true;
	usb_ep_enable(ep);

	क्रम (i = 0; i < params->req_number; i++) अणु
		अगर (!prm->reqs[i]) अणु
			req = usb_ep_alloc_request(ep, GFP_ATOMIC);
			अगर (req == शून्य)
				वापस -ENOMEM;

			prm->reqs[i] = req;

			req->zero = 0;
			req->context = prm;
			req->length = req_len;
			req->complete = u_audio_iso_complete;
			req->buf = prm->rbuf + i * ep->maxpacket;
		पूर्ण

		अगर (usb_ep_queue(ep, prm->reqs[i], GFP_ATOMIC))
			dev_err(dev, "%s:%d Error!\n", __func__, __LINE__);
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(u_audio_start_playback);

व्योम u_audio_stop_playback(काष्ठा g_audio *audio_dev)
अणु
	काष्ठा snd_uac_chip *uac = audio_dev->uac;

	मुक्त_ep(&uac->p_prm, audio_dev->in_ep);
पूर्ण
EXPORT_SYMBOL_GPL(u_audio_stop_playback);

पूर्णांक g_audio_setup(काष्ठा g_audio *g_audio, स्थिर अक्षर *pcm_name,
					स्थिर अक्षर *card_name)
अणु
	काष्ठा snd_uac_chip *uac;
	काष्ठा snd_card *card;
	काष्ठा snd_pcm *pcm;
	काष्ठा uac_params *params;
	पूर्णांक p_chmask, c_chmask;
	पूर्णांक err;

	अगर (!g_audio)
		वापस -EINVAL;

	uac = kzalloc(माप(*uac), GFP_KERNEL);
	अगर (!uac)
		वापस -ENOMEM;
	g_audio->uac = uac;
	uac->audio_dev = g_audio;

	params = &g_audio->params;
	p_chmask = params->p_chmask;
	c_chmask = params->c_chmask;

	अगर (c_chmask) अणु
		काष्ठा uac_rtd_params *prm = &uac->c_prm;

		uac->c_prm.uac = uac;
		prm->max_psize = g_audio->out_ep_maxpsize;

		prm->reqs = kसुस्मृति(params->req_number,
				    माप(काष्ठा usb_request *),
				    GFP_KERNEL);
		अगर (!prm->reqs) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		prm->rbuf = kसुस्मृति(params->req_number, prm->max_psize,
				GFP_KERNEL);
		अगर (!prm->rbuf) अणु
			prm->max_psize = 0;
			err = -ENOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण

	अगर (p_chmask) अणु
		काष्ठा uac_rtd_params *prm = &uac->p_prm;

		uac->p_prm.uac = uac;
		prm->max_psize = g_audio->in_ep_maxpsize;

		prm->reqs = kसुस्मृति(params->req_number,
				    माप(काष्ठा usb_request *),
				    GFP_KERNEL);
		अगर (!prm->reqs) अणु
			err = -ENOMEM;
			जाओ fail;
		पूर्ण

		prm->rbuf = kसुस्मृति(params->req_number, prm->max_psize,
				GFP_KERNEL);
		अगर (!prm->rbuf) अणु
			prm->max_psize = 0;
			err = -ENOMEM;
			जाओ fail;
		पूर्ण
	पूर्ण

	/* Choose any slot, with no id */
	err = snd_card_new(&g_audio->gadget->dev,
			-1, शून्य, THIS_MODULE, 0, &card);
	अगर (err < 0)
		जाओ fail;

	uac->card = card;

	/*
	 * Create first PCM device
	 * Create a substream only क्रम non-zero channel streams
	 */
	err = snd_pcm_new(uac->card, pcm_name, 0,
			       p_chmask ? 1 : 0, c_chmask ? 1 : 0, &pcm);
	अगर (err < 0)
		जाओ snd_fail;

	strscpy(pcm->name, pcm_name, माप(pcm->name));
	pcm->निजी_data = uac;
	uac->pcm = pcm;

	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_PLAYBACK, &uac_pcm_ops);
	snd_pcm_set_ops(pcm, SNDRV_PCM_STREAM_CAPTURE, &uac_pcm_ops);

	strscpy(card->driver, card_name, माप(card->driver));
	strscpy(card->लघुname, card_name, माप(card->लघुname));
	प्र_लिखो(card->दीर्घname, "%s %i", card_name, card->dev->id);

	snd_pcm_set_managed_buffer_all(pcm, SNDRV_DMA_TYPE_CONTINUOUS,
				       शून्य, 0, BUFF_SIZE_MAX);

	err = snd_card_रेजिस्टर(card);

	अगर (!err)
		वापस 0;

snd_fail:
	snd_card_मुक्त(card);
fail:
	kमुक्त(uac->p_prm.reqs);
	kमुक्त(uac->c_prm.reqs);
	kमुक्त(uac->p_prm.rbuf);
	kमुक्त(uac->c_prm.rbuf);
	kमुक्त(uac);

	वापस err;
पूर्ण
EXPORT_SYMBOL_GPL(g_audio_setup);

व्योम g_audio_cleanup(काष्ठा g_audio *g_audio)
अणु
	काष्ठा snd_uac_chip *uac;
	काष्ठा snd_card *card;

	अगर (!g_audio || !g_audio->uac)
		वापस;

	uac = g_audio->uac;
	card = uac->card;
	अगर (card)
		snd_card_मुक्त(card);

	kमुक्त(uac->p_prm.reqs);
	kमुक्त(uac->c_prm.reqs);
	kमुक्त(uac->p_prm.rbuf);
	kमुक्त(uac->c_prm.rbuf);
	kमुक्त(uac);
पूर्ण
EXPORT_SYMBOL_GPL(g_audio_cleanup);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("USB gadget \"ALSA sound card\" utilities");
MODULE_AUTHOR("Ruslan Bilovol");
