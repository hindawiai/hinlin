<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hardware definitions क्रम Palm Treo smartphones
 *
 * currently supported:
 *     Palm Treo 680 (GSM)
 *     Palm Centro 685 (GSM)
 *
 * Author:     Tomas Cech <sleep_walker@suse.cz>
 *
 * (find more info at www.hackndev.com)
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/memblock.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/w1-gpपन.स>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa27x.h"
#समावेश "pxa27x-udc.h"
#समावेश <mach/audपन.स>
#समावेश "palmtreo.h"
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <mach/pxa2xx-regs.h>
#समावेश <linux/platक्रमm_data/asoc-palm27x.h>
#समावेश <linux/platक्रमm_data/media/camera-pxa.h>
#समावेश "palm27x.h"

#समावेश <sound/pxa2xx-lib.h>

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ treo_pin_config[] __initdata = अणु
	/* MMC */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO113_GPIO,				/* SD detect */

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO89_AC97_SYSCLK,
	GPIO95_AC97_nRESET,

	/* IrDA */
	GPIO46_FICP_RXD,
	GPIO47_FICP_TXD,

	/* PWM */
	GPIO16_PWM0_OUT,

	/* USB */
	GPIO1_GPIO | WAKEUP_ON_EDGE_BOTH,	/* usb detect */

	/* MATRIX KEYPAD */
	GPIO101_KP_MKIN_1,
	GPIO102_KP_MKIN_2,
	GPIO97_KP_MKIN_3,
	GPIO98_KP_MKIN_4,
	GPIO91_KP_MKIN_6,
	GPIO13_KP_MKIN_7,
	GPIO103_KP_MKOUT_0 | MFP_LPM_DRIVE_HIGH,
	GPIO104_KP_MKOUT_1,
	GPIO105_KP_MKOUT_2,
	GPIO106_KP_MKOUT_3,
	GPIO107_KP_MKOUT_4,
	GPIO108_KP_MKOUT_5,
	GPIO96_KP_MKOUT_6,
	GPIO93_KP_DKIN_0 | WAKEUP_ON_LEVEL_HIGH,	/* Hotsync button */

	/* Quick Capture Interface */
	GPIO84_CIF_FV,
	GPIO85_CIF_LV,
	GPIO53_CIF_MCLK,
	GPIO54_CIF_PCLK,
	GPIO81_CIF_DD_0,
	GPIO55_CIF_DD_1,
	GPIO51_CIF_DD_2,
	GPIO50_CIF_DD_3,
	GPIO52_CIF_DD_4,
	GPIO48_CIF_DD_5,
	GPIO17_CIF_DD_6,
	GPIO12_CIF_DD_7,

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* GSM */
	GPIO14_GPIO | WAKEUP_ON_EDGE_BOTH,	/* GSM host wake up */
	GPIO34_FFUART_RXD,
	GPIO35_FFUART_CTS,
	GPIO39_FFUART_TXD,
	GPIO41_FFUART_RTS,

	/* MISC. */
	GPIO0_GPIO | WAKEUP_ON_EDGE_BOTH,	/* बाह्यal घातer detect */
	GPIO15_GPIO | WAKEUP_ON_EDGE_BOTH,	/* silent चयन */
	GPIO116_GPIO,				/* headphone detect */
	GPIO11_GPIO | WAKEUP_ON_EDGE_BOTH,	/* bluetooth host wake up */
पूर्ण;

#अगर_घोषित CONFIG_MACH_TREO680
अटल अचिन्हित दीर्घ treo680_pin_config[] __initdata = अणु
	GPIO33_GPIO,    /* SD पढ़ो only */

	/* MATRIX KEYPAD - dअगरferent wake up source */
	GPIO100_KP_MKIN_0 | WAKEUP_ON_LEVEL_HIGH,
	GPIO99_KP_MKIN_5,

	/* LCD... L_BIAS alt fn not configured on Treo680; is GPIO instead */
	GPIOxx_LCD_16BPP,
	GPIO74_LCD_FCLK,
	GPIO75_LCD_LCLK,
	GPIO76_LCD_PCLK,
पूर्ण;
#पूर्ण_अगर /* CONFIG_MACH_TREO680 */

#अगर_घोषित CONFIG_MACH_CENTRO
अटल अचिन्हित दीर्घ centro685_pin_config[] __initdata = अणु
	/* Bluetooth attached to BT UART*/
	MFP_CFG_OUT(GPIO80, AF0, DRIVE_LOW),    /* घातer: LOW = off */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,

	/* MATRIX KEYPAD - dअगरferent wake up source */
	GPIO100_KP_MKIN_0,
	GPIO99_KP_MKIN_5 | WAKEUP_ON_LEVEL_HIGH,

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,
पूर्ण;
#पूर्ण_अगर /* CONFIG_MACH_CENTRO */

