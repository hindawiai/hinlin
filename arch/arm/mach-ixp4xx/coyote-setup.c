<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/mach-ixp4xx/coyote-setup.c
 *
 * Board setup क्रम ADI Engineering and IXDGP425 boards
 *
 * Copyright (C) 2003-2005 MontaVista Software, Inc.
 *
 * Author: Deepak Saxena <dsaxena@plनिकासy.net>
 */

#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/device.h>
#समावेश <linux/serial.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_8250.h>

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "irqs.h"

#घोषणा COYOTE_IDE_BASE_PHYS	IXP4XX_EXP_BUS_BASE(3)
#घोषणा COYOTE_IDE_BASE_VIRT	0xFFFE1000
#घोषणा COYOTE_IDE_REGION_SIZE	0x1000

#घोषणा COYOTE_IDE_DATA_PORT	0xFFFE10E0
#घोषणा COYOTE_IDE_CTRL_PORT	0xFFFE10FC
#घोषणा COYOTE_IDE_ERROR_PORT	0xFFFE10E2
#घोषणा IRQ_COYOTE_IDE		IRQ_IXP4XX_GPIO5

अटल काष्ठा flash_platक्रमm_data coyote_flash_data = अणु
	.map_name	= "cfi_probe",
	.width		= 2,
पूर्ण;

अटल काष्ठा resource coyote_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device coyote_flash = अणु
	.name		= "IXP4XX-Flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &coyote_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &coyote_flash_resource,
पूर्ण;

अटल काष्ठा resource coyote_uart_resource = अणु
	.start	= IXP4XX_UART2_BASE_PHYS,
	.end	= IXP4XX_UART2_BASE_PHYS + 0x0fff,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा plat_serial8250_port coyote_uart_data[] = अणु
	अणु
		.mapbase	= IXP4XX_UART2_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART2_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART2,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device coyote_uart = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= coyote_uart_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &coyote_uart_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device *coyote_devices[] __initdata = अणु
	&coyote_flash,
	&coyote_uart
पूर्ण;

अटल व्योम __init coyote_init(व्योम)
अणु
	ixp4xx_sys_init();

	coyote_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	coyote_flash_resource.end = IXP4XX_EXP_BUS_BASE(0) + SZ_32M - 1;

	*IXP4XX_EXP_CS0 |= IXP4XX_FLASH_WRITABLE;
	*IXP4XX_EXP_CS1 = *IXP4XX_EXP_CS0;

	अगर (machine_is_ixdpg425()) अणु
		coyote_uart_data[0].membase =
			(अक्षर*)(IXP4XX_UART1_BASE_VIRT + REG_OFFSET);
		coyote_uart_data[0].mapbase = IXP4XX_UART1_BASE_PHYS;
		coyote_uart_data[0].irq = IRQ_IXP4XX_UART1;
	पूर्ण

	platक्रमm_add_devices(coyote_devices, ARRAY_SIZE(coyote_devices));
पूर्ण

#अगर_घोषित CONFIG_ARCH_ADI_COYOTE
MACHINE_START(ADI_COYOTE, "ADI Engineering Coyote")
	/* Maपूर्णांकainer: MontaVista Software, Inc. */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= coyote_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
#पूर्ण_अगर

/*
 * IXDPG425 is identical to Coyote except क्रम which serial port
 * is connected.
 */
#अगर_घोषित CONFIG_MACH_IXDPG425
MACHINE_START(IXDPG425, "Intel IXDPG425")
	/* Maपूर्णांकainer: MontaVista Software, Inc. */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= coyote_init,
	.restart	= ixp4xx_restart,
MACHINE_END
#पूर्ण_अगर

