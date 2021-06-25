<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/mach-ixp4xx/vulcan-setup.c
 *
 * Arcom/Eurotech Vulcan board-setup
 *
 * Copyright (C) 2010 Marc Zyngier <maz@misterjones.org>
 *
 * based on fsg-setup.c:
 *	Copyright (C) 2008 Rod Whitby <rod@whitby.id.au>
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/irq.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/पन.स>
#समावेश <linux/w1-gpपन.स>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/mtd/plat-ram.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "irqs.h"

अटल काष्ठा flash_platक्रमm_data vulcan_flash_data = अणु
	.map_name	= "cfi_probe",
	.width		= 2,
पूर्ण;

अटल काष्ठा resource vulcan_flash_resource = अणु
	.flags			= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device vulcan_flash = अणु
	.name			= "IXP4XX-Flash",
	.id			= 0,
	.dev = अणु
		.platक्रमm_data	= &vulcan_flash_data,
	पूर्ण,
	.resource		= &vulcan_flash_resource,
	.num_resources		= 1,
पूर्ण;

अटल काष्ठा platdata_mtd_ram vulcan_sram_data = अणु
	.mapname	= "Vulcan SRAM",
	.bankwidth	= 1,
पूर्ण;

अटल काष्ठा resource vulcan_sram_resource = अणु
	.flags			= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device vulcan_sram = अणु
	.name			= "mtd-ram",
	.id			= 0,
	.dev = अणु
		.platक्रमm_data	= &vulcan_sram_data,
	पूर्ण,
	.resource		= &vulcan_sram_resource,
	.num_resources		= 1,
पूर्ण;

अटल काष्ठा resource vulcan_uart_resources[] = अणु
	[0] = अणु
		.start		= IXP4XX_UART1_BASE_PHYS,
		.end		= IXP4XX_UART1_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[1] = अणु
		.start		= IXP4XX_UART2_BASE_PHYS,
		.end		= IXP4XX_UART2_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	[2] = अणु
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port vulcan_uart_data[] = अणु
	[0] = अणु
		.mapbase	= IXP4XX_UART1_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART1_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART1,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	[1] = अणु
		.mapbase	= IXP4XX_UART2_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART2_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	[2] = अणु
		.irq		= IXP4XX_GPIO_IRQ(4),
		.irqflags	= IRQF_TRIGGER_LOW,
		.flags		= UPF_IOREMAP | UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.uartclk	= 1843200,
	पूर्ण,
	[3] = अणु
		.irq		= IXP4XX_GPIO_IRQ(4),
		.irqflags	= IRQF_TRIGGER_LOW,
		.flags		= UPF_IOREMAP | UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.uartclk	= 1843200,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device vulcan_uart = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev = अणु
		.platक्रमm_data	= vulcan_uart_data,
	पूर्ण,
	.resource		= vulcan_uart_resources,
	.num_resources		= ARRAY_SIZE(vulcan_uart_resources),
पूर्ण;

अटल काष्ठा resource vulcan_npeb_resources[] = अणु
	अणु
		.start		= IXP4XX_EthB_BASE_PHYS,
		.end		= IXP4XX_EthB_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource vulcan_npec_resources[] = अणु
	अणु
		.start		= IXP4XX_EthC_BASE_PHYS,
		.end		= IXP4XX_EthC_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा eth_plat_info vulcan_plat_eth[] = अणु
	[0] = अणु
		.phy		= 0,
		.rxq		= 3,
		.txपढ़ोyq	= 20,
	पूर्ण,
	[1] = अणु
		.phy		= 1,
		.rxq		= 4,
		.txपढ़ोyq	= 21,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device vulcan_eth[] = अणु
	[0] = अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEB,
		.dev = अणु
			.platक्रमm_data	= &vulcan_plat_eth[0],
		पूर्ण,
		.num_resources		= ARRAY_SIZE(vulcan_npeb_resources),
		.resource		= vulcan_npeb_resources,
	पूर्ण,
	[1] = अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEC,
		.dev = अणु
			.platक्रमm_data	= &vulcan_plat_eth[1],
		पूर्ण,
		.num_resources		= ARRAY_SIZE(vulcan_npec_resources),
		.resource		= vulcan_npec_resources,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource vulcan_max6369_resource = अणु
	.flags			= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device vulcan_max6369 = अणु
	.name			= "max6369_wdt",
	.id			= -1,
	.resource		= &vulcan_max6369_resource,
	.num_resources		= 1,
पूर्ण;

