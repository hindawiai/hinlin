<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Derived from "arch/i386/kernel/process.c"
 *    Copyright (C) 1995  Linus Torvalds
 *
 *  Updated and modअगरied by Cort Dougan (cort@cs.nmt.edu) and
 *  Paul Mackerras (paulus@cs.anu.edu.au)
 *
 *  PowerPC version
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/sched/task_stack.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/smp.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/slab.h>
#समावेश <linux/user.h>
#समावेश <linux/elf.h>
#समावेश <linux/prctl.h>
#समावेश <linux/init_task.h>
#समावेश <linux/export.h>
#समावेश <linux/kallsyms.h>
#समावेश <linux/mqueue.h>
#समावेश <linux/hardirq.h>
#समावेश <linux/utsname.h>
#समावेश <linux/ftrace.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/personality.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/hw_अवरोधpoपूर्णांक.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/elf-अक्रमomize.h>
#समावेश <linux/pkeys.h>
#समावेश <linux/seq_buf.h>

#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/processor.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/समय.स>
#समावेश <यंत्र/runlatch.h>
#समावेश <यंत्र/syscalls.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/पंचांग.h>
#समावेश <यंत्र/debug.h>
#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/hw_irq.h>
#पूर्ण_अगर
#समावेश <यंत्र/code-patching.h>
#समावेश <यंत्र/exec.h>
#समावेश <यंत्र/livepatch.h>
#समावेश <यंत्र/cpu_has_feature.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>

#समावेश <linux/kprobes.h>
#समावेश <linux/kdebug.h>

/* Transactional Memory debug */
#अगर_घोषित TM_DEBUG_SW
#घोषणा TM_DEBUG(x...) prपूर्णांकk(KERN_INFO x)
#अन्यथा
#घोषणा TM_DEBUG(x...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ _get_SP(व्योम);

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
/*
 * Are we running in "Suspend disabled" mode? If so we have to block any
 * sigवापस that would get us पूर्णांकo suspended state, and we also warn in some
 * other paths that we should never reach with suspend disabled.
 */
bool पंचांग_suspend_disabled __ro_after_init = false;

अटल व्योम check_अगर_पंचांग_restore_required(काष्ठा task_काष्ठा *tsk)
अणु
	/*
	 * If we are saving the current thपढ़ो's रेजिस्टरs, and the
	 * thपढ़ो is in a transactional state, set the TIF_RESTORE_TM
	 * bit so that we know to restore the रेजिस्टरs beक्रमe
	 * वापसing to userspace.
	 */
	अगर (tsk == current && tsk->thपढ़ो.regs &&
	    MSR_TM_ACTIVE(tsk->thपढ़ो.regs->msr) &&
	    !test_thपढ़ो_flag(TIF_RESTORE_TM)) अणु
		tsk->thपढ़ो.ckpt_regs.msr = tsk->thपढ़ो.regs->msr;
		set_thपढ़ो_flag(TIF_RESTORE_TM);
	पूर्ण
पूर्ण

#अन्यथा
अटल अंतरभूत व्योम check_अगर_पंचांग_restore_required(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

bool strict_msr_control;
EXPORT_SYMBOL(strict_msr_control);

अटल पूर्णांक __init enable_strict_msr_control(अक्षर *str)
अणु
	strict_msr_control = true;
	pr_info("Enabling strict facility control\n");

	वापस 0;
पूर्ण
early_param("ppc_strict_facility_enable", enable_strict_msr_control);

/* notrace because it's called by restore_math */
अचिन्हित दीर्घ notrace msr_check_and_set(अचिन्हित दीर्घ bits)
अणु
	अचिन्हित दीर्घ oldmsr = mfmsr();
	अचिन्हित दीर्घ newmsr;

	newmsr = oldmsr | bits;

	अगर (cpu_has_feature(CPU_FTR_VSX) && (bits & MSR_FP))
		newmsr |= MSR_VSX;

	अगर (oldmsr != newmsr)
		mपंचांगsr_isync(newmsr);

	वापस newmsr;
पूर्ण
EXPORT_SYMBOL_GPL(msr_check_and_set);

/* notrace because it's called by restore_math */
व्योम notrace __msr_check_and_clear(अचिन्हित दीर्घ bits)
अणु
	अचिन्हित दीर्घ oldmsr = mfmsr();
	अचिन्हित दीर्घ newmsr;

	newmsr = oldmsr & ~bits;

	अगर (cpu_has_feature(CPU_FTR_VSX) && (bits & MSR_FP))
		newmsr &= ~MSR_VSX;

	अगर (oldmsr != newmsr)
		mपंचांगsr_isync(newmsr);
पूर्ण
EXPORT_SYMBOL(__msr_check_and_clear);

#अगर_घोषित CONFIG_PPC_FPU
अटल व्योम __giveup_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ msr;

	save_fpu(tsk);
	msr = tsk->thपढ़ो.regs->msr;
	msr &= ~(MSR_FP|MSR_FE0|MSR_FE1);
	अगर (cpu_has_feature(CPU_FTR_VSX))
		msr &= ~MSR_VSX;
	tsk->thपढ़ो.regs->msr = msr;
पूर्ण

व्योम giveup_fpu(काष्ठा task_काष्ठा *tsk)
अणु
	check_अगर_पंचांग_restore_required(tsk);

	msr_check_and_set(MSR_FP);
	__giveup_fpu(tsk);
	msr_check_and_clear(MSR_FP);
पूर्ण
EXPORT_SYMBOL(giveup_fpu);

/*
 * Make sure the भग्नing-poपूर्णांक रेजिस्टर state in the
 * the thपढ़ो_काष्ठा is up to date क्रम task tsk.
 */
व्योम flush_fp_to_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->thपढ़ो.regs) अणु
		/*
		 * We need to disable preemption here because अगर we didn't,
		 * another process could get scheduled after the regs->msr
		 * test but beक्रमe we have finished saving the FP रेजिस्टरs
		 * to the thपढ़ो_काष्ठा.  That process could take over the
		 * FPU, and then when we get scheduled again we would store
		 * bogus values क्रम the reमुख्यing FP रेजिस्टरs.
		 */
		preempt_disable();
		अगर (tsk->thपढ़ो.regs->msr & MSR_FP) अणु
			/*
			 * This should only ever be called क्रम current or
			 * क्रम a stopped child process.  Since we save away
			 * the FP रेजिस्टर state on context चयन,
			 * there is something wrong अगर a stopped child appears
			 * to still have its FP state in the CPU रेजिस्टरs.
			 */
			BUG_ON(tsk != current);
			giveup_fpu(tsk);
		पूर्ण
		preempt_enable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(flush_fp_to_thपढ़ो);

व्योम enable_kernel_fp(व्योम)
अणु
	अचिन्हित दीर्घ cpumsr;

	WARN_ON(preemptible());

	cpumsr = msr_check_and_set(MSR_FP);

	अगर (current->thपढ़ो.regs && (current->thपढ़ो.regs->msr & MSR_FP)) अणु
		check_अगर_पंचांग_restore_required(current);
		/*
		 * If a thपढ़ो has alपढ़ोy been reclaimed then the
		 * checkpoपूर्णांकed रेजिस्टरs are on the CPU but have definitely
		 * been saved by the reclaim code. Don't need to and *cannot*
		 * giveup as this would save  to the 'live' काष्ठाure not the
		 * checkpoपूर्णांकed काष्ठाure.
		 */
		अगर (!MSR_TM_ACTIVE(cpumsr) &&
		     MSR_TM_ACTIVE(current->thपढ़ो.regs->msr))
			वापस;
		__giveup_fpu(current);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(enable_kernel_fp);
#अन्यथा
अटल अंतरभूत व्योम __giveup_fpu(काष्ठा task_काष्ठा *tsk) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_FPU */

#अगर_घोषित CONFIG_ALTIVEC
अटल व्योम __giveup_altivec(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ msr;

	save_altivec(tsk);
	msr = tsk->thपढ़ो.regs->msr;
	msr &= ~MSR_VEC;
	अगर (cpu_has_feature(CPU_FTR_VSX))
		msr &= ~MSR_VSX;
	tsk->thपढ़ो.regs->msr = msr;
पूर्ण

व्योम giveup_altivec(काष्ठा task_काष्ठा *tsk)
अणु
	check_अगर_पंचांग_restore_required(tsk);

	msr_check_and_set(MSR_VEC);
	__giveup_altivec(tsk);
	msr_check_and_clear(MSR_VEC);
पूर्ण
EXPORT_SYMBOL(giveup_altivec);

व्योम enable_kernel_altivec(व्योम)
अणु
	अचिन्हित दीर्घ cpumsr;

	WARN_ON(preemptible());

	cpumsr = msr_check_and_set(MSR_VEC);

	अगर (current->thपढ़ो.regs && (current->thपढ़ो.regs->msr & MSR_VEC)) अणु
		check_अगर_पंचांग_restore_required(current);
		/*
		 * If a thपढ़ो has alपढ़ोy been reclaimed then the
		 * checkpoपूर्णांकed रेजिस्टरs are on the CPU but have definitely
		 * been saved by the reclaim code. Don't need to and *cannot*
		 * giveup as this would save  to the 'live' काष्ठाure not the
		 * checkpoपूर्णांकed काष्ठाure.
		 */
		अगर (!MSR_TM_ACTIVE(cpumsr) &&
		     MSR_TM_ACTIVE(current->thपढ़ो.regs->msr))
			वापस;
		__giveup_altivec(current);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(enable_kernel_altivec);

/*
 * Make sure the VMX/Altivec रेजिस्टर state in the
 * the thपढ़ो_काष्ठा is up to date क्रम task tsk.
 */
व्योम flush_altivec_to_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->thपढ़ो.regs) अणु
		preempt_disable();
		अगर (tsk->thपढ़ो.regs->msr & MSR_VEC) अणु
			BUG_ON(tsk != current);
			giveup_altivec(tsk);
		पूर्ण
		preempt_enable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(flush_altivec_to_thपढ़ो);
#पूर्ण_अगर /* CONFIG_ALTIVEC */

#अगर_घोषित CONFIG_VSX
अटल व्योम __giveup_vsx(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ msr = tsk->thपढ़ो.regs->msr;

	/*
	 * We should never be ssetting MSR_VSX without also setting
	 * MSR_FP and MSR_VEC
	 */
	WARN_ON((msr & MSR_VSX) && !((msr & MSR_FP) && (msr & MSR_VEC)));

	/* __giveup_fpu will clear MSR_VSX */
	अगर (msr & MSR_FP)
		__giveup_fpu(tsk);
	अगर (msr & MSR_VEC)
		__giveup_altivec(tsk);
पूर्ण

अटल व्योम giveup_vsx(काष्ठा task_काष्ठा *tsk)
अणु
	check_अगर_पंचांग_restore_required(tsk);

	msr_check_and_set(MSR_FP|MSR_VEC|MSR_VSX);
	__giveup_vsx(tsk);
	msr_check_and_clear(MSR_FP|MSR_VEC|MSR_VSX);
पूर्ण

व्योम enable_kernel_vsx(व्योम)
अणु
	अचिन्हित दीर्घ cpumsr;

	WARN_ON(preemptible());

	cpumsr = msr_check_and_set(MSR_FP|MSR_VEC|MSR_VSX);

	अगर (current->thपढ़ो.regs &&
	    (current->thपढ़ो.regs->msr & (MSR_VSX|MSR_VEC|MSR_FP))) अणु
		check_अगर_पंचांग_restore_required(current);
		/*
		 * If a thपढ़ो has alपढ़ोy been reclaimed then the
		 * checkpoपूर्णांकed रेजिस्टरs are on the CPU but have definitely
		 * been saved by the reclaim code. Don't need to and *cannot*
		 * giveup as this would save  to the 'live' काष्ठाure not the
		 * checkpoपूर्णांकed काष्ठाure.
		 */
		अगर (!MSR_TM_ACTIVE(cpumsr) &&
		     MSR_TM_ACTIVE(current->thपढ़ो.regs->msr))
			वापस;
		__giveup_vsx(current);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(enable_kernel_vsx);

व्योम flush_vsx_to_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->thपढ़ो.regs) अणु
		preempt_disable();
		अगर (tsk->thपढ़ो.regs->msr & (MSR_VSX|MSR_VEC|MSR_FP)) अणु
			BUG_ON(tsk != current);
			giveup_vsx(tsk);
		पूर्ण
		preempt_enable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(flush_vsx_to_thपढ़ो);
