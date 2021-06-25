<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Texas Instruments K3 AM65 Ethernet Switchdev Driver
 *
 * Copyright (C) 2020 Texas Instruments Incorporated - https://www.ti.com/
 *
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <net/चयनdev.h>

#समावेश "am65-cpsw-nuss.h"
#समावेश "am65-cpsw-switchdev.h"
#समावेश "cpsw_ale.h"

काष्ठा am65_cpsw_चयनdev_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा चयनdev_notअगरier_fdb_info fdb_info;
	काष्ठा am65_cpsw_port *port;
	अचिन्हित दीर्घ event;
पूर्ण;

अटल पूर्णांक am65_cpsw_port_stp_state_set(काष्ठा am65_cpsw_port *port, u8 state)
अणु
	काष्ठा am65_cpsw_common *cpsw = port->common;
	u8 cpsw_state;
	पूर्णांक ret = 0;

	चयन (state) अणु
	हाल BR_STATE_FORWARDING:
		cpsw_state = ALE_PORT_STATE_FORWARD;
		अवरोध;
	हाल BR_STATE_LEARNING:
		cpsw_state = ALE_PORT_STATE_LEARN;
		अवरोध;
	हाल BR_STATE_DISABLED:
		cpsw_state = ALE_PORT_STATE_DISABLE;
		अवरोध;
	हाल BR_STATE_LISTENING:
	हाल BR_STATE_BLOCKING:
		cpsw_state = ALE_PORT_STATE_BLOCK;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = cpsw_ale_control_set(cpsw->ale, port->port_id,
				   ALE_PORT_STATE, cpsw_state);
	netdev_dbg(port->ndev, "ale state: %u\n", cpsw_state);

	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_port_attr_br_flags_set(काष्ठा am65_cpsw_port *port,
					    काष्ठा net_device *orig_dev,
					    काष्ठा चयनdev_brport_flags flags)
अणु
	काष्ठा am65_cpsw_common *cpsw = port->common;

	अगर (flags.mask & BR_MCAST_FLOOD) अणु
		bool unreg_mcast_add = false;

		अगर (flags.val & BR_MCAST_FLOOD)
			unreg_mcast_add = true;

		netdev_dbg(port->ndev, "BR_MCAST_FLOOD: %d port %u\n",
			   unreg_mcast_add, port->port_id);

		cpsw_ale_set_unreg_mcast(cpsw->ale, BIT(port->port_id),
					 unreg_mcast_add);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpsw_port_attr_br_flags_pre_set(काष्ठा net_device *netdev,
						काष्ठा चयनdev_brport_flags flags)
