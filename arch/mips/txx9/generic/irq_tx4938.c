<शैली गुरु>
/*
 * linux/arch/mips/tx4938/common/irq.c
 *
 * Common tx4938 irq handler
 * Copyright (C) 2000-2001 Toshiba Corporation
 *
 * 2003-2005 (c) MontaVista Software, Inc. This file is licensed under the
 * terms of the GNU General Public License version 2. This program is
 * licensed "as is" without any warranty of any kind, whether express
 * or implied.
 *
 * Support क्रम TX4938 in 2.6 - Manish Lachwani (mlachwani@mvista.com)
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/txx9/tx4938.h>

व्योम __init tx4938_irq_init(व्योम)
अणु
	पूर्णांक i;

	mips_cpu_irq_init();
	txx9_irq_init(TX4938_IRC_REG & 0xfffffffffULL);
	irq_set_chained_handler(MIPS_CPU_IRQ_BASE + TX4938_IRC_INT,
				handle_simple_irq);
	/* उठाओ priority क्रम errors, समयrs, SIO */
	txx9_irq_set_pri(TX4938_IR_ECCERR, 7);
	txx9_irq_set_pri(TX4938_IR_WTOERR, 7);
	txx9_irq_set_pri(TX4938_IR_PCIERR, 7);
	txx9_irq_set_pri(TX4938_IR_PCIPME, 7);
	क्रम (i = 0; i < TX4938_NUM_IR_TMR; i++)
		txx9_irq_set_pri(TX4938_IR_TMR(i), 6);
	क्रम (i = 0; i < TX4938_NUM_IR_SIO; i++)
		txx9_irq_set_pri(TX4938_IR_SIO(i), 5);
पूर्ण
