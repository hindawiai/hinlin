<शैली गुरु>
/*
 * Kernel and userspace stack tracing.
 *
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 2001 - 2013 Tensilica Inc.
 * Copyright (C) 2015 Cadence Design Systems Inc.
 */
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/stacktrace.h>

#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/traps.h>
#समावेश <linux/uaccess.h>

#अगर IS_ENABLED(CONFIG_PERF_EVENTS)

/* Address of common_exception_वापस, used to check the
 * transition from kernel to user space.
 */
बाह्य पूर्णांक common_exception_वापस;

व्योम xtensa_backtrace_user(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक depth,
			   पूर्णांक (*ufn)(काष्ठा stackframe *frame, व्योम *data),
			   व्योम *data)
अणु
	अचिन्हित दीर्घ winकरोwstart = regs->winकरोwstart;
	अचिन्हित दीर्घ winकरोwbase = regs->winकरोwbase;
	अचिन्हित दीर्घ a0 = regs->areg[0];
	अचिन्हित दीर्घ a1 = regs->areg[1];
	अचिन्हित दीर्घ pc = regs->pc;
	काष्ठा stackframe frame;
	पूर्णांक index;

	अगर (!depth--)
		वापस;

	frame.pc = pc;
	frame.sp = a1;

	अगर (pc == 0 || pc >= TASK_SIZE || ufn(&frame, data))
		वापस;

	अगर (IS_ENABLED(CONFIG_USER_ABI_CALL0_ONLY) ||
	    (IS_ENABLED(CONFIG_USER_ABI_CALL0_PROBE) &&
	     !(regs->ps & PS_WOE_MASK)))
		वापस;

	/* Two steps:
	 *
	 * 1. Look through the रेजिस्टर winकरोw क्रम the
	 * previous PCs in the call trace.
	 *
	 * 2. Look on the stack.
	 */

	/* Step 1.  */
	/* Rotate WINDOWSTART to move the bit corresponding to
	 * the current winकरोw to the bit #0.
	 */
	winकरोwstart = (winकरोwstart << WSBITS | winकरोwstart) >> winकरोwbase;

	/* Look क्रम bits that are set, they correspond to
	 * valid winकरोws.
	 */
	क्रम (index = WSBITS - 1; (index > 0) && depth; depth--, index--)
		अगर (winकरोwstart & (1 << index)) अणु
			/* Get the PC from a0 and a1. */
			pc = MAKE_PC_FROM_RA(a0, pc);
			/* Read a0 and a1 from the
			 * corresponding position in AREGs.
			 */
			a0 = regs->areg[index * 4];
			a1 = regs->areg[index * 4 + 1];

			frame.pc = pc;
			frame.sp = a1;

			अगर (pc == 0 || pc >= TASK_SIZE || ufn(&frame, data))
				वापस;
		पूर्ण

	/* Step 2. */
	/* We are करोne with the रेजिस्टर winकरोw, we need to
	 * look through the stack.
	 */
	अगर (!depth)
		वापस;

	/* Start from the a1 रेजिस्टर. */
	/* a1 = regs->areg[1]; */
	जबतक (a0 != 0 && depth--) अणु
		pc = MAKE_PC_FROM_RA(a0, pc);

		/* Check अगर the region is OK to access. */
		अगर (!access_ok(&SPILL_SLOT(a1, 0), 8))
			वापस;
		/* Copy a1, a0 from user space stack frame. */
		अगर (__get_user(a0, &SPILL_SLOT(a1, 0)) ||
		    __get_user(a1, &SPILL_SLOT(a1, 1)))
			वापस;

		frame.pc = pc;
		frame.sp = a1;

		अगर (pc == 0 || pc >= TASK_SIZE || ufn(&frame, data))
			वापस;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(xtensa_backtrace_user);

व्योम xtensa_backtrace_kernel(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक depth,
			     पूर्णांक (*kfn)(काष्ठा stackframe *frame, व्योम *data),
			     पूर्णांक (*ufn)(काष्ठा stackframe *frame, व्योम *data),
			     व्योम *data)
