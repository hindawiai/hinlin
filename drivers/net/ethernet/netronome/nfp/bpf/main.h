<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause) */
/* Copyright (C) 2016-2018 Netronome Systems, Inc. */

#अगर_अघोषित __NFP_BPF_H__
#घोषणा __NFP_BPF_H__ 1

#समावेश <linux/bitfield.h>
#समावेश <linux/bpf.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/rhashtable.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/types.h>
#समावेश <linux/रुको.h>

#समावेश "../ccm.h"
#समावेश "../nfp_asm.h"
#समावेश "fw.h"

#घोषणा cmsg_warn(bpf, msg...)	nn_dp_warn(&(bpf)->app->ctrl->dp, msg)

/* For relocation logic use up-most byte of branch inकाष्ठाion as scratch
 * area.  Remember to clear this beक्रमe sending inकाष्ठाions to HW!
 */
#घोषणा OP_RELO_TYPE	0xff00000000000000ULL

क्रमागत nfp_relo_type अणु
	RELO_NONE = 0,
	/* standard पूर्णांकernal jumps */
	RELO_BR_REL,
	/* पूर्णांकernal jumps to parts of the outro */
	RELO_BR_GO_OUT,
	RELO_BR_GO_ABORT,
	RELO_BR_GO_CALL_PUSH_REGS,
	RELO_BR_GO_CALL_POP_REGS,
	/* बाह्यal jumps to fixed addresses */
	RELO_BR_NEXT_PKT,
	RELO_BR_HELPER,
	/* immediate relocation against load address */
	RELO_IMMED_REL,
पूर्ण;

/* To make असलolute relocated branches (branches other than RELO_BR_REL)
 * distinguishable in user space dumps from normal jumps, add a large offset
 * to them.
 */
#घोषणा BR_OFF_RELO		15000

क्रमागत अटल_regs अणु
	STATIC_REG_IMMA		= 20, /* Bank AB */
	STATIC_REG_IMM		= 21, /* Bank AB */
	STATIC_REG_STACK	= 22, /* Bank A */
	STATIC_REG_PKT_LEN	= 22, /* Bank B */
पूर्ण;

क्रमागत pkt_vec अणु
	PKT_VEC_PKT_LEN		= 0,
	PKT_VEC_PKT_PTR		= 2,
	PKT_VEC_QSEL_SET	= 4,
	PKT_VEC_QSEL_VAL	= 6,
पूर्ण;

#घोषणा PKT_VEL_QSEL_SET_BIT	4

#घोषणा pv_len(np)	reg_lm(1, PKT_VEC_PKT_LEN)
#घोषणा pv_cपंचांग_ptr(np)	reg_lm(1, PKT_VEC_PKT_PTR)
#घोषणा pv_qsel_set(np)	reg_lm(1, PKT_VEC_QSEL_SET)
#घोषणा pv_qsel_val(np)	reg_lm(1, PKT_VEC_QSEL_VAL)

#घोषणा stack_reg(np)	reg_a(STATIC_REG_STACK)
#घोषणा stack_imm(np)	imm_b(np)
#घोषणा plen_reg(np)	reg_b(STATIC_REG_PKT_LEN)
#घोषणा pptr_reg(np)	pv_cपंचांग_ptr(np)
#घोषणा imm_a(np)	reg_a(STATIC_REG_IMM)
#घोषणा imm_b(np)	reg_b(STATIC_REG_IMM)
#घोषणा imma_a(np)	reg_a(STATIC_REG_IMMA)
#घोषणा imma_b(np)	reg_b(STATIC_REG_IMMA)
#घोषणा imm_both(np)	reg_both(STATIC_REG_IMM)
#घोषणा ret_reg(np)	imm_a(np)

#घोषणा NFP_BPF_ABI_FLAGS	reg_imm(0)
#घोषणा   NFP_BPF_ABI_FLAG_MARK	1

