<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2010, Lars-Peter Clausen <lars@metafoo.de>
 */

#समावेश <linux/init.h>
#समावेश <linux/पन.स>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>

#समावेश <linux/clk.h>
#समावेश <linux/delay.h>

#समावेश <linux/dma-mapping.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/initval.h>
#समावेश <sound/dmaengine_pcm.h>

#समावेश "jz4740-i2s.h"

#घोषणा JZ_REG_AIC_CONF		0x00
#घोषणा JZ_REG_AIC_CTRL		0x04
#घोषणा JZ_REG_AIC_I2S_FMT	0x10
#घोषणा JZ_REG_AIC_FIFO_STATUS	0x14
#घोषणा JZ_REG_AIC_I2S_STATUS	0x1c
#घोषणा JZ_REG_AIC_CLK_DIV	0x30
#घोषणा JZ_REG_AIC_FIFO		0x34

#घोषणा JZ_AIC_CONF_FIFO_RX_THRESHOLD_MASK (0xf << 12)
#घोषणा JZ_AIC_CONF_FIFO_TX_THRESHOLD_MASK (0xf <<  8)
#घोषणा JZ_AIC_CONF_OVERFLOW_PLAY_LAST BIT(6)
#घोषणा JZ_AIC_CONF_INTERNAL_CODEC BIT(5)
#घोषणा JZ_AIC_CONF_I2S BIT(4)
#घोषणा JZ_AIC_CONF_RESET BIT(3)
#घोषणा JZ_AIC_CONF_BIT_CLK_MASTER BIT(2)
#घोषणा JZ_AIC_CONF_SYNC_CLK_MASTER BIT(1)
#घोषणा JZ_AIC_CONF_ENABLE BIT(0)

#घोषणा JZ_AIC_CONF_FIFO_RX_THRESHOLD_OFFSET 12
#घोषणा JZ_AIC_CONF_FIFO_TX_THRESHOLD_OFFSET 8
#घोषणा JZ4760_AIC_CONF_FIFO_RX_THRESHOLD_OFFSET 24
#घोषणा JZ4760_AIC_CONF_FIFO_TX_THRESHOLD_OFFSET 16

#घोषणा JZ_AIC_CTRL_OUTPUT_SAMPLE_SIZE_MASK (0x7 << 19)
#घोषणा JZ_AIC_CTRL_INPUT_SAMPLE_SIZE_MASK (0x7 << 16)
#घोषणा JZ_AIC_CTRL_ENABLE_RX_DMA BIT(15)
#घोषणा JZ_AIC_CTRL_ENABLE_TX_DMA BIT(14)
#घोषणा JZ_AIC_CTRL_MONO_TO_STEREO BIT(11)
#घोषणा JZ_AIC_CTRL_SWITCH_ENDIANNESS BIT(10)
#घोषणा JZ_AIC_CTRL_SIGNED_TO_UNSIGNED BIT(9)
#घोषणा JZ_AIC_CTRL_FLUSH		BIT(8)
#घोषणा JZ_AIC_CTRL_ENABLE_ROR_INT BIT(6)
#घोषणा JZ_AIC_CTRL_ENABLE_TUR_INT BIT(5)
#घोषणा JZ_AIC_CTRL_ENABLE_RFS_INT BIT(4)
#घोषणा JZ_AIC_CTRL_ENABLE_TFS_INT BIT(3)
#घोषणा JZ_AIC_CTRL_ENABLE_LOOPBACK BIT(2)
#घोषणा JZ_AIC_CTRL_ENABLE_PLAYBACK BIT(1)
#घोषणा JZ_AIC_CTRL_ENABLE_CAPTURE BIT(0)

#घोषणा JZ_AIC_CTRL_OUTPUT_SAMPLE_SIZE_OFFSET 19
#घोषणा JZ_AIC_CTRL_INPUT_SAMPLE_SIZE_OFFSET  16

#घोषणा JZ_AIC_I2S_FMT_DISABLE_BIT_CLK BIT(12)
#घोषणा JZ_AIC_I2S_FMT_DISABLE_BIT_ICLK BIT(13)
#घोषणा JZ_AIC_I2S_FMT_ENABLE_SYS_CLK BIT(4)
#घोषणा JZ_AIC_I2S_FMT_MSB BIT(0)