/******************************************************************************
 * GPIO keyboard
 ******************************************************************************/
#अगर IS_ENABLED(CONFIG_KEYBOARD_PXA27x)
अटल स्थिर अचिन्हित पूर्णांक treo680_matrix_keys[] = अणु
	KEY(0, 0, KEY_F8),		/* Red/Off/Power */
	KEY(0, 1, KEY_LEFT),
	KEY(0, 2, KEY_LEFTCTRL),	/* Alternate */
	KEY(0, 3, KEY_L),
	KEY(0, 4, KEY_A),
	KEY(0, 5, KEY_Q),
	KEY(0, 6, KEY_P),

	KEY(1, 0, KEY_RIGHTCTRL),	/* Menu */
	KEY(1, 1, KEY_RIGHT),
	KEY(1, 2, KEY_LEFTSHIFT),	/* Left shअगरt */
	KEY(1, 3, KEY_Z),
	KEY(1, 4, KEY_S),
	KEY(1, 5, KEY_W),

	KEY(2, 0, KEY_F1),		/* Phone */
	KEY(2, 1, KEY_UP),
	KEY(2, 2, KEY_0),
	KEY(2, 3, KEY_X),
	KEY(2, 4, KEY_D),
	KEY(2, 5, KEY_E),

	KEY(3, 0, KEY_F10),		/* Calendar */
	KEY(3, 1, KEY_DOWN),
	KEY(3, 2, KEY_SPACE),
	KEY(3, 3, KEY_C),
	KEY(3, 4, KEY_F),
	KEY(3, 5, KEY_R),

	KEY(4, 0, KEY_F12),		/* Mail */
	KEY(4, 1, KEY_KPENTER),
	KEY(4, 2, KEY_RIGHTALT),	/* Alt */
	KEY(4, 3, KEY_V),
	KEY(4, 4, KEY_G),
	KEY(4, 5, KEY_T),

	KEY(5, 0, KEY_F9),		/* Home */
	KEY(5, 1, KEY_PAGEUP),		/* Side up */
	KEY(5, 2, KEY_DOT),
	KEY(5, 3, KEY_B),
	KEY(5, 4, KEY_H),
	KEY(5, 5, KEY_Y),

	KEY(6, 0, KEY_TAB),		/* Side Activate */
	KEY(6, 1, KEY_PAGEDOWN),	/* Side करोwn */
	KEY(6, 2, KEY_ENTER),
	KEY(6, 3, KEY_N),
	KEY(6, 4, KEY_J),
	KEY(6, 5, KEY_U),

	KEY(7, 0, KEY_F6),		/* Green/Call */
	KEY(7, 1, KEY_O),
	KEY(7, 2, KEY_BACKSPACE),
	KEY(7, 3, KEY_M),
	KEY(7, 4, KEY_K),
	KEY(7, 5, KEY_I),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक centro_matrix_keys[] = अणु
	KEY(0, 0, KEY_F9),		/* Home */
	KEY(0, 1, KEY_LEFT),
	KEY(0, 2, KEY_LEFTCTRL),	/* Alternate */
	KEY(0, 3, KEY_L),
	KEY(0, 4, KEY_A),
	KEY(0, 5, KEY_Q),
	KEY(0, 6, KEY_P),

	KEY(1, 0, KEY_RIGHTCTRL),	/* Menu */
	KEY(1, 1, KEY_RIGHT),
	KEY(1, 2, KEY_LEFTSHIFT),	/* Left shअगरt */
	KEY(1, 3, KEY_Z),
	KEY(1, 4, KEY_S),
	KEY(1, 5, KEY_W),

	KEY(2, 0, KEY_F1),		/* Phone */
	KEY(2, 1, KEY_UP),
	KEY(2, 2, KEY_0),
	KEY(2, 3, KEY_X),
	KEY(2, 4, KEY_D),
	KEY(2, 5, KEY_E),

	KEY(3, 0, KEY_F10),		/* Calendar */
	KEY(3, 1, KEY_DOWN),
	KEY(3, 2, KEY_SPACE),
	KEY(3, 3, KEY_C),
	KEY(3, 4, KEY_F),
	KEY(3, 5, KEY_R),

	KEY(4, 0, KEY_F12),		/* Mail */
	KEY(4, 1, KEY_KPENTER),
	KEY(4, 2, KEY_RIGHTALT),	/* Alt */
	KEY(4, 3, KEY_V),
	KEY(4, 4, KEY_G),
	KEY(4, 5, KEY_T),

	KEY(5, 0, KEY_F8),		/* Red/Off/Power */
	KEY(5, 1, KEY_PAGEUP),		/* Side up */
	KEY(5, 2, KEY_DOT),
	KEY(5, 3, KEY_B),
	KEY(5, 4, KEY_H),
	KEY(5, 5, KEY_Y),

	KEY(6, 0, KEY_TAB),		/* Side Activate */
	KEY(6, 1, KEY_PAGEDOWN),	/* Side करोwn */
	KEY(6, 2, KEY_ENTER),
	KEY(6, 3, KEY_N),
	KEY(6, 4, KEY_J),
	KEY(6, 5, KEY_U),

	KEY(7, 0, KEY_F6),		/* Green/Call */
	KEY(7, 1, KEY_O),
	KEY(7, 2, KEY_BACKSPACE),
	KEY(7, 3, KEY_M),
	KEY(7, 4, KEY_K),
	KEY(7, 5, KEY_I),
