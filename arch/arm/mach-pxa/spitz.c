<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम Sharp SL-Cxx00 Series of PDAs
 * Models: SL-C3000 (Spitz), SL-C1000 (Akita) and SL-C3100 (Borzoi)
 *
 * Copyright (c) 2005 Riअक्षरd Purdie
 *
 * Based on Sharp's 2.4 kernel patches/lubbock.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>	/* symbol_get ; symbol_put */
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/leds.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/platक्रमm_data/pca953x.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/spi/corgi_lcd.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/mtd/sharpsl.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/पन.स>
#समावेश <linux/reboot.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/sharpsl_param.h>
#समावेश <यंत्र/hardware/scoop.h>

#समावेश "pxa27x.h"
#समावेश "pxa27x-udc.h"
#समावेश <mach/reset.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <mach/spitz.h>
#समावेश "sharpsl_pm.h"
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ spitz_pin_config[] __initdata = अणु
	/* Chip Selects */
	GPIO78_nCS_2,	/* SCOOP #2 */
	GPIO79_nCS_3,	/* न_अंकD */
	GPIO80_nCS_4,	/* SCOOP #1 */

	/* LCD - 16bpp Active TFT */
	GPIOxx_LCD_TFT_16BPP,

	/* PC Card */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO85_nPCE_1,
	GPIO54_nPCE_2,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,
	GPIO104_PSKTSEL,

	/* I2S */
	GPIO28_I2S_BITCLK_OUT,
	GPIO29_I2S_SDATA_IN,
	GPIO30_I2S_SDATA_OUT,
	GPIO31_I2S_SYNC,

	/* MMC */
	GPIO32_MMC_CLK,
	GPIO112_MMC_CMD,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,

	/* GPIOs */
	GPIO9_GPIO,	/* SPITZ_GPIO_nSD_DETECT */
	GPIO16_GPIO,	/* SPITZ_GPIO_SYNC */
	GPIO81_GPIO,	/* SPITZ_GPIO_nSD_WP */
	GPIO41_GPIO,	/* SPITZ_GPIO_USB_CONNECT */
	GPIO37_GPIO,	/* SPITZ_GPIO_USB_HOST */
	GPIO35_GPIO,	/* SPITZ_GPIO_USB_DEVICE */
	GPIO22_GPIO,	/* SPITZ_GPIO_HSYNC */
	GPIO94_GPIO,	/* SPITZ_GPIO_CF_CD */
	GPIO105_GPIO,	/* SPITZ_GPIO_CF_IRQ */
	GPIO106_GPIO,	/* SPITZ_GPIO_CF2_IRQ */

	/* GPIO matrix keypad */
	GPIO88_GPIO,	/* column 0 */
	GPIO23_GPIO,	/* column 1 */
	GPIO24_GPIO,	/* column 2 */
	GPIO25_GPIO,	/* column 3 */
	GPIO26_GPIO,	/* column 4 */
	GPIO27_GPIO,	/* column 5 */
	GPIO52_GPIO,	/* column 6 */
	GPIO103_GPIO,	/* column 7 */
	GPIO107_GPIO,	/* column 8 */
	GPIO108_GPIO,	/* column 9 */
	GPIO114_GPIO,	/* column 10 */
	GPIO12_GPIO,	/* row 0 */
	GPIO17_GPIO,	/* row 1 */
	GPIO91_GPIO,	/* row 2 */
	GPIO34_GPIO,	/* row 3 */
	GPIO36_GPIO,	/* row 4 */
	GPIO38_GPIO,	/* row 5 */
	GPIO39_GPIO,	/* row 6 */

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	GPIO0_GPIO | WAKEUP_ON_EDGE_RISE,	/* SPITZ_GPIO_KEY_INT */
	GPIO1_GPIO | WAKEUP_ON_EDGE_FALL,	/* SPITZ_GPIO_RESET */
पूर्ण;


/******************************************************************************
 * Scoop GPIO expander
 ******************************************************************************/
#अगर defined(CONFIG_SHARP_SCOOP) || defined(CONFIG_SHARP_SCOOP_MODULE)
/* SCOOP Device #1 */
अटल काष्ठा resource spitz_scoop_1_resources[] = अणु
	[0] = अणु
		.start		= 0x10800000,
		.end		= 0x10800fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा scoop_config spitz_scoop_1_setup = अणु
	.io_dir		= SPITZ_SCP_IO_सूची,
	.io_out		= SPITZ_SCP_IO_OUT,
	.suspend_clr	= SPITZ_SCP_SUS_CLR,
	.suspend_set	= SPITZ_SCP_SUS_SET,
	.gpio_base	= SPITZ_SCP_GPIO_BASE,
