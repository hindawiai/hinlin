<शैली गुरु>
/*
 * Hardware definitions क्रम the Toshiba eseries PDAs
 *
 * Copyright (c) 2003 Ian Molton <spyro@f2s.com>
 *
 * This file is licensed under
 * the terms of the GNU General Public License version 2. This program
 * is licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 */

#समावेश <linux/clkdev.h>
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/clk-provider.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mfd/tc6387xb.h>
#समावेश <linux/mfd/tc6393xb.h>
#समावेश <linux/mfd/t7l66xb.h>
#समावेश <linux/mtd/rawnand.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/memblock.h>

#समावेश <video/w100fb.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach-types.h>

#समावेश "pxa25x.h"
#समावेश <mach/eseries-gpपन.स>
#समावेश "eseries-irq.h"
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>

#समावेश "devices.h"
#समावेश "generic.h"

/* Only e800 has 128MB RAM */
व्योम __init eseries_fixup(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	अगर (machine_is_e800())
		memblock_add(0xa0000000, SZ_128M);
	अन्यथा
		memblock_add(0xa0000000, SZ_64M);
पूर्ण

अटल काष्ठा gpiod_lookup_table e7xx_gpio_vbus_gpiod_table __maybe_unused = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_E7XX_USB_DISC,
			    "vbus", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO_E7XX_USB_PULLUP,
			    "pullup", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device e7xx_gpio_vbus __maybe_unused = अणु
	.name	= "gpio-vbus",
	.id	= -1,
पूर्ण;

काष्ठा pxaficp_platक्रमm_data e7xx_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= GPIO_E7XX_IR_OFF,
	.transceiver_cap	= IR_SIRMODE | IR_OFF,
पूर्ण;

पूर्णांक eseries_पंचांगio_enable(काष्ठा platक्रमm_device *dev)
अणु
	/* Reset - bring SUSPEND high beक्रमe PCLR */
	gpio_set_value(GPIO_ESERIES_TMIO_SUSPEND, 0);
	gpio_set_value(GPIO_ESERIES_TMIO_PCLR, 0);
	msleep(1);
	gpio_set_value(GPIO_ESERIES_TMIO_SUSPEND, 1);
	msleep(1);
	gpio_set_value(GPIO_ESERIES_TMIO_PCLR, 1);
	msleep(1);
	वापस 0;
पूर्ण

पूर्णांक eseries_पंचांगio_disable(काष्ठा platक्रमm_device *dev)
अणु
	gpio_set_value(GPIO_ESERIES_TMIO_SUSPEND, 0);
	gpio_set_value(GPIO_ESERIES_TMIO_PCLR, 0);
	वापस 0;
पूर्ण

पूर्णांक eseries_पंचांगio_suspend(काष्ठा platक्रमm_device *dev)
अणु
	gpio_set_value(GPIO_ESERIES_TMIO_SUSPEND, 0);
	वापस 0;
पूर्ण

पूर्णांक eseries_पंचांगio_resume(काष्ठा platक्रमm_device *dev)
अणु
	gpio_set_value(GPIO_ESERIES_TMIO_SUSPEND, 1);
	msleep(1);
	वापस 0;
पूर्ण

व्योम eseries_get_पंचांगio_gpios(व्योम)
अणु
	gpio_request(GPIO_ESERIES_TMIO_SUSPEND, शून्य);
	gpio_request(GPIO_ESERIES_TMIO_PCLR, शून्य);
	gpio_direction_output(GPIO_ESERIES_TMIO_SUSPEND, 0);
	gpio_direction_output(GPIO_ESERIES_TMIO_PCLR, 0);
पूर्ण

/* TMIO controller uses the same resources on all e-series machines. */
काष्ठा resource eseries_पंचांगio_resources[] = अणु
	[0] = अणु
		.start  = PXA_CS4_PHYS,
		.end    = PXA_CS4_PHYS + 0x1fffff,
		.flags  = IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start  = PXA_GPIO_TO_IRQ(GPIO_ESERIES_TMIO_IRQ),
		.end    = PXA_GPIO_TO_IRQ(GPIO_ESERIES_TMIO_IRQ),
		.flags  = IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

/* Some e-series hardware cannot control the 32K घड़ी */
अटल व्योम __init __maybe_unused eseries_रेजिस्टर_clks(व्योम)
अणु
	clk_रेजिस्टर_fixed_rate(शून्य, "CLK_CK32K", शून्य, 0, 32768);
पूर्ण

#अगर_घोषित CONFIG_MACH_E330
/* -------------------- e330 tc6387xb parameters -------------------- */

अटल काष्ठा tc6387xb_platक्रमm_data e330_tc6387xb_info = अणु
	.enable   = &eseries_पंचांगio_enable,
	.disable  = &eseries_पंचांगio_disable,
	.suspend  = &eseries_पंचांगio_suspend,
	.resume   = &eseries_पंचांगio_resume,
पूर्ण;

अटल काष्ठा platक्रमm_device e330_tc6387xb_device = अणु
	.name           = "tc6387xb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data = &e330_tc6387xb_info,
	पूर्ण,
	.num_resources = 2,
	.resource      = eseries_पंचांगio_resources,
पूर्ण;

/* --------------------------------------------------------------- */

अटल काष्ठा platक्रमm_device *e330_devices[] __initdata = अणु
	&e330_tc6387xb_device,
	&e7xx_gpio_vbus,
पूर्ण;

अटल व्योम __init e330_init(व्योम)
अणु
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	eseries_रेजिस्टर_clks();
	eseries_get_पंचांगio_gpios();
	gpiod_add_lookup_table(&e7xx_gpio_vbus_gpiod_table);
	platक्रमm_add_devices(ARRAY_AND_SIZE(e330_devices));
पूर्ण

MACHINE_START(E330, "Toshiba e330")
	/* Maपूर्णांकainer: Ian Molton (spyro@f2s.com) */
	.atag_offset	= 0x100,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= ESERIES_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.fixup		= eseries_fixup,
	.init_machine	= e330_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_E350
/* -------------------- e350 t7l66xb parameters -------------------- */

अटल काष्ठा t7l66xb_platक्रमm_data e350_t7l66xb_info = अणु
	.irq_base               = IRQ_BOARD_START,
	.enable                 = &eseries_पंचांगio_enable,
	.suspend                = &eseries_पंचांगio_suspend,
	.resume                 = &eseries_पंचांगio_resume,
पूर्ण;

अटल काष्ठा platक्रमm_device e350_t7l66xb_device = अणु
	.name           = "t7l66xb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data = &e350_t7l66xb_info,
	पूर्ण,
	.num_resources = 2,
	.resource      = eseries_पंचांगio_resources,
पूर्ण;

/* ---------------------------------------------------------- */

अटल काष्ठा platक्रमm_device *e350_devices[] __initdata = अणु
	&e350_t7l66xb_device,
	&e7xx_gpio_vbus,
पूर्ण;

अटल व्योम __init e350_init(व्योम)
अणु
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	eseries_रेजिस्टर_clks();
	eseries_get_पंचांगio_gpios();
	gpiod_add_lookup_table(&e7xx_gpio_vbus_gpiod_table);
	platक्रमm_add_devices(ARRAY_AND_SIZE(e350_devices));
पूर्ण

MACHINE_START(E350, "Toshiba e350")
	/* Maपूर्णांकainer: Ian Molton (spyro@f2s.com) */
	.atag_offset	= 0x100,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= ESERIES_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.fixup		= eseries_fixup,
	.init_machine	= e350_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_E400
/* ------------------------ E400 LCD definitions ------------------------ */

अटल काष्ठा pxafb_mode_info e400_pxafb_mode_info = अणु
	.pixघड़ी       = 140703,
	.xres           = 240,
	.yres           = 320,
	.bpp            = 16,
	.hsync_len      = 4,
	.left_margin    = 28,
	.right_margin   = 8,
	.vsync_len      = 3,
	.upper_margin   = 5,
	.lower_margin   = 6,
	.sync           = 0,
पूर्ण;

अटल काष्ठा pxafb_mach_info e400_pxafb_mach_info = अणु
	.modes          = &e400_pxafb_mode_info,
	.num_modes      = 1,
	.lcd_conn	= LCD_COLOR_TFT_16BPP,
	.lccr3          = 0,
	.pxafb_backlight_घातer  = शून्य,
पूर्ण;

/* ------------------------ E400 MFP config ----------------------------- */

अटल अचिन्हित दीर्घ e400_pin_config[] __initdata = अणु
	/* Chip selects */
	GPIO15_nCS_1,   /* CS1 - Flash */
	GPIO80_nCS_4,   /* CS4 - TMIO */

	/* Clocks */
	GPIO12_32KHz,

	/* BTUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,

	/* TMIO controller */
	GPIO19_GPIO, /* t7l66xb #PCLR */
	GPIO45_GPIO, /* t7l66xb #SUSPEND (NOT BTUART!) */

	/* wakeup */
	GPIO0_GPIO | WAKEUP_ON_EDGE_RISE,
पूर्ण;

/* ---------------------------------------------------------------------- */

अटल काष्ठा mtd_partition partition_a = अणु
	.name = "Internal NAND flash",
	.offset =  0,
	.size =  MTDPART_SIZ_FULL,
पूर्ण;

अटल uपूर्णांक8_t scan_ff_pattern[] = अणु 0xff, 0xff पूर्ण;

अटल काष्ठा nand_bbt_descr e400_t7l66xb_nand_bbt = अणु
	.options = 0,
	.offs = 4,
	.len = 2,
	.pattern = scan_ff_pattern
पूर्ण;

अटल काष्ठा पंचांगio_nand_data e400_t7l66xb_nand_config = अणु
	.num_partitions = 1,
	.partition = &partition_a,
	.badblock_pattern = &e400_t7l66xb_nand_bbt,
पूर्ण;

अटल काष्ठा t7l66xb_platक्रमm_data e400_t7l66xb_info = अणु
	.irq_base 		= IRQ_BOARD_START,
	.enable                 = &eseries_पंचांगio_enable,
	.suspend                = &eseries_पंचांगio_suspend,
	.resume                 = &eseries_पंचांगio_resume,

	.nand_data              = &e400_t7l66xb_nand_config,
पूर्ण;

अटल काष्ठा platक्रमm_device e400_t7l66xb_device = अणु
	.name           = "t7l66xb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data = &e400_t7l66xb_info,
	पूर्ण,
	.num_resources = 2,
	.resource      = eseries_पंचांगio_resources,
पूर्ण;

/* ---------------------------------------------------------- */

अटल काष्ठा platक्रमm_device *e400_devices[] __initdata = अणु
	&e400_t7l66xb_device,
	&e7xx_gpio_vbus,
पूर्ण;

अटल व्योम __init e400_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(e400_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	/* Fixme - e400 may have a चयनed घड़ी */
	eseries_रेजिस्टर_clks();
	eseries_get_पंचांगio_gpios();
	pxa_set_fb_info(शून्य, &e400_pxafb_mach_info);
	gpiod_add_lookup_table(&e7xx_gpio_vbus_gpiod_table);
	platक्रमm_add_devices(ARRAY_AND_SIZE(e400_devices));
पूर्ण

MACHINE_START(E400, "Toshiba e400")
	/* Maपूर्णांकainer: Ian Molton (spyro@f2s.com) */
	.atag_offset	= 0x100,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= ESERIES_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.fixup		= eseries_fixup,
	.init_machine	= e400_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_E740
/* ------------------------ e740 video support --------------------------- */

अटल काष्ठा w100_gen_regs e740_lcd_regs = अणु
	.lcd_क्रमmat =            0x00008023,
	.lcdd_cntl1 =            0x0f000000,
	.lcdd_cntl2 =            0x0003ffff,
	.genlcd_cntl1 =          0x00ffff03,
	.genlcd_cntl2 =          0x003c0f03,
	.genlcd_cntl3 =          0x000143aa,
पूर्ण;

अटल काष्ठा w100_mode e740_lcd_mode = अणु
	.xres            = 240,
	.yres            = 320,
	.left_margin     = 20,
	.right_margin    = 28,
	.upper_margin    = 9,
	.lower_margin    = 8,
	.crtc_ss         = 0x80140013,
	.crtc_ls         = 0x81150110,
	.crtc_gs         = 0x80050005,
	.crtc_vpos_gs    = 0x000a0009,
	.crtc_rev        = 0x0040010a,
	.crtc_dclk       = 0xa906000a,
	.crtc_gclk       = 0x80050108,
	.crtc_goe        = 0x80050108,
	.pll_freq        = 57,
	.pixclk_भागider         = 4,
	.pixclk_भागider_rotated = 4,
	.pixclk_src     = CLK_SRC_XTAL,
	.sysclk_भागider  = 1,
	.sysclk_src     = CLK_SRC_PLL,
	.crtc_ps1_active =       0x41060010,
पूर्ण;

अटल काष्ठा w100_gpio_regs e740_w100_gpio_info = अणु
	.init_data1 = 0x21002103,
	.gpio_dir1  = 0xffffdeff,
	.gpio_oe1   = 0x03c00643,
	.init_data2 = 0x003f003f,
	.gpio_dir2  = 0xffffffff,
	.gpio_oe2   = 0x000000ff,
पूर्ण;

अटल काष्ठा w100fb_mach_info e740_fb_info = अणु
	.modelist   = &e740_lcd_mode,
	.num_modes  = 1,
	.regs       = &e740_lcd_regs,
	.gpio       = &e740_w100_gpio_info,
	.xtal_freq = 14318000,
	.xtal_dbl   = 1,
पूर्ण;

अटल काष्ठा resource e740_fb_resources[] = अणु
	[0] = अणु
		.start          = 0x0c000000,
		.end            = 0x0cffffff,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device e740_fb_device = अणु
	.name           = "w100fb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data  = &e740_fb_info,
	पूर्ण,
	.num_resources  = ARRAY_SIZE(e740_fb_resources),
	.resource       = e740_fb_resources,
पूर्ण;

/* --------------------------- MFP Pin config -------------------------- */

अटल अचिन्हित दीर्घ e740_pin_config[] __initdata = अणु
	/* Chip selects */
	GPIO15_nCS_1,   /* CS1 - Flash */
	GPIO79_nCS_3,   /* CS3 - IMAGEON */
	GPIO80_nCS_4,   /* CS4 - TMIO */

	/* Clocks */
	GPIO12_32KHz,

	/* BTUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,

	/* TMIO controller */
	GPIO19_GPIO, /* t7l66xb #PCLR */
	GPIO45_GPIO, /* t7l66xb #SUSPEND (NOT BTUART!) */

	/* UDC */
	GPIO13_GPIO,
	GPIO3_GPIO,

	/* IrDA */
	GPIO38_GPIO | MFP_LPM_DRIVE_HIGH,

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	/* Audio घातer control */
	GPIO16_GPIO,  /* AC97 codec AVDD2 supply (analogue घातer) */
	GPIO40_GPIO,  /* Mic amp घातer */
	GPIO41_GPIO,  /* Headphone amp घातer */

	/* PC Card */
	GPIO8_GPIO,   /* CD0 */
	GPIO44_GPIO,  /* CD1 */
	GPIO11_GPIO,  /* IRQ0 */
	GPIO6_GPIO,   /* IRQ1 */
	GPIO27_GPIO,  /* RST0 */
	GPIO24_GPIO,  /* RST1 */
	GPIO20_GPIO,  /* PWR0 */
	GPIO23_GPIO,  /* PWR1 */
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

	/* wakeup */
	GPIO0_GPIO | WAKEUP_ON_EDGE_RISE,
पूर्ण;

/* -------------------- e740 t7l66xb parameters -------------------- */

अटल काष्ठा t7l66xb_platक्रमm_data e740_t7l66xb_info = अणु
	.irq_base 		= IRQ_BOARD_START,
	.enable                 = &eseries_पंचांगio_enable,
	.suspend                = &eseries_पंचांगio_suspend,
	.resume                 = &eseries_पंचांगio_resume,
पूर्ण;

अटल काष्ठा platक्रमm_device e740_t7l66xb_device = अणु
	.name           = "t7l66xb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data = &e740_t7l66xb_info,
	पूर्ण,
	.num_resources = 2,
	.resource      = eseries_पंचांगio_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device e740_audio_device = अणु
	.name		= "e740-audio",
	.id		= -1,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल काष्ठा platक्रमm_device *e740_devices[] __initdata = अणु
	&e740_fb_device,
	&e740_t7l66xb_device,
	&e7xx_gpio_vbus,
	&e740_audio_device,
पूर्ण;

अटल व्योम __init e740_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(e740_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	eseries_रेजिस्टर_clks();
	clk_add_alias("CLK_CK48M", e740_t7l66xb_device.name,
			"UDCCLK", &pxa25x_device_udc.dev),
	eseries_get_पंचांगio_gpios();
	gpiod_add_lookup_table(&e7xx_gpio_vbus_gpiod_table);
	platक्रमm_add_devices(ARRAY_AND_SIZE(e740_devices));
	pxa_set_ac97_info(शून्य);
	pxa_set_ficp_info(&e7xx_ficp_platक्रमm_data);
पूर्ण

MACHINE_START(E740, "Toshiba e740")
	/* Maपूर्णांकainer: Ian Molton (spyro@f2s.com) */
	.atag_offset	= 0x100,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= ESERIES_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.fixup		= eseries_fixup,
	.init_machine	= e740_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_E750
/* ---------------------- E750 LCD definitions -------------------- */

अटल काष्ठा w100_gen_regs e750_lcd_regs = अणु
	.lcd_क्रमmat =            0x00008003,
	.lcdd_cntl1 =            0x00000000,
	.lcdd_cntl2 =            0x0003ffff,
	.genlcd_cntl1 =          0x00fff003,
	.genlcd_cntl2 =          0x003c0f03,
	.genlcd_cntl3 =          0x000143aa,
पूर्ण;

अटल काष्ठा w100_mode e750_lcd_mode = अणु
	.xres            = 240,
	.yres            = 320,
	.left_margin     = 21,
	.right_margin    = 22,
	.upper_margin    = 5,
	.lower_margin    = 4,
	.crtc_ss         = 0x80150014,
	.crtc_ls         = 0x8014000d,
	.crtc_gs         = 0xc1000005,
	.crtc_vpos_gs    = 0x00020147,
	.crtc_rev        = 0x0040010a,
	.crtc_dclk       = 0xa1700030,
	.crtc_gclk       = 0x80cc0015,
	.crtc_goe        = 0x80cc0015,
	.crtc_ps1_active = 0x61060017,
	.pll_freq        = 57,
	.pixclk_भागider         = 4,
	.pixclk_भागider_rotated = 4,
	.pixclk_src     = CLK_SRC_XTAL,
	.sysclk_भागider  = 1,
	.sysclk_src     = CLK_SRC_PLL,
पूर्ण;

अटल काष्ठा w100_gpio_regs e750_w100_gpio_info = अणु
	.init_data1 = 0x01192f1b,
	.gpio_dir1  = 0xd5ffdeff,
	.gpio_oe1   = 0x000020bf,
	.init_data2 = 0x010f010f,
	.gpio_dir2  = 0xffffffff,
	.gpio_oe2   = 0x000001cf,
पूर्ण;

अटल काष्ठा w100fb_mach_info e750_fb_info = अणु
	.modelist   = &e750_lcd_mode,
	.num_modes  = 1,
	.regs       = &e750_lcd_regs,
	.gpio       = &e750_w100_gpio_info,
	.xtal_freq  = 14318000,
	.xtal_dbl   = 1,
पूर्ण;

अटल काष्ठा resource e750_fb_resources[] = अणु
	[0] = अणु
		.start          = 0x0c000000,
		.end            = 0x0cffffff,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device e750_fb_device = अणु
	.name           = "w100fb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data  = &e750_fb_info,
	पूर्ण,
	.num_resources  = ARRAY_SIZE(e750_fb_resources),
	.resource       = e750_fb_resources,
पूर्ण;

/* -------------------- e750 MFP parameters -------------------- */

अटल अचिन्हित दीर्घ e750_pin_config[] __initdata = अणु
	/* Chip selects */
	GPIO15_nCS_1,   /* CS1 - Flash */
	GPIO79_nCS_3,   /* CS3 - IMAGEON */
	GPIO80_nCS_4,   /* CS4 - TMIO */

	/* Clocks */
	GPIO11_3_6MHz,

	/* BTUART */
	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,

	/* TMIO controller */
	GPIO19_GPIO, /* t7l66xb #PCLR */
	GPIO45_GPIO, /* t7l66xb #SUSPEND (NOT BTUART!) */

	/* UDC */
	GPIO13_GPIO,
	GPIO3_GPIO,

	/* IrDA */
	GPIO38_GPIO | MFP_LPM_DRIVE_HIGH,

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	/* Audio घातer control */
	GPIO4_GPIO,  /* Headphone amp घातer */
	GPIO7_GPIO,  /* Speaker amp घातer */
	GPIO37_GPIO, /* Headphone detect */

	/* PC Card */
	GPIO8_GPIO,   /* CD0 */
	GPIO44_GPIO,  /* CD1 */
	/* GPIO11_GPIO,  IRQ0 */
	GPIO6_GPIO,   /* IRQ1 */
	GPIO27_GPIO,  /* RST0 */
	GPIO24_GPIO,  /* RST1 */
	GPIO20_GPIO,  /* PWR0 */
	GPIO23_GPIO,  /* PWR1 */
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

	/* wakeup */
	GPIO0_GPIO | WAKEUP_ON_EDGE_RISE,
पूर्ण;

/* ----------------- e750 tc6393xb parameters ------------------ */

अटल काष्ठा tc6393xb_platक्रमm_data e750_tc6393xb_info = अणु
	.irq_base       = IRQ_BOARD_START,
	.scr_pll2cr     = 0x0cc1,
	.scr_gper       = 0,
	.gpio_base      = -1,
	.suspend        = &eseries_पंचांगio_suspend,
	.resume         = &eseries_पंचांगio_resume,
	.enable         = &eseries_पंचांगio_enable,
	.disable        = &eseries_पंचांगio_disable,
पूर्ण;

अटल काष्ठा platक्रमm_device e750_tc6393xb_device = अणु
	.name           = "tc6393xb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data = &e750_tc6393xb_info,
	पूर्ण,
	.num_resources = 2,
	.resource      = eseries_पंचांगio_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device e750_audio_device = अणु
	.name		= "e750-audio",
	.id		= -1,
पूर्ण;

/* ------------------------------------------------------------- */

अटल काष्ठा platक्रमm_device *e750_devices[] __initdata = अणु
	&e750_fb_device,
	&e750_tc6393xb_device,
	&e7xx_gpio_vbus,
	&e750_audio_device,
पूर्ण;

अटल व्योम __init e750_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(e750_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	clk_add_alias("CLK_CK3P6MI", e750_tc6393xb_device.name,
			"GPIO11_CLK", शून्य),
	eseries_get_पंचांगio_gpios();
	gpiod_add_lookup_table(&e7xx_gpio_vbus_gpiod_table);
	platक्रमm_add_devices(ARRAY_AND_SIZE(e750_devices));
	pxa_set_ac97_info(शून्य);
	pxa_set_ficp_info(&e7xx_ficp_platक्रमm_data);
पूर्ण

MACHINE_START(E750, "Toshiba e750")
	/* Maपूर्णांकainer: Ian Molton (spyro@f2s.com) */
	.atag_offset	= 0x100,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= ESERIES_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.fixup		= eseries_fixup,
	.init_machine	= e750_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_E800
/* ------------------------ e800 LCD definitions ------------------------- */

अटल अचिन्हित दीर्घ e800_pin_config[] __initdata = अणु
	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	/* tc6393xb */
	GPIO11_3_6MHz,
पूर्ण;

अटल काष्ठा w100_gen_regs e800_lcd_regs = अणु
	.lcd_क्रमmat =            0x00008003,
	.lcdd_cntl1 =            0x02a00000,
	.lcdd_cntl2 =            0x0003ffff,
	.genlcd_cntl1 =          0x000ff2a3,
	.genlcd_cntl2 =          0x000002a3,
	.genlcd_cntl3 =          0x000102aa,
पूर्ण;

अटल काष्ठा w100_mode e800_lcd_mode[2] = अणु
	[0] = अणु
		.xres            = 480,
		.yres            = 640,
		.left_margin     = 52,
		.right_margin    = 148,
		.upper_margin    = 2,
		.lower_margin    = 6,
		.crtc_ss         = 0x80350034,
		.crtc_ls         = 0x802b0026,
		.crtc_gs         = 0x80160016,
		.crtc_vpos_gs    = 0x00020003,
		.crtc_rev        = 0x0040001d,
		.crtc_dclk       = 0xe0000000,
		.crtc_gclk       = 0x82a50049,
		.crtc_goe        = 0x80ee001c,
		.crtc_ps1_active = 0x00000000,
		.pll_freq        = 128,
		.pixclk_भागider         = 4,
		.pixclk_भागider_rotated = 6,
		.pixclk_src     = CLK_SRC_PLL,
		.sysclk_भागider  = 0,
		.sysclk_src     = CLK_SRC_PLL,
	पूर्ण,
	[1] = अणु
		.xres            = 240,
		.yres            = 320,
		.left_margin     = 15,
		.right_margin    = 88,
		.upper_margin    = 0,
		.lower_margin    = 7,
		.crtc_ss         = 0xd010000f,
		.crtc_ls         = 0x80070003,
		.crtc_gs         = 0x80000000,
		.crtc_vpos_gs    = 0x01460147,
		.crtc_rev        = 0x00400003,
		.crtc_dclk       = 0xa1700030,
		.crtc_gclk       = 0x814b0008,
		.crtc_goe        = 0x80cc0015,
		.crtc_ps1_active = 0x00000000,
		.pll_freq        = 100,
		.pixclk_भागider         = 6, /* Wince uses 14 which gives a */
		.pixclk_भागider_rotated = 6, /* 7MHz Pclk. We use a 14MHz one */
		.pixclk_src     = CLK_SRC_PLL,
		.sysclk_भागider  = 0,
		.sysclk_src     = CLK_SRC_PLL,
	पूर्ण
पूर्ण;


अटल काष्ठा w100_gpio_regs e800_w100_gpio_info = अणु
	.init_data1 = 0xc13fc019,
	.gpio_dir1  = 0x3e40df7f,
	.gpio_oe1   = 0x003c3000,
	.init_data2 = 0x00000000,
	.gpio_dir2  = 0x00000000,
	.gpio_oe2   = 0x00000000,
पूर्ण;

अटल काष्ठा w100_mem_info e800_w100_mem_info = अणु
	.ext_cntl        = 0x09640011,
	.sdram_mode_reg  = 0x00600021,
	.ext_timing_cntl = 0x10001545,
	.io_cntl         = 0x7ddd7333,
	.size            = 0x1fffff,
पूर्ण;

अटल व्योम e800_tg_change(काष्ठा w100fb_par *par)
अणु
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = w100fb_gpio_पढ़ो(W100_GPIO_PORT_A);
	अगर (par->mode->xres == 480)
		पंचांगp |= 0x100;
	अन्यथा
		पंचांगp &= ~0x100;
	w100fb_gpio_ग_लिखो(W100_GPIO_PORT_A, पंचांगp);
पूर्ण

अटल काष्ठा w100_tg_info e800_tg_info = अणु
	.change = e800_tg_change,
पूर्ण;

अटल काष्ठा w100fb_mach_info e800_fb_info = अणु
	.modelist   = e800_lcd_mode,
	.num_modes  = 2,
	.regs       = &e800_lcd_regs,
	.gpio       = &e800_w100_gpio_info,
	.mem        = &e800_w100_mem_info,
	.tg         = &e800_tg_info,
	.xtal_freq  = 16000000,
पूर्ण;

अटल काष्ठा resource e800_fb_resources[] = अणु
	[0] = अणु
		.start          = 0x0c000000,
		.end            = 0x0cffffff,
		.flags          = IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device e800_fb_device = अणु
	.name           = "w100fb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data  = &e800_fb_info,
	पूर्ण,
	.num_resources  = ARRAY_SIZE(e800_fb_resources),
	.resource       = e800_fb_resources,
पूर्ण;

/* --------------------------- UDC definitions --------------------------- */

अटल काष्ठा gpiod_lookup_table e800_gpio_vbus_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_E800_USB_DISC,
			    "vbus", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO_E800_USB_PULLUP,
			    "pullup", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device e800_gpio_vbus = अणु
	.name	= "gpio-vbus",
	.id	= -1,
पूर्ण;


/* ----------------- e800 tc6393xb parameters ------------------ */

अटल काष्ठा tc6393xb_platक्रमm_data e800_tc6393xb_info = अणु
	.irq_base       = IRQ_BOARD_START,
	.scr_pll2cr     = 0x0cc1,
	.scr_gper       = 0,
	.gpio_base      = -1,
	.suspend        = &eseries_पंचांगio_suspend,
	.resume         = &eseries_पंचांगio_resume,
	.enable         = &eseries_पंचांगio_enable,
	.disable        = &eseries_पंचांगio_disable,
पूर्ण;

अटल काष्ठा platक्रमm_device e800_tc6393xb_device = अणु
	.name           = "tc6393xb",
	.id             = -1,
	.dev            = अणु
		.platक्रमm_data = &e800_tc6393xb_info,
	पूर्ण,
	.num_resources = 2,
	.resource      = eseries_पंचांगio_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device e800_audio_device = अणु
	.name		= "e800-audio",
	.id		= -1,
पूर्ण;

/* ----------------------------------------------------------------------- */

अटल काष्ठा platक्रमm_device *e800_devices[] __initdata = अणु
	&e800_fb_device,
	&e800_tc6393xb_device,
	&e800_gpio_vbus,
	&e800_audio_device,
पूर्ण;

अटल व्योम __init e800_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(e800_pin_config));
	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	clk_add_alias("CLK_CK3P6MI", e800_tc6393xb_device.name,
			"GPIO11_CLK", शून्य),
	eseries_get_पंचांगio_gpios();
	gpiod_add_lookup_table(&e800_gpio_vbus_gpiod_table);
	platक्रमm_add_devices(ARRAY_AND_SIZE(e800_devices));
	pxa_set_ac97_info(शून्य);
पूर्ण

MACHINE_START(E800, "Toshiba e800")
	/* Maपूर्णांकainer: Ian Molton (spyro@f2s.com) */
	.atag_offset	= 0x100,
	.map_io		= pxa25x_map_io,
	.nr_irqs	= ESERIES_NR_IRQS,
	.init_irq	= pxa25x_init_irq,
	.handle_irq	= pxa25x_handle_irq,
	.fixup		= eseries_fixup,
	.init_machine	= e800_init,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
#पूर्ण_अगर
