<शैली गुरु>
/*
 * This file is subject to the terms and conditions of the GNU General Public
 * License.  See the file "COPYING" in the मुख्य directory of this archive
 * क्रम more details.
 *
 * Copyright (C) 1994 Walकरोrf GMBH
 * Copyright (C) 1995, 1996, 1997, 1998, 1999, 2001, 2002, 2003 Ralf Baechle
 * Copyright (C) 1996 Paul M. Antoine
 * Copyright (C) 1999, 2000 Silicon Graphics, Inc.
 */
#अगर_अघोषित _ASM_PROCESSOR_H
#घोषणा _ASM_PROCESSOR_H

#समावेश <linux/atomic.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/sizes.h>
#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/cachectl.h>
#समावेश <यंत्र/cpu.h>
#समावेश <यंत्र/cpu-info.h>
#समावेश <यंत्र/dsemul.h>
#समावेश <यंत्र/mipsregs.h>
#समावेश <यंत्र/prefetch.h>
#समावेश <यंत्र/vdso/processor.h>

/*
 * System setup and hardware flags..
 */

बाह्य अचिन्हित पूर्णांक vced_count, vcei_count;
बाह्य पूर्णांक arch_dup_task_काष्ठा(काष्ठा task_काष्ठा *dst, काष्ठा task_काष्ठा *src);

#अगर_घोषित CONFIG_32BIT
/*
 * User space process size: 2GB. This is hardcoded पूर्णांकo a few places,
 * so करोn't change it unless you know what you are करोing.
 */
#घोषणा TASK_SIZE	0x80000000UL

#घोषणा STACK_TOP_MAX	TASK_SIZE

#घोषणा TASK_IS_32BIT_ADDR 1

#पूर्ण_अगर

#अगर_घोषित CONFIG_64BIT
/*
 * User space process size: 1TB. This is hardcoded पूर्णांकo a few places,
 * so करोn't change it unless you know what you are करोing.  TASK_SIZE
 * is limited to 1TB by the R4000 architecture; R10000 and better can
 * support 16TB; the architectural reserve क्रम future expansion is
 * 8192EB ...
 */
#घोषणा TASK_SIZE32	0x7fff8000UL
#अगर_घोषित CONFIG_MIPS_VA_BITS_48
#घोषणा TASK_SIZE64     (0x1UL << ((cpu_data[0].vmbits>48)?48:cpu_data[0].vmbits))
#अन्यथा
#घोषणा TASK_SIZE64     0x10000000000UL
#पूर्ण_अगर
#घोषणा TASK_SIZE (test_thपढ़ो_flag(TIF_32BIT_ADDR) ? TASK_SIZE32 : TASK_SIZE64)
#घोषणा STACK_TOP_MAX	TASK_SIZE64

#घोषणा TASK_SIZE_OF(tsk)						\
	(test_tsk_thपढ़ो_flag(tsk, TIF_32BIT_ADDR) ? TASK_SIZE32 : TASK_SIZE64)

#घोषणा TASK_IS_32BIT_ADDR test_thपढ़ो_flag(TIF_32BIT_ADDR)

#पूर्ण_अगर

#घोषणा VDSO_RANDOMIZE_SIZE	(TASK_IS_32BIT_ADDR ? SZ_1M : SZ_64M)

बाह्य अचिन्हित दीर्घ mips_stack_top(व्योम);
#घोषणा STACK_TOP		mips_stack_top()

/*
 * This decides where the kernel will search क्रम a मुक्त chunk of vm
 * space during mmap's.
 */
#घोषणा TASK_UNMAPPED_BASE PAGE_ALIGN(TASK_SIZE / 3)


#घोषणा NUM_FPU_REGS	32

#अगर_घोषित CONFIG_CPU_HAS_MSA
# define FPU_REG_WIDTH	128
#अन्यथा
# define FPU_REG_WIDTH	64
#पूर्ण_अगर