अटल काष्ठा gpiod_lookup_table vulcan_w1_gpiod_table = अणु
	.dev_id = "w1-gpio",
	.table = अणु
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", 14, शून्य, 0,
				GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा w1_gpio_platक्रमm_data vulcan_w1_gpio_pdata = अणु
	/* Intentionally left blank */
पूर्ण;

अटल काष्ठा platक्रमm_device vulcan_w1_gpio = अणु
	.name			= "w1-gpio",
	.id			= 0,
	.dev			= अणु
		.platक्रमm_data	= &vulcan_w1_gpio_pdata,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device *vulcan_devices[] __initdata = अणु
	&vulcan_uart,
	&vulcan_flash,
	&vulcan_sram,
	&vulcan_max6369,
	&vulcan_eth[0],
	&vulcan_eth[1],
	&vulcan_w1_gpio,
पूर्ण;

अटल व्योम __init vulcan_init(व्योम)
अणु
	ixp4xx_sys_init();

	/* Flash is spपढ़ो over both CS0 and CS1 */
	vulcan_flash_resource.start	 = IXP4XX_EXP_BUS_BASE(0);
	vulcan_flash_resource.end	 = IXP4XX_EXP_BUS_BASE(0) + SZ_32M - 1;
	*IXP4XX_EXP_CS0 = IXP4XX_EXP_BUS_CS_EN		|
			  IXP4XX_EXP_BUS_STROBE_T(3)	|
			  IXP4XX_EXP_BUS_SIZE(0xF)	|
			  IXP4XX_EXP_BUS_BYTE_RD16	|
			  IXP4XX_EXP_BUS_WR_EN;
	*IXP4XX_EXP_CS1 = *IXP4XX_EXP_CS0;

	/* SRAM on CS2, (256kB, 8bit, writable) */
	vulcan_sram_resource.start	= IXP4XX_EXP_BUS_BASE(2);
	vulcan_sram_resource.end	= IXP4XX_EXP_BUS_BASE(2) + SZ_256K - 1;
	*IXP4XX_EXP_CS2 = IXP4XX_EXP_BUS_CS_EN		|
			  IXP4XX_EXP_BUS_STROBE_T(1)	|
			  IXP4XX_EXP_BUS_HOLD_T(2)	|
			  IXP4XX_EXP_BUS_SIZE(9)	|
			  IXP4XX_EXP_BUS_SPLT_EN	|
			  IXP4XX_EXP_BUS_WR_EN		|
			  IXP4XX_EXP_BUS_BYTE_EN;

	/* XR16L2551 on CS3 (Moto style, 512 bytes, 8bits, writable) */
	vulcan_uart_resources[2].start	= IXP4XX_EXP_BUS_BASE(3);
	vulcan_uart_resources[2].end	= IXP4XX_EXP_BUS_BASE(3) + 16 - 1;
	vulcan_uart_data[2].mapbase	= vulcan_uart_resources[2].start;
	vulcan_uart_data[3].mapbase	= vulcan_uart_data[2].mapbase + 8;
	*IXP4XX_EXP_CS3 = IXP4XX_EXP_BUS_CS_EN		|
			  IXP4XX_EXP_BUS_STROBE_T(3)	|
			  IXP4XX_EXP_BUS_CYCLES(IXP4XX_EXP_BUS_CYCLES_MOTOROLA)|
			  IXP4XX_EXP_BUS_WR_EN		|
			  IXP4XX_EXP_BUS_BYTE_EN;

	/* GPIOS on CS4 (512 bytes, 8bits, writable) */
	*IXP4XX_EXP_CS4 = IXP4XX_EXP_BUS_CS_EN		|
			  IXP4XX_EXP_BUS_WR_EN		|
			  IXP4XX_EXP_BUS_BYTE_EN;

	/* max6369 on CS5 (512 bytes, 8bits, writable) */
	vulcan_max6369_resource.start	= IXP4XX_EXP_BUS_BASE(5);
	vulcan_max6369_resource.end	= IXP4XX_EXP_BUS_BASE(5);
	*IXP4XX_EXP_CS5 = IXP4XX_EXP_BUS_CS_EN		|
			  IXP4XX_EXP_BUS_WR_EN		|
			  IXP4XX_EXP_BUS_BYTE_EN;

	gpiod_add_lookup_table(&vulcan_w1_gpiod_table);
	platक्रमm_add_devices(vulcan_devices, ARRAY_SIZE(vulcan_devices));
पूर्ण

MACHINE_START(ARCOM_VULCAN, "Arcom/Eurotech Vulcan")
	/* Maपूर्णांकainer: Marc Zyngier <maz@misterjones.org> */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= vulcan_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
