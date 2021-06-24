<शैली गुरु>
अणु
	"variable-offset ctx access",
	.insns = अणु
	/* Get an unknown value */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	/* add it to skb.  We now have either &skb->len or
	 * &skb->pkt_type, but we करोn't know which
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_1, BPF_REG_2),
	/* dereference it */
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_1, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "variable ctx access var_off=(0x0; 0x4)",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_LWT_IN,
पूर्ण,
अणु
	"variable-offset stack read, priv vs unpriv",
	.insns = अणु
	/* Fill the top 8 bytes of the stack */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	/* Get an unknown value */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 8),
	/* add it to fp.  We now have either fp-4 or fp-8, but
	 * we करोn't know which
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* dereference it क्रम a stack पढ़ो */
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = ACCEPT,
	.result_unpriv = REJECT,
	.errstr_unpriv = "R2 variable stack access prohibited for !root",
	.prog_type = BPF_PROG_TYPE_CGROUP_SKB,
पूर्ण,
अणु
	"variable-offset stack read, uninitialized",
	.insns = अणु
	/* Get an unknown value */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 8),
	/* add it to fp.  We now have either fp-4 or fp-8, but
	 * we करोn't know which
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* dereference it क्रम a stack पढ़ो */
	BPF_LDX_MEM(BPF_W, BPF_REG_0, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.result = REJECT,
	.errstr = "invalid variable-offset read from stack R2",
	.prog_type = BPF_PROG_TYPE_LWT_IN,
पूर्ण,
अणु
	"variable-offset stack write, priv vs unpriv",
	.insns = अणु
	/* Get an unknown value */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 8-byte aligned */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 8),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 16),
	/* Add it to fp.  We now have either fp-8 or fp-16, but
	 * we करोn't know which
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* Dereference it क्रम a stack ग_लिखो */
	BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 0),
	/* Now पढ़ो from the address we just wrote. This shows
	 * that, after a variable-offset ग_लिखो, a priviledged
	 * program can पढ़ो the slots that were in the range of
	 * that ग_लिखो (even अगर the verअगरier करोesn't actually know
	 * अगर the slot being पढ़ो was really written to or not.
	 */
	BPF_LDX_MEM(BPF_DW, BPF_REG_3, BPF_REG_2, 0),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	/* Variable stack access is rejected क्रम unprivileged.
	 */
	.errstr_unpriv = "R2 variable stack access prohibited for !root",
	.result_unpriv = REJECT,
	.result = ACCEPT,
पूर्ण,
अणु
	"variable-offset stack write clobbers spilled regs",
	.insns = अणु
	/* Dummy inकाष्ठाion; needed because we need to patch the next one
	 * and we can't patch the first inकाष्ठाion.
	 */
	BPF_MOV64_IMM(BPF_REG_6, 0),
	/* Make R0 a map ptr */
	BPF_LD_MAP_FD(BPF_REG_0, 0),
	/* Get an unknown value */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 8-byte aligned */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 8),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 16),
	/* Add it to fp. We now have either fp-8 or fp-16, but
	 * we करोn't know which.
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* Spill R0(map ptr) पूर्णांकo stack */
	BPF_STX_MEM(BPF_DW, BPF_REG_10, BPF_REG_0, -8),
	/* Dereference the unknown value क्रम a stack ग_लिखो */
	BPF_ST_MEM(BPF_DW, BPF_REG_2, 0, 0),
	/* Fill the रेजिस्टर back पूर्णांकo R2 */
	BPF_LDX_MEM(BPF_DW, BPF_REG_2, BPF_REG_10, -8),
	/* Try to dereference R2 क्रम a memory load */
	BPF_LDX_MEM(BPF_DW, BPF_REG_0, BPF_REG_2, 8),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 1 पूर्ण,
	/* The unpriviledged हाल is not too पूर्णांकeresting; variable
	 * stack access is rejected.
	 */
	.errstr_unpriv = "R2 variable stack access prohibited for !root",
	.result_unpriv = REJECT,
	/* In the priviledged हाल, dereferencing a spilled-and-then-filled
	 * रेजिस्टर is rejected because the previous variable offset stack
	 * ग_लिखो might have overwritten the spilled poपूर्णांकer (i.e. we lose track
	 * of the spilled रेजिस्टर when we analyze the ग_लिखो).
	 */
	.errstr = "R2 invalid mem access 'inv'",
	.result = REJECT,
पूर्ण,
अणु
	"indirect variable-offset stack access, unbounded",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_2, 6),
	BPF_MOV64_IMM(BPF_REG_3, 28),
	/* Fill the top 16 bytes of the stack. */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, 0),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	/* Get an unknown value. */
	BPF_LDX_MEM(BPF_DW, BPF_REG_4, BPF_REG_1, दुरत्व(काष्ठा bpf_sock_ops,
							   bytes_received)),
	/* Check the lower bound but करोn't check the upper one. */
	BPF_JMP_IMM(BPF_JSLT, BPF_REG_4, 0, 4),
	/* Poपूर्णांक the lower bound to initialized stack. Offset is now in range
	 * from fp-16 to fp+0x7fffffffffffffef, i.e. max value is unbounded.
	 */
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_4, 16),
	BPF_ALU64_REG(BPF_ADD, BPF_REG_4, BPF_REG_10),
	BPF_MOV64_IMM(BPF_REG_5, 8),
	/* Dereference it indirectly. */
	BPF_EMIT_CALL(BPF_FUNC_माला_लोockopt),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "invalid unbounded variable-offset indirect access to stack R4",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SOCK_OPS,
