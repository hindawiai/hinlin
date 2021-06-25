<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/perf_event.h>
#समावेश <linux/types.h>

#समावेश <यंत्र/perf_event.h>
#समावेश <यंत्र/msr.h>
#समावेश <यंत्र/insn.h>

#समावेश "../perf_event.h"

अटल स्थिर क्रमागत अणु
	LBR_EIP_FLAGS		= 1,
	LBR_TSX			= 2,
पूर्ण lbr_desc[LBR_FORMAT_MAX_KNOWN + 1] = अणु
	[LBR_FORMAT_EIP_FLAGS]  = LBR_EIP_FLAGS,
	[LBR_FORMAT_EIP_FLAGS2] = LBR_EIP_FLAGS | LBR_TSX,
पूर्ण;

/*
 * Intel LBR_SELECT bits
 * Intel Vol3a, April 2011, Section 16.7 Table 16-10
 *
 * Hardware branch filter (not available on all CPUs)
 */
#घोषणा LBR_KERNEL_BIT		0 /* करो not capture at ring0 */
#घोषणा LBR_USER_BIT		1 /* करो not capture at ring > 0 */
#घोषणा LBR_JCC_BIT		2 /* करो not capture conditional branches */
#घोषणा LBR_REL_CALL_BIT	3 /* करो not capture relative calls */
#घोषणा LBR_IND_CALL_BIT	4 /* करो not capture indirect calls */
#घोषणा LBR_RETURN_BIT		5 /* करो not capture near वापसs */
#घोषणा LBR_IND_JMP_BIT		6 /* करो not capture indirect jumps */
#घोषणा LBR_REL_JMP_BIT		7 /* करो not capture relative jumps */
#घोषणा LBR_FAR_BIT		8 /* करो not capture far branches */
#घोषणा LBR_CALL_STACK_BIT	9 /* enable call stack */

/*
 * Following bit only exists in Linux; we mask it out beक्रमe writing it to
 * the actual MSR. But it helps the स्थिरraपूर्णांक perf code to understand
 * that this is a separate configuration.
 */
#घोषणा LBR_NO_INFO_BIT	       63 /* करोn't पढ़ो LBR_INFO. */

#घोषणा LBR_KERNEL	(1 << LBR_KERNEL_BIT)
#घोषणा LBR_USER	(1 << LBR_USER_BIT)
#घोषणा LBR_JCC		(1 << LBR_JCC_BIT)
#घोषणा LBR_REL_CALL	(1 << LBR_REL_CALL_BIT)
#घोषणा LBR_IND_CALL	(1 << LBR_IND_CALL_BIT)
#घोषणा LBR_RETURN	(1 << LBR_RETURN_BIT)
#घोषणा LBR_REL_JMP	(1 << LBR_REL_JMP_BIT)
#घोषणा LBR_IND_JMP	(1 << LBR_IND_JMP_BIT)
#घोषणा LBR_FAR		(1 << LBR_FAR_BIT)
#घोषणा LBR_CALL_STACK	(1 << LBR_CALL_STACK_BIT)
#घोषणा LBR_NO_INFO	(1ULL << LBR_NO_INFO_BIT)

#घोषणा LBR_PLM (LBR_KERNEL | LBR_USER)

#घोषणा LBR_SEL_MASK	0x3ff	/* valid bits in LBR_SELECT */
#घोषणा LBR_NOT_SUPP	-1	/* LBR filter not supported */
#घोषणा LBR_IGN		0	/* ignored */

#घोषणा LBR_ANY		 \
	(LBR_JCC	|\
	 LBR_REL_CALL	|\
	 LBR_IND_CALL	|\
	 LBR_RETURN	|\
	 LBR_REL_JMP	|\
	 LBR_IND_JMP	|\
	 LBR_FAR)

#घोषणा LBR_FROM_FLAG_MISPRED	BIT_ULL(63)
#घोषणा LBR_FROM_FLAG_IN_TX	BIT_ULL(62)
#घोषणा LBR_FROM_FLAG_ABORT	BIT_ULL(61)

#घोषणा LBR_FROM_SIGNEXT_2MSB	(BIT_ULL(60) | BIT_ULL(59))

/*
 * x86control flow change classअगरication
 * x86control flow changes include branches, पूर्णांकerrupts, traps, faults
 */
क्रमागत अणु
	X86_BR_NONE		= 0,      /* unknown */

	X86_BR_USER		= 1 << 0, /* branch target is user */
	X86_BR_KERNEL		= 1 << 1, /* branch target is kernel */

	X86_BR_CALL		= 1 << 2, /* call */
	X86_BR_RET		= 1 << 3, /* वापस */
	X86_BR_SYSCALL		= 1 << 4, /* syscall */
	X86_BR_SYSRET		= 1 << 5, /* syscall वापस */
	X86_BR_INT		= 1 << 6, /* sw पूर्णांकerrupt */
	X86_BR_IRET		= 1 << 7, /* वापस from पूर्णांकerrupt */
	X86_BR_JCC		= 1 << 8, /* conditional */
	X86_BR_JMP		= 1 << 9, /* jump */
	X86_BR_IRQ		= 1 << 10,/* hw पूर्णांकerrupt or trap or fault */
	X86_BR_IND_CALL		= 1 << 11,/* indirect calls */
	X86_BR_ABORT		= 1 << 12,/* transaction पात */
	X86_BR_IN_TX		= 1 << 13,/* in transaction */
	X86_BR_NO_TX		= 1 << 14,/* not in transaction */
	X86_BR_ZERO_CALL	= 1 << 15,/* zero length call */
	X86_BR_CALL_STACK	= 1 << 16,/* call stack */
	X86_BR_IND_JMP		= 1 << 17,/* indirect jump */

	X86_BR_TYPE_SAVE	= 1 << 18,/* indicate to save branch type */

पूर्ण;

#घोषणा X86_BR_PLM (X86_BR_USER | X86_BR_KERNEL)
#घोषणा X86_BR_ANYTX (X86_BR_NO_TX | X86_BR_IN_TX)

#घोषणा X86_BR_ANY       \
	(X86_BR_CALL    |\
	 X86_BR_RET     |\
	 X86_BR_SYSCALL |\
	 X86_BR_SYSRET  |\
	 X86_BR_INT     |\
	 X86_BR_IRET    |\
	 X86_BR_JCC     |\
	 X86_BR_JMP	 |\
	 X86_BR_IRQ	 |\
	 X86_BR_ABORT	 |\
	 X86_BR_IND_CALL |\
	 X86_BR_IND_JMP  |\
	 X86_BR_ZERO_CALL)

#घोषणा X86_BR_ALL (X86_BR_PLM | X86_BR_ANY)

#घोषणा X86_BR_ANY_CALL		 \
	(X86_BR_CALL		|\
	 X86_BR_IND_CALL	|\
	 X86_BR_ZERO_CALL	|\
	 X86_BR_SYSCALL		|\
	 X86_BR_IRQ		|\
	 X86_BR_INT)

/*
 * Intel LBR_CTL bits
 *
 * Hardware branch filter क्रम Arch LBR
 */
#घोषणा ARCH_LBR_KERNEL_BIT		1  /* capture at ring0 */
#घोषणा ARCH_LBR_USER_BIT		2  /* capture at ring > 0 */
#घोषणा ARCH_LBR_CALL_STACK_BIT		3  /* enable call stack */
#घोषणा ARCH_LBR_JCC_BIT		16 /* capture conditional branches */
#घोषणा ARCH_LBR_REL_JMP_BIT		17 /* capture relative jumps */
#घोषणा ARCH_LBR_IND_JMP_BIT		18 /* capture indirect jumps */
#घोषणा ARCH_LBR_REL_CALL_BIT		19 /* capture relative calls */
#घोषणा ARCH_LBR_IND_CALL_BIT		20 /* capture indirect calls */
#घोषणा ARCH_LBR_RETURN_BIT		21 /* capture near वापसs */
#घोषणा ARCH_LBR_OTHER_BRANCH_BIT	22 /* capture other branches */

#घोषणा ARCH_LBR_KERNEL			(1ULL << ARCH_LBR_KERNEL_BIT)
#घोषणा ARCH_LBR_USER			(1ULL << ARCH_LBR_USER_BIT)
#घोषणा ARCH_LBR_CALL_STACK		(1ULL << ARCH_LBR_CALL_STACK_BIT)
#घोषणा ARCH_LBR_JCC			(1ULL << ARCH_LBR_JCC_BIT)
#घोषणा ARCH_LBR_REL_JMP		(1ULL << ARCH_LBR_REL_JMP_BIT)
#घोषणा ARCH_LBR_IND_JMP		(1ULL << ARCH_LBR_IND_JMP_BIT)
#घोषणा ARCH_LBR_REL_CALL		(1ULL << ARCH_LBR_REL_CALL_BIT)
#घोषणा ARCH_LBR_IND_CALL		(1ULL << ARCH_LBR_IND_CALL_BIT)
#घोषणा ARCH_LBR_RETURN			(1ULL << ARCH_LBR_RETURN_BIT)
#घोषणा ARCH_LBR_OTHER_BRANCH		(1ULL << ARCH_LBR_OTHER_BRANCH_BIT)

#घोषणा ARCH_LBR_ANY			 \
	(ARCH_LBR_JCC			|\
	 ARCH_LBR_REL_JMP		|\
	 ARCH_LBR_IND_JMP		|\
	 ARCH_LBR_REL_CALL		|\
	 ARCH_LBR_IND_CALL		|\
	 ARCH_LBR_RETURN		|\
	 ARCH_LBR_OTHER_BRANCH)

#घोषणा ARCH_LBR_CTL_MASK			0x7f000e

अटल व्योम पूर्णांकel_pmu_lbr_filter(काष्ठा cpu_hw_events *cpuc);

अटल __always_अंतरभूत bool is_lbr_call_stack_bit_set(u64 config)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR))
		वापस !!(config & ARCH_LBR_CALL_STACK);

	वापस !!(config & LBR_CALL_STACK);
पूर्ण

