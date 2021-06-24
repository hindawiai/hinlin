<शैली गुरु>
/*
 * Just-In-Time compiler क्रम BPF filters on MIPS
 *
 * Copyright (c) 2014 Imagination Technologies Ltd.
 * Author: Markos Chandras <markos.chandras@imgtec.com>
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation; version 2 of the License.
 */

#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/moduleloader.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/types.h>
#समावेश <यंत्र/यंत्र.h>
#समावेश <यंत्र/bitops.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/cpu-features.h>
#समावेश <यंत्र/uयंत्र.h>

#समावेश "bpf_jit.h"

/* ABI
 * r_skb_hl	SKB header length
 * r_data	SKB data poपूर्णांकer
 * r_off	Offset
 * r_A		BPF रेजिस्टर A
 * r_X		BPF रेजिस्टर X
 * r_skb	*skb
 * r_M		*scratch memory
 * r_skb_len	SKB length
 *
 * On entry (*bpf_func)(*skb, *filter)
 * a0 = MIPS_R_A0 = skb;
 * a1 = MIPS_R_A1 = filter;
 *
 * Stack
 * ...
 * M[15]
 * M[14]
 * M[13]
 * ...
 * M[0] <-- r_M
 * saved reg k-1
 * saved reg k-2
 * ...
 * saved reg 0 <-- r_sp
 * <no argument area>
 *
 *                     Packet layout
 *
 * <--------------------- len ------------------------>
 * <--skb-len(r_skb_hl)-->< ----- skb->data_len ------>
 * ----------------------------------------------------
 * |                  skb->data                       |
 * ----------------------------------------------------
 */

#घोषणा ptr typeof(अचिन्हित दीर्घ)

#घोषणा SCRATCH_OFF(k)		(4 * (k))

/* JIT flags */
#घोषणा SEEN_CALL		(1 << BPF_MEMWORDS)
#घोषणा SEEN_SREG_SFT		(BPF_MEMWORDS + 1)
#घोषणा SEEN_SREG_BASE		(1 << SEEN_SREG_SFT)
#घोषणा SEEN_SREG(x)		(SEEN_SREG_BASE << (x))
#घोषणा SEEN_OFF		SEEN_SREG(2)
#घोषणा SEEN_A			SEEN_SREG(3)
#घोषणा SEEN_X			SEEN_SREG(4)
#घोषणा SEEN_SKB		SEEN_SREG(5)
#घोषणा SEEN_MEM		SEEN_SREG(6)
/* SEEN_SK_DATA also implies skb_hl an skb_len */
#घोषणा SEEN_SKB_DATA		(SEEN_SREG(7) | SEEN_SREG(1) | SEEN_SREG(0))

/* Arguments used by JIT */
#घोषणा ARGS_USED_BY_JIT	2 /* only applicable to 64-bit */

#घोषणा SBIT(x)			(1 << (x)) /* Signed version of BIT() */

/**
 * काष्ठा jit_ctx - JIT context
 * @skf:		The sk_filter
 * @prologue_bytes:	Number of bytes क्रम prologue
 * @idx:		Inकाष्ठाion index
 * @flags:		JIT flags
 * @offsets:		Inकाष्ठाion offsets
 * @target:		Memory location क्रम the compiled filter
 */
काष्ठा jit_ctx अणु
	स्थिर काष्ठा bpf_prog *skf;
	अचिन्हित पूर्णांक prologue_bytes;
	u32 idx;
	u32 flags;
	u32 *offsets;
	u32 *target;
पूर्ण;


अटल अंतरभूत पूर्णांक optimize_भाग(u32 *k)
अणु
	/* घातer of 2 भागides can be implemented with right shअगरt */
	अगर (!(*k & (*k-1))) अणु
		*k = ilog2(*k);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम emit_jit_reg_move(ptr dst, ptr src, काष्ठा jit_ctx *ctx);

/* Simply emit the inकाष्ठाion अगर the JIT memory space has been allocated */
#घोषणा emit_instr(ctx, func, ...)			\
करो अणु							\
	अगर ((ctx)->target != शून्य) अणु			\
		u32 *p = &(ctx)->target[ctx->idx];	\
		uयंत्र_i_##func(&p, ##__VA_ARGS__);	\
	पूर्ण						\
	(ctx)->idx++;					\
पूर्ण जबतक (0)

/*
 * Similar to emit_instr but it must be used when we need to emit
 * 32-bit or 64-bit inकाष्ठाions
 */
#घोषणा emit_दीर्घ_instr(ctx, func, ...)			\
करो अणु							\
	अगर ((ctx)->target != शून्य) अणु			\
		u32 *p = &(ctx)->target[ctx->idx];	\
		UASM_i_##func(&p, ##__VA_ARGS__);	\
	पूर्ण						\
	(ctx)->idx++;					\
पूर्ण जबतक (0)

/* Determine अगर immediate is within the 16-bit चिन्हित range */
अटल अंतरभूत bool is_range16(s32 imm)
अणु
	वापस !(imm >= SBIT(15) || imm < -SBIT(15));
पूर्ण

अटल अंतरभूत व्योम emit_addu(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src1,
			     अचिन्हित पूर्णांक src2, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, addu, dst, src1, src2);
पूर्ण

अटल अंतरभूत व्योम emit_nop(काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, nop);
पूर्ण

/* Load a u32 immediate to a रेजिस्टर */
अटल अंतरभूत व्योम emit_load_imm(अचिन्हित पूर्णांक dst, u32 imm, काष्ठा jit_ctx *ctx)
अणु
	अगर (ctx->target != शून्य) अणु
		/* addiu can only handle s16 */
		अगर (!is_range16(imm)) अणु
			u32 *p = &ctx->target[ctx->idx];
			uयंत्र_i_lui(&p, r_पंचांगp_imm, (s32)imm >> 16);
			p = &ctx->target[ctx->idx + 1];
			uयंत्र_i_ori(&p, dst, r_पंचांगp_imm, imm & 0xffff);
		पूर्ण अन्यथा अणु
			u32 *p = &ctx->target[ctx->idx];
			uयंत्र_i_addiu(&p, dst, r_zero, imm);
		पूर्ण
	पूर्ण
	ctx->idx++;

	अगर (!is_range16(imm))
		ctx->idx++;
पूर्ण

अटल अंतरभूत व्योम emit_or(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src1,
			   अचिन्हित पूर्णांक src2, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, or, dst, src1, src2);
पूर्ण

