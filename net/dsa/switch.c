<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * Handling of a single चयन chip, part of a चयन fabric
 *
 * Copyright (c) 2017 Savoir-faire Linux Inc.
 *	Vivien Didelot <vivien.didelot@savoirfairelinux.com>
 */

#समावेश <linux/अगर_bridge.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/notअगरier.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/चयनdev.h>

#समावेश "dsa_priv.h"

अटल अचिन्हित पूर्णांक dsa_चयन_fastest_ageing_समय(काष्ठा dsa_चयन *ds,
						   अचिन्हित पूर्णांक ageing_समय)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ds->num_ports; ++i) अणु
		काष्ठा dsa_port *dp = dsa_to_port(ds, i);

		अगर (dp->ageing_समय && dp->ageing_समय < ageing_समय)
			ageing_समय = dp->ageing_समय;
	पूर्ण

	वापस ageing_समय;
पूर्ण

अटल पूर्णांक dsa_चयन_ageing_समय(काष्ठा dsa_चयन *ds,
				  काष्ठा dsa_notअगरier_ageing_समय_info *info)
अणु
	अचिन्हित पूर्णांक ageing_समय = info->ageing_समय;

	अगर (ds->ageing_समय_min && ageing_समय < ds->ageing_समय_min)
		वापस -दुस्फल;

	अगर (ds->ageing_समय_max && ageing_समय > ds->ageing_समय_max)
		वापस -दुस्फल;

	/* Program the fastest ageing समय in हाल of multiple bridges */
	ageing_समय = dsa_चयन_fastest_ageing_समय(ds, ageing_समय);

	अगर (ds->ops->set_ageing_समय)
		वापस ds->ops->set_ageing_समय(ds, ageing_समय);

	वापस 0;
पूर्ण

अटल bool dsa_चयन_mtu_match(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा dsa_notअगरier_mtu_info *info)
अणु
	अगर (ds->index == info->sw_index)
		वापस (port == info->port) || dsa_is_dsa_port(ds, port);

	अगर (!info->propagate_upstream)
		वापस false;

	अगर (dsa_is_dsa_port(ds, port) || dsa_is_cpu_port(ds, port))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक dsa_चयन_mtu(काष्ठा dsa_चयन *ds,
			  काष्ठा dsa_notअगरier_mtu_info *info)
अणु
	पूर्णांक port, ret;

	अगर (!ds->ops->port_change_mtu)
		वापस -EOPNOTSUPP;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_चयन_mtu_match(ds, port, info)) अणु
			ret = ds->ops->port_change_mtu(ds, port, info->mtu);
			अगर (ret)
				वापस ret;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_bridge_join(काष्ठा dsa_चयन *ds,
				  काष्ठा dsa_notअगरier_bridge_info *info)
अणु
	काष्ठा dsa_चयन_tree *dst = ds->dst;

	अगर (dst->index == info->tree_index && ds->index == info->sw_index &&
	    ds->ops->port_bridge_join)
		वापस ds->ops->port_bridge_join(ds, info->port, info->br);

	अगर ((dst->index != info->tree_index || ds->index != info->sw_index) &&
	    ds->ops->crosschip_bridge_join)
		वापस ds->ops->crosschip_bridge_join(ds, info->tree_index,
						      info->sw_index,
						      info->port, info->br);

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_bridge_leave(काष्ठा dsa_चयन *ds,
				   काष्ठा dsa_notअगरier_bridge_info *info)
