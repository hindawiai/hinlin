<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * ARMv8 single-step debug support and mdscr context चयनing.
 *
 * Copyright (C) 2012 ARM Limited
 *
 * Author: Will Deacon <will.deacon@arm.com>
 */

#समावेश <linux/cpu.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/init.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/स्थिति.स>
#समावेश <linux/uaccess.h>
#समावेश <linux/sched/task_stack.h>

#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/cputype.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/traps.h>

/* Determine debug architecture. */
u8 debug_monitors_arch(व्योम)
अणु
	वापस cpuid_feature_extract_अचिन्हित_field(पढ़ो_sanitised_ftr_reg(SYS_ID_AA64DFR0_EL1),
						ID_AA64DFR0_DEBUGVER_SHIFT);
पूर्ण

/*
 * MDSCR access routines.
 */
अटल व्योम mdscr_ग_लिखो(u32 mdscr)
अणु
	अचिन्हित दीर्घ flags;
	flags = local_daअगर_save();
	ग_लिखो_sysreg(mdscr, mdscr_el1);
	local_daअगर_restore(flags);
पूर्ण
NOKPROBE_SYMBOL(mdscr_ग_लिखो);

अटल u32 mdscr_पढ़ो(व्योम)
अणु
	वापस पढ़ो_sysreg(mdscr_el1);
पूर्ण
NOKPROBE_SYMBOL(mdscr_पढ़ो);

/*
 * Allow root to disable self-hosted debug from userspace.
 * This is useful अगर you want to connect an बाह्यal JTAG debugger.
 */
अटल bool debug_enabled = true;

अटल पूर्णांक create_debug_debugfs_entry(व्योम)
अणु
	debugfs_create_bool("debug_enabled", 0644, शून्य, &debug_enabled);
	वापस 0;
पूर्ण
fs_initcall(create_debug_debugfs_entry);

अटल पूर्णांक __init early_debug_disable(अक्षर *buf)
अणु
	debug_enabled = false;
	वापस 0;
पूर्ण

early_param("nodebugmon", early_debug_disable);

/*
 * Keep track of debug users on each core.
 * The ref counts are per-cpu so we use a local_t type.
 */
अटल DEFINE_PER_CPU(पूर्णांक, mde_ref_count);
अटल DEFINE_PER_CPU(पूर्णांक, kde_ref_count);

व्योम enable_debug_monitors(क्रमागत dbg_active_el el)
अणु
	u32 mdscr, enable = 0;

	WARN_ON(preemptible());

	अगर (this_cpu_inc_वापस(mde_ref_count) == 1)
		enable = DBG_MDSCR_MDE;

	अगर (el == DBG_ACTIVE_EL1 &&
	    this_cpu_inc_वापस(kde_ref_count) == 1)
		enable |= DBG_MDSCR_KDE;

	अगर (enable && debug_enabled) अणु
		mdscr = mdscr_पढ़ो();
		mdscr |= enable;
		mdscr_ग_लिखो(mdscr);
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(enable_debug_monitors);

व्योम disable_debug_monitors(क्रमागत dbg_active_el el)
अणु
	u32 mdscr, disable = 0;

	WARN_ON(preemptible());

	अगर (this_cpu_dec_वापस(mde_ref_count) == 0)
		disable = ~DBG_MDSCR_MDE;

	अगर (el == DBG_ACTIVE_EL1 &&
	    this_cpu_dec_वापस(kde_ref_count) == 0)
		disable &= ~DBG_MDSCR_KDE;

	अगर (disable) अणु
		mdscr = mdscr_पढ़ो();
		mdscr &= disable;
		mdscr_ग_लिखो(mdscr);
	पूर्ण
पूर्ण
NOKPROBE_SYMBOL(disable_debug_monitors);

/*
 * OS lock clearing.
 */
अटल पूर्णांक clear_os_lock(अचिन्हित पूर्णांक cpu)
अणु
	ग_लिखो_sysreg(0, osdlr_el1);
	ग_लिखो_sysreg(0, oslar_el1);
	isb();
	वापस 0;
पूर्ण

