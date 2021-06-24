<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_INTERRUPT_H
#घोषणा _ASM_POWERPC_INTERRUPT_H

/* BookE/4xx */
#घोषणा INTERRUPT_CRITICAL_INPUT  0x100

/* BookE */
#घोषणा INTERRUPT_DEBUG           0xd00
#अगर_घोषित CONFIG_BOOKE
#घोषणा INTERRUPT_PERFMON         0x260
#घोषणा INTERRUPT_DOORBELL        0x280
#पूर्ण_अगर

/* BookS/4xx/8xx */
#घोषणा INTERRUPT_MACHINE_CHECK   0x200

/* BookS/8xx */
#घोषणा INTERRUPT_SYSTEM_RESET    0x100

/* BookS */
#घोषणा INTERRUPT_DATA_SEGMENT    0x380
#घोषणा INTERRUPT_INST_SEGMENT    0x480
#घोषणा INTERRUPT_TRACE           0xd00
#घोषणा INTERRUPT_H_DATA_STORAGE  0xe00
#घोषणा INTERRUPT_HMI			0xe60
#घोषणा INTERRUPT_H_FAC_UNAVAIL   0xf80
#अगर_घोषित CONFIG_PPC_BOOK3S
#घोषणा INTERRUPT_DOORBELL        0xa00
#घोषणा INTERRUPT_PERFMON         0xf00
#घोषणा INTERRUPT_ALTIVEC_UNAVAIL	0xf20
#पूर्ण_अगर

/* BookE/BookS/4xx/8xx */
#घोषणा INTERRUPT_DATA_STORAGE    0x300
#घोषणा INTERRUPT_INST_STORAGE    0x400
#घोषणा INTERRUPT_EXTERNAL		0x500
#घोषणा INTERRUPT_ALIGNMENT       0x600
#घोषणा INTERRUPT_PROGRAM         0x700
#घोषणा INTERRUPT_SYSCALL         0xc00
#घोषणा INTERRUPT_TRACE			0xd00

/* BookE/BookS/44x */
#घोषणा INTERRUPT_FP_UNAVAIL      0x800

/* BookE/BookS/44x/8xx */
#घोषणा INTERRUPT_DECREMENTER     0x900

#अगर_अघोषित INTERRUPT_PERFMON
#घोषणा INTERRUPT_PERFMON         0x0
#पूर्ण_अगर

/* 8xx */
#घोषणा INTERRUPT_SOFT_EMU_8xx		0x1000
#घोषणा INTERRUPT_INST_TLB_MISS_8xx	0x1100
#घोषणा INTERRUPT_DATA_TLB_MISS_8xx	0x1200
#घोषणा INTERRUPT_INST_TLB_ERROR_8xx	0x1300
#घोषणा INTERRUPT_DATA_TLB_ERROR_8xx	0x1400
#घोषणा INTERRUPT_DATA_BREAKPOINT_8xx	0x1c00
#घोषणा INTERRUPT_INST_BREAKPOINT_8xx	0x1d00

/* 603 */
#घोषणा INTERRUPT_INST_TLB_MISS_603		0x1000
#घोषणा INTERRUPT_DATA_LOAD_TLB_MISS_603	0x1100
#घोषणा INTERRUPT_DATA_STORE_TLB_MISS_603	0x1200

#अगर_अघोषित __ASSEMBLY__

#समावेश <linux/context_tracking.h>
#समावेश <linux/hardirq.h>
#समावेश <यंत्र/cpuसमय.स>
#समावेश <यंत्र/ftrace.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <यंत्र/runlatch.h>

अटल अंतरभूत व्योम nap_adjust_वापस(काष्ठा pt_regs *regs)
अणु
#अगर_घोषित CONFIG_PPC_970_NAP
	अगर (unlikely(test_thपढ़ो_local_flags(_TLF_NAPPING))) अणु
		/* Can aव्योम a test-and-clear because NMIs करो not call this */
		clear_thपढ़ो_local_flags(_TLF_NAPPING);
		regs->nip = (अचिन्हित दीर्घ)घातer4_idle_nap_वापस;
	पूर्ण
#पूर्ण_अगर
पूर्ण

