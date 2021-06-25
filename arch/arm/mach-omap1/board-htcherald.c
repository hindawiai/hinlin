<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * HTC Herald board configuration
 * Copyright (C) 2009 Cory Maccarrone <darkstar6262@gmail.com>
 * Copyright (C) 2009 Wing Linux
 *
 * Based on the board-htcwizard.c file from the linwizard project:
 * Copyright (C) 2006 Unai Uribarri
 * Copyright (C) 2008 linwizard.sourceक्रमge.net
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/input.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-gpपन.स>
#समावेश <linux/htcpld.h>
#समावेश <linux/leds.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/omapfb.h>
#समावेश <linux/platक्रमm_data/keypad-omap.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश <mach/omap7xx.h>
#समावेश "mmc.h"

#समावेश <mach/irqs.h>
#समावेश <mach/usb.h>

#समावेश "common.h"

/* LCD रेजिस्टर definition */
#घोषणा       OMAP_LCDC_CONTROL               (0xfffec000 + 0x00)
#घोषणा       OMAP_LCDC_STATUS                (0xfffec000 + 0x10)
#घोषणा       OMAP_DMA_LCD_CCR                (0xfffee300 + 0xc2)
#घोषणा       OMAP_DMA_LCD_CTRL               (0xfffee300 + 0xc4)
#घोषणा       OMAP_LCDC_CTRL_LCD_EN           (1 << 0)
#घोषणा       OMAP_LCDC_STAT_DONE             (1 << 0)

/* GPIO definitions क्रम the घातer button and keyboard slide चयन */
#घोषणा HTCHERALD_GPIO_POWER 139
#घोषणा HTCHERALD_GPIO_SLIDE 174
#घोषणा HTCHERALD_GIRQ_BTNS 141

/* GPIO definitions क्रम the touchscreen */
#घोषणा HTCHERALD_GPIO_TS 76

/* HTCPLD definitions */

/*
 * CPLD Logic
 *
 * Chip 3 - 0x03
 *
 * Function            7 6 5 4  3 2 1 0
 * ------------------------------------
 * DPAD light          x x x x  x x x 1
 * SoundDev            x x x x  1 x x x
 * Screen white        1 x x x  x x x x
 * MMC घातer on        x x x x  x 1 x x
 * Happy बार (n)     0 x x x  x 1 x x
 *
 * Chip 4 - 0x04
 *
 * Function            7 6 5 4  3 2 1 0
 * ------------------------------------
 * Keyboard light      x x x x  x x x 1
 * LCD Bright (4)      x x x x  x 1 1 x
 * LCD Bright (3)      x x x x  x 0 1 x
 * LCD Bright (2)      x x x x  x 1 0 x
 * LCD Bright (1)      x x x x  x 0 0 x
 * LCD Off             x x x x  0 x x x
 * LCD image (fb)      1 x x x  x x x x
 * LCD image (white)   0 x x x  x x x x
 * Caps lock LED       x x 1 x  x x x x
 *
 * Chip 5 - 0x05
 *
 * Function            7 6 5 4  3 2 1 0
 * ------------------------------------
 * Red (solid)         x x x x  x 1 x x
 * Red (flash)         x x x x  x x 1 x
 * Green (GSM flash)   x x x x  1 x x x
 * Green (GSM solid)   x x x 1  x x x x
 * Green (wअगरi flash)  x x 1 x  x x x x
 * Blue (bt flash)     x 1 x x  x x x x
 * DPAD Int Enable     1 x x x  x x x 0
 *
 * (Combinations of the above can be made क्रम dअगरferent colors.)
 * The direction pad पूर्णांकerrupt enable must be set each समय the
 * पूर्णांकerrupt is handled.
 *
 * Chip 6 - 0x06
 *
 * Function            7 6 5 4  3 2 1 0
 * ------------------------------------
 * Vibrator            x x x x  1 x x x
 * Alt LED             x x x 1  x x x x
 * Screen white        1 x x x  x x x x
 * Screen white        x x 1 x  x x x x
 * Screen white        x 0 x x  x x x x
 * Enable kbd dpad     x x x x  x x 0 x
 * Happy Times         0 1 0 x  x x 0 x
 */

