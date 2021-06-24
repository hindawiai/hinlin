<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Texas Instruments चयनdev Driver
 *
 * Copyright (C) 2019 Texas Instruments
 *
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/workqueue.h>
#समावेश <net/चयनdev.h>

#समावेश "cpsw.h"
#समावेश "cpsw_ale.h"
#समावेश "cpsw_priv.h"
#समावेश "cpsw_switchdev.h"

काष्ठा cpsw_चयनdev_event_work अणु
	काष्ठा work_काष्ठा work;
	काष्ठा चयनdev_notअगरier_fdb_info fdb_info;
	काष्ठा cpsw_priv *priv;
	अचिन्हित दीर्घ event;
पूर्ण;

अटल पूर्णांक cpsw_port_stp_state_set(काष्ठा cpsw_priv *priv, u8 state)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
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

	ret = cpsw_ale_control_set(cpsw->ale, priv->emac_port,
				   ALE_PORT_STATE, cpsw_state);
	dev_dbg(priv->dev, "ale state: %u\n", cpsw_state);

	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_port_attr_br_flags_set(काष्ठा cpsw_priv *priv,
				       काष्ठा net_device *orig_dev,
				       काष्ठा चयनdev_brport_flags flags)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;

	अगर (flags.mask & BR_MCAST_FLOOD) अणु
		bool unreg_mcast_add = false;

		अगर (flags.val & BR_MCAST_FLOOD)
			unreg_mcast_add = true;

		dev_dbg(priv->dev, "BR_MCAST_FLOOD: %d port %u\n",
			unreg_mcast_add, priv->emac_port);

		cpsw_ale_set_unreg_mcast(cpsw->ale, BIT(priv->emac_port),
					 unreg_mcast_add);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_port_attr_br_flags_pre_set(काष्ठा net_device *netdev,
					   काष्ठा चयनdev_brport_flags flags)
