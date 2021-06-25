<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/bug.h>
#समावेश <linux/पन.स>
#समावेश <linux/types.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kexec.h>
#समावेश <linux/sched/संकेत.स>

#समावेश <linux/extable.h>
#समावेश <linux/module.h>	/* prपूर्णांक_modules */
#समावेश <यंत्र/unwinder.h>
#समावेश <यंत्र/traps.h>

अटल DEFINE_SPINLOCK(die_lock);

व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अटल पूर्णांक die_counter;

	oops_enter();

	spin_lock_irq(&die_lock);
	console_verbose();
	bust_spinlocks(1);

	prपूर्णांकk("%s: %04lx [#%d]\n", str, err & 0xffff, ++die_counter);
	prपूर्णांक_modules();
	show_regs(regs);

	prपूर्णांकk("Process: %s (pid: %d, stack limit = %p)\n", current->comm,
			task_pid_nr(current), task_stack_page(current) + 1);

	अगर (!user_mode(regs) || in_पूर्णांकerrupt())
		dump_mem("Stack: ", KERN_DEFAULT, regs->regs[15],
			THREAD_SIZE + (अचिन्हित दीर्घ)task_stack_page(current));

	notअगरy_die(DIE_OOPS, str, regs, err, 255, संक_अंश);

	bust_spinlocks(0);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	spin_unlock_irq(&die_lock);
	oops_निकास();

	अगर (kexec_should_crash(current))
		crash_kexec(regs);

	अगर (in_पूर्णांकerrupt())
		panic("Fatal exception in interrupt");

	अगर (panic_on_oops)
		panic("Fatal exception");

	करो_निकास(संक_अंश);
पूर्ण

व्योम die_अगर_kernel(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अगर (!user_mode(regs))
		die(str, regs, err);
पूर्ण

/*
 * try and fix up kernelspace address errors
 * - userspace errors just cause EFAULT to be वापसed, resulting in SEGV
 * - kernel/userspace पूर्णांकerfaces cause a jump to an appropriate handler
 * - other kernel errors are bad
 */
व्योम die_अगर_no_fixup(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अगर (!user_mode(regs)) अणु
		स्थिर काष्ठा exception_table_entry *fixup;
		fixup = search_exception_tables(regs->pc);
		अगर (fixup) अणु
			regs->pc = fixup->fixup;
			वापस;
		पूर्ण

		die(str, regs, err);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_GENERIC_BUG
अटल व्योम handle_BUG(काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा bug_entry *bug;
	अचिन्हित दीर्घ bugaddr = regs->pc;
	क्रमागत bug_trap_type tt;

	अगर (!is_valid_bugaddr(bugaddr))
		जाओ invalid;

	bug = find_bug(bugaddr);

	/* Switch unwinders when unwind_stack() is called */
	अगर (bug->flags & BUGFLAG_UNWINDER)
		unwinder_faulted = 1;

	tt = report_bug(bugaddr, regs);
	अगर (tt == BUG_TRAP_TYPE_WARN) अणु
		regs->pc += inकाष्ठाion_size(bugaddr);
		वापस;
	पूर्ण

invalid:
	die("Kernel BUG", regs, TRAPA_BUG_OPCODE & 0xff);
पूर्ण

पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ addr)
अणु
	insn_माप_प्रकार opcode;

	अगर (addr < PAGE_OFFSET)
		वापस 0;
	अगर (get_kernel_nofault(opcode, (insn_माप_प्रकार *)addr))
		वापस 0;
	अगर (opcode == TRAPA_BUG_OPCODE)
		वापस 1;

	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * Generic trap handler.
 */
BUILD_TRAP_HANDLER(debug)
अणु
	TRAP_HANDLER_DECL;

	/* Rewind */
	regs->pc -= inकाष्ठाion_size(__raw_पढ़ोw(regs->pc - 4));

	अगर (notअगरy_die(DIE_TRAP, "debug trap", regs, 0, vec & 0xff,
		       SIGTRAP) == NOTIFY_STOP)
		वापस;

	क्रमce_sig(SIGTRAP);
पूर्ण

/*
 * Special handler क्रम BUG() traps.
 */
BUILD_TRAP_HANDLER(bug)
अणु
	TRAP_HANDLER_DECL;

	/* Rewind */
	regs->pc -= inकाष्ठाion_size(__raw_पढ़ोw(regs->pc - 4));

	अगर (notअगरy_die(DIE_TRAP, "bug trap", regs, 0, TRAPA_BUG_OPCODE & 0xff,
		       SIGTRAP) == NOTIFY_STOP)
		वापस;

#अगर_घोषित CONFIG_GENERIC_BUG
	अगर (__kernel_text_address(inकाष्ठाion_poपूर्णांकer(regs))) अणु
		insn_माप_प्रकार insn = *(insn_माप_प्रकार *)inकाष्ठाion_poपूर्णांकer(regs);
		अगर (insn == TRAPA_BUG_OPCODE)
			handle_BUG(regs);
		वापस;
	पूर्ण
#पूर्ण_अगर

	क्रमce_sig(SIGTRAP);
पूर्ण

#अगर_घोषित CONFIG_DYNAMIC_FTRACE
बाह्य व्योम arch_ftrace_nmi_enter(व्योम);
बाह्य व्योम arch_ftrace_nmi_निकास(व्योम);
#अन्यथा
अटल अंतरभूत व्योम arch_ftrace_nmi_enter(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम arch_ftrace_nmi_निकास(व्योम) अणु पूर्ण
#पूर्ण_अगर

BUILD_TRAP_HANDLER(nmi)
अणु
	TRAP_HANDLER_DECL;

	arch_ftrace_nmi_enter();

	nmi_enter();
	this_cpu_inc(irq_stat.__nmi_count);

	चयन (notअगरy_die(DIE_NMI, "NMI", regs, 0, vec & 0xff, संक_विघ्न)) अणु
	हाल NOTIFY_OK:
	हाल NOTIFY_STOP:
		अवरोध;
	हाल NOTIFY_BAD:
		die("Fatal Non-Maskable Interrupt", regs, संक_विघ्न);
	शेष:
		prपूर्णांकk(KERN_ALERT "Got NMI, but nobody cared. Ignoring...\n");
		अवरोध;
	पूर्ण

	nmi_निकास();

	arch_ftrace_nmi_निकास();
पूर्ण