/*
 * We only support LBR implementations that have FREEZE_LBRS_ON_PMI
 * otherwise it becomes near impossible to get a reliable stack.
 */

अटल व्योम __पूर्णांकel_pmu_lbr_enable(bool pmi)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	u64 debugctl, lbr_select = 0, orig_debugctl;

	/*
	 * No need to unमुक्तze manually, as v4 can करो that as part
	 * of the GLOBAL_STATUS ack.
	 */
	अगर (pmi && x86_pmu.version >= 4)
		वापस;

	/*
	 * No need to reprogram LBR_SELECT in a PMI, as it
	 * did not change.
	 */
	अगर (cpuc->lbr_sel)
		lbr_select = cpuc->lbr_sel->config & x86_pmu.lbr_sel_mask;
	अगर (!अटल_cpu_has(X86_FEATURE_ARCH_LBR) && !pmi && cpuc->lbr_sel)
		wrmsrl(MSR_LBR_SELECT, lbr_select);

	rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
	orig_debugctl = debugctl;

	अगर (!अटल_cpu_has(X86_FEATURE_ARCH_LBR))
		debugctl |= DEBUGCTLMSR_LBR;
	/*
	 * LBR callstack करोes not work well with FREEZE_LBRS_ON_PMI.
	 * If FREEZE_LBRS_ON_PMI is set, PMI near call/वापस inकाष्ठाions
	 * may cause superfluous increase/decrease of LBR_TOS.
	 */
	अगर (is_lbr_call_stack_bit_set(lbr_select))
		debugctl &= ~DEBUGCTLMSR_FREEZE_LBRS_ON_PMI;
	अन्यथा
		debugctl |= DEBUGCTLMSR_FREEZE_LBRS_ON_PMI;

	अगर (orig_debugctl != debugctl)
		wrmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);

	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR))
		wrmsrl(MSR_ARCH_LBR_CTL, lbr_select | ARCH_LBR_CTL_LBREN);
पूर्ण

अटल व्योम __पूर्णांकel_pmu_lbr_disable(व्योम)
अणु
	u64 debugctl;

	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR)) अणु
		wrmsrl(MSR_ARCH_LBR_CTL, 0);
		वापस;
	पूर्ण

	rdmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
	debugctl &= ~(DEBUGCTLMSR_LBR | DEBUGCTLMSR_FREEZE_LBRS_ON_PMI);
	wrmsrl(MSR_IA32_DEBUGCTLMSR, debugctl);
पूर्ण

व्योम पूर्णांकel_pmu_lbr_reset_32(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < x86_pmu.lbr_nr; i++)
		wrmsrl(x86_pmu.lbr_from + i, 0);
पूर्ण

व्योम पूर्णांकel_pmu_lbr_reset_64(व्योम)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < x86_pmu.lbr_nr; i++) अणु
		wrmsrl(x86_pmu.lbr_from + i, 0);
		wrmsrl(x86_pmu.lbr_to   + i, 0);
		अगर (x86_pmu.पूर्णांकel_cap.lbr_क्रमmat == LBR_FORMAT_INFO)
			wrmsrl(x86_pmu.lbr_info + i, 0);
	पूर्ण
पूर्ण

अटल व्योम पूर्णांकel_pmu_arch_lbr_reset(व्योम)
अणु
	/* Write to ARCH_LBR_DEPTH MSR, all LBR entries are reset to 0 */
	wrmsrl(MSR_ARCH_LBR_DEPTH, x86_pmu.lbr_nr);
पूर्ण

व्योम पूर्णांकel_pmu_lbr_reset(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (!x86_pmu.lbr_nr)
		वापस;

	x86_pmu.lbr_reset();

	cpuc->last_task_ctx = शून्य;
	cpuc->last_log_id = 0;
पूर्ण

/*
 * TOS = most recently recorded branch
 */
अटल अंतरभूत u64 पूर्णांकel_pmu_lbr_tos(व्योम)
अणु
	u64 tos;

	rdmsrl(x86_pmu.lbr_tos, tos);
	वापस tos;
पूर्ण

क्रमागत अणु
	LBR_NONE,
	LBR_VALID,
पूर्ण;

/*
 * For क्रमmats with LBR_TSX flags (e.g. LBR_FORMAT_EIP_FLAGS2), bits 61:62 in
 * MSR_LAST_BRANCH_FROM_x are the TSX flags when TSX is supported, but when
 * TSX is not supported they have no consistent behavior:
 *
 *   - For wrmsr(), bits 61:62 are considered part of the sign extension.
 *   - For HW updates (branch captures) bits 61:62 are always OFF and are not
 *     part of the sign extension.
 *
 * Thereक्रमe, अगर:
 *
 *   1) LBR has TSX क्रमmat
 *   2) CPU has no TSX support enabled
 *
 * ... then any value passed to wrmsr() must be sign extended to 63 bits and any
 * value from rdmsr() must be converted to have a 61 bits sign extension,
 * ignoring the TSX flags.
 */
अटल अंतरभूत bool lbr_from_signext_quirk_needed(व्योम)
अणु
	पूर्णांक lbr_क्रमmat = x86_pmu.पूर्णांकel_cap.lbr_क्रमmat;
	bool tsx_support = boot_cpu_has(X86_FEATURE_HLE) ||
			   boot_cpu_has(X86_FEATURE_RTM);

	वापस !tsx_support && (lbr_desc[lbr_क्रमmat] & LBR_TSX);
पूर्ण

अटल DEFINE_STATIC_KEY_FALSE(lbr_from_quirk_key);

/* If quirk is enabled, ensure sign extension is 63 bits: */
अंतरभूत u64 lbr_from_signext_quirk_wr(u64 val)
अणु
	अगर (अटल_branch_unlikely(&lbr_from_quirk_key)) अणु
		/*
		 * Sign extend पूर्णांकo bits 61:62 जबतक preserving bit 63.
		 *
		 * Quirk is enabled when TSX is disabled. Thereक्रमe TSX bits
		 * in val are always OFF and must be changed to be sign
		 * extension bits. Since bits 59:60 are guaranteed to be
		 * part of the sign extension bits, we can just copy them
		 * to 61:62.
		 */
		val |= (LBR_FROM_SIGNEXT_2MSB & val) << 2;
	पूर्ण
	वापस val;
पूर्ण

/*
 * If quirk is needed, ensure sign extension is 61 bits:
 */
अटल u64 lbr_from_signext_quirk_rd(u64 val)
अणु
	अगर (अटल_branch_unlikely(&lbr_from_quirk_key)) अणु
		/*
		 * Quirk is on when TSX is not enabled. Thereक्रमe TSX
		 * flags must be पढ़ो as OFF.
		 */
		val &= ~(LBR_FROM_FLAG_IN_TX | LBR_FROM_FLAG_ABORT);
	पूर्ण
	वापस val;
पूर्ण

अटल __always_अंतरभूत व्योम wrlbr_from(अचिन्हित पूर्णांक idx, u64 val)
अणु
	val = lbr_from_signext_quirk_wr(val);
	wrmsrl(x86_pmu.lbr_from + idx, val);
पूर्ण

अटल __always_अंतरभूत व्योम wrlbr_to(अचिन्हित पूर्णांक idx, u64 val)
अणु
	wrmsrl(x86_pmu.lbr_to + idx, val);
पूर्ण

अटल __always_अंतरभूत व्योम wrlbr_info(अचिन्हित पूर्णांक idx, u64 val)
अणु
	wrmsrl(x86_pmu.lbr_info + idx, val);
पूर्ण

अटल __always_अंतरभूत u64 rdlbr_from(अचिन्हित पूर्णांक idx, काष्ठा lbr_entry *lbr)
अणु
	u64 val;

	अगर (lbr)
		वापस lbr->from;

	rdmsrl(x86_pmu.lbr_from + idx, val);

	वापस lbr_from_signext_quirk_rd(val);
पूर्ण

अटल __always_अंतरभूत u64 rdlbr_to(अचिन्हित पूर्णांक idx, काष्ठा lbr_entry *lbr)
अणु
	u64 val;

	अगर (lbr)
		वापस lbr->to;

	rdmsrl(x86_pmu.lbr_to + idx, val);

	वापस val;
पूर्ण

अटल __always_अंतरभूत u64 rdlbr_info(अचिन्हित पूर्णांक idx, काष्ठा lbr_entry *lbr)
अणु
	u64 val;

	अगर (lbr)
		वापस lbr->info;

	rdmsrl(x86_pmu.lbr_info + idx, val);

	वापस val;
पूर्ण

अटल अंतरभूत व्योम
wrlbr_all(काष्ठा lbr_entry *lbr, अचिन्हित पूर्णांक idx, bool need_info)
अणु
	wrlbr_from(idx, lbr->from);
	wrlbr_to(idx, lbr->to);
	अगर (need_info)
		wrlbr_info(idx, lbr->info);
पूर्ण

अटल अंतरभूत bool
rdlbr_all(काष्ठा lbr_entry *lbr, अचिन्हित पूर्णांक idx, bool need_info)
अणु
	u64 from = rdlbr_from(idx, शून्य);

	/* Don't पढ़ो invalid entry */
	अगर (!from)
		वापस false;

	lbr->from = from;
	lbr->to = rdlbr_to(idx, शून्य);
	अगर (need_info)
		lbr->info = rdlbr_info(idx, शून्य);

	वापस true;
पूर्ण

व्योम पूर्णांकel_pmu_lbr_restore(व्योम *ctx)
अणु
	bool need_info = x86_pmu.पूर्णांकel_cap.lbr_क्रमmat == LBR_FORMAT_INFO;
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा x86_perf_task_context *task_ctx = ctx;
	पूर्णांक i;
	अचिन्हित lbr_idx, mask;
	u64 tos = task_ctx->tos;

	mask = x86_pmu.lbr_nr - 1;
	क्रम (i = 0; i < task_ctx->valid_lbrs; i++) अणु
		lbr_idx = (tos - i) & mask;
		wrlbr_all(&task_ctx->lbr[i], lbr_idx, need_info);
	पूर्ण

	क्रम (; i < x86_pmu.lbr_nr; i++) अणु
		lbr_idx = (tos - i) & mask;
		wrlbr_from(lbr_idx, 0);
		wrlbr_to(lbr_idx, 0);
		अगर (x86_pmu.पूर्णांकel_cap.lbr_क्रमmat == LBR_FORMAT_INFO)
			wrlbr_info(lbr_idx, 0);
	पूर्ण

	wrmsrl(x86_pmu.lbr_tos, tos);

	अगर (cpuc->lbr_select)
		wrmsrl(MSR_LBR_SELECT, task_ctx->lbr_sel);
पूर्ण

अटल व्योम पूर्णांकel_pmu_arch_lbr_restore(व्योम *ctx)
अणु
	काष्ठा x86_perf_task_context_arch_lbr *task_ctx = ctx;
	काष्ठा lbr_entry *entries = task_ctx->entries;
	पूर्णांक i;

	/* Fast reset the LBRs beक्रमe restore अगर the call stack is not full. */
	अगर (!entries[x86_pmu.lbr_nr - 1].from)
		पूर्णांकel_pmu_arch_lbr_reset();

	क्रम (i = 0; i < x86_pmu.lbr_nr; i++) अणु
		अगर (!entries[i].from)
			अवरोध;
		wrlbr_all(&entries[i], i, true);
	पूर्ण
पूर्ण

/*
 * Restore the Architecture LBR state from the xsave area in the perf
 * context data क्रम the task via the XRSTORS inकाष्ठाion.
 */
अटल व्योम पूर्णांकel_pmu_arch_lbr_xrstors(व्योम *ctx)
अणु
	काष्ठा x86_perf_task_context_arch_lbr_xsave *task_ctx = ctx;

	copy_kernel_to_dynamic_supervisor(&task_ctx->xsave, XFEATURE_MASK_LBR);
पूर्ण

अटल __always_अंतरभूत bool lbr_is_reset_in_cstate(व्योम *ctx)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR))
		वापस x86_pmu.lbr_deep_c_reset && !rdlbr_from(0, शून्य);

	वापस !rdlbr_from(((काष्ठा x86_perf_task_context *)ctx)->tos, शून्य);
