<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Inc. All rights reserved. */

#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "helper.h"
#समावेश "ofld.h"

अटल bool
esw_acl_ingress_prio_tag_enabled(काष्ठा mlx5_eचयन *esw,
				 स्थिर काष्ठा mlx5_vport *vport)
अणु
	वापस (MLX5_CAP_GEN(esw->dev, prio_tag_required) &&
		mlx5_eचयन_is_vf_vport(esw, vport->vport));
पूर्ण

अटल पूर्णांक esw_acl_ingress_prio_tag_create(काष्ठा mlx5_eचयन *esw,
					   काष्ठा mlx5_vport *vport)
अणु
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;

	/* For prio tag mode, there is only 1 FTEs:
	 * 1) Untagged packets - push prio tag VLAN and modअगरy metadata अगर
	 * required, allow
	 * Unmatched traffic is allowed by शेष
	 */
	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	/* Untagged packets - push prio tag VLAN, allow */
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.cvlan_tag);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.cvlan_tag, 0);
	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_VLAN_PUSH |
			  MLX5_FLOW_CONTEXT_ACTION_ALLOW;
	flow_act.vlan[0].ethtype = ETH_P_8021Q;
	flow_act.vlan[0].vid = 0;
	flow_act.vlan[0].prio = 0;

	अगर (vport->ingress.offloads.modअगरy_metadata_rule) अणु
		flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_MOD_HDR;
		flow_act.modअगरy_hdr = vport->ingress.offloads.modअगरy_metadata;
	पूर्ण

	vport->ingress.allow_rule = mlx5_add_flow_rules(vport->ingress.acl, spec,
							&flow_act, शून्य, 0);
	अगर (IS_ERR(vport->ingress.allow_rule)) अणु
		err = PTR_ERR(vport->ingress.allow_rule);
		esw_warn(esw->dev,
			 "vport[%d] configure ingress untagged allow rule, err(%d)\n",
			 vport->vport, err);
		vport->ingress.allow_rule = शून्य;
	पूर्ण

	kvमुक्त(spec);
	वापस err;
पूर्ण

अटल पूर्णांक esw_acl_ingress_mod_metadata_create(काष्ठा mlx5_eचयन *esw,
					       काष्ठा mlx5_vport *vport)
अणु
	u8 action[MLX5_UN_SZ_BYTES(set_add_copy_action_in_स्वतः)] = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	पूर्णांक err = 0;
	u32 key;

	key = mlx5_eचयन_get_vport_metadata_क्रम_match(esw, vport->vport);
	key >>= ESW_SOURCE_PORT_METADATA_OFFSET;

	MLX5_SET(set_action_in, action, action_type, MLX5_ACTION_TYPE_SET);
	MLX5_SET(set_action_in, action, field,
		 MLX5_ACTION_IN_FIELD_METADATA_REG_C_0);
	MLX5_SET(set_action_in, action, data, key);
	MLX5_SET(set_action_in, action, offset,
		 ESW_SOURCE_PORT_METADATA_OFFSET);
	MLX5_SET(set_action_in, action, length,
		 ESW_SOURCE_PORT_METADATA_BITS);

	vport->ingress.offloads.modअगरy_metadata =
		mlx5_modअगरy_header_alloc(esw->dev, MLX5_FLOW_NAMESPACE_ESW_INGRESS,
					 1, action);
	अगर (IS_ERR(vport->ingress.offloads.modअगरy_metadata)) अणु
		err = PTR_ERR(vport->ingress.offloads.modअगरy_metadata);
		esw_warn(esw->dev,
			 "failed to alloc modify header for vport %d ingress acl (%d)\n",
			 vport->vport, err);
		वापस err;
	पूर्ण

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_MOD_HDR | MLX5_FLOW_CONTEXT_ACTION_ALLOW;
	flow_act.modअगरy_hdr = vport->ingress.offloads.modअगरy_metadata;
	vport->ingress.offloads.modअगरy_metadata_rule =
				mlx5_add_flow_rules(vport->ingress.acl,
						    शून्य, &flow_act, शून्य, 0);
	अगर (IS_ERR(vport->ingress.offloads.modअगरy_metadata_rule)) अणु
		err = PTR_ERR(vport->ingress.offloads.modअगरy_metadata_rule);
		esw_warn(esw->dev,
			 "failed to add setting metadata rule for vport %d ingress acl, err(%d)\n",
			 vport->vport, err);
		mlx5_modअगरy_header_dealloc(esw->dev, vport->ingress.offloads.modअगरy_metadata);
		vport->ingress.offloads.modअगरy_metadata_rule = शून्य;
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम esw_acl_ingress_mod_metadata_destroy(काष्ठा mlx5_eचयन *esw,
						 काष्ठा mlx5_vport *vport)
