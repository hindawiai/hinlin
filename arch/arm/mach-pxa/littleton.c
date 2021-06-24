<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/littleton.c
 *
 *  Support क्रम the Marvell Littleton Development Platक्रमm.
 *
 *  Author:	Jason Chagas (largely modअगरied code)
 *  Created:	Nov 20, 2006
 *  Copyright:	(C) Copyright 2006 Marvell International Ltd.
 *
 *  2007-11-22  modअगरied to align with latest kernel
 *              eric miao <eric.miao@marvell.com>
 */

#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/delay.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/clk.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/smc91x.h>
#समावेश <linux/i2c.h>
#समावेश <linux/leds.h>
#समावेश <linux/mfd/da903x.h>
#समावेश <linux/platक्रमm_data/max732x.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>

#समावेश "pxa300.h"
#समावेश "devices.h"
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/keypad-pxa27x.h>
#समावेश "littleton.h"
#समावेश <linux/platक्रमm_data/mtd-nand-pxa3xx.h>

#समावेश "generic.h"

/* Littleton MFP configurations */
अटल mfp_cfg_t littleton_mfp_cfg[] __initdata = अणु
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
	GPIO70_LCD_LDD_16,
	GPIO71_LCD_LDD_17,
	GPIO72_LCD_FCLK,
	GPIO73_LCD_LCLK,
	GPIO74_LCD_PCLK,
	GPIO75_LCD_BIAS,

	/* SSP2 */
	GPIO25_SSP2_SCLK,
	GPIO27_SSP2_TXD,
	GPIO17_GPIO,	/* SFRM as chip-select */

	/* Debug Ethernet */
	GPIO90_GPIO,

	/* Keypad */
	GPIO107_KP_DKIN_0,
	GPIO108_KP_DKIN_1,
	GPIO115_KP_MKIN_0,
	GPIO116_KP_MKIN_1,
	GPIO117_KP_MKIN_2,
	GPIO118_KP_MKIN_3,
	GPIO119_KP_MKIN_4,
	GPIO120_KP_MKIN_5,
	GPIO121_KP_MKOUT_0,
	GPIO122_KP_MKOUT_1,
	GPIO123_KP_MKOUT_2,
	GPIO124_KP_MKOUT_3,
	GPIO125_KP_MKOUT_4,

	/* MMC1 */
	GPIO3_MMC1_DAT0,
	GPIO4_MMC1_DAT1,
	GPIO5_MMC1_DAT2,
	GPIO6_MMC1_DAT3,
	GPIO7_MMC1_CLK,
	GPIO8_MMC1_CMD,
	GPIO15_GPIO, /* card detect */

	/* UART3 */
	GPIO107_UART3_CTS,
	GPIO108_UART3_RTS,
	GPIO109_UART3_TXD,
	GPIO110_UART3_RXD,
पूर्ण;

अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= (LITTLETON_ETH_PHYS + 0x300),
		.end	= (LITTLETON_ETH_PHYS + 0xfffff),
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO90)),
		.end	= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO90)),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_LOWEDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा smc91x_platdata littleton_smc91x_info = अणु
	.flags	= SMC91X_USE_8BIT | SMC91X_USE_16BIT |
		  SMC91X_NOWAIT | SMC91X_USE_DMA,
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
	.dev		= अणु
		.platक्रमm_data = &littleton_smc91x_info,
	पूर्ण,
पूर्ण;

#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pxafb_mode_info tpo_tकरो24mtea1_modes[] = अणु
	[0] = अणु
		/* VGA */
		.pixघड़ी	= 38250,
		.xres		= 480,
		.yres		= 640,
		.bpp		= 16,
		.hsync_len	= 8,
		.left_margin	= 8,
		.right_margin	= 24,
		.vsync_len	= 2,
		.upper_margin	= 2,
		.lower_margin	= 4,
		.sync		= 0,
	पूर्ण,
	[1] = अणु
		/* QVGA */
		.pixघड़ी	= 153000,
		.xres		= 240,
		.yres		= 320,
		.bpp		= 16,
		.hsync_len	= 8,
		.left_margin	= 8,
		.right_margin	= 88,
		.vsync_len	= 2,
		.upper_margin	= 2,
		.lower_margin	= 2,
		.sync		= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा pxafb_mach_info littleton_lcd_info = अणु
	.modes			= tpo_tकरो24mtea1_modes,
	.num_modes		= 2,
	.lcd_conn		= LCD_COLOR_TFT_16BPP,
पूर्ण;

