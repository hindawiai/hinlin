<शैली गुरु>
अणु
	"invalid src register in STX",
	.insns = अणु
	BPF_STX_MEM(BPF_B, BPF_REG_10, -1, -1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R15 is invalid",
	.result = REJECT,
पूर्ण,
अणु
	"invalid dst register in STX",
	.insns = अणु
	BPF_STX_MEM(BPF_B, 14, BPF_REG_10, -1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R14 is invalid",
	.result = REJECT,
पूर्ण,
अणु
	"invalid dst register in ST",
	.insns = अणु
	BPF_ST_MEM(BPF_B, 14, -1, -1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R14 is invalid",
	.result = REJECT,
पूर्ण,
अणु
	"invalid src register in LDX",
	.insns = अणु
	BPF_LDX_MEM(BPF_B, BPF_REG_0, 12, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R12 is invalid",
	.result = REJECT,
पूर्ण,
अणु
	"invalid dst register in LDX",
	.insns = अणु
	BPF_LDX_MEM(BPF_B, 11, BPF_REG_1, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R11 is invalid",
	.result = REJECT,
पूर्ण,
