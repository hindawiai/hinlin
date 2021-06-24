<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt8192-mt6359-rt1015-rt5682.c  --
//	MT8192-MT6359-RT1015-RT6358 ALSA SoC machine driver
//
// Copyright (c) 2020 MediaTek Inc.
// Author: Jiaxin Yu <jiaxin.yu@mediatek.com>
//

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pm_runसमय.स>
#समावेश <sound/jack.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/rt5682.h>
#समावेश <sound/soc.h>

#समावेश "../../codecs/mt6359.h"
#समावेश "../../codecs/rt1015.h"
#समावेश "../../codecs/rt5682.h"
#समावेश "../common/mtk-afe-platform-driver.h"
#समावेश "mt8192-afe-common.h"
#समावेश "mt8192-afe-clk.h"
#समावेश "mt8192-afe-gpio.h"

#घोषणा RT1015_CODEC_DAI	"rt1015-aif"
#घोषणा RT1015_DEV0_NAME	"rt1015.1-0028"
#घोषणा RT1015_DEV1_NAME	"rt1015.1-0029"

#घोषणा RT5682_CODEC_DAI	"rt5682-aif1"
#घोषणा RT5682_DEV0_NAME	"rt5682.1-001a"

काष्ठा mt8192_mt6359_priv अणु
	काष्ठा snd_soc_jack headset_jack;
	काष्ठा snd_soc_jack hdmi_jack;
पूर्ण;

अटल पूर्णांक mt8192_rt1015_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai;
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक mclk_fs_ratio = 128;
	अचिन्हित पूर्णांक mclk_fs = rate * mclk_fs_ratio;
	पूर्णांक ret, i;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0,
					  RT1015_PLL_S_BCLK,
					  params_rate(params) * 64,
					  params_rate(params) * 256);
		अगर (ret) अणु
			dev_err(card->dev, "failed to set pll\n");
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_sysclk(codec_dai,
					     RT1015_SCLK_S_PLL,
					     params_rate(params) * 256,
					     SND_SOC_CLOCK_IN);
		अगर (ret) अणु
			dev_err(card->dev, "failed to set sysclk\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस snd_soc_dai_set_sysclk(cpu_dai, 0, mclk_fs, SND_SOC_CLOCK_OUT);
पूर्ण

अटल पूर्णांक mt8192_rt5682_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक mclk_fs_ratio = 128;
	अचिन्हित पूर्णांक mclk_fs = rate * mclk_fs_ratio;
	पूर्णांक bitwidth;
	पूर्णांक ret;

	bitwidth = snd_pcm_क्रमmat_width(params_क्रमmat(params));
	अगर (bitwidth < 0) अणु
		dev_err(card->dev, "invalid bit width: %d\n", bitwidth);
		वापस bitwidth;
	पूर्ण

	ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x00, 0x0, 0x2, bitwidth);
	अगर (ret) अणु
		dev_err(card->dev, "failed to set tdm slot\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_pll(codec_dai, RT5682_PLL1,
				  RT5682_PLL1_S_BCLK1,
				  params_rate(params) * 64,
				  params_rate(params) * 512);
	अगर (ret) अणु
		dev_err(card->dev, "failed to set pll\n");
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai,
				     RT5682_SCLK_S_PLL1,
				     params_rate(params) * 512,
				     SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		dev_err(card->dev, "failed to set sysclk\n");
		वापस ret;
	पूर्ण

	वापस snd_soc_dai_set_sysclk(cpu_dai, 0, mclk_fs, SND_SOC_CLOCK_OUT);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8192_rt1015_i2s_ops = अणु
	.hw_params = mt8192_rt1015_i2s_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops mt8192_rt5682_i2s_ops = अणु
	.hw_params = mt8192_rt5682_i2s_hw_params,
पूर्ण;

