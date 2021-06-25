<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2018 Intel Corporation.

/*
 * Intel Kabylake I2S Machine Driver with MAX98927, MAX98373 & DA7219 Codecs
 *
 * Modअगरied from:
 *   Intel Kabylake I2S Machine driver supporting MAX98927 and
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
#समावेश "../../codecs/da7219.h"
#समावेश "../../codecs/hdac_hdmi.h"
#समावेश "../../codecs/da7219-aad.h"

#घोषणा KBL_DIALOG_CODEC_DAI	"da7219-hifi"
#घोषणा MAX98927_CODEC_DAI	"max98927-aif1"
#घोषणा MAX98927_DEV0_NAME	"i2c-MX98927:00"
#घोषणा MAX98927_DEV1_NAME	"i2c-MX98927:01"

#घोषणा MAX98373_CODEC_DAI	"max98373-aif1"
#घोषणा MAX98373_DEV0_NAME	"i2c-MX98373:00"
#घोषणा MAX98373_DEV1_NAME	"i2c-MX98373:01"


#घोषणा DUAL_CHANNEL	2
#घोषणा QUAD_CHANNEL	4
#घोषणा NAME_SIZE	32

अटल काष्ठा snd_soc_card *kabylake_audio_card;
अटल काष्ठा snd_soc_jack kabylake_hdmi[3];

काष्ठा kbl_hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा kbl_codec_निजी अणु
	काष्ठा snd_soc_jack kabylake_headset;
	काष्ठा list_head hdmi_pcm_list;
पूर्ण;

क्रमागत अणु
	KBL_DPCM_AUDIO_PB = 0,
	KBL_DPCM_AUDIO_ECHO_REF_CP,
	KBL_DPCM_AUDIO_REF_CP,
	KBL_DPCM_AUDIO_DMIC_CP,
	KBL_DPCM_AUDIO_HDMI1_PB,
	KBL_DPCM_AUDIO_HDMI2_PB,
	KBL_DPCM_AUDIO_HDMI3_PB,
	KBL_DPCM_AUDIO_HS_PB,
	KBL_DPCM_AUDIO_CP,
पूर्ण;

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
					काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret = 0;

	codec_dai = snd_soc_card_get_codec_dai(card, KBL_DIALOG_CODEC_DAI);
	अगर (!codec_dai) अणु
		dev_err(card->dev, "Codec dai not found; Unable to set/unset codec pll\n");
		वापस -EIO;
	पूर्ण

	/* Configure sysclk क्रम codec */
	ret = snd_soc_dai_set_sysclk(codec_dai, DA7219_CLKSRC_MCLK, 24576000,
				     SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		dev_err(card->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0,
				     DA7219_SYSCLK_MCLK, 0, 0);
		अगर (ret)
			dev_err(card->dev, "failed to stop PLL: %d\n", ret);
	पूर्ण अन्यथा अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0,	DA7219_SYSCLK_PLL_SRM,
				     0, DA7219_PLL_FREQ_OUT_98304);
		अगर (ret)
			dev_err(card->dev, "failed to start PLL: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new kabylake_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Left Spk"),
	SOC_DAPM_PIN_SWITCH("Right Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget kabylake_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),
	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
	SND_SOC_DAPM_SPK("HDMI1", शून्य),
	SND_SOC_DAPM_SPK("HDMI2", शून्य),
	SND_SOC_DAPM_SPK("HDMI3", शून्य),
	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			platक्रमm_घड़ी_control, SND_SOC_DAPM_PRE_PMU |
			SND_SOC_DAPM_POST_PMD),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route kabylake_map[] = अणु
	/* speaker */
	अणु "Left Spk", शून्य, "Left BE_OUT" पूर्ण,
	अणु "Right Spk", शून्य, "Right BE_OUT" पूर्ण,

	/* other jacks */
	अणु "DMic", शून्य, "SoC DMIC" पूर्ण,

	अणु"HDMI1", शून्य, "hif5-0 Output"पूर्ण,
	अणु"HDMI2", शून्य, "hif6-0 Output"पूर्ण,
	अणु"HDMI3", शून्य, "hif7-0 Output"पूर्ण,

	/* CODEC BE connections */
	अणु "Left HiFi Playback", शून्य, "ssp0 Tx" पूर्ण,
	अणु "Right HiFi Playback", शून्य, "ssp0 Tx" पूर्ण,
	अणु "ssp0 Tx", शून्य, "spk_out" पूर्ण,

	/* IV feedback path */
	अणु "codec0_fb_in", शून्य, "ssp0 Rx"पूर्ण,
	अणु "ssp0 Rx", शून्य, "Left HiFi Capture" पूर्ण,
	अणु "ssp0 Rx", शून्य, "Right HiFi Capture" पूर्ण,

	/* AEC capture path */
	अणु "echo_ref_out", शून्य, "ssp0 Rx" पूर्ण,

	/* DMIC */
	अणु "dmic01_hifi", शून्य, "DMIC01 Rx" पूर्ण,
	अणु "DMIC01 Rx", शून्य, "DMIC AIF" पूर्ण,

	अणु "hifi1", शून्य, "iDisp1 Tx" पूर्ण,
	अणु "iDisp1 Tx", शून्य, "iDisp1_out" पूर्ण,
	अणु "hifi2", शून्य, "iDisp2 Tx" पूर्ण,
	अणु "iDisp2 Tx", शून्य, "iDisp2_out" पूर्ण,
	अणु "hifi3", शून्य, "iDisp3 Tx"पूर्ण,
	अणु "iDisp3 Tx", शून्य, "iDisp3_out"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route kabylake_ssp1_map[] = अणु
	अणु "Headphone Jack", शून्य, "HPL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPR" पूर्ण,

	/* other jacks */
	अणु "MIC", शून्य, "Headset Mic" पूर्ण,

	/* CODEC BE connections */
	अणु "Playback", शून्य, "ssp1 Tx" पूर्ण,
	अणु "ssp1 Tx", शून्य, "codec1_out" पूर्ण,

	अणु "hs_in", शून्य, "ssp1 Rx" पूर्ण,
	अणु "ssp1 Rx", शून्य, "Capture" पूर्ण,

	अणु "Headphone Jack", शून्य, "Platform Clock" पूर्ण,
	अणु "Headset Mic", शून्य, "Platform Clock" पूर्ण,
