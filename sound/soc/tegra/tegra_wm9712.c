<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * tegra20_wm9712.c - Tegra machine ASoC driver क्रम boards using WM9712 codec.
 *
 * Copyright 2012 Lucas Stach <dev@lynxeye.de>
 *
 * Partly based on code copyright/by:
 * Copyright 2011,2012 Toradex Inc.
 */

#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/of_gpपन.स>

#समावेश <sound/core.h>
#समावेश <sound/jack.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#समावेश "tegra_asoc_utils.h"

#घोषणा DRV_NAME "tegra-snd-wm9712"

काष्ठा tegra_wm9712 अणु
	काष्ठा platक्रमm_device *codec;
	काष्ठा tegra_asoc_utils_data util_data;
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget tegra_wm9712_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Headphone", शून्य),
	SND_SOC_DAPM_LINE("LineIn", शून्य),
	SND_SOC_DAPM_MIC("Mic", शून्य),
पूर्ण;

अटल पूर्णांक tegra_wm9712_init(काष्ठा snd_soc_pcm_runसमय *rtd)
अणु
	वापस snd_soc_dapm_क्रमce_enable_pin(&rtd->card->dapm, "Mic Bias");
पूर्ण

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link tegra_wm9712_dai = अणु
	.name = "AC97 HiFi",
	.stream_name = "AC97 HiFi",
	.init = tegra_wm9712_init,
	SND_SOC_DAILINK_REG(hअगरi),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_tegra_wm9712 = अणु
	.name = "tegra-wm9712",
	.owner = THIS_MODULE,
	.dai_link = &tegra_wm9712_dai,
	.num_links = 1,

	.dapm_widमाला_लो = tegra_wm9712_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(tegra_wm9712_dapm_widमाला_लो),
	.fully_routed = true,
पूर्ण;

अटल पूर्णांक tegra_wm9712_driver_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	काष्ठा snd_soc_card *card = &snd_soc_tegra_wm9712;
	काष्ठा tegra_wm9712 *machine;
	पूर्णांक ret;

	machine = devm_kzalloc(&pdev->dev, माप(काष्ठा tegra_wm9712),
			       GFP_KERNEL);
	अगर (!machine)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	snd_soc_card_set_drvdata(card, machine);

	machine->codec = platक्रमm_device_alloc("wm9712-codec", -1);
	अगर (!machine->codec) अणु
		dev_err(&pdev->dev, "Can't allocate wm9712 platform device\n");
		वापस -ENOMEM;
	पूर्ण

	ret = platक्रमm_device_add(machine->codec);
	अगर (ret)
		जाओ codec_put;

	ret = snd_soc_of_parse_card_name(card, "nvidia,model");
	अगर (ret)
		जाओ codec_unरेजिस्टर;

	ret = snd_soc_of_parse_audio_routing(card, "nvidia,audio-routing");
	अगर (ret)
		जाओ codec_unरेजिस्टर;

	tegra_wm9712_dai.cpus->of_node = of_parse_phandle(np,
				       "nvidia,ac97-controller", 0);
	अगर (!tegra_wm9712_dai.cpus->of_node) अणु
		dev_err(&pdev->dev,
			"Property 'nvidia,ac97-controller' missing or invalid\n");
		ret = -EINVAL;
		जाओ codec_unरेजिस्टर;
	पूर्ण

	tegra_wm9712_dai.platक्रमms->of_node = tegra_wm9712_dai.cpus->of_node;

	ret = tegra_asoc_utils_init(&machine->util_data, &pdev->dev);
	अगर (ret)
		जाओ codec_unरेजिस्टर;

	ret = tegra_asoc_utils_set_ac97_rate(&machine->util_data);
	अगर (ret)
		जाओ codec_unरेजिस्टर;

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err_probe(&pdev->dev, ret,
			      "snd_soc_register_card failed\n");
		जाओ codec_unरेजिस्टर;
	पूर्ण

	वापस 0;

codec_unरेजिस्टर:
	platक्रमm_device_del(machine->codec);
codec_put:
	platक्रमm_device_put(machine->codec);
	वापस ret;
पूर्ण

अटल पूर्णांक tegra_wm9712_driver_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);
	काष्ठा tegra_wm9712 *machine = snd_soc_card_get_drvdata(card);

	snd_soc_unरेजिस्टर_card(card);

	platक्रमm_device_unरेजिस्टर(machine->codec);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id tegra_wm9712_of_match[] = अणु
	अणु .compatible = "nvidia,tegra-audio-wm9712", पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_driver tegra_wm9712_driver = अणु
	.driver = अणु
		.name = DRV_NAME,
		.pm = &snd_soc_pm_ops,
		.of_match_table = tegra_wm9712_of_match,
	पूर्ण,
	.probe = tegra_wm9712_driver_probe,
	.हटाओ = tegra_wm9712_driver_हटाओ,
पूर्ण;
module_platक्रमm_driver(tegra_wm9712_driver);

MODULE_AUTHOR("Lucas Stach");
MODULE_DESCRIPTION("Tegra+WM9712 machine ASoC driver");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
MODULE_DEVICE_TABLE(of, tegra_wm9712_of_match);
