<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * BPF Jit compiler क्रम s390.
 *
 * Minimum build requirements:
 *
 *  - HAVE_MARCH_Z196_FEATURES: laal, laalg
 *  - HAVE_MARCH_Z10_FEATURES: msfi, cgrj, clgrj
 *  - HAVE_MARCH_Z9_109_FEATURES: alfi, llilf, clfi, oilf, nilf
 *  - PACK_STACK
 *  - 64BIT
 *
 * Copyright IBM Corp. 2012,2015
 *
 * Author(s): Martin Schwidefsky <schwidefsky@de.ibm.com>
 *	      Michael Holzheu <holzheu@linux.vnet.ibm.com>
 */

#घोषणा KMSG_COMPONENT "bpf_jit"
#घोषणा pr_fmt(fmt) KMSG_COMPONENT ": " fmt

#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/init.h>
#समावेश <linux/bpf.h>
#समावेश <linux/mm.h>
#समावेश <linux/kernel.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/dis.h>
#समावेश <यंत्र/facility.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/set_memory.h>
#समावेश "bpf_jit.h"

काष्ठा bpf_jit अणु
	u32 seen;		/* Flags to remember seen eBPF inकाष्ठाions */
	u32 seen_reg[16];	/* Array to remember which रेजिस्टरs are used */
	u32 *addrs;		/* Array with relative inकाष्ठाion addresses */
	u8 *prg_buf;		/* Start of program */
	पूर्णांक size;		/* Size of program and literal pool */
	पूर्णांक size_prg;		/* Size of program */
	पूर्णांक prg;		/* Current position in program */
	पूर्णांक lit32_start;	/* Start of 32-bit literal pool */
	पूर्णांक lit32;		/* Current position in 32-bit literal pool */
	पूर्णांक lit64_start;	/* Start of 64-bit literal pool */
	पूर्णांक lit64;		/* Current position in 64-bit literal pool */
	पूर्णांक base_ip;		/* Base address क्रम literal pool */
	पूर्णांक निकास_ip;		/* Address of निकास */
	पूर्णांक r1_thunk_ip;	/* Address of expoline thunk क्रम 'br %r1' */
	पूर्णांक r14_thunk_ip;	/* Address of expoline thunk क्रम 'br %r14' */
	पूर्णांक tail_call_start;	/* Tail call start offset */
	पूर्णांक excnt;		/* Number of exception table entries */
पूर्ण;

#घोषणा SEEN_MEM	BIT(0)		/* use mem[] क्रम temporary storage */
#घोषणा SEEN_LITERAL	BIT(1)		/* code uses literals */
#घोषणा SEEN_FUNC	BIT(2)		/* calls C functions */
#घोषणा SEEN_TAIL_CALL	BIT(3)		/* code uses tail calls */
#घोषणा SEEN_STACK	(SEEN_FUNC | SEEN_MEM)

/*
 * s390 रेजिस्टरs
 */
#घोषणा REG_W0		(MAX_BPF_JIT_REG + 0)	/* Work रेजिस्टर 1 (even) */
#घोषणा REG_W1		(MAX_BPF_JIT_REG + 1)	/* Work रेजिस्टर 2 (odd) */
#घोषणा REG_L		(MAX_BPF_JIT_REG + 2)	/* Literal pool रेजिस्टर */
#घोषणा REG_15		(MAX_BPF_JIT_REG + 3)	/* Register 15 */
#घोषणा REG_0		REG_W0			/* Register 0 */
#घोषणा REG_1		REG_W1			/* Register 1 */
#घोषणा REG_2		BPF_REG_1		/* Register 2 */
#घोषणा REG_14		BPF_REG_0		/* Register 14 */

/*
 * Mapping of BPF रेजिस्टरs to s390 रेजिस्टरs
 */
अटल स्थिर पूर्णांक reg2hex[] = अणु
	/* Return code */
	[BPF_REG_0]	= 14,
	/* Function parameters */
	[BPF_REG_1]	= 2,
	[BPF_REG_2]	= 3,
	[BPF_REG_3]	= 4,
	[BPF_REG_4]	= 5,
	[BPF_REG_5]	= 6,
	/* Call saved रेजिस्टरs */
	[BPF_REG_6]	= 7,
	[BPF_REG_7]	= 8,
	[BPF_REG_8]	= 9,
	[BPF_REG_9]	= 10,
	/* BPF stack poपूर्णांकer */
	[BPF_REG_FP]	= 13,
	/* Register क्रम blinding */
	[BPF_REG_AX]	= 12,
	/* Work रेजिस्टरs क्रम s390x backend */
	[REG_W0]	= 0,
	[REG_W1]	= 1,
	[REG_L]		= 11,
	[REG_15]	= 15,
पूर्ण;

अटल अंतरभूत u32 reg(u32 dst_reg, u32 src_reg)
अणु
	वापस reg2hex[dst_reg] << 4 | reg2hex[src_reg];
पूर्ण

अटल अंतरभूत u32 reg_high(u32 reg)
अणु
	वापस reg2hex[reg] << 4;
पूर्ण

अटल अंतरभूत व्योम reg_set_seen(काष्ठा bpf_jit *jit, u32 b1)
अणु
	u32 r1 = reg2hex[b1];

	अगर (!jit->seen_reg[r1] && r1 >= 6 && r1 <= 15)
		jit->seen_reg[r1] = 1;
पूर्ण

#घोषणा REG_SET_SEEN(b1)					\
(अणु								\
	reg_set_seen(jit, b1);					\
पूर्ण)

#घोषणा REG_SEEN(b1) jit->seen_reg[reg2hex[(b1)]]

/*
 * EMIT macros क्रम code generation
 */

#घोषणा _EMIT2(op)						\
(अणु								\
	अगर (jit->prg_buf)					\
		*(u16 *) (jit->prg_buf + jit->prg) = (op);	\
	jit->prg += 2;						\
पूर्ण)

#घोषणा EMIT2(op, b1, b2)					\
(अणु								\
	_EMIT2((op) | reg(b1, b2));				\
	REG_SET_SEEN(b1);					\
	REG_SET_SEEN(b2);					\
पूर्ण)

#घोषणा _EMIT4(op)						\
(अणु								\
	अगर (jit->prg_buf)					\
		*(u32 *) (jit->prg_buf + jit->prg) = (op);	\
	jit->prg += 4;						\
पूर्ण)

#घोषणा EMIT4(op, b1, b2)					\
(अणु								\
	_EMIT4((op) | reg(b1, b2));				\
	REG_SET_SEEN(b1);					\
	REG_SET_SEEN(b2);					\
पूर्ण)

#घोषणा EMIT4_RRF(op, b1, b2, b3)				\
(अणु								\
	_EMIT4((op) | reg_high(b3) << 8 | reg(b1, b2));		\
	REG_SET_SEEN(b1);					\
	REG_SET_SEEN(b2);					\
	REG_SET_SEEN(b3);					\
पूर्ण)

#घोषणा _EMIT4_DISP(op, disp)					\
(अणु								\
	अचिन्हित पूर्णांक __disp = (disp) & 0xfff;			\
	_EMIT4((op) | __disp);					\
पूर्ण)

#घोषणा EMIT4_DISP(op, b1, b2, disp)				\
(अणु								\
	_EMIT4_DISP((op) | reg_high(b1) << 16 |			\
		    reg_high(b2) << 8, (disp));			\
	REG_SET_SEEN(b1);					\
	REG_SET_SEEN(b2);					\
पूर्ण)

#घोषणा EMIT4_IMM(op, b1, imm)					\
(अणु								\
	अचिन्हित पूर्णांक __imm = (imm) & 0xffff;			\
	_EMIT4((op) | reg_high(b1) << 16 | __imm);		\
	REG_SET_SEEN(b1);					\
पूर्ण)

#घोषणा EMIT4_PCREL(op, pcrel)					\
(अणु								\
	दीर्घ __pcrel = ((pcrel) >> 1) & 0xffff;			\
	_EMIT4((op) | __pcrel);					\
पूर्ण)

#घोषणा EMIT4_PCREL_RIC(op, mask, target)			\
(अणु								\
	पूर्णांक __rel = ((target) - jit->prg) / 2;			\
	_EMIT4((op) | (mask) << 20 | (__rel & 0xffff));		\
पूर्ण)

#घोषणा _EMIT6(op1, op2)					\
(अणु								\
	अगर (jit->prg_buf) अणु					\
		*(u32 *) (jit->prg_buf + jit->prg) = (op1);	\
		*(u16 *) (jit->prg_buf + jit->prg + 4) = (op2);	\
	पूर्ण							\
	jit->prg += 6;						\
पूर्ण)

#घोषणा _EMIT6_DISP(op1, op2, disp)				\
(अणु								\
	अचिन्हित पूर्णांक __disp = (disp) & 0xfff;			\
	_EMIT6((op1) | __disp, op2);				\
पूर्ण)

#घोषणा _EMIT6_DISP_LH(op1, op2, disp)				\
(अणु								\
	u32 _disp = (u32) (disp);				\
	अचिन्हित पूर्णांक __disp_h = _disp & 0xff000;		\
	अचिन्हित पूर्णांक __disp_l = _disp & 0x00fff;		\
	_EMIT6((op1) | __disp_l, (op2) | __disp_h >> 4);	\
पूर्ण)

#घोषणा EMIT6_DISP_LH(op1, op2, b1, b2, b3, disp)		\
(अणु								\
	_EMIT6_DISP_LH((op1) | reg(b1, b2) << 16 |		\
		       reg_high(b3) << 8, op2, disp);		\
	REG_SET_SEEN(b1);					\
	REG_SET_SEEN(b2);					\
	REG_SET_SEEN(b3);					\
पूर्ण)

#घोषणा EMIT6_PCREL_RIEB(op1, op2, b1, b2, mask, target)	\
(अणु								\
	अचिन्हित पूर्णांक rel = (पूर्णांक)((target) - jit->prg) / 2;	\
	_EMIT6((op1) | reg(b1, b2) << 16 | (rel & 0xffff),	\
	       (op2) | (mask) << 12);				\
	REG_SET_SEEN(b1);					\
	REG_SET_SEEN(b2);					\
पूर्ण)

