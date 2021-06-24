<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Just-In-Time compiler क्रम eBPF filters on IA32 (32bit x86)
 *
 * Author: Wang YanQing (udknight@gmail.com)
 * The code based on code and ideas from:
 * Eric Dumazet (eric.dumazet@gmail.com)
 * and from:
 * Shubham Bansal <illusionist.neo@gmail.com>
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <यंत्र/cacheflush.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <linux/bpf.h>

/*
 * eBPF prog stack layout:
 *
 *                         high
 * original ESP =>        +-----+
 *                        |     | callee saved रेजिस्टरs
 *                        +-----+
 *                        | ... | eBPF JIT scratch space
 * BPF_FP,IA32_EBP  =>    +-----+
 *                        | ... | eBPF prog stack
 *                        +-----+
 *                        |RSVD | JIT scratchpad
 * current ESP =>         +-----+
 *                        |     |
 *                        | ... | Function call stack
 *                        |     |
 *                        +-----+
 *                          low
 *
 * The callee saved रेजिस्टरs:
 *
 *                                high
 * original ESP =>        +------------------+ \
 *                        |        ebp       | |
 * current EBP =>         +------------------+ पूर्ण callee saved रेजिस्टरs
 *                        |    ebx,esi,edi   | |
 *                        +------------------+ /
 *                                low
 */

अटल u8 *emit_code(u8 *ptr, u32 bytes, अचिन्हित पूर्णांक len)
अणु
	अगर (len == 1)
		*ptr = bytes;
	अन्यथा अगर (len == 2)
		*(u16 *)ptr = bytes;
	अन्यथा अणु
		*(u32 *)ptr = bytes;
		barrier();
	पूर्ण
	वापस ptr + len;
पूर्ण

#घोषणा EMIT(bytes, len) \
	करो अणु prog = emit_code(prog, bytes, len); cnt += len; पूर्ण जबतक (0)

#घोषणा EMIT1(b1)		EMIT(b1, 1)
#घोषणा EMIT2(b1, b2)		EMIT((b1) + ((b2) << 8), 2)
#घोषणा EMIT3(b1, b2, b3)	EMIT((b1) + ((b2) << 8) + ((b3) << 16), 3)
#घोषणा EMIT4(b1, b2, b3, b4)   \
	EMIT((b1) + ((b2) << 8) + ((b3) << 16) + ((b4) << 24), 4)

#घोषणा EMIT1_off32(b1, off) \
	करो अणु EMIT1(b1); EMIT(off, 4); पूर्ण जबतक (0)
#घोषणा EMIT2_off32(b1, b2, off) \
	करो अणु EMIT2(b1, b2); EMIT(off, 4); पूर्ण जबतक (0)
#घोषणा EMIT3_off32(b1, b2, b3, off) \
	करो अणु EMIT3(b1, b2, b3); EMIT(off, 4); पूर्ण जबतक (0)
#घोषणा EMIT4_off32(b1, b2, b3, b4, off) \
	करो अणु EMIT4(b1, b2, b3, b4); EMIT(off, 4); पूर्ण जबतक (0)

#घोषणा jmp_label(label, jmp_insn_len) (label - cnt - jmp_insn_len)

अटल bool is_imm8(पूर्णांक value)
अणु
	वापस value <= 127 && value >= -128;
पूर्ण

अटल bool is_simm32(s64 value)
अणु
	वापस value == (s64) (s32) value;
पूर्ण

#घोषणा STACK_OFFSET(k)	(k)
#घोषणा TCALL_CNT	(MAX_BPF_JIT_REG + 0)	/* Tail Call Count */

#घोषणा IA32_EAX	(0x0)
#घोषणा IA32_EBX	(0x3)
#घोषणा IA32_ECX	(0x1)
#घोषणा IA32_EDX	(0x2)
#घोषणा IA32_ESI	(0x6)
#घोषणा IA32_EDI	(0x7)
#घोषणा IA32_EBP	(0x5)
#घोषणा IA32_ESP	(0x4)

/*
 * List of x86 cond jumps opcodes (. + s8)
 * Add 0x10 (and an extra 0x0f) to generate far jumps (. + s32)
 */
#घोषणा IA32_JB  0x72
#घोषणा IA32_JAE 0x73
#घोषणा IA32_JE  0x74
#घोषणा IA32_JNE 0x75
#घोषणा IA32_JBE 0x76
#घोषणा IA32_JA  0x77
#घोषणा IA32_JL  0x7C
#घोषणा IA32_JGE 0x7D
#घोषणा IA32_JLE 0x7E
#घोषणा IA32_JG  0x7F

#घोषणा COND_JMP_OPCODE_INVALID	(0xFF)

/*
 * Map eBPF रेजिस्टरs to IA32 32bit रेजिस्टरs or stack scratch space.
 *
 * 1. All the रेजिस्टरs, R0-R10, are mapped to scratch space on stack.
 * 2. We need two 64 bit temp रेजिस्टरs to करो complex operations on eBPF
 *    रेजिस्टरs.
 * 3. For perक्रमmance reason, the BPF_REG_AX क्रम blinding स्थिरant, is
 *    mapped to real hardware रेजिस्टर pair, IA32_ESI and IA32_EDI.
 *
 * As the eBPF रेजिस्टरs are all 64 bit रेजिस्टरs and IA32 has only 32 bit
 * रेजिस्टरs, we have to map each eBPF रेजिस्टरs with two IA32 32 bit regs
 * or scratch memory space and we have to build eBPF 64 bit रेजिस्टर from those.
 *
 * We use IA32_EAX, IA32_EDX, IA32_ECX, IA32_EBX as temporary रेजिस्टरs.
 */
अटल स्थिर u8 bpf2ia32[][2] = अणु
	/* Return value from in-kernel function, and निकास value from eBPF */
	[BPF_REG_0] = अणुSTACK_OFFSET(0), STACK_OFFSET(4)पूर्ण,

	/* The arguments from eBPF program to in-kernel function */
	/* Stored on stack scratch space */
	[BPF_REG_1] = अणुSTACK_OFFSET(8), STACK_OFFSET(12)पूर्ण,
	[BPF_REG_2] = अणुSTACK_OFFSET(16), STACK_OFFSET(20)पूर्ण,
	[BPF_REG_3] = अणुSTACK_OFFSET(24), STACK_OFFSET(28)पूर्ण,
	[BPF_REG_4] = अणुSTACK_OFFSET(32), STACK_OFFSET(36)पूर्ण,
	[BPF_REG_5] = अणुSTACK_OFFSET(40), STACK_OFFSET(44)पूर्ण,

	/* Callee saved रेजिस्टरs that in-kernel function will preserve */
	/* Stored on stack scratch space */
	[BPF_REG_6] = अणुSTACK_OFFSET(48), STACK_OFFSET(52)पूर्ण,
	[BPF_REG_7] = अणुSTACK_OFFSET(56), STACK_OFFSET(60)पूर्ण,
	[BPF_REG_8] = अणुSTACK_OFFSET(64), STACK_OFFSET(68)पूर्ण,
	[BPF_REG_9] = अणुSTACK_OFFSET(72), STACK_OFFSET(76)पूर्ण,

	/* Read only Frame Poपूर्णांकer to access Stack */
	[BPF_REG_FP] = अणुSTACK_OFFSET(80), STACK_OFFSET(84)पूर्ण,

	/* Temporary रेजिस्टर क्रम blinding स्थिरants. */
	[BPF_REG_AX] = अणुIA32_ESI, IA32_EDIपूर्ण,

	/* Tail call count. Stored on stack scratch space. */
	[TCALL_CNT] = अणुSTACK_OFFSET(88), STACK_OFFSET(92)पूर्ण,
पूर्ण;

#घोषणा dst_lo	dst[0]
#घोषणा dst_hi	dst[1]
#घोषणा src_lo	src[0]
#घोषणा src_hi	src[1]

#घोषणा STACK_ALIGNMENT	8
/*
 * Stack space क्रम BPF_REG_1, BPF_REG_2, BPF_REG_3, BPF_REG_4,
 * BPF_REG_5, BPF_REG_6, BPF_REG_7, BPF_REG_8, BPF_REG_9,
 * BPF_REG_FP, BPF_REG_AX and Tail call counts.
 */
#घोषणा SCRATCH_SIZE 96

/* Total stack size used in JITed code */
#घोषणा _STACK_SIZE	(stack_depth + SCRATCH_SIZE)

#घोषणा STACK_SIZE ALIGN(_STACK_SIZE, STACK_ALIGNMENT)

/* Get the offset of eBPF REGISTERs stored on scratch space. */
#घोषणा STACK_VAR(off) (off)

/* Encode 'dst_reg' register into IA32 opcode 'byte' */
अटल u8 add_1reg(u8 byte, u32 dst_reg)
अणु
	वापस byte + dst_reg;
पूर्ण

/* Encode 'dst_reg' and 'src_reg' registers into IA32 opcode 'byte' */
अटल u8 add_2reg(u8 byte, u32 dst_reg, u32 src_reg)
अणु
	वापस byte + dst_reg + (src_reg << 3);
पूर्ण

अटल व्योम jit_fill_hole(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	/* Fill whole space with पूर्णांक3 inकाष्ठाions */
	स_रखो(area, 0xcc, size);
पूर्ण

अटल अंतरभूत व्योम emit_ia32_mov_i(स्थिर u8 dst, स्थिर u32 val, bool dstk,
				   u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (dstk) अणु
		अगर (val == 0) अणु
			/* xor eax,eax */
			EMIT2(0x33, add_2reg(0xC0, IA32_EAX, IA32_EAX));
			/* mov dword ptr [ebp+off],eax */
			EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAR(dst));
		पूर्ण अन्यथा अणु
			EMIT3_off32(0xC7, add_1reg(0x40, IA32_EBP),
				    STACK_VAR(dst), val);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (val == 0)
			EMIT2(0x33, add_2reg(0xC0, dst, dst));
		अन्यथा
			EMIT2_off32(0xC7, add_1reg(0xC0, dst),
				    val);
	पूर्ण
	*pprog = prog;
पूर्ण

/* dst = imm (4 bytes)*/
अटल अंतरभूत व्योम emit_ia32_mov_r(स्थिर u8 dst, स्थिर u8 src, bool dstk,
				   bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 sreg = sstk ? IA32_EAX : src;

	अगर (sstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(src));
	अगर (dstk)
		/* mov dword ptr [ebp+off],eax */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, sreg), STACK_VAR(dst));
	अन्यथा
		/* mov dst,sreg */
		EMIT2(0x89, add_2reg(0xC0, dst, sreg));

	*pprog = prog;
पूर्ण

/* dst = src */
अटल अंतरभूत व्योम emit_ia32_mov_r64(स्थिर bool is64, स्थिर u8 dst[],
				     स्थिर u8 src[], bool dstk,
				     bool sstk, u8 **pprog,
				     स्थिर काष्ठा bpf_prog_aux *aux)
अणु
	emit_ia32_mov_r(dst_lo, src_lo, dstk, sstk, pprog);
	अगर (is64)
		/* complete 8 byte move */
		emit_ia32_mov_r(dst_hi, src_hi, dstk, sstk, pprog);
	अन्यथा अगर (!aux->verअगरier_zext)
		/* zero out high 4 bytes */
		emit_ia32_mov_i(dst_hi, 0, dstk, pprog);
पूर्ण

/* Sign extended move */
अटल अंतरभूत व्योम emit_ia32_mov_i64(स्थिर bool is64, स्थिर u8 dst[],
				     स्थिर u32 val, bool dstk, u8 **pprog)
