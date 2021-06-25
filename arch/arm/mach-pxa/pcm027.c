<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *  linux/arch/arm/mach-pxa/pcm027.c
 *  Support क्रम the Phytec phyCORE-PXA270 CPU card (aka PCM-027).
 *
 *  Refer
 *   http://www.phytec.com/products/sbc/ARM-XScale/phyCORE-XScale-PXA270.hपंचांगl
 *  क्रम additional hardware info
 *
 *  Author:	Juergen Kilb
 *  Created:	April 05, 2005
 *  Copyright:	Phytec Messtechnik GmbH
 *  e-Mail:	armlinux@phytec.de
 *
 *  based on Intel Mainstone Board
 *
 *  Copyright 2007 Juergen Beisert @ Pengutronix (j.beisert@pengutronix.de)
 */

#समावेश <linux/irq.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/mtd/physmap.h>
#समावेश <linux/spi/spi.h>
#समावेश <linux/spi/max7301.h>
#समावेश <linux/spi/pxa2xx_spi.h>
#समावेश <linux/leds.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश "pxa27x.h"
#समावेश "pcm027.h"
#समावेश "generic.h"

/*
 * ABSTRACT:
 *
 * The PXA270 processor comes with a bunch of hardware on its silicon.
 * Not all of this hardware can be used at the same समय and not all
 * is routed to module's connectors. Also it depends on the baseboard, what
 * kind of hardware can be used in which way.
 * -> So this file supports the मुख्य devices on the CPU card only!
 * Refer pcm990-baseboard.c how to extend this features to get a full
 * blown प्रणाली with many common पूर्णांकerfaces.
 *
 * The PCM-027 supports the following पूर्णांकerfaces through its connectors and
 * will be used in pcm990-baseboard.c:
 *
 * - LCD support
 * - MMC support
 * - IDE/CF card
 * - FFUART
 * - BTUART
 * - IRUART
 * - AC97
 * - SSP
 * - SSP3
 *
 * Claimed GPIOs:
 * GPIO0 -> IRQ input from RTC
 * GPIO2 -> SYS_ENA*)
 * GPIO3 -> PWR_SCL
 * GPIO4 -> PWR_SDA
 * GPIO5 -> PowerCap0*)
 * GPIO6 -> PowerCap1*)
 * GPIO7 -> PowerCap2*)
 * GPIO8 -> PowerCap3*)
 * GPIO15 -> /CS1
 * GPIO20 -> /CS2
 * GPIO21 -> /CS3
 * GPIO33 -> /CS5 network controller select
 * GPIO52 -> IRQ from network controller
 * GPIO78 -> /CS2
 * GPIO80 -> /CS4
 * GPIO90 -> LED0
 * GPIO91 -> LED1
 * GPIO114 -> IRQ from CAN controller
 * GPIO117 -> SCL
 * GPIO118 -> SDA
 *
 * *) CPU पूर्णांकernal use only
 */

अटल अचिन्हित दीर्घ pcm027_pin_config[] __initdata = अणु
	/* Chip Selects */
	GPIO20_nSDCS_2,
	GPIO21_nSDCS_3,
	GPIO15_nCS_1,
	GPIO78_nCS_2,
	GPIO80_nCS_4,
	GPIO33_nCS_5,	/* Ethernet */

	/* I2C */
	GPIO117_I2C_SCL,
	GPIO118_I2C_SDA,

	/* GPIO */
	GPIO52_GPIO,	/* IRQ from network controller */
#अगर_घोषित CONFIG_LEDS_GPIO
	GPIO90_GPIO,	/* PCM027_LED_CPU */
	GPIO91_GPIO,	/* PCM027_LED_HEART_BEAT */
#पूर्ण_अगर
	GPIO114_GPIO,	/* IRQ from CAN controller */
पूर्ण;

/*
 * SMC91x network controller specअगरic stuff
 */
अटल काष्ठा resource smc91x_resources[] = अणु
	[0] = अणु
		.start	= PCM027_ETH_PHYS + 0x300,
		.end	= PCM027_ETH_PHYS + PCM027_ETH_SIZE,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start	= PCM027_ETH_IRQ,
		.end	= PCM027_ETH_IRQ,
		/* note: smc91x's driver doesn't use the trigger bits yet */
		.flags	= IORESOURCE_IRQ | PCM027_ETH_IRQ_EDGE,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device smc91x_device = अणु
	.name		= "smc91x",
	.id		= 0,
	.num_resources	= ARRAY_SIZE(smc91x_resources),
	.resource	= smc91x_resources,
पूर्ण;

/*
 * SPI host and devices
 */
