<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 * Copyright (c) 2016 Facebook
 * Copyright (c) 2018 Covalent IO, Inc. http://covalent.io
 */
#समावेश <uapi/linux/btf.h>
#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/bpf.h>
#समावेश <linux/btf.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <linux/filter.h>
#समावेश <net/netlink.h>
#समावेश <linux/file.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/stringअगरy.h>
#समावेश <linux/द्वा_खोज.h>
#समावेश <linux/sort.h>
#समावेश <linux/perf_event.h>
#समावेश <linux/प्रकार.स>
#समावेश <linux/error-injection.h>
#समावेश <linux/bpf_lsm.h>
#समावेश <linux/btf_ids.h>

#समावेश "disasm.h"

अटल स्थिर काष्ठा bpf_verअगरier_ops * स्थिर bpf_verअगरier_ops[] = अणु
#घोषणा BPF_PROG_TYPE(_id, _name, prog_ctx_type, kern_ctx_type) \
	[_id] = & _name ## _verअगरier_ops,
#घोषणा BPF_MAP_TYPE(_id, _ops)
#घोषणा BPF_LINK_TYPE(_id, _name)
#समावेश <linux/bpf_types.h>
#अघोषित BPF_PROG_TYPE
#अघोषित BPF_MAP_TYPE
#अघोषित BPF_LINK_TYPE
पूर्ण;

/* bpf_check() is a अटल code analyzer that walks eBPF program
 * inकाष्ठाion by inकाष्ठाion and updates रेजिस्टर/stack state.
 * All paths of conditional branches are analyzed until 'bpf_exit' insn.
 *
 * The first pass is depth-first-search to check that the program is a DAG.
 * It rejects the following programs:
 * - larger than BPF_MAXINSNS insns
 * - अगर loop is present (detected via back-edge)
 * - unreachable insns exist (shouldn't be a क्रमest. program = one function)
 * - out of bounds or malक्रमmed jumps
 * The second pass is all possible path descent from the 1st insn.
 * Since it's analyzing all pathes through the program, the length of the
 * analysis is limited to 64k insn, which may be hit even अगर total number of
 * insn is less then 4K, but there are too many branches that change stack/regs.
 * Number of 'branches to be analyzed' is limited to 1k
 *
 * On entry to each inकाष्ठाion, each रेजिस्टर has a type, and the inकाष्ठाion
 * changes the types of the रेजिस्टरs depending on inकाष्ठाion semantics.
 * If inकाष्ठाion is BPF_MOV64_REG(BPF_REG_1, BPF_REG_5), then type of R5 is
 * copied to R1.
 *
 * All रेजिस्टरs are 64-bit.
 * R0 - वापस रेजिस्टर
 * R1-R5 argument passing रेजिस्टरs
 * R6-R9 callee saved रेजिस्टरs
 * R10 - frame poपूर्णांकer पढ़ो-only
 *
 * At the start of BPF program the रेजिस्टर R1 contains a poपूर्णांकer to bpf_context
 * and has type PTR_TO_CTX.
 *
 * Verअगरier tracks arithmetic operations on poपूर्णांकers in हाल:
 *    BPF_MOV64_REG(BPF_REG_1, BPF_REG_10),
 *    BPF_ALU64_IMM(BPF_ADD, BPF_REG_1, -20),
 * 1st insn copies R10 (which has FRAME_PTR) type पूर्णांकo R1
 * and 2nd arithmetic inकाष्ठाion is pattern matched to recognize
 * that it wants to स्थिरruct a poपूर्णांकer to some element within stack.
 * So after 2nd insn, the रेजिस्टर R1 has type PTR_TO_STACK
 * (and -20 स्थिरant is saved क्रम further stack bounds checking).
 * Meaning that this reg is a poपूर्णांकer to stack plus known immediate स्थिरant.
 *
 * Most of the समय the रेजिस्टरs have SCALAR_VALUE type, which
 * means the रेजिस्टर has some value, but it's not a valid poपूर्णांकer.
 * (like poपूर्णांकer plus poपूर्णांकer becomes SCALAR_VALUE type)
 *
 * When verअगरier sees load or store inकाष्ठाions the type of base रेजिस्टर
 * can be: PTR_TO_MAP_VALUE, PTR_TO_CTX, PTR_TO_STACK, PTR_TO_SOCKET. These are
 * four poपूर्णांकer types recognized by check_mem_access() function.
 *
 * PTR_TO_MAP_VALUE means that this रेजिस्टर is poपूर्णांकing to 'map element value'
 * and the range of [ptr, ptr + map's value_size) is accessible.
 *
 * रेजिस्टरs used to pass values to function calls are checked against
 * function argument स्थिरraपूर्णांकs.
 *
 * ARG_PTR_TO_MAP_KEY is one of such argument स्थिरraपूर्णांकs.
 * It means that the रेजिस्टर type passed to this function must be
 * PTR_TO_STACK and it will be used inside the function as
 * 'pointer to map element key'
 *
 * For example the argument स्थिरraपूर्णांकs क्रम bpf_map_lookup_elem():
 *   .ret_type = RET_PTR_TO_MAP_VALUE_OR_शून्य,
 *   .arg1_type = ARG_CONST_MAP_PTR,
 *   .arg2_type = ARG_PTR_TO_MAP_KEY,
 *
 * ret_type says that this function वापसs 'pointer to map elem value or null'
 * function expects 1st argument to be a स्थिर poपूर्णांकer to 'struct bpf_map' and
 * 2nd argument should be a poपूर्णांकer to stack, which will be used inside
 * the helper function as a poपूर्णांकer to map element key.
 *
 * On the kernel side the helper function looks like:
 * u64 bpf_map_lookup_elem(u64 r1, u64 r2, u64 r3, u64 r4, u64 r5)
 * अणु
 *    काष्ठा bpf_map *map = (काष्ठा bpf_map *) (अचिन्हित दीर्घ) r1;
 *    व्योम *key = (व्योम *) (अचिन्हित दीर्घ) r2;
 *    व्योम *value;
 *
 *    here kernel can access 'key' and 'map' poपूर्णांकers safely, knowing that
 *    [key, key + map->key_size) bytes are valid and were initialized on
 *    the stack of eBPF program.
 * पूर्ण
 *
 * Corresponding eBPF program may look like:
 *    BPF_MOV64_REG(BPF_REG_2, BPF_REG_10),  // after this insn R2 type is FRAME_PTR
 *    BPF_ALU64_IMM(BPF_ADD, BPF_REG_2, -4), // after this insn R2 type is PTR_TO_STACK
 *    BPF_LD_MAP_FD(BPF_REG_1, map_fd),      // after this insn R1 type is CONST_PTR_TO_MAP
 *    BPF_RAW_INSN(BPF_JMP | BPF_CALL, 0, 0, 0, BPF_FUNC_map_lookup_elem),
 * here verअगरier looks at prototype of map_lookup_elem() and sees:
 * .arg1_type == ARG_CONST_MAP_PTR and R1->type == CONST_PTR_TO_MAP, which is ok,
 * Now verअगरier knows that this map has key of R1->map_ptr->key_size bytes
 *
 * Then .arg2_type == ARG_PTR_TO_MAP_KEY and R2->type == PTR_TO_STACK, ok so far,
 * Now verअगरier checks that [R2, R2 + map's key_size) are within stack limits
 * and were initialized prior to this call.
 * If it's ok, then verअगरier allows this BPF_CALL insn and looks at
 * .ret_type which is RET_PTR_TO_MAP_VALUE_OR_शून्य, so it sets
 * R0->type = PTR_TO_MAP_VALUE_OR_शून्य which means bpf_map_lookup_elem() function
 * वापसs ether poपूर्णांकer to map value or शून्य.
 *
 * When type PTR_TO_MAP_VALUE_OR_शून्य passes through 'if (reg != 0) goto +off'
 * insn, the रेजिस्टर holding that poपूर्णांकer in the true branch changes state to
 * PTR_TO_MAP_VALUE and the same रेजिस्टर changes state to CONST_IMM in the false
 * branch. See check_cond_jmp_op().
 *
 * After the call R0 is set to वापस type of the function and रेजिस्टरs R1-R5
 * are set to NOT_INIT to indicate that they are no दीर्घer पढ़ोable.
 *
 * The following reference types represent a potential reference to a kernel
 * resource which, after first being allocated, must be checked and मुक्तd by
 * the BPF program:
 * - PTR_TO_SOCKET_OR_शून्य, PTR_TO_SOCKET
 *
 * When the verअगरier sees a helper call वापस a reference type, it allocates a
 * poपूर्णांकer id क्रम the reference and stores it in the current function state.
 * Similar to the way that PTR_TO_MAP_VALUE_OR_शून्य is converted पूर्णांकo
 * PTR_TO_MAP_VALUE, PTR_TO_SOCKET_OR_शून्य becomes PTR_TO_SOCKET when the type
 * passes through a शून्य-check conditional. For the branch wherein the state is
 * changed to CONST_IMM, the verअगरier releases the reference.
 *
 * For each helper function that allocates a reference, such as
 * bpf_sk_lookup_tcp(), there is a corresponding release function, such as
 * bpf_sk_release(). When a reference type passes पूर्णांकo the release function,
 * the verअगरier also releases the reference. If any unchecked or unreleased
 * reference reमुख्यs at the end of the program, the verअगरier rejects it.
 */

/* verअगरier_state + insn_idx are pushed to stack when branch is encountered */
काष्ठा bpf_verअगरier_stack_elem अणु
	/* verअगरer state is 'st'
	 * beक्रमe processing inकाष्ठाion 'insn_idx'
	 * and after processing inकाष्ठाion 'prev_insn_idx'
	 */
	काष्ठा bpf_verअगरier_state st;
	पूर्णांक insn_idx;
	पूर्णांक prev_insn_idx;
	काष्ठा bpf_verअगरier_stack_elem *next;
	/* length of verअगरier log at the समय this state was pushed on stack */
	u32 log_pos;
पूर्ण;

#घोषणा BPF_COMPLEXITY_LIMIT_JMP_SEQ	8192
#घोषणा BPF_COMPLEXITY_LIMIT_STATES	64

#घोषणा BPF_MAP_KEY_POISON	(1ULL << 63)
#घोषणा BPF_MAP_KEY_SEEN	(1ULL << 62)

#घोषणा BPF_MAP_PTR_UNPRIV	1UL
#घोषणा BPF_MAP_PTR_POISON	((व्योम *)((0xeB9FUL << 1) +	\
					  POISON_POINTER_DELTA))
#घोषणा BPF_MAP_PTR(X)		((काष्ठा bpf_map *)((X) & ~BPF_MAP_PTR_UNPRIV))

अटल bool bpf_map_ptr_poisoned(स्थिर काष्ठा bpf_insn_aux_data *aux)
अणु
	वापस BPF_MAP_PTR(aux->map_ptr_state) == BPF_MAP_PTR_POISON;
पूर्ण

अटल bool bpf_map_ptr_unpriv(स्थिर काष्ठा bpf_insn_aux_data *aux)
अणु
	वापस aux->map_ptr_state & BPF_MAP_PTR_UNPRIV;
पूर्ण

अटल व्योम bpf_map_ptr_store(काष्ठा bpf_insn_aux_data *aux,
			      स्थिर काष्ठा bpf_map *map, bool unpriv)
अणु
	BUILD_BUG_ON((अचिन्हित दीर्घ)BPF_MAP_PTR_POISON & BPF_MAP_PTR_UNPRIV);
	unpriv |= bpf_map_ptr_unpriv(aux);
	aux->map_ptr_state = (अचिन्हित दीर्घ)map |
			     (unpriv ? BPF_MAP_PTR_UNPRIV : 0UL);
पूर्ण

अटल bool bpf_map_key_poisoned(स्थिर काष्ठा bpf_insn_aux_data *aux)
अणु
	वापस aux->map_key_state & BPF_MAP_KEY_POISON;
पूर्ण

अटल bool bpf_map_key_unseen(स्थिर काष्ठा bpf_insn_aux_data *aux)
अणु
	वापस !(aux->map_key_state & BPF_MAP_KEY_SEEN);
पूर्ण

अटल u64 bpf_map_key_immediate(स्थिर काष्ठा bpf_insn_aux_data *aux)
अणु
	वापस aux->map_key_state & ~(BPF_MAP_KEY_SEEN | BPF_MAP_KEY_POISON);
पूर्ण

अटल व्योम bpf_map_key_store(काष्ठा bpf_insn_aux_data *aux, u64 state)
अणु
	bool poisoned = bpf_map_key_poisoned(aux);

	aux->map_key_state = state | BPF_MAP_KEY_SEEN |
			     (poisoned ? BPF_MAP_KEY_POISON : 0ULL);
पूर्ण

अटल bool bpf_pseuकरो_call(स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस insn->code == (BPF_JMP | BPF_CALL) &&
	       insn->src_reg == BPF_PSEUDO_CALL;
पूर्ण

अटल bool bpf_pseuकरो_kfunc_call(स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस insn->code == (BPF_JMP | BPF_CALL) &&
	       insn->src_reg == BPF_PSEUDO_KFUNC_CALL;
पूर्ण

अटल bool bpf_pseuकरो_func(स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस insn->code == (BPF_LD | BPF_IMM | BPF_DW) &&
	       insn->src_reg == BPF_PSEUDO_FUNC;
पूर्ण

काष्ठा bpf_call_arg_meta अणु
	काष्ठा bpf_map *map_ptr;
	bool raw_mode;
	bool pkt_access;
	पूर्णांक regno;
	पूर्णांक access_size;
	पूर्णांक mem_size;
	u64 msize_max_value;
	पूर्णांक ref_obj_id;
	पूर्णांक func_id;
	काष्ठा btf *btf;
	u32 btf_id;
	काष्ठा btf *ret_btf;
	u32 ret_btf_id;
	u32 subprogno;
पूर्ण;

काष्ठा btf *btf_vmlinux;

अटल DEFINE_MUTEX(bpf_verअगरier_lock);

अटल स्थिर काष्ठा bpf_line_info *
find_linfo(स्थिर काष्ठा bpf_verअगरier_env *env, u32 insn_off)
अणु
	स्थिर काष्ठा bpf_line_info *linfo;
	स्थिर काष्ठा bpf_prog *prog;
	u32 i, nr_linfo;

	prog = env->prog;
	nr_linfo = prog->aux->nr_linfo;

	अगर (!nr_linfo || insn_off >= prog->len)
		वापस शून्य;

	linfo = prog->aux->linfo;
	क्रम (i = 1; i < nr_linfo; i++)
		अगर (insn_off < linfo[i].insn_off)
			अवरोध;

	वापस &linfo[i - 1];
पूर्ण

व्योम bpf_verअगरier_vlog(काष्ठा bpf_verअगरier_log *log, स्थिर अक्षर *fmt,
		       बहु_सूची args)
अणु
	अचिन्हित पूर्णांक n;

	n = vscnम_लिखो(log->kbuf, BPF_VERIFIER_TMP_LOG_SIZE, fmt, args);

	WARN_ONCE(n >= BPF_VERIFIER_TMP_LOG_SIZE - 1,
		  "verifier log line truncated - local buffer too short\n");

	n = min(log->len_total - log->len_used - 1, n);
	log->kbuf[n] = '\0';

	अगर (log->level == BPF_LOG_KERNEL) अणु
		pr_err("BPF:%s\n", log->kbuf);
		वापस;
	पूर्ण
	अगर (!copy_to_user(log->ubuf + log->len_used, log->kbuf, n + 1))
		log->len_used += n;
	अन्यथा
		log->ubuf = शून्य;
पूर्ण

अटल व्योम bpf_vlog_reset(काष्ठा bpf_verअगरier_log *log, u32 new_pos)
अणु
	अक्षर zero = 0;

	अगर (!bpf_verअगरier_log_needed(log))
		वापस;

	log->len_used = new_pos;
	अगर (put_user(zero, log->ubuf + new_pos))
		log->ubuf = शून्य;
पूर्ण

/* log_level controls verbosity level of eBPF verअगरier.
 * bpf_verअगरier_log_ग_लिखो() is used to dump the verअगरication trace to the log,
 * so the user can figure out what's wrong with the program
 */
__म_लिखो(2, 3) व्योम bpf_verअगरier_log_ग_लिखो(काष्ठा bpf_verअगरier_env *env,
					   स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (!bpf_verअगरier_log_needed(&env->log))
		वापस;

	बहु_शुरू(args, fmt);
	bpf_verअगरier_vlog(&env->log, fmt, args);
	बहु_पूर्ण(args);
पूर्ण
EXPORT_SYMBOL_GPL(bpf_verअगरier_log_ग_लिखो);

__म_लिखो(2, 3) अटल व्योम verbose(व्योम *निजी_data, स्थिर अक्षर *fmt, ...)
अणु
	काष्ठा bpf_verअगरier_env *env = निजी_data;
	बहु_सूची args;

	अगर (!bpf_verअगरier_log_needed(&env->log))
		वापस;

	बहु_शुरू(args, fmt);
	bpf_verअगरier_vlog(&env->log, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

__म_लिखो(2, 3) व्योम bpf_log(काष्ठा bpf_verअगरier_log *log,
			    स्थिर अक्षर *fmt, ...)
अणु
	बहु_सूची args;

	अगर (!bpf_verअगरier_log_needed(log))
		वापस;

	बहु_शुरू(args, fmt);
	bpf_verअगरier_vlog(log, fmt, args);
	बहु_पूर्ण(args);
पूर्ण

अटल स्थिर अक्षर *ltrim(स्थिर अक्षर *s)
अणु
	जबतक (है_खाली(*s))
		s++;

	वापस s;
पूर्ण

__म_लिखो(3, 4) अटल व्योम verbose_linfo(काष्ठा bpf_verअगरier_env *env,
					 u32 insn_off,
					 स्थिर अक्षर *prefix_fmt, ...)
अणु
	स्थिर काष्ठा bpf_line_info *linfo;

	अगर (!bpf_verअगरier_log_needed(&env->log))
		वापस;

	linfo = find_linfo(env, insn_off);
	अगर (!linfo || linfo == env->prev_linfo)
		वापस;

	अगर (prefix_fmt) अणु
		बहु_सूची args;

		बहु_शुरू(args, prefix_fmt);
		bpf_verअगरier_vlog(&env->log, prefix_fmt, args);
		बहु_पूर्ण(args);
	पूर्ण

	verbose(env, "%s\n",
		ltrim(btf_name_by_offset(env->prog->aux->btf,
					 linfo->line_off)));

	env->prev_linfo = linfo;
पूर्ण

अटल व्योम verbose_invalid_scalar(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_reg_state *reg,
				   काष्ठा tnum *range, स्थिर अक्षर *ctx,
				   स्थिर अक्षर *reg_name)
अणु
	अक्षर tn_buf[48];

	verbose(env, "At %s the register %s ", ctx, reg_name);
	अगर (!tnum_is_unknown(reg->var_off)) अणु
		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env, "has value %s", tn_buf);
	पूर्ण अन्यथा अणु
		verbose(env, "has unknown scalar value");
	पूर्ण
	tnum_strn(tn_buf, माप(tn_buf), *range);
	verbose(env, " should have been in %s\n", tn_buf);
पूर्ण

अटल bool type_is_pkt_poपूर्णांकer(क्रमागत bpf_reg_type type)
अणु
	वापस type == PTR_TO_PACKET ||
	       type == PTR_TO_PACKET_META;
पूर्ण

अटल bool type_is_sk_poपूर्णांकer(क्रमागत bpf_reg_type type)
अणु
	वापस type == PTR_TO_SOCKET ||
		type == PTR_TO_SOCK_COMMON ||
		type == PTR_TO_TCP_SOCK ||
		type == PTR_TO_XDP_SOCK;
पूर्ण

अटल bool reg_type_not_null(क्रमागत bpf_reg_type type)
अणु
	वापस type == PTR_TO_SOCKET ||
		type == PTR_TO_TCP_SOCK ||
		type == PTR_TO_MAP_VALUE ||
		type == PTR_TO_MAP_KEY ||
		type == PTR_TO_SOCK_COMMON;
पूर्ण

अटल bool reg_type_may_be_null(क्रमागत bpf_reg_type type)
अणु
	वापस type == PTR_TO_MAP_VALUE_OR_शून्य ||
	       type == PTR_TO_SOCKET_OR_शून्य ||
	       type == PTR_TO_SOCK_COMMON_OR_शून्य ||
	       type == PTR_TO_TCP_SOCK_OR_शून्य ||
	       type == PTR_TO_BTF_ID_OR_शून्य ||
	       type == PTR_TO_MEM_OR_शून्य ||
	       type == PTR_TO_RDONLY_BUF_OR_शून्य ||
	       type == PTR_TO_RDWR_BUF_OR_शून्य;
पूर्ण

अटल bool reg_may_poपूर्णांक_to_spin_lock(स्थिर काष्ठा bpf_reg_state *reg)
अणु
	वापस reg->type == PTR_TO_MAP_VALUE &&
		map_value_has_spin_lock(reg->map_ptr);
पूर्ण

अटल bool reg_type_may_be_refcounted_or_null(क्रमागत bpf_reg_type type)
अणु
	वापस type == PTR_TO_SOCKET ||
		type == PTR_TO_SOCKET_OR_शून्य ||
		type == PTR_TO_TCP_SOCK ||
		type == PTR_TO_TCP_SOCK_OR_शून्य ||
		type == PTR_TO_MEM ||
		type == PTR_TO_MEM_OR_शून्य;
पूर्ण

अटल bool arg_type_may_be_refcounted(क्रमागत bpf_arg_type type)
अणु
	वापस type == ARG_PTR_TO_SOCK_COMMON;
पूर्ण

अटल bool arg_type_may_be_null(क्रमागत bpf_arg_type type)
अणु
	वापस type == ARG_PTR_TO_MAP_VALUE_OR_शून्य ||
	       type == ARG_PTR_TO_MEM_OR_शून्य ||
	       type == ARG_PTR_TO_CTX_OR_शून्य ||
	       type == ARG_PTR_TO_SOCKET_OR_शून्य ||
	       type == ARG_PTR_TO_ALLOC_MEM_OR_शून्य ||
	       type == ARG_PTR_TO_STACK_OR_शून्य;
पूर्ण

/* Determine whether the function releases some resources allocated by another
 * function call. The first reference type argument will be assumed to be
 * released by release_reference().
 */
अटल bool is_release_function(क्रमागत bpf_func_id func_id)
अणु
	वापस func_id == BPF_FUNC_sk_release ||
	       func_id == BPF_FUNC_ringbuf_submit ||
	       func_id == BPF_FUNC_ringbuf_discard;
पूर्ण

अटल bool may_be_acquire_function(क्रमागत bpf_func_id func_id)
अणु
	वापस func_id == BPF_FUNC_sk_lookup_tcp ||
		func_id == BPF_FUNC_sk_lookup_udp ||
		func_id == BPF_FUNC_skc_lookup_tcp ||
		func_id == BPF_FUNC_map_lookup_elem ||
	        func_id == BPF_FUNC_ringbuf_reserve;
पूर्ण

अटल bool is_acquire_function(क्रमागत bpf_func_id func_id,
				स्थिर काष्ठा bpf_map *map)
अणु
	क्रमागत bpf_map_type map_type = map ? map->map_type : BPF_MAP_TYPE_UNSPEC;

	अगर (func_id == BPF_FUNC_sk_lookup_tcp ||
	    func_id == BPF_FUNC_sk_lookup_udp ||
	    func_id == BPF_FUNC_skc_lookup_tcp ||
	    func_id == BPF_FUNC_ringbuf_reserve)
		वापस true;

	अगर (func_id == BPF_FUNC_map_lookup_elem &&
	    (map_type == BPF_MAP_TYPE_SOCKMAP ||
	     map_type == BPF_MAP_TYPE_SOCKHASH))
		वापस true;

	वापस false;
पूर्ण

अटल bool is_ptr_cast_function(क्रमागत bpf_func_id func_id)
अणु
	वापस func_id == BPF_FUNC_tcp_sock ||
		func_id == BPF_FUNC_sk_fullsock ||
		func_id == BPF_FUNC_skc_to_tcp_sock ||
		func_id == BPF_FUNC_skc_to_tcp6_sock ||
		func_id == BPF_FUNC_skc_to_udp6_sock ||
		func_id == BPF_FUNC_skc_to_tcp_समयरुको_sock ||
		func_id == BPF_FUNC_skc_to_tcp_request_sock;
पूर्ण

अटल bool is_cmpxchg_insn(स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस BPF_CLASS(insn->code) == BPF_STX &&
	       BPF_MODE(insn->code) == BPF_ATOMIC &&
	       insn->imm == BPF_CMPXCHG;
पूर्ण

/* string representation of 'enum bpf_reg_type' */
अटल स्थिर अक्षर * स्थिर reg_type_str[] = अणु
	[NOT_INIT]		= "?",
	[SCALAR_VALUE]		= "inv",
	[PTR_TO_CTX]		= "ctx",
	[CONST_PTR_TO_MAP]	= "map_ptr",
	[PTR_TO_MAP_VALUE]	= "map_value",
	[PTR_TO_MAP_VALUE_OR_शून्य] = "map_value_or_null",
	[PTR_TO_STACK]		= "fp",
	[PTR_TO_PACKET]		= "pkt",
	[PTR_TO_PACKET_META]	= "pkt_meta",
	[PTR_TO_PACKET_END]	= "pkt_end",
	[PTR_TO_FLOW_KEYS]	= "flow_keys",
	[PTR_TO_SOCKET]		= "sock",
	[PTR_TO_SOCKET_OR_शून्य] = "sock_or_null",
	[PTR_TO_SOCK_COMMON]	= "sock_common",
	[PTR_TO_SOCK_COMMON_OR_शून्य] = "sock_common_or_null",
	[PTR_TO_TCP_SOCK]	= "tcp_sock",
	[PTR_TO_TCP_SOCK_OR_शून्य] = "tcp_sock_or_null",
	[PTR_TO_TP_BUFFER]	= "tp_buffer",
	[PTR_TO_XDP_SOCK]	= "xdp_sock",
	[PTR_TO_BTF_ID]		= "ptr_",
	[PTR_TO_BTF_ID_OR_शून्य]	= "ptr_or_null_",
	[PTR_TO_PERCPU_BTF_ID]	= "percpu_ptr_",
	[PTR_TO_MEM]		= "mem",
	[PTR_TO_MEM_OR_शून्य]	= "mem_or_null",
	[PTR_TO_RDONLY_BUF]	= "rdonly_buf",
	[PTR_TO_RDONLY_BUF_OR_शून्य] = "rdonly_buf_or_null",
	[PTR_TO_RDWR_BUF]	= "rdwr_buf",
	[PTR_TO_RDWR_BUF_OR_शून्य] = "rdwr_buf_or_null",
	[PTR_TO_FUNC]		= "func",
	[PTR_TO_MAP_KEY]	= "map_key",
पूर्ण;

अटल अक्षर slot_type_अक्षर[] = अणु
	[STACK_INVALID]	= '?',
	[STACK_SPILL]	= 'r',
	[STACK_MISC]	= 'm',
	[STACK_ZERO]	= '0',
पूर्ण;

अटल व्योम prपूर्णांक_liveness(काष्ठा bpf_verअगरier_env *env,
			   क्रमागत bpf_reg_liveness live)
अणु
	अगर (live & (REG_LIVE_READ | REG_LIVE_WRITTEN | REG_LIVE_DONE))
	    verbose(env, "_");
	अगर (live & REG_LIVE_READ)
		verbose(env, "r");
	अगर (live & REG_LIVE_WRITTEN)
		verbose(env, "w");
	अगर (live & REG_LIVE_DONE)
		verbose(env, "D");
पूर्ण

अटल काष्ठा bpf_func_state *func(काष्ठा bpf_verअगरier_env *env,
				   स्थिर काष्ठा bpf_reg_state *reg)
अणु
	काष्ठा bpf_verअगरier_state *cur = env->cur_state;

	वापस cur->frame[reg->frameno];
पूर्ण

अटल स्थिर अक्षर *kernel_type_name(स्थिर काष्ठा btf* btf, u32 id)
अणु
	वापस btf_name_by_offset(btf, btf_type_by_id(btf, id)->name_off);
पूर्ण

अटल व्योम prपूर्णांक_verअगरier_state(काष्ठा bpf_verअगरier_env *env,
				 स्थिर काष्ठा bpf_func_state *state)
अणु
	स्थिर काष्ठा bpf_reg_state *reg;
	क्रमागत bpf_reg_type t;
	पूर्णांक i;

	अगर (state->frameno)
		verbose(env, " frame%d:", state->frameno);
	क्रम (i = 0; i < MAX_BPF_REG; i++) अणु
		reg = &state->regs[i];
		t = reg->type;
		अगर (t == NOT_INIT)
			जारी;
		verbose(env, " R%d", i);
		prपूर्णांक_liveness(env, reg->live);
		verbose(env, "=%s", reg_type_str[t]);
		अगर (t == SCALAR_VALUE && reg->precise)
			verbose(env, "P");
		अगर ((t == SCALAR_VALUE || t == PTR_TO_STACK) &&
		    tnum_is_स्थिर(reg->var_off)) अणु
			/* reg->off should be 0 क्रम SCALAR_VALUE */
			verbose(env, "%lld", reg->var_off.value + reg->off);
		पूर्ण अन्यथा अणु
			अगर (t == PTR_TO_BTF_ID ||
			    t == PTR_TO_BTF_ID_OR_शून्य ||
			    t == PTR_TO_PERCPU_BTF_ID)
				verbose(env, "%s", kernel_type_name(reg->btf, reg->btf_id));
			verbose(env, "(id=%d", reg->id);
			अगर (reg_type_may_be_refcounted_or_null(t))
				verbose(env, ",ref_obj_id=%d", reg->ref_obj_id);
			अगर (t != SCALAR_VALUE)
				verbose(env, ",off=%d", reg->off);
			अगर (type_is_pkt_poपूर्णांकer(t))
				verbose(env, ",r=%d", reg->range);
			अन्यथा अगर (t == CONST_PTR_TO_MAP ||
				 t == PTR_TO_MAP_KEY ||
				 t == PTR_TO_MAP_VALUE ||
				 t == PTR_TO_MAP_VALUE_OR_शून्य)
				verbose(env, ",ks=%d,vs=%d",
					reg->map_ptr->key_size,
					reg->map_ptr->value_size);
			अगर (tnum_is_स्थिर(reg->var_off)) अणु
				/* Typically an immediate SCALAR_VALUE, but
				 * could be a poपूर्णांकer whose offset is too big
				 * क्रम reg->off
				 */
				verbose(env, ",imm=%llx", reg->var_off.value);
			पूर्ण अन्यथा अणु
				अगर (reg->smin_value != reg->umin_value &&
				    reg->smin_value != S64_MIN)
					verbose(env, ",smin_value=%lld",
						(दीर्घ दीर्घ)reg->smin_value);
				अगर (reg->smax_value != reg->umax_value &&
				    reg->smax_value != S64_MAX)
					verbose(env, ",smax_value=%lld",
						(दीर्घ दीर्घ)reg->smax_value);
				अगर (reg->umin_value != 0)
					verbose(env, ",umin_value=%llu",
						(अचिन्हित दीर्घ दीर्घ)reg->umin_value);
				अगर (reg->umax_value != U64_MAX)
					verbose(env, ",umax_value=%llu",
						(अचिन्हित दीर्घ दीर्घ)reg->umax_value);
				अगर (!tnum_is_unknown(reg->var_off)) अणु
					अक्षर tn_buf[48];

					tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
					verbose(env, ",var_off=%s", tn_buf);
				पूर्ण
				अगर (reg->s32_min_value != reg->smin_value &&
				    reg->s32_min_value != S32_MIN)
					verbose(env, ",s32_min_value=%d",
						(पूर्णांक)(reg->s32_min_value));
				अगर (reg->s32_max_value != reg->smax_value &&
				    reg->s32_max_value != S32_MAX)
					verbose(env, ",s32_max_value=%d",
						(पूर्णांक)(reg->s32_max_value));
				अगर (reg->u32_min_value != reg->umin_value &&
				    reg->u32_min_value != U32_MIN)
					verbose(env, ",u32_min_value=%d",
						(पूर्णांक)(reg->u32_min_value));
				अगर (reg->u32_max_value != reg->umax_value &&
				    reg->u32_max_value != U32_MAX)
					verbose(env, ",u32_max_value=%d",
						(पूर्णांक)(reg->u32_max_value));
			पूर्ण
			verbose(env, ")");
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < state->allocated_stack / BPF_REG_SIZE; i++) अणु
		अक्षर types_buf[BPF_REG_SIZE + 1];
		bool valid = false;
		पूर्णांक j;

		क्रम (j = 0; j < BPF_REG_SIZE; j++) अणु
			अगर (state->stack[i].slot_type[j] != STACK_INVALID)
				valid = true;
			types_buf[j] = slot_type_अक्षर[
					state->stack[i].slot_type[j]];
		पूर्ण
		types_buf[BPF_REG_SIZE] = 0;
		अगर (!valid)
			जारी;
		verbose(env, " fp%d", (-i - 1) * BPF_REG_SIZE);
		prपूर्णांक_liveness(env, state->stack[i].spilled_ptr.live);
		अगर (state->stack[i].slot_type[0] == STACK_SPILL) अणु
			reg = &state->stack[i].spilled_ptr;
			t = reg->type;
			verbose(env, "=%s", reg_type_str[t]);
			अगर (t == SCALAR_VALUE && reg->precise)
				verbose(env, "P");
			अगर (t == SCALAR_VALUE && tnum_is_स्थिर(reg->var_off))
				verbose(env, "%lld", reg->var_off.value + reg->off);
		पूर्ण अन्यथा अणु
			verbose(env, "=%s", types_buf);
		पूर्ण
	पूर्ण
	अगर (state->acquired_refs && state->refs[0].id) अणु
		verbose(env, " refs=%d", state->refs[0].id);
		क्रम (i = 1; i < state->acquired_refs; i++)
			अगर (state->refs[i].id)
				verbose(env, ",%d", state->refs[i].id);
	पूर्ण
	verbose(env, "\n");
पूर्ण

#घोषणा COPY_STATE_FN(NAME, COUNT, FIELD, SIZE)				\
अटल पूर्णांक copy_##NAME##_state(काष्ठा bpf_func_state *dst,		\
			       स्थिर काष्ठा bpf_func_state *src)	\
अणु									\
	अगर (!src->FIELD)						\
		वापस 0;						\
	अगर (WARN_ON_ONCE(dst->COUNT < src->COUNT)) अणु			\
		/* पूर्णांकernal bug, make state invalid to reject the program */ \
		स_रखो(dst, 0, माप(*dst));				\
		वापस -EFAULT;						\
	पूर्ण								\
	स_नकल(dst->FIELD, src->FIELD,					\
	       माप(*src->FIELD) * (src->COUNT / SIZE));		\
	वापस 0;							\
पूर्ण
/* copy_reference_state() */
COPY_STATE_FN(reference, acquired_refs, refs, 1)
/* copy_stack_state() */
COPY_STATE_FN(stack, allocated_stack, stack, BPF_REG_SIZE)
#अघोषित COPY_STATE_FN

#घोषणा REALLOC_STATE_FN(NAME, COUNT, FIELD, SIZE)			\
अटल पूर्णांक पुनः_स्मृति_##NAME##_state(काष्ठा bpf_func_state *state, पूर्णांक size, \
				  bool copy_old)			\
अणु									\
	u32 old_size = state->COUNT;					\
	काष्ठा bpf_##NAME##_state *new_##FIELD;				\
	पूर्णांक slot = size / SIZE;						\
									\
	अगर (size <= old_size || !size) अणु				\
		अगर (copy_old)						\
			वापस 0;					\
		state->COUNT = slot * SIZE;				\
		अगर (!size && old_size) अणु				\
			kमुक्त(state->FIELD);				\
			state->FIELD = शून्य;				\
		पूर्ण							\
		वापस 0;						\
	पूर्ण								\
	new_##FIELD = kदो_स्मृति_array(slot, माप(काष्ठा bpf_##NAME##_state), \
				    GFP_KERNEL);			\
	अगर (!new_##FIELD)						\
		वापस -ENOMEM;						\
	अगर (copy_old) अणु							\
		अगर (state->FIELD)					\
			स_नकल(new_##FIELD, state->FIELD,		\
			       माप(*new_##FIELD) * (old_size / SIZE)); \
		स_रखो(new_##FIELD + old_size / SIZE, 0,		\
		       माप(*new_##FIELD) * (size - old_size) / SIZE); \
	पूर्ण								\
	state->COUNT = slot * SIZE;					\
	kमुक्त(state->FIELD);						\
	state->FIELD = new_##FIELD;					\
	वापस 0;							\
पूर्ण
/* पुनः_स्मृति_reference_state() */
REALLOC_STATE_FN(reference, acquired_refs, refs, 1)
/* पुनः_स्मृति_stack_state() */
REALLOC_STATE_FN(stack, allocated_stack, stack, BPF_REG_SIZE)
#अघोषित REALLOC_STATE_FN

/* करो_check() starts with zero-sized stack in काष्ठा bpf_verअगरier_state to
 * make it consume minimal amount of memory. check_stack_ग_लिखो() access from
 * the program calls पूर्णांकo पुनः_स्मृति_func_state() to grow the stack size.
 * Note there is a non-zero 'parent' poपूर्णांकer inside bpf_verअगरier_state
 * which पुनः_स्मृति_stack_state() copies over. It poपूर्णांकs to previous
 * bpf_verअगरier_state which is never पुनः_स्मृतिated.
 */
अटल पूर्णांक पुनः_स्मृति_func_state(काष्ठा bpf_func_state *state, पूर्णांक stack_size,
			      पूर्णांक refs_size, bool copy_old)
अणु
	पूर्णांक err = पुनः_स्मृति_reference_state(state, refs_size, copy_old);
	अगर (err)
		वापस err;
	वापस पुनः_स्मृति_stack_state(state, stack_size, copy_old);
पूर्ण

/* Acquire a poपूर्णांकer id from the env and update the state->refs to include
 * this new poपूर्णांकer reference.
 * On success, वापसs a valid poपूर्णांकer id to associate with the रेजिस्टर
 * On failure, वापसs a negative त्रुटि_सं.
 */
अटल पूर्णांक acquire_reference_state(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx)
अणु
	काष्ठा bpf_func_state *state = cur_func(env);
	पूर्णांक new_ofs = state->acquired_refs;
	पूर्णांक id, err;

	err = पुनः_स्मृति_reference_state(state, state->acquired_refs + 1, true);
	अगर (err)
		वापस err;
	id = ++env->id_gen;
	state->refs[new_ofs].id = id;
	state->refs[new_ofs].insn_idx = insn_idx;

	वापस id;
पूर्ण

/* release function corresponding to acquire_reference_state(). Idempotent. */
अटल पूर्णांक release_reference_state(काष्ठा bpf_func_state *state, पूर्णांक ptr_id)
अणु
	पूर्णांक i, last_idx;

	last_idx = state->acquired_refs - 1;
	क्रम (i = 0; i < state->acquired_refs; i++) अणु
		अगर (state->refs[i].id == ptr_id) अणु
			अगर (last_idx && i != last_idx)
				स_नकल(&state->refs[i], &state->refs[last_idx],
				       माप(*state->refs));
			स_रखो(&state->refs[last_idx], 0, माप(*state->refs));
			state->acquired_refs--;
			वापस 0;
		पूर्ण
	पूर्ण
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक transfer_reference_state(काष्ठा bpf_func_state *dst,
				    काष्ठा bpf_func_state *src)
अणु
	पूर्णांक err = पुनः_स्मृति_reference_state(dst, src->acquired_refs, false);
	अगर (err)
		वापस err;
	err = copy_reference_state(dst, src);
	अगर (err)
		वापस err;
	वापस 0;
पूर्ण

अटल व्योम मुक्त_func_state(काष्ठा bpf_func_state *state)
अणु
	अगर (!state)
		वापस;
	kमुक्त(state->refs);
	kमुक्त(state->stack);
	kमुक्त(state);
पूर्ण

अटल व्योम clear_jmp_history(काष्ठा bpf_verअगरier_state *state)
अणु
	kमुक्त(state->jmp_history);
	state->jmp_history = शून्य;
	state->jmp_history_cnt = 0;
पूर्ण

अटल व्योम मुक्त_verअगरier_state(काष्ठा bpf_verअगरier_state *state,
				bool मुक्त_self)
अणु
	पूर्णांक i;

	क्रम (i = 0; i <= state->curframe; i++) अणु
		मुक्त_func_state(state->frame[i]);
		state->frame[i] = शून्य;
	पूर्ण
	clear_jmp_history(state);
	अगर (मुक्त_self)
		kमुक्त(state);
पूर्ण

/* copy verअगरier state from src to dst growing dst stack space
 * when necessary to accommodate larger src stack
 */
अटल पूर्णांक copy_func_state(काष्ठा bpf_func_state *dst,
			   स्थिर काष्ठा bpf_func_state *src)
अणु
	पूर्णांक err;

	err = पुनः_स्मृति_func_state(dst, src->allocated_stack, src->acquired_refs,
				 false);
	अगर (err)
		वापस err;
	स_नकल(dst, src, दुरत्व(काष्ठा bpf_func_state, acquired_refs));
	err = copy_reference_state(dst, src);
	अगर (err)
		वापस err;
	वापस copy_stack_state(dst, src);
पूर्ण

अटल पूर्णांक copy_verअगरier_state(काष्ठा bpf_verअगरier_state *dst_state,
			       स्थिर काष्ठा bpf_verअगरier_state *src)
अणु
	काष्ठा bpf_func_state *dst;
	u32 jmp_sz = माप(काष्ठा bpf_idx_pair) * src->jmp_history_cnt;
	पूर्णांक i, err;

	अगर (dst_state->jmp_history_cnt < src->jmp_history_cnt) अणु
		kमुक्त(dst_state->jmp_history);
		dst_state->jmp_history = kदो_स्मृति(jmp_sz, GFP_USER);
		अगर (!dst_state->jmp_history)
			वापस -ENOMEM;
	पूर्ण
	स_नकल(dst_state->jmp_history, src->jmp_history, jmp_sz);
	dst_state->jmp_history_cnt = src->jmp_history_cnt;

	/* अगर dst has more stack frames then src frame, मुक्त them */
	क्रम (i = src->curframe + 1; i <= dst_state->curframe; i++) अणु
		मुक्त_func_state(dst_state->frame[i]);
		dst_state->frame[i] = शून्य;
	पूर्ण
	dst_state->speculative = src->speculative;
	dst_state->curframe = src->curframe;
	dst_state->active_spin_lock = src->active_spin_lock;
	dst_state->branches = src->branches;
	dst_state->parent = src->parent;
	dst_state->first_insn_idx = src->first_insn_idx;
	dst_state->last_insn_idx = src->last_insn_idx;
	क्रम (i = 0; i <= src->curframe; i++) अणु
		dst = dst_state->frame[i];
		अगर (!dst) अणु
			dst = kzalloc(माप(*dst), GFP_KERNEL);
			अगर (!dst)
				वापस -ENOMEM;
			dst_state->frame[i] = dst;
		पूर्ण
		err = copy_func_state(dst, src->frame[i]);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम update_branch_counts(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_verअगरier_state *st)
अणु
	जबतक (st) अणु
		u32 br = --st->branches;

		/* WARN_ON(br > 1) technically makes sense here,
		 * but see comment in push_stack(), hence:
		 */
		WARN_ONCE((पूर्णांक)br < 0,
			  "BUG update_branch_counts:branches_to_explore=%d\n",
			  br);
		अगर (br)
			अवरोध;
		st = st->parent;
	पूर्ण
पूर्ण

अटल पूर्णांक pop_stack(काष्ठा bpf_verअगरier_env *env, पूर्णांक *prev_insn_idx,
		     पूर्णांक *insn_idx, bool pop_log)
अणु
	काष्ठा bpf_verअगरier_state *cur = env->cur_state;
	काष्ठा bpf_verअगरier_stack_elem *elem, *head = env->head;
	पूर्णांक err;

	अगर (env->head == शून्य)
		वापस -ENOENT;

	अगर (cur) अणु
		err = copy_verअगरier_state(cur, &head->st);
		अगर (err)
			वापस err;
	पूर्ण
	अगर (pop_log)
		bpf_vlog_reset(&env->log, head->log_pos);
	अगर (insn_idx)
		*insn_idx = head->insn_idx;
	अगर (prev_insn_idx)
		*prev_insn_idx = head->prev_insn_idx;
	elem = head->next;
	मुक्त_verअगरier_state(&head->st, false);
	kमुक्त(head);
	env->head = elem;
	env->stack_size--;
	वापस 0;
पूर्ण

अटल काष्ठा bpf_verअगरier_state *push_stack(काष्ठा bpf_verअगरier_env *env,
					     पूर्णांक insn_idx, पूर्णांक prev_insn_idx,
					     bool speculative)
अणु
	काष्ठा bpf_verअगरier_state *cur = env->cur_state;
	काष्ठा bpf_verअगरier_stack_elem *elem;
	पूर्णांक err;

	elem = kzalloc(माप(काष्ठा bpf_verअगरier_stack_elem), GFP_KERNEL);
	अगर (!elem)
		जाओ err;

	elem->insn_idx = insn_idx;
	elem->prev_insn_idx = prev_insn_idx;
	elem->next = env->head;
	elem->log_pos = env->log.len_used;
	env->head = elem;
	env->stack_size++;
	err = copy_verअगरier_state(&elem->st, cur);
	अगर (err)
		जाओ err;
	elem->st.speculative |= speculative;
	अगर (env->stack_size > BPF_COMPLEXITY_LIMIT_JMP_SEQ) अणु
		verbose(env, "The sequence of %d jumps is too complex.\n",
			env->stack_size);
		जाओ err;
	पूर्ण
	अगर (elem->st.parent) अणु
		++elem->st.parent->branches;
		/* WARN_ON(branches > 2) technically makes sense here,
		 * but
		 * 1. speculative states will bump 'branches' क्रम non-branch
		 * inकाष्ठाions
		 * 2. is_state_visited() heuristics may decide not to create
		 * a new state क्रम a sequence of branches and all such current
		 * and cloned states will be poपूर्णांकing to a single parent state
		 * which might have large 'branches' count.
		 */
	पूर्ण
	वापस &elem->st;
err:
	मुक्त_verअगरier_state(env->cur_state, true);
	env->cur_state = शून्य;
	/* pop all elements and वापस */
	जबतक (!pop_stack(env, शून्य, शून्य, false));
	वापस शून्य;
पूर्ण

#घोषणा CALLER_SAVED_REGS 6
अटल स्थिर पूर्णांक caller_saved[CALLER_SAVED_REGS] = अणु
	BPF_REG_0, BPF_REG_1, BPF_REG_2, BPF_REG_3, BPF_REG_4, BPF_REG_5
पूर्ण;

अटल व्योम __mark_reg_not_init(स्थिर काष्ठा bpf_verअगरier_env *env,
				काष्ठा bpf_reg_state *reg);

/* This helper करोesn't clear reg->id */
अटल व्योम ___mark_reg_known(काष्ठा bpf_reg_state *reg, u64 imm)
अणु
	reg->var_off = tnum_स्थिर(imm);
	reg->smin_value = (s64)imm;
	reg->smax_value = (s64)imm;
	reg->umin_value = imm;
	reg->umax_value = imm;

	reg->s32_min_value = (s32)imm;
	reg->s32_max_value = (s32)imm;
	reg->u32_min_value = (u32)imm;
	reg->u32_max_value = (u32)imm;
पूर्ण

/* Mark the unknown part of a रेजिस्टर (variable offset or scalar value) as
 * known to have the value @imm.
 */
अटल व्योम __mark_reg_known(काष्ठा bpf_reg_state *reg, u64 imm)
अणु
	/* Clear id, off, and जोड़(map_ptr, range) */
	स_रखो(((u8 *)reg) + माप(reg->type), 0,
	       दुरत्व(काष्ठा bpf_reg_state, var_off) - माप(reg->type));
	___mark_reg_known(reg, imm);
पूर्ण

अटल व्योम __mark_reg32_known(काष्ठा bpf_reg_state *reg, u64 imm)
अणु
	reg->var_off = tnum_स्थिर_subreg(reg->var_off, imm);
	reg->s32_min_value = (s32)imm;
	reg->s32_max_value = (s32)imm;
	reg->u32_min_value = (u32)imm;
	reg->u32_max_value = (u32)imm;
पूर्ण

/* Mark the 'variable offset' part of a रेजिस्टर as zero.  This should be
 * used only on रेजिस्टरs holding a poपूर्णांकer type.
 */
अटल व्योम __mark_reg_known_zero(काष्ठा bpf_reg_state *reg)
अणु
	__mark_reg_known(reg, 0);
पूर्ण

अटल व्योम __mark_reg_स्थिर_zero(काष्ठा bpf_reg_state *reg)
अणु
	__mark_reg_known(reg, 0);
	reg->type = SCALAR_VALUE;
पूर्ण

अटल व्योम mark_reg_known_zero(काष्ठा bpf_verअगरier_env *env,
				काष्ठा bpf_reg_state *regs, u32 regno)
अणु
	अगर (WARN_ON(regno >= MAX_BPF_REG)) अणु
		verbose(env, "mark_reg_known_zero(regs, %u)\n", regno);
		/* Something bad happened, let's समाप्त all regs */
		क्रम (regno = 0; regno < MAX_BPF_REG; regno++)
			__mark_reg_not_init(env, regs + regno);
		वापस;
	पूर्ण
	__mark_reg_known_zero(regs + regno);
पूर्ण

अटल व्योम mark_ptr_not_null_reg(काष्ठा bpf_reg_state *reg)
अणु
	चयन (reg->type) अणु
	हाल PTR_TO_MAP_VALUE_OR_शून्य: अणु
		स्थिर काष्ठा bpf_map *map = reg->map_ptr;

		अगर (map->inner_map_meta) अणु
			reg->type = CONST_PTR_TO_MAP;
			reg->map_ptr = map->inner_map_meta;
		पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_XSKMAP) अणु
			reg->type = PTR_TO_XDP_SOCK;
		पूर्ण अन्यथा अगर (map->map_type == BPF_MAP_TYPE_SOCKMAP ||
			   map->map_type == BPF_MAP_TYPE_SOCKHASH) अणु
			reg->type = PTR_TO_SOCKET;
		पूर्ण अन्यथा अणु
			reg->type = PTR_TO_MAP_VALUE;
		पूर्ण
		अवरोध;
	पूर्ण
	हाल PTR_TO_SOCKET_OR_शून्य:
		reg->type = PTR_TO_SOCKET;
		अवरोध;
	हाल PTR_TO_SOCK_COMMON_OR_शून्य:
		reg->type = PTR_TO_SOCK_COMMON;
		अवरोध;
	हाल PTR_TO_TCP_SOCK_OR_शून्य:
		reg->type = PTR_TO_TCP_SOCK;
		अवरोध;
	हाल PTR_TO_BTF_ID_OR_शून्य:
		reg->type = PTR_TO_BTF_ID;
		अवरोध;
	हाल PTR_TO_MEM_OR_शून्य:
		reg->type = PTR_TO_MEM;
		अवरोध;
	हाल PTR_TO_RDONLY_BUF_OR_शून्य:
		reg->type = PTR_TO_RDONLY_BUF;
		अवरोध;
	हाल PTR_TO_RDWR_BUF_OR_शून्य:
		reg->type = PTR_TO_RDWR_BUF;
		अवरोध;
	शेष:
		WARN_ONCE(1, "unknown nullable register type");
	पूर्ण
पूर्ण

अटल bool reg_is_pkt_poपूर्णांकer(स्थिर काष्ठा bpf_reg_state *reg)
अणु
	वापस type_is_pkt_poपूर्णांकer(reg->type);
पूर्ण

अटल bool reg_is_pkt_poपूर्णांकer_any(स्थिर काष्ठा bpf_reg_state *reg)
अणु
	वापस reg_is_pkt_poपूर्णांकer(reg) ||
	       reg->type == PTR_TO_PACKET_END;
पूर्ण

/* Unmodअगरied PTR_TO_PACKET[_META,_END] रेजिस्टर from ctx access. */
अटल bool reg_is_init_pkt_poपूर्णांकer(स्थिर काष्ठा bpf_reg_state *reg,
				    क्रमागत bpf_reg_type which)
अणु
	/* The रेजिस्टर can alपढ़ोy have a range from prior markings.
	 * This is fine as दीर्घ as it hasn't been advanced from its
	 * origin.
	 */
	वापस reg->type == which &&
	       reg->id == 0 &&
	       reg->off == 0 &&
	       tnum_equals_स्थिर(reg->var_off, 0);
पूर्ण

/* Reset the min/max bounds of a रेजिस्टर */
अटल व्योम __mark_reg_unbounded(काष्ठा bpf_reg_state *reg)
अणु
	reg->smin_value = S64_MIN;
	reg->smax_value = S64_MAX;
	reg->umin_value = 0;
	reg->umax_value = U64_MAX;

	reg->s32_min_value = S32_MIN;
	reg->s32_max_value = S32_MAX;
	reg->u32_min_value = 0;
	reg->u32_max_value = U32_MAX;
पूर्ण

अटल व्योम __mark_reg64_unbounded(काष्ठा bpf_reg_state *reg)
अणु
	reg->smin_value = S64_MIN;
	reg->smax_value = S64_MAX;
	reg->umin_value = 0;
	reg->umax_value = U64_MAX;
पूर्ण

अटल व्योम __mark_reg32_unbounded(काष्ठा bpf_reg_state *reg)
अणु
	reg->s32_min_value = S32_MIN;
	reg->s32_max_value = S32_MAX;
	reg->u32_min_value = 0;
	reg->u32_max_value = U32_MAX;
पूर्ण

अटल व्योम __update_reg32_bounds(काष्ठा bpf_reg_state *reg)
अणु
	काष्ठा tnum var32_off = tnum_subreg(reg->var_off);

	/* min चिन्हित is max(sign bit) | min(other bits) */
	reg->s32_min_value = max_t(s32, reg->s32_min_value,
			var32_off.value | (var32_off.mask & S32_MIN));
	/* max चिन्हित is min(sign bit) | max(other bits) */
	reg->s32_max_value = min_t(s32, reg->s32_max_value,
			var32_off.value | (var32_off.mask & S32_MAX));
	reg->u32_min_value = max_t(u32, reg->u32_min_value, (u32)var32_off.value);
	reg->u32_max_value = min(reg->u32_max_value,
				 (u32)(var32_off.value | var32_off.mask));
पूर्ण

अटल व्योम __update_reg64_bounds(काष्ठा bpf_reg_state *reg)
अणु
	/* min चिन्हित is max(sign bit) | min(other bits) */
	reg->smin_value = max_t(s64, reg->smin_value,
				reg->var_off.value | (reg->var_off.mask & S64_MIN));
	/* max चिन्हित is min(sign bit) | max(other bits) */
	reg->smax_value = min_t(s64, reg->smax_value,
				reg->var_off.value | (reg->var_off.mask & S64_MAX));
	reg->umin_value = max(reg->umin_value, reg->var_off.value);
	reg->umax_value = min(reg->umax_value,
			      reg->var_off.value | reg->var_off.mask);
पूर्ण

अटल व्योम __update_reg_bounds(काष्ठा bpf_reg_state *reg)
अणु
	__update_reg32_bounds(reg);
	__update_reg64_bounds(reg);
पूर्ण

/* Uses चिन्हित min/max values to inक्रमm अचिन्हित, and vice-versa */
अटल व्योम __reg32_deduce_bounds(काष्ठा bpf_reg_state *reg)
अणु
	/* Learn sign from चिन्हित bounds.
	 * If we cannot cross the sign boundary, then चिन्हित and अचिन्हित bounds
	 * are the same, so combine.  This works even in the negative हाल, e.g.
	 * -3 s<= x s<= -1 implies 0xf...fd u<= x u<= 0xf...ff.
	 */
	अगर (reg->s32_min_value >= 0 || reg->s32_max_value < 0) अणु
		reg->s32_min_value = reg->u32_min_value =
			max_t(u32, reg->s32_min_value, reg->u32_min_value);
		reg->s32_max_value = reg->u32_max_value =
			min_t(u32, reg->s32_max_value, reg->u32_max_value);
		वापस;
	पूर्ण
	/* Learn sign from अचिन्हित bounds.  Signed bounds cross the sign
	 * boundary, so we must be careful.
	 */
	अगर ((s32)reg->u32_max_value >= 0) अणु
		/* Positive.  We can't learn anything from the smin, but smax
		 * is positive, hence safe.
		 */
		reg->s32_min_value = reg->u32_min_value;
		reg->s32_max_value = reg->u32_max_value =
			min_t(u32, reg->s32_max_value, reg->u32_max_value);
	पूर्ण अन्यथा अगर ((s32)reg->u32_min_value < 0) अणु
		/* Negative.  We can't learn anything from the smax, but smin
		 * is negative, hence safe.
		 */
		reg->s32_min_value = reg->u32_min_value =
			max_t(u32, reg->s32_min_value, reg->u32_min_value);
		reg->s32_max_value = reg->u32_max_value;
	पूर्ण
पूर्ण

अटल व्योम __reg64_deduce_bounds(काष्ठा bpf_reg_state *reg)
अणु
	/* Learn sign from चिन्हित bounds.
	 * If we cannot cross the sign boundary, then चिन्हित and अचिन्हित bounds
	 * are the same, so combine.  This works even in the negative हाल, e.g.
	 * -3 s<= x s<= -1 implies 0xf...fd u<= x u<= 0xf...ff.
	 */
	अगर (reg->smin_value >= 0 || reg->smax_value < 0) अणु
		reg->smin_value = reg->umin_value = max_t(u64, reg->smin_value,
							  reg->umin_value);
		reg->smax_value = reg->umax_value = min_t(u64, reg->smax_value,
							  reg->umax_value);
		वापस;
	पूर्ण
	/* Learn sign from अचिन्हित bounds.  Signed bounds cross the sign
	 * boundary, so we must be careful.
	 */
	अगर ((s64)reg->umax_value >= 0) अणु
		/* Positive.  We can't learn anything from the smin, but smax
		 * is positive, hence safe.
		 */
		reg->smin_value = reg->umin_value;
		reg->smax_value = reg->umax_value = min_t(u64, reg->smax_value,
							  reg->umax_value);
	पूर्ण अन्यथा अगर ((s64)reg->umin_value < 0) अणु
		/* Negative.  We can't learn anything from the smax, but smin
		 * is negative, hence safe.
		 */
		reg->smin_value = reg->umin_value = max_t(u64, reg->smin_value,
							  reg->umin_value);
		reg->smax_value = reg->umax_value;
	पूर्ण
पूर्ण

अटल व्योम __reg_deduce_bounds(काष्ठा bpf_reg_state *reg)
अणु
	__reg32_deduce_bounds(reg);
	__reg64_deduce_bounds(reg);
पूर्ण

/* Attempts to improve var_off based on अचिन्हित min/max inक्रमmation */
अटल व्योम __reg_bound_offset(काष्ठा bpf_reg_state *reg)
अणु
	काष्ठा tnum var64_off = tnum_पूर्णांकersect(reg->var_off,
					       tnum_range(reg->umin_value,
							  reg->umax_value));
	काष्ठा tnum var32_off = tnum_पूर्णांकersect(tnum_subreg(reg->var_off),
						tnum_range(reg->u32_min_value,
							   reg->u32_max_value));

	reg->var_off = tnum_or(tnum_clear_subreg(var64_off), var32_off);
पूर्ण

अटल व्योम __reg_assign_32_पूर्णांकo_64(काष्ठा bpf_reg_state *reg)
अणु
	reg->umin_value = reg->u32_min_value;
	reg->umax_value = reg->u32_max_value;
	/* Attempt to pull 32-bit चिन्हित bounds पूर्णांकo 64-bit bounds
	 * but must be positive otherwise set to worse हाल bounds
	 * and refine later from tnum.
	 */
	अगर (reg->s32_min_value >= 0 && reg->s32_max_value >= 0)
		reg->smax_value = reg->s32_max_value;
	अन्यथा
		reg->smax_value = U32_MAX;
	अगर (reg->s32_min_value >= 0)
		reg->smin_value = reg->s32_min_value;
	अन्यथा
		reg->smin_value = 0;
पूर्ण

अटल व्योम __reg_combine_32_पूर्णांकo_64(काष्ठा bpf_reg_state *reg)
अणु
	/* special हाल when 64-bit रेजिस्टर has upper 32-bit रेजिस्टर
	 * zeroed. Typically happens after zext or <<32, >>32 sequence
	 * allowing us to use 32-bit bounds directly,
	 */
	अगर (tnum_equals_स्थिर(tnum_clear_subreg(reg->var_off), 0)) अणु
		__reg_assign_32_पूर्णांकo_64(reg);
	पूर्ण अन्यथा अणु
		/* Otherwise the best we can करो is push lower 32bit known and
		 * unknown bits पूर्णांकo रेजिस्टर (var_off set from jmp logic)
		 * then learn as much as possible from the 64-bit tnum
		 * known and unknown bits. The previous smin/smax bounds are
		 * invalid here because of jmp32 compare so mark them unknown
		 * so they करो not impact tnum bounds calculation.
		 */
		__mark_reg64_unbounded(reg);
		__update_reg_bounds(reg);
	पूर्ण

	/* Intersecting with the old var_off might have improved our bounds
	 * slightly.  e.g. अगर umax was 0x7f...f and var_off was (0; 0xf...fc),
	 * then new var_off is (0; 0x7f...fc) which improves our umax.
	 */
	__reg_deduce_bounds(reg);
	__reg_bound_offset(reg);
	__update_reg_bounds(reg);
पूर्ण

अटल bool __reg64_bound_s32(s64 a)
अणु
	वापस a > S32_MIN && a < S32_MAX;
पूर्ण

अटल bool __reg64_bound_u32(u64 a)
अणु
	वापस a > U32_MIN && a < U32_MAX;
पूर्ण

अटल व्योम __reg_combine_64_पूर्णांकo_32(काष्ठा bpf_reg_state *reg)
अणु
	__mark_reg32_unbounded(reg);

	अगर (__reg64_bound_s32(reg->smin_value) && __reg64_bound_s32(reg->smax_value)) अणु
		reg->s32_min_value = (s32)reg->smin_value;
		reg->s32_max_value = (s32)reg->smax_value;
	पूर्ण
	अगर (__reg64_bound_u32(reg->umin_value) && __reg64_bound_u32(reg->umax_value)) अणु
		reg->u32_min_value = (u32)reg->umin_value;
		reg->u32_max_value = (u32)reg->umax_value;
	पूर्ण

	/* Intersecting with the old var_off might have improved our bounds
	 * slightly.  e.g. अगर umax was 0x7f...f and var_off was (0; 0xf...fc),
	 * then new var_off is (0; 0x7f...fc) which improves our umax.
	 */
	__reg_deduce_bounds(reg);
	__reg_bound_offset(reg);
	__update_reg_bounds(reg);
पूर्ण

/* Mark a रेजिस्टर as having a completely unknown (scalar) value. */
अटल व्योम __mark_reg_unknown(स्थिर काष्ठा bpf_verअगरier_env *env,
			       काष्ठा bpf_reg_state *reg)
अणु
	/*
	 * Clear type, id, off, and जोड़(map_ptr, range) and
	 * padding between 'type' and जोड़
	 */
	स_रखो(reg, 0, दुरत्व(काष्ठा bpf_reg_state, var_off));
	reg->type = SCALAR_VALUE;
	reg->var_off = tnum_unknown;
	reg->frameno = 0;
	reg->precise = env->subprog_cnt > 1 || !env->bpf_capable;
	__mark_reg_unbounded(reg);
पूर्ण

अटल व्योम mark_reg_unknown(काष्ठा bpf_verअगरier_env *env,
			     काष्ठा bpf_reg_state *regs, u32 regno)
अणु
	अगर (WARN_ON(regno >= MAX_BPF_REG)) अणु
		verbose(env, "mark_reg_unknown(regs, %u)\n", regno);
		/* Something bad happened, let's समाप्त all regs except FP */
		क्रम (regno = 0; regno < BPF_REG_FP; regno++)
			__mark_reg_not_init(env, regs + regno);
		वापस;
	पूर्ण
	__mark_reg_unknown(env, regs + regno);
पूर्ण

अटल व्योम __mark_reg_not_init(स्थिर काष्ठा bpf_verअगरier_env *env,
				काष्ठा bpf_reg_state *reg)
अणु
	__mark_reg_unknown(env, reg);
	reg->type = NOT_INIT;
पूर्ण

अटल व्योम mark_reg_not_init(काष्ठा bpf_verअगरier_env *env,
			      काष्ठा bpf_reg_state *regs, u32 regno)
अणु
	अगर (WARN_ON(regno >= MAX_BPF_REG)) अणु
		verbose(env, "mark_reg_not_init(regs, %u)\n", regno);
		/* Something bad happened, let's समाप्त all regs except FP */
		क्रम (regno = 0; regno < BPF_REG_FP; regno++)
			__mark_reg_not_init(env, regs + regno);
		वापस;
	पूर्ण
	__mark_reg_not_init(env, regs + regno);
पूर्ण

अटल व्योम mark_btf_ld_reg(काष्ठा bpf_verअगरier_env *env,
			    काष्ठा bpf_reg_state *regs, u32 regno,
			    क्रमागत bpf_reg_type reg_type,
			    काष्ठा btf *btf, u32 btf_id)
अणु
	अगर (reg_type == SCALAR_VALUE) अणु
		mark_reg_unknown(env, regs, regno);
		वापस;
	पूर्ण
	mark_reg_known_zero(env, regs, regno);
	regs[regno].type = PTR_TO_BTF_ID;
	regs[regno].btf = btf;
	regs[regno].btf_id = btf_id;
पूर्ण

#घोषणा DEF_NOT_SUBREG	(0)
अटल व्योम init_reg_state(काष्ठा bpf_verअगरier_env *env,
			   काष्ठा bpf_func_state *state)
अणु
	काष्ठा bpf_reg_state *regs = state->regs;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BPF_REG; i++) अणु
		mark_reg_not_init(env, regs, i);
		regs[i].live = REG_LIVE_NONE;
		regs[i].parent = शून्य;
		regs[i].subreg_def = DEF_NOT_SUBREG;
	पूर्ण

	/* frame poपूर्णांकer */
	regs[BPF_REG_FP].type = PTR_TO_STACK;
	mark_reg_known_zero(env, regs, BPF_REG_FP);
	regs[BPF_REG_FP].frameno = state->frameno;
पूर्ण

#घोषणा BPF_MAIN_FUNC (-1)
अटल व्योम init_func_state(काष्ठा bpf_verअगरier_env *env,
			    काष्ठा bpf_func_state *state,
			    पूर्णांक callsite, पूर्णांक frameno, पूर्णांक subprogno)
अणु
	state->callsite = callsite;
	state->frameno = frameno;
	state->subprogno = subprogno;
	init_reg_state(env, state);
पूर्ण

क्रमागत reg_arg_type अणु
	SRC_OP,		/* रेजिस्टर is used as source opeअक्रम */
	DST_OP,		/* रेजिस्टर is used as destination opeअक्रम */
	DST_OP_NO_MARK	/* same as above, check only, करोn't mark */
पूर्ण;

अटल पूर्णांक cmp_subprogs(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	वापस ((काष्ठा bpf_subprog_info *)a)->start -
	       ((काष्ठा bpf_subprog_info *)b)->start;
पूर्ण

अटल पूर्णांक find_subprog(काष्ठा bpf_verअगरier_env *env, पूर्णांक off)
अणु
	काष्ठा bpf_subprog_info *p;

	p = द्वा_खोज(&off, env->subprog_info, env->subprog_cnt,
		    माप(env->subprog_info[0]), cmp_subprogs);
	अगर (!p)
		वापस -ENOENT;
	वापस p - env->subprog_info;

पूर्ण

अटल पूर्णांक add_subprog(काष्ठा bpf_verअगरier_env *env, पूर्णांक off)
अणु
	पूर्णांक insn_cnt = env->prog->len;
	पूर्णांक ret;

	अगर (off >= insn_cnt || off < 0) अणु
		verbose(env, "call to invalid destination\n");
		वापस -EINVAL;
	पूर्ण
	ret = find_subprog(env, off);
	अगर (ret >= 0)
		वापस ret;
	अगर (env->subprog_cnt >= BPF_MAX_SUBPROGS) अणु
		verbose(env, "too many subprograms\n");
		वापस -E2BIG;
	पूर्ण
	/* determine subprog starts. The end is one beक्रमe the next starts */
	env->subprog_info[env->subprog_cnt++].start = off;
	sort(env->subprog_info, env->subprog_cnt,
	     माप(env->subprog_info[0]), cmp_subprogs, शून्य);
	वापस env->subprog_cnt - 1;
पूर्ण

काष्ठा bpf_kfunc_desc अणु
	काष्ठा btf_func_model func_model;
	u32 func_id;
	s32 imm;
पूर्ण;

#घोषणा MAX_KFUNC_DESCS 256
काष्ठा bpf_kfunc_desc_tab अणु
	काष्ठा bpf_kfunc_desc descs[MAX_KFUNC_DESCS];
	u32 nr_descs;
पूर्ण;

अटल पूर्णांक kfunc_desc_cmp_by_id(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा bpf_kfunc_desc *d0 = a;
	स्थिर काष्ठा bpf_kfunc_desc *d1 = b;

	/* func_id is not greater than BTF_MAX_TYPE */
	वापस d0->func_id - d1->func_id;
पूर्ण

अटल स्थिर काष्ठा bpf_kfunc_desc *
find_kfunc_desc(स्थिर काष्ठा bpf_prog *prog, u32 func_id)
अणु
	काष्ठा bpf_kfunc_desc desc = अणु
		.func_id = func_id,
	पूर्ण;
	काष्ठा bpf_kfunc_desc_tab *tab;

	tab = prog->aux->kfunc_tab;
	वापस द्वा_खोज(&desc, tab->descs, tab->nr_descs,
		       माप(tab->descs[0]), kfunc_desc_cmp_by_id);
पूर्ण

अटल पूर्णांक add_kfunc_call(काष्ठा bpf_verअगरier_env *env, u32 func_id)
अणु
	स्थिर काष्ठा btf_type *func, *func_proto;
	काष्ठा bpf_kfunc_desc_tab *tab;
	काष्ठा bpf_prog_aux *prog_aux;
	काष्ठा bpf_kfunc_desc *desc;
	स्थिर अक्षर *func_name;
	अचिन्हित दीर्घ addr;
	पूर्णांक err;

	prog_aux = env->prog->aux;
	tab = prog_aux->kfunc_tab;
	अगर (!tab) अणु
		अगर (!btf_vmlinux) अणु
			verbose(env, "calling kernel function is not supported without CONFIG_DEBUG_INFO_BTF\n");
			वापस -ENOTSUPP;
		पूर्ण

		अगर (!env->prog->jit_requested) अणु
			verbose(env, "JIT is required for calling kernel function\n");
			वापस -ENOTSUPP;
		पूर्ण

		अगर (!bpf_jit_supports_kfunc_call()) अणु
			verbose(env, "JIT does not support calling kernel function\n");
			वापस -ENOTSUPP;
		पूर्ण

		अगर (!env->prog->gpl_compatible) अणु
			verbose(env, "cannot call kernel function from non-GPL compatible program\n");
			वापस -EINVAL;
		पूर्ण

		tab = kzalloc(माप(*tab), GFP_KERNEL);
		अगर (!tab)
			वापस -ENOMEM;
		prog_aux->kfunc_tab = tab;
	पूर्ण

	अगर (find_kfunc_desc(env->prog, func_id))
		वापस 0;

	अगर (tab->nr_descs == MAX_KFUNC_DESCS) अणु
		verbose(env, "too many different kernel function calls\n");
		वापस -E2BIG;
	पूर्ण

	func = btf_type_by_id(btf_vmlinux, func_id);
	अगर (!func || !btf_type_is_func(func)) अणु
		verbose(env, "kernel btf_id %u is not a function\n",
			func_id);
		वापस -EINVAL;
	पूर्ण
	func_proto = btf_type_by_id(btf_vmlinux, func->type);
	अगर (!func_proto || !btf_type_is_func_proto(func_proto)) अणु
		verbose(env, "kernel function btf_id %u does not have a valid func_proto\n",
			func_id);
		वापस -EINVAL;
	पूर्ण

	func_name = btf_name_by_offset(btf_vmlinux, func->name_off);
	addr = kallsyms_lookup_name(func_name);
	अगर (!addr) अणु
		verbose(env, "cannot find address for kernel function %s\n",
			func_name);
		वापस -EINVAL;
	पूर्ण

	desc = &tab->descs[tab->nr_descs++];
	desc->func_id = func_id;
	desc->imm = BPF_CAST_CALL(addr) - __bpf_call_base;
	err = btf_distill_func_proto(&env->log, btf_vmlinux,
				     func_proto, func_name,
				     &desc->func_model);
	अगर (!err)
		sort(tab->descs, tab->nr_descs, माप(tab->descs[0]),
		     kfunc_desc_cmp_by_id, शून्य);
	वापस err;
पूर्ण

अटल पूर्णांक kfunc_desc_cmp_by_imm(स्थिर व्योम *a, स्थिर व्योम *b)
अणु
	स्थिर काष्ठा bpf_kfunc_desc *d0 = a;
	स्थिर काष्ठा bpf_kfunc_desc *d1 = b;

	अगर (d0->imm > d1->imm)
		वापस 1;
	अन्यथा अगर (d0->imm < d1->imm)
		वापस -1;
	वापस 0;
पूर्ण

अटल व्योम sort_kfunc_descs_by_imm(काष्ठा bpf_prog *prog)
अणु
	काष्ठा bpf_kfunc_desc_tab *tab;

	tab = prog->aux->kfunc_tab;
	अगर (!tab)
		वापस;

	sort(tab->descs, tab->nr_descs, माप(tab->descs[0]),
	     kfunc_desc_cmp_by_imm, शून्य);
पूर्ण

bool bpf_prog_has_kfunc_call(स्थिर काष्ठा bpf_prog *prog)
अणु
	वापस !!prog->aux->kfunc_tab;
पूर्ण

स्थिर काष्ठा btf_func_model *
bpf_jit_find_kfunc_model(स्थिर काष्ठा bpf_prog *prog,
			 स्थिर काष्ठा bpf_insn *insn)
अणु
	स्थिर काष्ठा bpf_kfunc_desc desc = अणु
		.imm = insn->imm,
	पूर्ण;
	स्थिर काष्ठा bpf_kfunc_desc *res;
	काष्ठा bpf_kfunc_desc_tab *tab;

	tab = prog->aux->kfunc_tab;
	res = द्वा_खोज(&desc, tab->descs, tab->nr_descs,
		      माप(tab->descs[0]), kfunc_desc_cmp_by_imm);

	वापस res ? &res->func_model : शून्य;
पूर्ण

अटल पूर्णांक add_subprog_and_kfunc(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_subprog_info *subprog = env->subprog_info;
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	पूर्णांक i, ret, insn_cnt = env->prog->len;

	/* Add entry function. */
	ret = add_subprog(env, 0);
	अगर (ret)
		वापस ret;

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		अगर (!bpf_pseuकरो_func(insn) && !bpf_pseuकरो_call(insn) &&
		    !bpf_pseuकरो_kfunc_call(insn))
			जारी;

		अगर (!env->bpf_capable) अणु
			verbose(env, "loading/calling other bpf or kernel functions are allowed for CAP_BPF and CAP_SYS_ADMIN\n");
			वापस -EPERM;
		पूर्ण

		अगर (bpf_pseuकरो_func(insn)) अणु
			ret = add_subprog(env, i + insn->imm + 1);
			अगर (ret >= 0)
				/* remember subprog */
				insn[1].imm = ret;
		पूर्ण अन्यथा अगर (bpf_pseuकरो_call(insn)) अणु
			ret = add_subprog(env, i + insn->imm + 1);
		पूर्ण अन्यथा अणु
			ret = add_kfunc_call(env, insn->imm);
		पूर्ण

		अगर (ret < 0)
			वापस ret;
	पूर्ण

	/* Add a fake 'exit' subprog which could simplअगरy subprog iteration
	 * logic. 'subprog_cnt' should not be increased.
	 */
	subprog[env->subprog_cnt].start = insn_cnt;

	अगर (env->log.level & BPF_LOG_LEVEL2)
		क्रम (i = 0; i < env->subprog_cnt; i++)
			verbose(env, "func#%d @%d\n", i, subprog[i].start);

	वापस 0;
पूर्ण

अटल पूर्णांक check_subprogs(काष्ठा bpf_verअगरier_env *env)
अणु
	पूर्णांक i, subprog_start, subprog_end, off, cur_subprog = 0;
	काष्ठा bpf_subprog_info *subprog = env->subprog_info;
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	पूर्णांक insn_cnt = env->prog->len;

	/* now check that all jumps are within the same subprog */
	subprog_start = subprog[cur_subprog].start;
	subprog_end = subprog[cur_subprog + 1].start;
	क्रम (i = 0; i < insn_cnt; i++) अणु
		u8 code = insn[i].code;

		अगर (code == (BPF_JMP | BPF_CALL) &&
		    insn[i].imm == BPF_FUNC_tail_call &&
		    insn[i].src_reg != BPF_PSEUDO_CALL)
			subprog[cur_subprog].has_tail_call = true;
		अगर (BPF_CLASS(code) == BPF_LD &&
		    (BPF_MODE(code) == BPF_ABS || BPF_MODE(code) == BPF_IND))
			subprog[cur_subprog].has_ld_असल = true;
		अगर (BPF_CLASS(code) != BPF_JMP && BPF_CLASS(code) != BPF_JMP32)
			जाओ next;
		अगर (BPF_OP(code) == BPF_EXIT || BPF_OP(code) == BPF_CALL)
			जाओ next;
		off = i + insn[i].off + 1;
		अगर (off < subprog_start || off >= subprog_end) अणु
			verbose(env, "jump out of range from insn %d to %d\n", i, off);
			वापस -EINVAL;
		पूर्ण
next:
		अगर (i == subprog_end - 1) अणु
			/* to aव्योम fall-through from one subprog पूर्णांकo another
			 * the last insn of the subprog should be either निकास
			 * or unconditional jump back
			 */
			अगर (code != (BPF_JMP | BPF_EXIT) &&
			    code != (BPF_JMP | BPF_JA)) अणु
				verbose(env, "last insn is not an exit or jmp\n");
				वापस -EINVAL;
			पूर्ण
			subprog_start = subprog_end;
			cur_subprog++;
			अगर (cur_subprog < env->subprog_cnt)
				subprog_end = subprog[cur_subprog + 1].start;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Parentage chain of this रेजिस्टर (or stack slot) should take care of all
 * issues like callee-saved रेजिस्टरs, stack slot allocation समय, etc.
 */
अटल पूर्णांक mark_reg_पढ़ो(काष्ठा bpf_verअगरier_env *env,
			 स्थिर काष्ठा bpf_reg_state *state,
			 काष्ठा bpf_reg_state *parent, u8 flag)
अणु
	bool ग_लिखोs = parent == state->parent; /* Observe ग_लिखो marks */
	पूर्णांक cnt = 0;

	जबतक (parent) अणु
		/* अगर पढ़ो wasn't screened by an earlier ग_लिखो ... */
		अगर (ग_लिखोs && state->live & REG_LIVE_WRITTEN)
			अवरोध;
		अगर (parent->live & REG_LIVE_DONE) अणु
			verbose(env, "verifier BUG type %s var_off %lld off %d\n",
				reg_type_str[parent->type],
				parent->var_off.value, parent->off);
			वापस -EFAULT;
		पूर्ण
		/* The first condition is more likely to be true than the
		 * second, checked it first.
		 */
		अगर ((parent->live & REG_LIVE_READ) == flag ||
		    parent->live & REG_LIVE_READ64)
			/* The parentage chain never changes and
			 * this parent was alपढ़ोy marked as LIVE_READ.
			 * There is no need to keep walking the chain again and
			 * keep re-marking all parents as LIVE_READ.
			 * This हाल happens when the same रेजिस्टर is पढ़ो
			 * multiple बार without ग_लिखोs पूर्णांकo it in-between.
			 * Also, अगर parent has the stronger REG_LIVE_READ64 set,
			 * then no need to set the weak REG_LIVE_READ32.
			 */
			अवरोध;
		/* ... then we depend on parent's value */
		parent->live |= flag;
		/* REG_LIVE_READ64 overrides REG_LIVE_READ32. */
		अगर (flag == REG_LIVE_READ64)
			parent->live &= ~REG_LIVE_READ32;
		state = parent;
		parent = state->parent;
		ग_लिखोs = true;
		cnt++;
	पूर्ण

	अगर (env->दीर्घest_mark_पढ़ो_walk < cnt)
		env->दीर्घest_mark_पढ़ो_walk = cnt;
	वापस 0;
पूर्ण

/* This function is supposed to be used by the following 32-bit optimization
 * code only. It वापसs TRUE अगर the source or destination रेजिस्टर operates
 * on 64-bit, otherwise वापस FALSE.
 */
अटल bool is_reg64(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn,
		     u32 regno, काष्ठा bpf_reg_state *reg, क्रमागत reg_arg_type t)
अणु
	u8 code, class, op;

	code = insn->code;
	class = BPF_CLASS(code);
	op = BPF_OP(code);
	अगर (class == BPF_JMP) अणु
		/* BPF_EXIT क्रम "main" will reach here. Return TRUE
		 * conservatively.
		 */
		अगर (op == BPF_EXIT)
			वापस true;
		अगर (op == BPF_CALL) अणु
			/* BPF to BPF call will reach here because of marking
			 * caller saved clobber with DST_OP_NO_MARK क्रम which we
			 * करोn't care the रेजिस्टर def because they are anyway
			 * marked as NOT_INIT alपढ़ोy.
			 */
			अगर (insn->src_reg == BPF_PSEUDO_CALL)
				वापस false;
			/* Helper call will reach here because of arg type
			 * check, conservatively वापस TRUE.
			 */
			अगर (t == SRC_OP)
				वापस true;

			वापस false;
		पूर्ण
	पूर्ण

	अगर (class == BPF_ALU64 || class == BPF_JMP ||
	    /* BPF_END always use BPF_ALU class. */
	    (class == BPF_ALU && op == BPF_END && insn->imm == 64))
		वापस true;

	अगर (class == BPF_ALU || class == BPF_JMP32)
		वापस false;

	अगर (class == BPF_LDX) अणु
		अगर (t != SRC_OP)
			वापस BPF_SIZE(code) == BPF_DW;
		/* LDX source must be ptr. */
		वापस true;
	पूर्ण

	अगर (class == BPF_STX) अणु
		/* BPF_STX (including atomic variants) has multiple source
		 * opeअक्रमs, one of which is a ptr. Check whether the caller is
		 * asking about it.
		 */
		अगर (t == SRC_OP && reg->type != SCALAR_VALUE)
			वापस true;
		वापस BPF_SIZE(code) == BPF_DW;
	पूर्ण

	अगर (class == BPF_LD) अणु
		u8 mode = BPF_MODE(code);

		/* LD_IMM64 */
		अगर (mode == BPF_IMM)
			वापस true;

		/* Both LD_IND and LD_ABS वापस 32-bit data. */
		अगर (t != SRC_OP)
			वापस  false;

		/* Implicit ctx ptr. */
		अगर (regno == BPF_REG_6)
			वापस true;

		/* Explicit source could be any width. */
		वापस true;
	पूर्ण

	अगर (class == BPF_ST)
		/* The only source रेजिस्टर क्रम BPF_ST is a ptr. */
		वापस true;

	/* Conservatively वापस true at शेष. */
	वापस true;
पूर्ण

/* Return the regno defined by the insn, or -1. */
अटल पूर्णांक insn_def_regno(स्थिर काष्ठा bpf_insn *insn)
अणु
	चयन (BPF_CLASS(insn->code)) अणु
	हाल BPF_JMP:
	हाल BPF_JMP32:
	हाल BPF_ST:
		वापस -1;
	हाल BPF_STX:
		अगर (BPF_MODE(insn->code) == BPF_ATOMIC &&
		    (insn->imm & BPF_FETCH)) अणु
			अगर (insn->imm == BPF_CMPXCHG)
				वापस BPF_REG_0;
			अन्यथा
				वापस insn->src_reg;
		पूर्ण अन्यथा अणु
			वापस -1;
		पूर्ण
	शेष:
		वापस insn->dst_reg;
	पूर्ण
पूर्ण

/* Return TRUE अगर INSN has defined any 32-bit value explicitly. */
अटल bool insn_has_def32(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn)
अणु
	पूर्णांक dst_reg = insn_def_regno(insn);

	अगर (dst_reg == -1)
		वापस false;

	वापस !is_reg64(env, insn, dst_reg, शून्य, DST_OP);
पूर्ण

अटल व्योम mark_insn_zext(काष्ठा bpf_verअगरier_env *env,
			   काष्ठा bpf_reg_state *reg)
अणु
	s32 def_idx = reg->subreg_def;

	अगर (def_idx == DEF_NOT_SUBREG)
		वापस;

	env->insn_aux_data[def_idx - 1].zext_dst = true;
	/* The dst will be zero extended, so won't be sub-रेजिस्टर anymore. */
	reg->subreg_def = DEF_NOT_SUBREG;
पूर्ण

अटल पूर्णांक check_reg_arg(काष्ठा bpf_verअगरier_env *env, u32 regno,
			 क्रमागत reg_arg_type t)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	काष्ठा bpf_insn *insn = env->prog->insnsi + env->insn_idx;
	काष्ठा bpf_reg_state *reg, *regs = state->regs;
	bool rw64;

	अगर (regno >= MAX_BPF_REG) अणु
		verbose(env, "R%d is invalid\n", regno);
		वापस -EINVAL;
	पूर्ण

	reg = &regs[regno];
	rw64 = is_reg64(env, insn, regno, reg, t);
	अगर (t == SRC_OP) अणु
		/* check whether रेजिस्टर used as source opeअक्रम can be पढ़ो */
		अगर (reg->type == NOT_INIT) अणु
			verbose(env, "R%d !read_ok\n", regno);
			वापस -EACCES;
		पूर्ण
		/* We करोn't need to worry about FP liveness because it's पढ़ो-only */
		अगर (regno == BPF_REG_FP)
			वापस 0;

		अगर (rw64)
			mark_insn_zext(env, reg);

		वापस mark_reg_पढ़ो(env, reg, reg->parent,
				     rw64 ? REG_LIVE_READ64 : REG_LIVE_READ32);
	पूर्ण अन्यथा अणु
		/* check whether रेजिस्टर used as dest opeअक्रम can be written to */
		अगर (regno == BPF_REG_FP) अणु
			verbose(env, "frame pointer is read only\n");
			वापस -EACCES;
		पूर्ण
		reg->live |= REG_LIVE_WRITTEN;
		reg->subreg_def = rw64 ? DEF_NOT_SUBREG : env->insn_idx + 1;
		अगर (t == DST_OP)
			mark_reg_unknown(env, regs, regno);
	पूर्ण
	वापस 0;
पूर्ण

/* क्रम any branch, call, निकास record the history of jmps in the given state */
अटल पूर्णांक push_jmp_history(काष्ठा bpf_verअगरier_env *env,
			    काष्ठा bpf_verअगरier_state *cur)
अणु
	u32 cnt = cur->jmp_history_cnt;
	काष्ठा bpf_idx_pair *p;

	cnt++;
	p = kपुनः_स्मृति(cur->jmp_history, cnt * माप(*p), GFP_USER);
	अगर (!p)
		वापस -ENOMEM;
	p[cnt - 1].idx = env->insn_idx;
	p[cnt - 1].prev_idx = env->prev_insn_idx;
	cur->jmp_history = p;
	cur->jmp_history_cnt = cnt;
	वापस 0;
पूर्ण

/* Backtrack one insn at a समय. If idx is not at the top of recorded
 * history then previous inकाष्ठाion came from straight line execution.
 */
अटल पूर्णांक get_prev_insn_idx(काष्ठा bpf_verअगरier_state *st, पूर्णांक i,
			     u32 *history)
अणु
	u32 cnt = *history;

	अगर (cnt && st->jmp_history[cnt - 1].idx == i) अणु
		i = st->jmp_history[cnt - 1].prev_idx;
		(*history)--;
	पूर्ण अन्यथा अणु
		i--;
	पूर्ण
	वापस i;
पूर्ण

अटल स्थिर अक्षर *disयंत्र_kfunc_name(व्योम *data, स्थिर काष्ठा bpf_insn *insn)
अणु
	स्थिर काष्ठा btf_type *func;

	अगर (insn->src_reg != BPF_PSEUDO_KFUNC_CALL)
		वापस शून्य;

	func = btf_type_by_id(btf_vmlinux, insn->imm);
	वापस btf_name_by_offset(btf_vmlinux, func->name_off);
पूर्ण

/* For given verअगरier state backtrack_insn() is called from the last insn to
 * the first insn. Its purpose is to compute a biपंचांगask of रेजिस्टरs and
 * stack slots that needs precision in the parent verअगरier state.
 */
अटल पूर्णांक backtrack_insn(काष्ठा bpf_verअगरier_env *env, पूर्णांक idx,
			  u32 *reg_mask, u64 *stack_mask)
अणु
	स्थिर काष्ठा bpf_insn_cbs cbs = अणु
		.cb_call	= disयंत्र_kfunc_name,
		.cb_prपूर्णांक	= verbose,
		.निजी_data	= env,
	पूर्ण;
	काष्ठा bpf_insn *insn = env->prog->insnsi + idx;
	u8 class = BPF_CLASS(insn->code);
	u8 opcode = BPF_OP(insn->code);
	u8 mode = BPF_MODE(insn->code);
	u32 dreg = 1u << insn->dst_reg;
	u32 sreg = 1u << insn->src_reg;
	u32 spi;

	अगर (insn->code == 0)
		वापस 0;
	अगर (env->log.level & BPF_LOG_LEVEL) अणु
		verbose(env, "regs=%x stack=%llx before ", *reg_mask, *stack_mask);
		verbose(env, "%d: ", idx);
		prपूर्णांक_bpf_insn(&cbs, insn, env->allow_ptr_leaks);
	पूर्ण

	अगर (class == BPF_ALU || class == BPF_ALU64) अणु
		अगर (!(*reg_mask & dreg))
			वापस 0;
		अगर (opcode == BPF_MOV) अणु
			अगर (BPF_SRC(insn->code) == BPF_X) अणु
				/* dreg = sreg
				 * dreg needs precision after this insn
				 * sreg needs precision beक्रमe this insn
				 */
				*reg_mask &= ~dreg;
				*reg_mask |= sreg;
			पूर्ण अन्यथा अणु
				/* dreg = K
				 * dreg needs precision after this insn.
				 * Corresponding रेजिस्टर is alपढ़ोy marked
				 * as precise=true in this verअगरier state.
				 * No further markings in parent are necessary
				 */
				*reg_mask &= ~dreg;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (BPF_SRC(insn->code) == BPF_X) अणु
				/* dreg += sreg
				 * both dreg and sreg need precision
				 * beक्रमe this insn
				 */
				*reg_mask |= sreg;
			पूर्ण /* अन्यथा dreg += K
			   * dreg still needs precision beक्रमe this insn
			   */
		पूर्ण
	पूर्ण अन्यथा अगर (class == BPF_LDX) अणु
		अगर (!(*reg_mask & dreg))
			वापस 0;
		*reg_mask &= ~dreg;

		/* scalars can only be spilled पूर्णांकo stack w/o losing precision.
		 * Load from any other memory can be zero extended.
		 * The desire to keep that precision is alपढ़ोy indicated
		 * by 'precise' mark in corresponding रेजिस्टर of this state.
		 * No further tracking necessary.
		 */
		अगर (insn->src_reg != BPF_REG_FP)
			वापस 0;
		अगर (BPF_SIZE(insn->code) != BPF_DW)
			वापस 0;

		/* dreg = *(u64 *)[fp - off] was a fill from the stack.
		 * that [fp - off] slot contains scalar that needs to be
		 * tracked with precision
		 */
		spi = (-insn->off - 1) / BPF_REG_SIZE;
		अगर (spi >= 64) अणु
			verbose(env, "BUG spi %d\n", spi);
			WARN_ONCE(1, "verifier backtracking bug");
			वापस -EFAULT;
		पूर्ण
		*stack_mask |= 1ull << spi;
	पूर्ण अन्यथा अगर (class == BPF_STX || class == BPF_ST) अणु
		अगर (*reg_mask & dreg)
			/* stx & st shouldn't be using _scalar_ dst_reg
			 * to access memory. It means backtracking
			 * encountered a हाल of poपूर्णांकer subtraction.
			 */
			वापस -ENOTSUPP;
		/* scalars can only be spilled पूर्णांकo stack */
		अगर (insn->dst_reg != BPF_REG_FP)
			वापस 0;
		अगर (BPF_SIZE(insn->code) != BPF_DW)
			वापस 0;
		spi = (-insn->off - 1) / BPF_REG_SIZE;
		अगर (spi >= 64) अणु
			verbose(env, "BUG spi %d\n", spi);
			WARN_ONCE(1, "verifier backtracking bug");
			वापस -EFAULT;
		पूर्ण
		अगर (!(*stack_mask & (1ull << spi)))
			वापस 0;
		*stack_mask &= ~(1ull << spi);
		अगर (class == BPF_STX)
			*reg_mask |= sreg;
	पूर्ण अन्यथा अगर (class == BPF_JMP || class == BPF_JMP32) अणु
		अगर (opcode == BPF_CALL) अणु
			अगर (insn->src_reg == BPF_PSEUDO_CALL)
				वापस -ENOTSUPP;
			/* regular helper call sets R0 */
			*reg_mask &= ~1;
			अगर (*reg_mask & 0x3f) अणु
				/* अगर backtracing was looking क्रम रेजिस्टरs R1-R5
				 * they should have been found alपढ़ोy.
				 */
				verbose(env, "BUG regs %x\n", *reg_mask);
				WARN_ONCE(1, "verifier backtracking bug");
				वापस -EFAULT;
			पूर्ण
		पूर्ण अन्यथा अगर (opcode == BPF_EXIT) अणु
			वापस -ENOTSUPP;
		पूर्ण
	पूर्ण अन्यथा अगर (class == BPF_LD) अणु
		अगर (!(*reg_mask & dreg))
			वापस 0;
		*reg_mask &= ~dreg;
		/* It's ld_imm64 or ld_असल or ld_ind.
		 * For ld_imm64 no further tracking of precision
		 * पूर्णांकo parent is necessary
		 */
		अगर (mode == BPF_IND || mode == BPF_ABS)
			/* to be analyzed */
			वापस -ENOTSUPP;
	पूर्ण
	वापस 0;
पूर्ण

/* the scalar precision tracking algorithm:
 * . at the start all रेजिस्टरs have precise=false.
 * . scalar ranges are tracked as normal through alu and jmp insns.
 * . once precise value of the scalar रेजिस्टर is used in:
 *   .  ptr + scalar alu
 *   . अगर (scalar cond K|scalar)
 *   .  helper_call(.., scalar, ...) where ARG_CONST is expected
 *   backtrack through the verअगरier states and mark all रेजिस्टरs and
 *   stack slots with spilled स्थिरants that these scalar regisers
 *   should be precise.
 * . during state pruning two रेजिस्टरs (or spilled stack slots)
 *   are equivalent अगर both are not precise.
 *
 * Note the verअगरier cannot simply walk रेजिस्टर parentage chain,
 * since many dअगरferent रेजिस्टरs and stack slots could have been
 * used to compute single precise scalar.
 *
 * The approach of starting with precise=true क्रम all रेजिस्टरs and then
 * backtrack to mark a रेजिस्टर as not precise when the verअगरier detects
 * that program करोesn't care about specअगरic value (e.g., when helper
 * takes रेजिस्टर as ARG_ANYTHING parameter) is not safe.
 *
 * It's ok to walk single parentage chain of the verअगरier states.
 * It's possible that this backtracking will go all the way till 1st insn.
 * All other branches will be explored क्रम needing precision later.
 *
 * The backtracking needs to deal with हालs like:
 *   R8=map_value(id=0,off=0,ks=4,vs=1952,imm=0) R9_w=map_value(id=0,off=40,ks=4,vs=1952,imm=0)
 * r9 -= r8
 * r5 = r9
 * अगर r5 > 0x79f जाओ pc+7
 *    R5_w=inv(id=0,umax_value=1951,var_off=(0x0; 0x7ff))
 * r5 += 1
 * ...
 * call bpf_perf_event_output#25
 *   where .arg5_type = ARG_CONST_SIZE_OR_ZERO
 *
 * and this हाल:
 * r6 = 1
 * call foo // uses callee's r6 inside to compute r0
 * r0 += r6
 * अगर r0 == 0 जाओ
 *
 * to track above reg_mask/stack_mask needs to be independent क्रम each frame.
 *
 * Also अगर parent's curframe > frame where backtracking started,
 * the verअगरier need to mark रेजिस्टरs in both frames, otherwise callees
 * may incorrectly prune callers. This is similar to
 * commit 7640ead93924 ("bpf: verifier: make sure callees don't prune with caller differences")
 *
 * For now backtracking falls back पूर्णांकo conservative marking.
 */
अटल व्योम mark_all_scalars_precise(काष्ठा bpf_verअगरier_env *env,
				     काष्ठा bpf_verअगरier_state *st)
अणु
	काष्ठा bpf_func_state *func;
	काष्ठा bpf_reg_state *reg;
	पूर्णांक i, j;

	/* big hammer: mark all scalars precise in this path.
	 * pop_stack may still get !precise scalars.
	 */
	क्रम (; st; st = st->parent)
		क्रम (i = 0; i <= st->curframe; i++) अणु
			func = st->frame[i];
			क्रम (j = 0; j < BPF_REG_FP; j++) अणु
				reg = &func->regs[j];
				अगर (reg->type != SCALAR_VALUE)
					जारी;
				reg->precise = true;
			पूर्ण
			क्रम (j = 0; j < func->allocated_stack / BPF_REG_SIZE; j++) अणु
				अगर (func->stack[j].slot_type[0] != STACK_SPILL)
					जारी;
				reg = &func->stack[j].spilled_ptr;
				अगर (reg->type != SCALAR_VALUE)
					जारी;
				reg->precise = true;
			पूर्ण
		पूर्ण
पूर्ण

अटल पूर्णांक __mark_chain_precision(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno,
				  पूर्णांक spi)
अणु
	काष्ठा bpf_verअगरier_state *st = env->cur_state;
	पूर्णांक first_idx = st->first_insn_idx;
	पूर्णांक last_idx = env->insn_idx;
	काष्ठा bpf_func_state *func;
	काष्ठा bpf_reg_state *reg;
	u32 reg_mask = regno >= 0 ? 1u << regno : 0;
	u64 stack_mask = spi >= 0 ? 1ull << spi : 0;
	bool skip_first = true;
	bool new_marks = false;
	पूर्णांक i, err;

	अगर (!env->bpf_capable)
		वापस 0;

	func = st->frame[st->curframe];
	अगर (regno >= 0) अणु
		reg = &func->regs[regno];
		अगर (reg->type != SCALAR_VALUE) अणु
			WARN_ONCE(1, "backtracing misuse");
			वापस -EFAULT;
		पूर्ण
		अगर (!reg->precise)
			new_marks = true;
		अन्यथा
			reg_mask = 0;
		reg->precise = true;
	पूर्ण

	जबतक (spi >= 0) अणु
		अगर (func->stack[spi].slot_type[0] != STACK_SPILL) अणु
			stack_mask = 0;
			अवरोध;
		पूर्ण
		reg = &func->stack[spi].spilled_ptr;
		अगर (reg->type != SCALAR_VALUE) अणु
			stack_mask = 0;
			अवरोध;
		पूर्ण
		अगर (!reg->precise)
			new_marks = true;
		अन्यथा
			stack_mask = 0;
		reg->precise = true;
		अवरोध;
	पूर्ण

	अगर (!new_marks)
		वापस 0;
	अगर (!reg_mask && !stack_mask)
		वापस 0;
	क्रम (;;) अणु
		DECLARE_BITMAP(mask, 64);
		u32 history = st->jmp_history_cnt;

		अगर (env->log.level & BPF_LOG_LEVEL)
			verbose(env, "last_idx %d first_idx %d\n", last_idx, first_idx);
		क्रम (i = last_idx;;) अणु
			अगर (skip_first) अणु
				err = 0;
				skip_first = false;
			पूर्ण अन्यथा अणु
				err = backtrack_insn(env, i, &reg_mask, &stack_mask);
			पूर्ण
			अगर (err == -ENOTSUPP) अणु
				mark_all_scalars_precise(env, st);
				वापस 0;
			पूर्ण अन्यथा अगर (err) अणु
				वापस err;
			पूर्ण
			अगर (!reg_mask && !stack_mask)
				/* Found assignment(s) पूर्णांकo tracked रेजिस्टर in this state.
				 * Since this state is alपढ़ोy marked, just वापस.
				 * Nothing to be tracked further in the parent state.
				 */
				वापस 0;
			अगर (i == first_idx)
				अवरोध;
			i = get_prev_insn_idx(st, i, &history);
			अगर (i >= env->prog->len) अणु
				/* This can happen अगर backtracking reached insn 0
				 * and there are still reg_mask or stack_mask
				 * to backtrack.
				 * It means the backtracking missed the spot where
				 * particular रेजिस्टर was initialized with a स्थिरant.
				 */
				verbose(env, "BUG backtracking idx %d\n", i);
				WARN_ONCE(1, "verifier backtracking bug");
				वापस -EFAULT;
			पूर्ण
		पूर्ण
		st = st->parent;
		अगर (!st)
			अवरोध;

		new_marks = false;
		func = st->frame[st->curframe];
		biपंचांगap_from_u64(mask, reg_mask);
		क्रम_each_set_bit(i, mask, 32) अणु
			reg = &func->regs[i];
			अगर (reg->type != SCALAR_VALUE) अणु
				reg_mask &= ~(1u << i);
				जारी;
			पूर्ण
			अगर (!reg->precise)
				new_marks = true;
			reg->precise = true;
		पूर्ण

		biपंचांगap_from_u64(mask, stack_mask);
		क्रम_each_set_bit(i, mask, 64) अणु
			अगर (i >= func->allocated_stack / BPF_REG_SIZE) अणु
				/* the sequence of inकाष्ठाions:
				 * 2: (bf) r3 = r10
				 * 3: (7b) *(u64 *)(r3 -8) = r0
				 * 4: (79) r4 = *(u64 *)(r10 -8)
				 * करोesn't contain jmps. It's backtracked
				 * as a single block.
				 * During backtracking insn 3 is not recognized as
				 * stack access, so at the end of backtracking
				 * stack slot fp-8 is still marked in stack_mask.
				 * However the parent state may not have accessed
				 * fp-8 and it's "unallocated" stack space.
				 * In such हाल fallback to conservative.
				 */
				mark_all_scalars_precise(env, st);
				वापस 0;
			पूर्ण

			अगर (func->stack[i].slot_type[0] != STACK_SPILL) अणु
				stack_mask &= ~(1ull << i);
				जारी;
			पूर्ण
			reg = &func->stack[i].spilled_ptr;
			अगर (reg->type != SCALAR_VALUE) अणु
				stack_mask &= ~(1ull << i);
				जारी;
			पूर्ण
			अगर (!reg->precise)
				new_marks = true;
			reg->precise = true;
		पूर्ण
		अगर (env->log.level & BPF_LOG_LEVEL) अणु
			prपूर्णांक_verअगरier_state(env, func);
			verbose(env, "parent %s regs=%x stack=%llx marks\n",
				new_marks ? "didn't have" : "already had",
				reg_mask, stack_mask);
		पूर्ण

		अगर (!reg_mask && !stack_mask)
			अवरोध;
		अगर (!new_marks)
			अवरोध;

		last_idx = st->last_insn_idx;
		first_idx = st->first_insn_idx;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक mark_chain_precision(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno)
अणु
	वापस __mark_chain_precision(env, regno, -1);
पूर्ण

अटल पूर्णांक mark_chain_precision_stack(काष्ठा bpf_verअगरier_env *env, पूर्णांक spi)
अणु
	वापस __mark_chain_precision(env, -1, spi);
पूर्ण

अटल bool is_spillable_regtype(क्रमागत bpf_reg_type type)
अणु
	चयन (type) अणु
	हाल PTR_TO_MAP_VALUE:
	हाल PTR_TO_MAP_VALUE_OR_शून्य:
	हाल PTR_TO_STACK:
	हाल PTR_TO_CTX:
	हाल PTR_TO_PACKET:
	हाल PTR_TO_PACKET_META:
	हाल PTR_TO_PACKET_END:
	हाल PTR_TO_FLOW_KEYS:
	हाल CONST_PTR_TO_MAP:
	हाल PTR_TO_SOCKET:
	हाल PTR_TO_SOCKET_OR_शून्य:
	हाल PTR_TO_SOCK_COMMON:
	हाल PTR_TO_SOCK_COMMON_OR_शून्य:
	हाल PTR_TO_TCP_SOCK:
	हाल PTR_TO_TCP_SOCK_OR_शून्य:
	हाल PTR_TO_XDP_SOCK:
	हाल PTR_TO_BTF_ID:
	हाल PTR_TO_BTF_ID_OR_शून्य:
	हाल PTR_TO_RDONLY_BUF:
	हाल PTR_TO_RDONLY_BUF_OR_शून्य:
	हाल PTR_TO_RDWR_BUF:
	हाल PTR_TO_RDWR_BUF_OR_शून्य:
	हाल PTR_TO_PERCPU_BTF_ID:
	हाल PTR_TO_MEM:
	हाल PTR_TO_MEM_OR_शून्य:
	हाल PTR_TO_FUNC:
	हाल PTR_TO_MAP_KEY:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* Does this रेजिस्टर contain a स्थिरant zero? */
अटल bool रेजिस्टर_is_null(काष्ठा bpf_reg_state *reg)
अणु
	वापस reg->type == SCALAR_VALUE && tnum_equals_स्थिर(reg->var_off, 0);
पूर्ण

अटल bool रेजिस्टर_is_स्थिर(काष्ठा bpf_reg_state *reg)
अणु
	वापस reg->type == SCALAR_VALUE && tnum_is_स्थिर(reg->var_off);
पूर्ण

अटल bool __is_scalar_unbounded(काष्ठा bpf_reg_state *reg)
अणु
	वापस tnum_is_unknown(reg->var_off) &&
	       reg->smin_value == S64_MIN && reg->smax_value == S64_MAX &&
	       reg->umin_value == 0 && reg->umax_value == U64_MAX &&
	       reg->s32_min_value == S32_MIN && reg->s32_max_value == S32_MAX &&
	       reg->u32_min_value == 0 && reg->u32_max_value == U32_MAX;
पूर्ण

अटल bool रेजिस्टर_is_bounded(काष्ठा bpf_reg_state *reg)
अणु
	वापस reg->type == SCALAR_VALUE && !__is_scalar_unbounded(reg);
पूर्ण

अटल bool __is_poपूर्णांकer_value(bool allow_ptr_leaks,
			       स्थिर काष्ठा bpf_reg_state *reg)
अणु
	अगर (allow_ptr_leaks)
		वापस false;

	वापस reg->type != SCALAR_VALUE;
पूर्ण

अटल व्योम save_रेजिस्टर_state(काष्ठा bpf_func_state *state,
				पूर्णांक spi, काष्ठा bpf_reg_state *reg)
अणु
	पूर्णांक i;

	state->stack[spi].spilled_ptr = *reg;
	state->stack[spi].spilled_ptr.live |= REG_LIVE_WRITTEN;

	क्रम (i = 0; i < BPF_REG_SIZE; i++)
		state->stack[spi].slot_type[i] = STACK_SPILL;
पूर्ण

/* check_stack_अणुपढ़ो,ग_लिखोपूर्ण_fixed_off functions track spill/fill of रेजिस्टरs,
 * stack boundary and alignment are checked in check_mem_access()
 */
अटल पूर्णांक check_stack_ग_लिखो_fixed_off(काष्ठा bpf_verअगरier_env *env,
				       /* stack frame we're writing to */
				       काष्ठा bpf_func_state *state,
				       पूर्णांक off, पूर्णांक size, पूर्णांक value_regno,
				       पूर्णांक insn_idx)
अणु
	काष्ठा bpf_func_state *cur; /* state of the current function */
	पूर्णांक i, slot = -off - 1, spi = slot / BPF_REG_SIZE, err;
	u32 dst_reg = env->prog->insnsi[insn_idx].dst_reg;
	काष्ठा bpf_reg_state *reg = शून्य;

	err = पुनः_स्मृति_func_state(state, round_up(slot + 1, BPF_REG_SIZE),
				 state->acquired_refs, true);
	अगर (err)
		वापस err;
	/* caller checked that off % size == 0 and -MAX_BPF_STACK <= off < 0,
	 * so it's aligned access and [off, off + size) are within stack limits
	 */
	अगर (!env->allow_ptr_leaks &&
	    state->stack[spi].slot_type[0] == STACK_SPILL &&
	    size != BPF_REG_SIZE) अणु
		verbose(env, "attempt to corrupt spilled pointer on stack\n");
		वापस -EACCES;
	पूर्ण

	cur = env->cur_state->frame[env->cur_state->curframe];
	अगर (value_regno >= 0)
		reg = &cur->regs[value_regno];

	अगर (reg && size == BPF_REG_SIZE && रेजिस्टर_is_bounded(reg) &&
	    !रेजिस्टर_is_null(reg) && env->bpf_capable) अणु
		अगर (dst_reg != BPF_REG_FP) अणु
			/* The backtracking logic can only recognize explicit
			 * stack slot address like [fp - 8]. Other spill of
			 * scalar via dअगरferent रेजिस्टर has to be conervative.
			 * Backtrack from here and mark all रेजिस्टरs as precise
			 * that contributed पूर्णांकo 'reg' being a स्थिरant.
			 */
			err = mark_chain_precision(env, value_regno);
			अगर (err)
				वापस err;
		पूर्ण
		save_रेजिस्टर_state(state, spi, reg);
	पूर्ण अन्यथा अगर (reg && is_spillable_regtype(reg->type)) अणु
		/* रेजिस्टर containing poपूर्णांकer is being spilled पूर्णांकo stack */
		अगर (size != BPF_REG_SIZE) अणु
			verbose_linfo(env, insn_idx, "; ");
			verbose(env, "invalid size of register spill\n");
			वापस -EACCES;
		पूर्ण

		अगर (state != cur && reg->type == PTR_TO_STACK) अणु
			verbose(env, "cannot spill pointers to stack into stack frame of the caller\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!env->bypass_spec_v4) अणु
			bool sanitize = false;

			अगर (state->stack[spi].slot_type[0] == STACK_SPILL &&
			    रेजिस्टर_is_स्थिर(&state->stack[spi].spilled_ptr))
				sanitize = true;
			क्रम (i = 0; i < BPF_REG_SIZE; i++)
				अगर (state->stack[spi].slot_type[i] == STACK_MISC) अणु
					sanitize = true;
					अवरोध;
				पूर्ण
			अगर (sanitize) अणु
				पूर्णांक *poff = &env->insn_aux_data[insn_idx].sanitize_stack_off;
				पूर्णांक soff = (-spi - 1) * BPF_REG_SIZE;

				/* detected reuse of पूर्णांकeger stack slot with a poपूर्णांकer
				 * which means either llvm is reusing stack slot or
				 * an attacker is trying to exploit CVE-2018-3639
				 * (speculative store bypass)
				 * Have to sanitize that slot with preemptive
				 * store of zero.
				 */
				अगर (*poff && *poff != soff) अणु
					/* disallow programs where single insn stores
					 * पूर्णांकo two dअगरferent stack slots, since verअगरier
					 * cannot sanitize them
					 */
					verbose(env,
						"insn %d cannot access two stack slots fp%d and fp%d",
						insn_idx, *poff, soff);
					वापस -EINVAL;
				पूर्ण
				*poff = soff;
			पूर्ण
		पूर्ण
		save_रेजिस्टर_state(state, spi, reg);
	पूर्ण अन्यथा अणु
		u8 type = STACK_MISC;

		/* regular ग_लिखो of data पूर्णांकo stack destroys any spilled ptr */
		state->stack[spi].spilled_ptr.type = NOT_INIT;
		/* Mark slots as STACK_MISC अगर they beदीर्घed to spilled ptr. */
		अगर (state->stack[spi].slot_type[0] == STACK_SPILL)
			क्रम (i = 0; i < BPF_REG_SIZE; i++)
				state->stack[spi].slot_type[i] = STACK_MISC;

		/* only mark the slot as written अगर all 8 bytes were written
		 * otherwise पढ़ो propagation may incorrectly stop too soon
		 * when stack slots are partially written.
		 * This heuristic means that पढ़ो propagation will be
		 * conservative, since it will add reg_live_पढ़ो marks
		 * to stack slots all the way to first state when programs
		 * ग_लिखोs+पढ़ोs less than 8 bytes
		 */
		अगर (size == BPF_REG_SIZE)
			state->stack[spi].spilled_ptr.live |= REG_LIVE_WRITTEN;

		/* when we zero initialize stack slots mark them as such */
		अगर (reg && रेजिस्टर_is_null(reg)) अणु
			/* backtracking करोesn't work क्रम STACK_ZERO yet. */
			err = mark_chain_precision(env, value_regno);
			अगर (err)
				वापस err;
			type = STACK_ZERO;
		पूर्ण

		/* Mark slots affected by this stack ग_लिखो. */
		क्रम (i = 0; i < size; i++)
			state->stack[spi].slot_type[(slot - i) % BPF_REG_SIZE] =
				type;
	पूर्ण
	वापस 0;
पूर्ण

/* Write the stack: 'stack[ptr_regno + off] = value_regno'. 'ptr_regno' is
 * known to contain a variable offset.
 * This function checks whether the ग_लिखो is permitted and conservatively
 * tracks the effects of the ग_लिखो, considering that each stack slot in the
 * dynamic range is potentially written to.
 *
 * 'off' includes 'regno->off'.
 * 'value_regno' can be -1, meaning that an unknown value is being written to
 * the stack.
 *
 * Spilled poपूर्णांकers in range are not marked as written because we करोn't know
 * what's going to be actually written. This means that पढ़ो propagation क्रम
 * future पढ़ोs cannot be terminated by this ग_लिखो.
 *
 * For privileged programs, uninitialized stack slots are considered
 * initialized by this ग_लिखो (even though we करोn't know exactly what offsets
 * are going to be written to). The idea is that we करोn't want the verअगरier to
 * reject future पढ़ोs that access slots written to through variable offsets.
 */
अटल पूर्णांक check_stack_ग_लिखो_var_off(काष्ठा bpf_verअगरier_env *env,
				     /* func where रेजिस्टर poपूर्णांकs to */
				     काष्ठा bpf_func_state *state,
				     पूर्णांक ptr_regno, पूर्णांक off, पूर्णांक size,
				     पूर्णांक value_regno, पूर्णांक insn_idx)
अणु
	काष्ठा bpf_func_state *cur; /* state of the current function */
	पूर्णांक min_off, max_off;
	पूर्णांक i, err;
	काष्ठा bpf_reg_state *ptr_reg = शून्य, *value_reg = शून्य;
	bool writing_zero = false;
	/* set अगर the fact that we're writing a zero is used to let any
	 * stack slots reमुख्य STACK_ZERO
	 */
	bool zero_used = false;

	cur = env->cur_state->frame[env->cur_state->curframe];
	ptr_reg = &cur->regs[ptr_regno];
	min_off = ptr_reg->smin_value + off;
	max_off = ptr_reg->smax_value + off + size;
	अगर (value_regno >= 0)
		value_reg = &cur->regs[value_regno];
	अगर (value_reg && रेजिस्टर_is_null(value_reg))
		writing_zero = true;

	err = पुनः_स्मृति_func_state(state, round_up(-min_off, BPF_REG_SIZE),
				 state->acquired_refs, true);
	अगर (err)
		वापस err;


	/* Variable offset ग_लिखोs destroy any spilled poपूर्णांकers in range. */
	क्रम (i = min_off; i < max_off; i++) अणु
		u8 new_type, *stype;
		पूर्णांक slot, spi;

		slot = -i - 1;
		spi = slot / BPF_REG_SIZE;
		stype = &state->stack[spi].slot_type[slot % BPF_REG_SIZE];

		अगर (!env->allow_ptr_leaks
				&& *stype != NOT_INIT
				&& *stype != SCALAR_VALUE) अणु
			/* Reject the ग_लिखो अगर there's are spilled poपूर्णांकers in
			 * range. If we didn't reject here, the ptr status
			 * would be erased below (even though not all slots are
			 * actually overwritten), possibly खोलोing the करोor to
			 * leaks.
			 */
			verbose(env, "spilled ptr in range of var-offset stack write; insn %d, ptr off: %d",
				insn_idx, i);
			वापस -EINVAL;
		पूर्ण

		/* Erase all spilled poपूर्णांकers. */
		state->stack[spi].spilled_ptr.type = NOT_INIT;

		/* Update the slot type. */
		new_type = STACK_MISC;
		अगर (writing_zero && *stype == STACK_ZERO) अणु
			new_type = STACK_ZERO;
			zero_used = true;
		पूर्ण
		/* If the slot is STACK_INVALID, we check whether it's OK to
		 * pretend that it will be initialized by this ग_लिखो. The slot
		 * might not actually be written to, and so अगर we mark it as
		 * initialized future पढ़ोs might leak uninitialized memory.
		 * For privileged programs, we will accept such पढ़ोs to slots
		 * that may or may not be written because, अगर we're reject
		 * them, the error would be too confusing.
		 */
		अगर (*stype == STACK_INVALID && !env->allow_uninit_stack) अणु
			verbose(env, "uninit stack in range of var-offset write prohibited for !root; insn %d, off: %d",
					insn_idx, i);
			वापस -EINVAL;
		पूर्ण
		*stype = new_type;
	पूर्ण
	अगर (zero_used) अणु
		/* backtracking करोesn't work क्रम STACK_ZERO yet. */
		err = mark_chain_precision(env, value_regno);
		अगर (err)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

/* When रेजिस्टर 'dst_regno' is asचिन्हित some values from stack[min_off,
 * max_off), we set the रेजिस्टर's type according to the types of the
 * respective stack slots. If all the stack values are known to be zeros, then
 * so is the destination reg. Otherwise, the रेजिस्टर is considered to be
 * SCALAR. This function करोes not deal with रेजिस्टर filling; the caller must
 * ensure that all spilled रेजिस्टरs in the stack range have been marked as
 * पढ़ो.
 */
अटल व्योम mark_reg_stack_पढ़ो(काष्ठा bpf_verअगरier_env *env,
				/* func where src रेजिस्टर poपूर्णांकs to */
				काष्ठा bpf_func_state *ptr_state,
				पूर्णांक min_off, पूर्णांक max_off, पूर्णांक dst_regno)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	पूर्णांक i, slot, spi;
	u8 *stype;
	पूर्णांक zeros = 0;

	क्रम (i = min_off; i < max_off; i++) अणु
		slot = -i - 1;
		spi = slot / BPF_REG_SIZE;
		stype = ptr_state->stack[spi].slot_type;
		अगर (stype[slot % BPF_REG_SIZE] != STACK_ZERO)
			अवरोध;
		zeros++;
	पूर्ण
	अगर (zeros == max_off - min_off) अणु
		/* any access_size पढ़ो पूर्णांकo रेजिस्टर is zero extended,
		 * so the whole रेजिस्टर == स्थिर_zero
		 */
		__mark_reg_स्थिर_zero(&state->regs[dst_regno]);
		/* backtracking करोesn't support STACK_ZERO yet,
		 * so mark it precise here, so that later
		 * backtracking can stop here.
		 * Backtracking may not need this अगर this रेजिस्टर
		 * करोesn't participate in poपूर्णांकer adjusपंचांगent.
		 * Forward propagation of precise flag is not
		 * necessary either. This mark is only to stop
		 * backtracking. Any रेजिस्टर that contributed
		 * to स्थिर 0 was marked precise beक्रमe spill.
		 */
		state->regs[dst_regno].precise = true;
	पूर्ण अन्यथा अणु
		/* have पढ़ो misc data from the stack */
		mark_reg_unknown(env, state->regs, dst_regno);
	पूर्ण
	state->regs[dst_regno].live |= REG_LIVE_WRITTEN;
पूर्ण

/* Read the stack at 'off' and put the results पूर्णांकo the रेजिस्टर indicated by
 * 'dst_regno'. It handles reg filling अगर the addressed stack slot is a
 * spilled reg.
 *
 * 'dst_regno' can be -1, meaning that the पढ़ो value is not going to a
 * रेजिस्टर.
 *
 * The access is assumed to be within the current stack bounds.
 */
अटल पूर्णांक check_stack_पढ़ो_fixed_off(काष्ठा bpf_verअगरier_env *env,
				      /* func where src रेजिस्टर poपूर्णांकs to */
				      काष्ठा bpf_func_state *reg_state,
				      पूर्णांक off, पूर्णांक size, पूर्णांक dst_regno)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	पूर्णांक i, slot = -off - 1, spi = slot / BPF_REG_SIZE;
	काष्ठा bpf_reg_state *reg;
	u8 *stype;

	stype = reg_state->stack[spi].slot_type;
	reg = &reg_state->stack[spi].spilled_ptr;

	अगर (stype[0] == STACK_SPILL) अणु
		अगर (size != BPF_REG_SIZE) अणु
			अगर (reg->type != SCALAR_VALUE) अणु
				verbose_linfo(env, env->insn_idx, "; ");
				verbose(env, "invalid size of register fill\n");
				वापस -EACCES;
			पूर्ण
			अगर (dst_regno >= 0) अणु
				mark_reg_unknown(env, state->regs, dst_regno);
				state->regs[dst_regno].live |= REG_LIVE_WRITTEN;
			पूर्ण
			mark_reg_पढ़ो(env, reg, reg->parent, REG_LIVE_READ64);
			वापस 0;
		पूर्ण
		क्रम (i = 1; i < BPF_REG_SIZE; i++) अणु
			अगर (stype[(slot - i) % BPF_REG_SIZE] != STACK_SPILL) अणु
				verbose(env, "corrupted spill memory\n");
				वापस -EACCES;
			पूर्ण
		पूर्ण

		अगर (dst_regno >= 0) अणु
			/* restore रेजिस्टर state from stack */
			state->regs[dst_regno] = *reg;
			/* mark reg as written since spilled poपूर्णांकer state likely
			 * has its liveness marks cleared by is_state_visited()
			 * which resets stack/reg liveness क्रम state transitions
			 */
			state->regs[dst_regno].live |= REG_LIVE_WRITTEN;
		पूर्ण अन्यथा अगर (__is_poपूर्णांकer_value(env->allow_ptr_leaks, reg)) अणु
			/* If dst_regno==-1, the caller is asking us whether
			 * it is acceptable to use this value as a SCALAR_VALUE
			 * (e.g. क्रम XADD).
			 * We must not allow unprivileged callers to करो that
			 * with spilled poपूर्णांकers.
			 */
			verbose(env, "leaking pointer from stack off %d\n",
				off);
			वापस -EACCES;
		पूर्ण
		mark_reg_पढ़ो(env, reg, reg->parent, REG_LIVE_READ64);
	पूर्ण अन्यथा अणु
		u8 type;

		क्रम (i = 0; i < size; i++) अणु
			type = stype[(slot - i) % BPF_REG_SIZE];
			अगर (type == STACK_MISC)
				जारी;
			अगर (type == STACK_ZERO)
				जारी;
			verbose(env, "invalid read from stack off %d+%d size %d\n",
				off, i, size);
			वापस -EACCES;
		पूर्ण
		mark_reg_पढ़ो(env, reg, reg->parent, REG_LIVE_READ64);
		अगर (dst_regno >= 0)
			mark_reg_stack_पढ़ो(env, reg_state, off, off + size, dst_regno);
	पूर्ण
	वापस 0;
पूर्ण

क्रमागत stack_access_src अणु
	ACCESS_सूचीECT = 1,  /* the access is perक्रमmed by an inकाष्ठाion */
	ACCESS_HELPER = 2,  /* the access is perक्रमmed by a helper */
पूर्ण;

अटल पूर्णांक check_stack_range_initialized(काष्ठा bpf_verअगरier_env *env,
					 पूर्णांक regno, पूर्णांक off, पूर्णांक access_size,
					 bool zero_size_allowed,
					 क्रमागत stack_access_src type,
					 काष्ठा bpf_call_arg_meta *meta);

अटल काष्ठा bpf_reg_state *reg_state(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno)
अणु
	वापस cur_regs(env) + regno;
पूर्ण

/* Read the stack at 'ptr_regno + off' and put the result पूर्णांकo the रेजिस्टर
 * 'dst_regno'.
 * 'off' includes the pointer register's fixed offset(i.e. 'ptr_regno.off'),
 * but not its variable offset.
 * 'size' is assumed to be <= reg size and the access is assumed to be aligned.
 *
 * As opposed to check_stack_पढ़ो_fixed_off, this function करोesn't deal with
 * filling रेजिस्टरs (i.e. पढ़ोs of spilled रेजिस्टर cannot be detected when
 * the offset is not fixed). We conservatively mark 'dst_regno' as containing
 * SCALAR_VALUE. That's why we assert that the 'ptr_regno' has a variable
 * offset; क्रम a fixed offset check_stack_पढ़ो_fixed_off should be used
 * instead.
 */
अटल पूर्णांक check_stack_पढ़ो_var_off(काष्ठा bpf_verअगरier_env *env,
				    पूर्णांक ptr_regno, पूर्णांक off, पूर्णांक size, पूर्णांक dst_regno)
अणु
	/* The state of the source रेजिस्टर. */
	काष्ठा bpf_reg_state *reg = reg_state(env, ptr_regno);
	काष्ठा bpf_func_state *ptr_state = func(env, reg);
	पूर्णांक err;
	पूर्णांक min_off, max_off;

	/* Note that we pass a शून्य meta, so raw access will not be permitted.
	 */
	err = check_stack_range_initialized(env, ptr_regno, off, size,
					    false, ACCESS_सूचीECT, शून्य);
	अगर (err)
		वापस err;

	min_off = reg->smin_value + off;
	max_off = reg->smax_value + off;
	mark_reg_stack_पढ़ो(env, ptr_state, min_off, max_off + size, dst_regno);
	वापस 0;
पूर्ण

/* check_stack_पढ़ो dispatches to check_stack_पढ़ो_fixed_off or
 * check_stack_पढ़ो_var_off.
 *
 * The caller must ensure that the offset falls within the allocated stack
 * bounds.
 *
 * 'dst_regno' is a रेजिस्टर which will receive the value from the stack. It
 * can be -1, meaning that the पढ़ो value is not going to a रेजिस्टर.
 */
अटल पूर्णांक check_stack_पढ़ो(काष्ठा bpf_verअगरier_env *env,
			    पूर्णांक ptr_regno, पूर्णांक off, पूर्णांक size,
			    पूर्णांक dst_regno)
अणु
	काष्ठा bpf_reg_state *reg = reg_state(env, ptr_regno);
	काष्ठा bpf_func_state *state = func(env, reg);
	पूर्णांक err;
	/* Some accesses are only permitted with a अटल offset. */
	bool var_off = !tnum_is_स्थिर(reg->var_off);

	/* The offset is required to be अटल when पढ़ोs करोn't go to a
	 * रेजिस्टर, in order to not leak poपूर्णांकers (see
	 * check_stack_पढ़ो_fixed_off).
	 */
	अगर (dst_regno < 0 && var_off) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env, "variable offset stack pointer cannot be passed into helper function; var_off=%s off=%d size=%d\n",
			tn_buf, off, size);
		वापस -EACCES;
	पूर्ण
	/* Variable offset is prohibited क्रम unprivileged mode क्रम simplicity
	 * since it requires corresponding support in Spectre masking क्रम stack
	 * ALU. See also retrieve_ptr_limit().
	 */
	अगर (!env->bypass_spec_v1 && var_off) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env, "R%d variable offset stack access prohibited for !root, var_off=%s\n",
				ptr_regno, tn_buf);
		वापस -EACCES;
	पूर्ण

	अगर (!var_off) अणु
		off += reg->var_off.value;
		err = check_stack_पढ़ो_fixed_off(env, state, off, size,
						 dst_regno);
	पूर्ण अन्यथा अणु
		/* Variable offset stack पढ़ोs need more conservative handling
		 * than fixed offset ones. Note that dst_regno >= 0 on this
		 * branch.
		 */
		err = check_stack_पढ़ो_var_off(env, ptr_regno, off, size,
					       dst_regno);
	पूर्ण
	वापस err;
पूर्ण


/* check_stack_ग_लिखो dispatches to check_stack_ग_लिखो_fixed_off or
 * check_stack_ग_लिखो_var_off.
 *
 * 'ptr_regno' is the रेजिस्टर used as a poपूर्णांकer पूर्णांकo the stack.
 * 'off' includes 'ptr_regno->off', but not its variable offset (अगर any).
 * 'value_regno' is the register whose value we're writing to the stack. It can
 * be -1, meaning that we're not writing from a रेजिस्टर.
 *
 * The caller must ensure that the offset falls within the maximum stack size.
 */
अटल पूर्णांक check_stack_ग_लिखो(काष्ठा bpf_verअगरier_env *env,
			     पूर्णांक ptr_regno, पूर्णांक off, पूर्णांक size,
			     पूर्णांक value_regno, पूर्णांक insn_idx)
अणु
	काष्ठा bpf_reg_state *reg = reg_state(env, ptr_regno);
	काष्ठा bpf_func_state *state = func(env, reg);
	पूर्णांक err;

	अगर (tnum_is_स्थिर(reg->var_off)) अणु
		off += reg->var_off.value;
		err = check_stack_ग_लिखो_fixed_off(env, state, off, size,
						  value_regno, insn_idx);
	पूर्ण अन्यथा अणु
		/* Variable offset stack पढ़ोs need more conservative handling
		 * than fixed offset ones.
		 */
		err = check_stack_ग_लिखो_var_off(env, state,
						ptr_regno, off, size,
						value_regno, insn_idx);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक check_map_access_type(काष्ठा bpf_verअगरier_env *env, u32 regno,
				 पूर्णांक off, पूर्णांक size, क्रमागत bpf_access_type type)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	काष्ठा bpf_map *map = regs[regno].map_ptr;
	u32 cap = bpf_map_flags_to_cap(map);

	अगर (type == BPF_WRITE && !(cap & BPF_MAP_CAN_WRITE)) अणु
		verbose(env, "write into map forbidden, value_size=%d off=%d size=%d\n",
			map->value_size, off, size);
		वापस -EACCES;
	पूर्ण

	अगर (type == BPF_READ && !(cap & BPF_MAP_CAN_READ)) अणु
		verbose(env, "read from map forbidden, value_size=%d off=%d size=%d\n",
			map->value_size, off, size);
		वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

/* check पढ़ो/ग_लिखो पूर्णांकo memory region (e.g., map value, ringbuf sample, etc) */
अटल पूर्णांक __check_mem_access(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno,
			      पूर्णांक off, पूर्णांक size, u32 mem_size,
			      bool zero_size_allowed)
अणु
	bool size_ok = size > 0 || (size == 0 && zero_size_allowed);
	काष्ठा bpf_reg_state *reg;

	अगर (off >= 0 && size_ok && (u64)off + size <= mem_size)
		वापस 0;

	reg = &cur_regs(env)[regno];
	चयन (reg->type) अणु
	हाल PTR_TO_MAP_KEY:
		verbose(env, "invalid access to map key, key_size=%d off=%d size=%d\n",
			mem_size, off, size);
		अवरोध;
	हाल PTR_TO_MAP_VALUE:
		verbose(env, "invalid access to map value, value_size=%d off=%d size=%d\n",
			mem_size, off, size);
		अवरोध;
	हाल PTR_TO_PACKET:
	हाल PTR_TO_PACKET_META:
	हाल PTR_TO_PACKET_END:
		verbose(env, "invalid access to packet, off=%d size=%d, R%d(id=%d,off=%d,r=%d)\n",
			off, size, regno, reg->id, off, mem_size);
		अवरोध;
	हाल PTR_TO_MEM:
	शेष:
		verbose(env, "invalid access to memory, mem_size=%u off=%d size=%d\n",
			mem_size, off, size);
	पूर्ण

	वापस -EACCES;
पूर्ण

/* check पढ़ो/ग_लिखो पूर्णांकo a memory region with possible variable offset */
अटल पूर्णांक check_mem_region_access(काष्ठा bpf_verअगरier_env *env, u32 regno,
				   पूर्णांक off, पूर्णांक size, u32 mem_size,
				   bool zero_size_allowed)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	काष्ठा bpf_reg_state *reg = &state->regs[regno];
	पूर्णांक err;

	/* We may have adjusted the रेजिस्टर poपूर्णांकing to memory region, so we
	 * need to try adding each of min_value and max_value to off
	 * to make sure our theoretical access will be safe.
	 */
	अगर (env->log.level & BPF_LOG_LEVEL)
		prपूर्णांक_verअगरier_state(env, state);

	/* The minimum value is only important with चिन्हित
	 * comparisons where we can't assume the न्यूनमान of a
	 * value is 0.  If we are using चिन्हित variables क्रम our
	 * index'es we need to make sure that whatever we use
	 * will have a set न्यूनमान within our range.
	 */
	अगर (reg->smin_value < 0 &&
	    (reg->smin_value == S64_MIN ||
	     (off + reg->smin_value != (s64)(s32)(off + reg->smin_value)) ||
	      reg->smin_value + off < 0)) अणु
		verbose(env, "R%d min value is negative, either use unsigned index or do a if (index >=0) check.\n",
			regno);
		वापस -EACCES;
	पूर्ण
	err = __check_mem_access(env, regno, reg->smin_value + off, size,
				 mem_size, zero_size_allowed);
	अगर (err) अणु
		verbose(env, "R%d min value is outside of the allowed memory range\n",
			regno);
		वापस err;
	पूर्ण

	/* If we haven't set a max value then we need to bail since we can't be
	 * sure we won't करो bad things.
	 * If reg->umax_value + off could overflow, treat that as unbounded too.
	 */
	अगर (reg->umax_value >= BPF_MAX_VAR_OFF) अणु
		verbose(env, "R%d unbounded memory access, make sure to bounds check any such access\n",
			regno);
		वापस -EACCES;
	पूर्ण
	err = __check_mem_access(env, regno, reg->umax_value + off, size,
				 mem_size, zero_size_allowed);
	अगर (err) अणु
		verbose(env, "R%d max value is outside of the allowed memory range\n",
			regno);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/* check पढ़ो/ग_लिखो पूर्णांकo a map element with possible variable offset */
अटल पूर्णांक check_map_access(काष्ठा bpf_verअगरier_env *env, u32 regno,
			    पूर्णांक off, पूर्णांक size, bool zero_size_allowed)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	काष्ठा bpf_reg_state *reg = &state->regs[regno];
	काष्ठा bpf_map *map = reg->map_ptr;
	पूर्णांक err;

	err = check_mem_region_access(env, regno, off, size, map->value_size,
				      zero_size_allowed);
	अगर (err)
		वापस err;

	अगर (map_value_has_spin_lock(map)) अणु
		u32 lock = map->spin_lock_off;

		/* अगर any part of काष्ठा bpf_spin_lock can be touched by
		 * load/store reject this program.
		 * To check that [x1, x2) overlaps with [y1, y2)
		 * it is sufficient to check x1 < y2 && y1 < x2.
		 */
		अगर (reg->smin_value + off < lock + माप(काष्ठा bpf_spin_lock) &&
		     lock < reg->umax_value + off + size) अणु
			verbose(env, "bpf_spin_lock cannot be accessed directly by load/store\n");
			वापस -EACCES;
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

#घोषणा MAX_PACKET_OFF 0xffff

अटल क्रमागत bpf_prog_type resolve_prog_type(काष्ठा bpf_prog *prog)
अणु
	वापस prog->aux->dst_prog ? prog->aux->dst_prog->type : prog->type;
पूर्ण

अटल bool may_access_direct_pkt_data(काष्ठा bpf_verअगरier_env *env,
				       स्थिर काष्ठा bpf_call_arg_meta *meta,
				       क्रमागत bpf_access_type t)
अणु
	क्रमागत bpf_prog_type prog_type = resolve_prog_type(env->prog);

	चयन (prog_type) अणु
	/* Program types only with direct पढ़ो access go here! */
	हाल BPF_PROG_TYPE_LWT_IN:
	हाल BPF_PROG_TYPE_LWT_OUT:
	हाल BPF_PROG_TYPE_LWT_SEG6LOCAL:
	हाल BPF_PROG_TYPE_SK_REUSEPORT:
	हाल BPF_PROG_TYPE_FLOW_DISSECTOR:
	हाल BPF_PROG_TYPE_CGROUP_SKB:
		अगर (t == BPF_WRITE)
			वापस false;
		fallthrough;

	/* Program types with direct पढ़ो + ग_लिखो access go here! */
	हाल BPF_PROG_TYPE_SCHED_CLS:
	हाल BPF_PROG_TYPE_SCHED_ACT:
	हाल BPF_PROG_TYPE_XDP:
	हाल BPF_PROG_TYPE_LWT_XMIT:
	हाल BPF_PROG_TYPE_SK_SKB:
	हाल BPF_PROG_TYPE_SK_MSG:
		अगर (meta)
			वापस meta->pkt_access;

		env->seen_direct_ग_लिखो = true;
		वापस true;

	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
		अगर (t == BPF_WRITE)
			env->seen_direct_ग_लिखो = true;

		वापस true;

	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक check_packet_access(काष्ठा bpf_verअगरier_env *env, u32 regno, पूर्णांक off,
			       पूर्णांक size, bool zero_size_allowed)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	काष्ठा bpf_reg_state *reg = &regs[regno];
	पूर्णांक err;

	/* We may have added a variable offset to the packet poपूर्णांकer; but any
	 * reg->range we have comes after that.  We are only checking the fixed
	 * offset.
	 */

	/* We करोn't allow negative numbers, because we aren't tracking enough
	 * detail to prove they're safe.
	 */
	अगर (reg->smin_value < 0) अणु
		verbose(env, "R%d min value is negative, either use unsigned index or do a if (index >=0) check.\n",
			regno);
		वापस -EACCES;
	पूर्ण

	err = reg->range < 0 ? -EINVAL :
	      __check_mem_access(env, regno, off, size, reg->range,
				 zero_size_allowed);
	अगर (err) अणु
		verbose(env, "R%d offset is outside of the packet\n", regno);
		वापस err;
	पूर्ण

	/* __check_mem_access has made sure "off + size - 1" is within u16.
	 * reg->umax_value can't be bigger than MAX_PACKET_OFF which is 0xffff,
	 * otherwise find_good_pkt_poपूर्णांकers would have refused to set range info
	 * that __check_mem_access would have rejected this pkt access.
	 * Thereक्रमe, "off + reg->umax_value + size - 1" won't overflow u32.
	 */
	env->prog->aux->max_pkt_offset =
		max_t(u32, env->prog->aux->max_pkt_offset,
		      off + reg->umax_value + size - 1);

	वापस err;
पूर्ण

/* check access to 'struct bpf_context' fields.  Supports fixed offsets only */
अटल पूर्णांक check_ctx_access(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx, पूर्णांक off, पूर्णांक size,
			    क्रमागत bpf_access_type t, क्रमागत bpf_reg_type *reg_type,
			    काष्ठा btf **btf, u32 *btf_id)
अणु
	काष्ठा bpf_insn_access_aux info = अणु
		.reg_type = *reg_type,
		.log = &env->log,
	पूर्ण;

	अगर (env->ops->is_valid_access &&
	    env->ops->is_valid_access(off, size, t, env->prog, &info)) अणु
		/* A non zero info.ctx_field_size indicates that this field is a
		 * candidate क्रम later verअगरier transक्रमmation to load the whole
		 * field and then apply a mask when accessed with a narrower
		 * access than actual ctx access size. A zero info.ctx_field_size
		 * will only allow क्रम whole field access and rejects any other
		 * type of narrower access.
		 */
		*reg_type = info.reg_type;

		अगर (*reg_type == PTR_TO_BTF_ID || *reg_type == PTR_TO_BTF_ID_OR_शून्य) अणु
			*btf = info.btf;
			*btf_id = info.btf_id;
		पूर्ण अन्यथा अणु
			env->insn_aux_data[insn_idx].ctx_field_size = info.ctx_field_size;
		पूर्ण
		/* remember the offset of last byte accessed in ctx */
		अगर (env->prog->aux->max_ctx_offset < off + size)
			env->prog->aux->max_ctx_offset = off + size;
		वापस 0;
	पूर्ण

	verbose(env, "invalid bpf_context access off=%d size=%d\n", off, size);
	वापस -EACCES;
पूर्ण

अटल पूर्णांक check_flow_keys_access(काष्ठा bpf_verअगरier_env *env, पूर्णांक off,
				  पूर्णांक size)
अणु
	अगर (size < 0 || off < 0 ||
	    (u64)off + size > माप(काष्ठा bpf_flow_keys)) अणु
		verbose(env, "invalid access to flow keys off=%d size=%d\n",
			off, size);
		वापस -EACCES;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_sock_access(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx,
			     u32 regno, पूर्णांक off, पूर्णांक size,
			     क्रमागत bpf_access_type t)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	काष्ठा bpf_reg_state *reg = &regs[regno];
	काष्ठा bpf_insn_access_aux info = अणुपूर्ण;
	bool valid;

	अगर (reg->smin_value < 0) अणु
		verbose(env, "R%d min value is negative, either use unsigned index or do a if (index >=0) check.\n",
			regno);
		वापस -EACCES;
	पूर्ण

	चयन (reg->type) अणु
	हाल PTR_TO_SOCK_COMMON:
		valid = bpf_sock_common_is_valid_access(off, size, t, &info);
		अवरोध;
	हाल PTR_TO_SOCKET:
		valid = bpf_sock_is_valid_access(off, size, t, &info);
		अवरोध;
	हाल PTR_TO_TCP_SOCK:
		valid = bpf_tcp_sock_is_valid_access(off, size, t, &info);
		अवरोध;
	हाल PTR_TO_XDP_SOCK:
		valid = bpf_xdp_sock_is_valid_access(off, size, t, &info);
		अवरोध;
	शेष:
		valid = false;
	पूर्ण


	अगर (valid) अणु
		env->insn_aux_data[insn_idx].ctx_field_size =
			info.ctx_field_size;
		वापस 0;
	पूर्ण

	verbose(env, "R%d invalid %s access off=%d size=%d\n",
		regno, reg_type_str[reg->type], off, size);

	वापस -EACCES;
पूर्ण

अटल bool is_poपूर्णांकer_value(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno)
अणु
	वापस __is_poपूर्णांकer_value(env->allow_ptr_leaks, reg_state(env, regno));
पूर्ण

अटल bool is_ctx_reg(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno)
अणु
	स्थिर काष्ठा bpf_reg_state *reg = reg_state(env, regno);

	वापस reg->type == PTR_TO_CTX;
पूर्ण

अटल bool is_sk_reg(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno)
अणु
	स्थिर काष्ठा bpf_reg_state *reg = reg_state(env, regno);

	वापस type_is_sk_poपूर्णांकer(reg->type);
पूर्ण

अटल bool is_pkt_reg(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno)
अणु
	स्थिर काष्ठा bpf_reg_state *reg = reg_state(env, regno);

	वापस type_is_pkt_poपूर्णांकer(reg->type);
पूर्ण

अटल bool is_flow_key_reg(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno)
अणु
	स्थिर काष्ठा bpf_reg_state *reg = reg_state(env, regno);

	/* Separate to is_ctx_reg() since we still want to allow BPF_ST here. */
	वापस reg->type == PTR_TO_FLOW_KEYS;
पूर्ण

अटल पूर्णांक check_pkt_ptr_alignment(काष्ठा bpf_verअगरier_env *env,
				   स्थिर काष्ठा bpf_reg_state *reg,
				   पूर्णांक off, पूर्णांक size, bool strict)
अणु
	काष्ठा tnum reg_off;
	पूर्णांक ip_align;

	/* Byte size accesses are always allowed. */
	अगर (!strict || size == 1)
		वापस 0;

	/* For platक्रमms that करो not have a Kconfig enabling
	 * CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS the value of
	 * NET_IP_ALIGN is universally set to '2'.  And on platक्रमms
	 * that करो set CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS, we get
	 * to this code only in strict mode where we want to emulate
	 * the NET_IP_ALIGN==2 checking.  Thereक्रमe use an
	 * unconditional IP align value of '2'.
	 */
	ip_align = 2;

	reg_off = tnum_add(reg->var_off, tnum_स्थिर(ip_align + reg->off + off));
	अगर (!tnum_is_aligned(reg_off, size)) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env,
			"misaligned packet access off %d+%s+%d+%d size %d\n",
			ip_align, tn_buf, reg->off, off, size);
		वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_generic_ptr_alignment(काष्ठा bpf_verअगरier_env *env,
				       स्थिर काष्ठा bpf_reg_state *reg,
				       स्थिर अक्षर *poपूर्णांकer_desc,
				       पूर्णांक off, पूर्णांक size, bool strict)
अणु
	काष्ठा tnum reg_off;

	/* Byte size accesses are always allowed. */
	अगर (!strict || size == 1)
		वापस 0;

	reg_off = tnum_add(reg->var_off, tnum_स्थिर(reg->off + off));
	अगर (!tnum_is_aligned(reg_off, size)) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env, "misaligned %saccess off %s+%d+%d size %d\n",
			poपूर्णांकer_desc, tn_buf, reg->off, off, size);
		वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_ptr_alignment(काष्ठा bpf_verअगरier_env *env,
			       स्थिर काष्ठा bpf_reg_state *reg, पूर्णांक off,
			       पूर्णांक size, bool strict_alignment_once)
अणु
	bool strict = env->strict_alignment || strict_alignment_once;
	स्थिर अक्षर *poपूर्णांकer_desc = "";

	चयन (reg->type) अणु
	हाल PTR_TO_PACKET:
	हाल PTR_TO_PACKET_META:
		/* Special हाल, because of NET_IP_ALIGN. Given metadata sits
		 * right in front, treat it the very same way.
		 */
		वापस check_pkt_ptr_alignment(env, reg, off, size, strict);
	हाल PTR_TO_FLOW_KEYS:
		poपूर्णांकer_desc = "flow keys ";
		अवरोध;
	हाल PTR_TO_MAP_KEY:
		poपूर्णांकer_desc = "key ";
		अवरोध;
	हाल PTR_TO_MAP_VALUE:
		poपूर्णांकer_desc = "value ";
		अवरोध;
	हाल PTR_TO_CTX:
		poपूर्णांकer_desc = "context ";
		अवरोध;
	हाल PTR_TO_STACK:
		poपूर्णांकer_desc = "stack ";
		/* The stack spill tracking logic in check_stack_ग_लिखो_fixed_off()
		 * and check_stack_पढ़ो_fixed_off() relies on stack accesses being
		 * aligned.
		 */
		strict = true;
		अवरोध;
	हाल PTR_TO_SOCKET:
		poपूर्णांकer_desc = "sock ";
		अवरोध;
	हाल PTR_TO_SOCK_COMMON:
		poपूर्णांकer_desc = "sock_common ";
		अवरोध;
	हाल PTR_TO_TCP_SOCK:
		poपूर्णांकer_desc = "tcp_sock ";
		अवरोध;
	हाल PTR_TO_XDP_SOCK:
		poपूर्णांकer_desc = "xdp_sock ";
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस check_generic_ptr_alignment(env, reg, poपूर्णांकer_desc, off, size,
					   strict);
पूर्ण

अटल पूर्णांक update_stack_depth(काष्ठा bpf_verअगरier_env *env,
			      स्थिर काष्ठा bpf_func_state *func,
			      पूर्णांक off)
अणु
	u16 stack = env->subprog_info[func->subprogno].stack_depth;

	अगर (stack >= -off)
		वापस 0;

	/* update known max क्रम given subprogram */
	env->subprog_info[func->subprogno].stack_depth = -off;
	वापस 0;
पूर्ण

/* starting from मुख्य bpf function walk all inकाष्ठाions of the function
 * and recursively walk all callees that given function can call.
 * Ignore jump and निकास insns.
 * Since recursion is prevented by check_cfg() this algorithm
 * only needs a local stack of MAX_CALL_FRAMES to remember callsites
 */
अटल पूर्णांक check_max_stack_depth(काष्ठा bpf_verअगरier_env *env)
अणु
	पूर्णांक depth = 0, frame = 0, idx = 0, i = 0, subprog_end;
	काष्ठा bpf_subprog_info *subprog = env->subprog_info;
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	bool tail_call_reachable = false;
	पूर्णांक ret_insn[MAX_CALL_FRAMES];
	पूर्णांक ret_prog[MAX_CALL_FRAMES];
	पूर्णांक j;

process_func:
	/* protect against potential stack overflow that might happen when
	 * bpf2bpf calls get combined with tailcalls. Limit the caller's stack
	 * depth क्रम such हाल करोwn to 256 so that the worst हाल scenario
	 * would result in 8k stack size (32 which is tailcall limit * 256 =
	 * 8k).
	 *
	 * To get the idea what might happen, see an example:
	 * func1 -> sub rsp, 128
	 *  subfunc1 -> sub rsp, 256
	 *  tailcall1 -> add rsp, 256
	 *   func2 -> sub rsp, 192 (total stack size = 128 + 192 = 320)
	 *   subfunc2 -> sub rsp, 64
	 *   subfunc22 -> sub rsp, 128
	 *   tailcall2 -> add rsp, 128
	 *    func3 -> sub rsp, 32 (total stack size 128 + 192 + 64 + 32 = 416)
	 *
	 * tailcall will unwind the current stack frame but it will not get rid
	 * of caller's stack as shown on the example above.
	 */
	अगर (idx && subprog[idx].has_tail_call && depth >= 256) अणु
		verbose(env,
			"tail_calls are not allowed when call stack of previous frames is %d bytes. Too large\n",
			depth);
		वापस -EACCES;
	पूर्ण
	/* round up to 32-bytes, since this is granularity
	 * of पूर्णांकerpreter stack size
	 */
	depth += round_up(max_t(u32, subprog[idx].stack_depth, 1), 32);
	अगर (depth > MAX_BPF_STACK) अणु
		verbose(env, "combined stack size of %d calls is %d. Too large\n",
			frame + 1, depth);
		वापस -EACCES;
	पूर्ण
जारी_func:
	subprog_end = subprog[idx + 1].start;
	क्रम (; i < subprog_end; i++) अणु
		अगर (!bpf_pseuकरो_call(insn + i) && !bpf_pseuकरो_func(insn + i))
			जारी;
		/* remember insn and function to वापस to */
		ret_insn[frame] = i + 1;
		ret_prog[frame] = idx;

		/* find the callee */
		i = i + insn[i].imm + 1;
		idx = find_subprog(env, i);
		अगर (idx < 0) अणु
			WARN_ONCE(1, "verifier bug. No program starts at insn %d\n",
				  i);
			वापस -EFAULT;
		पूर्ण

		अगर (subprog[idx].has_tail_call)
			tail_call_reachable = true;

		frame++;
		अगर (frame >= MAX_CALL_FRAMES) अणु
			verbose(env, "the call stack of %d frames is too deep !\n",
				frame);
			वापस -E2BIG;
		पूर्ण
		जाओ process_func;
	पूर्ण
	/* अगर tail call got detected across bpf2bpf calls then mark each of the
	 * currently present subprog frames as tail call reachable subprogs;
	 * this info will be utilized by JIT so that we will be preserving the
	 * tail call counter throughout bpf2bpf calls combined with tailcalls
	 */
	अगर (tail_call_reachable)
		क्रम (j = 0; j < frame; j++)
			subprog[ret_prog[j]].tail_call_reachable = true;

	/* end of क्रम() loop means the last insn of the 'subprog'
	 * was reached. Doesn't matter whether it was JA or EXIT
	 */
	अगर (frame == 0)
		वापस 0;
	depth -= round_up(max_t(u32, subprog[idx].stack_depth, 1), 32);
	frame--;
	i = ret_insn[frame];
	idx = ret_prog[frame];
	जाओ जारी_func;
पूर्ण

#अगर_अघोषित CONFIG_BPF_JIT_ALWAYS_ON
अटल पूर्णांक get_callee_stack_depth(काष्ठा bpf_verअगरier_env *env,
				  स्थिर काष्ठा bpf_insn *insn, पूर्णांक idx)
अणु
	पूर्णांक start = idx + insn->imm + 1, subprog;

	subprog = find_subprog(env, start);
	अगर (subprog < 0) अणु
		WARN_ONCE(1, "verifier bug. No program starts at insn %d\n",
			  start);
		वापस -EFAULT;
	पूर्ण
	वापस env->subprog_info[subprog].stack_depth;
पूर्ण
#पूर्ण_अगर

पूर्णांक check_ctx_reg(काष्ठा bpf_verअगरier_env *env,
		  स्थिर काष्ठा bpf_reg_state *reg, पूर्णांक regno)
अणु
	/* Access to ctx or passing it to a helper is only allowed in
	 * its original, unmodअगरied क्रमm.
	 */

	अगर (reg->off) अणु
		verbose(env, "dereference of modified ctx ptr R%d off=%d disallowed\n",
			regno, reg->off);
		वापस -EACCES;
	पूर्ण

	अगर (!tnum_is_स्थिर(reg->var_off) || reg->var_off.value) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env, "variable ctx access var_off=%s disallowed\n", tn_buf);
		वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __check_buffer_access(काष्ठा bpf_verअगरier_env *env,
				 स्थिर अक्षर *buf_info,
				 स्थिर काष्ठा bpf_reg_state *reg,
				 पूर्णांक regno, पूर्णांक off, पूर्णांक size)
अणु
	अगर (off < 0) अणु
		verbose(env,
			"R%d invalid %s buffer access: off=%d, size=%d\n",
			regno, buf_info, off, size);
		वापस -EACCES;
	पूर्ण
	अगर (!tnum_is_स्थिर(reg->var_off) || reg->var_off.value) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env,
			"R%d invalid variable buffer offset: off=%d, var_off=%s\n",
			regno, off, tn_buf);
		वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_tp_buffer_access(काष्ठा bpf_verअगरier_env *env,
				  स्थिर काष्ठा bpf_reg_state *reg,
				  पूर्णांक regno, पूर्णांक off, पूर्णांक size)
अणु
	पूर्णांक err;

	err = __check_buffer_access(env, "tracepoint", reg, regno, off, size);
	अगर (err)
		वापस err;

	अगर (off + size > env->prog->aux->max_tp_access)
		env->prog->aux->max_tp_access = off + size;

	वापस 0;
पूर्ण

अटल पूर्णांक check_buffer_access(काष्ठा bpf_verअगरier_env *env,
			       स्थिर काष्ठा bpf_reg_state *reg,
			       पूर्णांक regno, पूर्णांक off, पूर्णांक size,
			       bool zero_size_allowed,
			       स्थिर अक्षर *buf_info,
			       u32 *max_access)
अणु
	पूर्णांक err;

	err = __check_buffer_access(env, buf_info, reg, regno, off, size);
	अगर (err)
		वापस err;

	अगर (off + size > *max_access)
		*max_access = off + size;

	वापस 0;
पूर्ण

/* BPF architecture zero extends alu32 ops पूर्णांकo 64-bit registesr */
अटल व्योम zext_32_to_64(काष्ठा bpf_reg_state *reg)
अणु
	reg->var_off = tnum_subreg(reg->var_off);
	__reg_assign_32_पूर्णांकo_64(reg);
पूर्ण

/* truncate रेजिस्टर to smaller size (in bytes)
 * must be called with size < BPF_REG_SIZE
 */
अटल व्योम coerce_reg_to_size(काष्ठा bpf_reg_state *reg, पूर्णांक size)
अणु
	u64 mask;

	/* clear high bits in bit representation */
	reg->var_off = tnum_cast(reg->var_off, size);

	/* fix arithmetic bounds */
	mask = ((u64)1 << (size * 8)) - 1;
	अगर ((reg->umin_value & ~mask) == (reg->umax_value & ~mask)) अणु
		reg->umin_value &= mask;
		reg->umax_value &= mask;
	पूर्ण अन्यथा अणु
		reg->umin_value = 0;
		reg->umax_value = mask;
	पूर्ण
	reg->smin_value = reg->umin_value;
	reg->smax_value = reg->umax_value;

	/* If size is smaller than 32bit रेजिस्टर the 32bit रेजिस्टर
	 * values are also truncated so we push 64-bit bounds पूर्णांकo
	 * 32-bit bounds. Above were truncated < 32-bits alपढ़ोy.
	 */
	अगर (size >= 4)
		वापस;
	__reg_combine_64_पूर्णांकo_32(reg);
पूर्ण

अटल bool bpf_map_is_rकरोnly(स्थिर काष्ठा bpf_map *map)
अणु
	वापस (map->map_flags & BPF_F_RDONLY_PROG) && map->frozen;
पूर्ण

अटल पूर्णांक bpf_map_direct_पढ़ो(काष्ठा bpf_map *map, पूर्णांक off, पूर्णांक size, u64 *val)
अणु
	व्योम *ptr;
	u64 addr;
	पूर्णांक err;

	err = map->ops->map_direct_value_addr(map, &addr, off);
	अगर (err)
		वापस err;
	ptr = (व्योम *)(दीर्घ)addr + off;

	चयन (size) अणु
	हाल माप(u8):
		*val = (u64)*(u8 *)ptr;
		अवरोध;
	हाल माप(u16):
		*val = (u64)*(u16 *)ptr;
		अवरोध;
	हाल माप(u32):
		*val = (u64)*(u32 *)ptr;
		अवरोध;
	हाल माप(u64):
		*val = *(u64 *)ptr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक check_ptr_to_btf_access(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_reg_state *regs,
				   पूर्णांक regno, पूर्णांक off, पूर्णांक size,
				   क्रमागत bpf_access_type atype,
				   पूर्णांक value_regno)
अणु
	काष्ठा bpf_reg_state *reg = regs + regno;
	स्थिर काष्ठा btf_type *t = btf_type_by_id(reg->btf, reg->btf_id);
	स्थिर अक्षर *tname = btf_name_by_offset(reg->btf, t->name_off);
	u32 btf_id;
	पूर्णांक ret;

	अगर (off < 0) अणु
		verbose(env,
			"R%d is ptr_%s invalid negative access: off=%d\n",
			regno, tname, off);
		वापस -EACCES;
	पूर्ण
	अगर (!tnum_is_स्थिर(reg->var_off) || reg->var_off.value) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env,
			"R%d is ptr_%s invalid variable offset: off=%d, var_off=%s\n",
			regno, tname, off, tn_buf);
		वापस -EACCES;
	पूर्ण

	अगर (env->ops->btf_काष्ठा_access) अणु
		ret = env->ops->btf_काष्ठा_access(&env->log, reg->btf, t,
						  off, size, atype, &btf_id);
	पूर्ण अन्यथा अणु
		अगर (atype != BPF_READ) अणु
			verbose(env, "only read is supported\n");
			वापस -EACCES;
		पूर्ण

		ret = btf_काष्ठा_access(&env->log, reg->btf, t, off, size,
					atype, &btf_id);
	पूर्ण

	अगर (ret < 0)
		वापस ret;

	अगर (atype == BPF_READ && value_regno >= 0)
		mark_btf_ld_reg(env, regs, value_regno, ret, reg->btf, btf_id);

	वापस 0;
पूर्ण

अटल पूर्णांक check_ptr_to_map_access(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_reg_state *regs,
				   पूर्णांक regno, पूर्णांक off, पूर्णांक size,
				   क्रमागत bpf_access_type atype,
				   पूर्णांक value_regno)
अणु
	काष्ठा bpf_reg_state *reg = regs + regno;
	काष्ठा bpf_map *map = reg->map_ptr;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *tname;
	u32 btf_id;
	पूर्णांक ret;

	अगर (!btf_vmlinux) अणु
		verbose(env, "map_ptr access not supported without CONFIG_DEBUG_INFO_BTF\n");
		वापस -ENOTSUPP;
	पूर्ण

	अगर (!map->ops->map_btf_id || !*map->ops->map_btf_id) अणु
		verbose(env, "map_ptr access not supported for map type %d\n",
			map->map_type);
		वापस -ENOTSUPP;
	पूर्ण

	t = btf_type_by_id(btf_vmlinux, *map->ops->map_btf_id);
	tname = btf_name_by_offset(btf_vmlinux, t->name_off);

	अगर (!env->allow_ptr_to_map_access) अणु
		verbose(env,
			"%s access is allowed only to CAP_PERFMON and CAP_SYS_ADMIN\n",
			tname);
		वापस -EPERM;
	पूर्ण

	अगर (off < 0) अणु
		verbose(env, "R%d is %s invalid negative access: off=%d\n",
			regno, tname, off);
		वापस -EACCES;
	पूर्ण

	अगर (atype != BPF_READ) अणु
		verbose(env, "only read from %s is supported\n", tname);
		वापस -EACCES;
	पूर्ण

	ret = btf_काष्ठा_access(&env->log, btf_vmlinux, t, off, size, atype, &btf_id);
	अगर (ret < 0)
		वापस ret;

	अगर (value_regno >= 0)
		mark_btf_ld_reg(env, regs, value_regno, ret, btf_vmlinux, btf_id);

	वापस 0;
पूर्ण

/* Check that the stack access at the given offset is within bounds. The
 * maximum valid offset is -1.
 *
 * The minimum valid offset is -MAX_BPF_STACK क्रम ग_लिखोs, and
 * -state->allocated_stack क्रम पढ़ोs.
 */
अटल पूर्णांक check_stack_slot_within_bounds(पूर्णांक off,
					  काष्ठा bpf_func_state *state,
					  क्रमागत bpf_access_type t)
अणु
	पूर्णांक min_valid_off;

	अगर (t == BPF_WRITE)
		min_valid_off = -MAX_BPF_STACK;
	अन्यथा
		min_valid_off = -state->allocated_stack;

	अगर (off < min_valid_off || off > -1)
		वापस -EACCES;
	वापस 0;
पूर्ण

/* Check that the stack access at 'regno + off' falls within the maximum stack
 * bounds.
 *
 * 'off' includes `regno->offset`, but not its dynamic part (अगर any).
 */
अटल पूर्णांक check_stack_access_within_bounds(
		काष्ठा bpf_verअगरier_env *env,
		पूर्णांक regno, पूर्णांक off, पूर्णांक access_size,
		क्रमागत stack_access_src src, क्रमागत bpf_access_type type)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	काष्ठा bpf_reg_state *reg = regs + regno;
	काष्ठा bpf_func_state *state = func(env, reg);
	पूर्णांक min_off, max_off;
	पूर्णांक err;
	अक्षर *err_extra;

	अगर (src == ACCESS_HELPER)
		/* We करोn't know अगर helpers are पढ़ोing or writing (or both). */
		err_extra = " indirect access to";
	अन्यथा अगर (type == BPF_READ)
		err_extra = " read from";
	अन्यथा
		err_extra = " write to";

	अगर (tnum_is_स्थिर(reg->var_off)) अणु
		min_off = reg->var_off.value + off;
		अगर (access_size > 0)
			max_off = min_off + access_size - 1;
		अन्यथा
			max_off = min_off;
	पूर्ण अन्यथा अणु
		अगर (reg->smax_value >= BPF_MAX_VAR_OFF ||
		    reg->smin_value <= -BPF_MAX_VAR_OFF) अणु
			verbose(env, "invalid unbounded variable-offset%s stack R%d\n",
				err_extra, regno);
			वापस -EACCES;
		पूर्ण
		min_off = reg->smin_value + off;
		अगर (access_size > 0)
			max_off = reg->smax_value + off + access_size - 1;
		अन्यथा
			max_off = min_off;
	पूर्ण

	err = check_stack_slot_within_bounds(min_off, state, type);
	अगर (!err)
		err = check_stack_slot_within_bounds(max_off, state, type);

	अगर (err) अणु
		अगर (tnum_is_स्थिर(reg->var_off)) अणु
			verbose(env, "invalid%s stack R%d off=%d size=%d\n",
				err_extra, regno, off, access_size);
		पूर्ण अन्यथा अणु
			अक्षर tn_buf[48];

			tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
			verbose(env, "invalid variable-offset%s stack R%d var_off=%s size=%d\n",
				err_extra, regno, tn_buf, access_size);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

/* check whether memory at (regno + off) is accessible क्रम t = (पढ़ो | ग_लिखो)
 * अगर t==ग_लिखो, value_regno is a रेजिस्टर which value is stored पूर्णांकo memory
 * अगर t==पढ़ो, value_regno is a रेजिस्टर which will receive the value from memory
 * अगर t==ग_लिखो && value_regno==-1, some unknown value is stored पूर्णांकo memory
 * अगर t==पढ़ो && value_regno==-1, करोn't care what we पढ़ो from memory
 */
अटल पूर्णांक check_mem_access(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx, u32 regno,
			    पूर्णांक off, पूर्णांक bpf_size, क्रमागत bpf_access_type t,
			    पूर्णांक value_regno, bool strict_alignment_once)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	काष्ठा bpf_reg_state *reg = regs + regno;
	काष्ठा bpf_func_state *state;
	पूर्णांक size, err = 0;

	size = bpf_माप_प्रकारo_bytes(bpf_size);
	अगर (size < 0)
		वापस size;

	/* alignment checks will add in reg->off themselves */
	err = check_ptr_alignment(env, reg, off, size, strict_alignment_once);
	अगर (err)
		वापस err;

	/* क्रम access checks, reg->off is just part of off */
	off += reg->off;

	अगर (reg->type == PTR_TO_MAP_KEY) अणु
		अगर (t == BPF_WRITE) अणु
			verbose(env, "write to change key R%d not allowed\n", regno);
			वापस -EACCES;
		पूर्ण

		err = check_mem_region_access(env, regno, off, size,
					      reg->map_ptr->key_size, false);
		अगर (err)
			वापस err;
		अगर (value_regno >= 0)
			mark_reg_unknown(env, regs, value_regno);
	पूर्ण अन्यथा अगर (reg->type == PTR_TO_MAP_VALUE) अणु
		अगर (t == BPF_WRITE && value_regno >= 0 &&
		    is_poपूर्णांकer_value(env, value_regno)) अणु
			verbose(env, "R%d leaks addr into map\n", value_regno);
			वापस -EACCES;
		पूर्ण
		err = check_map_access_type(env, regno, off, size, t);
		अगर (err)
			वापस err;
		err = check_map_access(env, regno, off, size, false);
		अगर (!err && t == BPF_READ && value_regno >= 0) अणु
			काष्ठा bpf_map *map = reg->map_ptr;

			/* अगर map is पढ़ो-only, track its contents as scalars */
			अगर (tnum_is_स्थिर(reg->var_off) &&
			    bpf_map_is_rकरोnly(map) &&
			    map->ops->map_direct_value_addr) अणु
				पूर्णांक map_off = off + reg->var_off.value;
				u64 val = 0;

				err = bpf_map_direct_पढ़ो(map, map_off, size,
							  &val);
				अगर (err)
					वापस err;

				regs[value_regno].type = SCALAR_VALUE;
				__mark_reg_known(&regs[value_regno], val);
			पूर्ण अन्यथा अणु
				mark_reg_unknown(env, regs, value_regno);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (reg->type == PTR_TO_MEM) अणु
		अगर (t == BPF_WRITE && value_regno >= 0 &&
		    is_poपूर्णांकer_value(env, value_regno)) अणु
			verbose(env, "R%d leaks addr into mem\n", value_regno);
			वापस -EACCES;
		पूर्ण
		err = check_mem_region_access(env, regno, off, size,
					      reg->mem_size, false);
		अगर (!err && t == BPF_READ && value_regno >= 0)
			mark_reg_unknown(env, regs, value_regno);
	पूर्ण अन्यथा अगर (reg->type == PTR_TO_CTX) अणु
		क्रमागत bpf_reg_type reg_type = SCALAR_VALUE;
		काष्ठा btf *btf = शून्य;
		u32 btf_id = 0;

		अगर (t == BPF_WRITE && value_regno >= 0 &&
		    is_poपूर्णांकer_value(env, value_regno)) अणु
			verbose(env, "R%d leaks addr into ctx\n", value_regno);
			वापस -EACCES;
		पूर्ण

		err = check_ctx_reg(env, reg, regno);
		अगर (err < 0)
			वापस err;

		err = check_ctx_access(env, insn_idx, off, size, t, &reg_type, &btf, &btf_id);
		अगर (err)
			verbose_linfo(env, insn_idx, "; ");
		अगर (!err && t == BPF_READ && value_regno >= 0) अणु
			/* ctx access वापसs either a scalar, or a
			 * PTR_TO_PACKET[_META,_END]. In the latter
			 * हाल, we know the offset is zero.
			 */
			अगर (reg_type == SCALAR_VALUE) अणु
				mark_reg_unknown(env, regs, value_regno);
			पूर्ण अन्यथा अणु
				mark_reg_known_zero(env, regs,
						    value_regno);
				अगर (reg_type_may_be_null(reg_type))
					regs[value_regno].id = ++env->id_gen;
				/* A load of ctx field could have dअगरferent
				 * actual load size with the one encoded in the
				 * insn. When the dst is PTR, it is क्रम sure not
				 * a sub-रेजिस्टर.
				 */
				regs[value_regno].subreg_def = DEF_NOT_SUBREG;
				अगर (reg_type == PTR_TO_BTF_ID ||
				    reg_type == PTR_TO_BTF_ID_OR_शून्य) अणु
					regs[value_regno].btf = btf;
					regs[value_regno].btf_id = btf_id;
				पूर्ण
			पूर्ण
			regs[value_regno].type = reg_type;
		पूर्ण

	पूर्ण अन्यथा अगर (reg->type == PTR_TO_STACK) अणु
		/* Basic bounds checks. */
		err = check_stack_access_within_bounds(env, regno, off, size, ACCESS_सूचीECT, t);
		अगर (err)
			वापस err;

		state = func(env, reg);
		err = update_stack_depth(env, state, off);
		अगर (err)
			वापस err;

		अगर (t == BPF_READ)
			err = check_stack_पढ़ो(env, regno, off, size,
					       value_regno);
		अन्यथा
			err = check_stack_ग_लिखो(env, regno, off, size,
						value_regno, insn_idx);
	पूर्ण अन्यथा अगर (reg_is_pkt_poपूर्णांकer(reg)) अणु
		अगर (t == BPF_WRITE && !may_access_direct_pkt_data(env, शून्य, t)) अणु
			verbose(env, "cannot write into packet\n");
			वापस -EACCES;
		पूर्ण
		अगर (t == BPF_WRITE && value_regno >= 0 &&
		    is_poपूर्णांकer_value(env, value_regno)) अणु
			verbose(env, "R%d leaks addr into packet\n",
				value_regno);
			वापस -EACCES;
		पूर्ण
		err = check_packet_access(env, regno, off, size, false);
		अगर (!err && t == BPF_READ && value_regno >= 0)
			mark_reg_unknown(env, regs, value_regno);
	पूर्ण अन्यथा अगर (reg->type == PTR_TO_FLOW_KEYS) अणु
		अगर (t == BPF_WRITE && value_regno >= 0 &&
		    is_poपूर्णांकer_value(env, value_regno)) अणु
			verbose(env, "R%d leaks addr into flow keys\n",
				value_regno);
			वापस -EACCES;
		पूर्ण

		err = check_flow_keys_access(env, off, size);
		अगर (!err && t == BPF_READ && value_regno >= 0)
			mark_reg_unknown(env, regs, value_regno);
	पूर्ण अन्यथा अगर (type_is_sk_poपूर्णांकer(reg->type)) अणु
		अगर (t == BPF_WRITE) अणु
			verbose(env, "R%d cannot write into %s\n",
				regno, reg_type_str[reg->type]);
			वापस -EACCES;
		पूर्ण
		err = check_sock_access(env, insn_idx, regno, off, size, t);
		अगर (!err && value_regno >= 0)
			mark_reg_unknown(env, regs, value_regno);
	पूर्ण अन्यथा अगर (reg->type == PTR_TO_TP_BUFFER) अणु
		err = check_tp_buffer_access(env, reg, regno, off, size);
		अगर (!err && t == BPF_READ && value_regno >= 0)
			mark_reg_unknown(env, regs, value_regno);
	पूर्ण अन्यथा अगर (reg->type == PTR_TO_BTF_ID) अणु
		err = check_ptr_to_btf_access(env, regs, regno, off, size, t,
					      value_regno);
	पूर्ण अन्यथा अगर (reg->type == CONST_PTR_TO_MAP) अणु
		err = check_ptr_to_map_access(env, regs, regno, off, size, t,
					      value_regno);
	पूर्ण अन्यथा अगर (reg->type == PTR_TO_RDONLY_BUF) अणु
		अगर (t == BPF_WRITE) अणु
			verbose(env, "R%d cannot write into %s\n",
				regno, reg_type_str[reg->type]);
			वापस -EACCES;
		पूर्ण
		err = check_buffer_access(env, reg, regno, off, size, false,
					  "rdonly",
					  &env->prog->aux->max_rकरोnly_access);
		अगर (!err && value_regno >= 0)
			mark_reg_unknown(env, regs, value_regno);
	पूर्ण अन्यथा अगर (reg->type == PTR_TO_RDWR_BUF) अणु
		err = check_buffer_access(env, reg, regno, off, size, false,
					  "rdwr",
					  &env->prog->aux->max_rdwr_access);
		अगर (!err && t == BPF_READ && value_regno >= 0)
			mark_reg_unknown(env, regs, value_regno);
	पूर्ण अन्यथा अणु
		verbose(env, "R%d invalid mem access '%s'\n", regno,
			reg_type_str[reg->type]);
		वापस -EACCES;
	पूर्ण

	अगर (!err && size < BPF_REG_SIZE && value_regno >= 0 && t == BPF_READ &&
	    regs[value_regno].type == SCALAR_VALUE) अणु
		/* b/h/w load zero-extends, mark upper bits as known 0 */
		coerce_reg_to_size(&regs[value_regno], size);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक check_atomic(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx, काष्ठा bpf_insn *insn)
अणु
	पूर्णांक load_reg;
	पूर्णांक err;

	चयन (insn->imm) अणु
	हाल BPF_ADD:
	हाल BPF_ADD | BPF_FETCH:
	हाल BPF_AND:
	हाल BPF_AND | BPF_FETCH:
	हाल BPF_OR:
	हाल BPF_OR | BPF_FETCH:
	हाल BPF_XOR:
	हाल BPF_XOR | BPF_FETCH:
	हाल BPF_XCHG:
	हाल BPF_CMPXCHG:
		अवरोध;
	शेष:
		verbose(env, "BPF_ATOMIC uses invalid atomic opcode %02x\n", insn->imm);
		वापस -EINVAL;
	पूर्ण

	अगर (BPF_SIZE(insn->code) != BPF_W && BPF_SIZE(insn->code) != BPF_DW) अणु
		verbose(env, "invalid atomic operand size\n");
		वापस -EINVAL;
	पूर्ण

	/* check src1 opeअक्रम */
	err = check_reg_arg(env, insn->src_reg, SRC_OP);
	अगर (err)
		वापस err;

	/* check src2 opeअक्रम */
	err = check_reg_arg(env, insn->dst_reg, SRC_OP);
	अगर (err)
		वापस err;

	अगर (insn->imm == BPF_CMPXCHG) अणु
		/* Check comparison of R0 with memory location */
		err = check_reg_arg(env, BPF_REG_0, SRC_OP);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (is_poपूर्णांकer_value(env, insn->src_reg)) अणु
		verbose(env, "R%d leaks addr into mem\n", insn->src_reg);
		वापस -EACCES;
	पूर्ण

	अगर (is_ctx_reg(env, insn->dst_reg) ||
	    is_pkt_reg(env, insn->dst_reg) ||
	    is_flow_key_reg(env, insn->dst_reg) ||
	    is_sk_reg(env, insn->dst_reg)) अणु
		verbose(env, "BPF_ATOMIC stores into R%d %s is not allowed\n",
			insn->dst_reg,
			reg_type_str[reg_state(env, insn->dst_reg)->type]);
		वापस -EACCES;
	पूर्ण

	अगर (insn->imm & BPF_FETCH) अणु
		अगर (insn->imm == BPF_CMPXCHG)
			load_reg = BPF_REG_0;
		अन्यथा
			load_reg = insn->src_reg;

		/* check and record load of old value */
		err = check_reg_arg(env, load_reg, DST_OP);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		/* This inकाष्ठाion accesses a memory location but करोesn't
		 * actually load it पूर्णांकo a रेजिस्टर.
		 */
		load_reg = -1;
	पूर्ण

	/* check whether we can पढ़ो the memory */
	err = check_mem_access(env, insn_idx, insn->dst_reg, insn->off,
			       BPF_SIZE(insn->code), BPF_READ, load_reg, true);
	अगर (err)
		वापस err;

	/* check whether we can ग_लिखो पूर्णांकo the same memory */
	err = check_mem_access(env, insn_idx, insn->dst_reg, insn->off,
			       BPF_SIZE(insn->code), BPF_WRITE, -1, true);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* When रेजिस्टर 'regno' is used to पढ़ो the stack (either directly or through
 * a helper function) make sure that it's within stack boundary and, depending
 * on the access type, that all elements of the stack are initialized.
 *
 * 'off' includes 'regno->off', but not its dynamic part (अगर any).
 *
 * All रेजिस्टरs that have been spilled on the stack in the slots within the
 * पढ़ो offsets are marked as पढ़ो.
 */
अटल पूर्णांक check_stack_range_initialized(
		काष्ठा bpf_verअगरier_env *env, पूर्णांक regno, पूर्णांक off,
		पूर्णांक access_size, bool zero_size_allowed,
		क्रमागत stack_access_src type, काष्ठा bpf_call_arg_meta *meta)
अणु
	काष्ठा bpf_reg_state *reg = reg_state(env, regno);
	काष्ठा bpf_func_state *state = func(env, reg);
	पूर्णांक err, min_off, max_off, i, j, slot, spi;
	अक्षर *err_extra = type == ACCESS_HELPER ? " indirect" : "";
	क्रमागत bpf_access_type bounds_check_type;
	/* Some accesses can ग_लिखो anything पूर्णांकo the stack, others are
	 * पढ़ो-only.
	 */
	bool clobber = false;

	अगर (access_size == 0 && !zero_size_allowed) अणु
		verbose(env, "invalid zero-sized read\n");
		वापस -EACCES;
	पूर्ण

	अगर (type == ACCESS_HELPER) अणु
		/* The bounds checks क्रम ग_लिखोs are more permissive than क्रम
		 * पढ़ोs. However, अगर raw_mode is not set, we'll करो extra
		 * checks below.
		 */
		bounds_check_type = BPF_WRITE;
		clobber = true;
	पूर्ण अन्यथा अणु
		bounds_check_type = BPF_READ;
	पूर्ण
	err = check_stack_access_within_bounds(env, regno, off, access_size,
					       type, bounds_check_type);
	अगर (err)
		वापस err;


	अगर (tnum_is_स्थिर(reg->var_off)) अणु
		min_off = max_off = reg->var_off.value + off;
	पूर्ण अन्यथा अणु
		/* Variable offset is prohibited क्रम unprivileged mode क्रम
		 * simplicity since it requires corresponding support in
		 * Spectre masking क्रम stack ALU.
		 * See also retrieve_ptr_limit().
		 */
		अगर (!env->bypass_spec_v1) अणु
			अक्षर tn_buf[48];

			tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
			verbose(env, "R%d%s variable offset stack access prohibited for !root, var_off=%s\n",
				regno, err_extra, tn_buf);
			वापस -EACCES;
		पूर्ण
		/* Only initialized buffer on stack is allowed to be accessed
		 * with variable offset. With uninitialized buffer it's hard to
		 * guarantee that whole memory is marked as initialized on
		 * helper वापस since specअगरic bounds are unknown what may
		 * cause uninitialized stack leaking.
		 */
		अगर (meta && meta->raw_mode)
			meta = शून्य;

		min_off = reg->smin_value + off;
		max_off = reg->smax_value + off;
	पूर्ण

	अगर (meta && meta->raw_mode) अणु
		meta->access_size = access_size;
		meta->regno = regno;
		वापस 0;
	पूर्ण

	क्रम (i = min_off; i < max_off + access_size; i++) अणु
		u8 *stype;

		slot = -i - 1;
		spi = slot / BPF_REG_SIZE;
		अगर (state->allocated_stack <= slot)
			जाओ err;
		stype = &state->stack[spi].slot_type[slot % BPF_REG_SIZE];
		अगर (*stype == STACK_MISC)
			जाओ mark;
		अगर (*stype == STACK_ZERO) अणु
			अगर (clobber) अणु
				/* helper can ग_लिखो anything पूर्णांकo the stack */
				*stype = STACK_MISC;
			पूर्ण
			जाओ mark;
		पूर्ण

		अगर (state->stack[spi].slot_type[0] == STACK_SPILL &&
		    state->stack[spi].spilled_ptr.type == PTR_TO_BTF_ID)
			जाओ mark;

		अगर (state->stack[spi].slot_type[0] == STACK_SPILL &&
		    (state->stack[spi].spilled_ptr.type == SCALAR_VALUE ||
		     env->allow_ptr_leaks)) अणु
			अगर (clobber) अणु
				__mark_reg_unknown(env, &state->stack[spi].spilled_ptr);
				क्रम (j = 0; j < BPF_REG_SIZE; j++)
					state->stack[spi].slot_type[j] = STACK_MISC;
			पूर्ण
			जाओ mark;
		पूर्ण

err:
		अगर (tnum_is_स्थिर(reg->var_off)) अणु
			verbose(env, "invalid%s read from stack R%d off %d+%d size %d\n",
				err_extra, regno, min_off, i - min_off, access_size);
		पूर्ण अन्यथा अणु
			अक्षर tn_buf[48];

			tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
			verbose(env, "invalid%s read from stack R%d var_off %s+%d size %d\n",
				err_extra, regno, tn_buf, i - min_off, access_size);
		पूर्ण
		वापस -EACCES;
mark:
		/* पढ़ोing any byte out of 8-byte 'spill_slot' will cause
		 * the whole slot to be marked as 'read'
		 */
		mark_reg_पढ़ो(env, &state->stack[spi].spilled_ptr,
			      state->stack[spi].spilled_ptr.parent,
			      REG_LIVE_READ64);
	पूर्ण
	वापस update_stack_depth(env, state, min_off);
पूर्ण

अटल पूर्णांक check_helper_mem_access(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno,
				   पूर्णांक access_size, bool zero_size_allowed,
				   काष्ठा bpf_call_arg_meta *meta)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env), *reg = &regs[regno];

	चयन (reg->type) अणु
	हाल PTR_TO_PACKET:
	हाल PTR_TO_PACKET_META:
		वापस check_packet_access(env, regno, reg->off, access_size,
					   zero_size_allowed);
	हाल PTR_TO_MAP_KEY:
		वापस check_mem_region_access(env, regno, reg->off, access_size,
					       reg->map_ptr->key_size, false);
	हाल PTR_TO_MAP_VALUE:
		अगर (check_map_access_type(env, regno, reg->off, access_size,
					  meta && meta->raw_mode ? BPF_WRITE :
					  BPF_READ))
			वापस -EACCES;
		वापस check_map_access(env, regno, reg->off, access_size,
					zero_size_allowed);
	हाल PTR_TO_MEM:
		वापस check_mem_region_access(env, regno, reg->off,
					       access_size, reg->mem_size,
					       zero_size_allowed);
	हाल PTR_TO_RDONLY_BUF:
		अगर (meta && meta->raw_mode)
			वापस -EACCES;
		वापस check_buffer_access(env, reg, regno, reg->off,
					   access_size, zero_size_allowed,
					   "rdonly",
					   &env->prog->aux->max_rकरोnly_access);
	हाल PTR_TO_RDWR_BUF:
		वापस check_buffer_access(env, reg, regno, reg->off,
					   access_size, zero_size_allowed,
					   "rdwr",
					   &env->prog->aux->max_rdwr_access);
	हाल PTR_TO_STACK:
		वापस check_stack_range_initialized(
				env,
				regno, reg->off, access_size,
				zero_size_allowed, ACCESS_HELPER, meta);
	शेष: /* scalar_value or invalid ptr */
		/* Allow zero-byte पढ़ो from शून्य, regardless of poपूर्णांकer type */
		अगर (zero_size_allowed && access_size == 0 &&
		    रेजिस्टर_is_null(reg))
			वापस 0;

		verbose(env, "R%d type=%s expected=%s\n", regno,
			reg_type_str[reg->type],
			reg_type_str[PTR_TO_STACK]);
		वापस -EACCES;
	पूर्ण
पूर्ण

पूर्णांक check_mem_reg(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_reg_state *reg,
		   u32 regno, u32 mem_size)
अणु
	अगर (रेजिस्टर_is_null(reg))
		वापस 0;

	अगर (reg_type_may_be_null(reg->type)) अणु
		/* Assuming that the रेजिस्टर contains a value check अगर the memory
		 * access is safe. Temporarily save and restore the रेजिस्टर's state as
		 * the conversion shouldn't be visible to a caller.
		 */
		स्थिर काष्ठा bpf_reg_state saved_reg = *reg;
		पूर्णांक rv;

		mark_ptr_not_null_reg(reg);
		rv = check_helper_mem_access(env, regno, mem_size, true, शून्य);
		*reg = saved_reg;
		वापस rv;
	पूर्ण

	वापस check_helper_mem_access(env, regno, mem_size, true, शून्य);
पूर्ण

/* Implementation details:
 * bpf_map_lookup वापसs PTR_TO_MAP_VALUE_OR_शून्य
 * Two bpf_map_lookups (even with the same key) will have dअगरferent reg->id.
 * For traditional PTR_TO_MAP_VALUE the verअगरier clears reg->id after
 * value_or_null->value transition, since the verअगरier only cares about
 * the range of access to valid map value poपूर्णांकer and करोesn't care about actual
 * address of the map element.
 * For maps with 'struct bpf_spin_lock' inside map value the verअगरier keeps
 * reg->id > 0 after value_or_null->value transition. By करोing so
 * two bpf_map_lookups will be considered two dअगरferent poपूर्णांकers that
 * poपूर्णांक to dअगरferent bpf_spin_locks.
 * The verअगरier allows taking only one bpf_spin_lock at a समय to aव्योम
 * dead-locks.
 * Since only one bpf_spin_lock is allowed the checks are simpler than
 * reg_is_refcounted() logic. The verअगरier needs to remember only
 * one spin_lock instead of array of acquired_refs.
 * cur_state->active_spin_lock remembers which map value element got locked
 * and clears it after bpf_spin_unlock.
 */
अटल पूर्णांक process_spin_lock(काष्ठा bpf_verअगरier_env *env, पूर्णांक regno,
			     bool is_lock)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env), *reg = &regs[regno];
	काष्ठा bpf_verअगरier_state *cur = env->cur_state;
	bool is_स्थिर = tnum_is_स्थिर(reg->var_off);
	काष्ठा bpf_map *map = reg->map_ptr;
	u64 val = reg->var_off.value;

	अगर (!is_स्थिर) अणु
		verbose(env,
			"R%d doesn't have constant offset. bpf_spin_lock has to be at the constant offset\n",
			regno);
		वापस -EINVAL;
	पूर्ण
	अगर (!map->btf) अणु
		verbose(env,
			"map '%s' has to have BTF in order to use bpf_spin_lock\n",
			map->name);
		वापस -EINVAL;
	पूर्ण
	अगर (!map_value_has_spin_lock(map)) अणु
		अगर (map->spin_lock_off == -E2BIG)
			verbose(env,
				"map '%s' has more than one 'struct bpf_spin_lock'\n",
				map->name);
		अन्यथा अगर (map->spin_lock_off == -ENOENT)
			verbose(env,
				"map '%s' doesn't have 'struct bpf_spin_lock'\n",
				map->name);
		अन्यथा
			verbose(env,
				"map '%s' is not a struct type or bpf_spin_lock is mangled\n",
				map->name);
		वापस -EINVAL;
	पूर्ण
	अगर (map->spin_lock_off != val + reg->off) अणु
		verbose(env, "off %lld doesn't point to 'struct bpf_spin_lock'\n",
			val + reg->off);
		वापस -EINVAL;
	पूर्ण
	अगर (is_lock) अणु
		अगर (cur->active_spin_lock) अणु
			verbose(env,
				"Locking two bpf_spin_locks are not allowed\n");
			वापस -EINVAL;
		पूर्ण
		cur->active_spin_lock = reg->id;
	पूर्ण अन्यथा अणु
		अगर (!cur->active_spin_lock) अणु
			verbose(env, "bpf_spin_unlock without taking a lock\n");
			वापस -EINVAL;
		पूर्ण
		अगर (cur->active_spin_lock != reg->id) अणु
			verbose(env, "bpf_spin_unlock of different lock\n");
			वापस -EINVAL;
		पूर्ण
		cur->active_spin_lock = 0;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool arg_type_is_mem_ptr(क्रमागत bpf_arg_type type)
अणु
	वापस type == ARG_PTR_TO_MEM ||
	       type == ARG_PTR_TO_MEM_OR_शून्य ||
	       type == ARG_PTR_TO_UNINIT_MEM;
पूर्ण

अटल bool arg_type_is_mem_size(क्रमागत bpf_arg_type type)
अणु
	वापस type == ARG_CONST_SIZE ||
	       type == ARG_CONST_SIZE_OR_ZERO;
पूर्ण

अटल bool arg_type_is_alloc_size(क्रमागत bpf_arg_type type)
अणु
	वापस type == ARG_CONST_ALLOC_SIZE_OR_ZERO;
पूर्ण

अटल bool arg_type_is_पूर्णांक_ptr(क्रमागत bpf_arg_type type)
अणु
	वापस type == ARG_PTR_TO_INT ||
	       type == ARG_PTR_TO_LONG;
पूर्ण

अटल पूर्णांक पूर्णांक_ptr_type_to_size(क्रमागत bpf_arg_type type)
अणु
	अगर (type == ARG_PTR_TO_INT)
		वापस माप(u32);
	अन्यथा अगर (type == ARG_PTR_TO_LONG)
		वापस माप(u64);

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक resolve_map_arg_type(काष्ठा bpf_verअगरier_env *env,
				 स्थिर काष्ठा bpf_call_arg_meta *meta,
				 क्रमागत bpf_arg_type *arg_type)
अणु
	अगर (!meta->map_ptr) अणु
		/* kernel subप्रणाली misconfigured verअगरier */
		verbose(env, "invalid map_ptr to access map->type\n");
		वापस -EACCES;
	पूर्ण

	चयन (meta->map_ptr->map_type) अणु
	हाल BPF_MAP_TYPE_SOCKMAP:
	हाल BPF_MAP_TYPE_SOCKHASH:
		अगर (*arg_type == ARG_PTR_TO_MAP_VALUE) अणु
			*arg_type = ARG_PTR_TO_BTF_ID_SOCK_COMMON;
		पूर्ण अन्यथा अणु
			verbose(env, "invalid arg_type for sockmap/sockhash\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

काष्ठा bpf_reg_types अणु
	स्थिर क्रमागत bpf_reg_type types[10];
	u32 *btf_id;
पूर्ण;

अटल स्थिर काष्ठा bpf_reg_types map_key_value_types = अणु
	.types = अणु
		PTR_TO_STACK,
		PTR_TO_PACKET,
		PTR_TO_PACKET_META,
		PTR_TO_MAP_KEY,
		PTR_TO_MAP_VALUE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bpf_reg_types sock_types = अणु
	.types = अणु
		PTR_TO_SOCK_COMMON,
		PTR_TO_SOCKET,
		PTR_TO_TCP_SOCK,
		PTR_TO_XDP_SOCK,
	पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_NET
अटल स्थिर काष्ठा bpf_reg_types btf_id_sock_common_types = अणु
	.types = अणु
		PTR_TO_SOCK_COMMON,
		PTR_TO_SOCKET,
		PTR_TO_TCP_SOCK,
		PTR_TO_XDP_SOCK,
		PTR_TO_BTF_ID,
	पूर्ण,
	.btf_id = &btf_sock_ids[BTF_SOCK_TYPE_SOCK_COMMON],
पूर्ण;
#पूर्ण_अगर

अटल स्थिर काष्ठा bpf_reg_types mem_types = अणु
	.types = अणु
		PTR_TO_STACK,
		PTR_TO_PACKET,
		PTR_TO_PACKET_META,
		PTR_TO_MAP_KEY,
		PTR_TO_MAP_VALUE,
		PTR_TO_MEM,
		PTR_TO_RDONLY_BUF,
		PTR_TO_RDWR_BUF,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bpf_reg_types पूर्णांक_ptr_types = अणु
	.types = अणु
		PTR_TO_STACK,
		PTR_TO_PACKET,
		PTR_TO_PACKET_META,
		PTR_TO_MAP_KEY,
		PTR_TO_MAP_VALUE,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा bpf_reg_types fullsock_types = अणु .types = अणु PTR_TO_SOCKET पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types scalar_types = अणु .types = अणु SCALAR_VALUE पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types context_types = अणु .types = अणु PTR_TO_CTX पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types alloc_mem_types = अणु .types = अणु PTR_TO_MEM पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types स्थिर_map_ptr_types = अणु .types = अणु CONST_PTR_TO_MAP पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types btf_ptr_types = अणु .types = अणु PTR_TO_BTF_ID पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types spin_lock_types = अणु .types = अणु PTR_TO_MAP_VALUE पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types percpu_btf_ptr_types = अणु .types = अणु PTR_TO_PERCPU_BTF_ID पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types func_ptr_types = अणु .types = अणु PTR_TO_FUNC पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types stack_ptr_types = अणु .types = अणु PTR_TO_STACK पूर्ण पूर्ण;
अटल स्थिर काष्ठा bpf_reg_types स्थिर_str_ptr_types = अणु .types = अणु PTR_TO_MAP_VALUE पूर्ण पूर्ण;

अटल स्थिर काष्ठा bpf_reg_types *compatible_reg_types[__BPF_ARG_TYPE_MAX] = अणु
	[ARG_PTR_TO_MAP_KEY]		= &map_key_value_types,
	[ARG_PTR_TO_MAP_VALUE]		= &map_key_value_types,
	[ARG_PTR_TO_UNINIT_MAP_VALUE]	= &map_key_value_types,
	[ARG_PTR_TO_MAP_VALUE_OR_शून्य]	= &map_key_value_types,
	[ARG_CONST_SIZE]		= &scalar_types,
	[ARG_CONST_SIZE_OR_ZERO]	= &scalar_types,
	[ARG_CONST_ALLOC_SIZE_OR_ZERO]	= &scalar_types,
	[ARG_CONST_MAP_PTR]		= &स्थिर_map_ptr_types,
	[ARG_PTR_TO_CTX]		= &context_types,
	[ARG_PTR_TO_CTX_OR_शून्य]	= &context_types,
	[ARG_PTR_TO_SOCK_COMMON]	= &sock_types,
#अगर_घोषित CONFIG_NET
	[ARG_PTR_TO_BTF_ID_SOCK_COMMON]	= &btf_id_sock_common_types,
#पूर्ण_अगर
	[ARG_PTR_TO_SOCKET]		= &fullsock_types,
	[ARG_PTR_TO_SOCKET_OR_शून्य]	= &fullsock_types,
	[ARG_PTR_TO_BTF_ID]		= &btf_ptr_types,
	[ARG_PTR_TO_SPIN_LOCK]		= &spin_lock_types,
	[ARG_PTR_TO_MEM]		= &mem_types,
	[ARG_PTR_TO_MEM_OR_शून्य]	= &mem_types,
	[ARG_PTR_TO_UNINIT_MEM]		= &mem_types,
	[ARG_PTR_TO_ALLOC_MEM]		= &alloc_mem_types,
	[ARG_PTR_TO_ALLOC_MEM_OR_शून्य]	= &alloc_mem_types,
	[ARG_PTR_TO_INT]		= &पूर्णांक_ptr_types,
	[ARG_PTR_TO_LONG]		= &पूर्णांक_ptr_types,
	[ARG_PTR_TO_PERCPU_BTF_ID]	= &percpu_btf_ptr_types,
	[ARG_PTR_TO_FUNC]		= &func_ptr_types,
	[ARG_PTR_TO_STACK_OR_शून्य]	= &stack_ptr_types,
	[ARG_PTR_TO_CONST_STR]		= &स्थिर_str_ptr_types,
पूर्ण;

अटल पूर्णांक check_reg_type(काष्ठा bpf_verअगरier_env *env, u32 regno,
			  क्रमागत bpf_arg_type arg_type,
			  स्थिर u32 *arg_btf_id)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env), *reg = &regs[regno];
	क्रमागत bpf_reg_type expected, type = reg->type;
	स्थिर काष्ठा bpf_reg_types *compatible;
	पूर्णांक i, j;

	compatible = compatible_reg_types[arg_type];
	अगर (!compatible) अणु
		verbose(env, "verifier internal error: unsupported arg type %d\n", arg_type);
		वापस -EFAULT;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(compatible->types); i++) अणु
		expected = compatible->types[i];
		अगर (expected == NOT_INIT)
			अवरोध;

		अगर (type == expected)
			जाओ found;
	पूर्ण

	verbose(env, "R%d type=%s expected=", regno, reg_type_str[type]);
	क्रम (j = 0; j + 1 < i; j++)
		verbose(env, "%s, ", reg_type_str[compatible->types[j]]);
	verbose(env, "%s\n", reg_type_str[compatible->types[j]]);
	वापस -EACCES;

found:
	अगर (type == PTR_TO_BTF_ID) अणु
		अगर (!arg_btf_id) अणु
			अगर (!compatible->btf_id) अणु
				verbose(env, "verifier internal error: missing arg compatible BTF ID\n");
				वापस -EFAULT;
			पूर्ण
			arg_btf_id = compatible->btf_id;
		पूर्ण

		अगर (!btf_काष्ठा_ids_match(&env->log, reg->btf, reg->btf_id, reg->off,
					  btf_vmlinux, *arg_btf_id)) अणु
			verbose(env, "R%d is of type %s but %s is expected\n",
				regno, kernel_type_name(reg->btf, reg->btf_id),
				kernel_type_name(btf_vmlinux, *arg_btf_id));
			वापस -EACCES;
		पूर्ण

		अगर (!tnum_is_स्थिर(reg->var_off) || reg->var_off.value) अणु
			verbose(env, "R%d is a pointer to in-kernel struct with non-zero offset\n",
				regno);
			वापस -EACCES;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक check_func_arg(काष्ठा bpf_verअगरier_env *env, u32 arg,
			  काष्ठा bpf_call_arg_meta *meta,
			  स्थिर काष्ठा bpf_func_proto *fn)
अणु
	u32 regno = BPF_REG_1 + arg;
	काष्ठा bpf_reg_state *regs = cur_regs(env), *reg = &regs[regno];
	क्रमागत bpf_arg_type arg_type = fn->arg_type[arg];
	क्रमागत bpf_reg_type type = reg->type;
	पूर्णांक err = 0;

	अगर (arg_type == ARG_DONTCARE)
		वापस 0;

	err = check_reg_arg(env, regno, SRC_OP);
	अगर (err)
		वापस err;

	अगर (arg_type == ARG_ANYTHING) अणु
		अगर (is_poपूर्णांकer_value(env, regno)) अणु
			verbose(env, "R%d leaks addr into helper function\n",
				regno);
			वापस -EACCES;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (type_is_pkt_poपूर्णांकer(type) &&
	    !may_access_direct_pkt_data(env, meta, BPF_READ)) अणु
		verbose(env, "helper access to the packet is not allowed\n");
		वापस -EACCES;
	पूर्ण

	अगर (arg_type == ARG_PTR_TO_MAP_VALUE ||
	    arg_type == ARG_PTR_TO_UNINIT_MAP_VALUE ||
	    arg_type == ARG_PTR_TO_MAP_VALUE_OR_शून्य) अणु
		err = resolve_map_arg_type(env, meta, &arg_type);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (रेजिस्टर_is_null(reg) && arg_type_may_be_null(arg_type))
		/* A शून्य रेजिस्टर has a SCALAR_VALUE type, so skip
		 * type checking.
		 */
		जाओ skip_type_check;

	err = check_reg_type(env, regno, arg_type, fn->arg_btf_id[arg]);
	अगर (err)
		वापस err;

	अगर (type == PTR_TO_CTX) अणु
		err = check_ctx_reg(env, reg, regno);
		अगर (err < 0)
			वापस err;
	पूर्ण

skip_type_check:
	अगर (reg->ref_obj_id) अणु
		अगर (meta->ref_obj_id) अणु
			verbose(env, "verifier internal error: more than one arg with ref_obj_id R%d %u %u\n",
				regno, reg->ref_obj_id,
				meta->ref_obj_id);
			वापस -EFAULT;
		पूर्ण
		meta->ref_obj_id = reg->ref_obj_id;
	पूर्ण

	अगर (arg_type == ARG_CONST_MAP_PTR) अणु
		/* bpf_map_xxx(map_ptr) call: remember that map_ptr */
		meta->map_ptr = reg->map_ptr;
	पूर्ण अन्यथा अगर (arg_type == ARG_PTR_TO_MAP_KEY) अणु
		/* bpf_map_xxx(..., map_ptr, ..., key) call:
		 * check that [key, key + map->key_size) are within
		 * stack limits and initialized
		 */
		अगर (!meta->map_ptr) अणु
			/* in function declaration map_ptr must come beक्रमe
			 * map_key, so that it's verअगरied and known beक्रमe
			 * we have to check map_key here. Otherwise it means
			 * that kernel subप्रणाली misconfigured verअगरier
			 */
			verbose(env, "invalid map_ptr to access map->key\n");
			वापस -EACCES;
		पूर्ण
		err = check_helper_mem_access(env, regno,
					      meta->map_ptr->key_size, false,
					      शून्य);
	पूर्ण अन्यथा अगर (arg_type == ARG_PTR_TO_MAP_VALUE ||
		   (arg_type == ARG_PTR_TO_MAP_VALUE_OR_शून्य &&
		    !रेजिस्टर_is_null(reg)) ||
		   arg_type == ARG_PTR_TO_UNINIT_MAP_VALUE) अणु
		/* bpf_map_xxx(..., map_ptr, ..., value) call:
		 * check [value, value + map->value_size) validity
		 */
		अगर (!meta->map_ptr) अणु
			/* kernel subप्रणाली misconfigured verअगरier */
			verbose(env, "invalid map_ptr to access map->value\n");
			वापस -EACCES;
		पूर्ण
		meta->raw_mode = (arg_type == ARG_PTR_TO_UNINIT_MAP_VALUE);
		err = check_helper_mem_access(env, regno,
					      meta->map_ptr->value_size, false,
					      meta);
	पूर्ण अन्यथा अगर (arg_type == ARG_PTR_TO_PERCPU_BTF_ID) अणु
		अगर (!reg->btf_id) अणु
			verbose(env, "Helper has invalid btf_id in R%d\n", regno);
			वापस -EACCES;
		पूर्ण
		meta->ret_btf = reg->btf;
		meta->ret_btf_id = reg->btf_id;
	पूर्ण अन्यथा अगर (arg_type == ARG_PTR_TO_SPIN_LOCK) अणु
		अगर (meta->func_id == BPF_FUNC_spin_lock) अणु
			अगर (process_spin_lock(env, regno, true))
				वापस -EACCES;
		पूर्ण अन्यथा अगर (meta->func_id == BPF_FUNC_spin_unlock) अणु
			अगर (process_spin_lock(env, regno, false))
				वापस -EACCES;
		पूर्ण अन्यथा अणु
			verbose(env, "verifier internal error\n");
			वापस -EFAULT;
		पूर्ण
	पूर्ण अन्यथा अगर (arg_type == ARG_PTR_TO_FUNC) अणु
		meta->subprogno = reg->subprogno;
	पूर्ण अन्यथा अगर (arg_type_is_mem_ptr(arg_type)) अणु
		/* The access to this poपूर्णांकer is only checked when we hit the
		 * next is_mem_size argument below.
		 */
		meta->raw_mode = (arg_type == ARG_PTR_TO_UNINIT_MEM);
	पूर्ण अन्यथा अगर (arg_type_is_mem_size(arg_type)) अणु
		bool zero_size_allowed = (arg_type == ARG_CONST_SIZE_OR_ZERO);

		/* This is used to refine r0 वापस value bounds क्रम helpers
		 * that enक्रमce this value as an upper bound on वापस values.
		 * See करो_refine_retval_range() क्रम helpers that can refine
		 * the वापस value. C type of helper is u32 so we pull रेजिस्टर
		 * bound from umax_value however, अगर negative verअगरier errors
		 * out. Only upper bounds can be learned because retval is an
		 * पूर्णांक type and negative retvals are allowed.
		 */
		meta->msize_max_value = reg->umax_value;

		/* The रेजिस्टर is SCALAR_VALUE; the access check
		 * happens using its boundaries.
		 */
		अगर (!tnum_is_स्थिर(reg->var_off))
			/* For unprivileged variable accesses, disable raw
			 * mode so that the program is required to
			 * initialize all the memory that the helper could
			 * just partially fill up.
			 */
			meta = शून्य;

		अगर (reg->smin_value < 0) अणु
			verbose(env, "R%d min value is negative, either use unsigned or 'var &= const'\n",
				regno);
			वापस -EACCES;
		पूर्ण

		अगर (reg->umin_value == 0) अणु
			err = check_helper_mem_access(env, regno - 1, 0,
						      zero_size_allowed,
						      meta);
			अगर (err)
				वापस err;
		पूर्ण

		अगर (reg->umax_value >= BPF_MAX_VAR_SIZ) अणु
			verbose(env, "R%d unbounded memory access, use 'var &= const' or 'if (var < const)'\n",
				regno);
			वापस -EACCES;
		पूर्ण
		err = check_helper_mem_access(env, regno - 1,
					      reg->umax_value,
					      zero_size_allowed, meta);
		अगर (!err)
			err = mark_chain_precision(env, regno);
	पूर्ण अन्यथा अगर (arg_type_is_alloc_size(arg_type)) अणु
		अगर (!tnum_is_स्थिर(reg->var_off)) अणु
			verbose(env, "R%d is not a known constant'\n",
				regno);
			वापस -EACCES;
		पूर्ण
		meta->mem_size = reg->var_off.value;
	पूर्ण अन्यथा अगर (arg_type_is_पूर्णांक_ptr(arg_type)) अणु
		पूर्णांक size = पूर्णांक_ptr_type_to_size(arg_type);

		err = check_helper_mem_access(env, regno, size, false, meta);
		अगर (err)
			वापस err;
		err = check_ptr_alignment(env, reg, 0, size, true);
	पूर्ण अन्यथा अगर (arg_type == ARG_PTR_TO_CONST_STR) अणु
		काष्ठा bpf_map *map = reg->map_ptr;
		पूर्णांक map_off;
		u64 map_addr;
		अक्षर *str_ptr;

		अगर (!bpf_map_is_rकरोnly(map)) अणु
			verbose(env, "R%d does not point to a readonly map'\n", regno);
			वापस -EACCES;
		पूर्ण

		अगर (!tnum_is_स्थिर(reg->var_off)) अणु
			verbose(env, "R%d is not a constant address'\n", regno);
			वापस -EACCES;
		पूर्ण

		अगर (!map->ops->map_direct_value_addr) अणु
			verbose(env, "no direct value access support for this map type\n");
			वापस -EACCES;
		पूर्ण

		err = check_map_access(env, regno, reg->off,
				       map->value_size - reg->off, false);
		अगर (err)
			वापस err;

		map_off = reg->off + reg->var_off.value;
		err = map->ops->map_direct_value_addr(map, &map_addr, map_off);
		अगर (err) अणु
			verbose(env, "direct value access on string failed\n");
			वापस err;
		पूर्ण

		str_ptr = (अक्षर *)(दीर्घ)(map_addr);
		अगर (!strnchr(str_ptr + map_off, map->value_size - map_off, 0)) अणु
			verbose(env, "string is not zero-terminated\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल bool may_update_sockmap(काष्ठा bpf_verअगरier_env *env, पूर्णांक func_id)
अणु
	क्रमागत bpf_attach_type eatype = env->prog->expected_attach_type;
	क्रमागत bpf_prog_type type = resolve_prog_type(env->prog);

	अगर (func_id != BPF_FUNC_map_update_elem)
		वापस false;

	/* It's not possible to get access to a locked काष्ठा sock in these
	 * contexts, so updating is safe.
	 */
	चयन (type) अणु
	हाल BPF_PROG_TYPE_TRACING:
		अगर (eatype == BPF_TRACE_ITER)
			वापस true;
		अवरोध;
	हाल BPF_PROG_TYPE_SOCKET_FILTER:
	हाल BPF_PROG_TYPE_SCHED_CLS:
	हाल BPF_PROG_TYPE_SCHED_ACT:
	हाल BPF_PROG_TYPE_XDP:
	हाल BPF_PROG_TYPE_SK_REUSEPORT:
	हाल BPF_PROG_TYPE_FLOW_DISSECTOR:
	हाल BPF_PROG_TYPE_SK_LOOKUP:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	verbose(env, "cannot update sockmap in this context\n");
	वापस false;
पूर्ण

अटल bool allow_tail_call_in_subprogs(काष्ठा bpf_verअगरier_env *env)
अणु
	वापस env->prog->jit_requested && IS_ENABLED(CONFIG_X86_64);
पूर्ण

अटल पूर्णांक check_map_func_compatibility(काष्ठा bpf_verअगरier_env *env,
					काष्ठा bpf_map *map, पूर्णांक func_id)
अणु
	अगर (!map)
		वापस 0;

	/* We need a two way check, first is from map perspective ... */
	चयन (map->map_type) अणु
	हाल BPF_MAP_TYPE_PROG_ARRAY:
		अगर (func_id != BPF_FUNC_tail_call)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_PERF_EVENT_ARRAY:
		अगर (func_id != BPF_FUNC_perf_event_पढ़ो &&
		    func_id != BPF_FUNC_perf_event_output &&
		    func_id != BPF_FUNC_skb_output &&
		    func_id != BPF_FUNC_perf_event_पढ़ो_value &&
		    func_id != BPF_FUNC_xdp_output)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_RINGBUF:
		अगर (func_id != BPF_FUNC_ringbuf_output &&
		    func_id != BPF_FUNC_ringbuf_reserve &&
		    func_id != BPF_FUNC_ringbuf_submit &&
		    func_id != BPF_FUNC_ringbuf_discard &&
		    func_id != BPF_FUNC_ringbuf_query)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_STACK_TRACE:
		अगर (func_id != BPF_FUNC_get_stackid)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_CGROUP_ARRAY:
		अगर (func_id != BPF_FUNC_skb_under_cgroup &&
		    func_id != BPF_FUNC_current_task_under_cgroup)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_CGROUP_STORAGE:
	हाल BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE:
		अगर (func_id != BPF_FUNC_get_local_storage)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_DEVMAP:
	हाल BPF_MAP_TYPE_DEVMAP_HASH:
		अगर (func_id != BPF_FUNC_redirect_map &&
		    func_id != BPF_FUNC_map_lookup_elem)
			जाओ error;
		अवरोध;
	/* Restrict bpf side of cpumap and xskmap, खोलो when use-हालs
	 * appear.
	 */
	हाल BPF_MAP_TYPE_CPUMAP:
		अगर (func_id != BPF_FUNC_redirect_map)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_XSKMAP:
		अगर (func_id != BPF_FUNC_redirect_map &&
		    func_id != BPF_FUNC_map_lookup_elem)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_ARRAY_OF_MAPS:
	हाल BPF_MAP_TYPE_HASH_OF_MAPS:
		अगर (func_id != BPF_FUNC_map_lookup_elem)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_SOCKMAP:
		अगर (func_id != BPF_FUNC_sk_redirect_map &&
		    func_id != BPF_FUNC_sock_map_update &&
		    func_id != BPF_FUNC_map_delete_elem &&
		    func_id != BPF_FUNC_msg_redirect_map &&
		    func_id != BPF_FUNC_sk_select_reuseport &&
		    func_id != BPF_FUNC_map_lookup_elem &&
		    !may_update_sockmap(env, func_id))
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_SOCKHASH:
		अगर (func_id != BPF_FUNC_sk_redirect_hash &&
		    func_id != BPF_FUNC_sock_hash_update &&
		    func_id != BPF_FUNC_map_delete_elem &&
		    func_id != BPF_FUNC_msg_redirect_hash &&
		    func_id != BPF_FUNC_sk_select_reuseport &&
		    func_id != BPF_FUNC_map_lookup_elem &&
		    !may_update_sockmap(env, func_id))
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_REUSEPORT_SOCKARRAY:
		अगर (func_id != BPF_FUNC_sk_select_reuseport)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_QUEUE:
	हाल BPF_MAP_TYPE_STACK:
		अगर (func_id != BPF_FUNC_map_peek_elem &&
		    func_id != BPF_FUNC_map_pop_elem &&
		    func_id != BPF_FUNC_map_push_elem)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_SK_STORAGE:
		अगर (func_id != BPF_FUNC_sk_storage_get &&
		    func_id != BPF_FUNC_sk_storage_delete)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_INODE_STORAGE:
		अगर (func_id != BPF_FUNC_inode_storage_get &&
		    func_id != BPF_FUNC_inode_storage_delete)
			जाओ error;
		अवरोध;
	हाल BPF_MAP_TYPE_TASK_STORAGE:
		अगर (func_id != BPF_FUNC_task_storage_get &&
		    func_id != BPF_FUNC_task_storage_delete)
			जाओ error;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/* ... and second from the function itself. */
	चयन (func_id) अणु
	हाल BPF_FUNC_tail_call:
		अगर (map->map_type != BPF_MAP_TYPE_PROG_ARRAY)
			जाओ error;
		अगर (env->subprog_cnt > 1 && !allow_tail_call_in_subprogs(env)) अणु
			verbose(env, "tail_calls are not allowed in non-JITed programs with bpf-to-bpf calls\n");
			वापस -EINVAL;
		पूर्ण
		अवरोध;
	हाल BPF_FUNC_perf_event_पढ़ो:
	हाल BPF_FUNC_perf_event_output:
	हाल BPF_FUNC_perf_event_पढ़ो_value:
	हाल BPF_FUNC_skb_output:
	हाल BPF_FUNC_xdp_output:
		अगर (map->map_type != BPF_MAP_TYPE_PERF_EVENT_ARRAY)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_get_stackid:
		अगर (map->map_type != BPF_MAP_TYPE_STACK_TRACE)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_current_task_under_cgroup:
	हाल BPF_FUNC_skb_under_cgroup:
		अगर (map->map_type != BPF_MAP_TYPE_CGROUP_ARRAY)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_redirect_map:
		अगर (map->map_type != BPF_MAP_TYPE_DEVMAP &&
		    map->map_type != BPF_MAP_TYPE_DEVMAP_HASH &&
		    map->map_type != BPF_MAP_TYPE_CPUMAP &&
		    map->map_type != BPF_MAP_TYPE_XSKMAP)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_sk_redirect_map:
	हाल BPF_FUNC_msg_redirect_map:
	हाल BPF_FUNC_sock_map_update:
		अगर (map->map_type != BPF_MAP_TYPE_SOCKMAP)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_sk_redirect_hash:
	हाल BPF_FUNC_msg_redirect_hash:
	हाल BPF_FUNC_sock_hash_update:
		अगर (map->map_type != BPF_MAP_TYPE_SOCKHASH)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_get_local_storage:
		अगर (map->map_type != BPF_MAP_TYPE_CGROUP_STORAGE &&
		    map->map_type != BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_sk_select_reuseport:
		अगर (map->map_type != BPF_MAP_TYPE_REUSEPORT_SOCKARRAY &&
		    map->map_type != BPF_MAP_TYPE_SOCKMAP &&
		    map->map_type != BPF_MAP_TYPE_SOCKHASH)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_map_peek_elem:
	हाल BPF_FUNC_map_pop_elem:
	हाल BPF_FUNC_map_push_elem:
		अगर (map->map_type != BPF_MAP_TYPE_QUEUE &&
		    map->map_type != BPF_MAP_TYPE_STACK)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_sk_storage_get:
	हाल BPF_FUNC_sk_storage_delete:
		अगर (map->map_type != BPF_MAP_TYPE_SK_STORAGE)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_inode_storage_get:
	हाल BPF_FUNC_inode_storage_delete:
		अगर (map->map_type != BPF_MAP_TYPE_INODE_STORAGE)
			जाओ error;
		अवरोध;
	हाल BPF_FUNC_task_storage_get:
	हाल BPF_FUNC_task_storage_delete:
		अगर (map->map_type != BPF_MAP_TYPE_TASK_STORAGE)
			जाओ error;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
error:
	verbose(env, "cannot pass map_type %d into func %s#%d\n",
		map->map_type, func_id_name(func_id), func_id);
	वापस -EINVAL;
पूर्ण

अटल bool check_raw_mode_ok(स्थिर काष्ठा bpf_func_proto *fn)
अणु
	पूर्णांक count = 0;

	अगर (fn->arg1_type == ARG_PTR_TO_UNINIT_MEM)
		count++;
	अगर (fn->arg2_type == ARG_PTR_TO_UNINIT_MEM)
		count++;
	अगर (fn->arg3_type == ARG_PTR_TO_UNINIT_MEM)
		count++;
	अगर (fn->arg4_type == ARG_PTR_TO_UNINIT_MEM)
		count++;
	अगर (fn->arg5_type == ARG_PTR_TO_UNINIT_MEM)
		count++;

	/* We only support one arg being in raw mode at the moment,
	 * which is sufficient क्रम the helper functions we have
	 * right now.
	 */
	वापस count <= 1;
पूर्ण

अटल bool check_args_pair_invalid(क्रमागत bpf_arg_type arg_curr,
				    क्रमागत bpf_arg_type arg_next)
अणु
	वापस (arg_type_is_mem_ptr(arg_curr) &&
	        !arg_type_is_mem_size(arg_next)) ||
	       (!arg_type_is_mem_ptr(arg_curr) &&
		arg_type_is_mem_size(arg_next));
पूर्ण

अटल bool check_arg_pair_ok(स्थिर काष्ठा bpf_func_proto *fn)
अणु
	/* bpf_xxx(..., buf, len) call will access 'len'
	 * bytes from memory 'buf'. Both arg types need
	 * to be paired, so make sure there's no buggy
	 * helper function specअगरication.
	 */
	अगर (arg_type_is_mem_size(fn->arg1_type) ||
	    arg_type_is_mem_ptr(fn->arg5_type)  ||
	    check_args_pair_invalid(fn->arg1_type, fn->arg2_type) ||
	    check_args_pair_invalid(fn->arg2_type, fn->arg3_type) ||
	    check_args_pair_invalid(fn->arg3_type, fn->arg4_type) ||
	    check_args_pair_invalid(fn->arg4_type, fn->arg5_type))
		वापस false;

	वापस true;
पूर्ण

अटल bool check_refcount_ok(स्थिर काष्ठा bpf_func_proto *fn, पूर्णांक func_id)
अणु
	पूर्णांक count = 0;

	अगर (arg_type_may_be_refcounted(fn->arg1_type))
		count++;
	अगर (arg_type_may_be_refcounted(fn->arg2_type))
		count++;
	अगर (arg_type_may_be_refcounted(fn->arg3_type))
		count++;
	अगर (arg_type_may_be_refcounted(fn->arg4_type))
		count++;
	अगर (arg_type_may_be_refcounted(fn->arg5_type))
		count++;

	/* A reference acquiring function cannot acquire
	 * another refcounted ptr.
	 */
	अगर (may_be_acquire_function(func_id) && count)
		वापस false;

	/* We only support one arg being unreferenced at the moment,
	 * which is sufficient क्रम the helper functions we have right now.
	 */
	वापस count <= 1;
पूर्ण

अटल bool check_btf_id_ok(स्थिर काष्ठा bpf_func_proto *fn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(fn->arg_type); i++) अणु
		अगर (fn->arg_type[i] == ARG_PTR_TO_BTF_ID && !fn->arg_btf_id[i])
			वापस false;

		अगर (fn->arg_type[i] != ARG_PTR_TO_BTF_ID && fn->arg_btf_id[i])
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक check_func_proto(स्थिर काष्ठा bpf_func_proto *fn, पूर्णांक func_id)
अणु
	वापस check_raw_mode_ok(fn) &&
	       check_arg_pair_ok(fn) &&
	       check_btf_id_ok(fn) &&
	       check_refcount_ok(fn, func_id) ? 0 : -EINVAL;
पूर्ण

/* Packet data might have moved, any old PTR_TO_PACKET[_META,_END]
 * are now invalid, so turn them पूर्णांकo unknown SCALAR_VALUE.
 */
अटल व्योम __clear_all_pkt_poपूर्णांकers(काष्ठा bpf_verअगरier_env *env,
				     काष्ठा bpf_func_state *state)
अणु
	काष्ठा bpf_reg_state *regs = state->regs, *reg;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BPF_REG; i++)
		अगर (reg_is_pkt_poपूर्णांकer_any(&regs[i]))
			mark_reg_unknown(env, regs, i);

	bpf_क्रम_each_spilled_reg(i, state, reg) अणु
		अगर (!reg)
			जारी;
		अगर (reg_is_pkt_poपूर्णांकer_any(reg))
			__mark_reg_unknown(env, reg);
	पूर्ण
पूर्ण

अटल व्योम clear_all_pkt_poपूर्णांकers(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	पूर्णांक i;

	क्रम (i = 0; i <= vstate->curframe; i++)
		__clear_all_pkt_poपूर्णांकers(env, vstate->frame[i]);
पूर्ण

क्रमागत अणु
	AT_PKT_END = -1,
	BEYOND_PKT_END = -2,
पूर्ण;

अटल व्योम mark_pkt_end(काष्ठा bpf_verअगरier_state *vstate, पूर्णांक regn, bool range_खोलो)
अणु
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	काष्ठा bpf_reg_state *reg = &state->regs[regn];

	अगर (reg->type != PTR_TO_PACKET)
		/* PTR_TO_PACKET_META is not supported yet */
		वापस;

	/* The 'reg' is pkt > pkt_end or pkt >= pkt_end.
	 * How far beyond pkt_end it goes is unknown.
	 * अगर (!range_खोलो) it's the हाल of pkt >= pkt_end
	 * अगर (range_खोलो) it's the हाल of pkt > pkt_end
	 * hence this poपूर्णांकer is at least 1 byte bigger than pkt_end
	 */
	अगर (range_खोलो)
		reg->range = BEYOND_PKT_END;
	अन्यथा
		reg->range = AT_PKT_END;
पूर्ण

अटल व्योम release_reg_references(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_func_state *state,
				   पूर्णांक ref_obj_id)
अणु
	काष्ठा bpf_reg_state *regs = state->regs, *reg;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BPF_REG; i++)
		अगर (regs[i].ref_obj_id == ref_obj_id)
			mark_reg_unknown(env, regs, i);

	bpf_क्रम_each_spilled_reg(i, state, reg) अणु
		अगर (!reg)
			जारी;
		अगर (reg->ref_obj_id == ref_obj_id)
			__mark_reg_unknown(env, reg);
	पूर्ण
पूर्ण

/* The poपूर्णांकer with the specअगरied id has released its reference to kernel
 * resources. Identअगरy all copies of the same poपूर्णांकer and clear the reference.
 */
अटल पूर्णांक release_reference(काष्ठा bpf_verअगरier_env *env,
			     पूर्णांक ref_obj_id)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	पूर्णांक err;
	पूर्णांक i;

	err = release_reference_state(cur_func(env), ref_obj_id);
	अगर (err)
		वापस err;

	क्रम (i = 0; i <= vstate->curframe; i++)
		release_reg_references(env, vstate->frame[i], ref_obj_id);

	वापस 0;
पूर्ण

अटल व्योम clear_caller_saved_regs(काष्ठा bpf_verअगरier_env *env,
				    काष्ठा bpf_reg_state *regs)
अणु
	पूर्णांक i;

	/* after the call रेजिस्टरs r0 - r5 were scratched */
	क्रम (i = 0; i < CALLER_SAVED_REGS; i++) अणु
		mark_reg_not_init(env, regs, caller_saved[i]);
		check_reg_arg(env, caller_saved[i], DST_OP_NO_MARK);
	पूर्ण
पूर्ण

प्रकार पूर्णांक (*set_callee_state_fn)(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_func_state *caller,
				   काष्ठा bpf_func_state *callee,
				   पूर्णांक insn_idx);

अटल पूर्णांक __check_func_call(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn,
			     पूर्णांक *insn_idx, पूर्णांक subprog,
			     set_callee_state_fn set_callee_state_cb)
अणु
	काष्ठा bpf_verअगरier_state *state = env->cur_state;
	काष्ठा bpf_func_info_aux *func_info_aux;
	काष्ठा bpf_func_state *caller, *callee;
	पूर्णांक err;
	bool is_global = false;

	अगर (state->curframe + 1 >= MAX_CALL_FRAMES) अणु
		verbose(env, "the call stack of %d frames is too deep\n",
			state->curframe + 2);
		वापस -E2BIG;
	पूर्ण

	caller = state->frame[state->curframe];
	अगर (state->frame[state->curframe + 1]) अणु
		verbose(env, "verifier bug. Frame %d already allocated\n",
			state->curframe + 1);
		वापस -EFAULT;
	पूर्ण

	func_info_aux = env->prog->aux->func_info_aux;
	अगर (func_info_aux)
		is_global = func_info_aux[subprog].linkage == BTF_FUNC_GLOBAL;
	err = btf_check_subprog_arg_match(env, subprog, caller->regs);
	अगर (err == -EFAULT)
		वापस err;
	अगर (is_global) अणु
		अगर (err) अणु
			verbose(env, "Caller passes invalid args into func#%d\n",
				subprog);
			वापस err;
		पूर्ण अन्यथा अणु
			अगर (env->log.level & BPF_LOG_LEVEL)
				verbose(env,
					"Func#%d is global and valid. Skipping.\n",
					subprog);
			clear_caller_saved_regs(env, caller->regs);

			/* All global functions वापस a 64-bit SCALAR_VALUE */
			mark_reg_unknown(env, caller->regs, BPF_REG_0);
			caller->regs[BPF_REG_0].subreg_def = DEF_NOT_SUBREG;

			/* जारी with next insn after call */
			वापस 0;
		पूर्ण
	पूर्ण

	callee = kzalloc(माप(*callee), GFP_KERNEL);
	अगर (!callee)
		वापस -ENOMEM;
	state->frame[state->curframe + 1] = callee;

	/* callee cannot access r0, r6 - r9 क्रम पढ़ोing and has to ग_लिखो
	 * पूर्णांकo its own stack beक्रमe पढ़ोing from it.
	 * callee can पढ़ो/ग_लिखो पूर्णांकo caller's stack
	 */
	init_func_state(env, callee,
			/* remember the callsite, it will be used by bpf_निकास */
			*insn_idx /* callsite */,
			state->curframe + 1 /* frameno within this callchain */,
			subprog /* subprog number within this prog */);

	/* Transfer references to the callee */
	err = transfer_reference_state(callee, caller);
	अगर (err)
		वापस err;

	err = set_callee_state_cb(env, caller, callee, *insn_idx);
	अगर (err)
		वापस err;

	clear_caller_saved_regs(env, caller->regs);

	/* only increment it after check_reg_arg() finished */
	state->curframe++;

	/* and go analyze first insn of the callee */
	*insn_idx = env->subprog_info[subprog].start - 1;

	अगर (env->log.level & BPF_LOG_LEVEL) अणु
		verbose(env, "caller:\n");
		prपूर्णांक_verअगरier_state(env, caller);
		verbose(env, "callee:\n");
		prपूर्णांक_verअगरier_state(env, callee);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक map_set_क्रम_each_callback_args(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_func_state *caller,
				   काष्ठा bpf_func_state *callee)
अणु
	/* bpf_क्रम_each_map_elem(काष्ठा bpf_map *map, व्योम *callback_fn,
	 *      व्योम *callback_ctx, u64 flags);
	 * callback_fn(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
	 *      व्योम *callback_ctx);
	 */
	callee->regs[BPF_REG_1] = caller->regs[BPF_REG_1];

	callee->regs[BPF_REG_2].type = PTR_TO_MAP_KEY;
	__mark_reg_known_zero(&callee->regs[BPF_REG_2]);
	callee->regs[BPF_REG_2].map_ptr = caller->regs[BPF_REG_1].map_ptr;

	callee->regs[BPF_REG_3].type = PTR_TO_MAP_VALUE;
	__mark_reg_known_zero(&callee->regs[BPF_REG_3]);
	callee->regs[BPF_REG_3].map_ptr = caller->regs[BPF_REG_1].map_ptr;

	/* poपूर्णांकer to stack or null */
	callee->regs[BPF_REG_4] = caller->regs[BPF_REG_3];

	/* unused */
	__mark_reg_not_init(env, &callee->regs[BPF_REG_5]);
	वापस 0;
पूर्ण

अटल पूर्णांक set_callee_state(काष्ठा bpf_verअगरier_env *env,
			    काष्ठा bpf_func_state *caller,
			    काष्ठा bpf_func_state *callee, पूर्णांक insn_idx)
अणु
	पूर्णांक i;

	/* copy r1 - r5 args that callee can access.  The copy includes parent
	 * poपूर्णांकers, which connects us up to the liveness chain
	 */
	क्रम (i = BPF_REG_1; i <= BPF_REG_5; i++)
		callee->regs[i] = caller->regs[i];
	वापस 0;
पूर्ण

अटल पूर्णांक check_func_call(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn,
			   पूर्णांक *insn_idx)
अणु
	पूर्णांक subprog, target_insn;

	target_insn = *insn_idx + insn->imm + 1;
	subprog = find_subprog(env, target_insn);
	अगर (subprog < 0) अणु
		verbose(env, "verifier bug. No program starts at insn %d\n",
			target_insn);
		वापस -EFAULT;
	पूर्ण

	वापस __check_func_call(env, insn, insn_idx, subprog, set_callee_state);
पूर्ण

अटल पूर्णांक set_map_elem_callback_state(काष्ठा bpf_verअगरier_env *env,
				       काष्ठा bpf_func_state *caller,
				       काष्ठा bpf_func_state *callee,
				       पूर्णांक insn_idx)
अणु
	काष्ठा bpf_insn_aux_data *insn_aux = &env->insn_aux_data[insn_idx];
	काष्ठा bpf_map *map;
	पूर्णांक err;

	अगर (bpf_map_ptr_poisoned(insn_aux)) अणु
		verbose(env, "tail_call abusing map_ptr\n");
		वापस -EINVAL;
	पूर्ण

	map = BPF_MAP_PTR(insn_aux->map_ptr_state);
	अगर (!map->ops->map_set_क्रम_each_callback_args ||
	    !map->ops->map_क्रम_each_callback) अणु
		verbose(env, "callback function not allowed for map\n");
		वापस -ENOTSUPP;
	पूर्ण

	err = map->ops->map_set_क्रम_each_callback_args(env, caller, callee);
	अगर (err)
		वापस err;

	callee->in_callback_fn = true;
	वापस 0;
पूर्ण

अटल पूर्णांक prepare_func_निकास(काष्ठा bpf_verअगरier_env *env, पूर्णांक *insn_idx)
अणु
	काष्ठा bpf_verअगरier_state *state = env->cur_state;
	काष्ठा bpf_func_state *caller, *callee;
	काष्ठा bpf_reg_state *r0;
	पूर्णांक err;

	callee = state->frame[state->curframe];
	r0 = &callee->regs[BPF_REG_0];
	अगर (r0->type == PTR_TO_STACK) अणु
		/* technically it's ok to return caller's stack poपूर्णांकer
		 * (or caller's caller's poपूर्णांकer) back to the caller,
		 * since these poपूर्णांकers are valid. Only current stack
		 * poपूर्णांकer will be invalid as soon as function निकासs,
		 * but let's be conservative
		 */
		verbose(env, "cannot return stack pointer to the caller\n");
		वापस -EINVAL;
	पूर्ण

	state->curframe--;
	caller = state->frame[state->curframe];
	अगर (callee->in_callback_fn) अणु
		/* enक्रमce R0 वापस value range [0, 1]. */
		काष्ठा tnum range = tnum_range(0, 1);

		अगर (r0->type != SCALAR_VALUE) अणु
			verbose(env, "R0 not a scalar value\n");
			वापस -EACCES;
		पूर्ण
		अगर (!tnum_in(range, r0->var_off)) अणु
			verbose_invalid_scalar(env, r0, &range, "callback return", "R0");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* वापस to the caller whatever r0 had in the callee */
		caller->regs[BPF_REG_0] = *r0;
	पूर्ण

	/* Transfer references to the caller */
	err = transfer_reference_state(caller, callee);
	अगर (err)
		वापस err;

	*insn_idx = callee->callsite + 1;
	अगर (env->log.level & BPF_LOG_LEVEL) अणु
		verbose(env, "returning from callee:\n");
		prपूर्णांक_verअगरier_state(env, callee);
		verbose(env, "to caller at %d:\n", *insn_idx);
		prपूर्णांक_verअगरier_state(env, caller);
	पूर्ण
	/* clear everything in the callee */
	मुक्त_func_state(callee);
	state->frame[state->curframe + 1] = शून्य;
	वापस 0;
पूर्ण

अटल व्योम करो_refine_retval_range(काष्ठा bpf_reg_state *regs, पूर्णांक ret_type,
				   पूर्णांक func_id,
				   काष्ठा bpf_call_arg_meta *meta)
अणु
	काष्ठा bpf_reg_state *ret_reg = &regs[BPF_REG_0];

	अगर (ret_type != RET_INTEGER ||
	    (func_id != BPF_FUNC_get_stack &&
	     func_id != BPF_FUNC_get_task_stack &&
	     func_id != BPF_FUNC_probe_पढ़ो_str &&
	     func_id != BPF_FUNC_probe_पढ़ो_kernel_str &&
	     func_id != BPF_FUNC_probe_पढ़ो_user_str))
		वापस;

	ret_reg->smax_value = meta->msize_max_value;
	ret_reg->s32_max_value = meta->msize_max_value;
	ret_reg->smin_value = -MAX_ERRNO;
	ret_reg->s32_min_value = -MAX_ERRNO;
	__reg_deduce_bounds(ret_reg);
	__reg_bound_offset(ret_reg);
	__update_reg_bounds(ret_reg);
पूर्ण

अटल पूर्णांक
record_func_map(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_call_arg_meta *meta,
		पूर्णांक func_id, पूर्णांक insn_idx)
अणु
	काष्ठा bpf_insn_aux_data *aux = &env->insn_aux_data[insn_idx];
	काष्ठा bpf_map *map = meta->map_ptr;

	अगर (func_id != BPF_FUNC_tail_call &&
	    func_id != BPF_FUNC_map_lookup_elem &&
	    func_id != BPF_FUNC_map_update_elem &&
	    func_id != BPF_FUNC_map_delete_elem &&
	    func_id != BPF_FUNC_map_push_elem &&
	    func_id != BPF_FUNC_map_pop_elem &&
	    func_id != BPF_FUNC_map_peek_elem &&
	    func_id != BPF_FUNC_क्रम_each_map_elem &&
	    func_id != BPF_FUNC_redirect_map)
		वापस 0;

	अगर (map == शून्य) अणु
		verbose(env, "kernel subsystem misconfigured verifier\n");
		वापस -EINVAL;
	पूर्ण

	/* In हाल of पढ़ो-only, some additional restrictions
	 * need to be applied in order to prevent altering the
	 * state of the map from program side.
	 */
	अगर ((map->map_flags & BPF_F_RDONLY_PROG) &&
	    (func_id == BPF_FUNC_map_delete_elem ||
	     func_id == BPF_FUNC_map_update_elem ||
	     func_id == BPF_FUNC_map_push_elem ||
	     func_id == BPF_FUNC_map_pop_elem)) अणु
		verbose(env, "write into map forbidden\n");
		वापस -EACCES;
	पूर्ण

	अगर (!BPF_MAP_PTR(aux->map_ptr_state))
		bpf_map_ptr_store(aux, meta->map_ptr,
				  !meta->map_ptr->bypass_spec_v1);
	अन्यथा अगर (BPF_MAP_PTR(aux->map_ptr_state) != meta->map_ptr)
		bpf_map_ptr_store(aux, BPF_MAP_PTR_POISON,
				  !meta->map_ptr->bypass_spec_v1);
	वापस 0;
पूर्ण

अटल पूर्णांक
record_func_key(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_call_arg_meta *meta,
		पूर्णांक func_id, पूर्णांक insn_idx)
अणु
	काष्ठा bpf_insn_aux_data *aux = &env->insn_aux_data[insn_idx];
	काष्ठा bpf_reg_state *regs = cur_regs(env), *reg;
	काष्ठा bpf_map *map = meta->map_ptr;
	काष्ठा tnum range;
	u64 val;
	पूर्णांक err;

	अगर (func_id != BPF_FUNC_tail_call)
		वापस 0;
	अगर (!map || map->map_type != BPF_MAP_TYPE_PROG_ARRAY) अणु
		verbose(env, "kernel subsystem misconfigured verifier\n");
		वापस -EINVAL;
	पूर्ण

	range = tnum_range(0, map->max_entries - 1);
	reg = &regs[BPF_REG_3];

	अगर (!रेजिस्टर_is_स्थिर(reg) || !tnum_in(range, reg->var_off)) अणु
		bpf_map_key_store(aux, BPF_MAP_KEY_POISON);
		वापस 0;
	पूर्ण

	err = mark_chain_precision(env, BPF_REG_3);
	अगर (err)
		वापस err;

	val = reg->var_off.value;
	अगर (bpf_map_key_unseen(aux))
		bpf_map_key_store(aux, val);
	अन्यथा अगर (!bpf_map_key_poisoned(aux) &&
		  bpf_map_key_immediate(aux) != val)
		bpf_map_key_store(aux, BPF_MAP_KEY_POISON);
	वापस 0;
पूर्ण

अटल पूर्णांक check_reference_leak(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_func_state *state = cur_func(env);
	पूर्णांक i;

	क्रम (i = 0; i < state->acquired_refs; i++) अणु
		verbose(env, "Unreleased reference id=%d alloc_insn=%d\n",
			state->refs[i].id, state->refs[i].insn_idx);
	पूर्ण
	वापस state->acquired_refs ? -EINVAL : 0;
पूर्ण

अटल पूर्णांक check_bpf_snम_लिखो_call(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_reg_state *regs)
अणु
	काष्ठा bpf_reg_state *fmt_reg = &regs[BPF_REG_3];
	काष्ठा bpf_reg_state *data_len_reg = &regs[BPF_REG_5];
	काष्ठा bpf_map *fmt_map = fmt_reg->map_ptr;
	पूर्णांक err, fmt_map_off, num_args;
	u64 fmt_addr;
	अक्षर *fmt;

	/* data must be an array of u64 */
	अगर (data_len_reg->var_off.value % 8)
		वापस -EINVAL;
	num_args = data_len_reg->var_off.value / 8;

	/* fmt being ARG_PTR_TO_CONST_STR guarantees that var_off is स्थिर
	 * and map_direct_value_addr is set.
	 */
	fmt_map_off = fmt_reg->off + fmt_reg->var_off.value;
	err = fmt_map->ops->map_direct_value_addr(fmt_map, &fmt_addr,
						  fmt_map_off);
	अगर (err) अणु
		verbose(env, "verifier bug\n");
		वापस -EFAULT;
	पूर्ण
	fmt = (अक्षर *)(दीर्घ)fmt_addr + fmt_map_off;

	/* We are also guaranteed that fmt+fmt_map_off is शून्य terminated, we
	 * can focus on validating the क्रमmat specअगरiers.
	 */
	err = bpf_bम_लिखो_prepare(fmt, अच_पूर्णांक_उच्च, शून्य, शून्य, num_args);
	अगर (err < 0)
		verbose(env, "Invalid format string\n");

	वापस err;
पूर्ण

अटल पूर्णांक check_helper_call(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn,
			     पूर्णांक *insn_idx_p)
अणु
	स्थिर काष्ठा bpf_func_proto *fn = शून्य;
	काष्ठा bpf_reg_state *regs;
	काष्ठा bpf_call_arg_meta meta;
	पूर्णांक insn_idx = *insn_idx_p;
	bool changes_data;
	पूर्णांक i, err, func_id;

	/* find function prototype */
	func_id = insn->imm;
	अगर (func_id < 0 || func_id >= __BPF_FUNC_MAX_ID) अणु
		verbose(env, "invalid func %s#%d\n", func_id_name(func_id),
			func_id);
		वापस -EINVAL;
	पूर्ण

	अगर (env->ops->get_func_proto)
		fn = env->ops->get_func_proto(func_id, env->prog);
	अगर (!fn) अणु
		verbose(env, "unknown func %s#%d\n", func_id_name(func_id),
			func_id);
		वापस -EINVAL;
	पूर्ण

	/* eBPF programs must be GPL compatible to use GPL-ed functions */
	अगर (!env->prog->gpl_compatible && fn->gpl_only) अणु
		verbose(env, "cannot call GPL-restricted function from non-GPL compatible program\n");
		वापस -EINVAL;
	पूर्ण

	अगर (fn->allowed && !fn->allowed(env->prog)) अणु
		verbose(env, "helper call is not allowed in probe\n");
		वापस -EINVAL;
	पूर्ण

	/* With LD_ABS/IND some JITs save/restore skb from r1. */
	changes_data = bpf_helper_changes_pkt_data(fn->func);
	अगर (changes_data && fn->arg1_type != ARG_PTR_TO_CTX) अणु
		verbose(env, "kernel subsystem misconfigured func %s#%d: r1 != ctx\n",
			func_id_name(func_id), func_id);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&meta, 0, माप(meta));
	meta.pkt_access = fn->pkt_access;

	err = check_func_proto(fn, func_id);
	अगर (err) अणु
		verbose(env, "kernel subsystem misconfigured func %s#%d\n",
			func_id_name(func_id), func_id);
		वापस err;
	पूर्ण

	meta.func_id = func_id;
	/* check args */
	क्रम (i = 0; i < MAX_BPF_FUNC_REG_ARGS; i++) अणु
		err = check_func_arg(env, i, &meta, fn);
		अगर (err)
			वापस err;
	पूर्ण

	err = record_func_map(env, &meta, func_id, insn_idx);
	अगर (err)
		वापस err;

	err = record_func_key(env, &meta, func_id, insn_idx);
	अगर (err)
		वापस err;

	/* Mark slots with STACK_MISC in हाल of raw mode, stack offset
	 * is inferred from रेजिस्टर state.
	 */
	क्रम (i = 0; i < meta.access_size; i++) अणु
		err = check_mem_access(env, insn_idx, meta.regno, i, BPF_B,
				       BPF_WRITE, -1, false);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (func_id == BPF_FUNC_tail_call) अणु
		err = check_reference_leak(env);
		अगर (err) अणु
			verbose(env, "tail_call would lead to reference leak\n");
			वापस err;
		पूर्ण
	पूर्ण अन्यथा अगर (is_release_function(func_id)) अणु
		err = release_reference(env, meta.ref_obj_id);
		अगर (err) अणु
			verbose(env, "func %s#%d reference has not been acquired before\n",
				func_id_name(func_id), func_id);
			वापस err;
		पूर्ण
	पूर्ण

	regs = cur_regs(env);

	/* check that flags argument in get_local_storage(map, flags) is 0,
	 * this is required because get_local_storage() can't वापस an error.
	 */
	अगर (func_id == BPF_FUNC_get_local_storage &&
	    !रेजिस्टर_is_null(&regs[BPF_REG_2])) अणु
		verbose(env, "get_local_storage() doesn't support non-zero flags\n");
		वापस -EINVAL;
	पूर्ण

	अगर (func_id == BPF_FUNC_क्रम_each_map_elem) अणु
		err = __check_func_call(env, insn, insn_idx_p, meta.subprogno,
					set_map_elem_callback_state);
		अगर (err < 0)
			वापस -EINVAL;
	पूर्ण

	अगर (func_id == BPF_FUNC_snम_लिखो) अणु
		err = check_bpf_snम_लिखो_call(env, regs);
		अगर (err < 0)
			वापस err;
	पूर्ण

	/* reset caller saved regs */
	क्रम (i = 0; i < CALLER_SAVED_REGS; i++) अणु
		mark_reg_not_init(env, regs, caller_saved[i]);
		check_reg_arg(env, caller_saved[i], DST_OP_NO_MARK);
	पूर्ण

	/* helper call वापसs 64-bit value. */
	regs[BPF_REG_0].subreg_def = DEF_NOT_SUBREG;

	/* update वापस रेजिस्टर (alपढ़ोy marked as written above) */
	अगर (fn->ret_type == RET_INTEGER) अणु
		/* sets type to SCALAR_VALUE */
		mark_reg_unknown(env, regs, BPF_REG_0);
	पूर्ण अन्यथा अगर (fn->ret_type == RET_VOID) अणु
		regs[BPF_REG_0].type = NOT_INIT;
	पूर्ण अन्यथा अगर (fn->ret_type == RET_PTR_TO_MAP_VALUE_OR_शून्य ||
		   fn->ret_type == RET_PTR_TO_MAP_VALUE) अणु
		/* There is no offset yet applied, variable or fixed */
		mark_reg_known_zero(env, regs, BPF_REG_0);
		/* remember map_ptr, so that check_map_access()
		 * can check 'value_size' boundary of memory access
		 * to map element वापसed from bpf_map_lookup_elem()
		 */
		अगर (meta.map_ptr == शून्य) अणु
			verbose(env,
				"kernel subsystem misconfigured verifier\n");
			वापस -EINVAL;
		पूर्ण
		regs[BPF_REG_0].map_ptr = meta.map_ptr;
		अगर (fn->ret_type == RET_PTR_TO_MAP_VALUE) अणु
			regs[BPF_REG_0].type = PTR_TO_MAP_VALUE;
			अगर (map_value_has_spin_lock(meta.map_ptr))
				regs[BPF_REG_0].id = ++env->id_gen;
		पूर्ण अन्यथा अणु
			regs[BPF_REG_0].type = PTR_TO_MAP_VALUE_OR_शून्य;
		पूर्ण
	पूर्ण अन्यथा अगर (fn->ret_type == RET_PTR_TO_SOCKET_OR_शून्य) अणु
		mark_reg_known_zero(env, regs, BPF_REG_0);
		regs[BPF_REG_0].type = PTR_TO_SOCKET_OR_शून्य;
	पूर्ण अन्यथा अगर (fn->ret_type == RET_PTR_TO_SOCK_COMMON_OR_शून्य) अणु
		mark_reg_known_zero(env, regs, BPF_REG_0);
		regs[BPF_REG_0].type = PTR_TO_SOCK_COMMON_OR_शून्य;
	पूर्ण अन्यथा अगर (fn->ret_type == RET_PTR_TO_TCP_SOCK_OR_शून्य) अणु
		mark_reg_known_zero(env, regs, BPF_REG_0);
		regs[BPF_REG_0].type = PTR_TO_TCP_SOCK_OR_शून्य;
	पूर्ण अन्यथा अगर (fn->ret_type == RET_PTR_TO_ALLOC_MEM_OR_शून्य) अणु
		mark_reg_known_zero(env, regs, BPF_REG_0);
		regs[BPF_REG_0].type = PTR_TO_MEM_OR_शून्य;
		regs[BPF_REG_0].mem_size = meta.mem_size;
	पूर्ण अन्यथा अगर (fn->ret_type == RET_PTR_TO_MEM_OR_BTF_ID_OR_शून्य ||
		   fn->ret_type == RET_PTR_TO_MEM_OR_BTF_ID) अणु
		स्थिर काष्ठा btf_type *t;

		mark_reg_known_zero(env, regs, BPF_REG_0);
		t = btf_type_skip_modअगरiers(meta.ret_btf, meta.ret_btf_id, शून्य);
		अगर (!btf_type_is_काष्ठा(t)) अणु
			u32 tsize;
			स्थिर काष्ठा btf_type *ret;
			स्थिर अक्षर *tname;

			/* resolve the type size of ksym. */
			ret = btf_resolve_size(meta.ret_btf, t, &tsize);
			अगर (IS_ERR(ret)) अणु
				tname = btf_name_by_offset(meta.ret_btf, t->name_off);
				verbose(env, "unable to resolve the size of type '%s': %ld\n",
					tname, PTR_ERR(ret));
				वापस -EINVAL;
			पूर्ण
			regs[BPF_REG_0].type =
				fn->ret_type == RET_PTR_TO_MEM_OR_BTF_ID ?
				PTR_TO_MEM : PTR_TO_MEM_OR_शून्य;
			regs[BPF_REG_0].mem_size = tsize;
		पूर्ण अन्यथा अणु
			regs[BPF_REG_0].type =
				fn->ret_type == RET_PTR_TO_MEM_OR_BTF_ID ?
				PTR_TO_BTF_ID : PTR_TO_BTF_ID_OR_शून्य;
			regs[BPF_REG_0].btf = meta.ret_btf;
			regs[BPF_REG_0].btf_id = meta.ret_btf_id;
		पूर्ण
	पूर्ण अन्यथा अगर (fn->ret_type == RET_PTR_TO_BTF_ID_OR_शून्य ||
		   fn->ret_type == RET_PTR_TO_BTF_ID) अणु
		पूर्णांक ret_btf_id;

		mark_reg_known_zero(env, regs, BPF_REG_0);
		regs[BPF_REG_0].type = fn->ret_type == RET_PTR_TO_BTF_ID ?
						     PTR_TO_BTF_ID :
						     PTR_TO_BTF_ID_OR_शून्य;
		ret_btf_id = *fn->ret_btf_id;
		अगर (ret_btf_id == 0) अणु
			verbose(env, "invalid return type %d of func %s#%d\n",
				fn->ret_type, func_id_name(func_id), func_id);
			वापस -EINVAL;
		पूर्ण
		/* current BPF helper definitions are only coming from
		 * built-in code with type IDs from  vmlinux BTF
		 */
		regs[BPF_REG_0].btf = btf_vmlinux;
		regs[BPF_REG_0].btf_id = ret_btf_id;
	पूर्ण अन्यथा अणु
		verbose(env, "unknown return type %d of func %s#%d\n",
			fn->ret_type, func_id_name(func_id), func_id);
		वापस -EINVAL;
	पूर्ण

	अगर (reg_type_may_be_null(regs[BPF_REG_0].type))
		regs[BPF_REG_0].id = ++env->id_gen;

	अगर (is_ptr_cast_function(func_id)) अणु
		/* For release_reference() */
		regs[BPF_REG_0].ref_obj_id = meta.ref_obj_id;
	पूर्ण अन्यथा अगर (is_acquire_function(func_id, meta.map_ptr)) अणु
		पूर्णांक id = acquire_reference_state(env, insn_idx);

		अगर (id < 0)
			वापस id;
		/* For mark_ptr_or_null_reg() */
		regs[BPF_REG_0].id = id;
		/* For release_reference() */
		regs[BPF_REG_0].ref_obj_id = id;
	पूर्ण

	करो_refine_retval_range(regs, fn->ret_type, func_id, &meta);

	err = check_map_func_compatibility(env, meta.map_ptr, func_id);
	अगर (err)
		वापस err;

	अगर ((func_id == BPF_FUNC_get_stack ||
	     func_id == BPF_FUNC_get_task_stack) &&
	    !env->prog->has_callchain_buf) अणु
		स्थिर अक्षर *err_str;

#अगर_घोषित CONFIG_PERF_EVENTS
		err = get_callchain_buffers(sysctl_perf_event_max_stack);
		err_str = "cannot get callchain buffer for func %s#%d\n";
#अन्यथा
		err = -ENOTSUPP;
		err_str = "func %s#%d not supported without CONFIG_PERF_EVENTS\n";
#पूर्ण_अगर
		अगर (err) अणु
			verbose(env, err_str, func_id_name(func_id), func_id);
			वापस err;
		पूर्ण

		env->prog->has_callchain_buf = true;
	पूर्ण

	अगर (func_id == BPF_FUNC_get_stackid || func_id == BPF_FUNC_get_stack)
		env->prog->call_get_stack = true;

	अगर (changes_data)
		clear_all_pkt_poपूर्णांकers(env);
	वापस 0;
पूर्ण

/* mark_btf_func_reg_size() is used when the reg size is determined by
 * the BTF func_proto's वापस value size and argument.
 */
अटल व्योम mark_btf_func_reg_size(काष्ठा bpf_verअगरier_env *env, u32 regno,
				   माप_प्रकार reg_size)
अणु
	काष्ठा bpf_reg_state *reg = &cur_regs(env)[regno];

	अगर (regno == BPF_REG_0) अणु
		/* Function वापस value */
		reg->live |= REG_LIVE_WRITTEN;
		reg->subreg_def = reg_size == माप(u64) ?
			DEF_NOT_SUBREG : env->insn_idx + 1;
	पूर्ण अन्यथा अणु
		/* Function argument */
		अगर (reg_size == माप(u64)) अणु
			mark_insn_zext(env, reg);
			mark_reg_पढ़ो(env, reg, reg->parent, REG_LIVE_READ64);
		पूर्ण अन्यथा अणु
			mark_reg_पढ़ो(env, reg, reg->parent, REG_LIVE_READ32);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक check_kfunc_call(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn)
अणु
	स्थिर काष्ठा btf_type *t, *func, *func_proto, *ptr_type;
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	स्थिर अक्षर *func_name, *ptr_type_name;
	u32 i, nargs, func_id, ptr_type_id;
	स्थिर काष्ठा btf_param *args;
	पूर्णांक err;

	func_id = insn->imm;
	func = btf_type_by_id(btf_vmlinux, func_id);
	func_name = btf_name_by_offset(btf_vmlinux, func->name_off);
	func_proto = btf_type_by_id(btf_vmlinux, func->type);

	अगर (!env->ops->check_kfunc_call ||
	    !env->ops->check_kfunc_call(func_id)) अणु
		verbose(env, "calling kernel function %s is not allowed\n",
			func_name);
		वापस -EACCES;
	पूर्ण

	/* Check the arguments */
	err = btf_check_kfunc_arg_match(env, btf_vmlinux, func_id, regs);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < CALLER_SAVED_REGS; i++)
		mark_reg_not_init(env, regs, caller_saved[i]);

	/* Check वापस type */
	t = btf_type_skip_modअगरiers(btf_vmlinux, func_proto->type, शून्य);
	अगर (btf_type_is_scalar(t)) अणु
		mark_reg_unknown(env, regs, BPF_REG_0);
		mark_btf_func_reg_size(env, BPF_REG_0, t->size);
	पूर्ण अन्यथा अगर (btf_type_is_ptr(t)) अणु
		ptr_type = btf_type_skip_modअगरiers(btf_vmlinux, t->type,
						   &ptr_type_id);
		अगर (!btf_type_is_काष्ठा(ptr_type)) अणु
			ptr_type_name = btf_name_by_offset(btf_vmlinux,
							   ptr_type->name_off);
			verbose(env, "kernel function %s returns pointer type %s %s is not supported\n",
				func_name, btf_type_str(ptr_type),
				ptr_type_name);
			वापस -EINVAL;
		पूर्ण
		mark_reg_known_zero(env, regs, BPF_REG_0);
		regs[BPF_REG_0].btf = btf_vmlinux;
		regs[BPF_REG_0].type = PTR_TO_BTF_ID;
		regs[BPF_REG_0].btf_id = ptr_type_id;
		mark_btf_func_reg_size(env, BPF_REG_0, माप(व्योम *));
	पूर्ण /* अन्यथा अणु add_kfunc_call() ensures it is btf_type_is_व्योम(t) पूर्ण */

	nargs = btf_type_vlen(func_proto);
	args = (स्थिर काष्ठा btf_param *)(func_proto + 1);
	क्रम (i = 0; i < nargs; i++) अणु
		u32 regno = i + 1;

		t = btf_type_skip_modअगरiers(btf_vmlinux, args[i].type, शून्य);
		अगर (btf_type_is_ptr(t))
			mark_btf_func_reg_size(env, regno, माप(व्योम *));
		अन्यथा
			/* scalar. ensured by btf_check_kfunc_arg_match() */
			mark_btf_func_reg_size(env, regno, t->size);
	पूर्ण

	वापस 0;
पूर्ण

अटल bool चिन्हित_add_overflows(s64 a, s64 b)
अणु
	/* Do the add in u64, where overflow is well-defined */
	s64 res = (s64)((u64)a + (u64)b);

	अगर (b < 0)
		वापस res > a;
	वापस res < a;
पूर्ण

अटल bool चिन्हित_add32_overflows(s32 a, s32 b)
अणु
	/* Do the add in u32, where overflow is well-defined */
	s32 res = (s32)((u32)a + (u32)b);

	अगर (b < 0)
		वापस res > a;
	वापस res < a;
पूर्ण

अटल bool चिन्हित_sub_overflows(s64 a, s64 b)
अणु
	/* Do the sub in u64, where overflow is well-defined */
	s64 res = (s64)((u64)a - (u64)b);

	अगर (b < 0)
		वापस res < a;
	वापस res > a;
पूर्ण

अटल bool चिन्हित_sub32_overflows(s32 a, s32 b)
अणु
	/* Do the sub in u32, where overflow is well-defined */
	s32 res = (s32)((u32)a - (u32)b);

	अगर (b < 0)
		वापस res < a;
	वापस res > a;
पूर्ण

अटल bool check_reg_sane_offset(काष्ठा bpf_verअगरier_env *env,
				  स्थिर काष्ठा bpf_reg_state *reg,
				  क्रमागत bpf_reg_type type)
अणु
	bool known = tnum_is_स्थिर(reg->var_off);
	s64 val = reg->var_off.value;
	s64 smin = reg->smin_value;

	अगर (known && (val >= BPF_MAX_VAR_OFF || val <= -BPF_MAX_VAR_OFF)) अणु
		verbose(env, "math between %s pointer and %lld is not allowed\n",
			reg_type_str[type], val);
		वापस false;
	पूर्ण

	अगर (reg->off >= BPF_MAX_VAR_OFF || reg->off <= -BPF_MAX_VAR_OFF) अणु
		verbose(env, "%s pointer offset %d is not allowed\n",
			reg_type_str[type], reg->off);
		वापस false;
	पूर्ण

	अगर (smin == S64_MIN) अणु
		verbose(env, "math between %s pointer and register with unbounded min value is not allowed\n",
			reg_type_str[type]);
		वापस false;
	पूर्ण

	अगर (smin >= BPF_MAX_VAR_OFF || smin <= -BPF_MAX_VAR_OFF) अणु
		verbose(env, "value %lld makes %s pointer be out of bounds\n",
			smin, reg_type_str[type]);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल काष्ठा bpf_insn_aux_data *cur_aux(काष्ठा bpf_verअगरier_env *env)
अणु
	वापस &env->insn_aux_data[env->insn_idx];
पूर्ण

क्रमागत अणु
	REASON_BOUNDS	= -1,
	REASON_TYPE	= -2,
	REASON_PATHS	= -3,
	REASON_LIMIT	= -4,
	REASON_STACK	= -5,
पूर्ण;

अटल पूर्णांक retrieve_ptr_limit(स्थिर काष्ठा bpf_reg_state *ptr_reg,
			      u32 *alu_limit, bool mask_to_left)
अणु
	u32 max = 0, ptr_limit = 0;

	चयन (ptr_reg->type) अणु
	हाल PTR_TO_STACK:
		/* Offset 0 is out-of-bounds, but acceptable start क्रम the
		 * left direction, see BPF_REG_FP. Also, unknown scalar
		 * offset where we would need to deal with min/max bounds is
		 * currently prohibited क्रम unprivileged.
		 */
		max = MAX_BPF_STACK + mask_to_left;
		ptr_limit = -(ptr_reg->var_off.value + ptr_reg->off);
		अवरोध;
	हाल PTR_TO_MAP_VALUE:
		max = ptr_reg->map_ptr->value_size;
		ptr_limit = (mask_to_left ?
			     ptr_reg->smin_value :
			     ptr_reg->umax_value) + ptr_reg->off;
		अवरोध;
	शेष:
		वापस REASON_TYPE;
	पूर्ण

	अगर (ptr_limit >= max)
		वापस REASON_LIMIT;
	*alu_limit = ptr_limit;
	वापस 0;
पूर्ण

अटल bool can_skip_alu_sanitation(स्थिर काष्ठा bpf_verअगरier_env *env,
				    स्थिर काष्ठा bpf_insn *insn)
अणु
	वापस env->bypass_spec_v1 || BPF_SRC(insn->code) == BPF_K;
पूर्ण

अटल पूर्णांक update_alu_sanitation_state(काष्ठा bpf_insn_aux_data *aux,
				       u32 alu_state, u32 alu_limit)
अणु
	/* If we arrived here from dअगरferent branches with dअगरferent
	 * state or limits to sanitize, then this won't work.
	 */
	अगर (aux->alu_state &&
	    (aux->alu_state != alu_state ||
	     aux->alu_limit != alu_limit))
		वापस REASON_PATHS;

	/* Corresponding fixup करोne in करो_misc_fixups(). */
	aux->alu_state = alu_state;
	aux->alu_limit = alu_limit;
	वापस 0;
पूर्ण

अटल पूर्णांक sanitize_val_alu(काष्ठा bpf_verअगरier_env *env,
			    काष्ठा bpf_insn *insn)
अणु
	काष्ठा bpf_insn_aux_data *aux = cur_aux(env);

	अगर (can_skip_alu_sanitation(env, insn))
		वापस 0;

	वापस update_alu_sanitation_state(aux, BPF_ALU_NON_POINTER, 0);
पूर्ण

अटल bool sanitize_needed(u8 opcode)
अणु
	वापस opcode == BPF_ADD || opcode == BPF_SUB;
पूर्ण

काष्ठा bpf_sanitize_info अणु
	काष्ठा bpf_insn_aux_data aux;
	bool mask_to_left;
पूर्ण;

अटल काष्ठा bpf_verअगरier_state *
sanitize_speculative_path(काष्ठा bpf_verअगरier_env *env,
			  स्थिर काष्ठा bpf_insn *insn,
			  u32 next_idx, u32 curr_idx)
अणु
	काष्ठा bpf_verअगरier_state *branch;
	काष्ठा bpf_reg_state *regs;

	branch = push_stack(env, next_idx, curr_idx, true);
	अगर (branch && insn) अणु
		regs = branch->frame[branch->curframe]->regs;
		अगर (BPF_SRC(insn->code) == BPF_K) अणु
			mark_reg_unknown(env, regs, insn->dst_reg);
		पूर्ण अन्यथा अगर (BPF_SRC(insn->code) == BPF_X) अणु
			mark_reg_unknown(env, regs, insn->dst_reg);
			mark_reg_unknown(env, regs, insn->src_reg);
		पूर्ण
	पूर्ण
	वापस branch;
पूर्ण

अटल पूर्णांक sanitize_ptr_alu(काष्ठा bpf_verअगरier_env *env,
			    काष्ठा bpf_insn *insn,
			    स्थिर काष्ठा bpf_reg_state *ptr_reg,
			    स्थिर काष्ठा bpf_reg_state *off_reg,
			    काष्ठा bpf_reg_state *dst_reg,
			    काष्ठा bpf_sanitize_info *info,
			    स्थिर bool commit_winकरोw)
अणु
	काष्ठा bpf_insn_aux_data *aux = commit_winकरोw ? cur_aux(env) : &info->aux;
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	bool off_is_imm = tnum_is_स्थिर(off_reg->var_off);
	bool off_is_neg = off_reg->smin_value < 0;
	bool ptr_is_dst_reg = ptr_reg == dst_reg;
	u8 opcode = BPF_OP(insn->code);
	u32 alu_state, alu_limit;
	काष्ठा bpf_reg_state पंचांगp;
	bool ret;
	पूर्णांक err;

	अगर (can_skip_alu_sanitation(env, insn))
		वापस 0;

	/* We alपढ़ोy marked aux क्रम masking from non-speculative
	 * paths, thus we got here in the first place. We only care
	 * to explore bad access from here.
	 */
	अगर (vstate->speculative)
		जाओ करो_sim;

	अगर (!commit_winकरोw) अणु
		अगर (!tnum_is_स्थिर(off_reg->var_off) &&
		    (off_reg->smin_value < 0) != (off_reg->smax_value < 0))
			वापस REASON_BOUNDS;

		info->mask_to_left = (opcode == BPF_ADD &&  off_is_neg) ||
				     (opcode == BPF_SUB && !off_is_neg);
	पूर्ण

	err = retrieve_ptr_limit(ptr_reg, &alu_limit, info->mask_to_left);
	अगर (err < 0)
		वापस err;

	अगर (commit_winकरोw) अणु
		/* In commit phase we narrow the masking winकरोw based on
		 * the observed poपूर्णांकer move after the simulated operation.
		 */
		alu_state = info->aux.alu_state;
		alu_limit = असल(info->aux.alu_limit - alu_limit);
	पूर्ण अन्यथा अणु
		alu_state  = off_is_neg ? BPF_ALU_NEG_VALUE : 0;
		alu_state |= off_is_imm ? BPF_ALU_IMMEDIATE : 0;
		alu_state |= ptr_is_dst_reg ?
			     BPF_ALU_SANITIZE_SRC : BPF_ALU_SANITIZE_DST;
	पूर्ण

	err = update_alu_sanitation_state(aux, alu_state, alu_limit);
	अगर (err < 0)
		वापस err;
करो_sim:
	/* If we're in commit phase, we're करोne here given we alपढ़ोy
	 * pushed the truncated dst_reg पूर्णांकo the speculative verअगरication
	 * stack.
	 *
	 * Also, when रेजिस्टर is a known स्थिरant, we reग_लिखो रेजिस्टर-based
	 * operation to immediate-based, and thus करो not need masking (and as
	 * a consequence, करो not need to simulate the zero-truncation either).
	 */
	अगर (commit_winकरोw || off_is_imm)
		वापस 0;

	/* Simulate and find potential out-of-bounds access under
	 * speculative execution from truncation as a result of
	 * masking when off was not within expected range. If off
	 * sits in dst, then we temporarily need to move ptr there
	 * to simulate dst (== 0) +/-= ptr. Needed, क्रम example,
	 * क्रम हालs where we use K-based arithmetic in one direction
	 * and truncated reg-based in the other in order to explore
	 * bad access.
	 */
	अगर (!ptr_is_dst_reg) अणु
		पंचांगp = *dst_reg;
		*dst_reg = *ptr_reg;
	पूर्ण
	ret = sanitize_speculative_path(env, शून्य, env->insn_idx + 1,
					env->insn_idx);
	अगर (!ptr_is_dst_reg && ret)
		*dst_reg = पंचांगp;
	वापस !ret ? REASON_STACK : 0;
पूर्ण

अटल व्योम sanitize_mark_insn_seen(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;

	/* If we simulate paths under speculation, we करोn't update the
	 * insn as 'seen' such that when we verअगरy unreachable paths in
	 * the non-speculative करोमुख्य, sanitize_dead_code() can still
	 * reग_लिखो/sanitize them.
	 */
	अगर (!vstate->speculative)
		env->insn_aux_data[env->insn_idx].seen = env->pass_cnt;
पूर्ण

अटल पूर्णांक sanitize_err(काष्ठा bpf_verअगरier_env *env,
			स्थिर काष्ठा bpf_insn *insn, पूर्णांक reason,
			स्थिर काष्ठा bpf_reg_state *off_reg,
			स्थिर काष्ठा bpf_reg_state *dst_reg)
अणु
	अटल स्थिर अक्षर *err = "pointer arithmetic with it prohibited for !root";
	स्थिर अक्षर *op = BPF_OP(insn->code) == BPF_ADD ? "add" : "sub";
	u32 dst = insn->dst_reg, src = insn->src_reg;

	चयन (reason) अणु
	हाल REASON_BOUNDS:
		verbose(env, "R%d has unknown scalar with mixed signed bounds, %s\n",
			off_reg == dst_reg ? dst : src, err);
		अवरोध;
	हाल REASON_TYPE:
		verbose(env, "R%d has pointer with unsupported alu operation, %s\n",
			off_reg == dst_reg ? src : dst, err);
		अवरोध;
	हाल REASON_PATHS:
		verbose(env, "R%d tried to %s from different maps, paths or scalars, %s\n",
			dst, op, err);
		अवरोध;
	हाल REASON_LIMIT:
		verbose(env, "R%d tried to %s beyond pointer bounds, %s\n",
			dst, op, err);
		अवरोध;
	हाल REASON_STACK:
		verbose(env, "R%d could not be pushed for speculative verification, %s\n",
			dst, err);
		अवरोध;
	शेष:
		verbose(env, "verifier internal error: unknown reason (%d)\n",
			reason);
		अवरोध;
	पूर्ण

	वापस -EACCES;
पूर्ण

/* check that stack access falls within stack limits and that 'reg' doesn't
 * have a variable offset.
 *
 * Variable offset is prohibited क्रम unprivileged mode क्रम simplicity since it
 * requires corresponding support in Spectre masking क्रम stack ALU.  See also
 * retrieve_ptr_limit().
 *
 *
 * 'off' includes 'reg->off'.
 */
अटल पूर्णांक check_stack_access_क्रम_ptr_arithmetic(
				काष्ठा bpf_verअगरier_env *env,
				पूर्णांक regno,
				स्थिर काष्ठा bpf_reg_state *reg,
				पूर्णांक off)
अणु
	अगर (!tnum_is_स्थिर(reg->var_off)) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg->var_off);
		verbose(env, "R%d variable stack access prohibited for !root, var_off=%s off=%d\n",
			regno, tn_buf, off);
		वापस -EACCES;
	पूर्ण

	अगर (off >= 0 || off < -MAX_BPF_STACK) अणु
		verbose(env, "R%d stack pointer arithmetic goes out of range, "
			"prohibited for !root; off=%d\n", regno, off);
		वापस -EACCES;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक sanitize_check_bounds(काष्ठा bpf_verअगरier_env *env,
				 स्थिर काष्ठा bpf_insn *insn,
				 स्थिर काष्ठा bpf_reg_state *dst_reg)
अणु
	u32 dst = insn->dst_reg;

	/* For unprivileged we require that resulting offset must be in bounds
	 * in order to be able to sanitize access later on.
	 */
	अगर (env->bypass_spec_v1)
		वापस 0;

	चयन (dst_reg->type) अणु
	हाल PTR_TO_STACK:
		अगर (check_stack_access_क्रम_ptr_arithmetic(env, dst, dst_reg,
					dst_reg->off + dst_reg->var_off.value))
			वापस -EACCES;
		अवरोध;
	हाल PTR_TO_MAP_VALUE:
		अगर (check_map_access(env, dst, dst_reg->off, 1, false)) अणु
			verbose(env, "R%d pointer arithmetic of map value goes out of range, "
				"prohibited for !root\n", dst);
			वापस -EACCES;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

/* Handles arithmetic on a poपूर्णांकer and a scalar: computes new min/max and var_off.
 * Caller should also handle BPF_MOV हाल separately.
 * If we वापस -EACCES, caller may want to try again treating poपूर्णांकer as a
 * scalar.  So we only emit a diagnostic अगर !env->allow_ptr_leaks.
 */
अटल पूर्णांक adjust_ptr_min_max_vals(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_insn *insn,
				   स्थिर काष्ठा bpf_reg_state *ptr_reg,
				   स्थिर काष्ठा bpf_reg_state *off_reg)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	काष्ठा bpf_reg_state *regs = state->regs, *dst_reg;
	bool known = tnum_is_स्थिर(off_reg->var_off);
	s64 smin_val = off_reg->smin_value, smax_val = off_reg->smax_value,
	    smin_ptr = ptr_reg->smin_value, smax_ptr = ptr_reg->smax_value;
	u64 umin_val = off_reg->umin_value, umax_val = off_reg->umax_value,
	    umin_ptr = ptr_reg->umin_value, umax_ptr = ptr_reg->umax_value;
	काष्ठा bpf_sanitize_info info = अणुपूर्ण;
	u8 opcode = BPF_OP(insn->code);
	u32 dst = insn->dst_reg;
	पूर्णांक ret;

	dst_reg = &regs[dst];

	अगर ((known && (smin_val != smax_val || umin_val != umax_val)) ||
	    smin_val > smax_val || umin_val > umax_val) अणु
		/* Taपूर्णांक dst रेजिस्टर अगर offset had invalid bounds derived from
		 * e.g. dead branches.
		 */
		__mark_reg_unknown(env, dst_reg);
		वापस 0;
	पूर्ण

	अगर (BPF_CLASS(insn->code) != BPF_ALU64) अणु
		/* 32-bit ALU ops on poपूर्णांकers produce (meaningless) scalars */
		अगर (opcode == BPF_SUB && env->allow_ptr_leaks) अणु
			__mark_reg_unknown(env, dst_reg);
			वापस 0;
		पूर्ण

		verbose(env,
			"R%d 32-bit pointer arithmetic prohibited\n",
			dst);
		वापस -EACCES;
	पूर्ण

	चयन (ptr_reg->type) अणु
	हाल PTR_TO_MAP_VALUE_OR_शून्य:
		verbose(env, "R%d pointer arithmetic on %s prohibited, null-check it first\n",
			dst, reg_type_str[ptr_reg->type]);
		वापस -EACCES;
	हाल CONST_PTR_TO_MAP:
		/* smin_val represents the known value */
		अगर (known && smin_val == 0 && opcode == BPF_ADD)
			अवरोध;
		fallthrough;
	हाल PTR_TO_PACKET_END:
	हाल PTR_TO_SOCKET:
	हाल PTR_TO_SOCKET_OR_शून्य:
	हाल PTR_TO_SOCK_COMMON:
	हाल PTR_TO_SOCK_COMMON_OR_शून्य:
	हाल PTR_TO_TCP_SOCK:
	हाल PTR_TO_TCP_SOCK_OR_शून्य:
	हाल PTR_TO_XDP_SOCK:
		verbose(env, "R%d pointer arithmetic on %s prohibited\n",
			dst, reg_type_str[ptr_reg->type]);
		वापस -EACCES;
	शेष:
		अवरोध;
	पूर्ण

	/* In हाल of 'scalar += pointer', dst_reg inherits poपूर्णांकer type and id.
	 * The id may be overwritten later अगर we create a new variable offset.
	 */
	dst_reg->type = ptr_reg->type;
	dst_reg->id = ptr_reg->id;

	अगर (!check_reg_sane_offset(env, off_reg, ptr_reg->type) ||
	    !check_reg_sane_offset(env, ptr_reg, ptr_reg->type))
		वापस -EINVAL;

	/* poपूर्णांकer types करो not carry 32-bit bounds at the moment. */
	__mark_reg32_unbounded(dst_reg);

	अगर (sanitize_needed(opcode)) अणु
		ret = sanitize_ptr_alu(env, insn, ptr_reg, off_reg, dst_reg,
				       &info, false);
		अगर (ret < 0)
			वापस sanitize_err(env, insn, ret, off_reg, dst_reg);
	पूर्ण

	चयन (opcode) अणु
	हाल BPF_ADD:
		/* We can take a fixed offset as दीर्घ as it करोesn't overflow
		 * the s32 'off' field
		 */
		अगर (known && (ptr_reg->off + smin_val ==
			      (s64)(s32)(ptr_reg->off + smin_val))) अणु
			/* poपूर्णांकer += K.  Accumulate it पूर्णांकo fixed offset */
			dst_reg->smin_value = smin_ptr;
			dst_reg->smax_value = smax_ptr;
			dst_reg->umin_value = umin_ptr;
			dst_reg->umax_value = umax_ptr;
			dst_reg->var_off = ptr_reg->var_off;
			dst_reg->off = ptr_reg->off + smin_val;
			dst_reg->raw = ptr_reg->raw;
			अवरोध;
		पूर्ण
		/* A new variable offset is created.  Note that off_reg->off
		 * == 0, since it's a scalar.
		 * dst_reg माला_लो the poपूर्णांकer type and since some positive
		 * पूर्णांकeger value was added to the poपूर्णांकer, give it a new 'id'
		 * अगर it's a PTR_TO_PACKET.
		 * this creates a new 'base' poपूर्णांकer, off_reg (variable) माला_लो
		 * added पूर्णांकo the variable offset, and we copy the fixed offset
		 * from ptr_reg.
		 */
		अगर (चिन्हित_add_overflows(smin_ptr, smin_val) ||
		    चिन्हित_add_overflows(smax_ptr, smax_val)) अणु
			dst_reg->smin_value = S64_MIN;
			dst_reg->smax_value = S64_MAX;
		पूर्ण अन्यथा अणु
			dst_reg->smin_value = smin_ptr + smin_val;
			dst_reg->smax_value = smax_ptr + smax_val;
		पूर्ण
		अगर (umin_ptr + umin_val < umin_ptr ||
		    umax_ptr + umax_val < umax_ptr) अणु
			dst_reg->umin_value = 0;
			dst_reg->umax_value = U64_MAX;
		पूर्ण अन्यथा अणु
			dst_reg->umin_value = umin_ptr + umin_val;
			dst_reg->umax_value = umax_ptr + umax_val;
		पूर्ण
		dst_reg->var_off = tnum_add(ptr_reg->var_off, off_reg->var_off);
		dst_reg->off = ptr_reg->off;
		dst_reg->raw = ptr_reg->raw;
		अगर (reg_is_pkt_poपूर्णांकer(ptr_reg)) अणु
			dst_reg->id = ++env->id_gen;
			/* something was added to pkt_ptr, set range to zero */
			स_रखो(&dst_reg->raw, 0, माप(dst_reg->raw));
		पूर्ण
		अवरोध;
	हाल BPF_SUB:
		अगर (dst_reg == off_reg) अणु
			/* scalar -= poपूर्णांकer.  Creates an unknown scalar */
			verbose(env, "R%d tried to subtract pointer from scalar\n",
				dst);
			वापस -EACCES;
		पूर्ण
		/* We करोn't allow subtraction from FP, because (according to
		 * test_verअगरier.c test "invalid fp arithmetic", JITs might not
		 * be able to deal with it.
		 */
		अगर (ptr_reg->type == PTR_TO_STACK) अणु
			verbose(env, "R%d subtraction from stack pointer prohibited\n",
				dst);
			वापस -EACCES;
		पूर्ण
		अगर (known && (ptr_reg->off - smin_val ==
			      (s64)(s32)(ptr_reg->off - smin_val))) अणु
			/* poपूर्णांकer -= K.  Subtract it from fixed offset */
			dst_reg->smin_value = smin_ptr;
			dst_reg->smax_value = smax_ptr;
			dst_reg->umin_value = umin_ptr;
			dst_reg->umax_value = umax_ptr;
			dst_reg->var_off = ptr_reg->var_off;
			dst_reg->id = ptr_reg->id;
			dst_reg->off = ptr_reg->off - smin_val;
			dst_reg->raw = ptr_reg->raw;
			अवरोध;
		पूर्ण
		/* A new variable offset is created.  If the subtrahend is known
		 * nonnegative, then any reg->range we had beक्रमe is still good.
		 */
		अगर (चिन्हित_sub_overflows(smin_ptr, smax_val) ||
		    चिन्हित_sub_overflows(smax_ptr, smin_val)) अणु
			/* Overflow possible, we know nothing */
			dst_reg->smin_value = S64_MIN;
			dst_reg->smax_value = S64_MAX;
		पूर्ण अन्यथा अणु
			dst_reg->smin_value = smin_ptr - smax_val;
			dst_reg->smax_value = smax_ptr - smin_val;
		पूर्ण
		अगर (umin_ptr < umax_val) अणु
			/* Overflow possible, we know nothing */
			dst_reg->umin_value = 0;
			dst_reg->umax_value = U64_MAX;
		पूर्ण अन्यथा अणु
			/* Cannot overflow (as दीर्घ as bounds are consistent) */
			dst_reg->umin_value = umin_ptr - umax_val;
			dst_reg->umax_value = umax_ptr - umin_val;
		पूर्ण
		dst_reg->var_off = tnum_sub(ptr_reg->var_off, off_reg->var_off);
		dst_reg->off = ptr_reg->off;
		dst_reg->raw = ptr_reg->raw;
		अगर (reg_is_pkt_poपूर्णांकer(ptr_reg)) अणु
			dst_reg->id = ++env->id_gen;
			/* something was added to pkt_ptr, set range to zero */
			अगर (smin_val < 0)
				स_रखो(&dst_reg->raw, 0, माप(dst_reg->raw));
		पूर्ण
		अवरोध;
	हाल BPF_AND:
	हाल BPF_OR:
	हाल BPF_XOR:
		/* bitwise ops on poपूर्णांकers are troublesome, prohibit. */
		verbose(env, "R%d bitwise operator %s on pointer prohibited\n",
			dst, bpf_alu_string[opcode >> 4]);
		वापस -EACCES;
	शेष:
		/* other चालकs (e.g. MUL,LSH) produce non-poपूर्णांकer results */
		verbose(env, "R%d pointer arithmetic with %s operator prohibited\n",
			dst, bpf_alu_string[opcode >> 4]);
		वापस -EACCES;
	पूर्ण

	अगर (!check_reg_sane_offset(env, dst_reg, ptr_reg->type))
		वापस -EINVAL;

	__update_reg_bounds(dst_reg);
	__reg_deduce_bounds(dst_reg);
	__reg_bound_offset(dst_reg);

	अगर (sanitize_check_bounds(env, insn, dst_reg) < 0)
		वापस -EACCES;
	अगर (sanitize_needed(opcode)) अणु
		ret = sanitize_ptr_alu(env, insn, dst_reg, off_reg, dst_reg,
				       &info, true);
		अगर (ret < 0)
			वापस sanitize_err(env, insn, ret, off_reg, dst_reg);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम scalar32_min_max_add(काष्ठा bpf_reg_state *dst_reg,
				 काष्ठा bpf_reg_state *src_reg)
अणु
	s32 smin_val = src_reg->s32_min_value;
	s32 smax_val = src_reg->s32_max_value;
	u32 umin_val = src_reg->u32_min_value;
	u32 umax_val = src_reg->u32_max_value;

	अगर (चिन्हित_add32_overflows(dst_reg->s32_min_value, smin_val) ||
	    चिन्हित_add32_overflows(dst_reg->s32_max_value, smax_val)) अणु
		dst_reg->s32_min_value = S32_MIN;
		dst_reg->s32_max_value = S32_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->s32_min_value += smin_val;
		dst_reg->s32_max_value += smax_val;
	पूर्ण
	अगर (dst_reg->u32_min_value + umin_val < umin_val ||
	    dst_reg->u32_max_value + umax_val < umax_val) अणु
		dst_reg->u32_min_value = 0;
		dst_reg->u32_max_value = U32_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->u32_min_value += umin_val;
		dst_reg->u32_max_value += umax_val;
	पूर्ण
पूर्ण

अटल व्योम scalar_min_max_add(काष्ठा bpf_reg_state *dst_reg,
			       काष्ठा bpf_reg_state *src_reg)
अणु
	s64 smin_val = src_reg->smin_value;
	s64 smax_val = src_reg->smax_value;
	u64 umin_val = src_reg->umin_value;
	u64 umax_val = src_reg->umax_value;

	अगर (चिन्हित_add_overflows(dst_reg->smin_value, smin_val) ||
	    चिन्हित_add_overflows(dst_reg->smax_value, smax_val)) अणु
		dst_reg->smin_value = S64_MIN;
		dst_reg->smax_value = S64_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->smin_value += smin_val;
		dst_reg->smax_value += smax_val;
	पूर्ण
	अगर (dst_reg->umin_value + umin_val < umin_val ||
	    dst_reg->umax_value + umax_val < umax_val) अणु
		dst_reg->umin_value = 0;
		dst_reg->umax_value = U64_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->umin_value += umin_val;
		dst_reg->umax_value += umax_val;
	पूर्ण
पूर्ण

अटल व्योम scalar32_min_max_sub(काष्ठा bpf_reg_state *dst_reg,
				 काष्ठा bpf_reg_state *src_reg)
अणु
	s32 smin_val = src_reg->s32_min_value;
	s32 smax_val = src_reg->s32_max_value;
	u32 umin_val = src_reg->u32_min_value;
	u32 umax_val = src_reg->u32_max_value;

	अगर (चिन्हित_sub32_overflows(dst_reg->s32_min_value, smax_val) ||
	    चिन्हित_sub32_overflows(dst_reg->s32_max_value, smin_val)) अणु
		/* Overflow possible, we know nothing */
		dst_reg->s32_min_value = S32_MIN;
		dst_reg->s32_max_value = S32_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->s32_min_value -= smax_val;
		dst_reg->s32_max_value -= smin_val;
	पूर्ण
	अगर (dst_reg->u32_min_value < umax_val) अणु
		/* Overflow possible, we know nothing */
		dst_reg->u32_min_value = 0;
		dst_reg->u32_max_value = U32_MAX;
	पूर्ण अन्यथा अणु
		/* Cannot overflow (as दीर्घ as bounds are consistent) */
		dst_reg->u32_min_value -= umax_val;
		dst_reg->u32_max_value -= umin_val;
	पूर्ण
पूर्ण

अटल व्योम scalar_min_max_sub(काष्ठा bpf_reg_state *dst_reg,
			       काष्ठा bpf_reg_state *src_reg)
अणु
	s64 smin_val = src_reg->smin_value;
	s64 smax_val = src_reg->smax_value;
	u64 umin_val = src_reg->umin_value;
	u64 umax_val = src_reg->umax_value;

	अगर (चिन्हित_sub_overflows(dst_reg->smin_value, smax_val) ||
	    चिन्हित_sub_overflows(dst_reg->smax_value, smin_val)) अणु
		/* Overflow possible, we know nothing */
		dst_reg->smin_value = S64_MIN;
		dst_reg->smax_value = S64_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->smin_value -= smax_val;
		dst_reg->smax_value -= smin_val;
	पूर्ण
	अगर (dst_reg->umin_value < umax_val) अणु
		/* Overflow possible, we know nothing */
		dst_reg->umin_value = 0;
		dst_reg->umax_value = U64_MAX;
	पूर्ण अन्यथा अणु
		/* Cannot overflow (as दीर्घ as bounds are consistent) */
		dst_reg->umin_value -= umax_val;
		dst_reg->umax_value -= umin_val;
	पूर्ण
पूर्ण

अटल व्योम scalar32_min_max_mul(काष्ठा bpf_reg_state *dst_reg,
				 काष्ठा bpf_reg_state *src_reg)
अणु
	s32 smin_val = src_reg->s32_min_value;
	u32 umin_val = src_reg->u32_min_value;
	u32 umax_val = src_reg->u32_max_value;

	अगर (smin_val < 0 || dst_reg->s32_min_value < 0) अणु
		/* Ain't nobody got समय to multiply that sign */
		__mark_reg32_unbounded(dst_reg);
		वापस;
	पूर्ण
	/* Both values are positive, so we can work with अचिन्हित and
	 * copy the result to चिन्हित (unless it exceeds S32_MAX).
	 */
	अगर (umax_val > U16_MAX || dst_reg->u32_max_value > U16_MAX) अणु
		/* Potential overflow, we know nothing */
		__mark_reg32_unbounded(dst_reg);
		वापस;
	पूर्ण
	dst_reg->u32_min_value *= umin_val;
	dst_reg->u32_max_value *= umax_val;
	अगर (dst_reg->u32_max_value > S32_MAX) अणु
		/* Overflow possible, we know nothing */
		dst_reg->s32_min_value = S32_MIN;
		dst_reg->s32_max_value = S32_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->s32_min_value = dst_reg->u32_min_value;
		dst_reg->s32_max_value = dst_reg->u32_max_value;
	पूर्ण
पूर्ण

अटल व्योम scalar_min_max_mul(काष्ठा bpf_reg_state *dst_reg,
			       काष्ठा bpf_reg_state *src_reg)
अणु
	s64 smin_val = src_reg->smin_value;
	u64 umin_val = src_reg->umin_value;
	u64 umax_val = src_reg->umax_value;

	अगर (smin_val < 0 || dst_reg->smin_value < 0) अणु
		/* Ain't nobody got समय to multiply that sign */
		__mark_reg64_unbounded(dst_reg);
		वापस;
	पूर्ण
	/* Both values are positive, so we can work with अचिन्हित and
	 * copy the result to चिन्हित (unless it exceeds S64_MAX).
	 */
	अगर (umax_val > U32_MAX || dst_reg->umax_value > U32_MAX) अणु
		/* Potential overflow, we know nothing */
		__mark_reg64_unbounded(dst_reg);
		वापस;
	पूर्ण
	dst_reg->umin_value *= umin_val;
	dst_reg->umax_value *= umax_val;
	अगर (dst_reg->umax_value > S64_MAX) अणु
		/* Overflow possible, we know nothing */
		dst_reg->smin_value = S64_MIN;
		dst_reg->smax_value = S64_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->smin_value = dst_reg->umin_value;
		dst_reg->smax_value = dst_reg->umax_value;
	पूर्ण
पूर्ण

अटल व्योम scalar32_min_max_and(काष्ठा bpf_reg_state *dst_reg,
				 काष्ठा bpf_reg_state *src_reg)
अणु
	bool src_known = tnum_subreg_is_स्थिर(src_reg->var_off);
	bool dst_known = tnum_subreg_is_स्थिर(dst_reg->var_off);
	काष्ठा tnum var32_off = tnum_subreg(dst_reg->var_off);
	s32 smin_val = src_reg->s32_min_value;
	u32 umax_val = src_reg->u32_max_value;

	अगर (src_known && dst_known) अणु
		__mark_reg32_known(dst_reg, var32_off.value);
		वापस;
	पूर्ण

	/* We get our minimum from the var_off, since that's inherently
	 * bitwise.  Our maximum is the minimum of the opeअक्रमs' maxima.
	 */
	dst_reg->u32_min_value = var32_off.value;
	dst_reg->u32_max_value = min(dst_reg->u32_max_value, umax_val);
	अगर (dst_reg->s32_min_value < 0 || smin_val < 0) अणु
		/* Lose चिन्हित bounds when ANDing negative numbers,
		 * ain't nobody got समय क्रम that.
		 */
		dst_reg->s32_min_value = S32_MIN;
		dst_reg->s32_max_value = S32_MAX;
	पूर्ण अन्यथा अणु
		/* ANDing two positives gives a positive, so safe to
		 * cast result पूर्णांकo s64.
		 */
		dst_reg->s32_min_value = dst_reg->u32_min_value;
		dst_reg->s32_max_value = dst_reg->u32_max_value;
	पूर्ण
पूर्ण

अटल व्योम scalar_min_max_and(काष्ठा bpf_reg_state *dst_reg,
			       काष्ठा bpf_reg_state *src_reg)
अणु
	bool src_known = tnum_is_स्थिर(src_reg->var_off);
	bool dst_known = tnum_is_स्थिर(dst_reg->var_off);
	s64 smin_val = src_reg->smin_value;
	u64 umax_val = src_reg->umax_value;

	अगर (src_known && dst_known) अणु
		__mark_reg_known(dst_reg, dst_reg->var_off.value);
		वापस;
	पूर्ण

	/* We get our minimum from the var_off, since that's inherently
	 * bitwise.  Our maximum is the minimum of the opeअक्रमs' maxima.
	 */
	dst_reg->umin_value = dst_reg->var_off.value;
	dst_reg->umax_value = min(dst_reg->umax_value, umax_val);
	अगर (dst_reg->smin_value < 0 || smin_val < 0) अणु
		/* Lose चिन्हित bounds when ANDing negative numbers,
		 * ain't nobody got समय क्रम that.
		 */
		dst_reg->smin_value = S64_MIN;
		dst_reg->smax_value = S64_MAX;
	पूर्ण अन्यथा अणु
		/* ANDing two positives gives a positive, so safe to
		 * cast result पूर्णांकo s64.
		 */
		dst_reg->smin_value = dst_reg->umin_value;
		dst_reg->smax_value = dst_reg->umax_value;
	पूर्ण
	/* We may learn something more from the var_off */
	__update_reg_bounds(dst_reg);
पूर्ण

अटल व्योम scalar32_min_max_or(काष्ठा bpf_reg_state *dst_reg,
				काष्ठा bpf_reg_state *src_reg)
अणु
	bool src_known = tnum_subreg_is_स्थिर(src_reg->var_off);
	bool dst_known = tnum_subreg_is_स्थिर(dst_reg->var_off);
	काष्ठा tnum var32_off = tnum_subreg(dst_reg->var_off);
	s32 smin_val = src_reg->s32_min_value;
	u32 umin_val = src_reg->u32_min_value;

	अगर (src_known && dst_known) अणु
		__mark_reg32_known(dst_reg, var32_off.value);
		वापस;
	पूर्ण

	/* We get our maximum from the var_off, and our minimum is the
	 * maximum of the opeअक्रमs' minima
	 */
	dst_reg->u32_min_value = max(dst_reg->u32_min_value, umin_val);
	dst_reg->u32_max_value = var32_off.value | var32_off.mask;
	अगर (dst_reg->s32_min_value < 0 || smin_val < 0) अणु
		/* Lose चिन्हित bounds when ORing negative numbers,
		 * ain't nobody got समय क्रम that.
		 */
		dst_reg->s32_min_value = S32_MIN;
		dst_reg->s32_max_value = S32_MAX;
	पूर्ण अन्यथा अणु
		/* ORing two positives gives a positive, so safe to
		 * cast result पूर्णांकo s64.
		 */
		dst_reg->s32_min_value = dst_reg->u32_min_value;
		dst_reg->s32_max_value = dst_reg->u32_max_value;
	पूर्ण
पूर्ण

अटल व्योम scalar_min_max_or(काष्ठा bpf_reg_state *dst_reg,
			      काष्ठा bpf_reg_state *src_reg)
अणु
	bool src_known = tnum_is_स्थिर(src_reg->var_off);
	bool dst_known = tnum_is_स्थिर(dst_reg->var_off);
	s64 smin_val = src_reg->smin_value;
	u64 umin_val = src_reg->umin_value;

	अगर (src_known && dst_known) अणु
		__mark_reg_known(dst_reg, dst_reg->var_off.value);
		वापस;
	पूर्ण

	/* We get our maximum from the var_off, and our minimum is the
	 * maximum of the opeअक्रमs' minima
	 */
	dst_reg->umin_value = max(dst_reg->umin_value, umin_val);
	dst_reg->umax_value = dst_reg->var_off.value | dst_reg->var_off.mask;
	अगर (dst_reg->smin_value < 0 || smin_val < 0) अणु
		/* Lose चिन्हित bounds when ORing negative numbers,
		 * ain't nobody got समय क्रम that.
		 */
		dst_reg->smin_value = S64_MIN;
		dst_reg->smax_value = S64_MAX;
	पूर्ण अन्यथा अणु
		/* ORing two positives gives a positive, so safe to
		 * cast result पूर्णांकo s64.
		 */
		dst_reg->smin_value = dst_reg->umin_value;
		dst_reg->smax_value = dst_reg->umax_value;
	पूर्ण
	/* We may learn something more from the var_off */
	__update_reg_bounds(dst_reg);
पूर्ण

अटल व्योम scalar32_min_max_xor(काष्ठा bpf_reg_state *dst_reg,
				 काष्ठा bpf_reg_state *src_reg)
अणु
	bool src_known = tnum_subreg_is_स्थिर(src_reg->var_off);
	bool dst_known = tnum_subreg_is_स्थिर(dst_reg->var_off);
	काष्ठा tnum var32_off = tnum_subreg(dst_reg->var_off);
	s32 smin_val = src_reg->s32_min_value;

	अगर (src_known && dst_known) अणु
		__mark_reg32_known(dst_reg, var32_off.value);
		वापस;
	पूर्ण

	/* We get both minimum and maximum from the var32_off. */
	dst_reg->u32_min_value = var32_off.value;
	dst_reg->u32_max_value = var32_off.value | var32_off.mask;

	अगर (dst_reg->s32_min_value >= 0 && smin_val >= 0) अणु
		/* XORing two positive sign numbers gives a positive,
		 * so safe to cast u32 result पूर्णांकo s32.
		 */
		dst_reg->s32_min_value = dst_reg->u32_min_value;
		dst_reg->s32_max_value = dst_reg->u32_max_value;
	पूर्ण अन्यथा अणु
		dst_reg->s32_min_value = S32_MIN;
		dst_reg->s32_max_value = S32_MAX;
	पूर्ण
पूर्ण

अटल व्योम scalar_min_max_xor(काष्ठा bpf_reg_state *dst_reg,
			       काष्ठा bpf_reg_state *src_reg)
अणु
	bool src_known = tnum_is_स्थिर(src_reg->var_off);
	bool dst_known = tnum_is_स्थिर(dst_reg->var_off);
	s64 smin_val = src_reg->smin_value;

	अगर (src_known && dst_known) अणु
		/* dst_reg->var_off.value has been updated earlier */
		__mark_reg_known(dst_reg, dst_reg->var_off.value);
		वापस;
	पूर्ण

	/* We get both minimum and maximum from the var_off. */
	dst_reg->umin_value = dst_reg->var_off.value;
	dst_reg->umax_value = dst_reg->var_off.value | dst_reg->var_off.mask;

	अगर (dst_reg->smin_value >= 0 && smin_val >= 0) अणु
		/* XORing two positive sign numbers gives a positive,
		 * so safe to cast u64 result पूर्णांकo s64.
		 */
		dst_reg->smin_value = dst_reg->umin_value;
		dst_reg->smax_value = dst_reg->umax_value;
	पूर्ण अन्यथा अणु
		dst_reg->smin_value = S64_MIN;
		dst_reg->smax_value = S64_MAX;
	पूर्ण

	__update_reg_bounds(dst_reg);
पूर्ण

अटल व्योम __scalar32_min_max_lsh(काष्ठा bpf_reg_state *dst_reg,
				   u64 umin_val, u64 umax_val)
अणु
	/* We lose all sign bit inक्रमmation (except what we can pick
	 * up from var_off)
	 */
	dst_reg->s32_min_value = S32_MIN;
	dst_reg->s32_max_value = S32_MAX;
	/* If we might shअगरt our top bit out, then we know nothing */
	अगर (umax_val > 31 || dst_reg->u32_max_value > 1ULL << (31 - umax_val)) अणु
		dst_reg->u32_min_value = 0;
		dst_reg->u32_max_value = U32_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->u32_min_value <<= umin_val;
		dst_reg->u32_max_value <<= umax_val;
	पूर्ण
पूर्ण

अटल व्योम scalar32_min_max_lsh(काष्ठा bpf_reg_state *dst_reg,
				 काष्ठा bpf_reg_state *src_reg)
अणु
	u32 umax_val = src_reg->u32_max_value;
	u32 umin_val = src_reg->u32_min_value;
	/* u32 alu operation will zext upper bits */
	काष्ठा tnum subreg = tnum_subreg(dst_reg->var_off);

	__scalar32_min_max_lsh(dst_reg, umin_val, umax_val);
	dst_reg->var_off = tnum_subreg(tnum_lshअगरt(subreg, umin_val));
	/* Not required but being careful mark reg64 bounds as unknown so
	 * that we are क्रमced to pick them up from tnum and zext later and
	 * अगर some path skips this step we are still safe.
	 */
	__mark_reg64_unbounded(dst_reg);
	__update_reg32_bounds(dst_reg);
पूर्ण

अटल व्योम __scalar64_min_max_lsh(काष्ठा bpf_reg_state *dst_reg,
				   u64 umin_val, u64 umax_val)
अणु
	/* Special हाल <<32 because it is a common compiler pattern to sign
	 * extend subreg by करोing <<32 s>>32. In this हाल अगर 32bit bounds are
	 * positive we know this shअगरt will also be positive so we can track
	 * bounds correctly. Otherwise we lose all sign bit inक्रमmation except
	 * what we can pick up from var_off. Perhaps we can generalize this
	 * later to shअगरts of any length.
	 */
	अगर (umin_val == 32 && umax_val == 32 && dst_reg->s32_max_value >= 0)
		dst_reg->smax_value = (s64)dst_reg->s32_max_value << 32;
	अन्यथा
		dst_reg->smax_value = S64_MAX;

	अगर (umin_val == 32 && umax_val == 32 && dst_reg->s32_min_value >= 0)
		dst_reg->smin_value = (s64)dst_reg->s32_min_value << 32;
	अन्यथा
		dst_reg->smin_value = S64_MIN;

	/* If we might shअगरt our top bit out, then we know nothing */
	अगर (dst_reg->umax_value > 1ULL << (63 - umax_val)) अणु
		dst_reg->umin_value = 0;
		dst_reg->umax_value = U64_MAX;
	पूर्ण अन्यथा अणु
		dst_reg->umin_value <<= umin_val;
		dst_reg->umax_value <<= umax_val;
	पूर्ण
पूर्ण

अटल व्योम scalar_min_max_lsh(काष्ठा bpf_reg_state *dst_reg,
			       काष्ठा bpf_reg_state *src_reg)
अणु
	u64 umax_val = src_reg->umax_value;
	u64 umin_val = src_reg->umin_value;

	/* scalar64 calc uses 32bit unshअगरted bounds so must be called first */
	__scalar64_min_max_lsh(dst_reg, umin_val, umax_val);
	__scalar32_min_max_lsh(dst_reg, umin_val, umax_val);

	dst_reg->var_off = tnum_lshअगरt(dst_reg->var_off, umin_val);
	/* We may learn something more from the var_off */
	__update_reg_bounds(dst_reg);
पूर्ण

अटल व्योम scalar32_min_max_rsh(काष्ठा bpf_reg_state *dst_reg,
				 काष्ठा bpf_reg_state *src_reg)
अणु
	काष्ठा tnum subreg = tnum_subreg(dst_reg->var_off);
	u32 umax_val = src_reg->u32_max_value;
	u32 umin_val = src_reg->u32_min_value;

	/* BPF_RSH is an अचिन्हित shअगरt.  If the value in dst_reg might
	 * be negative, then either:
	 * 1) src_reg might be zero, so the sign bit of the result is
	 *    unknown, so we lose our चिन्हित bounds
	 * 2) it's known negative, thus the अचिन्हित bounds capture the
	 *    चिन्हित bounds
	 * 3) the चिन्हित bounds cross zero, so they tell us nothing
	 *    about the result
	 * If the value in dst_reg is known nonnegative, then again the
	 * अचिन्हित bounds capture the चिन्हित bounds.
	 * Thus, in all हालs it suffices to blow away our चिन्हित bounds
	 * and rely on inferring new ones from the अचिन्हित bounds and
	 * var_off of the result.
	 */
	dst_reg->s32_min_value = S32_MIN;
	dst_reg->s32_max_value = S32_MAX;

	dst_reg->var_off = tnum_rshअगरt(subreg, umin_val);
	dst_reg->u32_min_value >>= umax_val;
	dst_reg->u32_max_value >>= umin_val;

	__mark_reg64_unbounded(dst_reg);
	__update_reg32_bounds(dst_reg);
पूर्ण

अटल व्योम scalar_min_max_rsh(काष्ठा bpf_reg_state *dst_reg,
			       काष्ठा bpf_reg_state *src_reg)
अणु
	u64 umax_val = src_reg->umax_value;
	u64 umin_val = src_reg->umin_value;

	/* BPF_RSH is an अचिन्हित shअगरt.  If the value in dst_reg might
	 * be negative, then either:
	 * 1) src_reg might be zero, so the sign bit of the result is
	 *    unknown, so we lose our चिन्हित bounds
	 * 2) it's known negative, thus the अचिन्हित bounds capture the
	 *    चिन्हित bounds
	 * 3) the चिन्हित bounds cross zero, so they tell us nothing
	 *    about the result
	 * If the value in dst_reg is known nonnegative, then again the
	 * अचिन्हित bounds capture the चिन्हित bounds.
	 * Thus, in all हालs it suffices to blow away our चिन्हित bounds
	 * and rely on inferring new ones from the अचिन्हित bounds and
	 * var_off of the result.
	 */
	dst_reg->smin_value = S64_MIN;
	dst_reg->smax_value = S64_MAX;
	dst_reg->var_off = tnum_rshअगरt(dst_reg->var_off, umin_val);
	dst_reg->umin_value >>= umax_val;
	dst_reg->umax_value >>= umin_val;

	/* Its not easy to operate on alu32 bounds here because it depends
	 * on bits being shअगरted in. Take easy way out and mark unbounded
	 * so we can recalculate later from tnum.
	 */
	__mark_reg32_unbounded(dst_reg);
	__update_reg_bounds(dst_reg);
पूर्ण

अटल व्योम scalar32_min_max_arsh(काष्ठा bpf_reg_state *dst_reg,
				  काष्ठा bpf_reg_state *src_reg)
अणु
	u64 umin_val = src_reg->u32_min_value;

	/* Upon reaching here, src_known is true and
	 * umax_val is equal to umin_val.
	 */
	dst_reg->s32_min_value = (u32)(((s32)dst_reg->s32_min_value) >> umin_val);
	dst_reg->s32_max_value = (u32)(((s32)dst_reg->s32_max_value) >> umin_val);

	dst_reg->var_off = tnum_arshअगरt(tnum_subreg(dst_reg->var_off), umin_val, 32);

	/* blow away the dst_reg umin_value/umax_value and rely on
	 * dst_reg var_off to refine the result.
	 */
	dst_reg->u32_min_value = 0;
	dst_reg->u32_max_value = U32_MAX;

	__mark_reg64_unbounded(dst_reg);
	__update_reg32_bounds(dst_reg);
पूर्ण

अटल व्योम scalar_min_max_arsh(काष्ठा bpf_reg_state *dst_reg,
				काष्ठा bpf_reg_state *src_reg)
अणु
	u64 umin_val = src_reg->umin_value;

	/* Upon reaching here, src_known is true and umax_val is equal
	 * to umin_val.
	 */
	dst_reg->smin_value >>= umin_val;
	dst_reg->smax_value >>= umin_val;

	dst_reg->var_off = tnum_arshअगरt(dst_reg->var_off, umin_val, 64);

	/* blow away the dst_reg umin_value/umax_value and rely on
	 * dst_reg var_off to refine the result.
	 */
	dst_reg->umin_value = 0;
	dst_reg->umax_value = U64_MAX;

	/* Its not easy to operate on alu32 bounds here because it depends
	 * on bits being shअगरted in from upper 32-bits. Take easy way out
	 * and mark unbounded so we can recalculate later from tnum.
	 */
	__mark_reg32_unbounded(dst_reg);
	__update_reg_bounds(dst_reg);
पूर्ण

/* WARNING: This function करोes calculations on 64-bit values, but the actual
 * execution may occur on 32-bit values. Thereक्रमe, things like bitshअगरts
 * need extra checks in the 32-bit हाल.
 */
अटल पूर्णांक adjust_scalar_min_max_vals(काष्ठा bpf_verअगरier_env *env,
				      काष्ठा bpf_insn *insn,
				      काष्ठा bpf_reg_state *dst_reg,
				      काष्ठा bpf_reg_state src_reg)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	u8 opcode = BPF_OP(insn->code);
	bool src_known;
	s64 smin_val, smax_val;
	u64 umin_val, umax_val;
	s32 s32_min_val, s32_max_val;
	u32 u32_min_val, u32_max_val;
	u64 insn_bitness = (BPF_CLASS(insn->code) == BPF_ALU64) ? 64 : 32;
	bool alu32 = (BPF_CLASS(insn->code) != BPF_ALU64);
	पूर्णांक ret;

	smin_val = src_reg.smin_value;
	smax_val = src_reg.smax_value;
	umin_val = src_reg.umin_value;
	umax_val = src_reg.umax_value;

	s32_min_val = src_reg.s32_min_value;
	s32_max_val = src_reg.s32_max_value;
	u32_min_val = src_reg.u32_min_value;
	u32_max_val = src_reg.u32_max_value;

	अगर (alu32) अणु
		src_known = tnum_subreg_is_स्थिर(src_reg.var_off);
		अगर ((src_known &&
		     (s32_min_val != s32_max_val || u32_min_val != u32_max_val)) ||
		    s32_min_val > s32_max_val || u32_min_val > u32_max_val) अणु
			/* Taपूर्णांक dst रेजिस्टर अगर offset had invalid bounds
			 * derived from e.g. dead branches.
			 */
			__mark_reg_unknown(env, dst_reg);
			वापस 0;
		पूर्ण
	पूर्ण अन्यथा अणु
		src_known = tnum_is_स्थिर(src_reg.var_off);
		अगर ((src_known &&
		     (smin_val != smax_val || umin_val != umax_val)) ||
		    smin_val > smax_val || umin_val > umax_val) अणु
			/* Taपूर्णांक dst रेजिस्टर अगर offset had invalid bounds
			 * derived from e.g. dead branches.
			 */
			__mark_reg_unknown(env, dst_reg);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (!src_known &&
	    opcode != BPF_ADD && opcode != BPF_SUB && opcode != BPF_AND) अणु
		__mark_reg_unknown(env, dst_reg);
		वापस 0;
	पूर्ण

	अगर (sanitize_needed(opcode)) अणु
		ret = sanitize_val_alu(env, insn);
		अगर (ret < 0)
			वापस sanitize_err(env, insn, ret, शून्य, शून्य);
	पूर्ण

	/* Calculate sign/अचिन्हित bounds and tnum क्रम alu32 and alu64 bit ops.
	 * There are two classes of inकाष्ठाions: The first class we track both
	 * alu32 and alu64 sign/अचिन्हित bounds independently this provides the
	 * greatest amount of precision when alu operations are mixed with jmp32
	 * operations. These operations are BPF_ADD, BPF_SUB, BPF_MUL, BPF_ADD,
	 * and BPF_OR. This is possible because these ops have fairly easy to
	 * understand and calculate behavior in both 32-bit and 64-bit alu ops.
	 * See alu32 verअगरier tests क्रम examples. The second class of
	 * operations, BPF_LSH, BPF_RSH, and BPF_ARSH, however are not so easy
	 * with regards to tracking sign/अचिन्हित bounds because the bits may
	 * cross subreg boundaries in the alu64 हाल. When this happens we mark
	 * the reg unbounded in the subreg bound space and use the resulting
	 * tnum to calculate an approximation of the sign/अचिन्हित bounds.
	 */
	चयन (opcode) अणु
	हाल BPF_ADD:
		scalar32_min_max_add(dst_reg, &src_reg);
		scalar_min_max_add(dst_reg, &src_reg);
		dst_reg->var_off = tnum_add(dst_reg->var_off, src_reg.var_off);
		अवरोध;
	हाल BPF_SUB:
		scalar32_min_max_sub(dst_reg, &src_reg);
		scalar_min_max_sub(dst_reg, &src_reg);
		dst_reg->var_off = tnum_sub(dst_reg->var_off, src_reg.var_off);
		अवरोध;
	हाल BPF_MUL:
		dst_reg->var_off = tnum_mul(dst_reg->var_off, src_reg.var_off);
		scalar32_min_max_mul(dst_reg, &src_reg);
		scalar_min_max_mul(dst_reg, &src_reg);
		अवरोध;
	हाल BPF_AND:
		dst_reg->var_off = tnum_and(dst_reg->var_off, src_reg.var_off);
		scalar32_min_max_and(dst_reg, &src_reg);
		scalar_min_max_and(dst_reg, &src_reg);
		अवरोध;
	हाल BPF_OR:
		dst_reg->var_off = tnum_or(dst_reg->var_off, src_reg.var_off);
		scalar32_min_max_or(dst_reg, &src_reg);
		scalar_min_max_or(dst_reg, &src_reg);
		अवरोध;
	हाल BPF_XOR:
		dst_reg->var_off = tnum_xor(dst_reg->var_off, src_reg.var_off);
		scalar32_min_max_xor(dst_reg, &src_reg);
		scalar_min_max_xor(dst_reg, &src_reg);
		अवरोध;
	हाल BPF_LSH:
		अगर (umax_val >= insn_bitness) अणु
			/* Shअगरts greater than 31 or 63 are undefined.
			 * This includes shअगरts by a negative number.
			 */
			mark_reg_unknown(env, regs, insn->dst_reg);
			अवरोध;
		पूर्ण
		अगर (alu32)
			scalar32_min_max_lsh(dst_reg, &src_reg);
		अन्यथा
			scalar_min_max_lsh(dst_reg, &src_reg);
		अवरोध;
	हाल BPF_RSH:
		अगर (umax_val >= insn_bitness) अणु
			/* Shअगरts greater than 31 or 63 are undefined.
			 * This includes shअगरts by a negative number.
			 */
			mark_reg_unknown(env, regs, insn->dst_reg);
			अवरोध;
		पूर्ण
		अगर (alu32)
			scalar32_min_max_rsh(dst_reg, &src_reg);
		अन्यथा
			scalar_min_max_rsh(dst_reg, &src_reg);
		अवरोध;
	हाल BPF_ARSH:
		अगर (umax_val >= insn_bitness) अणु
			/* Shअगरts greater than 31 or 63 are undefined.
			 * This includes shअगरts by a negative number.
			 */
			mark_reg_unknown(env, regs, insn->dst_reg);
			अवरोध;
		पूर्ण
		अगर (alu32)
			scalar32_min_max_arsh(dst_reg, &src_reg);
		अन्यथा
			scalar_min_max_arsh(dst_reg, &src_reg);
		अवरोध;
	शेष:
		mark_reg_unknown(env, regs, insn->dst_reg);
		अवरोध;
	पूर्ण

	/* ALU32 ops are zero extended पूर्णांकo 64bit रेजिस्टर */
	अगर (alu32)
		zext_32_to_64(dst_reg);

	__update_reg_bounds(dst_reg);
	__reg_deduce_bounds(dst_reg);
	__reg_bound_offset(dst_reg);
	वापस 0;
पूर्ण

/* Handles ALU ops other than BPF_END, BPF_NEG and BPF_MOV: computes new min/max
 * and var_off.
 */
अटल पूर्णांक adjust_reg_min_max_vals(काष्ठा bpf_verअगरier_env *env,
				   काष्ठा bpf_insn *insn)
अणु
	काष्ठा bpf_verअगरier_state *vstate = env->cur_state;
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	काष्ठा bpf_reg_state *regs = state->regs, *dst_reg, *src_reg;
	काष्ठा bpf_reg_state *ptr_reg = शून्य, off_reg = अणु0पूर्ण;
	u8 opcode = BPF_OP(insn->code);
	पूर्णांक err;

	dst_reg = &regs[insn->dst_reg];
	src_reg = शून्य;
	अगर (dst_reg->type != SCALAR_VALUE)
		ptr_reg = dst_reg;
	अन्यथा
		/* Make sure ID is cleared otherwise dst_reg min/max could be
		 * incorrectly propagated पूर्णांकo other रेजिस्टरs by find_equal_scalars()
		 */
		dst_reg->id = 0;
	अगर (BPF_SRC(insn->code) == BPF_X) अणु
		src_reg = &regs[insn->src_reg];
		अगर (src_reg->type != SCALAR_VALUE) अणु
			अगर (dst_reg->type != SCALAR_VALUE) अणु
				/* Combining two poपूर्णांकers by any ALU op yields
				 * an arbitrary scalar. Disallow all math except
				 * poपूर्णांकer subtraction
				 */
				अगर (opcode == BPF_SUB && env->allow_ptr_leaks) अणु
					mark_reg_unknown(env, regs, insn->dst_reg);
					वापस 0;
				पूर्ण
				verbose(env, "R%d pointer %s pointer prohibited\n",
					insn->dst_reg,
					bpf_alu_string[opcode >> 4]);
				वापस -EACCES;
			पूर्ण अन्यथा अणु
				/* scalar += poपूर्णांकer
				 * This is legal, but we have to reverse our
				 * src/dest handling in computing the range
				 */
				err = mark_chain_precision(env, insn->dst_reg);
				अगर (err)
					वापस err;
				वापस adjust_ptr_min_max_vals(env, insn,
							       src_reg, dst_reg);
			पूर्ण
		पूर्ण अन्यथा अगर (ptr_reg) अणु
			/* poपूर्णांकer += scalar */
			err = mark_chain_precision(env, insn->src_reg);
			अगर (err)
				वापस err;
			वापस adjust_ptr_min_max_vals(env, insn,
						       dst_reg, src_reg);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Pretend the src is a reg with a known value, since we only
		 * need to be able to पढ़ो from this state.
		 */
		off_reg.type = SCALAR_VALUE;
		__mark_reg_known(&off_reg, insn->imm);
		src_reg = &off_reg;
		अगर (ptr_reg) /* poपूर्णांकer += K */
			वापस adjust_ptr_min_max_vals(env, insn,
						       ptr_reg, src_reg);
	पूर्ण

	/* Got here implies adding two SCALAR_VALUEs */
	अगर (WARN_ON_ONCE(ptr_reg)) अणु
		prपूर्णांक_verअगरier_state(env, state);
		verbose(env, "verifier internal error: unexpected ptr_reg\n");
		वापस -EINVAL;
	पूर्ण
	अगर (WARN_ON(!src_reg)) अणु
		prपूर्णांक_verअगरier_state(env, state);
		verbose(env, "verifier internal error: no src_reg\n");
		वापस -EINVAL;
	पूर्ण
	वापस adjust_scalar_min_max_vals(env, insn, dst_reg, *src_reg);
पूर्ण

/* check validity of 32-bit and 64-bit arithmetic operations */
अटल पूर्णांक check_alu_op(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	u8 opcode = BPF_OP(insn->code);
	पूर्णांक err;

	अगर (opcode == BPF_END || opcode == BPF_NEG) अणु
		अगर (opcode == BPF_NEG) अणु
			अगर (BPF_SRC(insn->code) != 0 ||
			    insn->src_reg != BPF_REG_0 ||
			    insn->off != 0 || insn->imm != 0) अणु
				verbose(env, "BPF_NEG uses reserved fields\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (insn->src_reg != BPF_REG_0 || insn->off != 0 ||
			    (insn->imm != 16 && insn->imm != 32 && insn->imm != 64) ||
			    BPF_CLASS(insn->code) == BPF_ALU64) अणु
				verbose(env, "BPF_END uses reserved fields\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* check src opeअक्रम */
		err = check_reg_arg(env, insn->dst_reg, SRC_OP);
		अगर (err)
			वापस err;

		अगर (is_poपूर्णांकer_value(env, insn->dst_reg)) अणु
			verbose(env, "R%d pointer arithmetic prohibited\n",
				insn->dst_reg);
			वापस -EACCES;
		पूर्ण

		/* check dest opeअक्रम */
		err = check_reg_arg(env, insn->dst_reg, DST_OP);
		अगर (err)
			वापस err;

	पूर्ण अन्यथा अगर (opcode == BPF_MOV) अणु

		अगर (BPF_SRC(insn->code) == BPF_X) अणु
			अगर (insn->imm != 0 || insn->off != 0) अणु
				verbose(env, "BPF_MOV uses reserved fields\n");
				वापस -EINVAL;
			पूर्ण

			/* check src opeअक्रम */
			err = check_reg_arg(env, insn->src_reg, SRC_OP);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			अगर (insn->src_reg != BPF_REG_0 || insn->off != 0) अणु
				verbose(env, "BPF_MOV uses reserved fields\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* check dest opeअक्रम, mark as required later */
		err = check_reg_arg(env, insn->dst_reg, DST_OP_NO_MARK);
		अगर (err)
			वापस err;

		अगर (BPF_SRC(insn->code) == BPF_X) अणु
			काष्ठा bpf_reg_state *src_reg = regs + insn->src_reg;
			काष्ठा bpf_reg_state *dst_reg = regs + insn->dst_reg;

			अगर (BPF_CLASS(insn->code) == BPF_ALU64) अणु
				/* हाल: R1 = R2
				 * copy रेजिस्टर state to dest reg
				 */
				अगर (src_reg->type == SCALAR_VALUE && !src_reg->id)
					/* Assign src and dst रेजिस्टरs the same ID
					 * that will be used by find_equal_scalars()
					 * to propagate min/max range.
					 */
					src_reg->id = ++env->id_gen;
				*dst_reg = *src_reg;
				dst_reg->live |= REG_LIVE_WRITTEN;
				dst_reg->subreg_def = DEF_NOT_SUBREG;
			पूर्ण अन्यथा अणु
				/* R1 = (u32) R2 */
				अगर (is_poपूर्णांकer_value(env, insn->src_reg)) अणु
					verbose(env,
						"R%d partial copy of pointer\n",
						insn->src_reg);
					वापस -EACCES;
				पूर्ण अन्यथा अगर (src_reg->type == SCALAR_VALUE) अणु
					*dst_reg = *src_reg;
					/* Make sure ID is cleared otherwise
					 * dst_reg min/max could be incorrectly
					 * propagated पूर्णांकo src_reg by find_equal_scalars()
					 */
					dst_reg->id = 0;
					dst_reg->live |= REG_LIVE_WRITTEN;
					dst_reg->subreg_def = env->insn_idx + 1;
				पूर्ण अन्यथा अणु
					mark_reg_unknown(env, regs,
							 insn->dst_reg);
				पूर्ण
				zext_32_to_64(dst_reg);
			पूर्ण
		पूर्ण अन्यथा अणु
			/* हाल: R = imm
			 * remember the value we stored पूर्णांकo this reg
			 */
			/* clear any state __mark_reg_known करोesn't set */
			mark_reg_unknown(env, regs, insn->dst_reg);
			regs[insn->dst_reg].type = SCALAR_VALUE;
			अगर (BPF_CLASS(insn->code) == BPF_ALU64) अणु
				__mark_reg_known(regs + insn->dst_reg,
						 insn->imm);
			पूर्ण अन्यथा अणु
				__mark_reg_known(regs + insn->dst_reg,
						 (u32)insn->imm);
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (opcode > BPF_END) अणु
		verbose(env, "invalid BPF_ALU opcode %x\n", opcode);
		वापस -EINVAL;

	पूर्ण अन्यथा अणु	/* all other ALU ops: and, sub, xor, add, ... */

		अगर (BPF_SRC(insn->code) == BPF_X) अणु
			अगर (insn->imm != 0 || insn->off != 0) अणु
				verbose(env, "BPF_ALU uses reserved fields\n");
				वापस -EINVAL;
			पूर्ण
			/* check src1 opeअक्रम */
			err = check_reg_arg(env, insn->src_reg, SRC_OP);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			अगर (insn->src_reg != BPF_REG_0 || insn->off != 0) अणु
				verbose(env, "BPF_ALU uses reserved fields\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* check src2 opeअक्रम */
		err = check_reg_arg(env, insn->dst_reg, SRC_OP);
		अगर (err)
			वापस err;

		अगर ((opcode == BPF_MOD || opcode == BPF_DIV) &&
		    BPF_SRC(insn->code) == BPF_K && insn->imm == 0) अणु
			verbose(env, "div by zero\n");
			वापस -EINVAL;
		पूर्ण

		अगर ((opcode == BPF_LSH || opcode == BPF_RSH ||
		     opcode == BPF_ARSH) && BPF_SRC(insn->code) == BPF_K) अणु
			पूर्णांक size = BPF_CLASS(insn->code) == BPF_ALU64 ? 64 : 32;

			अगर (insn->imm < 0 || insn->imm >= size) अणु
				verbose(env, "invalid shift %d\n", insn->imm);
				वापस -EINVAL;
			पूर्ण
		पूर्ण

		/* check dest opeअक्रम */
		err = check_reg_arg(env, insn->dst_reg, DST_OP_NO_MARK);
		अगर (err)
			वापस err;

		वापस adjust_reg_min_max_vals(env, insn);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __find_good_pkt_poपूर्णांकers(काष्ठा bpf_func_state *state,
				     काष्ठा bpf_reg_state *dst_reg,
				     क्रमागत bpf_reg_type type, पूर्णांक new_range)
अणु
	काष्ठा bpf_reg_state *reg;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BPF_REG; i++) अणु
		reg = &state->regs[i];
		अगर (reg->type == type && reg->id == dst_reg->id)
			/* keep the maximum range alपढ़ोy checked */
			reg->range = max(reg->range, new_range);
	पूर्ण

	bpf_क्रम_each_spilled_reg(i, state, reg) अणु
		अगर (!reg)
			जारी;
		अगर (reg->type == type && reg->id == dst_reg->id)
			reg->range = max(reg->range, new_range);
	पूर्ण
पूर्ण

अटल व्योम find_good_pkt_poपूर्णांकers(काष्ठा bpf_verअगरier_state *vstate,
				   काष्ठा bpf_reg_state *dst_reg,
				   क्रमागत bpf_reg_type type,
				   bool range_right_खोलो)
अणु
	पूर्णांक new_range, i;

	अगर (dst_reg->off < 0 ||
	    (dst_reg->off == 0 && range_right_खोलो))
		/* This करोesn't give us any range */
		वापस;

	अगर (dst_reg->umax_value > MAX_PACKET_OFF ||
	    dst_reg->umax_value + dst_reg->off > MAX_PACKET_OFF)
		/* Risk of overflow.  For instance, ptr + (1<<63) may be less
		 * than pkt_end, but that's because it's also less than pkt.
		 */
		वापस;

	new_range = dst_reg->off;
	अगर (range_right_खोलो)
		new_range--;

	/* Examples क्रम रेजिस्टर markings:
	 *
	 * pkt_data in dst रेजिस्टर:
	 *
	 *   r2 = r3;
	 *   r2 += 8;
	 *   अगर (r2 > pkt_end) जाओ <handle exception>
	 *   <access okay>
	 *
	 *   r2 = r3;
	 *   r2 += 8;
	 *   अगर (r2 < pkt_end) जाओ <access okay>
	 *   <handle exception>
	 *
	 *   Where:
	 *     r2 == dst_reg, pkt_end == src_reg
	 *     r2=pkt(id=n,off=8,r=0)
	 *     r3=pkt(id=n,off=0,r=0)
	 *
	 * pkt_data in src रेजिस्टर:
	 *
	 *   r2 = r3;
	 *   r2 += 8;
	 *   अगर (pkt_end >= r2) जाओ <access okay>
	 *   <handle exception>
	 *
	 *   r2 = r3;
	 *   r2 += 8;
	 *   अगर (pkt_end <= r2) जाओ <handle exception>
	 *   <access okay>
	 *
	 *   Where:
	 *     pkt_end == dst_reg, r2 == src_reg
	 *     r2=pkt(id=n,off=8,r=0)
	 *     r3=pkt(id=n,off=0,r=0)
	 *
	 * Find रेजिस्टर r3 and mark its range as r3=pkt(id=n,off=0,r=8)
	 * or r3=pkt(id=n,off=0,r=8-1), so that range of bytes [r3, r3 + 8)
	 * and [r3, r3 + 8-1) respectively is safe to access depending on
	 * the check.
	 */

	/* If our ids match, then we must have the same max_value.  And we
	 * करोn't care about the other reg's fixed offset, since if it's too big
	 * the range won't allow anything.
	 * dst_reg->off is known < MAX_PACKET_OFF, thereक्रमe it fits in a u16.
	 */
	क्रम (i = 0; i <= vstate->curframe; i++)
		__find_good_pkt_poपूर्णांकers(vstate->frame[i], dst_reg, type,
					 new_range);
पूर्ण

अटल पूर्णांक is_branch32_taken(काष्ठा bpf_reg_state *reg, u32 val, u8 opcode)
अणु
	काष्ठा tnum subreg = tnum_subreg(reg->var_off);
	s32 sval = (s32)val;

	चयन (opcode) अणु
	हाल BPF_JEQ:
		अगर (tnum_is_स्थिर(subreg))
			वापस !!tnum_equals_स्थिर(subreg, val);
		अवरोध;
	हाल BPF_JNE:
		अगर (tnum_is_स्थिर(subreg))
			वापस !tnum_equals_स्थिर(subreg, val);
		अवरोध;
	हाल BPF_JSET:
		अगर ((~subreg.mask & subreg.value) & val)
			वापस 1;
		अगर (!((subreg.mask | subreg.value) & val))
			वापस 0;
		अवरोध;
	हाल BPF_JGT:
		अगर (reg->u32_min_value > val)
			वापस 1;
		अन्यथा अगर (reg->u32_max_value <= val)
			वापस 0;
		अवरोध;
	हाल BPF_JSGT:
		अगर (reg->s32_min_value > sval)
			वापस 1;
		अन्यथा अगर (reg->s32_max_value <= sval)
			वापस 0;
		अवरोध;
	हाल BPF_JLT:
		अगर (reg->u32_max_value < val)
			वापस 1;
		अन्यथा अगर (reg->u32_min_value >= val)
			वापस 0;
		अवरोध;
	हाल BPF_JSLT:
		अगर (reg->s32_max_value < sval)
			वापस 1;
		अन्यथा अगर (reg->s32_min_value >= sval)
			वापस 0;
		अवरोध;
	हाल BPF_JGE:
		अगर (reg->u32_min_value >= val)
			वापस 1;
		अन्यथा अगर (reg->u32_max_value < val)
			वापस 0;
		अवरोध;
	हाल BPF_JSGE:
		अगर (reg->s32_min_value >= sval)
			वापस 1;
		अन्यथा अगर (reg->s32_max_value < sval)
			वापस 0;
		अवरोध;
	हाल BPF_JLE:
		अगर (reg->u32_max_value <= val)
			वापस 1;
		अन्यथा अगर (reg->u32_min_value > val)
			वापस 0;
		अवरोध;
	हाल BPF_JSLE:
		अगर (reg->s32_max_value <= sval)
			वापस 1;
		अन्यथा अगर (reg->s32_min_value > sval)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण


अटल पूर्णांक is_branch64_taken(काष्ठा bpf_reg_state *reg, u64 val, u8 opcode)
अणु
	s64 sval = (s64)val;

	चयन (opcode) अणु
	हाल BPF_JEQ:
		अगर (tnum_is_स्थिर(reg->var_off))
			वापस !!tnum_equals_स्थिर(reg->var_off, val);
		अवरोध;
	हाल BPF_JNE:
		अगर (tnum_is_स्थिर(reg->var_off))
			वापस !tnum_equals_स्थिर(reg->var_off, val);
		अवरोध;
	हाल BPF_JSET:
		अगर ((~reg->var_off.mask & reg->var_off.value) & val)
			वापस 1;
		अगर (!((reg->var_off.mask | reg->var_off.value) & val))
			वापस 0;
		अवरोध;
	हाल BPF_JGT:
		अगर (reg->umin_value > val)
			वापस 1;
		अन्यथा अगर (reg->umax_value <= val)
			वापस 0;
		अवरोध;
	हाल BPF_JSGT:
		अगर (reg->smin_value > sval)
			वापस 1;
		अन्यथा अगर (reg->smax_value <= sval)
			वापस 0;
		अवरोध;
	हाल BPF_JLT:
		अगर (reg->umax_value < val)
			वापस 1;
		अन्यथा अगर (reg->umin_value >= val)
			वापस 0;
		अवरोध;
	हाल BPF_JSLT:
		अगर (reg->smax_value < sval)
			वापस 1;
		अन्यथा अगर (reg->smin_value >= sval)
			वापस 0;
		अवरोध;
	हाल BPF_JGE:
		अगर (reg->umin_value >= val)
			वापस 1;
		अन्यथा अगर (reg->umax_value < val)
			वापस 0;
		अवरोध;
	हाल BPF_JSGE:
		अगर (reg->smin_value >= sval)
			वापस 1;
		अन्यथा अगर (reg->smax_value < sval)
			वापस 0;
		अवरोध;
	हाल BPF_JLE:
		अगर (reg->umax_value <= val)
			वापस 1;
		अन्यथा अगर (reg->umin_value > val)
			वापस 0;
		अवरोध;
	हाल BPF_JSLE:
		अगर (reg->smax_value <= sval)
			वापस 1;
		अन्यथा अगर (reg->smin_value > sval)
			वापस 0;
		अवरोध;
	पूर्ण

	वापस -1;
पूर्ण

/* compute branch direction of the expression "if (reg opcode val) goto target;"
 * and वापस:
 *  1 - branch will be taken and "goto target" will be executed
 *  0 - branch will not be taken and fall-through to next insn
 * -1 - unknown. Example: "if (reg < 5)" is unknown when रेजिस्टर value
 *      range [0,10]
 */
अटल पूर्णांक is_branch_taken(काष्ठा bpf_reg_state *reg, u64 val, u8 opcode,
			   bool is_jmp32)
अणु
	अगर (__is_poपूर्णांकer_value(false, reg)) अणु
		अगर (!reg_type_not_null(reg->type))
			वापस -1;

		/* If poपूर्णांकer is valid tests against zero will fail so we can
		 * use this to direct branch taken.
		 */
		अगर (val != 0)
			वापस -1;

		चयन (opcode) अणु
		हाल BPF_JEQ:
			वापस 0;
		हाल BPF_JNE:
			वापस 1;
		शेष:
			वापस -1;
		पूर्ण
	पूर्ण

	अगर (is_jmp32)
		वापस is_branch32_taken(reg, val, opcode);
	वापस is_branch64_taken(reg, val, opcode);
पूर्ण

अटल पूर्णांक flip_opcode(u32 opcode)
अणु
	/* How can we transक्रमm "a <op> b" पूर्णांकo "b <op> a"? */
	अटल स्थिर u8 opcode_flip[16] = अणु
		/* these stay the same */
		[BPF_JEQ  >> 4] = BPF_JEQ,
		[BPF_JNE  >> 4] = BPF_JNE,
		[BPF_JSET >> 4] = BPF_JSET,
		/* these swap "lesser" and "greater" (L and G in the opcodes) */
		[BPF_JGE  >> 4] = BPF_JLE,
		[BPF_JGT  >> 4] = BPF_JLT,
		[BPF_JLE  >> 4] = BPF_JGE,
		[BPF_JLT  >> 4] = BPF_JGT,
		[BPF_JSGE >> 4] = BPF_JSLE,
		[BPF_JSGT >> 4] = BPF_JSLT,
		[BPF_JSLE >> 4] = BPF_JSGE,
		[BPF_JSLT >> 4] = BPF_JSGT
	पूर्ण;
	वापस opcode_flip[opcode >> 4];
पूर्ण

अटल पूर्णांक is_pkt_ptr_branch_taken(काष्ठा bpf_reg_state *dst_reg,
				   काष्ठा bpf_reg_state *src_reg,
				   u8 opcode)
अणु
	काष्ठा bpf_reg_state *pkt;

	अगर (src_reg->type == PTR_TO_PACKET_END) अणु
		pkt = dst_reg;
	पूर्ण अन्यथा अगर (dst_reg->type == PTR_TO_PACKET_END) अणु
		pkt = src_reg;
		opcode = flip_opcode(opcode);
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	अगर (pkt->range >= 0)
		वापस -1;

	चयन (opcode) अणु
	हाल BPF_JLE:
		/* pkt <= pkt_end */
		fallthrough;
	हाल BPF_JGT:
		/* pkt > pkt_end */
		अगर (pkt->range == BEYOND_PKT_END)
			/* pkt has at last one extra byte beyond pkt_end */
			वापस opcode == BPF_JGT;
		अवरोध;
	हाल BPF_JLT:
		/* pkt < pkt_end */
		fallthrough;
	हाल BPF_JGE:
		/* pkt >= pkt_end */
		अगर (pkt->range == BEYOND_PKT_END || pkt->range == AT_PKT_END)
			वापस opcode == BPF_JGE;
		अवरोध;
	पूर्ण
	वापस -1;
पूर्ण

/* Adjusts the रेजिस्टर min/max values in the हाल that the dst_reg is the
 * variable रेजिस्टर that we are working on, and src_reg is a स्थिरant or we're
 * simply करोing a BPF_K check.
 * In JEQ/JNE हालs we also adjust the var_off values.
 */
अटल व्योम reg_set_min_max(काष्ठा bpf_reg_state *true_reg,
			    काष्ठा bpf_reg_state *false_reg,
			    u64 val, u32 val32,
			    u8 opcode, bool is_jmp32)
अणु
	काष्ठा tnum false_32off = tnum_subreg(false_reg->var_off);
	काष्ठा tnum false_64off = false_reg->var_off;
	काष्ठा tnum true_32off = tnum_subreg(true_reg->var_off);
	काष्ठा tnum true_64off = true_reg->var_off;
	s64 sval = (s64)val;
	s32 sval32 = (s32)val32;

	/* If the dst_reg is a poपूर्णांकer, we can't learn anything about its
	 * variable offset from the compare (unless src_reg were a poपूर्णांकer पूर्णांकo
	 * the same object, but we करोn't bother with that.
	 * Since false_reg and true_reg have the same type by स्थिरruction, we
	 * only need to check one of them क्रम poपूर्णांकerness.
	 */
	अगर (__is_poपूर्णांकer_value(false, false_reg))
		वापस;

	चयन (opcode) अणु
	हाल BPF_JEQ:
	हाल BPF_JNE:
	अणु
		काष्ठा bpf_reg_state *reg =
			opcode == BPF_JEQ ? true_reg : false_reg;

		/* JEQ/JNE comparison करोesn't change the रेजिस्टर equivalence.
		 * r1 = r2;
		 * अगर (r1 == 42) जाओ label;
		 * ...
		 * label: // here both r1 and r2 are known to be 42.
		 *
		 * Hence when marking रेजिस्टर as known preserve it's ID.
		 */
		अगर (is_jmp32)
			__mark_reg32_known(reg, val32);
		अन्यथा
			___mark_reg_known(reg, val);
		अवरोध;
	पूर्ण
	हाल BPF_JSET:
		अगर (is_jmp32) अणु
			false_32off = tnum_and(false_32off, tnum_स्थिर(~val32));
			अगर (is_घातer_of_2(val32))
				true_32off = tnum_or(true_32off,
						     tnum_स्थिर(val32));
		पूर्ण अन्यथा अणु
			false_64off = tnum_and(false_64off, tnum_स्थिर(~val));
			अगर (is_घातer_of_2(val))
				true_64off = tnum_or(true_64off,
						     tnum_स्थिर(val));
		पूर्ण
		अवरोध;
	हाल BPF_JGE:
	हाल BPF_JGT:
	अणु
		अगर (is_jmp32) अणु
			u32 false_umax = opcode == BPF_JGT ? val32  : val32 - 1;
			u32 true_umin = opcode == BPF_JGT ? val32 + 1 : val32;

			false_reg->u32_max_value = min(false_reg->u32_max_value,
						       false_umax);
			true_reg->u32_min_value = max(true_reg->u32_min_value,
						      true_umin);
		पूर्ण अन्यथा अणु
			u64 false_umax = opcode == BPF_JGT ? val    : val - 1;
			u64 true_umin = opcode == BPF_JGT ? val + 1 : val;

			false_reg->umax_value = min(false_reg->umax_value, false_umax);
			true_reg->umin_value = max(true_reg->umin_value, true_umin);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BPF_JSGE:
	हाल BPF_JSGT:
	अणु
		अगर (is_jmp32) अणु
			s32 false_smax = opcode == BPF_JSGT ? sval32    : sval32 - 1;
			s32 true_smin = opcode == BPF_JSGT ? sval32 + 1 : sval32;

			false_reg->s32_max_value = min(false_reg->s32_max_value, false_smax);
			true_reg->s32_min_value = max(true_reg->s32_min_value, true_smin);
		पूर्ण अन्यथा अणु
			s64 false_smax = opcode == BPF_JSGT ? sval    : sval - 1;
			s64 true_smin = opcode == BPF_JSGT ? sval + 1 : sval;

			false_reg->smax_value = min(false_reg->smax_value, false_smax);
			true_reg->smin_value = max(true_reg->smin_value, true_smin);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BPF_JLE:
	हाल BPF_JLT:
	अणु
		अगर (is_jmp32) अणु
			u32 false_umin = opcode == BPF_JLT ? val32  : val32 + 1;
			u32 true_umax = opcode == BPF_JLT ? val32 - 1 : val32;

			false_reg->u32_min_value = max(false_reg->u32_min_value,
						       false_umin);
			true_reg->u32_max_value = min(true_reg->u32_max_value,
						      true_umax);
		पूर्ण अन्यथा अणु
			u64 false_umin = opcode == BPF_JLT ? val    : val + 1;
			u64 true_umax = opcode == BPF_JLT ? val - 1 : val;

			false_reg->umin_value = max(false_reg->umin_value, false_umin);
			true_reg->umax_value = min(true_reg->umax_value, true_umax);
		पूर्ण
		अवरोध;
	पूर्ण
	हाल BPF_JSLE:
	हाल BPF_JSLT:
	अणु
		अगर (is_jmp32) अणु
			s32 false_smin = opcode == BPF_JSLT ? sval32    : sval32 + 1;
			s32 true_smax = opcode == BPF_JSLT ? sval32 - 1 : sval32;

			false_reg->s32_min_value = max(false_reg->s32_min_value, false_smin);
			true_reg->s32_max_value = min(true_reg->s32_max_value, true_smax);
		पूर्ण अन्यथा अणु
			s64 false_smin = opcode == BPF_JSLT ? sval    : sval + 1;
			s64 true_smax = opcode == BPF_JSLT ? sval - 1 : sval;

			false_reg->smin_value = max(false_reg->smin_value, false_smin);
			true_reg->smax_value = min(true_reg->smax_value, true_smax);
		पूर्ण
		अवरोध;
	पूर्ण
	शेष:
		वापस;
	पूर्ण

	अगर (is_jmp32) अणु
		false_reg->var_off = tnum_or(tnum_clear_subreg(false_64off),
					     tnum_subreg(false_32off));
		true_reg->var_off = tnum_or(tnum_clear_subreg(true_64off),
					    tnum_subreg(true_32off));
		__reg_combine_32_पूर्णांकo_64(false_reg);
		__reg_combine_32_पूर्णांकo_64(true_reg);
	पूर्ण अन्यथा अणु
		false_reg->var_off = false_64off;
		true_reg->var_off = true_64off;
		__reg_combine_64_पूर्णांकo_32(false_reg);
		__reg_combine_64_पूर्णांकo_32(true_reg);
	पूर्ण
पूर्ण

/* Same as above, but क्रम the हाल that dst_reg holds a स्थिरant and src_reg is
 * the variable reg.
 */
अटल व्योम reg_set_min_max_inv(काष्ठा bpf_reg_state *true_reg,
				काष्ठा bpf_reg_state *false_reg,
				u64 val, u32 val32,
				u8 opcode, bool is_jmp32)
अणु
	opcode = flip_opcode(opcode);
	/* This uses zero as "not present in table"; luckily the zero opcode,
	 * BPF_JA, can't get here.
	 */
	अगर (opcode)
		reg_set_min_max(true_reg, false_reg, val, val32, opcode, is_jmp32);
पूर्ण

/* Regs are known to be equal, so पूर्णांकersect their min/max/var_off */
अटल व्योम __reg_combine_min_max(काष्ठा bpf_reg_state *src_reg,
				  काष्ठा bpf_reg_state *dst_reg)
अणु
	src_reg->umin_value = dst_reg->umin_value = max(src_reg->umin_value,
							dst_reg->umin_value);
	src_reg->umax_value = dst_reg->umax_value = min(src_reg->umax_value,
							dst_reg->umax_value);
	src_reg->smin_value = dst_reg->smin_value = max(src_reg->smin_value,
							dst_reg->smin_value);
	src_reg->smax_value = dst_reg->smax_value = min(src_reg->smax_value,
							dst_reg->smax_value);
	src_reg->var_off = dst_reg->var_off = tnum_पूर्णांकersect(src_reg->var_off,
							     dst_reg->var_off);
	/* We might have learned new bounds from the var_off. */
	__update_reg_bounds(src_reg);
	__update_reg_bounds(dst_reg);
	/* We might have learned something about the sign bit. */
	__reg_deduce_bounds(src_reg);
	__reg_deduce_bounds(dst_reg);
	/* We might have learned some bits from the bounds. */
	__reg_bound_offset(src_reg);
	__reg_bound_offset(dst_reg);
	/* Intersecting with the old var_off might have improved our bounds
	 * slightly.  e.g. अगर umax was 0x7f...f and var_off was (0; 0xf...fc),
	 * then new var_off is (0; 0x7f...fc) which improves our umax.
	 */
	__update_reg_bounds(src_reg);
	__update_reg_bounds(dst_reg);
पूर्ण

अटल व्योम reg_combine_min_max(काष्ठा bpf_reg_state *true_src,
				काष्ठा bpf_reg_state *true_dst,
				काष्ठा bpf_reg_state *false_src,
				काष्ठा bpf_reg_state *false_dst,
				u8 opcode)
अणु
	चयन (opcode) अणु
	हाल BPF_JEQ:
		__reg_combine_min_max(true_src, true_dst);
		अवरोध;
	हाल BPF_JNE:
		__reg_combine_min_max(false_src, false_dst);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mark_ptr_or_null_reg(काष्ठा bpf_func_state *state,
				 काष्ठा bpf_reg_state *reg, u32 id,
				 bool is_null)
अणु
	अगर (reg_type_may_be_null(reg->type) && reg->id == id &&
	    !WARN_ON_ONCE(!reg->id)) अणु
		/* Old offset (both fixed and variable parts) should
		 * have been known-zero, because we करोn't allow poपूर्णांकer
		 * arithmetic on poपूर्णांकers that might be शून्य.
		 */
		अगर (WARN_ON_ONCE(reg->smin_value || reg->smax_value ||
				 !tnum_equals_स्थिर(reg->var_off, 0) ||
				 reg->off)) अणु
			__mark_reg_known_zero(reg);
			reg->off = 0;
		पूर्ण
		अगर (is_null) अणु
			reg->type = SCALAR_VALUE;
			/* We करोn't need id and ref_obj_id from this poपूर्णांक
			 * onwards anymore, thus we should better reset it,
			 * so that state pruning has chances to take effect.
			 */
			reg->id = 0;
			reg->ref_obj_id = 0;

			वापस;
		पूर्ण

		mark_ptr_not_null_reg(reg);

		अगर (!reg_may_poपूर्णांक_to_spin_lock(reg)) अणु
			/* For not-शून्य ptr, reg->ref_obj_id will be reset
			 * in release_reg_references().
			 *
			 * reg->id is still used by spin_lock ptr. Other
			 * than spin_lock ptr type, reg->id can be reset.
			 */
			reg->id = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __mark_ptr_or_null_regs(काष्ठा bpf_func_state *state, u32 id,
				    bool is_null)
अणु
	काष्ठा bpf_reg_state *reg;
	पूर्णांक i;

	क्रम (i = 0; i < MAX_BPF_REG; i++)
		mark_ptr_or_null_reg(state, &state->regs[i], id, is_null);

	bpf_क्रम_each_spilled_reg(i, state, reg) अणु
		अगर (!reg)
			जारी;
		mark_ptr_or_null_reg(state, reg, id, is_null);
	पूर्ण
पूर्ण

/* The logic is similar to find_good_pkt_poपूर्णांकers(), both could eventually
 * be folded together at some poपूर्णांक.
 */
अटल व्योम mark_ptr_or_null_regs(काष्ठा bpf_verअगरier_state *vstate, u32 regno,
				  bool is_null)
अणु
	काष्ठा bpf_func_state *state = vstate->frame[vstate->curframe];
	काष्ठा bpf_reg_state *regs = state->regs;
	u32 ref_obj_id = regs[regno].ref_obj_id;
	u32 id = regs[regno].id;
	पूर्णांक i;

	अगर (ref_obj_id && ref_obj_id == id && is_null)
		/* regs[regno] is in the " == NULL" branch.
		 * No one could have मुक्तd the reference state beक्रमe
		 * करोing the शून्य check.
		 */
		WARN_ON_ONCE(release_reference_state(state, id));

	क्रम (i = 0; i <= vstate->curframe; i++)
		__mark_ptr_or_null_regs(vstate->frame[i], id, is_null);
पूर्ण

अटल bool try_match_pkt_poपूर्णांकers(स्थिर काष्ठा bpf_insn *insn,
				   काष्ठा bpf_reg_state *dst_reg,
				   काष्ठा bpf_reg_state *src_reg,
				   काष्ठा bpf_verअगरier_state *this_branch,
				   काष्ठा bpf_verअगरier_state *other_branch)
अणु
	अगर (BPF_SRC(insn->code) != BPF_X)
		वापस false;

	/* Poपूर्णांकers are always 64-bit. */
	अगर (BPF_CLASS(insn->code) == BPF_JMP32)
		वापस false;

	चयन (BPF_OP(insn->code)) अणु
	हाल BPF_JGT:
		अगर ((dst_reg->type == PTR_TO_PACKET &&
		     src_reg->type == PTR_TO_PACKET_END) ||
		    (dst_reg->type == PTR_TO_PACKET_META &&
		     reg_is_init_pkt_poपूर्णांकer(src_reg, PTR_TO_PACKET))) अणु
			/* pkt_data' > pkt_end, pkt_meta' > pkt_data */
			find_good_pkt_poपूर्णांकers(this_branch, dst_reg,
					       dst_reg->type, false);
			mark_pkt_end(other_branch, insn->dst_reg, true);
		पूर्ण अन्यथा अगर ((dst_reg->type == PTR_TO_PACKET_END &&
			    src_reg->type == PTR_TO_PACKET) ||
			   (reg_is_init_pkt_poपूर्णांकer(dst_reg, PTR_TO_PACKET) &&
			    src_reg->type == PTR_TO_PACKET_META)) अणु
			/* pkt_end > pkt_data', pkt_data > pkt_meta' */
			find_good_pkt_poपूर्णांकers(other_branch, src_reg,
					       src_reg->type, true);
			mark_pkt_end(this_branch, insn->src_reg, false);
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
		अवरोध;
	हाल BPF_JLT:
		अगर ((dst_reg->type == PTR_TO_PACKET &&
		     src_reg->type == PTR_TO_PACKET_END) ||
		    (dst_reg->type == PTR_TO_PACKET_META &&
		     reg_is_init_pkt_poपूर्णांकer(src_reg, PTR_TO_PACKET))) अणु
			/* pkt_data' < pkt_end, pkt_meta' < pkt_data */
			find_good_pkt_poपूर्णांकers(other_branch, dst_reg,
					       dst_reg->type, true);
			mark_pkt_end(this_branch, insn->dst_reg, false);
		पूर्ण अन्यथा अगर ((dst_reg->type == PTR_TO_PACKET_END &&
			    src_reg->type == PTR_TO_PACKET) ||
			   (reg_is_init_pkt_poपूर्णांकer(dst_reg, PTR_TO_PACKET) &&
			    src_reg->type == PTR_TO_PACKET_META)) अणु
			/* pkt_end < pkt_data', pkt_data > pkt_meta' */
			find_good_pkt_poपूर्णांकers(this_branch, src_reg,
					       src_reg->type, false);
			mark_pkt_end(other_branch, insn->src_reg, true);
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
		अवरोध;
	हाल BPF_JGE:
		अगर ((dst_reg->type == PTR_TO_PACKET &&
		     src_reg->type == PTR_TO_PACKET_END) ||
		    (dst_reg->type == PTR_TO_PACKET_META &&
		     reg_is_init_pkt_poपूर्णांकer(src_reg, PTR_TO_PACKET))) अणु
			/* pkt_data' >= pkt_end, pkt_meta' >= pkt_data */
			find_good_pkt_poपूर्णांकers(this_branch, dst_reg,
					       dst_reg->type, true);
			mark_pkt_end(other_branch, insn->dst_reg, false);
		पूर्ण अन्यथा अगर ((dst_reg->type == PTR_TO_PACKET_END &&
			    src_reg->type == PTR_TO_PACKET) ||
			   (reg_is_init_pkt_poपूर्णांकer(dst_reg, PTR_TO_PACKET) &&
			    src_reg->type == PTR_TO_PACKET_META)) अणु
			/* pkt_end >= pkt_data', pkt_data >= pkt_meta' */
			find_good_pkt_poपूर्णांकers(other_branch, src_reg,
					       src_reg->type, false);
			mark_pkt_end(this_branch, insn->src_reg, true);
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
		अवरोध;
	हाल BPF_JLE:
		अगर ((dst_reg->type == PTR_TO_PACKET &&
		     src_reg->type == PTR_TO_PACKET_END) ||
		    (dst_reg->type == PTR_TO_PACKET_META &&
		     reg_is_init_pkt_poपूर्णांकer(src_reg, PTR_TO_PACKET))) अणु
			/* pkt_data' <= pkt_end, pkt_meta' <= pkt_data */
			find_good_pkt_poपूर्णांकers(other_branch, dst_reg,
					       dst_reg->type, false);
			mark_pkt_end(this_branch, insn->dst_reg, true);
		पूर्ण अन्यथा अगर ((dst_reg->type == PTR_TO_PACKET_END &&
			    src_reg->type == PTR_TO_PACKET) ||
			   (reg_is_init_pkt_poपूर्णांकer(dst_reg, PTR_TO_PACKET) &&
			    src_reg->type == PTR_TO_PACKET_META)) अणु
			/* pkt_end <= pkt_data', pkt_data <= pkt_meta' */
			find_good_pkt_poपूर्णांकers(this_branch, src_reg,
					       src_reg->type, true);
			mark_pkt_end(other_branch, insn->src_reg, false);
		पूर्ण अन्यथा अणु
			वापस false;
		पूर्ण
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम find_equal_scalars(काष्ठा bpf_verअगरier_state *vstate,
			       काष्ठा bpf_reg_state *known_reg)
अणु
	काष्ठा bpf_func_state *state;
	काष्ठा bpf_reg_state *reg;
	पूर्णांक i, j;

	क्रम (i = 0; i <= vstate->curframe; i++) अणु
		state = vstate->frame[i];
		क्रम (j = 0; j < MAX_BPF_REG; j++) अणु
			reg = &state->regs[j];
			अगर (reg->type == SCALAR_VALUE && reg->id == known_reg->id)
				*reg = *known_reg;
		पूर्ण

		bpf_क्रम_each_spilled_reg(j, state, reg) अणु
			अगर (!reg)
				जारी;
			अगर (reg->type == SCALAR_VALUE && reg->id == known_reg->id)
				*reg = *known_reg;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक check_cond_jmp_op(काष्ठा bpf_verअगरier_env *env,
			     काष्ठा bpf_insn *insn, पूर्णांक *insn_idx)
अणु
	काष्ठा bpf_verअगरier_state *this_branch = env->cur_state;
	काष्ठा bpf_verअगरier_state *other_branch;
	काष्ठा bpf_reg_state *regs = this_branch->frame[this_branch->curframe]->regs;
	काष्ठा bpf_reg_state *dst_reg, *other_branch_regs, *src_reg = शून्य;
	u8 opcode = BPF_OP(insn->code);
	bool is_jmp32;
	पूर्णांक pred = -1;
	पूर्णांक err;

	/* Only conditional jumps are expected to reach here. */
	अगर (opcode == BPF_JA || opcode > BPF_JSLE) अणु
		verbose(env, "invalid BPF_JMP/JMP32 opcode %x\n", opcode);
		वापस -EINVAL;
	पूर्ण

	अगर (BPF_SRC(insn->code) == BPF_X) अणु
		अगर (insn->imm != 0) अणु
			verbose(env, "BPF_JMP/JMP32 uses reserved fields\n");
			वापस -EINVAL;
		पूर्ण

		/* check src1 opeअक्रम */
		err = check_reg_arg(env, insn->src_reg, SRC_OP);
		अगर (err)
			वापस err;

		अगर (is_poपूर्णांकer_value(env, insn->src_reg)) अणु
			verbose(env, "R%d pointer comparison prohibited\n",
				insn->src_reg);
			वापस -EACCES;
		पूर्ण
		src_reg = &regs[insn->src_reg];
	पूर्ण अन्यथा अणु
		अगर (insn->src_reg != BPF_REG_0) अणु
			verbose(env, "BPF_JMP/JMP32 uses reserved fields\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* check src2 opeअक्रम */
	err = check_reg_arg(env, insn->dst_reg, SRC_OP);
	अगर (err)
		वापस err;

	dst_reg = &regs[insn->dst_reg];
	is_jmp32 = BPF_CLASS(insn->code) == BPF_JMP32;

	अगर (BPF_SRC(insn->code) == BPF_K) अणु
		pred = is_branch_taken(dst_reg, insn->imm, opcode, is_jmp32);
	पूर्ण अन्यथा अगर (src_reg->type == SCALAR_VALUE &&
		   is_jmp32 && tnum_is_स्थिर(tnum_subreg(src_reg->var_off))) अणु
		pred = is_branch_taken(dst_reg,
				       tnum_subreg(src_reg->var_off).value,
				       opcode,
				       is_jmp32);
	पूर्ण अन्यथा अगर (src_reg->type == SCALAR_VALUE &&
		   !is_jmp32 && tnum_is_स्थिर(src_reg->var_off)) अणु
		pred = is_branch_taken(dst_reg,
				       src_reg->var_off.value,
				       opcode,
				       is_jmp32);
	पूर्ण अन्यथा अगर (reg_is_pkt_poपूर्णांकer_any(dst_reg) &&
		   reg_is_pkt_poपूर्णांकer_any(src_reg) &&
		   !is_jmp32) अणु
		pred = is_pkt_ptr_branch_taken(dst_reg, src_reg, opcode);
	पूर्ण

	अगर (pred >= 0) अणु
		/* If we get here with a dst_reg poपूर्णांकer type it is because
		 * above is_branch_taken() special हालd the 0 comparison.
		 */
		अगर (!__is_poपूर्णांकer_value(false, dst_reg))
			err = mark_chain_precision(env, insn->dst_reg);
		अगर (BPF_SRC(insn->code) == BPF_X && !err &&
		    !__is_poपूर्णांकer_value(false, src_reg))
			err = mark_chain_precision(env, insn->src_reg);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (pred == 1) अणु
		/* Only follow the जाओ, ignore fall-through. If needed, push
		 * the fall-through branch क्रम simulation under speculative
		 * execution.
		 */
		अगर (!env->bypass_spec_v1 &&
		    !sanitize_speculative_path(env, insn, *insn_idx + 1,
					       *insn_idx))
			वापस -EFAULT;
		*insn_idx += insn->off;
		वापस 0;
	पूर्ण अन्यथा अगर (pred == 0) अणु
		/* Only follow the fall-through branch, since that's where the
		 * program will go. If needed, push the जाओ branch क्रम
		 * simulation under speculative execution.
		 */
		अगर (!env->bypass_spec_v1 &&
		    !sanitize_speculative_path(env, insn,
					       *insn_idx + insn->off + 1,
					       *insn_idx))
			वापस -EFAULT;
		वापस 0;
	पूर्ण

	other_branch = push_stack(env, *insn_idx + insn->off + 1, *insn_idx,
				  false);
	अगर (!other_branch)
		वापस -EFAULT;
	other_branch_regs = other_branch->frame[other_branch->curframe]->regs;

	/* detect अगर we are comparing against a स्थिरant value so we can adjust
	 * our min/max values क्रम our dst रेजिस्टर.
	 * this is only legit अगर both are scalars (or poपूर्णांकers to the same
	 * object, I suppose, but we करोn't support that right now), because
	 * otherwise the dअगरferent base poपूर्णांकers mean the offsets aren't
	 * comparable.
	 */
	अगर (BPF_SRC(insn->code) == BPF_X) अणु
		काष्ठा bpf_reg_state *src_reg = &regs[insn->src_reg];

		अगर (dst_reg->type == SCALAR_VALUE &&
		    src_reg->type == SCALAR_VALUE) अणु
			अगर (tnum_is_स्थिर(src_reg->var_off) ||
			    (is_jmp32 &&
			     tnum_is_स्थिर(tnum_subreg(src_reg->var_off))))
				reg_set_min_max(&other_branch_regs[insn->dst_reg],
						dst_reg,
						src_reg->var_off.value,
						tnum_subreg(src_reg->var_off).value,
						opcode, is_jmp32);
			अन्यथा अगर (tnum_is_स्थिर(dst_reg->var_off) ||
				 (is_jmp32 &&
				  tnum_is_स्थिर(tnum_subreg(dst_reg->var_off))))
				reg_set_min_max_inv(&other_branch_regs[insn->src_reg],
						    src_reg,
						    dst_reg->var_off.value,
						    tnum_subreg(dst_reg->var_off).value,
						    opcode, is_jmp32);
			अन्यथा अगर (!is_jmp32 &&
				 (opcode == BPF_JEQ || opcode == BPF_JNE))
				/* Comparing क्रम equality, we can combine knowledge */
				reg_combine_min_max(&other_branch_regs[insn->src_reg],
						    &other_branch_regs[insn->dst_reg],
						    src_reg, dst_reg, opcode);
			अगर (src_reg->id &&
			    !WARN_ON_ONCE(src_reg->id != other_branch_regs[insn->src_reg].id)) अणु
				find_equal_scalars(this_branch, src_reg);
				find_equal_scalars(other_branch, &other_branch_regs[insn->src_reg]);
			पूर्ण

		पूर्ण
	पूर्ण अन्यथा अगर (dst_reg->type == SCALAR_VALUE) अणु
		reg_set_min_max(&other_branch_regs[insn->dst_reg],
					dst_reg, insn->imm, (u32)insn->imm,
					opcode, is_jmp32);
	पूर्ण

	अगर (dst_reg->type == SCALAR_VALUE && dst_reg->id &&
	    !WARN_ON_ONCE(dst_reg->id != other_branch_regs[insn->dst_reg].id)) अणु
		find_equal_scalars(this_branch, dst_reg);
		find_equal_scalars(other_branch, &other_branch_regs[insn->dst_reg]);
	पूर्ण

	/* detect अगर R == 0 where R is वापसed from bpf_map_lookup_elem().
	 * NOTE: these optimizations below are related with poपूर्णांकer comparison
	 *       which will never be JMP32.
	 */
	अगर (!is_jmp32 && BPF_SRC(insn->code) == BPF_K &&
	    insn->imm == 0 && (opcode == BPF_JEQ || opcode == BPF_JNE) &&
	    reg_type_may_be_null(dst_reg->type)) अणु
		/* Mark all identical रेजिस्टरs in each branch as either
		 * safe or unknown depending R == 0 or R != 0 conditional.
		 */
		mark_ptr_or_null_regs(this_branch, insn->dst_reg,
				      opcode == BPF_JNE);
		mark_ptr_or_null_regs(other_branch, insn->dst_reg,
				      opcode == BPF_JEQ);
	पूर्ण अन्यथा अगर (!try_match_pkt_poपूर्णांकers(insn, dst_reg, &regs[insn->src_reg],
					   this_branch, other_branch) &&
		   is_poपूर्णांकer_value(env, insn->dst_reg)) अणु
		verbose(env, "R%d pointer comparison prohibited\n",
			insn->dst_reg);
		वापस -EACCES;
	पूर्ण
	अगर (env->log.level & BPF_LOG_LEVEL)
		prपूर्णांक_verअगरier_state(env, this_branch->frame[this_branch->curframe]);
	वापस 0;
पूर्ण

/* verअगरy BPF_LD_IMM64 inकाष्ठाion */
अटल पूर्णांक check_ld_imm(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn)
अणु
	काष्ठा bpf_insn_aux_data *aux = cur_aux(env);
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	काष्ठा bpf_reg_state *dst_reg;
	काष्ठा bpf_map *map;
	पूर्णांक err;

	अगर (BPF_SIZE(insn->code) != BPF_DW) अणु
		verbose(env, "invalid BPF_LD_IMM insn\n");
		वापस -EINVAL;
	पूर्ण
	अगर (insn->off != 0) अणु
		verbose(env, "BPF_LD_IMM64 uses reserved fields\n");
		वापस -EINVAL;
	पूर्ण

	err = check_reg_arg(env, insn->dst_reg, DST_OP);
	अगर (err)
		वापस err;

	dst_reg = &regs[insn->dst_reg];
	अगर (insn->src_reg == 0) अणु
		u64 imm = ((u64)(insn + 1)->imm << 32) | (u32)insn->imm;

		dst_reg->type = SCALAR_VALUE;
		__mark_reg_known(&regs[insn->dst_reg], imm);
		वापस 0;
	पूर्ण

	अगर (insn->src_reg == BPF_PSEUDO_BTF_ID) अणु
		mark_reg_known_zero(env, regs, insn->dst_reg);

		dst_reg->type = aux->btf_var.reg_type;
		चयन (dst_reg->type) अणु
		हाल PTR_TO_MEM:
			dst_reg->mem_size = aux->btf_var.mem_size;
			अवरोध;
		हाल PTR_TO_BTF_ID:
		हाल PTR_TO_PERCPU_BTF_ID:
			dst_reg->btf = aux->btf_var.btf;
			dst_reg->btf_id = aux->btf_var.btf_id;
			अवरोध;
		शेष:
			verbose(env, "bpf verifier is misconfigured\n");
			वापस -EFAULT;
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (insn->src_reg == BPF_PSEUDO_FUNC) अणु
		काष्ठा bpf_prog_aux *aux = env->prog->aux;
		u32 subprogno = insn[1].imm;

		अगर (!aux->func_info) अणु
			verbose(env, "missing btf func_info\n");
			वापस -EINVAL;
		पूर्ण
		अगर (aux->func_info_aux[subprogno].linkage != BTF_FUNC_STATIC) अणु
			verbose(env, "callback function not static\n");
			वापस -EINVAL;
		पूर्ण

		dst_reg->type = PTR_TO_FUNC;
		dst_reg->subprogno = subprogno;
		वापस 0;
	पूर्ण

	map = env->used_maps[aux->map_index];
	mark_reg_known_zero(env, regs, insn->dst_reg);
	dst_reg->map_ptr = map;

	अगर (insn->src_reg == BPF_PSEUDO_MAP_VALUE) अणु
		dst_reg->type = PTR_TO_MAP_VALUE;
		dst_reg->off = aux->map_off;
		अगर (map_value_has_spin_lock(map))
			dst_reg->id = ++env->id_gen;
	पूर्ण अन्यथा अगर (insn->src_reg == BPF_PSEUDO_MAP_FD) अणु
		dst_reg->type = CONST_PTR_TO_MAP;
	पूर्ण अन्यथा अणु
		verbose(env, "bpf verifier is misconfigured\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल bool may_access_skb(क्रमागत bpf_prog_type type)
अणु
	चयन (type) अणु
	हाल BPF_PROG_TYPE_SOCKET_FILTER:
	हाल BPF_PROG_TYPE_SCHED_CLS:
	हाल BPF_PROG_TYPE_SCHED_ACT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

/* verअगरy safety of LD_ABS|LD_IND inकाष्ठाions:
 * - they can only appear in the programs where ctx == skb
 * - since they are wrappers of function calls, they scratch R1-R5 रेजिस्टरs,
 *   preserve R6-R9, and store वापस value पूर्णांकo R0
 *
 * Implicit input:
 *   ctx == skb == R6 == CTX
 *
 * Explicit input:
 *   SRC == any रेजिस्टर
 *   IMM == 32-bit immediate
 *
 * Output:
 *   R0 - 8/16/32-bit skb data converted to cpu endianness
 */
अटल पूर्णांक check_ld_असल(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_insn *insn)
अणु
	काष्ठा bpf_reg_state *regs = cur_regs(env);
	अटल स्थिर पूर्णांक ctx_reg = BPF_REG_6;
	u8 mode = BPF_MODE(insn->code);
	पूर्णांक i, err;

	अगर (!may_access_skb(resolve_prog_type(env->prog))) अणु
		verbose(env, "BPF_LD_[ABS|IND] instructions not allowed for this program type\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!env->ops->gen_ld_असल) अणु
		verbose(env, "bpf verifier is misconfigured\n");
		वापस -EINVAL;
	पूर्ण

	अगर (insn->dst_reg != BPF_REG_0 || insn->off != 0 ||
	    BPF_SIZE(insn->code) == BPF_DW ||
	    (mode == BPF_ABS && insn->src_reg != BPF_REG_0)) अणु
		verbose(env, "BPF_LD_[ABS|IND] uses reserved fields\n");
		वापस -EINVAL;
	पूर्ण

	/* check whether implicit source opeअक्रम (रेजिस्टर R6) is पढ़ोable */
	err = check_reg_arg(env, ctx_reg, SRC_OP);
	अगर (err)
		वापस err;

	/* Disallow usage of BPF_LD_[ABS|IND] with reference tracking, as
	 * gen_ld_असल() may terminate the program at runसमय, leading to
	 * reference leak.
	 */
	err = check_reference_leak(env);
	अगर (err) अणु
		verbose(env, "BPF_LD_[ABS|IND] cannot be mixed with socket references\n");
		वापस err;
	पूर्ण

	अगर (env->cur_state->active_spin_lock) अणु
		verbose(env, "BPF_LD_[ABS|IND] cannot be used inside bpf_spin_lock-ed region\n");
		वापस -EINVAL;
	पूर्ण

	अगर (regs[ctx_reg].type != PTR_TO_CTX) अणु
		verbose(env,
			"at the time of BPF_LD_ABS|IND R6 != pointer to skb\n");
		वापस -EINVAL;
	पूर्ण

	अगर (mode == BPF_IND) अणु
		/* check explicit source opeअक्रम */
		err = check_reg_arg(env, insn->src_reg, SRC_OP);
		अगर (err)
			वापस err;
	पूर्ण

	err = check_ctx_reg(env, &regs[ctx_reg], ctx_reg);
	अगर (err < 0)
		वापस err;

	/* reset caller saved regs to unपढ़ोable */
	क्रम (i = 0; i < CALLER_SAVED_REGS; i++) अणु
		mark_reg_not_init(env, regs, caller_saved[i]);
		check_reg_arg(env, caller_saved[i], DST_OP_NO_MARK);
	पूर्ण

	/* mark destination R0 रेजिस्टर as पढ़ोable, since it contains
	 * the value fetched from the packet.
	 * Alपढ़ोy marked as written above.
	 */
	mark_reg_unknown(env, regs, BPF_REG_0);
	/* ld_असल load up to 32-bit skb data. */
	regs[BPF_REG_0].subreg_def = env->insn_idx + 1;
	वापस 0;
पूर्ण

अटल पूर्णांक check_वापस_code(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा tnum enक्रमce_attach_type_range = tnum_unknown;
	स्थिर काष्ठा bpf_prog *prog = env->prog;
	काष्ठा bpf_reg_state *reg;
	काष्ठा tnum range = tnum_range(0, 1);
	क्रमागत bpf_prog_type prog_type = resolve_prog_type(env->prog);
	पूर्णांक err;
	स्थिर bool is_subprog = env->cur_state->frame[0]->subprogno;

	/* LSM and काष्ठा_ops func-ptr's वापस type could be "void" */
	अगर (!is_subprog &&
	    (prog_type == BPF_PROG_TYPE_STRUCT_OPS ||
	     prog_type == BPF_PROG_TYPE_LSM) &&
	    !prog->aux->attach_func_proto->type)
		वापस 0;

	/* eBPF calling convetion is such that R0 is used
	 * to वापस the value from eBPF program.
	 * Make sure that it's पढ़ोable at this समय
	 * of bpf_निकास, which means that program wrote
	 * something पूर्णांकo it earlier
	 */
	err = check_reg_arg(env, BPF_REG_0, SRC_OP);
	अगर (err)
		वापस err;

	अगर (is_poपूर्णांकer_value(env, BPF_REG_0)) अणु
		verbose(env, "R0 leaks addr as return value\n");
		वापस -EACCES;
	पूर्ण

	reg = cur_regs(env) + BPF_REG_0;
	अगर (is_subprog) अणु
		अगर (reg->type != SCALAR_VALUE) अणु
			verbose(env, "At subprogram exit the register R0 is not a scalar value (%s)\n",
				reg_type_str[reg->type]);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	चयन (prog_type) अणु
	हाल BPF_PROG_TYPE_CGROUP_SOCK_ADDR:
		अगर (env->prog->expected_attach_type == BPF_CGROUP_UDP4_RECVMSG ||
		    env->prog->expected_attach_type == BPF_CGROUP_UDP6_RECVMSG ||
		    env->prog->expected_attach_type == BPF_CGROUP_INET4_GETPEERNAME ||
		    env->prog->expected_attach_type == BPF_CGROUP_INET6_GETPEERNAME ||
		    env->prog->expected_attach_type == BPF_CGROUP_INET4_GETSOCKNAME ||
		    env->prog->expected_attach_type == BPF_CGROUP_INET6_GETSOCKNAME)
			range = tnum_range(1, 1);
		अगर (env->prog->expected_attach_type == BPF_CGROUP_INET4_BIND ||
		    env->prog->expected_attach_type == BPF_CGROUP_INET6_BIND)
			range = tnum_range(0, 3);
		अवरोध;
	हाल BPF_PROG_TYPE_CGROUP_SKB:
		अगर (env->prog->expected_attach_type == BPF_CGROUP_INET_EGRESS) अणु
			range = tnum_range(0, 3);
			enक्रमce_attach_type_range = tnum_range(2, 3);
		पूर्ण
		अवरोध;
	हाल BPF_PROG_TYPE_CGROUP_SOCK:
	हाल BPF_PROG_TYPE_SOCK_OPS:
	हाल BPF_PROG_TYPE_CGROUP_DEVICE:
	हाल BPF_PROG_TYPE_CGROUP_SYSCTL:
	हाल BPF_PROG_TYPE_CGROUP_SOCKOPT:
		अवरोध;
	हाल BPF_PROG_TYPE_RAW_TRACEPOINT:
		अगर (!env->prog->aux->attach_btf_id)
			वापस 0;
		range = tnum_स्थिर(0);
		अवरोध;
	हाल BPF_PROG_TYPE_TRACING:
		चयन (env->prog->expected_attach_type) अणु
		हाल BPF_TRACE_FENTRY:
		हाल BPF_TRACE_FEXIT:
			range = tnum_स्थिर(0);
			अवरोध;
		हाल BPF_TRACE_RAW_TP:
		हाल BPF_MODIFY_RETURN:
			वापस 0;
		हाल BPF_TRACE_ITER:
			अवरोध;
		शेष:
			वापस -ENOTSUPP;
		पूर्ण
		अवरोध;
	हाल BPF_PROG_TYPE_SK_LOOKUP:
		range = tnum_range(SK_DROP, SK_PASS);
		अवरोध;
	हाल BPF_PROG_TYPE_EXT:
		/* freplace program can वापस anything as its वापस value
		 * depends on the to-be-replaced kernel func or bpf program.
		 */
	शेष:
		वापस 0;
	पूर्ण

	अगर (reg->type != SCALAR_VALUE) अणु
		verbose(env, "At program exit the register R0 is not a known value (%s)\n",
			reg_type_str[reg->type]);
		वापस -EINVAL;
	पूर्ण

	अगर (!tnum_in(range, reg->var_off)) अणु
		verbose_invalid_scalar(env, reg, &range, "program exit", "R0");
		वापस -EINVAL;
	पूर्ण

	अगर (!tnum_is_unknown(enक्रमce_attach_type_range) &&
	    tnum_in(enक्रमce_attach_type_range, reg->var_off))
		env->prog->enक्रमce_expected_attach_type = 1;
	वापस 0;
पूर्ण

/* non-recursive DFS pseuकरो code
 * 1  procedure DFS-iterative(G,v):
 * 2      label v as discovered
 * 3      let S be a stack
 * 4      S.push(v)
 * 5      जबतक S is not empty
 * 6            t <- S.pop()
 * 7            अगर t is what we're looking क्रम:
 * 8                वापस t
 * 9            क्रम all edges e in G.adjacentEdges(t) करो
 * 10               अगर edge e is alपढ़ोy labelled
 * 11                   जारी with the next edge
 * 12               w <- G.adjacentVertex(t,e)
 * 13               अगर vertex w is not discovered and not explored
 * 14                   label e as tree-edge
 * 15                   label w as discovered
 * 16                   S.push(w)
 * 17                   जारी at 5
 * 18               अन्यथा अगर vertex w is discovered
 * 19                   label e as back-edge
 * 20               अन्यथा
 * 21                   // vertex w is explored
 * 22                   label e as क्रमward- or cross-edge
 * 23           label t as explored
 * 24           S.pop()
 *
 * convention:
 * 0x10 - discovered
 * 0x11 - discovered and fall-through edge labelled
 * 0x12 - discovered and fall-through and branch edges labelled
 * 0x20 - explored
 */

क्रमागत अणु
	DISCOVERED = 0x10,
	EXPLORED = 0x20,
	FALLTHROUGH = 1,
	BRANCH = 2,
पूर्ण;

अटल u32 state_htab_size(काष्ठा bpf_verअगरier_env *env)
अणु
	वापस env->prog->len;
पूर्ण

अटल काष्ठा bpf_verअगरier_state_list **explored_state(
					काष्ठा bpf_verअगरier_env *env,
					पूर्णांक idx)
अणु
	काष्ठा bpf_verअगरier_state *cur = env->cur_state;
	काष्ठा bpf_func_state *state = cur->frame[cur->curframe];

	वापस &env->explored_states[(idx ^ state->callsite) % state_htab_size(env)];
पूर्ण

अटल व्योम init_explored_state(काष्ठा bpf_verअगरier_env *env, पूर्णांक idx)
अणु
	env->insn_aux_data[idx].prune_poपूर्णांक = true;
पूर्ण

क्रमागत अणु
	DONE_EXPLORING = 0,
	KEEP_EXPLORING = 1,
पूर्ण;

/* t, w, e - match pseuकरो-code above:
 * t - index of current inकाष्ठाion
 * w - next inकाष्ठाion
 * e - edge
 */
अटल पूर्णांक push_insn(पूर्णांक t, पूर्णांक w, पूर्णांक e, काष्ठा bpf_verअगरier_env *env,
		     bool loop_ok)
अणु
	पूर्णांक *insn_stack = env->cfg.insn_stack;
	पूर्णांक *insn_state = env->cfg.insn_state;

	अगर (e == FALLTHROUGH && insn_state[t] >= (DISCOVERED | FALLTHROUGH))
		वापस DONE_EXPLORING;

	अगर (e == BRANCH && insn_state[t] >= (DISCOVERED | BRANCH))
		वापस DONE_EXPLORING;

	अगर (w < 0 || w >= env->prog->len) अणु
		verbose_linfo(env, t, "%d: ", t);
		verbose(env, "jump out of range from insn %d to %d\n", t, w);
		वापस -EINVAL;
	पूर्ण

	अगर (e == BRANCH)
		/* mark branch target क्रम state pruning */
		init_explored_state(env, w);

	अगर (insn_state[w] == 0) अणु
		/* tree-edge */
		insn_state[t] = DISCOVERED | e;
		insn_state[w] = DISCOVERED;
		अगर (env->cfg.cur_stack >= env->prog->len)
			वापस -E2BIG;
		insn_stack[env->cfg.cur_stack++] = w;
		वापस KEEP_EXPLORING;
	पूर्ण अन्यथा अगर ((insn_state[w] & 0xF0) == DISCOVERED) अणु
		अगर (loop_ok && env->bpf_capable)
			वापस DONE_EXPLORING;
		verbose_linfo(env, t, "%d: ", t);
		verbose_linfo(env, w, "%d: ", w);
		verbose(env, "back-edge from insn %d to %d\n", t, w);
		वापस -EINVAL;
	पूर्ण अन्यथा अगर (insn_state[w] == EXPLORED) अणु
		/* क्रमward- or cross-edge */
		insn_state[t] = DISCOVERED | e;
	पूर्ण अन्यथा अणु
		verbose(env, "insn state internal bug\n");
		वापस -EFAULT;
	पूर्ण
	वापस DONE_EXPLORING;
पूर्ण

अटल पूर्णांक visit_func_call_insn(पूर्णांक t, पूर्णांक insn_cnt,
				काष्ठा bpf_insn *insns,
				काष्ठा bpf_verअगरier_env *env,
				bool visit_callee)
अणु
	पूर्णांक ret;

	ret = push_insn(t, t + 1, FALLTHROUGH, env, false);
	अगर (ret)
		वापस ret;

	अगर (t + 1 < insn_cnt)
		init_explored_state(env, t + 1);
	अगर (visit_callee) अणु
		init_explored_state(env, t);
		ret = push_insn(t, t + insns[t].imm + 1, BRANCH,
				env, false);
	पूर्ण
	वापस ret;
पूर्ण

/* Visits the inकाष्ठाion at index t and वापसs one of the following:
 *  < 0 - an error occurred
 *  DONE_EXPLORING - the inकाष्ठाion was fully explored
 *  KEEP_EXPLORING - there is still work to be करोne beक्रमe it is fully explored
 */
अटल पूर्णांक visit_insn(पूर्णांक t, पूर्णांक insn_cnt, काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_insn *insns = env->prog->insnsi;
	पूर्णांक ret;

	अगर (bpf_pseuकरो_func(insns + t))
		वापस visit_func_call_insn(t, insn_cnt, insns, env, true);

	/* All non-branch inकाष्ठाions have a single fall-through edge. */
	अगर (BPF_CLASS(insns[t].code) != BPF_JMP &&
	    BPF_CLASS(insns[t].code) != BPF_JMP32)
		वापस push_insn(t, t + 1, FALLTHROUGH, env, false);

	चयन (BPF_OP(insns[t].code)) अणु
	हाल BPF_EXIT:
		वापस DONE_EXPLORING;

	हाल BPF_CALL:
		वापस visit_func_call_insn(t, insn_cnt, insns, env,
					    insns[t].src_reg == BPF_PSEUDO_CALL);

	हाल BPF_JA:
		अगर (BPF_SRC(insns[t].code) != BPF_K)
			वापस -EINVAL;

		/* unconditional jump with single edge */
		ret = push_insn(t, t + insns[t].off + 1, FALLTHROUGH, env,
				true);
		अगर (ret)
			वापस ret;

		/* unconditional jmp is not a good pruning poपूर्णांक,
		 * but it's marked, since backtracking needs
		 * to record jmp history in is_state_visited().
		 */
		init_explored_state(env, t + insns[t].off + 1);
		/* tell verअगरier to check क्रम equivalent states
		 * after every call and jump
		 */
		अगर (t + 1 < insn_cnt)
			init_explored_state(env, t + 1);

		वापस ret;

	शेष:
		/* conditional jump with two edges */
		init_explored_state(env, t);
		ret = push_insn(t, t + 1, FALLTHROUGH, env, true);
		अगर (ret)
			वापस ret;

		वापस push_insn(t, t + insns[t].off + 1, BRANCH, env, true);
	पूर्ण
पूर्ण

/* non-recursive depth-first-search to detect loops in BPF program
 * loop == back-edge in directed graph
 */
अटल पूर्णांक check_cfg(काष्ठा bpf_verअगरier_env *env)
अणु
	पूर्णांक insn_cnt = env->prog->len;
	पूर्णांक *insn_stack, *insn_state;
	पूर्णांक ret = 0;
	पूर्णांक i;

	insn_state = env->cfg.insn_state = kvसुस्मृति(insn_cnt, माप(पूर्णांक), GFP_KERNEL);
	अगर (!insn_state)
		वापस -ENOMEM;

	insn_stack = env->cfg.insn_stack = kvसुस्मृति(insn_cnt, माप(पूर्णांक), GFP_KERNEL);
	अगर (!insn_stack) अणु
		kvमुक्त(insn_state);
		वापस -ENOMEM;
	पूर्ण

	insn_state[0] = DISCOVERED; /* mark 1st insn as discovered */
	insn_stack[0] = 0; /* 0 is the first inकाष्ठाion */
	env->cfg.cur_stack = 1;

	जबतक (env->cfg.cur_stack > 0) अणु
		पूर्णांक t = insn_stack[env->cfg.cur_stack - 1];

		ret = visit_insn(t, insn_cnt, env);
		चयन (ret) अणु
		हाल DONE_EXPLORING:
			insn_state[t] = EXPLORED;
			env->cfg.cur_stack--;
			अवरोध;
		हाल KEEP_EXPLORING:
			अवरोध;
		शेष:
			अगर (ret > 0) अणु
				verbose(env, "visit_insn internal bug\n");
				ret = -EFAULT;
			पूर्ण
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण

	अगर (env->cfg.cur_stack < 0) अणु
		verbose(env, "pop stack internal bug\n");
		ret = -EFAULT;
		जाओ err_मुक्त;
	पूर्ण

	क्रम (i = 0; i < insn_cnt; i++) अणु
		अगर (insn_state[i] != EXPLORED) अणु
			verbose(env, "unreachable insn %d\n", i);
			ret = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण
	पूर्ण
	ret = 0; /* cfg looks good */

err_मुक्त:
	kvमुक्त(insn_state);
	kvमुक्त(insn_stack);
	env->cfg.insn_state = env->cfg.insn_stack = शून्य;
	वापस ret;
पूर्ण

अटल पूर्णांक check_abnormal_वापस(काष्ठा bpf_verअगरier_env *env)
अणु
	पूर्णांक i;

	क्रम (i = 1; i < env->subprog_cnt; i++) अणु
		अगर (env->subprog_info[i].has_ld_असल) अणु
			verbose(env, "LD_ABS is not allowed in subprogs without BTF\n");
			वापस -EINVAL;
		पूर्ण
		अगर (env->subprog_info[i].has_tail_call) अणु
			verbose(env, "tail_call is not allowed in subprogs without BTF\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* The minimum supported BTF func info size */
#घोषणा MIN_BPF_FUNCINFO_SIZE	8
#घोषणा MAX_FUNCINFO_REC_SIZE	252

अटल पूर्णांक check_btf_func(काष्ठा bpf_verअगरier_env *env,
			  स्थिर जोड़ bpf_attr *attr,
			  जोड़ bpf_attr __user *uattr)
अणु
	स्थिर काष्ठा btf_type *type, *func_proto, *ret_type;
	u32 i, nfuncs, urec_size, min_size;
	u32 krec_size = माप(काष्ठा bpf_func_info);
	काष्ठा bpf_func_info *krecord;
	काष्ठा bpf_func_info_aux *info_aux = शून्य;
	काष्ठा bpf_prog *prog;
	स्थिर काष्ठा btf *btf;
	व्योम __user *urecord;
	u32 prev_offset = 0;
	bool scalar_वापस;
	पूर्णांक ret = -ENOMEM;

	nfuncs = attr->func_info_cnt;
	अगर (!nfuncs) अणु
		अगर (check_abnormal_वापस(env))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	अगर (nfuncs != env->subprog_cnt) अणु
		verbose(env, "number of funcs in func_info doesn't match number of subprogs\n");
		वापस -EINVAL;
	पूर्ण

	urec_size = attr->func_info_rec_size;
	अगर (urec_size < MIN_BPF_FUNCINFO_SIZE ||
	    urec_size > MAX_FUNCINFO_REC_SIZE ||
	    urec_size % माप(u32)) अणु
		verbose(env, "invalid func info rec size %u\n", urec_size);
		वापस -EINVAL;
	पूर्ण

	prog = env->prog;
	btf = prog->aux->btf;

	urecord = u64_to_user_ptr(attr->func_info);
	min_size = min_t(u32, krec_size, urec_size);

	krecord = kvसुस्मृति(nfuncs, krec_size, GFP_KERNEL | __GFP_NOWARN);
	अगर (!krecord)
		वापस -ENOMEM;
	info_aux = kसुस्मृति(nfuncs, माप(*info_aux), GFP_KERNEL | __GFP_NOWARN);
	अगर (!info_aux)
		जाओ err_मुक्त;

	क्रम (i = 0; i < nfuncs; i++) अणु
		ret = bpf_check_uarg_tail_zero(urecord, krec_size, urec_size);
		अगर (ret) अणु
			अगर (ret == -E2BIG) अणु
				verbose(env, "nonzero tailing record in func info");
				/* set the size kernel expects so loader can zero
				 * out the rest of the record.
				 */
				अगर (put_user(min_size, &uattr->func_info_rec_size))
					ret = -EFAULT;
			पूर्ण
			जाओ err_मुक्त;
		पूर्ण

		अगर (copy_from_user(&krecord[i], urecord, min_size)) अणु
			ret = -EFAULT;
			जाओ err_मुक्त;
		पूर्ण

		/* check insn_off */
		ret = -EINVAL;
		अगर (i == 0) अणु
			अगर (krecord[i].insn_off) अणु
				verbose(env,
					"nonzero insn_off %u for the first func info record",
					krecord[i].insn_off);
				जाओ err_मुक्त;
			पूर्ण
		पूर्ण अन्यथा अगर (krecord[i].insn_off <= prev_offset) अणु
			verbose(env,
				"same or smaller insn offset (%u) than previous func info record (%u)",
				krecord[i].insn_off, prev_offset);
			जाओ err_मुक्त;
		पूर्ण

		अगर (env->subprog_info[i].start != krecord[i].insn_off) अणु
			verbose(env, "func_info BTF section doesn't match subprog layout in BPF program\n");
			जाओ err_मुक्त;
		पूर्ण

		/* check type_id */
		type = btf_type_by_id(btf, krecord[i].type_id);
		अगर (!type || !btf_type_is_func(type)) अणु
			verbose(env, "invalid type id %d in func info",
				krecord[i].type_id);
			जाओ err_मुक्त;
		पूर्ण
		info_aux[i].linkage = BTF_INFO_VLEN(type->info);

		func_proto = btf_type_by_id(btf, type->type);
		अगर (unlikely(!func_proto || !btf_type_is_func_proto(func_proto)))
			/* btf_func_check() alपढ़ोy verअगरied it during BTF load */
			जाओ err_मुक्त;
		ret_type = btf_type_skip_modअगरiers(btf, func_proto->type, शून्य);
		scalar_वापस =
			btf_type_is_small_पूर्णांक(ret_type) || btf_type_is_क्रमागत(ret_type);
		अगर (i && !scalar_वापस && env->subprog_info[i].has_ld_असल) अणु
			verbose(env, "LD_ABS is only allowed in functions that return 'int'.\n");
			जाओ err_मुक्त;
		पूर्ण
		अगर (i && !scalar_वापस && env->subprog_info[i].has_tail_call) अणु
			verbose(env, "tail_call is only allowed in functions that return 'int'.\n");
			जाओ err_मुक्त;
		पूर्ण

		prev_offset = krecord[i].insn_off;
		urecord += urec_size;
	पूर्ण

	prog->aux->func_info = krecord;
	prog->aux->func_info_cnt = nfuncs;
	prog->aux->func_info_aux = info_aux;
	वापस 0;

err_मुक्त:
	kvमुक्त(krecord);
	kमुक्त(info_aux);
	वापस ret;
पूर्ण

अटल व्योम adjust_btf_func(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_prog_aux *aux = env->prog->aux;
	पूर्णांक i;

	अगर (!aux->func_info)
		वापस;

	क्रम (i = 0; i < env->subprog_cnt; i++)
		aux->func_info[i].insn_off = env->subprog_info[i].start;
पूर्ण

#घोषणा MIN_BPF_LINEINFO_SIZE	(दुरत्व(काष्ठा bpf_line_info, line_col) + \
		माप(((काष्ठा bpf_line_info *)(0))->line_col))
#घोषणा MAX_LINEINFO_REC_SIZE	MAX_FUNCINFO_REC_SIZE

अटल पूर्णांक check_btf_line(काष्ठा bpf_verअगरier_env *env,
			  स्थिर जोड़ bpf_attr *attr,
			  जोड़ bpf_attr __user *uattr)
अणु
	u32 i, s, nr_linfo, ncopy, expected_size, rec_size, prev_offset = 0;
	काष्ठा bpf_subprog_info *sub;
	काष्ठा bpf_line_info *linfo;
	काष्ठा bpf_prog *prog;
	स्थिर काष्ठा btf *btf;
	व्योम __user *ulinfo;
	पूर्णांक err;

	nr_linfo = attr->line_info_cnt;
	अगर (!nr_linfo)
		वापस 0;

	rec_size = attr->line_info_rec_size;
	अगर (rec_size < MIN_BPF_LINEINFO_SIZE ||
	    rec_size > MAX_LINEINFO_REC_SIZE ||
	    rec_size & (माप(u32) - 1))
		वापस -EINVAL;

	/* Need to zero it in हाल the userspace may
	 * pass in a smaller bpf_line_info object.
	 */
	linfo = kvसुस्मृति(nr_linfo, माप(काष्ठा bpf_line_info),
			 GFP_KERNEL | __GFP_NOWARN);
	अगर (!linfo)
		वापस -ENOMEM;

	prog = env->prog;
	btf = prog->aux->btf;

	s = 0;
	sub = env->subprog_info;
	ulinfo = u64_to_user_ptr(attr->line_info);
	expected_size = माप(काष्ठा bpf_line_info);
	ncopy = min_t(u32, expected_size, rec_size);
	क्रम (i = 0; i < nr_linfo; i++) अणु
		err = bpf_check_uarg_tail_zero(ulinfo, expected_size, rec_size);
		अगर (err) अणु
			अगर (err == -E2BIG) अणु
				verbose(env, "nonzero tailing record in line_info");
				अगर (put_user(expected_size,
					     &uattr->line_info_rec_size))
					err = -EFAULT;
			पूर्ण
			जाओ err_मुक्त;
		पूर्ण

		अगर (copy_from_user(&linfo[i], ulinfo, ncopy)) अणु
			err = -EFAULT;
			जाओ err_मुक्त;
		पूर्ण

		/*
		 * Check insn_off to ensure
		 * 1) strictly increasing AND
		 * 2) bounded by prog->len
		 *
		 * The linfo[0].insn_off == 0 check logically falls पूर्णांकo
		 * the later "missing bpf_line_info for func..." हाल
		 * because the first linfo[0].insn_off must be the
		 * first sub also and the first sub must have
		 * subprog_info[0].start == 0.
		 */
		अगर ((i && linfo[i].insn_off <= prev_offset) ||
		    linfo[i].insn_off >= prog->len) अणु
			verbose(env, "Invalid line_info[%u].insn_off:%u (prev_offset:%u prog->len:%u)\n",
				i, linfo[i].insn_off, prev_offset,
				prog->len);
			err = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण

		अगर (!prog->insnsi[linfo[i].insn_off].code) अणु
			verbose(env,
				"Invalid insn code at line_info[%u].insn_off\n",
				i);
			err = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण

		अगर (!btf_name_by_offset(btf, linfo[i].line_off) ||
		    !btf_name_by_offset(btf, linfo[i].file_name_off)) अणु
			verbose(env, "Invalid line_info[%u].line_off or .file_name_off\n", i);
			err = -EINVAL;
			जाओ err_मुक्त;
		पूर्ण

		अगर (s != env->subprog_cnt) अणु
			अगर (linfo[i].insn_off == sub[s].start) अणु
				sub[s].linfo_idx = i;
				s++;
			पूर्ण अन्यथा अगर (sub[s].start < linfo[i].insn_off) अणु
				verbose(env, "missing bpf_line_info for func#%u\n", s);
				err = -EINVAL;
				जाओ err_मुक्त;
			पूर्ण
		पूर्ण

		prev_offset = linfo[i].insn_off;
		ulinfo += rec_size;
	पूर्ण

	अगर (s != env->subprog_cnt) अणु
		verbose(env, "missing bpf_line_info for %u funcs starting from func#%u\n",
			env->subprog_cnt - s, s);
		err = -EINVAL;
		जाओ err_मुक्त;
	पूर्ण

	prog->aux->linfo = linfo;
	prog->aux->nr_linfo = nr_linfo;

	वापस 0;

err_मुक्त:
	kvमुक्त(linfo);
	वापस err;
पूर्ण

अटल पूर्णांक check_btf_info(काष्ठा bpf_verअगरier_env *env,
			  स्थिर जोड़ bpf_attr *attr,
			  जोड़ bpf_attr __user *uattr)
अणु
	काष्ठा btf *btf;
	पूर्णांक err;

	अगर (!attr->func_info_cnt && !attr->line_info_cnt) अणु
		अगर (check_abnormal_वापस(env))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	btf = btf_get_by_fd(attr->prog_btf_fd);
	अगर (IS_ERR(btf))
		वापस PTR_ERR(btf);
	अगर (btf_is_kernel(btf)) अणु
		btf_put(btf);
		वापस -EACCES;
	पूर्ण
	env->prog->aux->btf = btf;

	err = check_btf_func(env, attr, uattr);
	अगर (err)
		वापस err;

	err = check_btf_line(env, attr, uattr);
	अगर (err)
		वापस err;

	वापस 0;
पूर्ण

/* check %cur's range satisfies %old's */
अटल bool range_within(काष्ठा bpf_reg_state *old,
			 काष्ठा bpf_reg_state *cur)
अणु
	वापस old->umin_value <= cur->umin_value &&
	       old->umax_value >= cur->umax_value &&
	       old->smin_value <= cur->smin_value &&
	       old->smax_value >= cur->smax_value &&
	       old->u32_min_value <= cur->u32_min_value &&
	       old->u32_max_value >= cur->u32_max_value &&
	       old->s32_min_value <= cur->s32_min_value &&
	       old->s32_max_value >= cur->s32_max_value;
पूर्ण

/* Maximum number of रेजिस्टर states that can exist at once */
#घोषणा ID_MAP_SIZE	(MAX_BPF_REG + MAX_BPF_STACK / BPF_REG_SIZE)
काष्ठा idpair अणु
	u32 old;
	u32 cur;
पूर्ण;

/* If in the old state two रेजिस्टरs had the same id, then they need to have
 * the same id in the new state as well.  But that id could be dअगरferent from
 * the old state, so we need to track the mapping from old to new ids.
 * Once we have seen that, say, a reg with old id 5 had new id 9, any subsequent
 * regs with old id 5 must also have new id 9 क्रम the new state to be safe.  But
 * regs with a dअगरferent old id could still have new id 9, we करोn't care about
 * that.
 * So we look through our idmap to see अगर this old id has been seen beक्रमe.  If
 * so, we require the new id to match; otherwise, we add the id pair to the map.
 */
अटल bool check_ids(u32 old_id, u32 cur_id, काष्ठा idpair *idmap)
अणु
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < ID_MAP_SIZE; i++) अणु
		अगर (!idmap[i].old) अणु
			/* Reached an empty slot; haven't seen this id beक्रमe */
			idmap[i].old = old_id;
			idmap[i].cur = cur_id;
			वापस true;
		पूर्ण
		अगर (idmap[i].old == old_id)
			वापस idmap[i].cur == cur_id;
	पूर्ण
	/* We ran out of idmap slots, which should be impossible */
	WARN_ON_ONCE(1);
	वापस false;
पूर्ण

अटल व्योम clean_func_state(काष्ठा bpf_verअगरier_env *env,
			     काष्ठा bpf_func_state *st)
अणु
	क्रमागत bpf_reg_liveness live;
	पूर्णांक i, j;

	क्रम (i = 0; i < BPF_REG_FP; i++) अणु
		live = st->regs[i].live;
		/* liveness must not touch this रेजिस्टर anymore */
		st->regs[i].live |= REG_LIVE_DONE;
		अगर (!(live & REG_LIVE_READ))
			/* since the रेजिस्टर is unused, clear its state
			 * to make further comparison simpler
			 */
			__mark_reg_not_init(env, &st->regs[i]);
	पूर्ण

	क्रम (i = 0; i < st->allocated_stack / BPF_REG_SIZE; i++) अणु
		live = st->stack[i].spilled_ptr.live;
		/* liveness must not touch this stack slot anymore */
		st->stack[i].spilled_ptr.live |= REG_LIVE_DONE;
		अगर (!(live & REG_LIVE_READ)) अणु
			__mark_reg_not_init(env, &st->stack[i].spilled_ptr);
			क्रम (j = 0; j < BPF_REG_SIZE; j++)
				st->stack[i].slot_type[j] = STACK_INVALID;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम clean_verअगरier_state(काष्ठा bpf_verअगरier_env *env,
				 काष्ठा bpf_verअगरier_state *st)
अणु
	पूर्णांक i;

	अगर (st->frame[0]->regs[0].live & REG_LIVE_DONE)
		/* all regs in this state in all frames were alपढ़ोy marked */
		वापस;

	क्रम (i = 0; i <= st->curframe; i++)
		clean_func_state(env, st->frame[i]);
पूर्ण

/* the parentage chains क्रमm a tree.
 * the verअगरier states are added to state lists at given insn and
 * pushed पूर्णांकo state stack क्रम future exploration.
 * when the verअगरier reaches bpf_निकास insn some of the verअगरer states
 * stored in the state lists have their final liveness state alपढ़ोy,
 * but a lot of states will get revised from liveness poपूर्णांक of view when
 * the verअगरier explores other branches.
 * Example:
 * 1: r0 = 1
 * 2: अगर r1 == 100 जाओ pc+1
 * 3: r0 = 2
 * 4: निकास
 * when the verअगरier reaches निकास insn the रेजिस्टर r0 in the state list of
 * insn 2 will be seen as !REG_LIVE_READ. Then the verअगरier pops the other_branch
 * of insn 2 and goes exploring further. At the insn 4 it will walk the
 * parentage chain from insn 4 पूर्णांकo insn 2 and will mark r0 as REG_LIVE_READ.
 *
 * Since the verअगरier pushes the branch states as it sees them जबतक exploring
 * the program the condition of walking the branch inकाष्ठाion क्रम the second
 * समय means that all states below this branch were alपढ़ोy explored and
 * their final liveness markes are alपढ़ोy propagated.
 * Hence when the verअगरier completes the search of state list in is_state_visited()
 * we can call this clean_live_states() function to mark all liveness states
 * as REG_LIVE_DONE to indicate that 'parent' pointers of 'struct bpf_reg_state'
 * will not be used.
 * This function also clears the रेजिस्टरs and stack क्रम states that !READ
 * to simplअगरy state merging.
 *
 * Important note here that walking the same branch inकाष्ठाion in the callee
 * करोesn't meant that the states are DONE. The verअगरier has to compare
 * the callsites
 */
अटल व्योम clean_live_states(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn,
			      काष्ठा bpf_verअगरier_state *cur)
अणु
	काष्ठा bpf_verअगरier_state_list *sl;
	पूर्णांक i;

	sl = *explored_state(env, insn);
	जबतक (sl) अणु
		अगर (sl->state.branches)
			जाओ next;
		अगर (sl->state.insn_idx != insn ||
		    sl->state.curframe != cur->curframe)
			जाओ next;
		क्रम (i = 0; i <= cur->curframe; i++)
			अगर (sl->state.frame[i]->callsite != cur->frame[i]->callsite)
				जाओ next;
		clean_verअगरier_state(env, &sl->state);
next:
		sl = sl->next;
	पूर्ण
पूर्ण

/* Returns true अगर (rold safe implies rcur safe) */
अटल bool regsafe(काष्ठा bpf_reg_state *rold, काष्ठा bpf_reg_state *rcur,
		    काष्ठा idpair *idmap)
अणु
	bool equal;

	अगर (!(rold->live & REG_LIVE_READ))
		/* explored state didn't use this */
		वापस true;

	equal = स_भेद(rold, rcur, दुरत्व(काष्ठा bpf_reg_state, parent)) == 0;

	अगर (rold->type == PTR_TO_STACK)
		/* two stack poपूर्णांकers are equal only अगर they're poपूर्णांकing to
		 * the same stack frame, since fp-8 in foo != fp-8 in bar
		 */
		वापस equal && rold->frameno == rcur->frameno;

	अगर (equal)
		वापस true;

	अगर (rold->type == NOT_INIT)
		/* explored state can't have used this */
		वापस true;
	अगर (rcur->type == NOT_INIT)
		वापस false;
	चयन (rold->type) अणु
	हाल SCALAR_VALUE:
		अगर (rcur->type == SCALAR_VALUE) अणु
			अगर (!rold->precise && !rcur->precise)
				वापस true;
			/* new val must satisfy old val knowledge */
			वापस range_within(rold, rcur) &&
			       tnum_in(rold->var_off, rcur->var_off);
		पूर्ण अन्यथा अणु
			/* We're trying to use a poपूर्णांकer in place of a scalar.
			 * Even अगर the scalar was unbounded, this could lead to
			 * poपूर्णांकer leaks because scalars are allowed to leak
			 * जबतक poपूर्णांकers are not. We could make this safe in
			 * special हालs अगर root is calling us, but it's
			 * probably not worth the hassle.
			 */
			वापस false;
		पूर्ण
	हाल PTR_TO_MAP_KEY:
	हाल PTR_TO_MAP_VALUE:
		/* If the new min/max/var_off satisfy the old ones and
		 * everything अन्यथा matches, we are OK.
		 * 'id' is not compared, since it's only used क्रम maps with
		 * bpf_spin_lock inside map element and in such हालs अगर
		 * the rest of the prog is valid क्रम one map element then
		 * it's valid क्रम all map elements regardless of the key
		 * used in bpf_map_lookup()
		 */
		वापस स_भेद(rold, rcur, दुरत्व(काष्ठा bpf_reg_state, id)) == 0 &&
		       range_within(rold, rcur) &&
		       tnum_in(rold->var_off, rcur->var_off);
	हाल PTR_TO_MAP_VALUE_OR_शून्य:
		/* a PTR_TO_MAP_VALUE could be safe to use as a
		 * PTR_TO_MAP_VALUE_OR_शून्य पूर्णांकo the same map.
		 * However, अगर the old PTR_TO_MAP_VALUE_OR_शून्य then got शून्य-
		 * checked, करोing so could have affected others with the same
		 * id, and we can't check क्रम that because we lost the id when
		 * we converted to a PTR_TO_MAP_VALUE.
		 */
		अगर (rcur->type != PTR_TO_MAP_VALUE_OR_शून्य)
			वापस false;
		अगर (स_भेद(rold, rcur, दुरत्व(काष्ठा bpf_reg_state, id)))
			वापस false;
		/* Check our ids match any regs they're supposed to */
		वापस check_ids(rold->id, rcur->id, idmap);
	हाल PTR_TO_PACKET_META:
	हाल PTR_TO_PACKET:
		अगर (rcur->type != rold->type)
			वापस false;
		/* We must have at least as much range as the old ptr
		 * did, so that any accesses which were safe beक्रमe are
		 * still safe.  This is true even अगर old range < old off,
		 * since someone could have accessed through (ptr - k), or
		 * even करोne ptr -= k in a रेजिस्टर, to get a safe access.
		 */
		अगर (rold->range > rcur->range)
			वापस false;
		/* If the offsets करोn't match, we can't trust our alignment;
		 * nor can we be sure that we won't fall out of range.
		 */
		अगर (rold->off != rcur->off)
			वापस false;
		/* id relations must be preserved */
		अगर (rold->id && !check_ids(rold->id, rcur->id, idmap))
			वापस false;
		/* new val must satisfy old val knowledge */
		वापस range_within(rold, rcur) &&
		       tnum_in(rold->var_off, rcur->var_off);
	हाल PTR_TO_CTX:
	हाल CONST_PTR_TO_MAP:
	हाल PTR_TO_PACKET_END:
	हाल PTR_TO_FLOW_KEYS:
	हाल PTR_TO_SOCKET:
	हाल PTR_TO_SOCKET_OR_शून्य:
	हाल PTR_TO_SOCK_COMMON:
	हाल PTR_TO_SOCK_COMMON_OR_शून्य:
	हाल PTR_TO_TCP_SOCK:
	हाल PTR_TO_TCP_SOCK_OR_शून्य:
	हाल PTR_TO_XDP_SOCK:
		/* Only valid matches are exact, which स_भेद() above
		 * would have accepted
		 */
	शेष:
		/* Don't know what's going on, just say it's not safe */
		वापस false;
	पूर्ण

	/* Shouldn't get here; if we do, say it's not safe */
	WARN_ON_ONCE(1);
	वापस false;
पूर्ण

अटल bool stacksafe(काष्ठा bpf_func_state *old,
		      काष्ठा bpf_func_state *cur,
		      काष्ठा idpair *idmap)
अणु
	पूर्णांक i, spi;

	/* walk slots of the explored stack and ignore any additional
	 * slots in the current stack, since explored(safe) state
	 * didn't use them
	 */
	क्रम (i = 0; i < old->allocated_stack; i++) अणु
		spi = i / BPF_REG_SIZE;

		अगर (!(old->stack[spi].spilled_ptr.live & REG_LIVE_READ)) अणु
			i += BPF_REG_SIZE - 1;
			/* explored state didn't use this */
			जारी;
		पूर्ण

		अगर (old->stack[spi].slot_type[i % BPF_REG_SIZE] == STACK_INVALID)
			जारी;

		/* explored stack has more populated slots than current stack
		 * and these slots were used
		 */
		अगर (i >= cur->allocated_stack)
			वापस false;

		/* अगर old state was safe with misc data in the stack
		 * it will be safe with zero-initialized stack.
		 * The opposite is not true
		 */
		अगर (old->stack[spi].slot_type[i % BPF_REG_SIZE] == STACK_MISC &&
		    cur->stack[spi].slot_type[i % BPF_REG_SIZE] == STACK_ZERO)
			जारी;
		अगर (old->stack[spi].slot_type[i % BPF_REG_SIZE] !=
		    cur->stack[spi].slot_type[i % BPF_REG_SIZE])
			/* Ex: old explored (safe) state has STACK_SPILL in
			 * this stack slot, but current has STACK_MISC ->
			 * this verअगरier states are not equivalent,
			 * वापस false to जारी verअगरication of this path
			 */
			वापस false;
		अगर (i % BPF_REG_SIZE)
			जारी;
		अगर (old->stack[spi].slot_type[0] != STACK_SPILL)
			जारी;
		अगर (!regsafe(&old->stack[spi].spilled_ptr,
			     &cur->stack[spi].spilled_ptr,
			     idmap))
			/* when explored and current stack slot are both storing
			 * spilled रेजिस्टरs, check that stored poपूर्णांकers types
			 * are the same as well.
			 * Ex: explored safe path could have stored
			 * (bpf_reg_state) अणु.type = PTR_TO_STACK, .off = -8पूर्ण
			 * but current path has stored:
			 * (bpf_reg_state) अणु.type = PTR_TO_STACK, .off = -16पूर्ण
			 * such verअगरier states are not equivalent.
			 * वापस false to जारी verअगरication of this path
			 */
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

अटल bool refsafe(काष्ठा bpf_func_state *old, काष्ठा bpf_func_state *cur)
अणु
	अगर (old->acquired_refs != cur->acquired_refs)
		वापस false;
	वापस !स_भेद(old->refs, cur->refs,
		       माप(*old->refs) * old->acquired_refs);
पूर्ण

/* compare two verअगरier states
 *
 * all states stored in state_list are known to be valid, since
 * verअगरier reached 'bpf_exit' inकाष्ठाion through them
 *
 * this function is called when verअगरier exploring dअगरferent branches of
 * execution popped from the state stack. If it sees an old state that has
 * more strict रेजिस्टर state and more strict stack state then this execution
 * branch करोesn't need to be explored further, since verअगरier alपढ़ोy
 * concluded that more strict state leads to valid finish.
 *
 * Thereक्रमe two states are equivalent अगर रेजिस्टर state is more conservative
 * and explored stack state is more conservative than the current one.
 * Example:
 *       explored                   current
 * (slot1=INV slot2=MISC) == (slot1=MISC slot2=MISC)
 * (slot1=MISC slot2=MISC) != (slot1=INV slot2=MISC)
 *
 * In other words अगर current stack state (one being explored) has more
 * valid slots than old one that alपढ़ोy passed validation, it means
 * the verअगरier can stop exploring and conclude that current state is valid too
 *
 * Similarly with रेजिस्टरs. If explored state has रेजिस्टर type as invalid
 * whereas रेजिस्टर type in current state is meaningful, it means that
 * the current state will reach 'bpf_exit' inकाष्ठाion safely
 */
अटल bool func_states_equal(काष्ठा bpf_func_state *old,
			      काष्ठा bpf_func_state *cur)
अणु
	काष्ठा idpair *idmap;
	bool ret = false;
	पूर्णांक i;

	idmap = kसुस्मृति(ID_MAP_SIZE, माप(काष्ठा idpair), GFP_KERNEL);
	/* If we failed to allocate the idmap, just say it's not safe */
	अगर (!idmap)
		वापस false;

	क्रम (i = 0; i < MAX_BPF_REG; i++) अणु
		अगर (!regsafe(&old->regs[i], &cur->regs[i], idmap))
			जाओ out_मुक्त;
	पूर्ण

	अगर (!stacksafe(old, cur, idmap))
		जाओ out_मुक्त;

	अगर (!refsafe(old, cur))
		जाओ out_मुक्त;
	ret = true;
out_मुक्त:
	kमुक्त(idmap);
	वापस ret;
पूर्ण

अटल bool states_equal(काष्ठा bpf_verअगरier_env *env,
			 काष्ठा bpf_verअगरier_state *old,
			 काष्ठा bpf_verअगरier_state *cur)
अणु
	पूर्णांक i;

	अगर (old->curframe != cur->curframe)
		वापस false;

	/* Verअगरication state from speculative execution simulation
	 * must never prune a non-speculative execution one.
	 */
	अगर (old->speculative && !cur->speculative)
		वापस false;

	अगर (old->active_spin_lock != cur->active_spin_lock)
		वापस false;

	/* क्रम states to be equal callsites have to be the same
	 * and all frame states need to be equivalent
	 */
	क्रम (i = 0; i <= old->curframe; i++) अणु
		अगर (old->frame[i]->callsite != cur->frame[i]->callsite)
			वापस false;
		अगर (!func_states_equal(old->frame[i], cur->frame[i]))
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Return 0 अगर no propagation happened. Return negative error code अगर error
 * happened. Otherwise, वापस the propagated bit.
 */
अटल पूर्णांक propagate_liveness_reg(काष्ठा bpf_verअगरier_env *env,
				  काष्ठा bpf_reg_state *reg,
				  काष्ठा bpf_reg_state *parent_reg)
अणु
	u8 parent_flag = parent_reg->live & REG_LIVE_READ;
	u8 flag = reg->live & REG_LIVE_READ;
	पूर्णांक err;

	/* When comes here, पढ़ो flags of PARENT_REG or REG could be any of
	 * REG_LIVE_READ64, REG_LIVE_READ32, REG_LIVE_NONE. There is no need
	 * of propagation अगर PARENT_REG has strongest REG_LIVE_READ64.
	 */
	अगर (parent_flag == REG_LIVE_READ64 ||
	    /* Or अगर there is no पढ़ो flag from REG. */
	    !flag ||
	    /* Or अगर the पढ़ो flag from REG is the same as PARENT_REG. */
	    parent_flag == flag)
		वापस 0;

	err = mark_reg_पढ़ो(env, reg, parent_reg, flag);
	अगर (err)
		वापस err;

	वापस flag;
पूर्ण

/* A ग_लिखो screens off any subsequent पढ़ोs; but ग_लिखो marks come from the
 * straight-line code between a state and its parent.  When we arrive at an
 * equivalent state (jump target or such) we didn't arrive by the straight-line
 * code, so पढ़ो marks in the state must propagate to the parent regardless
 * of the state's write marks. That's what 'parent == state->parent' comparison
 * in mark_reg_पढ़ो() is क्रम.
 */
अटल पूर्णांक propagate_liveness(काष्ठा bpf_verअगरier_env *env,
			      स्थिर काष्ठा bpf_verअगरier_state *vstate,
			      काष्ठा bpf_verअगरier_state *vparent)
अणु
	काष्ठा bpf_reg_state *state_reg, *parent_reg;
	काष्ठा bpf_func_state *state, *parent;
	पूर्णांक i, frame, err = 0;

	अगर (vparent->curframe != vstate->curframe) अणु
		WARN(1, "propagate_live: parent frame %d current frame %d\n",
		     vparent->curframe, vstate->curframe);
		वापस -EFAULT;
	पूर्ण
	/* Propagate पढ़ो liveness of रेजिस्टरs... */
	BUILD_BUG_ON(BPF_REG_FP + 1 != MAX_BPF_REG);
	क्रम (frame = 0; frame <= vstate->curframe; frame++) अणु
		parent = vparent->frame[frame];
		state = vstate->frame[frame];
		parent_reg = parent->regs;
		state_reg = state->regs;
		/* We करोn't need to worry about FP liveness, it's पढ़ो-only */
		क्रम (i = frame < vstate->curframe ? BPF_REG_6 : 0; i < BPF_REG_FP; i++) अणु
			err = propagate_liveness_reg(env, &state_reg[i],
						     &parent_reg[i]);
			अगर (err < 0)
				वापस err;
			अगर (err == REG_LIVE_READ64)
				mark_insn_zext(env, &parent_reg[i]);
		पूर्ण

		/* Propagate stack slots. */
		क्रम (i = 0; i < state->allocated_stack / BPF_REG_SIZE &&
			    i < parent->allocated_stack / BPF_REG_SIZE; i++) अणु
			parent_reg = &parent->stack[i].spilled_ptr;
			state_reg = &state->stack[i].spilled_ptr;
			err = propagate_liveness_reg(env, state_reg,
						     parent_reg);
			अगर (err < 0)
				वापस err;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* find precise scalars in the previous equivalent state and
 * propagate them पूर्णांकo the current state
 */
अटल पूर्णांक propagate_precision(काष्ठा bpf_verअगरier_env *env,
			       स्थिर काष्ठा bpf_verअगरier_state *old)
अणु
	काष्ठा bpf_reg_state *state_reg;
	काष्ठा bpf_func_state *state;
	पूर्णांक i, err = 0;

	state = old->frame[old->curframe];
	state_reg = state->regs;
	क्रम (i = 0; i < BPF_REG_FP; i++, state_reg++) अणु
		अगर (state_reg->type != SCALAR_VALUE ||
		    !state_reg->precise)
			जारी;
		अगर (env->log.level & BPF_LOG_LEVEL2)
			verbose(env, "propagating r%d\n", i);
		err = mark_chain_precision(env, i);
		अगर (err < 0)
			वापस err;
	पूर्ण

	क्रम (i = 0; i < state->allocated_stack / BPF_REG_SIZE; i++) अणु
		अगर (state->stack[i].slot_type[0] != STACK_SPILL)
			जारी;
		state_reg = &state->stack[i].spilled_ptr;
		अगर (state_reg->type != SCALAR_VALUE ||
		    !state_reg->precise)
			जारी;
		अगर (env->log.level & BPF_LOG_LEVEL2)
			verbose(env, "propagating fp%d\n",
				(-i - 1) * BPF_REG_SIZE);
		err = mark_chain_precision_stack(env, i);
		अगर (err < 0)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल bool states_maybe_looping(काष्ठा bpf_verअगरier_state *old,
				 काष्ठा bpf_verअगरier_state *cur)
अणु
	काष्ठा bpf_func_state *fold, *fcur;
	पूर्णांक i, fr = cur->curframe;

	अगर (old->curframe != fr)
		वापस false;

	fold = old->frame[fr];
	fcur = cur->frame[fr];
	क्रम (i = 0; i < MAX_BPF_REG; i++)
		अगर (स_भेद(&fold->regs[i], &fcur->regs[i],
			   दुरत्व(काष्ठा bpf_reg_state, parent)))
			वापस false;
	वापस true;
पूर्ण


अटल पूर्णांक is_state_visited(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx)
अणु
	काष्ठा bpf_verअगरier_state_list *new_sl;
	काष्ठा bpf_verअगरier_state_list *sl, **pprev;
	काष्ठा bpf_verअगरier_state *cur = env->cur_state, *new;
	पूर्णांक i, j, err, states_cnt = 0;
	bool add_new_state = env->test_state_freq ? true : false;

	cur->last_insn_idx = env->prev_insn_idx;
	अगर (!env->insn_aux_data[insn_idx].prune_poपूर्णांक)
		/* this 'insn_idx' instruction wasn't marked, so we will not
		 * be करोing state search here
		 */
		वापस 0;

	/* bpf progs typically have pruning poपूर्णांक every 4 inकाष्ठाions
	 * http://vger.kernel.org/bpfconf2019.hपंचांगl#session-1
	 * Do not add new state क्रम future pruning अगर the verअगरier hasn't seen
	 * at least 2 jumps and at least 8 inकाष्ठाions.
	 * This heuristics helps decrease 'total_states' and 'peak_states' metric.
	 * In tests that amounts to up to 50% reduction पूर्णांकo total verअगरier
	 * memory consumption and 20% verअगरier समय speedup.
	 */
	अगर (env->jmps_processed - env->prev_jmps_processed >= 2 &&
	    env->insn_processed - env->prev_insn_processed >= 8)
		add_new_state = true;

	pprev = explored_state(env, insn_idx);
	sl = *pprev;

	clean_live_states(env, insn_idx, cur);

	जबतक (sl) अणु
		states_cnt++;
		अगर (sl->state.insn_idx != insn_idx)
			जाओ next;
		अगर (sl->state.branches) अणु
			अगर (states_maybe_looping(&sl->state, cur) &&
			    states_equal(env, &sl->state, cur)) अणु
				verbose_linfo(env, insn_idx, "; ");
				verbose(env, "infinite loop detected at insn %d\n", insn_idx);
				वापस -EINVAL;
			पूर्ण
			/* अगर the verअगरier is processing a loop, aव्योम adding new state
			 * too often, since dअगरferent loop iterations have distinct
			 * states and may not help future pruning.
			 * This threshold shouldn't be too low to make sure that
			 * a loop with large bound will be rejected quickly.
			 * The most abusive loop will be:
			 * r1 += 1
			 * अगर r1 < 1000000 जाओ pc-2
			 * 1M insn_procssed limit / 100 == 10k peak states.
			 * This threshold shouldn't be too high either, since states
			 * at the end of the loop are likely to be useful in pruning.
			 */
			अगर (env->jmps_processed - env->prev_jmps_processed < 20 &&
			    env->insn_processed - env->prev_insn_processed < 100)
				add_new_state = false;
			जाओ miss;
		पूर्ण
		अगर (states_equal(env, &sl->state, cur)) अणु
			sl->hit_cnt++;
			/* reached equivalent रेजिस्टर/stack state,
			 * prune the search.
			 * Registers पढ़ो by the continuation are पढ़ो by us.
			 * If we have any ग_लिखो marks in env->cur_state, they
			 * will prevent corresponding पढ़ोs in the continuation
			 * from reaching our parent (an explored_state).  Our
			 * own state will get the पढ़ो marks recorded, but
			 * they'll be immediately forgotten as we're pruning
			 * this state and will pop a new one.
			 */
			err = propagate_liveness(env, &sl->state, cur);

			/* अगर previous state reached the निकास with precision and
			 * current state is equivalent to it (except precsion marks)
			 * the precision needs to be propagated back in
			 * the current state.
			 */
			err = err ? : push_jmp_history(env, cur);
			err = err ? : propagate_precision(env, &sl->state);
			अगर (err)
				वापस err;
			वापस 1;
		पूर्ण
miss:
		/* when new state is not going to be added करो not increase miss count.
		 * Otherwise several loop iterations will हटाओ the state
		 * recorded earlier. The goal of these heuristics is to have
		 * states from some iterations of the loop (some in the beginning
		 * and some at the end) to help pruning.
		 */
		अगर (add_new_state)
			sl->miss_cnt++;
		/* heuristic to determine whether this state is beneficial
		 * to keep checking from state equivalence poपूर्णांक of view.
		 * Higher numbers increase max_states_per_insn and verअगरication समय,
		 * but करो not meaningfully decrease insn_processed.
		 */
		अगर (sl->miss_cnt > sl->hit_cnt * 3 + 3) अणु
			/* the state is unlikely to be useful. Remove it to
			 * speed up verअगरication
			 */
			*pprev = sl->next;
			अगर (sl->state.frame[0]->regs[0].live & REG_LIVE_DONE) अणु
				u32 br = sl->state.branches;

				WARN_ONCE(br,
					  "BUG live_done but branches_to_explore %d\n",
					  br);
				मुक्त_verअगरier_state(&sl->state, false);
				kमुक्त(sl);
				env->peak_states--;
			पूर्ण अन्यथा अणु
				/* cannot मुक्त this state, since parentage chain may
				 * walk it later. Add it क्रम मुक्त_list instead to
				 * be मुक्तd at the end of verअगरication
				 */
				sl->next = env->मुक्त_list;
				env->मुक्त_list = sl;
			पूर्ण
			sl = *pprev;
			जारी;
		पूर्ण
next:
		pprev = &sl->next;
		sl = *pprev;
	पूर्ण

	अगर (env->max_states_per_insn < states_cnt)
		env->max_states_per_insn = states_cnt;

	अगर (!env->bpf_capable && states_cnt > BPF_COMPLEXITY_LIMIT_STATES)
		वापस push_jmp_history(env, cur);

	अगर (!add_new_state)
		वापस push_jmp_history(env, cur);

	/* There were no equivalent states, remember the current one.
	 * Technically the current state is not proven to be safe yet,
	 * but it will either reach outer most bpf_निकास (which means it's safe)
	 * or it will be rejected. When there are no loops the verअगरier won't be
	 * seeing this tuple (frame[0].callsite, frame[1].callsite, .. insn_idx)
	 * again on the way to bpf_निकास.
	 * When looping the sl->state.branches will be > 0 and this state
	 * will not be considered क्रम equivalence until branches == 0.
	 */
	new_sl = kzalloc(माप(काष्ठा bpf_verअगरier_state_list), GFP_KERNEL);
	अगर (!new_sl)
		वापस -ENOMEM;
	env->total_states++;
	env->peak_states++;
	env->prev_jmps_processed = env->jmps_processed;
	env->prev_insn_processed = env->insn_processed;

	/* add new state to the head of linked list */
	new = &new_sl->state;
	err = copy_verअगरier_state(new, cur);
	अगर (err) अणु
		मुक्त_verअगरier_state(new, false);
		kमुक्त(new_sl);
		वापस err;
	पूर्ण
	new->insn_idx = insn_idx;
	WARN_ONCE(new->branches != 1,
		  "BUG is_state_visited:branches_to_explore=%d insn %d\n", new->branches, insn_idx);

	cur->parent = new;
	cur->first_insn_idx = insn_idx;
	clear_jmp_history(cur);
	new_sl->next = *explored_state(env, insn_idx);
	*explored_state(env, insn_idx) = new_sl;
	/* connect new state to parentage chain. Current frame needs all
	 * रेजिस्टरs connected. Only r6 - r9 of the callers are alive (pushed
	 * to the stack implicitly by JITs) so in callers' frames connect just
	 * r6 - r9 as an optimization. Callers will have r1 - r5 connected to
	 * the state of the call inकाष्ठाion (with WRITTEN set), and r0 comes
	 * from callee with its full parentage chain, anyway.
	 */
	/* clear ग_लिखो marks in current state: the ग_लिखोs we did are not ग_लिखोs
	 * our child did, so they करोn't screen off its पढ़ोs from us.
	 * (There are no पढ़ो marks in current state, because पढ़ोs always mark
	 * their parent and current state never has children yet.  Only
	 * explored_states can get पढ़ो marks.)
	 */
	क्रम (j = 0; j <= cur->curframe; j++) अणु
		क्रम (i = j < cur->curframe ? BPF_REG_6 : 0; i < BPF_REG_FP; i++)
			cur->frame[j]->regs[i].parent = &new->frame[j]->regs[i];
		क्रम (i = 0; i < BPF_REG_FP; i++)
			cur->frame[j]->regs[i].live = REG_LIVE_NONE;
	पूर्ण

	/* all stack frames are accessible from callee, clear them all */
	क्रम (j = 0; j <= cur->curframe; j++) अणु
		काष्ठा bpf_func_state *frame = cur->frame[j];
		काष्ठा bpf_func_state *newframe = new->frame[j];

		क्रम (i = 0; i < frame->allocated_stack / BPF_REG_SIZE; i++) अणु
			frame->stack[i].spilled_ptr.live = REG_LIVE_NONE;
			frame->stack[i].spilled_ptr.parent =
						&newframe->stack[i].spilled_ptr;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* Return true अगर it's OK to have the same insn वापस a dअगरferent type. */
अटल bool reg_type_mismatch_ok(क्रमागत bpf_reg_type type)
अणु
	चयन (type) अणु
	हाल PTR_TO_CTX:
	हाल PTR_TO_SOCKET:
	हाल PTR_TO_SOCKET_OR_शून्य:
	हाल PTR_TO_SOCK_COMMON:
	हाल PTR_TO_SOCK_COMMON_OR_शून्य:
	हाल PTR_TO_TCP_SOCK:
	हाल PTR_TO_TCP_SOCK_OR_शून्य:
	हाल PTR_TO_XDP_SOCK:
	हाल PTR_TO_BTF_ID:
	हाल PTR_TO_BTF_ID_OR_शून्य:
		वापस false;
	शेष:
		वापस true;
	पूर्ण
पूर्ण

/* If an inकाष्ठाion was previously used with particular poपूर्णांकer types, then we
 * need to be careful to aव्योम हालs such as the below, where it may be ok
 * क्रम one branch accessing the poपूर्णांकer, but not ok क्रम the other branch:
 *
 * R1 = sock_ptr
 * जाओ X;
 * ...
 * R1 = some_other_valid_ptr;
 * जाओ X;
 * ...
 * R2 = *(u32 *)(R1 + 0);
 */
अटल bool reg_type_mismatch(क्रमागत bpf_reg_type src, क्रमागत bpf_reg_type prev)
अणु
	वापस src != prev && (!reg_type_mismatch_ok(src) ||
			       !reg_type_mismatch_ok(prev));
पूर्ण

अटल पूर्णांक करो_check(काष्ठा bpf_verअगरier_env *env)
अणु
	bool pop_log = !(env->log.level & BPF_LOG_LEVEL2);
	काष्ठा bpf_verअगरier_state *state = env->cur_state;
	काष्ठा bpf_insn *insns = env->prog->insnsi;
	काष्ठा bpf_reg_state *regs;
	पूर्णांक insn_cnt = env->prog->len;
	bool करो_prपूर्णांक_state = false;
	पूर्णांक prev_insn_idx = -1;

	क्रम (;;) अणु
		काष्ठा bpf_insn *insn;
		u8 class;
		पूर्णांक err;

		env->prev_insn_idx = prev_insn_idx;
		अगर (env->insn_idx >= insn_cnt) अणु
			verbose(env, "invalid insn idx %d insn_cnt %d\n",
				env->insn_idx, insn_cnt);
			वापस -EFAULT;
		पूर्ण

		insn = &insns[env->insn_idx];
		class = BPF_CLASS(insn->code);

		अगर (++env->insn_processed > BPF_COMPLEXITY_LIMIT_INSNS) अणु
			verbose(env,
				"BPF program is too large. Processed %d insn\n",
				env->insn_processed);
			वापस -E2BIG;
		पूर्ण

		err = is_state_visited(env, env->insn_idx);
		अगर (err < 0)
			वापस err;
		अगर (err == 1) अणु
			/* found equivalent state, can prune the search */
			अगर (env->log.level & BPF_LOG_LEVEL) अणु
				अगर (करो_prपूर्णांक_state)
					verbose(env, "\nfrom %d to %d%s: safe\n",
						env->prev_insn_idx, env->insn_idx,
						env->cur_state->speculative ?
						" (speculative execution)" : "");
				अन्यथा
					verbose(env, "%d: safe\n", env->insn_idx);
			पूर्ण
			जाओ process_bpf_निकास;
		पूर्ण

		अगर (संकेत_pending(current))
			वापस -EAGAIN;

		अगर (need_resched())
			cond_resched();

		अगर (env->log.level & BPF_LOG_LEVEL2 ||
		    (env->log.level & BPF_LOG_LEVEL && करो_prपूर्णांक_state)) अणु
			अगर (env->log.level & BPF_LOG_LEVEL2)
				verbose(env, "%d:", env->insn_idx);
			अन्यथा
				verbose(env, "\nfrom %d to %d%s:",
					env->prev_insn_idx, env->insn_idx,
					env->cur_state->speculative ?
					" (speculative execution)" : "");
			prपूर्णांक_verअगरier_state(env, state->frame[state->curframe]);
			करो_prपूर्णांक_state = false;
		पूर्ण

		अगर (env->log.level & BPF_LOG_LEVEL) अणु
			स्थिर काष्ठा bpf_insn_cbs cbs = अणु
				.cb_call	= disयंत्र_kfunc_name,
				.cb_prपूर्णांक	= verbose,
				.निजी_data	= env,
			पूर्ण;

			verbose_linfo(env, env->insn_idx, "; ");
			verbose(env, "%d: ", env->insn_idx);
			prपूर्णांक_bpf_insn(&cbs, insn, env->allow_ptr_leaks);
		पूर्ण

		अगर (bpf_prog_is_dev_bound(env->prog->aux)) अणु
			err = bpf_prog_offload_verअगरy_insn(env, env->insn_idx,
							   env->prev_insn_idx);
			अगर (err)
				वापस err;
		पूर्ण

		regs = cur_regs(env);
		sanitize_mark_insn_seen(env);
		prev_insn_idx = env->insn_idx;

		अगर (class == BPF_ALU || class == BPF_ALU64) अणु
			err = check_alu_op(env, insn);
			अगर (err)
				वापस err;

		पूर्ण अन्यथा अगर (class == BPF_LDX) अणु
			क्रमागत bpf_reg_type *prev_src_type, src_reg_type;

			/* check क्रम reserved fields is alपढ़ोy करोne */

			/* check src opeअक्रम */
			err = check_reg_arg(env, insn->src_reg, SRC_OP);
			अगर (err)
				वापस err;

			err = check_reg_arg(env, insn->dst_reg, DST_OP_NO_MARK);
			अगर (err)
				वापस err;

			src_reg_type = regs[insn->src_reg].type;

			/* check that memory (src_reg + off) is पढ़ोable,
			 * the state of dst_reg will be updated by this func
			 */
			err = check_mem_access(env, env->insn_idx, insn->src_reg,
					       insn->off, BPF_SIZE(insn->code),
					       BPF_READ, insn->dst_reg, false);
			अगर (err)
				वापस err;

			prev_src_type = &env->insn_aux_data[env->insn_idx].ptr_type;

			अगर (*prev_src_type == NOT_INIT) अणु
				/* saw a valid insn
				 * dst_reg = *(u32 *)(src_reg + off)
				 * save type to validate पूर्णांकersecting paths
				 */
				*prev_src_type = src_reg_type;

			पूर्ण अन्यथा अगर (reg_type_mismatch(src_reg_type, *prev_src_type)) अणु
				/* ABuser program is trying to use the same insn
				 * dst_reg = *(u32*) (src_reg + off)
				 * with dअगरferent poपूर्णांकer types:
				 * src_reg == ctx in one branch and
				 * src_reg == stack|map in some other branch.
				 * Reject it.
				 */
				verbose(env, "same insn cannot be used with different pointers\n");
				वापस -EINVAL;
			पूर्ण

		पूर्ण अन्यथा अगर (class == BPF_STX) अणु
			क्रमागत bpf_reg_type *prev_dst_type, dst_reg_type;

			अगर (BPF_MODE(insn->code) == BPF_ATOMIC) अणु
				err = check_atomic(env, env->insn_idx, insn);
				अगर (err)
					वापस err;
				env->insn_idx++;
				जारी;
			पूर्ण

			अगर (BPF_MODE(insn->code) != BPF_MEM || insn->imm != 0) अणु
				verbose(env, "BPF_STX uses reserved fields\n");
				वापस -EINVAL;
			पूर्ण

			/* check src1 opeअक्रम */
			err = check_reg_arg(env, insn->src_reg, SRC_OP);
			अगर (err)
				वापस err;
			/* check src2 opeअक्रम */
			err = check_reg_arg(env, insn->dst_reg, SRC_OP);
			अगर (err)
				वापस err;

			dst_reg_type = regs[insn->dst_reg].type;

			/* check that memory (dst_reg + off) is ग_लिखोable */
			err = check_mem_access(env, env->insn_idx, insn->dst_reg,
					       insn->off, BPF_SIZE(insn->code),
					       BPF_WRITE, insn->src_reg, false);
			अगर (err)
				वापस err;

			prev_dst_type = &env->insn_aux_data[env->insn_idx].ptr_type;

			अगर (*prev_dst_type == NOT_INIT) अणु
				*prev_dst_type = dst_reg_type;
			पूर्ण अन्यथा अगर (reg_type_mismatch(dst_reg_type, *prev_dst_type)) अणु
				verbose(env, "same insn cannot be used with different pointers\n");
				वापस -EINVAL;
			पूर्ण

		पूर्ण अन्यथा अगर (class == BPF_ST) अणु
			अगर (BPF_MODE(insn->code) != BPF_MEM ||
			    insn->src_reg != BPF_REG_0) अणु
				verbose(env, "BPF_ST uses reserved fields\n");
				वापस -EINVAL;
			पूर्ण
			/* check src opeअक्रम */
			err = check_reg_arg(env, insn->dst_reg, SRC_OP);
			अगर (err)
				वापस err;

			अगर (is_ctx_reg(env, insn->dst_reg)) अणु
				verbose(env, "BPF_ST stores into R%d %s is not allowed\n",
					insn->dst_reg,
					reg_type_str[reg_state(env, insn->dst_reg)->type]);
				वापस -EACCES;
			पूर्ण

			/* check that memory (dst_reg + off) is ग_लिखोable */
			err = check_mem_access(env, env->insn_idx, insn->dst_reg,
					       insn->off, BPF_SIZE(insn->code),
					       BPF_WRITE, -1, false);
			अगर (err)
				वापस err;

		पूर्ण अन्यथा अगर (class == BPF_JMP || class == BPF_JMP32) अणु
			u8 opcode = BPF_OP(insn->code);

			env->jmps_processed++;
			अगर (opcode == BPF_CALL) अणु
				अगर (BPF_SRC(insn->code) != BPF_K ||
				    insn->off != 0 ||
				    (insn->src_reg != BPF_REG_0 &&
				     insn->src_reg != BPF_PSEUDO_CALL &&
				     insn->src_reg != BPF_PSEUDO_KFUNC_CALL) ||
				    insn->dst_reg != BPF_REG_0 ||
				    class == BPF_JMP32) अणु
					verbose(env, "BPF_CALL uses reserved fields\n");
					वापस -EINVAL;
				पूर्ण

				अगर (env->cur_state->active_spin_lock &&
				    (insn->src_reg == BPF_PSEUDO_CALL ||
				     insn->imm != BPF_FUNC_spin_unlock)) अणु
					verbose(env, "function calls are not allowed while holding a lock\n");
					वापस -EINVAL;
				पूर्ण
				अगर (insn->src_reg == BPF_PSEUDO_CALL)
					err = check_func_call(env, insn, &env->insn_idx);
				अन्यथा अगर (insn->src_reg == BPF_PSEUDO_KFUNC_CALL)
					err = check_kfunc_call(env, insn);
				अन्यथा
					err = check_helper_call(env, insn, &env->insn_idx);
				अगर (err)
					वापस err;
			पूर्ण अन्यथा अगर (opcode == BPF_JA) अणु
				अगर (BPF_SRC(insn->code) != BPF_K ||
				    insn->imm != 0 ||
				    insn->src_reg != BPF_REG_0 ||
				    insn->dst_reg != BPF_REG_0 ||
				    class == BPF_JMP32) अणु
					verbose(env, "BPF_JA uses reserved fields\n");
					वापस -EINVAL;
				पूर्ण

				env->insn_idx += insn->off + 1;
				जारी;

			पूर्ण अन्यथा अगर (opcode == BPF_EXIT) अणु
				अगर (BPF_SRC(insn->code) != BPF_K ||
				    insn->imm != 0 ||
				    insn->src_reg != BPF_REG_0 ||
				    insn->dst_reg != BPF_REG_0 ||
				    class == BPF_JMP32) अणु
					verbose(env, "BPF_EXIT uses reserved fields\n");
					वापस -EINVAL;
				पूर्ण

				अगर (env->cur_state->active_spin_lock) अणु
					verbose(env, "bpf_spin_unlock is missing\n");
					वापस -EINVAL;
				पूर्ण

				अगर (state->curframe) अणु
					/* निकास from nested function */
					err = prepare_func_निकास(env, &env->insn_idx);
					अगर (err)
						वापस err;
					करो_prपूर्णांक_state = true;
					जारी;
				पूर्ण

				err = check_reference_leak(env);
				अगर (err)
					वापस err;

				err = check_वापस_code(env);
				अगर (err)
					वापस err;
process_bpf_निकास:
				update_branch_counts(env, env->cur_state);
				err = pop_stack(env, &prev_insn_idx,
						&env->insn_idx, pop_log);
				अगर (err < 0) अणु
					अगर (err != -ENOENT)
						वापस err;
					अवरोध;
				पूर्ण अन्यथा अणु
					करो_prपूर्णांक_state = true;
					जारी;
				पूर्ण
			पूर्ण अन्यथा अणु
				err = check_cond_jmp_op(env, insn, &env->insn_idx);
				अगर (err)
					वापस err;
			पूर्ण
		पूर्ण अन्यथा अगर (class == BPF_LD) अणु
			u8 mode = BPF_MODE(insn->code);

			अगर (mode == BPF_ABS || mode == BPF_IND) अणु
				err = check_ld_असल(env, insn);
				अगर (err)
					वापस err;

			पूर्ण अन्यथा अगर (mode == BPF_IMM) अणु
				err = check_ld_imm(env, insn);
				अगर (err)
					वापस err;

				env->insn_idx++;
				sanitize_mark_insn_seen(env);
			पूर्ण अन्यथा अणु
				verbose(env, "invalid BPF_LD mode\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			verbose(env, "unknown insn class %d\n", class);
			वापस -EINVAL;
		पूर्ण

		env->insn_idx++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक find_btf_percpu_datasec(काष्ठा btf *btf)
अणु
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *tname;
	पूर्णांक i, n;

	/*
	 * Both vmlinux and module each have their own ".data..percpu"
	 * DATASECs in BTF. So क्रम module's हाल, we need to skip vmlinux BTF
	 * types to look at only module's own BTF types.
	 */
	n = btf_nr_types(btf);
	अगर (btf_is_module(btf))
		i = btf_nr_types(btf_vmlinux);
	अन्यथा
		i = 1;

	क्रम(; i < n; i++) अणु
		t = btf_type_by_id(btf, i);
		अगर (BTF_INFO_KIND(t->info) != BTF_KIND_DATASEC)
			जारी;

		tname = btf_name_by_offset(btf, t->name_off);
		अगर (!म_भेद(tname, ".data..percpu"))
			वापस i;
	पूर्ण

	वापस -ENOENT;
पूर्ण

/* replace pseuकरो btf_id with kernel symbol address */
अटल पूर्णांक check_pseuकरो_btf_id(काष्ठा bpf_verअगरier_env *env,
			       काष्ठा bpf_insn *insn,
			       काष्ठा bpf_insn_aux_data *aux)
अणु
	स्थिर काष्ठा btf_var_secinfo *vsi;
	स्थिर काष्ठा btf_type *datasec;
	काष्ठा btf_mod_pair *btf_mod;
	स्थिर काष्ठा btf_type *t;
	स्थिर अक्षर *sym_name;
	bool percpu = false;
	u32 type, id = insn->imm;
	काष्ठा btf *btf;
	s32 datasec_id;
	u64 addr;
	पूर्णांक i, btf_fd, err;

	btf_fd = insn[1].imm;
	अगर (btf_fd) अणु
		btf = btf_get_by_fd(btf_fd);
		अगर (IS_ERR(btf)) अणु
			verbose(env, "invalid module BTF object FD specified.\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!btf_vmlinux) अणु
			verbose(env, "kernel is missing BTF, make sure CONFIG_DEBUG_INFO_BTF=y is specified in Kconfig.\n");
			वापस -EINVAL;
		पूर्ण
		btf = btf_vmlinux;
		btf_get(btf);
	पूर्ण

	t = btf_type_by_id(btf, id);
	अगर (!t) अणु
		verbose(env, "ldimm64 insn specifies invalid btf_id %d.\n", id);
		err = -ENOENT;
		जाओ err_put;
	पूर्ण

	अगर (!btf_type_is_var(t)) अणु
		verbose(env, "pseudo btf_id %d in ldimm64 isn't KIND_VAR.\n", id);
		err = -EINVAL;
		जाओ err_put;
	पूर्ण

	sym_name = btf_name_by_offset(btf, t->name_off);
	addr = kallsyms_lookup_name(sym_name);
	अगर (!addr) अणु
		verbose(env, "ldimm64 failed to find the address for kernel symbol '%s'.\n",
			sym_name);
		err = -ENOENT;
		जाओ err_put;
	पूर्ण

	datasec_id = find_btf_percpu_datasec(btf);
	अगर (datasec_id > 0) अणु
		datasec = btf_type_by_id(btf, datasec_id);
		क्रम_each_vsi(i, datasec, vsi) अणु
			अगर (vsi->type == id) अणु
				percpu = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	insn[0].imm = (u32)addr;
	insn[1].imm = addr >> 32;

	type = t->type;
	t = btf_type_skip_modअगरiers(btf, type, शून्य);
	अगर (percpu) अणु
		aux->btf_var.reg_type = PTR_TO_PERCPU_BTF_ID;
		aux->btf_var.btf = btf;
		aux->btf_var.btf_id = type;
	पूर्ण अन्यथा अगर (!btf_type_is_काष्ठा(t)) अणु
		स्थिर काष्ठा btf_type *ret;
		स्थिर अक्षर *tname;
		u32 tsize;

		/* resolve the type size of ksym. */
		ret = btf_resolve_size(btf, t, &tsize);
		अगर (IS_ERR(ret)) अणु
			tname = btf_name_by_offset(btf, t->name_off);
			verbose(env, "ldimm64 unable to resolve the size of type '%s': %ld\n",
				tname, PTR_ERR(ret));
			err = -EINVAL;
			जाओ err_put;
		पूर्ण
		aux->btf_var.reg_type = PTR_TO_MEM;
		aux->btf_var.mem_size = tsize;
	पूर्ण अन्यथा अणु
		aux->btf_var.reg_type = PTR_TO_BTF_ID;
		aux->btf_var.btf = btf;
		aux->btf_var.btf_id = type;
	पूर्ण

	/* check whether we recorded this BTF (and maybe module) alपढ़ोy */
	क्रम (i = 0; i < env->used_btf_cnt; i++) अणु
		अगर (env->used_btfs[i].btf == btf) अणु
			btf_put(btf);
			वापस 0;
		पूर्ण
	पूर्ण

	अगर (env->used_btf_cnt >= MAX_USED_BTFS) अणु
		err = -E2BIG;
		जाओ err_put;
	पूर्ण

	btf_mod = &env->used_btfs[env->used_btf_cnt];
	btf_mod->btf = btf;
	btf_mod->module = शून्य;

	/* अगर we reference variables from kernel module, bump its refcount */
	अगर (btf_is_module(btf)) अणु
		btf_mod->module = btf_try_get_module(btf);
		अगर (!btf_mod->module) अणु
			err = -ENXIO;
			जाओ err_put;
		पूर्ण
	पूर्ण

	env->used_btf_cnt++;

	वापस 0;
err_put:
	btf_put(btf);
	वापस err;
पूर्ण

अटल पूर्णांक check_map_pपुनः_स्मृति(काष्ठा bpf_map *map)
अणु
	वापस (map->map_type != BPF_MAP_TYPE_HASH &&
		map->map_type != BPF_MAP_TYPE_PERCPU_HASH &&
		map->map_type != BPF_MAP_TYPE_HASH_OF_MAPS) ||
		!(map->map_flags & BPF_F_NO_PREALLOC);
पूर्ण

अटल bool is_tracing_prog_type(क्रमागत bpf_prog_type type)
अणु
	चयन (type) अणु
	हाल BPF_PROG_TYPE_KPROBE:
	हाल BPF_PROG_TYPE_TRACEPOINT:
	हाल BPF_PROG_TYPE_PERF_EVENT:
	हाल BPF_PROG_TYPE_RAW_TRACEPOINT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool is_pपुनः_स्मृतिated_map(काष्ठा bpf_map *map)
अणु
	अगर (!check_map_pपुनः_स्मृति(map))
		वापस false;
	अगर (map->inner_map_meta && !check_map_pपुनः_स्मृति(map->inner_map_meta))
		वापस false;
	वापस true;
पूर्ण

अटल पूर्णांक check_map_prog_compatibility(काष्ठा bpf_verअगरier_env *env,
					काष्ठा bpf_map *map,
					काष्ठा bpf_prog *prog)

अणु
	क्रमागत bpf_prog_type prog_type = resolve_prog_type(prog);
	/*
	 * Validate that trace type programs use pपुनः_स्मृतिated hash maps.
	 *
	 * For programs attached to PERF events this is mandatory as the
	 * perf NMI can hit any arbitrary code sequence.
	 *
	 * All other trace types using pपुनः_स्मृतिated hash maps are unsafe as
	 * well because tracepoपूर्णांक or kprobes can be inside locked regions
	 * of the memory allocator or at a place where a recursion पूर्णांकo the
	 * memory allocator would see inconsistent state.
	 *
	 * On RT enabled kernels run-समय allocation of all trace type
	 * programs is strictly prohibited due to lock type स्थिरraपूर्णांकs. On
	 * !RT kernels it is allowed क्रम backwards compatibility reasons क्रम
	 * now, but warnings are emitted so developers are made aware of
	 * the unsafety and can fix their programs beक्रमe this is enक्रमced.
	 */
	अगर (is_tracing_prog_type(prog_type) && !is_pपुनः_स्मृतिated_map(map)) अणु
		अगर (prog_type == BPF_PROG_TYPE_PERF_EVENT) अणु
			verbose(env, "perf_event programs can only use preallocated hash map\n");
			वापस -EINVAL;
		पूर्ण
		अगर (IS_ENABLED(CONFIG_PREEMPT_RT)) अणु
			verbose(env, "trace type programs can only use preallocated hash map\n");
			वापस -EINVAL;
		पूर्ण
		WARN_ONCE(1, "trace type BPF program uses run-time allocation\n");
		verbose(env, "trace type programs with run-time allocated hash maps are unsafe. Switch to preallocated hash maps.\n");
	पूर्ण

	अगर (map_value_has_spin_lock(map)) अणु
		अगर (prog_type == BPF_PROG_TYPE_SOCKET_FILTER) अणु
			verbose(env, "socket filter progs cannot use bpf_spin_lock yet\n");
			वापस -EINVAL;
		पूर्ण

		अगर (is_tracing_prog_type(prog_type)) अणु
			verbose(env, "tracing progs cannot use bpf_spin_lock yet\n");
			वापस -EINVAL;
		पूर्ण

		अगर (prog->aux->sleepable) अणु
			verbose(env, "sleepable progs cannot use bpf_spin_lock yet\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर ((bpf_prog_is_dev_bound(prog->aux) || bpf_map_is_dev_bound(map)) &&
	    !bpf_offload_prog_map_match(prog, map)) अणु
		verbose(env, "offload device mismatch between prog and map\n");
		वापस -EINVAL;
	पूर्ण

	अगर (map->map_type == BPF_MAP_TYPE_STRUCT_OPS) अणु
		verbose(env, "bpf_struct_ops map cannot be used in prog\n");
		वापस -EINVAL;
	पूर्ण

	अगर (prog->aux->sleepable)
		चयन (map->map_type) अणु
		हाल BPF_MAP_TYPE_HASH:
		हाल BPF_MAP_TYPE_LRU_HASH:
		हाल BPF_MAP_TYPE_ARRAY:
		हाल BPF_MAP_TYPE_PERCPU_HASH:
		हाल BPF_MAP_TYPE_PERCPU_ARRAY:
		हाल BPF_MAP_TYPE_LRU_PERCPU_HASH:
		हाल BPF_MAP_TYPE_ARRAY_OF_MAPS:
		हाल BPF_MAP_TYPE_HASH_OF_MAPS:
			अगर (!is_pपुनः_स्मृतिated_map(map)) अणु
				verbose(env,
					"Sleepable programs can only use preallocated maps\n");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		हाल BPF_MAP_TYPE_RINGBUF:
			अवरोध;
		शेष:
			verbose(env,
				"Sleepable programs can only use array, hash, and ringbuf maps\n");
			वापस -EINVAL;
		पूर्ण

	वापस 0;
पूर्ण

अटल bool bpf_map_is_cgroup_storage(काष्ठा bpf_map *map)
अणु
	वापस (map->map_type == BPF_MAP_TYPE_CGROUP_STORAGE ||
		map->map_type == BPF_MAP_TYPE_PERCPU_CGROUP_STORAGE);
पूर्ण

/* find and reग_लिखो pseuकरो imm in ld_imm64 inकाष्ठाions:
 *
 * 1. अगर it accesses map FD, replace it with actual map poपूर्णांकer.
 * 2. अगर it accesses btf_id of a VAR, replace it with poपूर्णांकer to the var.
 *
 * NOTE: btf_vmlinux is required क्रम converting pseuकरो btf_id.
 */
अटल पूर्णांक resolve_pseuकरो_ldimm64(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	पूर्णांक insn_cnt = env->prog->len;
	पूर्णांक i, j, err;

	err = bpf_prog_calc_tag(env->prog);
	अगर (err)
		वापस err;

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		अगर (BPF_CLASS(insn->code) == BPF_LDX &&
		    (BPF_MODE(insn->code) != BPF_MEM || insn->imm != 0)) अणु
			verbose(env, "BPF_LDX uses reserved fields\n");
			वापस -EINVAL;
		पूर्ण

		अगर (insn[0].code == (BPF_LD | BPF_IMM | BPF_DW)) अणु
			काष्ठा bpf_insn_aux_data *aux;
			काष्ठा bpf_map *map;
			काष्ठा fd f;
			u64 addr;

			अगर (i == insn_cnt - 1 || insn[1].code != 0 ||
			    insn[1].dst_reg != 0 || insn[1].src_reg != 0 ||
			    insn[1].off != 0) अणु
				verbose(env, "invalid bpf_ld_imm64 insn\n");
				वापस -EINVAL;
			पूर्ण

			अगर (insn[0].src_reg == 0)
				/* valid generic load 64-bit imm */
				जाओ next_insn;

			अगर (insn[0].src_reg == BPF_PSEUDO_BTF_ID) अणु
				aux = &env->insn_aux_data[i];
				err = check_pseuकरो_btf_id(env, insn, aux);
				अगर (err)
					वापस err;
				जाओ next_insn;
			पूर्ण

			अगर (insn[0].src_reg == BPF_PSEUDO_FUNC) अणु
				aux = &env->insn_aux_data[i];
				aux->ptr_type = PTR_TO_FUNC;
				जाओ next_insn;
			पूर्ण

			/* In final convert_pseuकरो_ld_imm64() step, this is
			 * converted पूर्णांकo regular 64-bit imm load insn.
			 */
			अगर ((insn[0].src_reg != BPF_PSEUDO_MAP_FD &&
			     insn[0].src_reg != BPF_PSEUDO_MAP_VALUE) ||
			    (insn[0].src_reg == BPF_PSEUDO_MAP_FD &&
			     insn[1].imm != 0)) अणु
				verbose(env,
					"unrecognized bpf_ld_imm64 insn\n");
				वापस -EINVAL;
			पूर्ण

			f = fdget(insn[0].imm);
			map = __bpf_map_get(f);
			अगर (IS_ERR(map)) अणु
				verbose(env, "fd %d is not pointing to valid bpf_map\n",
					insn[0].imm);
				वापस PTR_ERR(map);
			पूर्ण

			err = check_map_prog_compatibility(env, map, env->prog);
			अगर (err) अणु
				fdput(f);
				वापस err;
			पूर्ण

			aux = &env->insn_aux_data[i];
			अगर (insn->src_reg == BPF_PSEUDO_MAP_FD) अणु
				addr = (अचिन्हित दीर्घ)map;
			पूर्ण अन्यथा अणु
				u32 off = insn[1].imm;

				अगर (off >= BPF_MAX_VAR_OFF) अणु
					verbose(env, "direct value offset of %u is not allowed\n", off);
					fdput(f);
					वापस -EINVAL;
				पूर्ण

				अगर (!map->ops->map_direct_value_addr) अणु
					verbose(env, "no direct value access support for this map type\n");
					fdput(f);
					वापस -EINVAL;
				पूर्ण

				err = map->ops->map_direct_value_addr(map, &addr, off);
				अगर (err) अणु
					verbose(env, "invalid access to map value pointer, value_size=%u off=%u\n",
						map->value_size, off);
					fdput(f);
					वापस err;
				पूर्ण

				aux->map_off = off;
				addr += off;
			पूर्ण

			insn[0].imm = (u32)addr;
			insn[1].imm = addr >> 32;

			/* check whether we recorded this map alपढ़ोy */
			क्रम (j = 0; j < env->used_map_cnt; j++) अणु
				अगर (env->used_maps[j] == map) अणु
					aux->map_index = j;
					fdput(f);
					जाओ next_insn;
				पूर्ण
			पूर्ण

			अगर (env->used_map_cnt >= MAX_USED_MAPS) अणु
				fdput(f);
				वापस -E2BIG;
			पूर्ण

			/* hold the map. If the program is rejected by verअगरier,
			 * the map will be released by release_maps() or it
			 * will be used by the valid program until it's unloaded
			 * and all maps are released in मुक्त_used_maps()
			 */
			bpf_map_inc(map);

			aux->map_index = env->used_map_cnt;
			env->used_maps[env->used_map_cnt++] = map;

			अगर (bpf_map_is_cgroup_storage(map) &&
			    bpf_cgroup_storage_assign(env->prog->aux, map)) अणु
				verbose(env, "only one cgroup storage of each type is allowed\n");
				fdput(f);
				वापस -EBUSY;
			पूर्ण

			fdput(f);
next_insn:
			insn++;
			i++;
			जारी;
		पूर्ण

		/* Basic sanity check beक्रमe we invest more work here. */
		अगर (!bpf_opcode_in_insntable(insn->code)) अणु
			verbose(env, "unknown opcode %02x\n", insn->code);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* now all pseuकरो BPF_LD_IMM64 inकाष्ठाions load valid
	 * 'struct bpf_map *' पूर्णांकo a रेजिस्टर instead of user map_fd.
	 * These poपूर्णांकers will be used later by verअगरier to validate map access.
	 */
	वापस 0;
पूर्ण

/* drop refcnt of maps used by the rejected program */
अटल व्योम release_maps(काष्ठा bpf_verअगरier_env *env)
अणु
	__bpf_मुक्त_used_maps(env->prog->aux, env->used_maps,
			     env->used_map_cnt);
पूर्ण

/* drop refcnt of maps used by the rejected program */
अटल व्योम release_btfs(काष्ठा bpf_verअगरier_env *env)
अणु
	__bpf_मुक्त_used_btfs(env->prog->aux, env->used_btfs,
			     env->used_btf_cnt);
पूर्ण

/* convert pseuकरो BPF_LD_IMM64 पूर्णांकo generic BPF_LD_IMM64 */
अटल व्योम convert_pseuकरो_ld_imm64(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	पूर्णांक insn_cnt = env->prog->len;
	पूर्णांक i;

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		अगर (insn->code != (BPF_LD | BPF_IMM | BPF_DW))
			जारी;
		अगर (insn->src_reg == BPF_PSEUDO_FUNC)
			जारी;
		insn->src_reg = 0;
	पूर्ण
पूर्ण

/* single env->prog->insni[off] inकाष्ठाion was replaced with the range
 * insni[off, off + cnt).  Adjust corresponding insn_aux_data by copying
 * [0, off) and [off, end) to new locations, so the patched range stays zero
 */
अटल पूर्णांक adjust_insn_aux_data(काष्ठा bpf_verअगरier_env *env,
				काष्ठा bpf_prog *new_prog, u32 off, u32 cnt)
अणु
	काष्ठा bpf_insn_aux_data *new_data, *old_data = env->insn_aux_data;
	काष्ठा bpf_insn *insn = new_prog->insnsi;
	u32 old_seen = old_data[off].seen;
	u32 prog_len;
	पूर्णांक i;

	/* aux info at OFF always needs adjusपंचांगent, no matter fast path
	 * (cnt == 1) is taken or not. There is no guarantee INSN at OFF is the
	 * original insn at old prog.
	 */
	old_data[off].zext_dst = insn_has_def32(env, insn + off + cnt - 1);

	अगर (cnt == 1)
		वापस 0;
	prog_len = new_prog->len;
	new_data = vzalloc(array_size(prog_len,
				      माप(काष्ठा bpf_insn_aux_data)));
	अगर (!new_data)
		वापस -ENOMEM;
	स_नकल(new_data, old_data, माप(काष्ठा bpf_insn_aux_data) * off);
	स_नकल(new_data + off + cnt - 1, old_data + off,
	       माप(काष्ठा bpf_insn_aux_data) * (prog_len - off - cnt + 1));
	क्रम (i = off; i < off + cnt - 1; i++) अणु
		/* Expand insni[off]'s seen count to the patched range. */
		new_data[i].seen = old_seen;
		new_data[i].zext_dst = insn_has_def32(env, insn + i);
	पूर्ण
	env->insn_aux_data = new_data;
	vमुक्त(old_data);
	वापस 0;
पूर्ण

अटल व्योम adjust_subprog_starts(काष्ठा bpf_verअगरier_env *env, u32 off, u32 len)
अणु
	पूर्णांक i;

	अगर (len == 1)
		वापस;
	/* NOTE: fake 'exit' subprog should be updated as well. */
	क्रम (i = 0; i <= env->subprog_cnt; i++) अणु
		अगर (env->subprog_info[i].start <= off)
			जारी;
		env->subprog_info[i].start += len - 1;
	पूर्ण
पूर्ण

अटल व्योम adjust_poke_descs(काष्ठा bpf_prog *prog, u32 len)
अणु
	काष्ठा bpf_jit_poke_descriptor *tab = prog->aux->poke_tab;
	पूर्णांक i, sz = prog->aux->size_poke_tab;
	काष्ठा bpf_jit_poke_descriptor *desc;

	क्रम (i = 0; i < sz; i++) अणु
		desc = &tab[i];
		desc->insn_idx += len - 1;
	पूर्ण
पूर्ण

अटल काष्ठा bpf_prog *bpf_patch_insn_data(काष्ठा bpf_verअगरier_env *env, u32 off,
					    स्थिर काष्ठा bpf_insn *patch, u32 len)
अणु
	काष्ठा bpf_prog *new_prog;

	new_prog = bpf_patch_insn_single(env->prog, off, patch, len);
	अगर (IS_ERR(new_prog)) अणु
		अगर (PTR_ERR(new_prog) == -दुस्फल)
			verbose(env,
				"insn %d cannot be patched due to 16-bit range\n",
				env->insn_aux_data[off].orig_idx);
		वापस शून्य;
	पूर्ण
	अगर (adjust_insn_aux_data(env, new_prog, off, len))
		वापस शून्य;
	adjust_subprog_starts(env, off, len);
	adjust_poke_descs(new_prog, len);
	वापस new_prog;
पूर्ण

अटल पूर्णांक adjust_subprog_starts_after_हटाओ(काष्ठा bpf_verअगरier_env *env,
					      u32 off, u32 cnt)
अणु
	पूर्णांक i, j;

	/* find first prog starting at or after off (first to हटाओ) */
	क्रम (i = 0; i < env->subprog_cnt; i++)
		अगर (env->subprog_info[i].start >= off)
			अवरोध;
	/* find first prog starting at or after off + cnt (first to stay) */
	क्रम (j = i; j < env->subprog_cnt; j++)
		अगर (env->subprog_info[j].start >= off + cnt)
			अवरोध;
	/* अगर j करोesn't start exactly at off + cnt, we are just removing
	 * the front of previous prog
	 */
	अगर (env->subprog_info[j].start != off + cnt)
		j--;

	अगर (j > i) अणु
		काष्ठा bpf_prog_aux *aux = env->prog->aux;
		पूर्णांक move;

		/* move fake 'exit' subprog as well */
		move = env->subprog_cnt + 1 - j;

		स_हटाओ(env->subprog_info + i,
			env->subprog_info + j,
			माप(*env->subprog_info) * move);
		env->subprog_cnt -= j - i;

		/* हटाओ func_info */
		अगर (aux->func_info) अणु
			move = aux->func_info_cnt - j;

			स_हटाओ(aux->func_info + i,
				aux->func_info + j,
				माप(*aux->func_info) * move);
			aux->func_info_cnt -= j - i;
			/* func_info->insn_off is set after all code reग_लिखोs,
			 * in adjust_btf_func() - no need to adjust
			 */
		पूर्ण
	पूर्ण अन्यथा अणु
		/* convert i from "first prog to remove" to "first to adjust" */
		अगर (env->subprog_info[i].start == off)
			i++;
	पूर्ण

	/* update fake 'exit' subprog as well */
	क्रम (; i <= env->subprog_cnt; i++)
		env->subprog_info[i].start -= cnt;

	वापस 0;
पूर्ण

अटल पूर्णांक bpf_adj_linfo_after_हटाओ(काष्ठा bpf_verअगरier_env *env, u32 off,
				      u32 cnt)
अणु
	काष्ठा bpf_prog *prog = env->prog;
	u32 i, l_off, l_cnt, nr_linfo;
	काष्ठा bpf_line_info *linfo;

	nr_linfo = prog->aux->nr_linfo;
	अगर (!nr_linfo)
		वापस 0;

	linfo = prog->aux->linfo;

	/* find first line info to हटाओ, count lines to be हटाओd */
	क्रम (i = 0; i < nr_linfo; i++)
		अगर (linfo[i].insn_off >= off)
			अवरोध;

	l_off = i;
	l_cnt = 0;
	क्रम (; i < nr_linfo; i++)
		अगर (linfo[i].insn_off < off + cnt)
			l_cnt++;
		अन्यथा
			अवरोध;

	/* First live insn करोesn't match first live linfo, it needs to "inherit"
	 * last हटाओd linfo.  prog is alपढ़ोy modअगरied, so prog->len == off
	 * means no live inकाष्ठाions after (tail of the program was हटाओd).
	 */
	अगर (prog->len != off && l_cnt &&
	    (i == nr_linfo || linfo[i].insn_off != off + cnt)) अणु
		l_cnt--;
		linfo[--i].insn_off = off + cnt;
	पूर्ण

	/* हटाओ the line info which refer to the हटाओd inकाष्ठाions */
	अगर (l_cnt) अणु
		स_हटाओ(linfo + l_off, linfo + i,
			माप(*linfo) * (nr_linfo - i));

		prog->aux->nr_linfo -= l_cnt;
		nr_linfo = prog->aux->nr_linfo;
	पूर्ण

	/* pull all linfo[i].insn_off >= off + cnt in by cnt */
	क्रम (i = l_off; i < nr_linfo; i++)
		linfo[i].insn_off -= cnt;

	/* fix up all subprogs (incl. 'exit') which start >= off */
	क्रम (i = 0; i <= env->subprog_cnt; i++)
		अगर (env->subprog_info[i].linfo_idx > l_off) अणु
			/* program may have started in the हटाओd region but
			 * may not be fully हटाओd
			 */
			अगर (env->subprog_info[i].linfo_idx >= l_off + l_cnt)
				env->subprog_info[i].linfo_idx -= l_cnt;
			अन्यथा
				env->subprog_info[i].linfo_idx = l_off;
		पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक verअगरier_हटाओ_insns(काष्ठा bpf_verअगरier_env *env, u32 off, u32 cnt)
अणु
	काष्ठा bpf_insn_aux_data *aux_data = env->insn_aux_data;
	अचिन्हित पूर्णांक orig_prog_len = env->prog->len;
	पूर्णांक err;

	अगर (bpf_prog_is_dev_bound(env->prog->aux))
		bpf_prog_offload_हटाओ_insns(env, off, cnt);

	err = bpf_हटाओ_insns(env->prog, off, cnt);
	अगर (err)
		वापस err;

	err = adjust_subprog_starts_after_हटाओ(env, off, cnt);
	अगर (err)
		वापस err;

	err = bpf_adj_linfo_after_हटाओ(env, off, cnt);
	अगर (err)
		वापस err;

	स_हटाओ(aux_data + off,	aux_data + off + cnt,
		माप(*aux_data) * (orig_prog_len - off - cnt));

	वापस 0;
पूर्ण

/* The verअगरier करोes more data flow analysis than llvm and will not
 * explore branches that are dead at run समय. Malicious programs can
 * have dead code too. Thereक्रमe replace all dead at-run-समय code
 * with 'ja -1'.
 *
 * Just nops are not optimal, e.g. अगर they would sit at the end of the
 * program and through another bug we would manage to jump there, then
 * we'd execute beyond program memory otherwise. Returning exception
 * code also wouldn't work since we can have subprogs where the dead
 * code could be located.
 */
अटल व्योम sanitize_dead_code(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_insn_aux_data *aux_data = env->insn_aux_data;
	काष्ठा bpf_insn trap = BPF_JMP_IMM(BPF_JA, 0, 0, -1);
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	स्थिर पूर्णांक insn_cnt = env->prog->len;
	पूर्णांक i;

	क्रम (i = 0; i < insn_cnt; i++) अणु
		अगर (aux_data[i].seen)
			जारी;
		स_नकल(insn + i, &trap, माप(trap));
	पूर्ण
पूर्ण

अटल bool insn_is_cond_jump(u8 code)
अणु
	u8 op;

	अगर (BPF_CLASS(code) == BPF_JMP32)
		वापस true;

	अगर (BPF_CLASS(code) != BPF_JMP)
		वापस false;

	op = BPF_OP(code);
	वापस op != BPF_JA && op != BPF_EXIT && op != BPF_CALL;
पूर्ण

अटल व्योम opt_hard_wire_dead_code_branches(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_insn_aux_data *aux_data = env->insn_aux_data;
	काष्ठा bpf_insn ja = BPF_JMP_IMM(BPF_JA, 0, 0, 0);
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	स्थिर पूर्णांक insn_cnt = env->prog->len;
	पूर्णांक i;

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		अगर (!insn_is_cond_jump(insn->code))
			जारी;

		अगर (!aux_data[i + 1].seen)
			ja.off = insn->off;
		अन्यथा अगर (!aux_data[i + 1 + insn->off].seen)
			ja.off = 0;
		अन्यथा
			जारी;

		अगर (bpf_prog_is_dev_bound(env->prog->aux))
			bpf_prog_offload_replace_insn(env, i, &ja);

		स_नकल(insn, &ja, माप(ja));
	पूर्ण
पूर्ण

अटल पूर्णांक opt_हटाओ_dead_code(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_insn_aux_data *aux_data = env->insn_aux_data;
	पूर्णांक insn_cnt = env->prog->len;
	पूर्णांक i, err;

	क्रम (i = 0; i < insn_cnt; i++) अणु
		पूर्णांक j;

		j = 0;
		जबतक (i + j < insn_cnt && !aux_data[i + j].seen)
			j++;
		अगर (!j)
			जारी;

		err = verअगरier_हटाओ_insns(env, i, j);
		अगर (err)
			वापस err;
		insn_cnt = env->prog->len;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक opt_हटाओ_nops(काष्ठा bpf_verअगरier_env *env)
अणु
	स्थिर काष्ठा bpf_insn ja = BPF_JMP_IMM(BPF_JA, 0, 0, 0);
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	पूर्णांक insn_cnt = env->prog->len;
	पूर्णांक i, err;

	क्रम (i = 0; i < insn_cnt; i++) अणु
		अगर (स_भेद(&insn[i], &ja, माप(ja)))
			जारी;

		err = verअगरier_हटाओ_insns(env, i, 1);
		अगर (err)
			वापस err;
		insn_cnt--;
		i--;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक opt_subreg_zext_lo32_rnd_hi32(काष्ठा bpf_verअगरier_env *env,
					 स्थिर जोड़ bpf_attr *attr)
अणु
	काष्ठा bpf_insn *patch, zext_patch[2], rnd_hi32_patch[4];
	काष्ठा bpf_insn_aux_data *aux = env->insn_aux_data;
	पूर्णांक i, patch_len, delta = 0, len = env->prog->len;
	काष्ठा bpf_insn *insns = env->prog->insnsi;
	काष्ठा bpf_prog *new_prog;
	bool rnd_hi32;

	rnd_hi32 = attr->prog_flags & BPF_F_TEST_RND_HI32;
	zext_patch[1] = BPF_ZEXT_REG(0);
	rnd_hi32_patch[1] = BPF_ALU64_IMM(BPF_MOV, BPF_REG_AX, 0);
	rnd_hi32_patch[2] = BPF_ALU64_IMM(BPF_LSH, BPF_REG_AX, 32);
	rnd_hi32_patch[3] = BPF_ALU64_REG(BPF_OR, 0, BPF_REG_AX);
	क्रम (i = 0; i < len; i++) अणु
		पूर्णांक adj_idx = i + delta;
		काष्ठा bpf_insn insn;
		पूर्णांक load_reg;

		insn = insns[adj_idx];
		load_reg = insn_def_regno(&insn);
		अगर (!aux[adj_idx].zext_dst) अणु
			u8 code, class;
			u32 imm_rnd;

			अगर (!rnd_hi32)
				जारी;

			code = insn.code;
			class = BPF_CLASS(code);
			अगर (load_reg == -1)
				जारी;

			/* NOTE: arg "reg" (the fourth one) is only used क्रम
			 *       BPF_STX + SRC_OP, so it is safe to pass शून्य
			 *       here.
			 */
			अगर (is_reg64(env, &insn, load_reg, शून्य, DST_OP)) अणु
				अगर (class == BPF_LD &&
				    BPF_MODE(code) == BPF_IMM)
					i++;
				जारी;
			पूर्ण

			/* ctx load could be transक्रमmed पूर्णांकo wider load. */
			अगर (class == BPF_LDX &&
			    aux[adj_idx].ptr_type == PTR_TO_CTX)
				जारी;

			imm_rnd = get_अक्रमom_पूर्णांक();
			rnd_hi32_patch[0] = insn;
			rnd_hi32_patch[1].imm = imm_rnd;
			rnd_hi32_patch[3].dst_reg = load_reg;
			patch = rnd_hi32_patch;
			patch_len = 4;
			जाओ apply_patch_buffer;
		पूर्ण

		/* Add in an zero-extend inकाष्ठाion अगर a) the JIT has requested
		 * it or b) it's a CMPXCHG.
		 *
		 * The latter is because: BPF_CMPXCHG always loads a value पूर्णांकo
		 * R0, thereक्रमe always zero-extends. However some archs'
		 * equivalent inकाष्ठाion only करोes this load when the
		 * comparison is successful. This detail of CMPXCHG is
		 * orthogonal to the general zero-extension behaviour of the
		 * CPU, so it's treated independently of bpf_jit_needs_zext.
		 */
		अगर (!bpf_jit_needs_zext() && !is_cmpxchg_insn(&insn))
			जारी;

		अगर (WARN_ON(load_reg == -1)) अणु
			verbose(env, "verifier bug. zext_dst is set, but no reg is defined\n");
			वापस -EFAULT;
		पूर्ण

		zext_patch[0] = insn;
		zext_patch[1].dst_reg = load_reg;
		zext_patch[1].src_reg = load_reg;
		patch = zext_patch;
		patch_len = 2;
apply_patch_buffer:
		new_prog = bpf_patch_insn_data(env, adj_idx, patch, patch_len);
		अगर (!new_prog)
			वापस -ENOMEM;
		env->prog = new_prog;
		insns = new_prog->insnsi;
		aux = env->insn_aux_data;
		delta += patch_len - 1;
	पूर्ण

	वापस 0;
पूर्ण

/* convert load inकाष्ठाions that access fields of a context type पूर्णांकo a
 * sequence of inकाष्ठाions that access fields of the underlying काष्ठाure:
 *     काष्ठा __sk_buff    -> काष्ठा sk_buff
 *     काष्ठा bpf_sock_ops -> काष्ठा sock
 */
अटल पूर्णांक convert_ctx_accesses(काष्ठा bpf_verअगरier_env *env)
अणु
	स्थिर काष्ठा bpf_verअगरier_ops *ops = env->ops;
	पूर्णांक i, cnt, size, ctx_field_size, delta = 0;
	स्थिर पूर्णांक insn_cnt = env->prog->len;
	काष्ठा bpf_insn insn_buf[16], *insn;
	u32 target_size, size_शेष, off;
	काष्ठा bpf_prog *new_prog;
	क्रमागत bpf_access_type type;
	bool is_narrower_load;

	अगर (ops->gen_prologue || env->seen_direct_ग_लिखो) अणु
		अगर (!ops->gen_prologue) अणु
			verbose(env, "bpf verifier is misconfigured\n");
			वापस -EINVAL;
		पूर्ण
		cnt = ops->gen_prologue(insn_buf, env->seen_direct_ग_लिखो,
					env->prog);
		अगर (cnt >= ARRAY_SIZE(insn_buf)) अणु
			verbose(env, "bpf verifier is misconfigured\n");
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (cnt) अणु
			new_prog = bpf_patch_insn_data(env, 0, insn_buf, cnt);
			अगर (!new_prog)
				वापस -ENOMEM;

			env->prog = new_prog;
			delta += cnt - 1;
		पूर्ण
	पूर्ण

	अगर (bpf_prog_is_dev_bound(env->prog->aux))
		वापस 0;

	insn = env->prog->insnsi + delta;

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		bpf_convert_ctx_access_t convert_ctx_access;

		अगर (insn->code == (BPF_LDX | BPF_MEM | BPF_B) ||
		    insn->code == (BPF_LDX | BPF_MEM | BPF_H) ||
		    insn->code == (BPF_LDX | BPF_MEM | BPF_W) ||
		    insn->code == (BPF_LDX | BPF_MEM | BPF_DW))
			type = BPF_READ;
		अन्यथा अगर (insn->code == (BPF_STX | BPF_MEM | BPF_B) ||
			 insn->code == (BPF_STX | BPF_MEM | BPF_H) ||
			 insn->code == (BPF_STX | BPF_MEM | BPF_W) ||
			 insn->code == (BPF_STX | BPF_MEM | BPF_DW))
			type = BPF_WRITE;
		अन्यथा
			जारी;

		अगर (type == BPF_WRITE &&
		    env->insn_aux_data[i + delta].sanitize_stack_off) अणु
			काष्ठा bpf_insn patch[] = अणु
				/* Sanitize suspicious stack slot with zero.
				 * There are no memory dependencies क्रम this store,
				 * since it's only using frame poपूर्णांकer and immediate
				 * स्थिरant of zero
				 */
				BPF_ST_MEM(BPF_DW, BPF_REG_FP,
					   env->insn_aux_data[i + delta].sanitize_stack_off,
					   0),
				/* the original STX inकाष्ठाion will immediately
				 * overग_लिखो the same stack slot with appropriate value
				 */
				*insn,
			पूर्ण;

			cnt = ARRAY_SIZE(patch);
			new_prog = bpf_patch_insn_data(env, i + delta, patch, cnt);
			अगर (!new_prog)
				वापस -ENOMEM;

			delta    += cnt - 1;
			env->prog = new_prog;
			insn      = new_prog->insnsi + i + delta;
			जारी;
		पूर्ण

		चयन (env->insn_aux_data[i + delta].ptr_type) अणु
		हाल PTR_TO_CTX:
			अगर (!ops->convert_ctx_access)
				जारी;
			convert_ctx_access = ops->convert_ctx_access;
			अवरोध;
		हाल PTR_TO_SOCKET:
		हाल PTR_TO_SOCK_COMMON:
			convert_ctx_access = bpf_sock_convert_ctx_access;
			अवरोध;
		हाल PTR_TO_TCP_SOCK:
			convert_ctx_access = bpf_tcp_sock_convert_ctx_access;
			अवरोध;
		हाल PTR_TO_XDP_SOCK:
			convert_ctx_access = bpf_xdp_sock_convert_ctx_access;
			अवरोध;
		हाल PTR_TO_BTF_ID:
			अगर (type == BPF_READ) अणु
				insn->code = BPF_LDX | BPF_PROBE_MEM |
					BPF_SIZE((insn)->code);
				env->prog->aux->num_exentries++;
			पूर्ण अन्यथा अगर (resolve_prog_type(env->prog) != BPF_PROG_TYPE_STRUCT_OPS) अणु
				verbose(env, "Writes through BTF pointers are not allowed\n");
				वापस -EINVAL;
			पूर्ण
			जारी;
		शेष:
			जारी;
		पूर्ण

		ctx_field_size = env->insn_aux_data[i + delta].ctx_field_size;
		size = BPF_LDST_BYTES(insn);

		/* If the पढ़ो access is a narrower load of the field,
		 * convert to a 4/8-byte load, to minimum program type specअगरic
		 * convert_ctx_access changes. If conversion is successful,
		 * we will apply proper mask to the result.
		 */
		is_narrower_load = size < ctx_field_size;
		size_शेष = bpf_ctx_off_adjust_machine(ctx_field_size);
		off = insn->off;
		अगर (is_narrower_load) अणु
			u8 size_code;

			अगर (type == BPF_WRITE) अणु
				verbose(env, "bpf verifier narrow ctx access misconfigured\n");
				वापस -EINVAL;
			पूर्ण

			size_code = BPF_H;
			अगर (ctx_field_size == 4)
				size_code = BPF_W;
			अन्यथा अगर (ctx_field_size == 8)
				size_code = BPF_DW;

			insn->off = off & ~(size_शेष - 1);
			insn->code = BPF_LDX | BPF_MEM | size_code;
		पूर्ण

		target_size = 0;
		cnt = convert_ctx_access(type, insn, insn_buf, env->prog,
					 &target_size);
		अगर (cnt == 0 || cnt >= ARRAY_SIZE(insn_buf) ||
		    (ctx_field_size && !target_size)) अणु
			verbose(env, "bpf verifier is misconfigured\n");
			वापस -EINVAL;
		पूर्ण

		अगर (is_narrower_load && size < target_size) अणु
			u8 shअगरt = bpf_ctx_narrow_access_offset(
				off, size, size_शेष) * 8;
			अगर (ctx_field_size <= 4) अणु
				अगर (shअगरt)
					insn_buf[cnt++] = BPF_ALU32_IMM(BPF_RSH,
									insn->dst_reg,
									shअगरt);
				insn_buf[cnt++] = BPF_ALU32_IMM(BPF_AND, insn->dst_reg,
								(1 << size * 8) - 1);
			पूर्ण अन्यथा अणु
				अगर (shअगरt)
					insn_buf[cnt++] = BPF_ALU64_IMM(BPF_RSH,
									insn->dst_reg,
									shअगरt);
				insn_buf[cnt++] = BPF_ALU64_IMM(BPF_AND, insn->dst_reg,
								(1ULL << size * 8) - 1);
			पूर्ण
		पूर्ण

		new_prog = bpf_patch_insn_data(env, i + delta, insn_buf, cnt);
		अगर (!new_prog)
			वापस -ENOMEM;

		delta += cnt - 1;

		/* keep walking new program and skip insns we just inserted */
		env->prog = new_prog;
		insn      = new_prog->insnsi + i + delta;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक jit_subprogs(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_prog *prog = env->prog, **func, *पंचांगp;
	पूर्णांक i, j, subprog_start, subprog_end = 0, len, subprog;
	काष्ठा bpf_map *map_ptr;
	काष्ठा bpf_insn *insn;
	व्योम *old_bpf_func;
	पूर्णांक err, num_exentries;

	अगर (env->subprog_cnt <= 1)
		वापस 0;

	क्रम (i = 0, insn = prog->insnsi; i < prog->len; i++, insn++) अणु
		अगर (bpf_pseuकरो_func(insn)) अणु
			env->insn_aux_data[i].call_imm = insn->imm;
			/* subprog is encoded in insn[1].imm */
			जारी;
		पूर्ण

		अगर (!bpf_pseuकरो_call(insn))
			जारी;
		/* Upon error here we cannot fall back to पूर्णांकerpreter but
		 * need a hard reject of the program. Thus -EFAULT is
		 * propagated in any हाल.
		 */
		subprog = find_subprog(env, i + insn->imm + 1);
		अगर (subprog < 0) अणु
			WARN_ONCE(1, "verifier bug. No program starts at insn %d\n",
				  i + insn->imm + 1);
			वापस -EFAULT;
		पूर्ण
		/* temporarily remember subprog id inside insn instead of
		 * aux_data, since next loop will split up all insns पूर्णांकo funcs
		 */
		insn->off = subprog;
		/* remember original imm in हाल JIT fails and fallback
		 * to पूर्णांकerpreter will be needed
		 */
		env->insn_aux_data[i].call_imm = insn->imm;
		/* poपूर्णांक imm to __bpf_call_base+1 from JITs poपूर्णांक of view */
		insn->imm = 1;
	पूर्ण

	err = bpf_prog_alloc_jited_linfo(prog);
	अगर (err)
		जाओ out_unकरो_insn;

	err = -ENOMEM;
	func = kसुस्मृति(env->subprog_cnt, माप(prog), GFP_KERNEL);
	अगर (!func)
		जाओ out_unकरो_insn;

	क्रम (i = 0; i < env->subprog_cnt; i++) अणु
		subprog_start = subprog_end;
		subprog_end = env->subprog_info[i + 1].start;

		len = subprog_end - subprog_start;
		/* BPF_PROG_RUN करोesn't call subprogs directly,
		 * hence मुख्य prog stats include the runसमय of subprogs.
		 * subprogs करोn't have IDs and not reachable via prog_get_next_id
		 * func[i]->stats will never be accessed and stays शून्य
		 */
		func[i] = bpf_prog_alloc_no_stats(bpf_prog_size(len), GFP_USER);
		अगर (!func[i])
			जाओ out_मुक्त;
		स_नकल(func[i]->insnsi, &prog->insnsi[subprog_start],
		       len * माप(काष्ठा bpf_insn));
		func[i]->type = prog->type;
		func[i]->len = len;
		अगर (bpf_prog_calc_tag(func[i]))
			जाओ out_मुक्त;
		func[i]->is_func = 1;
		func[i]->aux->func_idx = i;
		/* the btf and func_info will be मुक्तd only at prog->aux */
		func[i]->aux->btf = prog->aux->btf;
		func[i]->aux->func_info = prog->aux->func_info;

		क्रम (j = 0; j < prog->aux->size_poke_tab; j++) अणु
			u32 insn_idx = prog->aux->poke_tab[j].insn_idx;
			पूर्णांक ret;

			अगर (!(insn_idx >= subprog_start &&
			      insn_idx <= subprog_end))
				जारी;

			ret = bpf_jit_add_poke_descriptor(func[i],
							  &prog->aux->poke_tab[j]);
			अगर (ret < 0) अणु
				verbose(env, "adding tail call poke descriptor failed\n");
				जाओ out_मुक्त;
			पूर्ण

			func[i]->insnsi[insn_idx - subprog_start].imm = ret + 1;

			map_ptr = func[i]->aux->poke_tab[ret].tail_call.map;
			ret = map_ptr->ops->map_poke_track(map_ptr, func[i]->aux);
			अगर (ret < 0) अणु
				verbose(env, "tracking tail call prog failed\n");
				जाओ out_मुक्त;
			पूर्ण
		पूर्ण

		/* Use bpf_prog_F_tag to indicate functions in stack traces.
		 * Long term would need debug info to populate names
		 */
		func[i]->aux->name[0] = 'F';
		func[i]->aux->stack_depth = env->subprog_info[i].stack_depth;
		func[i]->jit_requested = 1;
		func[i]->aux->kfunc_tab = prog->aux->kfunc_tab;
		func[i]->aux->linfo = prog->aux->linfo;
		func[i]->aux->nr_linfo = prog->aux->nr_linfo;
		func[i]->aux->jited_linfo = prog->aux->jited_linfo;
		func[i]->aux->linfo_idx = env->subprog_info[i].linfo_idx;
		num_exentries = 0;
		insn = func[i]->insnsi;
		क्रम (j = 0; j < func[i]->len; j++, insn++) अणु
			अगर (BPF_CLASS(insn->code) == BPF_LDX &&
			    BPF_MODE(insn->code) == BPF_PROBE_MEM)
				num_exentries++;
		पूर्ण
		func[i]->aux->num_exentries = num_exentries;
		func[i]->aux->tail_call_reachable = env->subprog_info[i].tail_call_reachable;
		func[i] = bpf_पूर्णांक_jit_compile(func[i]);
		अगर (!func[i]->jited) अणु
			err = -ENOTSUPP;
			जाओ out_मुक्त;
		पूर्ण
		cond_resched();
	पूर्ण

	/* Untrack मुख्य program's aux काष्ठाs so that during map_poke_run()
	 * we will not stumble upon the unfilled poke descriptors; each
	 * of the मुख्य program's poke descs got distributed across subprogs
	 * and got tracked onto map, so we are sure that none of them will
	 * be missed after the operation below
	 */
	क्रम (i = 0; i < prog->aux->size_poke_tab; i++) अणु
		map_ptr = prog->aux->poke_tab[i].tail_call.map;

		map_ptr->ops->map_poke_untrack(map_ptr, prog->aux);
	पूर्ण

	/* at this poपूर्णांक all bpf functions were successfully JITed
	 * now populate all bpf_calls with correct addresses and
	 * run last pass of JIT
	 */
	क्रम (i = 0; i < env->subprog_cnt; i++) अणु
		insn = func[i]->insnsi;
		क्रम (j = 0; j < func[i]->len; j++, insn++) अणु
			अगर (bpf_pseuकरो_func(insn)) अणु
				subprog = insn[1].imm;
				insn[0].imm = (u32)(दीर्घ)func[subprog]->bpf_func;
				insn[1].imm = ((u64)(दीर्घ)func[subprog]->bpf_func) >> 32;
				जारी;
			पूर्ण
			अगर (!bpf_pseuकरो_call(insn))
				जारी;
			subprog = insn->off;
			insn->imm = BPF_CAST_CALL(func[subprog]->bpf_func) -
				    __bpf_call_base;
		पूर्ण

		/* we use the aux data to keep a list of the start addresses
		 * of the JITed images क्रम each function in the program
		 *
		 * क्रम some architectures, such as घातerpc64, the imm field
		 * might not be large enough to hold the offset of the start
		 * address of the callee's JITed image from __bpf_call_base
		 *
		 * in such हालs, we can lookup the start address of a callee
		 * by using its subprog id, available from the off field of
		 * the call inकाष्ठाion, as an index क्रम this list
		 */
		func[i]->aux->func = func;
		func[i]->aux->func_cnt = env->subprog_cnt;
	पूर्ण
	क्रम (i = 0; i < env->subprog_cnt; i++) अणु
		old_bpf_func = func[i]->bpf_func;
		पंचांगp = bpf_पूर्णांक_jit_compile(func[i]);
		अगर (पंचांगp != func[i] || func[i]->bpf_func != old_bpf_func) अणु
			verbose(env, "JIT doesn't support bpf-to-bpf calls\n");
			err = -ENOTSUPP;
			जाओ out_मुक्त;
		पूर्ण
		cond_resched();
	पूर्ण

	/* finally lock prog and jit images क्रम all functions and
	 * populate kallsysm
	 */
	क्रम (i = 0; i < env->subprog_cnt; i++) अणु
		bpf_prog_lock_ro(func[i]);
		bpf_prog_kallsyms_add(func[i]);
	पूर्ण

	/* Last step: make now unused पूर्णांकerpreter insns from मुख्य
	 * prog consistent क्रम later dump requests, so they can
	 * later look the same as अगर they were पूर्णांकerpreted only.
	 */
	क्रम (i = 0, insn = prog->insnsi; i < prog->len; i++, insn++) अणु
		अगर (bpf_pseuकरो_func(insn)) अणु
			insn[0].imm = env->insn_aux_data[i].call_imm;
			insn[1].imm = find_subprog(env, i + insn[0].imm + 1);
			जारी;
		पूर्ण
		अगर (!bpf_pseuकरो_call(insn))
			जारी;
		insn->off = env->insn_aux_data[i].call_imm;
		subprog = find_subprog(env, i + insn->off + 1);
		insn->imm = subprog;
	पूर्ण

	prog->jited = 1;
	prog->bpf_func = func[0]->bpf_func;
	prog->aux->func = func;
	prog->aux->func_cnt = env->subprog_cnt;
	bpf_prog_jit_attempt_करोne(prog);
	वापस 0;
out_मुक्त:
	क्रम (i = 0; i < env->subprog_cnt; i++) अणु
		अगर (!func[i])
			जारी;

		क्रम (j = 0; j < func[i]->aux->size_poke_tab; j++) अणु
			map_ptr = func[i]->aux->poke_tab[j].tail_call.map;
			map_ptr->ops->map_poke_untrack(map_ptr, func[i]->aux);
		पूर्ण
		bpf_jit_मुक्त(func[i]);
	पूर्ण
	kमुक्त(func);
out_unकरो_insn:
	/* cleanup मुख्य prog to be पूर्णांकerpreted */
	prog->jit_requested = 0;
	क्रम (i = 0, insn = prog->insnsi; i < prog->len; i++, insn++) अणु
		अगर (!bpf_pseuकरो_call(insn))
			जारी;
		insn->off = 0;
		insn->imm = env->insn_aux_data[i].call_imm;
	पूर्ण
	bpf_prog_jit_attempt_करोne(prog);
	वापस err;
पूर्ण

अटल पूर्णांक fixup_call_args(काष्ठा bpf_verअगरier_env *env)
अणु
#अगर_अघोषित CONFIG_BPF_JIT_ALWAYS_ON
	काष्ठा bpf_prog *prog = env->prog;
	काष्ठा bpf_insn *insn = prog->insnsi;
	bool has_kfunc_call = bpf_prog_has_kfunc_call(prog);
	पूर्णांक i, depth;
#पूर्ण_अगर
	पूर्णांक err = 0;

	अगर (env->prog->jit_requested &&
	    !bpf_prog_is_dev_bound(env->prog->aux)) अणु
		err = jit_subprogs(env);
		अगर (err == 0)
			वापस 0;
		अगर (err == -EFAULT)
			वापस err;
	पूर्ण
#अगर_अघोषित CONFIG_BPF_JIT_ALWAYS_ON
	अगर (has_kfunc_call) अणु
		verbose(env, "calling kernel functions are not allowed in non-JITed programs\n");
		वापस -EINVAL;
	पूर्ण
	अगर (env->subprog_cnt > 1 && env->prog->aux->tail_call_reachable) अणु
		/* When JIT fails the progs with bpf2bpf calls and tail_calls
		 * have to be rejected, since पूर्णांकerpreter करोesn't support them yet.
		 */
		verbose(env, "tail_calls are not allowed in non-JITed programs with bpf-to-bpf calls\n");
		वापस -EINVAL;
	पूर्ण
	क्रम (i = 0; i < prog->len; i++, insn++) अणु
		अगर (bpf_pseuकरो_func(insn)) अणु
			/* When JIT fails the progs with callback calls
			 * have to be rejected, since पूर्णांकerpreter करोesn't support them yet.
			 */
			verbose(env, "callbacks are not allowed in non-JITed programs\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!bpf_pseuकरो_call(insn))
			जारी;
		depth = get_callee_stack_depth(env, insn, i);
		अगर (depth < 0)
			वापस depth;
		bpf_patch_call_args(insn, depth);
	पूर्ण
	err = 0;
#पूर्ण_अगर
	वापस err;
पूर्ण

अटल पूर्णांक fixup_kfunc_call(काष्ठा bpf_verअगरier_env *env,
			    काष्ठा bpf_insn *insn)
अणु
	स्थिर काष्ठा bpf_kfunc_desc *desc;

	/* insn->imm has the btf func_id. Replace it with
	 * an address (relative to __bpf_base_call).
	 */
	desc = find_kfunc_desc(env->prog, insn->imm);
	अगर (!desc) अणु
		verbose(env, "verifier internal error: kernel function descriptor not found for func_id %u\n",
			insn->imm);
		वापस -EFAULT;
	पूर्ण

	insn->imm = desc->imm;

	वापस 0;
पूर्ण

/* Do various post-verअगरication reग_लिखोs in a single program pass.
 * These reग_लिखोs simplअगरy JIT and पूर्णांकerpreter implementations.
 */
अटल पूर्णांक करो_misc_fixups(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_prog *prog = env->prog;
	bool expect_blinding = bpf_jit_blinding_enabled(prog);
	काष्ठा bpf_insn *insn = prog->insnsi;
	स्थिर काष्ठा bpf_func_proto *fn;
	स्थिर पूर्णांक insn_cnt = prog->len;
	स्थिर काष्ठा bpf_map_ops *ops;
	काष्ठा bpf_insn_aux_data *aux;
	काष्ठा bpf_insn insn_buf[16];
	काष्ठा bpf_prog *new_prog;
	काष्ठा bpf_map *map_ptr;
	पूर्णांक i, ret, cnt, delta = 0;

	क्रम (i = 0; i < insn_cnt; i++, insn++) अणु
		/* Make भागide-by-zero exceptions impossible. */
		अगर (insn->code == (BPF_ALU64 | BPF_MOD | BPF_X) ||
		    insn->code == (BPF_ALU64 | BPF_DIV | BPF_X) ||
		    insn->code == (BPF_ALU | BPF_MOD | BPF_X) ||
		    insn->code == (BPF_ALU | BPF_DIV | BPF_X)) अणु
			bool is64 = BPF_CLASS(insn->code) == BPF_ALU64;
			bool isभाग = BPF_OP(insn->code) == BPF_DIV;
			काष्ठा bpf_insn *patchlet;
			काष्ठा bpf_insn chk_and_भाग[] = अणु
				/* [R,W]x भाग 0 -> 0 */
				BPF_RAW_INSN((is64 ? BPF_JMP : BPF_JMP32) |
					     BPF_JNE | BPF_K, insn->src_reg,
					     0, 2, 0),
				BPF_ALU32_REG(BPF_XOR, insn->dst_reg, insn->dst_reg),
				BPF_JMP_IMM(BPF_JA, 0, 0, 1),
				*insn,
			पूर्ण;
			काष्ठा bpf_insn chk_and_mod[] = अणु
				/* [R,W]x mod 0 -> [R,W]x */
				BPF_RAW_INSN((is64 ? BPF_JMP : BPF_JMP32) |
					     BPF_JEQ | BPF_K, insn->src_reg,
					     0, 1 + (is64 ? 0 : 1), 0),
				*insn,
				BPF_JMP_IMM(BPF_JA, 0, 0, 1),
				BPF_MOV32_REG(insn->dst_reg, insn->dst_reg),
			पूर्ण;

			patchlet = isभाग ? chk_and_भाग : chk_and_mod;
			cnt = isभाग ? ARRAY_SIZE(chk_and_भाग) :
				      ARRAY_SIZE(chk_and_mod) - (is64 ? 2 : 0);

			new_prog = bpf_patch_insn_data(env, i + delta, patchlet, cnt);
			अगर (!new_prog)
				वापस -ENOMEM;

			delta    += cnt - 1;
			env->prog = prog = new_prog;
			insn      = new_prog->insnsi + i + delta;
			जारी;
		पूर्ण

		/* Implement LD_ABS and LD_IND with a reग_लिखो, अगर supported by the program type. */
		अगर (BPF_CLASS(insn->code) == BPF_LD &&
		    (BPF_MODE(insn->code) == BPF_ABS ||
		     BPF_MODE(insn->code) == BPF_IND)) अणु
			cnt = env->ops->gen_ld_असल(insn, insn_buf);
			अगर (cnt == 0 || cnt >= ARRAY_SIZE(insn_buf)) अणु
				verbose(env, "bpf verifier is misconfigured\n");
				वापस -EINVAL;
			पूर्ण

			new_prog = bpf_patch_insn_data(env, i + delta, insn_buf, cnt);
			अगर (!new_prog)
				वापस -ENOMEM;

			delta    += cnt - 1;
			env->prog = prog = new_prog;
			insn      = new_prog->insnsi + i + delta;
			जारी;
		पूर्ण

		/* Reग_लिखो poपूर्णांकer arithmetic to mitigate speculation attacks. */
		अगर (insn->code == (BPF_ALU64 | BPF_ADD | BPF_X) ||
		    insn->code == (BPF_ALU64 | BPF_SUB | BPF_X)) अणु
			स्थिर u8 code_add = BPF_ALU64 | BPF_ADD | BPF_X;
			स्थिर u8 code_sub = BPF_ALU64 | BPF_SUB | BPF_X;
			काष्ठा bpf_insn *patch = &insn_buf[0];
			bool issrc, isneg, isimm;
			u32 off_reg;

			aux = &env->insn_aux_data[i + delta];
			अगर (!aux->alu_state ||
			    aux->alu_state == BPF_ALU_NON_POINTER)
				जारी;

			isneg = aux->alu_state & BPF_ALU_NEG_VALUE;
			issrc = (aux->alu_state & BPF_ALU_SANITIZE) ==
				BPF_ALU_SANITIZE_SRC;
			isimm = aux->alu_state & BPF_ALU_IMMEDIATE;

			off_reg = issrc ? insn->src_reg : insn->dst_reg;
			अगर (isimm) अणु
				*patch++ = BPF_MOV32_IMM(BPF_REG_AX, aux->alu_limit);
			पूर्ण अन्यथा अणु
				अगर (isneg)
					*patch++ = BPF_ALU64_IMM(BPF_MUL, off_reg, -1);
				*patch++ = BPF_MOV32_IMM(BPF_REG_AX, aux->alu_limit);
				*patch++ = BPF_ALU64_REG(BPF_SUB, BPF_REG_AX, off_reg);
				*patch++ = BPF_ALU64_REG(BPF_OR, BPF_REG_AX, off_reg);
				*patch++ = BPF_ALU64_IMM(BPF_NEG, BPF_REG_AX, 0);
				*patch++ = BPF_ALU64_IMM(BPF_ARSH, BPF_REG_AX, 63);
				*patch++ = BPF_ALU64_REG(BPF_AND, BPF_REG_AX, off_reg);
			पूर्ण
			अगर (!issrc)
				*patch++ = BPF_MOV64_REG(insn->dst_reg, insn->src_reg);
			insn->src_reg = BPF_REG_AX;
			अगर (isneg)
				insn->code = insn->code == code_add ?
					     code_sub : code_add;
			*patch++ = *insn;
			अगर (issrc && isneg && !isimm)
				*patch++ = BPF_ALU64_IMM(BPF_MUL, off_reg, -1);
			cnt = patch - insn_buf;

			new_prog = bpf_patch_insn_data(env, i + delta, insn_buf, cnt);
			अगर (!new_prog)
				वापस -ENOMEM;

			delta    += cnt - 1;
			env->prog = prog = new_prog;
			insn      = new_prog->insnsi + i + delta;
			जारी;
		पूर्ण

		अगर (insn->code != (BPF_JMP | BPF_CALL))
			जारी;
		अगर (insn->src_reg == BPF_PSEUDO_CALL)
			जारी;
		अगर (insn->src_reg == BPF_PSEUDO_KFUNC_CALL) अणु
			ret = fixup_kfunc_call(env, insn);
			अगर (ret)
				वापस ret;
			जारी;
		पूर्ण

		अगर (insn->imm == BPF_FUNC_get_route_realm)
			prog->dst_needed = 1;
		अगर (insn->imm == BPF_FUNC_get_pअक्रमom_u32)
			bpf_user_rnd_init_once();
		अगर (insn->imm == BPF_FUNC_override_वापस)
			prog->kprobe_override = 1;
		अगर (insn->imm == BPF_FUNC_tail_call) अणु
			/* If we tail call पूर्णांकo other programs, we
			 * cannot make any assumptions since they can
			 * be replaced dynamically during runसमय in
			 * the program array.
			 */
			prog->cb_access = 1;
			अगर (!allow_tail_call_in_subprogs(env))
				prog->aux->stack_depth = MAX_BPF_STACK;
			prog->aux->max_pkt_offset = MAX_PACKET_OFF;

			/* mark bpf_tail_call as dअगरferent opcode to aव्योम
			 * conditional branch in the पूर्णांकerpeter क्रम every normal
			 * call and to prevent accidental JITing by JIT compiler
			 * that करोesn't support bpf_tail_call yet
			 */
			insn->imm = 0;
			insn->code = BPF_JMP | BPF_TAIL_CALL;

			aux = &env->insn_aux_data[i + delta];
			अगर (env->bpf_capable && !expect_blinding &&
			    prog->jit_requested &&
			    !bpf_map_key_poisoned(aux) &&
			    !bpf_map_ptr_poisoned(aux) &&
			    !bpf_map_ptr_unpriv(aux)) अणु
				काष्ठा bpf_jit_poke_descriptor desc = अणु
					.reason = BPF_POKE_REASON_TAIL_CALL,
					.tail_call.map = BPF_MAP_PTR(aux->map_ptr_state),
					.tail_call.key = bpf_map_key_immediate(aux),
					.insn_idx = i + delta,
				पूर्ण;

				ret = bpf_jit_add_poke_descriptor(prog, &desc);
				अगर (ret < 0) अणु
					verbose(env, "adding tail call poke descriptor failed\n");
					वापस ret;
				पूर्ण

				insn->imm = ret + 1;
				जारी;
			पूर्ण

			अगर (!bpf_map_ptr_unpriv(aux))
				जारी;

			/* instead of changing every JIT dealing with tail_call
			 * emit two extra insns:
			 * अगर (index >= max_entries) जाओ out;
			 * index &= array->index_mask;
			 * to aव्योम out-of-bounds cpu speculation
			 */
			अगर (bpf_map_ptr_poisoned(aux)) अणु
				verbose(env, "tail_call abusing map_ptr\n");
				वापस -EINVAL;
			पूर्ण

			map_ptr = BPF_MAP_PTR(aux->map_ptr_state);
			insn_buf[0] = BPF_JMP_IMM(BPF_JGE, BPF_REG_3,
						  map_ptr->max_entries, 2);
			insn_buf[1] = BPF_ALU32_IMM(BPF_AND, BPF_REG_3,
						    container_of(map_ptr,
								 काष्ठा bpf_array,
								 map)->index_mask);
			insn_buf[2] = *insn;
			cnt = 3;
			new_prog = bpf_patch_insn_data(env, i + delta, insn_buf, cnt);
			अगर (!new_prog)
				वापस -ENOMEM;

			delta    += cnt - 1;
			env->prog = prog = new_prog;
			insn      = new_prog->insnsi + i + delta;
			जारी;
		पूर्ण

		/* BPF_EMIT_CALL() assumptions in some of the map_gen_lookup
		 * and other inlining handlers are currently limited to 64 bit
		 * only.
		 */
		अगर (prog->jit_requested && BITS_PER_LONG == 64 &&
		    (insn->imm == BPF_FUNC_map_lookup_elem ||
		     insn->imm == BPF_FUNC_map_update_elem ||
		     insn->imm == BPF_FUNC_map_delete_elem ||
		     insn->imm == BPF_FUNC_map_push_elem   ||
		     insn->imm == BPF_FUNC_map_pop_elem    ||
		     insn->imm == BPF_FUNC_map_peek_elem   ||
		     insn->imm == BPF_FUNC_redirect_map)) अणु
			aux = &env->insn_aux_data[i + delta];
			अगर (bpf_map_ptr_poisoned(aux))
				जाओ patch_call_imm;

			map_ptr = BPF_MAP_PTR(aux->map_ptr_state);
			ops = map_ptr->ops;
			अगर (insn->imm == BPF_FUNC_map_lookup_elem &&
			    ops->map_gen_lookup) अणु
				cnt = ops->map_gen_lookup(map_ptr, insn_buf);
				अगर (cnt == -EOPNOTSUPP)
					जाओ patch_map_ops_generic;
				अगर (cnt <= 0 || cnt >= ARRAY_SIZE(insn_buf)) अणु
					verbose(env, "bpf verifier is misconfigured\n");
					वापस -EINVAL;
				पूर्ण

				new_prog = bpf_patch_insn_data(env, i + delta,
							       insn_buf, cnt);
				अगर (!new_prog)
					वापस -ENOMEM;

				delta    += cnt - 1;
				env->prog = prog = new_prog;
				insn      = new_prog->insnsi + i + delta;
				जारी;
			पूर्ण

			BUILD_BUG_ON(!__same_type(ops->map_lookup_elem,
				     (व्योम *(*)(काष्ठा bpf_map *map, व्योम *key))शून्य));
			BUILD_BUG_ON(!__same_type(ops->map_delete_elem,
				     (पूर्णांक (*)(काष्ठा bpf_map *map, व्योम *key))शून्य));
			BUILD_BUG_ON(!__same_type(ops->map_update_elem,
				     (पूर्णांक (*)(काष्ठा bpf_map *map, व्योम *key, व्योम *value,
					      u64 flags))शून्य));
			BUILD_BUG_ON(!__same_type(ops->map_push_elem,
				     (पूर्णांक (*)(काष्ठा bpf_map *map, व्योम *value,
					      u64 flags))शून्य));
			BUILD_BUG_ON(!__same_type(ops->map_pop_elem,
				     (पूर्णांक (*)(काष्ठा bpf_map *map, व्योम *value))शून्य));
			BUILD_BUG_ON(!__same_type(ops->map_peek_elem,
				     (पूर्णांक (*)(काष्ठा bpf_map *map, व्योम *value))शून्य));
			BUILD_BUG_ON(!__same_type(ops->map_redirect,
				     (पूर्णांक (*)(काष्ठा bpf_map *map, u32 अगरindex, u64 flags))शून्य));

patch_map_ops_generic:
			चयन (insn->imm) अणु
			हाल BPF_FUNC_map_lookup_elem:
				insn->imm = BPF_CAST_CALL(ops->map_lookup_elem) -
					    __bpf_call_base;
				जारी;
			हाल BPF_FUNC_map_update_elem:
				insn->imm = BPF_CAST_CALL(ops->map_update_elem) -
					    __bpf_call_base;
				जारी;
			हाल BPF_FUNC_map_delete_elem:
				insn->imm = BPF_CAST_CALL(ops->map_delete_elem) -
					    __bpf_call_base;
				जारी;
			हाल BPF_FUNC_map_push_elem:
				insn->imm = BPF_CAST_CALL(ops->map_push_elem) -
					    __bpf_call_base;
				जारी;
			हाल BPF_FUNC_map_pop_elem:
				insn->imm = BPF_CAST_CALL(ops->map_pop_elem) -
					    __bpf_call_base;
				जारी;
			हाल BPF_FUNC_map_peek_elem:
				insn->imm = BPF_CAST_CALL(ops->map_peek_elem) -
					    __bpf_call_base;
				जारी;
			हाल BPF_FUNC_redirect_map:
				insn->imm = BPF_CAST_CALL(ops->map_redirect) -
					    __bpf_call_base;
				जारी;
			पूर्ण

			जाओ patch_call_imm;
		पूर्ण

		/* Implement bpf_jअगरfies64 अंतरभूत. */
		अगर (prog->jit_requested && BITS_PER_LONG == 64 &&
		    insn->imm == BPF_FUNC_jअगरfies64) अणु
			काष्ठा bpf_insn ld_jअगरfies_addr[2] = अणु
				BPF_LD_IMM64(BPF_REG_0,
					     (अचिन्हित दीर्घ)&jअगरfies),
			पूर्ण;

			insn_buf[0] = ld_jअगरfies_addr[0];
			insn_buf[1] = ld_jअगरfies_addr[1];
			insn_buf[2] = BPF_LDX_MEM(BPF_DW, BPF_REG_0,
						  BPF_REG_0, 0);
			cnt = 3;

			new_prog = bpf_patch_insn_data(env, i + delta, insn_buf,
						       cnt);
			अगर (!new_prog)
				वापस -ENOMEM;

			delta    += cnt - 1;
			env->prog = prog = new_prog;
			insn      = new_prog->insnsi + i + delta;
			जारी;
		पूर्ण

patch_call_imm:
		fn = env->ops->get_func_proto(insn->imm, env->prog);
		/* all functions that have prototype and verअगरier allowed
		 * programs to call them, must be real in-kernel functions
		 */
		अगर (!fn->func) अणु
			verbose(env,
				"kernel subsystem misconfigured func %s#%d\n",
				func_id_name(insn->imm), insn->imm);
			वापस -EFAULT;
		पूर्ण
		insn->imm = fn->func - __bpf_call_base;
	पूर्ण

	/* Since poke tab is now finalized, publish aux to tracker. */
	क्रम (i = 0; i < prog->aux->size_poke_tab; i++) अणु
		map_ptr = prog->aux->poke_tab[i].tail_call.map;
		अगर (!map_ptr->ops->map_poke_track ||
		    !map_ptr->ops->map_poke_untrack ||
		    !map_ptr->ops->map_poke_run) अणु
			verbose(env, "bpf verifier is misconfigured\n");
			वापस -EINVAL;
		पूर्ण

		ret = map_ptr->ops->map_poke_track(map_ptr, prog->aux);
		अगर (ret < 0) अणु
			verbose(env, "tracking tail call prog failed\n");
			वापस ret;
		पूर्ण
	पूर्ण

	sort_kfunc_descs_by_imm(env->prog);

	वापस 0;
पूर्ण

अटल व्योम मुक्त_states(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_verअगरier_state_list *sl, *sln;
	पूर्णांक i;

	sl = env->मुक्त_list;
	जबतक (sl) अणु
		sln = sl->next;
		मुक्त_verअगरier_state(&sl->state, false);
		kमुक्त(sl);
		sl = sln;
	पूर्ण
	env->मुक्त_list = शून्य;

	अगर (!env->explored_states)
		वापस;

	क्रम (i = 0; i < state_htab_size(env); i++) अणु
		sl = env->explored_states[i];

		जबतक (sl) अणु
			sln = sl->next;
			मुक्त_verअगरier_state(&sl->state, false);
			kमुक्त(sl);
			sl = sln;
		पूर्ण
		env->explored_states[i] = शून्य;
	पूर्ण
पूर्ण

/* The verअगरier is using insn_aux_data[] to store temporary data during
 * verअगरication and to store inक्रमmation क्रम passes that run after the
 * verअगरication like dead code sanitization. करो_check_common() क्रम subprogram N
 * may analyze many other subprograms. sanitize_insn_aux_data() clears all
 * temporary data after करो_check_common() finds that subprogram N cannot be
 * verअगरied independently. pass_cnt counts the number of बार
 * करो_check_common() was run and insn->aux->seen tells the pass number
 * insn_aux_data was touched. These variables are compared to clear temporary
 * data from failed pass. For testing and experiments करो_check_common() can be
 * run multiple बार even when prior attempt to verअगरy is unsuccessful.
 *
 * Note that special handling is needed on !env->bypass_spec_v1 अगर this is
 * ever called outside of error path with subsequent program rejection.
 */
अटल व्योम sanitize_insn_aux_data(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_insn *insn = env->prog->insnsi;
	काष्ठा bpf_insn_aux_data *aux;
	पूर्णांक i, class;

	क्रम (i = 0; i < env->prog->len; i++) अणु
		class = BPF_CLASS(insn[i].code);
		अगर (class != BPF_LDX && class != BPF_STX)
			जारी;
		aux = &env->insn_aux_data[i];
		अगर (aux->seen != env->pass_cnt)
			जारी;
		स_रखो(aux, 0, दुरत्व(typeof(*aux), orig_idx));
	पूर्ण
पूर्ण

अटल पूर्णांक करो_check_common(काष्ठा bpf_verअगरier_env *env, पूर्णांक subprog)
अणु
	bool pop_log = !(env->log.level & BPF_LOG_LEVEL2);
	काष्ठा bpf_verअगरier_state *state;
	काष्ठा bpf_reg_state *regs;
	पूर्णांक ret, i;

	env->prev_linfo = शून्य;
	env->pass_cnt++;

	state = kzalloc(माप(काष्ठा bpf_verअगरier_state), GFP_KERNEL);
	अगर (!state)
		वापस -ENOMEM;
	state->curframe = 0;
	state->speculative = false;
	state->branches = 1;
	state->frame[0] = kzalloc(माप(काष्ठा bpf_func_state), GFP_KERNEL);
	अगर (!state->frame[0]) अणु
		kमुक्त(state);
		वापस -ENOMEM;
	पूर्ण
	env->cur_state = state;
	init_func_state(env, state->frame[0],
			BPF_MAIN_FUNC /* callsite */,
			0 /* frameno */,
			subprog);

	regs = state->frame[state->curframe]->regs;
	अगर (subprog || env->prog->type == BPF_PROG_TYPE_EXT) अणु
		ret = btf_prepare_func_args(env, subprog, regs);
		अगर (ret)
			जाओ out;
		क्रम (i = BPF_REG_1; i <= BPF_REG_5; i++) अणु
			अगर (regs[i].type == PTR_TO_CTX)
				mark_reg_known_zero(env, regs, i);
			अन्यथा अगर (regs[i].type == SCALAR_VALUE)
				mark_reg_unknown(env, regs, i);
			अन्यथा अगर (regs[i].type == PTR_TO_MEM_OR_शून्य) अणु
				स्थिर u32 mem_size = regs[i].mem_size;

				mark_reg_known_zero(env, regs, i);
				regs[i].mem_size = mem_size;
				regs[i].id = ++env->id_gen;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* 1st arg to a function */
		regs[BPF_REG_1].type = PTR_TO_CTX;
		mark_reg_known_zero(env, regs, BPF_REG_1);
		ret = btf_check_subprog_arg_match(env, subprog, regs);
		अगर (ret == -EFAULT)
			/* unlikely verअगरier bug. पात.
			 * ret == 0 and ret < 0 are sadly acceptable क्रम
			 * मुख्य() function due to backward compatibility.
			 * Like socket filter program may be written as:
			 * पूर्णांक bpf_prog(काष्ठा pt_regs *ctx)
			 * and never dereference that ctx in the program.
			 * 'struct pt_regs' is a type mismatch क्रम socket
			 * filter that should be using 'struct __sk_buff'.
			 */
			जाओ out;
	पूर्ण

	ret = करो_check(env);
out:
	/* check क्रम शून्य is necessary, since cur_state can be मुक्तd inside
	 * करो_check() under memory pressure.
	 */
	अगर (env->cur_state) अणु
		मुक्त_verअगरier_state(env->cur_state, true);
		env->cur_state = शून्य;
	पूर्ण
	जबतक (!pop_stack(env, शून्य, शून्य, false));
	अगर (!ret && pop_log)
		bpf_vlog_reset(&env->log, 0);
	मुक्त_states(env);
	अगर (ret)
		/* clean aux data in हाल subprog was rejected */
		sanitize_insn_aux_data(env);
	वापस ret;
पूर्ण

/* Verअगरy all global functions in a BPF program one by one based on their BTF.
 * All global functions must pass verअगरication. Otherwise the whole program is rejected.
 * Consider:
 * पूर्णांक bar(पूर्णांक);
 * पूर्णांक foo(पूर्णांक f)
 * अणु
 *    वापस bar(f);
 * पूर्ण
 * पूर्णांक bar(पूर्णांक b)
 * अणु
 *    ...
 * पूर्ण
 * foo() will be verअगरied first क्रम R1=any_scalar_value. During verअगरication it
 * will be assumed that bar() alपढ़ोy verअगरied successfully and call to bar()
 * from foo() will be checked क्रम type match only. Later bar() will be verअगरied
 * independently to check that it's safe क्रम R1=any_scalar_value.
 */
अटल पूर्णांक करो_check_subprogs(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_prog_aux *aux = env->prog->aux;
	पूर्णांक i, ret;

	अगर (!aux->func_info)
		वापस 0;

	क्रम (i = 1; i < env->subprog_cnt; i++) अणु
		अगर (aux->func_info_aux[i].linkage != BTF_FUNC_GLOBAL)
			जारी;
		env->insn_idx = env->subprog_info[i].start;
		WARN_ON_ONCE(env->insn_idx == 0);
		ret = करो_check_common(env, i);
		अगर (ret) अणु
			वापस ret;
		पूर्ण अन्यथा अगर (env->log.level & BPF_LOG_LEVEL) अणु
			verbose(env,
				"Func#%d is safe for any args that match its prototype\n",
				i);
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक करो_check_मुख्य(काष्ठा bpf_verअगरier_env *env)
अणु
	पूर्णांक ret;

	env->insn_idx = 0;
	ret = करो_check_common(env, 0);
	अगर (!ret)
		env->prog->aux->stack_depth = env->subprog_info[0].stack_depth;
	वापस ret;
पूर्ण


अटल व्योम prपूर्णांक_verअगरication_stats(काष्ठा bpf_verअगरier_env *env)
अणु
	पूर्णांक i;

	अगर (env->log.level & BPF_LOG_STATS) अणु
		verbose(env, "verification time %lld usec\n",
			भाग_u64(env->verअगरication_समय, 1000));
		verbose(env, "stack depth ");
		क्रम (i = 0; i < env->subprog_cnt; i++) अणु
			u32 depth = env->subprog_info[i].stack_depth;

			verbose(env, "%d", depth);
			अगर (i + 1 < env->subprog_cnt)
				verbose(env, "+");
		पूर्ण
		verbose(env, "\n");
	पूर्ण
	verbose(env, "processed %d insns (limit %d) max_states_per_insn %d "
		"total_states %d peak_states %d mark_read %d\n",
		env->insn_processed, BPF_COMPLEXITY_LIMIT_INSNS,
		env->max_states_per_insn, env->total_states,
		env->peak_states, env->दीर्घest_mark_पढ़ो_walk);
पूर्ण

अटल पूर्णांक check_काष्ठा_ops_btf_id(काष्ठा bpf_verअगरier_env *env)
अणु
	स्थिर काष्ठा btf_type *t, *func_proto;
	स्थिर काष्ठा bpf_काष्ठा_ops *st_ops;
	स्थिर काष्ठा btf_member *member;
	काष्ठा bpf_prog *prog = env->prog;
	u32 btf_id, member_idx;
	स्थिर अक्षर *mname;

	अगर (!prog->gpl_compatible) अणु
		verbose(env, "struct ops programs must have a GPL compatible license\n");
		वापस -EINVAL;
	पूर्ण

	btf_id = prog->aux->attach_btf_id;
	st_ops = bpf_काष्ठा_ops_find(btf_id);
	अगर (!st_ops) अणु
		verbose(env, "attach_btf_id %u is not a supported struct\n",
			btf_id);
		वापस -ENOTSUPP;
	पूर्ण

	t = st_ops->type;
	member_idx = prog->expected_attach_type;
	अगर (member_idx >= btf_type_vlen(t)) अणु
		verbose(env, "attach to invalid member idx %u of struct %s\n",
			member_idx, st_ops->name);
		वापस -EINVAL;
	पूर्ण

	member = &btf_type_member(t)[member_idx];
	mname = btf_name_by_offset(btf_vmlinux, member->name_off);
	func_proto = btf_type_resolve_func_ptr(btf_vmlinux, member->type,
					       शून्य);
	अगर (!func_proto) अणु
		verbose(env, "attach to invalid member %s(@idx %u) of struct %s\n",
			mname, member_idx, st_ops->name);
		वापस -EINVAL;
	पूर्ण

	अगर (st_ops->check_member) अणु
		पूर्णांक err = st_ops->check_member(t, member);

		अगर (err) अणु
			verbose(env, "attach to unsupported member %s of struct %s\n",
				mname, st_ops->name);
			वापस err;
		पूर्ण
	पूर्ण

	prog->aux->attach_func_proto = func_proto;
	prog->aux->attach_func_name = mname;
	env->ops = st_ops->verअगरier_ops;

	वापस 0;
पूर्ण
#घोषणा SECURITY_PREFIX "security_"

अटल पूर्णांक check_attach_modअगरy_वापस(अचिन्हित दीर्घ addr, स्थिर अक्षर *func_name)
अणु
	अगर (within_error_injection_list(addr) ||
	    !म_भेदन(SECURITY_PREFIX, func_name, माप(SECURITY_PREFIX) - 1))
		वापस 0;

	वापस -EINVAL;
पूर्ण

/* list of non-sleepable functions that are otherwise on
 * ALLOW_ERROR_INJECTION list
 */
BTF_SET_START(btf_non_sleepable_error_inject)
/* Three functions below can be called from sleepable and non-sleepable context.
 * Assume non-sleepable from bpf safety poपूर्णांक of view.
 */
BTF_ID(func, __add_to_page_cache_locked)
BTF_ID(func, should_fail_alloc_page)
BTF_ID(func, should_failslab)
BTF_SET_END(btf_non_sleepable_error_inject)

अटल पूर्णांक check_non_sleepable_error_inject(u32 btf_id)
अणु
	वापस btf_id_set_contains(&btf_non_sleepable_error_inject, btf_id);
पूर्ण

पूर्णांक bpf_check_attach_target(काष्ठा bpf_verअगरier_log *log,
			    स्थिर काष्ठा bpf_prog *prog,
			    स्थिर काष्ठा bpf_prog *tgt_prog,
			    u32 btf_id,
			    काष्ठा bpf_attach_target_info *tgt_info)
अणु
	bool prog_extension = prog->type == BPF_PROG_TYPE_EXT;
	स्थिर अक्षर prefix[] = "btf_trace_";
	पूर्णांक ret = 0, subprog = -1, i;
	स्थिर काष्ठा btf_type *t;
	bool conservative = true;
	स्थिर अक्षर *tname;
	काष्ठा btf *btf;
	दीर्घ addr = 0;

	अगर (!btf_id) अणु
		bpf_log(log, "Tracing programs must provide btf_id\n");
		वापस -EINVAL;
	पूर्ण
	btf = tgt_prog ? tgt_prog->aux->btf : prog->aux->attach_btf;
	अगर (!btf) अणु
		bpf_log(log,
			"FENTRY/FEXIT program can only be attached to another program annotated with BTF\n");
		वापस -EINVAL;
	पूर्ण
	t = btf_type_by_id(btf, btf_id);
	अगर (!t) अणु
		bpf_log(log, "attach_btf_id %u is invalid\n", btf_id);
		वापस -EINVAL;
	पूर्ण
	tname = btf_name_by_offset(btf, t->name_off);
	अगर (!tname) अणु
		bpf_log(log, "attach_btf_id %u doesn't have a name\n", btf_id);
		वापस -EINVAL;
	पूर्ण
	अगर (tgt_prog) अणु
		काष्ठा bpf_prog_aux *aux = tgt_prog->aux;

		क्रम (i = 0; i < aux->func_info_cnt; i++)
			अगर (aux->func_info[i].type_id == btf_id) अणु
				subprog = i;
				अवरोध;
			पूर्ण
		अगर (subprog == -1) अणु
			bpf_log(log, "Subprog %s doesn't exist\n", tname);
			वापस -EINVAL;
		पूर्ण
		conservative = aux->func_info_aux[subprog].unreliable;
		अगर (prog_extension) अणु
			अगर (conservative) अणु
				bpf_log(log,
					"Cannot replace static functions\n");
				वापस -EINVAL;
			पूर्ण
			अगर (!prog->jit_requested) अणु
				bpf_log(log,
					"Extension programs should be JITed\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (!tgt_prog->jited) अणु
			bpf_log(log, "Can attach to only JITed progs\n");
			वापस -EINVAL;
		पूर्ण
		अगर (tgt_prog->type == prog->type) अणु
			/* Cannot fentry/fनिकास another fentry/fनिकास program.
			 * Cannot attach program extension to another extension.
			 * It's ok to attach fentry/fनिकास to extension program.
			 */
			bpf_log(log, "Cannot recursively attach\n");
			वापस -EINVAL;
		पूर्ण
		अगर (tgt_prog->type == BPF_PROG_TYPE_TRACING &&
		    prog_extension &&
		    (tgt_prog->expected_attach_type == BPF_TRACE_FENTRY ||
		     tgt_prog->expected_attach_type == BPF_TRACE_FEXIT)) अणु
			/* Program extensions can extend all program types
			 * except fentry/fनिकास. The reason is the following.
			 * The fentry/fनिकास programs are used क्रम perक्रमmance
			 * analysis, stats and can be attached to any program
			 * type except themselves. When extension program is
			 * replacing XDP function it is necessary to allow
			 * perक्रमmance analysis of all functions. Both original
			 * XDP program and its program extension. Hence
			 * attaching fentry/fनिकास to BPF_PROG_TYPE_EXT is
			 * allowed. If extending of fentry/fनिकास was allowed it
			 * would be possible to create दीर्घ call chain
			 * fentry->extension->fentry->extension beyond
			 * reasonable stack size. Hence extending fentry is not
			 * allowed.
			 */
			bpf_log(log, "Cannot extend fentry/fexit\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (prog_extension) अणु
			bpf_log(log, "Cannot replace kernel functions\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	चयन (prog->expected_attach_type) अणु
	हाल BPF_TRACE_RAW_TP:
		अगर (tgt_prog) अणु
			bpf_log(log,
				"Only FENTRY/FEXIT progs are attachable to another BPF prog\n");
			वापस -EINVAL;
		पूर्ण
		अगर (!btf_type_is_प्रकार(t)) अणु
			bpf_log(log, "attach_btf_id %u is not a typedef\n",
				btf_id);
			वापस -EINVAL;
		पूर्ण
		अगर (म_भेदन(prefix, tname, माप(prefix) - 1)) अणु
			bpf_log(log, "attach_btf_id %u points to wrong type name %s\n",
				btf_id, tname);
			वापस -EINVAL;
		पूर्ण
		tname += माप(prefix) - 1;
		t = btf_type_by_id(btf, t->type);
		अगर (!btf_type_is_ptr(t))
			/* should never happen in valid vmlinux build */
			वापस -EINVAL;
		t = btf_type_by_id(btf, t->type);
		अगर (!btf_type_is_func_proto(t))
			/* should never happen in valid vmlinux build */
			वापस -EINVAL;

		अवरोध;
	हाल BPF_TRACE_ITER:
		अगर (!btf_type_is_func(t)) अणु
			bpf_log(log, "attach_btf_id %u is not a function\n",
				btf_id);
			वापस -EINVAL;
		पूर्ण
		t = btf_type_by_id(btf, t->type);
		अगर (!btf_type_is_func_proto(t))
			वापस -EINVAL;
		ret = btf_distill_func_proto(log, btf, t, tname, &tgt_info->भ_शेषel);
		अगर (ret)
			वापस ret;
		अवरोध;
	शेष:
		अगर (!prog_extension)
			वापस -EINVAL;
		fallthrough;
	हाल BPF_MODIFY_RETURN:
	हाल BPF_LSM_MAC:
	हाल BPF_TRACE_FENTRY:
	हाल BPF_TRACE_FEXIT:
		अगर (!btf_type_is_func(t)) अणु
			bpf_log(log, "attach_btf_id %u is not a function\n",
				btf_id);
			वापस -EINVAL;
		पूर्ण
		अगर (prog_extension &&
		    btf_check_type_match(log, prog, btf, t))
			वापस -EINVAL;
		t = btf_type_by_id(btf, t->type);
		अगर (!btf_type_is_func_proto(t))
			वापस -EINVAL;

		अगर ((prog->aux->saved_dst_prog_type || prog->aux->saved_dst_attach_type) &&
		    (!tgt_prog || prog->aux->saved_dst_prog_type != tgt_prog->type ||
		     prog->aux->saved_dst_attach_type != tgt_prog->expected_attach_type))
			वापस -EINVAL;

		अगर (tgt_prog && conservative)
			t = शून्य;

		ret = btf_distill_func_proto(log, btf, t, tname, &tgt_info->भ_शेषel);
		अगर (ret < 0)
			वापस ret;

		अगर (tgt_prog) अणु
			अगर (subprog == 0)
				addr = (दीर्घ) tgt_prog->bpf_func;
			अन्यथा
				addr = (दीर्घ) tgt_prog->aux->func[subprog]->bpf_func;
		पूर्ण अन्यथा अणु
			addr = kallsyms_lookup_name(tname);
			अगर (!addr) अणु
				bpf_log(log,
					"The address of function %s cannot be found\n",
					tname);
				वापस -ENOENT;
			पूर्ण
		पूर्ण

		अगर (prog->aux->sleepable) अणु
			ret = -EINVAL;
			चयन (prog->type) अणु
			हाल BPF_PROG_TYPE_TRACING:
				/* fentry/fनिकास/भ_शेष_ret progs can be sleepable only अगर they are
				 * attached to ALLOW_ERROR_INJECTION and are not in denylist.
				 */
				अगर (!check_non_sleepable_error_inject(btf_id) &&
				    within_error_injection_list(addr))
					ret = 0;
				अवरोध;
			हाल BPF_PROG_TYPE_LSM:
				/* LSM progs check that they are attached to bpf_lsm_*() funcs.
				 * Only some of them are sleepable.
				 */
				अगर (bpf_lsm_is_sleepable_hook(btf_id))
					ret = 0;
				अवरोध;
			शेष:
				अवरोध;
			पूर्ण
			अगर (ret) अणु
				bpf_log(log, "%s is not sleepable\n", tname);
				वापस ret;
			पूर्ण
		पूर्ण अन्यथा अगर (prog->expected_attach_type == BPF_MODIFY_RETURN) अणु
			अगर (tgt_prog) अणु
				bpf_log(log, "can't modify return codes of BPF programs\n");
				वापस -EINVAL;
			पूर्ण
			ret = check_attach_modअगरy_वापस(addr, tname);
			अगर (ret) अणु
				bpf_log(log, "%s() is not modifiable\n", tname);
				वापस ret;
			पूर्ण
		पूर्ण

		अवरोध;
	पूर्ण
	tgt_info->tgt_addr = addr;
	tgt_info->tgt_name = tname;
	tgt_info->tgt_type = t;
	वापस 0;
पूर्ण

BTF_SET_START(btf_id_deny)
BTF_ID_UNUSED
#अगर_घोषित CONFIG_SMP
BTF_ID(func, migrate_disable)
BTF_ID(func, migrate_enable)
#पूर्ण_अगर
#अगर !defined CONFIG_PREEMPT_RCU && !defined CONFIG_TINY_RCU
BTF_ID(func, rcu_पढ़ो_unlock_strict)
#पूर्ण_अगर
BTF_SET_END(btf_id_deny)

अटल पूर्णांक check_attach_btf_id(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_prog *prog = env->prog;
	काष्ठा bpf_prog *tgt_prog = prog->aux->dst_prog;
	काष्ठा bpf_attach_target_info tgt_info = अणुपूर्ण;
	u32 btf_id = prog->aux->attach_btf_id;
	काष्ठा bpf_trampoline *tr;
	पूर्णांक ret;
	u64 key;

	अगर (prog->aux->sleepable && prog->type != BPF_PROG_TYPE_TRACING &&
	    prog->type != BPF_PROG_TYPE_LSM) अणु
		verbose(env, "Only fentry/fexit/fmod_ret and lsm programs can be sleepable\n");
		वापस -EINVAL;
	पूर्ण

	अगर (prog->type == BPF_PROG_TYPE_STRUCT_OPS)
		वापस check_काष्ठा_ops_btf_id(env);

	अगर (prog->type != BPF_PROG_TYPE_TRACING &&
	    prog->type != BPF_PROG_TYPE_LSM &&
	    prog->type != BPF_PROG_TYPE_EXT)
		वापस 0;

	ret = bpf_check_attach_target(&env->log, prog, tgt_prog, btf_id, &tgt_info);
	अगर (ret)
		वापस ret;

	अगर (tgt_prog && prog->type == BPF_PROG_TYPE_EXT) अणु
		/* to make freplace equivalent to their tarमाला_लो, they need to
		 * inherit env->ops and expected_attach_type क्रम the rest of the
		 * verअगरication
		 */
		env->ops = bpf_verअगरier_ops[tgt_prog->type];
		prog->expected_attach_type = tgt_prog->expected_attach_type;
	पूर्ण

	/* store info about the attachment target that will be used later */
	prog->aux->attach_func_proto = tgt_info.tgt_type;
	prog->aux->attach_func_name = tgt_info.tgt_name;

	अगर (tgt_prog) अणु
		prog->aux->saved_dst_prog_type = tgt_prog->type;
		prog->aux->saved_dst_attach_type = tgt_prog->expected_attach_type;
	पूर्ण

	अगर (prog->expected_attach_type == BPF_TRACE_RAW_TP) अणु
		prog->aux->attach_btf_trace = true;
		वापस 0;
	पूर्ण अन्यथा अगर (prog->expected_attach_type == BPF_TRACE_ITER) अणु
		अगर (!bpf_iter_prog_supported(prog))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	अगर (prog->type == BPF_PROG_TYPE_LSM) अणु
		ret = bpf_lsm_verअगरy_prog(&env->log, prog);
		अगर (ret < 0)
			वापस ret;
	पूर्ण अन्यथा अगर (prog->type == BPF_PROG_TYPE_TRACING &&
		   btf_id_set_contains(&btf_id_deny, btf_id)) अणु
		वापस -EINVAL;
	पूर्ण

	key = bpf_trampoline_compute_key(tgt_prog, prog->aux->attach_btf, btf_id);
	tr = bpf_trampoline_get(key, &tgt_info);
	अगर (!tr)
		वापस -ENOMEM;

	prog->aux->dst_trampoline = tr;
	वापस 0;
पूर्ण

काष्ठा btf *bpf_get_btf_vmlinux(व्योम)
अणु
	अगर (!btf_vmlinux && IS_ENABLED(CONFIG_DEBUG_INFO_BTF)) अणु
		mutex_lock(&bpf_verअगरier_lock);
		अगर (!btf_vmlinux)
			btf_vmlinux = btf_parse_vmlinux();
		mutex_unlock(&bpf_verअगरier_lock);
	पूर्ण
	वापस btf_vmlinux;
पूर्ण

पूर्णांक bpf_check(काष्ठा bpf_prog **prog, जोड़ bpf_attr *attr,
	      जोड़ bpf_attr __user *uattr)
अणु
	u64 start_समय = kसमय_get_ns();
	काष्ठा bpf_verअगरier_env *env;
	काष्ठा bpf_verअगरier_log *log;
	पूर्णांक i, len, ret = -EINVAL;
	bool is_priv;

	/* no program is valid */
	अगर (ARRAY_SIZE(bpf_verअगरier_ops) == 0)
		वापस -EINVAL;

	/* 'struct bpf_verifier_env' can be global, but since it's not small,
	 * allocate/मुक्त it every समय bpf_check() is called
	 */
	env = kzalloc(माप(काष्ठा bpf_verअगरier_env), GFP_KERNEL);
	अगर (!env)
		वापस -ENOMEM;
	log = &env->log;

	len = (*prog)->len;
	env->insn_aux_data =
		vzalloc(array_size(माप(काष्ठा bpf_insn_aux_data), len));
	ret = -ENOMEM;
	अगर (!env->insn_aux_data)
		जाओ err_मुक्त_env;
	क्रम (i = 0; i < len; i++)
		env->insn_aux_data[i].orig_idx = i;
	env->prog = *prog;
	env->ops = bpf_verअगरier_ops[env->prog->type];
	is_priv = bpf_capable();

	bpf_get_btf_vmlinux();

	/* grab the mutex to protect few globals used by verअगरier */
	अगर (!is_priv)
		mutex_lock(&bpf_verअगरier_lock);

	अगर (attr->log_level || attr->log_buf || attr->log_size) अणु
		/* user requested verbose verअगरier output
		 * and supplied buffer to store the verअगरication trace
		 */
		log->level = attr->log_level;
		log->ubuf = (अक्षर __user *) (अचिन्हित दीर्घ) attr->log_buf;
		log->len_total = attr->log_size;

		ret = -EINVAL;
		/* log attributes have to be sane */
		अगर (log->len_total < 128 || log->len_total > अच_पूर्णांक_उच्च >> 2 ||
		    !log->level || !log->ubuf || log->level & ~BPF_LOG_MASK)
			जाओ err_unlock;
	पूर्ण

	अगर (IS_ERR(btf_vmlinux)) अणु
		/* Either gcc or pahole or kernel are broken. */
		verbose(env, "in-kernel BTF is malformed\n");
		ret = PTR_ERR(btf_vmlinux);
		जाओ skip_full_check;
	पूर्ण

	env->strict_alignment = !!(attr->prog_flags & BPF_F_STRICT_ALIGNMENT);
	अगर (!IS_ENABLED(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS))
		env->strict_alignment = true;
	अगर (attr->prog_flags & BPF_F_ANY_ALIGNMENT)
		env->strict_alignment = false;

	env->allow_ptr_leaks = bpf_allow_ptr_leaks();
	env->allow_uninit_stack = bpf_allow_uninit_stack();
	env->allow_ptr_to_map_access = bpf_allow_ptr_to_map_access();
	env->bypass_spec_v1 = bpf_bypass_spec_v1();
	env->bypass_spec_v4 = bpf_bypass_spec_v4();
	env->bpf_capable = bpf_capable();

	अगर (is_priv)
		env->test_state_freq = attr->prog_flags & BPF_F_TEST_STATE_FREQ;

	env->explored_states = kvसुस्मृति(state_htab_size(env),
				       माप(काष्ठा bpf_verअगरier_state_list *),
				       GFP_USER);
	ret = -ENOMEM;
	अगर (!env->explored_states)
		जाओ skip_full_check;

	ret = add_subprog_and_kfunc(env);
	अगर (ret < 0)
		जाओ skip_full_check;

	ret = check_subprogs(env);
	अगर (ret < 0)
		जाओ skip_full_check;

	ret = check_btf_info(env, attr, uattr);
	अगर (ret < 0)
		जाओ skip_full_check;

	ret = check_attach_btf_id(env);
	अगर (ret)
		जाओ skip_full_check;

	ret = resolve_pseuकरो_ldimm64(env);
	अगर (ret < 0)
		जाओ skip_full_check;

	अगर (bpf_prog_is_dev_bound(env->prog->aux)) अणु
		ret = bpf_prog_offload_verअगरier_prep(env->prog);
		अगर (ret)
			जाओ skip_full_check;
	पूर्ण

	ret = check_cfg(env);
	अगर (ret < 0)
		जाओ skip_full_check;

	ret = करो_check_subprogs(env);
	ret = ret ?: करो_check_मुख्य(env);

	अगर (ret == 0 && bpf_prog_is_dev_bound(env->prog->aux))
		ret = bpf_prog_offload_finalize(env);

skip_full_check:
	kvमुक्त(env->explored_states);

	अगर (ret == 0)
		ret = check_max_stack_depth(env);

	/* inकाष्ठाion reग_लिखोs happen after this poपूर्णांक */
	अगर (is_priv) अणु
		अगर (ret == 0)
			opt_hard_wire_dead_code_branches(env);
		अगर (ret == 0)
			ret = opt_हटाओ_dead_code(env);
		अगर (ret == 0)
			ret = opt_हटाओ_nops(env);
	पूर्ण अन्यथा अणु
		अगर (ret == 0)
			sanitize_dead_code(env);
	पूर्ण

	अगर (ret == 0)
		/* program is valid, convert *(u32*)(ctx + off) accesses */
		ret = convert_ctx_accesses(env);

	अगर (ret == 0)
		ret = करो_misc_fixups(env);

	/* करो 32-bit optimization after insn patching has करोne so those patched
	 * insns could be handled correctly.
	 */
	अगर (ret == 0 && !bpf_prog_is_dev_bound(env->prog->aux)) अणु
		ret = opt_subreg_zext_lo32_rnd_hi32(env, attr);
		env->prog->aux->verअगरier_zext = bpf_jit_needs_zext() ? !ret
								     : false;
	पूर्ण

	अगर (ret == 0)
		ret = fixup_call_args(env);

	env->verअगरication_समय = kसमय_get_ns() - start_समय;
	prपूर्णांक_verअगरication_stats(env);

	अगर (log->level && bpf_verअगरier_log_full(log))
		ret = -ENOSPC;
	अगर (log->level && !log->ubuf) अणु
		ret = -EFAULT;
		जाओ err_release_maps;
	पूर्ण

	अगर (ret)
		जाओ err_release_maps;

	अगर (env->used_map_cnt) अणु
		/* अगर program passed verअगरier, update used_maps in bpf_prog_info */
		env->prog->aux->used_maps = kदो_स्मृति_array(env->used_map_cnt,
							  माप(env->used_maps[0]),
							  GFP_KERNEL);

		अगर (!env->prog->aux->used_maps) अणु
			ret = -ENOMEM;
			जाओ err_release_maps;
		पूर्ण

		स_नकल(env->prog->aux->used_maps, env->used_maps,
		       माप(env->used_maps[0]) * env->used_map_cnt);
		env->prog->aux->used_map_cnt = env->used_map_cnt;
	पूर्ण
	अगर (env->used_btf_cnt) अणु
		/* अगर program passed verअगरier, update used_btfs in bpf_prog_aux */
		env->prog->aux->used_btfs = kदो_स्मृति_array(env->used_btf_cnt,
							  माप(env->used_btfs[0]),
							  GFP_KERNEL);
		अगर (!env->prog->aux->used_btfs) अणु
			ret = -ENOMEM;
			जाओ err_release_maps;
		पूर्ण

		स_नकल(env->prog->aux->used_btfs, env->used_btfs,
		       माप(env->used_btfs[0]) * env->used_btf_cnt);
		env->prog->aux->used_btf_cnt = env->used_btf_cnt;
	पूर्ण
	अगर (env->used_map_cnt || env->used_btf_cnt) अणु
		/* program is valid. Convert pseuकरो bpf_ld_imm64 पूर्णांकo generic
		 * bpf_ld_imm64 inकाष्ठाions
		 */
		convert_pseuकरो_ld_imm64(env);
	पूर्ण

	adjust_btf_func(env);

err_release_maps:
	अगर (!env->prog->aux->used_maps)
		/* अगर we didn't copy map poपूर्णांकers पूर्णांकo bpf_prog_info, release
		 * them now. Otherwise मुक्त_used_maps() will release them.
		 */
		release_maps(env);
	अगर (!env->prog->aux->used_btfs)
		release_btfs(env);

	/* extension progs temporarily inherit the attach_type of their tarमाला_लो
	   क्रम verअगरication purposes, so set it back to zero beक्रमe वापसing
	 */
	अगर (env->prog->type == BPF_PROG_TYPE_EXT)
		env->prog->expected_attach_type = 0;

	*prog = env->prog;
err_unlock:
	अगर (!is_priv)
		mutex_unlock(&bpf_verअगरier_lock);
	vमुक्त(env->insn_aux_data);
err_मुक्त_env:
	kमुक्त(env);
	वापस ret;
पूर्ण
