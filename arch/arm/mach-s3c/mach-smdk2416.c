<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (c) 2009 Yauhen Kharuzhy <jekhor@gmail.com>,
//	as part of OpenInkpot project
// Copyright (c) 2009 Promwad Innovation Company
//	Yauhen Kharuzhy <yauhen.kharuzhy@promwad.com>

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
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/fb.h>
#समावेश <linux/delay.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <video/samsung_fimd.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "hardware-s3c24xx.h"
#समावेश "regs-gpio.h"
#समावेश "regs-s3c2443-clock.h"
#समावेश "gpio-samsung.h"

#समावेश <linux/platक्रमm_data/leds-s3c24xx.h>
#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>

#समावेश "gpio-cfg.h"
#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>
#समावेश "sdhci.h"
#समावेश <linux/platक्रमm_data/usb-s3c2410_udc.h>
#समावेश <linux/platक्रमm_data/s3c-hsudc.h>

#समावेश "fb.h"

#समावेश "s3c24xx.h"
#समावेश "common-smdk-s3c24xx.h"

अटल काष्ठा map_desc smdk2416_iodesc[] __initdata = अणु
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

#घोषणा UCON (S3C2410_UCON_DEFAULT	| \
		S3C2440_UCON_PCLK	| \
		S3C2443_UCON_RXERR_IRQEN)

#घोषणा ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE)

#घोषणा UFCON (S3C2410_UFCON_RXTRIG8	| \
		S3C2410_UFCON_FIFOMODE	| \
		S3C2440_UFCON_TXTRIG16)

अटल काष्ठा s3c2410_uartcfg smdk2416_uartcfgs[] __initdata = अणु
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
	/* IR port */
	[2] = अणु
		.hwport	     = 2,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON | 0x50,
		.ufcon	     = UFCON,
	पूर्ण,
	[3] = अणु
		.hwport	     = 3,
		.flags	     = 0,
		.ucon	     = UCON,
		.ulcon	     = ULCON,
		.ufcon	     = UFCON,
	पूर्ण
पूर्ण;

अटल व्योम smdk2416_hsudc_gpio_init(व्योम)
अणु
	s3c_gpio_setpull(S3C2410_GPH(14), S3C_GPIO_PULL_UP);
	s3c_gpio_setpull(S3C2410_GPF(2), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(14), S3C_GPIO_SFN(1));
	s3c2410_modअगरy_misccr(S3C2416_MISCCR_SEL_SUSPND, 0);
पूर्ण

अटल व्योम smdk2416_hsudc_gpio_uninit(व्योम)
अणु
	s3c2410_modअगरy_misccr(S3C2416_MISCCR_SEL_SUSPND, 1);
	s3c_gpio_setpull(S3C2410_GPH(14), S3C_GPIO_PULL_NONE);
	s3c_gpio_cfgpin(S3C2410_GPH(14), S3C_GPIO_SFN(0));
पूर्ण

अटल काष्ठा s3c24xx_hsudc_platdata smdk2416_hsudc_platdata = अणु
	.epnum = 9,
	.gpio_init = smdk2416_hsudc_gpio_init,
	.gpio_uninit = smdk2416_hsudc_gpio_uninit,
पूर्ण;

अटल काष्ठा s3c_fb_pd_win smdk2416_fb_win[] = अणु
	[0] = अणु
		.शेष_bpp	= 16,
		.max_bpp	= 32,
		.xres           = 800,
		.yres           = 480,
	पूर्ण,
पूर्ण;

अटल काष्ठा fb_videomode smdk2416_lcd_timing = अणु
	.pixघड़ी	= 41094,
	.left_margin	= 8,
	.right_margin	= 13,
	.upper_margin	= 7,
	.lower_margin	= 5,
	.hsync_len	= 3,
	.vsync_len	= 1,
	.xres           = 800,
	.yres           = 480,
पूर्ण;

