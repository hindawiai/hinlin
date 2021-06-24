<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Stack tracing support
 *
 * Copyright (C) 2012 ARM Ltd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/export.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>

#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/poपूर्णांकer_auth.h>
#समावेश <यंत्र/stack_poपूर्णांकer.h>
#समावेश <यंत्र/stacktrace.h>

/*
 * AArch64 PCS assigns the frame poपूर्णांकer to x29.
 *
 * A simple function prologue looks like this:
 * 	sub	sp, sp, #0x10
 *   	stp	x29, x30, [sp]
 *	mov	x29, sp
 *
 * A simple function epilogue looks like this:
 *	mov	sp, x29
 *	ldp	x29, x30, [sp]
 *	add	sp, sp, #0x10
 */


व्योम start_backtrace(काष्ठा stackframe *frame, अचिन्हित दीर्घ fp,
		     अचिन्हित दीर्घ pc)
अणु
	frame->fp = fp;
	frame->pc = pc;
#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	frame->graph = 0;
#पूर्ण_अगर

	/*
	 * Prime the first unwind.
	 *
	 * In unwind_frame() we'll check that the FP poपूर्णांकs to a valid stack,
	 * which can't be STACK_TYPE_UNKNOWN, and the first unwind will be
	 * treated as a transition to whichever stack that happens to be. The
	 * prev_fp value won't be used, but we set it to 0 such that it is
	 * definitely not an accessible stack address.
	 */
	biपंचांगap_zero(frame->stacks_करोne, __NR_STACK_TYPES);
	frame->prev_fp = 0;
	frame->prev_type = STACK_TYPE_UNKNOWN;
पूर्ण

/*
 * Unwind from one frame record (A) to the next frame record (B).
 *
 * We terminate early अगर the location of B indicates a malक्रमmed chain of frame
 * records (e.g. a cycle), determined based on the location and fp value of A
 * and the location (but not the fp value) of B.
 */
पूर्णांक notrace unwind_frame(काष्ठा task_काष्ठा *tsk, काष्ठा stackframe *frame)
अणु
	अचिन्हित दीर्घ fp = frame->fp;
	काष्ठा stack_info info;

	अगर (fp & 0xf)
		वापस -EINVAL;

	अगर (!tsk)
		tsk = current;

	अगर (!on_accessible_stack(tsk, fp, &info))
		वापस -EINVAL;

	अगर (test_bit(info.type, frame->stacks_करोne))
		वापस -EINVAL;

	/*
	 * As stacks grow करोwnward, any valid record on the same stack must be
	 * at a strictly higher address than the prior record.
	 *
	 * Stacks can nest in several valid orders, e.g.
	 *
	 * TASK -> IRQ -> OVERFLOW -> SDEI_NORMAL
	 * TASK -> SDEI_NORMAL -> SDEI_CRITICAL -> OVERFLOW
	 *
	 * ... but the nesting itself is strict. Once we transition from one
	 * stack to another, it's never valid to unwind back to that first
	 * stack.
	 */
	अगर (info.type == frame->prev_type) अणु
		अगर (fp <= frame->prev_fp)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		set_bit(frame->prev_type, frame->stacks_करोne);
	पूर्ण

	/*
	 * Record this frame record's values and location. The prev_fp and
	 * prev_type are only meaningful to the next unwind_frame() invocation.
	 */
	frame->fp = READ_ONCE_NOCHECK(*(अचिन्हित दीर्घ *)(fp));
	frame->pc = READ_ONCE_NOCHECK(*(अचिन्हित दीर्घ *)(fp + 8));
	frame->prev_fp = fp;
	frame->prev_type = info.type;

#अगर_घोषित CONFIG_FUNCTION_GRAPH_TRACER
	अगर (tsk->ret_stack &&
		(ptrauth_strip_insn_pac(frame->pc) == (अचिन्हित दीर्घ)वापस_to_handler)) अणु
		काष्ठा ftrace_ret_stack *ret_stack;
		/*
		 * This is a हाल where function graph tracer has
		 * modअगरied a वापस address (LR) in a stack frame
		 * to hook a function वापस.
		 * So replace it to an original value.
		 */
		ret_stack = ftrace_graph_get_ret_stack(tsk, frame->graph++);
		अगर (WARN_ON_ONCE(!ret_stack))
			वापस -EINVAL;
		frame->pc = ret_stack->ret;
	पूर्ण
