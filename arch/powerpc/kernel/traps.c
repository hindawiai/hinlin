<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 *  Copyright (C) 1995-1996  Gary Thomas (gdt@linuxppc.org)
 *  Copyright 2007-2010 Freescale Semiconductor, Inc.
 *
 *  Modअगरied by Cort Dougan (cort@cs.nmt.edu)
 *  and Paul Mackerras (paulus@samba.org)
 */

/*
 * This file handles the architecture-dependent parts of hardware exceptions
 */

#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/sched.h>
#समावेश <linux/sched/debug.h>
#समावेश <linux/kernel.h>
#समावेश <linux/mm.h>
#समावेश <linux/pkeys.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/unistd.h>
#समावेश <linux/ptrace.h>
#समावेश <linux/user.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/init.h>
#समावेश <linux/extable.h>
#समावेश <linux/module.h>	/* prपूर्णांक_modules */
#समावेश <linux/prctl.h>
#समावेश <linux/delay.h>
#समावेश <linux/kprobes.h>
#समावेश <linux/kexec.h>
#समावेश <linux/backlight.h>
#समावेश <linux/bug.h>
#समावेश <linux/kdebug.h>
#समावेश <linux/ratelimit.h>
#समावेश <linux/context_tracking.h>
#समावेश <linux/smp.h>
#समावेश <linux/console.h>
#समावेश <linux/kmsg_dump.h>

#समावेश <यंत्र/emulated_ops.h>
#समावेश <linux/uaccess.h>
#समावेश <यंत्र/debugfs.h>
#समावेश <यंत्र/पूर्णांकerrupt.h>
#समावेश <यंत्र/पन.स>
#समावेश <यंत्र/machdep.h>
#समावेश <यंत्र/rtas.h>
#समावेश <यंत्र/pmc.h>
#समावेश <यंत्र/reg.h>
#अगर_घोषित CONFIG_PMAC_BACKLIGHT
#समावेश <यंत्र/backlight.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/firmware.h>
#समावेश <यंत्र/processor.h>
#पूर्ण_अगर
#समावेश <यंत्र/kexec.h>
#समावेश <यंत्र/ppc-opcode.h>
#समावेश <यंत्र/rपन.स>
#समावेश <यंत्र/fadump.h>
#समावेश <यंत्र/चयन_to.h>
#समावेश <यंत्र/पंचांग.h>
#समावेश <यंत्र/debug.h>
#समावेश <यंत्र/यंत्र-prototypes.h>
#समावेश <यंत्र/hmi.h>
#समावेश <sysdev/fsl_pci.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/stacktrace.h>
#समावेश <यंत्र/nmi.h>

#अगर defined(CONFIG_DEBUGGER) || defined(CONFIG_KEXEC_CORE)
पूर्णांक (*__debugger)(काष्ठा pt_regs *regs) __पढ़ो_mostly;
पूर्णांक (*__debugger_ipi)(काष्ठा pt_regs *regs) __पढ़ो_mostly;
पूर्णांक (*__debugger_bpt)(काष्ठा pt_regs *regs) __पढ़ो_mostly;
पूर्णांक (*__debugger_sstep)(काष्ठा pt_regs *regs) __पढ़ो_mostly;
पूर्णांक (*__debugger_iabr_match)(काष्ठा pt_regs *regs) __पढ़ो_mostly;
पूर्णांक (*__debugger_अवरोध_match)(काष्ठा pt_regs *regs) __पढ़ो_mostly;
पूर्णांक (*__debugger_fault_handler)(काष्ठा pt_regs *regs) __पढ़ो_mostly;

EXPORT_SYMBOL(__debugger);
EXPORT_SYMBOL(__debugger_ipi);
EXPORT_SYMBOL(__debugger_bpt);
EXPORT_SYMBOL(__debugger_sstep);
EXPORT_SYMBOL(__debugger_iabr_match);
EXPORT_SYMBOL(__debugger_अवरोध_match);
EXPORT_SYMBOL(__debugger_fault_handler);
#पूर्ण_अगर

/* Transactional Memory trap debug */
#अगर_घोषित TM_DEBUG_SW
#घोषणा TM_DEBUG(x...) prपूर्णांकk(KERN_INFO x)
#अन्यथा
#घोषणा TM_DEBUG(x...) करो अणु पूर्ण जबतक(0)
#पूर्ण_अगर

अटल स्थिर अक्षर *signame(पूर्णांक signr)
अणु
	चयन (signr) अणु
	हाल SIGBUS:	वापस "bus error";
	हाल संक_भ_त्रुटि:	वापस "floating point exception";
	हाल संक_अवैध:	वापस "illegal instruction";
	हाल संक_अंश:	वापस "segfault";
	हाल SIGTRAP:	वापस "unhandled trap";
	पूर्ण

	वापस "unknown signal";
पूर्ण

/*
 * Trap & Exception support
 */

#अगर_घोषित CONFIG_PMAC_BACKLIGHT
अटल व्योम pmac_backlight_unblank(व्योम)
अणु
	mutex_lock(&pmac_backlight_mutex);
	अगर (pmac_backlight) अणु
		काष्ठा backlight_properties *props;

		props = &pmac_backlight->props;
		props->brightness = props->max_brightness;
		props->घातer = FB_BLANK_UNBLANK;
		backlight_update_status(pmac_backlight);
	पूर्ण
	mutex_unlock(&pmac_backlight_mutex);
पूर्ण
#अन्यथा
अटल अंतरभूत व्योम pmac_backlight_unblank(व्योम) अणु पूर्ण
#पूर्ण_अगर

/*
 * If oops/die is expected to crash the machine, वापस true here.
 *
 * This should not be expected to be 100% accurate, there may be
 * notअगरiers रेजिस्टरed or other unexpected conditions that may bring
 * करोwn the kernel. Or अगर the current process in the kernel is holding
 * locks or has other critical state, the kernel may become effectively
 * unusable anyway.
 */
bool die_will_crash(व्योम)
अणु
	अगर (should_fadump_crash())
		वापस true;
	अगर (kexec_should_crash(current))
		वापस true;
	अगर (in_पूर्णांकerrupt() || panic_on_oops ||
			!current->pid || is_global_init(current))
		वापस true;

	वापस false;
पूर्ण

अटल arch_spinlock_t die_lock = __ARCH_SPIN_LOCK_UNLOCKED;
अटल पूर्णांक die_owner = -1;
अटल अचिन्हित पूर्णांक die_nest_count;
अटल पूर्णांक die_counter;

बाह्य व्योम panic_flush_kmsg_start(व्योम)
अणु
	/*
	 * These are mostly taken from kernel/panic.c, but tries to करो
	 * relatively minimal work. Don't use delay functions (TB may
	 * be broken), करोn't crash dump (need to set a firmware log),
	 * करोn't run notअगरiers. We करो want to get some inक्रमmation to
	 * Linux console.
	 */
	console_verbose();
	bust_spinlocks(1);
पूर्ण

बाह्य व्योम panic_flush_kmsg_end(व्योम)
अणु
	prपूर्णांकk_safe_flush_on_panic();
	kmsg_dump(KMSG_DUMP_PANIC);
	bust_spinlocks(0);
	debug_locks_off();
	console_flush_on_panic(CONSOLE_FLUSH_PENDING);
पूर्ण

अटल अचिन्हित दीर्घ oops_begin(काष्ठा pt_regs *regs)
अणु
	पूर्णांक cpu;
	अचिन्हित दीर्घ flags;

	oops_enter();

	/* racy, but better than risking deadlock. */
	raw_local_irq_save(flags);
	cpu = smp_processor_id();
	अगर (!arch_spin_trylock(&die_lock)) अणु
		अगर (cpu == die_owner)
			/* nested oops. should stop eventually */;
		अन्यथा
			arch_spin_lock(&die_lock);
	पूर्ण
	die_nest_count++;
	die_owner = cpu;
	console_verbose();
	bust_spinlocks(1);
	अगर (machine_is(घातermac))
		pmac_backlight_unblank();
	वापस flags;
पूर्ण
NOKPROBE_SYMBOL(oops_begin);

अटल व्योम oops_end(अचिन्हित दीर्घ flags, काष्ठा pt_regs *regs,
			       पूर्णांक signr)
अणु
	bust_spinlocks(0);
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	die_nest_count--;
	oops_निकास();
	prपूर्णांकk("\n");
	अगर (!die_nest_count) अणु
		/* Nest count reaches zero, release the lock. */
		die_owner = -1;
		arch_spin_unlock(&die_lock);
	पूर्ण
	raw_local_irq_restore(flags);

	/*
	 * प्रणाली_reset_excption handles debugger, crash dump, panic, क्रम 0x100
	 */
	अगर (TRAP(regs) == INTERRUPT_SYSTEM_RESET)
		वापस;

	crash_fadump(regs, "die oops");

	अगर (kexec_should_crash(current))
		crash_kexec(regs);

	अगर (!signr)
		वापस;

	/*
	 * While our oops output is serialised by a spinlock, output
	 * from panic() called below can race and corrupt it. If we
	 * know we are going to panic, delay क्रम 1 second so we have a
	 * chance to get clean backtraces from all CPUs that are oopsing.
	 */
	अगर (in_पूर्णांकerrupt() || panic_on_oops || !current->pid ||
	    is_global_init(current)) अणु
		mdelay(MSEC_PER_SEC);
	पूर्ण

	अगर (panic_on_oops)
		panic("Fatal exception");
	करो_निकास(signr);
पूर्ण
NOKPROBE_SYMBOL(oops_end);

अटल अक्षर *get_mmu_str(व्योम)
अणु
	अगर (early_radix_enabled())
		वापस " MMU=Radix";
	अगर (early_mmu_has_feature(MMU_FTR_HPTE_TABLE))
		वापस " MMU=Hash";
	वापस "";
पूर्ण

अटल पूर्णांक __die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	prपूर्णांकk("Oops: %s, sig: %ld [#%d]\n", str, err, ++die_counter);

	prपूर्णांकk("%s PAGE_SIZE=%luK%s%s%s%s%s%s %s\n",
	       IS_ENABLED(CONFIG_CPU_LITTLE_ENDIAN) ? "LE" : "BE",
	       PAGE_SIZE / 1024, get_mmu_str(),
	       IS_ENABLED(CONFIG_PREEMPT) ? " PREEMPT" : "",
	       IS_ENABLED(CONFIG_SMP) ? " SMP" : "",
	       IS_ENABLED(CONFIG_SMP) ? (" NR_CPUS=" __stringअगरy(NR_CPUS)) : "",
	       debug_pagealloc_enabled() ? " DEBUG_PAGEALLOC" : "",
	       IS_ENABLED(CONFIG_NUMA) ? " NUMA" : "",
	       ppc_md.name ? ppc_md.name : "");

	अगर (notअगरy_die(DIE_OOPS, str, regs, err, 255, संक_अंश) == NOTIFY_STOP)
		वापस 1;

	prपूर्णांक_modules();
	show_regs(regs);

	वापस 0;
पूर्ण
NOKPROBE_SYMBOL(__die);

