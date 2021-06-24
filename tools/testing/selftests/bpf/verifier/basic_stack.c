<शैली गुरु>
अणु
	"stack out of bounds",
	.insns = अणु
	BPF_ST_MEM(BPF_DW, BPF_REG_10, 8, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "invalid write to stack",
	.result = REJECT,
पूर्ण,
अणु
	"uninitialized stack1",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 2 पूर्ण,
	.errstr = "invalid indirect read from stack",
	.result = REJECT,
पूर्ण,
अणु
	"uninitialized stack2",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_2, -8),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "invalid read from stack",
	.result = REJECT,
पूर्ण,
अणु
	"invalid fp arithmetic",
	/* If this माला_लो ever changed, make sure JITs can deal with it. */
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_1, 8),
	BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "R1 subtraction from stack pointer",
	.result = REJECT,
पूर्ण,
अणु
	"non-invalid fp arithmetic",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0, -8),
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"misaligned read from stack",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_2, -4),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "misaligned stack access",
	.result = REJECT,
पूर्ण,
