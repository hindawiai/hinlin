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

#समावेश "aiu.h"
#समावेश "aiu-fifo.h"

#घोषणा AIU_I2S_SOURCE_DESC_MODE_8CH	BIT(0)
#घोषणा AIU_I2S_SOURCE_DESC_MODE_24BIT	BIT(5)
#घोषणा AIU_I2S_SOURCE_DESC_MODE_32BIT	BIT(9)
#घोषणा AIU_I2S_SOURCE_DESC_MODE_SPLIT	BIT(11)
#घोषणा AIU_MEM_I2S_MASKS_IRQ_BLOCK	GENMASK(31, 16)
#घोषणा AIU_MEM_I2S_CONTROL_MODE_16BIT	BIT(6)
#घोषणा AIU_MEM_I2S_BUF_CNTL_INIT	BIT(0)
#घोषणा AIU_RST_SOFT_I2S_FAST		BIT(0)

#घोषणा AIU_FIFO_I2S_BLOCK		256

अटल काष्ठा snd_pcm_hardware fअगरo_i2s_pcm = अणु
	.info = (SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_PAUSE),
	.क्रमmats = AIU_FORMATS,
	.rate_min = 5512,
	.rate_max = 192000,
	.channels_min = 2,
	.channels_max = 8,
	.period_bytes_min = AIU_FIFO_I2S_BLOCK,
	.period_bytes_max = AIU_FIFO_I2S_BLOCK * अच_लघु_उच्च,
	.periods_min = 2,
	.periods_max = अच_पूर्णांक_उच्च,

	/* No real justअगरication क्रम this */
	.buffer_bytes_max = 1 * 1024 * 1024,
पूर्ण;

अटल पूर्णांक aiu_fअगरo_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		snd_soc_component_ग_लिखो(component, AIU_RST_SOFT,
					AIU_RST_SOFT_I2S_FAST);
		snd_soc_component_पढ़ो(component, AIU_I2S_SYNC);
		अवरोध;
	पूर्ण

	वापस aiu_fअगरo_trigger(substream, cmd, dai);
पूर्ण

अटल पूर्णांक aiu_fअगरo_i2s_prepare(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	ret = aiu_fअगरo_prepare(substream, dai);
	अगर (ret)
		वापस ret;

	snd_soc_component_update_bits(component,
				      AIU_MEM_I2S_BUF_CNTL,
				      AIU_MEM_I2S_BUF_CNTL_INIT,
				      AIU_MEM_I2S_BUF_CNTL_INIT);
	snd_soc_component_update_bits(component,
				      AIU_MEM_I2S_BUF_CNTL,
				      AIU_MEM_I2S_BUF_CNTL_INIT, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_fअगरo_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				  काष्ठा snd_pcm_hw_params *params,
				  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aiu_fअगरo *fअगरo = dai->playback_dma_data;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = aiu_fअगरo_hw_params(substream, params, dai);
	अगर (ret)
		वापस ret;

	चयन (params_physical_width(params)) अणु
	हाल 16:
		val = AIU_MEM_I2S_CONTROL_MODE_16BIT;
		अवरोध;
	हाल 32:
		val = 0;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unsupported physical width %u\n",
			params_physical_width(params));
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AIU_MEM_I2S_CONTROL,
				      AIU_MEM_I2S_CONTROL_MODE_16BIT,
				      val);

	/* Setup the irq periodicity */
	val = params_period_bytes(params) / fअगरo->fअगरo_block;
	val = FIELD_PREP(AIU_MEM_I2S_MASKS_IRQ_BLOCK, val);
	snd_soc_component_update_bits(component, AIU_MEM_I2S_MASKS,
				      AIU_MEM_I2S_MASKS_IRQ_BLOCK, val);

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops aiu_fअगरo_i2s_dai_ops = अणु
	.trigger	= aiu_fअगरo_i2s_trigger,
	.prepare	= aiu_fअगरo_i2s_prepare,
	.hw_params	= aiu_fअगरo_i2s_hw_params,
	.startup	= aiu_fअगरo_startup,
	.shutकरोwn	= aiu_fअगरo_shutकरोwn,
पूर्ण;

पूर्णांक aiu_fअगरo_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(component);
	काष्ठा aiu_fअगरo *fअगरo;
	पूर्णांक ret;

	ret = aiu_fअगरo_dai_probe(dai);
	अगर (ret)
		वापस ret;

	fअगरo = dai->playback_dma_data;

	fअगरo->pcm = &fअगरo_i2s_pcm;
	fअगरo->mem_offset = AIU_MEM_I2S_START;
	fअगरo->fअगरo_block = AIU_FIFO_I2S_BLOCK;
	fअगरo->pclk = aiu->i2s.clks[PCLK].clk;
	fअगरo->irq = aiu->i2s.irq;

	वापस 0;
पूर्ण