/**
 * काष्ठा nfp_app_bpf - bpf app priv काष्ठाure
 * @app:		backpoपूर्णांकer to the app
 * @ccm:		common control message handler data
 *
 * @bpf_dev:		BPF offload device handle
 *
 * @cmsg_key_sz:	size of key in cmsg element array
 * @cmsg_val_sz:	size of value in cmsg element array
 *
 * @map_list:		list of offloaded maps
 * @maps_in_use:	number of currently offloaded maps
 * @map_elems_in_use:	number of elements allocated to offloaded maps
 *
 * @maps_neutral:	hash table of offload-neutral maps (on poपूर्णांकer)
 *
 * @abi_version:	global BPF ABI version
 * @cmsg_cache_cnt:	number of entries to पढ़ो क्रम caching
 *
 * @adjust_head:	adjust head capability
 * @adjust_head.flags:		extra flags क्रम adjust head
 * @adjust_head.off_min:	minimal packet offset within buffer required
 * @adjust_head.off_max:	maximum packet offset within buffer required
 * @adjust_head.guaranteed_sub:	negative adjusपंचांगent guaranteed possible
 * @adjust_head.guaranteed_add:	positive adjusपंचांगent guaranteed possible
 *
 * @maps:		map capability
 * @maps.types:			supported map types
 * @maps.max_maps:		max number of maps supported
 * @maps.max_elems:		max number of entries in each map
 * @maps.max_key_sz:		max size of map key
 * @maps.max_val_sz:		max size of map value
 * @maps.max_elem_sz:		max size of map entry (key + value)
 *
 * @helpers:		helper addressess क्रम various calls
 * @helpers.map_lookup:		map lookup helper address
 * @helpers.map_update:		map update helper address
 * @helpers.map_delete:		map delete helper address
 * @helpers.perf_event_output:	output perf event to a ring buffer
 *
 * @pseuकरो_अक्रमom:	FW initialized the pseuकरो-अक्रमom machinery (CSRs)
 * @queue_select:	BPF can set the RX queue ID in packet vector
 * @adjust_tail:	BPF can simply trunc packet size क्रम adjust tail
 * @cmsg_multi_ent:	FW can pack multiple map entries in a single cmsg
 */
काष्ठा nfp_app_bpf अणु
	काष्ठा nfp_app *app;
	काष्ठा nfp_ccm ccm;

	काष्ठा bpf_offload_dev *bpf_dev;

	अचिन्हित पूर्णांक cmsg_key_sz;
	अचिन्हित पूर्णांक cmsg_val_sz;

	अचिन्हित पूर्णांक cmsg_cache_cnt;

	काष्ठा list_head map_list;
	अचिन्हित पूर्णांक maps_in_use;
	अचिन्हित पूर्णांक map_elems_in_use;

	काष्ठा rhashtable maps_neutral;

	u32 abi_version;

	काष्ठा nfp_bpf_cap_adjust_head अणु
		u32 flags;
		पूर्णांक off_min;
		पूर्णांक off_max;
		पूर्णांक guaranteed_sub;
		पूर्णांक guaranteed_add;
	पूर्ण adjust_head;

	काष्ठा अणु
		u32 types;
		u32 max_maps;
		u32 max_elems;
		u32 max_key_sz;
		u32 max_val_sz;
		u32 max_elem_sz;
	पूर्ण maps;

	काष्ठा अणु
		u32 map_lookup;
		u32 map_update;
		u32 map_delete;
		u32 perf_event_output;
	पूर्ण helpers;

	bool pseuकरो_अक्रमom;
	bool queue_select;
	bool adjust_tail;
	bool cmsg_multi_ent;
पूर्ण;

क्रमागत nfp_bpf_map_use अणु
	NFP_MAP_UNUSED = 0,
	NFP_MAP_USE_READ,
	NFP_MAP_USE_WRITE,
	NFP_MAP_USE_ATOMIC_CNT,
पूर्ण;