पूर्ण

अटल व्योम __पूर्णांकel_pmu_lbr_restore(व्योम *ctx)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (task_context_opt(ctx)->lbr_callstack_users == 0 ||
	    task_context_opt(ctx)->lbr_stack_state == LBR_NONE) अणु
		पूर्णांकel_pmu_lbr_reset();
		वापस;
	पूर्ण

	/*
	 * Does not restore the LBR रेजिस्टरs, अगर
	 * - No one अन्यथा touched them, and
	 * - Was not cleared in Cstate
	 */
	अगर ((ctx == cpuc->last_task_ctx) &&
	    (task_context_opt(ctx)->log_id == cpuc->last_log_id) &&
	    !lbr_is_reset_in_cstate(ctx)) अणु
		task_context_opt(ctx)->lbr_stack_state = LBR_NONE;
		वापस;
	पूर्ण

	x86_pmu.lbr_restore(ctx);

	task_context_opt(ctx)->lbr_stack_state = LBR_NONE;
पूर्ण

व्योम पूर्णांकel_pmu_lbr_save(व्योम *ctx)
अणु
	bool need_info = x86_pmu.पूर्णांकel_cap.lbr_क्रमmat == LBR_FORMAT_INFO;
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	काष्ठा x86_perf_task_context *task_ctx = ctx;
	अचिन्हित lbr_idx, mask;
	u64 tos;
	पूर्णांक i;

	mask = x86_pmu.lbr_nr - 1;
	tos = पूर्णांकel_pmu_lbr_tos();
	क्रम (i = 0; i < x86_pmu.lbr_nr; i++) अणु
		lbr_idx = (tos - i) & mask;
		अगर (!rdlbr_all(&task_ctx->lbr[i], lbr_idx, need_info))
			अवरोध;
	पूर्ण
	task_ctx->valid_lbrs = i;
	task_ctx->tos = tos;

	अगर (cpuc->lbr_select)
		rdmsrl(MSR_LBR_SELECT, task_ctx->lbr_sel);
पूर्ण

अटल व्योम पूर्णांकel_pmu_arch_lbr_save(व्योम *ctx)
अणु
	काष्ठा x86_perf_task_context_arch_lbr *task_ctx = ctx;
	काष्ठा lbr_entry *entries = task_ctx->entries;
	पूर्णांक i;

	क्रम (i = 0; i < x86_pmu.lbr_nr; i++) अणु
		अगर (!rdlbr_all(&entries[i], i, true))
			अवरोध;
	पूर्ण

	/* LBR call stack is not full. Reset is required in restore. */
	अगर (i < x86_pmu.lbr_nr)
		entries[x86_pmu.lbr_nr - 1].from = 0;
पूर्ण

/*
 * Save the Architecture LBR state to the xsave area in the perf
 * context data क्रम the task via the XSAVES inकाष्ठाion.
 */
अटल व्योम पूर्णांकel_pmu_arch_lbr_xsaves(व्योम *ctx)
अणु
	काष्ठा x86_perf_task_context_arch_lbr_xsave *task_ctx = ctx;

	copy_dynamic_supervisor_to_kernel(&task_ctx->xsave, XFEATURE_MASK_LBR);
पूर्ण

अटल व्योम __पूर्णांकel_pmu_lbr_save(व्योम *ctx)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (task_context_opt(ctx)->lbr_callstack_users == 0) अणु
		task_context_opt(ctx)->lbr_stack_state = LBR_NONE;
		वापस;
	पूर्ण

	x86_pmu.lbr_save(ctx);

	task_context_opt(ctx)->lbr_stack_state = LBR_VALID;

	cpuc->last_task_ctx = ctx;
	cpuc->last_log_id = ++task_context_opt(ctx)->log_id;
पूर्ण

व्योम पूर्णांकel_pmu_lbr_swap_task_ctx(काष्ठा perf_event_context *prev,
				 काष्ठा perf_event_context *next)
अणु
	व्योम *prev_ctx_data, *next_ctx_data;

	swap(prev->task_ctx_data, next->task_ctx_data);

	/*
	 * Architecture specअगरic synchronization makes sense in
	 * हाल both prev->task_ctx_data and next->task_ctx_data
	 * poपूर्णांकers are allocated.
	 */

	prev_ctx_data = next->task_ctx_data;
	next_ctx_data = prev->task_ctx_data;

	अगर (!prev_ctx_data || !next_ctx_data)
		वापस;

	swap(task_context_opt(prev_ctx_data)->lbr_callstack_users,
	     task_context_opt(next_ctx_data)->lbr_callstack_users);
पूर्ण

व्योम पूर्णांकel_pmu_lbr_sched_task(काष्ठा perf_event_context *ctx, bool sched_in)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);
	व्योम *task_ctx;

	अगर (!cpuc->lbr_users)
		वापस;

	/*
	 * If LBR callstack feature is enabled and the stack was saved when
	 * the task was scheduled out, restore the stack. Otherwise flush
	 * the LBR stack.
	 */
	task_ctx = ctx ? ctx->task_ctx_data : शून्य;
	अगर (task_ctx) अणु
		अगर (sched_in)
			__पूर्णांकel_pmu_lbr_restore(task_ctx);
		अन्यथा
			__पूर्णांकel_pmu_lbr_save(task_ctx);
		वापस;
	पूर्ण

	/*
	 * Since a context चयन can flip the address space and LBR entries
	 * are not tagged with an identअगरier, we need to wipe the LBR, even क्रम
	 * per-cpu events. You simply cannot resolve the branches from the old
	 * address space.
	 */
	अगर (sched_in)
		पूर्णांकel_pmu_lbr_reset();
पूर्ण

अटल अंतरभूत bool branch_user_callstack(अचिन्हित br_sel)
अणु
	वापस (br_sel & X86_BR_USER) && (br_sel & X86_BR_CALL_STACK);
पूर्ण

