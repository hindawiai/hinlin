<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 2020 Texas Instruments Incorporated - http://www.ti.com
 *  Author: Peter Ujfalusi <peter.ujfalusi@ti.com>
 */

#समावेश <linux/clk.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "davinci-mcasp.h"

/*
 * Maximum number of configuration entries क्रम prefixes:
 * CPB: 2 (mcasp10 + codec)
 * IVI: 3 (mcasp0 + 2x codec)
 */
#घोषणा J721E_CODEC_CONF_COUNT	5

#घोषणा J721E_AUDIO_DOMAIN_CPB	0
#घोषणा J721E_AUDIO_DOMAIN_IVI	1

#घोषणा J721E_CLK_PARENT_48000	0
#घोषणा J721E_CLK_PARENT_44100	1

#घोषणा J721E_MAX_CLK_HSDIV	128
#घोषणा PCM1368A_MAX_SYSCLK	36864000

#घोषणा J721E_DAI_FMT		(SND_SOC_DAIFMT_RIGHT_J | \
				 SND_SOC_DAIFMT_NB_NF |   \
				 SND_SOC_DAIFMT_CBS_CFS)

क्रमागत j721e_board_type अणु
	J721E_BOARD_CPB = 1,
	J721E_BOARD_CPB_IVI,
पूर्ण;

काष्ठा j721e_audio_match_data अणु
	क्रमागत j721e_board_type board_type;
	पूर्णांक num_links;
	अचिन्हित पूर्णांक pll_rates[2];
पूर्ण;

अटल अचिन्हित पूर्णांक ratios_क्रम_pcm3168a[] = अणु
	256,
	512,
	768,
पूर्ण;

काष्ठा j721e_audio_घड़ीs अणु
	काष्ठा clk *target;
	काष्ठा clk *parent[2];
पूर्ण;

काष्ठा j721e_audio_करोमुख्य अणु
	काष्ठा j721e_audio_घड़ीs codec;
	काष्ठा j721e_audio_घड़ीs mcasp;
	पूर्णांक parent_clk_id;

	पूर्णांक active;
	अचिन्हित पूर्णांक active_link;
	अचिन्हित पूर्णांक rate;
पूर्ण;

