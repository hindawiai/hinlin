<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mt8183-mt6358.c  --
//	MT8183-MT6358-TS3A227-MAX98357 ALSA SoC machine driver
//
// Copyright (c) 2018 MediaTek Inc.
// Author: Shunli Wang <shunli.wang@mediatek.com>

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/pinctrl/consumer.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "../../codecs/rt1015.h"
#समावेश "../../codecs/ts3a227e.h"
#समावेश "mt8183-afe-common.h"

#घोषणा RT1015_CODEC_DAI "rt1015-aif"
#घोषणा RT1015_DEV0_NAME "rt1015.6-0028"
#घोषणा RT1015_DEV1_NAME "rt1015.6-0029"

क्रमागत PINCTRL_PIN_STATE अणु
	PIN_STATE_DEFAULT = 0,
	PIN_TDM_OUT_ON,
	PIN_TDM_OUT_OFF,
	PIN_WOV,
	PIN_STATE_MAX
पूर्ण;

अटल स्थिर अक्षर * स्थिर mt8183_pin_str[PIN_STATE_MAX] = अणु
	"default", "aud_tdm_out_on", "aud_tdm_out_off", "wov",
पूर्ण;

काष्ठा mt8183_mt6358_ts3a227_max98357_priv अणु
	काष्ठा pinctrl *pinctrl;
	काष्ठा pinctrl_state *pin_states[PIN_STATE_MAX];
	काष्ठा snd_soc_jack headset_jack, hdmi_jack;
पूर्ण;

अटल पूर्णांक mt8183_mt6358_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				       काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक mclk_fs_ratio = 128;
	अचिन्हित पूर्णांक mclk_fs = rate * mclk_fs_ratio;

	वापस snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(rtd, 0),
				      0, mclk_fs, SND_SOC_CLOCK_OUT);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8183_mt6358_i2s_ops = अणु
	.hw_params = mt8183_mt6358_i2s_hw_params,
पूर्ण;

अटल पूर्णांक
mt8183_mt6358_rt1015_i2s_hw_params(काष्ठा snd_pcm_substream *substream,
				   काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक mclk_fs_ratio = 128;
	अचिन्हित पूर्णांक mclk_fs = rate * mclk_fs_ratio;
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret, i;

	क्रम_each_rtd_codec_dais(rtd, i, codec_dai) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0, RT1015_PLL_S_BCLK,
				rate * 64, rate * 256);
		अगर (ret < 0) अणु
			dev_err(card->dev, "failed to set pll\n");
			वापस ret;
		पूर्ण

		ret = snd_soc_dai_set_sysclk(codec_dai, RT1015_SCLK_S_PLL,
				rate * 256, SND_SOC_CLOCK_IN);
		अगर (ret < 0) अणु
			dev_err(card->dev, "failed to set sysclk\n");
			वापस ret;
		पूर्ण
	पूर्ण

	वापस snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(rtd, 0),
				      0, mclk_fs, SND_SOC_CLOCK_OUT);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8183_mt6358_rt1015_i2s_ops = अणु
	.hw_params = mt8183_mt6358_rt1015_i2s_hw_params,
पूर्ण;

अटल पूर्णांक mt8183_i2s_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
				      काष्ठा snd_pcm_hw_params *params)
अणु
	dev_dbg(rtd->dev, "%s(), fix format to 32bit\n", __func__);

	/* fix BE i2s क्रमmat to 32bit, clean param mask first */
	snd_mask_reset_range(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT),
			     0, SNDRV_PCM_FORMAT_LAST);

	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S32_LE);
	वापस 0;
पूर्ण

अटल पूर्णांक mt8183_rt1015_i2s_hw_params_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
					     काष्ठा snd_pcm_hw_params *params)
अणु
	dev_dbg(rtd->dev, "%s(), fix format to 32bit\n", __func__);

	/* fix BE i2s क्रमmat to 32bit, clean param mask first */
	snd_mask_reset_range(hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT),
			     0, SNDRV_PCM_FORMAT_LAST);

	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S24_LE);
	वापस 0;
पूर्ण

