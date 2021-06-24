<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
// Copyright (C) 2005-2017 Andes Technology Corporation

#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/ftrace.h>

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	save_stack_trace_tsk(current, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	अचिन्हित दीर्घ *fpn;
	पूर्णांक skip = trace->skip;
	पूर्णांक savesched;
	पूर्णांक graph_idx = 0;

	अगर (tsk == current) अणु
		__यंत्र__ __अस्थिर__("\tori\t%0, $fp, #0\n":"=r"(fpn));
		savesched = 1;
	पूर्ण अन्यथा अणु
		fpn = (अचिन्हित दीर्घ *)thपढ़ो_saved_fp(tsk);
		savesched = 0;
	पूर्ण

	जबतक (!kstack_end(fpn) && !((अचिन्हित दीर्घ)fpn & 0x3)
	       && (fpn >= (अचिन्हित दीर्घ *)TASK_SIZE)) अणु
		अचिन्हित दीर्घ lpp, fpp;

		lpp = fpn[LP_OFFSET];
		fpp = fpn[FP_OFFSET];
		अगर (!__kernel_text_address(lpp))
			अवरोध;
		अन्यथा
			lpp = ftrace_graph_ret_addr(tsk, &graph_idx, lpp, शून्य);

		अगर (savesched || !in_sched_functions(lpp)) अणु
			अगर (skip) अणु
				skip--;
			पूर्ण अन्यथा अणु
				trace->entries[trace->nr_entries++] = lpp;
				अगर (trace->nr_entries >= trace->max_entries)
					अवरोध;
			पूर्ण
		पूर्ण
		fpn = (अचिन्हित दीर्घ *)fpp;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);
