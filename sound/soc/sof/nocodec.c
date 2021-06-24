<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
//
// This file is provided under a dual BSD/GPLv2 license.  When using or
// redistributing this file, you may करो so under either license.
//
// Copyright(c) 2018 Intel Corporation. All rights reserved.
//
// Author: Liam Girdwood <liam.r.girdwood@linux.पूर्णांकel.com>
//

#समावेश <linux/module.h>
#समावेश <sound/sof.h>
#समावेश "sof-audio.h"
#समावेश "sof-priv.h"

अटल काष्ठा snd_soc_card sof_nocodec_card = अणु
	.name = "nocodec", /* the sof- prefix is added by the core */
	.topology_लघुname = "sof-nocodec",
	.owner = THIS_MODULE
पूर्ण;

अटल पूर्णांक sof_nocodec_bes_setup(काष्ठा device *dev,
				 काष्ठा snd_soc_dai_driver *drv,
				 काष्ठा snd_soc_dai_link *links,
				 पूर्णांक link_num, काष्ठा snd_soc_card *card)
अणु
	काष्ठा snd_soc_dai_link_component *dlc;
	पूर्णांक i;

	अगर (!drv || !links || !card)
		वापस -EINVAL;

	/* set up BE dai_links */
	क्रम (i = 0; i < link_num; i++) अणु
		dlc = devm_kzalloc(dev, 3 * माप(*dlc), GFP_KERNEL);
		अगर (!dlc)
			वापस -ENOMEM;

		links[i].name = devm_kaप्र_लिखो(dev, GFP_KERNEL,
					       "NoCodec-%d", i);
		अगर (!links[i].name)
			वापस -ENOMEM;

		links[i].stream_name = links[i].name;

		links[i].cpus = &dlc[0];
		links[i].codecs = &dlc[1];
		links[i].platक्रमms = &dlc[2];

		links[i].num_cpus = 1;
		links[i].num_codecs = 1;
		links[i].num_platक्रमms = 1;

		links[i].id = i;
		links[i].no_pcm = 1;
		links[i].cpus->dai_name = drv[i].name;
		links[i].platक्रमms->name = dev_name(dev->parent);
		links[i].codecs->dai_name = "snd-soc-dummy-dai";
		links[i].codecs->name = "snd-soc-dummy";
		अगर (drv[i].playback.channels_min)
			links[i].dpcm_playback = 1;
		अगर (drv[i].capture.channels_min)
			links[i].dpcm_capture = 1;

		links[i].be_hw_params_fixup = sof_pcm_dai_link_fixup;
	पूर्ण

	card->dai_link = links;
	card->num_links = link_num;

	वापस 0;
पूर्ण

अटल पूर्णांक sof_nocodec_setup(काष्ठा device *dev,
			     u32 num_dai_drivers,
			     काष्ठा snd_soc_dai_driver *dai_drivers)
अणु
	काष्ठा snd_soc_dai_link *links;

	/* create dummy BE dai_links */
	links = devm_kzalloc(dev, माप(काष्ठा snd_soc_dai_link) * num_dai_drivers, GFP_KERNEL);
	अगर (!links)
		वापस -ENOMEM;

	वापस sof_nocodec_bes_setup(dev, dai_drivers, links, num_dai_drivers, &sof_nocodec_card);
पूर्ण

अटल पूर्णांक sof_nocodec_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा snd_soc_card *card = &sof_nocodec_card;
	काष्ठा snd_soc_acpi_mach *mach;
	पूर्णांक ret;

	card->dev = &pdev->dev;
	card->topology_लघुname_created = true;
	mach = pdev->dev.platक्रमm_data;

	ret = sof_nocodec_setup(card->dev, mach->mach_params.num_dai_drivers,
				mach->mach_params.dai_drivers);
	अगर (ret < 0)
		वापस ret;

	वापस devm_snd_soc_रेजिस्टर_card(&pdev->dev, card);
पूर्ण

अटल पूर्णांक sof_nocodec_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	वापस 0;
पूर्ण

अटल काष्ठा platक्रमm_driver sof_nocodec_audio = अणु
	.probe = sof_nocodec_probe,
	.हटाओ = sof_nocodec_हटाओ,
	.driver = अणु
		.name = "sof-nocodec",
		.pm = &snd_soc_pm_ops,
	पूर्ण,
पूर्ण;
module_platक्रमm_driver(sof_nocodec_audio)

MODULE_DESCRIPTION("ASoC sof nocodec");
MODULE_AUTHOR("Liam Girdwood");
MODULE_LICENSE("Dual BSD/GPL");
MODULE_ALIAS("platform:sof-nocodec");