पूर्ण;

अटल पूर्णांक kabylake_ssp0_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret, j;

	क्रम_each_rtd_codec_dais(runसमय, j, codec_dai) अणु

		अगर (!म_भेद(codec_dai->component->name, MAX98927_DEV0_NAME)) अणु
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x30, 3, 8, 16);
			अगर (ret < 0) अणु
				dev_err(runसमय->dev, "DEV0 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (!म_भेद(codec_dai->component->name, MAX98927_DEV1_NAME)) अणु
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0xC0, 3, 8, 16);
			अगर (ret < 0) अणु
				dev_err(runसमय->dev, "DEV1 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (!म_भेद(codec_dai->component->name, MAX98373_DEV0_NAME)) अणु
			ret = snd_soc_dai_set_tdm_slot(codec_dai,
							0x03, 3, 8, 24);
			अगर (ret < 0) अणु
				dev_err(runसमय->dev,
						"DEV0 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (!म_भेद(codec_dai->component->name, MAX98373_DEV1_NAME)) अणु
			ret = snd_soc_dai_set_tdm_slot(codec_dai,
							0x0C, 3, 8, 24);
			अगर (ret < 0) अणु
				dev_err(runसमय->dev,
						"DEV0 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक kabylake_ssp0_trigger(काष्ठा snd_pcm_substream *substream, पूर्णांक cmd)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक j, ret;

	क्रम_each_rtd_codec_dais(rtd, j, codec_dai) अणु
		स्थिर अक्षर *name = codec_dai->component->name;
		काष्ठा snd_soc_component *component = codec_dai->component;
		काष्ठा snd_soc_dapm_context *dapm =
				snd_soc_component_get_dapm(component);
		अक्षर pin_name[20];

		अगर (म_भेद(name, MAX98927_DEV0_NAME) &&
			म_भेद(name, MAX98927_DEV1_NAME) &&
			म_भेद(name, MAX98373_DEV0_NAME) &&
			म_भेद(name, MAX98373_DEV1_NAME))
			जारी;

		snम_लिखो(pin_name, ARRAY_SIZE(pin_name), "%s Spk",
			codec_dai->component->name_prefix);

		चयन (cmd) अणु
		हाल SNDRV_PCM_TRIGGER_START:
		हाल SNDRV_PCM_TRIGGER_RESUME:
		हाल SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
			ret = snd_soc_dapm_enable_pin(dapm, pin_name);
			अगर (ret) अणु
				dev_err(rtd->dev, "failed to enable %s: %d\n",
				pin_name, ret);
				वापस ret;
			पूर्ण
			snd_soc_dapm_sync(dapm);
			अवरोध;
		हाल SNDRV_PCM_TRIGGER_STOP:
		हाल SNDRV_PCM_TRIGGER_SUSPEND:
		हाल SNDRV_PCM_TRIGGER_PAUSE_PUSH:
			ret = snd_soc_dapm_disable_pin(dapm, pin_name);
			अगर (ret) अणु
				dev_err(rtd->dev, "failed to disable %s: %d\n",
				pin_name, ret);
				वापस ret;
			पूर्ण
			snd_soc_dapm_sync(dapm);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops kabylake_ssp0_ops = अणु
	.hw_params = kabylake_ssp0_hw_params,
	.trigger = kabylake_ssp0_trigger,
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
	 * Topology क्रम kblda7219m98373 & kblmax98373 supports only S24_LE,
	 * where as kblda7219m98927 & kblmax98927 supports S16_LE by शेष.
	 * Skipping the port wise FE and BE configuration क्रम kblda7219m98373 &
	 * kblmax98373 as the topology (FE & BE) supports S24_LE only.
	 */

	अगर (!म_भेद(rtd->card->name, "kblda7219m98373") ||
		!म_भेद(rtd->card->name, "kblmax98373")) अणु
		/* The ADSP will convert the FE rate to 48k, stereo */
		rate->min = rate->max = 48000;
		chan->min = chan->max = DUAL_CHANNEL;

		/* set SSP to 24 bit */
		snd_mask_none(fmt);
		snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S24_LE);
		वापस 0;
	पूर्ण

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
	पूर्ण

	/*
	 * The speaker on the SSP0 supports S16_LE and not S24_LE.
	 * thus changing the mask here
	 */
	अगर (!म_भेद(rtd_dpcm->be->dai_link->name, "SSP0-Codec"))
		snd_mask_set_क्रमmat(fmt, SNDRV_PCM_FORMAT_S16_LE);

	वापस 0;
पूर्ण

अटल पूर्णांक kabylake_da7219_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	काष्ठा snd_soc_jack *jack;
	काष्ठा snd_soc_card *card = rtd->card;
	पूर्णांक ret;


	ret = snd_soc_dapm_add_routes(&card->dapm,
			kabylake_ssp1_map,
			ARRAY_SIZE(kabylake_ssp1_map));

	अगर (ret)
		वापस ret;

	/*
	 * Headset buttons map to the google Reference headset.
	 * These can be configured by userspace.
	 */
	ret = snd_soc_card_jack_new(kabylake_audio_card, "Headset Jack",
			SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
			SND_JACK_BTN_2 | SND_JACK_BTN_3 | SND_JACK_LINEOUT,
			&ctx->kabylake_headset, शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack creation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	jack = &ctx->kabylake_headset;
	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);

	da7219_aad_jack_det(component, &ctx->kabylake_headset);

	वापस 0;
पूर्ण

अटल पूर्णांक kabylake_dmic_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	पूर्णांक ret;
	ret = snd_soc_dapm_ignore_suspend(&rtd->card->dapm, "SoC DMIC");
	अगर (ret)
		dev_err(rtd->dev, "SoC DMIC - Ignore suspend failed %d\n", ret);

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

अटल पूर्णांक kabylake_hdmi3_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस kabylake_hdmi_init(rtd, KBL_DPCM_AUDIO_HDMI3_PB);
पूर्ण

अटल पूर्णांक kabylake_da7219_fe_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dapm_context *dapm;
	काष्ठा snd_soc_component *component = asoc_rtd_to_cpu(rtd, 0)->component;

	dapm = snd_soc_component_get_dapm(component);
	snd_soc_dapm_ignore_suspend(dapm, "Reference Capture");

	वापस 0;
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
	DUAL_CHANNEL,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels = अणु
	.count = ARRAY_SIZE(channels),
	.list = channels,
	.mask = 0,
पूर्ण;

अटल अचिन्हित पूर्णांक channels_quad[] = अणु
	QUAD_CHANNEL,
पूर्ण;

अटल काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_channels_quad = अणु
	.count = ARRAY_SIZE(channels_quad),
	.list = channels_quad,
	.mask = 0,
पूर्ण;

अटल पूर्णांक kbl_fe_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *soc_rt = asoc_substream_to_rtd(substream);

	/*
	 * On this platक्रमm क्रम PCM device we support,
	 * 48Khz
	 * stereo
	 */

	runसमय->hw.channels_max = DUAL_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
					   &स्थिरraपूर्णांकs_channels);
	/*
	 * Setup S24_LE (32 bit container and 24 bit valid data) क्रम
	 * kblda7219m98373 & kblmax98373. For kblda7219m98927 &
	 * kblmax98927 keeping it as 16/16 due to topology FW dependency.
	 */
	अगर (!म_भेद(soc_rt->card->name, "kblda7219m98373") ||
		!म_भेद(soc_rt->card->name, "kblmax98373")) अणु
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S24_LE;
		snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);

	पूर्ण अन्यथा अणु
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S16_LE;
		snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 16, 16);
	पूर्ण

	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops kabylake_da7219_fe_ops = अणु
	.startup = kbl_fe_startup,
