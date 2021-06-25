<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *	Copyright (C) 1992, 1998 Linus Torvalds, Ingo Molnar
 *
 * This file contains the lowest level x86-specअगरic पूर्णांकerrupt
 * entry, irq-stacks and irq statistics code. All the reमुख्यing
 * irq logic is करोne by the generic kernel/irq/ code and
 * by the x86-specअगरic irq controller code. (e.g. i8259.c and
 * io_apic.c.)
 */

#समावेश <linux/seq_file.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/irq.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/notअगरier.h>
#समावेश <linux/cpu.h>
#समावेश <linux/delay.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/percpu.h>
#समावेश <linux/mm.h>

#समावेश <यंत्र/apic.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/softirq_stack.h>

#अगर_घोषित CONFIG_DEBUG_STACKOVERFLOW

पूर्णांक sysctl_panic_on_stackoverflow __पढ़ो_mostly;

/* Debugging check क्रम stack overflow: is there less than 1KB मुक्त? */
अटल पूर्णांक check_stack_overflow(व्योम)
अणु
	दीर्घ sp;

	__यंत्र__ __अस्थिर__("andl %%esp,%0" :
			     "=r" (sp) : "0" (THREAD_SIZE - 1));

	वापस sp < (माप(काष्ठा thपढ़ो_info) + STACK_WARN);
पूर्ण

अटल व्योम prपूर्णांक_stack_overflow(व्योम)
अणु
	prपूर्णांकk(KERN_WARNING "low stack detected by irq handler\n");
	dump_stack();
	अगर (sysctl_panic_on_stackoverflow)
		panic("low stack detected by irq handler - check messages\n");
पूर्ण

#अन्यथा
अटल अंतरभूत पूर्णांक check_stack_overflow(व्योम) अणु वापस 0; पूर्ण
अटल अंतरभूत व्योम prपूर्णांक_stack_overflow(व्योम) अणु पूर्ण
#पूर्ण_अगर

DEFINE_PER_CPU(काष्ठा irq_stack *, hardirq_stack_ptr);
DEFINE_PER_CPU(काष्ठा irq_stack *, softirq_stack_ptr);

अटल व्योम call_on_stack(व्योम *func, व्योम *stack)
अणु
	यंत्र अस्थिर("xchgl	%%ebx,%%esp	\n"
		     CALL_NOSPEC
		     "movl	%%ebx,%%esp	\n"
		     : "=b" (stack)
		     : "0" (stack),
		       [thunk_target] "D"(func)
		     : "memory", "cc", "edx", "ecx", "eax");
पूर्ण

अटल अंतरभूत व्योम *current_stack(व्योम)
अणु
	वापस (व्योम *)(current_stack_poपूर्णांकer & ~(THREAD_SIZE - 1));
पूर्ण

अटल अंतरभूत पूर्णांक execute_on_irq_stack(पूर्णांक overflow, काष्ठा irq_desc *desc)
अणु
	काष्ठा irq_stack *curstk, *irqstk;
	u32 *isp, *prev_esp, arg1;

	curstk = (काष्ठा irq_stack *) current_stack();
	irqstk = __this_cpu_पढ़ो(hardirq_stack_ptr);

	/*
	 * this is where we चयन to the IRQ stack. However, अगर we are
	 * alपढ़ोy using the IRQ stack (because we पूर्णांकerrupted a hardirq
	 * handler) we can't करो that and just have to keep using the
	 * current stack (which is the irq stack alपढ़ोy after all)
	 */
	अगर (unlikely(curstk == irqstk))
		वापस 0;

	isp = (u32 *) ((अक्षर *)irqstk + माप(*irqstk));

	/* Save the next esp at the bottom of the stack */
	prev_esp = (u32 *)irqstk;
	*prev_esp = current_stack_poपूर्णांकer;

	अगर (unlikely(overflow))
		call_on_stack(prपूर्णांक_stack_overflow, isp);

	यंत्र अस्थिर("xchgl	%%ebx,%%esp	\n"
		     CALL_NOSPEC
		     "movl	%%ebx,%%esp	\n"
		     : "=a" (arg1), "=b" (isp)
		     :  "0" (desc),   "1" (isp),
			[thunk_target] "D" (desc->handle_irq)
		     : "memory", "cc", "ecx");
	वापस 1;
पूर्ण

/*
 * Allocate per-cpu stacks क्रम hardirq and softirq processing
 */
पूर्णांक irq_init_percpu_irqstack(अचिन्हित पूर्णांक cpu)
अणु
	पूर्णांक node = cpu_to_node(cpu);
	काष्ठा page *ph, *ps;

	अगर (per_cpu(hardirq_stack_ptr, cpu))
		वापस 0;

	ph = alloc_pages_node(node, THREADINFO_GFP, THREAD_SIZE_ORDER);
	अगर (!ph)
		वापस -ENOMEM;
	ps = alloc_pages_node(node, THREADINFO_GFP, THREAD_SIZE_ORDER);
	अगर (!ps) अणु
		__मुक्त_pages(ph, THREAD_SIZE_ORDER);
		वापस -ENOMEM;
	पूर्ण

	per_cpu(hardirq_stack_ptr, cpu) = page_address(ph);
	per_cpu(softirq_stack_ptr, cpu) = page_address(ps);
	वापस 0;
पूर्ण

व्योम करो_softirq_own_stack(व्योम)
अणु
	काष्ठा irq_stack *irqstk;
	u32 *isp, *prev_esp;

	irqstk = __this_cpu_पढ़ो(softirq_stack_ptr);

	/* build the stack frame on the softirq stack */
	isp = (u32 *) ((अक्षर *)irqstk + माप(*irqstk));

	/* Push the previous esp onto the stack */
	prev_esp = (u32 *)irqstk;
	*prev_esp = current_stack_poपूर्णांकer;

	call_on_stack(__करो_softirq, isp);
पूर्ण

व्योम __handle_irq(काष्ठा irq_desc *desc, काष्ठा pt_regs *regs)
अणु
	पूर्णांक overflow = check_stack_overflow();

	अगर (user_mode(regs) || !execute_on_irq_stack(overflow, desc)) अणु
		अगर (unlikely(overflow))
			prपूर्णांक_stack_overflow();
		generic_handle_irq_desc(desc);
	पूर्ण
पूर्ण