काष्ठा nfp_bpf_map_word अणु
	अचिन्हित अक्षर type		:4;
	अचिन्हित अक्षर non_zero_update	:1;
पूर्ण;

#घोषणा NFP_BPF_MAP_CACHE_CNT		4U
#घोषणा NFP_BPF_MAP_CACHE_TIME_NS	(250 * 1000)

/**
 * काष्ठा nfp_bpf_map - निजी per-map data attached to BPF maps क्रम offload
 * @offmap:	poपूर्णांकer to the offloaded BPF map
 * @bpf:	back poपूर्णांकer to bpf app निजी काष्ठाure
 * @tid:	table id identअगरying map on datapath
 *
 * @cache_lock:	protects @cache_blockers, @cache_to, @cache
 * @cache_blockers:	number of ops in flight which block caching
 * @cache_gen:	counter incremented by every blocker on निकास
 * @cache_to:	समय when cache will no दीर्घer be valid (ns)
 * @cache:	skb with cached response
 *
 * @l:		link on the nfp_app_bpf->map_list list
 * @use_map:	map of how the value is used (in 4B chunks)
 */
काष्ठा nfp_bpf_map अणु
	काष्ठा bpf_offloaded_map *offmap;
	काष्ठा nfp_app_bpf *bpf;
	u32 tid;

	spinlock_t cache_lock;
	u32 cache_blockers;
	u32 cache_gen;
	u64 cache_to;
	काष्ठा sk_buff *cache;

	काष्ठा list_head l;
	काष्ठा nfp_bpf_map_word use_map[];
पूर्ण;

काष्ठा nfp_bpf_neutral_map अणु
	काष्ठा rhash_head l;
	काष्ठा bpf_map *ptr;
	u32 map_id;
	u32 count;
पूर्ण;

बाह्य स्थिर काष्ठा rhashtable_params nfp_bpf_maps_neutral_params;

काष्ठा nfp_prog;
काष्ठा nfp_insn_meta;
प्रकार पूर्णांक (*instr_cb_t)(काष्ठा nfp_prog *, काष्ठा nfp_insn_meta *);

#घोषणा nfp_prog_first_meta(nfp_prog)					\
	list_first_entry(&(nfp_prog)->insns, काष्ठा nfp_insn_meta, l)
#घोषणा nfp_prog_last_meta(nfp_prog)					\
	list_last_entry(&(nfp_prog)->insns, काष्ठा nfp_insn_meta, l)
#घोषणा nfp_meta_next(meta)	list_next_entry(meta, l)
#घोषणा nfp_meta_prev(meta)	list_prev_entry(meta, l)

/**
 * काष्ठा nfp_bpf_reg_state - रेजिस्टर state क्रम calls
 * @reg: BPF रेजिस्टर state from latest path
 * @var_off: क्रम stack arg - changes stack offset on dअगरferent paths
 */
काष्ठा nfp_bpf_reg_state अणु
	काष्ठा bpf_reg_state reg;
	bool var_off;
पूर्ण;

#घोषणा FLAG_INSN_IS_JUMP_DST			BIT(0)
#घोषणा FLAG_INSN_IS_SUBPROG_START		BIT(1)
#घोषणा FLAG_INSN_PTR_CALLER_STACK_FRAME	BIT(2)
/* Inकाष्ठाion is poपूर्णांकless, noop even on its own */
#घोषणा FLAG_INSN_SKIP_NOOP			BIT(3)
/* Inकाष्ठाion is optimized out based on preceding inकाष्ठाions */
#घोषणा FLAG_INSN_SKIP_PREC_DEPENDENT		BIT(4)
/* Inकाष्ठाion is optimized by the verअगरier */
#घोषणा FLAG_INSN_SKIP_VERIFIER_OPT		BIT(5)
/* Inकाष्ठाion needs to zero extend to high 32-bit */
#घोषणा FLAG_INSN_DO_ZEXT			BIT(6)

