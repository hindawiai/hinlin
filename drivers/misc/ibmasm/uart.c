<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later

/*
 * IBM ASM Service Processor Device Driver
 *
 * Copyright (C) IBM Corporation, 2004
 *
 * Author: Max Asbथघck <amax@us.ibm.com>
 */

#समावेश <linux/termios.h>
#समावेश <linux/tty.h>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial_8250.h>
#समावेश "ibmasm.h"
#समावेश "lowlevel.h"


व्योम ibmयंत्र_रेजिस्टर_uart(काष्ठा service_processor *sp)
अणु
	काष्ठा uart_8250_port uart;
	व्योम __iomem *iomem_base;

	iomem_base = sp->base_address + SCOUT_COM_B_BASE;

	/* पढ़ो the uart scratch रेजिस्टर to determine अगर the UART
	 * is dedicated to the service processor or अगर the OS can use it
	 */
	अगर (0 == पढ़ोl(iomem_base + UART_SCR)) अणु
		dev_info(sp->dev, "IBM SP UART not registered, owned by service processor\n");
		sp->serial_line = -1;
		वापस;
	पूर्ण

	स_रखो(&uart, 0, माप(uart));
	uart.port.irq		= sp->irq;
	uart.port.uartclk	= 3686400;
	uart.port.flags		= UPF_SHARE_IRQ;
	uart.port.iotype	= UPIO_MEM;
	uart.port.membase	= iomem_base;

	sp->serial_line = serial8250_रेजिस्टर_8250_port(&uart);
	अगर (sp->serial_line < 0) अणु
		dev_err(sp->dev, "Failed to register serial port\n");
		वापस;
	पूर्ण
	enable_uart_पूर्णांकerrupts(sp->base_address);
पूर्ण

व्योम ibmयंत्र_unरेजिस्टर_uart(काष्ठा service_processor *sp)
अणु
	अगर (sp->serial_line < 0)
		वापस;

	disable_uart_पूर्णांकerrupts(sp->base_address);
	serial8250_unरेजिस्टर_port(sp->serial_line);
पूर्ण
