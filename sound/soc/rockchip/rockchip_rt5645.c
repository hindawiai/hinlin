<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Rockchip machine ASoC driver क्रम boards using a RT5645/RT5650 CODEC.
 *
 * Copyright (c) 2015, ROCKCHIP CORPORATION.  All rights reserved.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>
#समावेश <linux/delay.h>
#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>
#समावेश "rockchip_i2s.h"
#समावेश "../codecs/rt5645.h"

#घोषणा DRV_NAME "rockchip-snd-rt5645"

अटल काष्ठा snd_soc_jack headset_jack;

अटल स्थिर काष्ठा snd_soc_dapm_widget rk_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphones", शून्य),
	SND_SOC_DAPM_SPK("Speakers", शून्य),
	SND_SOC_DAPM_MIC("Headset Mic", शून्य),
	SND_SOC_DAPM_MIC("Int Mic", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route rk_audio_map[] = अणु
	/* Input Lines */
	अणु"DMIC L2", शून्य, "Int Mic"पूर्ण,
	अणु"DMIC R2", शून्य, "Int Mic"पूर्ण,
	अणु"RECMIXL", शून्य, "Headset Mic"पूर्ण,
	अणु"RECMIXR", शून्य, "Headset Mic"पूर्ण,

	/* Output Lines */
	अणु"Headphones", शून्य, "HPOR"पूर्ण,
	अणु"Headphones", शून्य, "HPOL"पूर्ण,
	अणु"Speakers", शून्य, "SPOL"पूर्ण,
	अणु"Speakers", शून्य, "SPOR"पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा snd_kcontrol_new rk_mc_controls[] = अणु
	SOC_DAPM_PIN_SWITCH("Headphones"),
	SOC_DAPM_PIN_SWITCH("Speakers"),
	SOC_DAPM_PIN_SWITCH("Headset Mic"),
	SOC_DAPM_PIN_SWITCH("Int Mic"),
पूर्ण;

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
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "Can't set codec clock %d\n", ret);
		वापस ret;
	पूर्ण

	ret = snd_soc_dai_set_sysclk(codec_dai, 0, mclk,
				     SND_SOC_CLOCK_IN);
	अगर (ret < 0) अणु
		dev_err(codec_dai->dev, "Can't set codec clock %d\n", ret);
		वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक rk_init(काष्ठा snd_soc_pcm_runसमय *runसमय)
अणु
	काष्ठा snd_soc_card *card = runसमय->card;
	पूर्णांक ret;

	/* Enable Headset and 4 Buttons Jack detection */
	ret = snd_soc_card_jack_new(card, "Headset Jack",
				    SND_JACK_HEADPHONE | SND_JACK_MICROPHONE |
				    SND_JACK_BTN_0 | SND_JACK_BTN_1 |
				    SND_JACK_BTN_2 | SND_JACK_BTN_3,
				    &headset_jack, शून्य, 0);
	अगर (ret) अणु
		dev_err(card->dev, "New Headset Jack failed! (%d)\n", ret);
		वापस ret;
	पूर्ण

	वापस rt5645_set_jack_detect(asoc_rtd_to_codec(runसमय, 0)->component,
				     &headset_jack,
				     &headset_jack,
				     &headset_jack);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops rk_aअगर1_ops = अणु
	.hw_params = rk_aअगर1_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(pcm,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "rt5645-aif1")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link rk_dailink = अणु
	.name = "rt5645",
	.stream_name = "rt5645 PCM",
	.init = rk_init,
	.ops = &rk_aअगर1_ops,
	/* set rt5645 as slave */
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_NB_NF |
		SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(pcm),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_card_rk = अणु
	.name = "I2S-RT5650",
	.owner = THIS_MODULE,
	.dai_link = &rk_dailink,
	.num_links = 1,
	.dapm_widमाला_लो = rk_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(rk_dapm_widमाला_लो),
	.dapm_routes = rk_audio_map,
	.num_dapm_routes = ARRAY_SIZE(rk_audio_map),
	.controls = rk_mc_controls,
	.num_controls = ARRAY_SIZE(rk_mc_controls),
पूर्ण;

अटल पूर्णांक snd_rk_mc_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = 0;
	काष्ठा snd_soc_card *card = &snd_soc_card_rk;
	काष्ठा device_node *np = pdev->dev.of_node;

	/* रेजिस्टर the soc card */
	card->dev = &pdev->dev;

	rk_dailink.codecs->of_node = of_parse_phandle(np,
			"rockchip,audio-codec", 0);
	अगर (!rk_dailink.codecs->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'rockchip,audio-codec' missing or invalid\n");
		वापस -EINVAL;
	पूर्ण

	rk_dailink.cpus->of_node = of_parse_phandle(np,
			"rockchip,i2s-controller", 0);
	अगर (!rk_dailink.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'rockchip,i2s-controller' missing or invalid\n");
		ret = -EINVAL;
		जाओ put_codec_of_node;
	पूर्ण

	rk_dailink.platक्रमms->of_node = rk_dailink.cpus->of_node;

	ret = snd_soc_of_parse_card_name(card, "rockchip,model");
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Soc parse card name failed %d\n", ret);
		जाओ put_cpu_of_node;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"Soc register card failed %d\n", ret);
		जाओ put_cpu_of_node;
	पूर्ण

	वापस ret;

put_cpu_of_node:
	of_node_put(rk_dailink.cpus->of_node);
	rk_dailink.cpus->of_node = शून्य;
put_codec_of_node:
	of_node_put(rk_dailink.codecs->of_node);
	rk_dailink.codecs->of_node = शून्य;

	वापस ret;
पूर्ण

अटल पूर्णांक snd_rk_mc_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	of_node_put(rk_dailink.cpus->of_node);
	rk_dailink.cpus->of_node = शून्य;
	of_node_put(rk_dailink.codecs->of_node);
	rk_dailink.codecs->of_node = शून्य;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id rockchip_rt5645_of_match[] = अणु
	अणु .compatible = "rockchip,rockchip-audio-rt5645", पूर्ण,
	अणुपूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(of, rockchip_rt5645_of_match);

अटल काष्ठा platक्रमm_driver snd_rk_mc_driver = अणु
	.probe = snd_rk_mc_probe,
	.हटाओ = snd_rk_mc_हटाओ,
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = rockchip_rt5645_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(snd_rk_mc_driver);

MODULE_AUTHOR("Xing Zheng <zhengxing@rock-chips.com>");
MODULE_DESCRIPTION("Rockchip rt5645 machine ASoC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
