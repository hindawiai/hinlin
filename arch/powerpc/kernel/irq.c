<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Derived from arch/i386/kernel/irq.c
 *    Copyright (C) 1992 Linus Torvalds
 *  Adapted from arch/i386 by Gary Thomas
 *    Copyright (C) 1995-1996 Gary Thomas (gdt@linuxppc.org)
 *  Updated and modअगरied by Cort Dougan <cort@fsmद_असल.com>
 *    Copyright (C) 1996-2001 Cort Dougan
 *  Adapted क्रम Power Macपूर्णांकosh by Paul Mackerras
 *    Copyright (C) 1996 Paul Mackerras (paulus@cs.anu.edu.au)
 *
 * This file contains the code used by various IRQ handling routines:
 * asking क्रम dअगरferent IRQ's should be करोne through these routines
 * instead of just grabbing them. Thus setups with dअगरferent IRQ numbers
 * shouldn't result in any weird surprises, and installing new handlers
 * should be easier.
 *
 * The MPC8xx has an पूर्णांकerrupt mask in the SIU.  If a bit is set, the
 * पूर्णांकerrupt is _enabled_.  As expected, IRQ0 is bit 0 in the 32-bit
 * mask रेजिस्टर (of which only 16 are defined), hence the weird shअगरting
 * and complement of the cached_irq_mask.  I want to be able to stuff
 * this right पूर्णांकo the SIU SMASK रेजिस्टर.
 * Many of the prep/chrp functions are conditional compiled on CONFIG_PPC_8xx
 * to reduce code space and undefined function references.
 */

#अघोषित DEBUG

#समावेश <linux/export.h>
#समावेश <linux/thपढ़ोs.h>
#समावेश <linux/kernel_स्थिति.स>
#समावेश <linux/संकेत.स>
#समावेश <linux/sched.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/ioport.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/समयx.h>
#समावेश <linux/init.h>
#समावेश <linux/slab.h>
#समावेश <linux/delay.h>
#समावेश <linux/irq.h>
#समावेश <linux/seq_file.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/profile.h>
#समावेश <linux/bitops.h>
#समावेश <linux/list.h>
#समावेश <linux/radix-tree.h>
#समावेश <linux/mutex.h>
#समावेश <linux/pci.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/of.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/pgtable.h>

#समावेश <linux/uaccess.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/irq.h>
#समावेश <यंत्र/cache.h>
#समावेश <यंत्र/prom.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/udbg.h>
#समावेश <यंत्र/smp.h>
#समावेश <यंत्र/livepatch.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/hw_irq.h>
#समावेश <यंत्र/softirq_stack.h>

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/paca.h>
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/lv1call.h>
#समावेश <यंत्र/dbell.h>
#पूर्ण_अगर
#घोषणा CREATE_TRACE_POINTS
#समावेश <यंत्र/trace.h>
#समावेश <यंत्र/cpu_has_feature.h>

DEFINE_PER_CPU_SHARED_ALIGNED(irq_cpustat_t, irq_stat);
EXPORT_PER_CPU_SYMBOL(irq_stat);

#अगर_घोषित CONFIG_PPC32
atomic_t ppc_n_lost_पूर्णांकerrupts;

#अगर_घोषित CONFIG_TAU_INT
बाह्य पूर्णांक tau_initialized;
u32 tau_पूर्णांकerrupts(अचिन्हित दीर्घ cpu);
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PPC32 */

#अगर_घोषित CONFIG_PPC64

पूर्णांक distribute_irqs = 1;

अटल अंतरभूत notrace अचिन्हित दीर्घ get_irq_happened(व्योम)
अणु
	अचिन्हित दीर्घ happened;

	__यंत्र__ __अस्थिर__("lbz %0,%1(13)"
	: "=r" (happened) : "i" (दुरत्व(काष्ठा paca_काष्ठा, irq_happened)));

	वापस happened;
पूर्ण

व्योम replay_soft_पूर्णांकerrupts(व्योम)
अणु
	काष्ठा pt_regs regs;

	/*
	 * Be careful here, calling these पूर्णांकerrupt handlers can cause
	 * softirqs to be उठाओd, which they may run when calling irq_निकास,
	 * which will cause local_irq_enable() to be run, which can then
	 * recurse पूर्णांकo this function. Don't keep any state across
	 * पूर्णांकerrupt handler calls which may change underneath us.
	 *
	 * We use local_paca rather than get_paca() to aव्योम all the
	 * debug_smp_processor_id() business in this low level function.
	 */

	ppc_save_regs(&regs);
	regs.softe = IRQS_ENABLED;

