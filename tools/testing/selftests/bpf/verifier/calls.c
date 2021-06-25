<शैली गुरु>
अणु
	"calls: basic sanity",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: not on unpriviledged",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr_unpriv = "loading/calling other bpf or kernel functions are allowed for",
	.result_unpriv = REJECT,
	.result = ACCEPT,
	.retval = 1,
पूर्ण,
अणु
	"calls: div by 0 in subprog",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 8),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_0),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_2, BPF_REG_1, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV32_IMM(BPF_REG_2, 0),
	BPF_MOV32_IMM(BPF_REG_3, 1),
	BPF_ALU32_REG(BPF_DIV, BPF_REG_3, BPF_REG_2),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.retval = 1,
पूर्ण,
अणु
	"calls: multiple ret types in subprog 1",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 8),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_0),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_2, BPF_REG_1, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),
	BPF_MOV32_IMM(BPF_REG_0, 42),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = REJECT,
	.errstr = "R0 invalid mem access 'inv'",
पूर्ण,
अणु
	"calls: multiple ret types in subprog 2",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 8),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_0),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_2, BPF_REG_1, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 9),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_6,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 64),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.fixup_map_hash_8b = अणु 16 पूर्ण,
	.result = REJECT,
	.errstr = "R0 min value is outside of the allowed memory range",
पूर्ण,
अणु
	"calls: overlapping caller/callee",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "last insn is not an exit or jmp",
	.result = REJECT,
पूर्ण,
अणु
	"calls: wrong recursive calls",
	.insns = अणु
	BPF_JMP_IMM(BPF_JA, 0, 0, 4),
	BPF_JMP_IMM(BPF_JA, 0, 0, 4),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, -2),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, -2),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, -2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "jump out of range",
	.result = REJECT,
पूर्ण,
अणु
	"calls: wrong src reg",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 3, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "BPF_CALL uses reserved fields",
	.result = REJECT,
पूर्ण,
अणु
	"calls: wrong off value",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, -1, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "BPF_CALL uses reserved fields",
	.result = REJECT,
पूर्ण,
अणु
	"calls: jump back loop",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, -1),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "back-edge from insn 0 to 0",
	.result = REJECT,
पूर्ण,
अणु
	"calls: conditional call",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, mark)),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 3),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "jump out of range",
	.result = REJECT,
पूर्ण,
अणु
	"calls: conditional call 2",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, mark)),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 3),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: conditional call 3",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, mark)),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 3),
	BPF_JMP_IMM(BPF_JA, 0, 0, 4),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, -6),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_JMP_IMM(BPF_JA, 0, 0, -6),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
	.errstr_unpriv = "back-edge from insn",
	.result_unpriv = REJECT,
	.result = ACCEPT,
	.retval = 1,
पूर्ण,
अणु
	"calls: conditional call 4",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, mark)),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 3),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, -5),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: conditional call 5",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, mark)),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 3),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, -6),
	BPF_MOV64_IMM(BPF_REG_0, 3),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.retval = 1,
पूर्ण,
अणु
	"calls: conditional call 6",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, -3),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, mark)),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.errstr = "infinite loop detected",
	.result = REJECT,
पूर्ण,
अणु
	"calls: using r0 returned by callee",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: using uninit r0 from callee",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "!read_ok",
	.result = REJECT,
पूर्ण,
अणु
	"calls: callee is using r1",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, len)),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_ACT,
	.result = ACCEPT,
	.retval = TEST_DATA_LEN,
पूर्ण,
अणु
	"calls: callee using args1",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr_unpriv = "allowed for",
	.result_unpriv = REJECT,
	.result = ACCEPT,
	.retval = POINTER_VALUE,
पूर्ण,
अणु
	"calls: callee using wrong args2",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "R2 !read_ok",
	.result = REJECT,
