<शैली गुरु>
/*
 * Efika driver क्रम the PSC of the Freescale MPC52xx
 * configured as AC97 पूर्णांकerface
 *
 * Copyright 2008 Jon Smirl, Digispeaker
 * Author: Jon Smirl <jonsmirl@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2. This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 */

#समावेश <linux/init.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/device.h>
#समावेश <linux/delay.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_platक्रमm.h>
#समावेश <linux/dma-mapping.h>

#समावेश <sound/core.h>
#समावेश <sound/pcm.h>
#समावेश <sound/pcm_params.h>
#समावेश <sound/initval.h>
#समावेश <sound/soc.h>

#समावेश "mpc5200_dma.h"

#घोषणा DRV_NAME "efika-audio-fabric"

SND_SOC_DAILINK_DEFS(analog,
	DAILINK_COMP_ARRAY(COMP_CPU("mpc5200-psc-ac97.0")),
	DAILINK_COMP_ARRAY(COMP_CODEC("stac9766-codec",
				      "stac9766-hifi-analog")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("mpc5200-pcm-audio")));

SND_SOC_DAILINK_DEFS(iec958,
	DAILINK_COMP_ARRAY(COMP_CPU("mpc5200-psc-ac97.1")),
	DAILINK_COMP_ARRAY(COMP_CODEC("stac9766-codec",
				      "stac9766-hifi-IEC958")),
	DAILINK_COMP_ARRAY(COMP_PLATFORM("mpc5200-pcm-audio")));

अटल काष्ठा snd_soc_dai_link efika_fabric_dai[] = अणु
अणु
	.name = "AC97",
	.stream_name = "AC97 Analog",
	SND_SOC_DAILINK_REG(analog),
पूर्ण,
अणु
	.name = "AC97",
	.stream_name = "AC97 IEC958",
	SND_SOC_DAILINK_REG(iec958),
पूर्ण,
पूर्ण;

अटल काष्ठा snd_soc_card card = अणु
	.name = "Efika",
	.owner = THIS_MODULE,
	.dai_link = efika_fabric_dai,
	.num_links = ARRAY_SIZE(efika_fabric_dai),
पूर्ण;

अटल __init पूर्णांक efika_fabric_init(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक rc;

	अगर (!of_machine_is_compatible("bplan,efika"))
		वापस -ENODEV;

	pdev = platक्रमm_device_alloc("soc-audio", 1);
	अगर (!pdev) अणु
		pr_err("efika_fabric_init: platform_device_alloc() failed\n");
		वापस -ENODEV;
	पूर्ण

	platक्रमm_set_drvdata(pdev, &card);

	rc = platक्रमm_device_add(pdev);
	अगर (rc) अणु
		pr_err("efika_fabric_init: platform_device_add() failed\n");
		platक्रमm_device_put(pdev);
		वापस -ENODEV;
	पूर्ण
	वापस 0;
पूर्ण

module_init(efika_fabric_init);


MODULE_AUTHOR("Jon Smirl <jonsmirl@gmail.com>");
MODULE_DESCRIPTION(DRV_NAME ": mpc5200 Efika fabric driver");
MODULE_LICENSE("GPL");

