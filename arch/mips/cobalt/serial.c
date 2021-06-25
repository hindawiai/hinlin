<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Registration of Cobalt UART platक्रमm device.
 *
 *  Copyright (C) 2007  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/init.h>
#समावेश <linux/ioport.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/serial_8250.h>

#समावेश <cobalt.h>
#समावेश <irq.h>

अटल काष्ठा resource cobalt_uart_resource[] __initdata = अणु
	अणु
		.start	= 0x1c800000,
		.end	= 0x1c800007,
		.flags	= IORESOURCE_MEM,
	पूर्ण,
	अणु
		.start	= SERIAL_IRQ,
		.end	= SERIAL_IRQ,
		.flags	= IORESOURCE_IRQ,
	पूर्ण,
पूर्ण;

अटल काष्ठा plat_serial8250_port cobalt_serial8250_port[] = अणु
	अणु
		.irq		= SERIAL_IRQ,
		.uartclk	= 18432000,
		.iotype		= UPIO_MEM,
		.flags		= UPF_IOREMAP | UPF_BOOT_AUTOCONF | UPF_SKIP_TEST,
		.mapbase	= 0x1c800000,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल __init पूर्णांक cobalt_uart_add(व्योम)
अणु
	काष्ठा platक्रमm_device *pdev;
	पूर्णांक retval;

	/*
	 * Cobalt Qube1 has no UART.
	 */
	अगर (cobalt_board_id == COBALT_BRD_ID_QUBE1)
		वापस 0;

	pdev = platक्रमm_device_alloc("serial8250", -1);
	अगर (!pdev)
		वापस -ENOMEM;

	pdev->id = PLAT8250_DEV_PLATFORM;
	pdev->dev.platक्रमm_data = cobalt_serial8250_port;

	retval = platक्रमm_device_add_resources(pdev, cobalt_uart_resource, ARRAY_SIZE(cobalt_uart_resource));
	अगर (retval)
		जाओ err_मुक्त_device;

	retval = platक्रमm_device_add(pdev);
	अगर (retval)
		जाओ err_मुक्त_device;

	वापस 0;

err_मुक्त_device:
	platक्रमm_device_put(pdev);

	वापस retval;
पूर्ण
device_initcall(cobalt_uart_add);