पूर्ण,
अणु
	"calls: callee using two args",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_LDX_MEM(BPF_W, BPF_REG_1, BPF_REG_6,
		    दुरत्व(काष्ठा __sk_buff, len)),
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_6,
		    दुरत्व(काष्ठा __sk_buff, len)),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_1),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_0, BPF_REG_2),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr_unpriv = "allowed for",
	.result_unpriv = REJECT,
	.result = ACCEPT,
	.retval = TEST_DATA_LEN + TEST_DATA_LEN - ETH_HLEN - ETH_HLEN,
पूर्ण,
अणु
	"calls: callee changing pkt pointers",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_6, BPF_REG_1, दुरत्व(काष्ठा xdp_md, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_7, BPF_REG_1,
		    दुरत्व(काष्ठा xdp_md, data_end)),
	BPF_MOV64_REG(BPF_REG_8, BPF_REG_6),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_8, 8),
	BPF_JMP_REG(BPF_JGT, BPF_REG_8, BPF_REG_7, 2),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	/* clear_all_pkt_poपूर्णांकers() has to walk all frames
	 * to make sure that pkt poपूर्णांकers in the caller
	 * are cleared when callee is calling a helper that
	 * adjusts packet size
	 */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_6, 0),
	BPF_MOV32_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_xdp_adjust_head),
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = REJECT,
	.errstr = "R6 invalid mem access 'inv'",
	.prog_type = BPF_PROG_TYPE_XDP,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: ptr null check in subprog",
	.insns = अणु
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_0, BPF_REG_6, 0),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 1),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr_unpriv = "loading/calling other bpf or kernel functions are allowed for",
	.fixup_map_hash_48b = अणु 3 पूर्ण,
	.result_unpriv = REJECT,
	.result = ACCEPT,
	.retval = 0,
पूर्ण,
अणु
	"calls: two calls with args",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 6),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_7, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_7),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, len)),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.retval = TEST_DATA_LEN + TEST_DATA_LEN,
पूर्ण,
अणु
	"calls: calls with stack arith",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -64),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -64),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -64),
	BPF_MOV64_IMM(BPF_REG_0, 42),
	BPF_STX_MEM(BPF_DW, BPF_REG_2, BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.retval = 42,
पूर्ण,
अणु
	"calls: calls with misaligned stack access",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -63),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -61),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -63),
	BPF_MOV64_IMM(BPF_REG_0, 42),
	BPF_STX_MEM(BPF_DW, BPF_REG_2, BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.flags = F_LOAD_WITH_STRICT_ALIGNMENT,
	.errstr = "misaligned stack access",
	.result = REJECT,
पूर्ण,
अणु
	"calls: calls control flow, jump test",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 42),
	BPF_JMP_IMM(BPF_JA, 0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 43),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_JMP_IMM(BPF_JA, 0, 0, -3),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.retval = 43,
पूर्ण,
अणु
	"calls: calls control flow, jump test 2",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 42),
	BPF_JMP_IMM(BPF_JA, 0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 43),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, -3),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.errstr = "jump out of range from insn 1 to 4",
	.result = REJECT,
पूर्ण,
अणु
	"calls: two calls with bad jump",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 6),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_7, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_7),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, len)),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, -3),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "jump out of range from insn 11 to 9",
	.result = REJECT,
पूर्ण,
अणु
	"calls: recursive call. test1",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, -1),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "back-edge",
	.result = REJECT,
पूर्ण,
अणु
	"calls: recursive call. test2",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, -3),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "back-edge",
	.result = REJECT,
पूर्ण,
अणु
	"calls: unreachable code",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "unreachable insn 6",
	.result = REJECT,
पूर्ण,
अणु
	"calls: invalid call",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, -4),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "invalid destination",
	.result = REJECT,
पूर्ण,
अणु
	"calls: invalid call 2",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 0x7fffffff),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "invalid destination",
	.result = REJECT,
पूर्ण,
अणु
	"calls: jumping across function bodies. test1",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, -3),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "jump out of range",
	.result = REJECT,
पूर्ण,
अणु
	"calls: jumping across function bodies. test2",
	.insns = अणु
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 3),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "jump out of range",
	.result = REJECT,
पूर्ण,
अणु
	"calls: call without exit",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, -2),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "not an exit",
	.result = REJECT,
