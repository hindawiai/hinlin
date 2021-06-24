<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम HTC Magician PDA phones:
 * i-mate JAM, O2 Xda mini, Orange SPV M500, Qtek s100, Qtek s110
 * and T-Mobile MDA Compact.
 *
 * Copyright (c) 2006-2007 Philipp Zabel
 *
 * Based on hx4700.c, spitz.c and others.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/mfd/htc-pasic3.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/platक्रमm_data/gpio-htc-egpपन.स>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/fixed.h>
#समावेश <linux/regulator/gpio-regulator.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश "pxa27x.h"
#समावेश <mach/magician.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>

#समावेश <linux/regulator/max1586.h>

#समावेश <linux/platक्रमm_data/pxa2xx_udc.h>

#समावेश "udc.h"
#समावेश "pxa27x-udc.h"
#समावेश "devices.h"
#समावेश "generic.h"

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/spi/ads7846.h>

अटल अचिन्हित दीर्घ magician_pin_config[] __initdata = अणु

	/* SDRAM and Static Memory I/O Signals */
	GPIO20_nSDCS_2,
	GPIO21_nSDCS_3,
	GPIO15_nCS_1,
	GPIO78_nCS_2,	/* PASIC3 */
	GPIO79_nCS_3,	/* EGPIO CPLD */
	GPIO80_nCS_4,
	GPIO33_nCS_5,

	/* I2C UDA1380 + OV9640 */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* PWM 0 - LCD backlight */
	GPIO16_PWM0_OUT,

	/* I2S UDA1380 capture */
	GPIO28_I2S_BITCLK_OUT,
	GPIO29_I2S_SDATA_IN,
	GPIO31_I2S_SYNC,
	GPIO113_I2S_SYSCLK,

	/* SSP 1 UDA1380 playback */
	GPIO23_SSP1_SCLK,
	GPIO24_SSP1_SFRM,
	GPIO25_SSP1_TXD,

	/* SSP 2 TSC2046 touchscreen */
	GPIO19_SSP2_SCLK,
	MFP_CFG_OUT(GPIO14, AF0, DRIVE_HIGH),	/* frame as GPIO */
	GPIO89_SSP2_TXD,
	GPIO88_SSP2_RXD,

	/* MMC/SD/SDHC slot */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,

	/* QCI camera पूर्णांकerface */
	GPIO12_CIF_DD_7,
	GPIO17_CIF_DD_6,
	GPIO50_CIF_DD_3,
	GPIO51_CIF_DD_2,
	GPIO52_CIF_DD_4,
	GPIO53_CIF_MCLK,
	GPIO54_CIF_PCLK,
	GPIO55_CIF_DD_1,
	GPIO81_CIF_DD_0,
	GPIO82_CIF_DD_5,
	GPIO84_CIF_FV,
	GPIO85_CIF_LV,

	/* Magician specअगरic input GPIOs */
	GPIO9_GPIO,	/* unknown */
	GPIO10_GPIO,	/* GSM_IRQ */
	GPIO13_GPIO,	/* CPLD_IRQ */
	GPIO107_GPIO,	/* DS1WM_IRQ */
	GPIO108_GPIO,	/* GSM_READY */
	GPIO115_GPIO,	/* nPEN_IRQ */
पूर्ण;

/*
 * IrDA
 */

अटल काष्ठा pxaficp_platक्रमm_data magician_ficp_info = अणु
	.gpio_pwकरोwn		= GPIO83_MAGICIAN_nIR_EN,
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
	.gpio_pwकरोwn_inverted	= 0,
पूर्ण;

/*
 * GPIO Keys
 */

#घोषणा INIT_KEY(_code, _gpio, _desc)	\
	अणु				\
		.code	= KEY_##_code,	\
		.gpio	= _gpio,	\
		.desc	= _desc,	\
		.type	= EV_KEY,	\
		.wakeup	= 1,		\
	पूर्ण

