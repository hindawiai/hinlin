<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/* Copyright (c) 2011-2014 PLUMgrid, http://plumgrid.com
 */
#अगर_अघोषित _LINUX_BPF_VERIFIER_H
#घोषणा _LINUX_BPF_VERIFIER_H 1

#समावेश <linux/bpf.h> /* क्रम क्रमागत bpf_reg_type */
#समावेश <linux/btf.h> /* क्रम काष्ठा btf and btf_id() */
#समावेश <linux/filter.h> /* क्रम MAX_BPF_STACK */
#समावेश <linux/tnum.h>

/* Maximum variable offset umax_value permitted when resolving memory accesses.
 * In practice this is far bigger than any realistic poपूर्णांकer offset; this limit
 * ensures that umax_value + (पूर्णांक)off + (पूर्णांक)size cannot overflow a u64.
 */
#घोषणा BPF_MAX_VAR_OFF	(1 << 29)
/* Maximum variable size permitted क्रम ARG_CONST_SIZE[_OR_ZERO].  This ensures
 * that converting umax_value to पूर्णांक cannot overflow.
 */
#घोषणा BPF_MAX_VAR_SIZ	(1 << 29)

/* Liveness marks, used क्रम रेजिस्टरs and spilled-regs (in stack slots).
 * Read marks propagate upwards until they find a ग_लिखो mark; they record that
 * "one of this state's descendants read this reg" (and thereक्रमe the reg is
 * relevant क्रम states_equal() checks).
 * Write marks collect करोwnwards and करो not propagate; they record that "the
 * straight-line code that reached this state (from its parent) wrote this reg"
 * (and thereक्रमe that पढ़ोs propagated from this state or its descendants
 * should not propagate to its parent).
 * A state with a ग_लिखो mark can receive पढ़ो marks; it just won't propagate
 * them to its parent, since the ग_लिखो mark is a property, not of the state,
 * but of the link between it and its parent.  See mark_reg_पढ़ो() and
 * mark_stack_slot_पढ़ो() in kernel/bpf/verअगरier.c.
 */
क्रमागत bpf_reg_liveness अणु
	REG_LIVE_NONE = 0, /* reg hasn't been पढ़ो or written this branch */
	REG_LIVE_READ32 = 0x1, /* reg was पढ़ो, so we're sensitive to initial value */
	REG_LIVE_READ64 = 0x2, /* likewise, but full 64-bit content matters */
	REG_LIVE_READ = REG_LIVE_READ32 | REG_LIVE_READ64,
	REG_LIVE_WRITTEN = 0x4, /* reg was written first, screening off later पढ़ोs */
	REG_LIVE_DONE = 0x8, /* liveness won't be updating this रेजिस्टर anymore */
पूर्ण;

