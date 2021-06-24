<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * This control block defines the PACA which defines the processor
 * specअगरic data क्रम each logical processor on the प्रणाली.
 * There are some poपूर्णांकers defined that are utilized by PLIC.
 *
 * C 2001 PPC 64 Team, IBM Corp
 */
#अगर_अघोषित _ASM_POWERPC_PACA_H
#घोषणा _ASM_POWERPC_PACA_H
#अगर_घोषित __KERNEL__

#अगर_घोषित CONFIG_PPC64

#समावेश <linux/माला.स>
#समावेश <यंत्र/types.h>
#समावेश <यंत्र/lppaca.h>
#समावेश <यंत्र/mmu.h>
#समावेश <यंत्र/page.h>
#अगर_घोषित CONFIG_PPC_BOOK3E
#समावेश <यंत्र/exception-64e.h>
#अन्यथा
#समावेश <यंत्र/exception-64s.h>
#पूर्ण_अगर
#अगर_घोषित CONFIG_KVM_BOOK3S_64_HANDLER
#समावेश <यंत्र/kvm_book3s_यंत्र.h>
#पूर्ण_अगर
#समावेश <यंत्र/accounting.h>
#समावेश <यंत्र/hmi.h>
#समावेश <यंत्र/cpuidle.h>
#समावेश <यंत्र/atomic.h>
#समावेश <यंत्र/mce.h>

#समावेश <यंत्र-generic/mmiowb_types.h>

रेजिस्टर काष्ठा paca_काष्ठा *local_paca यंत्र("r13");

#अगर defined(CONFIG_DEBUG_PREEMPT) && defined(CONFIG_SMP)
बाह्य अचिन्हित पूर्णांक debug_smp_processor_id(व्योम); /* from linux/smp.h */
/*
 * Add standard checks that preemption cannot occur when using get_paca():
 * otherwise the paca_काष्ठा it poपूर्णांकs to may be the wrong one just after.
 */
#घोषणा get_paca()	((व्योम) debug_smp_processor_id(), local_paca)
#अन्यथा
#घोषणा get_paca()	local_paca
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_PSERIES
#घोषणा get_lppaca()	(get_paca()->lppaca_ptr)
#पूर्ण_अगर

#घोषणा get_slb_shaकरोw()	(get_paca()->slb_shaकरोw_ptr)

काष्ठा task_काष्ठा;
काष्ठा rtas_args;

/*
 * Defines the layout of the paca.
 *
 * This काष्ठाure is not directly accessed by firmware or the service
 * processor.
 */
काष्ठा paca_काष्ठा अणु
#अगर_घोषित CONFIG_PPC_PSERIES
	/*
	 * Because hw_cpu_id, unlike other paca fields, is accessed
	 * routinely from other CPUs (from the IRQ code), we stick to
	 * पढ़ो-only (after boot) fields in the first cacheline to
	 * aव्योम cacheline bouncing.
	 */

	काष्ठा lppaca *lppaca_ptr;	/* Poपूर्णांकer to LpPaca क्रम PLIC */
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

	/*
	 * MAGIC: the spinlock functions in arch/घातerpc/lib/locks.c 
	 * load lock_token and paca_index with a single lwz
	 * inकाष्ठाion.  They must travel together and be properly
	 * aligned.
	 */
#अगर_घोषित __BIG_ENDIAN__
	u16 lock_token;			/* Constant 0x8000, used in locks */
	u16 paca_index;			/* Logical processor number */
#अन्यथा
	u16 paca_index;			/* Logical processor number */
	u16 lock_token;			/* Constant 0x8000, used in locks */
#पूर्ण_अगर

	u64 kernel_toc;			/* Kernel TOC address */
	u64 kernelbase;			/* Base address of kernel */
	u64 kernel_msr;			/* MSR जबतक running in kernel */
	व्योम *emergency_sp;		/* poपूर्णांकer to emergency stack */
	u64 data_offset;		/* per cpu data offset */
	s16 hw_cpu_id;			/* Physical processor number */
	u8 cpu_start;			/* At startup, processor spins until */
					/* this becomes non-zero. */
	u8 kexec_state;		/* set when kexec करोwn has irqs off */
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा slb_shaकरोw *slb_shaकरोw_ptr;
	काष्ठा dtl_entry *dispatch_log;
	काष्ठा dtl_entry *dispatch_log_end;
