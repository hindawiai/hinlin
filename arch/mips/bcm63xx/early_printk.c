<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2008 Maxime Bizon <mbizon@मुक्तbox.fr>
 */

#समावेश <bcm63xx_पन.स>
#समावेश <linux/serial_bcm63xx.h>
#समावेश <यंत्र/setup.h>

अटल व्योम रुको_xfered(व्योम)
अणु
	अचिन्हित पूर्णांक val;

	/* रुको क्रम any previous अक्षर to be transmitted */
	करो अणु
		val = bcm_uart0_पढ़ोl(UART_IR_REG);
		अगर (val & UART_IR_STAT(UART_IR_TXEMPTY))
			अवरोध;
	पूर्ण जबतक (1);
पूर्ण

व्योम prom_अक्षर_दो(अक्षर c)
अणु
	रुको_xfered();
	bcm_uart0_ग_लिखोl(c, UART_FIFO_REG);
	रुको_xfered();
पूर्ण