काष्ठा bpf_reg_state अणु
	/* Ordering of fields matters.  See states_equal() */
	क्रमागत bpf_reg_type type;
	/* Fixed part of poपूर्णांकer offset, poपूर्णांकer types only */
	s32 off;
	जोड़ अणु
		/* valid when type == PTR_TO_PACKET */
		पूर्णांक range;

		/* valid when type == CONST_PTR_TO_MAP | PTR_TO_MAP_VALUE |
		 *   PTR_TO_MAP_VALUE_OR_शून्य
		 */
		काष्ठा bpf_map *map_ptr;

		/* क्रम PTR_TO_BTF_ID */
		काष्ठा अणु
			काष्ठा btf *btf;
			u32 btf_id;
		पूर्ण;

		u32 mem_size; /* क्रम PTR_TO_MEM | PTR_TO_MEM_OR_शून्य */

		/* Max size from any of the above. */
		काष्ठा अणु
			अचिन्हित दीर्घ raw1;
			अचिन्हित दीर्घ raw2;
		पूर्ण raw;

		u32 subprogno; /* क्रम PTR_TO_FUNC */
	पूर्ण;
	/* For PTR_TO_PACKET, used to find other poपूर्णांकers with the same variable
	 * offset, so they can share range knowledge.
	 * For PTR_TO_MAP_VALUE_OR_शून्य this is used to share which map value we
	 * came from, when one is tested क्रम != शून्य.
	 * For PTR_TO_MEM_OR_शून्य this is used to identअगरy memory allocation
	 * क्रम the purpose of tracking that it's मुक्तd.
	 * For PTR_TO_SOCKET this is used to share which poपूर्णांकers retain the
	 * same reference to the socket, to determine proper reference मुक्तing.
	 */
	u32 id;
	/* PTR_TO_SOCKET and PTR_TO_TCP_SOCK could be a ptr वापसed
	 * from a poपूर्णांकer-cast helper, bpf_sk_fullsock() and
	 * bpf_tcp_sock().
	 *
	 * Consider the following where "sk" is a reference counted
	 * poपूर्णांकer वापसed from "sk = bpf_sk_lookup_tcp();":
	 *
	 * 1: sk = bpf_sk_lookup_tcp();
	 * 2: अगर (!sk) अणु वापस 0; पूर्ण
	 * 3: fullsock = bpf_sk_fullsock(sk);
	 * 4: अगर (!fullsock) अणु bpf_sk_release(sk); वापस 0; पूर्ण
	 * 5: tp = bpf_tcp_sock(fullsock);
	 * 6: अगर (!tp) अणु bpf_sk_release(sk); वापस 0; पूर्ण
	 * 7: bpf_sk_release(sk);
	 * 8: snd_cwnd = tp->snd_cwnd;  // verअगरier will complain
	 *
	 * After bpf_sk_release(sk) at line 7, both "fullsock" ptr and
	 * "tp" ptr should be invalidated also.  In order to करो that,
	 * the reg holding "fullsock" and "sk" need to remember
	 * the original refcounted ptr id (i.e. sk_reg->id) in ref_obj_id
	 * such that the verअगरier can reset all regs which have
	 * ref_obj_id matching the sk_reg->id.
	 *
	 * sk_reg->ref_obj_id is set to sk_reg->id at line 1.
	 * sk_reg->id will stay as शून्य-marking purpose only.
	 * After शून्य-marking is करोne, sk_reg->id can be reset to 0.
	 *
	 * After "fullsock = bpf_sk_fullsock(sk);" at line 3,
	 * fullsock_reg->ref_obj_id is set to sk_reg->ref_obj_id.
	 *
	 * After "tp = bpf_tcp_sock(fullsock);" at line 5,
	 * tp_reg->ref_obj_id is set to fullsock_reg->ref_obj_id
	 * which is the same as sk_reg->ref_obj_id.
	 *
	 * From the verअगरier perspective, अगर sk, fullsock and tp
	 * are not शून्य, they are the same ptr with dअगरferent
	 * reg->type.  In particular, bpf_sk_release(tp) is also
	 * allowed and has the same effect as bpf_sk_release(sk).
	 */
	u32 ref_obj_id;
	/* For scalar types (SCALAR_VALUE), this represents our knowledge of
	 * the actual value.
	 * For poपूर्णांकer types, this represents the variable part of the offset
	 * from the poपूर्णांकed-to object, and is shared with all bpf_reg_states
	 * with the same id as us.
	 */
	काष्ठा tnum var_off;
	/* Used to determine अगर any memory access using this रेजिस्टर will
	 * result in a bad access.
	 * These refer to the same value as var_off, not necessarily the actual
	 * contents of the रेजिस्टर.
	 */
	s64 smin_value; /* minimum possible (s64)value */
	s64 smax_value; /* maximum possible (s64)value */
	u64 umin_value; /* minimum possible (u64)value */
	u64 umax_value; /* maximum possible (u64)value */
	s32 s32_min_value; /* minimum possible (s32)value */
	s32 s32_max_value; /* maximum possible (s32)value */
	u32 u32_min_value; /* minimum possible (u32)value */
	u32 u32_max_value; /* maximum possible (u32)value */
	/* parentage chain क्रम liveness checking */
	काष्ठा bpf_reg_state *parent;
	/* Inside the callee two रेजिस्टरs can be both PTR_TO_STACK like
	 * R1=fp-8 and R2=fp-8, but one of them poपूर्णांकs to this function stack
	 * जबतक another to the caller's stack. To differentiate them 'frameno'
	 * is used which is an index in bpf_verअगरier_state->frame[] array
	 * poपूर्णांकing to bpf_func_state.
	 */
	u32 frameno;
	/* Tracks subreg definition. The stored value is the insn_idx of the
	 * writing insn. This is safe because subreg_def is used beक्रमe any insn
	 * patching which only happens after मुख्य verअगरication finished.
	 */
	s32 subreg_def;
	क्रमागत bpf_reg_liveness live;
	/* अगर (!precise && SCALAR_VALUE) min/max/tnum करोn't affect safety */
	bool precise;
