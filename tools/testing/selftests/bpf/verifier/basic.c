<शैली गुरु>
अणु
	"empty prog",
	.insns = अणु
	पूर्ण,
	.errstr = "last insn is not an exit or jmp",
	.result = REJECT,
पूर्ण,
अणु
	"only exit insn",
	.insns = अणु
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R0 !read_ok",
	.result = REJECT,
पूर्ण,
अणु
	"no bpf_exit",
	.insns = अणु
	BPF_ALU64_REG(BPF_MOV, BPF_REG_0, BPF_REG_2),
	पूर्ण,
	.errstr = "not an exit",
	.result = REJECT,
पूर्ण,
