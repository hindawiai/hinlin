<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम Sharp SL-C7xx PDAs
 * Models: SL-C700 (Corgi), SL-C750 (Shepherd), SL-C760 (Husky)
 *
 * Copyright (c) 2004-2005 Riअक्षरd Purdie
 *
 * Based on Sharp's 2.4 kernel patches/lubbock.c
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>	/* symbol_get ; symbol_put */
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/pm.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/backlight.h>
#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/पन.स>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/spi/corgi_lcd.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/mtd/sharpsl.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/memblock.h>
#समावेश <video/w100fb.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "pxa25x.h"
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "udc.h"
#समावेश <mach/corgi.h>
#समावेश "sharpsl_pm.h"

#समावेश <यंत्र/mach/sharpsl_param.h>
#समावेश <यंत्र/hardware/scoop.h>

#समावेश "generic.h"
#समावेश "devices.h"

अटल अचिन्हित दीर्घ corgi_pin_config[] __initdata = अणु
	/* Static Memory I/O */
	GPIO78_nCS_2,	/* w100fb */
	GPIO80_nCS_4,	/* scoop */

	/* SSP1 */
	GPIO23_SSP1_SCLK,
	GPIO25_SSP1_TXD,
	GPIO26_SSP1_RXD,
	GPIO24_GPIO,	/* CORGI_GPIO_ADS7846_CS - SFRM as chip select */

	/* I2S */
	GPIO28_I2S_BITCLK_OUT,
	GPIO29_I2S_SDATA_IN,
	GPIO30_I2S_SDATA_OUT,
	GPIO31_I2S_SYNC,
	GPIO32_I2S_SYSCLK,

	/* Infra-Red */
	GPIO47_FICP_TXD,
	GPIO46_FICP_RXD,

	/* FFUART */
	GPIO40_FFUART_DTR,
	GPIO41_FFUART_RTS,
	GPIO39_FFUART_TXD,
	GPIO37_FFUART_DSR,
	GPIO34_FFUART_RXD,
	GPIO35_FFUART_CTS,

	/* PC Card */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO52_nPCE_1,
	GPIO53_nPCE_2,
	GPIO54_nPSKTSEL,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,

	/* MMC */
	GPIO6_MMC_CLK,
	GPIO8_MMC_CS0,

	/* GPIO Matrix Keypad */
	GPIO66_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 0 */
	GPIO67_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 1 */
	GPIO68_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 2 */
	GPIO69_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 3 */
	GPIO70_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 4 */
	GPIO71_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 5 */
	GPIO72_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 6 */
	GPIO73_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 7 */
	GPIO74_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 8 */
	GPIO75_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 9 */
	GPIO76_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 10 */
	GPIO77_GPIO | MFP_LPM_DRIVE_HIGH,	/* column 11 */
	GPIO58_GPIO,	/* row 0 */
	GPIO59_GPIO,	/* row 1 */
	GPIO60_GPIO,	/* row 2 */
	GPIO61_GPIO,	/* row 3 */
	GPIO62_GPIO,	/* row 4 */
	GPIO63_GPIO,	/* row 5 */
	GPIO64_GPIO,	/* row 6 */
	GPIO65_GPIO,	/* row 7 */

	/* GPIO */
	GPIO9_GPIO,				/* CORGI_GPIO_nSD_DETECT */
	GPIO7_GPIO,				/* CORGI_GPIO_nSD_WP */
	GPIO11_GPIO | WAKEUP_ON_EDGE_BOTH,	/* CORGI_GPIO_MAIN_BAT_अणुLOW,COVERपूर्ण */
	GPIO13_GPIO | MFP_LPM_KEEP_OUTPUT,	/* CORGI_GPIO_LED_ORANGE */
	GPIO21_GPIO,				/* CORGI_GPIO_ADC_TEMP */
	GPIO22_GPIO,				/* CORGI_GPIO_IR_ON */
	GPIO33_GPIO,				/* CORGI_GPIO_SD_PWR */
	GPIO38_GPIO | MFP_LPM_KEEP_OUTPUT,	/* CORGI_GPIO_CHRG_ON */
	GPIO43_GPIO | MFP_LPM_KEEP_OUTPUT,	/* CORGI_GPIO_CHRG_UKN */
	GPIO44_GPIO,				/* CORGI_GPIO_HSYNC */

	GPIO0_GPIO | WAKEUP_ON_EDGE_BOTH,	/* CORGI_GPIO_KEY_INT */
	GPIO1_GPIO | WAKEUP_ON_EDGE_RISE,	/* CORGI_GPIO_AC_IN */
	GPIO3_GPIO | WAKEUP_ON_EDGE_BOTH,	/* CORGI_GPIO_WAKEUP */