पूर्ण;

क्रमागत bpf_stack_slot_type अणु
	STACK_INVALID,    /* nothing was stored in this stack slot */
	STACK_SPILL,      /* रेजिस्टर spilled पूर्णांकo stack */
	STACK_MISC,	  /* BPF program wrote some data पूर्णांकo this slot */
	STACK_ZERO,	  /* BPF program wrote स्थिरant zero */
पूर्ण;

#घोषणा BPF_REG_SIZE 8	/* size of eBPF रेजिस्टर in bytes */

काष्ठा bpf_stack_state अणु
	काष्ठा bpf_reg_state spilled_ptr;
	u8 slot_type[BPF_REG_SIZE];
पूर्ण;

काष्ठा bpf_reference_state अणु
	/* Track each reference created with a unique id, even अगर the same
	 * inकाष्ठाion creates the reference multiple बार (eg, via CALL).
	 */
	पूर्णांक id;
	/* Inकाष्ठाion where the allocation of this reference occurred. This
	 * is used purely to inक्रमm the user of a reference leak.
	 */
	पूर्णांक insn_idx;
पूर्ण;

/* state of the program:
 * type of all रेजिस्टरs and stack info
 */
काष्ठा bpf_func_state अणु
	काष्ठा bpf_reg_state regs[MAX_BPF_REG];
	/* index of call inकाष्ठाion that called पूर्णांकo this func */
	पूर्णांक callsite;
	/* stack frame number of this function state from pov of
	 * enclosing bpf_verअगरier_state.
	 * 0 = मुख्य function, 1 = first callee.
	 */
	u32 frameno;
	/* subprog number == index within subprog_info
	 * zero == मुख्य subprog
	 */
	u32 subprogno;

	/* The following fields should be last. See copy_func_state() */
	पूर्णांक acquired_refs;
	काष्ठा bpf_reference_state *refs;
	पूर्णांक allocated_stack;
	bool in_callback_fn;
	काष्ठा bpf_stack_state *stack;
पूर्ण;

काष्ठा bpf_idx_pair अणु
	u32 prev_idx;
	u32 idx;
पूर्ण;

#घोषणा MAX_CALL_FRAMES 8
काष्ठा bpf_verअगरier_state अणु
	/* call stack tracking */
	काष्ठा bpf_func_state *frame[MAX_CALL_FRAMES];
	काष्ठा bpf_verअगरier_state *parent;
	/*
	 * 'branches' field is the number of branches left to explore:
	 * 0 - all possible paths from this state reached bpf_निकास or
	 * were safely pruned
	 * 1 - at least one path is being explored.
	 * This state hasn't reached bpf_निकास
	 * 2 - at least two paths are being explored.
	 * This state is an immediate parent of two children.
	 * One is fallthrough branch with branches==1 and another
	 * state is pushed पूर्णांकo stack (to be explored later) also with
	 * branches==1. The parent of this state has branches==1.
	 * The verअगरier state tree connected via 'parent' poपूर्णांकer looks like:
	 * 1
	 * 1
	 * 2 -> 1 (first 'if' pushed पूर्णांकo stack)
	 * 1
	 * 2 -> 1 (second 'if' pushed पूर्णांकo stack)
	 * 1
	 * 1
	 * 1 bpf_निकास.
	 *
	 * Once करो_check() reaches bpf_निकास, it calls update_branch_counts()
	 * and the verअगरier state tree will look:
	 * 1
	 * 1
	 * 2 -> 1 (first 'if' pushed पूर्णांकo stack)
	 * 1
	 * 1 -> 1 (second 'if' pushed पूर्णांकo stack)
	 * 0
	 * 0
	 * 0 bpf_निकास.
	 * After pop_stack() the करो_check() will resume at second 'if'.
	 *
	 * If is_state_visited() sees a state with branches > 0 it means
	 * there is a loop. If such state is exactly equal to the current state
	 * it's an infinite loop. Note states_equal() checks क्रम states
	 * equvalency, so two states being 'states_equal' करोes not mean
	 * infinite loop. The exact comparison is provided by
	 * states_maybe_looping() function. It's a stronger pre-check and
	 * much faster than states_equal().
	 *
	 * This algorithm may not find all possible infinite loops or
	 * loop iteration count may be too high.
	 * In such हालs BPF_COMPLEXITY_LIMIT_INSNS limit kicks in.
	 */
	u32 branches;
	u32 insn_idx;
	u32 curframe;
	u32 active_spin_lock;
	bool speculative;

	/* first and last insn idx of this verअगरier state */
	u32 first_insn_idx;
	u32 last_insn_idx;
	/* jmp history recorded from first to last.
	 * backtracking is using it to go from last to first.
	 * For most states jmp_history_cnt is [0-3].
	 * For loops can go up to ~40.
	 */
	काष्ठा bpf_idx_pair *jmp_history;
	u32 jmp_history_cnt;
