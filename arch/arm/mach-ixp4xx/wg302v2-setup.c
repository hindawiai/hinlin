<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/mach-ixp4xx/wg302-setup.c
 *
 * Board setup क्रम the Netgear WG302 v2 and WAG302 v2
 *
 * Copyright (C) 2007 Imre Kaloz <Kaloz@खोलोwrt.org>
 *
 * based on coyote-setup.c:
 *      Copyright (C) 2003-2005 MontaVista Software, Inc.
 *
 * Author: Imre Kaloz <kaloz@खोलोwrt.org>
 *
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

अटल काष्ठा flash_platक्रमm_data wg302v2_flash_data = अणु
	.map_name	= "cfi_probe",
	.width		= 2,
पूर्ण;

अटल काष्ठा resource wg302v2_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device wg302v2_flash = अणु
	.name		= "IXP4XX-Flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &wg302v2_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &wg302v2_flash_resource,
पूर्ण;

अटल काष्ठा resource wg302v2_uart_resource = अणु
	.start	= IXP4XX_UART2_BASE_PHYS,
	.end	= IXP4XX_UART2_BASE_PHYS + 0x0fff,
	.flags	= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा plat_serial8250_port wg302v2_uart_data[] = अणु
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

अटल काष्ठा platक्रमm_device wg302v2_uart = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= wg302v2_uart_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &wg302v2_uart_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device *wg302v2_devices[] __initdata = अणु
	&wg302v2_flash,
	&wg302v2_uart,
पूर्ण;

अटल व्योम __init wg302v2_init(व्योम)
अणु
	ixp4xx_sys_init();

	wg302v2_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	wg302v2_flash_resource.end = IXP4XX_EXP_BUS_BASE(0) + SZ_32M - 1;

	*IXP4XX_EXP_CS0 |= IXP4XX_FLASH_WRITABLE;
	*IXP4XX_EXP_CS1 = *IXP4XX_EXP_CS0;

	platक्रमm_add_devices(wg302v2_devices, ARRAY_SIZE(wg302v2_devices));
पूर्ण

#अगर_घोषित CONFIG_MACH_WG302V2
MACHINE_START(WG302V2, "Netgear WG302 v2 / WAG302 v2")
	/* Maपूर्णांकainer: Imre Kaloz <kaloz@खोलोwrt.org> */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= wg302v2_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
#पूर्ण_अगर
