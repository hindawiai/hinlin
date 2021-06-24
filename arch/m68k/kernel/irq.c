<शैली गुरु>
/*
 * irq.c
 *
 * (C) Copyright 2007, Greg Ungerer <gerg@snapgear.com>
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file COPYING in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/types.h>
#समावेश <linux/init.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <यंत्र/traps.h>

यंत्रlinkage व्योम करो_IRQ(पूर्णांक irq, काष्ठा pt_regs *regs)
अणु
	काष्ठा pt_regs *oldregs = set_irq_regs(regs);

	irq_enter();
	generic_handle_irq(irq);
	irq_निकास();

	set_irq_regs(oldregs);
पूर्ण


/* The number of spurious पूर्णांकerrupts */
atomic_t irq_err_count;

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	seq_म_लिखो(p, "%*s: %10u\n", prec, "ERR", atomic_पढ़ो(&irq_err_count));
	वापस 0;
पूर्ण
