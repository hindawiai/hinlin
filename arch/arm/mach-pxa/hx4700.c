<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Support क्रम HP iPAQ hx4700 PDAs.
 *
 * Copyright (c) 2008-2009 Philipp Zabel
 *
 * Based on code:
 *    Copyright (c) 2004 Hewlett-Packard Company.
 *    Copyright (c) 2005 SDG Systems, LLC
 *    Copyright (c) 2006 Anton Vorontsov <cbou@mail.ru>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/fb.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/input/navpoपूर्णांक.h>
#समावेश <linux/lcd.h>
#समावेश <linux/mfd/asic3.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/pda_घातer.h>
#समावेश <linux/platक्रमm_data/gpio-htc-egpपन.स>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>
#समावेश <linux/regulator/driver.h>
#समावेश <linux/regulator/gpio-regulator.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/max1586.h>
#समावेश <linux/spi/ads7846.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa27x.h"
#समावेश <mach/hx4700.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>

#समावेश <sound/ak4641.h>
#समावेश <video/platक्रमm_lcd.h>
#समावेश <video/w100fb.h>

#समावेश "devices.h"
#समावेश "generic.h"
#समावेश "udc.h"

/* Physical address space inक्रमmation */

#घोषणा ATI_W3220_PHYS  PXA_CS2_PHYS /* ATI Imageon 3220 Graphics */
#घोषणा ASIC3_PHYS      PXA_CS3_PHYS
#घोषणा ASIC3_SD_PHYS   (PXA_CS3_PHYS + 0x02000000)

अटल अचिन्हित दीर्घ hx4700_pin_config[] __initdata = अणु

	/* SDRAM and Static Memory I/O Signals */
	GPIO20_nSDCS_2,
	GPIO21_nSDCS_3,
	GPIO15_nCS_1,
	GPIO78_nCS_2,   /* W3220 */
	GPIO79_nCS_3,   /* ASIC3 */
	GPIO80_nCS_4,
	GPIO33_nCS_5,	/* EGPIO, WLAN */

	/* PC CARD */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO54_nPCE_2,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,
	GPIO85_nPCE_1,
	GPIO104_PSKTSEL,

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* FFUART (RS-232) */
	GPIO34_FFUART_RXD,
	GPIO35_FFUART_CTS,
	GPIO36_FFUART_DCD,
	GPIO37_FFUART_DSR,
	GPIO38_FFUART_RI,
	GPIO39_FFUART_TXD,
	GPIO40_FFUART_DTR,
	GPIO41_FFUART_RTS,

	/* BTUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD_LPM_LOW,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS_LPM_LOW,

	/* STUART (IRDA) */
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,

	/* PWM 1 (Backlight) */
	GPIO17_PWM1_OUT,

	/* I2S */
	GPIO28_I2S_BITCLK_OUT,
	GPIO29_I2S_SDATA_IN,
	GPIO30_I2S_SDATA_OUT,
	GPIO31_I2S_SYNC,
	GPIO113_I2S_SYSCLK,

	/* SSP 1 (NavPoपूर्णांक) */
	GPIO23_SSP1_SCLK_IN,
	GPIO24_SSP1_SFRM,
	GPIO25_SSP1_TXD,
	GPIO26_SSP1_RXD,

	/* SSP 2 (TSC2046) */
	GPIO19_SSP2_SCLK,
	GPIO86_SSP2_RXD,
	GPIO87_SSP2_TXD,
	GPIO88_GPIO | MFP_LPM_DRIVE_HIGH,	/* TSC2046_CS */

	/* BQ24022 Regulator */
	GPIO72_GPIO | MFP_LPM_KEEP_OUTPUT,	/* BQ24022_nCHARGE_EN */
	GPIO96_GPIO | MFP_LPM_KEEP_OUTPUT,	/* BQ24022_ISET2 */

	/* HX4700 specअगरic input GPIOs */
	GPIO12_GPIO | WAKEUP_ON_EDGE_RISE,	/* ASIC3_IRQ */
	GPIO13_GPIO,	/* W3220_IRQ */
	GPIO14_GPIO,	/* nWLAN_IRQ */

	/* HX4700 specअगरic output GPIOs */
	GPIO61_GPIO | MFP_LPM_DRIVE_HIGH,	/* W3220_nRESET */
	GPIO71_GPIO | MFP_LPM_DRIVE_HIGH,	/* ASIC3_nRESET */
	GPIO81_GPIO | MFP_LPM_DRIVE_HIGH,	/* CPU_GP_nRESET */
	GPIO116_GPIO | MFP_LPM_DRIVE_HIGH,	/* CPU_HW_nRESET */
	GPIO102_GPIO | MFP_LPM_DRIVE_LOW,	/* SYNAPTICS_POWER_ON */

	GPIO10_GPIO,	/* GSM_IRQ */
	GPIO13_GPIO,	/* CPLD_IRQ */
	GPIO107_GPIO,	/* DS1WM_IRQ */
	GPIO108_GPIO,	/* GSM_READY */
	GPIO58_GPIO,	/* TSC2046_nPENIRQ */
	GPIO66_GPIO,	/* nSDIO_IRQ */