व्योम पूर्णांकel_pmu_lbr_add(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (!x86_pmu.lbr_nr)
		वापस;

	अगर (event->hw.flags & PERF_X86_EVENT_LBR_SELECT)
		cpuc->lbr_select = 1;

	cpuc->br_sel = event->hw.branch_reg.reg;

	अगर (branch_user_callstack(cpuc->br_sel) && event->ctx->task_ctx_data)
		task_context_opt(event->ctx->task_ctx_data)->lbr_callstack_users++;

	/*
	 * Request pmu::sched_task() callback, which will fire inside the
	 * regular perf event scheduling, so that call will:
	 *
	 *  - restore or wipe; when LBR-callstack,
	 *  - wipe; otherwise,
	 *
	 * when this is from __perf_event_task_sched_in().
	 *
	 * However, अगर this is from perf_install_in_context(), no such callback
	 * will follow and we'll need to reset the LBR here अगर this is the
	 * first LBR event.
	 *
	 * The problem is, we cannot tell these हालs apart... but we can
	 * exclude the biggest chunk of हालs by looking at
	 * event->total_समय_running. An event that has accrued runसमय cannot
	 * be 'new'. Conversely, a new event can get installed through the
	 * context चयन path क्रम the first समय.
	 */
	अगर (x86_pmu.पूर्णांकel_cap.pebs_baseline && event->attr.precise_ip > 0)
		cpuc->lbr_pebs_users++;
	perf_sched_cb_inc(event->ctx->pmu);
	अगर (!cpuc->lbr_users++ && !event->total_समय_running)
		पूर्णांकel_pmu_lbr_reset();
पूर्ण

व्योम release_lbr_buffers(व्योम)
अणु
	काष्ठा kmem_cache *kmem_cache;
	काष्ठा cpu_hw_events *cpuc;
	पूर्णांक cpu;

	अगर (!अटल_cpu_has(X86_FEATURE_ARCH_LBR))
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		cpuc = per_cpu_ptr(&cpu_hw_events, cpu);
		kmem_cache = x86_get_pmu(cpu)->task_ctx_cache;
		अगर (kmem_cache && cpuc->lbr_xsave) अणु
			kmem_cache_मुक्त(kmem_cache, cpuc->lbr_xsave);
			cpuc->lbr_xsave = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

व्योम reserve_lbr_buffers(व्योम)
अणु
	काष्ठा kmem_cache *kmem_cache;
	काष्ठा cpu_hw_events *cpuc;
	पूर्णांक cpu;

	अगर (!अटल_cpu_has(X86_FEATURE_ARCH_LBR))
		वापस;

	क्रम_each_possible_cpu(cpu) अणु
		cpuc = per_cpu_ptr(&cpu_hw_events, cpu);
		kmem_cache = x86_get_pmu(cpu)->task_ctx_cache;
		अगर (!kmem_cache || cpuc->lbr_xsave)
			जारी;

		cpuc->lbr_xsave = kmem_cache_alloc_node(kmem_cache, GFP_KERNEL,
							cpu_to_node(cpu));
	पूर्ण
पूर्ण

व्योम पूर्णांकel_pmu_lbr_del(काष्ठा perf_event *event)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (!x86_pmu.lbr_nr)
		वापस;

	अगर (branch_user_callstack(cpuc->br_sel) &&
	    event->ctx->task_ctx_data)
		task_context_opt(event->ctx->task_ctx_data)->lbr_callstack_users--;

	अगर (event->hw.flags & PERF_X86_EVENT_LBR_SELECT)
		cpuc->lbr_select = 0;

	अगर (x86_pmu.पूर्णांकel_cap.pebs_baseline && event->attr.precise_ip > 0)
		cpuc->lbr_pebs_users--;
	cpuc->lbr_users--;
	WARN_ON_ONCE(cpuc->lbr_users < 0);
	WARN_ON_ONCE(cpuc->lbr_pebs_users < 0);
	perf_sched_cb_dec(event->ctx->pmu);
पूर्ण

अटल अंतरभूत bool vlbr_exclude_host(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	वापस test_bit(INTEL_PMC_IDX_FIXED_VLBR,
		(अचिन्हित दीर्घ *)&cpuc->पूर्णांकel_ctrl_guest_mask);
पूर्ण

व्योम पूर्णांकel_pmu_lbr_enable_all(bool pmi)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (cpuc->lbr_users && !vlbr_exclude_host())
		__पूर्णांकel_pmu_lbr_enable(pmi);
पूर्ण

व्योम पूर्णांकel_pmu_lbr_disable_all(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	अगर (cpuc->lbr_users && !vlbr_exclude_host())
		__पूर्णांकel_pmu_lbr_disable();
पूर्ण

व्योम पूर्णांकel_pmu_lbr_पढ़ो_32(काष्ठा cpu_hw_events *cpuc)
अणु
	अचिन्हित दीर्घ mask = x86_pmu.lbr_nr - 1;
	u64 tos = पूर्णांकel_pmu_lbr_tos();
	पूर्णांक i;

	क्रम (i = 0; i < x86_pmu.lbr_nr; i++) अणु
		अचिन्हित दीर्घ lbr_idx = (tos - i) & mask;
		जोड़ अणु
			काष्ठा अणु
				u32 from;
				u32 to;
			पूर्ण;
			u64     lbr;
		पूर्ण msr_lastbranch;

		rdmsrl(x86_pmu.lbr_from + lbr_idx, msr_lastbranch.lbr);

		cpuc->lbr_entries[i].from	= msr_lastbranch.from;
		cpuc->lbr_entries[i].to		= msr_lastbranch.to;
		cpuc->lbr_entries[i].mispred	= 0;
		cpuc->lbr_entries[i].predicted	= 0;
		cpuc->lbr_entries[i].in_tx	= 0;
		cpuc->lbr_entries[i].पात	= 0;
		cpuc->lbr_entries[i].cycles	= 0;
		cpuc->lbr_entries[i].type	= 0;
		cpuc->lbr_entries[i].reserved	= 0;
	पूर्ण
	cpuc->lbr_stack.nr = i;
	cpuc->lbr_stack.hw_idx = tos;
पूर्ण

/*
 * Due to lack of segmentation in Linux the effective address (offset)
 * is the same as the linear address, allowing us to merge the LIP and EIP
 * LBR क्रमmats.
 */
व्योम पूर्णांकel_pmu_lbr_पढ़ो_64(काष्ठा cpu_hw_events *cpuc)
अणु
	bool need_info = false, call_stack = false;
	अचिन्हित दीर्घ mask = x86_pmu.lbr_nr - 1;
	पूर्णांक lbr_क्रमmat = x86_pmu.पूर्णांकel_cap.lbr_क्रमmat;
	u64 tos = पूर्णांकel_pmu_lbr_tos();
	पूर्णांक i;
	पूर्णांक out = 0;
	पूर्णांक num = x86_pmu.lbr_nr;

	अगर (cpuc->lbr_sel) अणु
		need_info = !(cpuc->lbr_sel->config & LBR_NO_INFO);
		अगर (cpuc->lbr_sel->config & LBR_CALL_STACK)
			call_stack = true;
	पूर्ण

	क्रम (i = 0; i < num; i++) अणु
		अचिन्हित दीर्घ lbr_idx = (tos - i) & mask;
		u64 from, to, mis = 0, pred = 0, in_tx = 0, पात = 0;
		पूर्णांक skip = 0;
		u16 cycles = 0;
		पूर्णांक lbr_flags = lbr_desc[lbr_क्रमmat];

		from = rdlbr_from(lbr_idx, शून्य);
		to   = rdlbr_to(lbr_idx, शून्य);

		/*
		 * Read LBR call stack entries
		 * until invalid entry (0s) is detected.
		 */
		अगर (call_stack && !from)
			अवरोध;

		अगर (lbr_क्रमmat == LBR_FORMAT_INFO && need_info) अणु
			u64 info;

			info = rdlbr_info(lbr_idx, शून्य);
			mis = !!(info & LBR_INFO_MISPRED);
			pred = !mis;
			in_tx = !!(info & LBR_INFO_IN_TX);
			पात = !!(info & LBR_INFO_ABORT);
			cycles = (info & LBR_INFO_CYCLES);
		पूर्ण

		अगर (lbr_क्रमmat == LBR_FORMAT_TIME) अणु
			mis = !!(from & LBR_FROM_FLAG_MISPRED);
			pred = !mis;
			skip = 1;
			cycles = ((to >> 48) & LBR_INFO_CYCLES);

			to = (u64)((((s64)to) << 16) >> 16);
		पूर्ण

		अगर (lbr_flags & LBR_EIP_FLAGS) अणु
			mis = !!(from & LBR_FROM_FLAG_MISPRED);
			pred = !mis;
			skip = 1;
		पूर्ण
		अगर (lbr_flags & LBR_TSX) अणु
			in_tx = !!(from & LBR_FROM_FLAG_IN_TX);
			पात = !!(from & LBR_FROM_FLAG_ABORT);
			skip = 3;
		पूर्ण
		from = (u64)((((s64)from) << skip) >> skip);

		/*
		 * Some CPUs report duplicated पात records,
		 * with the second entry not having an पात bit set.
		 * Skip them here. This loop runs backwards,
		 * so we need to unकरो the previous record.
		 * If the पात just happened outside the winकरोw
		 * the extra entry cannot be हटाओd.
		 */
		अगर (पात && x86_pmu.lbr_द्विगुन_पात && out > 0)
			out--;

		cpuc->lbr_entries[out].from	 = from;
		cpuc->lbr_entries[out].to	 = to;
		cpuc->lbr_entries[out].mispred	 = mis;
		cpuc->lbr_entries[out].predicted = pred;
		cpuc->lbr_entries[out].in_tx	 = in_tx;
		cpuc->lbr_entries[out].पात	 = पात;
		cpuc->lbr_entries[out].cycles	 = cycles;
		cpuc->lbr_entries[out].type	 = 0;
		cpuc->lbr_entries[out].reserved	 = 0;
		out++;
	पूर्ण
	cpuc->lbr_stack.nr = out;
	cpuc->lbr_stack.hw_idx = tos;
पूर्ण

अटल __always_अंतरभूत पूर्णांक get_lbr_br_type(u64 info)
अणु
	अगर (!अटल_cpu_has(X86_FEATURE_ARCH_LBR) || !x86_pmu.lbr_br_type)
		वापस 0;

	वापस (info & LBR_INFO_BR_TYPE) >> LBR_INFO_BR_TYPE_OFFSET;
पूर्ण

अटल __always_अंतरभूत bool get_lbr_mispred(u64 info)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR) && !x86_pmu.lbr_mispred)
		वापस 0;

	वापस !!(info & LBR_INFO_MISPRED);
पूर्ण

अटल __always_अंतरभूत bool get_lbr_predicted(u64 info)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR) && !x86_pmu.lbr_mispred)
		वापस 0;

	वापस !(info & LBR_INFO_MISPRED);
पूर्ण

अटल __always_अंतरभूत u16 get_lbr_cycles(u64 info)
अणु
	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR) &&
	    !(x86_pmu.lbr_समयd_lbr && info & LBR_INFO_CYC_CNT_VALID))
		वापस 0;

	वापस info & LBR_INFO_CYCLES;
पूर्ण

अटल व्योम पूर्णांकel_pmu_store_lbr(काष्ठा cpu_hw_events *cpuc,
				काष्ठा lbr_entry *entries)
अणु
	काष्ठा perf_branch_entry *e;
	काष्ठा lbr_entry *lbr;
	u64 from, to, info;
	पूर्णांक i;

	क्रम (i = 0; i < x86_pmu.lbr_nr; i++) अणु
		lbr = entries ? &entries[i] : शून्य;
		e = &cpuc->lbr_entries[i];

		from = rdlbr_from(i, lbr);
		/*
		 * Read LBR entries until invalid entry (0s) is detected.
		 */
		अगर (!from)
			अवरोध;

		to = rdlbr_to(i, lbr);
		info = rdlbr_info(i, lbr);

		e->from		= from;
		e->to		= to;
		e->mispred	= get_lbr_mispred(info);
		e->predicted	= get_lbr_predicted(info);
		e->in_tx	= !!(info & LBR_INFO_IN_TX);
		e->पात	= !!(info & LBR_INFO_ABORT);
		e->cycles	= get_lbr_cycles(info);
		e->type		= get_lbr_br_type(info);
		e->reserved	= 0;
	पूर्ण

	cpuc->lbr_stack.nr = i;