#घोषणा JZ_AIC_I2S_STATUS_BUSY BIT(2)

#घोषणा JZ_AIC_CLK_DIV_MASK 0xf
#घोषणा I2SDIV_DV_SHIFT 0
#घोषणा I2SDIV_DV_MASK (0xf << I2SDIV_DV_SHIFT)
#घोषणा I2SDIV_IDV_SHIFT 8
#घोषणा I2SDIV_IDV_MASK (0xf << I2SDIV_IDV_SHIFT)

क्रमागत jz47xx_i2s_version अणु
	JZ_I2S_JZ4740,
	JZ_I2S_JZ4760,
	JZ_I2S_JZ4770,
	JZ_I2S_JZ4780,
पूर्ण;

काष्ठा i2s_soc_info अणु
	क्रमागत jz47xx_i2s_version version;
	काष्ठा snd_soc_dai_driver *dai;
पूर्ण;

काष्ठा jz4740_i2s अणु
	काष्ठा resource *mem;
	व्योम __iomem *base;
	dma_addr_t phys_base;

	काष्ठा clk *clk_aic;
	काष्ठा clk *clk_i2s;

	काष्ठा snd_dmaengine_dai_dma_data playback_dma_data;
	काष्ठा snd_dmaengine_dai_dma_data capture_dma_data;

	स्थिर काष्ठा i2s_soc_info *soc_info;
पूर्ण;

अटल अंतरभूत uपूर्णांक32_t jz4740_i2s_पढ़ो(स्थिर काष्ठा jz4740_i2s *i2s,
	अचिन्हित पूर्णांक reg)
अणु
	वापस पढ़ोl(i2s->base + reg);
पूर्ण

अटल अंतरभूत व्योम jz4740_i2s_ग_लिखो(स्थिर काष्ठा jz4740_i2s *i2s,
	अचिन्हित पूर्णांक reg, uपूर्णांक32_t value)
अणु
	ग_लिखोl(value, i2s->base + reg);
पूर्ण

अटल पूर्णांक jz4740_i2s_startup(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t conf, ctrl;
	पूर्णांक ret;

	अगर (snd_soc_dai_active(dai))
		वापस 0;

	ctrl = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CTRL);
	ctrl |= JZ_AIC_CTRL_FLUSH;
	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CTRL, ctrl);

	ret = clk_prepare_enable(i2s->clk_i2s);
	अगर (ret)
		वापस ret;

	conf = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CONF);
	conf |= JZ_AIC_CONF_ENABLE;
	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CONF, conf);

	वापस 0;
पूर्ण

अटल व्योम jz4740_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t conf;

	अगर (snd_soc_dai_active(dai))
		वापस;

	conf = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CONF);
	conf &= ~JZ_AIC_CONF_ENABLE;
	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CONF, conf);

	clk_disable_unprepare(i2s->clk_i2s);
पूर्ण

