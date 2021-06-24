<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Stack trace management functions
 *
 *  Copyright (C) 2006 Atsushi Nemoto <anemo@mba.ocn.ne.jp>
 */
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/stacktrace.h>

/*
 * Save stack-backtrace addresses पूर्णांकo a stack_trace buffer:
 */
अटल व्योम save_raw_context_stack(काष्ठा stack_trace *trace,
	अचिन्हित दीर्घ reg29, पूर्णांक savesched)
अणु
	अचिन्हित दीर्घ *sp = (अचिन्हित दीर्घ *)reg29;
	अचिन्हित दीर्घ addr;

	जबतक (!kstack_end(sp)) अणु
		addr = *sp++;
		अगर (__kernel_text_address(addr) &&
		    (savesched || !in_sched_functions(addr))) अणु
			अगर (trace->skip > 0)
				trace->skip--;
			अन्यथा
				trace->entries[trace->nr_entries++] = addr;
			अगर (trace->nr_entries >= trace->max_entries)
				अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम save_context_stack(काष्ठा stack_trace *trace,
	काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs, पूर्णांक savesched)
अणु
	अचिन्हित दीर्घ sp = regs->regs[29];
#अगर_घोषित CONFIG_KALLSYMS
	अचिन्हित दीर्घ ra = regs->regs[31];
	अचिन्हित दीर्घ pc = regs->cp0_epc;

	अगर (raw_show_trace || !__kernel_text_address(pc)) अणु
		अचिन्हित दीर्घ stack_page =
			(अचिन्हित दीर्घ)task_stack_page(tsk);
		अगर (stack_page && sp >= stack_page &&
		    sp <= stack_page + THREAD_SIZE - 32)
			save_raw_context_stack(trace, sp, savesched);
		वापस;
	पूर्ण
	करो अणु
		अगर (savesched || !in_sched_functions(pc)) अणु
			अगर (trace->skip > 0)
				trace->skip--;
			अन्यथा
				trace->entries[trace->nr_entries++] = pc;
			अगर (trace->nr_entries >= trace->max_entries)
				अवरोध;
		पूर्ण
		pc = unwind_stack(tsk, &sp, pc, &ra);
	पूर्ण जबतक (pc);
#अन्यथा
	save_raw_context_stack(trace, sp, savesched);
#पूर्ण_अगर
पूर्ण

/*
 * Save stack-backtrace addresses पूर्णांकo a stack_trace buffer.
 */
व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	save_stack_trace_tsk(current, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	काष्ठा pt_regs dummyregs;
	काष्ठा pt_regs *regs = &dummyregs;

	WARN_ON(trace->nr_entries || !trace->max_entries);

	अगर (tsk != current) अणु
		regs->regs[29] = tsk->thपढ़ो.reg29;
		regs->regs[31] = 0;
		regs->cp0_epc = tsk->thपढ़ो.reg31;
	पूर्ण अन्यथा
		prepare_frametrace(regs);
	save_context_stack(trace, tsk, regs, tsk == current);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);
