<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (C) 2001 - 2007 Jeff Dike (jdike@अणुaddtoit,linux.पूर्णांकelपूर्ण.com)
 * Copyright (C) 2013 Riअक्षरd Weinberger <riअक्षरd@nod.at>
 * Copyright (C) 2014 Google Inc., Author: Daniel Walter <dwalter@google.com>
 */

#समावेश <linux/kallsyms.h>
#समावेश <linux/kernel.h>
#समावेश <linux/sched.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/module.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/stacktrace.h>

व्योम dump_trace(काष्ठा task_काष्ठा *tsk,
		स्थिर काष्ठा stacktrace_ops *ops,
		व्योम *data)
अणु
	पूर्णांक reliable = 0;
	अचिन्हित दीर्घ *sp, bp, addr;
	काष्ठा pt_regs *segv_regs = tsk->thपढ़ो.segv_regs;
	काष्ठा stack_frame *frame;

	bp = get_frame_poपूर्णांकer(tsk, segv_regs);
	sp = get_stack_poपूर्णांकer(tsk, segv_regs);

	frame = (काष्ठा stack_frame *)bp;
	जबतक (((दीर्घ) sp & (THREAD_SIZE-1)) != 0) अणु
		addr = *sp;
		अगर (__kernel_text_address(addr)) अणु
			reliable = 0;
			अगर ((अचिन्हित दीर्घ) sp == bp + माप(दीर्घ)) अणु
				frame = frame ? frame->next_frame : शून्य;
				bp = (अचिन्हित दीर्घ)frame;
				reliable = 1;
			पूर्ण
			ops->address(data, addr, reliable);
		पूर्ण
		sp++;
	पूर्ण
पूर्ण

अटल व्योम save_addr(व्योम *data, अचिन्हित दीर्घ address, पूर्णांक reliable)
अणु
	काष्ठा stack_trace *trace = data;

	अगर (!reliable)
		वापस;
	अगर (trace->nr_entries >= trace->max_entries)
		वापस;

	trace->entries[trace->nr_entries++] = address;
पूर्ण

अटल स्थिर काष्ठा stacktrace_ops dump_ops = अणु
	.address = save_addr
पूर्ण;

अटल व्योम __save_stack_trace(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	dump_trace(tsk, &dump_ops, trace);
पूर्ण

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	__save_stack_trace(current, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	__save_stack_trace(tsk, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);
