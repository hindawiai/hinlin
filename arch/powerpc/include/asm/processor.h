<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
#अगर_अघोषित _ASM_POWERPC_PROCESSOR_H
#घोषणा _ASM_POWERPC_PROCESSOR_H

/*
 * Copyright (C) 2001 PPC 64 Team, IBM Corp
 */

#समावेश <vdso/processor.h>

#समावेश <यंत्र/reg.h>

#अगर_घोषित CONFIG_VSX
#घोषणा TS_FPRWIDTH 2

#अगर_घोषित __BIG_ENDIAN__
#घोषणा TS_FPROFFSET 0
#घोषणा TS_VSRLOWOFFSET 1
#अन्यथा
#घोषणा TS_FPROFFSET 1
#घोषणा TS_VSRLOWOFFSET 0
#पूर्ण_अगर

#अन्यथा
#घोषणा TS_FPRWIDTH 1
#घोषणा TS_FPROFFSET 0
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC64
/* Default SMT priority is set to 3. Use 11- 13bits to save priority. */
#घोषणा PPR_PRIORITY 3
#अगर_घोषित __ASSEMBLY__
#घोषणा DEFAULT_PPR (PPR_PRIORITY << 50)
#अन्यथा
#घोषणा DEFAULT_PPR ((u64)PPR_PRIORITY << 50)
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* CONFIG_PPC64 */

#अगर_अघोषित __ASSEMBLY__
#समावेश <linux/types.h>
#समावेश <linux/thपढ़ो_info.h>
#समावेश <यंत्र/ptrace.h>
#समावेश <यंत्र/hw_अवरोधpoपूर्णांक.h>

/* We करो _not_ want to define new machine types at all, those must die
 * in favor of using the device-tree
 * -- BenH.
 */

/* PREP sub-platक्रमm types. Unused */
#घोषणा _PREP_Motorola	0x01	/* motorola prep */
#घोषणा _PREP_Firm	0x02	/* firmworks prep */
#घोषणा _PREP_IBM	0x00	/* ibm prep */
#घोषणा _PREP_Bull	0x03	/* bull prep */

/* CHRP sub-platक्रमm types. These are arbitrary */
#घोषणा _CHRP_Motorola	0x04	/* motorola chrp, the cobra */
#घोषणा _CHRP_IBM	0x05	/* IBM chrp, the दीर्घtrail and दीर्घtrail 2 */
#घोषणा _CHRP_Pegasos	0x06	/* Genesi/bplan's Pegasos and Pegasos2 */
#घोषणा _CHRP_briq	0x07	/* TotalImpact's briQ */

#अगर defined(__KERNEL__) && defined(CONFIG_PPC32)

बाह्य पूर्णांक _chrp_type;

#पूर्ण_अगर /* defined(__KERNEL__) && defined(CONFIG_PPC32) */

#अगर_घोषित __KERNEL__

#अगर_घोषित CONFIG_PPC64
#समावेश <यंत्र/task_size_64.h>
#अन्यथा
#समावेश <यंत्र/task_size_32.h>
#पूर्ण_अगर

काष्ठा task_काष्ठा;
व्योम start_thपढ़ो(काष्ठा pt_regs *regs, अचिन्हित दीर्घ fdptr, अचिन्हित दीर्घ sp);
व्योम release_thपढ़ो(काष्ठा task_काष्ठा *);

#घोषणा TS_FPR(i) fp_state.fpr[i][TS_FPROFFSET]
#घोषणा TS_CKFPR(i) ckfp_state.fpr[i][TS_FPROFFSET]

/* FP and VSX 0-31 रेजिस्टर set */
काष्ठा thपढ़ो_fp_state अणु
	u64	fpr[32][TS_FPRWIDTH] __attribute__((aligned(16)));
	u64	fpscr;		/* Floating poपूर्णांक status */
पूर्ण;

/* Complete AltiVec रेजिस्टर set including VSCR */
काष्ठा thपढ़ो_vr_state अणु
	vector128	vr[32] __attribute__((aligned(16)));
	vector128	vscr __attribute__((aligned(16)));
पूर्ण;

