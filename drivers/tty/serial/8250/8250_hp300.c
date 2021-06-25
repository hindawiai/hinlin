<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Driver क्रम the 98626/98644/पूर्णांकernal serial पूर्णांकerface on hp300/hp400
 * (based on the National Semiconductor INS8250/NS16550AF/WD16C552 UARTs)
 *
 * Ported from 2.2 and modअगरied to use the normal 8250 driver
 * by Kars de Jong <jongk@linux-m68k.org>, May 2004.
 */
#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/माला.स>
#समावेश <linux/kernel.h>
#समावेश <linux/serial.h>
#समावेश <linux/serial_8250.h>
#समावेश <linux/delay.h>
#समावेश <linux/dपन.स>
#समावेश <linux/console.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/पन.स>

#समावेश "8250.h"

#अगर !defined(CONFIG_HPDCA) && !defined(CONFIG_HPAPCI) && !defined(CONFIG_COMPILE_TEST)
#warning CONFIG_SERIAL_8250 defined but neither CONFIG_HPDCA nor CONFIG_HPAPCI defined, are you sure?
#पूर्ण_अगर

#अगर_घोषित CONFIG_HPAPCI
काष्ठा hp300_port अणु
	काष्ठा hp300_port *next;	/* next port */
	पूर्णांक line;			/* line (tty) number */
पूर्ण;

अटल काष्ठा hp300_port *hp300_ports;
#पूर्ण_अगर

#अगर_घोषित CONFIG_HPDCA

अटल पूर्णांक hpdca_init_one(काष्ठा dio_dev *d,
					स्थिर काष्ठा dio_device_id *ent);
अटल व्योम hpdca_हटाओ_one(काष्ठा dio_dev *d);

अटल काष्ठा dio_device_id hpdca_dio_tbl[] = अणु
	अणु DIO_ID_DCA0 पूर्ण,
	अणु DIO_ID_DCA0REM पूर्ण,
	अणु DIO_ID_DCA1 पूर्ण,
	अणु DIO_ID_DCA1REM पूर्ण,
	अणु 0 पूर्ण
पूर्ण;

अटल काष्ठा dio_driver hpdca_driver = अणु
	.name      = "hpdca",
	.id_table  = hpdca_dio_tbl,
	.probe     = hpdca_init_one,
	.हटाओ    = hpdca_हटाओ_one,
पूर्ण;

#पूर्ण_अगर

अटल अचिन्हित पूर्णांक num_ports;

बाह्य पूर्णांक hp300_uart_scode;

/* Offset to UART रेजिस्टरs from base of DCA */
#घोषणा UART_OFFSET	17

#घोषणा DCA_ID		0x01	/* ID (पढ़ो), reset (ग_लिखो) */
#घोषणा DCA_IC		0x03	/* Interrupt control        */

/* Interrupt control */
#घोषणा DCA_IC_IE	0x80	/* Master पूर्णांकerrupt enable  */

#घोषणा HPDCA_BAUD_BASE 153600

/* Base address of the Froकरो part */
#घोषणा FRODO_BASE	(0x41c000)

/*
 * Where we find the 8250-like APCI ports, and how far apart they are.
 */
#घोषणा FRODO_APCIBASE		0x0
#घोषणा FRODO_APCISPACE		0x20
#घोषणा FRODO_APCI_OFFSET(x)	(FRODO_APCIBASE + ((x) * FRODO_APCISPACE))

#घोषणा HPAPCI_BAUD_BASE 500400

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
/*
 * Parse the bootinfo to find descriptions क्रम headless console and
 * debug serial ports and रेजिस्टर them with the 8250 driver.
 */
पूर्णांक __init hp300_setup_serial_console(व्योम)
अणु
	पूर्णांक scode;
	काष्ठा uart_port port;

	स_रखो(&port, 0, माप(port));

	अगर (hp300_uart_scode < 0 || hp300_uart_scode > DIO_SCMAX)
		वापस 0;

	अगर (DIO_SCINHOLE(hp300_uart_scode))
		वापस 0;

	scode = hp300_uart_scode;

	/* Memory mapped I/O */
	port.iotype = UPIO_MEM;
	port.flags = UPF_SKIP_TEST | UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF;
	port.type = PORT_UNKNOWN;

	/* Check क्रम APCI console */
	अगर (scode == 256) अणु