पूर्ण,
अणु
	"calls: call into middle of ld_imm64",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_LD_IMM64(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "last insn",
	.result = REJECT,
पूर्ण,
अणु
	"calls: call into middle of other call",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "last insn",
	.result = REJECT,
पूर्ण,
अणु
	"calls: subprog call with ld_abs in main prog",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_LD_ABS(BPF_B, 0),
	BPF_LD_ABS(BPF_H, 0),
	BPF_LD_ABS(BPF_W, 0),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_6),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 5),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_7),
	BPF_LD_ABS(BPF_B, 0),
	BPF_LD_ABS(BPF_H, 0),
	BPF_LD_ABS(BPF_W, 0),
	BPF_EXIT_INSN(),
	BPF_MOV64_IMM(BPF_REG_2, 1),
	BPF_MOV64_IMM(BPF_REG_3, 2),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_skb_vlan_push),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: two calls with bad fallthrough",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 6),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_7, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_7),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_0),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, len)),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_TRACEPOINT,
	.errstr = "not an exit",
	.result = REJECT,
पूर्ण,
अणु
	"calls: two calls with stack read",
	.insns = अणु
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 6),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_7, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_7),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: two calls with stack write",
	.insns = अणु
	/* मुख्य prog */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -16),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 7),
	BPF_MOV64_REG(BPF_REG_8, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_8, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_8),
	/* ग_लिखो पूर्णांकo stack frame of मुख्य prog */
	BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 2 */
	/* पढ़ो from stack frame of मुख्य prog */
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: stack overflow using two frames (pre-call access)",
	.insns = अणु
	/* prog 1 */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -300, 0),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),

	/* prog 2 */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -300, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.errstr = "combined stack size",
	.result = REJECT,
पूर्ण,
अणु
	"calls: stack overflow using two frames (post-call access)",
	.insns = अणु
	/* prog 1 */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 2),
	BPF_ST_MEM(BPF_B, BPF_REG_10, -300, 0),
	BPF_EXIT_INSN(),

	/* prog 2 */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -300, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.errstr = "combined stack size",
	.result = REJECT,