अटल पूर्णांक
mt8183_mt6358_startup(काष्ठा snd_pcm_substream *substream)
अणु
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
		48000,
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(rates),
		.list  = rates,
		.mask = 0,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
		2,
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
		.count = ARRAY_SIZE(channels),
		.list = channels,
		.mask = 0,
	पूर्ण;

	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				   SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);
	runसमय->hw.channels_max = 2;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				   SNDRV_PCM_HW_PARAM_CHANNELS,
				   &स्थिरraपूर्णांकs_channels);

	runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 16, 16);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8183_mt6358_ops = अणु
	.startup = mt8183_mt6358_startup,
पूर्ण;

अटल पूर्णांक
mt8183_mt6358_ts3a227_max98357_bt_sco_startup(
	काष्ठा snd_pcm_substream *substream)
अणु
	अटल स्थिर अचिन्हित पूर्णांक rates[] = अणु
		8000, 16000
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_rates = अणु
		.count = ARRAY_SIZE(rates),
		.list  = rates,
		.mask = 0,
	पूर्ण;
	अटल स्थिर अचिन्हित पूर्णांक channels[] = अणु
		1,
	पूर्ण;
	अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
		.count = ARRAY_SIZE(channels),
		.list = channels,
		.mask = 0,
	पूर्ण;

	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);
	runसमय->hw.channels_max = 1;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
			SNDRV_PCM_HW_PARAM_CHANNELS,
			&स्थिरraपूर्णांकs_channels);

	runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 16, 16);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8183_mt6358_ts3a227_max98357_bt_sco_ops = अणु
	.startup = mt8183_mt6358_ts3a227_max98357_bt_sco_startup,
पूर्ण;

