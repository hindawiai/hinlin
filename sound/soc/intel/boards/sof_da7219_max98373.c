<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
// Copyright(c) 2019 Intel Corporation.

/*
 * Intel SOF Machine driver क्रम DA7219 + MAX98373/MAX98360A codec
 */

#समावेश <linux/input.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश "../../codecs/da7219.h"
#समावेश "../../codecs/da7219-aad.h"
#समावेश "hda_dsp_common.h"

#घोषणा DIALOG_CODEC_DAI	"da7219-hifi"
#घोषणा MAX98373_CODEC_DAI	"max98373-aif1"
#घोषणा MAXIM_DEV0_NAME		"i2c-MX98373:00"
#घोषणा MAXIM_DEV1_NAME		"i2c-MX98373:01"

काष्ठा hdmi_pcm अणु
	काष्ठा list_head head;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक device;
पूर्ण;

काष्ठा card_निजी अणु
	काष्ठा snd_soc_jack headset;
	काष्ठा list_head hdmi_pcm_list;
	काष्ठा snd_soc_jack hdmi[3];
पूर्ण;

अटल पूर्णांक platक्रमm_घड़ी_control(काष्ठा snd_soc_dapm_widget *w,
				  काष्ठा snd_kcontrol *k, पूर्णांक  event)
अणु
	काष्ठा snd_soc_dapm_context *dapm = w->dapm;
	काष्ठा snd_soc_card *card = dapm->card;
	काष्ठा snd_soc_dai *codec_dai;
	पूर्णांक ret = 0;

	codec_dai = snd_soc_card_get_codec_dai(card, DIALOG_CODEC_DAI);
	अगर (!codec_dai) अणु
		dev_err(card->dev, "Codec dai not found; Unable to set/unset codec pll\n");
		वापस -EIO;
	पूर्ण

	अगर (SND_SOC_DAPM_EVENT_OFF(event)) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0, DA7219_SYSCLK_MCLK,
					  0, 0);
		अगर (ret)
			dev_err(card->dev, "failed to stop PLL: %d\n", ret);
	पूर्ण अन्यथा अगर (SND_SOC_DAPM_EVENT_ON(event)) अणु
		ret = snd_soc_dai_set_pll(codec_dai, 0, DA7219_SYSCLK_PLL_SRM,
					  0, DA7219_PLL_FREQ_OUT_98304);
		अगर (ret)
			dev_err(card->dev, "failed to start PLL: %d\n", ret);
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Left Spk"),
	SOC_DAPM_PIN_SWITCH("Right Spk"),
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new m98360a_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone Jack"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Spk"),
पूर्ण;

/* For MAX98373 amp */
अटल स्थिर काष्ठा snd_soc_dapm_widget widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),

	SND_SOC_DAPM_SPK("Left Spk", शून्य),
	SND_SOC_DAPM_SPK("Right Spk", शून्य),

	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			    platक्रमm_घड़ी_control, SND_SOC_DAPM_POST_PMD |
			    SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route audio_map[] = अणु
	अणु "Headphone Jack", शून्य, "HPL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPR" पूर्ण,

	अणु "MIC", शून्य, "Headset Mic" पूर्ण,

	अणु "Headphone Jack", शून्य, "Platform Clock" पूर्ण,
	अणु "Headset Mic", शून्य, "Platform Clock" पूर्ण,

	अणु "Left Spk", शून्य, "Left BE_OUT" पूर्ण,
	अणु "Right Spk", शून्य, "Right BE_OUT" पूर्ण,

	/* digital mics */
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,
पूर्ण;

/* For MAX98360A amp */
अटल स्थिर काष्ठा snd_soc_dapm_widget max98360a_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone Jack", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),

	SND_SOC_DAPM_SPK("Spk", शून्य),

	SND_SOC_DAPM_SUPPLY("Platform Clock", SND_SOC_NOPM, 0, 0,
			    platक्रमm_घड़ी_control, SND_SOC_DAPM_POST_PMD |
			    SND_SOC_DAPM_PRE_PMU),

	SND_SOC_DAPM_MIC("SoC DMIC", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route max98360a_map[] = अणु
	अणु "Headphone Jack", शून्य, "HPL" पूर्ण,
	अणु "Headphone Jack", शून्य, "HPR" पूर्ण,

	अणु "MIC", शून्य, "Headset Mic" पूर्ण,

	अणु "Headphone Jack", शून्य, "Platform Clock" पूर्ण,
	अणु "Headset Mic", शून्य, "Platform Clock" पूर्ण,

	अणु"Spk", शून्य, "Speaker"पूर्ण,

	/* digital mics */
	अणु"DMic", शून्य, "SoC DMIC"पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_jack headset;

अटल पूर्णांक da7219_codec_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	काष्ठा snd_soc_jack *jack;
	पूर्णांक ret;

	/* Configure sysclk क्रम codec */
	ret = snd_soc_dai_set_sysclk(codec_dai, DA7219_CLKSRC_MCLK, 24000000,
				     SND_SOC_CLOCK_IN);
	अगर (ret) अणु
		dev_err(rtd->dev, "can't set codec sysclk configuration\n");
		वापस ret;
	पूर्ण

	/*
	 * Headset buttons map to the google Reference headset.
	 * These can be configured by userspace.
	 */
	ret = snd_soc_card_jack_new(rtd->card, "Headset Jack",
				    SND_JACK_HEADSET | SND_JACK_BTN_0 |
				    SND_JACK_BTN_1 | SND_JACK_BTN_2 |
				    SND_JACK_BTN_3 | SND_JACK_LINEOUT,
				    &headset, शून्य, 0);
	अगर (ret) अणु
		dev_err(rtd->dev, "Headset Jack creation failed: %d\n", ret);
		वापस ret;
	पूर्ण

	jack = &headset;
	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEDOWN);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOICECOMMAND);
	da7219_aad_jack_det(component, jack);

	वापस ret;
