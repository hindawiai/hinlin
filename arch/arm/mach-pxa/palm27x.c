<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Common code क्रम Palm LD, T5, TX, Z72
 *
 * Copyright (C) 2010-2011 Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/wm97xx.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/regulator/max1586.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa27x.h"
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/asoc-palm27x.h>
#समावेश "palm27x.h"

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
अटल काष्ठा pxamci_platक्रमm_data palm27x_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.detect_delay_ms	= 200,
पूर्ण;

व्योम __init palm27x_mmc_init(काष्ठा gpiod_lookup_table *gtable)
अणु
	अगर (gtable)
		gpiod_add_lookup_table(gtable);
	pxa_set_mci_info(&palm27x_mci_platक्रमm_data);
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Power management - standby
 ******************************************************************************/
#अगर defined(CONFIG_SUSPEND)
व्योम __init palm27x_pm_init(अचिन्हित दीर्घ str_base)
अणु
	अटल स्थिर अचिन्हित दीर्घ resume[] = अणु
		0xe3a00101,	/* mov	r0,	#0x40000000 */
		0xe380060f,	/* orr	r0, r0, #0x00f00000 */
		0xe590f008,	/* ldr	pc, [r0, #0x08] */
	पूर्ण;

	/*
	 * Copy the bootloader.
	 * NOTE: PalmZ72 uses a dअगरferent wakeup method!
	 */
	स_नकल(phys_to_virt(str_base), resume, माप(resume));
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Framebuffer
 ******************************************************************************/
#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
काष्ठा pxafb_mode_info palm_320x480_lcd_mode = अणु
	.pixघड़ी	= 57692,
	.xres		= 320,
	.yres		= 480,
	.bpp		= 16,

	.left_margin	= 32,
	.right_margin	= 1,
	.upper_margin	= 7,
	.lower_margin	= 1,

	.hsync_len	= 4,
	.vsync_len	= 1,
पूर्ण;

काष्ठा pxafb_mode_info palm_320x320_lcd_mode = अणु
	.pixघड़ी	= 115384,
	.xres		= 320,
	.yres		= 320,
	.bpp		= 16,

	.left_margin	= 27,
	.right_margin	= 7,
	.upper_margin	= 7,
	.lower_margin	= 8,

	.hsync_len	= 6,
	.vsync_len	= 1,
पूर्ण;

काष्ठा pxafb_mode_info palm_320x320_new_lcd_mode = अणु
	.pixघड़ी	= 86538,
	.xres		= 320,
	.yres		= 320,
	.bpp		= 16,

	.left_margin	= 20,
	.right_margin	= 8,
	.upper_margin	= 8,
	.lower_margin	= 5,

	.hsync_len	= 4,
	.vsync_len	= 1,
पूर्ण;

अटल काष्ठा pxafb_mach_info palm27x_lcd_screen = अणु
	.num_modes	= 1,
	.lcd_conn	= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल पूर्णांक palm27x_lcd_घातer;
अटल व्योम palm27x_lcd_ctl(पूर्णांक on, काष्ठा fb_var_screeninfo *info)
अणु
	gpio_set_value(palm27x_lcd_घातer, on);
पूर्ण

व्योम __init palm27x_lcd_init(पूर्णांक घातer, काष्ठा pxafb_mode_info *mode)
अणु
	palm27x_lcd_screen.modes = mode;

	अगर (gpio_is_valid(घातer)) अणु
		अगर (!gpio_request(घातer, "LCD power")) अणु
			pr_err("Palm27x: failed to claim lcd power gpio!\n");
			वापस;
		पूर्ण
		अगर (!gpio_direction_output(घातer, 1)) अणु
			pr_err("Palm27x: lcd power configuration failed!\n");
			वापस;
		पूर्ण
		palm27x_lcd_घातer = घातer;
		palm27x_lcd_screen.pxafb_lcd_घातer = palm27x_lcd_ctl;
	पूर्ण

	pxa_set_fb_info(शून्य, &palm27x_lcd_screen);
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB Gadget
 ******************************************************************************/
#अगर	defined(CONFIG_USB_PXA27X) || \
	defined(CONFIG_USB_PXA27X_MODULE)

/* The actual GPIO offsets get filled in in the palm27x_udc_init() call */
अटल काष्ठा gpiod_lookup_table palm27x_udc_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", 0,
			    "vbus", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", 0,
			    "pullup", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device palm27x_gpio_vbus = अणु
	.name	= "gpio-vbus",
	.id	= -1,
पूर्ण;

व्योम __init palm27x_udc_init(पूर्णांक vbus, पूर्णांक pullup, पूर्णांक vbus_inverted)
अणु
	palm27x_udc_gpiod_table.table[0].chip_hwnum = vbus;
	palm27x_udc_gpiod_table.table[1].chip_hwnum = pullup;
	अगर (vbus_inverted)
		palm27x_udc_gpiod_table.table[0].flags = GPIO_ACTIVE_LOW;

	gpiod_add_lookup_table(&palm27x_udc_gpiod_table);
	platक्रमm_device_रेजिस्टर(&palm27x_gpio_vbus);
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 * IrDA
 ******************************************************************************/
