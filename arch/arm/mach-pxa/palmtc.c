<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/palmtc.c
 *
 * Support क्रम the Palm Tungsten|C
 *
 * Author:	Marek Vasut <marek.vasut@gmail.com>
 *
 * Based on work of:
 *		Petr Blaha <p3t3@centrum.cz>
 *		Chetan S. Kumar <shivakumar.chetan@gmail.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/input.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/ucb1400.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/mtd/physmap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>

#समावेश "pxa25x.h"
#समावेश <mach/audपन.स>
#समावेश <mach/palmtc.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश "udc.h"

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ palmtc_pin_config[] __initdata = अणु
	/* MMC */
	GPIO6_MMC_CLK,
	GPIO8_MMC_CS0,
	GPIO12_GPIO,	/* detect */
	GPIO32_GPIO,	/* घातer */
	GPIO54_GPIO,	/* r/o चयन */

	/* PCMCIA */
	GPIO52_nPCE_1,
	GPIO53_nPCE_2,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO49_nPWE,
	GPIO48_nPOE,
	GPIO52_nPCE_1,
	GPIO53_nPCE_2,
	GPIO57_nIOIS16,
	GPIO56_nPWAIT,

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	/* IrDA */
	GPIO45_GPIO,	/* ir disable */
	GPIO46_FICP_RXD,
	GPIO47_FICP_TXD,

	/* PWM */
	GPIO17_PWM1_OUT,

	/* USB */
	GPIO4_GPIO,	/* detect */
	GPIO36_GPIO,	/* pullup */

	/* LCD */
	GPIOxx_LCD_TFT_16BPP,

	/* MATRIX KEYPAD */
	GPIO0_GPIO | WAKEUP_ON_EDGE_BOTH,	/* in 0 */
	GPIO9_GPIO | WAKEUP_ON_EDGE_BOTH,	/* in 1 */
	GPIO10_GPIO | WAKEUP_ON_EDGE_BOTH,	/* in 2 */
	GPIO11_GPIO | WAKEUP_ON_EDGE_BOTH,	/* in 3 */
	GPIO18_GPIO | MFP_LPM_DRIVE_LOW,	/* out 0 */
	GPIO19_GPIO | MFP_LPM_DRIVE_LOW,	/* out 1 */
	GPIO20_GPIO | MFP_LPM_DRIVE_LOW,	/* out 2 */
	GPIO21_GPIO | MFP_LPM_DRIVE_LOW,	/* out 3 */
	GPIO22_GPIO | MFP_LPM_DRIVE_LOW,	/* out 4 */
	GPIO23_GPIO | MFP_LPM_DRIVE_LOW,	/* out 5 */
	GPIO24_GPIO | MFP_LPM_DRIVE_LOW,	/* out 6 */
	GPIO25_GPIO | MFP_LPM_DRIVE_LOW,	/* out 7 */
	GPIO26_GPIO | MFP_LPM_DRIVE_LOW,	/* out 8 */
	GPIO27_GPIO | MFP_LPM_DRIVE_LOW,	/* out 9 */
	GPIO79_GPIO | MFP_LPM_DRIVE_LOW,	/* out 10 */
	GPIO80_GPIO | MFP_LPM_DRIVE_LOW,	/* out 11 */

	/* PXA GPIO KEYS */
	GPIO7_GPIO | WAKEUP_ON_EDGE_BOTH,	/* hotsync button on cradle */

	/* MISC */
	GPIO1_RST,	/* reset */
	GPIO2_GPIO,	/* earphone detect */
	GPIO16_GPIO,	/* backlight चयन */
पूर्ण;

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
अटल काष्ठा pxamci_platक्रमm_data palmtc_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.detect_delay_ms	= 200,
पूर्ण;

अटल काष्ठा gpiod_lookup_table palmtc_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTC_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTC_SD_READONLY,
			    "wp", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTC_SD_POWER,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmtc_mmc_init(व्योम)
अणु
	gpiod_add_lookup_table(&palmtc_mci_gpio_table);
	pxa_set_mci_info(&palmtc_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_mmc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keys
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
अटल काष्ठा gpio_keys_button palmtc_pxa_buttons[] = अणु
	अणुKEY_F8, GPIO_NR_PALMTC_HOTSYNC_BUTTON, 1, "HotSync Button", EV_KEY, 1पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data palmtc_pxa_keys_data = अणु
	.buttons	= palmtc_pxa_buttons,
	.nbuttons	= ARRAY_SIZE(palmtc_pxa_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device palmtc_pxa_keys = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &palmtc_pxa_keys_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmtc_keys_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmtc_pxa_keys);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_keys_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Backlight
 ******************************************************************************/
#अगर defined(CONFIG_BACKLIGHT_PWM) || defined(CONFIG_BACKLIGHT_PWM_MODULE)

अटल काष्ठा gpiod_lookup_table palmtc_pwm_bl_gpio_table = अणु
	.dev_id = "pwm-backlight.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTC_BL_POWER,
			    "enable", GPIO_ACTIVE_HIGH),
	पूर्ण,