पूर्ण;

/*
 * Corgi SCOOP Device
 */
अटल काष्ठा resource corgi_scoop_resources[] = अणु
	[0] = अणु
		.start		= 0x10800000,
		.end		= 0x10800fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा scoop_config corgi_scoop_setup = अणु
	.io_dir 	= CORGI_SCOOP_IO_सूची,
	.io_out		= CORGI_SCOOP_IO_OUT,
	.gpio_base	= CORGI_SCOOP_GPIO_BASE,
पूर्ण;

काष्ठा platक्रमm_device corgiscoop_device = अणु
	.name		= "sharp-scoop",
	.id		= -1,
	.dev		= अणु
 		.platक्रमm_data	= &corgi_scoop_setup,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(corgi_scoop_resources),
	.resource	= corgi_scoop_resources,
पूर्ण;

अटल काष्ठा scoop_pcmcia_dev corgi_pcmcia_scoop[] = अणु
अणु
	.dev        = &corgiscoop_device.dev,
	.irq        = CORGI_IRQ_GPIO_CF_IRQ,
	.cd_irq     = CORGI_IRQ_GPIO_CF_CD,
	.cd_irq_str = "PCMCIA0 CD",
पूर्ण,
पूर्ण;

अटल काष्ठा scoop_pcmcia_config corgi_pcmcia_config = अणु
	.devs         = &corgi_pcmcia_scoop[0],
	.num_devs     = 1,
पूर्ण;

अटल काष्ठा w100_mem_info corgi_fb_mem = अणु
	.ext_cntl          = 0x00040003,
	.sdram_mode_reg    = 0x00650021,
	.ext_timing_cntl   = 0x10002a4a,
	.io_cntl           = 0x7ff87012,
	.size              = 0x1fffff,
पूर्ण;

अटल काष्ठा w100_gen_regs corgi_fb_regs = अणु
	.lcd_क्रमmat    = 0x00000003,
	.lcdd_cntl1    = 0x01CC0000,
	.lcdd_cntl2    = 0x0003FFFF,
	.genlcd_cntl1  = 0x00FFFF0D,
	.genlcd_cntl2  = 0x003F3003,
	.genlcd_cntl3  = 0x000102aa,
पूर्ण;

अटल काष्ठा w100_gpio_regs corgi_fb_gpio = अणु
	.init_data1   = 0x000000bf,
	.init_data2   = 0x00000000,
	.gpio_dir1    = 0x00000000,
	.gpio_oe1     = 0x03c0feff,
	.gpio_dir2    = 0x00000000,
	.gpio_oe2     = 0x00000000,
पूर्ण;

अटल काष्ठा w100_mode corgi_fb_modes[] = अणु
अणु
	.xres            = 480,
	.yres            = 640,
	.left_margin     = 0x56,
	.right_margin    = 0x55,
	.upper_margin    = 0x03,
	.lower_margin    = 0x00,
	.crtc_ss         = 0x82360056,
	.crtc_ls         = 0xA0280000,
	.crtc_gs         = 0x80280028,
	.crtc_vpos_gs    = 0x02830002,
	.crtc_rev        = 0x00400008,
	.crtc_dclk       = 0xA0000000,
	.crtc_gclk       = 0x8015010F,
	.crtc_goe        = 0x80100110,
	.crtc_ps1_active = 0x41060010,
	.pll_freq        = 75,
	.fast_pll_freq   = 100,
	.sysclk_src      = CLK_SRC_PLL,
	.sysclk_भागider  = 0,
	.pixclk_src      = CLK_SRC_PLL,
	.pixclk_भागider  = 2,
	.pixclk_भागider_rotated = 6,
