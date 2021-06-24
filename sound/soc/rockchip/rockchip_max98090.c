<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip machine ASoC driver क्रम boards using a MAX90809 CODEC.
 *
 * Copyright (c) 2014, ROCKCHIP CORPORATION.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/of_device.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "rockchip_i2s.h"
#समावेश "../codecs/ts3a227e.h"

#घोषणा DRV_NAME "rockchip-snd-max98090"

अटल काष्ठा snd_soc_jack headset_jack;

/* Headset jack detection DAPM pins */
अटल काष्ठा snd_soc_jack_pin headset_jack_pins[] = अणु
	अणु
		.pin = "Headphone",
		.mask = SND_JACK_HEADPHONE,
	पूर्ण,
	अणु
		.pin = "Headset Mic",
		.mask = SND_JACK_MICROPHONE,
	पूर्ण,

पूर्ण;

#घोषणा RK_MAX98090_WIDGETS \
	SND_SOC_DAPM_HP("Headphone", शून्य), \
	SND_SOC_DAPM_MIC("Headset Mic", शून्य), \
	SND_SOC_DAPM_MIC("Int Mic", शून्य), \
	SND_SOC_DAPM_SPK("Speaker", शून्य)

#घोषणा RK_HDMI_WIDGETS \
	SND_SOC_DAPM_LINE("HDMI", शून्य)

अटल स्थिर काष्ठा snd_soc_dapm_widget rk_max98090_dapm_widमाला_लो[] = अणु
	RK_MAX98090_WIDGETS,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rk_hdmi_dapm_widमाला_लो[] = अणु
	RK_HDMI_WIDGETS,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget rk_max98090_hdmi_dapm_widमाला_लो[] = अणु
	RK_MAX98090_WIDGETS,
	RK_HDMI_WIDGETS,
पूर्ण;

#घोषणा RK_MAX98090_AUDIO_MAP \
	अणु"IN34", शून्य, "Headset Mic"पूर्ण, \
	अणु"Headset Mic", शून्य, "MICBIAS"पूर्ण, \
	अणु"DMICL", शून्य, "Int Mic"पूर्ण, \
	अणु"Headphone", शून्य, "HPL"पूर्ण, \
	अणु"Headphone", शून्य, "HPR"पूर्ण, \
	अणु"Speaker", शून्य, "SPKL"पूर्ण, \
	अणु"Speaker", शून्य, "SPKR"पूर्ण

#घोषणा RK_HDMI_AUDIO_MAP \
	अणु"HDMI", शून्य, "TX"पूर्ण

अटल स्थिर काष्ठा snd_soc_dapm_route rk_max98090_audio_map[] = अणु
	RK_MAX98090_AUDIO_MAP,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rk_hdmi_audio_map[] = अणु
	RK_HDMI_AUDIO_MAP,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rk_max98090_hdmi_audio_map[] = अणु
	RK_MAX98090_AUDIO_MAP,
	RK_HDMI_AUDIO_MAP,
पूर्ण;

#घोषणा RK_MAX98090_CONTROLS \
	SOC_DAPM_PIN_SWITCH("Headphone"), \
	SOC_DAPM_PIN_SWITCH("Headset Mic"), \
	SOC_DAPM_PIN_SWITCH("Int Mic"), \
	SOC_DAPM_PIN_SWITCH("Speaker")

#घोषणा RK_HDMI_CONTROLS \
	SOC_DAPM_PIN_SWITCH("HDMI")

अटल स्थिर काष्ठा snd_kcontrol_new rk_max98090_controls[] = अणु
	RK_MAX98090_CONTROLS,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rk_hdmi_controls[] = अणु
	RK_HDMI_CONTROLS,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rk_max98090_hdmi_controls[] = अणु
	RK_MAX98090_CONTROLS,
	RK_HDMI_CONTROLS,
पूर्ण;

अटल पूर्णांक rk_jack_event(काष्ठा notअगरier_block *nb, अचिन्हित दीर्घ event,
			 व्योम *data)