पूर्ण

अटल पूर्णांक ssp1_hw_params(काष्ठा snd_pcm_substream *substream,
			      काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *runसमय = asoc_substream_to_rtd(substream);
	पूर्णांक ret, j;

	क्रम (j = 0; j < runसमय->num_codecs; j++) अणु
		काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(runसमय, j);

		अगर (!म_भेद(codec_dai->component->name, MAXIM_DEV0_NAME)) अणु
			/* vmon_slot_no = 0 imon_slot_no = 1 क्रम TX slots */
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0x3, 3, 4, 16);
			अगर (ret < 0) अणु
				dev_err(runसमय->dev, "DEV0 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
		अगर (!म_भेद(codec_dai->component->name, MAXIM_DEV1_NAME)) अणु
			/* vmon_slot_no = 2 imon_slot_no = 3 क्रम TX slots */
			ret = snd_soc_dai_set_tdm_slot(codec_dai, 0xC, 3, 4, 16);
			अगर (ret < 0) अणु
				dev_err(runसमय->dev, "DEV1 TDM slot err:%d\n", ret);
				वापस ret;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा snd_soc_ops ssp1_ops = अणु
	.hw_params = ssp1_hw_params,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf max98373_codec_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF(MAXIM_DEV0_NAME),
		.name_prefix = "Right",
	पूर्ण,
	अणु
		.dlc = COMP_CODEC_CONF(MAXIM_DEV1_NAME),
		.name_prefix = "Left",
	पूर्ण,
पूर्ण;

अटल पूर्णांक hdmi_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा card_निजी *ctx = snd_soc_card_get_drvdata(rtd->card);
	काष्ठा snd_soc_dai *dai = asoc_rtd_to_codec(rtd, 0);
	काष्ठा hdmi_pcm *pcm;

	pcm = devm_kzalloc(rtd->card->dev, माप(*pcm), GFP_KERNEL);
	अगर (!pcm)
		वापस -ENOMEM;

	pcm->device = dai->id;
	pcm->codec_dai = dai;

	list_add_tail(&pcm->head, &ctx->hdmi_pcm_list);

	वापस 0;
पूर्ण

अटल पूर्णांक card_late_probe(काष्ठा snd_soc_card *card)
अणु
	काष्ठा card_निजी *ctx = snd_soc_card_get_drvdata(card);
	काष्ठा snd_soc_acpi_mach *mach = (card->dev)->platक्रमm_data;
	काष्ठा hdmi_pcm *pcm;

	अगर (mach->mach_params.common_hdmi_codec_drv) अणु
		pcm = list_first_entry(&ctx->hdmi_pcm_list, काष्ठा hdmi_pcm,
				       head);
		वापस hda_dsp_hdmi_build_controls(card,
						   pcm->codec_dai->component);
	पूर्ण

	वापस -EINVAL;
पूर्ण

SND_SOC_DAILINK_DEF(ssp0_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP0 Pin")));
SND_SOC_DAILINK_DEF(ssp0_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-DLGS7219:00", DIALOG_CODEC_DAI)));

SND_SOC_DAILINK_DEF(ssp1_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("SSP1 Pin")));
SND_SOC_DAILINK_DEF(ssp1_amps,
	DAILINK_COMP_ARRAY(
	/* Left */	COMP_CODEC(MAXIM_DEV0_NAME, MAX98373_CODEC_DAI),
	/* Right */	COMP_CODEC(MAXIM_DEV1_NAME, MAX98373_CODEC_DAI)));

SND_SOC_DAILINK_DEF(ssp1_m98360a,
	DAILINK_COMP_ARRAY(COMP_CODEC("MX98360A:00", "HiFi")));

SND_SOC_DAILINK_DEF(dmic_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC01 Pin")));
SND_SOC_DAILINK_DEF(dmic_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec", "dmic-hifi")));

SND_SOC_DAILINK_DEF(dmic16k_pin,
	DAILINK_COMP_ARRAY(COMP_CPU("DMIC16k Pin")));

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

SND_SOC_DAILINK_DEF(platक्रमm, /* subject to be overridden during probe */
	DAILINK_COMP_ARRAY(COMP_PLATFORM("0000:00:1f.3")));

अटल काष्ठा snd_soc_dai_link dais[] = अणु
	/* Back End DAI links */
	अणु
		.name = "SSP1-Codec",
		.id = 0,
		.ignore_pmकरोwn_समय = 1,
		.no_pcm = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1, /* IV feedback */
		.ops = &ssp1_ops,
		SND_SOC_DAILINK_REG(ssp1_pin, ssp1_amps, platक्रमm),
	पूर्ण,
	अणु
		.name = "SSP0-Codec",
		.id = 1,
		.no_pcm = 1,
		.init = da7219_codec_init,
		.ignore_pmकरोwn_समय = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		SND_SOC_DAILINK_REG(ssp0_pin, ssp0_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic01",
		.id = 2,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic_pin, dmic_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp1",
		.id = 3,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp1_pin, idisp1_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp2",
		.id = 4,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp2_pin, idisp2_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "iDisp3",
		.id = 5,
		.init = hdmi_init,
		.dpcm_playback = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(idisp3_pin, idisp3_codec, platक्रमm),
	पूर्ण,
	अणु
		.name = "dmic16k",
		.id = 6,
		.ignore_suspend = 1,
		.dpcm_capture = 1,
		.no_pcm = 1,
		SND_SOC_DAILINK_REG(dmic16k_pin, dmic_codec, platक्रमm),
	पूर्ण
पूर्ण;

अटल काष्ठा snd_soc_card card_da7219_m98373 = अणु
	.name = "da7219max",
	.owner = THIS_MODULE,
	.dai_link = dais,
	.num_links = ARRAY_SIZE(dais),
	.controls = controls,
	.num_controls = ARRAY_SIZE(controls),
	.dapm_widमाला_लो = widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(widमाला_लो),
	.dapm_routes = audio_map,
	.num_dapm_routes = ARRAY_SIZE(audio_map),
	.codec_conf = max98373_codec_conf,
	.num_configs = ARRAY_SIZE(max98373_codec_conf),
	.fully_routed = true,
	.late_probe = card_late_probe,
पूर्ण;

अटल काष्ठा snd_soc_card card_da7219_m98360a = अणु
	.name = "da7219max98360a",
	.owner = THIS_MODULE,
	.dai_link = dais,
	.num_links = ARRAY_SIZE(dais),
	.controls = m98360a_controls,
	.num_controls = ARRAY_SIZE(m98360a_controls),
	.dapm_widमाला_लो = max98360a_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(max98360a_widमाला_लो),
	.dapm_routes = max98360a_map,
	.num_dapm_routes = ARRAY_SIZE(max98360a_map),
	.fully_routed = true,
	.late_probe = card_late_probe,
पूर्ण;

अटल पूर्णांक audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	अटल काष्ठा snd_soc_card *card;
	काष्ठा snd_soc_acpi_mach *mach;
	काष्ठा card_निजी *ctx;
	पूर्णांक ret;

	ctx = devm_kzalloc(&pdev->dev, माप(*ctx), GFP_KERNEL);
	अगर (!ctx)
		वापस -ENOMEM;

	/* By शेष dais[0] is configured क्रम max98373 */
	अगर (!म_भेद(pdev->name, "sof_da7219_max98360a")) अणु
		dais[0] = (काष्ठा snd_soc_dai_link) अणु
			.name = "SSP1-Codec",
			.id = 0,
			.no_pcm = 1,
			.dpcm_playback = 1,
			.ignore_pmकरोwn_समय = 1,
			SND_SOC_DAILINK_REG(ssp1_pin, ssp1_m98360a, platक्रमm) पूर्ण;
	पूर्ण

	INIT_LIST_HEAD(&ctx->hdmi_pcm_list);
	card = (काष्ठा snd_soc_card *)pdev->id_entry->driver_data;
	card->dev = &pdev->dev;

	mach = pdev->dev.platक्रमm_data;
	ret = snd_soc_fixup_dai_links_platक्रमm_name(card,
						    mach->mach_params.platक्रमm);
	अगर (ret)
		वापस ret;

	snd_soc_card_set_drvdata(card, ctx);

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id board_ids[] = अणु
	अणु
		.name = "sof_da7219_max98373",
		.driver_data = (kernel_uदीर्घ_t)&card_da7219_m98373,
	पूर्ण,
	अणु
		.name = "sof_da7219_max98360a",
		.driver_data = (kernel_uदीर्घ_t)&card_da7219_m98360a,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_driver audio = अणु
	.probe = audio_probe,
	.driver = अणु
		.name = "sof_da7219_max98_360a_373",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.id_table = board_ids,
पूर्ण;
module_platक्रमm_driver(audio)

/* Module inक्रमmation */
MODULE_DESCRIPTION("ASoC Intel(R) SOF Machine driver");
MODULE_AUTHOR("Yong Zhi <yong.zhi@intel.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:sof_da7219_max98360a");
MODULE_ALIAS("platform:sof_da7219_max98373");