अटल व्योम s3c2416_fb_gpio_setup_24bpp(व्योम)
अणु
	अचिन्हित पूर्णांक gpio;

	क्रम (gpio = S3C2410_GPC(1); gpio <= S3C2410_GPC(4); gpio++) अणु
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	पूर्ण

	क्रम (gpio = S3C2410_GPC(8); gpio <= S3C2410_GPC(15); gpio++) अणु
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	पूर्ण

	क्रम (gpio = S3C2410_GPD(0); gpio <= S3C2410_GPD(15); gpio++) अणु
		s3c_gpio_cfgpin(gpio, S3C_GPIO_SFN(2));
		s3c_gpio_setpull(gpio, S3C_GPIO_PULL_NONE);
	पूर्ण
पूर्ण

अटल काष्ठा s3c_fb_platdata smdk2416_fb_platdata = अणु
	.win[0]		= &smdk2416_fb_win[0],
	.vtiming	= &smdk2416_lcd_timing,
	.setup_gpio	= s3c2416_fb_gpio_setup_24bpp,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
पूर्ण;

अटल काष्ठा s3c_sdhci_platdata smdk2416_hsmmc0_pdata __initdata = अणु
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_GPIO,
	.ext_cd_gpio		= S3C2410_GPF(1),
	.ext_cd_gpio_invert	= 1,
पूर्ण;

अटल काष्ठा s3c_sdhci_platdata smdk2416_hsmmc1_pdata __initdata = अणु
	.max_width		= 4,
	.cd_type		= S3C_SDHCI_CD_NONE,
पूर्ण;

अटल काष्ठा platक्रमm_device *smdk2416_devices[] __initdata = अणु
	&s3c_device_fb,
	&s3c_device_wdt,
	&s3c_device_ohci,
	&s3c_device_i2c0,
	&s3c_device_hsmmc0,
	&s3c_device_hsmmc1,
	&s3c_device_usb_hsudc,
	&s3c2443_device_dma,
पूर्ण;

अटल व्योम __init smdk2416_init_समय(व्योम)
अणु
	s3c2416_init_घड़ीs(12000000);
	s3c24xx_समयr_init();
पूर्ण

अटल व्योम __init smdk2416_map_io(व्योम)
अणु
	s3c24xx_init_io(smdk2416_iodesc, ARRAY_SIZE(smdk2416_iodesc));
	s3c24xx_init_uarts(smdk2416_uartcfgs, ARRAY_SIZE(smdk2416_uartcfgs));
	s3c24xx_set_समयr_source(S3C24XX_PWM3, S3C24XX_PWM4);
पूर्ण

अटल व्योम __init smdk2416_machine_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);
	s3c_fb_set_platdata(&smdk2416_fb_platdata);

	s3c_sdhci0_set_platdata(&smdk2416_hsmmc0_pdata);
	s3c_sdhci1_set_platdata(&smdk2416_hsmmc1_pdata);

	s3c24xx_hsudc_set_platdata(&smdk2416_hsudc_platdata);

	gpio_request(S3C2410_GPB(4), "USBHost Power");
	gpio_direction_output(S3C2410_GPB(4), 1);

	gpio_request(S3C2410_GPB(3), "Display Power");
	gpio_direction_output(S3C2410_GPB(3), 1);

	gpio_request(S3C2410_GPB(1), "Display Reset");
	gpio_direction_output(S3C2410_GPB(1), 1);

	platक्रमm_add_devices(smdk2416_devices, ARRAY_SIZE(smdk2416_devices));
	smdk_machine_init();
पूर्ण

MACHINE_START(SMDK2416, "SMDK2416")
	/* Maपूर्णांकainer: Yauhen Kharuzhy <jekhor@gmail.com> */
	.atag_offset	= 0x100,

	.init_irq	= s3c2416_init_irq,
	.map_io		= smdk2416_map_io,
	.init_machine	= smdk2416_machine_init,
	.init_समय	= smdk2416_init_समय,
MACHINE_END
