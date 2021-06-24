<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2010-2011,2013-2015 The Linux Foundation. All rights reserved.
 *
 * storm.c -- ALSA SoC machine driver क्रम QTi ipq806x-based Storm board
 */

#समावेश <linux/device.h>
#समावेश <linux/module.h>
#समावेश <linux/of.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/soc.h>

#घोषणा STORM_SYSCLK_MULT			4

अटल पूर्णांक storm_ops_hw_params(काष्ठा snd_pcm_substream *substream,
		काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *soc_runसमय = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_card *card = soc_runसमय->card;
	snd_pcm_क्रमmat_t क्रमmat = params_क्रमmat(params);
	अचिन्हित पूर्णांक rate = params_rate(params);
	अचिन्हित पूर्णांक sysclk_freq;
	पूर्णांक bitwidth, ret;

	bitwidth = snd_pcm_क्रमmat_width(क्रमmat);
	अगर (bitwidth < 0) अणु
		dev_err(card->dev, "invalid bit width given: %d\n", bitwidth);
		वापस bitwidth;
	पूर्ण

	/*
	 * as the CPU DAI is the I2S bus master and no प्रणाली घड़ी is needed by
	 * the MAX98357a DAC, simply set the प्रणाली घड़ी to be a स्थिरant
	 * multiple of the bit घड़ी क्रम the घड़ी भागider
	 */
	sysclk_freq = rate * bitwidth * 2 * STORM_SYSCLK_MULT;

	ret = snd_soc_dai_set_sysclk(asoc_rtd_to_cpu(soc_runसमय, 0), 0, sysclk_freq, 0);
	अगर (ret) अणु
		dev_err(card->dev, "error setting sysclk to %u: %d\n",
			sysclk_freq, ret);
		वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops storm_soc_ops = अणु
	.hw_params	= storm_ops_hw_params,
पूर्ण;

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_EMPTY()),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "HiFi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link storm_dai_link = अणु
	.name		= "Primary",
	.stream_name	= "Primary",
	.ops		= &storm_soc_ops,
	SND_SOC_DAILINK_REG(hअगरi),
पूर्ण;

अटल पूर्णांक storm_parse_of(काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link *dai_link = card->dai_link;
	काष्ठा device_node *np = card->dev->of_node;

	dai_link->cpus->of_node = of_parse_phandle(np, "cpu", 0);
	अगर (!dai_link->cpus->of_node) अणु
		dev_err(card->dev, "error getting cpu phandle\n");
		वापस -EINVAL;
	पूर्ण
	dai_link->platक्रमms->of_node = dai_link->cpus->of_node;

	dai_link->codecs->of_node = of_parse_phandle(np, "codec", 0);
	अगर (!dai_link->codecs->of_node) अणु
		dev_err(card->dev, "error getting codec phandle\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक storm_platक्रमm_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card;
	पूर्णांक ret;

	card = devm_kzalloc(&pdev->dev, माप(*card), GFP_KERNEL);
	अगर (!card)
		वापस -ENOMEM;

	card->dev = &pdev->dev;
	card->owner = THIS_MODULE;

	ret = snd_soc_of_parse_card_name(card, "qcom,model");
	अगर (ret) अणु
		dev_err(&pdev->dev, "error parsing card name: %d\n", ret);
		वापस ret;
	पूर्ण

	card->dai_link	= &storm_dai_link;
	card->num_links	= 1;

	ret = storm_parse_of(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "error resolving dai links: %d\n", ret);
		वापस ret;
	पूर्ण

	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret)
		dev_err(&pdev->dev, "error registering soundcard: %d\n", ret);

	वापस ret;

पूर्ण

#अगर_घोषित CONFIG_OF
अटल स्थिर काष्ठा of_device_id storm_device_id[]  = अणु
	अणु .compatible = "google,storm-audio" पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, storm_device_id);
#पूर्ण_अगर

अटल काष्ठा platक्रमm_driver storm_platक्रमm_driver = अणु
	.driver = अणु
		.name = "storm-audio",
		.of_match_table =
			of_match_ptr(storm_device_id),
	पूर्ण,
	.probe = storm_platक्रमm_probe,
पूर्ण;
module_platक्रमm_driver(storm_platक्रमm_driver);

MODULE_DESCRIPTION("QTi IPQ806x-based Storm Machine Driver");
MODULE_LICENSE("GPL v2");
