<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Handling of a single चयन port
 *
 * Copyright (c) 2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#समावेश <linux/अगर_bridge.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/of_net.h>

#समावेश "dsa_priv.h"

/**
 * dsa_port_notअगरy - Notअगरy the चयनing fabric of changes to a port
 * @dp: port on which change occurred
 * @e: event, must be of type DSA_NOTIFIER_*
 * @v: event-specअगरic value.
 *
 * Notअगरy all चयनes in the DSA tree that this port's चयन beदीर्घs to,
 * including this चयन itself, of an event. Allows the other चयनes to
 * reconfigure themselves क्रम cross-chip operations. Can also be used to
 * reconfigure ports without net_devices (CPU ports, DSA links) whenever
 * a user port's state changes.
 */
अटल पूर्णांक dsa_port_notअगरy(स्थिर काष्ठा dsa_port *dp, अचिन्हित दीर्घ e, व्योम *v)
अणु
	वापस dsa_tree_notअगरy(dp->ds->dst, e, v);
पूर्ण

पूर्णांक dsa_port_set_state(काष्ठा dsa_port *dp, u8 state)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक port = dp->index;

	अगर (!ds->ops->port_stp_state_set)
		वापस -EOPNOTSUPP;

	ds->ops->port_stp_state_set(ds, port, state);

	अगर (ds->ops->port_fast_age) अणु
		/* Fast age FDB entries or flush appropriate क्रमwarding database
		 * क्रम the given port, अगर we are moving it from Learning or
		 * Forwarding state, to Disabled or Blocking or Listening state.
		 */

		अगर ((dp->stp_state == BR_STATE_LEARNING ||
		     dp->stp_state == BR_STATE_FORWARDING) &&
		    (state == BR_STATE_DISABLED ||
		     state == BR_STATE_BLOCKING ||
		     state == BR_STATE_LISTENING))
			ds->ops->port_fast_age(ds, port);
	पूर्ण

	dp->stp_state = state;

	वापस 0;
पूर्ण

अटल व्योम dsa_port_set_state_now(काष्ठा dsa_port *dp, u8 state)
अणु
	पूर्णांक err;

	err = dsa_port_set_state(dp, state);
	अगर (err)
		pr_err("DSA: failed to set STP state %u (%d)\n", state, err);
पूर्ण

पूर्णांक dsa_port_enable_rt(काष्ठा dsa_port *dp, काष्ठा phy_device *phy)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक port = dp->index;
	पूर्णांक err;

	अगर (ds->ops->port_enable) अणु
		err = ds->ops->port_enable(ds, port, phy);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!dp->bridge_dev)
		dsa_port_set_state_now(dp, BR_STATE_FORWARDING);

	अगर (dp->pl)
		phylink_start(dp->pl);

	वापस 0;
पूर्ण

पूर्णांक dsa_port_enable(काष्ठा dsa_port *dp, काष्ठा phy_device *phy)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = dsa_port_enable_rt(dp, phy);
	rtnl_unlock();

	वापस err;
पूर्ण

व्योम dsa_port_disable_rt(काष्ठा dsa_port *dp)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक port = dp->index;

	अगर (dp->pl)
		phylink_stop(dp->pl);

	अगर (!dp->bridge_dev)
		dsa_port_set_state_now(dp, BR_STATE_DISABLED);

	अगर (ds->ops->port_disable)
		ds->ops->port_disable(ds, port);
पूर्ण

व्योम dsa_port_disable(काष्ठा dsa_port *dp)
अणु
	rtnl_lock();
	dsa_port_disable_rt(dp);
	rtnl_unlock();
पूर्ण