अणु
	अगर (!vport->ingress.offloads.modअगरy_metadata_rule)
		वापस;

	mlx5_del_flow_rules(vport->ingress.offloads.modअगरy_metadata_rule);
	mlx5_modअगरy_header_dealloc(esw->dev, vport->ingress.offloads.modअगरy_metadata);
	vport->ingress.offloads.modअगरy_metadata_rule = शून्य;
पूर्ण

अटल पूर्णांक esw_acl_ingress_ofld_rules_create(काष्ठा mlx5_eचयन *esw,
					     काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक err;

	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		err = esw_acl_ingress_mod_metadata_create(esw, vport);
		अगर (err) अणु
			esw_warn(esw->dev,
				 "vport(%d) create ingress modify metadata, err(%d)\n",
				 vport->vport, err);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (esw_acl_ingress_prio_tag_enabled(esw, vport)) अणु
		err = esw_acl_ingress_prio_tag_create(esw, vport);
		अगर (err) अणु
			esw_warn(esw->dev,
				 "vport(%d) create ingress prio tag rule, err(%d)\n",
				 vport->vport, err);
			जाओ prio_tag_err;
		पूर्ण
	पूर्ण

	वापस 0;

prio_tag_err:
	esw_acl_ingress_mod_metadata_destroy(esw, vport);
	वापस err;
पूर्ण

अटल व्योम esw_acl_ingress_ofld_rules_destroy(काष्ठा mlx5_eचयन *esw,
					       काष्ठा mlx5_vport *vport)
अणु
	esw_acl_ingress_allow_rule_destroy(vport);
	esw_acl_ingress_mod_metadata_destroy(esw, vport);
पूर्ण

अटल पूर्णांक esw_acl_ingress_ofld_groups_create(काष्ठा mlx5_eचयन *esw,
					      काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_group *g;
	व्योम *match_criteria;
	u32 *flow_group_in;
	u32 flow_index = 0;
	पूर्णांक ret = 0;

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in)
		वापस -ENOMEM;

	अगर (esw_acl_ingress_prio_tag_enabled(esw, vport)) अणु
		/* This group is to hold FTE to match untagged packets when prio_tag
		 * is enabled.
		 */
		match_criteria = MLX5_ADDR_OF(create_flow_group_in,
					      flow_group_in, match_criteria);
		MLX5_SET(create_flow_group_in, flow_group_in,
			 match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
		MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.cvlan_tag);
		MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, flow_index);
		MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, flow_index);

		g = mlx5_create_flow_group(vport->ingress.acl, flow_group_in);
		अगर (IS_ERR(g)) अणु
			ret = PTR_ERR(g);
			esw_warn(esw->dev, "vport[%d] ingress create untagged flow group, err(%d)\n",
				 vport->vport, ret);
			जाओ prio_tag_err;
		पूर्ण
		vport->ingress.offloads.metadata_prio_tag_grp = g;
		flow_index++;
	पूर्ण

	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw)) अणु
		/* This group holds an FTE with no match to add metadata क्रम
		 * tagged packets अगर prio-tag is enabled, or क्रम all untagged
		 * traffic in हाल prio-tag is disabled.
		 */
		स_रखो(flow_group_in, 0, inlen);
		MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, flow_index);
		MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, flow_index);

		g = mlx5_create_flow_group(vport->ingress.acl, flow_group_in);
		अगर (IS_ERR(g)) अणु
			ret = PTR_ERR(g);
			esw_warn(esw->dev, "vport[%d] ingress create drop flow group, err(%d)\n",
				 vport->vport, ret);
			जाओ metadata_err;
		पूर्ण
		vport->ingress.offloads.metadata_allmatch_grp = g;
	पूर्ण

	kvमुक्त(flow_group_in);
	वापस 0;