#पूर्ण_अगर /* CONFIG_VSX */

#अगर_घोषित CONFIG_SPE
व्योम giveup_spe(काष्ठा task_काष्ठा *tsk)
अणु
	check_अगर_पंचांग_restore_required(tsk);

	msr_check_and_set(MSR_SPE);
	__giveup_spe(tsk);
	msr_check_and_clear(MSR_SPE);
पूर्ण
EXPORT_SYMBOL(giveup_spe);

व्योम enable_kernel_spe(व्योम)
अणु
	WARN_ON(preemptible());

	msr_check_and_set(MSR_SPE);

	अगर (current->thपढ़ो.regs && (current->thपढ़ो.regs->msr & MSR_SPE)) अणु
		check_अगर_पंचांग_restore_required(current);
		__giveup_spe(current);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(enable_kernel_spe);

व्योम flush_spe_to_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->thपढ़ो.regs) अणु
		preempt_disable();
		अगर (tsk->thपढ़ो.regs->msr & MSR_SPE) अणु
			BUG_ON(tsk != current);
			tsk->thपढ़ो.spefscr = mfspr(SPRN_SPEFSCR);
			giveup_spe(tsk);
		पूर्ण
		preempt_enable();
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_SPE */

अटल अचिन्हित दीर्घ msr_all_available;

अटल पूर्णांक __init init_msr_all_available(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_PPC_FPU))
		msr_all_available |= MSR_FP;
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		msr_all_available |= MSR_VEC;
	अगर (cpu_has_feature(CPU_FTR_VSX))
		msr_all_available |= MSR_VSX;
	अगर (cpu_has_feature(CPU_FTR_SPE))
		msr_all_available |= MSR_SPE;

	वापस 0;
पूर्ण
early_initcall(init_msr_all_available);

