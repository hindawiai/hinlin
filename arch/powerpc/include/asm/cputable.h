<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित __ASM_POWERPC_CPUTABLE_H
#घोषणा __ASM_POWERPC_CPUTABLE_H


#समावेश <linux/types.h>
#समावेश <uapi/यंत्र/cputable.h>
#समावेश <यंत्र/यंत्र-स्थिर.h>

#अगर_अघोषित __ASSEMBLY__

/* This काष्ठाure can grow, it's real size is used by head.S code
 * via the mkdefs mechanism.
 */
काष्ठा cpu_spec;

प्रकार	व्योम (*cpu_setup_t)(अचिन्हित दीर्घ offset, काष्ठा cpu_spec* spec);
प्रकार	व्योम (*cpu_restore_t)(व्योम);

क्रमागत घातerpc_pmc_type अणु
	PPC_PMC_DEFAULT = 0,
	PPC_PMC_IBM = 1,
	PPC_PMC_PA6T = 2,
	PPC_PMC_G4 = 3,
पूर्ण;

काष्ठा pt_regs;

बाह्य पूर्णांक machine_check_generic(काष्ठा pt_regs *regs);
बाह्य पूर्णांक machine_check_4xx(काष्ठा pt_regs *regs);
बाह्य पूर्णांक machine_check_440A(काष्ठा pt_regs *regs);
बाह्य पूर्णांक machine_check_e500mc(काष्ठा pt_regs *regs);
बाह्य पूर्णांक machine_check_e500(काष्ठा pt_regs *regs);
बाह्य पूर्णांक machine_check_47x(काष्ठा pt_regs *regs);
पूर्णांक machine_check_8xx(काष्ठा pt_regs *regs);
पूर्णांक machine_check_83xx(काष्ठा pt_regs *regs);

बाह्य व्योम cpu_करोwn_flush_e500v2(व्योम);
बाह्य व्योम cpu_करोwn_flush_e500mc(व्योम);
बाह्य व्योम cpu_करोwn_flush_e5500(व्योम);
बाह्य व्योम cpu_करोwn_flush_e6500(व्योम);

/* NOTE WELL: Update identअगरy_cpu() अगर fields are added or हटाओd! */
काष्ठा cpu_spec अणु
	/* CPU is matched via (PVR & pvr_mask) == pvr_value */
	अचिन्हित पूर्णांक	pvr_mask;
	अचिन्हित पूर्णांक	pvr_value;

	अक्षर		*cpu_name;
	अचिन्हित दीर्घ	cpu_features;		/* Kernel features */
	अचिन्हित पूर्णांक	cpu_user_features;	/* Userland features */
	अचिन्हित पूर्णांक	cpu_user_features2;	/* Userland features v2 */
	अचिन्हित पूर्णांक	mmu_features;		/* MMU features */

	/* cache line sizes */
	अचिन्हित पूर्णांक	icache_bsize;
	अचिन्हित पूर्णांक	dcache_bsize;

	/* flush caches inside the current cpu */
	व्योम (*cpu_करोwn_flush)(व्योम);

	/* number of perक्रमmance monitor counters */
	अचिन्हित पूर्णांक	num_pmcs;
	क्रमागत घातerpc_pmc_type pmc_type;

	/* this is called to initialize various CPU bits like L1 cache,
	 * BHT, SPD, etc... from head.S beक्रमe branching to identअगरy_machine
	 */
	cpu_setup_t	cpu_setup;
	/* Used to restore cpu setup on secondary processors and at resume */
	cpu_restore_t	cpu_restore;

	/* Used by oprofile userspace to select the right counters */
	अक्षर		*oprofile_cpu_type;

	/* Name of processor class, क्रम the ELF AT_PLATFORM entry */
	अक्षर		*platक्रमm;

	/* Processor specअगरic machine check handling. Return negative
	 * अगर the error is fatal, 1 अगर it was fully recovered and 0 to
	 * pass up (not CPU originated) */
	पूर्णांक		(*machine_check)(काष्ठा pt_regs *regs);

	/*
	 * Processor specअगरic early machine check handler which is
	 * called in real mode to handle SLB and TLB errors.
	 */
	दीर्घ		(*machine_check_early)(काष्ठा pt_regs *regs);
पूर्ण;

बाह्य काष्ठा cpu_spec		*cur_cpu_spec;

बाह्य अचिन्हित पूर्णांक __start___ftr_fixup, __stop___ftr_fixup;

बाह्य व्योम set_cur_cpu_spec(काष्ठा cpu_spec *s);
बाह्य काष्ठा cpu_spec *identअगरy_cpu(अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक pvr);
बाह्य व्योम identअगरy_cpu_name(अचिन्हित पूर्णांक pvr);
बाह्य व्योम करो_feature_fixups(अचिन्हित दीर्घ value, व्योम *fixup_start,
			      व्योम *fixup_end);

बाह्य स्थिर अक्षर *घातerpc_base_platक्रमm;