पूर्ण,अणु
	.xres            = 240,
	.yres            = 320,
	.left_margin     = 0x27,
	.right_margin    = 0x2e,
	.upper_margin    = 0x01,
	.lower_margin    = 0x00,
	.crtc_ss         = 0x81170027,
	.crtc_ls         = 0xA0140000,
	.crtc_gs         = 0xC0140014,
	.crtc_vpos_gs    = 0x00010141,
	.crtc_rev        = 0x00400008,
	.crtc_dclk       = 0xA0000000,
	.crtc_gclk       = 0x8015010F,
	.crtc_goe        = 0x80100110,
	.crtc_ps1_active = 0x41060010,
	.pll_freq        = 0,
	.fast_pll_freq   = 0,
	.sysclk_src      = CLK_SRC_XTAL,
	.sysclk_भागider  = 0,
	.pixclk_src      = CLK_SRC_XTAL,
	.pixclk_भागider  = 1,
	.pixclk_भागider_rotated = 1,
पूर्ण,

पूर्ण;

अटल काष्ठा w100fb_mach_info corgi_fb_info = अणु
	.init_mode  = INIT_MODE_ROTATED,
	.mem        = &corgi_fb_mem,
	.regs       = &corgi_fb_regs,
	.modelist   = &corgi_fb_modes[0],
	.num_modes  = 2,
	.gpio       = &corgi_fb_gpio,
	.xtal_freq  = 12500000,
	.xtal_dbl   = 0,
पूर्ण;

अटल काष्ठा resource corgi_fb_resources[] = अणु
	[0] = अणु
		.start   = 0x08000000,
		.end     = 0x08ffffff,
		.flags   = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device corgअगरb_device = अणु
	.name           = "w100fb",
	.id             = -1,
	.num_resources	= ARRAY_SIZE(corgi_fb_resources),
	.resource	= corgi_fb_resources,
	.dev            = अणु
		.platक्रमm_data = &corgi_fb_info,
	पूर्ण,

पूर्ण;

/*
 * Corgi Keyboard Device
 */
#घोषणा CORGI_KEY_CALENDER	KEY_F1
#घोषणा CORGI_KEY_ADDRESS	KEY_F2
#घोषणा CORGI_KEY_FN		KEY_F3
#घोषणा CORGI_KEY_CANCEL	KEY_F4
#घोषणा CORGI_KEY_OFF		KEY_SUSPEND
#घोषणा CORGI_KEY_EXOK		KEY_F5
#घोषणा CORGI_KEY_EXCANCEL	KEY_F6
#घोषणा CORGI_KEY_EXJOGDOWN	KEY_F7
#घोषणा CORGI_KEY_EXJOGUP	KEY_F8
#घोषणा CORGI_KEY_JAP1		KEY_LEFTCTRL
#घोषणा CORGI_KEY_JAP2		KEY_LEFTALT
#घोषणा CORGI_KEY_MAIL		KEY_F10
#घोषणा CORGI_KEY_OK		KEY_F11
#घोषणा CORGI_KEY_MENU		KEY_F12

