<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * bpf-prologue.c
 *
 * Copyright (C) 2015 He Kuang <hekuang@huawei.com>
 * Copyright (C) 2015 Wang Nan <wangnan0@huawei.com>
 * Copyright (C) 2015 Huawei Inc.
 */

#समावेश <bpf/libbpf.h>
#समावेश "debug.h"
#समावेश "bpf-loader.h"
#समावेश "bpf-prologue.h"
#समावेश "probe-finder.h"
#समावेश <त्रुटिसं.स>
#समावेश <मानककोष.स>
#समावेश <dwarf-regs.h>
#समावेश <linux/filter.h>

#घोषणा BPF_REG_SIZE		8

#घोषणा JMP_TO_ERROR_CODE	-1
#घोषणा JMP_TO_SUCCESS_CODE	-2
#घोषणा JMP_TO_USER_CODE	-3

काष्ठा bpf_insn_pos अणु
	काष्ठा bpf_insn *begin;
	काष्ठा bpf_insn *end;
	काष्ठा bpf_insn *pos;
पूर्ण;

अटल अंतरभूत पूर्णांक
pos_get_cnt(काष्ठा bpf_insn_pos *pos)
अणु
	वापस pos->pos - pos->begin;
पूर्ण

अटल पूर्णांक
append_insn(काष्ठा bpf_insn new_insn, काष्ठा bpf_insn_pos *pos)
अणु
	अगर (!pos->pos)
		वापस -BPF_LOADER_ERRNO__PROLOGUE2BIG;

	अगर (pos->pos + 1 >= pos->end) अणु
		pr_err("bpf prologue: prologue too long\n");
		pos->pos = शून्य;
		वापस -BPF_LOADER_ERRNO__PROLOGUE2BIG;
	पूर्ण

	*(pos->pos)++ = new_insn;
	वापस 0;
पूर्ण

अटल पूर्णांक
check_pos(काष्ठा bpf_insn_pos *pos)
अणु
	अगर (!pos->pos || pos->pos >= pos->end)
		वापस -BPF_LOADER_ERRNO__PROLOGUE2BIG;
	वापस 0;
पूर्ण

/*
 * Convert type string (u8/u16/u32/u64/s8/s16/s32/s64 ..., see
 * Documentation/trace/kprobetrace.rst) to size field of BPF_LDX_MEM
 * inकाष्ठाion (BPF_अणुB,H,W,DWपूर्ण).
 */
अटल पूर्णांक
argtype_to_ldx_size(स्थिर अक्षर *type)
अणु
	पूर्णांक arg_size = type ? म_से_प(&type[1]) : 64;

	चयन (arg_size) अणु
	हाल 8:
		वापस BPF_B;
	हाल 16:
		वापस BPF_H;
	हाल 32:
		वापस BPF_W;
	हाल 64:
	शेष:
		वापस BPF_DW;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *
insn_sz_to_str(पूर्णांक insn_sz)
अणु
	चयन (insn_sz) अणु
	हाल BPF_B:
		वापस "BPF_B";
	हाल BPF_H:
		वापस "BPF_H";
	हाल BPF_W:
		वापस "BPF_W";
	हाल BPF_DW:
		वापस "BPF_DW";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

/* Give it a लघुer name */
#घोषणा ins(i, p) append_insn((i), (p))

/*
 * Give a रेजिस्टर name (in 'reg'), generate inकाष्ठाion to
 * load रेजिस्टर पूर्णांकo an eBPF रेजिस्टर rd:
 *   'ldd target_reg, offset(ctx_reg)', where:
 * ctx_reg is pre initialized to poपूर्णांकer of 'struct pt_regs'.
 */
अटल पूर्णांक
gen_ldx_reg_from_ctx(काष्ठा bpf_insn_pos *pos, पूर्णांक ctx_reg,
		     स्थिर अक्षर *reg, पूर्णांक target_reg)
अणु
	पूर्णांक offset = regs_query_रेजिस्टर_offset(reg);

	अगर (offset < 0) अणु
		pr_err("bpf: prologue: failed to get register %s\n",
		       reg);
		वापस offset;
	पूर्ण
	ins(BPF_LDX_MEM(BPF_DW, target_reg, ctx_reg, offset), pos);

	वापस check_pos(pos);
पूर्ण

/*
 * Generate a BPF_FUNC_probe_पढ़ो function call.
 *
 * src_base_addr_reg is a रेजिस्टर holding base address,
 * dst_addr_reg is a रेजिस्टर holding dest address (on stack),
 * result is:
 *
 *  *[dst_addr_reg] = *([src_base_addr_reg] + offset)
 *
 * Arguments of BPF_FUNC_probe_पढ़ो:
 *     ARG1: ptr to stack (dest)
 *     ARG2: size (8)
 *     ARG3: unsafe ptr (src)
 */
