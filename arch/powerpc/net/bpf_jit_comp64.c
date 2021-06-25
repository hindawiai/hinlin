<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bpf_jit_comp64.c: eBPF JIT compiler
 *
 * Copyright 2016 Naveen N. Rao <naveen.n.rao@linux.vnet.ibm.com>
 *		  IBM Corporation
 *
 * Based on the घातerpc classic BPF JIT compiler by Matt Evans
 */
#समावेश <linux/moduleloader.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/यंत्र-compat.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <linux/bpf.h>

#समावेश "bpf_jit64.h"

अटल अंतरभूत bool bpf_has_stack_frame(काष्ठा codegen_context *ctx)
अणु
	/*
	 * We only need a stack frame अगर:
	 * - we call other functions (kernel helpers), or
	 * - the bpf program uses its stack area
	 * The latter condition is deduced from the usage of BPF_REG_FP
	 */
	वापस ctx->seen & SEEN_FUNC || bpf_is_seen_रेजिस्टर(ctx, b2p[BPF_REG_FP]);
पूर्ण

/*
 * When not setting up our own stackframe, the redzone usage is:
 *
 *		[	prev sp		] <-------------
 *		[	  ...       	] 		|
 * sp (r1) --->	[    stack poपूर्णांकer	] --------------
 *		[   nv gpr save area	] 6*8
 *		[    tail_call_cnt	] 8
 *		[    local_पंचांगp_var	] 8
 *		[   unused red zone	] 208 bytes रक्षित
 */
अटल पूर्णांक bpf_jit_stack_local(काष्ठा codegen_context *ctx)
अणु
	अगर (bpf_has_stack_frame(ctx))
		वापस STACK_FRAME_MIN_SIZE + ctx->stack_size;
	अन्यथा
		वापस -(BPF_PPC_STACK_SAVE + 16);
पूर्ण

अटल पूर्णांक bpf_jit_stack_tailcallcnt(काष्ठा codegen_context *ctx)
अणु
	वापस bpf_jit_stack_local(ctx) + 8;
पूर्ण

अटल पूर्णांक bpf_jit_stack_दुरत्व(काष्ठा codegen_context *ctx, पूर्णांक reg)
अणु
	अगर (reg >= BPF_PPC_NVR_MIN && reg < 32)
		वापस (bpf_has_stack_frame(ctx) ?
			(BPF_PPC_STACKFRAME + ctx->stack_size) : 0)
				- (8 * (32 - reg));

	pr_err("BPF JIT is asking about unknown registers");
	BUG();
पूर्ण

व्योम bpf_jit_पुनः_स्मृति_regs(काष्ठा codegen_context *ctx)
अणु
पूर्ण

व्योम bpf_jit_build_prologue(u32 *image, काष्ठा codegen_context *ctx)
अणु
	पूर्णांक i;

	/*
	 * Initialize tail_call_cnt अगर we करो tail calls.
	 * Otherwise, put in NOPs so that it can be skipped when we are
	 * invoked through a tail call.
	 */
	अगर (ctx->seen & SEEN_TAILCALL) अणु
		EMIT(PPC_RAW_LI(b2p[TMP_REG_1], 0));
		/* this goes in the redzone */
		PPC_BPF_STL(b2p[TMP_REG_1], 1, -(BPF_PPC_STACK_SAVE + 8));
	पूर्ण अन्यथा अणु
		EMIT(PPC_RAW_NOP());
		EMIT(PPC_RAW_NOP());
	पूर्ण

#घोषणा BPF_TAILCALL_PROLOGUE_SIZE	8

	अगर (bpf_has_stack_frame(ctx)) अणु
		/*
		 * We need a stack frame, but we करोn't necessarily need to
		 * save/restore LR unless we call other functions
		 */
		अगर (ctx->seen & SEEN_FUNC) अणु
			EMIT(PPC_INST_MFLR | __PPC_RT(R0));
			PPC_BPF_STL(0, 1, PPC_LR_STKOFF);
		पूर्ण

		PPC_BPF_STLU(1, 1, -(BPF_PPC_STACKFRAME + ctx->stack_size));
	पूर्ण

	/*
	 * Back up non-अस्थिर regs -- BPF रेजिस्टरs 6-10
	 * If we haven't created our own stack frame, we save these
	 * in the रक्षित zone below the previous stack frame
	 */
	क्रम (i = BPF_REG_6; i <= BPF_REG_10; i++)
		अगर (bpf_is_seen_रेजिस्टर(ctx, b2p[i]))
			PPC_BPF_STL(b2p[i], 1, bpf_jit_stack_दुरत्व(ctx, b2p[i]));

	/* Setup frame poपूर्णांकer to poपूर्णांक to the bpf stack area */
	अगर (bpf_is_seen_रेजिस्टर(ctx, b2p[BPF_REG_FP]))
		EMIT(PPC_RAW_ADDI(b2p[BPF_REG_FP], 1,
				STACK_FRAME_MIN_SIZE + ctx->stack_size));
पूर्ण

अटल व्योम bpf_jit_emit_common_epilogue(u32 *image, काष्ठा codegen_context *ctx)
अणु
	पूर्णांक i;

	/* Restore NVRs */
	क्रम (i = BPF_REG_6; i <= BPF_REG_10; i++)
		अगर (bpf_is_seen_रेजिस्टर(ctx, b2p[i]))
			PPC_BPF_LL(b2p[i], 1, bpf_jit_stack_दुरत्व(ctx, b2p[i]));

	/* Tear करोwn our stack frame */
	अगर (bpf_has_stack_frame(ctx)) अणु
		EMIT(PPC_RAW_ADDI(1, 1, BPF_PPC_STACKFRAME + ctx->stack_size));
		अगर (ctx->seen & SEEN_FUNC) अणु
			PPC_BPF_LL(0, 1, PPC_LR_STKOFF);
			EMIT(PPC_RAW_MTLR(0));
		पूर्ण
	पूर्ण
पूर्ण

व्योम bpf_jit_build_epilogue(u32 *image, काष्ठा codegen_context *ctx)
अणु
	bpf_jit_emit_common_epilogue(image, ctx);

	/* Move result to r3 */
	EMIT(PPC_RAW_MR(3, b2p[BPF_REG_0]));

	EMIT(PPC_RAW_BLR());
पूर्ण

