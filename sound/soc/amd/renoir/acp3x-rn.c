<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Machine driver क्रम AMD Renoir platक्रमm using DMIC
//
//Copyright 2020 Advanced Micro Devices, Inc.

#समावेश <sound/soc.h>
#समावेश <sound/soc-dapm.h>
#समावेश <linux/module.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <linux/पन.स>

#समावेश "rn_acp3x.h"

#घोषणा DRV_NAME "acp_pdm_mach"

SND_SOC_DAILINK_DEF(acp_pdm,
		    DAILINK_COMP_ARRAY(COMP_CPU("acp_rn_pdm_dma.0")));

SND_SOC_DAILINK_DEF(dmic_codec,
		    DAILINK_COMP_ARRAY(COMP_CODEC("dmic-codec.0",
						  "dmic-hifi")));

SND_SOC_DAILINK_DEF(platक्रमm,
		    DAILINK_COMP_ARRAY(COMP_PLATFORM("acp_rn_pdm_dma.0")));

अटल काष्ठा snd_soc_dai_link acp_dai_pdm[] = अणु
	अणु
		.name = "acp3x-dmic-capture",
		.stream_name = "DMIC capture",
		.capture_only = 1,
		SND_SOC_DAILINK_REG(acp_pdm, dmic_codec, platक्रमm),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card acp_card = अणु
	.name = "acp",
	.owner = THIS_MODULE,
	.dai_link = acp_dai_pdm,
	.num_links = 1,
पूर्ण;

अटल पूर्णांक acp_probe(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret;
	काष्ठा acp_pdm *machine = शून्य;
	काष्ठा snd_soc_card *card;

	card = &acp_card;
	acp_card.dev = &pdev->dev;

	platक्रमm_set_drvdata(pdev, card);
	snd_soc_card_set_drvdata(card, machine);
	ret = devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
	अगर (ret) अणु
		dev_err(&pdev->dev,
			"snd_soc_register_card(%s) failed: %d\n",
			acp_card.name, ret);
		वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver acp_mach_driver = अणु
	.driver = अणु
		.name = "acp_pdm_mach",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
	.probe = acp_probe,
पूर्ण;

module_platक्रमm_driver(acp_mach_driver);

MODULE_AUTHOR("Vijendar.Mukunda@amd.com");
MODULE_LICENSE("GPL v2");
MODULE_ALIAS("platform:" DRV_NAME);