#घोषणा FLAG_INSN_SKIP_MASK		(FLAG_INSN_SKIP_NOOP | \
					 FLAG_INSN_SKIP_PREC_DEPENDENT | \
					 FLAG_INSN_SKIP_VERIFIER_OPT)

/**
 * काष्ठा nfp_insn_meta - BPF inकाष्ठाion wrapper
 * @insn: BPF inकाष्ठाion
 * @ptr: poपूर्णांकer type क्रम memory operations
 * @ldst_gather_len: स_नकल length gathered from load/store sequence
 * @paired_st: the paired store insn at the head of the sequence
 * @ptr_not_स्थिर: poपूर्णांकer is not always स्थिरant
 * @pkt_cache: packet data cache inक्रमmation
 * @pkt_cache.range_start: start offset क्रम associated packet data cache
 * @pkt_cache.range_end: end offset क्रम associated packet data cache
 * @pkt_cache.करो_init: this पढ़ो needs to initialize packet data cache
 * @xadd_over_16bit: 16bit immediate is not guaranteed
 * @xadd_maybe_16bit: 16bit immediate is possible
 * @jmp_dst: destination info क्रम jump inकाष्ठाions
 * @jump_neg_op: jump inकाष्ठाion has inverted immediate, use ADD instead of SUB
 * @num_insns_after_br: number of insns following a branch jump, used क्रम fixup
 * @func_id: function id क्रम call inकाष्ठाions
 * @arg1: arg1 क्रम call inकाष्ठाions
 * @arg2: arg2 क्रम call inकाष्ठाions
 * @umin_src: copy of core verअगरier umin_value क्रम src opearnd.
 * @umax_src: copy of core verअगरier umax_value क्रम src opeअक्रम.
 * @umin_dst: copy of core verअगरier umin_value क्रम dst opearnd.
 * @umax_dst: copy of core verअगरier umax_value क्रम dst opeअक्रम.
 * @off: index of first generated machine inकाष्ठाion (in nfp_prog.prog)
 * @n: eBPF inकाष्ठाion number
 * @flags: eBPF inकाष्ठाion extra optimization flags
 * @subprog_idx: index of subprogram to which the inकाष्ठाion beदीर्घs
 * @द्विगुन_cb: callback क्रम second part of the inकाष्ठाion
 * @l: link on nfp_prog->insns list
 */
काष्ठा nfp_insn_meta अणु
	काष्ठा bpf_insn insn;
	जोड़ अणु
		/* poपूर्णांकer ops (ld/st/xadd) */
		काष्ठा अणु
			काष्ठा bpf_reg_state ptr;
			काष्ठा bpf_insn *paired_st;
			s16 ldst_gather_len;
			bool ptr_not_स्थिर;
			काष्ठा अणु
				s16 range_start;
				s16 range_end;
				bool करो_init;
			पूर्ण pkt_cache;
			bool xadd_over_16bit;
			bool xadd_maybe_16bit;
		पूर्ण;
		/* jump */
		काष्ठा अणु
			काष्ठा nfp_insn_meta *jmp_dst;
			bool jump_neg_op;
			u32 num_insns_after_br; /* only क्रम BPF-to-BPF calls */
		पूर्ण;
		/* function calls */
		काष्ठा अणु
			u32 func_id;
			काष्ठा bpf_reg_state arg1;
			काष्ठा nfp_bpf_reg_state arg2;
		पूर्ण;
		/* We are पूर्णांकerested in range info क्रम opeअक्रमs of ALU
		 * operations. For example, shअगरt amount, multiplicand and
		 * multiplier etc.
		 */
		काष्ठा अणु
			u64 umin_src;
			u64 umax_src;
			u64 umin_dst;
			u64 umax_dst;
		पूर्ण;
	पूर्ण;
	अचिन्हित पूर्णांक off;
	अचिन्हित लघु n;
	अचिन्हित लघु flags;
	अचिन्हित लघु subprog_idx;
	instr_cb_t द्विगुन_cb;

	काष्ठा list_head l;
पूर्ण;

