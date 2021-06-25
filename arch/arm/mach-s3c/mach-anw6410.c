<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
//
// Copyright 2008 Openmoko, Inc.
// Copyright 2008 Simtec Electronics
//	Ben Dooks <ben@simtec.co.uk>
//	http://armlinux.simtec.co.uk/
// Copyright 2009 Kwangwoo Lee
//	Kwangwoo Lee <kwangwoo.lee@gmail.com>

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
#समावेश <linux/i2c.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/dm9000.h>

#समावेश <video/platक्रमm_lcd.h>
#समावेश <video/samsung_fimd.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "map.h"

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <linux/platक्रमm_data/i2c-s3c2410.h>
#समावेश "fb.h"

#समावेश "devs.h"
#समावेश "cpu.h"
#समावेश <mach/irqs.h>
#समावेश "regs-gpio.h"
#समावेश "gpio-samsung.h"

#समावेश "s3c64xx.h"
#समावेश "regs-modem-s3c64xx.h"

/* DM9000 */
#घोषणा ANW6410_PA_DM9000	(0x18000000)

/* A hardware buffer to control बाह्यal devices is mapped at 0x30000000.
 * It can not be पढ़ो. So current status must be kept in anw6410_extdev_status.
 */
#घोषणा ANW6410_VA_EXTDEV	S3C_ADDR(0x02000000)
#घोषणा ANW6410_PA_EXTDEV	(0x30000000)

#घोषणा ANW6410_EN_DM9000	(1<<11)
#घोषणा ANW6410_EN_LCD		(1<<14)

अटल __u32 anw6410_extdev_status;

अटल काष्ठा s3c2410_uartcfg anw6410_uartcfgs[] __initdata = अणु
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
पूर्ण;

/* framebuffer and LCD setup. */
अटल व्योम __init anw6410_lcd_mode_set(व्योम)
अणु
	u32 पंचांगp;

	/* set the LCD type */
	पंचांगp = __raw_पढ़ोl(S3C64XX_SPCON);
	पंचांगp &= ~S3C64XX_SPCON_LCD_SEL_MASK;
	पंचांगp |= S3C64XX_SPCON_LCD_SEL_RGB;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_SPCON);

	/* हटाओ the LCD bypass */
	पंचांगp = __raw_पढ़ोl(S3C64XX_MODEM_MIFPCON);
	पंचांगp &= ~MIFPCON_LCD_BYPASS;
	__raw_ग_लिखोl(पंचांगp, S3C64XX_MODEM_MIFPCON);
पूर्ण

/* GPF1 = LCD panel घातer
 * GPF4 = LCD backlight control
 */
अटल व्योम anw6410_lcd_घातer_set(काष्ठा plat_lcd_data *pd,
				   अचिन्हित पूर्णांक घातer)
अणु
	अगर (घातer) अणु
		anw6410_extdev_status |= (ANW6410_EN_LCD << 16);
		__raw_ग_लिखोl(anw6410_extdev_status, ANW6410_VA_EXTDEV);

		gpio_direction_output(S3C64XX_GPF(1), 1);
		gpio_direction_output(S3C64XX_GPF(4), 1);
	पूर्ण अन्यथा अणु
		anw6410_extdev_status &= ~(ANW6410_EN_LCD << 16);
		__raw_ग_लिखोl(anw6410_extdev_status, ANW6410_VA_EXTDEV);

		gpio_direction_output(S3C64XX_GPF(1), 0);
		gpio_direction_output(S3C64XX_GPF(4), 0);
	पूर्ण
पूर्ण

अटल काष्ठा plat_lcd_data anw6410_lcd_घातer_data = अणु
	.set_घातer	= anw6410_lcd_घातer_set,
पूर्ण;

अटल काष्ठा platक्रमm_device anw6410_lcd_घातerdev = अणु
	.name			= "platform-lcd",
	.dev.parent		= &s3c_device_fb.dev,
	.dev.platक्रमm_data	= &anw6410_lcd_घातer_data,
पूर्ण;

अटल काष्ठा s3c_fb_pd_win anw6410_fb_win0 = अणु
	.max_bpp	= 32,
	.शेष_bpp	= 16,
	.xres		= 800,
	.yres		= 480,