व्योम giveup_all(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ usermsr;

	अगर (!tsk->thपढ़ो.regs)
		वापस;

	check_अगर_पंचांग_restore_required(tsk);

	usermsr = tsk->thपढ़ो.regs->msr;

	अगर ((usermsr & msr_all_available) == 0)
		वापस;

	msr_check_and_set(msr_all_available);

	WARN_ON((usermsr & MSR_VSX) && !((usermsr & MSR_FP) && (usermsr & MSR_VEC)));

	अगर (usermsr & MSR_FP)
		__giveup_fpu(tsk);
	अगर (usermsr & MSR_VEC)
		__giveup_altivec(tsk);
	अगर (usermsr & MSR_SPE)
		__giveup_spe(tsk);

	msr_check_and_clear(msr_all_available);
पूर्ण
EXPORT_SYMBOL(giveup_all);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
#अगर_घोषित CONFIG_PPC_FPU
अटल bool should_restore_fp(व्योम)
अणु
	अगर (current->thपढ़ो.load_fp) अणु
		current->thपढ़ो.load_fp++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम करो_restore_fp(व्योम)
अणु
	load_fp_state(&current->thपढ़ो.fp_state);
पूर्ण
#अन्यथा
अटल bool should_restore_fp(व्योम) अणु वापस false; पूर्ण
अटल व्योम करो_restore_fp(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_FPU */

#अगर_घोषित CONFIG_ALTIVEC
अटल bool should_restore_altivec(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC) && (current->thपढ़ो.load_vec)) अणु
		current->thपढ़ो.load_vec++;
		वापस true;
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम करो_restore_altivec(व्योम)
अणु
	load_vr_state(&current->thपढ़ो.vr_state);
	current->thपढ़ो.used_vr = 1;
पूर्ण
#अन्यथा
अटल bool should_restore_altivec(व्योम) अणु वापस false; पूर्ण
अटल व्योम करो_restore_altivec(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_ALTIVEC */

अटल bool should_restore_vsx(व्योम)
अणु
	अगर (cpu_has_feature(CPU_FTR_VSX))
		वापस true;
	वापस false;
पूर्ण
#अगर_घोषित CONFIG_VSX
अटल व्योम करो_restore_vsx(व्योम)
अणु
	current->thपढ़ो.used_vsr = 1;
पूर्ण
#अन्यथा
अटल व्योम करो_restore_vsx(व्योम) अणु पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

/*
 * The exception निकास path calls restore_math() with पूर्णांकerrupts hard disabled
 * but the soft irq state not "reconciled". ftrace code that calls
 * local_irq_save/restore causes warnings.
 *
 * Rather than complicate the निकास path, just करोn't trace restore_math. This
 * could be करोne by having ftrace entry code check क्रम this un-reconciled
 * condition where MSR[EE]=0 and PACA_IRQ_HARD_DIS is not set, and
 * temporarily fix it up क्रम the duration of the ftrace call.
 */
व्योम notrace restore_math(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ msr;
	अचिन्हित दीर्घ new_msr = 0;

	msr = regs->msr;

	/*
	 * new_msr tracks the facilities that are to be restored. Only reload
	 * अगर the bit is not set in the user MSR (अगर it is set, the रेजिस्टरs
	 * are live क्रम the user thपढ़ो).
	 */
	अगर ((!(msr & MSR_FP)) && should_restore_fp())
		new_msr |= MSR_FP;

	अगर ((!(msr & MSR_VEC)) && should_restore_altivec())
		new_msr |= MSR_VEC;

	अगर ((!(msr & MSR_VSX)) && should_restore_vsx()) अणु
		अगर (((msr | new_msr) & (MSR_FP | MSR_VEC)) == (MSR_FP | MSR_VEC))
			new_msr |= MSR_VSX;
	पूर्ण

	अगर (new_msr) अणु
		अचिन्हित दीर्घ fpexc_mode = 0;

		msr_check_and_set(new_msr);

		अगर (new_msr & MSR_FP) अणु
			करो_restore_fp();

			// This also covers VSX, because VSX implies FP
			fpexc_mode = current->thपढ़ो.fpexc_mode;
		पूर्ण

		अगर (new_msr & MSR_VEC)
			करो_restore_altivec();

		अगर (new_msr & MSR_VSX)
			करो_restore_vsx();

		msr_check_and_clear(new_msr);

		regs->msr |= new_msr | fpexc_mode;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

अटल व्योम save_all(काष्ठा task_काष्ठा *tsk)
अणु
	अचिन्हित दीर्घ usermsr;

	अगर (!tsk->thपढ़ो.regs)
		वापस;

	usermsr = tsk->thपढ़ो.regs->msr;

	अगर ((usermsr & msr_all_available) == 0)
		वापस;

	msr_check_and_set(msr_all_available);

	WARN_ON((usermsr & MSR_VSX) && !((usermsr & MSR_FP) && (usermsr & MSR_VEC)));

	अगर (usermsr & MSR_FP)
		save_fpu(tsk);

	अगर (usermsr & MSR_VEC)
		save_altivec(tsk);

	अगर (usermsr & MSR_SPE)
		__giveup_spe(tsk);

	msr_check_and_clear(msr_all_available);
पूर्ण

व्योम flush_all_to_thपढ़ो(काष्ठा task_काष्ठा *tsk)
अणु
	अगर (tsk->thपढ़ो.regs) अणु
		preempt_disable();
		BUG_ON(tsk != current);
#अगर_घोषित CONFIG_SPE
		अगर (tsk->thपढ़ो.regs->msr & MSR_SPE)
			tsk->thपढ़ो.spefscr = mfspr(SPRN_SPEFSCR);
#पूर्ण_अगर
		save_all(tsk);

		preempt_enable();
	पूर्ण
पूर्ण
EXPORT_SYMBOL(flush_all_to_thपढ़ो);

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
व्योम करो_send_trap(काष्ठा pt_regs *regs, अचिन्हित दीर्घ address,
		  अचिन्हित दीर्घ error_code, पूर्णांक अवरोधpt)
अणु
	current->thपढ़ो.trap_nr = TRAP_HWBKPT;
	अगर (notअगरy_die(DIE_DABR_MATCH, "dabr_match", regs, error_code,
			11, संक_अंश) == NOTIFY_STOP)
		वापस;

	/* Deliver the संकेत to userspace */
	क्रमce_sig_ptrace_त्रुटि_सं_trap(अवरोधpt, /* अवरोधpoपूर्णांक or watchpoपूर्णांक id */
				    (व्योम __user *)address);
पूर्ण
#अन्यथा	/* !CONFIG_PPC_ADV_DEBUG_REGS */

अटल व्योम करो_अवरोध_handler(काष्ठा pt_regs *regs)
अणु
	काष्ठा arch_hw_अवरोधpoपूर्णांक null_brk = अणु0पूर्ण;
	काष्ठा arch_hw_अवरोधpoपूर्णांक *info;
	काष्ठा ppc_inst instr = ppc_inst(0);
	पूर्णांक type = 0;
	पूर्णांक size = 0;
	अचिन्हित दीर्घ ea;
	पूर्णांक i;

	/*
	 * If underneath hw supports only one watchpoपूर्णांक, we know it
	 * caused exception. 8xx also falls पूर्णांकo this category.
	 */
	अगर (nr_wp_slots() == 1) अणु
		__set_अवरोधpoपूर्णांक(0, &null_brk);
		current->thपढ़ो.hw_brk[0] = null_brk;
		current->thपढ़ो.hw_brk[0].flags |= HW_BRK_FLAG_DISABLED;
		वापस;
	पूर्ण

	/* Otherwise finकरोut which DAWR caused exception and disable it. */
	wp_get_instr_detail(regs, &instr, &type, &size, &ea);

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		info = &current->thपढ़ो.hw_brk[i];
		अगर (!info->address)
			जारी;

		अगर (wp_check_स्थिरraपूर्णांकs(regs, instr, ea, type, size, info)) अणु
			__set_अवरोधpoपूर्णांक(i, &null_brk);
			current->thपढ़ो.hw_brk[i] = null_brk;
			current->thपढ़ो.hw_brk[i].flags |= HW_BRK_FLAG_DISABLED;
		पूर्ण
	पूर्ण
पूर्ण

DEFINE_INTERRUPT_HANDLER(करो_अवरोध)
अणु
	current->thपढ़ो.trap_nr = TRAP_HWBKPT;
	अगर (notअगरy_die(DIE_DABR_MATCH, "dabr_match", regs, regs->dsisr,
			11, संक_अंश) == NOTIFY_STOP)
		वापस;

	अगर (debugger_अवरोध_match(regs))
		वापस;

	/*
	 * We reach here only when watchpoपूर्णांक exception is generated by ptrace
	 * event (or hw is buggy!). Now अगर CONFIG_HAVE_HW_BREAKPOINT is set,
	 * watchpoपूर्णांक is alपढ़ोy handled by hw_अवरोधpoपूर्णांक_handler() so we करोn't
	 * have to करो anything. But when CONFIG_HAVE_HW_BREAKPOINT is not set,
	 * we need to manually handle the watchpoपूर्णांक here.
	 */
	अगर (!IS_ENABLED(CONFIG_HAVE_HW_BREAKPOINT))
		करो_अवरोध_handler(regs);

	/* Deliver the संकेत to userspace */
	क्रमce_sig_fault(SIGTRAP, TRAP_HWBKPT, (व्योम __user *)regs->dar);
पूर्ण
#पूर्ण_अगर	/* CONFIG_PPC_ADV_DEBUG_REGS */

अटल DEFINE_PER_CPU(काष्ठा arch_hw_अवरोधpoपूर्णांक, current_brk[HBP_NUM_MAX]);

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
/*
 * Set the debug रेजिस्टरs back to their शेष "safe" values.
 */
अटल व्योम set_debug_reg_शेषs(काष्ठा thपढ़ो_काष्ठा *thपढ़ो)
अणु
	thपढ़ो->debug.iac1 = thपढ़ो->debug.iac2 = 0;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	thपढ़ो->debug.iac3 = thपढ़ो->debug.iac4 = 0;
#पूर्ण_अगर
	thपढ़ो->debug.dac1 = thपढ़ो->debug.dac2 = 0;
#अगर CONFIG_PPC_ADV_DEBUG_DVCS > 0
	thपढ़ो->debug.dvc1 = thपढ़ो->debug.dvc2 = 0;
#पूर्ण_अगर
	thपढ़ो->debug.dbcr0 = 0;
#अगर_घोषित CONFIG_BOOKE
	/*
	 * Force User/Supervisor bits to b11 (user-only MSR[PR]=1)
	 */
	thपढ़ो->debug.dbcr1 = DBCR1_IAC1US | DBCR1_IAC2US |
			DBCR1_IAC3US | DBCR1_IAC4US;
	/*
	 * Force Data Address Compare User/Supervisor bits to be User-only
	 * (0b11 MSR[PR]=1) and set all other bits in DBCR2 रेजिस्टर to be 0.
	 */
	thपढ़ो->debug.dbcr2 = DBCR2_DAC1US | DBCR2_DAC2US;
#अन्यथा
	thपढ़ो->debug.dbcr1 = 0;
#पूर्ण_अगर
पूर्ण

अटल व्योम prime_debug_regs(काष्ठा debug_reg *debug)
अणु
	/*
	 * We could have inherited MSR_DE from userspace, since
	 * it करोesn't get cleared on exception entry.  Make sure
	 * MSR_DE is clear beक्रमe we enable any debug events.
	 */
	mपंचांगsr(mfmsr() & ~MSR_DE);

	mtspr(SPRN_IAC1, debug->iac1);
	mtspr(SPRN_IAC2, debug->iac2);
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	mtspr(SPRN_IAC3, debug->iac3);
	mtspr(SPRN_IAC4, debug->iac4);
#पूर्ण_अगर
	mtspr(SPRN_DAC1, debug->dac1);
	mtspr(SPRN_DAC2, debug->dac2);
#अगर CONFIG_PPC_ADV_DEBUG_DVCS > 0
	mtspr(SPRN_DVC1, debug->dvc1);
	mtspr(SPRN_DVC2, debug->dvc2);
#पूर्ण_अगर
	mtspr(SPRN_DBCR0, debug->dbcr0);
	mtspr(SPRN_DBCR1, debug->dbcr1);
#अगर_घोषित CONFIG_BOOKE
	mtspr(SPRN_DBCR2, debug->dbcr2);
#पूर्ण_अगर
पूर्ण
/*
 * Unless neither the old or new thपढ़ो are making use of the
 * debug रेजिस्टरs, set the debug रेजिस्टरs from the values
 * stored in the new thपढ़ो.
 */
व्योम चयन_booke_debug_regs(काष्ठा debug_reg *new_debug)
अणु
	अगर ((current->thपढ़ो.debug.dbcr0 & DBCR0_IDM)
		|| (new_debug->dbcr0 & DBCR0_IDM))
			prime_debug_regs(new_debug);
पूर्ण
EXPORT_SYMBOL_GPL(चयन_booke_debug_regs);
#अन्यथा	/* !CONFIG_PPC_ADV_DEBUG_REGS */
#अगर_अघोषित CONFIG_HAVE_HW_BREAKPOINT
अटल व्योम set_अवरोधpoपूर्णांक(पूर्णांक i, काष्ठा arch_hw_अवरोधpoपूर्णांक *brk)
अणु
	preempt_disable();
	__set_अवरोधpoपूर्णांक(i, brk);
	preempt_enable();
पूर्ण

अटल व्योम set_debug_reg_शेषs(काष्ठा thपढ़ो_काष्ठा *thपढ़ो)
अणु
	पूर्णांक i;
	काष्ठा arch_hw_अवरोधpoपूर्णांक null_brk = अणु0पूर्ण;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		thपढ़ो->hw_brk[i] = null_brk;
		अगर (ppc_अवरोधpoपूर्णांक_available())
			set_अवरोधpoपूर्णांक(i, &thपढ़ो->hw_brk[i]);
	पूर्ण
पूर्ण

अटल अंतरभूत bool hw_brk_match(काष्ठा arch_hw_अवरोधpoपूर्णांक *a,
				काष्ठा arch_hw_अवरोधpoपूर्णांक *b)
अणु
	अगर (a->address != b->address)
		वापस false;
	अगर (a->type != b->type)
		वापस false;
	अगर (a->len != b->len)
		वापस false;
	/* no need to check hw_len. it's calculated from address and len */
	वापस true;
पूर्ण

अटल व्योम चयन_hw_अवरोधpoपूर्णांक(काष्ठा task_काष्ठा *new)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < nr_wp_slots(); i++) अणु
		अगर (likely(hw_brk_match(this_cpu_ptr(&current_brk[i]),
					&new->thपढ़ो.hw_brk[i])))
			जारी;

		__set_अवरोधpoपूर्णांक(i, &new->thपढ़ो.hw_brk[i]);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* !CONFIG_HAVE_HW_BREAKPOINT */
#पूर्ण_अगर	/* CONFIG_PPC_ADV_DEBUG_REGS */

अटल अंतरभूत पूर्णांक set_dabr(काष्ठा arch_hw_अवरोधpoपूर्णांक *brk)
अणु
	अचिन्हित दीर्घ dabr, dabrx;

	dabr = brk->address | (brk->type & HW_BRK_TYPE_DABR);
	dabrx = ((brk->type >> 3) & 0x7);

	अगर (ppc_md.set_dabr)
		वापस ppc_md.set_dabr(dabr, dabrx);

	अगर (IS_ENABLED(CONFIG_PPC_ADV_DEBUG_REGS)) अणु
		mtspr(SPRN_DAC1, dabr);
		अगर (IS_ENABLED(CONFIG_PPC_47x))
			isync();
		वापस 0;
	पूर्ण अन्यथा अगर (IS_ENABLED(CONFIG_PPC_BOOK3S)) अणु
		mtspr(SPRN_DABR, dabr);
		अगर (cpu_has_feature(CPU_FTR_DABRX))
			mtspr(SPRN_DABRX, dabrx);
		वापस 0;
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक set_अवरोधpoपूर्णांक_8xx(काष्ठा arch_hw_अवरोधpoपूर्णांक *brk)
अणु
	अचिन्हित दीर्घ lctrl1 = LCTRL1_CTE_GT | LCTRL1_CTF_LT | LCTRL1_CRWE_RW |
			       LCTRL1_CRWF_RW;
	अचिन्हित दीर्घ lctrl2 = LCTRL2_LW0EN | LCTRL2_LW0LADC | LCTRL2_SLW0EN;
	अचिन्हित दीर्घ start_addr = ALIGN_DOWN(brk->address, HW_BREAKPOINT_SIZE);
	अचिन्हित दीर्घ end_addr = ALIGN(brk->address + brk->len, HW_BREAKPOINT_SIZE);

	अगर (start_addr == 0)
		lctrl2 |= LCTRL2_LW0LA_F;
	अन्यथा अगर (end_addr == 0)
		lctrl2 |= LCTRL2_LW0LA_E;
	अन्यथा
		lctrl2 |= LCTRL2_LW0LA_EandF;

	mtspr(SPRN_LCTRL2, 0);

	अगर ((brk->type & HW_BRK_TYPE_RDWR) == 0)
		वापस 0;

	अगर ((brk->type & HW_BRK_TYPE_RDWR) == HW_BRK_TYPE_READ)
		lctrl1 |= LCTRL1_CRWE_RO | LCTRL1_CRWF_RO;
	अगर ((brk->type & HW_BRK_TYPE_RDWR) == HW_BRK_TYPE_WRITE)
		lctrl1 |= LCTRL1_CRWE_WO | LCTRL1_CRWF_WO;

	mtspr(SPRN_CMPE, start_addr - 1);
	mtspr(SPRN_CMPF, end_addr);
	mtspr(SPRN_LCTRL1, lctrl1);
	mtspr(SPRN_LCTRL2, lctrl2);

	वापस 0;
पूर्ण

व्योम __set_अवरोधpoपूर्णांक(पूर्णांक nr, काष्ठा arch_hw_अवरोधpoपूर्णांक *brk)
अणु
	स_नकल(this_cpu_ptr(&current_brk[nr]), brk, माप(*brk));

	अगर (dawr_enabled())
		// Power8 or later
		set_dawr(nr, brk);
	अन्यथा अगर (IS_ENABLED(CONFIG_PPC_8xx))
		set_अवरोधpoपूर्णांक_8xx(brk);
	अन्यथा अगर (!cpu_has_feature(CPU_FTR_ARCH_207S))
		// Power7 or earlier
		set_dabr(brk);
	अन्यथा
		// Shouldn't happen due to higher level checks
		WARN_ON_ONCE(1);
पूर्ण

/* Check अगर we have DAWR or DABR hardware */
bool ppc_अवरोधpoपूर्णांक_available(व्योम)
अणु
	अगर (dawr_enabled())
		वापस true; /* POWER8 DAWR or POWER9 क्रमced DAWR */
	अगर (cpu_has_feature(CPU_FTR_ARCH_207S))
		वापस false; /* POWER9 with DAWR disabled */
	/* DABR: Everything but POWER8 and POWER9 */
	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(ppc_अवरोधpoपूर्णांक_available);

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM

अटल अंतरभूत bool पंचांग_enabled(काष्ठा task_काष्ठा *tsk)
अणु
	वापस tsk && tsk->thपढ़ो.regs && (tsk->thपढ़ो.regs->msr & MSR_TM);
पूर्ण

अटल व्योम पंचांग_reclaim_thपढ़ो(काष्ठा thपढ़ो_काष्ठा *thr, uपूर्णांक8_t cause)
अणु
	/*
	 * Use the current MSR TM suspended bit to track अगर we have
	 * checkpoपूर्णांकed state outstanding.
	 * On संकेत delivery, we'd normally reclaim the checkpoपूर्णांकed
	 * state to obtain stack poपूर्णांकer (see:get_पंचांग_stackpoपूर्णांकer()).
	 * This will then directly वापस to userspace without going
	 * through __चयन_to(). However, अगर the stack frame is bad,
	 * we need to निकास this thपढ़ो which calls __चयन_to() which
	 * will again attempt to reclaim the alपढ़ोy saved पंचांग state.
	 * Hence we need to check that we've not alपढ़ोy reclaimed
	 * this state.
	 * We करो this using the current MSR, rather tracking it in
	 * some specअगरic thपढ़ो_काष्ठा bit, as it has the additional
	 * benefit of checking क्रम a potential TM bad thing exception.
	 */
	अगर (!MSR_TM_SUSPENDED(mfmsr()))
		वापस;

	giveup_all(container_of(thr, काष्ठा task_काष्ठा, thपढ़ो));

	पंचांग_reclaim(thr, cause);

	/*
	 * If we are in a transaction and FP is off then we can't have
	 * used FP inside that transaction. Hence the checkpoपूर्णांकed
	 * state is the same as the live state. We need to copy the
	 * live state to the checkpoपूर्णांकed state so that when the
	 * transaction is restored, the checkpoपूर्णांकed state is correct
	 * and the पातed transaction sees the correct state. We use
	 * ckpt_regs.msr here as that's what पंचांग_reclaim will use to
	 * determine अगर it's going to ग_लिखो the checkpoपूर्णांकed state or
	 * not. So either this will ग_लिखो the checkpoपूर्णांकed रेजिस्टरs,
	 * or reclaim will. Similarly क्रम VMX.
	 */
	अगर ((thr->ckpt_regs.msr & MSR_FP) == 0)
		स_नकल(&thr->ckfp_state, &thr->fp_state,
		       माप(काष्ठा thपढ़ो_fp_state));
	अगर ((thr->ckpt_regs.msr & MSR_VEC) == 0)
		स_नकल(&thr->ckvr_state, &thr->vr_state,
		       माप(काष्ठा thपढ़ो_vr_state));
पूर्ण

व्योम पंचांग_reclaim_current(uपूर्णांक8_t cause)
अणु
	पंचांग_enable();
	पंचांग_reclaim_thपढ़ो(&current->thपढ़ो, cause);
पूर्ण

अटल अंतरभूत व्योम पंचांग_reclaim_task(काष्ठा task_काष्ठा *tsk)
अणु
	/* We have to work out अगर we're switching from/to a task that's in the
	 * middle of a transaction.
	 *
	 * In चयनing we need to मुख्यtain a 2nd रेजिस्टर state as
	 * oldtask->thपढ़ो.ckpt_regs.  We पंचांग_reclaim(oldproc); this saves the
	 * checkpoपूर्णांकed (tbegin) state in ckpt_regs, ckfp_state and
	 * ckvr_state
	 *
	 * We also context चयन (save) TFHAR/TEXASR/TFIAR in here.
	 */
	काष्ठा thपढ़ो_काष्ठा *thr = &tsk->thपढ़ो;

	अगर (!thr->regs)
		वापस;

	अगर (!MSR_TM_ACTIVE(thr->regs->msr))
		जाओ out_and_saveregs;

	WARN_ON(पंचांग_suspend_disabled);

	TM_DEBUG("--- tm_reclaim on pid %d (NIP=%lx, "
		 "ccr=%lx, msr=%lx, trap=%lx)\n",
		 tsk->pid, thr->regs->nip,
		 thr->regs->ccr, thr->regs->msr,
		 thr->regs->trap);

	पंचांग_reclaim_thपढ़ो(thr, TM_CAUSE_RESCHED);

	TM_DEBUG("--- tm_reclaim on pid %d complete\n",
		 tsk->pid);

out_and_saveregs:
	/* Always save the regs here, even अगर a transaction's not active.
	 * This context-चयनes a thपढ़ो's TM info SPRs.  We करो it here to
	 * be consistent with the restore path (in recheckpoपूर्णांक) which
	 * cannot happen later in _चयन().
	 */
	पंचांग_save_sprs(thr);
पूर्ण

बाह्य व्योम __पंचांग_recheckpoपूर्णांक(काष्ठा thपढ़ो_काष्ठा *thपढ़ो);

व्योम पंचांग_recheckpoपूर्णांक(काष्ठा thपढ़ो_काष्ठा *thपढ़ो)
अणु
	अचिन्हित दीर्घ flags;

	अगर (!(thपढ़ो->regs->msr & MSR_TM))
		वापस;

	/* We really can't be interrupted here as the TEXASR registers can't
	 * change and later in the trecheckpoपूर्णांक code, we have a userspace R1.
	 * So let's hard disable over this region.
	 */
	local_irq_save(flags);
	hard_irq_disable();

	/* The TM SPRs are restored here, so that TEXASR.FS can be set
	 * beक्रमe the trecheckpoपूर्णांक and no explosion occurs.
	 */
	पंचांग_restore_sprs(thपढ़ो);

	__पंचांग_recheckpoपूर्णांक(thपढ़ो);

	local_irq_restore(flags);
पूर्ण

अटल अंतरभूत व्योम पंचांग_recheckpoपूर्णांक_new_task(काष्ठा task_काष्ठा *new)
अणु
	अगर (!cpu_has_feature(CPU_FTR_TM))
		वापस;

	/* Recheckpoपूर्णांक the रेजिस्टरs of the thपढ़ो we're about to चयन to.
	 *
	 * If the task was using FP, we non-lazily reload both the original and
	 * the speculative FP रेजिस्टर states.  This is because the kernel
	 * करोesn't see अगर/when a TM rollback occurs, so अगर we take an FP
	 * unavailable later, we are unable to determine which set of FP regs
	 * need to be restored.
	 */
	अगर (!पंचांग_enabled(new))
		वापस;

	अगर (!MSR_TM_ACTIVE(new->thपढ़ो.regs->msr))अणु
		पंचांग_restore_sprs(&new->thपढ़ो);
		वापस;
	पूर्ण
	/* Recheckpoपूर्णांक to restore original checkpoपूर्णांकed रेजिस्टर state. */
	TM_DEBUG("*** tm_recheckpoint of pid %d (new->msr 0x%lx)\n",
		 new->pid, new->thपढ़ो.regs->msr);

	पंचांग_recheckpoपूर्णांक(&new->thपढ़ो);

	/*
	 * The checkpoपूर्णांकed state has been restored but the live state has
	 * not, ensure all the math functionality is turned off to trigger
	 * restore_math() to reload.
	 */
	new->thपढ़ो.regs->msr &= ~(MSR_FP | MSR_VEC | MSR_VSX);

	TM_DEBUG("*** tm_recheckpoint of pid %d complete "
		 "(kernel msr 0x%lx)\n",
		 new->pid, mfmsr());
पूर्ण

अटल अंतरभूत व्योम __चयन_to_पंचांग(काष्ठा task_काष्ठा *prev,
		काष्ठा task_काष्ठा *new)
अणु
	अगर (cpu_has_feature(CPU_FTR_TM)) अणु
		अगर (पंचांग_enabled(prev) || पंचांग_enabled(new))
			पंचांग_enable();

		अगर (पंचांग_enabled(prev)) अणु
			prev->thपढ़ो.load_पंचांग++;
			पंचांग_reclaim_task(prev);
			अगर (!MSR_TM_ACTIVE(prev->thपढ़ो.regs->msr) && prev->thपढ़ो.load_पंचांग == 0)
				prev->thपढ़ो.regs->msr &= ~MSR_TM;
		पूर्ण

		पंचांग_recheckpoपूर्णांक_new_task(new);
	पूर्ण
पूर्ण

/*
 * This is called अगर we are on the way out to userspace and the
 * TIF_RESTORE_TM flag is set.  It checks अगर we need to reload
 * FP and/or vector state and करोes so अगर necessary.
 * If userspace is inside a transaction (whether active or
 * suspended) and FP/VMX/VSX inकाष्ठाions have ever been enabled
 * inside that transaction, then we have to keep them enabled
 * and keep the FP/VMX/VSX state loaded जबतक ever the transaction
 * जारीs.  The reason is that अगर we didn't, and subsequently
 * got a FP/VMX/VSX unavailable पूर्णांकerrupt inside a transaction,
 * we करोn't know whether it's the same transaction, and thus we
 * करोn't know which of the checkpoपूर्णांकed state and the transactional
 * state to use.
 */
व्योम restore_पंचांग_state(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ msr_dअगरf;

	/*
	 * This is the only moment we should clear TIF_RESTORE_TM as
	 * it is here that ckpt_regs.msr and pt_regs.msr become the same
	 * again, anything अन्यथा could lead to an incorrect ckpt_msr being
	 * saved and thereक्रमe incorrect संकेत contexts.
	 */
	clear_thपढ़ो_flag(TIF_RESTORE_TM);
	अगर (!MSR_TM_ACTIVE(regs->msr))
		वापस;

	msr_dअगरf = current->thपढ़ो.ckpt_regs.msr & ~regs->msr;
	msr_dअगरf &= MSR_FP | MSR_VEC | MSR_VSX;

	/* Ensure that restore_math() will restore */
	अगर (msr_dअगरf & MSR_FP)
		current->thपढ़ो.load_fp = 1;
#अगर_घोषित CONFIG_ALTIVEC
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC) && msr_dअगरf & MSR_VEC)
		current->thपढ़ो.load_vec = 1;
#पूर्ण_अगर
	restore_math(regs);

	regs->msr |= msr_dअगरf;
पूर्ण

#अन्यथा /* !CONFIG_PPC_TRANSACTIONAL_MEM */
#घोषणा पंचांग_recheckpoपूर्णांक_new_task(new)
#घोषणा __चयन_to_पंचांग(prev, new)
व्योम पंचांग_reclaim_current(uपूर्णांक8_t cause) अणुपूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

अटल अंतरभूत व्योम save_sprs(काष्ठा thपढ़ो_काष्ठा *t)
अणु
#अगर_घोषित CONFIG_ALTIVEC
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC))
		t->vrsave = mfspr(SPRN_VRSAVE);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (cpu_has_feature(CPU_FTR_DSCR))
		t->dscr = mfspr(SPRN_DSCR);

	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		t->bescr = mfspr(SPRN_BESCR);
		t->ebbhr = mfspr(SPRN_EBBHR);
		t->ebbrr = mfspr(SPRN_EBBRR);

		t->fscr = mfspr(SPRN_FSCR);

		/*
		 * Note that the TAR is not available क्रम use in the kernel.
		 * (To provide this, the TAR should be backed up/restored on
		 * exception entry/निकास instead, and be in pt_regs.  FIXME,
		 * this should be in pt_regs anyway (क्रम debug).)
		 */
		t->tar = mfspr(SPRN_TAR);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम restore_sprs(काष्ठा thपढ़ो_काष्ठा *old_thपढ़ो,
				काष्ठा thपढ़ो_काष्ठा *new_thपढ़ो)
