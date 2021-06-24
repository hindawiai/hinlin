<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * DSM-G600 board-setup
 *
 * Copyright (C) 2008 Rod Whitby <rod@whitby.id.au>
 * Copyright (C) 2006 Tower Technologies
 *
 * based on ixdp425-setup.c:
 *      Copyright (C) 2003-2004 MontaVista Software, Inc.
 * based on nslu2-घातer.c:
 *	Copyright (C) 2005 Tower Technologies
 * based on nslu2-io.c:
 *	Copyright (C) 2004 Karen Spearel
 *
 * Author: Alessandro Zummo <a.zummo@towertech.it>
 * Author: Michael Westerhof <mwester@dls.net>
 * Author: Rod Whitby <rod@whitby.id.au>
 * Maपूर्णांकainers: http://www.nslu2-linux.org/
 */
#समावेश <linux/gpपन.स>
#समावेश <linux/irq.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/समयr.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/leds.h>
#समावेश <linux/reboot.h>
#समावेश <linux/i2c.h>
#समावेश <linux/gpio/machine.h>

#समावेश <mach/hardware.h>

#समावेश <यंत्र/mach-types.h>
#समावेश <यंत्र/mach/arch.h>
#समावेश <यंत्र/mach/flash.h>
#समावेश <यंत्र/mach/समय.स>

#समावेश "irqs.h"

#घोषणा DSMG600_SDA_PIN		5
#घोषणा DSMG600_SCL_PIN		4

/* DSM-G600 Timer Setting */
#घोषणा DSMG600_FREQ		66000000

/* Buttons */
#घोषणा DSMG600_PB_GPIO		15	/* घातer button */
#घोषणा DSMG600_RB_GPIO		3	/* reset button */

/* Power control */
#घोषणा DSMG600_PO_GPIO		2	/* घातer off */

/* LEDs */
#घोषणा DSMG600_LED_PWR_GPIO	0
#घोषणा DSMG600_LED_WLAN_GPIO	14

अटल काष्ठा flash_platक्रमm_data dsmg600_flash_data = अणु
	.map_name		= "cfi_probe",
	.width			= 2,
पूर्ण;

अटल काष्ठा resource dsmg600_flash_resource = अणु
	.flags			= IORESOURCE_MEM,
पूर्ण;

अटल काष्ठा platक्रमm_device dsmg600_flash = अणु
	.name			= "IXP4XX-Flash",
	.id			= 0,
	.dev.platक्रमm_data	= &dsmg600_flash_data,
	.num_resources		= 1,
	.resource		= &dsmg600_flash_resource,
पूर्ण;

अटल काष्ठा gpiod_lookup_table dsmg600_i2c_gpiod_table = अणु
	.dev_id		= "i2c-gpio.0",
	.table		= अणु
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", DSMG600_SDA_PIN,
				शून्य, 0, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
		GPIO_LOOKUP_IDX("IXP4XX_GPIO_CHIP", DSMG600_SCL_PIN,
				शून्य, 1, GPIO_ACTIVE_HIGH | GPIO_OPEN_DRAIN),
	पूर्ण,
पूर्ण;

अटल काष्ठा platक्रमm_device dsmg600_i2c_gpio = अणु
	.name			= "i2c-gpio",
	.id			= 0,
	.dev	 = अणु
		.platक्रमm_data	= शून्य,
	पूर्ण,
पूर्ण;

अटल काष्ठा i2c_board_info __initdata dsmg600_i2c_board_info [] = अणु
	अणु
		I2C_BOARD_INFO("pcf8563", 0x51),
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led dsmg600_led_pins[] = अणु
	अणु
		.name		= "dsmg600:green:power",
		.gpio		= DSMG600_LED_PWR_GPIO,
	पूर्ण,
	अणु
		.name		= "dsmg600:green:wlan",
		.gpio		= DSMG600_LED_WLAN_GPIO,
		.active_low	= true,
	पूर्ण,
पूर्ण;

अटल काष्ठा gpio_led_platक्रमm_data dsmg600_led_data = अणु
	.num_leds		= ARRAY_SIZE(dsmg600_led_pins),
	.leds			= dsmg600_led_pins,
पूर्ण;

अटल काष्ठा platक्रमm_device dsmg600_leds = अणु
	.name			= "leds-gpio",
	.id			= -1,
	.dev.platक्रमm_data	= &dsmg600_led_data,
पूर्ण;

अटल काष्ठा resource dsmg600_uart_resources[] = अणु
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

अटल काष्ठा plat_serial8250_port dsmg600_uart_data[] = अणु
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

अटल काष्ठा platक्रमm_device dsmg600_uart = अणु
	.name			= "serial8250",
	.id			= PLAT8250_DEV_PLATFORM,
	.dev.platक्रमm_data	= dsmg600_uart_data,
	.num_resources		= ARRAY_SIZE(dsmg600_uart_resources),
	.resource		= dsmg600_uart_resources,
पूर्ण;

अटल काष्ठा platक्रमm_device *dsmg600_devices[] __initdata = अणु
	&dsmg600_i2c_gpio,
	&dsmg600_flash,
	&dsmg600_leds,
