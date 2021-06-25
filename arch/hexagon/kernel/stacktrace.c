<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Stacktrace support क्रम Hexagon
 *
 * Copyright (c) 2010-2011, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/sched.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/module.h>

काष्ठा stackframe अणु
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ rets;
पूर्ण;

/*
 * Save stack-backtrace addresses पूर्णांकo a stack_trace buffer.
 */
व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	अचिन्हित दीर्घ low, high;
	अचिन्हित दीर्घ fp;
	काष्ठा stackframe *frame;
	पूर्णांक skip = trace->skip;

	low = (अचिन्हित दीर्घ)task_stack_page(current);
	high = low + THREAD_SIZE;
	fp = (अचिन्हित दीर्घ)__builtin_frame_address(0);

	जबतक (fp >= low && fp <= (high - माप(*frame))) अणु
		frame = (काष्ठा stackframe *)fp;

		अगर (skip) अणु
			skip--;
		पूर्ण अन्यथा अणु
			trace->entries[trace->nr_entries++] = frame->rets;
			अगर (trace->nr_entries >= trace->max_entries)
				अवरोध;
		पूर्ण

		/*
		 * The next frame must be at a higher address than the
		 * current frame.
		 */
		low = fp + माप(*frame);
		fp = frame->fp;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);
