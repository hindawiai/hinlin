<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/arch/arm/mach-pxa/cm-x300.c
 *
 * Support क्रम the CompuLab CM-X300 modules
 *
 * Copyright (C) 2008,2009 CompuLab Ltd.
 *
 * Mike Rapoport <mike@compulab.co.il>
 * Igor Grinberg <grinberg@compulab.co.il>
 */
#घोषणा pr_fmt(fmt) "%s: " fmt, __func__

#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>

#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/leds.h>
#समावेश <linux/platक्रमm_data/rtc-v3020.h>
#समावेश <linux/pwm.h>
#समावेश <linux/pwm_backlight.h>

#समावेश <linux/i2c.h>
#समावेश <linux/platक्रमm_data/pca953x.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <linux/mfd/da903x.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/घातer_supply.h>
#समावेश <linux/apm-emulation.h>

#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/spi_gpपन.स>
#समावेश <linux/spi/tकरो24m.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश "pxa300.h"
#समावेश "pxa27x-udc.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/usb-pxa3xx-ulpi.h>

#समावेश <यंत्र/mach/map.h>

#समावेश "generic.h"
#समावेश "devices.h"

#घोषणा CM_X300_ETH_PHYS	0x08000010

#घोषणा GPIO82_MMC_IRQ		(82)
#घोषणा GPIO85_MMC_WP		(85)

#घोषणा	CM_X300_MMC_IRQ		PXA_GPIO_TO_IRQ(GPIO82_MMC_IRQ)

#घोषणा GPIO95_RTC_CS		(95)
#घोषणा GPIO96_RTC_WR		(96)
#घोषणा GPIO97_RTC_RD		(97)
#घोषणा GPIO98_RTC_IO		(98)

#घोषणा GPIO_ULPI_PHY_RST	(127)

अटल mfp_cfg_t cm_x3xx_mfp_cfg[] __initdata = अणु
	/* LCD */
	GPIO54_LCD_LDD_0,
	GPIO55_LCD_LDD_1,
	GPIO56_LCD_LDD_2,
	GPIO57_LCD_LDD_3,
	GPIO58_LCD_LDD_4,
	GPIO59_LCD_LDD_5,
	GPIO60_LCD_LDD_6,
	GPIO61_LCD_LDD_7,
	GPIO62_LCD_LDD_8,
	GPIO63_LCD_LDD_9,
	GPIO64_LCD_LDD_10,
	GPIO65_LCD_LDD_11,
	GPIO66_LCD_LDD_12,
	GPIO67_LCD_LDD_13,
	GPIO68_LCD_LDD_14,
	GPIO69_LCD_LDD_15,
	GPIO72_LCD_FCLK,
	GPIO73_LCD_LCLK,
	GPIO74_LCD_PCLK,
	GPIO75_LCD_BIAS,

	/* BTUART */
	GPIO111_UART2_RTS,
	GPIO112_UART2_RXD | MFP_LPM_EDGE_FALL,
	GPIO113_UART2_TXD,
	GPIO114_UART2_CTS | MFP_LPM_EDGE_BOTH,

	/* STUART */
	GPIO109_UART3_TXD,
	GPIO110_UART3_RXD | MFP_LPM_EDGE_FALL,

	/* AC97 */
	GPIO23_AC97_nACRESET,
	GPIO24_AC97_SYSCLK,
	GPIO29_AC97_BITCLK,
	GPIO25_AC97_SDATA_IN_0,
	GPIO27_AC97_SDATA_OUT,
	GPIO28_AC97_SYNC,

	/* Keypad */
	GPIO115_KP_MKIN_0 | MFP_LPM_EDGE_BOTH,
	GPIO116_KP_MKIN_1 | MFP_LPM_EDGE_BOTH,
	GPIO117_KP_MKIN_2 | MFP_LPM_EDGE_BOTH,
	GPIO118_KP_MKIN_3 | MFP_LPM_EDGE_BOTH,
	GPIO119_KP_MKIN_4 | MFP_LPM_EDGE_BOTH,
	GPIO120_KP_MKIN_5 | MFP_LPM_EDGE_BOTH,
	GPIO2_2_KP_MKIN_6 | MFP_LPM_EDGE_BOTH,
	GPIO3_2_KP_MKIN_7 | MFP_LPM_EDGE_BOTH,
	GPIO121_KP_MKOUT_0,
	GPIO122_KP_MKOUT_1,
	GPIO123_KP_MKOUT_2,
	GPIO124_KP_MKOUT_3,
	GPIO125_KP_MKOUT_4,
	GPIO4_2_KP_MKOUT_5,

	/* MMC1 */
	GPIO3_MMC1_DAT0,
	GPIO4_MMC1_DAT1 | MFP_LPM_EDGE_BOTH,
	GPIO5_MMC1_DAT2,
	GPIO6_MMC1_DAT3,
	GPIO7_MMC1_CLK,
	GPIO8_MMC1_CMD,	/* CMD0 क्रम slot 0 */

	/* MMC2 */
	GPIO9_MMC2_DAT0,
	GPIO10_MMC2_DAT1 | MFP_LPM_EDGE_BOTH,
	GPIO11_MMC2_DAT2,
	GPIO12_MMC2_DAT3,
	GPIO13_MMC2_CLK,
	GPIO14_MMC2_CMD,

	/* FFUART */
	GPIO30_UART1_RXD | MFP_LPM_EDGE_FALL,
	GPIO31_UART1_TXD,
	GPIO32_UART1_CTS,
	GPIO37_UART1_RTS,
	GPIO33_UART1_DCD,
	GPIO34_UART1_DSR | MFP_LPM_EDGE_FALL,
	GPIO35_UART1_RI,
	GPIO36_UART1_DTR,

	/* GPIOs */
	GPIO82_GPIO | MFP_PULL_HIGH,	/* MMC CD */
	GPIO85_GPIO,			/* MMC WP */
	GPIO99_GPIO,			/* Ethernet IRQ */

	/* RTC GPIOs */
	GPIO95_GPIO | MFP_LPM_DRIVE_HIGH,	/* RTC CS */
	GPIO96_GPIO | MFP_LPM_DRIVE_HIGH,	/* RTC WR */
	GPIO97_GPIO | MFP_LPM_DRIVE_HIGH,	/* RTC RD */
	GPIO98_GPIO,				/* RTC IO */

	/* Standard I2C */
	GPIO21_I2C_SCL,
	GPIO22_I2C_SDA,

	/* PWM Backlight */
	GPIO19_PWM2_OUT,
