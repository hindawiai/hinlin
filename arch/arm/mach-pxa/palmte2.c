<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hardware definitions क्रम Palm Tungsten|E2
 *
 * Author:
 *	Carlos Eduarकरो Medaglia Dyonisio <cadu@nerdfeliz.com>
 *
 * Reग_लिखो क्रम मुख्यline:
 *	Marek Vasut <marek.vasut@gmail.com>
 *
 * (find more info at www.hackndev.com)
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/input.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/wm97xx.h>
#समावेश <linux/घातer_supply.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa25x.h"
#समावेश <mach/audपन.स>
#समावेश "palmte2.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/asoc-palm27x.h>

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ palmte2_pin_config[] __initdata = अणु
	/* MMC */
	GPIO6_MMC_CLK,
	GPIO8_MMC_CS0,
	GPIO10_GPIO,	/* SD detect */
	GPIO55_GPIO,	/* SD घातer */
	GPIO51_GPIO,	/* SD r/o चयन */

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	/* PWM */
	GPIO16_PWM0_OUT,

	/* USB */
	GPIO15_GPIO,	/* usb detect */
	GPIO53_GPIO,	/* usb घातer */

	/* IrDA */
	GPIO48_GPIO,	/* ir disable */
	GPIO46_FICP_RXD,
	GPIO47_FICP_TXD,

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,

	/* GPIO KEYS */
	GPIO5_GPIO,	/* notes */
	GPIO7_GPIO,	/* tasks */
	GPIO11_GPIO,	/* calendar */
	GPIO13_GPIO,	/* contacts */
	GPIO14_GPIO,	/* center */
	GPIO19_GPIO,	/* left */
	GPIO20_GPIO,	/* right */
	GPIO21_GPIO,	/* करोwn */
	GPIO22_GPIO,	/* up */

	/* MISC */
	GPIO1_RST,	/* reset */
	GPIO4_GPIO,	/* Hotsync button */
	GPIO9_GPIO,	/* घातer detect */
	GPIO15_GPIO,	/* earphone detect */
	GPIO37_GPIO,	/* LCD घातer */
	GPIO56_GPIO,	/* Backlight घातer */
पूर्ण;

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
अटल काष्ठा pxamci_platक्रमm_data palmte2_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table palmte2_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTE2_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTE2_SD_READONLY,
			    "wp", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTE2_SD_POWER,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
/******************************************************************************
 * GPIO keys
 ******************************************************************************/
