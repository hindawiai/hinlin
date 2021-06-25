<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Just-In-Time compiler क्रम eBPF filters on 32bit ARM
 *
 * Copyright (c) 2017 Shubham Bansal <illusionist.neo@gmail.com>
 * Copyright (c) 2011 Mircea Gherzan <mgherzan@gmail.com>
 */

#समावेश <linux/bpf.h>
#समावेश <linux/bitops.h>
#समावेश <linux/compiler.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/filter.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/माला.स>
#समावेश <linux/slab.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/hwcap.h>
#समावेश <यंत्र/opcodes.h>
#समावेश <यंत्र/प्रणाली_info.h>

#समावेश "bpf_jit_32.h"

/*
 * eBPF prog stack layout:
 *
 *                         high
 * original ARM_SP =>     +-----+
 *                        |     | callee saved रेजिस्टरs
 *                        +-----+ <= (BPF_FP + SCRATCH_SIZE)
 *                        | ... | eBPF JIT scratch space
 * eBPF fp रेजिस्टर =>    +-----+
 *   (BPF_FP)             | ... | eBPF prog stack
 *                        +-----+
 *                        |RSVD | JIT scratchpad
 * current ARM_SP =>      +-----+ <= (BPF_FP - STACK_SIZE + SCRATCH_SIZE)
 *                        |     |
 *                        | ... | Function call stack
 *                        |     |
 *                        +-----+
 *                          low
 *
 * The callee saved रेजिस्टरs depends on whether frame poपूर्णांकers are enabled.
 * With frame poपूर्णांकers (to be compliant with the ABI):
 *
 *                              high
 * original ARM_SP =>     +--------------+ \
 *                        |      pc      | |
 * current ARM_FP =>      +--------------+ पूर्ण callee saved रेजिस्टरs
 *                        |r4-r9,fp,ip,lr| |
 *                        +--------------+ /
 *                              low
 *
 * Without frame poपूर्णांकers:
 *
 *                              high
 * original ARM_SP =>     +--------------+
 *                        |  r4-r9,fp,lr | callee saved रेजिस्टरs
 * current ARM_FP =>      +--------------+
 *                              low
 *
 * When popping रेजिस्टरs off the stack at the end of a BPF function, we
 * reference them via the current ARM_FP रेजिस्टर.
 */
#घोषणा CALLEE_MASK	(1 << ARM_R4 | 1 << ARM_R5 | 1 << ARM_R6 | \
			 1 << ARM_R7 | 1 << ARM_R8 | 1 << ARM_R9 | \
			 1 << ARM_FP)
#घोषणा CALLEE_PUSH_MASK (CALLEE_MASK | 1 << ARM_LR)
#घोषणा CALLEE_POP_MASK  (CALLEE_MASK | 1 << ARM_PC)

क्रमागत अणु
	/* Stack layout - these are offsets from (top of stack - 4) */
	BPF_R2_HI,
	BPF_R2_LO,
	BPF_R3_HI,
	BPF_R3_LO,
	BPF_R4_HI,
	BPF_R4_LO,
	BPF_R5_HI,
	BPF_R5_LO,
	BPF_R7_HI,
	BPF_R7_LO,
	BPF_R8_HI,
	BPF_R8_LO,
	BPF_R9_HI,
	BPF_R9_LO,
	BPF_FP_HI,
	BPF_FP_LO,
	BPF_TC_HI,
	BPF_TC_LO,
	BPF_AX_HI,
	BPF_AX_LO,
	/* Stack space क्रम BPF_REG_2, BPF_REG_3, BPF_REG_4,
	 * BPF_REG_5, BPF_REG_7, BPF_REG_8, BPF_REG_9,
	 * BPF_REG_FP and Tail call counts.
	 */
	BPF_JIT_SCRATCH_REGS,
पूर्ण;

/*
 * Negative "register" values indicate the रेजिस्टर is stored on the stack
 * and are the offset from the top of the eBPF JIT scratch space.
 */
#घोषणा STACK_OFFSET(k)	(-4 - (k) * 4)
#घोषणा SCRATCH_SIZE	(BPF_JIT_SCRATCH_REGS * 4)

#अगर_घोषित CONFIG_FRAME_POINTER
#घोषणा EBPF_SCRATCH_TO_ARM_FP(x) ((x) - 4 * hweight16(CALLEE_PUSH_MASK) - 4)
#अन्यथा
#घोषणा EBPF_SCRATCH_TO_ARM_FP(x) (x)
#पूर्ण_अगर

#घोषणा TMP_REG_1	(MAX_BPF_JIT_REG + 0)	/* TEMP Register 1 */
#घोषणा TMP_REG_2	(MAX_BPF_JIT_REG + 1)	/* TEMP Register 2 */
#घोषणा TCALL_CNT	(MAX_BPF_JIT_REG + 2)	/* Tail Call Count */

#घोषणा FLAG_IMM_OVERFLOW	(1 << 0)

/*
 * Map eBPF रेजिस्टरs to ARM 32bit रेजिस्टरs or stack scratch space.
 *
 * 1. First argument is passed using the arm 32bit रेजिस्टरs and rest of the
 * arguments are passed on stack scratch space.
 * 2. First callee-saved argument is mapped to arm 32 bit रेजिस्टरs and rest
 * arguments are mapped to scratch space on stack.
 * 3. We need two 64 bit temp रेजिस्टरs to करो complex operations on eBPF
 * रेजिस्टरs.
 *
 * As the eBPF रेजिस्टरs are all 64 bit रेजिस्टरs and arm has only 32 bit
 * रेजिस्टरs, we have to map each eBPF रेजिस्टरs with two arm 32 bit regs or
 * scratch memory space and we have to build eBPF 64 bit रेजिस्टर from those.
 *
 */
अटल स्थिर s8 bpf2a32[][2] = अणु
	/* वापस value from in-kernel function, and निकास value from eBPF */
	[BPF_REG_0] = अणुARM_R1, ARM_R0पूर्ण,
	/* arguments from eBPF program to in-kernel function */
	[BPF_REG_1] = अणुARM_R3, ARM_R2पूर्ण,
	/* Stored on stack scratch space */
	[BPF_REG_2] = अणुSTACK_OFFSET(BPF_R2_HI), STACK_OFFSET(BPF_R2_LO)पूर्ण,
	[BPF_REG_3] = अणुSTACK_OFFSET(BPF_R3_HI), STACK_OFFSET(BPF_R3_LO)पूर्ण,
	[BPF_REG_4] = अणुSTACK_OFFSET(BPF_R4_HI), STACK_OFFSET(BPF_R4_LO)पूर्ण,
	[BPF_REG_5] = अणुSTACK_OFFSET(BPF_R5_HI), STACK_OFFSET(BPF_R5_LO)पूर्ण,
	/* callee saved रेजिस्टरs that in-kernel function will preserve */
	[BPF_REG_6] = अणुARM_R5, ARM_R4पूर्ण,
	/* Stored on stack scratch space */
	[BPF_REG_7] = अणुSTACK_OFFSET(BPF_R7_HI), STACK_OFFSET(BPF_R7_LO)पूर्ण,
	[BPF_REG_8] = अणुSTACK_OFFSET(BPF_R8_HI), STACK_OFFSET(BPF_R8_LO)पूर्ण,
	[BPF_REG_9] = अणुSTACK_OFFSET(BPF_R9_HI), STACK_OFFSET(BPF_R9_LO)पूर्ण,
	/* Read only Frame Poपूर्णांकer to access Stack */
	[BPF_REG_FP] = अणुSTACK_OFFSET(BPF_FP_HI), STACK_OFFSET(BPF_FP_LO)पूर्ण,
	/* Temporary Register क्रम पूर्णांकernal BPF JIT, can be used
	 * क्रम स्थिरant blindings and others.
	 */
	[TMP_REG_1] = अणुARM_R7, ARM_R6पूर्ण,
	[TMP_REG_2] = अणुARM_R9, ARM_R8पूर्ण,
	/* Tail call count. Stored on stack scratch space. */
	[TCALL_CNT] = अणुSTACK_OFFSET(BPF_TC_HI), STACK_OFFSET(BPF_TC_LO)पूर्ण,
	/* temporary रेजिस्टर क्रम blinding स्थिरants.
	 * Stored on stack scratch space.
	 */
	[BPF_REG_AX] = अणुSTACK_OFFSET(BPF_AX_HI), STACK_OFFSET(BPF_AX_LO)पूर्ण,
पूर्ण;

#घोषणा	dst_lo	dst[1]
#घोषणा dst_hi	dst[0]
#घोषणा src_lo	src[1]
#घोषणा src_hi	src[0]

/*
 * JIT Context:
 *
 * prog			:	bpf_prog
 * idx			:	index of current last JITed inकाष्ठाion.
 * prologue_bytes	:	bytes used in prologue.
 * epilogue_offset	:	offset of epilogue starting.
 * offsets		:	array of eBPF inकाष्ठाion offsets in
 *				JITed code.
 * target		:	final JITed code.
 * epilogue_bytes	:	no of bytes used in epilogue.
 * imm_count		:	no of immediate counts used क्रम global
 *				variables.
 * imms			:	array of global variable addresses.
 */

काष्ठा jit_ctx अणु
	स्थिर काष्ठा bpf_prog *prog;
	अचिन्हित पूर्णांक idx;
	अचिन्हित पूर्णांक prologue_bytes;
	अचिन्हित पूर्णांक epilogue_offset;
	अचिन्हित पूर्णांक cpu_architecture;
	u32 flags;
	u32 *offsets;
	u32 *target;
	u32 stack_size;
#अगर __LINUX_ARM_ARCH__ < 7
	u16 epilogue_bytes;
	u16 imm_count;
	u32 *imms;
#पूर्ण_अगर
पूर्ण;

/*
 * Wrappers which handle both OABI and EABI and assures Thumb2 पूर्णांकerworking
 * (where the assembly routines like __aeabi_uiभाग could cause problems).
 */
अटल u32 jit_uभाग32(u32 भागidend, u32 भागisor)
अणु
	वापस भागidend / भागisor;
पूर्ण

अटल u32 jit_mod32(u32 भागidend, u32 भागisor)
अणु
	वापस भागidend % भागisor;
पूर्ण

अटल अंतरभूत व्योम _emit(पूर्णांक cond, u32 inst, काष्ठा jit_ctx *ctx)
अणु
	inst |= (cond << 28);
	inst = __opcode_to_mem_arm(inst);

	अगर (ctx->target != शून्य)
		ctx->target[ctx->idx] = inst;

	ctx->idx++;
पूर्ण

/*
 * Emit an inकाष्ठाion that will be executed unconditionally.
 */
अटल अंतरभूत व्योम emit(u32 inst, काष्ठा jit_ctx *ctx)
अणु
	_emit(ARM_COND_AL, inst, ctx);
पूर्ण

/*
 * This is rather horrid, but necessary to convert an पूर्णांकeger स्थिरant
 * to an immediate opeअक्रम क्रम the opcodes, and be able to detect at
 * build समय whether the स्थिरant can't be converted (iow, usable in
 * BUILD_BUG_ON()).
 */
