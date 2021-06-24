<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 *  Copyright (C) 1991, 1992  Linus Torvalds
 *  Copyright (C) 2000, 2001, 2002 Andi Kleen, SuSE Lअसल
 *  Copyright (C) 2009  Matt Fleming
 *  Copyright (C) 2002 - 2012  Paul Mundt
 */
#समावेश <linux/kallsyms.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/debug_locks.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/export.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/unwinder.h>
#समावेश <यंत्र/stacktrace.h>

व्योम dump_mem(स्थिर अक्षर *str, स्थिर अक्षर *loglvl, अचिन्हित दीर्घ bottom,
	      अचिन्हित दीर्घ top)
अणु
	अचिन्हित दीर्घ p;
	पूर्णांक i;

	prपूर्णांकk("%s%s(0x%08lx to 0x%08lx)\n", loglvl, str, bottom, top);

	क्रम (p = bottom & ~31; p < top; ) अणु
		prपूर्णांकk("%s%04lx: ", loglvl,  p & 0xffff);

		क्रम (i = 0; i < 8; i++, p += 4) अणु
			अचिन्हित पूर्णांक val;

			अगर (p < bottom || p >= top)
				pr_cont("         ");
			अन्यथा अणु
				अगर (__get_user(val, (अचिन्हित पूर्णांक __user *)p)) अणु
					pr_cont("\n");
					वापस;
				पूर्ण
				pr_cont("%08x ", val);
			पूर्ण
		पूर्ण
		pr_cont("\n");
	पूर्ण
पूर्ण

व्योम prपूर्णांकk_address(अचिन्हित दीर्घ address, पूर्णांक reliable)
अणु
	pr_cont(" [<%px>] %s%pS\n", (व्योम *) address,
		reliable ? "" : "? ", (व्योम *) address);
पूर्ण

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
अटल व्योम
prपूर्णांक_ftrace_graph_addr(अचिन्हित दीर्घ addr, व्योम *data,
			स्थिर काष्ठा stacktrace_ops *ops,
			काष्ठा thपढ़ो_info *tinfo, पूर्णांक *graph)
अणु
	काष्ठा task_काष्ठा *task = tinfo->task;
	काष्ठा ftrace_ret_stack *ret_stack;
	अचिन्हित दीर्घ ret_addr;

	अगर (addr != (अचिन्हित दीर्घ)वापस_to_handler)
		वापस;

	अगर (!task->ret_stack)
		वापस;

	ret_stack = ftrace_graph_get_ret_stack(task, *graph);
	अगर (!ret_stack)
		वापस;

	ret_addr = ret_stack->ret;

	ops->address(data, ret_addr, 1);

	(*graph)++;
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम
prपूर्णांक_ftrace_graph_addr(अचिन्हित दीर्घ addr, व्योम *data,
			स्थिर काष्ठा stacktrace_ops *ops,
			काष्ठा thपढ़ो_info *tinfo, पूर्णांक *graph)
अणु पूर्ण
#पूर्ण_अगर

व्योम
stack_पढ़ोer_dump(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
		  अचिन्हित दीर्घ *sp, स्थिर काष्ठा stacktrace_ops *ops,
		  व्योम *data)
अणु
	काष्ठा thपढ़ो_info *context;
	पूर्णांक graph = 0;

	context = (काष्ठा thपढ़ो_info *)
		((अचिन्हित दीर्घ)sp & (~(THREAD_SIZE - 1)));

	जबतक (!kstack_end(sp)) अणु
		अचिन्हित दीर्घ addr = *sp++;

		अगर (__kernel_text_address(addr)) अणु
			ops->address(data, addr, 1);

			prपूर्णांक_ftrace_graph_addr(addr, data, ops,
						context, &graph);
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Prपूर्णांक one address/symbol entries per line.
 */
अटल व्योम prपूर्णांक_trace_address(व्योम *data, अचिन्हित दीर्घ addr, पूर्णांक reliable)
अणु
	prपूर्णांकk("%s", (अक्षर *)data);
	prपूर्णांकk_address(addr, reliable);
पूर्ण

अटल स्थिर काष्ठा stacktrace_ops prपूर्णांक_trace_ops = अणु
	.address = prपूर्णांक_trace_address,
पूर्ण;

व्योम show_trace(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *sp,
		काष्ठा pt_regs *regs, स्थिर अक्षर *loglvl)
अणु
	अगर (regs && user_mode(regs))
		वापस;

	prपूर्णांकk("%s\nCall trace:\n", loglvl);

	unwind_stack(tsk, regs, sp, &prपूर्णांक_trace_ops, (व्योम *)loglvl);

	pr_cont("\n");

	अगर (!tsk)
		tsk = current;

	debug_show_held_locks(tsk);
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ stack;

	अगर (!tsk)
		tsk = current;
	अगर (tsk == current)
		sp = (अचिन्हित दीर्घ *)current_stack_poपूर्णांकer;
	अन्यथा
		sp = (अचिन्हित दीर्घ *)tsk->thपढ़ो.sp;

	stack = (अचिन्हित दीर्घ)sp;
	dump_mem("Stack: ", loglvl, stack, THREAD_SIZE +
		 (अचिन्हित दीर्घ)task_stack_page(tsk));
	show_trace(tsk, sp, शून्य, loglvl);
पूर्ण
