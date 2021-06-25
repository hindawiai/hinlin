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

#समावेश <यंत्र/cpu_entry_area.h>
#समावेश <यंत्र/stacktrace.h>

अटल स्थिर अक्षर * स्थिर exception_stack_names[] = अणु
		[ ESTACK_DF	]	= "#DF",
		[ ESTACK_NMI	]	= "NMI",
		[ ESTACK_DB	]	= "#DB",
		[ ESTACK_MCE	]	= "#MC",
		[ ESTACK_VC	]	= "#VC",
		[ ESTACK_VC2	]	= "#VC2",
पूर्ण;

स्थिर अक्षर *stack_type_name(क्रमागत stack_type type)
अणु
	BUILD_BUG_ON(N_EXCEPTION_STACKS != 6);

	अगर (type == STACK_TYPE_IRQ)
		वापस "IRQ";

	अगर (type == STACK_TYPE_ENTRY) अणु
		/*
		 * On 64-bit, we have a generic entry stack that we
		 * use क्रम all the kernel entry poपूर्णांकs, including
		 * SYSENTER.
		 */
		वापस "ENTRY_TRAMPOLINE";
	पूर्ण

	अगर (type >= STACK_TYPE_EXCEPTION && type <= STACK_TYPE_EXCEPTION_LAST)
		वापस exception_stack_names[type - STACK_TYPE_EXCEPTION];

	वापस शून्य;
पूर्ण

/**
 * काष्ठा estack_pages - Page descriptor क्रम exception stacks
 * @offs:	Offset from the start of the exception stack area
 * @size:	Size of the exception stack
 * @type:	Type to store in the stack_info काष्ठा
 */
काष्ठा estack_pages अणु
	u32	offs;
	u16	size;
	u16	type;
पूर्ण;

#घोषणा EPAGदुस्फल(st)							\
	[PFN_DOWN(CEA_ESTACK_OFFS(st)) ...				\
	 PFN_DOWN(CEA_ESTACK_OFFS(st) + CEA_ESTACK_SIZE(st) - 1)] = अणु	\
		.offs	= CEA_ESTACK_OFFS(st),				\
		.size	= CEA_ESTACK_SIZE(st),				\
		.type	= STACK_TYPE_EXCEPTION + ESTACK_ ##st, पूर्ण

/*
 * Array of exception stack page descriptors. If the stack is larger than
 * PAGE_SIZE, all pages covering a particular stack will have the same
 * info. The guard pages including the not mapped DB2 stack are zeroed
 * out.
 */
अटल स्थिर
काष्ठा estack_pages estack_pages[CEA_ESTACK_PAGES] ____cacheline_aligned = अणु
	EPAGदुस्फल(DF),
	EPAGदुस्फल(NMI),
	EPAGदुस्फल(DB),
	EPAGदुस्फल(MCE),
	EPAGदुस्फल(VC),
	EPAGदुस्फल(VC2),
पूर्ण;

अटल __always_अंतरभूत bool in_exception_stack(अचिन्हित दीर्घ *stack, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ begin, end, stk = (अचिन्हित दीर्घ)stack;
	स्थिर काष्ठा estack_pages *ep;
	काष्ठा pt_regs *regs;
	अचिन्हित पूर्णांक k;

	BUILD_BUG_ON(N_EXCEPTION_STACKS != 6);

	begin = (अचिन्हित दीर्घ)__this_cpu_पढ़ो(cea_exception_stacks);
	/*
	 * Handle the हाल where stack trace is collected _beक्रमe_
	 * cea_exception_stacks had been initialized.
	 */
	अगर (!begin)
		वापस false;

	end = begin + माप(काष्ठा cea_exception_stacks);
	/* Bail अगर @stack is outside the exception stack area. */
	अगर (stk < begin || stk >= end)
		वापस false;

	/* Calc page offset from start of exception stacks */
	k = (stk - begin) >> PAGE_SHIFT;
	/* Lookup the page descriptor */
	ep = &estack_pages[k];
	/* Guard page? */
	अगर (!ep->size)
		वापस false;

	begin += (अचिन्हित दीर्घ)ep->offs;
	end = begin + (अचिन्हित दीर्घ)ep->size;
	regs = (काष्ठा pt_regs *)end - 1;

	info->type	= ep->type;
	info->begin	= (अचिन्हित दीर्घ *)begin;
	info->end	= (अचिन्हित दीर्घ *)end;
	info->next_sp	= (अचिन्हित दीर्घ *)regs->sp;
	वापस true;
पूर्ण

अटल __always_अंतरभूत bool in_irq_stack(अचिन्हित दीर्घ *stack, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ *end = (अचिन्हित दीर्घ *)this_cpu_पढ़ो(hardirq_stack_ptr);
	अचिन्हित दीर्घ *begin;

	/*
	 * @end poपूर्णांकs directly to the top most stack entry to aव्योम a -8
	 * adjusपंचांगent in the stack चयन hotpath. Adjust it back beक्रमe
	 * calculating @begin.
	 */
	end++;
	begin = end - (IRQ_STACK_SIZE / माप(दीर्घ));

	/*
	 * Due to the चयनing logic RSP can never be == @end because the
	 * final operation is 'popq %rsp' which means after that RSP poपूर्णांकs
	 * to the original stack and not to @end.
	 */
	अगर (stack < begin || stack >= end)
		वापस false;

	info->type	= STACK_TYPE_IRQ;
	info->begin	= begin;
	info->end	= end;

	/*
	 * The next stack poपूर्णांकer is stored at the top of the irq stack
	 * beक्रमe चयनing to the irq stack. Actual stack entries are all
	 * below that.
	 */
	info->next_sp = (अचिन्हित दीर्घ *)*(end - 1);

	वापस true;
पूर्ण

bool noinstr get_stack_info_noinstr(अचिन्हित दीर्घ *stack, काष्ठा task_काष्ठा *task,
				    काष्ठा stack_info *info)
अणु
	अगर (in_task_stack(stack, task, info))
		वापस true;

	अगर (task != current)
		वापस false;

	अगर (in_exception_stack(stack, info))
		वापस true;

	अगर (in_irq_stack(stack, info))
		वापस true;

	अगर (in_entry_stack(stack, info))
		वापस true;

	वापस false;
पूर्ण

पूर्णांक get_stack_info(अचिन्हित दीर्घ *stack, काष्ठा task_काष्ठा *task,
		   काष्ठा stack_info *info, अचिन्हित दीर्घ *visit_mask)
अणु
	task = task ? : current;

	अगर (!stack)
		जाओ unknown;

	अगर (!get_stack_info_noinstr(stack, task, info))
		जाओ unknown;

	/*
	 * Make sure we करोn't iterate through any given stack more than once.
	 * If it comes up a second समय then there's something wrong going on:
	 * just अवरोध out and report an unknown stack type.
	 */
	अगर (visit_mask) अणु
		अगर (*visit_mask & (1UL << info->type)) अणु
			अगर (task == current)
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