पूर्ण;

अटल काष्ठा fb_videomode anw6410_lcd_timing = अणु
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
अटल काष्ठा s3c_fb_platdata anw6410_lcd_pdata __initdata = अणु
	.setup_gpio	= s3c64xx_fb_gpio_setup_24bpp,
	.vtiming	= &anw6410_lcd_timing,
	.win[0]		= &anw6410_fb_win0,
	.vidcon0	= VIDCON0_VIDOUT_RGB | VIDCON0_PNRMODE_RGB,
	.vidcon1	= VIDCON1_INV_HSYNC | VIDCON1_INV_VSYNC,
पूर्ण;

/* DM9000AEP 10/100 ethernet controller */
अटल व्योम __init anw6410_dm9000_enable(व्योम)
अणु
	anw6410_extdev_status |= (ANW6410_EN_DM9000 << 16);
	__raw_ग_लिखोl(anw6410_extdev_status, ANW6410_VA_EXTDEV);
पूर्ण

अटल काष्ठा resource anw6410_dm9000_resource[] = अणु
	[0] = DEFINE_RES_MEM(ANW6410_PA_DM9000, 4),
	[1] = DEFINE_RES_MEM(ANW6410_PA_DM9000 + 4, 501),
	[2] = DEFINE_RES_NAMED(IRQ_EINT(15), 1, शून्य, IORESOURCE_IRQ \
					| IRQF_TRIGGER_HIGH),
पूर्ण;

अटल काष्ठा dm9000_plat_data anw6410_dm9000_pdata = अणु
	.flags	  = (DM9000_PLATF_16BITONLY | DM9000_PLATF_NO_EEPROM),
	/* dev_addr can be set to provide hwaddr. */
पूर्ण;

अटल काष्ठा platक्रमm_device anw6410_device_eth = अणु
	.name	= "dm9000",
	.id	= -1,
	.num_resources	= ARRAY_SIZE(anw6410_dm9000_resource),
	.resource	= anw6410_dm9000_resource,
	.dev	= अणु
		.platक्रमm_data  = &anw6410_dm9000_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा map_desc anw6410_iodesc[] __initdata = अणु
	अणु
		.भव	= (अचिन्हित दीर्घ)ANW6410_VA_EXTDEV,
		.pfn		= __phys_to_pfn(ANW6410_PA_EXTDEV),
		.length		= SZ_64K,
		.type		= MT_DEVICE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *anw6410_devices[] __initdata = अणु
	&s3c_device_fb,
	&anw6410_lcd_घातerdev,
	&anw6410_device_eth,
पूर्ण;

अटल व्योम __init anw6410_map_io(व्योम)
अणु
	s3c64xx_init_io(anw6410_iodesc, ARRAY_SIZE(anw6410_iodesc));
	s3c64xx_set_xtal_freq(12000000);
	s3c24xx_init_uarts(anw6410_uartcfgs, ARRAY_SIZE(anw6410_uartcfgs));
	s3c64xx_set_समयr_source(S3C64XX_PWM3, S3C64XX_PWM4);

	anw6410_lcd_mode_set();
पूर्ण

अटल व्योम __init anw6410_machine_init(व्योम)
अणु
	s3c_fb_set_platdata(&anw6410_lcd_pdata);

	gpio_request(S3C64XX_GPF(1), "panel power");
	gpio_request(S3C64XX_GPF(4), "LCD backlight");

	anw6410_dm9000_enable();

	platक्रमm_add_devices(anw6410_devices, ARRAY_SIZE(anw6410_devices));
पूर्ण

MACHINE_START(ANW6410, "A&W6410")
	/* Maपूर्णांकainer: Kwangwoo Lee <kwangwoo.lee@gmail.com> */
	.atag_offset	= 0x100,
	.nr_irqs	= S3C64XX_NR_IRQS,
	.init_irq	= s3c6410_init_irq,
	.map_io		= anw6410_map_io,
	.init_machine	= anw6410_machine_init,
	.init_समय	= s3c64xx_समयr_init,
MACHINE_END