अटल पूर्णांक dsa_port_inherit_brport_flags(काष्ठा dsa_port *dp,
					 काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर अचिन्हित दीर्घ mask = BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD |
				   BR_BCAST_FLOOD;
	काष्ठा net_device *brport_dev = dsa_port_to_bridge_port(dp);
	पूर्णांक flag, err;

	क्रम_each_set_bit(flag, &mask, 32) अणु
		काष्ठा चयनdev_brport_flags flags = अणु0पूर्ण;

		flags.mask = BIT(flag);

		अगर (br_port_flag_is_set(brport_dev, BIT(flag)))
			flags.val = BIT(flag);

		err = dsa_port_bridge_flags(dp, flags, extack);
		अगर (err && err != -EOPNOTSUPP)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम dsa_port_clear_brport_flags(काष्ठा dsa_port *dp)
अणु
	स्थिर अचिन्हित दीर्घ val = BR_FLOOD | BR_MCAST_FLOOD | BR_BCAST_FLOOD;
	स्थिर अचिन्हित दीर्घ mask = BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD |
				   BR_BCAST_FLOOD;
	पूर्णांक flag, err;

	क्रम_each_set_bit(flag, &mask, 32) अणु
		काष्ठा चयनdev_brport_flags flags = अणु0पूर्ण;

		flags.mask = BIT(flag);
		flags.val = val & BIT(flag);

		err = dsa_port_bridge_flags(dp, flags, शून्य);
		अगर (err && err != -EOPNOTSUPP)
			dev_err(dp->ds->dev,
				"failed to clear bridge port flag %lu: %pe\n",
				flags.val, ERR_PTR(err));
	पूर्ण
पूर्ण

अटल पूर्णांक dsa_port_चयनdev_sync(काष्ठा dsa_port *dp,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *brport_dev = dsa_port_to_bridge_port(dp);
	काष्ठा net_device *br = dp->bridge_dev;
	पूर्णांक err;

	err = dsa_port_inherit_brport_flags(dp, extack);
	अगर (err)
		वापस err;

	err = dsa_port_set_state(dp, br_port_get_stp_state(brport_dev));
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	err = dsa_port_vlan_filtering(dp, br_vlan_enabled(br), extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	err = dsa_port_mrouter(dp->cpu_dp, br_multicast_router(br), extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	err = dsa_port_ageing_समय(dp, br_get_ageing_समय(br));
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	err = br_mdb_replay(br, brport_dev,
			    &dsa_slave_चयनdev_blocking_notअगरier,
			    extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	err = br_fdb_replay(br, brport_dev, &dsa_slave_चयनdev_notअगरier);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	err = br_vlan_replay(br, brport_dev,
			     &dsa_slave_चयनdev_blocking_notअगरier,
			     extack);
	अगर (err && err != -EOPNOTSUPP)
		वापस err;

	वापस 0;
पूर्ण

अटल व्योम dsa_port_चयनdev_unsync(काष्ठा dsa_port *dp)
अणु
	/* Configure the port क्रम standalone mode (no address learning,
	 * flood everything).
	 * The bridge only emits SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS events
	 * when the user requests it through netlink or sysfs, but not
	 * स्वतःmatically at port join or leave, so we need to handle resetting
	 * the brport flags ourselves. But we even prefer it that way, because
	 * otherwise, some setups might never get the notअगरication they need,
	 * क्रम example, when a port leaves a LAG that offloads the bridge,
	 * it becomes standalone, but as far as the bridge is concerned, no
	 * port ever left.
	 */
	dsa_port_clear_brport_flags(dp);

	/* Port left the bridge, put in BR_STATE_DISABLED by the bridge layer,
	 * so allow it to be in BR_STATE_FORWARDING to be kept functional
	 */
	dsa_port_set_state_now(dp, BR_STATE_FORWARDING);

	/* VLAN filtering is handled by dsa_चयन_bridge_leave */

	/* Some drivers treat the notअगरication क्रम having a local multicast
	 * router by allowing multicast to be flooded to the CPU, so we should
	 * allow this in standalone mode too.
	 */
	dsa_port_mrouter(dp->cpu_dp, true, शून्य);

	/* Ageing समय may be global to the चयन chip, so करोn't change it
	 * here because we have no good reason (or value) to change it to.
	 */
पूर्ण

पूर्णांक dsa_port_bridge_join(काष्ठा dsa_port *dp, काष्ठा net_device *br,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_notअगरier_bridge_info info = अणु
		.tree_index = dp->ds->dst->index,
		.sw_index = dp->ds->index,
		.port = dp->index,
		.br = br,
	पूर्ण;
	पूर्णांक err;

	/* Here the पूर्णांकerface is alपढ़ोy bridged. Reflect the current
	 * configuration so that drivers can program their chips accordingly.
	 */
	dp->bridge_dev = br;

	err = dsa_broadcast(DSA_NOTIFIER_BRIDGE_JOIN, &info);
	अगर (err)
		जाओ out_rollback;

	err = dsa_port_चयनdev_sync(dp, extack);
	अगर (err)
		जाओ out_rollback_unbridge;

	वापस 0;

out_rollback_unbridge:
	dsa_broadcast(DSA_NOTIFIER_BRIDGE_LEAVE, &info);
out_rollback:
	dp->bridge_dev = शून्य;
	वापस err;
पूर्ण

व्योम dsa_port_bridge_leave(काष्ठा dsa_port *dp, काष्ठा net_device *br)
अणु
	काष्ठा dsa_notअगरier_bridge_info info = अणु
		.tree_index = dp->ds->dst->index,
		.sw_index = dp->ds->index,
		.port = dp->index,
		.br = br,
	पूर्ण;
	पूर्णांक err;

	/* Here the port is alपढ़ोy unbridged. Reflect the current configuration
	 * so that drivers can program their chips accordingly.
	 */
	dp->bridge_dev = शून्य;

	err = dsa_broadcast(DSA_NOTIFIER_BRIDGE_LEAVE, &info);
	अगर (err)
		pr_err("DSA: failed to notify DSA_NOTIFIER_BRIDGE_LEAVE\n");

	dsa_port_चयनdev_unsync(dp);
पूर्ण

पूर्णांक dsa_port_lag_change(काष्ठा dsa_port *dp,
			काष्ठा netdev_lag_lower_state_info *linfo)
अणु
	काष्ठा dsa_notअगरier_lag_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
	पूर्ण;
	bool tx_enabled;

	अगर (!dp->lag_dev)
		वापस 0;

	/* On अटलally configured aggregates (e.g. loadbalance
	 * without LACP) ports will always be tx_enabled, even अगर the
	 * link is करोwn. Thus we require both link_up and tx_enabled
	 * in order to include it in the tx set.
	 */
	tx_enabled = linfo->link_up && linfo->tx_enabled;

	अगर (tx_enabled == dp->lag_tx_enabled)
		वापस 0;

	dp->lag_tx_enabled = tx_enabled;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_LAG_CHANGE, &info);
पूर्ण

पूर्णांक dsa_port_lag_join(काष्ठा dsa_port *dp, काष्ठा net_device *lag,
		      काष्ठा netdev_lag_upper_info *uinfo,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_notअगरier_lag_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.lag = lag,
		.info = uinfo,
	पूर्ण;
	काष्ठा net_device *bridge_dev;
	पूर्णांक err;

	dsa_lag_map(dp->ds->dst, lag);
	dp->lag_dev = lag;

	err = dsa_port_notअगरy(dp, DSA_NOTIFIER_LAG_JOIN, &info);
	अगर (err)
		जाओ err_lag_join;

	bridge_dev = netdev_master_upper_dev_get(lag);
	अगर (!bridge_dev || !netअगर_is_bridge_master(bridge_dev))
		वापस 0;

	err = dsa_port_bridge_join(dp, bridge_dev, extack);
	अगर (err)
		जाओ err_bridge_join;

	वापस 0;

err_bridge_join:
	dsa_port_notअगरy(dp, DSA_NOTIFIER_LAG_LEAVE, &info);
err_lag_join:
	dp->lag_dev = शून्य;
	dsa_lag_unmap(dp->ds->dst, lag);
	वापस err;
पूर्ण

व्योम dsa_port_lag_leave(काष्ठा dsa_port *dp, काष्ठा net_device *lag)
अणु
	काष्ठा dsa_notअगरier_lag_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.lag = lag,
	पूर्ण;
	पूर्णांक err;

	अगर (!dp->lag_dev)
		वापस;

	/* Port might have been part of a LAG that in turn was
	 * attached to a bridge.
	 */
	अगर (dp->bridge_dev)
		dsa_port_bridge_leave(dp, dp->bridge_dev);

	dp->lag_tx_enabled = false;
	dp->lag_dev = शून्य;

	err = dsa_port_notअगरy(dp, DSA_NOTIFIER_LAG_LEAVE, &info);
	अगर (err)
		pr_err("DSA: failed to notify DSA_NOTIFIER_LAG_LEAVE: %d\n",
		       err);

	dsa_lag_unmap(dp->ds->dst, lag);
पूर्ण

/* Must be called under rcu_पढ़ो_lock() */
अटल bool dsa_port_can_apply_vlan_filtering(काष्ठा dsa_port *dp,
					      bool vlan_filtering,
					      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक err, i;

	/* VLAN awareness was off, so the question is "can we turn it on".
	 * We may have had 8021q uppers, those need to go. Make sure we करोn't
	 * enter an inconsistent state: deny changing the VLAN awareness state
	 * as दीर्घ as we have 8021q uppers.
	 */
	अगर (vlan_filtering && dsa_is_user_port(ds, dp->index)) अणु
		काष्ठा net_device *upper_dev, *slave = dp->slave;
		काष्ठा net_device *br = dp->bridge_dev;
		काष्ठा list_head *iter;

		netdev_क्रम_each_upper_dev_rcu(slave, upper_dev, iter) अणु
			काष्ठा bridge_vlan_info br_info;
			u16 vid;

			अगर (!is_vlan_dev(upper_dev))
				जारी;

			vid = vlan_dev_vlan_id(upper_dev);

			/* br_vlan_get_info() वापसs -EINVAL or -ENOENT अगर the
			 * device, respectively the VID is not found, वापसing
			 * 0 means success, which is a failure क्रम us here.
			 */
			err = br_vlan_get_info(br, vid, &br_info);
			अगर (err == 0) अणु
				NL_SET_ERR_MSG_MOD(extack,
						   "Must first remove VLAN uppers having VIDs also present in bridge");
				वापस false;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!ds->vlan_filtering_is_global)
		वापस true;

	/* For हालs where enabling/disabling VLAN awareness is global to the
	 * चयन, we need to handle the हाल where multiple bridges span
	 * dअगरferent ports of the same चयन device and one of them has a
	 * dअगरferent setting than what is being requested.
	 */
	क्रम (i = 0; i < ds->num_ports; i++) अणु
		काष्ठा net_device *other_bridge;

		other_bridge = dsa_to_port(ds, i)->bridge_dev;
		अगर (!other_bridge)
			जारी;
		/* If it's the same bridge, it also has same
		 * vlan_filtering setting => no need to check
		 */
		अगर (other_bridge == dp->bridge_dev)
			जारी;
		अगर (br_vlan_enabled(other_bridge) != vlan_filtering) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "VLAN filtering is a global setting");
			वापस false;
		पूर्ण
	पूर्ण
	वापस true;
पूर्ण

पूर्णांक dsa_port_vlan_filtering(काष्ठा dsa_port *dp, bool vlan_filtering,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	bool apply;
	पूर्णांक err;

	अगर (!ds->ops->port_vlan_filtering)
		वापस -EOPNOTSUPP;

	/* We are called from dsa_slave_चयनdev_blocking_event(),
	 * which is not under rcu_पढ़ो_lock(), unlike
	 * dsa_slave_चयनdev_event().
	 */
	rcu_पढ़ो_lock();
	apply = dsa_port_can_apply_vlan_filtering(dp, vlan_filtering, extack);
	rcu_पढ़ो_unlock();
	अगर (!apply)
		वापस -EINVAL;

	अगर (dsa_port_is_vlan_filtering(dp) == vlan_filtering)
		वापस 0;

	err = ds->ops->port_vlan_filtering(ds, dp->index, vlan_filtering,
					   extack);
	अगर (err)
		वापस err;

	अगर (ds->vlan_filtering_is_global)
		ds->vlan_filtering = vlan_filtering;
	अन्यथा
		dp->vlan_filtering = vlan_filtering;

	वापस 0;
पूर्ण

/* This enक्रमces legacy behavior क्रम चयन drivers which assume they can't
 * receive VLAN configuration when enslaved to a bridge with vlan_filtering=0
 */
bool dsa_port_skip_vlan_configuration(काष्ठा dsa_port *dp)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!dp->bridge_dev)
		वापस false;

	वापस (!ds->configure_vlan_जबतक_not_filtering &&
		!br_vlan_enabled(dp->bridge_dev));
पूर्ण

पूर्णांक dsa_port_ageing_समय(काष्ठा dsa_port *dp, घड़ी_प्रकार ageing_घड़ी)
अणु
	अचिन्हित दीर्घ ageing_jअगरfies = घड़ी_प्रकार_to_jअगरfies(ageing_घड़ी);
	अचिन्हित पूर्णांक ageing_समय = jअगरfies_to_msecs(ageing_jअगरfies);
	काष्ठा dsa_notअगरier_ageing_समय_info info;
	पूर्णांक err;

	info.ageing_समय = ageing_समय;

	err = dsa_port_notअगरy(dp, DSA_NOTIFIER_AGEING_TIME, &info);
	अगर (err)
		वापस err;

	dp->ageing_समय = ageing_समय;

	वापस 0;
पूर्ण

पूर्णांक dsa_port_pre_bridge_flags(स्थिर काष्ठा dsa_port *dp,
			      काष्ठा चयनdev_brport_flags flags,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->port_pre_bridge_flags)
		वापस -EINVAL;

	वापस ds->ops->port_pre_bridge_flags(ds, dp->index, flags, extack);
पूर्ण

पूर्णांक dsa_port_bridge_flags(स्थिर काष्ठा dsa_port *dp,
			  काष्ठा चयनdev_brport_flags flags,
			  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->port_bridge_flags)
		वापस -EOPNOTSUPP;

	वापस ds->ops->port_bridge_flags(ds, dp->index, flags, extack);
पूर्ण

पूर्णांक dsa_port_mrouter(काष्ठा dsa_port *dp, bool mrouter,
		     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->port_set_mrouter)
		वापस -EOPNOTSUPP;

	वापस ds->ops->port_set_mrouter(ds, dp->index, mrouter, extack);
पूर्ण

पूर्णांक dsa_port_mtu_change(काष्ठा dsa_port *dp, पूर्णांक new_mtu,
			bool propagate_upstream)
अणु
	काष्ठा dsa_notअगरier_mtu_info info = अणु
		.sw_index = dp->ds->index,
		.propagate_upstream = propagate_upstream,
		.port = dp->index,
		.mtu = new_mtu,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_MTU, &info);
पूर्ण

पूर्णांक dsa_port_fdb_add(काष्ठा dsa_port *dp, स्थिर अचिन्हित अक्षर *addr,
		     u16 vid)
अणु
	काष्ठा dsa_notअगरier_fdb_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.addr = addr,
		.vid = vid,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_FDB_ADD, &info);
पूर्ण

पूर्णांक dsa_port_fdb_del(काष्ठा dsa_port *dp, स्थिर अचिन्हित अक्षर *addr,
		     u16 vid)
अणु
	काष्ठा dsa_notअगरier_fdb_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.addr = addr,
		.vid = vid,

	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_FDB_DEL, &info);
पूर्ण

पूर्णांक dsa_port_fdb_dump(काष्ठा dsa_port *dp, dsa_fdb_dump_cb_t *cb, व्योम *data)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक port = dp->index;

	अगर (!ds->ops->port_fdb_dump)
		वापस -EOPNOTSUPP;

	वापस ds->ops->port_fdb_dump(ds, port, cb, data);
पूर्ण

पूर्णांक dsa_port_mdb_add(स्थिर काष्ठा dsa_port *dp,
		     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा dsa_notअगरier_mdb_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.mdb = mdb,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_MDB_ADD, &info);
पूर्ण

पूर्णांक dsa_port_mdb_del(स्थिर काष्ठा dsa_port *dp,
		     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा dsa_notअगरier_mdb_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.mdb = mdb,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_MDB_DEL, &info);
पूर्ण

पूर्णांक dsa_port_vlan_add(काष्ठा dsa_port *dp,
		      स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
		      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_notअगरier_vlan_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.vlan = vlan,
		.extack = extack,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_VLAN_ADD, &info);
पूर्ण

पूर्णांक dsa_port_vlan_del(काष्ठा dsa_port *dp,
		      स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा dsa_notअगरier_vlan_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.vlan = vlan,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_VLAN_DEL, &info);
पूर्ण

पूर्णांक dsa_port_mrp_add(स्थिर काष्ठा dsa_port *dp,
		     स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	काष्ठा dsa_notअगरier_mrp_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.mrp = mrp,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_MRP_ADD, &info);
पूर्ण

पूर्णांक dsa_port_mrp_del(स्थिर काष्ठा dsa_port *dp,
		     स्थिर काष्ठा चयनdev_obj_mrp *mrp)
अणु
	काष्ठा dsa_notअगरier_mrp_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.mrp = mrp,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_MRP_DEL, &info);
पूर्ण

पूर्णांक dsa_port_mrp_add_ring_role(स्थिर काष्ठा dsa_port *dp,
			       स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	काष्ठा dsa_notअगरier_mrp_ring_role_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.mrp = mrp,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_MRP_ADD_RING_ROLE, &info);
पूर्ण

पूर्णांक dsa_port_mrp_del_ring_role(स्थिर काष्ठा dsa_port *dp,
			       स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp)
अणु
	काष्ठा dsa_notअगरier_mrp_ring_role_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.mrp = mrp,
	पूर्ण;

	वापस dsa_port_notअगरy(dp, DSA_NOTIFIER_MRP_DEL_RING_ROLE, &info);
पूर्ण

व्योम dsa_port_set_tag_protocol(काष्ठा dsa_port *cpu_dp,
			       स्थिर काष्ठा dsa_device_ops *tag_ops)
अणु
	cpu_dp->filter = tag_ops->filter;
	cpu_dp->rcv = tag_ops->rcv;
	cpu_dp->tag_ops = tag_ops;
पूर्ण

अटल काष्ठा phy_device *dsa_port_get_phy_device(काष्ठा dsa_port *dp)
अणु
	काष्ठा device_node *phy_dn;
	काष्ठा phy_device *phydev;

	phy_dn = of_parse_phandle(dp->dn, "phy-handle", 0);
	अगर (!phy_dn)
		वापस शून्य;

	phydev = of_phy_find_device(phy_dn);
	अगर (!phydev) अणु
		of_node_put(phy_dn);
		वापस ERR_PTR(-EPROBE_DEFER);
	पूर्ण

	of_node_put(phy_dn);
	वापस phydev;
पूर्ण

अटल व्योम dsa_port_phylink_validate(काष्ठा phylink_config *config,
				      अचिन्हित दीर्घ *supported,
				      काष्ठा phylink_link_state *state)
अणु
	काष्ठा dsa_port *dp = container_of(config, काष्ठा dsa_port, pl_config);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->phylink_validate)
		वापस;

	ds->ops->phylink_validate(ds, dp->index, supported, state);