काष्ठा j721e_priv अणु
	काष्ठा device *dev;
	काष्ठा snd_soc_card card;
	काष्ठा snd_soc_dai_link *dai_links;
	काष्ठा snd_soc_codec_conf codec_conf[J721E_CODEC_CONF_COUNT];
	काष्ठा snd_पूर्णांकerval rate_range;
	स्थिर काष्ठा j721e_audio_match_data *match_data;
	u32 pll_rates[2];
	अचिन्हित पूर्णांक hsभाग_rates[2];

	काष्ठा j721e_audio_करोमुख्य audio_करोमुख्यs[2];

	काष्ठा mutex mutex;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget j721e_cpb_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("CPB Stereo HP 1", शून्य),
	SND_SOC_DAPM_HP("CPB Stereo HP 2", शून्य),
	SND_SOC_DAPM_HP("CPB Stereo HP 3", शून्य),
	SND_SOC_DAPM_LINE("CPB Line Out", शून्य),
	SND_SOC_DAPM_MIC("CPB Stereo Mic 1", शून्य),
	SND_SOC_DAPM_MIC("CPB Stereo Mic 2", शून्य),
	SND_SOC_DAPM_LINE("CPB Line In", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route j721e_cpb_dapm_routes[] = अणु
	अणु"CPB Stereo HP 1", शून्य, "codec-1 AOUT1L"पूर्ण,
	अणु"CPB Stereo HP 1", शून्य, "codec-1 AOUT1R"पूर्ण,
	अणु"CPB Stereo HP 2", शून्य, "codec-1 AOUT2L"पूर्ण,
	अणु"CPB Stereo HP 2", शून्य, "codec-1 AOUT2R"पूर्ण,
	अणु"CPB Stereo HP 3", शून्य, "codec-1 AOUT3L"पूर्ण,
	अणु"CPB Stereo HP 3", शून्य, "codec-1 AOUT3R"पूर्ण,
	अणु"CPB Line Out", शून्य, "codec-1 AOUT4L"पूर्ण,
	अणु"CPB Line Out", शून्य, "codec-1 AOUT4R"पूर्ण,

	अणु"codec-1 AIN1L", शून्य, "CPB Stereo Mic 1"पूर्ण,
	अणु"codec-1 AIN1R", शून्य, "CPB Stereo Mic 1"पूर्ण,
	अणु"codec-1 AIN2L", शून्य, "CPB Stereo Mic 2"पूर्ण,
	अणु"codec-1 AIN2R", शून्य, "CPB Stereo Mic 2"पूर्ण,
	अणु"codec-1 AIN3L", शून्य, "CPB Line In"पूर्ण,
	अणु"codec-1 AIN3R", शून्य, "CPB Line In"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget j721e_ivi_codec_a_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("IVI A Line Out 1", शून्य),
	SND_SOC_DAPM_LINE("IVI A Line Out 2", शून्य),
	SND_SOC_DAPM_LINE("IVI A Line Out 3", शून्य),
	SND_SOC_DAPM_LINE("IVI A Line Out 4", शून्य),
	SND_SOC_DAPM_MIC("IVI A Stereo Mic 1", शून्य),
	SND_SOC_DAPM_MIC("IVI A Stereo Mic 2", शून्य),
	SND_SOC_DAPM_LINE("IVI A Line In", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route j721e_codec_a_dapm_routes[] = अणु
	अणु"IVI A Line Out 1", शून्य, "codec-a AOUT1L"पूर्ण,
	अणु"IVI A Line Out 1", शून्य, "codec-a AOUT1R"पूर्ण,
	अणु"IVI A Line Out 2", शून्य, "codec-a AOUT2L"पूर्ण,
	अणु"IVI A Line Out 2", शून्य, "codec-a AOUT2R"पूर्ण,
	अणु"IVI A Line Out 3", शून्य, "codec-a AOUT3L"पूर्ण,
	अणु"IVI A Line Out 3", शून्य, "codec-a AOUT3R"पूर्ण,
	अणु"IVI A Line Out 4", शून्य, "codec-a AOUT4L"पूर्ण,
	अणु"IVI A Line Out 4", शून्य, "codec-a AOUT4R"पूर्ण,

	अणु"codec-a AIN1L", शून्य, "IVI A Stereo Mic 1"पूर्ण,
	अणु"codec-a AIN1R", शून्य, "IVI A Stereo Mic 1"पूर्ण,
	अणु"codec-a AIN2L", शून्य, "IVI A Stereo Mic 2"पूर्ण,
	अणु"codec-a AIN2R", शून्य, "IVI A Stereo Mic 2"पूर्ण,
	अणु"codec-a AIN3L", शून्य, "IVI A Line In"पूर्ण,
	अणु"codec-a AIN3R", शून्य, "IVI A Line In"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget j721e_ivi_codec_b_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_LINE("IVI B Line Out 1", शून्य),
	SND_SOC_DAPM_LINE("IVI B Line Out 2", शून्य),
	SND_SOC_DAPM_LINE("IVI B Line Out 3", शून्य),
	SND_SOC_DAPM_LINE("IVI B Line Out 4", शून्य),
	SND_SOC_DAPM_MIC("IVI B Stereo Mic 1", शून्य),
	SND_SOC_DAPM_MIC("IVI B Stereo Mic 2", शून्य),
	SND_SOC_DAPM_LINE("IVI B Line In", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route j721e_codec_b_dapm_routes[] = अणु
	अणु"IVI B Line Out 1", शून्य, "codec-b AOUT1L"पूर्ण,
	अणु"IVI B Line Out 1", शून्य, "codec-b AOUT1R"पूर्ण,
	अणु"IVI B Line Out 2", शून्य, "codec-b AOUT2L"पूर्ण,
	अणु"IVI B Line Out 2", शून्य, "codec-b AOUT2R"पूर्ण,
	अणु"IVI B Line Out 3", शून्य, "codec-b AOUT3L"पूर्ण,
	अणु"IVI B Line Out 3", शून्य, "codec-b AOUT3R"पूर्ण,
	अणु"IVI B Line Out 4", शून्य, "codec-b AOUT4L"पूर्ण,
	अणु"IVI B Line Out 4", शून्य, "codec-b AOUT4R"पूर्ण,

	अणु"codec-b AIN1L", शून्य, "IVI B Stereo Mic 1"पूर्ण,
	अणु"codec-b AIN1R", शून्य, "IVI B Stereo Mic 1"पूर्ण,
	अणु"codec-b AIN2L", शून्य, "IVI B Stereo Mic 2"पूर्ण,
	अणु"codec-b AIN2R", शून्य, "IVI B Stereo Mic 2"पूर्ण,
	अणु"codec-b AIN3L", शून्य, "IVI B Line In"पूर्ण,
	अणु"codec-b AIN3R", शून्य, "IVI B Line In"पूर्ण,
पूर्ण;

अटल पूर्णांक j721e_configure_refclk(काष्ठा j721e_priv *priv,
				  अचिन्हित पूर्णांक audio_करोमुख्य, अचिन्हित पूर्णांक rate)
अणु
	काष्ठा j721e_audio_करोमुख्य *करोमुख्य = &priv->audio_करोमुख्यs[audio_करोमुख्य];
	अचिन्हित पूर्णांक scki;
	पूर्णांक ret = -EINVAL;
	पूर्णांक i, clk_id;

	अगर (!(rate % 8000) && priv->pll_rates[J721E_CLK_PARENT_48000])
		clk_id = J721E_CLK_PARENT_48000;
	अन्यथा अगर (!(rate % 11025) && priv->pll_rates[J721E_CLK_PARENT_44100])
		clk_id = J721E_CLK_PARENT_44100;
	अन्यथा
		वापस ret;

	क्रम (i = 0; i < ARRAY_SIZE(ratios_क्रम_pcm3168a); i++) अणु
		scki = ratios_क्रम_pcm3168a[i] * rate;

		अगर (priv->pll_rates[clk_id] / scki <= J721E_MAX_CLK_HSDIV) अणु
			ret = 0;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (ret) अणु
		dev_err(priv->dev, "No valid clock configuration for %u Hz\n",
			rate);
		वापस ret;
	पूर्ण

	अगर (priv->hsभाग_rates[करोमुख्य->parent_clk_id] != scki) अणु
		dev_dbg(priv->dev,
			"%s configuration for %u Hz: %s, %dxFS (SCKI: %u Hz)\n",
			audio_करोमुख्य == J721E_AUDIO_DOMAIN_CPB ? "CPB" : "IVI",
			rate,
			clk_id == J721E_CLK_PARENT_48000 ? "PLL4" : "PLL15",
			ratios_क्रम_pcm3168a[i], scki);

		अगर (करोमुख्य->parent_clk_id != clk_id) अणु
			ret = clk_set_parent(करोमुख्य->codec.target,
					     करोमुख्य->codec.parent[clk_id]);
			अगर (ret)
				वापस ret;

			ret = clk_set_parent(करोमुख्य->mcasp.target,
					     करोमुख्य->mcasp.parent[clk_id]);
			अगर (ret)
				वापस ret;

			करोमुख्य->parent_clk_id = clk_id;
		पूर्ण

		ret = clk_set_rate(करोमुख्य->codec.target, scki);
		अगर (ret) अणु
			dev_err(priv->dev, "codec set rate failed for %u Hz\n",
				scki);
			वापस ret;
		पूर्ण

		ret = clk_set_rate(करोमुख्य->mcasp.target, scki);
		अगर (!ret) अणु
			priv->hsभाग_rates[करोमुख्य->parent_clk_id] = scki;
		पूर्ण अन्यथा अणु
			dev_err(priv->dev, "mcasp set rate failed for %u Hz\n",
				scki);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक j721e_rule_rate(काष्ठा snd_pcm_hw_params *params,
			   काष्ठा snd_pcm_hw_rule *rule)
अणु
	काष्ठा snd_पूर्णांकerval *t = rule->निजी;

	वापस snd_पूर्णांकerval_refine(hw_param_पूर्णांकerval(params, rule->var), t);
पूर्ण

अटल पूर्णांक j721e_audio_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा j721e_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	अचिन्हित पूर्णांक करोमुख्य_id = rtd->dai_link->id;
	काष्ठा j721e_audio_करोमुख्य *करोमुख्य = &priv->audio_करोमुख्यs[करोमुख्य_id];
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai;
	अचिन्हित पूर्णांक active_rate;
	पूर्णांक ret = 0;
	पूर्णांक i;

	mutex_lock(&priv->mutex);

	करोमुख्य->active++;

	अगर (priv->audio_करोमुख्यs[J721E_AUDIO_DOMAIN_CPB].rate)
		active_rate = priv->audio_करोमुख्यs[J721E_AUDIO_DOMAIN_CPB].rate;
	अन्यथा
		active_rate = priv->audio_करोमुख्यs[J721E_AUDIO_DOMAIN_IVI].rate;

	अगर (active_rate)
		ret = snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
						   SNDRV_PCM_HW_PARAM_RATE,
						   active_rate);
	अन्यथा
		ret = snd_pcm_hw_rule_add(substream->runसमय, 0,
					  SNDRV_PCM_HW_PARAM_RATE,
					  j721e_rule_rate, &priv->rate_range,
					  SNDRV_PCM_HW_PARAM_RATE, -1);

	mutex_unlock(&priv->mutex);

	अगर (ret)
		वापस ret;

	/* Reset TDM slots to 32 */
	ret = snd_soc_dai_set_tdm_slot(cpu_dai, 0x3, 0x3, 2, 32);
	अगर (ret && ret != -ENOTSUPP)
		वापस ret;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x3, 0x3, 2, 32);
		अगर (ret && ret != -ENOTSUPP)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक j721e_audio_hw_params(काष्ठा snd_pcm_substream *substream,
				 काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा j721e_priv *priv = snd_soc_card_get_drvdata(card);
	अचिन्हित पूर्णांक करोमुख्य_id = rtd->dai_link->id;
	काष्ठा j721e_audio_करोमुख्य *करोमुख्य = &priv->audio_करोमुख्यs[करोमुख्य_id];
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai;
	अचिन्हित पूर्णांक sysclk_rate;
	पूर्णांक slot_width = 32;
	पूर्णांक ret;
	पूर्णांक i;

	mutex_lock(&priv->mutex);

	अगर (करोमुख्य->rate && करोमुख्य->rate != params_rate(params)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (params_width(params) == 16)
		slot_width = 16;

	ret = snd_soc_dai_set_tdm_slot(cpu_dai, 0x3, 0x3, 2, slot_width);
	अगर (ret && ret != -ENOTSUPP)
		जाओ out;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x3, 0x3, 2,
					       slot_width);
		अगर (ret && ret != -ENOTSUPP)
			जाओ out;
	पूर्ण

	ret = j721e_configure_refclk(priv, करोमुख्य_id, params_rate(params));
	अगर (ret)
		जाओ out;

	sysclk_rate = priv->hsभाग_rates[करोमुख्य->parent_clk_id];
	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_sysclk(codec_dai, 0, sysclk_rate,
					     SND_SOC_CLOCK_IN);
		अगर (ret && ret != -ENOTSUPP) अणु
			dev_err(priv->dev,
				"codec set_sysclk failed for %u Hz\n",
				sysclk_rate);
			जाओ out;
		पूर्ण
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, MCASP_CLK_HCLK_AUXCLK,
				     sysclk_rate, SND_SOC_CLOCK_IN);

	अगर (ret && ret != -ENOTSUPP) अणु
		dev_err(priv->dev, "mcasp set_sysclk failed for %u Hz\n",
			sysclk_rate);
	पूर्ण अन्यथा अणु
		करोमुख्य->rate = params_rate(params);
		ret = 0;
	पूर्ण

out:
	mutex_unlock(&priv->mutex);
	वापस ret;
पूर्ण

अटल व्योम j721e_audio_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा j721e_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	अचिन्हित पूर्णांक करोमुख्य_id = rtd->dai_link->id;
	काष्ठा j721e_audio_करोमुख्य *करोमुख्य = &priv->audio_करोमुख्यs[करोमुख्य_id];

	mutex_lock(&priv->mutex);

	करोमुख्य->active--;
	अगर (!करोमुख्य->active) अणु
		करोमुख्य->rate = 0;
		करोमुख्य->active_link = 0;
	पूर्ण

	mutex_unlock(&priv->mutex);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops j721e_audio_ops = अणु
	.startup = j721e_audio_startup,
	.hw_params = j721e_audio_hw_params,
	.shutकरोwn = j721e_audio_shutकरोwn,
पूर्ण;

अटल पूर्णांक j721e_audio_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा j721e_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	अचिन्हित पूर्णांक करोमुख्य_id = rtd->dai_link->id;
	काष्ठा j721e_audio_करोमुख्य *करोमुख्य = &priv->audio_करोमुख्यs[करोमुख्य_id];
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai;
	अचिन्हित पूर्णांक sysclk_rate;
	पूर्णांक i, ret;

	/* Set up initial घड़ी configuration */
	ret = j721e_configure_refclk(priv, करोमुख्य_id, 48000);
	अगर (ret)
		वापस ret;

	sysclk_rate = priv->hsभाग_rates[करोमुख्य->parent_clk_id];
	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_sysclk(codec_dai, 0, sysclk_rate,
					     SND_SOC_CLOCK_IN);
		अगर (ret && ret != -ENOTSUPP)
			वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, MCASP_CLK_HCLK_AUXCLK,
				     sysclk_rate, SND_SOC_CLOCK_IN);
	अगर (ret && ret != -ENOTSUPP)
		वापस ret;

	/* Set initial tdm slots */
	ret = snd_soc_dai_set_tdm_slot(cpu_dai, 0x3, 0x3, 2, 32);
	अगर (ret && ret != -ENOTSUPP)
		वापस ret;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x3, 0x3, 2, 32);
		अगर (ret && ret != -ENOTSUPP)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक j721e_audio_init_ivi(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm = &rtd->card->dapm;

	snd_soc_dapm_new_controls(dapm, j721e_ivi_codec_a_dapm_widमाला_लो,
				  ARRAY_SIZE(j721e_ivi_codec_a_dapm_widमाला_लो));
	snd_soc_dapm_add_routes(dapm, j721e_codec_a_dapm_routes,
				ARRAY_SIZE(j721e_codec_a_dapm_routes));
	snd_soc_dapm_new_controls(dapm, j721e_ivi_codec_b_dapm_widमाला_लो,
				  ARRAY_SIZE(j721e_ivi_codec_b_dapm_widमाला_लो));
	snd_soc_dapm_add_routes(dapm, j721e_codec_b_dapm_routes,
				ARRAY_SIZE(j721e_codec_b_dapm_routes));

	वापस j721e_audio_init(rtd);
पूर्ण

अटल पूर्णांक j721e_get_घड़ीs(काष्ठा device *dev,
			    काष्ठा j721e_audio_घड़ीs *घड़ीs, अक्षर *prefix)
अणु
	काष्ठा clk *parent;
	अक्षर *clk_name;
	पूर्णांक ret;

	घड़ीs->target = devm_clk_get(dev, prefix);
	अगर (IS_ERR(घड़ीs->target)) अणु
		ret = PTR_ERR(घड़ीs->target);
		अगर (ret != -EPROBE_DEFER)
			dev_err(dev, "failed to acquire %s: %d\n",
				prefix, ret);
		वापस ret;
	पूर्ण

	clk_name = kaप्र_लिखो(GFP_KERNEL, "%s-48000", prefix);
	अगर (clk_name) अणु
		parent = devm_clk_get(dev, clk_name);
		kमुक्त(clk_name);
		अगर (IS_ERR(parent)) अणु
			ret = PTR_ERR(parent);
			अगर (ret == -EPROBE_DEFER)
				वापस ret;

			dev_dbg(dev, "no 48KHz parent for %s: %d\n", prefix, ret);
			parent = शून्य;
		पूर्ण
		घड़ीs->parent[J721E_CLK_PARENT_48000] = parent;
	पूर्ण अन्यथा अणु
		वापस -ENOMEM;
	पूर्ण

	clk_name = kaप्र_लिखो(GFP_KERNEL, "%s-44100", prefix);
	अगर (clk_name) अणु
		parent = devm_clk_get(dev, clk_name);
		kमुक्त(clk_name);
		अगर (IS_ERR(parent)) अणु
			ret = PTR_ERR(parent);
			अगर (ret == -EPROBE_DEFER)
				वापस ret;

			dev_dbg(dev, "no 44.1KHz parent for %s: %d\n", prefix, ret);
			parent = शून्य;
		पूर्ण
		घड़ीs->parent[J721E_CLK_PARENT_44100] = parent;
	पूर्ण अन्यथा अणु
		वापस -ENOMEM;
	पूर्ण

	अगर (!घड़ीs->parent[J721E_CLK_PARENT_44100] &&
	    !घड़ीs->parent[J721E_CLK_PARENT_48000]) अणु
		dev_err(dev, "At least one parent clock is needed for %s\n",
			prefix);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा j721e_audio_match_data j721e_cpb_data = अणु
	.board_type = J721E_BOARD_CPB,
	.num_links = 2, /* CPB pcm3168a */
	.pll_rates = अणु
		[J721E_CLK_PARENT_44100] = 1083801600, /* PLL15 */
		[J721E_CLK_PARENT_48000] = 1179648000, /* PLL4 */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा j721e_audio_match_data j721e_cpb_ivi_data = अणु
	.board_type = J721E_BOARD_CPB_IVI,
	.num_links = 4, /* CPB pcm3168a + 2x pcm3168a on IVI */
	.pll_rates = अणु
		[J721E_CLK_PARENT_44100] = 1083801600, /* PLL15 */
		[J721E_CLK_PARENT_48000] = 1179648000, /* PLL4 */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा j721e_audio_match_data j7200_cpb_data = अणु
	.board_type = J721E_BOARD_CPB,
	.num_links = 2, /* CPB pcm3168a */
	.pll_rates = अणु
		[J721E_CLK_PARENT_48000] = 2359296000u, /* PLL4 */
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा of_device_id j721e_audio_of_match[] = अणु
	अणु
		.compatible = "ti,j721e-cpb-audio",
		.data = &j721e_cpb_data,
	पूर्ण, अणु
		.compatible = "ti,j721e-cpb-ivi-audio",
		.data = &j721e_cpb_ivi_data,
	पूर्ण, अणु
		.compatible = "ti,j7200-cpb-audio",
		.data = &j7200_cpb_data,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, j721e_audio_of_match);

अटल पूर्णांक j721e_calculate_rate_range(काष्ठा j721e_priv *priv)
अणु
	स्थिर काष्ठा j721e_audio_match_data *match_data = priv->match_data;
	काष्ठा j721e_audio_घड़ीs *करोमुख्य_घड़ीs;
	अचिन्हित पूर्णांक min_rate, max_rate, pll_rate;
	काष्ठा clk *pll;

	करोमुख्य_घड़ीs = &priv->audio_करोमुख्यs[J721E_AUDIO_DOMAIN_CPB].mcasp;

	pll = clk_get_parent(करोमुख्य_घड़ीs->parent[J721E_CLK_PARENT_44100]);
	अगर (IS_ERR_OR_शून्य(pll)) अणु
		priv->pll_rates[J721E_CLK_PARENT_44100] =
				match_data->pll_rates[J721E_CLK_PARENT_44100];
	पूर्ण अन्यथा अणु
		priv->pll_rates[J721E_CLK_PARENT_44100] = clk_get_rate(pll);
		clk_put(pll);
	पूर्ण

	pll = clk_get_parent(करोमुख्य_घड़ीs->parent[J721E_CLK_PARENT_48000]);
	अगर (IS_ERR_OR_शून्य(pll)) अणु
		priv->pll_rates[J721E_CLK_PARENT_48000] =
				match_data->pll_rates[J721E_CLK_PARENT_48000];
	पूर्ण अन्यथा अणु
		priv->pll_rates[J721E_CLK_PARENT_48000] = clk_get_rate(pll);
		clk_put(pll);
	पूर्ण

	अगर (!priv->pll_rates[J721E_CLK_PARENT_44100] &&
	    !priv->pll_rates[J721E_CLK_PARENT_48000]) अणु
		dev_err(priv->dev, "At least one PLL is needed\n");
		वापस -EINVAL;
	पूर्ण

	अगर (priv->pll_rates[J721E_CLK_PARENT_44100])
		pll_rate = priv->pll_rates[J721E_CLK_PARENT_44100];
	अन्यथा
		pll_rate = priv->pll_rates[J721E_CLK_PARENT_48000];

	min_rate = pll_rate / J721E_MAX_CLK_HSDIV;
	min_rate /= ratios_क्रम_pcm3168a[ARRAY_SIZE(ratios_क्रम_pcm3168a) - 1];

	अगर (priv->pll_rates[J721E_CLK_PARENT_48000])
		pll_rate = priv->pll_rates[J721E_CLK_PARENT_48000];
	अन्यथा
		pll_rate = priv->pll_rates[J721E_CLK_PARENT_44100];

	अगर (pll_rate > PCM1368A_MAX_SYSCLK)
		pll_rate = PCM1368A_MAX_SYSCLK;

	max_rate = pll_rate / ratios_क्रम_pcm3168a[0];

	snd_पूर्णांकerval_any(&priv->rate_range);
	priv->rate_range.min = min_rate;
	priv->rate_range.max = max_rate;

	वापस 0;