अटल काष्ठा gpio_keys_button magician_button_table[] = अणु
	INIT_KEY(POWER,      GPIO0_MAGICIAN_KEY_POWER,      "Power button"),
	INIT_KEY(ESC,        GPIO37_MAGICIAN_KEY_HANGUP,    "Hangup button"),
	INIT_KEY(F10,        GPIO38_MAGICIAN_KEY_CONTACTS,  "Contacts button"),
	INIT_KEY(CALENDAR,   GPIO90_MAGICIAN_KEY_CALENDAR,  "Calendar button"),
	INIT_KEY(CAMERA,     GPIO91_MAGICIAN_KEY_CAMERA,    "Camera button"),
	INIT_KEY(UP,         GPIO93_MAGICIAN_KEY_UP,        "Up button"),
	INIT_KEY(DOWN,       GPIO94_MAGICIAN_KEY_DOWN,      "Down button"),
	INIT_KEY(LEFT,       GPIO95_MAGICIAN_KEY_LEFT,      "Left button"),
	INIT_KEY(RIGHT,      GPIO96_MAGICIAN_KEY_RIGHT,     "Right button"),
	INIT_KEY(KPENTER,    GPIO97_MAGICIAN_KEY_ENTER,     "Action button"),
	INIT_KEY(RECORD,     GPIO98_MAGICIAN_KEY_RECORD,    "Record button"),
	INIT_KEY(VOLUMEUP,   GPIO100_MAGICIAN_KEY_VOL_UP,   "Volume up"),
	INIT_KEY(VOLUMEDOWN, GPIO101_MAGICIAN_KEY_VOL_DOWN, "Volume down"),
	INIT_KEY(PHONE,      GPIO102_MAGICIAN_KEY_PHONE,    "Phone button"),
	INIT_KEY(PLAY,       GPIO99_MAGICIAN_HEADPHONE_IN,  "Headset button"),
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data gpio_keys_data = अणु
	.buttons	= magician_button_table,
	.nbuttons	= ARRAY_SIZE(magician_button_table),
पूर्ण;

अटल काष्ठा platक्रमm_device gpio_keys = अणु
	.name	= "gpio-keys",
	.dev	= अणु
		.platक्रमm_data = &gpio_keys_data,
	पूर्ण,
	.id	= -1,
पूर्ण;

/*
 * EGPIO (Xilinx CPLD)
 *
 * 32-bit aligned 8-bit रेजिस्टरs
 * 16 possible रेजिस्टरs (reg winकरोws size), only 7 used:
 * 3x output, 1x irq, 3x input
 */

अटल काष्ठा resource egpio_resources[] = अणु
	[0] = अणु
		.start	= PXA_CS3_PHYS,
		.end	= PXA_CS3_PHYS + 0x20 - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_GPIO_TO_IRQ(GPIO13_MAGICIAN_CPLD_IRQ),
		.end	= PXA_GPIO_TO_IRQ(GPIO13_MAGICIAN_CPLD_IRQ),
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा htc_egpio_chip egpio_chips[] = अणु
	[0] = अणु
		.reg_start	= 0,
		.gpio_base	= MAGICIAN_EGPIO(0, 0),
		.num_gpios	= 24,
		.direction	= HTC_EGPIO_OUTPUT,
		/*
		 * Depends on modules configuration
		 */
		.initial_values	= 0x40, /* EGPIO_MAGICIAN_GSM_RESET */
	पूर्ण,
	[1] = अणु
		.reg_start	= 4,
		.gpio_base	= MAGICIAN_EGPIO(4, 0),
		.num_gpios	= 24,
		.direction	= HTC_EGPIO_INPUT,
	पूर्ण,
पूर्ण;

अटल काष्ठा htc_egpio_platक्रमm_data egpio_info = अणु
	.reg_width	= 8,
	.bus_width	= 32,
	.irq_base	= IRQ_BOARD_START,
	.num_irqs	= 4,
	.ack_रेजिस्टर	= 3,
	.chip		= egpio_chips,
	.num_chips	= ARRAY_SIZE(egpio_chips),
पूर्ण;

अटल काष्ठा platक्रमm_device egpio = अणु
	.name		= "htc-egpio",
	.id		= -1,
	.resource	= egpio_resources,
	.num_resources	= ARRAY_SIZE(egpio_resources),
	.dev = अणु
		.platक्रमm_data = &egpio_info,
	पूर्ण,
पूर्ण;

/*
 * PXAFB LCD - Toppoly TD028STEB1 or Samsung LTP280QV
 */

अटल काष्ठा pxafb_mode_info toppoly_modes[] = अणु
	अणु
		.pixघड़ी	= 96153,
		.bpp		= 16,
		.xres		= 240,
		.yres		= 320,
		.hsync_len	= 11,
		.vsync_len	= 3,
		.left_margin	= 19,
		.upper_margin	= 2,
		.right_margin	= 10,
		.lower_margin	= 2,
		.sync		= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mode_info samsung_modes[] = अणु
	अणु
		.pixघड़ी	= 226469,
		.bpp		= 16,
		.xres		= 240,
		.yres		= 320,
		.hsync_len	= 8,
		.vsync_len	= 4,
		.left_margin	= 9,
		.upper_margin	= 4,
		.right_margin	= 9,
		.lower_margin	= 4,
		.sync	= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	पूर्ण,
