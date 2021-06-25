<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 *	stacktrace.c : stacktracing APIs needed by rest of kernel
 *			(wrappers over ARC dwarf based unwinder)
 *
 * Copyright (C) 2004, 2007-2010, 2011-2012 Synopsys, Inc. (www.synopsys.com)
 *
 *  vineetg: aug 2009
 *  -Implemented CONFIG_STACKTRACE APIs, primarily save_stack_trace_tsk( )
 *   क्रम displaying task's kernel mode call stack in /proc/<pid>/stack
 *  -Iterator based approach to have single copy of unwinding core and APIs
 *   needing unwinding, implement the logic in iterator regarding:
 *      = which frame onwards to start capture
 *      = which frame to stop capturing (wchan)
 *      = specअगरics of data काष्ठाs where trace is saved(CONFIG_STACKTRACE etc)
 *
 *  vineetg: March 2009
 *  -Implemented correct versions of thपढ़ो_saved_pc() and get_wchan()
 *
 *  rajeshwarr: 2008
 *  -Initial implementation
 */

#समावेश <linux/ptrace.h>
#समावेश <linux/export.h>
#समावेश <linux/stacktrace.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/sched/debug.h>

#समावेश <यंत्र/arcregs.h>
#समावेश <यंत्र/unwind.h>
#समावेश <यंत्र/चयन_to.h>

/*-------------------------------------------------------------------------
 *              Unwinder Iterator
 *-------------------------------------------------------------------------
 */

#अगर_घोषित CONFIG_ARC_DW2_UNWIND

अटल पूर्णांक
seed_unwind_frame_info(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs,
		       काष्ठा unwind_frame_info *frame_info)
अणु
	अगर (regs) अणु
		/*
		 * Asynchronous unwinding of पूर्णांकr/exception
		 *  - Just uses the pt_regs passed
		 */
		frame_info->task = tsk;

		frame_info->regs.r27 = regs->fp;
		frame_info->regs.r28 = regs->sp;
		frame_info->regs.r31 = regs->blink;
		frame_info->regs.r63 = regs->ret;
		frame_info->call_frame = 0;
	पूर्ण अन्यथा अगर (tsk == शून्य || tsk == current) अणु
		/*
		 * synchronous unwinding (e.g. dump_stack)
		 *  - uses current values of SP and मित्रs
		 */
		अचिन्हित दीर्घ fp, sp, blink, ret;
		frame_info->task = current;

		__यंत्र__ __अस्थिर__(
			"mov %0,r27\n\t"
			"mov %1,r28\n\t"
			"mov %2,r31\n\t"
			"mov %3,r63\n\t"
			: "=r"(fp), "=r"(sp), "=r"(blink), "=r"(ret)
		);

		frame_info->regs.r27 = fp;
		frame_info->regs.r28 = sp;
		frame_info->regs.r31 = blink;
		frame_info->regs.r63 = ret;
		frame_info->call_frame = 0;
	पूर्ण अन्यथा अणु
		/*
		 * Asynchronous unwinding of a likely sleeping task
		 *  - first ensure it is actually sleeping
		 *  - अगर so, it will be in __चयन_to, kernel mode SP of task
		 *    is safe-kept and BLINK at a well known location in there
		 */

		अगर (tsk->state == TASK_RUNNING)
			वापस -1;

		frame_info->task = tsk;

		frame_info->regs.r27 = TSK_K_FP(tsk);
		frame_info->regs.r28 = TSK_K_ESP(tsk);
		frame_info->regs.r31 = TSK_K_BLINK(tsk);
		frame_info->regs.r63 = (अचिन्हित पूर्णांक)__चयन_to;

		/* In the prologue of __चयन_to, first FP is saved on stack
		 * and then SP is copied to FP. Dwarf assumes cfa as FP based
		 * but we didn't save FP. The value retrieved above is FP's
		 * state in previous frame.
		 * As a work around क्रम this, we unwind from __चयन_to start
		 * and adjust SP accordingly. The other limitation is that
		 * __चयन_to macro is dwarf rules are not generated क्रम अंतरभूत
		 * assembly code
		 */
		frame_info->regs.r27 = 0;
		frame_info->regs.r28 += 60;
		frame_info->call_frame = 0;

	पूर्ण
	वापस 0;
पूर्ण

#पूर्ण_अगर

notrace noअंतरभूत अचिन्हित पूर्णांक
arc_unwind_core(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs,
		पूर्णांक (*consumer_fn) (अचिन्हित पूर्णांक, व्योम *), व्योम *arg)