अणु
	अगर (flags.mask & ~(BR_LEARNING | BR_MCAST_FLOOD))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक cpsw_port_attr_set(काष्ठा net_device *ndev,
			      स्थिर काष्ठा चयनdev_attr *attr,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	पूर्णांक ret;

	dev_dbg(priv->dev, "attr: id %u port: %u\n", attr->id, priv->emac_port);

	चयन (attr->id) अणु
	हाल SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		ret = cpsw_port_attr_br_flags_pre_set(ndev,
						      attr->u.brport_flags);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		ret = cpsw_port_stp_state_set(priv, attr->u.stp_state);
		dev_dbg(priv->dev, "stp state: %u\n", attr->u.stp_state);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		ret = cpsw_port_attr_br_flags_set(priv, attr->orig_dev,
						  attr->u.brport_flags);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल u16 cpsw_get_pvid(काष्ठा cpsw_priv *priv)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	u32 __iomem *port_vlan_reg;
	u32 pvid;

	अगर (priv->emac_port) अणु
		पूर्णांक reg = CPSW2_PORT_VLAN;

		अगर (cpsw->version == CPSW_VERSION_1)
			reg = CPSW1_PORT_VLAN;
		pvid = slave_पढ़ो(cpsw->slaves + (priv->emac_port - 1), reg);
	पूर्ण अन्यथा अणु
		port_vlan_reg = &cpsw->host_port_regs->port_vlan;
		pvid = पढ़ोl(port_vlan_reg);
	पूर्ण

	pvid = pvid & 0xfff;

	वापस pvid;
पूर्ण

अटल व्योम cpsw_set_pvid(काष्ठा cpsw_priv *priv, u16 vid, bool cfi, u32 cos)
अणु
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	व्योम __iomem *port_vlan_reg;
	u32 pvid;

	pvid = vid;
	pvid |= cfi ? BIT(12) : 0;
	pvid |= (cos & 0x7) << 13;

	अगर (priv->emac_port) अणु
		पूर्णांक reg = CPSW2_PORT_VLAN;

		अगर (cpsw->version == CPSW_VERSION_1)
			reg = CPSW1_PORT_VLAN;
		/* no barrier */
		slave_ग_लिखो(cpsw->slaves + (priv->emac_port - 1), pvid, reg);
	पूर्ण अन्यथा अणु
		/* CPU port */
		port_vlan_reg = &cpsw->host_port_regs->port_vlan;
		ग_लिखोl(pvid, port_vlan_reg);
	पूर्ण
पूर्ण

अटल पूर्णांक cpsw_port_vlan_add(काष्ठा cpsw_priv *priv, bool untag, bool pvid,
			      u16 vid, काष्ठा net_device *orig_dev)
अणु
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
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
		port_mask = BIT(priv->emac_port);
		flags = priv->ndev->flags;
	पूर्ण

	अगर (flags & IFF_MULTICAST)
		reg_mcast_mask = port_mask;

	अगर (untag)
		untag_mask = port_mask;

	ret = cpsw_ale_vlan_add_modअगरy(cpsw->ale, vid, port_mask, untag_mask,
				       reg_mcast_mask, unreg_mcast_mask);
	अगर (ret) अणु
		dev_err(priv->dev, "Unable to add vlan\n");
		वापस ret;
	पूर्ण

	अगर (cpu_port)
		cpsw_ale_add_ucast(cpsw->ale, priv->mac_addr,
				   HOST_PORT_NUM, ALE_VLAN, vid);
	अगर (!pvid)
		वापस ret;

	cpsw_set_pvid(priv, vid, 0, 0);

	dev_dbg(priv->dev, "VID add: %s: vid:%u ports:%X\n",
		priv->ndev->name, vid, port_mask);
	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_port_vlan_del(काष्ठा cpsw_priv *priv, u16 vid,
			      काष्ठा net_device *orig_dev)
अणु
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक port_mask;
	पूर्णांक ret = 0;

	अगर (cpu_port)
		port_mask = BIT(HOST_PORT_NUM);
	अन्यथा
		port_mask = BIT(priv->emac_port);

	ret = cpsw_ale_vlan_del_modअगरy(cpsw->ale, vid, port_mask);
	अगर (ret != 0)
		वापस ret;

	/* We करोn't care क्रम the वापस value here, error is वापसed only अगर
	 * the unicast entry is not present
	 */
	अगर (cpu_port)
		cpsw_ale_del_ucast(cpsw->ale, priv->mac_addr,
				   HOST_PORT_NUM, ALE_VLAN, vid);

	अगर (vid == cpsw_get_pvid(priv))
		cpsw_set_pvid(priv, 0, 0, 0);

	/* We करोn't care क्रम the वापस value here, error is वापसed only अगर
	 * the multicast entry is not present
	 */
	cpsw_ale_del_mcast(cpsw->ale, priv->ndev->broadcast,
			   port_mask, ALE_VLAN, vid);
	dev_dbg(priv->dev, "VID del: %s: vid:%u ports:%X\n",
		priv->ndev->name, vid, port_mask);

	वापस ret;
पूर्ण

अटल पूर्णांक cpsw_port_vlans_add(काष्ठा cpsw_priv *priv,
			       स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	bool untag = vlan->flags & BRIDGE_VLAN_INFO_UNTAGGED;
	काष्ठा net_device *orig_dev = vlan->obj.orig_dev;
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	bool pvid = vlan->flags & BRIDGE_VLAN_INFO_PVID;

	dev_dbg(priv->dev, "VID add: %s: vid:%u flags:%X\n",
		priv->ndev->name, vlan->vid, vlan->flags);

	अगर (cpu_port && !(vlan->flags & BRIDGE_VLAN_INFO_BRENTRY))
		वापस 0;

	वापस cpsw_port_vlan_add(priv, untag, pvid, vlan->vid, orig_dev);
पूर्ण

अटल पूर्णांक cpsw_port_mdb_add(काष्ठा cpsw_priv *priv,
			     काष्ठा चयनdev_obj_port_mdb *mdb)

अणु
	काष्ठा net_device *orig_dev = mdb->obj.orig_dev;
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक port_mask;
	पूर्णांक err;

	अगर (cpu_port)
		port_mask = BIT(HOST_PORT_NUM);
	अन्यथा
		port_mask = BIT(priv->emac_port);

	err = cpsw_ale_add_mcast(cpsw->ale, mdb->addr, port_mask,
				 ALE_VLAN, mdb->vid, 0);
	dev_dbg(priv->dev, "MDB add: %s: vid %u:%pM  ports: %X\n",
		priv->ndev->name, mdb->vid, mdb->addr, port_mask);

	वापस err;
पूर्ण

अटल पूर्णांक cpsw_port_mdb_del(काष्ठा cpsw_priv *priv,
			     काष्ठा चयनdev_obj_port_mdb *mdb)

अणु
	काष्ठा net_device *orig_dev = mdb->obj.orig_dev;
	bool cpu_port = netअगर_is_bridge_master(orig_dev);
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक del_mask;
	पूर्णांक err;

	अगर (cpu_port)
		del_mask = BIT(HOST_PORT_NUM);
	अन्यथा
		del_mask = BIT(priv->emac_port);

	err = cpsw_ale_del_mcast(cpsw->ale, mdb->addr, del_mask,
				 ALE_VLAN, mdb->vid);
	dev_dbg(priv->dev, "MDB del: %s: vid %u:%pM  ports: %X\n",
		priv->ndev->name, mdb->vid, mdb->addr, del_mask);

	वापस err;
पूर्ण

अटल पूर्णांक cpsw_port_obj_add(काष्ठा net_device *ndev,
			     स्थिर काष्ठा चयनdev_obj *obj,
			     काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_obj_port_vlan *vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);
	काष्ठा चयनdev_obj_port_mdb *mdb = SWITCHDEV_OBJ_PORT_MDB(obj);
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	पूर्णांक err = 0;

	dev_dbg(priv->dev, "obj_add: id %u port: %u\n",
		obj->id, priv->emac_port);

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = cpsw_port_vlans_add(priv, vlan);
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
	हाल SWITCHDEV_OBJ_ID_HOST_MDB:
		err = cpsw_port_mdb_add(priv, mdb);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक cpsw_port_obj_del(काष्ठा net_device *ndev,
			     स्थिर काष्ठा चयनdev_obj *obj)
अणु
	काष्ठा चयनdev_obj_port_vlan *vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);
	काष्ठा चयनdev_obj_port_mdb *mdb = SWITCHDEV_OBJ_PORT_MDB(obj);
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	पूर्णांक err = 0;

	dev_dbg(priv->dev, "obj_del: id %u port: %u\n",
		obj->id, priv->emac_port);

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		err = cpsw_port_vlan_del(priv, vlan->vid, vlan->obj.orig_dev);
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
	हाल SWITCHDEV_OBJ_ID_HOST_MDB:
		err = cpsw_port_mdb_del(priv, mdb);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम cpsw_fdb_offload_notअगरy(काष्ठा net_device *ndev,
				    काष्ठा चयनdev_notअगरier_fdb_info *rcv)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info;

	info.addr = rcv->addr;
	info.vid = rcv->vid;
	info.offloaded = true;
	call_चयनdev_notअगरiers(SWITCHDEV_FDB_OFFLOADED,
				 ndev, &info.info, शून्य);
पूर्ण

अटल व्योम cpsw_चयनdev_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cpsw_चयनdev_event_work *चयनdev_work =
		container_of(work, काष्ठा cpsw_चयनdev_event_work, work);
	काष्ठा cpsw_priv *priv = चयनdev_work->priv;
	काष्ठा चयनdev_notअगरier_fdb_info *fdb;
	काष्ठा cpsw_common *cpsw = priv->cpsw;
	पूर्णांक port = priv->emac_port;

	rtnl_lock();
	चयन (चयनdev_work->event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
		fdb = &चयनdev_work->fdb_info;

		dev_dbg(cpsw->dev, "cpsw_fdb_add: MACID = %pM vid = %u flags = %u %u -- port %d\n",
			fdb->addr, fdb->vid, fdb->added_by_user,
			fdb->offloaded, port);

		अगर (!fdb->added_by_user || fdb->is_local)
			अवरोध;
		अगर (स_भेद(priv->mac_addr, (u8 *)fdb->addr, ETH_ALEN) == 0)
			port = HOST_PORT_NUM;

		cpsw_ale_add_ucast(cpsw->ale, (u8 *)fdb->addr, port,
				   fdb->vid ? ALE_VLAN : 0, fdb->vid);
		cpsw_fdb_offload_notअगरy(priv->ndev, fdb);
		अवरोध;
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		fdb = &चयनdev_work->fdb_info;

		dev_dbg(cpsw->dev, "cpsw_fdb_del: MACID = %pM vid = %u flags = %u %u -- port %d\n",
			fdb->addr, fdb->vid, fdb->added_by_user,
			fdb->offloaded, port);

		अगर (!fdb->added_by_user || fdb->is_local)
			अवरोध;
		अगर (स_भेद(priv->mac_addr, (u8 *)fdb->addr, ETH_ALEN) == 0)
			port = HOST_PORT_NUM;

		cpsw_ale_del_ucast(cpsw->ale, (u8 *)fdb->addr, port,
				   fdb->vid ? ALE_VLAN : 0, fdb->vid);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	rtnl_unlock();

	kमुक्त(चयनdev_work->fdb_info.addr);
	kमुक्त(चयनdev_work);
	dev_put(priv->ndev);
पूर्ण

/* called under rcu_पढ़ो_lock() */
अटल पूर्णांक cpsw_चयनdev_event(काष्ठा notअगरier_block *unused,
				अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *ndev = चयनdev_notअगरier_info_to_dev(ptr);
	काष्ठा चयनdev_notअगरier_fdb_info *fdb_info = ptr;
	काष्ठा cpsw_चयनdev_event_work *चयनdev_work;
	काष्ठा cpsw_priv *priv = netdev_priv(ndev);
	पूर्णांक err;

	अगर (event == SWITCHDEV_PORT_ATTR_SET) अणु
		err = चयनdev_handle_port_attr_set(ndev, ptr,
						     cpsw_port_dev_check,
						     cpsw_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	अगर (!cpsw_port_dev_check(ndev))
		वापस NOTIFY_DONE;

	चयनdev_work = kzalloc(माप(*चयनdev_work), GFP_ATOMIC);
	अगर (WARN_ON(!चयनdev_work))
		वापस NOTIFY_BAD;

	INIT_WORK(&चयनdev_work->work, cpsw_चयनdev_event_work);
	चयनdev_work->priv = priv;
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
	.notअगरier_call = cpsw_चयनdev_event,
पूर्ण;

अटल पूर्णांक cpsw_चयनdev_blocking_event(काष्ठा notअगरier_block *unused,
					 अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	पूर्णांक err;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
		err = चयनdev_handle_port_obj_add(dev, ptr,
						    cpsw_port_dev_check,
						    cpsw_port_obj_add);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_OBJ_DEL:
		err = चयनdev_handle_port_obj_del(dev, ptr,
						    cpsw_port_dev_check,
						    cpsw_port_obj_del);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_ATTR_SET:
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     cpsw_port_dev_check,
						     cpsw_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block cpsw_चयनdev_bl_notअगरier = अणु
	.notअगरier_call = cpsw_चयनdev_blocking_event,
पूर्ण;

पूर्णांक cpsw_चयनdev_रेजिस्टर_notअगरiers(काष्ठा cpsw_common *cpsw)
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

व्योम cpsw_चयनdev_unरेजिस्टर_notअगरiers(काष्ठा cpsw_common *cpsw)
अणु
	unरेजिस्टर_चयनdev_blocking_notअगरier(&cpsw_चयनdev_bl_notअगरier);
	unरेजिस्टर_चयनdev_notअगरier(&cpsw_चयनdev_notअगरier);
पूर्ण