#अगर_घोषित CONFIG_JUMP_LABEL_FEATURE_CHECKS
बाह्य व्योम cpu_feature_keys_init(व्योम);
#अन्यथा
अटल अंतरभूत व्योम cpu_feature_keys_init(व्योम) अणु पूर्ण
#पूर्ण_अगर

#पूर्ण_अगर /* __ASSEMBLY__ */

/* CPU kernel features */

/* Definitions क्रम features that we have on both 32-bit and 64-bit chips */
#घोषणा CPU_FTR_COHERENT_ICACHE		ASM_CONST(0x00000001)
#घोषणा CPU_FTR_ALTIVEC			ASM_CONST(0x00000002)
#घोषणा CPU_FTR_DBELL			ASM_CONST(0x00000004)
#घोषणा CPU_FTR_CAN_NAP			ASM_CONST(0x00000008)
#घोषणा CPU_FTR_DEBUG_LVL_EXC		ASM_CONST(0x00000010)
// ASM_CONST(0x00000020) Free
#घोषणा CPU_FTR_FPU_UNAVAILABLE		ASM_CONST(0x00000040)
#घोषणा CPU_FTR_LWSYNC			ASM_CONST(0x00000080)
#घोषणा CPU_FTR_NOEXECUTE		ASM_CONST(0x00000100)
#घोषणा CPU_FTR_EMB_HV			ASM_CONST(0x00000200)

/* Definitions क्रम features that only exist on 32-bit chips */
#अगर_घोषित CONFIG_PPC32
#घोषणा CPU_FTR_L2CR			ASM_CONST(0x00002000)
#घोषणा CPU_FTR_SPEC7450		ASM_CONST(0x00004000)
#घोषणा CPU_FTR_TAU			ASM_CONST(0x00008000)
#घोषणा CPU_FTR_CAN_DOZE		ASM_CONST(0x00010000)
#घोषणा CPU_FTR_L3CR			ASM_CONST(0x00040000)
#घोषणा CPU_FTR_L3_DISABLE_NAP		ASM_CONST(0x00080000)
#घोषणा CPU_FTR_NAP_DISABLE_L2_PR	ASM_CONST(0x00100000)
#घोषणा CPU_FTR_DUAL_PLL_750FX		ASM_CONST(0x00200000)
#घोषणा CPU_FTR_NO_DPM			ASM_CONST(0x00400000)
#घोषणा CPU_FTR_476_DD2			ASM_CONST(0x00800000)
#घोषणा CPU_FTR_NEED_COHERENT		ASM_CONST(0x01000000)
#घोषणा CPU_FTR_NO_BTIC			ASM_CONST(0x02000000)
#घोषणा CPU_FTR_PPC_LE			ASM_CONST(0x04000000)
#घोषणा CPU_FTR_SPE			ASM_CONST(0x10000000)
#घोषणा CPU_FTR_NEED_PAIRED_STWCX	ASM_CONST(0x20000000)
#घोषणा CPU_FTR_INDEXED_DCR		ASM_CONST(0x40000000)

#अन्यथा	/* CONFIG_PPC32 */
/* Define these to 0 क्रम the sake of tests in common code */
#घोषणा CPU_FTR_PPC_LE			(0)
#घोषणा CPU_FTR_SPE			(0)
#पूर्ण_अगर

/*
 * Definitions क्रम the 64-bit processor unique features;
 * on 32-bit, make the names available but defined to be 0.
 */
#अगर_घोषित __घातerpc64__
#घोषणा LONG_ASM_CONST(x)		ASM_CONST(x)
#अन्यथा
#घोषणा LONG_ASM_CONST(x)		0
#पूर्ण_अगर

