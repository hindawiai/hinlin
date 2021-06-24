<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Just-In-Time compiler क्रम eBPF filters on MIPS
 *
 * Copyright (c) 2017 Cavium, Inc.
 *
 * Based on code from:
 *
 * Copyright (c) 2014 Imagination Technologies Ltd.
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 */

#समावेश <linux/bitops.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/slab.h>
#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/isa-rev.h>
#समावेश <यंत्र/uयंत्र.h>

/* Registers used by JIT */
#घोषणा MIPS_R_ZERO	0
#घोषणा MIPS_R_AT	1
#घोषणा MIPS_R_V0	2	/* BPF_R0 */
#घोषणा MIPS_R_V1	3
#घोषणा MIPS_R_A0	4	/* BPF_R1 */
#घोषणा MIPS_R_A1	5	/* BPF_R2 */
#घोषणा MIPS_R_A2	6	/* BPF_R3 */
#घोषणा MIPS_R_A3	7	/* BPF_R4 */
#घोषणा MIPS_R_A4	8	/* BPF_R5 */
#घोषणा MIPS_R_T4	12	/* BPF_AX */
#घोषणा MIPS_R_T5	13
#घोषणा MIPS_R_T6	14
#घोषणा MIPS_R_T7	15
#घोषणा MIPS_R_S0	16	/* BPF_R6 */
#घोषणा MIPS_R_S1	17	/* BPF_R7 */
#घोषणा MIPS_R_S2	18	/* BPF_R8 */
#घोषणा MIPS_R_S3	19	/* BPF_R9 */
#घोषणा MIPS_R_S4	20	/* BPF_TCC */
#घोषणा MIPS_R_S5	21
#घोषणा MIPS_R_S6	22
#घोषणा MIPS_R_S7	23
#घोषणा MIPS_R_T8	24
#घोषणा MIPS_R_T9	25
#घोषणा MIPS_R_SP	29
#घोषणा MIPS_R_RA	31

/* eBPF flags */
#घोषणा EBPF_SAVE_S0	BIT(0)
#घोषणा EBPF_SAVE_S1	BIT(1)
#घोषणा EBPF_SAVE_S2	BIT(2)
#घोषणा EBPF_SAVE_S3	BIT(3)
#घोषणा EBPF_SAVE_S4	BIT(4)
#घोषणा EBPF_SAVE_RA	BIT(5)
#घोषणा EBPF_SEEN_FP	BIT(6)
#घोषणा EBPF_SEEN_TC	BIT(7)
#घोषणा EBPF_TCC_IN_V1	BIT(8)

/*
 * For the mips64 ISA, we need to track the value range or type क्रम
 * each JIT रेजिस्टर.  The BPF machine requires zero extended 32-bit
 * values, but the mips64 ISA requires sign extended 32-bit values.
 * At each poपूर्णांक in the BPF program we track the state of every
 * रेजिस्टर so that we can zero extend or sign extend as the BPF
 * semantics require.
 */
क्रमागत reg_val_type अणु
	/* uninitialized */
	REG_UNKNOWN,
	/* not known to be 32-bit compatible. */
	REG_64BIT,
	/* 32-bit compatible, no truncation needed क्रम 64-bit ops. */
	REG_64BIT_32BIT,
	/* 32-bit compatible, need truncation क्रम 64-bit ops. */
	REG_32BIT,
	/* 32-bit no sign/zero extension needed. */
	REG_32BIT_POS
पूर्ण;

/*
 * high bit of offsets indicates अगर दीर्घ branch conversion करोne at
 * this insn.
 */
#घोषणा OFFSETS_B_CONV	BIT(31)

/**
 * काष्ठा jit_ctx - JIT context
 * @skf:		The sk_filter
 * @stack_size:		eBPF stack size
 * @idx:		Inकाष्ठाion index
 * @flags:		JIT flags
 * @offsets:		Inकाष्ठाion offsets
 * @target:		Memory location क्रम the compiled filter
 * @reg_val_types	Packed क्रमागत reg_val_type क्रम each रेजिस्टर.
 */
काष्ठा jit_ctx अणु
	स्थिर काष्ठा bpf_prog *skf;
	पूर्णांक stack_size;
	u32 idx;
	u32 flags;
	u32 *offsets;
	u32 *target;
	u64 *reg_val_types;
	अचिन्हित पूर्णांक दीर्घ_b_conversion:1;
	अचिन्हित पूर्णांक gen_b_offsets:1;
	अचिन्हित पूर्णांक use_bbit_insns:1;
पूर्ण;

अटल व्योम set_reg_val_type(u64 *rvt, पूर्णांक reg, क्रमागत reg_val_type type)
अणु
	*rvt &= ~(7ull << (reg * 3));
	*rvt |= ((u64)type << (reg * 3));
पूर्ण

अटल क्रमागत reg_val_type get_reg_val_type(स्थिर काष्ठा jit_ctx *ctx,
					  पूर्णांक index, पूर्णांक reg)
अणु
	वापस (ctx->reg_val_types[index] >> (reg * 3)) & 7;
पूर्ण

/* Simply emit the inकाष्ठाion अगर the JIT memory space has been allocated */
#घोषणा emit_instr_दीर्घ(ctx, func64, func32, ...)		\
करो अणु								\
	अगर ((ctx)->target != शून्य) अणु				\
		u32 *p = &(ctx)->target[ctx->idx];		\
		अगर (IS_ENABLED(CONFIG_64BIT))			\
			uयंत्र_i_##func64(&p, ##__VA_ARGS__);	\
		अन्यथा						\
			uयंत्र_i_##func32(&p, ##__VA_ARGS__);	\
	पूर्ण							\
	(ctx)->idx++;						\
पूर्ण जबतक (0)