जोड़ fpureg अणु
	__u32	val32[FPU_REG_WIDTH / 32];
	__u64	val64[FPU_REG_WIDTH / 64];
पूर्ण;

#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
# define FPR_IDX(width, idx)	(idx)
#अन्यथा
# define FPR_IDX(width, idx)	((idx) ^ ((64 / (width)) - 1))
#पूर्ण_अगर

#घोषणा BUILD_FPR_ACCESS(width) \
अटल अंतरभूत u##width get_fpr##width(जोड़ fpureg *fpr, अचिन्हित idx)	\
अणु									\
	वापस fpr->val##width[FPR_IDX(width, idx)];			\
पूर्ण									\
									\
अटल अंतरभूत व्योम set_fpr##width(जोड़ fpureg *fpr, अचिन्हित idx,	\
				  u##width val)				\
अणु									\
	fpr->val##width[FPR_IDX(width, idx)] = val;			\
पूर्ण

BUILD_FPR_ACCESS(32)
BUILD_FPR_ACCESS(64)

/*
 * It would be nice to add some more fields क्रम emulator statistics,
 * the additional inक्रमmation is निजी to the FPU emulator क्रम now.
 * See arch/mips/include/यंत्र/fpu_emulator.h.
 */

काष्ठा mips_fpu_काष्ठा अणु
	जोड़ fpureg	fpr[NUM_FPU_REGS];
	अचिन्हित पूर्णांक	fcr31;
	अचिन्हित पूर्णांक	msacsr;
पूर्ण;

#घोषणा NUM_DSP_REGS   6

प्रकार अचिन्हित दीर्घ dspreg_t;

काष्ठा mips_dsp_state अणु
	dspreg_t	dspr[NUM_DSP_REGS];
	अचिन्हित पूर्णांक	dspcontrol;
पूर्ण;

#घोषणा INIT_CPUMASK अणु \
	अणु0,पूर्ण \
पूर्ण

काष्ठा mips3264_watch_reg_state अणु
	/* The width of watchlo is 32 in a 32 bit kernel and 64 in a
	   64 bit kernel.  We use अचिन्हित दीर्घ as it has the same
	   property. */
	अचिन्हित दीर्घ watchlo[NUM_WATCH_REGS];
	/* Only the mask and IRW bits from watchhi. */
	u16 watchhi[NUM_WATCH_REGS];
पूर्ण;

जोड़ mips_watch_reg_state अणु
	काष्ठा mips3264_watch_reg_state mips3264;
पूर्ण;

#अगर defined(CONFIG_CPU_CAVIUM_OCTEON)

