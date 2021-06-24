<शैली गुरु>
/*
 * Common tx3927 irq handler
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright 2001 MontaVista Software Inc.
 * Copyright (C) 2000-2001 Toshiba Corporation
 */
#समावेश <linux/init.h>
#समावेश <यंत्र/txx9irq.h>
#समावेश <यंत्र/txx9/tx3927.h>

व्योम __init tx3927_irq_init(व्योम)
अणु
	पूर्णांक i;

	txx9_irq_init(TX3927_IRC_REG);
	/* उठाओ priority क्रम समयrs, sio */
	क्रम (i = 0; i < TX3927_NR_TMR; i++)
		txx9_irq_set_pri(TX3927_IR_TMR(i), 6);
	क्रम (i = 0; i < TX3927_NR_SIO; i++)
		txx9_irq_set_pri(TX3927_IR_SIO(i), 7);
पूर्ण
