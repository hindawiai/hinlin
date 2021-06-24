<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
#अगर_अघोषित _SPARC_TRAP_BLOCK_H
#घोषणा _SPARC_TRAP_BLOCK_H

#समावेश <linux/thपढ़ोs.h>

#समावेश <यंत्र/hypervisor.h>
#समावेश <यंत्र/asi.h>

#अगर_अघोषित __ASSEMBLY__

/* Trap handling code needs to get at a few critical values upon
 * trap entry and to process TSB misses.  These cannot be in the
 * per_cpu() area as we really need to lock them पूर्णांकo the TLB and
 * thus make them part of the मुख्य kernel image.  As a result we
 * try to make this as small as possible.
 *
 * This is padded out and aligned to 64-bytes to aव्योम false sharing
 * on SMP.
 */

/* If you modअगरy the size of this काष्ठाure, please update
 * TRAP_BLOCK_SZ_SHIFT below.
 */
काष्ठा thपढ़ो_info;
काष्ठा trap_per_cpu अणु
/* D-cache line 1: Basic thपढ़ो inक्रमmation, cpu and device monकरो queues */
	काष्ठा thपढ़ो_info	*thपढ़ो;
	अचिन्हित दीर्घ		pgd_paddr;
	अचिन्हित दीर्घ		cpu_monकरो_pa;
	अचिन्हित दीर्घ		dev_monकरो_pa;

/* D-cache line 2: Error Monकरो Queue and kernel buffer poपूर्णांकers */
	अचिन्हित दीर्घ		resum_monकरो_pa;
	अचिन्हित दीर्घ		resum_kernel_buf_pa;
	अचिन्हित दीर्घ		nonresum_monकरो_pa;
	अचिन्हित दीर्घ		nonresum_kernel_buf_pa;

/* Dcache lines 3, 4, 5, and 6: Hypervisor Fault Status */
	काष्ठा hv_fault_status	fault_info;

/* Dcache line 7: Physical addresses of CPU send monकरो block and CPU list.  */
	अचिन्हित दीर्घ		cpu_monकरो_block_pa;
	अचिन्हित दीर्घ		cpu_list_pa;
	अचिन्हित दीर्घ		tsb_huge;
	अचिन्हित दीर्घ		tsb_huge_temp;

/* Dcache line 8: IRQ work list, and keep trap_block a घातer-of-2 in size.  */
	अचिन्हित दीर्घ		irq_worklist_pa;
	अचिन्हित पूर्णांक		cpu_monकरो_qmask;
	अचिन्हित पूर्णांक		dev_monकरो_qmask;
	अचिन्हित पूर्णांक		resum_qmask;
	अचिन्हित पूर्णांक		nonresum_qmask;
	अचिन्हित दीर्घ		__per_cpu_base;
पूर्ण __attribute__((aligned(64)));
बाह्य काष्ठा trap_per_cpu trap_block[NR_CPUS];
व्योम init_cur_cpu_trap(काष्ठा thपढ़ो_info *);
व्योम setup_tba(व्योम);
बाह्य पूर्णांक ncpus_probed;
बाह्य u64 cpu_monकरो_counter[NR_CPUS];

अचिन्हित दीर्घ real_hard_smp_processor_id(व्योम);

काष्ठा cpuid_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	cheetah_safari[4];
	अचिन्हित पूर्णांक	cheetah_jbus[4];
	अचिन्हित पूर्णांक	starfire[4];
	अचिन्हित पूर्णांक	sun4v[4];
पूर्ण;
बाह्य काष्ठा cpuid_patch_entry __cpuid_patch, __cpuid_patch_end;

काष्ठा sun4v_1insn_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	insn;
पूर्ण;
बाह्य काष्ठा sun4v_1insn_patch_entry __sun4v_1insn_patch,
	__sun4v_1insn_patch_end;
बाह्य काष्ठा sun4v_1insn_patch_entry __fast_win_ctrl_1insn_patch,
	__fast_win_ctrl_1insn_patch_end;
