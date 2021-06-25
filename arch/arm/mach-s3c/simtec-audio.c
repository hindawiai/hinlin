<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2009 Simtec Electronics
//	http://armlinux.simtec.co.uk/
//	Ben Dooks <ben@simtec.co.uk>
//
// Audio setup क्रम various Simtec S3C24XX implementations

#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#समावेश <linux/platक्रमm_data/asoc-s3c24xx_simtec.h>
#समावेश "devs.h"

#समावेश "bast.h"
#समावेश "simtec.h"

/* platक्रमm ops क्रम audio */

अटल व्योम simtec_audio_startup_lrroute(व्योम)
अणु
	अचिन्हित पूर्णांक पंचांगp;
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);

	पंचांगp = __raw_पढ़ोb(BAST_VA_CTRL1);
	पंचांगp &= ~BAST_CPLD_CTRL1_LRMASK;
	पंचांगp |= BAST_CPLD_CTRL1_LRCDAC;
	__raw_ग_लिखोb(पंचांगp, BAST_VA_CTRL1);

	local_irq_restore(flags);
पूर्ण

अटल काष्ठा s3c24xx_audio_simtec_pdata simtec_audio_platdata;
अटल अक्षर our_name[32];

अटल काष्ठा platक्रमm_device simtec_audio_dev = अणु
	.name	= our_name,
	.id	= -1,
	.dev	= अणु
		.parent		= &s3c_device_iis.dev,
		.platक्रमm_data	= &simtec_audio_platdata,
	पूर्ण,
पूर्ण;

पूर्णांक __init simtec_audio_add(स्थिर अक्षर *name, bool has_lr_routing,
			    काष्ठा s3c24xx_audio_simtec_pdata *spd)
अणु
	अगर (!name)
		name = "tlv320aic23";

	snम_लिखो(our_name, माप(our_name)-1, "s3c24xx-simtec-%s", name);

	/* copy platक्रमm data so the source can be __initdata */
	अगर (spd)
		simtec_audio_platdata = *spd;

	अगर (has_lr_routing)
		simtec_audio_platdata.startup = simtec_audio_startup_lrroute;

	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);

	platक्रमm_device_रेजिस्टर(&s3c_device_iis);
	platक्रमm_device_रेजिस्टर(&simtec_audio_dev);
	वापस 0;
पूर्ण
