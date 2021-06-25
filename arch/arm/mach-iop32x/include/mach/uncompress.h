<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * arch/arm/mach-iop32x/include/mach/uncompress.h
 */

#समावेश <यंत्र/types.h>
#समावेश <यंत्र/mach-types.h>
#समावेश <linux/serial_reg.h>

#घोषणा uart_base ((अस्थिर u8 *)0xfe800000)

#घोषणा TX_DONE		(UART_LSR_TEMT | UART_LSR_THRE)

अटल अंतरभूत व्योम अ_दो(अक्षर c)
अणु
	जबतक ((uart_base[UART_LSR] & TX_DONE) != TX_DONE)
		barrier();
	uart_base[UART_TX] = c;
पूर्ण

अटल अंतरभूत व्योम flush(व्योम)
अणु
पूर्ण

#घोषणा arch_decomp_setup() करो अणु पूर्ण जबतक (0)
