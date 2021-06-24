<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Lemote Inc.
 * Author: Fuxin Zhang, zhangfx@lemote.com
 */

#समावेश <linux/export.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/i8259.h>
#समावेश <यंत्र/mipsregs.h>

#समावेश <loongson.h>
#समावेश <machine.h>

#घोषणा LOONGSON_TIMER_IRQ	(MIPS_CPU_IRQ_BASE + 7) /* cpu समयr */
#घोषणा LOONGSON_NORTH_BRIDGE_IRQ	(MIPS_CPU_IRQ_BASE + 6) /* bonito */
#घोषणा LOONGSON_UART_IRQ	(MIPS_CPU_IRQ_BASE + 3) /* cpu serial port */
#घोषणा LOONGSON_SOUTH_BRIDGE_IRQ	(MIPS_CPU_IRQ_BASE + 2) /* i8259 */

#घोषणा LOONGSON_INT_BIT_INT0		(1 << 11)
#घोषणा LOONGSON_INT_BIT_INT1		(1 << 12)

/*
 * The generic i8259_irq() make the kernel hang on booting.  Since we cannot
 * get the irq via the IRR directly, we access the ISR instead.
 */
पूर्णांक mach_i8259_irq(व्योम)
अणु
	पूर्णांक irq, isr;

	irq = -1;

	अगर ((LOONGSON_INTISR & LOONGSON_INTEN) & LOONGSON_INT_BIT_INT0) अणु
		raw_spin_lock(&i8259A_lock);
		isr = inb(PIC_MASTER_CMD) &
			~inb(PIC_MASTER_IMR) & ~(1 << PIC_CASCADE_IR);
		अगर (!isr)
			isr = (inb(PIC_SLAVE_CMD) & ~inb(PIC_SLAVE_IMR)) << 8;
		irq = ffs(isr) - 1;
		अगर (unlikely(irq == 7)) अणु
			/*
			 * This may be a spurious पूर्णांकerrupt.
			 *
			 * Read the पूर्णांकerrupt status रेजिस्टर (ISR). If the most
			 * signअगरicant bit is not set then there is no valid
			 * पूर्णांकerrupt.
			 */
			outb(0x0B, PIC_MASTER_ISR);	/* ISR रेजिस्टर */
			अगर (~inb(PIC_MASTER_ISR) & 0x80)
				irq = -1;
		पूर्ण
		raw_spin_unlock(&i8259A_lock);
	पूर्ण

	वापस irq;
पूर्ण
EXPORT_SYMBOL(mach_i8259_irq);

अटल व्योम i8259_irqdispatch(व्योम)
अणु
	पूर्णांक irq;

	irq = mach_i8259_irq();
	अगर (irq >= 0)
		करो_IRQ(irq);
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

व्योम mach_irq_dispatch(अचिन्हित पूर्णांक pending)
अणु
	अगर (pending & CAUSEF_IP7)
		करो_IRQ(LOONGSON_TIMER_IRQ);
	अन्यथा अगर (pending & CAUSEF_IP6) अणु	/* North Bridge, Perf counter */
		bonito_irqdispatch();
	पूर्ण अन्यथा अगर (pending & CAUSEF_IP3)	/* CPU UART */
		करो_IRQ(LOONGSON_UART_IRQ);
	अन्यथा अगर (pending & CAUSEF_IP2)	/* South Bridge */
		i8259_irqdispatch();
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

अटल irqवापस_t ip6_action(पूर्णांक cpl, व्योम *dev_id)
अणु
	वापस IRQ_HANDLED;
पूर्ण

व्योम __init mach_init_irq(व्योम)
अणु
	/* init all controller
	 *   0-15	  ------> i8259 पूर्णांकerrupt
	 *   16-23	  ------> mips cpu पूर्णांकerrupt
	 *   32-63	  ------> bonito irq
	 */

	/* setup cs5536 as high level trigger */
	LOONGSON_INTPOL = LOONGSON_INT_BIT_INT0 | LOONGSON_INT_BIT_INT1;
	LOONGSON_INTEDGE &= ~(LOONGSON_INT_BIT_INT0 | LOONGSON_INT_BIT_INT1);

	/* Sets the first-level पूर्णांकerrupt dispatcher. */
	mips_cpu_irq_init();
	init_i8259_irqs();
	bonito_irq_init();

	/* setup north bridge irq (bonito) */
	अगर (request_irq(LOONGSON_NORTH_BRIDGE_IRQ, ip6_action,
			IRQF_SHARED | IRQF_NO_THREAD, "cascade", ip6_action))
		pr_err("Failed to register north bridge cascade interrupt\n");
	/* setup source bridge irq (i8259) */
	अगर (request_irq(LOONGSON_SOUTH_BRIDGE_IRQ, no_action,
			IRQF_NO_THREAD | IRQF_NO_SUSPEND, "cascade", शून्य))
		pr_err("Failed to register south bridge cascade interrupt\n");
पूर्ण