काष्ठा octeon_cop2_state अणु
	/* DMFC2 rt, 0x0201 */
	अचिन्हित दीर्घ	cop2_crc_iv;
	/* DMFC2 rt, 0x0202 (Set with DMTC2 rt, 0x1202) */
	अचिन्हित दीर्घ	cop2_crc_length;
	/* DMFC2 rt, 0x0200 (set with DMTC2 rt, 0x4200) */
	अचिन्हित दीर्घ	cop2_crc_poly;
	/* DMFC2 rt, 0x0402; DMFC2 rt, 0x040A */
	अचिन्हित दीर्घ	cop2_llm_dat[2];
       /* DMFC2 rt, 0x0084 */
	अचिन्हित दीर्घ	cop2_3des_iv;
	/* DMFC2 rt, 0x0080; DMFC2 rt, 0x0081; DMFC2 rt, 0x0082 */
	अचिन्हित दीर्घ	cop2_3des_key[3];
	/* DMFC2 rt, 0x0088 (Set with DMTC2 rt, 0x0098) */
	अचिन्हित दीर्घ	cop2_3des_result;
	/* DMFC2 rt, 0x0111 (FIXME: Read Pass1 Errata) */
	अचिन्हित दीर्घ	cop2_aes_inp0;
	/* DMFC2 rt, 0x0102; DMFC2 rt, 0x0103 */
	अचिन्हित दीर्घ	cop2_aes_iv[2];
	/* DMFC2 rt, 0x0104; DMFC2 rt, 0x0105; DMFC2 rt, 0x0106; DMFC2
	 * rt, 0x0107 */
	अचिन्हित दीर्घ	cop2_aes_key[4];
	/* DMFC2 rt, 0x0110 */
	अचिन्हित दीर्घ	cop2_aes_keylen;
	/* DMFC2 rt, 0x0100; DMFC2 rt, 0x0101 */
	अचिन्हित दीर्घ	cop2_aes_result[2];
	/* DMFC2 rt, 0x0240; DMFC2 rt, 0x0241; DMFC2 rt, 0x0242; DMFC2
	 * rt, 0x0243; DMFC2 rt, 0x0244; DMFC2 rt, 0x0245; DMFC2 rt,
	 * 0x0246; DMFC2 rt, 0x0247; DMFC2 rt, 0x0248; DMFC2 rt,
	 * 0x0249; DMFC2 rt, 0x024A; DMFC2 rt, 0x024B; DMFC2 rt,
	 * 0x024C; DMFC2 rt, 0x024D; DMFC2 rt, 0x024E - Pass2 */
	अचिन्हित दीर्घ	cop2_hsh_datw[15];
	/* DMFC2 rt, 0x0250; DMFC2 rt, 0x0251; DMFC2 rt, 0x0252; DMFC2
	 * rt, 0x0253; DMFC2 rt, 0x0254; DMFC2 rt, 0x0255; DMFC2 rt,
	 * 0x0256; DMFC2 rt, 0x0257 - Pass2 */
	अचिन्हित दीर्घ	cop2_hsh_ivw[8];
	/* DMFC2 rt, 0x0258; DMFC2 rt, 0x0259 - Pass2 */
	अचिन्हित दीर्घ	cop2_gfm_mult[2];
	/* DMFC2 rt, 0x025E - Pass2 */
	अचिन्हित दीर्घ	cop2_gfm_poly;
	/* DMFC2 rt, 0x025A; DMFC2 rt, 0x025B - Pass2 */
	अचिन्हित दीर्घ	cop2_gfm_result[2];
	/* DMFC2 rt, 0x24F, DMFC2 rt, 0x50, OCTEON III */
	अचिन्हित दीर्घ	cop2_sha3[2];
पूर्ण;
#घोषणा COP2_INIT						\
	.cp2			= अणु0,पूर्ण,

काष्ठा octeon_cvmseg_state अणु
	अचिन्हित दीर्घ cvmseg[CONFIG_CAVIUM_OCTEON_CVMSEG_SIZE]
			    [cpu_dcache_line_size() / माप(अचिन्हित दीर्घ)];
पूर्ण;

#या_अगर defined(CONFIG_CPU_XLP)
काष्ठा nlm_cop2_state अणु
	u64	rx[4];
	u64	tx[4];
	u32	tx_msg_status;
	u32	rx_msg_status;
पूर्ण;

#घोषणा COP2_INIT						\
	.cp2			= अणुअणु0पूर्ण, अणु0पूर्ण, 0, 0पूर्ण,
#अन्यथा
#घोषणा COP2_INIT
#पूर्ण_अगर

#अगर_घोषित CONFIG_CPU_HAS_MSA
# define ARCH_MIN_TASKALIGN	16
# define FPU_ALIGN		__aligned(16)
#अन्यथा
# define ARCH_MIN_TASKALIGN	8
# define FPU_ALIGN
#पूर्ण_अगर

काष्ठा mips_abi;

/*
 * If you change thपढ़ो_काष्ठा remember to change the #घोषणाs below too!
 */
