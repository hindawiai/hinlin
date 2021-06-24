<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 *
 * This file contains the lowest level x86_64-specअगरic पूर्णांकerrupt
 * entry and irq statistics code. All the reमुख्यing irq logic is
 * करोne by the generic kernel/irq/ code and in the
 * x86_64-specअगरic irq controller code. (e.g. i8259.c and
 * io_apic.c.)
 */

#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/delay.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/smp.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/softirq_stack.h>
#समावेश <यंत्र/irq_stack.h>
#समावेश <यंत्र/io_apic.h>
#समावेश <यंत्र/apic.h>

DEFINE_PER_CPU_PAGE_ALIGNED(काष्ठा irq_stack, irq_stack_backing_store) __visible;
DECLARE_INIT_PER_CPU(irq_stack_backing_store);

#अगर_घोषित CONFIG_VMAP_STACK
/*
 * VMAP the backing store with guard pages
 */
अटल पूर्णांक map_irq_stack(अचिन्हित पूर्णांक cpu)
अणु
	अक्षर *stack = (अक्षर *)per_cpu_ptr(&irq_stack_backing_store, cpu);
	काष्ठा page *pages[IRQ_STACK_SIZE / PAGE_SIZE];
	व्योम *va;
	पूर्णांक i;

	क्रम (i = 0; i < IRQ_STACK_SIZE / PAGE_SIZE; i++) अणु
		phys_addr_t pa = per_cpu_ptr_to_phys(stack + (i << PAGE_SHIFT));

		pages[i] = pfn_to_page(pa >> PAGE_SHIFT);
	पूर्ण

	va = vmap(pages, IRQ_STACK_SIZE / PAGE_SIZE, VM_MAP, PAGE_KERNEL);
	अगर (!va)
		वापस -ENOMEM;

	/* Store actual TOS to aव्योम adjusपंचांगent in the hotpath */
	per_cpu(hardirq_stack_ptr, cpu) = va + IRQ_STACK_SIZE - 8;
	वापस 0;
पूर्ण
#अन्यथा
/*
 * If VMAP stacks are disabled due to KASAN, just use the per cpu
 * backing store without guard pages.
 */
अटल पूर्णांक map_irq_stack(अचिन्हित पूर्णांक cpu)
अणु
	व्योम *va = per_cpu_ptr(&irq_stack_backing_store, cpu);

	/* Store actual TOS to aव्योम adjusपंचांगent in the hotpath */
	per_cpu(hardirq_stack_ptr, cpu) = va + IRQ_STACK_SIZE - 8;
	वापस 0;
पूर्ण
#पूर्ण_अगर

पूर्णांक irq_init_percpu_irqstack(अचिन्हित पूर्णांक cpu)
अणु
	अगर (per_cpu(hardirq_stack_ptr, cpu))
		वापस 0;
	वापस map_irq_stack(cpu);
पूर्ण