पूर्ण

अटल व्योम dsa_port_phylink_mac_pcs_get_state(काष्ठा phylink_config *config,
					       काष्ठा phylink_link_state *state)
अणु
	काष्ठा dsa_port *dp = container_of(config, काष्ठा dsa_port, pl_config);
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक err;

	/* Only called क्रम inband modes */
	अगर (!ds->ops->phylink_mac_link_state) अणु
		state->link = 0;
		वापस;
	पूर्ण

	err = ds->ops->phylink_mac_link_state(ds, dp->index, state);
	अगर (err < 0) अणु
		dev_err(ds->dev, "p%d: phylink_mac_link_state() failed: %d\n",
			dp->index, err);
		state->link = 0;
	पूर्ण
पूर्ण

अटल व्योम dsa_port_phylink_mac_config(काष्ठा phylink_config *config,
					अचिन्हित पूर्णांक mode,
					स्थिर काष्ठा phylink_link_state *state)
अणु
	काष्ठा dsa_port *dp = container_of(config, काष्ठा dsa_port, pl_config);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->phylink_mac_config)
		वापस;

	ds->ops->phylink_mac_config(ds, dp->index, mode, state);
पूर्ण

अटल व्योम dsa_port_phylink_mac_an_restart(काष्ठा phylink_config *config)
अणु
	काष्ठा dsa_port *dp = container_of(config, काष्ठा dsa_port, pl_config);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->phylink_mac_an_restart)
		वापस;

	ds->ops->phylink_mac_an_restart(ds, dp->index);