काष्ठा thपढ़ो_काष्ठा अणु
	/* Saved मुख्य processor रेजिस्टरs. */
	अचिन्हित दीर्घ reg16;
	अचिन्हित दीर्घ reg17, reg18, reg19, reg20, reg21, reg22, reg23;
	अचिन्हित दीर्घ reg29, reg30, reg31;

	/* Saved cp0 stuff. */
	अचिन्हित दीर्घ cp0_status;

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
	/* Saved fpu/fpu emulator stuff. */
	काष्ठा mips_fpu_काष्ठा fpu FPU_ALIGN;
	/* Asचिन्हित branch delay slot 'emulation' frame */
	atomic_t bd_emu_frame;
	/* PC of the branch from a branch delay slot 'emulation' */
	अचिन्हित दीर्घ bd_emu_branch_pc;
	/* PC to जारी from following a branch delay slot 'emulation' */
	अचिन्हित दीर्घ bd_emu_cont_pc;
#पूर्ण_अगर
#अगर_घोषित CONFIG_MIPS_MT_FPAFF
	/* Emulated inकाष्ठाion count */
	अचिन्हित दीर्घ emulated_fp;
	/* Saved per-thपढ़ो scheduler affinity mask */
	cpumask_t user_cpus_allowed;
#पूर्ण_अगर /* CONFIG_MIPS_MT_FPAFF */

	/* Saved state of the DSP ASE, अगर available. */
	काष्ठा mips_dsp_state dsp;

	/* Saved watch रेजिस्टर state, अगर available. */
	जोड़ mips_watch_reg_state watch;

	/* Other stuff associated with the thपढ़ो. */
	अचिन्हित दीर्घ cp0_badvaddr;	/* Last user fault */
	अचिन्हित दीर्घ cp0_baduaddr;	/* Last kernel fault accessing USEG */
	अचिन्हित दीर्घ error_code;
	अचिन्हित दीर्घ trap_nr;
#अगर_घोषित CONFIG_CPU_CAVIUM_OCTEON
	काष्ठा octeon_cop2_state cp2 __attribute__ ((__aligned__(128)));
	काष्ठा octeon_cvmseg_state cvmseg __attribute__ ((__aligned__(128)));
#पूर्ण_अगर
#अगर_घोषित CONFIG_CPU_XLP
	काष्ठा nlm_cop2_state cp2;
#पूर्ण_अगर
	काष्ठा mips_abi *abi;
पूर्ण;

#अगर_घोषित CONFIG_MIPS_MT_FPAFF
#घोषणा FPAFF_INIT						\
	.emulated_fp			= 0,			\
	.user_cpus_allowed		= INIT_CPUMASK,
#अन्यथा
#घोषणा FPAFF_INIT
#पूर्ण_अगर /* CONFIG_MIPS_MT_FPAFF */

#अगर_घोषित CONFIG_MIPS_FP_SUPPORT
# define FPU_INIT						\
	.fpu			= अणु				\
		.fpr		= अणुअणुअणु0,पूर्ण,पूर्ण,पूर्ण,			\
		.fcr31		= 0,				\
		.msacsr		= 0,				\
	पूर्ण,							\
	/* Delay slot emulation */				\
	.bd_emu_frame = ATOMIC_INIT(BD_EMUFRAME_NONE),		\
	.bd_emu_branch_pc = 0,					\
	.bd_emu_cont_pc = 0,
#अन्यथा
# define FPU_INIT
#पूर्ण_अगर

#घोषणा INIT_THREAD  अणु						\
	/*							\
	 * Saved मुख्य processor रेजिस्टरs			\
	 */							\
	.reg16			= 0,				\
	.reg17			= 0,				\
	.reg18			= 0,				\
	.reg19			= 0,				\
	.reg20			= 0,				\
	.reg21			= 0,				\
	.reg22			= 0,				\
	.reg23			= 0,				\
	.reg29			= 0,				\
	.reg30			= 0,				\
	.reg31			= 0,				\
	/*							\
	 * Saved cp0 stuff					\
	 */							\
	.cp0_status		= 0,				\
	/*							\
	 * Saved FPU/FPU emulator stuff				\
	 */							\
	FPU_INIT						\
	/*							\
	 * FPU affinity state (null अगर not FPAFF)		\
	 */							\
	FPAFF_INIT						\
	/*							\
	 * Saved DSP stuff					\
	 */							\
	.dsp			= अणु				\
		.dspr		= अणु0, पूर्ण,			\
		.dspcontrol	= 0,				\
	पूर्ण,							\
	/*							\
	 * saved watch रेजिस्टर stuff				\
	 */							\
	.watch = अणुअणुअणु0,पूर्ण,पूर्ण,पूर्ण,					\
	/*							\
	 * Other stuff associated with the process		\
	 */							\
	.cp0_badvaddr		= 0,				\
	.cp0_baduaddr		= 0,				\
	.error_code		= 0,				\
	.trap_nr		= 0,				\
	/*							\
	 * Platक्रमm specअगरic cop2 रेजिस्टरs(null अगर no COP2)	\
	 */							\
	COP2_INIT						\