व्योम die(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	अचिन्हित दीर्घ flags;

	/*
	 * प्रणाली_reset_excption handles debugger, crash dump, panic, क्रम 0x100
	 */
	अगर (TRAP(regs) != INTERRUPT_SYSTEM_RESET) अणु
		अगर (debugger(regs))
			वापस;
	पूर्ण

	flags = oops_begin(regs);
	अगर (__die(str, regs, err))
		err = 0;
	oops_end(flags, regs, err);
पूर्ण
NOKPROBE_SYMBOL(die);

व्योम user_single_step_report(काष्ठा pt_regs *regs)
अणु
	क्रमce_sig_fault(SIGTRAP, TRAP_TRACE, (व्योम __user *)regs->nip);
पूर्ण

अटल व्योम show_संकेत_msg(पूर्णांक signr, काष्ठा pt_regs *regs, पूर्णांक code,
			    अचिन्हित दीर्घ addr)
अणु
	अटल DEFINE_RATELIMIT_STATE(rs, DEFAULT_RATELIMIT_INTERVAL,
				      DEFAULT_RATELIMIT_BURST);

	अगर (!show_unhandled_संकेतs)
		वापस;

	अगर (!unhandled_संकेत(current, signr))
		वापस;

	अगर (!__ratelimit(&rs))
		वापस;

	pr_info("%s[%d]: %s (%d) at %lx nip %lx lr %lx code %x",
		current->comm, current->pid, signame(signr), signr,
		addr, regs->nip, regs->link, code);

	prपूर्णांक_vma_addr(KERN_CONT " in ", regs->nip);

	pr_cont("\n");

	show_user_inकाष्ठाions(regs);
पूर्ण

अटल bool exception_common(पूर्णांक signr, काष्ठा pt_regs *regs, पूर्णांक code,
			      अचिन्हित दीर्घ addr)
अणु
	अगर (!user_mode(regs)) अणु
		die("Exception in kernel mode", regs, signr);
		वापस false;
	पूर्ण

	show_संकेत_msg(signr, regs, code, addr);

	अगर (arch_irqs_disabled())
		पूर्णांकerrupt_cond_local_irq_enable(regs);

	current->thपढ़ो.trap_nr = code;

	वापस true;
पूर्ण

व्योम _exception_pkey(काष्ठा pt_regs *regs, अचिन्हित दीर्घ addr, पूर्णांक key)
अणु
	अगर (!exception_common(संक_अंश, regs, SEGV_PKUERR, addr))
		वापस;

	क्रमce_sig_pkuerr((व्योम __user *) addr, key);
पूर्ण

व्योम _exception(पूर्णांक signr, काष्ठा pt_regs *regs, पूर्णांक code, अचिन्हित दीर्घ addr)
अणु
	अगर (!exception_common(signr, regs, code, addr))
		वापस;

	क्रमce_sig_fault(signr, code, (व्योम __user *)addr);
पूर्ण

/*
 * The पूर्णांकerrupt architecture has a quirk in that the HV पूर्णांकerrupts excluding
 * the NMIs (0x100 and 0x200) करो not clear MSR[RI] at entry. The first thing
 * that an पूर्णांकerrupt handler must करो is save off a GPR पूर्णांकo a scratch रेजिस्टर,
 * and all पूर्णांकerrupts on POWERNV (HV=1) use the HSPRG1 रेजिस्टर as scratch.
 * Thereक्रमe an NMI can clobber an HV पूर्णांकerrupt's live HSPRG1 without noticing
 * that it is non-reentrant, which leads to अक्रमom data corruption.
 *
 * The solution is क्रम NMI पूर्णांकerrupts in HV mode to check अगर they originated
 * from these critical HV पूर्णांकerrupt regions. If so, then mark them not
 * recoverable.
 *
 * An alternative would be क्रम HV NMIs to use SPRG क्रम scratch to aव्योम the
 * HSPRG1 clobber, however this would cause guest SPRG to be clobbered. Linux
 * guests should always have MSR[RI]=0 when its scratch SPRG is in use, so
 * that would work. However any other guest OS that may have the SPRG live
 * and MSR[RI]=1 could encounter silent corruption.
 *
 * Builds that करो not support KVM could take this second option to increase
 * the recoverability of NMIs.
 */
व्योम hv_nmi_check_nonrecoverable(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_PPC_POWERNV
	अचिन्हित दीर्घ kbase = (अचिन्हित दीर्घ)_stext;
	अचिन्हित दीर्घ nip = regs->nip;

	अगर (!(regs->msr & MSR_RI))
		वापस;
	अगर (!(regs->msr & MSR_HV))
		वापस;
	अगर (regs->msr & MSR_PR)
		वापस;

	/*
	 * Now test अगर the पूर्णांकerrupt has hit a range that may be using
	 * HSPRG1 without having RI=0 (i.e., an HSRR पूर्णांकerrupt). The
	 * problem ranges all run un-relocated. Test real and virt modes
	 * at the same समय by dropping the high bit of the nip (virt mode
	 * entry poपूर्णांकs still have the +0x4000 offset).
	 */
	nip &= ~0xc000000000000000ULL;
	अगर ((nip >= 0x500 && nip < 0x600) || (nip >= 0x4500 && nip < 0x4600))
		जाओ nonrecoverable;
	अगर ((nip >= 0x980 && nip < 0xa00) || (nip >= 0x4980 && nip < 0x4a00))
		जाओ nonrecoverable;
	अगर ((nip >= 0xe00 && nip < 0xec0) || (nip >= 0x4e00 && nip < 0x4ec0))
		जाओ nonrecoverable;
	अगर ((nip >= 0xf80 && nip < 0xfa0) || (nip >= 0x4f80 && nip < 0x4fa0))
		जाओ nonrecoverable;

	/* Trampoline code runs un-relocated so subtract kbase. */
	अगर (nip >= (अचिन्हित दीर्घ)(start_real_trampolines - kbase) &&
			nip < (अचिन्हित दीर्घ)(end_real_trampolines - kbase))
		जाओ nonrecoverable;
	अगर (nip >= (अचिन्हित दीर्घ)(start_virt_trampolines - kbase) &&
			nip < (अचिन्हित दीर्घ)(end_virt_trampolines - kbase))
		जाओ nonrecoverable;
	वापस;

nonrecoverable:
	regs->msr &= ~MSR_RI;
#पूर्ण_अगर
पूर्ण
DEFINE_INTERRUPT_HANDLER_NMI(प्रणाली_reset_exception)
अणु
	अचिन्हित दीर्घ hsrr0, hsrr1;
	bool saved_hsrrs = false;

	/*
	 * System reset can पूर्णांकerrupt code where HSRRs are live and MSR[RI]=1.
	 * The प्रणाली reset पूर्णांकerrupt itself may clobber HSRRs (e.g., to call
	 * OPAL), so save them here and restore them beक्रमe वापसing.
	 *
	 * Machine checks करोn't need to save HSRRs, as the real mode handler
	 * is careful to aव्योम them, and the regular handler is not delivered
	 * as an NMI.
	 */
	अगर (cpu_has_feature(CPU_FTR_HVMODE)) अणु
		hsrr0 = mfspr(SPRN_HSRR0);
		hsrr1 = mfspr(SPRN_HSRR1);
		saved_hsrrs = true;
	पूर्ण

	hv_nmi_check_nonrecoverable(regs);

	__this_cpu_inc(irq_stat.sreset_irqs);

	/* See अगर any machine dependent calls */
	अगर (ppc_md.प्रणाली_reset_exception) अणु
		अगर (ppc_md.प्रणाली_reset_exception(regs))
			जाओ out;
	पूर्ण

	अगर (debugger(regs))
		जाओ out;

	kmsg_dump(KMSG_DUMP_OOPS);
	/*
	 * A प्रणाली reset is a request to dump, so we always send
	 * it through the crashdump code (अगर fadump or kdump are
	 * रेजिस्टरed).
	 */
	crash_fadump(regs, "System Reset");

	crash_kexec(regs);

	/*
	 * We aren't the primary crash CPU. We need to send it
	 * to a holding pattern to aव्योम it ending up in the panic
	 * code.
	 */
	crash_kexec_secondary(regs);

	/*
	 * No debugger or crash dump रेजिस्टरed, prपूर्णांक logs then
	 * panic.
	 */
	die("System Reset", regs, SIGABRT);

	mdelay(2*MSEC_PER_SEC); /* Wait a little जबतक क्रम others to prपूर्णांक */
	add_taपूर्णांक(TAINT_DIE, LOCKDEP_NOW_UNRELIABLE);
	nmi_panic(regs, "System Reset");

out:
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	BUG_ON(get_paca()->in_nmi == 0);
	अगर (get_paca()->in_nmi > 1)
		die("Unrecoverable nested System Reset", regs, SIGABRT);
#पूर्ण_अगर
	/* Must die अगर the पूर्णांकerrupt is not recoverable */
	अगर (!(regs->msr & MSR_RI)) अणु
		/* For the reason explained in die_mce, nmi_निकास beक्रमe die */
		nmi_निकास();
		die("Unrecoverable System Reset", regs, SIGABRT);
	पूर्ण

	अगर (saved_hsrrs) अणु
		mtspr(SPRN_HSRR0, hsrr0);
		mtspr(SPRN_HSRR1, hsrr1);
	पूर्ण

	/* What should we करो here? We could issue a shutकरोwn or hard reset. */

	वापस 0;
पूर्ण

/*
 * I/O accesses can cause machine checks on घातermacs.
 * Check अगर the NIP corresponds to the address of a sync
 * inकाष्ठाion क्रम which there is an entry in the exception
 * table.
 *  -- paulus.
 */
अटल अंतरभूत पूर्णांक check_io_access(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_PPC32
	अचिन्हित दीर्घ msr = regs->msr;
	स्थिर काष्ठा exception_table_entry *entry;
	अचिन्हित पूर्णांक *nip = (अचिन्हित पूर्णांक *)regs->nip;

	अगर (((msr & 0xffff0000) == 0 || (msr & (0x80000 | 0x40000)))
	    && (entry = search_exception_tables(regs->nip)) != शून्य) अणु
		/*
		 * Check that it's a sync inकाष्ठाion, or somewhere
		 * in the twi; isync; nop sequence that inb/inw/inl uses.
		 * As the address is in the exception table
		 * we should be able to पढ़ो the instr there.
		 * For the debug message, we look at the preceding
		 * load or store.
		 */
		अगर (*nip == PPC_INST_NOP)
			nip -= 2;
		अन्यथा अगर (*nip == PPC_INST_ISYNC)
			--nip;
		अगर (*nip == PPC_INST_SYNC || (*nip >> 26) == OP_TRAP) अणु
			अचिन्हित पूर्णांक rb;

			--nip;
			rb = (*nip >> 11) & 0x1f;
			prपूर्णांकk(KERN_DEBUG "%s bad port %lx at %p\n",
			       (*nip & 0x100)? "OUT to": "IN from",
			       regs->gpr[rb] - _IO_BASE, nip);
			regs->msr |= MSR_RI;
			regs->nip = extable_fixup(entry);
			वापस 1;
		पूर्ण
	पूर्ण
#पूर्ण_अगर /* CONFIG_PPC32 */
	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
/* On 4xx, the reason क्रम the machine check or program exception
   is in the ESR. */
#घोषणा get_reason(regs)	((regs)->dsisr)
#घोषणा REASON_FP		ESR_FP
#घोषणा REASON_ILLEGAL		(ESR_PIL | ESR_PUO)
#घोषणा REASON_PRIVILEGED	ESR_PPR
#घोषणा REASON_TRAP		ESR_PTR
#घोषणा REASON_PREFIXED		0
#घोषणा REASON_BOUNDARY		0

/* single-step stuff */
#घोषणा single_stepping(regs)	(current->thपढ़ो.debug.dbcr0 & DBCR0_IC)
#घोषणा clear_single_step(regs)	(current->thपढ़ो.debug.dbcr0 &= ~DBCR0_IC)
#घोषणा clear_br_trace(regs)	करो अणुपूर्ण जबतक(0)
#अन्यथा
/* On non-4xx, the reason क्रम the machine check or program
   exception is in the MSR. */
#घोषणा get_reason(regs)	((regs)->msr)
#घोषणा REASON_TM		SRR1_PROGTM
#घोषणा REASON_FP		SRR1_PROGFPE
#घोषणा REASON_ILLEGAL		SRR1_PROGILL
#घोषणा REASON_PRIVILEGED	SRR1_PROGPRIV
#घोषणा REASON_TRAP		SRR1_PROGTRAP
#घोषणा REASON_PREFIXED		SRR1_PREFIXED
#घोषणा REASON_BOUNDARY		SRR1_BOUNDARY

#घोषणा single_stepping(regs)	((regs)->msr & MSR_SE)
#घोषणा clear_single_step(regs)	((regs)->msr &= ~MSR_SE)
#घोषणा clear_br_trace(regs)	((regs)->msr &= ~MSR_BE)
#पूर्ण_अगर

#घोषणा inst_length(reason)	(((reason) & REASON_PREFIXED) ? 8 : 4)

#अगर defined(CONFIG_E500)
पूर्णांक machine_check_e500mc(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ mcsr = mfspr(SPRN_MCSR);
	अचिन्हित दीर्घ pvr = mfspr(SPRN_PVR);
	अचिन्हित दीर्घ reason = mcsr;
	पूर्णांक recoverable = 1;

	अगर (reason & MCSR_LD) अणु
		recoverable = fsl_rio_mcheck_exception(regs);
		अगर (recoverable == 1)
			जाओ silent_out;
	पूर्ण

	prपूर्णांकk("Machine check in kernel mode.\n");
	prपूर्णांकk("Caused by (from MCSR=%lx): ", reason);

	अगर (reason & MCSR_MCP)
		pr_cont("Machine Check Signal\n");

	अगर (reason & MCSR_ICPERR) अणु
		pr_cont("Instruction Cache Parity Error\n");

		/*
		 * This is recoverable by invalidating the i-cache.
		 */
		mtspr(SPRN_L1CSR1, mfspr(SPRN_L1CSR1) | L1CSR1_ICFI);
		जबतक (mfspr(SPRN_L1CSR1) & L1CSR1_ICFI)
			;

		/*
		 * This will generally be accompanied by an inकाष्ठाion
		 * fetch error report -- only treat MCSR_IF as fatal
		 * अगर it wasn't due to an L1 parity error.
		 */
		reason &= ~MCSR_IF;
	पूर्ण

	अगर (reason & MCSR_DCPERR_MC) अणु
		pr_cont("Data Cache Parity Error\n");

		/*
		 * In ग_लिखो shaकरोw mode we स्वतः-recover from the error, but it
		 * may still get logged and cause a machine check.  We should
		 * only treat the non-ग_लिखो shaकरोw हाल as non-recoverable.
		 */
		/* On e6500 core, L1 DCWS (Data cache ग_लिखो shaकरोw mode) bit
		 * is not implemented but L1 data cache always runs in ग_लिखो
		 * shaकरोw mode. Hence on data cache parity errors HW will
		 * स्वतःmatically invalidate the L1 Data Cache.
		 */
		अगर (PVR_VER(pvr) != PVR_VER_E6500) अणु
			अगर (!(mfspr(SPRN_L1CSR2) & L1CSR2_DCWS))
				recoverable = 0;
		पूर्ण
	पूर्ण

	अगर (reason & MCSR_L2MMU_MHIT) अणु
		pr_cont("Hit on multiple TLB entries\n");
		recoverable = 0;
	पूर्ण

	अगर (reason & MCSR_NMI)
		pr_cont("Non-maskable interrupt\n");

	अगर (reason & MCSR_IF) अणु
		pr_cont("Instruction Fetch Error Report\n");
		recoverable = 0;
	पूर्ण

	अगर (reason & MCSR_LD) अणु
		pr_cont("Load Error Report\n");
		recoverable = 0;
	पूर्ण

	अगर (reason & MCSR_ST) अणु
		pr_cont("Store Error Report\n");
		recoverable = 0;
	पूर्ण

	अगर (reason & MCSR_LDG) अणु
		pr_cont("Guarded Load Error Report\n");
		recoverable = 0;
	पूर्ण

	अगर (reason & MCSR_TLBSYNC)
		pr_cont("Simultaneous tlbsync operations\n");

	अगर (reason & MCSR_BSL2_ERR) अणु
		pr_cont("Level 2 Cache Error\n");
		recoverable = 0;
	पूर्ण

	अगर (reason & MCSR_MAV) अणु
		u64 addr;

		addr = mfspr(SPRN_MCAR);
		addr |= (u64)mfspr(SPRN_MCARU) << 32;

		pr_cont("Machine Check %s Address: %#llx\n",
		       reason & MCSR_MEA ? "Effective" : "Physical", addr);
	पूर्ण

silent_out:
	mtspr(SPRN_MCSR, mcsr);
	वापस mfspr(SPRN_MCSR) == 0 && recoverable;
पूर्ण

पूर्णांक machine_check_e500(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ reason = mfspr(SPRN_MCSR);

	अगर (reason & MCSR_BUS_RBERR) अणु
		अगर (fsl_rio_mcheck_exception(regs))
			वापस 1;
		अगर (fsl_pci_mcheck_exception(regs))
			वापस 1;
	पूर्ण

	prपूर्णांकk("Machine check in kernel mode.\n");
	prपूर्णांकk("Caused by (from MCSR=%lx): ", reason);

	अगर (reason & MCSR_MCP)
		pr_cont("Machine Check Signal\n");
	अगर (reason & MCSR_ICPERR)
		pr_cont("Instruction Cache Parity Error\n");
	अगर (reason & MCSR_DCP_PERR)
		pr_cont("Data Cache Push Parity Error\n");
	अगर (reason & MCSR_DCPERR)
		pr_cont("Data Cache Parity Error\n");
	अगर (reason & MCSR_BUS_IAERR)
		pr_cont("Bus - Instruction Address Error\n");
	अगर (reason & MCSR_BUS_RAERR)
		pr_cont("Bus - Read Address Error\n");
	अगर (reason & MCSR_BUS_WAERR)
		pr_cont("Bus - Write Address Error\n");
	अगर (reason & MCSR_BUS_IBERR)
		pr_cont("Bus - Instruction Data Error\n");
	अगर (reason & MCSR_BUS_RBERR)
		pr_cont("Bus - Read Data Bus Error\n");
	अगर (reason & MCSR_BUS_WBERR)
		pr_cont("Bus - Write Data Bus Error\n");
	अगर (reason & MCSR_BUS_IPERR)
		pr_cont("Bus - Instruction Parity Error\n");
	अगर (reason & MCSR_BUS_RPERR)
		pr_cont("Bus - Read Parity Error\n");

	वापस 0;
पूर्ण

पूर्णांक machine_check_generic(काष्ठा pt_regs *regs)
अणु
	वापस 0;
पूर्ण
#या_अगर defined(CONFIG_PPC32)
पूर्णांक machine_check_generic(काष्ठा pt_regs *regs)
अणु
	अचिन्हित दीर्घ reason = regs->msr;

	prपूर्णांकk("Machine check in kernel mode.\n");
	prपूर्णांकk("Caused by (from SRR1=%lx): ", reason);
	चयन (reason & 0x601F0000) अणु
	हाल 0x80000:
		pr_cont("Machine check signal\n");
		अवरोध;
	हाल 0x40000:
	हाल 0x140000:	/* 7450 MSS error and TEA */
		pr_cont("Transfer error ack signal\n");
		अवरोध;
	हाल 0x20000:
		pr_cont("Data parity error signal\n");
		अवरोध;
	हाल 0x10000:
		pr_cont("Address parity error signal\n");
		अवरोध;
	हाल 0x20000000:
		pr_cont("L1 Data Cache error\n");
		अवरोध;
	हाल 0x40000000:
		pr_cont("L1 Instruction Cache error\n");
		अवरोध;
	हाल 0x00100000:
		pr_cont("L2 data cache parity error\n");
		अवरोध;
	शेष:
		pr_cont("Unknown values in msr\n");
	पूर्ण
	वापस 0;
पूर्ण
#पूर्ण_अगर /* everything अन्यथा */

व्योम die_mce(स्थिर अक्षर *str, काष्ठा pt_regs *regs, दीर्घ err)
अणु
	/*
	 * The machine check wants to समाप्त the पूर्णांकerrupted context, but
	 * करो_निकास() checks क्रम in_पूर्णांकerrupt() and panics in that हाल, so
	 * निकास the irq/nmi beक्रमe calling die.
	 */
	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64))
		irq_निकास();
	अन्यथा
		nmi_निकास();
	die(str, regs, err);
पूर्ण

/*
 * BOOK3S_64 करोes not call this handler as a non-maskable पूर्णांकerrupt
 * (it uses its own early real-mode handler to handle the MCE proper
 * and then उठाओs irq_work to call this handler when पूर्णांकerrupts are
 * enabled).
 */
#अगर_घोषित CONFIG_PPC_BOOK3S_64
DEFINE_INTERRUPT_HANDLER_ASYNC(machine_check_exception)
#अन्यथा
DEFINE_INTERRUPT_HANDLER_NMI(machine_check_exception)
#पूर्ण_अगर
अणु
	पूर्णांक recover = 0;

	__this_cpu_inc(irq_stat.mce_exceptions);

	add_taपूर्णांक(TAINT_MACHINE_CHECK, LOCKDEP_NOW_UNRELIABLE);

	/* See अगर any machine dependent calls. In theory, we would want
	 * to call the CPU first, and call the ppc_md. one अगर the CPU
	 * one वापसs a positive number. However there is existing code
	 * that assumes the board माला_लो a first chance, so let's keep it
	 * that way क्रम now and fix things later. --BenH.
	 */
	अगर (ppc_md.machine_check_exception)
		recover = ppc_md.machine_check_exception(regs);
	अन्यथा अगर (cur_cpu_spec->machine_check)
		recover = cur_cpu_spec->machine_check(regs);

	अगर (recover > 0)
		जाओ bail;

	अगर (debugger_fault_handler(regs))
		जाओ bail;

	अगर (check_io_access(regs))
		जाओ bail;

	die_mce("Machine check", regs, SIGBUS);

bail:
	/* Must die अगर the पूर्णांकerrupt is not recoverable */
	अगर (!(regs->msr & MSR_RI))
		die_mce("Unrecoverable Machine check", regs, SIGBUS);

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	वापस;
#अन्यथा
	वापस 0;
#पूर्ण_अगर
पूर्ण

DEFINE_INTERRUPT_HANDLER(SMIException) /* async? */
अणु
	die("System Management Interrupt", regs, SIGABRT);
पूर्ण

#अगर_घोषित CONFIG_VSX
अटल व्योम p9_hmi_special_emu(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक ra, rb, t, i, sel, instr, rc;
	स्थिर व्योम __user *addr;
	u8 vbuf[16] __aligned(16), *vdst;
	अचिन्हित दीर्घ ea, msr, msr_mask;
	bool swap;

	अगर (__get_user(instr, (अचिन्हित पूर्णांक __user *)regs->nip))
		वापस;

	/*
	 * lxvb16x	opcode: 0x7c0006d8
	 * lxvd2x	opcode: 0x7c000698
	 * lxvh8x	opcode: 0x7c000658
	 * lxvw4x	opcode: 0x7c000618
	 */
	अगर ((instr & 0xfc00073e) != 0x7c000618) अणु
		pr_devel("HMI vec emu: not vector CI %i:%s[%d] nip=%016lx"
			 " instr=%08x\n",
			 smp_processor_id(), current->comm, current->pid,
			 regs->nip, instr);
		वापस;
	पूर्ण

	/* Grab vector रेजिस्टरs पूर्णांकo the task काष्ठा */
	msr = regs->msr; /* Grab msr beक्रमe we flush the bits */
	flush_vsx_to_thपढ़ो(current);
	enable_kernel_altivec();

	/*
	 * Is userspace running with a dअगरferent endian (this is rare but
	 * not impossible)
	 */
	swap = (msr & MSR_LE) != (MSR_KERNEL & MSR_LE);

	/* Decode the inकाष्ठाion */
	ra = (instr >> 16) & 0x1f;
	rb = (instr >> 11) & 0x1f;
	t = (instr >> 21) & 0x1f;
	अगर (instr & 1)
		vdst = (u8 *)&current->thपढ़ो.vr_state.vr[t];
	अन्यथा
		vdst = (u8 *)&current->thपढ़ो.fp_state.fpr[t][0];

	/* Grab the vector address */
	ea = regs->gpr[rb] + (ra ? regs->gpr[ra] : 0);
	अगर (is_32bit_task())
		ea &= 0xfffffffful;
	addr = (__क्रमce स्थिर व्योम __user *)ea;

	/* Check it */
	अगर (!access_ok(addr, 16)) अणु
		pr_devel("HMI vec emu: bad access %i:%s[%d] nip=%016lx"
			 " instr=%08x addr=%016lx\n",
			 smp_processor_id(), current->comm, current->pid,
			 regs->nip, instr, (अचिन्हित दीर्घ)addr);
		वापस;
	पूर्ण

	/* Read the vector */
	rc = 0;
	अगर ((अचिन्हित दीर्घ)addr & 0xfUL)
		/* unaligned हाल */
		rc = __copy_from_user_inatomic(vbuf, addr, 16);
	अन्यथा
		__get_user_atomic_128_aligned(vbuf, addr, rc);
	अगर (rc) अणु
		pr_devel("HMI vec emu: page fault %i:%s[%d] nip=%016lx"
			 " instr=%08x addr=%016lx\n",
			 smp_processor_id(), current->comm, current->pid,
			 regs->nip, instr, (अचिन्हित दीर्घ)addr);
		वापस;
	पूर्ण

	pr_devel("HMI vec emu: emulated vector CI %i:%s[%d] nip=%016lx"
		 " instr=%08x addr=%016lx\n",
		 smp_processor_id(), current->comm, current->pid, regs->nip,
		 instr, (अचिन्हित दीर्घ) addr);

	/* Grab inकाष्ठाion "selector" */
	sel = (instr >> 6) & 3;

	/*
	 * Check to make sure the facility is actually enabled. This
	 * could happen अगर we get a false positive hit.
	 *
	 * lxvd2x/lxvw4x always check MSR VSX sel = 0,2
	 * lxvh8x/lxvb16x check MSR VSX or VEC depending on VSR used sel = 1,3
	 */
	msr_mask = MSR_VSX;
	अगर ((sel & 1) && (instr & 1)) /* lxvh8x & lxvb16x + VSR >= 32 */
		msr_mask = MSR_VEC;
	अगर (!(msr & msr_mask)) अणु
		pr_devel("HMI vec emu: MSR fac clear %i:%s[%d] nip=%016lx"
			 " instr=%08x msr:%016lx\n",
			 smp_processor_id(), current->comm, current->pid,
			 regs->nip, instr, msr);
		वापस;
	पूर्ण

	/* Do logging here beक्रमe we modअगरy sel based on endian */
	चयन (sel) अणु
	हाल 0:	/* lxvw4x */
		PPC_WARN_EMULATED(lxvw4x, regs);
		अवरोध;
	हाल 1: /* lxvh8x */
		PPC_WARN_EMULATED(lxvh8x, regs);
		अवरोध;
	हाल 2: /* lxvd2x */
		PPC_WARN_EMULATED(lxvd2x, regs);
		अवरोध;
	हाल 3: /* lxvb16x */
		PPC_WARN_EMULATED(lxvb16x, regs);
		अवरोध;
	पूर्ण

#अगर_घोषित __LITTLE_ENDIAN__
	/*
	 * An LE kernel stores the vector in the task काष्ठा as an LE
	 * byte array (effectively swapping both the components and
	 * the content of the components). Those inकाष्ठाions expect
	 * the components to reमुख्य in ascending address order, so we
	 * swap them back.
	 *
	 * If we are running a BE user space, the expectation is that
	 * of a simple स_नकल, so क्रमcing the emulation to look like
	 * a lxvb16x should करो the trick.
	 */
	अगर (swap)
		sel = 3;

	चयन (sel) अणु
	हाल 0:	/* lxvw4x */
		क्रम (i = 0; i < 4; i++)
			((u32 *)vdst)[i] = ((u32 *)vbuf)[3-i];
		अवरोध;
	हाल 1: /* lxvh8x */
		क्रम (i = 0; i < 8; i++)
			((u16 *)vdst)[i] = ((u16 *)vbuf)[7-i];
		अवरोध;
	हाल 2: /* lxvd2x */
		क्रम (i = 0; i < 2; i++)
			((u64 *)vdst)[i] = ((u64 *)vbuf)[1-i];
		अवरोध;
	हाल 3: /* lxvb16x */
		क्रम (i = 0; i < 16; i++)
			vdst[i] = vbuf[15-i];
		अवरोध;
	पूर्ण
#अन्यथा /* __LITTLE_ENDIAN__ */
	/* On a big endian kernel, a BE userspace only needs a स_नकल */
	अगर (!swap)
		sel = 3;

	/* Otherwise, we need to swap the content of the components */
	चयन (sel) अणु
	हाल 0:	/* lxvw4x */
		क्रम (i = 0; i < 4; i++)
			((u32 *)vdst)[i] = cpu_to_le32(((u32 *)vbuf)[i]);
		अवरोध;
	हाल 1: /* lxvh8x */
		क्रम (i = 0; i < 8; i++)
			((u16 *)vdst)[i] = cpu_to_le16(((u16 *)vbuf)[i]);
		अवरोध;
	हाल 2: /* lxvd2x */
		क्रम (i = 0; i < 2; i++)
			((u64 *)vdst)[i] = cpu_to_le64(((u64 *)vbuf)[i]);
		अवरोध;
	हाल 3: /* lxvb16x */
		स_नकल(vdst, vbuf, 16);
		अवरोध;
	पूर्ण
#पूर्ण_अगर /* !__LITTLE_ENDIAN__ */

	/* Go to next inकाष्ठाion */
	regs->nip += 4;
पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

DEFINE_INTERRUPT_HANDLER_ASYNC(handle_hmi_exception)
अणु
	काष्ठा pt_regs *old_regs;

	old_regs = set_irq_regs(regs);

#अगर_घोषित CONFIG_VSX
	/* Real mode flagged P9 special emu is needed */
	अगर (local_paca->hmi_p9_special_emu) अणु
		local_paca->hmi_p9_special_emu = 0;

		/*
		 * We करोn't want to take page faults जबतक करोing the
		 * emulation, we just replay the inकाष्ठाion अगर necessary.
		 */
		pagefault_disable();
		p9_hmi_special_emu(regs);
		pagefault_enable();
	पूर्ण
#पूर्ण_अगर /* CONFIG_VSX */

	अगर (ppc_md.handle_hmi_exception)
		ppc_md.handle_hmi_exception(regs);

	set_irq_regs(old_regs);
पूर्ण

DEFINE_INTERRUPT_HANDLER(unknown_exception)
अणु
	prपूर्णांकk("Bad trap at PC: %lx, SR: %lx, vector=%lx\n",
	       regs->nip, regs->msr, regs->trap);

	_exception(SIGTRAP, regs, TRAP_UNK, 0);
पूर्ण

DEFINE_INTERRUPT_HANDLER_ASYNC(unknown_async_exception)
अणु
	prपूर्णांकk("Bad trap at PC: %lx, SR: %lx, vector=%lx\n",
	       regs->nip, regs->msr, regs->trap);

	_exception(SIGTRAP, regs, TRAP_UNK, 0);
पूर्ण

DEFINE_INTERRUPT_HANDLER_NMI(unknown_nmi_exception)
अणु
	prपूर्णांकk("Bad trap at PC: %lx, SR: %lx, vector=%lx\n",
	       regs->nip, regs->msr, regs->trap);

	_exception(SIGTRAP, regs, TRAP_UNK, 0);

	वापस 0;
पूर्ण

DEFINE_INTERRUPT_HANDLER(inकाष्ठाion_अवरोधpoपूर्णांक_exception)
अणु
	अगर (notअगरy_die(DIE_IABR_MATCH, "iabr_match", regs, 5,
					5, SIGTRAP) == NOTIFY_STOP)
		वापस;
	अगर (debugger_iabr_match(regs))
		वापस;
	_exception(SIGTRAP, regs, TRAP_BRKPT, regs->nip);
पूर्ण

DEFINE_INTERRUPT_HANDLER(RunModeException)
अणु
	_exception(SIGTRAP, regs, TRAP_UNK, 0);
पूर्ण

DEFINE_INTERRUPT_HANDLER(single_step_exception)
अणु
	clear_single_step(regs);
	clear_br_trace(regs);

	अगर (kprobe_post_handler(regs))
		वापस;

	अगर (notअगरy_die(DIE_SSTEP, "single_step", regs, 5,
					5, SIGTRAP) == NOTIFY_STOP)
		वापस;
	अगर (debugger_sstep(regs))
		वापस;

	_exception(SIGTRAP, regs, TRAP_TRACE, regs->nip);
पूर्ण

/*
 * After we have successfully emulated an inकाष्ठाion, we have to
 * check अगर the inकाष्ठाion was being single-stepped, and अगर so,
 * pretend we got a single-step exception.  This was poपूर्णांकed out
 * by Kumar Gala.  -- paulus
 */
अटल व्योम emulate_single_step(काष्ठा pt_regs *regs)
अणु
	अगर (single_stepping(regs))
		single_step_exception(regs);
पूर्ण

अटल अंतरभूत पूर्णांक __parse_fpscr(अचिन्हित दीर्घ fpscr)
अणु
	पूर्णांक ret = FPE_FLTUNK;

	/* Invalid operation */
	अगर ((fpscr & FPSCR_VE) && (fpscr & FPSCR_VX))
		ret = FPE_FLTINV;

	/* Overflow */
	अन्यथा अगर ((fpscr & FPSCR_OE) && (fpscr & FPSCR_OX))
		ret = FPE_FLTOVF;

	/* Underflow */
	अन्यथा अगर ((fpscr & FPSCR_UE) && (fpscr & FPSCR_UX))
		ret = FPE_FLTUND;

	/* Divide by zero */
	अन्यथा अगर ((fpscr & FPSCR_ZE) && (fpscr & FPSCR_ZX))
		ret = FPE_FLTDIV;

	/* Inexact result */
	अन्यथा अगर ((fpscr & FPSCR_XE) && (fpscr & FPSCR_XX))
		ret = FPE_FLTRES;

	वापस ret;
पूर्ण

अटल व्योम parse_fpe(काष्ठा pt_regs *regs)
अणु
	पूर्णांक code = 0;

	flush_fp_to_thपढ़ो(current);

#अगर_घोषित CONFIG_PPC_FPU_REGS
	code = __parse_fpscr(current->thपढ़ो.fp_state.fpscr);
#पूर्ण_अगर

	_exception(संक_भ_त्रुटि, regs, code, regs->nip);
पूर्ण

/*
 * Illegal inकाष्ठाion emulation support.  Originally written to
 * provide the PVR to user applications using the mfspr rd, PVR.
 * Return non-zero अगर we can't emulate, or -EFAULT अगर the associated
 * memory access caused an access fault.  Return zero on success.
 *
 * There are a couple of ways to करो this, either "decode" the inकाष्ठाion
 * or directly match lots of bits.  In this हाल, matching lots of
 * bits is faster and easier.
 *
 */
अटल पूर्णांक emulate_string_inst(काष्ठा pt_regs *regs, u32 instword)
अणु
	u8 rT = (instword >> 21) & 0x1f;
	u8 rA = (instword >> 16) & 0x1f;
	u8 NB_RB = (instword >> 11) & 0x1f;
	u32 num_bytes;
	अचिन्हित दीर्घ EA;
	पूर्णांक pos = 0;

	/* Early out अगर we are an invalid क्रमm of lswx */
	अगर ((instword & PPC_INST_STRING_MASK) == PPC_INST_LSWX)
		अगर ((rT == rA) || (rT == NB_RB))
			वापस -EINVAL;

	EA = (rA == 0) ? 0 : regs->gpr[rA];

	चयन (instword & PPC_INST_STRING_MASK) अणु
		हाल PPC_INST_LSWX:
		हाल PPC_INST_STSWX:
			EA += NB_RB;
			num_bytes = regs->xer & 0x7f;
			अवरोध;
		हाल PPC_INST_LSWI:
		हाल PPC_INST_STSWI:
			num_bytes = (NB_RB == 0) ? 32 : NB_RB;
			अवरोध;
		शेष:
			वापस -EINVAL;
	पूर्ण

	जबतक (num_bytes != 0)
	अणु
		u8 val;
		u32 shअगरt = 8 * (3 - (pos & 0x3));

		/* अगर process is 32-bit, clear upper 32 bits of EA */
		अगर ((regs->msr & MSR_64BIT) == 0)
			EA &= 0xFFFFFFFF;

		चयन ((instword & PPC_INST_STRING_MASK)) अणु
			हाल PPC_INST_LSWX:
			हाल PPC_INST_LSWI:
				अगर (get_user(val, (u8 __user *)EA))
					वापस -EFAULT;
				/* first समय updating this reg,
				 * zero it out */
				अगर (pos == 0)
					regs->gpr[rT] = 0;
				regs->gpr[rT] |= val << shअगरt;
				अवरोध;
			हाल PPC_INST_STSWI:
			हाल PPC_INST_STSWX:
				val = regs->gpr[rT] >> shअगरt;
				अगर (put_user(val, (u8 __user *)EA))
					वापस -EFAULT;
				अवरोध;
		पूर्ण
		/* move EA to next address */
		EA += 1;
		num_bytes--;

		/* manage our position within the रेजिस्टर */
		अगर (++pos == 4) अणु
			pos = 0;
			अगर (++rT == 32)
				rT = 0;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक emulate_popcntb_inst(काष्ठा pt_regs *regs, u32 instword)
अणु
	u32 ra,rs;
	अचिन्हित दीर्घ पंचांगp;

	ra = (instword >> 16) & 0x1f;
	rs = (instword >> 21) & 0x1f;

	पंचांगp = regs->gpr[rs];
	पंचांगp = पंचांगp - ((पंचांगp >> 1) & 0x5555555555555555ULL);
	पंचांगp = (पंचांगp & 0x3333333333333333ULL) + ((पंचांगp >> 2) & 0x3333333333333333ULL);
	पंचांगp = (पंचांगp + (पंचांगp >> 4)) & 0x0f0f0f0f0f0f0f0fULL;
	regs->gpr[ra] = पंचांगp;

	वापस 0;
पूर्ण

अटल पूर्णांक emulate_isel(काष्ठा pt_regs *regs, u32 instword)
अणु
	u8 rT = (instword >> 21) & 0x1f;
	u8 rA = (instword >> 16) & 0x1f;
	u8 rB = (instword >> 11) & 0x1f;
	u8 BC = (instword >> 6) & 0x1f;
	u8 bit;
	अचिन्हित दीर्घ पंचांगp;

	पंचांगp = (rA == 0) ? 0 : regs->gpr[rA];
	bit = (regs->ccr >> (31 - BC)) & 0x1;

	regs->gpr[rT] = bit ? पंचांगp : regs->gpr[rB];

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
अटल अंतरभूत bool पंचांग_पात_check(काष्ठा pt_regs *regs, पूर्णांक cause)
अणु
        /* If we're emulating a load/store in an active transaction, we cannot
         * emulate it as the kernel operates in transaction suspended context.
         * We need to पात the transaction.  This creates a persistent TM
         * पात so tell the user what caused it with a new code.
	 */
	अगर (MSR_TM_TRANSACTIONAL(regs->msr)) अणु
		पंचांग_enable();
		पंचांग_पात(cause);
		वापस true;
	पूर्ण
	वापस false;
पूर्ण
#अन्यथा
अटल अंतरभूत bool पंचांग_पात_check(काष्ठा pt_regs *regs, पूर्णांक reason)
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक emulate_inकाष्ठाion(काष्ठा pt_regs *regs)
अणु
	u32 instword;
	u32 rd;

	अगर (!user_mode(regs))
		वापस -EINVAL;

	अगर (get_user(instword, (u32 __user *)(regs->nip)))
		वापस -EFAULT;

	/* Emulate the mfspr rD, PVR. */
	अगर ((instword & PPC_INST_MFSPR_PVR_MASK) == PPC_INST_MFSPR_PVR) अणु
		PPC_WARN_EMULATED(mfpvr, regs);
		rd = (instword >> 21) & 0x1f;
		regs->gpr[rd] = mfspr(SPRN_PVR);
		वापस 0;
	पूर्ण

	/* Emulating the dcba insn is just a no-op.  */
	अगर ((instword & PPC_INST_DCBA_MASK) == PPC_INST_DCBA) अणु
		PPC_WARN_EMULATED(dcba, regs);
		वापस 0;
	पूर्ण

	/* Emulate the mcrxr insn.  */
	अगर ((instword & PPC_INST_MCRXR_MASK) == PPC_INST_MCRXR) अणु
		पूर्णांक shअगरt = (instword >> 21) & 0x1c;
		अचिन्हित दीर्घ msk = 0xf0000000UL >> shअगरt;

		PPC_WARN_EMULATED(mcrxr, regs);
		regs->ccr = (regs->ccr & ~msk) | ((regs->xer >> shअगरt) & msk);
		regs->xer &= ~0xf0000000UL;
		वापस 0;
	पूर्ण

	/* Emulate load/store string insn. */
	अगर ((instword & PPC_INST_STRING_GEN_MASK) == PPC_INST_STRING) अणु
		अगर (पंचांग_पात_check(regs,
				   TM_CAUSE_EMULATE | TM_CAUSE_PERSISTENT))
			वापस -EINVAL;
		PPC_WARN_EMULATED(string, regs);
		वापस emulate_string_inst(regs, instword);
	पूर्ण

	/* Emulate the popcntb (Population Count Bytes) inकाष्ठाion. */
	अगर ((instword & PPC_INST_POPCNTB_MASK) == PPC_INST_POPCNTB) अणु
		PPC_WARN_EMULATED(popcntb, regs);
		वापस emulate_popcntb_inst(regs, instword);
	पूर्ण

	/* Emulate isel (Integer Select) inकाष्ठाion */
	अगर ((instword & PPC_INST_ISEL_MASK) == PPC_INST_ISEL) अणु
		PPC_WARN_EMULATED(isel, regs);
		वापस emulate_isel(regs, instword);
	पूर्ण

	/* Emulate sync inकाष्ठाion variants */
	अगर ((instword & PPC_INST_SYNC_MASK) == PPC_INST_SYNC) अणु
		PPC_WARN_EMULATED(sync, regs);
		यंत्र अस्थिर("sync");
		वापस 0;
	पूर्ण

#अगर_घोषित CONFIG_PPC64
	/* Emulate the mfspr rD, DSCR. */
	अगर ((((instword & PPC_INST_MFSPR_DSCR_USER_MASK) ==
		PPC_INST_MFSPR_DSCR_USER) ||
	     ((instword & PPC_INST_MFSPR_DSCR_MASK) ==
		PPC_INST_MFSPR_DSCR)) &&
			cpu_has_feature(CPU_FTR_DSCR)) अणु
		PPC_WARN_EMULATED(mfdscr, regs);
		rd = (instword >> 21) & 0x1f;
		regs->gpr[rd] = mfspr(SPRN_DSCR);
		वापस 0;
	पूर्ण
	/* Emulate the mtspr DSCR, rD. */
	अगर ((((instword & PPC_INST_MTSPR_DSCR_USER_MASK) ==
		PPC_INST_MTSPR_DSCR_USER) ||
	     ((instword & PPC_INST_MTSPR_DSCR_MASK) ==
		PPC_INST_MTSPR_DSCR)) &&
			cpu_has_feature(CPU_FTR_DSCR)) अणु
		PPC_WARN_EMULATED(mtdscr, regs);
		rd = (instword >> 21) & 0x1f;
		current->thपढ़ो.dscr = regs->gpr[rd];
		current->thपढ़ो.dscr_inherit = 1;
		mtspr(SPRN_DSCR, current->thपढ़ो.dscr);
		वापस 0;
	पूर्ण
#पूर्ण_अगर

	वापस -EINVAL;
पूर्ण

पूर्णांक is_valid_bugaddr(अचिन्हित दीर्घ addr)
अणु
	वापस is_kernel_addr(addr);
पूर्ण

#अगर_घोषित CONFIG_MATH_EMULATION
अटल पूर्णांक emulate_math(काष्ठा pt_regs *regs)
अणु
	पूर्णांक ret;

	ret = करो_mathemu(regs);
	अगर (ret >= 0)
		PPC_WARN_EMULATED(math, regs);

	चयन (ret) अणु
	हाल 0:
		emulate_single_step(regs);
		वापस 0;
	हाल 1: अणु
			पूर्णांक code = 0;
			code = __parse_fpscr(current->thपढ़ो.fp_state.fpscr);
			_exception(संक_भ_त्रुटि, regs, code, regs->nip);
			वापस 0;
		पूर्ण
	हाल -EFAULT:
		_exception(संक_अंश, regs, SEGV_MAPERR, regs->nip);
		वापस 0;
	पूर्ण

	वापस -1;
पूर्ण
#अन्यथा
अटल अंतरभूत पूर्णांक emulate_math(काष्ठा pt_regs *regs) अणु वापस -1; पूर्ण
#पूर्ण_अगर

अटल व्योम करो_program_check(काष्ठा pt_regs *regs)
अणु
	अचिन्हित पूर्णांक reason = get_reason(regs);

	/* We can now get here via a FP Unavailable exception अगर the core
	 * has no FPU, in that हाल the reason flags will be 0 */

	अगर (reason & REASON_FP) अणु
		/* IEEE FP exception */
		parse_fpe(regs);
		वापस;
	पूर्ण
	अगर (reason & REASON_TRAP) अणु
		अचिन्हित दीर्घ bugaddr;
		/* Debugger is first in line to stop recursive faults in
		 * rcu_lock, notअगरy_die, or atomic_notअगरier_call_chain */
		अगर (debugger_bpt(regs))
			वापस;

		अगर (kprobe_handler(regs))
			वापस;

		/* trap exception */
		अगर (notअगरy_die(DIE_BPT, "breakpoint", regs, 5, 5, SIGTRAP)
				== NOTIFY_STOP)
			वापस;

		bugaddr = regs->nip;
		/*
		 * Fixup bugaddr क्रम BUG_ON() in real mode
		 */
		अगर (!is_kernel_addr(bugaddr) && !(regs->msr & MSR_IR))
			bugaddr += PAGE_OFFSET;

		अगर (!(regs->msr & MSR_PR) &&  /* not user-mode */
		    report_bug(bugaddr, regs) == BUG_TRAP_TYPE_WARN) अणु
			regs->nip += 4;
			वापस;
		पूर्ण
		_exception(SIGTRAP, regs, TRAP_BRKPT, regs->nip);
		वापस;
	पूर्ण
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	अगर (reason & REASON_TM) अणु
		/* This is a TM "Bad Thing Exception" program check.
		 * This occurs when:
		 * -  An rfid/hrfid/mपंचांगsrd attempts to cause an illegal
		 *    transition in TM states.
		 * -  A trechkpt is attempted when transactional.
		 * -  A treclaim is attempted when non transactional.
		 * -  A tend is illegally attempted.
		 * -  writing a TM SPR when transactional.
		 *
		 * If usermode caused this, it's करोne something illegal and
		 * माला_लो a संक_अवैध slap on the wrist.  We call it an illegal
		 * opeअक्रम to distinguish from the inकाष्ठाion just being bad
		 * (e.g. executing a 'tend' on a CPU without TM!); it's an
		 * illegal /placement/ of a valid inकाष्ठाion.
		 */
		अगर (user_mode(regs)) अणु
			_exception(संक_अवैध, regs, ILL_ILLOPN, regs->nip);
			वापस;
		पूर्ण अन्यथा अणु
			prपूर्णांकk(KERN_EMERG "Unexpected TM Bad Thing exception "
			       "at %lx (msr 0x%lx) tm_scratch=%llx\n",
			       regs->nip, regs->msr, get_paca()->पंचांग_scratch);
			die("Unrecoverable exception", regs, SIGABRT);
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/*
	 * If we took the program check in the kernel skip करोwn to sending a
	 * संक_अवैध. The subsequent हालs all relate to emulating inकाष्ठाions
	 * which we should only करो क्रम userspace. We also करो not want to enable
	 * पूर्णांकerrupts क्रम kernel faults because that might lead to further
	 * faults, and loose the context of the original exception.
	 */
	अगर (!user_mode(regs))
		जाओ sigill;

	पूर्णांकerrupt_cond_local_irq_enable(regs);

	/* (reason & REASON_ILLEGAL) would be the obvious thing here,
	 * but there seems to be a hardware bug on the 405GP (RevD)
	 * that means ESR is someबार set incorrectly - either to
	 * ESR_DST (!?) or 0.  In the process of chasing this with the
	 * hardware people - not sure अगर it can happen on any illegal
	 * inकाष्ठाion or only on FP inकाष्ठाions, whether there is a
	 * pattern to occurrences etc. -dgibson 31/Mar/2003
	 */
	अगर (!emulate_math(regs))
		वापस;

	/* Try to emulate it अगर we should. */
	अगर (reason & (REASON_ILLEGAL | REASON_PRIVILEGED)) अणु
		चयन (emulate_inकाष्ठाion(regs)) अणु
		हाल 0:
			regs->nip += 4;
			emulate_single_step(regs);
			वापस;
		हाल -EFAULT:
			_exception(संक_अंश, regs, SEGV_MAPERR, regs->nip);
			वापस;
		पूर्ण
	पूर्ण

sigill:
	अगर (reason & REASON_PRIVILEGED)
		_exception(संक_अवैध, regs, ILL_PRVOPC, regs->nip);
	अन्यथा
		_exception(संक_अवैध, regs, ILL_ILLOPC, regs->nip);

पूर्ण

DEFINE_INTERRUPT_HANDLER(program_check_exception)
अणु
	करो_program_check(regs);
पूर्ण

/*
 * This occurs when running in hypervisor mode on POWER6 or later
 * and an illegal inकाष्ठाion is encountered.
 */
DEFINE_INTERRUPT_HANDLER(emulation_assist_पूर्णांकerrupt)
अणु
	regs->msr |= REASON_ILLEGAL;
	करो_program_check(regs);
पूर्ण

DEFINE_INTERRUPT_HANDLER(alignment_exception)
अणु
	पूर्णांक sig, code, fixed = 0;
	अचिन्हित दीर्घ  reason;

	पूर्णांकerrupt_cond_local_irq_enable(regs);

	reason = get_reason(regs);
	अगर (reason & REASON_BOUNDARY) अणु
		sig = SIGBUS;
		code = BUS_ADRALN;
		जाओ bad;
	पूर्ण

	अगर (पंचांग_पात_check(regs, TM_CAUSE_ALIGNMENT | TM_CAUSE_PERSISTENT))
		वापस;

	/* we करोn't implement logging of alignment exceptions */
	अगर (!(current->thपढ़ो.align_ctl & PR_UNALIGN_SIGBUS))
		fixed = fix_alignment(regs);

	अगर (fixed == 1) अणु
		/* skip over emulated inकाष्ठाion */
		regs->nip += inst_length(reason);
		emulate_single_step(regs);
		वापस;
	पूर्ण

	/* Opeअक्रम address was bad */
	अगर (fixed == -EFAULT) अणु
		sig = संक_अंश;
		code = SEGV_ACCERR;
	पूर्ण अन्यथा अणु
		sig = SIGBUS;
		code = BUS_ADRALN;
	पूर्ण
bad:
	अगर (user_mode(regs))
		_exception(sig, regs, code, regs->dar);
	अन्यथा
		bad_page_fault(regs, sig);
पूर्ण

DEFINE_INTERRUPT_HANDLER(stack_overflow_exception)
अणु
	die("Kernel stack overflow", regs, संक_अंश);
पूर्ण

DEFINE_INTERRUPT_HANDLER(kernel_fp_unavailable_exception)
अणु
	prपूर्णांकk(KERN_EMERG "Unrecoverable FP Unavailable Exception "
			  "%lx at %lx\n", regs->trap, regs->nip);
	die("Unrecoverable FP Unavailable Exception", regs, SIGABRT);
पूर्ण

DEFINE_INTERRUPT_HANDLER(altivec_unavailable_exception)
अणु
	अगर (user_mode(regs)) अणु
		/* A user program has executed an altivec inकाष्ठाion,
		   but this kernel करोesn't support altivec. */
		_exception(संक_अवैध, regs, ILL_ILLOPC, regs->nip);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_EMERG "Unrecoverable VMX/Altivec Unavailable Exception "
			"%lx at %lx\n", regs->trap, regs->nip);
	die("Unrecoverable VMX/Altivec Unavailable Exception", regs, SIGABRT);
पूर्ण

DEFINE_INTERRUPT_HANDLER(vsx_unavailable_exception)
अणु
	अगर (user_mode(regs)) अणु
		/* A user program has executed an vsx inकाष्ठाion,
		   but this kernel करोesn't support vsx. */
		_exception(संक_अवैध, regs, ILL_ILLOPC, regs->nip);
		वापस;
	पूर्ण

	prपूर्णांकk(KERN_EMERG "Unrecoverable VSX Unavailable Exception "
			"%lx at %lx\n", regs->trap, regs->nip);
	die("Unrecoverable VSX Unavailable Exception", regs, SIGABRT);
पूर्ण

#अगर_घोषित CONFIG_PPC64
अटल व्योम पंचांग_unavailable(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	अगर (user_mode(regs)) अणु
		current->thपढ़ो.load_पंचांग++;
		regs->msr |= MSR_TM;
		पंचांग_enable();
		पंचांग_restore_sprs(&current->thपढ़ो);
		वापस;
	पूर्ण
#पूर्ण_अगर
	pr_emerg("Unrecoverable TM Unavailable Exception "
			"%lx at %lx\n", regs->trap, regs->nip);
	die("Unrecoverable TM Unavailable Exception", regs, SIGABRT);
पूर्ण

DEFINE_INTERRUPT_HANDLER(facility_unavailable_exception)
अणु
	अटल अक्षर *facility_strings[] = अणु
		[FSCR_FP_LG] = "FPU",
		[FSCR_VECVSX_LG] = "VMX/VSX",
		[FSCR_DSCR_LG] = "DSCR",
		[FSCR_PM_LG] = "PMU SPRs",
		[FSCR_BHRB_LG] = "BHRB",
		[FSCR_TM_LG] = "TM",
		[FSCR_EBB_LG] = "EBB",
		[FSCR_TAR_LG] = "TAR",
		[FSCR_MSGP_LG] = "MSGP",
		[FSCR_SCV_LG] = "SCV",
		[FSCR_PREFIX_LG] = "PREFIX",
	पूर्ण;
	अक्षर *facility = "unknown";
	u64 value;
	u32 instword, rd;
	u8 status;
	bool hv;

	hv = (TRAP(regs) == INTERRUPT_H_FAC_UNAVAIL);
	अगर (hv)
		value = mfspr(SPRN_HFSCR);
	अन्यथा
		value = mfspr(SPRN_FSCR);

	status = value >> 56;
	अगर ((hv || status >= 2) &&
	    (status < ARRAY_SIZE(facility_strings)) &&
	    facility_strings[status])
		facility = facility_strings[status];

	/* We should not have taken this पूर्णांकerrupt in kernel */
	अगर (!user_mode(regs)) अणु
		pr_emerg("Facility '%s' unavailable (%d) exception in kernel mode at %lx\n",
			 facility, status, regs->nip);
		die("Unexpected facility unavailable exception", regs, SIGABRT);
	पूर्ण

	पूर्णांकerrupt_cond_local_irq_enable(regs);

	अगर (status == FSCR_DSCR_LG) अणु
		/*
		 * User is accessing the DSCR रेजिस्टर using the problem
		 * state only SPR number (0x03) either through a mfspr or
		 * a mtspr inकाष्ठाion. If it is a ग_लिखो attempt through
		 * a mtspr, then we set the inherit bit. This also allows
		 * the user to ग_लिखो or पढ़ो the रेजिस्टर directly in the
		 * future by setting via the FSCR DSCR bit. But in हाल it
		 * is a पढ़ो DSCR attempt through a mfspr inकाष्ठाion, we
		 * just emulate the inकाष्ठाion instead. This code path will
		 * always emulate all the mfspr inकाष्ठाions till the user
		 * has attempted at least one mtspr inकाष्ठाion. This way it
		 * preserves the same behaviour when the user is accessing
		 * the DSCR through privilege level only SPR number (0x11)
		 * which is emulated through illegal inकाष्ठाion exception.
		 * We always leave HFSCR DSCR set.
		 */
		अगर (get_user(instword, (u32 __user *)(regs->nip))) अणु
			pr_err("Failed to fetch the user instruction\n");
			वापस;
		पूर्ण

		/* Write पूर्णांकo DSCR (mtspr 0x03, RS) */
		अगर ((instword & PPC_INST_MTSPR_DSCR_USER_MASK)
				== PPC_INST_MTSPR_DSCR_USER) अणु
			rd = (instword >> 21) & 0x1f;
			current->thपढ़ो.dscr = regs->gpr[rd];
			current->thपढ़ो.dscr_inherit = 1;
			current->thपढ़ो.fscr |= FSCR_DSCR;
			mtspr(SPRN_FSCR, current->thपढ़ो.fscr);
		पूर्ण

		/* Read from DSCR (mfspr RT, 0x03) */
		अगर ((instword & PPC_INST_MFSPR_DSCR_USER_MASK)
				== PPC_INST_MFSPR_DSCR_USER) अणु
			अगर (emulate_inकाष्ठाion(regs)) अणु
				pr_err("DSCR based mfspr emulation failed\n");
				वापस;
			पूर्ण
			regs->nip += 4;
			emulate_single_step(regs);
		पूर्ण
		वापस;
	पूर्ण

	अगर (status == FSCR_TM_LG) अणु
		/*
		 * If we're here then the hardware is TM aware because it
		 * generated an exception with FSRM_TM set.
		 *
		 * If cpu_has_feature(CPU_FTR_TM) is false, then either firmware
		 * told us not to करो TM, or the kernel is not built with TM
		 * support.
		 *
		 * If both of those things are true, then userspace can spam the
		 * console by triggering the prपूर्णांकk() below just by continually
		 * करोing tbegin (or any TM inकाष्ठाion). So in that हाल just
		 * send the process a संक_अवैध immediately.
		 */
		अगर (!cpu_has_feature(CPU_FTR_TM))
			जाओ out;

		पंचांग_unavailable(regs);
		वापस;
	पूर्ण

	pr_err_ratelimited("%sFacility '%s' unavailable (%d), exception at 0x%lx, MSR=%lx\n",
		hv ? "Hypervisor " : "", facility, status, regs->nip, regs->msr);

out:
	_exception(संक_अवैध, regs, ILL_ILLOPC, regs->nip);
पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM

DEFINE_INTERRUPT_HANDLER(fp_unavailable_पंचांग)
अणु
	/* Note:  This करोes not handle any kind of FP laziness. */

	TM_DEBUG("FP Unavailable trap whilst transactional at 0x%lx, MSR=%lx\n",
		 regs->nip, regs->msr);

        /* We can only have got here अगर the task started using FP after
         * beginning the transaction.  So, the transactional regs are just a
         * copy of the checkpoपूर्णांकed ones.  But, we still need to recheckpoपूर्णांक
         * as we're enabling FP क्रम the process; it will वापस, पात the
         * transaction, and probably retry but now with FP enabled.  So the
         * checkpoपूर्णांकed FP रेजिस्टरs need to be loaded.
	 */
	पंचांग_reclaim_current(TM_CAUSE_FAC_UNAV);

	/*
	 * Reclaim initially saved out bogus (lazy) FPRs to ckfp_state, and
	 * then it was overग_लिखो by the thr->fp_state by पंचांग_reclaim_thपढ़ो().
	 *
	 * At this poपूर्णांक, ckअणुfp,vrपूर्ण_state contains the exact values we want to
	 * recheckpoपूर्णांक.
	 */

	/* Enable FP क्रम the task: */
	current->thपढ़ो.load_fp = 1;

	/*
	 * Recheckpoपूर्णांक all the checkpoपूर्णांकed ckpt, ckअणुfp, vrपूर्ण_state रेजिस्टरs.
	 */
	पंचांग_recheckpoपूर्णांक(&current->thपढ़ो);
पूर्ण

DEFINE_INTERRUPT_HANDLER(altivec_unavailable_पंचांग)
अणु
	/* See the comments in fp_unavailable_पंचांग().  This function operates
	 * the same way.
	 */

	TM_DEBUG("Vector Unavailable trap whilst transactional at 0x%lx,"
		 "MSR=%lx\n",
		 regs->nip, regs->msr);
	पंचांग_reclaim_current(TM_CAUSE_FAC_UNAV);
	current->thपढ़ो.load_vec = 1;
	पंचांग_recheckpoपूर्णांक(&current->thपढ़ो);
	current->thपढ़ो.used_vr = 1;
पूर्ण

DEFINE_INTERRUPT_HANDLER(vsx_unavailable_पंचांग)
अणु
	/* See the comments in fp_unavailable_पंचांग().  This works similarly,
	 * though we're loading both FP and VEC रेजिस्टरs in here.
	 *
	 * If FP isn't in use, load FP regs.  If VEC isn't in use, load VEC
	 * regs.  Either way, set MSR_VSX.
	 */

	TM_DEBUG("VSX Unavailable trap whilst transactional at 0x%lx,"
		 "MSR=%lx\n",
		 regs->nip, regs->msr);

	current->thपढ़ो.used_vsr = 1;

	/* This reclaims FP and/or VR regs अगर they're alपढ़ोy enabled */
	पंचांग_reclaim_current(TM_CAUSE_FAC_UNAV);

	current->thपढ़ो.load_vec = 1;
	current->thपढ़ो.load_fp = 1;

	पंचांग_recheckpoपूर्णांक(&current->thपढ़ो);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */

#अगर_घोषित CONFIG_PPC64
DECLARE_INTERRUPT_HANDLER_NMI(perक्रमmance_monitor_exception_nmi);
DEFINE_INTERRUPT_HANDLER_NMI(perक्रमmance_monitor_exception_nmi)
अणु
	__this_cpu_inc(irq_stat.pmu_irqs);

	perf_irq(regs);

	वापस 0;
पूर्ण
#पूर्ण_अगर

DECLARE_INTERRUPT_HANDLER_ASYNC(perक्रमmance_monitor_exception_async);
DEFINE_INTERRUPT_HANDLER_ASYNC(perक्रमmance_monitor_exception_async)
अणु
	__this_cpu_inc(irq_stat.pmu_irqs);

	perf_irq(regs);
पूर्ण

DEFINE_INTERRUPT_HANDLER_RAW(perक्रमmance_monitor_exception)
अणु
	/*
	 * On 64-bit, अगर perf पूर्णांकerrupts hit in a local_irq_disable
	 * (soft-masked) region, we consider them as NMIs. This is required to
	 * prevent hash faults on user addresses when पढ़ोing callchains (and
	 * looks better from an irq tracing perspective).
	 */
	अगर (IS_ENABLED(CONFIG_PPC64) && unlikely(arch_irq_disabled_regs(regs)))
		perक्रमmance_monitor_exception_nmi(regs);
	अन्यथा
		perक्रमmance_monitor_exception_async(regs);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
अटल व्योम handle_debug(काष्ठा pt_regs *regs, अचिन्हित दीर्घ debug_status)
अणु
	पूर्णांक changed = 0;
	/*
	 * Determine the cause of the debug event, clear the
	 * event flags and send a trap to the handler. Torez
	 */
	अगर (debug_status & (DBSR_DAC1R | DBSR_DAC1W)) अणु
		dbcr_dac(current) &= ~(DBCR_DAC1R | DBCR_DAC1W);
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_DAC_RANGE
		current->thपढ़ो.debug.dbcr2 &= ~DBCR2_DAC12MODE;
#पूर्ण_अगर
		करो_send_trap(regs, mfspr(SPRN_DAC1), debug_status,
			     5);
		changed |= 0x01;
	पूर्ण  अन्यथा अगर (debug_status & (DBSR_DAC2R | DBSR_DAC2W)) अणु
		dbcr_dac(current) &= ~(DBCR_DAC2R | DBCR_DAC2W);
		करो_send_trap(regs, mfspr(SPRN_DAC2), debug_status,
			     6);
		changed |= 0x01;
	पूर्ण  अन्यथा अगर (debug_status & DBSR_IAC1) अणु
		current->thपढ़ो.debug.dbcr0 &= ~DBCR0_IAC1;
		dbcr_iac_range(current) &= ~DBCR_IAC12MODE;
		करो_send_trap(regs, mfspr(SPRN_IAC1), debug_status,
			     1);
		changed |= 0x01;
	पूर्ण  अन्यथा अगर (debug_status & DBSR_IAC2) अणु
		current->thपढ़ो.debug.dbcr0 &= ~DBCR0_IAC2;
		करो_send_trap(regs, mfspr(SPRN_IAC2), debug_status,
			     2);
		changed |= 0x01;
	पूर्ण  अन्यथा अगर (debug_status & DBSR_IAC3) अणु
		current->thपढ़ो.debug.dbcr0 &= ~DBCR0_IAC3;
		dbcr_iac_range(current) &= ~DBCR_IAC34MODE;
		करो_send_trap(regs, mfspr(SPRN_IAC3), debug_status,
			     3);
		changed |= 0x01;
	पूर्ण  अन्यथा अगर (debug_status & DBSR_IAC4) अणु
		current->thपढ़ो.debug.dbcr0 &= ~DBCR0_IAC4;
		करो_send_trap(regs, mfspr(SPRN_IAC4), debug_status,
			     4);
		changed |= 0x01;
	पूर्ण
	/*
	 * At the poपूर्णांक this routine was called, the MSR(DE) was turned off.
	 * Check all other debug flags and see अगर that bit needs to be turned
	 * back on or not.
	 */
	अगर (DBCR_ACTIVE_EVENTS(current->thपढ़ो.debug.dbcr0,
			       current->thपढ़ो.debug.dbcr1))
		regs->msr |= MSR_DE;
	अन्यथा
		/* Make sure the IDM flag is off */
		current->thपढ़ो.debug.dbcr0 &= ~DBCR0_IDM;

	अगर (changed & 0x01)
		mtspr(SPRN_DBCR0, current->thपढ़ो.debug.dbcr0);
पूर्ण

DEFINE_INTERRUPT_HANDLER(DebugException)
अणु
	अचिन्हित दीर्घ debug_status = regs->dsisr;

	current->thपढ़ो.debug.dbsr = debug_status;

	/* Hack alert: On BookE, Branch Taken stops on the branch itself, जबतक
	 * on server, it stops on the target of the branch. In order to simulate
	 * the server behaviour, we thus restart right away with a single step
	 * instead of stopping here when hitting a BT
	 */
	अगर (debug_status & DBSR_BT) अणु
		regs->msr &= ~MSR_DE;

		/* Disable BT */
		mtspr(SPRN_DBCR0, mfspr(SPRN_DBCR0) & ~DBCR0_BT);
		/* Clear the BT event */
		mtspr(SPRN_DBSR, DBSR_BT);

		/* Do the single step trick only when coming from userspace */
		अगर (user_mode(regs)) अणु
			current->thपढ़ो.debug.dbcr0 &= ~DBCR0_BT;
			current->thपढ़ो.debug.dbcr0 |= DBCR0_IDM | DBCR0_IC;
			regs->msr |= MSR_DE;
			वापस;
		पूर्ण

		अगर (kprobe_post_handler(regs))
			वापस;

		अगर (notअगरy_die(DIE_SSTEP, "block_step", regs, 5,
			       5, SIGTRAP) == NOTIFY_STOP) अणु
			वापस;
		पूर्ण
		अगर (debugger_sstep(regs))
			वापस;
	पूर्ण अन्यथा अगर (debug_status & DBSR_IC) अणु 	/* Inकाष्ठाion complete */
		regs->msr &= ~MSR_DE;

		/* Disable inकाष्ठाion completion */
		mtspr(SPRN_DBCR0, mfspr(SPRN_DBCR0) & ~DBCR0_IC);
		/* Clear the inकाष्ठाion completion event */
		mtspr(SPRN_DBSR, DBSR_IC);

		अगर (kprobe_post_handler(regs))
			वापस;

		अगर (notअगरy_die(DIE_SSTEP, "single_step", regs, 5,
			       5, SIGTRAP) == NOTIFY_STOP) अणु
			वापस;
		पूर्ण

		अगर (debugger_sstep(regs))
			वापस;

		अगर (user_mode(regs)) अणु
			current->thपढ़ो.debug.dbcr0 &= ~DBCR0_IC;
			अगर (DBCR_ACTIVE_EVENTS(current->thपढ़ो.debug.dbcr0,
					       current->thपढ़ो.debug.dbcr1))
				regs->msr |= MSR_DE;
			अन्यथा
				/* Make sure the IDM bit is off */
				current->thपढ़ो.debug.dbcr0 &= ~DBCR0_IDM;
		पूर्ण

		_exception(SIGTRAP, regs, TRAP_TRACE, regs->nip);
	पूर्ण अन्यथा
		handle_debug(regs, debug_status);
पूर्ण
#पूर्ण_अगर /* CONFIG_PPC_ADV_DEBUG_REGS */

#अगर_घोषित CONFIG_ALTIVEC
DEFINE_INTERRUPT_HANDLER(altivec_assist_exception)
अणु
	पूर्णांक err;

	अगर (!user_mode(regs)) अणु
		prपूर्णांकk(KERN_EMERG "VMX/Altivec assist exception in kernel mode"
		       " at %lx\n", regs->nip);
		die("Kernel VMX/Altivec assist exception", regs, संक_अवैध);
	पूर्ण

	flush_altivec_to_thपढ़ो(current);

	PPC_WARN_EMULATED(altivec, regs);
	err = emulate_altivec(regs);
	अगर (err == 0) अणु
		regs->nip += 4;		/* skip emulated inकाष्ठाion */
		emulate_single_step(regs);
		वापस;
	पूर्ण

	अगर (err == -EFAULT) अणु
		/* got an error पढ़ोing the inकाष्ठाion */
		_exception(संक_अंश, regs, SEGV_ACCERR, regs->nip);
	पूर्ण अन्यथा अणु
		/* didn't recognize the inकाष्ठाion */
		/* XXX quick hack क्रम now: set the non-Java bit in the VSCR */
		prपूर्णांकk_ratelimited(KERN_ERR "Unrecognized altivec instruction "
				   "in %s at %lx\n", current->comm, regs->nip);
		current->thपढ़ो.vr_state.vscr.u[3] |= 0x10000;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_ALTIVEC */

#अगर_घोषित CONFIG_FSL_BOOKE
DEFINE_INTERRUPT_HANDLER(CacheLockingException)
अणु
	अचिन्हित दीर्घ error_code = regs->dsisr;

	/* We treat cache locking inकाष्ठाions from the user
	 * as priv ops, in the future we could try to करो
	 * something smarter
	 */
	अगर (error_code & (ESR_DLK|ESR_ILK))
		_exception(संक_अवैध, regs, ILL_PRVOPC, regs->nip);
	वापस;
पूर्ण
#पूर्ण_अगर /* CONFIG_FSL_BOOKE */

#अगर_घोषित CONFIG_SPE
DEFINE_INTERRUPT_HANDLER(SPEFloatingPoपूर्णांकException)
अणु
	बाह्य पूर्णांक करो_spe_mathemu(काष्ठा pt_regs *regs);
	अचिन्हित दीर्घ spefscr;
	पूर्णांक fpexc_mode;
	पूर्णांक code = FPE_FLTUNK;
	पूर्णांक err;

	पूर्णांकerrupt_cond_local_irq_enable(regs);

	flush_spe_to_thपढ़ो(current);

	spefscr = current->thपढ़ो.spefscr;
	fpexc_mode = current->thपढ़ो.fpexc_mode;

	अगर ((spefscr & SPEFSCR_FOVF) && (fpexc_mode & PR_FP_EXC_OVF)) अणु
		code = FPE_FLTOVF;
	पूर्ण
	अन्यथा अगर ((spefscr & SPEFSCR_FUNF) && (fpexc_mode & PR_FP_EXC_UND)) अणु
		code = FPE_FLTUND;
	पूर्ण
	अन्यथा अगर ((spefscr & SPEFSCR_FDBZ) && (fpexc_mode & PR_FP_EXC_DIV))
		code = FPE_FLTDIV;
	अन्यथा अगर ((spefscr & SPEFSCR_FINV) && (fpexc_mode & PR_FP_EXC_INV)) अणु
		code = FPE_FLTINV;
	पूर्ण
	अन्यथा अगर ((spefscr & (SPEFSCR_FG | SPEFSCR_FX)) && (fpexc_mode & PR_FP_EXC_RES))
		code = FPE_FLTRES;

	err = करो_spe_mathemu(regs);
	अगर (err == 0) अणु
		regs->nip += 4;		/* skip emulated inकाष्ठाion */
		emulate_single_step(regs);
		वापस;
	पूर्ण

	अगर (err == -EFAULT) अणु
		/* got an error पढ़ोing the inकाष्ठाion */
		_exception(संक_अंश, regs, SEGV_ACCERR, regs->nip);
	पूर्ण अन्यथा अगर (err == -EINVAL) अणु
		/* didn't recognize the inकाष्ठाion */
		prपूर्णांकk(KERN_ERR "unrecognized spe instruction "
		       "in %s at %lx\n", current->comm, regs->nip);
	पूर्ण अन्यथा अणु
		_exception(संक_भ_त्रुटि, regs, code, regs->nip);
	पूर्ण

	वापस;
पूर्ण

DEFINE_INTERRUPT_HANDLER(SPEFloatingPoपूर्णांकRoundException)
अणु
	बाह्य पूर्णांक speround_handler(काष्ठा pt_regs *regs);
	पूर्णांक err;

	पूर्णांकerrupt_cond_local_irq_enable(regs);

	preempt_disable();
	अगर (regs->msr & MSR_SPE)
		giveup_spe(current);
	preempt_enable();

	regs->nip -= 4;
	err = speround_handler(regs);
	अगर (err == 0) अणु
		regs->nip += 4;		/* skip emulated inकाष्ठाion */
		emulate_single_step(regs);
		वापस;
	पूर्ण

	अगर (err == -EFAULT) अणु
		/* got an error पढ़ोing the inकाष्ठाion */
		_exception(संक_अंश, regs, SEGV_ACCERR, regs->nip);
	पूर्ण अन्यथा अगर (err == -EINVAL) अणु
		/* didn't recognize the inकाष्ठाion */
		prपूर्णांकk(KERN_ERR "unrecognized spe instruction "
		       "in %s at %lx\n", current->comm, regs->nip);
	पूर्ण अन्यथा अणु
		_exception(संक_भ_त्रुटि, regs, FPE_FLTUNK, regs->nip);
		वापस;
	पूर्ण
पूर्ण
#पूर्ण_अगर

/*
 * We enter here अगर we get an unrecoverable exception, that is, one
 * that happened at a poपूर्णांक where the RI (recoverable पूर्णांकerrupt) bit
 * in the MSR is 0.  This indicates that SRR0/1 are live, and that
 * we thereक्रमe lost state by taking this exception.
 */
व्योम __noवापस unrecoverable_exception(काष्ठा pt_regs *regs)
अणु
	pr_emerg("Unrecoverable exception %lx at %lx (msr=%lx)\n",
		 regs->trap, regs->nip, regs->msr);
	die("Unrecoverable exception", regs, SIGABRT);
	/* die() should not वापस */
	क्रम (;;)
		;
पूर्ण

#अगर defined(CONFIG_BOOKE_WDT) || defined(CONFIG_40x)
/*
 * Default handler क्रम a Watchकरोg exception,
 * spins until a reboot occurs
 */
व्योम __attribute__ ((weak)) WatchकरोgHandler(काष्ठा pt_regs *regs)
अणु
	/* Generic WatchकरोgHandler, implement your own */
	mtspr(SPRN_TCR, mfspr(SPRN_TCR)&(~TCR_WIE));
	वापस;
पूर्ण

DEFINE_INTERRUPT_HANDLER_NMI(WatchकरोgException)
अणु
	prपूर्णांकk (KERN_EMERG "PowerPC Book-E Watchdog Exception\n");
	WatchकरोgHandler(regs);
	वापस 0;
पूर्ण
#पूर्ण_अगर

/*
 * We enter here अगर we discover during exception entry that we are
 * running in supervisor mode with a userspace value in the stack poपूर्णांकer.
 */
DEFINE_INTERRUPT_HANDLER(kernel_bad_stack)
अणु
	prपूर्णांकk(KERN_EMERG "Bad kernel stack pointer %lx at %lx\n",
	       regs->gpr[1], regs->nip);
	die("Bad kernel stack pointer", regs, SIGABRT);
पूर्ण

व्योम __init trap_init(व्योम)
अणु
पूर्ण


#अगर_घोषित CONFIG_PPC_EMULATED_STATS

#घोषणा WARN_EMULATED_SETUP(type)	.type = अणु .name = #type पूर्ण

काष्ठा ppc_emulated ppc_emulated = अणु
#अगर_घोषित CONFIG_ALTIVEC
	WARN_EMULATED_SETUP(altivec),
#पूर्ण_अगर
	WARN_EMULATED_SETUP(dcba),
	WARN_EMULATED_SETUP(dcbz),
	WARN_EMULATED_SETUP(fp_pair),
	WARN_EMULATED_SETUP(isel),
	WARN_EMULATED_SETUP(mcrxr),
	WARN_EMULATED_SETUP(mfpvr),
	WARN_EMULATED_SETUP(multiple),
	WARN_EMULATED_SETUP(popcntb),
	WARN_EMULATED_SETUP(spe),
	WARN_EMULATED_SETUP(string),
	WARN_EMULATED_SETUP(sync),
	WARN_EMULATED_SETUP(unaligned),
#अगर_घोषित CONFIG_MATH_EMULATION
	WARN_EMULATED_SETUP(math),
#पूर्ण_अगर
#अगर_घोषित CONFIG_VSX
	WARN_EMULATED_SETUP(vsx),
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
	WARN_EMULATED_SETUP(mfdscr),
	WARN_EMULATED_SETUP(mtdscr),
	WARN_EMULATED_SETUP(lq_stq),
	WARN_EMULATED_SETUP(lxvw4x),
	WARN_EMULATED_SETUP(lxvh8x),
	WARN_EMULATED_SETUP(lxvd2x),
	WARN_EMULATED_SETUP(lxvb16x),
#पूर्ण_अगर
पूर्ण;

u32 ppc_warn_emulated;

व्योम ppc_warn_emulated_prपूर्णांक(स्थिर अक्षर *type)
अणु
	pr_warn_ratelimited("%s used emulated %s instruction\n", current->comm,
			    type);
पूर्ण

अटल पूर्णांक __init ppc_warn_emulated_init(व्योम)
अणु
	काष्ठा dentry *dir;
	अचिन्हित पूर्णांक i;
	काष्ठा ppc_emulated_entry *entries = (व्योम *)&ppc_emulated;

	dir = debugfs_create_dir("emulated_instructions",
				 घातerpc_debugfs_root);

	debugfs_create_u32("do_warn", 0644, dir, &ppc_warn_emulated);

	क्रम (i = 0; i < माप(ppc_emulated)/माप(*entries); i++)
		debugfs_create_u32(entries[i].name, 0644, dir,
				   (u32 *)&entries[i].val.counter);

	वापस 0;
पूर्ण

device_initcall(ppc_warn_emulated_init);

#पूर्ण_अगर /* CONFIG_PPC_EMULATED_STATS */
