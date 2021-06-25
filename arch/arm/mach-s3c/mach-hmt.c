<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// mach-hmt.c - Platक्रमm code क्रम Airgoo HMT
//
// Copyright 2009 Peter Korsgaard <jacmet@sunsite.dk>

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_s3c.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पन.स>
#समावेश <linux/i2c.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/leds.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश <video/samsung_fimd.h>
#समावेश "map.h"
#समावेश <mach/irqs.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "gpio-samsung.h"
#समावेश "fb.h"
#समावेश <linux/platक्रमm_data/mtd-nand-s3c2410.h>

#समावेश "devs.h"
#समावेश "cpu.h"

#समावेश "s3c64xx.h"

#घोषणा UCON S3C2410_UCON_DEFAULT
#घोषणा ULCON (S3C2410_LCON_CS8 | S3C2410_LCON_PNONE)
#घोषणा UFCON (S3C2410_UFCON_RXTRIG8 | S3C2410_UFCON_FIFOMODE)

अटल काष्ठा s3c2410_uartcfg hmt_uartcfgs[] __initdata = अणु
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
	पूर्ण,
पूर्ण;

अटल काष्ठा pwm_lookup hmt_pwm_lookup[] = अणु
	PWM_LOOKUP("samsung-pwm", 1, "pwm-backlight.0", शून्य,
		   1000000000 / (100 * 256 * 20), PWM_POLARITY_NORMAL),
पूर्ण;