#घोषणा CPU_FTR_REAL_LE			LONG_ASM_CONST(0x0000000000001000)
#घोषणा CPU_FTR_HVMODE			LONG_ASM_CONST(0x0000000000002000)
#घोषणा CPU_FTR_ARCH_206		LONG_ASM_CONST(0x0000000000008000)
#घोषणा CPU_FTR_ARCH_207S		LONG_ASM_CONST(0x0000000000010000)
#घोषणा CPU_FTR_ARCH_300		LONG_ASM_CONST(0x0000000000020000)
#घोषणा CPU_FTR_MMCRA			LONG_ASM_CONST(0x0000000000040000)
#घोषणा CPU_FTR_CTRL			LONG_ASM_CONST(0x0000000000080000)
#घोषणा CPU_FTR_SMT			LONG_ASM_CONST(0x0000000000100000)
#घोषणा CPU_FTR_PAUSE_ZERO		LONG_ASM_CONST(0x0000000000200000)
#घोषणा CPU_FTR_PURR			LONG_ASM_CONST(0x0000000000400000)
#घोषणा CPU_FTR_CELL_TB_BUG		LONG_ASM_CONST(0x0000000000800000)
#घोषणा CPU_FTR_SPURR			LONG_ASM_CONST(0x0000000001000000)
#घोषणा CPU_FTR_DSCR			LONG_ASM_CONST(0x0000000002000000)
#घोषणा CPU_FTR_VSX			LONG_ASM_CONST(0x0000000004000000)
#घोषणा CPU_FTR_SAO			LONG_ASM_CONST(0x0000000008000000)
#घोषणा CPU_FTR_CP_USE_DCBTZ		LONG_ASM_CONST(0x0000000010000000)
#घोषणा CPU_FTR_UNALIGNED_LD_STD	LONG_ASM_CONST(0x0000000020000000)
#घोषणा CPU_FTR_ASYM_SMT		LONG_ASM_CONST(0x0000000040000000)
#घोषणा CPU_FTR_STCX_CHECKS_ADDRESS	LONG_ASM_CONST(0x0000000080000000)
#घोषणा CPU_FTR_POPCNTB			LONG_ASM_CONST(0x0000000100000000)
#घोषणा CPU_FTR_POPCNTD			LONG_ASM_CONST(0x0000000200000000)
/* LONG_ASM_CONST(0x0000000400000000) Free */
#घोषणा CPU_FTR_VMX_COPY		LONG_ASM_CONST(0x0000000800000000)
#घोषणा CPU_FTR_TM			LONG_ASM_CONST(0x0000001000000000)
#घोषणा CPU_FTR_CFAR			LONG_ASM_CONST(0x0000002000000000)
#घोषणा	CPU_FTR_HAS_PPR			LONG_ASM_CONST(0x0000004000000000)
#घोषणा CPU_FTR_DAWR			LONG_ASM_CONST(0x0000008000000000)
#घोषणा CPU_FTR_DABRX			LONG_ASM_CONST(0x0000010000000000)
#घोषणा CPU_FTR_PMAO_BUG		LONG_ASM_CONST(0x0000020000000000)
#घोषणा CPU_FTR_POWER9_DD2_1		LONG_ASM_CONST(0x0000080000000000)
#घोषणा CPU_FTR_P9_TM_HV_ASSIST		LONG_ASM_CONST(0x0000100000000000)
#घोषणा CPU_FTR_P9_TM_XER_SO_BUG	LONG_ASM_CONST(0x0000200000000000)
#घोषणा CPU_FTR_P9_TLBIE_STQ_BUG	LONG_ASM_CONST(0x0000400000000000)
#घोषणा CPU_FTR_P9_TIDR			LONG_ASM_CONST(0x0000800000000000)
#घोषणा CPU_FTR_P9_TLBIE_ERAT_BUG	LONG_ASM_CONST(0x0001000000000000)
#घोषणा CPU_FTR_P9_RADIX_PREFETCH_BUG	LONG_ASM_CONST(0x0002000000000000)
#घोषणा CPU_FTR_ARCH_31			LONG_ASM_CONST(0x0004000000000000)
#घोषणा CPU_FTR_DAWR1			LONG_ASM_CONST(0x0008000000000000)

#अगर_अघोषित __ASSEMBLY__

#घोषणा CPU_FTR_PPCAS_ARCH_V2	(CPU_FTR_NOEXECUTE)

/* We only set the altivec features अगर the kernel was compiled with altivec
 * support
 */
#अगर_घोषित CONFIG_ALTIVEC
#घोषणा CPU_FTR_ALTIVEC_COMP	CPU_FTR_ALTIVEC
#घोषणा PPC_FEATURE_HAS_ALTIVEC_COMP PPC_FEATURE_HAS_ALTIVEC
#अन्यथा
#घोषणा CPU_FTR_ALTIVEC_COMP	0
#घोषणा PPC_FEATURE_HAS_ALTIVEC_COMP    0
#पूर्ण_अगर

/* We only set the VSX features अगर the kernel was compiled with VSX
 * support
 */
#अगर_घोषित CONFIG_VSX
#घोषणा CPU_FTR_VSX_COMP	CPU_FTR_VSX
#घोषणा PPC_FEATURE_HAS_VSX_COMP PPC_FEATURE_HAS_VSX
#अन्यथा
#घोषणा CPU_FTR_VSX_COMP	0
#घोषणा PPC_FEATURE_HAS_VSX_COMP    0
#पूर्ण_अगर

/* We only set the spe features अगर the kernel was compiled with spe
 * support
 */
#अगर_घोषित CONFIG_SPE
#घोषणा CPU_FTR_SPE_COMP	CPU_FTR_SPE
#घोषणा PPC_FEATURE_HAS_SPE_COMP PPC_FEATURE_HAS_SPE
#घोषणा PPC_FEATURE_HAS_EFP_SINGLE_COMP PPC_FEATURE_HAS_EFP_SINGLE
#घोषणा PPC_FEATURE_HAS_EFP_DOUBLE_COMP PPC_FEATURE_HAS_EFP_DOUBLE
#अन्यथा
#घोषणा CPU_FTR_SPE_COMP	0
#घोषणा PPC_FEATURE_HAS_SPE_COMP    0
#घोषणा PPC_FEATURE_HAS_EFP_SINGLE_COMP 0
#घोषणा PPC_FEATURE_HAS_EFP_DOUBLE_COMP 0
#पूर्ण_अगर

