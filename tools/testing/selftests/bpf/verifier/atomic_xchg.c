<शैली गुरु>
अणु
	"atomic exchange smoketest - 64bit",
	.insns = अणु
		/* val = 3; */
		BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 3),
		/* old = atomic_xchg(&val, 4); */
		BPF_MOV64_IMM(BPF_REG_1, 4),
		BPF_ATOMIC_OP(BPF_DW, BPF_XCHG, BPF_REG_10, BPF_REG_1, -8),
		/* अगर (old != 3) निकास(1); */
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 3, 2),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
		/* अगर (val != 4) निकास(2); */
		BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 4, 2),
		BPF_MOV64_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
		/* निकास(0); */
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"atomic exchange smoketest - 32bit",
	.insns = अणु
		/* val = 3; */
		BPF_ST_MEM(BPF_W, BPF_REG_10, -4, 3),
		/* old = atomic_xchg(&val, 4); */
		BPF_MOV32_IMM(BPF_REG_1, 4),
		BPF_ATOMIC_OP(BPF_W, BPF_XCHG, BPF_REG_10, BPF_REG_1, -4),
		/* अगर (old != 3) निकास(1); */
		BPF_JMP32_IMM(BPF_JEQ, BPF_REG_1, 3, 2),
		BPF_MOV32_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
		/* अगर (val != 4) निकास(2); */
		BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_10, -4),
		BPF_JMP32_IMM(BPF_JEQ, BPF_REG_0, 4, 2),
		BPF_MOV32_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
		/* निकास(0); */
		BPF_MOV32_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
