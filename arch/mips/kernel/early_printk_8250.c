<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  8250/16550-type serial ports prom_अक्षर_दो()
 *
 *  Copyright (C) 2010  Yoichi Yuasa <yuasa@linux-mips.org>
 */
#समावेश <linux/पन.स>
#समावेश <linux/serial_core.h>
#समावेश <linux/serial_reg.h>
#समावेश <यंत्र/setup.h>

अटल व्योम __iomem *serial8250_base;
अटल अचिन्हित पूर्णांक serial8250_reg_shअगरt;
अटल अचिन्हित पूर्णांक serial8250_tx_समयout;

व्योम setup_8250_early_prपूर्णांकk_port(अचिन्हित दीर्घ base, अचिन्हित पूर्णांक reg_shअगरt,
				  अचिन्हित पूर्णांक समयout)
अणु
	serial8250_base = (व्योम __iomem *)base;
	serial8250_reg_shअगरt = reg_shअगरt;
	serial8250_tx_समयout = समयout;
पूर्ण

अटल अंतरभूत u8 serial_in(पूर्णांक offset)
अणु
	वापस पढ़ोb(serial8250_base + (offset << serial8250_reg_shअगरt));
पूर्ण

अटल अंतरभूत व्योम serial_out(पूर्णांक offset, अक्षर value)
अणु
	ग_लिखोb(value, serial8250_base + (offset << serial8250_reg_shअगरt));
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	अचिन्हित पूर्णांक समयout;
	पूर्णांक status, bits;

	अगर (!serial8250_base)
		वापस;

	समयout = serial8250_tx_समयout;
	bits = UART_LSR_TEMT | UART_LSR_THRE;

	करो अणु
		status = serial_in(UART_LSR);

		अगर (--समयout == 0)
			अवरोध;
	पूर्ण जबतक ((status & bits) != bits);

	अगर (समयout)
		serial_out(UART_TX, c);
पूर्ण