पूर्ण

अटल व्योम dsa_port_phylink_mac_link_करोwn(काष्ठा phylink_config *config,
					   अचिन्हित पूर्णांक mode,
					   phy_पूर्णांकerface_t पूर्णांकerface)
अणु
	काष्ठा dsa_port *dp = container_of(config, काष्ठा dsa_port, pl_config);
	काष्ठा phy_device *phydev = शून्य;
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (dsa_is_user_port(ds, dp->index))
		phydev = dp->slave->phydev;

	अगर (!ds->ops->phylink_mac_link_करोwn) अणु
		अगर (ds->ops->adjust_link && phydev)
			ds->ops->adjust_link(ds, dp->index, phydev);
		वापस;
	पूर्ण

	ds->ops->phylink_mac_link_करोwn(ds, dp->index, mode, पूर्णांकerface);
पूर्ण

अटल व्योम dsa_port_phylink_mac_link_up(काष्ठा phylink_config *config,
					 काष्ठा phy_device *phydev,
					 अचिन्हित पूर्णांक mode,
					 phy_पूर्णांकerface_t पूर्णांकerface,
					 पूर्णांक speed, पूर्णांक duplex,
					 bool tx_छोड़ो, bool rx_छोड़ो)
अणु
	काष्ठा dsa_port *dp = container_of(config, काष्ठा dsa_port, pl_config);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->phylink_mac_link_up) अणु
		अगर (ds->ops->adjust_link && phydev)
			ds->ops->adjust_link(ds, dp->index, phydev);
		वापस;
	पूर्ण

	ds->ops->phylink_mac_link_up(ds, dp->index, mode, पूर्णांकerface, phydev,
				     speed, duplex, tx_छोड़ो, rx_छोड़ो);