काष्ठा पूर्णांकerrupt_state अणु
पूर्ण;

अटल अंतरभूत व्योम booke_restore_dbcr0(व्योम)
अणु
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
	अचिन्हित दीर्घ dbcr0 = current->thपढ़ो.debug.dbcr0;

	अगर (IS_ENABLED(CONFIG_PPC32) && unlikely(dbcr0 & DBCR0_IDM)) अणु
		mtspr(SPRN_DBSR, -1);
		mtspr(SPRN_DBCR0, global_dbcr0[smp_processor_id()]);
	पूर्ण
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम पूर्णांकerrupt_enter_prepare(काष्ठा pt_regs *regs, काष्ठा पूर्णांकerrupt_state *state)
अणु
#अगर_घोषित CONFIG_PPC32
	अगर (!arch_irq_disabled_regs(regs))
		trace_hardirqs_off();

	अगर (user_mode(regs)) अणु
		kuep_lock();
		account_cpu_user_entry();
	पूर्ण अन्यथा अणु
		kuap_save_and_lock(regs);
	पूर्ण
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
	अगर (irq_soft_mask_set_वापस(IRQS_ALL_DISABLED) == IRQS_ENABLED)
		trace_hardirqs_off();
	local_paca->irq_happened |= PACA_IRQ_HARD_DIS;

	अगर (user_mode(regs)) अणु
		CT_WARN_ON(ct_state() != CONTEXT_USER);
		user_निकास_irqoff();

		account_cpu_user_entry();
		account_stolen_समय();
	पूर्ण अन्यथा अणु
		/*
		 * CT_WARN_ON comes here via program_check_exception,
		 * so aव्योम recursion.
		 */
		अगर (TRAP(regs) != INTERRUPT_PROGRAM)
			CT_WARN_ON(ct_state() != CONTEXT_KERNEL);
	पूर्ण
#पूर्ण_अगर

	booke_restore_dbcr0();
पूर्ण

/*
 * Care should be taken to note that पूर्णांकerrupt_निकास_prepare and
 * पूर्णांकerrupt_async_निकास_prepare करो not necessarily वापस immediately to
 * regs context (e.g., अगर regs is usermode, we करोn't necessarily वापस to
 * user mode). Other पूर्णांकerrupts might be taken between here and वापस,
 * context चयन / preemption may occur in the निकास path after this, or a
 * संकेत may be delivered, etc.
 *
 * The real पूर्णांकerrupt निकास code is platक्रमm specअगरic, e.g.,
 * पूर्णांकerrupt_निकास_user_prepare / पूर्णांकerrupt_निकास_kernel_prepare क्रम 64s.
 *
 * However पूर्णांकerrupt_nmi_निकास_prepare करोes वापस directly to regs, because
 * NMIs करो not करो "exit work" or replay soft-masked पूर्णांकerrupts.
 */
अटल अंतरभूत व्योम पूर्णांकerrupt_निकास_prepare(काष्ठा pt_regs *regs, काष्ठा पूर्णांकerrupt_state *state)
अणु
पूर्ण

अटल अंतरभूत व्योम पूर्णांकerrupt_async_enter_prepare(काष्ठा pt_regs *regs, काष्ठा पूर्णांकerrupt_state *state)
अणु
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अगर (cpu_has_feature(CPU_FTR_CTRL) &&
	    !test_thपढ़ो_local_flags(_TLF_RUNLATCH))
		__ppc64_runlatch_on();
#पूर्ण_अगर

	पूर्णांकerrupt_enter_prepare(regs, state);
	irq_enter();
पूर्ण

अटल अंतरभूत व्योम पूर्णांकerrupt_async_निकास_prepare(काष्ठा pt_regs *regs, काष्ठा पूर्णांकerrupt_state *state)
अणु
	/*
	 * Adjust at निकास so the मुख्य handler sees the true NIA. This must
	 * come beक्रमe irq_निकास() because irq_निकास can enable पूर्णांकerrupts, and
	 * अगर another पूर्णांकerrupt is taken beक्रमe nap_adjust_वापस has run
	 * here, then that पूर्णांकerrupt would वापस directly to idle nap वापस.
	 */
	nap_adjust_वापस(regs);

	irq_निकास();
	पूर्णांकerrupt_निकास_prepare(regs, state);