/*
 * HTCPLD GPIO lines start 16 after OMAP_MAX_GPIO_LINES to account
 * क्रम the 16 MPUIO lines.
 */
#घोषणा HTCPLD_GPIO_START_OFFSET	(OMAP_MAX_GPIO_LINES + 16)
#घोषणा HTCPLD_IRQ(chip, offset)	(OMAP_IRQ_END + 8 * (chip) + (offset))
#घोषणा HTCPLD_BASE(chip, offset)	\
	(HTCPLD_GPIO_START_OFFSET + 8 * (chip) + (offset))

#घोषणा HTCPLD_GPIO_LED_DPAD		HTCPLD_BASE(0, 0)
#घोषणा HTCPLD_GPIO_LED_KBD		HTCPLD_BASE(1, 0)
#घोषणा HTCPLD_GPIO_LED_CAPS		HTCPLD_BASE(1, 5)
#घोषणा HTCPLD_GPIO_LED_RED_FLASH	HTCPLD_BASE(2, 1)
#घोषणा HTCPLD_GPIO_LED_RED_SOLID	HTCPLD_BASE(2, 2)
#घोषणा HTCPLD_GPIO_LED_GREEN_FLASH	HTCPLD_BASE(2, 3)
#घोषणा HTCPLD_GPIO_LED_GREEN_SOLID	HTCPLD_BASE(2, 4)
#घोषणा HTCPLD_GPIO_LED_WIFI		HTCPLD_BASE(2, 5)
#घोषणा HTCPLD_GPIO_LED_BT		HTCPLD_BASE(2, 6)
#घोषणा HTCPLD_GPIO_LED_VIBRATE		HTCPLD_BASE(3, 3)
#घोषणा HTCPLD_GPIO_LED_ALT		HTCPLD_BASE(3, 4)

#घोषणा HTCPLD_GPIO_RIGHT_KBD		HTCPLD_BASE(6, 7)
#घोषणा HTCPLD_GPIO_UP_KBD		HTCPLD_BASE(6, 6)
#घोषणा HTCPLD_GPIO_LEFT_KBD		HTCPLD_BASE(6, 5)
#घोषणा HTCPLD_GPIO_DOWN_KBD		HTCPLD_BASE(6, 4)

#घोषणा HTCPLD_GPIO_RIGHT_DPAD		HTCPLD_BASE(7, 7)
#घोषणा HTCPLD_GPIO_UP_DPAD		HTCPLD_BASE(7, 6)
#घोषणा HTCPLD_GPIO_LEFT_DPAD		HTCPLD_BASE(7, 5)
#घोषणा HTCPLD_GPIO_DOWN_DPAD		HTCPLD_BASE(7, 4)
#घोषणा HTCPLD_GPIO_ENTER_DPAD		HTCPLD_BASE(7, 3)

/*
 * The htcpld chip requires a gpio ग_लिखो to a specअगरic line
 * to re-enable पूर्णांकerrupts after one has occurred.
 */
#घोषणा HTCPLD_GPIO_INT_RESET_HI	HTCPLD_BASE(2, 7)
#घोषणा HTCPLD_GPIO_INT_RESET_LO	HTCPLD_BASE(2, 0)

/* Chip 5 */
#घोषणा HTCPLD_IRQ_RIGHT_KBD		HTCPLD_IRQ(0, 7)
#घोषणा HTCPLD_IRQ_UP_KBD		HTCPLD_IRQ(0, 6)
#घोषणा HTCPLD_IRQ_LEFT_KBD		HTCPLD_IRQ(0, 5)
#घोषणा HTCPLD_IRQ_DOWN_KBD		HTCPLD_IRQ(0, 4)

