<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2017-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/slab.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/list.h>
#समावेश <linux/माला.स>
#समावेश <linux/rhashtable.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/mutex.h>
#समावेश <net/net_namespace.h>
#समावेश <net/tc_act/tc_vlan.h>

#समावेश "reg.h"
#समावेश "core.h"
#समावेश "resources.h"
#समावेश "spectrum.h"
#समावेश "core_acl_flex_keys.h"
#समावेश "core_acl_flex_actions.h"
#समावेश "spectrum_acl_tcam.h"

काष्ठा mlxsw_sp_acl अणु
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_afk *afk;
	काष्ठा mlxsw_sp_fid *dummy_fid;
	काष्ठा rhashtable ruleset_ht;
	काष्ठा list_head rules;
	काष्ठा mutex rules_lock; /* Protects rules list */
	काष्ठा अणु
		काष्ठा delayed_work dw;
		अचिन्हित दीर्घ पूर्णांकerval;	/* ms */
#घोषणा MLXSW_SP_ACL_RULE_ACTIVITY_UPDATE_PERIOD_MS 1000
	पूर्ण rule_activity_update;
	काष्ठा mlxsw_sp_acl_tcam tcam;
पूर्ण;

काष्ठा mlxsw_afk *mlxsw_sp_acl_afk(काष्ठा mlxsw_sp_acl *acl)
अणु
	वापस acl->afk;
पूर्ण

काष्ठा mlxsw_sp_acl_ruleset_ht_key अणु
	काष्ठा mlxsw_sp_flow_block *block;
	u32 chain_index;
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops;
पूर्ण;

काष्ठा mlxsw_sp_acl_ruleset अणु
	काष्ठा rhash_head ht_node; /* Member of acl HT */
	काष्ठा mlxsw_sp_acl_ruleset_ht_key ht_key;
	काष्ठा rhashtable rule_ht;
	अचिन्हित पूर्णांक ref_count;
	अचिन्हित पूर्णांक min_prio;
	अचिन्हित पूर्णांक max_prio;
	अचिन्हित दीर्घ priv[];
	/* priv has to be always the last item */
पूर्ण;

काष्ठा mlxsw_sp_acl_rule अणु
	काष्ठा rhash_head ht_node; /* Member of rule HT */
	काष्ठा list_head list;
	अचिन्हित दीर्घ cookie; /* HT key */
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	काष्ठा mlxsw_sp_acl_rule_info *rulei;
	u64 last_used;
	u64 last_packets;
	u64 last_bytes;
	u64 last_drops;
	अचिन्हित दीर्घ priv[];
	/* priv has to be always the last item */
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_acl_ruleset_ht_params = अणु
	.key_len = माप(काष्ठा mlxsw_sp_acl_ruleset_ht_key),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_acl_ruleset, ht_key),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_acl_ruleset, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

अटल स्थिर काष्ठा rhashtable_params mlxsw_sp_acl_rule_ht_params = अणु
	.key_len = माप(अचिन्हित दीर्घ),
	.key_offset = दुरत्व(काष्ठा mlxsw_sp_acl_rule, cookie),
	.head_offset = दुरत्व(काष्ठा mlxsw_sp_acl_rule, ht_node),
	.स्वतःmatic_shrinking = true,
पूर्ण;

काष्ठा mlxsw_sp_fid *mlxsw_sp_acl_dummy_fid(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	वापस mlxsw_sp->acl->dummy_fid;
पूर्ण

अटल bool
mlxsw_sp_acl_ruleset_is_singular(स्थिर काष्ठा mlxsw_sp_acl_ruleset *ruleset)
अणु
	/* We hold a reference on ruleset ourselves */
	वापस ruleset->ref_count == 2;
पूर्ण

पूर्णांक mlxsw_sp_acl_ruleset_bind(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_flow_block *block,
			      काष्ठा mlxsw_sp_flow_block_binding *binding)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset = block->ruleset_zero;
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;

	वापस ops->ruleset_bind(mlxsw_sp, ruleset->priv,
				 binding->mlxsw_sp_port, binding->ingress);
पूर्ण

व्योम mlxsw_sp_acl_ruleset_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_flow_block *block,
				 काष्ठा mlxsw_sp_flow_block_binding *binding)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset = block->ruleset_zero;
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;

	ops->ruleset_unbind(mlxsw_sp, ruleset->priv,
			    binding->mlxsw_sp_port, binding->ingress);
पूर्ण

अटल पूर्णांक
mlxsw_sp_acl_ruleset_block_bind(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_ruleset *ruleset,
				काष्ठा mlxsw_sp_flow_block *block)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;
	पूर्णांक err;

	block->ruleset_zero = ruleset;
	list_क्रम_each_entry(binding, &block->binding_list, list) अणु
		err = mlxsw_sp_acl_ruleset_bind(mlxsw_sp, block, binding);
		अगर (err)
			जाओ rollback;
	पूर्ण
	वापस 0;