पूर्ण

काष्ठा पूर्णांकerrupt_nmi_state अणु
#अगर_घोषित CONFIG_PPC64
	u8 irq_soft_mask;
	u8 irq_happened;
	u8 ftrace_enabled;
#पूर्ण_अगर
पूर्ण;

अटल अंतरभूत bool nmi_disables_ftrace(काष्ठा pt_regs *regs)
अणु
	/* Allow DEC and PMI to be traced when they are soft-NMI */
	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64)) अणु
		अगर (TRAP(regs) == INTERRUPT_DECREMENTER)
		       वापस false;
		अगर (TRAP(regs) == INTERRUPT_PERFMON)
		       वापस false;
	पूर्ण
	अगर (IS_ENABLED(CONFIG_PPC_BOOK3E)) अणु
		अगर (TRAP(regs) == INTERRUPT_PERFMON)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल अंतरभूत व्योम पूर्णांकerrupt_nmi_enter_prepare(काष्ठा pt_regs *regs, काष्ठा पूर्णांकerrupt_nmi_state *state)
अणु
#अगर_घोषित CONFIG_PPC64
	state->irq_soft_mask = local_paca->irq_soft_mask;
	state->irq_happened = local_paca->irq_happened;

	/*
	 * Set IRQS_ALL_DISABLED unconditionally so irqs_disabled() करोes
	 * the right thing, and set IRQ_HARD_DIS. We करो not want to reconcile
	 * because that goes through irq tracing which we करोn't want in NMI.
	 */
	local_paca->irq_soft_mask = IRQS_ALL_DISABLED;
	local_paca->irq_happened |= PACA_IRQ_HARD_DIS;

	अगर (IS_ENABLED(CONFIG_PPC_BOOK3S_64) && !(regs->msr & MSR_PR) &&
				regs->nip < (अचिन्हित दीर्घ)__end_पूर्णांकerrupts) अणु
		// Kernel code running below __end_पूर्णांकerrupts is
		// implicitly soft-masked.
		regs->softe = IRQS_ALL_DISABLED;
	पूर्ण

	/* Don't करो any per-CPU operations until पूर्णांकerrupt state is fixed */

	अगर (nmi_disables_ftrace(regs)) अणु
		state->ftrace_enabled = this_cpu_get_ftrace_enabled();
		this_cpu_set_ftrace_enabled(0);
	पूर्ण
#पूर्ण_अगर

	/*
	 * Do not use nmi_enter() क्रम pseries hash guest taking a real-mode
	 * NMI because not everything it touches is within the RMA limit.
	 */
	अगर (!IS_ENABLED(CONFIG_PPC_BOOK3S_64) ||
			!firmware_has_feature(FW_FEATURE_LPAR) ||
			radix_enabled() || (mfmsr() & MSR_DR))
		nmi_enter();
पूर्ण

अटल अंतरभूत व्योम पूर्णांकerrupt_nmi_निकास_prepare(काष्ठा pt_regs *regs, काष्ठा पूर्णांकerrupt_nmi_state *state)
अणु
	अगर (!IS_ENABLED(CONFIG_PPC_BOOK3S_64) ||
			!firmware_has_feature(FW_FEATURE_LPAR) ||
			radix_enabled() || (mfmsr() & MSR_DR))
		nmi_निकास();

	/*
	 * nmi करोes not call nap_adjust_वापस because nmi should not create
	 * new work to करो (must use irq_work क्रम that).
	 */

#अगर_घोषित CONFIG_PPC64
	अगर (nmi_disables_ftrace(regs))
		this_cpu_set_ftrace_enabled(state->ftrace_enabled);

	/* Check we didn't change the pending पूर्णांकerrupt mask. */
	WARN_ON_ONCE((state->irq_happened | PACA_IRQ_HARD_DIS) != local_paca->irq_happened);
	local_paca->irq_happened = state->irq_happened;
	local_paca->irq_soft_mask = state->irq_soft_mask;
#पूर्ण_अगर
पूर्ण