/* Chip 6 */
#घोषणा HTCPLD_IRQ_RIGHT_DPAD		HTCPLD_IRQ(1, 7)
#घोषणा HTCPLD_IRQ_UP_DPAD		HTCPLD_IRQ(1, 6)
#घोषणा HTCPLD_IRQ_LEFT_DPAD		HTCPLD_IRQ(1, 5)
#घोषणा HTCPLD_IRQ_DOWN_DPAD		HTCPLD_IRQ(1, 4)
#घोषणा HTCPLD_IRQ_ENTER_DPAD		HTCPLD_IRQ(1, 3)

/* Keyboard definition */

अटल स्थिर अचिन्हित पूर्णांक htc_herald_keymap[] = अणु
	KEY(0, 0, KEY_RECORD), /* Mail button */
	KEY(1, 0, KEY_CAMERA), /* Camera */
	KEY(2, 0, KEY_PHONE), /* Send key */
	KEY(3, 0, KEY_VOLUMEUP), /* Volume up */
	KEY(4, 0, KEY_F2),  /* Right bar (landscape) */
	KEY(5, 0, KEY_MAIL), /* Win key (portrait) */
	KEY(6, 0, KEY_सूचीECTORY), /* Right bar (protrait) */
	KEY(0, 1, KEY_LEFTCTRL), /* Winकरोws key */
	KEY(1, 1, KEY_COMMA),
	KEY(2, 1, KEY_M),
	KEY(3, 1, KEY_K),
	KEY(4, 1, KEY_SLASH), /* OK key */
	KEY(5, 1, KEY_I),
	KEY(6, 1, KEY_U),
	KEY(0, 2, KEY_LEFTALT),
	KEY(1, 2, KEY_TAB),
	KEY(2, 2, KEY_N),
	KEY(3, 2, KEY_J),
	KEY(4, 2, KEY_ENTER),
	KEY(5, 2, KEY_H),
	KEY(6, 2, KEY_Y),
	KEY(0, 3, KEY_SPACE),
	KEY(1, 3, KEY_L),
	KEY(2, 3, KEY_B),
	KEY(3, 3, KEY_V),
	KEY(4, 3, KEY_BACKSPACE),
	KEY(5, 3, KEY_G),
	KEY(6, 3, KEY_T),
	KEY(0, 4, KEY_CAPSLOCK), /* Shअगरt */
	KEY(1, 4, KEY_C),
	KEY(2, 4, KEY_F),
	KEY(3, 4, KEY_R),
	KEY(4, 4, KEY_O),
	KEY(5, 4, KEY_E),
	KEY(6, 4, KEY_D),
	KEY(0, 5, KEY_X),
	KEY(1, 5, KEY_Z),
	KEY(2, 5, KEY_S),
	KEY(3, 5, KEY_W),
	KEY(4, 5, KEY_P),
	KEY(5, 5, KEY_Q),
	KEY(6, 5, KEY_A),
	KEY(0, 6, KEY_CONNECT), /* Voice button */
	KEY(2, 6, KEY_CANCEL), /* End key */
	KEY(3, 6, KEY_VOLUMEDOWN), /* Volume करोwn */
	KEY(4, 6, KEY_F1), /* Left bar (landscape) */
	KEY(5, 6, KEY_WWW), /* OK button (portrait) */
	KEY(6, 6, KEY_CALENDAR), /* Left bar (portrait) */
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data htc_herald_keymap_data = अणु
	.keymap		= htc_herald_keymap,
	.keymap_size	= ARRAY_SIZE(htc_herald_keymap),
पूर्ण;

अटल काष्ठा omap_kp_platक्रमm_data htcherald_kp_data = अणु
	.rows	= 7,
	.cols	= 7,
	.delay = 20,
	.rep = true,
	.keymap_data = &htc_herald_keymap_data,
पूर्ण;