अणु
#अगर_घोषित CONFIG_ALTIVEC
	अगर (cpu_has_feature(CPU_FTR_ALTIVEC) &&
	    old_thपढ़ो->vrsave != new_thपढ़ो->vrsave)
		mtspr(SPRN_VRSAVE, new_thपढ़ो->vrsave);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (cpu_has_feature(CPU_FTR_DSCR)) अणु
		u64 dscr = get_paca()->dscr_शेष;
		अगर (new_thपढ़ो->dscr_inherit)
			dscr = new_thपढ़ो->dscr;

		अगर (old_thपढ़ो->dscr != dscr)
			mtspr(SPRN_DSCR, dscr);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_ARCH_207S)) अणु
		अगर (old_thपढ़ो->bescr != new_thपढ़ो->bescr)
			mtspr(SPRN_BESCR, new_thपढ़ो->bescr);
		अगर (old_thपढ़ो->ebbhr != new_thपढ़ो->ebbhr)
			mtspr(SPRN_EBBHR, new_thपढ़ो->ebbhr);
		अगर (old_thपढ़ो->ebbrr != new_thपढ़ो->ebbrr)
			mtspr(SPRN_EBBRR, new_thपढ़ो->ebbrr);

		अगर (old_thपढ़ो->fscr != new_thपढ़ो->fscr)
			mtspr(SPRN_FSCR, new_thपढ़ो->fscr);

		अगर (old_thपढ़ो->tar != new_thपढ़ो->tar)
			mtspr(SPRN_TAR, new_thपढ़ो->tar);
	पूर्ण

	अगर (cpu_has_feature(CPU_FTR_P9_TIDR) &&
	    old_thपढ़ो->tidr != new_thपढ़ो->tidr)
		mtspr(SPRN_TIDR, new_thपढ़ो->tidr);