काष्ठा debug_reg अणु
#अगर_घोषित CONFIG_PPC_ADV_DEBUG_REGS
	/*
	 * The following help to manage the use of Debug Control Registers
	 * om the BookE platक्रमms.
	 */
	uपूर्णांक32_t	dbcr0;
	uपूर्णांक32_t	dbcr1;
#अगर_घोषित CONFIG_BOOKE
	uपूर्णांक32_t	dbcr2;
#पूर्ण_अगर
	/*
	 * The stored value of the DBSR रेजिस्टर will be the value at the
	 * last debug पूर्णांकerrupt. This रेजिस्टर can only be पढ़ो from the
	 * user (will never be written to) and has value जबतक helping to
	 * describe the reason क्रम the last debug trap.  Torez
	 */
	uपूर्णांक32_t	dbsr;
	/*
	 * The following will contain addresses used by debug applications
	 * to help trace and trap on particular address locations.
	 * The bits in the Debug Control Registers above help define which
	 * of the following रेजिस्टरs will contain valid data and/or addresses.
	 */
	अचिन्हित दीर्घ	iac1;
	अचिन्हित दीर्घ	iac2;
#अगर CONFIG_PPC_ADV_DEBUG_IACS > 2
	अचिन्हित दीर्घ	iac3;
	अचिन्हित दीर्घ	iac4;
#पूर्ण_अगर
	अचिन्हित दीर्घ	dac1;
	अचिन्हित दीर्घ	dac2;
#अगर CONFIG_PPC_ADV_DEBUG_DVCS > 0
	अचिन्हित दीर्घ	dvc1;
	अचिन्हित दीर्घ	dvc2;
#पूर्ण_अगर
#पूर्ण_अगर
पूर्ण;

काष्ठा thपढ़ो_काष्ठा अणु
	अचिन्हित दीर्घ	ksp;		/* Kernel stack poपूर्णांकer */

#अगर_घोषित CONFIG_PPC64
	अचिन्हित दीर्घ	ksp_vsid;
#पूर्ण_अगर
	काष्ठा pt_regs	*regs;		/* Poपूर्णांकer to saved रेजिस्टर state */
#अगर_घोषित CONFIG_BOOKE
	/* BookE base exception scratch space; align on cacheline */
	अचिन्हित दीर्घ	normsave[8] ____cacheline_aligned;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC32
	व्योम		*pgdir;		/* root of page-table tree */
#अगर_घोषित CONFIG_PPC_RTAS
	अचिन्हित दीर्घ	rtas_sp;	/* stack poपूर्णांकer क्रम when in RTAS */
#पूर्ण_अगर
#अगर defined(CONFIG_PPC_BOOK3S_32) && defined(CONFIG_PPC_KUAP)
	अचिन्हित दीर्घ	kuap;		/* खोलोed segments क्रम user access */
#पूर्ण_अगर
	अचिन्हित दीर्घ	srr0;
	अचिन्हित दीर्घ	srr1;
	अचिन्हित दीर्घ	dar;
	अचिन्हित दीर्घ	dsisr;
#अगर_घोषित CONFIG_PPC_BOOK3S_32
	अचिन्हित दीर्घ	r0, r3, r4, r5, r6, r8, r9, r11;
	अचिन्हित दीर्घ	lr, ctr;
#पूर्ण_अगर
#पूर्ण_अगर /* CONFIG_PPC32 */
	/* Debug Registers */
	काष्ठा debug_reg debug;
#अगर_घोषित CONFIG_PPC_FPU_REGS
	काष्ठा thपढ़ो_fp_state	fp_state;
	काष्ठा thपढ़ो_fp_state	*fp_save_area;
#पूर्ण_अगर
	पूर्णांक		fpexc_mode;	/* भग्नing-poपूर्णांक exception mode */
	अचिन्हित पूर्णांक	align_ctl;	/* alignment handling control */
#अगर_घोषित CONFIG_HAVE_HW_BREAKPOINT
	काष्ठा perf_event *ptrace_bps[HBP_NUM_MAX];
	/*
	 * Helps identअगरy source of single-step exception and subsequent
	 * hw-अवरोधpoपूर्णांक enablement
	 */
	काष्ठा perf_event *last_hit_ubp[HBP_NUM_MAX];
