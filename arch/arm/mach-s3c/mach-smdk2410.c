<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
//
// Copyright (C) 2004 by FS Forth-Systeme GmbH
// All rights reserved.
//
// @Author: Jonas Dietsche
//
// @History:
// derived from linux/arch/arm/mach-s3c2410/mach-bast.c, written by
// Ben Dooks <ben@simtec.co.uk>

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश "s3c24xx.h"
#समावेश "common-smdk-s3c24xx.h"

अटल काष्ठा map_desc smdk2410_iodesc[] __initdata = अणु
  /* nothing here yet */
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg smdk2410_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण,
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *smdk2410_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
पूर्ण;

अटल व्योम __init smdk2410_map_io(व्योम)
अणु
	s3c24xx_init_io(smdk2410_iodesc, ARRAY_SIZE(smdk2410_iodesc));
	s3c24xx_init_uarts(smdk2410_uartcfgs, ARRAY_SIZE(smdk2410_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init smdk2410_init_समय(व्योम)
अणु
	s3c2410_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init smdk2410_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);
	platक्रमm_add_devices(smdk2410_devices, ARRAY_SIZE(smdk2410_devices));
	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);
	smdk_machine_init();
पूर्ण

MACHINE_START(SMDK2410, "SMDK2410") /* @TODO: request a new identअगरier and चयन
				    * to SMDK2410 */
	/* Maपूर्णांकainer: Jonas Dietsche */
	.atag_offset	= 0x100,
	.map_io		= smdk2410_map_io,
	.init_irq	= s3c2410_init_irq,
	.init_machine	= smdk2410_init,
	.init_समय	= smdk2410_init_समय,
MACHINE_END