पूर्ण;

अटल काष्ठा pwm_lookup palmtc_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa25x-pwm.1", 0, "pwm-backlight.0", शून्य, PALMTC_PERIOD_NS,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data palmtc_backlight_data = अणु
	.max_brightness	= PALMTC_MAX_INTENSITY,
	.dft_brightness	= PALMTC_MAX_INTENSITY,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtc_backlight = अणु
	.name	= "pwm-backlight",
	.dev	= अणु
		.parent		= &pxa25x_device_pwm1.dev,
		.platक्रमm_data	= &palmtc_backlight_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmtc_pwm_init(व्योम)
अणु
	gpiod_add_lookup_table(&palmtc_pwm_bl_gpio_table);
	pwm_add_table(palmtc_pwm_lookup, ARRAY_SIZE(palmtc_pwm_lookup));
	platक्रमm_device_रेजिस्टर(&palmtc_backlight);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_pwm_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * IrDA
 ******************************************************************************/
#अगर defined(CONFIG_IRDA) || defined(CONFIG_IRDA_MODULE)
अटल काष्ठा pxaficp_platक्रमm_data palmtc_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= GPIO_NR_PALMTC_IR_DISABLE,
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
पूर्ण;

अटल व्योम __init palmtc_irda_init(व्योम)
अणु
	pxa_set_ficp_info(&palmtc_ficp_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_irda_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Keyboard
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_MATRIX) || defined(CONFIG_KEYBOARD_MATRIX_MODULE)
अटल स्थिर uपूर्णांक32_t palmtc_matrix_keys[] = अणु
	KEY(0, 0, KEY_F1),
	KEY(0, 1, KEY_X),
	KEY(0, 2, KEY_POWER),
	KEY(0, 3, KEY_TAB),
	KEY(0, 4, KEY_A),
	KEY(0, 5, KEY_Q),
	KEY(0, 6, KEY_LEFTSHIFT),
	KEY(0, 7, KEY_Z),
	KEY(0, 8, KEY_S),
	KEY(0, 9, KEY_W),
	KEY(0, 10, KEY_E),
	KEY(0, 11, KEY_UP),

	KEY(1, 0, KEY_F2),
	KEY(1, 1, KEY_DOWN),
	KEY(1, 3, KEY_D),
	KEY(1, 4, KEY_C),
	KEY(1, 5, KEY_F),
	KEY(1, 6, KEY_R),
	KEY(1, 7, KEY_SPACE),
	KEY(1, 8, KEY_V),
	KEY(1, 9, KEY_G),
	KEY(1, 10, KEY_T),
	KEY(1, 11, KEY_LEFT),

	KEY(2, 0, KEY_F3),
	KEY(2, 1, KEY_LEFTCTRL),
	KEY(2, 3, KEY_H),
	KEY(2, 4, KEY_Y),
	KEY(2, 5, KEY_N),
	KEY(2, 6, KEY_J),
	KEY(2, 7, KEY_U),
	KEY(2, 8, KEY_M),
	KEY(2, 9, KEY_K),
	KEY(2, 10, KEY_I),
	KEY(2, 11, KEY_RIGHT),

	KEY(3, 0, KEY_F4),
	KEY(3, 1, KEY_ENTER),
	KEY(3, 3, KEY_DOT),
	KEY(3, 4, KEY_L),
	KEY(3, 5, KEY_O),
	KEY(3, 6, KEY_LEFTALT),
	KEY(3, 7, KEY_ENTER),
	KEY(3, 8, KEY_BACKSPACE),
	KEY(3, 9, KEY_P),
	KEY(3, 10, KEY_B),
	KEY(3, 11, KEY_FN),
पूर्ण;

स्थिर काष्ठा matrix_keymap_data palmtc_keymap_data = अणु
	.keymap			= palmtc_matrix_keys,
	.keymap_size		= ARRAY_SIZE(palmtc_matrix_keys),
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक palmtc_keypad_row_gpios[] = अणु
	0, 9, 10, 11
पूर्ण;

अटल स्थिर अचिन्हित पूर्णांक palmtc_keypad_col_gpios[] = अणु
	18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 79, 80
पूर्ण;

अटल काष्ठा matrix_keypad_platक्रमm_data palmtc_keypad_platक्रमm_data = अणु
	.keymap_data	= &palmtc_keymap_data,
	.row_gpios	= palmtc_keypad_row_gpios,
	.num_row_gpios	= ARRAY_SIZE(palmtc_keypad_row_gpios),
	.col_gpios	= palmtc_keypad_col_gpios,
	.num_col_gpios	= ARRAY_SIZE(palmtc_keypad_col_gpios),
	.active_low	= 1,

	.debounce_ms		= 20,
	.col_scan_delay_us	= 5,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtc_keyboard = अणु
	.name	= "matrix-keypad",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &palmtc_keypad_platक्रमm_data,
	पूर्ण,