पूर्ण

अटल पूर्णांक j721e_soc_probe_cpb(काष्ठा j721e_priv *priv, पूर्णांक *link_idx,
			       पूर्णांक *conf_idx)
अणु
	काष्ठा device_node *node = priv->dev->of_node;
	काष्ठा snd_soc_dai_link_component *compnent;
	काष्ठा device_node *dai_node, *codec_node;
	काष्ठा j721e_audio_करोमुख्य *करोमुख्य;
	पूर्णांक comp_count, comp_idx;
	पूर्णांक ret;

	dai_node = of_parse_phandle(node, "ti,cpb-mcasp", 0);
	अगर (!dai_node) अणु
		dev_err(priv->dev, "CPB McASP node is not provided\n");
		वापस -EINVAL;
	पूर्ण

	codec_node = of_parse_phandle(node, "ti,cpb-codec", 0);
	अगर (!codec_node) अणु
		dev_err(priv->dev, "CPB codec node is not provided\n");
		वापस -EINVAL;
	पूर्ण

	करोमुख्य = &priv->audio_करोमुख्यs[J721E_AUDIO_DOMAIN_CPB];
	ret = j721e_get_घड़ीs(priv->dev, &करोमुख्य->codec, "cpb-codec-scki");
	अगर (ret)
		वापस ret;

	ret = j721e_get_घड़ीs(priv->dev, &करोमुख्य->mcasp, "cpb-mcasp-auxclk");
	अगर (ret)
		वापस ret;

	/*
	 * Common Processor Board, two links
	 * Link 1: McASP10 -> pcm3168a_1 DAC
	 * Link 2: McASP10 <- pcm3168a_1 ADC
	 */
	comp_count = 6;
	compnent = devm_kzalloc(priv->dev, comp_count * माप(*compnent),
				GFP_KERNEL);
	अगर (!compnent)
		वापस -ENOMEM;

	comp_idx = 0;
	priv->dai_links[*link_idx].cpus = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_cpus = 1;
	priv->dai_links[*link_idx].codecs = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_codecs = 1;
	priv->dai_links[*link_idx].platक्रमms = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_platक्रमms = 1;

	priv->dai_links[*link_idx].name = "CPB PCM3168A Playback";
	priv->dai_links[*link_idx].stream_name = "CPB PCM3168A Analog";
	priv->dai_links[*link_idx].cpus->of_node = dai_node;
	priv->dai_links[*link_idx].platक्रमms->of_node = dai_node;
	priv->dai_links[*link_idx].codecs->of_node = codec_node;
	priv->dai_links[*link_idx].codecs->dai_name = "pcm3168a-dac";
	priv->dai_links[*link_idx].playback_only = 1;
	priv->dai_links[*link_idx].id = J721E_AUDIO_DOMAIN_CPB;
	priv->dai_links[*link_idx].dai_fmt = J721E_DAI_FMT;
	priv->dai_links[*link_idx].init = j721e_audio_init;
	priv->dai_links[*link_idx].ops = &j721e_audio_ops;
	(*link_idx)++;

	priv->dai_links[*link_idx].cpus = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_cpus = 1;
	priv->dai_links[*link_idx].codecs = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_codecs = 1;
	priv->dai_links[*link_idx].platक्रमms = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_platक्रमms = 1;

	priv->dai_links[*link_idx].name = "CPB PCM3168A Capture";
	priv->dai_links[*link_idx].stream_name = "CPB PCM3168A Analog";
	priv->dai_links[*link_idx].cpus->of_node = dai_node;
	priv->dai_links[*link_idx].platक्रमms->of_node = dai_node;
	priv->dai_links[*link_idx].codecs->of_node = codec_node;
	priv->dai_links[*link_idx].codecs->dai_name = "pcm3168a-adc";
	priv->dai_links[*link_idx].capture_only = 1;
	priv->dai_links[*link_idx].id = J721E_AUDIO_DOMAIN_CPB;
	priv->dai_links[*link_idx].dai_fmt = J721E_DAI_FMT;
	priv->dai_links[*link_idx].init = j721e_audio_init;
	priv->dai_links[*link_idx].ops = &j721e_audio_ops;
	(*link_idx)++;

	priv->codec_conf[*conf_idx].dlc.of_node = codec_node;
	priv->codec_conf[*conf_idx].name_prefix = "codec-1";
	(*conf_idx)++;
	priv->codec_conf[*conf_idx].dlc.of_node = dai_node;
	priv->codec_conf[*conf_idx].name_prefix = "McASP10";
	(*conf_idx)++;

	वापस 0;