#घोषणा imm12val(v, s) (rol32(v, (s)) | (s) << 7)
#घोषणा स्थिर_imm8m(x)					\
	(अणु पूर्णांक r;					\
	   u32 v = (x);					\
	   अगर (!(v & ~0x000000ff))			\
		r = imm12val(v, 0);			\
	   अन्यथा अगर (!(v & ~0xc000003f))			\
		r = imm12val(v, 2);			\
	   अन्यथा अगर (!(v & ~0xf000000f))			\
		r = imm12val(v, 4);			\
	   अन्यथा अगर (!(v & ~0xfc000003))			\
		r = imm12val(v, 6);			\
	   अन्यथा अगर (!(v & ~0xff000000))			\
		r = imm12val(v, 8);			\
	   अन्यथा अगर (!(v & ~0x3fc00000))			\
		r = imm12val(v, 10);			\
	   अन्यथा अगर (!(v & ~0x0ff00000))			\
		r = imm12val(v, 12);			\
	   अन्यथा अगर (!(v & ~0x03fc0000))			\
		r = imm12val(v, 14);			\
	   अन्यथा अगर (!(v & ~0x00ff0000))			\
		r = imm12val(v, 16);			\
	   अन्यथा अगर (!(v & ~0x003fc000))			\
		r = imm12val(v, 18);			\
	   अन्यथा अगर (!(v & ~0x000ff000))			\
		r = imm12val(v, 20);			\
	   अन्यथा अगर (!(v & ~0x0003fc00))			\
		r = imm12val(v, 22);			\
	   अन्यथा अगर (!(v & ~0x0000ff00))			\
		r = imm12val(v, 24);			\
	   अन्यथा अगर (!(v & ~0x00003fc0))			\
		r = imm12val(v, 26);			\
	   अन्यथा अगर (!(v & ~0x00000ff0))			\
		r = imm12val(v, 28);			\
	   अन्यथा अगर (!(v & ~0x000003fc))			\
		r = imm12val(v, 30);			\
	   अन्यथा						\
		r = -1;					\
	   r; पूर्ण)

/*
 * Checks अगर immediate value can be converted to imm12(12 bits) value.
 */
अटल पूर्णांक imm8m(u32 x)
अणु
	u32 rot;

	क्रम (rot = 0; rot < 16; rot++)
		अगर ((x & ~ror32(0xff, 2 * rot)) == 0)
			वापस rol32(x, 2 * rot) | (rot << 8);
	वापस -1;
पूर्ण

#घोषणा imm8m(x) (__builtin_स्थिरant_p(x) ? स्थिर_imm8m(x) : imm8m(x))

अटल u32 arm_bpf_ldst_imm12(u32 op, u8 rt, u8 rn, s16 imm12)
अणु
	op |= rt << 12 | rn << 16;
	अगर (imm12 >= 0)
		op |= ARM_INST_LDST__U;
	अन्यथा
		imm12 = -imm12;
	वापस op | (imm12 & ARM_INST_LDST__IMM12);
पूर्ण

अटल u32 arm_bpf_ldst_imm8(u32 op, u8 rt, u8 rn, s16 imm8)
अणु
	op |= rt << 12 | rn << 16;
	अगर (imm8 >= 0)
		op |= ARM_INST_LDST__U;
	अन्यथा
		imm8 = -imm8;
	वापस op | (imm8 & 0xf0) << 4 | (imm8 & 0x0f);
पूर्ण

#घोषणा ARM_LDR_I(rt, rn, off)	arm_bpf_ldst_imm12(ARM_INST_LDR_I, rt, rn, off)
#घोषणा ARM_LDRB_I(rt, rn, off)	arm_bpf_ldst_imm12(ARM_INST_LDRB_I, rt, rn, off)
#घोषणा ARM_LDRD_I(rt, rn, off)	arm_bpf_ldst_imm8(ARM_INST_LDRD_I, rt, rn, off)
#घोषणा ARM_LDRH_I(rt, rn, off)	arm_bpf_ldst_imm8(ARM_INST_LDRH_I, rt, rn, off)

#घोषणा ARM_STR_I(rt, rn, off)	arm_bpf_ldst_imm12(ARM_INST_STR_I, rt, rn, off)
#घोषणा ARM_STRB_I(rt, rn, off)	arm_bpf_ldst_imm12(ARM_INST_STRB_I, rt, rn, off)
#घोषणा ARM_STRD_I(rt, rn, off)	arm_bpf_ldst_imm8(ARM_INST_STRD_I, rt, rn, off)
#घोषणा ARM_STRH_I(rt, rn, off)	arm_bpf_ldst_imm8(ARM_INST_STRH_I, rt, rn, off)

/*
 * Initializes the JIT space with undefined inकाष्ठाions.
 */