पूर्ण

स्थिर काष्ठा phylink_mac_ops dsa_port_phylink_mac_ops = अणु
	.validate = dsa_port_phylink_validate,
	.mac_pcs_get_state = dsa_port_phylink_mac_pcs_get_state,
	.mac_config = dsa_port_phylink_mac_config,
	.mac_an_restart = dsa_port_phylink_mac_an_restart,
	.mac_link_करोwn = dsa_port_phylink_mac_link_करोwn,
	.mac_link_up = dsa_port_phylink_mac_link_up,
पूर्ण;

अटल पूर्णांक dsa_port_setup_phy_of(काष्ठा dsa_port *dp, bool enable)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा phy_device *phydev;
	पूर्णांक port = dp->index;
	पूर्णांक err = 0;

	phydev = dsa_port_get_phy_device(dp);
	अगर (!phydev)
		वापस 0;

	अगर (IS_ERR(phydev))
		वापस PTR_ERR(phydev);

	अगर (enable) अणु
		err = genphy_resume(phydev);
		अगर (err < 0)
			जाओ err_put_dev;

		err = genphy_पढ़ो_status(phydev);
		अगर (err < 0)
			जाओ err_put_dev;
	पूर्ण अन्यथा अणु
		err = genphy_suspend(phydev);
		अगर (err < 0)
			जाओ err_put_dev;
	पूर्ण

	अगर (ds->ops->adjust_link)
		ds->ops->adjust_link(ds, port, phydev);

	dev_dbg(ds->dev, "enabled port's phy: %s", phydev_name(phydev));