rollback:
	list_क्रम_each_entry_जारी_reverse(binding, &block->binding_list,
					     list)
		mlxsw_sp_acl_ruleset_unbind(mlxsw_sp, block, binding);
	block->ruleset_zero = शून्य;

	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_acl_ruleset_block_unbind(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_ruleset *ruleset,
				  काष्ठा mlxsw_sp_flow_block *block)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;

	list_क्रम_each_entry(binding, &block->binding_list, list)
		mlxsw_sp_acl_ruleset_unbind(mlxsw_sp, block, binding);
	block->ruleset_zero = शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_acl_ruleset *
mlxsw_sp_acl_ruleset_create(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_flow_block *block, u32 chain_index,
			    स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops,
			    काष्ठा mlxsw_afk_element_usage *पंचांगplt_elusage)
अणु
	काष्ठा mlxsw_sp_acl *acl = mlxsw_sp->acl;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;
	माप_प्रकार alloc_size;
	पूर्णांक err;

	alloc_size = माप(*ruleset) + ops->ruleset_priv_size;
	ruleset = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!ruleset)
		वापस ERR_PTR(-ENOMEM);
	ruleset->ref_count = 1;
	ruleset->ht_key.block = block;
	ruleset->ht_key.chain_index = chain_index;
	ruleset->ht_key.ops = ops;

	err = rhashtable_init(&ruleset->rule_ht, &mlxsw_sp_acl_rule_ht_params);
	अगर (err)
		जाओ err_rhashtable_init;

	err = ops->ruleset_add(mlxsw_sp, &acl->tcam, ruleset->priv,
			       पंचांगplt_elusage, &ruleset->min_prio,
			       &ruleset->max_prio);
	अगर (err)
		जाओ err_ops_ruleset_add;

	err = rhashtable_insert_fast(&acl->ruleset_ht, &ruleset->ht_node,
				     mlxsw_sp_acl_ruleset_ht_params);
	अगर (err)
		जाओ err_ht_insert;

	वापस ruleset;

err_ht_insert:
	ops->ruleset_del(mlxsw_sp, ruleset->priv);
err_ops_ruleset_add:
	rhashtable_destroy(&ruleset->rule_ht);
err_rhashtable_init:
	kमुक्त(ruleset);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_acl_ruleset_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_acl_ruleset *ruleset)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	काष्ठा mlxsw_sp_acl *acl = mlxsw_sp->acl;

	rhashtable_हटाओ_fast(&acl->ruleset_ht, &ruleset->ht_node,
			       mlxsw_sp_acl_ruleset_ht_params);
	ops->ruleset_del(mlxsw_sp, ruleset->priv);
	rhashtable_destroy(&ruleset->rule_ht);
	kमुक्त(ruleset);
पूर्ण

अटल व्योम mlxsw_sp_acl_ruleset_ref_inc(काष्ठा mlxsw_sp_acl_ruleset *ruleset)
अणु
	ruleset->ref_count++;
पूर्ण

अटल व्योम mlxsw_sp_acl_ruleset_ref_dec(काष्ठा mlxsw_sp *mlxsw_sp,
					 काष्ठा mlxsw_sp_acl_ruleset *ruleset)
अणु
	अगर (--ruleset->ref_count)
		वापस;
	mlxsw_sp_acl_ruleset_destroy(mlxsw_sp, ruleset);
पूर्ण

अटल काष्ठा mlxsw_sp_acl_ruleset *
__mlxsw_sp_acl_ruleset_lookup(काष्ठा mlxsw_sp_acl *acl,
			      काष्ठा mlxsw_sp_flow_block *block, u32 chain_index,
			      स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops)
अणु
	काष्ठा mlxsw_sp_acl_ruleset_ht_key ht_key;

	स_रखो(&ht_key, 0, माप(ht_key));
	ht_key.block = block;
	ht_key.chain_index = chain_index;
	ht_key.ops = ops;
	वापस rhashtable_lookup_fast(&acl->ruleset_ht, &ht_key,
				      mlxsw_sp_acl_ruleset_ht_params);
पूर्ण

काष्ठा mlxsw_sp_acl_ruleset *
mlxsw_sp_acl_ruleset_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_flow_block *block, u32 chain_index,
			    क्रमागत mlxsw_sp_acl_profile profile)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops;
	काष्ठा mlxsw_sp_acl *acl = mlxsw_sp->acl;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;

	ops = mlxsw_sp_acl_tcam_profile_ops(mlxsw_sp, profile);
	अगर (!ops)
		वापस ERR_PTR(-EINVAL);
	ruleset = __mlxsw_sp_acl_ruleset_lookup(acl, block, chain_index, ops);
	अगर (!ruleset)
		वापस ERR_PTR(-ENOENT);
	वापस ruleset;
पूर्ण

काष्ठा mlxsw_sp_acl_ruleset *
mlxsw_sp_acl_ruleset_get(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा mlxsw_sp_flow_block *block, u32 chain_index,
			 क्रमागत mlxsw_sp_acl_profile profile,
			 काष्ठा mlxsw_afk_element_usage *पंचांगplt_elusage)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops;
	काष्ठा mlxsw_sp_acl *acl = mlxsw_sp->acl;
	काष्ठा mlxsw_sp_acl_ruleset *ruleset;

	ops = mlxsw_sp_acl_tcam_profile_ops(mlxsw_sp, profile);
	अगर (!ops)
		वापस ERR_PTR(-EINVAL);

	ruleset = __mlxsw_sp_acl_ruleset_lookup(acl, block, chain_index, ops);
	अगर (ruleset) अणु
		mlxsw_sp_acl_ruleset_ref_inc(ruleset);
		वापस ruleset;
	पूर्ण
	वापस mlxsw_sp_acl_ruleset_create(mlxsw_sp, block, chain_index, ops,
					   पंचांगplt_elusage);
