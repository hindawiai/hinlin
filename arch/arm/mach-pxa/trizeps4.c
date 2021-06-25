<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/trizeps4.c
 *
 *  Support क्रम the Keith und Koep Trizeps4 Module Platक्रमm.
 *
 *  Author:	Jथञrgen Schindele
 *  Created:	20 02, 2006
 *  Copyright:	Jथञrgen Schindele
 */

#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/leds.h>
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/bitops.h>
#समावेश <linux/fb.h>
#समावेश <linux/ioport.h>
#समावेश <linux/delay.h>
#समावेश <linux/gpपन.स>
#समावेश <linux/dm9000.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/regulator/machine.h>
#समावेश <linux/platक्रमm_data/i2c-pxa.h>

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>
#समावेश <linux/sizes.h>

#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/map.h>
#समावेश <यंत्र/mach/irq.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "pxa27x.h"
#समावेश <mach/trizeps4.h>
#समावेश <mach/audपन.स>
#समावेश <linux/platक्रमm_data/video-pxafb.h>
#समावेश <linux/platक्रमm_data/mmc-pxamci.h>
#समावेश <linux/platक्रमm_data/irda-pxaficp.h>
#समावेश <linux/platक्रमm_data/usb-ohci-pxa27x.h>
#समावेश <mach/smemc.h>

#समावेश "generic.h"
#समावेश "devices.h"

/*	comment out the following line अगर you want to use the
 *	Standard UART from PXA क्रम serial / irda transmission
 *	and acivate it अगर you have status leds connected */
#घोषणा STATUS_LEDS_ON_STUART_PINS 1

/*****************************************************************************
 * MultiFunctionPins of CPU
 *****************************************************************************/
अटल अचिन्हित दीर्घ trizeps4_pin_config[] __initdata = अणु
	/* Chip Selects */
	GPIO15_nCS_1,		/* DiskOnChip CS */
	GPIO93_GPIO,		/* TRIZEPS4_DOC_IRQ */
	GPIO94_GPIO,		/* DOC lock */

	GPIO78_nCS_2,		/* DM9000 CS */
	GPIO101_GPIO,		/* TRIZEPS4_ETH_IRQ */

	GPIO79_nCS_3,		/* Logic CS */
	GPIO0_GPIO | WAKEUP_ON_EDGE_RISE,	/* Logic irq */

	/* AC97 */
	GPIO28_AC97_BITCLK,
	GPIO29_AC97_SDATA_IN_0,
	GPIO30_AC97_SDATA_OUT,
	GPIO31_AC97_SYNC,

	/* LCD - 16bpp Active TFT */
	GPIOxx_LCD_TFT_16BPP,

	/* UART */
	GPIO9_FFUART_CTS,
	GPIO10_FFUART_DCD,
	GPIO16_FFUART_TXD,
	GPIO33_FFUART_DSR,
	GPIO38_FFUART_RI,
	GPIO82_FFUART_DTR,
	GPIO83_FFUART_RTS,
	GPIO96_FFUART_RXD,

	GPIO42_BTUART_RXD,
	GPIO43_BTUART_TXD,
	GPIO44_BTUART_CTS,
	GPIO45_BTUART_RTS,
#अगर_घोषित STATUS_LEDS_ON_STUART_PINS
	GPIO46_GPIO,
	GPIO47_GPIO,
#अन्यथा
	GPIO46_STUART_RXD,
	GPIO47_STUART_TXD,
#पूर्ण_अगर
	/* PCMCIA */
	GPIO11_GPIO,			/* TRIZEPS4_CD_IRQ */
	GPIO13_GPIO,			/* TRIZEPS4_READY_NINT */
	GPIO48_nPOE,
	GPIO49_nPWE,
	GPIO50_nPIOR,
	GPIO51_nPIOW,
	GPIO54_nPCE_2,
	GPIO55_nPREG,
	GPIO56_nPWAIT,
	GPIO57_nIOIS16,
	GPIO102_nPCE_1,
	GPIO104_PSKTSEL,

	/* MultiMediaCard */
	GPIO32_MMC_CLK,
	GPIO92_MMC_DAT_0,
	GPIO109_MMC_DAT_1,
	GPIO110_MMC_DAT_2,
	GPIO111_MMC_DAT_3,
	GPIO112_MMC_CMD,
	GPIO12_GPIO,			/* TRIZEPS4_MMC_IRQ */

	/* USB OHCI */
	GPIO88_USBH1_PWR,		/* USBHPWR1 */
	GPIO89_USBH1_PEN,		/* USBHPEN1 */

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,
पूर्ण;

