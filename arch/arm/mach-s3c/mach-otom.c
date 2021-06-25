<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2004 Nex Vision
//   Guillaume GOURAT <guillaume.gourat@nexvision.fr>

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

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#समावेश "cpu.h"
#समावेश "devs.h"

#समावेश "s3c24xx.h"
#समावेश "otom.h"

अटल काष्ठा map_desc otom11_iodesc[] __initdata = अणु
  /* Device area */
	अणु (u32)OTOM_VA_CS8900A_BASE, OTOM_PA_CS8900A_BASE, SZ_16M, MT_DEVICE पूर्ण,
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG12 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg otom11_uartcfgs[] __initdata = अणु
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
	/* port 2 is not actually used */
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण
पूर्ण;

/* NOR Flash on NexVision OTOM board */

अटल काष्ठा resource otom_nor_resource[] = अणु
	[0] = DEFINE_RES_MEM(S3C2410_CS0, SZ_4M),
पूर्ण;

अटल काष्ठा platक्रमm_device otom_device_nor = अणु
	.name		= "mtd-flash",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(otom_nor_resource),
	.resource	= otom_nor_resource,
पूर्ण;

/* Standard OTOM devices */

अटल काष्ठा platक्रमm_device *otom11_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
 	&s3c_device_rtc,
	&otom_device_nor,
पूर्ण;

अटल व्योम __init otom11_map_io(व्योम)
अणु
	s3c24xx_init_io(otom11_iodesc, ARRAY_SIZE(otom11_iodesc));
	s3c24xx_init_uarts(otom11_uartcfgs, ARRAY_SIZE(otom11_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init otom11_init_समय(व्योम)
अणु
	s3c2410_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init otom11_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);

	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);
	platक्रमm_add_devices(otom11_devices, ARRAY_SIZE(otom11_devices));
पूर्ण

MACHINE_START(OTOM, "Nex Vision - Otom 1.1")
	/* Maपूर्णांकainer: Guillaume GOURAT <guillaume.gourat@nexvision.tv> */
	.atag_offset	= 0x100,
	.map_io		= otom11_map_io,
	.init_machine	= otom11_init,
	.init_irq	= s3c2410_init_irq,
	.init_समय	= otom11_init_समय,
MACHINE_END