अणु
#अगर_घोषित CONFIG_ARC_DW2_UNWIND
	पूर्णांक ret = 0, cnt = 0;
	अचिन्हित पूर्णांक address;
	काष्ठा unwind_frame_info frame_info;

	अगर (seed_unwind_frame_info(tsk, regs, &frame_info))
		वापस 0;

	जबतक (1) अणु
		address = UNW_PC(&frame_info);

		अगर (!address || !__kernel_text_address(address))
			अवरोध;

		अगर (consumer_fn(address, arg) == -1)
			अवरोध;

		ret = arc_unwind(&frame_info);
		अगर (ret)
			अवरोध;

		frame_info.regs.r63 = frame_info.regs.r31;

		अगर (cnt++ > 128) अणु
			prपूर्णांकk("unwinder looping too long, aborting !\n");
			वापस 0;
		पूर्ण
	पूर्ण

	वापस address;		/* वापस the last address it saw */
#अन्यथा
	/* On ARC, only Dward based unwinder works. fp based backtracing is
	 * not possible (-fno-omit-frame-poपूर्णांकer) because of the way function
	 * prelogue is setup (callee regs saved and then fp set and not other
	 * way around
	 */
	pr_warn_once("CONFIG_ARC_DW2_UNWIND needs to be enabled\n");
	वापस 0;

#पूर्ण_अगर
पूर्ण

/*-------------------------------------------------------------------------
 * callbacks called by unwinder iterator to implement kernel APIs
 *
 * The callback can वापस -1 to क्रमce the iterator to stop, which by शेष
 * keeps going till the bottom-most frame.
 *-------------------------------------------------------------------------
 */

/* Call-back which plugs पूर्णांकo unwinding core to dump the stack in
 * हाल of panic/OOPs/BUG etc
 */
अटल पूर्णांक __prपूर्णांक_sym(अचिन्हित पूर्णांक address, व्योम *arg)
अणु
	स्थिर अक्षर *loglvl = arg;

	prपूर्णांकk("%s  %pS\n", loglvl, (व्योम *)address);
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE

/* Call-back which plugs पूर्णांकo unwinding core to capture the
 * traces needed by kernel on /proc/<pid>/stack
 */
अटल पूर्णांक __collect_all(अचिन्हित पूर्णांक address, व्योम *arg)
अणु
	काष्ठा stack_trace *trace = arg;

	अगर (trace->skip > 0)
		trace->skip--;
	अन्यथा
		trace->entries[trace->nr_entries++] = address;

	अगर (trace->nr_entries >= trace->max_entries)
		वापस -1;

	वापस 0;
पूर्ण

अटल पूर्णांक __collect_all_but_sched(अचिन्हित पूर्णांक address, व्योम *arg)
अणु
	काष्ठा stack_trace *trace = arg;

	अगर (in_sched_functions(address))
		वापस 0;

	अगर (trace->skip > 0)
		trace->skip--;
	अन्यथा
		trace->entries[trace->nr_entries++] = address;

	अगर (trace->nr_entries >= trace->max_entries)
		वापस -1;

	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक __get_first_nonsched(अचिन्हित पूर्णांक address, व्योम *unused)
अणु
	अगर (in_sched_functions(address))
		वापस 0;

	वापस -1;
पूर्ण

/*-------------------------------------------------------------------------
 *              APIs expected by various kernel sub-प्रणालीs
 *-------------------------------------------------------------------------
 */

noअंतरभूत व्योम show_stacktrace(काष्ठा task_काष्ठा *tsk, काष्ठा pt_regs *regs,
			      स्थिर अक्षर *loglvl)
अणु
	prपूर्णांकk("%s\nStack Trace:\n", loglvl);
	arc_unwind_core(tsk, regs, __prपूर्णांक_sym, (व्योम *)loglvl);
पूर्ण
EXPORT_SYMBOL(show_stacktrace);

/* Expected by sched Code */
व्योम show_stack(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *sp, स्थिर अक्षर *loglvl)
अणु
	show_stacktrace(tsk, शून्य, loglvl);
पूर्ण

/* Another API expected by schedular, shows up in "ps" as Wait Channel
 * Of course just वापसing schedule( ) would be poपूर्णांकless so unwind until
 * the function is not in schedular code
 */
अचिन्हित पूर्णांक get_wchan(काष्ठा task_काष्ठा *tsk)
अणु
	वापस arc_unwind_core(tsk, शून्य, __get_first_nonsched, शून्य);
पूर्ण

#अगर_घोषित CONFIG_STACKTRACE

/*
 * API required by CONFIG_STACKTRACE, CONFIG_LATENCYTOP.
 * A typical use is when /proc/<pid>/stack is queried by userland
 */
व्योम save_stack_trace_tsk(काष्ठा task_काष्ठा *tsk, काष्ठा stack_trace *trace)
अणु
	/* Assumes @tsk is sleeping so unwinds from __चयन_to */
	arc_unwind_core(tsk, शून्य, __collect_all_but_sched, trace);
पूर्ण

व्योम save_stack_trace(काष्ठा stack_trace *trace)
अणु
	/* Pass शून्य क्रम task so it unwinds the current call frame */
	arc_unwind_core(शून्य, शून्य, __collect_all, trace);
पूर्ण
EXPORT_SYMBOL_GPL(save_stack_trace);
#पूर्ण_अगर