पूर्ण;

काष्ठा platक्रमm_device spitz_scoop_1_device = अणु
	.name		= "sharp-scoop",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &spitz_scoop_1_setup,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(spitz_scoop_1_resources),
	.resource	= spitz_scoop_1_resources,
पूर्ण;

/* SCOOP Device #2 */
अटल काष्ठा resource spitz_scoop_2_resources[] = अणु
	[0] = अणु
		.start		= 0x08800040,
		.end		= 0x08800fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा scoop_config spitz_scoop_2_setup = अणु
	.io_dir		= SPITZ_SCP2_IO_सूची,
	.io_out		= SPITZ_SCP2_IO_OUT,
	.suspend_clr	= SPITZ_SCP2_SUS_CLR,
	.suspend_set	= SPITZ_SCP2_SUS_SET,
	.gpio_base	= SPITZ_SCP2_GPIO_BASE,
पूर्ण;

काष्ठा platक्रमm_device spitz_scoop_2_device = अणु
	.name		= "sharp-scoop",
	.id		= 1,
	.dev		= अणु
		.platक्रमm_data	= &spitz_scoop_2_setup,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(spitz_scoop_2_resources),
	.resource	= spitz_scoop_2_resources,
पूर्ण;

अटल व्योम __init spitz_scoop_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&spitz_scoop_1_device);

	/* Akita करोesn't have the second SCOOP chip */
	अगर (!machine_is_akita())
		platक्रमm_device_रेजिस्टर(&spitz_scoop_2_device);
पूर्ण

/* Power control is shared with between one of the CF slots and SD */
अटल व्योम __maybe_unused spitz_card_pwr_ctrl(uपूर्णांक8_t enable, uपूर्णांक8_t new_cpr)
अणु
	अचिन्हित लघु cpr;
	अचिन्हित दीर्घ flags;

	अगर (new_cpr & 0x7) अणु
		gpio_set_value(SPITZ_GPIO_CF_POWER, 1);
		mdelay(5);
	पूर्ण

	local_irq_save(flags);

	cpr = पढ़ो_scoop_reg(&spitz_scoop_1_device.dev, SCOOP_CPR);

	अगर (enable & new_cpr)
		cpr |= new_cpr;
	अन्यथा
		cpr &= ~enable;

	ग_लिखो_scoop_reg(&spitz_scoop_1_device.dev, SCOOP_CPR, cpr);

	local_irq_restore(flags);

	अगर (!(cpr & 0x7)) अणु
		mdelay(1);
		gpio_set_value(SPITZ_GPIO_CF_POWER, 0);
	पूर्ण
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम spitz_scoop_init(व्योम) अणुपूर्ण
अटल अंतरभूत व्योम spitz_card_pwr_ctrl(uपूर्णांक8_t enable, uपूर्णांक8_t new_cpr) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * PCMCIA
 ******************************************************************************/
#अगर defined(CONFIG_PCMCIA_PXA2XX) || defined(CONFIG_PCMCIA_PXA2XX_MODULE)
अटल व्योम spitz_pcmcia_pwr(काष्ठा device *scoop, uपूर्णांक16_t cpr, पूर्णांक nr)
अणु
	/* Only need to override behaviour क्रम slot 0 */
	अगर (nr == 0)
		spitz_card_pwr_ctrl(
			cpr & (SCOOP_CPR_CF_3V | SCOOP_CPR_CF_XV), cpr);
	अन्यथा
		ग_लिखो_scoop_reg(scoop, SCOOP_CPR, cpr);
पूर्ण

अटल काष्ठा scoop_pcmcia_dev spitz_pcmcia_scoop[] = अणु
	अणु
		.dev		= &spitz_scoop_1_device.dev,
		.irq		= SPITZ_IRQ_GPIO_CF_IRQ,
		.cd_irq		= SPITZ_IRQ_GPIO_CF_CD,
		.cd_irq_str	= "PCMCIA0 CD",
	पूर्ण, अणु
		.dev		= &spitz_scoop_2_device.dev,
		.irq		= SPITZ_IRQ_GPIO_CF2_IRQ,
		.cd_irq		= -1,
	पूर्ण,
