<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Phytec pcm030 driver क्रम the PSC of the Freescale MPC52xx
// configured as AC97 पूर्णांकerface
//
// Copyright 2008 Jon Smirl, Digispeaker
// Author: Jon Smirl <jonsmirl@gmail.com>

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/device.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>

#समावेश <sound/soc.h>

#समावेश "mpc5200_dma.h"

#घोषणा DRV_NAME "pcm030-audio-fabric"

काष्ठा pcm030_audio_data अणु
	काष्ठा snd_soc_card *card;
	काष्ठा platक्रमm_device *codec_device;
पूर्ण;

SND_SOC_DAILINK_DEFS(analog,
	DAILINK_COMP_ARRAY(COMP_CPU("mpc5200-psc-ac97.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(iec958,
	DAILINK_COMP_ARRAY(COMP_CPU("mpc5200-psc-ac97.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-aux")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link pcm030_fabric_dai[] = अणु
अणु
	.name = "AC97.0",
	.stream_name = "AC97 Analog",
	SND_SOC_DAILINK_REG(analog),
पूर्ण,
अणु
	.name = "AC97.1",
	.stream_name = "AC97 IEC958",
	SND_SOC_DAILINK_REG(iec958),
पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card pcm030_card = अणु
	.name = "pcm030",
	.owner = THIS_MODULE,
	.dai_link = pcm030_fabric_dai,
	.num_links = ARRAY_SIZE(pcm030_fabric_dai),
पूर्ण;

अटल पूर्णांक pcm030_fabric_probe(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा device_node *np = op->dev.of_node;
	काष्ठा device_node *platक्रमm_np;
	काष्ठा snd_soc_card *card = &pcm030_card;
	काष्ठा pcm030_audio_data *pdata;
	काष्ठा snd_soc_dai_link *dai_link;
	पूर्णांक ret;
	पूर्णांक i;

	अगर (!of_machine_is_compatible("phytec,pcm030"))
		वापस -ENODEV;

	pdata = devm_kzalloc(&op->dev, माप(काष्ठा pcm030_audio_data),
			     GFP_KERNEL);
	अगर (!pdata)
		वापस -ENOMEM;

	card->dev = &op->dev;

	pdata->card = card;

	platक्रमm_np = of_parse_phandle(np, "asoc-platform", 0);
	अगर (!platक्रमm_np) अणु
		dev_err(&op->dev, "ac97 not registered\n");
		वापस -ENODEV;
	पूर्ण

	क्रम_each_card_prelinks(card, i, dai_link)
		dai_link->platक्रमms->of_node = platक्रमm_np;

	ret = request_module("snd-soc-wm9712");
	अगर (ret)
		dev_err(&op->dev, "request_module returned: %d\n", ret);

	pdata->codec_device = platक्रमm_device_alloc("wm9712-codec", -1);
	अगर (!pdata->codec_device)
		dev_err(&op->dev, "platform_device_alloc() failed\n");

	ret = platक्रमm_device_add(pdata->codec_device);
	अगर (ret)
		dev_err(&op->dev, "platform_device_add() failed: %d\n", ret);

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret)
		dev_err(&op->dev, "snd_soc_register_card() failed: %d\n", ret);

	platक्रमm_set_drvdata(op, pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक pcm030_fabric_हटाओ(काष्ठा platक्रमm_device *op)
अणु
	काष्ठा pcm030_audio_data *pdata = platक्रमm_get_drvdata(op);
	पूर्णांक ret;

	ret = snd_soc_unरेजिस्टर_card(pdata->card);
	platक्रमm_device_unरेजिस्टर(pdata->codec_device);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा of_device_id pcm030_audio_match[] = अणु
	अणु .compatible = "phytec,pcm030-audio-fabric", पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, pcm030_audio_match);

अटल काष्ठा platक्रमm_driver pcm030_fabric_driver = अणु
	.probe		= pcm030_fabric_probe,
	.हटाओ		= pcm030_fabric_हटाओ,
	.driver		= अणु
		.name	= DRV_NAME,
		.of_match_table    = pcm030_audio_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(pcm030_fabric_driver);


MODULE_AUTHOR("Jon Smirl <jonsmirl@gmail.com>");
MODULE_DESCRIPTION(DRV_NAME ": mpc5200 pcm030 fabric driver");
MODULE_LICENSE("GPL");

