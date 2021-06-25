<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2015-2018 Mellanox Technologies. All rights reserved */

#समावेश <linux/kernel.h>
#समावेश <linux/types.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/slab.h>
#समावेश <linux/device.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/netlink.h>
#समावेश <net/चयनdev.h>
#समावेश <net/vxlan.h>

#समावेश "spectrum_span.h"
#समावेश "spectrum_switchdev.h"
#समावेश "spectrum.h"
#समावेश "core.h"
#समावेश "reg.h"

काष्ठा mlxsw_sp_bridge_ops;

काष्ठा mlxsw_sp_bridge अणु
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा अणु
		काष्ठा delayed_work dw;
#घोषणा MLXSW_SP_DEFAULT_LEARNING_INTERVAL 100
		अचिन्हित पूर्णांक पूर्णांकerval; /* ms */
	पूर्ण fdb_notअगरy;
#घोषणा MLXSW_SP_MIN_AGEING_TIME 10
#घोषणा MLXSW_SP_MAX_AGEING_TIME 1000000
#घोषणा MLXSW_SP_DEFAULT_AGEING_TIME 300
	u32 ageing_समय;
	bool vlan_enabled_exists;
	काष्ठा list_head bridges_list;
	DECLARE_BITMAP(mids_biपंचांगap, MLXSW_SP_MID_MAX);
	स्थिर काष्ठा mlxsw_sp_bridge_ops *bridge_8021q_ops;
	स्थिर काष्ठा mlxsw_sp_bridge_ops *bridge_8021d_ops;
	स्थिर काष्ठा mlxsw_sp_bridge_ops *bridge_8021ad_ops;
पूर्ण;

काष्ठा mlxsw_sp_bridge_device अणु
	काष्ठा net_device *dev;
	काष्ठा list_head list;
	काष्ठा list_head ports_list;
	काष्ठा list_head mids_list;
	u8 vlan_enabled:1,
	   multicast_enabled:1,
	   mrouter:1;
	स्थिर काष्ठा mlxsw_sp_bridge_ops *ops;
पूर्ण;

काष्ठा mlxsw_sp_bridge_port अणु
	काष्ठा net_device *dev;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा list_head list;
	काष्ठा list_head vlans_list;
	अचिन्हित पूर्णांक ref_count;
	u8 stp_state;
	अचिन्हित दीर्घ flags;
	bool mrouter;
	bool lagged;
	जोड़ अणु
		u16 lag_id;
		u16 प्रणाली_port;
	पूर्ण;
पूर्ण;

काष्ठा mlxsw_sp_bridge_vlan अणु
	काष्ठा list_head list;
	काष्ठा list_head port_vlan_list;
	u16 vid;
पूर्ण;

काष्ठा mlxsw_sp_bridge_ops अणु
	पूर्णांक (*port_join)(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			 काष्ठा mlxsw_sp_bridge_port *bridge_port,
			 काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			 काष्ठा netlink_ext_ack *extack);
	व्योम (*port_leave)(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			   काष्ठा mlxsw_sp_bridge_port *bridge_port,
			   काष्ठा mlxsw_sp_port *mlxsw_sp_port);
	पूर्णांक (*vxlan_join)(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			  स्थिर काष्ठा net_device *vxlan_dev, u16 vid,
			  काष्ठा netlink_ext_ack *extack);
	काष्ठा mlxsw_sp_fid *
		(*fid_get)(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			   u16 vid, काष्ठा netlink_ext_ack *extack);
	काष्ठा mlxsw_sp_fid *
		(*fid_lookup)(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			      u16 vid);
	u16 (*fid_vid)(काष्ठा mlxsw_sp_bridge_device *bridge_device,
		       स्थिर काष्ठा mlxsw_sp_fid *fid);
पूर्ण;

काष्ठा mlxsw_sp_चयनdev_ops अणु
	व्योम (*init)(काष्ठा mlxsw_sp *mlxsw_sp);
पूर्ण;

अटल पूर्णांक
mlxsw_sp_bridge_port_fdb_flush(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_bridge_port *bridge_port,
			       u16 fid_index);

अटल व्योम
mlxsw_sp_bridge_port_mdb_flush(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       काष्ठा mlxsw_sp_bridge_port *bridge_port);

अटल व्योम
mlxsw_sp_bridge_mdb_mc_enable_sync(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा mlxsw_sp_bridge_device
				   *bridge_device);

अटल व्योम
mlxsw_sp_port_mrouter_update_mdb(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 काष्ठा mlxsw_sp_bridge_port *bridge_port,
				 bool add);

अटल काष्ठा mlxsw_sp_bridge_device *
mlxsw_sp_bridge_device_find(स्थिर काष्ठा mlxsw_sp_bridge *bridge,
			    स्थिर काष्ठा net_device *br_dev)
अणु
	काष्ठा mlxsw_sp_bridge_device *bridge_device;

	list_क्रम_each_entry(bridge_device, &bridge->bridges_list, list)
		अगर (bridge_device->dev == br_dev)
			वापस bridge_device;

	वापस शून्य;
पूर्ण

bool mlxsw_sp_bridge_device_is_offloaded(स्थिर काष्ठा mlxsw_sp *mlxsw_sp,
					 स्थिर काष्ठा net_device *br_dev)
अणु
	वापस !!mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
पूर्ण

अटल पूर्णांक mlxsw_sp_bridge_device_upper_rअगर_destroy(काष्ठा net_device *dev,
						    काष्ठा netdev_nested_priv *priv)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = priv->data;

	mlxsw_sp_rअगर_destroy_by_dev(mlxsw_sp, dev);
	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_bridge_device_rअगरs_destroy(काष्ठा mlxsw_sp *mlxsw_sp,
						काष्ठा net_device *dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = (व्योम *)mlxsw_sp,
	पूर्ण;

	mlxsw_sp_rअगर_destroy_by_dev(mlxsw_sp, dev);
	netdev_walk_all_upper_dev_rcu(dev,
				      mlxsw_sp_bridge_device_upper_rअगर_destroy,
				      &priv);
पूर्ण

अटल पूर्णांक mlxsw_sp_bridge_device_vxlan_init(काष्ठा mlxsw_sp_bridge *bridge,
					     काष्ठा net_device *br_dev,
					     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *dev, *stop_dev;
	काष्ठा list_head *iter;
	पूर्णांक err;

	netdev_क्रम_each_lower_dev(br_dev, dev, iter) अणु
		अगर (netअगर_is_vxlan(dev) && netअगर_running(dev)) अणु
			err = mlxsw_sp_bridge_vxlan_join(bridge->mlxsw_sp,
							 br_dev, dev, 0,
							 extack);
			अगर (err) अणु
				stop_dev = dev;
				जाओ err_vxlan_join;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;

err_vxlan_join:
	netdev_क्रम_each_lower_dev(br_dev, dev, iter) अणु
		अगर (netअगर_is_vxlan(dev) && netअगर_running(dev)) अणु
			अगर (stop_dev == dev)
				अवरोध;
			mlxsw_sp_bridge_vxlan_leave(bridge->mlxsw_sp, dev);
		पूर्ण
	पूर्ण
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_bridge_device_vxlan_fini(काष्ठा mlxsw_sp_bridge *bridge,
					      काष्ठा net_device *br_dev)
अणु
	काष्ठा net_device *dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_lower_dev(br_dev, dev, iter) अणु
		अगर (netअगर_is_vxlan(dev) && netअगर_running(dev))
			mlxsw_sp_bridge_vxlan_leave(bridge->mlxsw_sp, dev);
	पूर्ण
पूर्ण

अटल काष्ठा mlxsw_sp_bridge_device *
mlxsw_sp_bridge_device_create(काष्ठा mlxsw_sp_bridge *bridge,
			      काष्ठा net_device *br_dev,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा device *dev = bridge->mlxsw_sp->bus_info->dev;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	bool vlan_enabled = br_vlan_enabled(br_dev);
	पूर्णांक err;

	अगर (vlan_enabled && bridge->vlan_enabled_exists) अणु
		dev_err(dev, "Only one VLAN-aware bridge is supported\n");
		NL_SET_ERR_MSG_MOD(extack, "Only one VLAN-aware bridge is supported");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	bridge_device = kzalloc(माप(*bridge_device), GFP_KERNEL);
	अगर (!bridge_device)
		वापस ERR_PTR(-ENOMEM);

	bridge_device->dev = br_dev;
	bridge_device->vlan_enabled = vlan_enabled;
	bridge_device->multicast_enabled = br_multicast_enabled(br_dev);
	bridge_device->mrouter = br_multicast_router(br_dev);
	INIT_LIST_HEAD(&bridge_device->ports_list);
	अगर (vlan_enabled) अणु
		u16 proto;

		bridge->vlan_enabled_exists = true;
		br_vlan_get_proto(br_dev, &proto);
		अगर (proto == ETH_P_8021AD)
			bridge_device->ops = bridge->bridge_8021ad_ops;
		अन्यथा
			bridge_device->ops = bridge->bridge_8021q_ops;
	पूर्ण अन्यथा अणु
		bridge_device->ops = bridge->bridge_8021d_ops;
	पूर्ण
	INIT_LIST_HEAD(&bridge_device->mids_list);
	list_add(&bridge_device->list, &bridge->bridges_list);

	/* It is possible we alपढ़ोy have VXLAN devices enslaved to the bridge.
	 * In which हाल, we need to replay their configuration as अगर they were
	 * just now enslaved to the bridge.
	 */
	err = mlxsw_sp_bridge_device_vxlan_init(bridge, br_dev, extack);
	अगर (err)
		जाओ err_vxlan_init;

	वापस bridge_device;

err_vxlan_init:
	list_del(&bridge_device->list);
	अगर (bridge_device->vlan_enabled)
		bridge->vlan_enabled_exists = false;
	kमुक्त(bridge_device);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
mlxsw_sp_bridge_device_destroy(काष्ठा mlxsw_sp_bridge *bridge,
			       काष्ठा mlxsw_sp_bridge_device *bridge_device)
अणु
	mlxsw_sp_bridge_device_vxlan_fini(bridge, bridge_device->dev);
	mlxsw_sp_bridge_device_rअगरs_destroy(bridge->mlxsw_sp,
					    bridge_device->dev);
	list_del(&bridge_device->list);
	अगर (bridge_device->vlan_enabled)
		bridge->vlan_enabled_exists = false;
	WARN_ON(!list_empty(&bridge_device->ports_list));
	WARN_ON(!list_empty(&bridge_device->mids_list));
	kमुक्त(bridge_device);
पूर्ण

अटल काष्ठा mlxsw_sp_bridge_device *
mlxsw_sp_bridge_device_get(काष्ठा mlxsw_sp_bridge *bridge,
			   काष्ठा net_device *br_dev,
			   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_bridge_device *bridge_device;

	bridge_device = mlxsw_sp_bridge_device_find(bridge, br_dev);
	अगर (bridge_device)
		वापस bridge_device;

	वापस mlxsw_sp_bridge_device_create(bridge, br_dev, extack);
पूर्ण

अटल व्योम
mlxsw_sp_bridge_device_put(काष्ठा mlxsw_sp_bridge *bridge,
			   काष्ठा mlxsw_sp_bridge_device *bridge_device)
अणु
	अगर (list_empty(&bridge_device->ports_list))
		mlxsw_sp_bridge_device_destroy(bridge, bridge_device);
पूर्ण

अटल काष्ठा mlxsw_sp_bridge_port *
__mlxsw_sp_bridge_port_find(स्थिर काष्ठा mlxsw_sp_bridge_device *bridge_device,
			    स्थिर काष्ठा net_device *brport_dev)
अणु
	काष्ठा mlxsw_sp_bridge_port *bridge_port;

	list_क्रम_each_entry(bridge_port, &bridge_device->ports_list, list) अणु
		अगर (bridge_port->dev == brport_dev)
			वापस bridge_port;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा mlxsw_sp_bridge_port *
mlxsw_sp_bridge_port_find(काष्ठा mlxsw_sp_bridge *bridge,
			  काष्ठा net_device *brport_dev)
अणु
	काष्ठा net_device *br_dev = netdev_master_upper_dev_get(brport_dev);
	काष्ठा mlxsw_sp_bridge_device *bridge_device;

	अगर (!br_dev)
		वापस शून्य;

	bridge_device = mlxsw_sp_bridge_device_find(bridge, br_dev);
	अगर (!bridge_device)
		वापस शून्य;

	वापस __mlxsw_sp_bridge_port_find(bridge_device, brport_dev);
पूर्ण

अटल काष्ठा mlxsw_sp_bridge_port *
mlxsw_sp_bridge_port_create(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			    काष्ठा net_device *brport_dev)
अणु
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;

	bridge_port = kzalloc(माप(*bridge_port), GFP_KERNEL);
	अगर (!bridge_port)
		वापस शून्य;

	mlxsw_sp_port = mlxsw_sp_port_dev_lower_find(brport_dev);
	bridge_port->lagged = mlxsw_sp_port->lagged;
	अगर (bridge_port->lagged)
		bridge_port->lag_id = mlxsw_sp_port->lag_id;
	अन्यथा
		bridge_port->प्रणाली_port = mlxsw_sp_port->local_port;
	bridge_port->dev = brport_dev;
	bridge_port->bridge_device = bridge_device;
	bridge_port->stp_state = BR_STATE_DISABLED;
	bridge_port->flags = BR_LEARNING | BR_FLOOD | BR_LEARNING_SYNC |
			     BR_MCAST_FLOOD;
	INIT_LIST_HEAD(&bridge_port->vlans_list);
	list_add(&bridge_port->list, &bridge_device->ports_list);
	bridge_port->ref_count = 1;

	वापस bridge_port;
पूर्ण

अटल व्योम
mlxsw_sp_bridge_port_destroy(काष्ठा mlxsw_sp_bridge_port *bridge_port)
अणु
	list_del(&bridge_port->list);
	WARN_ON(!list_empty(&bridge_port->vlans_list));
	kमुक्त(bridge_port);
पूर्ण

अटल काष्ठा mlxsw_sp_bridge_port *
mlxsw_sp_bridge_port_get(काष्ठा mlxsw_sp_bridge *bridge,
			 काष्ठा net_device *brport_dev,
			 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *br_dev = netdev_master_upper_dev_get(brport_dev);
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	पूर्णांक err;

	bridge_port = mlxsw_sp_bridge_port_find(bridge, brport_dev);
	अगर (bridge_port) अणु
		bridge_port->ref_count++;
		वापस bridge_port;
	पूर्ण

	bridge_device = mlxsw_sp_bridge_device_get(bridge, br_dev, extack);
	अगर (IS_ERR(bridge_device))
		वापस ERR_CAST(bridge_device);

	bridge_port = mlxsw_sp_bridge_port_create(bridge_device, brport_dev);
	अगर (!bridge_port) अणु
		err = -ENOMEM;
		जाओ err_bridge_port_create;
	पूर्ण

	वापस bridge_port;

err_bridge_port_create:
	mlxsw_sp_bridge_device_put(bridge, bridge_device);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम mlxsw_sp_bridge_port_put(काष्ठा mlxsw_sp_bridge *bridge,
				     काष्ठा mlxsw_sp_bridge_port *bridge_port)
अणु
	काष्ठा mlxsw_sp_bridge_device *bridge_device;

	अगर (--bridge_port->ref_count != 0)
		वापस;
	bridge_device = bridge_port->bridge_device;
	mlxsw_sp_bridge_port_destroy(bridge_port);
	mlxsw_sp_bridge_device_put(bridge, bridge_device);
पूर्ण

अटल काष्ठा mlxsw_sp_port_vlan *
mlxsw_sp_port_vlan_find_by_bridge(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  स्थिर काष्ठा mlxsw_sp_bridge_device *
				  bridge_device,
				  u16 vid)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	list_क्रम_each_entry(mlxsw_sp_port_vlan, &mlxsw_sp_port->vlans_list,
			    list) अणु
		अगर (!mlxsw_sp_port_vlan->bridge_port)
			जारी;
		अगर (mlxsw_sp_port_vlan->bridge_port->bridge_device !=
		    bridge_device)
			जारी;
		अगर (bridge_device->vlan_enabled &&
		    mlxsw_sp_port_vlan->vid != vid)
			जारी;
		वापस mlxsw_sp_port_vlan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_port_vlan*
mlxsw_sp_port_vlan_find_by_fid(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       u16 fid_index)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	list_क्रम_each_entry(mlxsw_sp_port_vlan, &mlxsw_sp_port->vlans_list,
			    list) अणु
		काष्ठा mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;

		अगर (fid && mlxsw_sp_fid_index(fid) == fid_index)
			वापस mlxsw_sp_port_vlan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_bridge_vlan *
mlxsw_sp_bridge_vlan_find(स्थिर काष्ठा mlxsw_sp_bridge_port *bridge_port,
			  u16 vid)
अणु
	काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan;

	list_क्रम_each_entry(bridge_vlan, &bridge_port->vlans_list, list) अणु
		अगर (bridge_vlan->vid == vid)
			वापस bridge_vlan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_bridge_vlan *
mlxsw_sp_bridge_vlan_create(काष्ठा mlxsw_sp_bridge_port *bridge_port, u16 vid)
अणु
	काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan;

	bridge_vlan = kzalloc(माप(*bridge_vlan), GFP_KERNEL);
	अगर (!bridge_vlan)
		वापस शून्य;

	INIT_LIST_HEAD(&bridge_vlan->port_vlan_list);
	bridge_vlan->vid = vid;
	list_add(&bridge_vlan->list, &bridge_port->vlans_list);

	वापस bridge_vlan;
पूर्ण

अटल व्योम
mlxsw_sp_bridge_vlan_destroy(काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan)
अणु
	list_del(&bridge_vlan->list);
	WARN_ON(!list_empty(&bridge_vlan->port_vlan_list));
	kमुक्त(bridge_vlan);
पूर्ण

अटल काष्ठा mlxsw_sp_bridge_vlan *
mlxsw_sp_bridge_vlan_get(काष्ठा mlxsw_sp_bridge_port *bridge_port, u16 vid)
अणु
	काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan;

	bridge_vlan = mlxsw_sp_bridge_vlan_find(bridge_port, vid);
	अगर (bridge_vlan)
		वापस bridge_vlan;

	वापस mlxsw_sp_bridge_vlan_create(bridge_port, vid);
पूर्ण

अटल व्योम mlxsw_sp_bridge_vlan_put(काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan)
अणु
	अगर (list_empty(&bridge_vlan->port_vlan_list))
		mlxsw_sp_bridge_vlan_destroy(bridge_vlan);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_bridge_vlan_stp_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan,
				  u8 state)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	list_क्रम_each_entry(mlxsw_sp_port_vlan, &bridge_vlan->port_vlan_list,
			    bridge_vlan_node) अणु
		अगर (mlxsw_sp_port_vlan->mlxsw_sp_port != mlxsw_sp_port)
			जारी;
		वापस mlxsw_sp_port_vid_stp_set(mlxsw_sp_port,
						 bridge_vlan->vid, state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_attr_stp_state_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					    काष्ठा net_device *orig_dev,
					    u8 state)
अणु
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan;
	पूर्णांक err;

	/* It's possible we failed to enslave the port, yet this
	 * operation is executed due to it being deferred.
	 */
	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp_port->mlxsw_sp->bridge,
						orig_dev);
	अगर (!bridge_port)
		वापस 0;

	list_क्रम_each_entry(bridge_vlan, &bridge_port->vlans_list, list) अणु
		err = mlxsw_sp_port_bridge_vlan_stp_set(mlxsw_sp_port,
							bridge_vlan, state);
		अगर (err)
			जाओ err_port_bridge_vlan_stp_set;
	पूर्ण

	bridge_port->stp_state = state;

	वापस 0;

err_port_bridge_vlan_stp_set:
	list_क्रम_each_entry_जारी_reverse(bridge_vlan,
					     &bridge_port->vlans_list, list)
		mlxsw_sp_port_bridge_vlan_stp_set(mlxsw_sp_port, bridge_vlan,
						  bridge_port->stp_state);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_bridge_vlan_flood_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan,
				    क्रमागत mlxsw_sp_flood_type packet_type,
				    bool member)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	list_क्रम_each_entry(mlxsw_sp_port_vlan, &bridge_vlan->port_vlan_list,
			    bridge_vlan_node) अणु
		अगर (mlxsw_sp_port_vlan->mlxsw_sp_port != mlxsw_sp_port)
			जारी;
		वापस mlxsw_sp_fid_flood_set(mlxsw_sp_port_vlan->fid,
					      packet_type,
					      mlxsw_sp_port->local_port,
					      member);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_port_flood_table_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     काष्ठा mlxsw_sp_bridge_port *bridge_port,
				     क्रमागत mlxsw_sp_flood_type packet_type,
				     bool member)
अणु
	काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan;
	पूर्णांक err;

	list_क्रम_each_entry(bridge_vlan, &bridge_port->vlans_list, list) अणु
		err = mlxsw_sp_port_bridge_vlan_flood_set(mlxsw_sp_port,
							  bridge_vlan,
							  packet_type,
							  member);
		अगर (err)
			जाओ err_port_bridge_vlan_flood_set;
	पूर्ण

	वापस 0;

err_port_bridge_vlan_flood_set:
	list_क्रम_each_entry_जारी_reverse(bridge_vlan,
					     &bridge_port->vlans_list, list)
		mlxsw_sp_port_bridge_vlan_flood_set(mlxsw_sp_port, bridge_vlan,
						    packet_type, !member);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_bridge_vlan_learning_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				       काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan,
				       bool set)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	u16 vid = bridge_vlan->vid;

	list_क्रम_each_entry(mlxsw_sp_port_vlan, &bridge_vlan->port_vlan_list,
			    bridge_vlan_node) अणु
		अगर (mlxsw_sp_port_vlan->mlxsw_sp_port != mlxsw_sp_port)
			जारी;
		वापस mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, set);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_port_learning_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  काष्ठा mlxsw_sp_bridge_port *bridge_port,
				  bool set)
