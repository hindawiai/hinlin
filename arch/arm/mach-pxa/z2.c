<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/z2.c
 *
 *  Support क्रम the Zipit Z2 Handheld device.
 *
 *  Copyright (C) 2009-2010 Marek Vasut <marek.vasut@gmail.com>
 *
 *  Based on research and code by: Ken McGuire
 *  Based on मुख्यstone.c as modअगरied क्रम the Zipit Z2.
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/z2_battery.h>
#समावेश <linux/dma-mapping.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/spi/libertas_spi.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/delay.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa27x.h"
#समावेश "mfp-pxa27x.h"
#समावेश <mach/z2.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश "pm.h"

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ z2_pin_config[] = अणु

	/* LCD - 16bpp Active TFT */
	GPIO58_LCD_LDD_0,
	GPIO59_LCD_LDD_1,
	GPIO60_LCD_LDD_2,
	GPIO61_LCD_LDD_3,
	GPIO62_LCD_LDD_4,
	GPIO63_LCD_LDD_5,
	GPIO64_LCD_LDD_6,
	GPIO65_LCD_LDD_7,
	GPIO66_LCD_LDD_8,
	GPIO67_LCD_LDD_9,
	GPIO68_LCD_LDD_10,
	GPIO69_LCD_LDD_11,
	GPIO70_LCD_LDD_12,
	GPIO71_LCD_LDD_13,
	GPIO72_LCD_LDD_14,
	GPIO73_LCD_LDD_15,
	GPIO74_LCD_FCLK,
	GPIO75_LCD_LCLK,
	GPIO76_LCD_PCLK,
	GPIO77_LCD_BIAS,
	GPIO19_GPIO,		/* LCD reset */
	GPIO88_GPIO,		/* LCD chipselect */

	/* PWM */
	GPIO115_PWM1_OUT,	/* Keypad Backlight */
	GPIO11_PWM2_OUT,	/* LCD Backlight */

	/* MMC */
	GPIO32_MMC_CLK,
	GPIO112_MMC_CMD,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO96_GPIO,		/* SD detect */

	/* STUART */
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,

	/* Keypad */
	GPIO100_KP_MKIN_0,
	GPIO101_KP_MKIN_1,
	GPIO102_KP_MKIN_2,
	GPIO34_KP_MKIN_3,
	GPIO38_KP_MKIN_4,
	GPIO16_KP_MKIN_5,
	GPIO17_KP_MKIN_6,
	GPIO103_KP_MKOUT_0,
	GPIO104_KP_MKOUT_1,
	GPIO105_KP_MKOUT_2,
	GPIO106_KP_MKOUT_3,
	GPIO107_KP_MKOUT_4,
	GPIO108_KP_MKOUT_5,
	GPIO35_KP_MKOUT_6,
	GPIO41_KP_MKOUT_7,

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* SSP1 */
	GPIO23_SSP1_SCLK,	/* SSP1_SCK */
	GPIO25_SSP1_TXD,	/* SSP1_TXD */
	GPIO26_SSP1_RXD,	/* SSP1_RXD */

	/* SSP2 */
	GPIO22_SSP2_SCLK,	/* SSP2_SCK */
	GPIO13_SSP2_TXD,	/* SSP2_TXD */
	GPIO40_SSP2_RXD,	/* SSP2_RXD */

	/* LEDs */
	GPIO10_GPIO,		/* WiFi LED */
	GPIO83_GPIO,		/* Charging LED */
	GPIO85_GPIO,		/* Charged LED */

	/* I2S */
	GPIO28_I2S_BITCLK_OUT,
	GPIO29_I2S_SDATA_IN,
	GPIO30_I2S_SDATA_OUT,
	GPIO31_I2S_SYNC,
	GPIO113_I2S_SYSCLK,

	/* MISC */
	GPIO0_GPIO,		/* AC घातer detect */
	GPIO1_GPIO,		/* Power button */
	GPIO37_GPIO,		/* Headphone detect */
	GPIO98_GPIO,		/* Lid चयन */
	GPIO14_GPIO,		/* WiFi Power */
	GPIO24_GPIO,		/* WiFi CS */
	GPIO36_GPIO,		/* WiFi IRQ */
	GPIO88_GPIO,		/* LCD CS */
पूर्ण;

