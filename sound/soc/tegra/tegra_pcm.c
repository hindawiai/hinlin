<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra_pcm.c - Tegra PCM driver
 *
 * Author: Stephen Warren <swarren@nvidia.com>
 * Copyright (C) 2010,2012 - NVIDIA, Inc.
 *
 * Based on code copyright/by:
 *
 * Copyright (c) 2009-2010, NVIDIA Corporation.
 * Scott Peterson <speterson@nvidia.com>
 * Vijay Mali <vmali@nvidia.com>
 *
 * Copyright (C) 2010 Google, Inc.
 * Iliyan Malchev <malchev@google.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/dmaengine_pcm.h>
#समावेश "tegra_pcm.h"

अटल स्थिर काष्ठा snd_pcm_hardware tegra_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED,
	.period_bytes_min	= 1024,
	.period_bytes_max	= PAGE_SIZE,
	.periods_min		= 2,
	.periods_max		= 8,
	.buffer_bytes_max	= PAGE_SIZE * 8,
	.fअगरo_size		= 4,
पूर्ण;

अटल स्थिर काष्ठा snd_dmaengine_pcm_config tegra_dmaengine_pcm_config = अणु
	.pcm_hardware = &tegra_pcm_hardware,
	.prepare_slave_config = snd_dmaengine_pcm_prepare_slave_config,
	.pपुनः_स्मृति_buffer_size = PAGE_SIZE * 8,
पूर्ण;

पूर्णांक tegra_pcm_platक्रमm_रेजिस्टर(काष्ठा device *dev)
अणु
	वापस snd_dmaengine_pcm_रेजिस्टर(dev, &tegra_dmaengine_pcm_config, 0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_platक्रमm_रेजिस्टर);

पूर्णांक tegra_pcm_platक्रमm_रेजिस्टर_with_chan_names(काष्ठा device *dev,
				काष्ठा snd_dmaengine_pcm_config *config,
				अक्षर *txdmachan, अक्षर *rxdmachan)
अणु
	*config = tegra_dmaengine_pcm_config;
	config->dma_dev = dev->parent;
	config->chan_names[0] = txdmachan;
	config->chan_names[1] = rxdmachan;

	वापस snd_dmaengine_pcm_रेजिस्टर(dev, config, 0);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_platक्रमm_रेजिस्टर_with_chan_names);

व्योम tegra_pcm_platक्रमm_unरेजिस्टर(काष्ठा device *dev)
अणु
	वापस snd_dmaengine_pcm_unरेजिस्टर(dev);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_platक्रमm_unरेजिस्टर);

पूर्णांक tegra_pcm_खोलो(काष्ठा snd_soc_component *component,
		   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_dmaengine_dai_dma_data *dmap;
	काष्ठा dma_chan *chan;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	पूर्णांक ret;

	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	dmap = snd_soc_dai_get_dma_data(cpu_dai, substream);

	/* Set HW params now that initialization is complete */
	snd_soc_set_runसमय_hwparams(substream, &tegra_pcm_hardware);

	/* Ensure period size is multiple of 8 */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 0x8);
	अगर (ret) अणु
		dev_err(rtd->dev, "failed to set constraint %d\n", ret);
		वापस ret;
	पूर्ण

	chan = dma_request_slave_channel(cpu_dai->dev, dmap->chan_name);
	अगर (!chan) अणु
		dev_err(cpu_dai->dev,
			"dmaengine request slave channel failed! (%s)\n",
			dmap->chan_name);
		वापस -ENODEV;
	पूर्ण

	ret = snd_dmaengine_pcm_खोलो(substream, chan);
	अगर (ret) अणु
		dev_err(rtd->dev,
			"dmaengine pcm open failed with err %d (%s)\n", ret,
			dmap->chan_name);

		dma_release_channel(chan);

		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_खोलो);

पूर्णांक tegra_pcm_बंद(काष्ठा snd_soc_component *component,
		    काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;

	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	snd_dmaengine_pcm_बंद_release_chan(substream);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_बंद);

