<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/moduleloader.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/bpf.h>
#समावेश <linux/cache.h>
#समावेश <linux/अगर_vlan.h>

#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/ptrace.h>

#समावेश "bpf_jit_64.h"

अटल अंतरभूत bool is_simm13(अचिन्हित पूर्णांक value)
अणु
	वापस value + 0x1000 < 0x2000;
पूर्ण

अटल अंतरभूत bool is_simm10(अचिन्हित पूर्णांक value)
अणु
	वापस value + 0x200 < 0x400;
पूर्ण

अटल अंतरभूत bool is_simm5(अचिन्हित पूर्णांक value)
अणु
	वापस value + 0x10 < 0x20;
पूर्ण

अटल अंतरभूत bool is_sethi(अचिन्हित पूर्णांक value)
अणु
	वापस (value & ~0x3fffff) == 0;
पूर्ण

अटल व्योम bpf_flush_icache(व्योम *start_, व्योम *end_)
अणु
	/* Cheetah's I-cache is fully coherent.  */
	अगर (tlb_type == spitfire) अणु
		अचिन्हित दीर्घ start = (अचिन्हित दीर्घ) start_;
		अचिन्हित दीर्घ end = (अचिन्हित दीर्घ) end_;

		start &= ~7UL;
		end = (end + 7UL) & ~7UL;
		जबतक (start < end) अणु
			flushi(start);
			start += 32;
		पूर्ण
	पूर्ण
पूर्ण

#घोषणा S13(X)		((X) & 0x1fff)
#घोषणा S5(X)		((X) & 0x1f)
#घोषणा IMMED		0x00002000
#घोषणा RD(X)		((X) << 25)
#घोषणा RS1(X)		((X) << 14)
#घोषणा RS2(X)		((X))
#घोषणा OP(X)		((X) << 30)
#घोषणा OP2(X)		((X) << 22)
#घोषणा OP3(X)		((X) << 19)
#घोषणा COND(X)		(((X) & 0xf) << 25)
#घोषणा CBCOND(X)	(((X) & 0x1f) << 25)
#घोषणा F1(X)		OP(X)
#घोषणा F2(X, Y)	(OP(X) | OP2(Y))
#घोषणा F3(X, Y)	(OP(X) | OP3(Y))
#घोषणा ASI(X)		(((X) & 0xff) << 5)

#घोषणा CONDN		COND(0x0)
#घोषणा CONDE		COND(0x1)
#घोषणा CONDLE		COND(0x2)
#घोषणा CONDL		COND(0x3)
#घोषणा CONDLEU		COND(0x4)
#घोषणा CONDCS		COND(0x5)
#घोषणा CONDNEG		COND(0x6)
#घोषणा CONDVC		COND(0x7)
#घोषणा CONDA		COND(0x8)
#घोषणा CONDNE		COND(0x9)
#घोषणा CONDG		COND(0xa)
#घोषणा CONDGE		COND(0xb)
#घोषणा CONDGU		COND(0xc)
#घोषणा CONDCC		COND(0xd)
#घोषणा CONDPOS		COND(0xe)
#घोषणा CONDVS		COND(0xf)

#घोषणा CONDGEU		CONDCC
#घोषणा CONDLU		CONDCS

#घोषणा WDISP22(X)	(((X) >> 2) & 0x3fffff)
#घोषणा WDISP19(X)	(((X) >> 2) & 0x7ffff)

/* The 10-bit branch displacement क्रम CBCOND is split पूर्णांकo two fields */
अटल u32 WDISP10(u32 off)
अणु
	u32 ret = ((off >> 2) & 0xff) << 5;

	ret |= ((off >> (2 + 8)) & 0x03) << 19;

	वापस ret;
पूर्ण

#घोषणा CBCONDE		CBCOND(0x09)
#घोषणा CBCONDLE	CBCOND(0x0a)
#घोषणा CBCONDL		CBCOND(0x0b)
#घोषणा CBCONDLEU	CBCOND(0x0c)
#घोषणा CBCONDCS	CBCOND(0x0d)
#घोषणा CBCONDN		CBCOND(0x0e)
#घोषणा CBCONDVS	CBCOND(0x0f)
#घोषणा CBCONDNE	CBCOND(0x19)
#घोषणा CBCONDG		CBCOND(0x1a)
#घोषणा CBCONDGE	CBCOND(0x1b)
#घोषणा CBCONDGU	CBCOND(0x1c)
#घोषणा CBCONDCC	CBCOND(0x1d)
#घोषणा CBCONDPOS	CBCOND(0x1e)
#घोषणा CBCONDVC	CBCOND(0x1f)

#घोषणा CBCONDGEU	CBCONDCC
#घोषणा CBCONDLU	CBCONDCS

#घोषणा ANNUL		(1 << 29)
#घोषणा XCC		(1 << 21)

#घोषणा BRANCH		(F2(0, 1) | XCC)
#घोषणा CBCOND_OP	(F2(0, 3) | XCC)

#घोषणा BA		(BRANCH | CONDA)
#घोषणा BG		(BRANCH | CONDG)
#घोषणा BL		(BRANCH | CONDL)
#घोषणा BLE		(BRANCH | CONDLE)
#घोषणा BGU		(BRANCH | CONDGU)
#घोषणा BLEU		(BRANCH | CONDLEU)
#घोषणा BGE		(BRANCH | CONDGE)
#घोषणा BGEU		(BRANCH | CONDGEU)
#घोषणा BLU		(BRANCH | CONDLU)
#घोषणा BE		(BRANCH | CONDE)
#घोषणा BNE		(BRANCH | CONDNE)

#घोषणा SETHI(K, REG)	\
	(F2(0, 0x4) | RD(REG) | (((K) >> 10) & 0x3fffff))
#घोषणा OR_LO(K, REG)	\
	(F3(2, 0x02) | IMMED | RS1(REG) | ((K) & 0x3ff) | RD(REG))

#घोषणा ADD		F3(2, 0x00)
#घोषणा AND		F3(2, 0x01)
#घोषणा ANDCC		F3(2, 0x11)
#घोषणा OR		F3(2, 0x02)
#घोषणा XOR		F3(2, 0x03)
#घोषणा SUB		F3(2, 0x04)
#घोषणा SUBCC		F3(2, 0x14)
#घोषणा MUL		F3(2, 0x0a)
#घोषणा MULX		F3(2, 0x09)
#घोषणा UDIVX		F3(2, 0x0d)
#घोषणा DIV		F3(2, 0x0e)
#घोषणा SLL		F3(2, 0x25)
#घोषणा SLLX		(F3(2, 0x25)|(1<<12))
#घोषणा SRA		F3(2, 0x27)
#घोषणा SRAX		(F3(2, 0x27)|(1<<12))
#घोषणा SRL		F3(2, 0x26)
#घोषणा SRLX		(F3(2, 0x26)|(1<<12))
#घोषणा JMPL		F3(2, 0x38)
#घोषणा SAVE		F3(2, 0x3c)
#घोषणा RESTORE		F3(2, 0x3d)
#घोषणा CALL		F1(1)
#घोषणा BR		F2(0, 0x01)
#घोषणा RD_Y		F3(2, 0x28)
#घोषणा WR_Y		F3(2, 0x30)

#घोषणा LD32		F3(3, 0x00)
#घोषणा LD8		F3(3, 0x01)
#घोषणा LD16		F3(3, 0x02)
#घोषणा LD64		F3(3, 0x0b)
#घोषणा LD64A		F3(3, 0x1b)
#घोषणा ST8		F3(3, 0x05)
#घोषणा ST16		F3(3, 0x06)
#घोषणा ST32		F3(3, 0x04)
#घोषणा ST64		F3(3, 0x0e)

#घोषणा CAS		F3(3, 0x3c)
#घोषणा CASX		F3(3, 0x3e)

#घोषणा LDPTR		LD64
#घोषणा BASE_STACKFRAME	176

