<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2020 BayLibre, SAS.
// Author: Jerome Brunet <jbrunet@baylibre.com>

#समावेश <linux/bitfield.h>
#समावेश <linux/clk.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/pcm_iec958.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-dai.h>

#समावेश "aiu.h"

#घोषणा AIU_958_MISC_NON_PCM		BIT(0)
#घोषणा AIU_958_MISC_MODE_16BITS	BIT(1)
#घोषणा AIU_958_MISC_16BITS_ALIGN	GENMASK(6, 5)
#घोषणा AIU_958_MISC_MODE_32BITS	BIT(7)
#घोषणा AIU_958_MISC_U_FROM_STREAM	BIT(12)
#घोषणा AIU_958_MISC_FORCE_LR		BIT(13)
#घोषणा AIU_958_CTRL_HOLD_EN		BIT(0)
#घोषणा AIU_CLK_CTRL_958_DIV_EN		BIT(1)
#घोषणा AIU_CLK_CTRL_958_DIV		GENMASK(5, 4)
#घोषणा AIU_CLK_CTRL_958_DIV_MORE	BIT(12)

#घोषणा AIU_CS_WORD_LEN			4
#घोषणा AIU_958_INTERNAL_DIV		2

अटल व्योम
aiu_encoder_spdअगर_भागider_enable(काष्ठा snd_soc_component *component,
				 bool enable)
अणु
	snd_soc_component_update_bits(component, AIU_CLK_CTRL,
				      AIU_CLK_CTRL_958_DIV_EN,
				      enable ? AIU_CLK_CTRL_958_DIV_EN : 0);
पूर्ण

अटल व्योम aiu_encoder_spdअगर_hold(काष्ठा snd_soc_component *component,
				   bool enable)
अणु
	snd_soc_component_update_bits(component, AIU_958_CTRL,
				      AIU_958_CTRL_HOLD_EN,
				      enable ? AIU_958_CTRL_HOLD_EN : 0);
पूर्ण

अटल पूर्णांक
aiu_encoder_spdअगर_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd,
			  काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	चयन (cmd) अणु
	हाल SNDRV_PCM_TRIGGER_START:
	हाल SNDRV_PCM_TRIGGER_RESUME:
	हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
		aiu_encoder_spdअगर_hold(component, false);
		वापस 0;

	हाल SNDRV_PCM_TRIGGER_STOP:
	हाल SNDRV_PCM_TRIGGER_SUSPEND:
	हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
		aiu_encoder_spdअगर_hold(component, true);
		वापस 0;

	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक aiu_encoder_spdअगर_setup_cs_word(काष्ठा snd_soc_component *component,
					   काष्ठा snd_pcm_hw_params *params)
