<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * arch/arm/mach-ixp4xx/omixp-setup.c
 *
 * omicron ixp4xx board setup
 *      Copyright (C) 2009 OMICRON electronics GmbH
 *
 * based nslu2-setup.c, ixdp425-setup.c:
 *      Copyright (C) 2003-2004 MontaVista Software, Inc.
 */

#समावेश <linux/kernel.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/mtd/mtd.h>
#समावेश <linux/mtd/partitions.h>
#समावेश <linux/leds.h>

#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश <mach/hardware.h>

#समावेश "irqs.h"

अटल काष्ठा resource omixp_flash_resources[] = अणु
	अणु
		.flags	= IORESOURCE_MEM,
	पूर्ण, अणु
		.flags	= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा mtd_partition omixp_partitions[] = अणु
	अणु
		.name =		"Recovery Bootloader",
		.size =		0x00020000,
		.offset =	0,
	पूर्ण, अणु
		.name =		"Calibration Data",
		.size =		0x00020000,
		.offset =	0x00020000,
	पूर्ण, अणु
		.name =		"Recovery FPGA",
		.size =		0x00020000,
		.offset =	0x00040000,
	पूर्ण, अणु
		.name =		"Release Bootloader",
		.size =		0x00020000,
		.offset =	0x00060000,
	पूर्ण, अणु
		.name =		"Release FPGA",
		.size =		0x00020000,
		.offset =	0x00080000,
	पूर्ण, अणु
		.name =		"Kernel",
		.size =		0x00160000,
		.offset =	0x000a0000,
	पूर्ण, अणु
		.name =		"Filesystem",
		.size =		0x00C00000,
		.offset =	0x00200000,
	पूर्ण, अणु
		.name =		"Persistent Storage",
		.size =		0x00200000,
		.offset =	0x00E00000,
	पूर्ण,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data omixp_flash_data[] = अणु
	अणु
		.map_name	= "cfi_probe",
		.parts		= omixp_partitions,
		.nr_parts	= ARRAY_SIZE(omixp_partitions),
	पूर्ण, अणु
		.map_name	= "cfi_probe",
		.parts		= शून्य,
		.nr_parts	= 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device omixp_flash_device[] = अणु
	अणु
		.name		= "IXP4XX-Flash",
		.id		= 0,
		.dev = अणु
			.platक्रमm_data = &omixp_flash_data[0],
		पूर्ण,
		.resource = &omixp_flash_resources[0],
		.num_resources = 1,
	पूर्ण, अणु
		.name		= "IXP4XX-Flash",
		.id		= 1,
		.dev = अणु
			.platक्रमm_data = &omixp_flash_data[1],
		पूर्ण,
		.resource = &omixp_flash_resources[1],
		.num_resources = 1,
	पूर्ण,
पूर्ण;

/* Swap UART's - These boards have the console on UART2. The following
 * configuration is used:
 *      ttyS0 .. UART2
 *      ttyS1 .. UART1
 * This way standard images can be used with the kernel that expect
 * the console on ttyS0.
 */
अटल काष्ठा resource omixp_uart_resources[] = अणु
	अणु
		.start		= IXP4XX_UART2_BASE_PHYS,
		.end		= IXP4XX_UART2_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण, अणु
		.start		= IXP4XX_UART1_BASE_PHYS,
		.end		= IXP4XX_UART1_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port omixp_uart_data[] = अणु
	अणु
		.mapbase	= IXP4XX_UART2_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART2_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण, अणु
		.mapbase	= IXP4XX_UART1_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART1_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART1,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण, अणु
		/* list termination */
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device omixp_uart = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev.platक्रमm_data	= omixp_uart_data,
	.num_resources		= 2,
	.resource		= omixp_uart_resources,
पूर्ण;

अटल काष्ठा gpio_led mic256_led_pins[] = अणु
	अणु
		.name		= "LED-A",
		.gpio		= 7,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data mic256_led_data = अणु
	.num_leds		= ARRAY_SIZE(mic256_led_pins),
	.leds			= mic256_led_pins,