पूर्ण;

अटल काष्ठा matrix_keymap_data treo680_matrix_keymap_data = अणु
	.keymap			= treo680_matrix_keys,
	.keymap_size		= ARRAY_SIZE(treo680_matrix_keys),
पूर्ण;

अटल काष्ठा matrix_keymap_data centro_matrix_keymap_data = अणु
	.keymap			= centro_matrix_keys,
	.keymap_size		= ARRAY_SIZE(centro_matrix_keys),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data treo680_keypad_pdata = अणु
	.matrix_key_rows	= 8,
	.matrix_key_cols	= 7,
	.matrix_keymap_data	= &treo680_matrix_keymap_data,
	.direct_key_map		= अणु KEY_CONNECT पूर्ण,
	.direct_key_num		= 1,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init palmtreo_kpc_init(व्योम)
अणु
	अटल काष्ठा pxa27x_keypad_platक्रमm_data *data = &treo680_keypad_pdata;

	अगर (machine_is_centro())
		data->matrix_keymap_data = &centro_matrix_keymap_data;

	pxa_set_keypad_info(&treo680_keypad_pdata);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtreo_kpc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB host
 ******************************************************************************/
#अगर IS_ENABLED(CONFIG_USB_OHCI_HCD)
अटल काष्ठा pxaohci_platक्रमm_data treo680_ohci_info = अणु
	.port_mode    = PMM_PERPORT_MODE,
	.flags        = ENABLE_PORT1 | ENABLE_PORT3,
	.घातer_budget = 0,
पूर्ण;

