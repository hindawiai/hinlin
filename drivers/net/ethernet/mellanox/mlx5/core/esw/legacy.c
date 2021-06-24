<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/* Copyright (c) 2021 Mellanox Technologies Ltd */

#समावेश <linux/etherdevice.h>
#समावेश <linux/mlx5/driver.h>
#समावेश <linux/mlx5/mlx5_अगरc.h>
#समावेश <linux/mlx5/vport.h>
#समावेश <linux/mlx5/fs.h>
#समावेश "esw/acl/lgcy.h"
#समावेश "esw/legacy.h"
#समावेश "mlx5_core.h"
#समावेश "eswitch.h"
#समावेश "fs_core.h"

क्रमागत अणु
	LEGACY_VEPA_PRIO = 0,
	LEGACY_FDB_PRIO,
पूर्ण;

अटल पूर्णांक esw_create_legacy_vepa_table(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_namespace *root_ns;
	काष्ठा mlx5_flow_table *fdb;
	पूर्णांक err;

	root_ns = mlx5_get_fdb_sub_ns(dev, 0);
	अगर (!root_ns) अणु
		esw_warn(dev, "Failed to get FDB flow namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	/* num FTE 2, num FG 2 */
	ft_attr.prio = LEGACY_VEPA_PRIO;
	ft_attr.max_fte = 2;
	ft_attr.स्वतःgroup.max_num_groups = 2;
	fdb = mlx5_create_स्वतः_grouped_flow_table(root_ns, &ft_attr);
	अगर (IS_ERR(fdb)) अणु
		err = PTR_ERR(fdb);
		esw_warn(dev, "Failed to create VEPA FDB err %d\n", err);
		वापस err;
	पूर्ण
	esw->fdb_table.legacy.vepa_fdb = fdb;

	वापस 0;
पूर्ण

अटल व्योम esw_destroy_legacy_fdb_table(काष्ठा mlx5_eचयन *esw)
अणु
	esw_debug(esw->dev, "Destroy FDB Table\n");
	अगर (!esw->fdb_table.legacy.fdb)
		वापस;

	अगर (esw->fdb_table.legacy.promisc_grp)
		mlx5_destroy_flow_group(esw->fdb_table.legacy.promisc_grp);
	अगर (esw->fdb_table.legacy.allmulti_grp)
		mlx5_destroy_flow_group(esw->fdb_table.legacy.allmulti_grp);
	अगर (esw->fdb_table.legacy.addr_grp)
		mlx5_destroy_flow_group(esw->fdb_table.legacy.addr_grp);
	mlx5_destroy_flow_table(esw->fdb_table.legacy.fdb);

	esw->fdb_table.legacy.fdb = शून्य;
	esw->fdb_table.legacy.addr_grp = शून्य;
	esw->fdb_table.legacy.allmulti_grp = शून्य;
	esw->fdb_table.legacy.promisc_grp = शून्य;
	atomic64_set(&esw->user_count, 0);
पूर्ण

अटल पूर्णांक esw_create_legacy_fdb_table(काष्ठा mlx5_eचयन *esw)
अणु
	पूर्णांक inlen = MLX5_ST_SZ_BYTES(create_flow_group_in);
	काष्ठा mlx5_flow_table_attr ft_attr = अणुपूर्ण;
	काष्ठा mlx5_core_dev *dev = esw->dev;
	काष्ठा mlx5_flow_namespace *root_ns;
	काष्ठा mlx5_flow_table *fdb;
	काष्ठा mlx5_flow_group *g;
	व्योम *match_criteria;
	पूर्णांक table_size;
	u32 *flow_group_in;
	u8 *dmac;
	पूर्णांक err = 0;

	esw_debug(dev, "Create FDB log_max_size(%d)\n",
		  MLX5_CAP_ESW_FLOWTABLE_FDB(dev, log_max_ft_size));

	root_ns = mlx5_get_fdb_sub_ns(dev, 0);
	अगर (!root_ns) अणु
		esw_warn(dev, "Failed to get FDB flow namespace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	flow_group_in = kvzalloc(inlen, GFP_KERNEL);
	अगर (!flow_group_in)
		वापस -ENOMEM;

	table_size = BIT(MLX5_CAP_ESW_FLOWTABLE_FDB(dev, log_max_ft_size));
	ft_attr.max_fte = table_size;
	ft_attr.prio = LEGACY_FDB_PRIO;
	fdb = mlx5_create_flow_table(root_ns, &ft_attr);
	अगर (IS_ERR(fdb)) अणु
		err = PTR_ERR(fdb);
		esw_warn(dev, "Failed to create FDB Table err %d\n", err);
		जाओ out;
	पूर्ण
	esw->fdb_table.legacy.fdb = fdb;

	/* Addresses group : Full match unicast/multicast addresses */
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_OUTER_HEADERS);
	match_criteria = MLX5_ADDR_OF(create_flow_group_in, flow_group_in, match_criteria);
	dmac = MLX5_ADDR_OF(fte_match_param, match_criteria, outer_headers.dmac_47_16);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, 0);
	/* Preserve 2 entries क्रम allmulti and promisc rules*/
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, table_size - 3);
	eth_broadcast_addr(dmac);
	g = mlx5_create_flow_group(fdb, flow_group_in);
	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create flow group err(%d)\n", err);
		जाओ out;
	पूर्ण
	esw->fdb_table.legacy.addr_grp = g;

	/* Allmulti group : One rule that क्रमwards any mcast traffic */
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_OUTER_HEADERS);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, table_size - 2);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, table_size - 2);
	eth_zero_addr(dmac);
	dmac[0] = 0x01;
	g = mlx5_create_flow_group(fdb, flow_group_in);
	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create allmulti flow group err(%d)\n", err);
		जाओ out;
	पूर्ण
	esw->fdb_table.legacy.allmulti_grp = g;

	/* Promiscuous group :
	 * One rule that क्रमward all unmatched traffic from previous groups
	 */
	eth_zero_addr(dmac);
	MLX5_SET(create_flow_group_in, flow_group_in, match_criteria_enable,
		 MLX5_MATCH_MISC_PARAMETERS);
	MLX5_SET_TO_ONES(fte_match_param, match_criteria, misc_parameters.source_port);
	MLX5_SET(create_flow_group_in, flow_group_in, start_flow_index, table_size - 1);
	MLX5_SET(create_flow_group_in, flow_group_in, end_flow_index, table_size - 1);
	g = mlx5_create_flow_group(fdb, flow_group_in);
	अगर (IS_ERR(g)) अणु
		err = PTR_ERR(g);
		esw_warn(dev, "Failed to create promisc flow group err(%d)\n", err);
		जाओ out;
	पूर्ण
	esw->fdb_table.legacy.promisc_grp = g;