अणु
	u32 hi = 0;

	अगर (is64 && (val & (1<<31)))
		hi = (u32)~0;
	emit_ia32_mov_i(dst_lo, val, dstk, pprog);
	emit_ia32_mov_i(dst_hi, hi, dstk, pprog);
पूर्ण

/*
 * ALU operation (32 bit)
 * dst = dst * src
 */
अटल अंतरभूत व्योम emit_ia32_mul_r(स्थिर u8 dst, स्थिर u8 src, bool dstk,
				   bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 sreg = sstk ? IA32_ECX : src;

	अगर (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(src));

	अगर (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(dst));
	अन्यथा
		/* mov eax,dst */
		EMIT2(0x8B, add_2reg(0xC0, dst, IA32_EAX));


	EMIT2(0xF7, add_1reg(0xE0, sreg));

	अगर (dstk)
		/* mov dword ptr [ebp+off],eax */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst));
	अन्यथा
		/* mov dst,eax */
		EMIT2(0x89, add_2reg(0xC0, dst, IA32_EAX));

	*pprog = prog;
पूर्ण

अटल अंतरभूत व्योम emit_ia32_to_le_r64(स्थिर u8 dst[], s32 val,
					 bool dstk, u8 **pprog,
					 स्थिर काष्ठा bpf_prog_aux *aux)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk && val != 64) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण
	चयन (val) अणु
	हाल 16:
		/*
		 * Emit 'movzwl eax,ax' to zero extend 16-bit
		 * पूर्णांकo 64 bit
		 */
		EMIT2(0x0F, 0xB7);
		EMIT1(add_2reg(0xC0, dreg_lo, dreg_lo));
		अगर (!aux->verअगरier_zext)
			/* xor dreg_hi,dreg_hi */
			EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
		अवरोध;
	हाल 32:
		अगर (!aux->verअगरier_zext)
			/* xor dreg_hi,dreg_hi */
			EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
		अवरोध;
	हाल 64:
		/* nop */
		अवरोध;
	पूर्ण

	अगर (dstk && val != 64) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	*pprog = prog;
पूर्ण

अटल अंतरभूत व्योम emit_ia32_to_be_r64(स्थिर u8 dst[], s32 val,
				       bool dstk, u8 **pprog,
				       स्थिर काष्ठा bpf_prog_aux *aux)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण
	चयन (val) अणु
	हाल 16:
		/* Emit 'ror %ax, 8' to swap lower 2 bytes */
		EMIT1(0x66);
		EMIT3(0xC1, add_1reg(0xC8, dreg_lo), 8);

		EMIT2(0x0F, 0xB7);
		EMIT1(add_2reg(0xC0, dreg_lo, dreg_lo));

		अगर (!aux->verअगरier_zext)
			/* xor dreg_hi,dreg_hi */
			EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
		अवरोध;
	हाल 32:
		/* Emit 'bswap eax' to swap lower 4 bytes */
		EMIT1(0x0F);
		EMIT1(add_1reg(0xC8, dreg_lo));

		अगर (!aux->verअगरier_zext)
			/* xor dreg_hi,dreg_hi */
			EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
		अवरोध;
	हाल 64:
		/* Emit 'bswap eax' to swap lower 4 bytes */
		EMIT1(0x0F);
		EMIT1(add_1reg(0xC8, dreg_lo));

		/* Emit 'bswap edx' to swap lower 4 bytes */
		EMIT1(0x0F);
		EMIT1(add_1reg(0xC8, dreg_hi));

		/* mov ecx,dreg_hi */
		EMIT2(0x89, add_2reg(0xC0, IA32_ECX, dreg_hi));
		/* mov dreg_hi,dreg_lo */
		EMIT2(0x89, add_2reg(0xC0, dreg_hi, dreg_lo));
		/* mov dreg_lo,ecx */
		EMIT2(0x89, add_2reg(0xC0, dreg_lo, IA32_ECX));

		अवरोध;
	पूर्ण
	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	*pprog = prog;
पूर्ण

/*
 * ALU operation (32 bit)
 * dst = dst (भाग|mod) src
 */
अटल अंतरभूत व्योम emit_ia32_भाग_mod_r(स्थिर u8 op, स्थिर u8 dst, स्थिर u8 src,
				       bool dstk, bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(src));
	अन्यथा अगर (src != IA32_ECX)
		/* mov ecx,src */
		EMIT2(0x8B, add_2reg(0xC0, src, IA32_ECX));

	अगर (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst));
	अन्यथा
		/* mov eax,dst */
		EMIT2(0x8B, add_2reg(0xC0, dst, IA32_EAX));

	/* xor edx,edx */
	EMIT2(0x31, add_2reg(0xC0, IA32_EDX, IA32_EDX));
	/* भाग ecx */
	EMIT2(0xF7, add_1reg(0xF0, IA32_ECX));

	अगर (op == BPF_MOD) अणु
		अगर (dstk)
			EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EDX),
			      STACK_VAR(dst));
		अन्यथा
			EMIT2(0x89, add_2reg(0xC0, dst, IA32_EDX));
	पूर्ण अन्यथा अणु
		अगर (dstk)
			EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAR(dst));
		अन्यथा
			EMIT2(0x89, add_2reg(0xC0, dst, IA32_EAX));
	पूर्ण
	*pprog = prog;
पूर्ण

/*
 * ALU operation (32 bit)
 * dst = dst (shअगरt) src
 */
अटल अंतरभूत व्योम emit_ia32_shअगरt_r(स्थिर u8 op, स्थिर u8 dst, स्थिर u8 src,
				     bool dstk, bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg = dstk ? IA32_EAX : dst;
	u8 b2;

	अगर (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(dst));

	अगर (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(src));
	अन्यथा अगर (src != IA32_ECX)
		/* mov ecx,src */
		EMIT2(0x8B, add_2reg(0xC0, src, IA32_ECX));

	चयन (op) अणु
	हाल BPF_LSH:
		b2 = 0xE0; अवरोध;
	हाल BPF_RSH:
		b2 = 0xE8; अवरोध;
	हाल BPF_ARSH:
		b2 = 0xF8; अवरोध;
	शेष:
		वापस;
	पूर्ण
	EMIT2(0xD3, add_1reg(b2, dreg));

	अगर (dstk)
		/* mov dword ptr [ebp+off],dreg */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg), STACK_VAR(dst));
	*pprog = prog;
पूर्ण

/*
 * ALU operation (32 bit)
 * dst = dst (op) src
 */
अटल अंतरभूत व्योम emit_ia32_alu_r(स्थिर bool is64, स्थिर bool hi, स्थिर u8 op,
				   स्थिर u8 dst, स्थिर u8 src, bool dstk,
				   bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 sreg = sstk ? IA32_EAX : src;
	u8 dreg = dstk ? IA32_EDX : dst;

	अगर (sstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(src));

	अगर (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX), STACK_VAR(dst));

	चयन (BPF_OP(op)) अणु
	/* dst = dst + src */
	हाल BPF_ADD:
		अगर (hi && is64)
			EMIT2(0x11, add_2reg(0xC0, dreg, sreg));
		अन्यथा
			EMIT2(0x01, add_2reg(0xC0, dreg, sreg));
		अवरोध;
	/* dst = dst - src */
	हाल BPF_SUB:
		अगर (hi && is64)
			EMIT2(0x19, add_2reg(0xC0, dreg, sreg));
		अन्यथा
			EMIT2(0x29, add_2reg(0xC0, dreg, sreg));
		अवरोध;
	/* dst = dst | src */
	हाल BPF_OR:
		EMIT2(0x09, add_2reg(0xC0, dreg, sreg));
		अवरोध;
	/* dst = dst & src */
	हाल BPF_AND:
		EMIT2(0x21, add_2reg(0xC0, dreg, sreg));
		अवरोध;
	/* dst = dst ^ src */
	हाल BPF_XOR:
		EMIT2(0x31, add_2reg(0xC0, dreg, sreg));
		अवरोध;
	पूर्ण

	अगर (dstk)
		/* mov dword ptr [ebp+off],dreg */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg),
		      STACK_VAR(dst));
	*pprog = prog;
पूर्ण

/* ALU operation (64 bit) */
अटल अंतरभूत व्योम emit_ia32_alu_r64(स्थिर bool is64, स्थिर u8 op,
				     स्थिर u8 dst[], स्थिर u8 src[],
				     bool dstk,  bool sstk,
				     u8 **pprog, स्थिर काष्ठा bpf_prog_aux *aux)
अणु
	u8 *prog = *pprog;

	emit_ia32_alu_r(is64, false, op, dst_lo, src_lo, dstk, sstk, &prog);
	अगर (is64)
		emit_ia32_alu_r(is64, true, op, dst_hi, src_hi, dstk, sstk,
				&prog);
	अन्यथा अगर (!aux->verअगरier_zext)
		emit_ia32_mov_i(dst_hi, 0, dstk, &prog);
	*pprog = prog;
पूर्ण

/*
 * ALU operation (32 bit)
 * dst = dst (op) val
 */
अटल अंतरभूत व्योम emit_ia32_alu_i(स्थिर bool is64, स्थिर bool hi, स्थिर u8 op,
				   स्थिर u8 dst, स्थिर s32 val, bool dstk,
				   u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg = dstk ? IA32_EAX : dst;
	u8 sreg = IA32_EDX;

	अगर (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(dst));

	अगर (!is_imm8(val))
		/* mov edx,imm32*/
		EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EDX), val);

	चयन (op) अणु
	/* dst = dst + val */
	हाल BPF_ADD:
		अगर (hi && is64) अणु
			अगर (is_imm8(val))
				EMIT3(0x83, add_1reg(0xD0, dreg), val);
			अन्यथा
				EMIT2(0x11, add_2reg(0xC0, dreg, sreg));
		पूर्ण अन्यथा अणु
			अगर (is_imm8(val))
				EMIT3(0x83, add_1reg(0xC0, dreg), val);
			अन्यथा
				EMIT2(0x01, add_2reg(0xC0, dreg, sreg));
		पूर्ण
		अवरोध;
	/* dst = dst - val */
	हाल BPF_SUB:
		अगर (hi && is64) अणु
			अगर (is_imm8(val))
				EMIT3(0x83, add_1reg(0xD8, dreg), val);
			अन्यथा
				EMIT2(0x19, add_2reg(0xC0, dreg, sreg));
		पूर्ण अन्यथा अणु
			अगर (is_imm8(val))
				EMIT3(0x83, add_1reg(0xE8, dreg), val);
			अन्यथा
				EMIT2(0x29, add_2reg(0xC0, dreg, sreg));
		पूर्ण
		अवरोध;
	/* dst = dst | val */
	हाल BPF_OR:
		अगर (is_imm8(val))
			EMIT3(0x83, add_1reg(0xC8, dreg), val);
		अन्यथा
			EMIT2(0x09, add_2reg(0xC0, dreg, sreg));
		अवरोध;
	/* dst = dst & val */
	हाल BPF_AND:
		अगर (is_imm8(val))
			EMIT3(0x83, add_1reg(0xE0, dreg), val);
		अन्यथा
			EMIT2(0x21, add_2reg(0xC0, dreg, sreg));
		अवरोध;
	/* dst = dst ^ val */
	हाल BPF_XOR:
		अगर (is_imm8(val))
			EMIT3(0x83, add_1reg(0xF0, dreg), val);
		अन्यथा
			EMIT2(0x31, add_2reg(0xC0, dreg, sreg));
		अवरोध;
	हाल BPF_NEG:
		EMIT2(0xF7, add_1reg(0xD8, dreg));
		अवरोध;
	पूर्ण

	अगर (dstk)
		/* mov dword ptr [ebp+off],dreg */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg),
		      STACK_VAR(dst));
	*pprog = prog;
पूर्ण

