<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2021 Mellanox Technologies. */

#समावेश <linux/skbuff.h>
#समावेश <net/psample.h>
#समावेश "en/mapping.h"
#समावेश "esw/sample.h"
#समावेश "eswitch.h"
#समावेश "en_tc.h"
#समावेश "fs_core.h"

#घोषणा MLX5_ESW_VPORT_TBL_SIZE_SAMPLE (64 * 1024)

अटल स्थिर काष्ठा esw_vport_tbl_namespace mlx5_esw_vport_tbl_sample_ns = अणु
	.max_fte = MLX5_ESW_VPORT_TBL_SIZE_SAMPLE,
	.max_num_groups = 0,    /* शेष num of groups */
	.flags = MLX5_FLOW_TABLE_TUNNEL_EN_REFORMAT | MLX5_FLOW_TABLE_TUNNEL_EN_DECAP,
पूर्ण;

काष्ठा mlx5_esw_psample अणु
	काष्ठा mlx5e_priv *priv;
	काष्ठा mlx5_flow_table *termtbl;
	काष्ठा mlx5_flow_handle *termtbl_rule;
	DECLARE_HASHTABLE(hashtbl, 8);
	काष्ठा mutex ht_lock; /* protect hashtbl */
	DECLARE_HASHTABLE(restore_hashtbl, 8);
	काष्ठा mutex restore_lock; /* protect restore_hashtbl */
पूर्ण;

काष्ठा mlx5_sampler अणु
	काष्ठा hlist_node hlist;
	u32 sampler_id;
	u32 sample_ratio;
	u32 sample_table_id;
	u32 शेष_table_id;
	पूर्णांक count;
पूर्ण;

काष्ठा mlx5_sample_flow अणु
	काष्ठा mlx5_sampler *sampler;
	काष्ठा mlx5_sample_restore *restore;
	काष्ठा mlx5_flow_attr *pre_attr;
	काष्ठा mlx5_flow_handle *pre_rule;
	काष्ठा mlx5_flow_handle *rule;
पूर्ण;

काष्ठा mlx5_sample_restore अणु
	काष्ठा hlist_node hlist;
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
	काष्ठा mlx5_flow_handle *rule;
	u32 obj_id;
	पूर्णांक count;
पूर्ण;