out:
	अगर (err)
		esw_destroy_legacy_fdb_table(esw);

	kvमुक्त(flow_group_in);
	वापस err;
पूर्ण

अटल व्योम esw_destroy_legacy_vepa_table(काष्ठा mlx5_eचयन *esw)
अणु
	esw_debug(esw->dev, "Destroy VEPA Table\n");
	अगर (!esw->fdb_table.legacy.vepa_fdb)
		वापस;

	mlx5_destroy_flow_table(esw->fdb_table.legacy.vepa_fdb);
	esw->fdb_table.legacy.vepa_fdb = शून्य;
पूर्ण

अटल पूर्णांक esw_create_legacy_table(काष्ठा mlx5_eचयन *esw)
अणु
	पूर्णांक err;

	स_रखो(&esw->fdb_table.legacy, 0, माप(काष्ठा legacy_fdb));
	atomic64_set(&esw->user_count, 0);

	err = esw_create_legacy_vepa_table(esw);
	अगर (err)
		वापस err;

	err = esw_create_legacy_fdb_table(esw);
	अगर (err)
		esw_destroy_legacy_vepa_table(esw);

	वापस err;
पूर्ण

अटल व्योम esw_cleanup_vepa_rules(काष्ठा mlx5_eचयन *esw)
अणु
	अगर (esw->fdb_table.legacy.vepa_uplink_rule)
		mlx5_del_flow_rules(esw->fdb_table.legacy.vepa_uplink_rule);

	अगर (esw->fdb_table.legacy.vepa_star_rule)
		mlx5_del_flow_rules(esw->fdb_table.legacy.vepa_star_rule);

	esw->fdb_table.legacy.vepa_uplink_rule = शून्य;
	esw->fdb_table.legacy.vepa_star_rule = शून्य;