again:
	अगर (IS_ENABLED(CONFIG_PPC_IRQ_SOFT_MASK_DEBUG))
		WARN_ON_ONCE(mfmsr() & MSR_EE);

	/*
	 * Force the delivery of pending soft-disabled पूर्णांकerrupts on PS3.
	 * Any HV call will have this side effect.
	 */
	अगर (firmware_has_feature(FW_FEATURE_PS3_LV1)) अणु
		u64 पंचांगp, पंचांगp2;
		lv1_get_version_info(&पंचांगp, &पंचांगp2);
	पूर्ण

	/*
	 * Check अगर an hypervisor Maपूर्णांकenance पूर्णांकerrupt happened.
	 * This is a higher priority पूर्णांकerrupt than the others, so
	 * replay it first.
	 */
	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S) && (local_paca->irq_happened & PACA_IRQ_HMI)) अणु
		local_paca->irq_happened &= ~PACA_IRQ_HMI;
		regs.trap = INTERRUPT_HMI;
		handle_hmi_exception(&regs);
		अगर (!(local_paca->irq_happened & PACA_IRQ_HARD_DIS))
			hard_irq_disable();
	पूर्ण

	अगर (local_paca->irq_happened & PACA_IRQ_DEC) अणु
		local_paca->irq_happened &= ~PACA_IRQ_DEC;
		regs.trap = INTERRUPT_DECREMENTER;
		समयr_पूर्णांकerrupt(&regs);
		अगर (!(local_paca->irq_happened & PACA_IRQ_HARD_DIS))
			hard_irq_disable();
	पूर्ण

	अगर (local_paca->irq_happened & PACA_IRQ_EE) अणु
		local_paca->irq_happened &= ~PACA_IRQ_EE;
		regs.trap = INTERRUPT_EXTERNAL;
		करो_IRQ(&regs);
		अगर (!(local_paca->irq_happened & PACA_IRQ_HARD_DIS))
			hard_irq_disable();
	पूर्ण

	अगर (IS_ENABLED(CONFIG_PPC_DOORBELL) && (local_paca->irq_happened & PACA_IRQ_DBELL)) अणु
		local_paca->irq_happened &= ~PACA_IRQ_DBELL;
		regs.trap = INTERRUPT_DOORBELL;
		करोorbell_exception(&regs);
		अगर (!(local_paca->irq_happened & PACA_IRQ_HARD_DIS))
			hard_irq_disable();
	पूर्ण

	/* Book3E करोes not support soft-masking PMI पूर्णांकerrupts */
	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S) && (local_paca->irq_happened & PACA_IRQ_PMI)) अणु
		local_paca->irq_happened &= ~PACA_IRQ_PMI;
		regs.trap = INTERRUPT_PERFMON;
		perक्रमmance_monitor_exception(&regs);
		अगर (!(local_paca->irq_happened & PACA_IRQ_HARD_DIS))
			hard_irq_disable();
	पूर्ण

	अगर (local_paca->irq_happened & ~PACA_IRQ_HARD_DIS) अणु
		/*
		 * We are responding to the next पूर्णांकerrupt, so पूर्णांकerrupt-off
		 * latencies should be reset here.
		 */
		trace_hardirqs_on();
		trace_hardirqs_off();
		जाओ again;
	पूर्ण
पूर्ण

#अगर defined(CONFIG_PPC_BOOK3S_64) && defined(CONFIG_PPC_KUAP)
अटल अंतरभूत व्योम replay_soft_पूर्णांकerrupts_irqrestore(व्योम)
अणु
	अचिन्हित दीर्घ kuap_state = get_kuap();

	/*
	 * Check अगर anything calls local_irq_enable/restore() when KUAP is
	 * disabled (user access enabled). We handle that हाल here by saving
	 * and re-locking AMR but we shouldn't get here in the first place,
	 * hence the warning.
	 */
	kuap_निश्चित_locked();

	अगर (kuap_state != AMR_KUAP_BLOCKED)
		set_kuap(AMR_KUAP_BLOCKED);

	replay_soft_पूर्णांकerrupts();

	अगर (kuap_state != AMR_KUAP_BLOCKED)
		set_kuap(kuap_state);
