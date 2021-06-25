<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (C) 2012 Regents of the University of Calअगरornia
 * Copyright (C) 2017 SiFive
 * Copyright (C) 2018 Christoph Hellwig
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/smp.h>

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	show_ipi_stats(p, prec);
	वापस 0;
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	irqchip_init();
	अगर (!handle_arch_irq)
		panic("No interrupt controller found.");
पूर्ण