#पूर्ण_अगर /* CONFIG_HAVE_HW_BREAKPOINT */
	काष्ठा arch_hw_अवरोधpoपूर्णांक hw_brk[HBP_NUM_MAX]; /* hardware अवरोधpoपूर्णांक info */
	अचिन्हित दीर्घ	trap_nr;	/* last trap # on this thपढ़ो */
	u8 load_slb;			/* Ages out SLB preload cache entries */
	u8 load_fp;
#अगर_घोषित CONFIG_ALTIVEC
	u8 load_vec;
	काष्ठा thपढ़ो_vr_state vr_state;
	काष्ठा thपढ़ो_vr_state *vr_save_area;
	अचिन्हित दीर्घ	vrsave;
	पूर्णांक		used_vr;	/* set अगर process has used altivec */
#पूर्ण_अगर /* CONFIG_ALTIVEC */
#अगर_घोषित CONFIG_VSX
	/* VSR status */
	पूर्णांक		used_vsr;	/* set अगर process has used VSX */
#पूर्ण_अगर /* CONFIG_VSX */
#अगर_घोषित CONFIG_SPE
	अचिन्हित दीर्घ	evr[32];	/* upper 32-bits of SPE regs */
	u64		acc;		/* Accumulator */
	अचिन्हित दीर्घ	spefscr;	/* SPE & eFP status */
	अचिन्हित दीर्घ	spefscr_last;	/* SPEFSCR value on last prctl
					   call or trap वापस */
	पूर्णांक		used_spe;	/* set अगर process has used spe */
#पूर्ण_अगर /* CONFIG_SPE */
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
	u8	load_पंचांग;
	u64		पंचांग_tfhar;	/* Transaction fail handler addr */
	u64		पंचांग_texasr;	/* Transaction exception & summary */
	u64		पंचांग_tfiar;	/* Transaction fail instr address reg */
	काष्ठा pt_regs	ckpt_regs;	/* Checkpoपूर्णांकed रेजिस्टरs */

	अचिन्हित दीर्घ	पंचांग_tar;
	अचिन्हित दीर्घ	पंचांग_ppr;
	अचिन्हित दीर्घ	पंचांग_dscr;
	अचिन्हित दीर्घ   पंचांग_amr;

	/*
	 * Checkpoपूर्णांकed FP and VSX 0-31 रेजिस्टर set.
	 *
	 * When a transaction is active/संकेतled/scheduled etc., *regs is the
	 * most recent set of/speculated GPRs with ckpt_regs being the older
	 * checkpoपूर्णांकed regs to which we roll back अगर transaction पातs.
	 *
	 * These are analogous to how ckpt_regs and pt_regs work
	 */
	काष्ठा thपढ़ो_fp_state ckfp_state; /* Checkpoपूर्णांकed FP state */
	काष्ठा thपढ़ो_vr_state ckvr_state; /* Checkpoपूर्णांकed VR state */
	अचिन्हित दीर्घ	ckvrsave; /* Checkpoपूर्णांकed VRSAVE */
#पूर्ण_अगर /* CONFIG_PPC_TRANSACTIONAL_MEM */
#अगर_घोषित CONFIG_KVM_BOOK3S_32_HANDLER
	व्योम*		kvm_shaकरोw_vcpu; /* KVM पूर्णांकernal data */
#पूर्ण_अगर /* CONFIG_KVM_BOOK3S_32_HANDLER */
#अगर defined(CONFIG_KVM) && defined(CONFIG_BOOKE)
	काष्ठा kvm_vcpu	*kvm_vcpu;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC64
	अचिन्हित दीर्घ	dscr;
	अचिन्हित दीर्घ	fscr;
	/*
	 * This member element dscr_inherit indicates that the process
	 * has explicitly attempted and changed the DSCR रेजिस्टर value
	 * क्रम itself. Hence kernel wont use the शेष CPU DSCR value
	 * contained in the PACA काष्ठाure anymore during process context
	 * चयन. Once this variable is set, this behaviour will also be
	 * inherited to all the children of this process from that poपूर्णांक
	 * onwards.
	 */
	पूर्णांक		dscr_inherit;
	अचिन्हित दीर्घ	tidr;
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_64
	अचिन्हित दीर्घ	tar;
	अचिन्हित दीर्घ	ebbrr;
	अचिन्हित दीर्घ	ebbhr;
	अचिन्हित दीर्घ	bescr;
	अचिन्हित दीर्घ	siar;
	अचिन्हित दीर्घ	sdar;
	अचिन्हित दीर्घ	sier;
	अचिन्हित दीर्घ	mmcr2;
	अचिन्हित 	mmcr0;

	अचिन्हित 	used_ebb;
	अचिन्हित दीर्घ   mmcr3;
	अचिन्हित दीर्घ   sier2;
	अचिन्हित दीर्घ   sier3;

