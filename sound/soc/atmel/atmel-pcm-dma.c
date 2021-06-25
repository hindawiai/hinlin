<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * aपंचांगel-pcm-dma.c  --  ALSA PCM DMA support क्रम the Aपंचांगel SoC.
 *
 *  Copyright (C) 2012 Aपंचांगel
 *
 * Author: Bo Shen <voice.shen@aपंचांगel.com>
 *
 * Based on aपंचांगel-pcm by:
 * Sedji Gaouaou <sedji.gaouaou@aपंचांगel.com>
 * Copyright 2008 Aपंचांगel
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/aपंचांगel-ssc.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "atmel-pcm.h"

/*--------------------------------------------------------------------------*\
 * Hardware definition
\*--------------------------------------------------------------------------*/
अटल स्थिर काष्ठा snd_pcm_hardware aपंचांगel_pcm_dma_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_RESUME |
				  SNDRV_PCM_INFO_PAUSE,
	.period_bytes_min	= 256,		/* lighting DMA overhead */
	.period_bytes_max	= 2 * 0xffff,	/* अगर 2 bytes क्रमmat */
	.periods_min		= 8,
	.periods_max		= 1024,		/* no limit */
	.buffer_bytes_max	= 512 * 1024,
पूर्ण;

/*
 * aपंचांगel_pcm_dma_irq: SSC पूर्णांकerrupt handler क्रम DMAENGINE enabled SSC
 *
 * We use DMAENGINE to send/receive data to/from SSC so this ISR is only to
 * check अगर any overrun occured.
 */
अटल व्योम aपंचांगel_pcm_dma_irq(u32 ssc_sr,
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_pcm_dma_params *prtd;

	prtd = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);

	अगर (ssc_sr & prtd->mask->ssc_error) अणु
		अगर (snd_pcm_running(substream))
			pr_warn("atmel-pcm: buffer %s on %s (SSC_SR=%#x)\n",
				substream->stream == SNDRV_PCM_STREAM_PLAYBACK
				? "underrun" : "overrun", prtd->name,
				ssc_sr);

		/* stop RX and capture: will be enabled again at restart */
		ssc_ग_लिखोx(prtd->ssc->regs, SSC_CR, prtd->mask->ssc_disable);
		snd_pcm_stop_xrun(substream);

		/* now drain RHR and पढ़ो status to हटाओ xrun condition */
		ssc_पढ़ोx(prtd->ssc->regs, SSC_RHR);
		ssc_पढ़ोx(prtd->ssc->regs, SSC_SR);
	पूर्ण
पूर्ण

अटल पूर्णांक aपंचांगel_pcm_configure_dma(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा dma_slave_config *slave_config)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा aपंचांगel_pcm_dma_params *prtd;
	काष्ठा ssc_device *ssc;
	पूर्णांक ret;

	prtd = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	ssc = prtd->ssc;

	ret = snd_hwparams_to_dma_slave_config(substream, params, slave_config);
	अगर (ret) अणु
		pr_err("atmel-pcm: hwparams to dma slave configure failed\n");
		वापस ret;
	पूर्ण

	slave_config->dst_addr = ssc->phybase + SSC_THR;
	slave_config->dst_maxburst = 1;

	slave_config->src_addr = ssc->phybase + SSC_RHR;
	slave_config->src_maxburst = 1;

	prtd->dma_पूर्णांकr_handler = aपंचांगel_pcm_dma_irq;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config aपंचांगel_dmaengine_pcm_config = अणु
	.prepare_slave_config = aपंचांगel_pcm_configure_dma,
	.pcm_hardware = &aपंचांगel_pcm_dma_hardware,
	.pपुनः_स्मृति_buffer_size = 64 * 1024,
पूर्ण;

पूर्णांक aपंचांगel_pcm_dma_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev,
					&aपंचांगel_dmaengine_pcm_config, 0);
पूर्ण
EXPORT_SYMBOL(aपंचांगel_pcm_dma_platक्रमm_रेजिस्टर);

MODULE_AUTHOR("Bo Shen <voice.shen@atmel.com>");
MODULE_DESCRIPTION("Atmel DMA based PCM module");
MODULE_LICENSE("GPL");