/* ALU operation (64 bit) */
अटल अंतरभूत व्योम emit_ia32_alu_i64(स्थिर bool is64, स्थिर u8 op,
				     स्थिर u8 dst[], स्थिर u32 val,
				     bool dstk, u8 **pprog,
				     स्थिर काष्ठा bpf_prog_aux *aux)
अणु
	u8 *prog = *pprog;
	u32 hi = 0;

	अगर (is64 && (val & (1<<31)))
		hi = (u32)~0;

	emit_ia32_alu_i(is64, false, op, dst_lo, val, dstk, &prog);
	अगर (is64)
		emit_ia32_alu_i(is64, true, op, dst_hi, hi, dstk, &prog);
	अन्यथा अगर (!aux->verअगरier_zext)
		emit_ia32_mov_i(dst_hi, 0, dstk, &prog);

	*pprog = prog;
पूर्ण

/* dst = ~dst (64 bit) */
अटल अंतरभूत व्योम emit_ia32_neg64(स्थिर u8 dst[], bool dstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण

	/* neg dreg_lo */
	EMIT2(0xF7, add_1reg(0xD8, dreg_lo));
	/* adc dreg_hi,0x0 */
	EMIT3(0x83, add_1reg(0xD0, dreg_hi), 0x00);
	/* neg dreg_hi */
	EMIT2(0xF7, add_1reg(0xD8, dreg_hi));

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	*pprog = prog;
पूर्ण

/* dst = dst << src */
अटल अंतरभूत व्योम emit_ia32_lsh_r64(स्थिर u8 dst[], स्थिर u8 src[],
				     bool dstk, bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण

	अगर (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(src_lo));
	अन्यथा
		/* mov ecx,src_lo */
		EMIT2(0x8B, add_2reg(0xC0, src_lo, IA32_ECX));

	/* shld dreg_hi,dreg_lo,cl */
	EMIT3(0x0F, 0xA5, add_2reg(0xC0, dreg_hi, dreg_lo));
	/* shl dreg_lo,cl */
	EMIT2(0xD3, add_1reg(0xE0, dreg_lo));

	/* अगर ecx >= 32, mov dreg_lo पूर्णांकo dreg_hi and clear dreg_lo */

	/* cmp ecx,32 */
	EMIT3(0x83, add_1reg(0xF8, IA32_ECX), 32);
	/* skip the next two inकाष्ठाions (4 bytes) when < 32 */
	EMIT2(IA32_JB, 4);

	/* mov dreg_hi,dreg_lo */
	EMIT2(0x89, add_2reg(0xC0, dreg_hi, dreg_lo));
	/* xor dreg_lo,dreg_lo */
	EMIT2(0x33, add_2reg(0xC0, dreg_lo, dreg_lo));

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	/* out: */
	*pprog = prog;
पूर्ण

/* dst = dst >> src (चिन्हित)*/
अटल अंतरभूत व्योम emit_ia32_arsh_r64(स्थिर u8 dst[], स्थिर u8 src[],
				      bool dstk, bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण

	अगर (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(src_lo));
	अन्यथा
		/* mov ecx,src_lo */
		EMIT2(0x8B, add_2reg(0xC0, src_lo, IA32_ECX));

	/* shrd dreg_lo,dreg_hi,cl */
	EMIT3(0x0F, 0xAD, add_2reg(0xC0, dreg_lo, dreg_hi));
	/* sar dreg_hi,cl */
	EMIT2(0xD3, add_1reg(0xF8, dreg_hi));

	/* अगर ecx >= 32, mov dreg_hi to dreg_lo and set/clear dreg_hi depending on sign */

	/* cmp ecx,32 */
	EMIT3(0x83, add_1reg(0xF8, IA32_ECX), 32);
	/* skip the next two inकाष्ठाions (5 bytes) when < 32 */
	EMIT2(IA32_JB, 5);

	/* mov dreg_lo,dreg_hi */
	EMIT2(0x89, add_2reg(0xC0, dreg_lo, dreg_hi));
	/* sar dreg_hi,31 */
	EMIT3(0xC1, add_1reg(0xF8, dreg_hi), 31);

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	/* out: */
	*pprog = prog;
पूर्ण

/* dst = dst >> src */
अटल अंतरभूत व्योम emit_ia32_rsh_r64(स्थिर u8 dst[], स्थिर u8 src[], bool dstk,
				     bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण

	अगर (sstk)
		/* mov ecx,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(src_lo));
	अन्यथा
		/* mov ecx,src_lo */
		EMIT2(0x8B, add_2reg(0xC0, src_lo, IA32_ECX));

	/* shrd dreg_lo,dreg_hi,cl */
	EMIT3(0x0F, 0xAD, add_2reg(0xC0, dreg_lo, dreg_hi));
	/* shr dreg_hi,cl */
	EMIT2(0xD3, add_1reg(0xE8, dreg_hi));

	/* अगर ecx >= 32, mov dreg_hi to dreg_lo and clear dreg_hi */

	/* cmp ecx,32 */
	EMIT3(0x83, add_1reg(0xF8, IA32_ECX), 32);
	/* skip the next two inकाष्ठाions (4 bytes) when < 32 */
	EMIT2(IA32_JB, 4);

	/* mov dreg_lo,dreg_hi */
	EMIT2(0x89, add_2reg(0xC0, dreg_lo, dreg_hi));
	/* xor dreg_hi,dreg_hi */
	EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	/* out: */
	*pprog = prog;
पूर्ण

/* dst = dst << val */
अटल अंतरभूत व्योम emit_ia32_lsh_i64(स्थिर u8 dst[], स्थिर u32 val,
				     bool dstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण
	/* Do LSH operation */
	अगर (val < 32) अणु
		/* shld dreg_hi,dreg_lo,imm8 */
		EMIT4(0x0F, 0xA4, add_2reg(0xC0, dreg_hi, dreg_lo), val);
		/* shl dreg_lo,imm8 */
		EMIT3(0xC1, add_1reg(0xE0, dreg_lo), val);
	पूर्ण अन्यथा अगर (val >= 32 && val < 64) अणु
		u32 value = val - 32;

		/* shl dreg_lo,imm8 */
		EMIT3(0xC1, add_1reg(0xE0, dreg_lo), value);
		/* mov dreg_hi,dreg_lo */
		EMIT2(0x89, add_2reg(0xC0, dreg_hi, dreg_lo));
		/* xor dreg_lo,dreg_lo */
		EMIT2(0x33, add_2reg(0xC0, dreg_lo, dreg_lo));
	पूर्ण अन्यथा अणु
		/* xor dreg_lo,dreg_lo */
		EMIT2(0x33, add_2reg(0xC0, dreg_lo, dreg_lo));
		/* xor dreg_hi,dreg_hi */
		EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
	पूर्ण

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	*pprog = prog;
पूर्ण

/* dst = dst >> val */
अटल अंतरभूत व्योम emit_ia32_rsh_i64(स्थिर u8 dst[], स्थिर u32 val,
				     bool dstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण

	/* Do RSH operation */
	अगर (val < 32) अणु
		/* shrd dreg_lo,dreg_hi,imm8 */
		EMIT4(0x0F, 0xAC, add_2reg(0xC0, dreg_lo, dreg_hi), val);
		/* shr dreg_hi,imm8 */
		EMIT3(0xC1, add_1reg(0xE8, dreg_hi), val);
	पूर्ण अन्यथा अगर (val >= 32 && val < 64) अणु
		u32 value = val - 32;

		/* shr dreg_hi,imm8 */
		EMIT3(0xC1, add_1reg(0xE8, dreg_hi), value);
		/* mov dreg_lo,dreg_hi */
		EMIT2(0x89, add_2reg(0xC0, dreg_lo, dreg_hi));
		/* xor dreg_hi,dreg_hi */
		EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
	पूर्ण अन्यथा अणु
		/* xor dreg_lo,dreg_lo */
		EMIT2(0x33, add_2reg(0xC0, dreg_lo, dreg_lo));
		/* xor dreg_hi,dreg_hi */
		EMIT2(0x33, add_2reg(0xC0, dreg_hi, dreg_hi));
	पूर्ण

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	*pprog = prog;
पूर्ण

/* dst = dst >> val (चिन्हित) */
अटल अंतरभूत व्योम emit_ia32_arsh_i64(स्थिर u8 dst[], स्थिर u32 val,
				      bool dstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
	u8 dreg_hi = dstk ? IA32_EDX : dst_hi;

	अगर (dstk) अणु
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(dst_hi));
	पूर्ण
	/* Do RSH operation */
	अगर (val < 32) अणु
		/* shrd dreg_lo,dreg_hi,imm8 */
		EMIT4(0x0F, 0xAC, add_2reg(0xC0, dreg_lo, dreg_hi), val);
		/* ashr dreg_hi,imm8 */
		EMIT3(0xC1, add_1reg(0xF8, dreg_hi), val);
	पूर्ण अन्यथा अगर (val >= 32 && val < 64) अणु
		u32 value = val - 32;

		/* ashr dreg_hi,imm8 */
		EMIT3(0xC1, add_1reg(0xF8, dreg_hi), value);
		/* mov dreg_lo,dreg_hi */
		EMIT2(0x89, add_2reg(0xC0, dreg_lo, dreg_hi));

		/* ashr dreg_hi,imm8 */
		EMIT3(0xC1, add_1reg(0xF8, dreg_hi), 31);
	पूर्ण अन्यथा अणु
		/* ashr dreg_hi,imm8 */
		EMIT3(0xC1, add_1reg(0xF8, dreg_hi), 31);
		/* mov dreg_lo,dreg_hi */
		EMIT2(0x89, add_2reg(0xC0, dreg_lo, dreg_hi));
	पूर्ण

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],dreg_lo */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_lo),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],dreg_hi */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, dreg_hi),
		      STACK_VAR(dst_hi));
	पूर्ण
	*pprog = prog;
पूर्ण

अटल अंतरभूत व्योम emit_ia32_mul_r64(स्थिर u8 dst[], स्थिर u8 src[], bool dstk,
				     bool sstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_hi));
	अन्यथा
		/* mov eax,dst_hi */
		EMIT2(0x8B, add_2reg(0xC0, dst_hi, IA32_EAX));

	अगर (sstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(src_lo));
	अन्यथा
		/* mul src_lo */
		EMIT2(0xF7, add_1reg(0xE0, src_lo));

	/* mov ecx,eax */
	EMIT2(0x89, add_2reg(0xC0, IA32_ECX, IA32_EAX));

	अगर (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
	अन्यथा
		/* mov eax,dst_lo */
		EMIT2(0x8B, add_2reg(0xC0, dst_lo, IA32_EAX));

	अगर (sstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(src_hi));
	अन्यथा
		/* mul src_hi */
		EMIT2(0xF7, add_1reg(0xE0, src_hi));

	/* add eax,eax */
	EMIT2(0x01, add_2reg(0xC0, IA32_ECX, IA32_EAX));

	अगर (dstk)
		/* mov eax,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
	अन्यथा
		/* mov eax,dst_lo */
		EMIT2(0x8B, add_2reg(0xC0, dst_lo, IA32_EAX));

	अगर (sstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(src_lo));
	अन्यथा
		/* mul src_lo */
		EMIT2(0xF7, add_1reg(0xE0, src_lo));

	/* add ecx,edx */
	EMIT2(0x01, add_2reg(0xC0, IA32_ECX, IA32_EDX));

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],eax */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],ecx */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(dst_hi));
	पूर्ण अन्यथा अणु
		/* mov dst_lo,eax */
		EMIT2(0x89, add_2reg(0xC0, dst_lo, IA32_EAX));
		/* mov dst_hi,ecx */
		EMIT2(0x89, add_2reg(0xC0, dst_hi, IA32_ECX));
	पूर्ण

	*pprog = prog;
