<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/mach-ixp4xx/nslu2-setup.c
 *
 * NSLU2 board-setup
 *
 * Copyright (C) 2008 Rod Whitby <rod@whitby.id.au>
 *
 * based on ixdp425-setup.c:
 *      Copyright (C) 2003-2004 MontaVista Software, Inc.
 * based on nslu2-घातer.c:
 *	Copyright (C) 2005 Tower Technologies
 *
 * Author: Mark Rakes <mrakes at mac.com>
 * Author: Rod Whitby <rod@whitby.id.au>
 * Author: Alessandro Zummo <a.zummo@towertech.it>
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
#समावेश <यंत्र/mach/समय.स>

#समावेश "irqs.h"

#घोषणा NSLU2_SDA_PIN		7
#घोषणा NSLU2_SCL_PIN		6

/* NSLU2 Timer */
#घोषणा NSLU2_FREQ 66000000

/* Buttons */
#घोषणा NSLU2_PB_GPIO		5	/* घातer button */
#घोषणा NSLU2_PO_GPIO		8	/* घातer off */
#घोषणा NSLU2_RB_GPIO		12	/* reset button */

/* Buzzer */
#घोषणा NSLU2_GPIO_BUZZ		4

/* LEDs */
#घोषणा NSLU2_LED_RED_GPIO	0
#घोषणा NSLU2_LED_GRN_GPIO	1
#घोषणा NSLU2_LED_DISK1_GPIO	3
#घोषणा NSLU2_LED_DISK2_GPIO	2

अटल काष्ठा flash_platक्रमm_data nslu2_flash_data = अणु
	.map_name		= "cfi_probe",
	.width			= 2,
पूर्ण;

अटल काष्ठा resource nslu2_flash_resource = अणु
	.flags			= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device nslu2_flash = अणु
	.name			= "IXP4XX-Flash",
	.id			= 0,
	.dev.platक्रमm_data	= &nslu2_flash_data,
	.num_resources		= 1,
	.resource		= &nslu2_flash_resource,
पूर्ण;

अटल काष्ठा gpiod_lookup_table nslu2_i2c_gpiod_table = अणु
	.dev_id		= "i2c-gpio.0",
	.table		= अणु
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", NSLU2_SDA_PIN,
				शून्य, 0, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", NSLU2_SCL_PIN,
				शून्य, 1, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata nslu2_i2c_board_info [] = अणु
	अणु
		I2C_BOARD_INFO("x1205", 0x6f),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led nslu2_led_pins[] = अणु
	अणु
		.name		= "nslu2:green:ready",
		.gpio		= NSLU2_LED_GRN_GPIO,
	पूर्ण,
	अणु
		.name		= "nslu2:red:status",
		.gpio		= NSLU2_LED_RED_GPIO,
	पूर्ण,
	अणु
		.name		= "nslu2:green:disk-1",
		.gpio		= NSLU2_LED_DISK1_GPIO,
		.active_low	= true,
	पूर्ण,
	अणु
		.name		= "nslu2:green:disk-2",
		.gpio		= NSLU2_LED_DISK2_GPIO,
		.active_low	= true,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data nslu2_led_data = अणु
	.num_leds		= ARRAY_SIZE(nslu2_led_pins),
	.leds			= nslu2_led_pins,
पूर्ण;

अटल काष्ठा platक्रमm_device nslu2_leds = अणु
	.name			= "leds-gpio",
	.id			= -1,
	.dev.platक्रमm_data	= &nslu2_led_data,
पूर्ण;

अटल काष्ठा platक्रमm_device nslu2_i2c_gpio = अणु
	.name			= "i2c-gpio",
	.id			= 0,
	.dev	 = अणु
		.platक्रमm_data	= शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource nslu2_beeper_resources[] = अणु
	अणु
		.start	= IRQ_IXP4XX_TIMER2,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device nslu2_beeper = अणु
	.name			= "ixp4xx-beeper",
	.id			= NSLU2_GPIO_BUZZ,
	.resource		= nslu2_beeper_resources,
	.num_resources		= ARRAY_SIZE(nslu2_beeper_resources),
पूर्ण;

अटल काष्ठा resource nslu2_uart_resources[] = अणु
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

अटल काष्ठा plat_serial8250_port nslu2_uart_data[] = अणु
	अणु
		.mapbase	= IXP4XX_UART1_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART1_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART1,
		.flags		= UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	अणु
		.mapbase	= IXP4XX_UART2_BASE_PHYS,
		.membase	= (अक्षर *)IXP4XX_UART2_BASE_VIRT + REG_OFFSET,
		.irq		= IRQ_IXP4XX_UART2,
		.flags		= UPF_BOOT_AUTOCONF,
		.iotype		= UPIO_MEM,
		.regshअगरt	= 2,
		.uartclk	= IXP4XX_UART_XTAL,
	पूर्ण,
	अणु पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device nslu2_uart = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev.platक्रमm_data	= nslu2_uart_data,
	.num_resources		= 2,
	.resource		= nslu2_uart_resources,
पूर्ण;

