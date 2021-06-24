<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
// imx-pcm-fiq.c  --  ALSA Soc Audio Layer
//
// Copyright 2009 Sascha Hauer <s.hauer@pengutronix.de>
//
// This code is based on code copyrighted by Freescale,
// Liam Girdwood, Javier Martin and probably others.

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>
#समावेश <linux/device.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <sound/core.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश <sound/initval.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/fiq.h>

#समावेश <linux/platक्रमm_data/asoc-imx-ssi.h>

#समावेश "imx-ssi.h"
#समावेश "imx-pcm.h"

काष्ठा imx_pcm_runसमय_data अणु
	अचिन्हित पूर्णांक period;
	पूर्णांक periods;
	अचिन्हित दीर्घ offset;
	काष्ठा hrसमयr hrt;
	पूर्णांक poll_समय_ns;
	काष्ठा snd_pcm_substream *substream;
	atomic_t playing;
	atomic_t capturing;
पूर्ण;

अटल क्रमागत hrसमयr_restart snd_hrसमयr_callback(काष्ठा hrसमयr *hrt)
अणु
	काष्ठा imx_pcm_runसमय_data *iprtd =
		container_of(hrt, काष्ठा imx_pcm_runसमय_data, hrt);
	काष्ठा snd_pcm_substream *substream = iprtd->substream;
	काष्ठा pt_regs regs;

	अगर (!atomic_पढ़ो(&iprtd->playing) && !atomic_पढ़ो(&iprtd->capturing))
		वापस HRTIMER_NORESTART;

	get_fiq_regs(&regs);

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		iprtd->offset = regs.ARM_r8 & 0xffff;
	अन्यथा
		iprtd->offset = regs.ARM_r9 & 0xffff;

	snd_pcm_period_elapsed(substream);

	hrसमयr_क्रमward_now(hrt, ns_to_kसमय(iprtd->poll_समय_ns));

	वापस HRTIMER_RESTART;
पूर्ण

अटल काष्ठा fiq_handler fh = अणु
	.name		= DRV_NAME,
पूर्ण;