पूर्ण,
अणु
	"calls: stack depth check using three frames. test1",
	.insns = अणु
	/* मुख्य */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 4), /* call A */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 5), /* call B */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -32, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	/* A */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -256, 0),
	BPF_EXIT_INSN(),
	/* B */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, -3), /* call A */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -64, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	/* stack_मुख्य=32, stack_A=256, stack_B=64
	 * and max(मुख्य+A, मुख्य+A+B) < 512
	 */
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: stack depth check using three frames. test2",
	.insns = अणु
	/* मुख्य */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 4), /* call A */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 5), /* call B */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -32, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	/* A */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -64, 0),
	BPF_EXIT_INSN(),
	/* B */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, -3), /* call A */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -256, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	/* stack_मुख्य=32, stack_A=64, stack_B=256
	 * and max(मुख्य+A, मुख्य+A+B) < 512
	 */
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: stack depth check using three frames. test3",
	.insns = अणु
	/* मुख्य */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 6), /* call A */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 8), /* call B */
	BPF_JMP_IMM(BPF_JGE, BPF_REG_6, 0, 1),
	BPF_ST_MEM(BPF_B, BPF_REG_10, -64, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	/* A */
	BPF_JMP_IMM(BPF_JLT, BPF_REG_1, 10, 1),
	BPF_EXIT_INSN(),
	BPF_ST_MEM(BPF_B, BPF_REG_10, -224, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, -3),
	/* B */
	BPF_JMP_IMM(BPF_JGT, BPF_REG_1, 2, 1),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, -6), /* call A */
	BPF_ST_MEM(BPF_B, BPF_REG_10, -256, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	/* stack_मुख्य=64, stack_A=224, stack_B=256
	 * and max(मुख्य+A, मुख्य+A+B) > 512
	 */
	.errstr = "combined stack",
	.result = REJECT,
पूर्ण,
अणु
	"calls: stack depth check using three frames. test4",
	/* व्योम मुख्य(व्योम) अणु
	 *   func1(0);
	 *   func1(1);
	 *   func2(1);
	 * पूर्ण
	 * व्योम func1(पूर्णांक alloc_or_recurse) अणु
	 *   अगर (alloc_or_recurse) अणु
	 *     frame_poपूर्णांकer[-300] = 1;
	 *   पूर्ण अन्यथा अणु
	 *     func2(alloc_or_recurse);
	 *   पूर्ण
	 * पूर्ण
	 * व्योम func2(पूर्णांक alloc_or_recurse) अणु
	 *   अगर (alloc_or_recurse) अणु
	 *     frame_poपूर्णांकer[-300] = 1;
	 *   पूर्ण
	 * पूर्ण
	 */
	.insns = अणु
	/* मुख्य */
	BPF_MOV64_IMM(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 6), /* call A */
	BPF_MOV64_IMM(BPF_REG_1, 1),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 4), /* call A */
	BPF_MOV64_IMM(BPF_REG_1, 1),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 7), /* call B */
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	/* A */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 2),
	BPF_ST_MEM(BPF_B, BPF_REG_10, -300, 0),
	BPF_EXIT_INSN(),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call B */
	BPF_EXIT_INSN(),
	/* B */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 1),
	BPF_ST_MEM(BPF_B, BPF_REG_10, -300, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.result = REJECT,
	.errstr = "combined stack",
पूर्ण,
अणु
	"calls: stack depth check using three frames. test5",
	.insns = अणु
	/* मुख्य */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call A */
	BPF_EXIT_INSN(),
	/* A */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call B */
	BPF_EXIT_INSN(),
	/* B */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call C */
	BPF_EXIT_INSN(),
	/* C */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call D */
	BPF_EXIT_INSN(),
	/* D */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call E */
	BPF_EXIT_INSN(),
	/* E */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call F */
	BPF_EXIT_INSN(),
	/* F */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call G */
	BPF_EXIT_INSN(),
	/* G */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call H */
	BPF_EXIT_INSN(),
	/* H */
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.errstr = "call stack",
	.result = REJECT,
पूर्ण,
अणु
	"calls: stack depth check in dead code",
	.insns = अणु
	/* मुख्य */
	BPF_MOV64_IMM(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call A */
	BPF_EXIT_INSN(),
	/* A */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 1),
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 2), /* call B */
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	/* B */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call C */
	BPF_EXIT_INSN(),
	/* C */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call D */
	BPF_EXIT_INSN(),
	/* D */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call E */
	BPF_EXIT_INSN(),
	/* E */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call F */
	BPF_EXIT_INSN(),
	/* F */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call G */
	BPF_EXIT_INSN(),
	/* G */
	BPF_RAW_INSN(BPF_JMP|BPF_CALL, 0, 1, 0, 1), /* call H */
	BPF_EXIT_INSN(),
	/* H */
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.errstr = "call stack",
	.result = REJECT,
पूर्ण,
अणु
	"calls: spill into caller stack frame",
	.insns = अणु
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),
	BPF_STX_MEM(BPF_DW, BPF_REG_1, BPF_REG_1, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.errstr = "cannot spill",
	.result = REJECT,
पूर्ण,
अणु
	"calls: write into caller stack frame",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_6, 0),
	BPF_EXIT_INSN(),
	BPF_ST_MEM(BPF_DW, BPF_REG_1, 0, 42),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.result = ACCEPT,
	.retval = 42,
पूर्ण,
अणु
	"calls: write into callee stack frame",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 42),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, -8),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.errstr = "cannot return stack pointer",
	.result = REJECT,
पूर्ण,
अणु
	"calls: two calls with stack write and void return",
	.insns = अणु
	/* मुख्य prog */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -16),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),

	/* subprog 2 */
	/* ग_लिखो पूर्णांकo stack frame of मुख्य prog */
	BPF_ST_MEM(BPF_DW, BPF_REG_1, 0, 0),
	BPF_EXIT_INSN(), /* व्योम वापस */
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: ambiguous return value",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 5),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 1),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr_unpriv = "allowed for",
	.result_unpriv = REJECT,
	.errstr = "R0 !read_ok",
	.result = REJECT,
