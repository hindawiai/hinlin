<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Intel Kabylake I2S Machine Driver with MAXIM98927
 * RT5514 and RT5663 Codecs
 *
 * Copyright (C) 2017, Intel Corporation. All rights reserved.
 *
 * Modअगरied from:
 *   Intel Kabylake I2S Machine driver supporting MAXIM98927 and
 *   RT5663 codecs
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/rt5514.h"
#समावेश "../../codecs/rt5663.h"
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश <linux/clk.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/clkdev.h>

#घोषणा KBL_REALTEK_CODEC_DAI "rt5663-aif"
#घोषणा KBL_REALTEK_DMIC_CODEC_DAI "rt5514-aif1"
#घोषणा KBL_MAXIM_CODEC_DAI "max98927-aif1"
#घोषणा MAXIM_DEV0_NAME "i2c-MX98927:00"
#घोषणा MAXIM_DEV1_NAME "i2c-MX98927:01"
#घोषणा RT5514_DEV_NAME "i2c-10EC5514:00"
#घोषणा RT5663_DEV_NAME "i2c-10EC5663:00"
#घोषणा RT5514_AIF1_BCLK_FREQ (48000 * 8 * 16)
#घोषणा RT5514_AIF1_SYSCLK_FREQ 12288000
#घोषणा NAME_SIZE 32

#घोषणा DMIC_CH(p) p->list[p->count-1]


अटल काष्ठा snd_soc_card kabylake_audio_card;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list *dmic_स्थिरraपूर्णांकs;

काष्ठा kbl_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा kbl_codec_निजी अणु
	काष्ठा snd_soc_jack kabylake_headset;
	काष्ठा list_head hdmi_pcm_list;
	काष्ठा snd_soc_jack kabylake_hdmi[2];
	काष्ठा clk *mclk;
	काष्ठा clk *sclk;
पूर्ण;

क्रमागत अणु
	KBL_DPCM_AUDIO_PB = 0,
	KBL_DPCM_AUDIO_CP,
	KBL_DPCM_AUDIO_HS_PB,
	KBL_DPCM_AUDIO_ECHO_REF_CP,
	KBL_DPCM_AUDIO_DMIC_CP,
	KBL_DPCM_AUDIO_RT5514_DSP,
	KBL_DPCM_AUDIO_HDMI1_PB,
	KBL_DPCM_AUDIO_HDMI2_PB,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new kabylake_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Left Spk"),
	SOC_DAPM_PIN_SWITCH("Right Spk"),
	SOC_DAPM_PIN_SWITCH("DMIC"),
पूर्ण;

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
			काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा kbl_codec_निजी *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret = 0;

	/*
	 * MCLK/SCLK need to be ON early क्रम a successful synchronization of
	 * codec पूर्णांकernal घड़ी. And the घड़ीs are turned off during
	 * POST_PMD after the stream is stopped.
	 */
	चयन (event) अणु
	हाल SND_SOC_DAPM_PRE_PMU:
		/* Enable MCLK */
		ret = clk_set_rate(priv->mclk, 24000000);
		अगर (ret < 0) अणु
			dev_err(card->dev, "Can't set rate for mclk, err: %d\n",
				ret);
			वापस ret;
		पूर्ण

		ret = clk_prepare_enable(priv->mclk);
		अगर (ret < 0) अणु
			dev_err(card->dev, "Can't enable mclk, err: %d\n", ret);
			वापस ret;
		पूर्ण

		/* Enable SCLK */
		ret = clk_set_rate(priv->sclk, 3072000);
		अगर (ret < 0) अणु
			dev_err(card->dev, "Can't set rate for sclk, err: %d\n",
				ret);
			clk_disable_unprepare(priv->mclk);
			वापस ret;
		पूर्ण

		ret = clk_prepare_enable(priv->sclk);
		अगर (ret < 0) अणु
			dev_err(card->dev, "Can't enable sclk, err: %d\n", ret);
			clk_disable_unprepare(priv->mclk);
		पूर्ण
		अवरोध;
	हाल SND_SOC_DAPM_POST_PMD:
		clk_disable_unprepare(priv->mclk);
		clk_disable_unprepare(priv->sclk);
		अवरोध;
	शेष:
		वापस 0;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_widget kabylake_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),
	SND_SOC_DAPM_MIC("DMIC", शून्य),
	SND_SOC_DAPM_SPK("HDMI1", शून्य),
	SND_SOC_DAPM_SPK("HDMI2", शून्य),
	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			platक्रमm_घड़ी_control, SND_SOC_DAPM_PRE_PMU |
			SND_SOC_DAPM_POST_PMD),

पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route kabylake_map[] = अणु
	/* Headphones */
	अणु "Headphone Jack", शून्य, "Platform Clock" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPOL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPOR" पूर्ण,

	/* speaker */
	अणु "Left Spk", शून्य, "Left BE_OUT" पूर्ण,
	अणु "Right Spk", शून्य, "Right BE_OUT" पूर्ण,

	/* other jacks */
	अणु "Headset Mic", शून्य, "Platform Clock" पूर्ण,
	अणु "IN1P", शून्य, "Headset Mic" पूर्ण,
	अणु "IN1N", शून्य, "Headset Mic" पूर्ण,

	/* CODEC BE connections */
	अणु "Left HiFi Playback", शून्य, "ssp0 Tx" पूर्ण,
	अणु "Right HiFi Playback", शून्य, "ssp0 Tx" पूर्ण,
	अणु "ssp0 Tx", शून्य, "spk_out" पूर्ण,

	अणु "AIF Playback", शून्य, "ssp1 Tx" पूर्ण,
	अणु "ssp1 Tx", शून्य, "codec1_out" पूर्ण,

	अणु "hs_in", शून्य, "ssp1 Rx" पूर्ण,
	अणु "ssp1 Rx", शून्य, "AIF Capture" पूर्ण,

	अणु "codec1_in", शून्य, "ssp0 Rx" पूर्ण,
	अणु "ssp0 Rx", शून्य, "AIF1 Capture" पूर्ण,

	/* IV feedback path */
	अणु "codec0_fb_in", शून्य, "ssp0 Rx"पूर्ण,
	अणु "ssp0 Rx", शून्य, "Left HiFi Capture" पूर्ण,
	अणु "ssp0 Rx", शून्य, "Right HiFi Capture" पूर्ण,

	/* DMIC */
	अणु "DMIC1L", शून्य, "DMIC" पूर्ण,
	अणु "DMIC1R", शून्य, "DMIC" पूर्ण,
	अणु "DMIC2L", शून्य, "DMIC" पूर्ण,
	अणु "DMIC2R", शून्य, "DMIC" पूर्ण,

	अणु "hifi2", शून्य, "iDisp2 Tx" पूर्ण,
	अणु "iDisp2 Tx", शून्य, "iDisp2_out" पूर्ण,
	अणु "hifi1", शून्य, "iDisp1 Tx" पूर्ण,
	अणु "iDisp1 Tx", शून्य, "iDisp1_out" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf max98927_codec_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF(MAXIM_DEV0_NAME),
		.name_prefix = "Right",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF(MAXIM_DEV1_NAME),
		.name_prefix = "Left",
	पूर्ण,
पूर्ण;