अटल पूर्णांक
gen_पढ़ो_mem(काष्ठा bpf_insn_pos *pos,
	     पूर्णांक src_base_addr_reg,
	     पूर्णांक dst_addr_reg,
	     दीर्घ offset,
	     पूर्णांक probeid)
अणु
	/* mov arg3, src_base_addr_reg */
	अगर (src_base_addr_reg != BPF_REG_ARG3)
		ins(BPF_MOV64_REG(BPF_REG_ARG3, src_base_addr_reg), pos);
	/* add arg3, #offset */
	अगर (offset)
		ins(BPF_ALU64_IMM(BPF_ADD, BPF_REG_ARG3, offset), pos);

	/* mov arg2, #reg_size */
	ins(BPF_ALU64_IMM(BPF_MOV, BPF_REG_ARG2, BPF_REG_SIZE), pos);

	/* mov arg1, dst_addr_reg */
	अगर (dst_addr_reg != BPF_REG_ARG1)
		ins(BPF_MOV64_REG(BPF_REG_ARG1, dst_addr_reg), pos);

	/* Call probe_पढ़ो  */
	ins(BPF_EMIT_CALL(probeid), pos);
	/*
	 * Error processing: अगर पढ़ो fail, जाओ error code,
	 * will be relocated. Target should be the start of
	 * error processing code.
	 */
	ins(BPF_JMP_IMM(BPF_JNE, BPF_REG_0, 0, JMP_TO_ERROR_CODE),
	    pos);

	वापस check_pos(pos);
पूर्ण

/*
 * Each arg should be bare रेजिस्टर. Fetch and save them पूर्णांकo argument
 * रेजिस्टरs (r3 - r5).
 *
 * BPF_REG_1 should have been initialized with poपूर्णांकer to
 * 'struct pt_regs'.
 */
अटल पूर्णांक
gen_prologue_fastpath(काष्ठा bpf_insn_pos *pos,
		      काष्ठा probe_trace_arg *args, पूर्णांक nargs)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < nargs; i++) अणु
		err = gen_ldx_reg_from_ctx(pos, BPF_REG_1, args[i].value,
					   BPF_PROLOGUE_START_ARG_REG + i);
		अगर (err)
			जाओ errout;
	पूर्ण

	वापस check_pos(pos);
errout:
	वापस err;
पूर्ण

/*
 * Slow path:
 *   At least one argument has the क्रमm of 'offset($rx)'.
 *
 * Following code first stores them पूर्णांकo stack, then loads all of then
 * to r2 - r5.
 * Beक्रमe final loading, the final result should be:
 *
 * low address
 * BPF_REG_FP - 24  ARG3
 * BPF_REG_FP - 16  ARG2
 * BPF_REG_FP - 8   ARG1
 * BPF_REG_FP
 * high address
 *
 * For each argument (described as: offn(...off2(off1(reg)))),
 * generates following code:
 *
 *  r7 <- fp
 *  r7 <- r7 - stack_offset  // Ideal code should initialize r7 using
 *                           // fp beक्रमe generating args. However,
 *                           // eBPF won't regard r7 as stack poपूर्णांकer
 *                           // अगर it is generated by minus 8 from
 *                           // another stack poपूर्णांकer except fp.
 *                           // This is why we have to set r7
 *                           // to fp क्रम each variable.
 *  r3 <- value of 'reg'-> generated using gen_ldx_reg_from_ctx()
 *  (r7) <- r3       // skip following inकाष्ठाions क्रम bare reg
 *  r3 <- r3 + off1  . // skip अगर off1 == 0
 *  r2 <- 8           \
 *  r1 <- r7           |-> generated by gen_पढ़ो_mem()
 *  call probe_पढ़ो    /
 *  jnei r0, 0, err  ./
 *  r3 <- (r7)
 *  r3 <- r3 + off2  . // skip अगर off2 == 0
 *  r2 <- 8           \  // r2 may be broken by probe_पढ़ो, so set again
 *  r1 <- r7           |-> generated by gen_पढ़ो_mem()
 *  call probe_पढ़ो    /
 *  jnei r0, 0, err  ./
 *  ...
 */
अटल पूर्णांक
gen_prologue_slowpath(काष्ठा bpf_insn_pos *pos,
		      काष्ठा probe_trace_arg *args, पूर्णांक nargs)
