<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright (C) 2010 Maurus Cuelenaere

#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/init.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <video/samsung_fimd.h>
#समावेश <mach/irqs.h>
#समावेश "map.h"
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "cpu.h"
#समावेश "devs.h"
#समावेश "fb.h"
#समावेश "gpio-cfg.h"

#समावेश "s3c64xx.h"
#समावेश "mach-smartq.h"

अटल काष्ठा gpio_led smartq7_leds[] = अणु
	अणु
		.name			= "smartq7:red",
		.active_low		= 1,
		.gpio			= S3C64XX_GPN(8),
	पूर्ण,
	अणु
		.name			= "smartq7:green",
		.active_low		= 1,
		.gpio			= S3C64XX_GPN(9),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data smartq7_led_data = अणु
	.num_leds = ARRAY_SIZE(smartq7_leds),
	.leds = smartq7_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device smartq7_leds_device = अणु
	.name			= "leds-gpio",
	.id			= -1,
	.dev.platक्रमm_data	= &smartq7_led_data,
पूर्ण;

/* Labels according to the SmartQ manual */
अटल काष्ठा gpio_keys_button smartq7_buttons[] = अणु
	अणु
		.gpio			= S3C64XX_GPL(14),
		.code			= KEY_POWER,
		.desc			= "Power",
		.active_low		= 1,
		.debounce_पूर्णांकerval	= 5,
		.type                   = EV_KEY,
	पूर्ण,
	अणु
		.gpio			= S3C64XX_GPN(2),
		.code			= KEY_FN,
		.desc			= "Function",
		.active_low		= 1,
		.debounce_पूर्णांकerval	= 5,
		.type                   = EV_KEY,
	पूर्ण,
	अणु
		.gpio			= S3C64XX_GPN(3),
		.code			= KEY_KPMINUS,
		.desc			= "Minus",
		.active_low		= 1,
		.debounce_पूर्णांकerval	= 5,
		.type                   = EV_KEY,
	पूर्ण,
	अणु
		.gpio			= S3C64XX_GPN(4),
		.code			= KEY_KPPLUS,
		.desc			= "Plus",
		.active_low		= 1,
		.debounce_पूर्णांकerval	= 5,
		.type                   = EV_KEY,
	पूर्ण,
	अणु
		.gpio			= S3C64XX_GPN(12),
		.code			= KEY_ENTER,
		.desc			= "Enter",
		.active_low		= 1,
		.debounce_पूर्णांकerval	= 5,
		.type                   = EV_KEY,
	पूर्ण,
	अणु
		.gpio			= S3C64XX_GPN(15),
		.code			= KEY_ESC,
		.desc			= "Cancel",
		.active_low		= 1,
		.debounce_पूर्णांकerval	= 5,
		.type                   = EV_KEY,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data smartq7_buttons_data  = अणु
	.buttons	= smartq7_buttons,
	.nbuttons	= ARRAY_SIZE(smartq7_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device smartq7_buttons_device  = अणु
	.name		= "gpio-keys",
	.id		= 0,
	.num_resources	= 0,
	.dev		= अणु
		.platक्रमm_data	= &smartq7_buttons_data,
	पूर्ण
पूर्ण;

अटल काष्ठा s3c_fb_pd_win smartq7_fb_win0 = अणु
	.max_bpp	= 32,
	.शेष_bpp	= 16,
	.xres		= 800,
	.yres		= 480,
पूर्ण;

अटल काष्ठा fb_videomode smartq7_lcd_timing = अणु
	.left_margin	= 3,
	.right_margin	= 5,
	.upper_margin	= 1,
	.lower_margin	= 20,
	.hsync_len	= 10,
	.vsync_len	= 3,
	.xres		= 800,
	.yres		= 480,
	.refresh	= 80,
पूर्ण;

अटल काष्ठा s3c_fb_platdata smartq7_lcd_pdata __initdata = अणु
	.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,
	.vtiming	= &smartq7_lcd_timing,
	.win[0]		= &smartq7_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC |
			  VIDCON1_INV_VCLK,
पूर्ण;

अटल काष्ठा platक्रमm_device *smartq7_devices[] __initdata = अणु
	&smartq7_leds_device,
	&smartq7_buttons_device,
पूर्ण;

अटल व्योम __init smartq7_machine_init(व्योम)
अणु
	s3c_fb_set_platdata(&smartq7_lcd_pdata);

	smartq_machine_init();

	platक्रमm_add_devices(smartq7_devices, ARRAY_SIZE(smartq7_devices));
पूर्ण

MACHINE_START(SMARTQ7, "SmartQ 7")
	/* Maपूर्णांकainer: Maurus Cuelenaere <mcuelenaere AT gmail DOT com> */
	.atag_offset	= 0x100,
	.nr_irqs	= S3C64XX_NR_IRQS,
	.init_irq	= s3c6410_init_irq,
	.map_io		= smartq_map_io,
	.init_machine	= smartq7_machine_init,
	.init_समय	= s3c64xx_समयr_init,
MACHINE_END
