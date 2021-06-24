<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Hardware definitions क्रम Voipac PXA270
 *
 * Copyright (C) 2010
 * Marek Vasut <marek.vasut@gmail.com>
 */

#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/gpio_keys.h>
#समावेश <linux/input.h>
#समावेश <linux/leds.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/onenand.h>
#समावेश <linux/dm9000.h>
#समावेश <linux/ucb1400.h>
#समावेश <linux/ata_platक्रमm.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/regulator/max1586.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>

#समावेश "pxa27x.h"
#समावेश <mach/audपन.स>
#समावेश <mach/vpac270.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश "pxa27x-udc.h"
#समावेश "udc.h"
#समावेश <linux/platक्रमm_data/ata-pxa.h>

#समावेश "generic.h"
#समावेश "devices.h"

/******************************************************************************
 * Pin configuration
 ******************************************************************************/
अटल अचिन्हित दीर्घ vpac270_pin_config[] __initdata = अणु
	/* MMC */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO53_GPIO,	/* SD detect */
	GPIO52_GPIO,	/* SD r/o चयन */

	/* GPIO KEYS */
	GPIO1_GPIO,	/* USER BTN */

	/* LEDs */
	GPIO15_GPIO,	/* orange led */

	/* FFUART */
	GPIO34_FFUART_RXD,
	GPIO39_FFUART_TXD,
	GPIO27_FFUART_RTS,
	GPIO100_FFUART_CTS,
	GPIO33_FFUART_DSR,
	GPIO40_FFUART_DTR,
	GPIO10_FFUART_DCD,
	GPIO38_FFUART_RI,

	/* LCD */
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
	GPIO86_LCD_LDD_16,
	GPIO87_LCD_LDD_17,
	GPIO74_LCD_FCLK,
	GPIO75_LCD_LCLK,
	GPIO76_LCD_PCLK,
	GPIO77_LCD_BIAS,

	/* PCMCIA */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO85_nPCE_1,
	GPIO54_nPCE_2,
	GPIO55_nPREG,
	GPIO57_nIOIS16,
	GPIO56_nPWAIT,
	GPIO104_PSKTSEL,
	GPIO84_GPIO,	/* PCMCIA CD */
	GPIO35_GPIO,	/* PCMCIA RDY */
	GPIO107_GPIO,	/* PCMCIA PPEN */
	GPIO11_GPIO,	/* PCMCIA RESET */
	GPIO17_GPIO,	/* CF CD */
	GPIO12_GPIO,	/* CF RDY */
	GPIO16_GPIO,	/* CF RESET */

	/* UHC */
	GPIO88_USBH1_PWR,
	GPIO89_USBH1_PEN,
	GPIO119_USBH2_PWR,
	GPIO120_USBH2_PEN,

	/* UDC */
	GPIO41_GPIO,

	/* Ethernet */
	GPIO114_GPIO,	/* IRQ */

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,
	GPIO95_AC97_nRESET,
	GPIO98_AC97_SYSCLK,
	GPIO113_GPIO,	/* TS IRQ */

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* IDE */
	GPIO36_GPIO,	/* IDE IRQ */
	GPIO80_DREQ_1,
पूर्ण;

/******************************************************************************
 * NOR Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_PHYSMAP) || defined(CONFIG_MTD_PHYSMAP_MODULE)
अटल काष्ठा mtd_partition vpac270_nor_partitions[] = अणु
	अणु
		.name		= "Flash",
		.offset		= 0x00000000,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data vpac270_flash_data[] = अणु
	अणु
		.width		= 2,	/* bankwidth in bytes */
		.parts		= vpac270_nor_partitions,
		.nr_parts	= ARRAY_SIZE(vpac270_nor_partitions)
	पूर्ण
पूर्ण;

अटल काष्ठा resource vpac270_flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_64M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device vpac270_flash = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.resource	= &vpac270_flash_resource,
	.num_resources	= 1,
	.dev 		= अणु
		.platक्रमm_data = vpac270_flash_data,
	पूर्ण,
पूर्ण;
अटल व्योम __init vpac270_nor_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&vpac270_flash);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_nor_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Oneन_अंकD Flash
 ******************************************************************************/
#अगर defined(CONFIG_MTD_ONEन_अंकD) || defined(CONFIG_MTD_ONEन_अंकD_MODULE)
अटल काष्ठा mtd_partition vpac270_onenand_partitions[] = अणु
	अणु
		.name		= "Flash",
		.offset		= 0x00000000,
		.size		= MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा onenand_platक्रमm_data vpac270_onenand_info = अणु
	.parts		= vpac270_onenand_partitions,
	.nr_parts	= ARRAY_SIZE(vpac270_onenand_partitions),
