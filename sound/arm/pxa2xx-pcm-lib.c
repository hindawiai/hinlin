<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only

#समावेश <linux/slab.h>
#समावेश <linux/module.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/dmaengine.h>
#समावेश <linux/dma/pxa-dma.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/pxa2xx-lib.h>
#समावेश <sound/dmaengine_pcm.h>

अटल स्थिर काष्ठा snd_pcm_hardware pxa2xx_pcm_hardware = अणु
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_PAUSE |
				  SNDRV_PCM_INFO_RESUME,
	.क्रमmats		= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S24_LE |
				  SNDRV_PCM_FMTBIT_S32_LE,
	.period_bytes_min	= 32,
	.period_bytes_max	= 8192 - 32,
	.periods_min		= 1,
	.periods_max		= 256,
	.buffer_bytes_max	= 128 * 1024,
	.fअगरo_size		= 32,
पूर्ण;

पूर्णांक pxa2xx_pcm_hw_params(काष्ठा snd_pcm_substream *substream,
			 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा dma_chan *chan = snd_dmaengine_pcm_get_chan(substream);
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_dmaengine_dai_dma_data *dma_params;
	काष्ठा dma_slave_config config;
	पूर्णांक ret;

	dma_params = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	अगर (!dma_params)
		वापस 0;

	ret = snd_hwparams_to_dma_slave_config(substream, params, &config);
	अगर (ret)
		वापस ret;

	snd_dmaengine_pcm_set_config_from_dai_data(substream,
			snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream),
			&config);

	ret = dmaengine_slave_config(chan, &config);
	अगर (ret)
		वापस ret;

	snd_pcm_set_runसमय_buffer(substream, &substream->dma_buffer);

	वापस 0;
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_hw_params);

पूर्णांक pxa2xx_pcm_hw_मुक्त(काष्ठा snd_pcm_substream *substream)
अणु
	snd_pcm_set_runसमय_buffer(substream, शून्य);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_hw_मुक्त);

पूर्णांक pxa2xx_pcm_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	वापस snd_dmaengine_pcm_trigger(substream, cmd);
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_trigger);

snd_pcm_uframes_t
pxa2xx_pcm_poपूर्णांकer(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_dmaengine_pcm_poपूर्णांकer(substream);
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_poपूर्णांकer);

पूर्णांक pxa2xx_pcm_prepare(काष्ठा snd_pcm_substream *substream)
अणु
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_prepare);

पूर्णांक pxa2xx_pcm_खोलो(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = substream->निजी_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_dmaengine_dai_dma_data *dma_params;
	पूर्णांक ret;

	runसमय->hw = pxa2xx_pcm_hardware;

	dma_params = snd_soc_dai_get_dma_data(asoc_rtd_to_cpu(rtd, 0), substream);
	अगर (!dma_params)
		वापस 0;

	/*
	 * For mysterious reasons (and despite what the manual says)
	 * playback samples are lost अगर the DMA count is not a multiple
	 * of the DMA burst size.  Let's add a rule to enक्रमce that.
	 */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
		SNDRV_PCM_HW_PARAM_PERIOD_BYTES, 32);
	अगर (ret)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(runसमय, 0,
		SNDRV_PCM_HW_PARAM_BUFFER_BYTES, 32);
	अगर (ret)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_पूर्णांकeger(runसमय,
					    SNDRV_PCM_HW_PARAM_PERIODS);
	अगर (ret < 0)
		वापस ret;

	वापस snd_dmaengine_pcm_खोलो(
		substream, dma_request_slave_channel(asoc_rtd_to_cpu(rtd, 0)->dev,
						     dma_params->chan_name));
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_खोलो);

पूर्णांक pxa2xx_pcm_बंद(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_dmaengine_pcm_बंद_release_chan(substream);
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_बंद);

पूर्णांक pxa2xx_pcm_mmap(काष्ठा snd_pcm_substream *substream,
	काष्ठा vm_area_काष्ठा *vma)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	वापस dma_mmap_wc(substream->pcm->card->dev, vma, runसमय->dma_area,
			   runसमय->dma_addr, runसमय->dma_bytes);
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_mmap);

