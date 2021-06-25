<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/income.c
 *
 * Support क्रम Income s.r.o. SH-Dmaster PXA270 SBC
 *
 * Copyright (C) 2010
 * Marek Vasut <marek.vasut@gmail.com>
 * Pavel Revak <palo@bielyvlk.sk>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/ioport.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>

#समावेश <mach/hardware.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश "pxa27x.h"
#समावेश "pxa27x-udc.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>

#समावेश "devices.h"
#समावेश "generic.h"

#घोषणा GPIO114_INCOME_ETH_IRQ  (114)
#घोषणा GPIO0_INCOME_SD_DETECT  (0)
#घोषणा GPIO0_INCOME_SD_RO      (1)
#घोषणा GPIO54_INCOME_LED_A     (54)
#घोषणा GPIO55_INCOME_LED_B     (55)
#घोषणा GPIO113_INCOME_TS_IRQ   (113)

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
अटल काष्ठा pxamci_platक्रमm_data income_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.detect_delay_ms	= 200,
पूर्ण;

अटल काष्ठा gpiod_lookup_table income_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		/* Card detect on GPIO 0 */
		GPIO_LOOKUP("gpio-pxa", GPIO0_INCOME_SD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		/* Write protect on GPIO 1 */
		GPIO_LOOKUP("gpio-pxa", GPIO0_INCOME_SD_RO,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init income_mmc_init(व्योम)
अणु
	gpiod_add_lookup_table(&income_mci_gpio_table);
	pxa_set_mci_info(&income_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम income_mmc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB Host
 ******************************************************************************/
#अगर defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
अटल काष्ठा pxaohci_platक्रमm_data income_ohci_info = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT1 | POWER_CONTROL_LOW | POWER_SENSE_LOW,
पूर्ण;

अटल व्योम __init income_uhc_init(व्योम)
अणु
	pxa_set_ohci_info(&income_ohci_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम income_uhc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * LED
 ******************************************************************************/
#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
काष्ठा gpio_led income_gpio_leds[] = अणु
	अणु
		.name			= "income:green:leda",
		.शेष_trigger	= "none",
		.gpio			= GPIO54_INCOME_LED_A,
		.active_low		= 1,
	पूर्ण,
	अणु
		.name			= "income:green:ledb",
		.शेष_trigger	= "none",
		.gpio			= GPIO55_INCOME_LED_B,
		.active_low		= 1,
	पूर्ण
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data income_gpio_led_info = अणु
	.leds		= income_gpio_leds,
	.num_leds	= ARRAY_SIZE(income_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device income_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &income_gpio_led_info,
	पूर्ण
पूर्ण;

अटल व्योम __init income_led_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&income_leds);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम income_led_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * I2C
 ******************************************************************************/
#अगर defined(CONFIG_I2C_PXA) || defined(CONFIG_I2C_PXA_MODULE)
अटल काष्ठा i2c_board_info __initdata income_i2c_devs[] = अणु
	अणु
		I2C_BOARD_INFO("ds1340", 0x68),
	पूर्ण, अणु
		I2C_BOARD_INFO("lm75", 0x4f),
	पूर्ण,
पूर्ण;

अटल व्योम __init income_i2c_init(व्योम)
अणु
	pxa_set_i2c_info(शून्य);
	pxa27x_set_i2c_घातer_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(income_i2c_devs));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम income_i2c_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Framebuffer
 ******************************************************************************/
#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pxafb_mode_info income_lcd_modes[] = अणु
अणु
	.pixघड़ी	= 144700,
	.xres		= 320,
	.yres		= 240,
	.bpp		= 32,
	.depth		= 18,

	.left_margin	= 10,
	.right_margin	= 10,
	.upper_margin	= 7,
	.lower_margin	= 8,

	.hsync_len	= 20,
	.vsync_len	= 2,

	.sync		= FB_SYNC_VERT_HIGH_ACT,
पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info income_lcd_screen = अणु
	.modes		= income_lcd_modes,
	.num_modes	= ARRAY_SIZE(income_lcd_modes),
	.lcd_conn	= LCD_COLOR_TFT_18BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल व्योम __init income_lcd_init(व्योम)
अणु
	pxa_set_fb_info(शून्य, &income_lcd_screen);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम income_lcd_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Backlight
 ******************************************************************************/
#अगर defined(CONFIG_BACKLIGHT_PWM) || defined(CONFIG_BACKLIGHT_PWM_MODULE)
अटल काष्ठा pwm_lookup income_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 0, "pwm-backlight.0", शून्य, 1000000,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data income_backlight_data = अणु
	.max_brightness	= 0x3ff,
	.dft_brightness	= 0x1ff,
पूर्ण;

अटल काष्ठा platक्रमm_device income_backlight = अणु
	.name	= "pwm-backlight",
	.dev	= अणु
		.parent		= &pxa27x_device_pwm0.dev,
		.platक्रमm_data	= &income_backlight_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init income_pwm_init(व्योम)
अणु
	pwm_add_table(income_pwm_lookup, ARRAY_SIZE(income_pwm_lookup));
	platक्रमm_device_रेजिस्टर(&income_backlight);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम income_pwm_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

व्योम __init colibri_pxa270_income_boardinit(व्योम)
अणु
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	income_mmc_init();
	income_uhc_init();
	income_led_init();
	income_i2c_init();
	income_lcd_init();
	income_pwm_init();
पूर्ण