पूर्ण;

अटल पूर्णांक kabylake_dmic_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
		काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *chan = hw_param_पूर्णांकerval(params,
				SNDRV_PCM_HW_PARAM_CHANNELS);

	/*
	 * set BE channel स्थिरraपूर्णांक as user FE channels
	 */

	अगर (params_channels(params) == 2)
		chan->min = chan->max = 2;
	अन्यथा
		chan->min = chan->max = 4;

	वापस 0;
पूर्ण

अटल पूर्णांक kabylake_dmic_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_pcm_runसमय *runसमय = substream->runसमय;
	काष्ठा snd_soc_pcm_runसमय *soc_rt = asoc_substream_to_rtd(substream);

	runसमय->hw.channels_min = runसमय->hw.channels_max = QUAD_CHANNEL;
	snd_pcm_hw_स्थिरraपूर्णांक_list(runसमय, 0, SNDRV_PCM_HW_PARAM_CHANNELS,
			&स्थिरraपूर्णांकs_channels_quad);

	/*
	 * Topology क्रम kblda7219m98373 & kblmax98373 supports only S24_LE.
	 * The DMIC also configured क्रम S24_LE. Forcing the DMIC क्रमmat to
	 * S24_LE due to the topology FW dependency.
	 */
	अगर (!म_भेद(soc_rt->card->name, "kblda7219m98373") ||
		!म_भेद(soc_rt->card->name, "kblmax98373")) अणु
		runसमय->hw.क्रमmats = SNDRV_PCM_FMTBIT_S24_LE;
		snd_pcm_hw_स्थिरraपूर्णांक_msbits(runसमय, 0, 32, 24);
	पूर्ण

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
			SNDRV_PCM_HW_PARAM_RATE, &स्थिरraपूर्णांकs_rates);
