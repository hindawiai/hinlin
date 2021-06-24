<शैली गुरु>
अणु
	"ARG_PTR_TO_LONG uninitialized",
	.insns = अणु
		/* bpf_म_से_अदीर्घ arg1 (buf) */
		BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
		BPF_MOV64_IMM(BPF_REG_0, 0x00303036),
		BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

		BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

		/* bpf_म_से_अदीर्घ arg2 (buf_len) */
		BPF_MOV64_IMM(BPF_REG_2, 4),

		/* bpf_म_से_अदीर्घ arg3 (flags) */
		BPF_MOV64_IMM(BPF_REG_3, 0),

		/* bpf_म_से_अदीर्घ arg4 (res) */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
		BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

		/* bpf_म_से_अदीर्घ() */
		BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_CGROUP_SYSCTL,
	.errstr = "invalid indirect read from stack R4 off -16+0 size 8",
पूर्ण,
अणु
	"ARG_PTR_TO_LONG half-uninitialized",
	.insns = अणु
		/* bpf_म_से_अदीर्घ arg1 (buf) */
		BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
		BPF_MOV64_IMM(BPF_REG_0, 0x00303036),
		BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

		BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

		/* bpf_म_से_अदीर्घ arg2 (buf_len) */
		BPF_MOV64_IMM(BPF_REG_2, 4),

		/* bpf_म_से_अदीर्घ arg3 (flags) */
		BPF_MOV64_IMM(BPF_REG_3, 0),

		/* bpf_म_से_अदीर्घ arg4 (res) */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
		BPF_STX_MEM(BPF_W, BPF_REG_7, BPF_REG_0, 0),
		BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

		/* bpf_म_से_अदीर्घ() */
		BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_CGROUP_SYSCTL,
	.errstr = "invalid indirect read from stack R4 off -16+4 size 8",
पूर्ण,
अणु
	"ARG_PTR_TO_LONG misaligned",
	.insns = अणु
		/* bpf_म_से_अदीर्घ arg1 (buf) */
		BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
		BPF_MOV64_IMM(BPF_REG_0, 0x00303036),
		BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

		BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

		/* bpf_म_से_अदीर्घ arg2 (buf_len) */
		BPF_MOV64_IMM(BPF_REG_2, 4),

		/* bpf_म_से_अदीर्घ arg3 (flags) */
		BPF_MOV64_IMM(BPF_REG_3, 0),

		/* bpf_म_से_अदीर्घ arg4 (res) */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -12),
		BPF_MOV64_IMM(BPF_REG_0, 0),
		BPF_STX_MEM(BPF_W, BPF_REG_7, BPF_REG_0, 0),
		BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 4),
		BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

		/* bpf_म_से_अदीर्घ() */
		BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_CGROUP_SYSCTL,
	.errstr = "misaligned stack access off (0x0; 0x0)+-20+0 size 8",
पूर्ण,
अणु
	"ARG_PTR_TO_LONG size < sizeof(long)",
	.insns = अणु
		/* bpf_म_से_अदीर्घ arg1 (buf) */
		BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -16),
		BPF_MOV64_IMM(BPF_REG_0, 0x00303036),
		BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

		BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

		/* bpf_म_से_अदीर्घ arg2 (buf_len) */
		BPF_MOV64_IMM(BPF_REG_2, 4),

		/* bpf_म_से_अदीर्घ arg3 (flags) */
		BPF_MOV64_IMM(BPF_REG_3, 0),

		/* bpf_म_से_अदीर्घ arg4 (res) */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, 12),
		BPF_STX_MEM(BPF_W, BPF_REG_7, BPF_REG_0, 0),
		BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

		/* bpf_म_से_अदीर्घ() */
		BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_CGROUP_SYSCTL,
	.errstr = "invalid indirect access to stack R4 off=-4 size=8",
पूर्ण,
अणु
	"ARG_PTR_TO_LONG initialized",
	.insns = अणु
		/* bpf_म_से_अदीर्घ arg1 (buf) */
		BPF_MOV64_REG(BPF_REG_7, BPF_REG_10),
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
		BPF_MOV64_IMM(BPF_REG_0, 0x00303036),
		BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),

		BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),

		/* bpf_म_से_अदीर्घ arg2 (buf_len) */
		BPF_MOV64_IMM(BPF_REG_2, 4),

		/* bpf_म_से_अदीर्घ arg3 (flags) */
		BPF_MOV64_IMM(BPF_REG_3, 0),

		/* bpf_म_से_अदीर्घ arg4 (res) */
		BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, -8),
		BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
		BPF_MOV64_REG(BPF_REG_4, BPF_REG_7),

		/* bpf_म_से_अदीर्घ() */
		BPF_EMIT_CALL(BPF_FUNC_म_से_अदीर्घ),

		BPF_MOV64_IMM(BPF_REG_0, 1),
		BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_CGROUP_SYSCTL,
पूर्ण,
