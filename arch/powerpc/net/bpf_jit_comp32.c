<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * eBPF JIT compiler क्रम PPC32
 *
 * Copyright 2020 Christophe Leroy <christophe.leroy@csgroup.eu>
 *		  CS GROUP France
 *
 * Based on PPC64 eBPF JIT compiler by Naveen N. Rao
 */
#समावेश <linux/moduleloader.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/यंत्र-compat.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <यंत्र/kprobes.h>
#समावेश <linux/bpf.h>

#समावेश "bpf_jit.h"

/*
 * Stack layout:
 *
 *		[	prev sp		] <-------------
 *		[   nv gpr save area	] 16 * 4	|
 * fp (r31) -->	[   ebpf stack space	] upto 512	|
 *		[     frame header	] 16		|
 * sp (r1) --->	[    stack poपूर्णांकer	] --------------
 */

/* क्रम gpr non अस्थिर रेजिस्टरs r17 to r31 (14) + tail call */
#घोषणा BPF_PPC_STACK_SAVE	(15 * 4 + 4)
/* stack frame, ensure this is quadword aligned */
#घोषणा BPF_PPC_STACKFRAME(ctx)	(STACK_FRAME_MIN_SIZE + BPF_PPC_STACK_SAVE + (ctx)->stack_size)

/* BPF रेजिस्टर usage */
#घोषणा TMP_REG	(MAX_BPF_JIT_REG + 0)

/* BPF to ppc रेजिस्टर mappings */
स्थिर पूर्णांक b2p[MAX_BPF_JIT_REG + 1] = अणु
	/* function वापस value */
	[BPF_REG_0] = 12,
	/* function arguments */
	[BPF_REG_1] = 4,
	[BPF_REG_2] = 6,
	[BPF_REG_3] = 8,
	[BPF_REG_4] = 10,
	[BPF_REG_5] = 22,
	/* non अस्थिर रेजिस्टरs */
	[BPF_REG_6] = 24,
	[BPF_REG_7] = 26,
	[BPF_REG_8] = 28,
	[BPF_REG_9] = 30,
	/* frame poपूर्णांकer aka BPF_REG_10 */
	[BPF_REG_FP] = 18,
	/* eBPF jit पूर्णांकernal रेजिस्टरs */
	[BPF_REG_AX] = 20,
	[TMP_REG] = 31,		/* 32 bits */
पूर्ण;

अटल पूर्णांक bpf_to_ppc(काष्ठा codegen_context *ctx, पूर्णांक reg)
अणु
	वापस ctx->b2p[reg];
पूर्ण

/* PPC NVR range -- update this अगर we ever use NVRs below r17 */
#घोषणा BPF_PPC_NVR_MIN		17
#घोषणा BPF_PPC_TC		16

अटल पूर्णांक bpf_jit_stack_दुरत्व(काष्ठा codegen_context *ctx, पूर्णांक reg)
अणु
	अगर ((reg >= BPF_PPC_NVR_MIN && reg < 32) || reg == BPF_PPC_TC)
		वापस BPF_PPC_STACKFRAME(ctx) - 4 * (32 - reg);

	WARN(true, "BPF JIT is asking about unknown registers, will crash the stack");
	/* Use the hole we have left क्रम alignment */
	वापस BPF_PPC_STACKFRAME(ctx) - 4;
पूर्ण

व्योम bpf_jit_पुनः_स्मृति_regs(काष्ठा codegen_context *ctx)
अणु
	अगर (ctx->seen & SEEN_FUNC)
		वापस;

	जबतक (ctx->seen & SEEN_NVREG_MASK &&
	      (ctx->seen & SEEN_VREG_MASK) != SEEN_VREG_MASK) अणु
		पूर्णांक old = 32 - fls(ctx->seen & (SEEN_NVREG_MASK & 0xaaaaaaab));
		पूर्णांक new = 32 - fls(~ctx->seen & (SEEN_VREG_MASK & 0xaaaaaaaa));
		पूर्णांक i;

		क्रम (i = BPF_REG_0; i <= TMP_REG; i++) अणु
			अगर (ctx->b2p[i] != old)
				जारी;
			ctx->b2p[i] = new;
			bpf_set_seen_रेजिस्टर(ctx, new);
			bpf_clear_seen_रेजिस्टर(ctx, old);
			अगर (i != TMP_REG) अणु
				bpf_set_seen_रेजिस्टर(ctx, new - 1);
				bpf_clear_seen_रेजिस्टर(ctx, old - 1);
			पूर्ण
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम bpf_jit_build_prologue(u32 *image, काष्ठा codegen_context *ctx)
अणु
	पूर्णांक i;

	/* First arg comes in as a 32 bits poपूर्णांकer. */
	EMIT(PPC_RAW_MR(bpf_to_ppc(ctx, BPF_REG_1), __REG_R3));
	EMIT(PPC_RAW_LI(bpf_to_ppc(ctx, BPF_REG_1) - 1, 0));
	EMIT(PPC_RAW_STWU(__REG_R1, __REG_R1, -BPF_PPC_STACKFRAME(ctx)));

	/*
	 * Initialize tail_call_cnt in stack frame अगर we करो tail calls.
	 * Otherwise, put in NOPs so that it can be skipped when we are
	 * invoked through a tail call.
	 */
	अगर (ctx->seen & SEEN_TAILCALL) अणु
		EMIT(PPC_RAW_STW(bpf_to_ppc(ctx, BPF_REG_1) - 1, __REG_R1, bpf_jit_stack_दुरत्व(ctx, BPF_PPC_TC)));
	पूर्ण अन्यथा अणु
		EMIT(PPC_RAW_NOP());
	पूर्ण

#घोषणा BPF_TAILCALL_PROLOGUE_SIZE	16

	/*
	 * We need a stack frame, but we करोn't necessarily need to
	 * save/restore LR unless we call other functions
	 */
	अगर (ctx->seen & SEEN_FUNC)
		EMIT(PPC_RAW_MFLR(__REG_R0));

	/*
	 * Back up non-अस्थिर regs -- रेजिस्टरs r18-r31
	 */
	क्रम (i = BPF_PPC_NVR_MIN; i <= 31; i++)
		अगर (bpf_is_seen_रेजिस्टर(ctx, i))
			EMIT(PPC_RAW_STW(i, __REG_R1, bpf_jit_stack_दुरत्व(ctx, i)));

	/* If needed retrieve arguments 9 and 10, ie 5th 64 bits arg.*/
	अगर (bpf_is_seen_रेजिस्टर(ctx, bpf_to_ppc(ctx, BPF_REG_5))) अणु
		EMIT(PPC_RAW_LWZ(bpf_to_ppc(ctx, BPF_REG_5) - 1, __REG_R1, BPF_PPC_STACKFRAME(ctx)) + 8);
		EMIT(PPC_RAW_LWZ(bpf_to_ppc(ctx, BPF_REG_5), __REG_R1, BPF_PPC_STACKFRAME(ctx)) + 12);
	पूर्ण

	/* Setup frame poपूर्णांकer to poपूर्णांक to the bpf stack area */
	अगर (bpf_is_seen_रेजिस्टर(ctx, bpf_to_ppc(ctx, BPF_REG_FP))) अणु
		EMIT(PPC_RAW_LI(bpf_to_ppc(ctx, BPF_REG_FP) - 1, 0));
		EMIT(PPC_RAW_ADDI(bpf_to_ppc(ctx, BPF_REG_FP), __REG_R1,
				  STACK_FRAME_MIN_SIZE + ctx->stack_size));
	पूर्ण

	अगर (ctx->seen & SEEN_FUNC)
		EMIT(PPC_RAW_STW(__REG_R0, __REG_R1, BPF_PPC_STACKFRAME(ctx) + PPC_LR_STKOFF));