अटल व्योम jit_fill_hole(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	u32 *ptr;
	/* We are guaranteed to have aligned memory. */
	क्रम (ptr = area; size >= माप(u32); size -= माप(u32))
		*ptr++ = __opcode_to_mem_arm(ARM_INST_UDF);
पूर्ण

#अगर defined(CONFIG_AEABI) && (__LINUX_ARM_ARCH__ >= 5)
/* EABI requires the stack to be aligned to 64-bit boundaries */
#घोषणा STACK_ALIGNMENT	8
#अन्यथा
/* Stack must be aligned to 32-bit boundaries */
#घोषणा STACK_ALIGNMENT	4
#पूर्ण_अगर

/* total stack size used in JITed code */
#घोषणा _STACK_SIZE	(ctx->prog->aux->stack_depth + SCRATCH_SIZE)
#घोषणा STACK_SIZE	ALIGN(_STACK_SIZE, STACK_ALIGNMENT)

#अगर __LINUX_ARM_ARCH__ < 7

अटल u16 imm_offset(u32 k, काष्ठा jit_ctx *ctx)
अणु
	अचिन्हित पूर्णांक i = 0, offset;
	u16 imm;

	/* on the "fake" run we just count them (duplicates included) */
	अगर (ctx->target == शून्य) अणु
		ctx->imm_count++;
		वापस 0;
	पूर्ण

	जबतक ((i < ctx->imm_count) && ctx->imms[i]) अणु
		अगर (ctx->imms[i] == k)
			अवरोध;
		i++;
	पूर्ण

	अगर (ctx->imms[i] == 0)
		ctx->imms[i] = k;

	/* स्थिरants go just after the epilogue */
	offset =  ctx->offsets[ctx->prog->len - 1] * 4;
	offset += ctx->prologue_bytes;
	offset += ctx->epilogue_bytes;
	offset += i * 4;

	ctx->target[offset / 4] = k;

	/* PC in ARM mode == address of the inकाष्ठाion + 8 */
	imm = offset - (8 + ctx->idx * 4);

	अगर (imm & ~0xfff) अणु
		/*
		 * literal pool is too far, संकेत it पूर्णांकo flags. we
		 * can only detect it on the second pass unक्रमtunately.
		 */
		ctx->flags |= FLAG_IMM_OVERFLOW;
		वापस 0;
	पूर्ण

	वापस imm;
पूर्ण

#पूर्ण_अगर /* __LINUX_ARM_ARCH__ */

अटल अंतरभूत पूर्णांक bpf2a32_offset(पूर्णांक bpf_to, पूर्णांक bpf_from,
				 स्थिर काष्ठा jit_ctx *ctx) अणु
	पूर्णांक to, from;

	अगर (ctx->target == शून्य)
		वापस 0;
	to = ctx->offsets[bpf_to];
	from = ctx->offsets[bpf_from];

	वापस to - from - 1;
पूर्ण

/*
 * Move an immediate that's not an imm8m to a core रेजिस्टर.
 */
अटल अंतरभूत व्योम emit_mov_i_no8m(स्थिर u8 rd, u32 val, काष्ठा jit_ctx *ctx)
अणु
#अगर __LINUX_ARM_ARCH__ < 7
	emit(ARM_LDR_I(rd, ARM_PC, imm_offset(val, ctx)), ctx);
#अन्यथा
	emit(ARM_MOVW(rd, val & 0xffff), ctx);
	अगर (val > 0xffff)
		emit(ARM_MOVT(rd, val >> 16), ctx);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत व्योम emit_mov_i(स्थिर u8 rd, u32 val, काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक imm12 = imm8m(val);

	अगर (imm12 >= 0)
		emit(ARM_MOV_I(rd, imm12), ctx);
	अन्यथा
		emit_mov_i_no8m(rd, val, ctx);
पूर्ण

अटल व्योम emit_bx_r(u8 tgt_reg, काष्ठा jit_ctx *ctx)
अणु
	अगर (elf_hwcap & HWCAP_THUMB)
		emit(ARM_BX(tgt_reg), ctx);
	अन्यथा
		emit(ARM_MOV_R(ARM_PC, tgt_reg), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_blx_r(u8 tgt_reg, काष्ठा jit_ctx *ctx)
अणु
#अगर __LINUX_ARM_ARCH__ < 5
	emit(ARM_MOV_R(ARM_LR, ARM_PC), ctx);
	emit_bx_r(tgt_reg, ctx);
#अन्यथा
	emit(ARM_BLX_R(tgt_reg), ctx);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत पूर्णांक epilogue_offset(स्थिर काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक to, from;
	/* No need क्रम 1st dummy run */
	अगर (ctx->target == शून्य)
		वापस 0;
	to = ctx->epilogue_offset;
	from = ctx->idx;

	वापस to - from - 2;
पूर्ण

अटल अंतरभूत व्योम emit_uभागmod(u8 rd, u8 rm, u8 rn, काष्ठा jit_ctx *ctx, u8 op)
अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];

#अगर __LINUX_ARM_ARCH__ == 7
	अगर (elf_hwcap & HWCAP_IDIVA) अणु
		अगर (op == BPF_DIV)
			emit(ARM_UDIV(rd, rm, rn), ctx);
		अन्यथा अणु
			emit(ARM_UDIV(ARM_IP, rm, rn), ctx);
			emit(ARM_MLS(rd, rn, ARM_IP, rm), ctx);
		पूर्ण
		वापस;
	पूर्ण
#पूर्ण_अगर

	/*
	 * For BPF_ALU | BPF_DIV | BPF_K inकाष्ठाions
	 * As ARM_R1 and ARM_R0 contains 1st argument of bpf
	 * function, we need to save it on caller side to save
	 * it from getting destroyed within callee.
	 * After the वापस from the callee, we restore ARM_R0
	 * ARM_R1.
	 */
	अगर (rn != ARM_R1) अणु
		emit(ARM_MOV_R(पंचांगp[0], ARM_R1), ctx);
		emit(ARM_MOV_R(ARM_R1, rn), ctx);
	पूर्ण
	अगर (rm != ARM_R0) अणु
		emit(ARM_MOV_R(पंचांगp[1], ARM_R0), ctx);
		emit(ARM_MOV_R(ARM_R0, rm), ctx);
	पूर्ण

	/* Call appropriate function */
	emit_mov_i(ARM_IP, op == BPF_DIV ?
		   (u32)jit_uभाग32 : (u32)jit_mod32, ctx);
	emit_blx_r(ARM_IP, ctx);

	/* Save वापस value */
	अगर (rd != ARM_R0)
		emit(ARM_MOV_R(rd, ARM_R0), ctx);

	/* Restore ARM_R0 and ARM_R1 */
	अगर (rn != ARM_R1)
		emit(ARM_MOV_R(ARM_R1, पंचांगp[0]), ctx);
	अगर (rm != ARM_R0)
		emit(ARM_MOV_R(ARM_R0, पंचांगp[1]), ctx);
पूर्ण

/* Is the translated BPF रेजिस्टर on stack? */
अटल bool is_stacked(s8 reg)
अणु
	वापस reg < 0;
पूर्ण

/* If a BPF रेजिस्टर is on the stack (stk is true), load it to the
 * supplied temporary रेजिस्टर and वापस the temporary रेजिस्टर
 * क्रम subsequent operations, otherwise just use the CPU रेजिस्टर.
 */
अटल s8 arm_bpf_get_reg32(s8 reg, s8 पंचांगp, काष्ठा jit_ctx *ctx)
अणु
	अगर (is_stacked(reg)) अणु
		emit(ARM_LDR_I(पंचांगp, ARM_FP, EBPF_SCRATCH_TO_ARM_FP(reg)), ctx);
		reg = पंचांगp;
	पूर्ण
	वापस reg;
पूर्ण

अटल स्थिर s8 *arm_bpf_get_reg64(स्थिर s8 *reg, स्थिर s8 *पंचांगp,
				   काष्ठा jit_ctx *ctx)
अणु
	अगर (is_stacked(reg[1])) अणु
		अगर (__LINUX_ARM_ARCH__ >= 6 ||
		    ctx->cpu_architecture >= CPU_ARCH_ARMv5TE) अणु
			emit(ARM_LDRD_I(पंचांगp[1], ARM_FP,
					EBPF_SCRATCH_TO_ARM_FP(reg[1])), ctx);
		पूर्ण अन्यथा अणु
			emit(ARM_LDR_I(पंचांगp[1], ARM_FP,
				       EBPF_SCRATCH_TO_ARM_FP(reg[1])), ctx);
			emit(ARM_LDR_I(पंचांगp[0], ARM_FP,
				       EBPF_SCRATCH_TO_ARM_FP(reg[0])), ctx);
		पूर्ण
		reg = पंचांगp;
	पूर्ण
	वापस reg;
पूर्ण

/* If a BPF रेजिस्टर is on the stack (stk is true), save the रेजिस्टर
 * back to the stack.  If the source रेजिस्टर is not the same, then
 * move it पूर्णांकo the correct रेजिस्टर.
 */
अटल व्योम arm_bpf_put_reg32(s8 reg, s8 src, काष्ठा jit_ctx *ctx)
अणु
	अगर (is_stacked(reg))
		emit(ARM_STR_I(src, ARM_FP, EBPF_SCRATCH_TO_ARM_FP(reg)), ctx);
	अन्यथा अगर (reg != src)
		emit(ARM_MOV_R(reg, src), ctx);
पूर्ण

अटल व्योम arm_bpf_put_reg64(स्थिर s8 *reg, स्थिर s8 *src,
			      काष्ठा jit_ctx *ctx)
अणु
	अगर (is_stacked(reg[1])) अणु
		अगर (__LINUX_ARM_ARCH__ >= 6 ||
		    ctx->cpu_architecture >= CPU_ARCH_ARMv5TE) अणु
			emit(ARM_STRD_I(src[1], ARM_FP,
				       EBPF_SCRATCH_TO_ARM_FP(reg[1])), ctx);
		पूर्ण अन्यथा अणु
			emit(ARM_STR_I(src[1], ARM_FP,
				       EBPF_SCRATCH_TO_ARM_FP(reg[1])), ctx);
			emit(ARM_STR_I(src[0], ARM_FP,
				       EBPF_SCRATCH_TO_ARM_FP(reg[0])), ctx);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (reg[1] != src[1])
			emit(ARM_MOV_R(reg[1], src[1]), ctx);
		अगर (reg[0] != src[0])
			emit(ARM_MOV_R(reg[0], src[0]), ctx);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम emit_a32_mov_i(स्थिर s8 dst, स्थिर u32 val,
				  काष्ठा jit_ctx *ctx)
अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];

	अगर (is_stacked(dst)) अणु
		emit_mov_i(पंचांगp[1], val, ctx);
		arm_bpf_put_reg32(dst, पंचांगp[1], ctx);
	पूर्ण अन्यथा अणु
		emit_mov_i(dst, val, ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_a32_mov_i64(स्थिर s8 dst[], u64 val, काष्ठा jit_ctx *ctx)
अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *rd = is_stacked(dst_lo) ? पंचांगp : dst;

	emit_mov_i(rd[1], (u32)val, ctx);
	emit_mov_i(rd[0], val >> 32, ctx);

	arm_bpf_put_reg64(dst, rd, ctx);
पूर्ण

/* Sign extended move */
अटल अंतरभूत व्योम emit_a32_mov_se_i64(स्थिर bool is64, स्थिर s8 dst[],
				       स्थिर u32 val, काष्ठा jit_ctx *ctx) अणु
	u64 val64 = val;

	अगर (is64 && (val & (1<<31)))
		val64 |= 0xffffffff00000000ULL;
	emit_a32_mov_i64(dst, val64, ctx);
पूर्ण

अटल अंतरभूत व्योम emit_a32_add_r(स्थिर u8 dst, स्थिर u8 src,
			      स्थिर bool is64, स्थिर bool hi,
			      काष्ठा jit_ctx *ctx) अणु
	/* 64 bit :
	 *	adds dst_lo, dst_lo, src_lo
	 *	adc dst_hi, dst_hi, src_hi
	 * 32 bit :
	 *	add dst_lo, dst_lo, src_lo
	 */
	अगर (!hi && is64)
		emit(ARM_ADDS_R(dst, dst, src), ctx);
	अन्यथा अगर (hi && is64)
		emit(ARM_ADC_R(dst, dst, src), ctx);
	अन्यथा
		emit(ARM_ADD_R(dst, dst, src), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_a32_sub_r(स्थिर u8 dst, स्थिर u8 src,
				  स्थिर bool is64, स्थिर bool hi,
				  काष्ठा jit_ctx *ctx) अणु
	/* 64 bit :
	 *	subs dst_lo, dst_lo, src_lo
	 *	sbc dst_hi, dst_hi, src_hi
	 * 32 bit :
	 *	sub dst_lo, dst_lo, src_lo
	 */
	अगर (!hi && is64)
		emit(ARM_SUBS_R(dst, dst, src), ctx);
	अन्यथा अगर (hi && is64)
		emit(ARM_SBC_R(dst, dst, src), ctx);
	अन्यथा
		emit(ARM_SUB_R(dst, dst, src), ctx);
पूर्ण

अटल अंतरभूत व्योम emit_alu_r(स्थिर u8 dst, स्थिर u8 src, स्थिर bool is64,
			      स्थिर bool hi, स्थिर u8 op, काष्ठा jit_ctx *ctx)अणु
	चयन (BPF_OP(op)) अणु
	/* dst = dst + src */
	हाल BPF_ADD:
		emit_a32_add_r(dst, src, is64, hi, ctx);
		अवरोध;
	/* dst = dst - src */
	हाल BPF_SUB:
		emit_a32_sub_r(dst, src, is64, hi, ctx);
		अवरोध;
	/* dst = dst | src */
	हाल BPF_OR:
		emit(ARM_ORR_R(dst, dst, src), ctx);
		अवरोध;
	/* dst = dst & src */
	हाल BPF_AND:
		emit(ARM_AND_R(dst, dst, src), ctx);
		अवरोध;
	/* dst = dst ^ src */
	हाल BPF_XOR:
		emit(ARM_EOR_R(dst, dst, src), ctx);
		अवरोध;
	/* dst = dst * src */
	हाल BPF_MUL:
		emit(ARM_MUL(dst, dst, src), ctx);
		अवरोध;
	/* dst = dst << src */
	हाल BPF_LSH:
		emit(ARM_LSL_R(dst, dst, src), ctx);
		अवरोध;
	/* dst = dst >> src */
	हाल BPF_RSH:
		emit(ARM_LSR_R(dst, dst, src), ctx);
		अवरोध;
	/* dst = dst >> src (चिन्हित)*/
	हाल BPF_ARSH:
		emit(ARM_MOV_SR(dst, dst, SRTYPE_ASR, src), ctx);
		अवरोध;
	पूर्ण
पूर्ण

/* ALU operation (32 bit)
 * dst = dst (op) src
 */
अटल अंतरभूत व्योम emit_a32_alu_r(स्थिर s8 dst, स्थिर s8 src,
				  काष्ठा jit_ctx *ctx, स्थिर bool is64,
				  स्थिर bool hi, स्थिर u8 op) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	s8 rn, rd;

	rn = arm_bpf_get_reg32(src, पंचांगp[1], ctx);
	rd = arm_bpf_get_reg32(dst, पंचांगp[0], ctx);
	/* ALU operation */
	emit_alu_r(rd, rn, is64, hi, op, ctx);
	arm_bpf_put_reg32(dst, rd, ctx);
पूर्ण

/* ALU operation (64 bit) */
अटल अंतरभूत व्योम emit_a32_alu_r64(स्थिर bool is64, स्थिर s8 dst[],
				  स्थिर s8 src[], काष्ठा jit_ctx *ctx,
				  स्थिर u8 op) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rd;

	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);
	अगर (is64) अणु
		स्थिर s8 *rs;

		rs = arm_bpf_get_reg64(src, पंचांगp2, ctx);

		/* ALU operation */
		emit_alu_r(rd[1], rs[1], true, false, op, ctx);
		emit_alu_r(rd[0], rs[0], true, true, op, ctx);
	पूर्ण अन्यथा अणु
		s8 rs;

		rs = arm_bpf_get_reg32(src_lo, पंचांगp2[1], ctx);

		/* ALU operation */
		emit_alu_r(rd[1], rs, true, false, op, ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit_a32_mov_i(rd[0], 0, ctx);
	पूर्ण

	arm_bpf_put_reg64(dst, rd, ctx);
पूर्ण

/* dst = src (4 bytes)*/
अटल अंतरभूत व्योम emit_a32_mov_r(स्थिर s8 dst, स्थिर s8 src,
				  काष्ठा jit_ctx *ctx) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	s8 rt;

	rt = arm_bpf_get_reg32(src, पंचांगp[0], ctx);
	arm_bpf_put_reg32(dst, rt, ctx);
पूर्ण

/* dst = src */
अटल अंतरभूत व्योम emit_a32_mov_r64(स्थिर bool is64, स्थिर s8 dst[],
				  स्थिर s8 src[],
				  काष्ठा jit_ctx *ctx) अणु
	अगर (!is64) अणु
		emit_a32_mov_r(dst_lo, src_lo, ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			/* Zero out high 4 bytes */
			emit_a32_mov_i(dst_hi, 0, ctx);
	पूर्ण अन्यथा अगर (__LINUX_ARM_ARCH__ < 6 &&
		   ctx->cpu_architecture < CPU_ARCH_ARMv5TE) अणु
		/* complete 8 byte move */
		emit_a32_mov_r(dst_lo, src_lo, ctx);
		emit_a32_mov_r(dst_hi, src_hi, ctx);
	पूर्ण अन्यथा अगर (is_stacked(src_lo) && is_stacked(dst_lo)) अणु
		स्थिर u8 *पंचांगp = bpf2a32[TMP_REG_1];

		emit(ARM_LDRD_I(पंचांगp[1], ARM_FP, EBPF_SCRATCH_TO_ARM_FP(src_lo)), ctx);
		emit(ARM_STRD_I(पंचांगp[1], ARM_FP, EBPF_SCRATCH_TO_ARM_FP(dst_lo)), ctx);
	पूर्ण अन्यथा अगर (is_stacked(src_lo)) अणु
		emit(ARM_LDRD_I(dst[1], ARM_FP, EBPF_SCRATCH_TO_ARM_FP(src_lo)), ctx);
	पूर्ण अन्यथा अगर (is_stacked(dst_lo)) अणु
		emit(ARM_STRD_I(src[1], ARM_FP, EBPF_SCRATCH_TO_ARM_FP(dst_lo)), ctx);
	पूर्ण अन्यथा अणु
		emit(ARM_MOV_R(dst[0], src[0]), ctx);
		emit(ARM_MOV_R(dst[1], src[1]), ctx);
	पूर्ण
पूर्ण

/* Shअगरt operations */
अटल अंतरभूत व्योम emit_a32_alu_i(स्थिर s8 dst, स्थिर u32 val,
				काष्ठा jit_ctx *ctx, स्थिर u8 op) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	s8 rd;

	rd = arm_bpf_get_reg32(dst, पंचांगp[0], ctx);

	/* Do shअगरt operation */
	चयन (op) अणु
	हाल BPF_LSH:
		emit(ARM_LSL_I(rd, rd, val), ctx);
		अवरोध;
	हाल BPF_RSH:
		emit(ARM_LSR_I(rd, rd, val), ctx);
		अवरोध;
	हाल BPF_ARSH:
		emit(ARM_ASR_I(rd, rd, val), ctx);
		अवरोध;
	हाल BPF_NEG:
		emit(ARM_RSB_I(rd, rd, val), ctx);
		अवरोध;
	पूर्ण

	arm_bpf_put_reg32(dst, rd, ctx);
पूर्ण

/* dst = ~dst (64 bit) */
अटल अंतरभूत व्योम emit_a32_neg64(स्थिर s8 dst[],
				काष्ठा jit_ctx *ctx)अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *rd;

	/* Setup Opeअक्रम */
	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);

	/* Do Negate Operation */
	emit(ARM_RSBS_I(rd[1], rd[1], 0), ctx);
	emit(ARM_RSC_I(rd[0], rd[0], 0), ctx);

	arm_bpf_put_reg64(dst, rd, ctx);
पूर्ण

/* dst = dst << src */
अटल अंतरभूत व्योम emit_a32_lsh_r64(स्थिर s8 dst[], स्थिर s8 src[],
				    काष्ठा jit_ctx *ctx) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rd;
	s8 rt;

	/* Setup Opeअक्रमs */
	rt = arm_bpf_get_reg32(src_lo, पंचांगp2[1], ctx);
	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);

	/* Do LSH operation */
	emit(ARM_SUB_I(ARM_IP, rt, 32), ctx);
	emit(ARM_RSB_I(पंचांगp2[0], rt, 32), ctx);
	emit(ARM_MOV_SR(ARM_LR, rd[0], SRTYPE_ASL, rt), ctx);
	emit(ARM_ORR_SR(ARM_LR, ARM_LR, rd[1], SRTYPE_ASL, ARM_IP), ctx);
	emit(ARM_ORR_SR(ARM_IP, ARM_LR, rd[1], SRTYPE_LSR, पंचांगp2[0]), ctx);
	emit(ARM_MOV_SR(ARM_LR, rd[1], SRTYPE_ASL, rt), ctx);

	arm_bpf_put_reg32(dst_lo, ARM_LR, ctx);
	arm_bpf_put_reg32(dst_hi, ARM_IP, ctx);
पूर्ण

/* dst = dst >> src (चिन्हित)*/
अटल अंतरभूत व्योम emit_a32_arsh_r64(स्थिर s8 dst[], स्थिर s8 src[],
				     काष्ठा jit_ctx *ctx) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rd;
	s8 rt;

	/* Setup Opeअक्रमs */
	rt = arm_bpf_get_reg32(src_lo, पंचांगp2[1], ctx);
	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);

	/* Do the ARSH operation */
	emit(ARM_RSB_I(ARM_IP, rt, 32), ctx);
	emit(ARM_SUBS_I(पंचांगp2[0], rt, 32), ctx);
	emit(ARM_MOV_SR(ARM_LR, rd[1], SRTYPE_LSR, rt), ctx);
	emit(ARM_ORR_SR(ARM_LR, ARM_LR, rd[0], SRTYPE_ASL, ARM_IP), ctx);
	_emit(ARM_COND_PL,
	      ARM_ORR_SR(ARM_LR, ARM_LR, rd[0], SRTYPE_ASR, पंचांगp2[0]), ctx);
	emit(ARM_MOV_SR(ARM_IP, rd[0], SRTYPE_ASR, rt), ctx);

	arm_bpf_put_reg32(dst_lo, ARM_LR, ctx);
	arm_bpf_put_reg32(dst_hi, ARM_IP, ctx);
पूर्ण

/* dst = dst >> src */
अटल अंतरभूत व्योम emit_a32_rsh_r64(स्थिर s8 dst[], स्थिर s8 src[],
				    काष्ठा jit_ctx *ctx) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rd;
	s8 rt;

	/* Setup Opeअक्रमs */
	rt = arm_bpf_get_reg32(src_lo, पंचांगp2[1], ctx);
	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);

	/* Do RSH operation */
	emit(ARM_RSB_I(ARM_IP, rt, 32), ctx);
	emit(ARM_SUBS_I(पंचांगp2[0], rt, 32), ctx);
	emit(ARM_MOV_SR(ARM_LR, rd[1], SRTYPE_LSR, rt), ctx);
	emit(ARM_ORR_SR(ARM_LR, ARM_LR, rd[0], SRTYPE_ASL, ARM_IP), ctx);
	emit(ARM_ORR_SR(ARM_LR, ARM_LR, rd[0], SRTYPE_LSR, पंचांगp2[0]), ctx);
	emit(ARM_MOV_SR(ARM_IP, rd[0], SRTYPE_LSR, rt), ctx);

	arm_bpf_put_reg32(dst_lo, ARM_LR, ctx);
	arm_bpf_put_reg32(dst_hi, ARM_IP, ctx);
पूर्ण

/* dst = dst << val */
अटल अंतरभूत व्योम emit_a32_lsh_i64(स्थिर s8 dst[],
				    स्थिर u32 val, काष्ठा jit_ctx *ctx)अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rd;

	/* Setup opeअक्रमs */
	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);

	/* Do LSH operation */
	अगर (val < 32) अणु
		emit(ARM_MOV_SI(पंचांगp2[0], rd[0], SRTYPE_ASL, val), ctx);
		emit(ARM_ORR_SI(rd[0], पंचांगp2[0], rd[1], SRTYPE_LSR, 32 - val), ctx);
		emit(ARM_MOV_SI(rd[1], rd[1], SRTYPE_ASL, val), ctx);
	पूर्ण अन्यथा अणु
		अगर (val == 32)
			emit(ARM_MOV_R(rd[0], rd[1]), ctx);
		अन्यथा
			emit(ARM_MOV_SI(rd[0], rd[1], SRTYPE_ASL, val - 32), ctx);
		emit(ARM_EOR_R(rd[1], rd[1], rd[1]), ctx);
	पूर्ण

	arm_bpf_put_reg64(dst, rd, ctx);