बाह्य काष्ठा sun4v_1insn_patch_entry __sun_m7_1insn_patch,
	__sun_m7_1insn_patch_end;

काष्ठा sun4v_2insn_patch_entry अणु
	अचिन्हित पूर्णांक	addr;
	अचिन्हित पूर्णांक	insns[2];
पूर्ण;
बाह्य काष्ठा sun4v_2insn_patch_entry __sun4v_2insn_patch,
	__sun4v_2insn_patch_end;
बाह्य काष्ठा sun4v_2insn_patch_entry __sun_m7_2insn_patch,
	__sun_m7_2insn_patch_end;


#पूर्ण_अगर /* !(__ASSEMBLY__) */

#घोषणा TRAP_PER_CPU_THREAD		0x00
#घोषणा TRAP_PER_CPU_PGD_PADDR		0x08
#घोषणा TRAP_PER_CPU_CPU_MONDO_PA	0x10
#घोषणा TRAP_PER_CPU_DEV_MONDO_PA	0x18
#घोषणा TRAP_PER_CPU_RESUM_MONDO_PA	0x20
#घोषणा TRAP_PER_CPU_RESUM_KBUF_PA	0x28
#घोषणा TRAP_PER_CPU_NONRESUM_MONDO_PA	0x30
#घोषणा TRAP_PER_CPU_NONRESUM_KBUF_PA	0x38
#घोषणा TRAP_PER_CPU_FAULT_INFO		0x40
#घोषणा TRAP_PER_CPU_CPU_MONDO_BLOCK_PA	0xc0
#घोषणा TRAP_PER_CPU_CPU_LIST_PA	0xc8
#घोषणा TRAP_PER_CPU_TSB_HUGE		0xd0
#घोषणा TRAP_PER_CPU_TSB_HUGE_TEMP	0xd8
#घोषणा TRAP_PER_CPU_IRQ_WORKLIST_PA	0xe0
#घोषणा TRAP_PER_CPU_CPU_MONDO_QMASK	0xe8
#घोषणा TRAP_PER_CPU_DEV_MONDO_QMASK	0xec
#घोषणा TRAP_PER_CPU_RESUM_QMASK	0xf0
#घोषणा TRAP_PER_CPU_NONRESUM_QMASK	0xf4
#घोषणा TRAP_PER_CPU_PER_CPU_BASE	0xf8

#घोषणा TRAP_BLOCK_SZ_SHIFT		8

#समावेश <यंत्र/scratchpad.h>

#घोषणा __GET_CPUID(REG)				\
	/* Spitfire implementation (शेष). */	\
661:	ldxa		[%g0] ASI_UPA_CONFIG, REG;	\
	srlx		REG, 17, REG;			\
	 and		REG, 0x1f, REG;			\
	nop;						\
	.section	.cpuid_patch, "ax";		\
	/* Inकाष्ठाion location. */			\
	.word		661b;				\
	/* Cheetah Safari implementation. */		\
	ldxa		[%g0] ASI_SAFARI_CONFIG, REG;	\
	srlx		REG, 17, REG;			\
	and		REG, 0x3ff, REG;		\
	nop;						\
	/* Cheetah JBUS implementation. */		\
	ldxa		[%g0] ASI_JBUS_CONFIG, REG;	\
	srlx		REG, 17, REG;			\
	and		REG, 0x1f, REG;			\
	nop;						\
	/* Starfire implementation. */			\
	sethi		%hi(0x1fff40000d0 >> 9), REG;	\
	sllx		REG, 9, REG;			\
	or		REG, 0xd0, REG;			\
	lduwa		[REG] ASI_PHYS_BYPASS_EC_E, REG;\
	/* sun4v implementation. */			\
	mov		SCRATCHPAD_CPUID, REG;		\
	ldxa		[REG] ASI_SCRATCHPAD, REG;	\
	nop;						\
	nop;						\
	.previous;

#अगर_घोषित CONFIG_SMP