पूर्ण;

अटल काष्ठा scoop_pcmcia_config spitz_pcmcia_config = अणु
	.devs		= &spitz_pcmcia_scoop[0],
	.num_devs	= 2,
	.घातer_ctrl	= spitz_pcmcia_pwr,
पूर्ण;

अटल व्योम __init spitz_pcmcia_init(व्योम)
अणु
	/* Akita has only one PCMCIA slot used */
	अगर (machine_is_akita())
		spitz_pcmcia_config.num_devs = 1;

	platक्रमm_scoop_config = &spitz_pcmcia_config;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_pcmcia_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keyboard
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_MATRIX) || defined(CONFIG_KEYBOARD_MATRIX_MODULE)

#घोषणा SPITZ_KEY_CALENDAR	KEY_F1
#घोषणा SPITZ_KEY_ADDRESS	KEY_F2
#घोषणा SPITZ_KEY_FN		KEY_F3
#घोषणा SPITZ_KEY_CANCEL	KEY_F4
#घोषणा SPITZ_KEY_EXOK		KEY_F5
#घोषणा SPITZ_KEY_EXCANCEL	KEY_F6
#घोषणा SPITZ_KEY_EXJOGDOWN	KEY_F7
#घोषणा SPITZ_KEY_EXJOGUP	KEY_F8
#घोषणा SPITZ_KEY_JAP1		KEY_LEFTALT
#घोषणा SPITZ_KEY_JAP2		KEY_RIGHTCTRL
#घोषणा SPITZ_KEY_SYNC		KEY_F9
#घोषणा SPITZ_KEY_MAIL		KEY_F10
#घोषणा SPITZ_KEY_OK		KEY_F11
#घोषणा SPITZ_KEY_MENU		KEY_F12

अटल स्थिर uपूर्णांक32_t spitz_keymap[] = अणु
	KEY(0, 0, KEY_LEFTCTRL),
	KEY(0, 1, KEY_1),
	KEY(0, 2, KEY_3),
	KEY(0, 3, KEY_5),
	KEY(0, 4, KEY_6),
	KEY(0, 5, KEY_7),
	KEY(0, 6, KEY_9),
	KEY(0, 7, KEY_0),
	KEY(0, 8, KEY_BACKSPACE),
	KEY(0, 9, SPITZ_KEY_EXOK),	/* EXOK */
	KEY(0, 10, SPITZ_KEY_EXCANCEL),	/* EXCANCEL */
	KEY(1, 1, KEY_2),
	KEY(1, 2, KEY_4),
	KEY(1, 3, KEY_R),
	KEY(1, 4, KEY_Y),
	KEY(1, 5, KEY_8),
	KEY(1, 6, KEY_I),
	KEY(1, 7, KEY_O),
	KEY(1, 8, KEY_P),
	KEY(1, 9, SPITZ_KEY_EXJOGDOWN),	/* EXJOGDOWN */
	KEY(1, 10, SPITZ_KEY_EXJOGUP),	/* EXJOGUP */
	KEY(2, 0, KEY_TAB),
	KEY(2, 1, KEY_Q),
	KEY(2, 2, KEY_E),
	KEY(2, 3, KEY_T),
	KEY(2, 4, KEY_G),
	KEY(2, 5, KEY_U),
	KEY(2, 6, KEY_J),
	KEY(2, 7, KEY_K),
	KEY(3, 0, SPITZ_KEY_ADDRESS),	/* ADDRESS */
	KEY(3, 1, KEY_W),
	KEY(3, 2, KEY_S),
	KEY(3, 3, KEY_F),
	KEY(3, 4, KEY_V),
	KEY(3, 5, KEY_H),
	KEY(3, 6, KEY_M),
	KEY(3, 7, KEY_L),
	KEY(3, 9, KEY_RIGHTSHIFT),
	KEY(4, 0, SPITZ_KEY_CALENDAR),	/* CALENDAR */
	KEY(4, 1, KEY_A),
	KEY(4, 2, KEY_D),
	KEY(4, 3, KEY_C),
	KEY(4, 4, KEY_B),
	KEY(4, 5, KEY_N),
	KEY(4, 6, KEY_DOT),
	KEY(4, 8, KEY_ENTER),
	KEY(4, 9, KEY_LEFTSHIFT),
	KEY(5, 0, SPITZ_KEY_MAIL),	/* MAIL */
	KEY(5, 1, KEY_Z),
	KEY(5, 2, KEY_X),
	KEY(5, 3, KEY_MINUS),
	KEY(5, 4, KEY_SPACE),
	KEY(5, 5, KEY_COMMA),
	KEY(5, 7, KEY_UP),
	KEY(5, 10, SPITZ_KEY_FN),	/* FN */
	KEY(6, 0, KEY_SYSRQ),
	KEY(6, 1, SPITZ_KEY_JAP1),	/* JAP1 */
	KEY(6, 2, SPITZ_KEY_JAP2),	/* JAP2 */
	KEY(6, 3, SPITZ_KEY_CANCEL),	/* CANCEL */
	KEY(6, 4, SPITZ_KEY_OK),	/* OK */
	KEY(6, 5, SPITZ_KEY_MENU),	/* MENU */
	KEY(6, 6, KEY_LEFT),
	KEY(6, 7, KEY_DOWN),
	KEY(6, 8, KEY_RIGHT),
