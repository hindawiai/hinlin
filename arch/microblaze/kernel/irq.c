<शैली गुरु>
/*
 * Copyright (C) 2007-2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2007-2009 PetaLogix
 * Copyright (C) 2006 Aपंचांगark Techno, Inc.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/init.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kernel.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irqflags.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/irq.h>
#समावेश <linux/irqchip.h>
#समावेश <linux/of_irq.h>

अटल u32 concurrent_irq;

व्योम __irq_entry करो_IRQ(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक irq;
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	trace_hardirqs_off();

	irq_enter();
	irq = xपूर्णांकc_get_irq();
next_irq:
	BUG_ON(!irq);
	generic_handle_irq(irq);

	irq = xपूर्णांकc_get_irq();
	अगर (irq != -1U) अणु
		pr_debug("next irq: %d\n", irq);
		++concurrent_irq;
		जाओ next_irq;
	पूर्ण

	irq_निकास();
	set_irq_regs(old_regs);
	trace_hardirqs_on();
पूर्ण

व्योम __init init_IRQ(व्योम)
अणु
	/* process the entire पूर्णांकerrupt tree in one go */
	irqchip_init();
पूर्ण