पूर्ण,
अणु
	"indirect variable-offset stack access, max out of bound",
	.insns = अणु
	/* Fill the top 8 bytes of the stack */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	/* Get an unknown value */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 8),
	/* add it to fp.  We now have either fp-4 or fp-8, but
	 * we करोn't know which
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* dereference it indirectly */
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 5 पूर्ण,
	.errstr = "invalid variable-offset indirect access to stack R2",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_LWT_IN,
पूर्ण,
अणु
	"indirect variable-offset stack access, min out of bound",
	.insns = अणु
	/* Fill the top 8 bytes of the stack */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	/* Get an unknown value */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 516),
	/* add it to fp.  We now have either fp-516 or fp-512, but
	 * we करोn't know which
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* dereference it indirectly */
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 5 पूर्ण,
	.errstr = "invalid variable-offset indirect access to stack R2",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_LWT_IN,
पूर्ण,
अणु
	"indirect variable-offset stack access, max_off+size > max_initialized",
	.insns = अणु
	/* Fill only the second from top 8 bytes of the stack. */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, 0),
	/* Get an unknown value. */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned. */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 16),
	/* Add it to fp.  We now have either fp-12 or fp-16, but we करोn't know
	 * which. fp-12 size 8 is partially uninitialized stack.
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* Dereference it indirectly. */
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 5 पूर्ण,
	.errstr = "invalid indirect read from stack R2 var_off",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_LWT_IN,
पूर्ण,
अणु
	"indirect variable-offset stack access, min_off < min_initialized",
	.insns = अणु
	/* Fill only the top 8 bytes of the stack. */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	/* Get an unknown value */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned. */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 16),
	/* Add it to fp.  We now have either fp-12 or fp-16, but we करोn't know
	 * which. fp-16 size 8 is partially uninitialized stack.
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* Dereference it indirectly. */
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 5 पूर्ण,
	.errstr = "invalid indirect read from stack R2 var_off",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_LWT_IN,
पूर्ण,
अणु
	"indirect variable-offset stack access, priv vs unpriv",
	.insns = अणु
	/* Fill the top 16 bytes of the stack. */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, 0),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	/* Get an unknown value. */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned. */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 16),
	/* Add it to fp.  We now have either fp-12 or fp-16, we करोn't know
	 * which, but either way it poपूर्णांकs to initialized stack.
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* Dereference it indirectly. */
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 6 पूर्ण,
	.errstr_unpriv = "R2 variable stack access prohibited for !root",
	.result_unpriv = REJECT,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_CGROUP_SKB,
पूर्ण,
अणु
	"indirect variable-offset stack access, uninitialized",
	.insns = अणु
	BPF_MOV64_IMM(BPF_REG_2, 6),
	BPF_MOV64_IMM(BPF_REG_3, 28),
	/* Fill the top 16 bytes of the stack. */
	BPF_ST_MEM(BPF_W, BPF_REG_10, -16, 0),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	/* Get an unknown value. */
	BPF_LDX_MEM(BPF_W, BPF_REG_4, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned. */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_4, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_4, 16),
	/* Add it to fp.  We now have either fp-12 or fp-16, we करोn't know
	 * which, but either way it poपूर्णांकs to initialized stack.
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_4, BPF_REG_10),
	BPF_MOV64_IMM(BPF_REG_5, 8),
	/* Dereference it indirectly. */
	BPF_EMIT_CALL(BPF_FUNC_माला_लोockopt),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.errstr = "invalid indirect read from stack R4 var_off",
	.result = REJECT,
	.prog_type = BPF_PROG_TYPE_SOCK_OPS,
पूर्ण,
अणु
	"indirect variable-offset stack access, ok",
	.insns = अणु
	/* Fill the top 16 bytes of the stack. */
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -16, 0),
	BPF_ST_MEM(BPF_DW, BPF_REG_10, -8, 0),
	/* Get an unknown value. */
	BPF_LDX_MEM(BPF_W, BPF_REG_2, BPF_REG_1, 0),
	/* Make it small and 4-byte aligned. */
	BPF_ALU64_IMM(BPF_AND, BPF_REG_2, 4),
	BPF_ALU64_IMM(BPF_SUB, BPF_REG_2, 16),
	/* Add it to fp.  We now have either fp-12 or fp-16, we करोn't know
	 * which, but either way it poपूर्णांकs to initialized stack.
	 */
	BPF_ALU64_REG(BPF_ADD, BPF_REG_2, BPF_REG_10),
	/* Dereference it indirectly. */
	BPF_LD_MAP_FD(BPF_REG_1, 0),
	BPF_EMIT_CALL(BPF_FUNC_map_lookup_elem),
	BPF_MOV64_IMM(BPF_REG_0, 0),
	BPF_EXIT_INSN(),
	पूर्ण,
	.fixup_map_hash_8b = अणु 6 पूर्ण,
	.result = ACCEPT,
	.prog_type = BPF_PROG_TYPE_LWT_IN,
पूर्ण,
