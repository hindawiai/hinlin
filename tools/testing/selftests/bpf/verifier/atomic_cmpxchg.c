<शैली गुरु>
अणु
	"atomic compare-and-exchange smoketest - 64bit",
	.insns = अणु
		/* val = 3; */
		BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
		/* old = atomic_cmpxchg(&val, 2, 4); */
		BPF_MOV64_IMM(BPF_REG_1, 4),
		BPF_MOV64_IMM(BPF_REG_0, 2),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_REG_10, BPF_REG_1, -8),
		/* अगर (old != 3) निकास(2); */
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
		BPF_MOV64_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
		/* अगर (val != 3) निकास(3); */
		BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
		BPF_MOV64_IMM(BPF_REG_0, 3),
		BPF_EXIT_INSN(),
		/* old = atomic_cmpxchg(&val, 3, 4); */
		BPF_MOV64_IMM(BPF_REG_1, 4),
		BPF_MOV64_IMM(BPF_REG_0, 3),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_REG_10, BPF_REG_1, -8),
		/* अगर (old != 3) निकास(4); */
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
		BPF_MOV64_IMM(BPF_REG_0, 4),
		BPF_EXIT_INSN(),
		/* अगर (val != 4) निकास(5); */
		BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 4, 2),
		BPF_MOV64_IMM(BPF_REG_0, 5),
		BPF_EXIT_INSN(),
		/* निकास(0); */
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"atomic compare-and-exchange smoketest - 32bit",
	.insns = अणु
		/* val = 3; */
		BPF_ST_MEM(BPF_W, BPF_REG_10, -4, 3),
		/* old = atomic_cmpxchg(&val, 2, 4); */
		BPF_MOV32_IMM(BPF_REG_1, 4),
		BPF_MOV32_IMM(BPF_REG_0, 2),
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_REG_10, BPF_REG_1, -4),
		/* अगर (old != 3) निकास(2); */
		BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
		BPF_MOV32_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
		/* अगर (val != 3) निकास(3); */
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_10, -4),
		BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
		BPF_MOV32_IMM(BPF_REG_0, 3),
		BPF_EXIT_INSN(),
		/* old = atomic_cmpxchg(&val, 3, 4); */
		BPF_MOV32_IMM(BPF_REG_1, 4),
		BPF_MOV32_IMM(BPF_REG_0, 3),
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_REG_10, BPF_REG_1, -4),
		/* अगर (old != 3) निकास(4); */
		BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 3, 2),
		BPF_MOV32_IMM(BPF_REG_0, 4),
		BPF_EXIT_INSN(),
		/* अगर (val != 4) निकास(5); */
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_10, -4),
		BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 4, 2),
		BPF_MOV32_IMM(BPF_REG_0, 5),
		BPF_EXIT_INSN(),
		/* निकास(0); */
		BPF_MOV32_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"Can't use cmpxchg on uninit src reg",
	.insns = अणु
		BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
		BPF_MOV64_IMM(BPF_REG_0, 3),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_REG_10, BPF_REG_2, -8),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = REJECT,
	.errstr = "!read_ok",
पूर्ण,
अणु
	"Can't use cmpxchg on uninit memory",
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_0, 3),
		BPF_MOV64_IMM(BPF_REG_2, 4),
		BPF_ATOMIC_OP(BPF_DW, BPF_CMPXCHG, BPF_REG_10, BPF_REG_2, -8),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = REJECT,
	.errstr = "invalid read from stack",
पूर्ण,
अणु
	"BPF_W cmpxchg should zero top 32 bits",
	.insns = अणु
		/* r0 = U64_MAX; */
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_ALU64_IMM(BPF_SUB, BPF_REG_0, 1),
		/* u64 val = r0; */
		BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0, -8),
		/* r0 = (u32)atomic_cmpxchg((u32 *)&val, r0, 1); */
		BPF_MOV32_IMM(BPF_REG_1, 1),
		BPF_ATOMIC_OP(BPF_W, BPF_CMPXCHG, BPF_REG_10, BPF_REG_1, -8),
		/* r1 = 0x00000000FFFFFFFFull; */
		BPF_MOV64_IMM(BPF_REG_1, 1),
		BPF_ALU64_IMM(BPF_LSH, BPF_REG_1, 32),
		BPF_ALU64_IMM(BPF_SUB, BPF_REG_1, 1),
		/* अगर (r0 != r1) निकास(1); */
		BPF_JMP_REG(BPF_JEQ, BPF_REG_0, BPF_REG_1, 2),
		BPF_MOV32_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
		/* निकास(0); */
		BPF_MOV32_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