पूर्ण;

अटल व्योम toppoly_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *si)
अणु
	pr_debug("Toppoly LCD power: %s\n", on ? "on" : "off");

	अगर (on) अणु
		gpio_set_value(EGPIO_MAGICIAN_TOPPOLY_POWER, 1);
		gpio_set_value(GPIO106_MAGICIAN_LCD_DCDC_NRESET, 1);
		udelay(2000);
		gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 1);
		udelay(2000);
		/* FIXME: enable LCDC here */
		udelay(2000);
		gpio_set_value(GPIO104_MAGICIAN_LCD_VOFF_EN, 1);
		udelay(2000);
		gpio_set_value(GPIO105_MAGICIAN_LCD_VON_EN, 1);
	पूर्ण अन्यथा अणु
		msleep(15);
		gpio_set_value(GPIO105_MAGICIAN_LCD_VON_EN, 0);
		udelay(500);
		gpio_set_value(GPIO104_MAGICIAN_LCD_VOFF_EN, 0);
		udelay(1000);
		gpio_set_value(GPIO106_MAGICIAN_LCD_DCDC_NRESET, 0);
		gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 0);
	पूर्ण
पूर्ण

अटल व्योम samsung_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *si)
अणु
	pr_debug("Samsung LCD power: %s\n", on ? "on" : "off");

	अगर (on) अणु
		अगर (प्रणाली_rev < 3)
			gpio_set_value(GPIO75_MAGICIAN_SAMSUNG_POWER, 1);
		अन्यथा
			gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 1);
		mdelay(6);
		gpio_set_value(GPIO106_MAGICIAN_LCD_DCDC_NRESET, 1);
		mdelay(6);	/* Avdd -> Voff >5ms */
		gpio_set_value(GPIO104_MAGICIAN_LCD_VOFF_EN, 1);
		mdelay(16);	/* Voff -> Von >(5+10)ms */
		gpio_set_value(GPIO105_MAGICIAN_LCD_VON_EN, 1);
	पूर्ण अन्यथा अणु
		gpio_set_value(GPIO105_MAGICIAN_LCD_VON_EN, 0);
		mdelay(16);
		gpio_set_value(GPIO104_MAGICIAN_LCD_VOFF_EN, 0);
		mdelay(6);
		gpio_set_value(GPIO106_MAGICIAN_LCD_DCDC_NRESET, 0);
		mdelay(6);
		अगर (प्रणाली_rev < 3)
			gpio_set_value(GPIO75_MAGICIAN_SAMSUNG_POWER, 0);
		अन्यथा
			gpio_set_value(EGPIO_MAGICIAN_LCD_POWER, 0);
	पूर्ण
पूर्ण

अटल काष्ठा pxafb_mach_info toppoly_info = अणु
	.modes			= toppoly_modes,
	.num_modes		= 1,
	.fixed_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP,
	.pxafb_lcd_घातer	= toppoly_lcd_घातer,
पूर्ण;

अटल काष्ठा pxafb_mach_info samsung_info = अणु
	.modes			= samsung_modes,
	.num_modes		= 1,
	.fixed_modes		= 1,
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL |
		LCD_ALTERNATE_MAPPING,
	.pxafb_lcd_घातer	= samsung_lcd_घातer,
पूर्ण;

/*
 * Backlight
 */

अटल काष्ठा pwm_lookup magician_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 0, "pwm-backlight", शून्य, 30923,
		   PWM_POLARITY_NORMAL),
पूर्ण;

 /*
 * fixed regulator क्रम pwm_backlight
 */

अटल काष्ठा regulator_consumer_supply pwm_backlight_supply[] = अणु
	REGULATOR_SUPPLY("power", "pwm_backlight"),
पूर्ण;


अटल काष्ठा gpio magician_bl_gpios[] = अणु
	अणु EGPIO_MAGICIAN_BL_POWER,	GPIOF_सूची_OUT, "Backlight power" पूर्ण,
	अणु EGPIO_MAGICIAN_BL_POWER2,	GPIOF_सूची_OUT, "Backlight power 2" पूर्ण,
पूर्ण;

अटल पूर्णांक magician_backlight_init(काष्ठा device *dev)
अणु
	वापस gpio_request_array(ARRAY_AND_SIZE(magician_bl_gpios));
पूर्ण

अटल पूर्णांक magician_backlight_notअगरy(काष्ठा device *dev, पूर्णांक brightness)
अणु
	pr_debug("Brightness = %i\n", brightness);
	gpio_set_value(EGPIO_MAGICIAN_BL_POWER, brightness);
	अगर (brightness >= 200) अणु
		gpio_set_value(EGPIO_MAGICIAN_BL_POWER2, 1);
		वापस brightness - 72;
	पूर्ण अन्यथा अणु
		gpio_set_value(EGPIO_MAGICIAN_BL_POWER2, 0);
		वापस brightness;
	पूर्ण