/*
 * Don't use noinstr here like x86, but rather add NOKPROBE_SYMBOL to each
 * function definition. The reason क्रम this is the noinstr section is placed
 * after the मुख्य text section, i.e., very far away from the पूर्णांकerrupt entry
 * यंत्र. That creates problems with fitting linker stubs when building large
 * kernels.
 */
#घोषणा पूर्णांकerrupt_handler __visible noअंतरभूत notrace __no_kcsan __no_sanitize_address

/**
 * DECLARE_INTERRUPT_HANDLER_RAW - Declare raw पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 * @वापसs:	Returns a value back to यंत्र caller
 */
#घोषणा DECLARE_INTERRUPT_HANDLER_RAW(func)				\
	__visible दीर्घ func(काष्ठा pt_regs *regs)

/**
 * DEFINE_INTERRUPT_HANDLER_RAW - Define raw पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 * @वापसs:	Returns a value back to यंत्र caller
 *
 * @func is called from ASM entry code.
 *
 * This is a plain function which करोes no tracing, reconciling, etc.
 * The macro is written so it acts as function definition. Append the
 * body with a pair of curly brackets.
 *
 * raw पूर्णांकerrupt handlers must not enable or disable पूर्णांकerrupts, or
 * schedule, tracing and instrumentation (ftrace, lockdep, etc) would
 * not be advisable either, although may be possible in a pinch, the
 * trace will look odd at least.
 *
 * A raw handler may call one of the other पूर्णांकerrupt handler functions
 * to be converted पूर्णांकo that पूर्णांकerrupt context without these restrictions.
 *
 * On PPC64, _RAW handlers may वापस with fast_पूर्णांकerrupt_वापस.
 *
 * Specअगरic handlers may have additional restrictions.
 */
#घोषणा DEFINE_INTERRUPT_HANDLER_RAW(func)				\
अटल __always_अंतरभूत दीर्घ ____##func(काष्ठा pt_regs *regs);		\
									\
पूर्णांकerrupt_handler दीर्घ func(काष्ठा pt_regs *regs)			\
अणु									\
	दीर्घ ret;							\
									\
	ret = ____##func (regs);					\
									\
	वापस ret;							\
पूर्ण									\
NOKPROBE_SYMBOL(func);							\
									\
अटल __always_अंतरभूत दीर्घ ____##func(काष्ठा pt_regs *regs)

/**
 * DECLARE_INTERRUPT_HANDLER - Declare synchronous पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 */
#घोषणा DECLARE_INTERRUPT_HANDLER(func)					\
	__visible व्योम func(काष्ठा pt_regs *regs)

/**
 * DEFINE_INTERRUPT_HANDLER - Define synchronous पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 *
 * @func is called from ASM entry code.
 *
 * The macro is written so it acts as function definition. Append the
 * body with a pair of curly brackets.
 */
#घोषणा DEFINE_INTERRUPT_HANDLER(func)					\
अटल __always_अंतरभूत व्योम ____##func(काष्ठा pt_regs *regs);		\
									\
पूर्णांकerrupt_handler व्योम func(काष्ठा pt_regs *regs)			\
अणु									\
	काष्ठा पूर्णांकerrupt_state state;					\
									\
	पूर्णांकerrupt_enter_prepare(regs, &state);				\
									\
	____##func (regs);						\
									\
	पूर्णांकerrupt_निकास_prepare(regs, &state);				\
पूर्ण									\
NOKPROBE_SYMBOL(func);							\
									\
अटल __always_अंतरभूत व्योम ____##func(काष्ठा pt_regs *regs)

/**
 * DECLARE_INTERRUPT_HANDLER_RET - Declare synchronous पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 * @वापसs:	Returns a value back to यंत्र caller
 */
#घोषणा DECLARE_INTERRUPT_HANDLER_RET(func)				\
	__visible दीर्घ func(काष्ठा pt_regs *regs)

/**
 * DEFINE_INTERRUPT_HANDLER_RET - Define synchronous पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 * @वापसs:	Returns a value back to यंत्र caller
 *
 * @func is called from ASM entry code.
 *
 * The macro is written so it acts as function definition. Append the
 * body with a pair of curly brackets.
 */