पूर्ण

अटल व्योम पूर्णांकel_pmu_arch_lbr_पढ़ो(काष्ठा cpu_hw_events *cpuc)
अणु
	पूर्णांकel_pmu_store_lbr(cpuc, शून्य);
पूर्ण

अटल व्योम पूर्णांकel_pmu_arch_lbr_पढ़ो_xsave(काष्ठा cpu_hw_events *cpuc)
अणु
	काष्ठा x86_perf_task_context_arch_lbr_xsave *xsave = cpuc->lbr_xsave;

	अगर (!xsave) अणु
		पूर्णांकel_pmu_store_lbr(cpuc, शून्य);
		वापस;
	पूर्ण
	copy_dynamic_supervisor_to_kernel(&xsave->xsave, XFEATURE_MASK_LBR);

	पूर्णांकel_pmu_store_lbr(cpuc, xsave->lbr.entries);
पूर्ण

व्योम पूर्णांकel_pmu_lbr_पढ़ो(व्योम)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/*
	 * Don't पढ़ो when all LBRs users are using adaptive PEBS.
	 *
	 * This could be smarter and actually check the event,
	 * but this simple approach seems to work क्रम now.
	 */
	अगर (!cpuc->lbr_users || vlbr_exclude_host() ||
	    cpuc->lbr_users == cpuc->lbr_pebs_users)
		वापस;

	x86_pmu.lbr_पढ़ो(cpuc);

	पूर्णांकel_pmu_lbr_filter(cpuc);
पूर्ण

/*
 * SW filter is used:
 * - in हाल there is no HW filter
 * - in हाल the HW filter has errata or limitations
 */
अटल पूर्णांक पूर्णांकel_pmu_setup_sw_lbr_filter(काष्ठा perf_event *event)
अणु
	u64 br_type = event->attr.branch_sample_type;
	पूर्णांक mask = 0;

	अगर (br_type & PERF_SAMPLE_BRANCH_USER)
		mask |= X86_BR_USER;

	अगर (br_type & PERF_SAMPLE_BRANCH_KERNEL)
		mask |= X86_BR_KERNEL;

	/* we ignore BRANCH_HV here */

	अगर (br_type & PERF_SAMPLE_BRANCH_ANY)
		mask |= X86_BR_ANY;

	अगर (br_type & PERF_SAMPLE_BRANCH_ANY_CALL)
		mask |= X86_BR_ANY_CALL;

	अगर (br_type & PERF_SAMPLE_BRANCH_ANY_RETURN)
		mask |= X86_BR_RET | X86_BR_IRET | X86_BR_SYSRET;

	अगर (br_type & PERF_SAMPLE_BRANCH_IND_CALL)
		mask |= X86_BR_IND_CALL;

	अगर (br_type & PERF_SAMPLE_BRANCH_ABORT_TX)
		mask |= X86_BR_ABORT;

	अगर (br_type & PERF_SAMPLE_BRANCH_IN_TX)
		mask |= X86_BR_IN_TX;

	अगर (br_type & PERF_SAMPLE_BRANCH_NO_TX)
		mask |= X86_BR_NO_TX;

	अगर (br_type & PERF_SAMPLE_BRANCH_COND)
		mask |= X86_BR_JCC;

	अगर (br_type & PERF_SAMPLE_BRANCH_CALL_STACK) अणु
		अगर (!x86_pmu_has_lbr_callstack())
			वापस -EOPNOTSUPP;
		अगर (mask & ~(X86_BR_USER | X86_BR_KERNEL))
			वापस -EINVAL;
		mask |= X86_BR_CALL | X86_BR_IND_CALL | X86_BR_RET |
			X86_BR_CALL_STACK;
	पूर्ण

	अगर (br_type & PERF_SAMPLE_BRANCH_IND_JUMP)
		mask |= X86_BR_IND_JMP;

	अगर (br_type & PERF_SAMPLE_BRANCH_CALL)
		mask |= X86_BR_CALL | X86_BR_ZERO_CALL;

	अगर (br_type & PERF_SAMPLE_BRANCH_TYPE_SAVE)
		mask |= X86_BR_TYPE_SAVE;

	/*
	 * stash actual user request पूर्णांकo reg, it may
	 * be used by fixup code क्रम some CPU
	 */
	event->hw.branch_reg.reg = mask;
	वापस 0;
पूर्ण

/*
 * setup the HW LBR filter
 * Used only when available, may not be enough to disambiguate
 * all branches, may need the help of the SW filter
 */
अटल पूर्णांक पूर्णांकel_pmu_setup_hw_lbr_filter(काष्ठा perf_event *event)
अणु
	काष्ठा hw_perf_event_extra *reg;
	u64 br_type = event->attr.branch_sample_type;
	u64 mask = 0, v;
	पूर्णांक i;

	क्रम (i = 0; i < PERF_SAMPLE_BRANCH_MAX_SHIFT; i++) अणु
		अगर (!(br_type & (1ULL << i)))
			जारी;

		v = x86_pmu.lbr_sel_map[i];
		अगर (v == LBR_NOT_SUPP)
			वापस -EOPNOTSUPP;

		अगर (v != LBR_IGN)
			mask |= v;
	पूर्ण

	reg = &event->hw.branch_reg;
	reg->idx = EXTRA_REG_LBR;

	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR)) अणु
		reg->config = mask;
		वापस 0;
	पूर्ण

	/*
	 * The first 9 bits (LBR_SEL_MASK) in LBR_SELECT operate
	 * in suppress mode. So LBR_SELECT should be set to
	 * (~mask & LBR_SEL_MASK) | (mask & ~LBR_SEL_MASK)
	 * But the 10th bit LBR_CALL_STACK करोes not operate
	 * in suppress mode.
	 */
	reg->config = mask ^ (x86_pmu.lbr_sel_mask & ~LBR_CALL_STACK);

	अगर ((br_type & PERF_SAMPLE_BRANCH_NO_CYCLES) &&
	    (br_type & PERF_SAMPLE_BRANCH_NO_FLAGS) &&
	    (x86_pmu.पूर्णांकel_cap.lbr_क्रमmat == LBR_FORMAT_INFO))
		reg->config |= LBR_NO_INFO;

	वापस 0;
पूर्ण

पूर्णांक पूर्णांकel_pmu_setup_lbr_filter(काष्ठा perf_event *event)
अणु
	पूर्णांक ret = 0;

	/*
	 * no LBR on this PMU
	 */
	अगर (!x86_pmu.lbr_nr)
		वापस -EOPNOTSUPP;

	/*
	 * setup SW LBR filter
	 */
	ret = पूर्णांकel_pmu_setup_sw_lbr_filter(event);
	अगर (ret)
		वापस ret;

	/*
	 * setup HW LBR filter, अगर any
	 */
	अगर (x86_pmu.lbr_sel_map)
		ret = पूर्णांकel_pmu_setup_hw_lbr_filter(event);

	वापस ret;
पूर्ण

/*
 * वापस the type of control flow change at address "from"
 * inकाष्ठाion is not necessarily a branch (in हाल of पूर्णांकerrupt).
 *
 * The branch type वापसed also includes the priv level of the
 * target of the control flow change (X86_BR_USER, X86_BR_KERNEL).
 *
 * If a branch type is unknown OR the inकाष्ठाion cannot be
 * decoded (e.g., text page not present), then X86_BR_NONE is
 * वापसed.
 */
अटल पूर्णांक branch_type(अचिन्हित दीर्घ from, अचिन्हित दीर्घ to, पूर्णांक पात)
अणु
	काष्ठा insn insn;
	व्योम *addr;
	पूर्णांक bytes_पढ़ो, bytes_left;
	पूर्णांक ret = X86_BR_NONE;
	पूर्णांक ext, to_plm, from_plm;
	u8 buf[MAX_INSN_SIZE];
	पूर्णांक is64 = 0;

	to_plm = kernel_ip(to) ? X86_BR_KERNEL : X86_BR_USER;
	from_plm = kernel_ip(from) ? X86_BR_KERNEL : X86_BR_USER;

	/*
	 * maybe zero अगर lbr did not fill up after a reset by the समय
	 * we get a PMU पूर्णांकerrupt
	 */
	अगर (from == 0 || to == 0)
		वापस X86_BR_NONE;

	अगर (पात)
		वापस X86_BR_ABORT | to_plm;

	अगर (from_plm == X86_BR_USER) अणु
		/*
		 * can happen अगर measuring at the user level only
		 * and we पूर्णांकerrupt in a kernel thपढ़ो, e.g., idle.
		 */
		अगर (!current->mm)
			वापस X86_BR_NONE;

		/* may fail अगर text not present */
		bytes_left = copy_from_user_nmi(buf, (व्योम __user *)from,
						MAX_INSN_SIZE);
		bytes_पढ़ो = MAX_INSN_SIZE - bytes_left;
		अगर (!bytes_पढ़ो)
			वापस X86_BR_NONE;

		addr = buf;
	पूर्ण अन्यथा अणु
		/*
		 * The LBR logs any address in the IP, even अगर the IP just
		 * faulted. This means userspace can control the from address.
		 * Ensure we करोn't blindly पढ़ो any address by validating it is
		 * a known text address.
		 */
		अगर (kernel_text_address(from)) अणु
			addr = (व्योम *)from;
			/*
			 * Assume we can get the maximum possible size
			 * when grabbing kernel data.  This is not
			 * _strictly_ true since we could possibly be
			 * executing up next to a memory hole, but
			 * it is very unlikely to be a problem.
			 */
			bytes_पढ़ो = MAX_INSN_SIZE;
		पूर्ण अन्यथा अणु
			वापस X86_BR_NONE;
		पूर्ण
	पूर्ण

	/*
	 * decoder needs to know the ABI especially
	 * on 64-bit प्रणालीs running 32-bit apps
	 */