अटल पूर्णांक mt8192_mt6359_mtkaअगर_calibration(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *cmpnt_afe =
		snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	काष्ठा snd_soc_component *cmpnt_codec =
		asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt_afe);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;
	पूर्णांक phase;
	अचिन्हित पूर्णांक monitor;
	पूर्णांक test_करोne_1, test_करोne_2, test_करोne_3;
	पूर्णांक cycle_1, cycle_2, cycle_3;
	पूर्णांक prev_cycle_1, prev_cycle_2, prev_cycle_3;
	पूर्णांक chosen_phase_1, chosen_phase_2, chosen_phase_3;
	पूर्णांक counter;
	पूर्णांक mtkaअगर_calib_ok;

	dev_info(afe->dev, "%s(), start\n", __func__);

	pm_runसमय_get_sync(afe->dev);
	mt8192_afe_gpio_request(afe->dev, true, MT8192_DAI_ADDA, 1);
	mt8192_afe_gpio_request(afe->dev, true, MT8192_DAI_ADDA, 0);
	mt8192_afe_gpio_request(afe->dev, true, MT8192_DAI_ADDA_CH34, 1);
	mt8192_afe_gpio_request(afe->dev, true, MT8192_DAI_ADDA_CH34, 0);

	mt6359_mtkaअगर_calibration_enable(cmpnt_codec);

	/* set घड़ी protocol 2 */
	regmap_update_bits(afe->regmap, AFE_AUD_PAD_TOP, 0xff, 0x38);
	regmap_update_bits(afe->regmap, AFE_AUD_PAD_TOP, 0xff, 0x39);

	/* set test type to synchronizer pulse */
	regmap_update_bits(afe_priv->topckgen,
			   CKSYS_AUD_TOP_CFG, 0xffff, 0x4);

	mtkaअगर_calib_ok = true;
	afe_priv->mtkaअगर_calibration_num_phase = 42;	/* mt6359: 0 ~ 42 */
	afe_priv->mtkaअगर_chosen_phase[0] = -1;
	afe_priv->mtkaअगर_chosen_phase[1] = -1;
	afe_priv->mtkaअगर_chosen_phase[2] = -1;

	क्रम (phase = 0;
	     phase <= afe_priv->mtkaअगर_calibration_num_phase &&
	     mtkaअगर_calib_ok;
	     phase++) अणु
		mt6359_set_mtkaअगर_calibration_phase(cmpnt_codec,
						    phase, phase, phase);

		regmap_update_bits(afe_priv->topckgen,
				   CKSYS_AUD_TOP_CFG, 0x1, 0x1);

		test_करोne_1 = 0;
		test_करोne_2 = 0;
		test_करोne_3 = 0;
		cycle_1 = -1;
		cycle_2 = -1;
		cycle_3 = -1;
		counter = 0;
		जबतक (test_करोne_1 == 0 ||
		       test_करोne_2 == 0 ||
		       test_करोne_3 == 0) अणु
			regmap_पढ़ो(afe_priv->topckgen,
				    CKSYS_AUD_TOP_MON, &monitor);

			test_करोne_1 = (monitor >> 28) & 0x1;
			test_करोne_2 = (monitor >> 29) & 0x1;
			test_करोne_3 = (monitor >> 30) & 0x1;
			अगर (test_करोne_1 == 1)
				cycle_1 = monitor & 0xf;

			अगर (test_करोne_2 == 1)
				cycle_2 = (monitor >> 4) & 0xf;

			अगर (test_करोne_3 == 1)
				cycle_3 = (monitor >> 8) & 0xf;

			/* handle अगर never test करोne */
			अगर (++counter > 10000) अणु
				dev_err(afe->dev, "%s(), test fail, cycle_1 %d, cycle_2 %d, cycle_3 %d, monitor 0x%x\n",
					__func__,
					cycle_1, cycle_2, cycle_3, monitor);
				mtkaअगर_calib_ok = false;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (phase == 0) अणु
			prev_cycle_1 = cycle_1;
			prev_cycle_2 = cycle_2;
			prev_cycle_3 = cycle_3;
		पूर्ण

		अगर (cycle_1 != prev_cycle_1 &&
		    afe_priv->mtkaअगर_chosen_phase[0] < 0) अणु
			afe_priv->mtkaअगर_chosen_phase[0] = phase - 1;
			afe_priv->mtkaअगर_phase_cycle[0] = prev_cycle_1;
		पूर्ण

		अगर (cycle_2 != prev_cycle_2 &&
		    afe_priv->mtkaअगर_chosen_phase[1] < 0) अणु
			afe_priv->mtkaअगर_chosen_phase[1] = phase - 1;
			afe_priv->mtkaअगर_phase_cycle[1] = prev_cycle_2;
		पूर्ण

		अगर (cycle_3 != prev_cycle_3 &&
		    afe_priv->mtkaअगर_chosen_phase[2] < 0) अणु
			afe_priv->mtkaअगर_chosen_phase[2] = phase - 1;
			afe_priv->mtkaअगर_phase_cycle[2] = prev_cycle_3;
		पूर्ण

		regmap_update_bits(afe_priv->topckgen,
				   CKSYS_AUD_TOP_CFG, 0x1, 0x0);

		अगर (afe_priv->mtkaअगर_chosen_phase[0] >= 0 &&
		    afe_priv->mtkaअगर_chosen_phase[1] >= 0 &&
		    afe_priv->mtkaअगर_chosen_phase[2] >= 0)
			अवरोध;
	पूर्ण

	अगर (afe_priv->mtkaअगर_chosen_phase[0] < 0)
		chosen_phase_1 = 0;
	अन्यथा
		chosen_phase_1 = afe_priv->mtkaअगर_chosen_phase[0];

	अगर (afe_priv->mtkaअगर_chosen_phase[1] < 0)
		chosen_phase_2 = 0;
	अन्यथा
		chosen_phase_2 = afe_priv->mtkaअगर_chosen_phase[1];

	अगर (afe_priv->mtkaअगर_chosen_phase[2] < 0)
		chosen_phase_3 = 0;
	अन्यथा
		chosen_phase_3 = afe_priv->mtkaअगर_chosen_phase[2];

	mt6359_set_mtkaअगर_calibration_phase(cmpnt_codec,
					    chosen_phase_1,
					    chosen_phase_2,
					    chosen_phase_3);

	/* disable rx fअगरo */
	regmap_update_bits(afe->regmap, AFE_AUD_PAD_TOP, 0xff, 0x38);

	mt6359_mtkaअगर_calibration_disable(cmpnt_codec);

	mt8192_afe_gpio_request(afe->dev, false, MT8192_DAI_ADDA, 1);
	mt8192_afe_gpio_request(afe->dev, false, MT8192_DAI_ADDA, 0);
	mt8192_afe_gpio_request(afe->dev, false, MT8192_DAI_ADDA_CH34, 1);
	mt8192_afe_gpio_request(afe->dev, false, MT8192_DAI_ADDA_CH34, 0);
	pm_runसमय_put(afe->dev);

	dev_info(afe->dev, "%s(), mtkaif_chosen_phase[0/1/2]:%d/%d/%d\n",
		 __func__,
		 afe_priv->mtkaअगर_chosen_phase[0],
		 afe_priv->mtkaअगर_chosen_phase[1],
		 afe_priv->mtkaअगर_chosen_phase[2]);

	वापस 0;