अटल अंतरभूत व्योम emit_ori(अचिन्हित पूर्णांक dst, अचिन्हित src, u32 imm,
			    काष्ठा jit_ctx *ctx)
अणु
	अगर (imm >= BIT(16)) अणु
		emit_load_imm(r_पंचांगp, imm, ctx);
		emit_or(dst, src, r_पंचांगp, ctx);
	पूर्ण अन्यथा अणु
		emit_instr(ctx, ori, dst, src, imm);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम emit_daddiu(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			       पूर्णांक imm, काष्ठा jit_ctx *ctx)
अणु
	/*
	 * Only used क्रम stack, so the imm is relatively small
	 * and it fits in 15-bits
	 */
	emit_instr(ctx, daddiu, dst, src, imm);
पूर्ण

अटल अंतरभूत व्योम emit_addiu(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			      u32 imm, काष्ठा jit_ctx *ctx)
अणु
	अगर (!is_range16(imm)) अणु
		emit_load_imm(r_पंचांगp, imm, ctx);
		emit_addu(dst, r_पंचांगp, src, ctx);
	पूर्ण अन्यथा अणु
		emit_instr(ctx, addiu, dst, src, imm);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम emit_and(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src1,
			    अचिन्हित पूर्णांक src2, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, and, dst, src1, src2);
पूर्ण

अटल अंतरभूत व्योम emit_andi(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			     u32 imm, काष्ठा jit_ctx *ctx)
अणु
	/* If imm करोes not fit in u16 then load it to रेजिस्टर */
	अगर (imm >= BIT(16)) अणु
		emit_load_imm(r_पंचांगp, imm, ctx);
		emit_and(dst, src, r_पंचांगp, ctx);
	पूर्ण अन्यथा अणु
		emit_instr(ctx, andi, dst, src, imm);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम emit_xor(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src1,
			    अचिन्हित पूर्णांक src2, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, xor, dst, src1, src2);
पूर्ण

अटल अंतरभूत व्योम emit_xori(ptr dst, ptr src, u32 imm, काष्ठा jit_ctx *ctx)
अणु
	/* If imm करोes not fit in u16 then load it to रेजिस्टर */
	अगर (imm >= BIT(16)) अणु
		emit_load_imm(r_पंचांगp, imm, ctx);
		emit_xor(dst, src, r_पंचांगp, ctx);
	पूर्ण अन्यथा अणु
		emit_instr(ctx, xori, dst, src, imm);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम emit_stack_offset(पूर्णांक offset, काष्ठा jit_ctx *ctx)
अणु
	emit_दीर्घ_instr(ctx, ADDIU, r_sp, r_sp, offset);
पूर्ण

अटल अंतरभूत व्योम emit_subu(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src1,
			     अचिन्हित पूर्णांक src2, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, subu, dst, src1, src2);
पूर्ण

अटल अंतरभूत व्योम emit_neg(अचिन्हित पूर्णांक reg, काष्ठा jit_ctx *ctx)
अणु
	emit_subu(reg, r_zero, reg, ctx);
पूर्ण

अटल अंतरभूत व्योम emit_sllv(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			     अचिन्हित पूर्णांक sa, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, sllv, dst, src, sa);
पूर्ण

अटल अंतरभूत व्योम emit_sll(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			    अचिन्हित पूर्णांक sa, काष्ठा jit_ctx *ctx)
अणु
	/* sa is 5-bits दीर्घ */
	अगर (sa >= BIT(5))
		/* Shअगरting >= 32 results in zero */
		emit_jit_reg_move(dst, r_zero, ctx);
	अन्यथा
		emit_instr(ctx, sll, dst, src, sa);
पूर्ण

अटल अंतरभूत व्योम emit_srlv(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			     अचिन्हित पूर्णांक sa, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, srlv, dst, src, sa);
पूर्ण

अटल अंतरभूत व्योम emit_srl(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			    अचिन्हित पूर्णांक sa, काष्ठा jit_ctx *ctx)
अणु
	/* sa is 5-bits दीर्घ */
	अगर (sa >= BIT(5))
		/* Shअगरting >= 32 results in zero */
		emit_jit_reg_move(dst, r_zero, ctx);
	अन्यथा
		emit_instr(ctx, srl, dst, src, sa);
पूर्ण

अटल अंतरभूत व्योम emit_slt(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src1,
			    अचिन्हित पूर्णांक src2, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, slt, dst, src1, src2);
पूर्ण

अटल अंतरभूत व्योम emit_sltu(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src1,
			     अचिन्हित पूर्णांक src2, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, sltu, dst, src1, src2);
पूर्ण

अटल अंतरभूत व्योम emit_sltiu(अचिन्हित dst, अचिन्हित पूर्णांक src,
			      अचिन्हित पूर्णांक imm, काष्ठा jit_ctx *ctx)
अणु
	/* 16 bit immediate */
	अगर (!is_range16((s32)imm)) अणु
		emit_load_imm(r_पंचांगp, imm, ctx);
		emit_sltu(dst, src, r_पंचांगp, ctx);
	पूर्ण अन्यथा अणु
		emit_instr(ctx, sltiu, dst, src, imm);
	पूर्ण

पूर्ण

/* Store रेजिस्टर on the stack */
अटल अंतरभूत व्योम emit_store_stack_reg(ptr reg, ptr base,
					अचिन्हित पूर्णांक offset,
					काष्ठा jit_ctx *ctx)
अणु
	emit_दीर्घ_instr(ctx, SW, reg, offset, base);
पूर्ण

अटल अंतरभूत व्योम emit_store(ptr reg, ptr base, अचिन्हित पूर्णांक offset,
			      काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, sw, reg, offset, base);
पूर्ण

अटल अंतरभूत व्योम emit_load_stack_reg(ptr reg, ptr base,
				       अचिन्हित पूर्णांक offset,
				       काष्ठा jit_ctx *ctx)
अणु
	emit_दीर्घ_instr(ctx, LW, reg, offset, base);
पूर्ण

अटल अंतरभूत व्योम emit_load(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक base,
			     अचिन्हित पूर्णांक offset, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, lw, reg, offset, base);
पूर्ण

अटल अंतरभूत व्योम emit_load_byte(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक base,
				  अचिन्हित पूर्णांक offset, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, lb, reg, offset, base);
पूर्ण

अटल अंतरभूत व्योम emit_half_load(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक base,
				  अचिन्हित पूर्णांक offset, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, lh, reg, offset, base);
