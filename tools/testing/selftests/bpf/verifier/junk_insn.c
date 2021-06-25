<शैली गुरु>
अणु
	"junk insn",
	.insns = अणु
	BPF_RAW_INSN(0, 0, 0, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "unknown opcode 00",
	.result = REJECT,
पूर्ण,
अणु
	"junk insn2",
	.insns = अणु
	BPF_RAW_INSN(1, 0, 0, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "BPF_LDX uses reserved fields",
	.result = REJECT,
पूर्ण,
अणु
	"junk insn3",
	.insns = अणु
	BPF_RAW_INSN(-1, 0, 0, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "unknown opcode ff",
	.result = REJECT,
पूर्ण,
अणु
	"junk insn4",
	.insns = अणु
	BPF_RAW_INSN(-1, -1, -1, -1, -1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "unknown opcode ff",
	.result = REJECT,
पूर्ण,
अणु
	"junk insn5",
	.insns = अणु
	BPF_RAW_INSN(0x7f, -1, -1, -1, -1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "BPF_ALU uses reserved fields",
	.result = REJECT,
पूर्ण,
