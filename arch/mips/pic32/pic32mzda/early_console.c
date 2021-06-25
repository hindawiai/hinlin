<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Joshua Henderson <joshua.henderson@microchip.com>
 * Copyright (C) 2015 Microchip Technology Inc.  All rights reserved.
 */
#समावेश <यंत्र/mach-pic32/pic32.h>
#समावेश <यंत्र/fw/fw.h>
#समावेश <यंत्र/setup.h>

#समावेश "pic32mzda.h"
#समावेश "early_pin.h"

/* Default early console parameters */
#घोषणा EARLY_CONSOLE_PORT	1
#घोषणा EARLY_CONSOLE_BAUDRATE	115200

#घोषणा UART_ENABLE		BIT(15)
#घोषणा UART_ENABLE_RX		BIT(12)
#घोषणा UART_ENABLE_TX		BIT(10)
#घोषणा UART_TX_FULL		BIT(9)

/* UART1(x == 0) - UART6(x == 5) */
#घोषणा UART_BASE(x)	((x) * 0x0200)
#घोषणा U_MODE(x)	UART_BASE(x)
#घोषणा U_STA(x)	(UART_BASE(x) + 0x10)
#घोषणा U_TXR(x)	(UART_BASE(x) + 0x20)
#घोषणा U_BRG(x)	(UART_BASE(x) + 0x40)

अटल व्योम __iomem *uart_base;
अटल अक्षर console_port = -1;

अटल पूर्णांक __init configure_uart_pins(पूर्णांक port)
अणु
	चयन (port) अणु
	हाल 1:
		pic32_pps_input(IN_FUNC_U2RX, IN_RPB0);
		pic32_pps_output(OUT_FUNC_U2TX, OUT_RPG9);
		अवरोध;
	हाल 5:
		pic32_pps_input(IN_FUNC_U6RX, IN_RPD0);
		pic32_pps_output(OUT_FUNC_U6TX, OUT_RPB8);
		अवरोध;
	शेष:
		वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __init configure_uart(अक्षर port, पूर्णांक baud)
अणु
	u32 pbclk;

	pbclk = pic32_get_pbclk(2);

	__raw_ग_लिखोl(0, uart_base + U_MODE(port));
	__raw_ग_लिखोl(((pbclk / baud) / 16) - 1, uart_base + U_BRG(port));
	__raw_ग_लिखोl(UART_ENABLE, uart_base + U_MODE(port));
	__raw_ग_लिखोl(UART_ENABLE_TX | UART_ENABLE_RX,
		     uart_base + PIC32_SET(U_STA(port)));
पूर्ण

अटल व्योम __init setup_early_console(अक्षर port, पूर्णांक baud)
अणु
	अगर (configure_uart_pins(port))
		वापस;

	console_port = port;
	configure_uart(console_port, baud);
पूर्ण

अटल अक्षर * __init pic32_अ_लोmdline(व्योम)
अणु
	/*
	 * arch_mem_init() has not been called yet, so we करोn't have a real
	 * command line setup अगर using CONFIG_CMDLINE_BOOL.
	 */
#अगर_घोषित CONFIG_CMDLINE_OVERRIDE
	वापस CONFIG_CMDLINE;
#अन्यथा
	वापस fw_अ_लोmdline();
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक __init get_port_from_cmdline(अक्षर *arch_cmdline)
अणु
	अक्षर *s;
	पूर्णांक port = -1;

	अगर (!arch_cmdline || *arch_cmdline == '\0')
		जाओ _out;

	s = म_माला(arch_cmdline, "earlyprintk=");
	अगर (s) अणु
		s = म_माला(s, "ttyS");
		अगर (s)
			s += 4;
		अन्यथा
			जाओ _out;

		port = (*s) - '0';
	पूर्ण

_out:
	वापस port;
पूर्ण

अटल पूर्णांक __init get_baud_from_cmdline(अक्षर *arch_cmdline)
अणु
	अक्षर *s;
	पूर्णांक baud = -1;

	अगर (!arch_cmdline || *arch_cmdline == '\0')
		जाओ _out;

	s = म_माला(arch_cmdline, "earlyprintk=");
	अगर (s) अणु
		s = म_माला(s, "ttyS");
		अगर (s)
			s += 6;
		अन्यथा
			जाओ _out;

		baud = 0;
		जबतक (*s >= '0' && *s <= '9')
			baud = baud * 10 + *s++ - '0';
	पूर्ण

_out:
	वापस baud;
पूर्ण

व्योम __init fw_init_early_console(अक्षर port)
अणु
	अक्षर *arch_cmdline = pic32_अ_लोmdline();
	पूर्णांक baud = -1;

	uart_base = ioremap(PIC32_BASE_UART, 0xc00);

	baud = get_baud_from_cmdline(arch_cmdline);
	अगर (port == -1)
		port = get_port_from_cmdline(arch_cmdline);

	अगर (port == -1)
		port = EARLY_CONSOLE_PORT;

	अगर (baud == -1)
		baud = EARLY_CONSOLE_BAUDRATE;

	setup_early_console(port, baud);
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	अगर (console_port >= 0) अणु
		जबतक (__raw_पढ़ोl(
				uart_base + U_STA(console_port)) & UART_TX_FULL)
			;

		__raw_ग_लिखोl(c, uart_base + U_TXR(console_port));
	पूर्ण
पूर्ण