पूर्ण;

#घोषणा bpf_get_spilled_reg(slot, frame)				\
	(((slot < frame->allocated_stack / BPF_REG_SIZE) &&		\
	  (frame->stack[slot].slot_type[0] == STACK_SPILL))		\
	 ? &frame->stack[slot].spilled_ptr : शून्य)

/* Iterate over 'frame', setting 'reg' to either शून्य or a spilled रेजिस्टर. */
#घोषणा bpf_क्रम_each_spilled_reg(iter, frame, reg)			\
	क्रम (iter = 0, reg = bpf_get_spilled_reg(iter, frame);		\
	     iter < frame->allocated_stack / BPF_REG_SIZE;		\
	     iter++, reg = bpf_get_spilled_reg(iter, frame))

/* linked list of verअगरier states used to prune search */
काष्ठा bpf_verअगरier_state_list अणु
	काष्ठा bpf_verअगरier_state state;
	काष्ठा bpf_verअगरier_state_list *next;
	पूर्णांक miss_cnt, hit_cnt;
पूर्ण;

/* Possible states क्रम alu_state member. */
#घोषणा BPF_ALU_SANITIZE_SRC		(1U << 0)
#घोषणा BPF_ALU_SANITIZE_DST		(1U << 1)
#घोषणा BPF_ALU_NEG_VALUE		(1U << 2)
#घोषणा BPF_ALU_NON_POINTER		(1U << 3)
#घोषणा BPF_ALU_IMMEDIATE		(1U << 4)
#घोषणा BPF_ALU_SANITIZE		(BPF_ALU_SANITIZE_SRC | \
					 BPF_ALU_SANITIZE_DST)

काष्ठा bpf_insn_aux_data अणु
	जोड़ अणु
		क्रमागत bpf_reg_type ptr_type;	/* poपूर्णांकer type क्रम load/store insns */
		अचिन्हित दीर्घ map_ptr_state;	/* poपूर्णांकer/poison value क्रम maps */
		s32 call_imm;			/* saved imm field of call insn */
		u32 alu_limit;			/* limit क्रम add/sub रेजिस्टर with poपूर्णांकer */
		काष्ठा अणु
			u32 map_index;		/* index पूर्णांकo used_maps[] */
			u32 map_off;		/* offset from value base address */
		पूर्ण;
		काष्ठा अणु
			क्रमागत bpf_reg_type reg_type;	/* type of pseuकरो_btf_id */
			जोड़ अणु
				काष्ठा अणु
					काष्ठा btf *btf;
					u32 btf_id;	/* btf_id क्रम काष्ठा typed var */
				पूर्ण;
				u32 mem_size;	/* mem_size क्रम non-काष्ठा typed var */
			पूर्ण;
		पूर्ण btf_var;
	पूर्ण;
	u64 map_key_state; /* स्थिरant (32 bit) key tracking क्रम maps */
	पूर्णांक ctx_field_size; /* the ctx field size क्रम load insn, maybe 0 */
	पूर्णांक sanitize_stack_off; /* stack slot to be cleared */
	u32 seen; /* this insn was processed by the verअगरier at env->pass_cnt */
	bool zext_dst; /* this insn zero extends dst reg */
	u8 alu_state; /* used in combination with alu_limit */

	/* below fields are initialized once */
	अचिन्हित पूर्णांक orig_idx; /* original inकाष्ठाion index */
	bool prune_poपूर्णांक;
