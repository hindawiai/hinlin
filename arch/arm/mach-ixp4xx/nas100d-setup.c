<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/arm/mach-ixp4xx/nas100d-setup.c
 *
 * NAS 100d board-setup
 *
 * Copyright (C) 2008 Rod Whitby <rod@whitby.id.au>
 *
 * based on ixdp425-setup.c:
 *      Copyright (C) 2003-2004 MontaVista Software, Inc.
 * based on nas100d-घातer.c:
 *	Copyright (C) 2005 Tower Technologies
 * based on nas100d-io.c
 *	Copyright (C) 2004 Karen Spearel
 *
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 * Author: Rod Whitby <rod@whitby.id.au>
 * Maपूर्णांकainers: http://www.nslu2-linux.org/
 *
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/irq.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
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

#घोषणा NAS100D_SDA_PIN		5
#घोषणा NAS100D_SCL_PIN		6

/* Buttons */
#घोषणा NAS100D_PB_GPIO         14   /* घातer button */
#घोषणा NAS100D_RB_GPIO         4    /* reset button */

/* Power control */
#घोषणा NAS100D_PO_GPIO         12   /* घातer off */

/* LEDs */
#घोषणा NAS100D_LED_WLAN_GPIO	0
#घोषणा NAS100D_LED_DISK_GPIO	3
#घोषणा NAS100D_LED_PWR_GPIO	15

अटल काष्ठा flash_platक्रमm_data nas100d_flash_data = अणु
	.map_name		= "cfi_probe",
	.width			= 2,
पूर्ण;

अटल काष्ठा resource nas100d_flash_resource = अणु
	.flags			= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device nas100d_flash = अणु
	.name			= "IXP4XX-Flash",
	.id			= 0,
	.dev.platक्रमm_data	= &nas100d_flash_data,
	.num_resources		= 1,
	.resource		= &nas100d_flash_resource,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata nas100d_i2c_board_info [] = अणु
	अणु
		I2C_BOARD_INFO("pcf8563", 0x51),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led nas100d_led_pins[] = अणु
	अणु
		.name		= "nas100d:green:wlan",
		.gpio		= NAS100D_LED_WLAN_GPIO,
		.active_low	= true,
	पूर्ण,
	अणु
		.name		= "nas100d:blue:power",  /* (off=flashing) */
		.gpio		= NAS100D_LED_PWR_GPIO,
		.active_low	= true,
	पूर्ण,
	अणु
		.name		= "nas100d:yellow:disk",
		.gpio		= NAS100D_LED_DISK_GPIO,
		.active_low	= true,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data nas100d_led_data = अणु
	.num_leds		= ARRAY_SIZE(nas100d_led_pins),
	.leds			= nas100d_led_pins,
पूर्ण;

अटल काष्ठा platक्रमm_device nas100d_leds = अणु
	.name			= "leds-gpio",
	.id			= -1,
	.dev.platक्रमm_data	= &nas100d_led_data,
पूर्ण;

अटल काष्ठा gpiod_lookup_table nas100d_i2c_gpiod_table = अणु
	.dev_id		= "i2c-gpio.0",
	.table		= अणु
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", NAS100D_SDA_PIN,
				शून्य, 0, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", NAS100D_SCL_PIN,
				शून्य, 1, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device nas100d_i2c_gpio = अणु
	.name			= "i2c-gpio",
	.id			= 0,
	.dev	 = अणु
		.platक्रमm_data	= शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा resource nas100d_uart_resources[] = अणु
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

अटल काष्ठा plat_serial8250_port nas100d_uart_data[] = अणु
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

अटल काष्ठा platक्रमm_device nas100d_uart = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev.platक्रमm_data	= nas100d_uart_data,
	.num_resources		= 2,
	.resource		= nas100d_uart_resources,
पूर्ण;

/* Built-in 10/100 Ethernet MAC पूर्णांकerfaces */
अटल काष्ठा resource nas100d_eth_resources[] = अणु
	अणु
		.start		= IXP4XX_EthB_BASE_PHYS,
		.end		= IXP4XX_EthB_BASE_PHYS + 0x0fff,
		.flags		= IORESOURCE_MEM,
	पूर्ण,
पूर्ण;

अटल काष्ठा eth_plat_info nas100d_plat_eth[] = अणु
	अणु
		.phy		= 0,
		.rxq		= 3,
		.txपढ़ोyq	= 20,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device nas100d_eth[] = अणु
	अणु
		.name			= "ixp4xx_eth",
		.id			= IXP4XX_ETH_NPEB,
		.dev.platक्रमm_data	= nas100d_plat_eth,
		.num_resources		= ARRAY_SIZE(nas100d_eth_resources),
		.resource		= nas100d_eth_resources,
	पूर्ण
पूर्ण;

अटल काष्ठा platक्रमm_device *nas100d_devices[] __initdata = अणु
	&nas100d_i2c_gpio,
	&nas100d_flash,
	&nas100d_leds,
	&nas100d_eth[0],
पूर्ण;

अटल व्योम nas100d_घातer_off(व्योम)
अणु
	/* This causes the box to drop the घातer and go dead. */

	/* enable the pwr cntl gpio and निश्चित घातer off */
	gpio_direction_output(NAS100D_PO_GPIO, 1);
पूर्ण

/* This is used to make sure the घातer-button pusher is serious.  The button
 * must be held until the value of this counter reaches zero.
 */
