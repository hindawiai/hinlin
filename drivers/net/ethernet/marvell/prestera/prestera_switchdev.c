<शैली गुरु>
// SPDX-License-Identअगरier: BSD-3-Clause OR GPL-2.0
/* Copyright (c) 2019-2020 Marvell International Ltd. All rights reserved */

#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/notअगरier.h>
#समावेश <net/netevent.h>
#समावेश <net/चयनdev.h>

#समावेश "prestera.h"
#समावेश "prestera_hw.h"
#समावेश "prestera_switchdev.h"

#घोषणा PRESTERA_VID_ALL (0xffff)

#घोषणा PRESTERA_DEFAULT_AGEING_TIME_MS 300000
#घोषणा PRESTERA_MAX_AGEING_TIME_MS 1000000000
#घोषणा PRESTERA_MIN_AGEING_TIME_MS 32000

काष्ठा prestera_fdb_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा चयनdev_notअगरier_fdb_info fdb_info;
	काष्ठा net_device *dev;
	अचिन्हित दीर्घ event;
पूर्ण;

काष्ठा prestera_चयनdev अणु
	काष्ठा prestera_चयन *sw;
	काष्ठा list_head bridge_list;
	bool bridge_8021q_exists;
	काष्ठा notअगरier_block swdev_nb_blk;
	काष्ठा notअगरier_block swdev_nb;
पूर्ण;

काष्ठा prestera_bridge अणु
	काष्ठा list_head head;
	काष्ठा net_device *dev;
	काष्ठा prestera_चयनdev *swdev;
	काष्ठा list_head port_list;
	bool vlan_enabled;
	u16 bridge_id;
पूर्ण;

काष्ठा prestera_bridge_port अणु
	काष्ठा list_head head;
	काष्ठा net_device *dev;
	काष्ठा prestera_bridge *bridge;
	काष्ठा list_head vlan_list;
	refcount_t ref_count;
	अचिन्हित दीर्घ flags;
	u8 stp_state;
पूर्ण;

काष्ठा prestera_bridge_vlan अणु
	काष्ठा list_head head;
	काष्ठा list_head port_vlan_list;
	u16 vid;
पूर्ण;

काष्ठा prestera_port_vlan अणु
	काष्ठा list_head br_vlan_head;
	काष्ठा list_head port_head;
	काष्ठा prestera_port *port;
	काष्ठा prestera_bridge_port *br_port;
	u16 vid;
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *swdev_wq;

अटल व्योम prestera_bridge_port_put(काष्ठा prestera_bridge_port *br_port);

अटल पूर्णांक prestera_port_vid_stp_set(काष्ठा prestera_port *port, u16 vid,
				     u8 state);

अटल काष्ठा prestera_bridge_vlan *
prestera_bridge_vlan_create(काष्ठा prestera_bridge_port *br_port, u16 vid)
अणु
	काष्ठा prestera_bridge_vlan *br_vlan;

	br_vlan = kzalloc(माप(*br_vlan), GFP_KERNEL);
	अगर (!br_vlan)
		वापस शून्य;

	INIT_LIST_HEAD(&br_vlan->port_vlan_list);
	br_vlan->vid = vid;
	list_add(&br_vlan->head, &br_port->vlan_list);

	वापस br_vlan;
पूर्ण

अटल व्योम prestera_bridge_vlan_destroy(काष्ठा prestera_bridge_vlan *br_vlan)
अणु
	list_del(&br_vlan->head);
	WARN_ON(!list_empty(&br_vlan->port_vlan_list));
	kमुक्त(br_vlan);
पूर्ण

अटल काष्ठा prestera_bridge_vlan *
prestera_bridge_vlan_by_vid(काष्ठा prestera_bridge_port *br_port, u16 vid)
अणु
	काष्ठा prestera_bridge_vlan *br_vlan;

	list_क्रम_each_entry(br_vlan, &br_port->vlan_list, head) अणु
		अगर (br_vlan->vid == vid)
			वापस br_vlan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक prestera_bridge_vlan_port_count(काष्ठा prestera_bridge *bridge,
					   u16 vid)
अणु
	काष्ठा prestera_bridge_port *br_port;
	काष्ठा prestera_bridge_vlan *br_vlan;
	पूर्णांक count = 0;

	list_क्रम_each_entry(br_port, &bridge->port_list, head) अणु
		list_क्रम_each_entry(br_vlan, &br_port->vlan_list, head) अणु
			अगर (br_vlan->vid == vid) अणु
				count += 1;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस count;
पूर्ण

अटल व्योम prestera_bridge_vlan_put(काष्ठा prestera_bridge_vlan *br_vlan)
अणु
	अगर (list_empty(&br_vlan->port_vlan_list))
		prestera_bridge_vlan_destroy(br_vlan);
पूर्ण

अटल काष्ठा prestera_port_vlan *
prestera_port_vlan_by_vid(काष्ठा prestera_port *port, u16 vid)
अणु
	काष्ठा prestera_port_vlan *port_vlan;

	list_क्रम_each_entry(port_vlan, &port->vlans_list, port_head) अणु
		अगर (port_vlan->vid == vid)
			वापस port_vlan;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा prestera_port_vlan *