/* We only set the TM feature अगर the kernel was compiled with TM supprt */
#अगर_घोषित CONFIG_PPC_TRANSACTIONAL_MEM
#घोषणा CPU_FTR_TM_COMP			CPU_FTR_TM
#घोषणा PPC_FEATURE2_HTM_COMP		PPC_FEATURE2_HTM
#घोषणा PPC_FEATURE2_HTM_NOSC_COMP	PPC_FEATURE2_HTM_NOSC
#अन्यथा
#घोषणा CPU_FTR_TM_COMP			0
#घोषणा PPC_FEATURE2_HTM_COMP		0
#घोषणा PPC_FEATURE2_HTM_NOSC_COMP	0
#पूर्ण_अगर

/* We need to mark all pages as being coherent अगर we're SMP or we have a
 * 74[45]x and an MPC107 host bridge. Also 83xx and PowerQUICC II
 * require it क्रम PCI "streaming/prefetch" to work properly.
 * This is also required by 52xx family.
 */
#अगर defined(CONFIG_SMP) || defined(CONFIG_MPC10X_BRIDGE) \
	|| defined(CONFIG_PPC_83xx) || defined(CONFIG_8260) \
	|| defined(CONFIG_PPC_MPC52xx)
#घोषणा CPU_FTR_COMMON                  CPU_FTR_NEED_COHERENT
#अन्यथा
#घोषणा CPU_FTR_COMMON                  0
#पूर्ण_अगर

/* The घातersave features NAP & DOZE seems to confuse BDI when
   debugging. So अगर a BDI is used, disable theses
 */
#अगर_अघोषित CONFIG_BDI_SWITCH
#घोषणा CPU_FTR_MAYBE_CAN_DOZE	CPU_FTR_CAN_DOZE
#घोषणा CPU_FTR_MAYBE_CAN_NAP	CPU_FTR_CAN_NAP
#अन्यथा
#घोषणा CPU_FTR_MAYBE_CAN_DOZE	0
#घोषणा CPU_FTR_MAYBE_CAN_NAP	0
#पूर्ण_अगर

#घोषणा CPU_FTRS_603	(CPU_FTR_COMMON | CPU_FTR_MAYBE_CAN_DOZE | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_PPC_LE | CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_604	(CPU_FTR_COMMON | CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_740_NOTAU	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_DOZE | CPU_FTR_L2CR | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_740	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_DOZE | CPU_FTR_L2CR | \
	    CPU_FTR_TAU | CPU_FTR_MAYBE_CAN_NAP | \
	    CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_750	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_DOZE | CPU_FTR_L2CR | \
	    CPU_FTR_TAU | CPU_FTR_MAYBE_CAN_NAP | \
	    CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_750CL	(CPU_FTRS_750)
#घोषणा CPU_FTRS_750FX1	(CPU_FTRS_750 | CPU_FTR_DUAL_PLL_750FX | CPU_FTR_NO_DPM)
#घोषणा CPU_FTRS_750FX2	(CPU_FTRS_750 | CPU_FTR_NO_DPM)
#घोषणा CPU_FTRS_750FX	(CPU_FTRS_750 | CPU_FTR_DUAL_PLL_750FX)
#घोषणा CPU_FTRS_750GX	(CPU_FTRS_750FX)
#घोषणा CPU_FTRS_7400_NOTAU	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_DOZE | CPU_FTR_L2CR | \
	    CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_7400	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_DOZE | CPU_FTR_L2CR | \
	    CPU_FTR_TAU | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_7450_20	(CPU_FTR_COMMON | \
	    CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_L3CR | CPU_FTR_SPEC7450 | \
	    CPU_FTR_NEED_COHERENT | CPU_FTR_PPC_LE | CPU_FTR_NEED_PAIRED_STWCX)
#घोषणा CPU_FTRS_7450_21	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_L3CR | CPU_FTR_SPEC7450 | \
	    CPU_FTR_NAP_DISABLE_L2_PR | CPU_FTR_L3_DISABLE_NAP | \
	    CPU_FTR_NEED_COHERENT | CPU_FTR_PPC_LE | CPU_FTR_NEED_PAIRED_STWCX)
#घोषणा CPU_FTRS_7450_23	(CPU_FTR_COMMON | \
	    CPU_FTR_NEED_PAIRED_STWCX | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_L3CR | CPU_FTR_SPEC7450 | \
	    CPU_FTR_NAP_DISABLE_L2_PR | CPU_FTR_NEED_COHERENT | CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_7455_1	(CPU_FTR_COMMON | \
	    CPU_FTR_NEED_PAIRED_STWCX | \
	    CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | CPU_FTR_L3CR | \
	    CPU_FTR_SPEC7450 | CPU_FTR_NEED_COHERENT | CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_7455_20	(CPU_FTR_COMMON | \
	    CPU_FTR_NEED_PAIRED_STWCX | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_L3CR | CPU_FTR_SPEC7450 | \
	    CPU_FTR_NAP_DISABLE_L2_PR | CPU_FTR_L3_DISABLE_NAP | \
	    CPU_FTR_NEED_COHERENT | CPU_FTR_PPC_LE)
#घोषणा CPU_FTRS_7455	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_L3CR | CPU_FTR_SPEC7450 | CPU_FTR_NAP_DISABLE_L2_PR | \
	    CPU_FTR_NEED_COHERENT | CPU_FTR_PPC_LE | CPU_FTR_NEED_PAIRED_STWCX)