#घोषणा emit_instr(ctx, func, ...)				\
	emit_instr_दीर्घ(ctx, func, func, ##__VA_ARGS__)

अटल अचिन्हित पूर्णांक j_target(काष्ठा jit_ctx *ctx, पूर्णांक target_idx)
अणु
	अचिन्हित दीर्घ target_va, base_va;
	अचिन्हित पूर्णांक r;

	अगर (!ctx->target)
		वापस 0;

	base_va = (अचिन्हित दीर्घ)ctx->target;
	target_va = base_va + (ctx->offsets[target_idx] & ~OFFSETS_B_CONV);

	अगर ((base_va & ~0x0ffffffful) != (target_va & ~0x0ffffffful))
		वापस (अचिन्हित पूर्णांक)-1;
	r = target_va & 0x0ffffffful;
	वापस r;
पूर्ण

/* Compute the immediate value क्रम PC-relative branches. */
अटल u32 b_imm(अचिन्हित पूर्णांक tgt, काष्ठा jit_ctx *ctx)
अणु
	अगर (!ctx->gen_b_offsets)
		वापस 0;

	/*
	 * We want a pc-relative branch.  tgt is the inकाष्ठाion offset
	 * we want to jump to.

	 * Branch on MIPS:
	 * I: target_offset <- sign_extend(offset)
	 * I+1: PC += target_offset (delay slot)
	 *
	 * ctx->idx currently poपूर्णांकs to the branch inकाष्ठाion
	 * but the offset is added to the delay slot so we need
	 * to subtract 4.
	 */
	वापस (ctx->offsets[tgt] & ~OFFSETS_B_CONV) -
		(ctx->idx * 4) - 4;
पूर्ण

क्रमागत which_ebpf_reg अणु
	src_reg,
	src_reg_no_fp,
	dst_reg,
	dst_reg_fp_ok
पूर्ण;

/*
 * For eBPF, the रेजिस्टर mapping naturally falls out of the
 * requirements of eBPF and the MIPS n64 ABI.  We करोn't मुख्यtain a
 * separate frame poपूर्णांकer, so BPF_REG_10 relative accesses are
 * adjusted to be $sp relative.
 */
अटल पूर्णांक ebpf_to_mips_reg(काष्ठा jit_ctx *ctx,
			    स्थिर काष्ठा bpf_insn *insn,
			    क्रमागत which_ebpf_reg w)
अणु
	पूर्णांक ebpf_reg = (w == src_reg || w == src_reg_no_fp) ?
		insn->src_reg : insn->dst_reg;

	चयन (ebpf_reg) अणु
	हाल BPF_REG_0:
		वापस MIPS_R_V0;
	हाल BPF_REG_1:
		वापस MIPS_R_A0;
	हाल BPF_REG_2:
		वापस MIPS_R_A1;
	हाल BPF_REG_3:
		वापस MIPS_R_A2;
	हाल BPF_REG_4:
		वापस MIPS_R_A3;
	हाल BPF_REG_5:
		वापस MIPS_R_A4;
	हाल BPF_REG_6:
		ctx->flags |= EBPF_SAVE_S0;
		वापस MIPS_R_S0;
	हाल BPF_REG_7:
		ctx->flags |= EBPF_SAVE_S1;
		वापस MIPS_R_S1;
	हाल BPF_REG_8:
		ctx->flags |= EBPF_SAVE_S2;
		वापस MIPS_R_S2;
	हाल BPF_REG_9:
		ctx->flags |= EBPF_SAVE_S3;
		वापस MIPS_R_S3;
	हाल BPF_REG_10:
		अगर (w == dst_reg || w == src_reg_no_fp)
			जाओ bad_reg;
		ctx->flags |= EBPF_SEEN_FP;
		/*
		 * Needs special handling, वापस something that
		 * cannot be clobbered just in हाल.
		 */
		वापस MIPS_R_ZERO;
	हाल BPF_REG_AX:
		वापस MIPS_R_T4;
	शेष:
bad_reg:
		WARN(1, "Illegal bpf reg: %d\n", ebpf_reg);
		वापस -EINVAL;
	पूर्ण
पूर्ण
/*
 * eBPF stack frame will be something like:
 *
 *  Entry $sp ------>   +--------------------------------+
 *                      |   $ra  (optional)              |
 *                      +--------------------------------+
 *                      |   $s0  (optional)              |
 *                      +--------------------------------+
 *                      |   $s1  (optional)              |
 *                      +--------------------------------+
 *                      |   $s2  (optional)              |
 *                      +--------------------------------+
 *                      |   $s3  (optional)              |
 *                      +--------------------------------+
 *                      |   $s4  (optional)              |
 *                      +--------------------------------+
 *                      |   पंचांगp-storage  (अगर $ra saved)  |
 * $sp + पंचांगp_offset --> +--------------------------------+ <--BPF_REG_10
 *                      |   BPF_REG_10 relative storage  |
 *                      |    MAX_BPF_STACK (optional)    |
 *                      |      .                         |
 *                      |      .                         |
 *                      |      .                         |
 *     $sp -------->    +--------------------------------+
 *
 * If BPF_REG_10 is never referenced, then the MAX_BPF_STACK sized
 * area is not allocated.
 */
अटल पूर्णांक gen_पूर्णांक_prologue(काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक stack_adjust = 0;
	पूर्णांक store_offset;
	पूर्णांक locals_size;

	अगर (ctx->flags & EBPF_SAVE_RA)
		/*
		 * If RA we are करोing a function call and may need
		 * extra 8-byte पंचांगp area.
		 */
		stack_adjust += 2 * माप(दीर्घ);
	अगर (ctx->flags & EBPF_SAVE_S0)
		stack_adjust += माप(दीर्घ);
	अगर (ctx->flags & EBPF_SAVE_S1)
		stack_adjust += माप(दीर्घ);
	अगर (ctx->flags & EBPF_SAVE_S2)
		stack_adjust += माप(दीर्घ);
	अगर (ctx->flags & EBPF_SAVE_S3)
		stack_adjust += माप(दीर्घ);
	अगर (ctx->flags & EBPF_SAVE_S4)
		stack_adjust += माप(दीर्घ);

	BUILD_BUG_ON(MAX_BPF_STACK & 7);
	locals_size = (ctx->flags & EBPF_SEEN_FP) ? MAX_BPF_STACK : 0;

	stack_adjust += locals_size;

	ctx->stack_size = stack_adjust;

	/*
	 * First inकाष्ठाion initializes the tail call count (TCC).
	 * On tail call we skip this inकाष्ठाion, and the TCC is
	 * passed in $v1 from the caller.
	 */
	emit_instr(ctx, addiu, MIPS_R_V1, MIPS_R_ZERO, MAX_TAIL_CALL_CNT);
	अगर (stack_adjust)
		emit_instr_दीर्घ(ctx, daddiu, addiu,
					MIPS_R_SP, MIPS_R_SP, -stack_adjust);
	अन्यथा
		वापस 0;

	store_offset = stack_adjust - माप(दीर्घ);

	अगर (ctx->flags & EBPF_SAVE_RA) अणु
		emit_instr_दीर्घ(ctx, sd, sw,
					MIPS_R_RA, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S0) अणु
		emit_instr_दीर्घ(ctx, sd, sw,
					MIPS_R_S0, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S1) अणु
		emit_instr_दीर्घ(ctx, sd, sw,
					MIPS_R_S1, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S2) अणु
		emit_instr_दीर्घ(ctx, sd, sw,
					MIPS_R_S2, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S3) अणु
		emit_instr_दीर्घ(ctx, sd, sw,
					MIPS_R_S3, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S4) अणु
		emit_instr_दीर्घ(ctx, sd, sw,
					MIPS_R_S4, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण

	अगर ((ctx->flags & EBPF_SEEN_TC) && !(ctx->flags & EBPF_TCC_IN_V1))
		emit_instr_दीर्घ(ctx, daddu, addu,
					MIPS_R_S4, MIPS_R_V1, MIPS_R_ZERO);

	वापस 0;
पूर्ण

अटल पूर्णांक build_पूर्णांक_epilogue(काष्ठा jit_ctx *ctx, पूर्णांक dest_reg)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->skf;
	पूर्णांक stack_adjust = ctx->stack_size;
	पूर्णांक store_offset = stack_adjust - माप(दीर्घ);
	क्रमागत reg_val_type td;
	पूर्णांक r0 = MIPS_R_V0;

	अगर (dest_reg == MIPS_R_RA) अणु
		/* Don't let zero extended value escape. */
		td = get_reg_val_type(ctx, prog->len, BPF_REG_0);
		अगर (td == REG_64BIT)
			emit_instr(ctx, sll, r0, r0, 0);
	पूर्ण

	अगर (ctx->flags & EBPF_SAVE_RA) अणु
		emit_instr_दीर्घ(ctx, ld, lw,
					MIPS_R_RA, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S0) अणु
		emit_instr_दीर्घ(ctx, ld, lw,
					MIPS_R_S0, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S1) अणु
		emit_instr_दीर्घ(ctx, ld, lw,
					MIPS_R_S1, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S2) अणु
		emit_instr_दीर्घ(ctx, ld, lw,
				MIPS_R_S2, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S3) अणु
		emit_instr_दीर्घ(ctx, ld, lw,
					MIPS_R_S3, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	अगर (ctx->flags & EBPF_SAVE_S4) अणु
		emit_instr_दीर्घ(ctx, ld, lw,
					MIPS_R_S4, store_offset, MIPS_R_SP);
		store_offset -= माप(दीर्घ);
	पूर्ण
	emit_instr(ctx, jr, dest_reg);

	अगर (stack_adjust)
		emit_instr_दीर्घ(ctx, daddiu, addiu,
					MIPS_R_SP, MIPS_R_SP, stack_adjust);
	अन्यथा
		emit_instr(ctx, nop);

	वापस 0;
पूर्ण

अटल व्योम gen_imm_to_reg(स्थिर काष्ठा bpf_insn *insn, पूर्णांक reg,
			   काष्ठा jit_ctx *ctx)
अणु
	अगर (insn->imm >= S16_MIN && insn->imm <= S16_MAX) अणु
		emit_instr(ctx, addiu, reg, MIPS_R_ZERO, insn->imm);
	पूर्ण अन्यथा अणु
		पूर्णांक lower = (s16)(insn->imm & 0xffff);
		पूर्णांक upper = insn->imm - lower;

		emit_instr(ctx, lui, reg, upper >> 16);
		emit_instr(ctx, addiu, reg, reg, lower);
	पूर्ण
पूर्ण

अटल पूर्णांक gen_imm_insn(स्थिर काष्ठा bpf_insn *insn, काष्ठा jit_ctx *ctx,
			पूर्णांक idx)
अणु
	पूर्णांक upper_bound, lower_bound;
	पूर्णांक dst = ebpf_to_mips_reg(ctx, insn, dst_reg);

	अगर (dst < 0)
		वापस dst;

	चयन (BPF_OP(insn->code)) अणु
	हाल BPF_MOV:
	हाल BPF_ADD:
		upper_bound = S16_MAX;
		lower_bound = S16_MIN;
		अवरोध;
	हाल BPF_SUB:
		upper_bound = -(पूर्णांक)S16_MIN;
		lower_bound = -(पूर्णांक)S16_MAX;
		अवरोध;
	हाल BPF_AND:
	हाल BPF_OR:
	हाल BPF_XOR:
		upper_bound = 0xffff;
		lower_bound = 0;
		अवरोध;
	हाल BPF_RSH:
	हाल BPF_LSH:
	हाल BPF_ARSH:
		/* Shअगरt amounts are truncated, no need क्रम bounds */
		upper_bound = S32_MAX;
		lower_bound = S32_MIN;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	/*
	 * Immediate move clobbers the रेजिस्टर, so no sign/zero
	 * extension needed.
	 */
	अगर (BPF_CLASS(insn->code) == BPF_ALU64 &&
	    BPF_OP(insn->code) != BPF_MOV &&
	    get_reg_val_type(ctx, idx, insn->dst_reg) == REG_32BIT)
		emit_instr(ctx, dinsu, dst, MIPS_R_ZERO, 32, 32);
	/* BPF_ALU | BPF_LSH करोesn't need separate sign extension */
	अगर (BPF_CLASS(insn->code) == BPF_ALU &&
	    BPF_OP(insn->code) != BPF_LSH &&
	    BPF_OP(insn->code) != BPF_MOV &&
	    get_reg_val_type(ctx, idx, insn->dst_reg) != REG_32BIT)
		emit_instr(ctx, sll, dst, dst, 0);

	अगर (insn->imm >= lower_bound && insn->imm <= upper_bound) अणु
		/* single insn immediate हाल */
		चयन (BPF_OP(insn->code) | BPF_CLASS(insn->code)) अणु
		हाल BPF_ALU64 | BPF_MOV:
			emit_instr(ctx, daddiu, dst, MIPS_R_ZERO, insn->imm);
			अवरोध;
		हाल BPF_ALU64 | BPF_AND:
		हाल BPF_ALU | BPF_AND:
			emit_instr(ctx, andi, dst, dst, insn->imm);
			अवरोध;
		हाल BPF_ALU64 | BPF_OR:
		हाल BPF_ALU | BPF_OR:
			emit_instr(ctx, ori, dst, dst, insn->imm);
			अवरोध;
		हाल BPF_ALU64 | BPF_XOR:
		हाल BPF_ALU | BPF_XOR:
			emit_instr(ctx, xori, dst, dst, insn->imm);
			अवरोध;
		हाल BPF_ALU64 | BPF_ADD:
			emit_instr(ctx, daddiu, dst, dst, insn->imm);
			अवरोध;
		हाल BPF_ALU64 | BPF_SUB:
			emit_instr(ctx, daddiu, dst, dst, -insn->imm);
			अवरोध;
		हाल BPF_ALU64 | BPF_RSH:
			emit_instr(ctx, dsrl_safe, dst, dst, insn->imm & 0x3f);
			अवरोध;
		हाल BPF_ALU | BPF_RSH:
			emit_instr(ctx, srl, dst, dst, insn->imm & 0x1f);
			अवरोध;
		हाल BPF_ALU64 | BPF_LSH:
			emit_instr(ctx, dsll_safe, dst, dst, insn->imm & 0x3f);
			अवरोध;
		हाल BPF_ALU | BPF_LSH:
			emit_instr(ctx, sll, dst, dst, insn->imm & 0x1f);
			अवरोध;
		हाल BPF_ALU64 | BPF_ARSH:
			emit_instr(ctx, dsra_safe, dst, dst, insn->imm & 0x3f);
			अवरोध;
		हाल BPF_ALU | BPF_ARSH:
			emit_instr(ctx, sra, dst, dst, insn->imm & 0x1f);
			अवरोध;
		हाल BPF_ALU | BPF_MOV:
			emit_instr(ctx, addiu, dst, MIPS_R_ZERO, insn->imm);
			अवरोध;
		हाल BPF_ALU | BPF_ADD:
			emit_instr(ctx, addiu, dst, dst, insn->imm);
			अवरोध;
		हाल BPF_ALU | BPF_SUB:
			emit_instr(ctx, addiu, dst, dst, -insn->imm);
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* multi insn immediate हाल */
		अगर (BPF_OP(insn->code) == BPF_MOV) अणु
			gen_imm_to_reg(insn, dst, ctx);
		पूर्ण अन्यथा अणु
			gen_imm_to_reg(insn, MIPS_R_AT, ctx);
			चयन (BPF_OP(insn->code) | BPF_CLASS(insn->code)) अणु
			हाल BPF_ALU64 | BPF_AND:
			हाल BPF_ALU | BPF_AND:
				emit_instr(ctx, and, dst, dst, MIPS_R_AT);
				अवरोध;
			हाल BPF_ALU64 | BPF_OR:
			हाल BPF_ALU | BPF_OR:
				emit_instr(ctx, or, dst, dst, MIPS_R_AT);
				अवरोध;
			हाल BPF_ALU64 | BPF_XOR:
			हाल BPF_ALU | BPF_XOR:
				emit_instr(ctx, xor, dst, dst, MIPS_R_AT);
				अवरोध;
			हाल BPF_ALU64 | BPF_ADD:
				emit_instr(ctx, daddu, dst, dst, MIPS_R_AT);
				अवरोध;
			हाल BPF_ALU64 | BPF_SUB:
				emit_instr(ctx, dsubu, dst, dst, MIPS_R_AT);
				अवरोध;
			हाल BPF_ALU | BPF_ADD:
				emit_instr(ctx, addu, dst, dst, MIPS_R_AT);
				अवरोध;
			हाल BPF_ALU | BPF_SUB:
				emit_instr(ctx, subu, dst, dst, MIPS_R_AT);
				अवरोध;
			शेष:
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम emit_स्थिर_to_reg(काष्ठा jit_ctx *ctx, पूर्णांक dst, u64 value)
अणु
	अगर (value >= 0xffffffffffff8000ull || value < 0x8000ull) अणु
		emit_instr(ctx, daddiu, dst, MIPS_R_ZERO, (पूर्णांक)value);
	पूर्ण अन्यथा अगर (value >= 0xffffffff80000000ull ||
		   (value < 0x80000000 && value > 0xffff)) अणु
		emit_instr(ctx, lui, dst, (s32)(s16)(value >> 16));
		emit_instr(ctx, ori, dst, dst, (अचिन्हित पूर्णांक)(value & 0xffff));
	पूर्ण अन्यथा अणु
		पूर्णांक i;
		bool seen_part = false;
		पूर्णांक needed_shअगरt = 0;

		क्रम (i = 0; i < 4; i++) अणु
			u64 part = (value >> (16 * (3 - i))) & 0xffff;

			अगर (seen_part && needed_shअगरt > 0 && (part || i == 3)) अणु
				emit_instr(ctx, dsll_safe, dst, dst, needed_shअगरt);
				needed_shअगरt = 0;
			पूर्ण
			अगर (part) अणु
				अगर (i == 0 || (!seen_part && i < 3 && part < 0x8000)) अणु
					emit_instr(ctx, lui, dst, (s32)(s16)part);
					needed_shअगरt = -16;
				पूर्ण अन्यथा अणु
					emit_instr(ctx, ori, dst,
						   seen_part ? dst : MIPS_R_ZERO,
						   (अचिन्हित पूर्णांक)part);
				पूर्ण
				seen_part = true;
			पूर्ण
			अगर (seen_part)
				needed_shअगरt += 16;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक emit_bpf_tail_call(काष्ठा jit_ctx *ctx, पूर्णांक this_idx)
अणु
	पूर्णांक off, b_off;
	पूर्णांक tcc_reg;

	ctx->flags |= EBPF_SEEN_TC;
	/*
	 * अगर (index >= array->map.max_entries)
	 *     जाओ out;
	 */
	off = दुरत्व(काष्ठा bpf_array, map.max_entries);
	emit_instr(ctx, lwu, MIPS_R_T5, off, MIPS_R_A1);
	emit_instr(ctx, sltu, MIPS_R_AT, MIPS_R_T5, MIPS_R_A2);
	b_off = b_imm(this_idx + 1, ctx);
	emit_instr(ctx, bne, MIPS_R_AT, MIPS_R_ZERO, b_off);
	/*
	 * अगर (TCC-- < 0)
	 *     जाओ out;
	 */
	/* Delay slot */
	tcc_reg = (ctx->flags & EBPF_TCC_IN_V1) ? MIPS_R_V1 : MIPS_R_S4;
	emit_instr(ctx, daddiu, MIPS_R_T5, tcc_reg, -1);
	b_off = b_imm(this_idx + 1, ctx);
	emit_instr(ctx, bltz, tcc_reg, b_off);
	/*
	 * prog = array->ptrs[index];
	 * अगर (prog == शून्य)
	 *     जाओ out;
	 */
	/* Delay slot */
	emit_instr(ctx, dsll, MIPS_R_T8, MIPS_R_A2, 3);
	emit_instr(ctx, daddu, MIPS_R_T8, MIPS_R_T8, MIPS_R_A1);
	off = दुरत्व(काष्ठा bpf_array, ptrs);
	emit_instr(ctx, ld, MIPS_R_AT, off, MIPS_R_T8);
	b_off = b_imm(this_idx + 1, ctx);
	emit_instr(ctx, beq, MIPS_R_AT, MIPS_R_ZERO, b_off);
	/* Delay slot */
	emit_instr(ctx, nop);

	/* जाओ *(prog->bpf_func + 4); */
	off = दुरत्व(काष्ठा bpf_prog, bpf_func);
	emit_instr(ctx, ld, MIPS_R_T9, off, MIPS_R_AT);
	/* All प्रणालीs are go... propagate TCC */
	emit_instr(ctx, daddu, MIPS_R_V1, MIPS_R_T5, MIPS_R_ZERO);
	/* Skip first inकाष्ठाion (TCC initialization) */
	emit_instr(ctx, daddiu, MIPS_R_T9, MIPS_R_T9, 4);
	वापस build_पूर्णांक_epilogue(ctx, MIPS_R_T9);
पूर्ण

अटल bool is_bad_offset(पूर्णांक b_off)
अणु
	वापस b_off > 0x1ffff || b_off < -0x20000;
पूर्ण

/* Returns the number of insn slots consumed. */
अटल पूर्णांक build_one_insn(स्थिर काष्ठा bpf_insn *insn, काष्ठा jit_ctx *ctx,
			  पूर्णांक this_idx, पूर्णांक निकास_idx)
अणु
	पूर्णांक src, dst, r, td, ts, mem_off, b_off;
	bool need_swap, did_move, cmp_eq;
	अचिन्हित पूर्णांक target = 0;
	u64 t64;
	s64 t64s;
	पूर्णांक bpf_op = BPF_OP(insn->code);

	अगर (IS_ENABLED(CONFIG_32BIT) && ((BPF_CLASS(insn->code) == BPF_ALU64)
						|| (bpf_op == BPF_DW)))
		वापस -EINVAL;

	चयन (insn->code) अणु
	हाल BPF_ALU64 | BPF_ADD | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU64 | BPF_SUB | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU64 | BPF_OR | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU64 | BPF_AND | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU64 | BPF_LSH | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU64 | BPF_RSH | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU64 | BPF_XOR | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU64 | BPF_ARSH | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU64 | BPF_MOV | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU | BPF_MOV | BPF_K: /* ALU32_IMM */
	हाल BPF_ALU | BPF_ADD | BPF_K: /* ALU32_IMM */
	हाल BPF_ALU | BPF_SUB | BPF_K: /* ALU32_IMM */
	हाल BPF_ALU | BPF_OR | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU | BPF_AND | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU | BPF_LSH | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU | BPF_RSH | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU | BPF_XOR | BPF_K: /* ALU64_IMM */
	हाल BPF_ALU | BPF_ARSH | BPF_K: /* ALU64_IMM */
		r = gen_imm_insn(insn, ctx, this_idx);
		अगर (r < 0)
			वापस r;
		अवरोध;
	हाल BPF_ALU64 | BPF_MUL | BPF_K: /* ALU64_IMM */
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		अगर (get_reg_val_type(ctx, this_idx, insn->dst_reg) == REG_32BIT)
			emit_instr(ctx, dinsu, dst, MIPS_R_ZERO, 32, 32);
		अगर (insn->imm == 1) /* Mult by 1 is a nop */
			अवरोध;
		gen_imm_to_reg(insn, MIPS_R_AT, ctx);
		अगर (MIPS_ISA_REV >= 6) अणु
			emit_instr(ctx, dmulu, dst, dst, MIPS_R_AT);
		पूर्ण अन्यथा अणु
			emit_instr(ctx, dmultu, MIPS_R_AT, dst);
			emit_instr(ctx, mflo, dst);
		पूर्ण
		अवरोध;
	हाल BPF_ALU64 | BPF_NEG | BPF_K: /* ALU64_IMM */
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		अगर (get_reg_val_type(ctx, this_idx, insn->dst_reg) == REG_32BIT)
			emit_instr(ctx, dinsu, dst, MIPS_R_ZERO, 32, 32);
		emit_instr(ctx, dsubu, dst, MIPS_R_ZERO, dst);
		अवरोध;
	हाल BPF_ALU | BPF_MUL | BPF_K: /* ALU_IMM */
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		td = get_reg_val_type(ctx, this_idx, insn->dst_reg);
		अगर (td == REG_64BIT) अणु
			/* sign extend */
			emit_instr(ctx, sll, dst, dst, 0);
		पूर्ण
		अगर (insn->imm == 1) /* Mult by 1 is a nop */
			अवरोध;
		gen_imm_to_reg(insn, MIPS_R_AT, ctx);
		अगर (MIPS_ISA_REV >= 6) अणु
			emit_instr(ctx, mulu, dst, dst, MIPS_R_AT);
		पूर्ण अन्यथा अणु
			emit_instr(ctx, multu, dst, MIPS_R_AT);
			emit_instr(ctx, mflo, dst);
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_NEG | BPF_K: /* ALU_IMM */
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		td = get_reg_val_type(ctx, this_idx, insn->dst_reg);
		अगर (td == REG_64BIT) अणु
			/* sign extend */
			emit_instr(ctx, sll, dst, dst, 0);
		पूर्ण
		emit_instr(ctx, subu, dst, MIPS_R_ZERO, dst);
		अवरोध;
	हाल BPF_ALU | BPF_DIV | BPF_K: /* ALU_IMM */
	हाल BPF_ALU | BPF_MOD | BPF_K: /* ALU_IMM */
		अगर (insn->imm == 0)
			वापस -EINVAL;
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		td = get_reg_val_type(ctx, this_idx, insn->dst_reg);
		अगर (td == REG_64BIT)
			/* sign extend */
			emit_instr(ctx, sll, dst, dst, 0);
		अगर (insn->imm == 1) अणु
			/* भाग by 1 is a nop, mod by 1 is zero */
			अगर (bpf_op == BPF_MOD)
				emit_instr(ctx, addu, dst, MIPS_R_ZERO, MIPS_R_ZERO);
			अवरोध;
		पूर्ण
		gen_imm_to_reg(insn, MIPS_R_AT, ctx);
		अगर (MIPS_ISA_REV >= 6) अणु
			अगर (bpf_op == BPF_DIV)
				emit_instr(ctx, भागu_r6, dst, dst, MIPS_R_AT);
			अन्यथा
				emit_instr(ctx, modu, dst, dst, MIPS_R_AT);
			अवरोध;
		पूर्ण
		emit_instr(ctx, भागu, dst, MIPS_R_AT);
		अगर (bpf_op == BPF_DIV)
			emit_instr(ctx, mflo, dst);
		अन्यथा
			emit_instr(ctx, mfhi, dst);
		अवरोध;
	हाल BPF_ALU64 | BPF_DIV | BPF_K: /* ALU_IMM */
	हाल BPF_ALU64 | BPF_MOD | BPF_K: /* ALU_IMM */
		अगर (insn->imm == 0)
			वापस -EINVAL;
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		अगर (get_reg_val_type(ctx, this_idx, insn->dst_reg) == REG_32BIT)
			emit_instr(ctx, dinsu, dst, MIPS_R_ZERO, 32, 32);
		अगर (insn->imm == 1) अणु
			/* भाग by 1 is a nop, mod by 1 is zero */
			अगर (bpf_op == BPF_MOD)
				emit_instr(ctx, addu, dst, MIPS_R_ZERO, MIPS_R_ZERO);
			अवरोध;
		पूर्ण
		gen_imm_to_reg(insn, MIPS_R_AT, ctx);
		अगर (MIPS_ISA_REV >= 6) अणु
			अगर (bpf_op == BPF_DIV)
				emit_instr(ctx, dभागu_r6, dst, dst, MIPS_R_AT);
			अन्यथा
				emit_instr(ctx, modu, dst, dst, MIPS_R_AT);
			अवरोध;
		पूर्ण
		emit_instr(ctx, dभागu, dst, MIPS_R_AT);
		अगर (bpf_op == BPF_DIV)
			emit_instr(ctx, mflo, dst);
		अन्यथा
			emit_instr(ctx, mfhi, dst);
		अवरोध;
	हाल BPF_ALU64 | BPF_MOV | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_ADD | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_SUB | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_XOR | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_OR | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_AND | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_MUL | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_DIV | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_MOD | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_LSH | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_RSH | BPF_X: /* ALU64_REG */
	हाल BPF_ALU64 | BPF_ARSH | BPF_X: /* ALU64_REG */
		src = ebpf_to_mips_reg(ctx, insn, src_reg);
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (src < 0 || dst < 0)
			वापस -EINVAL;
		अगर (get_reg_val_type(ctx, this_idx, insn->dst_reg) == REG_32BIT)
			emit_instr(ctx, dinsu, dst, MIPS_R_ZERO, 32, 32);
		did_move = false;
		अगर (insn->src_reg == BPF_REG_10) अणु
			अगर (bpf_op == BPF_MOV) अणु
				emit_instr(ctx, daddiu, dst, MIPS_R_SP, MAX_BPF_STACK);
				did_move = true;
			पूर्ण अन्यथा अणु
				emit_instr(ctx, daddiu, MIPS_R_AT, MIPS_R_SP, MAX_BPF_STACK);
				src = MIPS_R_AT;
			पूर्ण
		पूर्ण अन्यथा अगर (get_reg_val_type(ctx, this_idx, insn->src_reg) == REG_32BIT) अणु
			पूर्णांक पंचांगp_reg = MIPS_R_AT;

			अगर (bpf_op == BPF_MOV) अणु
				पंचांगp_reg = dst;
				did_move = true;
			पूर्ण
			emit_instr(ctx, daddu, पंचांगp_reg, src, MIPS_R_ZERO);
			emit_instr(ctx, dinsu, पंचांगp_reg, MIPS_R_ZERO, 32, 32);
			src = MIPS_R_AT;
		पूर्ण
		चयन (bpf_op) अणु
		हाल BPF_MOV:
			अगर (!did_move)
				emit_instr(ctx, daddu, dst, src, MIPS_R_ZERO);
			अवरोध;
		हाल BPF_ADD:
			emit_instr(ctx, daddu, dst, dst, src);
			अवरोध;
		हाल BPF_SUB:
			emit_instr(ctx, dsubu, dst, dst, src);
			अवरोध;
		हाल BPF_XOR:
			emit_instr(ctx, xor, dst, dst, src);
			अवरोध;
		हाल BPF_OR:
			emit_instr(ctx, or, dst, dst, src);
			अवरोध;
		हाल BPF_AND:
			emit_instr(ctx, and, dst, dst, src);
			अवरोध;
		हाल BPF_MUL:
			अगर (MIPS_ISA_REV >= 6) अणु
				emit_instr(ctx, dmulu, dst, dst, src);
			पूर्ण अन्यथा अणु
				emit_instr(ctx, dmultu, dst, src);
				emit_instr(ctx, mflo, dst);
			पूर्ण
			अवरोध;
		हाल BPF_DIV:
		हाल BPF_MOD:
			अगर (MIPS_ISA_REV >= 6) अणु
				अगर (bpf_op == BPF_DIV)
					emit_instr(ctx, dभागu_r6,
							dst, dst, src);
				अन्यथा
					emit_instr(ctx, modu, dst, dst, src);
				अवरोध;
			पूर्ण
			emit_instr(ctx, dभागu, dst, src);
			अगर (bpf_op == BPF_DIV)
				emit_instr(ctx, mflo, dst);
			अन्यथा
				emit_instr(ctx, mfhi, dst);
			अवरोध;
		हाल BPF_LSH:
			emit_instr(ctx, dsllv, dst, dst, src);
			अवरोध;
		हाल BPF_RSH:
			emit_instr(ctx, dsrlv, dst, dst, src);
			अवरोध;
		हाल BPF_ARSH:
			emit_instr(ctx, dsrav, dst, dst, src);
			अवरोध;
		शेष:
			pr_err("ALU64_REG NOT HANDLED\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_MOV | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_ADD | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_SUB | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_XOR | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_OR | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_AND | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_MUL | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_DIV | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_MOD | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_LSH | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_RSH | BPF_X: /* ALU_REG */
	हाल BPF_ALU | BPF_ARSH | BPF_X: /* ALU_REG */
		src = ebpf_to_mips_reg(ctx, insn, src_reg_no_fp);
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (src < 0 || dst < 0)
			वापस -EINVAL;
		td = get_reg_val_type(ctx, this_idx, insn->dst_reg);
		अगर (td == REG_64BIT) अणु
			/* sign extend */
			emit_instr(ctx, sll, dst, dst, 0);
		पूर्ण
		did_move = false;
		ts = get_reg_val_type(ctx, this_idx, insn->src_reg);
		अगर (ts == REG_64BIT) अणु
			पूर्णांक पंचांगp_reg = MIPS_R_AT;

			अगर (bpf_op == BPF_MOV) अणु
				पंचांगp_reg = dst;
				did_move = true;
			पूर्ण
			/* sign extend */
			emit_instr(ctx, sll, पंचांगp_reg, src, 0);
			src = MIPS_R_AT;
		पूर्ण
		चयन (bpf_op) अणु
		हाल BPF_MOV:
			अगर (!did_move)
				emit_instr(ctx, addu, dst, src, MIPS_R_ZERO);
			अवरोध;
		हाल BPF_ADD:
			emit_instr(ctx, addu, dst, dst, src);
			अवरोध;
		हाल BPF_SUB:
			emit_instr(ctx, subu, dst, dst, src);
			अवरोध;
		हाल BPF_XOR:
			emit_instr(ctx, xor, dst, dst, src);
			अवरोध;
		हाल BPF_OR:
			emit_instr(ctx, or, dst, dst, src);
			अवरोध;
		हाल BPF_AND:
			emit_instr(ctx, and, dst, dst, src);
			अवरोध;
		हाल BPF_MUL:
			emit_instr(ctx, mul, dst, dst, src);
			अवरोध;
		हाल BPF_DIV:
		हाल BPF_MOD:
			अगर (MIPS_ISA_REV >= 6) अणु
				अगर (bpf_op == BPF_DIV)
					emit_instr(ctx, भागu_r6, dst, dst, src);
				अन्यथा
					emit_instr(ctx, modu, dst, dst, src);
				अवरोध;
			पूर्ण
			emit_instr(ctx, भागu, dst, src);
			अगर (bpf_op == BPF_DIV)
				emit_instr(ctx, mflo, dst);
			अन्यथा
				emit_instr(ctx, mfhi, dst);
			अवरोध;
		हाल BPF_LSH:
			emit_instr(ctx, sllv, dst, dst, src);
			अवरोध;
		हाल BPF_RSH:
			emit_instr(ctx, srlv, dst, dst, src);
			अवरोध;
		हाल BPF_ARSH:
			emit_instr(ctx, srav, dst, dst, src);
			अवरोध;
		शेष:
			pr_err("ALU_REG NOT HANDLED\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल BPF_JMP | BPF_EXIT:
		अगर (this_idx + 1 < निकास_idx) अणु
			b_off = b_imm(निकास_idx, ctx);
			अगर (is_bad_offset(b_off))
				वापस -E2BIG;
			emit_instr(ctx, beq, MIPS_R_ZERO, MIPS_R_ZERO, b_off);
			emit_instr(ctx, nop);
		पूर्ण
		अवरोध;
	हाल BPF_JMP | BPF_JEQ | BPF_K: /* JMP_IMM */
	हाल BPF_JMP | BPF_JNE | BPF_K: /* JMP_IMM */
		cmp_eq = (bpf_op == BPF_JEQ);
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg_fp_ok);
		अगर (dst < 0)
			वापस dst;
		अगर (insn->imm == 0) अणु
			src = MIPS_R_ZERO;
		पूर्ण अन्यथा अणु
			gen_imm_to_reg(insn, MIPS_R_AT, ctx);
			src = MIPS_R_AT;
		पूर्ण
		जाओ jeq_common;
	हाल BPF_JMP | BPF_JEQ | BPF_X: /* JMP_REG */
	हाल BPF_JMP | BPF_JNE | BPF_X:
	हाल BPF_JMP | BPF_JSLT | BPF_X:
	हाल BPF_JMP | BPF_JSLE | BPF_X:
	हाल BPF_JMP | BPF_JSGT | BPF_X:
	हाल BPF_JMP | BPF_JSGE | BPF_X:
	हाल BPF_JMP | BPF_JLT | BPF_X:
	हाल BPF_JMP | BPF_JLE | BPF_X:
	हाल BPF_JMP | BPF_JGT | BPF_X:
	हाल BPF_JMP | BPF_JGE | BPF_X:
	हाल BPF_JMP | BPF_JSET | BPF_X:
		src = ebpf_to_mips_reg(ctx, insn, src_reg_no_fp);
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (src < 0 || dst < 0)
			वापस -EINVAL;
		td = get_reg_val_type(ctx, this_idx, insn->dst_reg);
		ts = get_reg_val_type(ctx, this_idx, insn->src_reg);
		अगर (td == REG_32BIT && ts != REG_32BIT) अणु
			emit_instr(ctx, sll, MIPS_R_AT, src, 0);
			src = MIPS_R_AT;
		पूर्ण अन्यथा अगर (ts == REG_32BIT && td != REG_32BIT) अणु
			emit_instr(ctx, sll, MIPS_R_AT, dst, 0);
			dst = MIPS_R_AT;
		पूर्ण
		अगर (bpf_op == BPF_JSET) अणु
			emit_instr(ctx, and, MIPS_R_AT, dst, src);
			cmp_eq = false;
			dst = MIPS_R_AT;
			src = MIPS_R_ZERO;
		पूर्ण अन्यथा अगर (bpf_op == BPF_JSGT || bpf_op == BPF_JSLE) अणु
			emit_instr(ctx, dsubu, MIPS_R_AT, dst, src);
			अगर ((insn + 1)->code == (BPF_JMP | BPF_EXIT) && insn->off == 1) अणु
				b_off = b_imm(निकास_idx, ctx);
				अगर (is_bad_offset(b_off))
					वापस -E2BIG;
				अगर (bpf_op == BPF_JSGT)
					emit_instr(ctx, blez, MIPS_R_AT, b_off);
				अन्यथा
					emit_instr(ctx, bgtz, MIPS_R_AT, b_off);
				emit_instr(ctx, nop);
				वापस 2; /* We consumed the निकास. */
			पूर्ण
			b_off = b_imm(this_idx + insn->off + 1, ctx);
			अगर (is_bad_offset(b_off))
				वापस -E2BIG;
			अगर (bpf_op == BPF_JSGT)
				emit_instr(ctx, bgtz, MIPS_R_AT, b_off);
			अन्यथा
				emit_instr(ctx, blez, MIPS_R_AT, b_off);
			emit_instr(ctx, nop);
			अवरोध;
		पूर्ण अन्यथा अगर (bpf_op == BPF_JSGE || bpf_op == BPF_JSLT) अणु
			emit_instr(ctx, slt, MIPS_R_AT, dst, src);
			cmp_eq = bpf_op == BPF_JSGE;
			dst = MIPS_R_AT;
			src = MIPS_R_ZERO;
		पूर्ण अन्यथा अगर (bpf_op == BPF_JGT || bpf_op == BPF_JLE) अणु
			/* dst or src could be AT */
			emit_instr(ctx, dsubu, MIPS_R_T8, dst, src);
			emit_instr(ctx, sltu, MIPS_R_AT, dst, src);
			/* SP known to be non-zero, movz becomes boolean not */
			अगर (MIPS_ISA_REV >= 6) अणु
				emit_instr(ctx, seleqz, MIPS_R_T9,
						MIPS_R_SP, MIPS_R_T8);
			पूर्ण अन्यथा अणु
				emit_instr(ctx, movz, MIPS_R_T9,
						MIPS_R_SP, MIPS_R_T8);
				emit_instr(ctx, movn, MIPS_R_T9,
						MIPS_R_ZERO, MIPS_R_T8);
			पूर्ण
			emit_instr(ctx, or, MIPS_R_AT, MIPS_R_T9, MIPS_R_AT);
			cmp_eq = bpf_op == BPF_JGT;
			dst = MIPS_R_AT;
			src = MIPS_R_ZERO;
		पूर्ण अन्यथा अगर (bpf_op == BPF_JGE || bpf_op == BPF_JLT) अणु
			emit_instr(ctx, sltu, MIPS_R_AT, dst, src);
			cmp_eq = bpf_op == BPF_JGE;
			dst = MIPS_R_AT;
			src = MIPS_R_ZERO;
		पूर्ण अन्यथा अणु /* JNE/JEQ हाल */
			cmp_eq = (bpf_op == BPF_JEQ);
		पूर्ण
jeq_common:
		/*
		 * If the next insn is EXIT and we are jumping arround
		 * only it, invert the sense of the compare and
		 * conditionally jump to the निकास.  Poor man's branch
		 * chaining.
		 */
		अगर ((insn + 1)->code == (BPF_JMP | BPF_EXIT) && insn->off == 1) अणु
			b_off = b_imm(निकास_idx, ctx);
			अगर (is_bad_offset(b_off)) अणु
				target = j_target(ctx, निकास_idx);
				अगर (target == (अचिन्हित पूर्णांक)-1)
					वापस -E2BIG;
				cmp_eq = !cmp_eq;
				b_off = 4 * 3;
				अगर (!(ctx->offsets[this_idx] & OFFSETS_B_CONV)) अणु
					ctx->offsets[this_idx] |= OFFSETS_B_CONV;
					ctx->दीर्घ_b_conversion = 1;
				पूर्ण
			पूर्ण

			अगर (cmp_eq)
				emit_instr(ctx, bne, dst, src, b_off);
			अन्यथा
				emit_instr(ctx, beq, dst, src, b_off);
			emit_instr(ctx, nop);
			अगर (ctx->offsets[this_idx] & OFFSETS_B_CONV) अणु
				emit_instr(ctx, j, target);
				emit_instr(ctx, nop);
			पूर्ण
			वापस 2; /* We consumed the निकास. */
		पूर्ण
		b_off = b_imm(this_idx + insn->off + 1, ctx);
		अगर (is_bad_offset(b_off)) अणु
			target = j_target(ctx, this_idx + insn->off + 1);
			अगर (target == (अचिन्हित पूर्णांक)-1)
				वापस -E2BIG;
			cmp_eq = !cmp_eq;
			b_off = 4 * 3;
			अगर (!(ctx->offsets[this_idx] & OFFSETS_B_CONV)) अणु
				ctx->offsets[this_idx] |= OFFSETS_B_CONV;
				ctx->दीर्घ_b_conversion = 1;
			पूर्ण
		पूर्ण

		अगर (cmp_eq)
			emit_instr(ctx, beq, dst, src, b_off);
		अन्यथा
			emit_instr(ctx, bne, dst, src, b_off);
		emit_instr(ctx, nop);
		अगर (ctx->offsets[this_idx] & OFFSETS_B_CONV) अणु
			emit_instr(ctx, j, target);
			emit_instr(ctx, nop);
		पूर्ण
		अवरोध;
	हाल BPF_JMP | BPF_JSGT | BPF_K: /* JMP_IMM */
	हाल BPF_JMP | BPF_JSGE | BPF_K: /* JMP_IMM */
	हाल BPF_JMP | BPF_JSLT | BPF_K: /* JMP_IMM */
	हाल BPF_JMP | BPF_JSLE | BPF_K: /* JMP_IMM */
		cmp_eq = (bpf_op == BPF_JSGE);
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg_fp_ok);
		अगर (dst < 0)
			वापस dst;

		अगर (insn->imm == 0) अणु
			अगर ((insn + 1)->code == (BPF_JMP | BPF_EXIT) && insn->off == 1) अणु
				b_off = b_imm(निकास_idx, ctx);
				अगर (is_bad_offset(b_off))
					वापस -E2BIG;
				चयन (bpf_op) अणु
				हाल BPF_JSGT:
					emit_instr(ctx, blez, dst, b_off);
					अवरोध;
				हाल BPF_JSGE:
					emit_instr(ctx, bltz, dst, b_off);
					अवरोध;
				हाल BPF_JSLT:
					emit_instr(ctx, bgez, dst, b_off);
					अवरोध;
				हाल BPF_JSLE:
					emit_instr(ctx, bgtz, dst, b_off);
					अवरोध;
				पूर्ण
				emit_instr(ctx, nop);
				वापस 2; /* We consumed the निकास. */
			पूर्ण
			b_off = b_imm(this_idx + insn->off + 1, ctx);
			अगर (is_bad_offset(b_off))
				वापस -E2BIG;
			चयन (bpf_op) अणु
			हाल BPF_JSGT:
				emit_instr(ctx, bgtz, dst, b_off);
				अवरोध;
			हाल BPF_JSGE:
				emit_instr(ctx, bgez, dst, b_off);
				अवरोध;
			हाल BPF_JSLT:
				emit_instr(ctx, bltz, dst, b_off);
				अवरोध;
			हाल BPF_JSLE:
				emit_instr(ctx, blez, dst, b_off);
				अवरोध;
			पूर्ण
			emit_instr(ctx, nop);
			अवरोध;
		पूर्ण
		/*
		 * only "LT" compare available, so we must use imm + 1
		 * to generate "GT" and imm -1 to generate LE
		 */
		अगर (bpf_op == BPF_JSGT)
			t64s = insn->imm + 1;
		अन्यथा अगर (bpf_op == BPF_JSLE)
			t64s = insn->imm + 1;
		अन्यथा
			t64s = insn->imm;

		cmp_eq = bpf_op == BPF_JSGT || bpf_op == BPF_JSGE;
		अगर (t64s >= S16_MIN && t64s <= S16_MAX) अणु
			emit_instr(ctx, slti, MIPS_R_AT, dst, (पूर्णांक)t64s);
			src = MIPS_R_AT;
			dst = MIPS_R_ZERO;
			जाओ jeq_common;
		पूर्ण
		emit_स्थिर_to_reg(ctx, MIPS_R_AT, (u64)t64s);
		emit_instr(ctx, slt, MIPS_R_AT, dst, MIPS_R_AT);
		src = MIPS_R_AT;
		dst = MIPS_R_ZERO;
		जाओ jeq_common;

	हाल BPF_JMP | BPF_JGT | BPF_K:
	हाल BPF_JMP | BPF_JGE | BPF_K:
	हाल BPF_JMP | BPF_JLT | BPF_K:
	हाल BPF_JMP | BPF_JLE | BPF_K:
		cmp_eq = (bpf_op == BPF_JGE);
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg_fp_ok);
		अगर (dst < 0)
			वापस dst;
		/*
		 * only "LT" compare available, so we must use imm + 1
		 * to generate "GT" and imm -1 to generate LE
		 */
		अगर (bpf_op == BPF_JGT)
			t64s = (u64)(u32)(insn->imm) + 1;
		अन्यथा अगर (bpf_op == BPF_JLE)
			t64s = (u64)(u32)(insn->imm) + 1;
		अन्यथा
			t64s = (u64)(u32)(insn->imm);

		cmp_eq = bpf_op == BPF_JGT || bpf_op == BPF_JGE;

		emit_स्थिर_to_reg(ctx, MIPS_R_AT, (u64)t64s);
		emit_instr(ctx, sltu, MIPS_R_AT, dst, MIPS_R_AT);
		src = MIPS_R_AT;
		dst = MIPS_R_ZERO;
		जाओ jeq_common;

	हाल BPF_JMP | BPF_JSET | BPF_K: /* JMP_IMM */
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg_fp_ok);
		अगर (dst < 0)
			वापस dst;

		अगर (ctx->use_bbit_insns && hweight32((u32)insn->imm) == 1) अणु
			अगर ((insn + 1)->code == (BPF_JMP | BPF_EXIT) && insn->off == 1) अणु
				b_off = b_imm(निकास_idx, ctx);
				अगर (is_bad_offset(b_off))
					वापस -E2BIG;
				emit_instr(ctx, bbit0, dst, ffs((u32)insn->imm) - 1, b_off);
				emit_instr(ctx, nop);
				वापस 2; /* We consumed the निकास. */
			पूर्ण
			b_off = b_imm(this_idx + insn->off + 1, ctx);
			अगर (is_bad_offset(b_off))
				वापस -E2BIG;
			emit_instr(ctx, bbit1, dst, ffs((u32)insn->imm) - 1, b_off);
			emit_instr(ctx, nop);
			अवरोध;
		पूर्ण
		t64 = (u32)insn->imm;
		emit_स्थिर_to_reg(ctx, MIPS_R_AT, t64);
		emit_instr(ctx, and, MIPS_R_AT, dst, MIPS_R_AT);
		src = MIPS_R_AT;
		dst = MIPS_R_ZERO;
		cmp_eq = false;
		जाओ jeq_common;

	हाल BPF_JMP | BPF_JA:
		/*
		 * Prefer relative branch क्रम easier debugging, but
		 * fall back अगर needed.
		 */
		b_off = b_imm(this_idx + insn->off + 1, ctx);
		अगर (is_bad_offset(b_off)) अणु
			target = j_target(ctx, this_idx + insn->off + 1);
			अगर (target == (अचिन्हित पूर्णांक)-1)
				वापस -E2BIG;
			emit_instr(ctx, j, target);
		पूर्ण अन्यथा अणु
			emit_instr(ctx, b, b_off);
		पूर्ण
		emit_instr(ctx, nop);
		अवरोध;
	हाल BPF_LD | BPF_DW | BPF_IMM:
		अगर (insn->src_reg != 0)
			वापस -EINVAL;
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		t64 = ((u64)(u32)insn->imm) | ((u64)(insn + 1)->imm << 32);
		emit_स्थिर_to_reg(ctx, dst, t64);
		वापस 2; /* Double slot insn */

	हाल BPF_JMP | BPF_CALL:
		ctx->flags |= EBPF_SAVE_RA;
		t64s = (s64)insn->imm + (दीर्घ)__bpf_call_base;
		emit_स्थिर_to_reg(ctx, MIPS_R_T9, (u64)t64s);
		emit_instr(ctx, jalr, MIPS_R_RA, MIPS_R_T9);
		/* delay slot */
		emit_instr(ctx, nop);
		अवरोध;

	हाल BPF_JMP | BPF_TAIL_CALL:
		अगर (emit_bpf_tail_call(ctx, this_idx))
			वापस -EINVAL;
		अवरोध;

	हाल BPF_ALU | BPF_END | BPF_FROM_BE:
	हाल BPF_ALU | BPF_END | BPF_FROM_LE:
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		td = get_reg_val_type(ctx, this_idx, insn->dst_reg);
		अगर (insn->imm == 64 && td == REG_32BIT)
			emit_instr(ctx, dinsu, dst, MIPS_R_ZERO, 32, 32);

		अगर (insn->imm != 64 && td == REG_64BIT) अणु
			/* sign extend */
			emit_instr(ctx, sll, dst, dst, 0);
		पूर्ण

#अगर_घोषित __BIG_ENDIAN
		need_swap = (BPF_SRC(insn->code) == BPF_FROM_LE);
#अन्यथा
		need_swap = (BPF_SRC(insn->code) == BPF_FROM_BE);
#पूर्ण_अगर
		अगर (insn->imm == 16) अणु
			अगर (need_swap)
				emit_instr(ctx, wsbh, dst, dst);
			emit_instr(ctx, andi, dst, dst, 0xffff);
		पूर्ण अन्यथा अगर (insn->imm == 32) अणु
			अगर (need_swap) अणु
				emit_instr(ctx, wsbh, dst, dst);
				emit_instr(ctx, rotr, dst, dst, 16);
			पूर्ण
		पूर्ण अन्यथा अणु /* 64-bit*/
			अगर (need_swap) अणु
				emit_instr(ctx, dsbh, dst, dst);
				emit_instr(ctx, dshd, dst, dst);
			पूर्ण
		पूर्ण
		अवरोध;

	हाल BPF_ST | BPF_B | BPF_MEM:
	हाल BPF_ST | BPF_H | BPF_MEM:
	हाल BPF_ST | BPF_W | BPF_MEM:
	हाल BPF_ST | BPF_DW | BPF_MEM:
		अगर (insn->dst_reg == BPF_REG_10) अणु
			ctx->flags |= EBPF_SEEN_FP;
			dst = MIPS_R_SP;
			mem_off = insn->off + MAX_BPF_STACK;
		पूर्ण अन्यथा अणु
			dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
			अगर (dst < 0)
				वापस dst;
			mem_off = insn->off;
		पूर्ण
		gen_imm_to_reg(insn, MIPS_R_AT, ctx);
		चयन (BPF_SIZE(insn->code)) अणु
		हाल BPF_B:
			emit_instr(ctx, sb, MIPS_R_AT, mem_off, dst);
			अवरोध;
		हाल BPF_H:
			emit_instr(ctx, sh, MIPS_R_AT, mem_off, dst);
			अवरोध;
		हाल BPF_W:
			emit_instr(ctx, sw, MIPS_R_AT, mem_off, dst);
			अवरोध;
		हाल BPF_DW:
			emit_instr(ctx, sd, MIPS_R_AT, mem_off, dst);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल BPF_LDX | BPF_B | BPF_MEM:
	हाल BPF_LDX | BPF_H | BPF_MEM:
	हाल BPF_LDX | BPF_W | BPF_MEM:
	हाल BPF_LDX | BPF_DW | BPF_MEM:
		अगर (insn->src_reg == BPF_REG_10) अणु
			ctx->flags |= EBPF_SEEN_FP;
			src = MIPS_R_SP;
			mem_off = insn->off + MAX_BPF_STACK;
		पूर्ण अन्यथा अणु
			src = ebpf_to_mips_reg(ctx, insn, src_reg_no_fp);
			अगर (src < 0)
				वापस src;
			mem_off = insn->off;
		पूर्ण
		dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
		अगर (dst < 0)
			वापस dst;
		चयन (BPF_SIZE(insn->code)) अणु
		हाल BPF_B:
			emit_instr(ctx, lbu, dst, mem_off, src);
			अवरोध;
		हाल BPF_H:
			emit_instr(ctx, lhu, dst, mem_off, src);
			अवरोध;
		हाल BPF_W:
			emit_instr(ctx, lw, dst, mem_off, src);
			अवरोध;
		हाल BPF_DW:
			emit_instr(ctx, ld, dst, mem_off, src);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल BPF_STX | BPF_B | BPF_MEM:
	हाल BPF_STX | BPF_H | BPF_MEM:
	हाल BPF_STX | BPF_W | BPF_MEM:
	हाल BPF_STX | BPF_DW | BPF_MEM:
	हाल BPF_STX | BPF_W | BPF_ATOMIC:
	हाल BPF_STX | BPF_DW | BPF_ATOMIC:
		अगर (insn->dst_reg == BPF_REG_10) अणु
			ctx->flags |= EBPF_SEEN_FP;
			dst = MIPS_R_SP;
			mem_off = insn->off + MAX_BPF_STACK;
		पूर्ण अन्यथा अणु
			dst = ebpf_to_mips_reg(ctx, insn, dst_reg);
			अगर (dst < 0)
				वापस dst;
			mem_off = insn->off;
		पूर्ण
		src = ebpf_to_mips_reg(ctx, insn, src_reg_no_fp);
		अगर (src < 0)
			वापस src;
		अगर (BPF_MODE(insn->code) == BPF_ATOMIC) अणु
			अगर (insn->imm != BPF_ADD) अणु
				pr_err("ATOMIC OP %02x NOT HANDLED\n", insn->imm);
				वापस -EINVAL;
			पूर्ण

			/*
			 * If mem_off करोes not fit within the 9 bit ll/sc
			 * inकाष्ठाion immediate field, use a temp reg.
			 */
			अगर (MIPS_ISA_REV >= 6 &&
			    (mem_off >= BIT(8) || mem_off < -BIT(8))) अणु
				emit_instr(ctx, daddiu, MIPS_R_T6,
						dst, mem_off);
				mem_off = 0;
				dst = MIPS_R_T6;
			पूर्ण
			चयन (BPF_SIZE(insn->code)) अणु
			हाल BPF_W:
				अगर (get_reg_val_type(ctx, this_idx, insn->src_reg) == REG_32BIT) अणु
					emit_instr(ctx, sll, MIPS_R_AT, src, 0);
					src = MIPS_R_AT;
				पूर्ण
				emit_instr(ctx, ll, MIPS_R_T8, mem_off, dst);
				emit_instr(ctx, addu, MIPS_R_T8, MIPS_R_T8, src);
				emit_instr(ctx, sc, MIPS_R_T8, mem_off, dst);
				/*
				 * On failure back up to LL (-4
				 * inकाष्ठाions of 4 bytes each
				 */
				emit_instr(ctx, beq, MIPS_R_T8, MIPS_R_ZERO, -4 * 4);
				emit_instr(ctx, nop);
				अवरोध;
			हाल BPF_DW:
				अगर (get_reg_val_type(ctx, this_idx, insn->src_reg) == REG_32BIT) अणु
					emit_instr(ctx, daddu, MIPS_R_AT, src, MIPS_R_ZERO);
					emit_instr(ctx, dinsu, MIPS_R_AT, MIPS_R_ZERO, 32, 32);
					src = MIPS_R_AT;
				पूर्ण
				emit_instr(ctx, lld, MIPS_R_T8, mem_off, dst);
				emit_instr(ctx, daddu, MIPS_R_T8, MIPS_R_T8, src);
				emit_instr(ctx, scd, MIPS_R_T8, mem_off, dst);
				emit_instr(ctx, beq, MIPS_R_T8, MIPS_R_ZERO, -4 * 4);
				emit_instr(ctx, nop);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु /* BPF_MEM */
			चयन (BPF_SIZE(insn->code)) अणु
			हाल BPF_B:
				emit_instr(ctx, sb, src, mem_off, dst);
				अवरोध;
			हाल BPF_H:
				emit_instr(ctx, sh, src, mem_off, dst);
				अवरोध;
			हाल BPF_W:
				emit_instr(ctx, sw, src, mem_off, dst);
				अवरोध;
			हाल BPF_DW:
				अगर (get_reg_val_type(ctx, this_idx, insn->src_reg) == REG_32BIT) अणु
					emit_instr(ctx, daddu, MIPS_R_AT, src, MIPS_R_ZERO);
					emit_instr(ctx, dinsu, MIPS_R_AT, MIPS_R_ZERO, 32, 32);
					src = MIPS_R_AT;
				पूर्ण
				emit_instr(ctx, sd, src, mem_off, dst);
				अवरोध;
			पूर्ण
		पूर्ण
		अवरोध;

	शेष:
		pr_err("NOT HANDLED %d - (%02x)\n",
		       this_idx, (अचिन्हित पूर्णांक)insn->code);
		वापस -EINVAL;
	पूर्ण
	वापस 1;
पूर्ण

#घोषणा RVT_VISITED_MASK 0xc000000000000000ull
#घोषणा RVT_FALL_THROUGH 0x4000000000000000ull
#घोषणा RVT_BRANCH_TAKEN 0x8000000000000000ull
#घोषणा RVT_DONE (RVT_FALL_THROUGH | RVT_BRANCH_TAKEN)

अटल पूर्णांक build_पूर्णांक_body(काष्ठा jit_ctx *ctx)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->skf;
	स्थिर काष्ठा bpf_insn *insn;
	पूर्णांक i, r;

	क्रम (i = 0; i < prog->len; ) अणु
		insn = prog->insnsi + i;
		अगर ((ctx->reg_val_types[i] & RVT_VISITED_MASK) == 0) अणु
			/* dead inकाष्ठाion, करोn't emit it. */
			i++;
			जारी;
		पूर्ण

		अगर (ctx->target == शून्य)
			ctx->offsets[i] = (ctx->offsets[i] & OFFSETS_B_CONV) | (ctx->idx * 4);

		r = build_one_insn(insn, ctx, i, prog->len);
		अगर (r < 0)
			वापस r;
		i += r;
	पूर्ण
	/* epilogue offset */
	अगर (ctx->target == शून्य)
		ctx->offsets[i] = ctx->idx * 4;

	/*
	 * All निकासs have an offset of the epilogue, some offsets may
	 * not have been set due to banch-around thपढ़ोing, so set
	 * them now.
	 */
	अगर (ctx->target == शून्य)
		क्रम (i = 0; i < prog->len; i++) अणु
			insn = prog->insnsi + i;
			अगर (insn->code == (BPF_JMP | BPF_EXIT))
				ctx->offsets[i] = ctx->idx * 4;
		पूर्ण
	वापस 0;
पूर्ण

/* वापस the last idx processed, or negative क्रम error */
अटल पूर्णांक reg_val_propagate_range(काष्ठा jit_ctx *ctx, u64 initial_rvt,
				   पूर्णांक start_idx, bool follow_taken)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->skf;
	स्थिर काष्ठा bpf_insn *insn;
	u64 निकास_rvt = initial_rvt;
	u64 *rvt = ctx->reg_val_types;
	पूर्णांक idx;
	पूर्णांक reg;

	क्रम (idx = start_idx; idx < prog->len; idx++) अणु
		rvt[idx] = (rvt[idx] & RVT_VISITED_MASK) | निकास_rvt;
		insn = prog->insnsi + idx;
		चयन (BPF_CLASS(insn->code)) अणु
		हाल BPF_ALU:
			चयन (BPF_OP(insn->code)) अणु
			हाल BPF_ADD:
			हाल BPF_SUB:
			हाल BPF_MUL:
			हाल BPF_DIV:
			हाल BPF_OR:
			हाल BPF_AND:
			हाल BPF_LSH:
			हाल BPF_RSH:
			हाल BPF_NEG:
			हाल BPF_MOD:
			हाल BPF_XOR:
				set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT);
				अवरोध;
			हाल BPF_MOV:
				अगर (BPF_SRC(insn->code)) अणु
					set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT);
				पूर्ण अन्यथा अणु
					/* IMM to REG move*/
					अगर (insn->imm >= 0)
						set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT_POS);
					अन्यथा
						set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT);
				पूर्ण
				अवरोध;
			हाल BPF_END:
				अगर (insn->imm == 64)
					set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_64BIT);
				अन्यथा अगर (insn->imm == 32)
					set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT);
				अन्यथा /* insn->imm == 16 */
					set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT_POS);
				अवरोध;
			पूर्ण
			rvt[idx] |= RVT_DONE;
			अवरोध;
		हाल BPF_ALU64:
			चयन (BPF_OP(insn->code)) अणु
			हाल BPF_MOV:
				अगर (BPF_SRC(insn->code)) अणु
					/* REG to REG move*/
					set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_64BIT);
				पूर्ण अन्यथा अणु
					/* IMM to REG move*/
					अगर (insn->imm >= 0)
						set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT_POS);
					अन्यथा
						set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_64BIT_32BIT);
				पूर्ण
				अवरोध;
			शेष:
				set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_64BIT);
			पूर्ण
			rvt[idx] |= RVT_DONE;
			अवरोध;
		हाल BPF_LD:
			चयन (BPF_SIZE(insn->code)) अणु
			हाल BPF_DW:
				अगर (BPF_MODE(insn->code) == BPF_IMM) अणु
					s64 val;

					val = (s64)((u32)insn->imm | ((u64)(insn + 1)->imm << 32));
					अगर (val > 0 && val <= S32_MAX)
						set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT_POS);
					अन्यथा अगर (val >= S32_MIN && val <= S32_MAX)
						set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_64BIT_32BIT);
					अन्यथा
						set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_64BIT);
					rvt[idx] |= RVT_DONE;
					idx++;
				पूर्ण अन्यथा अणु
					set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_64BIT);
				पूर्ण
				अवरोध;
			हाल BPF_B:
			हाल BPF_H:
				set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT_POS);
				अवरोध;
			हाल BPF_W:
				अगर (BPF_MODE(insn->code) == BPF_IMM)
					set_reg_val_type(&निकास_rvt, insn->dst_reg,
							 insn->imm >= 0 ? REG_32BIT_POS : REG_32BIT);
				अन्यथा
					set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT);
				अवरोध;
			पूर्ण
			rvt[idx] |= RVT_DONE;
			अवरोध;
		हाल BPF_LDX:
			चयन (BPF_SIZE(insn->code)) अणु
			हाल BPF_DW:
				set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_64BIT);
				अवरोध;
			हाल BPF_B:
			हाल BPF_H:
				set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT_POS);
				अवरोध;
			हाल BPF_W:
				set_reg_val_type(&निकास_rvt, insn->dst_reg, REG_32BIT);
				अवरोध;
			पूर्ण
			rvt[idx] |= RVT_DONE;
			अवरोध;
		हाल BPF_JMP:
			चयन (BPF_OP(insn->code)) अणु
			हाल BPF_EXIT:
				rvt[idx] = RVT_DONE | निकास_rvt;
				rvt[prog->len] = निकास_rvt;
				वापस idx;
			हाल BPF_JA:
				rvt[idx] |= RVT_DONE;
				idx += insn->off;
				अवरोध;
			हाल BPF_JEQ:
			हाल BPF_JGT:
			हाल BPF_JGE:
			हाल BPF_JLT:
			हाल BPF_JLE:
			हाल BPF_JSET:
			हाल BPF_JNE:
			हाल BPF_JSGT:
			हाल BPF_JSGE:
			हाल BPF_JSLT:
			हाल BPF_JSLE:
				अगर (follow_taken) अणु
					rvt[idx] |= RVT_BRANCH_TAKEN;
					idx += insn->off;
					follow_taken = false;
				पूर्ण अन्यथा अणु
					rvt[idx] |= RVT_FALL_THROUGH;
				पूर्ण
				अवरोध;
			हाल BPF_CALL:
				set_reg_val_type(&निकास_rvt, BPF_REG_0, REG_64BIT);
				/* Upon call वापस, argument रेजिस्टरs are clobbered. */
				क्रम (reg = BPF_REG_0; reg <= BPF_REG_5; reg++)
					set_reg_val_type(&निकास_rvt, reg, REG_64BIT);

				rvt[idx] |= RVT_DONE;
				अवरोध;
			शेष:
				WARN(1, "Unhandled BPF_JMP case.\n");
				rvt[idx] |= RVT_DONE;
				अवरोध;
			पूर्ण
			अवरोध;
		शेष:
			rvt[idx] |= RVT_DONE;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस idx;