पूर्ण;

अटल काष्ठा platक्रमm_device mic256_leds = अणु
	.name			= "leds-gpio",
	.id			= -1,
	.dev.platक्रमm_data	= &mic256_led_data,
पूर्ण;

/* Built-in 10/100 Ethernet MAC पूर्णांकerfaces */
अटल काष्ठा resource ixp425_npeb_resources[] = अणु
	अणु
		.start		= IXP4XX_EthB_BASE_PHYS,
		.end		= IXP4XX_EthB_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource ixp425_npec_resources[] = अणु
	अणु
		.start		= IXP4XX_EthC_BASE_PHYS,
		.end		= IXP4XX_EthC_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा eth_plat_info ixdp425_plat_eth[] = अणु
	अणु
		.phy		= 0,
		.rxq		= 3,
		.txपढ़ोyq	= 20,
	पूर्ण, अणु
		.phy		= 1,
		.rxq		= 4,
		.txपढ़ोyq	= 21,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device ixdp425_eth[] = अणु
	अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEB,
		.dev.platक्रमm_data	= ixdp425_plat_eth,
		.num_resources		= ARRAY_SIZE(ixp425_npeb_resources),
		.resource		= ixp425_npeb_resources,
	पूर्ण, अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEC,
		.dev.platक्रमm_data	= ixdp425_plat_eth + 1,
		.num_resources		= ARRAY_SIZE(ixp425_npec_resources),
		.resource		= ixp425_npec_resources,
	पूर्ण,
पूर्ण;


अटल काष्ठा platक्रमm_device *devixp_pldev[] __initdata = अणु
	&omixp_uart,
	&omixp_flash_device[0],
	&ixdp425_eth[0],
	&ixdp425_eth[1],
पूर्ण;

अटल काष्ठा platक्रमm_device *mic256_pldev[] __initdata = अणु
	&omixp_uart,
	&omixp_flash_device[0],
	&mic256_leds,
	&ixdp425_eth[0],
	&ixdp425_eth[1],
पूर्ण;

अटल काष्ठा platक्रमm_device *miccpt_pldev[] __initdata = अणु
	&omixp_uart,
	&omixp_flash_device[0],
	&omixp_flash_device[1],
	&ixdp425_eth[0],
	&ixdp425_eth[1],
पूर्ण;

अटल व्योम __init omixp_init(व्योम)
अणु
	ixp4xx_sys_init();

	/* 16MiB Boot Flash */
	omixp_flash_resources[0].start = IXP4XX_EXP_BUS_BASE(0);
	omixp_flash_resources[0].end   = IXP4XX_EXP_BUS_END(0);

	/* 32 MiB Data Flash */
	omixp_flash_resources[1].start = IXP4XX_EXP_BUS_BASE(2);
	omixp_flash_resources[1].end   = IXP4XX_EXP_BUS_END(2);

	अगर (machine_is_devixp())
		platक्रमm_add_devices(devixp_pldev, ARRAY_SIZE(devixp_pldev));
	अन्यथा अगर (machine_is_miccpt())
		platक्रमm_add_devices(miccpt_pldev, ARRAY_SIZE(miccpt_pldev));
	अन्यथा अगर (machine_is_mic256())
		platक्रमm_add_devices(mic256_pldev, ARRAY_SIZE(mic256_pldev));
पूर्ण

#अगर_घोषित CONFIG_MACH_DEVIXP
MACHINE_START(DEVIXP, "Omicron DEVIXP")
	.atag_offset    = 0x100,
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.init_machine	= omixp_init,
	.restart	= ixp4xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_MICCPT
MACHINE_START(MICCPT, "Omicron MICCPT")
	.atag_offset    = 0x100,
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.init_machine	= omixp_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
#पूर्ण_अगर

#अगर_घोषित CONFIG_MACH_MIC256
MACHINE_START(MIC256, "Omicron MIC256")
	.atag_offset    = 0x100,
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.init_machine	= omixp_init,
	.restart	= ixp4xx_restart,
MACHINE_END
#पूर्ण_अगर