/******************************************************************************
 * NOR Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_PHYSMAP) || defined(CONFIG_MTD_PHYSMAP_MODULE)
अटल काष्ठा resource z2_flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_8M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा mtd_partition z2_flash_parts[] = अणु
	अणु
		.name	= "U-Boot Bootloader",
		.offset	= 0x0,
		.size	= 0x40000,
	पूर्ण, अणु
		.name	= "U-Boot Environment",
		.offset	= 0x40000,
		.size	= 0x20000,
	पूर्ण, अणु
		.name	= "Flash",
		.offset	= 0x60000,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data z2_flash_data = अणु
	.width		= 2,
	.parts		= z2_flash_parts,
	.nr_parts	= ARRAY_SIZE(z2_flash_parts),
पूर्ण;

अटल काष्ठा platक्रमm_device z2_flash = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.resource	= &z2_flash_resource,
	.num_resources	= 1,
	.dev = अणु
		.platक्रमm_data	= &z2_flash_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init z2_nor_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&z2_flash);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_nor_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Backlight
 ******************************************************************************/
#अगर defined(CONFIG_BACKLIGHT_PWM) || defined(CONFIG_BACKLIGHT_PWM_MODULE)
अटल काष्ठा pwm_lookup z2_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.1", 0, "pwm-backlight.0", शून्य, 1260320,
		   PWM_POLARITY_NORMAL),
	PWM_LOOKUP("pxa27x-pwm.0", 1, "pwm-backlight.1", शून्य, 1260320,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data z2_backlight_data[] = अणु
	[0] = अणु
		/* Keypad Backlight */
		.max_brightness	= 1023,
		.dft_brightness	= 0,
	पूर्ण,
	[1] = अणु
		/* LCD Backlight */
		.max_brightness	= 1023,
		.dft_brightness	= 512,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device z2_backlight_devices[2] = अणु
	अणु
		.name	= "pwm-backlight",
		.id	= 0,
		.dev	= अणु
			.platक्रमm_data	= &z2_backlight_data[1],
		पूर्ण,
	पूर्ण,
	अणु
		.name	= "pwm-backlight",
		.id	= 1,
		.dev	= अणु
			.platक्रमm_data	= &z2_backlight_data[0],
		पूर्ण,
	पूर्ण,
पूर्ण;
अटल व्योम __init z2_pwm_init(व्योम)
अणु
	pwm_add_table(z2_pwm_lookup, ARRAY_SIZE(z2_pwm_lookup));
	platक्रमm_device_रेजिस्टर(&z2_backlight_devices[0]);
	platक्रमm_device_रेजिस्टर(&z2_backlight_devices[1]);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_pwm_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Framebuffer
 ******************************************************************************/
#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pxafb_mode_info z2_lcd_modes[] = अणु
अणु
	.pixघड़ी	= 192000,
	.xres		= 240,
	.yres		= 320,
	.bpp		= 16,

	.left_margin	= 4,
	.right_margin	= 8,
	.upper_margin	= 4,
	.lower_margin	= 8,

	.hsync_len	= 4,
	.vsync_len	= 4,
पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info z2_lcd_screen = अणु
	.modes		= z2_lcd_modes,
	.num_modes      = ARRAY_SIZE(z2_lcd_modes),
	.lcd_conn	= LCD_COLOR_TFT_16BPP | LCD_BIAS_ACTIVE_LOW |
			  LCD_ALTERNATE_MAPPING,
पूर्ण;

अटल व्योम __init z2_lcd_init(व्योम)
अणु
	pxa_set_fb_info(शून्य, &z2_lcd_screen);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_lcd_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
अटल काष्ठा pxamci_platक्रमm_data z2_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.detect_delay_ms	= 200,
पूर्ण;

अटल काष्ठा gpiod_lookup_table z2_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO96_ZIPITZ2_SD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init z2_mmc_init(व्योम)
अणु
	gpiod_add_lookup_table(&z2_mci_gpio_table);
	pxa_set_mci_info(&z2_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_mmc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * LEDs
 ******************************************************************************/
#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
काष्ठा gpio_led z2_gpio_leds[] = अणु
अणु
	.name			= "z2:green:wifi",
	.शेष_trigger	= "none",
	.gpio			= GPIO10_ZIPITZ2_LED_WIFI,
	.active_low		= 1,
पूर्ण, अणु
	.name			= "z2:green:charged",
	.शेष_trigger	= "mmc0",
	.gpio			= GPIO85_ZIPITZ2_LED_CHARGED,
	.active_low		= 1,
पूर्ण, अणु
	.name			= "z2:amber:charging",
	.शेष_trigger	= "Z2-charging-or-full",
	.gpio			= GPIO83_ZIPITZ2_LED_CHARGING,
	.active_low		= 1,
पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data z2_gpio_led_info = अणु
	.leds		= z2_gpio_leds,
	.num_leds	= ARRAY_SIZE(z2_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device z2_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &z2_gpio_led_info,
	पूर्ण
पूर्ण;

अटल व्योम __init z2_leds_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&z2_leds);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_leds_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keyboard
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक z2_matrix_keys[] = अणु
	KEY(0, 0, KEY_OPTION),
	KEY(1, 0, KEY_UP),
	KEY(2, 0, KEY_DOWN),
	KEY(3, 0, KEY_LEFT),
	KEY(4, 0, KEY_RIGHT),
	KEY(5, 0, KEY_END),
	KEY(6, 0, KEY_KPPLUS),

	KEY(0, 1, KEY_HOME),
	KEY(1, 1, KEY_Q),
	KEY(2, 1, KEY_I),
	KEY(3, 1, KEY_G),
	KEY(4, 1, KEY_X),
	KEY(5, 1, KEY_ENTER),
	KEY(6, 1, KEY_KPMINUS),

	KEY(0, 2, KEY_PAGEUP),
	KEY(1, 2, KEY_W),
	KEY(2, 2, KEY_O),
	KEY(3, 2, KEY_H),
	KEY(4, 2, KEY_C),
	KEY(5, 2, KEY_LEFTALT),

	KEY(0, 3, KEY_PAGEDOWN),
	KEY(1, 3, KEY_E),
	KEY(2, 3, KEY_P),
	KEY(3, 3, KEY_J),
	KEY(4, 3, KEY_V),
	KEY(5, 3, KEY_LEFTSHIFT),

	KEY(0, 4, KEY_ESC),
	KEY(1, 4, KEY_R),
	KEY(2, 4, KEY_A),
	KEY(3, 4, KEY_K),
	KEY(4, 4, KEY_B),
	KEY(5, 4, KEY_LEFTCTRL),

	KEY(0, 5, KEY_TAB),
	KEY(1, 5, KEY_T),
	KEY(2, 5, KEY_S),
	KEY(3, 5, KEY_L),
	KEY(4, 5, KEY_N),
	KEY(5, 5, KEY_SPACE),

	KEY(0, 6, KEY_STOPCD),
	KEY(1, 6, KEY_Y),
	KEY(2, 6, KEY_D),
	KEY(3, 6, KEY_BACKSPACE),
	KEY(4, 6, KEY_M),
	KEY(5, 6, KEY_COMMA),

	KEY(0, 7, KEY_PLAYCD),
	KEY(1, 7, KEY_U),
	KEY(2, 7, KEY_F),
	KEY(3, 7, KEY_Z),
	KEY(4, 7, KEY_SEMICOLON),
	KEY(5, 7, KEY_DOT),
पूर्ण;

अटल काष्ठा matrix_keymap_data z2_matrix_keymap_data = अणु
	.keymap			= z2_matrix_keys,
	.keymap_size		= ARRAY_SIZE(z2_matrix_keys),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data z2_keypad_platक्रमm_data = अणु
	.matrix_key_rows	= 7,
	.matrix_key_cols	= 8,
	.matrix_keymap_data	= &z2_matrix_keymap_data,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;

अटल व्योम __init z2_mkp_init(व्योम)
अणु
	pxa_set_keypad_info(&z2_keypad_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_mkp_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keys
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
अटल काष्ठा gpio_keys_button z2_pxa_buttons[] = अणु
	अणु
		.code		= KEY_POWER,
		.gpio		= GPIO1_ZIPITZ2_POWER_BUTTON,
		.active_low	= 0,
		.desc		= "Power Button",
		.wakeup		= 1,
		.type		= EV_KEY,
	पूर्ण,
	अणु
		.code		= SW_LID,
		.gpio		= GPIO98_ZIPITZ2_LID_BUTTON,
		.active_low	= 1,
		.desc		= "Lid Switch",
		.wakeup		= 0,
		.type		= EV_SW,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data z2_pxa_keys_data = अणु
	.buttons	= z2_pxa_buttons,
	.nbuttons	= ARRAY_SIZE(z2_pxa_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device z2_pxa_keys = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &z2_pxa_keys_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init z2_keys_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&z2_pxa_keys);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_keys_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Battery
 ******************************************************************************/
#अगर defined(CONFIG_I2C_PXA) || defined(CONFIG_I2C_PXA_MODULE)
अटल काष्ठा z2_battery_info batt_chip_info = अणु
	.batt_I2C_bus	= 0,
	.batt_I2C_addr	= 0x55,
	.batt_I2C_reg	= 2,
	.min_voltage	= 3475000,
	.max_voltage	= 4190000,
	.batt_भाग	= 59,
	.batt_mult	= 1000000,
	.batt_tech	= POWER_SUPPLY_TECHNOLOGY_LION,
	.batt_name	= "Z2",
पूर्ण;

अटल काष्ठा gpiod_lookup_table z2_battery_gpio_table = अणु
	.dev_id = "aer915",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO0_ZIPITZ2_AC_DETECT,
			    शून्य, GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata z2_i2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("aer915", 0x55),
		.dev_name = "aer915",
		.platक्रमm_data	= &batt_chip_info,
	पूर्ण, अणु
		I2C_BOARD_INFO("wm8750", 0x1b),
	पूर्ण,

पूर्ण;

अटल व्योम __init z2_i2c_init(व्योम)
अणु
	pxa_set_i2c_info(शून्य);
	gpiod_add_lookup_table(&z2_battery_gpio_table);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(z2_i2c_board_info));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_i2c_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * SSP Devices - WiFi and LCD control
 ******************************************************************************/
#अगर defined(CONFIG_SPI_PXA2XX) || defined(CONFIG_SPI_PXA2XX_MODULE)
/* WiFi */
अटल पूर्णांक z2_lbs_spi_setup(काष्ठा spi_device *spi)
अणु
	पूर्णांक ret = 0;

	ret = gpio_request(GPIO14_ZIPITZ2_WIFI_POWER, "WiFi Power");
	अगर (ret)
		जाओ err;

	ret = gpio_direction_output(GPIO14_ZIPITZ2_WIFI_POWER, 1);
	अगर (ret)
		जाओ err2;

	/* Wait until card is घातered on */
	mdelay(180);

	spi->bits_per_word = 16;
	spi->mode = SPI_MODE_2,

	spi_setup(spi);

	वापस 0;

err2:
	gpio_मुक्त(GPIO14_ZIPITZ2_WIFI_POWER);
err:
	वापस ret;
पूर्ण;

अटल पूर्णांक z2_lbs_spi_tearकरोwn(काष्ठा spi_device *spi)
अणु
	gpio_set_value(GPIO14_ZIPITZ2_WIFI_POWER, 0);
	gpio_मुक्त(GPIO14_ZIPITZ2_WIFI_POWER);

	वापस 0;
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip z2_lbs_chip_info = अणु
	.rx_threshold	= 8,
	.tx_threshold	= 8,
	.समयout	= 1000,
	.gpio_cs	= GPIO24_ZIPITZ2_WIFI_CS,
पूर्ण;

अटल काष्ठा libertas_spi_platक्रमm_data z2_lbs_pdata = अणु
	.use_dummy_ग_लिखोs	= 1,
	.setup			= z2_lbs_spi_setup,
	.tearकरोwn		= z2_lbs_spi_tearकरोwn,
पूर्ण;

/* LCD */
अटल काष्ठा pxa2xx_spi_chip lms283_chip_info = अणु
	.rx_threshold	= 1,
	.tx_threshold	= 1,
	.समयout	= 64,
	.gpio_cs	= GPIO88_ZIPITZ2_LCD_CS,
पूर्ण;

अटल काष्ठा gpiod_lookup_table lms283_gpio_table = अणु
	.dev_id = "spi2.0", /* SPI bus 2 chip select 0 */
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO19_ZIPITZ2_LCD_RESET,
			    "reset", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info spi_board_info[] __initdata = अणु
अणु
	.modalias		= "libertas_spi",
	.platक्रमm_data		= &z2_lbs_pdata,
	.controller_data	= &z2_lbs_chip_info,
	.irq			= PXA_GPIO_TO_IRQ(GPIO36_ZIPITZ2_WIFI_IRQ),
	.max_speed_hz		= 13000000,
	.bus_num		= 1,
	.chip_select		= 0,
पूर्ण,
अणु
	.modalias		= "lms283gf05",
	.controller_data	= &lms283_chip_info,
	.max_speed_hz		= 400000,
	.bus_num		= 2,
	.chip_select		= 0,
पूर्ण,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp1_master_info = अणु
	.num_chipselect	= 1,
	.enable_dma	= 1,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp2_master_info = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल व्योम __init z2_spi_init(व्योम)
अणु
	pxa2xx_set_spi_info(1, &pxa_ssp1_master_info);
	pxa2xx_set_spi_info(2, &pxa_ssp2_master_info);
	gpiod_add_lookup_table(&lms283_gpio_table);
	spi_रेजिस्टर_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_spi_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Core घातer regulator
 ******************************************************************************/
#अगर defined(CONFIG_REGULATOR_TPS65023) || \
	defined(CONFIG_REGULATOR_TPS65023_MODULE)
अटल काष्ठा regulator_consumer_supply z2_tps65021_consumers[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data z2_tps65021_info[] = अणु
	अणु
		.स्थिरraपूर्णांकs = अणु
			.name		= "vcc_core range",
			.min_uV		= 800000,
			.max_uV		= 1600000,
			.always_on	= 1,
			.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
		पूर्ण,
		.consumer_supplies	= z2_tps65021_consumers,
		.num_consumer_supplies	= ARRAY_SIZE(z2_tps65021_consumers),
	पूर्ण, अणु
		.स्थिरraपूर्णांकs = अणु
			.name		= "DCDC2",
			.min_uV		= 3300000,
			.max_uV		= 3300000,
			.always_on	= 1,
		पूर्ण,
	पूर्ण, अणु
		.स्थिरraपूर्णांकs = अणु
			.name		= "DCDC3",
			.min_uV		= 1800000,
			.max_uV		= 1800000,
			.always_on	= 1,
		पूर्ण,
	पूर्ण, अणु
		.स्थिरraपूर्णांकs = अणु
			.name		= "LDO1",
			.min_uV		= 1000000,
			.max_uV		= 3150000,
			.always_on	= 1,
		पूर्ण,
	पूर्ण, अणु
		.स्थिरraपूर्णांकs = अणु
			.name		= "LDO2",
			.min_uV		= 1050000,
			.max_uV		= 3300000,
			.always_on	= 1,
		पूर्ण,
	पूर्ण
पूर्ण;

अटल काष्ठा i2c_board_info __initdata z2_pi2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("tps65021", 0x48),
		.platक्रमm_data	= &z2_tps65021_info,
	पूर्ण,
पूर्ण;

अटल व्योम __init z2_pmic_init(व्योम)
अणु
	pxa27x_set_i2c_घातer_info(शून्य);
	i2c_रेजिस्टर_board_info(1, ARRAY_AND_SIZE(z2_pi2c_board_info));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम z2_pmic_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PM
अटल व्योम z2_घातer_off(व्योम)
अणु
	/* We're using deep sleep as घातeroff, so clear PSPR to ensure that
	 * bootloader will jump to its entry poपूर्णांक in resume handler
	 */
	PSPR = 0x0;
	local_irq_disable();
	pxa27x_set_pwrmode(PWRMODE_DEEPSLEEP);
	pxa27x_cpu_pm_enter(PM_SUSPEND_MEM);
पूर्ण
#अन्यथा
#घोषणा z2_घातer_off   शून्य
#पूर्ण_अगर

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल व्योम __init z2_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(z2_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	z2_lcd_init();
	z2_mmc_init();
	z2_mkp_init();
	z2_i2c_init();
	z2_spi_init();
	z2_nor_init();
	z2_pwm_init();
	z2_leds_init();
	z2_keys_init();
	z2_pmic_init();

	pm_घातer_off = z2_घातer_off;
पूर्ण

MACHINE_START(ZIPIT2, "Zipit Z2")
	.atag_offset	= 0x100,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= z2_init,
	.restart	= pxa_restart,
MACHINE_END