#घोषणा LD32I		(LD32 | IMMED)
#घोषणा LD8I		(LD8 | IMMED)
#घोषणा LD16I		(LD16 | IMMED)
#घोषणा LD64I		(LD64 | IMMED)
#घोषणा LDPTRI		(LDPTR | IMMED)
#घोषणा ST32I		(ST32 | IMMED)

काष्ठा jit_ctx अणु
	काष्ठा bpf_prog		*prog;
	अचिन्हित पूर्णांक		*offset;
	पूर्णांक			idx;
	पूर्णांक			epilogue_offset;
	bool 			पंचांगp_1_used;
	bool 			पंचांगp_2_used;
	bool 			पंचांगp_3_used;
	bool			saw_frame_poपूर्णांकer;
	bool			saw_call;
	bool			saw_tail_call;
	u32			*image;
पूर्ण;

#घोषणा TMP_REG_1	(MAX_BPF_JIT_REG + 0)
#घोषणा TMP_REG_2	(MAX_BPF_JIT_REG + 1)
#घोषणा TMP_REG_3	(MAX_BPF_JIT_REG + 2)

/* Map BPF रेजिस्टरs to SPARC रेजिस्टरs */
अटल स्थिर पूर्णांक bpf2sparc[] = अणु
	/* वापस value from in-kernel function, and निकास value from eBPF */
	[BPF_REG_0] = O5,

	/* arguments from eBPF program to in-kernel function */
	[BPF_REG_1] = O0,
	[BPF_REG_2] = O1,
	[BPF_REG_3] = O2,
	[BPF_REG_4] = O3,
	[BPF_REG_5] = O4,

	/* callee saved रेजिस्टरs that in-kernel function will preserve */
	[BPF_REG_6] = L0,
	[BPF_REG_7] = L1,
	[BPF_REG_8] = L2,
	[BPF_REG_9] = L3,

	/* पढ़ो-only frame poपूर्णांकer to access stack */
	[BPF_REG_FP] = L6,

	[BPF_REG_AX] = G7,

	/* temporary रेजिस्टर क्रम पूर्णांकernal BPF JIT */
	[TMP_REG_1] = G1,
	[TMP_REG_2] = G2,
	[TMP_REG_3] = G3,
पूर्ण;

अटल व्योम emit(स्थिर u32 insn, काष्ठा jit_ctx *ctx)
अणु
	अगर (ctx->image != शून्य)
		ctx->image[ctx->idx] = insn;

	ctx->idx++;
पूर्ण

अटल व्योम emit_call(u32 *func, काष्ठा jit_ctx *ctx)
अणु
	अगर (ctx->image != शून्य) अणु
		व्योम *here = &ctx->image[ctx->idx];
		अचिन्हित पूर्णांक off;

		off = (व्योम *)func - here;
		ctx->image[ctx->idx] = CALL | ((off >> 2) & 0x3fffffff);
	पूर्ण
	ctx->idx++;
पूर्ण

अटल व्योम emit_nop(काष्ठा jit_ctx *ctx)
अणु
	emit(SETHI(0, G0), ctx);
पूर्ण

अटल व्योम emit_reg_move(u32 from, u32 to, काष्ठा jit_ctx *ctx)
अणु
	emit(OR | RS1(G0) | RS2(from) | RD(to), ctx);
पूर्ण

/* Emit 32-bit स्थिरant, zero extended. */
अटल व्योम emit_set_स्थिर(s32 K, u32 reg, काष्ठा jit_ctx *ctx)
अणु
	emit(SETHI(K, reg), ctx);
	emit(OR_LO(K, reg), ctx);
पूर्ण

