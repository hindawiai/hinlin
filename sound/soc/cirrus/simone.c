<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * simone.c -- ASoC audio क्रम Simplemachines Sim.One board
 *
 * Copyright (c) 2010 Mika Westerberg
 *
 * Based on snappercl15 machine driver by Ryan Mallon.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/soc/cirrus/ep93xx.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_CPU("ep93xx-ac97")),
	DAILINK_COMP_ARRAY(COMP_CODEC("ac97-codec", "ac97-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("ep93xx-ac97")));

अटल काष्ठा snd_soc_dai_link simone_dai = अणु
	.name		= "AC97",
	.stream_name	= "AC97 HiFi",
	SND_SOC_DAILINK_REG(hअगरi),
पूर्ण;

अटल काष्ठा snd_soc_card snd_soc_simone = अणु
	.name		= "Sim.One",
	.owner		= THIS_MODULE,
	.dai_link	= &simone_dai,
	.num_links	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device *simone_snd_ac97_device;

अटल पूर्णांक simone_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &snd_soc_simone;
	पूर्णांक ret;

	simone_snd_ac97_device = platक्रमm_device_रेजिस्टर_simple("ac97-codec",
								 -1, शून्य, 0);
	अगर (IS_ERR(simone_snd_ac97_device))
		वापस PTR_ERR(simone_snd_ac97_device);

	card->dev = &pdev->dev;

	ret = snd_soc_रेजिस्टर_card(card);
	अगर (ret) अणु
		dev_err(&pdev->dev, "snd_soc_register_card() failed: %d\n",
			ret);
		platक्रमm_device_unरेजिस्टर(simone_snd_ac97_device);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक simone_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	snd_soc_unरेजिस्टर_card(card);
	platक्रमm_device_unरेजिस्टर(simone_snd_ac97_device);

	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver simone_driver = अणु
	.driver		= अणु
		.name	= "simone-audio",
	पूर्ण,
	.probe		= simone_probe,
	.हटाओ		= simone_हटाओ,
पूर्ण;

module_platक्रमm_driver(simone_driver);

MODULE_DESCRIPTION("ALSA SoC Simplemachines Sim.One");
MODULE_AUTHOR("Mika Westerberg <mika.westerberg@iki.fi>");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:simone-audio");