पूर्ण

अटल अंतरभूत व्योम emit_half_load_अचिन्हित(अचिन्हित पूर्णांक reg, अचिन्हित पूर्णांक base,
					   अचिन्हित पूर्णांक offset, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, lhu, reg, offset, base);
पूर्ण

अटल अंतरभूत व्योम emit_mul(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src1,
			    अचिन्हित पूर्णांक src2, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, mul, dst, src1, src2);
पूर्ण

अटल अंतरभूत व्योम emit_भाग(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			    काष्ठा jit_ctx *ctx)
अणु
	अगर (ctx->target != शून्य) अणु
		u32 *p = &ctx->target[ctx->idx];
		uयंत्र_i_भागu(&p, dst, src);
		p = &ctx->target[ctx->idx + 1];
		uयंत्र_i_mflo(&p, dst);
	पूर्ण
	ctx->idx += 2; /* 2 insts */
पूर्ण

अटल अंतरभूत व्योम emit_mod(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			    काष्ठा jit_ctx *ctx)
अणु
	अगर (ctx->target != शून्य) अणु
		u32 *p = &ctx->target[ctx->idx];
		uयंत्र_i_भागu(&p, dst, src);
		p = &ctx->target[ctx->idx + 1];
		uयंत्र_i_mfhi(&p, dst);
	पूर्ण
	ctx->idx += 2; /* 2 insts */
पूर्ण

अटल अंतरभूत व्योम emit_dsll(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			     अचिन्हित पूर्णांक sa, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, dsll, dst, src, sa);
पूर्ण

अटल अंतरभूत व्योम emit_dsrl32(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			       अचिन्हित पूर्णांक sa, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, dsrl32, dst, src, sa);
पूर्ण

अटल अंतरभूत व्योम emit_wsbh(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
			     काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, wsbh, dst, src);
पूर्ण

/* load poपूर्णांकer to रेजिस्टर */
अटल अंतरभूत व्योम emit_load_ptr(अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक src,
				     पूर्णांक imm, काष्ठा jit_ctx *ctx)
अणु
	/* src contains the base addr of the 32/64-poपूर्णांकer */
	emit_दीर्घ_instr(ctx, LW, dst, imm, src);
पूर्ण

/* load a function poपूर्णांकer to रेजिस्टर */
अटल अंतरभूत व्योम emit_load_func(अचिन्हित पूर्णांक reg, ptr imm,
				  काष्ठा jit_ctx *ctx)
अणु
	अगर (IS_ENABLED(CONFIG_64BIT)) अणु
		/* At this poपूर्णांक imm is always 64-bit */
		emit_load_imm(r_पंचांगp, (u64)imm >> 32, ctx);
		emit_dsll(r_पंचांगp_imm, r_पंचांगp, 16, ctx); /* left shअगरt by 16 */
		emit_ori(r_पंचांगp, r_पंचांगp_imm, (imm >> 16) & 0xffff, ctx);
		emit_dsll(r_पंचांगp_imm, r_पंचांगp, 16, ctx); /* left shअगरt by 16 */
		emit_ori(reg, r_पंचांगp_imm, imm & 0xffff, ctx);
	पूर्ण अन्यथा अणु
		emit_load_imm(reg, imm, ctx);
	पूर्ण
पूर्ण

/* Move to real MIPS रेजिस्टर */
अटल अंतरभूत व्योम emit_reg_move(ptr dst, ptr src, काष्ठा jit_ctx *ctx)
अणु
	emit_दीर्घ_instr(ctx, ADDU, dst, src, r_zero);
पूर्ण

/* Move to JIT (32-bit) रेजिस्टर */
अटल अंतरभूत व्योम emit_jit_reg_move(ptr dst, ptr src, काष्ठा jit_ctx *ctx)
अणु
	emit_addu(dst, src, r_zero, ctx);
पूर्ण

/* Compute the immediate value क्रम PC-relative branches. */
अटल अंतरभूत u32 b_imm(अचिन्हित पूर्णांक tgt, काष्ठा jit_ctx *ctx)
अणु
	अगर (ctx->target == शून्य)
		वापस 0;

	/*
	 * We want a pc-relative branch. We only करो क्रमward branches
	 * so tgt is always after pc. tgt is the inकाष्ठाion offset
	 * we want to jump to.

	 * Branch on MIPS:
	 * I: target_offset <- sign_extend(offset)
	 * I+1: PC += target_offset (delay slot)
	 *
	 * ctx->idx currently poपूर्णांकs to the branch inकाष्ठाion
	 * but the offset is added to the delay slot so we need
	 * to subtract 4.
	 */
	वापस ctx->offsets[tgt] -
		(ctx->idx * 4 - ctx->prologue_bytes) - 4;
पूर्ण

अटल अंतरभूत व्योम emit_bcond(पूर्णांक cond, अचिन्हित पूर्णांक reg1, अचिन्हित पूर्णांक reg2,
			     अचिन्हित पूर्णांक imm, काष्ठा jit_ctx *ctx)
अणु
	अगर (ctx->target != शून्य) अणु
		u32 *p = &ctx->target[ctx->idx];

		चयन (cond) अणु
		हाल MIPS_COND_EQ:
			uयंत्र_i_beq(&p, reg1, reg2, imm);
			अवरोध;
		हाल MIPS_COND_NE:
			uयंत्र_i_bne(&p, reg1, reg2, imm);
			अवरोध;
		हाल MIPS_COND_ALL:
			uयंत्र_i_b(&p, imm);
			अवरोध;
		शेष:
			pr_warn("%s: Unhandled branch conditional: %d\n",
				__func__, cond);
		पूर्ण
	पूर्ण
	ctx->idx++;
पूर्ण

अटल अंतरभूत व्योम emit_b(अचिन्हित पूर्णांक imm, काष्ठा jit_ctx *ctx)
अणु
	emit_bcond(MIPS_COND_ALL, r_zero, r_zero, imm, ctx);
पूर्ण

अटल अंतरभूत व्योम emit_jalr(अचिन्हित पूर्णांक link, अचिन्हित पूर्णांक reg,
			     काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, jalr, link, reg);
पूर्ण

अटल अंतरभूत व्योम emit_jr(अचिन्हित पूर्णांक reg, काष्ठा jit_ctx *ctx)
अणु
	emit_instr(ctx, jr, reg);
पूर्ण