prestera_port_vlan_create(काष्ठा prestera_port *port, u16 vid, bool untagged)
अणु
	काष्ठा prestera_port_vlan *port_vlan;
	पूर्णांक err;

	port_vlan = prestera_port_vlan_by_vid(port, vid);
	अगर (port_vlan)
		वापस ERR_PTR(-EEXIST);

	err = prestera_hw_vlan_port_set(port, vid, true, untagged);
	अगर (err)
		वापस ERR_PTR(err);

	port_vlan = kzalloc(माप(*port_vlan), GFP_KERNEL);
	अगर (!port_vlan) अणु
		err = -ENOMEM;
		जाओ err_port_vlan_alloc;
	पूर्ण

	port_vlan->port = port;
	port_vlan->vid = vid;

	list_add(&port_vlan->port_head, &port->vlans_list);

	वापस port_vlan;

err_port_vlan_alloc:
	prestera_hw_vlan_port_set(port, vid, false, false);
	वापस ERR_PTR(err);
पूर्ण

अटल व्योम
prestera_port_vlan_bridge_leave(काष्ठा prestera_port_vlan *port_vlan)
अणु
	u32 fdb_flush_mode = PRESTERA_FDB_FLUSH_MODE_DYNAMIC;
	काष्ठा prestera_port *port = port_vlan->port;
	काष्ठा prestera_bridge_vlan *br_vlan;
	काष्ठा prestera_bridge_port *br_port;
	bool last_port, last_vlan;
	u16 vid = port_vlan->vid;
	पूर्णांक port_count;

	br_port = port_vlan->br_port;
	port_count = prestera_bridge_vlan_port_count(br_port->bridge, vid);
	br_vlan = prestera_bridge_vlan_by_vid(br_port, vid);

	last_vlan = list_is_singular(&br_port->vlan_list);
	last_port = port_count == 1;

	अगर (last_vlan)
		prestera_hw_fdb_flush_port(port, fdb_flush_mode);
	अन्यथा अगर (last_port)
		prestera_hw_fdb_flush_vlan(port->sw, vid, fdb_flush_mode);
	अन्यथा
		prestera_hw_fdb_flush_port_vlan(port, vid, fdb_flush_mode);

	list_del(&port_vlan->br_vlan_head);
	prestera_bridge_vlan_put(br_vlan);
	prestera_bridge_port_put(br_port);
	port_vlan->br_port = शून्य;
पूर्ण

अटल व्योम prestera_port_vlan_destroy(काष्ठा prestera_port_vlan *port_vlan)
अणु
	काष्ठा prestera_port *port = port_vlan->port;
	u16 vid = port_vlan->vid;

	अगर (port_vlan->br_port)
		prestera_port_vlan_bridge_leave(port_vlan);

	prestera_hw_vlan_port_set(port, vid, false, false);
	list_del(&port_vlan->port_head);
	kमुक्त(port_vlan);
पूर्ण