पूर्ण;

अटल काष्ठा resource vpac270_onenand_resources[] = अणु
	[0] = अणु
		.start	= PXA_CS0_PHYS,
		.end	= PXA_CS0_PHYS + SZ_1M,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vpac270_onenand = अणु
	.name		= "onenand-flash",
	.id		= -1,
	.resource	= vpac270_onenand_resources,
	.num_resources	= ARRAY_SIZE(vpac270_onenand_resources),
	.dev		= अणु
		.platक्रमm_data	= &vpac270_onenand_info,
	पूर्ण,
पूर्ण;

अटल व्योम __init vpac270_onenand_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&vpac270_onenand);
पूर्ण
#अन्यथा
अटल व्योम __init vpac270_onenand_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * SD/MMC card controller
 ******************************************************************************/
#अगर defined(CONFIG_MMC_PXA) || defined(CONFIG_MMC_PXA_MODULE)
अटल काष्ठा pxamci_platक्रमm_data vpac270_mci_platक्रमm_data = अणु
	.ocr_mask		= MMC_VDD_32_33 | MMC_VDD_33_34,
	.detect_delay_ms	= 200,
पूर्ण;

अटल काष्ठा gpiod_lookup_table vpac270_mci_gpio_table = अणु
	.dev_id = "pxa2xx-mci.0",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO53_VPAC270_SD_DETECT_N,
			    "cd", GPIO_ACTIVE_LOW),
		GPIO_LOOKUP("gpio-pxa", GPIO52_VPAC270_SD_READONLY,
			    "wp", GPIO_ACTIVE_LOW),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल व्योम __init vpac270_mmc_init(व्योम)
अणु
	gpiod_add_lookup_table(&vpac270_mci_gpio_table);
	pxa_set_mci_info(&vpac270_mci_platक्रमm_data);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_mmc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * GPIO keys
 ******************************************************************************/
#अगर defined(CONFIG_KEYBOARD_GPIO) || defined(CONFIG_KEYBOARD_GPIO_MODULE)
अटल काष्ठा gpio_keys_button vpac270_pxa_buttons[] = अणु
	अणुKEY_POWER, GPIO1_VPAC270_USER_BTN, 0, "USER BTN"पूर्ण,
पूर्ण;

अटल काष्ठा gpio_keys_platक्रमm_data vpac270_pxa_keys_data = अणु
	.buttons	= vpac270_pxa_buttons,
	.nbuttons	= ARRAY_SIZE(vpac270_pxa_buttons),
पूर्ण;

अटल काष्ठा platक्रमm_device vpac270_pxa_keys = अणु
	.name	= "gpio-keys",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data = &vpac270_pxa_keys_data,
	पूर्ण,
पूर्ण;

अटल व्योम __init vpac270_keys_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&vpac270_pxa_keys);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_keys_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * LED
 ******************************************************************************/
#अगर defined(CONFIG_LEDS_GPIO) || defined(CONFIG_LEDS_GPIO_MODULE)
काष्ठा gpio_led vpac270_gpio_leds[] = अणु
अणु
	.name			= "vpac270:orange:user",
	.शेष_trigger	= "none",
	.gpio			= GPIO15_VPAC270_LED_ORANGE,
	.active_low		= 1,
पूर्ण
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data vpac270_gpio_led_info = अणु
	.leds		= vpac270_gpio_leds,
	.num_leds	= ARRAY_SIZE(vpac270_gpio_leds),
पूर्ण;

अटल काष्ठा platक्रमm_device vpac270_leds = अणु
	.name	= "leds-gpio",
	.id	= -1,
	.dev	= अणु
		.platक्रमm_data	= &vpac270_gpio_led_info,
	पूर्ण
पूर्ण;

अटल व्योम __init vpac270_leds_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&vpac270_leds);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_leds_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB Host
 ******************************************************************************/
#अगर defined(CONFIG_USB_OHCI_HCD) || defined(CONFIG_USB_OHCI_HCD_MODULE)
अटल पूर्णांक vpac270_ohci_init(काष्ठा device *dev)
अणु
	UP2OCR = UP2OCR_HXS | UP2OCR_HXOE | UP2OCR_DPPDE | UP2OCR_DMPDE;
	वापस 0;
पूर्ण