पूर्ण
#अन्यथा
#घोषणा replay_soft_पूर्णांकerrupts_irqrestore() replay_soft_पूर्णांकerrupts()
#पूर्ण_अगर

notrace व्योम arch_local_irq_restore(अचिन्हित दीर्घ mask)
अणु
	अचिन्हित अक्षर irq_happened;

	/* Write the new soft-enabled value */
	irq_soft_mask_set(mask);
	अगर (mask)
		वापस;

	/*
	 * From this poपूर्णांक onward, we can take पूर्णांकerrupts, preempt,
	 * etc... unless we got hard-disabled. We check अगर an event
	 * happened. If none happened, we know we can just वापस.
	 *
	 * We may have preempted beक्रमe the check below, in which हाल
	 * we are checking the "new" CPU instead of the old one. This
	 * is only a problem अगर an event happened on the "old" CPU.
	 *
	 * External पूर्णांकerrupt events will have caused पूर्णांकerrupts to
	 * be hard-disabled, so there is no problem, we
	 * cannot have preempted.
	 */
	irq_happened = get_irq_happened();
	अगर (!irq_happened) अणु
		अगर (IS_ENABLED(CONFIG_PPC_IRQ_SOFT_MASK_DEBUG))
			WARN_ON_ONCE(!(mfmsr() & MSR_EE));
		वापस;
	पूर्ण

	/* We need to hard disable to replay. */
	अगर (!(irq_happened & PACA_IRQ_HARD_DIS)) अणु
		अगर (IS_ENABLED(CONFIG_PPC_IRQ_SOFT_MASK_DEBUG))
			WARN_ON_ONCE(!(mfmsr() & MSR_EE));
		__hard_irq_disable();
		local_paca->irq_happened |= PACA_IRQ_HARD_DIS;
	पूर्ण अन्यथा अणु
		/*
		 * We should alपढ़ोy be hard disabled here. We had bugs
		 * where that wasn't the case so let's dbl check it and
		 * warn अगर we are wrong. Only करो that when IRQ tracing
		 * is enabled as mfmsr() can be costly.
		 */
		अगर (IS_ENABLED(CONFIG_PPC_IRQ_SOFT_MASK_DEBUG)) अणु
			अगर (WARN_ON_ONCE(mfmsr() & MSR_EE))
				__hard_irq_disable();
		पूर्ण

		अगर (irq_happened == PACA_IRQ_HARD_DIS) अणु
			local_paca->irq_happened = 0;
			__hard_irq_enable();
			वापस;
		पूर्ण
	पूर्ण

	/*
	 * Disable preempt here, so that the below preempt_enable will
	 * perक्रमm resched अगर required (a replayed पूर्णांकerrupt may set
	 * need_resched).
	 */
	preempt_disable();
	irq_soft_mask_set(IRQS_ALL_DISABLED);
	trace_hardirqs_off();

	replay_soft_पूर्णांकerrupts_irqrestore();
	local_paca->irq_happened = 0;

	trace_hardirqs_on();
	irq_soft_mask_set(IRQS_ENABLED);
	__hard_irq_enable();
	preempt_enable();
पूर्ण
EXPORT_SYMBOL(arch_local_irq_restore);

/*
 * This is a helper to use when about to go पूर्णांकo idle low-घातer
 * when the latter has the side effect of re-enabling पूर्णांकerrupts
 * (such as calling H_CEDE under pHyp).
 *
 * You call this function with पूर्णांकerrupts soft-disabled (this is
 * alपढ़ोy the हाल when ppc_md.घातer_save is called). The function
 * will वापस whether to enter घातer save or just वापस.
 *
 * In the क्रमmer हाल, it will have notअगरied lockdep of पूर्णांकerrupts
 * being re-enabled and generally sanitized the lazy irq state,
 * and in the latter हाल it will leave with पूर्णांकerrupts hard
 * disabled and marked as such, so the local_irq_enable() call
 * in arch_cpu_idle() will properly re-enable everything.
 */