पूर्ण

अटल व्योम magician_backlight_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त_array(ARRAY_AND_SIZE(magician_bl_gpios));
पूर्ण

/*
 * LCD PWM backlight (मुख्य)
 *
 * MP1521 frequency should be:
 *	100-400 Hz = 2ै /.5*10^6 - 10ै /*10^6 ns
 */

अटल काष्ठा platक्रमm_pwm_backlight_data backlight_data = अणु
	.max_brightness	= 272,
	.dft_brightness	= 100,
	.init		= magician_backlight_init,
	.notअगरy		= magician_backlight_notअगरy,
	.निकास		= magician_backlight_निकास,
पूर्ण;

अटल काष्ठा platक्रमm_device backlight = अणु
	.name	= "pwm-backlight",
	.id	= -1,
	.dev	= अणु
		.parent		= &pxa27x_device_pwm0.dev,
		.platक्रमm_data	= &backlight_data,
	पूर्ण,
पूर्ण;

/*
 * GPIO LEDs, Phone keys backlight, vibra
 */

अटल काष्ठा gpio_led gpio_leds[] = अणु
	अणु
		.name = "magician::vibra",
		.शेष_trigger = "none",
		.gpio = GPIO22_MAGICIAN_VIBRA_EN,
	पूर्ण,
	अणु
		.name = "magician::phone_bl",
		.शेष_trigger = "backlight",
		.gpio = GPIO103_MAGICIAN_LED_KP,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data gpio_led_info = अणु
	.leds = gpio_leds,
	.num_leds = ARRAY_SIZE(gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device leds_gpio = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &gpio_led_info,
	पूर्ण,
पूर्ण;

/*
 * PASIC3 with DS1WM
 */

अटल काष्ठा resource pasic3_resources[] = अणु
	[0] = अणु
		.start	= PXA_CS2_PHYS,
		.end	= PXA_CS2_PHYS + 0x1b,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	/* No IRQ handler in the PASIC3, DS1WM needs an बाह्यal IRQ */
	[1] = अणु
		.start	= PXA_GPIO_TO_IRQ(GPIO107_MAGICIAN_DS1WM_IRQ),
		.end	= PXA_GPIO_TO_IRQ(GPIO107_MAGICIAN_DS1WM_IRQ),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा pasic3_platक्रमm_data pasic3_platक्रमm_data = अणु
	.घड़ी_rate = 4000000,
पूर्ण;

अटल काष्ठा platक्रमm_device pasic3 = अणु
	.name		= "pasic3",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(pasic3_resources),
	.resource	= pasic3_resources,
	.dev = अणु
		.platक्रमm_data = &pasic3_platक्रमm_data,
	पूर्ण,
पूर्ण;

/*
 * PXA UDC
 */

अटल व्योम magician_udc_command(पूर्णांक cmd)
अणु
	अगर (cmd == PXA2XX_UDC_CMD_CONNECT)
		UP2OCR |= UP2OCR_DPPUE | UP2OCR_DPPUBE;
	अन्यथा अगर (cmd == PXA2XX_UDC_CMD_DISCONNECT)
		UP2OCR &= ~(UP2OCR_DPPUE | UP2OCR_DPPUBE);
पूर्ण

अटल काष्ठा pxa2xx_udc_mach_info magician_udc_info __initdata = अणु
	.udc_command	= magician_udc_command,
	.gpio_pullup	= GPIO27_MAGICIAN_USBC_PUEN,
पूर्ण;

/*
 * USB device VBus detection
 */

अटल काष्ठा resource gpio_vbus_resource = अणु
	.flags	= IORESOURCE_IRQ,
	.start	= IRQ_MAGICIAN_VBUS,
	.end	= IRQ_MAGICIAN_VBUS,
पूर्ण;

अटल काष्ठा gpiod_lookup_table gpio_vbus_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		/*
		 * EGPIO on रेजिस्टर 4 index 1, the second EGPIO chip
		 * starts at रेजिस्टर 4 so this will be at index 1 on that
		 * chip.
		 */
		GPIO_LOOKUP("htc-egpio-1", 1,
			    "vbus", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO27_MAGICIAN_USBC_PUEN,
			    "pullup", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device gpio_vbus = अणु
	.name		= "gpio-vbus",
	.id		= -1,
	.num_resources	= 1,
	.resource	= &gpio_vbus_resource,
पूर्ण;

/*
 * External घातer
 */

अटल पूर्णांक magician_supply_init(काष्ठा device *dev)
अणु
	पूर्णांक ret = -1;

	ret = gpio_request(EGPIO_MAGICIAN_CABLE_TYPE, "Cable is AC charger");
	अगर (ret) अणु
		pr_err("Cannot request AC/USB charger GPIO (%i)\n", ret);
		जाओ err_ac;
	पूर्ण

	ret = gpio_request(EGPIO_MAGICIAN_CABLE_INSERTED, "Cable inserted");
	अगर (ret) अणु
		pr_err("Cannot request cable detection GPIO (%i)\n", ret);
		जाओ err_usb;
	पूर्ण

	वापस 0;

err_usb:
	gpio_मुक्त(EGPIO_MAGICIAN_CABLE_TYPE);
err_ac:
	वापस ret;
पूर्ण

अटल व्योम magician_set_अक्षरge(पूर्णांक flags)
अणु
	अगर (flags & PDA_POWER_CHARGE_AC) अणु
		pr_debug("Charging from AC\n");
		gpio_set_value(EGPIO_MAGICIAN_NICD_CHARGE, 1);
	पूर्ण अन्यथा अगर (flags & PDA_POWER_CHARGE_USB) अणु
		pr_debug("Charging from USB\n");
		gpio_set_value(EGPIO_MAGICIAN_NICD_CHARGE, 1);
	पूर्ण अन्यथा अणु
		pr_debug("Charging disabled\n");
		gpio_set_value(EGPIO_MAGICIAN_NICD_CHARGE, 0);
	पूर्ण
पूर्ण

अटल पूर्णांक magician_is_ac_online(व्योम)
अणु
	वापस gpio_get_value(EGPIO_MAGICIAN_CABLE_INSERTED) &&
		gpio_get_value(EGPIO_MAGICIAN_CABLE_TYPE); /* AC=1 */
पूर्ण

अटल पूर्णांक magician_is_usb_online(व्योम)
अणु
	वापस gpio_get_value(EGPIO_MAGICIAN_CABLE_INSERTED) &&
		(!gpio_get_value(EGPIO_MAGICIAN_CABLE_TYPE)); /* USB=0 */
पूर्ण

अटल व्योम magician_supply_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(EGPIO_MAGICIAN_CABLE_INSERTED);
	gpio_मुक्त(EGPIO_MAGICIAN_CABLE_TYPE);
पूर्ण

अटल अक्षर *magician_supplicants[] = अणु
	"ds2760-battery.0", "backup-battery"
पूर्ण;

अटल काष्ठा pda_घातer_pdata घातer_supply_info = अणु
	.init			= magician_supply_init,
	.निकास			= magician_supply_निकास,
	.is_ac_online		= magician_is_ac_online,
	.is_usb_online		= magician_is_usb_online,
	.set_अक्षरge		= magician_set_अक्षरge,
	.supplied_to		= magician_supplicants,
	.num_supplicants	= ARRAY_SIZE(magician_supplicants),
पूर्ण;

अटल काष्ठा resource घातer_supply_resources[] = अणु
	[0] = अणु
		.name	= "ac",
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE |
			IORESOURCE_IRQ_LOWEDGE,
		.start	= IRQ_MAGICIAN_VBUS,
		.end	= IRQ_MAGICIAN_VBUS,
	पूर्ण,
	[1] = अणु
		.name	= "usb",
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE |
			IORESOURCE_IRQ_LOWEDGE,
		.start	= IRQ_MAGICIAN_VBUS,
		.end	= IRQ_MAGICIAN_VBUS,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device घातer_supply = अणु
	.name	= "pda-power",
	.id	= -1,
	.dev = अणु
		.platक्रमm_data = &घातer_supply_info,
	पूर्ण,
	.resource	= घातer_supply_resources,
	.num_resources	= ARRAY_SIZE(घातer_supply_resources),
पूर्ण;

/*
 * Battery अक्षरger
 */

अटल काष्ठा regulator_consumer_supply bq24022_consumers[] = अणु
	REGULATOR_SUPPLY("vbus_draw", शून्य),
	REGULATOR_SUPPLY("ac_draw", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data bq24022_init_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.max_uA		= 500000,
		.valid_ops_mask	= REGULATOR_CHANGE_CURRENT |
			REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies	= ARRAY_SIZE(bq24022_consumers),
	.consumer_supplies	= bq24022_consumers,
पूर्ण;


अटल क्रमागत gpiod_flags bq24022_gpiod_gflags[] = अणु GPIOD_OUT_LOW पूर्ण;

अटल काष्ठा gpio_regulator_state bq24022_states[] = अणु
	अणु .value = 100000, .gpios = (0 << 0) पूर्ण,
	अणु .value = 500000, .gpios = (1 << 0) पूर्ण,
पूर्ण;

अटल काष्ठा gpio_regulator_config bq24022_info = अणु
	.supply_name		= "bq24022",

	.enabled_at_boot	= 1,

	.gflags = bq24022_gpiod_gflags,
	.ngpios = ARRAY_SIZE(bq24022_gpiod_gflags),

	.states			= bq24022_states,
	.nr_states		= ARRAY_SIZE(bq24022_states),

	.type			= REGULATOR_CURRENT,
	.init_data		= &bq24022_init_data,
पूर्ण;

अटल काष्ठा platक्रमm_device bq24022 = अणु
	.name	= "gpio-regulator",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &bq24022_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table bq24022_gpiod_table = अणु
	.dev_id = "gpio-regulator",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", EGPIO_MAGICIAN_BQ24022_ISET2,
			    शून्य, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO30_MAGICIAN_BQ24022_nCHARGE_EN,
			    "enable", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * fixed regulator क्रम ads7846
 */

अटल काष्ठा regulator_consumer_supply ads7846_supply =
	REGULATOR_SUPPLY("vcc", "spi2.0");

अटल काष्ठा regulator_init_data vads7846_regulator = अणु
	.स्थिरraपूर्णांकs	= अणु
		.valid_ops_mask	= REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies	= 1,
	.consumer_supplies	= &ads7846_supply,
पूर्ण;

अटल काष्ठा fixed_voltage_config vads7846 = अणु
	.supply_name	= "vads7846",
	.microvolts	= 3300000, /* probably */
	.startup_delay	= 0,
	.init_data	= &vads7846_regulator,
पूर्ण;

अटल काष्ठा platक्रमm_device vads7846_device = अणु
	.name	= "reg-fixed-voltage",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &vads7846,
	पूर्ण,
पूर्ण;

/*
 * Vcore regulator MAX1587A
 */

अटल काष्ठा regulator_consumer_supply magician_max1587a_consumers[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data magician_max1587a_v3_info = अणु
	.स्थिरraपूर्णांकs = अणु
		.name		= "vcc_core range",
		.min_uV		= 700000,
		.max_uV		= 1475000,
		.always_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.consumer_supplies	= magician_max1587a_consumers,
	.num_consumer_supplies	= ARRAY_SIZE(magician_max1587a_consumers),
पूर्ण;

अटल काष्ठा max1586_subdev_data magician_max1587a_subdevs[] = अणु
	अणु
		.name		= "vcc_core",
		.id		= MAX1586_V3,
		.platक्रमm_data	= &magician_max1587a_v3_info,
	पूर्ण
पूर्ण;

अटल काष्ठा max1586_platक्रमm_data magician_max1587a_info = अणु
	.subdevs     = magician_max1587a_subdevs,
	.num_subdevs = ARRAY_SIZE(magician_max1587a_subdevs),
	/*
	 * NOTICE measured directly on the PCB (board_id == 0x3a), but
	 * अगर R24 is present, it will boost the voltage
	 * (ग_लिखो 1.475V, get 1.645V and smoke)
	 */
	.v3_gain     = MAX1586_GAIN_NO_R24,
पूर्ण;

अटल काष्ठा i2c_board_info magician_pwr_i2c_board_info[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("max1586", 0x14),
		.platक्रमm_data	= &magician_max1587a_info,
	पूर्ण,
पूर्ण;

/*
 * MMC/SD
 */

अटल पूर्णांक magician_mci_init(काष्ठा device *dev,
	irq_handler_t detect_irq, व्योम *data)
अणु
	वापस request_irq(IRQ_MAGICIAN_SD, detect_irq, 0,
		"mmc card detect", data);
पूर्ण

अटल व्योम magician_mci_निकास(काष्ठा device *dev, व्योम *data)
अणु
	मुक्त_irq(IRQ_MAGICIAN_SD, data);
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data magician_mci_info = अणु
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
	.init			= magician_mci_init,
	.निकास			= magician_mci_निकास,
	.gpio_card_ro_invert	= 1,
पूर्ण;

/*
 * Write protect on EGPIO रेजिस्टर 5 index 4, this is on the second HTC
 * EGPIO chip which starts at रेजिस्टर 4, so we need offset 8+4=12 on that
 * particular chip.
 */
#घोषणा EGPIO_MAGICIAN_nSD_READONLY_OFFSET 12
/*
 * Power on EGPIO रेजिस्टर 2 index 0, so this is on the first HTC EGPIO chip
 * starting at रेजिस्टर 0 so we need offset 2*8+0 = 16 on that chip.
 */
#घोषणा EGPIO_MAGICIAN_nSD_POWER_OFFSET 16

अटल काष्ठा gpiod_lookup_table magician_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("htc-egpio-1", EGPIO_MAGICIAN_nSD_READONLY_OFFSET,
			    "wp", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("htc-egpio-0", EGPIO_MAGICIAN_nSD_POWER_OFFSET,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * USB OHCI
 */

अटल काष्ठा pxaohci_platक्रमm_data magician_ohci_info = अणु
	.port_mode	= PMM_PERPORT_MODE,
	/* port1: CSR Bluetooth, port2: OTG with UDC */
	.flags		= ENABLE_PORT1 | ENABLE_PORT2 | POWER_CONTROL_LOW,
	.घातer_budget	= 0,
	.घातer_on_delay = 100,
पूर्ण;

/*
 * StrataFlash
 */

अटल पूर्णांक magician_flash_init(काष्ठा platक्रमm_device *pdev)
अणु
	पूर्णांक ret = gpio_request(EGPIO_MAGICIAN_FLASH_VPP, "flash Vpp enable");

	अगर (ret) अणु
		pr_err("Cannot request flash enable GPIO (%i)\n", ret);
		वापस ret;
	पूर्ण

	ret = gpio_direction_output(EGPIO_MAGICIAN_FLASH_VPP, 1);
	अगर (ret) अणु
		pr_err("Cannot set direction for flash enable (%i)\n", ret);
		gpio_मुक्त(EGPIO_MAGICIAN_FLASH_VPP);
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम magician_set_vpp(काष्ठा platक्रमm_device *pdev, पूर्णांक vpp)
अणु
	gpio_set_value(EGPIO_MAGICIAN_FLASH_VPP, vpp);
पूर्ण

अटल व्योम magician_flash_निकास(काष्ठा platक्रमm_device *pdev)
अणु
	gpio_मुक्त(EGPIO_MAGICIAN_FLASH_VPP);
पूर्ण

अटल काष्ठा resource strataflash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_64M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा mtd_partition magician_flash_parts[] = अणु
	अणु
		.name		= "Bootloader",
		.offset		= 0x0,
		.size		= 0x40000,
		.mask_flags	= MTD_WRITEABLE, /* EXPERIMENTAL */
	पूर्ण,
	अणु
		.name		= "Linux Kernel",
		.offset		= 0x40000,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

/*
 * physmap-flash driver
 */

अटल काष्ठा physmap_flash_data strataflash_data = अणु
	.width		= 4,
	.init		= magician_flash_init,
	.set_vpp	= magician_set_vpp,
	.निकास		= magician_flash_निकास,
	.parts		= magician_flash_parts,
	.nr_parts	= ARRAY_SIZE(magician_flash_parts),
पूर्ण;

अटल काष्ठा platक्रमm_device strataflash = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.resource	= &strataflash_resource,
	.num_resources	= 1,
	.dev = अणु
		.platक्रमm_data = &strataflash_data,
	पूर्ण,
पूर्ण;

/*
 * PXA I2C मुख्य controller
 */

अटल काष्ठा i2c_pxa_platक्रमm_data i2c_info = अणु
	/* OV9640 I2C device करोesn't support fast mode */
	.fast_mode	= 0,
पूर्ण;

/*
 * PXA I2C घातer controller
 */

अटल काष्ठा i2c_pxa_platक्रमm_data magician_i2c_घातer_info = अणु
	.fast_mode	= 1,
पूर्ण;

/*
 * Touchscreen
 */

अटल काष्ठा ads7846_platक्रमm_data ads7846_pdata = अणु
	.model		= 7846,
	.x_plate_ohms	= 317,
	.y_plate_ohms	= 500,
	.pressure_max	= 1023,	/* with x plate ohms it will overflow 255 */
	.debounce_max	= 3,	/* first पढ़ोout is always bad */
	.debounce_tol	= 30,
	.debounce_rep	= 0,
	.gpio_penकरोwn	= GPIO115_MAGICIAN_nPEN_IRQ,
	.keep_vref_on	= 1,
	.wakeup		= true,
	.vref_delay_usecs		= 100,
	.penirq_recheck_delay_usecs	= 100,
पूर्ण;

काष्ठा pxa2xx_spi_chip tsc2046_chip_info = अणु
	.tx_threshold	= 1,
	.rx_threshold	= 2,
	.समयout	= 64,
	/* NOTICE must be GPIO, incompatibility with hw PXA SPI framing */
	.gpio_cs	= GPIO14_MAGICIAN_TSC2046_CS,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller magician_spi_info = अणु
	.num_chipselect	= 1,
	.enable_dma	= 1,
पूर्ण;

अटल काष्ठा spi_board_info ads7846_spi_board_info[] __initdata = अणु
	अणु
		.modalias		= "ads7846",
		.bus_num		= 2,
		.max_speed_hz		= 2500000,
		.platक्रमm_data		= &ads7846_pdata,
		.controller_data	= &tsc2046_chip_info,
		.irq = PXA_GPIO_TO_IRQ(GPIO115_MAGICIAN_nPEN_IRQ),
	पूर्ण,
पूर्ण;

/*
 * Platक्रमm devices
 */

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&gpio_keys,
	&egpio,
	&backlight,
	&pasic3,
	&bq24022,
	&gpio_vbus,
	&घातer_supply,
	&strataflash,
	&leds_gpio,
	&vads7846_device,
पूर्ण;

अटल काष्ठा gpio magician_global_gpios[] = अणु
	अणु GPIO13_MAGICIAN_CPLD_IRQ, GPIOF_IN, "CPLD_IRQ" पूर्ण,
	अणु GPIO107_MAGICIAN_DS1WM_IRQ, GPIOF_IN, "DS1WM_IRQ" पूर्ण,

	/* NOTICE valid LCD init sequence */
	अणु GPIO106_MAGICIAN_LCD_DCDC_NRESET, GPIOF_OUT_INIT_LOW, "LCD DCDC nreset" पूर्ण,
	अणु GPIO104_MAGICIAN_LCD_VOFF_EN, GPIOF_OUT_INIT_LOW, "LCD VOFF enable" पूर्ण,
	अणु GPIO105_MAGICIAN_LCD_VON_EN, GPIOF_OUT_INIT_LOW, "LCD VON enable" पूर्ण,
पूर्ण;

अटल व्योम __init magician_init(व्योम)
अणु
	व्योम __iomem *cpld;
	पूर्णांक lcd_select;
	पूर्णांक err;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(magician_pin_config));
	err = gpio_request_array(ARRAY_AND_SIZE(magician_global_gpios));
	अगर (err)
		pr_err("magician: Failed to request global GPIOs: %d\n", err);

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);

	pwm_add_table(magician_pwm_lookup, ARRAY_SIZE(magician_pwm_lookup));

	pxa_set_ficp_info(&magician_ficp_info);
	pxa27x_set_i2c_घातer_info(&magician_i2c_घातer_info);
	pxa_set_i2c_info(&i2c_info);

	i2c_रेजिस्टर_board_info(1,
		ARRAY_AND_SIZE(magician_pwr_i2c_board_info));

	gpiod_add_lookup_table(&magician_mci_gpio_table);
	pxa_set_mci_info(&magician_mci_info);
	pxa_set_ohci_info(&magician_ohci_info);
	pxa_set_udc_info(&magician_udc_info);

	/* Check LCD type we have */
	cpld = ioremap(PXA_CS3_PHYS, 0x1000);
	अगर (cpld) अणु
		u8 board_id = __raw_पढ़ोb(cpld + 0x14);

		iounmap(cpld);
		प्रणाली_rev = board_id & 0x7;
		lcd_select = board_id & 0x8;
		pr_info("LCD type: %s\n", lcd_select ? "Samsung" : "Toppoly");
		अगर (lcd_select && (प्रणाली_rev < 3))
			/* NOTICE valid LCD init sequence */
			gpio_request_one(GPIO75_MAGICIAN_SAMSUNG_POWER,
				GPIOF_OUT_INIT_LOW, "Samsung LCD Power");
		pxa_set_fb_info(शून्य,
			lcd_select ? &samsung_info : &toppoly_info);
	पूर्ण अन्यथा
		pr_err("LCD detection: CPLD mapping failed\n");

	pxa2xx_set_spi_info(2, &magician_spi_info);
	spi_रेजिस्टर_board_info(ARRAY_AND_SIZE(ads7846_spi_board_info));

	regulator_रेजिस्टर_always_on(0, "power", pwm_backlight_supply,
		ARRAY_SIZE(pwm_backlight_supply), 5000000);

	gpiod_add_lookup_table(&bq24022_gpiod_table);
	gpiod_add_lookup_table(&gpio_vbus_gpiod_table);
	platक्रमm_add_devices(ARRAY_AND_SIZE(devices));
पूर्ण

MACHINE_START(MAGICIAN, "HTC Magician")
	.atag_offset	= 0x100,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= MAGICIAN_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_machine	= magician_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