अटल स्थिर uपूर्णांक32_t corgikbd_keymap[] = अणु
	KEY(0, 1, KEY_1),
	KEY(0, 2, KEY_3),
	KEY(0, 3, KEY_5),
	KEY(0, 4, KEY_6),
	KEY(0, 5, KEY_7),
	KEY(0, 6, KEY_9),
	KEY(0, 7, KEY_0),
	KEY(0, 8, KEY_BACKSPACE),
	KEY(1, 1, KEY_2),
	KEY(1, 2, KEY_4),
	KEY(1, 3, KEY_R),
	KEY(1, 4, KEY_Y),
	KEY(1, 5, KEY_8),
	KEY(1, 6, KEY_I),
	KEY(1, 7, KEY_O),
	KEY(1, 8, KEY_P),
	KEY(2, 0, KEY_TAB),
	KEY(2, 1, KEY_Q),
	KEY(2, 2, KEY_E),
	KEY(2, 3, KEY_T),
	KEY(2, 4, KEY_G),
	KEY(2, 5, KEY_U),
	KEY(2, 6, KEY_J),
	KEY(2, 7, KEY_K),
	KEY(3, 0, CORGI_KEY_CALENDER),
	KEY(3, 1, KEY_W),
	KEY(3, 2, KEY_S),
	KEY(3, 3, KEY_F),
	KEY(3, 4, KEY_V),
	KEY(3, 5, KEY_H),
	KEY(3, 6, KEY_M),
	KEY(3, 7, KEY_L),
	KEY(3, 9, KEY_RIGHTSHIFT),
	KEY(4, 0, CORGI_KEY_ADDRESS),
	KEY(4, 1, KEY_A),
	KEY(4, 2, KEY_D),
	KEY(4, 3, KEY_C),
	KEY(4, 4, KEY_B),
	KEY(4, 5, KEY_N),
	KEY(4, 6, KEY_DOT),
	KEY(4, 8, KEY_ENTER),
	KEY(4, 10, KEY_LEFTSHIFT),
	KEY(5, 0, CORGI_KEY_MAIL),
	KEY(5, 1, KEY_Z),
	KEY(5, 2, KEY_X),
	KEY(5, 3, KEY_MINUS),
	KEY(5, 4, KEY_SPACE),
	KEY(5, 5, KEY_COMMA),
	KEY(5, 7, KEY_UP),
	KEY(5, 11, CORGI_KEY_FN),
	KEY(6, 0, KEY_SYSRQ),
	KEY(6, 1, CORGI_KEY_JAP1),
	KEY(6, 2, CORGI_KEY_JAP2),
	KEY(6, 3, CORGI_KEY_CANCEL),
	KEY(6, 4, CORGI_KEY_OK),
	KEY(6, 5, CORGI_KEY_MENU),
	KEY(6, 6, KEY_LEFT),
	KEY(6, 7, KEY_DOWN),
	KEY(6, 8, KEY_RIGHT),
	KEY(7, 0, CORGI_KEY_OFF),
	KEY(7, 1, CORGI_KEY_EXOK),
	KEY(7, 2, CORGI_KEY_EXCANCEL),
	KEY(7, 3, CORGI_KEY_EXJOGDOWN),
	KEY(7, 4, CORGI_KEY_EXJOGUP),
पूर्ण;

अटल काष्ठा matrix_keymap_data corgikbd_keymap_data = अणु
	.keymap		= corgikbd_keymap,
	.keymap_size	= ARRAY_SIZE(corgikbd_keymap),
पूर्ण;

अटल स्थिर पूर्णांक corgikbd_row_gpios[] =
		अणु 58, 59, 60, 61, 62, 63, 64, 65 पूर्ण;
अटल स्थिर पूर्णांक corgikbd_col_gpios[] =
		अणु 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77 पूर्ण;

अटल काष्ठा matrix_keypad_platक्रमm_data corgikbd_pdata = अणु
	.keymap_data		= &corgikbd_keymap_data,
	.row_gpios		= corgikbd_row_gpios,
	.col_gpios		= corgikbd_col_gpios,
	.num_row_gpios		= ARRAY_SIZE(corgikbd_row_gpios),
	.num_col_gpios		= ARRAY_SIZE(corgikbd_col_gpios),
	.col_scan_delay_us	= 10,
	.debounce_ms		= 10,
	.wakeup			= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device corgikbd_device = अणु
	.name		= "matrix-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &corgikbd_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_button corgi_gpio_keys[] = अणु
	अणु
		.type	= EV_SW,
		.code	= SW_LID,
		.gpio	= CORGI_GPIO_SWA,
		.desc	= "Lid close switch",
		.debounce_पूर्णांकerval = 500,
	पूर्ण,
	अणु
		.type	= EV_SW,
		.code	= SW_TABLET_MODE,
		.gpio	= CORGI_GPIO_SWB,
		.desc	= "Tablet mode switch",
		.debounce_पूर्णांकerval = 500,
	पूर्ण,
	अणु
		.type	= EV_SW,
		.code	= SW_HEADPHONE_INSERT,
		.gpio	= CORGI_GPIO_AK_INT,
		.desc	= "HeadPhone insert",
		.debounce_पूर्णांकerval = 500,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data corgi_gpio_keys_platक्रमm_data = अणु
	.buttons	= corgi_gpio_keys,
	.nbuttons	= ARRAY_SIZE(corgi_gpio_keys),
	.poll_पूर्णांकerval	= 250,