पूर्ण

/*
 * Track the value range (i.e. 32-bit vs. 64-bit) of each रेजिस्टर at
 * each eBPF insn.  This allows unneeded sign and zero extension
 * operations to be omitted.
 *
 * Doesn't handle yet confluence of control paths with conflicting
 * ranges, but it is good enough क्रम most sane code.
 */
अटल पूर्णांक reg_val_propagate(काष्ठा jit_ctx *ctx)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->skf;
	u64 निकास_rvt;
	पूर्णांक reg;
	पूर्णांक i;

	/*
	 * 11 रेजिस्टरs * 3 bits/reg leaves top bits मुक्त क्रम other
	 * uses.  Bit-62..63 used to see अगर we have visited an insn.
	 */
	निकास_rvt = 0;

	/* Upon entry, argument रेजिस्टरs are 64-bit. */
	क्रम (reg = BPF_REG_1; reg <= BPF_REG_5; reg++)
		set_reg_val_type(&निकास_rvt, reg, REG_64BIT);

	/*
	 * First follow all conditional branches on the fall-through
	 * edge of control flow..
	 */
	reg_val_propagate_range(ctx, निकास_rvt, 0, false);
restart_search:
	/*
	 * Then repeatedly find the first conditional branch where
	 * both edges of control flow have not been taken, and follow
	 * the branch taken edge.  We will end up restarting the
	 * search once per conditional branch insn.
	 */
	क्रम (i = 0; i < prog->len; i++) अणु
		u64 rvt = ctx->reg_val_types[i];

		अगर ((rvt & RVT_VISITED_MASK) == RVT_DONE ||
		    (rvt & RVT_VISITED_MASK) == 0)
			जारी;
		अगर ((rvt & RVT_VISITED_MASK) == RVT_FALL_THROUGH) अणु
			reg_val_propagate_range(ctx, rvt & ~RVT_VISITED_MASK, i, true);
		पूर्ण अन्यथा अणु /* RVT_BRANCH_TAKEN */
			WARN(1, "Unexpected RVT_BRANCH_TAKEN case.\n");
			reg_val_propagate_range(ctx, rvt & ~RVT_VISITED_MASK, i, false);
		पूर्ण
		जाओ restart_search;
	पूर्ण
	/*
	 * Eventually all conditional branches have been followed on
	 * both branches and we are करोne.  Any insn that has not been
	 * visited at this poपूर्णांक is dead.
	 */

	वापस 0;