पूर्ण

अटल अंतरभूत व्योम emit_ia32_mul_i64(स्थिर u8 dst[], स्थिर u32 val,
				     bool dstk, u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	u32 hi;

	hi = val & (1<<31) ? (u32)~0 : 0;
	/* movl eax,imm32 */
	EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EAX), val);
	अगर (dstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(dst_hi));
	अन्यथा
		/* mul dst_hi */
		EMIT2(0xF7, add_1reg(0xE0, dst_hi));

	/* mov ecx,eax */
	EMIT2(0x89, add_2reg(0xC0, IA32_ECX, IA32_EAX));

	/* movl eax,imm32 */
	EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EAX), hi);
	अगर (dstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(dst_lo));
	अन्यथा
		/* mul dst_lo */
		EMIT2(0xF7, add_1reg(0xE0, dst_lo));
	/* add ecx,eax */
	EMIT2(0x01, add_2reg(0xC0, IA32_ECX, IA32_EAX));

	/* movl eax,imm32 */
	EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EAX), val);
	अगर (dstk)
		/* mul dword ptr [ebp+off] */
		EMIT3(0xF7, add_1reg(0x60, IA32_EBP), STACK_VAR(dst_lo));
	अन्यथा
		/* mul dst_lo */
		EMIT2(0xF7, add_1reg(0xE0, dst_lo));

	/* add ecx,edx */
	EMIT2(0x01, add_2reg(0xC0, IA32_ECX, IA32_EDX));

	अगर (dstk) अणु
		/* mov dword ptr [ebp+off],eax */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(dst_lo));
		/* mov dword ptr [ebp+off],ecx */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_ECX),
		      STACK_VAR(dst_hi));
	पूर्ण अन्यथा अणु
		/* mov dword ptr [ebp+off],eax */
		EMIT2(0x89, add_2reg(0xC0, dst_lo, IA32_EAX));
		/* mov dword ptr [ebp+off],ecx */
		EMIT2(0x89, add_2reg(0xC0, dst_hi, IA32_ECX));
	पूर्ण

	*pprog = prog;
पूर्ण

अटल पूर्णांक bpf_माप_प्रकारo_x86_bytes(पूर्णांक bpf_size)
अणु
	अगर (bpf_size == BPF_W)
		वापस 4;
	अन्यथा अगर (bpf_size == BPF_H)
		वापस 2;
	अन्यथा अगर (bpf_size == BPF_B)
		वापस 1;
	अन्यथा अगर (bpf_size == BPF_DW)
		वापस 4; /* imm32 */
	अन्यथा
		वापस 0;
पूर्ण

काष्ठा jit_context अणु
	पूर्णांक cleanup_addr; /* Epilogue code offset */
पूर्ण;

/* Maximum number of bytes emitted जबतक JITing one eBPF insn */
#घोषणा BPF_MAX_INSN_SIZE	128
#घोषणा BPF_INSN_SAFETY		64

#घोषणा PROLOGUE_SIZE 35

/*
 * Emit prologue code क्रम BPF program and check it's size.
 * bpf_tail_call helper will skip it जबतक jumping पूर्णांकo another program.
 */
अटल व्योम emit_prologue(u8 **pprog, u32 stack_depth)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	स्थिर u8 *r1 = bpf2ia32[BPF_REG_1];
	स्थिर u8 fplo = bpf2ia32[BPF_REG_FP][0];
	स्थिर u8 fphi = bpf2ia32[BPF_REG_FP][1];
	स्थिर u8 *tcc = bpf2ia32[TCALL_CNT];

	/* push ebp */
	EMIT1(0x55);
	/* mov ebp,esp */
	EMIT2(0x89, 0xE5);
	/* push edi */
	EMIT1(0x57);
	/* push esi */
	EMIT1(0x56);
	/* push ebx */
	EMIT1(0x53);

	/* sub esp,STACK_SIZE */
	EMIT2_off32(0x81, 0xEC, STACK_SIZE);
	/* sub ebp,SCRATCH_SIZE+12*/
	EMIT3(0x83, add_1reg(0xE8, IA32_EBP), SCRATCH_SIZE + 12);
	/* xor ebx,ebx */
	EMIT2(0x31, add_2reg(0xC0, IA32_EBX, IA32_EBX));

	/* Set up BPF prog stack base रेजिस्टर */
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBP), STACK_VAR(fplo));
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(fphi));

	/* Move BPF_CTX (EAX) to BPF_REG_R1 */
	/* mov dword ptr [ebp+off],eax */
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(r1[0]));
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(r1[1]));

	/* Initialize Tail Count */
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(tcc[0]));
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(tcc[1]));

	BUILD_BUG_ON(cnt != PROLOGUE_SIZE);
	*pprog = prog;
पूर्ण

/* Emit epilogue code क्रम BPF program */
अटल व्योम emit_epilogue(u8 **pprog, u32 stack_depth)
अणु
	u8 *prog = *pprog;
	स्थिर u8 *r0 = bpf2ia32[BPF_REG_0];
	पूर्णांक cnt = 0;

	/* mov eax,dword ptr [ebp+off]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(r0[0]));
	/* mov edx,dword ptr [ebp+off]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX), STACK_VAR(r0[1]));

	/* add ebp,SCRATCH_SIZE+12*/
	EMIT3(0x83, add_1reg(0xC0, IA32_EBP), SCRATCH_SIZE + 12);

	/* mov ebx,dword ptr [ebp-12]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EBX), -12);
	/* mov esi,dword ptr [ebp-8]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ESI), -8);
	/* mov edi,dword ptr [ebp-4]*/
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDI), -4);

	EMIT1(0xC9); /* leave */
	EMIT1(0xC3); /* ret */
	*pprog = prog;
पूर्ण

/*
 * Generate the following code:
 * ... bpf_tail_call(व्योम *ctx, काष्ठा bpf_array *array, u64 index) ...
 *   अगर (index >= array->map.max_entries)
 *     जाओ out;
 *   अगर (++tail_call_cnt > MAX_TAIL_CALL_CNT)
 *     जाओ out;
 *   prog = array->ptrs[index];
 *   अगर (prog == शून्य)
 *     जाओ out;
 *   जाओ *(prog->bpf_func + prologue_size);
 * out:
 */
अटल व्योम emit_bpf_tail_call(u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	स्थिर u8 *r1 = bpf2ia32[BPF_REG_1];
	स्थिर u8 *r2 = bpf2ia32[BPF_REG_2];
	स्थिर u8 *r3 = bpf2ia32[BPF_REG_3];
	स्थिर u8 *tcc = bpf2ia32[TCALL_CNT];
	u32 lo, hi;
	अटल पूर्णांक jmp_label1 = -1;

	/*
	 * अगर (index >= array->map.max_entries)
	 *     जाओ out;
	 */
	/* mov eax,dword ptr [ebp+off] */
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(r2[0]));
	/* mov edx,dword ptr [ebp+off] */
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX), STACK_VAR(r3[0]));

	/* cmp dword ptr [eax+off],edx */
	EMIT3(0x39, add_2reg(0x40, IA32_EAX, IA32_EDX),
	      दुरत्व(काष्ठा bpf_array, map.max_entries));
	/* jbe out */
	EMIT2(IA32_JBE, jmp_label(jmp_label1, 2));

	/*
	 * अगर (tail_call_cnt > MAX_TAIL_CALL_CNT)
	 *     जाओ out;
	 */
	lo = (u32)MAX_TAIL_CALL_CNT;
	hi = (u32)((u64)MAX_TAIL_CALL_CNT >> 32);
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(tcc[0]));
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(tcc[1]));

	/* cmp edx,hi */
	EMIT3(0x83, add_1reg(0xF8, IA32_EBX), hi);
	EMIT2(IA32_JNE, 3);
	/* cmp ecx,lo */
	EMIT3(0x83, add_1reg(0xF8, IA32_ECX), lo);

	/* ja out */
	EMIT2(IA32_JAE, jmp_label(jmp_label1, 2));

	/* add eax,0x1 */
	EMIT3(0x83, add_1reg(0xC0, IA32_ECX), 0x01);
	/* adc ebx,0x0 */
	EMIT3(0x83, add_1reg(0xD0, IA32_EBX), 0x00);

	/* mov dword ptr [ebp+off],eax */
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(tcc[0]));
	/* mov dword ptr [ebp+off],edx */
	EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EBX), STACK_VAR(tcc[1]));

	/* prog = array->ptrs[index]; */
	/* mov edx, [eax + edx * 4 + दुरत्व(...)] */
	EMIT3_off32(0x8B, 0x94, 0x90, दुरत्व(काष्ठा bpf_array, ptrs));

	/*
	 * अगर (prog == शून्य)
	 *     जाओ out;
	 */
	/* test edx,edx */
	EMIT2(0x85, add_2reg(0xC0, IA32_EDX, IA32_EDX));
	/* je out */
	EMIT2(IA32_JE, jmp_label(jmp_label1, 2));

	/* जाओ *(prog->bpf_func + prologue_size); */
	/* mov edx, dword ptr [edx + 32] */
	EMIT3(0x8B, add_2reg(0x40, IA32_EDX, IA32_EDX),
	      दुरत्व(काष्ठा bpf_prog, bpf_func));
	/* add edx,prologue_size */
	EMIT3(0x83, add_1reg(0xC0, IA32_EDX), PROLOGUE_SIZE);

	/* mov eax,dword ptr [ebp+off] */
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX), STACK_VAR(r1[0]));

	/*
	 * Now we're पढ़ोy to jump पूर्णांकo next BPF program:
	 * eax == ctx (1st arg)
	 * edx == prog->bpf_func + prologue_size
	 */
	RETPOLINE_EDX_BPF_JIT();

	अगर (jmp_label1 == -1)
		jmp_label1 = cnt;

	/* out: */
	*pprog = prog;
पूर्ण

/* Push the scratch stack रेजिस्टर on top of the stack. */
अटल अंतरभूत व्योम emit_push_r64(स्थिर u8 src[], u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	/* mov ecx,dword ptr [ebp+off] */
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(src_hi));
	/* push ecx */
	EMIT1(0x51);

	/* mov ecx,dword ptr [ebp+off] */
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(src_lo));
	/* push ecx */
	EMIT1(0x51);

	*pprog = prog;
पूर्ण

अटल व्योम emit_push_r32(स्थिर u8 src[], u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	/* mov ecx,dword ptr [ebp+off] */
	EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX), STACK_VAR(src_lo));
	/* push ecx */
	EMIT1(0x51);

	*pprog = prog;
पूर्ण

