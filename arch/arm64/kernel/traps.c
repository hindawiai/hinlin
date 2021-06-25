<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Based on arch/arm/kernel/traps.c
 *
 * Copyright (C) 1995-2009 Russell King
 * Copyright (C) 2012 ARM Ltd.
 */

#समावेश <linux/bug.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/संकेत.स>
#समावेश <linux/personality.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/module.h>
#समावेश <linux/kexec.h>
#समावेश <linux/delay.h>
#समावेश <linux/init.h>
#समावेश <linux/sched/संकेत.स>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/sizes.h>
#समावेश <linux/syscalls.h>
#समावेश <linux/mm_types.h>
#समावेश <linux/kasan.h>

#समावेश <यंत्र/atomic.h>
#समावेश <यंत्र/bug.h>
#समावेश <यंत्र/cpufeature.h>
#समावेश <यंत्र/daअगरflags.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/esr.h>
#समावेश <यंत्र/exception.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/insn.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/traps.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/stack_poपूर्णांकer.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/प्रणाली_misc.h>
#समावेश <यंत्र/sysreg.h>

अटल स्थिर अक्षर *handler[] = अणु
	"Synchronous Abort",
	"IRQ",
	"FIQ",
	"Error"
पूर्ण;

पूर्णांक show_unhandled_संकेतs = 0;

अटल व्योम dump_kernel_instr(स्थिर अक्षर *lvl, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ addr = inकाष्ठाion_poपूर्णांकer(regs);
	अक्षर str[माप("00000000 ") * 5 + 2 + 1], *p = str;
	पूर्णांक i;

	अगर (user_mode(regs))
		वापस;

	क्रम (i = -4; i < 1; i++) अणु
		अचिन्हित पूर्णांक val, bad;

		bad = aarch64_insn_पढ़ो(&((u32 *)addr)[i], &val);

		अगर (!bad)
			p += प्र_लिखो(p, i == 0 ? "(%08x) " : "%08x ", val);
		अन्यथा अणु
			p += प्र_लिखो(p, "bad PC value");
			अवरोध;
		पूर्ण
	पूर्ण

	prपूर्णांकk("%sCode: %s\n", lvl, str);
पूर्ण

#अगर_घोषित CONFIG_PREEMPT
#घोषणा S_PREEMPT " PREEMPT"
#या_अगर defined(CONFIG_PREEMPT_RT)
#घोषणा S_PREEMPT " PREEMPT_RT"
#अन्यथा
#घोषणा S_PREEMPT ""
#पूर्ण_अगर

#घोषणा S_SMP " SMP"

अटल पूर्णांक __die(स्थिर अक्षर *str, पूर्णांक err, काष्ठा pt_regs *regs)
अणु
	अटल पूर्णांक die_counter;
	पूर्णांक ret;

	pr_emerg("Internal error: %s: %x [#%d]" S_PREEMPT S_SMP "\n",
		 str, err, ++die_counter);

	/* trap and error numbers are mostly meaningless on ARM */
	ret = notअगरy_die(DIE_OOPS, str, regs, err, 0, संक_अंश);
	अगर (ret == NOTIFY_STOP)
		वापस ret;

	prपूर्णांक_modules();
	show_regs(regs);

	dump_kernel_instr(KERN_EMERG, regs);

	वापस ret;
पूर्ण

अटल DEFINE_RAW_SPINLOCK(die_lock);

/*
 * This function is रक्षित against re-entrancy.
 */
व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, पूर्णांक err)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&die_lock, flags);

	oops_enter();

	console_verbose();
	bust_spinlocks(1);
	ret = __die(str, err, regs);

	अगर (regs && kexec_should_crash(current))
		crash_kexec(regs);

	bust_spinlocks(0);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	oops_निकास();

	अगर (in_पूर्णांकerrupt())
		panic("%s: Fatal exception in interrupt", str);
	अगर (panic_on_oops)
		panic("%s: Fatal exception", str);

	raw_spin_unlock_irqrestore(&die_lock, flags);

	अगर (ret != NOTIFY_STOP)
		करो_निकास(संक_अंश);
पूर्ण

अटल व्योम arm64_show_संकेत(पूर्णांक signo, स्थिर अक्षर *str)
अणु
	अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);
	काष्ठा task_काष्ठा *tsk = current;
	अचिन्हित पूर्णांक esr = tsk->thपढ़ो.fault_code;
	काष्ठा pt_regs *regs = task_pt_regs(tsk);

	/* Leave अगर the संकेत won't be shown */
	अगर (!show_unhandled_संकेतs ||
	    !unhandled_संकेत(tsk, signo) ||
	    !__ratelimit(&rs))
		वापस;

	pr_info("%s[%d]: unhandled exception: ", tsk->comm, task_pid_nr(tsk));
	अगर (esr)
		pr_cont("%s, ESR 0x%08x, ", esr_get_class_string(esr), esr);

	pr_cont("%s", str);
	prपूर्णांक_vma_addr(KERN_CONT " in ", regs->pc);
	pr_cont("\n");
	__show_regs(regs);
पूर्ण

