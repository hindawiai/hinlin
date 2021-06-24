<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/clk.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "aiu.h"
#समावेश "aiu-fifo.h"

#घोषणा AIU_IEC958_DCU_FF_CTRL_EN		BIT(0)
#घोषणा AIU_IEC958_DCU_FF_CTRL_AUTO_DISABLE	BIT(1)
#घोषणा AIU_IEC958_DCU_FF_CTRL_IRQ_MODE		GENMASK(3, 2)
#घोषणा AIU_IEC958_DCU_FF_CTRL_IRQ_OUT_THD	BIT(2)
#घोषणा AIU_IEC958_DCU_FF_CTRL_IRQ_FRAME_READ	BIT(3)
#घोषणा AIU_IEC958_DCU_FF_CTRL_SYNC_HEAD_EN	BIT(4)
#घोषणा AIU_IEC958_DCU_FF_CTRL_BYTE_SEEK	BIT(5)
#घोषणा AIU_IEC958_DCU_FF_CTRL_CONTINUE		BIT(6)
#घोषणा AIU_MEM_IEC958_CONTROL_ENDIAN		GENMASK(5, 3)
#घोषणा AIU_MEM_IEC958_CONTROL_RD_DDR		BIT(6)
#घोषणा AIU_MEM_IEC958_CONTROL_MODE_16BIT	BIT(7)
#घोषणा AIU_MEM_IEC958_CONTROL_MODE_LINEAR	BIT(8)
#घोषणा AIU_MEM_IEC958_BUF_CNTL_INIT		BIT(0)

#घोषणा AIU_FIFO_SPDIF_BLOCK			8

अटल काष्ठा snd_pcm_hardware fअगरo_spdअगर_pcm = अणु
	.info = (SNDRV_PCM_INFO_INTERLEAVED |
		 SNDRV_PCM_INFO_MMAP |
		 SNDRV_PCM_INFO_MMAP_VALID |
		 SNDRV_PCM_INFO_PAUSE),
	.क्रमmats = AIU_FORMATS,
	.rate_min = 5512,
	.rate_max = 192000,
	.channels_min = 2,
	.channels_max = 2,
	.period_bytes_min = AIU_FIFO_SPDIF_BLOCK,
	.period_bytes_max = AIU_FIFO_SPDIF_BLOCK * अच_लघु_उच्च,
	.periods_min = 2,
	.periods_max = अच_पूर्णांक_उच्च,

	/* No real justअगरication क्रम this */
	.buffer_bytes_max = 1 * 1024 * 1024,
पूर्ण;

अटल व्योम fअगरo_spdअगर_dcu_enable(काष्ठा snd_soc_component *component,
				  bool enable)
अणु
	snd_soc_component_update_bits(component, AIU_IEC958_DCU_FF_CTRL,
				      AIU_IEC958_DCU_FF_CTRL_EN,
				      enable ? AIU_IEC958_DCU_FF_CTRL_EN : 0);
पूर्ण

अटल पूर्णांक fअगरo_spdअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	ret = aiu_fअगरo_trigger(substream, cmd, dai);
	अगर (ret)
		वापस ret;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		fअगरo_spdअगर_dcu_enable(component, true);
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
	हाल SNDRV_PCM_TRIGGER_STOP:
		fअगरo_spdअगर_dcu_enable(component, false);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक fअगरo_spdअगर_prepare(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	ret = aiu_fअगरo_prepare(substream, dai);
	अगर (ret)
		वापस ret;

	snd_soc_component_update_bits(component,
				      AIU_MEM_IEC958_BUF_CNTL,
				      AIU_MEM_IEC958_BUF_CNTL_INIT,
				      AIU_MEM_IEC958_BUF_CNTL_INIT);
	snd_soc_component_update_bits(component,
				      AIU_MEM_IEC958_BUF_CNTL,
				      AIU_MEM_IEC958_BUF_CNTL_INIT, 0);

	वापस 0;
पूर्ण

अटल पूर्णांक fअगरo_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				काष्ठा snd_pcm_hw_params *params,
				काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = aiu_fअगरo_hw_params(substream, params, dai);
	अगर (ret)
		वापस ret;

	val = AIU_MEM_IEC958_CONTROL_RD_DDR |
	      AIU_MEM_IEC958_CONTROL_MODE_LINEAR;

	चयन (params_physical_width(params)) अणु
	हाल 16:
		val |= AIU_MEM_IEC958_CONTROL_MODE_16BIT;
		अवरोध;
	हाल 32:
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unsupported physical width %u\n",
			params_physical_width(params));
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AIU_MEM_IEC958_CONTROL,
				      AIU_MEM_IEC958_CONTROL_ENDIAN |
				      AIU_MEM_IEC958_CONTROL_RD_DDR |
				      AIU_MEM_IEC958_CONTROL_MODE_LINEAR |
				      AIU_MEM_IEC958_CONTROL_MODE_16BIT,
				      val);

	/* Number bytes पढ़ो by the FIFO between each IRQ */
	snd_soc_component_ग_लिखो(component, AIU_IEC958_BPF,
				params_period_bytes(params));

	/*
	 * AUTO_DISABLE and SYNC_HEAD are enabled by शेष but
	 * this should be disabled in PCM (uncompressed) mode
	 */
	snd_soc_component_update_bits(component, AIU_IEC958_DCU_FF_CTRL,
				      AIU_IEC958_DCU_FF_CTRL_AUTO_DISABLE |
				      AIU_IEC958_DCU_FF_CTRL_IRQ_MODE |
				      AIU_IEC958_DCU_FF_CTRL_SYNC_HEAD_EN,
				      AIU_IEC958_DCU_FF_CTRL_IRQ_FRAME_READ);

	वापस 0;
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops aiu_fअगरo_spdअगर_dai_ops = अणु
	.trigger	= fअगरo_spdअगर_trigger,
	.prepare	= fअगरo_spdअगर_prepare,
	.hw_params	= fअगरo_spdअगर_hw_params,
	.startup	= aiu_fअगरo_startup,
	.shutकरोwn	= aiu_fअगरo_shutकरोwn,
पूर्ण;

पूर्णांक aiu_fअगरo_spdअगर_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(component);
	काष्ठा aiu_fअगरo *fअगरo;
	पूर्णांक ret;

	ret = aiu_fअगरo_dai_probe(dai);
	अगर (ret)
		वापस ret;

	fअगरo = dai->playback_dma_data;

	fअगरo->pcm = &fअगरo_spdअगर_pcm;
	fअगरo->mem_offset = AIU_MEM_IEC958_START;
	fअगरo->fअगरo_block = 1;
	fअगरo->pclk = aiu->spdअगर.clks[PCLK].clk;
	fअगरo->irq = aiu->spdअगर.irq;

	वापस 0;
पूर्ण