अटल व्योम __init palmtreo_uhc_init(व्योम)
अणु
	अगर (machine_is_treo680())
		pxa_set_ohci_info(&treo680_ohci_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtreo_uhc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Vibra and LEDs
 ******************************************************************************/
अटल काष्ठा gpio_led treo680_gpio_leds[] = अणु
	अणु
		.name			= "treo680:vibra:vibra",
		.शेष_trigger	= "none",
		.gpio			= GPIO_NR_TREO680_VIBRATE_EN,
	पूर्ण,
	अणु
		.name			= "treo680:green:led",
		.शेष_trigger	= "mmc0",
		.gpio			= GPIO_NR_TREO_GREEN_LED,
	पूर्ण,
	अणु
		.name			= "treo680:white:keybbl",
		.शेष_trigger	= "none",
		.gpio			= GPIO_NR_TREO680_KEYB_BL,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data treo680_gpio_led_info = अणु
	.leds		= treo680_gpio_leds,
	.num_leds	= ARRAY_SIZE(treo680_gpio_leds),
पूर्ण;

अटल काष्ठा gpio_led centro_gpio_leds[] = अणु
	अणु
		.name			= "centro:vibra:vibra",
		.शेष_trigger	= "none",
		.gpio			= GPIO_NR_CENTRO_VIBRATE_EN,
	पूर्ण,
	अणु
		.name			= "centro:green:led",
		.शेष_trigger	= "mmc0",
		.gpio			= GPIO_NR_TREO_GREEN_LED,
	पूर्ण,
	अणु
		.name			= "centro:white:keybbl",
		.शेष_trigger	= "none",
		.active_low		= 1,
		.gpio			= GPIO_NR_CENTRO_KEYB_BL,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data centro_gpio_led_info = अणु
	.leds		= centro_gpio_leds,
	.num_leds	= ARRAY_SIZE(centro_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device palmtreo_leds = अणु
	.name   = "leds-gpio",
	.id     = -1,
पूर्ण;

अटल व्योम __init palmtreo_leds_init(व्योम)
अणु
	अगर (machine_is_centro())
		palmtreo_leds.dev.platक्रमm_data = &centro_gpio_led_info;
	अन्यथा अगर (machine_is_treo680())
		palmtreo_leds.dev.platक्रमm_data = &treo680_gpio_led_info;

	platक्रमm_device_रेजिस्टर(&palmtreo_leds);
पूर्ण

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल व्योम __init treo_reserve(व्योम)
अणु
	memblock_reserve(0xa0000000, 0x1000);
	memblock_reserve(0xa2000000, 0x1000);
पूर्ण

अटल व्योम __init palmphone_common_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(treo_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	palm27x_pm_init(TREO_STR_BASE);
	palm27x_lcd_init(GPIO_NR_TREO_BL_POWER, &palm_320x320_new_lcd_mode);
	palm27x_udc_init(GPIO_NR_TREO_USB_DETECT, GPIO_NR_TREO_USB_PULLUP, 1);
	palm27x_irda_init(GPIO_NR_TREO_IR_EN);
	palm27x_ac97_init(-1, -1, -1, 95);
	palm27x_pwm_init(GPIO_NR_TREO_BL_POWER, -1);
	palm27x_घातer_init(GPIO_NR_TREO_POWER_DETECT, -1);
	palm27x_pmic_init();
	palmtreo_kpc_init();
	palmtreo_uhc_init();
	palmtreo_leds_init();
पूर्ण

#अगर_घोषित CONFIG_MACH_TREO680
व्योम __init treo680_gpio_init(व्योम)
अणु
	अचिन्हित पूर्णांक gpio;

	/* drive all three lcd gpios high initially */
	स्थिर अचिन्हित दीर्घ lcd_flags = GPIOF_INIT_HIGH | GPIOF_सूची_OUT;

	/*
	 * LCD GPIO initialization...
	 */

	/*
	 * This is likely the घातer to the lcd.  Toggling it low/high appears to
	 * turn the lcd off/on.  Can be toggled after lcd is initialized without
	 * any apparent adverse effects to the lcd operation.  Note that this
	 * gpio line is used by the lcd controller as the L_BIAS संकेत, but
	 * treo680 configures it as gpio.
	 */
	gpio = GPIO_NR_TREO680_LCD_POWER;
	अगर (gpio_request_one(gpio, lcd_flags, "LCD power") < 0)
		जाओ fail;

	/*
	 * These two are called "enables", क्रम lack of a better understanding.
	 * If either of these are toggled after the lcd is initialized, the
	 * image becomes degraded.  N.B. The IPL shipped with the treo
	 * configures GPIO_NR_TREO680_LCD_EN_N as output and drives it high.  If
	 * the IPL is ever reprogrammed, this initialization may be need to be
	 * revisited.
	 */
	gpio = GPIO_NR_TREO680_LCD_EN;
	अगर (gpio_request_one(gpio, lcd_flags, "LCD enable") < 0)
		जाओ fail;
	gpio = GPIO_NR_TREO680_LCD_EN_N;
	अगर (gpio_request_one(gpio, lcd_flags, "LCD enable_n") < 0)
		जाओ fail;

	/* driving this low turns LCD on */
	gpio_set_value(GPIO_NR_TREO680_LCD_EN_N, 0);

	वापस;
 fail:
	pr_err("gpio %d initialization failed\n", gpio);
	gpio_मुक्त(GPIO_NR_TREO680_LCD_POWER);
	gpio_मुक्त(GPIO_NR_TREO680_LCD_EN);
	gpio_मुक्त(GPIO_NR_TREO680_LCD_EN_N);
पूर्ण

अटल काष्ठा gpiod_lookup_table treo680_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_TREO_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_TREO680_SD_READONLY,
			    "wp", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_TREO680_SD_POWER,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init treo680_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(treo680_pin_config));
	palmphone_common_init();
	treo680_gpio_init();
	palm27x_mmc_init(&treo680_mci_gpio_table);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_CENTRO

अटल काष्ठा gpiod_lookup_table centro685_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_TREO_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_CENTRO_SD_POWER,
			    "power", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init centro_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(centro685_pin_config));
	palmphone_common_init();
	palm27x_mmc_init(&centro685_mci_gpio_table);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_TREO680
MACHINE_START(TREO680, "Palm Treo 680")
	.atag_offset    = 0x100,
	.map_io         = pxa27x_map_io,
	.reserve	= treo_reserve,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq       = pxa27x_init_irq,
	.handle_irq       = pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine   = treo680_init,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_CENTRO
MACHINE_START(CENTRO, "Palm Centro 685")
	.atag_offset    = 0x100,
	.map_io         = pxa27x_map_io,
	.reserve	= treo_reserve,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq       = pxa27x_init_irq,
	.handle_irq       = pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= centro_init,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर
