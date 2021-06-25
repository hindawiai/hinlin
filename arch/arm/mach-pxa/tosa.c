<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  Support क्रम Sharp SL-C6000x PDAs
 *  Model: (Tosa)
 *
 *  Copyright (c) 2005 Dirk Opfer
 *
 *	Based on code written by Sharp/Lineo क्रम 2.4 kernels
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/major.h>
#समावेश <linux/fs.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/mmc/host.h>
#समावेश <linux/mfd/tc6393xb.h>
#समावेश <linux/mfd/पंचांगपन.स>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/pm.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/घातer/gpio-अक्षरger.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/input/matrix_keypad.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>
#समावेश <linux/reboot.h>
#समावेश <linux/memblock.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "pxa25x.h"
#समावेश <mach/reset.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश "udc.h"
#समावेश "tosa_bt.h"
#समावेश <mach/audपन.स>
#समावेश <mach/smemc.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <mach/tosa.h>

#समावेश <यंत्र/hardware/scoop.h>
#समावेश <यंत्र/mach/sharpsl_param.h>

#समावेश "generic.h"
#समावेश "devices.h"

अटल अचिन्हित दीर्घ tosa_pin_config[] = अणु
	GPIO78_nCS_2, /* Scoop */
	GPIO80_nCS_4, /* tg6393xb */
	GPIO33_nCS_5, /* Scoop */

	// GPIO76 CARD_VCC_ON1

	GPIO19_GPIO, /* Reset out */
	GPIO1_RST | WAKEUP_ON_EDGE_FALL,

	GPIO0_GPIO | WAKEUP_ON_EDGE_FALL, /* WAKE_UP */
	GPIO2_GPIO | WAKEUP_ON_EDGE_BOTH, /* AC_IN */
	GPIO3_GPIO | WAKEUP_ON_EDGE_FALL, /* RECORD */
	GPIO4_GPIO | WAKEUP_ON_EDGE_FALL, /* SYNC */
	GPIO20_GPIO, /* EAR_IN */
	GPIO22_GPIO, /* On */

	GPIO5_GPIO, /* USB_IN */
	GPIO32_GPIO, /* Pen IRQ */

	GPIO7_GPIO, /* Jacket Detect */
	GPIO14_GPIO, /* BAT0_CRG */
	GPIO12_GPIO, /* BAT1_CRG */
	GPIO17_GPIO, /* BAT0_LOW */
	GPIO84_GPIO, /* BAT1_LOW */
	GPIO38_GPIO, /* BAT_LOCK */

	GPIO11_3_6MHz,
	GPIO15_GPIO, /* TC6393XB IRQ */
	GPIO18_RDY,
	GPIO27_GPIO, /* LCD Sync */

	/* MMC */
	GPIO6_MMC_CLK,
	GPIO8_MMC_CS0,
	GPIO9_GPIO, /* Detect */
	GPIO10_GPIO, /* nSD_INT */

	/* CF */
	GPIO13_GPIO, /* CD_IRQ */
	GPIO21_GPIO, /* Main Slot IRQ */
	GPIO36_GPIO, /* Jacket Slot IRQ */
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

	/* AC97 */
	GPIO31_AC97_SYNC,
	GPIO30_AC97_SDATA_OUT,
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	// GPIO79 nAUD_IRQ

	/* FFUART */
	GPIO34_FFUART_RXD,
	GPIO35_FFUART_CTS,
	GPIO37_FFUART_DSR,
	GPIO39_FFUART_TXD,
	GPIO40_FFUART_DTR,
	GPIO41_FFUART_RTS,

	/* BTUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,

	/* Keybd */
	GPIO58_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 0 */
	GPIO59_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 1 */
	GPIO60_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 2 */
	GPIO61_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 3 */
	GPIO62_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 4 */
	GPIO63_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 5 */
	GPIO64_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 6 */
	GPIO65_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 7 */
	GPIO66_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 8 */
	GPIO67_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 9 */
	GPIO68_GPIO | MFP_LPM_DRIVE_LOW,	/* Column 10 */
	GPIO69_GPIO | MFP_LPM_DRIVE_LOW,	/* Row 0 */
	GPIO70_GPIO | MFP_LPM_DRIVE_LOW,	/* Row 1 */
	GPIO71_GPIO | MFP_LPM_DRIVE_LOW,	/* Row 2 */
	GPIO72_GPIO | MFP_LPM_DRIVE_LOW,	/* Row 3 */
	GPIO73_GPIO | MFP_LPM_DRIVE_LOW,	/* Row 4 */
	GPIO74_GPIO | MFP_LPM_DRIVE_LOW,	/* Row 5 */
	GPIO75_GPIO | MFP_LPM_DRIVE_LOW,	/* Row 6 */

	/* SPI */
	GPIO81_SSP2_CLK_OUT,
	GPIO82_SSP2_FRM_OUT,
	GPIO83_SSP2_TXD,

	/* IrDA is managed in other way */
	GPIO46_GPIO,
	GPIO47_GPIO,
पूर्ण;

/*
 * SCOOP Device
 */
अटल काष्ठा resource tosa_scoop_resources[] = अणु
	[0] = अणु
		.start	= TOSA_CF_PHYS,
		.end	= TOSA_CF_PHYS + 0xfff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा scoop_config tosa_scoop_setup = अणु
	.io_dir 	= TOSA_SCOOP_IO_सूची,
	.gpio_base	= TOSA_SCOOP_GPIO_BASE,
पूर्ण;

अटल काष्ठा platक्रमm_device tosascoop_device = अणु
	.name		= "sharp-scoop",
	.id		= 0,
	.dev		= अणु
 		.platक्रमm_data	= &tosa_scoop_setup,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(tosa_scoop_resources),
	.resource	= tosa_scoop_resources,
पूर्ण;


/*
 * SCOOP Device Jacket
 */
अटल काष्ठा resource tosa_scoop_jc_resources[] = अणु
	[0] = अणु
		.start		= TOSA_SCOOP_PHYS + 0x40,
		.end		= TOSA_SCOOP_PHYS + 0xfff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा scoop_config tosa_scoop_jc_setup = अणु
	.io_dir 	= TOSA_SCOOP_JC_IO_सूची,
	.gpio_base	= TOSA_SCOOP_JC_GPIO_BASE,
पूर्ण;

अटल काष्ठा platक्रमm_device tosascoop_jc_device = अणु
	.name		= "sharp-scoop",
	.id		= 1,
	.dev		= अणु
 		.platक्रमm_data	= &tosa_scoop_jc_setup,
		.parent 	= &tosascoop_device.dev,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(tosa_scoop_jc_resources),
	.resource	= tosa_scoop_jc_resources,
पूर्ण;

/*
 * PCMCIA
 */
अटल काष्ठा scoop_pcmcia_dev tosa_pcmcia_scoop[] = अणु
अणु
	.dev        = &tosascoop_device.dev,
	.irq        = TOSA_IRQ_GPIO_CF_IRQ,
	.cd_irq     = TOSA_IRQ_GPIO_CF_CD,
	.cd_irq_str = "PCMCIA0 CD",
पूर्ण,अणु
	.dev        = &tosascoop_jc_device.dev,
	.irq        = TOSA_IRQ_GPIO_JC_CF_IRQ,
	.cd_irq     = -1,
पूर्ण,
पूर्ण;

अटल काष्ठा scoop_pcmcia_config tosa_pcmcia_config = अणु
	.devs         = &tosa_pcmcia_scoop[0],
	.num_devs     = 2,
पूर्ण;

/*
 * USB Device Controller
 */
अटल काष्ठा gpiod_lookup_table tosa_udc_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", TOSA_GPIO_USB_IN,
			    "vbus", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", TOSA_GPIO_USB_PULLUP,
			    "pullup", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device tosa_gpio_vbus = अणु
	.name	= "gpio-vbus",
	.id	= -1,
पूर्ण;

/*
 * MMC/SD Device
 */
अटल पूर्णांक tosa_mci_init(काष्ठा device *dev, irq_handler_t tosa_detect_पूर्णांक, व्योम *data)
अणु
	पूर्णांक err;

	err = gpio_request(TOSA_GPIO_nSD_INT, "SD Int");
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "tosa_mci_init: can't request SD_PWR gpio\n");
		जाओ err_gpio_पूर्णांक;
	पूर्ण
	err = gpio_direction_input(TOSA_GPIO_nSD_INT);
	अगर (err)
		जाओ err_gpio_पूर्णांक_dir;

	वापस 0;

err_gpio_पूर्णांक_dir:
	gpio_मुक्त(TOSA_GPIO_nSD_INT);
err_gpio_पूर्णांक:
	वापस err;
पूर्ण

अटल व्योम tosa_mci_निकास(काष्ठा device *dev, व्योम *data)
अणु
	gpio_मुक्त(TOSA_GPIO_nSD_INT);
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data tosa_mci_platक्रमm_data = अणु
	.detect_delay_ms	= 250,
	.ocr_mask       	= MMC_VDD_32_33|MMC_VDD_33_34,
	.init           	= tosa_mci_init,
	.निकास           	= tosa_mci_निकास,
पूर्ण;

अटल काष्ठा gpiod_lookup_table tosa_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", TOSA_GPIO_nSD_DETECT,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", TOSA_GPIO_SD_WP,
			    "wp", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", TOSA_GPIO_PWR_ON,
			    "power", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * Irda
 */
अटल व्योम tosa_irda_transceiver_mode(काष्ठा device *dev, पूर्णांक mode)
अणु
	अगर (mode & IR_OFF) अणु
		gpio_set_value(TOSA_GPIO_IR_POWERDWN, 0);
		pxa2xx_transceiver_mode(dev, mode);
		gpio_direction_output(TOSA_GPIO_IRDA_TX, 0);
	पूर्ण अन्यथा अणु
		pxa2xx_transceiver_mode(dev, mode);
		gpio_set_value(TOSA_GPIO_IR_POWERDWN, 1);
	पूर्ण
पूर्ण

अटल पूर्णांक tosa_irda_startup(काष्ठा device *dev)
अणु
	पूर्णांक ret;

	ret = gpio_request(TOSA_GPIO_IRDA_TX, "IrDA TX");
	अगर (ret)
		जाओ err_tx;
	ret = gpio_direction_output(TOSA_GPIO_IRDA_TX, 0);
	अगर (ret)
		जाओ err_tx_dir;

	ret = gpio_request(TOSA_GPIO_IR_POWERDWN, "IrDA powerdown");
	अगर (ret)
		जाओ err_pwr;

	ret = gpio_direction_output(TOSA_GPIO_IR_POWERDWN, 0);
	अगर (ret)
		जाओ err_pwr_dir;

	tosa_irda_transceiver_mode(dev, IR_SIRMODE | IR_OFF);

	वापस 0;

err_pwr_dir:
	gpio_मुक्त(TOSA_GPIO_IR_POWERDWN);
err_pwr:
err_tx_dir:
	gpio_मुक्त(TOSA_GPIO_IRDA_TX);
err_tx:
	वापस ret;
पूर्ण

अटल व्योम tosa_irda_shutकरोwn(काष्ठा device *dev)
अणु
	tosa_irda_transceiver_mode(dev, IR_SIRMODE | IR_OFF);
	gpio_मुक्त(TOSA_GPIO_IR_POWERDWN);
	gpio_मुक्त(TOSA_GPIO_IRDA_TX);
पूर्ण

अटल काष्ठा pxaficp_platक्रमm_data tosa_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= -1,
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
	.transceiver_mode	= tosa_irda_transceiver_mode,
	.startup		= tosa_irda_startup,
	.shutकरोwn		= tosa_irda_shutकरोwn,
पूर्ण;

/*
 * Tosa AC IN
 */
अटल काष्ठा gpiod_lookup_table tosa_घातer_gpiod_table = अणु
	.dev_id = "gpio-charger",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", TOSA_GPIO_AC_IN,
			    शून्य, GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल अक्षर *tosa_ac_supplied_to[] = अणु
	"main-battery",
	"backup-battery",
	"jacket-battery",
पूर्ण;