अटल अचिन्हित दीर्घ trizeps4wl_pin_config[] __initdata = अणु
	/* SSP 2 */
	GPIO14_SSP2_SFRM,
	GPIO19_SSP2_SCLK,
	GPIO53_GPIO,			/* TRIZEPS4_SPI_IRQ */
	GPIO86_SSP2_RXD,
	GPIO87_SSP2_TXD,
पूर्ण;

/****************************************************************************
 * ONBOARD FLASH
 ****************************************************************************/
अटल काष्ठा mtd_partition trizeps4_partitions[] = अणु
	अणु
		.name =		"Bootloader",
		.offset =	0x00000000,
		.size =		0x00040000,
		.mask_flags =	MTD_WRITEABLE  /* क्रमce पढ़ो-only */
	पूर्ण, अणु
		.name =		"Backup",
		.offset =	0x00040000,
		.size =		0x00040000,
	पूर्ण, अणु
		.name =		"Image",
		.offset =	0x00080000,
		.size =		0x01080000,
	पूर्ण, अणु
		.name =		"IPSM",
		.offset =	0x01100000,
		.size =		0x00e00000,
	पूर्ण, अणु
		.name =		"Registry",
		.offset =	0x01f00000,
		.size =		MTDPART_SIZ_FULL,
	पूर्ण
पूर्ण;

अटल काष्ठा physmap_flash_data trizeps4_flash_data[] = अणु
	अणु
		.width		= 4,			/* bankwidth in bytes */
		.parts		= trizeps4_partitions,
		.nr_parts	= ARRAY_SIZE(trizeps4_partitions)
	पूर्ण
पूर्ण;

अटल काष्ठा resource flash_resource = अणु
	.start	= PXA_CS0_PHYS,
	.end	= PXA_CS0_PHYS + SZ_32M - 1,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device flash_device = अणु
	.name		= "physmap-flash",
	.id		= 0,
	.dev = अणु
		.platक्रमm_data = trizeps4_flash_data,
	पूर्ण,
	.resource = &flash_resource,
	.num_resources = 1,
पूर्ण;

/****************************************************************************
 * DAVICOM DM9000 Ethernet
 ****************************************************************************/
अटल काष्ठा resource dm9000_resources[] = अणु
	[0] = अणु
		.start	= TRIZEPS4_ETH_PHYS+0x300,
		.end	= TRIZEPS4_ETH_PHYS+0x400-1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= TRIZEPS4_ETH_PHYS+0x8300,
		.end	= TRIZEPS4_ETH_PHYS+0x8400-1,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.start	= TRIZEPS4_ETH_IRQ,
		.end	= TRIZEPS4_ETH_IRQ,
		.flags	= IORESOURCE_IRQ | IORESOURCE_IRQ_HIGHEDGE,
	पूर्ण,
पूर्ण;

अटल काष्ठा dm9000_plat_data tri_dm9000_platdata = अणु
	.flags		= DM9000_PLATF_32BITONLY,
पूर्ण;

अटल काष्ठा platक्रमm_device dm9000_device = अणु
	.name		= "dm9000",
	.id		= -1,
	.num_resources	= ARRAY_SIZE(dm9000_resources),
	.resource	= dm9000_resources,
	.dev		= अणु
		.platक्रमm_data = &tri_dm9000_platdata,
	पूर्ण
पूर्ण;

/****************************************************************************
 * LED's on GPIO pins of PXA
 ****************************************************************************/
अटल काष्ठा gpio_led trizeps4_led[] = अणु
#अगर_घोषित STATUS_LEDS_ON_STUART_PINS
	अणु
		.name = "led0:orange:heartbeat",	/* */
		.शेष_trigger = "heartbeat",
		.gpio = GPIO_HEARTBEAT_LED,
		.active_low = 1,
	पूर्ण,
	अणु
		.name = "led1:yellow:cpubusy",		/* */
		.शेष_trigger = "cpu-busy",
		.gpio = GPIO_SYS_BUSY_LED,
		.active_low = 1,
	पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data trizeps4_led_data = अणु
	.leds		= trizeps4_led,
	.num_leds	= ARRAY_SIZE(trizeps4_led),
पूर्ण;