bool prep_irq_क्रम_idle(व्योम)
अणु
	/*
	 * First we need to hard disable to ensure no पूर्णांकerrupt
	 * occurs beक्रमe we effectively enter the low घातer state
	 */
	__hard_irq_disable();
	local_paca->irq_happened |= PACA_IRQ_HARD_DIS;

	/*
	 * If anything happened जबतक we were soft-disabled,
	 * we वापस now and करो not enter the low घातer state.
	 */
	अगर (lazy_irq_pending())
		वापस false;

	/* Tell lockdep we are about to re-enable */
	trace_hardirqs_on();

	/*
	 * Mark पूर्णांकerrupts as soft-enabled and clear the
	 * PACA_IRQ_HARD_DIS from the pending mask since we
	 * are about to hard enable as well as a side effect
	 * of entering the low घातer state.
	 */
	local_paca->irq_happened &= ~PACA_IRQ_HARD_DIS;
	irq_soft_mask_set(IRQS_ENABLED);

	/* Tell the caller to enter the low घातer state */
	वापस true;
पूर्ण

#अगर_घोषित CONFIG_PPC_BOOK3S
/*
 * This is क्रम idle sequences that वापस with IRQs off, but the
 * idle state itself wakes on पूर्णांकerrupt. Tell the irq tracer that
 * IRQs are enabled क्रम the duration of idle so it करोes not get दीर्घ
 * off बार. Must be paired with fini_irq_क्रम_idle_irqsoff.
 */
bool prep_irq_क्रम_idle_irqsoff(व्योम)
अणु
	WARN_ON(!irqs_disabled());

	/*
	 * First we need to hard disable to ensure no पूर्णांकerrupt
	 * occurs beक्रमe we effectively enter the low घातer state
	 */
	__hard_irq_disable();
	local_paca->irq_happened |= PACA_IRQ_HARD_DIS;

	/*
	 * If anything happened जबतक we were soft-disabled,
	 * we वापस now and करो not enter the low घातer state.
	 */
	अगर (lazy_irq_pending())
		वापस false;

	/* Tell lockdep we are about to re-enable */
	trace_hardirqs_on();

	वापस true;
पूर्ण

/*
 * Take the SRR1 wakeup reason, index पूर्णांकo this table to find the
 * appropriate irq_happened bit.
 *
 * Sytem reset exceptions taken in idle state also come through here,
 * but they are NMI पूर्णांकerrupts so करो not need to रुको क्रम IRQs to be
 * restored, and should be taken as early as practical. These are marked
 * with 0xff in the table. The Power ISA specअगरies 0100b as the प्रणाली
 * reset पूर्णांकerrupt reason.
 */
#घोषणा IRQ_SYSTEM_RESET	0xff

अटल स्थिर u8 srr1_to_lazyirq[0x10] = अणु
	0, 0, 0,
	PACA_IRQ_DBELL,
	IRQ_SYSTEM_RESET,
	PACA_IRQ_DBELL,
	PACA_IRQ_DEC,
	0,
	PACA_IRQ_EE,
	PACA_IRQ_EE,
	PACA_IRQ_HMI,
	0, 0, 0, 0, 0 पूर्ण;

व्योम replay_प्रणाली_reset(व्योम)
अणु
	काष्ठा pt_regs regs;

	ppc_save_regs(&regs);
	regs.trap = 0x100;
	get_paca()->in_nmi = 1;
	प्रणाली_reset_exception(&regs);
	get_paca()->in_nmi = 0;
पूर्ण
EXPORT_SYMBOL_GPL(replay_प्रणाली_reset);

व्योम irq_set_pending_from_srr1(अचिन्हित दीर्घ srr1)
अणु
	अचिन्हित पूर्णांक idx = (srr1 & SRR1_WAKEMASK_P8) >> 18;
	u8 reason = srr1_to_lazyirq[idx];

	/*
	 * Take the प्रणाली reset now, which is immediately after रेजिस्टरs
	 * are restored from idle. It's an NMI, so पूर्णांकerrupts need not be
	 * re-enabled beक्रमe it is taken.
	 */
	अगर (unlikely(reason == IRQ_SYSTEM_RESET)) अणु
		replay_प्रणाली_reset();
		वापस;
	पूर्ण

	अगर (reason == PACA_IRQ_DBELL) अणु
		/*
		 * When करोorbell triggers a प्रणाली reset wakeup, the message
		 * is not cleared, so अगर the करोorbell पूर्णांकerrupt is replayed
		 * and the IPI handled, the करोorbell पूर्णांकerrupt would still
		 * fire when EE is enabled.
		 *
		 * To aव्योम taking the superfluous करोorbell पूर्णांकerrupt,
		 * execute a msgclr here beक्रमe the पूर्णांकerrupt is replayed.
		 */
		ppc_msgclr(PPC_DBELL_MSGTYPE);
	पूर्ण

	/*
	 * The 0 index (SRR1[42:45]=b0000) must always evaluate to 0,
	 * so this can be called unconditionally with the SRR1 wake
	 * reason as वापसed by the idle code, which uses 0 to mean no
	 * पूर्णांकerrupt.
	 *
	 * If a future CPU was to designate this as an पूर्णांकerrupt reason,
	 * then a new index क्रम no पूर्णांकerrupt must be asचिन्हित.
	 */
	local_paca->irq_happened |= reason;
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S */

