<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* BPF JIT compiler क्रम RV64G
 *
 * Copyright(c) 2019 Bjथघrn Tथघpel <bjorn.topel@gmail.com>
 *
 */

#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश "bpf_jit.h"

#घोषणा RV_REG_TCC RV_REG_A6
#घोषणा RV_REG_TCC_SAVED RV_REG_S6 /* Store A6 in S6 अगर program करो calls */

अटल स्थिर पूर्णांक regmap[] = अणु
	[BPF_REG_0] =	RV_REG_A5,
	[BPF_REG_1] =	RV_REG_A0,
	[BPF_REG_2] =	RV_REG_A1,
	[BPF_REG_3] =	RV_REG_A2,
	[BPF_REG_4] =	RV_REG_A3,
	[BPF_REG_5] =	RV_REG_A4,
	[BPF_REG_6] =	RV_REG_S1,
	[BPF_REG_7] =	RV_REG_S2,
	[BPF_REG_8] =	RV_REG_S3,
	[BPF_REG_9] =	RV_REG_S4,
	[BPF_REG_FP] =	RV_REG_S5,
	[BPF_REG_AX] =	RV_REG_T0,
पूर्ण;

क्रमागत अणु
	RV_CTX_F_SEEN_TAIL_CALL =	0,
	RV_CTX_F_SEEN_CALL =		RV_REG_RA,
	RV_CTX_F_SEEN_S1 =		RV_REG_S1,
	RV_CTX_F_SEEN_S2 =		RV_REG_S2,
	RV_CTX_F_SEEN_S3 =		RV_REG_S3,
	RV_CTX_F_SEEN_S4 =		RV_REG_S4,
	RV_CTX_F_SEEN_S5 =		RV_REG_S5,
	RV_CTX_F_SEEN_S6 =		RV_REG_S6,
पूर्ण;

अटल u8 bpf_to_rv_reg(पूर्णांक bpf_reg, काष्ठा rv_jit_context *ctx)
अणु
	u8 reg = regmap[bpf_reg];

	चयन (reg) अणु
	हाल RV_CTX_F_SEEN_S1:
	हाल RV_CTX_F_SEEN_S2:
	हाल RV_CTX_F_SEEN_S3:
	हाल RV_CTX_F_SEEN_S4:
	हाल RV_CTX_F_SEEN_S5:
	हाल RV_CTX_F_SEEN_S6:
		__set_bit(reg, &ctx->flags);
	पूर्ण
	वापस reg;
पूर्ण;

अटल bool seen_reg(पूर्णांक reg, काष्ठा rv_jit_context *ctx)
अणु
	चयन (reg) अणु
	हाल RV_CTX_F_SEEN_CALL:
	हाल RV_CTX_F_SEEN_S1:
	हाल RV_CTX_F_SEEN_S2:
	हाल RV_CTX_F_SEEN_S3:
	हाल RV_CTX_F_SEEN_S4:
	हाल RV_CTX_F_SEEN_S5:
	हाल RV_CTX_F_SEEN_S6:
		वापस test_bit(reg, &ctx->flags);
	पूर्ण
	वापस false;
पूर्ण

अटल व्योम mark_fp(काष्ठा rv_jit_context *ctx)
अणु
	__set_bit(RV_CTX_F_SEEN_S5, &ctx->flags);
पूर्ण

अटल व्योम mark_call(काष्ठा rv_jit_context *ctx)
अणु
	__set_bit(RV_CTX_F_SEEN_CALL, &ctx->flags);
पूर्ण

अटल bool seen_call(काष्ठा rv_jit_context *ctx)
अणु
	वापस test_bit(RV_CTX_F_SEEN_CALL, &ctx->flags);
पूर्ण

अटल व्योम mark_tail_call(काष्ठा rv_jit_context *ctx)
अणु
	__set_bit(RV_CTX_F_SEEN_TAIL_CALL, &ctx->flags);
पूर्ण

अटल bool seen_tail_call(काष्ठा rv_jit_context *ctx)
अणु
	वापस test_bit(RV_CTX_F_SEEN_TAIL_CALL, &ctx->flags);
पूर्ण

अटल u8 rv_tail_call_reg(काष्ठा rv_jit_context *ctx)
अणु
	mark_tail_call(ctx);

	अगर (seen_call(ctx)) अणु
		__set_bit(RV_CTX_F_SEEN_S6, &ctx->flags);
		वापस RV_REG_S6;
	पूर्ण
	वापस RV_REG_A6;
पूर्ण

अटल bool is_32b_पूर्णांक(s64 val)
अणु
	वापस -(1L << 31) <= val && val < (1L << 31);
पूर्ण

अटल bool in_auipc_jalr_range(s64 val)
अणु
	/*
	 * auipc+jalr can reach any चिन्हित PC-relative offset in the range
	 * [-2^31 - 2^11, 2^31 - 2^11).
	 */
	वापस (-(1L << 31) - (1L << 11)) <= val &&
		val < ((1L << 31) - (1L << 11));
पूर्ण

