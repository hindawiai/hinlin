<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * DB1200/DB1300/DB1550 ASoC audio fabric support code.
 *
 * (c) 2008-2011 Manuel Lauss <manuel.lauss@googlemail.com>
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
#समावेश <यंत्र/mach-au1x00/au1xxx_psc.h>
#समावेश <यंत्र/mach-au1x00/au1xxx_dbdma.h>
#समावेश <यंत्र/mach-db1x00/bcsr.h>

#समावेश "../codecs/wm8731.h"
#समावेश "psc.h"

अटल स्थिर काष्ठा platक्रमm_device_id db1200_pids[] = अणु
	अणु
		.name		= "db1200-ac97",
		.driver_data	= 0,
	पूर्ण, अणु
		.name		= "db1200-i2s",
		.driver_data	= 1,
	पूर्ण, अणु
		.name		= "db1300-ac97",
		.driver_data	= 2,
	पूर्ण, अणु
		.name		= "db1300-i2s",
		.driver_data	= 3,
	पूर्ण, अणु
		.name		= "db1550-ac97",
		.driver_data	= 4,
	पूर्ण, अणु
		.name		= "db1550-i2s",
		.driver_data	= 5,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

/*-------------------------  AC97 PART  ---------------------------*/

SND_SOC_DAILINK_DEFS(db1200_ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("au1xpsc_ac97.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("ac97-codec.1", "ac97-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("au1xpsc-pcm.1")));

अटल काष्ठा snd_soc_dai_link db1200_ac97_dai = अणु
	.name		= "AC97",
	.stream_name	= "AC97 HiFi",
	SND_SOC_DAILINK_REG(db1200_ac97),
पूर्ण;

अटल काष्ठा snd_soc_card db1200_ac97_machine = अणु
	.name		= "DB1200_AC97",
	.owner		= THIS_MODULE,
	.dai_link	= &db1200_ac97_dai,
	.num_links	= 1,
पूर्ण;

SND_SOC_DAILINK_DEFS(db1300_ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("au1xpsc_ac97.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec.1", "wm9712-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("au1xpsc-pcm.1")));

अटल काष्ठा snd_soc_dai_link db1300_ac97_dai = अणु
	.name		= "AC97",
	.stream_name	= "AC97 HiFi",
	SND_SOC_DAILINK_REG(db1300_ac97),
पूर्ण;

अटल काष्ठा snd_soc_card db1300_ac97_machine = अणु
	.name		= "DB1300_AC97",
	.owner		= THIS_MODULE,
	.dai_link	= &db1300_ac97_dai,
	.num_links	= 1,
पूर्ण;

अटल काष्ठा snd_soc_card db1550_ac97_machine = अणु
	.name		= "DB1550_AC97",
	.owner		= THIS_MODULE,
	.dai_link	= &db1200_ac97_dai,
	.num_links	= 1,
पूर्ण;

/*-------------------------  I2S PART  ---------------------------*/

अटल पूर्णांक db1200_i2s_startup(काष्ठा snd_pcm_substream *substream)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);

	/* WM8731 has its own 12MHz crystal */
	snd_soc_dai_set_sysclk(codec_dai, WM8731_SYSCLK_XTAL,
				12000000, SND_SOC_CLOCK_IN);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops db1200_i2s_wm8731_ops = अणु
	.startup	= db1200_i2s_startup,
पूर्ण;

SND_SOC_DAILINK_DEFS(db1200_i2s,
	DAILINK_COMP_ARRAY(COMP_CPU("au1xpsc_i2s.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8731.0-001b", "wm8731-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("au1xpsc-pcm.1")));

अटल काष्ठा snd_soc_dai_link db1200_i2s_dai = अणु
	.name		= "WM8731",
	.stream_name	= "WM8731 PCM",
	.dai_fmt	= SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBM_CFM,
	.ops		= &db1200_i2s_wm8731_ops,
	SND_SOC_DAILINK_REG(db1200_i2s),
पूर्ण;

अटल काष्ठा snd_soc_card db1200_i2s_machine = अणु
	.name		= "DB1200_I2S",
	.owner		= THIS_MODULE,
	.dai_link	= &db1200_i2s_dai,
	.num_links	= 1,
पूर्ण;

SND_SOC_DAILINK_DEFS(db1300_i2s,
	DAILINK_COMP_ARRAY(COMP_CPU("au1xpsc_i2s.2")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8731.0-001b", "wm8731-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("au1xpsc-pcm.2")));

अटल काष्ठा snd_soc_dai_link db1300_i2s_dai = अणु
	.name		= "WM8731",
	.stream_name	= "WM8731 PCM",
	.dai_fmt	= SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBM_CFM,
	.ops		= &db1200_i2s_wm8731_ops,
	SND_SOC_DAILINK_REG(db1300_i2s),
पूर्ण;

अटल काष्ठा snd_soc_card db1300_i2s_machine = अणु
	.name		= "DB1300_I2S",
	.owner		= THIS_MODULE,
	.dai_link	= &db1300_i2s_dai,
	.num_links	= 1,
पूर्ण;

SND_SOC_DAILINK_DEFS(db1550_i2s,
	DAILINK_COMP_ARRAY(COMP_CPU("au1xpsc_i2s.3")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm8731.0-001b", "wm8731-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("au1xpsc-pcm.3")));

अटल काष्ठा snd_soc_dai_link db1550_i2s_dai = अणु
	.name		= "WM8731",
	.stream_name	= "WM8731 PCM",
	.dai_fmt	= SND_SOC_DAIFMT_LEFT_J | SND_SOC_DAIFMT_NB_NF |
			  SND_SOC_DAIFMT_CBM_CFM,
	.ops		= &db1200_i2s_wm8731_ops,
	SND_SOC_DAILINK_REG(db1550_i2s),
पूर्ण;

अटल काष्ठा snd_soc_card db1550_i2s_machine = अणु
	.name		= "DB1550_I2S",
	.owner		= THIS_MODULE,
	.dai_link	= &db1550_i2s_dai,
	.num_links	= 1,
पूर्ण;

/*-------------------------  COMMON PART  ---------------------------*/

अटल काष्ठा snd_soc_card *db1200_cards[] = अणु
	&db1200_ac97_machine,
	&db1200_i2s_machine,
	&db1300_ac97_machine,
	&db1300_i2s_machine,
	&db1550_ac97_machine,
	&db1550_i2s_machine,
पूर्ण;

अटल पूर्णांक db1200_audio_probe(काष्ठा platक्रमm_device *pdev)
अणु
	स्थिर काष्ठा platक्रमm_device_id *pid = platक्रमm_get_device_id(pdev);
	काष्ठा snd_soc_card *card;

	card = db1200_cards[pid->driver_data];
	card->dev = &pdev->dev;
	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल काष्ठा platक्रमm_driver db1200_audio_driver = अणु
	.driver	= अणु
		.name	= "db1200-ac97",
		.pm	= &snd_soc_pm_ops,
	पूर्ण,
	.id_table	= db1200_pids,
	.probe		= db1200_audio_probe,
पूर्ण;

module_platक्रमm_driver(db1200_audio_driver);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("DB1200/DB1300/DB1550 ASoC audio support");
MODULE_AUTHOR("Manuel Lauss");