पूर्ण

/* dst = dst >> val */
अटल अंतरभूत व्योम emit_a32_rsh_i64(स्थिर s8 dst[],
				    स्थिर u32 val, काष्ठा jit_ctx *ctx) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rd;

	/* Setup opeअक्रमs */
	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);

	/* Do LSR operation */
	अगर (val == 0) अणु
		/* An immediate value of 0 encodes a shअगरt amount of 32
		 * क्रम LSR. To shअगरt by 0, करोn't करो anything.
		 */
	पूर्ण अन्यथा अगर (val < 32) अणु
		emit(ARM_MOV_SI(पंचांगp2[1], rd[1], SRTYPE_LSR, val), ctx);
		emit(ARM_ORR_SI(rd[1], पंचांगp2[1], rd[0], SRTYPE_ASL, 32 - val), ctx);
		emit(ARM_MOV_SI(rd[0], rd[0], SRTYPE_LSR, val), ctx);
	पूर्ण अन्यथा अगर (val == 32) अणु
		emit(ARM_MOV_R(rd[1], rd[0]), ctx);
		emit(ARM_MOV_I(rd[0], 0), ctx);
	पूर्ण अन्यथा अणु
		emit(ARM_MOV_SI(rd[1], rd[0], SRTYPE_LSR, val - 32), ctx);
		emit(ARM_MOV_I(rd[0], 0), ctx);
	पूर्ण

	arm_bpf_put_reg64(dst, rd, ctx);
पूर्ण

/* dst = dst >> val (चिन्हित) */
अटल अंतरभूत व्योम emit_a32_arsh_i64(स्थिर s8 dst[],
				     स्थिर u32 val, काष्ठा jit_ctx *ctx)अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rd;

	/* Setup opeअक्रमs */
	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);

	/* Do ARSH operation */
	अगर (val == 0) अणु
		/* An immediate value of 0 encodes a shअगरt amount of 32
		 * क्रम ASR. To shअगरt by 0, करोn't करो anything.
		 */
	पूर्ण अन्यथा अगर (val < 32) अणु
		emit(ARM_MOV_SI(पंचांगp2[1], rd[1], SRTYPE_LSR, val), ctx);
		emit(ARM_ORR_SI(rd[1], पंचांगp2[1], rd[0], SRTYPE_ASL, 32 - val), ctx);
		emit(ARM_MOV_SI(rd[0], rd[0], SRTYPE_ASR, val), ctx);
	पूर्ण अन्यथा अगर (val == 32) अणु
		emit(ARM_MOV_R(rd[1], rd[0]), ctx);
		emit(ARM_MOV_SI(rd[0], rd[0], SRTYPE_ASR, 31), ctx);
	पूर्ण अन्यथा अणु
		emit(ARM_MOV_SI(rd[1], rd[0], SRTYPE_ASR, val - 32), ctx);
		emit(ARM_MOV_SI(rd[0], rd[0], SRTYPE_ASR, 31), ctx);
	पूर्ण

	arm_bpf_put_reg64(dst, rd, ctx);
पूर्ण

अटल अंतरभूत व्योम emit_a32_mul_r64(स्थिर s8 dst[], स्थिर s8 src[],
				    काष्ठा jit_ctx *ctx) अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rd, *rt;

	/* Setup opeअक्रमs क्रम multiplication */
	rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);
	rt = arm_bpf_get_reg64(src, पंचांगp2, ctx);

	/* Do Multiplication */
	emit(ARM_MUL(ARM_IP, rd[1], rt[0]), ctx);
	emit(ARM_MUL(ARM_LR, rd[0], rt[1]), ctx);
	emit(ARM_ADD_R(ARM_LR, ARM_IP, ARM_LR), ctx);

	emit(ARM_UMULL(ARM_IP, rd[0], rd[1], rt[1]), ctx);
	emit(ARM_ADD_R(rd[0], ARM_LR, rd[0]), ctx);

	arm_bpf_put_reg32(dst_lo, ARM_IP, ctx);
	arm_bpf_put_reg32(dst_hi, rd[0], ctx);
