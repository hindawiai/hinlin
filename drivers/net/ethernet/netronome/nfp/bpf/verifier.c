<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-2-Clause)
/* Copyright (C) 2016-2018 Netronome Systems, Inc. */

#समावेश <linux/bpf.h>
#समावेश <linux/bpf_verअगरier.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/pkt_cls.h>

#समावेश "../nfp_app.h"
#समावेश "../nfp_main.h"
#समावेश "../nfp_net.h"
#समावेश "fw.h"
#समावेश "main.h"

#घोषणा pr_vlog(env, fmt, ...)	\
	bpf_verअगरier_log_ग_लिखो(env, "[nfp] " fmt, ##__VA_ARGS__)

काष्ठा nfp_insn_meta *
nfp_bpf_जाओ_meta(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		  अचिन्हित पूर्णांक insn_idx)
अणु
	अचिन्हित पूर्णांक क्रमward, backward, i;

	backward = meta->n - insn_idx;
	क्रमward = insn_idx - meta->n;

	अगर (min(क्रमward, backward) > nfp_prog->n_insns - insn_idx - 1) अणु
		backward = nfp_prog->n_insns - insn_idx - 1;
		meta = nfp_prog_last_meta(nfp_prog);
	पूर्ण
	अगर (min(क्रमward, backward) > insn_idx && backward > insn_idx) अणु
		क्रमward = insn_idx;
		meta = nfp_prog_first_meta(nfp_prog);
	पूर्ण

	अगर (क्रमward < backward)
		क्रम (i = 0; i < क्रमward; i++)
			meta = nfp_meta_next(meta);
	अन्यथा
		क्रम (i = 0; i < backward; i++)
			meta = nfp_meta_prev(meta);

	वापस meta;
पूर्ण

अटल व्योम
nfp_record_adjust_head(काष्ठा nfp_app_bpf *bpf, काष्ठा nfp_prog *nfp_prog,
		       काष्ठा nfp_insn_meta *meta,
		       स्थिर काष्ठा bpf_reg_state *reg2)
अणु
	अचिन्हित पूर्णांक location =	अच_पूर्णांक_उच्च;
	पूर्णांक imm;

	/* Datapath usually can give us guarantees on how much adjust head
	 * can be करोne without the need क्रम any checks.  Optimize the simple
	 * हाल where there is only one adjust head by a स्थिरant.
	 */
	अगर (reg2->type != SCALAR_VALUE || !tnum_is_स्थिर(reg2->var_off))
		जाओ निकास_set_location;
	imm = reg2->var_off.value;
	/* Translator will skip all checks, we need to guarantee min pkt len */
	अगर (imm > ETH_ZLEN - ETH_HLEN)
		जाओ निकास_set_location;
	अगर (imm > (पूर्णांक)bpf->adjust_head.guaranteed_add ||
	    imm < -bpf->adjust_head.guaranteed_sub)
		जाओ निकास_set_location;

	अगर (nfp_prog->adjust_head_location) अणु
		/* Only one call per program allowed */
		अगर (nfp_prog->adjust_head_location != meta->n)
			जाओ निकास_set_location;

		अगर (meta->arg2.reg.var_off.value != imm)
			जाओ निकास_set_location;
	पूर्ण

	location = meta->n;
निकास_set_location:
	nfp_prog->adjust_head_location = location;
पूर्ण

अटल bool nfp_bpf_map_update_value_ok(काष्ठा bpf_verअगरier_env *env)
अणु
	स्थिर काष्ठा bpf_reg_state *reg1 = cur_regs(env) + BPF_REG_1;
	स्थिर काष्ठा bpf_reg_state *reg3 = cur_regs(env) + BPF_REG_3;
	काष्ठा bpf_offloaded_map *offmap;
	काष्ठा bpf_func_state *state;
	काष्ठा nfp_bpf_map *nfp_map;
	पूर्णांक off, i;

	state = env->cur_state->frame[reg3->frameno];

	/* We need to record each समय update happens with non-zero words,
	 * in हाल such word is used in atomic operations.
	 * Implicitly depend on nfp_bpf_stack_arg_ok(reg3) being run beक्रमe.
	 */

	offmap = map_to_offmap(reg1->map_ptr);
	nfp_map = offmap->dev_priv;
	off = reg3->off + reg3->var_off.value;

	क्रम (i = 0; i < offmap->map.value_size; i++) अणु
		काष्ठा bpf_stack_state *stack_entry;
		अचिन्हित पूर्णांक soff;

		soff = -(off + i) - 1;
		stack_entry = &state->stack[soff / BPF_REG_SIZE];
		अगर (stack_entry->slot_type[soff % BPF_REG_SIZE] == STACK_ZERO)
			जारी;

		अगर (nfp_map->use_map[i / 4].type == NFP_MAP_USE_ATOMIC_CNT) अणु
			pr_vlog(env, "value at offset %d/%d may be non-zero, bpf_map_update_elem() is required to initialize atomic counters to zero to avoid offload endian issues\n",
				i, soff);
			वापस false;
		पूर्ण
		nfp_map->use_map[i / 4].non_zero_update = 1;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
nfp_bpf_stack_arg_ok(स्थिर अक्षर *fname, काष्ठा bpf_verअगरier_env *env,
		     स्थिर काष्ठा bpf_reg_state *reg,
		     काष्ठा nfp_bpf_reg_state *old_arg)
अणु
	s64 off, old_off;

	अगर (reg->type != PTR_TO_STACK) अणु
		pr_vlog(env, "%s: unsupported ptr type %d\n",
			fname, reg->type);
		वापस false;
	पूर्ण
	अगर (!tnum_is_स्थिर(reg->var_off)) अणु
		pr_vlog(env, "%s: variable pointer\n", fname);
		वापस false;
	पूर्ण

	off = reg->var_off.value + reg->off;
	अगर (-off % 4) अणु
		pr_vlog(env, "%s: unaligned stack pointer %lld\n", fname, -off);
		वापस false;
	पूर्ण

	/* Rest of the checks is only अगर we re-parse the same insn */
	अगर (!old_arg)
		वापस true;

	old_off = old_arg->reg.var_off.value + old_arg->reg.off;
	old_arg->var_off |= off != old_off;

	वापस true;
पूर्ण

अटल bool
nfp_bpf_map_call_ok(स्थिर अक्षर *fname, काष्ठा bpf_verअगरier_env *env,
		    काष्ठा nfp_insn_meta *meta,
		    u32 helper_tgt, स्थिर काष्ठा bpf_reg_state *reg1)
अणु
	अगर (!helper_tgt) अणु
		pr_vlog(env, "%s: not supported by FW\n", fname);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक
nfp_bpf_check_helper_call(काष्ठा nfp_prog *nfp_prog,
			  काष्ठा bpf_verअगरier_env *env,
			  काष्ठा nfp_insn_meta *meta)
अणु
	स्थिर काष्ठा bpf_reg_state *reg1 = cur_regs(env) + BPF_REG_1;
	स्थिर काष्ठा bpf_reg_state *reg2 = cur_regs(env) + BPF_REG_2;
	स्थिर काष्ठा bpf_reg_state *reg3 = cur_regs(env) + BPF_REG_3;
	काष्ठा nfp_app_bpf *bpf = nfp_prog->bpf;
	u32 func_id = meta->insn.imm;

	चयन (func_id) अणु
	हाल BPF_FUNC_xdp_adjust_head:
		अगर (!bpf->adjust_head.off_max) अणु
			pr_vlog(env, "adjust_head not supported by FW\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (!(bpf->adjust_head.flags & NFP_BPF_ADJUST_HEAD_NO_META)) अणु
			pr_vlog(env, "adjust_head: FW requires shifting metadata, not supported by the driver\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		nfp_record_adjust_head(bpf, nfp_prog, meta, reg2);
		अवरोध;

	हाल BPF_FUNC_xdp_adjust_tail:
		अगर (!bpf->adjust_tail) अणु
			pr_vlog(env, "adjust_tail not supported by FW\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अवरोध;

	हाल BPF_FUNC_map_lookup_elem:
		अगर (!nfp_bpf_map_call_ok("map_lookup", env, meta,
					 bpf->helpers.map_lookup, reg1) ||
		    !nfp_bpf_stack_arg_ok("map_lookup", env, reg2,
					  meta->func_id ? &meta->arg2 : शून्य))
			वापस -EOPNOTSUPP;
		अवरोध;

	हाल BPF_FUNC_map_update_elem:
		अगर (!nfp_bpf_map_call_ok("map_update", env, meta,
					 bpf->helpers.map_update, reg1) ||
		    !nfp_bpf_stack_arg_ok("map_update", env, reg2,
					  meta->func_id ? &meta->arg2 : शून्य) ||
		    !nfp_bpf_stack_arg_ok("map_update", env, reg3, शून्य) ||
		    !nfp_bpf_map_update_value_ok(env))
			वापस -EOPNOTSUPP;
		अवरोध;

	हाल BPF_FUNC_map_delete_elem:
		अगर (!nfp_bpf_map_call_ok("map_delete", env, meta,
					 bpf->helpers.map_delete, reg1) ||
		    !nfp_bpf_stack_arg_ok("map_delete", env, reg2,
					  meta->func_id ? &meta->arg2 : शून्य))
			वापस -EOPNOTSUPP;
		अवरोध;

	हाल BPF_FUNC_get_pअक्रमom_u32:
		अगर (bpf->pseuकरो_अक्रमom)
			अवरोध;
		pr_vlog(env, "bpf_get_prandom_u32(): FW doesn't support random number generation\n");
		वापस -EOPNOTSUPP;

	हाल BPF_FUNC_perf_event_output:
		BUILD_BUG_ON(NFP_BPF_SCALAR_VALUE != SCALAR_VALUE ||
			     NFP_BPF_MAP_VALUE != PTR_TO_MAP_VALUE ||
			     NFP_BPF_STACK != PTR_TO_STACK ||
			     NFP_BPF_PACKET_DATA != PTR_TO_PACKET);

		अगर (!bpf->helpers.perf_event_output) अणु
			pr_vlog(env, "event_output: not supported by FW\n");
			वापस -EOPNOTSUPP;
		पूर्ण

		/* Force current CPU to make sure we can report the event
		 * wherever we get the control message from FW.
		 */
		अगर (reg3->var_off.mask & BPF_F_INDEX_MASK ||
		    (reg3->var_off.value & BPF_F_INDEX_MASK) !=
		    BPF_F_CURRENT_CPU) अणु
			अक्षर tn_buf[48];

			tnum_strn(tn_buf, माप(tn_buf), reg3->var_off);
			pr_vlog(env, "event_output: must use BPF_F_CURRENT_CPU, var_off: %s\n",
				tn_buf);
			वापस -EOPNOTSUPP;
		पूर्ण

		/* Save space in meta, we करोn't care about arguments other
		 * than 4th meta, shove it पूर्णांकo arg1.
		 */
		reg1 = cur_regs(env) + BPF_REG_4;

		अगर (reg1->type != SCALAR_VALUE /* शून्य ptr */ &&
		    reg1->type != PTR_TO_STACK &&
		    reg1->type != PTR_TO_MAP_VALUE &&
		    reg1->type != PTR_TO_PACKET) अणु
			pr_vlog(env, "event_output: unsupported ptr type: %d\n",
				reg1->type);
			वापस -EOPNOTSUPP;
		पूर्ण

		अगर (reg1->type == PTR_TO_STACK &&
		    !nfp_bpf_stack_arg_ok("event_output", env, reg1, शून्य))
			वापस -EOPNOTSUPP;

		/* Warn user that on offload NFP may वापस success even अगर map
		 * is not going to accept the event, since the event output is
		 * fully async and device won't know the state of the map.
		 * There is also FW limitation on the event length.
		 *
		 * Lost events will not show up on the perf ring, driver
		 * won't see them at all.  Events may also get reordered.
		 */
		dev_warn_once(&nfp_prog->bpf->app->pf->pdev->dev,
			      "bpf: note: return codes and behavior of bpf_event_output() helper differs for offloaded programs!\n");
		pr_vlog(env, "warning: return codes and behavior of event_output helper differ for offload!\n");

		अगर (!meta->func_id)
			अवरोध;

		अगर (reg1->type != meta->arg1.type) अणु
			pr_vlog(env, "event_output: ptr type changed: %d %d\n",
				meta->arg1.type, reg1->type);
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	शेष:
		pr_vlog(env, "unsupported function id: %d\n", func_id);
		वापस -EOPNOTSUPP;
	पूर्ण

	meta->func_id = func_id;
	meta->arg1 = *reg1;
	meta->arg2.reg = *reg2;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_check_निकास(काष्ठा nfp_prog *nfp_prog,
		   काष्ठा bpf_verअगरier_env *env)
अणु
	स्थिर काष्ठा bpf_reg_state *reg0 = cur_regs(env) + BPF_REG_0;
	u64 imm;

	अगर (nfp_prog->type == BPF_PROG_TYPE_XDP)
		वापस 0;

	अगर (!(reg0->type == SCALAR_VALUE && tnum_is_स्थिर(reg0->var_off))) अणु
		अक्षर tn_buf[48];

		tnum_strn(tn_buf, माप(tn_buf), reg0->var_off);
		pr_vlog(env, "unsupported exit state: %d, var_off: %s\n",
			reg0->type, tn_buf);
		वापस -EINVAL;
	पूर्ण

	imm = reg0->var_off.value;
	अगर (nfp_prog->type == BPF_PROG_TYPE_SCHED_CLS &&
	    imm <= TC_ACT_REसूचीECT &&
	    imm != TC_ACT_SHOT && imm != TC_ACT_STOLEN &&
	    imm != TC_ACT_QUEUED) अणु
		pr_vlog(env, "unsupported exit state: %d, imm: %llx\n",
			reg0->type, imm);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_check_stack_access(काष्ठा nfp_prog *nfp_prog,
			   काष्ठा nfp_insn_meta *meta,
			   स्थिर काष्ठा bpf_reg_state *reg,
			   काष्ठा bpf_verअगरier_env *env)
अणु
	s32 old_off, new_off;

	अगर (reg->frameno != env->cur_state->curframe)
		meta->flags |= FLAG_INSN_PTR_CALLER_STACK_FRAME;

	अगर (!tnum_is_स्थिर(reg->var_off)) अणु
		pr_vlog(env, "variable ptr stack access\n");
		वापस -EINVAL;
	पूर्ण

	अगर (meta->ptr.type == NOT_INIT)
		वापस 0;

	old_off = meta->ptr.off + meta->ptr.var_off.value;
	new_off = reg->off + reg->var_off.value;

	meta->ptr_not_स्थिर |= old_off != new_off;

	अगर (!meta->ptr_not_स्थिर)
		वापस 0;

	अगर (old_off % 4 == new_off % 4)
		वापस 0;

	pr_vlog(env, "stack access changed location was:%d is:%d\n",
		old_off, new_off);
	वापस -EINVAL;
पूर्ण

अटल स्थिर अक्षर *nfp_bpf_map_use_name(क्रमागत nfp_bpf_map_use use)
अणु
	अटल स्थिर अक्षर * स्थिर names[] = अणु
		[NFP_MAP_UNUSED]	= "unused",
		[NFP_MAP_USE_READ]	= "read",
		[NFP_MAP_USE_WRITE]	= "write",
		[NFP_MAP_USE_ATOMIC_CNT] = "atomic",
	पूर्ण;

	अगर (use >= ARRAY_SIZE(names) || !names[use])
		वापस "unknown";
	वापस names[use];
पूर्ण

अटल पूर्णांक
nfp_bpf_map_mark_used_one(काष्ठा bpf_verअगरier_env *env,
			  काष्ठा nfp_bpf_map *nfp_map,
			  अचिन्हित पूर्णांक off, क्रमागत nfp_bpf_map_use use)
अणु
	अगर (nfp_map->use_map[off / 4].type != NFP_MAP_UNUSED &&
	    nfp_map->use_map[off / 4].type != use) अणु
		pr_vlog(env, "map value use type conflict %s vs %s off: %u\n",
			nfp_bpf_map_use_name(nfp_map->use_map[off / 4].type),
			nfp_bpf_map_use_name(use), off);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (nfp_map->use_map[off / 4].non_zero_update &&
	    use == NFP_MAP_USE_ATOMIC_CNT) अणु
		pr_vlog(env, "atomic counter in map value may already be initialized to non-zero value off: %u\n",
			off);
		वापस -EOPNOTSUPP;
	पूर्ण

	nfp_map->use_map[off / 4].type = use;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_map_mark_used(काष्ठा bpf_verअगरier_env *env, काष्ठा nfp_insn_meta *meta,
		      स्थिर काष्ठा bpf_reg_state *reg,
		      क्रमागत nfp_bpf_map_use use)
अणु
	काष्ठा bpf_offloaded_map *offmap;
	काष्ठा nfp_bpf_map *nfp_map;
	अचिन्हित पूर्णांक size, off;
	पूर्णांक i, err;

	अगर (!tnum_is_स्थिर(reg->var_off)) अणु
		pr_vlog(env, "map value offset is variable\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	off = reg->var_off.value + meta->insn.off + reg->off;
	size = BPF_LDST_BYTES(&meta->insn);
	offmap = map_to_offmap(reg->map_ptr);
	nfp_map = offmap->dev_priv;

	अगर (off + size > offmap->map.value_size) अणु
		pr_vlog(env, "map value access out-of-bounds\n");
		वापस -EINVAL;
	पूर्ण

	क्रम (i = 0; i < size; i += 4 - (off + i) % 4) अणु
		err = nfp_bpf_map_mark_used_one(env, nfp_map, off + i, use);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_check_ptr(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		  काष्ठा bpf_verअगरier_env *env, u8 reg_no)
अणु
	स्थिर काष्ठा bpf_reg_state *reg = cur_regs(env) + reg_no;
	पूर्णांक err;

	अगर (reg->type != PTR_TO_CTX &&
	    reg->type != PTR_TO_STACK &&
	    reg->type != PTR_TO_MAP_VALUE &&
	    reg->type != PTR_TO_PACKET) अणु
		pr_vlog(env, "unsupported ptr type: %d\n", reg->type);
		वापस -EINVAL;
	पूर्ण

	अगर (reg->type == PTR_TO_STACK) अणु
		err = nfp_bpf_check_stack_access(nfp_prog, meta, reg, env);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (reg->type == PTR_TO_MAP_VALUE) अणु
		अगर (is_mbpf_load(meta)) अणु
			err = nfp_bpf_map_mark_used(env, meta, reg,
						    NFP_MAP_USE_READ);
			अगर (err)
				वापस err;
		पूर्ण
		अगर (is_mbpf_store(meta)) अणु
			pr_vlog(env, "map writes not supported\n");
			वापस -EOPNOTSUPP;
		पूर्ण
		अगर (is_mbpf_atomic(meta)) अणु
			err = nfp_bpf_map_mark_used(env, meta, reg,
						    NFP_MAP_USE_ATOMIC_CNT);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	अगर (meta->ptr.type != NOT_INIT && meta->ptr.type != reg->type) अणु
		pr_vlog(env, "ptr type changed for instruction %d -> %d\n",
			meta->ptr.type, reg->type);
		वापस -EINVAL;
	पूर्ण

	meta->ptr = *reg;

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_bpf_check_store(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		    काष्ठा bpf_verअगरier_env *env)
अणु
	स्थिर काष्ठा bpf_reg_state *reg = cur_regs(env) + meta->insn.dst_reg;

	अगर (reg->type == PTR_TO_CTX) अणु
		अगर (nfp_prog->type == BPF_PROG_TYPE_XDP) अणु
			/* XDP ctx accesses must be 4B in size */
			चयन (meta->insn.off) अणु
			हाल दुरत्व(काष्ठा xdp_md, rx_queue_index):
				अगर (nfp_prog->bpf->queue_select)
					जाओ निकास_check_ptr;
				pr_vlog(env, "queue selection not supported by FW\n");
				वापस -EOPNOTSUPP;
			पूर्ण
		पूर्ण
		pr_vlog(env, "unsupported store to context field\n");
		वापस -EOPNOTSUPP;
	पूर्ण
निकास_check_ptr:
	वापस nfp_bpf_check_ptr(nfp_prog, meta, env, meta->insn.dst_reg);
पूर्ण

अटल पूर्णांक
nfp_bpf_check_atomic(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		     काष्ठा bpf_verअगरier_env *env)
अणु
	स्थिर काष्ठा bpf_reg_state *sreg = cur_regs(env) + meta->insn.src_reg;
	स्थिर काष्ठा bpf_reg_state *dreg = cur_regs(env) + meta->insn.dst_reg;

	अगर (meta->insn.imm != BPF_ADD) अणु
		pr_vlog(env, "atomic op not implemented: %d\n", meta->insn.imm);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (dreg->type != PTR_TO_MAP_VALUE) अणु
		pr_vlog(env, "atomic add not to a map value pointer: %d\n",
			dreg->type);
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (sreg->type != SCALAR_VALUE) अणु
		pr_vlog(env, "atomic add not of a scalar: %d\n", sreg->type);
		वापस -EOPNOTSUPP;
	पूर्ण

	meta->xadd_over_16bit |=
		sreg->var_off.value > 0xffff || sreg->var_off.mask > 0xffff;
	meta->xadd_maybe_16bit |=
		(sreg->var_off.value & ~sreg->var_off.mask) <= 0xffff;

	वापस nfp_bpf_check_ptr(nfp_prog, meta, env, meta->insn.dst_reg);
पूर्ण

अटल पूर्णांक
nfp_bpf_check_alu(काष्ठा nfp_prog *nfp_prog, काष्ठा nfp_insn_meta *meta,
		  काष्ठा bpf_verअगरier_env *env)
अणु
	स्थिर काष्ठा bpf_reg_state *sreg =
		cur_regs(env) + meta->insn.src_reg;
	स्थिर काष्ठा bpf_reg_state *dreg =
		cur_regs(env) + meta->insn.dst_reg;

	meta->umin_src = min(meta->umin_src, sreg->umin_value);
	meta->umax_src = max(meta->umax_src, sreg->umax_value);
	meta->umin_dst = min(meta->umin_dst, dreg->umin_value);
	meta->umax_dst = max(meta->umax_dst, dreg->umax_value);

	/* NFP supports u16 and u32 multiplication.
	 *
	 * For ALU64, अगर either opeअक्रम is beyond u32's value range, we reject
	 * it. One thing to note, अगर the source opeअक्रम is BPF_K, then we need
	 * to check "imm" field directly, and we'd reject it अगर it is negative.
	 * Because क्रम ALU64, "imm" (with s32 type) is expected to be sign
	 * extended to s64 which NFP mul करोesn't support.
	 *
	 * For ALU32, it is fine क्रम "imm" be negative though, because the
	 * result is 32-bits and there is no dअगरference on the low halve of
	 * the result क्रम चिन्हित/अचिन्हित mul, so we will get correct result.
	 */
	अगर (is_mbpf_mul(meta)) अणु
		अगर (meta->umax_dst > U32_MAX) अणु
			pr_vlog(env, "multiplier is not within u32 value range\n");
			वापस -EINVAL;
		पूर्ण
		अगर (mbpf_src(meta) == BPF_X && meta->umax_src > U32_MAX) अणु
			pr_vlog(env, "multiplicand is not within u32 value range\n");
			वापस -EINVAL;
		पूर्ण
		अगर (mbpf_class(meta) == BPF_ALU64 &&
		    mbpf_src(meta) == BPF_K && meta->insn.imm < 0) अणु
			pr_vlog(env, "sign extended multiplicand won't be within u32 value range\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	/* NFP करोesn't have भागide inकाष्ठाions, we support भागide by स्थिरant
	 * through reciprocal multiplication. Given NFP support multiplication
	 * no bigger than u32, we'd require भागisor and भागidend no bigger than
	 * that as well.
	 *
	 * Also eBPF करोesn't support चिन्हित भागide and has enक्रमced this on C
	 * language level by failing compilation. However LLVM assembler hasn't
	 * enक्रमced this, so it is possible क्रम negative स्थिरant to leak in as
	 * a BPF_K opeअक्रम through assembly code, we reject such हालs as well.
	 */
	अगर (is_mbpf_भाग(meta)) अणु
		अगर (meta->umax_dst > U32_MAX) अणु
			pr_vlog(env, "dividend is not within u32 value range\n");
			वापस -EINVAL;
		पूर्ण
		अगर (mbpf_src(meta) == BPF_X) अणु
			अगर (meta->umin_src != meta->umax_src) अणु
				pr_vlog(env, "divisor is not constant\n");
				वापस -EINVAL;
			पूर्ण
			अगर (meta->umax_src > U32_MAX) अणु
				pr_vlog(env, "divisor is not within u32 value range\n");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
		अगर (mbpf_src(meta) == BPF_K && meta->insn.imm < 0) अणु
			pr_vlog(env, "divide by negative constant is not supported\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक nfp_verअगरy_insn(काष्ठा bpf_verअगरier_env *env, पूर्णांक insn_idx,
		    पूर्णांक prev_insn_idx)
अणु
	काष्ठा nfp_prog *nfp_prog = env->prog->aux->offload->dev_priv;
	काष्ठा nfp_insn_meta *meta = nfp_prog->verअगरier_meta;

	meta = nfp_bpf_जाओ_meta(nfp_prog, meta, insn_idx);
	nfp_prog->verअगरier_meta = meta;

	अगर (!nfp_bpf_supported_opcode(meta->insn.code)) अणु
		pr_vlog(env, "instruction %#02x not supported\n",
			meta->insn.code);
		वापस -EINVAL;
	पूर्ण

	अगर (meta->insn.src_reg >= MAX_BPF_REG ||
	    meta->insn.dst_reg >= MAX_BPF_REG) अणु
		pr_vlog(env, "program uses extended registers - jit hardening?\n");
		वापस -EINVAL;
	पूर्ण

	अगर (is_mbpf_helper_call(meta))
		वापस nfp_bpf_check_helper_call(nfp_prog, env, meta);
	अगर (meta->insn.code == (BPF_JMP | BPF_EXIT))
		वापस nfp_bpf_check_निकास(nfp_prog, env);

	अगर (is_mbpf_load(meta))
		वापस nfp_bpf_check_ptr(nfp_prog, meta, env,
					 meta->insn.src_reg);
	अगर (is_mbpf_store(meta))
		वापस nfp_bpf_check_store(nfp_prog, meta, env);

	अगर (is_mbpf_atomic(meta))
		वापस nfp_bpf_check_atomic(nfp_prog, meta, env);

	अगर (is_mbpf_alu(meta))
		वापस nfp_bpf_check_alu(nfp_prog, meta, env);

	वापस 0;
पूर्ण

अटल पूर्णांक
nfp_assign_subprog_idx_and_regs(काष्ठा bpf_verअगरier_env *env,
				काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta;
	पूर्णांक index = 0;

	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		अगर (nfp_is_subprog_start(meta))
			index++;
		meta->subprog_idx = index;

		अगर (meta->insn.dst_reg >= BPF_REG_6 &&
		    meta->insn.dst_reg <= BPF_REG_9)
			nfp_prog->subprog[index].needs_reg_push = 1;
	पूर्ण

	अगर (index + 1 != nfp_prog->subprog_cnt) अणु
		pr_vlog(env, "BUG: number of processed BPF functions is not consistent (processed %d, expected %d)\n",
			index + 1, nfp_prog->subprog_cnt);
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल अचिन्हित पूर्णांक nfp_bpf_get_stack_usage(काष्ठा nfp_prog *nfp_prog)
अणु
	काष्ठा nfp_insn_meta *meta = nfp_prog_first_meta(nfp_prog);
	अचिन्हित पूर्णांक max_depth = 0, depth = 0, frame = 0;
	काष्ठा nfp_insn_meta *ret_insn[MAX_CALL_FRAMES];
	अचिन्हित लघु frame_depths[MAX_CALL_FRAMES];
	अचिन्हित लघु ret_prog[MAX_CALL_FRAMES];
	अचिन्हित लघु idx = meta->subprog_idx;

	/* Inspired from check_max_stack_depth() from kernel verअगरier.
	 * Starting from मुख्य subprogram, walk all inकाष्ठाions and recursively
	 * walk all callees that given subprogram can call. Since recursion is
	 * prevented by the kernel verअगरier, this algorithm only needs a local
	 * stack of MAX_CALL_FRAMES to remember callsites.
	 */
process_subprog:
	frame_depths[frame] = nfp_prog->subprog[idx].stack_depth;
	frame_depths[frame] = round_up(frame_depths[frame], STACK_FRAME_ALIGN);
	depth += frame_depths[frame];
	max_depth = max(max_depth, depth);

जारी_subprog:
	क्रम (; meta != nfp_prog_last_meta(nfp_prog) && meta->subprog_idx == idx;
	     meta = nfp_meta_next(meta)) अणु
		अगर (!is_mbpf_pseuकरो_call(meta))
			जारी;

		/* We found a call to a subprogram. Remember inकाष्ठाion to
		 * वापस to and subprog id.
		 */
		ret_insn[frame] = nfp_meta_next(meta);
		ret_prog[frame] = idx;

		/* Find the callee and start processing it. */
		meta = nfp_bpf_जाओ_meta(nfp_prog, meta,
					 meta->n + 1 + meta->insn.imm);
		idx = meta->subprog_idx;
		frame++;
		जाओ process_subprog;
	पूर्ण
	/* End of क्रम() loop means the last inकाष्ठाion of the subprog was
	 * reached. If we popped all stack frames, वापस; otherwise, go on
	 * processing reमुख्यing inकाष्ठाions from the caller.
	 */
	अगर (frame == 0)
		वापस max_depth;

	depth -= frame_depths[frame];
	frame--;
	meta = ret_insn[frame];
	idx = ret_prog[frame];
	जाओ जारी_subprog;
पूर्ण

अटल व्योम nfp_bpf_insn_flag_zext(काष्ठा nfp_prog *nfp_prog,
				   काष्ठा bpf_insn_aux_data *aux)
अणु
	काष्ठा nfp_insn_meta *meta;

	list_क्रम_each_entry(meta, &nfp_prog->insns, l) अणु
		अगर (aux[meta->n].zext_dst)
			meta->flags |= FLAG_INSN_DO_ZEXT;
	पूर्ण
पूर्ण

पूर्णांक nfp_bpf_finalize(काष्ठा bpf_verअगरier_env *env)
अणु
	काष्ठा bpf_subprog_info *info;
	काष्ठा nfp_prog *nfp_prog;
	अचिन्हित पूर्णांक max_stack;
	काष्ठा nfp_net *nn;
	पूर्णांक i;

	nfp_prog = env->prog->aux->offload->dev_priv;
	nfp_prog->subprog_cnt = env->subprog_cnt;
	nfp_prog->subprog = kसुस्मृति(nfp_prog->subprog_cnt,
				    माप(nfp_prog->subprog[0]), GFP_KERNEL);
	अगर (!nfp_prog->subprog)
		वापस -ENOMEM;

	nfp_assign_subprog_idx_and_regs(env, nfp_prog);

	info = env->subprog_info;
	क्रम (i = 0; i < nfp_prog->subprog_cnt; i++) अणु
		nfp_prog->subprog[i].stack_depth = info[i].stack_depth;

		अगर (i == 0)
			जारी;

		/* Account क्रम size of वापस address. */
		nfp_prog->subprog[i].stack_depth += REG_WIDTH;
		/* Account क्रम size of saved रेजिस्टरs, अगर necessary. */
		अगर (nfp_prog->subprog[i].needs_reg_push)
			nfp_prog->subprog[i].stack_depth += BPF_REG_SIZE * 4;
	पूर्ण

	nn = netdev_priv(env->prog->aux->offload->netdev);
	max_stack = nn_पढ़ोb(nn, NFP_NET_CFG_BPF_STACK_SZ) * 64;
	nfp_prog->stack_size = nfp_bpf_get_stack_usage(nfp_prog);
	अगर (nfp_prog->stack_size > max_stack) अणु
		pr_vlog(env, "stack too large: program %dB > FW stack %dB\n",
			nfp_prog->stack_size, max_stack);
		वापस -EOPNOTSUPP;
	पूर्ण

	nfp_bpf_insn_flag_zext(nfp_prog, env->insn_aux_data);
	वापस 0;
पूर्ण

पूर्णांक nfp_bpf_opt_replace_insn(काष्ठा bpf_verअगरier_env *env, u32 off,
			     काष्ठा bpf_insn *insn)
अणु
	काष्ठा nfp_prog *nfp_prog = env->prog->aux->offload->dev_priv;
	काष्ठा bpf_insn_aux_data *aux_data = env->insn_aux_data;
	काष्ठा nfp_insn_meta *meta = nfp_prog->verअगरier_meta;

	meta = nfp_bpf_जाओ_meta(nfp_prog, meta, aux_data[off].orig_idx);
	nfp_prog->verअगरier_meta = meta;

	/* conditional jump to jump conversion */
	अगर (is_mbpf_cond_jump(meta) &&
	    insn->code == (BPF_JMP | BPF_JA | BPF_K)) अणु
		अचिन्हित पूर्णांक tgt_off;

		tgt_off = off + insn->off + 1;

		अगर (!insn->off) अणु
			meta->jmp_dst = list_next_entry(meta, l);
			meta->jump_neg_op = false;
		पूर्ण अन्यथा अगर (meta->jmp_dst->n != aux_data[tgt_off].orig_idx) अणु
			pr_vlog(env, "branch hard wire at %d changes target %d -> %d\n",
				off, meta->jmp_dst->n,
				aux_data[tgt_off].orig_idx);
			वापस -EINVAL;
		पूर्ण
		वापस 0;
	पूर्ण

	pr_vlog(env, "unsupported instruction replacement %hhx -> %hhx\n",
		meta->insn.code, insn->code);
	वापस -EINVAL;
पूर्ण

पूर्णांक nfp_bpf_opt_हटाओ_insns(काष्ठा bpf_verअगरier_env *env, u32 off, u32 cnt)
अणु
	काष्ठा nfp_prog *nfp_prog = env->prog->aux->offload->dev_priv;
	काष्ठा bpf_insn_aux_data *aux_data = env->insn_aux_data;
	काष्ठा nfp_insn_meta *meta = nfp_prog->verअगरier_meta;
	अचिन्हित पूर्णांक i;

	meta = nfp_bpf_जाओ_meta(nfp_prog, meta, aux_data[off].orig_idx);

	क्रम (i = 0; i < cnt; i++) अणु
		अगर (WARN_ON_ONCE(&meta->l == &nfp_prog->insns))
			वापस -EINVAL;

		/* करोesn't count अगर it alपढ़ोy has the flag */
		अगर (meta->flags & FLAG_INSN_SKIP_VERIFIER_OPT)
			i--;

		meta->flags |= FLAG_INSN_SKIP_VERIFIER_OPT;
		meta = list_next_entry(meta, l);
	पूर्ण

	वापस 0;
पूर्ण