#घोषणा DEFINE_INTERRUPT_HANDLER_RET(func)				\
अटल __always_अंतरभूत दीर्घ ____##func(काष्ठा pt_regs *regs);		\
									\
पूर्णांकerrupt_handler दीर्घ func(काष्ठा pt_regs *regs)			\
अणु									\
	काष्ठा पूर्णांकerrupt_state state;					\
	दीर्घ ret;							\
									\
	पूर्णांकerrupt_enter_prepare(regs, &state);				\
									\
	ret = ____##func (regs);					\
									\
	पूर्णांकerrupt_निकास_prepare(regs, &state);				\
									\
	वापस ret;							\
पूर्ण									\
NOKPROBE_SYMBOL(func);							\
									\
अटल __always_अंतरभूत दीर्घ ____##func(काष्ठा pt_regs *regs)

/**
 * DECLARE_INTERRUPT_HANDLER_ASYNC - Declare asynchronous पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 */
#घोषणा DECLARE_INTERRUPT_HANDLER_ASYNC(func)				\
	__visible व्योम func(काष्ठा pt_regs *regs)

/**
 * DEFINE_INTERRUPT_HANDLER_ASYNC - Define asynchronous पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 *
 * @func is called from ASM entry code.
 *
 * The macro is written so it acts as function definition. Append the
 * body with a pair of curly brackets.
 */
#घोषणा DEFINE_INTERRUPT_HANDLER_ASYNC(func)				\
अटल __always_अंतरभूत व्योम ____##func(काष्ठा pt_regs *regs);		\
									\
पूर्णांकerrupt_handler व्योम func(काष्ठा pt_regs *regs)			\
अणु									\
	काष्ठा पूर्णांकerrupt_state state;					\
									\
	पूर्णांकerrupt_async_enter_prepare(regs, &state);			\
									\
	____##func (regs);						\
									\
	पूर्णांकerrupt_async_निकास_prepare(regs, &state);			\
पूर्ण									\
NOKPROBE_SYMBOL(func);							\
									\
अटल __always_अंतरभूत व्योम ____##func(काष्ठा pt_regs *regs)

/**
 * DECLARE_INTERRUPT_HANDLER_NMI - Declare NMI पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 * @वापसs:	Returns a value back to यंत्र caller
 */
#घोषणा DECLARE_INTERRUPT_HANDLER_NMI(func)				\
	__visible दीर्घ func(काष्ठा pt_regs *regs)

/**
 * DEFINE_INTERRUPT_HANDLER_NMI - Define NMI पूर्णांकerrupt handler function
 * @func:	Function name of the entry poपूर्णांक
 * @वापसs:	Returns a value back to यंत्र caller
 *
 * @func is called from ASM entry code.
 *
 * The macro is written so it acts as function definition. Append the
 * body with a pair of curly brackets.
 */
#घोषणा DEFINE_INTERRUPT_HANDLER_NMI(func)				\
अटल __always_अंतरभूत दीर्घ ____##func(काष्ठा pt_regs *regs);		\
									\
पूर्णांकerrupt_handler दीर्घ func(काष्ठा pt_regs *regs)			\
अणु									\
	काष्ठा पूर्णांकerrupt_nmi_state state;				\
	दीर्घ ret;							\
									\
	पूर्णांकerrupt_nmi_enter_prepare(regs, &state);			\
									\
	ret = ____##func (regs);					\
									\
	पूर्णांकerrupt_nmi_निकास_prepare(regs, &state);			\
									\
	वापस ret;							\
पूर्ण									\
NOKPROBE_SYMBOL(func);							\
									\
अटल __always_अंतरभूत दीर्घ ____##func(काष्ठा pt_regs *regs)


