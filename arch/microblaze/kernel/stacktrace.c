<शैली गुरु>
/*
 * Stack trace support क्रम Microblaze.
 *
 * Copyright (C) 2009 Michal Simek <monstr@monstr.eu>
 * Copyright (C) 2009 PetaLogix
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License. See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 */

#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <linux/ptrace.h>
#समावेश <यंत्र/unwind.h>

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	/* Exclude our helper functions from the trace*/
	trace->skip += 2;
	microblaze_unwind(शून्य, trace, "");
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	microblaze_unwind(tsk, trace, "");
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);