अटल पूर्णांक snd_imx_pcm_hw_params(काष्ठा snd_soc_component *component,
				 काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा imx_pcm_runसमय_data *iprtd = runसमय->निजी_data;

	iprtd->periods = params_periods(params);
	iprtd->period = params_period_bytes(params);
	iprtd->offset = 0;
	iprtd->poll_समय_ns = 1000000000 / params_rate(params) *
				params_period_size(params);
	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_imx_pcm_prepare(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा imx_pcm_runसमय_data *iprtd = runसमय->निजी_data;
	काष्ठा pt_regs regs;

	get_fiq_regs(&regs);
	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		regs.ARM_r8 = (iprtd->period * iprtd->periods - 1) << 16;
	अन्यथा
		regs.ARM_r9 = (iprtd->period * iprtd->periods - 1) << 16;

	set_fiq_regs(&regs);

	वापस 0;
पूर्ण

अटल पूर्णांक imx_pcm_fiq;

अटल पूर्णांक snd_imx_pcm_trigger(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा imx_pcm_runसमय_data *iprtd = runसमय->निजी_data;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			atomic_set(&iprtd->playing, 1);
		अन्यथा
			atomic_set(&iprtd->capturing, 1);
		hrसमयr_start(&iprtd->hrt, ns_to_kसमय(iprtd->poll_समय_ns),
		      HRTIMER_MODE_REL);
		enable_fiq(imx_pcm_fiq);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
			atomic_set(&iprtd->playing, 0);
		अन्यथा
			atomic_set(&iprtd->capturing, 0);
		अगर (!atomic_पढ़ो(&iprtd->playing) &&
				!atomic_पढ़ो(&iprtd->capturing))
			disable_fiq(imx_pcm_fiq);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल snd_pcm_uframes_t
snd_imx_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
		    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा imx_pcm_runसमय_data *iprtd = runसमय->निजी_data;

	वापस bytes_to_frames(substream->runसमय, iprtd->offset);
पूर्ण

अटल स्थिर काष्ठा snd_pcm_hardware snd_imx_hardware = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_BLOCK_TRANSFER |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_MMAP_VALID |
		SNDRV_PCM_INFO_PAUSE |
		SNDRV_PCM_INFO_RESUME,
	.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE,
	.buffer_bytes_max = IMX_SSI_DMABUF_SIZE,
	.period_bytes_min = 128,
	.period_bytes_max = 16 * 1024,
	.periods_min = 4,
	.periods_max = 255,
	.fअगरo_size = 0,
पूर्ण;

अटल पूर्णांक snd_imx_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा imx_pcm_runसमय_data *iprtd;
	पूर्णांक ret;

	iprtd = kzalloc(माप(*iprtd), GFP_KERNEL);
	अगर (iprtd == शून्य)
		वापस -ENOMEM;
	runसमय->निजी_data = iprtd;

	iprtd->substream = substream;

	atomic_set(&iprtd->playing, 0);
	atomic_set(&iprtd->capturing, 0);
	hrसमयr_init(&iprtd->hrt, CLOCK_MONOTONIC, HRTIMER_MODE_REL);
	iprtd->hrt.function = snd_hrसमयr_callback;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(substream->runसमय,
			SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0) अणु
		kमुक्त(iprtd);
		वापस ret;
	पूर्ण

	snd_soc_set_runसमय_hwparams(substream, &snd_imx_hardware);
	वापस 0;
पूर्ण

अटल पूर्णांक snd_imx_बंद(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा imx_pcm_runसमय_data *iprtd = runसमय->निजी_data;

	hrसमयr_cancel(&iprtd->hrt);

	kमुक्त(iprtd);

	वापस 0;
पूर्ण

अटल पूर्णांक snd_imx_pcm_mmap(काष्ठा snd_soc_component *component,
			    काष्ठा snd_pcm_substream *substream,
			    काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret;

	ret = dma_mmap_wc(substream->pcm->card->dev, vma, runसमय->dma_area,
			  runसमय->dma_addr, runसमय->dma_bytes);

	pr_debug("%s: ret: %d %p %pad 0x%08zx\n", __func__, ret,
			runसमय->dma_area,
			&runसमय->dma_addr,
			runसमय->dma_bytes);
	वापस ret;
पूर्ण

अटल पूर्णांक imx_pcm_pपुनः_स्मृतिate_dma_buffer(काष्ठा snd_pcm *pcm, पूर्णांक stream)
अणु
	काष्ठा snd_pcm_substream *substream = pcm->streams[stream].substream;
	काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;
	माप_प्रकार size = IMX_SSI_DMABUF_SIZE;

	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->निजी_data = शून्य;
	buf->area = dma_alloc_wc(pcm->card->dev, size, &buf->addr, GFP_KERNEL);
	अगर (!buf->area)
		वापस -ENOMEM;
	buf->bytes = size;

	वापस 0;
पूर्ण

अटल पूर्णांक imx_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) अणु
		ret = imx_pcm_pपुनः_स्मृतिate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_PLAYBACK);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) अणु
		ret = imx_pcm_pपुनः_स्मृतिate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_CAPTURE);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ssi_irq;

अटल पूर्णांक snd_imx_pcm_new(काष्ठा snd_soc_component *component,
			   काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_pcm *pcm = rtd->pcm;
	काष्ठा snd_pcm_substream *substream;
	पूर्णांक ret;

	ret = imx_pcm_new(rtd);
	अगर (ret)
		वापस ret;

	substream = pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream;
	अगर (substream) अणु
		काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;

		imx_ssi_fiq_tx_buffer = (अचिन्हित दीर्घ)buf->area;
	पूर्ण

	substream = pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream;
	अगर (substream) अणु
		काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;

		imx_ssi_fiq_rx_buffer = (अचिन्हित दीर्घ)buf->area;
	पूर्ण

	set_fiq_handler(&imx_ssi_fiq_start,
		&imx_ssi_fiq_end - &imx_ssi_fiq_start);

	वापस 0;
पूर्ण

अटल व्योम imx_pcm_मुक्त(काष्ठा snd_pcm *pcm)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_dma_buffer *buf;
	पूर्णांक stream;

	क्रम (stream = 0; stream < 2; stream++) अणु
		substream = pcm->streams[stream].substream;
		अगर (!substream)
			जारी;

		buf = &substream->dma_buffer;
		अगर (!buf->area)
			जारी;

		dma_मुक्त_wc(pcm->card->dev, buf->bytes, buf->area, buf->addr);
		buf->area = शून्य;
	पूर्ण
पूर्ण

अटल व्योम snd_imx_pcm_मुक्त(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm *pcm)
अणु
	mxc_set_irq_fiq(ssi_irq, 0);
	release_fiq(&fh);
	imx_pcm_मुक्त(pcm);
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver imx_soc_component_fiq = अणु
	.खोलो		= snd_imx_खोलो,
	.बंद		= snd_imx_बंद,
	.hw_params	= snd_imx_pcm_hw_params,
	.prepare	= snd_imx_pcm_prepare,
	.trigger	= snd_imx_pcm_trigger,
	.poपूर्णांकer	= snd_imx_pcm_poपूर्णांकer,
	.mmap		= snd_imx_pcm_mmap,
	.pcm_स्थिरruct	= snd_imx_pcm_new,
	.pcm_deकाष्ठा	= snd_imx_pcm_मुक्त,
पूर्ण;

पूर्णांक imx_pcm_fiq_init(काष्ठा platक्रमm_device *pdev,
		काष्ठा imx_pcm_fiq_params *params)
अणु
	पूर्णांक ret;

	ret = claim_fiq(&fh);
	अगर (ret) अणु
		dev_err(&pdev->dev, "failed to claim fiq: %d", ret);
		वापस ret;
	पूर्ण

	mxc_set_irq_fiq(params->irq, 1);
	ssi_irq = params->irq;

	imx_pcm_fiq = params->irq;

	imx_ssi_fiq_base = (अचिन्हित दीर्घ)params->base;

	params->dma_params_tx->maxburst = 4;
	params->dma_params_rx->maxburst = 6;

	ret = devm_snd_soc_रेजिस्टर_component(&pdev->dev, &imx_soc_component_fiq,
					      शून्य, 0);
	अगर (ret)
		जाओ failed_रेजिस्टर;

	वापस 0;

failed_रेजिस्टर:
	mxc_set_irq_fiq(ssi_irq, 0);
	release_fiq(&fh);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(imx_pcm_fiq_init);

व्योम imx_pcm_fiq_निकास(काष्ठा platक्रमm_device *pdev)
अणु
पूर्ण
EXPORT_SYMBOL_GPL(imx_pcm_fiq_निकास);

MODULE_LICENSE("GPL");