अणु
	पूर्णांक err, i, probeid;

	क्रम (i = 0; i < nargs; i++) अणु
		काष्ठा probe_trace_arg *arg = &args[i];
		स्थिर अक्षर *reg = arg->value;
		काष्ठा probe_trace_arg_ref *ref = शून्य;
		पूर्णांक stack_offset = (i + 1) * -8;

		pr_debug("prologue: fetch arg %d, base reg is %s\n",
			 i, reg);

		/* value of base रेजिस्टर is stored पूर्णांकo ARG3 */
		err = gen_ldx_reg_from_ctx(pos, BPF_REG_CTX, reg,
					   BPF_REG_ARG3);
		अगर (err) अणु
			pr_err("prologue: failed to get offset of register %s\n",
			       reg);
			जाओ errout;
		पूर्ण

		/* Make r7 the stack poपूर्णांकer. */
		ins(BPF_MOV64_REG(BPF_REG_7, BPF_REG_FP), pos);
		/* r7 += -8 */
		ins(BPF_ALU64_IMM(BPF_ADD, BPF_REG_7, stack_offset), pos);
		/*
		 * Store r3 (base रेजिस्टर) onto stack
		 * Ensure fp[offset] is set.
		 * fp is the only valid base रेजिस्टर when storing
		 * पूर्णांकo stack. We are not allowed to use r7 as base
		 * रेजिस्टर here.
		 */
		ins(BPF_STX_MEM(BPF_DW, BPF_REG_FP, BPF_REG_ARG3,
				stack_offset), pos);

		ref = arg->ref;
		probeid = BPF_FUNC_probe_पढ़ो_kernel;
		जबतक (ref) अणु
			pr_debug("prologue: arg %d: offset %ld\n",
				 i, ref->offset);

			अगर (ref->user_access)
				probeid = BPF_FUNC_probe_पढ़ो_user;

			err = gen_पढ़ो_mem(pos, BPF_REG_3, BPF_REG_7,
					   ref->offset, probeid);
			अगर (err) अणु
				pr_err("prologue: failed to generate probe_read function call\n");
				जाओ errout;
			पूर्ण

			ref = ref->next;
			/*
			 * Load previous result पूर्णांकo ARG3. Use
			 * BPF_REG_FP instead of r7 because verअगरier
			 * allows FP based addressing only.
			 */
			अगर (ref)
				ins(BPF_LDX_MEM(BPF_DW, BPF_REG_ARG3,
						BPF_REG_FP, stack_offset), pos);
		पूर्ण
	पूर्ण

	/* Final pass: पढ़ो to रेजिस्टरs */
	क्रम (i = 0; i < nargs; i++) अणु
		पूर्णांक insn_sz = (args[i].ref) ? argtype_to_ldx_size(args[i].type) : BPF_DW;

		pr_debug("prologue: load arg %d, insn_sz is %s\n",
			 i, insn_sz_to_str(insn_sz));
		ins(BPF_LDX_MEM(insn_sz, BPF_PROLOGUE_START_ARG_REG + i,
				BPF_REG_FP, -BPF_REG_SIZE * (i + 1)), pos);
	पूर्ण

	ins(BPF_JMP_IMM(BPF_JA, BPF_REG_0, 0, JMP_TO_SUCCESS_CODE), pos);

	वापस check_pos(pos);
errout:
	वापस err;
पूर्ण

अटल पूर्णांक
prologue_relocate(काष्ठा bpf_insn_pos *pos, काष्ठा bpf_insn *error_code,
		  काष्ठा bpf_insn *success_code, काष्ठा bpf_insn *user_code)
अणु
	काष्ठा bpf_insn *insn;

	अगर (check_pos(pos))
		वापस -BPF_LOADER_ERRNO__PROLOGUE2BIG;

	क्रम (insn = pos->begin; insn < pos->pos; insn++) अणु
		काष्ठा bpf_insn *target;
		u8 class = BPF_CLASS(insn->code);
		u8 opcode;

		अगर (class != BPF_JMP)
			जारी;
		opcode = BPF_OP(insn->code);
		अगर (opcode == BPF_CALL)
			जारी;

		चयन (insn->off) अणु
		हाल JMP_TO_ERROR_CODE:
			target = error_code;
			अवरोध;
		हाल JMP_TO_SUCCESS_CODE:
			target = success_code;
			अवरोध;
		हाल JMP_TO_USER_CODE:
			target = user_code;
			अवरोध;
		शेष:
			pr_err("bpf prologue: internal error: relocation failed\n");
			वापस -BPF_LOADER_ERRNO__PROLOGUE;
		पूर्ण

		insn->off = target - (insn + 1);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक bpf__gen_prologue(काष्ठा probe_trace_arg *args, पूर्णांक nargs,
		      काष्ठा bpf_insn *new_prog, माप_प्रकार *new_cnt,
		      माप_प्रकार cnt_space)
