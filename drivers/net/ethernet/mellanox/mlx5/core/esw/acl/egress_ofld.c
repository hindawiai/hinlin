<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2020 Mellanox Technologies Inc. All rights reserved. */

#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "helper.h"
#समावेश "ofld.h"

अटल व्योम esw_acl_egress_ofld_fwd2vport_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (!vport->egress.offloads.fwd_rule)
		वापस;

	mlx5_del_flow_rules(vport->egress.offloads.fwd_rule);
	vport->egress.offloads.fwd_rule = शून्य;
पूर्ण

अटल पूर्णांक esw_acl_egress_ofld_fwd2vport_create(काष्ठा mlx5_eचयन *esw,
						काष्ठा mlx5_vport *vport,
						काष्ठा mlx5_flow_destination *fwd_dest)
अणु
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	पूर्णांक err = 0;

	esw_debug(esw->dev, "vport(%d) configure egress acl rule fwd2vport(%d)\n",
		  vport->vport, fwd_dest->vport.num);

	/* Delete the old egress क्रमward-to-vport rule अगर any */
	esw_acl_egress_ofld_fwd2vport_destroy(vport);

	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;

	vport->egress.offloads.fwd_rule =
		mlx5_add_flow_rules(vport->egress.acl, शून्य,
				    &flow_act, fwd_dest, 1);
	अगर (IS_ERR(vport->egress.offloads.fwd_rule)) अणु
		err = PTR_ERR(vport->egress.offloads.fwd_rule);
		esw_warn(esw->dev,
			 "vport(%d) failed to add fwd2vport acl rule err(%d)\n",
			 vport->vport, err);
		vport->egress.offloads.fwd_rule = शून्य;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक esw_acl_egress_ofld_rules_create(काष्ठा mlx5_eचयन *esw,
					    काष्ठा mlx5_vport *vport,
					    काष्ठा mlx5_flow_destination *fwd_dest)
अणु
	पूर्णांक err = 0;
	पूर्णांक action;

	अगर (MLX5_CAP_GEN(esw->dev, prio_tag_required)) अणु
		/* For prio tag mode, there is only 1 FTEs:
		 * 1) prio tag packets - pop the prio tag VLAN, allow
		 * Unmatched traffic is allowed by शेष
		 */
		esw_debug(esw->dev,
			  "vport[%d] configure prio tag egress rules\n", vport->vport);

		action = MLX5_FLOW_CONTEXT_ACTION_VLAN_POP;
		action |= fwd_dest ? MLX5_FLOW_CONTEXT_ACTION_FWD_DEST :
			  MLX5_FLOW_CONTEXT_ACTION_ALLOW;

		/* prio tag vlan rule - pop it so vport receives untagged packets */
		err = esw_egress_acl_vlan_create(esw, vport, fwd_dest, 0, action);
		अगर (err)
			जाओ prio_err;
	पूर्ण

	अगर (fwd_dest) अणु
		err = esw_acl_egress_ofld_fwd2vport_create(esw, vport, fwd_dest);
		अगर (err)
			जाओ fwd_err;
	पूर्ण

	वापस 0;

fwd_err:
	esw_acl_egress_vlan_destroy(vport);
prio_err:
	वापस err;
पूर्ण

अटल व्योम esw_acl_egress_ofld_rules_destroy(काष्ठा mlx5_vport *vport)
अणु
	esw_acl_egress_vlan_destroy(vport);
	esw_acl_egress_ofld_fwd2vport_destroy(vport);
पूर्ण

अटल पूर्णांक esw_acl_egress_ofld_groups_create(काष्ठा mlx5_eचयन *esw,
					     काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_group *fwd_grp;
	u32 *flow_group_in;
	u32 flow_index = 0;
	पूर्णांक ret = 0;

	अगर (MLX5_CAP_GEN(esw->dev, prio_tag_required)) अणु
		ret = esw_acl_egress_vlan_grp_create(esw, vport);
		अगर (ret)
			वापस ret;

		flow_index++;
	पूर्ण

	अगर (!mlx5_esw_acl_egress_fwd2vport_supported(esw))
		जाओ out;

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in) अणु
		ret = -ENOMEM;
		जाओ fwd_grp_err;
	पूर्ण

	/* This group holds 1 FTE to क्रमward all packets to other vport
	 * when bond vports is supported.
	 */
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, flow_index);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, flow_index);
	fwd_grp = mlx5_create_flow_group(vport->egress.acl, flow_group_in);
	अगर (IS_ERR(fwd_grp)) अणु
		ret = PTR_ERR(fwd_grp);
		esw_warn(esw->dev,
			 "Failed to create vport[%d] egress fwd2vport flow group, err(%d)\n",
			 vport->vport, ret);
		kvमुक्त(flow_group_in);
		जाओ fwd_grp_err;
	पूर्ण
	vport->egress.offloads.fwd_grp = fwd_grp;
	kvमुक्त(flow_group_in);
	वापस 0;