पूर्ण

अटल पूर्णांक j721e_soc_probe_ivi(काष्ठा j721e_priv *priv, पूर्णांक *link_idx,
			       पूर्णांक *conf_idx)
अणु
	काष्ठा device_node *node = priv->dev->of_node;
	काष्ठा snd_soc_dai_link_component *compnent;
	काष्ठा device_node *dai_node, *codeca_node, *codecb_node;
	काष्ठा j721e_audio_करोमुख्य *करोमुख्य;
	पूर्णांक comp_count, comp_idx;
	पूर्णांक ret;

	अगर (priv->match_data->board_type != J721E_BOARD_CPB_IVI)
		वापस 0;

	dai_node = of_parse_phandle(node, "ti,ivi-mcasp", 0);
	अगर (!dai_node) अणु
		dev_err(priv->dev, "IVI McASP node is not provided\n");
		वापस -EINVAL;
	पूर्ण

	codeca_node = of_parse_phandle(node, "ti,ivi-codec-a", 0);
	अगर (!codeca_node) अणु
		dev_err(priv->dev, "IVI codec-a node is not provided\n");
		वापस -EINVAL;
	पूर्ण

	codecb_node = of_parse_phandle(node, "ti,ivi-codec-b", 0);
	अगर (!codecb_node) अणु
		dev_warn(priv->dev, "IVI codec-b node is not provided\n");
		वापस 0;
	पूर्ण

	करोमुख्य = &priv->audio_करोमुख्यs[J721E_AUDIO_DOMAIN_IVI];
	ret = j721e_get_घड़ीs(priv->dev, &करोमुख्य->codec, "ivi-codec-scki");
	अगर (ret)
		वापस ret;

	ret = j721e_get_घड़ीs(priv->dev, &करोमुख्य->mcasp, "ivi-mcasp-auxclk");
	अगर (ret)
		वापस ret;

	/*
	 * IVI extension, two links
	 * Link 1: McASP0 -> pcm3168a_a DAC
	 *		  \> pcm3168a_b DAC
	 * Link 2: McASP0 <- pcm3168a_a ADC
	 *		   \ pcm3168a_b ADC
	 */
	comp_count = 8;
	compnent = devm_kzalloc(priv->dev, comp_count * माप(*compnent),
				GFP_KERNEL);
	अगर (!compnent)
		वापस -ENOMEM;

	comp_idx = 0;
	priv->dai_links[*link_idx].cpus = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_cpus = 1;
	priv->dai_links[*link_idx].platक्रमms = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_platक्रमms = 1;
	priv->dai_links[*link_idx].codecs = &compnent[comp_idx];
	priv->dai_links[*link_idx].num_codecs = 2;
	comp_idx += 2;

	priv->dai_links[*link_idx].name = "IVI 2xPCM3168A Playback";
	priv->dai_links[*link_idx].stream_name = "IVI 2xPCM3168A Analog";
	priv->dai_links[*link_idx].cpus->of_node = dai_node;
	priv->dai_links[*link_idx].platक्रमms->of_node = dai_node;
	priv->dai_links[*link_idx].codecs[0].of_node = codeca_node;
	priv->dai_links[*link_idx].codecs[0].dai_name = "pcm3168a-dac";
	priv->dai_links[*link_idx].codecs[1].of_node = codecb_node;
	priv->dai_links[*link_idx].codecs[1].dai_name = "pcm3168a-dac";
	priv->dai_links[*link_idx].playback_only = 1;
	priv->dai_links[*link_idx].id = J721E_AUDIO_DOMAIN_IVI;
	priv->dai_links[*link_idx].dai_fmt = J721E_DAI_FMT;
	priv->dai_links[*link_idx].init = j721e_audio_init_ivi;
	priv->dai_links[*link_idx].ops = &j721e_audio_ops;
	(*link_idx)++;

	priv->dai_links[*link_idx].cpus = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_cpus = 1;
	priv->dai_links[*link_idx].platक्रमms = &compnent[comp_idx++];
	priv->dai_links[*link_idx].num_platक्रमms = 1;
	priv->dai_links[*link_idx].codecs = &compnent[comp_idx];
	priv->dai_links[*link_idx].num_codecs = 2;

	priv->dai_links[*link_idx].name = "IVI 2xPCM3168A Capture";
	priv->dai_links[*link_idx].stream_name = "IVI 2xPCM3168A Analog";
	priv->dai_links[*link_idx].cpus->of_node = dai_node;
	priv->dai_links[*link_idx].platक्रमms->of_node = dai_node;
	priv->dai_links[*link_idx].codecs[0].of_node = codeca_node;
	priv->dai_links[*link_idx].codecs[0].dai_name = "pcm3168a-adc";
	priv->dai_links[*link_idx].codecs[1].of_node = codecb_node;
	priv->dai_links[*link_idx].codecs[1].dai_name = "pcm3168a-adc";
	priv->dai_links[*link_idx].capture_only = 1;
	priv->dai_links[*link_idx].id = J721E_AUDIO_DOMAIN_IVI;
	priv->dai_links[*link_idx].dai_fmt = J721E_DAI_FMT;
	priv->dai_links[*link_idx].init = j721e_audio_init;
	priv->dai_links[*link_idx].ops = &j721e_audio_ops;
	(*link_idx)++;

	priv->codec_conf[*conf_idx].dlc.of_node = codeca_node;
	priv->codec_conf[*conf_idx].name_prefix = "codec-a";
	(*conf_idx)++;

	priv->codec_conf[*conf_idx].dlc.of_node = codecb_node;
	priv->codec_conf[*conf_idx].name_prefix = "codec-b";
	(*conf_idx)++;

	priv->codec_conf[*conf_idx].dlc.of_node = dai_node;
	priv->codec_conf[*conf_idx].name_prefix = "McASP0";
	(*conf_idx)++;

	वापस 0;