पूर्ण;

अटल mfp_cfg_t cm_x3xx_rev_lt130_mfp_cfg[] __initdata = अणु
	/* GPIOs */
	GPIO79_GPIO,			/* LED */
	GPIO77_GPIO,			/* WiFi reset */
	GPIO78_GPIO,			/* BT reset */
पूर्ण;

अटल mfp_cfg_t cm_x3xx_rev_ge130_mfp_cfg[] __initdata = अणु
	/* GPIOs */
	GPIO76_GPIO,			/* LED */
	GPIO71_GPIO,			/* WiFi reset */
	GPIO70_GPIO,			/* BT reset */
पूर्ण;

अटल mfp_cfg_t cm_x310_mfp_cfg[] __initdata = अणु
	/* USB PORT 2 */
	ULPI_STP,
	ULPI_NXT,
	ULPI_सूची,
	GPIO30_ULPI_DATA_OUT_0,
	GPIO31_ULPI_DATA_OUT_1,
	GPIO32_ULPI_DATA_OUT_2,
	GPIO33_ULPI_DATA_OUT_3,
	GPIO34_ULPI_DATA_OUT_4,
	GPIO35_ULPI_DATA_OUT_5,
	GPIO36_ULPI_DATA_OUT_6,
	GPIO37_ULPI_DATA_OUT_7,
	GPIO38_ULPI_CLK,
	/* बाह्यal PHY reset pin */
	GPIO127_GPIO,

	/* USB PORT 3 */
	GPIO77_USB_P3_1,
	GPIO78_USB_P3_2,
	GPIO79_USB_P3_3,
	GPIO80_USB_P3_4,
	GPIO81_USB_P3_5,
	GPIO82_USB_P3_6,
	GPIO0_2_USBH_PEN,
पूर्ण;

#अगर defined(CONFIG_DM9000) || defined(CONFIG_DM9000_MODULE)
अटल काष्ठा resource dm9000_resources[] = अणु
	[0] = अणु
		.start	= CM_X300_ETH_PHYS,
		.end	= CM_X300_ETH_PHYS + 0x3,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= CM_X300_ETH_PHYS + 0x4,
		.end	= CM_X300_ETH_PHYS + 0x4 + 500,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start	= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO99)),
		.end	= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO99)),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा dm9000_plat_data cm_x300_dm9000_platdata = अणु
	.flags		= DM9000_PLATF_16BITONLY | DM9000_PLATF_NO_EEPROM,
