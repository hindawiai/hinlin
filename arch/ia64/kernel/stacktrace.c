<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * arch/ia64/kernel/stacktrace.c
 *
 * Stack trace management functions
 *
 */
#समावेश <linux/sched.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/module.h>

अटल व्योम
ia64_करो_save_stack(काष्ठा unw_frame_info *info, व्योम *arg)
अणु
	काष्ठा stack_trace *trace = arg;
	अचिन्हित दीर्घ ip;
	पूर्णांक skip = trace->skip;

	trace->nr_entries = 0;
	करो अणु
		unw_get_ip(info, &ip);
		अगर (ip == 0)
			अवरोध;
		अगर (skip == 0) अणु
			trace->entries[trace->nr_entries++] = ip;
			अगर (trace->nr_entries == trace->max_entries)
				अवरोध;
		पूर्ण अन्यथा
			skip--;
	पूर्ण जबतक (unw_unwind(info) >= 0);
पूर्ण

/*
 * Save stack-backtrace addresses पूर्णांकo a stack_trace buffer.
 */
व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	unw_init_running(ia64_करो_save_stack, trace);
पूर्ण
EXPORT_SYMBOL(save_stack_trace);
