<शैली गुरु>
अणु
	"invalid call insn1",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL | BPF_X, 0, 0, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "unknown opcode 8d",
	.result = REJECT,
पूर्ण,
अणु
	"invalid call insn2",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 1, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "BPF_CALL uses reserved",
	.result = REJECT,
पूर्ण,
अणु
	"invalid function call",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, 1234567),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "invalid func unknown#1234567",
	.result = REJECT,
पूर्ण,
अणु
	"invalid argument register",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_cgroup_classid),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_cgroup_classid),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R1 !read_ok",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
पूर्ण,
अणु
	"non-invalid argument register",
	.insns = अणु
	BPF_ALU64_REG(BPF_MOV, BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_cgroup_classid),
	BPF_ALU64_REG(BPF_MOV, BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_cgroup_classid),
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
पूर्ण,