अटल पूर्णांक jz4740_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
	काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	uपूर्णांक32_t ctrl;
	uपूर्णांक32_t mask;

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
		mask = JZ_AIC_CTRL_ENABLE_PLAYBACK | JZ_AIC_CTRL_ENABLE_TX_DMA;
	अन्यथा
		mask = JZ_AIC_CTRL_ENABLE_CAPTURE | JZ_AIC_CTRL_ENABLE_RX_DMA;

	ctrl = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CTRL);

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		ctrl |= mask;
		अवरोध;
	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		ctrl &= ~mask;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CTRL, ctrl);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_i2s_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	uपूर्णांक32_t क्रमmat = 0;
	uपूर्णांक32_t conf;

	conf = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CONF);

	conf &= ~(JZ_AIC_CONF_BIT_CLK_MASTER | JZ_AIC_CONF_SYNC_CLK_MASTER);

	चयन (fmt & SND_SOC_DAIFMT_MASTER_MASK) अणु
	हाल SND_SOC_DAIFMT_CBS_CFS:
		conf |= JZ_AIC_CONF_BIT_CLK_MASTER | JZ_AIC_CONF_SYNC_CLK_MASTER;
		क्रमmat |= JZ_AIC_I2S_FMT_ENABLE_SYS_CLK;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFS:
		conf |= JZ_AIC_CONF_SYNC_CLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBS_CFM:
		conf |= JZ_AIC_CONF_BIT_CLK_MASTER;
		अवरोध;
	हाल SND_SOC_DAIFMT_CBM_CFM:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_MSB:
		क्रमmat |= JZ_AIC_I2S_FMT_MSB;
		अवरोध;
	हाल SND_SOC_DAIFMT_I2S:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (fmt & SND_SOC_DAIFMT_INV_MASK) अणु
	हाल SND_SOC_DAIFMT_NB_NF:
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CONF, conf);
	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_I2S_FMT, क्रमmat);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params, काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	अचिन्हित पूर्णांक sample_size;
	uपूर्णांक32_t ctrl, भाग_reg;
	पूर्णांक भाग;

	ctrl = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CTRL);

	भाग_reg = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CLK_DIV);
	भाग = clk_get_rate(i2s->clk_i2s) / (64 * params_rate(params));

	चयन (params_क्रमmat(params)) अणु
	हाल SNDRV_PCM_FORMAT_S8:
		sample_size = 0;
		अवरोध;
	हाल SNDRV_PCM_FORMAT_S16:
		sample_size = 1;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (substream->stream == SNDRV_PCM_STREAM_PLAYBACK) अणु
		ctrl &= ~JZ_AIC_CTRL_OUTPUT_SAMPLE_SIZE_MASK;
		ctrl |= sample_size << JZ_AIC_CTRL_OUTPUT_SAMPLE_SIZE_OFFSET;
		अगर (params_channels(params) == 1)
			ctrl |= JZ_AIC_CTRL_MONO_TO_STEREO;
		अन्यथा
			ctrl &= ~JZ_AIC_CTRL_MONO_TO_STEREO;

		भाग_reg &= ~I2SDIV_DV_MASK;
		भाग_reg |= (भाग - 1) << I2SDIV_DV_SHIFT;
	पूर्ण अन्यथा अणु
		ctrl &= ~JZ_AIC_CTRL_INPUT_SAMPLE_SIZE_MASK;
		ctrl |= sample_size << JZ_AIC_CTRL_INPUT_SAMPLE_SIZE_OFFSET;

		अगर (i2s->soc_info->version >= JZ_I2S_JZ4770) अणु
			भाग_reg &= ~I2SDIV_IDV_MASK;
			भाग_reg |= (भाग - 1) << I2SDIV_IDV_SHIFT;
		पूर्ण अन्यथा अणु
			भाग_reg &= ~I2SDIV_DV_MASK;
			भाग_reg |= (भाग - 1) << I2SDIV_DV_SHIFT;
		पूर्ण
	पूर्ण

	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CTRL, ctrl);
	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CLK_DIV, भाग_reg);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_i2s_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
	अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	काष्ठा clk *parent;
	पूर्णांक ret = 0;

	चयन (clk_id) अणु
	हाल JZ4740_I2S_CLKSRC_EXT:
		parent = clk_get(शून्य, "ext");
		अगर (IS_ERR(parent))
			वापस PTR_ERR(parent);
		clk_set_parent(i2s->clk_i2s, parent);
		अवरोध;
	हाल JZ4740_I2S_CLKSRC_PLL:
		parent = clk_get(शून्य, "pll half");
		अगर (IS_ERR(parent))
			वापस PTR_ERR(parent);
		clk_set_parent(i2s->clk_i2s, parent);
		ret = clk_set_rate(i2s->clk_i2s, freq);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	clk_put(parent);

	वापस ret;
पूर्ण