पूर्ण;

/*
 * IRDA
 */

अटल काष्ठा pxaficp_platक्रमm_data ficp_info = अणु
	.gpio_pwकरोwn		= GPIO105_HX4700_nIR_ON,
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
पूर्ण;

/*
 * GPIO Keys
 */

#घोषणा INIT_KEY(_code, _gpio, _active_low, _desc)	\
	अणु						\
		.code       = KEY_##_code,		\
		.gpio       = _gpio,			\
		.active_low = _active_low,		\
		.desc       = _desc,			\
		.type       = EV_KEY,			\
		.wakeup     = 1,			\
	पूर्ण

अटल काष्ठा gpio_keys_button gpio_keys_buttons[] = अणु
	INIT_KEY(POWER,       GPIO0_HX4700_nKEY_POWER,   1, "Power button"),
	INIT_KEY(MAIL,        GPIO94_HX4700_KEY_MAIL,    0, "Mail button"),
	INIT_KEY(ADDRESSBOOK, GPIO99_HX4700_KEY_CONTACTS,0, "Contacts button"),
	INIT_KEY(RECORD,      GPIOD6_nKEY_RECORD,        1, "Record button"),
	INIT_KEY(CALENDAR,    GPIOD1_nKEY_CALENDAR,      1, "Calendar button"),
	INIT_KEY(HOMEPAGE,    GPIOD3_nKEY_HOME,          1, "Home button"),
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data gpio_keys_data = अणु
	.buttons = gpio_keys_buttons,
	.nbuttons = ARRAY_SIZE(gpio_keys_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device gpio_keys = अणु
	.name = "gpio-keys",
	.dev  = अणु
		.platक्रमm_data = &gpio_keys_data,
	पूर्ण,
	.id   = -1,
पूर्ण;

/*
 * Synaptics NavPoपूर्णांक connected to SSP1
 */

अटल काष्ठा navpoपूर्णांक_platक्रमm_data navpoपूर्णांक_platक्रमm_data = अणु
	.port	= 1,
	.gpio	= GPIO102_HX4700_SYNAPTICS_POWER_ON,
पूर्ण;

अटल काष्ठा platक्रमm_device navpoपूर्णांक = अणु
	.name	= "navpoint",
	.id	= -1,
	.dev = अणु
		.platक्रमm_data = &navpoपूर्णांक_platक्रमm_data,
	पूर्ण,
पूर्ण;

/*
 * ASIC3
 */

अटल u16 asic3_gpio_config[] = अणु
	/* ASIC3 GPIO banks A and B aदीर्घ with some of C and D
	   implement the buffering क्रम the CF slot. */
	ASIC3_CONFIG_GPIO(0, 1, 1, 0),
	ASIC3_CONFIG_GPIO(1, 1, 1, 0),
	ASIC3_CONFIG_GPIO(2, 1, 1, 0),
	ASIC3_CONFIG_GPIO(3, 1, 1, 0),
	ASIC3_CONFIG_GPIO(4, 1, 1, 0),
	ASIC3_CONFIG_GPIO(5, 1, 1, 0),
	ASIC3_CONFIG_GPIO(6, 1, 1, 0),
	ASIC3_CONFIG_GPIO(7, 1, 1, 0),
	ASIC3_CONFIG_GPIO(8, 1, 1, 0),
	ASIC3_CONFIG_GPIO(9, 1, 1, 0),
	ASIC3_CONFIG_GPIO(10, 1, 1, 0),
	ASIC3_CONFIG_GPIO(11, 1, 1, 0),
	ASIC3_CONFIG_GPIO(12, 1, 1, 0),
	ASIC3_CONFIG_GPIO(13, 1, 1, 0),
	ASIC3_CONFIG_GPIO(14, 1, 1, 0),
	ASIC3_CONFIG_GPIO(15, 1, 1, 0),

	ASIC3_CONFIG_GPIO(16, 1, 1, 0),
	ASIC3_CONFIG_GPIO(17, 1, 1, 0),
	ASIC3_CONFIG_GPIO(18, 1, 1, 0),
	ASIC3_CONFIG_GPIO(19, 1, 1, 0),
	ASIC3_CONFIG_GPIO(20, 1, 1, 0),
	ASIC3_CONFIG_GPIO(21, 1, 1, 0),
	ASIC3_CONFIG_GPIO(22, 1, 1, 0),
	ASIC3_CONFIG_GPIO(23, 1, 1, 0),
	ASIC3_CONFIG_GPIO(24, 1, 1, 0),
	ASIC3_CONFIG_GPIO(25, 1, 1, 0),
	ASIC3_CONFIG_GPIO(26, 1, 1, 0),
	ASIC3_CONFIG_GPIO(27, 1, 1, 0),
	ASIC3_CONFIG_GPIO(28, 1, 1, 0),
	ASIC3_CONFIG_GPIO(29, 1, 1, 0),
	ASIC3_CONFIG_GPIO(30, 1, 1, 0),
	ASIC3_CONFIG_GPIO(31, 1, 1, 0),

	/* GPIOC - CF, LEDs, SD */
	ASIC3_GPIOC0_LED0,		/* red */
	ASIC3_GPIOC1_LED1,		/* green */
	ASIC3_GPIOC2_LED2,		/* blue */
	ASIC3_GPIOC5_nCIOW,
	ASIC3_GPIOC6_nCIOR,
	ASIC3_GPIOC7_nPCE_1,
	ASIC3_GPIOC8_nPCE_2,
	ASIC3_GPIOC9_nPOE,
	ASIC3_GPIOC10_nPWE,
	ASIC3_GPIOC11_PSKTSEL,
	ASIC3_GPIOC12_nPREG,
	ASIC3_GPIOC13_nPWAIT,
	ASIC3_GPIOC14_nPIOIS16,
	ASIC3_GPIOC15_nPIOR,

	/* GPIOD: input GPIOs, CF */
	ASIC3_GPIOD4_CF_nCD,
	ASIC3_GPIOD11_nCIOIS16,
	ASIC3_GPIOD12_nCWAIT,
	ASIC3_GPIOD15_nPIOW,
पूर्ण;

अटल काष्ठा asic3_led asic3_leds[ASIC3_NUM_LEDS] = अणु
	[0] = अणु
		.name = "hx4700:amber",
		.शेष_trigger = "ds2760-battery.0-charging-blink-full-solid",
	पूर्ण,
	[1] = अणु
		.name = "hx4700:green",
		.शेष_trigger = "unused",
	पूर्ण,
	[2] = अणु
		.name = "hx4700:blue",
		.शेष_trigger = "hx4700-radio",
	पूर्ण,
पूर्ण;

अटल काष्ठा resource asic3_resources[] = अणु
	/* GPIO part */
	[0] = DEFINE_RES_MEM(ASIC3_PHYS, ASIC3_MAP_SIZE_16BIT),
	[1] = DEFINE_RES_IRQ(PXA_GPIO_TO_IRQ(GPIO12_HX4700_ASIC3_IRQ)),
	/* SD part */
	[2] = DEFINE_RES_MEM(ASIC3_SD_PHYS, ASIC3_MAP_SIZE_16BIT),
	[3] = DEFINE_RES_IRQ(PXA_GPIO_TO_IRQ(GPIO66_HX4700_ASIC3_nSDIO_IRQ)),
पूर्ण;

अटल काष्ठा asic3_platक्रमm_data asic3_platक्रमm_data = अणु
	.gpio_config     = asic3_gpio_config,
	.gpio_config_num = ARRAY_SIZE(asic3_gpio_config),
	.irq_base        = IRQ_BOARD_START,
	.gpio_base       = HX4700_ASIC3_GPIO_BASE,
	.घड़ी_rate      = 4000000,
	.leds            = asic3_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device asic3 = अणु
	.name          = "asic3",
	.id            = -1,
	.resource      = asic3_resources,
	.num_resources = ARRAY_SIZE(asic3_resources),
	.dev = अणु
		.platक्रमm_data = &asic3_platक्रमm_data,
	पूर्ण,
पूर्ण;

/*
 * EGPIO
 */

अटल काष्ठा resource egpio_resources[] = अणु
	[0] = DEFINE_RES_MEM(PXA_CS5_PHYS, 0x4),
पूर्ण;

अटल काष्ठा htc_egpio_chip egpio_chips[] = अणु
	[0] = अणु
		.reg_start = 0,
		.gpio_base = HX4700_EGPIO_BASE,
		.num_gpios = 8,
		.direction = HTC_EGPIO_OUTPUT,
	पूर्ण,
पूर्ण;

अटल काष्ठा htc_egpio_platक्रमm_data egpio_info = अणु
	.reg_width = 16,
	.bus_width = 16,
	.chip      = egpio_chips,
	.num_chips = ARRAY_SIZE(egpio_chips),
पूर्ण;

अटल काष्ठा platक्रमm_device egpio = अणु
	.name          = "htc-egpio",
	.id            = -1,
	.resource      = egpio_resources,
	.num_resources = ARRAY_SIZE(egpio_resources),
	.dev = अणु
		.platक्रमm_data = &egpio_info,
	पूर्ण,
पूर्ण;

/*
 * LCD - Sony display connected to ATI Imageon w3220
 */

अटल व्योम sony_lcd_init(व्योम)
अणु
	gpio_set_value(GPIO84_HX4700_LCD_SQN, 1);
	gpio_set_value(GPIO110_HX4700_LCD_LVDD_3V3_ON, 0);
	gpio_set_value(GPIO111_HX4700_LCD_AVDD_3V3_ON, 0);
	gpio_set_value(GPIO70_HX4700_LCD_SLIN1, 0);
	gpio_set_value(GPIO62_HX4700_LCD_nRESET, 0);
	mdelay(10);
	gpio_set_value(GPIO59_HX4700_LCD_PC1, 0);
	gpio_set_value(GPIO110_HX4700_LCD_LVDD_3V3_ON, 0);
	mdelay(20);

	gpio_set_value(GPIO110_HX4700_LCD_LVDD_3V3_ON, 1);
	mdelay(5);
	gpio_set_value(GPIO111_HX4700_LCD_AVDD_3V3_ON, 1);

	/* FIXME: init w3220 रेजिस्टरs here */

	mdelay(5);
	gpio_set_value(GPIO70_HX4700_LCD_SLIN1, 1);
	mdelay(10);
	gpio_set_value(GPIO62_HX4700_LCD_nRESET, 1);
	mdelay(10);
	gpio_set_value(GPIO59_HX4700_LCD_PC1, 1);
	mdelay(10);
	gpio_set_value(GPIO112_HX4700_LCD_N2V7_7V3_ON, 1);
पूर्ण

अटल व्योम sony_lcd_off(व्योम)
अणु
	gpio_set_value(GPIO59_HX4700_LCD_PC1, 0);
	gpio_set_value(GPIO62_HX4700_LCD_nRESET, 0);
	mdelay(10);
	gpio_set_value(GPIO112_HX4700_LCD_N2V7_7V3_ON, 0);
	mdelay(10);
	gpio_set_value(GPIO111_HX4700_LCD_AVDD_3V3_ON, 0);
	mdelay(10);
	gpio_set_value(GPIO110_HX4700_LCD_LVDD_3V3_ON, 0);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम w3220_lcd_suspend(काष्ठा w100fb_par *wfb)
अणु
	sony_lcd_off();
पूर्ण

अटल व्योम w3220_lcd_resume(काष्ठा w100fb_par *wfb)
अणु
	sony_lcd_init();
पूर्ण
#अन्यथा
#घोषणा w3220_lcd_resume	शून्य
#घोषणा w3220_lcd_suspend	शून्य
#पूर्ण_अगर

अटल काष्ठा w100_tg_info w3220_tg_info = अणु
	.suspend	= w3220_lcd_suspend,
	.resume		= w3220_lcd_resume,
पूर्ण;

/*  				 W3220_VGA		QVGA */
अटल काष्ठा w100_gen_regs w3220_regs = अणु
	.lcd_क्रमmat =        0x00000003,
	.lcdd_cntl1 =        0x00000000,
	.lcdd_cntl2 =        0x0003ffff,
	.genlcd_cntl1 =      0x00abf003,	/* 0x00fff003 */
	.genlcd_cntl2 =      0x00000003,
	.genlcd_cntl3 =      0x000102aa,
पूर्ण;

अटल काष्ठा w100_mode w3220_modes[] = अणु
अणु
	.xres 		= 480,
	.yres 		= 640,
	.left_margin 	= 15,
	.right_margin 	= 16,
	.upper_margin 	= 8,
	.lower_margin 	= 7,
	.crtc_ss	= 0x00000000,
	.crtc_ls	= 0xa1ff01f9,	/* 0x21ff01f9 */
	.crtc_gs	= 0xc0000000,	/* 0x40000000 */
	.crtc_vpos_gs	= 0x0000028f,
	.crtc_ps1_active = 0x00000000,	/* 0x41060010 */
	.crtc_rev	= 0,
	.crtc_dclk	= 0x80000000,
	.crtc_gclk	= 0x040a0104,
	.crtc_goe	= 0,
	.pll_freq 	= 95,
	.pixclk_भागider = 4,
	.pixclk_भागider_rotated = 4,
	.pixclk_src     = CLK_SRC_PLL,
	.sysclk_भागider = 0,
	.sysclk_src     = CLK_SRC_PLL,
पूर्ण,
अणु
	.xres 		= 240,
	.yres 		= 320,
	.left_margin 	= 9,
	.right_margin 	= 8,
	.upper_margin 	= 5,
	.lower_margin 	= 4,
	.crtc_ss	= 0x80150014,
	.crtc_ls        = 0xa0fb00f7,
	.crtc_gs	= 0xc0080007,
	.crtc_vpos_gs	= 0x00080007,
	.crtc_rev	= 0x0000000a,
	.crtc_dclk	= 0x81700030,
	.crtc_gclk	= 0x8015010f,
	.crtc_goe	= 0x00000000,
	.pll_freq 	= 95,
	.pixclk_भागider = 4,
	.pixclk_भागider_rotated = 4,
	.pixclk_src     = CLK_SRC_PLL,
	.sysclk_भागider = 0,
	.sysclk_src     = CLK_SRC_PLL,
पूर्ण,
पूर्ण;

काष्ठा w100_mem_info w3220_mem_info = अणु
	.ext_cntl        = 0x09640011,
	.sdram_mode_reg  = 0x00600021,
	.ext_timing_cntl = 0x1a001545,	/* 0x15001545 */
	.io_cntl         = 0x7ddd7333,
	.size            = 0x1fffff,
पूर्ण;

काष्ठा w100_bm_mem_info w3220_bm_mem_info = अणु
	.ext_mem_bw = 0x50413e01,
	.offset = 0,
	.ext_timing_ctl = 0x00043f7f,
	.ext_cntl = 0x00000010,
	.mode_reg = 0x00250000,
	.io_cntl = 0x0fff0000,
	.config = 0x08301480,
पूर्ण;

अटल काष्ठा w100_gpio_regs w3220_gpio_info = अणु
	.init_data1 = 0xdfe00100,	/* GPIO_DATA */
	.gpio_dir1  = 0xffff0000,	/* GPIO_CNTL1 */
	.gpio_oe1   = 0x00000000,	/* GPIO_CNTL2 */
	.init_data2 = 0x00000000,	/* GPIO_DATA2 */
	.gpio_dir2  = 0x00000000,	/* GPIO_CNTL3 */
	.gpio_oe2   = 0x00000000,	/* GPIO_CNTL4 */
पूर्ण;

अटल काष्ठा w100fb_mach_info w3220_info = अणु
	.tg        = &w3220_tg_info,
	.mem       = &w3220_mem_info,
	.bm_mem    = &w3220_bm_mem_info,
	.gpio      = &w3220_gpio_info,
	.regs      = &w3220_regs,
	.modelist  = w3220_modes,
	.num_modes = 2,
	.xtal_freq = 16000000,
पूर्ण;

अटल काष्ठा resource w3220_resources[] = अणु
	[0] = DEFINE_RES_MEM(ATI_W3220_PHYS, SZ_16M),
पूर्ण;

अटल काष्ठा platक्रमm_device w3220 = अणु
	.name	= "w100fb",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &w3220_info,
	पूर्ण,
	.num_resources = ARRAY_SIZE(w3220_resources),
	.resource      = w3220_resources,
पूर्ण;

अटल व्योम hx4700_lcd_set_घातer(काष्ठा plat_lcd_data *pd, अचिन्हित पूर्णांक घातer)
अणु
	अगर (घातer)
		sony_lcd_init();
	अन्यथा
		sony_lcd_off();
पूर्ण

अटल काष्ठा plat_lcd_data hx4700_lcd_data = अणु
	.set_घातer = hx4700_lcd_set_घातer,
पूर्ण;

अटल काष्ठा platक्रमm_device hx4700_lcd = अणु
	.name = "platform-lcd",
	.id   = -1,
	.dev  = अणु
		.platक्रमm_data = &hx4700_lcd_data,
		.parent        = &w3220.dev,
	पूर्ण,
पूर्ण;

/*
 * Backlight
 */

अटल काष्ठा platक्रमm_pwm_backlight_data backlight_data = अणु
	.max_brightness = 200,
	.dft_brightness = 100,
पूर्ण;

अटल काष्ठा platक्रमm_device backlight = अणु
	.name = "pwm-backlight",
	.id   = -1,
	.dev  = अणु
		.parent        = &pxa27x_device_pwm1.dev,
		.platक्रमm_data = &backlight_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा pwm_lookup hx4700_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.1", 0, "pwm-backlight", शून्य,
		   30923, PWM_POLARITY_NORMAL),