पूर्ण

अटल पूर्णांक mt8192_mt6359_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *cmpnt_afe =
		snd_soc_rtdcom_lookup(rtd, AFE_PCM_NAME);
	काष्ठा snd_soc_component *cmpnt_codec =
		asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा mtk_base_afe *afe = snd_soc_component_get_drvdata(cmpnt_afe);
	काष्ठा mt8192_afe_निजी *afe_priv = afe->platक्रमm_priv;

	/* set mtkaअगर protocol */
	mt6359_set_mtkaअगर_protocol(cmpnt_codec,
				   MT6359_MTKAIF_PROTOCOL_2_CLK_P2);
	afe_priv->mtkaअगर_protocol = MTKAIF_PROTOCOL_2_CLK_P2;

	/* mtkaअगर calibration */
	mt8192_mt6359_mtkaअगर_calibration(rtd);

	वापस 0;
पूर्ण

अटल पूर्णांक mt8192_rt5682_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *cmpnt_codec =
		asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा mt8192_mt6359_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_jack *jack = &priv->headset_jack;
	पूर्णांक ret;

	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 |
				    SND_JACK_BTN_3,
				    jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack creation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	वापस snd_soc_component_set_jack(cmpnt_codec, jack, शून्य);
पूर्ण;

अटल पूर्णांक mt8192_mt6359_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *cmpnt_codec =
		asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा mt8192_mt6359_priv *priv = snd_soc_card_get_drvdata(rtd->card);
	पूर्णांक ret;

	ret = snd_soc_card_jack_new(rtd->card, "HDMI Jack", SND_JACK_LINEOUT,
				    &priv->hdmi_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "HDMI Jack creation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस snd_soc_component_set_jack(cmpnt_codec, &priv->hdmi_jack, शून्य);
पूर्ण

अटल पूर्णांक mt8192_i2s_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	/* fix BE i2s क्रमmat to 32bit, clean param mask first */
	snd_mask_reset_range(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT),
			     0, SNDRV_PCM_FORMAT_LAST);

	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S24_LE);

	वापस 0;