अटल काष्ठा gpio_अक्षरger_platक्रमm_data tosa_घातer_data = अणु
	.name			= "charger",
	.type			= POWER_SUPPLY_TYPE_MAINS,
	.supplied_to		= tosa_ac_supplied_to,
	.num_supplicants	= ARRAY_SIZE(tosa_ac_supplied_to),
पूर्ण;

अटल काष्ठा resource tosa_घातer_resource[] = अणु
	अणु
		.name		= "ac",
		.start		= PXA_GPIO_TO_IRQ(TOSA_GPIO_AC_IN),
		.end		= PXA_GPIO_TO_IRQ(TOSA_GPIO_AC_IN),
		.flags		= IORESOURCE_IRQ |
				  IORESOURCE_IRQ_HIGHEDGE |
				  IORESOURCE_IRQ_LOWEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device tosa_घातer_device = अणु
	.name			= "gpio-charger",
	.id			= -1,
	.dev.platक्रमm_data	= &tosa_घातer_data,
	.resource		= tosa_घातer_resource,
	.num_resources		= ARRAY_SIZE(tosa_घातer_resource),
पूर्ण;

/*
 * Tosa Keyboard
 */
अटल स्थिर uपूर्णांक32_t tosakbd_keymap[] = अणु
	KEY(0, 1, KEY_W),
	KEY(0, 5, KEY_K),
	KEY(0, 6, KEY_BACKSPACE),
	KEY(0, 7, KEY_P),
	KEY(1, 0, KEY_Q),
	KEY(1, 1, KEY_E),
	KEY(1, 2, KEY_T),
	KEY(1, 3, KEY_Y),
	KEY(1, 5, KEY_O),
	KEY(1, 6, KEY_I),
	KEY(1, 7, KEY_COMMA),
	KEY(2, 0, KEY_A),
	KEY(2, 1, KEY_D),
	KEY(2, 2, KEY_G),
	KEY(2, 3, KEY_U),
	KEY(2, 5, KEY_L),
	KEY(2, 6, KEY_ENTER),
	KEY(2, 7, KEY_DOT),
	KEY(3, 0, KEY_Z),
	KEY(3, 1, KEY_C),
	KEY(3, 2, KEY_V),
	KEY(3, 3, KEY_J),
	KEY(3, 4, TOSA_KEY_ADDRESSBOOK),
	KEY(3, 5, TOSA_KEY_CANCEL),
	KEY(3, 6, TOSA_KEY_CENTER),
	KEY(3, 7, TOSA_KEY_OK),
	KEY(3, 8, KEY_LEFTSHIFT),
	KEY(4, 0, KEY_S),
	KEY(4, 1, KEY_R),
	KEY(4, 2, KEY_B),
	KEY(4, 3, KEY_N),
	KEY(4, 4, TOSA_KEY_CALENDAR),
	KEY(4, 5, TOSA_KEY_HOMEPAGE),
	KEY(4, 6, KEY_LEFTCTRL),
	KEY(4, 7, TOSA_KEY_LIGHT),
	KEY(4, 9, KEY_RIGHTSHIFT),
	KEY(5, 0, KEY_TAB),
	KEY(5, 1, KEY_SLASH),
	KEY(5, 2, KEY_H),
	KEY(5, 3, KEY_M),
	KEY(5, 4, TOSA_KEY_MENU),
	KEY(5, 6, KEY_UP),
	KEY(5, 10, TOSA_KEY_FN),
	KEY(6, 0, KEY_X),
	KEY(6, 1, KEY_F),
	KEY(6, 2, KEY_SPACE),
	KEY(6, 3, KEY_APOSTROPHE),
	KEY(6, 4, TOSA_KEY_MAIL),
	KEY(6, 5, KEY_LEFT),
	KEY(6, 6, KEY_DOWN),
	KEY(6, 7, KEY_RIGHT),
पूर्ण;

अटल काष्ठा matrix_keymap_data tosakbd_keymap_data = अणु
	.keymap		= tosakbd_keymap,
	.keymap_size	= ARRAY_SIZE(tosakbd_keymap),
पूर्ण;

अटल स्थिर पूर्णांक tosakbd_col_gpios[] =
			अणु 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68 पूर्ण;