अटल अंतरभूत u16 align_sp(अचिन्हित पूर्णांक num)
अणु
	/* Double word alignment क्रम 32-bit, quadword क्रम 64-bit */
	अचिन्हित पूर्णांक align = IS_ENABLED(CONFIG_64BIT) ? 16 : 8;
	num = (num + (align - 1)) & -align;
	वापस num;
पूर्ण

अटल व्योम save_bpf_jit_regs(काष्ठा jit_ctx *ctx, अचिन्हित offset)
अणु
	पूर्णांक i = 0, real_off = 0;
	u32 sflags, पंचांगp_flags;

	/* Adjust the stack poपूर्णांकer */
	अगर (offset)
		emit_stack_offset(-align_sp(offset), ctx);

	पंचांगp_flags = sflags = ctx->flags >> SEEN_SREG_SFT;
	/* sflags is essentially a biपंचांगap */
	जबतक (पंचांगp_flags) अणु
		अगर ((sflags >> i) & 0x1) अणु
			emit_store_stack_reg(MIPS_R_S0 + i, r_sp, real_off,
					     ctx);
			real_off += SZREG;
		पूर्ण
		i++;
		पंचांगp_flags >>= 1;
	पूर्ण

	/* save वापस address */
	अगर (ctx->flags & SEEN_CALL) अणु
		emit_store_stack_reg(r_ra, r_sp, real_off, ctx);
		real_off += SZREG;
	पूर्ण

	/* Setup r_M leaving the alignment gap अगर necessary */
	अगर (ctx->flags & SEEN_MEM) अणु
		अगर (real_off % (SZREG * 2))
			real_off += SZREG;
		emit_दीर्घ_instr(ctx, ADDIU, r_M, r_sp, real_off);
	पूर्ण
पूर्ण

अटल व्योम restore_bpf_jit_regs(काष्ठा jit_ctx *ctx,
				 अचिन्हित पूर्णांक offset)
अणु
	पूर्णांक i, real_off = 0;
	u32 sflags, पंचांगp_flags;

	पंचांगp_flags = sflags = ctx->flags >> SEEN_SREG_SFT;
	/* sflags is a biपंचांगap */
	i = 0;
	जबतक (पंचांगp_flags) अणु
		अगर ((sflags >> i) & 0x1) अणु
			emit_load_stack_reg(MIPS_R_S0 + i, r_sp, real_off,
					    ctx);
			real_off += SZREG;
		पूर्ण
		i++;
		पंचांगp_flags >>= 1;
	पूर्ण

	/* restore वापस address */
	अगर (ctx->flags & SEEN_CALL)
		emit_load_stack_reg(r_ra, r_sp, real_off, ctx);

	/* Restore the sp and discard the scrach memory */
	अगर (offset)
		emit_stack_offset(align_sp(offset), ctx);
पूर्ण