पूर्ण

अटल काष्ठा snd_soc_ops kabylake_dmic_ops = अणु
	.startup = kabylake_dmic_startup,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक rates_16000[] = अणु
	16000,
पूर्ण;

अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_16000 = अणु
	.count = ARRAY_SIZE(rates_16000),
	.list  = rates_16000,
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक ch_mono[] = अणु
	1,
पूर्ण;
अटल स्थिर काष्ठा snd_pcm_hw_स्थिरraपूर्णांक_list स्थिरraपूर्णांकs_refcap = अणु
	.count = ARRAY_SIZE(ch_mono),
	.list  = ch_mono,
पूर्ण;

अटल पूर्णांक kabylake_refcap_startup(काष्ठा snd_pcm_substream *substream)
अणु
	substream->runसमय->hw.channels_max = 1;
	snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
					SNDRV_PCM_HW_PARAM_CHANNELS,
					&स्थिरraपूर्णांकs_refcap);

	वापस snd_pcm_hw_स्थिरraपूर्णांक_list(substream->runसमय, 0,
				SNDRV_PCM_HW_PARAM_RATE,
				&स्थिरraपूर्णांकs_16000);
पूर्ण


अटल काष्ठा snd_soc_ops skylake_refcap_ops = अणु
	.startup = kabylake_refcap_startup,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf max98927_codec_conf[] = अणु

	अणु
		.dlc = COMP_CODEC_CONF(MAX98927_DEV0_NAME),
		.name_prefix = "Right",
	पूर्ण,

	अणु
		.dlc = COMP_CODEC_CONF(MAX98927_DEV1_NAME),
		.name_prefix = "Left",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf max98373_codec_conf[] = अणु

	अणु
		.dlc = COMP_CODEC_CONF(MAX98373_DEV0_NAME),
		.name_prefix = "Right",
	पूर्ण,

	अणु
		.dlc = COMP_CODEC_CONF(MAX98373_DEV1_NAME),
		.name_prefix = "Left",
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_dai_link_component max98373_ssp0_codec_components[] = अणु
	अणु /* Left */
		.name = MAX98373_DEV0_NAME,
		.dai_name = MAX98373_CODEC_DAI,
	पूर्ण,

	अणु  /* For Right */
		.name = MAX98373_DEV1_NAME,
		.dai_name = MAX98373_CODEC_DAI,
	पूर्ण,

पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(प्रणाली,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin")));

SND_SOC_DAILINK_DEF(echoref,
	DAILINK_COMP_ARRAY(COMP_CPU("Echoref Pin")));

SND_SOC_DAILINK_DEF(reference,
	DAILINK_COMP_ARRAY(COMP_CPU("Reference Pin")));

SND_SOC_DAILINK_DEF(dmic,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC Pin")));

SND_SOC_DAILINK_DEF(hdmi1,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI1 Pin")));

SND_SOC_DAILINK_DEF(hdmi2,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI2 Pin")));

SND_SOC_DAILINK_DEF(hdmi3,
	DAILINK_COMP_ARRAY(COMP_CPU("HDMI3 Pin")));

SND_SOC_DAILINK_DEF(प्रणाली2,
	DAILINK_COMP_ARRAY(COMP_CPU("System Pin2")));

SND_SOC_DAILINK_DEF(ssp0_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP0 Pin")));
SND_SOC_DAILINK_DEF(ssp0_codec,
	DAILINK_COMP_ARRAY(
	/* Left */	COMP_CODEC(MAX98927_DEV0_NAME, MAX98927_CODEC_DAI),
	/* For Right */	COMP_CODEC(MAX98927_DEV1_NAME, MAX98927_CODEC_DAI)));

SND_SOC_DAILINK_DEF(ssp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAILINK_DEF(ssp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-DLGS7219:00",
				      KBL_DIALOG_CODEC_DAI)));

SND_SOC_DAILINK_DEF(dmic_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC01 Pin")));
SND_SOC_DAILINK_DEF(dmic_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

SND_SOC_DAILINK_DEF(idisp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp1 Pin")));
SND_SOC_DAILINK_DEF(idisp1_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi1")));

SND_SOC_DAILINK_DEF(idisp2_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp2 Pin")));
SND_SOC_DAILINK_DEF(idisp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi2")));

SND_SOC_DAILINK_DEF(idisp3_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("iDisp3 Pin")));
SND_SOC_DAILINK_DEF(idisp3_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("ehdaudio0D2", "intel-hdmi-hifi3")));

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
		.init = kabylake_da7219_fe_init,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.ops = &kabylake_da7219_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_ECHO_REF_CP] = अणु
		.name = "Kbl Audio Echo Reference cap",
		.stream_name = "Echoreference Capture",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		SND_SOC_DAILINK_REG(echoref, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_REF_CP] = अणु
		.name = "Kbl Audio Reference cap",
		.stream_name = "Wake on Voice",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &skylake_refcap_ops,
		SND_SOC_DAILINK_REG(reference, dummy, platक्रमm),
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
	[KBL_DPCM_AUDIO_HDMI3_PB] = अणु
		.name = "Kbl HDMI Port3",
		.stream_name = "Hdmi3",
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi3, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_HS_PB] = अणु
		.name = "Kbl Audio Headset Playback",
		.stream_name = "Headset Audio",
		.dpcm_playback = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.init = kabylake_da7219_fe_init,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.ops = &kabylake_da7219_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली2, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_CP] = अणु
		.name = "Kbl Audio Capture Port",
		.stream_name = "Audio Record",
		.dynamic = 1,
		.nonatomic = 1,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_capture = 1,
		.ops = &kabylake_da7219_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,

	/* Back End DAI links */
	अणु
		/* SSP0 - Codec */
		.name = "SSP0-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_DSP_B |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = kabylake_ssp_fixup,
		.ops = &kabylake_ssp0_ops,
		SND_SOC_DAILINK_REG(ssp0_pin, ssp0_codec, platक्रमm),
	पूर्ण,
	अणु
		/* SSP1 - Codec */
		.name = "SSP1-Codec",
		.id = 1,
		.no_pcm = 1,
		.init = kabylake_da7219_codec_init,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = kabylake_ssp_fixup,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp1_pin, ssp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic01",
		.id = 2,
		.init = kabylake_dmic_init,
		.be_hw_params_fixup = kabylake_dmic_fixup,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic_pin, dmic_codec, platक्रमm),
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
	अणु
		.name = "iDisp3",
		.id = 5,
		.init = kabylake_hdmi3_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* kabylake digital audio पूर्णांकerface glue - connects codec <--> CPU */
अटल काष्ठा snd_soc_dai_link kabylake_max98_927_373_dais[] = अणु
	/* Front End DAI links */
	[KBL_DPCM_AUDIO_PB] = अणु
		.name = "Kbl Audio Port",
		.stream_name = "Audio",
		.dynamic = 1,
		.nonatomic = 1,
		.init = kabylake_da7219_fe_init,
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.ops = &kabylake_da7219_fe_ops,
		SND_SOC_DAILINK_REG(प्रणाली, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_ECHO_REF_CP] = अणु
		.name = "Kbl Audio Echo Reference cap",
		.stream_name = "Echoreference Capture",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		SND_SOC_DAILINK_REG(echoref, dummy, platक्रमm),
	पूर्ण,
	[KBL_DPCM_AUDIO_REF_CP] = अणु
		.name = "Kbl Audio Reference cap",
		.stream_name = "Wake on Voice",
		.init = शून्य,
		.dpcm_capture = 1,
		.nonatomic = 1,
		.dynamic = 1,
		.ops = &skylake_refcap_ops,
		SND_SOC_DAILINK_REG(reference, dummy, platक्रमm),
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
	[KBL_DPCM_AUDIO_HDMI3_PB] = अणु
		.name = "Kbl HDMI Port3",
		.stream_name = "Hdmi3",
		.trigger = अणु
			SND_SOC_DPCM_TRIGGER_POST, SND_SOC_DPCM_TRIGGER_POSTपूर्ण,
		.dpcm_playback = 1,
		.init = शून्य,
		.nonatomic = 1,
		.dynamic = 1,
		SND_SOC_DAILINK_REG(hdmi3, dummy, platक्रमm),
	पूर्ण,

	/* Back End DAI links */
	अणु
		/* SSP0 - Codec */
		.name = "SSP0-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_DSP_B |
			SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ignore_pmकरोwn_समय = 1,
		.be_hw_params_fixup = kabylake_ssp_fixup,
		.ops = &kabylake_ssp0_ops,
		SND_SOC_DAILINK_REG(ssp0_pin, ssp0_codec),
	पूर्ण,
	अणु
		.name = "dmic01",
		.id = 1,
		.init = kabylake_dmic_init,
		.be_hw_params_fixup = kabylake_dmic_fixup,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 2,
		.dpcm_playback = 1,
		.init = kabylake_hdmi1_init,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 3,
		.init = kabylake_hdmi2_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 4,
		.init = kabylake_hdmi3_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल पूर्णांक kabylake_card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा kbl_codec_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा kbl_hdmi_pcm *pcm;
	काष्ठा snd_soc_dapm_context *dapm = &card->dapm;
	काष्ठा snd_soc_component *component = शून्य;
	पूर्णांक err, i = 0;
	अक्षर jack_name[NAME_SIZE];

	list_क्रम_each_entry(pcm, &ctx->hdmi_pcm_list, head) अणु
		component = pcm->codec_dai->component;
		snम_लिखो(jack_name, माप(jack_name),
			"HDMI/DP, pcm=%d Jack", pcm->device);
		err = snd_soc_card_jack_new(card, jack_name,
					SND_JACK_AVOUT, &kabylake_hdmi[i],
					शून्य, 0);

		अगर (err)
			वापस err;

		err = hdac_hdmi_jack_init(pcm->codec_dai, pcm->device,
						&kabylake_hdmi[i]);
		अगर (err < 0)
			वापस err;

		i++;
	पूर्ण

	अगर (!component)
		वापस -EINVAL;


	err = hdac_hdmi_jack_port_init(component, &card->dapm);

	अगर (err < 0)
		वापस err;

	err = snd_soc_dapm_disable_pin(dapm, "Left Spk");
	अगर (err) अणु
		dev_err(card->dev, "failed to disable Left Spk: %d\n", err);
		वापस err;
	पूर्ण

	err = snd_soc_dapm_disable_pin(dapm, "Right Spk");
	अगर (err) अणु
		dev_err(card->dev, "failed to disable Right Spk: %d\n", err);
		वापस err;
	पूर्ण

	वापस snd_soc_dapm_sync(dapm);
पूर्ण

/* kabylake audio machine driver क्रम SPT + DA7219 */
अटल काष्ठा snd_soc_card kbl_audio_card_da7219_m98927 = अणु
	.name = "kblda7219m98927",
	.owner = THIS_MODULE,
	.dai_link = kabylake_dais,
	.num_links = ARRAY_SIZE(kabylake_dais),
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

/* kabylake audio machine driver क्रम Maxim98927 */
अटल काष्ठा snd_soc_card kbl_audio_card_max98927 = अणु
	.name = "kblmax98927",
	.owner = THIS_MODULE,
	.dai_link = kabylake_max98_927_373_dais,
	.num_links = ARRAY_SIZE(kabylake_max98_927_373_dais),
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

अटल काष्ठा snd_soc_card kbl_audio_card_da7219_m98373 = अणु
	.name = "kblda7219m98373",
	.owner = THIS_MODULE,
	.dai_link = kabylake_dais,
	.num_links = ARRAY_SIZE(kabylake_dais),
	.controls = kabylake_controls,
	.num_controls = ARRAY_SIZE(kabylake_controls),
	.dapm_widमाला_लो = kabylake_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(kabylake_widमाला_लो),
	.dapm_routes = kabylake_map,
	.num_dapm_routes = ARRAY_SIZE(kabylake_map),
	.codec_conf = max98373_codec_conf,
	.num_configs = ARRAY_SIZE(max98373_codec_conf),
	.fully_routed = true,
	.late_probe = kabylake_card_late_probe,
पूर्ण;

अटल काष्ठा snd_soc_card kbl_audio_card_max98373 = अणु
	.name = "kblmax98373",
	.owner = THIS_MODULE,
	.dai_link = kabylake_max98_927_373_dais,
	.num_links = ARRAY_SIZE(kabylake_max98_927_373_dais),
	.controls = kabylake_controls,
	.num_controls = ARRAY_SIZE(kabylake_controls),
	.dapm_widमाला_लो = kabylake_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(kabylake_widमाला_लो),
	.dapm_routes = kabylake_map,
	.num_dapm_routes = ARRAY_SIZE(kabylake_map),
	.codec_conf = max98373_codec_conf,
	.num_configs = ARRAY_SIZE(max98373_codec_conf),
	.fully_routed = true,
	.late_probe = kabylake_card_late_probe,
पूर्ण;

अटल पूर्णांक kabylake_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा kbl_codec_निजी *ctx;
	काष्ठा snd_soc_dai_link *kbl_dai_link;
	काष्ठा snd_soc_dai_link_component **codecs;
	पूर्णांक i;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);

	kabylake_audio_card =
		(काष्ठा snd_soc_card *)pdev->id_entry->driver_data;

	kbl_dai_link = kabylake_audio_card->dai_link;

	/* Update codecs क्रम SSP0 with max98373 codec info */
	अगर (!म_भेद(pdev->name, "kbl_da7219_max98373") ||
		(!म_भेद(pdev->name, "kbl_max98373"))) अणु
		क्रम (i = 0; i < kabylake_audio_card->num_links; ++i) अणु
			अगर (म_भेद(kbl_dai_link[i].name, "SSP0-Codec"))
				जारी;

			codecs = &(kbl_dai_link[i].codecs);
			*codecs = max98373_ssp0_codec_components;
			kbl_dai_link[i].num_codecs =
				ARRAY_SIZE(max98373_ssp0_codec_components);
			अवरोध;
		पूर्ण
	पूर्ण
	kabylake_audio_card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(kabylake_audio_card, ctx);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, kabylake_audio_card);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id kbl_board_ids[] = अणु
	अणु
		.name = "kbl_da7219_max98927",
		.driver_data =
			(kernel_uदीर्घ_t)&kbl_audio_card_da7219_m98927,
	पूर्ण,
	अणु
		.name = "kbl_max98927",
		.driver_data =
			(kernel_uदीर्घ_t)&kbl_audio_card_max98927,
	पूर्ण,
	अणु
		.name = "kbl_da7219_max98373",
		.driver_data =
			(kernel_uदीर्घ_t)&kbl_audio_card_da7219_m98373,
	पूर्ण,
	अणु
		.name = "kbl_max98373",
		.driver_data =
			(kernel_uदीर्घ_t)&kbl_audio_card_max98373,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver kabylake_audio = अणु
	.probe = kabylake_audio_probe,
	.driver = अणु
		.name = "kbl_da7219_max98_927_373",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = kbl_board_ids,
पूर्ण;

module_platक्रमm_driver(kabylake_audio)

/* Module inक्रमmation */
MODULE_DESCRIPTION("Audio KabyLake Machine driver for MAX98927/MAX98373 & DA7219");
MODULE_AUTHOR("Mac Chiang <mac.chiang@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:kbl_da7219_max98927");
MODULE_ALIAS("platform:kbl_max98927");
MODULE_ALIAS("platform:kbl_da7219_max98373");
MODULE_ALIAS("platform:kbl_max98373");