अटल स्थिर पूर्णांक tosakbd_row_gpios[] =
			अणु 69, 70, 71, 72, 73, 74, 75 पूर्ण;

अटल काष्ठा matrix_keypad_platक्रमm_data tosakbd_pdata = अणु
	.keymap_data		= &tosakbd_keymap_data,
	.row_gpios		= tosakbd_row_gpios,
	.col_gpios		= tosakbd_col_gpios,
	.num_row_gpios		= ARRAY_SIZE(tosakbd_row_gpios),
	.num_col_gpios		= ARRAY_SIZE(tosakbd_col_gpios),
	.col_scan_delay_us	= 10,
	.debounce_ms		= 10,
	.wakeup			= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device tosakbd_device = अणु
	.name		= "matrix-keypad",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &tosakbd_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_button tosa_gpio_keys[] = अणु
	/*
	 * Two following keys are directly tied to "ON" button of tosa. Why?
	 * The first one can be used as a wakeup source, the second can't;
	 * also the first one is OR of ac_घातered and on_button.
	 */
	अणु
		.type	= EV_PWR,
		.code	= KEY_RESERVED,
		.gpio	= TOSA_GPIO_POWERON,
		.desc	= "Poweron",
		.wakeup	= 1,
		.active_low = 1,
	पूर्ण,
	अणु
		.type	= EV_PWR,
		.code	= KEY_SUSPEND,
		.gpio	= TOSA_GPIO_ON_KEY,
		.desc	= "On key",
		/*
		 * can't be used as wakeup
		 * .wakeup	= 1,
		 */
		.active_low = 1,
	पूर्ण,
	अणु
		.type	= EV_KEY,
		.code	= TOSA_KEY_RECORD,
		.gpio	= TOSA_GPIO_RECORD_BTN,
		.desc	= "Record Button",
		.wakeup	= 1,
		.active_low = 1,
	पूर्ण,
	अणु
		.type	= EV_KEY,
		.code	= TOSA_KEY_SYNC,
		.gpio	= TOSA_GPIO_SYNC,
		.desc	= "Sync Button",
		.wakeup	= 1,
		.active_low = 1,
	पूर्ण,
	अणु
		.type	= EV_SW,
		.code	= SW_HEADPHONE_INSERT,
		.gpio	= TOSA_GPIO_EAR_IN,
		.desc	= "HeadPhone insert",
		.active_low = 1,
		.debounce_पूर्णांकerval = 300,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data tosa_gpio_keys_platक्रमm_data = अणु
	.buttons	= tosa_gpio_keys,
	.nbuttons	= ARRAY_SIZE(tosa_gpio_keys),
पूर्ण;

अटल काष्ठा platक्रमm_device tosa_gpio_keys_device = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &tosa_gpio_keys_platक्रमm_data,
	पूर्ण,
पूर्ण;

/*
 * Tosa LEDs
 */
