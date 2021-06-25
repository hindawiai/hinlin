<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Serial port routines क्रम use during early boot reporting. This code is
 * included from both the compressed kernel and the regular kernel.
 */
#समावेश "boot.h"

#घोषणा DEFAULT_SERIAL_PORT 0x3f8 /* ttyS0 */

#घोषणा DLAB		0x80

#घोषणा TXR             0       /*  Transmit रेजिस्टर (WRITE) */
#घोषणा RXR             0       /*  Receive रेजिस्टर  (READ)  */
#घोषणा IER             1       /*  Interrupt Enable          */
#घोषणा IIR             2       /*  Interrupt ID              */
#घोषणा FCR             2       /*  FIFO control              */
#घोषणा LCR             3       /*  Line control              */
#घोषणा MCR             4       /*  Modem control             */
#घोषणा LSR             5       /*  Line Status               */
#घोषणा MSR             6       /*  Modem Status              */
#घोषणा DLL             0       /*  Divisor Latch Low         */
#घोषणा DLH             1       /*  Divisor latch High        */

#घोषणा DEFAULT_BAUD 9600

अटल व्योम early_serial_init(पूर्णांक port, पूर्णांक baud)
अणु
	अचिन्हित अक्षर c;
	अचिन्हित भागisor;

	outb(0x3, port + LCR);	/* 8n1 */
	outb(0, port + IER);	/* no पूर्णांकerrupt */
	outb(0, port + FCR);	/* no fअगरo */
	outb(0x3, port + MCR);	/* DTR + RTS */

	भागisor	= 115200 / baud;
	c = inb(port + LCR);
	outb(c | DLAB, port + LCR);
	outb(भागisor & 0xff, port + DLL);
	outb((भागisor >> 8) & 0xff, port + DLH);
	outb(c & ~DLAB, port + LCR);

	early_serial_base = port;
पूर्ण

अटल व्योम parse_earlyprपूर्णांकk(व्योम)
अणु
	पूर्णांक baud = DEFAULT_BAUD;
	अक्षर arg[32];
	पूर्णांक pos = 0;
	पूर्णांक port = 0;

	अगर (cmdline_find_option("earlyprintk", arg, माप(arg)) > 0) अणु
		अक्षर *e;

		अगर (!म_भेदन(arg, "serial", 6)) अणु
			port = DEFAULT_SERIAL_PORT;
			pos += 6;
		पूर्ण

		अगर (arg[pos] == ',')
			pos++;

		/*
		 * make sure we have
		 *	"serial,0x3f8,115200"
		 *	"serial,ttyS0,115200"
		 *	"ttyS0,115200"
		 */
		अगर (pos == 7 && !म_भेदन(arg + pos, "0x", 2)) अणु
			port = simple_म_से_अदीर्घl(arg + pos, &e, 16);
			अगर (port == 0 || arg + pos == e)
				port = DEFAULT_SERIAL_PORT;
			अन्यथा
				pos = e - arg;
		पूर्ण अन्यथा अगर (!म_भेदन(arg + pos, "ttyS", 4)) अणु
			अटल स्थिर पूर्णांक bases[] = अणु 0x3f8, 0x2f8 पूर्ण;
			पूर्णांक idx = 0;

			/* += म_माप("ttyS"); */
			pos += 4;

			अगर (arg[pos++] == '1')
				idx = 1;

			port = bases[idx];
		पूर्ण

		अगर (arg[pos] == ',')
			pos++;

		baud = simple_म_से_अदीर्घl(arg + pos, &e, 0);
		अगर (baud == 0 || arg + pos == e)
			baud = DEFAULT_BAUD;
	पूर्ण

	अगर (port)
		early_serial_init(port, baud);
पूर्ण

#घोषणा BASE_BAUD (1843200/16)
अटल अचिन्हित पूर्णांक probe_baud(पूर्णांक port)
अणु
	अचिन्हित अक्षर lcr, dll, dlh;
	अचिन्हित पूर्णांक quot;

	lcr = inb(port + LCR);
	outb(lcr | DLAB, port + LCR);
	dll = inb(port + DLL);
	dlh = inb(port + DLH);
	outb(lcr, port + LCR);
	quot = (dlh << 8) | dll;

	वापस BASE_BAUD / quot;
पूर्ण

अटल व्योम parse_console_uart8250(व्योम)
अणु
	अक्षर optstr[64], *options;
	पूर्णांक baud = DEFAULT_BAUD;
	पूर्णांक port = 0;

	/*
	 * console=uart8250,io,0x3f8,115200n8
	 * need to make sure it is last one console !
	 */
	अगर (cmdline_find_option("console", optstr, माप(optstr)) <= 0)
		वापस;

	options = optstr;

	अगर (!म_भेदन(options, "uart8250,io,", 12))
		port = simple_म_से_अदीर्घl(options + 12, &options, 0);
	अन्यथा अगर (!म_भेदन(options, "uart,io,", 8))
		port = simple_म_से_अदीर्घl(options + 8, &options, 0);
	अन्यथा
		वापस;

	अगर (options && (options[0] == ','))
		baud = simple_म_से_अदीर्घl(options + 1, &options, 0);
	अन्यथा
		baud = probe_baud(port);

	अगर (port)
		early_serial_init(port, baud);
पूर्ण

व्योम console_init(व्योम)
अणु
	parse_earlyprपूर्णांकk();

	अगर (!early_serial_base)
		parse_console_uart8250();
पूर्ण