अणु
	काष्ठा snd_soc_jack *jack = (काष्ठा snd_soc_jack *)data;
	काष्ठा snd_soc_dapm_context *dapm = &jack->card->dapm;

	अगर (event & SND_JACK_MICROPHONE) अणु
		snd_soc_dapm_क्रमce_enable_pin(dapm, "MICBIAS");
		snd_soc_dapm_क्रमce_enable_pin(dapm, "SHDN");
	पूर्ण अन्यथा अणु
		snd_soc_dapm_disable_pin(dapm, "MICBIAS");
		snd_soc_dapm_disable_pin(dapm, "SHDN");
	पूर्ण

	snd_soc_dapm_sync(dapm);

	वापस 0;
पूर्ण

अटल काष्ठा notअगरier_block rk_jack_nb = अणु
	.notअगरier_call = rk_jack_event,
पूर्ण;

अटल पूर्णांक rk_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	/*
	 * The jack has alपढ़ोy been created in the rk_98090_headset_init()
	 * function.
	 */
	snd_soc_jack_notअगरier_रेजिस्टर(&headset_jack, &rk_jack_nb);

	वापस 0;
पूर्ण

अटल पूर्णांक rk_aअगर1_hw_params(काष्ठा snd_pcm_substream *substream,
			     काष्ठा snd_pcm_hw_params *params)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *cpu_dai = asoc_rtd_to_cpu(rtd, 0);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	पूर्णांक mclk;

	चयन (params_rate(params)) अणु
	हाल 8000:
	हाल 16000:
	हाल 24000:
	हाल 32000:
	हाल 48000:
	हाल 64000:
	हाल 96000:
		mclk = 12288000;
		अवरोध;
	हाल 11025:
	हाल 22050:
	हाल 44100:
	हाल 88200:
		mclk = 11289600;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(cpu_dai, 0, mclk,
				     SND_SOC_CLOCK_OUT);
	अगर (ret) अणु
		dev_err(cpu_dai->dev, "Can't set cpu dai clock %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
				     SND_SOC_CLOCK_IN);

	/* HDMI codec dai करोes not need to set sysclk. */
	अगर (!म_भेद(rtd->dai_link->name, "HDMI"))
		वापस 0;

	अगर (ret) अणु
		dev_err(codec_dai->dev, "Can't set codec dai clock %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rk_aअगर1_startup(काष्ठा snd_pcm_substream *substream)
अणु
	/*
	 * Set period size to 240 because pl330 has issue
	 * dealing with larger period in stress testing.
	 */
	वापस snd_pcm_hw_स्थिरraपूर्णांक_minmax(substream->runसमय,
			SNDRV_PCM_HW_PARAM_PERIOD_SIZE, 240, 240);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops rk_aअगर1_ops = अणु
	.hw_params = rk_aअगर1_hw_params,
	.startup = rk_aअगर1_startup,
पूर्ण;

SND_SOC_DAILINK_DEFS(analog,
		     DAILINK_COMP_ARRAY(COMP_EMPTY()),
		     DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "HiFi")),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(hdmi,
		     DAILINK_COMP_ARRAY(COMP_EMPTY()),
		     DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "i2s-hifi")),
		     DAILINK_COMP_ARRAY(COMP_EMPTY()));

क्रमागत अणु
	DAILINK_MAX98090,
	DAILINK_HDMI,
पूर्ण;

अटल काष्ठा snd_soc_jack rk_hdmi_jack;

अटल पूर्णांक rk_hdmi_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_card *card = runसमय->card;
	काष्ठा snd_soc_component *component = asoc_rtd_to_codec(runसमय, 0)->component;
	पूर्णांक ret;

	/* enable jack detection */
	ret = snd_soc_card_jack_new(card, "HDMI Jack", SND_JACK_LINEOUT,
				    &rk_hdmi_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "Can't new HDMI Jack %d\n", ret);
		वापस ret;
	पूर्ण

	वापस snd_soc_component_set_jack(component, &rk_hdmi_jack, शून्य);
पूर्ण