पूर्ण

अटल bool is_ldst_imm(s16 off, स्थिर u8 size)
अणु
	s16 off_max = 0;

	चयन (size) अणु
	हाल BPF_B:
	हाल BPF_W:
		off_max = 0xfff;
		अवरोध;
	हाल BPF_H:
		off_max = 0xff;
		अवरोध;
	हाल BPF_DW:
		/* Need to make sure off+4 करोes not overflow. */
		off_max = 0xfff - 4;
		अवरोध;
	पूर्ण
	वापस -off_max <= off && off <= off_max;
पूर्ण

/* *(size *)(dst + off) = src */
अटल अंतरभूत व्योम emit_str_r(स्थिर s8 dst, स्थिर s8 src[],
			      s16 off, काष्ठा jit_ctx *ctx, स्थिर u8 sz)अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	s8 rd;

	rd = arm_bpf_get_reg32(dst, पंचांगp[1], ctx);

	अगर (!is_ldst_imm(off, sz)) अणु
		emit_a32_mov_i(पंचांगp[0], off, ctx);
		emit(ARM_ADD_R(पंचांगp[0], पंचांगp[0], rd), ctx);
		rd = पंचांगp[0];
		off = 0;
	पूर्ण
	चयन (sz) अणु
	हाल BPF_B:
		/* Store a Byte */
		emit(ARM_STRB_I(src_lo, rd, off), ctx);
		अवरोध;
	हाल BPF_H:
		/* Store a HalfWord */
		emit(ARM_STRH_I(src_lo, rd, off), ctx);
		अवरोध;
	हाल BPF_W:
		/* Store a Word */
		emit(ARM_STR_I(src_lo, rd, off), ctx);
		अवरोध;
	हाल BPF_DW:
		/* Store a Double Word */
		emit(ARM_STR_I(src_lo, rd, off), ctx);
		emit(ARM_STR_I(src_hi, rd, off + 4), ctx);
		अवरोध;
	पूर्ण
पूर्ण