#पूर्ण_अगर

पूर्ण

काष्ठा task_काष्ठा *__चयन_to(काष्ठा task_काष्ठा *prev,
	काष्ठा task_काष्ठा *new)
अणु
	काष्ठा thपढ़ो_काष्ठा *new_thपढ़ो, *old_thपढ़ो;
	काष्ठा task_काष्ठा *last;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा ppc64_tlb_batch *batch;
#पूर्ण_अगर

	new_thपढ़ो = &new->thपढ़ो;
	old_thपढ़ो = &current->thपढ़ो;

	WARN_ON(!irqs_disabled());

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	batch = this_cpu_ptr(&ppc64_tlb_batch);
	अगर (batch->active) अणु
		current_thपढ़ो_info()->local_flags |= _TLF_LAZY_MMU;
		अगर (batch->index)
			__flush_tlb_pending(batch);
		batch->active = 0;
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
	चयन_booke_debug_regs(&new->thपढ़ो.debug);
#अन्यथा
/*
 * For PPC_BOOK3S_64, we use the hw-अवरोधpoपूर्णांक पूर्णांकerfaces that would
 * schedule DABR
 */
#अगर_अघोषित CONFIG_HAVE_HW_BREAKPOINT
	चयन_hw_अवरोधpoपूर्णांक(new);
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
#पूर्ण_अगर

	/*
	 * We need to save SPRs beक्रमe treclaim/trecheckpoपूर्णांक as these will
	 * change a number of them.
	 */
	save_sprs(&prev->thपढ़ो);

	/* Save FPU, Altivec, VSX and SPE state */
	giveup_all(prev);

	__चयन_to_पंचांग(prev, new);

	अगर (!radix_enabled()) अणु
		/*
		 * We can't take a PMU exception inside _चयन() since there
		 * is a winकरोw where the kernel stack SLB and the kernel stack
		 * are out of sync. Hard disable here.
		 */
		hard_irq_disable();
	पूर्ण

	/*
	 * Call restore_sprs() beक्रमe calling _चयन(). If we move it after
	 * _चयन() then we miss out on calling it क्रम new tasks. The reason
	 * क्रम this is we manually create a stack frame क्रम new tasks that
	 * directly वापसs through ret_from_विभाजन() or
	 * ret_from_kernel_thपढ़ो(). See copy_thपढ़ो() क्रम details.
	 */
	restore_sprs(old_thपढ़ो, new_thपढ़ो);

#अगर_घोषित CONFIG_PPC32
	kuap_निश्चित_locked();
#पूर्ण_अगर
	last = _चयन(old_thपढ़ो, new_thपढ़ो);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (current_thपढ़ो_info()->local_flags & _TLF_LAZY_MMU) अणु
		current_thपढ़ो_info()->local_flags &= ~_TLF_LAZY_MMU;
		batch = this_cpu_ptr(&ppc64_tlb_batch);
		batch->active = 1;
	पूर्ण

	अगर (current->thपढ़ो.regs) अणु
		restore_math(current->thपढ़ो.regs);

		/*
		 * On POWER9 the copy-paste buffer can only paste पूर्णांकo
		 * क्रमeign real addresses, so unprivileged processes can not
		 * see the data or use it in any way unless they have
		 * क्रमeign real mappings. If the new process has the क्रमeign
		 * real address mappings, we must issue a cp_पात to clear
		 * any state and prevent snooping, corruption or a covert
		 * channel. ISA v3.1 supports paste पूर्णांकo local memory.
		 */
		अगर (current->mm &&
			(cpu_has_feature(CPU_FTR_ARCH_31) ||
			atomic_पढ़ो(&current->mm->context.vas_winकरोws)))
			यंत्र अस्थिर(PPC_CP_ABORT);
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

	वापस last;
पूर्ण

#घोषणा NR_INSN_TO_PRINT	16