अटल व्योम emit_imm(u8 rd, s64 val, काष्ठा rv_jit_context *ctx)
अणु
	/* Note that the immediate from the add is sign-extended,
	 * which means that we need to compensate this by adding 2^12,
	 * when the 12th bit is set. A simpler way of करोing this, and
	 * getting rid of the check, is to just add 2**11 beक्रमe the
	 * shअगरt. The "Loading a 32-Bit constant" example from the
	 * "Computer Organization and Design, RISC-V edition" book by
	 * Patterson/Hennessy highlights this fact.
	 *
	 * This also means that we need to process LSB to MSB.
	 */
	s64 upper = (val + (1 << 11)) >> 12;
	/* Sign-extend lower 12 bits to 64 bits since immediates क्रम li, addiw,
	 * and addi are चिन्हित and RVC checks will perक्रमm चिन्हित comparisons.
	 */
	s64 lower = ((val & 0xfff) << 52) >> 52;
	पूर्णांक shअगरt;

	अगर (is_32b_पूर्णांक(val)) अणु
		अगर (upper)
			emit_lui(rd, upper, ctx);

		अगर (!upper) अणु
			emit_li(rd, lower, ctx);
			वापस;
		पूर्ण

		emit_addiw(rd, rd, lower, ctx);
		वापस;
	पूर्ण

	shअगरt = __ffs(upper);
	upper >>= shअगरt;
	shअगरt += 12;

	emit_imm(rd, upper, ctx);

	emit_slli(rd, rd, shअगरt, ctx);
	अगर (lower)
		emit_addi(rd, rd, lower, ctx);
पूर्ण

अटल व्योम __build_epilogue(bool is_tail_call, काष्ठा rv_jit_context *ctx)
अणु
	पूर्णांक stack_adjust = ctx->stack_size, store_offset = stack_adjust - 8;

	अगर (seen_reg(RV_REG_RA, ctx)) अणु
		emit_ld(RV_REG_RA, store_offset, RV_REG_SP, ctx);
		store_offset -= 8;
	पूर्ण
	emit_ld(RV_REG_FP, store_offset, RV_REG_SP, ctx);
	store_offset -= 8;
	अगर (seen_reg(RV_REG_S1, ctx)) अणु
		emit_ld(RV_REG_S1, store_offset, RV_REG_SP, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S2, ctx)) अणु
		emit_ld(RV_REG_S2, store_offset, RV_REG_SP, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S3, ctx)) अणु
		emit_ld(RV_REG_S3, store_offset, RV_REG_SP, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S4, ctx)) अणु
		emit_ld(RV_REG_S4, store_offset, RV_REG_SP, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S5, ctx)) अणु
		emit_ld(RV_REG_S5, store_offset, RV_REG_SP, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S6, ctx)) अणु
		emit_ld(RV_REG_S6, store_offset, RV_REG_SP, ctx);
		store_offset -= 8;
	पूर्ण

	emit_addi(RV_REG_SP, RV_REG_SP, stack_adjust, ctx);
	/* Set वापस value. */
	अगर (!is_tail_call)
		emit_mv(RV_REG_A0, RV_REG_A5, ctx);
	emit_jalr(RV_REG_ZERO, is_tail_call ? RV_REG_T3 : RV_REG_RA,
		  is_tail_call ? 4 : 0, /* skip TCC init */
		  ctx);
पूर्ण

अटल व्योम emit_bcc(u8 cond, u8 rd, u8 rs, पूर्णांक rvoff,
		     काष्ठा rv_jit_context *ctx)