अणु
	काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan;
	पूर्णांक err;

	list_क्रम_each_entry(bridge_vlan, &bridge_port->vlans_list, list) अणु
		err = mlxsw_sp_port_bridge_vlan_learning_set(mlxsw_sp_port,
							     bridge_vlan, set);
		अगर (err)
			जाओ err_port_bridge_vlan_learning_set;
	पूर्ण

	वापस 0;

err_port_bridge_vlan_learning_set:
	list_क्रम_each_entry_जारी_reverse(bridge_vlan,
					     &bridge_port->vlans_list, list)
		mlxsw_sp_port_bridge_vlan_learning_set(mlxsw_sp_port,
						       bridge_vlan, !set);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_attr_br_pre_flags_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				    काष्ठा चयनdev_brport_flags flags)
अणु
	अगर (flags.mask & ~(BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_attr_br_flags_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					   काष्ठा net_device *orig_dev,
					   काष्ठा चयनdev_brport_flags flags)
अणु
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	पूर्णांक err;

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp_port->mlxsw_sp->bridge,
						orig_dev);
	अगर (!bridge_port)
		वापस 0;

	अगर (flags.mask & BR_FLOOD) अणु
		err = mlxsw_sp_bridge_port_flood_table_set(mlxsw_sp_port,
							   bridge_port,
							   MLXSW_SP_FLOOD_TYPE_UC,
							   flags.val & BR_FLOOD);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (flags.mask & BR_LEARNING) अणु
		err = mlxsw_sp_bridge_port_learning_set(mlxsw_sp_port,
							bridge_port,
							flags.val & BR_LEARNING);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (bridge_port->bridge_device->multicast_enabled)
		जाओ out;

	अगर (flags.mask & BR_MCAST_FLOOD) अणु
		err = mlxsw_sp_bridge_port_flood_table_set(mlxsw_sp_port,
							   bridge_port,
							   MLXSW_SP_FLOOD_TYPE_MC,
							   flags.val & BR_MCAST_FLOOD);
		अगर (err)
			वापस err;
	पूर्ण

out:
	स_नकल(&bridge_port->flags, &flags.val, माप(flags.val));
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_ageing_set(काष्ठा mlxsw_sp *mlxsw_sp, u32 ageing_समय)
अणु
	अक्षर sfdat_pl[MLXSW_REG_SFDAT_LEN];
	पूर्णांक err;

	mlxsw_reg_sfdat_pack(sfdat_pl, ageing_समय);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfdat), sfdat_pl);
	अगर (err)
		वापस err;
	mlxsw_sp->bridge->ageing_समय = ageing_समय;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_attr_br_ageing_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					    अचिन्हित दीर्घ ageing_घड़ी_प्रकार)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अचिन्हित दीर्घ ageing_jअगरfies = घड़ी_प्रकार_to_jअगरfies(ageing_घड़ी_प्रकार);
	u32 ageing_समय = jअगरfies_to_msecs(ageing_jअगरfies) / 1000;

	अगर (ageing_समय < MLXSW_SP_MIN_AGEING_TIME ||
	    ageing_समय > MLXSW_SP_MAX_AGEING_TIME)
		वापस -दुस्फल;

	वापस mlxsw_sp_ageing_set(mlxsw_sp, ageing_समय);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_attr_br_vlan_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					  काष्ठा net_device *orig_dev,
					  bool vlan_enabled)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, orig_dev);
	अगर (WARN_ON(!bridge_device))
		वापस -EINVAL;

	अगर (bridge_device->vlan_enabled == vlan_enabled)
		वापस 0;

	netdev_err(bridge_device->dev, "VLAN filtering can't be changed for existing bridge\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_attr_br_vlan_proto_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
						काष्ठा net_device *orig_dev,
						u16 vlan_proto)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, orig_dev);
	अगर (WARN_ON(!bridge_device))
		वापस -EINVAL;

	netdev_err(bridge_device->dev, "VLAN protocol can't be changed on existing bridge\n");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_attr_mrouter_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					  काष्ठा net_device *orig_dev,
					  bool is_port_mrouter)
अणु
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	पूर्णांक err;

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp_port->mlxsw_sp->bridge,
						orig_dev);
	अगर (!bridge_port)
		वापस 0;

	अगर (!bridge_port->bridge_device->multicast_enabled)
		जाओ out;

	err = mlxsw_sp_bridge_port_flood_table_set(mlxsw_sp_port, bridge_port,
						   MLXSW_SP_FLOOD_TYPE_MC,
						   is_port_mrouter);
	अगर (err)
		वापस err;

	mlxsw_sp_port_mrouter_update_mdb(mlxsw_sp_port, bridge_port,
					 is_port_mrouter);
out:
	bridge_port->mrouter = is_port_mrouter;
	वापस 0;
पूर्ण

अटल bool mlxsw_sp_mc_flood(स्थिर काष्ठा mlxsw_sp_bridge_port *bridge_port)
अणु
	स्थिर काष्ठा mlxsw_sp_bridge_device *bridge_device;

	bridge_device = bridge_port->bridge_device;
	वापस bridge_device->multicast_enabled ? bridge_port->mrouter :
					bridge_port->flags & BR_MCAST_FLOOD;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_mc_disabled_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					 काष्ठा net_device *orig_dev,
					 bool mc_disabled)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	पूर्णांक err;

	/* It's possible we failed to enslave the port, yet this
	 * operation is executed due to it being deferred.
	 */
	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, orig_dev);
	अगर (!bridge_device)
		वापस 0;

	अगर (bridge_device->multicast_enabled != !mc_disabled) अणु
		bridge_device->multicast_enabled = !mc_disabled;
		mlxsw_sp_bridge_mdb_mc_enable_sync(mlxsw_sp_port,
						   bridge_device);
	पूर्ण

	list_क्रम_each_entry(bridge_port, &bridge_device->ports_list, list) अणु
		क्रमागत mlxsw_sp_flood_type packet_type = MLXSW_SP_FLOOD_TYPE_MC;
		bool member = mlxsw_sp_mc_flood(bridge_port);

		err = mlxsw_sp_bridge_port_flood_table_set(mlxsw_sp_port,
							   bridge_port,
							   packet_type, member);
		अगर (err)
			वापस err;
	पूर्ण

	bridge_device->multicast_enabled = !mc_disabled;

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_smid_router_port_set(काष्ठा mlxsw_sp *mlxsw_sp,
					 u16 mid_idx, bool add)
अणु
	अक्षर *smid_pl;
	पूर्णांक err;

	smid_pl = kदो_स्मृति(MLXSW_REG_SMID_LEN, GFP_KERNEL);
	अगर (!smid_pl)
		वापस -ENOMEM;

	mlxsw_reg_smid_pack(smid_pl, mid_idx,
			    mlxsw_sp_router_port(mlxsw_sp), add);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(smid), smid_pl);
	kमुक्त(smid_pl);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_bridge_mrouter_update_mdb(काष्ठा mlxsw_sp *mlxsw_sp,
				   काष्ठा mlxsw_sp_bridge_device *bridge_device,
				   bool add)
अणु
	काष्ठा mlxsw_sp_mid *mid;

	list_क्रम_each_entry(mid, &bridge_device->mids_list, list)
		mlxsw_sp_smid_router_port_set(mlxsw_sp, mid->mid, add);
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_attr_br_mrouter_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  काष्ठा net_device *orig_dev,
				  bool is_mrouter)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;

	/* It's possible we failed to enslave the port, yet this
	 * operation is executed due to it being deferred.
	 */
	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, orig_dev);
	अगर (!bridge_device)
		वापस 0;

	अगर (bridge_device->mrouter != is_mrouter)
		mlxsw_sp_bridge_mrouter_update_mdb(mlxsw_sp, bridge_device,
						   is_mrouter);
	bridge_device->mrouter = is_mrouter;
	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_attr_set(काष्ठा net_device *dev,
				  स्थिर काष्ठा चयनdev_attr *attr,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक err;

	चयन (attr->id) अणु
	हाल SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		err = mlxsw_sp_port_attr_stp_state_set(mlxsw_sp_port,
						       attr->orig_dev,
						       attr->u.stp_state);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		err = mlxsw_sp_port_attr_br_pre_flags_set(mlxsw_sp_port,
							  attr->u.brport_flags);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		err = mlxsw_sp_port_attr_br_flags_set(mlxsw_sp_port,
						      attr->orig_dev,
						      attr->u.brport_flags);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
		err = mlxsw_sp_port_attr_br_ageing_set(mlxsw_sp_port,
						       attr->u.ageing_समय);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		err = mlxsw_sp_port_attr_br_vlan_set(mlxsw_sp_port,
						     attr->orig_dev,
						     attr->u.vlan_filtering);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_VLAN_PROTOCOL:
		err = mlxsw_sp_port_attr_br_vlan_proto_set(mlxsw_sp_port,
							   attr->orig_dev,
							   attr->u.vlan_protocol);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_MROUTER:
		err = mlxsw_sp_port_attr_mrouter_set(mlxsw_sp_port,
						     attr->orig_dev,
						     attr->u.mrouter);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_MC_DISABLED:
		err = mlxsw_sp_port_mc_disabled_set(mlxsw_sp_port,
						    attr->orig_dev,
						    attr->u.mc_disabled);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_MROUTER:
		err = mlxsw_sp_port_attr_br_mrouter_set(mlxsw_sp_port,
							attr->orig_dev,
							attr->u.mrouter);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mlxsw_sp_span_respin(mlxsw_sp_port->mlxsw_sp);

	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_vlan_fid_join(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan,
			    काष्ठा mlxsw_sp_bridge_port *bridge_port,
			    काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	u8 local_port = mlxsw_sp_port->local_port;
	u16 vid = mlxsw_sp_port_vlan->vid;
	काष्ठा mlxsw_sp_fid *fid;
	पूर्णांक err;

	bridge_device = bridge_port->bridge_device;
	fid = bridge_device->ops->fid_get(bridge_device, vid, extack);
	अगर (IS_ERR(fid))
		वापस PTR_ERR(fid);

	err = mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_UC, local_port,
				     bridge_port->flags & BR_FLOOD);
	अगर (err)
		जाओ err_fid_uc_flood_set;

	err = mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_MC, local_port,
				     mlxsw_sp_mc_flood(bridge_port));
	अगर (err)
		जाओ err_fid_mc_flood_set;

	err = mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_BC, local_port,
				     true);
	अगर (err)
		जाओ err_fid_bc_flood_set;

	err = mlxsw_sp_fid_port_vid_map(fid, mlxsw_sp_port, vid);
	अगर (err)
		जाओ err_fid_port_vid_map;

	mlxsw_sp_port_vlan->fid = fid;

	वापस 0;

err_fid_port_vid_map:
	mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_BC, local_port, false);
err_fid_bc_flood_set:
	mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_MC, local_port, false);
err_fid_mc_flood_set:
	mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_UC, local_port, false);