अटल काष्ठा platक्रमm_device leds_devices = अणु
	.name		= "leds-gpio",
	.id		= -1,
	.dev		= अणु
		.platक्रमm_data	= &trizeps4_led_data,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *trizeps4_devices[] __initdata = अणु
	&flash_device,
	&dm9000_device,
	&leds_devices,
पूर्ण;

अटल काष्ठा platक्रमm_device *trizeps4wl_devices[] __initdata = अणु
	&flash_device,
	&leds_devices,
पूर्ण;

अटल लघु trizeps_conxs_bcr;

/* PCCARD घातer चयनing supports only 3,3V */
व्योम board_pcmcia_घातer(पूर्णांक घातer)
अणु
	अगर (घातer) अणु
		/* चयन घातer on, put in reset and enable buffers */
		trizeps_conxs_bcr |= घातer;
		trizeps_conxs_bcr |= ConXS_BCR_CF_RESET;
		trizeps_conxs_bcr &= ~ConXS_BCR_CF_BUF_EN;
		BCR_ग_लिखोw(trizeps_conxs_bcr);
		/* रुको a little */
		udelay(2000);
		/* take reset away */
		trizeps_conxs_bcr &= ~ConXS_BCR_CF_RESET;
		BCR_ग_लिखोw(trizeps_conxs_bcr);
		udelay(2000);
	पूर्ण अन्यथा अणु
		/* put in reset */
		trizeps_conxs_bcr |= ConXS_BCR_CF_RESET;
		BCR_ग_लिखोw(trizeps_conxs_bcr);
		udelay(1000);
		/* चयन घातer off */
		trizeps_conxs_bcr &= ~0xf;
		BCR_ग_लिखोw(trizeps_conxs_bcr);
	पूर्ण
	pr_debug("%s: o%s 0x%x\n", __func__, घातer ? "n" : "ff",
			trizeps_conxs_bcr);
पूर्ण
EXPORT_SYMBOL(board_pcmcia_घातer);

/* backlight घातer चयनing क्रम LCD panel */
अटल व्योम board_backlight_घातer(पूर्णांक on)
अणु
	अगर (on)
		trizeps_conxs_bcr |= ConXS_BCR_L_DISP;
	अन्यथा
		trizeps_conxs_bcr &= ~ConXS_BCR_L_DISP;

	pr_debug("%s: o%s 0x%x\n", __func__, on ? "n" : "ff",
			trizeps_conxs_bcr);
	BCR_ग_लिखोw(trizeps_conxs_bcr);
पूर्ण

/* a I2C based RTC is known on CONXS board */
अटल काष्ठा i2c_board_info trizeps4_i2c_devices[] __initdata = अणु
	अणु I2C_BOARD_INFO("rtc-pcf8593", 0x51) पूर्ण
पूर्ण;

/****************************************************************************
 * MMC card slot बाह्यal to module
 ****************************************************************************/
अटल पूर्णांक trizeps4_mci_init(काष्ठा device *dev, irq_handler_t mci_detect_पूर्णांक,
		व्योम *data)
अणु
	पूर्णांक err;

	err = request_irq(TRIZEPS4_MMC_IRQ, mci_detect_पूर्णांक,
			  IRQF_TRIGGER_RISING, "MMC card detect", data);
	अगर (err) अणु
		prपूर्णांकk(KERN_ERR "trizeps4_mci_init: MMC/SD: can't request"
						"MMC card detect IRQ\n");
		वापस -1;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम trizeps4_mci_निकास(काष्ठा device *dev, व्योम *data)
अणु
	मुक्त_irq(TRIZEPS4_MMC_IRQ, data);
पूर्ण

अटल काष्ठा pxamci_platक्रमm_data trizeps4_mci_platक्रमm_data = अणु
	.ocr_mask	= MMC_VDD_32_33|MMC_VDD_33_34,
	.detect_delay_ms= 10,
	.init 		= trizeps4_mci_init,
	.निकास		= trizeps4_mci_निकास,
	.get_ro		= शून्य,	/* ग_लिखो-protection not supported */
	.setघातer 	= शून्य,	/* घातer-चयनing not supported */
पूर्ण;

/****************************************************************************
 * IRDA mode चयनing on stuart
 ****************************************************************************/
#अगर_अघोषित STATUS_LEDS_ON_STUART_PINS
अटल लघु trizeps_conxs_ircr;

अटल पूर्णांक trizeps4_irda_startup(काष्ठा device *dev)
अणु
	trizeps_conxs_ircr &= ~ConXS_IRCR_SD;
	IRCR_ग_लिखोw(trizeps_conxs_ircr);
	वापस 0;