पूर्ण;

अटल व्योम dsmg600_घातer_off(व्योम)
अणु
	/* enable the pwr cntl and drive it high */
	gpio_direction_output(DSMG600_PO_GPIO, 1);
पूर्ण

/* This is used to make sure the घातer-button pusher is serious.  The button
 * must be held until the value of this counter reaches zero.
 */
अटल पूर्णांक घातer_button_countकरोwn;

/* Must hold the button करोwn क्रम at least this many counts to be processed */
#घोषणा PBUTTON_HOLDDOWN_COUNT 4 /* 2 secs */

अटल व्योम dsmg600_घातer_handler(काष्ठा समयr_list *unused);
अटल DEFINE_TIMER(dsmg600_घातer_समयr, dsmg600_घातer_handler);

अटल व्योम dsmg600_घातer_handler(काष्ठा समयr_list *unused)
अणु
	/* This routine is called twice per second to check the
	 * state of the घातer button.
	 */

	अगर (gpio_get_value(DSMG600_PB_GPIO)) अणु

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
			gpio_set_value(DSMG600_LED_PWR_GPIO, 0);
		पूर्ण अन्यथा अणु
			घातer_button_countकरोwn = PBUTTON_HOLDDOWN_COUNT;
		पूर्ण
	पूर्ण

	mod_समयr(&dsmg600_घातer_समयr, jअगरfies + msecs_to_jअगरfies(500));
पूर्ण

अटल irqवापस_t dsmg600_reset_handler(पूर्णांक irq, व्योम *dev_id)
अणु
	/* This is the paper-clip reset, it shuts the machine करोwn directly. */
	machine_घातer_off();

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम __init dsmg600_समयr_init(व्योम)
अणु
    /* The xtal on this machine is non-standard. */
    ixp4xx_समयr_freq = DSMG600_FREQ;

    /* Call standard समयr_init function. */
    ixp4xx_समयr_init();
पूर्ण

अटल पूर्णांक __init dsmg600_gpio_init(व्योम)
अणु
	अगर (!machine_is_dsmg600())
		वापस 0;

	gpio_request(DSMG600_RB_GPIO, "reset button");
	अगर (request_irq(gpio_to_irq(DSMG600_RB_GPIO), &dsmg600_reset_handler,
		IRQF_TRIGGER_LOW, "DSM-G600 reset button", शून्य) < 0) अणु

		prपूर्णांकk(KERN_DEBUG "Reset Button IRQ %d not available\n",
			gpio_to_irq(DSMG600_RB_GPIO));
	पूर्ण

	/*
	 * The घातer button on the D-Link DSM-G600 is on GPIO 15, but
	 * it cannot handle पूर्णांकerrupts on that GPIO line.  So we'll
	 * have to poll it with a kernel समयr.
	 */

	/* Make sure that the घातer button GPIO is set up as an input */
	gpio_request(DSMG600_PB_GPIO, "power button");
	gpio_direction_input(DSMG600_PB_GPIO);
	/* Request घातeroff GPIO line */
	gpio_request(DSMG600_PO_GPIO, "power off button");

	/* Set the initial value क्रम the घातer button IRQ handler */
	घातer_button_countकरोwn = PBUTTON_HOLDDOWN_COUNT;

	mod_समयr(&dsmg600_घातer_समयr, jअगरfies + msecs_to_jअगरfies(500));
	वापस 0;
पूर्ण
device_initcall(dsmg600_gpio_init);

अटल व्योम __init dsmg600_init(व्योम)
अणु
	ixp4xx_sys_init();

	dsmg600_flash_resource.start = IXP4XX_EXP_BUS_BASE(0);
	dsmg600_flash_resource.end =
		IXP4XX_EXP_BUS_BASE(0) + ixp4xx_exp_bus_size - 1;

	gpiod_add_lookup_table(&dsmg600_i2c_gpiod_table);
	i2c_रेजिस्टर_board_info(0, dsmg600_i2c_board_info,
				ARRAY_SIZE(dsmg600_i2c_board_info));

	/* The UART is required on the DSM-G600 (Redboot cannot use the
	 * NIC) -- करो it here so that it करोes *not* get हटाओd अगर
	 * platक्रमm_add_devices fails!
         */
        (व्योम)platक्रमm_device_रेजिस्टर(&dsmg600_uart);

	platक्रमm_add_devices(dsmg600_devices, ARRAY_SIZE(dsmg600_devices));

	pm_घातer_off = dsmg600_घातer_off;
पूर्ण

MACHINE_START(DSMG600, "D-Link DSM-G600 RevA")
	/* Maपूर्णांकainer: www.nslu2-linux.org */
	.atag_offset	= 0x100,
	.map_io		= ixp4xx_map_io,
	.init_early	= ixp4xx_init_early,
	.init_irq	= ixp4xx_init_irq,
	.init_समय	= dsmg600_समयr_init,
	.init_machine	= dsmg600_init,
#अगर defined(CONFIG_PCI)
	.dma_zone_size	= SZ_64M,
#पूर्ण_अगर
	.restart	= ixp4xx_restart,
MACHINE_END