#अगर_घोषित CONFIG_X86_64
	is64 = kernel_ip((अचिन्हित दीर्घ)addr) || any_64bit_mode(current_pt_regs());
#पूर्ण_अगर
	insn_init(&insn, addr, bytes_पढ़ो, is64);
	अगर (insn_get_opcode(&insn))
		वापस X86_BR_ABORT;

	चयन (insn.opcode.bytes[0]) अणु
	हाल 0xf:
		चयन (insn.opcode.bytes[1]) अणु
		हाल 0x05: /* syscall */
		हाल 0x34: /* sysenter */
			ret = X86_BR_SYSCALL;
			अवरोध;
		हाल 0x07: /* sysret */
		हाल 0x35: /* sysनिकास */
			ret = X86_BR_SYSRET;
			अवरोध;
		हाल 0x80 ... 0x8f: /* conditional */
			ret = X86_BR_JCC;
			अवरोध;
		शेष:
			ret = X86_BR_NONE;
		पूर्ण
		अवरोध;
	हाल 0x70 ... 0x7f: /* conditional */
		ret = X86_BR_JCC;
		अवरोध;
	हाल 0xc2: /* near ret */
	हाल 0xc3: /* near ret */
	हाल 0xca: /* far ret */
	हाल 0xcb: /* far ret */
		ret = X86_BR_RET;
		अवरोध;
	हाल 0xcf: /* iret */
		ret = X86_BR_IRET;
		अवरोध;
	हाल 0xcc ... 0xce: /* पूर्णांक */
		ret = X86_BR_INT;
		अवरोध;
	हाल 0xe8: /* call near rel */
		अगर (insn_get_immediate(&insn) || insn.immediate1.value == 0) अणु
			/* zero length call */
			ret = X86_BR_ZERO_CALL;
			अवरोध;
		पूर्ण
		fallthrough;
	हाल 0x9a: /* call far असलolute */
		ret = X86_BR_CALL;
		अवरोध;
	हाल 0xe0 ... 0xe3: /* loop jmp */
		ret = X86_BR_JCC;
		अवरोध;
	हाल 0xe9 ... 0xeb: /* jmp */
		ret = X86_BR_JMP;
		अवरोध;
	हाल 0xff: /* call near असलolute, call far असलolute ind */
		अगर (insn_get_modrm(&insn))
			वापस X86_BR_ABORT;

		ext = (insn.modrm.bytes[0] >> 3) & 0x7;
		चयन (ext) अणु
		हाल 2: /* near ind call */
		हाल 3: /* far ind call */
			ret = X86_BR_IND_CALL;
			अवरोध;
		हाल 4:
		हाल 5:
			ret = X86_BR_IND_JMP;
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		ret = X86_BR_NONE;
	पूर्ण
	/*
	 * पूर्णांकerrupts, traps, faults (and thus ring transition) may
	 * occur on any inकाष्ठाions. Thus, to classअगरy them correctly,
	 * we need to first look at the from and to priv levels. If they
	 * are dअगरferent and to is in the kernel, then it indicates
	 * a ring transition. If the from inकाष्ठाion is not a ring
	 * transition instr (syscall, systenter, पूर्णांक), then it means
	 * it was a irq, trap or fault.
	 *
	 * we have no way of detecting kernel to kernel faults.
	 */
	अगर (from_plm == X86_BR_USER && to_plm == X86_BR_KERNEL
	    && ret != X86_BR_SYSCALL && ret != X86_BR_INT)
		ret = X86_BR_IRQ;

	/*
	 * branch priv level determined by target as
	 * is करोne by HW when LBR_SELECT is implemented
	 */
	अगर (ret != X86_BR_NONE)
		ret |= to_plm;

	वापस ret;
पूर्ण

#घोषणा X86_BR_TYPE_MAP_MAX	16

अटल पूर्णांक branch_map[X86_BR_TYPE_MAP_MAX] = अणु
	PERF_BR_CALL,		/* X86_BR_CALL */
	PERF_BR_RET,		/* X86_BR_RET */
	PERF_BR_SYSCALL,	/* X86_BR_SYSCALL */
	PERF_BR_SYSRET,		/* X86_BR_SYSRET */
	PERF_BR_UNKNOWN,	/* X86_BR_INT */
	PERF_BR_UNKNOWN,	/* X86_BR_IRET */
	PERF_BR_COND,		/* X86_BR_JCC */
	PERF_BR_UNCOND,		/* X86_BR_JMP */
	PERF_BR_UNKNOWN,	/* X86_BR_IRQ */
	PERF_BR_IND_CALL,	/* X86_BR_IND_CALL */
	PERF_BR_UNKNOWN,	/* X86_BR_ABORT */
	PERF_BR_UNKNOWN,	/* X86_BR_IN_TX */
	PERF_BR_UNKNOWN,	/* X86_BR_NO_TX */
	PERF_BR_CALL,		/* X86_BR_ZERO_CALL */
	PERF_BR_UNKNOWN,	/* X86_BR_CALL_STACK */
	PERF_BR_IND,		/* X86_BR_IND_JMP */
पूर्ण;

अटल पूर्णांक
common_branch_type(पूर्णांक type)
अणु
	पूर्णांक i;

	type >>= 2; /* skip X86_BR_USER and X86_BR_KERNEL */

	अगर (type) अणु
		i = __ffs(type);
		अगर (i < X86_BR_TYPE_MAP_MAX)
			वापस branch_map[i];
	पूर्ण

	वापस PERF_BR_UNKNOWN;
पूर्ण

क्रमागत अणु
	ARCH_LBR_BR_TYPE_JCC			= 0,
	ARCH_LBR_BR_TYPE_NEAR_IND_JMP		= 1,
	ARCH_LBR_BR_TYPE_NEAR_REL_JMP		= 2,
	ARCH_LBR_BR_TYPE_NEAR_IND_CALL		= 3,
	ARCH_LBR_BR_TYPE_NEAR_REL_CALL		= 4,
	ARCH_LBR_BR_TYPE_NEAR_RET		= 5,
	ARCH_LBR_BR_TYPE_KNOWN_MAX		= ARCH_LBR_BR_TYPE_NEAR_RET,

	ARCH_LBR_BR_TYPE_MAP_MAX		= 16,
पूर्ण;

अटल स्थिर पूर्णांक arch_lbr_br_type_map[ARCH_LBR_BR_TYPE_MAP_MAX] = अणु
	[ARCH_LBR_BR_TYPE_JCC]			= X86_BR_JCC,
	[ARCH_LBR_BR_TYPE_NEAR_IND_JMP]		= X86_BR_IND_JMP,
	[ARCH_LBR_BR_TYPE_NEAR_REL_JMP]		= X86_BR_JMP,
	[ARCH_LBR_BR_TYPE_NEAR_IND_CALL]	= X86_BR_IND_CALL,
	[ARCH_LBR_BR_TYPE_NEAR_REL_CALL]	= X86_BR_CALL,
	[ARCH_LBR_BR_TYPE_NEAR_RET]		= X86_BR_RET,
पूर्ण;

/*
 * implement actual branch filter based on user demand.
 * Hardware may not exactly satisfy that request, thus
 * we need to inspect opcodes. Mismatched branches are
 * discarded. Thereक्रमe, the number of branches वापसed
 * in PERF_SAMPLE_BRANCH_STACK sample may vary.
 */
अटल व्योम
पूर्णांकel_pmu_lbr_filter(काष्ठा cpu_hw_events *cpuc)
अणु
	u64 from, to;
	पूर्णांक br_sel = cpuc->br_sel;
	पूर्णांक i, j, type, to_plm;
	bool compress = false;

	/* अगर sampling all branches, then nothing to filter */
	अगर (((br_sel & X86_BR_ALL) == X86_BR_ALL) &&
	    ((br_sel & X86_BR_TYPE_SAVE) != X86_BR_TYPE_SAVE))
		वापस;

	क्रम (i = 0; i < cpuc->lbr_stack.nr; i++) अणु

		from = cpuc->lbr_entries[i].from;
		to = cpuc->lbr_entries[i].to;
		type = cpuc->lbr_entries[i].type;

		/*
		 * Parse the branch type recorded in LBR_x_INFO MSR.
		 * Doesn't support OTHER_BRANCH decoding क्रम now.
		 * OTHER_BRANCH branch type still rely on software decoding.
		 */
		अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR) &&
		    type <= ARCH_LBR_BR_TYPE_KNOWN_MAX) अणु
			to_plm = kernel_ip(to) ? X86_BR_KERNEL : X86_BR_USER;
			type = arch_lbr_br_type_map[type] | to_plm;
		पूर्ण अन्यथा
			type = branch_type(from, to, cpuc->lbr_entries[i].पात);
		अगर (type != X86_BR_NONE && (br_sel & X86_BR_ANYTX)) अणु
			अगर (cpuc->lbr_entries[i].in_tx)
				type |= X86_BR_IN_TX;
			अन्यथा
				type |= X86_BR_NO_TX;
		पूर्ण

		/* अगर type करोes not correspond, then discard */
		अगर (type == X86_BR_NONE || (br_sel & type) != type) अणु
			cpuc->lbr_entries[i].from = 0;
			compress = true;
		पूर्ण

		अगर ((br_sel & X86_BR_TYPE_SAVE) == X86_BR_TYPE_SAVE)
			cpuc->lbr_entries[i].type = common_branch_type(type);
	पूर्ण

	अगर (!compress)
		वापस;

	/* हटाओ all entries with from=0 */
	क्रम (i = 0; i < cpuc->lbr_stack.nr; ) अणु
		अगर (!cpuc->lbr_entries[i].from) अणु
			j = i;
			जबतक (++j < cpuc->lbr_stack.nr)
				cpuc->lbr_entries[j-1] = cpuc->lbr_entries[j];
			cpuc->lbr_stack.nr--;
			अगर (!cpuc->lbr_entries[i].from)
				जारी;
		पूर्ण
		i++;
	पूर्ण
