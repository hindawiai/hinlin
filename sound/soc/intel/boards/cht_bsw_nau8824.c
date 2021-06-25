<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  cht-bsw-nau8824.c - ASoc Machine driver क्रम Intel Cherryview-based
 *          platक्रमms Cherrytrail and Braswell, with nau8824 codec.
 *
 *  Copyright (C) 2018 Intel Corp
 *  Copyright (C) 2018 Nuvoton Technology Corp
 *
 *  Author: Wang, Joseph C <joequant@gmail.com>
 *  Co-author: John Hsu <KCHSU0@nuvoton.com>
 *  This file is based on cht_bsw_rt5672.c and cht-bsw-max98090.c
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश <sound/soc-acpi.h>
#समावेश <sound/jack.h>
#समावेश <linux/input.h>
#समावेश "../atom/sst-atom-controls.h"
#समावेश "../../codecs/nau8824.h"

काष्ठा cht_mc_निजी अणु
	काष्ठा snd_soc_jack jack;
पूर्ण;

अटल काष्ठा snd_soc_jack_pin cht_bsw_jack_pins[] = अणु
	अणु
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget cht_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
	SND_SOC_DAPM_SPK("Ext Spk", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route cht_audio_map[] = अणु
	अणु"Ext Spk", शून्य, "SPKOUTL"पूर्ण,
	अणु"Ext Spk", शून्य, "SPKOUTR"पूर्ण,
	अणु"Headphone", शून्य, "HPOL"पूर्ण,
	अणु"Headphone", शून्य, "HPOR"पूर्ण,
	अणु"MIC1", शून्य, "Int Mic"पूर्ण,
	अणु"MIC2", शून्य, "Int Mic"पूर्ण,
	अणु"HSMIC1", शून्य, "Headset Mic"पूर्ण,
	अणु"HSMIC2", शून्य, "Headset Mic"पूर्ण,
	अणु"Playback", शून्य, "ssp2 Tx"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out0"पूर्ण,
	अणु"ssp2 Tx", शून्य, "codec_out1"पूर्ण,
	अणु"codec_in0", शून्य, "ssp2 Rx" पूर्ण,
	अणु"codec_in1", शून्य, "ssp2 Rx" पूर्ण,
	अणु"ssp2 Rx", शून्य, "Capture"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new cht_mc_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphone"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
	SOC_DAPM_PIN_SWITCH("Ext Spk"),
पूर्ण;

अटल पूर्णांक cht_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक ret;

	ret = snd_soc_dai_set_sysclk(codec_dai, NAU8824_CLK_FLL_FS, 0,
		SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "can't set FS clock %d\n", ret);
		वापस ret;
	पूर्ण
	ret = snd_soc_dai_set_pll(codec_dai, 0, 0, params_rate(params),
		params_rate(params) * 256);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "can't set FLL: %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cht_codec_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा cht_mc_निजी *ctx = snd_soc_card_get_drvdata(runसमय->card);
	काष्ठा snd_soc_jack *jack = &ctx->jack;
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(runसमय, 0);
	काष्ठा snd_soc_component *component = codec_dai->component;
	पूर्णांक ret, jack_type;

	/* NAU88L24 supports 4 butons headset detection
	 * KEY_PLAYPAUSE
	 * KEY_VOICECOMMAND
	 * KEY_VOLUMEUP
	 * KEY_VOLUMEDOWN
	 */
	jack_type = SND_JACK_HEADSET | SND_JACK_BTN_0 | SND_JACK_BTN_1 |
		SND_JACK_BTN_2 | SND_JACK_BTN_3;
	ret = snd_soc_card_jack_new(runसमय->card, "Headset", jack_type, jack,
		cht_bsw_jack_pins, ARRAY_SIZE(cht_bsw_jack_pins));
	अगर (ret) अणु
		dev_err(runसमय->dev,
			"Headset Jack creation failed %d\n", ret);
		वापस ret;
	पूर्ण
	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	nau8824_enable_jack_detect(component, jack);

	वापस ret;
पूर्ण

अटल पूर्णांक cht_codec_fixup(काष्ठा snd_soc_pcm_runसमय *rtd,
	काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_पूर्णांकerval *rate = hw_param_पूर्णांकerval(params,
		SNDRV_PCM_HW_PARAM_RATE);
	काष्ठा snd_पूर्णांकerval *channels = hw_param_पूर्णांकerval(params,
		SNDRV_PCM_HW_PARAM_CHANNELS);
	काष्ठा snd_mask *fmt =
		hw_param_mask(params, SNDRV_PCM_HW_PARAM_FORMAT);
	पूर्णांक ret;

	/* The DSP will covert the FE rate to 48k, stereo, 24bits */
	rate->min = rate->max = 48000;
	channels->min = channels->max = 2;

	/* set SSP2 to 24-bit */
	snd_mask_none(fmt);
	params_set_क्रमmat(params, SNDRV_PCM_FORMAT_S24_LE);

	/* TDM 4 slots 24 bit, set Rx & Tx biपंचांगask to 4 active slots */
	ret = snd_soc_dai_set_tdm_slot(asoc_rtd_to_codec(rtd, 0), 0xf, 0x1, 4, 24);
	अगर (ret < 0) अणु
		dev_err(rtd->dev, "can't set codec TDM slot %d\n", ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cht_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	वापस snd_pcm_hw_स्थिरraपूर्णांक_single(substream->runसमय,
		SNDRV_PCM_HW_PARAM_RATE, 48000);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops cht_aअगर1_ops = अणु
	.startup = cht_aअगर1_startup,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_ops cht_be_ssp2_ops = अणु
	.hw_params = cht_aअगर1_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEF(dummy,
	DAILINK_COMP_ARRAY(COMP_DUMMY()));

SND_SOC_DAILINK_DEF(media,
	DAILINK_COMP_ARRAY(COMP_CPU("media-cpu-dai")));

SND_SOC_DAILINK_DEF(deepbuffer,
	DAILINK_COMP_ARRAY(COMP_CPU("deepbuffer-cpu-dai")));

SND_SOC_DAILINK_DEF(ssp2_port,
	DAILINK_COMP_ARRAY(COMP_CPU("ssp2-port")));
SND_SOC_DAILINK_DEF(ssp2_codec,
	DAILINK_COMP_ARRAY(COMP_CODEC("i2c-10508824:00",
				      NAU8824_CODEC_DAI)));

SND_SOC_DAILINK_DEF(platक्रमm,
	DAILINK_COMP_ARRAY(COMP_PLATFORM("sst-mfld-platform")));

अटल काष्ठा snd_soc_dai_link cht_dailink[] = अणु
	/* Front End DAI links */
	[MERR_DPCM_AUDIO] = अणु
		.name = "Audio Port",
		.stream_name = "Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &cht_aअगर1_ops,
		SND_SOC_DAILINK_REG(media, dummy, platक्रमm),
	पूर्ण,
	[MERR_DPCM_DEEP_BUFFER] = अणु
		.name = "Deep-Buffer Audio Port",
		.stream_name = "Deep-Buffer Audio",
		.nonatomic = true,
		.dynamic = 1,
		.dpcm_playback = 1,
		.ops = &cht_aअगर1_ops,
		SND_SOC_DAILINK_REG(deepbuffer, dummy, platक्रमm),
	पूर्ण,
	/* Back End DAI links */
	अणु
		/* SSP2 - Codec */
		.name = "SSP2-Codec",
		.id = 0,
		.no_pcm = 1,
		.dai_fmt = SND_SOC_DAIFMT_DSP_B | SND_SOC_DAIFMT_IB_NF
			| SND_SOC_DAIFMT_CBS_CFS,
		.init = cht_codec_init,
		.be_hw_params_fixup = cht_codec_fixup,
		.dpcm_playback = 1,
		.dpcm_capture = 1,
		.ops = &cht_be_ssp2_ops,
		SND_SOC_DAILINK_REG(ssp2_port, ssp2_codec, platक्रमm),
	पूर्ण,
पूर्ण;

/* use space beक्रमe codec name to simplअगरy card ID, and simplअगरy driver name */
#घोषणा SOF_CARD_NAME "bytcht nau8824" /* card name will be 'sof-bytcht nau8824 */
#घोषणा SOF_DRIVER_NAME "SOF"

#घोषणा CARD_NAME "chtnau8824"
#घोषणा DRIVER_NAME शून्य /* card name will be used क्रम driver name */

/* SoC card */
अटल काष्ठा snd_soc_card snd_soc_card_cht = अणु
	.owner = THIS_MODULE,
	.dai_link = cht_dailink,
	.num_links = ARRAY_SIZE(cht_dailink),
	.dapm_widमाला_लो = cht_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(cht_dapm_widमाला_लो),
	.dapm_routes = cht_audio_map,
	.num_dapm_routes = ARRAY_SIZE(cht_audio_map),
	.controls = cht_mc_controls,
	.num_controls = ARRAY_SIZE(cht_mc_controls),
पूर्ण;

अटल पूर्णांक snd_cht_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा cht_mc_निजी *drv;
	काष्ठा snd_soc_acpi_mach *mach;
	स्थिर अक्षर *platक्रमm_name;
	bool sof_parent;
	पूर्णांक ret_val;

	drv = devm_kzalloc(&pdev->dev, माप(*drv), GFP_KERNEL);
	अगर (!drv)
		वापस -ENOMEM;
	snd_soc_card_set_drvdata(&snd_soc_card_cht, drv);

	/* override plaक्रमm name, अगर required */
	snd_soc_card_cht.dev = &pdev->dev;
	mach = pdev->dev.platक्रमm_data;
	platक्रमm_name = mach->mach_params.platक्रमm;

	ret_val = snd_soc_fixup_dai_links_platक्रमm_name(&snd_soc_card_cht,
							platक्रमm_name);
	अगर (ret_val)
		वापस ret_val;

	sof_parent = snd_soc_acpi_sof_parent(&pdev->dev);

	/* set card and driver name */
	अगर (sof_parent) अणु
		snd_soc_card_cht.name = SOF_CARD_NAME;
		snd_soc_card_cht.driver_name = SOF_DRIVER_NAME;
	पूर्ण अन्यथा अणु
		snd_soc_card_cht.name = CARD_NAME;
		snd_soc_card_cht.driver_name = DRIVER_NAME;
	पूर्ण

	/* set pm ops */
	अगर (sof_parent)
		pdev->dev.driver->pm = &snd_soc_pm_ops;

	/* रेजिस्टर the soc card */
	ret_val = devm_snd_soc_रेजिस्टर_card(&pdev->dev, &snd_soc_card_cht);
	अगर (ret_val) अणु
		dev_err(&pdev->dev,
			"snd_soc_register_card failed %d\n", ret_val);
		वापस ret_val;
	पूर्ण
	platक्रमm_set_drvdata(pdev, &snd_soc_card_cht);

	वापस ret_val;
पूर्ण

अटल काष्ठा platक्रमm_driver snd_cht_mc_driver = अणु
	.driver = अणु
		.name = "cht-bsw-nau8824",
	पूर्ण,
	.probe = snd_cht_mc_probe,
पूर्ण;

module_platक्रमm_driver(snd_cht_mc_driver);

MODULE_DESCRIPTION("ASoC Intel(R) Baytrail CR Machine driver");
MODULE_AUTHOR("Wang, Joseph C <joequant@gmail.com>");
MODULE_AUTHOR("John Hsu <KCHSU0@nuvoton.com>");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:cht-bsw-nau8824");