#अगर_घोषित CONFIG_HPAPCI
		pr_info("Serial console is HP APCI 1\n");

		port.uartclk = HPAPCI_BAUD_BASE * 16;
		port.mapbase = (FRODO_BASE + FRODO_APCI_OFFSET(1));
		port.membase = (अक्षर *)(port.mapbase + DIO_VIRADDRBASE);
		port.regshअगरt = 2;
		add_preferred_console("ttyS", port.line, "9600n8");
#अन्यथा
		pr_warn("Serial console is APCI but support is disabled (CONFIG_HPAPCI)!\n");
		वापस 0;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
#अगर_घोषित CONFIG_HPDCA
		अचिन्हित दीर्घ pa = dio_scodetophysaddr(scode);
		अगर (!pa)
			वापस 0;

		pr_info("Serial console is HP DCA at select code %d\n", scode);

		port.uartclk = HPDCA_BAUD_BASE * 16;
		port.mapbase = (pa + UART_OFFSET);
		port.membase = (अक्षर *)(port.mapbase + DIO_VIRADDRBASE);
		port.regshअगरt = 1;
		port.irq = DIO_IPL(pa + DIO_VIRADDRBASE);

		/* Enable board-पूर्णांकerrupts */
		out_8(pa + DIO_VIRADDRBASE + DCA_IC, DCA_IC_IE);

		अगर (DIO_ID(pa + DIO_VIRADDRBASE) & 0x80)
			add_preferred_console("ttyS", port.line, "9600n8");
#अन्यथा
		pr_warn("Serial console is DCA but support is disabled (CONFIG_HPDCA)!\n");
		वापस 0;
#पूर्ण_अगर
	पूर्ण

	अगर (early_serial_setup(&port) < 0)
		pr_warn("%s: early_serial_setup() failed.\n", __func__);
	वापस 0;
पूर्ण
#पूर्ण_अगर /* CONFIG_SERIAL_8250_CONSOLE */

#अगर_घोषित CONFIG_HPDCA
अटल पूर्णांक hpdca_init_one(काष्ठा dio_dev *d,
				स्थिर काष्ठा dio_device_id *ent)
अणु
	काष्ठा uart_8250_port uart;
	पूर्णांक line;

#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
	अगर (hp300_uart_scode == d->scode) अणु
		/* Alपढ़ोy got it. */
		वापस 0;
	पूर्ण
#पूर्ण_अगर
	स_रखो(&uart, 0, माप(uart));

	/* Memory mapped I/O */
	uart.port.iotype = UPIO_MEM;
	uart.port.flags = UPF_SKIP_TEST | UPF_SHARE_IRQ | UPF_BOOT_AUTOCONF;
	uart.port.irq = d->ipl;
	uart.port.uartclk = HPDCA_BAUD_BASE * 16;
	uart.port.mapbase = (d->resource.start + UART_OFFSET);
	uart.port.membase = (अक्षर *)(uart.port.mapbase + DIO_VIRADDRBASE);
	uart.port.regshअगरt = 1;
	uart.port.dev = &d->dev;
	line = serial8250_रेजिस्टर_8250_port(&uart);

	अगर (line < 0) अणु
		dev_notice(&d->dev,
			  "8250_hp300: register_serial() DCA scode %d irq %d failed\n",
			  d->scode, uart.port.irq);
		वापस -ENOMEM;
	पूर्ण

	/* Enable board-पूर्णांकerrupts */
	out_8(d->resource.start + DIO_VIRADDRBASE + DCA_IC, DCA_IC_IE);
	dio_set_drvdata(d, (व्योम *)line);

	/* Reset the DCA */
	out_8(d->resource.start + DIO_VIRADDRBASE + DCA_ID, 0xff);
	udelay(100);

	num_ports++;

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक __init hp300_8250_init(व्योम)
अणु
	अटल पूर्णांक called;