अटल काष्ठा resource kp_resources[] = अणु
	[0] = अणु
		.start	= INT_7XX_MPUIO_KEYPAD,
		.end	= INT_7XX_MPUIO_KEYPAD,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device kp_device = अणु
	.name		= "omap-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &htcherald_kp_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(kp_resources),
	.resource	= kp_resources,
पूर्ण;

/* GPIO buttons क्रम keyboard slide and घातer button */
अटल काष्ठा gpio_keys_button herald_gpio_keys_table[] = अणु
	अणुBTN_0,  HTCHERALD_GPIO_POWER, 1, "POWER", EV_KEY, 1, 20पूर्ण,
	अणुSW_LID, HTCHERALD_GPIO_SLIDE, 0, "SLIDE", EV_SW,  1, 20पूर्ण,

	अणुKEY_LEFT,  HTCPLD_GPIO_LEFT_KBD,  1, "LEFT",  EV_KEY, 1, 20पूर्ण,
	अणुKEY_RIGHT, HTCPLD_GPIO_RIGHT_KBD, 1, "RIGHT", EV_KEY, 1, 20पूर्ण,
	अणुKEY_UP,    HTCPLD_GPIO_UP_KBD,    1, "UP",    EV_KEY, 1, 20पूर्ण,
	अणुKEY_DOWN,  HTCPLD_GPIO_DOWN_KBD,  1, "DOWN",  EV_KEY, 1, 20पूर्ण,

	अणुKEY_LEFT,  HTCPLD_GPIO_LEFT_DPAD,   1, "DLEFT",  EV_KEY, 1, 20पूर्ण,
	अणुKEY_RIGHT, HTCPLD_GPIO_RIGHT_DPAD,  1, "DRIGHT", EV_KEY, 1, 20पूर्ण,
	अणुKEY_UP,    HTCPLD_GPIO_UP_DPAD,     1, "DUP",    EV_KEY, 1, 20पूर्ण,
	अणुKEY_DOWN,  HTCPLD_GPIO_DOWN_DPAD,   1, "DDOWN",  EV_KEY, 1, 20पूर्ण,
	अणुKEY_ENTER, HTCPLD_GPIO_ENTER_DPAD,  1, "DENTER", EV_KEY, 1, 20पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data herald_gpio_keys_data = अणु
	.buttons	= herald_gpio_keys_table,
	.nbuttons	= ARRAY_SIZE(herald_gpio_keys_table),
	.rep		= true,
पूर्ण;

अटल काष्ठा platक्रमm_device herald_gpiokeys_device = अणु
	.name      = "gpio-keys",
	.id		= -1,
	.dev = अणु
		.platक्रमm_data = &herald_gpio_keys_data,
	पूर्ण,
पूर्ण;