पूर्ण,
अणु
	"calls: two calls that return map_value",
	.insns = अणु
	/* मुख्य prog */
	/* pass fp-16, fp-8 पूर्णांकo a function */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 8),

	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 1),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	/* fetch secound map_value_ptr from the stack */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -16),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 1),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	/* call 3rd function twice */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	/* first समय with fp-8 */
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),
	/* second समय with fp-16 */
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),

	/* subprog 2 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	/* lookup from map */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(), /* वापस 0 */
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.fixup_map_hash_8b = अणु 23 पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: two calls that return map_value with bool condition",
	.insns = अणु
	/* मुख्य prog */
	/* pass fp-16, fp-8 पूर्णांकo a function */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	/* call 3rd function twice */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	/* first समय with fp-8 */
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 9),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_6, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),
	/* second समय with fp-16 */
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 1, 2),
	/* fetch secound map_value_ptr from the stack */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_7, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	BPF_EXIT_INSN(),

	/* subprog 2 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	/* lookup from map */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(), /* वापस 0 */
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(), /* वापस 1 */
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.fixup_map_hash_8b = अणु 23 पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: two calls that return map_value with incorrect bool check",
	.insns = अणु
	/* मुख्य prog */
	/* pass fp-16, fp-8 पूर्णांकo a function */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	/* call 3rd function twice */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	/* first समय with fp-8 */
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 9),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_6, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_7),
	/* second समय with fp-16 */
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	/* fetch secound map_value_ptr from the stack */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_7, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	BPF_EXIT_INSN(),

	/* subprog 2 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	/* lookup from map */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(), /* वापस 0 */
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_0, 1),
	BPF_EXIT_INSN(), /* वापस 1 */
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_XDP,
	.fixup_map_hash_8b = अणु 23 पूर्ण,
	.result = REJECT,
	.errstr = "invalid read from stack R7 off=-16 size=8",