अटल व्योम show_inकाष्ठाions(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ nip = regs->nip;
	अचिन्हित दीर्घ pc = regs->nip - (NR_INSN_TO_PRINT * 3 / 4 * माप(पूर्णांक));

	prपूर्णांकk("Instruction dump:");

	/*
	 * If we were executing with the MMU off क्रम inकाष्ठाions, adjust pc
	 * rather than prपूर्णांकing XXXXXXXX.
	 */
	अगर (!IS_ENABLED(CONFIG_BOOKE) && !(regs->msr & MSR_IR)) अणु
		pc = (अचिन्हित दीर्घ)phys_to_virt(pc);
		nip = (अचिन्हित दीर्घ)phys_to_virt(regs->nip);
	पूर्ण

	क्रम (i = 0; i < NR_INSN_TO_PRINT; i++) अणु
		पूर्णांक instr;

		अगर (!(i % 8))
			pr_cont("\n");

		अगर (!__kernel_text_address(pc) ||
		    get_kernel_nofault(instr, (स्थिर व्योम *)pc)) अणु
			pr_cont("XXXXXXXX ");
		पूर्ण अन्यथा अणु
			अगर (nip == pc)
				pr_cont("<%08x> ", instr);
			अन्यथा
				pr_cont("%08x ", instr);
		पूर्ण

		pc += माप(पूर्णांक);
	पूर्ण

	pr_cont("\n");
पूर्ण

व्योम show_user_inकाष्ठाions(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ pc;
	पूर्णांक n = NR_INSN_TO_PRINT;
	काष्ठा seq_buf s;
	अक्षर buf[96]; /* enough क्रम 8 बार 9 + 2 अक्षरs */

	pc = regs->nip - (NR_INSN_TO_PRINT * 3 / 4 * माप(पूर्णांक));

	seq_buf_init(&s, buf, माप(buf));

	जबतक (n) अणु
		पूर्णांक i;

		seq_buf_clear(&s);

		क्रम (i = 0; i < 8 && n; i++, n--, pc += माप(पूर्णांक)) अणु
			पूर्णांक instr;

			अगर (copy_from_user_nofault(&instr, (व्योम __user *)pc,
					माप(instr))) अणु
				seq_buf_म_लिखो(&s, "XXXXXXXX ");
				जारी;
			पूर्ण
			seq_buf_म_लिखो(&s, regs->nip == pc ? "<%08x> " : "%08x ", instr);
		पूर्ण

		अगर (!seq_buf_has_overflowed(&s))
			pr_info("%s[%d]: code: %s\n", current->comm,
				current->pid, s.buffer);
	पूर्ण
पूर्ण

काष्ठा regbit अणु
	अचिन्हित दीर्घ bit;
	स्थिर अक्षर *name;
पूर्ण;

अटल काष्ठा regbit msr_bits[] = अणु
#अगर defined(CONFIG_PPC64) && !defined(CONFIG_BOOKE)
	अणुMSR_SF,	"SF"पूर्ण,
	अणुMSR_HV,	"HV"पूर्ण,
#पूर्ण_अगर
	अणुMSR_VEC,	"VEC"पूर्ण,
	अणुMSR_VSX,	"VSX"पूर्ण,
#अगर_घोषित CONFIG_BOOKE
	अणुMSR_CE,	"CE"पूर्ण,
#पूर्ण_अगर
	अणुMSR_EE,	"EE"पूर्ण,
	अणुMSR_PR,	"PR"पूर्ण,
	अणुMSR_FP,	"FP"पूर्ण,
	अणुMSR_ME,	"ME"पूर्ण,
#अगर_घोषित CONFIG_BOOKE
	अणुMSR_DE,	"DE"पूर्ण,
#अन्यथा
	अणुMSR_SE,	"SE"पूर्ण,
	अणुMSR_BE,	"BE"पूर्ण,
#पूर्ण_अगर
	अणुMSR_IR,	"IR"पूर्ण,
	अणुMSR_DR,	"DR"पूर्ण,
	अणुMSR_PMM,	"PMM"पूर्ण,
#अगर_अघोषित CONFIG_BOOKE
	अणुMSR_RI,	"RI"पूर्ण,
	अणुMSR_LE,	"LE"पूर्ण,
#पूर्ण_अगर
	अणु0,		शून्यपूर्ण
पूर्ण;

अटल व्योम prपूर्णांक_bits(अचिन्हित दीर्घ val, काष्ठा regbit *bits, स्थिर अक्षर *sep)
अणु
	स्थिर अक्षर *s = "";

	क्रम (; bits->bit; ++bits)
		अगर (val & bits->bit) अणु
			pr_cont("%s%s", s, bits->name);
			s = sep;
		पूर्ण
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
अटल काष्ठा regbit msr_पंचांग_bits[] = अणु
	अणुMSR_TS_T,	"T"पूर्ण,
	अणुMSR_TS_S,	"S"पूर्ण,
	अणुMSR_TM,	"E"पूर्ण,
	अणु0,		शून्यपूर्ण
पूर्ण;

अटल व्योम prपूर्णांक_पंचांग_bits(अचिन्हित दीर्घ val)
अणु
/*
 * This only prपूर्णांकs something अगर at least one of the TM bit is set.
 * Inside the TM[], the output means:
 *   E: Enabled		(bit 32)
 *   S: Suspended	(bit 33)
 *   T: Transactional	(bit 34)
 */
	अगर (val & (MSR_TM | MSR_TS_S | MSR_TS_T)) अणु
		pr_cont(",TM[");
		prपूर्णांक_bits(val, msr_पंचांग_bits, "");
		pr_cont("]");
	पूर्ण
पूर्ण
#अन्यथा
अटल व्योम prपूर्णांक_पंचांग_bits(अचिन्हित दीर्घ val) अणुपूर्ण
#पूर्ण_अगर

अटल व्योम prपूर्णांक_msr_bits(अचिन्हित दीर्घ val)
अणु
	pr_cont("<");
	prपूर्णांक_bits(val, msr_bits, ",");
	prपूर्णांक_पंचांग_bits(val);
	pr_cont(">");
पूर्ण

#अगर_घोषित CONFIG_PPC64
#घोषणा REG		"%016lx"
#घोषणा REGS_PER_LINE	4
#अन्यथा
#घोषणा REG		"%08lx"
#घोषणा REGS_PER_LINE	8
#पूर्ण_अगर

अटल व्योम __show_regs(काष्ठा pt_regs *regs)
अणु
	पूर्णांक i, trap;

	prपूर्णांकk("NIP:  "REG" LR: "REG" CTR: "REG"\n",
	       regs->nip, regs->link, regs->ctr);
	prपूर्णांकk("REGS: %px TRAP: %04lx   %s  (%s)\n",
	       regs, regs->trap, prपूर्णांक_taपूर्णांकed(), init_utsname()->release);
	prपूर्णांकk("MSR:  "REG" ", regs->msr);
	prपूर्णांक_msr_bits(regs->msr);
	pr_cont("  CR: %08lx  XER: %08lx\n", regs->ccr, regs->xer);
	trap = TRAP(regs);
	अगर (!trap_is_syscall(regs) && cpu_has_feature(CPU_FTR_CFAR))
		pr_cont("CFAR: "REG" ", regs->orig_gpr3);
	अगर (trap == INTERRUPT_MACHINE_CHECK ||
	    trap == INTERRUPT_DATA_STORAGE ||
	    trap == INTERRUPT_ALIGNMENT) अणु
		अगर (IS_ENABLED(CONFIG_4xx) || IS_ENABLED(CONFIG_BOOKE))
			pr_cont("DEAR: "REG" ESR: "REG" ", regs->dar, regs->dsisr);
		अन्यथा
			pr_cont("DAR: "REG" DSISR: %08lx ", regs->dar, regs->dsisr);
	पूर्ण

#अगर_घोषित CONFIG_PPC64
	pr_cont("IRQMASK: %lx ", regs->softe);
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	अगर (MSR_TM_ACTIVE(regs->msr))
		pr_cont("\nPACATMSCRATCH: %016llx ", get_paca()->पंचांग_scratch);
#पूर्ण_अगर

	क्रम (i = 0;  i < 32;  i++) अणु
		अगर ((i % REGS_PER_LINE) == 0)
			pr_cont("\nGPR%02d: ", i);
		pr_cont(REG " ", regs->gpr[i]);
	पूर्ण
	pr_cont("\n");
	/*
	 * Lookup NIP late so we have the best change of getting the
	 * above info out without failing
	 */
	अगर (IS_ENABLED(CONFIG_KALLSYMS)) अणु
		prपूर्णांकk("NIP ["REG"] %pS\n", regs->nip, (व्योम *)regs->nip);
		prपूर्णांकk("LR ["REG"] %pS\n", regs->link, (व्योम *)regs->link);
	पूर्ण
पूर्ण

व्योम show_regs(काष्ठा pt_regs *regs)
अणु
	show_regs_prपूर्णांक_info(KERN_DEFAULT);
	__show_regs(regs);
	show_stack(current, (अचिन्हित दीर्घ *) regs->gpr[1], KERN_DEFAULT);
	अगर (!user_mode(regs))
		show_inकाष्ठाions(regs);
पूर्ण

व्योम flush_thपढ़ो(व्योम)
अणु
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	flush_ptrace_hw_अवरोधpoपूर्णांक(current);
#अन्यथा /* CONFIG_HAVE_HW_BREAKPOINT */
	set_debug_reg_शेषs(&current->thपढ़ो);
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
पूर्ण

व्योम arch_setup_new_exec(व्योम)
अणु

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (!radix_enabled())
		hash__setup_new_exec();
#पूर्ण_अगर
	/*
	 * If we exec out of a kernel thपढ़ो then thपढ़ो.regs will not be
	 * set.  Do it now.
	 */
	अगर (!current->thपढ़ो.regs) अणु
		काष्ठा pt_regs *regs = task_stack_page(current) + THREAD_SIZE;
		current->thपढ़ो.regs = regs - 1;
	पूर्ण

#अगर_घोषित CONFIG_PPC_MEM_KEYS
	current->thपढ़ो.regs->amr  = शेष_amr;
	current->thपढ़ो.regs->iamr  = शेष_iamr;
#पूर्ण_अगर
पूर्ण

#अगर_घोषित CONFIG_PPC64
/**
 * Assign a TIDR (thपढ़ो ID) क्रम task @t and set it in the thपढ़ो
 * काष्ठाure. For now, we only support setting TIDR क्रम 'current' task.
 *
 * Since the TID value is a truncated क्रमm of it PID, it is possible
 * (but unlikely) क्रम 2 thपढ़ोs to have the same TID. In the unlikely event
 * that 2 thपढ़ोs share the same TID and are रुकोing, one of the following
 * हालs will happen:
 *
 * 1. The correct thपढ़ो is running, the wrong thपढ़ो is not
 * In this situation, the correct thपढ़ो is woken and proceeds to pass it's
 * condition check.
 *
 * 2. Neither thपढ़ोs are running
 * In this situation, neither thपढ़ो will be woken. When scheduled, the रुकोing
 * thपढ़ोs will execute either a रुको, which will वापस immediately, followed
 * by a condition check, which will pass क्रम the correct thपढ़ो and fail
 * क्रम the wrong thपढ़ो, or they will execute the condition check immediately.
 *
 * 3. The wrong thपढ़ो is running, the correct thपढ़ो is not
 * The wrong thपढ़ो will be woken, but will fail it's condition check and
 * re-execute रुको. The correct thपढ़ो, when scheduled, will execute either
 * it's condition check (which will pass), or रुको, which वापसs immediately
 * when called the first समय after the thपढ़ो is scheduled, followed by it's
 * condition check (which will pass).
 *
 * 4. Both thपढ़ोs are running
 * Both thपढ़ोs will be woken. The wrong thपढ़ो will fail it's condition check
 * and execute another रुको, जबतक the correct thपढ़ो will pass it's condition
 * check.
 *
 * @t: the task to set the thपढ़ो ID क्रम
 */
पूर्णांक set_thपढ़ो_tidr(काष्ठा task_काष्ठा *t)
अणु
	अगर (!cpu_has_feature(CPU_FTR_P9_TIDR))
		वापस -EINVAL;

	अगर (t != current)
		वापस -EINVAL;

	अगर (t->thपढ़ो.tidr)
		वापस 0;

	t->thपढ़ो.tidr = (u16)task_pid_nr(t);
	mtspr(SPRN_TIDR, t->thपढ़ो.tidr);

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(set_thपढ़ो_tidr);

#पूर्ण_अगर /* CONFIG_PPC64 */

व्योम
release_thपढ़ो(काष्ठा task_काष्ठा *t)
अणु
पूर्ण

/*
 * this माला_लो called so that we can store coprocessor state पूर्णांकo memory and
 * copy the current task पूर्णांकo the new thपढ़ो.
 */
पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src)
अणु
	flush_all_to_thपढ़ो(src);
	/*
	 * Flush TM state out so we can copy it.  __चयन_to_पंचांग() करोes this
	 * flush but it हटाओs the checkpoपूर्णांकed state from the current CPU and
	 * transitions the CPU out of TM mode.  Hence we need to call
	 * पंचांग_recheckpoपूर्णांक_new_task() (on the same task) to restore the
	 * checkpoपूर्णांकed state back and the TM mode.
	 *
	 * Can't pass dst because it isn't ready. Doesn't matter, passing
	 * dst is only important क्रम __चयन_to()
	 */
	__चयन_to_पंचांग(src, src);

	*dst = *src;

	clear_task_ebb(dst);

	वापस 0;
पूर्ण

अटल व्योम setup_ksp_vsid(काष्ठा task_काष्ठा *p, अचिन्हित दीर्घ sp)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अचिन्हित दीर्घ sp_vsid;
	अचिन्हित दीर्घ llp = mmu_psize_defs[mmu_linear_psize].sllp;

	अगर (radix_enabled())
		वापस;

	अगर (mmu_has_feature(MMU_FTR_1T_SEGMENT))
		sp_vsid = get_kernel_vsid(sp, MMU_SEGSIZE_1T)
			<< SLB_VSID_SHIFT_1T;
	अन्यथा
		sp_vsid = get_kernel_vsid(sp, MMU_SEGSIZE_256M)
			<< SLB_VSID_SHIFT;
	sp_vsid |= SLB_VSID_KERNEL | llp;
	p->thपढ़ो.ksp_vsid = sp_vsid;
#पूर्ण_अगर
पूर्ण

/*
 * Copy a thपढ़ो..
 */

/*
 * Copy architecture-specअगरic thपढ़ो state
 */
पूर्णांक copy_thपढ़ो(अचिन्हित दीर्घ clone_flags, अचिन्हित दीर्घ usp,
		अचिन्हित दीर्घ kthपढ़ो_arg, काष्ठा task_काष्ठा *p,
		अचिन्हित दीर्घ tls)
अणु
	काष्ठा pt_regs *childregs, *kregs;
	बाह्य व्योम ret_from_विभाजन(व्योम);
	बाह्य व्योम ret_from_विभाजन_scv(व्योम);
	बाह्य व्योम ret_from_kernel_thपढ़ो(व्योम);
	व्योम (*f)(व्योम);
	अचिन्हित दीर्घ sp = (अचिन्हित दीर्घ)task_stack_page(p) + THREAD_SIZE;
	काष्ठा thपढ़ो_info *ti = task_thपढ़ो_info(p);
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	पूर्णांक i;
#पूर्ण_अगर

	klp_init_thपढ़ो_info(p);

	/* Copy रेजिस्टरs */
	sp -= माप(काष्ठा pt_regs);
	childregs = (काष्ठा pt_regs *) sp;
	अगर (unlikely(p->flags & (PF_KTHREAD | PF_IO_WORKER))) अणु
		/* kernel thपढ़ो */
		स_रखो(childregs, 0, माप(काष्ठा pt_regs));
		childregs->gpr[1] = sp + माप(काष्ठा pt_regs);
		/* function */
		अगर (usp)
			childregs->gpr[14] = ppc_function_entry((व्योम *)usp);
#अगर_घोषित CONFIG_PPC64
		clear_tsk_thपढ़ो_flag(p, TIF_32BIT);
		childregs->softe = IRQS_ENABLED;
#पूर्ण_अगर
		childregs->gpr[15] = kthपढ़ो_arg;
		p->thपढ़ो.regs = शून्य;	/* no user रेजिस्टर state */
		ti->flags |= _TIF_RESTOREALL;
		f = ret_from_kernel_thपढ़ो;
	पूर्ण अन्यथा अणु
		/* user thपढ़ो */
		काष्ठा pt_regs *regs = current_pt_regs();
		*childregs = *regs;
		अगर (usp)
			childregs->gpr[1] = usp;
		p->thपढ़ो.regs = childregs;
		/* 64s sets this in ret_from_विभाजन */
		अगर (!IS_ENABLED(CONFIG_PPC_BOOK3S_64))
			childregs->gpr[3] = 0;  /* Result from विभाजन() */
		अगर (clone_flags & CLONE_SETTLS) अणु
			अगर (!is_32bit_task())
				childregs->gpr[13] = tls;
			अन्यथा
				childregs->gpr[2] = tls;
		पूर्ण

		अगर (trap_is_scv(regs))
			f = ret_from_विभाजन_scv;
		अन्यथा
			f = ret_from_विभाजन;
	पूर्ण
	childregs->msr &= ~(MSR_FP|MSR_VEC|MSR_VSX);
	sp -= STACK_FRAME_OVERHEAD;

	/*
	 * The way this works is that at some poपूर्णांक in the future
	 * some task will call _चयन to चयन to the new task.
	 * That will pop off the stack frame created below and start
	 * the new task running at ret_from_विभाजन.  The new task will
	 * करो some house keeping and then वापस from the विभाजन or clone
	 * प्रणाली call, using the stack frame created above.
	 */
	((अचिन्हित दीर्घ *)sp)[0] = 0;
	sp -= माप(काष्ठा pt_regs);
	kregs = (काष्ठा pt_regs *) sp;
	sp -= STACK_FRAME_OVERHEAD;
	p->thपढ़ो.ksp = sp;
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	क्रम (i = 0; i < nr_wp_slots(); i++)
		p->thपढ़ो.ptrace_bps[i] = शून्य;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_FPU_REGS
	p->thपढ़ो.fp_save_area = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	p->thपढ़ो.vr_save_area = शून्य;
#पूर्ण_अगर

	setup_ksp_vsid(p, sp);

#अगर_घोषित CONFIG_PPC64 
	अगर (cpu_has_feature(CPU_FTR_DSCR)) अणु
		p->thपढ़ो.dscr_inherit = current->thपढ़ो.dscr_inherit;
		p->thपढ़ो.dscr = mfspr(SPRN_DSCR);
	पूर्ण
	अगर (cpu_has_feature(CPU_FTR_HAS_PPR))
		childregs->ppr = DEFAULT_PPR;

	p->thपढ़ो.tidr = 0;
#पूर्ण_अगर
	/*
	 * Run with the current AMR value of the kernel
	 */
#अगर_घोषित CONFIG_PPC_PKEY
	अगर (mmu_has_feature(MMU_FTR_BOOK3S_KUAP))
		kregs->amr = AMR_KUAP_BLOCKED;

	अगर (mmu_has_feature(MMU_FTR_BOOK3S_KUEP))
		kregs->iamr = AMR_KUEP_BLOCKED;
#पूर्ण_अगर
	kregs->nip = ppc_function_entry(f);
	वापस 0;
पूर्ण

व्योम preload_new_slb_context(अचिन्हित दीर्घ start, अचिन्हित दीर्घ sp);

/*
 * Set up a thपढ़ो क्रम executing a new program
 */
व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ start, अचिन्हित दीर्घ sp)
अणु
#अगर_घोषित CONFIG_PPC64
	अचिन्हित दीर्घ load_addr = regs->gpr[2];	/* saved by ELF_PLAT_INIT */

	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64) && !radix_enabled())
		preload_new_slb_context(start, sp);
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	/*
	 * Clear any transactional state, we're exec()ing. The cause is
	 * not important as there will never be a recheckpoपूर्णांक so it's not
	 * user visible.
	 */
	अगर (MSR_TM_SUSPENDED(mfmsr()))
		पंचांग_reclaim_current(0);