#पूर्ण_अगर
	u64 dscr_शेष;		/* per-CPU शेष DSCR */

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/*
	 * Now, starting in cacheline 2, the exception save areas
	 */
	/* used क्रम most पूर्णांकerrupts/exceptions */
	u64 exgen[EX_SIZE] __attribute__((aligned(0x80)));

	/* SLB related definitions */
	u16 vदो_स्मृति_sllp;
	u8 slb_cache_ptr;
	u8 stab_rr;			/* stab/slb round-robin counter */
#अगर_घोषित CONFIG_DEBUG_VM
	u8 in_kernel_slb_handler;
#पूर्ण_अगर
	u32 slb_used_biपंचांगap;		/* Biपंचांगaps क्रम first 32 SLB entries. */
	u32 slb_kern_biपंचांगap;
	u32 slb_cache[SLB_CACHE_ENTRIES];
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */

#अगर_घोषित CONFIG_PPC_BOOK3E
	u64 exgen[8] __aligned(0x40);
	/* Keep pgd in the same cacheline as the start of extlb */
	pgd_t *pgd __aligned(0x40); /* Current PGD */
	pgd_t *kernel_pgd;		/* Kernel PGD */

	/* Shared by all thपढ़ोs of a core -- poपूर्णांकs to tcd of first thपढ़ो */
	काष्ठा tlb_core_data *tcd_ptr;

	/*
	 * We can have up to 3 levels of reentrancy in the TLB miss handler,
	 * in each of four exception levels (normal, crit, mcheck, debug).
	 */
	u64 extlb[12][EX_TLB_SIZE / माप(u64)];
	u64 exmc[8];		/* used क्रम machine checks */
	u64 excrit[8];		/* used क्रम crit पूर्णांकerrupts */
	u64 exdbg[8];		/* used क्रम debug पूर्णांकerrupts */

	/* Kernel stack poपूर्णांकers क्रम use by special exceptions */
	व्योम *mc_kstack;
	व्योम *crit_kstack;
	व्योम *dbg_kstack;

	काष्ठा tlb_core_data tcd;
#पूर्ण_अगर /* CONFIG_PPC_BOOK3E */

#अगर_घोषित CONFIG_PPC_BOOK3S
	mm_context_id_t mm_ctx_id;
#अगर_घोषित CONFIG_PPC_MM_SLICES
	अचिन्हित अक्षर mm_ctx_low_slices_psize[BITS_PER_LONG / BITS_PER_BYTE];
	अचिन्हित अक्षर mm_ctx_high_slices_psize[SLICE_ARRAY_SIZE];
	अचिन्हित दीर्घ mm_ctx_slb_addr_limit;
#अन्यथा
	u16 mm_ctx_user_psize;
	u16 mm_ctx_sllp;
#पूर्ण_अगर
#पूर्ण_अगर

	/*
	 * then miscellaneous पढ़ो-ग_लिखो fields
	 */
	काष्ठा task_काष्ठा *__current;	/* Poपूर्णांकer to current */
	u64 kstack;			/* Saved Kernel stack addr */
	u64 saved_r1;			/* r1 save क्रम RTAS calls or PM or EE=0 */
	u64 saved_msr;			/* MSR saved here by enter_rtas */
#अगर_घोषित CONFIG_PPC_BOOK3E
	u16 trap_save;			/* Used when bad stack is encountered */
#पूर्ण_अगर
	u8 irq_soft_mask;		/* mask क्रम irq soft masking */
	u8 irq_happened;		/* irq happened जबतक soft-disabled */
	u8 irq_work_pending;		/* IRQ_WORK पूर्णांकerrupt जबतक soft-disable */
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	u8 pmcregs_in_use;		/* pseries माला_दो this in lppaca */
#पूर्ण_अगर
	u64 sprg_vdso;			/* Saved user-visible sprg */
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	u64 पंचांग_scratch;                 /* TM scratch area क्रम reclaim */
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_POWERNV
	/* PowerNV idle fields */
	/* PNV_CORE_IDLE_* bits, all siblings work on thपढ़ो 0 paca */
	अचिन्हित दीर्घ idle_state;
	जोड़ अणु
		/* P7/P8 specअगरic fields */
		काष्ठा अणु
			/* PNV_THREAD_RUNNING/NAP/SLEEP	*/
			u8 thपढ़ो_idle_state;
			/* Mask to denote subcore sibling thपढ़ोs */
			u8 subcore_sibling_mask;
		पूर्ण;

		/* P9 specअगरic fields */
		काष्ठा अणु
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
			/* The PSSCR value that the kernel requested beक्रमe going to stop */
			u64 requested_psscr;
			/* Flag to request this thपढ़ो not to stop */
			atomic_t करोnt_stop;