अणु
	अगर (flags.mask & ~(BR_LEARNING | BR_MCAST_FLOOD))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpsw_port_attr_set(काष्ठा net_device *ndev,
				   स्थिर काष्ठा चयनdev_attr *attr,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	पूर्णांक ret;

	netdev_dbg(ndev, "attr: id %u port: %u\n", attr->id, port->port_id);

	चयन (attr->id) अणु
	हाल SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		ret = am65_cpsw_port_attr_br_flags_pre_set(ndev,
							   attr->u.brport_flags);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		ret = am65_cpsw_port_stp_state_set(port, attr->u.stp_state);
		netdev_dbg(ndev, "stp state: %u\n", attr->u.stp_state);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		ret = am65_cpsw_port_attr_br_flags_set(port, attr->orig_dev,
						       attr->u.brport_flags);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u16 am65_cpsw_get_pvid(काष्ठा am65_cpsw_port *port)
अणु
	काष्ठा am65_cpsw_common *cpsw = port->common;
	काष्ठा am65_cpsw_host *host_p = am65_common_get_host(cpsw);
	u32 pvid;

	अगर (port->port_id)
		pvid = पढ़ोl(port->port_base + AM65_CPSW_PORT_VLAN_REG_OFFSET);
	अन्यथा
		pvid = पढ़ोl(host_p->port_base + AM65_CPSW_PORT_VLAN_REG_OFFSET);

	pvid = pvid & 0xfff;

	वापस pvid;
पूर्ण

अटल व्योम am65_cpsw_set_pvid(काष्ठा am65_cpsw_port *port, u16 vid, bool cfi, u32 cos)
अणु
	काष्ठा am65_cpsw_common *cpsw = port->common;
	काष्ठा am65_cpsw_host *host_p = am65_common_get_host(cpsw);
	u32 pvid;

	pvid = vid;
	pvid |= cfi ? BIT(12) : 0;
	pvid |= (cos & 0x7) << 13;

	अगर (port->port_id)
		ग_लिखोl(pvid, port->port_base + AM65_CPSW_PORT_VLAN_REG_OFFSET);
	अन्यथा
		ग_लिखोl(pvid, host_p->port_base + AM65_CPSW_PORT_VLAN_REG_OFFSET);
पूर्ण

अटल पूर्णांक am65_cpsw_port_vlan_add(काष्ठा am65_cpsw_port *port, bool untag, bool pvid,
				   u16 vid, काष्ठा net_device *orig_dev)
अणु
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	काष्ठा am65_cpsw_common *cpsw = port->common;
	पूर्णांक unreg_mcast_mask = 0;
	पूर्णांक reg_mcast_mask = 0;
	पूर्णांक untag_mask = 0;
	पूर्णांक port_mask;
	पूर्णांक ret = 0;
	u32 flags;

	अगर (cpu_port) अणु
		port_mask = BIT(HOST_PORT_NUM);
		flags = orig_dev->flags;
		unreg_mcast_mask = port_mask;
	पूर्ण अन्यथा अणु
		port_mask = BIT(port->port_id);
		flags = port->ndev->flags;
	पूर्ण

	अगर (flags & IFF_MULTICAST)
		reg_mcast_mask = port_mask;

	अगर (untag)
		untag_mask = port_mask;

	ret = cpsw_ale_vlan_add_modअगरy(cpsw->ale, vid, port_mask, untag_mask,
				       reg_mcast_mask, unreg_mcast_mask);
	अगर (ret) अणु
		netdev_err(port->ndev, "Unable to add vlan\n");
		वापस ret;
	पूर्ण

	अगर (cpu_port)
		cpsw_ale_add_ucast(cpsw->ale, port->slave.mac_addr,
				   HOST_PORT_NUM, ALE_VLAN | ALE_SECURE, vid);
	अगर (!pvid)
		वापस ret;

	am65_cpsw_set_pvid(port, vid, 0, 0);

	netdev_dbg(port->ndev, "VID add: %s: vid:%u ports:%X\n",
		   port->ndev->name, vid, port_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_port_vlan_del(काष्ठा am65_cpsw_port *port, u16 vid,
				   काष्ठा net_device *orig_dev)
अणु
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	काष्ठा am65_cpsw_common *cpsw = port->common;
	पूर्णांक port_mask;
	पूर्णांक ret = 0;

	अगर (cpu_port)
		port_mask = BIT(HOST_PORT_NUM);
	अन्यथा
		port_mask = BIT(port->port_id);

	ret = cpsw_ale_del_vlan(cpsw->ale, vid, port_mask);
	अगर (ret != 0)
		वापस ret;

	/* We करोn't care क्रम the वापस value here, error is वापसed only अगर
	 * the unicast entry is not present
	 */
	अगर (cpu_port)
		cpsw_ale_del_ucast(cpsw->ale, port->slave.mac_addr,
				   HOST_PORT_NUM, ALE_VLAN, vid);

	अगर (vid == am65_cpsw_get_pvid(port))
		am65_cpsw_set_pvid(port, 0, 0, 0);

	/* We करोn't care क्रम the वापस value here, error is वापसed only अगर
	 * the multicast entry is not present
	 */
	cpsw_ale_del_mcast(cpsw->ale, port->ndev->broadcast, port_mask,
			   ALE_VLAN, vid);
	netdev_dbg(port->ndev, "VID del: %s: vid:%u ports:%X\n",
		   port->ndev->name, vid, port_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक am65_cpsw_port_vlans_add(काष्ठा am65_cpsw_port *port,
				    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	bool untag = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	काष्ठा net_device *orig_dev = vlan->obj.orig_dev;
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;

	netdev_dbg(port->ndev, "VID add: %s: vid:%u flags:%X\n",
		   port->ndev->name, vlan->vid, vlan->flags);

	अगर (cpu_port && !(vlan->flags & BRIDGE_VLAN_INFO_BRENTRY))
		वापस 0;

	वापस am65_cpsw_port_vlan_add(port, untag, pvid, vlan->vid, orig_dev);
पूर्ण

अटल पूर्णांक am65_cpsw_port_vlans_del(काष्ठा am65_cpsw_port *port,
				    स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)

अणु
	वापस am65_cpsw_port_vlan_del(port, vlan->vid, vlan->obj.orig_dev);
पूर्ण

अटल पूर्णांक am65_cpsw_port_mdb_add(काष्ठा am65_cpsw_port *port,
				  काष्ठा चयनdev_obj_port_mdb *mdb)

अणु
	काष्ठा net_device *orig_dev = mdb->obj.orig_dev;
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	काष्ठा am65_cpsw_common *cpsw = port->common;
	पूर्णांक port_mask;
	पूर्णांक err;

	अगर (cpu_port)
		port_mask = BIT(HOST_PORT_NUM);
	अन्यथा
		port_mask = BIT(port->port_id);

	err = cpsw_ale_add_mcast(cpsw->ale, mdb->addr, port_mask,
				 ALE_VLAN, mdb->vid, 0);
	netdev_dbg(port->ndev, "MDB add: %s: vid %u:%pM  ports: %X\n",
		   port->ndev->name, mdb->vid, mdb->addr, port_mask);

	वापस err;
पूर्ण

अटल पूर्णांक am65_cpsw_port_mdb_del(काष्ठा am65_cpsw_port *port,
				  काष्ठा चयनdev_obj_port_mdb *mdb)

अणु
	काष्ठा net_device *orig_dev = mdb->obj.orig_dev;
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	काष्ठा am65_cpsw_common *cpsw = port->common;
	पूर्णांक del_mask;

	अगर (cpu_port)
		del_mask = BIT(HOST_PORT_NUM);
	अन्यथा
		del_mask = BIT(port->port_id);

	/* Ignore error as error code is वापसed only when entry is alपढ़ोy हटाओd */
	cpsw_ale_del_mcast(cpsw->ale, mdb->addr, del_mask,
			   ALE_VLAN, mdb->vid);
	netdev_dbg(port->ndev, "MDB del: %s: vid %u:%pM  ports: %X\n",
		   port->ndev->name, mdb->vid, mdb->addr, del_mask);

	वापस 0;
पूर्ण

अटल पूर्णांक am65_cpsw_port_obj_add(काष्ठा net_device *ndev,
				  स्थिर काष्ठा चयनdev_obj *obj,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_obj_port_vlan *vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);
	काष्ठा चयनdev_obj_port_mdb *mdb = SWITCHDEV_OBJ_PORT_MDB(obj);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	पूर्णांक err = 0;

	netdev_dbg(ndev, "obj_add: id %u port: %u\n", obj->id, port->port_id);

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = am65_cpsw_port_vlans_add(port, vlan);
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
	हाल SWITCHDEV_OBJ_ID_HOST_MDB:
		err = am65_cpsw_port_mdb_add(port, mdb);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक am65_cpsw_port_obj_del(काष्ठा net_device *ndev,
				  स्थिर काष्ठा चयनdev_obj *obj)
अणु
	काष्ठा चयनdev_obj_port_vlan *vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);
	काष्ठा चयनdev_obj_port_mdb *mdb = SWITCHDEV_OBJ_PORT_MDB(obj);
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	पूर्णांक err = 0;

	netdev_dbg(ndev, "obj_del: id %u port: %u\n", obj->id, port->port_id);

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = am65_cpsw_port_vlans_del(port, vlan);
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
	हाल SWITCHDEV_OBJ_ID_HOST_MDB:
		err = am65_cpsw_port_mdb_del(port, mdb);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम am65_cpsw_fdb_offload_notअगरy(काष्ठा net_device *ndev,
					 काष्ठा चयनdev_notअगरier_fdb_info *rcv)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info;

	info.addr = rcv->addr;
	info.vid = rcv->vid;
	info.offloaded = true;
	call_चयनdev_notअगरiers(SWITCHDEV_FDB_OFFLOADED,
				 ndev, &info.info, शून्य);
पूर्ण

अटल व्योम am65_cpsw_चयनdev_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा am65_cpsw_चयनdev_event_work *चयनdev_work =
		container_of(work, काष्ठा am65_cpsw_चयनdev_event_work, work);
	काष्ठा am65_cpsw_port *port = चयनdev_work->port;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb;
	काष्ठा am65_cpsw_common *cpsw = port->common;
	पूर्णांक port_id = port->port_id;

	rtnl_lock();
	चयन (चयनdev_work->event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb = &चयनdev_work->fdb_info;

		netdev_dbg(port->ndev, "cpsw_fdb_add: MACID = %pM vid = %u flags = %u %u -- port %d\n",
			   fdb->addr, fdb->vid, fdb->added_by_user,
			   fdb->offloaded, port_id);

		अगर (!fdb->added_by_user || fdb->is_local)
			अवरोध;
		अगर (स_भेद(port->slave.mac_addr, (u8 *)fdb->addr, ETH_ALEN) == 0)
			port_id = HOST_PORT_NUM;

		cpsw_ale_add_ucast(cpsw->ale, (u8 *)fdb->addr, port_id,
				   fdb->vid ? ALE_VLAN : 0, fdb->vid);
		am65_cpsw_fdb_offload_notअगरy(port->ndev, fdb);
		अवरोध;
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		fdb = &चयनdev_work->fdb_info;

		netdev_dbg(port->ndev, "cpsw_fdb_del: MACID = %pM vid = %u flags = %u %u -- port %d\n",
			   fdb->addr, fdb->vid, fdb->added_by_user,
			   fdb->offloaded, port_id);

		अगर (!fdb->added_by_user || fdb->is_local)
			अवरोध;
		अगर (स_भेद(port->slave.mac_addr, (u8 *)fdb->addr, ETH_ALEN) == 0)
			port_id = HOST_PORT_NUM;

		cpsw_ale_del_ucast(cpsw->ale, (u8 *)fdb->addr, port_id,
				   fdb->vid ? ALE_VLAN : 0, fdb->vid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rtnl_unlock();

	kमुक्त(चयनdev_work->fdb_info.addr);
	kमुक्त(चयनdev_work);
	dev_put(port->ndev);
पूर्ण

/* called under rcu_पढ़ो_lock() */
अटल पूर्णांक am65_cpsw_चयनdev_event(काष्ठा notअगरier_block *unused,
				     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = चयनdev_notअगरier_info_to_dev(ptr);
	काष्ठा am65_cpsw_चयनdev_event_work *चयनdev_work;
	काष्ठा am65_cpsw_port *port = am65_ndev_to_port(ndev);
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info = ptr;
	पूर्णांक err;

	अगर (event == SWITCHDEV_PORT_ATTR_SET) अणु
		err = चयनdev_handle_port_attr_set(ndev, ptr,
						     am65_cpsw_port_dev_check,
						     am65_cpsw_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	अगर (!am65_cpsw_port_dev_check(ndev))
		वापस NOTIFY_DONE;

	चयनdev_work = kzalloc(माप(*चयनdev_work), GFP_ATOMIC);
	अगर (WARN_ON(!चयनdev_work))
		वापस NOTIFY_BAD;

	INIT_WORK(&चयनdev_work->work, am65_cpsw_चयनdev_event_work);
	चयनdev_work->port = port;
	चयनdev_work->event = event;

	चयन (event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		स_नकल(&चयनdev_work->fdb_info, ptr,
		       माप(चयनdev_work->fdb_info));
		चयनdev_work->fdb_info.addr = kzalloc(ETH_ALEN, GFP_ATOMIC);
		अगर (!चयनdev_work->fdb_info.addr)
			जाओ err_addr_alloc;
		ether_addr_copy((u8 *)चयनdev_work->fdb_info.addr,
				fdb_info->addr);
		dev_hold(ndev);
		अवरोध;
	शेष:
		kमुक्त(चयनdev_work);
		वापस NOTIFY_DONE;
	पूर्ण

	queue_work(प्रणाली_दीर्घ_wq, &चयनdev_work->work);

	वापस NOTIFY_DONE;

err_addr_alloc:
	kमुक्त(चयनdev_work);
	वापस NOTIFY_BAD;
पूर्ण

अटल काष्ठा notअगरier_block cpsw_चयनdev_notअगरier = अणु
	.notअगरier_call = am65_cpsw_चयनdev_event,
पूर्ण;

अटल पूर्णांक am65_cpsw_चयनdev_blocking_event(काष्ठा notअगरier_block *unused,
					      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	पूर्णांक err;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
		err = चयनdev_handle_port_obj_add(dev, ptr,
						    am65_cpsw_port_dev_check,
						    am65_cpsw_port_obj_add);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_OBJ_DEL:
		err = चयनdev_handle_port_obj_del(dev, ptr,
						    am65_cpsw_port_dev_check,
						    am65_cpsw_port_obj_del);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_ATTR_SET:
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     am65_cpsw_port_dev_check,
						     am65_cpsw_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block cpsw_चयनdev_bl_notअगरier = अणु
	.notअगरier_call = am65_cpsw_चयनdev_blocking_event,
पूर्ण;

पूर्णांक am65_cpsw_चयनdev_रेजिस्टर_notअगरiers(काष्ठा am65_cpsw_common *cpsw)
अणु
	पूर्णांक ret = 0;

	ret = रेजिस्टर_चयनdev_notअगरier(&cpsw_चयनdev_notअगरier);
	अगर (ret) अणु
		dev_err(cpsw->dev, "register switchdev notifier fail ret:%d\n",
			ret);
		वापस ret;
	पूर्ण

	ret = रेजिस्टर_चयनdev_blocking_notअगरier(&cpsw_चयनdev_bl_notअगरier);
	अगर (ret) अणु
		dev_err(cpsw->dev, "register switchdev blocking notifier ret:%d\n",
			ret);
		unरेजिस्टर_चयनdev_notअगरier(&cpsw_चयनdev_notअगरier);
	पूर्ण

	वापस ret;
पूर्ण

व्योम am65_cpsw_चयनdev_unरेजिस्टर_notअगरiers(काष्ठा am65_cpsw_common *cpsw)
अणु
	unरेजिस्टर_चयनdev_blocking_notअगरier(&cpsw_चयनdev_bl_notअगरier);
	unरेजिस्टर_चयनdev_notअगरier(&cpsw_चयनdev_notअगरier);
पूर्ण