पूर्ण

काष्ठा task_काष्ठा;

/* Free all resources held by a thपढ़ो. */
#घोषणा release_thपढ़ो(thपढ़ो) करो अणु पूर्ण जबतक(0)

/*
 * Do necessary setup to start up a newly executed thपढ़ो.
 */
बाह्य व्योम start_thपढ़ो(काष्ठा pt_regs * regs, अचिन्हित दीर्घ pc, अचिन्हित दीर्घ sp);

अटल अंतरभूत व्योम flush_thपढ़ो(व्योम)
अणु
पूर्ण

अचिन्हित दीर्घ get_wchan(काष्ठा task_काष्ठा *p);

#घोषणा __KSTK_TOS(tsk) ((अचिन्हित दीर्घ)task_stack_page(tsk) + \
			 THREAD_SIZE - 32 - माप(काष्ठा pt_regs))
#घोषणा task_pt_regs(tsk) ((काष्ठा pt_regs *)__KSTK_TOS(tsk))
#घोषणा KSTK_EIP(tsk) (task_pt_regs(tsk)->cp0_epc)
#घोषणा KSTK_ESP(tsk) (task_pt_regs(tsk)->regs[29])
#घोषणा KSTK_STATUS(tsk) (task_pt_regs(tsk)->cp0_status)

/*
 * Return_address is a replacement क्रम __builtin_वापस_address(count)
 * which on certain architectures cannot reasonably be implemented in GCC
 * (MIPS, Alpha) or is unusable with -fomit-frame-poपूर्णांकer (i386).
 * Note that __builtin_वापस_address(x>=1) is क्रमbidden because GCC
 * पातs compilation on some CPUs.  It's simply not possible to unwind
 * some CPU's stackframes.
 *
 * __builtin_वापस_address works only क्रम non-leaf functions.	We aव्योम the
 * overhead of a function call by क्रमcing the compiler to save the वापस
 * address रेजिस्टर on the stack.
 */
#घोषणा वापस_address() (अणु__यंत्र__ __अस्थिर__("":::"$31");__builtin_वापस_address(0);पूर्ण)

#अगर_घोषित CONFIG_CPU_HAS_PREFETCH

#घोषणा ARCH_HAS_PREFETCH
#घोषणा prefetch(x) __builtin_prefetch((x), 0, 1)

#घोषणा ARCH_HAS_PREFETCHW
#घोषणा prefetchw(x) __builtin_prefetch((x), 1, 1)

#पूर्ण_अगर

/*
 * Functions & macros implementing the PR_GET_FP_MODE & PR_SET_FP_MODE options
 * to the prctl syscall.
 */
बाह्य पूर्णांक mips_get_process_fp_mode(काष्ठा task_काष्ठा *task);
बाह्य पूर्णांक mips_set_process_fp_mode(काष्ठा task_काष्ठा *task,
				    अचिन्हित पूर्णांक value);

#घोषणा GET_FP_MODE(task)		mips_get_process_fp_mode(task)
#घोषणा SET_FP_MODE(task,value)		mips_set_process_fp_mode(task, value)

#पूर्ण_अगर /* _ASM_PROCESSOR_H */
