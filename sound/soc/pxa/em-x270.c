<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * SoC audio driver क्रम EM-X270, eXeda and CM-X300
 *
 * Copyright 2007, 2009 CompuLab, Ltd.
 *
 * Author: Mike Rapoport <mike@compulab.co.il>
 *
 * Copied from tosa.c:
 * Copyright 2005 Wolfson Microelectronics PLC.
 * Copyright 2005 Openedhand Ltd.
 *
 * Authors: Liam Girdwood <lrg@slimlogic.co.uk>
 *          Riअक्षरd Purdie <riअक्षरd@खोलोedhand.com>
 */

#समावेश <linux/module.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/device.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/soc.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <mach/audपन.स>

SND_SOC_DAILINK_DEFS(ac97,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-hifi")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

SND_SOC_DAILINK_DEFS(ac97_aux,
	DAILINK_COMP_ARRAY(COMP_CPU("pxa2xx-ac97-aux")),
	DAILINK_COMP_ARRAY(COMP_CODEC("wm9712-codec", "wm9712-aux")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("pxa-pcm-audio")));

अटल काष्ठा snd_soc_dai_link em_x270_dai[] = अणु
	अणु
		.name = "AC97",
		.stream_name = "AC97 HiFi",
		SND_SOC_DAILINK_REG(ac97),
	पूर्ण,
	अणु
		.name = "AC97 Aux",
		.stream_name = "AC97 Aux",
		SND_SOC_DAILINK_REG(ac97_aux),
	पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card em_x270 = अणु
	.name = "EM-X270",
	.owner = THIS_MODULE,
	.dai_link = em_x270_dai,
	.num_links = ARRAY_SIZE(em_x270_dai),
पूर्ण;

अटल काष्ठा platक्रमm_device *em_x270_snd_device;

अटल पूर्णांक __init em_x270_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (!(machine_is_em_x270() || machine_is_exeda()
	      || machine_is_cm_x300()))
		वापस -ENODEV;

	em_x270_snd_device = platक्रमm_device_alloc("soc-audio", -1);
	अगर (!em_x270_snd_device)
		वापस -ENOMEM;

	platक्रमm_set_drvdata(em_x270_snd_device, &em_x270);
	ret = platक्रमm_device_add(em_x270_snd_device);

	अगर (ret)
		platक्रमm_device_put(em_x270_snd_device);

	वापस ret;
पूर्ण

अटल व्योम __निकास em_x270_निकास(व्योम)
अणु
	platक्रमm_device_unरेजिस्टर(em_x270_snd_device);
पूर्ण

module_init(em_x270_init);
module_निकास(em_x270_निकास);

/* Module inक्रमmation */
MODULE_AUTHOR("Mike Rapoport");
MODULE_DESCRIPTION("ALSA SoC EM-X270, eXeda and CM-X300");
MODULE_LICENSE("GPL");
