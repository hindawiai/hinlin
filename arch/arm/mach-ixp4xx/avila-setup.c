<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/mach-ixp4xx/avila-setup.c
 *
 * Gateworks Avila board-setup
 *
 * Author: Michael-Luke Jones <mlj28@cam.ac.uk>
 *
 * Based on ixdp-setup.c
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
#समावेश <linux/gpio/machine.h>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/setup.h>
#समावेश <यंत्र/memory.h>
#समावेश <mach/hardware.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "irqs.h"

#घोषणा AVILA_SDA_PIN	7
#घोषणा AVILA_SCL_PIN	6

अटल काष्ठा flash_platक्रमm_data avila_flash_data = अणु
	.map_name	= "cfi_probe",
	.width		= 2,
पूर्ण;

अटल काष्ठा resource avila_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device avila_flash = अणु
	.name		= "IXP4XX-Flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &avila_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &avila_flash_resource,
पूर्ण;

अटल काष्ठा gpiod_lookup_table avila_i2c_gpiod_table = अणु
	.dev_id		= "i2c-gpio.0",
	.table		= अणु
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", AVILA_SDA_PIN,
				शून्य, 0, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", AVILA_SCL_PIN,
				शून्य, 1, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device avila_i2c_gpio = अणु
	.name		= "i2c-gpio",
	.id		= 0,
	.dev	 = अणु
		.platक्रमm_data	= शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource avila_uart_resources[] = अणु
	अणु
		.start		= IXP4XX_UART1_BASE_PHYS,
		.end		= IXP4XX_UART1_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM
	पूर्ण,
	अणु
		.start		= IXP4XX_UART2_BASE_PHYS,
		.end		= IXP4XX_UART2_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM
	पूर्ण
पूर्ण;

अटल काष्ठा plat_serial8250_port avila_uart_data[] = अणु
	अणु
		.mapbase	= IXP4XX_UART1_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART1_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART1,
		.flags		= UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
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

अटल काष्ठा platक्रमm_device avila_uart = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev.platक्रमm_data	= avila_uart_data,
	.num_resources		= 2,
	.resource		= avila_uart_resources
पूर्ण;

अटल काष्ठा resource avila_pata_resources[] = अणु
	अणु
		.flags	= IORESOURCE_MEM
	पूर्ण,
	अणु
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.name	= "intrq",
		.start	= IRQ_IXP4XX_GPIO12,
		.end	= IRQ_IXP4XX_GPIO12,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा ixp4xx_pata_data avila_pata_data = अणु
	.cs0_bits	= 0xbfff0043,
	.cs1_bits	= 0xbfff0043,
पूर्ण;

अटल काष्ठा platक्रमm_device avila_pata = अणु
	.name			= "pata_ixp4xx_cf",
	.id			= 0,
	.dev.platक्रमm_data      = &avila_pata_data,
	.num_resources		= ARRAY_SIZE(avila_pata_resources),
	.resource		= avila_pata_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *avila_devices[] __initdata = अणु
	&avila_i2c_gpio,
	&avila_flash,
	&avila_uart
पूर्ण;

अटल व्योम __init avila_init(व्योम)
अणु
	ixp4xx_sys_init();

	avila_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	avila_flash_resource.end =
		IXP4XX_EXP_BUS_BASE(0) + ixp4xx_exp_bus_size - 1;

	gpiod_add_lookup_table(&avila_i2c_gpiod_table);

	platक्रमm_add_devices(avila_devices, ARRAY_SIZE(avila_devices));

	avila_pata_resources[0].start = IXP4XX_EXP_BUS_BASE(1);
	avila_pata_resources[0].end = IXP4XX_EXP_BUS_END(1);

	avila_pata_resources[1].start = IXP4XX_EXP_BUS_BASE(2);
	avila_pata_resources[1].end = IXP4XX_EXP_BUS_END(2);

	avila_pata_data.cs0_cfg = IXP4XX_EXP_CS1;
	avila_pata_data.cs1_cfg = IXP4XX_EXP_CS2;

	platक्रमm_device_रेजिस्टर(&avila_pata);

पूर्ण

MACHINE_START(AVILA, "Gateworks Avila Network Platform")
	/* Maपूर्णांकainer: Deepak Saxena <dsaxena@plनिकासy.net> */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= avila_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END

 /*
  * Loft is functionally equivalent to Avila except that it has a
  * dअगरferent number क्रम the maximum PCI devices.  The MACHINE
  * काष्ठाure below is identical to Avila except क्रम the comment.
  */
#अगर_घोषित CONFIG_MACH_LOFT
MACHINE_START(LOFT, "Giant Shoulder Inc Loft board")
	/* Maपूर्णांकainer: Tom Billman <kernel@giantshoulderinc.com> */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= avila_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
#पूर्ण_अगर