#अगर defined(CONFIG_IRDA) || defined(CONFIG_IRDA_MODULE)
अटल काष्ठा pxaficp_platक्रमm_data palm27x_ficp_platक्रमm_data = अणु
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
पूर्ण;

व्योम __init palm27x_irda_init(पूर्णांक pwdn)
अणु
	palm27x_ficp_platक्रमm_data.gpio_pwकरोwn = pwdn;
	pxa_set_ficp_info(&palm27x_ficp_platक्रमm_data);
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 * WM97xx audio, battery
 ******************************************************************************/
#अगर	defined(CONFIG_TOUCHSCREEN_WM97XX) || \
	defined(CONFIG_TOUCHSCREEN_WM97XX_MODULE)
अटल काष्ठा wm97xx_batt_pdata palm27x_batt_pdata = अणु
	.batt_aux	= WM97XX_AUX_ID3,
	.temp_aux	= WM97XX_AUX_ID2,
	.batt_mult	= 1000,
	.batt_भाग	= 414,
	.temp_mult	= 1,
	.temp_भाग	= 1,
	.batt_tech	= POWER_SUPPLY_TECHNOLOGY_LIPO,
	.batt_name	= "main-batt",
पूर्ण;

अटल काष्ठा wm97xx_pdata palm27x_wm97xx_pdata = अणु
	.batt_pdata	= &palm27x_batt_pdata,
पूर्ण;

अटल pxa2xx_audio_ops_t palm27x_ac97_pdata = अणु
	.codec_pdata	= अणु &palm27x_wm97xx_pdata, पूर्ण,
पूर्ण;

अटल काष्ठा palm27x_asoc_info palm27x_asoc_pdata = अणु
	.jack_gpio	= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device palm27x_asoc = अणु
	.name = "palm27x-asoc",
	.id   = -1,
	.dev  = अणु
		.platक्रमm_data = &palm27x_asoc_pdata,
	पूर्ण,
पूर्ण;

व्योम __init palm27x_ac97_init(पूर्णांक minv, पूर्णांक maxv, पूर्णांक jack, पूर्णांक reset)
अणु
	palm27x_ac97_pdata.reset_gpio	= reset;
	palm27x_asoc_pdata.jack_gpio	= jack;

	अगर (minv < 0 || maxv < 0) अणु
		palm27x_ac97_pdata.codec_pdata[0] = शून्य;
		pxa_set_ac97_info(&palm27x_ac97_pdata);
	पूर्ण अन्यथा अणु
		palm27x_batt_pdata.min_voltage	= minv,
		palm27x_batt_pdata.max_voltage	= maxv,

		pxa_set_ac97_info(&palm27x_ac97_pdata);
		platक्रमm_device_रेजिस्टर(&palm27x_asoc);
	पूर्ण
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Backlight
 ******************************************************************************/
#अगर defined(CONFIG_BACKLIGHT_PWM) || defined(CONFIG_BACKLIGHT_PWM_MODULE)
अटल काष्ठा pwm_lookup palm27x_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 0, "pwm-backlight.0", शून्य, 3500 * 1024,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल पूर्णांक palm_bl_घातer;
अटल पूर्णांक palm_lcd_घातer;