metadata_err:
	अगर (!IS_ERR_OR_शून्य(vport->ingress.offloads.metadata_prio_tag_grp)) अणु
		mlx5_destroy_flow_group(vport->ingress.offloads.metadata_prio_tag_grp);
		vport->ingress.offloads.metadata_prio_tag_grp = शून्य;
	पूर्ण
prio_tag_err:
	kvमुक्त(flow_group_in);
	वापस ret;
पूर्ण

अटल व्योम esw_acl_ingress_ofld_groups_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (vport->ingress.offloads.metadata_allmatch_grp) अणु
		mlx5_destroy_flow_group(vport->ingress.offloads.metadata_allmatch_grp);
		vport->ingress.offloads.metadata_allmatch_grp = शून्य;
	पूर्ण

	अगर (vport->ingress.offloads.metadata_prio_tag_grp) अणु
		mlx5_destroy_flow_group(vport->ingress.offloads.metadata_prio_tag_grp);
		vport->ingress.offloads.metadata_prio_tag_grp = शून्य;
	पूर्ण
पूर्ण

पूर्णांक esw_acl_ingress_ofld_setup(काष्ठा mlx5_eचयन *esw,
			       काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक num_ftes = 0;
	पूर्णांक err;

	अगर (!mlx5_eचयन_vport_match_metadata_enabled(esw) &&
	    !esw_acl_ingress_prio_tag_enabled(esw, vport))
		वापस 0;

	esw_acl_ingress_allow_rule_destroy(vport);

	अगर (mlx5_eचयन_vport_match_metadata_enabled(esw))
		num_ftes++;
	अगर (esw_acl_ingress_prio_tag_enabled(esw, vport))
		num_ftes++;

	vport->ingress.acl = esw_acl_table_create(esw, vport,
						  MLX5_FLOW_NAMESPACE_ESW_INGRESS,
						  num_ftes);
	अगर (IS_ERR(vport->ingress.acl)) अणु
		err = PTR_ERR(vport->ingress.acl);
		vport->ingress.acl = शून्य;
		वापस err;
	पूर्ण

	err = esw_acl_ingress_ofld_groups_create(esw, vport);
	अगर (err)
		जाओ group_err;

	esw_debug(esw->dev,
		  "vport[%d] configure ingress rules\n", vport->vport);

	err = esw_acl_ingress_ofld_rules_create(esw, vport);
	अगर (err)
		जाओ rules_err;

	वापस 0;

rules_err:
	esw_acl_ingress_ofld_groups_destroy(vport);
group_err:
	esw_acl_ingress_table_destroy(vport);
	वापस err;
पूर्ण

व्योम esw_acl_ingress_ofld_cleanup(काष्ठा mlx5_eचयन *esw,
				  काष्ठा mlx5_vport *vport)
अणु
	esw_acl_ingress_ofld_rules_destroy(esw, vport);
	esw_acl_ingress_ofld_groups_destroy(vport);
	esw_acl_ingress_table_destroy(vport);
पूर्ण

/* Caller must hold rtnl_lock */
पूर्णांक mlx5_esw_acl_ingress_vport_bond_update(काष्ठा mlx5_eचयन *esw, u16 vport_num,
					   u32 metadata)
अणु
	काष्ठा mlx5_vport *vport = mlx5_eचयन_get_vport(esw, vport_num);
	पूर्णांक err;

	अगर (WARN_ON_ONCE(IS_ERR(vport))) अणु
		esw_warn(esw->dev, "vport(%d) invalid!\n", vport_num);
		err = PTR_ERR(vport);
		जाओ out;
	पूर्ण

	esw_acl_ingress_ofld_rules_destroy(esw, vport);

	vport->metadata = metadata ? metadata : vport->शेष_metadata;

	/* Recreate ingress acl rules with vport->metadata */
	err = esw_acl_ingress_ofld_rules_create(esw, vport);
	अगर (err)
		जाओ out;

	वापस 0;

out:
	vport->metadata = vport->शेष_metadata;
	वापस err;
पूर्ण