/* FE */
SND_SOC_DAILINK_DEFS(playback1,
	DAILINK_COMP_ARRAY(COMP_CPU("DL1")),
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

SND_SOC_DAILINK_DEFS(capture_mono,
	DAILINK_COMP_ARRAY(COMP_CPU("UL_MONO_1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(playback_hdmi,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(wake_on_voice,
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

/* BE */
SND_SOC_DAILINK_DEFS(primary_codec,
	DAILINK_COMP_ARRAY(COMP_CPU("ADDA")),
	DAILINK_COMP_ARRAY(COMP_CODEC("mt6358-sound", "mt6358-snd-codec-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(pcm1,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM 1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(pcm2,
	DAILINK_COMP_ARRAY(COMP_CPU("PCM 2")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s0,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("bt-sco", "bt-sco-pcm")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s1,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S1")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s2,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S2")),
	DAILINK_COMP_ARRAY(COMP_DUMMY()),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s3_max98357a,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S3")),
	DAILINK_COMP_ARRAY(COMP_CODEC("max98357a", "HiFi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s3_rt1015,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S3")),
	DAILINK_COMP_ARRAY(COMP_CODEC(RT1015_DEV0_NAME, RT1015_CODEC_DAI),
			   COMP_CODEC(RT1015_DEV1_NAME, RT1015_CODEC_DAI)),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s3_rt1015p,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S3")),
	DAILINK_COMP_ARRAY(COMP_CODEC("rt1015p", "HiFi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(i2s5,
	DAILINK_COMP_ARRAY(COMP_CPU("I2S5")),
	DAILINK_COMP_ARRAY(COMP_CODEC("bt-sco", "bt-sco-pcm")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(tdm,
	DAILINK_COMP_ARRAY(COMP_CPU("TDM")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "i2s-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल पूर्णांक mt8183_mt6358_tdm_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा mt8183_mt6358_ts3a227_max98357_priv *priv =
		snd_soc_card_get_drvdata(rtd->card);
	पूर्णांक ret;

	अगर (IS_ERR(priv->pin_states[PIN_TDM_OUT_ON]))
		वापस PTR_ERR(priv->pin_states[PIN_TDM_OUT_ON]);

	ret = pinctrl_select_state(priv->pinctrl,
				   priv->pin_states[PIN_TDM_OUT_ON]);
	अगर (ret)
		dev_err(rtd->card->dev, "%s failed to select state %d\n",
			__func__, ret);

	वापस ret;
पूर्ण

अटल व्योम mt8183_mt6358_tdm_shutकरोwn(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा mt8183_mt6358_ts3a227_max98357_priv *priv =
		snd_soc_card_get_drvdata(rtd->card);
	पूर्णांक ret;

	अगर (IS_ERR(priv->pin_states[PIN_TDM_OUT_OFF]))
		वापस;

	ret = pinctrl_select_state(priv->pinctrl,
				   priv->pin_states[PIN_TDM_OUT_OFF]);
	अगर (ret)
		dev_err(rtd->card->dev, "%s failed to select state %d\n",
			__func__, ret);
पूर्ण

अटल काष्ठा snd_soc_ops mt8183_mt6358_tdm_ops = अणु
	.startup = mt8183_mt6358_tdm_startup,
	.shutकरोwn = mt8183_mt6358_tdm_shutकरोwn,
पूर्ण;

अटल पूर्णांक
mt8183_mt6358_ts3a227_max98357_wov_startup(
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा mt8183_mt6358_ts3a227_max98357_priv *priv =
			snd_soc_card_get_drvdata(card);

	वापस pinctrl_select_state(priv->pinctrl,
				    priv->pin_states[PIN_WOV]);
पूर्ण

अटल व्योम
mt8183_mt6358_ts3a227_max98357_wov_shutकरोwn(
	काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = rtd->card;
	काष्ठा mt8183_mt6358_ts3a227_max98357_priv *priv =
			snd_soc_card_get_drvdata(card);
	पूर्णांक ret;

	ret = pinctrl_select_state(priv->pinctrl,
				   priv->pin_states[PIN_STATE_DEFAULT]);
	अगर (ret)
		dev_err(card->dev, "%s failed to select state %d\n",
			__func__, ret);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops mt8183_mt6358_ts3a227_max98357_wov_ops = अणु
	.startup = mt8183_mt6358_ts3a227_max98357_wov_startup,
	.shutकरोwn = mt8183_mt6358_ts3a227_max98357_wov_shutकरोwn,
पूर्ण;

अटल पूर्णांक
mt8183_mt6358_ts3a227_max98357_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा mt8183_mt6358_ts3a227_max98357_priv *priv =
		snd_soc_card_get_drvdata(rtd->card);
	पूर्णांक ret;

	ret = snd_soc_card_jack_new(rtd->card, "HDMI Jack", SND_JACK_LINEOUT,
				    &priv->hdmi_jack, शून्य, 0);
	अगर (ret)
		वापस ret;

	वापस snd_soc_component_set_jack(asoc_rtd_to_codec(rtd, 0)->component,
					  &priv->hdmi_jack, शून्य);
पूर्ण

अटल काष्ठा snd_soc_dai_link mt8183_mt6358_ts3a227_dai_links[] = अणु
	/* FE */
	अणु
		.name = "Playback_1",
		.stream_name = "Playback_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &mt8183_mt6358_ops,
		SND_SOC_DAILINK_REG(playback1),
	पूर्ण,
	अणु
		.name = "Playback_2",
		.stream_name = "Playback_2",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &mt8183_mt6358_ts3a227_max98357_bt_sco_ops,
		SND_SOC_DAILINK_REG(playback2),
	पूर्ण,
	अणु
		.name = "Playback_3",
		.stream_name = "Playback_3",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback3),
	पूर्ण,
	अणु
		.name = "Capture_1",
		.stream_name = "Capture_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		.ops = &mt8183_mt6358_ts3a227_max98357_bt_sco_ops,
		SND_SOC_DAILINK_REG(capture1),
	पूर्ण,
	अणु
		.name = "Capture_2",
		.stream_name = "Capture_2",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture2),
	पूर्ण,
	अणु
		.name = "Capture_3",
		.stream_name = "Capture_3",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		.ops = &mt8183_mt6358_ops,
		SND_SOC_DAILINK_REG(capture3),
	पूर्ण,
	अणु
		.name = "Capture_Mono_1",
		.stream_name = "Capture_Mono_1",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(capture_mono),
	पूर्ण,
	अणु
		.name = "Playback_HDMI",
		.stream_name = "Playback_HDMI",
		.trigger = अणुSND_SOC_DPCM_TRIGGER_PRE,
			    SND_SOC_DPCM_TRIGGER_PREपूर्ण,
		.dynamic = 1,
		.dpcm_playback = 1,
		SND_SOC_DAILINK_REG(playback_hdmi),
	पूर्ण,
	अणु
		.name = "Wake on Voice",
		.stream_name = "Wake on Voice",
		.ignore_suspend = 1,
		.ignore = 1,
		SND_SOC_DAILINK_REG(wake_on_voice),
		.ops = &mt8183_mt6358_ts3a227_max98357_wov_ops,
	पूर्ण,

	/* BE */
	अणु
		.name = "Primary Codec",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(primary_codec),
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
		.name = "I2S0",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8183_i2s_hw_params_fixup,
		.ops = &mt8183_mt6358_i2s_ops,
		SND_SOC_DAILINK_REG(i2s0),
	पूर्ण,
	अणु
		.name = "I2S1",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8183_i2s_hw_params_fixup,
		.ops = &mt8183_mt6358_i2s_ops,
		SND_SOC_DAILINK_REG(i2s1),
	पूर्ण,
	अणु
		.name = "I2S2",
		.no_pcm = 1,
		.dpcm_capture = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8183_i2s_hw_params_fixup,
		.ops = &mt8183_mt6358_i2s_ops,
		SND_SOC_DAILINK_REG(i2s2),
	पूर्ण,
	अणु
		.name = "I2S3",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
	पूर्ण,
	अणु
		.name = "I2S5",
		.no_pcm = 1,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8183_i2s_hw_params_fixup,
		.ops = &mt8183_mt6358_i2s_ops,
		SND_SOC_DAILINK_REG(i2s5),
	पूर्ण,
	अणु
		.name = "TDM",
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_I2S |
			   SND_SOC_DAIFMT_IB_IF |
			   SND_SOC_DAIFMT_CBM_CFM,
		.dpcm_playback = 1,
		.ignore_suspend = 1,
		.be_hw_params_fixup = mt8183_i2s_hw_params_fixup,
		.ops = &mt8183_mt6358_tdm_ops,
		.ignore = 1,
		.init = mt8183_mt6358_ts3a227_max98357_hdmi_init,
		SND_SOC_DAILINK_REG(tdm),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt8183_mt6358_ts3a227_max98357_card = अणु
	.name = "mt8183_mt6358_ts3a227_max98357",
	.owner = THIS_MODULE,
	.dai_link = mt8183_mt6358_ts3a227_dai_links,
	.num_links = ARRAY_SIZE(mt8183_mt6358_ts3a227_dai_links),
पूर्ण;

अटल काष्ठा snd_soc_card mt8183_mt6358_ts3a227_max98357b_card = अणु
	.name = "mt8183_mt6358_ts3a227_max98357b",
	.owner = THIS_MODULE,
	.dai_link = mt8183_mt6358_ts3a227_dai_links,
	.num_links = ARRAY_SIZE(mt8183_mt6358_ts3a227_dai_links),
पूर्ण;

अटल काष्ठा snd_soc_codec_conf mt8183_mt6358_ts3a227_rt1015_amp_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF(RT1015_DEV0_NAME),
		.name_prefix = "Left",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF(RT1015_DEV1_NAME),
		.name_prefix = "Right",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mt8183_mt6358_ts3a227_rt1015_card = अणु
	.name = "mt8183_mt6358_ts3a227_rt1015",
	.owner = THIS_MODULE,
	.dai_link = mt8183_mt6358_ts3a227_dai_links,
	.num_links = ARRAY_SIZE(mt8183_mt6358_ts3a227_dai_links),
	.codec_conf = mt8183_mt6358_ts3a227_rt1015_amp_conf,
	.num_configs = ARRAY_SIZE(mt8183_mt6358_ts3a227_rt1015_amp_conf),
पूर्ण;

अटल काष्ठा snd_soc_card mt8183_mt6358_ts3a227_rt1015p_card = अणु
	.name = "mt8183_mt6358_ts3a227_rt1015p",
	.owner = THIS_MODULE,
	.dai_link = mt8183_mt6358_ts3a227_dai_links,
	.num_links = ARRAY_SIZE(mt8183_mt6358_ts3a227_dai_links),
पूर्ण;

अटल पूर्णांक
mt8183_mt6358_ts3a227_max98357_headset_init(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;
	काष्ठा mt8183_mt6358_ts3a227_max98357_priv *priv =
			snd_soc_card_get_drvdata(component->card);

	/* Enable Headset and 4 Buttons Jack detection */
	ret = snd_soc_card_jack_new(component->card,
				    "Headset Jack",
				    SND_JACK_HEADSET |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3,
				    &priv->headset_jack,
				    शून्य, 0);
	अगर (ret)
		वापस ret;

	ret = ts3a227e_enable_jack_detect(component, &priv->headset_jack);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_aux_dev mt8183_mt6358_ts3a227_max98357_headset_dev = अणु
	.dlc = COMP_EMPTY(),
	.init = mt8183_mt6358_ts3a227_max98357_headset_init,
पूर्ण;

अटल पूर्णांक
mt8183_mt6358_ts3a227_max98357_dev_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	काष्ठा device_node *platक्रमm_node, *ec_codec, *hdmi_codec;
	काष्ठा snd_soc_dai_link *dai_link;
	काष्ठा mt8183_mt6358_ts3a227_max98357_priv *priv;
	स्थिर काष्ठा of_device_id *match;
	पूर्णांक ret, i;

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

	ec_codec = of_parse_phandle(pdev->dev.of_node, "mediatek,ec-codec", 0);
	hdmi_codec = of_parse_phandle(pdev->dev.of_node,
				      "mediatek,hdmi-codec", 0);

	क्रम_each_card_prelinks(card, i, dai_link) अणु
		अगर (ec_codec && म_भेद(dai_link->name, "Wake on Voice") == 0) अणु
			dai_link->cpus[0].name = शून्य;
			dai_link->cpus[0].of_node = ec_codec;
			dai_link->cpus[0].dai_name = शून्य;
			dai_link->codecs[0].name = शून्य;
			dai_link->codecs[0].of_node = ec_codec;
			dai_link->codecs[0].dai_name = "Wake on Voice";
			dai_link->platक्रमms[0].of_node = ec_codec;
			dai_link->ignore = 0;
		पूर्ण

		अगर (म_भेद(dai_link->name, "I2S3") == 0) अणु
			अगर (card == &mt8183_mt6358_ts3a227_max98357_card ||
			    card == &mt8183_mt6358_ts3a227_max98357b_card) अणु
				dai_link->be_hw_params_fixup =
					mt8183_i2s_hw_params_fixup;
				dai_link->ops = &mt8183_mt6358_i2s_ops;
				dai_link->cpus = i2s3_max98357a_cpus;
				dai_link->num_cpus =
					ARRAY_SIZE(i2s3_max98357a_cpus);
				dai_link->codecs = i2s3_max98357a_codecs;
				dai_link->num_codecs =
					ARRAY_SIZE(i2s3_max98357a_codecs);
				dai_link->platक्रमms = i2s3_max98357a_platक्रमms;
				dai_link->num_platक्रमms =
					ARRAY_SIZE(i2s3_max98357a_platक्रमms);
			पूर्ण अन्यथा अगर (card == &mt8183_mt6358_ts3a227_rt1015_card) अणु
				dai_link->be_hw_params_fixup =
					mt8183_rt1015_i2s_hw_params_fixup;
				dai_link->ops = &mt8183_mt6358_rt1015_i2s_ops;
				dai_link->cpus = i2s3_rt1015_cpus;
				dai_link->num_cpus =
					ARRAY_SIZE(i2s3_rt1015_cpus);
				dai_link->codecs = i2s3_rt1015_codecs;
				dai_link->num_codecs =
					ARRAY_SIZE(i2s3_rt1015_codecs);
				dai_link->platक्रमms = i2s3_rt1015_platक्रमms;
				dai_link->num_platक्रमms =
					ARRAY_SIZE(i2s3_rt1015_platक्रमms);
			पूर्ण अन्यथा अगर (card == &mt8183_mt6358_ts3a227_rt1015p_card) अणु
				dai_link->be_hw_params_fixup =
					mt8183_rt1015_i2s_hw_params_fixup;
				dai_link->ops = &mt8183_mt6358_i2s_ops;
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

		अगर (card == &mt8183_mt6358_ts3a227_max98357b_card) अणु
			अगर (म_भेद(dai_link->name, "I2S2") == 0 ||
			    म_भेद(dai_link->name, "I2S3") == 0)
				dai_link->dai_fmt = SND_SOC_DAIFMT_LEFT_J |
						    SND_SOC_DAIFMT_NB_NF |
						    SND_SOC_DAIFMT_CBM_CFM;
		पूर्ण

		अगर (hdmi_codec && म_भेद(dai_link->name, "TDM") == 0) अणु
			dai_link->codecs->of_node = hdmi_codec;
			dai_link->ignore = 0;
		पूर्ण

		अगर (!dai_link->platक्रमms->name)
			dai_link->platक्रमms->of_node = platक्रमm_node;
	पूर्ण

	mt8183_mt6358_ts3a227_max98357_headset_dev.dlc.of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "mediatek,headset-codec", 0);
	अगर (mt8183_mt6358_ts3a227_max98357_headset_dev.dlc.of_node) अणु
		card->aux_dev = &mt8183_mt6358_ts3a227_max98357_headset_dev;
		card->num_aux_devs = 1;
	पूर्ण

	priv = devm_kzalloc(&pdev->dev, माप(*priv), GFP_KERNEL);
	अगर (!priv)
		वापस -ENOMEM;

	snd_soc_card_set_drvdata(card, priv);

	priv->pinctrl = devm_pinctrl_get(&pdev->dev);
	अगर (IS_ERR(priv->pinctrl)) अणु
		dev_err(&pdev->dev, "%s devm_pinctrl_get failed\n",
			__func__);
		वापस PTR_ERR(priv->pinctrl);
	पूर्ण

	क्रम (i = 0; i < PIN_STATE_MAX; i++) अणु
		priv->pin_states[i] = pinctrl_lookup_state(priv->pinctrl,
							   mt8183_pin_str[i]);
		अगर (IS_ERR(priv->pin_states[i])) अणु
			ret = PTR_ERR(priv->pin_states[i]);
			dev_info(&pdev->dev, "%s Can't find pin state %s %d\n",
				 __func__, mt8183_pin_str[i], ret);
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(priv->pin_states[PIN_TDM_OUT_OFF])) अणु
		ret = pinctrl_select_state(priv->pinctrl,
					   priv->pin_states[PIN_TDM_OUT_OFF]);
		अगर (ret)
			dev_info(&pdev->dev,
				 "%s failed to select state %d\n",
				 __func__, ret);
	पूर्ण

	अगर (!IS_ERR(priv->pin_states[PIN_STATE_DEFAULT])) अणु
		ret = pinctrl_select_state(priv->pinctrl,
					   priv->pin_states[PIN_STATE_DEFAULT]);
		अगर (ret)
			dev_info(&pdev->dev,
				 "%s failed to select state %d\n",
				 __func__, ret);
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id mt8183_mt6358_ts3a227_max98357_dt_match[] = अणु
	अणु
		.compatible = "mediatek,mt8183_mt6358_ts3a227_max98357",
		.data = &mt8183_mt6358_ts3a227_max98357_card,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8183_mt6358_ts3a227_max98357b",
		.data = &mt8183_mt6358_ts3a227_max98357b_card,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8183_mt6358_ts3a227_rt1015",
		.data = &mt8183_mt6358_ts3a227_rt1015_card,
	पूर्ण,
	अणु
		.compatible = "mediatek,mt8183_mt6358_ts3a227_rt1015p",
		.data = &mt8183_mt6358_ts3a227_rt1015p_card,
	पूर्ण,
	अणुपूर्ण
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver mt8183_mt6358_ts3a227_max98357_driver = अणु
	.driver = अणु
		.name = "mt8183_mt6358_ts3a227",
#अगर_घोषित CONFIG_OF
		.of_match_table = mt8183_mt6358_ts3a227_max98357_dt_match,
#पूर्ण_अगर
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = mt8183_mt6358_ts3a227_max98357_dev_probe,
पूर्ण;

module_platक्रमm_driver(mt8183_mt6358_ts3a227_max98357_driver);

/* Module inक्रमmation */
MODULE_DESCRIPTION("MT8183-MT6358-TS3A227-MAX98357 ALSA SoC machine driver");
MODULE_AUTHOR("Shunli Wang <shunli.wang@mediatek.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("mt8183_mt6358_ts3a227_max98357 soc card");
