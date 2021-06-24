<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Early serial console क्रम 8250/16550 devices
 *
 * (c) Copyright 2004 Hewlett-Packard Development Company, L.P.
 *	Bjorn Helgaas <bjorn.helgaas@hp.com>
 *
 * Based on the 8250.c serial driver, Copyright (C) 2001 Russell King,
 * and on early_prपूर्णांकk.c by Andi Kleen.
 *
 * This is क्रम use beक्रमe the serial driver has initialized, in
 * particular, beक्रमe the UARTs have been discovered and named.
 * Instead of specअगरying the console device as, e.g., "ttyS0",
 * we locate the device directly by its MMIO or I/O port address.
 *
 * The user can specअगरy the device directly, e.g.,
 *	earlycon=uart8250,io,0x3f8,9600n8
 *	earlycon=uart8250,mmio,0xff5e0000,115200n8
 *	earlycon=uart8250,mmio32,0xff5e0000,115200n8
 * or
 *	console=uart8250,io,0x3f8,9600n8
 *	console=uart8250,mmio,0xff5e0000,115200n8
 *	console=uart8250,mmio32,0xff5e0000,115200n8
 */

#समावेश <linux/tty.h>
#समावेश <linux/init.h>
#समावेश <linux/console.h>
#समावेश <linux/of.h>
#समावेश <linux/of_device.h>
#समावेश <linux/serial_reg.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/serial.h>

अटल अचिन्हित पूर्णांक serial8250_early_in(काष्ठा uart_port *port, पूर्णांक offset)
अणु
	पूर्णांक reg_offset = offset;
	offset <<= port->regshअगरt;

	चयन (port->iotype) अणु
	हाल UPIO_MEM:
		वापस पढ़ोb(port->membase + offset);
	हाल UPIO_MEM16:
		वापस पढ़ोw(port->membase + offset);
	हाल UPIO_MEM32:
		वापस पढ़ोl(port->membase + offset);
	हाल UPIO_MEM32BE:
		वापस ioपढ़ो32be(port->membase + offset);
	हाल UPIO_PORT:
		वापस inb(port->iobase + offset);
	हाल UPIO_AU:
		वापस port->serial_in(port, reg_offset);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम serial8250_early_out(काष्ठा uart_port *port, पूर्णांक offset, पूर्णांक value)
अणु
	पूर्णांक reg_offset = offset;
	offset <<= port->regshअगरt;

	चयन (port->iotype) अणु
	हाल UPIO_MEM:
		ग_लिखोb(value, port->membase + offset);
		अवरोध;
	हाल UPIO_MEM16:
		ग_लिखोw(value, port->membase + offset);
		अवरोध;
	हाल UPIO_MEM32:
		ग_लिखोl(value, port->membase + offset);
		अवरोध;
	हाल UPIO_MEM32BE:
		ioग_लिखो32be(value, port->membase + offset);
		अवरोध;
	हाल UPIO_PORT:
		outb(value, port->iobase + offset);
		अवरोध;
	हाल UPIO_AU:
		port->serial_out(port, reg_offset, value);
		अवरोध;
	पूर्ण
पूर्ण

#घोषणा BOTH_EMPTY (UART_LSR_TEMT | UART_LSR_THRE)

अटल व्योम serial_अ_दो(काष्ठा uart_port *port, पूर्णांक c)
अणु
	अचिन्हित पूर्णांक status;

	serial8250_early_out(port, UART_TX, c);

	क्रम (;;) अणु
		status = serial8250_early_in(port, UART_LSR);
		अगर ((status & BOTH_EMPTY) == BOTH_EMPTY)
			अवरोध;
		cpu_relax();
	पूर्ण
पूर्ण