पूर्ण;

#घोषणा MAX_USED_MAPS 64 /* max number of maps accessed by one eBPF program */
#घोषणा MAX_USED_BTFS 64 /* max number of BTFs accessed by one BPF program */

#घोषणा BPF_VERIFIER_TMP_LOG_SIZE	1024

काष्ठा bpf_verअगरier_log अणु
	u32 level;
	अक्षर kbuf[BPF_VERIFIER_TMP_LOG_SIZE];
	अक्षर __user *ubuf;
	u32 len_used;
	u32 len_total;
पूर्ण;

अटल अंतरभूत bool bpf_verअगरier_log_full(स्थिर काष्ठा bpf_verअगरier_log *log)
अणु
	वापस log->len_used >= log->len_total - 1;
पूर्ण

#घोषणा BPF_LOG_LEVEL1	1
#घोषणा BPF_LOG_LEVEL2	2
#घोषणा BPF_LOG_STATS	4
#घोषणा BPF_LOG_LEVEL	(BPF_LOG_LEVEL1 | BPF_LOG_LEVEL2)
#घोषणा BPF_LOG_MASK	(BPF_LOG_LEVEL | BPF_LOG_STATS)
#घोषणा BPF_LOG_KERNEL	(BPF_LOG_MASK + 1) /* kernel पूर्णांकernal flag */

अटल अंतरभूत bool bpf_verअगरier_log_needed(स्थिर काष्ठा bpf_verअगरier_log *log)
अणु
	वापस log &&
		((log->level && log->ubuf && !bpf_verअगरier_log_full(log)) ||
		 log->level == BPF_LOG_KERNEL);
पूर्ण

#घोषणा BPF_MAX_SUBPROGS 256

काष्ठा bpf_subprog_info अणु
	/* 'start' has to be the first field otherwise find_subprog() won't work */
	u32 start; /* insn idx of function entry poपूर्णांक */
	u32 linfo_idx; /* The idx to the मुख्य_prog->aux->linfo */
	u16 stack_depth; /* max. stack depth used by this function */
	bool has_tail_call;
	bool tail_call_reachable;
	bool has_ld_असल;
पूर्ण;

/* single container क्रम all काष्ठाs
 * one verअगरier_env per bpf_check() call
 */
काष्ठा bpf_verअगरier_env अणु
	u32 insn_idx;
	u32 prev_insn_idx;
	काष्ठा bpf_prog *prog;		/* eBPF program being verअगरied */
	स्थिर काष्ठा bpf_verअगरier_ops *ops;
	काष्ठा bpf_verअगरier_stack_elem *head; /* stack of verअगरier states to be processed */
	पूर्णांक stack_size;			/* number of states to be processed */
	bool strict_alignment;		/* perक्रमm strict poपूर्णांकer alignment checks */
	bool test_state_freq;		/* test verअगरier with dअगरferent pruning frequency */
	काष्ठा bpf_verअगरier_state *cur_state; /* current verअगरier state */
	काष्ठा bpf_verअगरier_state_list **explored_states; /* search pruning optimization */
	काष्ठा bpf_verअगरier_state_list *मुक्त_list;
	काष्ठा bpf_map *used_maps[MAX_USED_MAPS]; /* array of map's used by eBPF program */
	काष्ठा btf_mod_pair used_btfs[MAX_USED_BTFS]; /* array of BTF's used by BPF program */
	u32 used_map_cnt;		/* number of used maps */
	u32 used_btf_cnt;		/* number of used BTF objects */
	u32 id_gen;			/* used to generate unique reg IDs */
	bool allow_ptr_leaks;
	bool allow_uninit_stack;
	bool allow_ptr_to_map_access;
	bool bpf_capable;
	bool bypass_spec_v1;
	bool bypass_spec_v4;
	bool seen_direct_ग_लिखो;
	काष्ठा bpf_insn_aux_data *insn_aux_data; /* array of per-insn state */
	स्थिर काष्ठा bpf_line_info *prev_linfo;
	काष्ठा bpf_verअगरier_log log;
	काष्ठा bpf_subprog_info subprog_info[BPF_MAX_SUBPROGS + 1];
	काष्ठा अणु
		पूर्णांक *insn_state;
		पूर्णांक *insn_stack;
		पूर्णांक cur_stack;
	पूर्ण cfg;
	u32 pass_cnt; /* number of बार करो_check() was called */
	u32 subprog_cnt;
	/* number of inकाष्ठाions analyzed by the verअगरier */
	u32 prev_insn_processed, insn_processed;
	/* number of jmps, calls, निकासs analyzed so far */
	u32 prev_jmps_processed, jmps_processed;
	/* total verअगरication समय */
	u64 verअगरication_समय;
	/* maximum number of verअगरier states kept in 'branching' inकाष्ठाions */
	u32 max_states_per_insn;
	/* total number of allocated verअगरier states */
	u32 total_states;
	/* some states are मुक्तd during program analysis.
	 * this is peak number of states. this number करोminates kernel
	 * memory consumption during verअगरication
	 */
	u32 peak_states;
	/* दीर्घest रेजिस्टर parentage chain walked क्रम liveness marking */
	u32 दीर्घest_mark_पढ़ो_walk;