पूर्ण;
अटल व्योम __init palmtc_mkp_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmtc_keyboard);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_mkp_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * UDC
 ******************************************************************************/
#अगर defined(CONFIG_USB_PXA25X)||defined(CONFIG_USB_PXA25X_MODULE)
अटल काष्ठा gpiod_lookup_table palmtc_udc_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTC_USB_DETECT_N,
			    "vbus", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO_NR_PALMTC_USB_POWER,
			    "pullup", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device palmtc_gpio_vbus = अणु
	.name	= "gpio-vbus",
	.id	= -1,
पूर्ण;

अटल व्योम __init palmtc_udc_init(व्योम)
अणु
	gpiod_add_lookup_table(&palmtc_udc_gpiod_table);
	platक्रमm_device_रेजिस्टर(&palmtc_gpio_vbus);
पूर्ण;
#अन्यथा
अटल अंतरभूत व्योम palmtc_udc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Touchscreen / Battery / GPIO-extender
 ******************************************************************************/
#अगर	defined(CONFIG_TOUCHSCREEN_UCB1400) || \
	defined(CONFIG_TOUCHSCREEN_UCB1400_MODULE)
अटल काष्ठा platक्रमm_device palmtc_ucb1400_device = अणु
	.name	= "ucb1400_core",
	.id	= -1,
पूर्ण;

अटल व्योम __init palmtc_ts_init(व्योम)
अणु
	pxa_set_ac97_info(शून्य);
	platक्रमm_device_रेजिस्टर(&palmtc_ucb1400_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_ts_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * LEDs
 ******************************************************************************/
#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
काष्ठा gpio_led palmtc_gpio_leds[] = अणु
अणु
	.name			= "palmtc:green:user",
	.शेष_trigger	= "none",
	.gpio			= GPIO_NR_PALMTC_LED_POWER,
	.active_low		= 1,
पूर्ण, अणु
	.name			= "palmtc:vibra:vibra",
	.शेष_trigger	= "none",
	.gpio			= GPIO_NR_PALMTC_VIBRA_POWER,
	.active_low		= 1,
पूर्ण

पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data palmtc_gpio_led_info = अणु
	.leds		= palmtc_gpio_leds,
	.num_leds	= ARRAY_SIZE(palmtc_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device palmtc_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &palmtc_gpio_led_info,
	पूर्ण
पूर्ण;

अटल व्योम __init palmtc_leds_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmtc_leds);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_leds_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * NOR Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_PHYSMAP) || defined(CONFIG_MTD_PHYSMAP_MODULE)
अटल काष्ठा resource palmtc_flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_16M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा mtd_partition palmtc_flash_parts[] = अणु
	अणु
		.name	= "U-Boot Bootloader",
		.offset	= 0x0,
		.size	= 0x40000,
	पूर्ण,
	अणु
		.name	= "Linux Kernel",
		.offset	= 0x40000,
		.size	= 0x2c0000,
	पूर्ण,
	अणु
		.name	= "Filesystem",
		.offset	= 0x300000,
		.size	= 0xcc0000,
	पूर्ण,
	अणु
		.name	= "U-Boot Environment",
		.offset	= 0xfc0000,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data palmtc_flash_data = अणु
	.width		= 4,
	.parts		= palmtc_flash_parts,
	.nr_parts	= ARRAY_SIZE(palmtc_flash_parts),
पूर्ण;

अटल काष्ठा platक्रमm_device palmtc_flash = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.resource	= &palmtc_flash_resource,
	.num_resources	= 1,
	.dev = अणु
		.platक्रमm_data	= &palmtc_flash_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init palmtc_nor_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&palmtc_flash);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_nor_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Framebuffer
 ******************************************************************************/
#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pxafb_mode_info palmtc_lcd_modes[] = अणु
	अणु
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
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info palmtc_lcd_screen = अणु
	.modes			= palmtc_lcd_modes,
	.num_modes		= ARRAY_SIZE(palmtc_lcd_modes),
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल व्योम __init palmtc_lcd_init(व्योम)
अणु
	pxa_set_fb_info(शून्य, &palmtc_lcd_screen);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम palmtc_lcd_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल व्योम __init palmtc_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(palmtc_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	pxa_set_hwuart_info(शून्य);

	palmtc_mmc_init();
	palmtc_keys_init();
	palmtc_pwm_init();
	palmtc_irda_init();
	palmtc_mkp_init();
	palmtc_udc_init();
	palmtc_ts_init();
	palmtc_nor_init();
	palmtc_lcd_init();
	palmtc_leds_init();
पूर्ण;

MACHINE_START(PALMTC, "Palm Tungsten|C")
	.atag_offset 	= 0x100,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= palmtc_init,
	.restart	= pxa_restart,
MACHINE_END
