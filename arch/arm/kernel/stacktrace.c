<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
#समावेश <linux/export.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/stacktrace.h>

#समावेश <यंत्र/sections.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/traps.h>

#अगर defined(CONFIG_FRAME_POINTER) && !defined(CONFIG_ARM_UNWIND)
/*
 * Unwind the current stack frame and store the new रेजिस्टर values in the
 * काष्ठाure passed as argument. Unwinding is equivalent to a function वापस,
 * hence the new PC value rather than LR should be used क्रम backtrace.
 *
 * With framepoपूर्णांकer enabled, a simple function prologue looks like this:
 *	mov	ip, sp
 *	sपंचांगdb	sp!, अणुfp, ip, lr, pcपूर्ण
 *	sub	fp, ip, #4
 *
 * A simple function epilogue looks like this:
 *	ldm	sp, अणुfp, sp, pcपूर्ण
 *
 * When compiled with clang, pc and sp are not pushed. A simple function
 * prologue looks like this when built with clang:
 *
 *	sपंचांगdb	अणु..., fp, lrपूर्ण
 *	add	fp, sp, #x
 *	sub	sp, sp, #y
 *
 * A simple function epilogue looks like this when built with clang:
 *
 *	sub	sp, fp, #x
 *	ldm	अणु..., fp, pcपूर्ण
 *
 *
 * Note that with framepoपूर्णांकer enabled, even the leaf functions have the same
 * prologue and epilogue, thereक्रमe we can ignore the LR value in this हाल.
 */
पूर्णांक notrace unwind_frame(काष्ठा stackframe *frame)
अणु
	अचिन्हित दीर्घ high, low;
	अचिन्हित दीर्घ fp = frame->fp;

	/* only go to a higher address on the stack */
	low = frame->sp;
	high = ALIGN(low, THREAD_SIZE);

#अगर_घोषित CONFIG_CC_IS_CLANG
	/* check current frame poपूर्णांकer is within bounds */
	अगर (fp < low + 4 || fp > high - 4)
		वापस -EINVAL;

	frame->sp = frame->fp;
	frame->fp = *(अचिन्हित दीर्घ *)(fp);
	frame->pc = frame->lr;
	frame->lr = *(अचिन्हित दीर्घ *)(fp + 4);
#अन्यथा
	/* check current frame poपूर्णांकer is within bounds */
	अगर (fp < low + 12 || fp > high - 4)
		वापस -EINVAL;

	/* restore the रेजिस्टरs from the stack frame */
	frame->fp = *(अचिन्हित दीर्घ *)(fp - 12);
	frame->sp = *(अचिन्हित दीर्घ *)(fp - 8);
	frame->pc = *(अचिन्हित दीर्घ *)(fp - 4);
#पूर्ण_अगर

	वापस 0;
पूर्ण
#पूर्ण_अगर

व्योम notrace walk_stackframe(काष्ठा stackframe *frame,
		     पूर्णांक (*fn)(काष्ठा stackframe *, व्योम *), व्योम *data)
अणु
	जबतक (1) अणु
		पूर्णांक ret;

		अगर (fn(frame, data))
			अवरोध;
		ret = unwind_frame(frame);
		अगर (ret < 0)
			अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(walk_stackframe);

#अगर_घोषित CONFIG_STACKTRACE
काष्ठा stack_trace_data अणु
	काष्ठा stack_trace *trace;
	अचिन्हित पूर्णांक no_sched_functions;
	अचिन्हित पूर्णांक skip;
पूर्ण;

अटल पूर्णांक save_trace(काष्ठा stackframe *frame, व्योम *d)
अणु
	काष्ठा stack_trace_data *data = d;
	काष्ठा stack_trace *trace = data->trace;
	काष्ठा pt_regs *regs;
	अचिन्हित दीर्घ addr = frame->pc;

	अगर (data->no_sched_functions && in_sched_functions(addr))
		वापस 0;
	अगर (data->skip) अणु
		data->skip--;
		वापस 0;
	पूर्ण

	trace->entries[trace->nr_entries++] = addr;

	अगर (trace->nr_entries >= trace->max_entries)
		वापस 1;

	अगर (!in_entry_text(frame->pc))
		वापस 0;

	regs = (काष्ठा pt_regs *)frame->sp;
	अगर ((अचिन्हित दीर्घ)&regs[1] > ALIGN(frame->sp, THREAD_SIZE))
		वापस 0;

	trace->entries[trace->nr_entries++] = regs->ARM_pc;

	वापस trace->nr_entries >= trace->max_entries;
पूर्ण

/* This must be noअंतरभूत to so that our skip calculation works correctly */
अटल noअंतरभूत व्योम __save_stack_trace(काष्ठा task_काष्ठा *tsk,
	काष्ठा stack_trace *trace, अचिन्हित पूर्णांक nosched)
अणु
	काष्ठा stack_trace_data data;
	काष्ठा stackframe frame;

	data.trace = trace;
	data.skip = trace->skip;
	data.no_sched_functions = nosched;

	अगर (tsk != current) अणु
#अगर_घोषित CONFIG_SMP
		/*
		 * What guarantees करो we have here that 'tsk' is not
		 * running on another CPU?  For now, ignore it as we
		 * can't guarantee we won't explode.
		 */
		वापस;
#अन्यथा
		frame.fp = thपढ़ो_saved_fp(tsk);
		frame.sp = thपढ़ो_saved_sp(tsk);
		frame.lr = 0;		/* recovered from the stack */
		frame.pc = thपढ़ो_saved_pc(tsk);
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		/* We करोn't want this function nor the caller */
		data.skip += 2;
		frame.fp = (अचिन्हित दीर्घ)__builtin_frame_address(0);
		frame.sp = current_stack_poपूर्णांकer;
		frame.lr = (अचिन्हित दीर्घ)__builtin_वापस_address(0);
		frame.pc = (अचिन्हित दीर्घ)__save_stack_trace;
	पूर्ण

	walk_stackframe(&frame, save_trace, &data);
पूर्ण

व्योम save_stack_trace_regs(काष्ठा pt_regs *regs, काष्ठा stack_trace *trace)
अणु
	काष्ठा stack_trace_data data;
	काष्ठा stackframe frame;

	data.trace = trace;
	data.skip = trace->skip;
	data.no_sched_functions = 0;

	frame.fp = regs->ARM_fp;
	frame.sp = regs->ARM_sp;
	frame.lr = regs->ARM_lr;
	frame.pc = regs->ARM_pc;

	walk_stackframe(&frame, save_trace, &data);
पूर्ण

व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	__save_stack_trace(tsk, trace, 1);
पूर्ण
EXPORT_SYMBOL(save_stack_trace_tsk);

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	__save_stack_trace(current, trace, 0);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);
#पूर्ण_अगर