अटल u8 get_cond_jmp_opcode(स्थिर u8 op, bool is_cmp_lo)
अणु
	u8 jmp_cond;

	/* Convert BPF opcode to x86 */
	चयन (op) अणु
	हाल BPF_JEQ:
		jmp_cond = IA32_JE;
		अवरोध;
	हाल BPF_JSET:
	हाल BPF_JNE:
		jmp_cond = IA32_JNE;
		अवरोध;
	हाल BPF_JGT:
		/* GT is अचिन्हित '>', JA in x86 */
		jmp_cond = IA32_JA;
		अवरोध;
	हाल BPF_JLT:
		/* LT is अचिन्हित '<', JB in x86 */
		jmp_cond = IA32_JB;
		अवरोध;
	हाल BPF_JGE:
		/* GE is अचिन्हित '>=', JAE in x86 */
		jmp_cond = IA32_JAE;
		अवरोध;
	हाल BPF_JLE:
		/* LE is अचिन्हित '<=', JBE in x86 */
		jmp_cond = IA32_JBE;
		अवरोध;
	हाल BPF_JSGT:
		अगर (!is_cmp_lo)
			/* Signed '>', GT in x86 */
			jmp_cond = IA32_JG;
		अन्यथा
			/* GT is अचिन्हित '>', JA in x86 */
			jmp_cond = IA32_JA;
		अवरोध;
	हाल BPF_JSLT:
		अगर (!is_cmp_lo)
			/* Signed '<', LT in x86 */
			jmp_cond = IA32_JL;
		अन्यथा
			/* LT is अचिन्हित '<', JB in x86 */
			jmp_cond = IA32_JB;
		अवरोध;
	हाल BPF_JSGE:
		अगर (!is_cmp_lo)
			/* Signed '>=', GE in x86 */
			jmp_cond = IA32_JGE;
		अन्यथा
			/* GE is अचिन्हित '>=', JAE in x86 */
			jmp_cond = IA32_JAE;
		अवरोध;
	हाल BPF_JSLE:
		अगर (!is_cmp_lo)
			/* Signed '<=', LE in x86 */
			jmp_cond = IA32_JLE;
		अन्यथा
			/* LE is अचिन्हित '<=', JBE in x86 */
			jmp_cond = IA32_JBE;
		अवरोध;
	शेष: /* to silence GCC warning */
		jmp_cond = COND_JMP_OPCODE_INVALID;
		अवरोध;
	पूर्ण

	वापस jmp_cond;
पूर्ण

/* i386 kernel compiles with "-mregparm=3".  From gcc करोcument:
 *
 * ==== snippet ====
 * regparm (number)
 *	On x86-32 tarमाला_लो, the regparm attribute causes the compiler
 *	to pass arguments number one to (number) अगर they are of पूर्णांकegral
 *	type in रेजिस्टरs EAX, EDX, and ECX instead of on the stack.
 *	Functions that take a variable number of arguments जारी
 *	to be passed all of their arguments on the stack.
 * ==== snippet ====
 *
 * The first three args of a function will be considered क्रम
 * putting पूर्णांकo the 32bit रेजिस्टर EAX, EDX, and ECX.
 *
 * Two 32bit रेजिस्टरs are used to pass a 64bit arg.
 *
 * For example,
 * व्योम foo(u32 a, u32 b, u32 c, u32 d):
 *	u32 a: EAX
 *	u32 b: EDX
 *	u32 c: ECX
 *	u32 d: stack
 *
 * व्योम foo(u64 a, u32 b, u32 c):
 *	u64 a: EAX (lo32) EDX (hi32)
 *	u32 b: ECX
 *	u32 c: stack
 *
 * व्योम foo(u32 a, u64 b, u32 c):
 *	u32 a: EAX
 *	u64 b: EDX (lo32) ECX (hi32)
 *	u32 c: stack
 *
 * व्योम foo(u32 a, u32 b, u64 c):
 *	u32 a: EAX
 *	u32 b: EDX
 *	u64 c: stack
 *
 * The वापस value will be stored in the EAX (and EDX क्रम 64bit value).
 *
 * For example,
 * u32 foo(u32 a, u32 b, u32 c):
 *	वापस value: EAX
 *
 * u64 foo(u32 a, u32 b, u32 c):
 *	वापस value: EAX (lo32) EDX (hi32)
 *
 * Notes:
 *	The verअगरier only accepts function having पूर्णांकeger and poपूर्णांकers
 *	as its args and वापस value, so it करोes not have
 *	काष्ठा-by-value.
 *
 * emit_kfunc_call() finds out the btf_func_model by calling
 * bpf_jit_find_kfunc_model().  A btf_func_model
 * has the details about the number of args, size of each arg,
 * and the size of the वापस value.
 *
 * It first decides how many args can be passed by EAX, EDX, and ECX.
 * That will decide what args should be pushed to the stack:
 * [first_stack_regno, last_stack_regno] are the bpf regnos
 * that should be pushed to the stack.
 *
 * It will first push all args to the stack because the push
 * will need to use ECX.  Then, it moves
 * [BPF_REG_1, first_stack_regno) to EAX, EDX, and ECX.
 *
 * When emitting a call (0xE8), it needs to figure out
 * the jmp_offset relative to the jit-insn address immediately
 * following the call (0xE8) inकाष्ठाion.  At this poपूर्णांक, it knows
 * the end of the jit-insn address after completely translated the
 * current (BPF_JMP | BPF_CALL) bpf-insn.  It is passed as "end_addr"
 * to the emit_kfunc_call().  Thus, it can learn the "immediate-follow-call"
 * address by figuring out how many jit-insn is generated between
 * the call (0xE8) and the end_addr:
 *	- 0-1 jit-insn (3 bytes each) to restore the esp poपूर्णांकer अगर there
 *	  is arg pushed to the stack.
 *	- 0-2 jit-insns (3 bytes each) to handle the वापस value.
 */
अटल पूर्णांक emit_kfunc_call(स्थिर काष्ठा bpf_prog *bpf_prog, u8 *end_addr,
			   स्थिर काष्ठा bpf_insn *insn, u8 **pprog)
अणु
	स्थिर u8 arg_regs[] = अणु IA32_EAX, IA32_EDX, IA32_ECX पूर्ण;
	पूर्णांक i, cnt = 0, first_stack_regno, last_stack_regno;
	पूर्णांक मुक्त_arg_regs = ARRAY_SIZE(arg_regs);
	स्थिर काष्ठा btf_func_model *fm;
	पूर्णांक bytes_in_stack = 0;
	स्थिर u8 *cur_arg_reg;
	u8 *prog = *pprog;
	s64 jmp_offset;

	fm = bpf_jit_find_kfunc_model(bpf_prog, insn);
	अगर (!fm)
		वापस -EINVAL;

	first_stack_regno = BPF_REG_1;
	क्रम (i = 0; i < fm->nr_args; i++) अणु
		पूर्णांक regs_needed = fm->arg_size[i] > माप(u32) ? 2 : 1;

		अगर (regs_needed > मुक्त_arg_regs)
			अवरोध;

		मुक्त_arg_regs -= regs_needed;
		first_stack_regno++;
	पूर्ण

	/* Push the args to the stack */
	last_stack_regno = BPF_REG_0 + fm->nr_args;
	क्रम (i = last_stack_regno; i >= first_stack_regno; i--) अणु
		अगर (fm->arg_size[i - 1] > माप(u32)) अणु
			emit_push_r64(bpf2ia32[i], &prog);
			bytes_in_stack += 8;
		पूर्ण अन्यथा अणु
			emit_push_r32(bpf2ia32[i], &prog);
			bytes_in_stack += 4;
		पूर्ण
	पूर्ण

	cur_arg_reg = &arg_regs[0];
	क्रम (i = BPF_REG_1; i < first_stack_regno; i++) अणु
		/* mov e[adc]x,dword ptr [ebp+off] */
		EMIT3(0x8B, add_2reg(0x40, IA32_EBP, *cur_arg_reg++),
		      STACK_VAR(bpf2ia32[i][0]));
		अगर (fm->arg_size[i - 1] > माप(u32))
			/* mov e[adc]x,dword ptr [ebp+off] */
			EMIT3(0x8B, add_2reg(0x40, IA32_EBP, *cur_arg_reg++),
			      STACK_VAR(bpf2ia32[i][1]));
	पूर्ण

	अगर (bytes_in_stack)
		/* add esp,"bytes_in_stack" */
		end_addr -= 3;

	/* mov dword ptr [ebp+off],edx */
	अगर (fm->ret_size > माप(u32))
		end_addr -= 3;

	/* mov dword ptr [ebp+off],eax */
	अगर (fm->ret_size)
		end_addr -= 3;

	jmp_offset = (u8 *)__bpf_call_base + insn->imm - end_addr;
	अगर (!is_simm32(jmp_offset)) अणु
		pr_err("unsupported BPF kernel function jmp_offset:%lld\n",
		       jmp_offset);
		वापस -EINVAL;
	पूर्ण

	EMIT1_off32(0xE8, jmp_offset);

	अगर (fm->ret_size)
		/* mov dword ptr [ebp+off],eax */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
		      STACK_VAR(bpf2ia32[BPF_REG_0][0]));

	अगर (fm->ret_size > माप(u32))
		/* mov dword ptr [ebp+off],edx */
		EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EDX),
		      STACK_VAR(bpf2ia32[BPF_REG_0][1]));

	अगर (bytes_in_stack)
		/* add esp,"bytes_in_stack" */
		EMIT3(0x83, add_1reg(0xC0, IA32_ESP), bytes_in_stack);

	*pprog = prog;

	वापस 0;
पूर्ण

अटल पूर्णांक करो_jit(काष्ठा bpf_prog *bpf_prog, पूर्णांक *addrs, u8 *image,
		  पूर्णांक oldproglen, काष्ठा jit_context *ctx)