अटल काष्ठा gpio_led tosa_gpio_leds[] = अणु
	अणु
		.name			= "tosa:amber:charge",
		.शेष_trigger	= "main-battery-charging",
		.gpio			= TOSA_GPIO_CHRG_ERR_LED,
	पूर्ण,
	अणु
		.name			= "tosa:green:mail",
		.शेष_trigger	= "nand-disk",
		.gpio			= TOSA_GPIO_NOTE_LED,
	पूर्ण,
	अणु
		.name			= "tosa:dual:wlan",
		.शेष_trigger	= "none",
		.gpio			= TOSA_GPIO_WLAN_LED,
	पूर्ण,
	अणु
		.name			= "tosa:blue:bluetooth",
		.शेष_trigger	= "tosa-bt",
		.gpio			= TOSA_GPIO_BT_LED,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data tosa_gpio_leds_platक्रमm_data = अणु
	.leds		= tosa_gpio_leds,
	.num_leds	= ARRAY_SIZE(tosa_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device tosaled_device = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &tosa_gpio_leds_platक्रमm_data,
	पूर्ण,
पूर्ण;

/*
 * Toshiba Mobile IO Controller
 */
अटल काष्ठा resource tc6393xb_resources[] = अणु
	[0] = अणु
		.start	= TOSA_LCDC_PHYS,
		.end	= TOSA_LCDC_PHYS + 0x3ffffff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,

	[1] = अणु
		.start	= TOSA_IRQ_GPIO_TC6393XB_INT,
		.end	= TOSA_IRQ_GPIO_TC6393XB_INT,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;


अटल पूर्णांक tosa_tc6393xb_enable(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक rc;

	rc = gpio_request(TOSA_GPIO_TC6393XB_REST_IN, "tc6393xb #pclr");
	अगर (rc)
		जाओ err_req_pclr;
	rc = gpio_request(TOSA_GPIO_TC6393XB_SUSPEND, "tc6393xb #suspend");
	अगर (rc)
		जाओ err_req_suspend;
	rc = gpio_request(TOSA_GPIO_TC6393XB_L3V_ON, "tc6393xb l3v");
	अगर (rc)
		जाओ err_req_l3v;
	rc = gpio_direction_output(TOSA_GPIO_TC6393XB_L3V_ON, 0);
	अगर (rc)
		जाओ err_dir_l3v;
	rc = gpio_direction_output(TOSA_GPIO_TC6393XB_SUSPEND, 0);
	अगर (rc)
		जाओ err_dir_suspend;
	rc = gpio_direction_output(TOSA_GPIO_TC6393XB_REST_IN, 0);
	अगर (rc)
		जाओ err_dir_pclr;

	mdelay(1);

	gpio_set_value(TOSA_GPIO_TC6393XB_SUSPEND, 1);

	mdelay(10);

	gpio_set_value(TOSA_GPIO_TC6393XB_REST_IN, 1);
	gpio_set_value(TOSA_GPIO_TC6393XB_L3V_ON, 1);

	वापस 0;
err_dir_pclr:
err_dir_suspend:
err_dir_l3v:
	gpio_मुक्त(TOSA_GPIO_TC6393XB_L3V_ON);
err_req_l3v:
	gpio_मुक्त(TOSA_GPIO_TC6393XB_SUSPEND);
err_req_suspend:
	gpio_मुक्त(TOSA_GPIO_TC6393XB_REST_IN);
err_req_pclr:
	वापस rc;
पूर्ण

अटल पूर्णांक tosa_tc6393xb_disable(काष्ठा platक्रमm_device *dev)
अणु
	gpio_मुक्त(TOSA_GPIO_TC6393XB_L3V_ON);
	gpio_मुक्त(TOSA_GPIO_TC6393XB_SUSPEND);
	gpio_मुक्त(TOSA_GPIO_TC6393XB_REST_IN);

	वापस 0;
पूर्ण

अटल पूर्णांक tosa_tc6393xb_resume(काष्ठा platक्रमm_device *dev)
अणु
	gpio_set_value(TOSA_GPIO_TC6393XB_SUSPEND, 1);
	mdelay(10);
	gpio_set_value(TOSA_GPIO_TC6393XB_L3V_ON, 1);
	mdelay(10);

	वापस 0;
पूर्ण

अटल पूर्णांक tosa_tc6393xb_suspend(काष्ठा platक्रमm_device *dev)
अणु
	gpio_set_value(TOSA_GPIO_TC6393XB_L3V_ON, 0);
	gpio_set_value(TOSA_GPIO_TC6393XB_SUSPEND, 0);
	वापस 0;
पूर्ण

अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff, 0xff पूर्ण;

अटल काष्ठा nand_bbt_descr tosa_tc6393xb_nand_bbt = अणु
	.options	= 0,
	.offs		= 4,
	.len		= 2,
	.pattern	= scan_ff_pattern
पूर्ण;

अटल स्थिर अक्षर * स्थिर probes[] = अणु
	"cmdlinepart",
	"ofpart",
	"sharpslpart",
	शून्य,
पूर्ण;

अटल काष्ठा पंचांगio_nand_data tosa_tc6393xb_nand_config = अणु
	.badblock_pattern = &tosa_tc6393xb_nand_bbt,
	.part_parsers = probes,
पूर्ण;

अटल पूर्णांक tosa_tc6393xb_setup(काष्ठा platक्रमm_device *dev)
अणु
	पूर्णांक rc;

	rc = gpio_request(TOSA_GPIO_CARD_VCC_ON, "CARD_VCC_ON");
	अगर (rc)
		जाओ err_req;

	rc = gpio_direction_output(TOSA_GPIO_CARD_VCC_ON, 1);
	अगर (rc)
		जाओ err_dir;

	वापस rc;

err_dir:
	gpio_मुक्त(TOSA_GPIO_CARD_VCC_ON);
err_req:
	वापस rc;
पूर्ण

अटल व्योम tosa_tc6393xb_tearकरोwn(काष्ठा platक्रमm_device *dev)
अणु
	gpio_मुक्त(TOSA_GPIO_CARD_VCC_ON);
पूर्ण

#अगर_घोषित CONFIG_MFD_TC6393XB
अटल काष्ठा fb_videomode tosa_tc6393xb_lcd_mode[] = अणु
	अणु
		.xres = 480,
		.yres = 640,
		.pixघड़ी = 0x002cdf00,/* PLL भागisor */
		.left_margin = 0x004c,
		.right_margin = 0x005b,
		.upper_margin = 0x0001,
		.lower_margin = 0x000d,
		.hsync_len = 0x0002,
		.vsync_len = 0x0001,
		.sync = FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode = FB_VMODE_NONINTERLACED,
	पूर्ण,अणु
		.xres = 240,
		.yres = 320,
		.pixघड़ी = 0x00e7f203,/* PLL भागisor */
		.left_margin = 0x0024,
		.right_margin = 0x002f,
		.upper_margin = 0x0001,
		.lower_margin = 0x000d,
		.hsync_len = 0x0002,
		.vsync_len = 0x0001,
		.sync = FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
		.vmode = FB_VMODE_NONINTERLACED,
	पूर्ण
पूर्ण;

अटल काष्ठा पंचांगio_fb_data tosa_tc6393xb_fb_config = अणु
	.lcd_set_घातer	= tc6393xb_lcd_set_घातer,
	.lcd_mode	= tc6393xb_lcd_mode,
	.num_modes	= ARRAY_SIZE(tosa_tc6393xb_lcd_mode),
	.modes		= &tosa_tc6393xb_lcd_mode[0],
	.height		= 82,
	.width		= 60,
पूर्ण;
#पूर्ण_अगर

अटल काष्ठा tc6393xb_platक्रमm_data tosa_tc6393xb_data = अणु
	.scr_pll2cr	= 0x0cc1,
	.scr_gper	= 0x3300,

	.irq_base	= IRQ_BOARD_START,
	.gpio_base	= TOSA_TC6393XB_GPIO_BASE,
	.setup		= tosa_tc6393xb_setup,
	.tearकरोwn	= tosa_tc6393xb_tearकरोwn,

	.enable		= tosa_tc6393xb_enable,
	.disable	= tosa_tc6393xb_disable,
	.suspend	= tosa_tc6393xb_suspend,
	.resume		= tosa_tc6393xb_resume,

	.nand_data	= &tosa_tc6393xb_nand_config,
#अगर_घोषित CONFIG_MFD_TC6393XB
	.fb_data	= &tosa_tc6393xb_fb_config,
#पूर्ण_अगर

	.resume_restore = 1,
पूर्ण;


अटल काष्ठा platक्रमm_device tc6393xb_device = अणु
	.name	= "tc6393xb",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &tosa_tc6393xb_data,
	पूर्ण,
	.num_resources	= ARRAY_SIZE(tc6393xb_resources),
	.resource	= tc6393xb_resources,
पूर्ण;

अटल काष्ठा tosa_bt_data tosa_bt_data = अणु
	.gpio_pwr	= TOSA_GPIO_BT_PWR_EN,
	.gpio_reset	= TOSA_GPIO_BT_RESET,
पूर्ण;

अटल काष्ठा platक्रमm_device tosa_bt_device = अणु
	.name	= "tosa-bt",
	.id	= -1,
	.dev.platक्रमm_data = &tosa_bt_data,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp_master_info = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table tosa_lcd_gpio_table = अणु
	.dev_id = "spi2.0",
	.table = अणु
		GPIO_LOOKUP("tc6393xb",
			    TOSA_GPIO_TG_ON - TOSA_TC6393XB_GPIO_BASE,
			    "tg #pwr", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table tosa_lcd_bl_gpio_table = अणु
	.dev_id = "i2c-tosa-bl",
	.table = अणु
		GPIO_LOOKUP("tc6393xb",
			    TOSA_GPIO_BL_C20MA - TOSA_TC6393XB_GPIO_BASE,
			    "backlight", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा spi_board_info spi_board_info[] __initdata = अणु
	अणु
		.modalias	= "tosa-lcd",
		// .platक्रमm_data
		.max_speed_hz	= 28750,
		.bus_num	= 2,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition sharpsl_rom_parts[] = अणु
	अणु
		.name	="Boot PROM Filesystem",
		.offset	= 0x00160000,
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

अटल काष्ठा platक्रमm_device wm9712_device = अणु
	.name	= "wm9712-codec",
	.id	= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device tosa_audio_device = अणु
	.name	= "tosa-audio",
	.id	= -1,
पूर्ण;

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&tosascoop_device,
	&tosascoop_jc_device,
	&tc6393xb_device,
	&tosa_घातer_device,
	&tosakbd_device,
	&tosa_gpio_keys_device,
	&tosaled_device,
	&tosa_bt_device,
	&sharpsl_rom_device,
	&wm9712_device,
	&tosa_gpio_vbus,
	&tosa_audio_device,
पूर्ण;

अटल व्योम tosa_घातeroff(व्योम)
अणु
	pxa_restart(REBOOT_GPIO, शून्य);
पूर्ण

अटल व्योम tosa_restart(क्रमागत reboot_mode mode, स्थिर अक्षर *cmd)
अणु
	uपूर्णांक32_t msc0 = __raw_पढ़ोl(MSC0);

	/* Bootloader magic क्रम a reboot */
	अगर((msc0 & 0xffff0000) == 0x7ff00000)
		__raw_ग_लिखोl((msc0 & 0xffff) | 0x7ee00000, MSC0);

	tosa_घातeroff();
पूर्ण

अटल व्योम __init tosa_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(tosa_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	gpio_set_wake(MFP_PIN_GPIO1, 1);
	/* We can't pass to gpio-keys since it will drop the Reset altfunc */

	init_gpio_reset(TOSA_GPIO_ON_RESET, 0, 0);

	pm_घातer_off = tosa_घातeroff;

	PCFR |= PCFR_OPDE;

	/* enable batt_fault */
	PMCR = 0x01;

	gpiod_add_lookup_table(&tosa_mci_gpio_table);
	pxa_set_mci_info(&tosa_mci_platक्रमm_data);
	pxa_set_ficp_info(&tosa_ficp_platक्रमm_data);
	pxa_set_i2c_info(शून्य);
	pxa_set_ac97_info(शून्य);
	platक्रमm_scoop_config = &tosa_pcmcia_config;

	pxa2xx_set_spi_info(2, &pxa_ssp_master_info);
	gpiod_add_lookup_table(&tosa_lcd_gpio_table);
	gpiod_add_lookup_table(&tosa_lcd_bl_gpio_table);
	spi_रेजिस्टर_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));

	clk_add_alias("CLK_CK3P6MI", tc6393xb_device.name, "GPIO11_CLK", शून्य);

	gpiod_add_lookup_table(&tosa_udc_gpiod_table);
	gpiod_add_lookup_table(&tosa_घातer_gpiod_table);
	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
पूर्ण

अटल व्योम __init fixup_tosa(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	sharpsl_save_param();
	memblock_add(0xa0000000, SZ_64M);
पूर्ण

MACHINE_START(TOSA, "SHARP Tosa")
	.fixup          = fixup_tosa,
	.map_io         = pxa25x_map_io,
	.nr_irqs	= TOSA_NR_IRQS,
	.init_irq       = pxa25x_init_irq,
	.handle_irq       = pxa25x_handle_irq,
	.init_machine   = tosa_init,
	.init_समय	= pxa_समयr_init,
	.restart	= tosa_restart,
MACHINE_END