अटल काष्ठा pxa2xx_spi_controller pxa_ssp_master_info = अणु
	.num_chipselect	= 1,
पूर्ण;

अटल काष्ठा max7301_platक्रमm_data max7301_info = अणु
	.base = -1,
पूर्ण;

/* bus_num must match id in pxa2xx_set_spi_info() call */
अटल काष्ठा spi_board_info spi_board_info[] __initdata = अणु
	अणु
		.modalias	= "max7301",
		.platक्रमm_data	= &max7301_info,
		.max_speed_hz	= 13000000,
		.bus_num	= 1,
		.chip_select	= 0,
		.mode		= SPI_MODE_0,
	पूर्ण,
पूर्ण;

/*
 * NOR flash
 */
अटल काष्ठा physmap_flash_data pcm027_flash_data = अणु
	.width  = 4,
पूर्ण;

अटल काष्ठा resource pcm027_flash_resource = अणु
	.start          = PCM027_FLASH_PHYS,
	.end            = PCM027_FLASH_PHYS + PCM027_FLASH_SIZE - 1 ,
	.flags          = IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device pcm027_flash = अणु
	.name           = "physmap-flash",
	.id             = 0,
	.dev            = अणु
		.platक्रमm_data  = &pcm027_flash_data,
	पूर्ण,
	.resource       = &pcm027_flash_resource,
	.num_resources  = 1,
पूर्ण;

#अगर_घोषित CONFIG_LEDS_GPIO

अटल काष्ठा gpio_led pcm027_led[] = अणु
	अणु
		.name = "led0:red",	/* FIXME */
		.gpio = PCM027_LED_CPU
	पूर्ण,
	अणु
		.name = "led1:green",	/* FIXME */
		.gpio = PCM027_LED_HEARD_BEAT
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data pcm027_led_data = अणु
	.num_leds	= ARRAY_SIZE(pcm027_led),
	.leds		= pcm027_led
पूर्ण;

अटल काष्ठा platक्रमm_device pcm027_led_dev = अणु
	.name		= "leds-gpio",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data	= &pcm027_led_data,
	पूर्ण,
पूर्ण;

#पूर्ण_अगर /* CONFIG_LEDS_GPIO */

/*
 * declare the available device resources on this board
 */
अटल काष्ठा platक्रमm_device *devices[] __initdata = अणु
	&smc91x_device,
	&pcm027_flash,
#अगर_घोषित CONFIG_LEDS_GPIO
	&pcm027_led_dev
#पूर्ण_अगर
पूर्ण;

/*
 * pcm027_init - breath some lअगरe पूर्णांकo the board
 */
अटल व्योम __init pcm027_init(व्योम)
अणु
	/* प्रणाली bus arbiter setting
	 * - Core_Park
	 * - LCD_wt:DMA_wt:CORE_Wt = 2:3:4
	 */
	ARB_CNTRL = ARB_CORE_PARK | 0x234;

	pxa2xx_mfp_config(pcm027_pin_config, ARRAY_SIZE(pcm027_pin_config));

	pxa_set_ffuart_info(शून्य);
	pxa_set_btuart_info(शून्य);
	pxa_set_stuart_info(शून्य);

	platक्रमm_add_devices(devices, ARRAY_SIZE(devices));

	/* at last call the baseboard to initialize itself */
#अगर_घोषित CONFIG_MACH_PCM990_BASEBOARD
	pcm990_baseboard_init();
#पूर्ण_अगर

	pxa2xx_set_spi_info(1, &pxa_ssp_master_info);
	spi_रेजिस्टर_board_info(spi_board_info, ARRAY_SIZE(spi_board_info));
पूर्ण

अटल व्योम __init pcm027_map_io(व्योम)
अणु
	pxa27x_map_io();

	/* initialize sleep mode regs (wake-up sources, etc) */
	PGSR0 = 0x01308000;
	PGSR1 = 0x00CF0002;
	PGSR2 = 0x0E294000;
	PGSR3 = 0x0000C000;
	PWER  = 0x40000000 | PWER_GPIO0 | PWER_GPIO1;
	PRER  = 0x00000000;
	PFER  = 0x00000003;
पूर्ण

MACHINE_START(PCM027, "Phytec Messtechnik GmbH phyCORE-PXA270")
	/* Maपूर्णांकainer: Pengutronix */
	.atag_offset	= 0x100,
	.map_io		= pcm027_map_io,
	.nr_irqs	= PCM027_NR_IRQS,
	.init_irq	= pxa27x_init_irq,
	.handle_irq	= pxa27x_handle_irq,
	.init_समय	= pxa_समयr_init,
	.init_machine	= pcm027_init,
	.restart	= pxa_restart,
MACHINE_END