#पूर्ण_अगर
पूर्ण;

#घोषणा ARCH_MIN_TASKALIGN 16

#घोषणा INIT_SP		(माप(init_stack) + (अचिन्हित दीर्घ) &init_stack)
#घोषणा INIT_SP_LIMIT	((अचिन्हित दीर्घ)&init_stack)

#अगर_घोषित CONFIG_SPE
#घोषणा SPEFSCR_INIT \
	.spefscr = SPEFSCR_FINVE | SPEFSCR_FDBZE | SPEFSCR_FUNFE | SPEFSCR_FOVFE, \
	.spefscr_last = SPEFSCR_FINVE | SPEFSCR_FDBZE | SPEFSCR_FUNFE | SPEFSCR_FOVFE,
#अन्यथा
#घोषणा SPEFSCR_INIT
#पूर्ण_अगर

#अगर_घोषित CONFIG_PPC32
#घोषणा INIT_THREAD अणु \
	.ksp = INIT_SP, \
	.pgdir = swapper_pg_dir, \
	.fpexc_mode = MSR_FE0 | MSR_FE1, \
	SPEFSCR_INIT \
पूर्ण
#अन्यथा
#घोषणा INIT_THREAD  अणु \
	.ksp = INIT_SP, \
	.fpexc_mode = 0, \
पूर्ण
#पूर्ण_अगर

#घोषणा task_pt_regs(tsk)	((tsk)->thपढ़ो.regs)

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा KSTK_EIP(tsk)  ((tsk)->thपढ़ो.regs? (tsk)->thपढ़ो.regs->nip: 0)
#घोषणा KSTK_ESP(tsk)  ((tsk)->thपढ़ो.regs? (tsk)->thपढ़ो.regs->gpr[1]: 0)

/* Get/set भग्नing-poपूर्णांक exception mode */
#घोषणा GET_FPEXC_CTL(tsk, adr) get_fpexc_mode((tsk), (adr))
#घोषणा SET_FPEXC_CTL(tsk, val) set_fpexc_mode((tsk), (val))

बाह्य पूर्णांक get_fpexc_mode(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ adr);
बाह्य पूर्णांक set_fpexc_mode(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक val);

#घोषणा GET_ENDIAN(tsk, adr) get_endian((tsk), (adr))
#घोषणा SET_ENDIAN(tsk, val) set_endian((tsk), (val))

बाह्य पूर्णांक get_endian(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ adr);
बाह्य पूर्णांक set_endian(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक val);

#घोषणा GET_UNALIGN_CTL(tsk, adr)	get_unalign_ctl((tsk), (adr))
#घोषणा SET_UNALIGN_CTL(tsk, val)	set_unalign_ctl((tsk), (val))

बाह्य पूर्णांक get_unalign_ctl(काष्ठा task_काष्ठा *tsk, अचिन्हित दीर्घ adr);
बाह्य पूर्णांक set_unalign_ctl(काष्ठा task_काष्ठा *tsk, अचिन्हित पूर्णांक val);

बाह्य व्योम load_fp_state(काष्ठा thपढ़ो_fp_state *fp);
बाह्य व्योम store_fp_state(काष्ठा thपढ़ो_fp_state *fp);
बाह्य व्योम load_vr_state(काष्ठा thपढ़ो_vr_state *vr);
बाह्य व्योम store_vr_state(काष्ठा thपढ़ो_vr_state *vr);

अटल अंतरभूत अचिन्हित पूर्णांक __unpack_fe01(अचिन्हित दीर्घ msr_bits)
अणु
	वापस ((msr_bits & MSR_FE0) >> 10) | ((msr_bits & MSR_FE1) >> 8);
