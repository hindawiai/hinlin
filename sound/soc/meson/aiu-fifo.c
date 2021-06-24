<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "aiu-fifo.h"

#घोषणा AIU_MEM_START	0x00
#घोषणा AIU_MEM_RD	0x04
#घोषणा AIU_MEM_END	0x08
#घोषणा AIU_MEM_MASKS	0x0c
#घोषणा  AIU_MEM_MASK_CH_RD GENMASK(7, 0)
#घोषणा  AIU_MEM_MASK_CH_MEM GENMASK(15, 8)
#घोषणा AIU_MEM_CONTROL	0x10
#घोषणा  AIU_MEM_CONTROL_INIT BIT(0)
#घोषणा  AIU_MEM_CONTROL_FILL_EN BIT(1)
#घोषणा  AIU_MEM_CONTROL_EMPTY_EN BIT(2)

अटल काष्ठा snd_soc_dai *aiu_fअगरo_dai(काष्ठा snd_pcm_substream *ss)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = ss->निजी_data;

	वापस asoc_rtd_to_cpu(rtd, 0);
पूर्ण

snd_pcm_uframes_t aiu_fअगरo_poपूर्णांकer(काष्ठा snd_soc_component *component,
				   काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_dai *dai = aiu_fअगरo_dai(substream);
	काष्ठा aiu_fअगरo *fअगरo = dai->playback_dma_data;
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	अचिन्हित पूर्णांक addr;

	addr = snd_soc_component_पढ़ो(component, fअगरo->mem_offset + AIU_MEM_RD);

	वापस bytes_to_frames(runसमय, addr - (अचिन्हित पूर्णांक)runसमय->dma_addr);
पूर्ण

अटल व्योम aiu_fअगरo_enable(काष्ठा snd_soc_dai *dai, bool enable)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aiu_fअगरo *fअगरo = dai->playback_dma_data;
	अचिन्हित पूर्णांक en_mask = (AIU_MEM_CONTROL_FILL_EN |
				AIU_MEM_CONTROL_EMPTY_EN);

	snd_soc_component_update_bits(component,
				      fअगरo->mem_offset + AIU_MEM_CONTROL,
				      en_mask, enable ? en_mask : 0);
पूर्ण

पूर्णांक aiu_fअगरo_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
		     काष्ठा snd_soc_dai *dai)
अणु
	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		aiu_fअगरo_enable(dai, true);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_STOP:
		aiu_fअगरo_enable(dai, false);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक aiu_fअगरo_prepare(काष्ठा snd_pcm_substream *substream,
		     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aiu_fअगरo *fअगरo = dai->playback_dma_data;

	snd_soc_component_update_bits(component,
				      fअगरo->mem_offset + AIU_MEM_CONTROL,
				      AIU_MEM_CONTROL_INIT,
				      AIU_MEM_CONTROL_INIT);
	snd_soc_component_update_bits(component,
				      fअगरo->mem_offset + AIU_MEM_CONTROL,
				      AIU_MEM_CONTROL_INIT, 0);
	वापस 0;
पूर्ण

पूर्णांक aiu_fअगरo_hw_params(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_pcm_hw_params *params,
		       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aiu_fअगरo *fअगरo = dai->playback_dma_data;
	dma_addr_t end;

	/* Setup the fअगरo boundaries */
	end = runसमय->dma_addr + runसमय->dma_bytes - fअगरo->fअगरo_block;
	snd_soc_component_ग_लिखो(component, fअगरo->mem_offset + AIU_MEM_START,
				runसमय->dma_addr);
	snd_soc_component_ग_लिखो(component, fअगरo->mem_offset + AIU_MEM_RD,
				runसमय->dma_addr);
	snd_soc_component_ग_लिखो(component, fअगरo->mem_offset + AIU_MEM_END,
				end);

	/* Setup the fअगरo to पढ़ो all the memory - no skip */
	snd_soc_component_update_bits(component,
				      fअगरo->mem_offset + AIU_MEM_MASKS,
				      AIU_MEM_MASK_CH_RD | AIU_MEM_MASK_CH_MEM,
				      FIELD_PREP(AIU_MEM_MASK_CH_RD, 0xff) |
				      FIELD_PREP(AIU_MEM_MASK_CH_MEM, 0xff));

	वापस 0;
पूर्ण

अटल irqवापस_t aiu_fअगरo_isr(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा snd_pcm_substream *playback = dev_id;

	snd_pcm_period_elapsed(playback);

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक aiu_fअगरo_startup(काष्ठा snd_pcm_substream *substream,
		     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aiu_fअगरo *fअगरo = dai->playback_dma_data;
	पूर्णांक ret;

	snd_soc_set_runसमय_hwparams(substream, fअगरo->pcm);

	/*
	 * Make sure the buffer and period size are multiple of the fअगरo burst
	 * size
	 */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_BUFFER_BYTES,
					 fअगरo->fअगरo_block);
	अगर (ret)
		वापस ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_step(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_PERIOD_BYTES,
					 fअगरo->fअगरo_block);
	अगर (ret)
		वापस ret;

	ret = clk_prepare_enable(fअगरo->pclk);
	अगर (ret)
		वापस ret;

	ret = request_irq(fअगरo->irq, aiu_fअगरo_isr, 0, dev_name(dai->dev),
			  substream);
	अगर (ret)
		clk_disable_unprepare(fअगरo->pclk);

	वापस ret;
पूर्ण

व्योम aiu_fअगरo_shutकरोwn(काष्ठा snd_pcm_substream *substream,
		       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aiu_fअगरo *fअगरo = dai->playback_dma_data;

	मुक्त_irq(fअगरo->irq, substream);
	clk_disable_unprepare(fअगरo->pclk);
पूर्ण

पूर्णांक aiu_fअगरo_pcm_new(काष्ठा snd_soc_pcm_runसमय *rtd,
		     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_card *card = rtd->card->snd_card;
	काष्ठा aiu_fअगरo *fअगरo = dai->playback_dma_data;
	माप_प्रकार size = fअगरo->pcm->buffer_bytes_max;

	snd_pcm_set_managed_buffer_all(rtd->pcm, SNDRV_DMA_TYPE_DEV,
				       card->dev, size, size);

	वापस 0;
पूर्ण

पूर्णांक aiu_fअगरo_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aiu_fअगरo *fअगरo;

	fअगरo = kzalloc(माप(*fअगरo), GFP_KERNEL);
	अगर (!fअगरo)
		वापस -ENOMEM;

	dai->playback_dma_data = fअगरo;

	वापस 0;
पूर्ण

पूर्णांक aiu_fअगरo_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	kमुक्त(dai->playback_dma_data);

	वापस 0;
पूर्ण