err_fid_uc_flood_set:
	mlxsw_sp_fid_put(fid);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_port_vlan_fid_leave(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	काष्ठा mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;
	u8 local_port = mlxsw_sp_port->local_port;
	u16 vid = mlxsw_sp_port_vlan->vid;

	mlxsw_sp_port_vlan->fid = शून्य;
	mlxsw_sp_fid_port_vid_unmap(fid, mlxsw_sp_port, vid);
	mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_BC, local_port, false);
	mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_MC, local_port, false);
	mlxsw_sp_fid_flood_set(fid, MLXSW_SP_FLOOD_TYPE_UC, local_port, false);
	mlxsw_sp_fid_put(fid);
पूर्ण

अटल u16
mlxsw_sp_port_pvid_determine(स्थिर काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			     u16 vid, bool is_pvid)
अणु
	अगर (is_pvid)
		वापस vid;
	अन्यथा अगर (mlxsw_sp_port->pvid == vid)
		वापस 0;	/* Dis-allow untagged packets */
	अन्यथा
		वापस mlxsw_sp_port->pvid;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_vlan_bridge_join(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan,
			       काष्ठा mlxsw_sp_bridge_port *bridge_port,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan;
	u16 vid = mlxsw_sp_port_vlan->vid;
	पूर्णांक err;

	/* No need to जारी अगर only VLAN flags were changed */
	अगर (mlxsw_sp_port_vlan->bridge_port)
		वापस 0;

	err = mlxsw_sp_port_vlan_fid_join(mlxsw_sp_port_vlan, bridge_port,
					  extack);
	अगर (err)
		वापस err;

	err = mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid,
					     bridge_port->flags & BR_LEARNING);
	अगर (err)
		जाओ err_port_vid_learning_set;

	err = mlxsw_sp_port_vid_stp_set(mlxsw_sp_port, vid,
					bridge_port->stp_state);
	अगर (err)
		जाओ err_port_vid_stp_set;

	bridge_vlan = mlxsw_sp_bridge_vlan_get(bridge_port, vid);
	अगर (!bridge_vlan) अणु
		err = -ENOMEM;
		जाओ err_bridge_vlan_get;
	पूर्ण

	list_add(&mlxsw_sp_port_vlan->bridge_vlan_node,
		 &bridge_vlan->port_vlan_list);

	mlxsw_sp_bridge_port_get(mlxsw_sp_port->mlxsw_sp->bridge,
				 bridge_port->dev, extack);
	mlxsw_sp_port_vlan->bridge_port = bridge_port;

	वापस 0;

err_bridge_vlan_get:
	mlxsw_sp_port_vid_stp_set(mlxsw_sp_port, vid, BR_STATE_DISABLED);
err_port_vid_stp_set:
	mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, false);
err_port_vid_learning_set:
	mlxsw_sp_port_vlan_fid_leave(mlxsw_sp_port_vlan);
	वापस err;
पूर्ण

व्योम
mlxsw_sp_port_vlan_bridge_leave(काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = mlxsw_sp_port_vlan->mlxsw_sp_port;
	काष्ठा mlxsw_sp_fid *fid = mlxsw_sp_port_vlan->fid;
	काष्ठा mlxsw_sp_bridge_vlan *bridge_vlan;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	u16 vid = mlxsw_sp_port_vlan->vid;
	bool last_port, last_vlan;

	अगर (WARN_ON(mlxsw_sp_fid_type(fid) != MLXSW_SP_FID_TYPE_8021Q &&
		    mlxsw_sp_fid_type(fid) != MLXSW_SP_FID_TYPE_8021D))
		वापस;

	bridge_port = mlxsw_sp_port_vlan->bridge_port;
	last_vlan = list_is_singular(&bridge_port->vlans_list);
	bridge_vlan = mlxsw_sp_bridge_vlan_find(bridge_port, vid);
	last_port = list_is_singular(&bridge_vlan->port_vlan_list);

	list_del(&mlxsw_sp_port_vlan->bridge_vlan_node);
	mlxsw_sp_bridge_vlan_put(bridge_vlan);
	mlxsw_sp_port_vid_stp_set(mlxsw_sp_port, vid, BR_STATE_DISABLED);
	mlxsw_sp_port_vid_learning_set(mlxsw_sp_port, vid, false);
	अगर (last_port)
		mlxsw_sp_bridge_port_fdb_flush(mlxsw_sp_port->mlxsw_sp,
					       bridge_port,
					       mlxsw_sp_fid_index(fid));
	अगर (last_vlan)
		mlxsw_sp_bridge_port_mdb_flush(mlxsw_sp_port, bridge_port);

	mlxsw_sp_port_vlan_fid_leave(mlxsw_sp_port_vlan);

	mlxsw_sp_bridge_port_put(mlxsw_sp_port->mlxsw_sp->bridge, bridge_port);
	mlxsw_sp_port_vlan->bridge_port = शून्य;
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_port_vlan_add(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_bridge_port *bridge_port,
			      u16 vid, bool is_untagged, bool is_pvid,
			      काष्ठा netlink_ext_ack *extack)
अणु
	u16 pvid = mlxsw_sp_port_pvid_determine(mlxsw_sp_port, vid, is_pvid);
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	u16 old_pvid = mlxsw_sp_port->pvid;
	u16 proto;
	पूर्णांक err;

	/* The only valid scenario in which a port-vlan alपढ़ोy exists, is अगर
	 * the VLAN flags were changed and the port-vlan is associated with the
	 * correct bridge port
	 */
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	अगर (mlxsw_sp_port_vlan &&
	    mlxsw_sp_port_vlan->bridge_port != bridge_port)
		वापस -EEXIST;

	अगर (!mlxsw_sp_port_vlan) अणु
		mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_create(mlxsw_sp_port,
							       vid);
		अगर (IS_ERR(mlxsw_sp_port_vlan))
			वापस PTR_ERR(mlxsw_sp_port_vlan);
	पूर्ण

	err = mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, true,
				     is_untagged);
	अगर (err)
		जाओ err_port_vlan_set;

	br_vlan_get_proto(bridge_port->bridge_device->dev, &proto);
	err = mlxsw_sp_port_pvid_set(mlxsw_sp_port, pvid, proto);
	अगर (err)
		जाओ err_port_pvid_set;

	err = mlxsw_sp_port_vlan_bridge_join(mlxsw_sp_port_vlan, bridge_port,
					     extack);
	अगर (err)
		जाओ err_port_vlan_bridge_join;

	वापस 0;

err_port_vlan_bridge_join:
	mlxsw_sp_port_pvid_set(mlxsw_sp_port, old_pvid, proto);
err_port_pvid_set:
	mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, false, false);
err_port_vlan_set:
	mlxsw_sp_port_vlan_destroy(mlxsw_sp_port_vlan);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_br_ban_rअगर_pvid_change(काष्ठा mlxsw_sp *mlxsw_sp,
				स्थिर काष्ठा net_device *br_dev,
				स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	u16 pvid;

	pvid = mlxsw_sp_rअगर_vid(mlxsw_sp, br_dev);
	अगर (!pvid)
		वापस 0;

	अगर (vlan->flags & BRIDGE_VLAN_INFO_PVID) अणु
		अगर (vlan->vid != pvid) अणु
			netdev_err(br_dev, "Can't change PVID, it's used by router interface\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (vlan->vid == pvid) अणु
			netdev_err(br_dev, "Can't remove PVID, it's used by router interface\n");
			वापस -EBUSY;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_vlans_add(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
				   काष्ठा netlink_ext_ack *extack)
अणु
	bool flag_untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool flag_pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा net_device *orig_dev = vlan->obj.orig_dev;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;

	अगर (netअगर_is_bridge_master(orig_dev)) अणु
		पूर्णांक err = 0;

		अगर ((vlan->flags & BRIDGE_VLAN_INFO_BRENTRY) &&
		    br_vlan_enabled(orig_dev))
			err = mlxsw_sp_br_ban_rअगर_pvid_change(mlxsw_sp,
							      orig_dev, vlan);
		अगर (!err)
			err = -EOPNOTSUPP;
		वापस err;
	पूर्ण

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp->bridge, orig_dev);
	अगर (WARN_ON(!bridge_port))
		वापस -EINVAL;

	अगर (!bridge_port->bridge_device->vlan_enabled)
		वापस 0;

	वापस mlxsw_sp_bridge_port_vlan_add(mlxsw_sp_port, bridge_port,
					     vlan->vid, flag_untagged,
					     flag_pvid, extack);
पूर्ण

अटल क्रमागत mlxsw_reg_sfdf_flush_type mlxsw_sp_fdb_flush_type(bool lagged)
अणु
	वापस lagged ? MLXSW_REG_SFDF_FLUSH_PER_LAG_AND_FID :
			MLXSW_REG_SFDF_FLUSH_PER_PORT_AND_FID;
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_port_fdb_flush(काष्ठा mlxsw_sp *mlxsw_sp,
			       काष्ठा mlxsw_sp_bridge_port *bridge_port,
			       u16 fid_index)
अणु
	bool lagged = bridge_port->lagged;
	अक्षर sfdf_pl[MLXSW_REG_SFDF_LEN];
	u16 प्रणाली_port;

	प्रणाली_port = lagged ? bridge_port->lag_id : bridge_port->प्रणाली_port;
	mlxsw_reg_sfdf_pack(sfdf_pl, mlxsw_sp_fdb_flush_type(lagged));
	mlxsw_reg_sfdf_fid_set(sfdf_pl, fid_index);
	mlxsw_reg_sfdf_port_fid_प्रणाली_port_set(sfdf_pl, प्रणाली_port);

	वापस mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfdf), sfdf_pl);
पूर्ण

अटल क्रमागत mlxsw_reg_sfd_rec_policy mlxsw_sp_sfd_rec_policy(bool dynamic)
अणु
	वापस dynamic ? MLXSW_REG_SFD_REC_POLICY_DYNAMIC_ENTRY_INGRESS :
			 MLXSW_REG_SFD_REC_POLICY_DYNAMIC_ENTRY_MLAG;
पूर्ण

अटल क्रमागत mlxsw_reg_sfd_op mlxsw_sp_sfd_op(bool adding)
अणु
	वापस adding ? MLXSW_REG_SFD_OP_WRITE_EDIT :
			MLXSW_REG_SFD_OP_WRITE_REMOVE;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_fdb_tunnel_uc_op(काष्ठा mlxsw_sp *mlxsw_sp,
					  स्थिर अक्षर *mac, u16 fid,
					  क्रमागत mlxsw_sp_l3proto proto,
					  स्थिर जोड़ mlxsw_sp_l3addr *addr,
					  bool adding, bool dynamic)
अणु
	क्रमागत mlxsw_reg_sfd_uc_tunnel_protocol sfd_proto;
	अक्षर *sfd_pl;
	u8 num_rec;
	u32 uip;
	पूर्णांक err;

	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		uip = be32_to_cpu(addr->addr4);
		sfd_proto = MLXSW_REG_SFD_UC_TUNNEL_PROTOCOL_IPV4;
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
	शेष:
		WARN_ON(1);
		वापस -EOPNOTSUPP;
	पूर्ण

	sfd_pl = kदो_स्मृति(MLXSW_REG_SFD_LEN, GFP_KERNEL);
	अगर (!sfd_pl)
		वापस -ENOMEM;

	mlxsw_reg_sfd_pack(sfd_pl, mlxsw_sp_sfd_op(adding), 0);
	mlxsw_reg_sfd_uc_tunnel_pack(sfd_pl, 0,
				     mlxsw_sp_sfd_rec_policy(dynamic), mac, fid,
				     MLXSW_REG_SFD_REC_ACTION_NOP, uip,
				     sfd_proto);
	num_rec = mlxsw_reg_sfd_num_rec_get(sfd_pl);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfd), sfd_pl);
	अगर (err)
		जाओ out;

	अगर (num_rec != mlxsw_reg_sfd_num_rec_get(sfd_pl))
		err = -EBUSY;

out:
	kमुक्त(sfd_pl);
	वापस err;
पूर्ण

अटल पूर्णांक __mlxsw_sp_port_fdb_uc_op(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				     स्थिर अक्षर *mac, u16 fid, bool adding,
				     क्रमागत mlxsw_reg_sfd_rec_action action,
				     क्रमागत mlxsw_reg_sfd_rec_policy policy)
अणु
	अक्षर *sfd_pl;
	u8 num_rec;
	पूर्णांक err;

	sfd_pl = kदो_स्मृति(MLXSW_REG_SFD_LEN, GFP_KERNEL);
	अगर (!sfd_pl)
		वापस -ENOMEM;

	mlxsw_reg_sfd_pack(sfd_pl, mlxsw_sp_sfd_op(adding), 0);
	mlxsw_reg_sfd_uc_pack(sfd_pl, 0, policy, mac, fid, action, local_port);
	num_rec = mlxsw_reg_sfd_num_rec_get(sfd_pl);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfd), sfd_pl);
	अगर (err)
		जाओ out;

	अगर (num_rec != mlxsw_reg_sfd_num_rec_get(sfd_pl))
		err = -EBUSY;

out:
	kमुक्त(sfd_pl);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_fdb_uc_op(काष्ठा mlxsw_sp *mlxsw_sp, u8 local_port,
				   स्थिर अक्षर *mac, u16 fid, bool adding,
				   bool dynamic)
अणु
	वापस __mlxsw_sp_port_fdb_uc_op(mlxsw_sp, local_port, mac, fid, adding,
					 MLXSW_REG_SFD_REC_ACTION_NOP,
					 mlxsw_sp_sfd_rec_policy(dynamic));
पूर्ण

पूर्णांक mlxsw_sp_rअगर_fdb_op(काष्ठा mlxsw_sp *mlxsw_sp, स्थिर अक्षर *mac, u16 fid,
			bool adding)
अणु
	वापस __mlxsw_sp_port_fdb_uc_op(mlxsw_sp, 0, mac, fid, adding,
					 MLXSW_REG_SFD_REC_ACTION_FORWARD_IP_ROUTER,
					 MLXSW_REG_SFD_REC_POLICY_STATIC_ENTRY);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_fdb_uc_lag_op(काष्ठा mlxsw_sp *mlxsw_sp, u16 lag_id,
				       स्थिर अक्षर *mac, u16 fid, u16 lag_vid,
				       bool adding, bool dynamic)
अणु
	अक्षर *sfd_pl;
	u8 num_rec;
	पूर्णांक err;

	sfd_pl = kदो_स्मृति(MLXSW_REG_SFD_LEN, GFP_KERNEL);
	अगर (!sfd_pl)
		वापस -ENOMEM;

	mlxsw_reg_sfd_pack(sfd_pl, mlxsw_sp_sfd_op(adding), 0);
	mlxsw_reg_sfd_uc_lag_pack(sfd_pl, 0, mlxsw_sp_sfd_rec_policy(dynamic),
				  mac, fid, MLXSW_REG_SFD_REC_ACTION_NOP,
				  lag_vid, lag_id);
	num_rec = mlxsw_reg_sfd_num_rec_get(sfd_pl);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfd), sfd_pl);
	अगर (err)
		जाओ out;

	अगर (num_rec != mlxsw_reg_sfd_num_rec_get(sfd_pl))
		err = -EBUSY;

out:
	kमुक्त(sfd_pl);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_port_fdb_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
		      काष्ठा चयनdev_notअगरier_fdb_info *fdb_info, bool adding)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा net_device *orig_dev = fdb_info->info.dev;
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	u16 fid_index, vid;

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp->bridge, orig_dev);
	अगर (!bridge_port)
		वापस -EINVAL;

	bridge_device = bridge_port->bridge_device;
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_bridge(mlxsw_sp_port,
							       bridge_device,
							       fdb_info->vid);
	अगर (!mlxsw_sp_port_vlan)
		वापस 0;

	fid_index = mlxsw_sp_fid_index(mlxsw_sp_port_vlan->fid);
	vid = mlxsw_sp_port_vlan->vid;

	अगर (!bridge_port->lagged)
		वापस mlxsw_sp_port_fdb_uc_op(mlxsw_sp,
					       bridge_port->प्रणाली_port,
					       fdb_info->addr, fid_index,
					       adding, false);
	अन्यथा
		वापस mlxsw_sp_port_fdb_uc_lag_op(mlxsw_sp,
						   bridge_port->lag_id,
						   fdb_info->addr, fid_index,
						   vid, adding, false);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_mdb_op(काष्ठा mlxsw_sp *mlxsw_sp, स्थिर अक्षर *addr,
				u16 fid, u16 mid_idx, bool adding)