#घोषणा EMIT6_PCREL_RIEC(op1, op2, b1, imm, mask, target)	\
(अणु								\
	अचिन्हित पूर्णांक rel = (पूर्णांक)((target) - jit->prg) / 2;	\
	_EMIT6((op1) | (reg_high(b1) | (mask)) << 16 |		\
		(rel & 0xffff), (op2) | ((imm) & 0xff) << 8);	\
	REG_SET_SEEN(b1);					\
	BUILD_BUG_ON(((अचिन्हित दीर्घ) (imm)) > 0xff);		\
पूर्ण)

#घोषणा EMIT6_PCREL(op1, op2, b1, b2, i, off, mask)		\
(अणु								\
	/* Branch inकाष्ठाion needs 6 bytes */			\
	पूर्णांक rel = (addrs[(i) + (off) + 1] - (addrs[(i) + 1] - 6)) / 2;\
	_EMIT6((op1) | reg(b1, b2) << 16 | (rel & 0xffff), (op2) | (mask));\
	REG_SET_SEEN(b1);					\
	REG_SET_SEEN(b2);					\
पूर्ण)

#घोषणा EMIT6_PCREL_RILB(op, b, target)				\
(अणु								\
	अचिन्हित पूर्णांक rel = (पूर्णांक)((target) - jit->prg) / 2;	\
	_EMIT6((op) | reg_high(b) << 16 | rel >> 16, rel & 0xffff);\
	REG_SET_SEEN(b);					\
पूर्ण)

#घोषणा EMIT6_PCREL_RIL(op, target)				\
(अणु								\
	अचिन्हित पूर्णांक rel = (पूर्णांक)((target) - jit->prg) / 2;	\
	_EMIT6((op) | rel >> 16, rel & 0xffff);			\
पूर्ण)

#घोषणा EMIT6_PCREL_RILC(op, mask, target)			\
(अणु								\
	EMIT6_PCREL_RIL((op) | (mask) << 20, (target));		\
पूर्ण)

#घोषणा _EMIT6_IMM(op, imm)					\
(अणु								\
	अचिन्हित पूर्णांक __imm = (imm);				\
	_EMIT6((op) | (__imm >> 16), __imm & 0xffff);		\
पूर्ण)

#घोषणा EMIT6_IMM(op, b1, imm)					\
(अणु								\
	_EMIT6_IMM((op) | reg_high(b1) << 16, imm);		\
	REG_SET_SEEN(b1);					\
पूर्ण)

#घोषणा _EMIT_CONST_U32(val)					\
(अणु								\
	अचिन्हित पूर्णांक ret;					\
	ret = jit->lit32;					\
	अगर (jit->prg_buf)					\
		*(u32 *)(jit->prg_buf + jit->lit32) = (u32)(val);\
	jit->lit32 += 4;					\
	ret;							\
पूर्ण)

#घोषणा EMIT_CONST_U32(val)					\
(अणु								\
	jit->seen |= SEEN_LITERAL;				\
	_EMIT_CONST_U32(val) - jit->base_ip;			\
पूर्ण)

#घोषणा _EMIT_CONST_U64(val)					\
(अणु								\
	अचिन्हित पूर्णांक ret;					\
	ret = jit->lit64;					\
	अगर (jit->prg_buf)					\
		*(u64 *)(jit->prg_buf + jit->lit64) = (u64)(val);\
	jit->lit64 += 8;					\
	ret;							\
पूर्ण)

#घोषणा EMIT_CONST_U64(val)					\
(अणु								\
	jit->seen |= SEEN_LITERAL;				\
	_EMIT_CONST_U64(val) - jit->base_ip;			\
पूर्ण)

#घोषणा EMIT_ZERO(b1)						\
(अणु								\
	अगर (!fp->aux->verअगरier_zext) अणु				\
		/* llgfr %dst,%dst (zero extend to 64 bit) */	\
		EMIT4(0xb9160000, b1, b1);			\
		REG_SET_SEEN(b1);				\
	पूर्ण							\
पूर्ण)

/*
 * Return whether this is the first pass. The first pass is special, since we
 * करोn't know any sizes yet, and thus must be conservative.
 */
अटल bool is_first_pass(काष्ठा bpf_jit *jit)
अणु
	वापस jit->size == 0;
पूर्ण

/*
 * Return whether this is the code generation pass. The code generation pass is
 * special, since we should change as little as possible.
 */
अटल bool is_codegen_pass(काष्ठा bpf_jit *jit)
अणु
	वापस jit->prg_buf;
पूर्ण

/*
 * Return whether "rel" can be encoded as a लघु PC-relative offset
 */
अटल bool is_valid_rel(पूर्णांक rel)
अणु
	वापस rel >= -65536 && rel <= 65534;
पूर्ण

/*
 * Return whether "off" can be reached using a लघु PC-relative offset
 */
अटल bool can_use_rel(काष्ठा bpf_jit *jit, पूर्णांक off)
अणु
	वापस is_valid_rel(off - jit->prg);
पूर्ण

/*
 * Return whether given displacement can be encoded using
 * Long-Displacement Facility
 */
अटल bool is_valid_ldisp(पूर्णांक disp)
अणु
	वापस disp >= -524288 && disp <= 524287;
पूर्ण

/*
 * Return whether the next 32-bit literal pool entry can be referenced using
 * Long-Displacement Facility
 */
अटल bool can_use_ldisp_क्रम_lit32(काष्ठा bpf_jit *jit)
अणु
	वापस is_valid_ldisp(jit->lit32 - jit->base_ip);
पूर्ण

/*
 * Return whether the next 64-bit literal pool entry can be referenced using
 * Long-Displacement Facility
 */
अटल bool can_use_ldisp_क्रम_lit64(काष्ठा bpf_jit *jit)
अणु
	वापस is_valid_ldisp(jit->lit64 - jit->base_ip);
पूर्ण

/*
 * Fill whole space with illegal inकाष्ठाions
 */