अणु
	काष्ठा bpf_insn *insn = bpf_prog->insnsi;
	पूर्णांक insn_cnt = bpf_prog->len;
	bool seen_निकास = false;
	u8 temp[BPF_MAX_INSN_SIZE + BPF_INSN_SAFETY];
	पूर्णांक i, cnt = 0;
	पूर्णांक proglen = 0;
	u8 *prog = temp;

	emit_prologue(&prog, bpf_prog->aux->stack_depth);

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		स्थिर s32 imm32 = insn->imm;
		स्थिर bool is64 = BPF_CLASS(insn->code) == BPF_ALU64;
		स्थिर bool dstk = insn->dst_reg != BPF_REG_AX;
		स्थिर bool sstk = insn->src_reg != BPF_REG_AX;
		स्थिर u8 code = insn->code;
		स्थिर u8 *dst = bpf2ia32[insn->dst_reg];
		स्थिर u8 *src = bpf2ia32[insn->src_reg];
		स्थिर u8 *r0 = bpf2ia32[BPF_REG_0];
		s64 jmp_offset;
		u8 jmp_cond;
		पूर्णांक ilen;
		u8 *func;

		चयन (code) अणु
		/* ALU operations */
		/* dst = src */
		हाल BPF_ALU | BPF_MOV | BPF_K:
		हाल BPF_ALU | BPF_MOV | BPF_X:
		हाल BPF_ALU64 | BPF_MOV | BPF_K:
		हाल BPF_ALU64 | BPF_MOV | BPF_X:
			चयन (BPF_SRC(code)) अणु
			हाल BPF_X:
				अगर (imm32 == 1) अणु
					/* Special mov32 क्रम zext. */
					emit_ia32_mov_i(dst_hi, 0, dstk, &prog);
					अवरोध;
				पूर्ण
				emit_ia32_mov_r64(is64, dst, src, dstk, sstk,
						  &prog, bpf_prog->aux);
				अवरोध;
			हाल BPF_K:
				/* Sign-extend immediate value to dst reg */
				emit_ia32_mov_i64(is64, dst, imm32,
						  dstk, &prog);
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
				emit_ia32_alu_r64(is64, BPF_OP(code), dst,
						  src, dstk, sstk, &prog,
						  bpf_prog->aux);
				अवरोध;
			हाल BPF_K:
				emit_ia32_alu_i64(is64, BPF_OP(code), dst,
						  imm32, dstk, &prog,
						  bpf_prog->aux);
				अवरोध;
			पूर्ण
			अवरोध;
		हाल BPF_ALU | BPF_MUL | BPF_K:
		हाल BPF_ALU | BPF_MUL | BPF_X:
			चयन (BPF_SRC(code)) अणु
			हाल BPF_X:
				emit_ia32_mul_r(dst_lo, src_lo, dstk,
						sstk, &prog);
				अवरोध;
			हाल BPF_K:
				/* mov ecx,imm32*/
				EMIT2_off32(0xC7, add_1reg(0xC0, IA32_ECX),
					    imm32);
				emit_ia32_mul_r(dst_lo, IA32_ECX, dstk,
						false, &prog);
				अवरोध;
			पूर्ण
			अगर (!bpf_prog->aux->verअगरier_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &prog);
			अवरोध;
		हाल BPF_ALU | BPF_LSH | BPF_X:
		हाल BPF_ALU | BPF_RSH | BPF_X:
		हाल BPF_ALU | BPF_ARSH | BPF_K:
		हाल BPF_ALU | BPF_ARSH | BPF_X:
			चयन (BPF_SRC(code)) अणु
			हाल BPF_X:
				emit_ia32_shअगरt_r(BPF_OP(code), dst_lo, src_lo,
						  dstk, sstk, &prog);
				अवरोध;
			हाल BPF_K:
				/* mov ecx,imm32*/
				EMIT2_off32(0xC7, add_1reg(0xC0, IA32_ECX),
					    imm32);
				emit_ia32_shअगरt_r(BPF_OP(code), dst_lo,
						  IA32_ECX, dstk, false,
						  &prog);
				अवरोध;
			पूर्ण
			अगर (!bpf_prog->aux->verअगरier_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &prog);
			अवरोध;
		/* dst = dst / src(imm) */
		/* dst = dst % src(imm) */
		हाल BPF_ALU | BPF_DIV | BPF_K:
		हाल BPF_ALU | BPF_DIV | BPF_X:
		हाल BPF_ALU | BPF_MOD | BPF_K:
		हाल BPF_ALU | BPF_MOD | BPF_X:
			चयन (BPF_SRC(code)) अणु
			हाल BPF_X:
				emit_ia32_भाग_mod_r(BPF_OP(code), dst_lo,
						    src_lo, dstk, sstk, &prog);
				अवरोध;
			हाल BPF_K:
				/* mov ecx,imm32*/
				EMIT2_off32(0xC7, add_1reg(0xC0, IA32_ECX),
					    imm32);
				emit_ia32_भाग_mod_r(BPF_OP(code), dst_lo,
						    IA32_ECX, dstk, false,
						    &prog);
				अवरोध;
			पूर्ण
			अगर (!bpf_prog->aux->verअगरier_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &prog);
			अवरोध;
		हाल BPF_ALU64 | BPF_DIV | BPF_K:
		हाल BPF_ALU64 | BPF_DIV | BPF_X:
		हाल BPF_ALU64 | BPF_MOD | BPF_K:
		हाल BPF_ALU64 | BPF_MOD | BPF_X:
			जाओ notyet;
		/* dst = dst >> imm */
		/* dst = dst << imm */
		हाल BPF_ALU | BPF_RSH | BPF_K:
		हाल BPF_ALU | BPF_LSH | BPF_K:
			अगर (unlikely(imm32 > 31))
				वापस -EINVAL;
			/* mov ecx,imm32*/
			EMIT2_off32(0xC7, add_1reg(0xC0, IA32_ECX), imm32);
			emit_ia32_shअगरt_r(BPF_OP(code), dst_lo, IA32_ECX, dstk,
					  false, &prog);
			अगर (!bpf_prog->aux->verअगरier_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &prog);
			अवरोध;
		/* dst = dst << imm */
		हाल BPF_ALU64 | BPF_LSH | BPF_K:
			अगर (unlikely(imm32 > 63))
				वापस -EINVAL;
			emit_ia32_lsh_i64(dst, imm32, dstk, &prog);
			अवरोध;
		/* dst = dst >> imm */
		हाल BPF_ALU64 | BPF_RSH | BPF_K:
			अगर (unlikely(imm32 > 63))
				वापस -EINVAL;
			emit_ia32_rsh_i64(dst, imm32, dstk, &prog);
			अवरोध;
		/* dst = dst << src */
		हाल BPF_ALU64 | BPF_LSH | BPF_X:
			emit_ia32_lsh_r64(dst, src, dstk, sstk, &prog);
			अवरोध;
		/* dst = dst >> src */
		हाल BPF_ALU64 | BPF_RSH | BPF_X:
			emit_ia32_rsh_r64(dst, src, dstk, sstk, &prog);
			अवरोध;
		/* dst = dst >> src (चिन्हित) */
		हाल BPF_ALU64 | BPF_ARSH | BPF_X:
			emit_ia32_arsh_r64(dst, src, dstk, sstk, &prog);
			अवरोध;
		/* dst = dst >> imm (चिन्हित) */
		हाल BPF_ALU64 | BPF_ARSH | BPF_K:
			अगर (unlikely(imm32 > 63))
				वापस -EINVAL;
			emit_ia32_arsh_i64(dst, imm32, dstk, &prog);
			अवरोध;
		/* dst = ~dst */
		हाल BPF_ALU | BPF_NEG:
			emit_ia32_alu_i(is64, false, BPF_OP(code),
					dst_lo, 0, dstk, &prog);
			अगर (!bpf_prog->aux->verअगरier_zext)
				emit_ia32_mov_i(dst_hi, 0, dstk, &prog);
			अवरोध;
		/* dst = ~dst (64 bit) */
		हाल BPF_ALU64 | BPF_NEG:
			emit_ia32_neg64(dst, dstk, &prog);
			अवरोध;
		/* dst = dst * src/imm */
		हाल BPF_ALU64 | BPF_MUL | BPF_X:
		हाल BPF_ALU64 | BPF_MUL | BPF_K:
			चयन (BPF_SRC(code)) अणु
			हाल BPF_X:
				emit_ia32_mul_r64(dst, src, dstk, sstk, &prog);
				अवरोध;
			हाल BPF_K:
				emit_ia32_mul_i64(dst, imm32, dstk, &prog);
				अवरोध;
			पूर्ण
			अवरोध;
		/* dst = htole(dst) */
		हाल BPF_ALU | BPF_END | BPF_FROM_LE:
			emit_ia32_to_le_r64(dst, imm32, dstk, &prog,
					    bpf_prog->aux);
			अवरोध;
		/* dst = htobe(dst) */
		हाल BPF_ALU | BPF_END | BPF_FROM_BE:
			emit_ia32_to_be_r64(dst, imm32, dstk, &prog,
					    bpf_prog->aux);
			अवरोध;
		/* dst = imm64 */
		हाल BPF_LD | BPF_IMM | BPF_DW: अणु
			s32 hi, lo = imm32;

			hi = insn[1].imm;
			emit_ia32_mov_i(dst_lo, lo, dstk, &prog);
			emit_ia32_mov_i(dst_hi, hi, dstk, &prog);
			insn++;
			i++;
			अवरोध;
		पूर्ण
		/* ST: *(u8*)(dst_reg + off) = imm */
		हाल BPF_ST | BPF_MEM | BPF_H:
		हाल BPF_ST | BPF_MEM | BPF_B:
		हाल BPF_ST | BPF_MEM | BPF_W:
		हाल BPF_ST | BPF_MEM | BPF_DW:
			अगर (dstk)
				/* mov eax,dword ptr [ebp+off] */
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(dst_lo));
			अन्यथा
				/* mov eax,dst_lo */
				EMIT2(0x8B, add_2reg(0xC0, dst_lo, IA32_EAX));

			चयन (BPF_SIZE(code)) अणु
			हाल BPF_B:
				EMIT(0xC6, 1); अवरोध;
			हाल BPF_H:
				EMIT2(0x66, 0xC7); अवरोध;
			हाल BPF_W:
			हाल BPF_DW:
				EMIT(0xC7, 1); अवरोध;
			पूर्ण

			अगर (is_imm8(insn->off))
				EMIT2(add_1reg(0x40, IA32_EAX), insn->off);
			अन्यथा
				EMIT1_off32(add_1reg(0x80, IA32_EAX),
					    insn->off);
			EMIT(imm32, bpf_माप_प्रकारo_x86_bytes(BPF_SIZE(code)));

			अगर (BPF_SIZE(code) == BPF_DW) अणु
				u32 hi;

				hi = imm32 & (1<<31) ? (u32)~0 : 0;
				EMIT2_off32(0xC7, add_1reg(0x80, IA32_EAX),
					    insn->off + 4);
				EMIT(hi, 4);
			पूर्ण
			अवरोध;

		/* STX: *(u8*)(dst_reg + off) = src_reg */
		हाल BPF_STX | BPF_MEM | BPF_B:
		हाल BPF_STX | BPF_MEM | BPF_H:
		हाल BPF_STX | BPF_MEM | BPF_W:
		हाल BPF_STX | BPF_MEM | BPF_DW:
			अगर (dstk)
				/* mov eax,dword ptr [ebp+off] */
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(dst_lo));
			अन्यथा
				/* mov eax,dst_lo */
				EMIT2(0x8B, add_2reg(0xC0, dst_lo, IA32_EAX));

			अगर (sstk)
				/* mov edx,dword ptr [ebp+off] */
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
				      STACK_VAR(src_lo));
			अन्यथा
				/* mov edx,src_lo */
				EMIT2(0x8B, add_2reg(0xC0, src_lo, IA32_EDX));

			चयन (BPF_SIZE(code)) अणु
			हाल BPF_B:
				EMIT(0x88, 1); अवरोध;
			हाल BPF_H:
				EMIT2(0x66, 0x89); अवरोध;
			हाल BPF_W:
			हाल BPF_DW:
				EMIT(0x89, 1); अवरोध;
			पूर्ण

			अगर (is_imm8(insn->off))
				EMIT2(add_2reg(0x40, IA32_EAX, IA32_EDX),
				      insn->off);
			अन्यथा
				EMIT1_off32(add_2reg(0x80, IA32_EAX, IA32_EDX),
					    insn->off);

			अगर (BPF_SIZE(code) == BPF_DW) अणु
				अगर (sstk)
					/* mov edi,dword ptr [ebp+off] */
					EMIT3(0x8B, add_2reg(0x40, IA32_EBP,
							     IA32_EDX),
					      STACK_VAR(src_hi));
				अन्यथा
					/* mov edi,src_hi */
					EMIT2(0x8B, add_2reg(0xC0, src_hi,
							     IA32_EDX));
				EMIT1(0x89);
				अगर (is_imm8(insn->off + 4)) अणु
					EMIT2(add_2reg(0x40, IA32_EAX,
						       IA32_EDX),
					      insn->off + 4);
				पूर्ण अन्यथा अणु
					EMIT1(add_2reg(0x80, IA32_EAX,
						       IA32_EDX));
					EMIT(insn->off + 4, 4);
				पूर्ण
			पूर्ण
			अवरोध;

		/* LDX: dst_reg = *(u8*)(src_reg + off) */
		हाल BPF_LDX | BPF_MEM | BPF_B:
		हाल BPF_LDX | BPF_MEM | BPF_H:
		हाल BPF_LDX | BPF_MEM | BPF_W:
		हाल BPF_LDX | BPF_MEM | BPF_DW:
			अगर (sstk)
				/* mov eax,dword ptr [ebp+off] */
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(src_lo));
			अन्यथा
				/* mov eax,dword ptr [ebp+off] */
				EMIT2(0x8B, add_2reg(0xC0, src_lo, IA32_EAX));

			चयन (BPF_SIZE(code)) अणु
			हाल BPF_B:
				EMIT2(0x0F, 0xB6); अवरोध;
			हाल BPF_H:
				EMIT2(0x0F, 0xB7); अवरोध;
			हाल BPF_W:
			हाल BPF_DW:
				EMIT(0x8B, 1); अवरोध;
			पूर्ण

			अगर (is_imm8(insn->off))
				EMIT2(add_2reg(0x40, IA32_EAX, IA32_EDX),
				      insn->off);
			अन्यथा
				EMIT1_off32(add_2reg(0x80, IA32_EAX, IA32_EDX),
					    insn->off);

			अगर (dstk)
				/* mov dword ptr [ebp+off],edx */
				EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EDX),
				      STACK_VAR(dst_lo));
			अन्यथा
				/* mov dst_lo,edx */
				EMIT2(0x89, add_2reg(0xC0, dst_lo, IA32_EDX));
			चयन (BPF_SIZE(code)) अणु
			हाल BPF_B:
			हाल BPF_H:
			हाल BPF_W:
				अगर (bpf_prog->aux->verअगरier_zext)
					अवरोध;
				अगर (dstk) अणु
					EMIT3(0xC7, add_1reg(0x40, IA32_EBP),
					      STACK_VAR(dst_hi));
					EMIT(0x0, 4);
				पूर्ण अन्यथा अणु
					/* xor dst_hi,dst_hi */
					EMIT2(0x33,
					      add_2reg(0xC0, dst_hi, dst_hi));
				पूर्ण
				अवरोध;
			हाल BPF_DW:
				EMIT2_off32(0x8B,
					    add_2reg(0x80, IA32_EAX, IA32_EDX),
					    insn->off + 4);
				अगर (dstk)
					EMIT3(0x89,
					      add_2reg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAR(dst_hi));
				अन्यथा
					EMIT2(0x89,
					      add_2reg(0xC0, dst_hi, IA32_EDX));
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अवरोध;
		/* call */
		हाल BPF_JMP | BPF_CALL:
		अणु
			स्थिर u8 *r1 = bpf2ia32[BPF_REG_1];
			स्थिर u8 *r2 = bpf2ia32[BPF_REG_2];
			स्थिर u8 *r3 = bpf2ia32[BPF_REG_3];
			स्थिर u8 *r4 = bpf2ia32[BPF_REG_4];
			स्थिर u8 *r5 = bpf2ia32[BPF_REG_5];

			अगर (insn->src_reg == BPF_PSEUDO_CALL)
				जाओ notyet;

			अगर (insn->src_reg == BPF_PSEUDO_KFUNC_CALL) अणु
				पूर्णांक err;

				err = emit_kfunc_call(bpf_prog,
						      image + addrs[i],
						      insn, &prog);

				अगर (err)
					वापस err;
				अवरोध;
			पूर्ण

			func = (u8 *) __bpf_call_base + imm32;
			jmp_offset = func - (image + addrs[i]);

			अगर (!imm32 || !is_simm32(jmp_offset)) अणु
				pr_err("unsupported BPF func %d addr %p image %p\n",
				       imm32, func, image);
				वापस -EINVAL;
			पूर्ण

			/* mov eax,dword ptr [ebp+off] */
			EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAR(r1[0]));
			/* mov edx,dword ptr [ebp+off] */
			EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EDX),
			      STACK_VAR(r1[1]));

			emit_push_r64(r5, &prog);
			emit_push_r64(r4, &prog);
			emit_push_r64(r3, &prog);
			emit_push_r64(r2, &prog);

			EMIT1_off32(0xE8, jmp_offset + 9);

			/* mov dword ptr [ebp+off],eax */
			EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EAX),
			      STACK_VAR(r0[0]));
			/* mov dword ptr [ebp+off],edx */
			EMIT3(0x89, add_2reg(0x40, IA32_EBP, IA32_EDX),
			      STACK_VAR(r0[1]));

			/* add esp,32 */
			EMIT3(0x83, add_1reg(0xC0, IA32_ESP), 32);
			अवरोध;
		पूर्ण
		हाल BPF_JMP | BPF_TAIL_CALL:
			emit_bpf_tail_call(&prog);
			अवरोध;

		/* cond jump */
		हाल BPF_JMP | BPF_JEQ | BPF_X:
		हाल BPF_JMP | BPF_JNE | BPF_X:
		हाल BPF_JMP | BPF_JGT | BPF_X:
		हाल BPF_JMP | BPF_JLT | BPF_X:
		हाल BPF_JMP | BPF_JGE | BPF_X:
		हाल BPF_JMP | BPF_JLE | BPF_X:
		हाल BPF_JMP32 | BPF_JEQ | BPF_X:
		हाल BPF_JMP32 | BPF_JNE | BPF_X:
		हाल BPF_JMP32 | BPF_JGT | BPF_X:
		हाल BPF_JMP32 | BPF_JLT | BPF_X:
		हाल BPF_JMP32 | BPF_JGE | BPF_X:
		हाल BPF_JMP32 | BPF_JLE | BPF_X:
		हाल BPF_JMP32 | BPF_JSGT | BPF_X:
		हाल BPF_JMP32 | BPF_JSLE | BPF_X:
		हाल BPF_JMP32 | BPF_JSLT | BPF_X:
		हाल BPF_JMP32 | BPF_JSGE | BPF_X: अणु
			bool is_jmp64 = BPF_CLASS(insn->code) == BPF_JMP;
			u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
			u8 dreg_hi = dstk ? IA32_EDX : dst_hi;
			u8 sreg_lo = sstk ? IA32_ECX : src_lo;
			u8 sreg_hi = sstk ? IA32_EBX : src_hi;

			अगर (dstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(dst_lo));
				अगर (is_jmp64)
					EMIT3(0x8B,
					      add_2reg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAR(dst_hi));
			पूर्ण

			अगर (sstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
				      STACK_VAR(src_lo));
				अगर (is_jmp64)
					EMIT3(0x8B,
					      add_2reg(0x40, IA32_EBP,
						       IA32_EBX),
					      STACK_VAR(src_hi));
			पूर्ण

			अगर (is_jmp64) अणु
				/* cmp dreg_hi,sreg_hi */
				EMIT2(0x39, add_2reg(0xC0, dreg_hi, sreg_hi));
				EMIT2(IA32_JNE, 2);
			पूर्ण
			/* cmp dreg_lo,sreg_lo */
			EMIT2(0x39, add_2reg(0xC0, dreg_lo, sreg_lo));
			जाओ emit_cond_jmp;
		पूर्ण
		हाल BPF_JMP | BPF_JSGT | BPF_X:
		हाल BPF_JMP | BPF_JSLE | BPF_X:
		हाल BPF_JMP | BPF_JSLT | BPF_X:
		हाल BPF_JMP | BPF_JSGE | BPF_X: अणु
			u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
			u8 dreg_hi = dstk ? IA32_EDX : dst_hi;
			u8 sreg_lo = sstk ? IA32_ECX : src_lo;
			u8 sreg_hi = sstk ? IA32_EBX : src_hi;

			अगर (dstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(dst_lo));
				EMIT3(0x8B,
				      add_2reg(0x40, IA32_EBP,
					       IA32_EDX),
				      STACK_VAR(dst_hi));
			पूर्ण

			अगर (sstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
				      STACK_VAR(src_lo));
				EMIT3(0x8B,
				      add_2reg(0x40, IA32_EBP,
					       IA32_EBX),
				      STACK_VAR(src_hi));
			पूर्ण

			/* cmp dreg_hi,sreg_hi */
			EMIT2(0x39, add_2reg(0xC0, dreg_hi, sreg_hi));
			EMIT2(IA32_JNE, 10);
			/* cmp dreg_lo,sreg_lo */
			EMIT2(0x39, add_2reg(0xC0, dreg_lo, sreg_lo));
			जाओ emit_cond_jmp_चिन्हित;
		पूर्ण
		हाल BPF_JMP | BPF_JSET | BPF_X:
		हाल BPF_JMP32 | BPF_JSET | BPF_X: अणु
			bool is_jmp64 = BPF_CLASS(insn->code) == BPF_JMP;
			u8 dreg_lo = IA32_EAX;
			u8 dreg_hi = IA32_EDX;
			u8 sreg_lo = sstk ? IA32_ECX : src_lo;
			u8 sreg_hi = sstk ? IA32_EBX : src_hi;

			अगर (dstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(dst_lo));
				अगर (is_jmp64)
					EMIT3(0x8B,
					      add_2reg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAR(dst_hi));
			पूर्ण अन्यथा अणु
				/* mov dreg_lo,dst_lo */
				EMIT2(0x89, add_2reg(0xC0, dreg_lo, dst_lo));
				अगर (is_jmp64)
					/* mov dreg_hi,dst_hi */
					EMIT2(0x89,
					      add_2reg(0xC0, dreg_hi, dst_hi));
			पूर्ण

			अगर (sstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_ECX),
				      STACK_VAR(src_lo));
				अगर (is_jmp64)
					EMIT3(0x8B,
					      add_2reg(0x40, IA32_EBP,
						       IA32_EBX),
					      STACK_VAR(src_hi));
			पूर्ण
			/* and dreg_lo,sreg_lo */
			EMIT2(0x23, add_2reg(0xC0, sreg_lo, dreg_lo));
			अगर (is_jmp64) अणु
				/* and dreg_hi,sreg_hi */
				EMIT2(0x23, add_2reg(0xC0, sreg_hi, dreg_hi));
				/* or dreg_lo,dreg_hi */
				EMIT2(0x09, add_2reg(0xC0, dreg_lo, dreg_hi));
			पूर्ण
			जाओ emit_cond_jmp;
		पूर्ण
		हाल BPF_JMP | BPF_JSET | BPF_K:
		हाल BPF_JMP32 | BPF_JSET | BPF_K: अणु
			bool is_jmp64 = BPF_CLASS(insn->code) == BPF_JMP;
			u8 dreg_lo = IA32_EAX;
			u8 dreg_hi = IA32_EDX;
			u8 sreg_lo = IA32_ECX;
			u8 sreg_hi = IA32_EBX;
			u32 hi;

			अगर (dstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(dst_lo));
				अगर (is_jmp64)
					EMIT3(0x8B,
					      add_2reg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAR(dst_hi));
			पूर्ण अन्यथा अणु
				/* mov dreg_lo,dst_lo */
				EMIT2(0x89, add_2reg(0xC0, dreg_lo, dst_lo));
				अगर (is_jmp64)
					/* mov dreg_hi,dst_hi */
					EMIT2(0x89,
					      add_2reg(0xC0, dreg_hi, dst_hi));
			पूर्ण

			/* mov ecx,imm32 */
			EMIT2_off32(0xC7, add_1reg(0xC0, sreg_lo), imm32);

			/* and dreg_lo,sreg_lo */
			EMIT2(0x23, add_2reg(0xC0, sreg_lo, dreg_lo));
			अगर (is_jmp64) अणु
				hi = imm32 & (1 << 31) ? (u32)~0 : 0;
				/* mov ebx,imm32 */
				EMIT2_off32(0xC7, add_1reg(0xC0, sreg_hi), hi);
				/* and dreg_hi,sreg_hi */
				EMIT2(0x23, add_2reg(0xC0, sreg_hi, dreg_hi));
				/* or dreg_lo,dreg_hi */
				EMIT2(0x09, add_2reg(0xC0, dreg_lo, dreg_hi));
			पूर्ण
			जाओ emit_cond_jmp;
		पूर्ण
		हाल BPF_JMP | BPF_JEQ | BPF_K:
		हाल BPF_JMP | BPF_JNE | BPF_K:
		हाल BPF_JMP | BPF_JGT | BPF_K:
		हाल BPF_JMP | BPF_JLT | BPF_K:
		हाल BPF_JMP | BPF_JGE | BPF_K:
		हाल BPF_JMP | BPF_JLE | BPF_K:
		हाल BPF_JMP32 | BPF_JEQ | BPF_K:
		हाल BPF_JMP32 | BPF_JNE | BPF_K:
		हाल BPF_JMP32 | BPF_JGT | BPF_K:
		हाल BPF_JMP32 | BPF_JLT | BPF_K:
		हाल BPF_JMP32 | BPF_JGE | BPF_K:
		हाल BPF_JMP32 | BPF_JLE | BPF_K:
		हाल BPF_JMP32 | BPF_JSGT | BPF_K:
		हाल BPF_JMP32 | BPF_JSLE | BPF_K:
		हाल BPF_JMP32 | BPF_JSLT | BPF_K:
		हाल BPF_JMP32 | BPF_JSGE | BPF_K: अणु
			bool is_jmp64 = BPF_CLASS(insn->code) == BPF_JMP;
			u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
			u8 dreg_hi = dstk ? IA32_EDX : dst_hi;
			u8 sreg_lo = IA32_ECX;
			u8 sreg_hi = IA32_EBX;
			u32 hi;

			अगर (dstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(dst_lo));
				अगर (is_jmp64)
					EMIT3(0x8B,
					      add_2reg(0x40, IA32_EBP,
						       IA32_EDX),
					      STACK_VAR(dst_hi));
			पूर्ण

			/* mov ecx,imm32 */
			EMIT2_off32(0xC7, add_1reg(0xC0, IA32_ECX), imm32);
			अगर (is_jmp64) अणु
				hi = imm32 & (1 << 31) ? (u32)~0 : 0;
				/* mov ebx,imm32 */
				EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EBX), hi);
				/* cmp dreg_hi,sreg_hi */
				EMIT2(0x39, add_2reg(0xC0, dreg_hi, sreg_hi));
				EMIT2(IA32_JNE, 2);
			पूर्ण
			/* cmp dreg_lo,sreg_lo */
			EMIT2(0x39, add_2reg(0xC0, dreg_lo, sreg_lo));