अणु
	अक्षर *sfd_pl;
	u8 num_rec;
	पूर्णांक err;

	sfd_pl = kदो_स्मृति(MLXSW_REG_SFD_LEN, GFP_KERNEL);
	अगर (!sfd_pl)
		वापस -ENOMEM;

	mlxsw_reg_sfd_pack(sfd_pl, mlxsw_sp_sfd_op(adding), 0);
	mlxsw_reg_sfd_mc_pack(sfd_pl, 0, addr, fid,
			      MLXSW_REG_SFD_REC_ACTION_NOP, mid_idx);
	num_rec = mlxsw_reg_sfd_num_rec_get(sfd_pl);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(sfd), sfd_pl);
	अगर (err)
		जाओ out;

	अगर (num_rec != mlxsw_reg_sfd_num_rec_get(sfd_pl))
		err = -EBUSY;

out:
	kमुक्त(sfd_pl);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_smid_full_entry(काष्ठा mlxsw_sp *mlxsw_sp, u16 mid_idx,
					 दीर्घ *ports_biपंचांगap,
					 bool set_router_port)
अणु
	अक्षर *smid_pl;
	पूर्णांक err, i;

	smid_pl = kदो_स्मृति(MLXSW_REG_SMID_LEN, GFP_KERNEL);
	अगर (!smid_pl)
		वापस -ENOMEM;

	mlxsw_reg_smid_pack(smid_pl, mid_idx, 0, false);
	क्रम (i = 1; i < mlxsw_core_max_ports(mlxsw_sp->core); i++) अणु
		अगर (mlxsw_sp->ports[i])
			mlxsw_reg_smid_port_mask_set(smid_pl, i, 1);
	पूर्ण

	mlxsw_reg_smid_port_mask_set(smid_pl,
				     mlxsw_sp_router_port(mlxsw_sp), 1);

	क्रम_each_set_bit(i, ports_biपंचांगap, mlxsw_core_max_ports(mlxsw_sp->core))
		mlxsw_reg_smid_port_set(smid_pl, i, 1);

	mlxsw_reg_smid_port_set(smid_pl, mlxsw_sp_router_port(mlxsw_sp),
				set_router_port);

	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(smid), smid_pl);
	kमुक्त(smid_pl);
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_smid_set(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  u16 mid_idx, bool add)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	अक्षर *smid_pl;
	पूर्णांक err;

	smid_pl = kदो_स्मृति(MLXSW_REG_SMID_LEN, GFP_KERNEL);
	अगर (!smid_pl)
		वापस -ENOMEM;

	mlxsw_reg_smid_pack(smid_pl, mid_idx, mlxsw_sp_port->local_port, add);
	err = mlxsw_reg_ग_लिखो(mlxsw_sp->core, MLXSW_REG(smid), smid_pl);
	kमुक्त(smid_pl);
	वापस err;
पूर्ण

अटल काष्ठा
mlxsw_sp_mid *__mlxsw_sp_mc_get(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				स्थिर अचिन्हित अक्षर *addr,
				u16 fid)
अणु
	काष्ठा mlxsw_sp_mid *mid;

	list_क्रम_each_entry(mid, &bridge_device->mids_list, list) अणु
		अगर (ether_addr_equal(mid->addr, addr) && mid->fid == fid)
			वापस mid;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल व्योम
mlxsw_sp_bridge_port_get_ports_biपंचांगap(काष्ठा mlxsw_sp *mlxsw_sp,
				      काष्ठा mlxsw_sp_bridge_port *bridge_port,
				      अचिन्हित दीर्घ *ports_biपंचांगap)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	u64 max_lag_members, i;
	पूर्णांक lag_id;

	अगर (!bridge_port->lagged) अणु
		set_bit(bridge_port->प्रणाली_port, ports_biपंचांगap);
	पूर्ण अन्यथा अणु
		max_lag_members = MLXSW_CORE_RES_GET(mlxsw_sp->core,
						     MAX_LAG_MEMBERS);
		lag_id = bridge_port->lag_id;
		क्रम (i = 0; i < max_lag_members; i++) अणु
			mlxsw_sp_port = mlxsw_sp_port_lagged_get(mlxsw_sp,
								 lag_id, i);
			अगर (mlxsw_sp_port)
				set_bit(mlxsw_sp_port->local_port,
					ports_biपंचांगap);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_mc_get_mrouters_biपंचांगap(अचिन्हित दीर्घ *flood_biपंचांगap,
				काष्ठा mlxsw_sp_bridge_device *bridge_device,
				काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_bridge_port *bridge_port;

	list_क्रम_each_entry(bridge_port, &bridge_device->ports_list, list) अणु
		अगर (bridge_port->mrouter) अणु
			mlxsw_sp_bridge_port_get_ports_biपंचांगap(mlxsw_sp,
							      bridge_port,
							      flood_biपंचांगap);
		पूर्ण
	पूर्ण
पूर्ण

अटल bool
mlxsw_sp_mc_ग_लिखो_mdb_entry(काष्ठा mlxsw_sp *mlxsw_sp,
			    काष्ठा mlxsw_sp_mid *mid,
			    काष्ठा mlxsw_sp_bridge_device *bridge_device)
अणु
	दीर्घ *flood_biपंचांगap;
	पूर्णांक num_of_ports;
	पूर्णांक alloc_size;
	u16 mid_idx;
	पूर्णांक err;

	mid_idx = find_first_zero_bit(mlxsw_sp->bridge->mids_biपंचांगap,
				      MLXSW_SP_MID_MAX);
	अगर (mid_idx == MLXSW_SP_MID_MAX)
		वापस false;

	num_of_ports = mlxsw_core_max_ports(mlxsw_sp->core);
	alloc_size = माप(दीर्घ) * BITS_TO_LONGS(num_of_ports);
	flood_biपंचांगap = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!flood_biपंचांगap)
		वापस false;

	biपंचांगap_copy(flood_biपंचांगap,  mid->ports_in_mid, num_of_ports);
	mlxsw_sp_mc_get_mrouters_biपंचांगap(flood_biपंचांगap, bridge_device, mlxsw_sp);

	mid->mid = mid_idx;
	err = mlxsw_sp_port_smid_full_entry(mlxsw_sp, mid_idx, flood_biपंचांगap,
					    bridge_device->mrouter);
	kमुक्त(flood_biपंचांगap);
	अगर (err)
		वापस false;

	err = mlxsw_sp_port_mdb_op(mlxsw_sp, mid->addr, mid->fid, mid_idx,
				   true);
	अगर (err)
		वापस false;

	set_bit(mid_idx, mlxsw_sp->bridge->mids_biपंचांगap);
	mid->in_hw = true;
	वापस true;
पूर्ण

अटल पूर्णांक mlxsw_sp_mc_हटाओ_mdb_entry(काष्ठा mlxsw_sp *mlxsw_sp,
					काष्ठा mlxsw_sp_mid *mid)
अणु
	अगर (!mid->in_hw)
		वापस 0;

	clear_bit(mid->mid, mlxsw_sp->bridge->mids_biपंचांगap);
	mid->in_hw = false;
	वापस mlxsw_sp_port_mdb_op(mlxsw_sp, mid->addr, mid->fid, mid->mid,
				    false);
पूर्ण

अटल काष्ठा
mlxsw_sp_mid *__mlxsw_sp_mc_alloc(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_bridge_device *bridge_device,
				  स्थिर अचिन्हित अक्षर *addr,
				  u16 fid)
अणु
	काष्ठा mlxsw_sp_mid *mid;
	माप_प्रकार alloc_size;

	mid = kzalloc(माप(*mid), GFP_KERNEL);
	अगर (!mid)
		वापस शून्य;

	alloc_size = माप(अचिन्हित दीर्घ) *
		     BITS_TO_LONGS(mlxsw_core_max_ports(mlxsw_sp->core));

	mid->ports_in_mid = kzalloc(alloc_size, GFP_KERNEL);
	अगर (!mid->ports_in_mid)
		जाओ err_ports_in_mid_alloc;

	ether_addr_copy(mid->addr, addr);
	mid->fid = fid;
	mid->in_hw = false;

	अगर (!bridge_device->multicast_enabled)
		जाओ out;

	अगर (!mlxsw_sp_mc_ग_लिखो_mdb_entry(mlxsw_sp, mid, bridge_device))
		जाओ err_ग_लिखो_mdb_entry;

out:
	list_add_tail(&mid->list, &bridge_device->mids_list);
	वापस mid;

err_ग_लिखो_mdb_entry:
	kमुक्त(mid->ports_in_mid);