अटल अचिन्हित पूर्णांक get_stack_depth(काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक sp_off = 0;


	/* How may s* regs करो we need to preserved? */
	sp_off += hweight32(ctx->flags >> SEEN_SREG_SFT) * SZREG;

	अगर (ctx->flags & SEEN_MEM)
		sp_off += 4 * BPF_MEMWORDS; /* BPF_MEMWORDS are 32-bit */

	अगर (ctx->flags & SEEN_CALL)
		sp_off += SZREG; /* Space क्रम our ra रेजिस्टर */

	वापस sp_off;
पूर्ण

अटल व्योम build_prologue(काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक sp_off;

	/* Calculate the total offset क्रम the stack poपूर्णांकer */
	sp_off = get_stack_depth(ctx);
	save_bpf_jit_regs(ctx, sp_off);

	अगर (ctx->flags & SEEN_SKB)
		emit_reg_move(r_skb, MIPS_R_A0, ctx);

	अगर (ctx->flags & SEEN_SKB_DATA) अणु
		/* Load packet length */
		emit_load(r_skb_len, r_skb, दुरत्व(काष्ठा sk_buff, len),
			  ctx);
		emit_load(r_पंचांगp, r_skb, दुरत्व(काष्ठा sk_buff, data_len),
			  ctx);
		/* Load the data poपूर्णांकer */
		emit_load_ptr(r_skb_data, r_skb,
			      दुरत्व(काष्ठा sk_buff, data), ctx);
		/* Load the header length */
		emit_subu(r_skb_hl, r_skb_len, r_पंचांगp, ctx);
	पूर्ण

	अगर (ctx->flags & SEEN_X)
		emit_jit_reg_move(r_X, r_zero, ctx);

	/*
	 * Do not leak kernel data to userspace, we only need to clear
	 * r_A अगर it is ever used.  In fact अगर it is never used, we
	 * will not save/restore it, so clearing it in this हाल would
	 * corrupt the state of the caller.
	 */
	अगर (bpf_needs_clear_a(&ctx->skf->insns[0]) &&
	    (ctx->flags & SEEN_A))
		emit_jit_reg_move(r_A, r_zero, ctx);
पूर्ण

अटल व्योम build_epilogue(काष्ठा jit_ctx *ctx)
अणु
	अचिन्हित पूर्णांक sp_off;

	/* Calculate the total offset क्रम the stack poपूर्णांकer */

	sp_off = get_stack_depth(ctx);
	restore_bpf_jit_regs(ctx, sp_off);

	/* Return */
	emit_jr(r_ra, ctx);
	emit_nop(ctx);
पूर्ण

#घोषणा CHOOSE_LOAD_FUNC(K, func) \
	((पूर्णांक)K < 0 ? ((पूर्णांक)K >= SKF_LL_OFF ? func##_negative : func) : \
	 func##_positive)

अटल पूर्णांक build_body(काष्ठा jit_ctx *ctx)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->skf;
	स्थिर काष्ठा sock_filter *inst;
	अचिन्हित पूर्णांक i, off, condt;
	u32 k, b_off __maybe_unused;
	u8 (*sk_load_func)(अचिन्हित दीर्घ *skb, पूर्णांक offset);

	क्रम (i = 0; i < prog->len; i++) अणु
		u16 code;

		inst = &(prog->insns[i]);
		pr_debug("%s: code->0x%02x, jt->0x%x, jf->0x%x, k->0x%x\n",
			 __func__, inst->code, inst->jt, inst->jf, inst->k);
		k = inst->k;
		code = bpf_anc_helper(inst);

		अगर (ctx->target == शून्य)
			ctx->offsets[i] = ctx->idx * 4;

		चयन (code) अणु
		हाल BPF_LD | BPF_IMM:
			/* A <- k ==> li r_A, k */
			ctx->flags |= SEEN_A;
			emit_load_imm(r_A, k, ctx);
			अवरोध;
		हाल BPF_LD | BPF_W | BPF_LEN:
			BUILD_BUG_ON(माप_field(काष्ठा sk_buff, len) != 4);
			/* A <- len ==> lw r_A, offset(skb) */
			ctx->flags |= SEEN_SKB | SEEN_A;
			off = दुरत्व(काष्ठा sk_buff, len);
			emit_load(r_A, r_skb, off, ctx);
			अवरोध;
		हाल BPF_LD | BPF_MEM:
			/* A <- M[k] ==> lw r_A, offset(M) */
			ctx->flags |= SEEN_MEM | SEEN_A;
			emit_load(r_A, r_M, SCRATCH_OFF(k), ctx);
			अवरोध;
		हाल BPF_LD | BPF_W | BPF_ABS:
			/* A <- P[k:4] */
			sk_load_func = CHOOSE_LOAD_FUNC(k, sk_load_word);
			जाओ load;
		हाल BPF_LD | BPF_H | BPF_ABS:
			/* A <- P[k:2] */
			sk_load_func = CHOOSE_LOAD_FUNC(k, sk_load_half);
			जाओ load;
		हाल BPF_LD | BPF_B | BPF_ABS:
			/* A <- P[k:1] */
			sk_load_func = CHOOSE_LOAD_FUNC(k, sk_load_byte);
load:
			emit_load_imm(r_off, k, ctx);
load_common:
			ctx->flags |= SEEN_CALL | SEEN_OFF |
				SEEN_SKB | SEEN_A | SEEN_SKB_DATA;

			emit_load_func(r_s0, (ptr)sk_load_func, ctx);
			emit_reg_move(MIPS_R_A0, r_skb, ctx);
			emit_jalr(MIPS_R_RA, r_s0, ctx);
			/* Load second argument to delay slot */
			emit_reg_move(MIPS_R_A1, r_off, ctx);
			/* Check the error value */
			emit_bcond(MIPS_COND_EQ, r_ret, 0, b_imm(i + 1, ctx),
				   ctx);
			/* Load वापस रेजिस्टर on DS क्रम failures */
			emit_reg_move(r_ret, r_zero, ctx);
			/* Return with error */
			emit_b(b_imm(prog->len, ctx), ctx);
			emit_nop(ctx);
			अवरोध;
		हाल BPF_LD | BPF_W | BPF_IND:
			/* A <- P[X + k:4] */
			sk_load_func = sk_load_word;
			जाओ load_ind;
		हाल BPF_LD | BPF_H | BPF_IND:
			/* A <- P[X + k:2] */
			sk_load_func = sk_load_half;
			जाओ load_ind;
		हाल BPF_LD | BPF_B | BPF_IND:
			/* A <- P[X + k:1] */
			sk_load_func = sk_load_byte;
load_ind:
			ctx->flags |= SEEN_OFF | SEEN_X;
			emit_addiu(r_off, r_X, k, ctx);
			जाओ load_common;
		हाल BPF_LDX | BPF_IMM:
			/* X <- k */
			ctx->flags |= SEEN_X;
			emit_load_imm(r_X, k, ctx);
			अवरोध;
		हाल BPF_LDX | BPF_MEM:
			/* X <- M[k] */
			ctx->flags |= SEEN_X | SEEN_MEM;
			emit_load(r_X, r_M, SCRATCH_OFF(k), ctx);
			अवरोध;
		हाल BPF_LDX | BPF_W | BPF_LEN:
			/* X <- len */
			ctx->flags |= SEEN_X | SEEN_SKB;
			off = दुरत्व(काष्ठा sk_buff, len);
			emit_load(r_X, r_skb, off, ctx);
			अवरोध;
		हाल BPF_LDX | BPF_B | BPF_MSH:
			/* X <- 4 * (P[k:1] & 0xf) */
			ctx->flags |= SEEN_X | SEEN_CALL | SEEN_SKB;
			/* Load offset to a1 */
			emit_load_func(r_s0, (ptr)sk_load_byte, ctx);
			/*
			 * This may emit two inकाष्ठाions so it may not fit
			 * in the delay slot. So use a0 in the delay slot.
			 */
			emit_load_imm(MIPS_R_A1, k, ctx);
			emit_jalr(MIPS_R_RA, r_s0, ctx);
			emit_reg_move(MIPS_R_A0, r_skb, ctx); /* delay slot */
			/* Check the error value */
			emit_bcond(MIPS_COND_NE, r_ret, 0,
				   b_imm(prog->len, ctx), ctx);
			emit_reg_move(r_ret, r_zero, ctx);
			/* We are good */
			/* X <- P[1:K] & 0xf */
			emit_andi(r_X, r_A, 0xf, ctx);
			/* X << 2 */
			emit_b(b_imm(i + 1, ctx), ctx);
			emit_sll(r_X, r_X, 2, ctx); /* delay slot */
			अवरोध;
		हाल BPF_ST:
			/* M[k] <- A */
			ctx->flags |= SEEN_MEM | SEEN_A;
			emit_store(r_A, r_M, SCRATCH_OFF(k), ctx);
			अवरोध;
		हाल BPF_STX:
			/* M[k] <- X */
			ctx->flags |= SEEN_MEM | SEEN_X;
			emit_store(r_X, r_M, SCRATCH_OFF(k), ctx);
			अवरोध;
		हाल BPF_ALU | BPF_ADD | BPF_K:
			/* A += K */
			ctx->flags |= SEEN_A;
			emit_addiu(r_A, r_A, k, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_ADD | BPF_X:
			/* A += X */
			ctx->flags |= SEEN_A | SEEN_X;
			emit_addu(r_A, r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_SUB | BPF_K:
			/* A -= K */
			ctx->flags |= SEEN_A;
			emit_addiu(r_A, r_A, -k, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_SUB | BPF_X:
			/* A -= X */
			ctx->flags |= SEEN_A | SEEN_X;
			emit_subu(r_A, r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_MUL | BPF_K:
			/* A *= K */
			/* Load K to scratch रेजिस्टर beक्रमe MUL */
			ctx->flags |= SEEN_A;
			emit_load_imm(r_s0, k, ctx);
			emit_mul(r_A, r_A, r_s0, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_MUL | BPF_X:
			/* A *= X */
			ctx->flags |= SEEN_A | SEEN_X;
			emit_mul(r_A, r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_DIV | BPF_K:
			/* A /= k */
			अगर (k == 1)
				अवरोध;
			अगर (optimize_भाग(&k)) अणु
				ctx->flags |= SEEN_A;
				emit_srl(r_A, r_A, k, ctx);
				अवरोध;
			पूर्ण
			ctx->flags |= SEEN_A;
			emit_load_imm(r_s0, k, ctx);
			emit_भाग(r_A, r_s0, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_MOD | BPF_K:
			/* A %= k */
			अगर (k == 1) अणु
				ctx->flags |= SEEN_A;
				emit_jit_reg_move(r_A, r_zero, ctx);
			पूर्ण अन्यथा अणु
				ctx->flags |= SEEN_A;
				emit_load_imm(r_s0, k, ctx);
				emit_mod(r_A, r_s0, ctx);
			पूर्ण
			अवरोध;
		हाल BPF_ALU | BPF_DIV | BPF_X:
			/* A /= X */
			ctx->flags |= SEEN_X | SEEN_A;
			/* Check अगर r_X is zero */
			emit_bcond(MIPS_COND_EQ, r_X, r_zero,
				   b_imm(prog->len, ctx), ctx);
			emit_load_imm(r_ret, 0, ctx); /* delay slot */
			emit_भाग(r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_MOD | BPF_X:
			/* A %= X */
			ctx->flags |= SEEN_X | SEEN_A;
			/* Check अगर r_X is zero */
			emit_bcond(MIPS_COND_EQ, r_X, r_zero,
				   b_imm(prog->len, ctx), ctx);
			emit_load_imm(r_ret, 0, ctx); /* delay slot */
			emit_mod(r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_OR | BPF_K:
			/* A |= K */
			ctx->flags |= SEEN_A;
			emit_ori(r_A, r_A, k, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_OR | BPF_X:
			/* A |= X */
			ctx->flags |= SEEN_A;
			emit_ori(r_A, r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_XOR | BPF_K:
			/* A ^= k */
			ctx->flags |= SEEN_A;
			emit_xori(r_A, r_A, k, ctx);
			अवरोध;
		हाल BPF_ANC | SKF_AD_ALU_XOR_X:
		हाल BPF_ALU | BPF_XOR | BPF_X:
			/* A ^= X */
			ctx->flags |= SEEN_A;
			emit_xor(r_A, r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_AND | BPF_K:
			/* A &= K */
			ctx->flags |= SEEN_A;
			emit_andi(r_A, r_A, k, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_AND | BPF_X:
			/* A &= X */
			ctx->flags |= SEEN_A | SEEN_X;
			emit_and(r_A, r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_LSH | BPF_K:
			/* A <<= K */
			ctx->flags |= SEEN_A;
			emit_sll(r_A, r_A, k, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_LSH | BPF_X:
			/* A <<= X */
			ctx->flags |= SEEN_A | SEEN_X;
			emit_sllv(r_A, r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_RSH | BPF_K:
			/* A >>= K */
			ctx->flags |= SEEN_A;
			emit_srl(r_A, r_A, k, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_RSH | BPF_X:
			ctx->flags |= SEEN_A | SEEN_X;
			emit_srlv(r_A, r_A, r_X, ctx);
			अवरोध;
		हाल BPF_ALU | BPF_NEG:
			/* A = -A */
			ctx->flags |= SEEN_A;
			emit_neg(r_A, ctx);
			अवरोध;
		हाल BPF_JMP | BPF_JA:
			/* pc += K */
			emit_b(b_imm(i + k + 1, ctx), ctx);
			emit_nop(ctx);
			अवरोध;
		हाल BPF_JMP | BPF_JEQ | BPF_K:
			/* pc += ( A == K ) ? pc->jt : pc->jf */
			condt = MIPS_COND_EQ | MIPS_COND_K;
			जाओ jmp_cmp;
		हाल BPF_JMP | BPF_JEQ | BPF_X:
			ctx->flags |= SEEN_X;
			/* pc += ( A == X ) ? pc->jt : pc->jf */
			condt = MIPS_COND_EQ | MIPS_COND_X;
			जाओ jmp_cmp;
		हाल BPF_JMP | BPF_JGE | BPF_K:
			/* pc += ( A >= K ) ? pc->jt : pc->jf */
			condt = MIPS_COND_GE | MIPS_COND_K;
			जाओ jmp_cmp;
		हाल BPF_JMP | BPF_JGE | BPF_X:
			ctx->flags |= SEEN_X;
			/* pc += ( A >= X ) ? pc->jt : pc->jf */
			condt = MIPS_COND_GE | MIPS_COND_X;
			जाओ jmp_cmp;
		हाल BPF_JMP | BPF_JGT | BPF_K:
			/* pc += ( A > K ) ? pc->jt : pc->jf */
			condt = MIPS_COND_GT | MIPS_COND_K;
			जाओ jmp_cmp;
		हाल BPF_JMP | BPF_JGT | BPF_X:
			ctx->flags |= SEEN_X;
			/* pc += ( A > X ) ? pc->jt : pc->jf */
			condt = MIPS_COND_GT | MIPS_COND_X;
jmp_cmp:
			/* Greater or Equal */
			अगर ((condt & MIPS_COND_GE) ||
			    (condt & MIPS_COND_GT)) अणु
				अगर (condt & MIPS_COND_K) अणु /* K */
					ctx->flags |= SEEN_A;
					emit_sltiu(r_s0, r_A, k, ctx);
				पूर्ण अन्यथा अणु /* X */
					ctx->flags |= SEEN_A |
						SEEN_X;
					emit_sltu(r_s0, r_A, r_X, ctx);
				पूर्ण
				/* A < (K|X) ? r_scrach = 1 */
				b_off = b_imm(i + inst->jf + 1, ctx);
				emit_bcond(MIPS_COND_NE, r_s0, r_zero, b_off,
					   ctx);
				emit_nop(ctx);
				/* A > (K|X) ? scratch = 0 */
				अगर (condt & MIPS_COND_GT) अणु
					/* Checking क्रम equality */
					ctx->flags |= SEEN_A | SEEN_X;
					अगर (condt & MIPS_COND_K)
						emit_load_imm(r_s0, k, ctx);
					अन्यथा
						emit_jit_reg_move(r_s0, r_X,
								  ctx);
					b_off = b_imm(i + inst->jf + 1, ctx);
					emit_bcond(MIPS_COND_EQ, r_A, r_s0,
						   b_off, ctx);
					emit_nop(ctx);
					/* Finally, A > K|X */
					b_off = b_imm(i + inst->jt + 1, ctx);
					emit_b(b_off, ctx);
					emit_nop(ctx);
				पूर्ण अन्यथा अणु
					/* A >= (K|X) so jump */
					b_off = b_imm(i + inst->jt + 1, ctx);
					emit_b(b_off, ctx);
					emit_nop(ctx);
				पूर्ण
			पूर्ण अन्यथा अणु
				/* A == K|X */
				अगर (condt & MIPS_COND_K) अणु /* K */
					ctx->flags |= SEEN_A;
					emit_load_imm(r_s0, k, ctx);
					/* jump true */
					b_off = b_imm(i + inst->jt + 1, ctx);
					emit_bcond(MIPS_COND_EQ, r_A, r_s0,
						   b_off, ctx);
					emit_nop(ctx);
					/* jump false */
					b_off = b_imm(i + inst->jf + 1,
						      ctx);
					emit_bcond(MIPS_COND_NE, r_A, r_s0,
						   b_off, ctx);
					emit_nop(ctx);
				पूर्ण अन्यथा अणु /* X */
					/* jump true */
					ctx->flags |= SEEN_A | SEEN_X;
					b_off = b_imm(i + inst->jt + 1,
						      ctx);
					emit_bcond(MIPS_COND_EQ, r_A, r_X,
						   b_off, ctx);
					emit_nop(ctx);
					/* jump false */
					b_off = b_imm(i + inst->jf + 1, ctx);
					emit_bcond(MIPS_COND_NE, r_A, r_X,
						   b_off, ctx);
					emit_nop(ctx);
				पूर्ण
			पूर्ण
			अवरोध;
		हाल BPF_JMP | BPF_JSET | BPF_K:
			ctx->flags |= SEEN_A;
			/* pc += (A & K) ? pc -> jt : pc -> jf */
			emit_load_imm(r_s1, k, ctx);
			emit_and(r_s0, r_A, r_s1, ctx);
			/* jump true */
			b_off = b_imm(i + inst->jt + 1, ctx);
			emit_bcond(MIPS_COND_NE, r_s0, r_zero, b_off, ctx);
			emit_nop(ctx);
			/* jump false */
			b_off = b_imm(i + inst->jf + 1, ctx);
			emit_b(b_off, ctx);
			emit_nop(ctx);
			अवरोध;
		हाल BPF_JMP | BPF_JSET | BPF_X:
			ctx->flags |= SEEN_X | SEEN_A;
			/* pc += (A & X) ? pc -> jt : pc -> jf */
			emit_and(r_s0, r_A, r_X, ctx);
			/* jump true */
			b_off = b_imm(i + inst->jt + 1, ctx);
			emit_bcond(MIPS_COND_NE, r_s0, r_zero, b_off, ctx);
			emit_nop(ctx);
			/* jump false */
			b_off = b_imm(i + inst->jf + 1, ctx);
			emit_b(b_off, ctx);
			emit_nop(ctx);
			अवरोध;
		हाल BPF_RET | BPF_A:
			ctx->flags |= SEEN_A;
			अगर (i != prog->len - 1)
				/*
				 * If this is not the last inकाष्ठाion
				 * then jump to the epilogue
				 */
				emit_b(b_imm(prog->len, ctx), ctx);
			emit_reg_move(r_ret, r_A, ctx); /* delay slot */
			अवरोध;
		हाल BPF_RET | BPF_K:
			/*
			 * It can emit two inकाष्ठाions so it करोes not fit on
			 * the delay slot.
			 */
			emit_load_imm(r_ret, k, ctx);
			अगर (i != prog->len - 1) अणु
				/*
				 * If this is not the last inकाष्ठाion
				 * then jump to the epilogue
				 */
				emit_b(b_imm(prog->len, ctx), ctx);
				emit_nop(ctx);
			पूर्ण
			अवरोध;
		हाल BPF_MISC | BPF_TAX:
			/* X = A */
			ctx->flags |= SEEN_X | SEEN_A;
			emit_jit_reg_move(r_X, r_A, ctx);
			अवरोध;
		हाल BPF_MISC | BPF_TXA:
			/* A = X */
			ctx->flags |= SEEN_A | SEEN_X;
			emit_jit_reg_move(r_A, r_X, ctx);
			अवरोध;
		/* AUX */
		हाल BPF_ANC | SKF_AD_PROTOCOL:
			/* A = ntohs(skb->protocol */
			ctx->flags |= SEEN_SKB | SEEN_OFF | SEEN_A;
			BUILD_BUG_ON(माप_field(काष्ठा sk_buff,
						  protocol) != 2);
			off = दुरत्व(काष्ठा sk_buff, protocol);
			emit_half_load(r_A, r_skb, off, ctx);
#अगर_घोषित CONFIG_CPU_LITTLE_ENDIAN
			/* This needs little endian fixup */
			अगर (cpu_has_wsbh) अणु
				/* R2 and later have the wsbh inकाष्ठाion */
				emit_wsbh(r_A, r_A, ctx);
			पूर्ण अन्यथा अणु
				/* Get first byte */
				emit_andi(r_पंचांगp_imm, r_A, 0xff, ctx);
				/* Shअगरt it */
				emit_sll(r_पंचांगp, r_पंचांगp_imm, 8, ctx);
				/* Get second byte */
				emit_srl(r_पंचांगp_imm, r_A, 8, ctx);
				emit_andi(r_पंचांगp_imm, r_पंचांगp_imm, 0xff, ctx);
				/* Put everyting together in r_A */
				emit_or(r_A, r_पंचांगp, r_पंचांगp_imm, ctx);
			पूर्ण
#पूर्ण_अगर
			अवरोध;
		हाल BPF_ANC | SKF_AD_CPU:
			ctx->flags |= SEEN_A | SEEN_OFF;
			/* A = current_thपढ़ो_info()->cpu */
			BUILD_BUG_ON(माप_field(काष्ठा thपढ़ो_info,
						  cpu) != 4);
			off = दुरत्व(काष्ठा thपढ़ो_info, cpu);
			/* $28/gp poपूर्णांकs to the thपढ़ो_info काष्ठा */
			emit_load(r_A, 28, off, ctx);
			अवरोध;
		हाल BPF_ANC | SKF_AD_IFINDEX:
			/* A = skb->dev->अगरindex */
		हाल BPF_ANC | SKF_AD_HATYPE:
			/* A = skb->dev->type */
			ctx->flags |= SEEN_SKB | SEEN_A;
			off = दुरत्व(काष्ठा sk_buff, dev);
			/* Load *dev poपूर्णांकer */
			emit_load_ptr(r_s0, r_skb, off, ctx);
			/* error (0) in the delay slot */
			emit_bcond(MIPS_COND_EQ, r_s0, r_zero,
				   b_imm(prog->len, ctx), ctx);
			emit_reg_move(r_ret, r_zero, ctx);
			अगर (code == (BPF_ANC | SKF_AD_IFINDEX)) अणु
				BUILD_BUG_ON(माप_field(काष्ठा net_device, अगरindex) != 4);
				off = दुरत्व(काष्ठा net_device, अगरindex);
				emit_load(r_A, r_s0, off, ctx);
			पूर्ण अन्यथा अणु /* (code == (BPF_ANC | SKF_AD_HATYPE) */
				BUILD_BUG_ON(माप_field(काष्ठा net_device, type) != 2);
				off = दुरत्व(काष्ठा net_device, type);
				emit_half_load_अचिन्हित(r_A, r_s0, off, ctx);
			पूर्ण
			अवरोध;
		हाल BPF_ANC | SKF_AD_MARK:
			ctx->flags |= SEEN_SKB | SEEN_A;
			BUILD_BUG_ON(माप_field(काष्ठा sk_buff, mark) != 4);
			off = दुरत्व(काष्ठा sk_buff, mark);
			emit_load(r_A, r_skb, off, ctx);
			अवरोध;
		हाल BPF_ANC | SKF_AD_RXHASH:
			ctx->flags |= SEEN_SKB | SEEN_A;
			BUILD_BUG_ON(माप_field(काष्ठा sk_buff, hash) != 4);
			off = दुरत्व(काष्ठा sk_buff, hash);
			emit_load(r_A, r_skb, off, ctx);
			अवरोध;
		हाल BPF_ANC | SKF_AD_VLAN_TAG:
			ctx->flags |= SEEN_SKB | SEEN_A;
			BUILD_BUG_ON(माप_field(काष्ठा sk_buff,
						  vlan_tci) != 2);
			off = दुरत्व(काष्ठा sk_buff, vlan_tci);
			emit_half_load_अचिन्हित(r_A, r_skb, off, ctx);
			अवरोध;
		हाल BPF_ANC | SKF_AD_VLAN_TAG_PRESENT:
			ctx->flags |= SEEN_SKB | SEEN_A;
			emit_load_byte(r_A, r_skb, PKT_VLAN_PRESENT_OFFSET(), ctx);
			अगर (PKT_VLAN_PRESENT_BIT)
				emit_srl(r_A, r_A, PKT_VLAN_PRESENT_BIT, ctx);
			अगर (PKT_VLAN_PRESENT_BIT < 7)
				emit_andi(r_A, r_A, 1, ctx);
			अवरोध;
		हाल BPF_ANC | SKF_AD_PKTTYPE:
			ctx->flags |= SEEN_SKB;

			emit_load_byte(r_पंचांगp, r_skb, PKT_TYPE_OFFSET(), ctx);
			/* Keep only the last 3 bits */
			emit_andi(r_A, r_पंचांगp, PKT_TYPE_MAX, ctx);
#अगर_घोषित __BIG_ENDIAN_BITFIELD
			/* Get the actual packet type to the lower 3 bits */
			emit_srl(r_A, r_A, 5, ctx);
#पूर्ण_अगर
			अवरोध;
		हाल BPF_ANC | SKF_AD_QUEUE:
			ctx->flags |= SEEN_SKB | SEEN_A;
			BUILD_BUG_ON(माप_field(काष्ठा sk_buff,
						  queue_mapping) != 2);
			BUILD_BUG_ON(दुरत्व(काष्ठा sk_buff,
					      queue_mapping) > 0xff);
			off = दुरत्व(काष्ठा sk_buff, queue_mapping);
			emit_half_load_अचिन्हित(r_A, r_skb, off, ctx);
			अवरोध;
		शेष:
			pr_debug("%s: Unhandled opcode: 0x%02x\n", __खाता__,
				 inst->code);
			वापस -1;
		पूर्ण
	पूर्ण

	/* compute offsets only during the first pass */
	अगर (ctx->target == शून्य)
		ctx->offsets[i] = ctx->idx * 4;

	वापस 0;
पूर्ण

व्योम bpf_jit_compile(काष्ठा bpf_prog *fp)
अणु
	काष्ठा jit_ctx ctx;
	अचिन्हित पूर्णांक alloc_size, पंचांगp_idx;

	अगर (!bpf_jit_enable)
		वापस;

	स_रखो(&ctx, 0, माप(ctx));

	ctx.offsets = kसुस्मृति(fp->len + 1, माप(*ctx.offsets), GFP_KERNEL);
	अगर (ctx.offsets == शून्य)
		वापस;

	ctx.skf = fp;

	अगर (build_body(&ctx))
		जाओ out;

	पंचांगp_idx = ctx.idx;
	build_prologue(&ctx);
	ctx.prologue_bytes = (ctx.idx - पंचांगp_idx) * 4;
	/* just to complete the ctx.idx count */
	build_epilogue(&ctx);

	alloc_size = 4 * ctx.idx;
	ctx.target = module_alloc(alloc_size);
	अगर (ctx.target == शून्य)
		जाओ out;

	/* Clean it */
	स_रखो(ctx.target, 0, alloc_size);

	ctx.idx = 0;

	/* Generate the actual JIT code */
	build_prologue(&ctx);
	build_body(&ctx);
	build_epilogue(&ctx);

	/* Update the icache */
	flush_icache_range((ptr)ctx.target, (ptr)(ctx.target + ctx.idx));

	अगर (bpf_jit_enable > 1)
		/* Dump JIT code */
		bpf_jit_dump(fp->len, alloc_size, 2, ctx.target);

	fp->bpf_func = (व्योम *)ctx.target;
	fp->jited = 1;

out:
	kमुक्त(ctx.offsets);
पूर्ण

व्योम bpf_jit_मुक्त(काष्ठा bpf_prog *fp)
अणु
	अगर (fp->jited)
		module_memमुक्त(fp->bpf_func);

	bpf_prog_unlock_मुक्त(fp);
पूर्ण