अणु
	bool unset_vlan_filtering = br_vlan_enabled(info->br);
	काष्ठा dsa_चयन_tree *dst = ds->dst;
	काष्ठा netlink_ext_ack extack = अणु0पूर्ण;
	पूर्णांक err, port;

	अगर (dst->index == info->tree_index && ds->index == info->sw_index &&
	    ds->ops->port_bridge_join)
		ds->ops->port_bridge_leave(ds, info->port, info->br);

	अगर ((dst->index != info->tree_index || ds->index != info->sw_index) &&
	    ds->ops->crosschip_bridge_join)
		ds->ops->crosschip_bridge_leave(ds, info->tree_index,
						info->sw_index, info->port,
						info->br);

	/* If the bridge was vlan_filtering, the bridge core करोesn't trigger an
	 * event क्रम changing vlan_filtering setting upon slave ports leaving
	 * it. That is a good thing, because that lets us handle it and also
	 * handle the हाल where the चयन's vlan_filtering setting is global
	 * (not per port). When that happens, the correct moment to trigger the
	 * vlan_filtering callback is only when the last port leaves the last
	 * VLAN-aware bridge.
	 */
	अगर (unset_vlan_filtering && ds->vlan_filtering_is_global) अणु
		क्रम (port = 0; port < ds->num_ports; port++) अणु
			काष्ठा net_device *bridge_dev;

			bridge_dev = dsa_to_port(ds, port)->bridge_dev;

			अगर (bridge_dev && br_vlan_enabled(bridge_dev)) अणु
				unset_vlan_filtering = false;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (unset_vlan_filtering) अणु
		err = dsa_port_vlan_filtering(dsa_to_port(ds, info->port),
					      false, &extack);
		अगर (extack._msg)
			dev_err(ds->dev, "port %d: %s\n", info->port,
				extack._msg);
		अगर (err && err != EOPNOTSUPP)
			वापस err;
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_fdb_add(काष्ठा dsa_चयन *ds,
			      काष्ठा dsa_notअगरier_fdb_info *info)
अणु
	पूर्णांक port = dsa_towards_port(ds, info->sw_index, info->port);

	अगर (!ds->ops->port_fdb_add)
		वापस -EOPNOTSUPP;

	वापस ds->ops->port_fdb_add(ds, port, info->addr, info->vid);
पूर्ण

अटल पूर्णांक dsa_चयन_fdb_del(काष्ठा dsa_चयन *ds,
			      काष्ठा dsa_notअगरier_fdb_info *info)
अणु
	पूर्णांक port = dsa_towards_port(ds, info->sw_index, info->port);

	अगर (!ds->ops->port_fdb_del)
		वापस -EOPNOTSUPP;

	वापस ds->ops->port_fdb_del(ds, port, info->addr, info->vid);
पूर्ण

अटल पूर्णांक dsa_चयन_hsr_join(काष्ठा dsa_चयन *ds,
			       काष्ठा dsa_notअगरier_hsr_info *info)
अणु
	अगर (ds->index == info->sw_index && ds->ops->port_hsr_join)
		वापस ds->ops->port_hsr_join(ds, info->port, info->hsr);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक dsa_चयन_hsr_leave(काष्ठा dsa_चयन *ds,
				काष्ठा dsa_notअगरier_hsr_info *info)
अणु
	अगर (ds->index == info->sw_index && ds->ops->port_hsr_leave)
		वापस ds->ops->port_hsr_leave(ds, info->port, info->hsr);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक dsa_चयन_lag_change(काष्ठा dsa_चयन *ds,
				 काष्ठा dsa_notअगरier_lag_info *info)
अणु
	अगर (ds->index == info->sw_index && ds->ops->port_lag_change)
		वापस ds->ops->port_lag_change(ds, info->port);

	अगर (ds->index != info->sw_index && ds->ops->crosschip_lag_change)
		वापस ds->ops->crosschip_lag_change(ds, info->sw_index,
						     info->port);

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_lag_join(काष्ठा dsa_चयन *ds,
			       काष्ठा dsa_notअगरier_lag_info *info)
अणु
	अगर (ds->index == info->sw_index && ds->ops->port_lag_join)
		वापस ds->ops->port_lag_join(ds, info->port, info->lag,
					      info->info);

	अगर (ds->index != info->sw_index && ds->ops->crosschip_lag_join)
		वापस ds->ops->crosschip_lag_join(ds, info->sw_index,
						   info->port, info->lag,
						   info->info);

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_lag_leave(काष्ठा dsa_चयन *ds,
				काष्ठा dsa_notअगरier_lag_info *info)
अणु
	अगर (ds->index == info->sw_index && ds->ops->port_lag_leave)
		वापस ds->ops->port_lag_leave(ds, info->port, info->lag);

	अगर (ds->index != info->sw_index && ds->ops->crosschip_lag_leave)
		वापस ds->ops->crosschip_lag_leave(ds, info->sw_index,
						    info->port, info->lag);

	वापस 0;
पूर्ण

अटल bool dsa_चयन_mdb_match(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा dsa_notअगरier_mdb_info *info)
अणु
	अगर (ds->index == info->sw_index && port == info->port)
		वापस true;

	अगर (dsa_is_dsa_port(ds, port))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक dsa_चयन_mdb_add(काष्ठा dsa_चयन *ds,
			      काष्ठा dsa_notअगरier_mdb_info *info)
