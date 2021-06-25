<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/mach-ixp4xx/fsg-setup.c
 *
 * FSG board-setup
 *
 * Copyright (C) 2008 Rod Whitby <rod@whitby.id.au>
 *
 * based on ixdp425-setup.c:
 *	Copyright (C) 2003-2004 MontaVista Software, Inc.
 * based on nslu2-घातer.c
 *	Copyright (C) 2005 Tower Technologies
 *
 * Author: Rod Whitby <rod@whitby.id.au>
 * Maपूर्णांकainers: http://www.nslu2-linux.org/
 *
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/irq.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/leds.h>
#समावेश <linux/reboot.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/machine.h>
#समावेश <linux/पन.स>
#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>

#समावेश "irqs.h"

#घोषणा FSG_SDA_PIN		12
#घोषणा FSG_SCL_PIN		13

#घोषणा FSG_SB_GPIO		4	/* sync button */
#घोषणा FSG_RB_GPIO		9	/* reset button */
#घोषणा FSG_UB_GPIO		10	/* usb button */

अटल काष्ठा flash_platक्रमm_data fsg_flash_data = अणु
	.map_name		= "cfi_probe",
	.width			= 2,
पूर्ण;

अटल काष्ठा resource fsg_flash_resource = अणु
	.flags			= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device fsg_flash = अणु
	.name			= "IXP4XX-Flash",
	.id			= 0,
	.dev = अणु
		.platक्रमm_data	= &fsg_flash_data,
	पूर्ण,
	.num_resources		= 1,
	.resource		= &fsg_flash_resource,
पूर्ण;

अटल काष्ठा gpiod_lookup_table fsg_i2c_gpiod_table = अणु
	.dev_id		= "i2c-gpio.0",
	.table		= अणु
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", FSG_SDA_PIN,
				शून्य, 0, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", FSG_SCL_PIN,
				शून्य, 1, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device fsg_i2c_gpio = अणु
	.name			= "i2c-gpio",
	.id			= 0,
	.dev = अणु
		.platक्रमm_data	= शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata fsg_i2c_board_info [] = अणु
	अणु
		I2C_BOARD_INFO("isl1208", 0x6f),
	पूर्ण,
पूर्ण;

अटल काष्ठा resource fsg_uart_resources[] = अणु
	अणु
		.start		= IXP4XX_UART1_BASE_PHYS,
		.end		= IXP4XX_UART1_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start		= IXP4XX_UART2_BASE_PHYS,
		.end		= IXP4XX_UART2_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण
पूर्ण;

अटल काष्ठा plat_serial8250_port fsg_uart_data[] = अणु
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
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device fsg_uart = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev = अणु
		.platक्रमm_data	= fsg_uart_data,
	पूर्ण,
	.num_resources		= ARRAY_SIZE(fsg_uart_resources),
	.resource		= fsg_uart_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device fsg_leds = अणु
	.name		= "fsg-led",
	.id		= -1,
पूर्ण;

/* Built-in 10/100 Ethernet MAC पूर्णांकerfaces */
अटल काष्ठा resource fsg_eth_npeb_resources[] = अणु
	अणु
		.start		= IXP4XX_EthB_BASE_PHYS,
		.end		= IXP4XX_EthB_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource fsg_eth_npec_resources[] = अणु
	अणु
		.start		= IXP4XX_EthC_BASE_PHYS,
		.end		= IXP4XX_EthC_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा eth_plat_info fsg_plat_eth[] = अणु
	अणु
		.phy		= 5,
		.rxq		= 3,
		.txपढ़ोyq	= 20,
	पूर्ण, अणु
		.phy		= 4,
		.rxq		= 4,
		.txपढ़ोyq	= 21,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device fsg_eth[] = अणु
	अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEB,
		.dev = अणु
			.platक्रमm_data	= fsg_plat_eth,
		पूर्ण,
		.num_resources	= ARRAY_SIZE(fsg_eth_npeb_resources),
		.resource	= fsg_eth_npeb_resources,
	पूर्ण, अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEC,
		.dev = अणु
			.platक्रमm_data	= fsg_plat_eth + 1,
		पूर्ण,
		.num_resources	= ARRAY_SIZE(fsg_eth_npec_resources),
		.resource	= fsg_eth_npec_resources,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *fsg_devices[] __initdata = अणु
	&fsg_i2c_gpio,
	&fsg_flash,
	&fsg_leds,
	&fsg_eth[0],
	&fsg_eth[1],
पूर्ण;

अटल irqवापस_t fsg_घातer_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	/* Signal init to करो the ctrlaltdel action, this will bypass init अगर
	 * it hasn't started and करो a kernel_restart.
	 */
	ctrl_alt_del();

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t fsg_reset_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	/* This is the paper-clip reset which करोes an emergency reboot. */
	prपूर्णांकk(KERN_INFO "Restarting system.\n");
	machine_restart(शून्य);

	/* This should never be reached. */
	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init fsg_init(व्योम)
