<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BPF JIT compiler क्रम RV32G
 *
 * Copyright (c) 2020 Luke Nelson <luke.r.nels@gmail.com>
 * Copyright (c) 2020 Xi Wang <xi.wang@gmail.com>
 *
 * The code is based on the BPF JIT compiler क्रम RV64G by Bjथघrn Tथघpel and
 * the BPF JIT compiler क्रम 32-bit ARM by Shubham Bansal and Mircea Gherzan.
 */

#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश "bpf_jit.h"

/*
 * Stack layout during BPF program execution:
 *
 *                     high
 *     RV32 fp =>  +----------+
 *                 | saved ra |
 *                 | saved fp | RV32 callee-saved रेजिस्टरs
 *                 |   ...    |
 *                 +----------+ <= (fp - 4 * NR_SAVED_REGISTERS)
 *                 |  hi(R6)  |
 *                 |  lo(R6)  |
 *                 |  hi(R7)  | JIT scratch space क्रम BPF रेजिस्टरs
 *                 |  lo(R7)  |
 *                 |   ...    |
 *  BPF_REG_FP =>  +----------+ <= (fp - 4 * NR_SAVED_REGISTERS
 *                 |          |        - 4 * BPF_JIT_SCRATCH_REGS)
 *                 |          |
 *                 |   ...    | BPF program stack
 *                 |          |
 *     RV32 sp =>  +----------+
 *                 |          |
 *                 |   ...    | Function call stack
 *                 |          |
 *                 +----------+
 *                     low
 */

क्रमागत अणु
	/* Stack layout - these are offsets from top of JIT scratch space. */
	BPF_R6_HI,
	BPF_R6_LO,
	BPF_R7_HI,
	BPF_R7_LO,
	BPF_R8_HI,
	BPF_R8_LO,
	BPF_R9_HI,
	BPF_R9_LO,
	BPF_AX_HI,
	BPF_AX_LO,
	/* Stack space क्रम BPF_REG_6 through BPF_REG_9 and BPF_REG_AX. */
	BPF_JIT_SCRATCH_REGS,
पूर्ण;

/* Number of callee-saved रेजिस्टरs stored to stack: ra, fp, s1--s7. */
#घोषणा NR_SAVED_REGISTERS	9

/* Offset from fp क्रम BPF रेजिस्टरs stored on stack. */
#घोषणा STACK_OFFSET(k)	(-4 - (4 * NR_SAVED_REGISTERS) - (4 * (k)))

#घोषणा TMP_REG_1	(MAX_BPF_JIT_REG + 0)
#घोषणा TMP_REG_2	(MAX_BPF_JIT_REG + 1)

#घोषणा RV_REG_TCC		RV_REG_T6
#घोषणा RV_REG_TCC_SAVED	RV_REG_S7

अटल स्थिर s8 bpf2rv32[][2] = अणु
	/* Return value from in-kernel function, and निकास value from eBPF. */
	[BPF_REG_0] = अणुRV_REG_S2, RV_REG_S1पूर्ण,
	/* Arguments from eBPF program to in-kernel function. */
	[BPF_REG_1] = अणुRV_REG_A1, RV_REG_A0पूर्ण,
	[BPF_REG_2] = अणुRV_REG_A3, RV_REG_A2पूर्ण,
	[BPF_REG_3] = अणुRV_REG_A5, RV_REG_A4पूर्ण,
	[BPF_REG_4] = अणुRV_REG_A7, RV_REG_A6पूर्ण,
	[BPF_REG_5] = अणुRV_REG_S4, RV_REG_S3पूर्ण,
	/*
	 * Callee-saved रेजिस्टरs that in-kernel function will preserve.
	 * Stored on the stack.
	 */
	[BPF_REG_6] = अणुSTACK_OFFSET(BPF_R6_HI), STACK_OFFSET(BPF_R6_LO)पूर्ण,
	[BPF_REG_7] = अणुSTACK_OFFSET(BPF_R7_HI), STACK_OFFSET(BPF_R7_LO)पूर्ण,
	[BPF_REG_8] = अणुSTACK_OFFSET(BPF_R8_HI), STACK_OFFSET(BPF_R8_LO)पूर्ण,
	[BPF_REG_9] = अणुSTACK_OFFSET(BPF_R9_HI), STACK_OFFSET(BPF_R9_LO)पूर्ण,
	/* Read-only frame poपूर्णांकer to access BPF stack. */
	[BPF_REG_FP] = अणुRV_REG_S6, RV_REG_S5पूर्ण,
	/* Temporary रेजिस्टर क्रम blinding स्थिरants. Stored on the stack. */
	[BPF_REG_AX] = अणुSTACK_OFFSET(BPF_AX_HI), STACK_OFFSET(BPF_AX_LO)पूर्ण,
	/*
	 * Temporary रेजिस्टरs used by the JIT to operate on रेजिस्टरs stored
	 * on the stack. Save t0 and t1 to be used as temporaries in generated
	 * code.
	 */
	[TMP_REG_1] = अणुRV_REG_T3, RV_REG_T2पूर्ण,
	[TMP_REG_2] = अणुRV_REG_T5, RV_REG_T4पूर्ण,
पूर्ण;

अटल s8 hi(स्थिर s8 *r)
अणु
	वापस r[0];
पूर्ण

अटल s8 lo(स्थिर s8 *r)
अणु
	वापस r[1];
पूर्ण