अणु
	काष्ठा bpf_insn *success_code = शून्य;
	काष्ठा bpf_insn *error_code = शून्य;
	काष्ठा bpf_insn *user_code = शून्य;
	काष्ठा bpf_insn_pos pos;
	bool fastpath = true;
	पूर्णांक err = 0, i;

	अगर (!new_prog || !new_cnt)
		वापस -EINVAL;

	अगर (cnt_space > BPF_MAXINSNS)
		cnt_space = BPF_MAXINSNS;

	pos.begin = new_prog;
	pos.end = new_prog + cnt_space;
	pos.pos = new_prog;

	अगर (!nargs) अणु
		ins(BPF_ALU64_IMM(BPF_MOV, BPF_PROLOGUE_FETCH_RESULT_REG, 0),
		    &pos);

		अगर (check_pos(&pos))
			जाओ errout;

		*new_cnt = pos_get_cnt(&pos);
		वापस 0;
	पूर्ण

	अगर (nargs > BPF_PROLOGUE_MAX_ARGS) अणु
		pr_warning("bpf: prologue: %d arguments are dropped\n",
			   nargs - BPF_PROLOGUE_MAX_ARGS);
		nargs = BPF_PROLOGUE_MAX_ARGS;
	पूर्ण

	/* First pass: validation */
	क्रम (i = 0; i < nargs; i++) अणु
		काष्ठा probe_trace_arg_ref *ref = args[i].ref;

		अगर (args[i].value[0] == '@') अणु
			/* TODO: fetch global variable */
			pr_err("bpf: prologue: global %s%+ld not support\n",
				args[i].value, ref ? ref->offset : 0);
			वापस -ENOTSUP;
		पूर्ण

		जबतक (ref) अणु
			/* fastpath is true अगर all args has ref == शून्य */
			fastpath = false;

			/*
			 * Inकाष्ठाion encodes immediate value using
			 * s32, ref->offset is दीर्घ. On प्रणालीs which
			 * can't fill दीर्घ in s32, refuse to process अगर
			 * ref->offset too large (or small).
			 */
#अगर_घोषित __LP64__
#घोषणा OFFSET_MAX	((1LL << 31) - 1)
#घोषणा OFFSET_MIN	((1LL << 31) * -1)
			अगर (ref->offset > OFFSET_MAX ||
					ref->offset < OFFSET_MIN) अणु
				pr_err("bpf: prologue: offset out of bound: %ld\n",
				       ref->offset);
				वापस -BPF_LOADER_ERRNO__PROLOGUEOOB;
			पूर्ण
#पूर्ण_अगर
			ref = ref->next;
		पूर्ण
	पूर्ण
	pr_debug("prologue: pass validation\n");

	अगर (fastpath) अणु
		/* If all variables are रेजिस्टरs... */
		pr_debug("prologue: fast path\n");
		err = gen_prologue_fastpath(&pos, args, nargs);
		अगर (err)
			जाओ errout;
	पूर्ण अन्यथा अणु
		pr_debug("prologue: slow path\n");

		/* Initialization: move ctx to a callee saved रेजिस्टर. */
		ins(BPF_MOV64_REG(BPF_REG_CTX, BPF_REG_ARG1), &pos);

		err = gen_prologue_slowpath(&pos, args, nargs);
		अगर (err)
			जाओ errout;
		/*
		 * start of ERROR_CODE (only slow pass needs error code)
		 *   mov r2 <- 1  // r2 is error number
		 *   mov r3 <- 0  // r3, r4... should be touched or
		 *                // verअगरier would complain
		 *   mov r4 <- 0
		 *   ...
		 *   जाओ usercode
		 */
		error_code = pos.pos;
		ins(BPF_ALU64_IMM(BPF_MOV, BPF_PROLOGUE_FETCH_RESULT_REG, 1),
		    &pos);

		क्रम (i = 0; i < nargs; i++)
			ins(BPF_ALU64_IMM(BPF_MOV,
					  BPF_PROLOGUE_START_ARG_REG + i,
					  0),
			    &pos);
		ins(BPF_JMP_IMM(BPF_JA, BPF_REG_0, 0, JMP_TO_USER_CODE),
				&pos);
	पूर्ण

	/*
	 * start of SUCCESS_CODE:
	 *   mov r2 <- 0
	 *   जाओ usercode  // skip
	 */
	success_code = pos.pos;
	ins(BPF_ALU64_IMM(BPF_MOV, BPF_PROLOGUE_FETCH_RESULT_REG, 0), &pos);

	/*
	 * start of USER_CODE:
	 *   Restore ctx to r1
	 */
	user_code = pos.pos;
	अगर (!fastpath) अणु
		/*
		 * Only slow path needs restoring of ctx. In fast path,
		 * रेजिस्टर are loaded directly from r1.
		 */
		ins(BPF_MOV64_REG(BPF_REG_ARG1, BPF_REG_CTX), &pos);
		err = prologue_relocate(&pos, error_code, success_code,
					user_code);
		अगर (err)
			जाओ errout;
	पूर्ण

	err = check_pos(&pos);
	अगर (err)
		जाओ errout;

	*new_cnt = pos_get_cnt(&pos);
	वापस 0;
errout:
	वापस err;
पूर्ण