fwd_grp_err:
	esw_acl_egress_vlan_grp_destroy(vport);
out:
	वापस ret;
पूर्ण

अटल व्योम esw_acl_egress_ofld_groups_destroy(काष्ठा mlx5_vport *vport)
अणु
	अगर (!IS_ERR_OR_शून्य(vport->egress.offloads.fwd_grp)) अणु
		mlx5_destroy_flow_group(vport->egress.offloads.fwd_grp);
		vport->egress.offloads.fwd_grp = शून्य;
	पूर्ण
	esw_acl_egress_vlan_grp_destroy(vport);
पूर्ण

अटल bool esw_acl_egress_needed(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	वापस mlx5_eचयन_is_vf_vport(esw, vport_num) || mlx5_esw_is_sf_vport(esw, vport_num);
पूर्ण

पूर्णांक esw_acl_egress_ofld_setup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक table_size = 0;
	पूर्णांक err;

	अगर (!mlx5_esw_acl_egress_fwd2vport_supported(esw) &&
	    !MLX5_CAP_GEN(esw->dev, prio_tag_required))
		वापस 0;

	अगर (!esw_acl_egress_needed(esw, vport->vport))
		वापस 0;

	esw_acl_egress_ofld_rules_destroy(vport);

	अगर (mlx5_esw_acl_egress_fwd2vport_supported(esw))
		table_size++;
	अगर (MLX5_CAP_GEN(esw->dev, prio_tag_required))
		table_size++;
	vport->egress.acl = esw_acl_table_create(esw, vport,
						 MLX5_FLOW_NAMESPACE_ESW_EGRESS, table_size);
	अगर (IS_ERR(vport->egress.acl)) अणु
		err = PTR_ERR(vport->egress.acl);
		vport->egress.acl = शून्य;
		वापस err;
	पूर्ण

	err = esw_acl_egress_ofld_groups_create(esw, vport);
	अगर (err)
		जाओ group_err;

	esw_debug(esw->dev, "vport[%d] configure egress rules\n", vport->vport);

	err = esw_acl_egress_ofld_rules_create(esw, vport, शून्य);
	अगर (err)
		जाओ rules_err;

	वापस 0;

rules_err:
	esw_acl_egress_ofld_groups_destroy(vport);
group_err:
	esw_acl_egress_table_destroy(vport);
	वापस err;
पूर्ण

व्योम esw_acl_egress_ofld_cleanup(काष्ठा mlx5_vport *vport)
अणु
	esw_acl_egress_ofld_rules_destroy(vport);
	esw_acl_egress_ofld_groups_destroy(vport);
	esw_acl_egress_table_destroy(vport);
पूर्ण

पूर्णांक mlx5_esw_acl_egress_vport_bond(काष्ठा mlx5_eचयन *esw, u16 active_vport_num,
				   u16 passive_vport_num)
अणु
	काष्ठा mlx5_vport *passive_vport = mlx5_eचयन_get_vport(esw, passive_vport_num);
	काष्ठा mlx5_vport *active_vport = mlx5_eचयन_get_vport(esw, active_vport_num);
	काष्ठा mlx5_flow_destination fwd_dest = अणुपूर्ण;

	अगर (IS_ERR(active_vport))
		वापस PTR_ERR(active_vport);
	अगर (IS_ERR(passive_vport))
		वापस PTR_ERR(passive_vport);

	/* Cleanup and recreate rules WITHOUT fwd2vport of active vport */
	esw_acl_egress_ofld_rules_destroy(active_vport);
	esw_acl_egress_ofld_rules_create(esw, active_vport, शून्य);

	/* Cleanup and recreate all rules + fwd2vport rule of passive vport to क्रमward */
	esw_acl_egress_ofld_rules_destroy(passive_vport);
	fwd_dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	fwd_dest.vport.num = active_vport_num;
	fwd_dest.vport.vhca_id = MLX5_CAP_GEN(esw->dev, vhca_id);
	fwd_dest.vport.flags = MLX5_FLOW_DEST_VPORT_VHCA_ID;

	वापस esw_acl_egress_ofld_rules_create(esw, passive_vport, &fwd_dest);
पूर्ण

पूर्णांक mlx5_esw_acl_egress_vport_unbond(काष्ठा mlx5_eचयन *esw, u16 vport_num)
अणु
	काष्ठा mlx5_vport *vport = mlx5_eचयन_get_vport(esw, vport_num);

	अगर (IS_ERR(vport))
		वापस PTR_ERR(vport);

	esw_acl_egress_ofld_rules_destroy(vport);
	वापस esw_acl_egress_ofld_rules_create(esw, vport, शून्य);
पूर्ण