पूर्ण;

__म_लिखो(2, 0) व्योम bpf_verअगरier_vlog(काष्ठा bpf_verअगरier_log *log,
				      स्थिर अक्षर *fmt, बहु_सूची args);
__म_लिखो(2, 3) व्योम bpf_verअगरier_log_ग_लिखो(काष्ठा bpf_verअगरier_env *env,
					   स्थिर अक्षर *fmt, ...);
__म_लिखो(2, 3) व्योम bpf_log(काष्ठा bpf_verअगरier_log *log,
			    स्थिर अक्षर *fmt, ...);

अटल अंतरभूत काष्ठा bpf_func_state *cur_func(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_verअगरier_state *cur = env->cur_state;

	वापस cur->frame[cur->curframe];
पूर्ण

अटल अंतरभूत काष्ठा bpf_reg_state *cur_regs(काष्ठा bpf_verअगरier_env *env)
अणु
	वापस cur_func(env)->regs;
पूर्ण

पूर्णांक bpf_prog_offload_verअगरier_prep(काष्ठा bpf_prog *prog);
पूर्णांक bpf_prog_offload_verअगरy_insn(काष्ठा bpf_verअगरier_env *env,
				 पूर्णांक insn_idx, पूर्णांक prev_insn_idx);
पूर्णांक bpf_prog_offload_finalize(काष्ठा bpf_verअगरier_env *env);
व्योम
bpf_prog_offload_replace_insn(काष्ठा bpf_verअगरier_env *env, u32 off,
			      काष्ठा bpf_insn *insn);
व्योम
bpf_prog_offload_हटाओ_insns(काष्ठा bpf_verअगरier_env *env, u32 off, u32 cnt);

पूर्णांक check_ctx_reg(काष्ठा bpf_verअगरier_env *env,
		  स्थिर काष्ठा bpf_reg_state *reg, पूर्णांक regno);
पूर्णांक check_mem_reg(काष्ठा bpf_verअगरier_env *env, काष्ठा bpf_reg_state *reg,
		   u32 regno, u32 mem_size);

/* this lives here instead of in bpf.h because it needs to dereference tgt_prog */
अटल अंतरभूत u64 bpf_trampoline_compute_key(स्थिर काष्ठा bpf_prog *tgt_prog,
					     काष्ठा btf *btf, u32 btf_id)
अणु
	अगर (tgt_prog)
		वापस ((u64)tgt_prog->aux->id << 32) | btf_id;
	अन्यथा
		वापस ((u64)btf_obj_id(btf) << 32) | 0x80000000 | btf_id;
पूर्ण

/* unpack the IDs from the key as स्थिरructed above */
अटल अंतरभूत व्योम bpf_trampoline_unpack_key(u64 key, u32 *obj_id, u32 *btf_id)
अणु
	अगर (obj_id)
		*obj_id = key >> 32;
	अगर (btf_id)
		*btf_id = key & 0x7FFFFFFF;
पूर्ण

पूर्णांक bpf_check_attach_target(काष्ठा bpf_verअगरier_log *log,
			    स्थिर काष्ठा bpf_prog *prog,
			    स्थिर काष्ठा bpf_prog *tgt_prog,
			    u32 btf_id,
			    काष्ठा bpf_attach_target_info *tgt_info);

#पूर्ण_अगर /* _LINUX_BPF_VERIFIER_H */
