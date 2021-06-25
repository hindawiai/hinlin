<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja <ola.o.lilja@stericsson.com>,
 *         Roger Nilsson <roger.xr.nilsson@stericsson.com>
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */

#समावेश <यंत्र/page.h>

#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/slab.h>
#समावेश <linux/platक्रमm_data/dma-ste-dma40.h>

#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "ux500_msp_i2s.h"
#समावेश "ux500_pcm.h"

#घोषणा UX500_PLATFORM_PERIODS_BYTES_MIN	128
#घोषणा UX500_PLATFORM_PERIODS_BYTES_MAX	(64 * PAGE_SIZE)
#घोषणा UX500_PLATFORM_PERIODS_MIN		2
#घोषणा UX500_PLATFORM_PERIODS_MAX		48
#घोषणा UX500_PLATFORM_BUFFER_BYTES_MAX		(2048 * PAGE_SIZE)

अटल स्थिर काष्ठा snd_pcm_hardware ux500_pcm_hw = अणु
	.info = SNDRV_PCM_INFO_INTERLEAVED |
		SNDRV_PCM_INFO_MMAP |
		SNDRV_PCM_INFO_RESUME |
		SNDRV_PCM_INFO_PAUSE,
	.buffer_bytes_max = UX500_PLATFORM_BUFFER_BYTES_MAX,
	.period_bytes_min = UX500_PLATFORM_PERIODS_BYTES_MIN,
	.period_bytes_max = UX500_PLATFORM_PERIODS_BYTES_MAX,
	.periods_min = UX500_PLATFORM_PERIODS_MIN,
	.periods_max = UX500_PLATFORM_PERIODS_MAX,
पूर्ण;

अटल काष्ठा dma_chan *ux500_pcm_request_chan(काष्ठा snd_soc_pcm_runसमय *rtd,
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_cpu(rtd, 0);
	u16 per_data_width, mem_data_width;
	काष्ठा stedma40_chan_cfg *dma_cfg;
	काष्ठा ux500_msp_dma_params *dma_params;

	dma_params = snd_soc_dai_get_dma_data(dai, substream);
	dma_cfg = dma_params->dma_cfg;

	mem_data_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	चयन (dma_params->data_size) अणु
	हाल 32:
		per_data_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		अवरोध;
	हाल 16:
		per_data_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
		अवरोध;
	हाल 8:
		per_data_width = DMA_SLAVE_BUSWIDTH_1_BYTE;
		अवरोध;
	शेष:
		per_data_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		dma_cfg->src_info.data_width = mem_data_width;
		dma_cfg->dst_info.data_width = per_data_width;
	पूर्ण अन्यथा अणु
		dma_cfg->src_info.data_width = per_data_width;
		dma_cfg->dst_info.data_width = mem_data_width;
	पूर्ण

	वापस snd_dmaengine_pcm_request_channel(stedma40_filter, dma_cfg);
पूर्ण

अटल पूर्णांक ux500_pcm_prepare_slave_config(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params,
		काष्ठा dma_slave_config *slave_config)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा msp_i2s_platक्रमm_data *pdata = asoc_rtd_to_cpu(rtd, 0)->dev->platक्रमm_data;
	काष्ठा snd_dmaengine_dai_dma_data *snd_dma_params;
	काष्ठा ux500_msp_dma_params *ste_dma_params;
	dma_addr_t dma_addr;
	पूर्णांक ret;

	अगर (pdata) अणु
		ste_dma_params =
			snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
		dma_addr = ste_dma_params->tx_rx_addr;
	पूर्ण अन्यथा अणु
		snd_dma_params =
			snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
		dma_addr = snd_dma_params->addr;
	पूर्ण

	ret = snd_hwparams_to_dma_slave_config(substream, params, slave_config);
	अगर (ret)
		वापस ret;

	slave_config->dst_maxburst = 4;
	slave_config->src_maxburst = 4;

	slave_config->src_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;
	slave_config->dst_addr_width = DMA_SLAVE_BUSWIDTH_2_BYTES;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		slave_config->dst_addr = dma_addr;
	अन्यथा
		slave_config->src_addr = dma_addr;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_dmaengine_pcm_config ux500_dmaengine_pcm_config = अणु
	.pcm_hardware = &ux500_pcm_hw,
	.compat_request_channel = ux500_pcm_request_chan,
	.pपुनः_स्मृति_buffer_size = 128 * 1024,
	.prepare_slave_config = ux500_pcm_prepare_slave_config,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config ux500_dmaengine_of_pcm_config = अणु
	.compat_request_channel = ux500_pcm_request_chan,
	.prepare_slave_config = ux500_pcm_prepare_slave_config,
पूर्ण;

पूर्णांक ux500_pcm_रेजिस्टर_platक्रमm(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा snd_dmaengine_pcm_config *pcm_config;
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	अगर (np)
		pcm_config = &ux500_dmaengine_of_pcm_config;
	अन्यथा
		pcm_config = &ux500_dmaengine_pcm_config;

	ret = snd_dmaengine_pcm_रेजिस्टर(&pdev->dev, pcm_config,
					 SND_DMAENGINE_PCM_FLAG_COMPAT);
	अगर (ret < 0) अणु
		dev_err(&pdev->dev,
			"%s: ERROR: Failed to register platform '%s' (%d)!\n",
			__func__, pdev->name, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ux500_pcm_रेजिस्टर_platक्रमm);

पूर्णांक ux500_pcm_unरेजिस्टर_platक्रमm(काष्ठा platक्रमm_device *pdev)
अणु
	snd_dmaengine_pcm_unरेजिस्टर(&pdev->dev);
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(ux500_pcm_unरेजिस्टर_platक्रमm);

MODULE_AUTHOR("Ola Lilja");
MODULE_AUTHOR("Roger Nilsson");
MODULE_DESCRIPTION("ASoC UX500 driver");
MODULE_LICENSE("GPL v2");