अटल पूर्णांक kabylake_rt5663_fe_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा snd_soc_component *component = asoc_rtd_to_cpu(rtd, 0)->component;
	पूर्णांक ret;

	dapm = snd_soc_component_get_dapm(component);
	ret = snd_soc_dapm_ignore_suspend(dapm, "Reference Capture");
	अगर (ret)
		dev_err(rtd->dev, "Ref Cap -Ignore suspend failed = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक kabylake_rt5663_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_jack *jack;

	/*
	 * Headset buttons map to the google Reference headset.
	 * These can be configured by userspace.
	 */
	ret = snd_soc_card_jack_new(&kabylake_audio_card, "Headset Jack",
			SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3, &ctx->kabylake_headset,
			शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण

	jack = &ctx->kabylake_headset;
	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	snd_soc_component_set_jack(component, &ctx->kabylake_headset, शून्य);

	ret = snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "DMIC");
	अगर (ret)
		dev_err(rtd->dev, "DMIC - Ignore suspend failed = %d\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक kabylake_hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd, पूर्णांक device)
अणु
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा kbl_hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	pcm->device = device;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

अटल पूर्णांक kabylake_hdmi1_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस kabylake_hdmi_init(rtd, KBL_DPCM_AUDIO_HDMI1_PB);
पूर्ण

अटल पूर्णांक kabylake_hdmi2_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस kabylake_hdmi_init(rtd, KBL_DPCM_AUDIO_HDMI2_PB);
पूर्ण

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

अटल पूर्णांक kbl_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	/*
	 * On this platक्रमm क्रम PCM device we support,
	 * 48Khz
	 * stereo
	 * 16 bit audio
	 */

	runसमय->hw.channels_max = 2;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					   &स्थिरraपूर्णांकs_channels);

	runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 16, 16);

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops kabylake_rt5663_fe_ops = अणु
	.startup = kbl_fe_startup,
पूर्ण;

अटल पूर्णांक kabylake_ssp_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
					काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
			SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmt = hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	काष्ठा snd_soc_dpcm *dpcm, *rtd_dpcm = शून्य;

	/*
	 * The following loop will be called only क्रम playback stream
	 * In this platक्रमm, there is only one playback device on every SSP
	 */
	क्रम_each_dpcm_fe(rtd, SNDRV_PCM_STREAM_PLAYBACK, dpcm) अणु
		rtd_dpcm = dpcm;
		अवरोध;
	पूर्ण

	/*
	 * This following loop will be called only क्रम capture stream
	 * In this platक्रमm, there is only one capture device on every SSP
	 */
	क्रम_each_dpcm_fe(rtd, SNDRV_PCM_STREAM_CAPTURE, dpcm) अणु
		rtd_dpcm = dpcm;
		अवरोध;
	पूर्ण

	अगर (!rtd_dpcm)
		वापस -EINVAL;

	/*
	 * The above 2 loops are mutually exclusive based on the stream direction,
	 * thus rtd_dpcm variable will never be overwritten
	 */

	/*
	 * The ADSP will convert the FE rate to 48k, stereo, 24 bit
	 */
	अगर (!म_भेद(rtd_dpcm->fe->dai_link->name, "Kbl Audio Port") ||
	    !म_भेद(rtd_dpcm->fe->dai_link->name, "Kbl Audio Headset Playback") ||
	    !म_भेद(rtd_dpcm->fe->dai_link->name, "Kbl Audio Capture Port")) अणु
		rate->min = rate->max = 48000;
		chan->min = chan->max = 2;
		snd_mask_none(fmt);
		snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S24_LE);
	पूर्ण अन्यथा अगर (!म_भेद(rtd_dpcm->fe->dai_link->name, "Kbl Audio DMIC cap")) अणु
		अगर (params_channels(params) == 2 ||
				DMIC_CH(dmic_स्थिरraपूर्णांकs) == 2)
			chan->min = chan->max = 2;
		अन्यथा
			chan->min = chan->max = 4;
	पूर्ण
	/*
	 * The speaker on the SSP0 supports S16_LE and not S24_LE.
	 * thus changing the mask here
	 */
	अगर (!म_भेद(rtd_dpcm->be->dai_link->name, "SSP0-Codec"))
		snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S16_LE);

	वापस 0;
पूर्ण

अटल पूर्णांक kabylake_rt5663_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	/* use ASRC क्रम पूर्णांकernal घड़ीs, as PLL rate isn't multiple of BCLK */
	rt5663_sel_asrc_clk_src(codec_dai->component,
			RT5663_DA_STEREO_FILTER | RT5663_AD_STEREO_FILTER,
			RT5663_CLK_SEL_I2S1_ASRC);

	ret = snd_soc_dai_set_sysclk(codec_dai,
			RT5663_SCLK_S_MCLK, 24576000, SND_SOC_CLOCK_IN);
	अगर (ret < 0)
		dev_err(rtd->dev, "snd_soc_dai_set_sysclk err = %d\n", ret);

	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops kabylake_rt5663_ops = अणु
	.hw_params = kabylake_rt5663_hw_params,