पूर्ण

अटल व्योम esw_destroy_legacy_table(काष्ठा mlx5_eचयन *esw)
अणु
	esw_cleanup_vepa_rules(esw);
	esw_destroy_legacy_fdb_table(esw);
	esw_destroy_legacy_vepa_table(esw);
पूर्ण

#घोषणा MLX5_LEGACY_SRIOV_VPORT_EVENTS (MLX5_VPORT_UC_ADDR_CHANGE | \
					MLX5_VPORT_MC_ADDR_CHANGE | \
					MLX5_VPORT_PROMISC_CHANGE)

पूर्णांक esw_legacy_enable(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा mlx5_vport *vport;
	अचिन्हित दीर्घ i;
	पूर्णांक ret;

	ret = esw_create_legacy_table(esw);
	अगर (ret)
		वापस ret;

	mlx5_esw_क्रम_each_vf_vport(esw, i, vport, esw->esw_funcs.num_vfs)
		vport->info.link_state = MLX5_VPORT_ADMIN_STATE_AUTO;

	ret = mlx5_eचयन_enable_pf_vf_vports(esw, MLX5_LEGACY_SRIOV_VPORT_EVENTS);
	अगर (ret)
		esw_destroy_legacy_table(esw);
	वापस ret;
पूर्ण

व्योम esw_legacy_disable(काष्ठा mlx5_eचयन *esw)
अणु
	काष्ठा esw_mc_addr *mc_promisc;

	mlx5_eचयन_disable_pf_vf_vports(esw);

	mc_promisc = &esw->mc_promisc;
	अगर (mc_promisc->uplink_rule)
		mlx5_del_flow_rules(mc_promisc->uplink_rule);

	esw_destroy_legacy_table(esw);
पूर्ण

अटल पूर्णांक _mlx5_eचयन_set_vepa_locked(काष्ठा mlx5_eचयन *esw,
					 u8 setting)
अणु
	काष्ठा mlx5_flow_destination dest = अणुपूर्ण;
	काष्ठा mlx5_flow_act flow_act = अणुपूर्ण;
	काष्ठा mlx5_flow_handle *flow_rule;
	काष्ठा mlx5_flow_spec *spec;
	पूर्णांक err = 0;
	व्योम *misc;

	अगर (!setting) अणु
		esw_cleanup_vepa_rules(esw);
		वापस 0;
	पूर्ण

	अगर (esw->fdb_table.legacy.vepa_uplink_rule)
		वापस 0;

	spec = kvzalloc(माप(*spec), GFP_KERNEL);
	अगर (!spec)
		वापस -ENOMEM;

	/* Uplink rule क्रमward uplink traffic to FDB */
	misc = MLX5_ADDR_OF(fte_match_param, spec->match_value, misc_parameters);
	MLX5_SET(fte_match_set_misc, misc, source_port, MLX5_VPORT_UPLINK);

	misc = MLX5_ADDR_OF(fte_match_param, spec->match_criteria, misc_parameters);
	MLX5_SET_TO_ONES(fte_match_set_misc, misc, source_port);

	spec->match_criteria_enable = MLX5_MATCH_MISC_PARAMETERS;
	dest.type = MLX5_FLOW_DESTINATION_TYPE_FLOW_TABLE;
	dest.ft = esw->fdb_table.legacy.fdb;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	flow_rule = mlx5_add_flow_rules(esw->fdb_table.legacy.vepa_fdb, spec,
					&flow_act, &dest, 1);
	अगर (IS_ERR(flow_rule)) अणु
		err = PTR_ERR(flow_rule);
		जाओ out;
	पूर्ण अन्यथा अणु
		esw->fdb_table.legacy.vepa_uplink_rule = flow_rule;
	पूर्ण

	/* Star rule to क्रमward all traffic to uplink vport */
	स_रखो(&dest, 0, माप(dest));
	dest.type = MLX5_FLOW_DESTINATION_TYPE_VPORT;
	dest.vport.num = MLX5_VPORT_UPLINK;
	flow_act.action = MLX5_FLOW_CONTEXT_ACTION_FWD_DEST;
	flow_rule = mlx5_add_flow_rules(esw->fdb_table.legacy.vepa_fdb, शून्य,
					&flow_act, &dest, 1);
	अगर (IS_ERR(flow_rule)) अणु
		err = PTR_ERR(flow_rule);
		जाओ out;
	पूर्ण अन्यथा अणु
		esw->fdb_table.legacy.vepa_star_rule = flow_rule;
	पूर्ण

out:
	kvमुक्त(spec);
	अगर (err)
		esw_cleanup_vepa_rules(esw);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_set_vepa(काष्ठा mlx5_eचयन *esw, u8 setting)
अणु
	पूर्णांक err = 0;

	अगर (!esw)
		वापस -EOPNOTSUPP;

	अगर (!mlx5_esw_allowed(esw))
		वापस -EPERM;

	mutex_lock(&esw->state_lock);
	अगर (esw->mode != MLX5_ESWITCH_LEGACY) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	err = _mlx5_eचयन_set_vepa_locked(esw, setting);

out:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_get_vepa(काष्ठा mlx5_eचयन *esw, u8 *setting)
अणु
	अगर (!esw)
		वापस -EOPNOTSUPP;

	अगर (!mlx5_esw_allowed(esw))
		वापस -EPERM;

	अगर (esw->mode != MLX5_ESWITCH_LEGACY)
		वापस -EOPNOTSUPP;

	*setting = esw->fdb_table.legacy.vepa_uplink_rule ? 1 : 0;
	वापस 0;
पूर्ण

पूर्णांक esw_legacy_vport_acl_setup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport)
अणु
	पूर्णांक ret;

	/* Only non manager vports need ACL in legacy mode */
	अगर (mlx5_esw_is_manager_vport(esw, vport->vport))
		वापस 0;

	ret = esw_acl_ingress_lgcy_setup(esw, vport);
	अगर (ret)
		जाओ ingress_err;

	ret = esw_acl_egress_lgcy_setup(esw, vport);
	अगर (ret)
		जाओ egress_err;

	वापस 0;