व्योम arm64_क्रमce_sig_fault(पूर्णांक signo, पूर्णांक code, अचिन्हित दीर्घ far,
			   स्थिर अक्षर *str)
अणु
	arm64_show_संकेत(signo, str);
	अगर (signo == SIGKILL)
		क्रमce_sig(SIGKILL);
	अन्यथा
		क्रमce_sig_fault(signo, code, (व्योम __user *)far);
पूर्ण

व्योम arm64_क्रमce_sig_mceerr(पूर्णांक code, अचिन्हित दीर्घ far, लघु lsb,
			    स्थिर अक्षर *str)
अणु
	arm64_show_संकेत(SIGBUS, str);
	क्रमce_sig_mceerr(code, (व्योम __user *)far, lsb);
पूर्ण

व्योम arm64_क्रमce_sig_ptrace_त्रुटि_सं_trap(पूर्णांक त्रुटि_सं, अचिन्हित दीर्घ far,
				       स्थिर अक्षर *str)
अणु
	arm64_show_संकेत(SIGTRAP, str);
	क्रमce_sig_ptrace_त्रुटि_सं_trap(त्रुटि_सं, (व्योम __user *)far);
पूर्ण

व्योम arm64_notअगरy_die(स्थिर अक्षर *str, काष्ठा pt_regs *regs,
		      पूर्णांक signo, पूर्णांक sicode, अचिन्हित दीर्घ far,
		      पूर्णांक err)
अणु
	अगर (user_mode(regs)) अणु
		WARN_ON(regs != current_pt_regs());
		current->thपढ़ो.fault_address = 0;
		current->thपढ़ो.fault_code = err;

		arm64_क्रमce_sig_fault(signo, sicode, far, str);
	पूर्ण अन्यथा अणु
		die(str, regs, err);
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_COMPAT
#घोषणा PSTATE_IT_1_0_SHIFT	25
#घोषणा PSTATE_IT_1_0_MASK	(0x3 << PSTATE_IT_1_0_SHIFT)
#घोषणा PSTATE_IT_7_2_SHIFT	10
#घोषणा PSTATE_IT_7_2_MASK	(0x3f << PSTATE_IT_7_2_SHIFT)

अटल u32 compat_get_it_state(काष्ठा pt_regs *regs)
अणु
	u32 it, pstate = regs->pstate;

	it  = (pstate & PSTATE_IT_1_0_MASK) >> PSTATE_IT_1_0_SHIFT;
	it |= ((pstate & PSTATE_IT_7_2_MASK) >> PSTATE_IT_7_2_SHIFT) << 2;

	वापस it;
पूर्ण

अटल व्योम compat_set_it_state(काष्ठा pt_regs *regs, u32 it)
अणु
	u32 pstate_it;

	pstate_it  = (it << PSTATE_IT_1_0_SHIFT) & PSTATE_IT_1_0_MASK;
	pstate_it |= ((it >> 2) << PSTATE_IT_7_2_SHIFT) & PSTATE_IT_7_2_MASK;

	regs->pstate &= ~PSR_AA32_IT_MASK;
	regs->pstate |= pstate_it;
पूर्ण

अटल व्योम advance_itstate(काष्ठा pt_regs *regs)
अणु
	u32 it;

	/* ARM mode */
	अगर (!(regs->pstate & PSR_AA32_T_BIT) ||
	    !(regs->pstate & PSR_AA32_IT_MASK))
		वापस;

	it  = compat_get_it_state(regs);

	/*
	 * If this is the last inकाष्ठाion of the block, wipe the IT
	 * state. Otherwise advance it.
	 */
	अगर (!(it & 7))
		it = 0;
	अन्यथा
		it = (it & 0xe0) | ((it << 1) & 0x1f);

	compat_set_it_state(regs, it);
पूर्ण
#अन्यथा
अटल व्योम advance_itstate(काष्ठा pt_regs *regs)
अणु
पूर्ण
#पूर्ण_अगर

व्योम arm64_skip_faulting_inकाष्ठाion(काष्ठा pt_regs *regs, अचिन्हित दीर्घ size)
अणु
	regs->pc += size;

	/*
	 * If we were single stepping, we want to get the step exception after
	 * we वापस from the trap.
	 */
	अगर (user_mode(regs))
		user_fastक्रमward_single_step(current);

	अगर (compat_user_mode(regs))
		advance_itstate(regs);
	अन्यथा
		regs->pstate &= ~PSR_BTYPE_MASK;
पूर्ण

अटल LIST_HEAD(undef_hook);
अटल DEFINE_RAW_SPINLOCK(undef_lock);

व्योम रेजिस्टर_undef_hook(काष्ठा undef_hook *hook)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_add(&hook->node, &undef_hook);
	raw_spin_unlock_irqrestore(&undef_lock, flags);
पूर्ण

व्योम unरेजिस्टर_undef_hook(काष्ठा undef_hook *hook)
अणु
	अचिन्हित दीर्घ flags;

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_del(&hook->node);
	raw_spin_unlock_irqrestore(&undef_lock, flags);
पूर्ण