अटल पूर्णांक jz4740_i2s_suspend(काष्ठा snd_soc_component *component)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_component_get_drvdata(component);
	uपूर्णांक32_t conf;

	अगर (snd_soc_component_active(component)) अणु
		conf = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CONF);
		conf &= ~JZ_AIC_CONF_ENABLE;
		jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CONF, conf);

		clk_disable_unprepare(i2s->clk_i2s);
	पूर्ण

	clk_disable_unprepare(i2s->clk_aic);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_i2s_resume(काष्ठा snd_soc_component *component)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_component_get_drvdata(component);
	uपूर्णांक32_t conf;
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s->clk_aic);
	अगर (ret)
		वापस ret;

	अगर (snd_soc_component_active(component)) अणु
		ret = clk_prepare_enable(i2s->clk_i2s);
		अगर (ret) अणु
			clk_disable_unprepare(i2s->clk_aic);
			वापस ret;
		पूर्ण

		conf = jz4740_i2s_पढ़ो(i2s, JZ_REG_AIC_CONF);
		conf |= JZ_AIC_CONF_ENABLE;
		jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CONF, conf);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम jz4740_i2c_init_pcm_config(काष्ठा jz4740_i2s *i2s)
अणु
	काष्ठा snd_dmaengine_dai_dma_data *dma_data;

	/* Playback */
	dma_data = &i2s->playback_dma_data;
	dma_data->maxburst = 16;
	dma_data->addr = i2s->phys_base + JZ_REG_AIC_FIFO;

	/* Capture */
	dma_data = &i2s->capture_dma_data;
	dma_data->maxburst = 16;
	dma_data->addr = i2s->phys_base + JZ_REG_AIC_FIFO;
पूर्ण

अटल पूर्णांक jz4740_i2s_dai_probe(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);
	uपूर्णांक32_t conf;
	पूर्णांक ret;

	ret = clk_prepare_enable(i2s->clk_aic);
	अगर (ret)
		वापस ret;

	jz4740_i2c_init_pcm_config(i2s);
	snd_soc_dai_init_dma_data(dai, &i2s->playback_dma_data,
		&i2s->capture_dma_data);

	अगर (i2s->soc_info->version >= JZ_I2S_JZ4760) अणु
		conf = (7 << JZ4760_AIC_CONF_FIFO_RX_THRESHOLD_OFFSET) |
			(8 << JZ4760_AIC_CONF_FIFO_TX_THRESHOLD_OFFSET) |
			JZ_AIC_CONF_OVERFLOW_PLAY_LAST |
			JZ_AIC_CONF_I2S |
			JZ_AIC_CONF_INTERNAL_CODEC;
	पूर्ण अन्यथा अणु
		conf = (7 << JZ_AIC_CONF_FIFO_RX_THRESHOLD_OFFSET) |
			(8 << JZ_AIC_CONF_FIFO_TX_THRESHOLD_OFFSET) |
			JZ_AIC_CONF_OVERFLOW_PLAY_LAST |
			JZ_AIC_CONF_I2S |
			JZ_AIC_CONF_INTERNAL_CODEC;
	पूर्ण

	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CONF, JZ_AIC_CONF_RESET);
	jz4740_i2s_ग_लिखो(i2s, JZ_REG_AIC_CONF, conf);

	वापस 0;
पूर्ण

अटल पूर्णांक jz4740_i2s_dai_हटाओ(काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा jz4740_i2s *i2s = snd_soc_dai_get_drvdata(dai);

	clk_disable_unprepare(i2s->clk_aic);
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dai_ops jz4740_i2s_dai_ops = अणु
	.startup = jz4740_i2s_startup,
	.shutकरोwn = jz4740_i2s_shutकरोwn,
	.trigger = jz4740_i2s_trigger,
	.hw_params = jz4740_i2s_hw_params,
	.set_fmt = jz4740_i2s_set_fmt,
	.set_sysclk = jz4740_i2s_set_sysclk,
पूर्ण;

#घोषणा JZ4740_I2S_FMTS (SNDRV_PCM_FMTBIT_S8 | \
		SNDRV_PCM_FMTBIT_S16_LE)

अटल काष्ठा snd_soc_dai_driver jz4740_i2s_dai = अणु
	.probe = jz4740_i2s_dai_probe,
	.हटाओ = jz4740_i2s_dai_हटाओ,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = JZ4740_I2S_FMTS,
	पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = JZ4740_I2S_FMTS,
	पूर्ण,
	.symmetric_rate = 1,
	.ops = &jz4740_i2s_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा i2s_soc_info jz4740_i2s_soc_info = अणु
	.version = JZ_I2S_JZ4740,
	.dai = &jz4740_i2s_dai,