emit_cond_jmp:		jmp_cond = get_cond_jmp_opcode(BPF_OP(code), false);
			अगर (jmp_cond == COND_JMP_OPCODE_INVALID)
				वापस -EFAULT;
			jmp_offset = addrs[i + insn->off] - addrs[i];
			अगर (is_imm8(jmp_offset)) अणु
				EMIT2(jmp_cond, jmp_offset);
			पूर्ण अन्यथा अगर (is_simm32(jmp_offset)) अणु
				EMIT2_off32(0x0F, jmp_cond + 0x10, jmp_offset);
			पूर्ण अन्यथा अणु
				pr_err("cond_jmp gen bug %llx\n", jmp_offset);
				वापस -EFAULT;
			पूर्ण
			अवरोध;
		पूर्ण
		हाल BPF_JMP | BPF_JSGT | BPF_K:
		हाल BPF_JMP | BPF_JSLE | BPF_K:
		हाल BPF_JMP | BPF_JSLT | BPF_K:
		हाल BPF_JMP | BPF_JSGE | BPF_K: अणु
			u8 dreg_lo = dstk ? IA32_EAX : dst_lo;
			u8 dreg_hi = dstk ? IA32_EDX : dst_hi;
			u8 sreg_lo = IA32_ECX;
			u8 sreg_hi = IA32_EBX;
			u32 hi;

			अगर (dstk) अणु
				EMIT3(0x8B, add_2reg(0x40, IA32_EBP, IA32_EAX),
				      STACK_VAR(dst_lo));
				EMIT3(0x8B,
				      add_2reg(0x40, IA32_EBP,
					       IA32_EDX),
				      STACK_VAR(dst_hi));
			पूर्ण

			/* mov ecx,imm32 */
			EMIT2_off32(0xC7, add_1reg(0xC0, IA32_ECX), imm32);
			hi = imm32 & (1 << 31) ? (u32)~0 : 0;
			/* mov ebx,imm32 */
			EMIT2_off32(0xC7, add_1reg(0xC0, IA32_EBX), hi);
			/* cmp dreg_hi,sreg_hi */
			EMIT2(0x39, add_2reg(0xC0, dreg_hi, sreg_hi));
			EMIT2(IA32_JNE, 10);
			/* cmp dreg_lo,sreg_lo */
			EMIT2(0x39, add_2reg(0xC0, dreg_lo, sreg_lo));

			/*
			 * For simplicity of branch offset computation,
			 * let's use fixed jump coding here.
			 */