पूर्ण

अटल पूर्णांक
mt8192_mt6359_cap1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
		1, 2, 4
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
		.count = ARRAY_SIZE(channels),
		.list = channels,
		.mask = 0,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
		8000, 16000, 32000, 48000, 96000, 192000
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(rates),
		.list  = rates,
		.mask = 0,
	पूर्ण;

	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_CHANNELS,
					 &स्थिरraपूर्णांकs_channels);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "hw_constraint_list channels failed\n");
		वापस ret;
	पूर्ण

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_RATE,
					 &स्थिरraपूर्णांकs_rates);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "hw_constraint_list rate failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8192_mt6359_capture1_ops = अणु
	.startup = mt8192_mt6359_cap1_startup,
पूर्ण;

अटल पूर्णांक
mt8192_mt6359_rt5682_startup(काष्ठा snd_pcm_substream *substream)
अणु
	अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
		1, 2
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
		.count = ARRAY_SIZE(channels),
		.list = channels,
		.mask = 0,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
		48000
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(rates),
		.list  = rates,
		.mask = 0,
	पूर्ण;

	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	पूर्णांक ret;

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_CHANNELS,
					 &स्थिरraपूर्णांकs_channels);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "hw_constraint_list channels failed\n");
		वापस ret;
	पूर्ण

	ret = snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
					 SNDRV_PCM_HW_PARAM_RATE,
					 &स्थिरraपूर्णांकs_rates);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "hw_constraint_list rate failed\n");
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8192_mt6359_rt5682_ops = अणु
	.startup = mt8192_mt6359_rt5682_startup,
पूर्ण;