अटल काष्ठा pxaohci_platक्रमm_data vpac270_ohci_info = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT1 | ENABLE_PORT2 |
			POWER_CONTROL_LOW | POWER_SENSE_LOW,
	.init		= vpac270_ohci_init,
पूर्ण;

अटल व्योम __init vpac270_uhc_init(व्योम)
अणु
	pxa_set_ohci_info(&vpac270_ohci_info);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_uhc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * USB Gadget
 ******************************************************************************/
#अगर defined(CONFIG_USB_PXA27X)||defined(CONFIG_USB_PXA27X_MODULE)
अटल काष्ठा gpiod_lookup_table vpac270_gpio_vbus_gpiod_table = अणु
	.dev_id = "gpio-vbus",
	.table = अणु
		GPIO_LOOKUP("gpio-pxa", GPIO41_VPAC270_UDC_DETECT,
			    "vbus", GPIO_ACTIVE_HIGH),
		अणु पूर्ण,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vpac270_gpio_vbus = अणु
	.name	= "gpio-vbus",
	.id	= -1,
पूर्ण;

अटल व्योम vpac270_udc_command(पूर्णांक cmd)
अणु
	अगर (cmd == PXA2XX_UDC_CMD_CONNECT)
		UP2OCR = UP2OCR_HXOE | UP2OCR_DPPUE;
	अन्यथा अगर (cmd == PXA2XX_UDC_CMD_DISCONNECT)
		UP2OCR = UP2OCR_HXOE;
पूर्ण

अटल काष्ठा pxa2xx_udc_mach_info vpac270_udc_info __initdata = अणु
	.udc_command		= vpac270_udc_command,
	.gpio_pullup		= -1,
पूर्ण;

अटल व्योम __init vpac270_udc_init(व्योम)
अणु
	pxa_set_udc_info(&vpac270_udc_info);
	gpiod_add_lookup_table(&vpac270_gpio_vbus_gpiod_table);
	platक्रमm_device_रेजिस्टर(&vpac270_gpio_vbus);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_udc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Ethernet
 ******************************************************************************/
#अगर defined(CONFIG_DM9000) || defined(CONFIG_DM9000_MODULE)
अटल काष्ठा resource vpac270_dm9000_resources[] = अणु
	[0] = अणु
		.start	= PXA_CS2_PHYS + 0x300,
		.end	= PXA_CS2_PHYS + 0x303,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PXA_CS2_PHYS + 0x304,
		.end	= PXA_CS2_PHYS + 0x343,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start	= PXA_GPIO_TO_IRQ(GPIO114_VPAC270_ETH_IRQ),
		.end	= PXA_GPIO_TO_IRQ(GPIO114_VPAC270_ETH_IRQ),
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा dm9000_plat_data vpac270_dm9000_platdata = अणु
	.flags		= DM9000_PLATF_32BITONLY,
पूर्ण;

अटल काष्ठा platक्रमm_device vpac270_dm9000_device = अणु
	.name		= "dm9000",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(vpac270_dm9000_resources),
	.resource	= vpac270_dm9000_resources,
	.dev		= अणु
		.platक्रमm_data = &vpac270_dm9000_platdata,
	पूर्ण
पूर्ण;

अटल व्योम __init vpac270_eth_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&vpac270_dm9000_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_eth_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Audio and Touchscreen
 ******************************************************************************/
#अगर	defined(CONFIG_TOUCHSCREEN_UCB1400) || \
	defined(CONFIG_TOUCHSCREEN_UCB1400_MODULE)
अटल pxa2xx_audio_ops_t vpac270_ac97_pdata = अणु
	.reset_gpio	= 95,
पूर्ण;

अटल काष्ठा ucb1400_pdata vpac270_ucb1400_pdata = अणु
	.irq		= PXA_GPIO_TO_IRQ(GPIO113_VPAC270_TS_IRQ),
पूर्ण;

अटल काष्ठा platक्रमm_device vpac270_ucb1400_device = अणु
	.name		= "ucb1400_core",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data = &vpac270_ucb1400_pdata,
	पूर्ण,
पूर्ण;