पूर्ण;

अटल पूर्णांक kabylake_ssp0_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret = 0, j;

	क्रम_each_rtd_codec_dais(rtd, j, codec_dai) अणु
		अगर (!म_भेद(codec_dai->component->name, RT5514_DEV_NAME)) अणु
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0xF, 0, 8, 16);
			अगर (ret < 0) अणु
				dev_err(rtd->dev, "set TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण

			ret = snd_soc_dai_set_sysclk(codec_dai,
				RT5514_SCLK_S_MCLK, 24576000, SND_SOC_CLOCK_IN);
			अगर (ret < 0) अणु
				dev_err(rtd->dev, "set sysclk err: %d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (!म_भेद(codec_dai->component->name, MAXIM_DEV0_NAME)) अणु
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x30, 3, 8, 16);
			अगर (ret < 0) अणु
				dev_err(rtd->dev, "DEV0 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण

		अगर (!म_भेद(codec_dai->component->name, MAXIM_DEV1_NAME)) अणु
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0xC0, 3, 8, 16);
			अगर (ret < 0) अणु
				dev_err(rtd->dev, "DEV1 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा snd_soc_ops kabylake_ssp0_ops = अणु
	.hw_params = kabylake_ssp0_hw_params,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक channels_dmic[] = अणु
	4,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_dmic_channels = अणु
	.count = ARRAY_SIZE(channels_dmic),
	.list = channels_dmic,
	.mask = 0,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक dmic_2ch[] = अणु
	2,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_dmic_2ch = अणु
	.count = ARRAY_SIZE(dmic_2ch),
	.list = dmic_2ch,
	.mask = 0,
पूर्ण;

अटल पूर्णांक kabylake_dmic_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;

	runसमय->hw.channels_max = DMIC_CH(dmic_स्थिरraपूर्णांकs);
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			dmic_स्थिरraपूर्णांकs);

	runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
	snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 16, 16);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);
पूर्ण

अटल काष्ठा snd_soc_ops kabylake_dmic_ops = अणु
	.startup = kabylake_dmic_startup,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(प्रणाली2,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin2")));

SND_SOC_DAILINK_DEF(echoref,
	DAILINK_COMP_ARRAY(COMP_CPU("Echoref Pin")));

SND_SOC_DAILINK_DEF(spi_cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("spi-PRP0001:00")));
SND_SOC_DAILINK_DEF(spi_platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("spi-PRP0001:00")));