/*
 * Force a replay of the बाह्यal पूर्णांकerrupt handler on this CPU.
 */
व्योम क्रमce_बाह्यal_irq_replay(व्योम)
अणु
	/*
	 * This must only be called with पूर्णांकerrupts soft-disabled,
	 * the replay will happen when re-enabling.
	 */
	WARN_ON(!arch_irqs_disabled());

	/*
	 * Interrupts must always be hard disabled beक्रमe irq_happened is
	 * modअगरied (to prevent lost update in हाल of पूर्णांकerrupt between
	 * load and store).
	 */
	__hard_irq_disable();
	local_paca->irq_happened |= PACA_IRQ_HARD_DIS;

	/* Indicate in the PACA that we have an पूर्णांकerrupt to replay */
	local_paca->irq_happened |= PACA_IRQ_EE;
पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

पूर्णांक arch_show_पूर्णांकerrupts(काष्ठा seq_file *p, पूर्णांक prec)
अणु
	पूर्णांक j;

#अगर defined(CONFIG_PPC32) && defined(CONFIG_TAU_INT)
	अगर (tau_initialized) अणु
		seq_म_लिखो(p, "%*s: ", prec, "TAU");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ", tau_पूर्णांकerrupts(j));
		seq_माला_दो(p, "  PowerPC             Thermal Assist (cpu temp)\n");
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 && CONFIG_TAU_INT */

	seq_म_लिखो(p, "%*s: ", prec, "LOC");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).समयr_irqs_event);
        seq_म_लिखो(p, "  Local timer interrupts for timer event device\n");

	seq_म_लिखो(p, "%*s: ", prec, "BCT");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).broadcast_irqs_event);
	seq_म_लिखो(p, "  Broadcast timer interrupts for timer event device\n");

	seq_म_लिखो(p, "%*s: ", prec, "LOC");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).समयr_irqs_others);
        seq_म_लिखो(p, "  Local timer interrupts for others\n");

	seq_म_लिखो(p, "%*s: ", prec, "SPU");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).spurious_irqs);
	seq_म_लिखो(p, "  Spurious interrupts\n");

	seq_म_लिखो(p, "%*s: ", prec, "PMI");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).pmu_irqs);
	seq_म_लिखो(p, "  Performance monitoring interrupts\n");

	seq_म_लिखो(p, "%*s: ", prec, "MCE");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).mce_exceptions);
	seq_म_लिखो(p, "  Machine check exceptions\n");

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		seq_म_लिखो(p, "%*s: ", prec, "HMI");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ", paca_ptrs[j]->hmi_irqs);
		seq_म_लिखो(p, "  Hypervisor Maintenance Interrupts\n");
	पूर्ण
#पूर्ण_अगर

	seq_म_लिखो(p, "%*s: ", prec, "NMI");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).sreset_irqs);
	seq_म_लिखो(p, "  System Reset interrupts\n");

#अगर_घोषित CONFIG_PPC_WATCHDOG
	seq_म_लिखो(p, "%*s: ", prec, "WDG");
	क्रम_each_online_cpu(j)
		seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).soft_nmi_irqs);
	seq_म_लिखो(p, "  Watchdog soft-NMI interrupts\n");
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_DOORBELL
	अगर (cpu_has_feature(CPU_FTR_DBELL)) अणु
		seq_म_लिखो(p, "%*s: ", prec, "DBL");
		क्रम_each_online_cpu(j)
			seq_म_लिखो(p, "%10u ", per_cpu(irq_stat, j).करोorbell_irqs);
		seq_म_लिखो(p, "  Doorbell interrupts\n");
	पूर्ण
#पूर्ण_अगर

	वापस 0;
पूर्ण

/*
 * /proc/stat helpers
 */