#पूर्ण_अगर /* CONFIG_FUNCTION_GRAPH_TRACER */

	frame->pc = ptrauth_strip_insn_pac(frame->pc);

	/*
	 * This is a terminal record, so we have finished unwinding.
	 */
	अगर (!frame->fp && !frame->pc)
		वापस -ENOENT;

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(unwind_frame);

व्योम notrace walk_stackframe(काष्ठा task_काष्ठा *tsk, काष्ठा stackframe *frame,
			     bool (*fn)(व्योम *, अचिन्हित दीर्घ), व्योम *data)
अणु
	जबतक (1) अणु
		पूर्णांक ret;

		अगर (!fn(data, frame->pc))
			अवरोध;
		ret = unwind_frame(tsk, frame);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(walk_stackframe);

अटल व्योम dump_backtrace_entry(अचिन्हित दीर्घ where, स्थिर अक्षर *loglvl)
अणु
	prपूर्णांकk("%s %pS\n", loglvl, (व्योम *)where);
पूर्ण

व्योम dump_backtrace(काष्ठा pt_regs *regs, काष्ठा task_काष्ठा *tsk,
		    स्थिर अक्षर *loglvl)
अणु
	काष्ठा stackframe frame;
	पूर्णांक skip = 0;

	pr_debug("%s(regs = %p tsk = %p)\n", __func__, regs, tsk);

	अगर (regs) अणु
		अगर (user_mode(regs))
			वापस;
		skip = 1;
	पूर्ण

	अगर (!tsk)
		tsk = current;

	अगर (!try_get_task_stack(tsk))
		वापस;

	अगर (tsk == current) अणु
		start_backtrace(&frame,
				(अचिन्हित दीर्घ)__builtin_frame_address(0),
				(अचिन्हित दीर्घ)dump_backtrace);
	पूर्ण अन्यथा अणु
		/*
		 * task blocked in __चयन_to
		 */
		start_backtrace(&frame,
				thपढ़ो_saved_fp(tsk),
				thपढ़ो_saved_pc(tsk));
	पूर्ण

	prपूर्णांकk("%sCall trace:\n", loglvl);
	करो अणु
		/* skip until specअगरied stack frame */
		अगर (!skip) अणु
			dump_backtrace_entry(frame.pc, loglvl);
		पूर्ण अन्यथा अगर (frame.fp == regs->regs[29]) अणु
			skip = 0;
			/*
			 * Mostly, this is the हाल where this function is
			 * called in panic/पात. As exception handler's
			 * stack frame करोes not contain the corresponding pc
			 * at which an exception has taken place, use regs->pc
			 * instead.
			 */
			dump_backtrace_entry(regs->pc, loglvl);
		पूर्ण
	पूर्ण जबतक (!unwind_frame(tsk, &frame));

	put_task_stack(tsk);
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	dump_backtrace(शून्य, tsk, loglvl);
	barrier();
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE

noअंतरभूत व्योम arch_stack_walk(stack_trace_consume_fn consume_entry,
			      व्योम *cookie, काष्ठा task_काष्ठा *task,
			      काष्ठा pt_regs *regs)
अणु
	काष्ठा stackframe frame;

	अगर (regs)
		start_backtrace(&frame, regs->regs[29], regs->pc);
	अन्यथा अगर (task == current)
		start_backtrace(&frame,
				(अचिन्हित दीर्घ)__builtin_frame_address(1),
				(अचिन्हित दीर्घ)__builtin_वापस_address(0));
	अन्यथा
		start_backtrace(&frame, thपढ़ो_saved_fp(task),
				thपढ़ो_saved_pc(task));

	walk_stackframe(task, &frame, consume_entry, cookie);
पूर्ण

#पूर्ण_अगर
