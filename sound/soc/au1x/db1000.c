<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DB1000/DB1500/DB1100 ASoC audio fabric support code.
 *
 * (c) 2011 Manuel Lauss <manuel.lauss@googlemail.com>
 *
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/समयr.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>
#समावेश <यंत्र/mach-au1x00/au1000.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>

#समावेश "psc.h"

SND_SOC_DAILINK_DEFS(hअगरi,
	DAILINK_COMP_ARRAY(COMP_CPU("alchemy-ac97c")),
	DAILINK_COMP_ARRAY(COMP_CODEC("ac97-codec", "ac97-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("alchemy-pcm-dma.0")));

अटल काष्ठा snd_soc_dai_link db1000_ac97_dai = अणु
	.name		= "AC97",
	.stream_name	= "AC97 HiFi",
	SND_SOC_DAILINK_REG(hअगरi),
पूर्ण;

अटल काष्ठा snd_soc_card db1000_ac97 = अणु
	.name		= "DB1000_AC97",
	.owner		= THIS_MODULE,
	.dai_link	= &db1000_ac97_dai,
	.num_links	= 1,
पूर्ण;

अटल पूर्णांक db1000_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &db1000_ac97;
	card->dev = &pdev->dev;
	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल काष्ठा platक्रमm_driver db1000_audio_driver = अणु
	.driver	= अणु
		.name	= "db1000-audio",
		.pm	= &snd_soc_pm_ops,
	पूर्ण,
	.probe		= db1000_audio_probe,
पूर्ण;

module_platक्रमm_driver(db1000_audio_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DB1000/DB1500/DB1100 ASoC audio");
MODULE_AUTHOR("Manuel Lauss");
