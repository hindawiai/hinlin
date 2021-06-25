<शैली गुरु>
अणु
	"read uninitialized register",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R2 !read_ok",
	.result = REJECT,
पूर्ण,
अणु
	"read invalid register",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_0, -1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R15 is invalid",
	.result = REJECT,
पूर्ण,
अणु
	"program doesn't init R0 before exit",
	.insns = अणु
	BPF_ALU64_REG(BPF_MOV, BPF_REG_2, BPF_REG_1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R0 !read_ok",
	.result = REJECT,
पूर्ण,
अणु
	"program doesn't init R0 before exit in all branches",
	.insns = अणु
	BPF_JMP_IMM(BPF_JGE, BPF_REG_1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R0 !read_ok",
	.errstr_unpriv = "R1 pointer comparison",
	.result = REJECT,
पूर्ण,