अटल व्योम jit_fill_hole(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	स_रखो(area, 0, size);
पूर्ण

/*
 * Save रेजिस्टरs from "rs" (रेजिस्टर start) to "re" (रेजिस्टर end) on stack
 */
अटल व्योम save_regs(काष्ठा bpf_jit *jit, u32 rs, u32 re)
अणु
	u32 off = STK_OFF_R6 + (rs - 6) * 8;

	अगर (rs == re)
		/* stg %rs,off(%r15) */
		_EMIT6(0xe300f000 | rs << 20 | off, 0x0024);
	अन्यथा
		/* sपंचांगg %rs,%re,off(%r15) */
		_EMIT6_DISP(0xeb00f000 | rs << 20 | re << 16, 0x0024, off);
पूर्ण

/*
 * Restore रेजिस्टरs from "rs" (रेजिस्टर start) to "re" (रेजिस्टर end) on stack
 */
अटल व्योम restore_regs(काष्ठा bpf_jit *jit, u32 rs, u32 re, u32 stack_depth)
अणु
	u32 off = STK_OFF_R6 + (rs - 6) * 8;

	अगर (jit->seen & SEEN_STACK)
		off += STK_OFF + stack_depth;

	अगर (rs == re)
		/* lg %rs,off(%r15) */
		_EMIT6(0xe300f000 | rs << 20 | off, 0x0004);
	अन्यथा
		/* lmg %rs,%re,off(%r15) */
		_EMIT6_DISP(0xeb00f000 | rs << 20 | re << 16, 0x0004, off);
पूर्ण

/*
 * Return first seen रेजिस्टर (from start)
 */
अटल पूर्णांक get_start(काष्ठा bpf_jit *jit, पूर्णांक start)
अणु
	पूर्णांक i;

	क्रम (i = start; i <= 15; i++) अणु
		अगर (jit->seen_reg[i])
			वापस i;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Return last seen रेजिस्टर (from start) (gap >= 2)
 */
अटल पूर्णांक get_end(काष्ठा bpf_jit *jit, पूर्णांक start)
अणु
	पूर्णांक i;

	क्रम (i = start; i < 15; i++) अणु
		अगर (!jit->seen_reg[i] && !jit->seen_reg[i + 1])
			वापस i - 1;
	पूर्ण
	वापस jit->seen_reg[15] ? 15 : 14;
पूर्ण

#घोषणा REGS_SAVE	1
#घोषणा REGS_RESTORE	0
/*
 * Save and restore clobbered रेजिस्टरs (6-15) on stack.
 * We save/restore रेजिस्टरs in chunks with gap >= 2 रेजिस्टरs.
 */
अटल व्योम save_restore_regs(काष्ठा bpf_jit *jit, पूर्णांक op, u32 stack_depth)
अणु
	स्थिर पूर्णांक last = 15, save_restore_size = 6;
	पूर्णांक re = 6, rs;

	अगर (is_first_pass(jit)) अणु
		/*
		 * We करोn't know yet which रेजिस्टरs are used. Reserve space
		 * conservatively.
		 */
		jit->prg += (last - re + 1) * save_restore_size;
		वापस;
	पूर्ण

	करो अणु
		rs = get_start(jit, re);
		अगर (!rs)
			अवरोध;
		re = get_end(jit, rs + 1);
		अगर (op == REGS_SAVE)
			save_regs(jit, rs, re);
		अन्यथा
			restore_regs(jit, rs, re, stack_depth);
		re++;
	पूर्ण जबतक (re <= last);
पूर्ण

अटल व्योम bpf_skip(काष्ठा bpf_jit *jit, पूर्णांक size)
अणु
	अगर (size >= 6 && !is_valid_rel(size)) अणु
		/* brcl 0xf,size */
		EMIT6_PCREL_RIL(0xc0f4000000, size);
		size -= 6;
	पूर्ण अन्यथा अगर (size >= 4 && is_valid_rel(size)) अणु
		/* brc 0xf,size */
		EMIT4_PCREL(0xa7f40000, size);
		size -= 4;
	पूर्ण
	जबतक (size >= 2) अणु
		/* bcr 0,%0 */
		_EMIT2(0x0700);
		size -= 2;
	पूर्ण
पूर्ण

/*
 * Emit function prologue
 *
 * Save रेजिस्टरs and create stack frame अगर necessary.
 * See stack frame layout desription in "bpf_jit.h"!
 */
अटल व्योम bpf_jit_prologue(काष्ठा bpf_jit *jit, u32 stack_depth)
अणु
	अगर (jit->seen & SEEN_TAIL_CALL) अणु
		/* xc STK_OFF_TCCNT(4,%r15),STK_OFF_TCCNT(%r15) */
		_EMIT6(0xd703f000 | STK_OFF_TCCNT, 0xf000 | STK_OFF_TCCNT);
	पूर्ण अन्यथा अणु
		/*
		 * There are no tail calls. Insert nops in order to have
		 * tail_call_start at a predictable offset.
		 */
		bpf_skip(jit, 6);
	पूर्ण
	/* Tail calls have to skip above initialization */
	jit->tail_call_start = jit->prg;
	/* Save रेजिस्टरs */
	save_restore_regs(jit, REGS_SAVE, stack_depth);
	/* Setup literal pool */
	अगर (is_first_pass(jit) || (jit->seen & SEEN_LITERAL)) अणु
		अगर (!is_first_pass(jit) &&
		    is_valid_ldisp(jit->size - (jit->prg + 2))) अणु
			/* basr %l,0 */
			EMIT2(0x0d00, REG_L, REG_0);
			jit->base_ip = jit->prg;
		पूर्ण अन्यथा अणु
			/* larl %l,lit32_start */
			EMIT6_PCREL_RILB(0xc0000000, REG_L, jit->lit32_start);
			jit->base_ip = jit->lit32_start;
		पूर्ण
	पूर्ण
	/* Setup stack and backchain */
	अगर (is_first_pass(jit) || (jit->seen & SEEN_STACK)) अणु
		अगर (is_first_pass(jit) || (jit->seen & SEEN_FUNC))
			/* lgr %w1,%r15 (backchain) */
			EMIT4(0xb9040000, REG_W1, REG_15);
		/* la %bfp,STK_160_UNUSED(%r15) (BPF frame poपूर्णांकer) */
		EMIT4_DISP(0x41000000, BPF_REG_FP, REG_15, STK_160_UNUSED);
		/* aghi %r15,-STK_OFF */
		EMIT4_IMM(0xa70b0000, REG_15, -(STK_OFF + stack_depth));
		अगर (is_first_pass(jit) || (jit->seen & SEEN_FUNC))
			/* stg %w1,152(%r15) (backchain) */
			EMIT6_DISP_LH(0xe3000000, 0x0024, REG_W1, REG_0,
				      REG_15, 152);
	पूर्ण
पूर्ण

/*
 * Function epilogue
 */
अटल व्योम bpf_jit_epilogue(काष्ठा bpf_jit *jit, u32 stack_depth)
अणु
	jit->निकास_ip = jit->prg;
	/* Load निकास code: lgr %r2,%b0 */
	EMIT4(0xb9040000, REG_2, BPF_REG_0);
	/* Restore रेजिस्टरs */
	save_restore_regs(jit, REGS_RESTORE, stack_depth);
	अगर (__is_defined(CC_USING_EXPOLINE) && !nospec_disable) अणु
		jit->r14_thunk_ip = jit->prg;
		/* Generate __s390_indirect_jump_r14 thunk */
		अगर (test_facility(35)) अणु
			/* exrl %r0,.+10 */
			EMIT6_PCREL_RIL(0xc6000000, jit->prg + 10);
		पूर्ण अन्यथा अणु
			/* larl %r1,.+14 */
			EMIT6_PCREL_RILB(0xc0000000, REG_1, jit->prg + 14);
			/* ex 0,0(%r1) */
			EMIT4_DISP(0x44000000, REG_0, REG_1, 0);
		पूर्ण
		/* j . */
		EMIT4_PCREL(0xa7f40000, 0);
	पूर्ण
	/* br %r14 */
	_EMIT2(0x07fe);

	अगर (__is_defined(CC_USING_EXPOLINE) && !nospec_disable &&
	    (is_first_pass(jit) || (jit->seen & SEEN_FUNC))) अणु
		jit->r1_thunk_ip = jit->prg;
		/* Generate __s390_indirect_jump_r1 thunk */
		अगर (test_facility(35)) अणु
			/* exrl %r0,.+10 */
			EMIT6_PCREL_RIL(0xc6000000, jit->prg + 10);
			/* j . */
			EMIT4_PCREL(0xa7f40000, 0);
			/* br %r1 */
			_EMIT2(0x07f1);
		पूर्ण अन्यथा अणु
			/* ex 0,S390_lowcore.br_r1_tampoline */
			EMIT4_DISP(0x44000000, REG_0, REG_0,
				   दुरत्व(काष्ठा lowcore, br_r1_trampoline));
			/* j . */
			EMIT4_PCREL(0xa7f40000, 0);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक get_probe_mem_regno(स्थिर u8 *insn)
अणु
	/*
	 * insn must poपूर्णांक to llgc, llgh, llgf or lg, which have destination
	 * रेजिस्टर at the same position.
	 */
	अगर (insn[0] != 0xe3) /* common llgc, llgh, llgf and lg prefix */
		वापस -1;
	अगर (insn[5] != 0x90 && /* llgc */
	    insn[5] != 0x91 && /* llgh */
	    insn[5] != 0x16 && /* llgf */
	    insn[5] != 0x04) /* lg */
		वापस -1;
	वापस insn[1] >> 4;
पूर्ण

अटल bool ex_handler_bpf(स्थिर काष्ठा exception_table_entry *x,
			   काष्ठा pt_regs *regs)
अणु
	पूर्णांक regno;
	u8 *insn;

	regs->psw.addr = extable_fixup(x);
	insn = (u8 *)__शुरुआत_psw(regs->psw, regs->पूर्णांक_code >> 16);
	regno = get_probe_mem_regno(insn);
	अगर (WARN_ON_ONCE(regno < 0))
		/* JIT bug - unexpected inकाष्ठाion. */
		वापस false;
	regs->gprs[regno] = 0;
	वापस true;
पूर्ण

अटल पूर्णांक bpf_jit_probe_mem(काष्ठा bpf_jit *jit, काष्ठा bpf_prog *fp,
			     पूर्णांक probe_prg, पूर्णांक nop_prg)
अणु
	काष्ठा exception_table_entry *ex;
	s64 delta;
	u8 *insn;
	पूर्णांक prg;
	पूर्णांक i;

	अगर (!fp->aux->extable)
		/* Do nothing during early JIT passes. */
		वापस 0;
	insn = jit->prg_buf + probe_prg;
	अगर (WARN_ON_ONCE(get_probe_mem_regno(insn) < 0))
		/* JIT bug - unexpected probe inकाष्ठाion. */
		वापस -1;
	अगर (WARN_ON_ONCE(probe_prg + insn_length(*insn) != nop_prg))
		/* JIT bug - gap between probe and nop inकाष्ठाions. */
		वापस -1;
	क्रम (i = 0; i < 2; i++) अणु
		अगर (WARN_ON_ONCE(jit->excnt >= fp->aux->num_exentries))
			/* Verअगरier bug - not enough entries. */
			वापस -1;
		ex = &fp->aux->extable[jit->excnt];
		/* Add extable entries क्रम probe and nop inकाष्ठाions. */
		prg = i == 0 ? probe_prg : nop_prg;
		delta = jit->prg_buf + prg - (u8 *)&ex->insn;
		अगर (WARN_ON_ONCE(delta < पूर्णांक_न्यून || delta > पूर्णांक_उच्च))
			/* JIT bug - code and extable must be बंद. */
			वापस -1;
		ex->insn = delta;
		/*
		 * Always land on the nop. Note that extable infraकाष्ठाure
		 * ignores fixup field, it is handled by ex_handler_bpf().
		 */
		delta = jit->prg_buf + nop_prg - (u8 *)&ex->fixup;
		अगर (WARN_ON_ONCE(delta < पूर्णांक_न्यून || delta > पूर्णांक_उच्च))
			/* JIT bug - landing pad and extable must be बंद. */
			वापस -1;
		ex->fixup = delta;
		ex->handler = (u8 *)ex_handler_bpf - (u8 *)&ex->handler;
		jit->excnt++;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Compile one eBPF inकाष्ठाion पूर्णांकo s390x code
 *
 * NOTE: Use noअंतरभूत because क्रम gcov (-fprofile-arcs) gcc allocates a lot of
 * stack space क्रम the large चयन statement.
 */
अटल noअंतरभूत पूर्णांक bpf_jit_insn(काष्ठा bpf_jit *jit, काष्ठा bpf_prog *fp,
				 पूर्णांक i, bool extra_pass, u32 stack_depth)
अणु
	काष्ठा bpf_insn *insn = &fp->insnsi[i];
	u32 dst_reg = insn->dst_reg;
	u32 src_reg = insn->src_reg;
	पूर्णांक last, insn_count = 1;
	u32 *addrs = jit->addrs;
	s32 imm = insn->imm;
	s16 off = insn->off;
	पूर्णांक probe_prg = -1;
	अचिन्हित पूर्णांक mask;
	पूर्णांक nop_prg;
	पूर्णांक err;

	अगर (BPF_CLASS(insn->code) == BPF_LDX &&
	    BPF_MODE(insn->code) == BPF_PROBE_MEM)
		probe_prg = jit->prg;

	चयन (insn->code) अणु
	/*
	 * BPF_MOV
	 */
	हाल BPF_ALU | BPF_MOV | BPF_X: /* dst = (u32) src */
		/* llgfr %dst,%src */
		EMIT4(0xb9160000, dst_reg, src_reg);
		अगर (insn_is_zext(&insn[1]))
			insn_count = 2;
		अवरोध;
	हाल BPF_ALU64 | BPF_MOV | BPF_X: /* dst = src */
		/* lgr %dst,%src */
		EMIT4(0xb9040000, dst_reg, src_reg);
		अवरोध;
	हाल BPF_ALU | BPF_MOV | BPF_K: /* dst = (u32) imm */
		/* llilf %dst,imm */
		EMIT6_IMM(0xc00f0000, dst_reg, imm);
		अगर (insn_is_zext(&insn[1]))
			insn_count = 2;
		अवरोध;
	हाल BPF_ALU64 | BPF_MOV | BPF_K: /* dst = imm */
		/* lgfi %dst,imm */
		EMIT6_IMM(0xc0010000, dst_reg, imm);
		अवरोध;
	/*
	 * BPF_LD 64
	 */
	हाल BPF_LD | BPF_IMM | BPF_DW: /* dst = (u64) imm */
	अणु
		/* 16 byte inकाष्ठाion that uses two 'struct bpf_insn' */
		u64 imm64;

		imm64 = (u64)(u32) insn[0].imm | ((u64)(u32) insn[1].imm) << 32;
		/* lgrl %dst,imm */
		EMIT6_PCREL_RILB(0xc4080000, dst_reg, _EMIT_CONST_U64(imm64));
		insn_count = 2;
		अवरोध;
	पूर्ण
	/*
	 * BPF_ADD
	 */
	हाल BPF_ALU | BPF_ADD | BPF_X: /* dst = (u32) dst + (u32) src */
		/* ar %dst,%src */
		EMIT2(0x1a00, dst_reg, src_reg);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_ADD | BPF_X: /* dst = dst + src */
		/* agr %dst,%src */
		EMIT4(0xb9080000, dst_reg, src_reg);
		अवरोध;
	हाल BPF_ALU | BPF_ADD | BPF_K: /* dst = (u32) dst + (u32) imm */
		अगर (!imm)
			अवरोध;
		/* alfi %dst,imm */
		EMIT6_IMM(0xc20b0000, dst_reg, imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_ADD | BPF_K: /* dst = dst + imm */
		अगर (!imm)
			अवरोध;
		/* agfi %dst,imm */
		EMIT6_IMM(0xc2080000, dst_reg, imm);
		अवरोध;
	/*
	 * BPF_SUB
	 */
	हाल BPF_ALU | BPF_SUB | BPF_X: /* dst = (u32) dst - (u32) src */
		/* sr %dst,%src */
		EMIT2(0x1b00, dst_reg, src_reg);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_SUB | BPF_X: /* dst = dst - src */
		/* sgr %dst,%src */
		EMIT4(0xb9090000, dst_reg, src_reg);
		अवरोध;
	हाल BPF_ALU | BPF_SUB | BPF_K: /* dst = (u32) dst - (u32) imm */
		अगर (!imm)
			अवरोध;
		/* alfi %dst,-imm */
		EMIT6_IMM(0xc20b0000, dst_reg, -imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_SUB | BPF_K: /* dst = dst - imm */
		अगर (!imm)
			अवरोध;
		/* agfi %dst,-imm */
		EMIT6_IMM(0xc2080000, dst_reg, -imm);
		अवरोध;
	/*
	 * BPF_MUL
	 */
	हाल BPF_ALU | BPF_MUL | BPF_X: /* dst = (u32) dst * (u32) src */
		/* msr %dst,%src */
		EMIT4(0xb2520000, dst_reg, src_reg);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_MUL | BPF_X: /* dst = dst * src */
		/* msgr %dst,%src */
		EMIT4(0xb90c0000, dst_reg, src_reg);
		अवरोध;
	हाल BPF_ALU | BPF_MUL | BPF_K: /* dst = (u32) dst * (u32) imm */
		अगर (imm == 1)
			अवरोध;
		/* msfi %r5,imm */
		EMIT6_IMM(0xc2010000, dst_reg, imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_MUL | BPF_K: /* dst = dst * imm */
		अगर (imm == 1)
			अवरोध;
		/* msgfi %dst,imm */
		EMIT6_IMM(0xc2000000, dst_reg, imm);
		अवरोध;
	/*
	 * BPF_DIV / BPF_MOD
	 */
	हाल BPF_ALU | BPF_DIV | BPF_X: /* dst = (u32) dst / (u32) src */
	हाल BPF_ALU | BPF_MOD | BPF_X: /* dst = (u32) dst % (u32) src */
	अणु
		पूर्णांक rc_reg = BPF_OP(insn->code) == BPF_DIV ? REG_W1 : REG_W0;

		/* lhi %w0,0 */
		EMIT4_IMM(0xa7080000, REG_W0, 0);
		/* lr %w1,%dst */
		EMIT2(0x1800, REG_W1, dst_reg);
		/* dlr %w0,%src */
		EMIT4(0xb9970000, REG_W0, src_reg);
		/* llgfr %dst,%rc */
		EMIT4(0xb9160000, dst_reg, rc_reg);
		अगर (insn_is_zext(&insn[1]))
			insn_count = 2;
		अवरोध;
	पूर्ण
	हाल BPF_ALU64 | BPF_DIV | BPF_X: /* dst = dst / src */
	हाल BPF_ALU64 | BPF_MOD | BPF_X: /* dst = dst % src */
	अणु
		पूर्णांक rc_reg = BPF_OP(insn->code) == BPF_DIV ? REG_W1 : REG_W0;

		/* lghi %w0,0 */
		EMIT4_IMM(0xa7090000, REG_W0, 0);
		/* lgr %w1,%dst */
		EMIT4(0xb9040000, REG_W1, dst_reg);
		/* dlgr %w0,%dst */
		EMIT4(0xb9870000, REG_W0, src_reg);
		/* lgr %dst,%rc */
		EMIT4(0xb9040000, dst_reg, rc_reg);
		अवरोध;
	पूर्ण
	हाल BPF_ALU | BPF_DIV | BPF_K: /* dst = (u32) dst / (u32) imm */
	हाल BPF_ALU | BPF_MOD | BPF_K: /* dst = (u32) dst % (u32) imm */
	अणु
		पूर्णांक rc_reg = BPF_OP(insn->code) == BPF_DIV ? REG_W1 : REG_W0;

		अगर (imm == 1) अणु
			अगर (BPF_OP(insn->code) == BPF_MOD)
				/* lhgi %dst,0 */
				EMIT4_IMM(0xa7090000, dst_reg, 0);
			अवरोध;
		पूर्ण
		/* lhi %w0,0 */
		EMIT4_IMM(0xa7080000, REG_W0, 0);
		/* lr %w1,%dst */
		EMIT2(0x1800, REG_W1, dst_reg);
		अगर (!is_first_pass(jit) && can_use_ldisp_क्रम_lit32(jit)) अणु
			/* dl %w0,<d(imm)>(%l) */
			EMIT6_DISP_LH(0xe3000000, 0x0097, REG_W0, REG_0, REG_L,
				      EMIT_CONST_U32(imm));
		पूर्ण अन्यथा अणु
			/* lgfrl %dst,imm */
			EMIT6_PCREL_RILB(0xc40c0000, dst_reg,
					 _EMIT_CONST_U32(imm));
			jit->seen |= SEEN_LITERAL;
			/* dlr %w0,%dst */
			EMIT4(0xb9970000, REG_W0, dst_reg);
		पूर्ण
		/* llgfr %dst,%rc */
		EMIT4(0xb9160000, dst_reg, rc_reg);
		अगर (insn_is_zext(&insn[1]))
			insn_count = 2;
		अवरोध;
	पूर्ण
	हाल BPF_ALU64 | BPF_DIV | BPF_K: /* dst = dst / imm */
	हाल BPF_ALU64 | BPF_MOD | BPF_K: /* dst = dst % imm */
	अणु
		पूर्णांक rc_reg = BPF_OP(insn->code) == BPF_DIV ? REG_W1 : REG_W0;

		अगर (imm == 1) अणु
			अगर (BPF_OP(insn->code) == BPF_MOD)
				/* lhgi %dst,0 */
				EMIT4_IMM(0xa7090000, dst_reg, 0);
			अवरोध;
		पूर्ण
		/* lghi %w0,0 */
		EMIT4_IMM(0xa7090000, REG_W0, 0);
		/* lgr %w1,%dst */
		EMIT4(0xb9040000, REG_W1, dst_reg);
		अगर (!is_first_pass(jit) && can_use_ldisp_क्रम_lit64(jit)) अणु
			/* dlg %w0,<d(imm)>(%l) */
			EMIT6_DISP_LH(0xe3000000, 0x0087, REG_W0, REG_0, REG_L,
				      EMIT_CONST_U64(imm));
		पूर्ण अन्यथा अणु
			/* lgrl %dst,imm */
			EMIT6_PCREL_RILB(0xc4080000, dst_reg,
					 _EMIT_CONST_U64(imm));
			jit->seen |= SEEN_LITERAL;
			/* dlgr %w0,%dst */
			EMIT4(0xb9870000, REG_W0, dst_reg);
		पूर्ण
		/* lgr %dst,%rc */
		EMIT4(0xb9040000, dst_reg, rc_reg);
		अवरोध;
	पूर्ण
	/*
	 * BPF_AND
	 */
	हाल BPF_ALU | BPF_AND | BPF_X: /* dst = (u32) dst & (u32) src */
		/* nr %dst,%src */
		EMIT2(0x1400, dst_reg, src_reg);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_AND | BPF_X: /* dst = dst & src */
		/* ngr %dst,%src */
		EMIT4(0xb9800000, dst_reg, src_reg);
		अवरोध;
	हाल BPF_ALU | BPF_AND | BPF_K: /* dst = (u32) dst & (u32) imm */
		/* nilf %dst,imm */
		EMIT6_IMM(0xc00b0000, dst_reg, imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_AND | BPF_K: /* dst = dst & imm */
		अगर (!is_first_pass(jit) && can_use_ldisp_क्रम_lit64(jit)) अणु
			/* ng %dst,<d(imm)>(%l) */
			EMIT6_DISP_LH(0xe3000000, 0x0080,
				      dst_reg, REG_0, REG_L,
				      EMIT_CONST_U64(imm));
		पूर्ण अन्यथा अणु
			/* lgrl %w0,imm */
			EMIT6_PCREL_RILB(0xc4080000, REG_W0,
					 _EMIT_CONST_U64(imm));
			jit->seen |= SEEN_LITERAL;
			/* ngr %dst,%w0 */
			EMIT4(0xb9800000, dst_reg, REG_W0);
		पूर्ण
		अवरोध;
	/*
	 * BPF_OR
	 */
	हाल BPF_ALU | BPF_OR | BPF_X: /* dst = (u32) dst | (u32) src */
		/* or %dst,%src */
		EMIT2(0x1600, dst_reg, src_reg);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_OR | BPF_X: /* dst = dst | src */
		/* ogr %dst,%src */
		EMIT4(0xb9810000, dst_reg, src_reg);
		अवरोध;
	हाल BPF_ALU | BPF_OR | BPF_K: /* dst = (u32) dst | (u32) imm */
		/* oilf %dst,imm */
		EMIT6_IMM(0xc00d0000, dst_reg, imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_OR | BPF_K: /* dst = dst | imm */
		अगर (!is_first_pass(jit) && can_use_ldisp_क्रम_lit64(jit)) अणु
			/* og %dst,<d(imm)>(%l) */
			EMIT6_DISP_LH(0xe3000000, 0x0081,
				      dst_reg, REG_0, REG_L,
				      EMIT_CONST_U64(imm));
		पूर्ण अन्यथा अणु
			/* lgrl %w0,imm */
			EMIT6_PCREL_RILB(0xc4080000, REG_W0,
					 _EMIT_CONST_U64(imm));
			jit->seen |= SEEN_LITERAL;
			/* ogr %dst,%w0 */
			EMIT4(0xb9810000, dst_reg, REG_W0);
		पूर्ण
		अवरोध;
	/*
	 * BPF_XOR
	 */
	हाल BPF_ALU | BPF_XOR | BPF_X: /* dst = (u32) dst ^ (u32) src */
		/* xr %dst,%src */
		EMIT2(0x1700, dst_reg, src_reg);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_XOR | BPF_X: /* dst = dst ^ src */
		/* xgr %dst,%src */
		EMIT4(0xb9820000, dst_reg, src_reg);
		अवरोध;
	हाल BPF_ALU | BPF_XOR | BPF_K: /* dst = (u32) dst ^ (u32) imm */
		अगर (!imm)
			अवरोध;
		/* xilf %dst,imm */
		EMIT6_IMM(0xc0070000, dst_reg, imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_XOR | BPF_K: /* dst = dst ^ imm */
		अगर (!is_first_pass(jit) && can_use_ldisp_क्रम_lit64(jit)) अणु
			/* xg %dst,<d(imm)>(%l) */
			EMIT6_DISP_LH(0xe3000000, 0x0082,
				      dst_reg, REG_0, REG_L,
				      EMIT_CONST_U64(imm));
		पूर्ण अन्यथा अणु
			/* lgrl %w0,imm */
			EMIT6_PCREL_RILB(0xc4080000, REG_W0,
					 _EMIT_CONST_U64(imm));
			jit->seen |= SEEN_LITERAL;
			/* xgr %dst,%w0 */
			EMIT4(0xb9820000, dst_reg, REG_W0);
		पूर्ण
		अवरोध;
	/*
	 * BPF_LSH
	 */
	हाल BPF_ALU | BPF_LSH | BPF_X: /* dst = (u32) dst << (u32) src */
		/* sll %dst,0(%src) */
		EMIT4_DISP(0x89000000, dst_reg, src_reg, 0);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_LSH | BPF_X: /* dst = dst << src */
		/* sllg %dst,%dst,0(%src) */
		EMIT6_DISP_LH(0xeb000000, 0x000d, dst_reg, dst_reg, src_reg, 0);
		अवरोध;
	हाल BPF_ALU | BPF_LSH | BPF_K: /* dst = (u32) dst << (u32) imm */
		अगर (imm == 0)
			अवरोध;
		/* sll %dst,imm(%r0) */
		EMIT4_DISP(0x89000000, dst_reg, REG_0, imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_LSH | BPF_K: /* dst = dst << imm */
		अगर (imm == 0)
			अवरोध;
		/* sllg %dst,%dst,imm(%r0) */
		EMIT6_DISP_LH(0xeb000000, 0x000d, dst_reg, dst_reg, REG_0, imm);
		अवरोध;
	/*
	 * BPF_RSH
	 */
	हाल BPF_ALU | BPF_RSH | BPF_X: /* dst = (u32) dst >> (u32) src */
		/* srl %dst,0(%src) */
		EMIT4_DISP(0x88000000, dst_reg, src_reg, 0);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_RSH | BPF_X: /* dst = dst >> src */
		/* srlg %dst,%dst,0(%src) */
		EMIT6_DISP_LH(0xeb000000, 0x000c, dst_reg, dst_reg, src_reg, 0);
		अवरोध;
	हाल BPF_ALU | BPF_RSH | BPF_K: /* dst = (u32) dst >> (u32) imm */
		अगर (imm == 0)
			अवरोध;
		/* srl %dst,imm(%r0) */
		EMIT4_DISP(0x88000000, dst_reg, REG_0, imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_RSH | BPF_K: /* dst = dst >> imm */
		अगर (imm == 0)
			अवरोध;
		/* srlg %dst,%dst,imm(%r0) */
		EMIT6_DISP_LH(0xeb000000, 0x000c, dst_reg, dst_reg, REG_0, imm);
		अवरोध;
	/*
	 * BPF_ARSH
	 */
	हाल BPF_ALU | BPF_ARSH | BPF_X: /* ((s32) dst) >>= src */
		/* sra %dst,%dst,0(%src) */
		EMIT4_DISP(0x8a000000, dst_reg, src_reg, 0);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_ARSH | BPF_X: /* ((s64) dst) >>= src */
		/* srag %dst,%dst,0(%src) */
		EMIT6_DISP_LH(0xeb000000, 0x000a, dst_reg, dst_reg, src_reg, 0);
		अवरोध;
	हाल BPF_ALU | BPF_ARSH | BPF_K: /* ((s32) dst >> imm */
		अगर (imm == 0)
			अवरोध;
		/* sra %dst,imm(%r0) */
		EMIT4_DISP(0x8a000000, dst_reg, REG_0, imm);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_ARSH | BPF_K: /* ((s64) dst) >>= imm */
		अगर (imm == 0)
			अवरोध;
		/* srag %dst,%dst,imm(%r0) */
		EMIT6_DISP_LH(0xeb000000, 0x000a, dst_reg, dst_reg, REG_0, imm);
		अवरोध;
	/*
	 * BPF_NEG
	 */
	हाल BPF_ALU | BPF_NEG: /* dst = (u32) -dst */
		/* lcr %dst,%dst */
		EMIT2(0x1300, dst_reg, dst_reg);
		EMIT_ZERO(dst_reg);
		अवरोध;
	हाल BPF_ALU64 | BPF_NEG: /* dst = -dst */
		/* lcgr %dst,%dst */
		EMIT4(0xb9030000, dst_reg, dst_reg);
		अवरोध;
	/*
	 * BPF_FROM_BE/LE
	 */
	हाल BPF_ALU | BPF_END | BPF_FROM_BE:
		/* s390 is big endian, thereक्रमe only clear high order bytes */
		चयन (imm) अणु
		हाल 16: /* dst = (u16) cpu_to_be16(dst) */
			/* llghr %dst,%dst */
			EMIT4(0xb9850000, dst_reg, dst_reg);
			अगर (insn_is_zext(&insn[1]))
				insn_count = 2;
			अवरोध;
		हाल 32: /* dst = (u32) cpu_to_be32(dst) */
			अगर (!fp->aux->verअगरier_zext)
				/* llgfr %dst,%dst */
				EMIT4(0xb9160000, dst_reg, dst_reg);
			अवरोध;
		हाल 64: /* dst = (u64) cpu_to_be64(dst) */
			अवरोध;
		पूर्ण
		अवरोध;
	हाल BPF_ALU | BPF_END | BPF_FROM_LE:
		चयन (imm) अणु
		हाल 16: /* dst = (u16) cpu_to_le16(dst) */
			/* lrvr %dst,%dst */
			EMIT4(0xb91f0000, dst_reg, dst_reg);
			/* srl %dst,16(%r0) */
			EMIT4_DISP(0x88000000, dst_reg, REG_0, 16);
			/* llghr %dst,%dst */
			EMIT4(0xb9850000, dst_reg, dst_reg);
			अगर (insn_is_zext(&insn[1]))
				insn_count = 2;
			अवरोध;
		हाल 32: /* dst = (u32) cpu_to_le32(dst) */
			/* lrvr %dst,%dst */
			EMIT4(0xb91f0000, dst_reg, dst_reg);
			अगर (!fp->aux->verअगरier_zext)
				/* llgfr %dst,%dst */
				EMIT4(0xb9160000, dst_reg, dst_reg);
			अवरोध;
		हाल 64: /* dst = (u64) cpu_to_le64(dst) */
			/* lrvgr %dst,%dst */
			EMIT4(0xb90f0000, dst_reg, dst_reg);
			अवरोध;
		पूर्ण
		अवरोध;
	/*
	 * BPF_ST(X)
	 */
	हाल BPF_STX | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = src_reg */
		/* stcy %src,off(%dst) */
		EMIT6_DISP_LH(0xe3000000, 0x0072, src_reg, dst_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अवरोध;
	हाल BPF_STX | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = src */
		/* sthy %src,off(%dst) */
		EMIT6_DISP_LH(0xe3000000, 0x0070, src_reg, dst_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अवरोध;
	हाल BPF_STX | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = src */
		/* sty %src,off(%dst) */
		EMIT6_DISP_LH(0xe3000000, 0x0050, src_reg, dst_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अवरोध;
	हाल BPF_STX | BPF_MEM | BPF_DW: /* (u64 *)(dst + off) = src */
		/* stg %src,off(%dst) */
		EMIT6_DISP_LH(0xe3000000, 0x0024, src_reg, dst_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अवरोध;
	हाल BPF_ST | BPF_MEM | BPF_B: /* *(u8 *)(dst + off) = imm */
		/* lhi %w0,imm */
		EMIT4_IMM(0xa7080000, REG_W0, (u8) imm);
		/* stcy %w0,off(dst) */
		EMIT6_DISP_LH(0xe3000000, 0x0072, REG_W0, dst_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अवरोध;
	हाल BPF_ST | BPF_MEM | BPF_H: /* (u16 *)(dst + off) = imm */
		/* lhi %w0,imm */
		EMIT4_IMM(0xa7080000, REG_W0, (u16) imm);
		/* sthy %w0,off(dst) */
		EMIT6_DISP_LH(0xe3000000, 0x0070, REG_W0, dst_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अवरोध;
	हाल BPF_ST | BPF_MEM | BPF_W: /* *(u32 *)(dst + off) = imm */
		/* llilf %w0,imm  */
		EMIT6_IMM(0xc00f0000, REG_W0, (u32) imm);
		/* sty %w0,off(%dst) */
		EMIT6_DISP_LH(0xe3000000, 0x0050, REG_W0, dst_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अवरोध;
	हाल BPF_ST | BPF_MEM | BPF_DW: /* *(u64 *)(dst + off) = imm */
		/* lgfi %w0,imm */
		EMIT6_IMM(0xc0010000, REG_W0, imm);
		/* stg %w0,off(%dst) */
		EMIT6_DISP_LH(0xe3000000, 0x0024, REG_W0, dst_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अवरोध;
	/*
	 * BPF_ATOMIC
	 */
	हाल BPF_STX | BPF_ATOMIC | BPF_DW:
	हाल BPF_STX | BPF_ATOMIC | BPF_W:
	अणु
		bool is32 = BPF_SIZE(insn->code) == BPF_W;

		चयन (insn->imm) अणु
/* अणुop32|op64पूर्ण अणु%w0|%srcपूर्ण,%src,off(%dst) */
#घोषणा EMIT_ATOMIC(op32, op64) करो अणु					\
	EMIT6_DISP_LH(0xeb000000, is32 ? (op32) : (op64),		\
		      (insn->imm & BPF_FETCH) ? src_reg : REG_W0,	\
		      src_reg, dst_reg, off);				\
	अगर (is32 && (insn->imm & BPF_FETCH))				\
		EMIT_ZERO(src_reg);					\
पूर्ण जबतक (0)
		हाल BPF_ADD:
		हाल BPF_ADD | BPF_FETCH:
			/* अणुlaal|laalgपूर्ण */
			EMIT_ATOMIC(0x00fa, 0x00ea);
			अवरोध;
		हाल BPF_AND:
		हाल BPF_AND | BPF_FETCH:
			/* अणुlan|langपूर्ण */
			EMIT_ATOMIC(0x00f4, 0x00e4);
			अवरोध;
		हाल BPF_OR:
		हाल BPF_OR | BPF_FETCH:
			/* अणुlao|laogपूर्ण */
			EMIT_ATOMIC(0x00f6, 0x00e6);
			अवरोध;
		हाल BPF_XOR:
		हाल BPF_XOR | BPF_FETCH:
			/* अणुlax|laxgपूर्ण */
			EMIT_ATOMIC(0x00f7, 0x00e7);
			अवरोध;
#अघोषित EMIT_ATOMIC
		हाल BPF_XCHG:
			/* अणुly|lgपूर्ण %w0,off(%dst) */
			EMIT6_DISP_LH(0xe3000000,
				      is32 ? 0x0058 : 0x0004, REG_W0, REG_0,
				      dst_reg, off);
			/* 0: अणुcsy|csgपूर्ण %w0,%src,off(%dst) */
			EMIT6_DISP_LH(0xeb000000, is32 ? 0x0014 : 0x0030,
				      REG_W0, src_reg, dst_reg, off);
			/* brc 4,0b */
			EMIT4_PCREL_RIC(0xa7040000, 4, jit->prg - 6);
			/* अणुllgfr|lgrपूर्ण %src,%w0 */
			EMIT4(is32 ? 0xb9160000 : 0xb9040000, src_reg, REG_W0);
			अगर (is32 && insn_is_zext(&insn[1]))
				insn_count = 2;
			अवरोध;
		हाल BPF_CMPXCHG:
			/* 0: अणुcsy|csgपूर्ण %b0,%src,off(%dst) */
			EMIT6_DISP_LH(0xeb000000, is32 ? 0x0014 : 0x0030,
				      BPF_REG_0, src_reg, dst_reg, off);
			अवरोध;
		शेष:
			pr_err("Unknown atomic operation %02x\n", insn->imm);
			वापस -1;
		पूर्ण

		jit->seen |= SEEN_MEM;
		अवरोध;
	पूर्ण
	/*
	 * BPF_LDX
	 */
	हाल BPF_LDX | BPF_MEM | BPF_B: /* dst = *(u8 *)(ul) (src + off) */
	हाल BPF_LDX | BPF_PROBE_MEM | BPF_B:
		/* llgc %dst,0(off,%src) */
		EMIT6_DISP_LH(0xe3000000, 0x0090, dst_reg, src_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अगर (insn_is_zext(&insn[1]))
			insn_count = 2;
		अवरोध;
	हाल BPF_LDX | BPF_MEM | BPF_H: /* dst = *(u16 *)(ul) (src + off) */
	हाल BPF_LDX | BPF_PROBE_MEM | BPF_H:
		/* llgh %dst,0(off,%src) */
		EMIT6_DISP_LH(0xe3000000, 0x0091, dst_reg, src_reg, REG_0, off);
		jit->seen |= SEEN_MEM;
		अगर (insn_is_zext(&insn[1]))
			insn_count = 2;
		अवरोध;
	हाल BPF_LDX | BPF_MEM | BPF_W: /* dst = *(u32 *)(ul) (src + off) */
	हाल BPF_LDX | BPF_PROBE_MEM | BPF_W:
		/* llgf %dst,off(%src) */
		jit->seen |= SEEN_MEM;
		EMIT6_DISP_LH(0xe3000000, 0x0016, dst_reg, src_reg, REG_0, off);
		अगर (insn_is_zext(&insn[1]))
			insn_count = 2;
		अवरोध;
	हाल BPF_LDX | BPF_MEM | BPF_DW: /* dst = *(u64 *)(ul) (src + off) */
	हाल BPF_LDX | BPF_PROBE_MEM | BPF_DW:
		/* lg %dst,0(off,%src) */
		jit->seen |= SEEN_MEM;
		EMIT6_DISP_LH(0xe3000000, 0x0004, dst_reg, src_reg, REG_0, off);
		अवरोध;
	/*
	 * BPF_JMP / CALL
	 */
	हाल BPF_JMP | BPF_CALL:
	अणु
		u64 func;
		bool func_addr_fixed;
		पूर्णांक ret;

		ret = bpf_jit_get_func_addr(fp, insn, extra_pass,
					    &func, &func_addr_fixed);
		अगर (ret < 0)
			वापस -1;

		REG_SET_SEEN(BPF_REG_5);
		jit->seen |= SEEN_FUNC;
		/* lgrl %w1,func */
		EMIT6_PCREL_RILB(0xc4080000, REG_W1, _EMIT_CONST_U64(func));
		अगर (__is_defined(CC_USING_EXPOLINE) && !nospec_disable) अणु
			/* brasl %r14,__s390_indirect_jump_r1 */
			EMIT6_PCREL_RILB(0xc0050000, REG_14, jit->r1_thunk_ip);
		पूर्ण अन्यथा अणु
			/* basr %r14,%w1 */
			EMIT2(0x0d00, REG_14, REG_W1);
		पूर्ण
		/* lgr %b0,%r2: load वापस value पूर्णांकo %b0 */
		EMIT4(0xb9040000, BPF_REG_0, REG_2);
		अवरोध;
	पूर्ण
	हाल BPF_JMP | BPF_TAIL_CALL: अणु
		पूर्णांक patch_1_clrj, patch_2_clij, patch_3_brc;

		/*
		 * Implicit input:
		 *  B1: poपूर्णांकer to ctx
		 *  B2: poपूर्णांकer to bpf_array
		 *  B3: index in bpf_array
		 */
		jit->seen |= SEEN_TAIL_CALL;

		/*
		 * अगर (index >= array->map.max_entries)
		 *         जाओ out;
		 */

		/* llgf %w1,map.max_entries(%b2) */
		EMIT6_DISP_LH(0xe3000000, 0x0016, REG_W1, REG_0, BPF_REG_2,
			      दुरत्व(काष्ठा bpf_array, map.max_entries));
		/* अगर ((u32)%b3 >= (u32)%w1) जाओ out; */
		/* clrj %b3,%w1,0xa,out */
		patch_1_clrj = jit->prg;
		EMIT6_PCREL_RIEB(0xec000000, 0x0077, BPF_REG_3, REG_W1, 0xa,
				 jit->prg);

		/*
		 * अगर (tail_call_cnt++ > MAX_TAIL_CALL_CNT)
		 *         जाओ out;
		 */

		अगर (jit->seen & SEEN_STACK)
			off = STK_OFF_TCCNT + STK_OFF + stack_depth;
		अन्यथा
			off = STK_OFF_TCCNT;
		/* lhi %w0,1 */
		EMIT4_IMM(0xa7080000, REG_W0, 1);
		/* laal %w1,%w0,off(%r15) */
		EMIT6_DISP_LH(0xeb000000, 0x00fa, REG_W1, REG_W0, REG_15, off);
		/* clij %w1,MAX_TAIL_CALL_CNT,0x2,out */
		patch_2_clij = jit->prg;
		EMIT6_PCREL_RIEC(0xec000000, 0x007f, REG_W1, MAX_TAIL_CALL_CNT,
				 2, jit->prg);

		/*
		 * prog = array->ptrs[index];
		 * अगर (prog == शून्य)
		 *         जाओ out;
		 */

		/* llgfr %r1,%b3: %r1 = (u32) index */
		EMIT4(0xb9160000, REG_1, BPF_REG_3);
		/* sllg %r1,%r1,3: %r1 *= 8 */
		EMIT6_DISP_LH(0xeb000000, 0x000d, REG_1, REG_1, REG_0, 3);
		/* ltg %r1,prog(%b2,%r1) */
		EMIT6_DISP_LH(0xe3000000, 0x0002, REG_1, BPF_REG_2,
			      REG_1, दुरत्व(काष्ठा bpf_array, ptrs));
		/* brc 0x8,out */
		patch_3_brc = jit->prg;
		EMIT4_PCREL_RIC(0xa7040000, 8, jit->prg);

		/*
		 * Restore रेजिस्टरs beक्रमe calling function
		 */
		save_restore_regs(jit, REGS_RESTORE, stack_depth);

		/*
		 * जाओ *(prog->bpf_func + tail_call_start);
		 */

		/* lg %r1,bpf_func(%r1) */
		EMIT6_DISP_LH(0xe3000000, 0x0004, REG_1, REG_1, REG_0,
			      दुरत्व(काष्ठा bpf_prog, bpf_func));
		/* bc 0xf,tail_call_start(%r1) */
		_EMIT4(0x47f01000 + jit->tail_call_start);
		/* out: */
		अगर (jit->prg_buf) अणु
			*(u16 *)(jit->prg_buf + patch_1_clrj + 2) =
				(jit->prg - patch_1_clrj) >> 1;
			*(u16 *)(jit->prg_buf + patch_2_clij + 2) =
				(jit->prg - patch_2_clij) >> 1;
			*(u16 *)(jit->prg_buf + patch_3_brc + 2) =
				(jit->prg - patch_3_brc) >> 1;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BPF_JMP | BPF_EXIT: /* वापस b0 */
		last = (i == fp->len - 1) ? 1 : 0;
		अगर (last)
			अवरोध;
		अगर (!is_first_pass(jit) && can_use_rel(jit, jit->निकास_ip))
			/* brc 0xf, <निकास> */
			EMIT4_PCREL_RIC(0xa7040000, 0xf, jit->निकास_ip);
		अन्यथा
			/* brcl 0xf, <निकास> */
			EMIT6_PCREL_RILC(0xc0040000, 0xf, jit->निकास_ip);
		अवरोध;
	/*
	 * Branch relative (number of skipped inकाष्ठाions) to offset on
	 * condition.
	 *
	 * Condition code to mask mapping:
	 *
	 * CC | Description	   | Mask
	 * ------------------------------
	 * 0  | Opeअक्रमs equal	   |	8
	 * 1  | First opeअक्रम low  |	4
	 * 2  | First opeअक्रम high |	2
	 * 3  | Unused		   |	1
	 *
	 * For s390x relative branches: ip = ip + off_bytes
	 * For BPF relative branches:	insn = insn + off_insns + 1
	 *
	 * For example क्रम s390x with offset 0 we jump to the branch
	 * inकाष्ठाion itself (loop) and क्रम BPF with offset 0 we
	 * branch to the inकाष्ठाion behind the branch.
	 */
	हाल BPF_JMP | BPF_JA: /* अगर (true) */
		mask = 0xf000; /* j */
		जाओ branch_oc;
	हाल BPF_JMP | BPF_JSGT | BPF_K: /* ((s64) dst > (s64) imm) */
	हाल BPF_JMP32 | BPF_JSGT | BPF_K: /* ((s32) dst > (s32) imm) */
		mask = 0x2000; /* jh */
		जाओ branch_ks;
	हाल BPF_JMP | BPF_JSLT | BPF_K: /* ((s64) dst < (s64) imm) */
	हाल BPF_JMP32 | BPF_JSLT | BPF_K: /* ((s32) dst < (s32) imm) */
		mask = 0x4000; /* jl */
		जाओ branch_ks;
	हाल BPF_JMP | BPF_JSGE | BPF_K: /* ((s64) dst >= (s64) imm) */
	हाल BPF_JMP32 | BPF_JSGE | BPF_K: /* ((s32) dst >= (s32) imm) */
		mask = 0xa000; /* jhe */
		जाओ branch_ks;
	हाल BPF_JMP | BPF_JSLE | BPF_K: /* ((s64) dst <= (s64) imm) */
	हाल BPF_JMP32 | BPF_JSLE | BPF_K: /* ((s32) dst <= (s32) imm) */
		mask = 0xc000; /* jle */
		जाओ branch_ks;
	हाल BPF_JMP | BPF_JGT | BPF_K: /* (dst_reg > imm) */
	हाल BPF_JMP32 | BPF_JGT | BPF_K: /* ((u32) dst_reg > (u32) imm) */
		mask = 0x2000; /* jh */
		जाओ branch_ku;
	हाल BPF_JMP | BPF_JLT | BPF_K: /* (dst_reg < imm) */
	हाल BPF_JMP32 | BPF_JLT | BPF_K: /* ((u32) dst_reg < (u32) imm) */
		mask = 0x4000; /* jl */
		जाओ branch_ku;
	हाल BPF_JMP | BPF_JGE | BPF_K: /* (dst_reg >= imm) */
	हाल BPF_JMP32 | BPF_JGE | BPF_K: /* ((u32) dst_reg >= (u32) imm) */
		mask = 0xa000; /* jhe */
		जाओ branch_ku;
	हाल BPF_JMP | BPF_JLE | BPF_K: /* (dst_reg <= imm) */
	हाल BPF_JMP32 | BPF_JLE | BPF_K: /* ((u32) dst_reg <= (u32) imm) */
		mask = 0xc000; /* jle */
		जाओ branch_ku;
	हाल BPF_JMP | BPF_JNE | BPF_K: /* (dst_reg != imm) */
	हाल BPF_JMP32 | BPF_JNE | BPF_K: /* ((u32) dst_reg != (u32) imm) */
		mask = 0x7000; /* jne */
		जाओ branch_ku;
	हाल BPF_JMP | BPF_JEQ | BPF_K: /* (dst_reg == imm) */
	हाल BPF_JMP32 | BPF_JEQ | BPF_K: /* ((u32) dst_reg == (u32) imm) */
		mask = 0x8000; /* je */
		जाओ branch_ku;
	हाल BPF_JMP | BPF_JSET | BPF_K: /* (dst_reg & imm) */
	हाल BPF_JMP32 | BPF_JSET | BPF_K: /* ((u32) dst_reg & (u32) imm) */
		mask = 0x7000; /* jnz */
		अगर (BPF_CLASS(insn->code) == BPF_JMP32) अणु
			/* llilf %w1,imm (load zero extend imm) */
			EMIT6_IMM(0xc00f0000, REG_W1, imm);
			/* nr %w1,%dst */
			EMIT2(0x1400, REG_W1, dst_reg);
		पूर्ण अन्यथा अणु
			/* lgfi %w1,imm (load sign extend imm) */
			EMIT6_IMM(0xc0010000, REG_W1, imm);
			/* ngr %w1,%dst */
			EMIT4(0xb9800000, REG_W1, dst_reg);
		पूर्ण
		जाओ branch_oc;

	हाल BPF_JMP | BPF_JSGT | BPF_X: /* ((s64) dst > (s64) src) */
	हाल BPF_JMP32 | BPF_JSGT | BPF_X: /* ((s32) dst > (s32) src) */
		mask = 0x2000; /* jh */
		जाओ branch_xs;
	हाल BPF_JMP | BPF_JSLT | BPF_X: /* ((s64) dst < (s64) src) */
	हाल BPF_JMP32 | BPF_JSLT | BPF_X: /* ((s32) dst < (s32) src) */
		mask = 0x4000; /* jl */
		जाओ branch_xs;
	हाल BPF_JMP | BPF_JSGE | BPF_X: /* ((s64) dst >= (s64) src) */
	हाल BPF_JMP32 | BPF_JSGE | BPF_X: /* ((s32) dst >= (s32) src) */
		mask = 0xa000; /* jhe */
		जाओ branch_xs;
	हाल BPF_JMP | BPF_JSLE | BPF_X: /* ((s64) dst <= (s64) src) */
	हाल BPF_JMP32 | BPF_JSLE | BPF_X: /* ((s32) dst <= (s32) src) */
		mask = 0xc000; /* jle */
		जाओ branch_xs;
	हाल BPF_JMP | BPF_JGT | BPF_X: /* (dst > src) */
	हाल BPF_JMP32 | BPF_JGT | BPF_X: /* ((u32) dst > (u32) src) */
		mask = 0x2000; /* jh */
		जाओ branch_xu;
	हाल BPF_JMP | BPF_JLT | BPF_X: /* (dst < src) */
	हाल BPF_JMP32 | BPF_JLT | BPF_X: /* ((u32) dst < (u32) src) */
		mask = 0x4000; /* jl */
		जाओ branch_xu;
	हाल BPF_JMP | BPF_JGE | BPF_X: /* (dst >= src) */
	हाल BPF_JMP32 | BPF_JGE | BPF_X: /* ((u32) dst >= (u32) src) */
		mask = 0xa000; /* jhe */
		जाओ branch_xu;
	हाल BPF_JMP | BPF_JLE | BPF_X: /* (dst <= src) */
	हाल BPF_JMP32 | BPF_JLE | BPF_X: /* ((u32) dst <= (u32) src) */
		mask = 0xc000; /* jle */
		जाओ branch_xu;
	हाल BPF_JMP | BPF_JNE | BPF_X: /* (dst != src) */
	हाल BPF_JMP32 | BPF_JNE | BPF_X: /* ((u32) dst != (u32) src) */
		mask = 0x7000; /* jne */
		जाओ branch_xu;
	हाल BPF_JMP | BPF_JEQ | BPF_X: /* (dst == src) */
	हाल BPF_JMP32 | BPF_JEQ | BPF_X: /* ((u32) dst == (u32) src) */
		mask = 0x8000; /* je */
		जाओ branch_xu;
	हाल BPF_JMP | BPF_JSET | BPF_X: /* (dst & src) */
	हाल BPF_JMP32 | BPF_JSET | BPF_X: /* ((u32) dst & (u32) src) */
	अणु
		bool is_jmp32 = BPF_CLASS(insn->code) == BPF_JMP32;

		mask = 0x7000; /* jnz */
		/* nrk or ngrk %w1,%dst,%src */
		EMIT4_RRF((is_jmp32 ? 0xb9f40000 : 0xb9e40000),
			  REG_W1, dst_reg, src_reg);
		जाओ branch_oc;
branch_ks:
		is_jmp32 = BPF_CLASS(insn->code) == BPF_JMP32;
		/* cfi or cgfi %dst,imm */
		EMIT6_IMM(is_jmp32 ? 0xc20d0000 : 0xc20c0000,
			  dst_reg, imm);
		अगर (!is_first_pass(jit) &&
		    can_use_rel(jit, addrs[i + off + 1])) अणु
			/* brc mask,off */
			EMIT4_PCREL_RIC(0xa7040000,
					mask >> 12, addrs[i + off + 1]);
		पूर्ण अन्यथा अणु
			/* brcl mask,off */
			EMIT6_PCREL_RILC(0xc0040000,
					 mask >> 12, addrs[i + off + 1]);
		पूर्ण
		अवरोध;
branch_ku:
		/* lgfi %w1,imm (load sign extend imm) */
		src_reg = REG_1;
		EMIT6_IMM(0xc0010000, src_reg, imm);
		जाओ branch_xu;
branch_xs:
		is_jmp32 = BPF_CLASS(insn->code) == BPF_JMP32;
		अगर (!is_first_pass(jit) &&
		    can_use_rel(jit, addrs[i + off + 1])) अणु
			/* crj or cgrj %dst,%src,mask,off */
			EMIT6_PCREL(0xec000000, (is_jmp32 ? 0x0076 : 0x0064),
				    dst_reg, src_reg, i, off, mask);
		पूर्ण अन्यथा अणु
			/* cr or cgr %dst,%src */
			अगर (is_jmp32)
				EMIT2(0x1900, dst_reg, src_reg);
			अन्यथा
				EMIT4(0xb9200000, dst_reg, src_reg);
			/* brcl mask,off */
			EMIT6_PCREL_RILC(0xc0040000,
					 mask >> 12, addrs[i + off + 1]);
		पूर्ण
		अवरोध;
branch_xu:
		is_jmp32 = BPF_CLASS(insn->code) == BPF_JMP32;
		अगर (!is_first_pass(jit) &&
		    can_use_rel(jit, addrs[i + off + 1])) अणु
			/* clrj or clgrj %dst,%src,mask,off */
			EMIT6_PCREL(0xec000000, (is_jmp32 ? 0x0077 : 0x0065),
				    dst_reg, src_reg, i, off, mask);
		पूर्ण अन्यथा अणु
			/* clr or clgr %dst,%src */
			अगर (is_jmp32)
				EMIT2(0x1500, dst_reg, src_reg);
			अन्यथा
				EMIT4(0xb9210000, dst_reg, src_reg);
			/* brcl mask,off */
			EMIT6_PCREL_RILC(0xc0040000,
					 mask >> 12, addrs[i + off + 1]);
		पूर्ण
		अवरोध;
branch_oc:
		अगर (!is_first_pass(jit) &&
		    can_use_rel(jit, addrs[i + off + 1])) अणु
			/* brc mask,off */
			EMIT4_PCREL_RIC(0xa7040000,
					mask >> 12, addrs[i + off + 1]);
		पूर्ण अन्यथा अणु
			/* brcl mask,off */
			EMIT6_PCREL_RILC(0xc0040000,
					 mask >> 12, addrs[i + off + 1]);
		पूर्ण
		अवरोध;
	पूर्ण
	शेष: /* too complex, give up */
		pr_err("Unknown opcode %02x\n", insn->code);
		वापस -1;
	पूर्ण

	अगर (probe_prg != -1) अणु
		/*
		 * Handlers of certain exceptions leave psw.addr poपूर्णांकing to
		 * the inकाष्ठाion directly after the failing one. Thereक्रमe,
		 * create two exception table entries and also add a nop in
		 * हाल two probing inकाष्ठाions come directly after each
		 * other.
		 */
		nop_prg = jit->prg;
		/* bcr 0,%0 */
		_EMIT2(0x0700);
		err = bpf_jit_probe_mem(jit, fp, probe_prg, nop_prg);
		अगर (err < 0)
			वापस err;
	पूर्ण

	वापस insn_count;
पूर्ण

/*
 * Return whether new i-th inकाष्ठाion address करोes not violate any invariant
 */
अटल bool bpf_is_new_addr_sane(काष्ठा bpf_jit *jit, पूर्णांक i)
अणु
	/* On the first pass anything goes */
	अगर (is_first_pass(jit))
		वापस true;

	/* The codegen pass must not change anything */
	अगर (is_codegen_pass(jit))
		वापस jit->addrs[i] == jit->prg;

	/* Passes in between must not increase code size */
	वापस jit->addrs[i] >= jit->prg;
पूर्ण

/*
 * Update the address of i-th inकाष्ठाion
 */
अटल पूर्णांक bpf_set_addr(काष्ठा bpf_jit *jit, पूर्णांक i)
अणु
	पूर्णांक delta;

	अगर (is_codegen_pass(jit)) अणु
		delta = jit->prg - jit->addrs[i];
		अगर (delta < 0)
			bpf_skip(jit, -delta);
	पूर्ण
	अगर (WARN_ON_ONCE(!bpf_is_new_addr_sane(jit, i)))
		वापस -1;
	jit->addrs[i] = jit->prg;
	वापस 0;
पूर्ण

/*
 * Compile eBPF program पूर्णांकo s390x code
 */
अटल पूर्णांक bpf_jit_prog(काष्ठा bpf_jit *jit, काष्ठा bpf_prog *fp,
			bool extra_pass, u32 stack_depth)
अणु
	पूर्णांक i, insn_count, lit32_size, lit64_size;

	jit->lit32 = jit->lit32_start;
	jit->lit64 = jit->lit64_start;
	jit->prg = 0;
	jit->excnt = 0;

	bpf_jit_prologue(jit, stack_depth);
	अगर (bpf_set_addr(jit, 0) < 0)
		वापस -1;
	क्रम (i = 0; i < fp->len; i += insn_count) अणु
		insn_count = bpf_jit_insn(jit, fp, i, extra_pass, stack_depth);
		अगर (insn_count < 0)
			वापस -1;
		/* Next inकाष्ठाion address */
		अगर (bpf_set_addr(jit, i + insn_count) < 0)
			वापस -1;
	पूर्ण
	bpf_jit_epilogue(jit, stack_depth);

	lit32_size = jit->lit32 - jit->lit32_start;
	lit64_size = jit->lit64 - jit->lit64_start;
	jit->lit32_start = jit->prg;
	अगर (lit32_size)
		jit->lit32_start = ALIGN(jit->lit32_start, 4);
	jit->lit64_start = jit->lit32_start + lit32_size;
	अगर (lit64_size)
		jit->lit64_start = ALIGN(jit->lit64_start, 8);
	jit->size = jit->lit64_start + lit64_size;
	jit->size_prg = jit->prg;

	अगर (WARN_ON_ONCE(fp->aux->extable &&
			 jit->excnt != fp->aux->num_exentries))
		/* Verअगरier bug - too many entries. */
		वापस -1;

	वापस 0;
पूर्ण

bool bpf_jit_needs_zext(व्योम)
अणु
	वापस true;
पूर्ण

काष्ठा s390_jit_data अणु
	काष्ठा bpf_binary_header *header;
	काष्ठा bpf_jit ctx;
	पूर्णांक pass;
पूर्ण;

अटल काष्ठा bpf_binary_header *bpf_jit_alloc(काष्ठा bpf_jit *jit,
					       काष्ठा bpf_prog *fp)
अणु
	काष्ठा bpf_binary_header *header;
	u32 extable_size;
	u32 code_size;

	/* We need two entries per insn. */
	fp->aux->num_exentries *= 2;

	code_size = roundup(jit->size,
			    __alignof__(काष्ठा exception_table_entry));
	extable_size = fp->aux->num_exentries *
		माप(काष्ठा exception_table_entry);
	header = bpf_jit_binary_alloc(code_size + extable_size, &jit->prg_buf,
				      8, jit_fill_hole);
	अगर (!header)
		वापस शून्य;
	fp->aux->extable = (काष्ठा exception_table_entry *)
		(jit->prg_buf + code_size);
	वापस header;
पूर्ण

/*
 * Compile eBPF program "fp"
 */
काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *fp)
अणु
	u32 stack_depth = round_up(fp->aux->stack_depth, 8);
	काष्ठा bpf_prog *पंचांगp, *orig_fp = fp;
	काष्ठा bpf_binary_header *header;
	काष्ठा s390_jit_data *jit_data;
	bool पंचांगp_blinded = false;
	bool extra_pass = false;
	काष्ठा bpf_jit jit;
	पूर्णांक pass;

	अगर (!fp->jit_requested)
		वापस orig_fp;

	पंचांगp = bpf_jit_blind_स्थिरants(fp);
	/*
	 * If blinding was requested and we failed during blinding,
	 * we must fall back to the पूर्णांकerpreter.
	 */
	अगर (IS_ERR(पंचांगp))
		वापस orig_fp;
	अगर (पंचांगp != fp) अणु
		पंचांगp_blinded = true;
		fp = पंचांगp;
	पूर्ण

	jit_data = fp->aux->jit_data;
	अगर (!jit_data) अणु
		jit_data = kzalloc(माप(*jit_data), GFP_KERNEL);
		अगर (!jit_data) अणु
			fp = orig_fp;
			जाओ out;
		पूर्ण
		fp->aux->jit_data = jit_data;
	पूर्ण
	अगर (jit_data->ctx.addrs) अणु
		jit = jit_data->ctx;
		header = jit_data->header;
		extra_pass = true;
		pass = jit_data->pass + 1;
		जाओ skip_init_ctx;
	पूर्ण

	स_रखो(&jit, 0, माप(jit));
	jit.addrs = kvसुस्मृति(fp->len + 1, माप(*jit.addrs), GFP_KERNEL);
	अगर (jit.addrs == शून्य) अणु
		fp = orig_fp;
		जाओ out;
	पूर्ण
	/*
	 * Three initial passes:
	 *   - 1/2: Determine clobbered रेजिस्टरs
	 *   - 3:   Calculate program size and addrs arrray
	 */
	क्रम (pass = 1; pass <= 3; pass++) अणु
		अगर (bpf_jit_prog(&jit, fp, extra_pass, stack_depth)) अणु
			fp = orig_fp;
			जाओ मुक्त_addrs;
		पूर्ण
	पूर्ण
	/*
	 * Final pass: Allocate and generate program
	 */
	header = bpf_jit_alloc(&jit, fp);
	अगर (!header) अणु
		fp = orig_fp;
		जाओ मुक्त_addrs;
	पूर्ण
skip_init_ctx:
	अगर (bpf_jit_prog(&jit, fp, extra_pass, stack_depth)) अणु
		bpf_jit_binary_मुक्त(header);
		fp = orig_fp;
		जाओ मुक्त_addrs;
	पूर्ण
	अगर (bpf_jit_enable > 1) अणु
		bpf_jit_dump(fp->len, jit.size, pass, jit.prg_buf);
		prपूर्णांक_fn_code(jit.prg_buf, jit.size_prg);
	पूर्ण
	अगर (!fp->is_func || extra_pass) अणु
		bpf_jit_binary_lock_ro(header);
	पूर्ण अन्यथा अणु
		jit_data->header = header;
		jit_data->ctx = jit;
		jit_data->pass = pass;
	पूर्ण
	fp->bpf_func = (व्योम *) jit.prg_buf;
	fp->jited = 1;
	fp->jited_len = jit.size;

	अगर (!fp->is_func || extra_pass) अणु
		bpf_prog_fill_jited_linfo(fp, jit.addrs + 1);
मुक्त_addrs:
		kvमुक्त(jit.addrs);
		kमुक्त(jit_data);
		fp->aux->jit_data = शून्य;
	पूर्ण
out:
	अगर (पंचांगp_blinded)
		bpf_jit_prog_release_other(fp, fp == orig_fp ?
					   पंचांगp : orig_fp);
	वापस fp;
पूर्ण
