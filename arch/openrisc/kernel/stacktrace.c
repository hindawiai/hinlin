<शैली गुरु>
/*
 * Stack trace utility क्रम OpenRISC
 *
 * Copyright (C) 2017 Stafक्रमd Horne <shorne@gmail.com>
 *
 * This file is licensed under the terms of the GNU General Public License
 * version 2.  This program is licensed "as is" without any warranty of any
 * kind, whether express or implied.
 *
 * Losely based on work from sh and घातerpc.
 */

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>

#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/unwinder.h>

/*
 * Save stack-backtrace addresses पूर्णांकo a stack_trace buffer.
 */
अटल व्योम
save_stack_address(व्योम *data, अचिन्हित दीर्घ addr, पूर्णांक reliable)
अणु
	काष्ठा stack_trace *trace = data;

	अगर (!reliable)
		वापस;

	अगर (trace->skip > 0) अणु
		trace->skip--;
		वापस;
	पूर्ण

	अगर (trace->nr_entries < trace->max_entries)
		trace->entries[trace->nr_entries++] = addr;
पूर्ण

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	unwind_stack(trace, (अचिन्हित दीर्घ *) &trace, save_stack_address);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

अटल व्योम
save_stack_address_nosched(व्योम *data, अचिन्हित दीर्घ addr, पूर्णांक reliable)
अणु
	काष्ठा stack_trace *trace = (काष्ठा stack_trace *)data;

	अगर (!reliable)
		वापस;

	अगर (in_sched_functions(addr))
		वापस;

	अगर (trace->skip > 0) अणु
		trace->skip--;
		वापस;
	पूर्ण

	अगर (trace->nr_entries < trace->max_entries)
		trace->entries[trace->nr_entries++] = addr;
पूर्ण

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	अचिन्हित दीर्घ *sp = शून्य;

	अगर (!try_get_task_stack(tsk))
		वापस;

	अगर (tsk == current)
		sp = (अचिन्हित दीर्घ *) &sp;
	अन्यथा अणु
		अचिन्हित दीर्घ ksp;

		/* Locate stack from kernel context */
		ksp = task_thपढ़ो_info(tsk)->ksp;
		ksp += STACK_FRAME_OVERHEAD;	/* redzone */
		ksp += माप(काष्ठा pt_regs);

		sp = (अचिन्हित दीर्घ *) ksp;
	पूर्ण

	unwind_stack(trace, sp, save_stack_address_nosched);

	put_task_stack(tsk);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);

व्योम
save_stack_trace_regs(काष्ठा pt_regs *regs, काष्ठा stack_trace *trace)
अणु
	unwind_stack(trace, (अचिन्हित दीर्घ *) regs->sp,
		     save_stack_address_nosched);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_regs);