अणु
	चयन (cond) अणु
	हाल BPF_JEQ:
		emit(rv_beq(rd, rs, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JGT:
		emit(rv_bltu(rs, rd, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JLT:
		emit(rv_bltu(rd, rs, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JGE:
		emit(rv_bgeu(rd, rs, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JLE:
		emit(rv_bgeu(rs, rd, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JNE:
		emit(rv_bne(rd, rs, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JSGT:
		emit(rv_blt(rs, rd, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JSLT:
		emit(rv_blt(rd, rs, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JSGE:
		emit(rv_bge(rd, rs, rvoff >> 1), ctx);
		वापस;
	हाल BPF_JSLE:
		emit(rv_bge(rs, rd, rvoff >> 1), ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_branch(u8 cond, u8 rd, u8 rs, पूर्णांक rvoff,
			काष्ठा rv_jit_context *ctx)
अणु
	s64 upper, lower;

	अगर (is_13b_पूर्णांक(rvoff)) अणु
		emit_bcc(cond, rd, rs, rvoff, ctx);
		वापस;
	पूर्ण

	/* Adjust क्रम jal */
	rvoff -= 4;

	/* Transक्रमm, e.g.:
	 *   bne rd,rs,foo
	 * to
	 *   beq rd,rs,<.L1>
	 *   (auipc foo)
	 *   jal(r) foo
	 * .L1
	 */
	cond = invert_bpf_cond(cond);
	अगर (is_21b_पूर्णांक(rvoff)) अणु
		emit_bcc(cond, rd, rs, 8, ctx);
		emit(rv_jal(RV_REG_ZERO, rvoff >> 1), ctx);
		वापस;
	पूर्ण

	/* 32b No need क्रम an additional rvoff adjusपंचांगent, since we
	 * get that from the auipc at PC', where PC = PC' + 4.
	 */
	upper = (rvoff + (1 << 11)) >> 12;
	lower = rvoff & 0xfff;

	emit_bcc(cond, rd, rs, 12, ctx);
	emit(rv_auipc(RV_REG_T1, upper), ctx);
	emit(rv_jalr(RV_REG_ZERO, RV_REG_T1, lower), ctx);
पूर्ण

अटल व्योम emit_zext_32(u8 reg, काष्ठा rv_jit_context *ctx)
अणु
	emit_slli(reg, reg, 32, ctx);
	emit_srli(reg, reg, 32, ctx);
पूर्ण

अटल पूर्णांक emit_bpf_tail_call(पूर्णांक insn, काष्ठा rv_jit_context *ctx)
अणु
	पूर्णांक tc_ninsn, off, start_insn = ctx->ninsns;
	u8 tcc = rv_tail_call_reg(ctx);

	/* a0: &ctx
	 * a1: &array
	 * a2: index
	 *
	 * अगर (index >= array->map.max_entries)
	 *	जाओ out;
	 */
	tc_ninsn = insn ? ctx->offset[insn] - ctx->offset[insn - 1] :
		   ctx->offset[0];
	emit_zext_32(RV_REG_A2, ctx);

	off = दुरत्व(काष्ठा bpf_array, map.max_entries);
	अगर (is_12b_check(off, insn))
		वापस -1;
	emit(rv_lwu(RV_REG_T1, off, RV_REG_A1), ctx);
	off = ninsns_rvoff(tc_ninsn - (ctx->ninsns - start_insn));
	emit_branch(BPF_JGE, RV_REG_A2, RV_REG_T1, off, ctx);

	/* अगर (TCC-- < 0)
	 *     जाओ out;
	 */
	emit_addi(RV_REG_T1, tcc, -1, ctx);
	off = ninsns_rvoff(tc_ninsn - (ctx->ninsns - start_insn));
	emit_branch(BPF_JSLT, tcc, RV_REG_ZERO, off, ctx);

	/* prog = array->ptrs[index];
	 * अगर (!prog)
	 *     जाओ out;
	 */
	emit_slli(RV_REG_T2, RV_REG_A2, 3, ctx);
	emit_add(RV_REG_T2, RV_REG_T2, RV_REG_A1, ctx);
	off = दुरत्व(काष्ठा bpf_array, ptrs);
	अगर (is_12b_check(off, insn))
		वापस -1;
	emit_ld(RV_REG_T2, off, RV_REG_T2, ctx);
	off = ninsns_rvoff(tc_ninsn - (ctx->ninsns - start_insn));
	emit_branch(BPF_JEQ, RV_REG_T2, RV_REG_ZERO, off, ctx);

	/* जाओ *(prog->bpf_func + 4); */
	off = दुरत्व(काष्ठा bpf_prog, bpf_func);
	अगर (is_12b_check(off, insn))
		वापस -1;
	emit_ld(RV_REG_T3, off, RV_REG_T2, ctx);
	emit_mv(RV_REG_TCC, RV_REG_T1, ctx);
	__build_epilogue(true, ctx);
	वापस 0;
पूर्ण

अटल व्योम init_regs(u8 *rd, u8 *rs, स्थिर काष्ठा bpf_insn *insn,
		      काष्ठा rv_jit_context *ctx)
अणु
	u8 code = insn->code;

	चयन (code) अणु
	हाल BPF_JMP | BPF_JA:
	हाल BPF_JMP | BPF_CALL:
	हाल BPF_JMP | BPF_EXIT:
	हाल BPF_JMP | BPF_TAIL_CALL:
		अवरोध;
	शेष:
		*rd = bpf_to_rv_reg(insn->dst_reg, ctx);
	पूर्ण

	अगर (code & (BPF_ALU | BPF_X) || code & (BPF_ALU64 | BPF_X) ||
	    code & (BPF_JMP | BPF_X) || code & (BPF_JMP32 | BPF_X) ||
	    code & BPF_LDX || code & BPF_STX)
		*rs = bpf_to_rv_reg(insn->src_reg, ctx);
पूर्ण

अटल व्योम emit_zext_32_rd_rs(u8 *rd, u8 *rs, काष्ठा rv_jit_context *ctx)
अणु
	emit_mv(RV_REG_T2, *rd, ctx);
	emit_zext_32(RV_REG_T2, ctx);
	emit_mv(RV_REG_T1, *rs, ctx);
	emit_zext_32(RV_REG_T1, ctx);
	*rd = RV_REG_T2;
	*rs = RV_REG_T1;
पूर्ण

अटल व्योम emit_sext_32_rd_rs(u8 *rd, u8 *rs, काष्ठा rv_jit_context *ctx)
अणु
	emit_addiw(RV_REG_T2, *rd, 0, ctx);
	emit_addiw(RV_REG_T1, *rs, 0, ctx);
	*rd = RV_REG_T2;
	*rs = RV_REG_T1;
पूर्ण

अटल व्योम emit_zext_32_rd_t1(u8 *rd, काष्ठा rv_jit_context *ctx)
अणु
	emit_mv(RV_REG_T2, *rd, ctx);
	emit_zext_32(RV_REG_T2, ctx);
	emit_zext_32(RV_REG_T1, ctx);
	*rd = RV_REG_T2;
पूर्ण

अटल व्योम emit_sext_32_rd(u8 *rd, काष्ठा rv_jit_context *ctx)
अणु
	emit_addiw(RV_REG_T2, *rd, 0, ctx);
	*rd = RV_REG_T2;
पूर्ण

अटल पूर्णांक emit_jump_and_link(u8 rd, s64 rvoff, bool क्रमce_jalr,
			      काष्ठा rv_jit_context *ctx)
अणु
	s64 upper, lower;

	अगर (rvoff && is_21b_पूर्णांक(rvoff) && !क्रमce_jalr) अणु
		emit(rv_jal(rd, rvoff >> 1), ctx);
		वापस 0;
	पूर्ण अन्यथा अगर (in_auipc_jalr_range(rvoff)) अणु
		upper = (rvoff + (1 << 11)) >> 12;
		lower = rvoff & 0xfff;
		emit(rv_auipc(RV_REG_T1, upper), ctx);
		emit(rv_jalr(rd, RV_REG_T1, lower), ctx);
		वापस 0;
	पूर्ण

	pr_err("bpf-jit: target offset 0x%llx is out of range\n", rvoff);
	वापस -दुस्फल;
पूर्ण

अटल bool is_चिन्हित_bpf_cond(u8 cond)
अणु
	वापस cond == BPF_JSGT || cond == BPF_JSLT ||
		cond == BPF_JSGE || cond == BPF_JSLE;
पूर्ण

अटल पूर्णांक emit_call(bool fixed, u64 addr, काष्ठा rv_jit_context *ctx)
अणु
	s64 off = 0;
	u64 ip;
	u8 rd;
	पूर्णांक ret;

	अगर (addr && ctx->insns) अणु
		ip = (u64)(दीर्घ)(ctx->insns + ctx->ninsns);
		off = addr - ip;
	पूर्ण

	ret = emit_jump_and_link(RV_REG_RA, off, !fixed, ctx);
	अगर (ret)
		वापस ret;
	rd = bpf_to_rv_reg(BPF_REG_0, ctx);
	emit_mv(rd, RV_REG_A0, ctx);
	वापस 0;
पूर्ण

पूर्णांक bpf_jit_emit_insn(स्थिर काष्ठा bpf_insn *insn, काष्ठा rv_jit_context *ctx,
		      bool extra_pass)
अणु
	bool is64 = BPF_CLASS(insn->code) == BPF_ALU64 ||
		    BPF_CLASS(insn->code) == BPF_JMP;
	पूर्णांक s, e, rvoff, ret, i = insn - ctx->prog->insnsi;
	काष्ठा bpf_prog_aux *aux = ctx->prog->aux;
	u8 rd = -1, rs = -1, code = insn->code;
	s16 off = insn->off;
	s32 imm = insn->imm;

	init_regs(&rd, &rs, insn, ctx);

	चयन (code) अणु
	/* dst = src */
	हाल BPF_ALU | BPF_MOV | BPF_X:
	हाल BPF_ALU64 | BPF_MOV | BPF_X:
		अगर (imm == 1) अणु
			/* Special mov32 क्रम zext */
			emit_zext_32(rd, ctx);
			अवरोध;
		पूर्ण
		emit_mv(rd, rs, ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;

	/* dst = dst OP src */
	हाल BPF_ALU | BPF_ADD | BPF_X:
	हाल BPF_ALU64 | BPF_ADD | BPF_X:
		emit_add(rd, rd, rs, ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_SUB | BPF_X:
	हाल BPF_ALU64 | BPF_SUB | BPF_X:
		अगर (is64)
			emit_sub(rd, rd, rs, ctx);
		अन्यथा
			emit_subw(rd, rd, rs, ctx);

		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_AND | BPF_X:
	हाल BPF_ALU64 | BPF_AND | BPF_X:
		emit_and(rd, rd, rs, ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_OR | BPF_X:
	हाल BPF_ALU64 | BPF_OR | BPF_X:
		emit_or(rd, rd, rs, ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_XOR | BPF_X:
	हाल BPF_ALU64 | BPF_XOR | BPF_X:
		emit_xor(rd, rd, rs, ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_MUL | BPF_X:
	हाल BPF_ALU64 | BPF_MUL | BPF_X:
		emit(is64 ? rv_mul(rd, rd, rs) : rv_mulw(rd, rd, rs), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_DIV | BPF_X:
	हाल BPF_ALU64 | BPF_DIV | BPF_X:
		emit(is64 ? rv_भागu(rd, rd, rs) : rv_भागuw(rd, rd, rs), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_MOD | BPF_X:
	हाल BPF_ALU64 | BPF_MOD | BPF_X:
		emit(is64 ? rv_remu(rd, rd, rs) : rv_remuw(rd, rd, rs), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_LSH | BPF_X:
	हाल BPF_ALU64 | BPF_LSH | BPF_X:
		emit(is64 ? rv_sll(rd, rd, rs) : rv_sllw(rd, rd, rs), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_RSH | BPF_X:
	हाल BPF_ALU64 | BPF_RSH | BPF_X:
		emit(is64 ? rv_srl(rd, rd, rs) : rv_srlw(rd, rd, rs), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_ARSH | BPF_X:
	हाल BPF_ALU64 | BPF_ARSH | BPF_X:
		emit(is64 ? rv_sra(rd, rd, rs) : rv_sraw(rd, rd, rs), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;

	/* dst = -dst */
	हाल BPF_ALU | BPF_NEG:
	हाल BPF_ALU64 | BPF_NEG:
		emit_sub(rd, RV_REG_ZERO, rd, ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;

	/* dst = BSWAP##imm(dst) */
	हाल BPF_ALU | BPF_END | BPF_FROM_LE:
		चयन (imm) अणु
		हाल 16:
			emit_slli(rd, rd, 48, ctx);
			emit_srli(rd, rd, 48, ctx);
			अवरोध;
		हाल 32:
			अगर (!aux->verअगरier_zext)
				emit_zext_32(rd, ctx);
			अवरोध;
		हाल 64:
			/* Do nothing */
			अवरोध;
		पूर्ण
		अवरोध;

	हाल BPF_ALU | BPF_END | BPF_FROM_BE:
		emit_li(RV_REG_T2, 0, ctx);

		emit_andi(RV_REG_T1, rd, 0xff, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, RV_REG_T1, ctx);
		emit_slli(RV_REG_T2, RV_REG_T2, 8, ctx);
		emit_srli(rd, rd, 8, ctx);
		अगर (imm == 16)
			जाओ out_be;

		emit_andi(RV_REG_T1, rd, 0xff, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, RV_REG_T1, ctx);
		emit_slli(RV_REG_T2, RV_REG_T2, 8, ctx);
		emit_srli(rd, rd, 8, ctx);

		emit_andi(RV_REG_T1, rd, 0xff, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, RV_REG_T1, ctx);
		emit_slli(RV_REG_T2, RV_REG_T2, 8, ctx);
		emit_srli(rd, rd, 8, ctx);
		अगर (imm == 32)
			जाओ out_be;

		emit_andi(RV_REG_T1, rd, 0xff, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, RV_REG_T1, ctx);
		emit_slli(RV_REG_T2, RV_REG_T2, 8, ctx);
		emit_srli(rd, rd, 8, ctx);

		emit_andi(RV_REG_T1, rd, 0xff, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, RV_REG_T1, ctx);
		emit_slli(RV_REG_T2, RV_REG_T2, 8, ctx);
		emit_srli(rd, rd, 8, ctx);

		emit_andi(RV_REG_T1, rd, 0xff, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, RV_REG_T1, ctx);
		emit_slli(RV_REG_T2, RV_REG_T2, 8, ctx);
		emit_srli(rd, rd, 8, ctx);

		emit_andi(RV_REG_T1, rd, 0xff, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, RV_REG_T1, ctx);
		emit_slli(RV_REG_T2, RV_REG_T2, 8, ctx);
		emit_srli(rd, rd, 8, ctx);
out_be:
		emit_andi(RV_REG_T1, rd, 0xff, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, RV_REG_T1, ctx);

		emit_mv(rd, RV_REG_T2, ctx);
		अवरोध;

	/* dst = imm */
	हाल BPF_ALU | BPF_MOV | BPF_K:
	हाल BPF_ALU64 | BPF_MOV | BPF_K:
		emit_imm(rd, imm, ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;

	/* dst = dst OP imm */
	हाल BPF_ALU | BPF_ADD | BPF_K:
	हाल BPF_ALU64 | BPF_ADD | BPF_K:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit_addi(rd, rd, imm, ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T1, imm, ctx);
			emit_add(rd, rd, RV_REG_T1, ctx);
		पूर्ण
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_SUB | BPF_K:
	हाल BPF_ALU64 | BPF_SUB | BPF_K:
		अगर (is_12b_पूर्णांक(-imm)) अणु
			emit_addi(rd, rd, -imm, ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T1, imm, ctx);
			emit_sub(rd, rd, RV_REG_T1, ctx);
		पूर्ण
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_AND | BPF_K:
	हाल BPF_ALU64 | BPF_AND | BPF_K:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit_andi(rd, rd, imm, ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T1, imm, ctx);
			emit_and(rd, rd, RV_REG_T1, ctx);
		पूर्ण
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_OR | BPF_K:
	हाल BPF_ALU64 | BPF_OR | BPF_K:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_ori(rd, rd, imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T1, imm, ctx);
			emit_or(rd, rd, RV_REG_T1, ctx);
		पूर्ण
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_XOR | BPF_K:
	हाल BPF_ALU64 | BPF_XOR | BPF_K:
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit(rv_xori(rd, rd, imm), ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T1, imm, ctx);
			emit_xor(rd, rd, RV_REG_T1, ctx);
		पूर्ण
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_MUL | BPF_K:
	हाल BPF_ALU64 | BPF_MUL | BPF_K:
		emit_imm(RV_REG_T1, imm, ctx);
		emit(is64 ? rv_mul(rd, rd, RV_REG_T1) :
		     rv_mulw(rd, rd, RV_REG_T1), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_DIV | BPF_K:
	हाल BPF_ALU64 | BPF_DIV | BPF_K:
		emit_imm(RV_REG_T1, imm, ctx);
		emit(is64 ? rv_भागu(rd, rd, RV_REG_T1) :
		     rv_भागuw(rd, rd, RV_REG_T1), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_MOD | BPF_K:
	हाल BPF_ALU64 | BPF_MOD | BPF_K:
		emit_imm(RV_REG_T1, imm, ctx);
		emit(is64 ? rv_remu(rd, rd, RV_REG_T1) :
		     rv_remuw(rd, rd, RV_REG_T1), ctx);
		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_LSH | BPF_K:
	हाल BPF_ALU64 | BPF_LSH | BPF_K:
		emit_slli(rd, rd, imm, ctx);

		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_RSH | BPF_K:
	हाल BPF_ALU64 | BPF_RSH | BPF_K:
		अगर (is64)
			emit_srli(rd, rd, imm, ctx);
		अन्यथा
			emit(rv_srliw(rd, rd, imm), ctx);

		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_ARSH | BPF_K:
	हाल BPF_ALU64 | BPF_ARSH | BPF_K:
		अगर (is64)
			emit_srai(rd, rd, imm, ctx);
		अन्यथा
			emit(rv_sraiw(rd, rd, imm), ctx);

		अगर (!is64 && !aux->verअगरier_zext)
			emit_zext_32(rd, ctx);
		अवरोध;

	/* JUMP off */
	हाल BPF_JMP | BPF_JA:
		rvoff = rv_offset(i, off, ctx);
		ret = emit_jump_and_link(RV_REG_ZERO, rvoff, false, ctx);
		अगर (ret)
			वापस ret;
		अवरोध;

	/* IF (dst COND src) JUMP off */
	हाल BPF_JMP | BPF_JEQ | BPF_X:
	हाल BPF_JMP32 | BPF_JEQ | BPF_X:
	हाल BPF_JMP | BPF_JGT | BPF_X:
	हाल BPF_JMP32 | BPF_JGT | BPF_X:
	हाल BPF_JMP | BPF_JLT | BPF_X:
	हाल BPF_JMP32 | BPF_JLT | BPF_X:
	हाल BPF_JMP | BPF_JGE | BPF_X:
	हाल BPF_JMP32 | BPF_JGE | BPF_X:
	हाल BPF_JMP | BPF_JLE | BPF_X:
	हाल BPF_JMP32 | BPF_JLE | BPF_X:
	हाल BPF_JMP | BPF_JNE | BPF_X:
	हाल BPF_JMP32 | BPF_JNE | BPF_X:
	हाल BPF_JMP | BPF_JSGT | BPF_X:
	हाल BPF_JMP32 | BPF_JSGT | BPF_X:
	हाल BPF_JMP | BPF_JSLT | BPF_X:
	हाल BPF_JMP32 | BPF_JSLT | BPF_X:
	हाल BPF_JMP | BPF_JSGE | BPF_X:
	हाल BPF_JMP32 | BPF_JSGE | BPF_X:
	हाल BPF_JMP | BPF_JSLE | BPF_X:
	हाल BPF_JMP32 | BPF_JSLE | BPF_X:
	हाल BPF_JMP | BPF_JSET | BPF_X:
	हाल BPF_JMP32 | BPF_JSET | BPF_X:
		rvoff = rv_offset(i, off, ctx);
		अगर (!is64) अणु
			s = ctx->ninsns;
			अगर (is_चिन्हित_bpf_cond(BPF_OP(code)))
				emit_sext_32_rd_rs(&rd, &rs, ctx);
			अन्यथा
				emit_zext_32_rd_rs(&rd, &rs, ctx);
			e = ctx->ninsns;

			/* Adjust क्रम extra insns */
			rvoff -= ninsns_rvoff(e - s);
		पूर्ण

		अगर (BPF_OP(code) == BPF_JSET) अणु
			/* Adjust क्रम and */
			rvoff -= 4;
			emit_and(RV_REG_T1, rd, rs, ctx);
			emit_branch(BPF_JNE, RV_REG_T1, RV_REG_ZERO, rvoff,
				    ctx);
		पूर्ण अन्यथा अणु
			emit_branch(BPF_OP(code), rd, rs, rvoff, ctx);
		पूर्ण
		अवरोध;

	/* IF (dst COND imm) JUMP off */
	हाल BPF_JMP | BPF_JEQ | BPF_K:
	हाल BPF_JMP32 | BPF_JEQ | BPF_K:
	हाल BPF_JMP | BPF_JGT | BPF_K:
	हाल BPF_JMP32 | BPF_JGT | BPF_K:
	हाल BPF_JMP | BPF_JLT | BPF_K:
	हाल BPF_JMP32 | BPF_JLT | BPF_K:
	हाल BPF_JMP | BPF_JGE | BPF_K:
	हाल BPF_JMP32 | BPF_JGE | BPF_K:
	हाल BPF_JMP | BPF_JLE | BPF_K:
	हाल BPF_JMP32 | BPF_JLE | BPF_K:
	हाल BPF_JMP | BPF_JNE | BPF_K:
	हाल BPF_JMP32 | BPF_JNE | BPF_K:
	हाल BPF_JMP | BPF_JSGT | BPF_K:
	हाल BPF_JMP32 | BPF_JSGT | BPF_K:
	हाल BPF_JMP | BPF_JSLT | BPF_K:
	हाल BPF_JMP32 | BPF_JSLT | BPF_K:
	हाल BPF_JMP | BPF_JSGE | BPF_K:
	हाल BPF_JMP32 | BPF_JSGE | BPF_K:
	हाल BPF_JMP | BPF_JSLE | BPF_K:
	हाल BPF_JMP32 | BPF_JSLE | BPF_K:
		rvoff = rv_offset(i, off, ctx);
		s = ctx->ninsns;
		अगर (imm) अणु
			emit_imm(RV_REG_T1, imm, ctx);
			rs = RV_REG_T1;
		पूर्ण अन्यथा अणु
			/* If imm is 0, simply use zero रेजिस्टर. */
			rs = RV_REG_ZERO;
		पूर्ण
		अगर (!is64) अणु
			अगर (is_चिन्हित_bpf_cond(BPF_OP(code)))
				emit_sext_32_rd(&rd, ctx);
			अन्यथा
				emit_zext_32_rd_t1(&rd, ctx);
		पूर्ण
		e = ctx->ninsns;

		/* Adjust क्रम extra insns */
		rvoff -= ninsns_rvoff(e - s);
		emit_branch(BPF_OP(code), rd, rs, rvoff, ctx);
		अवरोध;

	हाल BPF_JMP | BPF_JSET | BPF_K:
	हाल BPF_JMP32 | BPF_JSET | BPF_K:
		rvoff = rv_offset(i, off, ctx);
		s = ctx->ninsns;
		अगर (is_12b_पूर्णांक(imm)) अणु
			emit_andi(RV_REG_T1, rd, imm, ctx);
		पूर्ण अन्यथा अणु
			emit_imm(RV_REG_T1, imm, ctx);
			emit_and(RV_REG_T1, rd, RV_REG_T1, ctx);
		पूर्ण
		/* For jset32, we should clear the upper 32 bits of t1, but
		 * sign-extension is sufficient here and saves one inकाष्ठाion,
		 * as t1 is used only in comparison against zero.
		 */
		अगर (!is64 && imm < 0)
			emit_addiw(RV_REG_T1, RV_REG_T1, 0, ctx);
		e = ctx->ninsns;
		rvoff -= ninsns_rvoff(e - s);
		emit_branch(BPF_JNE, RV_REG_T1, RV_REG_ZERO, rvoff, ctx);
		अवरोध;

	/* function call */
	हाल BPF_JMP | BPF_CALL:
	अणु
		bool fixed;
		u64 addr;

		mark_call(ctx);
		ret = bpf_jit_get_func_addr(ctx->prog, insn, extra_pass, &addr,
					    &fixed);
		अगर (ret < 0)
			वापस ret;
		ret = emit_call(fixed, addr, ctx);
		अगर (ret)
			वापस ret;
		अवरोध;
	पूर्ण
	/* tail call */
	हाल BPF_JMP | BPF_TAIL_CALL:
		अगर (emit_bpf_tail_call(i, ctx))
			वापस -1;
		अवरोध;

	/* function वापस */
	हाल BPF_JMP | BPF_EXIT:
		अगर (i == ctx->prog->len - 1)
			अवरोध;

		rvoff = epilogue_offset(ctx);
		ret = emit_jump_and_link(RV_REG_ZERO, rvoff, false, ctx);
		अगर (ret)
			वापस ret;
		अवरोध;

	/* dst = imm64 */
	हाल BPF_LD | BPF_IMM | BPF_DW:
	अणु
		काष्ठा bpf_insn insn1 = insn[1];
		u64 imm64;

		imm64 = (u64)insn1.imm << 32 | (u32)imm;
		emit_imm(rd, imm64, ctx);
		वापस 1;
	पूर्ण

	/* LDX: dst = *(size *)(src + off) */
	हाल BPF_LDX | BPF_MEM | BPF_B:
		अगर (is_12b_पूर्णांक(off)) अणु
			emit(rv_lbu(rd, off, rs), ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T1, off, ctx);
		emit_add(RV_REG_T1, RV_REG_T1, rs, ctx);
		emit(rv_lbu(rd, 0, RV_REG_T1), ctx);
		अगर (insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	हाल BPF_LDX | BPF_MEM | BPF_H:
		अगर (is_12b_पूर्णांक(off)) अणु
			emit(rv_lhu(rd, off, rs), ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T1, off, ctx);
		emit_add(RV_REG_T1, RV_REG_T1, rs, ctx);
		emit(rv_lhu(rd, 0, RV_REG_T1), ctx);
		अगर (insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	हाल BPF_LDX | BPF_MEM | BPF_W:
		अगर (is_12b_पूर्णांक(off)) अणु
			emit(rv_lwu(rd, off, rs), ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T1, off, ctx);
		emit_add(RV_REG_T1, RV_REG_T1, rs, ctx);
		emit(rv_lwu(rd, 0, RV_REG_T1), ctx);
		अगर (insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	हाल BPF_LDX | BPF_MEM | BPF_DW:
		अगर (is_12b_पूर्णांक(off)) अणु
			emit_ld(rd, off, rs, ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T1, off, ctx);
		emit_add(RV_REG_T1, RV_REG_T1, rs, ctx);
		emit_ld(rd, 0, RV_REG_T1, ctx);
		अवरोध;

	/* ST: *(size *)(dst + off) = imm */
	हाल BPF_ST | BPF_MEM | BPF_B:
		emit_imm(RV_REG_T1, imm, ctx);
		अगर (is_12b_पूर्णांक(off)) अणु
			emit(rv_sb(rd, off, RV_REG_T1), ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T2, off, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, rd, ctx);
		emit(rv_sb(RV_REG_T2, 0, RV_REG_T1), ctx);
		अवरोध;

	हाल BPF_ST | BPF_MEM | BPF_H:
		emit_imm(RV_REG_T1, imm, ctx);
		अगर (is_12b_पूर्णांक(off)) अणु
			emit(rv_sh(rd, off, RV_REG_T1), ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T2, off, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, rd, ctx);
		emit(rv_sh(RV_REG_T2, 0, RV_REG_T1), ctx);
		अवरोध;
	हाल BPF_ST | BPF_MEM | BPF_W:
		emit_imm(RV_REG_T1, imm, ctx);
		अगर (is_12b_पूर्णांक(off)) अणु
			emit_sw(rd, off, RV_REG_T1, ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T2, off, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, rd, ctx);
		emit_sw(RV_REG_T2, 0, RV_REG_T1, ctx);
		अवरोध;
	हाल BPF_ST | BPF_MEM | BPF_DW:
		emit_imm(RV_REG_T1, imm, ctx);
		अगर (is_12b_पूर्णांक(off)) अणु
			emit_sd(rd, off, RV_REG_T1, ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T2, off, ctx);
		emit_add(RV_REG_T2, RV_REG_T2, rd, ctx);
		emit_sd(RV_REG_T2, 0, RV_REG_T1, ctx);
		अवरोध;

	/* STX: *(size *)(dst + off) = src */
	हाल BPF_STX | BPF_MEM | BPF_B:
		अगर (is_12b_पूर्णांक(off)) अणु
			emit(rv_sb(rd, off, rs), ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T1, off, ctx);
		emit_add(RV_REG_T1, RV_REG_T1, rd, ctx);
		emit(rv_sb(RV_REG_T1, 0, rs), ctx);
		अवरोध;
	हाल BPF_STX | BPF_MEM | BPF_H:
		अगर (is_12b_पूर्णांक(off)) अणु
			emit(rv_sh(rd, off, rs), ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T1, off, ctx);
		emit_add(RV_REG_T1, RV_REG_T1, rd, ctx);
		emit(rv_sh(RV_REG_T1, 0, rs), ctx);
		अवरोध;
	हाल BPF_STX | BPF_MEM | BPF_W:
		अगर (is_12b_पूर्णांक(off)) अणु
			emit_sw(rd, off, rs, ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T1, off, ctx);
		emit_add(RV_REG_T1, RV_REG_T1, rd, ctx);
		emit_sw(RV_REG_T1, 0, rs, ctx);
		अवरोध;
	हाल BPF_STX | BPF_MEM | BPF_DW:
		अगर (is_12b_पूर्णांक(off)) अणु
			emit_sd(rd, off, rs, ctx);
			अवरोध;
		पूर्ण

		emit_imm(RV_REG_T1, off, ctx);
		emit_add(RV_REG_T1, RV_REG_T1, rd, ctx);
		emit_sd(RV_REG_T1, 0, rs, ctx);
		अवरोध;
	हाल BPF_STX | BPF_ATOMIC | BPF_W:
	हाल BPF_STX | BPF_ATOMIC | BPF_DW:
		अगर (insn->imm != BPF_ADD) अणु
			pr_err("bpf-jit: not supported: atomic operation %02x ***\n",
			       insn->imm);
			वापस -EINVAL;
		पूर्ण

		/* atomic_add: lock *(u32 *)(dst + off) += src
		 * atomic_add: lock *(u64 *)(dst + off) += src
		 */

		अगर (off) अणु
			अगर (is_12b_पूर्णांक(off)) अणु
				emit_addi(RV_REG_T1, rd, off, ctx);
			पूर्ण अन्यथा अणु
				emit_imm(RV_REG_T1, off, ctx);
				emit_add(RV_REG_T1, RV_REG_T1, rd, ctx);
			पूर्ण

			rd = RV_REG_T1;
		पूर्ण

		emit(BPF_SIZE(code) == BPF_W ?
		     rv_amoadd_w(RV_REG_ZERO, rs, rd, 0, 0) :
		     rv_amoadd_d(RV_REG_ZERO, rs, rd, 0, 0), ctx);
		अवरोध;
	शेष:
		pr_err("bpf-jit: unknown opcode %02x\n", code);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

व्योम bpf_jit_build_prologue(काष्ठा rv_jit_context *ctx)
अणु
	पूर्णांक stack_adjust = 0, store_offset, bpf_stack_adjust;

	bpf_stack_adjust = round_up(ctx->prog->aux->stack_depth, 16);
	अगर (bpf_stack_adjust)
		mark_fp(ctx);

	अगर (seen_reg(RV_REG_RA, ctx))
		stack_adjust += 8;
	stack_adjust += 8; /* RV_REG_FP */
	अगर (seen_reg(RV_REG_S1, ctx))
		stack_adjust += 8;
	अगर (seen_reg(RV_REG_S2, ctx))
		stack_adjust += 8;
	अगर (seen_reg(RV_REG_S3, ctx))
		stack_adjust += 8;
	अगर (seen_reg(RV_REG_S4, ctx))
		stack_adjust += 8;
	अगर (seen_reg(RV_REG_S5, ctx))
		stack_adjust += 8;
	अगर (seen_reg(RV_REG_S6, ctx))
		stack_adjust += 8;

	stack_adjust = round_up(stack_adjust, 16);
	stack_adjust += bpf_stack_adjust;

	store_offset = stack_adjust - 8;

	/* First inकाष्ठाion is always setting the tail-call-counter
	 * (TCC) रेजिस्टर. This inकाष्ठाion is skipped क्रम tail calls.
	 * Force using a 4-byte (non-compressed) inकाष्ठाion.
	 */
	emit(rv_addi(RV_REG_TCC, RV_REG_ZERO, MAX_TAIL_CALL_CNT), ctx);

	emit_addi(RV_REG_SP, RV_REG_SP, -stack_adjust, ctx);

	अगर (seen_reg(RV_REG_RA, ctx)) अणु
		emit_sd(RV_REG_SP, store_offset, RV_REG_RA, ctx);
		store_offset -= 8;
	पूर्ण
	emit_sd(RV_REG_SP, store_offset, RV_REG_FP, ctx);
	store_offset -= 8;
	अगर (seen_reg(RV_REG_S1, ctx)) अणु
		emit_sd(RV_REG_SP, store_offset, RV_REG_S1, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S2, ctx)) अणु
		emit_sd(RV_REG_SP, store_offset, RV_REG_S2, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S3, ctx)) अणु
		emit_sd(RV_REG_SP, store_offset, RV_REG_S3, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S4, ctx)) अणु
		emit_sd(RV_REG_SP, store_offset, RV_REG_S4, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S5, ctx)) अणु
		emit_sd(RV_REG_SP, store_offset, RV_REG_S5, ctx);
		store_offset -= 8;
	पूर्ण
	अगर (seen_reg(RV_REG_S6, ctx)) अणु
		emit_sd(RV_REG_SP, store_offset, RV_REG_S6, ctx);
		store_offset -= 8;
	पूर्ण

	emit_addi(RV_REG_FP, RV_REG_SP, stack_adjust, ctx);

	अगर (bpf_stack_adjust)
		emit_addi(RV_REG_S5, RV_REG_SP, bpf_stack_adjust, ctx);

	/* Program contains calls and tail calls, so RV_REG_TCC need
	 * to be saved across calls.
	 */
	अगर (seen_tail_call(ctx) && seen_call(ctx))
		emit_mv(RV_REG_TCC_SAVED, RV_REG_TCC, ctx);

	ctx->stack_size = stack_adjust;
पूर्ण

व्योम bpf_jit_build_epilogue(काष्ठा rv_jit_context *ctx)
अणु
	__build_epilogue(false, ctx);
पूर्ण
