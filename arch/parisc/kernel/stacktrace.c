<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Stack trace management functions
 *
 *  Copyright (C) 2009 Helge Deller <deller@gmx.de>
 *  based on arch/x86/kernel/stacktrace.c by Ingo Molnar <mingo@redhat.com>
 *  and parisc unwind functions by Ranकरोlph Chung <tausq@debian.org>
 *
 *  TODO: Userspace stacktrace (CONFIG_USER_STACKTRACE_SUPPORT)
 */
#समावेश <linux/module.h>
#समावेश <linux/stacktrace.h>

#समावेश <यंत्र/unwind.h>

अटल व्योम dump_trace(काष्ठा task_काष्ठा *task, काष्ठा stack_trace *trace)
अणु
	काष्ठा unwind_frame_info info;

	unwind_frame_init_task(&info, task, शून्य);

	/* unwind stack and save entries in stack_trace काष्ठा */
	trace->nr_entries = 0;
	जबतक (trace->nr_entries < trace->max_entries) अणु
		अगर (unwind_once(&info) < 0 || info.ip == 0)
			अवरोध;

		अगर (__kernel_text_address(info.ip))
			trace->entries[trace->nr_entries++] = info.ip;
	पूर्ण
पूर्ण

/*
 * Save stack-backtrace addresses पूर्णांकo a stack_trace buffer.
 */
व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	dump_trace(current, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	dump_trace(tsk, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);
