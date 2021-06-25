<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// linux/arch/arm/mach-s3c2440/mach-smdk2440.c
//
// Copyright (c) 2004-2005 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//
// http://www.fluff.org/ben/smdk2440/
//
// Thanks to Dimity Andric and TomTom क्रम the loan of an SMDK2440.

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

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"
#समावेश "gpio-cfg.h"

#समावेश <linux/platक्रमm_data/fb-s3c2410.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश "s3c24xx.h"
#समावेश "common-smdk-s3c24xx.h"

अटल काष्ठा map_desc smdk2440_iodesc[] __initdata = अणु
	/* ISA IO Space map (memory space selected by A24) */

	अणु
		.भव	= (u32)S3C24XX_VA_ISA_WORD,
		.pfn		= __phys_to_pfn(S3C2410_CS2),
		.length		= 0x10000,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (u32)S3C24XX_VA_ISA_WORD + 0x10000,
		.pfn		= __phys_to_pfn(S3C2410_CS2 + (1<<24)),
		.length		= SZ_4M,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (u32)S3C24XX_VA_ISA_BYTE,
		.pfn		= __phys_to_pfn(S3C2410_CS2),
		.length		= 0x10000,
		.type		= MT_DEVICE,
	पूर्ण, अणु
		.भव	= (u32)S3C24XX_VA_ISA_BYTE + 0x10000,
		.pfn		= __phys_to_pfn(S3C2410_CS2 + (1<<24)),
		.length		= SZ_4M,
		.type		= MT_DEVICE,
	पूर्ण
पूर्ण;

#घोषणा UCON S3C2410_UCON_DEFAULT | S3C2410_UCON_UCLK
#घोषणा ULCON S3C2410_LCON_CS8 | S3C2410_LCON_PNONE | S3C2410_LCON_STOPB
#घोषणा UFCON S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE

अटल काष्ठा s3c2410_uartcfg smdk2440_uartcfgs[] __initdata = अणु
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

/* LCD driver info */

अटल काष्ठा s3c2410fb_display smdk2440_lcd_cfg __initdata = अणु

	.lcdcon5	= S3C2410_LCDCON5_FRM565 |
			  S3C2410_LCDCON5_INVVLINE |
			  S3C2410_LCDCON5_INVVFRAME |
			  S3C2410_LCDCON5_PWREN |
			  S3C2410_LCDCON5_HWSWP,

	.type		= S3C2410_LCDCON1_TFT,

	.width		= 240,
	.height		= 320,

	.pixघड़ी	= 166667, /* HCLK 60 MHz, भागisor 10 */
	.xres		= 240,
	.yres		= 320,
	.bpp		= 16,
	.left_margin	= 20,
	.right_margin	= 8,
	.hsync_len	= 4,
	.upper_margin	= 8,
	.lower_margin	= 7,
	.vsync_len	= 4,
पूर्ण;

अटल काष्ठा s3c2410fb_mach_info smdk2440_fb_info __initdata = अणु
	.displays	= &smdk2440_lcd_cfg,
	.num_displays	= 1,
	.शेष_display = 0,

#अगर 0
	/* currently setup by करोwnloader */
	.gpccon		= 0xaa940659,
	.gpccon_mask	= 0xffffffff,
	.gpcup		= 0x0000ffff,
	.gpcup_mask	= 0xffffffff,
	.gpdcon		= 0xaa84aaa0,
	.gpdcon_mask	= 0xffffffff,
	.gpdup		= 0x0000faff,
	.gpdup_mask	= 0xffffffff,

	.gpccon_reg	= S3C2410_GPCCON,
	.gpcup_reg	= S3C2410_GPCUP,
	.gpdcon_reg	= S3C2410_GPDCON,
	.gpdup_reg	= S3C2410_GPDUP,
#पूर्ण_अगर

	.lpcsel		= ((0xCE6) & ~7) | 1<<4,
पूर्ण;

अटल काष्ठा platक्रमm_device *smdk2440_devices[] __initdata = अणु
	&s3c_device_ohci,
	&s3c_device_lcd,
	&s3c_device_wdt,
	&s3c_device_i2c0,
	&s3c_device_iis,
पूर्ण;

अटल व्योम __init smdk2440_map_io(व्योम)
अणु
	s3c24xx_init_io(smdk2440_iodesc, ARRAY_SIZE(smdk2440_iodesc));
	s3c24xx_init_uarts(smdk2440_uartcfgs, ARRAY_SIZE(smdk2440_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init smdk2440_init_समय(व्योम)
अणु
	s3c2440_init_घड़ीs(16934400);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init smdk2440_machine_init(व्योम)
अणु
	s3c24xx_fb_set_platdata(&smdk2440_fb_info);
	s3c_i2c0_set_platdata(शून्य);
	/* Configure the I2S pins (GPE0...GPE4) in correct mode */
	s3c_gpio_cfgall_range(S3C2410_GPE(0), 5, S3C_GPIO_SFN(2),
			      S3C_GPIO_PULL_NONE);
	platक्रमm_add_devices(smdk2440_devices, ARRAY_SIZE(smdk2440_devices));
	smdk_machine_init();
पूर्ण

MACHINE_START(S3C2440, "SMDK2440")
	/* Maपूर्णांकainer: Ben Dooks <ben-linux@fluff.org> */
	.atag_offset	= 0x100,

	.init_irq	= s3c2440_init_irq,
	.map_io		= smdk2440_map_io,
	.init_machine	= smdk2440_machine_init,
	.init_समय	= smdk2440_init_समय,
MACHINE_END
