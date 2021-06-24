<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * aपंचांगel-pcm.c  --  ALSA PCM पूर्णांकerface क्रम the Aपंचांगel aपंचांगel SoC.
 *
 *  Copyright (C) 2005 SAN People
 *  Copyright (C) 2008 Aपंचांगel
 *
 * Authors: Sedji Gaouaou <sedji.gaouaou@aपंचांगel.com>
 *
 * Based on at91-pcm. by:
 * Frank Mandarino <fmandarino@endrelia.com>
 * Copyright 2006 Endrelia Technologies Inc.
 *
 * Based on pxa2xx-pcm.c by:
 *
 * Author:	Nicolas Pitre
 * Created:	Nov 30, 2004
 * Copyright:	(C) 2004 MontaVista Software, Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/aपंचांगel_pdc.h>
#समावेश <linux/aपंचांगel-ssc.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "atmel-pcm.h"


अटल पूर्णांक aपंचांगel_pcm_new(काष्ठा snd_soc_component *component,
			 काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_DEV,
				       card->dev, ATMEL_SSC_DMABUF_SIZE,
				       ATMEL_SSC_DMABUF_SIZE);

	वापस 0;
पूर्ण

/*--------------------------------------------------------------------------*\
 * Hardware definition
\*--------------------------------------------------------------------------*/
/* TODO: These values were taken from the AT91 platक्रमm driver, check
 *	 them against real values क्रम AT32
 */
अटल स्थिर काष्ठा snd_pcm_hardware aपंचांगel_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_PAUSE,
	.period_bytes_min	= 32,
	.period_bytes_max	= 8192,
	.periods_min		= 2,
	.periods_max		= 1024,
	.buffer_bytes_max	= ATMEL_SSC_DMABUF_SIZE,
पूर्ण;


/*--------------------------------------------------------------------------*\
 * Data types
\*--------------------------------------------------------------------------*/
काष्ठा aपंचांगel_runसमय_data अणु
	काष्ठा aपंचांगel_pcm_dma_params *params;
	dma_addr_t dma_buffer;		/* physical address of dma buffer */
	dma_addr_t dma_buffer_end;	/* first address beyond DMA buffer */
	माप_प्रकार period_size;

	dma_addr_t period_ptr;		/* physical address of next period */
पूर्ण;