अटल व्योम __init littleton_init_lcd(व्योम)
अणु
	pxa_set_fb_info(शून्य, &littleton_lcd_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम littleton_init_lcd(व्योम) अणुपूर्ण;
#पूर्ण_अगर /* CONFIG_FB_PXA || CONFIG_FB_PXA_MODULE */

#अगर defined(CONFIG_SPI_PXA2XX) || defined(CONFIG_SPI_PXA2XX_MODULE)
अटल काष्ठा pxa2xx_spi_controller littleton_spi_info = अणु
	.num_chipselect		= 1,
पूर्ण;

अटल काष्ठा pxa2xx_spi_chip littleton_tकरो24m_chip = अणु
	.rx_threshold	= 1,
	.tx_threshold	= 1,
	.gpio_cs	= LITTLETON_GPIO_LCD_CS,
पूर्ण;

अटल काष्ठा spi_board_info littleton_spi_devices[] __initdata = अणु
	अणु
		.modalias	= "tdo24m",
		.max_speed_hz	= 1000000,
		.bus_num	= 2,
		.chip_select	= 0,
		.controller_data= &littleton_tकरो24m_chip,
	पूर्ण,
पूर्ण;

अटल व्योम __init littleton_init_spi(व्योम)
अणु
	pxa2xx_set_spi_info(2, &littleton_spi_info);
	spi_रेजिस्टर_board_info(ARRAY_AND_SIZE(littleton_spi_devices));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम littleton_init_spi(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_KEYBOARD_PXA27x) || defined(CONFIG_KEYBOARD_PXA27x_MODULE)
अटल स्थिर अचिन्हित पूर्णांक littleton_matrix_key_map[] = अणु
	/* KEY(row, col, key_code) */
	KEY(1, 3, KEY_0), KEY(0, 0, KEY_1), KEY(1, 0, KEY_2), KEY(2, 0, KEY_3),
	KEY(0, 1, KEY_4), KEY(1, 1, KEY_5), KEY(2, 1, KEY_6), KEY(0, 2, KEY_7),
	KEY(1, 2, KEY_8), KEY(2, 2, KEY_9),

	KEY(0, 3, KEY_KPASTERISK), 	/* * */
	KEY(2, 3, KEY_KPDOT), 		/* # */

	KEY(5, 4, KEY_ENTER),

	KEY(5, 0, KEY_UP),
	KEY(5, 1, KEY_DOWN),
	KEY(5, 2, KEY_LEFT),
	KEY(5, 3, KEY_RIGHT),
	KEY(3, 2, KEY_HOME),
	KEY(4, 1, KEY_END),
	KEY(3, 3, KEY_BACK),

	KEY(4, 0, KEY_SEND),
	KEY(4, 2, KEY_VOLUMEUP),
	KEY(4, 3, KEY_VOLUMEDOWN),

	KEY(3, 0, KEY_F22),	/* soft1 */
	KEY(3, 1, KEY_F23),	/* soft2 */
पूर्ण;

अटल काष्ठा matrix_keymap_data littleton_matrix_keymap_data = अणु
	.keymap			= littleton_matrix_key_map,
	.keymap_size		= ARRAY_SIZE(littleton_matrix_key_map),
पूर्ण;

अटल काष्ठा pxa27x_keypad_platक्रमm_data littleton_keypad_info = अणु
	.matrix_key_rows	= 6,
	.matrix_key_cols	= 5,
	.matrix_keymap_data	= &littleton_matrix_keymap_data,

	.enable_rotary0		= 1,
	.rotary0_up_key		= KEY_UP,
	.rotary0_करोwn_key	= KEY_DOWN,

	.debounce_पूर्णांकerval	= 30,
पूर्ण;
अटल व्योम __init littleton_init_keypad(व्योम)
अणु
	pxa_set_keypad_info(&littleton_keypad_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम littleton_init_keypad(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
अटल काष्ठा pxamci_platक्रमm_data littleton_mci_platक्रमm_data = अणु
	.detect_delay_ms	= 200,
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
पूर्ण;

अटल काष्ठा gpiod_lookup_table littleton_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		/* Card detect on MFP (gpio-pxa) GPIO 15 */
		GPIO_LOOKUP("gpio-pxa", MFP_PIN_GPIO15,
			    "cd", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init littleton_init_mmc(व्योम)
अणु
	gpiod_add_lookup_table(&littleton_mci_gpio_table);
	pxa_set_mci_info(&littleton_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम littleton_init_mmc(व्योम) अणुपूर्ण
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL)
अटल काष्ठा mtd_partition littleton_nand_partitions[] = अणु
	[0] = अणु
		.name        = "Bootloader",
		.offset      = 0,
		.size        = 0x060000,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	[1] = अणु
		.name        = "Kernel",
		.offset      = 0x060000,
		.size        = 0x200000,
		.mask_flags  = MTD_WRITEABLE, /* क्रमce पढ़ो-only */
	पूर्ण,
	[2] = अणु
		.name        = "Filesystem",
		.offset      = 0x0260000,
		.size        = 0x3000000,     /* 48M - rootfs */
	पूर्ण,
	[3] = अणु
		.name        = "MassStorage",
		.offset      = 0x3260000,
		.size        = 0x3d40000,
	पूर्ण,
	[4] = अणु
		.name        = "BBT",
		.offset      = 0x6FA0000,
		.size        = 0x80000,
		.mask_flags  = MTD_WRITEABLE,  /* क्रमce पढ़ो-only */
	पूर्ण,
	/* NOTE: we reserve some blocks at the end of the न_अंकD flash क्रम
	 * bad block management, and the max number of relocation blocks
	 * dअगरfers on dअगरferent platक्रमms. Please take care with it when
	 * defining the partition table.
	 */
पूर्ण;

अटल काष्ठा pxa3xx_nand_platक्रमm_data littleton_nand_info = अणु
	.parts		= littleton_nand_partitions,
	.nr_parts	= ARRAY_SIZE(littleton_nand_partitions),
पूर्ण;

अटल व्योम __init littleton_init_nand(व्योम)
अणु
	pxa3xx_set_nand_info(&littleton_nand_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम littleton_init_nand(व्योम) अणुपूर्ण
#पूर्ण_अगर /* IS_ENABLED(CONFIG_MTD_न_अंकD_MARVELL) */

#अगर defined(CONFIG_I2C_PXA) || defined(CONFIG_I2C_PXA_MODULE)
अटल काष्ठा led_info littleton_da9034_leds[] = अणु
	[0] = अणु
		.name	= "littleton:keypad1",
		.flags	= DA9034_LED_RAMP,
	पूर्ण,
	[1] = अणु
		.name	= "littleton:keypad2",
		.flags	= DA9034_LED_RAMP,
	पूर्ण,
	[2] = अणु
		.name	= "littleton:vibra",
		.flags	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा da9034_touch_pdata littleton_da9034_touch = अणु
	.x_inverted     = 1,
	.पूर्णांकerval_ms    = 20,
पूर्ण;

अटल काष्ठा da903x_subdev_info littleton_da9034_subdevs[] = अणु
	अणु
		.name		= "da903x-led",
		.id		= DA9034_ID_LED_1,
		.platक्रमm_data	= &littleton_da9034_leds[0],
	पूर्ण, अणु
		.name		= "da903x-led",
		.id		= DA9034_ID_LED_2,
		.platक्रमm_data	= &littleton_da9034_leds[1],
	पूर्ण, अणु
		.name		= "da903x-led",
		.id		= DA9034_ID_VIBRA,
		.platक्रमm_data	= &littleton_da9034_leds[2],
	पूर्ण, अणु
		.name		= "da903x-backlight",
		.id		= DA9034_ID_WLED,
	पूर्ण, अणु
		.name		= "da9034-touch",
		.id		= DA9034_ID_TOUCH,
		.platक्रमm_data	= &littleton_da9034_touch,
	पूर्ण,
पूर्ण;

अटल काष्ठा da903x_platक्रमm_data littleton_da9034_info = अणु
	.num_subdevs	= ARRAY_SIZE(littleton_da9034_subdevs),
	.subdevs	= littleton_da9034_subdevs,
पूर्ण;

अटल काष्ठा max732x_platक्रमm_data littleton_max7320_info = अणु
	.gpio_base	= EXT0_GPIO_BASE,
पूर्ण;

अटल काष्ठा i2c_board_info littleton_i2c_info[] = अणु
	[0] = अणु
		.type		= "da9034",
		.addr		= 0x34,
		.platक्रमm_data	= &littleton_da9034_info,
		.irq		= PXA_GPIO_TO_IRQ(mfp_to_gpio(MFP_PIN_GPIO18)),
	पूर्ण,
	[1] = अणु
		.type		= "max7320",
		.addr		= 0x50,
		.platक्रमm_data	= &littleton_max7320_info,
	पूर्ण,
पूर्ण;

अटल व्योम __init littleton_init_i2c(व्योम)
अणु
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(littleton_i2c_info));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम littleton_init_i2c(व्योम) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_I2C_PXA || CONFIG_I2C_PXA_MODULE */

अटल व्योम __init littleton_init(व्योम)
अणु
	/* initialize MFP configurations */
	pxa3xx_mfp_config(ARRAY_AND_SIZE(littleton_mfp_cfg));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	/*
	 * Note: we depend bootloader set the correct
	 * value to MSC रेजिस्टर क्रम SMC91x.
	 */
	platक्रमm_device_रेजिस्टर(&smc91x_device);

	littleton_init_spi();
	littleton_init_i2c();
	littleton_init_mmc();
	littleton_init_lcd();
	littleton_init_keypad();
	littleton_init_nand();
पूर्ण

MACHINE_START(LITTLETON, "Marvell Form Factor Development Platform (aka Littleton)")
	.atag_offset	= 0x100,
	.map_io		= pxa3xx_map_io,
	.nr_irqs	= LITTLETON_NR_IRQS,
	.init_irq	= pxa3xx_init_irq,
	.handle_irq	= pxa3xx_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= littleton_init,
	.restart	= pxa_restart,
MACHINE_END