/* LEDs क्रम the Herald.  These connect to the HTCPLD GPIO device. */
अटल स्थिर काष्ठा gpio_led gpio_leds[] = अणु
	अणु"dpad",        शून्य, HTCPLD_GPIO_LED_DPAD,        0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"kbd",         शून्य, HTCPLD_GPIO_LED_KBD,         0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"vibrate",     शून्य, HTCPLD_GPIO_LED_VIBRATE,     0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"green_solid", शून्य, HTCPLD_GPIO_LED_GREEN_SOLID, 0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"green_flash", शून्य, HTCPLD_GPIO_LED_GREEN_FLASH, 0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"red_solid",   "mmc0", HTCPLD_GPIO_LED_RED_SOLID, 0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"red_flash",   शून्य, HTCPLD_GPIO_LED_RED_FLASH,   0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"wifi",        शून्य, HTCPLD_GPIO_LED_WIFI,        0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"bt",          शून्य, HTCPLD_GPIO_LED_BT,          0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"caps",        शून्य, HTCPLD_GPIO_LED_CAPS,        0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
	अणु"alt",         शून्य, HTCPLD_GPIO_LED_ALT,         0, 0, LEDS_GPIO_DEFSTATE_OFFपूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data gpio_leds_data = अणु
	.leds		= gpio_leds,
	.num_leds	= ARRAY_SIZE(gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device gpio_leds_device = अणु
	.name		= "leds-gpio",
	.id		= 0,
	.dev	= अणु
		.platक्रमm_data	= &gpio_leds_data,
	पूर्ण,
पूर्ण;

/* HTC PLD chips */

अटल काष्ठा resource htcpld_resources[] = अणु
	[0] = अणु
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा htcpld_chip_platक्रमm_data htcpld_chips[] = अणु
	[0] = अणु
		.addr		= 0x03,
		.reset		= 0x04,
		.num_gpios	= 8,
		.gpio_out_base	= HTCPLD_BASE(0, 0),
		.gpio_in_base	= HTCPLD_BASE(4, 0),
	पूर्ण,
	[1] = अणु
		.addr		= 0x04,
		.reset		= 0x8e,
		.num_gpios	= 8,
		.gpio_out_base	= HTCPLD_BASE(1, 0),
		.gpio_in_base	= HTCPLD_BASE(5, 0),
	पूर्ण,
	[2] = अणु
		.addr		= 0x05,
		.reset		= 0x80,
		.num_gpios	= 8,
		.gpio_out_base	= HTCPLD_BASE(2, 0),
		.gpio_in_base	= HTCPLD_BASE(6, 0),
		.irq_base	= HTCPLD_IRQ(0, 0),
		.num_irqs	= 8,
	पूर्ण,
	[3] = अणु
		.addr		= 0x06,
		.reset		= 0x40,
		.num_gpios	= 8,
		.gpio_out_base	= HTCPLD_BASE(3, 0),
		.gpio_in_base	= HTCPLD_BASE(7, 0),
		.irq_base	= HTCPLD_IRQ(1, 0),
		.num_irqs	= 8,
	पूर्ण,
पूर्ण;

अटल काष्ठा htcpld_core_platक्रमm_data htcpld_pfdata = अणु
	.पूर्णांक_reset_gpio_hi = HTCPLD_GPIO_INT_RESET_HI,
	.पूर्णांक_reset_gpio_lo = HTCPLD_GPIO_INT_RESET_LO,
	.i2c_adapter_id	   = 1,

	.chip		   = htcpld_chips,
	.num_chip	   = ARRAY_SIZE(htcpld_chips),
पूर्ण;

अटल काष्ठा platक्रमm_device htcpld_device = अणु
	.name		= "i2c-htcpld",
	.id		= -1,
	.resource	= htcpld_resources,
	.num_resources	= ARRAY_SIZE(htcpld_resources),
	.dev	= अणु
		.platक्रमm_data	= &htcpld_pfdata,
	पूर्ण,
पूर्ण;

/* USB Device */
अटल काष्ठा omap_usb_config htcherald_usb_config __initdata = अणु
	.otg = 0,
	.रेजिस्टर_host = 0,
	.रेजिस्टर_dev  = 1,
	.hmc_mode = 4,
	.pins[0] = 2,
पूर्ण;

/* LCD Device resources */
अटल स्थिर काष्ठा omap_lcd_config htcherald_lcd_config __initस्थिर = अणु
	.ctrl_name	= "internal",
पूर्ण;

अटल काष्ठा platक्रमm_device lcd_device = अणु
	.name           = "lcd_htcherald",
	.id             = -1,
पूर्ण;

/* MMC Card */
#अगर IS_ENABLED(CONFIG_MMC_OMAP)
अटल काष्ठा omap_mmc_platक्रमm_data htc_mmc1_data = अणु
	.nr_slots                       = 1,
	.चयन_slot                    = शून्य,
	.slots[0]       = अणु
		.ocr_mask               = MMC_VDD_32_33 | MMC_VDD_33_34,
		.name                   = "mmcblk",
		.nomux                  = 1,
		.wires                  = 4,
		.चयन_pin             = -1,
	पूर्ण,
पूर्ण;

अटल काष्ठा omap_mmc_platक्रमm_data *htc_mmc_data[1];
#पूर्ण_अगर


/* Platक्रमm devices क्रम the Herald */
अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&kp_device,
	&lcd_device,
	&htcpld_device,
	&gpio_leds_device,
	&herald_gpiokeys_device,
पूर्ण;

/*
 * Touchscreen
 */
अटल स्थिर काष्ठा ads7846_platक्रमm_data htcherald_ts_platक्रमm_data = अणु
	.model			= 7846,
	.keep_vref_on		= 1,
	.x_plate_ohms		= 496,
	.gpio_penकरोwn		= HTCHERALD_GPIO_TS,
	.pressure_max		= 10000,
	.pressure_min		= 5000,
	.x_min			= 528,
	.x_max			= 3760,
	.y_min			= 624,
	.y_max			= 3760,
पूर्ण;

अटल काष्ठा spi_board_info __initdata htcherald_spi_board_info[] = अणु
	अणु
		.modalias		= "ads7846",
		.platक्रमm_data		= &htcherald_ts_platक्रमm_data,
		.max_speed_hz		= 2500000,
		.bus_num		= 2,
		.chip_select		= 1,
	पूर्ण
पूर्ण;

/*
 * Init functions from here on
 */

अटल व्योम __init htcherald_lcd_init(व्योम)
अणु
	u32 reg;
	अचिन्हित पूर्णांक tries = 200;

	/* disable controller अगर active */
	reg = omap_पढ़ोl(OMAP_LCDC_CONTROL);
	अगर (reg & OMAP_LCDC_CTRL_LCD_EN) अणु
		reg &= ~OMAP_LCDC_CTRL_LCD_EN;
		omap_ग_लिखोl(reg, OMAP_LCDC_CONTROL);

		/* रुको क्रम end of frame */
		जबतक (!(omap_पढ़ोl(OMAP_LCDC_STATUS) & OMAP_LCDC_STAT_DONE)) अणु
			tries--;
			अगर (!tries)
				अवरोध;
		पूर्ण
		अगर (!tries)
			pr_err("Timeout waiting for end of frame -- LCD may not be available\n");

		/* turn off DMA */
		reg = omap_पढ़ोw(OMAP_DMA_LCD_CCR);
		reg &= ~(1 << 7);
		omap_ग_लिखोw(reg, OMAP_DMA_LCD_CCR);

		reg = omap_पढ़ोw(OMAP_DMA_LCD_CTRL);
		reg &= ~(1 << 8);
		omap_ग_लिखोw(reg, OMAP_DMA_LCD_CTRL);
	पूर्ण
पूर्ण

अटल व्योम __init htcherald_map_io(व्योम)
अणु
	omap7xx_map_io();

	/*
	 * The LCD panel must be disabled and DMA turned off here, as करोing
	 * it later causes the LCD never to reinitialize.
	 */
	htcherald_lcd_init();

	prपूर्णांकk(KERN_INFO "htcherald_map_io done.\n");
पूर्ण

अटल व्योम __init htcherald_disable_watchकरोg(व्योम)
अणु
	/* Disable watchकरोg अगर running */
	अगर (omap_पढ़ोl(OMAP_WDT_TIMER_MODE) & 0x8000) अणु
		/*
		 * disable a potentially running watchकरोg समयr beक्रमe
		 * it समाप्तs us.
		 */
		prपूर्णांकk(KERN_WARNING "OMAP850 Watchdog seems to be activated, disabling it for now.\n");
		omap_ग_लिखोl(0xF5, OMAP_WDT_TIMER_MODE);
		omap_ग_लिखोl(0xA0, OMAP_WDT_TIMER_MODE);
	पूर्ण
पूर्ण

#घोषणा HTCHERALD_GPIO_USB_EN1 33
#घोषणा HTCHERALD_GPIO_USB_EN2 73
#घोषणा HTCHERALD_GPIO_USB_DM  35
#घोषणा HTCHERALD_GPIO_USB_DP  36

अटल व्योम __init htcherald_usb_enable(व्योम)
अणु
	अचिन्हित पूर्णांक tries = 20;
	अचिन्हित पूर्णांक value = 0;

	/* Request the GPIOs we need to control here */
	अगर (gpio_request(HTCHERALD_GPIO_USB_EN1, "herald_usb") < 0)
		जाओ err1;

	अगर (gpio_request(HTCHERALD_GPIO_USB_EN2, "herald_usb") < 0)
		जाओ err2;

	अगर (gpio_request(HTCHERALD_GPIO_USB_DM, "herald_usb") < 0)
		जाओ err3;

	अगर (gpio_request(HTCHERALD_GPIO_USB_DP, "herald_usb") < 0)
		जाओ err4;

	/* क्रमce USB_EN GPIO to 0 */
	करो अणु
		/* output low */
		gpio_direction_output(HTCHERALD_GPIO_USB_EN1, 0);
	पूर्ण जबतक ((value = gpio_get_value(HTCHERALD_GPIO_USB_EN1)) == 1 &&
			--tries);

	अगर (value == 1)
		prपूर्णांकk(KERN_WARNING "Unable to reset USB, trying to continue\n");

	gpio_direction_output(HTCHERALD_GPIO_USB_EN2, 0); /* output low */
	gpio_direction_input(HTCHERALD_GPIO_USB_DM); /* input */
	gpio_direction_input(HTCHERALD_GPIO_USB_DP); /* input */

	जाओ करोne;

err4:
	gpio_मुक्त(HTCHERALD_GPIO_USB_DM);
err3:
	gpio_मुक्त(HTCHERALD_GPIO_USB_EN2);
err2:
	gpio_मुक्त(HTCHERALD_GPIO_USB_EN1);
err1:
	prपूर्णांकk(KERN_ERR "Unabled to request GPIO for USB\n");
करोne:
	prपूर्णांकk(KERN_INFO "USB setup complete.\n");
पूर्ण

अटल व्योम __init htcherald_init(व्योम)
अणु
	prपूर्णांकk(KERN_INFO "HTC Herald init.\n");

	/* Do board initialization beक्रमe we रेजिस्टर all the devices */
	htcpld_resources[0].start = gpio_to_irq(HTCHERALD_GIRQ_BTNS);
	htcpld_resources[0].end = gpio_to_irq(HTCHERALD_GIRQ_BTNS);
	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));

	htcherald_disable_watchकरोg();

	htcherald_usb_enable();
	omap1_usb_init(&htcherald_usb_config);

	htcherald_spi_board_info[0].irq = gpio_to_irq(HTCHERALD_GPIO_TS);
	spi_रेजिस्टर_board_info(htcherald_spi_board_info,
		ARRAY_SIZE(htcherald_spi_board_info));

	omap_रेजिस्टर_i2c_bus(1, 100, शून्य, 0);

#अगर IS_ENABLED(CONFIG_MMC_OMAP)
	htc_mmc_data[0] = &htc_mmc1_data;
	omap1_init_mmc(htc_mmc_data, 1);
#पूर्ण_अगर

	omapfb_set_lcd_config(&htcherald_lcd_config);
पूर्ण

MACHINE_START(HERALD, "HTC Herald")
	/* Maपूर्णांकainer: Cory Maccarrone <darkstar6262@gmail.com> */
	/* Maपूर्णांकainer: wing-linux.sourceक्रमge.net */
	.atag_offset    = 0x100,
	.map_io         = htcherald_map_io,
	.init_early     = omap1_init_early,
	.init_irq       = omap1_init_irq,
	.handle_irq	= omap1_handle_irq,
	.init_machine   = htcherald_init,
	.init_late	= omap1_init_late,
	.init_समय	= omap1_समयr_init,
	.restart	= omap1_restart,
MACHINE_END