अटल व्योम early_serial8250_ग_लिखो(काष्ठा console *console,
					स्थिर अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा earlycon_device *device = console->data;
	काष्ठा uart_port *port = &device->port;

	uart_console_ग_लिखो(port, s, count, serial_अ_दो);
पूर्ण

#अगर_घोषित CONFIG_CONSOLE_POLL
अटल पूर्णांक early_serial8250_पढ़ो(काष्ठा console *console,
				 अक्षर *s, अचिन्हित पूर्णांक count)
अणु
	काष्ठा earlycon_device *device = console->data;
	काष्ठा uart_port *port = &device->port;
	अचिन्हित पूर्णांक status;
	पूर्णांक num_पढ़ो = 0;

	जबतक (num_पढ़ो < count) अणु
		status = serial8250_early_in(port, UART_LSR);
		अगर (!(status & UART_LSR_DR))
			अवरोध;
		s[num_पढ़ो++] = serial8250_early_in(port, UART_RX);
	पूर्ण

	वापस num_पढ़ो;
पूर्ण
#अन्यथा
#घोषणा early_serial8250_पढ़ो शून्य
#पूर्ण_अगर

अटल व्योम __init init_port(काष्ठा earlycon_device *device)
अणु
	काष्ठा uart_port *port = &device->port;
	अचिन्हित पूर्णांक भागisor;
	अचिन्हित अक्षर c;
	अचिन्हित पूर्णांक ier;

	serial8250_early_out(port, UART_LCR, 0x3);	/* 8n1 */
	ier = serial8250_early_in(port, UART_IER);
	serial8250_early_out(port, UART_IER, ier & UART_IER_UUE); /* no पूर्णांकerrupt */
	serial8250_early_out(port, UART_FCR, 0);	/* no fअगरo */
	serial8250_early_out(port, UART_MCR, 0x3);	/* DTR + RTS */

	अगर (port->uartclk) अणु
		भागisor = DIV_ROUND_CLOSEST(port->uartclk, 16 * device->baud);
		c = serial8250_early_in(port, UART_LCR);
		serial8250_early_out(port, UART_LCR, c | UART_LCR_DLAB);
		serial8250_early_out(port, UART_DLL, भागisor & 0xff);
		serial8250_early_out(port, UART_DLM, (भागisor >> 8) & 0xff);
		serial8250_early_out(port, UART_LCR, c & ~UART_LCR_DLAB);
	पूर्ण
पूर्ण

पूर्णांक __init early_serial8250_setup(काष्ठा earlycon_device *device,
					 स्थिर अक्षर *options)
अणु
	अगर (!(device->port.membase || device->port.iobase))
		वापस -ENODEV;

	अगर (!device->baud) अणु
		काष्ठा uart_port *port = &device->port;
		अचिन्हित पूर्णांक ier;

		/* assume the device was initialized, only mask पूर्णांकerrupts */
		ier = serial8250_early_in(port, UART_IER);
		serial8250_early_out(port, UART_IER, ier & UART_IER_UUE);
	पूर्ण अन्यथा
		init_port(device);

	device->con->ग_लिखो = early_serial8250_ग_लिखो;
	device->con->पढ़ो = early_serial8250_पढ़ो;
	वापस 0;
पूर्ण
EARLYCON_DECLARE(uart8250, early_serial8250_setup);
EARLYCON_DECLARE(uart, early_serial8250_setup);
OF_EARLYCON_DECLARE(ns16550, "ns16550", early_serial8250_setup);
OF_EARLYCON_DECLARE(ns16550a, "ns16550a", early_serial8250_setup);
OF_EARLYCON_DECLARE(uart, "nvidia,tegra20-uart", early_serial8250_setup);
OF_EARLYCON_DECLARE(uart, "snps,dw-apb-uart", early_serial8250_setup);

#अगर_घोषित CONFIG_SERIAL_8250_OMAP

अटल पूर्णांक __init early_omap8250_setup(काष्ठा earlycon_device *device,
				       स्थिर अक्षर *options)
अणु
	काष्ठा uart_port *port = &device->port;

	अगर (!(device->port.membase || device->port.iobase))
		वापस -ENODEV;

	port->regshअगरt = 2;
	device->con->ग_लिखो = early_serial8250_ग_लिखो;
	वापस 0;
पूर्ण

OF_EARLYCON_DECLARE(omap8250, "ti,omap2-uart", early_omap8250_setup);
OF_EARLYCON_DECLARE(omap8250, "ti,omap3-uart", early_omap8250_setup);
OF_EARLYCON_DECLARE(omap8250, "ti,omap4-uart", early_omap8250_setup);

#पूर्ण_अगर

#अगर_घोषित CONFIG_SERIAL_8250_RT288X

अटल पूर्णांक __init early_au_setup(काष्ठा earlycon_device *dev, स्थिर अक्षर *opt)
अणु
	dev->port.serial_in = au_serial_in;
	dev->port.serial_out = au_serial_out;
	dev->port.iotype = UPIO_AU;
	dev->con->ग_लिखो = early_serial8250_ग_लिखो;
	वापस 0;
पूर्ण
OF_EARLYCON_DECLARE(palmchip, "ralink,rt2880-uart", early_au_setup);

#पूर्ण_अगर