पूर्ण,
अणु
	"calls: two calls that receive map_value via arg=ptr_stack_of_caller. test1",
	.insns = अणु
	/* मुख्य prog */
	/* pass fp-16, fp-8 पूर्णांकo a function */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	/* 1st lookup from map */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_8, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 2),
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog at fp-8 */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_8, 1),

	/* 2nd lookup from map */
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10), /* 20 */
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, /* 24 */
		     BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_9, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 2),
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog at fp-16 */
	BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_9, 1),

	/* call 3rd func with fp-8, 0|1, fp-16, 0|1 */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6), /* 30 */
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_8),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_7),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_9),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),  /* 34 */
	BPF_EXIT_INSN(),

	/* subprog 2 */
	/* अगर arg2 == 1 करो *arg1 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_2, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_1, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),

	/* अगर arg4 == 1 करो *arg3 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_4, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_3, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 2, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.fixup_map_hash_8b = अणु 12, 22 पूर्ण,
	.result = REJECT,
	.errstr = "invalid access to map value, value_size=8 off=2 size=8",
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: two calls that receive map_value via arg=ptr_stack_of_caller. test2",
	.insns = अणु
	/* मुख्य prog */
	/* pass fp-16, fp-8 पूर्णांकo a function */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	/* 1st lookup from map */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_8, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 2),
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog at fp-8 */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_8, 1),

	/* 2nd lookup from map */
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10), /* 20 */
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, /* 24 */
		     BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_9, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 2),
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog at fp-16 */
	BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_9, 1),

	/* call 3rd func with fp-8, 0|1, fp-16, 0|1 */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6), /* 30 */
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_8),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_7),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_9),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),  /* 34 */
	BPF_EXIT_INSN(),

	/* subprog 2 */
	/* अगर arg2 == 1 करो *arg1 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_2, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_1, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),

	/* अगर arg4 == 1 करो *arg3 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_4, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_3, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.fixup_map_hash_8b = अणु 12, 22 पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: two jumps that receive map_value via arg=ptr_stack_of_jumper. test3",
	.insns = अणु
	/* मुख्य prog */
	/* pass fp-16, fp-8 पूर्णांकo a function */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	/* 1st lookup from map */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -24, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -24),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_8, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 2),
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog at fp-8 */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_8, 1),

	/* 2nd lookup from map */
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -24),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_9, 0),  // 26
	BPF_JMP_IMM(BPF_JA, 0, 0, 2),
	/* ग_लिखो map_value_ptr पूर्णांकo stack frame of मुख्य prog at fp-16 */
	BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
	BPF_MOV64_IMM(BPF_REG_9, 1),

	/* call 3rd func with fp-8, 0|1, fp-16, 0|1 */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6), // 30
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_8),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_7),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_9),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_1, 0, 1), // 34
	BPF_JMP_IMM(BPF_JA, 0, 0, -30),

	/* subprog 2 */
	/* अगर arg2 == 1 करो *arg1 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_2, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_1, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),

	/* अगर arg4 == 1 करो *arg3 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_4, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_3, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 2, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, -8),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.fixup_map_hash_8b = अणु 12, 22 पूर्ण,
	.result = REJECT,
	.errstr = "invalid access to map value, value_size=8 off=2 size=8",
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: two calls that receive map_value_ptr_or_null via arg. test1",
	.insns = अणु
	/* मुख्य prog */
	/* pass fp-16, fp-8 पूर्णांकo a function */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	/* 1st lookup from map */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	/* ग_लिखो map_value_ptr_or_null पूर्णांकo stack frame of मुख्य prog at fp-8 */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_8, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_MOV64_IMM(BPF_REG_8, 1),

	/* 2nd lookup from map */
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	/* ग_लिखो map_value_ptr_or_null पूर्णांकo stack frame of मुख्य prog at fp-16 */
	BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_9, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_MOV64_IMM(BPF_REG_9, 1),

	/* call 3rd func with fp-8, 0|1, fp-16, 0|1 */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_8),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_7),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_9),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),

	/* subprog 2 */
	/* अगर arg2 == 1 करो *arg1 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_2, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_1, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),

	/* अगर arg4 == 1 करो *arg3 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_4, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_3, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.fixup_map_hash_8b = अणु 12, 22 पूर्ण,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: two calls that receive map_value_ptr_or_null via arg. test2",
	.insns = अणु
	/* मुख्य prog */
	/* pass fp-16, fp-8 पूर्णांकo a function */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -16),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_MOV64_REG(BPF_REG_7, BPF_REG_2),
	/* 1st lookup from map */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	/* ग_लिखो map_value_ptr_or_null पूर्णांकo stack frame of मुख्य prog at fp-8 */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_8, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_MOV64_IMM(BPF_REG_8, 1),

	/* 2nd lookup from map */
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	/* ग_लिखो map_value_ptr_or_null पूर्णांकo stack frame of मुख्य prog at fp-16 */
	BPF_STX_MEM(BPF_DW, BPF_REG_7, BPF_REG_0, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 2),
	BPF_MOV64_IMM(BPF_REG_9, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 1),
	BPF_MOV64_IMM(BPF_REG_9, 1),

	/* call 3rd func with fp-8, 0|1, fp-16, 0|1 */
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_8),
	BPF_MOV64_REG(BPF_REG_3, BPF_REG_7),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_9),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),

	/* subprog 2 */
	/* अगर arg2 == 1 करो *arg1 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_2, 1, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_1, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),

	/* अगर arg4 == 0 करो *arg3 = 0 */
	BPF_JMP_IMM(BPF_JNE, BPF_REG_4, 0, 2),
	/* fetch map_value_ptr from the stack of this function */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_3, 0),
	/* ग_लिखो पूर्णांकo map value */
	BPF_ST_MEM(BPF_DW, BPF_REG_0, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.fixup_map_hash_8b = अणु 12, 22 पूर्ण,
	.result = REJECT,
	.errstr = "R0 invalid mem access 'inv'",
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 1),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	/* spill unchecked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 2),
	/* now the pkt range is verअगरied, पढ़ो pkt_ptr from stack */
	BPF_LDX_MEM(BPF_DW, BPF_REG_2, BPF_REG_4, 0),
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.retval = POINTER_VALUE,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack 2",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	/* Marking is still kept, but not in all हालs safe. */
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_ST_MEM(BPF_W, BPF_REG_4, 0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	/* spill unchecked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 2),
	/* now the pkt range is verअगरied, पढ़ो pkt_ptr from stack */
	BPF_LDX_MEM(BPF_DW, BPF_REG_2, BPF_REG_4, 0),
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.errstr = "invalid access to packet",
	.result = REJECT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack 3",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2),
	/* Marking is still kept and safe here. */
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_ST_MEM(BPF_W, BPF_REG_4, 0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	/* spill unchecked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_5, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 3),
	BPF_MOV64_IMM(BPF_REG_5, 1),
	/* now the pkt range is verअगरied, पढ़ो pkt_ptr from stack */
	BPF_LDX_MEM(BPF_DW, BPF_REG_2, BPF_REG_4, 0),
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_5),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.retval = 1,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack 4",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 2),
	/* Check marking propagated. */
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_ST_MEM(BPF_W, BPF_REG_4, 0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	/* spill unchecked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_5, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 2),
	BPF_MOV64_IMM(BPF_REG_5, 1),
	/* करोn't पढ़ो back pkt_ptr from stack here */
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_5),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.retval = 1,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack 5",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_4, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_MOV64_IMM(BPF_REG_5, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 3),
	/* spill checked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_5, 1),
	/* करोn't पढ़ो back pkt_ptr from stack here */
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_5),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.errstr = "same insn cannot be used with different",
	.result = REJECT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack 6",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_4, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_MOV64_IMM(BPF_REG_5, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 3),
	/* spill checked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_5, 1),
	/* करोn't पढ़ो back pkt_ptr from stack here */
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_5),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.errstr = "R4 invalid mem access",
	.result = REJECT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack 7",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_2, 0),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_4, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_MOV64_IMM(BPF_REG_5, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 3),
	/* spill checked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_5, 1),
	/* करोn't पढ़ो back pkt_ptr from stack here */
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_5),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.errstr = "R4 invalid mem access",
	.result = REJECT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack 8",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JLE, BPF_REG_0, BPF_REG_3, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_4, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_MOV64_IMM(BPF_REG_5, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 3),
	/* spill checked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_5, 1),
	/* करोn't पढ़ो back pkt_ptr from stack here */
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_5),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.result = ACCEPT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: pkt_ptr spill into caller stack 9",
	.insns = अणु
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_JMP_REG(BPF_JLE, BPF_REG_0, BPF_REG_3, 1),
	BPF_EXIT_INSN(),
	BPF_MOV64_REG(BPF_REG_4, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_4, -8),
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 3),
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_10, -8),
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_4, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data)),
	BPF_LDX_MEM(BPF_W, BPF_REG_3, BPF_REG_1,
		    दुरत्व(काष्ठा __sk_buff, data_end)),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_2),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_0, 8),
	BPF_MOV64_IMM(BPF_REG_5, 0),
	/* spill unchecked pkt_ptr पूर्णांकo stack of caller */
	BPF_STX_MEM(BPF_DW, BPF_REG_4, BPF_REG_2, 0),
	BPF_JMP_REG(BPF_JGT, BPF_REG_0, BPF_REG_3, 2),
	BPF_MOV64_IMM(BPF_REG_5, 1),
	/* करोn't पढ़ो back pkt_ptr from stack here */
	/* ग_लिखो 4 bytes पूर्णांकo packet */
	BPF_ST_MEM(BPF_W, BPF_REG_2, 0, 0),
	BPF_MOV64_REG(BPF_REG_0, BPF_REG_5),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SCHED_CLS,
	.errstr = "invalid access to packet",
	.result = REJECT,
	.flags = F_NEEDS_EFFICIENT_UNALIGNED_ACCESS,
