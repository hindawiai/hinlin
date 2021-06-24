<शैली गुरु>
अणु
	"BPF_ATOMIC_AND without fetch",
	.insns = अणु
		/* val = 0x110; */
		BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0x110),
		/* atomic_and(&val, 0x011); */
		BPF_MOV64_IMM(BPF_REG_1, 0x011),
		BPF_ATOMIC_OP(BPF_DW, BPF_AND, BPF_REG_10, BPF_REG_1, -8),
		/* अगर (val != 0x010) निकास(2); */
		BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0x010, 2),
		BPF_MOV64_IMM(BPF_REG_0, 2),
		BPF_EXIT_INSN(),
		/* r1 should not be clobbered, no BPF_FETCH flag */
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0x011, 1),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"BPF_ATOMIC_AND with fetch",
	.insns = अणु
		BPF_MOV64_IMM(BPF_REG_0, 123),
		/* val = 0x110; */
		BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0x110),
		/* old = atomic_fetch_and(&val, 0x011); */
		BPF_MOV64_IMM(BPF_REG_1, 0x011),
		BPF_ATOMIC_OP(BPF_DW, BPF_AND | BPF_FETCH, BPF_REG_10, BPF_REG_1, -8),
		/* अगर (old != 0x110) निकास(3); */
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0x110, 2),
		BPF_MOV64_IMM(BPF_REG_0, 3),
		BPF_EXIT_INSN(),
		/* अगर (val != 0x010) निकास(2); */
		BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0x010, 2),
		BPF_MOV64_IMM(BPF_REG_1, 2),
		BPF_EXIT_INSN(),
		/* Check R0 wasn't clobbered (क्रम fear of x86 JIT bug) */
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 123, 2),
		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
		/* निकास(0); */
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"BPF_ATOMIC_AND with fetch 32bit",
	.insns = अणु
		/* r0 = (s64) -1 */
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_ALU64_IMM(BPF_SUB, BPF_REG_0, 1),
		/* val = 0x110; */
		BPF_ST_MEM(BPF_W, BPF_REG_10, -4, 0x110),
		/* old = atomic_fetch_and(&val, 0x011); */
		BPF_MOV32_IMM(BPF_REG_1, 0x011),
		BPF_ATOMIC_OP(BPF_W, BPF_AND | BPF_FETCH, BPF_REG_10, BPF_REG_1, -4),
		/* अगर (old != 0x110) निकास(3); */
		BPF_JMP32_IMM(BPF_JEQ, BPF_REG_1, 0x110, 2),
		BPF_MOV32_IMM(BPF_REG_0, 3),
		BPF_EXIT_INSN(),
		/* अगर (val != 0x010) निकास(2); */
		BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_10, -4),
		BPF_JMP32_IMM(BPF_JEQ, BPF_REG_1, 0x010, 2),
		BPF_MOV32_IMM(BPF_REG_1, 2),
		BPF_EXIT_INSN(),
		/* Check R0 wasn't clobbered (क्रम fear of x86 JIT bug)
		 * It should be -1 so add 1 to get निकास code.
		 */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"BPF_ATOMIC_AND with fetch - r0 as source reg",
	.insns = अणु
		/* val = 0x110; */
		BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0x110),
		/* old = atomic_fetch_and(&val, 0x011); */
		BPF_MOV64_IMM(BPF_REG_0, 0x011),
		BPF_ATOMIC_OP(BPF_DW, BPF_AND | BPF_FETCH, BPF_REG_10, BPF_REG_0, -8),
		/* अगर (old != 0x110) निकास(3); */
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0x110, 2),
		BPF_MOV64_IMM(BPF_REG_0, 3),
		BPF_EXIT_INSN(),
		/* अगर (val != 0x010) निकास(2); */
		BPF_LDX_MEM(BPF_DW, BPF_REG_1, BPF_REG_10, -8),
		BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0x010, 2),
		BPF_MOV64_IMM(BPF_REG_1, 2),
		BPF_EXIT_INSN(),
		/* निकास(0); */
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
पूर्ण,
