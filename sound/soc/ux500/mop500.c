<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) ST-Ericsson SA 2012
 *
 * Author: Ola Lilja (ola.o.lilja@stericsson.com)
 *         क्रम ST-Ericsson.
 *
 * License terms:
 */

#समावेश <यंत्र/mach-types.h>

#समावेश <linux/module.h>
#समावेश <linux/पन.स>
#समावेश <linux/spi/spi.h>
#समावेश <linux/of.h>

#समावेश <sound/soc.h>
#समावेश <sound/initval.h>

#समावेश "ux500_pcm.h"
#समावेश "ux500_msp_dai.h"

#समावेश "mop500_ab8500.h"

/* Define the whole MOP500 soundcard, linking platक्रमm to the codec-drivers  */
SND_SOC_DAILINK_DEFS(link1,
	DAILINK_COMP_ARRAY(COMP_CPU("ux500-msp-i2s.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("ab8500-codec.0", "ab8500-codec-dai.0")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("ux500-msp-i2s.1")));

SND_SOC_DAILINK_DEFS(link2,
	DAILINK_COMP_ARRAY(COMP_CPU("ux500-msp-i2s.3")),
	DAILINK_COMP_ARRAY(COMP_CODEC("ab8500-codec.0", "ab8500-codec-dai.1")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("ux500-msp-i2s.3")));

अटल काष्ठा snd_soc_dai_link mop500_dai_links[] = अणु
	अणु
		.name = "ab8500_0",
		.stream_name = "ab8500_0",
		.init = mop500_ab8500_machine_init,
		.ops = mop500_ab8500_ops,
		SND_SOC_DAILINK_REG(link1),
	पूर्ण,
	अणु
		.name = "ab8500_1",
		.stream_name = "ab8500_1",
		.init = शून्य,
		.ops = mop500_ab8500_ops,
		SND_SOC_DAILINK_REG(link2),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card mop500_card = अणु
	.name = "MOP500-card",
	.owner = THIS_MODULE,
	.probe = शून्य,
	.dai_link = mop500_dai_links,
	.num_links = ARRAY_SIZE(mop500_dai_links),
पूर्ण;

अटल व्योम mop500_of_node_put(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 2; i++)
		of_node_put(mop500_dai_links[i].cpus->of_node);

	/* Both links use the same codec, which is refcounted only once */
	of_node_put(mop500_dai_links[0].codecs->of_node);
पूर्ण

अटल पूर्णांक mop500_of_probe(काष्ठा platक्रमm_device *pdev,
			   काष्ठा device_node *np)
अणु
	काष्ठा device_node *codec_np, *msp_np[2];
	पूर्णांक i;

	msp_np[0] = of_parse_phandle(np, "stericsson,cpu-dai", 0);
	msp_np[1] = of_parse_phandle(np, "stericsson,cpu-dai", 1);
	codec_np  = of_parse_phandle(np, "stericsson,audio-codec", 0);

	अगर (!(msp_np[0] && msp_np[1] && codec_np)) अणु
		dev_err(&pdev->dev, "Phandle missing or invalid\n");
		क्रम (i = 0; i < 2; i++)
			of_node_put(msp_np[i]);
		of_node_put(codec_np);
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < 2; i++) अणु
		mop500_dai_links[i].cpus->of_node = msp_np[i];
		mop500_dai_links[i].cpus->dai_name = शून्य;
		mop500_dai_links[i].platक्रमms->of_node = msp_np[i];
		mop500_dai_links[i].platक्रमms->name = शून्य;
		mop500_dai_links[i].codecs->of_node = codec_np;
		mop500_dai_links[i].codecs->name = शून्य;
	पूर्ण

	snd_soc_of_parse_card_name(&mop500_card, "stericsson,card-name");

	वापस 0;
पूर्ण

अटल पूर्णांक mop500_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *np = pdev->dev.of_node;
	पूर्णांक ret;

	dev_dbg(&pdev->dev, "%s: Enter.\n", __func__);

	mop500_card.dev = &pdev->dev;

	अगर (np) अणु
		ret = mop500_of_probe(pdev, np);
		अगर (ret)
			वापस ret;
	पूर्ण

	dev_dbg(&pdev->dev, "%s: Card %s: Set platform drvdata.\n",
		__func__, mop500_card.name);

	snd_soc_card_set_drvdata(&mop500_card, शून्य);

	dev_dbg(&pdev->dev, "%s: Card %s: num_links = %d\n",
		__func__, mop500_card.name, mop500_card.num_links);
	dev_dbg(&pdev->dev, "%s: Card %s: DAI-link 0: name = %s\n",
		__func__, mop500_card.name, mop500_card.dai_link[0].name);
	dev_dbg(&pdev->dev, "%s: Card %s: DAI-link 0: stream_name = %s\n",
		__func__, mop500_card.name,
		mop500_card.dai_link[0].stream_name);

	ret = snd_soc_रेजिस्टर_card(&mop500_card);
	अगर (ret)
		dev_err(&pdev->dev,
			"Error: snd_soc_register_card failed (%d)!\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक mop500_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = platक्रमm_get_drvdata(pdev);

	pr_debug("%s: Enter.\n", __func__);

	snd_soc_unरेजिस्टर_card(card);
	mop500_ab8500_हटाओ(card);
	mop500_of_node_put();

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id snd_soc_mop500_match[] = अणु
	अणु .compatible = "stericsson,snd-soc-mop500", पूर्ण,
	अणुपूर्ण,
पूर्ण;
MODULE_DEVICE_TABLE(of, snd_soc_mop500_match);

अटल काष्ठा platक्रमm_driver snd_soc_mop500_driver = अणु
	.driver = अणु
		.name = "snd-soc-mop500",
		.of_match_table = snd_soc_mop500_match,
	पूर्ण,
	.probe = mop500_probe,
	.हटाओ = mop500_हटाओ,
पूर्ण;

module_platक्रमm_driver(snd_soc_mop500_driver);

MODULE_LICENSE("GPL v2");
MODULE_DESCRIPTION("ASoC MOP500 board driver");
MODULE_AUTHOR("Ola Lilja");