पूर्ण

अटल व्योम trizeps4_irda_shutकरोwn(काष्ठा device *dev)
अणु
	trizeps_conxs_ircr |= ConXS_IRCR_SD;
	IRCR_ग_लिखोw(trizeps_conxs_ircr);
पूर्ण

अटल व्योम trizeps4_irda_transceiver_mode(काष्ठा device *dev, पूर्णांक mode)
अणु
	अचिन्हित दीर्घ flags;

	local_irq_save(flags);
	/* Switch mode */
	अगर (mode & IR_SIRMODE)
		trizeps_conxs_ircr &= ~ConXS_IRCR_MODE;	/* Slow mode */
	अन्यथा अगर (mode & IR_FIRMODE)
		trizeps_conxs_ircr |= ConXS_IRCR_MODE;	/* Fast mode */

	/* Switch घातer */
	अगर (mode & IR_OFF)
		trizeps_conxs_ircr |= ConXS_IRCR_SD;
	अन्यथा
		trizeps_conxs_ircr &= ~ConXS_IRCR_SD;

	IRCR_ग_लिखोw(trizeps_conxs_ircr);
	local_irq_restore(flags);

	pxa2xx_transceiver_mode(dev, mode);
पूर्ण

अटल काष्ठा pxaficp_platक्रमm_data trizeps4_ficp_platक्रमm_data = अणु
	.gpio_pwकरोwn		= -1,
	.transceiver_cap	= IR_SIRMODE | IR_FIRMODE | IR_OFF,
	.transceiver_mode	= trizeps4_irda_transceiver_mode,
	.startup		= trizeps4_irda_startup,
	.shutकरोwn		= trizeps4_irda_shutकरोwn,
पूर्ण;
#पूर्ण_अगर

/****************************************************************************
 * OHCI USB port
 ****************************************************************************/
अटल काष्ठा pxaohci_platक्रमm_data trizeps4_ohci_platक्रमm_data = अणु
	.port_mode	= PMM_PERPORT_MODE,
	.flags		= ENABLE_PORT_ALL | POWER_CONTROL_LOW | POWER_SENSE_LOW,
पूर्ण;

अटल काष्ठा map_desc trizeps4_io_desc[] __initdata = अणु
	अणु 	/* ConXS CFSR */
		.भव	= TRIZEPS4_CFSR_VIRT,
		.pfn		= __phys_to_pfn(TRIZEPS4_CFSR_PHYS),
		.length		= 0x00001000,
		.type		= MT_DEVICE
	पूर्ण,
	अणु	/* ConXS BCR */
		.भव	= TRIZEPS4_BOCR_VIRT,
		.pfn		= __phys_to_pfn(TRIZEPS4_BOCR_PHYS),
		.length		= 0x00001000,
		.type		= MT_DEVICE
	पूर्ण,
	अणु 	/* ConXS IRCR */
		.भव	= TRIZEPS4_IRCR_VIRT,
		.pfn		= __phys_to_pfn(TRIZEPS4_IRCR_PHYS),
		.length		= 0x00001000,
		.type		= MT_DEVICE
	पूर्ण,
	अणु	/* ConXS DCR */
		.भव	= TRIZEPS4_DICR_VIRT,
		.pfn		= __phys_to_pfn(TRIZEPS4_DICR_PHYS),
		.length		= 0x00001000,
		.type		= MT_DEVICE
	पूर्ण,
	अणु	/* ConXS UPSR */
		.भव	= TRIZEPS4_UPSR_VIRT,
		.pfn		= __phys_to_pfn(TRIZEPS4_UPSR_PHYS),
		.length		= 0x00001000,
		.type		= MT_DEVICE
	पूर्ण
पूर्ण;

अटल काष्ठा pxafb_mode_info sharp_lcd_mode = अणु
	.pixघड़ी	= 78000,
	.xres		= 640,
	.yres		= 480,
	.bpp		= 8,
	.hsync_len	= 4,
	.left_margin	= 4,
	.right_margin	= 4,
	.vsync_len	= 2,
	.upper_margin	= 0,
	.lower_margin	= 0,
	.sync		= FB_SYNC_HOR_HIGH_ACT | FB_SYNC_VERT_HIGH_ACT,
	.cmap_greyscale	= 0,
पूर्ण;