/* Built-in 10/100 Ethernet MAC पूर्णांकerfaces */
अटल काष्ठा resource nslu2_eth_resources[] = अणु
	अणु
		.start		= IXP4XX_EthB_BASE_PHYS,
		.end		= IXP4XX_EthB_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा eth_plat_info nslu2_plat_eth[] = अणु
	अणु
		.phy		= 1,
		.rxq		= 3,
		.txपढ़ोyq	= 20,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device nslu2_eth[] = अणु
	अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEB,
		.dev.platक्रमm_data	= nslu2_plat_eth,
		.num_resources		= ARRAY_SIZE(nslu2_eth_resources),
		.resource		= nslu2_eth_resources,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *nslu2_devices[] __initdata = अणु
	&nslu2_i2c_gpio,
	&nslu2_flash,
	&nslu2_beeper,
	&nslu2_leds,
	&nslu2_eth[0],
पूर्ण;

अटल व्योम nslu2_घातer_off(व्योम)
अणु
	/* This causes the box to drop the घातer and go dead. */

	/* enable the pwr cntl gpio and निश्चित घातer off */
	gpio_direction_output(NSLU2_PO_GPIO, 1);
पूर्ण

अटल irqवापस_t nslu2_घातer_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	/* Signal init to करो the ctrlaltdel action, this will bypass init अगर
	 * it hasn't started and करो a kernel_restart.
	 */
	ctrl_alt_del();

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t nslu2_reset_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	/* This is the paper-clip reset, it shuts the machine करोwn directly.
	 */
	machine_घातer_off();

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init nslu2_gpio_init(व्योम)
अणु
	अगर (!machine_is_nslu2())
		वापस 0;

	/* Request the घातer off GPIO */
	वापस gpio_request(NSLU2_PO_GPIO, "power off");
पूर्ण
device_initcall(nslu2_gpio_init);

अटल व्योम __init nslu2_समयr_init(व्योम)
अणु
    /* The xtal on this machine is non-standard. */
    ixp4xx_समयr_freq = NSLU2_FREQ;

    /* Call standard समयr_init function. */
    ixp4xx_समयr_init();
पूर्ण

अटल व्योम __init nslu2_init(व्योम)
अणु
	uपूर्णांक8_t __iomem *f;
	पूर्णांक i;

	ixp4xx_sys_init();

	nslu2_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	nslu2_flash_resource.end =
		IXP4XX_EXP_BUS_BASE(0) + ixp4xx_exp_bus_size - 1;

	gpiod_add_lookup_table(&nslu2_i2c_gpiod_table);
	i2c_रेजिस्टर_board_info(0, nslu2_i2c_board_info,
				ARRAY_SIZE(nslu2_i2c_board_info));

	/*
	 * This is only useful on a modअगरied machine, but it is valuable
	 * to have it first in order to see debug messages, and so that
	 * it करोes *not* get हटाओd अगर platक्रमm_add_devices fails!
	 */
	(व्योम)platक्रमm_device_रेजिस्टर(&nslu2_uart);

	platक्रमm_add_devices(nslu2_devices, ARRAY_SIZE(nslu2_devices));

	pm_घातer_off = nslu2_घातer_off;

	अगर (request_irq(gpio_to_irq(NSLU2_RB_GPIO), &nslu2_reset_handler,
		IRQF_TRIGGER_LOW, "NSLU2 reset button", शून्य) < 0) अणु

		prपूर्णांकk(KERN_DEBUG "Reset Button IRQ %d not available\n",
			gpio_to_irq(NSLU2_RB_GPIO));
	पूर्ण

	अगर (request_irq(gpio_to_irq(NSLU2_PB_GPIO), &nslu2_घातer_handler,
		IRQF_TRIGGER_HIGH, "NSLU2 power button", शून्य) < 0) अणु

		prपूर्णांकk(KERN_DEBUG "Power Button IRQ %d not available\n",
			gpio_to_irq(NSLU2_PB_GPIO));
	पूर्ण

	/*
	 * Map in a portion of the flash and पढ़ो the MAC address.
	 * Since it is stored in BE in the flash itself, we need to
	 * byteswap it अगर we're in LE mode.
	 */
	f = ioremap(IXP4XX_EXP_BUS_BASE(0), 0x40000);
	अगर (f) अणु
		क्रम (i = 0; i < 6; i++)
#अगर_घोषित __ARMEB__
			nslu2_plat_eth[0].hwaddr[i] = पढ़ोb(f + 0x3FFB0 + i);
#अन्यथा
			nslu2_plat_eth[0].hwaddr[i] = पढ़ोb(f + 0x3FFB0 + (i^3));
#पूर्ण_अगर
		iounmap(f);
	पूर्ण
	prपूर्णांकk(KERN_INFO "NSLU2: Using MAC address %pM for port 0\n",
	       nslu2_plat_eth[0].hwaddr);

पूर्ण

MACHINE_START(NSLU2, "Linksys NSLU2")
	/* Maपूर्णांकainer: www.nslu2-linux.org */
	.atag_offset	= 0x100,
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= nslu2_समयr_init,
	.init_machine	= nslu2_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