अणु
	अचिन्हित दीर्घ pc = regs->depc > VALID_DOUBLE_EXCEPTION_ADDRESS ?
		regs->depc : regs->pc;
	अचिन्हित दीर्घ sp_start, sp_end;
	अचिन्हित दीर्घ a0 = regs->areg[0];
	अचिन्हित दीर्घ a1 = regs->areg[1];

	sp_start = a1 & ~(THREAD_SIZE - 1);
	sp_end = sp_start + THREAD_SIZE;

	/* Spill the रेजिस्टर winकरोw to the stack first. */
	spill_रेजिस्टरs();

	/* Read the stack frames one by one and create the PC
	 * from the a0 and a1 रेजिस्टरs saved there.
	 */
	जबतक (a1 > sp_start && a1 < sp_end && depth--) अणु
		काष्ठा stackframe frame;

		frame.pc = pc;
		frame.sp = a1;

		अगर (kernel_text_address(pc) && kfn(&frame, data))
			वापस;

		अगर (pc == (अचिन्हित दीर्घ)&common_exception_वापस) अणु
			regs = (काष्ठा pt_regs *)a1;
			अगर (user_mode(regs)) अणु
				अगर (ufn == शून्य)
					वापस;
				xtensa_backtrace_user(regs, depth, ufn, data);
				वापस;
			पूर्ण
			a0 = regs->areg[0];
			a1 = regs->areg[1];
			जारी;
		पूर्ण

		sp_start = a1;

		pc = MAKE_PC_FROM_RA(a0, pc);
		a0 = SPILL_SLOT(a1, 0);
		a1 = SPILL_SLOT(a1, 1);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(xtensa_backtrace_kernel);

#पूर्ण_अगर

व्योम walk_stackframe(अचिन्हित दीर्घ *sp,
		पूर्णांक (*fn)(काष्ठा stackframe *frame, व्योम *data),
		व्योम *data)
अणु
	अचिन्हित दीर्घ a0, a1;
	अचिन्हित दीर्घ sp_end;

	a1 = (अचिन्हित दीर्घ)sp;
	sp_end = ALIGN(a1, THREAD_SIZE);

	spill_रेजिस्टरs();

	जबतक (a1 < sp_end) अणु
		काष्ठा stackframe frame;

		sp = (अचिन्हित दीर्घ *)a1;

		a0 = SPILL_SLOT(a1, 0);
		a1 = SPILL_SLOT(a1, 1);

		अगर (a1 <= (अचिन्हित दीर्घ)sp)
			अवरोध;

		frame.pc = MAKE_PC_FROM_RA(a0, a1);
		frame.sp = a1;

		अगर (fn(&frame, data))
			वापस;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE

काष्ठा stack_trace_data अणु
	काष्ठा stack_trace *trace;
	अचिन्हित skip;
पूर्ण;

अटल पूर्णांक stack_trace_cb(काष्ठा stackframe *frame, व्योम *data)
अणु
	काष्ठा stack_trace_data *trace_data = data;
	काष्ठा stack_trace *trace = trace_data->trace;

	अगर (trace_data->skip) अणु
		--trace_data->skip;
		वापस 0;
	पूर्ण
	अगर (!kernel_text_address(frame->pc))
		वापस 0;

	trace->entries[trace->nr_entries++] = frame->pc;
	वापस trace->nr_entries >= trace->max_entries;
पूर्ण

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *task, काष्ठा stack_trace *trace)
अणु
	काष्ठा stack_trace_data trace_data = अणु
		.trace = trace,
		.skip = trace->skip,
	पूर्ण;
	walk_stackframe(stack_poपूर्णांकer(task), stack_trace_cb, &trace_data);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	save_stack_trace_tsk(current, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

#पूर्ण_अगर

#अगर_घोषित CONFIG_FRAME_POINTER

काष्ठा वापस_addr_data अणु
	अचिन्हित दीर्घ addr;
	अचिन्हित skip;
पूर्ण;

अटल पूर्णांक वापस_address_cb(काष्ठा stackframe *frame, व्योम *data)
अणु
	काष्ठा वापस_addr_data *r = data;

	अगर (r->skip) अणु
		--r->skip;
		वापस 0;
	पूर्ण
	अगर (!kernel_text_address(frame->pc))
		वापस 0;
	r->addr = frame->pc;
	वापस 1;
पूर्ण

/*
 * level == 0 is क्रम the वापस address from the caller of this function,
 * not from this function itself.
 */
अचिन्हित दीर्घ वापस_address(अचिन्हित level)
अणु
	काष्ठा वापस_addr_data r = अणु
		.skip = level,
	पूर्ण;
	walk_stackframe(stack_poपूर्णांकer(शून्य), वापस_address_cb, &r);
	वापस r.addr;
पूर्ण
EXPORT_SYMBOL(वापस_address);

#पूर्ण_अगर