#पूर्ण_अगर
		पूर्ण;
	पूर्ण;
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* Non-maskable exceptions that are not perक्रमmance critical */
	u64 exnmi[EX_SIZE];	/* used क्रम प्रणाली reset (nmi) */
	u64 exmc[EX_SIZE];	/* used क्रम machine checks */
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* Exclusive stacks क्रम प्रणाली reset and machine check exception. */
	व्योम *nmi_emergency_sp;
	व्योम *mc_emergency_sp;

	u16 in_nmi;			/* In nmi handler */

	/*
	 * Flag to check whether we are in machine check early handler
	 * and alपढ़ोy using emergency stack.
	 */
	u16 in_mce;
	u8 hmi_event_available;		/* HMI event is available */
	u8 hmi_p9_special_emu;		/* HMI P9 special emulation */
	u32 hmi_irqs;			/* HMI irq stat */
#पूर्ण_अगर
	u8 ftrace_enabled;		/* Hard disable ftrace */

	/* Stuff क्रम accurate समय accounting */
	काष्ठा cpu_accounting_data accounting;
	u64 dtl_ridx;			/* पढ़ो index in dispatch log */
	काष्ठा dtl_entry *dtl_curr;	/* poपूर्णांकer corresponding to dtl_ridx */

#अगर_घोषित CONFIG_KVM_BOOK3S_HANDLER
#अगर_घोषित CONFIG_KVM_BOOK3S_PR_POSSIBLE
	/* We use this to store guest state in */
	काष्ठा kvmppc_book3s_shaकरोw_vcpu shaकरोw_vcpu;
#पूर्ण_अगर
	काष्ठा kvmppc_host_state kvm_hstate;
#अगर_घोषित CONFIG_KVM_BOOK3S_HV_POSSIBLE
	/*
	 * Biपंचांगap क्रम sibling subcore status. See kvm/book3s_hv_ras.c क्रम
	 * more details
	 */
	काष्ठा sibling_subcore_state *sibling_subcore_state;
#पूर्ण_अगर
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/*
	 * rfi fallback flush must be in its own cacheline to prevent
	 * other paca data leaking पूर्णांकo the L1d
	 */
	u64 exrfi[EX_SIZE] __aligned(0x80);
	व्योम *rfi_flush_fallback_area;
	u64 l1d_flush_size;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_PSERIES
	काष्ठा rtas_args *rtas_args_reentrant;
	u8 *mce_data_buf;		/* buffer to hold per cpu rtas errlog */
#पूर्ण_अगर /* CONFIG_PPC_PSERIES */

#अगर_घोषित CONFIG_PPC_BOOK3S_64
	/* Capture SLB related old contents in MCE handler. */
	काष्ठा slb_entry *mce_faulty_slbs;
	u16 slb_save_cache_ptr;
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */
#अगर_घोषित CONFIG_STACKPROTECTOR
	अचिन्हित दीर्घ canary;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MMIOWB
	काष्ठा mmiowb_state mmiowb_state;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	काष्ठा mce_info *mce_info;
#पूर्ण_अगर /* CONFIG_PPC_BOOK3S_64 */
पूर्ण ____cacheline_aligned;

बाह्य व्योम copy_mm_to_paca(काष्ठा mm_काष्ठा *mm);
बाह्य काष्ठा paca_काष्ठा **paca_ptrs;
बाह्य व्योम initialise_paca(काष्ठा paca_काष्ठा *new_paca, पूर्णांक cpu);
बाह्य व्योम setup_paca(काष्ठा paca_काष्ठा *new_paca);
बाह्य व्योम allocate_paca_ptrs(व्योम);
बाह्य व्योम allocate_paca(पूर्णांक cpu);
बाह्य व्योम मुक्त_unused_pacas(व्योम);

#अन्यथा /* CONFIG_PPC64 */

अटल अंतरभूत व्योम allocate_paca_ptrs(व्योम) अणु पूर्ण
अटल अंतरभूत व्योम allocate_paca(पूर्णांक cpu) अणु पूर्ण
अटल अंतरभूत व्योम मुक्त_unused_pacas(व्योम) अणु पूर्ण

#पूर्ण_अगर /* CONFIG_PPC64 */

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* _ASM_POWERPC_PACA_H */
