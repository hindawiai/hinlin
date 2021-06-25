<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * BPF JIT compiler क्रम ARM64
 *
 * Copyright (C) 2014-2016 Zi Shen Lim <zlim.lnx@gmail.com>
 */

#घोषणा pr_fmt(fmt) "bpf_jit: " fmt

#समावेश <linux/bitfield.h>
#समावेश <linux/bpf.h>
#समावेश <linux/filter.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/slab.h>

#समावेश <यंत्र/byteorder.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/debug-monitors.h>
#समावेश <यंत्र/set_memory.h>

#समावेश "bpf_jit.h"

#घोषणा TMP_REG_1 (MAX_BPF_JIT_REG + 0)
#घोषणा TMP_REG_2 (MAX_BPF_JIT_REG + 1)
#घोषणा TCALL_CNT (MAX_BPF_JIT_REG + 2)
#घोषणा TMP_REG_3 (MAX_BPF_JIT_REG + 3)

/* Map BPF रेजिस्टरs to A64 रेजिस्टरs */
अटल स्थिर पूर्णांक bpf2a64[] = अणु
	/* वापस value from in-kernel function, and निकास value from eBPF */
	[BPF_REG_0] = A64_R(7),
	/* arguments from eBPF program to in-kernel function */
	[BPF_REG_1] = A64_R(0),
	[BPF_REG_2] = A64_R(1),
	[BPF_REG_3] = A64_R(2),
	[BPF_REG_4] = A64_R(3),
	[BPF_REG_5] = A64_R(4),
	/* callee saved रेजिस्टरs that in-kernel function will preserve */
	[BPF_REG_6] = A64_R(19),
	[BPF_REG_7] = A64_R(20),
	[BPF_REG_8] = A64_R(21),
	[BPF_REG_9] = A64_R(22),
	/* पढ़ो-only frame poपूर्णांकer to access stack */
	[BPF_REG_FP] = A64_R(25),
	/* temporary रेजिस्टरs क्रम पूर्णांकernal BPF JIT */
	[TMP_REG_1] = A64_R(10),
	[TMP_REG_2] = A64_R(11),
	[TMP_REG_3] = A64_R(12),
	/* tail_call_cnt */
	[TCALL_CNT] = A64_R(26),
	/* temporary रेजिस्टर क्रम blinding स्थिरants */
	[BPF_REG_AX] = A64_R(9),
पूर्ण;

काष्ठा jit_ctx अणु
	स्थिर काष्ठा bpf_prog *prog;
	पूर्णांक idx;
	पूर्णांक epilogue_offset;
	पूर्णांक *offset;
	पूर्णांक exentry_idx;
	__le32 *image;
	u32 stack_size;
पूर्ण;

अटल अंतरभूत व्योम emit(स्थिर u32 insn, काष्ठा jit_ctx *ctx)
अणु
	अगर (ctx->image != शून्य)
		ctx->image[ctx->idx] = cpu_to_le32(insn);

	ctx->idx++;
पूर्ण

अटल अंतरभूत व्योम emit_a64_mov_i(स्थिर पूर्णांक is64, स्थिर पूर्णांक reg,
				  स्थिर s32 val, काष्ठा jit_ctx *ctx)
अणु
	u16 hi = val >> 16;
	u16 lo = val & 0xffff;

	अगर (hi & 0x8000) अणु
		अगर (hi == 0xffff) अणु
			emit(A64_MOVN(is64, reg, (u16)~lo, 0), ctx);
		पूर्ण अन्यथा अणु
			emit(A64_MOVN(is64, reg, (u16)~hi, 16), ctx);
			अगर (lo != 0xffff)
				emit(A64_MOVK(is64, reg, lo, 0), ctx);
		पूर्ण
	पूर्ण अन्यथा अणु
		emit(A64_MOVZ(is64, reg, lo, 0), ctx);
		अगर (hi)
			emit(A64_MOVK(is64, reg, hi, 16), ctx);
	पूर्ण
पूर्ण

अटल पूर्णांक i64_i16_blocks(स्थिर u64 val, bool inverse)
अणु
	वापस (((val >>  0) & 0xffff) != (inverse ? 0xffff : 0x0000)) +
	       (((val >> 16) & 0xffff) != (inverse ? 0xffff : 0x0000)) +
	       (((val >> 32) & 0xffff) != (inverse ? 0xffff : 0x0000)) +
	       (((val >> 48) & 0xffff) != (inverse ? 0xffff : 0x0000));
पूर्ण

अटल अंतरभूत व्योम emit_a64_mov_i64(स्थिर पूर्णांक reg, स्थिर u64 val,
				    काष्ठा jit_ctx *ctx)
अणु
	u64 nrm_पंचांगp = val, rev_पंचांगp = ~val;
	bool inverse;
	पूर्णांक shअगरt;

	अगर (!(nrm_पंचांगp >> 32))
		वापस emit_a64_mov_i(0, reg, (u32)val, ctx);

	inverse = i64_i16_blocks(nrm_पंचांगp, true) < i64_i16_blocks(nrm_पंचांगp, false);
	shअगरt = max(round_करोwn((inverse ? (fls64(rev_पंचांगp) - 1) :
					  (fls64(nrm_पंचांगp) - 1)), 16), 0);
	अगर (inverse)
		emit(A64_MOVN(1, reg, (rev_पंचांगp >> shअगरt) & 0xffff, shअगरt), ctx);
	अन्यथा
		emit(A64_MOVZ(1, reg, (nrm_पंचांगp >> shअगरt) & 0xffff, shअगरt), ctx);
	shअगरt -= 16;
	जबतक (shअगरt >= 0) अणु
		अगर (((nrm_पंचांगp >> shअगरt) & 0xffff) != (inverse ? 0xffff : 0x0000))
			emit(A64_MOVK(1, reg, (nrm_पंचांगp >> shअगरt) & 0xffff, shअगरt), ctx);
		shअगरt -= 16;
	पूर्ण
पूर्ण

/*
 * Kernel addresses in the vदो_स्मृति space use at most 48 bits, and the
 * reमुख्यing bits are guaranteed to be 0x1. So we can compose the address
 * with a fixed length movn/movk/movk sequence.
 */
