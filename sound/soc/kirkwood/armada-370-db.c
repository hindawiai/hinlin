<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2014 Marvell
 *
 * Thomas Petazzoni <thomas.petazzoni@मुक्त-electrons.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/slab.h>
#समावेश <sound/soc.h>
#समावेश <linux/of.h>
#समावेश <linux/platक्रमm_data/asoc-kirkwood.h>
#समावेश "../codecs/cs42l51.h"

अटल पूर्णांक a370db_hw_params(काष्ठा snd_pcm_substream *substream,
			    काष्ठा snd_pcm_hw_params *params)
अणु
	काष्ठा snd_soc_pcm_runसमय *rtd = asoc_substream_to_rtd(substream);
	काष्ठा snd_soc_dai *codec_dai = asoc_rtd_to_codec(rtd, 0);
	अचिन्हित पूर्णांक freq;

	चयन (params_rate(params)) अणु
	शेष:
	हाल 44100:
		freq = 11289600;
		अवरोध;
	हाल 48000:
		freq = 12288000;
		अवरोध;
	हाल 96000:
		freq = 24576000;
		अवरोध;
	पूर्ण

	वापस snd_soc_dai_set_sysclk(codec_dai, 0, freq, SND_SOC_CLOCK_IN);
पूर्ण

अटल स्थिर काष्ठा snd_soc_ops a370db_ops = अणु
	.hw_params = a370db_hw_params,
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_widget a370db_dapm_widमाला_लो[] = अणु
	SND_SOC_DAPM_HP("Out Jack", शून्य),
	SND_SOC_DAPM_LINE("In Jack", शून्य),
पूर्ण;

अटल स्थिर काष्ठा snd_soc_dapm_route a370db_route[] = अणु
	अणु "Out Jack",	शून्य,	"HPL" पूर्ण,
	अणु "Out Jack",	शून्य,	"HPR" पूर्ण,
	अणु "AIN1L",	शून्य,	"In Jack" पूर्ण,
	अणु "AIN1L",	शून्य,	"In Jack" पूर्ण,
पूर्ण;

SND_SOC_DAILINK_DEFS(analog,
	DAILINK_COMP_ARRAY(COMP_CPU("i2s")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "cs42l51-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(spdअगर_out,
	DAILINK_COMP_ARRAY(COMP_CPU("spdif")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "dit-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

SND_SOC_DAILINK_DEFS(spdअगर_in,
	DAILINK_COMP_ARRAY(COMP_CPU("spdif")),
	DAILINK_COMP_ARRAY(COMP_CODEC(शून्य, "dir-hifi")),
	DAILINK_COMP_ARRAY(COMP_EMPTY()));

अटल काष्ठा snd_soc_dai_link a370db_dai[] = अणु
अणु
	.name = "CS42L51",
	.stream_name = "analog",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS,
	.ops = &a370db_ops,
	SND_SOC_DAILINK_REG(analog),
पूर्ण,
अणु
	.name = "S/PDIF out",
	.stream_name = "spdif-out",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(spdअगर_out),
पूर्ण,
अणु
	.name = "S/PDIF in",
	.stream_name = "spdif-in",
	.dai_fmt = SND_SOC_DAIFMT_I2S | SND_SOC_DAIFMT_CBS_CFS,
	SND_SOC_DAILINK_REG(spdअगर_in),
पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card a370db = अणु
	.name = "a370db",
	.owner = THIS_MODULE,
	.dai_link = a370db_dai,
	.num_links = ARRAY_SIZE(a370db_dai),
	.dapm_widमाला_लो = a370db_dapm_widमाला_लो,
	.num_dapm_widमाला_लो = ARRAY_SIZE(a370db_dapm_widमाला_लो),
	.dapm_routes = a370db_route,
	.num_dapm_routes = ARRAY_SIZE(a370db_route),
पूर्ण;

अटल पूर्णांक a370db_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &a370db;

	card->dev = &pdev->dev;

	a370db_dai[0].cpus->of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-controller", 0);
	a370db_dai[0].platक्रमms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[0].codecs->of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 0);

	a370db_dai[1].cpus->of_node = a370db_dai[0].cpus->of_node;
	a370db_dai[1].platक्रमms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[1].codecs->of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 1);

	a370db_dai[2].cpus->of_node = a370db_dai[0].cpus->of_node;
	a370db_dai[2].platक्रमms->of_node = a370db_dai[0].cpus->of_node;

	a370db_dai[2].codecs->of_node =
		of_parse_phandle(pdev->dev.of_node,
				 "marvell,audio-codec", 2);

	वापस devm_snd_soc_रेजिस्टर_card(card->dev, card);
पूर्ण

अटल स्थिर काष्ठा of_device_id a370db_dt_ids[] __maybe_unused = अणु
	अणु .compatible = "marvell,a370db-audio" पूर्ण,
	अणु पूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, a370db_dt_ids);

अटल काष्ठा platक्रमm_driver a370db_driver = अणु
	.driver		= अणु
		.name	= "a370db-audio",
		.of_match_table = of_match_ptr(a370db_dt_ids),
	पूर्ण,
	.probe		= a370db_probe,
पूर्ण;

module_platक्रमm_driver(a370db_driver);

MODULE_AUTHOR("Thomas Petazzoni <thomas.petazzoni@free-electrons.com>");
MODULE_DESCRIPTION("ALSA SoC a370db audio client");
MODULE_LICENSE("GPL");
MODULE_ALIAS("platform:a370db-audio");