err_put_dev:
	put_device(&phydev->mdio.dev);
	वापस err;
पूर्ण

अटल पूर्णांक dsa_port_fixed_link_रेजिस्टर_of(काष्ठा dsa_port *dp)
अणु
	काष्ठा device_node *dn = dp->dn;
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा phy_device *phydev;
	पूर्णांक port = dp->index;
	phy_पूर्णांकerface_t mode;
	पूर्णांक err;

	err = of_phy_रेजिस्टर_fixed_link(dn);
	अगर (err) अणु
		dev_err(ds->dev,
			"failed to register the fixed PHY of port %d\n",
			port);
		वापस err;
	पूर्ण

	phydev = of_phy_find_device(dn);

	err = of_get_phy_mode(dn, &mode);
	अगर (err)
		mode = PHY_INTERFACE_MODE_NA;
	phydev->पूर्णांकerface = mode;

	genphy_पढ़ो_status(phydev);

	अगर (ds->ops->adjust_link)
		ds->ops->adjust_link(ds, port, phydev);

	put_device(&phydev->mdio.dev);

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_port_phylink_रेजिस्टर(काष्ठा dsa_port *dp)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा device_node *port_dn = dp->dn;
	phy_पूर्णांकerface_t mode;
	पूर्णांक err;

	err = of_get_phy_mode(port_dn, &mode);
	अगर (err)
		mode = PHY_INTERFACE_MODE_NA;

	dp->pl_config.dev = ds->dev;
	dp->pl_config.type = PHYLINK_DEV;
	dp->pl_config.pcs_poll = ds->pcs_poll;

	dp->pl = phylink_create(&dp->pl_config, of_fwnode_handle(port_dn),
				mode, &dsa_port_phylink_mac_ops);
	अगर (IS_ERR(dp->pl)) अणु
		pr_err("error creating PHYLINK: %ld\n", PTR_ERR(dp->pl));
		वापस PTR_ERR(dp->pl);
	पूर्ण

	err = phylink_of_phy_connect(dp->pl, port_dn, 0);
	अगर (err && err != -ENODEV) अणु
		pr_err("could not attach to PHY: %d\n", err);
		जाओ err_phy_connect;
	पूर्ण

	वापस 0;