#पूर्ण_अगर

	स_रखो(regs->gpr, 0, माप(regs->gpr));
	regs->ctr = 0;
	regs->link = 0;
	regs->xer = 0;
	regs->ccr = 0;
	regs->gpr[1] = sp;

#अगर_घोषित CONFIG_PPC32
	regs->mq = 0;
	regs->nip = start;
	regs->msr = MSR_USER;
#अन्यथा
	अगर (!is_32bit_task()) अणु
		अचिन्हित दीर्घ entry;

		अगर (is_elf2_task()) अणु
			/* Look ma, no function descriptors! */
			entry = start;

			/*
			 * Ulrich says:
			 *   The latest iteration of the ABI requires that when
			 *   calling a function (at its global entry poपूर्णांक),
			 *   the caller must ensure r12 holds the entry poपूर्णांक
			 *   address (so that the function can quickly
			 *   establish addressability).
			 */
			regs->gpr[12] = start;
			/* Make sure that's restored on entry to userspace. */
			set_thपढ़ो_flag(TIF_RESTOREALL);
		पूर्ण अन्यथा अणु
			अचिन्हित दीर्घ toc;

			/* start is a relocated poपूर्णांकer to the function
			 * descriptor क्रम the elf _start routine.  The first
			 * entry in the function descriptor is the entry
			 * address of _start and the second entry is the TOC
			 * value we need to use.
			 */
			__get_user(entry, (अचिन्हित दीर्घ __user *)start);
			__get_user(toc, (अचिन्हित दीर्घ __user *)start+1);

			/* Check whether the e_entry function descriptor entries
			 * need to be relocated beक्रमe we can use them.
			 */
			अगर (load_addr != 0) अणु
				entry += load_addr;
				toc   += load_addr;
			पूर्ण
			regs->gpr[2] = toc;
		पूर्ण
		regs->nip = entry;
		regs->msr = MSR_USER64;
	पूर्ण अन्यथा अणु
		regs->nip = start;
		regs->gpr[2] = 0;
		regs->msr = MSR_USER32;
	पूर्ण
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	current->thपढ़ो.used_vsr = 0;
#पूर्ण_अगर
	current->thपढ़ो.load_slb = 0;
	current->thपढ़ो.load_fp = 0;
#अगर_घोषित CONFIG_PPC_FPU_REGS
	स_रखो(&current->thपढ़ो.fp_state, 0, माप(current->thपढ़ो.fp_state));
	current->thपढ़ो.fp_save_area = शून्य;
#पूर्ण_अगर
#अगर_घोषित CONFIG_ALTIVEC
	स_रखो(&current->thपढ़ो.vr_state, 0, माप(current->thपढ़ो.vr_state));
	current->thपढ़ो.vr_state.vscr.u[3] = 0x00010000; /* Java mode disabled */
	current->thपढ़ो.vr_save_area = शून्य;
	current->thपढ़ो.vrsave = 0;
	current->thपढ़ो.used_vr = 0;
	current->thपढ़ो.load_vec = 0;
#पूर्ण_अगर /* CONFIG_ALTIVEC */
#अगर_घोषित CONFIG_SPE
	स_रखो(current->thपढ़ो.evr, 0, माप(current->thपढ़ो.evr));
	current->thपढ़ो.acc = 0;
	current->thपढ़ो.spefscr = 0;
	current->thपढ़ो.used_spe = 0;
#पूर्ण_अगर /* CONFIG_SPE */
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	current->thपढ़ो.पंचांग_tfhar = 0;
	current->thपढ़ो.पंचांग_texasr = 0;
	current->thपढ़ो.पंचांग_tfiar = 0;
	current->thपढ़ो.load_पंचांग = 0;
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

पूर्ण
EXPORT_SYMBOL(start_thपढ़ो);

#घोषणा PR_FP_ALL_EXCEPT (PR_FP_EXC_DIV | PR_FP_EXC_OVF | PR_FP_EXC_UND \
		| PR_FP_EXC_RES | PR_FP_EXC_INV)

पूर्णांक set_fpexc_mode(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक val)
अणु
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;

	/* This is a bit hairy.  If we are an SPE enabled  processor
	 * (have embedded fp) we store the IEEE exception enable flags in
	 * fpexc_mode.  fpexc_mode is also used क्रम setting FP exception
	 * mode (asyn, precise, disabled) क्रम 'Classic' FP. */
	अगर (val & PR_FP_EXC_SW_ENABLE) अणु
		अगर (cpu_has_feature(CPU_FTR_SPE)) अणु
			/*
			 * When the sticky exception bits are set
			 * directly by userspace, it must call prctl
			 * with PR_GET_FPEXC (with PR_FP_EXC_SW_ENABLE
			 * in the existing prctl settings) or
			 * PR_SET_FPEXC (with PR_FP_EXC_SW_ENABLE in
			 * the bits being set).  <fenv.h> functions
			 * saving and restoring the whole
			 * भग्नing-poपूर्णांक environment need to करो so
			 * anyway to restore the prctl settings from
			 * the saved environment.
			 */
#अगर_घोषित CONFIG_SPE
			tsk->thपढ़ो.spefscr_last = mfspr(SPRN_SPEFSCR);
			tsk->thपढ़ो.fpexc_mode = val &
				(PR_FP_EXC_SW_ENABLE | PR_FP_ALL_EXCEPT);
#पूर्ण_अगर
			वापस 0;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* on a CONFIG_SPE this करोes not hurt us.  The bits that
	 * __pack_fe01 use करो not overlap with bits used क्रम
	 * PR_FP_EXC_SW_ENABLE.  Additionally, the MSR[FE0,FE1] bits
	 * on CONFIG_SPE implementations are reserved so writing to
	 * them करोes not change anything */
	अगर (val > PR_FP_EXC_PRECISE)
		वापस -EINVAL;
	tsk->thपढ़ो.fpexc_mode = __pack_fe01(val);
	अगर (regs != शून्य && (regs->msr & MSR_FP) != 0)
		regs->msr = (regs->msr & ~(MSR_FE0|MSR_FE1))
			| tsk->thपढ़ो.fpexc_mode;
	वापस 0;
पूर्ण

पूर्णांक get_fpexc_mode(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ adr)
अणु
	अचिन्हित पूर्णांक val = 0;

	अगर (tsk->thपढ़ो.fpexc_mode & PR_FP_EXC_SW_ENABLE) अणु
		अगर (cpu_has_feature(CPU_FTR_SPE)) अणु
			/*
			 * When the sticky exception bits are set
			 * directly by userspace, it must call prctl
			 * with PR_GET_FPEXC (with PR_FP_EXC_SW_ENABLE
			 * in the existing prctl settings) or
			 * PR_SET_FPEXC (with PR_FP_EXC_SW_ENABLE in
			 * the bits being set).  <fenv.h> functions
			 * saving and restoring the whole
			 * भग्नing-poपूर्णांक environment need to करो so
			 * anyway to restore the prctl settings from
			 * the saved environment.
			 */
#अगर_घोषित CONFIG_SPE
			tsk->thपढ़ो.spefscr_last = mfspr(SPRN_SPEFSCR);
			val = tsk->thपढ़ो.fpexc_mode;
#पूर्ण_अगर
		पूर्ण अन्यथा
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		val = __unpack_fe01(tsk->thपढ़ो.fpexc_mode);
	पूर्ण
	वापस put_user(val, (अचिन्हित पूर्णांक __user *) adr);
पूर्ण

