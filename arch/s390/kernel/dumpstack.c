<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Stack dumping functions
 *
 *  Copyright IBM Corp. 1999, 2013
 */

#समावेश <linux/kallsyms.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/utsname.h>
#समावेश <linux/export.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/mm.h>
#समावेश <linux/module.h>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/dis.h>
#समावेश <यंत्र/ipl.h>
#समावेश <यंत्र/unwind.h>

स्थिर अक्षर *stack_type_name(क्रमागत stack_type type)
अणु
	चयन (type) अणु
	हाल STACK_TYPE_TASK:
		वापस "task";
	हाल STACK_TYPE_IRQ:
		वापस "irq";
	हाल STACK_TYPE_NODAT:
		वापस "nodat";
	हाल STACK_TYPE_RESTART:
		वापस "restart";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(stack_type_name);

अटल अंतरभूत bool in_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info,
			    क्रमागत stack_type type, अचिन्हित दीर्घ low,
			    अचिन्हित दीर्घ high)
अणु
	अगर (sp < low || sp >= high)
		वापस false;
	info->type = type;
	info->begin = low;
	info->end = high;
	वापस true;
पूर्ण

अटल bool in_task_stack(अचिन्हित दीर्घ sp, काष्ठा task_काष्ठा *task,
			  काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ stack;

	stack = (अचिन्हित दीर्घ) task_stack_page(task);
	वापस in_stack(sp, info, STACK_TYPE_TASK, stack, stack + THREAD_SIZE);
पूर्ण

अटल bool in_irq_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ frame_size, top;

	frame_size = STACK_FRAME_OVERHEAD + माप(काष्ठा pt_regs);
	top = S390_lowcore.async_stack + frame_size;
	वापस in_stack(sp, info, STACK_TYPE_IRQ, top - THREAD_SIZE, top);
पूर्ण

अटल bool in_nodat_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ frame_size, top;

	frame_size = STACK_FRAME_OVERHEAD + माप(काष्ठा pt_regs);
	top = S390_lowcore.nodat_stack + frame_size;
	वापस in_stack(sp, info, STACK_TYPE_NODAT, top - THREAD_SIZE, top);
पूर्ण

अटल bool in_mcck_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ frame_size, top;

	frame_size = STACK_FRAME_OVERHEAD + माप(काष्ठा pt_regs);
	top = S390_lowcore.mcck_stack + frame_size;
	वापस in_stack(sp, info, STACK_TYPE_MCCK, top - THREAD_SIZE, top);
पूर्ण

अटल bool in_restart_stack(अचिन्हित दीर्घ sp, काष्ठा stack_info *info)
अणु
	अचिन्हित दीर्घ frame_size, top;

	frame_size = STACK_FRAME_OVERHEAD + माप(काष्ठा pt_regs);
	top = S390_lowcore.restart_stack + frame_size;
	वापस in_stack(sp, info, STACK_TYPE_RESTART, top - THREAD_SIZE, top);
पूर्ण

पूर्णांक get_stack_info(अचिन्हित दीर्घ sp, काष्ठा task_काष्ठा *task,
		   काष्ठा stack_info *info, अचिन्हित दीर्घ *visit_mask)
अणु
	अगर (!sp)
		जाओ unknown;

	/* Sanity check: ABI requires SP to be aligned 8 bytes. */
	अगर (sp & 0x7)
		जाओ unknown;

	/* Check per-task stack */
	अगर (in_task_stack(sp, task, info))
		जाओ recursion_check;

	अगर (task != current)
		जाओ unknown;

	/* Check per-cpu stacks */
	अगर (!in_irq_stack(sp, info) &&
	    !in_nodat_stack(sp, info) &&
	    !in_restart_stack(sp, info) &&
	    !in_mcck_stack(sp, info))
		जाओ unknown;

recursion_check:
	/*
	 * Make sure we करोn't iterate through any given stack more than once.
	 * If it comes up a second समय then there's something wrong going on:
	 * just अवरोध out and report an unknown stack type.
	 */
	अगर (*visit_mask & (1UL << info->type))
		जाओ unknown;
	*visit_mask |= 1UL << info->type;
	वापस 0;
unknown:
	info->type = STACK_TYPE_UNKNOWN;
	वापस -EINVAL;
पूर्ण

व्योम show_stack(काष्ठा task_काष्ठा *task, अचिन्हित दीर्घ *stack,
		       स्थिर अक्षर *loglvl)
अणु
	काष्ठा unwind_state state;

	prपूर्णांकk("%sCall Trace:\n", loglvl);
	unwind_क्रम_each_frame(&state, task, शून्य, (अचिन्हित दीर्घ) stack)
		prपूर्णांकk(state.reliable ? "%s [<%016lx>] %pSR \n" :
					"%s([<%016lx>] %pSR)\n",
		       loglvl, state.ip, (व्योम *) state.ip);
	debug_show_held_locks(task ? : current);
पूर्ण

अटल व्योम show_last_अवरोधing_event(काष्ठा pt_regs *regs)
अणु
	prपूर्णांकk("Last Breaking-Event-Address:\n");
	prपूर्णांकk(" [<%016lx>] %pSR\n", regs->args[0], (व्योम *)regs->args[0]);
पूर्ण

व्योम show_रेजिस्टरs(काष्ठा pt_regs *regs)
अणु
	काष्ठा psw_bits *psw = &psw_bits(regs->psw);
	अक्षर *mode;

	mode = user_mode(regs) ? "User" : "Krnl";
	prपूर्णांकk("%s PSW : %px %px", mode, (व्योम *)regs->psw.mask, (व्योम *)regs->psw.addr);
	अगर (!user_mode(regs))
		pr_cont(" (%pSR)", (व्योम *)regs->psw.addr);
	pr_cont("\n");
	prपूर्णांकk("           R:%x T:%x IO:%x EX:%x Key:%x M:%x W:%x "
	       "P:%x AS:%x CC:%x PM:%x", psw->per, psw->dat, psw->io, psw->ext,
	       psw->key, psw->mcheck, psw->रुको, psw->pstate, psw->as, psw->cc, psw->pm);
	pr_cont(" RI:%x EA:%x\n", psw->ri, psw->eaba);
	prपूर्णांकk("%s GPRS: %016lx %016lx %016lx %016lx\n", mode,
	       regs->gprs[0], regs->gprs[1], regs->gprs[2], regs->gprs[3]);
	prपूर्णांकk("           %016lx %016lx %016lx %016lx\n",
	       regs->gprs[4], regs->gprs[5], regs->gprs[6], regs->gprs[7]);
	prपूर्णांकk("           %016lx %016lx %016lx %016lx\n",
	       regs->gprs[8], regs->gprs[9], regs->gprs[10], regs->gprs[11]);
	prपूर्णांकk("           %016lx %016lx %016lx %016lx\n",
	       regs->gprs[12], regs->gprs[13], regs->gprs[14], regs->gprs[15]);
	show_code(regs);
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	show_regs_prपूर्णांक_info(KERN_DEFAULT);
	show_रेजिस्टरs(regs);
	/* Show stack backtrace अगर pt_regs is from kernel mode */
	अगर (!user_mode(regs))
		show_stack(शून्य, (अचिन्हित दीर्घ *) regs->gprs[15], KERN_DEFAULT);
	show_last_अवरोधing_event(regs);
पूर्ण

अटल DEFINE_SPINLOCK(die_lock);

व्योम die(काष्ठा pt_regs *regs, स्थिर अक्षर *str)
अणु
	अटल पूर्णांक die_counter;

	oops_enter();
	lgr_info_log();
	debug_stop_all();
	console_verbose();
	spin_lock_irq(&die_lock);
	bust_spinlocks(1);
	prपूर्णांकk("%s: %04x ilc:%d [#%d] ", str, regs->पूर्णांक_code & 0xffff,
	       regs->पूर्णांक_code >> 17, ++die_counter);
#अगर_घोषित CONFIG_PREEMPT
	pr_cont("PREEMPT ");
#या_अगर defined(CONFIG_PREEMPT_RT)
	pr_cont("PREEMPT_RT ");
#पूर्ण_अगर
	pr_cont("SMP ");
	अगर (debug_pagealloc_enabled())
		pr_cont("DEBUG_PAGEALLOC");
	pr_cont("\n");
	notअगरy_die(DIE_OOPS, str, regs, 0, regs->पूर्णांक_code & 0xffff, संक_अंश);
	prपूर्णांक_modules();
	show_regs(regs);
	bust_spinlocks(0);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irq(&die_lock);
	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");
	अगर (panic_on_oops)
		panic("Fatal exception: panic_on_oops");
	oops_निकास();
	करो_निकास(संक_अंश);
पूर्ण