#घोषणा CPU_FTRS_7447_10	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_L3CR | CPU_FTR_SPEC7450 | CPU_FTR_NAP_DISABLE_L2_PR | \
	    CPU_FTR_NEED_COHERENT | CPU_FTR_NO_BTIC | CPU_FTR_PPC_LE | \
	    CPU_FTR_NEED_PAIRED_STWCX)
#घोषणा CPU_FTRS_7447	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_L3CR | CPU_FTR_SPEC7450 | CPU_FTR_NAP_DISABLE_L2_PR | \
	    CPU_FTR_NEED_COHERENT | CPU_FTR_PPC_LE | CPU_FTR_NEED_PAIRED_STWCX)
#घोषणा CPU_FTRS_7447A	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_SPEC7450 | CPU_FTR_NAP_DISABLE_L2_PR | \
	    CPU_FTR_NEED_COHERENT | CPU_FTR_PPC_LE | CPU_FTR_NEED_PAIRED_STWCX)
#घोषणा CPU_FTRS_7448	(CPU_FTR_COMMON | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_L2CR | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_SPEC7450 | CPU_FTR_NAP_DISABLE_L2_PR | \
	    CPU_FTR_PPC_LE | CPU_FTR_NEED_PAIRED_STWCX)
#घोषणा CPU_FTRS_82XX	(CPU_FTR_COMMON | CPU_FTR_MAYBE_CAN_DOZE | CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_G2_LE	(CPU_FTR_COMMON | CPU_FTR_MAYBE_CAN_DOZE | \
	    CPU_FTR_MAYBE_CAN_NAP | CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_E300	(CPU_FTR_MAYBE_CAN_DOZE | \
	    CPU_FTR_MAYBE_CAN_NAP | \
	    CPU_FTR_COMMON  | CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_E300C2	(CPU_FTR_MAYBE_CAN_DOZE | \
	    CPU_FTR_MAYBE_CAN_NAP | \
	    CPU_FTR_COMMON | CPU_FTR_FPU_UNAVAILABLE  | CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_CLASSIC32	(CPU_FTR_COMMON)
#घोषणा CPU_FTRS_8XX	(CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_40X	(CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_44X	(CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_440x6	(CPU_FTR_NOEXECUTE | \
	    CPU_FTR_INDEXED_DCR)
#घोषणा CPU_FTRS_47X	(CPU_FTRS_440x6)
#घोषणा CPU_FTRS_E500	(CPU_FTR_MAYBE_CAN_DOZE | \
	    CPU_FTR_SPE_COMP | CPU_FTR_MAYBE_CAN_NAP | \
	    CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_E500_2	(CPU_FTR_MAYBE_CAN_DOZE | \
	    CPU_FTR_SPE_COMP | CPU_FTR_MAYBE_CAN_NAP | \
	    CPU_FTR_NOEXECUTE)
#घोषणा CPU_FTRS_E500MC	( \
	    CPU_FTR_LWSYNC | CPU_FTR_NOEXECUTE | \
	    CPU_FTR_DBELL | CPU_FTR_DEBUG_LVL_EXC | CPU_FTR_EMB_HV)
/*
 * e5500/e6500 erratum A-006958 is a समयbase bug that can use the
 * same workaround as CPU_FTR_CELL_TB_BUG.
 */
#घोषणा CPU_FTRS_E5500	( \
	    CPU_FTR_LWSYNC | CPU_FTR_NOEXECUTE | \
	    CPU_FTR_DBELL | CPU_FTR_POPCNTB | CPU_FTR_POPCNTD | \
	    CPU_FTR_DEBUG_LVL_EXC | CPU_FTR_EMB_HV | CPU_FTR_CELL_TB_BUG)
#घोषणा CPU_FTRS_E6500	( \
	    CPU_FTR_LWSYNC | CPU_FTR_NOEXECUTE | \
	    CPU_FTR_DBELL | CPU_FTR_POPCNTB | CPU_FTR_POPCNTD | \
	    CPU_FTR_DEBUG_LVL_EXC | CPU_FTR_EMB_HV | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_CELL_TB_BUG | CPU_FTR_SMT)

/* 64-bit CPUs */
#घोषणा CPU_FTRS_PPC970	(CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_CTRL | \
	    CPU_FTR_ALTIVEC_COMP | CPU_FTR_CAN_NAP | CPU_FTR_MMCRA | \
	    CPU_FTR_CP_USE_DCBTZ | CPU_FTR_STCX_CHECKS_ADDRESS | \
	    CPU_FTR_HVMODE | CPU_FTR_DABRX)