पूर्ण;

अटल स्थिर काष्ठा matrix_keymap_data spitz_keymap_data = अणु
	.keymap		= spitz_keymap,
	.keymap_size	= ARRAY_SIZE(spitz_keymap),
पूर्ण;

अटल स्थिर uपूर्णांक32_t spitz_row_gpios[] =
		अणु 12, 17, 91, 34, 36, 38, 39 पूर्ण;
अटल स्थिर uपूर्णांक32_t spitz_col_gpios[] =
		अणु 88, 23, 24, 25, 26, 27, 52, 103, 107, 108, 114 पूर्ण;

अटल काष्ठा matrix_keypad_platक्रमm_data spitz_mkp_pdata = अणु
	.keymap_data		= &spitz_keymap_data,
	.row_gpios		= spitz_row_gpios,
	.col_gpios		= spitz_col_gpios,
	.num_row_gpios		= ARRAY_SIZE(spitz_row_gpios),
	.num_col_gpios		= ARRAY_SIZE(spitz_col_gpios),
	.col_scan_delay_us	= 10,
	.debounce_ms		= 10,
	.wakeup			= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device spitz_mkp_device = अणु
	.name		= "matrix-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &spitz_mkp_pdata,
	पूर्ण,
पूर्ण;

अटल व्योम __init spitz_mkp_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&spitz_mkp_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_mkp_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keys
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
अटल काष्ठा gpio_keys_button spitz_gpio_keys[] = अणु
	अणु
		.type	= EV_PWR,
		.code	= KEY_SUSPEND,
		.gpio	= SPITZ_GPIO_ON_KEY,
		.desc	= "On Off",
		.wakeup	= 1,
	पूर्ण,
	/* Two buttons detecting the lid state */
	अणु
		.type	= EV_SW,
		.code	= 0,
		.gpio	= SPITZ_GPIO_SWA,
		.desc	= "Display Down",
	पूर्ण,
	अणु
		.type	= EV_SW,
		.code	= 1,
		.gpio	= SPITZ_GPIO_SWB,
		.desc	= "Lid Closed",
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data spitz_gpio_keys_platक्रमm_data = अणु
	.buttons	= spitz_gpio_keys,
	.nbuttons	= ARRAY_SIZE(spitz_gpio_keys),
पूर्ण;

अटल काष्ठा platक्रमm_device spitz_gpio_keys_device = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &spitz_gpio_keys_platक्रमm_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init spitz_keys_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&spitz_gpio_keys_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_keys_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * LEDs
 ******************************************************************************/