अणु
	uपूर्णांक8_t __iomem *f;

	ixp4xx_sys_init();

	fsg_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	fsg_flash_resource.end =
		IXP4XX_EXP_BUS_BASE(0) + ixp4xx_exp_bus_size - 1;

	*IXP4XX_EXP_CS0 |= IXP4XX_FLASH_WRITABLE;
	*IXP4XX_EXP_CS1 = *IXP4XX_EXP_CS0;

	/* Configure CS2 क्रम operation, 8bit and writable */
	*IXP4XX_EXP_CS2 = 0xbfff0002;

	gpiod_add_lookup_table(&fsg_i2c_gpiod_table);
	i2c_रेजिस्टर_board_info(0, fsg_i2c_board_info,
				ARRAY_SIZE(fsg_i2c_board_info));

	/* This is only useful on a modअगरied machine, but it is valuable
	 * to have it first in order to see debug messages, and so that
	 * it करोes *not* get हटाओd अगर platक्रमm_add_devices fails!
	 */
	(व्योम)platक्रमm_device_रेजिस्टर(&fsg_uart);

	platक्रमm_add_devices(fsg_devices, ARRAY_SIZE(fsg_devices));

	अगर (request_irq(gpio_to_irq(FSG_RB_GPIO), &fsg_reset_handler,
			IRQF_TRIGGER_LOW, "FSG reset button", शून्य) < 0) अणु

		prपूर्णांकk(KERN_DEBUG "Reset Button IRQ %d not available\n",
			gpio_to_irq(FSG_RB_GPIO));
	पूर्ण

	अगर (request_irq(gpio_to_irq(FSG_SB_GPIO), &fsg_घातer_handler,
			IRQF_TRIGGER_LOW, "FSG power button", शून्य) < 0) अणु

		prपूर्णांकk(KERN_DEBUG "Power Button IRQ %d not available\n",
			gpio_to_irq(FSG_SB_GPIO));
	पूर्ण

	/*
	 * Map in a portion of the flash and पढ़ो the MAC addresses.
	 * Since it is stored in BE in the flash itself, we need to
	 * byteswap it अगर we're in LE mode.
	 */
	f = ioremap(IXP4XX_EXP_BUS_BASE(0), 0x400000);
	अगर (f) अणु
#अगर_घोषित __ARMEB__
		पूर्णांक i;
		क्रम (i = 0; i < 6; i++) अणु
			fsg_plat_eth[0].hwaddr[i] = पढ़ोb(f + 0x3C0422 + i);
			fsg_plat_eth[1].hwaddr[i] = पढ़ोb(f + 0x3C043B + i);
		पूर्ण
#अन्यथा

		/*
		  Endian-swapped पढ़ोs from unaligned addresses are
		  required to extract the two MACs from the big-endian
		  Redboot config area in flash.
		*/

		fsg_plat_eth[0].hwaddr[0] = पढ़ोb(f + 0x3C0421);
		fsg_plat_eth[0].hwaddr[1] = पढ़ोb(f + 0x3C0420);
		fsg_plat_eth[0].hwaddr[2] = पढ़ोb(f + 0x3C0427);
		fsg_plat_eth[0].hwaddr[3] = पढ़ोb(f + 0x3C0426);
		fsg_plat_eth[0].hwaddr[4] = पढ़ोb(f + 0x3C0425);
		fsg_plat_eth[0].hwaddr[5] = पढ़ोb(f + 0x3C0424);

		fsg_plat_eth[1].hwaddr[0] = पढ़ोb(f + 0x3C0439);
		fsg_plat_eth[1].hwaddr[1] = पढ़ोb(f + 0x3C043F);
		fsg_plat_eth[1].hwaddr[2] = पढ़ोb(f + 0x3C043E);
		fsg_plat_eth[1].hwaddr[3] = पढ़ोb(f + 0x3C043D);
		fsg_plat_eth[1].hwaddr[4] = पढ़ोb(f + 0x3C043C);
		fsg_plat_eth[1].hwaddr[5] = पढ़ोb(f + 0x3C0443);
#पूर्ण_अगर
		iounmap(f);
	पूर्ण
	prपूर्णांकk(KERN_INFO "FSG: Using MAC address %pM for port 0\n",
	       fsg_plat_eth[0].hwaddr);
	prपूर्णांकk(KERN_INFO "FSG: Using MAC address %pM for port 1\n",
	       fsg_plat_eth[1].hwaddr);

पूर्ण

MACHINE_START(FSG, "Freecom FSG-3")
	/* Maपूर्णांकainer: www.nslu2-linux.org */
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.atag_offset	= 0x100,
	.init_machine	= fsg_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END

