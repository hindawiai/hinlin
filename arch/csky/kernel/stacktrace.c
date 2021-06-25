<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0

#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/ptrace.h>

#अगर_घोषित CONFIG_FRAME_POINTER

काष्ठा stackframe अणु
	अचिन्हित दीर्घ fp;
	अचिन्हित दीर्घ ra;
पूर्ण;

व्योम notrace walk_stackframe(काष्ठा task_काष्ठा *task, काष्ठा pt_regs *regs,
			     bool (*fn)(अचिन्हित दीर्घ, व्योम *), व्योम *arg)
अणु
	अचिन्हित दीर्घ fp, sp, pc;

	अगर (regs) अणु
		fp = frame_poपूर्णांकer(regs);
		sp = user_stack_poपूर्णांकer(regs);
		pc = inकाष्ठाion_poपूर्णांकer(regs);
	पूर्ण अन्यथा अगर (task == शून्य || task == current) अणु
		स्थिर रेजिस्टर अचिन्हित दीर्घ current_sp __यंत्र__ ("sp");
		स्थिर रेजिस्टर अचिन्हित दीर्घ current_fp __यंत्र__ ("r8");
		fp = current_fp;
		sp = current_sp;
		pc = (अचिन्हित दीर्घ)walk_stackframe;
	पूर्ण अन्यथा अणु
		/* task blocked in __चयन_to */
		fp = thपढ़ो_saved_fp(task);
		sp = thपढ़ो_saved_sp(task);
		pc = thपढ़ो_saved_lr(task);
	पूर्ण

	क्रम (;;) अणु
		अचिन्हित दीर्घ low, high;
		काष्ठा stackframe *frame;

		अगर (unlikely(!__kernel_text_address(pc) || fn(pc, arg)))
			अवरोध;

		/* Validate frame poपूर्णांकer */
		low = sp;
		high = ALIGN(sp, THREAD_SIZE);
		अगर (unlikely(fp < low || fp > high || fp & 0x3))
			अवरोध;
		/* Unwind stack frame */
		frame = (काष्ठा stackframe *)fp;
		sp = fp;
		fp = frame->fp;
		pc = ftrace_graph_ret_addr(current, शून्य, frame->ra,
					   (अचिन्हित दीर्घ *)(fp - 8));
	पूर्ण
पूर्ण

#अन्यथा /* !CONFIG_FRAME_POINTER */

अटल व्योम notrace walk_stackframe(काष्ठा task_काष्ठा *task,
	काष्ठा pt_regs *regs, bool (*fn)(अचिन्हित दीर्घ, व्योम *), व्योम *arg)
अणु
	अचिन्हित दीर्घ sp, pc;
	अचिन्हित दीर्घ *ksp;

	अगर (regs) अणु
		sp = user_stack_poपूर्णांकer(regs);
		pc = inकाष्ठाion_poपूर्णांकer(regs);
	पूर्ण अन्यथा अगर (task == शून्य || task == current) अणु
		स्थिर रेजिस्टर अचिन्हित दीर्घ current_sp __यंत्र__ ("sp");
		sp = current_sp;
		pc = (अचिन्हित दीर्घ)walk_stackframe;
	पूर्ण अन्यथा अणु
		/* task blocked in __चयन_to */
		sp = thपढ़ो_saved_sp(task);
		pc = thपढ़ो_saved_lr(task);
	पूर्ण

	अगर (unlikely(sp & 0x3))
		वापस;

	ksp = (अचिन्हित दीर्घ *)sp;
	जबतक (!kstack_end(ksp)) अणु
		अगर (__kernel_text_address(pc) && unlikely(fn(pc, arg)))
			अवरोध;
		pc = (*ksp++) - 0x4;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_FRAME_POINTER */

अटल bool prपूर्णांक_trace_address(अचिन्हित दीर्घ pc, व्योम *arg)
अणु
	prपूर्णांक_ip_sym((स्थिर अक्षर *)arg, pc);
	वापस false;
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	pr_cont("Call Trace:\n");
	walk_stackframe(task, शून्य, prपूर्णांक_trace_address, (व्योम *)loglvl);
पूर्ण

अटल bool save_wchan(अचिन्हित दीर्घ pc, व्योम *arg)
अणु
	अगर (!in_sched_functions(pc)) अणु
		अचिन्हित दीर्घ *p = arg;
		*p = pc;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *task)
अणु
	अचिन्हित दीर्घ pc = 0;

	अगर (likely(task && task != current && task->state != TASK_RUNNING))
		walk_stackframe(task, शून्य, save_wchan, &pc);
	वापस pc;
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE
अटल bool __save_trace(अचिन्हित दीर्घ pc, व्योम *arg, bool nosched)
अणु
	काष्ठा stack_trace *trace = arg;

	अगर (unlikely(nosched && in_sched_functions(pc)))
		वापस false;
	अगर (unlikely(trace->skip > 0)) अणु
		trace->skip--;
		वापस false;
	पूर्ण

	trace->entries[trace->nr_entries++] = pc;
	वापस (trace->nr_entries >= trace->max_entries);
पूर्ण

अटल bool save_trace(अचिन्हित दीर्घ pc, व्योम *arg)
अणु
	वापस __save_trace(pc, arg, false);
पूर्ण

/*
 * Save stack-backtrace addresses पूर्णांकo a stack_trace buffer.
 */
व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	walk_stackframe(tsk, शून्य, save_trace, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace_tsk);

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	save_stack_trace_tsk(शून्य, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);

#पूर्ण_अगर /* CONFIG_STACKTRACE */