/*--------------------------------------------------------------------------*\
 * ISR
\*--------------------------------------------------------------------------*/
अटल व्योम aपंचांगel_pcm_dma_irq(u32 ssc_sr,
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_runसमय_data *prtd = substream->runसमय->निजी_data;
	काष्ठा aपंचांगel_pcm_dma_params *params = prtd->params;
	अटल पूर्णांक count;

	count++;

	अगर (ssc_sr & params->mask->ssc_endbuf) अणु
		pr_warn("atmel-pcm: buffer %s on %s (SSC_SR=%#x, count=%d)\n",
				substream->stream == SNDRV_PCM_STREAM_PLAYBACK
				? "underrun" : "overrun",
				params->name, ssc_sr, count);

		/* re-start the PDC */
		ssc_ग_लिखोx(params->ssc->regs, ATMEL_PDC_PTCR,
			   params->mask->pdc_disable);
		prtd->period_ptr += prtd->period_size;
		अगर (prtd->period_ptr >= prtd->dma_buffer_end)
			prtd->period_ptr = prtd->dma_buffer;

		ssc_ग_लिखोx(params->ssc->regs, params->pdc->xpr,
			   prtd->period_ptr);
		ssc_ग_लिखोx(params->ssc->regs, params->pdc->xcr,
			   prtd->period_size / params->pdc_xfer_size);
		ssc_ग_लिखोx(params->ssc->regs, ATMEL_PDC_PTCR,
			   params->mask->pdc_enable);
	पूर्ण

	अगर (ssc_sr & params->mask->ssc_endx) अणु
		/* Load the PDC next poपूर्णांकer and counter रेजिस्टरs */
		prtd->period_ptr += prtd->period_size;
		अगर (prtd->period_ptr >= prtd->dma_buffer_end)
			prtd->period_ptr = prtd->dma_buffer;

		ssc_ग_लिखोx(params->ssc->regs, params->pdc->xnpr,
			   prtd->period_ptr);
		ssc_ग_लिखोx(params->ssc->regs, params->pdc->xncr,
			   prtd->period_size / params->pdc_xfer_size);
	पूर्ण

	snd_pcm_period_elapsed(substream);
पूर्ण


/*--------------------------------------------------------------------------*\
 * PCM operations
\*--------------------------------------------------------------------------*/
अटल पूर्णांक aपंचांगel_pcm_hw_params(काष्ठा snd_soc_component *component,
			       काष्ठा snd_pcm_substream *substream,
			       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा aपंचांगel_runसमय_data *prtd = runसमय->निजी_data;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);

	/* this may get called several बार by oss emulation
	 * with dअगरferent params */

	prtd->params = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	prtd->params->dma_पूर्णांकr_handler = aपंचांगel_pcm_dma_irq;

	prtd->dma_buffer = runसमय->dma_addr;
	prtd->dma_buffer_end = runसमय->dma_addr + runसमय->dma_bytes;
	prtd->period_size = params_period_bytes(params);

	pr_debug("atmel-pcm: "
		"hw_params: DMA for %s initialized "
		"(dma_bytes=%zu, period_size=%zu)\n",
		prtd->params->name,
		runसमय->dma_bytes,
		prtd->period_size);
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_runसमय_data *prtd = substream->runसमय->निजी_data;
	काष्ठा aपंचांगel_pcm_dma_params *params = prtd->params;

	अगर (params != शून्य) अणु
		ssc_ग_लिखोx(params->ssc->regs, SSC_PDC_PTCR,
			   params->mask->pdc_disable);
		prtd->params->dma_पूर्णांकr_handler = शून्य;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_pcm_prepare(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_runसमय_data *prtd = substream->runसमय->निजी_data;
	काष्ठा aपंचांगel_pcm_dma_params *params = prtd->params;

	ssc_ग_लिखोx(params->ssc->regs, SSC_IDR,
		   params->mask->ssc_endx | params->mask->ssc_endbuf);
	ssc_ग_लिखोx(params->ssc->regs, ATMEL_PDC_PTCR,
		   params->mask->pdc_disable);
	वापस 0;
पूर्ण

अटल पूर्णांक aपंचांगel_pcm_trigger(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_pcm_runसमय *rtd = substream->runसमय;
	काष्ठा aपंचांगel_runसमय_data *prtd = rtd->निजी_data;
	काष्ठा aपंचांगel_pcm_dma_params *params = prtd->params;
	पूर्णांक ret = 0;

	pr_debug("atmel-pcm:buffer_size = %ld,"
		"dma_area = %p, dma_bytes = %zu\n",
		rtd->buffer_size, rtd->dma_area, rtd->dma_bytes);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
		prtd->period_ptr = prtd->dma_buffer;

		ssc_ग_लिखोx(params->ssc->regs, params->pdc->xpr,
			   prtd->period_ptr);
		ssc_ग_लिखोx(params->ssc->regs, params->pdc->xcr,
			   prtd->period_size / params->pdc_xfer_size);

		prtd->period_ptr += prtd->period_size;
		ssc_ग_लिखोx(params->ssc->regs, params->pdc->xnpr,
			   prtd->period_ptr);
		ssc_ग_लिखोx(params->ssc->regs, params->pdc->xncr,
			   prtd->period_size / params->pdc_xfer_size);

		pr_debug("atmel-pcm: trigger: "
			"period_ptr=%lx, xpr=%u, "
			"xcr=%u, xnpr=%u, xncr=%u\n",
			(अचिन्हित दीर्घ)prtd->period_ptr,
			ssc_पढ़ोx(params->ssc->regs, params->pdc->xpr),
			ssc_पढ़ोx(params->ssc->regs, params->pdc->xcr),
			ssc_पढ़ोx(params->ssc->regs, params->pdc->xnpr),
			ssc_पढ़ोx(params->ssc->regs, params->pdc->xncr));

		ssc_ग_लिखोx(params->ssc->regs, SSC_IER,
			   params->mask->ssc_endx | params->mask->ssc_endbuf);
		ssc_ग_लिखोx(params->ssc->regs, SSC_PDC_PTCR,
			   params->mask->pdc_enable);

		pr_debug("sr=%u imr=%u\n",
			ssc_पढ़ोx(params->ssc->regs, SSC_SR),
			ssc_पढ़ोx(params->ssc->regs, SSC_IER));
		अवरोध;		/* SNDRV_PCM_TRIGGER_START */

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ssc_ग_लिखोx(params->ssc->regs, ATMEL_PDC_PTCR,
			   params->mask->pdc_disable);
		अवरोध;

	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ssc_ग_लिखोx(params->ssc->regs, ATMEL_PDC_PTCR,
			   params->mask->pdc_enable);
		अवरोध;

	शेष:
		ret = -EINVAL;
	पूर्ण

	वापस ret;
पूर्ण

अटल snd_pcm_uframes_t aपंचांगel_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
					   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा aपंचांगel_runसमय_data *prtd = runसमय->निजी_data;
	काष्ठा aपंचांगel_pcm_dma_params *params = prtd->params;
	dma_addr_t ptr;
	snd_pcm_uframes_t x;

	ptr = (dma_addr_t) ssc_पढ़ोx(params->ssc->regs, params->pdc->xpr);
	x = bytes_to_frames(runसमय, ptr - prtd->dma_buffer);

	अगर (x == runसमय->buffer_size)
		x = 0;

	वापस x;
पूर्ण

अटल पूर्णांक aपंचांगel_pcm_खोलो(काष्ठा snd_soc_component *component,
			  काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा aपंचांगel_runसमय_data *prtd;
	पूर्णांक ret = 0;

	snd_soc_set_runसमय_hwparams(substream, &aपंचांगel_pcm_hardware);

	/* ensure that buffer size is a multiple of period size */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
						SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		जाओ out;

	prtd = kzalloc(माप(काष्ठा aपंचांगel_runसमय_data), GFP_KERNEL);
	अगर (prtd == शून्य) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	runसमय->निजी_data = prtd;

 out:
	वापस ret;
पूर्ण

अटल पूर्णांक aपंचांगel_pcm_बंद(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा aपंचांगel_runसमय_data *prtd = substream->runसमय->निजी_data;

	kमुक्त(prtd);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_component_driver aपंचांगel_soc_platक्रमm = अणु
	.खोलो		= aपंचांगel_pcm_खोलो,
	.बंद		= aपंचांगel_pcm_बंद,
	.hw_params	= aपंचांगel_pcm_hw_params,
	.hw_मुक्त	= aपंचांगel_pcm_hw_मुक्त,
	.prepare	= aपंचांगel_pcm_prepare,
	.trigger	= aपंचांगel_pcm_trigger,
	.poपूर्णांकer	= aपंचांगel_pcm_poपूर्णांकer,
	.pcm_स्थिरruct	= aपंचांगel_pcm_new,
पूर्ण;

पूर्णांक aपंचांगel_pcm_pdc_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस devm_snd_soc_रेजिस्टर_component(dev, &aपंचांगel_soc_platक्रमm,
					       शून्य, 0);
पूर्ण
EXPORT_SYMBOL(aपंचांगel_pcm_pdc_platक्रमm_रेजिस्टर);

MODULE_AUTHOR("Sedji Gaouaou <sedji.gaouaou@atmel.com>");
MODULE_DESCRIPTION("Atmel PCM module");
MODULE_LICENSE("GPL");