emit_cond_jmp_चिन्हित:	/* Check the condition क्रम low 32-bit comparison */
			jmp_cond = get_cond_jmp_opcode(BPF_OP(code), true);
			अगर (jmp_cond == COND_JMP_OPCODE_INVALID)
				वापस -EFAULT;
			jmp_offset = addrs[i + insn->off] - addrs[i] + 8;
			अगर (is_simm32(jmp_offset)) अणु
				EMIT2_off32(0x0F, jmp_cond + 0x10, jmp_offset);
			पूर्ण अन्यथा अणु
				pr_err("cond_jmp gen bug %llx\n", jmp_offset);
				वापस -EFAULT;
			पूर्ण
			EMIT2(0xEB, 6);

			/* Check the condition क्रम high 32-bit comparison */
			jmp_cond = get_cond_jmp_opcode(BPF_OP(code), false);
			अगर (jmp_cond == COND_JMP_OPCODE_INVALID)
				वापस -EFAULT;
			jmp_offset = addrs[i + insn->off] - addrs[i];
			अगर (is_simm32(jmp_offset)) अणु
				EMIT2_off32(0x0F, jmp_cond + 0x10, jmp_offset);
			पूर्ण अन्यथा अणु
				pr_err("cond_jmp gen bug %llx\n", jmp_offset);
				वापस -EFAULT;
			पूर्ण
			अवरोध;
		पूर्ण
		हाल BPF_JMP | BPF_JA:
			अगर (insn->off == -1)
				/* -1 jmp inकाष्ठाions will always jump
				 * backwards two bytes. Explicitly handling
				 * this हाल aव्योमs wasting too many passes
				 * when there are दीर्घ sequences of replaced
				 * dead code.
				 */
				jmp_offset = -2;
			अन्यथा
				jmp_offset = addrs[i + insn->off] - addrs[i];

			अगर (!jmp_offset)
				/* Optimize out nop jumps */
				अवरोध;
emit_jmp:
			अगर (is_imm8(jmp_offset)) अणु
				EMIT2(0xEB, jmp_offset);
			पूर्ण अन्यथा अगर (is_simm32(jmp_offset)) अणु
				EMIT1_off32(0xE9, jmp_offset);
			पूर्ण अन्यथा अणु
				pr_err("jmp gen bug %llx\n", jmp_offset);
				वापस -EFAULT;
			पूर्ण
			अवरोध;
		हाल BPF_STX | BPF_ATOMIC | BPF_W:
		हाल BPF_STX | BPF_ATOMIC | BPF_DW:
			जाओ notyet;
		हाल BPF_JMP | BPF_EXIT:
			अगर (seen_निकास) अणु
				jmp_offset = ctx->cleanup_addr - addrs[i];
				जाओ emit_jmp;
			पूर्ण
			seen_निकास = true;
			/* Update cleanup_addr */
			ctx->cleanup_addr = proglen;
			emit_epilogue(&prog, bpf_prog->aux->stack_depth);
			अवरोध;
notyet:
			pr_info_once("*** NOT YET: opcode %02x ***\n", code);
			वापस -EFAULT;
		शेष:
			/*
			 * This error will be seen अगर new inकाष्ठाion was added
			 * to पूर्णांकerpreter, but not to JIT or अगर there is junk in
			 * bpf_prog
			 */
			pr_err("bpf_jit: unknown opcode %02x\n", code);
			वापस -EINVAL;
		पूर्ण

		ilen = prog - temp;
		अगर (ilen > BPF_MAX_INSN_SIZE) अणु
			pr_err("bpf_jit: fatal insn size error\n");
			वापस -EFAULT;
		पूर्ण

		अगर (image) अणु
			/*
			 * When populating the image, निश्चित that:
			 *
			 *  i) We करो not ग_लिखो beyond the allocated space, and
			 * ii) addrs[i] did not change from the prior run, in order
			 *     to validate assumptions made क्रम computing branch
			 *     displacements.
			 */
			अगर (unlikely(proglen + ilen > oldproglen ||
				     proglen + ilen != addrs[i])) अणु
				pr_err("bpf_jit: fatal error\n");
				वापस -EFAULT;
			पूर्ण
			स_नकल(image + proglen, temp, ilen);
		पूर्ण
		proglen += ilen;
		addrs[i] = proglen;
		prog = temp;
	पूर्ण
	वापस proglen;
पूर्ण

bool bpf_jit_needs_zext(व्योम)
अणु
	वापस true;
पूर्ण

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_binary_header *header = शून्य;
	काष्ठा bpf_prog *पंचांगp, *orig_prog = prog;
	पूर्णांक proglen, oldproglen = 0;
	काष्ठा jit_context ctx = अणुपूर्ण;
	bool पंचांगp_blinded = false;
	u8 *image = शून्य;
	पूर्णांक *addrs;
	पूर्णांक pass;
	पूर्णांक i;

	अगर (!prog->jit_requested)
		वापस orig_prog;

	पंचांगp = bpf_jit_blind_स्थिरants(prog);
	/*
	 * If blinding was requested and we failed during blinding,
	 * we must fall back to the पूर्णांकerpreter.
	 */
	अगर (IS_ERR(पंचांगp))
		वापस orig_prog;
	अगर (पंचांगp != prog) अणु
		पंचांगp_blinded = true;
		prog = पंचांगp;
	पूर्ण

	addrs = kदो_स्मृति_array(prog->len, माप(*addrs), GFP_KERNEL);
	अगर (!addrs) अणु
		prog = orig_prog;
		जाओ out;
	पूर्ण

	/*
	 * Beक्रमe first pass, make a rough estimation of addrs[]
	 * each BPF inकाष्ठाion is translated to less than 64 bytes
	 */
	क्रम (proglen = 0, i = 0; i < prog->len; i++) अणु
		proglen += 64;
		addrs[i] = proglen;
	पूर्ण
	ctx.cleanup_addr = proglen;

	/*
	 * JITed image shrinks with every pass and the loop iterates
	 * until the image stops shrinking. Very large BPF programs
	 * may converge on the last pass. In such हाल करो one more
	 * pass to emit the final image.
	 */
	क्रम (pass = 0; pass < 20 || image; pass++) अणु
		proglen = करो_jit(prog, addrs, image, oldproglen, &ctx);
		अगर (proglen <= 0) अणु
out_image:
			image = शून्य;
			अगर (header)
				bpf_jit_binary_मुक्त(header);
			prog = orig_prog;
			जाओ out_addrs;
		पूर्ण
		अगर (image) अणु
			अगर (proglen != oldproglen) अणु
				pr_err("bpf_jit: proglen=%d != oldproglen=%d\n",
				       proglen, oldproglen);
				जाओ out_image;
			पूर्ण
			अवरोध;
		पूर्ण
		अगर (proglen == oldproglen) अणु
			header = bpf_jit_binary_alloc(proglen, &image,
						      1, jit_fill_hole);
			अगर (!header) अणु
				prog = orig_prog;
				जाओ out_addrs;
			पूर्ण
		पूर्ण
		oldproglen = proglen;
		cond_resched();
	पूर्ण

	अगर (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, proglen, pass + 1, image);

	अगर (image) अणु
		bpf_jit_binary_lock_ro(header);
		prog->bpf_func = (व्योम *)image;
		prog->jited = 1;
		prog->jited_len = proglen;
	पूर्ण अन्यथा अणु
		prog = orig_prog;
	पूर्ण

out_addrs:
	kमुक्त(addrs);
out:
	अगर (पंचांगp_blinded)
		bpf_jit_prog_release_other(prog, prog == orig_prog ?
					   पंचांगp : orig_prog);
	वापस prog;
पूर्ण

bool bpf_jit_supports_kfunc_call(व्योम)
अणु
	वापस true;
पूर्ण