/* Emit 32-bit स्थिरant, sign extended. */
अटल व्योम emit_set_स्थिर_sext(s32 K, u32 reg, काष्ठा jit_ctx *ctx)
अणु
	अगर (K >= 0) अणु
		emit(SETHI(K, reg), ctx);
		emit(OR_LO(K, reg), ctx);
	पूर्ण अन्यथा अणु
		u32 hbits = ~(u32) K;
		u32 lbits = -0x400 | (u32) K;

		emit(SETHI(hbits, reg), ctx);
		emit(XOR | IMMED | RS1(reg) | S13(lbits) | RD(reg), ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_alu(u32 opcode, u32 src, u32 dst, काष्ठा jit_ctx *ctx)
अणु
	emit(opcode | RS1(dst) | RS2(src) | RD(dst), ctx);
पूर्ण

अटल व्योम emit_alu3(u32 opcode, u32 a, u32 b, u32 c, काष्ठा jit_ctx *ctx)
अणु
	emit(opcode | RS1(a) | RS2(b) | RD(c), ctx);
पूर्ण

अटल व्योम emit_alu_K(अचिन्हित पूर्णांक opcode, अचिन्हित पूर्णांक dst, अचिन्हित पूर्णांक imm,
		       काष्ठा jit_ctx *ctx)
अणु
	bool small_immed = is_simm13(imm);
	अचिन्हित पूर्णांक insn = opcode;

	insn |= RS1(dst) | RD(dst);
	अगर (small_immed) अणु
		emit(insn | IMMED | S13(imm), ctx);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक पंचांगp = bpf2sparc[TMP_REG_1];

		ctx->पंचांगp_1_used = true;

		emit_set_स्थिर_sext(imm, पंचांगp, ctx);
		emit(insn | RS2(पंचांगp), ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_alu3_K(अचिन्हित पूर्णांक opcode, अचिन्हित पूर्णांक src, अचिन्हित पूर्णांक imm,
			अचिन्हित पूर्णांक dst, काष्ठा jit_ctx *ctx)
अणु
	bool small_immed = is_simm13(imm);
	अचिन्हित पूर्णांक insn = opcode;

	insn |= RS1(src) | RD(dst);
	अगर (small_immed) अणु
		emit(insn | IMMED | S13(imm), ctx);
	पूर्ण अन्यथा अणु
		अचिन्हित पूर्णांक पंचांगp = bpf2sparc[TMP_REG_1];

		ctx->पंचांगp_1_used = true;

		emit_set_स्थिर_sext(imm, पंचांगp, ctx);
		emit(insn | RS2(पंचांगp), ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_loadimm32(s32 K, अचिन्हित पूर्णांक dest, काष्ठा jit_ctx *ctx)
अणु
	अगर (K >= 0 && is_simm13(K)) अणु
		/* or %g0, K, DEST */
		emit(OR | IMMED | RS1(G0) | S13(K) | RD(dest), ctx);
	पूर्ण अन्यथा अणु
		emit_set_स्थिर(K, dest, ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_loadimm(s32 K, अचिन्हित पूर्णांक dest, काष्ठा jit_ctx *ctx)
अणु
	अगर (is_simm13(K)) अणु
		/* or %g0, K, DEST */
		emit(OR | IMMED | RS1(G0) | S13(K) | RD(dest), ctx);
	पूर्ण अन्यथा अणु
		emit_set_स्थिर(K, dest, ctx);
	पूर्ण
पूर्ण

अटल व्योम emit_loadimm_sext(s32 K, अचिन्हित पूर्णांक dest, काष्ठा jit_ctx *ctx)
अणु
	अगर (is_simm13(K)) अणु
		/* or %g0, K, DEST */
		emit(OR | IMMED | RS1(G0) | S13(K) | RD(dest), ctx);
	पूर्ण अन्यथा अणु
		emit_set_स्थिर_sext(K, dest, ctx);
	पूर्ण
पूर्ण

अटल व्योम analyze_64bit_स्थिरant(u32 high_bits, u32 low_bits,
				   पूर्णांक *hbsp, पूर्णांक *lbsp, पूर्णांक *abbasp)
अणु
	पूर्णांक lowest_bit_set, highest_bit_set, all_bits_between_are_set;
	पूर्णांक i;

	lowest_bit_set = highest_bit_set = -1;
	i = 0;
	करो अणु
		अगर ((lowest_bit_set == -1) && ((low_bits >> i) & 1))
			lowest_bit_set = i;
		अगर ((highest_bit_set == -1) && ((high_bits >> (32 - i - 1)) & 1))
			highest_bit_set = (64 - i - 1);
	पूर्ण  जबतक (++i < 32 && (highest_bit_set == -1 ||
			       lowest_bit_set == -1));
	अगर (i == 32) अणु
		i = 0;
		करो अणु
			अगर (lowest_bit_set == -1 && ((high_bits >> i) & 1))
				lowest_bit_set = i + 32;
			अगर (highest_bit_set == -1 &&
			    ((low_bits >> (32 - i - 1)) & 1))
				highest_bit_set = 32 - i - 1;
		पूर्ण जबतक (++i < 32 && (highest_bit_set == -1 ||
				      lowest_bit_set == -1));
	पूर्ण

	all_bits_between_are_set = 1;
	क्रम (i = lowest_bit_set; i <= highest_bit_set; i++) अणु
		अगर (i < 32) अणु
			अगर ((low_bits & (1 << i)) != 0)
				जारी;
		पूर्ण अन्यथा अणु
			अगर ((high_bits & (1 << (i - 32))) != 0)
				जारी;
		पूर्ण
		all_bits_between_are_set = 0;
		अवरोध;
	पूर्ण
	*hbsp = highest_bit_set;
	*lbsp = lowest_bit_set;
	*abbasp = all_bits_between_are_set;
पूर्ण

अटल अचिन्हित दीर्घ create_simple_focus_bits(अचिन्हित दीर्घ high_bits,
					      अचिन्हित दीर्घ low_bits,
					      पूर्णांक lowest_bit_set, पूर्णांक shअगरt)
अणु
	दीर्घ hi, lo;

	अगर (lowest_bit_set < 32) अणु
		lo = (low_bits >> lowest_bit_set) << shअगरt;
		hi = ((high_bits << (32 - lowest_bit_set)) << shअगरt);
	पूर्ण अन्यथा अणु
		lo = 0;
		hi = ((high_bits >> (lowest_bit_set - 32)) << shअगरt);
	पूर्ण
	वापस hi | lo;
पूर्ण

अटल bool स्थिर64_is_2insns(अचिन्हित दीर्घ high_bits,
			      अचिन्हित दीर्घ low_bits)
अणु
	पूर्णांक highest_bit_set, lowest_bit_set, all_bits_between_are_set;

	अगर (high_bits == 0 || high_bits == 0xffffffff)
		वापस true;

	analyze_64bit_स्थिरant(high_bits, low_bits,
			       &highest_bit_set, &lowest_bit_set,
			       &all_bits_between_are_set);

	अगर ((highest_bit_set == 63 || lowest_bit_set == 0) &&
	    all_bits_between_are_set != 0)
		वापस true;

	अगर (highest_bit_set - lowest_bit_set < 21)
		वापस true;

	वापस false;
पूर्ण

अटल व्योम sparc_emit_set_स्थिर64_quick2(अचिन्हित दीर्घ high_bits,
					  अचिन्हित दीर्घ low_imm,
					  अचिन्हित पूर्णांक dest,
					  पूर्णांक shअगरt_count, काष्ठा jit_ctx *ctx)
अणु
	emit_loadimm32(high_bits, dest, ctx);

	/* Now shअगरt it up पूर्णांकo place.  */
	emit_alu_K(SLLX, dest, shअगरt_count, ctx);

	/* If there is a low immediate part piece, finish up by
	 * putting that in as well.
	 */
	अगर (low_imm != 0)
		emit(OR | IMMED | RS1(dest) | S13(low_imm) | RD(dest), ctx);
पूर्ण

अटल व्योम emit_loadimm64(u64 K, अचिन्हित पूर्णांक dest, काष्ठा jit_ctx *ctx)
अणु
	पूर्णांक all_bits_between_are_set, lowest_bit_set, highest_bit_set;
	अचिन्हित पूर्णांक पंचांगp = bpf2sparc[TMP_REG_1];
	u32 low_bits = (K & 0xffffffff);
	u32 high_bits = (K >> 32);

	/* These two tests also take care of all of the one
	 * inकाष्ठाion हालs.
	 */
	अगर (high_bits == 0xffffffff && (low_bits & 0x80000000))
		वापस emit_loadimm_sext(K, dest, ctx);
	अगर (high_bits == 0x00000000)
		वापस emit_loadimm32(K, dest, ctx);

	analyze_64bit_स्थिरant(high_bits, low_bits, &highest_bit_set,
			       &lowest_bit_set, &all_bits_between_are_set);

	/* 1) mov	-1, %reg
	 *    sllx	%reg, shअगरt, %reg
	 * 2) mov	-1, %reg
	 *    srlx	%reg, shअगरt, %reg
	 * 3) mov	some_small_स्थिर, %reg
	 *    sllx	%reg, shअगरt, %reg
	 */
	अगर (((highest_bit_set == 63 || lowest_bit_set == 0) &&
	     all_bits_between_are_set != 0) ||
	    ((highest_bit_set - lowest_bit_set) < 12)) अणु
		पूर्णांक shअगरt = lowest_bit_set;
		दीर्घ the_स्थिर = -1;

		अगर ((highest_bit_set != 63 && lowest_bit_set != 0) ||
		    all_bits_between_are_set == 0) अणु
			the_स्थिर =
				create_simple_focus_bits(high_bits, low_bits,
							 lowest_bit_set, 0);
		पूर्ण अन्यथा अगर (lowest_bit_set == 0)
			shअगरt = -(63 - highest_bit_set);

		emit(OR | IMMED | RS1(G0) | S13(the_स्थिर) | RD(dest), ctx);
		अगर (shअगरt > 0)
			emit_alu_K(SLLX, dest, shअगरt, ctx);
		अन्यथा अगर (shअगरt < 0)
			emit_alu_K(SRLX, dest, -shअगरt, ctx);

		वापस;
	पूर्ण

	/* Now a range of 22 or less bits set somewhere.
	 * 1) sethi	%hi(focus_bits), %reg
	 *    sllx	%reg, shअगरt, %reg
	 * 2) sethi	%hi(focus_bits), %reg
	 *    srlx	%reg, shअगरt, %reg
	 */
	अगर ((highest_bit_set - lowest_bit_set) < 21) अणु
		अचिन्हित दीर्घ focus_bits =
			create_simple_focus_bits(high_bits, low_bits,
						 lowest_bit_set, 10);

		emit(SETHI(focus_bits, dest), ctx);

		/* If lowest_bit_set == 10 then a sethi alone could
		 * have करोne it.
		 */
		अगर (lowest_bit_set < 10)
			emit_alu_K(SRLX, dest, 10 - lowest_bit_set, ctx);
		अन्यथा अगर (lowest_bit_set > 10)
			emit_alu_K(SLLX, dest, lowest_bit_set - 10, ctx);
		वापस;
	पूर्ण

	/* Ok, now 3 inकाष्ठाion sequences.  */
	अगर (low_bits == 0) अणु
		emit_loadimm32(high_bits, dest, ctx);
		emit_alu_K(SLLX, dest, 32, ctx);
		वापस;
	पूर्ण

	/* We may be able to करो something quick
	 * when the स्थिरant is negated, so try that.
	 */
	अगर (स्थिर64_is_2insns((~high_bits) & 0xffffffff,
			      (~low_bits) & 0xfffffc00)) अणु
		/* NOTE: The trailing bits get XOR'd so we need the
		 * non-negated bits, not the negated ones.
		 */
		अचिन्हित दीर्घ trailing_bits = low_bits & 0x3ff;

		अगर ((((~high_bits) & 0xffffffff) == 0 &&
		     ((~low_bits) & 0x80000000) == 0) ||
		    (((~high_bits) & 0xffffffff) == 0xffffffff &&
		     ((~low_bits) & 0x80000000) != 0)) अणु
			अचिन्हित दीर्घ fast_पूर्णांक = (~low_bits & 0xffffffff);

			अगर ((is_sethi(fast_पूर्णांक) &&
			     (~high_bits & 0xffffffff) == 0)) अणु
				emit(SETHI(fast_पूर्णांक, dest), ctx);
			पूर्ण अन्यथा अगर (is_simm13(fast_पूर्णांक)) अणु
				emit(OR | IMMED | RS1(G0) | S13(fast_पूर्णांक) | RD(dest), ctx);
			पूर्ण अन्यथा अणु
				emit_loadimm64(fast_पूर्णांक, dest, ctx);
			पूर्ण
		पूर्ण अन्यथा अणु
			u64 n = ((~low_bits) & 0xfffffc00) |
				(((अचिन्हित दीर्घ)((~high_bits) & 0xffffffff))<<32);
			emit_loadimm64(n, dest, ctx);
		पूर्ण

		low_bits = -0x400 | trailing_bits;

		emit(XOR | IMMED | RS1(dest) | S13(low_bits) | RD(dest), ctx);
		वापस;
	पूर्ण

	/* 1) sethi	%hi(xxx), %reg
	 *    or	%reg, %lo(xxx), %reg
	 *    sllx	%reg, yyy, %reg
	 */
	अगर ((highest_bit_set - lowest_bit_set) < 32) अणु
		अचिन्हित दीर्घ focus_bits =
			create_simple_focus_bits(high_bits, low_bits,
						 lowest_bit_set, 0);

		/* So what we know is that the set bits straddle the
		 * middle of the 64-bit word.
		 */
		sparc_emit_set_स्थिर64_quick2(focus_bits, 0, dest,
					      lowest_bit_set, ctx);
		वापस;
	पूर्ण

	/* 1) sethi	%hi(high_bits), %reg
	 *    or	%reg, %lo(high_bits), %reg
	 *    sllx	%reg, 32, %reg
	 *    or	%reg, low_bits, %reg
	 */
	अगर (is_simm13(low_bits) && ((पूर्णांक)low_bits > 0)) अणु
		sparc_emit_set_स्थिर64_quick2(high_bits, low_bits,
					      dest, 32, ctx);
		वापस;
	पूर्ण

	/* Oh well, we tried... Do a full 64-bit decomposition.  */
	ctx->पंचांगp_1_used = true;

	emit_loadimm32(high_bits, पंचांगp, ctx);
	emit_loadimm32(low_bits, dest, ctx);
	emit_alu_K(SLLX, पंचांगp, 32, ctx);
	emit(OR | RS1(dest) | RS2(पंचांगp) | RD(dest), ctx);
पूर्ण

अटल व्योम emit_branch(अचिन्हित पूर्णांक br_opc, अचिन्हित पूर्णांक from_idx, अचिन्हित पूर्णांक to_idx,
			काष्ठा jit_ctx *ctx)
अणु
	अचिन्हित पूर्णांक off = to_idx - from_idx;

	अगर (br_opc & XCC)
		emit(br_opc | WDISP19(off << 2), ctx);
	अन्यथा
		emit(br_opc | WDISP22(off << 2), ctx);
पूर्ण

अटल व्योम emit_cbcond(अचिन्हित पूर्णांक cb_opc, अचिन्हित पूर्णांक from_idx, अचिन्हित पूर्णांक to_idx,
			स्थिर u8 dst, स्थिर u8 src, काष्ठा jit_ctx *ctx)
अणु
	अचिन्हित पूर्णांक off = to_idx - from_idx;

	emit(cb_opc | WDISP10(off << 2) | RS1(dst) | RS2(src), ctx);
पूर्ण

अटल व्योम emit_cbcondi(अचिन्हित पूर्णांक cb_opc, अचिन्हित पूर्णांक from_idx, अचिन्हित पूर्णांक to_idx,
			 स्थिर u8 dst, s32 imm, काष्ठा jit_ctx *ctx)
अणु
	अचिन्हित पूर्णांक off = to_idx - from_idx;

	emit(cb_opc | IMMED | WDISP10(off << 2) | RS1(dst) | S5(imm), ctx);
पूर्ण

#घोषणा emit_पढ़ो_y(REG, CTX)	emit(RD_Y | RD(REG), CTX)
#घोषणा emit_ग_लिखो_y(REG, CTX)	emit(WR_Y | IMMED | RS1(REG) | S13(0), CTX)

#घोषणा emit_cmp(R1, R2, CTX)				\
	emit(SUBCC | RS1(R1) | RS2(R2) | RD(G0), CTX)

#घोषणा emit_cmpi(R1, IMM, CTX)				\
	emit(SUBCC | IMMED | RS1(R1) | S13(IMM) | RD(G0), CTX)

#घोषणा emit_btst(R1, R2, CTX)				\
	emit(ANDCC | RS1(R1) | RS2(R2) | RD(G0), CTX)

#घोषणा emit_btsti(R1, IMM, CTX)			\
	emit(ANDCC | IMMED | RS1(R1) | S13(IMM) | RD(G0), CTX)

अटल पूर्णांक emit_compare_and_branch(स्थिर u8 code, स्थिर u8 dst, u8 src,
				   स्थिर s32 imm, bool is_imm, पूर्णांक branch_dst,
				   काष्ठा jit_ctx *ctx)
अणु
	bool use_cbcond = (sparc64_elf_hwcap & AV_SPARC_CBCOND) != 0;
	स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];

	branch_dst = ctx->offset[branch_dst];

	अगर (!is_simm10(branch_dst - ctx->idx) ||
	    BPF_OP(code) == BPF_JSET)
		use_cbcond = false;

	अगर (is_imm) अणु
		bool fits = true;

		अगर (use_cbcond) अणु
			अगर (!is_simm5(imm))
				fits = false;
		पूर्ण अन्यथा अगर (!is_simm13(imm)) अणु
			fits = false;
		पूर्ण
		अगर (!fits) अणु
			ctx->पंचांगp_1_used = true;
			emit_loadimm_sext(imm, पंचांगp, ctx);
			src = पंचांगp;
			is_imm = false;
		पूर्ण
	पूर्ण

	अगर (!use_cbcond) अणु
		u32 br_opcode;

		अगर (BPF_OP(code) == BPF_JSET) अणु
			अगर (is_imm)
				emit_btsti(dst, imm, ctx);
			अन्यथा
				emit_btst(dst, src, ctx);
		पूर्ण अन्यथा अणु
			अगर (is_imm)
				emit_cmpi(dst, imm, ctx);
			अन्यथा
				emit_cmp(dst, src, ctx);
		पूर्ण
		चयन (BPF_OP(code)) अणु
		हाल BPF_JEQ:
			br_opcode = BE;
			अवरोध;
		हाल BPF_JGT:
			br_opcode = BGU;
			अवरोध;
		हाल BPF_JLT:
			br_opcode = BLU;
			अवरोध;
		हाल BPF_JGE:
			br_opcode = BGEU;
			अवरोध;
		हाल BPF_JLE:
			br_opcode = BLEU;
			अवरोध;
		हाल BPF_JSET:
		हाल BPF_JNE:
			br_opcode = BNE;
			अवरोध;
		हाल BPF_JSGT:
			br_opcode = BG;
			अवरोध;
		हाल BPF_JSLT:
			br_opcode = BL;
			अवरोध;
		हाल BPF_JSGE:
			br_opcode = BGE;
			अवरोध;
		हाल BPF_JSLE:
			br_opcode = BLE;
			अवरोध;
		शेष:
			/* Make sure we करोnt leak kernel inक्रमmation to the
			 * user.
			 */
			वापस -EFAULT;
		पूर्ण
		emit_branch(br_opcode, ctx->idx, branch_dst, ctx);
		emit_nop(ctx);
	पूर्ण अन्यथा अणु
		u32 cbcond_opcode;

		चयन (BPF_OP(code)) अणु
		हाल BPF_JEQ:
			cbcond_opcode = CBCONDE;
			अवरोध;
		हाल BPF_JGT:
			cbcond_opcode = CBCONDGU;
			अवरोध;
		हाल BPF_JLT:
			cbcond_opcode = CBCONDLU;
			अवरोध;
		हाल BPF_JGE:
			cbcond_opcode = CBCONDGEU;
			अवरोध;
		हाल BPF_JLE:
			cbcond_opcode = CBCONDLEU;
			अवरोध;
		हाल BPF_JNE:
			cbcond_opcode = CBCONDNE;
			अवरोध;
		हाल BPF_JSGT:
			cbcond_opcode = CBCONDG;
			अवरोध;
		हाल BPF_JSLT:
			cbcond_opcode = CBCONDL;
			अवरोध;
		हाल BPF_JSGE:
			cbcond_opcode = CBCONDGE;
			अवरोध;
		हाल BPF_JSLE:
			cbcond_opcode = CBCONDLE;
			अवरोध;
		शेष:
			/* Make sure we करोnt leak kernel inक्रमmation to the
			 * user.
			 */
			वापस -EFAULT;
		पूर्ण
		cbcond_opcode |= CBCOND_OP;
		अगर (is_imm)
			emit_cbcondi(cbcond_opcode, ctx->idx, branch_dst,
				     dst, imm, ctx);
		अन्यथा
			emit_cbcond(cbcond_opcode, ctx->idx, branch_dst,
				    dst, src, ctx);
	पूर्ण
	वापस 0;
पूर्ण

/* Just skip the save inकाष्ठाion and the ctx रेजिस्टर move.  */
#घोषणा BPF_TAILCALL_PROLOGUE_SKIP	32
#घोषणा BPF_TAILCALL_CNT_SP_OFF		(STACK_BIAS + 128)

अटल व्योम build_prologue(काष्ठा jit_ctx *ctx)
अणु
	s32 stack_needed = BASE_STACKFRAME;

	अगर (ctx->saw_frame_poपूर्णांकer || ctx->saw_tail_call) अणु
		काष्ठा bpf_prog *prog = ctx->prog;
		u32 stack_depth;

		stack_depth = prog->aux->stack_depth;
		stack_needed += round_up(stack_depth, 16);
	पूर्ण

	अगर (ctx->saw_tail_call)
		stack_needed += 8;

	/* save %sp, -176, %sp */
	emit(SAVE | IMMED | RS1(SP) | S13(-stack_needed) | RD(SP), ctx);

	/* tail_call_cnt = 0 */
	अगर (ctx->saw_tail_call) अणु
		u32 off = BPF_TAILCALL_CNT_SP_OFF;

		emit(ST32 | IMMED | RS1(SP) | S13(off) | RD(G0), ctx);
	पूर्ण अन्यथा अणु
		emit_nop(ctx);
	पूर्ण
	अगर (ctx->saw_frame_poपूर्णांकer) अणु
		स्थिर u8 vfp = bpf2sparc[BPF_REG_FP];

		emit(ADD | IMMED | RS1(FP) | S13(STACK_BIAS) | RD(vfp), ctx);
	पूर्ण अन्यथा अणु
		emit_nop(ctx);
	पूर्ण

	emit_reg_move(I0, O0, ctx);
	emit_reg_move(I1, O1, ctx);
	emit_reg_move(I2, O2, ctx);
	emit_reg_move(I3, O3, ctx);
	emit_reg_move(I4, O4, ctx);
	/* If you add anything here, adjust BPF_TAILCALL_PROLOGUE_SKIP above. */
पूर्ण

अटल व्योम build_epilogue(काष्ठा jit_ctx *ctx)
अणु
	ctx->epilogue_offset = ctx->idx;

	/* ret (jmpl %i7 + 8, %g0) */
	emit(JMPL | IMMED | RS1(I7) | S13(8) | RD(G0), ctx);

	/* restore %i5, %g0, %o0 */
	emit(RESTORE | RS1(bpf2sparc[BPF_REG_0]) | RS2(G0) | RD(O0), ctx);
पूर्ण

अटल व्योम emit_tail_call(काष्ठा jit_ctx *ctx)
अणु
	स्थिर u8 bpf_array = bpf2sparc[BPF_REG_2];
	स्थिर u8 bpf_index = bpf2sparc[BPF_REG_3];
	स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];
	u32 off;

	ctx->saw_tail_call = true;

	off = दुरत्व(काष्ठा bpf_array, map.max_entries);
	emit(LD32 | IMMED | RS1(bpf_array) | S13(off) | RD(पंचांगp), ctx);
	emit_cmp(bpf_index, पंचांगp, ctx);
#घोषणा OFFSET1 17
	emit_branch(BGEU, ctx->idx, ctx->idx + OFFSET1, ctx);
	emit_nop(ctx);

	off = BPF_TAILCALL_CNT_SP_OFF;
	emit(LD32 | IMMED | RS1(SP) | S13(off) | RD(पंचांगp), ctx);
	emit_cmpi(पंचांगp, MAX_TAIL_CALL_CNT, ctx);
#घोषणा OFFSET2 13
	emit_branch(BGU, ctx->idx, ctx->idx + OFFSET2, ctx);
	emit_nop(ctx);

	emit_alu_K(ADD, पंचांगp, 1, ctx);
	off = BPF_TAILCALL_CNT_SP_OFF;
	emit(ST32 | IMMED | RS1(SP) | S13(off) | RD(पंचांगp), ctx);

	emit_alu3_K(SLL, bpf_index, 3, पंचांगp, ctx);
	emit_alu(ADD, bpf_array, पंचांगp, ctx);
	off = दुरत्व(काष्ठा bpf_array, ptrs);
	emit(LD64 | IMMED | RS1(पंचांगp) | S13(off) | RD(पंचांगp), ctx);

	emit_cmpi(पंचांगp, 0, ctx);
#घोषणा OFFSET3 5
	emit_branch(BE, ctx->idx, ctx->idx + OFFSET3, ctx);
	emit_nop(ctx);

	off = दुरत्व(काष्ठा bpf_prog, bpf_func);
	emit(LD64 | IMMED | RS1(पंचांगp) | S13(off) | RD(पंचांगp), ctx);

	off = BPF_TAILCALL_PROLOGUE_SKIP;
	emit(JMPL | IMMED | RS1(पंचांगp) | S13(off) | RD(G0), ctx);
	emit_nop(ctx);
पूर्ण

अटल पूर्णांक build_insn(स्थिर काष्ठा bpf_insn *insn, काष्ठा jit_ctx *ctx)
अणु
	स्थिर u8 code = insn->code;
	स्थिर u8 dst = bpf2sparc[insn->dst_reg];
	स्थिर u8 src = bpf2sparc[insn->src_reg];
	स्थिर पूर्णांक i = insn - ctx->prog->insnsi;
	स्थिर s16 off = insn->off;
	स्थिर s32 imm = insn->imm;

	अगर (insn->src_reg == BPF_REG_FP)
		ctx->saw_frame_poपूर्णांकer = true;

	चयन (code) अणु
	/* dst = src */
	हाल BPF_ALU | BPF_MOV | BPF_X:
		emit_alu3_K(SRL, src, 0, dst, ctx);
		अगर (insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	हाल BPF_ALU64 | BPF_MOV | BPF_X:
		emit_reg_move(src, dst, ctx);
		अवरोध;
	/* dst = dst OP src */
	हाल BPF_ALU | BPF_ADD | BPF_X:
	हाल BPF_ALU64 | BPF_ADD | BPF_X:
		emit_alu(ADD, src, dst, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_SUB | BPF_X:
	हाल BPF_ALU64 | BPF_SUB | BPF_X:
		emit_alu(SUB, src, dst, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_AND | BPF_X:
	हाल BPF_ALU64 | BPF_AND | BPF_X:
		emit_alu(AND, src, dst, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_OR | BPF_X:
	हाल BPF_ALU64 | BPF_OR | BPF_X:
		emit_alu(OR, src, dst, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_XOR | BPF_X:
	हाल BPF_ALU64 | BPF_XOR | BPF_X:
		emit_alu(XOR, src, dst, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_MUL | BPF_X:
		emit_alu(MUL, src, dst, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU64 | BPF_MUL | BPF_X:
		emit_alu(MULX, src, dst, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_DIV | BPF_X:
		emit_ग_लिखो_y(G0, ctx);
		emit_alu(DIV, src, dst, ctx);
		अगर (insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	हाल BPF_ALU64 | BPF_DIV | BPF_X:
		emit_alu(UDIVX, src, dst, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_MOD | BPF_X: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];

		ctx->पंचांगp_1_used = true;

		emit_ग_लिखो_y(G0, ctx);
		emit_alu3(DIV, dst, src, पंचांगp, ctx);
		emit_alu3(MULX, पंचांगp, src, पंचांगp, ctx);
		emit_alu3(SUB, dst, पंचांगp, dst, ctx);
		जाओ करो_alu32_trunc;
	पूर्ण
	हाल BPF_ALU64 | BPF_MOD | BPF_X: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];

		ctx->पंचांगp_1_used = true;

		emit_alu3(UDIVX, dst, src, पंचांगp, ctx);
		emit_alu3(MULX, पंचांगp, src, पंचांगp, ctx);
		emit_alu3(SUB, dst, पंचांगp, dst, ctx);
		अवरोध;
	पूर्ण
	हाल BPF_ALU | BPF_LSH | BPF_X:
		emit_alu(SLL, src, dst, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU64 | BPF_LSH | BPF_X:
		emit_alu(SLLX, src, dst, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_RSH | BPF_X:
		emit_alu(SRL, src, dst, ctx);
		अगर (insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	हाल BPF_ALU64 | BPF_RSH | BPF_X:
		emit_alu(SRLX, src, dst, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_ARSH | BPF_X:
		emit_alu(SRA, src, dst, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU64 | BPF_ARSH | BPF_X:
		emit_alu(SRAX, src, dst, ctx);
		अवरोध;

	/* dst = -dst */
	हाल BPF_ALU | BPF_NEG:
	हाल BPF_ALU64 | BPF_NEG:
		emit(SUB | RS1(0) | RS2(dst) | RD(dst), ctx);
		जाओ करो_alu32_trunc;

	हाल BPF_ALU | BPF_END | BPF_FROM_BE:
		चयन (imm) अणु
		हाल 16:
			emit_alu_K(SLL, dst, 16, ctx);
			emit_alu_K(SRL, dst, 16, ctx);
			अगर (insn_is_zext(&insn[1]))
				वापस 1;
			अवरोध;
		हाल 32:
			अगर (!ctx->prog->aux->verअगरier_zext)
				emit_alu_K(SRL, dst, 0, ctx);
			अवरोध;
		हाल 64:
			/* nop */
			अवरोध;

		पूर्ण
		अवरोध;

	/* dst = BSWAP##imm(dst) */
	हाल BPF_ALU | BPF_END | BPF_FROM_LE: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];
		स्थिर u8 पंचांगp2 = bpf2sparc[TMP_REG_2];

		ctx->पंचांगp_1_used = true;
		चयन (imm) अणु
		हाल 16:
			emit_alu3_K(AND, dst, 0xff, पंचांगp, ctx);
			emit_alu3_K(SRL, dst, 8, dst, ctx);
			emit_alu3_K(AND, dst, 0xff, dst, ctx);
			emit_alu3_K(SLL, पंचांगp, 8, पंचांगp, ctx);
			emit_alu(OR, पंचांगp, dst, ctx);
			अगर (insn_is_zext(&insn[1]))
				वापस 1;
			अवरोध;

		हाल 32:
			ctx->पंचांगp_2_used = true;
			emit_alu3_K(SRL, dst, 24, पंचांगp, ctx);	/* पंचांगp  = dst >> 24 */
			emit_alu3_K(SRL, dst, 16, पंचांगp2, ctx);	/* पंचांगp2 = dst >> 16 */
			emit_alu3_K(AND, पंचांगp2, 0xff, पंचांगp2, ctx);/* पंचांगp2 = पंचांगp2 & 0xff */
			emit_alu3_K(SLL, पंचांगp2, 8, पंचांगp2, ctx);	/* पंचांगp2 = पंचांगp2 << 8 */
			emit_alu(OR, पंचांगp2, पंचांगp, ctx);		/* पंचांगp  = पंचांगp | पंचांगp2 */
			emit_alu3_K(SRL, dst, 8, पंचांगp2, ctx);	/* पंचांगp2 = dst >> 8 */
			emit_alu3_K(AND, पंचांगp2, 0xff, पंचांगp2, ctx);/* पंचांगp2 = पंचांगp2 & 0xff */
			emit_alu3_K(SLL, पंचांगp2, 16, पंचांगp2, ctx);	/* पंचांगp2 = पंचांगp2 << 16 */
			emit_alu(OR, पंचांगp2, पंचांगp, ctx);		/* पंचांगp  = पंचांगp | पंचांगp2 */
			emit_alu3_K(AND, dst, 0xff, dst, ctx);	/* dst	= dst & 0xff */
			emit_alu3_K(SLL, dst, 24, dst, ctx);	/* dst  = dst << 24 */
			emit_alu(OR, पंचांगp, dst, ctx);		/* dst  = dst | पंचांगp */
			अगर (insn_is_zext(&insn[1]))
				वापस 1;
			अवरोध;

		हाल 64:
			emit_alu3_K(ADD, SP, STACK_BIAS + 128, पंचांगp, ctx);
			emit(ST64 | RS1(पंचांगp) | RS2(G0) | RD(dst), ctx);
			emit(LD64A | ASI(ASI_PL) | RS1(पंचांगp) | RS2(G0) | RD(dst), ctx);
			अवरोध;
		पूर्ण
		अवरोध;
	पूर्ण
	/* dst = imm */
	हाल BPF_ALU | BPF_MOV | BPF_K:
		emit_loadimm32(imm, dst, ctx);
		अगर (insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	हाल BPF_ALU64 | BPF_MOV | BPF_K:
		emit_loadimm_sext(imm, dst, ctx);
		अवरोध;
	/* dst = dst OP imm */
	हाल BPF_ALU | BPF_ADD | BPF_K:
	हाल BPF_ALU64 | BPF_ADD | BPF_K:
		emit_alu_K(ADD, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_SUB | BPF_K:
	हाल BPF_ALU64 | BPF_SUB | BPF_K:
		emit_alu_K(SUB, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_AND | BPF_K:
	हाल BPF_ALU64 | BPF_AND | BPF_K:
		emit_alu_K(AND, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_OR | BPF_K:
	हाल BPF_ALU64 | BPF_OR | BPF_K:
		emit_alu_K(OR, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_XOR | BPF_K:
	हाल BPF_ALU64 | BPF_XOR | BPF_K:
		emit_alu_K(XOR, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU | BPF_MUL | BPF_K:
		emit_alu_K(MUL, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU64 | BPF_MUL | BPF_K:
		emit_alu_K(MULX, dst, imm, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_DIV | BPF_K:
		अगर (imm == 0)
			वापस -EINVAL;

		emit_ग_लिखो_y(G0, ctx);
		emit_alu_K(DIV, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU64 | BPF_DIV | BPF_K:
		अगर (imm == 0)
			वापस -EINVAL;

		emit_alu_K(UDIVX, dst, imm, ctx);
		अवरोध;
	हाल BPF_ALU64 | BPF_MOD | BPF_K:
	हाल BPF_ALU | BPF_MOD | BPF_K: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_2];
		अचिन्हित पूर्णांक भाग;

		अगर (imm == 0)
			वापस -EINVAL;

		भाग = (BPF_CLASS(code) == BPF_ALU64) ? UDIVX : DIV;

		ctx->पंचांगp_2_used = true;

		अगर (BPF_CLASS(code) != BPF_ALU64)
			emit_ग_लिखो_y(G0, ctx);
		अगर (is_simm13(imm)) अणु
			emit(भाग | IMMED | RS1(dst) | S13(imm) | RD(पंचांगp), ctx);
			emit(MULX | IMMED | RS1(पंचांगp) | S13(imm) | RD(पंचांगp), ctx);
			emit(SUB | RS1(dst) | RS2(पंचांगp) | RD(dst), ctx);
		पूर्ण अन्यथा अणु
			स्थिर u8 पंचांगp1 = bpf2sparc[TMP_REG_1];

			ctx->पंचांगp_1_used = true;

			emit_set_स्थिर_sext(imm, पंचांगp1, ctx);
			emit(भाग | RS1(dst) | RS2(पंचांगp1) | RD(पंचांगp), ctx);
			emit(MULX | RS1(पंचांगp) | RS2(पंचांगp1) | RD(पंचांगp), ctx);
			emit(SUB | RS1(dst) | RS2(पंचांगp) | RD(dst), ctx);
		पूर्ण
		जाओ करो_alu32_trunc;
	पूर्ण
	हाल BPF_ALU | BPF_LSH | BPF_K:
		emit_alu_K(SLL, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU64 | BPF_LSH | BPF_K:
		emit_alu_K(SLLX, dst, imm, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_RSH | BPF_K:
		emit_alu_K(SRL, dst, imm, ctx);
		अगर (insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	हाल BPF_ALU64 | BPF_RSH | BPF_K:
		emit_alu_K(SRLX, dst, imm, ctx);
		अवरोध;
	हाल BPF_ALU | BPF_ARSH | BPF_K:
		emit_alu_K(SRA, dst, imm, ctx);
		जाओ करो_alu32_trunc;
	हाल BPF_ALU64 | BPF_ARSH | BPF_K:
		emit_alu_K(SRAX, dst, imm, ctx);
		अवरोध;

	करो_alu32_trunc:
		अगर (BPF_CLASS(code) == BPF_ALU &&
		    !ctx->prog->aux->verअगरier_zext)
			emit_alu_K(SRL, dst, 0, ctx);
		अवरोध;

	/* JUMP off */
	हाल BPF_JMP | BPF_JA:
		emit_branch(BA, ctx->idx, ctx->offset[i + off], ctx);
		emit_nop(ctx);
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
	हाल BPF_JMP | BPF_JSET | BPF_X: अणु
		पूर्णांक err;

		err = emit_compare_and_branch(code, dst, src, 0, false, i + off, ctx);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण
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
	हाल BPF_JMP | BPF_JSET | BPF_K: अणु
		पूर्णांक err;

		err = emit_compare_and_branch(code, dst, 0, imm, true, i + off, ctx);
		अगर (err)
			वापस err;
		अवरोध;
	पूर्ण

	/* function call */
	हाल BPF_JMP | BPF_CALL:
	अणु
		u8 *func = ((u8 *)__bpf_call_base) + imm;

		ctx->saw_call = true;

		emit_call((u32 *)func, ctx);
		emit_nop(ctx);

		emit_reg_move(O0, bpf2sparc[BPF_REG_0], ctx);
		अवरोध;
	पूर्ण

	/* tail call */
	हाल BPF_JMP | BPF_TAIL_CALL:
		emit_tail_call(ctx);
		अवरोध;

	/* function वापस */
	हाल BPF_JMP | BPF_EXIT:
		/* Optimization: when last inकाष्ठाion is EXIT,
		   simply fallthrough to epilogue. */
		अगर (i == ctx->prog->len - 1)
			अवरोध;
		emit_branch(BA, ctx->idx, ctx->epilogue_offset, ctx);
		emit_nop(ctx);
		अवरोध;

	/* dst = imm64 */
	हाल BPF_LD | BPF_IMM | BPF_DW:
	अणु
		स्थिर काष्ठा bpf_insn insn1 = insn[1];
		u64 imm64;

		imm64 = (u64)insn1.imm << 32 | (u32)imm;
		emit_loadimm64(imm64, dst, ctx);

		वापस 1;
	पूर्ण

	/* LDX: dst = *(size *)(src + off) */
	हाल BPF_LDX | BPF_MEM | BPF_W:
	हाल BPF_LDX | BPF_MEM | BPF_H:
	हाल BPF_LDX | BPF_MEM | BPF_B:
	हाल BPF_LDX | BPF_MEM | BPF_DW: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];
		u32 opcode = 0, rs2;

		ctx->पंचांगp_1_used = true;
		चयन (BPF_SIZE(code)) अणु
		हाल BPF_W:
			opcode = LD32;
			अवरोध;
		हाल BPF_H:
			opcode = LD16;
			अवरोध;
		हाल BPF_B:
			opcode = LD8;
			अवरोध;
		हाल BPF_DW:
			opcode = LD64;
			अवरोध;
		पूर्ण

		अगर (is_simm13(off)) अणु
			opcode |= IMMED;
			rs2 = S13(off);
		पूर्ण अन्यथा अणु
			emit_loadimm(off, पंचांगp, ctx);
			rs2 = RS2(पंचांगp);
		पूर्ण
		emit(opcode | RS1(src) | rs2 | RD(dst), ctx);
		अगर (opcode != LD64 && insn_is_zext(&insn[1]))
			वापस 1;
		अवरोध;
	पूर्ण
	/* ST: *(size *)(dst + off) = imm */
	हाल BPF_ST | BPF_MEM | BPF_W:
	हाल BPF_ST | BPF_MEM | BPF_H:
	हाल BPF_ST | BPF_MEM | BPF_B:
	हाल BPF_ST | BPF_MEM | BPF_DW: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];
		स्थिर u8 पंचांगp2 = bpf2sparc[TMP_REG_2];
		u32 opcode = 0, rs2;

		अगर (insn->dst_reg == BPF_REG_FP)
			ctx->saw_frame_poपूर्णांकer = true;

		ctx->पंचांगp_2_used = true;
		emit_loadimm(imm, पंचांगp2, ctx);

		चयन (BPF_SIZE(code)) अणु
		हाल BPF_W:
			opcode = ST32;
			अवरोध;
		हाल BPF_H:
			opcode = ST16;
			अवरोध;
		हाल BPF_B:
			opcode = ST8;
			अवरोध;
		हाल BPF_DW:
			opcode = ST64;
			अवरोध;
		पूर्ण

		अगर (is_simm13(off)) अणु
			opcode |= IMMED;
			rs2 = S13(off);
		पूर्ण अन्यथा अणु
			ctx->पंचांगp_1_used = true;
			emit_loadimm(off, पंचांगp, ctx);
			rs2 = RS2(पंचांगp);
		पूर्ण
		emit(opcode | RS1(dst) | rs2 | RD(पंचांगp2), ctx);
		अवरोध;
	पूर्ण

	/* STX: *(size *)(dst + off) = src */
	हाल BPF_STX | BPF_MEM | BPF_W:
	हाल BPF_STX | BPF_MEM | BPF_H:
	हाल BPF_STX | BPF_MEM | BPF_B:
	हाल BPF_STX | BPF_MEM | BPF_DW: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];
		u32 opcode = 0, rs2;

		अगर (insn->dst_reg == BPF_REG_FP)
			ctx->saw_frame_poपूर्णांकer = true;

		चयन (BPF_SIZE(code)) अणु
		हाल BPF_W:
			opcode = ST32;
			अवरोध;
		हाल BPF_H:
			opcode = ST16;
			अवरोध;
		हाल BPF_B:
			opcode = ST8;
			अवरोध;
		हाल BPF_DW:
			opcode = ST64;
			अवरोध;
		पूर्ण
		अगर (is_simm13(off)) अणु
			opcode |= IMMED;
			rs2 = S13(off);
		पूर्ण अन्यथा अणु
			ctx->पंचांगp_1_used = true;
			emit_loadimm(off, पंचांगp, ctx);
			rs2 = RS2(पंचांगp);
		पूर्ण
		emit(opcode | RS1(dst) | rs2 | RD(src), ctx);
		अवरोध;
	पूर्ण

	हाल BPF_STX | BPF_ATOMIC | BPF_W: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];
		स्थिर u8 पंचांगp2 = bpf2sparc[TMP_REG_2];
		स्थिर u8 पंचांगp3 = bpf2sparc[TMP_REG_3];

		अगर (insn->imm != BPF_ADD) अणु
			pr_err_once("unknown atomic op %02x\n", insn->imm);
			वापस -EINVAL;
		पूर्ण

		/* lock *(u32 *)(dst + off) += src */

		अगर (insn->dst_reg == BPF_REG_FP)
			ctx->saw_frame_poपूर्णांकer = true;

		ctx->पंचांगp_1_used = true;
		ctx->पंचांगp_2_used = true;
		ctx->पंचांगp_3_used = true;
		emit_loadimm(off, पंचांगp, ctx);
		emit_alu3(ADD, dst, पंचांगp, पंचांगp, ctx);

		emit(LD32 | RS1(पंचांगp) | RS2(G0) | RD(पंचांगp2), ctx);
		emit_alu3(ADD, पंचांगp2, src, पंचांगp3, ctx);
		emit(CAS | ASI(ASI_P) | RS1(पंचांगp) | RS2(पंचांगp2) | RD(पंचांगp3), ctx);
		emit_cmp(पंचांगp2, पंचांगp3, ctx);
		emit_branch(BNE, 4, 0, ctx);
		emit_nop(ctx);
		अवरोध;
	पूर्ण
	/* STX XADD: lock *(u64 *)(dst + off) += src */
	हाल BPF_STX | BPF_ATOMIC | BPF_DW: अणु
		स्थिर u8 पंचांगp = bpf2sparc[TMP_REG_1];
		स्थिर u8 पंचांगp2 = bpf2sparc[TMP_REG_2];
		स्थिर u8 पंचांगp3 = bpf2sparc[TMP_REG_3];

		अगर (insn->imm != BPF_ADD) अणु
			pr_err_once("unknown atomic op %02x\n", insn->imm);
			वापस -EINVAL;
		पूर्ण

		अगर (insn->dst_reg == BPF_REG_FP)
			ctx->saw_frame_poपूर्णांकer = true;

		ctx->पंचांगp_1_used = true;
		ctx->पंचांगp_2_used = true;
		ctx->पंचांगp_3_used = true;
		emit_loadimm(off, पंचांगp, ctx);
		emit_alu3(ADD, dst, पंचांगp, पंचांगp, ctx);

		emit(LD64 | RS1(पंचांगp) | RS2(G0) | RD(पंचांगp2), ctx);
		emit_alu3(ADD, पंचांगp2, src, पंचांगp3, ctx);
		emit(CASX | ASI(ASI_P) | RS1(पंचांगp) | RS2(पंचांगp2) | RD(पंचांगp3), ctx);
		emit_cmp(पंचांगp2, पंचांगp3, ctx);
		emit_branch(BNE, 4, 0, ctx);
		emit_nop(ctx);
		अवरोध;
	पूर्ण

	शेष:
		pr_err_once("unknown opcode %02x\n", code);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक build_body(काष्ठा jit_ctx *ctx)
अणु
	स्थिर काष्ठा bpf_prog *prog = ctx->prog;
	पूर्णांक i;

	क्रम (i = 0; i < prog->len; i++) अणु
		स्थिर काष्ठा bpf_insn *insn = &prog->insnsi[i];
		पूर्णांक ret;

		ret = build_insn(insn, ctx);

		अगर (ret > 0) अणु
			i++;
			ctx->offset[i] = ctx->idx;
			जारी;
		पूर्ण
		ctx->offset[i] = ctx->idx;
		अगर (ret)
			वापस ret;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम jit_fill_hole(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	u32 *ptr;
	/* We are guaranteed to have aligned memory. */
	क्रम (ptr = area; size >= माप(u32); size -= माप(u32))
		*ptr++ = 0x91d02005; /* ta 5 */
पूर्ण

bool bpf_jit_needs_zext(व्योम)
अणु
	वापस true;
पूर्ण

काष्ठा sparc64_jit_data अणु
	काष्ठा bpf_binary_header *header;
	u8 *image;
	काष्ठा jit_ctx ctx;
पूर्ण;

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_prog *पंचांगp, *orig_prog = prog;
	काष्ठा sparc64_jit_data *jit_data;
	काष्ठा bpf_binary_header *header;
	u32 prev_image_size, image_size;
	bool पंचांगp_blinded = false;
	bool extra_pass = false;
	काष्ठा jit_ctx ctx;
	u8 *image_ptr;
	पूर्णांक pass, i;

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
		image_size = माप(u32) * ctx.idx;
		prev_image_size = image_size;
		pass = 1;
		जाओ skip_init_ctx;
	पूर्ण

	स_रखो(&ctx, 0, माप(ctx));
	ctx.prog = prog;

	ctx.offset = kदो_स्मृति_array(prog->len, माप(अचिन्हित पूर्णांक), GFP_KERNEL);
	अगर (ctx.offset == शून्य) अणु
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	/* Longest sequence emitted is क्रम bswap32, 12 inकाष्ठाions.  Pre-cook
	 * the offset array so that we converge faster.
	 */
	क्रम (i = 0; i < prog->len; i++)
		ctx.offset[i] = i * (12 * 4);

	prev_image_size = ~0U;
	क्रम (pass = 1; pass < 40; pass++) अणु
		ctx.idx = 0;

		build_prologue(&ctx);
		अगर (build_body(&ctx)) अणु
			prog = orig_prog;
			जाओ out_off;
		पूर्ण
		build_epilogue(&ctx);

		अगर (bpf_jit_enable > 1)
			pr_info("Pass %d: size = %u, seen = [%c%c%c%c%c%c]\n", pass,
				ctx.idx * 4,
				ctx.पंचांगp_1_used ? '1' : ' ',
				ctx.पंचांगp_2_used ? '2' : ' ',
				ctx.पंचांगp_3_used ? '3' : ' ',
				ctx.saw_frame_poपूर्णांकer ? 'F' : ' ',
				ctx.saw_call ? 'C' : ' ',
				ctx.saw_tail_call ? 'T' : ' ');

		अगर (ctx.idx * 4 == prev_image_size)
			अवरोध;
		prev_image_size = ctx.idx * 4;
		cond_resched();
	पूर्ण

	/* Now we know the actual image size. */
	image_size = माप(u32) * ctx.idx;
	header = bpf_jit_binary_alloc(image_size, &image_ptr,
				      माप(u32), jit_fill_hole);
	अगर (header == शून्य) अणु
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	ctx.image = (u32 *)image_ptr;
skip_init_ctx:
	ctx.idx = 0;

	build_prologue(&ctx);

	अगर (build_body(&ctx)) अणु
		bpf_jit_binary_मुक्त(header);
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	build_epilogue(&ctx);

	अगर (ctx.idx * 4 != prev_image_size) अणु
		pr_err("bpf_jit: Failed to converge, prev_size=%u size=%d\n",
		       prev_image_size, ctx.idx * 4);
		bpf_jit_binary_मुक्त(header);
		prog = orig_prog;
		जाओ out_off;
	पूर्ण

	अगर (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, image_size, pass, ctx.image);

	bpf_flush_icache(header, (u8 *)header + (header->pages * PAGE_SIZE));

	अगर (!prog->is_func || extra_pass) अणु
		bpf_jit_binary_lock_ro(header);
	पूर्ण अन्यथा अणु
		jit_data->ctx = ctx;
		jit_data->image = image_ptr;
		jit_data->header = header;
	पूर्ण

	prog->bpf_func = (व्योम *)ctx.image;
	prog->jited = 1;
	prog->jited_len = image_size;

	अगर (!prog->is_func || extra_pass) अणु
		bpf_prog_fill_jited_linfo(prog, ctx.offset);
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
