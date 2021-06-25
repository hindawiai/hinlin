<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// linux/arch/arm/mach-s3c2440/mach-nexcoder.c
//
// Copyright (c) 2004 Nex Vision
//   Guillaume GOURAT <guillaume.gourat@nexvision.tv>
//
// Modअगरications:
//     15-10-2004 GG  Created initial version
//     12-03-2005 BJD Updated क्रम release

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/माला.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>

#समावेश <linux/mtd/map.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

//#समावेश <यंत्र/debug-ll.h>
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश "gpio-cfg.h"
#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश "s3c24xx.h"

अटल काष्ठा map_desc nexcoder_iodesc[] __initdata = अणु
	/* nothing here yet */
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG12 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg nexcoder_uartcfgs[] __initdata = अणु
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

/* NOR Flash on NexVision NexCoder 2440 board */

अटल काष्ठा resource nexcoder_nor_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS0, SZ_8M),
पूर्ण;

अटल काष्ठा map_info nexcoder_nor_map = अणु
	.bankwidth = 2,
पूर्ण;

अटल काष्ठा platक्रमm_device nexcoder_device_nor = अणु
	.name		= "mtd-flash",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(nexcoder_nor_resource),
	.resource	= nexcoder_nor_resource,
	.dev =
	अणु
		.platक्रमm_data = &nexcoder_nor_map,
	पूर्ण
पूर्ण;

/* Standard Nexcoder devices */

अटल काष्ठा platक्रमm_device *nexcoder_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
 	&s3c_device_rtc,
	&s3c_device_camअगर,
	&s3c_device_spi0,
	&s3c_device_spi1,
	&nexcoder_device_nor,
पूर्ण;

अटल व्योम __init nexcoder_sensorboard_init(व्योम)
अणु
	/* Initialize SCCB bus */
	gpio_request_one(S3C2410_GPE(14), GPIOF_OUT_INIT_HIGH, शून्य);
	gpio_मुक्त(S3C2410_GPE(14)); /* IICSCL */
	gpio_request_one(S3C2410_GPE(15), GPIOF_OUT_INIT_HIGH, शून्य);
	gpio_मुक्त(S3C2410_GPE(15)); /* IICSDA */

	/* Power up the sensor board */
	gpio_request_one(S3C2410_GPF(1), GPIOF_OUT_INIT_HIGH, शून्य);
	gpio_मुक्त(S3C2410_GPF(1)); /* CAM_GPIO7 => nLDO_PWRDN */
	gpio_request_one(S3C2410_GPF(2), GPIOF_OUT_INIT_LOW, शून्य);
	gpio_मुक्त(S3C2410_GPF(2)); /* CAM_GPIO6 => CAM_PWRDN */
पूर्ण

अटल व्योम __init nexcoder_map_io(व्योम)
अणु
	s3c24xx_init_io(nexcoder_iodesc, ARRAY_SIZE(nexcoder_iodesc));
	s3c24xx_init_uarts(nexcoder_uartcfgs, ARRAY_SIZE(nexcoder_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);

	nexcoder_sensorboard_init();
पूर्ण

अटल व्योम __init nexcoder_init_समय(व्योम)
अणु
	s3c2440_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init nexcoder_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);

	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);

	platक्रमm_add_devices(nexcoder_devices, ARRAY_SIZE(nexcoder_devices));
पूर्ण;

MACHINE_START(NEXCODER_2440, "NexVision - Nexcoder 2440")
	/* Maपूर्णांकainer: Guillaume GOURAT <guillaume.gourat@nexvision.tv> */
	.atag_offset	= 0x100,
	.map_io		= nexcoder_map_io,
	.init_machine	= nexcoder_init,
	.init_irq	= s3c2440_init_irq,
	.init_समय	= nexcoder_init_समय,
MACHINE_END