अटल काष्ठा prestera_bridge *
prestera_bridge_create(काष्ठा prestera_चयनdev *swdev, काष्ठा net_device *dev)
अणु
	bool vlan_enabled = br_vlan_enabled(dev);
	काष्ठा prestera_bridge *bridge;
	u16 bridge_id;
	पूर्णांक err;

	अगर (vlan_enabled && swdev->bridge_8021q_exists) अणु
		netdev_err(dev, "Only one VLAN-aware bridge is supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	bridge = kzalloc(माप(*bridge), GFP_KERNEL);
	अगर (!bridge)
		वापस ERR_PTR(-ENOMEM);

	अगर (vlan_enabled) अणु
		swdev->bridge_8021q_exists = true;
	पूर्ण अन्यथा अणु
		err = prestera_hw_bridge_create(swdev->sw, &bridge_id);
		अगर (err) अणु
			kमुक्त(bridge);
			वापस ERR_PTR(err);
		पूर्ण

		bridge->bridge_id = bridge_id;
	पूर्ण

	bridge->vlan_enabled = vlan_enabled;
	bridge->swdev = swdev;
	bridge->dev = dev;

	INIT_LIST_HEAD(&bridge->port_list);

	list_add(&bridge->head, &swdev->bridge_list);

	वापस bridge;
पूर्ण

अटल व्योम prestera_bridge_destroy(काष्ठा prestera_bridge *bridge)
अणु
	काष्ठा prestera_चयनdev *swdev = bridge->swdev;

	list_del(&bridge->head);

	अगर (bridge->vlan_enabled)
		swdev->bridge_8021q_exists = false;
	अन्यथा
		prestera_hw_bridge_delete(swdev->sw, bridge->bridge_id);

	WARN_ON(!list_empty(&bridge->port_list));
	kमुक्त(bridge);
पूर्ण

अटल व्योम prestera_bridge_put(काष्ठा prestera_bridge *bridge)
अणु
	अगर (list_empty(&bridge->port_list))
		prestera_bridge_destroy(bridge);
पूर्ण

अटल
काष्ठा prestera_bridge *prestera_bridge_by_dev(काष्ठा prestera_चयनdev *swdev,
					       स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा prestera_bridge *bridge;

	list_क्रम_each_entry(bridge, &swdev->bridge_list, head)
		अगर (bridge->dev == dev)
			वापस bridge;

	वापस शून्य;
पूर्ण

अटल काष्ठा prestera_bridge_port *
__prestera_bridge_port_by_dev(काष्ठा prestera_bridge *bridge,
			      काष्ठा net_device *dev)
अणु
	काष्ठा prestera_bridge_port *br_port;

	list_क्रम_each_entry(br_port, &bridge->port_list, head) अणु
		अगर (br_port->dev == dev)
			वापस br_port;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल काष्ठा prestera_bridge_port *
prestera_bridge_port_by_dev(काष्ठा prestera_चयनdev *swdev,
			    काष्ठा net_device *dev)
अणु
	काष्ठा net_device *br_dev = netdev_master_upper_dev_get(dev);
	काष्ठा prestera_bridge *bridge;

	अगर (!br_dev)
		वापस शून्य;

	bridge = prestera_bridge_by_dev(swdev, br_dev);
	अगर (!bridge)
		वापस शून्य;

	वापस __prestera_bridge_port_by_dev(bridge, dev);
पूर्ण

अटल काष्ठा prestera_bridge_port *
prestera_bridge_port_create(काष्ठा prestera_bridge *bridge,
			    काष्ठा net_device *dev)
अणु
	काष्ठा prestera_bridge_port *br_port;

	br_port = kzalloc(माप(*br_port), GFP_KERNEL);
	अगर (!br_port)
		वापस शून्य;

	br_port->flags = BR_LEARNING | BR_FLOOD | BR_LEARNING_SYNC |
				BR_MCAST_FLOOD;
	br_port->stp_state = BR_STATE_DISABLED;
	refcount_set(&br_port->ref_count, 1);
	br_port->bridge = bridge;
	br_port->dev = dev;

	INIT_LIST_HEAD(&br_port->vlan_list);
	list_add(&br_port->head, &bridge->port_list);

	वापस br_port;
पूर्ण

अटल व्योम
prestera_bridge_port_destroy(काष्ठा prestera_bridge_port *br_port)
अणु
	list_del(&br_port->head);
	WARN_ON(!list_empty(&br_port->vlan_list));
	kमुक्त(br_port);
पूर्ण

अटल व्योम prestera_bridge_port_get(काष्ठा prestera_bridge_port *br_port)
अणु
	refcount_inc(&br_port->ref_count);
पूर्ण

अटल व्योम prestera_bridge_port_put(काष्ठा prestera_bridge_port *br_port)
अणु
	काष्ठा prestera_bridge *bridge = br_port->bridge;

	अगर (refcount_dec_and_test(&br_port->ref_count)) अणु
		prestera_bridge_port_destroy(br_port);
		prestera_bridge_put(bridge);
	पूर्ण
पूर्ण

अटल काष्ठा prestera_bridge_port *
prestera_bridge_port_add(काष्ठा prestera_bridge *bridge, काष्ठा net_device *dev)
अणु
	काष्ठा prestera_bridge_port *br_port;

	br_port = __prestera_bridge_port_by_dev(bridge, dev);
	अगर (br_port) अणु
		prestera_bridge_port_get(br_port);
		वापस br_port;
	पूर्ण

	br_port = prestera_bridge_port_create(bridge, dev);
	अगर (!br_port)
		वापस ERR_PTR(-ENOMEM);

	वापस br_port;
पूर्ण

अटल पूर्णांक
prestera_bridge_1d_port_join(काष्ठा prestera_bridge_port *br_port)
अणु
	काष्ठा prestera_port *port = netdev_priv(br_port->dev);
	काष्ठा prestera_bridge *bridge = br_port->bridge;
	पूर्णांक err;

	err = prestera_hw_bridge_port_add(port, bridge->bridge_id);
	अगर (err)
		वापस err;

	err = prestera_hw_port_flood_set(port, br_port->flags & BR_FLOOD);
	अगर (err)
		जाओ err_port_flood_set;

	err = prestera_hw_port_learning_set(port, br_port->flags & BR_LEARNING);
	अगर (err)
		जाओ err_port_learning_set;

	वापस 0;

err_port_learning_set:
	prestera_hw_port_flood_set(port, false);
err_port_flood_set:
	prestera_hw_bridge_port_delete(port, bridge->bridge_id);

	वापस err;
पूर्ण

अटल पूर्णांक prestera_port_bridge_join(काष्ठा prestera_port *port,
				     काष्ठा net_device *upper)
अणु
	काष्ठा prestera_चयनdev *swdev = port->sw->swdev;
	काष्ठा prestera_bridge_port *br_port;
	काष्ठा prestera_bridge *bridge;
	पूर्णांक err;

	bridge = prestera_bridge_by_dev(swdev, upper);
	अगर (!bridge) अणु
		bridge = prestera_bridge_create(swdev, upper);
		अगर (IS_ERR(bridge))
			वापस PTR_ERR(bridge);
	पूर्ण

	br_port = prestera_bridge_port_add(bridge, port->dev);
	अगर (IS_ERR(br_port)) अणु
		err = PTR_ERR(br_port);
		जाओ err_brport_create;
	पूर्ण

	अगर (bridge->vlan_enabled)
		वापस 0;

	err = prestera_bridge_1d_port_join(br_port);
	अगर (err)
		जाओ err_port_join;

	वापस 0;

err_port_join:
	prestera_bridge_port_put(br_port);
err_brport_create:
	prestera_bridge_put(bridge);
	वापस err;
पूर्ण

अटल व्योम prestera_bridge_1q_port_leave(काष्ठा prestera_bridge_port *br_port)
अणु
	काष्ठा prestera_port *port = netdev_priv(br_port->dev);

	prestera_hw_fdb_flush_port(port, PRESTERA_FDB_FLUSH_MODE_ALL);
	prestera_port_pvid_set(port, PRESTERA_DEFAULT_VID);
पूर्ण

अटल व्योम prestera_bridge_1d_port_leave(काष्ठा prestera_bridge_port *br_port)
अणु
	काष्ठा prestera_port *port = netdev_priv(br_port->dev);

	prestera_hw_fdb_flush_port(port, PRESTERA_FDB_FLUSH_MODE_ALL);
	prestera_hw_bridge_port_delete(port, br_port->bridge->bridge_id);
पूर्ण

अटल पूर्णांक prestera_port_vid_stp_set(काष्ठा prestera_port *port, u16 vid,
				     u8 state)
अणु
	u8 hw_state = state;

	चयन (state) अणु
	हाल BR_STATE_DISABLED:
		hw_state = PRESTERA_STP_DISABLED;
		अवरोध;

	हाल BR_STATE_BLOCKING:
	हाल BR_STATE_LISTENING:
		hw_state = PRESTERA_STP_BLOCK_LISTEN;
		अवरोध;

	हाल BR_STATE_LEARNING:
		hw_state = PRESTERA_STP_LEARN;
		अवरोध;

	हाल BR_STATE_FORWARDING:
		hw_state = PRESTERA_STP_FORWARD;
		अवरोध;

	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस prestera_hw_vlan_port_stp_set(port, vid, hw_state);
पूर्ण

अटल व्योम prestera_port_bridge_leave(काष्ठा prestera_port *port,
				       काष्ठा net_device *upper)
अणु
	काष्ठा prestera_चयनdev *swdev = port->sw->swdev;
	काष्ठा prestera_bridge_port *br_port;
	काष्ठा prestera_bridge *bridge;

	bridge = prestera_bridge_by_dev(swdev, upper);
	अगर (!bridge)
		वापस;

	br_port = __prestera_bridge_port_by_dev(bridge, port->dev);
	अगर (!br_port)
		वापस;

	bridge = br_port->bridge;

	अगर (bridge->vlan_enabled)
		prestera_bridge_1q_port_leave(br_port);
	अन्यथा
		prestera_bridge_1d_port_leave(br_port);

	prestera_hw_port_learning_set(port, false);
	prestera_hw_port_flood_set(port, false);
	prestera_port_vid_stp_set(port, PRESTERA_VID_ALL, BR_STATE_FORWARDING);
	prestera_bridge_port_put(br_port);
पूर्ण

पूर्णांक prestera_bridge_port_event(काष्ठा net_device *dev, अचिन्हित दीर्घ event,
			       व्योम *ptr)
अणु
	काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
	काष्ठा netlink_ext_ack *extack;
	काष्ठा prestera_port *port;
	काष्ठा net_device *upper;
	पूर्णांक err;

	extack = netdev_notअगरier_info_to_extack(&info->info);
	port = netdev_priv(dev);
	upper = info->upper_dev;

	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER:
		अगर (!netअगर_is_bridge_master(upper)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Unknown upper device type");
			वापस -EINVAL;
		पूर्ण

		अगर (!info->linking)
			अवरोध;

		अगर (netdev_has_any_upper_dev(upper)) अणु
			NL_SET_ERR_MSG_MOD(extack, "Upper device is already enslaved");
			वापस -EINVAL;
		पूर्ण
		अवरोध;

	हाल NETDEV_CHANGEUPPER:
		अगर (!netअगर_is_bridge_master(upper))
			अवरोध;

		अगर (info->linking) अणु
			err = prestera_port_bridge_join(port, upper);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			prestera_port_bridge_leave(port, upper);
		पूर्ण
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_attr_br_flags_set(काष्ठा prestera_port *port,
					   काष्ठा net_device *dev,
					   काष्ठा चयनdev_brport_flags flags)
अणु
	काष्ठा prestera_bridge_port *br_port;
	पूर्णांक err;

	br_port = prestera_bridge_port_by_dev(port->sw->swdev, dev);
	अगर (!br_port)
		वापस 0;

	अगर (flags.mask & BR_FLOOD) अणु
		err = prestera_hw_port_flood_set(port, flags.val & BR_FLOOD);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (flags.mask & BR_LEARNING) अणु
		err = prestera_hw_port_learning_set(port,
						    flags.val & BR_LEARNING);
		अगर (err)
			वापस err;
	पूर्ण

	स_नकल(&br_port->flags, &flags.val, माप(flags.val));

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_attr_br_ageing_set(काष्ठा prestera_port *port,
					    अचिन्हित दीर्घ ageing_घड़ी_प्रकार)
अणु
	अचिन्हित दीर्घ ageing_jअगरfies = घड़ी_प्रकार_to_jअगरfies(ageing_घड़ी_प्रकार);
	u32 ageing_समय_ms = jअगरfies_to_msecs(ageing_jअगरfies);
	काष्ठा prestera_चयन *sw = port->sw;

	अगर (ageing_समय_ms < PRESTERA_MIN_AGEING_TIME_MS ||
	    ageing_समय_ms > PRESTERA_MAX_AGEING_TIME_MS)
		वापस -दुस्फल;

	वापस prestera_hw_चयन_ageing_set(sw, ageing_समय_ms);
पूर्ण

अटल पूर्णांक prestera_port_attr_br_vlan_set(काष्ठा prestera_port *port,
					  काष्ठा net_device *dev,
					  bool vlan_enabled)
अणु
	काष्ठा prestera_चयन *sw = port->sw;
	काष्ठा prestera_bridge *bridge;

	bridge = prestera_bridge_by_dev(sw->swdev, dev);
	अगर (WARN_ON(!bridge))
		वापस -EINVAL;

	अगर (bridge->vlan_enabled == vlan_enabled)
		वापस 0;

	netdev_err(bridge->dev, "VLAN filtering can't be changed for existing bridge\n");

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक prestera_port_bridge_vlan_stp_set(काष्ठा prestera_port *port,
					     काष्ठा prestera_bridge_vlan *br_vlan,
					     u8 state)
अणु
	काष्ठा prestera_port_vlan *port_vlan;

	list_क्रम_each_entry(port_vlan, &br_vlan->port_vlan_list, br_vlan_head) अणु
		अगर (port_vlan->port != port)
			जारी;

		वापस prestera_port_vid_stp_set(port, br_vlan->vid, state);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_attr_stp_state_set(काष्ठा prestera_port *port,
					    काष्ठा net_device *dev,
					    u8 state)
अणु
	काष्ठा prestera_bridge_port *br_port;
	काष्ठा prestera_bridge_vlan *br_vlan;
	पूर्णांक err;
	u16 vid;

	br_port = prestera_bridge_port_by_dev(port->sw->swdev, dev);
	अगर (!br_port)
		वापस 0;

	अगर (!br_port->bridge->vlan_enabled) अणु
		vid = br_port->bridge->bridge_id;
		err = prestera_port_vid_stp_set(port, vid, state);
		अगर (err)
			जाओ err_port_stp_set;
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(br_vlan, &br_port->vlan_list, head) अणु
			err = prestera_port_bridge_vlan_stp_set(port, br_vlan,
								state);
			अगर (err)
				जाओ err_port_vlan_stp_set;
		पूर्ण
	पूर्ण

	br_port->stp_state = state;

	वापस 0;

err_port_vlan_stp_set:
	list_क्रम_each_entry_जारी_reverse(br_vlan, &br_port->vlan_list, head)
		prestera_port_bridge_vlan_stp_set(port, br_vlan, br_port->stp_state);
	वापस err;

err_port_stp_set:
	prestera_port_vid_stp_set(port, vid, br_port->stp_state);

	वापस err;
पूर्ण

अटल पूर्णांक prestera_port_obj_attr_set(काष्ठा net_device *dev,
				      स्थिर काष्ठा चयनdev_attr *attr,
				      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	पूर्णांक err = 0;

	चयन (attr->id) अणु
	हाल SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		err = prestera_port_attr_stp_state_set(port, attr->orig_dev,
						       attr->u.stp_state);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		अगर (attr->u.brport_flags.mask &
		    ~(BR_LEARNING | BR_FLOOD | BR_MCAST_FLOOD))
			err = -EINVAL;
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		err = prestera_port_attr_br_flags_set(port, attr->orig_dev,
						      attr->u.brport_flags);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
		err = prestera_port_attr_br_ageing_set(port,
						       attr->u.ageing_समय);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		err = prestera_port_attr_br_vlan_set(port, attr->orig_dev,
						     attr->u.vlan_filtering);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम
prestera_fdb_offload_notअगरy(काष्ठा prestera_port *port,
			    काष्ठा चयनdev_notअगरier_fdb_info *info)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info send_info;

	send_info.addr = info->addr;
	send_info.vid = info->vid;
	send_info.offloaded = true;

	call_चयनdev_notअगरiers(SWITCHDEV_FDB_OFFLOADED, port->dev,
				 &send_info.info, शून्य);
पूर्ण

अटल पूर्णांक prestera_port_fdb_set(काष्ठा prestera_port *port,
				 काष्ठा चयनdev_notअगरier_fdb_info *fdb_info,
				 bool adding)
अणु
	काष्ठा prestera_चयन *sw = port->sw;
	काष्ठा prestera_bridge_port *br_port;
	काष्ठा prestera_bridge *bridge;
	पूर्णांक err;
	u16 vid;

	br_port = prestera_bridge_port_by_dev(sw->swdev, port->dev);
	अगर (!br_port)
		वापस -EINVAL;

	bridge = br_port->bridge;

	अगर (bridge->vlan_enabled)
		vid = fdb_info->vid;
	अन्यथा
		vid = bridge->bridge_id;

	अगर (adding)
		err = prestera_hw_fdb_add(port, fdb_info->addr, vid, false);
	अन्यथा
		err = prestera_hw_fdb_del(port, fdb_info->addr, vid);

	वापस err;
पूर्ण

अटल व्योम prestera_fdb_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	काष्ठा prestera_fdb_event_work *swdev_work;
	काष्ठा prestera_port *port;
	काष्ठा net_device *dev;
	पूर्णांक err;

	swdev_work = container_of(work, काष्ठा prestera_fdb_event_work, work);
	dev = swdev_work->dev;

	rtnl_lock();

	port = prestera_port_dev_lower_find(dev);
	अगर (!port)
		जाओ out_unlock;

	चयन (swdev_work->event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb_info = &swdev_work->fdb_info;
		अगर (!fdb_info->added_by_user || fdb_info->is_local)
			अवरोध;

		err = prestera_port_fdb_set(port, fdb_info, true);
		अगर (err)
			अवरोध;

		prestera_fdb_offload_notअगरy(port, fdb_info);
		अवरोध;

	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		fdb_info = &swdev_work->fdb_info;
		prestera_port_fdb_set(port, fdb_info, false);
		अवरोध;
	पूर्ण

out_unlock:
	rtnl_unlock();

	kमुक्त(swdev_work->fdb_info.addr);
	kमुक्त(swdev_work);
	dev_put(dev);
पूर्ण

अटल पूर्णांक prestera_चयनdev_event(काष्ठा notअगरier_block *unused,
				    अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	काष्ठा चयनdev_notअगरier_info *info = ptr;
	काष्ठा prestera_fdb_event_work *swdev_work;
	काष्ठा net_device *upper;
	पूर्णांक err;

	अगर (event == SWITCHDEV_PORT_ATTR_SET) अणु
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     prestera_netdev_check,
						     prestera_port_obj_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	अगर (!prestera_netdev_check(dev))
		वापस NOTIFY_DONE;

	upper = netdev_master_upper_dev_get_rcu(dev);
	अगर (!upper)
		वापस NOTIFY_DONE;

	अगर (!netअगर_is_bridge_master(upper))
		वापस NOTIFY_DONE;

	swdev_work = kzalloc(माप(*swdev_work), GFP_ATOMIC);
	अगर (!swdev_work)
		वापस NOTIFY_BAD;

	swdev_work->event = event;
	swdev_work->dev = dev;

	चयन (event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		fdb_info = container_of(info,
					काष्ठा चयनdev_notअगरier_fdb_info,
					info);

		INIT_WORK(&swdev_work->work, prestera_fdb_event_work);
		स_नकल(&swdev_work->fdb_info, ptr,
		       माप(swdev_work->fdb_info));

		swdev_work->fdb_info.addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
		अगर (!swdev_work->fdb_info.addr)
			जाओ out_bad;

		ether_addr_copy((u8 *)swdev_work->fdb_info.addr,
				fdb_info->addr);
		dev_hold(dev);
		अवरोध;

	शेष:
		kमुक्त(swdev_work);
		वापस NOTIFY_DONE;
	पूर्ण

	queue_work(swdev_wq, &swdev_work->work);
	वापस NOTIFY_DONE;

out_bad:
	kमुक्त(swdev_work);
	वापस NOTIFY_BAD;
पूर्ण

अटल पूर्णांक
prestera_port_vlan_bridge_join(काष्ठा prestera_port_vlan *port_vlan,
			       काष्ठा prestera_bridge_port *br_port)
अणु
	काष्ठा prestera_port *port = port_vlan->port;
	काष्ठा prestera_bridge_vlan *br_vlan;
	u16 vid = port_vlan->vid;
	पूर्णांक err;

	अगर (port_vlan->br_port)
		वापस 0;

	err = prestera_hw_port_flood_set(port, br_port->flags & BR_FLOOD);
	अगर (err)
		वापस err;

	err = prestera_hw_port_learning_set(port, br_port->flags & BR_LEARNING);
	अगर (err)
		जाओ err_port_learning_set;

	err = prestera_port_vid_stp_set(port, vid, br_port->stp_state);
	अगर (err)
		जाओ err_port_vid_stp_set;

	br_vlan = prestera_bridge_vlan_by_vid(br_port, vid);
	अगर (!br_vlan) अणु
		br_vlan = prestera_bridge_vlan_create(br_port, vid);
		अगर (!br_vlan) अणु
			err = -ENOMEM;
			जाओ err_bridge_vlan_get;
		पूर्ण
	पूर्ण

	list_add(&port_vlan->br_vlan_head, &br_vlan->port_vlan_list);

	prestera_bridge_port_get(br_port);
	port_vlan->br_port = br_port;

	वापस 0;

err_bridge_vlan_get:
	prestera_port_vid_stp_set(port, vid, BR_STATE_FORWARDING);
err_port_vid_stp_set:
	prestera_hw_port_learning_set(port, false);
err_port_learning_set:
	वापस err;
पूर्ण

अटल पूर्णांक
prestera_bridge_port_vlan_add(काष्ठा prestera_port *port,
			      काष्ठा prestera_bridge_port *br_port,
			      u16 vid, bool is_untagged, bool is_pvid,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा prestera_port_vlan *port_vlan;
	u16 old_pvid = port->pvid;
	u16 pvid;
	पूर्णांक err;

	अगर (is_pvid)
		pvid = vid;
	अन्यथा
		pvid = port->pvid == vid ? 0 : port->pvid;

	port_vlan = prestera_port_vlan_by_vid(port, vid);
	अगर (port_vlan && port_vlan->br_port != br_port)
		वापस -EEXIST;

	अगर (!port_vlan) अणु
		port_vlan = prestera_port_vlan_create(port, vid, is_untagged);
		अगर (IS_ERR(port_vlan))
			वापस PTR_ERR(port_vlan);
	पूर्ण अन्यथा अणु
		err = prestera_hw_vlan_port_set(port, vid, true, is_untagged);
		अगर (err)
			जाओ err_port_vlan_set;
	पूर्ण

	err = prestera_port_pvid_set(port, pvid);
	अगर (err)
		जाओ err_port_pvid_set;

	err = prestera_port_vlan_bridge_join(port_vlan, br_port);
	अगर (err)
		जाओ err_port_vlan_bridge_join;

	वापस 0;

err_port_vlan_bridge_join:
	prestera_port_pvid_set(port, old_pvid);
err_port_pvid_set:
	prestera_hw_vlan_port_set(port, vid, false, false);
err_port_vlan_set:
	prestera_port_vlan_destroy(port_vlan);

	वापस err;
पूर्ण

अटल व्योम
prestera_bridge_port_vlan_del(काष्ठा prestera_port *port,
			      काष्ठा prestera_bridge_port *br_port, u16 vid)
अणु
	u16 pvid = port->pvid == vid ? 0 : port->pvid;
	काष्ठा prestera_port_vlan *port_vlan;

	port_vlan = prestera_port_vlan_by_vid(port, vid);
	अगर (WARN_ON(!port_vlan))
		वापस;

	prestera_port_vlan_bridge_leave(port_vlan);
	prestera_port_pvid_set(port, pvid);
	prestera_port_vlan_destroy(port_vlan);
पूर्ण

अटल पूर्णांक prestera_port_vlans_add(काष्ठा prestera_port *port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
				   काष्ठा netlink_ext_ack *extack)
अणु
	bool flag_untagged = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	bool flag_pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;
	काष्ठा net_device *dev = vlan->obj.orig_dev;
	काष्ठा prestera_bridge_port *br_port;
	काष्ठा prestera_चयन *sw = port->sw;
	काष्ठा prestera_bridge *bridge;

	अगर (netअगर_is_bridge_master(dev))
		वापस 0;

	br_port = prestera_bridge_port_by_dev(sw->swdev, dev);
	अगर (WARN_ON(!br_port))
		वापस -EINVAL;

	bridge = br_port->bridge;
	अगर (!bridge->vlan_enabled)
		वापस 0;

	वापस prestera_bridge_port_vlan_add(port, br_port,
					     vlan->vid, flag_untagged,
					     flag_pvid, extack);
पूर्ण

अटल पूर्णांक prestera_port_obj_add(काष्ठा net_device *dev,
				 स्थिर काष्ठा चयनdev_obj *obj,
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);
	स्थिर काष्ठा चयनdev_obj_port_vlan *vlan;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);
		वापस prestera_port_vlans_add(port, vlan, extack);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक prestera_port_vlans_del(काष्ठा prestera_port *port,
				   स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा net_device *dev = vlan->obj.orig_dev;
	काष्ठा prestera_bridge_port *br_port;
	काष्ठा prestera_चयन *sw = port->sw;

	अगर (netअगर_is_bridge_master(dev))
		वापस -EOPNOTSUPP;

	br_port = prestera_bridge_port_by_dev(sw->swdev, dev);
	अगर (WARN_ON(!br_port))
		वापस -EINVAL;

	अगर (!br_port->bridge->vlan_enabled)
		वापस 0;

	prestera_bridge_port_vlan_del(port, br_port, vlan->vid);

	वापस 0;
पूर्ण

अटल पूर्णांक prestera_port_obj_del(काष्ठा net_device *dev,
				 स्थिर काष्ठा चयनdev_obj *obj)
अणु
	काष्ठा prestera_port *port = netdev_priv(dev);

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		वापस prestera_port_vlans_del(port, SWITCHDEV_OBJ_PORT_VLAN(obj));
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक prestera_चयनdev_blk_event(काष्ठा notअगरier_block *unused,
					अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	पूर्णांक err;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
		err = चयनdev_handle_port_obj_add(dev, ptr,
						    prestera_netdev_check,
						    prestera_port_obj_add);
		अवरोध;
	हाल SWITCHDEV_PORT_OBJ_DEL:
		err = चयनdev_handle_port_obj_del(dev, ptr,
						    prestera_netdev_check,
						    prestera_port_obj_del);
		अवरोध;
	हाल SWITCHDEV_PORT_ATTR_SET:
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     prestera_netdev_check,
						     prestera_port_obj_attr_set);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
	पूर्ण

	वापस notअगरier_from_त्रुटि_सं(err);
पूर्ण

अटल व्योम prestera_fdb_event(काष्ठा prestera_चयन *sw,
			       काष्ठा prestera_event *evt, व्योम *arg)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info;
	काष्ठा prestera_port *port;

	port = prestera_find_port(sw, evt->fdb_evt.port_id);
	अगर (!port)
		वापस;

	info.addr = evt->fdb_evt.data.mac;
	info.vid = evt->fdb_evt.vid;
	info.offloaded = true;

	rtnl_lock();

	चयन (evt->id) अणु
	हाल PRESTERA_FDB_EVENT_LEARNED:
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_ADD_TO_BRIDGE,
					 port->dev, &info.info, शून्य);
		अवरोध;
	हाल PRESTERA_FDB_EVENT_AGED:
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_DEL_TO_BRIDGE,
					 port->dev, &info.info, शून्य);
		अवरोध;
	पूर्ण

	rtnl_unlock();
पूर्ण

अटल पूर्णांक prestera_fdb_init(काष्ठा prestera_चयन *sw)
अणु
	पूर्णांक err;

	err = prestera_hw_event_handler_रेजिस्टर(sw, PRESTERA_EVENT_TYPE_FDB,
						 prestera_fdb_event, शून्य);
	अगर (err)
		वापस err;

	err = prestera_hw_चयन_ageing_set(sw, PRESTERA_DEFAULT_AGEING_TIME_MS);
	अगर (err)
		जाओ err_ageing_set;

	वापस 0;

err_ageing_set:
	prestera_hw_event_handler_unरेजिस्टर(sw, PRESTERA_EVENT_TYPE_FDB,
					     prestera_fdb_event);
	वापस err;
पूर्ण

अटल व्योम prestera_fdb_fini(काष्ठा prestera_चयन *sw)
अणु
	prestera_hw_event_handler_unरेजिस्टर(sw, PRESTERA_EVENT_TYPE_FDB,
					     prestera_fdb_event);
पूर्ण

अटल पूर्णांक prestera_चयनdev_handler_init(काष्ठा prestera_चयनdev *swdev)
अणु
	पूर्णांक err;

	swdev->swdev_nb.notअगरier_call = prestera_चयनdev_event;
	err = रेजिस्टर_चयनdev_notअगरier(&swdev->swdev_nb);
	अगर (err)
		जाओ err_रेजिस्टर_swdev_notअगरier;

	swdev->swdev_nb_blk.notअगरier_call = prestera_चयनdev_blk_event;
	err = रेजिस्टर_चयनdev_blocking_notअगरier(&swdev->swdev_nb_blk);
	अगर (err)
		जाओ err_रेजिस्टर_blk_swdev_notअगरier;

	वापस 0;

err_रेजिस्टर_blk_swdev_notअगरier:
	unरेजिस्टर_चयनdev_notअगरier(&swdev->swdev_nb);
err_रेजिस्टर_swdev_notअगरier:
	destroy_workqueue(swdev_wq);
	वापस err;
पूर्ण

अटल व्योम prestera_चयनdev_handler_fini(काष्ठा prestera_चयनdev *swdev)
अणु
	unरेजिस्टर_चयनdev_blocking_notअगरier(&swdev->swdev_nb_blk);
	unरेजिस्टर_चयनdev_notअगरier(&swdev->swdev_nb);
पूर्ण

पूर्णांक prestera_चयनdev_init(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा prestera_चयनdev *swdev;
	पूर्णांक err;

	swdev = kzalloc(माप(*swdev), GFP_KERNEL);
	अगर (!swdev)
		वापस -ENOMEM;

	sw->swdev = swdev;
	swdev->sw = sw;

	INIT_LIST_HEAD(&swdev->bridge_list);

	swdev_wq = alloc_ordered_workqueue("%s_ordered", 0, "prestera_br");
	अगर (!swdev_wq) अणु
		err = -ENOMEM;
		जाओ err_alloc_wq;
	पूर्ण

	err = prestera_चयनdev_handler_init(swdev);
	अगर (err)
		जाओ err_swdev_init;

	err = prestera_fdb_init(sw);
	अगर (err)
		जाओ err_fdb_init;

	वापस 0;

err_fdb_init:
err_swdev_init:
	destroy_workqueue(swdev_wq);
err_alloc_wq:
	kमुक्त(swdev);

	वापस err;
पूर्ण

व्योम prestera_चयनdev_fini(काष्ठा prestera_चयन *sw)
अणु
	काष्ठा prestera_चयनdev *swdev = sw->swdev;

	prestera_fdb_fini(sw);
	prestera_चयनdev_handler_fini(swdev);
	destroy_workqueue(swdev_wq);
	kमुक्त(swdev);
पूर्ण
