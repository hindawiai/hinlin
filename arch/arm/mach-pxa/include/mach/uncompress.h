<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 * arch/arm/mach-pxa/include/mach/uncompress.h
 *
 * Author:	Nicolas Pitre
 * Copyright:	(C) 2001 MontaVista Software Inc.
 */

#समावेश <linux/serial_reg.h>
#समावेश <यंत्र/mach-types.h>

#घोषणा FFUART_BASE	(0x40100000)
#घोषणा BTUART_BASE	(0x40200000)
#घोषणा STUART_BASE	(0x40700000)

अचिन्हित दीर्घ uart_base;
अचिन्हित पूर्णांक uart_shअगरt;
अचिन्हित पूर्णांक uart_is_pxa;

अटल अंतरभूत अचिन्हित अक्षर uart_पढ़ो(पूर्णांक offset)
अणु
	वापस *(अस्थिर अचिन्हित अक्षर *)(uart_base + (offset << uart_shअगरt));
पूर्ण

अटल अंतरभूत व्योम uart_ग_लिखो(अचिन्हित अक्षर val, पूर्णांक offset)
अणु
	*(अस्थिर अचिन्हित अक्षर *)(uart_base + (offset << uart_shअगरt)) = val;
पूर्ण

अटल अंतरभूत पूर्णांक uart_is_enabled(व्योम)
अणु
	/* assume enabled by शेष क्रम non-PXA uarts */
	वापस uart_is_pxa ? uart_पढ़ो(UART_IER) & UART_IER_UUE : 1;
पूर्ण

अटल अंतरभूत व्योम अ_दो(अक्षर c)
अणु
	अगर (!uart_is_enabled())
		वापस;

	जबतक (!(uart_पढ़ो(UART_LSR) & UART_LSR_THRE))
		barrier();

	uart_ग_लिखो(c, UART_TX);
पूर्ण

/*
 * This करोes not append a newline
 */
अटल अंतरभूत व्योम flush(व्योम)
अणु
पूर्ण

अटल अंतरभूत व्योम arch_decomp_setup(व्योम)
अणु
	/* initialize to शेष */
	uart_base = FFUART_BASE;
	uart_shअगरt = 2;
	uart_is_pxa = 1;

	अगर (machine_is_littleton() || machine_is_पूर्णांकelmote2()
	    || machine_is_csb726() || machine_is_stargate2()
	    || machine_is_cm_x300() || machine_is_balloon3())
		uart_base = STUART_BASE;

	अगर (machine_is_arcom_zeus()) अणु
		uart_base = 0x10000000;	/* nCS4 */
		uart_shअगरt = 1;
		uart_is_pxa = 0;
	पूर्ण
पूर्ण