पूर्णांक tegra_pcm_hw_params(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream,
			काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_dmaengine_dai_dma_data *dmap;
	काष्ठा dma_slave_config slave_config;
	काष्ठा dma_chan *chan;
	पूर्णांक ret;

	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	dmap = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	अगर (!dmap)
		वापस 0;

	chan = snd_dmaengine_pcm_get_chan(substream);

	ret = snd_hwparams_to_dma_slave_config(substream, params,
					       &slave_config);
	अगर (ret) अणु
		dev_err(rtd->dev, "hw params config failed with err %d\n", ret);
		वापस ret;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		slave_config.dst_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		slave_config.dst_addr = dmap->addr;
		slave_config.dst_maxburst = 8;
	पूर्ण अन्यथा अणु
		slave_config.src_addr_width = DMA_SLAVE_BUSWIDTH_4_BYTES;
		slave_config.src_addr = dmap->addr;
		slave_config.src_maxburst = 8;
	पूर्ण

	ret = dmaengine_slave_config(chan, &slave_config);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "dma slave config failed with err %d\n", ret);
		वापस ret;
	पूर्ण

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_hw_params);

पूर्णांक tegra_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
		      काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;

	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	snd_pcm_set_runसमय_buffer(substream, शून्य);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_hw_मुक्त);

पूर्णांक tegra_pcm_mmap(काष्ठा snd_soc_component *component,
		   काष्ठा snd_pcm_substream *substream,
		   काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	अगर (rtd->dai_link->no_pcm)
		वापस 0;

	वापस dma_mmap_wc(substream->pcm->card->dev, vma, runसमय->dma_area,
			   runसमय->dma_addr, runसमय->dma_bytes);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_mmap);

snd_pcm_uframes_t tegra_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
				    काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_dmaengine_pcm_poपूर्णांकer(substream);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_poपूर्णांकer);

अटल पूर्णांक tegra_pcm_pपुनः_स्मृतिate_dma_buffer(काष्ठा snd_pcm *pcm, पूर्णांक stream,
					    माप_प्रकार size)
अणु
	काष्ठा snd_pcm_substream *substream = pcm->streams[stream].substream;
	काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;

	buf->area = dma_alloc_wc(pcm->card->dev, size, &buf->addr, GFP_KERNEL);
	अगर (!buf->area)
		वापस -ENOMEM;

	buf->निजी_data = शून्य;
	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->bytes = size;

	वापस 0;
पूर्ण

अटल व्योम tegra_pcm_deallocate_dma_buffer(काष्ठा snd_pcm *pcm, पूर्णांक stream)
अणु
	काष्ठा snd_pcm_substream *substream;
	काष्ठा snd_dma_buffer *buf;

	substream = pcm->streams[stream].substream;
	अगर (!substream)
		वापस;

	buf = &substream->dma_buffer;
	अगर (!buf->area)
		वापस;

	dma_मुक्त_wc(pcm->card->dev, buf->bytes, buf->area, buf->addr);
	buf->area = शून्य;
पूर्ण

अटल पूर्णांक tegra_pcm_dma_allocate(काष्ठा snd_soc_pcm_runसमय *rtd,
				  माप_प्रकार size)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	पूर्णांक ret;

	ret = dma_set_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret < 0)
		वापस ret;

	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) अणु
		ret = tegra_pcm_pपुनः_स्मृतिate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_PLAYBACK, size);
		अगर (ret)
			जाओ err;
	पूर्ण

	अगर (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) अणु
		ret = tegra_pcm_pपुनः_स्मृतिate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_CAPTURE, size);
		अगर (ret)
			जाओ err_मुक्त_play;
	पूर्ण

	वापस 0;

err_मुक्त_play:
	tegra_pcm_deallocate_dma_buffer(pcm, SNDRV_PCM_STREAM_PLAYBACK);
err:
	वापस ret;
पूर्ण

पूर्णांक tegra_pcm_स्थिरruct(काष्ठा snd_soc_component *component,
			काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस tegra_pcm_dma_allocate(rtd, tegra_pcm_hardware.buffer_bytes_max);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_स्थिरruct);

व्योम tegra_pcm_deकाष्ठा(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm *pcm)
अणु
	tegra_pcm_deallocate_dma_buffer(pcm, SNDRV_PCM_STREAM_CAPTURE);
	tegra_pcm_deallocate_dma_buffer(pcm, SNDRV_PCM_STREAM_PLAYBACK);
पूर्ण
EXPORT_SYMBOL_GPL(tegra_pcm_deकाष्ठा);

MODULE_AUTHOR("Stephen Warren <swarren@nvidia.com>");
MODULE_DESCRIPTION("Tegra PCM ASoC driver");
MODULE_LICENSE("GPL");
