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

#घोषणा AIU_I2S_SOURCE_DESC_MODE_8CH	BIT(0)
#घोषणा AIU_I2S_SOURCE_DESC_MODE_24BIT	BIT(5)
#घोषणा AIU_I2S_SOURCE_DESC_MODE_32BIT	BIT(9)
#घोषणा AIU_I2S_SOURCE_DESC_MODE_SPLIT	BIT(11)
#घोषणा AIU_RST_SOFT_I2S_FAST		BIT(0)

#घोषणा AIU_I2S_DAC_CFG_MSB_FIRST	BIT(2)
#घोषणा AIU_I2S_MISC_HOLD_EN		BIT(2)
#घोषणा AIU_CLK_CTRL_I2S_DIV_EN		BIT(0)
#घोषणा AIU_CLK_CTRL_I2S_DIV		GENMASK(3, 2)
#घोषणा AIU_CLK_CTRL_AOCLK_INVERT	BIT(6)
#घोषणा AIU_CLK_CTRL_LRCLK_INVERT	BIT(7)
#घोषणा AIU_CLK_CTRL_LRCLK_SKEW		GENMASK(9, 8)
#घोषणा AIU_CLK_CTRL_MORE_HDMI_AMCLK	BIT(6)
#घोषणा AIU_CLK_CTRL_MORE_I2S_DIV	GENMASK(5, 0)
#घोषणा AIU_CODEC_DAC_LRCLK_CTRL_DIV	GENMASK(11, 0)

अटल व्योम aiu_encoder_i2s_भागider_enable(काष्ठा snd_soc_component *component,
					   bool enable)
अणु
	snd_soc_component_update_bits(component, AIU_CLK_CTRL,
				      AIU_CLK_CTRL_I2S_DIV_EN,
				      enable ? AIU_CLK_CTRL_I2S_DIV_EN : 0);
पूर्ण

अटल व्योम aiu_encoder_i2s_hold(काष्ठा snd_soc_component *component,
				 bool enable)
अणु
	snd_soc_component_update_bits(component, AIU_I2S_MISC,
				      AIU_I2S_MISC_HOLD_EN,
				      enable ? AIU_I2S_MISC_HOLD_EN : 0);
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		aiu_encoder_i2s_hold(component, false);
		वापस 0;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		aiu_encoder_i2s_hold(component, true);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_setup_desc(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	/* Always operate in split (classic पूर्णांकerleaved) mode */
	अचिन्हित पूर्णांक desc = AIU_I2S_SOURCE_DESC_MODE_SPLIT;

	/* Reset required to update the pipeline */
	snd_soc_component_ग_लिखो(component, AIU_RST_SOFT, AIU_RST_SOFT_I2S_FAST);
	snd_soc_component_पढ़ो(component, AIU_I2S_SYNC);

	चयन (params_physical_width(params)) अणु
	हाल 16: /* Nothing to करो */
		अवरोध;

	हाल 32:
		desc |= (AIU_I2S_SOURCE_DESC_MODE_24BIT |
			 AIU_I2S_SOURCE_DESC_MODE_32BIT);
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (params_channels(params)) अणु
	हाल 2: /* Nothing to करो */
		अवरोध;
	हाल 8:
		desc |= AIU_I2S_SOURCE_DESC_MODE_8CH;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AIU_I2S_SOURCE_DESC,
				      AIU_I2S_SOURCE_DESC_MODE_8CH |
				      AIU_I2S_SOURCE_DESC_MODE_24BIT |
				      AIU_I2S_SOURCE_DESC_MODE_32BIT |
				      AIU_I2S_SOURCE_DESC_MODE_SPLIT,
				      desc);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_set_legacy_भाग(काष्ठा snd_soc_component *component,
					  काष्ठा snd_pcm_hw_params *params,
					  अचिन्हित पूर्णांक bs)