#घोषणा CPU_FTRS_POWER5	(CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_CTRL | \
	    CPU_FTR_MMCRA | CPU_FTR_SMT | \
	    CPU_FTR_COHERENT_ICACHE | CPU_FTR_PURR | \
	    CPU_FTR_STCX_CHECKS_ADDRESS | CPU_FTR_POPCNTB | CPU_FTR_DABRX)
#घोषणा CPU_FTRS_POWER6 (CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_CTRL | \
	    CPU_FTR_MMCRA | CPU_FTR_SMT | \
	    CPU_FTR_COHERENT_ICACHE | \
	    CPU_FTR_PURR | CPU_FTR_SPURR | CPU_FTR_REAL_LE | \
	    CPU_FTR_DSCR | CPU_FTR_UNALIGNED_LD_STD | \
	    CPU_FTR_STCX_CHECKS_ADDRESS | CPU_FTR_POPCNTB | CPU_FTR_CFAR | \
	    CPU_FTR_DABRX)
#घोषणा CPU_FTRS_POWER7 (CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_CTRL | CPU_FTR_ARCH_206 |\
	    CPU_FTR_MMCRA | CPU_FTR_SMT | \
	    CPU_FTR_COHERENT_ICACHE | \
	    CPU_FTR_PURR | CPU_FTR_SPURR | CPU_FTR_REAL_LE | \
	    CPU_FTR_DSCR | CPU_FTR_SAO  | CPU_FTR_ASYM_SMT | \
	    CPU_FTR_STCX_CHECKS_ADDRESS | CPU_FTR_POPCNTB | CPU_FTR_POPCNTD | \
	    CPU_FTR_CFAR | CPU_FTR_HVMODE | \
	    CPU_FTR_VMX_COPY | CPU_FTR_HAS_PPR | CPU_FTR_DABRX )
#घोषणा CPU_FTRS_POWER8 (CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_CTRL | CPU_FTR_ARCH_206 |\
	    CPU_FTR_MMCRA | CPU_FTR_SMT | \
	    CPU_FTR_COHERENT_ICACHE | \
	    CPU_FTR_PURR | CPU_FTR_SPURR | CPU_FTR_REAL_LE | \
	    CPU_FTR_DSCR | CPU_FTR_SAO  | \
	    CPU_FTR_STCX_CHECKS_ADDRESS | CPU_FTR_POPCNTB | CPU_FTR_POPCNTD | \
	    CPU_FTR_CFAR | CPU_FTR_HVMODE | CPU_FTR_VMX_COPY | \
	    CPU_FTR_DBELL | CPU_FTR_HAS_PPR | CPU_FTR_DAWR | \
	    CPU_FTR_ARCH_207S | CPU_FTR_TM_COMP )
#घोषणा CPU_FTRS_POWER8E (CPU_FTRS_POWER8 | CPU_FTR_PMAO_BUG)
#घोषणा CPU_FTRS_POWER9 (CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_CTRL | CPU_FTR_ARCH_206 |\
	    CPU_FTR_MMCRA | CPU_FTR_SMT | \
	    CPU_FTR_COHERENT_ICACHE | \
	    CPU_FTR_PURR | CPU_FTR_SPURR | CPU_FTR_REAL_LE | \
	    CPU_FTR_DSCR | CPU_FTR_SAO  | \
	    CPU_FTR_STCX_CHECKS_ADDRESS | CPU_FTR_POPCNTB | CPU_FTR_POPCNTD | \
	    CPU_FTR_CFAR | CPU_FTR_HVMODE | CPU_FTR_VMX_COPY | \
	    CPU_FTR_DBELL | CPU_FTR_HAS_PPR | CPU_FTR_ARCH_207S | \
	    CPU_FTR_TM_COMP | CPU_FTR_ARCH_300 | CPU_FTR_P9_TLBIE_STQ_BUG | \
	    CPU_FTR_P9_TLBIE_ERAT_BUG | CPU_FTR_P9_TIDR)
#घोषणा CPU_FTRS_POWER9_DD2_0 (CPU_FTRS_POWER9 | CPU_FTR_P9_RADIX_PREFETCH_BUG)
#घोषणा CPU_FTRS_POWER9_DD2_1 (CPU_FTRS_POWER9 | \
			       CPU_FTR_P9_RADIX_PREFETCH_BUG | \
			       CPU_FTR_POWER9_DD2_1)
#घोषणा CPU_FTRS_POWER9_DD2_2 (CPU_FTRS_POWER9 | CPU_FTR_POWER9_DD2_1 | \
			       CPU_FTR_P9_TM_HV_ASSIST | \
			       CPU_FTR_P9_TM_XER_SO_BUG)