पूर्ण;

अटल काष्ठा platक्रमm_device corgi_gpio_keys_device = अणु
	.name	= "gpio-keys-polled",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &corgi_gpio_keys_platक्रमm_data,
	पूर्ण,
पूर्ण;

/*
 * Corgi LEDs
 */
अटल काष्ठा gpio_led corgi_gpio_leds[] = अणु
	अणु
		.name			= "corgi:amber:charge",
		.शेष_trigger	= "sharpsl-charge",
		.gpio			= CORGI_GPIO_LED_ORANGE,
	पूर्ण,
	अणु
		.name			= "corgi:green:mail",
		.शेष_trigger	= "nand-disk",
		.gpio			= CORGI_GPIO_LED_GREEN,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data corgi_gpio_leds_info = अणु
	.leds		= corgi_gpio_leds,
	.num_leds	= ARRAY_SIZE(corgi_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device corgiled_device = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &corgi_gpio_leds_info,
	पूर्ण,
पूर्ण;

/*
 * Corgi Audio
 */
अटल काष्ठा platक्रमm_device corgi_audio_device = अणु
	.name	= "corgi-audio",
	.id	= -1,
पूर्ण;

/*
 * MMC/SD Device
 *
 * The card detect पूर्णांकerrupt isn't debounced so we delay it by 250ms
 * to give the card a chance to fully insert/eject.
 */
अटल काष्ठा pxamci_platक्रमm_data corgi_mci_platक्रमm_data = अणु
	.detect_delay_ms	= 250,
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table corgi_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		/* Card detect on GPIO 9 */
		GPIO_LOOKUP("gpio-pxa", CORGI_GPIO_nSD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		/* Write protect on GPIO 7 */
		GPIO_LOOKUP("gpio-pxa", CORGI_GPIO_nSD_WP,
			    "wp", GPIO_ACTIVE_LOW),
		/* Power on GPIO 33 */
		GPIO_LOOKUP("gpio-pxa", CORGI_GPIO_SD_PWR,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * Irda
 */
अटल काष्ठा pxaficp_platक्रमm_data corgi_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= CORGI_GPIO_IR_ON,
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
पूर्ण;


/*
 * USB Device Controller
 */
अटल काष्ठा pxa2xx_udc_mach_info udc_info __initdata = अणु
	/* no connect GPIO; corgi can't tell connection status */
	.gpio_pullup		= CORGI_GPIO_USB_PULLUP,
पूर्ण;

#अगर IS_ENABLED(CONFIG_SPI_PXA2XX)
अटल काष्ठा pxa2xx_spi_controller corgi_spi_info = अणु
	.num_chipselect	= 3,
पूर्ण;

अटल व्योम corgi_रुको_क्रम_hsync(व्योम)
अणु
	जबतक (gpio_get_value(CORGI_GPIO_HSYNC))
		cpu_relax();

	जबतक (!gpio_get_value(CORGI_GPIO_HSYNC))
		cpu_relax();
पूर्ण

अटल काष्ठा ads7846_platक्रमm_data corgi_ads7846_info = अणु
	.model			= 7846,
	.vref_delay_usecs	= 100,
	.x_plate_ohms		= 419,
	.y_plate_ohms		= 486,
	.gpio_penकरोwn		= CORGI_GPIO_TP_INT,
	.रुको_क्रम_sync		= corgi_रुको_क्रम_hsync,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip corgi_ads7846_chip = अणु
	.gpio_cs	= CORGI_GPIO_ADS7846_CS,
पूर्ण;

अटल व्योम corgi_bl_kick_battery(व्योम)
अणु
	व्योम (*kick_batt)(व्योम);

	kick_batt = symbol_get(sharpsl_battery_kick);
	अगर (kick_batt) अणु
		kick_batt();
		symbol_put(sharpsl_battery_kick);
	पूर्ण
पूर्ण

अटल काष्ठा gpiod_lookup_table corgi_lcdcon_gpio_table = अणु
	.dev_id = "spi1.1",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", CORGI_GPIO_BACKLIGHT_CONT,
			    "BL_CONT", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा corgi_lcd_platक्रमm_data corgi_lcdcon_info = अणु
	.init_mode		= CORGI_LCD_MODE_VGA,
	.max_पूर्णांकensity		= 0x2f,
	.शेष_पूर्णांकensity	= 0x1f,
	.limit_mask		= 0x0b,
	.kick_battery		= corgi_bl_kick_battery,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip corgi_lcdcon_chip = अणु
	.gpio_cs	= CORGI_GPIO_LCDCON_CS,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip corgi_max1111_chip = अणु
	.gpio_cs	= CORGI_GPIO_MAX1111_CS,
पूर्ण;

अटल काष्ठा spi_board_info corgi_spi_devices[] = अणु
	अणु
		.modalias	= "ads7846",
		.max_speed_hz	= 1200000,
		.bus_num	= 1,
		.chip_select	= 0,
		.platक्रमm_data	= &corgi_ads7846_info,
		.controller_data= &corgi_ads7846_chip,
		.irq		= PXA_GPIO_TO_IRQ(CORGI_GPIO_TP_INT),
	पूर्ण, अणु
		.modalias	= "corgi-lcd",
		.max_speed_hz	= 50000,
		.bus_num	= 1,
		.chip_select	= 1,
		.platक्रमm_data	= &corgi_lcdcon_info,
		.controller_data= &corgi_lcdcon_chip,
	पूर्ण, अणु
		.modalias	= "max1111",
		.max_speed_hz	= 450000,
		.bus_num	= 1,
		.chip_select	= 2,
		.controller_data= &corgi_max1111_chip,
	पूर्ण,
पूर्ण;

अटल व्योम __init corgi_init_spi(व्योम)
अणु
	pxa2xx_set_spi_info(1, &corgi_spi_info);
	gpiod_add_lookup_table(&corgi_lcdcon_gpio_table);
	spi_रेजिस्टर_board_info(ARRAY_AND_SIZE(corgi_spi_devices));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम corgi_init_spi(व्योम) अणुपूर्ण
#पूर्ण_अगर

अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff, 0xff पूर्ण;

अटल काष्ठा nand_bbt_descr sharpsl_bbt = अणु
	.options = 0,
	.offs = 4,
	.len = 2,
	.pattern = scan_ff_pattern
पूर्ण;

अटल स्थिर अक्षर * स्थिर probes[] = अणु
	"cmdlinepart",
	"ofpart",
	"sharpslpart",
	शून्य,
पूर्ण;

अटल काष्ठा sharpsl_nand_platक्रमm_data sharpsl_nand_platक्रमm_data = अणु
	.badblock_pattern	= &sharpsl_bbt,
	.part_parsers		= probes,
पूर्ण;

अटल काष्ठा resource sharpsl_nand_resources[] = अणु
	अणु
		.start	= 0x0C000000,
		.end	= 0x0C000FFF,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sharpsl_nand_device = अणु
	.name		= "sharpsl-nand",
	.id		= -1,
	.resource	= sharpsl_nand_resources,
	.num_resources	= ARRAY_SIZE(sharpsl_nand_resources),
	.dev.platक्रमm_data	= &sharpsl_nand_platक्रमm_data,
पूर्ण;

अटल काष्ठा mtd_partition sharpsl_rom_parts[] = अणु
	अणु
		.name	="Boot PROM Filesystem",
		.offset	= 0x00120000,
		.size	= MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा physmap_flash_data sharpsl_rom_data = अणु
	.width		= 2,
	.nr_parts	= ARRAY_SIZE(sharpsl_rom_parts),
	.parts		= sharpsl_rom_parts,
पूर्ण;

अटल काष्ठा resource sharpsl_rom_resources[] = अणु
	अणु
		.start	= 0x00000000,
		.end	= 0x007fffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device sharpsl_rom_device = अणु
	.name	= "physmap-flash",
	.id	= -1,
	.resource = sharpsl_rom_resources,
	.num_resources = ARRAY_SIZE(sharpsl_rom_resources),
	.dev.platक्रमm_data = &sharpsl_rom_data,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&corgiscoop_device,
	&corgअगरb_device,
	&corgi_gpio_keys_device,
	&corgikbd_device,
	&corgiled_device,
	&corgi_audio_device,
	&sharpsl_nand_device,
	&sharpsl_rom_device,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata corgi_i2c_devices[] = अणु
	अणु I2C_BOARD_INFO("wm8731", 0x1b) पूर्ण,
पूर्ण;

अटल व्योम corgi_घातeroff(व्योम)
अणु
	अगर (!machine_is_corgi())
		/* Green LED off tells the bootloader to halt */
		gpio_set_value(CORGI_GPIO_LED_GREEN, 0);

	pxa_restart(REBOOT_HARD, शून्य);
पूर्ण

अटल व्योम corgi_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	अगर (!machine_is_corgi())
		/* Green LED on tells the bootloader to reboot */
		gpio_set_value(CORGI_GPIO_LED_GREEN, 1);

	pxa_restart(REBOOT_HARD, cmd);
पूर्ण

अटल व्योम __init corgi_init(व्योम)
अणु
	pm_घातer_off = corgi_घातeroff;

	/* Stop 3.6MHz and drive HIGH to PCMCIA and CS */
	PCFR |= PCFR_OPDE;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(corgi_pin_config));

	/* allow wakeup from various GPIOs */
	gpio_set_wake(CORGI_GPIO_KEY_INT, 1);
	gpio_set_wake(CORGI_GPIO_WAKEUP, 1);
	gpio_set_wake(CORGI_GPIO_AC_IN, 1);
	gpio_set_wake(CORGI_GPIO_CHRG_FULL, 1);

	अगर (!machine_is_corgi())
		gpio_set_wake(CORGI_GPIO_MAIN_BAT_LOW, 1);

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	corgi_init_spi();

 	pxa_set_udc_info(&udc_info);
	gpiod_add_lookup_table(&corgi_mci_gpio_table);
	pxa_set_mci_info(&corgi_mci_platक्रमm_data);
	pxa_set_ficp_info(&corgi_ficp_platक्रमm_data);
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(corgi_i2c_devices));

	platक्रमm_scoop_config = &corgi_pcmcia_config;

	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

अटल व्योम __init fixup_corgi(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	sharpsl_save_param();
	अगर (machine_is_corgi())
		memblock_add(0xa0000000, SZ_32M);
	अन्यथा
		memblock_add(0xa0000000, SZ_64M);
पूर्ण

#अगर_घोषित CONFIG_MACH_CORGI
MACHINE_START(CORGI, "SHARP Corgi")
	.fixup		= fixup_corgi,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_machine	= corgi_init,
	.init_समय	= pxa_समयr_init,
	.restart	= corgi_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_SHEPHERD
MACHINE_START(SHEPHERD, "SHARP Shepherd")
	.fixup		= fixup_corgi,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_machine	= corgi_init,
	.init_समय	= pxa_समयr_init,
	.restart	= corgi_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_HUSKY
MACHINE_START(HUSKY, "SHARP Husky")
	.fixup		= fixup_corgi,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.init_machine	= corgi_init,
	.init_समय	= pxa_समयr_init,
	.restart	= corgi_restart,
MACHINE_END
#पूर्ण_अगर