पूर्णांक set_endian(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक val)
अणु
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;

	अगर ((val == PR_ENDIAN_LITTLE && !cpu_has_feature(CPU_FTR_REAL_LE)) ||
	    (val == PR_ENDIAN_PPC_LITTLE && !cpu_has_feature(CPU_FTR_PPC_LE)))
		वापस -EINVAL;

	अगर (regs == शून्य)
		वापस -EINVAL;

	अगर (val == PR_ENDIAN_BIG)
		regs->msr &= ~MSR_LE;
	अन्यथा अगर (val == PR_ENDIAN_LITTLE || val == PR_ENDIAN_PPC_LITTLE)
		regs->msr |= MSR_LE;
	अन्यथा
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक get_endian(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ adr)
अणु
	काष्ठा pt_regs *regs = tsk->thपढ़ो.regs;
	अचिन्हित पूर्णांक val;

	अगर (!cpu_has_feature(CPU_FTR_PPC_LE) &&
	    !cpu_has_feature(CPU_FTR_REAL_LE))
		वापस -EINVAL;

	अगर (regs == शून्य)
		वापस -EINVAL;

	अगर (regs->msr & MSR_LE) अणु
		अगर (cpu_has_feature(CPU_FTR_REAL_LE))
			val = PR_ENDIAN_LITTLE;
		अन्यथा
			val = PR_ENDIAN_PPC_LITTLE;
	पूर्ण अन्यथा
		val = PR_ENDIAN_BIG;

	वापस put_user(val, (अचिन्हित पूर्णांक __user *)adr);
पूर्ण

पूर्णांक set_unalign_ctl(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक val)
अणु
	tsk->thपढ़ो.align_ctl = val;
	वापस 0;
पूर्ण

पूर्णांक get_unalign_ctl(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ adr)
अणु
	वापस put_user(tsk->thपढ़ो.align_ctl, (अचिन्हित पूर्णांक __user *)adr);
पूर्ण

अटल अंतरभूत पूर्णांक valid_irq_stack(अचिन्हित दीर्घ sp, काष्ठा task_काष्ठा *p,
				  अचिन्हित दीर्घ nbytes)
अणु
	अचिन्हित दीर्घ stack_page;
	अचिन्हित दीर्घ cpu = task_cpu(p);

	stack_page = (अचिन्हित दीर्घ)hardirq_ctx[cpu];
	अगर (sp >= stack_page && sp <= stack_page + THREAD_SIZE - nbytes)
		वापस 1;

	stack_page = (अचिन्हित दीर्घ)softirq_ctx[cpu];
	अगर (sp >= stack_page && sp <= stack_page + THREAD_SIZE - nbytes)
		वापस 1;

	वापस 0;
पूर्ण

अटल अंतरभूत पूर्णांक valid_emergency_stack(अचिन्हित दीर्घ sp, काष्ठा task_काष्ठा *p,
					अचिन्हित दीर्घ nbytes)
अणु
#अगर_घोषित CONFIG_PPC64
	अचिन्हित दीर्घ stack_page;
	अचिन्हित दीर्घ cpu = task_cpu(p);

	अगर (!paca_ptrs)
		वापस 0;

	stack_page = (अचिन्हित दीर्घ)paca_ptrs[cpu]->emergency_sp - THREAD_SIZE;
	अगर (sp >= stack_page && sp <= stack_page + THREAD_SIZE - nbytes)
		वापस 1;

# अगरdef CONFIG_PPC_BOOK3S_64
	stack_page = (अचिन्हित दीर्घ)paca_ptrs[cpu]->nmi_emergency_sp - THREAD_SIZE;
	अगर (sp >= stack_page && sp <= stack_page + THREAD_SIZE - nbytes)
		वापस 1;

	stack_page = (अचिन्हित दीर्घ)paca_ptrs[cpu]->mc_emergency_sp - THREAD_SIZE;
	अगर (sp >= stack_page && sp <= stack_page + THREAD_SIZE - nbytes)
		वापस 1;
# endअगर
#पूर्ण_अगर

	वापस 0;
पूर्ण


पूर्णांक validate_sp(अचिन्हित दीर्घ sp, काष्ठा task_काष्ठा *p,
		       अचिन्हित दीर्घ nbytes)
अणु
	अचिन्हित दीर्घ stack_page = (अचिन्हित दीर्घ)task_stack_page(p);

	अगर (sp < THREAD_SIZE)
		वापस 0;

	अगर (sp >= stack_page && sp <= stack_page + THREAD_SIZE - nbytes)
		वापस 1;

	अगर (valid_irq_stack(sp, p, nbytes))
		वापस 1;

	वापस valid_emergency_stack(sp, p, nbytes);
पूर्ण

EXPORT_SYMBOL(validate_sp);

अटल अचिन्हित दीर्घ __get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ ip, sp;
	पूर्णांक count = 0;

	अगर (!p || p == current || p->state == TASK_RUNNING)
		वापस 0;

	sp = p->thपढ़ो.ksp;
	अगर (!validate_sp(sp, p, STACK_FRAME_OVERHEAD))
		वापस 0;

	करो अणु
		sp = *(अचिन्हित दीर्घ *)sp;
		अगर (!validate_sp(sp, p, STACK_FRAME_OVERHEAD) ||
		    p->state == TASK_RUNNING)
			वापस 0;
		अगर (count > 0) अणु
			ip = ((अचिन्हित दीर्घ *)sp)[STACK_FRAME_LR_SAVE];
			अगर (!in_sched_functions(ip))
				वापस ip;
		पूर्ण
	पूर्ण जबतक (count++ < 16);
	वापस 0;
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p)
अणु
	अचिन्हित दीर्घ ret;

	अगर (!try_get_task_stack(p))
		वापस 0;

	ret = __get_wchan(p);

	put_task_stack(p);

	वापस ret;
पूर्ण

अटल पूर्णांक kstack_depth_to_prपूर्णांक = CONFIG_PRINT_STACK_DEPTH;

व्योम show_stack(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ *stack,
		स्थिर अक्षर *loglvl)
अणु
	अचिन्हित दीर्घ sp, ip, lr, newsp;
	पूर्णांक count = 0;
	पूर्णांक firstframe = 1;
	अचिन्हित दीर्घ ret_addr;
	पूर्णांक ftrace_idx = 0;

	अगर (tsk == शून्य)
		tsk = current;

	अगर (!try_get_task_stack(tsk))
		वापस;

	sp = (अचिन्हित दीर्घ) stack;
	अगर (sp == 0) अणु
		अगर (tsk == current)
			sp = current_stack_frame();
		अन्यथा
			sp = tsk->thपढ़ो.ksp;
	पूर्ण

	lr = 0;
	prपूर्णांकk("%sCall Trace:\n", loglvl);
	करो अणु
		अगर (!validate_sp(sp, tsk, STACK_FRAME_OVERHEAD))
			अवरोध;

		stack = (अचिन्हित दीर्घ *) sp;
		newsp = stack[0];
		ip = stack[STACK_FRAME_LR_SAVE];
		अगर (!firstframe || ip != lr) अणु
			prपूर्णांकk("%s["REG"] ["REG"] %pS",
				loglvl, sp, ip, (व्योम *)ip);
			ret_addr = ftrace_graph_ret_addr(current,
						&ftrace_idx, ip, stack);
			अगर (ret_addr != ip)
				pr_cont(" (%pS)", (व्योम *)ret_addr);
			अगर (firstframe)
				pr_cont(" (unreliable)");
			pr_cont("\n");
		पूर्ण
		firstframe = 0;

		/*
		 * See अगर this is an exception frame.
		 * We look क्रम the "regshere" marker in the current frame.
		 */
		अगर (validate_sp(sp, tsk, STACK_FRAME_WITH_PT_REGS)
		    && stack[STACK_FRAME_MARKER] == STACK_FRAME_REGS_MARKER) अणु
			काष्ठा pt_regs *regs = (काष्ठा pt_regs *)
				(sp + STACK_FRAME_OVERHEAD);

			lr = regs->link;
			prपूर्णांकk("%s--- interrupt: %lx at %pS\n",
			       loglvl, regs->trap, (व्योम *)regs->nip);
			__show_regs(regs);
			prपूर्णांकk("%s--- interrupt: %lx\n",
			       loglvl, regs->trap);

			firstframe = 1;
		पूर्ण

		sp = newsp;
	पूर्ण जबतक (count++ < kstack_depth_to_prपूर्णांक);

	put_task_stack(tsk);
पूर्ण

#अगर_घोषित CONFIG_PPC64
/* Called with hard IRQs off */
व्योम notrace __ppc64_runlatch_on(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();

	अगर (cpu_has_feature(CPU_FTR_ARCH_206)) अणु
		/*
		 * Least signअगरicant bit (RUN) is the only writable bit of
		 * the CTRL रेजिस्टर, so we can aव्योम mfspr. 2.06 is not the
		 * earliest ISA where this is the हाल, but it's convenient.
		 */
		mtspr(SPRN_CTRLT, CTRL_RUNLATCH);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ ctrl;

		/*
		 * Some architectures (e.g., Cell) have writable fields other
		 * than RUN, so करो the पढ़ो-modअगरy-ग_लिखो.
		 */
		ctrl = mfspr(SPRN_CTRLF);
		ctrl |= CTRL_RUNLATCH;
		mtspr(SPRN_CTRLT, ctrl);
	पूर्ण

	ti->local_flags |= _TLF_RUNLATCH;
पूर्ण

/* Called with hard IRQs off */
व्योम notrace __ppc64_runlatch_off(व्योम)
अणु
	काष्ठा thपढ़ो_info *ti = current_thपढ़ो_info();

	ti->local_flags &= ~_TLF_RUNLATCH;

	अगर (cpu_has_feature(CPU_FTR_ARCH_206)) अणु
		mtspr(SPRN_CTRLT, 0);
	पूर्ण अन्यथा अणु
		अचिन्हित दीर्घ ctrl;

		ctrl = mfspr(SPRN_CTRLF);
		ctrl &= ~CTRL_RUNLATCH;
		mtspr(SPRN_CTRLT, ctrl);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC64 */

अचिन्हित दीर्घ arch_align_stack(अचिन्हित दीर्घ sp)
अणु
	अगर (!(current->personality & ADDR_NO_RANDOMIZE) && अक्रमomize_va_space)
		sp -= get_अक्रमom_पूर्णांक() & ~PAGE_MASK;
	वापस sp & ~0xf;
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ brk_rnd(व्योम)
अणु
        अचिन्हित दीर्घ rnd = 0;

	/* 8MB क्रम 32bit, 1GB क्रम 64bit */
	अगर (is_32bit_task())
		rnd = (get_अक्रमom_दीर्घ() % (1UL<<(23-PAGE_SHIFT)));
	अन्यथा
		rnd = (get_अक्रमom_दीर्घ() % (1UL<<(30-PAGE_SHIFT)));

	वापस rnd << PAGE_SHIFT;
पूर्ण

अचिन्हित दीर्घ arch_अक्रमomize_brk(काष्ठा mm_काष्ठा *mm)
अणु
	अचिन्हित दीर्घ base = mm->brk;
	अचिन्हित दीर्घ ret;

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/*
	 * If we are using 1TB segments and we are allowed to अक्रमomise
	 * the heap, we can put it above 1TB so it is backed by a 1TB
	 * segment. Otherwise the heap will be in the bottom 1TB
	 * which always uses 256MB segments and this may result in a
	 * perक्रमmance penalty. We करोn't need to worry about radix. For
	 * radix, mmu_highuser_ssize reमुख्यs unchanged from 256MB.
	 */
	अगर (!is_32bit_task() && (mmu_highuser_ssize == MMU_SEGSIZE_1T))
		base = max_t(अचिन्हित दीर्घ, mm->brk, 1UL << SID_SHIFT_1T);
#पूर्ण_अगर

	ret = PAGE_ALIGN(base + brk_rnd());

	अगर (ret < mm->brk)
		वापस mm->brk;

	वापस ret;
पूर्ण