#घोषणा CPU_FTRS_POWER10 (CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_CTRL | CPU_FTR_ARCH_206 |\
	    CPU_FTR_MMCRA | CPU_FTR_SMT | \
	    CPU_FTR_COHERENT_ICACHE | \
	    CPU_FTR_PURR | CPU_FTR_SPURR | CPU_FTR_REAL_LE | \
	    CPU_FTR_DSCR | CPU_FTR_SAO  | \
	    CPU_FTR_STCX_CHECKS_ADDRESS | CPU_FTR_POPCNTB | CPU_FTR_POPCNTD | \
	    CPU_FTR_CFAR | CPU_FTR_HVMODE | CPU_FTR_VMX_COPY | \
	    CPU_FTR_DBELL | CPU_FTR_HAS_PPR | CPU_FTR_ARCH_207S | \
	    CPU_FTR_ARCH_300 | CPU_FTR_ARCH_31 | \
	    CPU_FTR_DAWR | CPU_FTR_DAWR1)
#घोषणा CPU_FTRS_CELL	(CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_CTRL | \
	    CPU_FTR_ALTIVEC_COMP | CPU_FTR_MMCRA | CPU_FTR_SMT | \
	    CPU_FTR_PAUSE_ZERO  | CPU_FTR_CELL_TB_BUG | CPU_FTR_CP_USE_DCBTZ | \
	    CPU_FTR_UNALIGNED_LD_STD | CPU_FTR_DABRX)
#घोषणा CPU_FTRS_PA6T (CPU_FTR_LWSYNC | \
	    CPU_FTR_PPCAS_ARCH_V2 | CPU_FTR_ALTIVEC_COMP | \
	    CPU_FTR_PURR | CPU_FTR_REAL_LE | CPU_FTR_DABRX)
#घोषणा CPU_FTRS_COMPATIBLE	(CPU_FTR_PPCAS_ARCH_V2)

#अगर_घोषित CONFIG_PPC64
#अगर_घोषित CONFIG_PPC_BOOK3E
#घोषणा CPU_FTRS_POSSIBLE	(CPU_FTRS_E6500 | CPU_FTRS_E5500)
#अन्यथा
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
#घोषणा CPU_FTRS_POSSIBLE	\
	    (CPU_FTRS_POWER7 | CPU_FTRS_POWER8E | CPU_FTRS_POWER8 | \
	     CPU_FTR_ALTIVEC_COMP | CPU_FTR_VSX_COMP | CPU_FTRS_POWER9 | \
	     CPU_FTRS_POWER9_DD2_1 | CPU_FTRS_POWER9_DD2_2 | CPU_FTRS_POWER10)
#अन्यथा
#घोषणा CPU_FTRS_POSSIBLE	\
	    (CPU_FTRS_PPC970 | CPU_FTRS_POWER5 | \
	     CPU_FTRS_POWER6 | CPU_FTRS_POWER7 | CPU_FTRS_POWER8E | \
	     CPU_FTRS_POWER8 | CPU_FTRS_CELL | CPU_FTRS_PA6T | \
	     CPU_FTR_VSX_COMP | CPU_FTR_ALTIVEC_COMP | CPU_FTRS_POWER9 | \
	     CPU_FTRS_POWER9_DD2_1 | CPU_FTRS_POWER9_DD2_2 | CPU_FTRS_POWER10)
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
#पूर्ण_अगर
#अन्यथा
क्रमागत अणु
	CPU_FTRS_POSSIBLE =
#अगर_घोषित CONFIG_PPC_BOOK3S_604
	    CPU_FTRS_604 | CPU_FTRS_740_NOTAU |
	    CPU_FTRS_740 | CPU_FTRS_750 | CPU_FTRS_750FX1 |
	    CPU_FTRS_750FX2 | CPU_FTRS_750FX | CPU_FTRS_750GX |
	    CPU_FTRS_7400_NOTAU | CPU_FTRS_7400 | CPU_FTRS_7450_20 |
	    CPU_FTRS_7450_21 | CPU_FTRS_7450_23 | CPU_FTRS_7455_1 |
	    CPU_FTRS_7455_20 | CPU_FTRS_7455 | CPU_FTRS_7447_10 |
	    CPU_FTRS_7447 | CPU_FTRS_7447A |
	    CPU_FTRS_CLASSIC32 |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_603
	    CPU_FTRS_603 | CPU_FTRS_82XX |
	    CPU_FTRS_G2_LE | CPU_FTRS_E300 | CPU_FTRS_E300C2 |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_8xx
	    CPU_FTRS_8XX |
#पूर्ण_अगर
#अगर_घोषित CONFIG_40x
	    CPU_FTRS_40X |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_47x
	    CPU_FTRS_47X | CPU_FTR_476_DD2 |
#या_अगर defined(CONFIG_44x)
	    CPU_FTRS_44X | CPU_FTRS_440x6 |
#पूर्ण_अगर
#अगर_घोषित CONFIG_E500
	    CPU_FTRS_E500 | CPU_FTRS_E500_2 |
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_E500MC
	    CPU_FTRS_E500MC | CPU_FTRS_E5500 | CPU_FTRS_E6500 |