अटल काष्ठा gpio_keys_button palmte2_pxa_buttons[] = अणु
	अणुKEY_F1,	GPIO_NR_PALMTE2_KEY_CONTACTS,	1, "Contacts" पूर्ण,
	अणुKEY_F2,	GPIO_NR_PALMTE2_KEY_CALENDAR,	1, "Calendar" पूर्ण,
	अणुKEY_F3,	GPIO_NR_PALMTE2_KEY_TASKS,	1, "Tasks" पूर्ण,
	अणुKEY_F4,	GPIO_NR_PALMTE2_KEY_NOTES,	1, "Notes" पूर्ण,
	अणुKEY_ENTER,	GPIO_NR_PALMTE2_KEY_CENTER,	1, "Center" पूर्ण,
	अणुKEY_LEFT,	GPIO_NR_PALMTE2_KEY_LEFT,	1, "Left" पूर्ण,
	अणुKEY_RIGHT,	GPIO_NR_PALMTE2_KEY_RIGHT,	1, "Right" पूर्ण,
	अणुKEY_DOWN,	GPIO_NR_PALMTE2_KEY_DOWN,	1, "Down" पूर्ण,
	अणुKEY_UP,	GPIO_NR_PALMTE2_KEY_UP,		1, "Up" पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data palmte2_pxa_keys_data = अणु
	.buttons	= palmte2_pxa_buttons,
	.nbuttons	= ARRAY_SIZE(palmte2_pxa_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device palmte2_pxa_keys = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &palmte2_pxa_keys_data,
	पूर्ण,
पूर्ण;
#पूर्ण_अगर

/******************************************************************************
 * Backlight
 ******************************************************************************/
अटल काष्ठा pwm_lookup palmte2_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa25x-pwm.0", 0, "pwm-backlight.0", शून्य,
		   PALMTE2_PERIOD_NS, PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा gpio palmte_bl_gpios[] = अणु
	अणु GPIO_NR_PALMTE2_BL_POWER, GPIOF_INIT_LOW, "Backlight power" पूर्ण,
	अणु GPIO_NR_PALMTE2_LCD_POWER, GPIOF_INIT_LOW, "LCD power" पूर्ण,
पूर्ण;

अटल पूर्णांक palmte2_backlight_init(काष्ठा device *dev)
अणु
	वापस gpio_request_array(ARRAY_AND_SIZE(palmte_bl_gpios));
पूर्ण

अटल पूर्णांक palmte2_backlight_notअगरy(काष्ठा device *dev, पूर्णांक brightness)
अणु
	gpio_set_value(GPIO_NR_PALMTE2_BL_POWER, brightness);
	gpio_set_value(GPIO_NR_PALMTE2_LCD_POWER, brightness);
	वापस brightness;
पूर्ण

अटल व्योम palmte2_backlight_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त_array(ARRAY_AND_SIZE(palmte_bl_gpios));
पूर्ण

अटल काष्ठा platक्रमm_pwm_backlight_data palmte2_backlight_data = अणु
	.max_brightness	= PALMTE2_MAX_INTENSITY,
	.dft_brightness	= PALMTE2_MAX_INTENSITY,
	.init		= palmte2_backlight_init,
	.notअगरy		= palmte2_backlight_notअगरy,
	.निकास		= palmte2_backlight_निकास,
पूर्ण;

अटल काष्ठा platक्रमm_device palmte2_backlight = अणु
	.name	= "pwm-backlight",
	.dev	= अणु
		.parent		= &pxa25x_device_pwm0.dev,
		.platक्रमm_data	= &palmte2_backlight_data,
	पूर्ण,
पूर्ण;

/******************************************************************************
 * IrDA
 ******************************************************************************/
अटल काष्ठा pxaficp_platक्रमm_data palmte2_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= GPIO_NR_PALMTE2_IR_DISABLE,
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
पूर्ण;

/******************************************************************************
 * UDC
 ******************************************************************************/
अटल काष्ठा gpiod_lookup_table palmte2_udc_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTE2_USB_DETECT_N,
			    "vbus", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTE2_USB_PULLUP,
			    "pullup", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device palmte2_gpio_vbus = अणु
	.name	= "gpio-vbus",
	.id	= -1,
पूर्ण;

/******************************************************************************
 * Power supply
 ******************************************************************************/
अटल पूर्णांक घातer_supply_init(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = gpio_request(GPIO_NR_PALMTE2_POWER_DETECT, "CABLE_STATE_AC");
	अगर (ret)
		जाओ err1;
	ret = gpio_direction_input(GPIO_NR_PALMTE2_POWER_DETECT);
	अगर (ret)
		जाओ err2;

	वापस 0;

err2:
	gpio_मुक्त(GPIO_NR_PALMTE2_POWER_DETECT);
err1:
	वापस ret;
पूर्ण

अटल पूर्णांक palmte2_is_ac_online(व्योम)
अणु
	वापस gpio_get_value(GPIO_NR_PALMTE2_POWER_DETECT);
पूर्ण

अटल व्योम घातer_supply_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(GPIO_NR_PALMTE2_POWER_DETECT);
पूर्ण

अटल अक्षर *palmte2_supplicants[] = अणु
	"main-battery",
पूर्ण;

अटल काष्ठा pda_घातer_pdata घातer_supply_info = अणु
	.init            = घातer_supply_init,
	.is_ac_online    = palmte2_is_ac_online,
	.निकास            = घातer_supply_निकास,
	.supplied_to     = palmte2_supplicants,
	.num_supplicants = ARRAY_SIZE(palmte2_supplicants),
पूर्ण;

अटल काष्ठा platक्रमm_device घातer_supply = अणु
	.name = "pda-power",
	.id   = -1,
	.dev  = अणु
		.platक्रमm_data = &घातer_supply_info,
	पूर्ण,
पूर्ण;

/******************************************************************************
 * WM97xx audio, battery
 ******************************************************************************/
अटल काष्ठा wm97xx_batt_pdata palmte2_batt_pdata = अणु
	.batt_aux	= WM97XX_AUX_ID3,
	.temp_aux	= WM97XX_AUX_ID2,
	.max_voltage	= PALMTE2_BAT_MAX_VOLTAGE,
	.min_voltage	= PALMTE2_BAT_MIN_VOLTAGE,
	.batt_mult	= 1000,
	.batt_भाग	= 414,
	.temp_mult	= 1,
	.temp_भाग	= 1,
	.batt_tech	= POWER_SUPPLY_TECHNOLOGY_LIPO,
	.batt_name	= "main-batt",
पूर्ण;

अटल काष्ठा wm97xx_pdata palmte2_wm97xx_pdata = अणु
	.batt_pdata	= &palmte2_batt_pdata,
पूर्ण;

अटल pxa2xx_audio_ops_t palmte2_ac97_pdata = अणु
	.codec_pdata	= अणु &palmte2_wm97xx_pdata, पूर्ण,
पूर्ण;

अटल काष्ठा palm27x_asoc_info palmte2_asoc_pdata = अणु
	.jack_gpio	= GPIO_NR_PALMTE2_EARPHONE_DETECT,
पूर्ण;

अटल काष्ठा platक्रमm_device palmte2_asoc = अणु
	.name = "palm27x-asoc",
	.id   = -1,
	.dev  = अणु
		.platक्रमm_data = &palmte2_asoc_pdata,
	पूर्ण,
पूर्ण;

/******************************************************************************
 * Framebuffer
 ******************************************************************************/
अटल काष्ठा pxafb_mode_info palmte2_lcd_modes[] = अणु
अणु
	.pixघड़ी	= 77757,
	.xres		= 320,
	.yres		= 320,
	.bpp		= 16,

	.left_margin	= 28,
	.right_margin	= 7,
	.upper_margin	= 7,
	.lower_margin	= 5,

	.hsync_len	= 4,
	.vsync_len	= 1,
पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info palmte2_lcd_screen = अणु
	.modes		= palmte2_lcd_modes,
	.num_modes	= ARRAY_SIZE(palmte2_lcd_modes),
	.lcd_conn	= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
	&palmte2_pxa_keys,
#पूर्ण_अगर
	&palmte2_backlight,
	&घातer_supply,
	&palmte2_asoc,
	&palmte2_gpio_vbus,
पूर्ण;

/* setup udc GPIOs initial state */
अटल व्योम __init palmte2_udc_init(व्योम)
अणु
	अगर (!gpio_request(GPIO_NR_PALMTE2_USB_PULLUP, "UDC Vbus")) अणु
		gpio_direction_output(GPIO_NR_PALMTE2_USB_PULLUP, 1);
		gpio_मुक्त(GPIO_NR_PALMTE2_USB_PULLUP);
	पूर्ण
पूर्ण

अटल व्योम __init palmte2_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(palmte2_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	pxa_set_fb_info(शून्य, &palmte2_lcd_screen);
	gpiod_add_lookup_table(&palmte2_mci_gpio_table);
	pxa_set_mci_info(&palmte2_mci_platक्रमm_data);
	palmte2_udc_init();
	pxa_set_ac97_info(&palmte2_ac97_pdata);
	pxa_set_ficp_info(&palmte2_ficp_platक्रमm_data);

	pwm_add_table(palmte2_pwm_lookup, ARRAY_SIZE(palmte2_pwm_lookup));
	gpiod_add_lookup_table(&palmte2_udc_gpiod_table);
	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
पूर्ण

MACHINE_START(PALMTE2, "Palm Tungsten|E2")
	.atag_offset	= 0x100,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= palmte2_init,
	.restart	= pxa_restart,
MACHINE_END