पूर्ण

व्योम mlxsw_sp_acl_ruleset_put(काष्ठा mlxsw_sp *mlxsw_sp,
			      काष्ठा mlxsw_sp_acl_ruleset *ruleset)
अणु
	mlxsw_sp_acl_ruleset_ref_dec(mlxsw_sp, ruleset);
पूर्ण

u16 mlxsw_sp_acl_ruleset_group_id(काष्ठा mlxsw_sp_acl_ruleset *ruleset)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;

	वापस ops->ruleset_group_id(ruleset->priv);
पूर्ण

व्योम mlxsw_sp_acl_ruleset_prio_get(काष्ठा mlxsw_sp_acl_ruleset *ruleset,
				   अचिन्हित पूर्णांक *p_min_prio,
				   अचिन्हित पूर्णांक *p_max_prio)
अणु
	*p_min_prio = ruleset->min_prio;
	*p_max_prio = ruleset->max_prio;
पूर्ण

काष्ठा mlxsw_sp_acl_rule_info *
mlxsw_sp_acl_rulei_create(काष्ठा mlxsw_sp_acl *acl,
			  काष्ठा mlxsw_afa_block *afa_block)
अणु
	काष्ठा mlxsw_sp_acl_rule_info *rulei;
	पूर्णांक err;

	rulei = kzalloc(माप(*rulei), GFP_KERNEL);
	अगर (!rulei)
		वापस ERR_PTR(-ENOMEM);

	अगर (afa_block) अणु
		rulei->act_block = afa_block;
		वापस rulei;
	पूर्ण

	rulei->act_block = mlxsw_afa_block_create(acl->mlxsw_sp->afa);
	अगर (IS_ERR(rulei->act_block)) अणु
		err = PTR_ERR(rulei->act_block);
		जाओ err_afa_block_create;
	पूर्ण
	rulei->action_created = 1;
	वापस rulei;

