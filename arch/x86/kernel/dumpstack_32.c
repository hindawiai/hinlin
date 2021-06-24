<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 2000, 2001, 2002 Andi Kleen, SuSE Lअसल
 */
#समावेश <linux/sched/debug.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/export.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kexec.h>
#समावेश <linux/sysfs.h>
#समावेश <linux/bug.h>
#समावेश <linux/nmi.h>

#समावेश <यंत्र/stacktrace.h>

स्थिर अक्षर *stack_type_name(क्रमागत stack_type type)
अणु
	अगर (type == STACK_TYPE_IRQ)
		वापस "IRQ";

	अगर (type == STACK_TYPE_SOFTIRQ)
		वापस "SOFTIRQ";

	अगर (type == STACK_TYPE_ENTRY)
		वापस "ENTRY_TRAMPOLINE";

	अगर (type == STACK_TYPE_EXCEPTION)
		वापस "#DF";

	वापस शून्य;
पूर्ण

अटल bool in_hardirq_stack(अचिन्हित दीर्घ *stack, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ *begin = (अचिन्हित दीर्घ *)this_cpu_पढ़ो(hardirq_stack_ptr);
	अचिन्हित दीर्घ *end   = begin + (THREAD_SIZE / माप(दीर्घ));

	/*
	 * This is a software stack, so 'end' can be a valid stack poपूर्णांकer.
	 * It just means the stack is empty.
	 */
	अगर (stack < begin || stack > end)
		वापस false;

	info->type	= STACK_TYPE_IRQ;
	info->begin	= begin;
	info->end	= end;

	/*
	 * See irq_32.c -- the next stack poपूर्णांकer is stored at the beginning of
	 * the stack.
	 */
	info->next_sp	= (अचिन्हित दीर्घ *)*begin;

	वापस true;
पूर्ण

अटल bool in_softirq_stack(अचिन्हित दीर्घ *stack, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ *begin = (अचिन्हित दीर्घ *)this_cpu_पढ़ो(softirq_stack_ptr);
	अचिन्हित दीर्घ *end   = begin + (THREAD_SIZE / माप(दीर्घ));

	/*
	 * This is a software stack, so 'end' can be a valid stack poपूर्णांकer.
	 * It just means the stack is empty.
	 */
	अगर (stack < begin || stack > end)
		वापस false;

	info->type	= STACK_TYPE_SOFTIRQ;
	info->begin	= begin;
	info->end	= end;

	/*
	 * The next stack poपूर्णांकer is stored at the beginning of the stack.
	 * See irq_32.c.
	 */
	info->next_sp	= (अचिन्हित दीर्घ *)*begin;

	वापस true;
पूर्ण

अटल bool in_द्विगुनfault_stack(अचिन्हित दीर्घ *stack, काष्ठा stack_info *info)
अणु
	काष्ठा cpu_entry_area *cea = get_cpu_entry_area(raw_smp_processor_id());
	काष्ठा द्विगुनfault_stack *ss = &cea->द्विगुनfault_stack;

	व्योम *begin = ss->stack;
	व्योम *end = begin + माप(ss->stack);

	अगर ((व्योम *)stack < begin || (व्योम *)stack >= end)
		वापस false;

	info->type	= STACK_TYPE_EXCEPTION;
	info->begin	= begin;
	info->end	= end;
	info->next_sp	= (अचिन्हित दीर्घ *)this_cpu_पढ़ो(cpu_tss_rw.x86_tss.sp);

	वापस true;
पूर्ण


पूर्णांक get_stack_info(अचिन्हित दीर्घ *stack, काष्ठा task_काष्ठा *task,
		   काष्ठा stack_info *info, अचिन्हित दीर्घ *visit_mask)
अणु
	अगर (!stack)
		जाओ unknown;

	task = task ? : current;

	अगर (in_task_stack(stack, task, info))
		जाओ recursion_check;

	अगर (task != current)
		जाओ unknown;

	अगर (in_entry_stack(stack, info))
		जाओ recursion_check;

	अगर (in_hardirq_stack(stack, info))
		जाओ recursion_check;

	अगर (in_softirq_stack(stack, info))
		जाओ recursion_check;

	अगर (in_द्विगुनfault_stack(stack, info))
		जाओ recursion_check;

	जाओ unknown;

recursion_check:
	/*
	 * Make sure we करोn't iterate through any given stack more than once.
	 * If it comes up a second समय then there's something wrong going on:
	 * just अवरोध out and report an unknown stack type.
	 */
	अगर (visit_mask) अणु
		अगर (*visit_mask & (1UL << info->type)) अणु
			prपूर्णांकk_deferred_once(KERN_WARNING "WARNING: stack recursion on stack type %d\n", info->type);
			जाओ unknown;
		पूर्ण
		*visit_mask |= 1UL << info->type;
	पूर्ण

	वापस 0;

unknown:
	info->type = STACK_TYPE_UNKNOWN;
	वापस -EINVAL;
पूर्ण
