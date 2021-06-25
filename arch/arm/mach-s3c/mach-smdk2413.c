<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2006 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// Thanks to Dimity Andric (TomTom) and Steven Ryu (Samsung) क्रम the
// loans of SMDK2413 to work with.

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/list.h>
#समावेश <linux/समयr.h>
#समावेश <linux/init.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/hardware/iomd.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

//#समावेश <यंत्र/debug-ll.h>
#समावेश "hardware-s3c24xx.h"
#समावेश "regs-gpio.h"

#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश "s3c24xx.h"
#समावेश "common-smdk-s3c24xx.h"

अटल काष्ठा map_desc smdk2413_iodesc[] __initdata = अणु
पूर्ण;

अटल काष्ठा s3c2410_uartcfg smdk2413_uartcfgs[] __initdata = अणु
	[0] = अणु
		.hwport	     = 0,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण,
	[1] = अणु
		.hwport	     = 1,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x03,
		.ufcon	     = 0x51,
	पूर्ण,
	/* IR port */
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = 0x3c5,
		.ulcon	     = 0x43,
		.ufcon	     = 0x51,
	पूर्ण
पूर्ण;


अटल काष्ठा s3c2410_udc_mach_info smdk2413_udc_cfg __initdata = अणु
	.pullup_pin = S3C2410_GPF(2),
पूर्ण;


अटल काष्ठा platक्रमm_device *smdk2413_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
	&s3c_device_usbgadget,
	&s3c2412_device_dma,
पूर्ण;

अटल व्योम __init smdk2413_fixup(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	अगर (tags != phys_to_virt(S3C2410_SDRAM_PA + 0x100)) अणु
		memblock_add(0x30000000, SZ_64M);
	पूर्ण
पूर्ण

अटल व्योम __init smdk2413_map_io(व्योम)
अणु
	s3c24xx_init_io(smdk2413_iodesc, ARRAY_SIZE(smdk2413_iodesc));
	s3c24xx_init_uarts(smdk2413_uartcfgs, ARRAY_SIZE(smdk2413_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init smdk2413_init_समय(व्योम)
अणु
	s3c2412_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init smdk2413_machine_init(व्योम)
अणु	/* Turn off suspend on both USB ports, and चयन the
	 * selectable USB port to USB device mode. */

	s3c2410_modअगरy_misccr(S3C2410_MISCCR_USBHOST |
			      S3C2410_MISCCR_USBSUSPND0 |
			      S3C2410_MISCCR_USBSUSPND1, 0x0);


 	s3c24xx_udc_set_platdata(&smdk2413_udc_cfg);
	s3c_i2c0_set_platdata(शून्य);
	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);

	platक्रमm_add_devices(smdk2413_devices, ARRAY_SIZE(smdk2413_devices));
	smdk_machine_init();
पूर्ण

MACHINE_START(S3C2413, "S3C2413")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,

	.fixup		= smdk2413_fixup,
	.init_irq	= s3c2412_init_irq,
	.map_io		= smdk2413_map_io,
	.init_machine	= smdk2413_machine_init,
	.init_समय	= s3c24xx_समयr_init,
MACHINE_END

MACHINE_START(SMDK2412, "SMDK2412")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,

	.fixup		= smdk2413_fixup,
	.init_irq	= s3c2412_init_irq,
	.map_io		= smdk2413_map_io,
	.init_machine	= smdk2413_machine_init,
	.init_समय	= s3c24xx_समयr_init,
MACHINE_END

MACHINE_START(SMDK2413, "SMDK2413")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,

	.fixup		= smdk2413_fixup,
	.init_irq	= s3c2412_init_irq,
	.map_io		= smdk2413_map_io,
	.init_machine	= smdk2413_machine_init,
	.init_समय	= smdk2413_init_समय,
MACHINE_END
