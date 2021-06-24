<शैली गुरु>
/*
 * This file is licensed under the terms of the GNU General Public
 * License version 2.  This program is licensed "as is" without any
 * warranty of any kind, whether express or implied.
 */

#घोषणा UART0_PHYS_BASE (0xf1000000 + 0x12000)

#घोषणा UART_THR ((अस्थिर अचिन्हित अक्षर *)(UART0_PHYS_BASE + 0x0))
#घोषणा UART_LSR ((अस्थिर अचिन्हित अक्षर *)(UART0_PHYS_BASE + 0x14))

#घोषणा LSR_THRE	0x20

अटल व्योम अ_दो(स्थिर अक्षर c)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < 0x1000; i++) अणु
		/* Transmit fअगरo not full? */
		अगर (*UART_LSR & LSR_THRE)
			अवरोध;
	पूर्ण

	*UART_THR = c;
पूर्ण

अटल व्योम flush(व्योम)
अणु
पूर्ण

/*
 * nothing to करो
 */
#घोषणा arch_decomp_setup()