SND_SOC_DAILINK_DEF(dmic,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC Pin")));

SND_SOC_DAILINK_DEF(hdmi1,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI1 Pin")));

SND_SOC_DAILINK_DEF(hdmi2,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI2 Pin")));

SND_SOC_DAILINK_DEF(ssp0_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP0 Pin")));
SND_SOC_DAILINK_DEF(ssp0_codec,
	DAILINK_COMP_ARRAY(
	/* Left */ COMP_CODEC(MAXIM_DEV0_NAME, KBL_MAXIM_CODEC_DAI),
	/* Right */COMP_CODEC(MAXIM_DEV1_NAME, KBL_MAXIM_CODEC_DAI),
	/* dmic */ COMP_CODEC(RT5514_DEV_NAME, KBL_REALTEK_DMIC_CODEC_DAI)));

SND_SOC_DAILINK_DEF(ssp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAILINK_DEF(ssp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC(RT5663_DEV_NAME, KBL_REALTEK_CODEC_DAI)));

SND_SOC_DAILINK_DEF(idisp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAILINK_DEF(idisp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi1")));

SND_SOC_DAILINK_DEF(idisp2_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAILINK_DEF(idisp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi2")));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:1f.3")));

/* kabylake digital audio पूर्णांकerface glue - connects codec <--> CPU */
अटल काष्ठा snd_soc_dai_link kabylake_dais[] = अणु
	/* Front End DAI links */
	[KBL_DPCM_AUDIO_PB] = अणु
		.name = "Kbl Audio Port",
		.stream_name = "Audio",
		.dynamic = 1,
		.nonatomic = 1,
		.init = kabylake_rt5663_fe_init,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.ops = &kabylake_rt5663_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_CP] = अणु
		.name = "Kbl Audio Capture Port",
		.stream_name = "Audio Record",
		.dynamic = 1,
		.nonatomic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_capture = 1,
		.ops = &kabylake_rt5663_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_HS_PB] = अणु
		.name = "Kbl Audio Headset Playback",
		.stream_name = "Headset Audio",
		.dpcm_playback = 1,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(प्रणाली2, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_ECHO_REF_CP] = अणु
		.name = "Kbl Audio Echo Reference cap",
		.stream_name = "Echoreference Capture",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		SND_SOC_DAILINK_REG(echoref, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_RT5514_DSP] = अणु
		.name = "rt5514 dsp",
		.stream_name = "Wake on Voice",
		SND_SOC_DAILINK_REG(spi_cpu, dummy, spi_platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_DMIC_CP] = अणु
		.name = "Kbl Audio DMIC cap",
		.stream_name = "dmiccap",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &kabylake_dmic_ops,
		SND_SOC_DAILINK_REG(dmic, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_HDMI1_PB] = अणु
		.name = "Kbl HDMI Port1",
		.stream_name = "Hdmi1",
		.dpcm_playback = 1,
		.init = शून्य,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi1, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_HDMI2_PB] = अणु
		.name = "Kbl HDMI Port2",
		.stream_name = "Hdmi2",
		.dpcm_playback = 1,
		.init = शून्य,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi2, dummy, platक्रमm),
	पूर्ण,
	/* Back End DAI links */
	/* single Back end dai क्रम both max speakers and dmic */
	अणु
		/* SSP0 - Codec */
		.name = "SSP0-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_DSP_B |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = kabylake_ssp_fixup,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &kabylake_ssp0_ops,
		SND_SOC_DAILINK_REG(ssp0_pin, ssp0_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "SSP1-Codec",
		.id = 1,
		.no_pcm = 1,
		.init = kabylake_rt5663_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = kabylake_ssp_fixup,
		.ops = &kabylake_rt5663_ops,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp1_pin, ssp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 3,
		.dpcm_playback = 1,
		.init = kabylake_hdmi1_init,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 4,
		.init = kabylake_hdmi2_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल पूर्णांक kabylake_set_bias_level(काष्ठा snd_soc_card *card,
	काष्ठा snd_soc_dapm_context *dapm, क्रमागत snd_soc_bias_level level)
अणु
	काष्ठा snd_soc_component *component = dapm->component;
	काष्ठा kbl_codec_निजी *priv = snd_soc_card_get_drvdata(card);
	पूर्णांक ret = 0;

	अगर (!component || म_भेद(component->name, RT5514_DEV_NAME))
		वापस 0;

	अगर (IS_ERR(priv->mclk))
		वापस 0;

	/*
	 * It's required to control mclk directly in the set_bias_level
	 * function क्रम rt5514 codec or the recording function could
	 * अवरोध.
	 */
	चयन (level) अणु
	हाल SND_SOC_BIAS_PREPARE:
		अगर (dapm->bias_level == SND_SOC_BIAS_ON) अणु
			अगर (!__clk_is_enabled(priv->mclk))
				वापस 0;
			dev_dbg(card->dev, "Disable mclk");
			clk_disable_unprepare(priv->mclk);
		पूर्ण अन्यथा अणु
			dev_dbg(card->dev, "Enable mclk");
			ret = clk_set_rate(priv->mclk, 24000000);
			अगर (ret) अणु
				dev_err(card->dev, "Can't set rate for mclk, err: %d\n",
					ret);
				वापस ret;
			पूर्ण

			ret = clk_prepare_enable(priv->mclk);
			अगर (ret) अणु
				dev_err(card->dev, "Can't enable mclk, err: %d\n",
					ret);

				/* mclk is alपढ़ोy enabled in FW */
				ret = 0;
			पूर्ण
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक kabylake_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा kbl_hdmi_pcm *pcm;
	काष्ठा snd_soc_component *component = शून्य;
	पूर्णांक err, i = 0;
	अक्षर jack_name[NAME_SIZE];

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			"HDMI/DP,pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
				SND_JACK_AVOUT, &ctx->kabylake_hdmi[i],
				शून्य, 0);

		अगर (err)
			वापस err;
		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
						&ctx->kabylake_hdmi[i]);
		अगर (err < 0)
			वापस err;
		i++;
	पूर्ण

	अगर (!component)
		वापस -EINVAL;

	वापस hdac_hdmi_jack_port_init(component, &card->dapm);
