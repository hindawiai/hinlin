<शैली गुरु>
/*
 * IRQ vector handles
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1995, 1996, 1997, 2003 by Ralf Baechle
 */
#समावेश <linux/kernel.h>
#समावेश <linux/init.h>
#समावेश <linux/irq.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>

#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/irq_gt641xx.h>
#समावेश <यंत्र/gt64120.h>

#समावेश <irq.h>

यंत्रlinkage व्योम plat_irq_dispatch(व्योम)
अणु
	अचिन्हित pending = पढ़ो_c0_status() & पढ़ो_c0_cause() & ST0_IM;
	पूर्णांक irq;

	अगर (pending & CAUSEF_IP2)
		gt641xx_irq_dispatch();
	अन्यथा अगर (pending & CAUSEF_IP6) अणु
		irq = i8259_irq();
		अगर (irq < 0)
			spurious_पूर्णांकerrupt();
		अन्यथा
			करो_IRQ(irq);
	पूर्ण अन्यथा अगर (pending & CAUSEF_IP3)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 3);
	अन्यथा अगर (pending & CAUSEF_IP4)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 4);
	अन्यथा अगर (pending & CAUSEF_IP5)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 5);
	अन्यथा अगर (pending & CAUSEF_IP7)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 7);
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

व्योम __init arch_init_irq(व्योम)
अणु
	mips_cpu_irq_init();
	gt641xx_irq_init();
	init_i8259_irqs();

	अगर (request_irq(GT641XX_CASCADE_IRQ, no_action, IRQF_NO_THREAD,
			"cascade", शून्य)) अणु
		pr_err("Failed to request irq %d (cascade)\n",
		       GT641XX_CASCADE_IRQ);
	पूर्ण
	अगर (request_irq(I8259_CASCADE_IRQ, no_action, IRQF_NO_THREAD,
			"cascade", शून्य)) अणु
		pr_err("Failed to request irq %d (cascade)\n",
		       I8259_CASCADE_IRQ);
	पूर्ण
पूर्ण