#घोषणा BPF_SIZE_MASK	0x18

अटल अंतरभूत u8 mbpf_class(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस BPF_CLASS(meta->insn.code);
पूर्ण

अटल अंतरभूत u8 mbpf_src(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस BPF_SRC(meta->insn.code);
पूर्ण

अटल अंतरभूत u8 mbpf_op(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस BPF_OP(meta->insn.code);
पूर्ण

अटल अंतरभूत u8 mbpf_mode(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस BPF_MODE(meta->insn.code);
पूर्ण

अटल अंतरभूत bool is_mbpf_alu(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस mbpf_class(meta) == BPF_ALU64 || mbpf_class(meta) == BPF_ALU;
पूर्ण

अटल अंतरभूत bool is_mbpf_load(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस (meta->insn.code & ~BPF_SIZE_MASK) == (BPF_LDX | BPF_MEM);
पूर्ण

अटल अंतरभूत bool is_mbpf_jmp32(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस mbpf_class(meta) == BPF_JMP32;
पूर्ण

अटल अंतरभूत bool is_mbpf_jmp64(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस mbpf_class(meta) == BPF_JMP;
पूर्ण

अटल अंतरभूत bool is_mbpf_jmp(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस is_mbpf_jmp32(meta) || is_mbpf_jmp64(meta);
पूर्ण

अटल अंतरभूत bool is_mbpf_store(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस (meta->insn.code & ~BPF_SIZE_MASK) == (BPF_STX | BPF_MEM);
पूर्ण

अटल अंतरभूत bool is_mbpf_load_pkt(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस is_mbpf_load(meta) && meta->ptr.type == PTR_TO_PACKET;
पूर्ण

अटल अंतरभूत bool is_mbpf_store_pkt(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस is_mbpf_store(meta) && meta->ptr.type == PTR_TO_PACKET;
पूर्ण

अटल अंतरभूत bool is_mbpf_classic_load(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	u8 code = meta->insn.code;

	वापस BPF_CLASS(code) == BPF_LD &&
	       (BPF_MODE(code) == BPF_ABS || BPF_MODE(code) == BPF_IND);
पूर्ण

अटल अंतरभूत bool is_mbpf_classic_store(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	u8 code = meta->insn.code;

	वापस BPF_CLASS(code) == BPF_ST && BPF_MODE(code) == BPF_MEM;
पूर्ण

अटल अंतरभूत bool is_mbpf_classic_store_pkt(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस is_mbpf_classic_store(meta) && meta->ptr.type == PTR_TO_PACKET;
पूर्ण

अटल अंतरभूत bool is_mbpf_atomic(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस (meta->insn.code & ~BPF_SIZE_MASK) == (BPF_STX | BPF_ATOMIC);
पूर्ण

अटल अंतरभूत bool is_mbpf_mul(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस is_mbpf_alu(meta) && mbpf_op(meta) == BPF_MUL;
पूर्ण

अटल अंतरभूत bool is_mbpf_भाग(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	वापस is_mbpf_alu(meta) && mbpf_op(meta) == BPF_DIV;
पूर्ण

अटल अंतरभूत bool is_mbpf_cond_jump(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	u8 op;

	अगर (is_mbpf_jmp32(meta))
		वापस true;

	अगर (!is_mbpf_jmp64(meta))
		वापस false;

	op = mbpf_op(meta);
	वापस op != BPF_JA && op != BPF_EXIT && op != BPF_CALL;
पूर्ण

अटल अंतरभूत bool is_mbpf_helper_call(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	काष्ठा bpf_insn insn = meta->insn;

	वापस insn.code == (BPF_JMP | BPF_CALL) &&
		insn.src_reg != BPF_PSEUDO_CALL;
पूर्ण

अटल अंतरभूत bool is_mbpf_pseuकरो_call(स्थिर काष्ठा nfp_insn_meta *meta)
अणु
	काष्ठा bpf_insn insn = meta->insn;

	वापस insn.code == (BPF_JMP | BPF_CALL) &&
		insn.src_reg == BPF_PSEUDO_CALL;
पूर्ण

#घोषणा STACK_FRAME_ALIGN 64

/**
 * काष्ठा nfp_bpf_subprog_info - nfp BPF sub-program (a.k.a. function) info
 * @stack_depth:	maximum stack depth used by this sub-program
 * @needs_reg_push:	whether sub-program uses callee-saved रेजिस्टरs
 */
काष्ठा nfp_bpf_subprog_info अणु
	u16 stack_depth;
	u8 needs_reg_push : 1;
पूर्ण;

/**
 * काष्ठा nfp_prog - nfp BPF program
 * @bpf: backpoपूर्णांकer to the bpf app priv काष्ठाure
 * @prog: machine code
 * @prog_len: number of valid inकाष्ठाions in @prog array
 * @__prog_alloc_len: alloc size of @prog array
 * @stack_size: total amount of stack used
 * @verअगरier_meta: temporary storage क्रम verअगरier's insn meta
 * @type: BPF program type
 * @last_bpf_off: address of the last inकाष्ठाion translated from BPF
 * @tgt_out: jump target क्रम normal निकास
 * @tgt_पात: jump target क्रम पात (e.g. access outside of packet buffer)
 * @tgt_call_push_regs: jump target क्रम subroutine क्रम saving R6~R9 to stack
 * @tgt_call_pop_regs: jump target क्रम subroutine used क्रम restoring R6~R9
 * @n_translated: number of successfully translated inकाष्ठाions (क्रम errors)
 * @error: error code अगर something went wrong
 * @stack_frame_depth: max stack depth क्रम current frame
 * @adjust_head_location: अगर program has single adjust head call - the insn no.
 * @map_records_cnt: the number of map poपूर्णांकers recorded क्रम this prog
 * @subprog_cnt: number of sub-programs, including मुख्य function
 * @map_records: the map record poपूर्णांकers from bpf->maps_neutral
 * @subprog: poपूर्णांकer to an array of objects holding info about sub-programs
 * @n_insns: number of inकाष्ठाions on @insns list
 * @insns: list of BPF inकाष्ठाion wrappers (काष्ठा nfp_insn_meta)
 */
काष्ठा nfp_prog अणु
	काष्ठा nfp_app_bpf *bpf;

	u64 *prog;
	अचिन्हित पूर्णांक prog_len;
	अचिन्हित पूर्णांक __prog_alloc_len;

	अचिन्हित पूर्णांक stack_size;

	काष्ठा nfp_insn_meta *verअगरier_meta;

	क्रमागत bpf_prog_type type;

	अचिन्हित पूर्णांक last_bpf_off;
	अचिन्हित पूर्णांक tgt_out;
	अचिन्हित पूर्णांक tgt_पात;
	अचिन्हित पूर्णांक tgt_call_push_regs;
	अचिन्हित पूर्णांक tgt_call_pop_regs;

	अचिन्हित पूर्णांक n_translated;
	पूर्णांक error;

	अचिन्हित पूर्णांक stack_frame_depth;
	अचिन्हित पूर्णांक adjust_head_location;

	अचिन्हित पूर्णांक map_records_cnt;
	अचिन्हित पूर्णांक subprog_cnt;
	काष्ठा nfp_bpf_neutral_map **map_records;
	काष्ठा nfp_bpf_subprog_info *subprog;

	अचिन्हित पूर्णांक n_insns;
	काष्ठा list_head insns;
पूर्ण;

/**
 * काष्ठा nfp_bpf_vnic - per-vNIC BPF priv काष्ठाure
 * @tc_prog:	currently loaded cls_bpf program
 * @start_off:	address of the first inकाष्ठाion in the memory
 * @tgt_करोne:	jump target to get the next packet
 */
काष्ठा nfp_bpf_vnic अणु
	काष्ठा bpf_prog *tc_prog;
	अचिन्हित पूर्णांक start_off;
	अचिन्हित पूर्णांक tgt_करोne;
पूर्ण;

bool nfp_is_subprog_start(काष्ठा nfp_insn_meta *meta);
व्योम nfp_bpf_jit_prepare(काष्ठा nfp_prog *nfp_prog);
पूर्णांक nfp_bpf_jit(काष्ठा nfp_prog *prog);
bool nfp_bpf_supported_opcode(u8 code);

पूर्णांक nfp_verअगरy_insn(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx,
		    पूर्णांक prev_insn_idx);
पूर्णांक nfp_bpf_finalize(काष्ठा bpf_verअगरier_env *env);

पूर्णांक nfp_bpf_opt_replace_insn(काष्ठा bpf_verअगरier_env *env, u32 off,
			     काष्ठा bpf_insn *insn);
पूर्णांक nfp_bpf_opt_हटाओ_insns(काष्ठा bpf_verअगरier_env *env, u32 off, u32 cnt);

बाह्य स्थिर काष्ठा bpf_prog_offload_ops nfp_bpf_dev_ops;

काष्ठा netdev_bpf;
काष्ठा nfp_app;
काष्ठा nfp_net;

पूर्णांक nfp_nकरो_bpf(काष्ठा nfp_app *app, काष्ठा nfp_net *nn,
		काष्ठा netdev_bpf *bpf);
पूर्णांक nfp_net_bpf_offload(काष्ठा nfp_net *nn, काष्ठा bpf_prog *prog,
			bool old_prog, काष्ठा netlink_ext_ack *extack);

काष्ठा nfp_insn_meta *
nfp_bpf_जाओ_meta(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		  अचिन्हित पूर्णांक insn_idx);

व्योम *nfp_bpf_relo_क्रम_vnic(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_bpf_vnic *bv);

अचिन्हित पूर्णांक nfp_bpf_ctrl_cmsg_min_mtu(काष्ठा nfp_app_bpf *bpf);
अचिन्हित पूर्णांक nfp_bpf_ctrl_cmsg_mtu(काष्ठा nfp_app_bpf *bpf);
अचिन्हित पूर्णांक nfp_bpf_ctrl_cmsg_cache_cnt(काष्ठा nfp_app_bpf *bpf);
दीर्घ दीर्घ पूर्णांक
nfp_bpf_ctrl_alloc_map(काष्ठा nfp_app_bpf *bpf, काष्ठा bpf_map *map);
व्योम
nfp_bpf_ctrl_मुक्त_map(काष्ठा nfp_app_bpf *bpf, काष्ठा nfp_bpf_map *nfp_map);
पूर्णांक nfp_bpf_ctrl_getfirst_entry(काष्ठा bpf_offloaded_map *offmap,
				व्योम *next_key);
पूर्णांक nfp_bpf_ctrl_update_entry(काष्ठा bpf_offloaded_map *offmap,
			      व्योम *key, व्योम *value, u64 flags);
पूर्णांक nfp_bpf_ctrl_del_entry(काष्ठा bpf_offloaded_map *offmap, व्योम *key);
पूर्णांक nfp_bpf_ctrl_lookup_entry(काष्ठा bpf_offloaded_map *offmap,
			      व्योम *key, व्योम *value);
पूर्णांक nfp_bpf_ctrl_getnext_entry(काष्ठा bpf_offloaded_map *offmap,
			       व्योम *key, व्योम *next_key);

पूर्णांक nfp_bpf_event_output(काष्ठा nfp_app_bpf *bpf, स्थिर व्योम *data,
			 अचिन्हित पूर्णांक len);

व्योम nfp_bpf_ctrl_msg_rx(काष्ठा nfp_app *app, काष्ठा sk_buff *skb);
व्योम
nfp_bpf_ctrl_msg_rx_raw(काष्ठा nfp_app *app, स्थिर व्योम *data,
			अचिन्हित पूर्णांक len);
#पूर्ण_अगर