अटल व्योम __init vpac270_ts_init(व्योम)
अणु
	pxa_set_ac97_info(&vpac270_ac97_pdata);
	platक्रमm_device_रेजिस्टर(&vpac270_ucb1400_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_ts_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * RTC
 ******************************************************************************/
#अगर defined(CONFIG_RTC_DRV_DS1307) || defined(CONFIG_RTC_DRV_DS1307_MODULE)
अटल काष्ठा i2c_board_info __initdata vpac270_i2c_devs[] = अणु
	अणु
		I2C_BOARD_INFO("ds1339", 0x68),
	पूर्ण,
पूर्ण;

अटल व्योम __init vpac270_rtc_init(व्योम)
अणु
	i2c_रेजिस्टर_board_info(0, ARRAY_AND_SIZE(vpac270_i2c_devs));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_rtc_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Framebuffer
 ******************************************************************************/
#अगर defined(CONFIG_FB_PXA) || defined(CONFIG_FB_PXA_MODULE)
अटल काष्ठा pxafb_mode_info vpac270_lcd_modes[] = अणु
अणु
	.pixघड़ी	= 57692,
	.xres		= 640,
	.yres		= 480,
	.bpp		= 32,
	.depth		= 18,

	.left_margin	= 144,
	.right_margin	= 32,
	.upper_margin	= 13,
	.lower_margin	= 30,

	.hsync_len	= 32,
	.vsync_len	= 2,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण, अणु	/* CRT 640x480 */
	.pixघड़ी	= 35000,
	.xres		= 640,
	.yres		= 480,
	.bpp		= 16,
	.depth		= 16,

	.left_margin	= 96,
	.right_margin	= 48,
	.upper_margin	= 33,
	.lower_margin	= 10,

	.hsync_len	= 48,
	.vsync_len	= 1,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण, अणु	/* CRT 800x600 H=30kHz V=48HZ */
	.pixघड़ी	= 25000,
	.xres		= 800,
	.yres		= 600,
	.bpp		= 16,
	.depth		= 16,

	.left_margin	= 50,
	.right_margin	= 1,
	.upper_margin	= 21,
	.lower_margin	= 12,

	.hsync_len	= 8,
	.vsync_len	= 1,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण, अणु	/* CRT 1024x768 H=40kHz V=50Hz */
	.pixघड़ी	= 15000,
	.xres		= 1024,
	.yres		= 768,
	.bpp		= 16,
	.depth		= 16,

	.left_margin	= 220,
	.right_margin	= 8,
	.upper_margin	= 33,
	.lower_margin	= 2,

	.hsync_len	= 48,
	.vsync_len	= 1,

	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
पूर्ण
पूर्ण;

अटल काष्ठा pxafb_mach_info vpac270_lcd_screen = अणु
	.modes		= vpac270_lcd_modes,
	.num_modes	= ARRAY_SIZE(vpac270_lcd_modes),
	.lcd_conn	= LCD_COLOR_TFT_18BPP,
पूर्ण;

अटल व्योम vpac270_lcd_घातer(पूर्णांक on, काष्ठा fb_var_screeninfo *info)
अणु
	gpio_set_value(GPIO81_VPAC270_BKL_ON, on);
पूर्ण

अटल व्योम __init vpac270_lcd_init(व्योम)
अणु
	पूर्णांक ret;

	ret = gpio_request(GPIO81_VPAC270_BKL_ON, "BKL-ON");
	अगर (ret) अणु
		pr_err("Requesting BKL-ON GPIO failed!\n");
		जाओ err;
	पूर्ण

	ret = gpio_direction_output(GPIO81_VPAC270_BKL_ON, 1);
	अगर (ret) अणु
		pr_err("Setting BKL-ON GPIO direction failed!\n");
		जाओ err2;
	पूर्ण

	vpac270_lcd_screen.pxafb_lcd_घातer = vpac270_lcd_घातer;
	pxa_set_fb_info(शून्य, &vpac270_lcd_screen);
	वापस;

err2:
	gpio_मुक्त(GPIO81_VPAC270_BKL_ON);
err:
	वापस;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_lcd_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * PATA IDE
 ******************************************************************************/
#अगर defined(CONFIG_PATA_PXA) || defined(CONFIG_PATA_PXA_MODULE)
अटल काष्ठा pata_pxa_pdata vpac270_pata_pdata = अणु
	.reg_shअगरt	= 1,
	.dma_dreq	= 1,
	.irq_flags	= IRQF_TRIGGER_RISING,
पूर्ण;

अटल काष्ठा resource vpac270_ide_resources[] = अणु
	[0] = अणु	/* I/O Base address */
	       .start	= PXA_CS3_PHYS + 0x120,
	       .end	= PXA_CS3_PHYS + 0x13f,
	       .flags	= IORESOURCE_MEM
	पूर्ण,
	[1] = अणु	/* CTL Base address */
	       .start	= PXA_CS3_PHYS + 0x15c,
	       .end	= PXA_CS3_PHYS + 0x15f,
	       .flags	= IORESOURCE_MEM
	पूर्ण,
	[2] = अणु	/* DMA Base address */
	       .start	= PXA_CS3_PHYS + 0x20,
	       .end	= PXA_CS3_PHYS + 0x2f,
	       .flags	= IORESOURCE_DMA
	पूर्ण,
	[3] = अणु	/* IDE IRQ pin */
	       .start	= PXA_GPIO_TO_IRQ(GPIO36_VPAC270_IDE_IRQ),
	       .end	= PXA_GPIO_TO_IRQ(GPIO36_VPAC270_IDE_IRQ),
	       .flags	= IORESOURCE_IRQ
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device vpac270_ide_device = अणु
	.name		= "pata_pxa",
	.num_resources	= ARRAY_SIZE(vpac270_ide_resources),
	.resource	= vpac270_ide_resources,
	.dev		= अणु
		.platक्रमm_data	= &vpac270_pata_pdata,
		.coherent_dma_mask	= 0xffffffff,
	पूर्ण
पूर्ण;

अटल व्योम __init vpac270_ide_init(व्योम)
अणु
	platक्रमm_device_रेजिस्टर(&vpac270_ide_device);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_ide_init(व्योम) अणुपूर्ण
#पूर्ण_अगर

/******************************************************************************
 * Core घातer regulator
 ******************************************************************************/
#अगर defined(CONFIG_REGULATOR_MAX1586) || \
    defined(CONFIG_REGULATOR_MAX1586_MODULE)
अटल काष्ठा regulator_consumer_supply vpac270_max1587a_consumers[] = अणु
	REGULATOR_SUPPLY("vcc_core", शून्य),
पूर्ण;

अटल काष्ठा regulator_init_data vpac270_max1587a_v3_info = अणु
	.स्थिरraपूर्णांकs = अणु
		.name		= "vcc_core range",
		.min_uV		= 900000,
		.max_uV		= 1705000,
		.always_on	= 1,
		.valid_ops_mask	= REGULATOR_CHANGE_VOLTAGE,
	पूर्ण,
	.consumer_supplies	= vpac270_max1587a_consumers,
	.num_consumer_supplies	= ARRAY_SIZE(vpac270_max1587a_consumers),
पूर्ण;

अटल काष्ठा max1586_subdev_data vpac270_max1587a_subdevs[] = अणु
	अणु
		.name		= "vcc_core",
		.id		= MAX1586_V3,
		.platक्रमm_data	= &vpac270_max1587a_v3_info,
	पूर्ण
पूर्ण;

अटल काष्ठा max1586_platक्रमm_data vpac270_max1587a_info = अणु
	.subdevs     = vpac270_max1587a_subdevs,
	.num_subdevs = ARRAY_SIZE(vpac270_max1587a_subdevs),
	.v3_gain     = MAX1586_GAIN_R24_3k32, /* 730..1550 mV */
पूर्ण;

अटल काष्ठा i2c_board_info __initdata vpac270_pi2c_board_info[] = अणु
	अणु
		I2C_BOARD_INFO("max1586", 0x14),
		.platक्रमm_data	= &vpac270_max1587a_info,
	पूर्ण,
पूर्ण;

अटल व्योम __init vpac270_pmic_init(व्योम)
अणु
	i2c_रेजिस्टर_board_info(1, ARRAY_AND_SIZE(vpac270_pi2c_board_info));
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम vpac270_pmic_init(व्योम) अणुपूर्ण
#पूर्ण_अगर


/******************************************************************************
 * Machine init
 ******************************************************************************/
अटल व्योम __init vpac270_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(vpac270_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);
	pxa_set_i2c_info(शून्य);
	pxa27x_set_i2c_घातer_info(शून्य);

	vpac270_pmic_init();
	vpac270_lcd_init();
	vpac270_mmc_init();
	vpac270_nor_init();
	vpac270_onenand_init();
	vpac270_leds_init();
	vpac270_keys_init();
	vpac270_uhc_init();
	vpac270_udc_init();
	vpac270_eth_init();
	vpac270_ts_init();
	vpac270_rtc_init();
	vpac270_ide_init();

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

MACHINE_START(VPAC270, "Voipac PXA270")
	.atag_offset	= 0x100,
	.map_io		= pxa27x_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= vpac270_init,
	.restart	= pxa_restart,
MACHINE_END