अटल व्योम emit_imm(स्थिर s8 rd, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	u32 upper = (imm + (1 << 11)) >> 12;
	u32 lower = imm & 0xfff;

	अगर (upper) अणु
		emit(rv_lui(rd, upper), ctx);
		emit(rv_addi(rd, rd, lower), ctx);
	पूर्ण अन्यथा अणु
		emit(rv_addi(rd, RV_REG_ZERO, lower), ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_imm32(स्थिर s8 *rd, s32 imm, काष्ठा rv_jit_context *ctx)
अणु
	/* Emit immediate पूर्णांकo lower bits. */
	emit_imm(lo(rd), imm, ctx);

	/* Sign-extend पूर्णांकo upper bits. */
	अगर (imm >= 0)
		emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
	अन्यथा
		emit(rv_addi(hi(rd), RV_REG_ZERO, -1), ctx);
पूर्ण

अटल व्योम emit_imm64(स्थिर s8 *rd, s32 imm_hi, s32 imm_lo,
		       काष्ठा rv_jit_context *ctx)
अणु
	emit_imm(lo(rd), imm_lo, ctx);
	emit_imm(hi(rd), imm_hi, ctx);
पूर्ण

अटल व्योम __build_epilogue(bool is_tail_call, काष्ठा rv_jit_context *ctx)
अणु
	पूर्णांक stack_adjust = ctx->stack_size;
	स्थिर s8 *r0 = bpf2rv32[BPF_REG_0];

	/* Set वापस value अगर not tail call. */
	अगर (!is_tail_call) अणु
		emit(rv_addi(RV_REG_A0, lo(r0), 0), ctx);
		emit(rv_addi(RV_REG_A1, hi(r0), 0), ctx);
	पूर्ण

	/* Restore callee-saved रेजिस्टरs. */
	emit(rv_lw(RV_REG_RA, stack_adjust - 4, RV_REG_SP), ctx);
	emit(rv_lw(RV_REG_FP, stack_adjust - 8, RV_REG_SP), ctx);
	emit(rv_lw(RV_REG_S1, stack_adjust - 12, RV_REG_SP), ctx);
	emit(rv_lw(RV_REG_S2, stack_adjust - 16, RV_REG_SP), ctx);
	emit(rv_lw(RV_REG_S3, stack_adjust - 20, RV_REG_SP), ctx);
	emit(rv_lw(RV_REG_S4, stack_adjust - 24, RV_REG_SP), ctx);
	emit(rv_lw(RV_REG_S5, stack_adjust - 28, RV_REG_SP), ctx);
	emit(rv_lw(RV_REG_S6, stack_adjust - 32, RV_REG_SP), ctx);
	emit(rv_lw(RV_REG_S7, stack_adjust - 36, RV_REG_SP), ctx);

	emit(rv_addi(RV_REG_SP, RV_REG_SP, stack_adjust), ctx);

	अगर (is_tail_call) अणु
		/*
		 * जाओ *(t0 + 4);
		 * Skips first inकाष्ठाion of prologue which initializes tail
		 * call counter. Assumes t0 contains address of target program,
		 * see emit_bpf_tail_call.
		 */
		emit(rv_jalr(RV_REG_ZERO, RV_REG_T0, 4), ctx);
	पूर्ण अन्यथा अणु
		emit(rv_jalr(RV_REG_ZERO, RV_REG_RA, 0), ctx);
	पूर्ण
पूर्ण

अटल bool is_stacked(s8 reg)
अणु
	वापस reg < 0;
पूर्ण

अटल स्थिर s8 *bpf_get_reg64(स्थिर s8 *reg, स्थिर s8 *पंचांगp,
			       काष्ठा rv_jit_context *ctx)
अणु
	अगर (is_stacked(hi(reg))) अणु
		emit(rv_lw(hi(पंचांगp), hi(reg), RV_REG_FP), ctx);
		emit(rv_lw(lo(पंचांगp), lo(reg), RV_REG_FP), ctx);
		reg = पंचांगp;
	पूर्ण
	वापस reg;
पूर्ण

अटल व्योम bpf_put_reg64(स्थिर s8 *reg, स्थिर s8 *src,
			  काष्ठा rv_jit_context *ctx)
अणु
	अगर (is_stacked(hi(reg))) अणु
		emit(rv_sw(RV_REG_FP, hi(reg), hi(src)), ctx);
		emit(rv_sw(RV_REG_FP, lo(reg), lo(src)), ctx);
	पूर्ण
पूर्ण

अटल स्थिर s8 *bpf_get_reg32(स्थिर s8 *reg, स्थिर s8 *पंचांगp,
			       काष्ठा rv_jit_context *ctx)
अणु
	अगर (is_stacked(lo(reg))) अणु
		emit(rv_lw(lo(पंचांगp), lo(reg), RV_REG_FP), ctx);
		reg = पंचांगp;
	पूर्ण
	वापस reg;
पूर्ण

अटल व्योम bpf_put_reg32(स्थिर s8 *reg, स्थिर s8 *src,
			  काष्ठा rv_jit_context *ctx)
अणु
	अगर (is_stacked(lo(reg))) अणु
		emit(rv_sw(RV_REG_FP, lo(reg), lo(src)), ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit(rv_sw(RV_REG_FP, hi(reg), RV_REG_ZERO), ctx);
	पूर्ण अन्यथा अगर (!ctx->prog->aux->verअगरier_zext) अणु
		emit(rv_addi(hi(reg), RV_REG_ZERO, 0), ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_jump_and_link(u8 rd, s32 rvoff, bool क्रमce_jalr,
			       काष्ठा rv_jit_context *ctx)
अणु
	s32 upper, lower;

	अगर (rvoff && is_21b_पूर्णांक(rvoff) && !क्रमce_jalr) अणु
		emit(rv_jal(rd, rvoff >> 1), ctx);
		वापस;
	पूर्ण

	upper = (rvoff + (1 << 11)) >> 12;
	lower = rvoff & 0xfff;
	emit(rv_auipc(RV_REG_T1, upper), ctx);
	emit(rv_jalr(rd, RV_REG_T1, lower), ctx);
पूर्ण

अटल व्योम emit_alu_i64(स्थिर s8 *dst, s32 imm,
			 काष्ठा rv_jit_context *ctx, स्थिर u8 op)
अणु
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *rd = bpf_get_reg64(dst, पंचांगp1, ctx);

	चयन (op) अणु
	हाल BPF_MOV:
		emit_imm32(rd, imm, ctx);
		अवरोध;
	हाल BPF_AND:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_andi(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_and(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अगर (imm >= 0)
			emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
		अवरोध;
	हाल BPF_OR:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_ori(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_or(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अगर (imm < 0)
			emit(rv_ori(hi(rd), RV_REG_ZERO, -1), ctx);
		अवरोध;
	हाल BPF_XOR:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_xori(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_xor(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अगर (imm < 0)
			emit(rv_xori(hi(rd), hi(rd), -1), ctx);
		अवरोध;
	हाल BPF_LSH:
		अगर (imm >= 32) अणु
			emit(rv_slli(hi(rd), lo(rd), imm - 32), ctx);
			emit(rv_addi(lo(rd), RV_REG_ZERO, 0), ctx);
		पूर्ण अन्यथा अगर (imm == 0) अणु
			/* Do nothing. */
		पूर्ण अन्यथा अणु
			emit(rv_srli(RV_REG_T0, lo(rd), 32 - imm), ctx);
			emit(rv_slli(hi(rd), hi(rd), imm), ctx);
			emit(rv_or(hi(rd), RV_REG_T0, hi(rd)), ctx);
			emit(rv_slli(lo(rd), lo(rd), imm), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_RSH:
		अगर (imm >= 32) अणु
			emit(rv_srli(lo(rd), hi(rd), imm - 32), ctx);
			emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
		पूर्ण अन्यथा अगर (imm == 0) अणु
			/* Do nothing. */
		पूर्ण अन्यथा अणु
			emit(rv_slli(RV_REG_T0, hi(rd), 32 - imm), ctx);
			emit(rv_srli(lo(rd), lo(rd), imm), ctx);
			emit(rv_or(lo(rd), RV_REG_T0, lo(rd)), ctx);
			emit(rv_srli(hi(rd), hi(rd), imm), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_ARSH:
		अगर (imm >= 32) अणु
			emit(rv_srai(lo(rd), hi(rd), imm - 32), ctx);
			emit(rv_srai(hi(rd), hi(rd), 31), ctx);
		पूर्ण अन्यथा अगर (imm == 0) अणु
			/* Do nothing. */
		पूर्ण अन्यथा अणु
			emit(rv_slli(RV_REG_T0, hi(rd), 32 - imm), ctx);
			emit(rv_srli(lo(rd), lo(rd), imm), ctx);
			emit(rv_or(lo(rd), RV_REG_T0, lo(rd)), ctx);
			emit(rv_srai(hi(rd), hi(rd), imm), ctx);
		पूर्ण
		अवरोध;
	पूर्ण

	bpf_put_reg64(dst, rd, ctx);
पूर्ण

अटल व्योम emit_alu_i32(स्थिर s8 *dst, s32 imm,
			 काष्ठा rv_jit_context *ctx, स्थिर u8 op)
अणु
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *rd = bpf_get_reg32(dst, पंचांगp1, ctx);

	चयन (op) अणु
	हाल BPF_MOV:
		emit_imm(lo(rd), imm, ctx);
		अवरोध;
	हाल BPF_ADD:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_addi(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_add(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_SUB:
		अगर (is_12b_पूर्णांक(-imm)) अणु
			emit(rv_addi(lo(rd), lo(rd), -imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_sub(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_AND:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_andi(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_and(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_OR:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_ori(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_or(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_XOR:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_xori(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_xor(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_LSH:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_slli(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_sll(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_RSH:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_srli(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_srl(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_ARSH:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_srai(lo(rd), lo(rd), imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T0, imm, ctx);
			emit(rv_sra(lo(rd), lo(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	पूर्ण

	bpf_put_reg32(dst, rd, ctx);
पूर्ण

अटल व्योम emit_alu_r64(स्थिर s8 *dst, स्थिर s8 *src,
			 काष्ठा rv_jit_context *ctx, स्थिर u8 op)
अणु
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2rv32[TMP_REG_2];
	स्थिर s8 *rd = bpf_get_reg64(dst, पंचांगp1, ctx);
	स्थिर s8 *rs = bpf_get_reg64(src, पंचांगp2, ctx);

	चयन (op) अणु
	हाल BPF_MOV:
		emit(rv_addi(lo(rd), lo(rs), 0), ctx);
		emit(rv_addi(hi(rd), hi(rs), 0), ctx);
		अवरोध;
	हाल BPF_ADD:
		अगर (rd == rs) अणु
			emit(rv_srli(RV_REG_T0, lo(rd), 31), ctx);
			emit(rv_slli(hi(rd), hi(rd), 1), ctx);
			emit(rv_or(hi(rd), RV_REG_T0, hi(rd)), ctx);
			emit(rv_slli(lo(rd), lo(rd), 1), ctx);
		पूर्ण अन्यथा अणु
			emit(rv_add(lo(rd), lo(rd), lo(rs)), ctx);
			emit(rv_sltu(RV_REG_T0, lo(rd), lo(rs)), ctx);
			emit(rv_add(hi(rd), hi(rd), hi(rs)), ctx);
			emit(rv_add(hi(rd), hi(rd), RV_REG_T0), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_SUB:
		emit(rv_sub(RV_REG_T1, hi(rd), hi(rs)), ctx);
		emit(rv_sltu(RV_REG_T0, lo(rd), lo(rs)), ctx);
		emit(rv_sub(hi(rd), RV_REG_T1, RV_REG_T0), ctx);
		emit(rv_sub(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_AND:
		emit(rv_and(lo(rd), lo(rd), lo(rs)), ctx);
		emit(rv_and(hi(rd), hi(rd), hi(rs)), ctx);
		अवरोध;
	हाल BPF_OR:
		emit(rv_or(lo(rd), lo(rd), lo(rs)), ctx);
		emit(rv_or(hi(rd), hi(rd), hi(rs)), ctx);
		अवरोध;
	हाल BPF_XOR:
		emit(rv_xor(lo(rd), lo(rd), lo(rs)), ctx);
		emit(rv_xor(hi(rd), hi(rd), hi(rs)), ctx);
		अवरोध;
	हाल BPF_MUL:
		emit(rv_mul(RV_REG_T0, hi(rs), lo(rd)), ctx);
		emit(rv_mul(hi(rd), hi(rd), lo(rs)), ctx);
		emit(rv_mulhu(RV_REG_T1, lo(rd), lo(rs)), ctx);
		emit(rv_add(hi(rd), hi(rd), RV_REG_T0), ctx);
		emit(rv_mul(lo(rd), lo(rd), lo(rs)), ctx);
		emit(rv_add(hi(rd), hi(rd), RV_REG_T1), ctx);
		अवरोध;
	हाल BPF_LSH:
		emit(rv_addi(RV_REG_T0, lo(rs), -32), ctx);
		emit(rv_blt(RV_REG_T0, RV_REG_ZERO, 8), ctx);
		emit(rv_sll(hi(rd), lo(rd), RV_REG_T0), ctx);
		emit(rv_addi(lo(rd), RV_REG_ZERO, 0), ctx);
		emit(rv_jal(RV_REG_ZERO, 16), ctx);
		emit(rv_addi(RV_REG_T1, RV_REG_ZERO, 31), ctx);
		emit(rv_srli(RV_REG_T0, lo(rd), 1), ctx);
		emit(rv_sub(RV_REG_T1, RV_REG_T1, lo(rs)), ctx);
		emit(rv_srl(RV_REG_T0, RV_REG_T0, RV_REG_T1), ctx);
		emit(rv_sll(hi(rd), hi(rd), lo(rs)), ctx);
		emit(rv_or(hi(rd), RV_REG_T0, hi(rd)), ctx);
		emit(rv_sll(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_RSH:
		emit(rv_addi(RV_REG_T0, lo(rs), -32), ctx);
		emit(rv_blt(RV_REG_T0, RV_REG_ZERO, 8), ctx);
		emit(rv_srl(lo(rd), hi(rd), RV_REG_T0), ctx);
		emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
		emit(rv_jal(RV_REG_ZERO, 16), ctx);
		emit(rv_addi(RV_REG_T1, RV_REG_ZERO, 31), ctx);
		emit(rv_slli(RV_REG_T0, hi(rd), 1), ctx);
		emit(rv_sub(RV_REG_T1, RV_REG_T1, lo(rs)), ctx);
		emit(rv_sll(RV_REG_T0, RV_REG_T0, RV_REG_T1), ctx);
		emit(rv_srl(lo(rd), lo(rd), lo(rs)), ctx);
		emit(rv_or(lo(rd), RV_REG_T0, lo(rd)), ctx);
		emit(rv_srl(hi(rd), hi(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_ARSH:
		emit(rv_addi(RV_REG_T0, lo(rs), -32), ctx);
		emit(rv_blt(RV_REG_T0, RV_REG_ZERO, 8), ctx);
		emit(rv_sra(lo(rd), hi(rd), RV_REG_T0), ctx);
		emit(rv_srai(hi(rd), hi(rd), 31), ctx);
		emit(rv_jal(RV_REG_ZERO, 16), ctx);
		emit(rv_addi(RV_REG_T1, RV_REG_ZERO, 31), ctx);
		emit(rv_slli(RV_REG_T0, hi(rd), 1), ctx);
		emit(rv_sub(RV_REG_T1, RV_REG_T1, lo(rs)), ctx);
		emit(rv_sll(RV_REG_T0, RV_REG_T0, RV_REG_T1), ctx);
		emit(rv_srl(lo(rd), lo(rd), lo(rs)), ctx);
		emit(rv_or(lo(rd), RV_REG_T0, lo(rd)), ctx);
		emit(rv_sra(hi(rd), hi(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_NEG:
		emit(rv_sub(lo(rd), RV_REG_ZERO, lo(rd)), ctx);
		emit(rv_sltu(RV_REG_T0, RV_REG_ZERO, lo(rd)), ctx);
		emit(rv_sub(hi(rd), RV_REG_ZERO, hi(rd)), ctx);
		emit(rv_sub(hi(rd), hi(rd), RV_REG_T0), ctx);
		अवरोध;
	पूर्ण

	bpf_put_reg64(dst, rd, ctx);
पूर्ण

अटल व्योम emit_alu_r32(स्थिर s8 *dst, स्थिर s8 *src,
			 काष्ठा rv_jit_context *ctx, स्थिर u8 op)
अणु
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2rv32[TMP_REG_2];
	स्थिर s8 *rd = bpf_get_reg32(dst, पंचांगp1, ctx);
	स्थिर s8 *rs = bpf_get_reg32(src, पंचांगp2, ctx);

	चयन (op) अणु
	हाल BPF_MOV:
		emit(rv_addi(lo(rd), lo(rs), 0), ctx);
		अवरोध;
	हाल BPF_ADD:
		emit(rv_add(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_SUB:
		emit(rv_sub(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_AND:
		emit(rv_and(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_OR:
		emit(rv_or(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_XOR:
		emit(rv_xor(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_MUL:
		emit(rv_mul(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_DIV:
		emit(rv_भागu(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_MOD:
		emit(rv_remu(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_LSH:
		emit(rv_sll(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_RSH:
		emit(rv_srl(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_ARSH:
		emit(rv_sra(lo(rd), lo(rd), lo(rs)), ctx);
		अवरोध;
	हाल BPF_NEG:
		emit(rv_sub(lo(rd), RV_REG_ZERO, lo(rd)), ctx);
		अवरोध;
	पूर्ण

	bpf_put_reg32(dst, rd, ctx);
पूर्ण

अटल पूर्णांक emit_branch_r64(स्थिर s8 *src1, स्थिर s8 *src2, s32 rvoff,
			   काष्ठा rv_jit_context *ctx, स्थिर u8 op)
अणु
	पूर्णांक e, s = ctx->ninsns;
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2rv32[TMP_REG_2];

	स्थिर s8 *rs1 = bpf_get_reg64(src1, पंचांगp1, ctx);
	स्थिर s8 *rs2 = bpf_get_reg64(src2, पंचांगp2, ctx);

	/*
	 * NO_JUMP skips over the rest of the inकाष्ठाions and the
	 * emit_jump_and_link, meaning the BPF branch is not taken.
	 * JUMP skips directly to the emit_jump_and_link, meaning
	 * the BPF branch is taken.
	 *
	 * The fallthrough हाल results in the BPF branch being taken.
	 */
#घोषणा NO_JUMP(idx) (6 + (2 * (idx)))
#घोषणा JUMP(idx) (2 + (2 * (idx)))

	चयन (op) अणु
	हाल BPF_JEQ:
		emit(rv_bne(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bne(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JGT:
		emit(rv_bgtu(hi(rs1), hi(rs2), JUMP(2)), ctx);
		emit(rv_bltu(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bleu(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JLT:
		emit(rv_bltu(hi(rs1), hi(rs2), JUMP(2)), ctx);
		emit(rv_bgtu(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bgeu(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JGE:
		emit(rv_bgtu(hi(rs1), hi(rs2), JUMP(2)), ctx);
		emit(rv_bltu(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bltu(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JLE:
		emit(rv_bltu(hi(rs1), hi(rs2), JUMP(2)), ctx);
		emit(rv_bgtu(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bgtu(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JNE:
		emit(rv_bne(hi(rs1), hi(rs2), JUMP(1)), ctx);
		emit(rv_beq(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JSGT:
		emit(rv_bgt(hi(rs1), hi(rs2), JUMP(2)), ctx);
		emit(rv_blt(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bleu(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JSLT:
		emit(rv_blt(hi(rs1), hi(rs2), JUMP(2)), ctx);
		emit(rv_bgt(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bgeu(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JSGE:
		emit(rv_bgt(hi(rs1), hi(rs2), JUMP(2)), ctx);
		emit(rv_blt(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bltu(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JSLE:
		emit(rv_blt(hi(rs1), hi(rs2), JUMP(2)), ctx);
		emit(rv_bgt(hi(rs1), hi(rs2), NO_JUMP(1)), ctx);
		emit(rv_bgtu(lo(rs1), lo(rs2), NO_JUMP(0)), ctx);
		अवरोध;
	हाल BPF_JSET:
		emit(rv_and(RV_REG_T0, hi(rs1), hi(rs2)), ctx);
		emit(rv_bne(RV_REG_T0, RV_REG_ZERO, JUMP(2)), ctx);
		emit(rv_and(RV_REG_T0, lo(rs1), lo(rs2)), ctx);
		emit(rv_beq(RV_REG_T0, RV_REG_ZERO, NO_JUMP(0)), ctx);
		अवरोध;
	पूर्ण

#अघोषित NO_JUMP
#अघोषित JUMP

	e = ctx->ninsns;
	/* Adjust क्रम extra insns. */
	rvoff -= ninsns_rvoff(e - s);
	emit_jump_and_link(RV_REG_ZERO, rvoff, true, ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक emit_bcc(u8 op, u8 rd, u8 rs, पूर्णांक rvoff, काष्ठा rv_jit_context *ctx)
अणु
	पूर्णांक e, s = ctx->ninsns;
	bool far = false;
	पूर्णांक off;

	अगर (op == BPF_JSET) अणु
		/*
		 * BPF_JSET is a special हाल: it has no inverse so we always
		 * treat it as a far branch.
		 */
		far = true;
	पूर्ण अन्यथा अगर (!is_13b_पूर्णांक(rvoff)) अणु
		op = invert_bpf_cond(op);
		far = true;
	पूर्ण

	/*
	 * For a far branch, the condition is negated and we jump over the
	 * branch itself, and the two inकाष्ठाions from emit_jump_and_link.
	 * For a near branch, just use rvoff.
	 */
	off = far ? 6 : (rvoff >> 1);

	चयन (op) अणु
	हाल BPF_JEQ:
		emit(rv_beq(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JGT:
		emit(rv_bgtu(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JLT:
		emit(rv_bltu(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JGE:
		emit(rv_bgeu(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JLE:
		emit(rv_bleu(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JNE:
		emit(rv_bne(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JSGT:
		emit(rv_bgt(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JSLT:
		emit(rv_blt(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JSGE:
		emit(rv_bge(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JSLE:
		emit(rv_ble(rd, rs, off), ctx);
		अवरोध;
	हाल BPF_JSET:
		emit(rv_and(RV_REG_T0, rd, rs), ctx);
		emit(rv_beq(RV_REG_T0, RV_REG_ZERO, off), ctx);
		अवरोध;
	पूर्ण

	अगर (far) अणु
		e = ctx->ninsns;
		/* Adjust क्रम extra insns. */
		rvoff -= ninsns_rvoff(e - s);
		emit_jump_and_link(RV_REG_ZERO, rvoff, true, ctx);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक emit_branch_r32(स्थिर s8 *src1, स्थिर s8 *src2, s32 rvoff,
			   काष्ठा rv_jit_context *ctx, स्थिर u8 op)
अणु
	पूर्णांक e, s = ctx->ninsns;
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2rv32[TMP_REG_2];

	स्थिर s8 *rs1 = bpf_get_reg32(src1, पंचांगp1, ctx);
	स्थिर s8 *rs2 = bpf_get_reg32(src2, पंचांगp2, ctx);

	e = ctx->ninsns;
	/* Adjust क्रम extra insns. */
	rvoff -= ninsns_rvoff(e - s);

	अगर (emit_bcc(op, lo(rs1), lo(rs2), rvoff, ctx))
		वापस -1;

	वापस 0;
पूर्ण

अटल व्योम emit_call(bool fixed, u64 addr, काष्ठा rv_jit_context *ctx)
अणु
	स्थिर s8 *r0 = bpf2rv32[BPF_REG_0];
	स्थिर s8 *r5 = bpf2rv32[BPF_REG_5];
	u32 upper = ((u32)addr + (1 << 11)) >> 12;
	u32 lower = addr & 0xfff;

	/* R1-R4 alपढ़ोy in correct रेजिस्टरs---need to push R5 to stack. */
	emit(rv_addi(RV_REG_SP, RV_REG_SP, -16), ctx);
	emit(rv_sw(RV_REG_SP, 0, lo(r5)), ctx);
	emit(rv_sw(RV_REG_SP, 4, hi(r5)), ctx);

	/* Backup TCC. */
	emit(rv_addi(RV_REG_TCC_SAVED, RV_REG_TCC, 0), ctx);

	/*
	 * Use lui/jalr pair to jump to असलolute address. Don't use emit_imm as
	 * the number of emitted inकाष्ठाions should not depend on the value of
	 * addr.
	 */
	emit(rv_lui(RV_REG_T1, upper), ctx);
	emit(rv_jalr(RV_REG_RA, RV_REG_T1, lower), ctx);

	/* Restore TCC. */
	emit(rv_addi(RV_REG_TCC, RV_REG_TCC_SAVED, 0), ctx);

	/* Set वापस value and restore stack. */
	emit(rv_addi(lo(r0), RV_REG_A0, 0), ctx);
	emit(rv_addi(hi(r0), RV_REG_A1, 0), ctx);
	emit(rv_addi(RV_REG_SP, RV_REG_SP, 16), ctx);
पूर्ण

अटल पूर्णांक emit_bpf_tail_call(पूर्णांक insn, काष्ठा rv_jit_context *ctx)
अणु
	/*
	 * R1 -> &ctx
	 * R2 -> &array
	 * R3 -> index
	 */
	पूर्णांक tc_ninsn, off, start_insn = ctx->ninsns;
	स्थिर s8 *arr_reg = bpf2rv32[BPF_REG_2];
	स्थिर s8 *idx_reg = bpf2rv32[BPF_REG_3];

	tc_ninsn = insn ? ctx->offset[insn] - ctx->offset[insn - 1] :
		ctx->offset[0];

	/* max_entries = array->map.max_entries; */
	off = दुरत्व(काष्ठा bpf_array, map.max_entries);
	अगर (is_12b_check(off, insn))
		वापस -1;
	emit(rv_lw(RV_REG_T1, off, lo(arr_reg)), ctx);

	/*
	 * अगर (index >= max_entries)
	 *   जाओ out;
	 */
	off = ninsns_rvoff(tc_ninsn - (ctx->ninsns - start_insn));
	emit_bcc(BPF_JGE, lo(idx_reg), RV_REG_T1, off, ctx);

	/*
	 * temp_tcc = tcc - 1;
	 * अगर (tcc < 0)
	 *   जाओ out;
	 */
	emit(rv_addi(RV_REG_T1, RV_REG_TCC, -1), ctx);
	off = ninsns_rvoff(tc_ninsn - (ctx->ninsns - start_insn));
	emit_bcc(BPF_JSLT, RV_REG_TCC, RV_REG_ZERO, off, ctx);

	/*
	 * prog = array->ptrs[index];
	 * अगर (!prog)
	 *   जाओ out;
	 */
	emit(rv_slli(RV_REG_T0, lo(idx_reg), 2), ctx);
	emit(rv_add(RV_REG_T0, RV_REG_T0, lo(arr_reg)), ctx);
	off = दुरत्व(काष्ठा bpf_array, ptrs);
	अगर (is_12b_check(off, insn))
		वापस -1;
	emit(rv_lw(RV_REG_T0, off, RV_REG_T0), ctx);
	off = ninsns_rvoff(tc_ninsn - (ctx->ninsns - start_insn));
	emit_bcc(BPF_JEQ, RV_REG_T0, RV_REG_ZERO, off, ctx);

	/*
	 * tcc = temp_tcc;
	 * जाओ *(prog->bpf_func + 4);
	 */
	off = दुरत्व(काष्ठा bpf_prog, bpf_func);
	अगर (is_12b_check(off, insn))
		वापस -1;
	emit(rv_lw(RV_REG_T0, off, RV_REG_T0), ctx);
	emit(rv_addi(RV_REG_TCC, RV_REG_T1, 0), ctx);
	/* Epilogue jumps to *(t0 + 4). */
	__build_epilogue(true, ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक emit_load_r64(स्थिर s8 *dst, स्थिर s8 *src, s16 off,
			 काष्ठा rv_jit_context *ctx, स्थिर u8 size)
अणु
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2rv32[TMP_REG_2];
	स्थिर s8 *rd = bpf_get_reg64(dst, पंचांगp1, ctx);
	स्थिर s8 *rs = bpf_get_reg64(src, पंचांगp2, ctx);

	emit_imm(RV_REG_T0, off, ctx);
	emit(rv_add(RV_REG_T0, RV_REG_T0, lo(rs)), ctx);

	चयन (size) अणु
	हाल BPF_B:
		emit(rv_lbu(lo(rd), 0, RV_REG_T0), ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
		अवरोध;
	हाल BPF_H:
		emit(rv_lhu(lo(rd), 0, RV_REG_T0), ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
		अवरोध;
	हाल BPF_W:
		emit(rv_lw(lo(rd), 0, RV_REG_T0), ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
		अवरोध;
	हाल BPF_DW:
		emit(rv_lw(lo(rd), 0, RV_REG_T0), ctx);
		emit(rv_lw(hi(rd), 4, RV_REG_T0), ctx);
		अवरोध;
	पूर्ण

	bpf_put_reg64(dst, rd, ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक emit_store_r64(स्थिर s8 *dst, स्थिर s8 *src, s16 off,
			  काष्ठा rv_jit_context *ctx, स्थिर u8 size,
			  स्थिर u8 mode)
अणु
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2rv32[TMP_REG_2];
	स्थिर s8 *rd = bpf_get_reg64(dst, पंचांगp1, ctx);
	स्थिर s8 *rs = bpf_get_reg64(src, पंचांगp2, ctx);

	अगर (mode == BPF_ATOMIC && size != BPF_W)
		वापस -1;

	emit_imm(RV_REG_T0, off, ctx);
	emit(rv_add(RV_REG_T0, RV_REG_T0, lo(rd)), ctx);

	चयन (size) अणु
	हाल BPF_B:
		emit(rv_sb(RV_REG_T0, 0, lo(rs)), ctx);
		अवरोध;
	हाल BPF_H:
		emit(rv_sh(RV_REG_T0, 0, lo(rs)), ctx);
		अवरोध;
	हाल BPF_W:
		चयन (mode) अणु
		हाल BPF_MEM:
			emit(rv_sw(RV_REG_T0, 0, lo(rs)), ctx);
			अवरोध;
		हाल BPF_ATOMIC: /* Only BPF_ADD supported */
			emit(rv_amoadd_w(RV_REG_ZERO, lo(rs), RV_REG_T0, 0, 0),
			     ctx);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BPF_DW:
		emit(rv_sw(RV_REG_T0, 0, lo(rs)), ctx);
		emit(rv_sw(RV_REG_T0, 4, hi(rs)), ctx);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम emit_rev16(स्थिर s8 rd, काष्ठा rv_jit_context *ctx)
अणु
	emit(rv_slli(rd, rd, 16), ctx);
	emit(rv_slli(RV_REG_T1, rd, 8), ctx);
	emit(rv_srli(rd, rd, 8), ctx);
	emit(rv_add(RV_REG_T1, rd, RV_REG_T1), ctx);
	emit(rv_srli(rd, RV_REG_T1, 16), ctx);
पूर्ण

अटल व्योम emit_rev32(स्थिर s8 rd, काष्ठा rv_jit_context *ctx)
अणु
	emit(rv_addi(RV_REG_T1, RV_REG_ZERO, 0), ctx);
	emit(rv_andi(RV_REG_T0, rd, 255), ctx);
	emit(rv_add(RV_REG_T1, RV_REG_T1, RV_REG_T0), ctx);
	emit(rv_slli(RV_REG_T1, RV_REG_T1, 8), ctx);
	emit(rv_srli(rd, rd, 8), ctx);
	emit(rv_andi(RV_REG_T0, rd, 255), ctx);
	emit(rv_add(RV_REG_T1, RV_REG_T1, RV_REG_T0), ctx);
	emit(rv_slli(RV_REG_T1, RV_REG_T1, 8), ctx);
	emit(rv_srli(rd, rd, 8), ctx);
	emit(rv_andi(RV_REG_T0, rd, 255), ctx);
	emit(rv_add(RV_REG_T1, RV_REG_T1, RV_REG_T0), ctx);
	emit(rv_slli(RV_REG_T1, RV_REG_T1, 8), ctx);
	emit(rv_srli(rd, rd, 8), ctx);
	emit(rv_andi(RV_REG_T0, rd, 255), ctx);
	emit(rv_add(RV_REG_T1, RV_REG_T1, RV_REG_T0), ctx);
	emit(rv_addi(rd, RV_REG_T1, 0), ctx);
पूर्ण

अटल व्योम emit_zext64(स्थिर s8 *dst, काष्ठा rv_jit_context *ctx)
अणु
	स्थिर s8 *rd;
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];

	rd = bpf_get_reg64(dst, पंचांगp1, ctx);
	emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
	bpf_put_reg64(dst, rd, ctx);
पूर्ण

पूर्णांक bpf_jit_emit_insn(स्थिर काष्ठा bpf_insn *insn, काष्ठा rv_jit_context *ctx,
		      bool extra_pass)
अणु
	bool is64 = BPF_CLASS(insn->code) == BPF_ALU64 ||
		BPF_CLASS(insn->code) == BPF_JMP;
	पूर्णांक s, e, rvoff, i = insn - ctx->prog->insnsi;
	u8 code = insn->code;
	s16 off = insn->off;
	s32 imm = insn->imm;

	स्थिर s8 *dst = bpf2rv32[insn->dst_reg];
	स्थिर s8 *src = bpf2rv32[insn->src_reg];
	स्थिर s8 *पंचांगp1 = bpf2rv32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2rv32[TMP_REG_2];

	चयन (code) अणु
	हाल BPF_ALU64 | BPF_MOV | BPF_X:

	हाल BPF_ALU64 | BPF_ADD | BPF_X:
	हाल BPF_ALU64 | BPF_ADD | BPF_K:

	हाल BPF_ALU64 | BPF_SUB | BPF_X:
	हाल BPF_ALU64 | BPF_SUB | BPF_K:

	हाल BPF_ALU64 | BPF_AND | BPF_X:
	हाल BPF_ALU64 | BPF_OR | BPF_X:
	हाल BPF_ALU64 | BPF_XOR | BPF_X:

	हाल BPF_ALU64 | BPF_MUL | BPF_X:
	हाल BPF_ALU64 | BPF_MUL | BPF_K:

	हाल BPF_ALU64 | BPF_LSH | BPF_X:
	हाल BPF_ALU64 | BPF_RSH | BPF_X:
	हाल BPF_ALU64 | BPF_ARSH | BPF_X:
		अगर (BPF_SRC(code) == BPF_K) अणु
			emit_imm32(पंचांगp2, imm, ctx);
			src = पंचांगp2;
		पूर्ण
		emit_alu_r64(dst, src, ctx, BPF_OP(code));
		अवरोध;

	हाल BPF_ALU64 | BPF_NEG:
		emit_alu_r64(dst, पंचांगp2, ctx, BPF_OP(code));
		अवरोध;

	हाल BPF_ALU64 | BPF_DIV | BPF_X:
	हाल BPF_ALU64 | BPF_DIV | BPF_K:
	हाल BPF_ALU64 | BPF_MOD | BPF_X:
	हाल BPF_ALU64 | BPF_MOD | BPF_K:
		जाओ notsupported;

	हाल BPF_ALU64 | BPF_MOV | BPF_K:
	हाल BPF_ALU64 | BPF_AND | BPF_K:
	हाल BPF_ALU64 | BPF_OR | BPF_K:
	हाल BPF_ALU64 | BPF_XOR | BPF_K:
	हाल BPF_ALU64 | BPF_LSH | BPF_K:
	हाल BPF_ALU64 | BPF_RSH | BPF_K:
	हाल BPF_ALU64 | BPF_ARSH | BPF_K:
		emit_alu_i64(dst, imm, ctx, BPF_OP(code));
		अवरोध;

	हाल BPF_ALU | BPF_MOV | BPF_X:
		अगर (imm == 1) अणु
			/* Special mov32 क्रम zext. */
			emit_zext64(dst, ctx);
			अवरोध;
		पूर्ण
		fallthrough;

	हाल BPF_ALU | BPF_ADD | BPF_X:
	हाल BPF_ALU | BPF_SUB | BPF_X:
	हाल BPF_ALU | BPF_AND | BPF_X:
	हाल BPF_ALU | BPF_OR | BPF_X:
	हाल BPF_ALU | BPF_XOR | BPF_X:

	हाल BPF_ALU | BPF_MUL | BPF_X:
	हाल BPF_ALU | BPF_MUL | BPF_K:

	हाल BPF_ALU | BPF_DIV | BPF_X:
	हाल BPF_ALU | BPF_DIV | BPF_K:

	हाल BPF_ALU | BPF_MOD | BPF_X:
	हाल BPF_ALU | BPF_MOD | BPF_K:

	हाल BPF_ALU | BPF_LSH | BPF_X:
	हाल BPF_ALU | BPF_RSH | BPF_X:
	हाल BPF_ALU | BPF_ARSH | BPF_X:
		अगर (BPF_SRC(code) == BPF_K) अणु
			emit_imm32(पंचांगp2, imm, ctx);
			src = पंचांगp2;
		पूर्ण
		emit_alu_r32(dst, src, ctx, BPF_OP(code));
		अवरोध;

	हाल BPF_ALU | BPF_MOV | BPF_K:
	हाल BPF_ALU | BPF_ADD | BPF_K:
	हाल BPF_ALU | BPF_SUB | BPF_K:
	हाल BPF_ALU | BPF_AND | BPF_K:
	हाल BPF_ALU | BPF_OR | BPF_K:
	हाल BPF_ALU | BPF_XOR | BPF_K:
	हाल BPF_ALU | BPF_LSH | BPF_K:
	हाल BPF_ALU | BPF_RSH | BPF_K:
	हाल BPF_ALU | BPF_ARSH | BPF_K:
		/*
		 * mul,भाग,mod are handled in the BPF_X हाल since there are
		 * no RISC-V I-type equivalents.
		 */
		emit_alu_i32(dst, imm, ctx, BPF_OP(code));
		अवरोध;

	हाल BPF_ALU | BPF_NEG:
		/*
		 * src is ignored---choose पंचांगp2 as a dummy रेजिस्टर since it
		 * is not on the stack.
		 */
		emit_alu_r32(dst, पंचांगp2, ctx, BPF_OP(code));
		अवरोध;

	हाल BPF_ALU | BPF_END | BPF_FROM_LE:
	अणु
		स्थिर s8 *rd = bpf_get_reg64(dst, पंचांगp1, ctx);

		चयन (imm) अणु
		हाल 16:
			emit(rv_slli(lo(rd), lo(rd), 16), ctx);
			emit(rv_srli(lo(rd), lo(rd), 16), ctx);
			fallthrough;
		हाल 32:
			अगर (!ctx->prog->aux->verअगरier_zext)
				emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
			अवरोध;
		हाल 64:
			/* Do nothing. */
			अवरोध;
		शेष:
			pr_err("bpf-jit: BPF_END imm %d invalid\n", imm);
			वापस -1;
		पूर्ण

		bpf_put_reg64(dst, rd, ctx);
		अवरोध;
	पूर्ण

	हाल BPF_ALU | BPF_END | BPF_FROM_BE:
	अणु
		स्थिर s8 *rd = bpf_get_reg64(dst, पंचांगp1, ctx);

		चयन (imm) अणु
		हाल 16:
			emit_rev16(lo(rd), ctx);
			अगर (!ctx->prog->aux->verअगरier_zext)
				emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
			अवरोध;
		हाल 32:
			emit_rev32(lo(rd), ctx);
			अगर (!ctx->prog->aux->verअगरier_zext)
				emit(rv_addi(hi(rd), RV_REG_ZERO, 0), ctx);
			अवरोध;
		हाल 64:
			/* Swap upper and lower halves. */
			emit(rv_addi(RV_REG_T0, lo(rd), 0), ctx);
			emit(rv_addi(lo(rd), hi(rd), 0), ctx);
			emit(rv_addi(hi(rd), RV_REG_T0, 0), ctx);

			/* Swap each half. */
			emit_rev32(lo(rd), ctx);
			emit_rev32(hi(rd), ctx);
			अवरोध;
		शेष:
			pr_err("bpf-jit: BPF_END imm %d invalid\n", imm);
			वापस -1;
		पूर्ण

		bpf_put_reg64(dst, rd, ctx);
		अवरोध;
	पूर्ण

	हाल BPF_JMP | BPF_JA:
		rvoff = rv_offset(i, off, ctx);
		emit_jump_and_link(RV_REG_ZERO, rvoff, false, ctx);
		अवरोध;

	हाल BPF_JMP | BPF_CALL:
	अणु
		bool fixed;
		पूर्णांक ret;
		u64 addr;

		ret = bpf_jit_get_func_addr(ctx->prog, insn, extra_pass, &addr,
					    &fixed);
		अगर (ret < 0)
			वापस ret;
		emit_call(fixed, addr, ctx);
		अवरोध;
	पूर्ण

	हाल BPF_JMP | BPF_TAIL_CALL:
		अगर (emit_bpf_tail_call(i, ctx))
			वापस -1;
		अवरोध;

	हाल BPF_JMP | BPF_JEQ | BPF_X:
	हाल BPF_JMP | BPF_JEQ | BPF_K:
	हाल BPF_JMP32 | BPF_JEQ | BPF_X:
	हाल BPF_JMP32 | BPF_JEQ | BPF_K:

	हाल BPF_JMP | BPF_JNE | BPF_X:
	हाल BPF_JMP | BPF_JNE | BPF_K:
	हाल BPF_JMP32 | BPF_JNE | BPF_X:
	हाल BPF_JMP32 | BPF_JNE | BPF_K:

	हाल BPF_JMP | BPF_JLE | BPF_X:
	हाल BPF_JMP | BPF_JLE | BPF_K:
	हाल BPF_JMP32 | BPF_JLE | BPF_X:
	हाल BPF_JMP32 | BPF_JLE | BPF_K:

	हाल BPF_JMP | BPF_JLT | BPF_X:
	हाल BPF_JMP | BPF_JLT | BPF_K:
	हाल BPF_JMP32 | BPF_JLT | BPF_X:
	हाल BPF_JMP32 | BPF_JLT | BPF_K:

	हाल BPF_JMP | BPF_JGE | BPF_X:
	हाल BPF_JMP | BPF_JGE | BPF_K:
	हाल BPF_JMP32 | BPF_JGE | BPF_X:
	हाल BPF_JMP32 | BPF_JGE | BPF_K:

	हाल BPF_JMP | BPF_JGT | BPF_X:
	हाल BPF_JMP | BPF_JGT | BPF_K:
	हाल BPF_JMP32 | BPF_JGT | BPF_X:
	हाल BPF_JMP32 | BPF_JGT | BPF_K:

	हाल BPF_JMP | BPF_JSLE | BPF_X:
	हाल BPF_JMP | BPF_JSLE | BPF_K:
	हाल BPF_JMP32 | BPF_JSLE | BPF_X:
	हाल BPF_JMP32 | BPF_JSLE | BPF_K:

	हाल BPF_JMP | BPF_JSLT | BPF_X:
	हाल BPF_JMP | BPF_JSLT | BPF_K:
	हाल BPF_JMP32 | BPF_JSLT | BPF_X:
	हाल BPF_JMP32 | BPF_JSLT | BPF_K:

	हाल BPF_JMP | BPF_JSGE | BPF_X:
	हाल BPF_JMP | BPF_JSGE | BPF_K:
	हाल BPF_JMP32 | BPF_JSGE | BPF_X:
	हाल BPF_JMP32 | BPF_JSGE | BPF_K:

	हाल BPF_JMP | BPF_JSGT | BPF_X:
	हाल BPF_JMP | BPF_JSGT | BPF_K:
	हाल BPF_JMP32 | BPF_JSGT | BPF_X:
	हाल BPF_JMP32 | BPF_JSGT | BPF_K:

	हाल BPF_JMP | BPF_JSET | BPF_X:
	हाल BPF_JMP | BPF_JSET | BPF_K:
	हाल BPF_JMP32 | BPF_JSET | BPF_X:
	हाल BPF_JMP32 | BPF_JSET | BPF_K:
		rvoff = rv_offset(i, off, ctx);
		अगर (BPF_SRC(code) == BPF_K) अणु
			s = ctx->ninsns;
			emit_imm32(पंचांगp2, imm, ctx);
			src = पंचांगp2;
			e = ctx->ninsns;
			rvoff -= ninsns_rvoff(e - s);
		पूर्ण

		अगर (is64)
			emit_branch_r64(dst, src, rvoff, ctx, BPF_OP(code));
		अन्यथा
			emit_branch_r32(dst, src, rvoff, ctx, BPF_OP(code));
		अवरोध;

	हाल BPF_JMP | BPF_EXIT:
		अगर (i == ctx->prog->len - 1)
			अवरोध;

		rvoff = epilogue_offset(ctx);
		emit_jump_and_link(RV_REG_ZERO, rvoff, false, ctx);
		अवरोध;

	हाल BPF_LD | BPF_IMM | BPF_DW:
	अणु
		काष्ठा bpf_insn insn1 = insn[1];
		s32 imm_lo = imm;
		s32 imm_hi = insn1.imm;
		स्थिर s8 *rd = bpf_get_reg64(dst, पंचांगp1, ctx);

		emit_imm64(rd, imm_hi, imm_lo, ctx);
		bpf_put_reg64(dst, rd, ctx);
		वापस 1;
	पूर्ण

	हाल BPF_LDX | BPF_MEM | BPF_B:
	हाल BPF_LDX | BPF_MEM | BPF_H:
	हाल BPF_LDX | BPF_MEM | BPF_W:
	हाल BPF_LDX | BPF_MEM | BPF_DW:
		अगर (emit_load_r64(dst, src, off, ctx, BPF_SIZE(code)))
			वापस -1;
		अवरोध;

	हाल BPF_ST | BPF_MEM | BPF_B:
	हाल BPF_ST | BPF_MEM | BPF_H:
	हाल BPF_ST | BPF_MEM | BPF_W:
	हाल BPF_ST | BPF_MEM | BPF_DW:

	हाल BPF_STX | BPF_MEM | BPF_B:
	हाल BPF_STX | BPF_MEM | BPF_H:
	हाल BPF_STX | BPF_MEM | BPF_W:
	हाल BPF_STX | BPF_MEM | BPF_DW:
		अगर (BPF_CLASS(code) == BPF_ST) अणु
			emit_imm32(पंचांगp2, imm, ctx);
			src = पंचांगp2;
		पूर्ण

		अगर (emit_store_r64(dst, src, off, ctx, BPF_SIZE(code),
				   BPF_MODE(code)))
			वापस -1;
		अवरोध;

	हाल BPF_STX | BPF_ATOMIC | BPF_W:
		अगर (insn->imm != BPF_ADD) अणु
			pr_info_once(
				"bpf-jit: not supported: atomic operation %02x ***\n",
				insn->imm);
			वापस -EFAULT;
		पूर्ण

		अगर (emit_store_r64(dst, src, off, ctx, BPF_SIZE(code),
				   BPF_MODE(code)))
			वापस -1;
		अवरोध;

	/* No hardware support क्रम 8-byte atomics in RV32. */
	हाल BPF_STX | BPF_ATOMIC | BPF_DW:
		/* Fallthrough. */

notsupported:
		pr_info_once("bpf-jit: not supported: opcode %02x ***\n", code);
		वापस -EFAULT;

	शेष:
		pr_err("bpf-jit: unknown opcode %02x\n", code);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम bpf_jit_build_prologue(काष्ठा rv_jit_context *ctx)
अणु
	स्थिर s8 *fp = bpf2rv32[BPF_REG_FP];
	स्थिर s8 *r1 = bpf2rv32[BPF_REG_1];
	पूर्णांक stack_adjust = 0;
	पूर्णांक bpf_stack_adjust =
		round_up(ctx->prog->aux->stack_depth, STACK_ALIGN);

	/* Make space क्रम callee-saved रेजिस्टरs. */
	stack_adjust += NR_SAVED_REGISTERS * माप(u32);
	/* Make space क्रम BPF रेजिस्टरs on stack. */
	stack_adjust += BPF_JIT_SCRATCH_REGS * माप(u32);
	/* Make space क्रम BPF stack. */
	stack_adjust += bpf_stack_adjust;
	/* Round up क्रम stack alignment. */
	stack_adjust = round_up(stack_adjust, STACK_ALIGN);

	/*
	 * The first inकाष्ठाion sets the tail-call-counter (TCC) रेजिस्टर.
	 * This inकाष्ठाion is skipped by tail calls.
	 */
	emit(rv_addi(RV_REG_TCC, RV_REG_ZERO, MAX_TAIL_CALL_CNT), ctx);

	emit(rv_addi(RV_REG_SP, RV_REG_SP, -stack_adjust), ctx);

	/* Save callee-save रेजिस्टरs. */
	emit(rv_sw(RV_REG_SP, stack_adjust - 4, RV_REG_RA), ctx);
	emit(rv_sw(RV_REG_SP, stack_adjust - 8, RV_REG_FP), ctx);
	emit(rv_sw(RV_REG_SP, stack_adjust - 12, RV_REG_S1), ctx);
	emit(rv_sw(RV_REG_SP, stack_adjust - 16, RV_REG_S2), ctx);
	emit(rv_sw(RV_REG_SP, stack_adjust - 20, RV_REG_S3), ctx);
	emit(rv_sw(RV_REG_SP, stack_adjust - 24, RV_REG_S4), ctx);
	emit(rv_sw(RV_REG_SP, stack_adjust - 28, RV_REG_S5), ctx);
	emit(rv_sw(RV_REG_SP, stack_adjust - 32, RV_REG_S6), ctx);
	emit(rv_sw(RV_REG_SP, stack_adjust - 36, RV_REG_S7), ctx);

	/* Set fp: used as the base address क्रम stacked BPF रेजिस्टरs. */
	emit(rv_addi(RV_REG_FP, RV_REG_SP, stack_adjust), ctx);

	/* Set up BPF frame poपूर्णांकer. */
	emit(rv_addi(lo(fp), RV_REG_SP, bpf_stack_adjust), ctx);
	emit(rv_addi(hi(fp), RV_REG_ZERO, 0), ctx);

	/* Set up BPF context poपूर्णांकer. */
	emit(rv_addi(lo(r1), RV_REG_A0, 0), ctx);
	emit(rv_addi(hi(r1), RV_REG_ZERO, 0), ctx);

	ctx->stack_size = stack_adjust;
पूर्ण

व्योम bpf_jit_build_epilogue(काष्ठा rv_jit_context *ctx)
अणु
	__build_epilogue(false, ctx);
पूर्ण
