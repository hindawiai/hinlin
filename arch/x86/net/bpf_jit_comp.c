<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * bpf_jit_comp.c: BPF JIT compiler
 *
 * Copyright (C) 2011-2013 Eric Dumazet (eric.dumazet@gmail.com)
 * Internal BPF Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 */
#समावेश <linux/netdevice.h>
#समावेश <linux/filter.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/bpf.h>
#समावेश <linux/memory.h>
#समावेश <linux/sort.h>
#समावेश <यंत्र/extable.h>
#समावेश <यंत्र/set_memory.h>
#समावेश <यंत्र/nospec-branch.h>
#समावेश <यंत्र/text-patching.h>
#समावेश <यंत्र/यंत्र-prototypes.h>

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
#घोषणा EMIT4(b1, b2, b3, b4)   EMIT((b1) + ((b2) << 8) + ((b3) << 16) + ((b4) << 24), 4)

#घोषणा EMIT1_off32(b1, off) \
	करो अणु EMIT1(b1); EMIT(off, 4); पूर्ण जबतक (0)
#घोषणा EMIT2_off32(b1, b2, off) \
	करो अणु EMIT2(b1, b2); EMIT(off, 4); पूर्ण जबतक (0)
#घोषणा EMIT3_off32(b1, b2, b3, off) \
	करो अणु EMIT3(b1, b2, b3); EMIT(off, 4); पूर्ण जबतक (0)
#घोषणा EMIT4_off32(b1, b2, b3, b4, off) \
	करो अणु EMIT4(b1, b2, b3, b4); EMIT(off, 4); पूर्ण जबतक (0)

अटल bool is_imm8(पूर्णांक value)
अणु
	वापस value <= 127 && value >= -128;
पूर्ण

अटल bool is_simm32(s64 value)
अणु
	वापस value == (s64)(s32)value;
पूर्ण

अटल bool is_uimm32(u64 value)
अणु
	वापस value == (u64)(u32)value;
पूर्ण

/* mov dst, src */
#घोषणा EMIT_mov(DST, SRC)								 \
	करो अणु										 \
		अगर (DST != SRC)								 \
			EMIT3(add_2mod(0x48, DST, SRC), 0x89, add_2reg(0xC0, DST, SRC)); \
	पूर्ण जबतक (0)

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

/*
 * List of x86 cond jumps opcodes (. + s8)
 * Add 0x10 (and an extra 0x0f) to generate far jumps (. + s32)
 */
#घोषणा X86_JB  0x72
#घोषणा X86_JAE 0x73
#घोषणा X86_JE  0x74
#घोषणा X86_JNE 0x75
#घोषणा X86_JBE 0x76
#घोषणा X86_JA  0x77
#घोषणा X86_JL  0x7C
#घोषणा X86_JGE 0x7D
#घोषणा X86_JLE 0x7E
#घोषणा X86_JG  0x7F

/* Pick a रेजिस्टर outside of BPF range क्रम JIT पूर्णांकernal work */
#घोषणा AUX_REG (MAX_BPF_JIT_REG + 1)
#घोषणा X86_REG_R9 (MAX_BPF_JIT_REG + 2)

/*
 * The following table maps BPF रेजिस्टरs to x86-64 रेजिस्टरs.
 *
 * x86-64 रेजिस्टर R12 is unused, since अगर used as base address
 * रेजिस्टर in load/store inकाष्ठाions, it always needs an
 * extra byte of encoding and is callee saved.
 *
 * x86-64 रेजिस्टर R9 is not used by BPF programs, but can be used by BPF
 * trampoline. x86-64 रेजिस्टर R10 is used क्रम blinding (अगर enabled).
 */
अटल स्थिर पूर्णांक reg2hex[] = अणु
	[BPF_REG_0] = 0,  /* RAX */
	[BPF_REG_1] = 7,  /* RDI */
	[BPF_REG_2] = 6,  /* RSI */
	[BPF_REG_3] = 2,  /* RDX */
	[BPF_REG_4] = 1,  /* RCX */
	[BPF_REG_5] = 0,  /* R8  */
	[BPF_REG_6] = 3,  /* RBX callee saved */
	[BPF_REG_7] = 5,  /* R13 callee saved */
	[BPF_REG_8] = 6,  /* R14 callee saved */
	[BPF_REG_9] = 7,  /* R15 callee saved */
	[BPF_REG_FP] = 5, /* RBP पढ़ोonly */
	[BPF_REG_AX] = 2, /* R10 temp रेजिस्टर */
	[AUX_REG] = 3,    /* R11 temp रेजिस्टर */
	[X86_REG_R9] = 1, /* R9 रेजिस्टर, 6th function argument */
पूर्ण;

अटल स्थिर पूर्णांक reg2pt_regs[] = अणु
	[BPF_REG_0] = दुरत्व(काष्ठा pt_regs, ax),
	[BPF_REG_1] = दुरत्व(काष्ठा pt_regs, di),
	[BPF_REG_2] = दुरत्व(काष्ठा pt_regs, si),
	[BPF_REG_3] = दुरत्व(काष्ठा pt_regs, dx),
	[BPF_REG_4] = दुरत्व(काष्ठा pt_regs, cx),
	[BPF_REG_5] = दुरत्व(काष्ठा pt_regs, r8),
	[BPF_REG_6] = दुरत्व(काष्ठा pt_regs, bx),
	[BPF_REG_7] = दुरत्व(काष्ठा pt_regs, r13),
	[BPF_REG_8] = दुरत्व(काष्ठा pt_regs, r14),
	[BPF_REG_9] = दुरत्व(काष्ठा pt_regs, r15),
पूर्ण;

/*
 * is_ereg() == true अगर BPF रेजिस्टर 'reg' maps to x86-64 r8..r15
 * which need extra byte of encoding.
 * rax,rcx,...,rbp have simpler encoding
 */
अटल bool is_ereg(u32 reg)
अणु
	वापस (1 << reg) & (BIT(BPF_REG_5) |
			     BIT(AUX_REG) |
			     BIT(BPF_REG_7) |
			     BIT(BPF_REG_8) |
			     BIT(BPF_REG_9) |
			     BIT(X86_REG_R9) |
			     BIT(BPF_REG_AX));
पूर्ण

/*
 * is_ereg_8l() == true अगर BPF रेजिस्टर 'reg' is mapped to access x86-64
 * lower 8-bit रेजिस्टरs dil,sil,bpl,spl,r8b..r15b, which need extra byte
 * of encoding. al,cl,dl,bl have simpler encoding.
 */
अटल bool is_ereg_8l(u32 reg)
अणु
	वापस is_ereg(reg) ||
	    (1 << reg) & (BIT(BPF_REG_1) |
			  BIT(BPF_REG_2) |
			  BIT(BPF_REG_FP));
पूर्ण

अटल bool is_axreg(u32 reg)
अणु
	वापस reg == BPF_REG_0;
पूर्ण

/* Add modअगरiers अगर 'reg' maps to x86-64 रेजिस्टरs R8..R15 */
अटल u8 add_1mod(u8 byte, u32 reg)
अणु
	अगर (is_ereg(reg))
		byte |= 1;
	वापस byte;
पूर्ण

अटल u8 add_2mod(u8 byte, u32 r1, u32 r2)
अणु
	अगर (is_ereg(r1))
		byte |= 1;
	अगर (is_ereg(r2))
		byte |= 4;
	वापस byte;
पूर्ण

/* Encode 'dst_reg' register into x86-64 opcode 'byte' */
अटल u8 add_1reg(u8 byte, u32 dst_reg)
अणु
	वापस byte + reg2hex[dst_reg];
पूर्ण

/* Encode 'dst_reg' and 'src_reg' registers into x86-64 opcode 'byte' */
अटल u8 add_2reg(u8 byte, u32 dst_reg, u32 src_reg)
अणु
	वापस byte + reg2hex[dst_reg] + (reg2hex[src_reg] << 3);
पूर्ण

/* Some 1-byte opcodes क्रम binary ALU operations */
अटल u8 simple_alu_opcodes[] = अणु
	[BPF_ADD] = 0x01,
	[BPF_SUB] = 0x29,
	[BPF_AND] = 0x21,
	[BPF_OR] = 0x09,
	[BPF_XOR] = 0x31,
	[BPF_LSH] = 0xE0,
	[BPF_RSH] = 0xE8,
	[BPF_ARSH] = 0xF8,
पूर्ण;

अटल व्योम jit_fill_hole(व्योम *area, अचिन्हित पूर्णांक size)
अणु
	/* Fill whole space with INT3 inकाष्ठाions */
	स_रखो(area, 0xcc, size);
पूर्ण

काष्ठा jit_context अणु
	पूर्णांक cleanup_addr; /* Epilogue code offset */
पूर्ण;

/* Maximum number of bytes emitted जबतक JITing one eBPF insn */
#घोषणा BPF_MAX_INSN_SIZE	128
#घोषणा BPF_INSN_SAFETY		64

/* Number of bytes emit_patch() needs to generate inकाष्ठाions */
#घोषणा X86_PATCH_SIZE		5
/* Number of bytes that will be skipped on tailcall */
#घोषणा X86_TAIL_CALL_OFFSET	11

अटल व्योम push_callee_regs(u8 **pprog, bool *callee_regs_used)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (callee_regs_used[0])
		EMIT1(0x53);         /* push rbx */
	अगर (callee_regs_used[1])
		EMIT2(0x41, 0x55);   /* push r13 */
	अगर (callee_regs_used[2])
		EMIT2(0x41, 0x56);   /* push r14 */
	अगर (callee_regs_used[3])
		EMIT2(0x41, 0x57);   /* push r15 */
	*pprog = prog;
पूर्ण

अटल व्योम pop_callee_regs(u8 **pprog, bool *callee_regs_used)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (callee_regs_used[3])
		EMIT2(0x41, 0x5F);   /* pop r15 */
	अगर (callee_regs_used[2])
		EMIT2(0x41, 0x5E);   /* pop r14 */
	अगर (callee_regs_used[1])
		EMIT2(0x41, 0x5D);   /* pop r13 */
	अगर (callee_regs_used[0])
		EMIT1(0x5B);         /* pop rbx */
	*pprog = prog;
पूर्ण

/*
 * Emit x86-64 prologue code क्रम BPF program.
 * bpf_tail_call helper will skip the first X86_TAIL_CALL_OFFSET bytes
 * जबतक jumping to another program
 */
