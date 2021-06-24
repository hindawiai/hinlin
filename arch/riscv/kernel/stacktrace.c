<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2008 ARM Limited
 * Copyright (C) 2014 Regents of the University of Calअगरornia
 */

#समावेश <linux/export.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/ftrace.h>

#समावेश <यंत्र/stacktrace.h>

रेजिस्टर अचिन्हित दीर्घ sp_in_global __यंत्र__("sp");

#अगर_घोषित CONFIG_FRAME_POINTER

व्योम notrace walk_stackframe(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
			     bool (*fn)(व्योम *, अचिन्हित दीर्घ), व्योम *arg)
अणु
	अचिन्हित दीर्घ fp, sp, pc;

	अगर (regs) अणु
		fp = frame_poपूर्णांकer(regs);
		sp = user_stack_poपूर्णांकer(regs);
		pc = inकाष्ठाion_poपूर्णांकer(regs);
	पूर्ण अन्यथा अगर (task == current) अणु
		fp = (अचिन्हित दीर्घ)__builtin_frame_address(1);
		sp = (अचिन्हित दीर्घ)__builtin_frame_address(0);
		pc = (अचिन्हित दीर्घ)__builtin_वापस_address(0);
	पूर्ण अन्यथा अणु
		/* task blocked in __चयन_to */
		fp = task->thपढ़ो.s[0];
		sp = task->thपढ़ो.sp;
		pc = task->thपढ़ो.ra;
	पूर्ण

	क्रम (;;) अणु
		अचिन्हित दीर्घ low, high;
		काष्ठा stackframe *frame;

		अगर (unlikely(!__kernel_text_address(pc) || !fn(arg, pc)))
			अवरोध;

		/* Validate frame poपूर्णांकer */
		low = sp + माप(काष्ठा stackframe);
		high = ALIGN(sp, THREAD_SIZE);
		अगर (unlikely(fp < low || fp > high || fp & 0x7))
			अवरोध;
		/* Unwind stack frame */
		frame = (काष्ठा stackframe *)fp - 1;
		sp = fp;
		अगर (regs && (regs->epc == pc) && (frame->fp & 0x7)) अणु
			fp = frame->ra;
			pc = regs->ra;
		पूर्ण अन्यथा अणु
			fp = frame->fp;
			pc = ftrace_graph_ret_addr(current, शून्य, frame->ra,
						   (अचिन्हित दीर्घ *)(fp - 8));
		पूर्ण

	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_FRAME_POINTER */

व्योम notrace walk_stackframe(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, bool (*fn)(व्योम *, अचिन्हित दीर्घ), व्योम *arg)
अणु
	अचिन्हित दीर्घ sp, pc;
	अचिन्हित दीर्घ *ksp;

	अगर (regs) अणु
		sp = user_stack_poपूर्णांकer(regs);
		pc = inकाष्ठाion_poपूर्णांकer(regs);
	पूर्ण अन्यथा अगर (task == शून्य || task == current) अणु
		sp = sp_in_global;
		pc = (अचिन्हित दीर्घ)walk_stackframe;
	पूर्ण अन्यथा अणु
		/* task blocked in __चयन_to */
		sp = task->thपढ़ो.sp;
		pc = task->thपढ़ो.ra;
	पूर्ण

	अगर (unlikely(sp & 0x7))
		वापस;

	ksp = (अचिन्हित दीर्घ *)sp;
	जबतक (!kstack_end(ksp)) अणु
		अगर (__kernel_text_address(pc) && unlikely(!fn(arg, pc)))
			अवरोध;
		pc = (*ksp++) - 0x4;
	पूर्ण
पूर्ण

#पूर्ण_अगर /* CONFIG_FRAME_POINTER */

अटल bool prपूर्णांक_trace_address(व्योम *arg, अचिन्हित दीर्घ pc)
अणु
	स्थिर अक्षर *loglvl = arg;

	prपूर्णांक_ip_sym(loglvl, pc);
	वापस true;
पूर्ण

noअंतरभूत व्योम dump_backtrace(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *task,
		    स्थिर अक्षर *loglvl)
अणु
	walk_stackframe(task, regs, prपूर्णांक_trace_address, (व्योम *)loglvl);
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	pr_cont("%sCall Trace:\n", loglvl);
	dump_backtrace(शून्य, task, loglvl);
पूर्ण

अटल bool save_wchan(व्योम *arg, अचिन्हित दीर्घ pc)
अणु
	अगर (!in_sched_functions(pc)) अणु
		अचिन्हित दीर्घ *p = arg;
		*p = pc;
		वापस false;
	पूर्ण
	वापस true;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ pc = 0;

	अगर (likely(task && task != current && task->state != TASK_RUNNING))
		walk_stackframe(task, शून्य, save_wchan, &pc);
	वापस pc;
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE

noअंतरभूत व्योम arch_stack_walk(stack_trace_consume_fn consume_entry, व्योम *cookie,
		     काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs)
अणु
	walk_stackframe(task, regs, consume_entry, cookie);
पूर्ण

#पूर्ण_अगर /* CONFIG_STACKTRACE */