अटल पूर्णांक palm27x_backlight_init(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = gpio_request(palm_bl_घातer, "BL POWER");
	अगर (ret)
		जाओ err;
	ret = gpio_direction_output(palm_bl_घातer, 0);
	अगर (ret)
		जाओ err2;

	अगर (gpio_is_valid(palm_lcd_घातer)) अणु
		ret = gpio_request(palm_lcd_घातer, "LCD POWER");
		अगर (ret)
			जाओ err2;
		ret = gpio_direction_output(palm_lcd_घातer, 0);
		अगर (ret)
			जाओ err3;
	पूर्ण

	वापस 0;
err3:
	gpio_मुक्त(palm_lcd_घातer);
err2:
	gpio_मुक्त(palm_bl_घातer);
err:
	वापस ret;
पूर्ण

अटल पूर्णांक palm27x_backlight_notअगरy(काष्ठा device *dev, पूर्णांक brightness)
अणु
	gpio_set_value(palm_bl_घातer, brightness);
	अगर (gpio_is_valid(palm_lcd_घातer))
		gpio_set_value(palm_lcd_घातer, brightness);
	वापस brightness;
पूर्ण

अटल व्योम palm27x_backlight_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(palm_bl_घातer);
	अगर (gpio_is_valid(palm_lcd_घातer))
		gpio_मुक्त(palm_lcd_घातer);
पूर्ण

अटल काष्ठा platक्रमm_pwm_backlight_data palm27x_backlight_data = अणु
	.max_brightness	= 0xfe,
	.dft_brightness	= 0x7e,
	.init		= palm27x_backlight_init,
	.notअगरy		= palm27x_backlight_notअगरy,
	.निकास		= palm27x_backlight_निकास,
पूर्ण;

अटल काष्ठा platक्रमm_device palm27x_backlight = अणु
	.name	= "pwm-backlight",
	.dev	= अणु
		.parent		= &pxa27x_device_pwm0.dev,
		.platक्रमm_data	= &palm27x_backlight_data,
	पूर्ण,
पूर्ण;

व्योम __init palm27x_pwm_init(पूर्णांक bl, पूर्णांक lcd)
अणु
	palm_bl_घातer	= bl;
	palm_lcd_घातer	= lcd;
	pwm_add_table(palm27x_pwm_lookup, ARRAY_SIZE(palm27x_pwm_lookup));
	platक्रमm_device_रेजिस्टर(&palm27x_backlight);
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Power supply
 ******************************************************************************/
#अगर defined(CONFIG_PDA_POWER) || defined(CONFIG_PDA_POWER_MODULE)
अटल पूर्णांक palm_ac_state;
अटल पूर्णांक palm_usb_state;

अटल पूर्णांक palm27x_घातer_supply_init(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = gpio_request(palm_ac_state, "AC state");
	अगर (ret)
		जाओ err1;
	ret = gpio_direction_input(palm_ac_state);
	अगर (ret)
		जाओ err2;

	अगर (gpio_is_valid(palm_usb_state)) अणु
		ret = gpio_request(palm_usb_state, "USB state");
		अगर (ret)
			जाओ err2;
		ret = gpio_direction_input(palm_usb_state);
		अगर (ret)
			जाओ err3;
	पूर्ण

	वापस 0;
err3:
	gpio_मुक्त(palm_usb_state);
err2:
	gpio_मुक्त(palm_ac_state);
err1:
	वापस ret;
पूर्ण

अटल व्योम palm27x_घातer_supply_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(palm_usb_state);
	gpio_मुक्त(palm_ac_state);
पूर्ण

अटल पूर्णांक palm27x_is_ac_online(व्योम)
अणु
	वापस gpio_get_value(palm_ac_state);
पूर्ण

अटल पूर्णांक palm27x_is_usb_online(व्योम)
अणु
	वापस !gpio_get_value(palm_usb_state);
पूर्ण
अटल अक्षर *palm27x_supplicants[] = अणु
	"main-battery",
पूर्ण;

अटल काष्ठा pda_घातer_pdata palm27x_ps_info = अणु
	.init			= palm27x_घातer_supply_init,
	.निकास			= palm27x_घातer_supply_निकास,
	.is_ac_online		= palm27x_is_ac_online,
	.is_usb_online		= palm27x_is_usb_online,
	.supplied_to		= palm27x_supplicants,
	.num_supplicants	= ARRAY_SIZE(palm27x_supplicants),
पूर्ण;

अटल काष्ठा platक्रमm_device palm27x_घातer_supply = अणु
	.name = "pda-power",
	.id   = -1,
	.dev  = अणु
		.platक्रमm_data = &palm27x_ps_info,
	पूर्ण,
पूर्ण;

व्योम __init palm27x_घातer_init(पूर्णांक ac, पूर्णांक usb)
अणु
	palm_ac_state	= ac;
	palm_usb_state	= usb;
	platक्रमm_device_रेजिस्टर(&palm27x_घातer_supply);
पूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Core घातer regulator
 ******************************************************************************/
#अगर defined(CONFIG_REGULATOR_MAX1586) || \
    defined(CONFIG_REGULATOR_MAX1586_MODULE)
अटल काष्ठा regulator_consumer_supply palm27x_max1587a_consumers[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data palm27x_max1587a_v3_info = अणु
	.स्थिरraपूर्णांकs = अणु
		.name		= "vcc_core range",
		.min_uV		= 900000,
		.max_uV		= 1705000,
		.always_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.consumer_supplies	= palm27x_max1587a_consumers,
	.num_consumer_supplies	= ARRAY_SIZE(palm27x_max1587a_consumers),
पूर्ण;

अटल काष्ठा max1586_subdev_data palm27x_max1587a_subdevs[] = अणु
	अणु
		.name		= "vcc_core",
		.id		= MAX1586_V3,
		.platक्रमm_data	= &palm27x_max1587a_v3_info,
	पूर्ण
पूर्ण;

अटल काष्ठा max1586_platक्रमm_data palm27x_max1587a_info = अणु
	.subdevs     = palm27x_max1587a_subdevs,
	.num_subdevs = ARRAY_SIZE(palm27x_max1587a_subdevs),
	.v3_gain     = MAX1586_GAIN_R24_3k32, /* 730..1550 mV */
पूर्ण;

अटल काष्ठा i2c_board_info __initdata palm27x_pi2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("max1586", 0x14),
		.platक्रमm_data	= &palm27x_max1587a_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_pxa_platक्रमm_data palm27x_i2c_घातer_info = अणु
	.use_pio	= 1,
पूर्ण;

व्योम __init palm27x_pmic_init(व्योम)
अणु
	i2c_रेजिस्टर_board_info(1, ARRAY_AND_SIZE(palm27x_pi2c_board_info));
	pxa27x_set_i2c_घातer_info(&palm27x_i2c_घातer_info);
पूर्ण
#पूर्ण_अगर
