<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * linux/arch/sh/boards/lboxre2/irq.c
 *
 * Copyright (C) 2007 Nobuhiro Iwamatsu
 *
 * NTT COMWARE L-BOX RE2 Support.
 */
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/पन.स>
#समावेश <mach/lboxre2.h>

/*
 * Initialize IRQ setting
 */
व्योम __init init_lboxre2_IRQ(व्योम)
अणु
	make_imask_irq(IRQ_CF1);
	make_imask_irq(IRQ_CF0);
	make_imask_irq(IRQ_INTD);
	make_imask_irq(IRQ_ETH1);
	make_imask_irq(IRQ_ETH0);
	make_imask_irq(IRQ_INTA);
पूर्ण