पूर्ण

व्योम पूर्णांकel_pmu_store_pebs_lbrs(काष्ठा lbr_entry *lbr)
अणु
	काष्ठा cpu_hw_events *cpuc = this_cpu_ptr(&cpu_hw_events);

	/* Cannot get TOS क्रम large PEBS and Arch LBR */
	अगर (अटल_cpu_has(X86_FEATURE_ARCH_LBR) ||
	    (cpuc->n_pebs == cpuc->n_large_pebs))
		cpuc->lbr_stack.hw_idx = -1ULL;
	अन्यथा
		cpuc->lbr_stack.hw_idx = पूर्णांकel_pmu_lbr_tos();

	पूर्णांकel_pmu_store_lbr(cpuc, lbr);
	पूर्णांकel_pmu_lbr_filter(cpuc);
पूर्ण

/*
 * Map पूर्णांकerface branch filters onto LBR filters
 */
अटल स्थिर पूर्णांक nhm_lbr_sel_map[PERF_SAMPLE_BRANCH_MAX_SHIFT] = अणु
	[PERF_SAMPLE_BRANCH_ANY_SHIFT]		= LBR_ANY,
	[PERF_SAMPLE_BRANCH_USER_SHIFT]		= LBR_USER,
	[PERF_SAMPLE_BRANCH_KERNEL_SHIFT]	= LBR_KERNEL,
	[PERF_SAMPLE_BRANCH_HV_SHIFT]		= LBR_IGN,
	[PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT]	= LBR_RETURN | LBR_REL_JMP
						| LBR_IND_JMP | LBR_FAR,
	/*
	 * NHM/WSM erratum: must include REL_JMP+IND_JMP to get CALL branches
	 */
	[PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT] =
	 LBR_REL_CALL | LBR_IND_CALL | LBR_REL_JMP | LBR_IND_JMP | LBR_FAR,
	/*
	 * NHM/WSM erratum: must include IND_JMP to capture IND_CALL
	 */
	[PERF_SAMPLE_BRANCH_IND_CALL_SHIFT] = LBR_IND_CALL | LBR_IND_JMP,
	[PERF_SAMPLE_BRANCH_COND_SHIFT]     = LBR_JCC,
	[PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT] = LBR_IND_JMP,
पूर्ण;

अटल स्थिर पूर्णांक snb_lbr_sel_map[PERF_SAMPLE_BRANCH_MAX_SHIFT] = अणु
	[PERF_SAMPLE_BRANCH_ANY_SHIFT]		= LBR_ANY,
	[PERF_SAMPLE_BRANCH_USER_SHIFT]		= LBR_USER,
	[PERF_SAMPLE_BRANCH_KERNEL_SHIFT]	= LBR_KERNEL,
	[PERF_SAMPLE_BRANCH_HV_SHIFT]		= LBR_IGN,
	[PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT]	= LBR_RETURN | LBR_FAR,
	[PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT]	= LBR_REL_CALL | LBR_IND_CALL
						| LBR_FAR,
	[PERF_SAMPLE_BRANCH_IND_CALL_SHIFT]	= LBR_IND_CALL,
	[PERF_SAMPLE_BRANCH_COND_SHIFT]		= LBR_JCC,
	[PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT]	= LBR_IND_JMP,
	[PERF_SAMPLE_BRANCH_CALL_SHIFT]		= LBR_REL_CALL,
पूर्ण;

अटल स्थिर पूर्णांक hsw_lbr_sel_map[PERF_SAMPLE_BRANCH_MAX_SHIFT] = अणु
	[PERF_SAMPLE_BRANCH_ANY_SHIFT]		= LBR_ANY,
	[PERF_SAMPLE_BRANCH_USER_SHIFT]		= LBR_USER,
	[PERF_SAMPLE_BRANCH_KERNEL_SHIFT]	= LBR_KERNEL,
	[PERF_SAMPLE_BRANCH_HV_SHIFT]		= LBR_IGN,
	[PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT]	= LBR_RETURN | LBR_FAR,
	[PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT]	= LBR_REL_CALL | LBR_IND_CALL
						| LBR_FAR,
	[PERF_SAMPLE_BRANCH_IND_CALL_SHIFT]	= LBR_IND_CALL,
	[PERF_SAMPLE_BRANCH_COND_SHIFT]		= LBR_JCC,
	[PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT]	= LBR_REL_CALL | LBR_IND_CALL
						| LBR_RETURN | LBR_CALL_STACK,
	[PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT]	= LBR_IND_JMP,
	[PERF_SAMPLE_BRANCH_CALL_SHIFT]		= LBR_REL_CALL,
पूर्ण;

अटल पूर्णांक arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_MAX_SHIFT] = अणु
	[PERF_SAMPLE_BRANCH_ANY_SHIFT]		= ARCH_LBR_ANY,
	[PERF_SAMPLE_BRANCH_USER_SHIFT]		= ARCH_LBR_USER,
	[PERF_SAMPLE_BRANCH_KERNEL_SHIFT]	= ARCH_LBR_KERNEL,
	[PERF_SAMPLE_BRANCH_HV_SHIFT]		= LBR_IGN,
	[PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT]	= ARCH_LBR_RETURN |
						  ARCH_LBR_OTHER_BRANCH,
	[PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT]     = ARCH_LBR_REL_CALL |
						  ARCH_LBR_IND_CALL |
						  ARCH_LBR_OTHER_BRANCH,
	[PERF_SAMPLE_BRANCH_IND_CALL_SHIFT]     = ARCH_LBR_IND_CALL,
	[PERF_SAMPLE_BRANCH_COND_SHIFT]         = ARCH_LBR_JCC,
	[PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT]   = ARCH_LBR_REL_CALL |
						  ARCH_LBR_IND_CALL |
						  ARCH_LBR_RETURN |
						  ARCH_LBR_CALL_STACK,
	[PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT]	= ARCH_LBR_IND_JMP,
	[PERF_SAMPLE_BRANCH_CALL_SHIFT]		= ARCH_LBR_REL_CALL,
पूर्ण;

/* core */
व्योम __init पूर्णांकel_pmu_lbr_init_core(व्योम)
अणु
	x86_pmu.lbr_nr     = 4;
	x86_pmu.lbr_tos    = MSR_LBR_TOS;
	x86_pmu.lbr_from   = MSR_LBR_CORE_FROM;
	x86_pmu.lbr_to     = MSR_LBR_CORE_TO;

	/*
	 * SW branch filter usage:
	 * - compensate क्रम lack of HW filter
	 */
पूर्ण

/* nehalem/wesपंचांगere */
व्योम __init पूर्णांकel_pmu_lbr_init_nhm(व्योम)
अणु
	x86_pmu.lbr_nr     = 16;
	x86_pmu.lbr_tos    = MSR_LBR_TOS;
	x86_pmu.lbr_from   = MSR_LBR_NHM_FROM;
	x86_pmu.lbr_to     = MSR_LBR_NHM_TO;

	x86_pmu.lbr_sel_mask = LBR_SEL_MASK;
	x86_pmu.lbr_sel_map  = nhm_lbr_sel_map;

	/*
	 * SW branch filter usage:
	 * - workaround LBR_SEL errata (see above)
	 * - support syscall, sysret capture.
	 *   That requires LBR_FAR but that means far
	 *   jmp need to be filtered out
	 */
पूर्ण

/* sandy bridge */
व्योम __init पूर्णांकel_pmu_lbr_init_snb(व्योम)
अणु
	x86_pmu.lbr_nr	 = 16;
	x86_pmu.lbr_tos	 = MSR_LBR_TOS;
	x86_pmu.lbr_from = MSR_LBR_NHM_FROM;
	x86_pmu.lbr_to   = MSR_LBR_NHM_TO;

	x86_pmu.lbr_sel_mask = LBR_SEL_MASK;
	x86_pmu.lbr_sel_map  = snb_lbr_sel_map;

	/*
	 * SW branch filter usage:
	 * - support syscall, sysret capture.
	 *   That requires LBR_FAR but that means far
	 *   jmp need to be filtered out
	 */
पूर्ण

अटल अंतरभूत काष्ठा kmem_cache *
create_lbr_kmem_cache(माप_प्रकार size, माप_प्रकार align)
अणु
	वापस kmem_cache_create("x86_lbr", size, align, 0, शून्य);
पूर्ण

/* haswell */
व्योम पूर्णांकel_pmu_lbr_init_hsw(व्योम)
अणु
	माप_प्रकार size = माप(काष्ठा x86_perf_task_context);

	x86_pmu.lbr_nr	 = 16;
	x86_pmu.lbr_tos	 = MSR_LBR_TOS;
	x86_pmu.lbr_from = MSR_LBR_NHM_FROM;
	x86_pmu.lbr_to   = MSR_LBR_NHM_TO;

	x86_pmu.lbr_sel_mask = LBR_SEL_MASK;
	x86_pmu.lbr_sel_map  = hsw_lbr_sel_map;

	x86_get_pmu(smp_processor_id())->task_ctx_cache = create_lbr_kmem_cache(size, 0);

	अगर (lbr_from_signext_quirk_needed())
		अटल_branch_enable(&lbr_from_quirk_key);
पूर्ण

/* skylake */
__init व्योम पूर्णांकel_pmu_lbr_init_skl(व्योम)
अणु
	माप_प्रकार size = माप(काष्ठा x86_perf_task_context);

	x86_pmu.lbr_nr	 = 32;
	x86_pmu.lbr_tos	 = MSR_LBR_TOS;
	x86_pmu.lbr_from = MSR_LBR_NHM_FROM;
	x86_pmu.lbr_to   = MSR_LBR_NHM_TO;
	x86_pmu.lbr_info = MSR_LBR_INFO_0;

	x86_pmu.lbr_sel_mask = LBR_SEL_MASK;
	x86_pmu.lbr_sel_map  = hsw_lbr_sel_map;

	x86_get_pmu(smp_processor_id())->task_ctx_cache = create_lbr_kmem_cache(size, 0);

	/*
	 * SW branch filter usage:
	 * - support syscall, sysret capture.
	 *   That requires LBR_FAR but that means far
	 *   jmp need to be filtered out
	 */