पूर्ण

अटल अंतरभूत अचिन्हित दीर्घ __pack_fe01(अचिन्हित पूर्णांक fpmode)
अणु
	वापस ((fpmode << 10) & MSR_FE0) | ((fpmode << 8) & MSR_FE1);
पूर्ण

#अगर_घोषित CONFIG_PPC64

#घोषणा spin_begin()	HMT_low()

#घोषणा spin_cpu_relax()	barrier()

#घोषणा spin_end()	HMT_medium()

#घोषणा spin_until_cond(cond)					\
करो अणु								\
	अगर (unlikely(!(cond))) अणु				\
		spin_begin();					\
		करो अणु						\
			spin_cpu_relax();			\
		पूर्ण जबतक (!(cond));				\
		spin_end();					\
	पूर्ण							\
पूर्ण जबतक (0)

#पूर्ण_अगर

/* Check that a certain kernel stack poपूर्णांकer is valid in task_काष्ठा p */
पूर्णांक validate_sp(अचिन्हित दीर्घ sp, काष्ठा task_काष्ठा *p,
                       अचिन्हित दीर्घ nbytes);

/*
 * Prefetch macros.
 */
#घोषणा ARCH_HAS_PREFETCH
#घोषणा ARCH_HAS_PREFETCHW
#घोषणा ARCH_HAS_SPINLOCK_PREFETCH

अटल अंतरभूत व्योम prefetch(स्थिर व्योम *x)
अणु
	अगर (unlikely(!x))
		वापस;

	__यंत्र__ __अस्थिर__ ("dcbt 0,%0" : : "r" (x));
पूर्ण

अटल अंतरभूत व्योम prefetchw(स्थिर व्योम *x)
अणु
	अगर (unlikely(!x))
		वापस;

	__यंत्र__ __अस्थिर__ ("dcbtst 0,%0" : : "r" (x));
पूर्ण

#घोषणा spin_lock_prefetch(x)	prefetchw(x)

#घोषणा HAVE_ARCH_PICK_MMAP_LAYOUT

/* यंत्र stubs */
बाह्य अचिन्हित दीर्घ isa300_idle_stop_noloss(अचिन्हित दीर्घ psscr_val);
बाह्य अचिन्हित दीर्घ isa300_idle_stop_mayloss(अचिन्हित दीर्घ psscr_val);
बाह्य अचिन्हित दीर्घ isa206_idle_insn_mayloss(अचिन्हित दीर्घ type);
#अगर_घोषित CONFIG_PPC_970_NAP
बाह्य व्योम घातer4_idle_nap(व्योम);
व्योम घातer4_idle_nap_वापस(व्योम);
#पूर्ण_अगर

बाह्य अचिन्हित दीर्घ cpuidle_disable;
क्रमागत idle_boot_override अणुIDLE_NO_OVERRIDE = 0, IDLE_POWERSAVE_OFFपूर्ण;

बाह्य पूर्णांक घातersave_nap;	/* set अगर nap mode can be used in idle loop */

बाह्य व्योम घातer7_idle_type(अचिन्हित दीर्घ type);
बाह्य व्योम arch300_idle_type(अचिन्हित दीर्घ stop_psscr_val,
			      अचिन्हित दीर्घ stop_psscr_mask);

बाह्य पूर्णांक fix_alignment(काष्ठा pt_regs *);

#अगर_घोषित CONFIG_PPC64
/*
 * We handle most unaligned accesses in hardware. On the other hand 
 * unaligned DMA can be very expensive on some ppc64 IO chips (it करोes
 * घातers of 2 ग_लिखोs until it reaches sufficient alignment).
 *
 * Based on this we disable the IP header alignment in network drivers.
 */
#घोषणा NET_IP_ALIGN	0
#पूर्ण_अगर

पूर्णांक करो_mathemu(काष्ठा pt_regs *regs);

#पूर्ण_अगर /* __KERNEL__ */
#पूर्ण_अगर /* __ASSEMBLY__ */
#पूर्ण_अगर /* _ASM_POWERPC_PROCESSOR_H */