u64 arch_irq_stat_cpu(अचिन्हित पूर्णांक cpu)
अणु
	u64 sum = per_cpu(irq_stat, cpu).समयr_irqs_event;

	sum += per_cpu(irq_stat, cpu).broadcast_irqs_event;
	sum += per_cpu(irq_stat, cpu).pmu_irqs;
	sum += per_cpu(irq_stat, cpu).mce_exceptions;
	sum += per_cpu(irq_stat, cpu).spurious_irqs;
	sum += per_cpu(irq_stat, cpu).समयr_irqs_others;
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	sum += paca_ptrs[cpu]->hmi_irqs;
#पूर्ण_अगर
	sum += per_cpu(irq_stat, cpu).sreset_irqs;
#अगर_घोषित CONFIG_PPC_WATCHDOG
	sum += per_cpu(irq_stat, cpu).soft_nmi_irqs;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_DOORBELL
	sum += per_cpu(irq_stat, cpu).करोorbell_irqs;
#पूर्ण_अगर

	वापस sum;
पूर्ण

अटल अंतरभूत व्योम check_stack_overflow(व्योम)
अणु
	दीर्घ sp;

	अगर (!IS_ENABLED(CONFIG_DEBUG_STACKOVERFLOW))
		वापस;

	sp = current_stack_poपूर्णांकer & (THREAD_SIZE - 1);

	/* check क्रम stack overflow: is there less than 2KB मुक्त? */
	अगर (unlikely(sp < 2048)) अणु
		pr_err("do_IRQ: stack overflow: %ld\n", sp);
		dump_stack();
	पूर्ण
पूर्ण

अटल __always_अंतरभूत व्योम call_करो_softirq(स्थिर व्योम *sp)
अणु
	/* Temporarily चयन r1 to sp, call __करो_softirq() then restore r1. */
	यंत्र अस्थिर (
		 PPC_STLU "	%%r1, %[offset](%[sp])	;"
		"mr		%%r1, %[sp]		;"
		"bl		%[callee]		;"
		 PPC_LL "	%%r1, 0(%%r1)		;"
		 : // Outमाला_दो
		 : // Inमाला_दो
		   [sp] "b" (sp), [offset] "i" (THREAD_SIZE - STACK_FRAME_OVERHEAD),
		   [callee] "i" (__करो_softirq)
		 : // Clobbers
		   "lr", "xer", "ctr", "memory", "cr0", "cr1", "cr5", "cr6",
		   "cr7", "r0", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10",
		   "r11", "r12"
	);
पूर्ण

अटल __always_अंतरभूत व्योम call_करो_irq(काष्ठा pt_regs *regs, व्योम *sp)
अणु
	रेजिस्टर अचिन्हित दीर्घ r3 यंत्र("r3") = (अचिन्हित दीर्घ)regs;

	/* Temporarily चयन r1 to sp, call __करो_irq() then restore r1. */
	यंत्र अस्थिर (
		 PPC_STLU "	%%r1, %[offset](%[sp])	;"
		"mr		%%r1, %[sp]		;"
		"bl		%[callee]		;"
		 PPC_LL "	%%r1, 0(%%r1)		;"
		 : // Outमाला_दो
		   "+r" (r3)
		 : // Inमाला_दो
		   [sp] "b" (sp), [offset] "i" (THREAD_SIZE - STACK_FRAME_OVERHEAD),
		   [callee] "i" (__करो_irq)
		 : // Clobbers
		   "lr", "xer", "ctr", "memory", "cr0", "cr1", "cr5", "cr6",
		   "cr7", "r0", "r4", "r5", "r6", "r7", "r8", "r9", "r10",
		   "r11", "r12"
	);
पूर्ण

