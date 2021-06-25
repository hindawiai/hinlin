<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Inc. All rights reserved. */

#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "helper.h"

काष्ठा mlx5_flow_table *
esw_acl_table_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport, पूर्णांक ns, पूर्णांक size)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_namespace *root_ns;
	काष्ठा mlx5_flow_table *acl;
	पूर्णांक acl_supported;
	u16 vport_num;
	पूर्णांक err;

	acl_supported = (ns == MLX5_FLOW_NAMESPACE_ESW_INGRESS) ?
			MLX5_CAP_ESW_INGRESS_ACL(dev, ft_support) :
			MLX5_CAP_ESW_EGRESS_ACL(dev, ft_support);

	अगर (!acl_supported)
		वापस ERR_PTR(-EOPNOTSUPP);

	vport_num = vport->vport;
	esw_debug(dev, "Create vport[%d] %s ACL table\n", vport_num,
		  ns == MLX5_FLOW_NAMESPACE_ESW_INGRESS ? "ingress" : "egress");

	root_ns = mlx5_get_flow_vport_acl_namespace(dev, ns, vport->index);
	अगर (!root_ns) अणु
		esw_warn(dev, "Failed to get E-Switch root namespace for vport (%d)\n",
			 vport_num);
		वापस ERR_PTR(-EOPNOTSUPP);
	पूर्ण

	ft_attr.max_fte = size;
	ft_attr.flags = MLX5_FLOW_TABLE_OTHER_VPORT;
	acl = mlx5_create_vport_flow_table(root_ns, &ft_attr, vport_num);
	अगर (IS_ERR(acl)) अणु
		err = PTR_ERR(acl);
		esw_warn(dev, "vport[%d] create %s ACL table, err(%d)\n", vport_num,
			 ns == MLX5_FLOW_NAMESPACE_ESW_INGRESS ? "ingress" : "egress", err);
	पूर्ण
	वापस acl;
पूर्ण

पूर्णांक esw_egress_acl_vlan_create(काष्ठा mlx5_eचयन *esw,
			       काष्ठा mlx5_vport *vport,
			       काष्ठा mlx5_flow_destination *fwd_dest,
			       u16 vlan_id, u32 flow_action)
अणु
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;

	अगर (vport->egress.allowed_vlan)
		वापस -EEXIST;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, spec->match_value, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, spec->match_criteria, outer_headers.first_vid);
	MLX5_SET(fte_match_param, spec->match_value, outer_headers.first_vid, vlan_id);

	spec->match_criteria_enable = MLX5_MATCH_OUTER_HEADERS;
	flow_act.action = flow_action;
	vport->egress.allowed_vlan =
		mlx5_add_flow_rules(vport->egress.acl, spec,
				    &flow_act, fwd_dest, 0);
	अगर (IS_ERR(vport->egress.allowed_vlan)) अणु
		err = PTR_ERR(vport->egress.allowed_vlan);
		esw_warn(esw->dev,
			 "vport[%d] configure egress vlan rule failed, err(%d)\n",
			 vport->vport, err);
		vport->egress.allowed_vlan = शून्य;
	पूर्ण

	kvमुक्त(spec);
	वापस err;
पूर्ण

व्योम esw_acl_egress_vlan_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (!IS_ERR_OR_शून्य(vport->egress.allowed_vlan)) अणु
		mlx5_del_flow_rules(vport->egress.allowed_vlan);
		vport->egress.allowed_vlan = शून्य;
	पूर्ण
पूर्ण

पूर्णांक esw_acl_egress_vlan_grp_create(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_group *vlan_grp;
	व्योम *match_criteria;
	u32 *flow_group_in;
	पूर्णांक ret = 0;

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in)
		वापस -ENOMEM;

	MLX5_SET(create_flow_group_in, flow_group_in,
		 match_criteria_enable, MLX5_MATCH_OUTER_HEADERS);
	match_criteria = MLX5_ADDR_OF(create_flow_group_in,
				      flow_group_in, match_criteria);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.cvlan_tag);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, outer_headers.first_vid);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 0);

	vlan_grp = mlx5_create_flow_group(vport->egress.acl, flow_group_in);
	अगर (IS_ERR(vlan_grp)) अणु
		ret = PTR_ERR(vlan_grp);
		esw_warn(esw->dev,
			 "Failed to create E-Switch vport[%d] egress pop vlans flow group, err(%d)\n",
			 vport->vport, ret);
		जाओ out;
	पूर्ण
	vport->egress.vlan_grp = vlan_grp;

out:
	kvमुक्त(flow_group_in);
	वापस ret;
पूर्ण

व्योम esw_acl_egress_vlan_grp_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (!IS_ERR_OR_शून्य(vport->egress.vlan_grp)) अणु
		mlx5_destroy_flow_group(vport->egress.vlan_grp);
		vport->egress.vlan_grp = शून्य;
	पूर्ण
पूर्ण

व्योम esw_acl_egress_table_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (IS_ERR_OR_शून्य(vport->egress.acl))
		वापस;

	mlx5_destroy_flow_table(vport->egress.acl);
	vport->egress.acl = शून्य;
पूर्ण

व्योम esw_acl_ingress_table_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (!vport->ingress.acl)
		वापस;

	mlx5_destroy_flow_table(vport->ingress.acl);
	vport->ingress.acl = शून्य;
पूर्ण

व्योम esw_acl_ingress_allow_rule_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (!vport->ingress.allow_rule)
		वापस;

	mlx5_del_flow_rules(vport->ingress.allow_rule);
	vport->ingress.allow_rule = शून्य;
पूर्ण