err_phy_connect:
	phylink_destroy(dp->pl);
	वापस err;
पूर्ण

पूर्णांक dsa_port_link_रेजिस्टर_of(काष्ठा dsa_port *dp)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा device_node *phy_np;
	पूर्णांक port = dp->index;

	अगर (!ds->ops->adjust_link) अणु
		phy_np = of_parse_phandle(dp->dn, "phy-handle", 0);
		अगर (of_phy_is_fixed_link(dp->dn) || phy_np) अणु
			अगर (ds->ops->phylink_mac_link_करोwn)
				ds->ops->phylink_mac_link_करोwn(ds, port,
					MLO_AN_FIXED, PHY_INTERFACE_MODE_NA);
			वापस dsa_port_phylink_रेजिस्टर(dp);
		पूर्ण
		वापस 0;
	पूर्ण

	dev_warn(ds->dev,
		 "Using legacy PHYLIB callbacks. Please migrate to PHYLINK!\n");

	अगर (of_phy_is_fixed_link(dp->dn))
		वापस dsa_port_fixed_link_रेजिस्टर_of(dp);
	अन्यथा
		वापस dsa_port_setup_phy_of(dp, true);
पूर्ण

व्योम dsa_port_link_unरेजिस्टर_of(काष्ठा dsa_port *dp)
अणु
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->adjust_link && dp->pl) अणु
		rtnl_lock();
		phylink_disconnect_phy(dp->pl);
		rtnl_unlock();
		phylink_destroy(dp->pl);
		dp->pl = शून्य;
		वापस;
	पूर्ण

	अगर (of_phy_is_fixed_link(dp->dn))
		of_phy_deरेजिस्टर_fixed_link(dp->dn);
	अन्यथा
		dsa_port_setup_phy_of(dp, false);