व्योम __करो_irq(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक irq;

	trace_irq_entry(regs);

	/*
	 * Query the platक्रमm PIC क्रम the पूर्णांकerrupt & ack it.
	 *
	 * This will typically lower the पूर्णांकerrupt line to the CPU
	 */
	irq = ppc_md.get_irq();

	/* We can hard enable पूर्णांकerrupts now to allow perf पूर्णांकerrupts */
	may_hard_irq_enable();

	/* And finally process it */
	अगर (unlikely(!irq))
		__this_cpu_inc(irq_stat.spurious_irqs);
	अन्यथा
		generic_handle_irq(irq);

	trace_irq_निकास(regs);
पूर्ण

DEFINE_INTERRUPT_HANDLER_ASYNC(करो_IRQ)
अणु
	काष्ठा pt_regs *old_regs = set_irq_regs(regs);
	व्योम *cursp, *irqsp, *sirqsp;

	/* Switch to the irq stack to handle this */
	cursp = (व्योम *)(current_stack_poपूर्णांकer & ~(THREAD_SIZE - 1));
	irqsp = hardirq_ctx[raw_smp_processor_id()];
	sirqsp = softirq_ctx[raw_smp_processor_id()];

	check_stack_overflow();

	/* Alपढ़ोy there ? */
	अगर (unlikely(cursp == irqsp || cursp == sirqsp)) अणु
		__करो_irq(regs);
		set_irq_regs(old_regs);
		वापस;
	पूर्ण
	/* Switch stack and call */
	call_करो_irq(regs, irqsp);

	set_irq_regs(old_regs);
पूर्ण

अटल व्योम *__init alloc_vm_stack(व्योम)
अणु
	वापस __vदो_स्मृति_node(THREAD_SIZE, THREAD_ALIGN, THREADINFO_GFP,
			      NUMA_NO_NODE, (व्योम *)_RET_IP_);
पूर्ण

अटल व्योम __init vmap_irqstack_init(व्योम)
अणु
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		softirq_ctx[i] = alloc_vm_stack();
		hardirq_ctx[i] = alloc_vm_stack();
	पूर्ण
पूर्ण


व्योम __init init_IRQ(व्योम)
अणु
	अगर (IS_ENABLED(CONFIG_VMAP_STACK))
		vmap_irqstack_init();

	अगर (ppc_md.init_IRQ)
		ppc_md.init_IRQ();
पूर्ण

#अगर defined(CONFIG_BOOKE) || defined(CONFIG_40x)
व्योम   *critirq_ctx[NR_CPUS] __पढ़ो_mostly;
व्योम    *dbgirq_ctx[NR_CPUS] __पढ़ो_mostly;
व्योम *mcheckirq_ctx[NR_CPUS] __पढ़ो_mostly;
#पूर्ण_अगर

व्योम *softirq_ctx[NR_CPUS] __पढ़ो_mostly;
व्योम *hardirq_ctx[NR_CPUS] __पढ़ो_mostly;

व्योम करो_softirq_own_stack(व्योम)
अणु
	call_करो_softirq(softirq_ctx[smp_processor_id()]);
पूर्ण

irq_hw_number_t virq_to_hw(अचिन्हित पूर्णांक virq)
अणु
	काष्ठा irq_data *irq_data = irq_get_irq_data(virq);
	वापस WARN_ON(!irq_data) ? 0 : irq_data->hwirq;
पूर्ण
EXPORT_SYMBOL_GPL(virq_to_hw);

#अगर_घोषित CONFIG_SMP
पूर्णांक irq_choose_cpu(स्थिर काष्ठा cpumask *mask)
अणु
	पूर्णांक cpuid;

	अगर (cpumask_equal(mask, cpu_online_mask)) अणु
		अटल पूर्णांक irq_rover;
		अटल DEFINE_RAW_SPINLOCK(irq_rover_lock);
		अचिन्हित दीर्घ flags;

		/* Round-robin distribution... */
करो_round_robin:
		raw_spin_lock_irqsave(&irq_rover_lock, flags);

		irq_rover = cpumask_next(irq_rover, cpu_online_mask);
		अगर (irq_rover >= nr_cpu_ids)
			irq_rover = cpumask_first(cpu_online_mask);

		cpuid = irq_rover;

		raw_spin_unlock_irqrestore(&irq_rover_lock, flags);
	पूर्ण अन्यथा अणु
		cpuid = cpumask_first_and(mask, cpu_online_mask);
		अगर (cpuid >= nr_cpu_ids)
			जाओ करो_round_robin;
	पूर्ण

	वापस get_hard_smp_processor_id(cpuid);
पूर्ण
#अन्यथा
पूर्णांक irq_choose_cpu(स्थिर काष्ठा cpumask *mask)
अणु
	वापस hard_smp_processor_id();
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
अटल पूर्णांक __init setup_noirqdistrib(अक्षर *str)
अणु
	distribute_irqs = 0;
	वापस 1;
पूर्ण

__setup("noirqdistrib", setup_noirqdistrib);
#पूर्ण_अगर /* CONFIG_PPC64 */