पूर्ण,
अणु
	"calls: caller stack init to zero or map_value_or_null",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0, -8),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	/* fetch map_value_or_null or स्थिर_zero from stack */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_10, -8),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_0, 0, 1),
	/* store पूर्णांकo map_value */
	BPF_ST_MEM(BPF_W, BPF_REG_0, 0, 0),
	BPF_EXIT_INSN(),

	/* subprog 1 */
	/* अगर (ctx == 0) वापस; */
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 8),
	/* अन्यथा bpf_map_lookup() and *(fp - 8) = r0 */
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_2),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	/* ग_लिखो map_value_ptr_or_null पूर्णांकo stack frame of मुख्य prog at fp-8 */
	BPF_STX_MEM(BPF_DW, BPF_REG_6, BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 13 पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_XDP,
पूर्ण,
अणु
	"calls: stack init to zero and pruning",
	.insns = अणु
	/* first make allocated_stack 16 byte */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, 0),
	/* now विभाजन the execution such that the false branch
	 * of JGT insn will be verअगरied second and it skisp zero
	 * init of fp-8 stack slot. If stack liveness marking
	 * is missing live_पढ़ो marks from call map_lookup
	 * processing then pruning will incorrectly assume
	 * that fp-8 stack slot was unused in the fall-through
	 * branch and will accept the program incorrectly
	 */
	BPF_JMP_IMM(BPF_JGT, BPF_REG_1, 2, 2),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	BPF_JMP_IMM(BPF_JA, 0, 0, 0),
	BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),
	BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -8),
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_48b = अणु 6 पूर्ण,
	.errstr = "invalid indirect read from stack R2 off -8+0 size 8",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_XDP,