egress_err:
	esw_acl_ingress_lgcy_cleanup(esw, vport);
ingress_err:
	वापस ret;
पूर्ण

व्योम esw_legacy_vport_acl_cleanup(काष्ठा mlx5_eचयन *esw, काष्ठा mlx5_vport *vport)
अणु
	अगर (mlx5_esw_is_manager_vport(esw, vport->vport))
		वापस;

	esw_acl_egress_lgcy_cleanup(esw, vport);
	esw_acl_ingress_lgcy_cleanup(esw, vport);
पूर्ण

पूर्णांक mlx5_esw_query_vport_drop_stats(काष्ठा mlx5_core_dev *dev,
				    काष्ठा mlx5_vport *vport,
				    काष्ठा mlx5_vport_drop_stats *stats)
अणु
	u64 rx_discard_vport_करोwn, tx_discard_vport_करोwn;
	काष्ठा mlx5_eचयन *esw = dev->priv.eचयन;
	u64 bytes = 0;
	पूर्णांक err = 0;

	अगर (esw->mode != MLX5_ESWITCH_LEGACY)
		वापस 0;

	mutex_lock(&esw->state_lock);
	अगर (!vport->enabled)
		जाओ unlock;

	अगर (!IS_ERR_OR_शून्य(vport->egress.legacy.drop_counter))
		mlx5_fc_query(dev, vport->egress.legacy.drop_counter,
			      &stats->rx_dropped, &bytes);

	अगर (vport->ingress.legacy.drop_counter)
		mlx5_fc_query(dev, vport->ingress.legacy.drop_counter,
			      &stats->tx_dropped, &bytes);

	अगर (!MLX5_CAP_GEN(dev, receive_discard_vport_करोwn) &&
	    !MLX5_CAP_GEN(dev, transmit_discard_vport_करोwn))
		जाओ unlock;

	err = mlx5_query_vport_करोwn_stats(dev, vport->vport, 1,
					  &rx_discard_vport_करोwn,
					  &tx_discard_vport_करोwn);
	अगर (err)
		जाओ unlock;

	अगर (MLX5_CAP_GEN(dev, receive_discard_vport_करोwn))
		stats->rx_dropped += rx_discard_vport_करोwn;
	अगर (MLX5_CAP_GEN(dev, transmit_discard_vport_करोwn))
		stats->tx_dropped += tx_discard_vport_करोwn;