अटल व्योम bpf_jit_emit_func_call_hlp(u32 *image, काष्ठा codegen_context *ctx,
				       u64 func)
अणु
#अगर_घोषित PPC64_ELF_ABI_v1
	/* func poपूर्णांकs to the function descriptor */
	PPC_LI64(b2p[TMP_REG_2], func);
	/* Load actual entry poपूर्णांक from function descriptor */
	PPC_BPF_LL(b2p[TMP_REG_1], b2p[TMP_REG_2], 0);
	/* ... and move it to LR */
	EMIT(PPC_RAW_MTLR(b2p[TMP_REG_1]));
	/*
	 * Load TOC from function descriptor at offset 8.
	 * We can clobber r2 since we get called through a
	 * function poपूर्णांकer (so caller will save/restore r2)
	 * and since we करोn't use a TOC ourself.
	 */
	PPC_BPF_LL(2, b2p[TMP_REG_2], 8);
#अन्यथा
	/* We can clobber r12 */
	PPC_FUNC_ADDR(12, func);
	EMIT(PPC_RAW_MTLR(12));
#पूर्ण_अगर
	EMIT(PPC_RAW_BLRL());
पूर्ण

व्योम bpf_jit_emit_func_call_rel(u32 *image, काष्ठा codegen_context *ctx, u64 func)
अणु
	अचिन्हित पूर्णांक i, ctx_idx = ctx->idx;

	/* Load function address पूर्णांकo r12 */
	PPC_LI64(12, func);

	/* For bpf-to-bpf function calls, the callee's address is unknown
	 * until the last extra pass. As seen above, we use PPC_LI64() to
	 * load the callee's address, but this may optimize the number of
	 * inकाष्ठाions required based on the nature of the address.
	 *
	 * Since we करोn't want the number of inकाष्ठाions emitted to change,
	 * we pad the optimized PPC_LI64() call with NOPs to guarantee that
	 * we always have a five-inकाष्ठाion sequence, which is the maximum
	 * that PPC_LI64() can emit.
	 */
	क्रम (i = ctx->idx - ctx_idx; i < 5; i++)
		EMIT(PPC_RAW_NOP());

#अगर_घोषित PPC64_ELF_ABI_v1
	/*
	 * Load TOC from function descriptor at offset 8.
	 * We can clobber r2 since we get called through a
	 * function poपूर्णांकer (so caller will save/restore r2)
	 * and since we करोn't use a TOC ourself.
	 */
	PPC_BPF_LL(2, 12, 8);
	/* Load actual entry poपूर्णांक from function descriptor */
	PPC_BPF_LL(12, 12, 0);
#पूर्ण_अगर

	EMIT(PPC_RAW_MTLR(12));
	EMIT(PPC_RAW_BLRL());
पूर्ण

अटल व्योम bpf_jit_emit_tail_call(u32 *image, काष्ठा codegen_context *ctx, u32 out)
अणु
	/*
	 * By now, the eBPF program has alपढ़ोy setup parameters in r3, r4 and r5
	 * r3/BPF_REG_1 - poपूर्णांकer to ctx -- passed as is to the next bpf program
	 * r4/BPF_REG_2 - poपूर्णांकer to bpf_array
	 * r5/BPF_REG_3 - index in bpf_array
	 */
	पूर्णांक b2p_bpf_array = b2p[BPF_REG_2];
	पूर्णांक b2p_index = b2p[BPF_REG_3];

	/*
	 * अगर (index >= array->map.max_entries)
	 *   जाओ out;
	 */
	EMIT(PPC_RAW_LWZ(b2p[TMP_REG_1], b2p_bpf_array, दुरत्व(काष्ठा bpf_array, map.max_entries)));
	EMIT(PPC_RAW_RLWINM(b2p_index, b2p_index, 0, 0, 31));
	EMIT(PPC_RAW_CMPLW(b2p_index, b2p[TMP_REG_1]));
	PPC_BCC(COND_GE, out);

	/*
	 * अगर (tail_call_cnt > MAX_TAIL_CALL_CNT)
	 *   जाओ out;
	 */
	PPC_BPF_LL(b2p[TMP_REG_1], 1, bpf_jit_stack_tailcallcnt(ctx));
	EMIT(PPC_RAW_CMPLWI(b2p[TMP_REG_1], MAX_TAIL_CALL_CNT));
	PPC_BCC(COND_GT, out);

	/*
	 * tail_call_cnt++;
	 */
	EMIT(PPC_RAW_ADDI(b2p[TMP_REG_1], b2p[TMP_REG_1], 1));
	PPC_BPF_STL(b2p[TMP_REG_1], 1, bpf_jit_stack_tailcallcnt(ctx));

	/* prog = array->ptrs[index]; */
	EMIT(PPC_RAW_MULI(b2p[TMP_REG_1], b2p_index, 8));
	EMIT(PPC_RAW_ADD(b2p[TMP_REG_1], b2p[TMP_REG_1], b2p_bpf_array));
	PPC_BPF_LL(b2p[TMP_REG_1], b2p[TMP_REG_1], दुरत्व(काष्ठा bpf_array, ptrs));

	/*
	 * अगर (prog == शून्य)
	 *   जाओ out;
	 */
	EMIT(PPC_RAW_CMPLDI(b2p[TMP_REG_1], 0));
	PPC_BCC(COND_EQ, out);

	/* जाओ *(prog->bpf_func + prologue_size); */
	PPC_BPF_LL(b2p[TMP_REG_1], b2p[TMP_REG_1], दुरत्व(काष्ठा bpf_prog, bpf_func));
#अगर_घोषित PPC64_ELF_ABI_v1
	/* skip past the function descriptor */
	EMIT(PPC_RAW_ADDI(b2p[TMP_REG_1], b2p[TMP_REG_1],
			FUNCTION_DESCR_SIZE + BPF_TAILCALL_PROLOGUE_SIZE));
#अन्यथा
	EMIT(PPC_RAW_ADDI(b2p[TMP_REG_1], b2p[TMP_REG_1], BPF_TAILCALL_PROLOGUE_SIZE));
#पूर्ण_अगर
	EMIT(PPC_RAW_MTCTR(b2p[TMP_REG_1]));

	/* tear करोwn stack, restore NVRs, ... */
	bpf_jit_emit_common_epilogue(image, ctx);

	EMIT(PPC_RAW_BCTR());
	/* out: */
