<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Lowland audio support
//
// Copyright 2011 Wolfson Microelectronics

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <sound/jack.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/module.h>

#समावेश "../codecs/wm5100.h"
#समावेश "../codecs/wm9081.h"

#घोषणा MCLK1_RATE (44100 * 512)
#घोषणा CLKOUT_RATE (44100 * 256)

अटल काष्ठा snd_soc_jack lowland_headset;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin lowland_headset_pins[] = अणु
	अणु
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE | SND_JACK_LINEOUT,
	पूर्ण,
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,
पूर्ण;

अटल पूर्णांक lowland_wm5100_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;
	पूर्णांक ret;

	ret = snd_soc_component_set_sysclk(component, WM5100_CLK_SYSCLK,
				       WM5100_CLKSRC_MCLK1, MCLK1_RATE,
				       SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		pr_err("Failed to set SYSCLK clock source: %d\n", ret);
		वापस ret;
	पूर्ण

	/* Clock OPCLK, used by the other audio components. */
	ret = snd_soc_component_set_sysclk(component, WM5100_CLK_OPCLK, 0,
				       CLKOUT_RATE, 0);
	अगर (ret < 0) अणु
		pr_err("Failed to set OPCLK rate: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_card_jack_new(rtd->card, "Headset", SND_JACK_LINEOUT |
				    SND_JACK_HEADSET | SND_JACK_BTN_0,
				    &lowland_headset, lowland_headset_pins,
				    ARRAY_SIZE(lowland_headset_pins));
	अगर (ret)
		वापस ret;

	wm5100_detect(component, &lowland_headset);

	वापस 0;
पूर्ण

अटल पूर्णांक lowland_wm9081_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(rtd, 0)->component;

	snd_soc_dapm_nc_pin(&rtd->card->dapm, "LINEOUT");

	/* At any समय the WM9081 is active it will have this घड़ी */
	वापस snd_soc_component_set_sysclk(component, WM9081_SYSCLK_MCLK, 0,
					CLKOUT_RATE, 0);
पूर्ण

अटल स्थिर काष्ठा snd_soc_pcm_stream sub_params = अणु
	.क्रमmats = SNDRV_PCM_FMTBIT_S32_LE,
	.rate_min = 44100,
	.rate_max = 44100,
	.channels_min = 2,
	.channels_max = 2,
पूर्ण;

SND_SOC_DAILINK_DEFS(cpu,
	DAILINK_COMP_ARRAY(COMP_CPU("samsung-i2s.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm5100.1-001a", "wm5100-aif1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("samsung-i2s.0")));

SND_SOC_DAILINK_DEFS(baseband,
	DAILINK_COMP_ARRAY(COMP_CPU("wm5100-aif2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm1250-ev1.1-0027", "wm1250-ev1")));

SND_SOC_DAILINK_DEFS(speaker,
	DAILINK_COMP_ARRAY(COMP_CPU("wm5100-aif3")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9081.1-006c", "wm9081-hifi")));

अटल काष्ठा snd_soc_dai_link lowland_dai[] = अणु
	अणु
		.name = "CPU",
		.stream_name = "CPU",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBM_CFM,
		.init = lowland_wm5100_init,
		SND_SOC_DAILINK_REG(cpu),
	पूर्ण,
	अणु
		.name = "Baseband",
		.stream_name = "Baseband",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBM_CFM,
		.ignore_suspend = 1,
		SND_SOC_DAILINK_REG(baseband),
	पूर्ण,
	अणु
		.name = "Sub Speaker",
		.stream_name = "Sub Speaker",
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
				SND_SOC_DAIFMT_CBM_CFM,
		.ignore_suspend = 1,
		.params = &sub_params,
		.init = lowland_wm9081_init,
		SND_SOC_DAILINK_REG(speaker),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_codec_conf lowland_codec_conf[] = अणु
	अणु
		.dlc = COMP_CODEC_CONF("wm9081.1-006c"),
		.name_prefix = "Sub",
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Main Speaker"),
	SOC_DAPM_PIN_SWITCH("Main DMIC"),
	SOC_DAPM_PIN_SWITCH("Main AMIC"),
	SOC_DAPM_PIN_SWITCH("WM1250 Input"),
	SOC_DAPM_PIN_SWITCH("WM1250 Output"),
	SOC_DAPM_PIN_SWITCH("Headphone"),
पूर्ण;

अटल काष्ठा snd_soc_dapm_widget widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),

	SND_SOC_DAPM_SPK("Main Speaker", शून्य),

	SND_SOC_DAPM_MIC("Main AMIC", शून्य),
	SND_SOC_DAPM_MIC("Main DMIC", शून्य),
पूर्ण;

अटल काष्ठा snd_soc_dapm_route audio_paths[] = अणु
	अणु "Sub IN1", शून्य, "HPOUT2L" पूर्ण,
	अणु "Sub IN2", शून्य, "HPOUT2R" पूर्ण,

	अणु "Main Speaker", शून्य, "Sub SPKN" पूर्ण,
	अणु "Main Speaker", शून्य, "Sub SPKP" पूर्ण,
	अणु "Main Speaker", शून्य, "SPKDAT1" पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card lowland = अणु
	.name = "Lowland",
	.owner = THIS_MODULE,
	.dai_link = lowland_dai,
	.num_links = ARRAY_SIZE(lowland_dai),
	.codec_conf = lowland_codec_conf,
	.num_configs = ARRAY_SIZE(lowland_codec_conf),

	.controls = controls,
	.num_controls = ARRAY_SIZE(controls),
	.dapm_widमाला_लो = widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(widमाला_लो),
	.dapm_routes = audio_paths,
	.num_dapm_routes = ARRAY_SIZE(audio_paths),
पूर्ण;

अटल पूर्णांक lowland_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &lowland;
	पूर्णांक ret;

	card->dev = &pdev->dev;

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret && ret != -EPROBE_DEFER)
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);

	वापस ret;
पूर्ण

अटल काष्ठा platक्रमm_driver lowland_driver = अणु
	.driver = अणु
		.name = "lowland",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = lowland_probe,
पूर्ण;

module_platक्रमm_driver(lowland_driver);

MODULE_DESCRIPTION("Lowland audio support");
MODULE_AUTHOR("Mark Brown <broonie@opensource.wolfsonmicro.com>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:lowland");