अटल पूर्णांक call_undef_hook(काष्ठा pt_regs *regs)
अणु
	काष्ठा undef_hook *hook;
	अचिन्हित दीर्घ flags;
	u32 instr;
	पूर्णांक (*fn)(काष्ठा pt_regs *regs, u32 instr) = शून्य;
	व्योम __user *pc = (व्योम __user *)inकाष्ठाion_poपूर्णांकer(regs);

	अगर (!user_mode(regs)) अणु
		__le32 instr_le;
		अगर (get_kernel_nofault(instr_le, (__क्रमce __le32 *)pc))
			जाओ निकास;
		instr = le32_to_cpu(instr_le);
	पूर्ण अन्यथा अगर (compat_thumb_mode(regs)) अणु
		/* 16-bit Thumb inकाष्ठाion */
		__le16 instr_le;
		अगर (get_user(instr_le, (__le16 __user *)pc))
			जाओ निकास;
		instr = le16_to_cpu(instr_le);
		अगर (aarch32_insn_is_wide(instr)) अणु
			u32 instr2;

			अगर (get_user(instr_le, (__le16 __user *)(pc + 2)))
				जाओ निकास;
			instr2 = le16_to_cpu(instr_le);
			instr = (instr << 16) | instr2;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 32-bit ARM inकाष्ठाion */
		__le32 instr_le;
		अगर (get_user(instr_le, (__le32 __user *)pc))
			जाओ निकास;
		instr = le32_to_cpu(instr_le);
	पूर्ण

	raw_spin_lock_irqsave(&undef_lock, flags);
	list_क्रम_each_entry(hook, &undef_hook, node)
		अगर ((instr & hook->instr_mask) == hook->instr_val &&
			(regs->pstate & hook->pstate_mask) == hook->pstate_val)
			fn = hook->fn;

	raw_spin_unlock_irqrestore(&undef_lock, flags);
निकास:
	वापस fn ? fn(regs, instr) : 1;
पूर्ण

व्योम क्रमce_संकेत_inject(पूर्णांक संकेत, पूर्णांक code, अचिन्हित दीर्घ address, अचिन्हित पूर्णांक err)
अणु
	स्थिर अक्षर *desc;
	काष्ठा pt_regs *regs = current_pt_regs();

	अगर (WARN_ON(!user_mode(regs)))
		वापस;

	चयन (संकेत) अणु
	हाल संक_अवैध:
		desc = "undefined instruction";
		अवरोध;
	हाल संक_अंश:
		desc = "illegal memory access";
		अवरोध;
	शेष:
		desc = "unknown or unrecoverable error";
		अवरोध;
	पूर्ण

	/* Force संकेतs we करोn't understand to SIGKILL */
	अगर (WARN_ON(संकेत != SIGKILL &&
		    siginfo_layout(संकेत, code) != SIL_FAULT)) अणु
		संकेत = SIGKILL;
	पूर्ण

	arm64_notअगरy_die(desc, regs, संकेत, code, address, err);
पूर्ण

/*
 * Set up process info to संकेत segmentation fault - called on access error.
 */
व्योम arm64_notअगरy_segfault(अचिन्हित दीर्घ addr)
अणु
	पूर्णांक code;

	mmap_पढ़ो_lock(current->mm);
	अगर (find_vma(current->mm, untagged_addr(addr)) == शून्य)
		code = SEGV_MAPERR;
	अन्यथा
		code = SEGV_ACCERR;
	mmap_पढ़ो_unlock(current->mm);

	क्रमce_संकेत_inject(संक_अंश, code, addr, 0);
पूर्ण

व्योम करो_undefinstr(काष्ठा pt_regs *regs)
अणु
	/* check क्रम AArch32 अवरोधpoपूर्णांक inकाष्ठाions */
	अगर (!aarch32_अवरोध_handler(regs))
		वापस;

	अगर (call_undef_hook(regs) == 0)
		वापस;

	BUG_ON(!user_mode(regs));
	क्रमce_संकेत_inject(संक_अवैध, ILL_ILLOPC, regs->pc, 0);
पूर्ण
NOKPROBE_SYMBOL(करो_undefinstr);

व्योम करो_bti(काष्ठा pt_regs *regs)
अणु
	BUG_ON(!user_mode(regs));
	क्रमce_संकेत_inject(संक_अवैध, ILL_ILLOPC, regs->pc, 0);
पूर्ण
NOKPROBE_SYMBOL(करो_bti);