पूर्ण

/* Assemble the body code between the prologue & epilogue */
पूर्णांक bpf_jit_build_body(काष्ठा bpf_prog *fp, u32 *image, काष्ठा codegen_context *ctx,
		       u32 *addrs, bool extra_pass)
अणु
	स्थिर काष्ठा bpf_insn *insn = fp->insnsi;
	पूर्णांक flen = fp->len;
	पूर्णांक i, ret;

	/* Start of epilogue code - will only be valid 2nd pass onwards */
	u32 निकास_addr = addrs[flen];

	क्रम (i = 0; i < flen; i++) अणु
		u32 code = insn[i].code;
		u32 dst_reg = b2p[insn[i].dst_reg];
		u32 src_reg = b2p[insn[i].src_reg];
		s16 off = insn[i].off;
		s32 imm = insn[i].imm;
		bool func_addr_fixed;
		u64 func_addr;
		u64 imm64;
		u32 true_cond;
		u32 पंचांगp_idx;

		/*
		 * addrs[] maps a BPF bytecode address पूर्णांकo a real offset from
		 * the start of the body code.
		 */
		addrs[i] = ctx->idx * 4;

		/*
		 * As an optimization, we note करोwn which non-अस्थिर रेजिस्टरs
		 * are used so that we can only save/restore those in our
		 * prologue and epilogue. We करो this here regardless of whether
		 * the actual BPF inकाष्ठाion uses src/dst रेजिस्टरs or not
		 * (क्रम instance, BPF_CALL करोes not use them). The expectation
		 * is that those inकाष्ठाions will have src_reg/dst_reg set to
		 * 0. Even otherwise, we just lose some prologue/epilogue
		 * optimization but everything अन्यथा should work without
		 * any issues.
		 */
		अगर (dst_reg >= BPF_PPC_NVR_MIN && dst_reg < 32)
			bpf_set_seen_रेजिस्टर(ctx, dst_reg);
		अगर (src_reg >= BPF_PPC_NVR_MIN && src_reg < 32)
			bpf_set_seen_रेजिस्टर(ctx, src_reg);

		चयन (code) अणु
		/*
		 * Arithmetic operations: ADD/SUB/MUL/DIV/MOD/NEG
		 */
		हाल BPF_ALU | BPF_ADD | BPF_X: /* (u32) dst += (u32) src */
		हाल BPF_ALU64 | BPF_ADD | BPF_X: /* dst += src */
			EMIT(PPC_RAW_ADD(dst_reg, dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_SUB | BPF_X: /* (u32) dst -= (u32) src */
		हाल BPF_ALU64 | BPF_SUB | BPF_X: /* dst -= src */
			EMIT(PPC_RAW_SUB(dst_reg, dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_ADD | BPF_K: /* (u32) dst += (u32) imm */
		हाल BPF_ALU | BPF_SUB | BPF_K: /* (u32) dst -= (u32) imm */
		हाल BPF_ALU64 | BPF_ADD | BPF_K: /* dst += imm */
		हाल BPF_ALU64 | BPF_SUB | BPF_K: /* dst -= imm */
			अगर (BPF_OP(code) == BPF_SUB)
				imm = -imm;
			अगर (imm) अणु
				अगर (imm >= -32768 && imm < 32768)
					EMIT(PPC_RAW_ADDI(dst_reg, dst_reg, IMM_L(imm)));
				अन्यथा अणु
					PPC_LI32(b2p[TMP_REG_1], imm);
					EMIT(PPC_RAW_ADD(dst_reg, dst_reg, b2p[TMP_REG_1]));
				पूर्ण
			पूर्ण
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_MUL | BPF_X: /* (u32) dst *= (u32) src */
		हाल BPF_ALU64 | BPF_MUL | BPF_X: /* dst *= src */
			अगर (BPF_CLASS(code) == BPF_ALU)
				EMIT(PPC_RAW_MULW(dst_reg, dst_reg, src_reg));
			अन्यथा
				EMIT(PPC_RAW_MULD(dst_reg, dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_MUL | BPF_K: /* (u32) dst *= (u32) imm */
		हाल BPF_ALU64 | BPF_MUL | BPF_K: /* dst *= imm */
			अगर (imm >= -32768 && imm < 32768)
				EMIT(PPC_RAW_MULI(dst_reg, dst_reg, IMM_L(imm)));
			अन्यथा अणु
				PPC_LI32(b2p[TMP_REG_1], imm);
				अगर (BPF_CLASS(code) == BPF_ALU)
					EMIT(PPC_RAW_MULW(dst_reg, dst_reg,
							b2p[TMP_REG_1]));
				अन्यथा
					EMIT(PPC_RAW_MULD(dst_reg, dst_reg,
							b2p[TMP_REG_1]));
			पूर्ण
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_DIV | BPF_X: /* (u32) dst /= (u32) src */
		हाल BPF_ALU | BPF_MOD | BPF_X: /* (u32) dst %= (u32) src */
			अगर (BPF_OP(code) == BPF_MOD) अणु
				EMIT(PPC_RAW_DIVWU(b2p[TMP_REG_1], dst_reg, src_reg));
				EMIT(PPC_RAW_MULW(b2p[TMP_REG_1], src_reg,
						b2p[TMP_REG_1]));
				EMIT(PPC_RAW_SUB(dst_reg, dst_reg, b2p[TMP_REG_1]));
			पूर्ण अन्यथा
				EMIT(PPC_RAW_DIVWU(dst_reg, dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU64 | BPF_DIV | BPF_X: /* dst /= src */
		हाल BPF_ALU64 | BPF_MOD | BPF_X: /* dst %= src */
			अगर (BPF_OP(code) == BPF_MOD) अणु
				EMIT(PPC_RAW_DIVDU(b2p[TMP_REG_1], dst_reg, src_reg));
				EMIT(PPC_RAW_MULD(b2p[TMP_REG_1], src_reg,
						b2p[TMP_REG_1]));
				EMIT(PPC_RAW_SUB(dst_reg, dst_reg, b2p[TMP_REG_1]));
			पूर्ण अन्यथा
				EMIT(PPC_RAW_DIVDU(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU | BPF_MOD | BPF_K: /* (u32) dst %= (u32) imm */
		हाल BPF_ALU | BPF_DIV | BPF_K: /* (u32) dst /= (u32) imm */
		हाल BPF_ALU64 | BPF_MOD | BPF_K: /* dst %= imm */
		हाल BPF_ALU64 | BPF_DIV | BPF_K: /* dst /= imm */
			अगर (imm == 0)
				वापस -EINVAL;
			अन्यथा अगर (imm == 1)
				जाओ bpf_alu32_trunc;

			PPC_LI32(b2p[TMP_REG_1], imm);
			चयन (BPF_CLASS(code)) अणु
			हाल BPF_ALU:
				अगर (BPF_OP(code) == BPF_MOD) अणु
					EMIT(PPC_RAW_DIVWU(b2p[TMP_REG_2],
							dst_reg,
							b2p[TMP_REG_1]));
					EMIT(PPC_RAW_MULW(b2p[TMP_REG_1],
							b2p[TMP_REG_1],
							b2p[TMP_REG_2]));
					EMIT(PPC_RAW_SUB(dst_reg, dst_reg,
							b2p[TMP_REG_1]));
				पूर्ण अन्यथा
					EMIT(PPC_RAW_DIVWU(dst_reg, dst_reg,
							b2p[TMP_REG_1]));
				अवरोध;
			हाल BPF_ALU64:
				अगर (BPF_OP(code) == BPF_MOD) अणु
					EMIT(PPC_RAW_DIVDU(b2p[TMP_REG_2],
							dst_reg,
							b2p[TMP_REG_1]));
					EMIT(PPC_RAW_MULD(b2p[TMP_REG_1],
							b2p[TMP_REG_1],
							b2p[TMP_REG_2]));
					EMIT(PPC_RAW_SUB(dst_reg, dst_reg,
							b2p[TMP_REG_1]));
				पूर्ण अन्यथा
					EMIT(PPC_RAW_DIVDU(dst_reg, dst_reg,
							b2p[TMP_REG_1]));
				अवरोध;
			पूर्ण
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_NEG: /* (u32) dst = -dst */
		हाल BPF_ALU64 | BPF_NEG: /* dst = -dst */
			EMIT(PPC_RAW_NEG(dst_reg, dst_reg));
			जाओ bpf_alu32_trunc;

		/*
		 * Logical operations: AND/OR/XOR/[A]LSH/[A]RSH
		 */
		हाल BPF_ALU | BPF_AND | BPF_X: /* (u32) dst = dst & src */
		हाल BPF_ALU64 | BPF_AND | BPF_X: /* dst = dst & src */
			EMIT(PPC_RAW_AND(dst_reg, dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_AND | BPF_K: /* (u32) dst = dst & imm */
		हाल BPF_ALU64 | BPF_AND | BPF_K: /* dst = dst & imm */
			अगर (!IMM_H(imm))
				EMIT(PPC_RAW_ANDI(dst_reg, dst_reg, IMM_L(imm)));
			अन्यथा अणु
				/* Sign-extended */
				PPC_LI32(b2p[TMP_REG_1], imm);
				EMIT(PPC_RAW_AND(dst_reg, dst_reg, b2p[TMP_REG_1]));
			पूर्ण
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_OR | BPF_X: /* dst = (u32) dst | (u32) src */
		हाल BPF_ALU64 | BPF_OR | BPF_X: /* dst = dst | src */
			EMIT(PPC_RAW_OR(dst_reg, dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_OR | BPF_K:/* dst = (u32) dst | (u32) imm */
		हाल BPF_ALU64 | BPF_OR | BPF_K:/* dst = dst | imm */
			अगर (imm < 0 && BPF_CLASS(code) == BPF_ALU64) अणु
				/* Sign-extended */
				PPC_LI32(b2p[TMP_REG_1], imm);
				EMIT(PPC_RAW_OR(dst_reg, dst_reg, b2p[TMP_REG_1]));
			पूर्ण अन्यथा अणु
				अगर (IMM_L(imm))
					EMIT(PPC_RAW_ORI(dst_reg, dst_reg, IMM_L(imm)));
				अगर (IMM_H(imm))
					EMIT(PPC_RAW_ORIS(dst_reg, dst_reg, IMM_H(imm)));
			पूर्ण
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_XOR | BPF_X: /* (u32) dst ^= src */
		हाल BPF_ALU64 | BPF_XOR | BPF_X: /* dst ^= src */
			EMIT(PPC_RAW_XOR(dst_reg, dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_XOR | BPF_K: /* (u32) dst ^= (u32) imm */
		हाल BPF_ALU64 | BPF_XOR | BPF_K: /* dst ^= imm */
			अगर (imm < 0 && BPF_CLASS(code) == BPF_ALU64) अणु
				/* Sign-extended */
				PPC_LI32(b2p[TMP_REG_1], imm);
				EMIT(PPC_RAW_XOR(dst_reg, dst_reg, b2p[TMP_REG_1]));
			पूर्ण अन्यथा अणु
				अगर (IMM_L(imm))
					EMIT(PPC_RAW_XORI(dst_reg, dst_reg, IMM_L(imm)));
				अगर (IMM_H(imm))
					EMIT(PPC_RAW_XORIS(dst_reg, dst_reg, IMM_H(imm)));
			पूर्ण
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_LSH | BPF_X: /* (u32) dst <<= (u32) src */
			/* slw clears top 32 bits */
			EMIT(PPC_RAW_SLW(dst_reg, dst_reg, src_reg));
			/* skip zero extension move, but set address map. */
			अगर (insn_is_zext(&insn[i + 1]))
				addrs[++i] = ctx->idx * 4;
			अवरोध;
		हाल BPF_ALU64 | BPF_LSH | BPF_X: /* dst <<= src; */
			EMIT(PPC_RAW_SLD(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU | BPF_LSH | BPF_K: /* (u32) dst <<== (u32) imm */
			/* with imm 0, we still need to clear top 32 bits */
			EMIT(PPC_RAW_SLWI(dst_reg, dst_reg, imm));
			अगर (insn_is_zext(&insn[i + 1]))
				addrs[++i] = ctx->idx * 4;
			अवरोध;
		हाल BPF_ALU64 | BPF_LSH | BPF_K: /* dst <<== imm */
			अगर (imm != 0)
				EMIT(PPC_RAW_SLDI(dst_reg, dst_reg, imm));
			अवरोध;
		हाल BPF_ALU | BPF_RSH | BPF_X: /* (u32) dst >>= (u32) src */
			EMIT(PPC_RAW_SRW(dst_reg, dst_reg, src_reg));
			अगर (insn_is_zext(&insn[i + 1]))
				addrs[++i] = ctx->idx * 4;
			अवरोध;
		हाल BPF_ALU64 | BPF_RSH | BPF_X: /* dst >>= src */
			EMIT(PPC_RAW_SRD(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU | BPF_RSH | BPF_K: /* (u32) dst >>= (u32) imm */
			EMIT(PPC_RAW_SRWI(dst_reg, dst_reg, imm));
			अगर (insn_is_zext(&insn[i + 1]))
				addrs[++i] = ctx->idx * 4;
			अवरोध;
		हाल BPF_ALU64 | BPF_RSH | BPF_K: /* dst >>= imm */
			अगर (imm != 0)
				EMIT(PPC_RAW_SRDI(dst_reg, dst_reg, imm));
			अवरोध;
		हाल BPF_ALU | BPF_ARSH | BPF_X: /* (s32) dst >>= src */
			EMIT(PPC_RAW_SRAW(dst_reg, dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU64 | BPF_ARSH | BPF_X: /* (s64) dst >>= src */
			EMIT(PPC_RAW_SRAD(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU | BPF_ARSH | BPF_K: /* (s32) dst >>= imm */
			EMIT(PPC_RAW_SRAWI(dst_reg, dst_reg, imm));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU64 | BPF_ARSH | BPF_K: /* (s64) dst >>= imm */
			अगर (imm != 0)
				EMIT(PPC_RAW_SRADI(dst_reg, dst_reg, imm));
			अवरोध;

		/*
		 * MOV
		 */
		हाल BPF_ALU | BPF_MOV | BPF_X: /* (u32) dst = src */
		हाल BPF_ALU64 | BPF_MOV | BPF_X: /* dst = src */
			अगर (imm == 1) अणु
				/* special mov32 क्रम zext */
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 0, 0, 31));
				अवरोध;
			पूर्ण
			EMIT(PPC_RAW_MR(dst_reg, src_reg));
			जाओ bpf_alu32_trunc;
		हाल BPF_ALU | BPF_MOV | BPF_K: /* (u32) dst = imm */
		हाल BPF_ALU64 | BPF_MOV | BPF_K: /* dst = (s64) imm */
			PPC_LI32(dst_reg, imm);
			अगर (imm < 0)
				जाओ bpf_alu32_trunc;
			अन्यथा अगर (insn_is_zext(&insn[i + 1]))
				addrs[++i] = ctx->idx * 4;
			अवरोध;

bpf_alu32_trunc:
		/* Truncate to 32-bits */
		अगर (BPF_CLASS(code) == BPF_ALU && !fp->aux->verअगरier_zext)
			EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 0, 0, 31));
		अवरोध;

		/*
		 * BPF_FROM_BE/LE
		 */
		हाल BPF_ALU | BPF_END | BPF_FROM_LE:
		हाल BPF_ALU | BPF_END | BPF_FROM_BE:
#अगर_घोषित __BIG_ENDIAN__
			अगर (BPF_SRC(code) == BPF_FROM_BE)
				जाओ emit_clear;
#अन्यथा /* !__BIG_ENDIAN__ */
			अगर (BPF_SRC(code) == BPF_FROM_LE)
				जाओ emit_clear;
#पूर्ण_अगर
			चयन (imm) अणु
			हाल 16:
				/* Rotate 8 bits left & mask with 0x0000ff00 */
				EMIT(PPC_RAW_RLWINM(b2p[TMP_REG_1], dst_reg, 8, 16, 23));
				/* Rotate 8 bits right & insert LSB to reg */
				EMIT(PPC_RAW_RLWIMI(b2p[TMP_REG_1], dst_reg, 24, 24, 31));
				/* Move result back to dst_reg */
				EMIT(PPC_RAW_MR(dst_reg, b2p[TMP_REG_1]));
				अवरोध;
			हाल 32:
				/*
				 * Rotate word left by 8 bits:
				 * 2 bytes are alपढ़ोy in their final position
				 * -- byte 2 and 4 (of bytes 1, 2, 3 and 4)
				 */
				EMIT(PPC_RAW_RLWINM(b2p[TMP_REG_1], dst_reg, 8, 0, 31));
				/* Rotate 24 bits and insert byte 1 */
				EMIT(PPC_RAW_RLWIMI(b2p[TMP_REG_1], dst_reg, 24, 0, 7));
				/* Rotate 24 bits and insert byte 3 */
				EMIT(PPC_RAW_RLWIMI(b2p[TMP_REG_1], dst_reg, 24, 16, 23));
				EMIT(PPC_RAW_MR(dst_reg, b2p[TMP_REG_1]));
				अवरोध;
			हाल 64:
				/*
				 * Way easier and faster(?) to store the value
				 * पूर्णांकo stack and then use ldbrx
				 *
				 * ctx->seen will be reliable in pass2, but
				 * the inकाष्ठाions generated will reमुख्य the
				 * same across all passes
				 */
				PPC_BPF_STL(dst_reg, 1, bpf_jit_stack_local(ctx));
				EMIT(PPC_RAW_ADDI(b2p[TMP_REG_1], 1, bpf_jit_stack_local(ctx)));
				EMIT(PPC_RAW_LDBRX(dst_reg, 0, b2p[TMP_REG_1]));
				अवरोध;
			पूर्ण
			अवरोध;

emit_clear:
			चयन (imm) अणु
			हाल 16:
				/* zero-extend 16 bits पूर्णांकo 64 bits */
				EMIT(PPC_RAW_RLDICL(dst_reg, dst_reg, 0, 48));
				अगर (insn_is_zext(&insn[i + 1]))
					addrs[++i] = ctx->idx * 4;
				अवरोध;
			हाल 32:
				अगर (!fp->aux->verअगरier_zext)
					/* zero-extend 32 bits पूर्णांकo 64 bits */
					EMIT(PPC_RAW_RLDICL(dst_reg, dst_reg, 0, 32));
				अवरोध;
			हाल 64:
				/* nop */
				अवरोध;
			पूर्ण
			अवरोध;

		/*
		 * BPF_ST(X)
		 */
		हाल BPF_STX | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = src */
		हाल BPF_ST | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = imm */
			अगर (BPF_CLASS(code) == BPF_ST) अणु
				EMIT(PPC_RAW_LI(b2p[TMP_REG_1], imm));
				src_reg = b2p[TMP_REG_1];
			पूर्ण
			EMIT(PPC_RAW_STB(src_reg, dst_reg, off));
			अवरोध;
		हाल BPF_STX | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = src */
		हाल BPF_ST | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = imm */
			अगर (BPF_CLASS(code) == BPF_ST) अणु
				EMIT(PPC_RAW_LI(b2p[TMP_REG_1], imm));
				src_reg = b2p[TMP_REG_1];
			पूर्ण
			EMIT(PPC_RAW_STH(src_reg, dst_reg, off));
			अवरोध;
		हाल BPF_STX | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = src */
		हाल BPF_ST | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = imm */
			अगर (BPF_CLASS(code) == BPF_ST) अणु
				PPC_LI32(b2p[TMP_REG_1], imm);
				src_reg = b2p[TMP_REG_1];
			पूर्ण
			EMIT(PPC_RAW_STW(src_reg, dst_reg, off));
			अवरोध;
		हाल BPF_STX | BPF_MEM | BPF_DW: /* (u64 *)(dst + off) = src */
		हाल BPF_ST | BPF_MEM | BPF_DW: /* *(u64 *)(dst + off) = imm */
			अगर (BPF_CLASS(code) == BPF_ST) अणु
				PPC_LI32(b2p[TMP_REG_1], imm);
				src_reg = b2p[TMP_REG_1];
			पूर्ण
			PPC_BPF_STL(src_reg, dst_reg, off);
			अवरोध;

		/*
		 * BPF_STX ATOMIC (atomic ops)
		 */
		हाल BPF_STX | BPF_ATOMIC | BPF_W:
			अगर (insn->imm != BPF_ADD) अणु
				pr_err_ratelimited(
					"eBPF filter atomic op code %02x (@%d) unsupported\n",
					code, i);
				वापस -ENOTSUPP;
			पूर्ण

			/* *(u32 *)(dst + off) += src */

			/* Get EA पूर्णांकo TMP_REG_1 */
			EMIT(PPC_RAW_ADDI(b2p[TMP_REG_1], dst_reg, off));
			पंचांगp_idx = ctx->idx * 4;
			/* load value from memory पूर्णांकo TMP_REG_2 */
			EMIT(PPC_RAW_LWARX(b2p[TMP_REG_2], 0, b2p[TMP_REG_1], 0));
			/* add value from src_reg पूर्णांकo this */
			EMIT(PPC_RAW_ADD(b2p[TMP_REG_2], b2p[TMP_REG_2], src_reg));
			/* store result back */
			EMIT(PPC_RAW_STWCX(b2p[TMP_REG_2], 0, b2p[TMP_REG_1]));
			/* we're करोne अगर this succeeded */
			PPC_BCC_SHORT(COND_NE, पंचांगp_idx);
			अवरोध;
		हाल BPF_STX | BPF_ATOMIC | BPF_DW:
			अगर (insn->imm != BPF_ADD) अणु
				pr_err_ratelimited(
					"eBPF filter atomic op code %02x (@%d) unsupported\n",
					code, i);
				वापस -ENOTSUPP;
			पूर्ण
			/* *(u64 *)(dst + off) += src */

			EMIT(PPC_RAW_ADDI(b2p[TMP_REG_1], dst_reg, off));
			पंचांगp_idx = ctx->idx * 4;
			EMIT(PPC_RAW_LDARX(b2p[TMP_REG_2], 0, b2p[TMP_REG_1], 0));
			EMIT(PPC_RAW_ADD(b2p[TMP_REG_2], b2p[TMP_REG_2], src_reg));
			EMIT(PPC_RAW_STDCX(b2p[TMP_REG_2], 0, b2p[TMP_REG_1]));
			PPC_BCC_SHORT(COND_NE, पंचांगp_idx);
			अवरोध;

		/*
		 * BPF_LDX
		 */
		/* dst = *(u8 *)(ul) (src + off) */
		हाल BPF_LDX | BPF_MEM | BPF_B:
			EMIT(PPC_RAW_LBZ(dst_reg, src_reg, off));
			अगर (insn_is_zext(&insn[i + 1]))
				addrs[++i] = ctx->idx * 4;
			अवरोध;
		/* dst = *(u16 *)(ul) (src + off) */
		हाल BPF_LDX | BPF_MEM | BPF_H:
			EMIT(PPC_RAW_LHZ(dst_reg, src_reg, off));
			अगर (insn_is_zext(&insn[i + 1]))
				addrs[++i] = ctx->idx * 4;
			अवरोध;
		/* dst = *(u32 *)(ul) (src + off) */
		हाल BPF_LDX | BPF_MEM | BPF_W:
			EMIT(PPC_RAW_LWZ(dst_reg, src_reg, off));
			अगर (insn_is_zext(&insn[i + 1]))
				addrs[++i] = ctx->idx * 4;
			अवरोध;
		/* dst = *(u64 *)(ul) (src + off) */
		हाल BPF_LDX | BPF_MEM | BPF_DW:
			PPC_BPF_LL(dst_reg, src_reg, off);
			अवरोध;

		/*
		 * Doubleword load
		 * 16 byte inकाष्ठाion that uses two 'struct bpf_insn'
		 */
		हाल BPF_LD | BPF_IMM | BPF_DW: /* dst = (u64) imm */
			imm64 = ((u64)(u32) insn[i].imm) |
				    (((u64)(u32) insn[i+1].imm) << 32);
			/* Adjust क्रम two bpf inकाष्ठाions */
			addrs[++i] = ctx->idx * 4;
			PPC_LI64(dst_reg, imm64);
			अवरोध;

		/*
		 * Return/Exit
		 */
		हाल BPF_JMP | BPF_EXIT:
			/*
			 * If this isn't the very last inकाष्ठाion, branch to
			 * the epilogue. If we _are_ the last inकाष्ठाion,
			 * we'll just fall through to the epilogue.
			 */
			अगर (i != flen - 1)
				PPC_JMP(निकास_addr);
			/* अन्यथा fall through to the epilogue */
			अवरोध;

		/*
		 * Call kernel helper or bpf function
		 */
		हाल BPF_JMP | BPF_CALL:
			ctx->seen |= SEEN_FUNC;

			ret = bpf_jit_get_func_addr(fp, &insn[i], extra_pass,
						    &func_addr, &func_addr_fixed);
			अगर (ret < 0)
				वापस ret;

			अगर (func_addr_fixed)
				bpf_jit_emit_func_call_hlp(image, ctx, func_addr);
			अन्यथा
				bpf_jit_emit_func_call_rel(image, ctx, func_addr);
			/* move वापस value from r3 to BPF_REG_0 */
			EMIT(PPC_RAW_MR(b2p[BPF_REG_0], 3));
			अवरोध;

		/*
		 * Jumps and branches
		 */
		हाल BPF_JMP | BPF_JA:
			PPC_JMP(addrs[i + 1 + off]);
			अवरोध;

		हाल BPF_JMP | BPF_JGT | BPF_K:
		हाल BPF_JMP | BPF_JGT | BPF_X:
		हाल BPF_JMP | BPF_JSGT | BPF_K:
		हाल BPF_JMP | BPF_JSGT | BPF_X:
		हाल BPF_JMP32 | BPF_JGT | BPF_K:
		हाल BPF_JMP32 | BPF_JGT | BPF_X:
		हाल BPF_JMP32 | BPF_JSGT | BPF_K:
		हाल BPF_JMP32 | BPF_JSGT | BPF_X:
			true_cond = COND_GT;
			जाओ cond_branch;
		हाल BPF_JMP | BPF_JLT | BPF_K:
		हाल BPF_JMP | BPF_JLT | BPF_X:
		हाल BPF_JMP | BPF_JSLT | BPF_K:
		हाल BPF_JMP | BPF_JSLT | BPF_X:
		हाल BPF_JMP32 | BPF_JLT | BPF_K:
		हाल BPF_JMP32 | BPF_JLT | BPF_X:
		हाल BPF_JMP32 | BPF_JSLT | BPF_K:
		हाल BPF_JMP32 | BPF_JSLT | BPF_X:
			true_cond = COND_LT;
			जाओ cond_branch;
		हाल BPF_JMP | BPF_JGE | BPF_K:
		हाल BPF_JMP | BPF_JGE | BPF_X:
		हाल BPF_JMP | BPF_JSGE | BPF_K:
		हाल BPF_JMP | BPF_JSGE | BPF_X:
		हाल BPF_JMP32 | BPF_JGE | BPF_K:
		हाल BPF_JMP32 | BPF_JGE | BPF_X:
		हाल BPF_JMP32 | BPF_JSGE | BPF_K:
		हाल BPF_JMP32 | BPF_JSGE | BPF_X:
			true_cond = COND_GE;
			जाओ cond_branch;
		हाल BPF_JMP | BPF_JLE | BPF_K:
		हाल BPF_JMP | BPF_JLE | BPF_X:
		हाल BPF_JMP | BPF_JSLE | BPF_K:
		हाल BPF_JMP | BPF_JSLE | BPF_X:
		हाल BPF_JMP32 | BPF_JLE | BPF_K:
		हाल BPF_JMP32 | BPF_JLE | BPF_X:
		हाल BPF_JMP32 | BPF_JSLE | BPF_K:
		हाल BPF_JMP32 | BPF_JSLE | BPF_X:
			true_cond = COND_LE;
			जाओ cond_branch;
		हाल BPF_JMP | BPF_JEQ | BPF_K:
		हाल BPF_JMP | BPF_JEQ | BPF_X:
		हाल BPF_JMP32 | BPF_JEQ | BPF_K:
		हाल BPF_JMP32 | BPF_JEQ | BPF_X:
			true_cond = COND_EQ;
			जाओ cond_branch;
		हाल BPF_JMP | BPF_JNE | BPF_K:
		हाल BPF_JMP | BPF_JNE | BPF_X:
		हाल BPF_JMP32 | BPF_JNE | BPF_K:
		हाल BPF_JMP32 | BPF_JNE | BPF_X:
			true_cond = COND_NE;
			जाओ cond_branch;
		हाल BPF_JMP | BPF_JSET | BPF_K:
		हाल BPF_JMP | BPF_JSET | BPF_X:
		हाल BPF_JMP32 | BPF_JSET | BPF_K:
		हाल BPF_JMP32 | BPF_JSET | BPF_X:
			true_cond = COND_NE;
			/* Fall through */

cond_branch:
			चयन (code) अणु
			हाल BPF_JMP | BPF_JGT | BPF_X:
			हाल BPF_JMP | BPF_JLT | BPF_X:
			हाल BPF_JMP | BPF_JGE | BPF_X:
			हाल BPF_JMP | BPF_JLE | BPF_X:
			हाल BPF_JMP | BPF_JEQ | BPF_X:
			हाल BPF_JMP | BPF_JNE | BPF_X:
			हाल BPF_JMP32 | BPF_JGT | BPF_X:
			हाल BPF_JMP32 | BPF_JLT | BPF_X:
			हाल BPF_JMP32 | BPF_JGE | BPF_X:
			हाल BPF_JMP32 | BPF_JLE | BPF_X:
			हाल BPF_JMP32 | BPF_JEQ | BPF_X:
			हाल BPF_JMP32 | BPF_JNE | BPF_X:
				/* अचिन्हित comparison */
				अगर (BPF_CLASS(code) == BPF_JMP32)
					EMIT(PPC_RAW_CMPLW(dst_reg, src_reg));
				अन्यथा
					EMIT(PPC_RAW_CMPLD(dst_reg, src_reg));
				अवरोध;
			हाल BPF_JMP | BPF_JSGT | BPF_X:
			हाल BPF_JMP | BPF_JSLT | BPF_X:
			हाल BPF_JMP | BPF_JSGE | BPF_X:
			हाल BPF_JMP | BPF_JSLE | BPF_X:
			हाल BPF_JMP32 | BPF_JSGT | BPF_X:
			हाल BPF_JMP32 | BPF_JSLT | BPF_X:
			हाल BPF_JMP32 | BPF_JSGE | BPF_X:
			हाल BPF_JMP32 | BPF_JSLE | BPF_X:
				/* चिन्हित comparison */
				अगर (BPF_CLASS(code) == BPF_JMP32)
					EMIT(PPC_RAW_CMPW(dst_reg, src_reg));
				अन्यथा
					EMIT(PPC_RAW_CMPD(dst_reg, src_reg));
				अवरोध;
			हाल BPF_JMP | BPF_JSET | BPF_X:
			हाल BPF_JMP32 | BPF_JSET | BPF_X:
				अगर (BPF_CLASS(code) == BPF_JMP) अणु
					EMIT(PPC_RAW_AND_DOT(b2p[TMP_REG_1], dst_reg,
						    src_reg));
				पूर्ण अन्यथा अणु
					पूर्णांक पंचांगp_reg = b2p[TMP_REG_1];

					EMIT(PPC_RAW_AND(पंचांगp_reg, dst_reg, src_reg));
					EMIT(PPC_RAW_RLWINM_DOT(पंचांगp_reg, पंचांगp_reg, 0, 0,
						       31));
				पूर्ण
				अवरोध;
			हाल BPF_JMP | BPF_JNE | BPF_K:
			हाल BPF_JMP | BPF_JEQ | BPF_K:
			हाल BPF_JMP | BPF_JGT | BPF_K:
			हाल BPF_JMP | BPF_JLT | BPF_K:
			हाल BPF_JMP | BPF_JGE | BPF_K:
			हाल BPF_JMP | BPF_JLE | BPF_K:
			हाल BPF_JMP32 | BPF_JNE | BPF_K:
			हाल BPF_JMP32 | BPF_JEQ | BPF_K:
			हाल BPF_JMP32 | BPF_JGT | BPF_K:
			हाल BPF_JMP32 | BPF_JLT | BPF_K:
			हाल BPF_JMP32 | BPF_JGE | BPF_K:
			हाल BPF_JMP32 | BPF_JLE | BPF_K:
			अणु
				bool is_jmp32 = BPF_CLASS(code) == BPF_JMP32;

				/*
				 * Need sign-extended load, so only positive
				 * values can be used as imm in cmpldi
				 */
				अगर (imm >= 0 && imm < 32768) अणु
					अगर (is_jmp32)
						EMIT(PPC_RAW_CMPLWI(dst_reg, imm));
					अन्यथा
						EMIT(PPC_RAW_CMPLDI(dst_reg, imm));
				पूर्ण अन्यथा अणु
					/* sign-extending load */
					PPC_LI32(b2p[TMP_REG_1], imm);
					/* ... but अचिन्हित comparison */
					अगर (is_jmp32)
						EMIT(PPC_RAW_CMPLW(dst_reg,
							  b2p[TMP_REG_1]));
					अन्यथा
						EMIT(PPC_RAW_CMPLD(dst_reg,
							  b2p[TMP_REG_1]));
				पूर्ण
				अवरोध;
			पूर्ण
			हाल BPF_JMP | BPF_JSGT | BPF_K:
			हाल BPF_JMP | BPF_JSLT | BPF_K:
			हाल BPF_JMP | BPF_JSGE | BPF_K:
			हाल BPF_JMP | BPF_JSLE | BPF_K:
			हाल BPF_JMP32 | BPF_JSGT | BPF_K:
			हाल BPF_JMP32 | BPF_JSLT | BPF_K:
			हाल BPF_JMP32 | BPF_JSGE | BPF_K:
			हाल BPF_JMP32 | BPF_JSLE | BPF_K:
			अणु
				bool is_jmp32 = BPF_CLASS(code) == BPF_JMP32;

				/*
				 * चिन्हित comparison, so any 16-bit value
				 * can be used in cmpdi
				 */
				अगर (imm >= -32768 && imm < 32768) अणु
					अगर (is_jmp32)
						EMIT(PPC_RAW_CMPWI(dst_reg, imm));
					अन्यथा
						EMIT(PPC_RAW_CMPDI(dst_reg, imm));
				पूर्ण अन्यथा अणु
					PPC_LI32(b2p[TMP_REG_1], imm);
					अगर (is_jmp32)
						EMIT(PPC_RAW_CMPW(dst_reg,
							 b2p[TMP_REG_1]));
					अन्यथा
						EMIT(PPC_RAW_CMPD(dst_reg,
							 b2p[TMP_REG_1]));
				पूर्ण
				अवरोध;
			पूर्ण
			हाल BPF_JMP | BPF_JSET | BPF_K:
			हाल BPF_JMP32 | BPF_JSET | BPF_K:
				/* andi करोes not sign-extend the immediate */
				अगर (imm >= 0 && imm < 32768)
					/* PPC_ANDI is _only/always_ करोt-क्रमm */
					EMIT(PPC_RAW_ANDI(b2p[TMP_REG_1], dst_reg, imm));
				अन्यथा अणु
					पूर्णांक पंचांगp_reg = b2p[TMP_REG_1];

					PPC_LI32(पंचांगp_reg, imm);
					अगर (BPF_CLASS(code) == BPF_JMP) अणु
						EMIT(PPC_RAW_AND_DOT(पंचांगp_reg, dst_reg,
							    पंचांगp_reg));
					पूर्ण अन्यथा अणु
						EMIT(PPC_RAW_AND(पंचांगp_reg, dst_reg,
							पंचांगp_reg));
						EMIT(PPC_RAW_RLWINM_DOT(पंचांगp_reg, पंचांगp_reg,
							       0, 0, 31));
					पूर्ण
				पूर्ण
				अवरोध;
			पूर्ण
			PPC_BCC(true_cond, addrs[i + 1 + off]);
			अवरोध;

		/*
		 * Tail call
		 */
		हाल BPF_JMP | BPF_TAIL_CALL:
			ctx->seen |= SEEN_TAILCALL;
			bpf_jit_emit_tail_call(image, ctx, addrs[i + 1]);
			अवरोध;

		शेष:
			/*
			 * The filter contains something cruel & unusual.
			 * We करोn't handle it, but also there shouldn't be
			 * anything missing from our list.
			 */
			pr_err_ratelimited("eBPF filter opcode %04x (@%d) unsupported\n",
					code, i);
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण

	/* Set end-of-body-code address क्रम निकास. */
	addrs[i] = ctx->idx * 4;

	वापस 0;
पूर्ण