#पूर्ण_अगर
	    0,
पूर्ण;
#पूर्ण_अगर /* __घातerpc64__ */

#अगर_घोषित CONFIG_PPC64
#अगर_घोषित CONFIG_PPC_BOOK3E
#घोषणा CPU_FTRS_ALWAYS		(CPU_FTRS_E6500 & CPU_FTRS_E5500)
#अन्यथा

#अगर_घोषित CONFIG_PPC_DT_CPU_FTRS
#घोषणा CPU_FTRS_DT_CPU_BASE			\
	(CPU_FTR_LWSYNC |			\
	 CPU_FTR_FPU_UNAVAILABLE |		\
	 CPU_FTR_NOEXECUTE |			\
	 CPU_FTR_COHERENT_ICACHE |		\
	 CPU_FTR_STCX_CHECKS_ADDRESS |		\
	 CPU_FTR_POPCNTB | CPU_FTR_POPCNTD |	\
	 CPU_FTR_DAWR |				\
	 CPU_FTR_ARCH_206 |			\
	 CPU_FTR_ARCH_207S)
#अन्यथा
#घोषणा CPU_FTRS_DT_CPU_BASE	(~0ul)
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
#घोषणा CPU_FTRS_ALWAYS \
	    (CPU_FTRS_POSSIBLE & ~CPU_FTR_HVMODE & CPU_FTRS_POWER7 & \
	     CPU_FTRS_POWER8E & CPU_FTRS_POWER8 & CPU_FTRS_POWER9 & \
	     CPU_FTRS_POWER9_DD2_1 & CPU_FTRS_DT_CPU_BASE)
#अन्यथा
#घोषणा CPU_FTRS_ALWAYS		\
	    (CPU_FTRS_PPC970 & CPU_FTRS_POWER5 & \
	     CPU_FTRS_POWER6 & CPU_FTRS_POWER7 & CPU_FTRS_CELL & \
	     CPU_FTRS_PA6T & CPU_FTRS_POWER8 & CPU_FTRS_POWER8E & \
	     ~CPU_FTR_HVMODE & CPU_FTRS_POSSIBLE & CPU_FTRS_POWER9 & \
	     CPU_FTRS_POWER9_DD2_1 & CPU_FTRS_DT_CPU_BASE)
#पूर्ण_अगर /* CONFIG_CPU_LITTLE_ENDIAN */
#पूर्ण_अगर
#अन्यथा
क्रमागत अणु
	CPU_FTRS_ALWAYS =
#अगर_घोषित CONFIG_PPC_BOOK3S_604
	    CPU_FTRS_604 & CPU_FTRS_740_NOTAU &
	    CPU_FTRS_740 & CPU_FTRS_750 & CPU_FTRS_750FX1 &
	    CPU_FTRS_750FX2 & CPU_FTRS_750FX & CPU_FTRS_750GX &
	    CPU_FTRS_7400_NOTAU & CPU_FTRS_7400 & CPU_FTRS_7450_20 &
	    CPU_FTRS_7450_21 & CPU_FTRS_7450_23 & CPU_FTRS_7455_1 &
	    CPU_FTRS_7455_20 & CPU_FTRS_7455 & CPU_FTRS_7447_10 &
	    CPU_FTRS_7447 & CPU_FTRS_7447A &
	    CPU_FTRS_CLASSIC32 &
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_BOOK3S_603
	    CPU_FTRS_603 & CPU_FTRS_82XX &
	    CPU_FTRS_G2_LE & CPU_FTRS_E300 & CPU_FTRS_E300C2 &
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_8xx
	    CPU_FTRS_8XX &
#पूर्ण_अगर
#अगर_घोषित CONFIG_40x
	    CPU_FTRS_40X &
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_47x
	    CPU_FTRS_47X &
#या_अगर defined(CONFIG_44x)
	    CPU_FTRS_44X & CPU_FTRS_440x6 &
#पूर्ण_अगर
#अगर_घोषित CONFIG_E500
	    CPU_FTRS_E500 & CPU_FTRS_E500_2 &
#पूर्ण_अगर
#अगर_घोषित CONFIG_PPC_E500MC
	    CPU_FTRS_E500MC & CPU_FTRS_E5500 & CPU_FTRS_E6500 &
#पूर्ण_अगर
	    ~CPU_FTR_EMB_HV &	/* can be हटाओd at runसमय */
	    CPU_FTRS_POSSIBLE,
पूर्ण;
#पूर्ण_अगर /* __घातerpc64__ */

/*
 * Maximum number of hw अवरोधpoपूर्णांक supported on घातerpc. Number of
 * अवरोधpoपूर्णांकs supported by actual hw might be less than this, which
 * is decided at run समय in nr_wp_slots().
 */
#घोषणा HBP_NUM_MAX	2

#पूर्ण_अगर /* !__ASSEMBLY__ */

#पूर्ण_अगर /* __ASM_POWERPC_CPUTABLE_H */