अटल पूर्णांक घातer_button_countकरोwn;

/* Must hold the button करोwn क्रम at least this many counts to be processed */
#घोषणा PBUTTON_HOLDDOWN_COUNT 4 /* 2 secs */

अटल व्योम nas100d_घातer_handler(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(nas100d_घातer_समयr, nas100d_घातer_handler);

अटल व्योम nas100d_घातer_handler(काष्ठा समयr_list *unused)
अणु
	/* This routine is called twice per second to check the
	 * state of the घातer button.
	 */

	अगर (gpio_get_value(NAS100D_PB_GPIO)) अणु

		/* IO Pin is 1 (button pushed) */
		अगर (घातer_button_countकरोwn > 0)
			घातer_button_countकरोwn--;

	पूर्ण अन्यथा अणु

		/* Done on button release, to allow क्रम स्वतः-घातer-on mods. */
		अगर (घातer_button_countकरोwn == 0) अणु
			/* Signal init to करो the ctrlaltdel action,
			 * this will bypass init अगर it hasn't started
			 * and करो a kernel_restart.
			 */
			ctrl_alt_del();

			/* Change the state of the घातer LED to "blink" */
			gpio_set_value(NAS100D_LED_PWR_GPIO, 0);
		पूर्ण अन्यथा अणु
			घातer_button_countकरोwn = PBUTTON_HOLDDOWN_COUNT;
		पूर्ण
	पूर्ण

	mod_समयr(&nas100d_घातer_समयr, jअगरfies + msecs_to_jअगरfies(500));
पूर्ण

अटल irqवापस_t nas100d_reset_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	/* This is the paper-clip reset, it shuts the machine करोwn directly. */
	machine_घातer_off();

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक __init nas100d_gpio_init(व्योम)
अणु
	अगर (!machine_is_nas100d())
		वापस 0;

	/*
	 * The घातer button on the Iomega NAS100d is on GPIO 14, but
	 * it cannot handle पूर्णांकerrupts on that GPIO line.  So we'll
	 * have to poll it with a kernel समयr.
	 */

	/* Request the घातer off GPIO */
	gpio_request(NAS100D_PO_GPIO, "power off");

	/* Make sure that the घातer button GPIO is set up as an input */
	gpio_request(NAS100D_PB_GPIO, "power button");
	gpio_direction_input(NAS100D_PB_GPIO);

	/* Set the initial value क्रम the घातer button IRQ handler */
	घातer_button_countकरोwn = PBUTTON_HOLDDOWN_COUNT;

	mod_समयr(&nas100d_घातer_समयr, jअगरfies + msecs_to_jअगरfies(500));

	वापस 0;
पूर्ण
device_initcall(nas100d_gpio_init);

अटल व्योम __init nas100d_init(व्योम)
अणु
	uपूर्णांक8_t __iomem *f;
	पूर्णांक i;

	ixp4xx_sys_init();

	nas100d_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	nas100d_flash_resource.end =
		IXP4XX_EXP_BUS_BASE(0) + ixp4xx_exp_bus_size - 1;

	gpiod_add_lookup_table(&nas100d_i2c_gpiod_table);
	i2c_रेजिस्टर_board_info(0, nas100d_i2c_board_info,
				ARRAY_SIZE(nas100d_i2c_board_info));

	/*
	 * This is only useful on a modअगरied machine, but it is valuable
	 * to have it first in order to see debug messages, and so that
	 * it करोes *not* get हटाओd अगर platक्रमm_add_devices fails!
	 */
	(व्योम)platक्रमm_device_रेजिस्टर(&nas100d_uart);

	platक्रमm_add_devices(nas100d_devices, ARRAY_SIZE(nas100d_devices));

	pm_घातer_off = nas100d_घातer_off;

	अगर (request_irq(gpio_to_irq(NAS100D_RB_GPIO), &nas100d_reset_handler,
		IRQF_TRIGGER_LOW, "NAS100D reset button", शून्य) < 0) अणु

		prपूर्णांकk(KERN_DEBUG "Reset Button IRQ %d not available\n",
			gpio_to_irq(NAS100D_RB_GPIO));
	पूर्ण

	/*
	 * Map in a portion of the flash and पढ़ो the MAC address.
	 * Since it is stored in BE in the flash itself, we need to
	 * byteswap it अगर we're in LE mode.
	 */
	f = ioremap(IXP4XX_EXP_BUS_BASE(0), 0x1000000);
	अगर (f) अणु
		क्रम (i = 0; i < 6; i++)
#अगर_घोषित __ARMEB__
			nas100d_plat_eth[0].hwaddr[i] = पढ़ोb(f + 0xFC0FD8 + i);
#अन्यथा
			nas100d_plat_eth[0].hwaddr[i] = पढ़ोb(f + 0xFC0FD8 + (i^3));
#पूर्ण_अगर
		iounmap(f);
	पूर्ण
	prपूर्णांकk(KERN_INFO "NAS100D: Using MAC address %pM for port 0\n",
	       nas100d_plat_eth[0].hwaddr);

पूर्ण

MACHINE_START(NAS100D, "Iomega NAS 100d")
	/* Maपूर्णांकainer: www.nslu2-linux.org */
	.atag_offset	= 0x100,
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= ixp4xx_समयr_init,
	.init_machine	= nas100d_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