अटल अंतरभूत व्योम emit_addr_mov_i64(स्थिर पूर्णांक reg, स्थिर u64 val,
				     काष्ठा jit_ctx *ctx)
अणु
	u64 पंचांगp = val;
	पूर्णांक shअगरt = 0;

	emit(A64_MOVN(1, reg, ~पंचांगp & 0xffff, shअगरt), ctx);
	जबतक (shअगरt < 32) अणु
		पंचांगp >>= 16;
		shअगरt += 16;
		emit(A64_MOVK(1, reg, पंचांगp & 0xffff, shअगरt), ctx);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक bpf2a64_offset(पूर्णांक bpf_insn, पूर्णांक off,
				 स्थिर काष्ठा jit_ctx *ctx)
अणु
	/* BPF JMP offset is relative to the next inकाष्ठाion */
	bpf_insn++;
	/*
	 * Whereas arm64 branch inकाष्ठाions encode the offset
	 * from the branch itself, so we must subtract 1 from the
	 * inकाष्ठाion offset.
	 */
	वापस ctx->offset[bpf_insn + off] - (ctx->offset[bpf_insn] - 1);
पूर्ण

अटल व्योम jit_fill_hole(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	__le32 *ptr;
	/* We are guaranteed to have aligned memory. */
	क्रम (ptr = area; size >= माप(u32); size -= माप(u32))
		*ptr++ = cpu_to_le32(AARCH64_BREAK_FAULT);
पूर्ण

अटल अंतरभूत पूर्णांक epilogue_offset(स्थिर काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक to = ctx->epilogue_offset;
	पूर्णांक from = ctx->idx;

	वापस to - from;
पूर्ण

अटल bool is_addsub_imm(u32 imm)
अणु
	/* Either imm12 or shअगरted imm12. */
	वापस !(imm & ~0xfff) || !(imm & ~0xfff000);
पूर्ण

/* Stack must be multiples of 16B */
#घोषणा STACK_ALIGN(sz) (((sz) + 15) & ~15)

/* Tail call offset to jump पूर्णांकo */
#अगर IS_ENABLED(CONFIG_ARM64_BTI_KERNEL)
#घोषणा PROLOGUE_OFFSET 8
#अन्यथा
#घोषणा PROLOGUE_OFFSET 7
#पूर्ण_अगर

अटल पूर्णांक build_prologue(काष्ठा jit_ctx *ctx, bool ebpf_from_cbpf)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->prog;
	स्थिर u8 r6 = bpf2a64[BPF_REG_6];
	स्थिर u8 r7 = bpf2a64[BPF_REG_7];
	स्थिर u8 r8 = bpf2a64[BPF_REG_8];
	स्थिर u8 r9 = bpf2a64[BPF_REG_9];
	स्थिर u8 fp = bpf2a64[BPF_REG_FP];
	स्थिर u8 tcc = bpf2a64[TCALL_CNT];
	स्थिर पूर्णांक idx0 = ctx->idx;
	पूर्णांक cur_offset;

	/*
	 * BPF prog stack layout
	 *
	 *                         high
	 * original A64_SP =>   0:+-----+ BPF prologue
	 *                        |FP/LR|
	 * current A64_FP =>  -16:+-----+
	 *                        | ... | callee saved रेजिस्टरs
	 * BPF fp रेजिस्टर => -64:+-----+ <= (BPF_FP)
	 *                        |     |
	 *                        | ... | BPF prog stack
	 *                        |     |
	 *                        +-----+ <= (BPF_FP - prog->aux->stack_depth)
	 *                        |RSVD | padding
	 * current A64_SP =>      +-----+ <= (BPF_FP - ctx->stack_size)
	 *                        |     |
	 *                        | ... | Function call stack
	 *                        |     |
	 *                        +-----+
	 *                          low
	 *
	 */

	/* BTI landing pad */
	अगर (IS_ENABLED(CONFIG_ARM64_BTI_KERNEL))
		emit(A64_BTI_C, ctx);

	/* Save FP and LR रेजिस्टरs to stay align with ARM64 AAPCS */
	emit(A64_PUSH(A64_FP, A64_LR, A64_SP), ctx);
	emit(A64_MOV(1, A64_FP, A64_SP), ctx);

	/* Save callee-saved रेजिस्टरs */
	emit(A64_PUSH(r6, r7, A64_SP), ctx);
	emit(A64_PUSH(r8, r9, A64_SP), ctx);
	emit(A64_PUSH(fp, tcc, A64_SP), ctx);

	/* Set up BPF prog stack base रेजिस्टर */
	emit(A64_MOV(1, fp, A64_SP), ctx);

	अगर (!ebpf_from_cbpf) अणु
		/* Initialize tail_call_cnt */
		emit(A64_MOVZ(1, tcc, 0, 0), ctx);

		cur_offset = ctx->idx - idx0;
		अगर (cur_offset != PROLOGUE_OFFSET) अणु
			pr_err_once("PROLOGUE_OFFSET = %d, expected %d!\n",
				    cur_offset, PROLOGUE_OFFSET);
			वापस -1;
		पूर्ण

		/* BTI landing pad क्रम the tail call, करोne with a BR */
		अगर (IS_ENABLED(CONFIG_ARM64_BTI_KERNEL))
			emit(A64_BTI_J, ctx);
	पूर्ण

	ctx->stack_size = STACK_ALIGN(prog->aux->stack_depth);

	/* Set up function call stack */
	emit(A64_SUB_I(1, A64_SP, A64_SP, ctx->stack_size), ctx);
	वापस 0;
पूर्ण

अटल पूर्णांक out_offset = -1; /* initialized on the first pass of build_body() */
अटल पूर्णांक emit_bpf_tail_call(काष्ठा jit_ctx *ctx)
अणु
	/* bpf_tail_call(व्योम *prog_ctx, काष्ठा bpf_array *array, u64 index) */
	स्थिर u8 r2 = bpf2a64[BPF_REG_2];
	स्थिर u8 r3 = bpf2a64[BPF_REG_3];

	स्थिर u8 पंचांगp = bpf2a64[TMP_REG_1];
	स्थिर u8 prg = bpf2a64[TMP_REG_2];
	स्थिर u8 tcc = bpf2a64[TCALL_CNT];
	स्थिर पूर्णांक idx0 = ctx->idx;
#घोषणा cur_offset (ctx->idx - idx0)
#घोषणा jmp_offset (out_offset - (cur_offset))
	माप_प्रकार off;

	/* अगर (index >= array->map.max_entries)
	 *     जाओ out;
	 */
	off = दुरत्व(काष्ठा bpf_array, map.max_entries);
	emit_a64_mov_i64(पंचांगp, off, ctx);
	emit(A64_LDR32(पंचांगp, r2, पंचांगp), ctx);
	emit(A64_MOV(0, r3, r3), ctx);
	emit(A64_CMP(0, r3, पंचांगp), ctx);
	emit(A64_B_(A64_COND_CS, jmp_offset), ctx);

	/* अगर (tail_call_cnt > MAX_TAIL_CALL_CNT)
	 *     जाओ out;
	 * tail_call_cnt++;
	 */
	emit_a64_mov_i64(पंचांगp, MAX_TAIL_CALL_CNT, ctx);
	emit(A64_CMP(1, tcc, पंचांगp), ctx);
	emit(A64_B_(A64_COND_HI, jmp_offset), ctx);
	emit(A64_ADD_I(1, tcc, tcc, 1), ctx);

	/* prog = array->ptrs[index];
	 * अगर (prog == शून्य)
	 *     जाओ out;
	 */
	off = दुरत्व(काष्ठा bpf_array, ptrs);
	emit_a64_mov_i64(पंचांगp, off, ctx);
	emit(A64_ADD(1, पंचांगp, r2, पंचांगp), ctx);
	emit(A64_LSL(1, prg, r3, 3), ctx);
	emit(A64_LDR64(prg, पंचांगp, prg), ctx);
	emit(A64_CBZ(1, prg, jmp_offset), ctx);

	/* जाओ *(prog->bpf_func + prologue_offset); */
	off = दुरत्व(काष्ठा bpf_prog, bpf_func);
	emit_a64_mov_i64(पंचांगp, off, ctx);
	emit(A64_LDR64(पंचांगp, prg, पंचांगp), ctx);
	emit(A64_ADD_I(1, पंचांगp, पंचांगp, माप(u32) * PROLOGUE_OFFSET), ctx);
	emit(A64_ADD_I(1, A64_SP, A64_SP, ctx->stack_size), ctx);
	emit(A64_BR(पंचांगp), ctx);

	/* out: */
	अगर (out_offset == -1)
		out_offset = cur_offset;
	अगर (cur_offset != out_offset) अणु
		pr_err_once("tail_call out_offset = %d, expected %d!\n",
			    cur_offset, out_offset);
		वापस -1;
	पूर्ण
	वापस 0;
#अघोषित cur_offset
#अघोषित jmp_offset
पूर्ण

अटल व्योम build_epilogue(काष्ठा jit_ctx *ctx)
अणु
	स्थिर u8 r0 = bpf2a64[BPF_REG_0];
	स्थिर u8 r6 = bpf2a64[BPF_REG_6];
	स्थिर u8 r7 = bpf2a64[BPF_REG_7];
	स्थिर u8 r8 = bpf2a64[BPF_REG_8];
	स्थिर u8 r9 = bpf2a64[BPF_REG_9];
	स्थिर u8 fp = bpf2a64[BPF_REG_FP];

	/* We're करोne with BPF stack */
	emit(A64_ADD_I(1, A64_SP, A64_SP, ctx->stack_size), ctx);

	/* Restore fs (x25) and x26 */
	emit(A64_POP(fp, A64_R(26), A64_SP), ctx);

	/* Restore callee-saved रेजिस्टर */
	emit(A64_POP(r8, r9, A64_SP), ctx);
	emit(A64_POP(r6, r7, A64_SP), ctx);

	/* Restore FP/LR रेजिस्टरs */
	emit(A64_POP(A64_FP, A64_LR, A64_SP), ctx);

	/* Set वापस value */
	emit(A64_MOV(1, A64_R(0), r0), ctx);

	emit(A64_RET(A64_LR), ctx);
पूर्ण

#घोषणा BPF_FIXUP_OFFSET_MASK	GENMASK(26, 0)
#घोषणा BPF_FIXUP_REG_MASK	GENMASK(31, 27)

पूर्णांक arm64_bpf_fixup_exception(स्थिर काष्ठा exception_table_entry *ex,
			      काष्ठा pt_regs *regs)
अणु
	off_t offset = FIELD_GET(BPF_FIXUP_OFFSET_MASK, ex->fixup);
	पूर्णांक dst_reg = FIELD_GET(BPF_FIXUP_REG_MASK, ex->fixup);

	regs->regs[dst_reg] = 0;
	regs->pc = (अचिन्हित दीर्घ)&ex->fixup - offset;
	वापस 1;
पूर्ण

/* For accesses to BTF poपूर्णांकers, add an entry to the exception table */
अटल पूर्णांक add_exception_handler(स्थिर काष्ठा bpf_insn *insn,
				 काष्ठा jit_ctx *ctx,
				 पूर्णांक dst_reg)
अणु
	off_t offset;
	अचिन्हित दीर्घ pc;
	काष्ठा exception_table_entry *ex;

	अगर (!ctx->image)
		/* First pass */
		वापस 0;

	अगर (BPF_MODE(insn->code) != BPF_PROBE_MEM)
		वापस 0;

	अगर (!ctx->prog->aux->extable ||
	    WARN_ON_ONCE(ctx->exentry_idx >= ctx->prog->aux->num_exentries))
		वापस -EINVAL;

	ex = &ctx->prog->aux->extable[ctx->exentry_idx];
	pc = (अचिन्हित दीर्घ)&ctx->image[ctx->idx - 1];

	offset = pc - (दीर्घ)&ex->insn;
	अगर (WARN_ON_ONCE(offset >= 0 || offset < पूर्णांक_न्यून))
		वापस -दुस्फल;
	ex->insn = offset;

	/*
	 * Since the extable follows the program, the fixup offset is always
	 * negative and limited to BPF_JIT_REGION_SIZE. Store a positive value
	 * to keep things simple, and put the destination रेजिस्टर in the upper
	 * bits. We करोn't need to worry about buildसमय or runसमय sort
	 * modअगरying the upper bits because the table is alपढ़ोy sorted, and
	 * isn't part of the मुख्य exception table.
	 */
	offset = (दीर्घ)&ex->fixup - (pc + AARCH64_INSN_SIZE);
	अगर (!FIELD_FIT(BPF_FIXUP_OFFSET_MASK, offset))
		वापस -दुस्फल;

	ex->fixup = FIELD_PREP(BPF_FIXUP_OFFSET_MASK, offset) |
		    FIELD_PREP(BPF_FIXUP_REG_MASK, dst_reg);

	ctx->exentry_idx++;
	वापस 0;
पूर्ण

/* JITs an eBPF inकाष्ठाion.
 * Returns:
 * 0  - successfully JITed an 8-byte eBPF inकाष्ठाion.
 * >0 - successfully JITed a 16-byte eBPF inकाष्ठाion.
 * <0 - failed to JIT.
 */
अटल पूर्णांक build_insn(स्थिर काष्ठा bpf_insn *insn, काष्ठा jit_ctx *ctx,
		      bool extra_pass)
अणु
	स्थिर u8 code = insn->code;
	स्थिर u8 dst = bpf2a64[insn->dst_reg];
	स्थिर u8 src = bpf2a64[insn->src_reg];
	स्थिर u8 पंचांगp = bpf2a64[TMP_REG_1];
	स्थिर u8 पंचांगp2 = bpf2a64[TMP_REG_2];
	स्थिर u8 पंचांगp3 = bpf2a64[TMP_REG_3];
	स्थिर s16 off = insn->off;
	स्थिर s32 imm = insn->imm;
	स्थिर पूर्णांक i = insn - ctx->prog->insnsi;
	स्थिर bool is64 = BPF_CLASS(code) == BPF_ALU64 ||
			  BPF_CLASS(code) == BPF_JMP;
	स्थिर bool isdw = BPF_SIZE(code) == BPF_DW;
	u8 jmp_cond, reg;
	s32 jmp_offset;
	u32 a64_insn;
	पूर्णांक ret;

#घोषणा check_imm(bits, imm) करो अणु				\
	अगर ((((imm) > 0) && ((imm) >> (bits))) ||		\
	    (((imm) < 0) && (~(imm) >> (bits)))) अणु		\
		pr_info("[%2d] imm=%d(0x%x) out of range\n",	\
			i, imm, imm);				\
		वापस -EINVAL;					\
	पूर्ण							\
पूर्ण जबतक (0)
#घोषणा check_imm19(imm) check_imm(19, imm)
#घोषणा check_imm26(imm) check_imm(26, imm)

	चयन (code) अणु
	/* dst = src */
	हाल BPF_ALU | BPF_MOV | BPF_X:
	हाल BPF_ALU64 | BPF_MOV | BPF_X:
		emit(A64_MOV(is64, dst, src), ctx);
		अवरोध;
	/* dst = dst OP src */
	हाल BPF_ALU | BPF_ADD | BPF_X:
	हाल BPF_ALU64 | BPF_ADD | BPF_X:
		emit(A64_ADD(is64, dst, dst, src), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_SUB | BPF_X:
	हाल BPF_ALU64 | BPF_SUB | BPF_X:
		emit(A64_SUB(is64, dst, dst, src), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_AND | BPF_X:
	हाल BPF_ALU64 | BPF_AND | BPF_X:
		emit(A64_AND(is64, dst, dst, src), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_OR | BPF_X:
	हाल BPF_ALU64 | BPF_OR | BPF_X:
		emit(A64_ORR(is64, dst, dst, src), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_XOR | BPF_X:
	हाल BPF_ALU64 | BPF_XOR | BPF_X:
		emit(A64_EOR(is64, dst, dst, src), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_MUL | BPF_X:
	हाल BPF_ALU64 | BPF_MUL | BPF_X:
		emit(A64_MUL(is64, dst, dst, src), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_DIV | BPF_X:
	हाल BPF_ALU64 | BPF_DIV | BPF_X:
	हाल BPF_ALU | BPF_MOD | BPF_X:
	हाल BPF_ALU64 | BPF_MOD | BPF_X:
		चयन (BPF_OP(code)) अणु
		हाल BPF_DIV:
			emit(A64_UDIV(is64, dst, dst, src), ctx);
			अवरोध;
		हाल BPF_MOD:
			emit(A64_UDIV(is64, पंचांगp, dst, src), ctx);
			emit(A64_MSUB(is64, dst, dst, पंचांगp, src), ctx);
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_LSH | BPF_X:
	हाल BPF_ALU64 | BPF_LSH | BPF_X:
		emit(A64_LSLV(is64, dst, dst, src), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_RSH | BPF_X:
	हाल BPF_ALU64 | BPF_RSH | BPF_X:
		emit(A64_LSRV(is64, dst, dst, src), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_ARSH | BPF_X:
	हाल BPF_ALU64 | BPF_ARSH | BPF_X:
		emit(A64_ASRV(is64, dst, dst, src), ctx);
		अवरोध;
	/* dst = -dst */
	हाल BPF_ALU | BPF_NEG:
	हाल BPF_ALU64 | BPF_NEG:
		emit(A64_NEG(is64, dst, dst), ctx);
		अवरोध;
	/* dst = BSWAP##imm(dst) */
	हाल BPF_ALU | BPF_END | BPF_FROM_LE:
	हाल BPF_ALU | BPF_END | BPF_FROM_BE:
#अगर_घोषित CONFIG_CPU_BIG_ENDIAN
		अगर (BPF_SRC(code) == BPF_FROM_BE)
			जाओ emit_bswap_uxt;
#अन्यथा /* !CONFIG_CPU_BIG_ENDIAN */
		अगर (BPF_SRC(code) == BPF_FROM_LE)
			जाओ emit_bswap_uxt;
#पूर्ण_अगर
		चयन (imm) अणु
		हाल 16:
			emit(A64_REV16(is64, dst, dst), ctx);
			/* zero-extend 16 bits पूर्णांकo 64 bits */
			emit(A64_UXTH(is64, dst, dst), ctx);
			अवरोध;
		हाल 32:
			emit(A64_REV32(is64, dst, dst), ctx);
			/* upper 32 bits alपढ़ोy cleared */
			अवरोध;
		हाल 64:
			emit(A64_REV64(dst, dst), ctx);
			अवरोध;
		पूर्ण
		अवरोध;
emit_bswap_uxt:
		चयन (imm) अणु
		हाल 16:
			/* zero-extend 16 bits पूर्णांकo 64 bits */
			emit(A64_UXTH(is64, dst, dst), ctx);
			अवरोध;
		हाल 32:
			/* zero-extend 32 bits पूर्णांकo 64 bits */
			emit(A64_UXTW(is64, dst, dst), ctx);
			अवरोध;
		हाल 64:
			/* nop */
			अवरोध;
		पूर्ण
		अवरोध;
	/* dst = imm */
	हाल BPF_ALU | BPF_MOV | BPF_K:
	हाल BPF_ALU64 | BPF_MOV | BPF_K:
		emit_a64_mov_i(is64, dst, imm, ctx);
		अवरोध;
	/* dst = dst OP imm */
	हाल BPF_ALU | BPF_ADD | BPF_K:
	हाल BPF_ALU64 | BPF_ADD | BPF_K:
		अगर (is_addsub_imm(imm)) अणु
			emit(A64_ADD_I(is64, dst, dst, imm), ctx);
		पूर्ण अन्यथा अगर (is_addsub_imm(-imm)) अणु
			emit(A64_SUB_I(is64, dst, dst, -imm), ctx);
		पूर्ण अन्यथा अणु
			emit_a64_mov_i(is64, पंचांगp, imm, ctx);
			emit(A64_ADD(is64, dst, dst, पंचांगp), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_SUB | BPF_K:
	हाल BPF_ALU64 | BPF_SUB | BPF_K:
		अगर (is_addsub_imm(imm)) अणु
			emit(A64_SUB_I(is64, dst, dst, imm), ctx);
		पूर्ण अन्यथा अगर (is_addsub_imm(-imm)) अणु
			emit(A64_ADD_I(is64, dst, dst, -imm), ctx);
		पूर्ण अन्यथा अणु
			emit_a64_mov_i(is64, पंचांगp, imm, ctx);
			emit(A64_SUB(is64, dst, dst, पंचांगp), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_AND | BPF_K:
	हाल BPF_ALU64 | BPF_AND | BPF_K:
		a64_insn = A64_AND_I(is64, dst, dst, imm);
		अगर (a64_insn != AARCH64_BREAK_FAULT) अणु
			emit(a64_insn, ctx);
		पूर्ण अन्यथा अणु
			emit_a64_mov_i(is64, पंचांगp, imm, ctx);
			emit(A64_AND(is64, dst, dst, पंचांगp), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_OR | BPF_K:
	हाल BPF_ALU64 | BPF_OR | BPF_K:
		a64_insn = A64_ORR_I(is64, dst, dst, imm);
		अगर (a64_insn != AARCH64_BREAK_FAULT) अणु
			emit(a64_insn, ctx);
		पूर्ण अन्यथा अणु
			emit_a64_mov_i(is64, पंचांगp, imm, ctx);
			emit(A64_ORR(is64, dst, dst, पंचांगp), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_XOR | BPF_K:
	हाल BPF_ALU64 | BPF_XOR | BPF_K:
		a64_insn = A64_EOR_I(is64, dst, dst, imm);
		अगर (a64_insn != AARCH64_BREAK_FAULT) अणु
			emit(a64_insn, ctx);
		पूर्ण अन्यथा अणु
			emit_a64_mov_i(is64, पंचांगp, imm, ctx);
			emit(A64_EOR(is64, dst, dst, पंचांगp), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_MUL | BPF_K:
	हाल BPF_ALU64 | BPF_MUL | BPF_K:
		emit_a64_mov_i(is64, पंचांगp, imm, ctx);
		emit(A64_MUL(is64, dst, dst, पंचांगp), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_DIV | BPF_K:
	हाल BPF_ALU64 | BPF_DIV | BPF_K:
		emit_a64_mov_i(is64, पंचांगp, imm, ctx);
		emit(A64_UDIV(is64, dst, dst, पंचांगp), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_MOD | BPF_K:
	हाल BPF_ALU64 | BPF_MOD | BPF_K:
		emit_a64_mov_i(is64, पंचांगp2, imm, ctx);
		emit(A64_UDIV(is64, पंचांगp, dst, पंचांगp2), ctx);
		emit(A64_MSUB(is64, dst, dst, पंचांगp, पंचांगp2), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_LSH | BPF_K:
	हाल BPF_ALU64 | BPF_LSH | BPF_K:
		emit(A64_LSL(is64, dst, dst, imm), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_RSH | BPF_K:
	हाल BPF_ALU64 | BPF_RSH | BPF_K:
		emit(A64_LSR(is64, dst, dst, imm), ctx);
		अवरोध;
	हाल BPF_ALU | BPF_ARSH | BPF_K:
	हाल BPF_ALU64 | BPF_ARSH | BPF_K:
		emit(A64_ASR(is64, dst, dst, imm), ctx);
		अवरोध;

	/* JUMP off */
	हाल BPF_JMP | BPF_JA:
		jmp_offset = bpf2a64_offset(i, off, ctx);
		check_imm26(jmp_offset);
		emit(A64_B(jmp_offset), ctx);
		अवरोध;
	/* IF (dst COND src) JUMP off */
	हाल BPF_JMP | BPF_JEQ | BPF_X:
	हाल BPF_JMP | BPF_JGT | BPF_X:
	हाल BPF_JMP | BPF_JLT | BPF_X:
	हाल BPF_JMP | BPF_JGE | BPF_X:
	हाल BPF_JMP | BPF_JLE | BPF_X:
	हाल BPF_JMP | BPF_JNE | BPF_X:
	हाल BPF_JMP | BPF_JSGT | BPF_X:
	हाल BPF_JMP | BPF_JSLT | BPF_X:
	हाल BPF_JMP | BPF_JSGE | BPF_X:
	हाल BPF_JMP | BPF_JSLE | BPF_X:
	हाल BPF_JMP32 | BPF_JEQ | BPF_X:
	हाल BPF_JMP32 | BPF_JGT | BPF_X:
	हाल BPF_JMP32 | BPF_JLT | BPF_X:
	हाल BPF_JMP32 | BPF_JGE | BPF_X:
	हाल BPF_JMP32 | BPF_JLE | BPF_X:
	हाल BPF_JMP32 | BPF_JNE | BPF_X:
	हाल BPF_JMP32 | BPF_JSGT | BPF_X:
	हाल BPF_JMP32 | BPF_JSLT | BPF_X:
	हाल BPF_JMP32 | BPF_JSGE | BPF_X:
	हाल BPF_JMP32 | BPF_JSLE | BPF_X:
		emit(A64_CMP(is64, dst, src), ctx);
emit_cond_jmp:
		jmp_offset = bpf2a64_offset(i, off, ctx);
		check_imm19(jmp_offset);
		चयन (BPF_OP(code)) अणु
		हाल BPF_JEQ:
			jmp_cond = A64_COND_EQ;
			अवरोध;
		हाल BPF_JGT:
			jmp_cond = A64_COND_HI;
			अवरोध;
		हाल BPF_JLT:
			jmp_cond = A64_COND_CC;
			अवरोध;
		हाल BPF_JGE:
			jmp_cond = A64_COND_CS;
			अवरोध;
		हाल BPF_JLE:
			jmp_cond = A64_COND_LS;
			अवरोध;
		हाल BPF_JSET:
		हाल BPF_JNE:
			jmp_cond = A64_COND_NE;
			अवरोध;
		हाल BPF_JSGT:
			jmp_cond = A64_COND_GT;
			अवरोध;
		हाल BPF_JSLT:
			jmp_cond = A64_COND_LT;
			अवरोध;
		हाल BPF_JSGE:
			jmp_cond = A64_COND_GE;
			अवरोध;
		हाल BPF_JSLE:
			jmp_cond = A64_COND_LE;
			अवरोध;
		शेष:
			वापस -EFAULT;
		पूर्ण
		emit(A64_B_(jmp_cond, jmp_offset), ctx);
		अवरोध;
	हाल BPF_JMP | BPF_JSET | BPF_X:
	हाल BPF_JMP32 | BPF_JSET | BPF_X:
		emit(A64_TST(is64, dst, src), ctx);
		जाओ emit_cond_jmp;
	/* IF (dst COND imm) JUMP off */
	हाल BPF_JMP | BPF_JEQ | BPF_K:
	हाल BPF_JMP | BPF_JGT | BPF_K:
	हाल BPF_JMP | BPF_JLT | BPF_K:
	हाल BPF_JMP | BPF_JGE | BPF_K:
	हाल BPF_JMP | BPF_JLE | BPF_K:
	हाल BPF_JMP | BPF_JNE | BPF_K:
	हाल BPF_JMP | BPF_JSGT | BPF_K:
	हाल BPF_JMP | BPF_JSLT | BPF_K:
	हाल BPF_JMP | BPF_JSGE | BPF_K:
	हाल BPF_JMP | BPF_JSLE | BPF_K:
	हाल BPF_JMP32 | BPF_JEQ | BPF_K:
	हाल BPF_JMP32 | BPF_JGT | BPF_K:
	हाल BPF_JMP32 | BPF_JLT | BPF_K:
	हाल BPF_JMP32 | BPF_JGE | BPF_K:
	हाल BPF_JMP32 | BPF_JLE | BPF_K:
	हाल BPF_JMP32 | BPF_JNE | BPF_K:
	हाल BPF_JMP32 | BPF_JSGT | BPF_K:
	हाल BPF_JMP32 | BPF_JSLT | BPF_K:
	हाल BPF_JMP32 | BPF_JSGE | BPF_K:
	हाल BPF_JMP32 | BPF_JSLE | BPF_K:
		अगर (is_addsub_imm(imm)) अणु
			emit(A64_CMP_I(is64, dst, imm), ctx);
		पूर्ण अन्यथा अगर (is_addsub_imm(-imm)) अणु
			emit(A64_CMN_I(is64, dst, -imm), ctx);
		पूर्ण अन्यथा अणु
			emit_a64_mov_i(is64, पंचांगp, imm, ctx);
			emit(A64_CMP(is64, dst, पंचांगp), ctx);
		पूर्ण
		जाओ emit_cond_jmp;
	हाल BPF_JMP | BPF_JSET | BPF_K:
	हाल BPF_JMP32 | BPF_JSET | BPF_K:
		a64_insn = A64_TST_I(is64, dst, imm);
		अगर (a64_insn != AARCH64_BREAK_FAULT) अणु
			emit(a64_insn, ctx);
		पूर्ण अन्यथा अणु
			emit_a64_mov_i(is64, पंचांगp, imm, ctx);
			emit(A64_TST(is64, dst, पंचांगp), ctx);
		पूर्ण
		जाओ emit_cond_jmp;
	/* function call */
	हाल BPF_JMP | BPF_CALL:
	अणु
		स्थिर u8 r0 = bpf2a64[BPF_REG_0];
		bool func_addr_fixed;
		u64 func_addr;

		ret = bpf_jit_get_func_addr(ctx->prog, insn, extra_pass,
					    &func_addr, &func_addr_fixed);
		अगर (ret < 0)
			वापस ret;
		emit_addr_mov_i64(पंचांगp, func_addr, ctx);
		emit(A64_BLR(पंचांगp), ctx);
		emit(A64_MOV(1, r0, A64_R(0)), ctx);
		अवरोध;
	पूर्ण
	/* tail call */
	हाल BPF_JMP | BPF_TAIL_CALL:
		अगर (emit_bpf_tail_call(ctx))
			वापस -EFAULT;
		अवरोध;
	/* function वापस */
	हाल BPF_JMP | BPF_EXIT:
		/* Optimization: when last inकाष्ठाion is EXIT,
		   simply fallthrough to epilogue. */
		अगर (i == ctx->prog->len - 1)
			अवरोध;
		jmp_offset = epilogue_offset(ctx);
		check_imm26(jmp_offset);
		emit(A64_B(jmp_offset), ctx);
		अवरोध;

	/* dst = imm64 */
	हाल BPF_LD | BPF_IMM | BPF_DW:
	अणु
		स्थिर काष्ठा bpf_insn insn1 = insn[1];
		u64 imm64;

		imm64 = (u64)insn1.imm << 32 | (u32)imm;
		emit_a64_mov_i64(dst, imm64, ctx);

		वापस 1;
	पूर्ण

	/* LDX: dst = *(size *)(src + off) */
	हाल BPF_LDX | BPF_MEM | BPF_W:
	हाल BPF_LDX | BPF_MEM | BPF_H:
	हाल BPF_LDX | BPF_MEM | BPF_B:
	हाल BPF_LDX | BPF_MEM | BPF_DW:
	हाल BPF_LDX | BPF_PROBE_MEM | BPF_DW:
	हाल BPF_LDX | BPF_PROBE_MEM | BPF_W:
	हाल BPF_LDX | BPF_PROBE_MEM | BPF_H:
	हाल BPF_LDX | BPF_PROBE_MEM | BPF_B:
		emit_a64_mov_i(1, पंचांगp, off, ctx);
		चयन (BPF_SIZE(code)) अणु
		हाल BPF_W:
			emit(A64_LDR32(dst, src, पंचांगp), ctx);
			अवरोध;
		हाल BPF_H:
			emit(A64_LDRH(dst, src, पंचांगp), ctx);
			अवरोध;
		हाल BPF_B:
			emit(A64_LDRB(dst, src, पंचांगp), ctx);
			अवरोध;
		हाल BPF_DW:
			emit(A64_LDR64(dst, src, पंचांगp), ctx);
			अवरोध;
		पूर्ण

		ret = add_exception_handler(insn, ctx, dst);
		अगर (ret)
			वापस ret;
		अवरोध;

	/* ST: *(size *)(dst + off) = imm */
	हाल BPF_ST | BPF_MEM | BPF_W:
	हाल BPF_ST | BPF_MEM | BPF_H:
	हाल BPF_ST | BPF_MEM | BPF_B:
	हाल BPF_ST | BPF_MEM | BPF_DW:
		/* Load imm to a रेजिस्टर then store it */
		emit_a64_mov_i(1, पंचांगp2, off, ctx);
		emit_a64_mov_i(1, पंचांगp, imm, ctx);
		चयन (BPF_SIZE(code)) अणु
		हाल BPF_W:
			emit(A64_STR32(पंचांगp, dst, पंचांगp2), ctx);
			अवरोध;
		हाल BPF_H:
			emit(A64_STRH(पंचांगp, dst, पंचांगp2), ctx);
			अवरोध;
		हाल BPF_B:
			emit(A64_STRB(पंचांगp, dst, पंचांगp2), ctx);
			अवरोध;
		हाल BPF_DW:
			emit(A64_STR64(पंचांगp, dst, पंचांगp2), ctx);
			अवरोध;
		पूर्ण
		अवरोध;

	/* STX: *(size *)(dst + off) = src */
	हाल BPF_STX | BPF_MEM | BPF_W:
	हाल BPF_STX | BPF_MEM | BPF_H:
	हाल BPF_STX | BPF_MEM | BPF_B:
	हाल BPF_STX | BPF_MEM | BPF_DW:
		emit_a64_mov_i(1, पंचांगp, off, ctx);
		चयन (BPF_SIZE(code)) अणु
		हाल BPF_W:
			emit(A64_STR32(src, dst, पंचांगp), ctx);
			अवरोध;
		हाल BPF_H:
			emit(A64_STRH(src, dst, पंचांगp), ctx);
			अवरोध;
		हाल BPF_B:
			emit(A64_STRB(src, dst, पंचांगp), ctx);
			अवरोध;
		हाल BPF_DW:
			emit(A64_STR64(src, dst, पंचांगp), ctx);
			अवरोध;
		पूर्ण
		अवरोध;

	हाल BPF_STX | BPF_ATOMIC | BPF_W:
	हाल BPF_STX | BPF_ATOMIC | BPF_DW:
		अगर (insn->imm != BPF_ADD) अणु
			pr_err_once("unknown atomic op code %02x\n", insn->imm);
			वापस -EINVAL;
		पूर्ण

		/* STX XADD: lock *(u32 *)(dst + off) += src
		 * and
		 * STX XADD: lock *(u64 *)(dst + off) += src
		 */

		अगर (!off) अणु
			reg = dst;
		पूर्ण अन्यथा अणु
			emit_a64_mov_i(1, पंचांगp, off, ctx);
			emit(A64_ADD(1, पंचांगp, पंचांगp, dst), ctx);
			reg = पंचांगp;
		पूर्ण
		अगर (cpus_have_cap(ARM64_HAS_LSE_ATOMICS)) अणु
			emit(A64_STADD(isdw, reg, src), ctx);
		पूर्ण अन्यथा अणु
			emit(A64_LDXR(isdw, पंचांगp2, reg), ctx);
			emit(A64_ADD(isdw, पंचांगp2, पंचांगp2, src), ctx);
			emit(A64_STXR(isdw, पंचांगp2, reg, पंचांगp3), ctx);
			jmp_offset = -3;
			check_imm19(jmp_offset);
			emit(A64_CBNZ(0, पंचांगp3, jmp_offset), ctx);
		पूर्ण
		अवरोध;

	शेष:
		pr_err_once("unknown opcode %02x\n", code);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक build_body(काष्ठा jit_ctx *ctx, bool extra_pass)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->prog;
	पूर्णांक i;

	/*
	 * - offset[0] offset of the end of prologue,
	 *   start of the 1st inकाष्ठाion.
	 * - offset[1] - offset of the end of 1st inकाष्ठाion,
	 *   start of the 2nd inकाष्ठाion
	 * [....]
	 * - offset[3] - offset of the end of 3rd inकाष्ठाion,
	 *   start of 4th inकाष्ठाion
	 */
	क्रम (i = 0; i < prog->len; i++) अणु
		स्थिर काष्ठा bpf_insn *insn = &prog->insnsi[i];
		पूर्णांक ret;

		अगर (ctx->image == शून्य)
			ctx->offset[i] = ctx->idx;
		ret = build_insn(insn, ctx, extra_pass);
		अगर (ret > 0) अणु
			i++;
			अगर (ctx->image == शून्य)
				ctx->offset[i] = ctx->idx;
			जारी;
		पूर्ण
		अगर (ret)
			वापस ret;
	पूर्ण
	/*
	 * offset is allocated with prog->len + 1 so fill in
	 * the last element with the offset after the last
	 * inकाष्ठाion (end of program)
	 */
	अगर (ctx->image == शून्य)
		ctx->offset[i] = ctx->idx;

	वापस 0;
पूर्ण

अटल पूर्णांक validate_code(काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ctx->idx; i++) अणु
		u32 a64_insn = le32_to_cpu(ctx->image[i]);

		अगर (a64_insn == AARCH64_BREAK_FAULT)
			वापस -1;
	पूर्ण

	अगर (WARN_ON_ONCE(ctx->exentry_idx != ctx->prog->aux->num_exentries))
		वापस -1;

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम bpf_flush_icache(व्योम *start, व्योम *end)
अणु
	flush_icache_range((अचिन्हित दीर्घ)start, (अचिन्हित दीर्घ)end);
पूर्ण

काष्ठा arm64_jit_data अणु
	काष्ठा bpf_binary_header *header;
	u8 *image;
	काष्ठा jit_ctx ctx;
पूर्ण;

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog)
अणु
	पूर्णांक image_size, prog_size, extable_size;
	काष्ठा bpf_prog *पंचांगp, *orig_prog = prog;
	काष्ठा bpf_binary_header *header;
	काष्ठा arm64_jit_data *jit_data;
	bool was_classic = bpf_prog_was_classic(prog);
	bool पंचांगp_blinded = false;
	bool extra_pass = false;
	काष्ठा jit_ctx ctx;
	u8 *image_ptr;

	अगर (!prog->jit_requested)
		वापस orig_prog;

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

	jit_data = prog->aux->jit_data;
	अगर (!jit_data) अणु
		jit_data = kzalloc(माप(*jit_data), GFP_KERNEL);
		अगर (!jit_data) अणु
			prog = orig_prog;
			जाओ out;
		पूर्ण
		prog->aux->jit_data = jit_data;
	पूर्ण
	अगर (jit_data->ctx.offset) अणु
		ctx = jit_data->ctx;
		image_ptr = jit_data->image;
		header = jit_data->header;
		extra_pass = true;
		prog_size = माप(u32) * ctx.idx;
		जाओ skip_init_ctx;
	पूर्ण
	स_रखो(&ctx, 0, माप(ctx));
	ctx.prog = prog;

	ctx.offset = kसुस्मृति(prog->len + 1, माप(पूर्णांक), GFP_KERNEL);
	अगर (ctx.offset == शून्य) अणु
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	/* 1. Initial fake pass to compute ctx->idx. */

	/* Fake pass to fill in ctx->offset. */
	अगर (build_body(&ctx, extra_pass)) अणु
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	अगर (build_prologue(&ctx, was_classic)) अणु
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	ctx.epilogue_offset = ctx.idx;
	build_epilogue(&ctx);

	extable_size = prog->aux->num_exentries *
		माप(काष्ठा exception_table_entry);

	/* Now we know the actual image size. */
	prog_size = माप(u32) * ctx.idx;
	image_size = prog_size + extable_size;
	header = bpf_jit_binary_alloc(image_size, &image_ptr,
				      माप(u32), jit_fill_hole);
	अगर (header == शून्य) अणु
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	/* 2. Now, the actual pass. */

	ctx.image = (__le32 *)image_ptr;
	अगर (extable_size)
		prog->aux->extable = (व्योम *)image_ptr + prog_size;
skip_init_ctx:
	ctx.idx = 0;
	ctx.exentry_idx = 0;

	build_prologue(&ctx, was_classic);

	अगर (build_body(&ctx, extra_pass)) अणु
		bpf_jit_binary_मुक्त(header);
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	build_epilogue(&ctx);

	/* 3. Extra pass to validate JITed code. */
	अगर (validate_code(&ctx)) अणु
		bpf_jit_binary_मुक्त(header);
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	/* And we're करोne. */
	अगर (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, prog_size, 2, ctx.image);

	bpf_flush_icache(header, ctx.image + ctx.idx);

	अगर (!prog->is_func || extra_pass) अणु
		अगर (extra_pass && ctx.idx != jit_data->ctx.idx) अणु
			pr_err_once("multi-func JIT bug %d != %d\n",
				    ctx.idx, jit_data->ctx.idx);
			bpf_jit_binary_मुक्त(header);
			prog->bpf_func = शून्य;
			prog->jited = 0;
			जाओ out_off;
		पूर्ण
		bpf_jit_binary_lock_ro(header);
	पूर्ण अन्यथा अणु
		jit_data->ctx = ctx;
		jit_data->image = image_ptr;
		jit_data->header = header;
	पूर्ण
	prog->bpf_func = (व्योम *)ctx.image;
	prog->jited = 1;
	prog->jited_len = prog_size;

	अगर (!prog->is_func || extra_pass) अणु
		bpf_prog_fill_jited_linfo(prog, ctx.offset + 1);
out_off:
		kमुक्त(ctx.offset);
		kमुक्त(jit_data);
		prog->aux->jit_data = शून्य;
	पूर्ण
out:
	अगर (पंचांगp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   पंचांगp : orig_prog);
	वापस prog;
पूर्ण

व्योम *bpf_jit_alloc_exec(अचिन्हित दीर्घ size)
अणु
	वापस __vदो_स्मृति_node_range(size, PAGE_SIZE, BPF_JIT_REGION_START,
				    BPF_JIT_REGION_END, GFP_KERNEL,
				    PAGE_KERNEL, 0, NUMA_NO_NODE,
				    __builtin_वापस_address(0));
पूर्ण

व्योम bpf_jit_मुक्त_exec(व्योम *addr)
अणु
	वापस vमुक्त(addr);
पूर्ण