अटल पूर्णांक hmt_bl_init(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = gpio_request(S3C64XX_GPB(4), "lcd backlight enable");
	अगर (!ret)
		ret = gpio_direction_output(S3C64XX_GPB(4), 0);

	वापस ret;
पूर्ण

अटल पूर्णांक hmt_bl_notअगरy(काष्ठा device *dev, पूर्णांक brightness)
अणु
	/*
	 * translate from CIELUV/CIELAB L*->brightness, E.G. from
	 * perceived luminance to light output. Assumes range 0..25600
	 */
	अगर (brightness < 0x800) अणु
		/* Y = Yn * L / 903.3 */
		brightness = (100*256 * brightness + 231245/2) / 231245;
	पूर्ण अन्यथा अणु
		/* Y = Yn * ((L + 16) / 116 )^3 */
		पूर्णांक t = (brightness*4 + 16*1024 + 58)/116;
		brightness = 25 * ((t * t * t + 0x100000/2) / 0x100000);
	पूर्ण

	gpio_set_value(S3C64XX_GPB(4), brightness);

	वापस brightness;
पूर्ण

अटल व्योम hmt_bl_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(S3C64XX_GPB(4));
पूर्ण

अटल काष्ठा platक्रमm_pwm_backlight_data hmt_backlight_data = अणु
	.max_brightness	= 100 * 256,
	.dft_brightness	= 40 * 256,
	.init		= hmt_bl_init,
	.notअगरy		= hmt_bl_notअगरy,
	.निकास		= hmt_bl_निकास,

पूर्ण;

अटल काष्ठा platक्रमm_device hmt_backlight_device = अणु
	.name		= "pwm-backlight",
	.dev		= अणु
		.parent	= &samsung_device_pwm.dev,
		.platक्रमm_data = &hmt_backlight_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c_fb_pd_win hmt_fb_win0 = अणु
	.max_bpp	= 32,
	.शेष_bpp	= 16,
	.xres		= 800,
	.yres		= 480,
पूर्ण;

अटल काष्ठा fb_videomode hmt_lcd_timing = अणु
	.left_margin	= 8,
	.right_margin	= 13,
	.upper_margin	= 7,
	.lower_margin	= 5,
	.hsync_len	= 3,
	.vsync_len	= 1,
	.xres		= 800,
	.yres		= 480,
पूर्ण;

/* 405566 घड़ीs per frame => 60Hz refresh requires 24333960Hz घड़ी */
अटल काष्ठा s3c_fb_platdata hmt_lcd_pdata __initdata = अणु
	.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,
	.vtiming	= &hmt_lcd_timing,
	.win[0]		= &hmt_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
पूर्ण;

अटल काष्ठा mtd_partition hmt_nand_part[] = अणु
	[0] = अणु
		.name	= "uboot",
		.size	= SZ_512K,
		.offset	= 0,
	पूर्ण,
	[1] = अणु
		.name	= "uboot-env1",
		.size	= SZ_256K,
		.offset	= SZ_512K,
	पूर्ण,
	[2] = अणु
		.name	= "uboot-env2",
		.size	= SZ_256K,
		.offset	= SZ_512K + SZ_256K,
	पूर्ण,
	[3] = अणु
		.name	= "kernel",
		.size	= SZ_2M,
		.offset	= SZ_1M,
	पूर्ण,
	[4] = अणु
		.name	= "rootfs",
		.size	= MTDPART_SIZ_FULL,
		.offset	= SZ_1M + SZ_2M,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_nand_set hmt_nand_sets[] = अणु
	[0] = अणु
		.name		= "nand",
		.nr_chips	= 1,
		.nr_partitions	= ARRAY_SIZE(hmt_nand_part),
		.partitions	= hmt_nand_part,
	पूर्ण,
पूर्ण;

अटल काष्ठा s3c2410_platक्रमm_nand hmt_nand_info = अणु
	.tacls		= 25,
	.twrph0		= 55,
	.twrph1		= 40,
	.nr_sets	= ARRAY_SIZE(hmt_nand_sets),
	.sets		= hmt_nand_sets,
	.engine_type	= न_अंकD_ECC_ENGINE_TYPE_SOFT,
पूर्ण;

अटल काष्ठा gpio_led hmt_leds[] = अणु
	अणु /* left function keys */
		.name			= "left:blue",
		.gpio			= S3C64XX_GPO(12),
		.शेष_trigger	= "default-on",
	पूर्ण,
	अणु /* right function keys - red */
		.name			= "right:red",
		.gpio			= S3C64XX_GPO(13),
	पूर्ण,
	अणु /* right function keys - green */
		.name			= "right:green",
		.gpio			= S3C64XX_GPO(14),
	पूर्ण,
	अणु /* right function keys - blue */
		.name			= "right:blue",
		.gpio			= S3C64XX_GPO(15),
		.शेष_trigger	= "default-on",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data hmt_led_data = अणु
	.num_leds = ARRAY_SIZE(hmt_leds),
	.leds = hmt_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device hmt_leds_device = अणु
	.name			= "leds-gpio",
	.id			= -1,
	.dev.platक्रमm_data	= &hmt_led_data,
पूर्ण;

अटल काष्ठा map_desc hmt_iodesc[] = अणुपूर्ण;

अटल काष्ठा platक्रमm_device *hmt_devices[] __initdata = अणु
	&s3c_device_i2c0,
	&s3c_device_nand,
	&s3c_device_fb,
	&s3c_device_ohci,
	&samsung_device_pwm,
	&hmt_backlight_device,
	&hmt_leds_device,
पूर्ण;

अटल व्योम __init hmt_map_io(व्योम)
अणु
	s3c64xx_init_io(hmt_iodesc, ARRAY_SIZE(hmt_iodesc));
	s3c64xx_set_xtal_freq(12000000);
	s3c24xx_init_uarts(hmt_uartcfgs, ARRAY_SIZE(hmt_uartcfgs));
	s3c64xx_set_समयr_source(S3C64XX_PWM3, S3C64XX_PWM4);
पूर्ण

अटल व्योम __init hmt_machine_init(व्योम)
अणु
	s3c_i2c0_set_platdata(शून्य);
	s3c_fb_set_platdata(&hmt_lcd_pdata);
	s3c_nand_set_platdata(&hmt_nand_info);

	gpio_request(S3C64XX_GPC(7), "usb power");
	gpio_direction_output(S3C64XX_GPC(7), 0);
	gpio_request(S3C64XX_GPM(0), "usb power");
	gpio_direction_output(S3C64XX_GPM(0), 1);
	gpio_request(S3C64XX_GPK(7), "usb power");
	gpio_direction_output(S3C64XX_GPK(7), 1);
	gpio_request(S3C64XX_GPF(13), "usb power");
	gpio_direction_output(S3C64XX_GPF(13), 1);

	pwm_add_table(hmt_pwm_lookup, ARRAY_SIZE(hmt_pwm_lookup));
	platक्रमm_add_devices(hmt_devices, ARRAY_SIZE(hmt_devices));
पूर्ण

MACHINE_START(HMT, "Airgoo-HMT")
	/* Maपूर्णांकainer: Peter Korsgaard <jacmet@sunsite.dk> */
	.atag_offset	= 0x100,
	.nr_irqs	= S3C64XX_NR_IRQS,
	.init_irq	= s3c6410_init_irq,
	.map_io		= hmt_map_io,
	.init_machine	= hmt_machine_init,
	.init_समय	= s3c64xx_समयr_init,
MACHINE_END