#घोषणा TRAP_LOAD_TRAP_BLOCK(DEST, TMP)		\
	__GET_CPUID(TMP)			\
	sethi	%hi(trap_block), DEST;		\
	sllx	TMP, TRAP_BLOCK_SZ_SHIFT, TMP;	\
	or	DEST, %lo(trap_block), DEST;	\
	add	DEST, TMP, DEST;		\

/* Clobbers TMP, current address space PGD phys address पूर्णांकo DEST.  */
#घोषणा TRAP_LOAD_PGD_PHYS(DEST, TMP)		\
	TRAP_LOAD_TRAP_BLOCK(DEST, TMP)		\
	ldx	[DEST + TRAP_PER_CPU_PGD_PADDR], DEST;

/* Clobbers TMP, loads local processor's IRQ work area पूर्णांकo DEST.  */
#घोषणा TRAP_LOAD_IRQ_WORK_PA(DEST, TMP)	\
	TRAP_LOAD_TRAP_BLOCK(DEST, TMP)		\
	add	DEST, TRAP_PER_CPU_IRQ_WORKLIST_PA, DEST;

/* Clobbers TMP, loads DEST with current thपढ़ो info poपूर्णांकer.  */
#घोषणा TRAP_LOAD_THREAD_REG(DEST, TMP)		\
	TRAP_LOAD_TRAP_BLOCK(DEST, TMP)		\
	ldx	[DEST + TRAP_PER_CPU_THREAD], DEST;

/* Given the current thपढ़ो info poपूर्णांकer in THR, load the per-cpu
 * area base of the current processor पूर्णांकo DEST.  REG1, REG2, and REG3 are
 * clobbered.
 *
 * You असलolutely cannot use DEST as a temporary in this code.  The
 * reason is that traps can happen during execution, and वापस from
 * trap will load the fully resolved DEST per-cpu base.  This can corrupt
 * the calculations करोne by the macro mid-stream.
 */
#घोषणा LOAD_PER_CPU_BASE(DEST, THR, REG1, REG2, REG3)	\
	lduh	[THR + TI_CPU], REG1;			\
	sethi	%hi(trap_block), REG2;			\
	sllx	REG1, TRAP_BLOCK_SZ_SHIFT, REG1;	\
	or	REG2, %lo(trap_block), REG2;		\
	add	REG2, REG1, REG2;			\
	ldx	[REG2 + TRAP_PER_CPU_PER_CPU_BASE], DEST;

#अन्यथा

#घोषणा TRAP_LOAD_TRAP_BLOCK(DEST, TMP)		\
	sethi	%hi(trap_block), DEST;		\
	or	DEST, %lo(trap_block), DEST;	\

/* Uniprocessor versions, we know the cpuid is zero.  */
#घोषणा TRAP_LOAD_PGD_PHYS(DEST, TMP)		\
	TRAP_LOAD_TRAP_BLOCK(DEST, TMP)		\
	ldx	[DEST + TRAP_PER_CPU_PGD_PADDR], DEST;

/* Clobbers TMP, loads local processor's IRQ work area पूर्णांकo DEST.  */
#घोषणा TRAP_LOAD_IRQ_WORK_PA(DEST, TMP)	\
	TRAP_LOAD_TRAP_BLOCK(DEST, TMP)		\
	add	DEST, TRAP_PER_CPU_IRQ_WORKLIST_PA, DEST;

#घोषणा TRAP_LOAD_THREAD_REG(DEST, TMP)		\
	TRAP_LOAD_TRAP_BLOCK(DEST, TMP)		\
	ldx	[DEST + TRAP_PER_CPU_THREAD], DEST;

/* No per-cpu areas on uniprocessor, so no need to load DEST.  */
#घोषणा LOAD_PER_CPU_BASE(DEST, THR, REG1, REG2, REG3)

#पूर्ण_अगर /* !(CONFIG_SMP) */

#पूर्ण_अगर /* _SPARC_TRAP_BLOCK_H */
