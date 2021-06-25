<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/export.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/stacktrace.h>

#समावेश "kstack.h"

अटल व्योम __save_stack_trace(काष्ठा thपढ़ो_info *tp,
			       काष्ठा stack_trace *trace,
			       bool skip_sched)
अणु
	अचिन्हित दीर्घ ksp, fp;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	काष्ठा task_काष्ठा *t;
	पूर्णांक graph = 0;
#पूर्ण_अगर

	अगर (tp == current_thपढ़ो_info()) अणु
		stack_trace_flush();
		__यंत्र__ __अस्थिर__("mov %%fp, %0" : "=r" (ksp));
	पूर्ण अन्यथा अणु
		ksp = tp->ksp;
	पूर्ण

	fp = ksp + STACK_BIAS;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	t = tp->task;
#पूर्ण_अगर
	करो अणु
		काष्ठा sparc_stackf *sf;
		काष्ठा pt_regs *regs;
		अचिन्हित दीर्घ pc;

		अगर (!kstack_valid(tp, fp))
			अवरोध;

		sf = (काष्ठा sparc_stackf *) fp;
		regs = (काष्ठा pt_regs *) (sf + 1);

		अगर (kstack_is_trap_frame(tp, regs)) अणु
			अगर (!(regs->tstate & TSTATE_PRIV))
				अवरोध;
			pc = regs->tpc;
			fp = regs->u_regs[UREG_I6] + STACK_BIAS;
		पूर्ण अन्यथा अणु
			pc = sf->callers_pc;
			fp = (अचिन्हित दीर्घ)sf->fp + STACK_BIAS;
		पूर्ण

		अगर (trace->skip > 0)
			trace->skip--;
		अन्यथा अगर (!skip_sched || !in_sched_functions(pc)) अणु
			trace->entries[trace->nr_entries++] = pc;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
			अगर ((pc + 8UL) == (अचिन्हित दीर्घ) &वापस_to_handler) अणु
				काष्ठा ftrace_ret_stack *ret_stack;
				ret_stack = ftrace_graph_get_ret_stack(t,
								       graph);
				अगर (ret_stack) अणु
					pc = ret_stack->ret;
					अगर (trace->nr_entries <
					    trace->max_entries)
						trace->entries[trace->nr_entries++] = pc;
					graph++;
				पूर्ण
			पूर्ण
#पूर्ण_अगर
		पूर्ण
	पूर्ण जबतक (trace->nr_entries < trace->max_entries);
पूर्ण

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	__save_stack_trace(current_thपढ़ो_info(), trace, false);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	काष्ठा thपढ़ो_info *tp = task_thपढ़ो_info(tsk);

	__save_stack_trace(tp, trace, true);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);