पूर्णांक pxa2xx_pcm_pपुनः_स्मृतिate_dma_buffer(काष्ठा snd_pcm *pcm, पूर्णांक stream)
अणु
	काष्ठा snd_pcm_substream *substream = pcm->streams[stream].substream;
	काष्ठा snd_dma_buffer *buf = &substream->dma_buffer;
	माप_प्रकार size = pxa2xx_pcm_hardware.buffer_bytes_max;
	buf->dev.type = SNDRV_DMA_TYPE_DEV;
	buf->dev.dev = pcm->card->dev;
	buf->निजी_data = शून्य;
	buf->area = dma_alloc_wc(pcm->card->dev, size, &buf->addr, GFP_KERNEL);
	अगर (!buf->area)
		वापस -ENOMEM;
	buf->bytes = size;
	वापस 0;
पूर्ण
EXPORT_SYMBOL(pxa2xx_pcm_pपुनः_स्मृतिate_dma_buffer);

व्योम pxa2xx_pcm_मुक्त_dma_buffers(काष्ठा snd_pcm *pcm)
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
EXPORT_SYMBOL(pxa2xx_pcm_मुक्त_dma_buffers);

व्योम pxa2xx_soc_pcm_मुक्त(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm *pcm)
अणु
	pxa2xx_pcm_मुक्त_dma_buffers(pcm);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_मुक्त);

पूर्णांक pxa2xx_soc_pcm_new(काष्ठा snd_soc_component *component,
		       काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा snd_pcm *pcm = rtd->pcm;
	पूर्णांक ret;

	ret = dma_coerce_mask_and_coherent(card->dev, DMA_BIT_MASK(32));
	अगर (ret)
		वापस ret;

	अगर (pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream) अणु
		ret = pxa2xx_pcm_pपुनः_स्मृतिate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_PLAYBACK);
		अगर (ret)
			जाओ out;
	पूर्ण

	अगर (pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream) अणु
		ret = pxa2xx_pcm_pपुनः_स्मृतिate_dma_buffer(pcm,
			SNDRV_PCM_STREAM_CAPTURE);
		अगर (ret)
			जाओ out;
	पूर्ण
 out:
	वापस ret;
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_new);

पूर्णांक pxa2xx_soc_pcm_खोलो(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream)
अणु
	वापस pxa2xx_pcm_खोलो(substream);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_खोलो);

पूर्णांक pxa2xx_soc_pcm_बंद(काष्ठा snd_soc_component *component,
			 काष्ठा snd_pcm_substream *substream)
अणु
	वापस pxa2xx_pcm_बंद(substream);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_बंद);

पूर्णांक pxa2xx_soc_pcm_hw_params(काष्ठा snd_soc_component *component,
			     काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	वापस pxa2xx_pcm_hw_params(substream, params);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_hw_params);

पूर्णांक pxa2xx_soc_pcm_hw_मुक्त(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	वापस pxa2xx_pcm_hw_मुक्त(substream);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_hw_मुक्त);

पूर्णांक pxa2xx_soc_pcm_prepare(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream)
अणु
	वापस pxa2xx_pcm_prepare(substream);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_prepare);

पूर्णांक pxa2xx_soc_pcm_trigger(काष्ठा snd_soc_component *component,
			   काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	वापस pxa2xx_pcm_trigger(substream, cmd);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_trigger);

snd_pcm_uframes_t
pxa2xx_soc_pcm_poपूर्णांकer(काष्ठा snd_soc_component *component,
		       काष्ठा snd_pcm_substream *substream)
अणु
	वापस pxa2xx_pcm_poपूर्णांकer(substream);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_poपूर्णांकer);

पूर्णांक pxa2xx_soc_pcm_mmap(काष्ठा snd_soc_component *component,
			काष्ठा snd_pcm_substream *substream,
			काष्ठा vm_area_काष्ठा *vma)
अणु
	वापस pxa2xx_pcm_mmap(substream, vma);
पूर्ण
EXPORT_SYMBOL(pxa2xx_soc_pcm_mmap);

MODULE_AUTHOR("Nicolas Pitre");
MODULE_DESCRIPTION("Intel PXA2xx sound library");
MODULE_LICENSE("GPL");