पूर्ण;

/*
 * USB "Transceiver"
 */

अटल काष्ठा gpiod_lookup_table gpio_vbus_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		/* This GPIO is on ASIC3 */
		GPIO_LOOKUP("asic3",
			    /* Convert to a local offset on the ASIC3 */
			    GPIOD14_nUSBC_DETECT - HX4700_ASIC3_GPIO_BASE,
			    "vbus", GPIO_ACTIVE_LOW),
		/* This one is on the primary SOC GPIO */
		GPIO_LOOKUP("gpio-pxa", GPIO76_HX4700_USBC_PUEN,
			    "pullup", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device gpio_vbus = अणु
	.name          = "gpio-vbus",
	.id            = -1,
पूर्ण;

अटल काष्ठा pxa2xx_udc_mach_info hx4700_udc_info;

/*
 * Touchscreen - TSC2046 connected to SSP2
 */

अटल स्थिर काष्ठा ads7846_platक्रमm_data tsc2046_info = अणु
	.model            = 7846,
	.vref_delay_usecs = 100,
	.pressure_max     = 1024,
	.debounce_max     = 10,
	.debounce_tol     = 3,
	.debounce_rep     = 1,
	.gpio_penकरोwn     = GPIO58_HX4700_TSC2046_nPENIRQ,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip tsc2046_chip = अणु
	.tx_threshold = 1,
	.rx_threshold = 2,
	.समयout      = 64,
	.gpio_cs      = GPIO88_HX4700_TSC2046_CS,
पूर्ण;

अटल काष्ठा spi_board_info tsc2046_board_info[] __initdata = अणु
	अणु
		.modalias        = "ads7846",
		.bus_num         = 2,
		.max_speed_hz    = 2600000, /* 100 kHz sample rate */
		.irq             = PXA_GPIO_TO_IRQ(GPIO58_HX4700_TSC2046_nPENIRQ),
		.platक्रमm_data   = &tsc2046_info,
		.controller_data = &tsc2046_chip,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxa2xx_spi_controller pxa_ssp2_master_info = अणु
	.num_chipselect = 1,
	.enable_dma     = 1,
पूर्ण;

/*
 * External घातer
 */

अटल पूर्णांक घातer_supply_init(काष्ठा device *dev)
अणु
	वापस gpio_request(GPIOD9_nAC_IN, "AC charger detect");
पूर्ण

अटल पूर्णांक hx4700_is_ac_online(व्योम)
अणु
	वापस !gpio_get_value(GPIOD9_nAC_IN);
पूर्ण

अटल व्योम घातer_supply_निकास(काष्ठा device *dev)
अणु
	gpio_मुक्त(GPIOD9_nAC_IN);
पूर्ण

अटल अक्षर *hx4700_supplicants[] = अणु
	"ds2760-battery.0", "backup-battery"
पूर्ण;

अटल काष्ठा pda_घातer_pdata घातer_supply_info = अणु
	.init            = घातer_supply_init,
	.is_ac_online    = hx4700_is_ac_online,
	.निकास            = घातer_supply_निकास,
	.supplied_to     = hx4700_supplicants,
	.num_supplicants = ARRAY_SIZE(hx4700_supplicants),
पूर्ण;

अटल काष्ठा resource घातer_supply_resources[] = अणु
	[0] = DEFINE_RES_NAMED(PXA_GPIO_TO_IRQ(GPIOD9_nAC_IN), 1, "ac",
		IORESOURCE_IRQ |
		IORESOURCE_IRQ_HIGHEDGE | IORESOURCE_IRQ_LOWEDGE),
	[1] = DEFINE_RES_NAMED(PXA_GPIO_TO_IRQ(GPIOD14_nUSBC_DETECT), 1, "usb",
		IORESOURCE_IRQ |
		IORESOURCE_IRQ_HIGHEDGE | IORESOURCE_IRQ_LOWEDGE),
पूर्ण;

अटल काष्ठा platक्रमm_device घातer_supply = अणु
	.name = "pda-power",
	.id   = -1,
	.dev  = अणु
		.platक्रमm_data = &घातer_supply_info,
	पूर्ण,
	.resource      = घातer_supply_resources,
	.num_resources = ARRAY_SIZE(घातer_supply_resources),
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
		.max_uA         = 500000,
		.valid_ops_mask = REGULATOR_CHANGE_CURRENT|REGULATOR_CHANGE_STATUS,
	पूर्ण,
	.num_consumer_supplies  = ARRAY_SIZE(bq24022_consumers),
	.consumer_supplies      = bq24022_consumers,
पूर्ण;

अटल क्रमागत gpiod_flags bq24022_gpiod_gflags[] = अणु GPIOD_OUT_LOW पूर्ण;

अटल काष्ठा gpio_regulator_state bq24022_states[] = अणु
	अणु .value = 100000, .gpios = (0 << 0) पूर्ण,
	अणु .value = 500000, .gpios = (1 << 0) पूर्ण,
पूर्ण;

अटल काष्ठा gpio_regulator_config bq24022_info = अणु
	.supply_name = "bq24022",

	.enabled_at_boot = 0,

	.gflags = bq24022_gpiod_gflags,
	.ngpios = ARRAY_SIZE(bq24022_gpiod_gflags),

	.states = bq24022_states,
	.nr_states = ARRAY_SIZE(bq24022_states),

	.type = REGULATOR_CURRENT,
	.init_data = &bq24022_init_data,
पूर्ण;

अटल काष्ठा platक्रमm_device bq24022 = अणु
	.name = "gpio-regulator",
	.id   = -1,
	.dev  = अणु
		.platक्रमm_data = &bq24022_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table bq24022_gpiod_table = अणु
	.dev_id = "gpio-regulator",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO96_HX4700_BQ24022_ISET2,
			    शून्य, GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO72_HX4700_BQ24022_nCHARGE_EN,
			    "enable", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/*
 * StrataFlash
 */

अटल व्योम hx4700_set_vpp(काष्ठा platक्रमm_device *pdev, पूर्णांक vpp)
अणु
	gpio_set_value(GPIO91_HX4700_FLASH_VPEN, vpp);
पूर्ण

अटल काष्ठा resource strataflash_resource[] = अणु
	[0] = DEFINE_RES_MEM(PXA_CS0_PHYS, SZ_64M),
	[1] = DEFINE_RES_MEM(PXA_CS0_PHYS + SZ_64M, SZ_64M),
पूर्ण;

अटल काष्ठा physmap_flash_data strataflash_data = अणु
	.width = 4,
	.set_vpp = hx4700_set_vpp,
पूर्ण;

अटल काष्ठा platक्रमm_device strataflash = अणु
	.name          = "physmap-flash",
	.id            = -1,
	.resource      = strataflash_resource,
	.num_resources = ARRAY_SIZE(strataflash_resource),
	.dev = अणु
		.platक्रमm_data = &strataflash_data,
	पूर्ण,
पूर्ण;

/*
 * Maxim MAX1587A on PI2C
 */

अटल काष्ठा regulator_consumer_supply max1587a_consumer =
	REGULATOR_SUPPLY("vcc_core", शून्य);

अटल काष्ठा regulator_init_data max1587a_v3_info = अणु
	.स्थिरraपूर्णांकs = अणु
		.name = "vcc_core range",
		.min_uV =  900000,
		.max_uV = 1705000,
		.always_on = 1,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.num_consumer_supplies = 1,
	.consumer_supplies     = &max1587a_consumer,
पूर्ण;

अटल काष्ठा max1586_subdev_data max1587a_subdev = अणु
	.name = "vcc_core",
	.id   = MAX1586_V3,
	.platक्रमm_data = &max1587a_v3_info,
पूर्ण;

अटल काष्ठा max1586_platक्रमm_data max1587a_info = अणु
	.num_subdevs = 1,
	.subdevs     = &max1587a_subdev,
	.v3_gain     = MAX1586_GAIN_R24_3k32, /* 730..1550 mV */
पूर्ण;

अटल काष्ठा i2c_board_info __initdata pi2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("max1586", 0x14),
		.platक्रमm_data = &max1587a_info,
	पूर्ण,
पूर्ण;

/*
 * Asahi Kasei AK4641 on I2C
 */

अटल काष्ठा ak4641_platक्रमm_data ak4641_info = अणु
	.gpio_घातer = GPIO27_HX4700_CODEC_ON,
	.gpio_npdn  = GPIO109_HX4700_CODEC_nPDN,
पूर्ण;

अटल काष्ठा i2c_board_info i2c_board_info[] __initdata = अणु
	अणु
		I2C_BOARD_INFO("ak4641", 0x12),
		.platक्रमm_data = &ak4641_info,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device audio = अणु
	.name	= "hx4700-audio",
	.id	= -1,
पूर्ण;


/*
 * Platक्रमm devices
 */

अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&asic3,
	&gpio_keys,
	&navpoपूर्णांक,
	&backlight,
	&w3220,
	&hx4700_lcd,
	&egpio,
	&bq24022,
	&gpio_vbus,
	&घातer_supply,
	&strataflash,
	&audio,
पूर्ण;

अटल काष्ठा gpio global_gpios[] = अणु
	अणु GPIO12_HX4700_ASIC3_IRQ, GPIOF_IN, "ASIC3_IRQ" पूर्ण,
	अणु GPIO13_HX4700_W3220_IRQ, GPIOF_IN, "W3220_IRQ" पूर्ण,
	अणु GPIO14_HX4700_nWLAN_IRQ, GPIOF_IN, "WLAN_IRQ" पूर्ण,
	अणु GPIO59_HX4700_LCD_PC1,          GPIOF_OUT_INIT_HIGH, "LCD_PC1" पूर्ण,
	अणु GPIO62_HX4700_LCD_nRESET,       GPIOF_OUT_INIT_HIGH, "LCD_RESET" पूर्ण,
	अणु GPIO70_HX4700_LCD_SLIN1,        GPIOF_OUT_INIT_HIGH, "LCD_SLIN1" पूर्ण,
	अणु GPIO84_HX4700_LCD_SQN,          GPIOF_OUT_INIT_HIGH, "LCD_SQN" पूर्ण,
	अणु GPIO110_HX4700_LCD_LVDD_3V3_ON, GPIOF_OUT_INIT_HIGH, "LCD_LVDD" पूर्ण,
	अणु GPIO111_HX4700_LCD_AVDD_3V3_ON, GPIOF_OUT_INIT_HIGH, "LCD_AVDD" पूर्ण,
	अणु GPIO32_HX4700_RS232_ON,         GPIOF_OUT_INIT_HIGH, "RS232_ON" पूर्ण,
	अणु GPIO61_HX4700_W3220_nRESET,     GPIOF_OUT_INIT_HIGH, "W3220_nRESET" पूर्ण,
	अणु GPIO71_HX4700_ASIC3_nRESET,     GPIOF_OUT_INIT_HIGH, "ASIC3_nRESET" पूर्ण,
	अणु GPIO81_HX4700_CPU_GP_nRESET,    GPIOF_OUT_INIT_HIGH, "CPU_GP_nRESET" पूर्ण,
	अणु GPIO82_HX4700_EUART_RESET,      GPIOF_OUT_INIT_HIGH, "EUART_RESET" पूर्ण,
	अणु GPIO116_HX4700_CPU_HW_nRESET,   GPIOF_OUT_INIT_HIGH, "CPU_HW_nRESET" पूर्ण,
पूर्ण;

अटल व्योम __init hx4700_init(व्योम)
अणु
	पूर्णांक ret;

	PCFR = PCFR_GPR_EN | PCFR_OPDE;

	pxa2xx_mfp_config(ARRAY_AND_SIZE(hx4700_pin_config));
	gpio_set_wake(GPIO12_HX4700_ASIC3_IRQ, 1);
	ret = gpio_request_array(ARRAY_AND_SIZE(global_gpios));
	अगर (ret)
		pr_err ("hx4700: Failed to request GPIOs.\n");

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	gpiod_add_lookup_table(&bq24022_gpiod_table);
	gpiod_add_lookup_table(&gpio_vbus_gpiod_table);
	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));
	pwm_add_table(hx4700_pwm_lookup, ARRAY_SIZE(hx4700_pwm_lookup));

	pxa_set_ficp_info(&ficp_info);
	pxa27x_set_i2c_घातer_info(शून्य);
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(i2c_board_info));
	i2c_रेजिस्टर_board_info(1, ARRAY_AND_SIZE(pi2c_board_info));
	pxa2xx_set_spi_info(2, &pxa_ssp2_master_info);
	spi_रेजिस्टर_board_info(ARRAY_AND_SIZE(tsc2046_board_info));

	gpio_set_value(GPIO71_HX4700_ASIC3_nRESET, 0);
	mdelay(10);
	gpio_set_value(GPIO71_HX4700_ASIC3_nRESET, 1);
	mdelay(10);

	pxa_set_udc_info(&hx4700_udc_info);
	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

MACHINE_START(H4700, "HP iPAQ HX4700")
	.atag_offset  = 0x100,
	.map_io       = pxa27x_map_io,
	.nr_irqs      = HX4700_NR_IRQS,
	.init_irq     = pxa27x_init_irq,
	.handle_irq     = pxa27x_handle_irq,
	.init_machine = hx4700_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