अटल पूर्णांक
sampler_termtbl_create(काष्ठा mlx5_esw_psample *esw_psample)
अणु
	काष्ठा mlx5_core_dev *dev = esw_psample->priv->mdev;
	काष्ठा mlx5_eचयन *esw = dev->priv.eचयन;
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_namespace *root_ns;
	काष्ठा mlx5_flow_act act = अणुपूर्ण;
	पूर्णांक err;

	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(dev, termination_table))  अणु
		mlx5_core_warn(dev, "termination table is not supported\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	root_ns = mlx5_get_flow_namespace(dev, MLX5_FLOW_NAMESPACE_FDB);
	अगर (!root_ns) अणु
		mlx5_core_warn(dev, "failed to get FDB flow namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	ft_attr.flags = MLX5_FLOW_TABLE_TERMINATION | MLX5_FLOW_TABLE_UNMANAGED;
	ft_attr.स्वतःgroup.max_num_groups = 1;
	ft_attr.prio = FDB_SLOW_PATH;
	ft_attr.max_fte = 1;
	ft_attr.level = 1;
	esw_psample->termtbl = mlx5_create_स्वतः_grouped_flow_table(root_ns, &ft_attr);
	अगर (IS_ERR(esw_psample->termtbl)) अणु
		err = PTR_ERR(esw_psample->termtbl);
		mlx5_core_warn(dev, "failed to create termtbl, err: %d\n", err);
		वापस err;
	पूर्ण

	act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	dest.vport.num = esw->manager_vport;
	esw_psample->termtbl_rule = mlx5_add_flow_rules(esw_psample->termtbl, शून्य, &act, &dest, 1);
	अगर (IS_ERR(esw_psample->termtbl_rule)) अणु
		err = PTR_ERR(esw_psample->termtbl_rule);
		mlx5_core_warn(dev, "failed to create termtbl rule, err: %d\n", err);
		mlx5_destroy_flow_table(esw_psample->termtbl);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम
sampler_termtbl_destroy(काष्ठा mlx5_esw_psample *esw_psample)
अणु
	mlx5_del_flow_rules(esw_psample->termtbl_rule);
	mlx5_destroy_flow_table(esw_psample->termtbl);
पूर्ण

अटल पूर्णांक
sampler_obj_create(काष्ठा mlx5_core_dev *mdev, काष्ठा mlx5_sampler *sampler)
अणु
	u32 in[MLX5_ST_SZ_DW(create_sampler_obj_in)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];
	u64 general_obj_types;
	व्योम *obj;
	पूर्णांक err;

	general_obj_types = MLX5_CAP_GEN_64(mdev, general_obj_types);
	अगर (!(general_obj_types & MLX5_HCA_CAP_GENERAL_OBJECT_TYPES_SAMPLER))
		वापस -EOPNOTSUPP;
	अगर (!MLX5_CAP_ESW_FLOWTABLE_FDB(mdev, ignore_flow_level))
		वापस -EOPNOTSUPP;

	obj = MLX5_ADDR_OF(create_sampler_obj_in, in, sampler_object);
	MLX5_SET(sampler_obj, obj, table_type, FS_FT_FDB);
	MLX5_SET(sampler_obj, obj, ignore_flow_level, 1);
	MLX5_SET(sampler_obj, obj, level, 1);
	MLX5_SET(sampler_obj, obj, sample_ratio, sampler->sample_ratio);
	MLX5_SET(sampler_obj, obj, sample_table_id, sampler->sample_table_id);
	MLX5_SET(sampler_obj, obj, शेष_table_id, sampler->शेष_table_id);
	MLX5_SET(general_obj_in_cmd_hdr, in, opcode, MLX5_CMD_OP_CREATE_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type, MLX5_GENERAL_OBJECT_TYPES_SAMPLER);

	err = mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
	अगर (!err)
		sampler->sampler_id = MLX5_GET(general_obj_out_cmd_hdr, out, obj_id);

	वापस err;
पूर्ण

अटल व्योम
sampler_obj_destroy(काष्ठा mlx5_core_dev *mdev, u32 sampler_id)
अणु
	u32 in[MLX5_ST_SZ_DW(general_obj_in_cmd_hdr)] = अणुपूर्ण;
	u32 out[MLX5_ST_SZ_DW(general_obj_out_cmd_hdr)];

	MLX5_SET(general_obj_in_cmd_hdr, in, opcode, MLX5_CMD_OP_DESTROY_GENERAL_OBJECT);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_type, MLX5_GENERAL_OBJECT_TYPES_SAMPLER);
	MLX5_SET(general_obj_in_cmd_hdr, in, obj_id, sampler_id);

	mlx5_cmd_exec(mdev, in, माप(in), out, माप(out));
पूर्ण

अटल u32
sampler_hash(u32 sample_ratio, u32 शेष_table_id)
अणु
	वापस jhash_2words(sample_ratio, शेष_table_id, 0);
पूर्ण

अटल पूर्णांक
sampler_cmp(u32 sample_ratio1, u32 शेष_table_id1, u32 sample_ratio2, u32 शेष_table_id2)
अणु
	वापस sample_ratio1 != sample_ratio2 || शेष_table_id1 != शेष_table_id2;
पूर्ण

अटल काष्ठा mlx5_sampler *
sampler_get(काष्ठा mlx5_esw_psample *esw_psample, u32 sample_ratio, u32 शेष_table_id)
अणु
	काष्ठा mlx5_sampler *sampler;
	u32 hash_key;
	पूर्णांक err;

	mutex_lock(&esw_psample->ht_lock);
	hash_key = sampler_hash(sample_ratio, शेष_table_id);
	hash_क्रम_each_possible(esw_psample->hashtbl, sampler, hlist, hash_key)
		अगर (!sampler_cmp(sampler->sample_ratio, sampler->शेष_table_id,
				 sample_ratio, शेष_table_id))
			जाओ add_ref;

	sampler = kzalloc(माप(*sampler), GFP_KERNEL);
	अगर (!sampler) अणु
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण

	sampler->sample_table_id = esw_psample->termtbl->id;
	sampler->शेष_table_id = शेष_table_id;
	sampler->sample_ratio = sample_ratio;

	err = sampler_obj_create(esw_psample->priv->mdev, sampler);
	अगर (err)
		जाओ err_create;

	hash_add(esw_psample->hashtbl, &sampler->hlist, hash_key);

add_ref:
	sampler->count++;
	mutex_unlock(&esw_psample->ht_lock);
	वापस sampler;

err_create:
	kमुक्त(sampler);
err_alloc:
	mutex_unlock(&esw_psample->ht_lock);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
sampler_put(काष्ठा mlx5_esw_psample *esw_psample, काष्ठा mlx5_sampler *sampler)
अणु
	mutex_lock(&esw_psample->ht_lock);
	अगर (--sampler->count == 0) अणु
		hash_del(&sampler->hlist);
		sampler_obj_destroy(esw_psample->priv->mdev, sampler->sampler_id);
		kमुक्त(sampler);
	पूर्ण
	mutex_unlock(&esw_psample->ht_lock);
पूर्ण

अटल काष्ठा mlx5_modअगरy_hdr *
sample_metadata_rule_get(काष्ठा mlx5_core_dev *mdev, u32 obj_id)
अणु
	काष्ठा mlx5e_tc_mod_hdr_acts mod_acts = अणुपूर्ण;
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
	पूर्णांक err;

	err = mlx5e_tc_match_to_reg_set(mdev, &mod_acts, MLX5_FLOW_NAMESPACE_FDB,
					CHAIN_TO_REG, obj_id);
	अगर (err)
		जाओ err_set_regc0;

	modअगरy_hdr = mlx5_modअगरy_header_alloc(mdev, MLX5_FLOW_NAMESPACE_FDB,
					      mod_acts.num_actions,
					      mod_acts.actions);
	अगर (IS_ERR(modअगरy_hdr)) अणु
		err = PTR_ERR(modअगरy_hdr);
		जाओ err_modअगरy_hdr;
	पूर्ण

	dealloc_mod_hdr_actions(&mod_acts);
	वापस modअगरy_hdr;

err_modअगरy_hdr:
	dealloc_mod_hdr_actions(&mod_acts);
err_set_regc0:
	वापस ERR_PTR(err);
पूर्ण

अटल काष्ठा mlx5_sample_restore *
sample_restore_get(काष्ठा mlx5_esw_psample *esw_psample, u32 obj_id)
अणु
	काष्ठा mlx5_core_dev *mdev = esw_psample->priv->mdev;
	काष्ठा mlx5_eचयन *esw = mdev->priv.eचयन;
	काष्ठा mlx5_sample_restore *restore;
	काष्ठा mlx5_modअगरy_hdr *modअगरy_hdr;
	पूर्णांक err;

	mutex_lock(&esw_psample->restore_lock);
	hash_क्रम_each_possible(esw_psample->restore_hashtbl, restore, hlist, obj_id)
		अगर (restore->obj_id == obj_id)
			जाओ add_ref;

	restore = kzalloc(माप(*restore), GFP_KERNEL);
	अगर (!restore) अणु
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण
	restore->obj_id = obj_id;

	modअगरy_hdr = sample_metadata_rule_get(mdev, obj_id);
	अगर (IS_ERR(modअगरy_hdr)) अणु
		err = PTR_ERR(modअगरy_hdr);
		जाओ err_modअगरy_hdr;
	पूर्ण
	restore->modअगरy_hdr = modअगरy_hdr;

	restore->rule = esw_add_restore_rule(esw, obj_id);
	अगर (IS_ERR(restore->rule)) अणु
		err = PTR_ERR(restore->rule);
		जाओ err_restore;
	पूर्ण

	hash_add(esw_psample->restore_hashtbl, &restore->hlist, obj_id);
add_ref:
	restore->count++;
	mutex_unlock(&esw_psample->restore_lock);
	वापस restore;

err_restore:
	mlx5_modअगरy_header_dealloc(mdev, restore->modअगरy_hdr);
err_modअगरy_hdr:
	kमुक्त(restore);
err_alloc:
	mutex_unlock(&esw_psample->restore_lock);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
sample_restore_put(काष्ठा mlx5_esw_psample *esw_psample, काष्ठा mlx5_sample_restore *restore)
अणु
	mutex_lock(&esw_psample->restore_lock);
	अगर (--restore->count == 0)
		hash_del(&restore->hlist);
	mutex_unlock(&esw_psample->restore_lock);

	अगर (!restore->count) अणु
		mlx5_del_flow_rules(restore->rule);
		mlx5_modअगरy_header_dealloc(esw_psample->priv->mdev, restore->modअगरy_hdr);
		kमुक्त(restore);
	पूर्ण
पूर्ण

व्योम mlx5_esw_sample_skb(काष्ठा sk_buff *skb, काष्ठा mlx5_mapped_obj *mapped_obj)
अणु
	u32 trunc_size = mapped_obj->sample.trunc_size;
	काष्ठा psample_group psample_group = अणुपूर्ण;
	काष्ठा psample_metadata md = अणुपूर्ण;

	md.trunc_size = trunc_size ? min(trunc_size, skb->len) : skb->len;
	md.in_अगरindex = skb->dev->अगरindex;
	psample_group.group_num = mapped_obj->sample.group_id;
	psample_group.net = &init_net;
	skb_push(skb, skb->mac_len);

	psample_sample_packet(&psample_group, skb, mapped_obj->sample.rate, &md);
पूर्ण

/* For the following typical flow table:
 *
 * +-------------------------------+
 * +       original flow table     +
 * +-------------------------------+
 * +         original match        +
 * +-------------------------------+
 * + sample action + other actions +
 * +-------------------------------+
 *
 * We translate the tc filter with sample action to the following HW model:
 *
 *         +---------------------+
 *         + original flow table +
 *         +---------------------+
 *         +   original match    +
 *         +---------------------+
 *                    |
 *                    v
 * +------------------------------------------------+
 * +                Flow Sampler Object             +
 * +------------------------------------------------+
 * +                    sample ratio                +
 * +------------------------------------------------+
 * +    sample table id    |    शेष table id    +
 * +------------------------------------------------+
 *            |                            |
 *            v                            v
 * +-----------------------------+  +----------------------------------------+
 * +        sample table         +  + शेष table per <vport, chain, prio> +
 * +-----------------------------+  +----------------------------------------+
 * + क्रमward to management vport +  +            original match              +
 * +-----------------------------+  +----------------------------------------+
 *                                  +            other actions               +
 *                                  +----------------------------------------+
 */
काष्ठा mlx5_flow_handle *
mlx5_esw_sample_offload(काष्ठा mlx5_esw_psample *esw_psample,
			काष्ठा mlx5_flow_spec *spec,
			काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_vport_tbl_attr per_vport_tbl_attr;
	काष्ठा mlx5_esw_flow_attr *pre_esw_attr;
	काष्ठा mlx5_mapped_obj restore_obj = अणुपूर्ण;
	काष्ठा mlx5_sample_flow *sample_flow;
	काष्ठा mlx5_sample_attr *sample_attr;
	काष्ठा mlx5_flow_table *शेष_tbl;
	काष्ठा mlx5_flow_attr *pre_attr;
	काष्ठा mlx5_eचयन *esw;
	u32 obj_id;
	पूर्णांक err;

	अगर (IS_ERR_OR_शून्य(esw_psample))
		वापस ERR_PTR(-EOPNOTSUPP);

	/* If slow path flag is set, eg. when the neigh is invalid क्रम encap,
	 * करोn't offload sample action.
	 */
	esw = esw_psample->priv->mdev->priv.eचयन;
	अगर (attr->flags & MLX5_ESW_ATTR_FLAG_SLOW_PATH)
		वापस mlx5_eचयन_add_offloaded_rule(esw, spec, attr);

	sample_flow = kzalloc(माप(*sample_flow), GFP_KERNEL);
	अगर (!sample_flow)
		वापस ERR_PTR(-ENOMEM);
	esw_attr->sample->sample_flow = sample_flow;

	/* Allocate शेष table per vport, chain and prio. Otherwise, there is
	 * only one शेष table क्रम the same sampler object. Rules with dअगरferent
	 * prio and chain may overlap. For CT sample action, per vport शेष
	 * table is needed to resotre the metadata.
	 */
	per_vport_tbl_attr.chain = attr->chain;
	per_vport_tbl_attr.prio = attr->prio;
	per_vport_tbl_attr.vport = esw_attr->in_rep->vport;
	per_vport_tbl_attr.vport_ns = &mlx5_esw_vport_tbl_sample_ns;
	शेष_tbl = mlx5_esw_vporttbl_get(esw, &per_vport_tbl_attr);
	अगर (IS_ERR(शेष_tbl)) अणु
		err = PTR_ERR(शेष_tbl);
		जाओ err_शेष_tbl;
	पूर्ण

	/* Perक्रमm the original matches on the शेष table.
	 * Offload all actions except the sample action.
	 */
	esw_attr->sample->sample_शेष_tbl = शेष_tbl;
	/* When offloading sample and encap action, अगर there is no valid
	 * neigh data काष्ठा, a slow path rule is offloaded first. Source
	 * port metadata match is set at that समय. A per vport table is
	 * alपढ़ोy allocated. No need to match it again. So clear the source
	 * port metadata match.
	 */
	mlx5_eचयन_clear_rule_source_port(esw, spec);
	sample_flow->rule = mlx5_eचयन_add_offloaded_rule(esw, spec, attr);
	अगर (IS_ERR(sample_flow->rule)) अणु
		err = PTR_ERR(sample_flow->rule);
		जाओ err_offload_rule;
	पूर्ण

	/* Create sampler object. */
	sample_flow->sampler = sampler_get(esw_psample, esw_attr->sample->rate, शेष_tbl->id);
	अगर (IS_ERR(sample_flow->sampler)) अणु
		err = PTR_ERR(sample_flow->sampler);
		जाओ err_sampler;
	पूर्ण

	/* Create an id mapping reg_c0 value to sample object. */
	restore_obj.type = MLX5_MAPPED_OBJ_SAMPLE;
	restore_obj.sample.group_id = esw_attr->sample->group_num;
	restore_obj.sample.rate = esw_attr->sample->rate;
	restore_obj.sample.trunc_size = esw_attr->sample->trunc_size;
	err = mapping_add(esw->offloads.reg_c0_obj_pool, &restore_obj, &obj_id);
	अगर (err)
		जाओ err_obj_id;
	esw_attr->sample->restore_obj_id = obj_id;

	/* Create sample restore context. */
	sample_flow->restore = sample_restore_get(esw_psample, obj_id);
	अगर (IS_ERR(sample_flow->restore)) अणु
		err = PTR_ERR(sample_flow->restore);
		जाओ err_sample_restore;
	पूर्ण

	/* Perक्रमm the original matches on the original table. Offload the
	 * sample action. The destination is the sampler object.
	 */
	pre_attr = mlx5_alloc_flow_attr(MLX5_FLOW_NAMESPACE_FDB);
	अगर (!pre_attr) अणु
		err = -ENOMEM;
		जाओ err_alloc_flow_attr;
	पूर्ण
	sample_attr = kzalloc(माप(*sample_attr), GFP_KERNEL);
	अगर (!sample_attr) अणु
		err = -ENOMEM;
		जाओ err_alloc_sample_attr;
	पूर्ण
	pre_esw_attr = pre_attr->esw_attr;
	pre_attr->action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST | MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
	pre_attr->modअगरy_hdr = sample_flow->restore->modअगरy_hdr;
	pre_attr->flags = MLX5_ESW_ATTR_FLAG_SAMPLE;
	pre_attr->chain = attr->chain;
	pre_attr->prio = attr->prio;
	pre_esw_attr->sample = sample_attr;
	pre_esw_attr->sample->sampler_id = sample_flow->sampler->sampler_id;
	pre_esw_attr->in_mdev = esw_attr->in_mdev;
	pre_esw_attr->in_rep = esw_attr->in_rep;
	sample_flow->pre_rule = mlx5_eचयन_add_offloaded_rule(esw, spec, pre_attr);
	अगर (IS_ERR(sample_flow->pre_rule)) अणु
		err = PTR_ERR(sample_flow->pre_rule);
		जाओ err_pre_offload_rule;
	पूर्ण
	sample_flow->pre_attr = pre_attr;

	वापस sample_flow->rule;

err_pre_offload_rule:
	kमुक्त(sample_attr);
err_alloc_sample_attr:
	kमुक्त(pre_attr);
err_alloc_flow_attr:
	sample_restore_put(esw_psample, sample_flow->restore);
err_sample_restore:
	mapping_हटाओ(esw->offloads.reg_c0_obj_pool, obj_id);
err_obj_id:
	sampler_put(esw_psample, sample_flow->sampler);
err_sampler:
	/* For sample offload, rule is added in शेष_tbl. No need to call
	 * mlx5_esw_chains_put_table()
	 */
	attr->prio = 0;
	attr->chain = 0;
	mlx5_eचयन_del_offloaded_rule(esw, sample_flow->rule, attr);
err_offload_rule:
	mlx5_esw_vporttbl_put(esw, &per_vport_tbl_attr);
err_शेष_tbl:
	वापस ERR_PTR(err);
पूर्ण

व्योम
mlx5_esw_sample_unoffload(काष्ठा mlx5_esw_psample *esw_psample,
			  काष्ठा mlx5_flow_handle *rule,
			  काष्ठा mlx5_flow_attr *attr)
अणु
	काष्ठा mlx5_esw_flow_attr *esw_attr = attr->esw_attr;
	काष्ठा mlx5_sample_flow *sample_flow;
	काष्ठा mlx5_vport_tbl_attr tbl_attr;
	काष्ठा mlx5_flow_attr *pre_attr;
	काष्ठा mlx5_eचयन *esw;

	अगर (IS_ERR_OR_शून्य(esw_psample))
		वापस;

	/* If slow path flag is set, sample action is not offloaded.
	 * No need to delete sample rule.
	 */
	esw = esw_psample->priv->mdev->priv.eचयन;
	अगर (attr->flags & MLX5_ESW_ATTR_FLAG_SLOW_PATH) अणु
		mlx5_eचयन_del_offloaded_rule(esw, rule, attr);
		वापस;
	पूर्ण

	sample_flow = esw_attr->sample->sample_flow;
	pre_attr = sample_flow->pre_attr;
	स_रखो(pre_attr, 0, माप(*pre_attr));
	esw = esw_psample->priv->mdev->priv.eचयन;
	mlx5_eचयन_del_offloaded_rule(esw, sample_flow->pre_rule, pre_attr);
	mlx5_eचयन_del_offloaded_rule(esw, sample_flow->rule, attr);

	sample_restore_put(esw_psample, sample_flow->restore);
	mapping_हटाओ(esw->offloads.reg_c0_obj_pool, esw_attr->sample->restore_obj_id);
	sampler_put(esw_psample, sample_flow->sampler);
	tbl_attr.chain = attr->chain;
	tbl_attr.prio = attr->prio;
	tbl_attr.vport = esw_attr->in_rep->vport;
	tbl_attr.vport_ns = &mlx5_esw_vport_tbl_sample_ns;
	mlx5_esw_vporttbl_put(esw, &tbl_attr);

	kमुक्त(pre_attr->esw_attr->sample);
	kमुक्त(pre_attr);
	kमुक्त(sample_flow);
पूर्ण

काष्ठा mlx5_esw_psample *
mlx5_esw_sample_init(काष्ठा mlx5e_priv *priv)
अणु
	काष्ठा mlx5_esw_psample *esw_psample;
	पूर्णांक err;

	esw_psample = kzalloc(माप(*esw_psample), GFP_KERNEL);
	अगर (!esw_psample)
		वापस ERR_PTR(-ENOMEM);
	esw_psample->priv = priv;
	err = sampler_termtbl_create(esw_psample);
	अगर (err)
		जाओ err_termtbl;

	mutex_init(&esw_psample->ht_lock);
	mutex_init(&esw_psample->restore_lock);

	वापस esw_psample;

err_termtbl:
	kमुक्त(esw_psample);
	वापस ERR_PTR(err);
पूर्ण

व्योम
mlx5_esw_sample_cleanup(काष्ठा mlx5_esw_psample *esw_psample)
अणु
	अगर (IS_ERR_OR_शून्य(esw_psample))
		वापस;

	mutex_destroy(&esw_psample->restore_lock);
	mutex_destroy(&esw_psample->ht_lock);
	sampler_termtbl_destroy(esw_psample);
	kमुक्त(esw_psample);
पूर्ण