पूर्ण;

अटल स्थिर काष्ठा i2s_soc_info jz4760_i2s_soc_info = अणु
	.version = JZ_I2S_JZ4760,
	.dai = &jz4740_i2s_dai,
पूर्ण;

अटल काष्ठा snd_soc_dai_driver jz4770_i2s_dai = अणु
	.probe = jz4740_i2s_dai_probe,
	.हटाओ = jz4740_i2s_dai_हटाओ,
	.playback = अणु
		.channels_min = 1,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = JZ4740_I2S_FMTS,
	पूर्ण,
	.capture = अणु
		.channels_min = 2,
		.channels_max = 2,
		.rates = SNDRV_PCM_RATE_8000_48000,
		.क्रमmats = JZ4740_I2S_FMTS,
	पूर्ण,
	.ops = &jz4740_i2s_dai_ops,
पूर्ण;

अटल स्थिर काष्ठा i2s_soc_info jz4770_i2s_soc_info = अणु
	.version = JZ_I2S_JZ4770,
	.dai = &jz4770_i2s_dai,
पूर्ण;

अटल स्थिर काष्ठा i2s_soc_info jz4780_i2s_soc_info = अणु
	.version = JZ_I2S_JZ4780,
	.dai = &jz4770_i2s_dai,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_component_driver jz4740_i2s_component = अणु
	.name		= "jz4740-i2s",
	.suspend	= jz4740_i2s_suspend,
	.resume		= jz4740_i2s_resume,
पूर्ण;

अटल स्थिर काष्ठा of_device_id jz4740_of_matches[] = अणु
	अणु .compatible = "ingenic,jz4740-i2s", .data = &jz4740_i2s_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4760-i2s", .data = &jz4760_i2s_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4770-i2s", .data = &jz4770_i2s_soc_info पूर्ण,
	अणु .compatible = "ingenic,jz4780-i2s", .data = &jz4780_i2s_soc_info पूर्ण,
	अणु /* sentinel */ पूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, jz4740_of_matches);

अटल पूर्णांक jz4740_i2s_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device *dev = &pdev->dev;
	काष्ठा jz4740_i2s *i2s;
	काष्ठा resource *mem;
	पूर्णांक ret;

	i2s = devm_kzalloc(dev, माप(*i2s), GFP_KERNEL);
	अगर (!i2s)
		वापस -ENOMEM;

	i2s->soc_info = device_get_match_data(dev);

	mem = platक्रमm_get_resource(pdev, IORESOURCE_MEM, 0);
	i2s->base = devm_ioremap_resource(dev, mem);
	अगर (IS_ERR(i2s->base))
		वापस PTR_ERR(i2s->base);

	i2s->phys_base = mem->start;

	i2s->clk_aic = devm_clk_get(dev, "aic");
	अगर (IS_ERR(i2s->clk_aic))
		वापस PTR_ERR(i2s->clk_aic);

	i2s->clk_i2s = devm_clk_get(dev, "i2s");
	अगर (IS_ERR(i2s->clk_i2s))
		वापस PTR_ERR(i2s->clk_i2s);

	platक्रमm_set_drvdata(pdev, i2s);

	ret = devm_snd_soc_रेजिस्टर_component(dev, &jz4740_i2s_component,
					      i2s->soc_info->dai, 1);
	अगर (ret)
		वापस ret;

	वापस devm_snd_dmaengine_pcm_रेजिस्टर(dev, शून्य,
		SND_DMAENGINE_PCM_FLAG_COMPAT);
पूर्ण

अटल काष्ठा platक्रमm_driver jz4740_i2s_driver = अणु
	.probe = jz4740_i2s_dev_probe,
	.driver = अणु
		.name = "jz4740-i2s",
		.of_match_table = jz4740_of_matches,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(jz4740_i2s_driver);

MODULE_AUTHOR("Lars-Peter Clausen, <lars@metafoo.de>");
MODULE_DESCRIPTION("Ingenic JZ4740 SoC I2S driver");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:jz4740-i2s");