पूर्ण

पूर्णांक dsa_port_get_phy_strings(काष्ठा dsa_port *dp, uपूर्णांक8_t *data)
अणु
	काष्ठा phy_device *phydev;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (of_phy_is_fixed_link(dp->dn))
		वापस ret;

	phydev = dsa_port_get_phy_device(dp);
	अगर (IS_ERR_OR_शून्य(phydev))
		वापस ret;

	ret = phy_ethtool_get_strings(phydev, data);
	put_device(&phydev->mdio.dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_port_get_phy_strings);

पूर्णांक dsa_port_get_ethtool_phy_stats(काष्ठा dsa_port *dp, uपूर्णांक64_t *data)
अणु
	काष्ठा phy_device *phydev;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (of_phy_is_fixed_link(dp->dn))
		वापस ret;

	phydev = dsa_port_get_phy_device(dp);
	अगर (IS_ERR_OR_शून्य(phydev))
		वापस ret;

	ret = phy_ethtool_get_stats(phydev, शून्य, data);
	put_device(&phydev->mdio.dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_port_get_ethtool_phy_stats);

पूर्णांक dsa_port_get_phy_sset_count(काष्ठा dsa_port *dp)
अणु
	काष्ठा phy_device *phydev;
	पूर्णांक ret = -EOPNOTSUPP;

	अगर (of_phy_is_fixed_link(dp->dn))
		वापस ret;

	phydev = dsa_port_get_phy_device(dp);
	अगर (IS_ERR_OR_शून्य(phydev))
		वापस ret;

	ret = phy_ethtool_get_sset_count(phydev);
	put_device(&phydev->mdio.dev);

	वापस ret;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_port_get_phy_sset_count);

पूर्णांक dsa_port_hsr_join(काष्ठा dsa_port *dp, काष्ठा net_device *hsr)
अणु
	काष्ठा dsa_notअगरier_hsr_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.hsr = hsr,
	पूर्ण;
	पूर्णांक err;

	dp->hsr_dev = hsr;

	err = dsa_port_notअगरy(dp, DSA_NOTIFIER_HSR_JOIN, &info);
	अगर (err)
		dp->hsr_dev = शून्य;

	वापस err;
पूर्ण

व्योम dsa_port_hsr_leave(काष्ठा dsa_port *dp, काष्ठा net_device *hsr)
अणु
	काष्ठा dsa_notअगरier_hsr_info info = अणु
		.sw_index = dp->ds->index,
		.port = dp->index,
		.hsr = hsr,
	पूर्ण;
	पूर्णांक err;

	dp->hsr_dev = शून्य;

	err = dsa_port_notअगरy(dp, DSA_NOTIFIER_HSR_LEAVE, &info);
	अगर (err)
		pr_err("DSA: failed to notify DSA_NOTIFIER_HSR_LEAVE\n");
पूर्ण