अणु
	चयन (bs) अणु
	हाल 1:
	हाल 2:
	हाल 4:
	हाल 8:
		/* These are the only valid legacy भागiders */
		अवरोध;

	शेष:
		dev_err(component->dev, "Unsupported i2s divider: %u\n", bs);
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AIU_CLK_CTRL,
				      AIU_CLK_CTRL_I2S_DIV,
				      FIELD_PREP(AIU_CLK_CTRL_I2S_DIV,
						 __ffs(bs)));

	snd_soc_component_update_bits(component, AIU_CLK_CTRL_MORE,
				      AIU_CLK_CTRL_MORE_I2S_DIV,
				      FIELD_PREP(AIU_CLK_CTRL_MORE_I2S_DIV,
						 0));

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_set_more_भाग(काष्ठा snd_soc_component *component,
					काष्ठा snd_pcm_hw_params *params,
					अचिन्हित पूर्णांक bs)
अणु
	/*
	 * NOTE: this HW is odd.
	 * In most configuration, the i2s भागider is 'mclk / blck'.
	 * However, in 16 bits - 8ch mode, this factor needs to be
	 * increased by 50% to get the correct output rate.
	 * No idea why !
	 */
	अगर (params_width(params) == 16 && params_channels(params) == 8) अणु
		अगर (bs % 2) अणु
			dev_err(component->dev,
				"Cannot increase i2s divider by 50%%\n");
			वापस -EINVAL;
		पूर्ण
		bs += bs / 2;
	पूर्ण

	/* Use CLK_MORE क्रम mclk to bclk भागider */
	snd_soc_component_update_bits(component, AIU_CLK_CTRL,
				      AIU_CLK_CTRL_I2S_DIV,
				      FIELD_PREP(AIU_CLK_CTRL_I2S_DIV, 0));

	snd_soc_component_update_bits(component, AIU_CLK_CTRL_MORE,
				      AIU_CLK_CTRL_MORE_I2S_DIV,
				      FIELD_PREP(AIU_CLK_CTRL_MORE_I2S_DIV,
						 bs - 1));

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_set_घड़ीs(काष्ठा snd_soc_component *component,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक srate = params_rate(params);
	अचिन्हित पूर्णांक fs, bs;
	पूर्णांक ret;

	/* Get the oversampling factor */
	fs = DIV_ROUND_CLOSEST(clk_get_rate(aiu->i2s.clks[MCLK].clk), srate);

	अगर (fs % 64)
		वापस -EINVAL;

	/* Send data MSB first */
	snd_soc_component_update_bits(component, AIU_I2S_DAC_CFG,
				      AIU_I2S_DAC_CFG_MSB_FIRST,
				      AIU_I2S_DAC_CFG_MSB_FIRST);

	/* Set bclk to lrlck ratio */
	snd_soc_component_update_bits(component, AIU_CODEC_DAC_LRCLK_CTRL,
				      AIU_CODEC_DAC_LRCLK_CTRL_DIV,
				      FIELD_PREP(AIU_CODEC_DAC_LRCLK_CTRL_DIV,
						 64 - 1));

	bs = fs / 64;

	अगर (aiu->platक्रमm->has_clk_ctrl_more_i2s_भाग)
		ret = aiu_encoder_i2s_set_more_भाग(component, params, bs);
	अन्यथा
		ret = aiu_encoder_i2s_set_legacy_भाग(component, params, bs);

	अगर (ret)
		वापस ret;

	/* Make sure amclk is used क्रम HDMI i2s as well */
	snd_soc_component_update_bits(component, AIU_CLK_CTRL_MORE,
				      AIU_CLK_CTRL_MORE_HDMI_AMCLK,
				      AIU_CLK_CTRL_MORE_HDMI_AMCLK);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_pcm_hw_params *params,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	पूर्णांक ret;

	/* Disable the घड़ी जबतक changing the settings */
	aiu_encoder_i2s_भागider_enable(component, false);

	ret = aiu_encoder_i2s_setup_desc(component, params);
	अगर (ret) अणु
		dev_err(dai->dev, "setting i2s desc failed\n");
		वापस ret;
	पूर्ण

	ret = aiu_encoder_i2s_set_घड़ीs(component, params);
	अगर (ret) अणु
		dev_err(dai->dev, "setting i2s clocks failed\n");
		वापस ret;
	पूर्ण

	aiu_encoder_i2s_भागider_enable(component, true);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	aiu_encoder_i2s_भागider_enable(component, false);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_set_fmt(काष्ठा snd_soc_dai *dai, अचिन्हित पूर्णांक fmt)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	अचिन्हित पूर्णांक inv = fmt & SND_SOC_DAIFMT_INV_MASK;
	अचिन्हित पूर्णांक val = 0;
	अचिन्हित पूर्णांक skew;

	/* Only CPU Master / Codec Slave supported ATM */
	अगर ((fmt & SND_SOC_DAIFMT_MASTER_MASK) != SND_SOC_DAIFMT_CBS_CFS)
		वापस -EINVAL;

	अगर (inv == SND_SOC_DAIFMT_NB_IF ||
	    inv == SND_SOC_DAIFMT_IB_IF)
		val |= AIU_CLK_CTRL_LRCLK_INVERT;

	अगर (inv == SND_SOC_DAIFMT_IB_NF ||
	    inv == SND_SOC_DAIFMT_IB_IF)
		val |= AIU_CLK_CTRL_AOCLK_INVERT;

	/* Signal skew */
	चयन (fmt & SND_SOC_DAIFMT_FORMAT_MASK) अणु
	हाल SND_SOC_DAIFMT_I2S:
		/* Invert sample घड़ी क्रम i2s */
		val ^= AIU_CLK_CTRL_LRCLK_INVERT;
		skew = 1;
		अवरोध;
	हाल SND_SOC_DAIFMT_LEFT_J:
		skew = 0;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	val |= FIELD_PREP(AIU_CLK_CTRL_LRCLK_SKEW, skew);
	snd_soc_component_update_bits(component, AIU_CLK_CTRL,
				      AIU_CLK_CTRL_LRCLK_INVERT |
				      AIU_CLK_CTRL_AOCLK_INVERT |
				      AIU_CLK_CTRL_LRCLK_SKEW,
				      val);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_i2s_set_sysclk(काष्ठा snd_soc_dai *dai, पूर्णांक clk_id,
				      अचिन्हित पूर्णांक freq, पूर्णांक dir)
अणु
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret;

	अगर (WARN_ON(clk_id != 0))
		वापस -EINVAL;

	अगर (dir == SND_SOC_CLOCK_IN)
		वापस 0;

	ret = clk_set_rate(aiu->i2s.clks[MCLK].clk, freq);
	अगर (ret)
		dev_err(dai->dev, "Failed to set sysclk to %uHz", freq);

	वापस ret;
पूर्ण

अटल स्थिर अचिन्हित पूर्णांक hw_channels[] = अणु2, 8पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list hw_channel_स्थिरraपूर्णांकs = अणु
	.list = hw_channels,
	.count = ARRAY_SIZE(hw_channels),
	.mask = 0,
पूर्ण;

अटल पूर्णांक aiu_encoder_i2s_startup(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret;

	/* Make sure the encoder माला_लो either 2 or 8 channels */
	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					 SNDRV_PCM_HW_PARAM_CHANNELS,
					 &hw_channel_स्थिरraपूर्णांकs);
	अगर (ret) अणु
		dev_err(dai->dev, "adding channels constraints failed\n");
		वापस ret;
	पूर्ण

	ret = clk_bulk_prepare_enable(aiu->i2s.clk_num, aiu->i2s.clks);
	अगर (ret)
		dev_err(dai->dev, "failed to enable i2s clocks\n");

	वापस ret;
पूर्ण

अटल व्योम aiu_encoder_i2s_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(dai->component);

	clk_bulk_disable_unprepare(aiu->i2s.clk_num, aiu->i2s.clks);
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops aiu_encoder_i2s_dai_ops = अणु
	.trigger	= aiu_encoder_i2s_trigger,
	.hw_params	= aiu_encoder_i2s_hw_params,
	.hw_मुक्त	= aiu_encoder_i2s_hw_मुक्त,
	.set_fmt	= aiu_encoder_i2s_set_fmt,
	.set_sysclk	= aiu_encoder_i2s_set_sysclk,
	.startup	= aiu_encoder_i2s_startup,
	.shutकरोwn	= aiu_encoder_i2s_shutकरोwn,
पूर्ण;