पूर्ण

अटल व्योम jit_fill_hole(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	u32 *p;

	/* We are guaranteed to have aligned memory. */
	क्रम (p = area; size >= माप(u32); size -= माप(u32))
		uयंत्र_i_अवरोध(&p, BRK_BUG); /* Increments p */
पूर्ण

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *orig_prog = prog;
	bool पंचांगp_blinded = false;
	काष्ठा bpf_prog *पंचांगp;
	काष्ठा bpf_binary_header *header = शून्य;
	काष्ठा jit_ctx ctx;
	अचिन्हित पूर्णांक image_size;
	u8 *image_ptr;

	अगर (!prog->jit_requested)
		वापस prog;

	पंचांगp = bpf_jit_blind_स्थिरants(prog);
	/* If blinding was requested and we failed during blinding,
	 * we must fall back to the पूर्णांकerpreter.
	 */
	अगर (IS_ERR(पंचांगp))
		वापस orig_prog;
	अगर (पंचांगp != prog) अणु
		पंचांगp_blinded = true;
		prog = पंचांगp;
	पूर्ण

	स_रखो(&ctx, 0, माप(ctx));

	preempt_disable();
	चयन (current_cpu_type()) अणु
	हाल CPU_CAVIUM_OCTEON:
	हाल CPU_CAVIUM_OCTEON_PLUS:
	हाल CPU_CAVIUM_OCTEON2:
	हाल CPU_CAVIUM_OCTEON3:
		ctx.use_bbit_insns = 1;
		अवरोध;
	शेष:
		ctx.use_bbit_insns = 0;
	पूर्ण
	preempt_enable();

	ctx.offsets = kसुस्मृति(prog->len + 1, माप(*ctx.offsets), GFP_KERNEL);
	अगर (ctx.offsets == शून्य)
		जाओ out_err;

	ctx.reg_val_types = kसुस्मृति(prog->len + 1, माप(*ctx.reg_val_types), GFP_KERNEL);
	अगर (ctx.reg_val_types == शून्य)
		जाओ out_err;

	ctx.skf = prog;

	अगर (reg_val_propagate(&ctx))
		जाओ out_err;

	/*
	 * First pass discovers used resources and inकाष्ठाion offsets
	 * assuming लघु branches are used.
	 */
	अगर (build_पूर्णांक_body(&ctx))
		जाओ out_err;

	/*
	 * If no calls are made (EBPF_SAVE_RA), then tail call count
	 * in $v1, अन्यथा we must save in n$s4.
	 */
	अगर (ctx.flags & EBPF_SEEN_TC) अणु
		अगर (ctx.flags & EBPF_SAVE_RA)
			ctx.flags |= EBPF_SAVE_S4;
		अन्यथा
			ctx.flags |= EBPF_TCC_IN_V1;
	पूर्ण

	/*
	 * Second pass generates offsets, अगर any branches are out of
	 * range a jump-around दीर्घ sequence is generated, and we have
	 * to try again from the beginning to generate the new
	 * offsets.  This is करोne until no additional conversions are
	 * necessary.
	 */
	करो अणु
		ctx.idx = 0;
		ctx.gen_b_offsets = 1;
		ctx.दीर्घ_b_conversion = 0;
		अगर (gen_पूर्णांक_prologue(&ctx))
			जाओ out_err;
		अगर (build_पूर्णांक_body(&ctx))
			जाओ out_err;
		अगर (build_पूर्णांक_epilogue(&ctx, MIPS_R_RA))
			जाओ out_err;
	पूर्ण जबतक (ctx.दीर्घ_b_conversion);

	image_size = 4 * ctx.idx;

	header = bpf_jit_binary_alloc(image_size, &image_ptr,
				      माप(u32), jit_fill_hole);
	अगर (header == शून्य)
		जाओ out_err;

	ctx.target = (u32 *)image_ptr;

	/* Third pass generates the code */
	ctx.idx = 0;
	अगर (gen_पूर्णांक_prologue(&ctx))
		जाओ out_err;
	अगर (build_पूर्णांक_body(&ctx))
		जाओ out_err;
	अगर (build_पूर्णांक_epilogue(&ctx, MIPS_R_RA))
		जाओ out_err;

	/* Update the icache */
	flush_icache_range((अचिन्हित दीर्घ)ctx.target,
			   (अचिन्हित दीर्घ)&ctx.target[ctx.idx]);

	अगर (bpf_jit_enable > 1)
		/* Dump JIT code */
		bpf_jit_dump(prog->len, image_size, 2, ctx.target);

	bpf_jit_binary_lock_ro(header);
	prog->bpf_func = (व्योम *)ctx.target;
	prog->jited = 1;
	prog->jited_len = image_size;
out_normal:
	अगर (पंचांगp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   पंचांगp : orig_prog);
	kमुक्त(ctx.offsets);
	kमुक्त(ctx.reg_val_types);

	वापस prog;

out_err:
	prog = orig_prog;
	अगर (header)
		bpf_jit_binary_मुक्त(header);
	जाओ out_normal;
पूर्ण