पूर्ण

/* atom */
व्योम __init पूर्णांकel_pmu_lbr_init_atom(व्योम)
अणु
	/*
	 * only models starting at stepping 10 seems
	 * to have an operational LBR which can मुक्तze
	 * on PMU पूर्णांकerrupt
	 */
	अगर (boot_cpu_data.x86_model == 28
	    && boot_cpu_data.x86_stepping < 10) अणु
		pr_cont("LBR disabled due to erratum");
		वापस;
	पूर्ण

	x86_pmu.lbr_nr	   = 8;
	x86_pmu.lbr_tos    = MSR_LBR_TOS;
	x86_pmu.lbr_from   = MSR_LBR_CORE_FROM;
	x86_pmu.lbr_to     = MSR_LBR_CORE_TO;

	/*
	 * SW branch filter usage:
	 * - compensate क्रम lack of HW filter
	 */
पूर्ण

/* slm */
व्योम __init पूर्णांकel_pmu_lbr_init_slm(व्योम)
अणु
	x86_pmu.lbr_nr	   = 8;
	x86_pmu.lbr_tos    = MSR_LBR_TOS;
	x86_pmu.lbr_from   = MSR_LBR_CORE_FROM;
	x86_pmu.lbr_to     = MSR_LBR_CORE_TO;

	x86_pmu.lbr_sel_mask = LBR_SEL_MASK;
	x86_pmu.lbr_sel_map  = nhm_lbr_sel_map;

	/*
	 * SW branch filter usage:
	 * - compensate क्रम lack of HW filter
	 */
	pr_cont("8-deep LBR, ");
पूर्ण

/* Knights Landing */
व्योम पूर्णांकel_pmu_lbr_init_knl(व्योम)
अणु
	x86_pmu.lbr_nr	   = 8;
	x86_pmu.lbr_tos    = MSR_LBR_TOS;
	x86_pmu.lbr_from   = MSR_LBR_NHM_FROM;
	x86_pmu.lbr_to     = MSR_LBR_NHM_TO;

	x86_pmu.lbr_sel_mask = LBR_SEL_MASK;
	x86_pmu.lbr_sel_map  = snb_lbr_sel_map;

	/* Knights Landing करोes have MISPREDICT bit */
	अगर (x86_pmu.पूर्णांकel_cap.lbr_क्रमmat == LBR_FORMAT_LIP)
		x86_pmu.पूर्णांकel_cap.lbr_क्रमmat = LBR_FORMAT_EIP_FLAGS;
पूर्ण

/*
 * LBR state size is variable based on the max number of रेजिस्टरs.
 * This calculates the expected state size, which should match
 * what the hardware क्रमागतerates क्रम the size of XFEATURE_LBR.
 */
अटल अंतरभूत अचिन्हित पूर्णांक get_lbr_state_size(व्योम)
अणु
	वापस माप(काष्ठा arch_lbr_state) +
	       x86_pmu.lbr_nr * माप(काष्ठा lbr_entry);
पूर्ण

अटल bool is_arch_lbr_xsave_available(व्योम)
अणु
	अगर (!boot_cpu_has(X86_FEATURE_XSAVES))
		वापस false;

	/*
	 * Check the LBR state with the corresponding software काष्ठाure.
	 * Disable LBR XSAVES support अगर the size करोesn't match.
	 */
	अगर (WARN_ON(xfeature_size(XFEATURE_LBR) != get_lbr_state_size()))
		वापस false;

	वापस true;
पूर्ण

व्योम __init पूर्णांकel_pmu_arch_lbr_init(व्योम)
अणु
	काष्ठा pmu *pmu = x86_get_pmu(smp_processor_id());
	जोड़ cpuid28_eax eax;
	जोड़ cpuid28_ebx ebx;
	जोड़ cpuid28_ecx ecx;
	अचिन्हित पूर्णांक unused_edx;
	bool arch_lbr_xsave;
	माप_प्रकार size;
	u64 lbr_nr;

	/* Arch LBR Capabilities */
	cpuid(28, &eax.full, &ebx.full, &ecx.full, &unused_edx);

	lbr_nr = fls(eax.split.lbr_depth_mask) * 8;
	अगर (!lbr_nr)
		जाओ clear_arch_lbr;

	/* Apply the max depth of Arch LBR */
	अगर (wrmsrl_safe(MSR_ARCH_LBR_DEPTH, lbr_nr))
		जाओ clear_arch_lbr;

	x86_pmu.lbr_depth_mask = eax.split.lbr_depth_mask;
	x86_pmu.lbr_deep_c_reset = eax.split.lbr_deep_c_reset;
	x86_pmu.lbr_lip = eax.split.lbr_lip;
	x86_pmu.lbr_cpl = ebx.split.lbr_cpl;
	x86_pmu.lbr_filter = ebx.split.lbr_filter;
	x86_pmu.lbr_call_stack = ebx.split.lbr_call_stack;
	x86_pmu.lbr_mispred = ecx.split.lbr_mispred;
	x86_pmu.lbr_समयd_lbr = ecx.split.lbr_समयd_lbr;
	x86_pmu.lbr_br_type = ecx.split.lbr_br_type;
	x86_pmu.lbr_nr = lbr_nr;


	arch_lbr_xsave = is_arch_lbr_xsave_available();
	अगर (arch_lbr_xsave) अणु
		size = माप(काष्ठा x86_perf_task_context_arch_lbr_xsave) +
		       get_lbr_state_size();
		pmu->task_ctx_cache = create_lbr_kmem_cache(size,
							    XSAVE_ALIGNMENT);
	पूर्ण

	अगर (!pmu->task_ctx_cache) अणु
		arch_lbr_xsave = false;

		size = माप(काष्ठा x86_perf_task_context_arch_lbr) +
		       lbr_nr * माप(काष्ठा lbr_entry);
		pmu->task_ctx_cache = create_lbr_kmem_cache(size, 0);
	पूर्ण

	x86_pmu.lbr_from = MSR_ARCH_LBR_FROM_0;
	x86_pmu.lbr_to = MSR_ARCH_LBR_TO_0;
	x86_pmu.lbr_info = MSR_ARCH_LBR_INFO_0;

	/* LBR callstack requires both CPL and Branch Filtering support */
	अगर (!x86_pmu.lbr_cpl ||
	    !x86_pmu.lbr_filter ||
	    !x86_pmu.lbr_call_stack)
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_CALL_STACK_SHIFT] = LBR_NOT_SUPP;

	अगर (!x86_pmu.lbr_cpl) अणु
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_USER_SHIFT] = LBR_NOT_SUPP;
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_KERNEL_SHIFT] = LBR_NOT_SUPP;
	पूर्ण अन्यथा अगर (!x86_pmu.lbr_filter) अणु
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_ANY_SHIFT] = LBR_NOT_SUPP;
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_ANY_RETURN_SHIFT] = LBR_NOT_SUPP;
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_ANY_CALL_SHIFT] = LBR_NOT_SUPP;
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_IND_CALL_SHIFT] = LBR_NOT_SUPP;
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_COND_SHIFT] = LBR_NOT_SUPP;
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_IND_JUMP_SHIFT] = LBR_NOT_SUPP;
		arch_lbr_ctl_map[PERF_SAMPLE_BRANCH_CALL_SHIFT] = LBR_NOT_SUPP;
	पूर्ण

	x86_pmu.lbr_ctl_mask = ARCH_LBR_CTL_MASK;
	x86_pmu.lbr_ctl_map  = arch_lbr_ctl_map;

	अगर (!x86_pmu.lbr_cpl && !x86_pmu.lbr_filter)
		x86_pmu.lbr_ctl_map = शून्य;

	x86_pmu.lbr_reset = पूर्णांकel_pmu_arch_lbr_reset;
	अगर (arch_lbr_xsave) अणु
		x86_pmu.lbr_save = पूर्णांकel_pmu_arch_lbr_xsaves;
		x86_pmu.lbr_restore = पूर्णांकel_pmu_arch_lbr_xrstors;
		x86_pmu.lbr_पढ़ो = पूर्णांकel_pmu_arch_lbr_पढ़ो_xsave;
		pr_cont("XSAVE ");
	पूर्ण अन्यथा अणु
		x86_pmu.lbr_save = पूर्णांकel_pmu_arch_lbr_save;
		x86_pmu.lbr_restore = पूर्णांकel_pmu_arch_lbr_restore;
		x86_pmu.lbr_पढ़ो = पूर्णांकel_pmu_arch_lbr_पढ़ो;
	पूर्ण

	pr_cont("Architectural LBR, ");

	वापस;

clear_arch_lbr:
	clear_cpu_cap(&boot_cpu_data, X86_FEATURE_ARCH_LBR);
पूर्ण

/**
 * x86_perf_get_lbr - get the LBR records inक्रमmation
 *
 * @lbr: the caller's memory to store the LBR records inक्रमmation
 *
 * Returns: 0 indicates the LBR info has been successfully obtained
 */
पूर्णांक x86_perf_get_lbr(काष्ठा x86_pmu_lbr *lbr)
अणु
	पूर्णांक lbr_fmt = x86_pmu.पूर्णांकel_cap.lbr_क्रमmat;

	lbr->nr = x86_pmu.lbr_nr;
	lbr->from = x86_pmu.lbr_from;
	lbr->to = x86_pmu.lbr_to;
	lbr->info = (lbr_fmt == LBR_FORMAT_INFO) ? x86_pmu.lbr_info : 0;

	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(x86_perf_get_lbr);

काष्ठा event_स्थिरraपूर्णांक vlbr_स्थिरraपूर्णांक =
	__EVENT_CONSTRAINT(INTEL_FIXED_VLBR_EVENT, (1ULL << INTEL_PMC_IDX_FIXED_VLBR),
			  FIXED_EVENT_FLAGS, 1, 0, PERF_X86_EVENT_LBR_SELECT);