पूर्ण

अटल पूर्णांक j721e_soc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *node = pdev->dev.of_node;
	काष्ठा snd_soc_card *card;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा j721e_priv *priv;
	पूर्णांक link_cnt, conf_cnt, ret;

	अगर (!node) अणु
		dev_err(&pdev->dev, "of node is missing.\n");
		वापस -ENODEV;
	पूर्ण

	match = of_match_node(j721e_audio_of_match, node);
	अगर (!match) अणु
		dev_err(&pdev->dev, "No compatible match found\n");
		वापस -ENODEV;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	priv->match_data = match->data;

	priv->dai_links = devm_kसुस्मृति(&pdev->dev, priv->match_data->num_links,
				       माप(*priv->dai_links), GFP_KERNEL);
	अगर (!priv->dai_links)
		वापस -ENOMEM;

	priv->audio_करोमुख्यs[J721E_AUDIO_DOMAIN_CPB].parent_clk_id = -1;
	priv->audio_करोमुख्यs[J721E_AUDIO_DOMAIN_IVI].parent_clk_id = -1;
	priv->dev = &pdev->dev;
	card = &priv->card;
	card->dev = &pdev->dev;
	card->owner = THIS_MODULE;
	card->dapm_widमाला_लो = j721e_cpb_dapm_widमाला_लो;
	card->num_dapm_widमाला_लो = ARRAY_SIZE(j721e_cpb_dapm_widमाला_लो);
	card->dapm_routes = j721e_cpb_dapm_routes;
	card->num_dapm_routes = ARRAY_SIZE(j721e_cpb_dapm_routes);
	card->fully_routed = 1;

	अगर (snd_soc_of_parse_card_name(card, "model")) अणु
		dev_err(&pdev->dev, "Card name is not provided\n");
		वापस -ENODEV;
	पूर्ण

	link_cnt = 0;
	conf_cnt = 0;
	ret = j721e_soc_probe_cpb(priv, &link_cnt, &conf_cnt);
	अगर (ret)
		वापस ret;

	ret = j721e_soc_probe_ivi(priv, &link_cnt, &conf_cnt);
	अगर (ret)
		वापस ret;

	card->dai_link = priv->dai_links;
	card->num_links = link_cnt;

	card->codec_conf = priv->codec_conf;
	card->num_configs = conf_cnt;

	ret = j721e_calculate_rate_range(priv);
	अगर (ret)
		वापस ret;

	snd_soc_card_set_drvdata(card, priv);

	mutex_init(&priv->mutex);
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "devm_snd_soc_register_card() failed: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver j721e_soc_driver = अणु
	.driver = अणु
		.name = "j721e-audio",
		.pm = &snd_soc_pm_ops,
		.of_match_table = j721e_audio_of_match,
	पूर्ण,
	.probe = j721e_soc_probe,
पूर्ण;

module_platक्रमm_driver(j721e_soc_driver);

MODULE_AUTHOR("Peter Ujfalusi <peter.ujfalusi@ti.com>");
MODULE_DESCRIPTION("ASoC machine driver for j721e Common Processor Board");
MODULE_LICENSE("GPL v2");