/* max98090 dai_link */
अटल काष्ठा snd_soc_dai_link rk_max98090_dailinks[] = अणु
	अणु
		.name = "max98090",
		.stream_name = "Analog",
		.init = rk_init,
		.ops = &rk_aअगर1_ops,
		/* set max98090 as slave */
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(analog),
	पूर्ण,
पूर्ण;

/* HDMI codec dai_link */
अटल काष्ठा snd_soc_dai_link rk_hdmi_dailinks[] = अणु
	अणु
		.name = "HDMI",
		.stream_name = "HDMI",
		.init = rk_hdmi_init,
		.ops = &rk_aअगर1_ops,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(hdmi),
	पूर्ण
पूर्ण;

/* max98090 and HDMI codec dai_link */
अटल काष्ठा snd_soc_dai_link rk_max98090_hdmi_dailinks[] = अणु
	[DAILINK_MAX98090] = अणु
		.name = "max98090",
		.stream_name = "Analog",
		.init = rk_init,
		.ops = &rk_aअगर1_ops,
		/* set max98090 as slave */
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(analog),
	पूर्ण,
	[DAILINK_HDMI] = अणु
		.name = "HDMI",
		.stream_name = "HDMI",
		.init = rk_hdmi_init,
		.ops = &rk_aअगर1_ops,
		.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
			SND_SOC_DAIFMT_CBS_CFS,
		SND_SOC_DAILINK_REG(hdmi),
	पूर्ण
पूर्ण;

अटल पूर्णांक rk_98090_headset_init(काष्ठा snd_soc_component *component);

अटल काष्ठा snd_soc_aux_dev rk_98090_headset_dev = अणु
	.dlc = COMP_EMPTY(),
	.init = rk_98090_headset_init,
पूर्ण;

अटल काष्ठा snd_soc_card rockchip_max98090_card = अणु
	.name = "ROCKCHIP-I2S",
	.owner = THIS_MODULE,
	.dai_link = rk_max98090_dailinks,
	.num_links = ARRAY_SIZE(rk_max98090_dailinks),
	.aux_dev = &rk_98090_headset_dev,
	.num_aux_devs = 1,
	.dapm_widमाला_लो = rk_max98090_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rk_max98090_dapm_widमाला_लो),
	.dapm_routes = rk_max98090_audio_map,
	.num_dapm_routes = ARRAY_SIZE(rk_max98090_audio_map),
	.controls = rk_max98090_controls,
	.num_controls = ARRAY_SIZE(rk_max98090_controls),
पूर्ण;

अटल काष्ठा snd_soc_card rockchip_hdmi_card = अणु
	.name = "ROCKCHIP-HDMI",
	.owner = THIS_MODULE,
	.dai_link = rk_hdmi_dailinks,
	.num_links = ARRAY_SIZE(rk_hdmi_dailinks),
	.dapm_widमाला_लो = rk_hdmi_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rk_hdmi_dapm_widमाला_लो),
	.dapm_routes = rk_hdmi_audio_map,
	.num_dapm_routes = ARRAY_SIZE(rk_hdmi_audio_map),
	.controls = rk_hdmi_controls,
	.num_controls = ARRAY_SIZE(rk_hdmi_controls),
पूर्ण;

अटल काष्ठा snd_soc_card rockchip_max98090_hdmi_card = अणु
	.name = "ROCKCHIP-MAX98090-HDMI",
	.owner = THIS_MODULE,
	.dai_link = rk_max98090_hdmi_dailinks,
	.num_links = ARRAY_SIZE(rk_max98090_hdmi_dailinks),
	.aux_dev = &rk_98090_headset_dev,
	.num_aux_devs = 1,
	.dapm_widमाला_लो = rk_max98090_hdmi_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rk_max98090_hdmi_dapm_widमाला_लो),
	.dapm_routes = rk_max98090_hdmi_audio_map,
	.num_dapm_routes = ARRAY_SIZE(rk_max98090_hdmi_audio_map),
	.controls = rk_max98090_hdmi_controls,
	.num_controls = ARRAY_SIZE(rk_max98090_hdmi_controls),
