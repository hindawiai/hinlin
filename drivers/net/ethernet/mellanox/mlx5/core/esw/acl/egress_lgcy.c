<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Inc. All rights reserved. */

#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "helper.h"
#समावेश "lgcy.h"

अटल व्योम esw_acl_egress_lgcy_rules_destroy(काष्ठा mlx5_vport *vport)
अणु
	esw_acl_egress_vlan_destroy(vport);
	अगर (!IS_ERR_OR_शून्य(vport->egress.legacy.drop_rule)) अणु
		mlx5_del_flow_rules(vport->egress.legacy.drop_rule);
		vport->egress.legacy.drop_rule = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक esw_acl_egress_lgcy_groups_create(काष्ठा mlx5_eचयन *esw,
					     काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_group *drop_grp;
	u32 *flow_group_in;
	पूर्णांक err = 0;

	err = esw_acl_egress_vlan_grp_create(esw, vport);
	अगर (err)
		वापस err;

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in) अणु
		err = -ENOMEM;
		जाओ alloc_err;
	पूर्ण

	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 1);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, 1);
	drop_grp = mlx5_create_flow_group(vport->egress.acl, flow_group_in);
	अगर (IS_ERR(drop_grp)) अणु
		err = PTR_ERR(drop_grp);
		esw_warn(dev, "Failed to create E-Switch vport[%d] egress drop flow group, err(%d)\n",
			 vport->vport, err);
		जाओ drop_grp_err;
	पूर्ण

	vport->egress.legacy.drop_grp = drop_grp;
	kvमुक्त(flow_group_in);
	वापस 0;

drop_grp_err:
	kvमुक्त(flow_group_in);
alloc_err:
	esw_acl_egress_vlan_grp_destroy(vport);
	वापस err;
पूर्ण

अटल व्योम esw_acl_egress_lgcy_groups_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (!IS_ERR_OR_शून्य(vport->egress.legacy.drop_grp)) अणु
		mlx5_destroy_flow_group(vport->egress.legacy.drop_grp);
		vport->egress.legacy.drop_grp = शून्य;
	पूर्ण
	esw_acl_egress_vlan_grp_destroy(vport);
पूर्ण

पूर्णांक esw_acl_egress_lgcy_setup(काष्ठा mlx5_eचयन *esw,
			      काष्ठा mlx5_vport *vport)
अणु
	काष्ठा mlx5_flow_destination drop_ctr_dst = अणुपूर्ण;
	काष्ठा mlx5_flow_destination *dst = शून्य;
	काष्ठा mlx5_fc *drop_counter = शून्य;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	/* The egress acl table contains 2 rules:
	 * 1)Allow traffic with vlan_tag=vst_vlan_id
	 * 2)Drop all other traffic.
	 */
	पूर्णांक table_size = 2;
	पूर्णांक dest_num = 0;
	पूर्णांक err = 0;

	अगर (MLX5_CAP_ESW_EGRESS_ACL(esw->dev, flow_counter)) अणु
		drop_counter = mlx5_fc_create(esw->dev, false);
		अगर (IS_ERR(drop_counter))
			esw_warn(esw->dev,
				 "vport[%d] configure egress drop rule counter err(%ld)\n",
				 vport->vport, PTR_ERR(drop_counter));
		vport->egress.legacy.drop_counter = drop_counter;
	पूर्ण

	esw_acl_egress_lgcy_rules_destroy(vport);

	अगर (!vport->info.vlan && !vport->info.qos) अणु
		esw_acl_egress_lgcy_cleanup(esw, vport);
		वापस 0;
	पूर्ण

	अगर (!vport->egress.acl) अणु
		vport->egress.acl = esw_acl_table_create(esw, vport,
							 MLX5_FLOW_NAMESPACE_ESW_EGRESS,
							 table_size);
		अगर (IS_ERR(vport->egress.acl)) अणु
			err = PTR_ERR(vport->egress.acl);
			vport->egress.acl = शून्य;
			जाओ out;
		पूर्ण

		err = esw_acl_egress_lgcy_groups_create(esw, vport);
		अगर (err)
			जाओ out;
	पूर्ण

	esw_debug(esw->dev,
		  "vport[%d] configure egress rules, vlan(%d) qos(%d)\n",
		  vport->vport, vport->info.vlan, vport->info.qos);

	/* Allowed vlan rule */
	err = esw_egress_acl_vlan_create(esw, vport, शून्य, vport->info.vlan,
					 MLX5_FLOW_CONTEXT_ACTION_ALLOW);
	अगर (err)
		जाओ out;

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_DROP;

	/* Attach egress drop flow counter */
	अगर (!IS_ERR_OR_शून्य(drop_counter)) अणु
		flow_act.action |= MLX5_FLOW_CONTEXT_ACTION_COUNT;
		drop_ctr_dst.type = MLX5_FLOW_DESTINATION_TYPE_COUNTER;
		drop_ctr_dst.counter_id = mlx5_fc_id(drop_counter);
		dst = &drop_ctr_dst;
		dest_num++;
	पूर्ण
	vport->egress.legacy.drop_rule =
		mlx5_add_flow_rules(vport->egress.acl, शून्य,
				    &flow_act, dst, dest_num);
	अगर (IS_ERR(vport->egress.legacy.drop_rule)) अणु
		err = PTR_ERR(vport->egress.legacy.drop_rule);
		esw_warn(esw->dev,
			 "vport[%d] configure egress drop rule failed, err(%d)\n",
			 vport->vport, err);
		vport->egress.legacy.drop_rule = शून्य;
		जाओ out;
	पूर्ण

	वापस err;

out:
	esw_acl_egress_lgcy_cleanup(esw, vport);
	वापस err;
पूर्ण

व्योम esw_acl_egress_lgcy_cleanup(काष्ठा mlx5_eचयन *esw,
				 काष्ठा mlx5_vport *vport)
अणु
	अगर (IS_ERR_OR_शून्य(vport->egress.acl))
		जाओ clean_drop_counter;

	esw_debug(esw->dev, "Destroy vport[%d] E-Switch egress ACL\n", vport->vport);

	esw_acl_egress_lgcy_rules_destroy(vport);
	esw_acl_egress_lgcy_groups_destroy(vport);
	esw_acl_egress_table_destroy(vport);

clean_drop_counter:
	अगर (!IS_ERR_OR_शून्य(vport->egress.legacy.drop_counter)) अणु
		mlx5_fc_destroy(esw->dev, vport->egress.legacy.drop_counter);
		vport->egress.legacy.drop_counter = शून्य;
	पूर्ण
पूर्ण