/* dst = *(size*)(src + off) */
अटल अंतरभूत व्योम emit_ldx_r(स्थिर s8 dst[], स्थिर s8 src,
			      s16 off, काष्ठा jit_ctx *ctx, स्थिर u8 sz)अणु
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *rd = is_stacked(dst_lo) ? पंचांगp : dst;
	s8 rm = src;

	अगर (!is_ldst_imm(off, sz)) अणु
		emit_a32_mov_i(पंचांगp[0], off, ctx);
		emit(ARM_ADD_R(पंचांगp[0], पंचांगp[0], src), ctx);
		rm = पंचांगp[0];
		off = 0;
	पूर्ण अन्यथा अगर (rd[1] == rm) अणु
		emit(ARM_MOV_R(पंचांगp[0], rm), ctx);
		rm = पंचांगp[0];
	पूर्ण
	चयन (sz) अणु
	हाल BPF_B:
		/* Load a Byte */
		emit(ARM_LDRB_I(rd[1], rm, off), ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit_a32_mov_i(rd[0], 0, ctx);
		अवरोध;
	हाल BPF_H:
		/* Load a HalfWord */
		emit(ARM_LDRH_I(rd[1], rm, off), ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit_a32_mov_i(rd[0], 0, ctx);
		अवरोध;
	हाल BPF_W:
		/* Load a Word */
		emit(ARM_LDR_I(rd[1], rm, off), ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit_a32_mov_i(rd[0], 0, ctx);
		अवरोध;
	हाल BPF_DW:
		/* Load a Double Word */
		emit(ARM_LDR_I(rd[1], rm, off), ctx);
		emit(ARM_LDR_I(rd[0], rm, off + 4), ctx);
		अवरोध;
	पूर्ण
	arm_bpf_put_reg64(dst, rd, ctx);
पूर्ण

/* Arithmatic Operation */
अटल अंतरभूत व्योम emit_ar_r(स्थिर u8 rd, स्थिर u8 rt, स्थिर u8 rm,
			     स्थिर u8 rn, काष्ठा jit_ctx *ctx, u8 op,
			     bool is_jmp64) अणु
	चयन (op) अणु
	हाल BPF_JSET:
		अगर (is_jmp64) अणु
			emit(ARM_AND_R(ARM_IP, rt, rn), ctx);
			emit(ARM_AND_R(ARM_LR, rd, rm), ctx);
			emit(ARM_ORRS_R(ARM_IP, ARM_LR, ARM_IP), ctx);
		पूर्ण अन्यथा अणु
			emit(ARM_ANDS_R(ARM_IP, rt, rn), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_JEQ:
	हाल BPF_JNE:
	हाल BPF_JGT:
	हाल BPF_JGE:
	हाल BPF_JLE:
	हाल BPF_JLT:
		अगर (is_jmp64) अणु
			emit(ARM_CMP_R(rd, rm), ctx);
			/* Only compare low halve अगर high halve are equal. */
			_emit(ARM_COND_EQ, ARM_CMP_R(rt, rn), ctx);
		पूर्ण अन्यथा अणु
			emit(ARM_CMP_R(rt, rn), ctx);
		पूर्ण
		अवरोध;
	हाल BPF_JSLE:
	हाल BPF_JSGT:
		emit(ARM_CMP_R(rn, rt), ctx);
		अगर (is_jmp64)
			emit(ARM_SBCS_R(ARM_IP, rm, rd), ctx);
		अवरोध;
	हाल BPF_JSLT:
	हाल BPF_JSGE:
		emit(ARM_CMP_R(rt, rn), ctx);
		अगर (is_jmp64)
			emit(ARM_SBCS_R(ARM_IP, rd, rm), ctx);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक out_offset = -1; /* initialized on the first pass of build_body() */
अटल पूर्णांक emit_bpf_tail_call(काष्ठा jit_ctx *ctx)
अणु

	/* bpf_tail_call(व्योम *prog_ctx, काष्ठा bpf_array *array, u64 index) */
	स्थिर s8 *r2 = bpf2a32[BPF_REG_2];
	स्थिर s8 *r3 = bpf2a32[BPF_REG_3];
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *tcc = bpf2a32[TCALL_CNT];
	स्थिर s8 *tc;
	स्थिर पूर्णांक idx0 = ctx->idx;
#घोषणा cur_offset (ctx->idx - idx0)
#घोषणा jmp_offset (out_offset - (cur_offset) - 2)
	u32 lo, hi;
	s8 r_array, r_index;
	पूर्णांक off;

	/* अगर (index >= array->map.max_entries)
	 *	जाओ out;
	 */
	BUILD_BUG_ON(दुरत्व(काष्ठा bpf_array, map.max_entries) >
		     ARM_INST_LDST__IMM12);
	off = दुरत्व(काष्ठा bpf_array, map.max_entries);
	r_array = arm_bpf_get_reg32(r2[1], पंचांगp2[0], ctx);
	/* index is 32-bit क्रम arrays */
	r_index = arm_bpf_get_reg32(r3[1], पंचांगp2[1], ctx);
	/* array->map.max_entries */
	emit(ARM_LDR_I(पंचांगp[1], r_array, off), ctx);
	/* index >= array->map.max_entries */
	emit(ARM_CMP_R(r_index, पंचांगp[1]), ctx);
	_emit(ARM_COND_CS, ARM_B(jmp_offset), ctx);

	/* पंचांगp2[0] = array, पंचांगp2[1] = index */

	/* अगर (tail_call_cnt > MAX_TAIL_CALL_CNT)
	 *	जाओ out;
	 * tail_call_cnt++;
	 */
	lo = (u32)MAX_TAIL_CALL_CNT;
	hi = (u32)((u64)MAX_TAIL_CALL_CNT >> 32);
	tc = arm_bpf_get_reg64(tcc, पंचांगp, ctx);
	emit(ARM_CMP_I(tc[0], hi), ctx);
	_emit(ARM_COND_EQ, ARM_CMP_I(tc[1], lo), ctx);
	_emit(ARM_COND_HI, ARM_B(jmp_offset), ctx);
	emit(ARM_ADDS_I(tc[1], tc[1], 1), ctx);
	emit(ARM_ADC_I(tc[0], tc[0], 0), ctx);
	arm_bpf_put_reg64(tcc, पंचांगp, ctx);

	/* prog = array->ptrs[index]
	 * अगर (prog == शून्य)
	 *	जाओ out;
	 */
	BUILD_BUG_ON(imm8m(दुरत्व(काष्ठा bpf_array, ptrs)) < 0);
	off = imm8m(दुरत्व(काष्ठा bpf_array, ptrs));
	emit(ARM_ADD_I(पंचांगp[1], r_array, off), ctx);
	emit(ARM_LDR_R_SI(पंचांगp[1], पंचांगp[1], r_index, SRTYPE_ASL, 2), ctx);
	emit(ARM_CMP_I(पंचांगp[1], 0), ctx);
	_emit(ARM_COND_EQ, ARM_B(jmp_offset), ctx);

	/* जाओ *(prog->bpf_func + prologue_size); */
	BUILD_BUG_ON(दुरत्व(काष्ठा bpf_prog, bpf_func) >
		     ARM_INST_LDST__IMM12);
	off = दुरत्व(काष्ठा bpf_prog, bpf_func);
	emit(ARM_LDR_I(पंचांगp[1], पंचांगp[1], off), ctx);
	emit(ARM_ADD_I(पंचांगp[1], पंचांगp[1], ctx->prologue_bytes), ctx);
	emit_bx_r(पंचांगp[1], ctx);

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

/* 0xabcd => 0xcdab */
अटल अंतरभूत व्योम emit_rev16(स्थिर u8 rd, स्थिर u8 rn, काष्ठा jit_ctx *ctx)
अणु
#अगर __LINUX_ARM_ARCH__ < 6
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];

	emit(ARM_AND_I(पंचांगp2[1], rn, 0xff), ctx);
	emit(ARM_MOV_SI(पंचांगp2[0], rn, SRTYPE_LSR, 8), ctx);
	emit(ARM_AND_I(पंचांगp2[0], पंचांगp2[0], 0xff), ctx);
	emit(ARM_ORR_SI(rd, पंचांगp2[0], पंचांगp2[1], SRTYPE_LSL, 8), ctx);
#अन्यथा /* ARMv6+ */
	emit(ARM_REV16(rd, rn), ctx);
#पूर्ण_अगर
पूर्ण

/* 0xabcdefgh => 0xghefcdab */
अटल अंतरभूत व्योम emit_rev32(स्थिर u8 rd, स्थिर u8 rn, काष्ठा jit_ctx *ctx)
अणु
#अगर __LINUX_ARM_ARCH__ < 6
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];

	emit(ARM_AND_I(पंचांगp2[1], rn, 0xff), ctx);
	emit(ARM_MOV_SI(पंचांगp2[0], rn, SRTYPE_LSR, 24), ctx);
	emit(ARM_ORR_SI(ARM_IP, पंचांगp2[0], पंचांगp2[1], SRTYPE_LSL, 24), ctx);

	emit(ARM_MOV_SI(पंचांगp2[1], rn, SRTYPE_LSR, 8), ctx);
	emit(ARM_AND_I(पंचांगp2[1], पंचांगp2[1], 0xff), ctx);
	emit(ARM_MOV_SI(पंचांगp2[0], rn, SRTYPE_LSR, 16), ctx);
	emit(ARM_AND_I(पंचांगp2[0], पंचांगp2[0], 0xff), ctx);
	emit(ARM_MOV_SI(पंचांगp2[0], पंचांगp2[0], SRTYPE_LSL, 8), ctx);
	emit(ARM_ORR_SI(पंचांगp2[0], पंचांगp2[0], पंचांगp2[1], SRTYPE_LSL, 16), ctx);
	emit(ARM_ORR_R(rd, ARM_IP, पंचांगp2[0]), ctx);

#अन्यथा /* ARMv6+ */
	emit(ARM_REV(rd, rn), ctx);
#पूर्ण_अगर
पूर्ण

// push the scratch stack रेजिस्टर on top of the stack
अटल अंतरभूत व्योम emit_push_r64(स्थिर s8 src[], काष्ठा jit_ctx *ctx)
अणु
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s8 *rt;
	u16 reg_set = 0;

	rt = arm_bpf_get_reg64(src, पंचांगp2, ctx);

	reg_set = (1 << rt[1]) | (1 << rt[0]);
	emit(ARM_PUSH(reg_set), ctx);
पूर्ण

अटल व्योम build_prologue(काष्ठा jit_ctx *ctx)
अणु
	स्थिर s8 arm_r0 = bpf2a32[BPF_REG_0][1];
	स्थिर s8 *bpf_r1 = bpf2a32[BPF_REG_1];
	स्थिर s8 *bpf_fp = bpf2a32[BPF_REG_FP];
	स्थिर s8 *tcc = bpf2a32[TCALL_CNT];

	/* Save callee saved रेजिस्टरs. */
#अगर_घोषित CONFIG_FRAME_POINTER
	u16 reg_set = CALLEE_PUSH_MASK | 1 << ARM_IP | 1 << ARM_PC;
	emit(ARM_MOV_R(ARM_IP, ARM_SP), ctx);
	emit(ARM_PUSH(reg_set), ctx);
	emit(ARM_SUB_I(ARM_FP, ARM_IP, 4), ctx);
#अन्यथा
	emit(ARM_PUSH(CALLEE_PUSH_MASK), ctx);
	emit(ARM_MOV_R(ARM_FP, ARM_SP), ctx);
#पूर्ण_अगर
	/* mov r3, #0 */
	/* sub r2, sp, #SCRATCH_SIZE */
	emit(ARM_MOV_I(bpf_r1[0], 0), ctx);
	emit(ARM_SUB_I(bpf_r1[1], ARM_SP, SCRATCH_SIZE), ctx);

	ctx->stack_size = imm8m(STACK_SIZE);

	/* Set up function call stack */
	emit(ARM_SUB_I(ARM_SP, ARM_SP, ctx->stack_size), ctx);

	/* Set up BPF prog stack base रेजिस्टर */
	emit_a32_mov_r64(true, bpf_fp, bpf_r1, ctx);

	/* Initialize Tail Count */
	emit(ARM_MOV_I(bpf_r1[1], 0), ctx);
	emit_a32_mov_r64(true, tcc, bpf_r1, ctx);

	/* Move BPF_CTX to BPF_R1 */
	emit(ARM_MOV_R(bpf_r1[1], arm_r0), ctx);

	/* end of prologue */
पूर्ण

/* restore callee saved रेजिस्टरs. */
अटल व्योम build_epilogue(काष्ठा jit_ctx *ctx)
अणु
#अगर_घोषित CONFIG_FRAME_POINTER
	/* When using frame poपूर्णांकers, some additional रेजिस्टरs need to
	 * be loaded. */
	u16 reg_set = CALLEE_POP_MASK | 1 << ARM_SP;
	emit(ARM_SUB_I(ARM_SP, ARM_FP, hweight16(reg_set) * 4), ctx);
	emit(ARM_LDM(ARM_SP, reg_set), ctx);
#अन्यथा
	/* Restore callee saved रेजिस्टरs. */
	emit(ARM_MOV_R(ARM_SP, ARM_FP), ctx);
	emit(ARM_POP(CALLEE_POP_MASK), ctx);
#पूर्ण_अगर
पूर्ण

/*
 * Convert an eBPF inकाष्ठाion to native inकाष्ठाion, i.e
 * JITs an eBPF inकाष्ठाion.
 * Returns :
 *	0  - Successfully JITed an 8-byte eBPF inकाष्ठाion
 *	>0 - Successfully JITed a 16-byte eBPF inकाष्ठाion
 *	<0 - Failed to JIT.
 */
अटल पूर्णांक build_insn(स्थिर काष्ठा bpf_insn *insn, काष्ठा jit_ctx *ctx)
अणु
	स्थिर u8 code = insn->code;
	स्थिर s8 *dst = bpf2a32[insn->dst_reg];
	स्थिर s8 *src = bpf2a32[insn->src_reg];
	स्थिर s8 *पंचांगp = bpf2a32[TMP_REG_1];
	स्थिर s8 *पंचांगp2 = bpf2a32[TMP_REG_2];
	स्थिर s16 off = insn->off;
	स्थिर s32 imm = insn->imm;
	स्थिर पूर्णांक i = insn - ctx->prog->insnsi;
	स्थिर bool is64 = BPF_CLASS(code) == BPF_ALU64;
	स्थिर s8 *rd, *rs;
	s8 rd_lo, rt, rm, rn;
	s32 jmp_offset;

#घोषणा check_imm(bits, imm) करो अणु				\
	अगर ((imm) >= (1 << ((bits) - 1)) ||			\
	    (imm) < -(1 << ((bits) - 1))) अणु			\
		pr_info("[%2d] imm=%d(0x%x) out of range\n",	\
			i, imm, imm);				\
		वापस -EINVAL;					\
	पूर्ण							\
पूर्ण जबतक (0)
#घोषणा check_imm24(imm) check_imm(24, imm)

	चयन (code) अणु
	/* ALU operations */

	/* dst = src */
	हाल BPF_ALU | BPF_MOV | BPF_K:
	हाल BPF_ALU | BPF_MOV | BPF_X:
	हाल BPF_ALU64 | BPF_MOV | BPF_K:
	हाल BPF_ALU64 | BPF_MOV | BPF_X:
		चयन (BPF_SRC(code)) अणु
		हाल BPF_X:
			अगर (imm == 1) अणु
				/* Special mov32 क्रम zext */
				emit_a32_mov_i(dst_hi, 0, ctx);
				अवरोध;
			पूर्ण
			emit_a32_mov_r64(is64, dst, src, ctx);
			अवरोध;
		हाल BPF_K:
			/* Sign-extend immediate value to destination reg */
			emit_a32_mov_se_i64(is64, dst, imm, ctx);
			अवरोध;
		पूर्ण
		अवरोध;
	/* dst = dst + src/imm */
	/* dst = dst - src/imm */
	/* dst = dst | src/imm */
	/* dst = dst & src/imm */
	/* dst = dst ^ src/imm */
	/* dst = dst * src/imm */
	/* dst = dst << src */
	/* dst = dst >> src */
	हाल BPF_ALU | BPF_ADD | BPF_K:
	हाल BPF_ALU | BPF_ADD | BPF_X:
	हाल BPF_ALU | BPF_SUB | BPF_K:
	हाल BPF_ALU | BPF_SUB | BPF_X:
	हाल BPF_ALU | BPF_OR | BPF_K:
	हाल BPF_ALU | BPF_OR | BPF_X:
	हाल BPF_ALU | BPF_AND | BPF_K:
	हाल BPF_ALU | BPF_AND | BPF_X:
	हाल BPF_ALU | BPF_XOR | BPF_K:
	हाल BPF_ALU | BPF_XOR | BPF_X:
	हाल BPF_ALU | BPF_MUL | BPF_K:
	हाल BPF_ALU | BPF_MUL | BPF_X:
	हाल BPF_ALU | BPF_LSH | BPF_X:
	हाल BPF_ALU | BPF_RSH | BPF_X:
	हाल BPF_ALU | BPF_ARSH | BPF_X:
	हाल BPF_ALU64 | BPF_ADD | BPF_K:
	हाल BPF_ALU64 | BPF_ADD | BPF_X:
	हाल BPF_ALU64 | BPF_SUB | BPF_K:
	हाल BPF_ALU64 | BPF_SUB | BPF_X:
	हाल BPF_ALU64 | BPF_OR | BPF_K:
	हाल BPF_ALU64 | BPF_OR | BPF_X:
	हाल BPF_ALU64 | BPF_AND | BPF_K:
	हाल BPF_ALU64 | BPF_AND | BPF_X:
	हाल BPF_ALU64 | BPF_XOR | BPF_K:
	हाल BPF_ALU64 | BPF_XOR | BPF_X:
		चयन (BPF_SRC(code)) अणु
		हाल BPF_X:
			emit_a32_alu_r64(is64, dst, src, ctx, BPF_OP(code));
			अवरोध;
		हाल BPF_K:
			/* Move immediate value to the temporary रेजिस्टर
			 * and then करो the ALU operation on the temporary
			 * रेजिस्टर as this will sign-extend the immediate
			 * value पूर्णांकo temporary reg and then it would be
			 * safe to करो the operation on it.
			 */
			emit_a32_mov_se_i64(is64, पंचांगp2, imm, ctx);
			emit_a32_alu_r64(is64, dst, पंचांगp2, ctx, BPF_OP(code));
			अवरोध;
		पूर्ण
		अवरोध;
	/* dst = dst / src(imm) */
	/* dst = dst % src(imm) */
	हाल BPF_ALU | BPF_DIV | BPF_K:
	हाल BPF_ALU | BPF_DIV | BPF_X:
	हाल BPF_ALU | BPF_MOD | BPF_K:
	हाल BPF_ALU | BPF_MOD | BPF_X:
		rd_lo = arm_bpf_get_reg32(dst_lo, पंचांगp2[1], ctx);
		चयन (BPF_SRC(code)) अणु
		हाल BPF_X:
			rt = arm_bpf_get_reg32(src_lo, पंचांगp2[0], ctx);
			अवरोध;
		हाल BPF_K:
			rt = पंचांगp2[0];
			emit_a32_mov_i(rt, imm, ctx);
			अवरोध;
		शेष:
			rt = src_lo;
			अवरोध;
		पूर्ण
		emit_uभागmod(rd_lo, rd_lo, rt, ctx, BPF_OP(code));
		arm_bpf_put_reg32(dst_lo, rd_lo, ctx);
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit_a32_mov_i(dst_hi, 0, ctx);
		अवरोध;
	हाल BPF_ALU64 | BPF_DIV | BPF_K:
	हाल BPF_ALU64 | BPF_DIV | BPF_X:
	हाल BPF_ALU64 | BPF_MOD | BPF_K:
	हाल BPF_ALU64 | BPF_MOD | BPF_X:
		जाओ notyet;
	/* dst = dst << imm */
	/* dst = dst >> imm */
	/* dst = dst >> imm (चिन्हित) */
	हाल BPF_ALU | BPF_LSH | BPF_K:
	हाल BPF_ALU | BPF_RSH | BPF_K:
	हाल BPF_ALU | BPF_ARSH | BPF_K:
		अगर (unlikely(imm > 31))
			वापस -EINVAL;
		अगर (imm)
			emit_a32_alu_i(dst_lo, imm, ctx, BPF_OP(code));
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit_a32_mov_i(dst_hi, 0, ctx);
		अवरोध;
	/* dst = dst << imm */
	हाल BPF_ALU64 | BPF_LSH | BPF_K:
		अगर (unlikely(imm > 63))
			वापस -EINVAL;
		emit_a32_lsh_i64(dst, imm, ctx);
		अवरोध;
	/* dst = dst >> imm */
	हाल BPF_ALU64 | BPF_RSH | BPF_K:
		अगर (unlikely(imm > 63))
			वापस -EINVAL;
		emit_a32_rsh_i64(dst, imm, ctx);
		अवरोध;
	/* dst = dst << src */
	हाल BPF_ALU64 | BPF_LSH | BPF_X:
		emit_a32_lsh_r64(dst, src, ctx);
		अवरोध;
	/* dst = dst >> src */
	हाल BPF_ALU64 | BPF_RSH | BPF_X:
		emit_a32_rsh_r64(dst, src, ctx);
		अवरोध;
	/* dst = dst >> src (चिन्हित) */
	हाल BPF_ALU64 | BPF_ARSH | BPF_X:
		emit_a32_arsh_r64(dst, src, ctx);
		अवरोध;
	/* dst = dst >> imm (चिन्हित) */
	हाल BPF_ALU64 | BPF_ARSH | BPF_K:
		अगर (unlikely(imm > 63))
			वापस -EINVAL;
		emit_a32_arsh_i64(dst, imm, ctx);
		अवरोध;
	/* dst = ~dst */
	हाल BPF_ALU | BPF_NEG:
		emit_a32_alu_i(dst_lo, 0, ctx, BPF_OP(code));
		अगर (!ctx->prog->aux->verअगरier_zext)
			emit_a32_mov_i(dst_hi, 0, ctx);
		अवरोध;
	/* dst = ~dst (64 bit) */
	हाल BPF_ALU64 | BPF_NEG:
		emit_a32_neg64(dst, ctx);
		अवरोध;
	/* dst = dst * src/imm */
	हाल BPF_ALU64 | BPF_MUL | BPF_X:
	हाल BPF_ALU64 | BPF_MUL | BPF_K:
		चयन (BPF_SRC(code)) अणु
		हाल BPF_X:
			emit_a32_mul_r64(dst, src, ctx);
			अवरोध;
		हाल BPF_K:
			/* Move immediate value to the temporary रेजिस्टर
			 * and then करो the multiplication on it as this
			 * will sign-extend the immediate value पूर्णांकo temp
			 * reg then it would be safe to करो the operation
			 * on it.
			 */
			emit_a32_mov_se_i64(is64, पंचांगp2, imm, ctx);
			emit_a32_mul_r64(dst, पंचांगp2, ctx);
			अवरोध;
		पूर्ण
		अवरोध;
	/* dst = htole(dst) */
	/* dst = htobe(dst) */
	हाल BPF_ALU | BPF_END | BPF_FROM_LE:
	हाल BPF_ALU | BPF_END | BPF_FROM_BE:
		rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);
		अगर (BPF_SRC(code) == BPF_FROM_LE)
			जाओ emit_bswap_uxt;
		चयन (imm) अणु
		हाल 16:
			emit_rev16(rd[1], rd[1], ctx);
			जाओ emit_bswap_uxt;
		हाल 32:
			emit_rev32(rd[1], rd[1], ctx);
			जाओ emit_bswap_uxt;
		हाल 64:
			emit_rev32(ARM_LR, rd[1], ctx);
			emit_rev32(rd[1], rd[0], ctx);
			emit(ARM_MOV_R(rd[0], ARM_LR), ctx);
			अवरोध;
		पूर्ण
		जाओ निकास;
emit_bswap_uxt:
		चयन (imm) अणु
		हाल 16:
			/* zero-extend 16 bits पूर्णांकo 64 bits */
#अगर __LINUX_ARM_ARCH__ < 6
			emit_a32_mov_i(पंचांगp2[1], 0xffff, ctx);
			emit(ARM_AND_R(rd[1], rd[1], पंचांगp2[1]), ctx);
#अन्यथा /* ARMv6+ */
			emit(ARM_UXTH(rd[1], rd[1]), ctx);
#पूर्ण_अगर
			अगर (!ctx->prog->aux->verअगरier_zext)
				emit(ARM_EOR_R(rd[0], rd[0], rd[0]), ctx);
			अवरोध;
		हाल 32:
			/* zero-extend 32 bits पूर्णांकo 64 bits */
			अगर (!ctx->prog->aux->verअगरier_zext)
				emit(ARM_EOR_R(rd[0], rd[0], rd[0]), ctx);
			अवरोध;
		हाल 64:
			/* nop */
			अवरोध;
		पूर्ण
निकास:
		arm_bpf_put_reg64(dst, rd, ctx);
		अवरोध;
	/* dst = imm64 */
	हाल BPF_LD | BPF_IMM | BPF_DW:
	अणु
		u64 val = (u32)imm | (u64)insn[1].imm << 32;

		emit_a32_mov_i64(dst, val, ctx);

		वापस 1;
	पूर्ण
	/* LDX: dst = *(size *)(src + off) */
	हाल BPF_LDX | BPF_MEM | BPF_W:
	हाल BPF_LDX | BPF_MEM | BPF_H:
	हाल BPF_LDX | BPF_MEM | BPF_B:
	हाल BPF_LDX | BPF_MEM | BPF_DW:
		rn = arm_bpf_get_reg32(src_lo, पंचांगp2[1], ctx);
		emit_ldx_r(dst, rn, off, ctx, BPF_SIZE(code));
		अवरोध;
	/* ST: *(size *)(dst + off) = imm */
	हाल BPF_ST | BPF_MEM | BPF_W:
	हाल BPF_ST | BPF_MEM | BPF_H:
	हाल BPF_ST | BPF_MEM | BPF_B:
	हाल BPF_ST | BPF_MEM | BPF_DW:
		चयन (BPF_SIZE(code)) अणु
		हाल BPF_DW:
			/* Sign-extend immediate value पूर्णांकo temp reg */
			emit_a32_mov_se_i64(true, पंचांगp2, imm, ctx);
			अवरोध;
		हाल BPF_W:
		हाल BPF_H:
		हाल BPF_B:
			emit_a32_mov_i(पंचांगp2[1], imm, ctx);
			अवरोध;
		पूर्ण
		emit_str_r(dst_lo, पंचांगp2, off, ctx, BPF_SIZE(code));
		अवरोध;
	/* Atomic ops */
	हाल BPF_STX | BPF_ATOMIC | BPF_W:
	हाल BPF_STX | BPF_ATOMIC | BPF_DW:
		जाओ notyet;
	/* STX: *(size *)(dst + off) = src */
	हाल BPF_STX | BPF_MEM | BPF_W:
	हाल BPF_STX | BPF_MEM | BPF_H:
	हाल BPF_STX | BPF_MEM | BPF_B:
	हाल BPF_STX | BPF_MEM | BPF_DW:
		rs = arm_bpf_get_reg64(src, पंचांगp2, ctx);
		emit_str_r(dst_lo, rs, off, ctx, BPF_SIZE(code));
		अवरोध;
	/* PC += off अगर dst == src */
	/* PC += off अगर dst > src */
	/* PC += off अगर dst >= src */
	/* PC += off अगर dst < src */
	/* PC += off अगर dst <= src */
	/* PC += off अगर dst != src */
	/* PC += off अगर dst > src (चिन्हित) */
	/* PC += off अगर dst >= src (चिन्हित) */
	/* PC += off अगर dst < src (चिन्हित) */
	/* PC += off अगर dst <= src (चिन्हित) */
	/* PC += off अगर dst & src */
	हाल BPF_JMP | BPF_JEQ | BPF_X:
	हाल BPF_JMP | BPF_JGT | BPF_X:
	हाल BPF_JMP | BPF_JGE | BPF_X:
	हाल BPF_JMP | BPF_JNE | BPF_X:
	हाल BPF_JMP | BPF_JSGT | BPF_X:
	हाल BPF_JMP | BPF_JSGE | BPF_X:
	हाल BPF_JMP | BPF_JSET | BPF_X:
	हाल BPF_JMP | BPF_JLE | BPF_X:
	हाल BPF_JMP | BPF_JLT | BPF_X:
	हाल BPF_JMP | BPF_JSLT | BPF_X:
	हाल BPF_JMP | BPF_JSLE | BPF_X:
	हाल BPF_JMP32 | BPF_JEQ | BPF_X:
	हाल BPF_JMP32 | BPF_JGT | BPF_X:
	हाल BPF_JMP32 | BPF_JGE | BPF_X:
	हाल BPF_JMP32 | BPF_JNE | BPF_X:
	हाल BPF_JMP32 | BPF_JSGT | BPF_X:
	हाल BPF_JMP32 | BPF_JSGE | BPF_X:
	हाल BPF_JMP32 | BPF_JSET | BPF_X:
	हाल BPF_JMP32 | BPF_JLE | BPF_X:
	हाल BPF_JMP32 | BPF_JLT | BPF_X:
	हाल BPF_JMP32 | BPF_JSLT | BPF_X:
	हाल BPF_JMP32 | BPF_JSLE | BPF_X:
		/* Setup source रेजिस्टरs */
		rm = arm_bpf_get_reg32(src_hi, पंचांगp2[0], ctx);
		rn = arm_bpf_get_reg32(src_lo, पंचांगp2[1], ctx);
		जाओ go_jmp;
	/* PC += off अगर dst == imm */
	/* PC += off अगर dst > imm */
	/* PC += off अगर dst >= imm */
	/* PC += off अगर dst < imm */
	/* PC += off अगर dst <= imm */
	/* PC += off अगर dst != imm */
	/* PC += off अगर dst > imm (चिन्हित) */
	/* PC += off अगर dst >= imm (चिन्हित) */
	/* PC += off अगर dst < imm (चिन्हित) */
	/* PC += off अगर dst <= imm (चिन्हित) */
	/* PC += off अगर dst & imm */
	हाल BPF_JMP | BPF_JEQ | BPF_K:
	हाल BPF_JMP | BPF_JGT | BPF_K:
	हाल BPF_JMP | BPF_JGE | BPF_K:
	हाल BPF_JMP | BPF_JNE | BPF_K:
	हाल BPF_JMP | BPF_JSGT | BPF_K:
	हाल BPF_JMP | BPF_JSGE | BPF_K:
	हाल BPF_JMP | BPF_JSET | BPF_K:
	हाल BPF_JMP | BPF_JLT | BPF_K:
	हाल BPF_JMP | BPF_JLE | BPF_K:
	हाल BPF_JMP | BPF_JSLT | BPF_K:
	हाल BPF_JMP | BPF_JSLE | BPF_K:
	हाल BPF_JMP32 | BPF_JEQ | BPF_K:
	हाल BPF_JMP32 | BPF_JGT | BPF_K:
	हाल BPF_JMP32 | BPF_JGE | BPF_K:
	हाल BPF_JMP32 | BPF_JNE | BPF_K:
	हाल BPF_JMP32 | BPF_JSGT | BPF_K:
	हाल BPF_JMP32 | BPF_JSGE | BPF_K:
	हाल BPF_JMP32 | BPF_JSET | BPF_K:
	हाल BPF_JMP32 | BPF_JLT | BPF_K:
	हाल BPF_JMP32 | BPF_JLE | BPF_K:
	हाल BPF_JMP32 | BPF_JSLT | BPF_K:
	हाल BPF_JMP32 | BPF_JSLE | BPF_K:
		अगर (off == 0)
			अवरोध;
		rm = पंचांगp2[0];
		rn = पंचांगp2[1];
		/* Sign-extend immediate value */
		emit_a32_mov_se_i64(true, पंचांगp2, imm, ctx);
go_jmp:
		/* Setup destination रेजिस्टर */
		rd = arm_bpf_get_reg64(dst, पंचांगp, ctx);

		/* Check क्रम the condition */
		emit_ar_r(rd[0], rd[1], rm, rn, ctx, BPF_OP(code),
			  BPF_CLASS(code) == BPF_JMP);

		/* Setup JUMP inकाष्ठाion */
		jmp_offset = bpf2a32_offset(i+off, i, ctx);
		चयन (BPF_OP(code)) अणु
		हाल BPF_JNE:
		हाल BPF_JSET:
			_emit(ARM_COND_NE, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JEQ:
			_emit(ARM_COND_EQ, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JGT:
			_emit(ARM_COND_HI, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JGE:
			_emit(ARM_COND_CS, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JSGT:
			_emit(ARM_COND_LT, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JSGE:
			_emit(ARM_COND_GE, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JLE:
			_emit(ARM_COND_LS, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JLT:
			_emit(ARM_COND_CC, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JSLT:
			_emit(ARM_COND_LT, ARM_B(jmp_offset), ctx);
			अवरोध;
		हाल BPF_JSLE:
			_emit(ARM_COND_GE, ARM_B(jmp_offset), ctx);
			अवरोध;
		पूर्ण
		अवरोध;
	/* JMP OFF */
	हाल BPF_JMP | BPF_JA:
	अणु
		अगर (off == 0)
			अवरोध;
		jmp_offset = bpf2a32_offset(i+off, i, ctx);
		check_imm24(jmp_offset);
		emit(ARM_B(jmp_offset), ctx);
		अवरोध;
	पूर्ण
	/* tail call */
	हाल BPF_JMP | BPF_TAIL_CALL:
		अगर (emit_bpf_tail_call(ctx))
			वापस -EFAULT;
		अवरोध;
	/* function call */
	हाल BPF_JMP | BPF_CALL:
	अणु
		स्थिर s8 *r0 = bpf2a32[BPF_REG_0];
		स्थिर s8 *r1 = bpf2a32[BPF_REG_1];
		स्थिर s8 *r2 = bpf2a32[BPF_REG_2];
		स्थिर s8 *r3 = bpf2a32[BPF_REG_3];
		स्थिर s8 *r4 = bpf2a32[BPF_REG_4];
		स्थिर s8 *r5 = bpf2a32[BPF_REG_5];
		स्थिर u32 func = (u32)__bpf_call_base + (u32)imm;

		emit_a32_mov_r64(true, r0, r1, ctx);
		emit_a32_mov_r64(true, r1, r2, ctx);
		emit_push_r64(r5, ctx);
		emit_push_r64(r4, ctx);
		emit_push_r64(r3, ctx);

		emit_a32_mov_i(पंचांगp[1], func, ctx);
		emit_blx_r(पंचांगp[1], ctx);

		emit(ARM_ADD_I(ARM_SP, ARM_SP, imm8m(24)), ctx); // callee clean
		अवरोध;
	पूर्ण
	/* function वापस */
	हाल BPF_JMP | BPF_EXIT:
		/* Optimization: when last inकाष्ठाion is EXIT
		 * simply fallthrough to epilogue.
		 */
		अगर (i == ctx->prog->len - 1)
			अवरोध;
		jmp_offset = epilogue_offset(ctx);
		check_imm24(jmp_offset);
		emit(ARM_B(jmp_offset), ctx);
		अवरोध;
notyet:
		pr_info_once("*** NOT YET: opcode %02x ***\n", code);
		वापस -EFAULT;
	शेष:
		pr_err_once("unknown opcode %02x\n", code);
		वापस -EINVAL;
	पूर्ण

	अगर (ctx->flags & FLAG_IMM_OVERFLOW)
		/*
		 * this inकाष्ठाion generated an overflow when
		 * trying to access the literal pool, so
		 * delegate this filter to the kernel पूर्णांकerpreter.
		 */
		वापस -1;
	वापस 0;
पूर्ण

अटल पूर्णांक build_body(काष्ठा jit_ctx *ctx)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->prog;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < prog->len; i++) अणु
		स्थिर काष्ठा bpf_insn *insn = &(prog->insnsi[i]);
		पूर्णांक ret;

		ret = build_insn(insn, ctx);

		/* It's used with loading the 64 bit immediate value. */
		अगर (ret > 0) अणु
			i++;
			अगर (ctx->target == शून्य)
				ctx->offsets[i] = ctx->idx;
			जारी;
		पूर्ण

		अगर (ctx->target == शून्य)
			ctx->offsets[i] = ctx->idx;

		/* If unsuccesfull, वापस with error code */
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक validate_code(काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ctx->idx; i++) अणु
		अगर (ctx->target[i] == __opcode_to_mem_arm(ARM_INST_UDF))
			वापस -1;
	पूर्ण

	वापस 0;
पूर्ण

व्योम bpf_jit_compile(काष्ठा bpf_prog *prog)
अणु
	/* Nothing to करो here. We support Internal BPF. */
पूर्ण

bool bpf_jit_needs_zext(व्योम)
अणु
	वापस true;
पूर्ण

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *पंचांगp, *orig_prog = prog;
	काष्ठा bpf_binary_header *header;
	bool पंचांगp_blinded = false;
	काष्ठा jit_ctx ctx;
	अचिन्हित पूर्णांक पंचांगp_idx;
	अचिन्हित पूर्णांक image_size;
	u8 *image_ptr;

	/* If BPF JIT was not enabled then we must fall back to
	 * the पूर्णांकerpreter.
	 */
	अगर (!prog->jit_requested)
		वापस orig_prog;

	/* If स्थिरant blinding was enabled and we failed during blinding
	 * then we must fall back to the पूर्णांकerpreter. Otherwise, we save
	 * the new JITed code.
	 */
	पंचांगp = bpf_jit_blind_स्थिरants(prog);

	अगर (IS_ERR(पंचांगp))
		वापस orig_prog;
	अगर (पंचांगp != prog) अणु
		पंचांगp_blinded = true;
		prog = पंचांगp;
	पूर्ण

	स_रखो(&ctx, 0, माप(ctx));
	ctx.prog = prog;
	ctx.cpu_architecture = cpu_architecture();

	/* Not able to allocate memory क्रम offsets[] , then
	 * we must fall back to the पूर्णांकerpreter
	 */
	ctx.offsets = kसुस्मृति(prog->len, माप(पूर्णांक), GFP_KERNEL);
	अगर (ctx.offsets == शून्य) अणु
		prog = orig_prog;
		जाओ out;
	पूर्ण

	/* 1) fake pass to find in the length of the JITed code,
	 * to compute ctx->offsets and other context variables
	 * needed to compute final JITed code.
	 * Also, calculate अक्रमom starting poपूर्णांकer/start of JITed code
	 * which is prefixed by अक्रमom number of fault inकाष्ठाions.
	 *
	 * If the first pass fails then there is no chance of it
	 * being successful in the second pass, so just fall back
	 * to the पूर्णांकerpreter.
	 */
	अगर (build_body(&ctx)) अणु
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	पंचांगp_idx = ctx.idx;
	build_prologue(&ctx);
	ctx.prologue_bytes = (ctx.idx - पंचांगp_idx) * 4;

	ctx.epilogue_offset = ctx.idx;

#अगर __LINUX_ARM_ARCH__ < 7
	पंचांगp_idx = ctx.idx;
	build_epilogue(&ctx);
	ctx.epilogue_bytes = (ctx.idx - पंचांगp_idx) * 4;

	ctx.idx += ctx.imm_count;
	अगर (ctx.imm_count) अणु
		ctx.imms = kसुस्मृति(ctx.imm_count, माप(u32), GFP_KERNEL);
		अगर (ctx.imms == शून्य) अणु
			prog = orig_prog;
			जाओ out_off;
		पूर्ण
	पूर्ण
#अन्यथा
	/* there's nothing about the epilogue on ARMv7 */
	build_epilogue(&ctx);
#पूर्ण_अगर
	/* Now we can get the actual image size of the JITed arm code.
	 * Currently, we are not considering the THUMB-2 inकाष्ठाions
	 * क्रम jit, although it can decrease the size of the image.
	 *
	 * As each arm inकाष्ठाion is of length 32bit, we are translating
	 * number of JITed पूर्णांकructions पूर्णांकo the size required to store these
	 * JITed code.
	 */
	image_size = माप(u32) * ctx.idx;

	/* Now we know the size of the काष्ठाure to make */
	header = bpf_jit_binary_alloc(image_size, &image_ptr,
				      माप(u32), jit_fill_hole);
	/* Not able to allocate memory क्रम the काष्ठाure then
	 * we must fall back to the पूर्णांकerpretation
	 */
	अगर (header == शून्य) अणु
		prog = orig_prog;
		जाओ out_imms;
	पूर्ण

	/* 2.) Actual pass to generate final JIT code */
	ctx.target = (u32 *) image_ptr;
	ctx.idx = 0;

	build_prologue(&ctx);

	/* If building the body of the JITed code fails somehow,
	 * we fall back to the पूर्णांकerpretation.
	 */
	अगर (build_body(&ctx) < 0) अणु
		image_ptr = शून्य;
		bpf_jit_binary_मुक्त(header);
		prog = orig_prog;
		जाओ out_imms;
	पूर्ण
	build_epilogue(&ctx);

	/* 3.) Extra pass to validate JITed Code */
	अगर (validate_code(&ctx)) अणु
		image_ptr = शून्य;
		bpf_jit_binary_मुक्त(header);
		prog = orig_prog;
		जाओ out_imms;
	पूर्ण
	flush_icache_range((u32)header, (u32)(ctx.target + ctx.idx));

	अगर (bpf_jit_enable > 1)
		/* there are 2 passes here */
		bpf_jit_dump(prog->len, image_size, 2, ctx.target);

	bpf_jit_binary_lock_ro(header);
	prog->bpf_func = (व्योम *)ctx.target;
	prog->jited = 1;
	prog->jited_len = image_size;

out_imms:
#अगर __LINUX_ARM_ARCH__ < 7
	अगर (ctx.imm_count)
		kमुक्त(ctx.imms);
#पूर्ण_अगर
out_off:
	kमुक्त(ctx.offsets);
out:
	अगर (पंचांगp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   पंचांगp : orig_prog);
	वापस prog;
पूर्ण

