<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * arch/arm/mach-ixp4xx/gtwx5715-setup.c
 *
 * Gemtek GTWX5715 (Linksys WRV54G) board setup
 *
 * Copyright (C) 2004 George T. Joseph
 * Derived from Coyote
 */

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

/* GPIO 5,6,7 and 12 are hard wired to the Kendin KS8995M Switch
   and operate as an SPI type पूर्णांकerface.  The details of the पूर्णांकerface
   are available on Kendin/Micrel's web site. */

#घोषणा GTWX5715_KSSPI_SELECT	5
#घोषणा GTWX5715_KSSPI_TXD	6
#घोषणा GTWX5715_KSSPI_CLOCK	7
#घोषणा GTWX5715_KSSPI_RXD	12

/* The "reset" button is wired to GPIO 3.
   The GPIO is brought "low" when the button is pushed. */

#घोषणा GTWX5715_BUTTON_GPIO	3

/* Board Label      Front Label
   LED1             Power
   LED2             Wireless-G
   LED3             not populated but could be
   LED4             Internet
   LED5 - LED8      Controlled by KS8995M Switch
   LED9             DMZ */

#घोषणा GTWX5715_LED1_GPIO	2
#घोषणा GTWX5715_LED2_GPIO	9
#घोषणा GTWX5715_LED3_GPIO	8
#घोषणा GTWX5715_LED4_GPIO	1
#घोषणा GTWX5715_LED9_GPIO	4

/*
 * Xscale UART रेजिस्टरs are 32 bits wide with only the least
 * signअगरicant 8 bits having any meaning.  From a configuration
 * perspective, this means 2 things...
 *
 *   Setting .regshअगरt = 2 so that the standard 16550 रेजिस्टरs
 *   line up on every 4th byte.
 *
 *   Shअगरting the रेजिस्टर start भव address +3 bytes when
 *   compiled big-endian.  Since रेजिस्टर ग_लिखोs are करोne on a
 *   single byte basis, अगर the shअगरt isn't करोne the driver will
 *   ग_लिखो the value पूर्णांकo the most signअगरicant byte of the रेजिस्टर,
 *   which is ignored, instead of the least signअगरicant.
 */

#अगर_घोषित	__ARMEB__
#घोषणा	REG_OFFSET	3
#अन्यथा
#घोषणा	REG_OFFSET	0
#पूर्ण_अगर

/*
 * Only the second or "console" uart is connected on the gtwx5715.
 */

अटल काष्ठा resource gtwx5715_uart_resources[] = अणु
	अणु
		.start	= IXP4XX_UART2_BASE_PHYS,
		.end	= IXP4XX_UART2_BASE_PHYS + 0x0fff,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= IRQ_IXP4XX_UART2,
		.end	= IRQ_IXP4XX_UART2,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
	अणु पूर्ण,
पूर्ण;


अटल काष्ठा plat_serial8250_port gtwx5715_uart_platक्रमm_data[] = अणु
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

अटल काष्ठा platक्रमm_device gtwx5715_uart_device = अणु
	.name		= "serial8250",
	.id		= PLAT8250_DEV_PLATFORM,
	.dev			= अणु
		.platक्रमm_data	= gtwx5715_uart_platक्रमm_data,
	पूर्ण,
	.num_resources	= 2,
	.resource	= gtwx5715_uart_resources,
पूर्ण;

अटल काष्ठा flash_platक्रमm_data gtwx5715_flash_data = अणु
	.map_name	= "cfi_probe",
	.width		= 2,
पूर्ण;

अटल काष्ठा resource gtwx5715_flash_resource = अणु
	.flags		= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device gtwx5715_flash = अणु
	.name		= "IXP4XX-Flash",
	.id		= 0,
	.dev		= अणु
		.platक्रमm_data = &gtwx5715_flash_data,
	पूर्ण,
	.num_resources	= 1,
	.resource	= &gtwx5715_flash_resource,
पूर्ण;

अटल काष्ठा platक्रमm_device *gtwx5715_devices[] __initdata = अणु
	&gtwx5715_uart_device,
	&gtwx5715_flash,
पूर्ण;

अटल व्योम __init gtwx5715_init(व्योम)
अणु
	ixp4xx_sys_init();

	gtwx5715_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	gtwx5715_flash_resource.end = IXP4XX_EXP_BUS_BASE(0) + SZ_8M - 1;

	platक्रमm_add_devices(gtwx5715_devices, ARRAY_SIZE(gtwx5715_devices));
पूर्ण


MACHINE_START(GTWX5715, "Gemtek GTWX5715 (Linksys WRV54G)")
	/* Maपूर्णांकainer: George Joseph */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= gtwx5715_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END