अटल काष्ठा pxafb_mach_info sharp_lcd = अणु
	.modes		= &sharp_lcd_mode,
	.num_modes	= 1,
	.lcd_conn	= LCD_COLOR_DSTN_16BPP | LCD_PCLK_EDGE_FALL,
	.cmap_inverse	= 0,
	.cmap_अटल	= 0,
	.pxafb_backlight_घातer = board_backlight_घातer,
पूर्ण;

अटल काष्ठा pxafb_mode_info toshiba_lcd_mode = अणु
	.pixघड़ी	= 39720,
	.xres		= 640,
	.yres		= 480,
	.bpp		= 8,
	.hsync_len	= 63,
	.left_margin	= 12,
	.right_margin	= 12,
	.vsync_len	= 4,
	.upper_margin	= 32,
	.lower_margin	= 10,
	.sync		= 0,
	.cmap_greyscale	= 0,
पूर्ण;

अटल काष्ठा pxafb_mach_info toshiba_lcd = अणु
	.modes		= &toshiba_lcd_mode,
	.num_modes	= 1,
	.lcd_conn	= (LCD_COLOR_TFT_16BPP | LCD_PCLK_EDGE_FALL),
	.cmap_inverse	= 0,
	.cmap_अटल	= 0,
	.pxafb_backlight_घातer = board_backlight_घातer,
पूर्ण;

अटल व्योम __init trizeps4_init(व्योम)
अणु
	pxa2xx_mfp_config(ARRAY_AND_SIZE(trizeps4_pin_config));
	अगर (machine_is_trizeps4wl()) अणु
		pxa2xx_mfp_config(ARRAY_AND_SIZE(trizeps4wl_pin_config));
		platक्रमm_add_devices(trizeps4wl_devices,
					ARRAY_SIZE(trizeps4wl_devices));
	पूर्ण अन्यथा अणु
		platक्रमm_add_devices(trizeps4_devices,
					ARRAY_SIZE(trizeps4_devices));
	पूर्ण

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	अगर (0)	/* करोnt know how to determine LCD */
		pxa_set_fb_info(शून्य, &sharp_lcd);
	अन्यथा
		pxa_set_fb_info(शून्य, &toshiba_lcd);

	pxa_set_mci_info(&trizeps4_mci_platक्रमm_data);
#अगर_अघोषित STATUS_LEDS_ON_STUART_PINS
	pxa_set_ficp_info(&trizeps4_ficp_platक्रमm_data);
#पूर्ण_अगर
	pxa_set_ohci_info(&trizeps4_ohci_platक्रमm_data);
	pxa_set_ac97_info(शून्य);
	pxa_set_i2c_info(शून्य);
	i2c_रेजिस्टर_board_info(0, trizeps4_i2c_devices,
					ARRAY_SIZE(trizeps4_i2c_devices));

	/* this is the reset value */
	trizeps_conxs_bcr = 0x00A0;

	BCR_ग_लिखोw(trizeps_conxs_bcr);
	board_backlight_घातer(1);

	regulator_has_full_स्थिरraपूर्णांकs();
पूर्ण

अटल व्योम __init trizeps4_map_io(व्योम)
अणु
	pxa27x_map_io();
	iotable_init(trizeps4_io_desc, ARRAY_SIZE(trizeps4_io_desc));

	अगर ((__raw_पढ़ोl(MSC0) & 0x8) && (__raw_पढ़ोl(BOOT_DEF) & 0x1)) अणु
		/* अगर flash is 16 bit wide its a Trizeps4 WL */
		__machine_arch_type = MACH_TYPE_TRIZEPS4WL;
		trizeps4_flash_data[0].width = 2;
	पूर्ण अन्यथा अणु
		/* अगर flash is 32 bit wide its a Trizeps4 */
		__machine_arch_type = MACH_TYPE_TRIZEPS4;
		trizeps4_flash_data[0].width = 4;
	पूर्ण
पूर्ण

MACHINE_START(TRIZEPS4, "Keith und Koep Trizeps IV module")
	/* MAINTAINER("Jथञrgen Schindele") */
	.atag_offset	= 0x100,
	.init_machine	= trizeps4_init,
	.map_io		= trizeps4_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END

MACHINE_START(TRIZEPS4WL, "Keith und Koep Trizeps IV-WL module")
	/* MAINTAINER("Jथञrgen Schindele") */
	.atag_offset	= 0x100,
	.init_machine	= trizeps4_init,
	.map_io		= trizeps4_map_io,
	.nr_irqs	= PXA_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.restart	= pxa_restart,
MACHINE_END
