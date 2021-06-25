<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 2008-2010 Thomas Chou <thomas@wytron.com.tw>
 */

#समावेश <linux/पन.स>

#अगर (defined(CONFIG_SERIAL_ALTERA_JTAGUART_CONSOLE) && defined(JTAG_UART_BASE))\
	|| (defined(CONFIG_SERIAL_ALTERA_UART_CONSOLE) && defined(UART0_BASE))
अटल व्योम *my_ioremap(अचिन्हित दीर्घ physaddr)
अणु
	वापस (व्योम *)(physaddr | CONFIG_NIOS2_IO_REGION_BASE);
पूर्ण
#पूर्ण_अगर

#अगर defined(CONFIG_SERIAL_ALTERA_JTAGUART_CONSOLE) && defined(JTAG_UART_BASE)

#घोषणा ALTERA_JTAGUART_SIZE				8
#घोषणा ALTERA_JTAGUART_DATA_REG			0
#घोषणा ALTERA_JTAGUART_CONTROL_REG			4
#घोषणा ALTERA_JTAGUART_CONTROL_AC_MSK			(0x00000400)
#घोषणा ALTERA_JTAGUART_CONTROL_WSPACE_MSK		(0xFFFF0000)
अटल व्योम *uartbase;

#अगर defined(CONFIG_SERIAL_ALTERA_JTAGUART_CONSOLE_BYPASS)
अटल व्योम jtag_अ_दो(पूर्णांक ch)
अणु
	अगर (पढ़ोl(uartbase + ALTERA_JTAGUART_CONTROL_REG) &
		ALTERA_JTAGUART_CONTROL_WSPACE_MSK)
		ग_लिखोb(ch, uartbase + ALTERA_JTAGUART_DATA_REG);
पूर्ण
#अन्यथा
अटल व्योम jtag_अ_दो(पूर्णांक ch)
अणु
	जबतक ((पढ़ोl(uartbase + ALTERA_JTAGUART_CONTROL_REG) &
		ALTERA_JTAGUART_CONTROL_WSPACE_MSK) == 0)
		;
	ग_लिखोb(ch, uartbase + ALTERA_JTAGUART_DATA_REG);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक अक्षर_दो(पूर्णांक ch)
अणु
	jtag_अ_दो(ch);
	वापस ch;
पूर्ण

अटल व्योम console_init(व्योम)
अणु
	uartbase = my_ioremap((अचिन्हित दीर्घ) JTAG_UART_BASE);
	ग_लिखोl(ALTERA_JTAGUART_CONTROL_AC_MSK,
		uartbase + ALTERA_JTAGUART_CONTROL_REG);
पूर्ण

#या_अगर defined(CONFIG_SERIAL_ALTERA_UART_CONSOLE) && defined(UART0_BASE)

#घोषणा ALTERA_UART_SIZE		32
#घोषणा ALTERA_UART_TXDATA_REG		4
#घोषणा ALTERA_UART_STATUS_REG		8
#घोषणा ALTERA_UART_DIVISOR_REG		16
#घोषणा ALTERA_UART_STATUS_TRDY_MSK	(0x40)
अटल अचिन्हित uartbase;

अटल व्योम uart_अ_दो(पूर्णांक ch)
अणु
	पूर्णांक i;

	क्रम (i = 0; (i < 0x10000); i++) अणु
		अगर (पढ़ोw(uartbase + ALTERA_UART_STATUS_REG) &
			ALTERA_UART_STATUS_TRDY_MSK)
			अवरोध;
	पूर्ण
	ग_लिखोb(ch, uartbase + ALTERA_UART_TXDATA_REG);
पूर्ण

अटल पूर्णांक अक्षर_दो(पूर्णांक ch)
अणु
	uart_अ_दो(ch);
	अगर (ch == '\n')
		uart_अ_दो('\r');
	वापस ch;
पूर्ण

अटल व्योम console_init(व्योम)
अणु
	अचिन्हित पूर्णांक baud, baudclk;

	uartbase = (अचिन्हित दीर्घ) my_ioremap((अचिन्हित दीर्घ) UART0_BASE);
	baud = CONFIG_SERIAL_ALTERA_UART_BAUDRATE;
	baudclk = UART0_FREQ / baud;
	ग_लिखोw(baudclk, uartbase + ALTERA_UART_DIVISOR_REG);
पूर्ण

#अन्यथा

अटल पूर्णांक अक्षर_दो(पूर्णांक ch)
अणु
	वापस ch;
पूर्ण

अटल व्योम console_init(व्योम)
अणु
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक माला_दो(स्थिर अक्षर *s)
अणु
	जबतक (*s)
		अक्षर_दो(*s++);
	वापस 0;
पूर्ण