व्योम करो_ptrauth_fault(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	/*
	 * Unexpected FPAC exception or poपूर्णांकer authentication failure in
	 * the kernel: समाप्त the task beक्रमe it करोes any more harm.
	 */
	BUG_ON(!user_mode(regs));
	क्रमce_संकेत_inject(संक_अवैध, ILL_ILLOPN, regs->pc, esr);
पूर्ण
NOKPROBE_SYMBOL(करो_ptrauth_fault);

#घोषणा __user_cache_मुख्यt(insn, address, res)			\
	अगर (address >= user_addr_max()) अणु			\
		res = -EFAULT;					\
	पूर्ण अन्यथा अणु						\
		uaccess_ttbr0_enable();				\
		यंत्र अस्थिर (					\
			"1:	" insn ", %1\n"			\
			"	mov	%w0, #0\n"		\
			"2:\n"					\
			"	.pushsection .fixup,\"ax\"\n"	\
			"	.align	2\n"			\
			"3:	mov	%w0, %w2\n"		\
			"	b	2b\n"			\
			"	.popsection\n"			\
			_ASM_EXTABLE(1b, 3b)			\
			: "=r" (res)				\
			: "r" (address), "i" (-EFAULT));	\
		uaccess_ttbr0_disable();			\
	पूर्ण

अटल व्योम user_cache_मुख्यt_handler(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ tagged_address, address;
	पूर्णांक rt = ESR_ELx_SYS64_ISS_RT(esr);
	पूर्णांक crm = (esr & ESR_ELx_SYS64_ISS_CRM_MASK) >> ESR_ELx_SYS64_ISS_CRM_SHIFT;
	पूर्णांक ret = 0;

	tagged_address = pt_regs_पढ़ो_reg(regs, rt);
	address = untagged_addr(tagged_address);

	चयन (crm) अणु
	हाल ESR_ELx_SYS64_ISS_CRM_DC_CVAU:	/* DC CVAU, माला_लो promoted */
		__user_cache_मुख्यt("dc civac", address, ret);
		अवरोध;
	हाल ESR_ELx_SYS64_ISS_CRM_DC_CVAC:	/* DC CVAC, माला_लो promoted */
		__user_cache_मुख्यt("dc civac", address, ret);
		अवरोध;
	हाल ESR_ELx_SYS64_ISS_CRM_DC_CVADP:	/* DC CVADP */
		__user_cache_मुख्यt("sys 3, c7, c13, 1", address, ret);
		अवरोध;
	हाल ESR_ELx_SYS64_ISS_CRM_DC_CVAP:	/* DC CVAP */
		__user_cache_मुख्यt("sys 3, c7, c12, 1", address, ret);
		अवरोध;
	हाल ESR_ELx_SYS64_ISS_CRM_DC_CIVAC:	/* DC CIVAC */
		__user_cache_मुख्यt("dc civac", address, ret);
		अवरोध;
	हाल ESR_ELx_SYS64_ISS_CRM_IC_IVAU:	/* IC IVAU */
		__user_cache_मुख्यt("ic ivau", address, ret);
		अवरोध;
	शेष:
		क्रमce_संकेत_inject(संक_अवैध, ILL_ILLOPC, regs->pc, 0);
		वापस;
	पूर्ण

	अगर (ret)
		arm64_notअगरy_segfault(tagged_address);
	अन्यथा
		arm64_skip_faulting_inकाष्ठाion(regs, AARCH64_INSN_SIZE);
पूर्ण

अटल व्योम ctr_पढ़ो_handler(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rt = ESR_ELx_SYS64_ISS_RT(esr);
	अचिन्हित दीर्घ val = arm64_ftr_reg_user_value(&arm64_ftr_reg_ctrel0);

	अगर (cpus_have_स्थिर_cap(ARM64_WORKAROUND_1542419)) अणु
		/* Hide DIC so that we can trap the unnecessary मुख्यtenance...*/
		val &= ~BIT(CTR_DIC_SHIFT);

		/* ... and fake IminLine to reduce the number of traps. */
		val &= ~CTR_IMINLINE_MASK;
		val |= (PAGE_SHIFT - 2) & CTR_IMINLINE_MASK;
	पूर्ण

	pt_regs_ग_लिखो_reg(regs, rt, val);

	arm64_skip_faulting_inकाष्ठाion(regs, AARCH64_INSN_SIZE);
पूर्ण

अटल व्योम cntvct_पढ़ो_handler(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rt = ESR_ELx_SYS64_ISS_RT(esr);

	pt_regs_ग_लिखो_reg(regs, rt, arch_समयr_पढ़ो_counter());
	arm64_skip_faulting_inकाष्ठाion(regs, AARCH64_INSN_SIZE);
पूर्ण

अटल व्योम cntfrq_पढ़ो_handler(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rt = ESR_ELx_SYS64_ISS_RT(esr);

	pt_regs_ग_लिखो_reg(regs, rt, arch_समयr_get_rate());
	arm64_skip_faulting_inकाष्ठाion(regs, AARCH64_INSN_SIZE);
पूर्ण

अटल व्योम mrs_handler(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	u32 sysreg, rt;

	rt = ESR_ELx_SYS64_ISS_RT(esr);
	sysreg = esr_sys64_to_sysreg(esr);

	अगर (करो_emulate_mrs(regs, sysreg, rt) != 0)
		क्रमce_संकेत_inject(संक_अवैध, ILL_ILLOPC, regs->pc, 0);
पूर्ण

अटल व्योम wfi_handler(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	arm64_skip_faulting_inकाष्ठाion(regs, AARCH64_INSN_SIZE);
पूर्ण

काष्ठा sys64_hook अणु
	अचिन्हित पूर्णांक esr_mask;
	अचिन्हित पूर्णांक esr_val;
	व्योम (*handler)(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs);
पूर्ण;

अटल स्थिर काष्ठा sys64_hook sys64_hooks[] = अणु
	अणु
		.esr_mask = ESR_ELx_SYS64_ISS_EL0_CACHE_OP_MASK,
		.esr_val = ESR_ELx_SYS64_ISS_EL0_CACHE_OP_VAL,
		.handler = user_cache_मुख्यt_handler,
	पूर्ण,
	अणु
		/* Trap पढ़ो access to CTR_EL0 */
		.esr_mask = ESR_ELx_SYS64_ISS_SYS_OP_MASK,
		.esr_val = ESR_ELx_SYS64_ISS_SYS_CTR_READ,
		.handler = ctr_पढ़ो_handler,
	पूर्ण,
	अणु
		/* Trap पढ़ो access to CNTVCT_EL0 */
		.esr_mask = ESR_ELx_SYS64_ISS_SYS_OP_MASK,
		.esr_val = ESR_ELx_SYS64_ISS_SYS_CNTVCT,
		.handler = cntvct_पढ़ो_handler,
	पूर्ण,
	अणु
		/* Trap पढ़ो access to CNTFRQ_EL0 */
		.esr_mask = ESR_ELx_SYS64_ISS_SYS_OP_MASK,
		.esr_val = ESR_ELx_SYS64_ISS_SYS_CNTFRQ,
		.handler = cntfrq_पढ़ो_handler,
	पूर्ण,
	अणु
		/* Trap पढ़ो access to CPUID रेजिस्टरs */
		.esr_mask = ESR_ELx_SYS64_ISS_SYS_MRS_OP_MASK,
		.esr_val = ESR_ELx_SYS64_ISS_SYS_MRS_OP_VAL,
		.handler = mrs_handler,
	पूर्ण,
	अणु
		/* Trap WFI inकाष्ठाions executed in userspace */
		.esr_mask = ESR_ELx_WFx_MASK,
		.esr_val = ESR_ELx_WFx_WFI_VAL,
		.handler = wfi_handler,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_COMPAT
अटल bool cp15_cond_valid(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक cond;

	/* Only a T32 inकाष्ठाion can trap without CV being set */
	अगर (!(esr & ESR_ELx_CV)) अणु
		u32 it;

		it = compat_get_it_state(regs);
		अगर (!it)
			वापस true;

		cond = it >> 4;
	पूर्ण अन्यथा अणु
		cond = (esr & ESR_ELx_COND_MASK) >> ESR_ELx_COND_SHIFT;
	पूर्ण

	वापस aarch32_opcode_cond_checks[cond](regs->pstate);
पूर्ण

अटल व्योम compat_cntfrq_पढ़ो_handler(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक reg = (esr & ESR_ELx_CP15_32_ISS_RT_MASK) >> ESR_ELx_CP15_32_ISS_RT_SHIFT;

	pt_regs_ग_लिखो_reg(regs, reg, arch_समयr_get_rate());
	arm64_skip_faulting_inकाष्ठाion(regs, 4);
पूर्ण

अटल स्थिर काष्ठा sys64_hook cp15_32_hooks[] = अणु
	अणु
		.esr_mask = ESR_ELx_CP15_32_ISS_SYS_MASK,
		.esr_val = ESR_ELx_CP15_32_ISS_SYS_CNTFRQ,
		.handler = compat_cntfrq_पढ़ो_handler,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

अटल व्योम compat_cntvct_पढ़ो_handler(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	पूर्णांक rt = (esr & ESR_ELx_CP15_64_ISS_RT_MASK) >> ESR_ELx_CP15_64_ISS_RT_SHIFT;
	पूर्णांक rt2 = (esr & ESR_ELx_CP15_64_ISS_RT2_MASK) >> ESR_ELx_CP15_64_ISS_RT2_SHIFT;
	u64 val = arch_समयr_पढ़ो_counter();

	pt_regs_ग_लिखो_reg(regs, rt, lower_32_bits(val));
	pt_regs_ग_लिखो_reg(regs, rt2, upper_32_bits(val));
	arm64_skip_faulting_inकाष्ठाion(regs, 4);
पूर्ण

अटल स्थिर काष्ठा sys64_hook cp15_64_hooks[] = अणु
	अणु
		.esr_mask = ESR_ELx_CP15_64_ISS_SYS_MASK,
		.esr_val = ESR_ELx_CP15_64_ISS_SYS_CNTVCT,
		.handler = compat_cntvct_पढ़ो_handler,
	पूर्ण,
	अणुपूर्ण,
पूर्ण;

व्योम करो_cp15instr(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा sys64_hook *hook, *hook_base;

	अगर (!cp15_cond_valid(esr, regs)) अणु
		/*
		 * There is no T16 variant of a CP access, so we
		 * always advance PC by 4 bytes.
		 */
		arm64_skip_faulting_inकाष्ठाion(regs, 4);
		वापस;
	पूर्ण

	चयन (ESR_ELx_EC(esr)) अणु
	हाल ESR_ELx_EC_CP15_32:
		hook_base = cp15_32_hooks;
		अवरोध;
	हाल ESR_ELx_EC_CP15_64:
		hook_base = cp15_64_hooks;
		अवरोध;
	शेष:
		करो_undefinstr(regs);
		वापस;
	पूर्ण

	क्रम (hook = hook_base; hook->handler; hook++)
		अगर ((hook->esr_mask & esr) == hook->esr_val) अणु
			hook->handler(esr, regs);
			वापस;
		पूर्ण

	/*
	 * New cp15 inकाष्ठाions may previously have been undefined at
	 * EL0. Fall back to our usual undefined inकाष्ठाion handler
	 * so that we handle these consistently.
	 */
	करो_undefinstr(regs);
पूर्ण
NOKPROBE_SYMBOL(करो_cp15instr);
#पूर्ण_अगर

व्योम करो_sysinstr(अचिन्हित पूर्णांक esr, काष्ठा pt_regs *regs)
अणु
	स्थिर काष्ठा sys64_hook *hook;

	क्रम (hook = sys64_hooks; hook->handler; hook++)
		अगर ((hook->esr_mask & esr) == hook->esr_val) अणु
			hook->handler(esr, regs);
			वापस;
		पूर्ण

	/*
	 * New SYS inकाष्ठाions may previously have been undefined at EL0. Fall
	 * back to our usual undefined inकाष्ठाion handler so that we handle
	 * these consistently.
	 */
	करो_undefinstr(regs);
पूर्ण
NOKPROBE_SYMBOL(करो_sysinstr);

अटल स्थिर अक्षर *esr_class_str[] = अणु
	[0 ... ESR_ELx_EC_MAX]		= "UNRECOGNIZED EC",
	[ESR_ELx_EC_UNKNOWN]		= "Unknown/Uncategorized",
	[ESR_ELx_EC_WFx]		= "WFI/WFE",
	[ESR_ELx_EC_CP15_32]		= "CP15 MCR/MRC",
	[ESR_ELx_EC_CP15_64]		= "CP15 MCRR/MRRC",
	[ESR_ELx_EC_CP14_MR]		= "CP14 MCR/MRC",
	[ESR_ELx_EC_CP14_LS]		= "CP14 LDC/STC",
	[ESR_ELx_EC_FP_ASIMD]		= "ASIMD",
	[ESR_ELx_EC_CP10_ID]		= "CP10 MRC/VMRS",
	[ESR_ELx_EC_PAC]		= "PAC",
	[ESR_ELx_EC_CP14_64]		= "CP14 MCRR/MRRC",
	[ESR_ELx_EC_BTI]		= "BTI",
	[ESR_ELx_EC_ILL]		= "PSTATE.IL",
	[ESR_ELx_EC_SVC32]		= "SVC (AArch32)",
	[ESR_ELx_EC_HVC32]		= "HVC (AArch32)",
	[ESR_ELx_EC_SMC32]		= "SMC (AArch32)",
	[ESR_ELx_EC_SVC64]		= "SVC (AArch64)",
	[ESR_ELx_EC_HVC64]		= "HVC (AArch64)",
	[ESR_ELx_EC_SMC64]		= "SMC (AArch64)",
	[ESR_ELx_EC_SYS64]		= "MSR/MRS (AArch64)",
	[ESR_ELx_EC_SVE]		= "SVE",
	[ESR_ELx_EC_ERET]		= "ERET/ERETAA/ERETAB",
	[ESR_ELx_EC_FPAC]		= "FPAC",
	[ESR_ELx_EC_IMP_DEF]		= "EL3 IMP DEF",
	[ESR_ELx_EC_IABT_LOW]		= "IABT (lower EL)",
	[ESR_ELx_EC_IABT_CUR]		= "IABT (current EL)",
	[ESR_ELx_EC_PC_ALIGN]		= "PC Alignment",
	[ESR_ELx_EC_DABT_LOW]		= "DABT (lower EL)",
	[ESR_ELx_EC_DABT_CUR]		= "DABT (current EL)",
	[ESR_ELx_EC_SP_ALIGN]		= "SP Alignment",
	[ESR_ELx_EC_FP_EXC32]		= "FP (AArch32)",
	[ESR_ELx_EC_FP_EXC64]		= "FP (AArch64)",
	[ESR_ELx_EC_SERROR]		= "SError",
	[ESR_ELx_EC_BREAKPT_LOW]	= "Breakpoint (lower EL)",
	[ESR_ELx_EC_BREAKPT_CUR]	= "Breakpoint (current EL)",
	[ESR_ELx_EC_SOFTSTP_LOW]	= "Software Step (lower EL)",
	[ESR_ELx_EC_SOFTSTP_CUR]	= "Software Step (current EL)",
	[ESR_ELx_EC_WATCHPT_LOW]	= "Watchpoint (lower EL)",
	[ESR_ELx_EC_WATCHPT_CUR]	= "Watchpoint (current EL)",
	[ESR_ELx_EC_BKPT32]		= "BKPT (AArch32)",
	[ESR_ELx_EC_VECTOR32]		= "Vector catch (AArch32)",
	[ESR_ELx_EC_BRK64]		= "BRK (AArch64)",
पूर्ण;

स्थिर अक्षर *esr_get_class_string(u32 esr)
अणु
	वापस esr_class_str[ESR_ELx_EC(esr)];
पूर्ण

/*
 * bad_mode handles the impossible हाल in the exception vector. This is always
 * fatal.
 */
यंत्रlinkage व्योम notrace bad_mode(काष्ठा pt_regs *regs, पूर्णांक reason, अचिन्हित पूर्णांक esr)
अणु
	arm64_enter_nmi(regs);

	console_verbose();

	pr_crit("Bad mode in %s handler detected on CPU%d, code 0x%08x -- %s\n",
		handler[reason], smp_processor_id(), esr,
		esr_get_class_string(esr));

	__show_regs(regs);
	local_daअगर_mask();
	panic("bad mode");
पूर्ण

/*
 * bad_el0_sync handles unexpected, but potentially recoverable synchronous
 * exceptions taken from EL0. Unlike bad_mode, this वापसs.
 */
व्योम bad_el0_sync(काष्ठा pt_regs *regs, पूर्णांक reason, अचिन्हित पूर्णांक esr)
अणु
	अचिन्हित दीर्घ pc = inकाष्ठाion_poपूर्णांकer(regs);

	current->thपढ़ो.fault_address = 0;
	current->thपढ़ो.fault_code = esr;

	arm64_क्रमce_sig_fault(संक_अवैध, ILL_ILLOPC, pc,
			      "Bad EL0 synchronous exception");
पूर्ण

#अगर_घोषित CONFIG_VMAP_STACK

DEFINE_PER_CPU(अचिन्हित दीर्घ [OVERFLOW_STACK_SIZE/माप(दीर्घ)], overflow_stack)
	__aligned(16);

यंत्रlinkage व्योम noinstr handle_bad_stack(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ tsk_stk = (अचिन्हित दीर्घ)current->stack;
	अचिन्हित दीर्घ irq_stk = (अचिन्हित दीर्घ)this_cpu_पढ़ो(irq_stack_ptr);
	अचिन्हित दीर्घ ovf_stk = (अचिन्हित दीर्घ)this_cpu_ptr(overflow_stack);
	अचिन्हित पूर्णांक esr = पढ़ो_sysreg(esr_el1);
	अचिन्हित दीर्घ far = पढ़ो_sysreg(far_el1);

	arm64_enter_nmi(regs);

	console_verbose();
	pr_emerg("Insufficient stack space to handle exception!");

	pr_emerg("ESR: 0x%08x -- %s\n", esr, esr_get_class_string(esr));
	pr_emerg("FAR: 0x%016lx\n", far);

	pr_emerg("Task stack:     [0x%016lx..0x%016lx]\n",
		 tsk_stk, tsk_stk + THREAD_SIZE);
	pr_emerg("IRQ stack:      [0x%016lx..0x%016lx]\n",
		 irq_stk, irq_stk + IRQ_STACK_SIZE);
	pr_emerg("Overflow stack: [0x%016lx..0x%016lx]\n",
		 ovf_stk, ovf_stk + OVERFLOW_STACK_SIZE);

	__show_regs(regs);

	/*
	 * We use nmi_panic to limit the potential क्रम recusive overflows, and
	 * to get a better stack trace.
	 */
	nmi_panic(शून्य, "kernel stack overflow");
	cpu_park_loop();
पूर्ण
#पूर्ण_अगर

व्योम __noवापस arm64_serror_panic(काष्ठा pt_regs *regs, u32 esr)
अणु
	console_verbose();

	pr_crit("SError Interrupt on CPU%d, code 0x%08x -- %s\n",
		smp_processor_id(), esr, esr_get_class_string(esr));
	अगर (regs)
		__show_regs(regs);

	nmi_panic(regs, "Asynchronous SError Interrupt");

	cpu_park_loop();
	unreachable();
पूर्ण

bool arm64_is_fatal_ras_serror(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	u32 aet = arm64_ras_serror_get_severity(esr);

	चयन (aet) अणु
	हाल ESR_ELx_AET_CE:	/* corrected error */
	हाल ESR_ELx_AET_UEO:	/* restartable, not yet consumed */
		/*
		 * The CPU can make progress. We may take UEO again as
		 * a more severe error.
		 */
		वापस false;

	हाल ESR_ELx_AET_UEU:	/* Uncorrected Unrecoverable */
	हाल ESR_ELx_AET_UER:	/* Uncorrected Recoverable */
		/*
		 * The CPU can't make progress. The exception may have
		 * been imprecise.
		 *
		 * Neoverse-N1 #1349291 means a non-KVM SError reported as
		 * Unrecoverable should be treated as Uncontainable. We
		 * call arm64_serror_panic() in both हालs.
		 */
		वापस true;

	हाल ESR_ELx_AET_UC:	/* Uncontainable or Uncategorized error */
	शेष:
		/* Error has been silently propagated */
		arm64_serror_panic(regs, esr);
	पूर्ण
पूर्ण

यंत्रlinkage व्योम noinstr करो_serror(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	arm64_enter_nmi(regs);

	/* non-RAS errors are not containable */
	अगर (!arm64_is_ras_serror(esr) || arm64_is_fatal_ras_serror(regs, esr))
		arm64_serror_panic(regs, esr);

	arm64_निकास_nmi(regs);
पूर्ण

/* GENERIC_BUG traps */

पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ addr)
अणु
	/*
	 * bug_handler() only called क्रम BRK #BUG_BRK_IMM.
	 * So the answer is trivial -- any spurious instances with no
	 * bug table entry will be rejected by report_bug() and passed
	 * back to the debug-monitors code and handled as a fatal
	 * unexpected debug exception.
	 */
	वापस 1;
पूर्ण

अटल पूर्णांक bug_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	चयन (report_bug(regs->pc, regs)) अणु
	हाल BUG_TRAP_TYPE_BUG:
		die("Oops - BUG", regs, 0);
		अवरोध;

	हाल BUG_TRAP_TYPE_WARN:
		अवरोध;

	शेष:
		/* unknown/unrecognised bug trap type */
		वापस DBG_HOOK_ERROR;
	पूर्ण

	/* If thपढ़ो survives, skip over the BUG inकाष्ठाion and जारी: */
	arm64_skip_faulting_inकाष्ठाion(regs, AARCH64_INSN_SIZE);
	वापस DBG_HOOK_HANDLED;
पूर्ण

अटल काष्ठा अवरोध_hook bug_अवरोध_hook = अणु
	.fn = bug_handler,
	.imm = BUG_BRK_IMM,
पूर्ण;

अटल पूर्णांक reserved_fault_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	pr_err("%s generated an invalid instruction at %pS!\n",
		in_bpf_jit(regs) ? "BPF JIT" : "Kernel text patching",
		(व्योम *)inकाष्ठाion_poपूर्णांकer(regs));

	/* We cannot handle this */
	वापस DBG_HOOK_ERROR;
पूर्ण

अटल काष्ठा अवरोध_hook fault_अवरोध_hook = अणु
	.fn = reserved_fault_handler,
	.imm = FAULT_BRK_IMM,
पूर्ण;

#अगर_घोषित CONFIG_KASAN_SW_TAGS

#घोषणा KASAN_ESR_RECOVER	0x20
#घोषणा KASAN_ESR_WRITE	0x10
#घोषणा KASAN_ESR_SIZE_MASK	0x0f
#घोषणा KASAN_ESR_SIZE(esr)	(1 << ((esr) & KASAN_ESR_SIZE_MASK))

अटल पूर्णांक kasan_handler(काष्ठा pt_regs *regs, अचिन्हित पूर्णांक esr)
अणु
	bool recover = esr & KASAN_ESR_RECOVER;
	bool ग_लिखो = esr & KASAN_ESR_WRITE;
	माप_प्रकार size = KASAN_ESR_SIZE(esr);
	u64 addr = regs->regs[0];
	u64 pc = regs->pc;

	kasan_report(addr, size, ग_लिखो, pc);

	/*
	 * The instrumentation allows to control whether we can proceed after
	 * a crash was detected. This is करोne by passing the -recover flag to
	 * the compiler. Disabling recovery allows to generate more compact
	 * code.
	 *
	 * Unक्रमtunately disabling recovery करोesn't work क्रम the kernel right
	 * now. KASAN reporting is disabled in some contexts (क्रम example when
	 * the allocator accesses slab object metadata; this is controlled by
	 * current->kasan_depth). All these accesses are detected by the tool,
	 * even though the reports क्रम them are not prपूर्णांकed.
	 *
	 * This is something that might be fixed at some poपूर्णांक in the future.
	 */
	अगर (!recover)
		die("Oops - KASAN", regs, 0);

	/* If thपढ़ो survives, skip over the brk inकाष्ठाion and जारी: */
	arm64_skip_faulting_inकाष्ठाion(regs, AARCH64_INSN_SIZE);
	वापस DBG_HOOK_HANDLED;
पूर्ण

अटल काष्ठा अवरोध_hook kasan_अवरोध_hook = अणु
	.fn	= kasan_handler,
	.imm	= KASAN_BRK_IMM,
	.mask	= KASAN_BRK_MASK,
पूर्ण;
#पूर्ण_अगर

/*
 * Initial handler क्रम AArch64 BRK exceptions
 * This handler only used until debug_traps_init().
 */
पूर्णांक __init early_brk64(अचिन्हित दीर्घ addr, अचिन्हित पूर्णांक esr,
		काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_KASAN_SW_TAGS
	अचिन्हित पूर्णांक comment = esr & ESR_ELx_BRK64_ISS_COMMENT_MASK;

	अगर ((comment & ~KASAN_BRK_MASK) == KASAN_BRK_IMM)
		वापस kasan_handler(regs, esr) != DBG_HOOK_HANDLED;
#पूर्ण_अगर
	वापस bug_handler(regs, esr) != DBG_HOOK_HANDLED;
पूर्ण

व्योम __init trap_init(व्योम)
अणु
	रेजिस्टर_kernel_अवरोध_hook(&bug_अवरोध_hook);
	रेजिस्टर_kernel_अवरोध_hook(&fault_अवरोध_hook);
#अगर_घोषित CONFIG_KASAN_SW_TAGS
	रेजिस्टर_kernel_अवरोध_hook(&kasan_अवरोध_hook);
#पूर्ण_अगर
	debug_traps_init();
पूर्ण