पूर्ण;

अटल काष्ठा platक्रमm_device dm9000_device = अणु
	.name		= "dm9000",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(dm9000_resources),
	.resource	= dm9000_resources,
	.dev		= अणु
		.platक्रमm_data = &cm_x300_dm9000_platdata,
	पूर्ण

पूर्ण;

अटल व्योम __init cm_x300_init_dm9000(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&dm9000_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_dm9000(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* LCD */
#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pxafb_mode_info cm_x300_lcd_modes[] = अणु
	[0] = अणु
		.pixघड़ी	= 38250,
		.bpp		= 16,
		.xres		= 480,
		.yres		= 640,
		.hsync_len	= 8,
		.vsync_len	= 2,
		.left_margin	= 8,
		.upper_margin	= 2,
		.right_margin	= 24,
		.lower_margin	= 4,
		.cmap_greyscale	= 0,
	पूर्ण,
	[1] = अणु
		.pixघड़ी	= 153800,
		.bpp		= 16,
		.xres		= 240,
		.yres		= 320,
		.hsync_len	= 8,
		.vsync_len	= 2,
		.left_margin	= 8,
		.upper_margin	= 2,
		.right_margin	= 88,
		.lower_margin	= 2,
		.cmap_greyscale	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info cm_x300_lcd = अणु
	.modes			= cm_x300_lcd_modes,
	.num_modes		= ARRAY_SIZE(cm_x300_lcd_modes),
	.lcd_conn		= LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL,
पूर्ण;

अटल व्योम __init cm_x300_init_lcd(व्योम)
अणु
	pxa_set_fb_info(शून्य, &cm_x300_lcd);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_lcd(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_BACKLIGHT_PWM) || defined(CONFIG_BACKLIGHT_PWM_MODULE)
अटल काष्ठा pwm_lookup cm_x300_pwm_lookup[] = अणु
	PWM_LOOKUP("pxa27x-pwm.0", 1, "pwm-backlight.0", शून्य, 10000,
		   PWM_POLARITY_NORMAL),
पूर्ण;

अटल काष्ठा platक्रमm_pwm_backlight_data cm_x300_backlight_data = अणु
	.max_brightness	= 100,
	.dft_brightness	= 100,
पूर्ण;

अटल काष्ठा platक्रमm_device cm_x300_backlight_device = अणु
	.name		= "pwm-backlight",
	.dev		= अणु
		.parent = &pxa27x_device_pwm0.dev,
		.platक्रमm_data	= &cm_x300_backlight_data,
	पूर्ण,
पूर्ण;

अटल व्योम cm_x300_init_bl(व्योम)
अणु
	pwm_add_table(cm_x300_pwm_lookup, ARRAY_SIZE(cm_x300_pwm_lookup));
	platक्रमm_device_रेजिस्टर(&cm_x300_backlight_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_bl(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SPI_GPIO) || defined(CONFIG_SPI_GPIO_MODULE)
#घोषणा GPIO_LCD_BASE	(144)
#घोषणा GPIO_LCD_DIN	(GPIO_LCD_BASE + 8)	/* aux_gpio3_0 */
#घोषणा GPIO_LCD_DOUT	(GPIO_LCD_BASE + 9)	/* aux_gpio3_1 */
#घोषणा GPIO_LCD_SCL	(GPIO_LCD_BASE + 10)	/* aux_gpio3_2 */
#घोषणा GPIO_LCD_CS	(GPIO_LCD_BASE + 11)	/* aux_gpio3_3 */
#घोषणा LCD_SPI_BUS_NUM	(1)

अटल काष्ठा spi_gpio_platक्रमm_data cm_x300_spi_gpio_pdata = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल काष्ठा platक्रमm_device cm_x300_spi_gpio = अणु
	.name		= "spi_gpio",
	.id		= LCD_SPI_BUS_NUM,
	.dev		= अणु
		.platक्रमm_data	= &cm_x300_spi_gpio_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpiod_lookup_table cm_x300_spi_gpiod_table = अणु
	.dev_id         = "spi_gpio",
	.table          = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO_LCD_SCL,
			    "sck", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO_LCD_DIN,
			    "mosi", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO_LCD_DOUT,
			    "miso", GPIO_ACTIVE_HIGH),
		GPIO_LOOKUP("gpio-pxa", GPIO_LCD_CS,
			    "cs", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा tकरो24m_platक्रमm_data cm_x300_tकरो24m_pdata = अणु
	.model = TDO35S,
पूर्ण;

अटल काष्ठा spi_board_info cm_x300_spi_devices[] __initdata = अणु
	अणु
		.modalias		= "tdo24m",
		.max_speed_hz		= 1000000,
		.bus_num		= LCD_SPI_BUS_NUM,
		.chip_select		= 0,
		.platक्रमm_data		= &cm_x300_tकरो24m_pdata,
	पूर्ण,
पूर्ण;

अटल व्योम __init cm_x300_init_spi(व्योम)
अणु
	spi_रेजिस्टर_board_info(cm_x300_spi_devices,
				ARRAY_SIZE(cm_x300_spi_devices));
	gpiod_add_lookup_table(&cm_x300_spi_gpiod_table);
	platक्रमm_device_रेजिस्टर(&cm_x300_spi_gpio);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_spi(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SND_PXA2XX_LIB_AC97)
अटल व्योम __init cm_x300_init_ac97(व्योम)
अणु
	pxa_set_ac97_info(शून्य);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_ac97(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL)
अटल काष्ठा mtd_partition cm_x300_nand_partitions[] = अणु
	[0] = अणु
		.name        = "OBM",
		.offset      = 0,
		.size        = SZ_256K,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	[1] = अणु
		.name        = "U-Boot",
		.offset      = MTDPART_OFS_APPEND,
		.size        = SZ_256K,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	[2] = अणु
		.name        = "Environment",
		.offset      = MTDPART_OFS_APPEND,
		.size        = SZ_256K,
	पूर्ण,
	[3] = अणु
		.name        = "reserved",
		.offset      = MTDPART_OFS_APPEND,
		.size        = SZ_256K + SZ_1M,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	[4] = अणु
		.name        = "kernel",
		.offset      = MTDPART_OFS_APPEND,
		.size        = SZ_4M,
	पूर्ण,
	[5] = अणु
		.name        = "fs",
		.offset      = MTDPART_OFS_APPEND,
		.size        = MTDPART_SIZ_FULL,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxa3xx_nand_platक्रमm_data cm_x300_nand_info = अणु
	.keep_config	= 1,
	.parts		= cm_x300_nand_partitions,
	.nr_parts	= ARRAY_SIZE(cm_x300_nand_partitions),
पूर्ण;

अटल व्योम __init cm_x300_init_nand(व्योम)
अणु
	pxa3xx_set_nand_info(&cm_x300_nand_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_nand(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_MMC) || defined(CONFIG_MMC_MODULE)
अटल काष्ठा pxamci_platक्रमm_data cm_x300_mci_platक्रमm_data = अणु
	.detect_delay_ms	= 200,
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table cm_x300_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		/* Card detect on GPIO 82 */
		GPIO_LOOKUP("gpio-pxa", GPIO82_MMC_IRQ, "cd", GPIO_ACTIVE_LOW),
		/* Write protect on GPIO 85 */
		GPIO_LOOKUP("gpio-pxa", GPIO85_MMC_WP, "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

/* The second MMC slot of CM-X300 is hardwired to Libertas card and has
   no detection/ro pins */
अटल पूर्णांक cm_x300_mci2_init(काष्ठा device *dev,
			     irq_handler_t cm_x300_detect_पूर्णांक,
	व्योम *data)
अणु
	वापस 0;
पूर्ण

अटल व्योम cm_x300_mci2_निकास(काष्ठा device *dev, व्योम *data)
अणु
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data cm_x300_mci2_platक्रमm_data = अणु
	.detect_delay_ms	= 200,
	.ocr_mask		= MMC_VDD_32_33|MMC_VDD_33_34,
	.init 			= cm_x300_mci2_init,
	.निकास			= cm_x300_mci2_निकास,
पूर्ण;

अटल व्योम __init cm_x300_init_mmc(व्योम)
अणु
	gpiod_add_lookup_table(&cm_x300_mci_gpio_table);
	pxa_set_mci_info(&cm_x300_mci_platक्रमm_data);
	pxa3xx_set_mci2_info(&cm_x300_mci2_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_mmc(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_PXA310_ULPI)
अटल काष्ठा clk *pout_clk;

अटल पूर्णांक cm_x300_ulpi_phy_reset(व्योम)
अणु
	पूर्णांक err;

	/* reset the PHY */
	err = gpio_request_one(GPIO_ULPI_PHY_RST, GPIOF_OUT_INIT_LOW,
			       "ulpi reset");
	अगर (err) अणु
		pr_err("failed to request ULPI reset GPIO: %d\n", err);
		वापस err;
	पूर्ण

	msleep(10);
	gpio_set_value(GPIO_ULPI_PHY_RST, 1);
	msleep(10);

	gpio_मुक्त(GPIO_ULPI_PHY_RST);

	वापस 0;
पूर्ण

अटल पूर्णांक cm_x300_u2d_init(काष्ठा device *dev)
अणु
	पूर्णांक err = 0;

	अगर (cpu_is_pxa310()) अणु
		/* CLK_POUT is connected to the ULPI PHY */
		pout_clk = clk_get(शून्य, "CLK_POUT");
		अगर (IS_ERR(pout_clk)) अणु
			err = PTR_ERR(pout_clk);
			pr_err("failed to get CLK_POUT: %d\n", err);
			वापस err;
		पूर्ण
		clk_prepare_enable(pout_clk);

		err = cm_x300_ulpi_phy_reset();
		अगर (err) अणु
			clk_disable(pout_clk);
			clk_put(pout_clk);
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम cm_x300_u2d_निकास(काष्ठा device *dev)
अणु
	अगर (cpu_is_pxa310()) अणु
		clk_disable_unprepare(pout_clk);
		clk_put(pout_clk);
	पूर्ण
पूर्ण

अटल काष्ठा pxa3xx_u2d_platक्रमm_data cm_x300_u2d_platक्रमm_data = अणु
	.ulpi_mode	= ULPI_SER_6PIN,
	.init		= cm_x300_u2d_init,
	.निकास		= cm_x300_u2d_निकास,
पूर्ण;

अटल व्योम __init cm_x300_init_u2d(व्योम)
अणु
	pxa3xx_set_u2d_info(&cm_x300_u2d_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_u2d(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
अटल पूर्णांक cm_x300_ohci_init(काष्ठा device *dev)
अणु
	अगर (cpu_is_pxa300())
		UP2OCR = UP2OCR_HXS
			| UP2OCR_HXOE | UP2OCR_DMPDE | UP2OCR_DPPDE;

	वापस 0;
पूर्ण

अटल काष्ठा pxaohci_platक्रमm_data cm_x300_ohci_platक्रमm_data = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT_ALL | POWER_CONTROL_LOW,
	.init		= cm_x300_ohci_init,
पूर्ण;

अटल व्योम __init cm_x300_init_ohci(व्योम)
अणु
	pxa_set_ohci_info(&cm_x300_ohci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_ohci(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
अटल काष्ठा gpio_led cm_x300_leds[] = अणु
	[0] = अणु
		.name = "cm-x300:green",
		.शेष_trigger = "heartbeat",
		.active_low = 1,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data cm_x300_gpio_led_pdata = अणु
	.num_leds = ARRAY_SIZE(cm_x300_leds),
	.leds = cm_x300_leds,
पूर्ण;

अटल काष्ठा platक्रमm_device cm_x300_led_device = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &cm_x300_gpio_led_pdata,
	पूर्ण,
पूर्ण;

अटल व्योम __init cm_x300_init_leds(व्योम)
अणु
	अगर (प्रणाली_rev < 130)
		cm_x300_leds[0].gpio = 79;
	अन्यथा
		cm_x300_leds[0].gpio = 76;

	platक्रमm_device_रेजिस्टर(&cm_x300_led_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_leds(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_I2C) || defined(CONFIG_I2C_MODULE)
/* PCA9555 */
अटल काष्ठा pca953x_platक्रमm_data cm_x300_gpio_ext_pdata_0 = अणु
	.gpio_base = 128,
पूर्ण;

अटल काष्ठा pca953x_platक्रमm_data cm_x300_gpio_ext_pdata_1 = अणु
	.gpio_base = 144,
पूर्ण;

अटल काष्ठा i2c_board_info cm_x300_gpio_ext_info[] = अणु
	[0] = अणु
		I2C_BOARD_INFO("pca9555", 0x24),
		.platक्रमm_data = &cm_x300_gpio_ext_pdata_0,
	पूर्ण,
	[1] = अणु
		I2C_BOARD_INFO("pca9555", 0x25),
		.platक्रमm_data = &cm_x300_gpio_ext_pdata_1,
	पूर्ण,
पूर्ण;

अटल व्योम __init cm_x300_init_i2c(व्योम)
अणु
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, cm_x300_gpio_ext_info,
				ARRAY_SIZE(cm_x300_gpio_ext_info));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_i2c(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_RTC_DRV_V3020) || defined(CONFIG_RTC_DRV_V3020_MODULE)
काष्ठा v3020_platक्रमm_data cm_x300_v3020_pdata = अणु
	.use_gpio	= 1,
	.gpio_cs	= GPIO95_RTC_CS,
	.gpio_wr	= GPIO96_RTC_WR,
	.gpio_rd	= GPIO97_RTC_RD,
	.gpio_io	= GPIO98_RTC_IO,
पूर्ण;

अटल काष्ठा platक्रमm_device cm_x300_rtc_device = अणु
	.name		= "v3020",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &cm_x300_v3020_pdata,
	पूर्ण
पूर्ण;

अटल व्योम __init cm_x300_init_rtc(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&cm_x300_rtc_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम cm_x300_init_rtc(व्योम) अणुपूर्ण
#पूर्ण_अगर

/* Battery */
काष्ठा घातer_supply_info cm_x300_psy_info = अणु
	.name = "battery",
	.technology = POWER_SUPPLY_TECHNOLOGY_LIPO,
	.voltage_max_design = 4200000,
	.voltage_min_design = 3000000,
	.use_क्रम_apm = 1,
पूर्ण;

अटल व्योम cm_x300_battery_low(व्योम)
अणु
#अगर defined(CONFIG_APM_EMULATION)
	apm_queue_event(APM_LOW_BATTERY);
#पूर्ण_अगर
पूर्ण

अटल व्योम cm_x300_battery_critical(व्योम)
अणु
#अगर defined(CONFIG_APM_EMULATION)
	apm_queue_event(APM_CRITICAL_SUSPEND);
#पूर्ण_अगर
पूर्ण

काष्ठा da9030_battery_info cm_x300_battery_info = अणु
	.battery_info = &cm_x300_psy_info,

	.अक्षरge_milliamp = 1000,
	.अक्षरge_millivolt = 4200,

	.vbat_low = 3600,
	.vbat_crit = 3400,
	.vbat_अक्षरge_start = 4100,
	.vbat_अक्षरge_stop = 4200,
	.vbat_अक्षरge_restart = 4000,

	.vअक्षरge_min = 3200,
	.vअक्षरge_max = 5500,

	.tbat_low = 197,
	.tbat_high = 78,
	.tbat_restart = 100,

	.baपंचांगon_पूर्णांकerval = 0,

	.battery_low = cm_x300_battery_low,
	.battery_critical = cm_x300_battery_critical,
पूर्ण;

अटल काष्ठा regulator_consumer_supply buck2_consumers[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data buck2_data = अणु
	.स्थिरraपूर्णांकs = अणु
		.min_uV = 1375000,
		.max_uV = 1375000,
		.state_mem = अणु
			.enabled = 0,
		पूर्ण,
		.valid_ops_mask = REGULATOR_CHANGE_VOLTAGE,
		.apply_uV = 1,
	पूर्ण,
	.num_consumer_supplies = ARRAY_SIZE(buck2_consumers),
	.consumer_supplies = buck2_consumers,
पूर्ण;

/* DA9030 */
काष्ठा da903x_subdev_info cm_x300_da9030_subdevs[] = अणु
	अणु
		.name = "da903x-battery",
		.id = DA9030_ID_BAT,
		.platक्रमm_data = &cm_x300_battery_info,
	पूर्ण,
	अणु
		.name = "da903x-regulator",
		.id = DA9030_ID_BUCK2,
		.platक्रमm_data = &buck2_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा da903x_platक्रमm_data cm_x300_da9030_info = अणु
	.num_subdevs = ARRAY_SIZE(cm_x300_da9030_subdevs),
	.subdevs = cm_x300_da9030_subdevs,
पूर्ण;

अटल काष्ठा i2c_board_info cm_x300_pmic_info = अणु
	I2C_BOARD_INFO("da9030", 0x49),
	.irq = IRQ_WAKEUP0,
	.platक्रमm_data = &cm_x300_da9030_info,
पूर्ण;

अटल काष्ठा i2c_pxa_platक्रमm_data cm_x300_pwr_i2c_info = अणु
	.use_pio = 1,
पूर्ण;

अटल व्योम __init cm_x300_init_da9030(व्योम)
अणु
	pxa3xx_set_i2c_घातer_info(&cm_x300_pwr_i2c_info);
	i2c_रेजिस्टर_board_info(1, &cm_x300_pmic_info, 1);
	irq_set_irq_wake(IRQ_WAKEUP0, 1);
पूर्ण

/* wi2wi gpio setting क्रम प्रणाली_rev >= 130 */
अटल काष्ठा gpio cm_x300_wi2wi_gpios[] __initdata = अणु
	अणु 71, GPIOF_OUT_INIT_HIGH, "wlan en" पूर्ण,
	अणु 70, GPIOF_OUT_INIT_HIGH, "bt reset" पूर्ण,
पूर्ण;

अटल व्योम __init cm_x300_init_wi2wi(व्योम)
अणु
	पूर्णांक err;

	अगर (प्रणाली_rev < 130) अणु
		cm_x300_wi2wi_gpios[0].gpio = 77;	/* wlan en */
		cm_x300_wi2wi_gpios[1].gpio = 78;	/* bt reset */
	पूर्ण

	/* Libertas and CSR reset */
	err = gpio_request_array(ARRAY_AND_SIZE(cm_x300_wi2wi_gpios));
	अगर (err) अणु
		pr_err("failed to request wifi/bt gpios: %d\n", err);
		वापस;
	पूर्ण

	udelay(10);
	gpio_set_value(cm_x300_wi2wi_gpios[1].gpio, 0);
	udelay(10);
	gpio_set_value(cm_x300_wi2wi_gpios[1].gpio, 1);

	gpio_मुक्त_array(ARRAY_AND_SIZE(cm_x300_wi2wi_gpios));
पूर्ण

/* MFP */
अटल व्योम __init cm_x300_init_mfp(व्योम)
अणु
	/* board-processor specअगरic GPIO initialization */
	pxa3xx_mfp_config(ARRAY_AND_SIZE(cm_x3xx_mfp_cfg));

	अगर (प्रणाली_rev < 130)
		pxa3xx_mfp_config(ARRAY_AND_SIZE(cm_x3xx_rev_lt130_mfp_cfg));
	अन्यथा
		pxa3xx_mfp_config(ARRAY_AND_SIZE(cm_x3xx_rev_ge130_mfp_cfg));

	अगर (cpu_is_pxa310())
		pxa3xx_mfp_config(ARRAY_AND_SIZE(cm_x310_mfp_cfg));
पूर्ण

अटल व्योम __init cm_x300_init(व्योम)
अणु
	cm_x300_init_mfp();

	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	अगर (cpu_is_pxa300())
		pxa_set_ffuart_info(शून्य);

	cm_x300_init_da9030();
	cm_x300_init_dm9000();
	cm_x300_init_lcd();
	cm_x300_init_u2d();
	cm_x300_init_ohci();
	cm_x300_init_mmc();
	cm_x300_init_nand();
	cm_x300_init_leds();
	cm_x300_init_i2c();
	cm_x300_init_spi();
	cm_x300_init_rtc();
	cm_x300_init_ac97();
	cm_x300_init_wi2wi();
	cm_x300_init_bl();

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

अटल व्योम __init cm_x300_fixup(काष्ठा tag *tags, अक्षर **cmdline)
अणु
	/* Make sure that mi->bank[0].start = PHYS_ADDR */
	क्रम (; tags->hdr.size; tags = tag_next(tags))
		अगर (tags->hdr.tag == ATAG_MEM &&
			tags->u.mem.start == 0x80000000) अणु
			tags->u.mem.start = 0xa0000000;
			अवरोध;
		पूर्ण
पूर्ण

MACHINE_START(CM_X300, "CM-X300 module")
	.atag_offset	= 0x100,
	.map_io		= pxa3xx_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa3xx_init_irq,
	.handle_irq	= pxa3xx_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= cm_x300_init,
	.fixup		= cm_x300_fixup,
	.restart	= pxa_restart,
MACHINE_END