अणु
	पूर्णांक err = 0;
	पूर्णांक port;

	अगर (!ds->ops->port_mdb_add)
		वापस -EOPNOTSUPP;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_चयन_mdb_match(ds, port, info)) अणु
			err = ds->ops->port_mdb_add(ds, port, info->mdb);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dsa_चयन_mdb_del(काष्ठा dsa_चयन *ds,
			      काष्ठा dsa_notअगरier_mdb_info *info)
अणु
	अगर (!ds->ops->port_mdb_del)
		वापस -EOPNOTSUPP;

	अगर (ds->index == info->sw_index)
		वापस ds->ops->port_mdb_del(ds, info->port, info->mdb);

	वापस 0;
पूर्ण

अटल bool dsa_चयन_vlan_match(काष्ठा dsa_चयन *ds, पूर्णांक port,
				  काष्ठा dsa_notअगरier_vlan_info *info)
अणु
	अगर (ds->index == info->sw_index && port == info->port)
		वापस true;

	अगर (dsa_is_dsa_port(ds, port))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक dsa_चयन_vlan_add(काष्ठा dsa_चयन *ds,
			       काष्ठा dsa_notअगरier_vlan_info *info)
अणु
	पूर्णांक port, err;

	अगर (!ds->ops->port_vlan_add)
		वापस -EOPNOTSUPP;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_चयन_vlan_match(ds, port, info)) अणु
			err = ds->ops->port_vlan_add(ds, port, info->vlan,
						     info->extack);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_vlan_del(काष्ठा dsa_चयन *ds,
			       काष्ठा dsa_notअगरier_vlan_info *info)
अणु
	अगर (!ds->ops->port_vlan_del)
		वापस -EOPNOTSUPP;

	अगर (ds->index == info->sw_index)
		वापस ds->ops->port_vlan_del(ds, info->port, info->vlan);

	/* Do not deprogram the DSA links as they may be used as conduit
	 * क्रम other VLAN members in the fabric.
	 */
	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_change_tag_proto(काष्ठा dsa_चयन *ds,
				       काष्ठा dsa_notअगरier_tag_proto_info *info)
अणु
	स्थिर काष्ठा dsa_device_ops *tag_ops = info->tag_ops;
	पूर्णांक port, err;

	अगर (!ds->ops->change_tag_protocol)
		वापस -EOPNOTSUPP;

	ASSERT_RTNL();

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (!dsa_is_cpu_port(ds, port))
			जारी;

		err = ds->ops->change_tag_protocol(ds, port, tag_ops->proto);
		अगर (err)
			वापस err;

		dsa_port_set_tag_protocol(dsa_to_port(ds, port), tag_ops);
	पूर्ण

	/* Now that changing the tag protocol can no दीर्घer fail, let's update
	 * the reमुख्यing bits which are "duplicated for faster access", and the
	 * bits that depend on the tagger, such as the MTU.
	 */
	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_is_user_port(ds, port)) अणु
			काष्ठा net_device *slave;

			slave = dsa_to_port(ds, port)->slave;
			dsa_slave_setup_tagger(slave);

			/* rtnl_mutex is held in dsa_tree_change_tag_proto */
			dsa_slave_change_mtu(slave, slave->mtu);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल bool dsa_चयन_mrp_match(काष्ठा dsa_चयन *ds, पूर्णांक port,
				 काष्ठा dsa_notअगरier_mrp_info *info)
अणु
	अगर (ds->index == info->sw_index && port == info->port)
		वापस true;

	अगर (dsa_is_dsa_port(ds, port))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक dsa_चयन_mrp_add(काष्ठा dsa_चयन *ds,
			      काष्ठा dsa_notअगरier_mrp_info *info)
अणु
	पूर्णांक err = 0;
	पूर्णांक port;

	अगर (!ds->ops->port_mrp_add)
		वापस -EOPNOTSUPP;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_चयन_mrp_match(ds, port, info)) अणु
			err = ds->ops->port_mrp_add(ds, port, info->mrp);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dsa_चयन_mrp_del(काष्ठा dsa_चयन *ds,
			      काष्ठा dsa_notअगरier_mrp_info *info)