पूर्ण

अटल व्योम bpf_jit_emit_common_epilogue(u32 *image, काष्ठा codegen_context *ctx)
अणु
	पूर्णांक i;

	/* Restore NVRs */
	क्रम (i = BPF_PPC_NVR_MIN; i <= 31; i++)
		अगर (bpf_is_seen_रेजिस्टर(ctx, i))
			EMIT(PPC_RAW_LWZ(i, __REG_R1, bpf_jit_stack_दुरत्व(ctx, i)));
पूर्ण

व्योम bpf_jit_build_epilogue(u32 *image, काष्ठा codegen_context *ctx)
अणु
	EMIT(PPC_RAW_MR(__REG_R3, bpf_to_ppc(ctx, BPF_REG_0)));

	bpf_jit_emit_common_epilogue(image, ctx);

	/* Tear करोwn our stack frame */

	अगर (ctx->seen & SEEN_FUNC)
		EMIT(PPC_RAW_LWZ(__REG_R0, __REG_R1, BPF_PPC_STACKFRAME(ctx) + PPC_LR_STKOFF));

	EMIT(PPC_RAW_ADDI(__REG_R1, __REG_R1, BPF_PPC_STACKFRAME(ctx)));

	अगर (ctx->seen & SEEN_FUNC)
		EMIT(PPC_RAW_MTLR(__REG_R0));

	EMIT(PPC_RAW_BLR());
पूर्ण

व्योम bpf_jit_emit_func_call_rel(u32 *image, काष्ठा codegen_context *ctx, u64 func)
अणु
	s32 rel = (s32)func - (s32)(image + ctx->idx);

	अगर (image && rel < 0x2000000 && rel >= -0x2000000) अणु
		PPC_BL_ABS(func);
	पूर्ण अन्यथा अणु
		/* Load function address पूर्णांकo r0 */
		EMIT(PPC_RAW_LIS(__REG_R0, IMM_H(func)));
		EMIT(PPC_RAW_ORI(__REG_R0, __REG_R0, IMM_L(func)));
		EMIT(PPC_RAW_MTLR(__REG_R0));
		EMIT(PPC_RAW_BLRL());
	पूर्ण
पूर्ण

