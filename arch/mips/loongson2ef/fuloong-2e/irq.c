<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Copyright (C) 2007 Lemote Inc. & Institute of Computing Technology
 * Author: Fuxin Zhang, zhangfx@lemote.com
 */
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश <यंत्र/irq_cpu.h>
#समावेश <यंत्र/i8259.h>

#समावेश <loongson.h>

अटल व्योम i8259_irqdispatch(व्योम)
अणु
	पूर्णांक irq;

	irq = i8259_irq();
	अगर (irq >= 0)
		करो_IRQ(irq);
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

यंत्रlinkage व्योम mach_irq_dispatch(अचिन्हित पूर्णांक pending)
अणु
	अगर (pending & CAUSEF_IP7)
		करो_IRQ(MIPS_CPU_IRQ_BASE + 7);
	अन्यथा अगर (pending & CAUSEF_IP6) /* perf counter loverflow */
		वापस;
	अन्यथा अगर (pending & CAUSEF_IP5)
		i8259_irqdispatch();
	अन्यथा अगर (pending & CAUSEF_IP2)
		bonito_irqdispatch();
	अन्यथा
		spurious_पूर्णांकerrupt();
पूर्ण

व्योम __init mach_init_irq(व्योम)
अणु
	पूर्णांक irq;

	/* init all controller
	 *   0-15	  ------> i8259 पूर्णांकerrupt
	 *   16-23	  ------> mips cpu पूर्णांकerrupt
	 *   32-63	  ------> bonito irq
	 */

	/* most bonito irq should be level triggered */
	LOONGSON_INTEDGE = LOONGSON_ICU_SYSTEMERR | LOONGSON_ICU_MASTERERR |
	    LOONGSON_ICU_RETRYERR | LOONGSON_ICU_MBOXES;

	/* Sets the first-level पूर्णांकerrupt dispatcher. */
	mips_cpu_irq_init();
	init_i8259_irqs();
	bonito_irq_init();

	/* bonito irq at IP2 */
	irq = MIPS_CPU_IRQ_BASE + 2;
	अगर (request_irq(irq, no_action, IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to request irq %d (cascade)\n", irq);
	/* 8259 irq at IP5 */
	irq = MIPS_CPU_IRQ_BASE + 5;
	अगर (request_irq(irq, no_action, IRQF_NO_THREAD, "cascade", शून्य))
		pr_err("Failed to request irq %d (cascade)\n", irq);
पूर्ण