अणु
	अगर (!ds->ops->port_mrp_del)
		वापस -EOPNOTSUPP;

	अगर (ds->index == info->sw_index)
		वापस ds->ops->port_mrp_del(ds, info->port, info->mrp);

	वापस 0;
पूर्ण

अटल bool
dsa_चयन_mrp_ring_role_match(काष्ठा dsa_चयन *ds, पूर्णांक port,
			       काष्ठा dsa_notअगरier_mrp_ring_role_info *info)
अणु
	अगर (ds->index == info->sw_index && port == info->port)
		वापस true;

	अगर (dsa_is_dsa_port(ds, port))
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक
dsa_चयन_mrp_add_ring_role(काष्ठा dsa_चयन *ds,
			     काष्ठा dsa_notअगरier_mrp_ring_role_info *info)
अणु
	पूर्णांक err = 0;
	पूर्णांक port;

	अगर (!ds->ops->port_mrp_add)
		वापस -EOPNOTSUPP;

	क्रम (port = 0; port < ds->num_ports; port++) अणु
		अगर (dsa_चयन_mrp_ring_role_match(ds, port, info)) अणु
			err = ds->ops->port_mrp_add_ring_role(ds, port,
							      info->mrp);
			अगर (err)
				अवरोध;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
dsa_चयन_mrp_del_ring_role(काष्ठा dsa_चयन *ds,
			     काष्ठा dsa_notअगरier_mrp_ring_role_info *info)
अणु
	अगर (!ds->ops->port_mrp_del)
		वापस -EOPNOTSUPP;

	अगर (ds->index == info->sw_index)
		वापस ds->ops->port_mrp_del_ring_role(ds, info->port,
						       info->mrp);

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_चयन_event(काष्ठा notअगरier_block *nb,
			    अचिन्हित दीर्घ event, व्योम *info)
अणु
	काष्ठा dsa_चयन *ds = container_of(nb, काष्ठा dsa_चयन, nb);
	पूर्णांक err;

	चयन (event) अणु
	हाल DSA_NOTIFIER_AGEING_TIME:
		err = dsa_चयन_ageing_समय(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_BRIDGE_JOIN:
		err = dsa_चयन_bridge_join(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_BRIDGE_LEAVE:
		err = dsa_चयन_bridge_leave(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_FDB_ADD:
		err = dsa_चयन_fdb_add(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_FDB_DEL:
		err = dsa_चयन_fdb_del(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_HSR_JOIN:
		err = dsa_चयन_hsr_join(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_HSR_LEAVE:
		err = dsa_चयन_hsr_leave(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_LAG_CHANGE:
		err = dsa_चयन_lag_change(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_LAG_JOIN:
		err = dsa_चयन_lag_join(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_LAG_LEAVE:
		err = dsa_चयन_lag_leave(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_MDB_ADD:
		err = dsa_चयन_mdb_add(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_MDB_DEL:
		err = dsa_चयन_mdb_del(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_VLAN_ADD:
		err = dsa_चयन_vlan_add(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_VLAN_DEL:
		err = dsa_चयन_vlan_del(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_MTU:
		err = dsa_चयन_mtu(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_TAG_PROTO:
		err = dsa_चयन_change_tag_proto(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_MRP_ADD:
		err = dsa_चयन_mrp_add(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_MRP_DEL:
		err = dsa_चयन_mrp_del(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_MRP_ADD_RING_ROLE:
		err = dsa_चयन_mrp_add_ring_role(ds, info);
		अवरोध;
	हाल DSA_NOTIFIER_MRP_DEL_RING_ROLE:
		err = dsa_चयन_mrp_del_ring_role(ds, info);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	अगर (err)
		dev_dbg(ds->dev, "breaking chain for DSA event %lu (%d)\n",
			event, err);

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

पूर्णांक dsa_चयन_रेजिस्टर_notअगरier(काष्ठा dsa_चयन *ds)
अणु
	ds->nb.notअगरier_call = dsa_चयन_event;

	वापस raw_notअगरier_chain_रेजिस्टर(&ds->dst->nh, &ds->nb);
पूर्ण

व्योम dsa_चयन_unरेजिस्टर_notअगरier(काष्ठा dsa_चयन *ds)
अणु
	पूर्णांक err;

	err = raw_notअगरier_chain_unरेजिस्टर(&ds->dst->nh, &ds->nb);
	अगर (err)
		dev_err(ds->dev, "failed to unregister notifier (%d)\n", err);
पूर्ण