#अगर_घोषित CONFIG_HPAPCI
	पूर्णांक line;
	अचिन्हित दीर्घ base;
	काष्ठा uart_8250_port uart;
	काष्ठा hp300_port *port;
	पूर्णांक i;
#पूर्ण_अगर
	अगर (called)
		वापस -ENODEV;
	called = 1;

	अगर (!MACH_IS_HP300)
		वापस -ENODEV;

#अगर_घोषित CONFIG_HPDCA
	dio_रेजिस्टर_driver(&hpdca_driver);
#पूर्ण_अगर
#अगर_घोषित CONFIG_HPAPCI
	अगर (hp300_model < HP_400) अणु
		अगर (!num_ports)
			वापस -ENODEV;
		वापस 0;
	पूर्ण
	/* These models have the Froकरो chip.
	 * Port 0 is reserved क्रम the Apollo Doमुख्य keyboard.
	 * Port 1 is either the console or the DCA.
	 */
	क्रम (i = 1; i < 4; i++) अणु
		/* Port 1 is the console on a 425e, on other machines it's
		 * mapped to DCA.
		 */
#अगर_घोषित CONFIG_SERIAL_8250_CONSOLE
		अगर (i == 1)
			जारी;
#पूर्ण_अगर

		/* Create new serial device */
		port = kदो_स्मृति(माप(काष्ठा hp300_port), GFP_KERNEL);
		अगर (!port)
			वापस -ENOMEM;

		स_रखो(&uart, 0, माप(uart));

		base = (FRODO_BASE + FRODO_APCI_OFFSET(i));

		/* Memory mapped I/O */
		uart.port.iotype = UPIO_MEM;
		uart.port.flags = UPF_SKIP_TEST | UPF_SHARE_IRQ
				| UPF_BOOT_AUTOCONF;
		/* XXX - no पूर्णांकerrupt support yet */
		uart.port.irq = 0;
		uart.port.uartclk = HPAPCI_BAUD_BASE * 16;
		uart.port.mapbase = base;
		uart.port.membase = (अक्षर *)(base + DIO_VIRADDRBASE);
		uart.port.regshअगरt = 2;

		line = serial8250_रेजिस्टर_8250_port(&uart);

		अगर (line < 0) अणु
			dev_notice(uart.port.dev,
				   "8250_hp300: register_serial() APCI %d irq %d failed\n",
				   i, uart.port.irq);
			kमुक्त(port);
			जारी;
		पूर्ण

		port->line = line;
		port->next = hp300_ports;
		hp300_ports = port;

		num_ports++;
	पूर्ण
#पूर्ण_अगर

	/* Any boards found? */
	अगर (!num_ports)
		वापस -ENODEV;

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_HPDCA
अटल व्योम hpdca_हटाओ_one(काष्ठा dio_dev *d)
अणु
	पूर्णांक line;

	line = (पूर्णांक) dio_get_drvdata(d);
	अगर (d->resource.start) अणु
		/* Disable board-पूर्णांकerrupts */
		out_8(d->resource.start + DIO_VIRADDRBASE + DCA_IC, 0);
	पूर्ण
	serial8250_unरेजिस्टर_port(line);
पूर्ण
#पूर्ण_अगर

अटल व्योम __निकास hp300_8250_निकास(व्योम)
अणु
#अगर_घोषित CONFIG_HPAPCI
	काष्ठा hp300_port *port, *to_मुक्त;

	क्रम (port = hp300_ports; port; ) अणु
		serial8250_unरेजिस्टर_port(port->line);
		to_मुक्त = port;
		port = port->next;
		kमुक्त(to_मुक्त);
	पूर्ण

	hp300_ports = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_HPDCA
	dio_unरेजिस्टर_driver(&hpdca_driver);
#पूर्ण_अगर
पूर्ण

module_init(hp300_8250_init);
module_निकास(hp300_8250_निकास);
MODULE_DESCRIPTION("HP DCA/APCI serial driver");
MODULE_AUTHOR("Kars de Jong <jongk@linux-m68k.org>");
MODULE_LICENSE("GPL");