अटल व्योम bpf_jit_emit_tail_call(u32 *image, काष्ठा codegen_context *ctx, u32 out)
अणु
	/*
	 * By now, the eBPF program has alपढ़ोy setup parameters in r3-r6
	 * r3-r4/BPF_REG_1 - poपूर्णांकer to ctx -- passed as is to the next bpf program
	 * r5-r6/BPF_REG_2 - poपूर्णांकer to bpf_array
	 * r7-r8/BPF_REG_3 - index in bpf_array
	 */
	पूर्णांक b2p_bpf_array = bpf_to_ppc(ctx, BPF_REG_2);
	पूर्णांक b2p_index = bpf_to_ppc(ctx, BPF_REG_3);

	/*
	 * अगर (index >= array->map.max_entries)
	 *   जाओ out;
	 */
	EMIT(PPC_RAW_LWZ(__REG_R0, b2p_bpf_array, दुरत्व(काष्ठा bpf_array, map.max_entries)));
	EMIT(PPC_RAW_CMPLW(b2p_index, __REG_R0));
	EMIT(PPC_RAW_LWZ(__REG_R0, __REG_R1, bpf_jit_stack_दुरत्व(ctx, BPF_PPC_TC)));
	PPC_BCC(COND_GE, out);

	/*
	 * अगर (tail_call_cnt > MAX_TAIL_CALL_CNT)
	 *   जाओ out;
	 */
	EMIT(PPC_RAW_CMPLWI(__REG_R0, MAX_TAIL_CALL_CNT));
	/* tail_call_cnt++; */
	EMIT(PPC_RAW_ADDIC(__REG_R0, __REG_R0, 1));
	PPC_BCC(COND_GT, out);

	/* prog = array->ptrs[index]; */
	EMIT(PPC_RAW_RLWINM(__REG_R3, b2p_index, 2, 0, 29));
	EMIT(PPC_RAW_ADD(__REG_R3, __REG_R3, b2p_bpf_array));
	EMIT(PPC_RAW_LWZ(__REG_R3, __REG_R3, दुरत्व(काष्ठा bpf_array, ptrs)));
	EMIT(PPC_RAW_STW(__REG_R0, __REG_R1, bpf_jit_stack_दुरत्व(ctx, BPF_PPC_TC)));

	/*
	 * अगर (prog == शून्य)
	 *   जाओ out;
	 */
	EMIT(PPC_RAW_CMPLWI(__REG_R3, 0));
	PPC_BCC(COND_EQ, out);

	/* जाओ *(prog->bpf_func + prologue_size); */
	EMIT(PPC_RAW_LWZ(__REG_R3, __REG_R3, दुरत्व(काष्ठा bpf_prog, bpf_func)));

	अगर (ctx->seen & SEEN_FUNC)
		EMIT(PPC_RAW_LWZ(__REG_R0, __REG_R1, BPF_PPC_STACKFRAME(ctx) + PPC_LR_STKOFF));

	EMIT(PPC_RAW_ADDIC(__REG_R3, __REG_R3, BPF_TAILCALL_PROLOGUE_SIZE));

	अगर (ctx->seen & SEEN_FUNC)
		EMIT(PPC_RAW_MTLR(__REG_R0));

	EMIT(PPC_RAW_MTCTR(__REG_R3));

	EMIT(PPC_RAW_MR(__REG_R3, bpf_to_ppc(ctx, BPF_REG_1)));

	/* tear restore NVRs, ... */
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
		u32 dst_reg = bpf_to_ppc(ctx, insn[i].dst_reg);
		u32 dst_reg_h = dst_reg - 1;
		u32 src_reg = bpf_to_ppc(ctx, insn[i].src_reg);
		u32 src_reg_h = src_reg - 1;
		u32 पंचांगp_reg = bpf_to_ppc(ctx, TMP_REG);
		s16 off = insn[i].off;
		s32 imm = insn[i].imm;
		bool func_addr_fixed;
		u64 func_addr;
		u32 true_cond;

		/*
		 * addrs[] maps a BPF bytecode address पूर्णांकo a real offset from
		 * the start of the body code.
		 */
		addrs[i] = ctx->idx * 4;

		/*
		 * As an optimization, we note करोwn which रेजिस्टरs
		 * are used so that we can only save/restore those in our
		 * prologue and epilogue. We करो this here regardless of whether
		 * the actual BPF inकाष्ठाion uses src/dst रेजिस्टरs or not
		 * (क्रम instance, BPF_CALL करोes not use them). The expectation
		 * is that those inकाष्ठाions will have src_reg/dst_reg set to
		 * 0. Even otherwise, we just lose some prologue/epilogue
		 * optimization but everything अन्यथा should work without
		 * any issues.
		 */
		अगर (dst_reg >= 3 && dst_reg < 32) अणु
			bpf_set_seen_रेजिस्टर(ctx, dst_reg);
			bpf_set_seen_रेजिस्टर(ctx, dst_reg_h);
		पूर्ण

		अगर (src_reg >= 3 && src_reg < 32) अणु
			bpf_set_seen_रेजिस्टर(ctx, src_reg);
			bpf_set_seen_रेजिस्टर(ctx, src_reg_h);
		पूर्ण

		चयन (code) अणु
		/*
		 * Arithmetic operations: ADD/SUB/MUL/DIV/MOD/NEG
		 */
		हाल BPF_ALU | BPF_ADD | BPF_X: /* (u32) dst += (u32) src */
			EMIT(PPC_RAW_ADD(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_ADD | BPF_X: /* dst += src */
			EMIT(PPC_RAW_ADDC(dst_reg, dst_reg, src_reg));
			EMIT(PPC_RAW_ADDE(dst_reg_h, dst_reg_h, src_reg_h));
			अवरोध;
		हाल BPF_ALU | BPF_SUB | BPF_X: /* (u32) dst -= (u32) src */
			EMIT(PPC_RAW_SUB(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_SUB | BPF_X: /* dst -= src */
			EMIT(PPC_RAW_SUBFC(dst_reg, src_reg, dst_reg));
			EMIT(PPC_RAW_SUBFE(dst_reg_h, src_reg_h, dst_reg_h));
			अवरोध;
		हाल BPF_ALU | BPF_SUB | BPF_K: /* (u32) dst -= (u32) imm */
			imm = -imm;
			fallthrough;
		हाल BPF_ALU | BPF_ADD | BPF_K: /* (u32) dst += (u32) imm */
			अगर (IMM_HA(imm) & 0xffff)
				EMIT(PPC_RAW_ADDIS(dst_reg, dst_reg, IMM_HA(imm)));
			अगर (IMM_L(imm))
				EMIT(PPC_RAW_ADDI(dst_reg, dst_reg, IMM_L(imm)));
			अवरोध;
		हाल BPF_ALU64 | BPF_SUB | BPF_K: /* dst -= imm */
			imm = -imm;
			fallthrough;
		हाल BPF_ALU64 | BPF_ADD | BPF_K: /* dst += imm */
			अगर (!imm)
				अवरोध;

			अगर (imm >= -32768 && imm < 32768) अणु
				EMIT(PPC_RAW_ADDIC(dst_reg, dst_reg, imm));
			पूर्ण अन्यथा अणु
				PPC_LI32(__REG_R0, imm);
				EMIT(PPC_RAW_ADDC(dst_reg, dst_reg, __REG_R0));
			पूर्ण
			अगर (imm >= 0)
				EMIT(PPC_RAW_ADDZE(dst_reg_h, dst_reg_h));
			अन्यथा
				EMIT(PPC_RAW_ADDME(dst_reg_h, dst_reg_h));
			अवरोध;
		हाल BPF_ALU64 | BPF_MUL | BPF_X: /* dst *= src */
			bpf_set_seen_रेजिस्टर(ctx, पंचांगp_reg);
			EMIT(PPC_RAW_MULW(__REG_R0, dst_reg, src_reg_h));
			EMIT(PPC_RAW_MULW(dst_reg_h, dst_reg_h, src_reg));
			EMIT(PPC_RAW_MULHWU(पंचांगp_reg, dst_reg, src_reg));
			EMIT(PPC_RAW_MULW(dst_reg, dst_reg, src_reg));
			EMIT(PPC_RAW_ADD(dst_reg_h, dst_reg_h, __REG_R0));
			EMIT(PPC_RAW_ADD(dst_reg_h, dst_reg_h, पंचांगp_reg));
			अवरोध;
		हाल BPF_ALU | BPF_MUL | BPF_X: /* (u32) dst *= (u32) src */
			EMIT(PPC_RAW_MULW(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU | BPF_MUL | BPF_K: /* (u32) dst *= (u32) imm */
			अगर (imm >= -32768 && imm < 32768) अणु
				EMIT(PPC_RAW_MULI(dst_reg, dst_reg, imm));
			पूर्ण अन्यथा अणु
				PPC_LI32(__REG_R0, imm);
				EMIT(PPC_RAW_MULW(dst_reg, dst_reg, __REG_R0));
			पूर्ण
			अवरोध;
		हाल BPF_ALU64 | BPF_MUL | BPF_K: /* dst *= imm */
			अगर (!imm) अणु
				PPC_LI32(dst_reg, 0);
				PPC_LI32(dst_reg_h, 0);
				अवरोध;
			पूर्ण
			अगर (imm == 1)
				अवरोध;
			अगर (imm == -1) अणु
				EMIT(PPC_RAW_SUBFIC(dst_reg, dst_reg, 0));
				EMIT(PPC_RAW_SUBFZE(dst_reg_h, dst_reg_h));
				अवरोध;
			पूर्ण
			bpf_set_seen_रेजिस्टर(ctx, पंचांगp_reg);
			PPC_LI32(पंचांगp_reg, imm);
			EMIT(PPC_RAW_MULW(dst_reg_h, dst_reg_h, पंचांगp_reg));
			अगर (imm < 0)
				EMIT(PPC_RAW_SUB(dst_reg_h, dst_reg_h, dst_reg));
			EMIT(PPC_RAW_MULHWU(__REG_R0, dst_reg, पंचांगp_reg));
			EMIT(PPC_RAW_MULW(dst_reg, dst_reg, पंचांगp_reg));
			EMIT(PPC_RAW_ADD(dst_reg_h, dst_reg_h, __REG_R0));
			अवरोध;
		हाल BPF_ALU | BPF_DIV | BPF_X: /* (u32) dst /= (u32) src */
			EMIT(PPC_RAW_DIVWU(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU | BPF_MOD | BPF_X: /* (u32) dst %= (u32) src */
			EMIT(PPC_RAW_DIVWU(__REG_R0, dst_reg, src_reg));
			EMIT(PPC_RAW_MULW(__REG_R0, src_reg, __REG_R0));
			EMIT(PPC_RAW_SUB(dst_reg, dst_reg, __REG_R0));
			अवरोध;
		हाल BPF_ALU64 | BPF_DIV | BPF_X: /* dst /= src */
			वापस -EOPNOTSUPP;
		हाल BPF_ALU64 | BPF_MOD | BPF_X: /* dst %= src */
			वापस -EOPNOTSUPP;
		हाल BPF_ALU | BPF_DIV | BPF_K: /* (u32) dst /= (u32) imm */
			अगर (!imm)
				वापस -EINVAL;
			अगर (imm == 1)
				अवरोध;

			PPC_LI32(__REG_R0, imm);
			EMIT(PPC_RAW_DIVWU(dst_reg, dst_reg, __REG_R0));
			अवरोध;
		हाल BPF_ALU | BPF_MOD | BPF_K: /* (u32) dst %= (u32) imm */
			अगर (!imm)
				वापस -EINVAL;

			अगर (!is_घातer_of_2((u32)imm)) अणु
				bpf_set_seen_रेजिस्टर(ctx, पंचांगp_reg);
				PPC_LI32(पंचांगp_reg, imm);
				EMIT(PPC_RAW_DIVWU(__REG_R0, dst_reg, पंचांगp_reg));
				EMIT(PPC_RAW_MULW(__REG_R0, पंचांगp_reg, __REG_R0));
				EMIT(PPC_RAW_SUB(dst_reg, dst_reg, __REG_R0));
				अवरोध;
			पूर्ण
			अगर (imm == 1)
				EMIT(PPC_RAW_LI(dst_reg, 0));
			अन्यथा
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 0, 32 - ilog2((u32)imm), 31));

			अवरोध;
		हाल BPF_ALU64 | BPF_MOD | BPF_K: /* dst %= imm */
			अगर (!imm)
				वापस -EINVAL;
			अगर (imm < 0)
				imm = -imm;
			अगर (!is_घातer_of_2(imm))
				वापस -EOPNOTSUPP;
			अगर (imm == 1)
				EMIT(PPC_RAW_LI(dst_reg, 0));
			अन्यथा
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 0, 32 - ilog2(imm), 31));
			EMIT(PPC_RAW_LI(dst_reg_h, 0));
			अवरोध;
		हाल BPF_ALU64 | BPF_DIV | BPF_K: /* dst /= imm */
			अगर (!imm)
				वापस -EINVAL;
			अगर (!is_घातer_of_2(असल(imm)))
				वापस -EOPNOTSUPP;

			अगर (imm < 0) अणु
				EMIT(PPC_RAW_SUBFIC(dst_reg, dst_reg, 0));
				EMIT(PPC_RAW_SUBFZE(dst_reg_h, dst_reg_h));
				imm = -imm;
			पूर्ण
			अगर (imm == 1)
				अवरोध;
			imm = ilog2(imm);
			EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 32 - imm, imm, 31));
			EMIT(PPC_RAW_RLWIMI(dst_reg, dst_reg_h, 32 - imm, 0, imm - 1));
			EMIT(PPC_RAW_SRAWI(dst_reg_h, dst_reg_h, imm));
			अवरोध;
		हाल BPF_ALU | BPF_NEG: /* (u32) dst = -dst */
			EMIT(PPC_RAW_NEG(dst_reg, dst_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_NEG: /* dst = -dst */
			EMIT(PPC_RAW_SUBFIC(dst_reg, dst_reg, 0));
			EMIT(PPC_RAW_SUBFZE(dst_reg_h, dst_reg_h));
			अवरोध;

		/*
		 * Logical operations: AND/OR/XOR/[A]LSH/[A]RSH
		 */
		हाल BPF_ALU64 | BPF_AND | BPF_X: /* dst = dst & src */
			EMIT(PPC_RAW_AND(dst_reg, dst_reg, src_reg));
			EMIT(PPC_RAW_AND(dst_reg_h, dst_reg_h, src_reg_h));
			अवरोध;
		हाल BPF_ALU | BPF_AND | BPF_X: /* (u32) dst = dst & src */
			EMIT(PPC_RAW_AND(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_AND | BPF_K: /* dst = dst & imm */
			अगर (imm >= 0)
				EMIT(PPC_RAW_LI(dst_reg_h, 0));
			fallthrough;
		हाल BPF_ALU | BPF_AND | BPF_K: /* (u32) dst = dst & imm */
			अगर (!IMM_H(imm)) अणु
				EMIT(PPC_RAW_ANDI(dst_reg, dst_reg, IMM_L(imm)));
			पूर्ण अन्यथा अगर (!IMM_L(imm)) अणु
				EMIT(PPC_RAW_ANDIS(dst_reg, dst_reg, IMM_H(imm)));
			पूर्ण अन्यथा अगर (imm == (((1 << fls(imm)) - 1) ^ ((1 << (ffs(i) - 1)) - 1))) अणु
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 0,
						    32 - fls(imm), 32 - ffs(imm)));
			पूर्ण अन्यथा अणु
				PPC_LI32(__REG_R0, imm);
				EMIT(PPC_RAW_AND(dst_reg, dst_reg, __REG_R0));
			पूर्ण
			अवरोध;
		हाल BPF_ALU64 | BPF_OR | BPF_X: /* dst = dst | src */
			EMIT(PPC_RAW_OR(dst_reg, dst_reg, src_reg));
			EMIT(PPC_RAW_OR(dst_reg_h, dst_reg_h, src_reg_h));
			अवरोध;
		हाल BPF_ALU | BPF_OR | BPF_X: /* dst = (u32) dst | (u32) src */
			EMIT(PPC_RAW_OR(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_OR | BPF_K:/* dst = dst | imm */
			/* Sign-extended */
			अगर (imm < 0)
				EMIT(PPC_RAW_LI(dst_reg_h, -1));
			fallthrough;
		हाल BPF_ALU | BPF_OR | BPF_K:/* dst = (u32) dst | (u32) imm */
			अगर (IMM_L(imm))
				EMIT(PPC_RAW_ORI(dst_reg, dst_reg, IMM_L(imm)));
			अगर (IMM_H(imm))
				EMIT(PPC_RAW_ORIS(dst_reg, dst_reg, IMM_H(imm)));
			अवरोध;
		हाल BPF_ALU64 | BPF_XOR | BPF_X: /* dst ^= src */
			अगर (dst_reg == src_reg) अणु
				EMIT(PPC_RAW_LI(dst_reg, 0));
				EMIT(PPC_RAW_LI(dst_reg_h, 0));
			पूर्ण अन्यथा अणु
				EMIT(PPC_RAW_XOR(dst_reg, dst_reg, src_reg));
				EMIT(PPC_RAW_XOR(dst_reg_h, dst_reg_h, src_reg_h));
			पूर्ण
			अवरोध;
		हाल BPF_ALU | BPF_XOR | BPF_X: /* (u32) dst ^= src */
			अगर (dst_reg == src_reg)
				EMIT(PPC_RAW_LI(dst_reg, 0));
			अन्यथा
				EMIT(PPC_RAW_XOR(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_XOR | BPF_K: /* dst ^= imm */
			अगर (imm < 0)
				EMIT(PPC_RAW_NOR(dst_reg_h, dst_reg_h, dst_reg_h));
			fallthrough;
		हाल BPF_ALU | BPF_XOR | BPF_K: /* (u32) dst ^= (u32) imm */
			अगर (IMM_L(imm))
				EMIT(PPC_RAW_XORI(dst_reg, dst_reg, IMM_L(imm)));
			अगर (IMM_H(imm))
				EMIT(PPC_RAW_XORIS(dst_reg, dst_reg, IMM_H(imm)));
			अवरोध;
		हाल BPF_ALU | BPF_LSH | BPF_X: /* (u32) dst <<= (u32) src */
			EMIT(PPC_RAW_SLW(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_LSH | BPF_X: /* dst <<= src; */
			bpf_set_seen_रेजिस्टर(ctx, पंचांगp_reg);
			EMIT(PPC_RAW_SUBFIC(__REG_R0, src_reg, 32));
			EMIT(PPC_RAW_SLW(dst_reg_h, dst_reg_h, src_reg));
			EMIT(PPC_RAW_ADDI(पंचांगp_reg, src_reg, 32));
			EMIT(PPC_RAW_SRW(__REG_R0, dst_reg, __REG_R0));
			EMIT(PPC_RAW_SLW(पंचांगp_reg, dst_reg, पंचांगp_reg));
			EMIT(PPC_RAW_OR(dst_reg_h, dst_reg_h, __REG_R0));
			EMIT(PPC_RAW_SLW(dst_reg, dst_reg, src_reg));
			EMIT(PPC_RAW_OR(dst_reg_h, dst_reg_h, पंचांगp_reg));
			अवरोध;
		हाल BPF_ALU | BPF_LSH | BPF_K: /* (u32) dst <<= (u32) imm */
			अगर (!imm)
				अवरोध;
			EMIT(PPC_RAW_SLWI(dst_reg, dst_reg, imm));
			अवरोध;
		हाल BPF_ALU64 | BPF_LSH | BPF_K: /* dst <<= imm */
			अगर (imm < 0)
				वापस -EINVAL;
			अगर (!imm)
				अवरोध;
			अगर (imm < 32) अणु
				EMIT(PPC_RAW_RLWINM(dst_reg_h, dst_reg_h, imm, 0, 31 - imm));
				EMIT(PPC_RAW_RLWIMI(dst_reg_h, dst_reg, imm, 32 - imm, 31));
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, imm, 0, 31 - imm));
				अवरोध;
			पूर्ण
			अगर (imm < 64)
				EMIT(PPC_RAW_RLWINM(dst_reg_h, dst_reg, imm, 0, 31 - imm));
			अन्यथा
				EMIT(PPC_RAW_LI(dst_reg_h, 0));
			EMIT(PPC_RAW_LI(dst_reg, 0));
			अवरोध;
		हाल BPF_ALU | BPF_RSH | BPF_X: /* (u32) dst >>= (u32) src */
			EMIT(PPC_RAW_SRW(dst_reg, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_RSH | BPF_X: /* dst >>= src */
			bpf_set_seen_रेजिस्टर(ctx, पंचांगp_reg);
			EMIT(PPC_RAW_SUBFIC(__REG_R0, src_reg, 32));
			EMIT(PPC_RAW_SRW(dst_reg, dst_reg, src_reg));
			EMIT(PPC_RAW_ADDI(पंचांगp_reg, src_reg, 32));
			EMIT(PPC_RAW_SLW(__REG_R0, dst_reg_h, __REG_R0));
			EMIT(PPC_RAW_SRW(पंचांगp_reg, dst_reg_h, पंचांगp_reg));
			EMIT(PPC_RAW_OR(dst_reg, dst_reg, __REG_R0));
			EMIT(PPC_RAW_SRW(dst_reg_h, dst_reg_h, src_reg));
			EMIT(PPC_RAW_OR(dst_reg, dst_reg, पंचांगp_reg));
			अवरोध;
		हाल BPF_ALU | BPF_RSH | BPF_K: /* (u32) dst >>= (u32) imm */
			अगर (!imm)
				अवरोध;
			EMIT(PPC_RAW_SRWI(dst_reg, dst_reg, imm));
			अवरोध;
		हाल BPF_ALU64 | BPF_RSH | BPF_K: /* dst >>= imm */
			अगर (imm < 0)
				वापस -EINVAL;
			अगर (!imm)
				अवरोध;
			अगर (imm < 32) अणु
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 32 - imm, imm, 31));
				EMIT(PPC_RAW_RLWIMI(dst_reg, dst_reg_h, 32 - imm, 0, imm - 1));
				EMIT(PPC_RAW_RLWINM(dst_reg_h, dst_reg_h, 32 - imm, imm, 31));
				अवरोध;
			पूर्ण
			अगर (imm < 64)
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg_h, 64 - imm, imm - 32, 31));
			अन्यथा
				EMIT(PPC_RAW_LI(dst_reg, 0));
			EMIT(PPC_RAW_LI(dst_reg_h, 0));
			अवरोध;
		हाल BPF_ALU | BPF_ARSH | BPF_X: /* (s32) dst >>= src */
			EMIT(PPC_RAW_SRAW(dst_reg_h, dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_ARSH | BPF_X: /* (s64) dst >>= src */
			bpf_set_seen_रेजिस्टर(ctx, पंचांगp_reg);
			EMIT(PPC_RAW_SUBFIC(__REG_R0, src_reg, 32));
			EMIT(PPC_RAW_SRW(dst_reg, dst_reg, src_reg));
			EMIT(PPC_RAW_SLW(__REG_R0, dst_reg_h, __REG_R0));
			EMIT(PPC_RAW_ADDI(पंचांगp_reg, src_reg, 32));
			EMIT(PPC_RAW_OR(dst_reg, dst_reg, __REG_R0));
			EMIT(PPC_RAW_RLWINM(__REG_R0, पंचांगp_reg, 0, 26, 26));
			EMIT(PPC_RAW_SRAW(पंचांगp_reg, dst_reg_h, पंचांगp_reg));
			EMIT(PPC_RAW_SRAW(dst_reg_h, dst_reg_h, src_reg));
			EMIT(PPC_RAW_SLW(पंचांगp_reg, पंचांगp_reg, __REG_R0));
			EMIT(PPC_RAW_OR(dst_reg, dst_reg, पंचांगp_reg));
			अवरोध;
		हाल BPF_ALU | BPF_ARSH | BPF_K: /* (s32) dst >>= imm */
			अगर (!imm)
				अवरोध;
			EMIT(PPC_RAW_SRAWI(dst_reg, dst_reg, imm));
			अवरोध;
		हाल BPF_ALU64 | BPF_ARSH | BPF_K: /* (s64) dst >>= imm */
			अगर (imm < 0)
				वापस -EINVAL;
			अगर (!imm)
				अवरोध;
			अगर (imm < 32) अणु
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 32 - imm, imm, 31));
				EMIT(PPC_RAW_RLWIMI(dst_reg, dst_reg_h, 32 - imm, 0, imm - 1));
				EMIT(PPC_RAW_SRAWI(dst_reg_h, dst_reg_h, imm));
				अवरोध;
			पूर्ण
			अगर (imm < 64)
				EMIT(PPC_RAW_SRAWI(dst_reg, dst_reg_h, imm - 32));
			अन्यथा
				EMIT(PPC_RAW_SRAWI(dst_reg, dst_reg_h, 31));
			EMIT(PPC_RAW_SRAWI(dst_reg_h, dst_reg_h, 31));
			अवरोध;

		/*
		 * MOV
		 */
		हाल BPF_ALU64 | BPF_MOV | BPF_X: /* dst = src */
			अगर (dst_reg == src_reg)
				अवरोध;
			EMIT(PPC_RAW_MR(dst_reg, src_reg));
			EMIT(PPC_RAW_MR(dst_reg_h, src_reg_h));
			अवरोध;
		हाल BPF_ALU | BPF_MOV | BPF_X: /* (u32) dst = src */
			/* special mov32 क्रम zext */
			अगर (imm == 1)
				EMIT(PPC_RAW_LI(dst_reg_h, 0));
			अन्यथा अगर (dst_reg != src_reg)
				EMIT(PPC_RAW_MR(dst_reg, src_reg));
			अवरोध;
		हाल BPF_ALU64 | BPF_MOV | BPF_K: /* dst = (s64) imm */
			PPC_LI32(dst_reg, imm);
			PPC_EX32(dst_reg_h, imm);
			अवरोध;
		हाल BPF_ALU | BPF_MOV | BPF_K: /* (u32) dst = imm */
			PPC_LI32(dst_reg, imm);
			अवरोध;

		/*
		 * BPF_FROM_BE/LE
		 */
		हाल BPF_ALU | BPF_END | BPF_FROM_LE:
			चयन (imm) अणु
			हाल 16:
				/* Copy 16 bits to upper part */
				EMIT(PPC_RAW_RLWIMI(dst_reg, dst_reg, 16, 0, 15));
				/* Rotate 8 bits right & mask */
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 24, 16, 31));
				अवरोध;
			हाल 32:
				/*
				 * Rotate word left by 8 bits:
				 * 2 bytes are alपढ़ोy in their final position
				 * -- byte 2 and 4 (of bytes 1, 2, 3 and 4)
				 */
				EMIT(PPC_RAW_RLWINM(__REG_R0, dst_reg, 8, 0, 31));
				/* Rotate 24 bits and insert byte 1 */
				EMIT(PPC_RAW_RLWIMI(__REG_R0, dst_reg, 24, 0, 7));
				/* Rotate 24 bits and insert byte 3 */
				EMIT(PPC_RAW_RLWIMI(__REG_R0, dst_reg, 24, 16, 23));
				EMIT(PPC_RAW_MR(dst_reg, __REG_R0));
				अवरोध;
			हाल 64:
				bpf_set_seen_रेजिस्टर(ctx, पंचांगp_reg);
				EMIT(PPC_RAW_RLWINM(पंचांगp_reg, dst_reg, 8, 0, 31));
				EMIT(PPC_RAW_RLWINM(__REG_R0, dst_reg_h, 8, 0, 31));
				/* Rotate 24 bits and insert byte 1 */
				EMIT(PPC_RAW_RLWIMI(पंचांगp_reg, dst_reg, 24, 0, 7));
				EMIT(PPC_RAW_RLWIMI(__REG_R0, dst_reg_h, 24, 0, 7));
				/* Rotate 24 bits and insert byte 3 */
				EMIT(PPC_RAW_RLWIMI(पंचांगp_reg, dst_reg, 24, 16, 23));
				EMIT(PPC_RAW_RLWIMI(__REG_R0, dst_reg_h, 24, 16, 23));
				EMIT(PPC_RAW_MR(dst_reg, __REG_R0));
				EMIT(PPC_RAW_MR(dst_reg_h, पंचांगp_reg));
				अवरोध;
			पूर्ण
			अवरोध;
		हाल BPF_ALU | BPF_END | BPF_FROM_BE:
			चयन (imm) अणु
			हाल 16:
				/* zero-extend 16 bits पूर्णांकo 32 bits */
				EMIT(PPC_RAW_RLWINM(dst_reg, dst_reg, 0, 16, 31));
				अवरोध;
			हाल 32:
			हाल 64:
				/* nop */
				अवरोध;
			पूर्ण
			अवरोध;

		/*
		 * BPF_ST(X)
		 */
		हाल BPF_STX | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = src */
			EMIT(PPC_RAW_STB(src_reg, dst_reg, off));
			अवरोध;
		हाल BPF_ST | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = imm */
			PPC_LI32(__REG_R0, imm);
			EMIT(PPC_RAW_STB(__REG_R0, dst_reg, off));
			अवरोध;
		हाल BPF_STX | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = src */
			EMIT(PPC_RAW_STH(src_reg, dst_reg, off));
			अवरोध;
		हाल BPF_ST | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = imm */
			PPC_LI32(__REG_R0, imm);
			EMIT(PPC_RAW_STH(__REG_R0, dst_reg, off));
			अवरोध;
		हाल BPF_STX | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = src */
			EMIT(PPC_RAW_STW(src_reg, dst_reg, off));
			अवरोध;
		हाल BPF_ST | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = imm */
			PPC_LI32(__REG_R0, imm);
			EMIT(PPC_RAW_STW(__REG_R0, dst_reg, off));
			अवरोध;
		हाल BPF_STX | BPF_MEM | BPF_DW: /* (u64 *)(dst + off) = src */
			EMIT(PPC_RAW_STW(src_reg_h, dst_reg, off));
			EMIT(PPC_RAW_STW(src_reg, dst_reg, off + 4));
			अवरोध;
		हाल BPF_ST | BPF_MEM | BPF_DW: /* *(u64 *)(dst + off) = imm */
			PPC_LI32(__REG_R0, imm);
			EMIT(PPC_RAW_STW(__REG_R0, dst_reg, off + 4));
			PPC_EX32(__REG_R0, imm);
			EMIT(PPC_RAW_STW(__REG_R0, dst_reg, off));
			अवरोध;

		/*
		 * BPF_STX XADD (atomic_add)
		 */
		हाल BPF_STX | BPF_XADD | BPF_W: /* *(u32 *)(dst + off) += src */
			bpf_set_seen_रेजिस्टर(ctx, पंचांगp_reg);
			/* Get offset पूर्णांकo TMP_REG */
			EMIT(PPC_RAW_LI(पंचांगp_reg, off));
			/* load value from memory पूर्णांकo r0 */
			EMIT(PPC_RAW_LWARX(__REG_R0, पंचांगp_reg, dst_reg, 0));
			/* add value from src_reg पूर्णांकo this */
			EMIT(PPC_RAW_ADD(__REG_R0, __REG_R0, src_reg));
			/* store result back */
			EMIT(PPC_RAW_STWCX(__REG_R0, पंचांगp_reg, dst_reg));
			/* we're करोne अगर this succeeded */
			PPC_BCC_SHORT(COND_NE, (ctx->idx - 3) * 4);
			अवरोध;

		हाल BPF_STX | BPF_XADD | BPF_DW: /* *(u64 *)(dst + off) += src */
			वापस -EOPNOTSUPP;

		/*
		 * BPF_LDX
		 */
		हाल BPF_LDX | BPF_MEM | BPF_B: /* dst = *(u8 *)(ul) (src + off) */
			EMIT(PPC_RAW_LBZ(dst_reg, src_reg, off));
			अगर (!fp->aux->verअगरier_zext)
				EMIT(PPC_RAW_LI(dst_reg_h, 0));
			अवरोध;
		हाल BPF_LDX | BPF_MEM | BPF_H: /* dst = *(u16 *)(ul) (src + off) */
			EMIT(PPC_RAW_LHZ(dst_reg, src_reg, off));
			अगर (!fp->aux->verअगरier_zext)
				EMIT(PPC_RAW_LI(dst_reg_h, 0));
			अवरोध;
		हाल BPF_LDX | BPF_MEM | BPF_W: /* dst = *(u32 *)(ul) (src + off) */
			EMIT(PPC_RAW_LWZ(dst_reg, src_reg, off));
			अगर (!fp->aux->verअगरier_zext)
				EMIT(PPC_RAW_LI(dst_reg_h, 0));
			अवरोध;
		हाल BPF_LDX | BPF_MEM | BPF_DW: /* dst = *(u64 *)(ul) (src + off) */
			EMIT(PPC_RAW_LWZ(dst_reg_h, src_reg, off));
			EMIT(PPC_RAW_LWZ(dst_reg, src_reg, off + 4));
			अवरोध;

		/*
		 * Doubleword load
		 * 16 byte inकाष्ठाion that uses two 'struct bpf_insn'
		 */
		हाल BPF_LD | BPF_IMM | BPF_DW: /* dst = (u64) imm */
			PPC_LI32(dst_reg_h, (u32)insn[i + 1].imm);
			PPC_LI32(dst_reg, (u32)insn[i].imm);
			/* Adjust क्रम two bpf inकाष्ठाions */
			addrs[++i] = ctx->idx * 4;
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

			अगर (bpf_is_seen_रेजिस्टर(ctx, bpf_to_ppc(ctx, BPF_REG_5))) अणु
				EMIT(PPC_RAW_STW(bpf_to_ppc(ctx, BPF_REG_5) - 1, __REG_R1, 8));
				EMIT(PPC_RAW_STW(bpf_to_ppc(ctx, BPF_REG_5), __REG_R1, 12));
			पूर्ण

			bpf_jit_emit_func_call_rel(image, ctx, func_addr);

			EMIT(PPC_RAW_MR(bpf_to_ppc(ctx, BPF_REG_0) - 1, __REG_R3));
			EMIT(PPC_RAW_MR(bpf_to_ppc(ctx, BPF_REG_0), __REG_R4));
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
			/* fallthrough; */

cond_branch:
			चयन (code) अणु
			हाल BPF_JMP | BPF_JGT | BPF_X:
			हाल BPF_JMP | BPF_JLT | BPF_X:
			हाल BPF_JMP | BPF_JGE | BPF_X:
			हाल BPF_JMP | BPF_JLE | BPF_X:
			हाल BPF_JMP | BPF_JEQ | BPF_X:
			हाल BPF_JMP | BPF_JNE | BPF_X:
				/* अचिन्हित comparison */
				EMIT(PPC_RAW_CMPLW(dst_reg_h, src_reg_h));
				PPC_BCC_SHORT(COND_NE, (ctx->idx + 2) * 4);
				EMIT(PPC_RAW_CMPLW(dst_reg, src_reg));
				अवरोध;
			हाल BPF_JMP32 | BPF_JGT | BPF_X:
			हाल BPF_JMP32 | BPF_JLT | BPF_X:
			हाल BPF_JMP32 | BPF_JGE | BPF_X:
			हाल BPF_JMP32 | BPF_JLE | BPF_X:
			हाल BPF_JMP32 | BPF_JEQ | BPF_X:
			हाल BPF_JMP32 | BPF_JNE | BPF_X:
				/* अचिन्हित comparison */
				EMIT(PPC_RAW_CMPLW(dst_reg, src_reg));
				अवरोध;
			हाल BPF_JMP | BPF_JSGT | BPF_X:
			हाल BPF_JMP | BPF_JSLT | BPF_X:
			हाल BPF_JMP | BPF_JSGE | BPF_X:
			हाल BPF_JMP | BPF_JSLE | BPF_X:
				/* चिन्हित comparison */
				EMIT(PPC_RAW_CMPW(dst_reg_h, src_reg_h));
				PPC_BCC_SHORT(COND_NE, (ctx->idx + 2) * 4);
				EMIT(PPC_RAW_CMPLW(dst_reg, src_reg));
				अवरोध;
			हाल BPF_JMP32 | BPF_JSGT | BPF_X:
			हाल BPF_JMP32 | BPF_JSLT | BPF_X:
			हाल BPF_JMP32 | BPF_JSGE | BPF_X:
			हाल BPF_JMP32 | BPF_JSLE | BPF_X:
				/* चिन्हित comparison */
				EMIT(PPC_RAW_CMPW(dst_reg, src_reg));
				अवरोध;
			हाल BPF_JMP | BPF_JSET | BPF_X:
				EMIT(PPC_RAW_AND_DOT(__REG_R0, dst_reg_h, src_reg_h));
				PPC_BCC_SHORT(COND_NE, (ctx->idx + 2) * 4);
				EMIT(PPC_RAW_AND_DOT(__REG_R0, dst_reg, src_reg));
				अवरोध;
			हाल BPF_JMP32 | BPF_JSET | BPF_X: अणु
				EMIT(PPC_RAW_AND_DOT(__REG_R0, dst_reg, src_reg));
				अवरोध;
			हाल BPF_JMP | BPF_JNE | BPF_K:
			हाल BPF_JMP | BPF_JEQ | BPF_K:
			हाल BPF_JMP | BPF_JGT | BPF_K:
			हाल BPF_JMP | BPF_JLT | BPF_K:
			हाल BPF_JMP | BPF_JGE | BPF_K:
			हाल BPF_JMP | BPF_JLE | BPF_K:
				/*
				 * Need sign-extended load, so only positive
				 * values can be used as imm in cmplwi
				 */
				अगर (imm >= 0 && imm < 32768) अणु
					EMIT(PPC_RAW_CMPLWI(dst_reg_h, 0));
					PPC_BCC_SHORT(COND_NE, (ctx->idx + 2) * 4);
					EMIT(PPC_RAW_CMPLWI(dst_reg, imm));
				पूर्ण अन्यथा अणु
					/* sign-extending load ... but अचिन्हित comparison */
					PPC_EX32(__REG_R0, imm);
					EMIT(PPC_RAW_CMPLW(dst_reg_h, __REG_R0));
					PPC_LI32(__REG_R0, imm);
					PPC_BCC_SHORT(COND_NE, (ctx->idx + 2) * 4);
					EMIT(PPC_RAW_CMPLW(dst_reg, __REG_R0));
				पूर्ण
				अवरोध;
			हाल BPF_JMP32 | BPF_JNE | BPF_K:
			हाल BPF_JMP32 | BPF_JEQ | BPF_K:
			हाल BPF_JMP32 | BPF_JGT | BPF_K:
			हाल BPF_JMP32 | BPF_JLT | BPF_K:
			हाल BPF_JMP32 | BPF_JGE | BPF_K:
			हाल BPF_JMP32 | BPF_JLE | BPF_K:
				अगर (imm >= 0 && imm < 65536) अणु
					EMIT(PPC_RAW_CMPLWI(dst_reg, imm));
				पूर्ण अन्यथा अणु
					PPC_LI32(__REG_R0, imm);
					EMIT(PPC_RAW_CMPLW(dst_reg, __REG_R0));
				पूर्ण
				अवरोध;
			पूर्ण
			हाल BPF_JMP | BPF_JSGT | BPF_K:
			हाल BPF_JMP | BPF_JSLT | BPF_K:
			हाल BPF_JMP | BPF_JSGE | BPF_K:
			हाल BPF_JMP | BPF_JSLE | BPF_K:
				अगर (imm >= 0 && imm < 65536) अणु
					EMIT(PPC_RAW_CMPWI(dst_reg_h, imm < 0 ? -1 : 0));
					PPC_BCC_SHORT(COND_NE, (ctx->idx + 2) * 4);
					EMIT(PPC_RAW_CMPLWI(dst_reg, imm));
				पूर्ण अन्यथा अणु
					/* sign-extending load */
					EMIT(PPC_RAW_CMPWI(dst_reg_h, imm < 0 ? -1 : 0));
					PPC_LI32(__REG_R0, imm);
					PPC_BCC_SHORT(COND_NE, (ctx->idx + 2) * 4);
					EMIT(PPC_RAW_CMPLW(dst_reg, __REG_R0));
				पूर्ण
				अवरोध;
			हाल BPF_JMP32 | BPF_JSGT | BPF_K:
			हाल BPF_JMP32 | BPF_JSLT | BPF_K:
			हाल BPF_JMP32 | BPF_JSGE | BPF_K:
			हाल BPF_JMP32 | BPF_JSLE | BPF_K:
				/*
				 * चिन्हित comparison, so any 16-bit value
				 * can be used in cmpwi
				 */
				अगर (imm >= -32768 && imm < 32768) अणु
					EMIT(PPC_RAW_CMPWI(dst_reg, imm));
				पूर्ण अन्यथा अणु
					/* sign-extending load */
					PPC_LI32(__REG_R0, imm);
					EMIT(PPC_RAW_CMPW(dst_reg, __REG_R0));
				पूर्ण
				अवरोध;
			हाल BPF_JMP | BPF_JSET | BPF_K:
				/* andi करोes not sign-extend the immediate */
				अगर (imm >= 0 && imm < 32768) अणु
					/* PPC_ANDI is _only/always_ करोt-क्रमm */
					EMIT(PPC_RAW_ANDI(__REG_R0, dst_reg, imm));
				पूर्ण अन्यथा अणु
					PPC_LI32(__REG_R0, imm);
					अगर (imm < 0) अणु
						EMIT(PPC_RAW_CMPWI(dst_reg_h, 0));
						PPC_BCC_SHORT(COND_NE, (ctx->idx + 2) * 4);
					पूर्ण
					EMIT(PPC_RAW_AND_DOT(__REG_R0, dst_reg, __REG_R0));
				पूर्ण
				अवरोध;
			हाल BPF_JMP32 | BPF_JSET | BPF_K:
				/* andi करोes not sign-extend the immediate */
				अगर (imm >= -32768 && imm < 32768) अणु
					/* PPC_ANDI is _only/always_ करोt-क्रमm */
					EMIT(PPC_RAW_ANDI(__REG_R0, dst_reg, imm));
				पूर्ण अन्यथा अणु
					PPC_LI32(__REG_R0, imm);
					EMIT(PPC_RAW_AND_DOT(__REG_R0, dst_reg, __REG_R0));
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
			pr_err_ratelimited("eBPF filter opcode %04x (@%d) unsupported\n", code, i);
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (BPF_CLASS(code) == BPF_ALU && !fp->aux->verअगरier_zext &&
		    !insn_is_zext(&insn[i + 1]))
			EMIT(PPC_RAW_LI(dst_reg_h, 0));
	पूर्ण

	/* Set end-of-body-code address क्रम निकास. */
	addrs[i] = ctx->idx * 4;

	वापस 0;
पूर्ण