अटल पूर्णांक __init debug_monitors_init(व्योम)
अणु
	वापस cpuhp_setup_state(CPUHP_AP_ARM64_DEBUG_MONITORS_STARTING,
				 "arm64/debug_monitors:starting",
				 clear_os_lock, शून्य);
पूर्ण
postcore_initcall(debug_monitors_init);

/*
 * Single step API and exception handling.
 */
अटल व्योम set_user_regs_spsr_ss(काष्ठा user_pt_regs *regs)
अणु
	regs->pstate |= DBG_SPSR_SS;
पूर्ण
NOKPROBE_SYMBOL(set_user_regs_spsr_ss);

अटल व्योम clear_user_regs_spsr_ss(काष्ठा user_pt_regs *regs)
अणु
	regs->pstate &= ~DBG_SPSR_SS;
पूर्ण
NOKPROBE_SYMBOL(clear_user_regs_spsr_ss);

#घोषणा set_regs_spsr_ss(r)	set_user_regs_spsr_ss(&(r)->user_regs)
#घोषणा clear_regs_spsr_ss(r)	clear_user_regs_spsr_ss(&(r)->user_regs)

अटल DEFINE_SPINLOCK(debug_hook_lock);
अटल LIST_HEAD(user_step_hook);
अटल LIST_HEAD(kernel_step_hook);

अटल व्योम रेजिस्टर_debug_hook(काष्ठा list_head *node, काष्ठा list_head *list)
अणु
	spin_lock(&debug_hook_lock);
	list_add_rcu(node, list);
	spin_unlock(&debug_hook_lock);

पूर्ण

अटल व्योम unरेजिस्टर_debug_hook(काष्ठा list_head *node)
अणु
	spin_lock(&debug_hook_lock);
	list_del_rcu(node);
	spin_unlock(&debug_hook_lock);
	synchronize_rcu();
पूर्ण

व्योम रेजिस्टर_user_step_hook(काष्ठा step_hook *hook)
अणु
	रेजिस्टर_debug_hook(&hook->node, &user_step_hook);
पूर्ण

व्योम unरेजिस्टर_user_step_hook(काष्ठा step_hook *hook)
अणु
	unरेजिस्टर_debug_hook(&hook->node);
पूर्ण

व्योम रेजिस्टर_kernel_step_hook(काष्ठा step_hook *hook)
अणु
	रेजिस्टर_debug_hook(&hook->node, &kernel_step_hook);
पूर्ण

व्योम unरेजिस्टर_kernel_step_hook(काष्ठा step_hook *hook)
अणु
	unरेजिस्टर_debug_hook(&hook->node);
पूर्ण

/*
 * Call रेजिस्टरed single step handlers
 * There is no Syndrome info to check क्रम determining the handler.
 * So we call all the रेजिस्टरed handlers, until the right handler is
 * found which वापसs zero.
 */