पूर्ण,
अणु
	"calls: ctx read at start of subprog",
	.insns = अणु
	BPF_MOV64_REG(BPF_REG_6, BPF_REG_1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 5),
	BPF_JMP_REG(BPF_JSGT, BPF_REG_0, BPF_REG_0, 0),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_6),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 2),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_0),
	BPF_EXIT_INSN(),
	BPF_LDX_MEM(BPF_B, BPF_REG_9, BPF_REG_1, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
	.errstr_unpriv = "loading/calling other bpf or kernel functions are allowed for",
	.result_unpriv = REJECT,
	.result = ACCEPT,
पूर्ण,
अणु
	"calls: cross frame pruning",
	.insns = अणु
	/* r8 = !!अक्रमom();
	 * call pruner()
	 * अगर (r8)
	 *     करो something bad;
	 */
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_pअक्रमom_u32),
	BPF_MOV64_IMM(BPF_REG_8, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),
	BPF_MOV64_IMM(BPF_REG_8, 1),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_8),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_8, 1, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_9, BPF_REG_1, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
	.errstr_unpriv = "loading/calling other bpf or kernel functions are allowed for",
	.errstr = "!read_ok",
	.result = REJECT,
पूर्ण,
अणु
	"calls: cross frame pruning - liveness propagation",
	.insns = अणु
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_pअक्रमom_u32),
	BPF_MOV64_IMM(BPF_REG_8, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),
	BPF_MOV64_IMM(BPF_REG_8, 1),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_get_pअक्रमom_u32),
	BPF_MOV64_IMM(BPF_REG_9, 0),
	BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, 1),
	BPF_MOV64_IMM(BPF_REG_9, 1),
	BPF_MOV64_REG(BPF_REG_1, BPF_REG_0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 1, 0, 4),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_8, 1, 1),
	BPF_LDX_MEM(BPF_B, BPF_REG_1, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	BPF_JMP_IMM(BPF_JEQ, BPF_REG_1, 0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.prog_type = BPF_PROG_TYPE_SOCKET_FILTER,
	.errstr_unpriv = "loading/calling other bpf or kernel functions are allowed for",
	.errstr = "!read_ok",
	.result = REJECT,
पूर्ण,