पूर्ण

/*
 * kabylake audio machine driver क्रम  MAX98927 + RT5514 + RT5663
 */
अटल काष्ठा snd_soc_card kabylake_audio_card = अणु
	.name = "kbl-r5514-5663-max",
	.owner = THIS_MODULE,
	.dai_link = kabylake_dais,
	.num_links = ARRAY_SIZE(kabylake_dais),
	.set_bias_level = kabylake_set_bias_level,
	.controls = kabylake_controls,
	.num_controls = ARRAY_SIZE(kabylake_controls),
	.dapm_widमाला_लो = kabylake_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(kabylake_widमाला_लो),
	.dapm_routes = kabylake_map,
	.num_dapm_routes = ARRAY_SIZE(kabylake_map),
	.codec_conf = max98927_codec_conf,
	.num_configs = ARRAY_SIZE(max98927_codec_conf),
	.fully_routed = true,
	.late_probe = kabylake_card_late_probe,
पूर्ण;

अटल पूर्णांक kabylake_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kbl_codec_निजी *ctx;
	काष्ठा snd_soc_acpi_mach *mach;
	पूर्णांक ret;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	kabylake_audio_card.dev = &pdev->dev;
	snd_soc_card_set_drvdata(&kabylake_audio_card, ctx);

	mach = pdev->dev.platक्रमm_data;
	अगर (mach)
		dmic_स्थिरraपूर्णांकs = mach->mach_params.dmic_num == 2 ?
			&स्थिरraपूर्णांकs_dmic_2ch : &स्थिरraपूर्णांकs_dmic_channels;

	ctx->mclk = devm_clk_get(&pdev->dev, "ssp1_mclk");
	अगर (IS_ERR(ctx->mclk)) अणु
		ret = PTR_ERR(ctx->mclk);
		अगर (ret == -ENOENT) अणु
			dev_info(&pdev->dev,
				"Failed to get ssp1_mclk, defer probe\n");
			वापस -EPROBE_DEFER;
		पूर्ण

		dev_err(&pdev->dev, "Failed to get ssp1_mclk with err:%d\n",
								ret);
		वापस ret;
	पूर्ण

	ctx->sclk = devm_clk_get(&pdev->dev, "ssp1_sclk");
	अगर (IS_ERR(ctx->sclk)) अणु
		ret = PTR_ERR(ctx->sclk);
		अगर (ret == -ENOENT) अणु
			dev_info(&pdev->dev,
				"Failed to get ssp1_sclk, defer probe\n");
			वापस -EPROBE_DEFER;
		पूर्ण

		dev_err(&pdev->dev, "Failed to get ssp1_sclk with err:%d\n",
								ret);
		वापस ret;
	पूर्ण

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, &kabylake_audio_card);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id kbl_board_ids[] = अणु
	अणु .name = "kbl_r5514_5663_max" पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver kabylake_audio = अणु
	.probe = kabylake_audio_probe,
	.driver = अणु
		.name = "kbl_r5514_5663_max",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = kbl_board_ids,
पूर्ण;

module_platक्रमm_driver(kabylake_audio)

/* Module inक्रमmation */
MODULE_DESCRIPTION("Audio Machine driver-RT5663 RT5514 & MAX98927");
MODULE_AUTHOR("Harsha Priya <harshapriya.n@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:kbl_r5514_5663_max");