err_ports_in_mid_alloc:
	kमुक्त(mid);
	वापस शून्य;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_हटाओ_from_mid(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
					 काष्ठा mlxsw_sp_mid *mid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	पूर्णांक err = 0;

	clear_bit(mlxsw_sp_port->local_port, mid->ports_in_mid);
	अगर (biपंचांगap_empty(mid->ports_in_mid,
			 mlxsw_core_max_ports(mlxsw_sp->core))) अणु
		err = mlxsw_sp_mc_हटाओ_mdb_entry(mlxsw_sp, mid);
		list_del(&mid->list);
		kमुक्त(mid->ports_in_mid);
		kमुक्त(mid);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_mdb_add(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा net_device *orig_dev = mdb->obj.orig_dev;
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	काष्ठा net_device *dev = mlxsw_sp_port->dev;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	काष्ठा mlxsw_sp_mid *mid;
	u16 fid_index;
	पूर्णांक err = 0;

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp->bridge, orig_dev);
	अगर (!bridge_port)
		वापस 0;

	bridge_device = bridge_port->bridge_device;
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_bridge(mlxsw_sp_port,
							       bridge_device,
							       mdb->vid);
	अगर (!mlxsw_sp_port_vlan)
		वापस 0;

	fid_index = mlxsw_sp_fid_index(mlxsw_sp_port_vlan->fid);

	mid = __mlxsw_sp_mc_get(bridge_device, mdb->addr, fid_index);
	अगर (!mid) अणु
		mid = __mlxsw_sp_mc_alloc(mlxsw_sp, bridge_device, mdb->addr,
					  fid_index);
		अगर (!mid) अणु
			netdev_err(dev, "Unable to allocate MC group\n");
			वापस -ENOMEM;
		पूर्ण
	पूर्ण
	set_bit(mlxsw_sp_port->local_port, mid->ports_in_mid);

	अगर (!bridge_device->multicast_enabled)
		वापस 0;

	अगर (bridge_port->mrouter)
		वापस 0;

	err = mlxsw_sp_port_smid_set(mlxsw_sp_port, mid->mid, true);
	अगर (err) अणु
		netdev_err(dev, "Unable to set SMID\n");
		जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	mlxsw_sp_port_हटाओ_from_mid(mlxsw_sp_port, mid);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_bridge_mdb_mc_enable_sync(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   काष्ठा mlxsw_sp_bridge_device
				   *bridge_device)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_mid *mid;
	bool mc_enabled;

	mc_enabled = bridge_device->multicast_enabled;

	list_क्रम_each_entry(mid, &bridge_device->mids_list, list) अणु
		अगर (mc_enabled)
			mlxsw_sp_mc_ग_लिखो_mdb_entry(mlxsw_sp, mid,
						    bridge_device);
		अन्यथा
			mlxsw_sp_mc_हटाओ_mdb_entry(mlxsw_sp, mid);
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_port_mrouter_update_mdb(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 काष्ठा mlxsw_sp_bridge_port *bridge_port,
				 bool add)
अणु
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_mid *mid;

	bridge_device = bridge_port->bridge_device;

	list_क्रम_each_entry(mid, &bridge_device->mids_list, list) अणु
		अगर (!test_bit(mlxsw_sp_port->local_port, mid->ports_in_mid))
			mlxsw_sp_port_smid_set(mlxsw_sp_port, mid->mid, add);
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_port_obj_add(काष्ठा net_device *dev,
				 स्थिर काष्ठा चयनdev_obj *obj,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	स्थिर काष्ठा चयनdev_obj_port_vlan *vlan;
	पूर्णांक err = 0;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);

		err = mlxsw_sp_port_vlans_add(mlxsw_sp_port, vlan, extack);

		/* The event is emitted beक्रमe the changes are actually
		 * applied to the bridge. Thereक्रमe schedule the respin
		 * call क्रम later, so that the respin logic sees the
		 * updated bridge state.
		 */
		mlxsw_sp_span_respin(mlxsw_sp_port->mlxsw_sp);
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		err = mlxsw_sp_port_mdb_add(mlxsw_sp_port,
					    SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_bridge_port_vlan_del(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा mlxsw_sp_bridge_port *bridge_port, u16 vid)
अणु
	u16 pvid = mlxsw_sp_port->pvid == vid ? 0 : mlxsw_sp_port->pvid;
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	u16 proto;

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	अगर (WARN_ON(!mlxsw_sp_port_vlan))
		वापस;

	mlxsw_sp_port_vlan_bridge_leave(mlxsw_sp_port_vlan);
	br_vlan_get_proto(bridge_port->bridge_device->dev, &proto);
	mlxsw_sp_port_pvid_set(mlxsw_sp_port, pvid, proto);
	mlxsw_sp_port_vlan_set(mlxsw_sp_port, vid, vid, false, false);
	mlxsw_sp_port_vlan_destroy(mlxsw_sp_port_vlan);
पूर्ण

अटल पूर्णांक mlxsw_sp_port_vlans_del(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा net_device *orig_dev = vlan->obj.orig_dev;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;

	अगर (netअगर_is_bridge_master(orig_dev))
		वापस -EOPNOTSUPP;

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp->bridge, orig_dev);
	अगर (WARN_ON(!bridge_port))
		वापस -EINVAL;

	अगर (!bridge_port->bridge_device->vlan_enabled)
		वापस 0;

	mlxsw_sp_bridge_port_vlan_del(mlxsw_sp_port, bridge_port, vlan->vid);

	वापस 0;
पूर्ण

अटल पूर्णांक
__mlxsw_sp_port_mdb_del(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			काष्ठा mlxsw_sp_bridge_port *bridge_port,
			काष्ठा mlxsw_sp_mid *mid)
अणु
	काष्ठा net_device *dev = mlxsw_sp_port->dev;
	पूर्णांक err;

	अगर (bridge_port->bridge_device->multicast_enabled &&
	    !bridge_port->mrouter) अणु
		err = mlxsw_sp_port_smid_set(mlxsw_sp_port, mid->mid, false);
		अगर (err)
			netdev_err(dev, "Unable to remove port from SMID\n");
	पूर्ण

	err = mlxsw_sp_port_हटाओ_from_mid(mlxsw_sp_port, mid);
	अगर (err)
		netdev_err(dev, "Unable to remove MC SFD\n");

	वापस err;
पूर्ण

अटल पूर्णांक mlxsw_sp_port_mdb_del(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 स्थिर काष्ठा चयनdev_obj_port_mdb *mdb)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा net_device *orig_dev = mdb->obj.orig_dev;
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा net_device *dev = mlxsw_sp_port->dev;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	काष्ठा mlxsw_sp_mid *mid;
	u16 fid_index;

	bridge_port = mlxsw_sp_bridge_port_find(mlxsw_sp->bridge, orig_dev);
	अगर (!bridge_port)
		वापस 0;

	bridge_device = bridge_port->bridge_device;
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_bridge(mlxsw_sp_port,
							       bridge_device,
							       mdb->vid);
	अगर (!mlxsw_sp_port_vlan)
		वापस 0;

	fid_index = mlxsw_sp_fid_index(mlxsw_sp_port_vlan->fid);

	mid = __mlxsw_sp_mc_get(bridge_device, mdb->addr, fid_index);
	अगर (!mid) अणु
		netdev_err(dev, "Unable to remove port from MC DB\n");
		वापस -EINVAL;
	पूर्ण

	वापस __mlxsw_sp_port_mdb_del(mlxsw_sp_port, bridge_port, mid);
पूर्ण

अटल व्योम
mlxsw_sp_bridge_port_mdb_flush(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			       काष्ठा mlxsw_sp_bridge_port *bridge_port)
अणु
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_mid *mid, *पंचांगp;

	bridge_device = bridge_port->bridge_device;

	list_क्रम_each_entry_safe(mid, पंचांगp, &bridge_device->mids_list, list) अणु
		अगर (test_bit(mlxsw_sp_port->local_port, mid->ports_in_mid)) अणु
			__mlxsw_sp_port_mdb_del(mlxsw_sp_port, bridge_port,
						mid);
		पूर्ण अन्यथा अगर (bridge_device->multicast_enabled &&
			   bridge_port->mrouter) अणु
			mlxsw_sp_port_smid_set(mlxsw_sp_port, mid->mid, false);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_port_obj_del(काष्ठा net_device *dev,
				 स्थिर काष्ठा चयनdev_obj *obj)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port = netdev_priv(dev);
	पूर्णांक err = 0;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = mlxsw_sp_port_vlans_del(mlxsw_sp_port,
					      SWITCHDEV_OBJ_PORT_VLAN(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		err = mlxsw_sp_port_mdb_del(mlxsw_sp_port,
					    SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	mlxsw_sp_span_respin(mlxsw_sp_port->mlxsw_sp);

	वापस err;
पूर्ण

अटल काष्ठा mlxsw_sp_port *mlxsw_sp_lag_rep_port(काष्ठा mlxsw_sp *mlxsw_sp,
						   u16 lag_id)
अणु
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	u64 max_lag_members;
	पूर्णांक i;

	max_lag_members = MLXSW_CORE_RES_GET(mlxsw_sp->core,
					     MAX_LAG_MEMBERS);
	क्रम (i = 0; i < max_lag_members; i++) अणु
		mlxsw_sp_port = mlxsw_sp_port_lagged_get(mlxsw_sp, lag_id, i);
		अगर (mlxsw_sp_port)
			वापस mlxsw_sp_port;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_vlan_aware_port_join(काष्ठा mlxsw_sp_bridge_port *bridge_port,
				     काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				     काष्ठा netlink_ext_ack *extack)
अणु
	अगर (is_vlan_dev(bridge_port->dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Can not enslave a VLAN device to a VLAN-aware bridge");
		वापस -EINVAL;
	पूर्ण

	/* Port is no दीर्घer usable as a router पूर्णांकerface */
	अगर (mlxsw_sp_port->शेष_vlan->fid)
		mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port->शेष_vlan);

	वापस 0;
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_8021q_port_join(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				काष्ठा mlxsw_sp_bridge_port *bridge_port,
				काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				काष्ठा netlink_ext_ack *extack)
अणु
	वापस mlxsw_sp_bridge_vlan_aware_port_join(bridge_port, mlxsw_sp_port,
						    extack);
पूर्ण

अटल व्योम
mlxsw_sp_bridge_vlan_aware_port_leave(काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	/* Make sure untagged frames are allowed to ingress */
	mlxsw_sp_port_pvid_set(mlxsw_sp_port, MLXSW_SP_DEFAULT_VID,
			       ETH_P_8021Q);
पूर्ण

अटल व्योम
mlxsw_sp_bridge_8021q_port_leave(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				 काष्ठा mlxsw_sp_bridge_port *bridge_port,
				 काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	mlxsw_sp_bridge_vlan_aware_port_leave(mlxsw_sp_port);
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_vlan_aware_vxlan_join(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				      स्थिर काष्ठा net_device *vxlan_dev,
				      u16 vid, u16 ethertype,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);
	काष्ठा vxlan_dev *vxlan = netdev_priv(vxlan_dev);
	काष्ठा mlxsw_sp_nve_params params = अणु
		.type = MLXSW_SP_NVE_TYPE_VXLAN,
		.vni = vxlan->cfg.vni,
		.dev = vxlan_dev,
		.ethertype = ethertype,
	पूर्ण;
	काष्ठा mlxsw_sp_fid *fid;
	पूर्णांक err;

	/* If the VLAN is 0, we need to find the VLAN that is configured as
	 * PVID and egress untagged on the bridge port of the VxLAN device.
	 * It is possible no such VLAN exists
	 */
	अगर (!vid) अणु
		err = mlxsw_sp_vxlan_mapped_vid(vxlan_dev, &vid);
		अगर (err || !vid)
			वापस err;
	पूर्ण

	fid = mlxsw_sp_fid_8021q_get(mlxsw_sp, vid);
	अगर (IS_ERR(fid)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to create 802.1Q FID");
		वापस PTR_ERR(fid);
	पूर्ण

	अगर (mlxsw_sp_fid_vni_is_set(fid)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VNI is already set on FID");
		err = -EINVAL;
		जाओ err_vni_exists;
	पूर्ण

	err = mlxsw_sp_nve_fid_enable(mlxsw_sp, fid, &params, extack);
	अगर (err)
		जाओ err_nve_fid_enable;

	वापस 0;

err_nve_fid_enable:
err_vni_exists:
	mlxsw_sp_fid_put(fid);
	वापस err;
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_8021q_vxlan_join(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				 स्थिर काष्ठा net_device *vxlan_dev, u16 vid,
				 काष्ठा netlink_ext_ack *extack)
अणु
	वापस mlxsw_sp_bridge_vlan_aware_vxlan_join(bridge_device, vxlan_dev,
						     vid, ETH_P_8021Q, extack);
पूर्ण

अटल काष्ठा net_device *
mlxsw_sp_bridge_8021q_vxlan_dev_find(काष्ठा net_device *br_dev, u16 vid)
अणु
	काष्ठा net_device *dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_lower_dev(br_dev, dev, iter) अणु
		u16 pvid;
		पूर्णांक err;

		अगर (!netअगर_is_vxlan(dev))
			जारी;

		err = mlxsw_sp_vxlan_mapped_vid(dev, &pvid);
		अगर (err || pvid != vid)
			जारी;

		वापस dev;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा mlxsw_sp_fid *
mlxsw_sp_bridge_8021q_fid_get(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			      u16 vid, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);

	वापस mlxsw_sp_fid_8021q_get(mlxsw_sp, vid);
पूर्ण

अटल काष्ठा mlxsw_sp_fid *
mlxsw_sp_bridge_8021q_fid_lookup(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				 u16 vid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);

	वापस mlxsw_sp_fid_8021q_lookup(mlxsw_sp, vid);
पूर्ण

अटल u16
mlxsw_sp_bridge_8021q_fid_vid(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			      स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस mlxsw_sp_fid_8021q_vid(fid);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_bridge_ops mlxsw_sp_bridge_8021q_ops = अणु
	.port_join	= mlxsw_sp_bridge_8021q_port_join,
	.port_leave	= mlxsw_sp_bridge_8021q_port_leave,
	.vxlan_join	= mlxsw_sp_bridge_8021q_vxlan_join,
	.fid_get	= mlxsw_sp_bridge_8021q_fid_get,
	.fid_lookup	= mlxsw_sp_bridge_8021q_fid_lookup,
	.fid_vid	= mlxsw_sp_bridge_8021q_fid_vid,
पूर्ण;

अटल bool
mlxsw_sp_port_is_br_member(स्थिर काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			   स्थिर काष्ठा net_device *br_dev)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;

	list_क्रम_each_entry(mlxsw_sp_port_vlan, &mlxsw_sp_port->vlans_list,
			    list) अणु
		अगर (mlxsw_sp_port_vlan->bridge_port &&
		    mlxsw_sp_port_vlan->bridge_port->bridge_device->dev ==
		    br_dev)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_8021d_port_join(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				काष्ठा mlxsw_sp_bridge_port *bridge_port,
				काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	काष्ठा net_device *dev = bridge_port->dev;
	u16 vid;

	vid = is_vlan_dev(dev) ? vlan_dev_vlan_id(dev) : MLXSW_SP_DEFAULT_VID;
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	अगर (WARN_ON(!mlxsw_sp_port_vlan))
		वापस -EINVAL;

	अगर (mlxsw_sp_port_is_br_member(mlxsw_sp_port, bridge_device->dev)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Can not bridge VLAN uppers of the same port");
		वापस -EINVAL;
	पूर्ण

	/* Port is no दीर्घer usable as a router पूर्णांकerface */
	अगर (mlxsw_sp_port_vlan->fid)
		mlxsw_sp_port_vlan_router_leave(mlxsw_sp_port_vlan);

	वापस mlxsw_sp_port_vlan_bridge_join(mlxsw_sp_port_vlan, bridge_port,
					      extack);
पूर्ण

अटल व्योम
mlxsw_sp_bridge_8021d_port_leave(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				 काष्ठा mlxsw_sp_bridge_port *bridge_port,
				 काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	काष्ठा net_device *dev = bridge_port->dev;
	u16 vid;

	vid = is_vlan_dev(dev) ? vlan_dev_vlan_id(dev) : MLXSW_SP_DEFAULT_VID;
	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_vid(mlxsw_sp_port, vid);
	अगर (!mlxsw_sp_port_vlan || !mlxsw_sp_port_vlan->bridge_port)
		वापस;

	mlxsw_sp_port_vlan_bridge_leave(mlxsw_sp_port_vlan);
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_8021d_vxlan_join(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				 स्थिर काष्ठा net_device *vxlan_dev, u16 vid,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);
	काष्ठा vxlan_dev *vxlan = netdev_priv(vxlan_dev);
	काष्ठा mlxsw_sp_nve_params params = अणु
		.type = MLXSW_SP_NVE_TYPE_VXLAN,
		.vni = vxlan->cfg.vni,
		.dev = vxlan_dev,
		.ethertype = ETH_P_8021Q,
	पूर्ण;
	काष्ठा mlxsw_sp_fid *fid;
	पूर्णांक err;

	fid = mlxsw_sp_fid_8021d_get(mlxsw_sp, bridge_device->dev->अगरindex);
	अगर (IS_ERR(fid)) अणु
		NL_SET_ERR_MSG_MOD(extack, "Failed to create 802.1D FID");
		वापस -EINVAL;
	पूर्ण

	अगर (mlxsw_sp_fid_vni_is_set(fid)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VNI is already set on FID");
		err = -EINVAL;
		जाओ err_vni_exists;
	पूर्ण

	err = mlxsw_sp_nve_fid_enable(mlxsw_sp, fid, &params, extack);
	अगर (err)
		जाओ err_nve_fid_enable;

	वापस 0;

err_nve_fid_enable:
err_vni_exists:
	mlxsw_sp_fid_put(fid);
	वापस err;
पूर्ण

अटल काष्ठा mlxsw_sp_fid *
mlxsw_sp_bridge_8021d_fid_get(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			      u16 vid, काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);

	वापस mlxsw_sp_fid_8021d_get(mlxsw_sp, bridge_device->dev->अगरindex);
पूर्ण

अटल काष्ठा mlxsw_sp_fid *
mlxsw_sp_bridge_8021d_fid_lookup(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				 u16 vid)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_lower_get(bridge_device->dev);

	/* The only valid VLAN क्रम a VLAN-unaware bridge is 0 */
	अगर (vid)
		वापस शून्य;

	वापस mlxsw_sp_fid_8021d_lookup(mlxsw_sp, bridge_device->dev->अगरindex);
पूर्ण

अटल u16
mlxsw_sp_bridge_8021d_fid_vid(काष्ठा mlxsw_sp_bridge_device *bridge_device,
			      स्थिर काष्ठा mlxsw_sp_fid *fid)
अणु
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_bridge_ops mlxsw_sp_bridge_8021d_ops = अणु
	.port_join	= mlxsw_sp_bridge_8021d_port_join,
	.port_leave	= mlxsw_sp_bridge_8021d_port_leave,
	.vxlan_join	= mlxsw_sp_bridge_8021d_vxlan_join,
	.fid_get	= mlxsw_sp_bridge_8021d_fid_get,
	.fid_lookup	= mlxsw_sp_bridge_8021d_fid_lookup,
	.fid_vid	= mlxsw_sp_bridge_8021d_fid_vid,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_bridge_8021ad_port_join(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				 काष्ठा mlxsw_sp_bridge_port *bridge_port,
				 काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				 काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	err = mlxsw_sp_port_vlan_classअगरication_set(mlxsw_sp_port, true, false);
	अगर (err)
		वापस err;

	err = mlxsw_sp_bridge_vlan_aware_port_join(bridge_port, mlxsw_sp_port,
						   extack);
	अगर (err)
		जाओ err_bridge_vlan_aware_port_join;

	वापस 0;

err_bridge_vlan_aware_port_join:
	mlxsw_sp_port_vlan_classअगरication_set(mlxsw_sp_port, false, true);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_bridge_8021ad_port_leave(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				  काष्ठा mlxsw_sp_bridge_port *bridge_port,
				  काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	mlxsw_sp_bridge_vlan_aware_port_leave(mlxsw_sp_port);
	mlxsw_sp_port_vlan_classअगरication_set(mlxsw_sp_port, false, true);
पूर्ण

अटल पूर्णांक
mlxsw_sp_bridge_8021ad_vxlan_join(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				  स्थिर काष्ठा net_device *vxlan_dev, u16 vid,
				  काष्ठा netlink_ext_ack *extack)
अणु
	वापस mlxsw_sp_bridge_vlan_aware_vxlan_join(bridge_device, vxlan_dev,
						     vid, ETH_P_8021AD, extack);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_bridge_ops mlxsw_sp1_bridge_8021ad_ops = अणु
	.port_join	= mlxsw_sp_bridge_8021ad_port_join,
	.port_leave	= mlxsw_sp_bridge_8021ad_port_leave,
	.vxlan_join	= mlxsw_sp_bridge_8021ad_vxlan_join,
	.fid_get	= mlxsw_sp_bridge_8021q_fid_get,
	.fid_lookup	= mlxsw_sp_bridge_8021q_fid_lookup,
	.fid_vid	= mlxsw_sp_bridge_8021q_fid_vid,
पूर्ण;

अटल पूर्णांक
mlxsw_sp2_bridge_8021ad_port_join(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				  काष्ठा mlxsw_sp_bridge_port *bridge_port,
				  काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				  काष्ठा netlink_ext_ack *extack)
अणु
	पूर्णांक err;

	/* The EtherType of decapsulated packets is determined at the egress
	 * port to allow 802.1d and 802.1ad bridges with VXLAN devices to
	 * co-exist.
	 */
	err = mlxsw_sp_port_egress_ethtype_set(mlxsw_sp_port, ETH_P_8021AD);
	अगर (err)
		वापस err;

	err = mlxsw_sp_bridge_8021ad_port_join(bridge_device, bridge_port,
					       mlxsw_sp_port, extack);
	अगर (err)
		जाओ err_bridge_8021ad_port_join;

	वापस 0;

err_bridge_8021ad_port_join:
	mlxsw_sp_port_egress_ethtype_set(mlxsw_sp_port, ETH_P_8021Q);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp2_bridge_8021ad_port_leave(काष्ठा mlxsw_sp_bridge_device *bridge_device,
				   काष्ठा mlxsw_sp_bridge_port *bridge_port,
				   काष्ठा mlxsw_sp_port *mlxsw_sp_port)
अणु
	mlxsw_sp_bridge_8021ad_port_leave(bridge_device, bridge_port,
					  mlxsw_sp_port);
	mlxsw_sp_port_egress_ethtype_set(mlxsw_sp_port, ETH_P_8021Q);
पूर्ण

अटल स्थिर काष्ठा mlxsw_sp_bridge_ops mlxsw_sp2_bridge_8021ad_ops = अणु
	.port_join	= mlxsw_sp2_bridge_8021ad_port_join,
	.port_leave	= mlxsw_sp2_bridge_8021ad_port_leave,
	.vxlan_join	= mlxsw_sp_bridge_8021ad_vxlan_join,
	.fid_get	= mlxsw_sp_bridge_8021q_fid_get,
	.fid_lookup	= mlxsw_sp_bridge_8021q_fid_lookup,
	.fid_vid	= mlxsw_sp_bridge_8021q_fid_vid,
पूर्ण;

पूर्णांक mlxsw_sp_port_bridge_join(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
			      काष्ठा net_device *brport_dev,
			      काष्ठा net_device *br_dev,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	पूर्णांक err;

	bridge_port = mlxsw_sp_bridge_port_get(mlxsw_sp->bridge, brport_dev,
					       extack);
	अगर (IS_ERR(bridge_port))
		वापस PTR_ERR(bridge_port);
	bridge_device = bridge_port->bridge_device;

	err = bridge_device->ops->port_join(bridge_device, bridge_port,
					    mlxsw_sp_port, extack);
	अगर (err)
		जाओ err_port_join;

	वापस 0;

err_port_join:
	mlxsw_sp_bridge_port_put(mlxsw_sp->bridge, bridge_port);
	वापस err;
पूर्ण

व्योम mlxsw_sp_port_bridge_leave(काष्ठा mlxsw_sp_port *mlxsw_sp_port,
				काष्ठा net_device *brport_dev,
				काष्ठा net_device *br_dev)
अणु
	काष्ठा mlxsw_sp *mlxsw_sp = mlxsw_sp_port->mlxsw_sp;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	अगर (!bridge_device)
		वापस;
	bridge_port = __mlxsw_sp_bridge_port_find(bridge_device, brport_dev);
	अगर (!bridge_port)
		वापस;

	bridge_device->ops->port_leave(bridge_device, bridge_port,
				       mlxsw_sp_port);
	mlxsw_sp_bridge_port_put(mlxsw_sp->bridge, bridge_port);
पूर्ण

पूर्णांक mlxsw_sp_bridge_vxlan_join(काष्ठा mlxsw_sp *mlxsw_sp,
			       स्थिर काष्ठा net_device *br_dev,
			       स्थिर काष्ठा net_device *vxlan_dev, u16 vid,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा mlxsw_sp_bridge_device *bridge_device;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	अगर (WARN_ON(!bridge_device))
		वापस -EINVAL;

	वापस bridge_device->ops->vxlan_join(bridge_device, vxlan_dev, vid,
					      extack);
पूर्ण

व्योम mlxsw_sp_bridge_vxlan_leave(काष्ठा mlxsw_sp *mlxsw_sp,
				 स्थिर काष्ठा net_device *vxlan_dev)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(vxlan_dev);
	काष्ठा mlxsw_sp_fid *fid;

	/* If the VxLAN device is करोwn, then the FID करोes not have a VNI */
	fid = mlxsw_sp_fid_lookup_by_vni(mlxsw_sp, vxlan->cfg.vni);
	अगर (!fid)
		वापस;

	mlxsw_sp_nve_fid_disable(mlxsw_sp, fid);
	/* Drop both the reference we just took during lookup and the reference
	 * the VXLAN device took.
	 */
	mlxsw_sp_fid_put(fid);
	mlxsw_sp_fid_put(fid);
पूर्ण

अटल व्योम
mlxsw_sp_चयनdev_vxlan_addr_convert(स्थिर जोड़ vxlan_addr *vxlan_addr,
				      क्रमागत mlxsw_sp_l3proto *proto,
				      जोड़ mlxsw_sp_l3addr *addr)
अणु
	अगर (vxlan_addr->sa.sa_family == AF_INET) अणु
		addr->addr4 = vxlan_addr->sin.sin_addr.s_addr;
		*proto = MLXSW_SP_L3_PROTO_IPV4;
	पूर्ण अन्यथा अणु
		addr->addr6 = vxlan_addr->sin6.sin6_addr;
		*proto = MLXSW_SP_L3_PROTO_IPV6;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_चयनdev_addr_vxlan_convert(क्रमागत mlxsw_sp_l3proto proto,
				      स्थिर जोड़ mlxsw_sp_l3addr *addr,
				      जोड़ vxlan_addr *vxlan_addr)
अणु
	चयन (proto) अणु
	हाल MLXSW_SP_L3_PROTO_IPV4:
		vxlan_addr->sa.sa_family = AF_INET;
		vxlan_addr->sin.sin_addr.s_addr = addr->addr4;
		अवरोध;
	हाल MLXSW_SP_L3_PROTO_IPV6:
		vxlan_addr->sa.sa_family = AF_INET6;
		vxlan_addr->sin6.sin6_addr = addr->addr6;
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_fdb_vxlan_call_notअगरiers(काष्ठा net_device *dev,
					      स्थिर अक्षर *mac,
					      क्रमागत mlxsw_sp_l3proto proto,
					      जोड़ mlxsw_sp_l3addr *addr,
					      __be32 vni, bool adding)
अणु
	काष्ठा चयनdev_notअगरier_vxlan_fdb_info info;
	काष्ठा vxlan_dev *vxlan = netdev_priv(dev);
	क्रमागत चयनdev_notअगरier_type type;

	type = adding ? SWITCHDEV_VXLAN_FDB_ADD_TO_BRIDGE :
			SWITCHDEV_VXLAN_FDB_DEL_TO_BRIDGE;
	mlxsw_sp_चयनdev_addr_vxlan_convert(proto, addr, &info.remote_ip);
	info.remote_port = vxlan->cfg.dst_port;
	info.remote_vni = vni;
	info.remote_अगरindex = 0;
	ether_addr_copy(info.eth_addr, mac);
	info.vni = vni;
	info.offloaded = adding;
	call_चयनdev_notअगरiers(type, dev, &info.info, शून्य);
पूर्ण

अटल व्योम mlxsw_sp_fdb_nve_call_notअगरiers(काष्ठा net_device *dev,
					    स्थिर अक्षर *mac,
					    क्रमागत mlxsw_sp_l3proto proto,
					    जोड़ mlxsw_sp_l3addr *addr,
					    __be32 vni,
					    bool adding)
अणु
	अगर (netअगर_is_vxlan(dev))
		mlxsw_sp_fdb_vxlan_call_notअगरiers(dev, mac, proto, addr, vni,
						  adding);
पूर्ण

अटल व्योम
mlxsw_sp_fdb_call_notअगरiers(क्रमागत चयनdev_notअगरier_type type,
			    स्थिर अक्षर *mac, u16 vid,
			    काष्ठा net_device *dev, bool offloaded)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info;

	info.addr = mac;
	info.vid = vid;
	info.offloaded = offloaded;
	call_चयनdev_notअगरiers(type, dev, &info.info, शून्य);
पूर्ण

अटल व्योम mlxsw_sp_fdb_notअगरy_mac_process(काष्ठा mlxsw_sp *mlxsw_sp,
					    अक्षर *sfn_pl, पूर्णांक rec_index,
					    bool adding)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	क्रमागत चयनdev_notअगरier_type type;
	अक्षर mac[ETH_ALEN];
	u8 local_port;
	u16 vid, fid;
	bool करो_notअगरication = true;
	पूर्णांक err;

	mlxsw_reg_sfn_mac_unpack(sfn_pl, rec_index, mac, &fid, &local_port);
	mlxsw_sp_port = mlxsw_sp->ports[local_port];
	अगर (!mlxsw_sp_port) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Incorrect local port in FDB notification\n");
		जाओ just_हटाओ;
	पूर्ण

	अगर (mlxsw_sp_fid_is_dummy(mlxsw_sp, fid))
		जाओ just_हटाओ;

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_fid(mlxsw_sp_port, fid);
	अगर (!mlxsw_sp_port_vlan) अणु
		netdev_err(mlxsw_sp_port->dev, "Failed to find a matching {Port, VID} following FDB notification\n");
		जाओ just_हटाओ;
	पूर्ण

	bridge_port = mlxsw_sp_port_vlan->bridge_port;
	अगर (!bridge_port) अणु
		netdev_err(mlxsw_sp_port->dev, "{Port, VID} not associated with a bridge\n");
		जाओ just_हटाओ;
	पूर्ण

	bridge_device = bridge_port->bridge_device;
	vid = bridge_device->vlan_enabled ? mlxsw_sp_port_vlan->vid : 0;

करो_fdb_op:
	err = mlxsw_sp_port_fdb_uc_op(mlxsw_sp, local_port, mac, fid,
				      adding, true);
	अगर (err) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to set FDB entry\n");
		वापस;
	पूर्ण

	अगर (!करो_notअगरication)
		वापस;
	type = adding ? SWITCHDEV_FDB_ADD_TO_BRIDGE : SWITCHDEV_FDB_DEL_TO_BRIDGE;
	mlxsw_sp_fdb_call_notअगरiers(type, mac, vid, bridge_port->dev, adding);

	वापस;

just_हटाओ:
	adding = false;
	करो_notअगरication = false;
	जाओ करो_fdb_op;
पूर्ण

अटल व्योम mlxsw_sp_fdb_notअगरy_mac_lag_process(काष्ठा mlxsw_sp *mlxsw_sp,
						अक्षर *sfn_pl, पूर्णांक rec_index,
						bool adding)
अणु
	काष्ठा mlxsw_sp_port_vlan *mlxsw_sp_port_vlan;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp_bridge_port *bridge_port;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	क्रमागत चयनdev_notअगरier_type type;
	अक्षर mac[ETH_ALEN];
	u16 lag_vid = 0;
	u16 lag_id;
	u16 vid, fid;
	bool करो_notअगरication = true;
	पूर्णांक err;

	mlxsw_reg_sfn_mac_lag_unpack(sfn_pl, rec_index, mac, &fid, &lag_id);
	mlxsw_sp_port = mlxsw_sp_lag_rep_port(mlxsw_sp, lag_id);
	अगर (!mlxsw_sp_port) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Cannot find port representor for LAG\n");
		जाओ just_हटाओ;
	पूर्ण

	अगर (mlxsw_sp_fid_is_dummy(mlxsw_sp, fid))
		जाओ just_हटाओ;

	mlxsw_sp_port_vlan = mlxsw_sp_port_vlan_find_by_fid(mlxsw_sp_port, fid);
	अगर (!mlxsw_sp_port_vlan) अणु
		netdev_err(mlxsw_sp_port->dev, "Failed to find a matching {Port, VID} following FDB notification\n");
		जाओ just_हटाओ;
	पूर्ण

	bridge_port = mlxsw_sp_port_vlan->bridge_port;
	अगर (!bridge_port) अणु
		netdev_err(mlxsw_sp_port->dev, "{Port, VID} not associated with a bridge\n");
		जाओ just_हटाओ;
	पूर्ण

	bridge_device = bridge_port->bridge_device;
	vid = bridge_device->vlan_enabled ? mlxsw_sp_port_vlan->vid : 0;
	lag_vid = mlxsw_sp_fid_lag_vid_valid(mlxsw_sp_port_vlan->fid) ?
		  mlxsw_sp_port_vlan->vid : 0;

करो_fdb_op:
	err = mlxsw_sp_port_fdb_uc_lag_op(mlxsw_sp, lag_id, mac, fid, lag_vid,
					  adding, true);
	अगर (err) अणु
		dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to set FDB entry\n");
		वापस;
	पूर्ण

	अगर (!करो_notअगरication)
		वापस;
	type = adding ? SWITCHDEV_FDB_ADD_TO_BRIDGE : SWITCHDEV_FDB_DEL_TO_BRIDGE;
	mlxsw_sp_fdb_call_notअगरiers(type, mac, vid, bridge_port->dev, adding);

	वापस;

just_हटाओ:
	adding = false;
	करो_notअगरication = false;
	जाओ करो_fdb_op;
पूर्ण

अटल पूर्णांक
__mlxsw_sp_fdb_notअगरy_mac_uc_tunnel_process(काष्ठा mlxsw_sp *mlxsw_sp,
					    स्थिर काष्ठा mlxsw_sp_fid *fid,
					    bool adding,
					    काष्ठा net_device **nve_dev,
					    u16 *p_vid, __be32 *p_vni)
अणु
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा net_device *br_dev, *dev;
	पूर्णांक nve_अगरindex;
	पूर्णांक err;

	err = mlxsw_sp_fid_nve_अगरindex(fid, &nve_अगरindex);
	अगर (err)
		वापस err;

	err = mlxsw_sp_fid_vni(fid, p_vni);
	अगर (err)
		वापस err;

	dev = __dev_get_by_index(mlxsw_sp_net(mlxsw_sp), nve_अगरindex);
	अगर (!dev)
		वापस -EINVAL;
	*nve_dev = dev;

	अगर (!netअगर_running(dev))
		वापस -EINVAL;

	अगर (adding && !br_port_flag_is_set(dev, BR_LEARNING))
		वापस -EINVAL;

	अगर (adding && netअगर_is_vxlan(dev)) अणु
		काष्ठा vxlan_dev *vxlan = netdev_priv(dev);

		अगर (!(vxlan->cfg.flags & VXLAN_F_LEARN))
			वापस -EINVAL;
	पूर्ण

	br_dev = netdev_master_upper_dev_get(dev);
	अगर (!br_dev)
		वापस -EINVAL;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	अगर (!bridge_device)
		वापस -EINVAL;

	*p_vid = bridge_device->ops->fid_vid(bridge_device, fid);

	वापस 0;
पूर्ण

अटल व्योम mlxsw_sp_fdb_notअगरy_mac_uc_tunnel_process(काष्ठा mlxsw_sp *mlxsw_sp,
						      अक्षर *sfn_pl,
						      पूर्णांक rec_index,
						      bool adding)
अणु
	क्रमागत mlxsw_reg_sfn_uc_tunnel_protocol sfn_proto;
	क्रमागत चयनdev_notअगरier_type type;
	काष्ठा net_device *nve_dev;
	जोड़ mlxsw_sp_l3addr addr;
	काष्ठा mlxsw_sp_fid *fid;
	अक्षर mac[ETH_ALEN];
	u16 fid_index, vid;
	__be32 vni;
	u32 uip;
	पूर्णांक err;

	mlxsw_reg_sfn_uc_tunnel_unpack(sfn_pl, rec_index, mac, &fid_index,
				       &uip, &sfn_proto);

	fid = mlxsw_sp_fid_lookup_by_index(mlxsw_sp, fid_index);
	अगर (!fid)
		जाओ err_fid_lookup;

	err = mlxsw_sp_nve_learned_ip_resolve(mlxsw_sp, uip,
					      (क्रमागत mlxsw_sp_l3proto) sfn_proto,
					      &addr);
	अगर (err)
		जाओ err_ip_resolve;

	err = __mlxsw_sp_fdb_notअगरy_mac_uc_tunnel_process(mlxsw_sp, fid, adding,
							  &nve_dev, &vid, &vni);
	अगर (err)
		जाओ err_fdb_process;

	err = mlxsw_sp_port_fdb_tunnel_uc_op(mlxsw_sp, mac, fid_index,
					     (क्रमागत mlxsw_sp_l3proto) sfn_proto,
					     &addr, adding, true);
	अगर (err)
		जाओ err_fdb_op;

	mlxsw_sp_fdb_nve_call_notअगरiers(nve_dev, mac,
					(क्रमागत mlxsw_sp_l3proto) sfn_proto,
					&addr, vni, adding);

	type = adding ? SWITCHDEV_FDB_ADD_TO_BRIDGE :
			SWITCHDEV_FDB_DEL_TO_BRIDGE;
	mlxsw_sp_fdb_call_notअगरiers(type, mac, vid, nve_dev, adding);

	mlxsw_sp_fid_put(fid);

	वापस;

err_fdb_op:
err_fdb_process:
err_ip_resolve:
	mlxsw_sp_fid_put(fid);
err_fid_lookup:
	/* Remove an FDB entry in हाल we cannot process it. Otherwise the
	 * device will keep sending the same notअगरication over and over again.
	 */
	mlxsw_sp_port_fdb_tunnel_uc_op(mlxsw_sp, mac, fid_index,
				       (क्रमागत mlxsw_sp_l3proto) sfn_proto, &addr,
				       false, true);
पूर्ण

अटल व्योम mlxsw_sp_fdb_notअगरy_rec_process(काष्ठा mlxsw_sp *mlxsw_sp,
					    अक्षर *sfn_pl, पूर्णांक rec_index)
अणु
	चयन (mlxsw_reg_sfn_rec_type_get(sfn_pl, rec_index)) अणु
	हाल MLXSW_REG_SFN_REC_TYPE_LEARNED_MAC:
		mlxsw_sp_fdb_notअगरy_mac_process(mlxsw_sp, sfn_pl,
						rec_index, true);
		अवरोध;
	हाल MLXSW_REG_SFN_REC_TYPE_AGED_OUT_MAC:
		mlxsw_sp_fdb_notअगरy_mac_process(mlxsw_sp, sfn_pl,
						rec_index, false);
		अवरोध;
	हाल MLXSW_REG_SFN_REC_TYPE_LEARNED_MAC_LAG:
		mlxsw_sp_fdb_notअगरy_mac_lag_process(mlxsw_sp, sfn_pl,
						    rec_index, true);
		अवरोध;
	हाल MLXSW_REG_SFN_REC_TYPE_AGED_OUT_MAC_LAG:
		mlxsw_sp_fdb_notअगरy_mac_lag_process(mlxsw_sp, sfn_pl,
						    rec_index, false);
		अवरोध;
	हाल MLXSW_REG_SFN_REC_TYPE_LEARNED_UNICAST_TUNNEL:
		mlxsw_sp_fdb_notअगरy_mac_uc_tunnel_process(mlxsw_sp, sfn_pl,
							  rec_index, true);
		अवरोध;
	हाल MLXSW_REG_SFN_REC_TYPE_AGED_OUT_UNICAST_TUNNEL:
		mlxsw_sp_fdb_notअगरy_mac_uc_tunnel_process(mlxsw_sp, sfn_pl,
							  rec_index, false);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम mlxsw_sp_fdb_notअगरy_work_schedule(काष्ठा mlxsw_sp *mlxsw_sp,
					      bool no_delay)
अणु
	काष्ठा mlxsw_sp_bridge *bridge = mlxsw_sp->bridge;
	अचिन्हित पूर्णांक पूर्णांकerval = no_delay ? 0 : bridge->fdb_notअगरy.पूर्णांकerval;

	mlxsw_core_schedule_dw(&bridge->fdb_notअगरy.dw,
			       msecs_to_jअगरfies(पूर्णांकerval));
पूर्ण

#घोषणा MLXSW_SP_FDB_SFN_QUERIES_PER_SESSION 10

अटल व्योम mlxsw_sp_fdb_notअगरy_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_bridge *bridge;
	काष्ठा mlxsw_sp *mlxsw_sp;
	अक्षर *sfn_pl;
	पूर्णांक queries;
	u8 num_rec;
	पूर्णांक i;
	पूर्णांक err;

	sfn_pl = kदो_स्मृति(MLXSW_REG_SFN_LEN, GFP_KERNEL);
	अगर (!sfn_pl)
		वापस;

	bridge = container_of(work, काष्ठा mlxsw_sp_bridge, fdb_notअगरy.dw.work);
	mlxsw_sp = bridge->mlxsw_sp;

	rtnl_lock();
	queries = MLXSW_SP_FDB_SFN_QUERIES_PER_SESSION;
	जबतक (queries > 0) अणु
		mlxsw_reg_sfn_pack(sfn_pl);
		err = mlxsw_reg_query(mlxsw_sp->core, MLXSW_REG(sfn), sfn_pl);
		अगर (err) अणु
			dev_err_ratelimited(mlxsw_sp->bus_info->dev, "Failed to get FDB notifications\n");
			जाओ out;
		पूर्ण
		num_rec = mlxsw_reg_sfn_num_rec_get(sfn_pl);
		क्रम (i = 0; i < num_rec; i++)
			mlxsw_sp_fdb_notअगरy_rec_process(mlxsw_sp, sfn_pl, i);
		अगर (num_rec != MLXSW_REG_SFN_REC_MAX_COUNT)
			जाओ out;
		queries--;
	पूर्ण

out:
	rtnl_unlock();
	kमुक्त(sfn_pl);
	mlxsw_sp_fdb_notअगरy_work_schedule(mlxsw_sp, !queries);
पूर्ण

काष्ठा mlxsw_sp_चयनdev_event_work अणु
	काष्ठा work_काष्ठा work;
	जोड़ अणु
		काष्ठा चयनdev_notअगरier_fdb_info fdb_info;
		काष्ठा चयनdev_notअगरier_vxlan_fdb_info vxlan_fdb_info;
	पूर्ण;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ event;
पूर्ण;

अटल व्योम
mlxsw_sp_चयनdev_bridge_vxlan_fdb_event(काष्ठा mlxsw_sp *mlxsw_sp,
					  काष्ठा mlxsw_sp_चयनdev_event_work *
					  चयनdev_work,
					  काष्ठा mlxsw_sp_fid *fid, __be32 vni)
अणु
	काष्ठा चयनdev_notअगरier_vxlan_fdb_info vxlan_fdb_info;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	काष्ठा net_device *dev = चयनdev_work->dev;
	क्रमागत mlxsw_sp_l3proto proto;
	जोड़ mlxsw_sp_l3addr addr;
	पूर्णांक err;

	fdb_info = &चयनdev_work->fdb_info;
	err = vxlan_fdb_find_uc(dev, fdb_info->addr, vni, &vxlan_fdb_info);
	अगर (err)
		वापस;

	mlxsw_sp_चयनdev_vxlan_addr_convert(&vxlan_fdb_info.remote_ip,
					      &proto, &addr);

	चयन (चयनdev_work->event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
		err = mlxsw_sp_port_fdb_tunnel_uc_op(mlxsw_sp,
						     vxlan_fdb_info.eth_addr,
						     mlxsw_sp_fid_index(fid),
						     proto, &addr, true, false);
		अगर (err)
			वापस;
		vxlan_fdb_info.offloaded = true;
		call_चयनdev_notअगरiers(SWITCHDEV_VXLAN_FDB_OFFLOADED, dev,
					 &vxlan_fdb_info.info, शून्य);
		mlxsw_sp_fdb_call_notअगरiers(SWITCHDEV_FDB_OFFLOADED,
					    vxlan_fdb_info.eth_addr,
					    fdb_info->vid, dev, true);
		अवरोध;
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		err = mlxsw_sp_port_fdb_tunnel_uc_op(mlxsw_sp,
						     vxlan_fdb_info.eth_addr,
						     mlxsw_sp_fid_index(fid),
						     proto, &addr, false,
						     false);
		vxlan_fdb_info.offloaded = false;
		call_चयनdev_notअगरiers(SWITCHDEV_VXLAN_FDB_OFFLOADED, dev,
					 &vxlan_fdb_info.info, शून्य);
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
mlxsw_sp_चयनdev_bridge_nve_fdb_event(काष्ठा mlxsw_sp_चयनdev_event_work *
					चयनdev_work)
अणु
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा net_device *dev = चयनdev_work->dev;
	काष्ठा net_device *br_dev;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा mlxsw_sp_fid *fid;
	__be32 vni;
	पूर्णांक err;

	अगर (चयनdev_work->event != SWITCHDEV_FDB_ADD_TO_DEVICE &&
	    चयनdev_work->event != SWITCHDEV_FDB_DEL_TO_DEVICE)
		वापस;

	अगर (चयनdev_work->event == SWITCHDEV_FDB_ADD_TO_DEVICE &&
	    (!चयनdev_work->fdb_info.added_by_user ||
	     चयनdev_work->fdb_info.is_local))
		वापस;

	अगर (!netअगर_running(dev))
		वापस;
	br_dev = netdev_master_upper_dev_get(dev);
	अगर (!br_dev)
		वापस;
	अगर (!netअगर_is_bridge_master(br_dev))
		वापस;
	mlxsw_sp = mlxsw_sp_lower_get(br_dev);
	अगर (!mlxsw_sp)
		वापस;
	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	अगर (!bridge_device)
		वापस;

	fid = bridge_device->ops->fid_lookup(bridge_device,
					     चयनdev_work->fdb_info.vid);
	अगर (!fid)
		वापस;

	err = mlxsw_sp_fid_vni(fid, &vni);
	अगर (err)
		जाओ out;

	mlxsw_sp_चयनdev_bridge_vxlan_fdb_event(mlxsw_sp, चयनdev_work, fid,
						  vni);

out:
	mlxsw_sp_fid_put(fid);
पूर्ण

अटल व्योम mlxsw_sp_चयनdev_bridge_fdb_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_चयनdev_event_work *चयनdev_work =
		container_of(work, काष्ठा mlxsw_sp_चयनdev_event_work, work);
	काष्ठा net_device *dev = चयनdev_work->dev;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	काष्ठा mlxsw_sp_port *mlxsw_sp_port;
	पूर्णांक err;

	rtnl_lock();
	अगर (netअगर_is_vxlan(dev)) अणु
		mlxsw_sp_चयनdev_bridge_nve_fdb_event(चयनdev_work);
		जाओ out;
	पूर्ण

	mlxsw_sp_port = mlxsw_sp_port_dev_lower_find(dev);
	अगर (!mlxsw_sp_port)
		जाओ out;

	चयन (चयनdev_work->event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb_info = &चयनdev_work->fdb_info;
		अगर (!fdb_info->added_by_user || fdb_info->is_local)
			अवरोध;
		err = mlxsw_sp_port_fdb_set(mlxsw_sp_port, fdb_info, true);
		अगर (err)
			अवरोध;
		mlxsw_sp_fdb_call_notअगरiers(SWITCHDEV_FDB_OFFLOADED,
					    fdb_info->addr,
					    fdb_info->vid, dev, true);
		अवरोध;
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		fdb_info = &चयनdev_work->fdb_info;
		mlxsw_sp_port_fdb_set(mlxsw_sp_port, fdb_info, false);
		अवरोध;
	हाल SWITCHDEV_FDB_ADD_TO_BRIDGE:
	हाल SWITCHDEV_FDB_DEL_TO_BRIDGE:
		/* These events are only used to potentially update an existing
		 * SPAN mirror.
		 */
		अवरोध;
	पूर्ण

	mlxsw_sp_span_respin(mlxsw_sp_port->mlxsw_sp);

out:
	rtnl_unlock();
	kमुक्त(चयनdev_work->fdb_info.addr);
	kमुक्त(चयनdev_work);
	dev_put(dev);
पूर्ण

अटल व्योम
mlxsw_sp_चयनdev_vxlan_fdb_add(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_चयनdev_event_work *
				 चयनdev_work)
अणु
	काष्ठा चयनdev_notअगरier_vxlan_fdb_info *vxlan_fdb_info;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा net_device *dev = चयनdev_work->dev;
	u8 all_zeros_mac[ETH_ALEN] = अणु 0 पूर्ण;
	क्रमागत mlxsw_sp_l3proto proto;
	जोड़ mlxsw_sp_l3addr addr;
	काष्ठा net_device *br_dev;
	काष्ठा mlxsw_sp_fid *fid;
	u16 vid;
	पूर्णांक err;

	vxlan_fdb_info = &चयनdev_work->vxlan_fdb_info;
	br_dev = netdev_master_upper_dev_get(dev);

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	अगर (!bridge_device)
		वापस;

	fid = mlxsw_sp_fid_lookup_by_vni(mlxsw_sp, vxlan_fdb_info->vni);
	अगर (!fid)
		वापस;

	mlxsw_sp_चयनdev_vxlan_addr_convert(&vxlan_fdb_info->remote_ip,
					      &proto, &addr);

	अगर (ether_addr_equal(vxlan_fdb_info->eth_addr, all_zeros_mac)) अणु
		err = mlxsw_sp_nve_flood_ip_add(mlxsw_sp, fid, proto, &addr);
		अगर (err) अणु
			mlxsw_sp_fid_put(fid);
			वापस;
		पूर्ण
		vxlan_fdb_info->offloaded = true;
		call_चयनdev_notअगरiers(SWITCHDEV_VXLAN_FDB_OFFLOADED, dev,
					 &vxlan_fdb_info->info, शून्य);
		mlxsw_sp_fid_put(fid);
		वापस;
	पूर्ण

	/* The device has a single FDB table, whereas Linux has two - one
	 * in the bridge driver and another in the VxLAN driver. We only
	 * program an entry to the device अगर the MAC poपूर्णांकs to the VxLAN
	 * device in the bridge's FDB table
	 */
	vid = bridge_device->ops->fid_vid(bridge_device, fid);
	अगर (br_fdb_find_port(br_dev, vxlan_fdb_info->eth_addr, vid) != dev)
		जाओ err_br_fdb_find;

	err = mlxsw_sp_port_fdb_tunnel_uc_op(mlxsw_sp, vxlan_fdb_info->eth_addr,
					     mlxsw_sp_fid_index(fid), proto,
					     &addr, true, false);
	अगर (err)
		जाओ err_fdb_tunnel_uc_op;
	vxlan_fdb_info->offloaded = true;
	call_चयनdev_notअगरiers(SWITCHDEV_VXLAN_FDB_OFFLOADED, dev,
				 &vxlan_fdb_info->info, शून्य);
	mlxsw_sp_fdb_call_notअगरiers(SWITCHDEV_FDB_OFFLOADED,
				    vxlan_fdb_info->eth_addr, vid, dev, true);

	mlxsw_sp_fid_put(fid);

	वापस;

err_fdb_tunnel_uc_op:
err_br_fdb_find:
	mlxsw_sp_fid_put(fid);
पूर्ण

अटल व्योम
mlxsw_sp_चयनdev_vxlan_fdb_del(काष्ठा mlxsw_sp *mlxsw_sp,
				 काष्ठा mlxsw_sp_चयनdev_event_work *
				 चयनdev_work)
अणु
	काष्ठा चयनdev_notअगरier_vxlan_fdb_info *vxlan_fdb_info;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा net_device *dev = चयनdev_work->dev;
	काष्ठा net_device *br_dev = netdev_master_upper_dev_get(dev);
	u8 all_zeros_mac[ETH_ALEN] = अणु 0 पूर्ण;
	क्रमागत mlxsw_sp_l3proto proto;
	जोड़ mlxsw_sp_l3addr addr;
	काष्ठा mlxsw_sp_fid *fid;
	u16 vid;

	vxlan_fdb_info = &चयनdev_work->vxlan_fdb_info;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	अगर (!bridge_device)
		वापस;

	fid = mlxsw_sp_fid_lookup_by_vni(mlxsw_sp, vxlan_fdb_info->vni);
	अगर (!fid)
		वापस;

	mlxsw_sp_चयनdev_vxlan_addr_convert(&vxlan_fdb_info->remote_ip,
					      &proto, &addr);

	अगर (ether_addr_equal(vxlan_fdb_info->eth_addr, all_zeros_mac)) अणु
		mlxsw_sp_nve_flood_ip_del(mlxsw_sp, fid, proto, &addr);
		mlxsw_sp_fid_put(fid);
		वापस;
	पूर्ण

	mlxsw_sp_port_fdb_tunnel_uc_op(mlxsw_sp, vxlan_fdb_info->eth_addr,
				       mlxsw_sp_fid_index(fid), proto, &addr,
				       false, false);
	vid = bridge_device->ops->fid_vid(bridge_device, fid);
	mlxsw_sp_fdb_call_notअगरiers(SWITCHDEV_FDB_OFFLOADED,
				    vxlan_fdb_info->eth_addr, vid, dev, false);

	mlxsw_sp_fid_put(fid);
पूर्ण

अटल व्योम mlxsw_sp_चयनdev_vxlan_fdb_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mlxsw_sp_चयनdev_event_work *चयनdev_work =
		container_of(work, काष्ठा mlxsw_sp_चयनdev_event_work, work);
	काष्ठा net_device *dev = चयनdev_work->dev;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा net_device *br_dev;

	rtnl_lock();

	अगर (!netअगर_running(dev))
		जाओ out;
	br_dev = netdev_master_upper_dev_get(dev);
	अगर (!br_dev)
		जाओ out;
	अगर (!netअगर_is_bridge_master(br_dev))
		जाओ out;
	mlxsw_sp = mlxsw_sp_lower_get(br_dev);
	अगर (!mlxsw_sp)
		जाओ out;

	चयन (चयनdev_work->event) अणु
	हाल SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE:
		mlxsw_sp_चयनdev_vxlan_fdb_add(mlxsw_sp, चयनdev_work);
		अवरोध;
	हाल SWITCHDEV_VXLAN_FDB_DEL_TO_DEVICE:
		mlxsw_sp_चयनdev_vxlan_fdb_del(mlxsw_sp, चयनdev_work);
		अवरोध;
	पूर्ण

out:
	rtnl_unlock();
	kमुक्त(चयनdev_work);
	dev_put(dev);
पूर्ण

अटल पूर्णांक
mlxsw_sp_चयनdev_vxlan_work_prepare(काष्ठा mlxsw_sp_चयनdev_event_work *
				      चयनdev_work,
				      काष्ठा चयनdev_notअगरier_info *info)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(चयनdev_work->dev);
	काष्ठा चयनdev_notअगरier_vxlan_fdb_info *vxlan_fdb_info;
	काष्ठा vxlan_config *cfg = &vxlan->cfg;
	काष्ठा netlink_ext_ack *extack;

	extack = चयनdev_notअगरier_info_to_extack(info);
	vxlan_fdb_info = container_of(info,
				      काष्ठा चयनdev_notअगरier_vxlan_fdb_info,
				      info);

	अगर (vxlan_fdb_info->remote_port != cfg->dst_port) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: FDB: Non-default remote port is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (vxlan_fdb_info->remote_vni != cfg->vni ||
	    vxlan_fdb_info->vni != cfg->vni) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: FDB: Non-default VNI is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (vxlan_fdb_info->remote_अगरindex) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: FDB: Local interface is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (is_multicast_ether_addr(vxlan_fdb_info->eth_addr)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: FDB: Multicast MAC addresses not supported");
		वापस -EOPNOTSUPP;
	पूर्ण
	अगर (vxlan_addr_multicast(&vxlan_fdb_info->remote_ip)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VxLAN: FDB: Multicast destination IP is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	चयनdev_work->vxlan_fdb_info = *vxlan_fdb_info;

	वापस 0;
पूर्ण

/* Called under rcu_पढ़ो_lock() */
अटल पूर्णांक mlxsw_sp_चयनdev_event(काष्ठा notअगरier_block *unused,
				    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	काष्ठा mlxsw_sp_चयनdev_event_work *चयनdev_work;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	काष्ठा चयनdev_notअगरier_info *info = ptr;
	काष्ठा net_device *br_dev;
	पूर्णांक err;

	अगर (event == SWITCHDEV_PORT_ATTR_SET) अणु
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     mlxsw_sp_port_dev_check,
						     mlxsw_sp_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	/* Tunnel devices are not our uppers, so check their master instead */
	br_dev = netdev_master_upper_dev_get_rcu(dev);
	अगर (!br_dev)
		वापस NOTIFY_DONE;
	अगर (!netअगर_is_bridge_master(br_dev))
		वापस NOTIFY_DONE;
	अगर (!mlxsw_sp_port_dev_lower_find_rcu(br_dev))
		वापस NOTIFY_DONE;

	चयनdev_work = kzalloc(माप(*चयनdev_work), GFP_ATOMIC);
	अगर (!चयनdev_work)
		वापस NOTIFY_BAD;

	चयनdev_work->dev = dev;
	चयनdev_work->event = event;

	चयन (event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
	हाल SWITCHDEV_FDB_ADD_TO_BRIDGE:
	हाल SWITCHDEV_FDB_DEL_TO_BRIDGE:
		fdb_info = container_of(info,
					काष्ठा चयनdev_notअगरier_fdb_info,
					info);
		INIT_WORK(&चयनdev_work->work,
			  mlxsw_sp_चयनdev_bridge_fdb_event_work);
		स_नकल(&चयनdev_work->fdb_info, ptr,
		       माप(चयनdev_work->fdb_info));
		चयनdev_work->fdb_info.addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
		अगर (!चयनdev_work->fdb_info.addr)
			जाओ err_addr_alloc;
		ether_addr_copy((u8 *)चयनdev_work->fdb_info.addr,
				fdb_info->addr);
		/* Take a reference on the device. This can be either
		 * upper device containig mlxsw_sp_port or just a
		 * mlxsw_sp_port
		 */
		dev_hold(dev);
		अवरोध;
	हाल SWITCHDEV_VXLAN_FDB_ADD_TO_DEVICE:
	हाल SWITCHDEV_VXLAN_FDB_DEL_TO_DEVICE:
		INIT_WORK(&चयनdev_work->work,
			  mlxsw_sp_चयनdev_vxlan_fdb_event_work);
		err = mlxsw_sp_चयनdev_vxlan_work_prepare(चयनdev_work,
							    info);
		अगर (err)
			जाओ err_vxlan_work_prepare;
		dev_hold(dev);
		अवरोध;
	शेष:
		kमुक्त(चयनdev_work);
		वापस NOTIFY_DONE;
	पूर्ण

	mlxsw_core_schedule_work(&चयनdev_work->work);

	वापस NOTIFY_DONE;

err_vxlan_work_prepare:
err_addr_alloc:
	kमुक्त(चयनdev_work);
	वापस NOTIFY_BAD;
पूर्ण

काष्ठा notअगरier_block mlxsw_sp_चयनdev_notअगरier = अणु
	.notअगरier_call = mlxsw_sp_चयनdev_event,
पूर्ण;

अटल पूर्णांक
mlxsw_sp_चयनdev_vxlan_vlan_add(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_bridge_device *bridge_device,
				  स्थिर काष्ठा net_device *vxlan_dev, u16 vid,
				  bool flag_untagged, bool flag_pvid,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(vxlan_dev);
	__be32 vni = vxlan->cfg.vni;
	काष्ठा mlxsw_sp_fid *fid;
	u16 old_vid;
	पूर्णांक err;

	/* We cannot have the same VLAN as PVID and egress untagged on multiple
	 * VxLAN devices. Note that we get this notअगरication beक्रमe the VLAN is
	 * actually added to the bridge's database, so it is not possible क्रम
	 * the lookup function to वापस 'vxlan_dev'
	 */
	अगर (flag_untagged && flag_pvid &&
	    mlxsw_sp_bridge_8021q_vxlan_dev_find(bridge_device->dev, vid)) अणु
		NL_SET_ERR_MSG_MOD(extack, "VLAN already mapped to a different VNI");
		वापस -EINVAL;
	पूर्ण

	अगर (!netअगर_running(vxlan_dev))
		वापस 0;

	/* First हाल: FID is not associated with this VNI, but the new VLAN
	 * is both PVID and egress untagged. Need to enable NVE on the FID, अगर
	 * it exists
	 */
	fid = mlxsw_sp_fid_lookup_by_vni(mlxsw_sp, vni);
	अगर (!fid) अणु
		अगर (!flag_untagged || !flag_pvid)
			वापस 0;
		वापस bridge_device->ops->vxlan_join(bridge_device, vxlan_dev,
						      vid, extack);
	पूर्ण

	/* Second हाल: FID is associated with the VNI and the VLAN associated
	 * with the FID is the same as the notअगरied VLAN. This means the flags
	 * (PVID / egress untagged) were toggled and that NVE should be
	 * disabled on the FID
	 */
	old_vid = mlxsw_sp_fid_8021q_vid(fid);
	अगर (vid == old_vid) अणु
		अगर (WARN_ON(flag_untagged && flag_pvid)) अणु
			mlxsw_sp_fid_put(fid);
			वापस -EINVAL;
		पूर्ण
		mlxsw_sp_bridge_vxlan_leave(mlxsw_sp, vxlan_dev);
		mlxsw_sp_fid_put(fid);
		वापस 0;
	पूर्ण

	/* Third हाल: A new VLAN was configured on the VxLAN device, but this
	 * VLAN is not PVID, so there is nothing to करो.
	 */
	अगर (!flag_pvid) अणु
		mlxsw_sp_fid_put(fid);
		वापस 0;
	पूर्ण

	/* Fourth हाल: Thew new VLAN is PVID, which means the VLAN currently
	 * mapped to the VNI should be unmapped
	 */
	mlxsw_sp_bridge_vxlan_leave(mlxsw_sp, vxlan_dev);
	mlxsw_sp_fid_put(fid);

	/* Fअगरth हाल: The new VLAN is also egress untagged, which means the
	 * VLAN needs to be mapped to the VNI
	 */
	अगर (!flag_untagged)
		वापस 0;

	err = bridge_device->ops->vxlan_join(bridge_device, vxlan_dev, vid, extack);
	अगर (err)
		जाओ err_vxlan_join;

	वापस 0;

err_vxlan_join:
	bridge_device->ops->vxlan_join(bridge_device, vxlan_dev, old_vid, शून्य);
	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_चयनdev_vxlan_vlan_del(काष्ठा mlxsw_sp *mlxsw_sp,
				  काष्ठा mlxsw_sp_bridge_device *bridge_device,
				  स्थिर काष्ठा net_device *vxlan_dev, u16 vid)
अणु
	काष्ठा vxlan_dev *vxlan = netdev_priv(vxlan_dev);
	__be32 vni = vxlan->cfg.vni;
	काष्ठा mlxsw_sp_fid *fid;

	अगर (!netअगर_running(vxlan_dev))
		वापस;

	fid = mlxsw_sp_fid_lookup_by_vni(mlxsw_sp, vni);
	अगर (!fid)
		वापस;

	/* A dअगरferent VLAN than the one mapped to the VNI is deleted */
	अगर (mlxsw_sp_fid_8021q_vid(fid) != vid)
		जाओ out;

	mlxsw_sp_bridge_vxlan_leave(mlxsw_sp, vxlan_dev);

out:
	mlxsw_sp_fid_put(fid);
पूर्ण

अटल पूर्णांक
mlxsw_sp_चयनdev_vxlan_vlans_add(काष्ठा net_device *vxlan_dev,
				   काष्ठा चयनdev_notअगरier_port_obj_info *
				   port_obj_info)
अणु
	काष्ठा चयनdev_obj_port_vlan *vlan =
		SWITCHDEV_OBJ_PORT_VLAN(port_obj_info->obj);
	bool flag_untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool flag_pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा net_device *br_dev;

	extack = चयनdev_notअगरier_info_to_extack(&port_obj_info->info);
	br_dev = netdev_master_upper_dev_get(vxlan_dev);
	अगर (!br_dev)
		वापस 0;

	mlxsw_sp = mlxsw_sp_lower_get(br_dev);
	अगर (!mlxsw_sp)
		वापस 0;

	port_obj_info->handled = true;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	अगर (!bridge_device)
		वापस -EINVAL;

	अगर (!bridge_device->vlan_enabled)
		वापस 0;

	वापस mlxsw_sp_चयनdev_vxlan_vlan_add(mlxsw_sp, bridge_device,
						 vxlan_dev, vlan->vid,
						 flag_untagged,
						 flag_pvid, extack);
पूर्ण

अटल व्योम
mlxsw_sp_चयनdev_vxlan_vlans_del(काष्ठा net_device *vxlan_dev,
				   काष्ठा चयनdev_notअगरier_port_obj_info *
				   port_obj_info)
अणु
	काष्ठा चयनdev_obj_port_vlan *vlan =
		SWITCHDEV_OBJ_PORT_VLAN(port_obj_info->obj);
	काष्ठा mlxsw_sp_bridge_device *bridge_device;
	काष्ठा mlxsw_sp *mlxsw_sp;
	काष्ठा net_device *br_dev;

	br_dev = netdev_master_upper_dev_get(vxlan_dev);
	अगर (!br_dev)
		वापस;

	mlxsw_sp = mlxsw_sp_lower_get(br_dev);
	अगर (!mlxsw_sp)
		वापस;

	port_obj_info->handled = true;

	bridge_device = mlxsw_sp_bridge_device_find(mlxsw_sp->bridge, br_dev);
	अगर (!bridge_device)
		वापस;

	अगर (!bridge_device->vlan_enabled)
		वापस;

	mlxsw_sp_चयनdev_vxlan_vlan_del(mlxsw_sp, bridge_device, vxlan_dev,
					  vlan->vid);
पूर्ण

अटल पूर्णांक
mlxsw_sp_चयनdev_handle_vxlan_obj_add(काष्ठा net_device *vxlan_dev,
					काष्ठा चयनdev_notअगरier_port_obj_info *
					port_obj_info)
अणु
	पूर्णांक err = 0;

	चयन (port_obj_info->obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = mlxsw_sp_चयनdev_vxlan_vlans_add(vxlan_dev,
							 port_obj_info);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
mlxsw_sp_चयनdev_handle_vxlan_obj_del(काष्ठा net_device *vxlan_dev,
					काष्ठा चयनdev_notअगरier_port_obj_info *
					port_obj_info)
अणु
	चयन (port_obj_info->obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		mlxsw_sp_चयनdev_vxlan_vlans_del(vxlan_dev, port_obj_info);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक mlxsw_sp_चयनdev_blocking_event(काष्ठा notअगरier_block *unused,
					     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	पूर्णांक err = 0;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
		अगर (netअगर_is_vxlan(dev))
			err = mlxsw_sp_चयनdev_handle_vxlan_obj_add(dev, ptr);
		अन्यथा
			err = चयनdev_handle_port_obj_add(dev, ptr,
							mlxsw_sp_port_dev_check,
							mlxsw_sp_port_obj_add);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_OBJ_DEL:
		अगर (netअगर_is_vxlan(dev))
			mlxsw_sp_चयनdev_handle_vxlan_obj_del(dev, ptr);
		अन्यथा
			err = चयनdev_handle_port_obj_del(dev, ptr,
							mlxsw_sp_port_dev_check,
							mlxsw_sp_port_obj_del);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_ATTR_SET:
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     mlxsw_sp_port_dev_check,
						     mlxsw_sp_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block mlxsw_sp_चयनdev_blocking_notअगरier = अणु
	.notअगरier_call = mlxsw_sp_चयनdev_blocking_event,
पूर्ण;

u8
mlxsw_sp_bridge_port_stp_state(काष्ठा mlxsw_sp_bridge_port *bridge_port)
अणु
	वापस bridge_port->stp_state;
पूर्ण

अटल पूर्णांक mlxsw_sp_fdb_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_bridge *bridge = mlxsw_sp->bridge;
	काष्ठा notअगरier_block *nb;
	पूर्णांक err;

	err = mlxsw_sp_ageing_set(mlxsw_sp, MLXSW_SP_DEFAULT_AGEING_TIME);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to set default ageing time\n");
		वापस err;
	पूर्ण

	err = रेजिस्टर_चयनdev_notअगरier(&mlxsw_sp_चयनdev_notअगरier);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to register switchdev notifier\n");
		वापस err;
	पूर्ण

	nb = &mlxsw_sp_चयनdev_blocking_notअगरier;
	err = रेजिस्टर_चयनdev_blocking_notअगरier(nb);
	अगर (err) अणु
		dev_err(mlxsw_sp->bus_info->dev, "Failed to register switchdev blocking notifier\n");
		जाओ err_रेजिस्टर_चयनdev_blocking_notअगरier;
	पूर्ण

	INIT_DELAYED_WORK(&bridge->fdb_notअगरy.dw, mlxsw_sp_fdb_notअगरy_work);
	bridge->fdb_notअगरy.पूर्णांकerval = MLXSW_SP_DEFAULT_LEARNING_INTERVAL;
	mlxsw_sp_fdb_notअगरy_work_schedule(mlxsw_sp, false);
	वापस 0;

err_रेजिस्टर_चयनdev_blocking_notअगरier:
	unरेजिस्टर_चयनdev_notअगरier(&mlxsw_sp_चयनdev_notअगरier);
	वापस err;
पूर्ण

अटल व्योम mlxsw_sp_fdb_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा notअगरier_block *nb;

	cancel_delayed_work_sync(&mlxsw_sp->bridge->fdb_notअगरy.dw);

	nb = &mlxsw_sp_चयनdev_blocking_notअगरier;
	unरेजिस्टर_चयनdev_blocking_notअगरier(nb);

	unरेजिस्टर_चयनdev_notअगरier(&mlxsw_sp_चयनdev_notअगरier);
पूर्ण

अटल व्योम mlxsw_sp1_चयनdev_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	mlxsw_sp->bridge->bridge_8021ad_ops = &mlxsw_sp1_bridge_8021ad_ops;
पूर्ण

स्थिर काष्ठा mlxsw_sp_चयनdev_ops mlxsw_sp1_चयनdev_ops = अणु
	.init	= mlxsw_sp1_चयनdev_init,
पूर्ण;

अटल व्योम mlxsw_sp2_चयनdev_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	mlxsw_sp->bridge->bridge_8021ad_ops = &mlxsw_sp2_bridge_8021ad_ops;
पूर्ण

स्थिर काष्ठा mlxsw_sp_चयनdev_ops mlxsw_sp2_चयनdev_ops = अणु
	.init	= mlxsw_sp2_चयनdev_init,
पूर्ण;

पूर्णांक mlxsw_sp_चयनdev_init(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	काष्ठा mlxsw_sp_bridge *bridge;

	bridge = kzalloc(माप(*mlxsw_sp->bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस -ENOMEM;
	mlxsw_sp->bridge = bridge;
	bridge->mlxsw_sp = mlxsw_sp;

	INIT_LIST_HEAD(&mlxsw_sp->bridge->bridges_list);

	bridge->bridge_8021q_ops = &mlxsw_sp_bridge_8021q_ops;
	bridge->bridge_8021d_ops = &mlxsw_sp_bridge_8021d_ops;

	mlxsw_sp->चयनdev_ops->init(mlxsw_sp);

	वापस mlxsw_sp_fdb_init(mlxsw_sp);
पूर्ण

व्योम mlxsw_sp_चयनdev_fini(काष्ठा mlxsw_sp *mlxsw_sp)
अणु
	mlxsw_sp_fdb_fini(mlxsw_sp);
	WARN_ON(!list_empty(&mlxsw_sp->bridge->bridges_list));
	kमुक्त(mlxsw_sp->bridge);
पूर्ण