#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
अटल काष्ठा gpio_led spitz_gpio_leds[] = अणु
	अणु
		.name			= "spitz:amber:charge",
		.शेष_trigger	= "sharpsl-charge",
		.gpio			= SPITZ_GPIO_LED_ORANGE,
	पूर्ण,
	अणु
		.name			= "spitz:green:hddactivity",
		.शेष_trigger	= "disk-activity",
		.gpio			= SPITZ_GPIO_LED_GREEN,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data spitz_gpio_leds_info = अणु
	.leds		= spitz_gpio_leds,
	.num_leds	= ARRAY_SIZE(spitz_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device spitz_led_device = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &spitz_gpio_leds_info,
	पूर्ण,
पूर्ण;

अटल व्योम __init spitz_leds_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&spitz_led_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_leds_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * SSP Devices
 ******************************************************************************/
#अगर defined(CONFIG_SPI_PXA2XX) || defined(CONFIG_SPI_PXA2XX_MODULE)
अटल व्योम spitz_ads7846_रुको_क्रम_hsync(व्योम)
अणु
	जबतक (gpio_get_value(SPITZ_GPIO_HSYNC))
		cpu_relax();

	जबतक (!gpio_get_value(SPITZ_GPIO_HSYNC))
		cpu_relax();
पूर्ण

अटल काष्ठा ads7846_platक्रमm_data spitz_ads7846_info = अणु
	.model			= 7846,
	.vref_delay_usecs	= 100,
	.x_plate_ohms		= 419,
	.y_plate_ohms		= 486,
	.pressure_max		= 1024,
	.gpio_penकरोwn		= SPITZ_GPIO_TP_INT,
	.रुको_क्रम_sync		= spitz_ads7846_रुको_क्रम_hsync,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip spitz_ads7846_chip = अणु
	.gpio_cs		= SPITZ_GPIO_ADS7846_CS,
पूर्ण;

अटल व्योम spitz_bl_kick_battery(व्योम)
अणु
	व्योम (*kick_batt)(व्योम);

	kick_batt = symbol_get(sharpsl_battery_kick);
	अगर (kick_batt) अणु
		kick_batt();
		symbol_put(sharpsl_battery_kick);
	पूर्ण
पूर्ण

अटल काष्ठा gpiod_lookup_table spitz_lcdcon_gpio_table = अणु
	.dev_id = "spi2.1",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", SPITZ_GPIO_BACKLIGHT_CONT,
			    "BL_CONT", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", SPITZ_GPIO_BACKLIGHT_ON,
			    "BL_ON", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table akita_lcdcon_gpio_table = अणु
	.dev_id = "spi2.1",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", AKITA_GPIO_BACKLIGHT_CONT,
			    "BL_CONT", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", AKITA_GPIO_BACKLIGHT_ON,
			    "BL_ON", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा corgi_lcd_platक्रमm_data spitz_lcdcon_info = अणु
	.init_mode		= CORGI_LCD_MODE_VGA,
	.max_पूर्णांकensity		= 0x2f,
	.शेष_पूर्णांकensity	= 0x1f,
	.limit_mask		= 0x0b,
	.kick_battery		= spitz_bl_kick_battery,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip spitz_lcdcon_chip = अणु
	.gpio_cs	= SPITZ_GPIO_LCDCON_CS,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip spitz_max1111_chip = अणु
	.gpio_cs	= SPITZ_GPIO_MAX1111_CS,
पूर्ण;

अटल काष्ठा spi_board_info spitz_spi_devices[] = अणु
	अणु
		.modalias		= "ads7846",
		.max_speed_hz		= 1200000,
		.bus_num		= 2,
		.chip_select		= 0,
		.platक्रमm_data		= &spitz_ads7846_info,
		.controller_data	= &spitz_ads7846_chip,
		.irq			= PXA_GPIO_TO_IRQ(SPITZ_GPIO_TP_INT),
	पूर्ण, अणु
		.modalias		= "corgi-lcd",
		.max_speed_hz		= 50000,
		.bus_num		= 2,
		.chip_select		= 1,
		.platक्रमm_data		= &spitz_lcdcon_info,
		.controller_data	= &spitz_lcdcon_chip,
	पूर्ण, अणु
		.modalias		= "max1111",
		.max_speed_hz		= 450000,
		.bus_num		= 2,
		.chip_select		= 2,
		.controller_data	= &spitz_max1111_chip,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller spitz_spi_info = अणु
	.num_chipselect	= 3,
पूर्ण;

अटल व्योम __init spitz_spi_init(व्योम)
अणु
	अगर (machine_is_akita())
		gpiod_add_lookup_table(&akita_lcdcon_gpio_table);
	अन्यथा
		gpiod_add_lookup_table(&spitz_lcdcon_gpio_table);

	pxa2xx_set_spi_info(2, &spitz_spi_info);
	spi_रेजिस्टर_board_info(ARRAY_AND_SIZE(spitz_spi_devices));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_spi_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
/*
 * NOTE: The card detect पूर्णांकerrupt isn't debounced so we delay it by 250ms to
 * give the card a chance to fully insert/eject.
 */
अटल पूर्णांक spitz_mci_setघातer(काष्ठा device *dev, अचिन्हित पूर्णांक vdd)
अणु
	काष्ठा pxamci_platक्रमm_data* p_d = dev->platक्रमm_data;

	अगर ((1 << vdd) & p_d->ocr_mask)
		spitz_card_pwr_ctrl(SCOOP_CPR_SD_3V, SCOOP_CPR_SD_3V);
	अन्यथा
		spitz_card_pwr_ctrl(SCOOP_CPR_SD_3V, 0x0);

	वापस 0;
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data spitz_mci_platक्रमm_data = अणु
	.detect_delay_ms	= 250,
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
	.setघातer		= spitz_mci_setघातer,
पूर्ण;

अटल काष्ठा gpiod_lookup_table spitz_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", SPITZ_GPIO_nSD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", SPITZ_GPIO_nSD_WP,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init spitz_mmc_init(व्योम)
अणु
	gpiod_add_lookup_table(&spitz_mci_gpio_table);
	pxa_set_mci_info(&spitz_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_mmc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB Host
 ******************************************************************************/
#अगर defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
अटल पूर्णांक spitz_ohci_init(काष्ठा device *dev)
अणु
	पूर्णांक err;

	err = gpio_request(SPITZ_GPIO_USB_HOST, "USB_HOST");
	अगर (err)
		वापस err;

	/* Only Port 2 is connected, setup USB Port 2 Output Control Register */
	UP2OCR = UP2OCR_HXS | UP2OCR_HXOE | UP2OCR_DPPDE | UP2OCR_DMPDE;

	वापस gpio_direction_output(SPITZ_GPIO_USB_HOST, 1);
पूर्ण

अटल व्योम spitz_ohci_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(SPITZ_GPIO_USB_HOST);
पूर्ण

अटल काष्ठा pxaohci_platक्रमm_data spitz_ohci_platक्रमm_data = अणु
	.port_mode	= PMM_NPS_MODE,
	.init		= spitz_ohci_init,
	.निकास		= spitz_ohci_निकास,
	.flags		= ENABLE_PORT_ALL | NO_OC_PROTECTION,
	.घातer_budget	= 150,
पूर्ण;

अटल व्योम __init spitz_uhc_init(व्योम)
अणु
	pxa_set_ohci_info(&spitz_ohci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_uhc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * IrDA
 ******************************************************************************/
#अगर defined(CONFIG_PXA_FICP) || defined(CONFIG_PXA_FICP_MODULE)
अटल काष्ठा pxaficp_platक्रमm_data spitz_ficp_platक्रमm_data = अणु
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
पूर्ण;

अटल व्योम __init spitz_irda_init(व्योम)
अणु
	अगर (machine_is_akita())
		spitz_ficp_platक्रमm_data.gpio_pwकरोwn = AKITA_GPIO_IR_ON;
	अन्यथा
		spitz_ficp_platक्रमm_data.gpio_pwकरोwn = SPITZ_GPIO_IR_ON;

	pxa_set_ficp_info(&spitz_ficp_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_irda_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Framebuffer
 ******************************************************************************/
#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pxafb_mode_info spitz_pxafb_modes[] = अणु
	अणु
		.pixघड़ी       = 19231,
		.xres           = 480,
		.yres           = 640,
		.bpp            = 16,
		.hsync_len      = 40,
		.left_margin    = 46,
		.right_margin   = 125,
		.vsync_len      = 3,
		.upper_margin   = 1,
		.lower_margin   = 0,
		.sync           = 0,
	पूर्ण, अणु
		.pixघड़ी       = 134617,
		.xres           = 240,
		.yres           = 320,
		.bpp            = 16,
		.hsync_len      = 20,
		.left_margin    = 20,
		.right_margin   = 46,
		.vsync_len      = 2,
		.upper_margin   = 1,
		.lower_margin   = 0,
		.sync           = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info spitz_pxafb_info = अणु
	.modes          = spitz_pxafb_modes,
	.num_modes      = ARRAY_SIZE(spitz_pxafb_modes),
	.fixed_modes    = 1,
	.lcd_conn	= LCD_COLOR_TFT_16BPP | LCD_ALTERNATE_MAPPING,
पूर्ण;

अटल व्योम __init spitz_lcd_init(व्योम)
अणु
	pxa_set_fb_info(शून्य, &spitz_pxafb_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_lcd_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * न_अंकD Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_न_अंकD_SHARPSL) || defined(CONFIG_MTD_न_अंकD_SHARPSL_MODULE)
अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff, 0xff पूर्ण;

अटल काष्ठा nand_bbt_descr spitz_nand_bbt = अणु
	.options	= 0,
	.offs		= 4,
	.len		= 2,
	.pattern	= scan_ff_pattern
पूर्ण;

अटल पूर्णांक akita_ooblayout_ecc(काष्ठा mtd_info *mtd, पूर्णांक section,
			       काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section > 12)
		वापस -दुस्फल;

	चयन (section % 3) अणु
	हाल 0:
		oobregion->offset = 5;
		oobregion->length = 1;
		अवरोध;

	हाल 1:
		oobregion->offset = 1;
		oobregion->length = 3;
		अवरोध;

	हाल 2:
		oobregion->offset = 6;
		oobregion->length = 2;
		अवरोध;
	पूर्ण

	oobregion->offset += (section / 3) * 0x10;

	वापस 0;
पूर्ण

अटल पूर्णांक akita_ooblayout_मुक्त(काष्ठा mtd_info *mtd, पूर्णांक section,
				काष्ठा mtd_oob_region *oobregion)
अणु
	अगर (section)
		वापस -दुस्फल;

	oobregion->offset = 8;
	oobregion->length = 9;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mtd_ooblayout_ops akita_ooblayout_ops = अणु
	.ecc = akita_ooblayout_ecc,
	.मुक्त = akita_ooblayout_मुक्त,
पूर्ण;

अटल स्थिर अक्षर * स्थिर probes[] = अणु
	"cmdlinepart",
	"ofpart",
	"sharpslpart",
	शून्य,
पूर्ण;

अटल काष्ठा sharpsl_nand_platक्रमm_data spitz_nand_pdata = अणु
	.badblock_pattern	= &spitz_nand_bbt,
	.part_parsers		= probes,
पूर्ण;

अटल काष्ठा resource spitz_nand_resources[] = अणु
	अणु
		.start	= PXA_CS3_PHYS,
		.end	= PXA_CS3_PHYS + SZ_4K - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device spitz_nand_device = अणु
	.name		= "sharpsl-nand",
	.id		= -1,
	.resource	= spitz_nand_resources,
	.num_resources	= ARRAY_SIZE(spitz_nand_resources),
	.dev		= अणु
		.platक्रमm_data	= &spitz_nand_pdata,
	पूर्ण
पूर्ण;

अटल व्योम __init spitz_nand_init(व्योम)
अणु
	अगर (machine_is_akita() || machine_is_borzoi()) अणु
		spitz_nand_bbt.len = 1;
		spitz_nand_pdata.ecc_layout = &akita_ooblayout_ops;
	पूर्ण

	platक्रमm_device_रेजिस्टर(&spitz_nand_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_nand_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * NOR Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_PHYSMAP) || defined(CONFIG_MTD_PHYSMAP_MODULE)
अटल काष्ठा mtd_partition spitz_rom_parts[] = अणु
	अणु
		.name	="Boot PROM Filesystem",
		.offset	= 0x00140000,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data spitz_rom_data = अणु
	.width		= 2,
	.nr_parts	= ARRAY_SIZE(spitz_rom_parts),
	.parts		= spitz_rom_parts,
पूर्ण;

अटल काष्ठा resource spitz_rom_resources[] = अणु
	अणु
		.start	= PXA_CS0_PHYS,
		.end	= PXA_CS0_PHYS + SZ_8M - 1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device spitz_rom_device = अणु
	.name		= "physmap-flash",
	.id		= -1,
	.resource	= spitz_rom_resources,
	.num_resources	= ARRAY_SIZE(spitz_rom_resources),
	.dev		= अणु
		.platक्रमm_data	= &spitz_rom_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init spitz_nor_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&spitz_rom_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_nor_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * I2C devices
 ******************************************************************************/
#अगर defined(CONFIG_I2C_PXA) || defined(CONFIG_I2C_PXA_MODULE)
अटल काष्ठा pca953x_platक्रमm_data akita_pca953x_pdata = अणु
	.gpio_base		= AKITA_IOEXP_GPIO_BASE,
पूर्ण;

अटल काष्ठा i2c_board_info spitz_i2c_devs[] = अणु
	अणु
		.type		= "wm8750",
		.addr		= 0x1b,
	पूर्ण, अणु
		.type		= "max7310",
		.addr		= 0x18,
		.platक्रमm_data	= &akita_pca953x_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा regulator_consumer_supply isl6271a_consumers[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data isl6271a_info[] = अणु
	अणु
		.स्थिरraपूर्णांकs = अणु
			.name		= "vcc_core range",
			.min_uV		= 850000,
			.max_uV		= 1600000,
			.always_on	= 1,
			.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
		पूर्ण,
	.consumer_supplies	= isl6271a_consumers,
	.num_consumer_supplies	= ARRAY_SIZE(isl6271a_consumers),
	पूर्ण
पूर्ण;

अटल काष्ठा i2c_board_info spitz_pi2c_devs[] = अणु
	अणु
		.type		= "isl6271a",
		.addr		= 0x0c,
		.platक्रमm_data	= &isl6271a_info,
	पूर्ण,
पूर्ण;

अटल व्योम __init spitz_i2c_init(व्योम)
अणु
	पूर्णांक size = ARRAY_SIZE(spitz_i2c_devs);

	/* Only Akita has the max7310 chip */
	अगर (!machine_is_akita())
		size--;

	pxa_set_i2c_info(शून्य);
	pxa27x_set_i2c_घातer_info(शून्य);
	i2c_रेजिस्टर_board_info(0, spitz_i2c_devs, size);
	i2c_रेजिस्टर_board_info(1, ARRAY_AND_SIZE(spitz_pi2c_devs));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम spitz_i2c_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Audio devices
 ******************************************************************************/
अटल अंतरभूत व्योम spitz_audio_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर_simple("spitz-audio", -1, शून्य, 0);
पूर्ण

/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल व्योम spitz_घातeroff(व्योम)
अणु
	pxa_restart(REBOOT_GPIO, शून्य);
पूर्ण

अटल व्योम spitz_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	uपूर्णांक32_t msc0 = __raw_पढ़ोl(MSC0);
	/* Bootloader magic क्रम a reboot */
	अगर ((msc0 & 0xffff0000) == 0x7ff00000)
		__raw_ग_लिखोl((msc0 & 0xffff) | 0x7ee00000, MSC0);

	spitz_घातeroff();
पूर्ण

अटल व्योम __init spitz_init(व्योम)
अणु
	init_gpio_reset(SPITZ_GPIO_ON_RESET, 1, 0);
	pm_घातer_off = spitz_घातeroff;

	PMCR = 0x00;

	/* Stop 3.6MHz and drive HIGH to PCMCIA and CS */
	PCFR |= PCFR_OPDE;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(spitz_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	spitz_spi_init();
	spitz_scoop_init();
	spitz_mkp_init();
	spitz_keys_init();
	spitz_leds_init();
	spitz_mmc_init();
	spitz_pcmcia_init();
	spitz_irda_init();
	spitz_uhc_init();
	spitz_lcd_init();
	spitz_nor_init();
	spitz_nand_init();
	spitz_i2c_init();
	spitz_audio_init();

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

अटल व्योम __init spitz_fixup(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	sharpsl_save_param();
	memblock_add(0xa0000000, SZ_64M);
पूर्ण

#अगर_घोषित CONFIG_MACH_SPITZ
MACHINE_START(SPITZ, "SHARP Spitz")
	.fixup		= spitz_fixup,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_machine	= spitz_init,
	.init_समय	= pxa_समयr_init,
	.restart	= spitz_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_BORZOI
MACHINE_START(BORZOI, "SHARP Borzoi")
	.fixup		= spitz_fixup,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_machine	= spitz_init,
	.init_समय	= pxa_समयr_init,
	.restart	= spitz_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_AKITA
MACHINE_START(AKITA, "SHARP Akita")
	.fixup		= spitz_fixup,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_machine	= spitz_init,
	.init_समय	= pxa_समयr_init,
	.restart	= spitz_restart,
MACHINE_END
#पूर्ण_अगर
