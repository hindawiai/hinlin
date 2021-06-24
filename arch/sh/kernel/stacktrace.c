<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/sh/kernel/stacktrace.c
 *
 * Stack trace management functions
 *
 *  Copyright (C) 2006 - 2008  Paul Mundt
 */
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/module.h>
#समावेश <यंत्र/unwinder.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/stacktrace.h>

/*
 * Save stack-backtrace addresses पूर्णांकo a stack_trace buffer.
 */
अटल व्योम save_stack_address(व्योम *data, अचिन्हित दीर्घ addr, पूर्णांक reliable)
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

अटल स्थिर काष्ठा stacktrace_ops save_stack_ops = अणु
	.address = save_stack_address,
पूर्ण;

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	अचिन्हित दीर्घ *sp = (अचिन्हित दीर्घ *)current_stack_poपूर्णांकer;

	unwind_stack(current, शून्य, sp,  &save_stack_ops, trace);
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

अटल स्थिर काष्ठा stacktrace_ops save_stack_ops_nosched = अणु
	.address = save_stack_address_nosched,
पूर्ण;

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	अचिन्हित दीर्घ *sp = (अचिन्हित दीर्घ *)tsk->thपढ़ो.sp;

	unwind_stack(current, शून्य, sp,  &save_stack_ops_nosched, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);