/* Interrupt handlers */
/* kernel/traps.c */
DECLARE_INTERRUPT_HANDLER_NMI(प्रणाली_reset_exception);
#अगर_घोषित CONFIG_PPC_BOOK3S_64
DECLARE_INTERRUPT_HANDLER_ASYNC(machine_check_exception);
#अन्यथा
DECLARE_INTERRUPT_HANDLER_NMI(machine_check_exception);
#पूर्ण_अगर
DECLARE_INTERRUPT_HANDLER(SMIException);
DECLARE_INTERRUPT_HANDLER(handle_hmi_exception);
DECLARE_INTERRUPT_HANDLER(unknown_exception);
DECLARE_INTERRUPT_HANDLER_ASYNC(unknown_async_exception);
DECLARE_INTERRUPT_HANDLER_NMI(unknown_nmi_exception);
DECLARE_INTERRUPT_HANDLER(inकाष्ठाion_अवरोधpoपूर्णांक_exception);
DECLARE_INTERRUPT_HANDLER(RunModeException);
DECLARE_INTERRUPT_HANDLER(single_step_exception);
DECLARE_INTERRUPT_HANDLER(program_check_exception);
DECLARE_INTERRUPT_HANDLER(emulation_assist_पूर्णांकerrupt);
DECLARE_INTERRUPT_HANDLER(alignment_exception);
DECLARE_INTERRUPT_HANDLER(StackOverflow);
DECLARE_INTERRUPT_HANDLER(stack_overflow_exception);
DECLARE_INTERRUPT_HANDLER(kernel_fp_unavailable_exception);
DECLARE_INTERRUPT_HANDLER(altivec_unavailable_exception);
DECLARE_INTERRUPT_HANDLER(vsx_unavailable_exception);
DECLARE_INTERRUPT_HANDLER(facility_unavailable_exception);
DECLARE_INTERRUPT_HANDLER(fp_unavailable_पंचांग);
DECLARE_INTERRUPT_HANDLER(altivec_unavailable_पंचांग);
DECLARE_INTERRUPT_HANDLER(vsx_unavailable_पंचांग);
DECLARE_INTERRUPT_HANDLER_NMI(perक्रमmance_monitor_exception_nmi);
DECLARE_INTERRUPT_HANDLER_ASYNC(perक्रमmance_monitor_exception_async);
DECLARE_INTERRUPT_HANDLER_RAW(perक्रमmance_monitor_exception);
DECLARE_INTERRUPT_HANDLER(DebugException);
DECLARE_INTERRUPT_HANDLER(altivec_assist_exception);
DECLARE_INTERRUPT_HANDLER(CacheLockingException);
DECLARE_INTERRUPT_HANDLER(SPEFloatingPoपूर्णांकException);
DECLARE_INTERRUPT_HANDLER(SPEFloatingPoपूर्णांकRoundException);
DECLARE_INTERRUPT_HANDLER_NMI(WatchकरोgException);
DECLARE_INTERRUPT_HANDLER(kernel_bad_stack);

/* slb.c */
DECLARE_INTERRUPT_HANDLER_RAW(करो_slb_fault);
DECLARE_INTERRUPT_HANDLER(करो_bad_slb_fault);

/* hash_utils.c */
DECLARE_INTERRUPT_HANDLER_RAW(करो_hash_fault);

/* fault.c */
DECLARE_INTERRUPT_HANDLER(करो_page_fault);
DECLARE_INTERRUPT_HANDLER(करो_bad_page_fault_segv);

/* process.c */
DECLARE_INTERRUPT_HANDLER(करो_अवरोध);

/* समय.c */
DECLARE_INTERRUPT_HANDLER_ASYNC(समयr_पूर्णांकerrupt);

/* mce.c */
DECLARE_INTERRUPT_HANDLER_NMI(machine_check_early);
DECLARE_INTERRUPT_HANDLER_NMI(hmi_exception_realmode);

DECLARE_INTERRUPT_HANDLER_ASYNC(TAUException);

व्योम __noवापस unrecoverable_exception(काष्ठा pt_regs *regs);

व्योम replay_प्रणाली_reset(व्योम);
व्योम replay_soft_पूर्णांकerrupts(व्योम);

अटल अंतरभूत व्योम पूर्णांकerrupt_cond_local_irq_enable(काष्ठा pt_regs *regs)
अणु
	अगर (!arch_irq_disabled_regs(regs))
		local_irq_enable();
पूर्ण

#पूर्ण_अगर /* __ASSEMBLY__ */

#पूर्ण_अगर /* _ASM_POWERPC_INTERRUPT_H */