पूर्ण;

अटल पूर्णांक rk_98090_headset_init(काष्ठा snd_soc_component *component)
अणु
	पूर्णांक ret;

	/* Enable Headset and 4 Buttons Jack detection */
	ret = snd_soc_card_jack_new(component->card, "Headset Jack",
				    SND_JACK_HEADSET |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3,
				    &headset_jack,
				    headset_jack_pins,
				    ARRAY_SIZE(headset_jack_pins));
	अगर (ret)
		वापस ret;

	ret = ts3a227e_enable_jack_detect(component, &headset_jack);

	वापस ret;
पूर्ण

अटल पूर्णांक rk_parse_headset_from_of(काष्ठा device *dev, काष्ठा device_node *np)
अणु
	rk_98090_headset_dev.dlc.of_node = of_parse_phandle(
			np, "rockchip,headset-codec", 0);
	अगर (!rk_98090_headset_dev.dlc.of_node) अणु
		dev_err(dev,
			"Property 'rockchip,headset-codec' missing/invalid\n");
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक snd_rk_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_card *card;
	काष्ठा device *dev = &pdev->dev;
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा device_node *np_cpu;
	काष्ठा device_node *np_audio, *np_hdmi;

	/* Parse DTS क्रम I2S controller. */
	np_cpu = of_parse_phandle(np, "rockchip,i2s-controller", 0);

	अगर (!np_cpu) अणु
		dev_err(&pdev->dev,
			"Property 'rockchip,i2s-controller missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	/*
	 * Find the card to use based on the presences of audio codec
	 * and hdmi codec in device property. Set their of_node accordingly.
	 */
	np_audio = of_parse_phandle(np, "rockchip,audio-codec", 0);
	np_hdmi = of_parse_phandle(np, "rockchip,hdmi-codec", 0);
	अगर (np_audio && np_hdmi) अणु
		card = &rockchip_max98090_hdmi_card;
		card->dai_link[DAILINK_MAX98090].codecs->of_node = np_audio;
		card->dai_link[DAILINK_HDMI].codecs->of_node = np_hdmi;
		card->dai_link[DAILINK_MAX98090].cpus->of_node = np_cpu;
		card->dai_link[DAILINK_MAX98090].platक्रमms->of_node = np_cpu;
		card->dai_link[DAILINK_HDMI].cpus->of_node = np_cpu;
		card->dai_link[DAILINK_HDMI].platक्रमms->of_node = np_cpu;
	पूर्ण अन्यथा अगर (np_audio) अणु
		card = &rockchip_max98090_card;
		card->dai_link[0].codecs->of_node = np_audio;
		card->dai_link[0].cpus->of_node = np_cpu;
		card->dai_link[0].platक्रमms->of_node = np_cpu;
	पूर्ण अन्यथा अगर (np_hdmi) अणु
		card = &rockchip_hdmi_card;
		card->dai_link[0].codecs->of_node = np_hdmi;
		card->dai_link[0].cpus->of_node = np_cpu;
		card->dai_link[0].platक्रमms->of_node = np_cpu;
	पूर्ण अन्यथा अणु
		dev_err(dev, "At least one of codecs should be specified\n");
		वापस -EINVAL;
	पूर्ण

	card->dev = dev;

	/* Parse headset detection codec. */
	अगर (np_audio) अणु
		ret = rk_parse_headset_from_of(dev, np);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Parse card name. */
	ret = snd_soc_of_parse_card_name(card, "rockchip,model");
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Soc parse card name failed %d\n", ret);
		वापस ret;
	पूर्ण

	/* रेजिस्टर the soc card */
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Soc register card failed %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_max98090_of_match[] = अणु
	अणु .compatible = "rockchip,rockchip-audio-max98090", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_max98090_of_match);

अटल काष्ठा platक्रमm_driver snd_rk_mc_driver = अणु
	.probe = snd_rk_mc_probe,
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = rockchip_max98090_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(snd_rk_mc_driver);

MODULE_AUTHOR("jianqun <jay.xu@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip max98090 machine ASoC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