/* FE */
SND_SOC_DAILINK_DEFS(playback1,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL1")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback12,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL12")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback2,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL2")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback3,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL3")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback4,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL4")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback5,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL5")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback6,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL6")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback7,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL7")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback8,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL8")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback9,
		     DAILINK_COMP_ARRAY(COMP_CPU("DL9")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture1,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL1")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture2,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL2")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture3,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL3")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture4,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL4")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture5,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL5")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture6,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL6")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture7,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL7")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture8,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL8")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture_mono1,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL_MONO_1")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture_mono2,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL_MONO_2")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(capture_mono3,
		     DAILINK_COMP_ARRAY(COMP_CPU("UL_MONO_3")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback_hdmi,
		     DAILINK_COMP_ARRAY(COMP_CPU("HDMI")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

/* BE */
SND_SOC_DAILINK_DEFS(primary_codec,
		     DAILINK_COMP_ARRAY(COMP_CPU("ADDA")),
		     DAILINK_COMP_ARRAY(COMP_CODEC("mt6359-sound",
						   "mt6359-snd-codec-aif1"),
					COMP_CODEC("dmic-codec",
						   "dmic-hifi")),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(primary_codec_ch34,
		     DAILINK_COMP_ARRAY(COMP_CPU("ADDA_CH34")),
		     DAILINK_COMP_ARRAY(COMP_CODEC("mt6359-sound",
						   "mt6359-snd-codec-aif2")),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(ap_dmic,
		     DAILINK_COMP_ARRAY(COMP_CPU("AP_DMIC")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(ap_dmic_ch34,
		     DAILINK_COMP_ARRAY(COMP_CPU("AP_DMIC_CH34")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s0,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S0")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s1,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S1")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s2,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S2")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s3_rt1015,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S3")),
		     DAILINK_COMP_ARRAY(COMP_CODEC(RT1015_DEV0_NAME,
						   RT1015_CODEC_DAI),
					COMP_CODEC(RT1015_DEV1_NAME,
						   RT1015_CODEC_DAI)),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s3_rt1015p,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S3")),
		     DAILINK_COMP_ARRAY(COMP_CODEC("rt1015p", "HiFi")),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s5,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S5")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s6,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S6")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s7,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S7")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s8,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S8")),
		     DAILINK_COMP_ARRAY(COMP_CODEC(RT5682_DEV0_NAME,
						   RT5682_CODEC_DAI)),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s9,
		     DAILINK_COMP_ARRAY(COMP_CPU("I2S9")),
		     DAILINK_COMP_ARRAY(COMP_CODEC(RT5682_DEV0_NAME,
						   RT5682_CODEC_DAI)),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(connsys_i2s,
		     DAILINK_COMP_ARRAY(COMP_CPU("CONNSYS_I2S")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(pcm1,
		     DAILINK_COMP_ARRAY(COMP_CPU("PCM 1")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(pcm2,
		     DAILINK_COMP_ARRAY(COMP_CPU("PCM 2")),
		     DAILINK_COMP_ARRAY(COMP_DUMMY()),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(tdm,
		     DAILINK_COMP_ARRAY(COMP_CPU("TDM")),
		     DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "i2s-hifi")),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link mt8192_mt6359_dai_links[] = अणु
	/* Front End DAI links */
	अणु
		.name = "Playback_1",
		.stream_name = "Playback_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback1),
	पूर्ण,
	अणु
		.name = "Playback_12",
		.stream_name = "Playback_12",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback12),
	पूर्ण,
	अणु
		.name = "Playback_2",
		.stream_name = "Playback_2",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback2),
	पूर्ण,
	अणु
		.name = "Playback_3",
		.stream_name = "Playback_3",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &mt8192_mt6359_rt5682_ops,
		SND_SOC_DAILINK_REG(playback3),
	पूर्ण,
	अणु
		.name = "Playback_4",
		.stream_name = "Playback_4",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback4),
	पूर्ण,
	अणु
		.name = "Playback_5",
		.stream_name = "Playback_5",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback5),
	पूर्ण,
	अणु
		.name = "Playback_6",
		.stream_name = "Playback_6",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback6),
	पूर्ण,
	अणु
		.name = "Playback_7",
		.stream_name = "Playback_7",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback7),
	पूर्ण,
	अणु
		.name = "Playback_8",
		.stream_name = "Playback_8",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback8),
	पूर्ण,
	अणु
		.name = "Playback_9",
		.stream_name = "Playback_9",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback9),
	पूर्ण,
	अणु
		.name = "Capture_1",
		.stream_name = "Capture_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		.ops = &mt8192_mt6359_capture1_ops,
		SND_SOC_DAILINK_REG(capture1),
	पूर्ण,
	अणु
		.name = "Capture_2",
		.stream_name = "Capture_2",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		.ops = &mt8192_mt6359_rt5682_ops,
		SND_SOC_DAILINK_REG(capture2),
	पूर्ण,
	अणु
		.name = "Capture_3",
		.stream_name = "Capture_3",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture3),
	पूर्ण,
	अणु
		.name = "Capture_4",
		.stream_name = "Capture_4",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture4),
	पूर्ण,
	अणु
		.name = "Capture_5",
		.stream_name = "Capture_5",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture5),
	पूर्ण,
	अणु
		.name = "Capture_6",
		.stream_name = "Capture_6",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture6),
	पूर्ण,
	अणु
		.name = "Capture_7",
		.stream_name = "Capture_7",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture7),
	पूर्ण,
	अणु
		.name = "Capture_8",
		.stream_name = "Capture_8",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture8),
	पूर्ण,
	अणु
		.name = "Capture_Mono_1",
		.stream_name = "Capture_Mono_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture_mono1),
	पूर्ण,
	अणु
		.name = "Capture_Mono_2",
		.stream_name = "Capture_Mono_2",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture_mono2),
	पूर्ण,
	अणु
		.name = "Capture_Mono_3",
		.stream_name = "Capture_Mono_3",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture_mono3),
	पूर्ण,
	अणु
		.name = "playback_hdmi",
		.stream_name = "Playback_HDMI",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback_hdmi),
	पूर्ण,
	/* Back End DAI links */
	अणु
		.name = "Primary Codec",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		.init = mt8192_mt6359_init,
		SND_SOC_DAILINK_REG(primary_codec),
	पूर्ण,
	अणु
		.name = "Primary Codec CH34",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(primary_codec_ch34),
	पूर्ण,
	अणु
		.name = "AP_DMIC",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(ap_dmic),
	पूर्ण,
	अणु
		.name = "AP_DMIC_CH34",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(ap_dmic_ch34),
	पूर्ण,
	अणु
		.name = "I2S0",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		SND_SOC_DAILINK_REG(i2s0),
	पूर्ण,
	अणु
		.name = "I2S1",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		SND_SOC_DAILINK_REG(i2s1),
	पूर्ण,
	अणु
		.name = "I2S2",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		SND_SOC_DAILINK_REG(i2s2),
	पूर्ण,
	अणु
		.name = "I2S3",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
	पूर्ण,
	अणु
		.name = "I2S5",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		SND_SOC_DAILINK_REG(i2s5),
	पूर्ण,
	अणु
		.name = "I2S6",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		SND_SOC_DAILINK_REG(i2s6),
	पूर्ण,
	अणु
		.name = "I2S7",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		SND_SOC_DAILINK_REG(i2s7),
	पूर्ण,
	अणु
		.name = "I2S8",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		.init = mt8192_rt5682_init,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		SND_SOC_DAILINK_REG(i2s8),
		.ops = &mt8192_rt5682_i2s_ops,
	पूर्ण,
	अणु
		.name = "I2S9",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		SND_SOC_DAILINK_REG(i2s9),
		.ops = &mt8192_rt5682_i2s_ops,
	पूर्ण,
	अणु
		.name = "CONNSYS_I2S",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(connsys_i2s),
	पूर्ण,
	अणु
		.name = "PCM 1",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(pcm1),
	पूर्ण,
	अणु
		.name = "PCM 2",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(pcm2),
	पूर्ण,
	अणु
		.name = "TDM",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_DSP_A |
			   SND_SOC_DAIFMT_IB_NF |
			   SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8192_i2s_hw_params_fixup,
		.ignore = 1,
		.init = mt8192_mt6359_hdmi_init,
		SND_SOC_DAILINK_REG(tdm),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget
mt8192_mt6359_rt1015_rt5682_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_OUTPUT("TDM Out"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8192_mt6359_rt1015_rt5682_routes[] = अणु
	/* speaker */
	अणु "Left Spk", शून्य, "Left SPO" पूर्ण,
	अणु "Right Spk", शून्य, "Right SPO" पूर्ण,
	/* headset */
	अणु "Headphone Jack", शून्य, "HPOL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPOR" पूर्ण,
	अणु "IN1P", शून्य, "Headset Mic" पूर्ण,
	/* TDM */
	अणु "TDM Out", शून्य, "TDM" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8192_mt6359_rt1015_rt5682_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Left Spk"),
	SOC_DAPM_PIN_SWITCH("Right Spk"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल काष्ठा snd_soc_codec_conf rt1015_amp_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF(RT1015_DEV0_NAME),
		.name_prefix = "Left",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF(RT1015_DEV1_NAME),
		.name_prefix = "Right",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt8192_mt6359_rt1015_rt5682_card = अणु
	.name = "mt8192_mt6359_rt1015_rt5682",
	.owner = THIS_MODULE,
	.dai_link = mt8192_mt6359_dai_links,
	.num_links = ARRAY_SIZE(mt8192_mt6359_dai_links),
	.controls = mt8192_mt6359_rt1015_rt5682_controls,
	.num_controls = ARRAY_SIZE(mt8192_mt6359_rt1015_rt5682_controls),
	.dapm_widमाला_लो = mt8192_mt6359_rt1015_rt5682_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt8192_mt6359_rt1015_rt5682_widमाला_लो),
	.dapm_routes = mt8192_mt6359_rt1015_rt5682_routes,
	.num_dapm_routes = ARRAY_SIZE(mt8192_mt6359_rt1015_rt5682_routes),
	.codec_conf = rt1015_amp_conf,
	.num_configs = ARRAY_SIZE(rt1015_amp_conf),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget
mt8192_mt6359_rt1015p_rt5682_widमाला_लो[] = अणु
	SND_SOC_DAPM_SPK("Speakers", शून्य),
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route mt8192_mt6359_rt1015p_rt5682_routes[] = अणु
	/* speaker */
	अणु "Speakers", शून्य, "Speaker" पूर्ण,
	/* headset */
	अणु "Headphone Jack", शून्य, "HPOL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPOR" पूर्ण,
	अणु "IN1P", शून्य, "Headset Mic" पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new mt8192_mt6359_rt1015p_rt5682_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Speakers"),
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
पूर्ण;

अटल काष्ठा snd_soc_card mt8192_mt6359_rt1015p_rt5682_card = अणु
	.name = "mt8192_mt6359_rt1015p_rt5682",
	.owner = THIS_MODULE,
	.dai_link = mt8192_mt6359_dai_links,
	.num_links = ARRAY_SIZE(mt8192_mt6359_dai_links),
	.controls = mt8192_mt6359_rt1015p_rt5682_controls,
	.num_controls = ARRAY_SIZE(mt8192_mt6359_rt1015p_rt5682_controls),
	.dapm_widमाला_लो = mt8192_mt6359_rt1015p_rt5682_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(mt8192_mt6359_rt1015p_rt5682_widमाला_लो),
	.dapm_routes = mt8192_mt6359_rt1015p_rt5682_routes,
	.num_dapm_routes = ARRAY_SIZE(mt8192_mt6359_rt1015p_rt5682_routes),
पूर्ण;

अटल पूर्णांक mt8192_mt6359_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा device_node *platक्रमm_node, *hdmi_codec;
	पूर्णांक ret, i;
	काष्ठा snd_soc_dai_link *dai_link;
	स्थिर काष्ठा of_device_id *match;
	काष्ठा mt8192_mt6359_priv *priv;

	platक्रमm_node = of_parse_phandle(pdev->dev.of_node,
					 "mediatek,platform", 0);
	अगर (!platक्रमm_node) अणु
		dev_err(&pdev->dev, "Property 'platform' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	match = of_match_device(pdev->dev.driver->of_match_table, &pdev->dev);
	अगर (!match || !match->data)
		वापस -EINVAL;

	card = (काष्ठा snd_soc_card *)match->data;
	card->dev = &pdev->dev;

	hdmi_codec = of_parse_phandle(pdev->dev.of_node,
				      "mediatek,hdmi-codec", 0);

	क्रम_each_card_prelinks(card, i, dai_link) अणु
		अगर (म_भेद(dai_link->name, "I2S3") == 0) अणु
			अगर (card == &mt8192_mt6359_rt1015_rt5682_card) अणु
				dai_link->ops = &mt8192_rt1015_i2s_ops;
				dai_link->cpus = i2s3_rt1015_cpus;
				dai_link->num_cpus =
					ARRAY_SIZE(i2s3_rt1015_cpus);
				dai_link->codecs = i2s3_rt1015_codecs;
				dai_link->num_codecs =
					ARRAY_SIZE(i2s3_rt1015_codecs);
				dai_link->platक्रमms = i2s3_rt1015_platक्रमms;
				dai_link->num_platक्रमms =
					ARRAY_SIZE(i2s3_rt1015_platक्रमms);
			पूर्ण अन्यथा अगर (card == &mt8192_mt6359_rt1015p_rt5682_card) अणु
				dai_link->cpus = i2s3_rt1015p_cpus;
				dai_link->num_cpus =
					ARRAY_SIZE(i2s3_rt1015p_cpus);
				dai_link->codecs = i2s3_rt1015p_codecs;
				dai_link->num_codecs =
					ARRAY_SIZE(i2s3_rt1015p_codecs);
				dai_link->platक्रमms = i2s3_rt1015p_platक्रमms;
				dai_link->num_platक्रमms =
					ARRAY_SIZE(i2s3_rt1015p_platक्रमms);
			पूर्ण
		पूर्ण

		अगर (hdmi_codec && म_भेद(dai_link->name, "TDM") == 0) अणु
			dai_link->codecs->of_node = hdmi_codec;
			dai_link->ignore = 0;
		पूर्ण

		अगर (!dai_link->platक्रमms->name)
			dai_link->platक्रमms->of_node = platक्रमm_node;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;
	snd_soc_card_set_drvdata(card, priv);

	ret = mt8192_afe_gpio_init(&pdev->dev);
	अगर (ret) अणु
		dev_err(&pdev->dev, "init gpio error %d\n", ret);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mt8192_mt6359_dt_match[] = अणु
	अणु
		.compatible = "mediatek,mt8192_mt6359_rt1015_rt5682",
		.data = &mt8192_mt6359_rt1015_rt5682_card,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8192_mt6359_rt1015p_rt5682",
		.data = &mt8192_mt6359_rt1015p_rt5682_card,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा dev_pm_ops mt8192_mt6359_pm_ops = अणु
	.घातeroff = snd_soc_घातeroff,
	.restore = snd_soc_resume,
पूर्ण;

अटल काष्ठा platक्रमm_driver mt8192_mt6359_driver = अणु
	.driver = अणु
		.name = "mt8192_mt6359",
#अगर_घोषित CONFIG_OF
		.of_match_table = mt8192_mt6359_dt_match,
#पूर्ण_अगर
		.pm = &mt8192_mt6359_pm_ops,
	पूर्ण,
	.probe = mt8192_mt6359_dev_probe,
पूर्ण;

module_platक्रमm_driver(mt8192_mt6359_driver);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT8192-MT6359 ALSA SoC machine driver");
MODULE_AUTHOR("Jiaxin Yu <jiaxin.yu@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("mt8192_mt6359 soc card");