अटल पूर्णांक call_step_hook(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	काष्ठा step_hook *hook;
	काष्ठा list_head *list;
	पूर्णांक retval = DBG_HOOK_ERROR;

	list = user_mode(regs) ? &user_step_hook : &kernel_step_hook;

	/*
	 * Since single-step exception disables पूर्णांकerrupt, this function is
	 * entirely not preemptible, and we can use rcu list safely here.
	 */
	list_क्रम_each_entry_rcu(hook, list, node)	अणु
		retval = hook->fn(regs, esr);
		अगर (retval == DBG_HOOK_HANDLED)
			अवरोध;
	पूर्ण

	वापस retval;
पूर्ण
NOKPROBE_SYMBOL(call_step_hook);

अटल व्योम send_user_sigtrap(पूर्णांक si_code)
अणु
	काष्ठा pt_regs *regs = current_pt_regs();

	अगर (WARN_ON(!user_mode(regs)))
		वापस;

	अगर (पूर्णांकerrupts_enabled(regs))
		local_irq_enable();

	arm64_क्रमce_sig_fault(SIGTRAP, si_code, inकाष्ठाion_poपूर्णांकer(regs),
			      "User debug trap");
पूर्ण

अटल पूर्णांक single_step_handler(अचिन्हित दीर्घ unused, अचिन्हित पूर्णांक esr,
			       काष्ठा pt_regs *regs)
अणु
	bool handler_found = false;

	/*
	 * If we are stepping a pending अवरोधpoपूर्णांक, call the hw_अवरोधpoपूर्णांक
	 * handler first.
	 */
	अगर (!reinstall_suspended_bps(regs))
		वापस 0;

	अगर (!handler_found && call_step_hook(regs, esr) == DBG_HOOK_HANDLED)
		handler_found = true;

	अगर (!handler_found && user_mode(regs)) अणु
		send_user_sigtrap(TRAP_TRACE);

		/*
		 * ptrace will disable single step unless explicitly
		 * asked to re-enable it. For other clients, it makes
		 * sense to leave it enabled (i.e. शुरुआत the controls
		 * to the active-not-pending state).
		 */
		user_शुरुआत_single_step(current);
	पूर्ण अन्यथा अगर (!handler_found) अणु
		pr_warn("Unexpected kernel single-step exception at EL1\n");
		/*
		 * Re-enable stepping since we know that we will be
		 * वापसing to regs.
		 */
		set_regs_spsr_ss(regs);
	पूर्ण

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(single_step_handler);

अटल LIST_HEAD(user_अवरोध_hook);
अटल LIST_HEAD(kernel_अवरोध_hook);

व्योम रेजिस्टर_user_अवरोध_hook(काष्ठा अवरोध_hook *hook)
अणु
	रेजिस्टर_debug_hook(&hook->node, &user_अवरोध_hook);
पूर्ण

व्योम unरेजिस्टर_user_अवरोध_hook(काष्ठा अवरोध_hook *hook)
अणु
	unरेजिस्टर_debug_hook(&hook->node);
पूर्ण

व्योम रेजिस्टर_kernel_अवरोध_hook(काष्ठा अवरोध_hook *hook)
अणु
	रेजिस्टर_debug_hook(&hook->node, &kernel_अवरोध_hook);
पूर्ण

व्योम unरेजिस्टर_kernel_अवरोध_hook(काष्ठा अवरोध_hook *hook)
अणु
	unरेजिस्टर_debug_hook(&hook->node);
पूर्ण

अटल पूर्णांक call_अवरोध_hook(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	काष्ठा अवरोध_hook *hook;
	काष्ठा list_head *list;
	पूर्णांक (*fn)(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr) = शून्य;

	list = user_mode(regs) ? &user_अवरोध_hook : &kernel_अवरोध_hook;

	/*
	 * Since brk exception disables पूर्णांकerrupt, this function is
	 * entirely not preemptible, and we can use rcu list safely here.
	 */
	list_क्रम_each_entry_rcu(hook, list, node) अणु
		अचिन्हित पूर्णांक comment = esr & ESR_ELx_BRK64_ISS_COMMENT_MASK;

		अगर ((comment & ~hook->mask) == hook->imm)
			fn = hook->fn;
	पूर्ण

	वापस fn ? fn(regs, esr) : DBG_HOOK_ERROR;
पूर्ण
NOKPROBE_SYMBOL(call_अवरोध_hook);

अटल पूर्णांक brk_handler(अचिन्हित दीर्घ unused, अचिन्हित पूर्णांक esr,
		       काष्ठा pt_regs *regs)
अणु
	अगर (call_अवरोध_hook(regs, esr) == DBG_HOOK_HANDLED)
		वापस 0;

	अगर (user_mode(regs)) अणु
		send_user_sigtrap(TRAP_BRKPT);
	पूर्ण अन्यथा अणु
		pr_warn("Unexpected kernel BRK exception at EL1\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(brk_handler);

पूर्णांक aarch32_अवरोध_handler(काष्ठा pt_regs *regs)
अणु
	u32 arm_instr;
	u16 thumb_instr;
	bool bp = false;
	व्योम __user *pc = (व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs);

	अगर (!compat_user_mode(regs))
		वापस -EFAULT;

	अगर (compat_thumb_mode(regs)) अणु
		/* get 16-bit Thumb inकाष्ठाion */
		__le16 instr;
		get_user(instr, (__le16 __user *)pc);
		thumb_instr = le16_to_cpu(instr);
		अगर (thumb_instr == AARCH32_BREAK_THUMB2_LO) अणु
			/* get second half of 32-bit Thumb-2 inकाष्ठाion */
			get_user(instr, (__le16 __user *)(pc + 2));
			thumb_instr = le16_to_cpu(instr);
			bp = thumb_instr == AARCH32_BREAK_THUMB2_HI;
		पूर्ण अन्यथा अणु
			bp = thumb_instr == AARCH32_BREAK_THUMB;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 32-bit ARM inकाष्ठाion */
		__le32 instr;
		get_user(instr, (__le32 __user *)pc);
		arm_instr = le32_to_cpu(instr);
		bp = (arm_instr & ~0xf0000000) == AARCH32_BREAK_ARM;
	पूर्ण

	अगर (!bp)
		वापस -EFAULT;

	send_user_sigtrap(TRAP_BRKPT);
	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(aarch32_अवरोध_handler);

व्योम __init debug_traps_init(व्योम)
अणु
	hook_debug_fault_code(DBG_ESR_EVT_HWSS, single_step_handler, SIGTRAP,
			      TRAP_TRACE, "single-step handler");
	hook_debug_fault_code(DBG_ESR_EVT_BRK, brk_handler, SIGTRAP,
			      TRAP_BRKPT, "BRK handler");
पूर्ण

/* Re-enable single step क्रम syscall restarting. */
व्योम user_शुरुआत_single_step(काष्ठा task_काष्ठा *task)
अणु
	/*
	 * If single step is active क्रम this thपढ़ो, then set SPSR.SS
	 * to 1 to aव्योम वापसing to the active-pending state.
	 */
	अगर (test_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP))
		set_regs_spsr_ss(task_pt_regs(task));
पूर्ण
NOKPROBE_SYMBOL(user_शुरुआत_single_step);

व्योम user_fastक्रमward_single_step(काष्ठा task_काष्ठा *task)
अणु
	अगर (test_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP))
		clear_regs_spsr_ss(task_pt_regs(task));
पूर्ण

व्योम user_regs_reset_single_step(काष्ठा user_pt_regs *regs,
				 काष्ठा task_काष्ठा *task)
अणु
	अगर (test_tsk_thपढ़ो_flag(task, TIF_SINGLESTEP))
		set_user_regs_spsr_ss(regs);
	अन्यथा
		clear_user_regs_spsr_ss(regs);
पूर्ण

/* Kernel API */
व्योम kernel_enable_single_step(काष्ठा pt_regs *regs)
अणु
	WARN_ON(!irqs_disabled());
	set_regs_spsr_ss(regs);
	mdscr_ग_लिखो(mdscr_पढ़ो() | DBG_MDSCR_SS);
	enable_debug_monitors(DBG_ACTIVE_EL1);
पूर्ण
NOKPROBE_SYMBOL(kernel_enable_single_step);

व्योम kernel_disable_single_step(व्योम)
अणु
	WARN_ON(!irqs_disabled());
	mdscr_ग_लिखो(mdscr_पढ़ो() & ~DBG_MDSCR_SS);
	disable_debug_monitors(DBG_ACTIVE_EL1);
पूर्ण
NOKPROBE_SYMBOL(kernel_disable_single_step);

पूर्णांक kernel_active_single_step(व्योम)
अणु
	WARN_ON(!irqs_disabled());
	वापस mdscr_पढ़ो() & DBG_MDSCR_SS;
पूर्ण
NOKPROBE_SYMBOL(kernel_active_single_step);

/* ptrace API */
व्योम user_enable_single_step(काष्ठा task_काष्ठा *task)
अणु
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(task);

	अगर (!test_and_set_ti_thपढ़ो_flag(ti, TIF_SINGLESTEP))
		set_regs_spsr_ss(task_pt_regs(task));
पूर्ण
NOKPROBE_SYMBOL(user_enable_single_step);

व्योम user_disable_single_step(काष्ठा task_काष्ठा *task)
अणु
	clear_ti_thपढ़ो_flag(task_thपढ़ो_info(task), TIF_SINGLESTEP);
पूर्ण
NOKPROBE_SYMBOL(user_disable_single_step);