अटल व्योम emit_prologue(u8 **pprog, u32 stack_depth, bool ebpf_from_cbpf,
			  bool tail_call_reachable, bool is_subprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = X86_PATCH_SIZE;

	/* BPF trampoline can be made to work without these nops,
	 * but let's waste 5 bytes क्रम now and optimize later
	 */
	स_नकल(prog, x86_nops[5], cnt);
	prog += cnt;
	अगर (!ebpf_from_cbpf) अणु
		अगर (tail_call_reachable && !is_subprog)
			EMIT2(0x31, 0xC0); /* xor eax, eax */
		अन्यथा
			EMIT2(0x66, 0x90); /* nop2 */
	पूर्ण
	EMIT1(0x55);             /* push rbp */
	EMIT3(0x48, 0x89, 0xE5); /* mov rbp, rsp */
	/* sub rsp, rounded_stack_depth */
	अगर (stack_depth)
		EMIT3_off32(0x48, 0x81, 0xEC, round_up(stack_depth, 8));
	अगर (tail_call_reachable)
		EMIT1(0x50);         /* push rax */
	*pprog = prog;
पूर्ण

अटल पूर्णांक emit_patch(u8 **pprog, व्योम *func, व्योम *ip, u8 opcode)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	s64 offset;

	offset = func - (ip + X86_PATCH_SIZE);
	अगर (!is_simm32(offset)) अणु
		pr_err("Target call %p is out of range\n", func);
		वापस -दुस्फल;
	पूर्ण
	EMIT1_off32(opcode, offset);
	*pprog = prog;
	वापस 0;
पूर्ण

अटल पूर्णांक emit_call(u8 **pprog, व्योम *func, व्योम *ip)
अणु
	वापस emit_patch(pprog, func, ip, 0xE8);
पूर्ण

अटल पूर्णांक emit_jump(u8 **pprog, व्योम *func, व्योम *ip)
अणु
	वापस emit_patch(pprog, func, ip, 0xE9);
पूर्ण

अटल पूर्णांक __bpf_arch_text_poke(व्योम *ip, क्रमागत bpf_text_poke_type t,
				व्योम *old_addr, व्योम *new_addr,
				स्थिर bool text_live)
अणु
	स्थिर u8 *nop_insn = x86_nops[5];
	u8 old_insn[X86_PATCH_SIZE];
	u8 new_insn[X86_PATCH_SIZE];
	u8 *prog;
	पूर्णांक ret;

	स_नकल(old_insn, nop_insn, X86_PATCH_SIZE);
	अगर (old_addr) अणु
		prog = old_insn;
		ret = t == BPF_MOD_CALL ?
		      emit_call(&prog, old_addr, ip) :
		      emit_jump(&prog, old_addr, ip);
		अगर (ret)
			वापस ret;
	पूर्ण

	स_नकल(new_insn, nop_insn, X86_PATCH_SIZE);
	अगर (new_addr) अणु
		prog = new_insn;
		ret = t == BPF_MOD_CALL ?
		      emit_call(&prog, new_addr, ip) :
		      emit_jump(&prog, new_addr, ip);
		अगर (ret)
			वापस ret;
	पूर्ण

	ret = -EBUSY;
	mutex_lock(&text_mutex);
	अगर (स_भेद(ip, old_insn, X86_PATCH_SIZE))
		जाओ out;
	ret = 1;
	अगर (स_भेद(ip, new_insn, X86_PATCH_SIZE)) अणु
		अगर (text_live)
			text_poke_bp(ip, new_insn, X86_PATCH_SIZE, शून्य);
		अन्यथा
			स_नकल(ip, new_insn, X86_PATCH_SIZE);
		ret = 0;
	पूर्ण
out:
	mutex_unlock(&text_mutex);
	वापस ret;
पूर्ण

पूर्णांक bpf_arch_text_poke(व्योम *ip, क्रमागत bpf_text_poke_type t,
		       व्योम *old_addr, व्योम *new_addr)
अणु
	अगर (!is_kernel_text((दीर्घ)ip) &&
	    !is_bpf_text_address((दीर्घ)ip))
		/* BPF poking in modules is not supported */
		वापस -EINVAL;

	वापस __bpf_arch_text_poke(ip, t, old_addr, new_addr, true);
पूर्ण

अटल पूर्णांक get_pop_bytes(bool *callee_regs_used)
अणु
	पूर्णांक bytes = 0;

	अगर (callee_regs_used[3])
		bytes += 2;
	अगर (callee_regs_used[2])
		bytes += 2;
	अगर (callee_regs_used[1])
		bytes += 2;
	अगर (callee_regs_used[0])
		bytes += 1;

	वापस bytes;
पूर्ण

/*
 * Generate the following code:
 *
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
अटल व्योम emit_bpf_tail_call_indirect(u8 **pprog, bool *callee_regs_used,
					u32 stack_depth)
अणु
	पूर्णांक tcc_off = -4 - round_up(stack_depth, 8);
	u8 *prog = *pprog;
	पूर्णांक pop_bytes = 0;
	पूर्णांक off1 = 42;
	पूर्णांक off2 = 31;
	पूर्णांक off3 = 9;
	पूर्णांक cnt = 0;

	/* count the additional bytes used क्रम popping callee regs from stack
	 * that need to be taken पूर्णांकo account क्रम each of the offsets that
	 * are used क्रम bailing out of the tail call
	 */
	pop_bytes = get_pop_bytes(callee_regs_used);
	off1 += pop_bytes;
	off2 += pop_bytes;
	off3 += pop_bytes;

	अगर (stack_depth) अणु
		off1 += 7;
		off2 += 7;
		off3 += 7;
	पूर्ण

	/*
	 * rdi - poपूर्णांकer to ctx
	 * rsi - poपूर्णांकer to bpf_array
	 * rdx - index in bpf_array
	 */

	/*
	 * अगर (index >= array->map.max_entries)
	 *	जाओ out;
	 */
	EMIT2(0x89, 0xD2);                        /* mov edx, edx */
	EMIT3(0x39, 0x56,                         /* cmp dword ptr [rsi + 16], edx */
	      दुरत्व(काष्ठा bpf_array, map.max_entries));
#घोषणा OFFSET1 (off1 + RETPOLINE_RCX_BPF_JIT_SIZE) /* Number of bytes to jump */
	EMIT2(X86_JBE, OFFSET1);                  /* jbe out */

	/*
	 * अगर (tail_call_cnt > MAX_TAIL_CALL_CNT)
	 *	जाओ out;
	 */
	EMIT2_off32(0x8B, 0x85, tcc_off);         /* mov eax, dword ptr [rbp - tcc_off] */
	EMIT3(0x83, 0xF8, MAX_TAIL_CALL_CNT);     /* cmp eax, MAX_TAIL_CALL_CNT */
#घोषणा OFFSET2 (off2 + RETPOLINE_RCX_BPF_JIT_SIZE)
	EMIT2(X86_JA, OFFSET2);                   /* ja out */
	EMIT3(0x83, 0xC0, 0x01);                  /* add eax, 1 */
	EMIT2_off32(0x89, 0x85, tcc_off);         /* mov dword ptr [rbp - tcc_off], eax */

	/* prog = array->ptrs[index]; */
	EMIT4_off32(0x48, 0x8B, 0x8C, 0xD6,       /* mov rcx, [rsi + rdx * 8 + दुरत्व(...)] */
		    दुरत्व(काष्ठा bpf_array, ptrs));

	/*
	 * अगर (prog == शून्य)
	 *	जाओ out;
	 */
	EMIT3(0x48, 0x85, 0xC9);                  /* test rcx,rcx */
#घोषणा OFFSET3 (off3 + RETPOLINE_RCX_BPF_JIT_SIZE)
	EMIT2(X86_JE, OFFSET3);                   /* je out */

	*pprog = prog;
	pop_callee_regs(pprog, callee_regs_used);
	prog = *pprog;

	EMIT1(0x58);                              /* pop rax */
	अगर (stack_depth)
		EMIT3_off32(0x48, 0x81, 0xC4,     /* add rsp, sd */
			    round_up(stack_depth, 8));

	/* जाओ *(prog->bpf_func + X86_TAIL_CALL_OFFSET); */
	EMIT4(0x48, 0x8B, 0x49,                   /* mov rcx, qword ptr [rcx + 32] */
	      दुरत्व(काष्ठा bpf_prog, bpf_func));
	EMIT4(0x48, 0x83, 0xC1,                   /* add rcx, X86_TAIL_CALL_OFFSET */
	      X86_TAIL_CALL_OFFSET);
	/*
	 * Now we're पढ़ोy to jump पूर्णांकo next BPF program
	 * rdi == ctx (1st arg)
	 * rcx == prog->bpf_func + X86_TAIL_CALL_OFFSET
	 */
	RETPOLINE_RCX_BPF_JIT();

	/* out: */
	*pprog = prog;
पूर्ण

अटल व्योम emit_bpf_tail_call_direct(काष्ठा bpf_jit_poke_descriptor *poke,
				      u8 **pprog, पूर्णांक addr, u8 *image,
				      bool *callee_regs_used, u32 stack_depth)
अणु
	पूर्णांक tcc_off = -4 - round_up(stack_depth, 8);
	u8 *prog = *pprog;
	पूर्णांक pop_bytes = 0;
	पूर्णांक off1 = 20;
	पूर्णांक poke_off;
	पूर्णांक cnt = 0;

	/* count the additional bytes used क्रम popping callee regs to stack
	 * that need to be taken पूर्णांकo account क्रम jump offset that is used क्रम
	 * bailing out from of the tail call when limit is reached
	 */
	pop_bytes = get_pop_bytes(callee_regs_used);
	off1 += pop_bytes;

	/*
	 * total bytes क्रम:
	 * - nop5/ jmpq $off
	 * - pop callee regs
	 * - sub rsp, $val अगर depth > 0
	 * - pop rax
	 */
	poke_off = X86_PATCH_SIZE + pop_bytes + 1;
	अगर (stack_depth) अणु
		poke_off += 7;
		off1 += 7;
	पूर्ण

	/*
	 * अगर (tail_call_cnt > MAX_TAIL_CALL_CNT)
	 *	जाओ out;
	 */
	EMIT2_off32(0x8B, 0x85, tcc_off);             /* mov eax, dword ptr [rbp - tcc_off] */
	EMIT3(0x83, 0xF8, MAX_TAIL_CALL_CNT);         /* cmp eax, MAX_TAIL_CALL_CNT */
	EMIT2(X86_JA, off1);                          /* ja out */
	EMIT3(0x83, 0xC0, 0x01);                      /* add eax, 1 */
	EMIT2_off32(0x89, 0x85, tcc_off);             /* mov dword ptr [rbp - tcc_off], eax */

	poke->tailcall_bypass = image + (addr - poke_off - X86_PATCH_SIZE);
	poke->adj_off = X86_TAIL_CALL_OFFSET;
	poke->tailcall_target = image + (addr - X86_PATCH_SIZE);
	poke->bypass_addr = (u8 *)poke->tailcall_target + X86_PATCH_SIZE;

	emit_jump(&prog, (u8 *)poke->tailcall_target + X86_PATCH_SIZE,
		  poke->tailcall_bypass);

	*pprog = prog;
	pop_callee_regs(pprog, callee_regs_used);
	prog = *pprog;
	EMIT1(0x58);                                  /* pop rax */
	अगर (stack_depth)
		EMIT3_off32(0x48, 0x81, 0xC4, round_up(stack_depth, 8));

	स_नकल(prog, x86_nops[5], X86_PATCH_SIZE);
	prog += X86_PATCH_SIZE;
	/* out: */

	*pprog = prog;
पूर्ण

अटल व्योम bpf_tail_call_direct_fixup(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_jit_poke_descriptor *poke;
	काष्ठा bpf_array *array;
	काष्ठा bpf_prog *target;
	पूर्णांक i, ret;

	क्रम (i = 0; i < prog->aux->size_poke_tab; i++) अणु
		poke = &prog->aux->poke_tab[i];
		WARN_ON_ONCE(READ_ONCE(poke->tailcall_target_stable));

		अगर (poke->reason != BPF_POKE_REASON_TAIL_CALL)
			जारी;

		array = container_of(poke->tail_call.map, काष्ठा bpf_array, map);
		mutex_lock(&array->aux->poke_mutex);
		target = array->ptrs[poke->tail_call.key];
		अगर (target) अणु
			/* Plain स_नकल is used when image is not live yet
			 * and still not locked as पढ़ो-only. Once poke
			 * location is active (poke->tailcall_target_stable),
			 * any parallel bpf_arch_text_poke() might occur
			 * still on the पढ़ो-ग_लिखो image until we finally
			 * locked it as पढ़ो-only. Both modअगरications on
			 * the given image are under text_mutex to aव्योम
			 * पूर्णांकerference.
			 */
			ret = __bpf_arch_text_poke(poke->tailcall_target,
						   BPF_MOD_JUMP, शून्य,
						   (u8 *)target->bpf_func +
						   poke->adj_off, false);
			BUG_ON(ret < 0);
			ret = __bpf_arch_text_poke(poke->tailcall_bypass,
						   BPF_MOD_JUMP,
						   (u8 *)poke->tailcall_target +
						   X86_PATCH_SIZE, शून्य, false);
			BUG_ON(ret < 0);
		पूर्ण
		WRITE_ONCE(poke->tailcall_target_stable, true);
		mutex_unlock(&array->aux->poke_mutex);
	पूर्ण
पूर्ण

अटल व्योम emit_mov_imm32(u8 **pprog, bool sign_propagate,
			   u32 dst_reg, स्थिर u32 imm32)
अणु
	u8 *prog = *pprog;
	u8 b1, b2, b3;
	पूर्णांक cnt = 0;

	/*
	 * Optimization: अगर imm32 is positive, use 'mov %eax, imm32'
	 * (which zero-extends imm32) to save 2 bytes.
	 */
	अगर (sign_propagate && (s32)imm32 < 0) अणु
		/* 'mov %rax, imm32' sign extends imm32 */
		b1 = add_1mod(0x48, dst_reg);
		b2 = 0xC7;
		b3 = 0xC0;
		EMIT3_off32(b1, b2, add_1reg(b3, dst_reg), imm32);
		जाओ करोne;
	पूर्ण

	/*
	 * Optimization: अगर imm32 is zero, use 'xor %eax, %eax'
	 * to save 3 bytes.
	 */
	अगर (imm32 == 0) अणु
		अगर (is_ereg(dst_reg))
			EMIT1(add_2mod(0x40, dst_reg, dst_reg));
		b2 = 0x31; /* xor */
		b3 = 0xC0;
		EMIT2(b2, add_2reg(b3, dst_reg, dst_reg));
		जाओ करोne;
	पूर्ण

	/* mov %eax, imm32 */
	अगर (is_ereg(dst_reg))
		EMIT1(add_1mod(0x40, dst_reg));
	EMIT1_off32(add_1reg(0xB8, dst_reg), imm32);
करोne:
	*pprog = prog;
पूर्ण

अटल व्योम emit_mov_imm64(u8 **pprog, u32 dst_reg,
			   स्थिर u32 imm32_hi, स्थिर u32 imm32_lo)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (is_uimm32(((u64)imm32_hi << 32) | (u32)imm32_lo)) अणु
		/*
		 * For emitting plain u32, where sign bit must not be
		 * propagated LLVM tends to load imm64 over mov32
		 * directly, so save couple of bytes by just करोing
		 * 'mov %eax, imm32' instead.
		 */
		emit_mov_imm32(&prog, false, dst_reg, imm32_lo);
	पूर्ण अन्यथा अणु
		/* movअसलq %rax, imm64 */
		EMIT2(add_1mod(0x48, dst_reg), add_1reg(0xB8, dst_reg));
		EMIT(imm32_lo, 4);
		EMIT(imm32_hi, 4);
	पूर्ण

	*pprog = prog;
पूर्ण

अटल व्योम emit_mov_reg(u8 **pprog, bool is64, u32 dst_reg, u32 src_reg)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (is64) अणु
		/* mov dst, src */
		EMIT_mov(dst_reg, src_reg);
	पूर्ण अन्यथा अणु
		/* mov32 dst, src */
		अगर (is_ereg(dst_reg) || is_ereg(src_reg))
			EMIT1(add_2mod(0x40, dst_reg, src_reg));
		EMIT2(0x89, add_2reg(0xC0, dst_reg, src_reg));
	पूर्ण

	*pprog = prog;
पूर्ण

/* Emit the suffix (ModR/M etc) क्रम addressing *(ptr_reg + off) and val_reg */
अटल व्योम emit_insn_suffix(u8 **pprog, u32 ptr_reg, u32 val_reg, पूर्णांक off)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (is_imm8(off)) अणु
		/* 1-byte चिन्हित displacement.
		 *
		 * If off == 0 we could skip this and save one extra byte, but
		 * special हाल of x86 R13 which always needs an offset is not
		 * worth the hassle
		 */
		EMIT2(add_2reg(0x40, ptr_reg, val_reg), off);
	पूर्ण अन्यथा अणु
		/* 4-byte चिन्हित displacement */
		EMIT1_off32(add_2reg(0x80, ptr_reg, val_reg), off);
	पूर्ण
	*pprog = prog;
पूर्ण

/*
 * Emit a REX byte अगर it will be necessary to address these रेजिस्टरs
 */
अटल व्योम maybe_emit_mod(u8 **pprog, u32 dst_reg, u32 src_reg, bool is64)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	अगर (is64)
		EMIT1(add_2mod(0x48, dst_reg, src_reg));
	अन्यथा अगर (is_ereg(dst_reg) || is_ereg(src_reg))
		EMIT1(add_2mod(0x40, dst_reg, src_reg));
	*pprog = prog;
पूर्ण

/* LDX: dst_reg = *(u8*)(src_reg + off) */
अटल व्योम emit_ldx(u8 **pprog, u32 size, u32 dst_reg, u32 src_reg, पूर्णांक off)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	चयन (size) अणु
	हाल BPF_B:
		/* Emit 'movzx rax, byte ptr [rax + off]' */
		EMIT3(add_2mod(0x48, src_reg, dst_reg), 0x0F, 0xB6);
		अवरोध;
	हाल BPF_H:
		/* Emit 'movzx rax, word ptr [rax + off]' */
		EMIT3(add_2mod(0x48, src_reg, dst_reg), 0x0F, 0xB7);
		अवरोध;
	हाल BPF_W:
		/* Emit 'mov eax, dword ptr [rax+0x14]' */
		अगर (is_ereg(dst_reg) || is_ereg(src_reg))
			EMIT2(add_2mod(0x40, src_reg, dst_reg), 0x8B);
		अन्यथा
			EMIT1(0x8B);
		अवरोध;
	हाल BPF_DW:
		/* Emit 'mov rax, qword ptr [rax+0x14]' */
		EMIT2(add_2mod(0x48, src_reg, dst_reg), 0x8B);
		अवरोध;
	पूर्ण
	emit_insn_suffix(&prog, src_reg, dst_reg, off);
	*pprog = prog;
पूर्ण

/* STX: *(u8*)(dst_reg + off) = src_reg */
अटल व्योम emit_stx(u8 **pprog, u32 size, u32 dst_reg, u32 src_reg, पूर्णांक off)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	चयन (size) अणु
	हाल BPF_B:
		/* Emit 'mov byte ptr [rax + off], al' */
		अगर (is_ereg(dst_reg) || is_ereg_8l(src_reg))
			/* Add extra byte क्रम eregs or SIL,DIL,BPL in src_reg */
			EMIT2(add_2mod(0x40, dst_reg, src_reg), 0x88);
		अन्यथा
			EMIT1(0x88);
		अवरोध;
	हाल BPF_H:
		अगर (is_ereg(dst_reg) || is_ereg(src_reg))
			EMIT3(0x66, add_2mod(0x40, dst_reg, src_reg), 0x89);
		अन्यथा
			EMIT2(0x66, 0x89);
		अवरोध;
	हाल BPF_W:
		अगर (is_ereg(dst_reg) || is_ereg(src_reg))
			EMIT2(add_2mod(0x40, dst_reg, src_reg), 0x89);
		अन्यथा
			EMIT1(0x89);
		अवरोध;
	हाल BPF_DW:
		EMIT2(add_2mod(0x48, dst_reg, src_reg), 0x89);
		अवरोध;
	पूर्ण
	emit_insn_suffix(&prog, dst_reg, src_reg, off);
	*pprog = prog;
पूर्ण

अटल पूर्णांक emit_atomic(u8 **pprog, u8 atomic_op,
		       u32 dst_reg, u32 src_reg, s16 off, u8 bpf_size)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;

	EMIT1(0xF0); /* lock prefix */

	maybe_emit_mod(&prog, dst_reg, src_reg, bpf_size == BPF_DW);

	/* emit opcode */
	चयन (atomic_op) अणु
	हाल BPF_ADD:
	हाल BPF_SUB:
	हाल BPF_AND:
	हाल BPF_OR:
	हाल BPF_XOR:
		/* lock *(u32/u64*)(dst_reg + off) <op>= src_reg */
		EMIT1(simple_alu_opcodes[atomic_op]);
		अवरोध;
	हाल BPF_ADD | BPF_FETCH:
		/* src_reg = atomic_fetch_add(dst_reg + off, src_reg); */
		EMIT2(0x0F, 0xC1);
		अवरोध;
	हाल BPF_XCHG:
		/* src_reg = atomic_xchg(dst_reg + off, src_reg); */
		EMIT1(0x87);
		अवरोध;
	हाल BPF_CMPXCHG:
		/* r0 = atomic_cmpxchg(dst_reg + off, r0, src_reg); */
		EMIT2(0x0F, 0xB1);
		अवरोध;
	शेष:
		pr_err("bpf_jit: unknown atomic opcode %02x\n", atomic_op);
		वापस -EFAULT;
	पूर्ण

	emit_insn_suffix(&prog, dst_reg, src_reg, off);

	*pprog = prog;
	वापस 0;
पूर्ण

अटल bool ex_handler_bpf(स्थिर काष्ठा exception_table_entry *x,
			   काष्ठा pt_regs *regs, पूर्णांक trapnr,
			   अचिन्हित दीर्घ error_code, अचिन्हित दीर्घ fault_addr)
अणु
	u32 reg = x->fixup >> 8;

	/* jump over faulting load and clear dest रेजिस्टर */
	*(अचिन्हित दीर्घ *)((व्योम *)regs + reg) = 0;
	regs->ip += x->fixup & 0xff;
	वापस true;
पूर्ण

अटल व्योम detect_reg_usage(काष्ठा bpf_insn *insn, पूर्णांक insn_cnt,
			     bool *regs_used, bool *tail_call_seen)
अणु
	पूर्णांक i;

	क्रम (i = 1; i <= insn_cnt; i++, insn++) अणु
		अगर (insn->code == (BPF_JMP | BPF_TAIL_CALL))
			*tail_call_seen = true;
		अगर (insn->dst_reg == BPF_REG_6 || insn->src_reg == BPF_REG_6)
			regs_used[0] = true;
		अगर (insn->dst_reg == BPF_REG_7 || insn->src_reg == BPF_REG_7)
			regs_used[1] = true;
		अगर (insn->dst_reg == BPF_REG_8 || insn->src_reg == BPF_REG_8)
			regs_used[2] = true;
		अगर (insn->dst_reg == BPF_REG_9 || insn->src_reg == BPF_REG_9)
			regs_used[3] = true;
	पूर्ण
पूर्ण

अटल पूर्णांक emit_nops(u8 **pprog, पूर्णांक len)
अणु
	u8 *prog = *pprog;
	पूर्णांक i, noplen, cnt = 0;

	जबतक (len > 0) अणु
		noplen = len;

		अगर (noplen > ASM_NOP_MAX)
			noplen = ASM_NOP_MAX;

		क्रम (i = 0; i < noplen; i++)
			EMIT1(x86_nops[noplen][i]);
		len -= noplen;
	पूर्ण

	*pprog = prog;

	वापस cnt;
पूर्ण

#घोषणा INSN_SZ_DIFF (((addrs[i] - addrs[i - 1]) - (prog - temp)))

अटल पूर्णांक करो_jit(काष्ठा bpf_prog *bpf_prog, पूर्णांक *addrs, u8 *image,
		  पूर्णांक oldproglen, काष्ठा jit_context *ctx, bool jmp_padding)
अणु
	bool tail_call_reachable = bpf_prog->aux->tail_call_reachable;
	काष्ठा bpf_insn *insn = bpf_prog->insnsi;
	bool callee_regs_used[4] = अणुपूर्ण;
	पूर्णांक insn_cnt = bpf_prog->len;
	bool tail_call_seen = false;
	bool seen_निकास = false;
	u8 temp[BPF_MAX_INSN_SIZE + BPF_INSN_SAFETY];
	पूर्णांक i, cnt = 0, excnt = 0;
	पूर्णांक ilen, proglen = 0;
	u8 *prog = temp;
	पूर्णांक err;

	detect_reg_usage(insn, insn_cnt, callee_regs_used,
			 &tail_call_seen);

	/* tail call's presence in current prog implies it is reachable */
	tail_call_reachable |= tail_call_seen;

	emit_prologue(&prog, bpf_prog->aux->stack_depth,
		      bpf_prog_was_classic(bpf_prog), tail_call_reachable,
		      bpf_prog->aux->func_idx != 0);
	push_callee_regs(&prog, callee_regs_used);

	ilen = prog - temp;
	अगर (image)
		स_नकल(image + proglen, temp, ilen);
	proglen += ilen;
	addrs[0] = proglen;
	prog = temp;

	क्रम (i = 1; i <= insn_cnt; i++, insn++) अणु
		स्थिर s32 imm32 = insn->imm;
		u32 dst_reg = insn->dst_reg;
		u32 src_reg = insn->src_reg;
		u8 b2 = 0, b3 = 0;
		u8 *start_of_ldx;
		s64 jmp_offset;
		u8 jmp_cond;
		u8 *func;
		पूर्णांक nops;

		चयन (insn->code) अणु
			/* ALU */
		हाल BPF_ALU | BPF_ADD | BPF_X:
		हाल BPF_ALU | BPF_SUB | BPF_X:
		हाल BPF_ALU | BPF_AND | BPF_X:
		हाल BPF_ALU | BPF_OR | BPF_X:
		हाल BPF_ALU | BPF_XOR | BPF_X:
		हाल BPF_ALU64 | BPF_ADD | BPF_X:
		हाल BPF_ALU64 | BPF_SUB | BPF_X:
		हाल BPF_ALU64 | BPF_AND | BPF_X:
		हाल BPF_ALU64 | BPF_OR | BPF_X:
		हाल BPF_ALU64 | BPF_XOR | BPF_X:
			maybe_emit_mod(&prog, dst_reg, src_reg,
				       BPF_CLASS(insn->code) == BPF_ALU64);
			b2 = simple_alu_opcodes[BPF_OP(insn->code)];
			EMIT2(b2, add_2reg(0xC0, dst_reg, src_reg));
			अवरोध;

		हाल BPF_ALU64 | BPF_MOV | BPF_X:
		हाल BPF_ALU | BPF_MOV | BPF_X:
			emit_mov_reg(&prog,
				     BPF_CLASS(insn->code) == BPF_ALU64,
				     dst_reg, src_reg);
			अवरोध;

			/* neg dst */
		हाल BPF_ALU | BPF_NEG:
		हाल BPF_ALU64 | BPF_NEG:
			अगर (BPF_CLASS(insn->code) == BPF_ALU64)
				EMIT1(add_1mod(0x48, dst_reg));
			अन्यथा अगर (is_ereg(dst_reg))
				EMIT1(add_1mod(0x40, dst_reg));
			EMIT2(0xF7, add_1reg(0xD8, dst_reg));
			अवरोध;

		हाल BPF_ALU | BPF_ADD | BPF_K:
		हाल BPF_ALU | BPF_SUB | BPF_K:
		हाल BPF_ALU | BPF_AND | BPF_K:
		हाल BPF_ALU | BPF_OR | BPF_K:
		हाल BPF_ALU | BPF_XOR | BPF_K:
		हाल BPF_ALU64 | BPF_ADD | BPF_K:
		हाल BPF_ALU64 | BPF_SUB | BPF_K:
		हाल BPF_ALU64 | BPF_AND | BPF_K:
		हाल BPF_ALU64 | BPF_OR | BPF_K:
		हाल BPF_ALU64 | BPF_XOR | BPF_K:
			अगर (BPF_CLASS(insn->code) == BPF_ALU64)
				EMIT1(add_1mod(0x48, dst_reg));
			अन्यथा अगर (is_ereg(dst_reg))
				EMIT1(add_1mod(0x40, dst_reg));

			/*
			 * b3 holds 'normal' opcode, b2 लघु क्रमm only valid
			 * in हाल dst is eax/rax.
			 */
			चयन (BPF_OP(insn->code)) अणु
			हाल BPF_ADD:
				b3 = 0xC0;
				b2 = 0x05;
				अवरोध;
			हाल BPF_SUB:
				b3 = 0xE8;
				b2 = 0x2D;
				अवरोध;
			हाल BPF_AND:
				b3 = 0xE0;
				b2 = 0x25;
				अवरोध;
			हाल BPF_OR:
				b3 = 0xC8;
				b2 = 0x0D;
				अवरोध;
			हाल BPF_XOR:
				b3 = 0xF0;
				b2 = 0x35;
				अवरोध;
			पूर्ण

			अगर (is_imm8(imm32))
				EMIT3(0x83, add_1reg(b3, dst_reg), imm32);
			अन्यथा अगर (is_axreg(dst_reg))
				EMIT1_off32(b2, imm32);
			अन्यथा
				EMIT2_off32(0x81, add_1reg(b3, dst_reg), imm32);
			अवरोध;

		हाल BPF_ALU64 | BPF_MOV | BPF_K:
		हाल BPF_ALU | BPF_MOV | BPF_K:
			emit_mov_imm32(&prog, BPF_CLASS(insn->code) == BPF_ALU64,
				       dst_reg, imm32);
			अवरोध;

		हाल BPF_LD | BPF_IMM | BPF_DW:
			emit_mov_imm64(&prog, dst_reg, insn[1].imm, insn[0].imm);
			insn++;
			i++;
			अवरोध;

			/* dst %= src, dst /= src, dst %= imm32, dst /= imm32 */
		हाल BPF_ALU | BPF_MOD | BPF_X:
		हाल BPF_ALU | BPF_DIV | BPF_X:
		हाल BPF_ALU | BPF_MOD | BPF_K:
		हाल BPF_ALU | BPF_DIV | BPF_K:
		हाल BPF_ALU64 | BPF_MOD | BPF_X:
		हाल BPF_ALU64 | BPF_DIV | BPF_X:
		हाल BPF_ALU64 | BPF_MOD | BPF_K:
		हाल BPF_ALU64 | BPF_DIV | BPF_K:
			EMIT1(0x50); /* push rax */
			EMIT1(0x52); /* push rdx */

			अगर (BPF_SRC(insn->code) == BPF_X)
				/* mov r11, src_reg */
				EMIT_mov(AUX_REG, src_reg);
			अन्यथा
				/* mov r11, imm32 */
				EMIT3_off32(0x49, 0xC7, 0xC3, imm32);

			/* mov rax, dst_reg */
			EMIT_mov(BPF_REG_0, dst_reg);

			/*
			 * xor edx, edx
			 * equivalent to 'xor rdx, rdx', but one byte less
			 */
			EMIT2(0x31, 0xd2);

			अगर (BPF_CLASS(insn->code) == BPF_ALU64)
				/* भाग r11 */
				EMIT3(0x49, 0xF7, 0xF3);
			अन्यथा
				/* भाग r11d */
				EMIT3(0x41, 0xF7, 0xF3);

			अगर (BPF_OP(insn->code) == BPF_MOD)
				/* mov r11, rdx */
				EMIT3(0x49, 0x89, 0xD3);
			अन्यथा
				/* mov r11, rax */
				EMIT3(0x49, 0x89, 0xC3);

			EMIT1(0x5A); /* pop rdx */
			EMIT1(0x58); /* pop rax */

			/* mov dst_reg, r11 */
			EMIT_mov(dst_reg, AUX_REG);
			अवरोध;

		हाल BPF_ALU | BPF_MUL | BPF_K:
		हाल BPF_ALU | BPF_MUL | BPF_X:
		हाल BPF_ALU64 | BPF_MUL | BPF_K:
		हाल BPF_ALU64 | BPF_MUL | BPF_X:
		अणु
			bool is64 = BPF_CLASS(insn->code) == BPF_ALU64;

			अगर (dst_reg != BPF_REG_0)
				EMIT1(0x50); /* push rax */
			अगर (dst_reg != BPF_REG_3)
				EMIT1(0x52); /* push rdx */

			/* mov r11, dst_reg */
			EMIT_mov(AUX_REG, dst_reg);

			अगर (BPF_SRC(insn->code) == BPF_X)
				emit_mov_reg(&prog, is64, BPF_REG_0, src_reg);
			अन्यथा
				emit_mov_imm32(&prog, is64, BPF_REG_0, imm32);

			अगर (is64)
				EMIT1(add_1mod(0x48, AUX_REG));
			अन्यथा अगर (is_ereg(AUX_REG))
				EMIT1(add_1mod(0x40, AUX_REG));
			/* mul(q) r11 */
			EMIT2(0xF7, add_1reg(0xE0, AUX_REG));

			अगर (dst_reg != BPF_REG_3)
				EMIT1(0x5A); /* pop rdx */
			अगर (dst_reg != BPF_REG_0) अणु
				/* mov dst_reg, rax */
				EMIT_mov(dst_reg, BPF_REG_0);
				EMIT1(0x58); /* pop rax */
			पूर्ण
			अवरोध;
		पूर्ण
			/* Shअगरts */
		हाल BPF_ALU | BPF_LSH | BPF_K:
		हाल BPF_ALU | BPF_RSH | BPF_K:
		हाल BPF_ALU | BPF_ARSH | BPF_K:
		हाल BPF_ALU64 | BPF_LSH | BPF_K:
		हाल BPF_ALU64 | BPF_RSH | BPF_K:
		हाल BPF_ALU64 | BPF_ARSH | BPF_K:
			अगर (BPF_CLASS(insn->code) == BPF_ALU64)
				EMIT1(add_1mod(0x48, dst_reg));
			अन्यथा अगर (is_ereg(dst_reg))
				EMIT1(add_1mod(0x40, dst_reg));

			b3 = simple_alu_opcodes[BPF_OP(insn->code)];
			अगर (imm32 == 1)
				EMIT2(0xD1, add_1reg(b3, dst_reg));
			अन्यथा
				EMIT3(0xC1, add_1reg(b3, dst_reg), imm32);
			अवरोध;

		हाल BPF_ALU | BPF_LSH | BPF_X:
		हाल BPF_ALU | BPF_RSH | BPF_X:
		हाल BPF_ALU | BPF_ARSH | BPF_X:
		हाल BPF_ALU64 | BPF_LSH | BPF_X:
		हाल BPF_ALU64 | BPF_RSH | BPF_X:
		हाल BPF_ALU64 | BPF_ARSH | BPF_X:

			/* Check क्रम bad हाल when dst_reg == rcx */
			अगर (dst_reg == BPF_REG_4) अणु
				/* mov r11, dst_reg */
				EMIT_mov(AUX_REG, dst_reg);
				dst_reg = AUX_REG;
			पूर्ण

			अगर (src_reg != BPF_REG_4) अणु /* common हाल */
				EMIT1(0x51); /* push rcx */

				/* mov rcx, src_reg */
				EMIT_mov(BPF_REG_4, src_reg);
			पूर्ण

			/* shl %rax, %cl | shr %rax, %cl | sar %rax, %cl */
			अगर (BPF_CLASS(insn->code) == BPF_ALU64)
				EMIT1(add_1mod(0x48, dst_reg));
			अन्यथा अगर (is_ereg(dst_reg))
				EMIT1(add_1mod(0x40, dst_reg));

			b3 = simple_alu_opcodes[BPF_OP(insn->code)];
			EMIT2(0xD3, add_1reg(b3, dst_reg));

			अगर (src_reg != BPF_REG_4)
				EMIT1(0x59); /* pop rcx */

			अगर (insn->dst_reg == BPF_REG_4)
				/* mov dst_reg, r11 */
				EMIT_mov(insn->dst_reg, AUX_REG);
			अवरोध;

		हाल BPF_ALU | BPF_END | BPF_FROM_BE:
			चयन (imm32) अणु
			हाल 16:
				/* Emit 'ror %ax, 8' to swap lower 2 bytes */
				EMIT1(0x66);
				अगर (is_ereg(dst_reg))
					EMIT1(0x41);
				EMIT3(0xC1, add_1reg(0xC8, dst_reg), 8);

				/* Emit 'movzwl eax, ax' */
				अगर (is_ereg(dst_reg))
					EMIT3(0x45, 0x0F, 0xB7);
				अन्यथा
					EMIT2(0x0F, 0xB7);
				EMIT1(add_2reg(0xC0, dst_reg, dst_reg));
				अवरोध;
			हाल 32:
				/* Emit 'bswap eax' to swap lower 4 bytes */
				अगर (is_ereg(dst_reg))
					EMIT2(0x41, 0x0F);
				अन्यथा
					EMIT1(0x0F);
				EMIT1(add_1reg(0xC8, dst_reg));
				अवरोध;
			हाल 64:
				/* Emit 'bswap rax' to swap 8 bytes */
				EMIT3(add_1mod(0x48, dst_reg), 0x0F,
				      add_1reg(0xC8, dst_reg));
				अवरोध;
			पूर्ण
			अवरोध;

		हाल BPF_ALU | BPF_END | BPF_FROM_LE:
			चयन (imm32) अणु
			हाल 16:
				/*
				 * Emit 'movzwl eax, ax' to zero extend 16-bit
				 * पूर्णांकo 64 bit
				 */
				अगर (is_ereg(dst_reg))
					EMIT3(0x45, 0x0F, 0xB7);
				अन्यथा
					EMIT2(0x0F, 0xB7);
				EMIT1(add_2reg(0xC0, dst_reg, dst_reg));
				अवरोध;
			हाल 32:
				/* Emit 'mov eax, eax' to clear upper 32-bits */
				अगर (is_ereg(dst_reg))
					EMIT1(0x45);
				EMIT2(0x89, add_2reg(0xC0, dst_reg, dst_reg));
				अवरोध;
			हाल 64:
				/* nop */
				अवरोध;
			पूर्ण
			अवरोध;

			/* ST: *(u8*)(dst_reg + off) = imm */
		हाल BPF_ST | BPF_MEM | BPF_B:
			अगर (is_ereg(dst_reg))
				EMIT2(0x41, 0xC6);
			अन्यथा
				EMIT1(0xC6);
			जाओ st;
		हाल BPF_ST | BPF_MEM | BPF_H:
			अगर (is_ereg(dst_reg))
				EMIT3(0x66, 0x41, 0xC7);
			अन्यथा
				EMIT2(0x66, 0xC7);
			जाओ st;
		हाल BPF_ST | BPF_MEM | BPF_W:
			अगर (is_ereg(dst_reg))
				EMIT2(0x41, 0xC7);
			अन्यथा
				EMIT1(0xC7);
			जाओ st;
		हाल BPF_ST | BPF_MEM | BPF_DW:
			EMIT2(add_1mod(0x48, dst_reg), 0xC7);

st:			अगर (is_imm8(insn->off))
				EMIT2(add_1reg(0x40, dst_reg), insn->off);
			अन्यथा
				EMIT1_off32(add_1reg(0x80, dst_reg), insn->off);

			EMIT(imm32, bpf_माप_प्रकारo_x86_bytes(BPF_SIZE(insn->code)));
			अवरोध;

			/* STX: *(u8*)(dst_reg + off) = src_reg */
		हाल BPF_STX | BPF_MEM | BPF_B:
		हाल BPF_STX | BPF_MEM | BPF_H:
		हाल BPF_STX | BPF_MEM | BPF_W:
		हाल BPF_STX | BPF_MEM | BPF_DW:
			emit_stx(&prog, BPF_SIZE(insn->code), dst_reg, src_reg, insn->off);
			अवरोध;

			/* LDX: dst_reg = *(u8*)(src_reg + off) */
		हाल BPF_LDX | BPF_MEM | BPF_B:
		हाल BPF_LDX | BPF_PROBE_MEM | BPF_B:
		हाल BPF_LDX | BPF_MEM | BPF_H:
		हाल BPF_LDX | BPF_PROBE_MEM | BPF_H:
		हाल BPF_LDX | BPF_MEM | BPF_W:
		हाल BPF_LDX | BPF_PROBE_MEM | BPF_W:
		हाल BPF_LDX | BPF_MEM | BPF_DW:
		हाल BPF_LDX | BPF_PROBE_MEM | BPF_DW:
			अगर (BPF_MODE(insn->code) == BPF_PROBE_MEM) अणु
				/* test src_reg, src_reg */
				maybe_emit_mod(&prog, src_reg, src_reg, true); /* always 1 byte */
				EMIT2(0x85, add_2reg(0xC0, src_reg, src_reg));
				/* jne start_of_ldx */
				EMIT2(X86_JNE, 0);
				/* xor dst_reg, dst_reg */
				emit_mov_imm32(&prog, false, dst_reg, 0);
				/* jmp byte_after_ldx */
				EMIT2(0xEB, 0);

				/* populate jmp_offset क्रम JNE above */
				temp[4] = prog - temp - 5 /* माप(test + jne) */;
				start_of_ldx = prog;
			पूर्ण
			emit_ldx(&prog, BPF_SIZE(insn->code), dst_reg, src_reg, insn->off);
			अगर (BPF_MODE(insn->code) == BPF_PROBE_MEM) अणु
				काष्ठा exception_table_entry *ex;
				u8 *_insn = image + proglen;
				s64 delta;

				/* populate jmp_offset क्रम JMP above */
				start_of_ldx[-1] = prog - start_of_ldx;

				अगर (!bpf_prog->aux->extable)
					अवरोध;

				अगर (excnt >= bpf_prog->aux->num_exentries) अणु
					pr_err("ex gen bug\n");
					वापस -EFAULT;
				पूर्ण
				ex = &bpf_prog->aux->extable[excnt++];

				delta = _insn - (u8 *)&ex->insn;
				अगर (!is_simm32(delta)) अणु
					pr_err("extable->insn doesn't fit into 32-bit\n");
					वापस -EFAULT;
				पूर्ण
				ex->insn = delta;

				delta = (u8 *)ex_handler_bpf - (u8 *)&ex->handler;
				अगर (!is_simm32(delta)) अणु
					pr_err("extable->handler doesn't fit into 32-bit\n");
					वापस -EFAULT;
				पूर्ण
				ex->handler = delta;

				अगर (dst_reg > BPF_REG_9) अणु
					pr_err("verifier error\n");
					वापस -EFAULT;
				पूर्ण
				/*
				 * Compute size of x86 insn and its target dest x86 रेजिस्टर.
				 * ex_handler_bpf() will use lower 8 bits to adjust
				 * pt_regs->ip to jump over this x86 inकाष्ठाion
				 * and upper bits to figure out which pt_regs to zero out.
				 * End result: x86 insn "mov rbx, qword ptr [rax+0x14]"
				 * of 4 bytes will be ignored and rbx will be zero inited.
				 */
				ex->fixup = (prog - temp) | (reg2pt_regs[dst_reg] << 8);
			पूर्ण
			अवरोध;

		हाल BPF_STX | BPF_ATOMIC | BPF_W:
		हाल BPF_STX | BPF_ATOMIC | BPF_DW:
			अगर (insn->imm == (BPF_AND | BPF_FETCH) ||
			    insn->imm == (BPF_OR | BPF_FETCH) ||
			    insn->imm == (BPF_XOR | BPF_FETCH)) अणु
				u8 *branch_target;
				bool is64 = BPF_SIZE(insn->code) == BPF_DW;
				u32 real_src_reg = src_reg;

				/*
				 * Can't be implemented with a single x86 insn.
				 * Need to करो a CMPXCHG loop.
				 */

				/* Will need RAX as a CMPXCHG opeअक्रम so save R0 */
				emit_mov_reg(&prog, true, BPF_REG_AX, BPF_REG_0);
				अगर (src_reg == BPF_REG_0)
					real_src_reg = BPF_REG_AX;

				branch_target = prog;
				/* Load old value */
				emit_ldx(&prog, BPF_SIZE(insn->code),
					 BPF_REG_0, dst_reg, insn->off);
				/*
				 * Perक्रमm the (commutative) operation locally,
				 * put the result in the AUX_REG.
				 */
				emit_mov_reg(&prog, is64, AUX_REG, BPF_REG_0);
				maybe_emit_mod(&prog, AUX_REG, real_src_reg, is64);
				EMIT2(simple_alu_opcodes[BPF_OP(insn->imm)],
				      add_2reg(0xC0, AUX_REG, real_src_reg));
				/* Attempt to swap in new value */
				err = emit_atomic(&prog, BPF_CMPXCHG,
						  dst_reg, AUX_REG, insn->off,
						  BPF_SIZE(insn->code));
				अगर (WARN_ON(err))
					वापस err;
				/*
				 * ZF tells us whether we won the race. If it's
				 * cleared we need to try again.
				 */
				EMIT2(X86_JNE, -(prog - branch_target) - 2);
				/* Return the pre-modअगरication value */
				emit_mov_reg(&prog, is64, real_src_reg, BPF_REG_0);
				/* Restore R0 after clobbering RAX */
				emit_mov_reg(&prog, true, BPF_REG_0, BPF_REG_AX);
				अवरोध;

			पूर्ण

			err = emit_atomic(&prog, insn->imm, dst_reg, src_reg,
						  insn->off, BPF_SIZE(insn->code));
			अगर (err)
				वापस err;
			अवरोध;

			/* call */
		हाल BPF_JMP | BPF_CALL:
			func = (u8 *) __bpf_call_base + imm32;
			अगर (tail_call_reachable) अणु
				EMIT3_off32(0x48, 0x8B, 0x85,
					    -(bpf_prog->aux->stack_depth + 8));
				अगर (!imm32 || emit_call(&prog, func, image + addrs[i - 1] + 7))
					वापस -EINVAL;
			पूर्ण अन्यथा अणु
				अगर (!imm32 || emit_call(&prog, func, image + addrs[i - 1]))
					वापस -EINVAL;
			पूर्ण
			अवरोध;

		हाल BPF_JMP | BPF_TAIL_CALL:
			अगर (imm32)
				emit_bpf_tail_call_direct(&bpf_prog->aux->poke_tab[imm32 - 1],
							  &prog, addrs[i], image,
							  callee_regs_used,
							  bpf_prog->aux->stack_depth);
			अन्यथा
				emit_bpf_tail_call_indirect(&prog,
							    callee_regs_used,
							    bpf_prog->aux->stack_depth);
			अवरोध;

			/* cond jump */
		हाल BPF_JMP | BPF_JEQ | BPF_X:
		हाल BPF_JMP | BPF_JNE | BPF_X:
		हाल BPF_JMP | BPF_JGT | BPF_X:
		हाल BPF_JMP | BPF_JLT | BPF_X:
		हाल BPF_JMP | BPF_JGE | BPF_X:
		हाल BPF_JMP | BPF_JLE | BPF_X:
		हाल BPF_JMP | BPF_JSGT | BPF_X:
		हाल BPF_JMP | BPF_JSLT | BPF_X:
		हाल BPF_JMP | BPF_JSGE | BPF_X:
		हाल BPF_JMP | BPF_JSLE | BPF_X:
		हाल BPF_JMP32 | BPF_JEQ | BPF_X:
		हाल BPF_JMP32 | BPF_JNE | BPF_X:
		हाल BPF_JMP32 | BPF_JGT | BPF_X:
		हाल BPF_JMP32 | BPF_JLT | BPF_X:
		हाल BPF_JMP32 | BPF_JGE | BPF_X:
		हाल BPF_JMP32 | BPF_JLE | BPF_X:
		हाल BPF_JMP32 | BPF_JSGT | BPF_X:
		हाल BPF_JMP32 | BPF_JSLT | BPF_X:
		हाल BPF_JMP32 | BPF_JSGE | BPF_X:
		हाल BPF_JMP32 | BPF_JSLE | BPF_X:
			/* cmp dst_reg, src_reg */
			maybe_emit_mod(&prog, dst_reg, src_reg,
				       BPF_CLASS(insn->code) == BPF_JMP);
			EMIT2(0x39, add_2reg(0xC0, dst_reg, src_reg));
			जाओ emit_cond_jmp;

		हाल BPF_JMP | BPF_JSET | BPF_X:
		हाल BPF_JMP32 | BPF_JSET | BPF_X:
			/* test dst_reg, src_reg */
			maybe_emit_mod(&prog, dst_reg, src_reg,
				       BPF_CLASS(insn->code) == BPF_JMP);
			EMIT2(0x85, add_2reg(0xC0, dst_reg, src_reg));
			जाओ emit_cond_jmp;

		हाल BPF_JMP | BPF_JSET | BPF_K:
		हाल BPF_JMP32 | BPF_JSET | BPF_K:
			/* test dst_reg, imm32 */
			अगर (BPF_CLASS(insn->code) == BPF_JMP)
				EMIT1(add_1mod(0x48, dst_reg));
			अन्यथा अगर (is_ereg(dst_reg))
				EMIT1(add_1mod(0x40, dst_reg));
			EMIT2_off32(0xF7, add_1reg(0xC0, dst_reg), imm32);
			जाओ emit_cond_jmp;

		हाल BPF_JMP | BPF_JEQ | BPF_K:
		हाल BPF_JMP | BPF_JNE | BPF_K:
		हाल BPF_JMP | BPF_JGT | BPF_K:
		हाल BPF_JMP | BPF_JLT | BPF_K:
		हाल BPF_JMP | BPF_JGE | BPF_K:
		हाल BPF_JMP | BPF_JLE | BPF_K:
		हाल BPF_JMP | BPF_JSGT | BPF_K:
		हाल BPF_JMP | BPF_JSLT | BPF_K:
		हाल BPF_JMP | BPF_JSGE | BPF_K:
		हाल BPF_JMP | BPF_JSLE | BPF_K:
		हाल BPF_JMP32 | BPF_JEQ | BPF_K:
		हाल BPF_JMP32 | BPF_JNE | BPF_K:
		हाल BPF_JMP32 | BPF_JGT | BPF_K:
		हाल BPF_JMP32 | BPF_JLT | BPF_K:
		हाल BPF_JMP32 | BPF_JGE | BPF_K:
		हाल BPF_JMP32 | BPF_JLE | BPF_K:
		हाल BPF_JMP32 | BPF_JSGT | BPF_K:
		हाल BPF_JMP32 | BPF_JSLT | BPF_K:
		हाल BPF_JMP32 | BPF_JSGE | BPF_K:
		हाल BPF_JMP32 | BPF_JSLE | BPF_K:
			/* test dst_reg, dst_reg to save one extra byte */
			अगर (imm32 == 0) अणु
				maybe_emit_mod(&prog, dst_reg, dst_reg,
					       BPF_CLASS(insn->code) == BPF_JMP);
				EMIT2(0x85, add_2reg(0xC0, dst_reg, dst_reg));
				जाओ emit_cond_jmp;
			पूर्ण

			/* cmp dst_reg, imm8/32 */
			अगर (BPF_CLASS(insn->code) == BPF_JMP)
				EMIT1(add_1mod(0x48, dst_reg));
			अन्यथा अगर (is_ereg(dst_reg))
				EMIT1(add_1mod(0x40, dst_reg));

			अगर (is_imm8(imm32))
				EMIT3(0x83, add_1reg(0xF8, dst_reg), imm32);
			अन्यथा
				EMIT2_off32(0x81, add_1reg(0xF8, dst_reg), imm32);

emit_cond_jmp:		/* Convert BPF opcode to x86 */
			चयन (BPF_OP(insn->code)) अणु
			हाल BPF_JEQ:
				jmp_cond = X86_JE;
				अवरोध;
			हाल BPF_JSET:
			हाल BPF_JNE:
				jmp_cond = X86_JNE;
				अवरोध;
			हाल BPF_JGT:
				/* GT is अचिन्हित '>', JA in x86 */
				jmp_cond = X86_JA;
				अवरोध;
			हाल BPF_JLT:
				/* LT is अचिन्हित '<', JB in x86 */
				jmp_cond = X86_JB;
				अवरोध;
			हाल BPF_JGE:
				/* GE is अचिन्हित '>=', JAE in x86 */
				jmp_cond = X86_JAE;
				अवरोध;
			हाल BPF_JLE:
				/* LE is अचिन्हित '<=', JBE in x86 */
				jmp_cond = X86_JBE;
				अवरोध;
			हाल BPF_JSGT:
				/* Signed '>', GT in x86 */
				jmp_cond = X86_JG;
				अवरोध;
			हाल BPF_JSLT:
				/* Signed '<', LT in x86 */
				jmp_cond = X86_JL;
				अवरोध;
			हाल BPF_JSGE:
				/* Signed '>=', GE in x86 */
				jmp_cond = X86_JGE;
				अवरोध;
			हाल BPF_JSLE:
				/* Signed '<=', LE in x86 */
				jmp_cond = X86_JLE;
				अवरोध;
			शेष: /* to silence GCC warning */
				वापस -EFAULT;
			पूर्ण
			jmp_offset = addrs[i + insn->off] - addrs[i];
			अगर (is_imm8(jmp_offset)) अणु
				अगर (jmp_padding) अणु
					/* To keep the jmp_offset valid, the extra bytes are
					 * padded beक्रमe the jump insn, so we subtract the
					 * 2 bytes of jmp_cond insn from INSN_SZ_DIFF.
					 *
					 * If the previous pass alपढ़ोy emits an imm8
					 * jmp_cond, then this BPF insn won't shrink, so
					 * "nops" is 0.
					 *
					 * On the other hand, अगर the previous pass emits an
					 * imm32 jmp_cond, the extra 4 bytes(*) is padded to
					 * keep the image from shrinking further.
					 *
					 * (*) imm32 jmp_cond is 6 bytes, and imm8 jmp_cond
					 *     is 2 bytes, so the size dअगरference is 4 bytes.
					 */
					nops = INSN_SZ_DIFF - 2;
					अगर (nops != 0 && nops != 4) अणु
						pr_err("unexpected jmp_cond padding: %d bytes\n",
						       nops);
						वापस -EFAULT;
					पूर्ण
					cnt += emit_nops(&prog, nops);
				पूर्ण
				EMIT2(jmp_cond, jmp_offset);
			पूर्ण अन्यथा अगर (is_simm32(jmp_offset)) अणु
				EMIT2_off32(0x0F, jmp_cond + 0x10, jmp_offset);
			पूर्ण अन्यथा अणु
				pr_err("cond_jmp gen bug %llx\n", jmp_offset);
				वापस -EFAULT;
			पूर्ण

			अवरोध;

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

			अगर (!jmp_offset) अणु
				/*
				 * If jmp_padding is enabled, the extra nops will
				 * be inserted. Otherwise, optimize out nop jumps.
				 */
				अगर (jmp_padding) अणु
					/* There are 3 possible conditions.
					 * (1) This BPF_JA is alपढ़ोy optimized out in
					 *     the previous run, so there is no need
					 *     to pad any extra byte (0 byte).
					 * (2) The previous pass emits an imm8 jmp,
					 *     so we pad 2 bytes to match the previous
					 *     insn size.
					 * (3) Similarly, the previous pass emits an
					 *     imm32 jmp, and 5 bytes is padded.
					 */
					nops = INSN_SZ_DIFF;
					अगर (nops != 0 && nops != 2 && nops != 5) अणु
						pr_err("unexpected nop jump padding: %d bytes\n",
						       nops);
						वापस -EFAULT;
					पूर्ण
					cnt += emit_nops(&prog, nops);
				पूर्ण
				अवरोध;
			पूर्ण
emit_jmp:
			अगर (is_imm8(jmp_offset)) अणु
				अगर (jmp_padding) अणु
					/* To aव्योम अवरोधing jmp_offset, the extra bytes
					 * are padded beक्रमe the actual jmp insn, so
					 * 2 bytes is subtracted from INSN_SZ_DIFF.
					 *
					 * If the previous pass alपढ़ोy emits an imm8
					 * jmp, there is nothing to pad (0 byte).
					 *
					 * If it emits an imm32 jmp (5 bytes) previously
					 * and now an imm8 jmp (2 bytes), then we pad
					 * (5 - 2 = 3) bytes to stop the image from
					 * shrinking further.
					 */
					nops = INSN_SZ_DIFF - 2;
					अगर (nops != 0 && nops != 3) अणु
						pr_err("unexpected jump padding: %d bytes\n",
						       nops);
						वापस -EFAULT;
					पूर्ण
					cnt += emit_nops(&prog, INSN_SZ_DIFF - 2);
				पूर्ण
				EMIT2(0xEB, jmp_offset);
			पूर्ण अन्यथा अगर (is_simm32(jmp_offset)) अणु
				EMIT1_off32(0xE9, jmp_offset);
			पूर्ण अन्यथा अणु
				pr_err("jmp gen bug %llx\n", jmp_offset);
				वापस -EFAULT;
			पूर्ण
			अवरोध;

		हाल BPF_JMP | BPF_EXIT:
			अगर (seen_निकास) अणु
				jmp_offset = ctx->cleanup_addr - addrs[i];
				जाओ emit_jmp;
			पूर्ण
			seen_निकास = true;
			/* Update cleanup_addr */
			ctx->cleanup_addr = proglen;
			pop_callee_regs(&prog, callee_regs_used);
			EMIT1(0xC9);         /* leave */
			EMIT1(0xC3);         /* ret */
			अवरोध;

		शेष:
			/*
			 * By design x86-64 JIT should support all BPF inकाष्ठाions.
			 * This error will be seen अगर new inकाष्ठाion was added
			 * to the पूर्णांकerpreter, but not to the JIT, or अगर there is
			 * junk in bpf_prog.
			 */
			pr_err("bpf_jit: unknown opcode %02x\n", insn->code);
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

	अगर (image && excnt != bpf_prog->aux->num_exentries) अणु
		pr_err("extable is not populated\n");
		वापस -EFAULT;
	पूर्ण
	वापस proglen;
पूर्ण

अटल व्योम save_regs(स्थिर काष्ठा btf_func_model *m, u8 **prog, पूर्णांक nr_args,
		      पूर्णांक stack_size)
अणु
	पूर्णांक i;
	/* Store function arguments to stack.
	 * For a function that accepts two poपूर्णांकers the sequence will be:
	 * mov QWORD PTR [rbp-0x10],rdi
	 * mov QWORD PTR [rbp-0x8],rsi
	 */
	क्रम (i = 0; i < min(nr_args, 6); i++)
		emit_stx(prog, bytes_to_bpf_size(m->arg_size[i]),
			 BPF_REG_FP,
			 i == 5 ? X86_REG_R9 : BPF_REG_1 + i,
			 -(stack_size - i * 8));
पूर्ण

अटल व्योम restore_regs(स्थिर काष्ठा btf_func_model *m, u8 **prog, पूर्णांक nr_args,
			 पूर्णांक stack_size)
अणु
	पूर्णांक i;

	/* Restore function arguments from stack.
	 * For a function that accepts two poपूर्णांकers the sequence will be:
	 * EMIT4(0x48, 0x8B, 0x7D, 0xF0); mov rdi,QWORD PTR [rbp-0x10]
	 * EMIT4(0x48, 0x8B, 0x75, 0xF8); mov rsi,QWORD PTR [rbp-0x8]
	 */
	क्रम (i = 0; i < min(nr_args, 6); i++)
		emit_ldx(prog, bytes_to_bpf_size(m->arg_size[i]),
			 i == 5 ? X86_REG_R9 : BPF_REG_1 + i,
			 BPF_REG_FP,
			 -(stack_size - i * 8));
पूर्ण

अटल पूर्णांक invoke_bpf_prog(स्थिर काष्ठा btf_func_model *m, u8 **pprog,
			   काष्ठा bpf_prog *p, पूर्णांक stack_size, bool mod_ret)
अणु
	u8 *prog = *pprog;
	u8 *jmp_insn;
	पूर्णांक cnt = 0;

	/* arg1: mov rdi, progs[i] */
	emit_mov_imm64(&prog, BPF_REG_1, (दीर्घ) p >> 32, (u32) (दीर्घ) p);
	अगर (emit_call(&prog,
		      p->aux->sleepable ? __bpf_prog_enter_sleepable :
		      __bpf_prog_enter, prog))
			वापस -EINVAL;
	/* remember prog start समय वापसed by __bpf_prog_enter */
	emit_mov_reg(&prog, true, BPF_REG_6, BPF_REG_0);

	/* अगर (__bpf_prog_enter*(prog) == 0)
	 *	जाओ skip_exec_of_prog;
	 */
	EMIT3(0x48, 0x85, 0xC0);  /* test rax,rax */
	/* emit 2 nops that will be replaced with JE insn */
	jmp_insn = prog;
	emit_nops(&prog, 2);

	/* arg1: lea rdi, [rbp - stack_size] */
	EMIT4(0x48, 0x8D, 0x7D, -stack_size);
	/* arg2: progs[i]->insnsi क्रम पूर्णांकerpreter */
	अगर (!p->jited)
		emit_mov_imm64(&prog, BPF_REG_2,
			       (दीर्घ) p->insnsi >> 32,
			       (u32) (दीर्घ) p->insnsi);
	/* call JITed bpf program or पूर्णांकerpreter */
	अगर (emit_call(&prog, p->bpf_func, prog))
		वापस -EINVAL;

	/* BPF_TRAMP_MODIFY_RETURN trampolines can modअगरy the वापस
	 * of the previous call which is then passed on the stack to
	 * the next BPF program.
	 */
	अगर (mod_ret)
		emit_stx(&prog, BPF_DW, BPF_REG_FP, BPF_REG_0, -8);

	/* replace 2 nops with JE insn, since jmp target is known */
	jmp_insn[0] = X86_JE;
	jmp_insn[1] = prog - jmp_insn - 2;

	/* arg1: mov rdi, progs[i] */
	emit_mov_imm64(&prog, BPF_REG_1, (दीर्घ) p >> 32, (u32) (दीर्घ) p);
	/* arg2: mov rsi, rbx <- start समय in nsec */
	emit_mov_reg(&prog, true, BPF_REG_2, BPF_REG_6);
	अगर (emit_call(&prog,
		      p->aux->sleepable ? __bpf_prog_निकास_sleepable :
		      __bpf_prog_निकास, prog))
			वापस -EINVAL;

	*pprog = prog;
	वापस 0;
पूर्ण

अटल व्योम emit_align(u8 **pprog, u32 align)
अणु
	u8 *target, *prog = *pprog;

	target = PTR_ALIGN(prog, align);
	अगर (target != prog)
		emit_nops(&prog, target - prog);

	*pprog = prog;
पूर्ण

अटल पूर्णांक emit_cond_near_jump(u8 **pprog, व्योम *func, व्योम *ip, u8 jmp_cond)
अणु
	u8 *prog = *pprog;
	पूर्णांक cnt = 0;
	s64 offset;

	offset = func - (ip + 2 + 4);
	अगर (!is_simm32(offset)) अणु
		pr_err("Target %p is out of range\n", func);
		वापस -EINVAL;
	पूर्ण
	EMIT2_off32(0x0F, jmp_cond + 0x10, offset);
	*pprog = prog;
	वापस 0;
पूर्ण

अटल पूर्णांक invoke_bpf(स्थिर काष्ठा btf_func_model *m, u8 **pprog,
		      काष्ठा bpf_tramp_progs *tp, पूर्णांक stack_size)
अणु
	पूर्णांक i;
	u8 *prog = *pprog;

	क्रम (i = 0; i < tp->nr_progs; i++) अणु
		अगर (invoke_bpf_prog(m, &prog, tp->progs[i], stack_size, false))
			वापस -EINVAL;
	पूर्ण
	*pprog = prog;
	वापस 0;
पूर्ण

अटल पूर्णांक invoke_bpf_mod_ret(स्थिर काष्ठा btf_func_model *m, u8 **pprog,
			      काष्ठा bpf_tramp_progs *tp, पूर्णांक stack_size,
			      u8 **branches)
अणु
	u8 *prog = *pprog;
	पूर्णांक i, cnt = 0;

	/* The first भ_शेष_ret program will receive a garbage वापस value.
	 * Set this to 0 to aव्योम confusing the program.
	 */
	emit_mov_imm32(&prog, false, BPF_REG_0, 0);
	emit_stx(&prog, BPF_DW, BPF_REG_FP, BPF_REG_0, -8);
	क्रम (i = 0; i < tp->nr_progs; i++) अणु
		अगर (invoke_bpf_prog(m, &prog, tp->progs[i], stack_size, true))
			वापस -EINVAL;

		/* mod_ret prog stored वापस value पूर्णांकo [rbp - 8]. Emit:
		 * अगर (*(u64 *)(rbp - 8) !=  0)
		 *	जाओ करो_fनिकास;
		 */
		/* cmp QWORD PTR [rbp - 0x8], 0x0 */
		EMIT4(0x48, 0x83, 0x7d, 0xf8); EMIT1(0x00);

		/* Save the location of the branch and Generate 6 nops
		 * (4 bytes क्रम an offset and 2 bytes क्रम the jump) These nops
		 * are replaced with a conditional jump once करो_fनिकास (i.e. the
		 * start of the fनिकास invocation) is finalized.
		 */
		branches[i] = prog;
		emit_nops(&prog, 4 + 2);
	पूर्ण

	*pprog = prog;
	वापस 0;
पूर्ण

/* Example:
 * __be16 eth_type_trans(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
 * its 'struct btf_func_model' will be nr_args=2
 * The assembly code when eth_type_trans is executing after trampoline:
 *
 * push rbp
 * mov rbp, rsp
 * sub rsp, 16                     // space क्रम skb and dev
 * push rbx                        // temp regs to pass start समय
 * mov qword ptr [rbp - 16], rdi   // save skb poपूर्णांकer to stack
 * mov qword ptr [rbp - 8], rsi    // save dev poपूर्णांकer to stack
 * call __bpf_prog_enter           // rcu_पढ़ो_lock and preempt_disable
 * mov rbx, rax                    // remember start समय in bpf stats are enabled
 * lea rdi, [rbp - 16]             // R1==ctx of bpf prog
 * call addr_of_jited_FENTRY_prog
 * movअसलq rdi, 64bit_addr_of_काष्ठा_bpf_prog  // unused अगर bpf stats are off
 * mov rsi, rbx                    // prog start समय
 * call __bpf_prog_निकास            // rcu_पढ़ो_unlock, preempt_enable and stats math
 * mov rdi, qword ptr [rbp - 16]   // restore skb poपूर्णांकer from stack
 * mov rsi, qword ptr [rbp - 8]    // restore dev poपूर्णांकer from stack
 * pop rbx
 * leave
 * ret
 *
 * eth_type_trans has 5 byte nop at the beginning. These 5 bytes will be
 * replaced with 'call generated_bpf_trampoline'. When it वापसs
 * eth_type_trans will जारी executing with original skb and dev poपूर्णांकers.
 *
 * The assembly code when eth_type_trans is called from trampoline:
 *
 * push rbp
 * mov rbp, rsp
 * sub rsp, 24                     // space क्रम skb, dev, वापस value
 * push rbx                        // temp regs to pass start समय
 * mov qword ptr [rbp - 24], rdi   // save skb poपूर्णांकer to stack
 * mov qword ptr [rbp - 16], rsi   // save dev poपूर्णांकer to stack
 * call __bpf_prog_enter           // rcu_पढ़ो_lock and preempt_disable
 * mov rbx, rax                    // remember start समय अगर bpf stats are enabled
 * lea rdi, [rbp - 24]             // R1==ctx of bpf prog
 * call addr_of_jited_FENTRY_prog  // bpf prog can access skb and dev
 * movअसलq rdi, 64bit_addr_of_काष्ठा_bpf_prog  // unused अगर bpf stats are off
 * mov rsi, rbx                    // prog start समय
 * call __bpf_prog_निकास            // rcu_पढ़ो_unlock, preempt_enable and stats math
 * mov rdi, qword ptr [rbp - 24]   // restore skb poपूर्णांकer from stack
 * mov rsi, qword ptr [rbp - 16]   // restore dev poपूर्णांकer from stack
 * call eth_type_trans+5           // execute body of eth_type_trans
 * mov qword ptr [rbp - 8], rax    // save वापस value
 * call __bpf_prog_enter           // rcu_पढ़ो_lock and preempt_disable
 * mov rbx, rax                    // remember start समय in bpf stats are enabled
 * lea rdi, [rbp - 24]             // R1==ctx of bpf prog
 * call addr_of_jited_FEXIT_prog   // bpf prog can access skb, dev, वापस value
 * movअसलq rdi, 64bit_addr_of_काष्ठा_bpf_prog  // unused अगर bpf stats are off
 * mov rsi, rbx                    // prog start समय
 * call __bpf_prog_निकास            // rcu_पढ़ो_unlock, preempt_enable and stats math
 * mov rax, qword ptr [rbp - 8]    // restore eth_type_trans's वापस value
 * pop rbx
 * leave
 * add rsp, 8                      // skip eth_type_trans's frame
 * ret                             // वापस to its caller
 */
पूर्णांक arch_prepare_bpf_trampoline(काष्ठा bpf_tramp_image *im, व्योम *image, व्योम *image_end,
				स्थिर काष्ठा btf_func_model *m, u32 flags,
				काष्ठा bpf_tramp_progs *tprogs,
				व्योम *orig_call)
अणु
	पूर्णांक ret, i, cnt = 0, nr_args = m->nr_args;
	पूर्णांक stack_size = nr_args * 8;
	काष्ठा bpf_tramp_progs *fentry = &tprogs[BPF_TRAMP_FENTRY];
	काष्ठा bpf_tramp_progs *fनिकास = &tprogs[BPF_TRAMP_FEXIT];
	काष्ठा bpf_tramp_progs *भ_शेष_ret = &tprogs[BPF_TRAMP_MODIFY_RETURN];
	u8 **branches = शून्य;
	u8 *prog;

	/* x86-64 supports up to 6 arguments. 7+ can be added in the future */
	अगर (nr_args > 6)
		वापस -ENOTSUPP;

	अगर ((flags & BPF_TRAMP_F_RESTORE_REGS) &&
	    (flags & BPF_TRAMP_F_SKIP_FRAME))
		वापस -EINVAL;

	अगर (flags & BPF_TRAMP_F_CALL_ORIG)
		stack_size += 8; /* room क्रम वापस value of orig_call */

	अगर (flags & BPF_TRAMP_F_SKIP_FRAME)
		/* skip patched call inकाष्ठाion and poपूर्णांक orig_call to actual
		 * body of the kernel function.
		 */
		orig_call += X86_PATCH_SIZE;

	prog = image;

	EMIT1(0x55);		 /* push rbp */
	EMIT3(0x48, 0x89, 0xE5); /* mov rbp, rsp */
	EMIT4(0x48, 0x83, 0xEC, stack_size); /* sub rsp, stack_size */
	EMIT1(0x53);		 /* push rbx */

	save_regs(m, &prog, nr_args, stack_size);

	अगर (flags & BPF_TRAMP_F_CALL_ORIG) अणु
		/* arg1: mov rdi, im */
		emit_mov_imm64(&prog, BPF_REG_1, (दीर्घ) im >> 32, (u32) (दीर्घ) im);
		अगर (emit_call(&prog, __bpf_tramp_enter, prog)) अणु
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	अगर (fentry->nr_progs)
		अगर (invoke_bpf(m, &prog, fentry, stack_size))
			वापस -EINVAL;

	अगर (भ_शेष_ret->nr_progs) अणु
		branches = kसुस्मृति(भ_शेष_ret->nr_progs, माप(u8 *),
				   GFP_KERNEL);
		अगर (!branches)
			वापस -ENOMEM;

		अगर (invoke_bpf_mod_ret(m, &prog, भ_शेष_ret, stack_size,
				       branches)) अणु
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण
	पूर्ण

	अगर (flags & BPF_TRAMP_F_CALL_ORIG) अणु
		restore_regs(m, &prog, nr_args, stack_size);

		/* call original function */
		अगर (emit_call(&prog, orig_call, prog)) अणु
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण
		/* remember वापस value in a stack क्रम bpf prog to access */
		emit_stx(&prog, BPF_DW, BPF_REG_FP, BPF_REG_0, -8);
		im->ip_after_call = prog;
		स_नकल(prog, x86_nops[5], X86_PATCH_SIZE);
		prog += X86_PATCH_SIZE;
	पूर्ण

	अगर (भ_शेष_ret->nr_progs) अणु
		/* From Intel 64 and IA-32 Architectures Optimization
		 * Reference Manual, 3.4.1.4 Code Alignment, Assembly/Compiler
		 * Coding Rule 11: All branch tarमाला_लो should be 16-byte
		 * aligned.
		 */
		emit_align(&prog, 16);
		/* Update the branches saved in invoke_bpf_mod_ret with the
		 * aligned address of करो_fनिकास.
		 */
		क्रम (i = 0; i < भ_शेष_ret->nr_progs; i++)
			emit_cond_near_jump(&branches[i], prog, branches[i],
					    X86_JNE);
	पूर्ण

	अगर (fनिकास->nr_progs)
		अगर (invoke_bpf(m, &prog, fनिकास, stack_size)) अणु
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण

	अगर (flags & BPF_TRAMP_F_RESTORE_REGS)
		restore_regs(m, &prog, nr_args, stack_size);

	/* This needs to be करोne regardless. If there were भ_शेष_ret programs,
	 * the वापस value is only updated on the stack and still needs to be
	 * restored to R0.
	 */
	अगर (flags & BPF_TRAMP_F_CALL_ORIG) अणु
		im->ip_epilogue = prog;
		/* arg1: mov rdi, im */
		emit_mov_imm64(&prog, BPF_REG_1, (दीर्घ) im >> 32, (u32) (दीर्घ) im);
		अगर (emit_call(&prog, __bpf_tramp_निकास, prog)) अणु
			ret = -EINVAL;
			जाओ cleanup;
		पूर्ण
		/* restore original वापस value back पूर्णांकo RAX */
		emit_ldx(&prog, BPF_DW, BPF_REG_0, BPF_REG_FP, -8);
	पूर्ण

	EMIT1(0x5B); /* pop rbx */
	EMIT1(0xC9); /* leave */
	अगर (flags & BPF_TRAMP_F_SKIP_FRAME)
		/* skip our वापस address and वापस to parent */
		EMIT4(0x48, 0x83, 0xC4, 8); /* add rsp, 8 */
	EMIT1(0xC3); /* ret */
	/* Make sure the trampoline generation logic करोesn't overflow */
	अगर (WARN_ON_ONCE(prog > (u8 *)image_end - BPF_INSN_SAFETY)) अणु
		ret = -EFAULT;
		जाओ cleanup;
	पूर्ण
	ret = prog - (u8 *)image;

cleanup:
	kमुक्त(branches);
	वापस ret;
पूर्ण

अटल पूर्णांक emit_fallback_jump(u8 **pprog)
अणु
	u8 *prog = *pprog;
	पूर्णांक err = 0;

#अगर_घोषित CONFIG_RETPOLINE
	/* Note that this assumes the the compiler uses बाह्यal
	 * thunks क्रम indirect calls. Both clang and GCC use the same
	 * naming convention क्रम बाह्यal thunks.
	 */
	err = emit_jump(&prog, __x86_indirect_thunk_rdx, prog);
#अन्यथा
	पूर्णांक cnt = 0;

	EMIT2(0xFF, 0xE2);	/* jmp rdx */
#पूर्ण_अगर
	*pprog = prog;
	वापस err;
पूर्ण

अटल पूर्णांक emit_bpf_dispatcher(u8 **pprog, पूर्णांक a, पूर्णांक b, s64 *progs)
अणु
	u8 *jg_reloc, *prog = *pprog;
	पूर्णांक pivot, err, jg_bytes = 1, cnt = 0;
	s64 jg_offset;

	अगर (a == b) अणु
		/* Leaf node of recursion, i.e. not a range of indices
		 * anymore.
		 */
		EMIT1(add_1mod(0x48, BPF_REG_3));	/* cmp rdx,func */
		अगर (!is_simm32(progs[a]))
			वापस -1;
		EMIT2_off32(0x81, add_1reg(0xF8, BPF_REG_3),
			    progs[a]);
		err = emit_cond_near_jump(&prog,	/* je func */
					  (व्योम *)progs[a], prog,
					  X86_JE);
		अगर (err)
			वापस err;

		err = emit_fallback_jump(&prog);	/* jmp thunk/indirect */
		अगर (err)
			वापस err;

		*pprog = prog;
		वापस 0;
	पूर्ण

	/* Not a leaf node, so we pivot, and recursively descend पूर्णांकo
	 * the lower and upper ranges.
	 */
	pivot = (b - a) / 2;
	EMIT1(add_1mod(0x48, BPF_REG_3));		/* cmp rdx,func */
	अगर (!is_simm32(progs[a + pivot]))
		वापस -1;
	EMIT2_off32(0x81, add_1reg(0xF8, BPF_REG_3), progs[a + pivot]);

	अगर (pivot > 2) अणु				/* jg upper_part */
		/* Require near jump. */
		jg_bytes = 4;
		EMIT2_off32(0x0F, X86_JG + 0x10, 0);
	पूर्ण अन्यथा अणु
		EMIT2(X86_JG, 0);
	पूर्ण
	jg_reloc = prog;

	err = emit_bpf_dispatcher(&prog, a, a + pivot,	/* emit lower_part */
				  progs);
	अगर (err)
		वापस err;

	/* From Intel 64 and IA-32 Architectures Optimization
	 * Reference Manual, 3.4.1.4 Code Alignment, Assembly/Compiler
	 * Coding Rule 11: All branch tarमाला_लो should be 16-byte
	 * aligned.
	 */
	emit_align(&prog, 16);
	jg_offset = prog - jg_reloc;
	emit_code(jg_reloc - jg_bytes, jg_offset, jg_bytes);

	err = emit_bpf_dispatcher(&prog, a + pivot + 1,	/* emit upper_part */
				  b, progs);
	अगर (err)
		वापस err;

	*pprog = prog;
	वापस 0;
पूर्ण

अटल पूर्णांक cmp_ips(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर s64 *ipa = a;
	स्थिर s64 *ipb = b;

	अगर (*ipa > *ipb)
		वापस 1;
	अगर (*ipa < *ipb)
		वापस -1;
	वापस 0;
पूर्ण

पूर्णांक arch_prepare_bpf_dispatcher(व्योम *image, s64 *funcs, पूर्णांक num_funcs)
अणु
	u8 *prog = image;

	sort(funcs, num_funcs, माप(funcs[0]), cmp_ips, शून्य);
	वापस emit_bpf_dispatcher(&prog, 0, num_funcs - 1, funcs);
पूर्ण

काष्ठा x64_jit_data अणु
	काष्ठा bpf_binary_header *header;
	पूर्णांक *addrs;
	u8 *image;
	पूर्णांक proglen;
	काष्ठा jit_context ctx;
पूर्ण;

#घोषणा MAX_PASSES 20
#घोषणा PADDING_PASSES (MAX_PASSES - 5)

काष्ठा bpf_prog *bpf_पूर्णांक_jit_compile(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_binary_header *header = शून्य;
	काष्ठा bpf_prog *पंचांगp, *orig_prog = prog;
	काष्ठा x64_jit_data *jit_data;
	पूर्णांक proglen, oldproglen = 0;
	काष्ठा jit_context ctx = अणुपूर्ण;
	bool पंचांगp_blinded = false;
	bool extra_pass = false;
	bool padding = false;
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

	jit_data = prog->aux->jit_data;
	अगर (!jit_data) अणु
		jit_data = kzalloc(माप(*jit_data), GFP_KERNEL);
		अगर (!jit_data) अणु
			prog = orig_prog;
			जाओ out;
		पूर्ण
		prog->aux->jit_data = jit_data;
	पूर्ण
	addrs = jit_data->addrs;
	अगर (addrs) अणु
		ctx = jit_data->ctx;
		oldproglen = jit_data->proglen;
		image = jit_data->image;
		header = jit_data->header;
		extra_pass = true;
		padding = true;
		जाओ skip_init_addrs;
	पूर्ण
	addrs = kvदो_स्मृति_array(prog->len + 1, माप(*addrs), GFP_KERNEL);
	अगर (!addrs) अणु
		prog = orig_prog;
		जाओ out_addrs;
	पूर्ण

	/*
	 * Beक्रमe first pass, make a rough estimation of addrs[]
	 * each BPF inकाष्ठाion is translated to less than 64 bytes
	 */
	क्रम (proglen = 0, i = 0; i <= prog->len; i++) अणु
		proglen += 64;
		addrs[i] = proglen;
	पूर्ण
	ctx.cleanup_addr = proglen;
skip_init_addrs:

	/*
	 * JITed image shrinks with every pass and the loop iterates
	 * until the image stops shrinking. Very large BPF programs
	 * may converge on the last pass. In such हाल करो one more
	 * pass to emit the final image.
	 */
	क्रम (pass = 0; pass < MAX_PASSES || image; pass++) अणु
		अगर (!padding && pass >= PADDING_PASSES)
			padding = true;
		proglen = करो_jit(prog, addrs, image, oldproglen, &ctx, padding);
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
			/*
			 * The number of entries in extable is the number of BPF_LDX
			 * insns that access kernel memory via "pointer to BTF type".
			 * The verअगरier changed their opcode from LDX|MEM|size
			 * to LDX|PROBE_MEM|size to make JITing easier.
			 */
			u32 align = __alignof__(काष्ठा exception_table_entry);
			u32 extable_size = prog->aux->num_exentries *
				माप(काष्ठा exception_table_entry);

			/* allocate module memory क्रम x86 insns and extable */
			header = bpf_jit_binary_alloc(roundup(proglen, align) + extable_size,
						      &image, align, jit_fill_hole);
			अगर (!header) अणु
				prog = orig_prog;
				जाओ out_addrs;
			पूर्ण
			prog->aux->extable = (व्योम *) image + roundup(proglen, align);
		पूर्ण
		oldproglen = proglen;
		cond_resched();
	पूर्ण

	अगर (bpf_jit_enable > 1)
		bpf_jit_dump(prog->len, proglen, pass + 1, image);

	अगर (image) अणु
		अगर (!prog->is_func || extra_pass) अणु
			bpf_tail_call_direct_fixup(prog);
			bpf_jit_binary_lock_ro(header);
		पूर्ण अन्यथा अणु
			jit_data->addrs = addrs;
			jit_data->ctx = ctx;
			jit_data->proglen = proglen;
			jit_data->image = image;
			jit_data->header = header;
		पूर्ण
		prog->bpf_func = (व्योम *)image;
		prog->jited = 1;
		prog->jited_len = proglen;
	पूर्ण अन्यथा अणु
		prog = orig_prog;
	पूर्ण

	अगर (!image || !prog->is_func || extra_pass) अणु
		अगर (image)
			bpf_prog_fill_jited_linfo(prog, addrs + 1);
out_addrs:
		kvमुक्त(addrs);
		kमुक्त(jit_data);
		prog->aux->jit_data = शून्य;
	पूर्ण
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