err_afa_block_create:
	kमुक्त(rulei);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxsw_sp_acl_rulei_destroy(काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	अगर (rulei->action_created)
		mlxsw_afa_block_destroy(rulei->act_block);
	kमुक्त(rulei);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_commit(काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	वापस mlxsw_afa_block_commit(rulei->act_block);
पूर्ण

व्योम mlxsw_sp_acl_rulei_priority(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				 अचिन्हित पूर्णांक priority)
अणु
	rulei->priority = priority;
पूर्ण

व्योम mlxsw_sp_acl_rulei_keymask_u32(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				    क्रमागत mlxsw_afk_element element,
				    u32 key_value, u32 mask_value)
अणु
	mlxsw_afk_values_add_u32(&rulei->values, element,
				 key_value, mask_value);
पूर्ण

व्योम mlxsw_sp_acl_rulei_keymask_buf(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				    क्रमागत mlxsw_afk_element element,
				    स्थिर अक्षर *key_value,
				    स्थिर अक्षर *mask_value, अचिन्हित पूर्णांक len)
अणु
	mlxsw_afk_values_add_buf(&rulei->values, element,
				 key_value, mask_value, len);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_जारी(काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	वापस mlxsw_afa_block_जारी(rulei->act_block);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_jump(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				u16 group_id)
अणु
	वापस mlxsw_afa_block_jump(rulei->act_block, group_id);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_terminate(काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	वापस mlxsw_afa_block_terminate(rulei->act_block);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_drop(काष्ठा mlxsw_sp_acl_rule_info *rulei,
				bool ingress,
				स्थिर काष्ठा flow_action_cookie *fa_cookie,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस mlxsw_afa_block_append_drop(rulei->act_block, ingress,
					   fa_cookie, extack);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_trap(काष्ठा mlxsw_sp_acl_rule_info *rulei)
अणु
	वापस mlxsw_afa_block_append_trap(rulei->act_block,
					   MLXSW_TRAP_ID_ACL0);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_fwd(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_rule_info *rulei,
			       काष्ठा net_device *out_dev,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	u8 local_port;
	bool in_port;

	अगर (out_dev) अणु
		अगर (!mlxsw_sp_port_dev_check(out_dev)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid output device");
			वापस -EINVAL;
		पूर्ण
		mlxsw_sp_port = netdev_priv(out_dev);
		अगर (mlxsw_sp_port->mlxsw_sp != mlxsw_sp) अणु
			NL_SET_ERR_MSG_MOD(extack, "Invalid output device");
			वापस -EINVAL;
		पूर्ण
		local_port = mlxsw_sp_port->local_port;
		in_port = false;
	पूर्ण अन्यथा अणु
		/* If out_dev is शून्य, the caller wants to
		 * set क्रमward to ingress port.
		 */
		local_port = 0;
		in_port = true;
	पूर्ण
	वापस mlxsw_afa_block_append_fwd(rulei->act_block,
					  local_port, in_port, extack);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_mirror(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei,
				  काष्ठा mlxsw_sp_flow_block *block,
				  काष्ठा net_device *out_dev,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;
	काष्ठा mlxsw_sp_port *in_port;

	अगर (!list_is_singular(&block->binding_list)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Only a single mirror source is allowed");
		वापस -EOPNOTSUPP;
	पूर्ण
	binding = list_first_entry(&block->binding_list,
				   काष्ठा mlxsw_sp_flow_block_binding, list);
	in_port = binding->mlxsw_sp_port;

	वापस mlxsw_afa_block_append_mirror(rulei->act_block,
					     in_port->local_port,
					     out_dev,
					     binding->ingress,
					     extack);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_vlan(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_rule_info *rulei,
				u32 action, u16 vid, u16 proto, u8 prio,
				काष्ठा netlink_ext_ack *extack)
अणु
	u8 ethertype;

	अगर (action == FLOW_ACTION_VLAN_MANGLE) अणु
		चयन (proto) अणु
		हाल ETH_P_8021Q:
			ethertype = 0;
			अवरोध;
		हाल ETH_P_8021AD:
			ethertype = 1;
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_MOD(extack, "Unsupported VLAN protocol");
			dev_err(mlxsw_sp->bus_info->dev, "Unsupported VLAN protocol %#04x\n",
				proto);
			वापस -EINVAL;
		पूर्ण

		वापस mlxsw_afa_block_append_vlan_modअगरy(rulei->act_block,
							  vid, prio, ethertype,
							  extack);
	पूर्ण अन्यथा अणु
		NL_SET_ERR_MSG_MOD(extack, "Unsupported VLAN action");
		dev_err(mlxsw_sp->bus_info->dev, "Unsupported VLAN action\n");
		वापस -EINVAL;
	पूर्ण
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_priority(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_acl_rule_info *rulei,
				    u32 prio, काष्ठा netlink_ext_ack *extack)
अणु
	/* Even though both Linux and Spectrum चयनes support 16 priorities,
	 * spectrum_qdisc only processes the first eight priomap elements, and
	 * the DCB and PFC features are tied to 8 priorities as well. Thereक्रमe
	 * bounce attempts to prioritize packets to higher priorities.
	 */
	अगर (prio >= IEEE_8021QAZ_MAX_TCS) अणु
		NL_SET_ERR_MSG_MOD(extack, "Only priorities 0..7 are supported");
		वापस -EINVAL;
	पूर्ण
	वापस mlxsw_afa_block_append_qos_चयन_prio(rulei->act_block, prio,
						      extack);
पूर्ण

क्रमागत mlxsw_sp_acl_mangle_field अणु
	MLXSW_SP_ACL_MANGLE_FIELD_IP_DSFIELD,
	MLXSW_SP_ACL_MANGLE_FIELD_IP_DSCP,
	MLXSW_SP_ACL_MANGLE_FIELD_IP_ECN,
	MLXSW_SP_ACL_MANGLE_FIELD_IP_SPORT,
	MLXSW_SP_ACL_MANGLE_FIELD_IP_DPORT,
पूर्ण;

काष्ठा mlxsw_sp_acl_mangle_action अणु
	क्रमागत flow_action_mangle_base htype;
	/* Offset is u32-aligned. */
	u32 offset;
	/* Mask bits are unset क्रम the modअगरied field. */
	u32 mask;
	/* Shअगरt required to extract the set value. */
	u32 shअगरt;
	क्रमागत mlxsw_sp_acl_mangle_field field;
पूर्ण;

#घोषणा MLXSW_SP_ACL_MANGLE_ACTION(_htype, _offset, _mask, _shअगरt, _field) \
	अणु								\
		.htype = _htype,					\
		.offset = _offset,					\
		.mask = _mask,						\
		.shअगरt = _shअगरt,					\
		.field = MLXSW_SP_ACL_MANGLE_FIELD_##_field,		\
	पूर्ण

#घोषणा MLXSW_SP_ACL_MANGLE_ACTION_IP4(_offset, _mask, _shअगरt, _field) \
	MLXSW_SP_ACL_MANGLE_ACTION(FLOW_ACT_MANGLE_HDR_TYPE_IP4,       \
				   _offset, _mask, _shअगरt, _field)

#घोषणा MLXSW_SP_ACL_MANGLE_ACTION_IP6(_offset, _mask, _shअगरt, _field) \
	MLXSW_SP_ACL_MANGLE_ACTION(FLOW_ACT_MANGLE_HDR_TYPE_IP6,       \
				   _offset, _mask, _shअगरt, _field)

#घोषणा MLXSW_SP_ACL_MANGLE_ACTION_TCP(_offset, _mask, _shअगरt, _field) \
	MLXSW_SP_ACL_MANGLE_ACTION(FLOW_ACT_MANGLE_HDR_TYPE_TCP, _offset, _mask, _shअगरt, _field)

#घोषणा MLXSW_SP_ACL_MANGLE_ACTION_UDP(_offset, _mask, _shअगरt, _field) \
	MLXSW_SP_ACL_MANGLE_ACTION(FLOW_ACT_MANGLE_HDR_TYPE_UDP, _offset, _mask, _shअगरt, _field)

अटल काष्ठा mlxsw_sp_acl_mangle_action mlxsw_sp_acl_mangle_actions[] = अणु
	MLXSW_SP_ACL_MANGLE_ACTION_IP4(0, 0xff00ffff, 16, IP_DSFIELD),
	MLXSW_SP_ACL_MANGLE_ACTION_IP4(0, 0xff03ffff, 18, IP_DSCP),
	MLXSW_SP_ACL_MANGLE_ACTION_IP4(0, 0xfffcffff, 16, IP_ECN),

	MLXSW_SP_ACL_MANGLE_ACTION_IP6(0, 0xf00fffff, 20, IP_DSFIELD),
	MLXSW_SP_ACL_MANGLE_ACTION_IP6(0, 0xf03fffff, 22, IP_DSCP),
	MLXSW_SP_ACL_MANGLE_ACTION_IP6(0, 0xffcfffff, 20, IP_ECN),

	MLXSW_SP_ACL_MANGLE_ACTION_TCP(0, 0x0000ffff, 16, IP_SPORT),
	MLXSW_SP_ACL_MANGLE_ACTION_TCP(0, 0xffff0000, 0,  IP_DPORT),

	MLXSW_SP_ACL_MANGLE_ACTION_UDP(0, 0x0000ffff, 16, IP_SPORT),
	MLXSW_SP_ACL_MANGLE_ACTION_UDP(0, 0xffff0000, 0,  IP_DPORT),
पूर्ण;

अटल पूर्णांक
mlxsw_sp_acl_rulei_act_mangle_field(काष्ठा mlxsw_sp *mlxsw_sp,
				    काष्ठा mlxsw_sp_acl_rule_info *rulei,
				    काष्ठा mlxsw_sp_acl_mangle_action *mact,
				    u32 val, काष्ठा netlink_ext_ack *extack)
अणु
	चयन (mact->field) अणु
	हाल MLXSW_SP_ACL_MANGLE_FIELD_IP_DSFIELD:
		वापस mlxsw_afa_block_append_qos_dsfield(rulei->act_block,
							  val, extack);
	हाल MLXSW_SP_ACL_MANGLE_FIELD_IP_DSCP:
		वापस mlxsw_afa_block_append_qos_dscp(rulei->act_block,
						       val, extack);
	हाल MLXSW_SP_ACL_MANGLE_FIELD_IP_ECN:
		वापस mlxsw_afa_block_append_qos_ecn(rulei->act_block,
						      val, extack);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp1_acl_rulei_act_mangle_field(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_acl_rule_info *rulei,
						काष्ठा mlxsw_sp_acl_mangle_action *mact,
						u32 val, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = mlxsw_sp_acl_rulei_act_mangle_field(mlxsw_sp, rulei, mact, val, extack);
	अगर (err != -EOPNOTSUPP)
		वापस err;

	NL_SET_ERR_MSG_MOD(extack, "Unsupported mangle field");
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp2_acl_rulei_act_mangle_field(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा mlxsw_sp_acl_rule_info *rulei,
						काष्ठा mlxsw_sp_acl_mangle_action *mact,
						u32 val, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = mlxsw_sp_acl_rulei_act_mangle_field(mlxsw_sp, rulei, mact, val, extack);
	अगर (err != -EOPNOTSUPP)
		वापस err;

	चयन (mact->field) अणु
	हाल MLXSW_SP_ACL_MANGLE_FIELD_IP_SPORT:
		वापस mlxsw_afa_block_append_l4port(rulei->act_block, false, val, extack);
	हाल MLXSW_SP_ACL_MANGLE_FIELD_IP_DPORT:
		वापस mlxsw_afa_block_append_l4port(rulei->act_block, true, val, extack);
	शेष:
		अवरोध;
	पूर्ण

	NL_SET_ERR_MSG_MOD(extack, "Unsupported mangle field");
	वापस err;
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_mangle(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei,
				  क्रमागत flow_action_mangle_base htype,
				  u32 offset, u32 mask, u32 val,
				  काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_rulei_ops *acl_rulei_ops = mlxsw_sp->acl_rulei_ops;
	काष्ठा mlxsw_sp_acl_mangle_action *mact;
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(mlxsw_sp_acl_mangle_actions); ++i) अणु
		mact = &mlxsw_sp_acl_mangle_actions[i];
		अगर (mact->htype == htype &&
		    mact->offset == offset &&
		    mact->mask == mask) अणु
			val >>= mact->shअगरt;
			वापस acl_rulei_ops->act_mangle_field(mlxsw_sp,
							       rulei, mact,
							       val, extack);
		पूर्ण
	पूर्ण

	NL_SET_ERR_MSG_MOD(extack, "Unknown mangle field");
	वापस -EINVAL;
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_police(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei,
				  u32 index, u64 rate_bytes_ps,
				  u32 burst, काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = mlxsw_afa_block_append_police(rulei->act_block, index,
					    rate_bytes_ps, burst,
					    &rulei->policer_index, extack);
	अगर (err)
		वापस err;

	rulei->policer_index_valid = true;

	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_count(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_acl_rule_info *rulei,
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = mlxsw_afa_block_append_counter(rulei->act_block,
					     &rulei->counter_index, extack);
	अगर (err)
		वापस err;
	rulei->counter_valid = true;
	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_fid_set(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_acl_rule_info *rulei,
				   u16 fid, काष्ठा netlink_ext_ack *extack)
अणु
	वापस mlxsw_afa_block_append_fid_set(rulei->act_block, fid, extack);
पूर्ण

पूर्णांक mlxsw_sp_acl_rulei_act_sample(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_acl_rule_info *rulei,
				  काष्ठा mlxsw_sp_flow_block *block,
				  काष्ठा psample_group *psample_group, u32 rate,
				  u32 trunc_size, bool truncate,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_flow_block_binding *binding;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;

	अगर (!list_is_singular(&block->binding_list)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Only a single sampling source is allowed");
		वापस -EOPNOTSUPP;
	पूर्ण
	binding = list_first_entry(&block->binding_list,
				   काष्ठा mlxsw_sp_flow_block_binding, list);
	mlxsw_sp_port = binding->mlxsw_sp_port;

	वापस mlxsw_afa_block_append_sampler(rulei->act_block,
					      mlxsw_sp_port->local_port,
					      psample_group, rate, trunc_size,
					      truncate, binding->ingress,
					      extack);
पूर्ण

काष्ठा mlxsw_sp_acl_rule *
mlxsw_sp_acl_rule_create(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा mlxsw_sp_acl_ruleset *ruleset,
			 अचिन्हित दीर्घ cookie,
			 काष्ठा mlxsw_afa_block *afa_block,
			 काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	काष्ठा mlxsw_sp_acl_rule *rule;
	पूर्णांक err;

	mlxsw_sp_acl_ruleset_ref_inc(ruleset);
	rule = kzalloc(माप(*rule) + ops->rule_priv_size,
		       GFP_KERNEL);
	अगर (!rule) अणु
		err = -ENOMEM;
		जाओ err_alloc;
	पूर्ण
	rule->cookie = cookie;
	rule->ruleset = ruleset;

	rule->rulei = mlxsw_sp_acl_rulei_create(mlxsw_sp->acl, afa_block);
	अगर (IS_ERR(rule->rulei)) अणु
		err = PTR_ERR(rule->rulei);
		जाओ err_rulei_create;
	पूर्ण

	वापस rule;

err_rulei_create:
	kमुक्त(rule);
err_alloc:
	mlxsw_sp_acl_ruleset_ref_dec(mlxsw_sp, ruleset);
	वापस ERR_PTR(err);
पूर्ण

व्योम mlxsw_sp_acl_rule_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_acl_rule *rule)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;

	mlxsw_sp_acl_rulei_destroy(rule->rulei);
	kमुक्त(rule);
	mlxsw_sp_acl_ruleset_ref_dec(mlxsw_sp, ruleset);
पूर्ण

पूर्णांक mlxsw_sp_acl_rule_add(काष्ठा mlxsw_sp *mlxsw_sp,
			  काष्ठा mlxsw_sp_acl_rule *rule)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	काष्ठा mlxsw_sp_flow_block *block = ruleset->ht_key.block;
	पूर्णांक err;

	err = ops->rule_add(mlxsw_sp, ruleset->priv, rule->priv, rule->rulei);
	अगर (err)
		वापस err;

	err = rhashtable_insert_fast(&ruleset->rule_ht, &rule->ht_node,
				     mlxsw_sp_acl_rule_ht_params);
	अगर (err)
		जाओ err_rhashtable_insert;

	अगर (!ruleset->ht_key.chain_index &&
	    mlxsw_sp_acl_ruleset_is_singular(ruleset)) अणु
		/* We only need ruleset with chain index 0, the implicit
		 * one, to be directly bound to device. The rest of the
		 * rulesets are bound by "Goto action set".
		 */
		err = mlxsw_sp_acl_ruleset_block_bind(mlxsw_sp, ruleset, block);
		अगर (err)
			जाओ err_ruleset_block_bind;
	पूर्ण

	mutex_lock(&mlxsw_sp->acl->rules_lock);
	list_add_tail(&rule->list, &mlxsw_sp->acl->rules);
	mutex_unlock(&mlxsw_sp->acl->rules_lock);
	block->rule_count++;
	block->ingress_blocker_rule_count += rule->rulei->ingress_bind_blocker;
	block->egress_blocker_rule_count += rule->rulei->egress_bind_blocker;
	वापस 0;

err_ruleset_block_bind:
	rhashtable_हटाओ_fast(&ruleset->rule_ht, &rule->ht_node,
			       mlxsw_sp_acl_rule_ht_params);
err_rhashtable_insert:
	ops->rule_del(mlxsw_sp, rule->priv);
	वापस err;
पूर्ण

व्योम mlxsw_sp_acl_rule_del(काष्ठा mlxsw_sp *mlxsw_sp,
			   काष्ठा mlxsw_sp_acl_rule *rule)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	काष्ठा mlxsw_sp_flow_block *block = ruleset->ht_key.block;

	block->egress_blocker_rule_count -= rule->rulei->egress_bind_blocker;
	block->ingress_blocker_rule_count -= rule->rulei->ingress_bind_blocker;
	block->rule_count--;
	mutex_lock(&mlxsw_sp->acl->rules_lock);
	list_del(&rule->list);
	mutex_unlock(&mlxsw_sp->acl->rules_lock);
	अगर (!ruleset->ht_key.chain_index &&
	    mlxsw_sp_acl_ruleset_is_singular(ruleset))
		mlxsw_sp_acl_ruleset_block_unbind(mlxsw_sp, ruleset, block);
	rhashtable_हटाओ_fast(&ruleset->rule_ht, &rule->ht_node,
			       mlxsw_sp_acl_rule_ht_params);
	ops->rule_del(mlxsw_sp, rule->priv);
पूर्ण

पूर्णांक mlxsw_sp_acl_rule_action_replace(काष्ठा mlxsw_sp *mlxsw_sp,
				     काष्ठा mlxsw_sp_acl_rule *rule,
				     काष्ठा mlxsw_afa_block *afa_block)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	काष्ठा mlxsw_sp_acl_rule_info *rulei;

	rulei = mlxsw_sp_acl_rule_rulei(rule);
	rulei->act_block = afa_block;

	वापस ops->rule_action_replace(mlxsw_sp, rule->priv, rule->rulei);
पूर्ण

काष्ठा mlxsw_sp_acl_rule *
mlxsw_sp_acl_rule_lookup(काष्ठा mlxsw_sp *mlxsw_sp,
			 काष्ठा mlxsw_sp_acl_ruleset *ruleset,
			 अचिन्हित दीर्घ cookie)
अणु
	वापस rhashtable_lookup_fast(&ruleset->rule_ht, &cookie,
				       mlxsw_sp_acl_rule_ht_params);
पूर्ण

काष्ठा mlxsw_sp_acl_rule_info *
mlxsw_sp_acl_rule_rulei(काष्ठा mlxsw_sp_acl_rule *rule)
अणु
	वापस rule->rulei;
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_rule_activity_update(काष्ठा mlxsw_sp *mlxsw_sp,
					     काष्ठा mlxsw_sp_acl_rule *rule)
अणु
	काष्ठा mlxsw_sp_acl_ruleset *ruleset = rule->ruleset;
	स्थिर काष्ठा mlxsw_sp_acl_profile_ops *ops = ruleset->ht_key.ops;
	bool active;
	पूर्णांक err;

	err = ops->rule_activity_get(mlxsw_sp, rule->priv, &active);
	अगर (err)
		वापस err;
	अगर (active)
		rule->last_used = jअगरfies;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_acl_rules_activity_update(काष्ठा mlxsw_sp_acl *acl)
अणु
	काष्ठा mlxsw_sp_acl_rule *rule;
	पूर्णांक err;

	mutex_lock(&acl->rules_lock);
	list_क्रम_each_entry(rule, &acl->rules, list) अणु
		err = mlxsw_sp_acl_rule_activity_update(acl->mlxsw_sp,
							rule);
		अगर (err)
			जाओ err_rule_update;
	पूर्ण
	mutex_unlock(&acl->rules_lock);
	वापस 0;

err_rule_update:
	mutex_unlock(&acl->rules_lock);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_acl_rule_activity_work_schedule(काष्ठा mlxsw_sp_acl *acl)
अणु
	अचिन्हित दीर्घ पूर्णांकerval = acl->rule_activity_update.पूर्णांकerval;

	mlxsw_core_schedule_dw(&acl->rule_activity_update.dw,
			       msecs_to_jअगरfies(पूर्णांकerval));
पूर्ण

अटल व्योम mlxsw_sp_acl_rule_activity_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_acl *acl = container_of(work, काष्ठा mlxsw_sp_acl,
						rule_activity_update.dw.work);
	पूर्णांक err;

	err = mlxsw_sp_acl_rules_activity_update(acl);
	अगर (err)
		dev_err(acl->mlxsw_sp->bus_info->dev, "Could not update acl activity");

	mlxsw_sp_acl_rule_activity_work_schedule(acl);
पूर्ण

पूर्णांक mlxsw_sp_acl_rule_get_stats(काष्ठा mlxsw_sp *mlxsw_sp,
				काष्ठा mlxsw_sp_acl_rule *rule,
				u64 *packets, u64 *bytes, u64 *drops,
				u64 *last_use,
				क्रमागत flow_action_hw_stats *used_hw_stats)

अणु
	क्रमागत mlxsw_sp_policer_type type = MLXSW_SP_POLICER_TYPE_SINGLE_RATE;
	काष्ठा mlxsw_sp_acl_rule_info *rulei;
	u64 current_packets = 0;
	u64 current_bytes = 0;
	u64 current_drops = 0;
	पूर्णांक err;

	rulei = mlxsw_sp_acl_rule_rulei(rule);
	अगर (rulei->counter_valid) अणु
		err = mlxsw_sp_flow_counter_get(mlxsw_sp, rulei->counter_index,
						&current_packets,
						&current_bytes);
		अगर (err)
			वापस err;
		*used_hw_stats = FLOW_ACTION_HW_STATS_IMMEDIATE;
	पूर्ण
	अगर (rulei->policer_index_valid) अणु
		err = mlxsw_sp_policer_drops_counter_get(mlxsw_sp, type,
							 rulei->policer_index,
							 &current_drops);
		अगर (err)
			वापस err;
	पूर्ण
	*packets = current_packets - rule->last_packets;
	*bytes = current_bytes - rule->last_bytes;
	*drops = current_drops - rule->last_drops;
	*last_use = rule->last_used;

	rule->last_bytes = current_bytes;
	rule->last_packets = current_packets;
	rule->last_drops = current_drops;

	वापस 0;
पूर्ण

पूर्णांक mlxsw_sp_acl_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_fid *fid;
	काष्ठा mlxsw_sp_acl *acl;
	माप_प्रकार alloc_size;
	पूर्णांक err;

	alloc_size = माप(*acl) + mlxsw_sp_acl_tcam_priv_size(mlxsw_sp);
	acl = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!acl)
		वापस -ENOMEM;
	mlxsw_sp->acl = acl;
	acl->mlxsw_sp = mlxsw_sp;
	acl->afk = mlxsw_afk_create(MLXSW_CORE_RES_GET(mlxsw_sp->core,
						       ACL_FLEX_KEYS),
				    mlxsw_sp->afk_ops);
	अगर (!acl->afk) अणु
		err = -ENOMEM;
		जाओ err_afk_create;
	पूर्ण

	err = rhashtable_init(&acl->ruleset_ht,
			      &mlxsw_sp_acl_ruleset_ht_params);
	अगर (err)
		जाओ err_rhashtable_init;

	fid = mlxsw_sp_fid_dummy_get(mlxsw_sp);
	अगर (IS_ERR(fid)) अणु
		err = PTR_ERR(fid);
		जाओ err_fid_get;
	पूर्ण
	acl->dummy_fid = fid;

	INIT_LIST_HEAD(&acl->rules);
	mutex_init(&acl->rules_lock);
	err = mlxsw_sp_acl_tcam_init(mlxsw_sp, &acl->tcam);
	अगर (err)
		जाओ err_acl_ops_init;

	/* Create the delayed work क्रम the rule activity_update */
	INIT_DELAYED_WORK(&acl->rule_activity_update.dw,
			  mlxsw_sp_acl_rule_activity_update_work);
	acl->rule_activity_update.पूर्णांकerval = MLXSW_SP_ACL_RULE_ACTIVITY_UPDATE_PERIOD_MS;
	mlxsw_core_schedule_dw(&acl->rule_activity_update.dw, 0);
	वापस 0;

err_acl_ops_init:
	mutex_destroy(&acl->rules_lock);
	mlxsw_sp_fid_put(fid);
err_fid_get:
	rhashtable_destroy(&acl->ruleset_ht);
err_rhashtable_init:
	mlxsw_afk_destroy(acl->afk);
err_afk_create:
	kमुक्त(acl);
	वापस err;
पूर्ण

व्योम mlxsw_sp_acl_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_acl *acl = mlxsw_sp->acl;

	cancel_delayed_work_sync(&mlxsw_sp->acl->rule_activity_update.dw);
	mlxsw_sp_acl_tcam_fini(mlxsw_sp, &acl->tcam);
	mutex_destroy(&acl->rules_lock);
	WARN_ON(!list_empty(&acl->rules));
	mlxsw_sp_fid_put(acl->dummy_fid);
	rhashtable_destroy(&acl->ruleset_ht);
	mlxsw_afk_destroy(acl->afk);
	kमुक्त(acl);
पूर्ण

u32 mlxsw_sp_acl_region_rehash_पूर्णांकrvl_get(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_acl *acl = mlxsw_sp->acl;

	वापस mlxsw_sp_acl_tcam_vregion_rehash_पूर्णांकrvl_get(mlxsw_sp,
							   &acl->tcam);
पूर्ण

पूर्णांक mlxsw_sp_acl_region_rehash_पूर्णांकrvl_set(काष्ठा mlxsw_sp *mlxsw_sp, u32 val)
अणु
	काष्ठा mlxsw_sp_acl *acl = mlxsw_sp->acl;

	वापस mlxsw_sp_acl_tcam_vregion_rehash_पूर्णांकrvl_set(mlxsw_sp,
							   &acl->tcam, val);
पूर्ण

काष्ठा mlxsw_sp_acl_rulei_ops mlxsw_sp1_acl_rulei_ops = अणु
	.act_mangle_field = mlxsw_sp1_acl_rulei_act_mangle_field,
पूर्ण;

काष्ठा mlxsw_sp_acl_rulei_ops mlxsw_sp2_acl_rulei_ops = अणु
	.act_mangle_field = mlxsw_sp2_acl_rulei_act_mangle_field,
पूर्ण;