अणु
	u8 cs[AIU_CS_WORD_LEN];
	अचिन्हित पूर्णांक val;
	पूर्णांक ret;

	ret = snd_pcm_create_iec958_consumer_hw_params(params, cs,
						       AIU_CS_WORD_LEN);
	अगर (ret < 0)
		वापस ret;

	/* Write the 1st half word */
	val = cs[1] | cs[0] << 8;
	snd_soc_component_ग_लिखो(component, AIU_958_CHSTAT_L0, val);
	snd_soc_component_ग_लिखो(component, AIU_958_CHSTAT_R0, val);

	/* Write the 2nd half word */
	val = cs[3] | cs[2] << 8;
	snd_soc_component_ग_लिखो(component, AIU_958_CHSTAT_L1, val);
	snd_soc_component_ग_लिखो(component, AIU_958_CHSTAT_R1, val);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_spdअगर_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *params,
				       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(component);
	अचिन्हित पूर्णांक val = 0, mrate;
	पूर्णांक ret;

	/* Disable the घड़ी जबतक changing the settings */
	aiu_encoder_spdअगर_भागider_enable(component, false);

	चयन (params_physical_width(params)) अणु
	हाल 16:
		val |= AIU_958_MISC_MODE_16BITS;
		val |= FIELD_PREP(AIU_958_MISC_16BITS_ALIGN, 2);
		अवरोध;
	हाल 32:
		val |= AIU_958_MISC_MODE_32BITS;
		अवरोध;
	शेष:
		dev_err(dai->dev, "Unsupport physical width\n");
		वापस -EINVAL;
	पूर्ण

	snd_soc_component_update_bits(component, AIU_958_MISC,
				      AIU_958_MISC_NON_PCM |
				      AIU_958_MISC_MODE_16BITS |
				      AIU_958_MISC_16BITS_ALIGN |
				      AIU_958_MISC_MODE_32BITS |
				      AIU_958_MISC_FORCE_LR |
				      AIU_958_MISC_U_FROM_STREAM,
				      val);

	/* Set the stream channel status word */
	ret = aiu_encoder_spdअगर_setup_cs_word(component, params);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to set channel status word\n");
		वापस ret;
	पूर्ण

	snd_soc_component_update_bits(component, AIU_CLK_CTRL,
				      AIU_CLK_CTRL_958_DIV |
				      AIU_CLK_CTRL_958_DIV_MORE,
				      FIELD_PREP(AIU_CLK_CTRL_958_DIV,
						 __ffs(AIU_958_INTERNAL_DIV)));

	/* 2 * 32bits per subframe * 2 channels = 128 */
	mrate = params_rate(params) * 128 * AIU_958_INTERNAL_DIV;
	ret = clk_set_rate(aiu->spdअगर.clks[MCLK].clk, mrate);
	अगर (ret) अणु
		dev_err(dai->dev, "failed to set mclk rate\n");
		वापस ret;
	पूर्ण

	aiu_encoder_spdअगर_भागider_enable(component, true);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_spdअगर_hw_मुक्त(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा snd_soc_component *component = dai->component;

	aiu_encoder_spdअगर_भागider_enable(component, false);

	वापस 0;
पूर्ण

अटल पूर्णांक aiu_encoder_spdअगर_startup(काष्ठा snd_pcm_substream *substream,
				     काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(dai->component);
	पूर्णांक ret;

	/*
	 * NOTE: Make sure the spdअगर block is on its own भागider.
	 *
	 * The spdअगर can be घड़ीed by the i2s master घड़ी or its own
	 * घड़ी. We should (in theory) change the source depending on the
	 * origin of the data.
	 *
	 * However, considering the घड़ीing scheme used on these platक्रमms,
	 * the master घड़ीs will pick the same PLL source when they are
	 * playing from the same FIFO. The घड़ी should be in sync so, it
	 * should not be necessary to reparent the spdअगर master घड़ी.
	 */
	ret = clk_set_parent(aiu->spdअगर.clks[MCLK].clk,
			     aiu->spdअगर_mclk);
	अगर (ret)
		वापस ret;

	ret = clk_bulk_prepare_enable(aiu->spdअगर.clk_num, aiu->spdअगर.clks);
	अगर (ret)
		dev_err(dai->dev, "failed to enable spdif clocks\n");

	वापस ret;
पूर्ण

अटल व्योम aiu_encoder_spdअगर_shutकरोwn(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_soc_dai *dai)
अणु
	काष्ठा aiu *aiu = snd_soc_component_get_drvdata(dai->component);

	clk_bulk_disable_unprepare(aiu->spdअगर.clk_num, aiu->spdअगर.clks);
पूर्ण

स्थिर काष्ठा snd_soc_dai_ops aiu_encoder_spdअगर_dai_ops = अणु
	.trigger	= aiu_encoder_spdअगर_trigger,
	.hw_params	= aiu_encoder_spdअगर_hw_params,
	.hw_मुक्त	= aiu_encoder_spdअगर_hw_मुक्त,
	.startup	= aiu_encoder_spdअगर_startup,
	.shutकरोwn	= aiu_encoder_spdअगर_shutकरोwn,
पूर्ण;
