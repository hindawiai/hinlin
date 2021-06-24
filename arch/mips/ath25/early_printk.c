<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2010 Gabor Juhos <juhosg@खोलोwrt.org>
 */

#समावेश <linux/mm.h>
#समावेश <linux/पन.स>
#समावेश <linux/serial_reg.h>
#समावेश <यंत्र/setup.h>

#समावेश "devices.h"
#समावेश "ar2315_regs.h"
#समावेश "ar5312_regs.h"

अटल अंतरभूत व्योम prom_uart_wr(व्योम __iomem *base, अचिन्हित reg,
				अचिन्हित अक्षर ch)
अणु
	__raw_ग_लिखोl(ch, base + 4 * reg);
पूर्ण

अटल अंतरभूत अचिन्हित अक्षर prom_uart_rr(व्योम __iomem *base, अचिन्हित reg)
अणु
	वापस __raw_पढ़ोl(base + 4 * reg);
पूर्ण

व्योम prom_अक्षर_दो(अक्षर ch)
अणु
	अटल व्योम __iomem *base;

	अगर (unlikely(base == शून्य)) अणु
		अगर (is_ar2315())
			base = (व्योम __iomem *)(KSEG1ADDR(AR2315_UART0_BASE));
		अन्यथा
			base = (व्योम __iomem *)(KSEG1ADDR(AR5312_UART0_BASE));
	पूर्ण

	जबतक ((prom_uart_rr(base, UART_LSR) & UART_LSR_THRE) == 0)
		;
	prom_uart_wr(base, UART_TX, (अचिन्हित अक्षर)ch);
	जबतक ((prom_uart_rr(base, UART_LSR) & UART_LSR_THRE) == 0)
		;
पूर्ण