unlock:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_set_vport_vlan(काष्ठा mlx5_eचयन *esw,
				u16 vport, u16 vlan, u8 qos)
अणु
	u8 set_flags = 0;
	पूर्णांक err = 0;

	अगर (!mlx5_esw_allowed(esw))
		वापस -EPERM;

	अगर (vlan || qos)
		set_flags = SET_VLAN_STRIP | SET_VLAN_INSERT;

	mutex_lock(&esw->state_lock);
	अगर (esw->mode != MLX5_ESWITCH_LEGACY) अणु
		अगर (!vlan)
			जाओ unlock; /* compatibility with libvirt */

		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण

	err = __mlx5_eचयन_set_vport_vlan(esw, vport, vlan, qos, set_flags);

unlock:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_set_vport_spoofchk(काष्ठा mlx5_eचयन *esw,
				    u16 vport, bool spoofchk)
अणु
	काष्ठा mlx5_vport *evport = mlx5_eचयन_get_vport(esw, vport);
	bool pschk;
	पूर्णांक err = 0;

	अगर (!mlx5_esw_allowed(esw))
		वापस -EPERM;
	अगर (IS_ERR(evport))
		वापस PTR_ERR(evport);

	mutex_lock(&esw->state_lock);
	अगर (esw->mode != MLX5_ESWITCH_LEGACY) अणु
		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण
	pschk = evport->info.spoofchk;
	evport->info.spoofchk = spoofchk;
	अगर (pschk && !is_valid_ether_addr(evport->info.mac))
		mlx5_core_warn(esw->dev,
			       "Spoofchk in set while MAC is invalid, vport(%d)\n",
			       evport->vport);
	अगर (evport->enabled && esw->mode == MLX5_ESWITCH_LEGACY)
		err = esw_acl_ingress_lgcy_setup(esw, evport);
	अगर (err)
		evport->info.spoofchk = pschk;

unlock:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण

पूर्णांक mlx5_eचयन_set_vport_trust(काष्ठा mlx5_eचयन *esw,
				 u16 vport, bool setting)
अणु
	काष्ठा mlx5_vport *evport = mlx5_eचयन_get_vport(esw, vport);
	पूर्णांक err = 0;

	अगर (!mlx5_esw_allowed(esw))
		वापस -EPERM;
	अगर (IS_ERR(evport))
		वापस PTR_ERR(evport);

	mutex_lock(&esw->state_lock);
	अगर (esw->mode != MLX5_ESWITCH_LEGACY) अणु
		err = -EOPNOTSUPP;
		जाओ unlock;
	पूर्ण
	evport->info.trusted = setting;
	अगर (evport->enabled)
		esw_vport_change_handle_locked(evport);

unlock:
	mutex_unlock(&esw->state_lock);
	वापस err;
पूर्ण
