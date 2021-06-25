<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
#समावेश <linux/kernel.h>
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/skbuff.h>
#समावेश <net/चयनdev.h>

#समावेश "br_private.h"

अटल पूर्णांक br_चयनdev_mark_get(काष्ठा net_bridge *br, काष्ठा net_device *dev)
अणु
	काष्ठा net_bridge_port *p;

	/* dev is yet to be added to the port list. */
	list_क्रम_each_entry(p, &br->port_list, list) अणु
		अगर (netdev_port_same_parent_id(dev, p->dev))
			वापस p->offload_fwd_mark;
	पूर्ण

	वापस ++br->offload_fwd_mark;
पूर्ण

पूर्णांक nbp_चयनdev_mark_set(काष्ठा net_bridge_port *p)
अणु
	काष्ठा netdev_phys_item_id ppid = अणु पूर्ण;
	पूर्णांक err;

	ASSERT_RTNL();

	err = dev_get_port_parent_id(p->dev, &ppid, true);
	अगर (err) अणु
		अगर (err == -EOPNOTSUPP)
			वापस 0;
		वापस err;
	पूर्ण

	p->offload_fwd_mark = br_चयनdev_mark_get(p->br, p->dev);

	वापस 0;
पूर्ण

व्योम nbp_चयनdev_frame_mark(स्थिर काष्ठा net_bridge_port *p,
			      काष्ठा sk_buff *skb)
अणु
	अगर (skb->offload_fwd_mark && !WARN_ON_ONCE(!p->offload_fwd_mark))
		BR_INPUT_SKB_CB(skb)->offload_fwd_mark = p->offload_fwd_mark;
पूर्ण

bool nbp_चयनdev_allowed_egress(स्थिर काष्ठा net_bridge_port *p,
				  स्थिर काष्ठा sk_buff *skb)
अणु
	वापस !skb->offload_fwd_mark ||
	       BR_INPUT_SKB_CB(skb)->offload_fwd_mark != p->offload_fwd_mark;
पूर्ण

/* Flags that can be offloaded to hardware */
#घोषणा BR_PORT_FLAGS_HW_OFFLOAD (BR_LEARNING | BR_FLOOD | \
				  BR_MCAST_FLOOD | BR_BCAST_FLOOD)

पूर्णांक br_चयनdev_set_port_flag(काष्ठा net_bridge_port *p,
			       अचिन्हित दीर्घ flags,
			       अचिन्हित दीर्घ mask,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_attr attr = अणु
		.orig_dev = p->dev,
	पूर्ण;
	काष्ठा चयनdev_notअगरier_port_attr_info info = अणु
		.attr = &attr,
	पूर्ण;
	पूर्णांक err;

	mask &= BR_PORT_FLAGS_HW_OFFLOAD;
	अगर (!mask)
		वापस 0;

	attr.id = SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS;
	attr.u.brport_flags.val = flags;
	attr.u.brport_flags.mask = mask;

	/* We run from atomic context here */
	err = call_चयनdev_notअगरiers(SWITCHDEV_PORT_ATTR_SET, p->dev,
				       &info.info, extack);
	err = notअगरier_to_त्रुटि_सं(err);
	अगर (err == -EOPNOTSUPP)
		वापस 0;

	अगर (err) अणु
		अगर (extack && !extack->_msg)
			NL_SET_ERR_MSG_MOD(extack,
					   "bridge flag offload is not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	attr.id = SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS;
	attr.flags = SWITCHDEV_F_DEFER;

	err = चयनdev_port_attr_set(p->dev, &attr, extack);
	अगर (err) अणु
		अगर (extack && !extack->_msg)
			NL_SET_ERR_MSG_MOD(extack,
					   "error setting offload flag on port");
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

व्योम
br_चयनdev_fdb_notअगरy(स्थिर काष्ठा net_bridge_fdb_entry *fdb, पूर्णांक type)
अणु
	काष्ठा चयनdev_notअगरier_fdb_info info = अणु
		.addr = fdb->key.addr.addr,
		.vid = fdb->key.vlan_id,
		.added_by_user = test_bit(BR_FDB_ADDED_BY_USER, &fdb->flags),
		.is_local = test_bit(BR_FDB_LOCAL, &fdb->flags),
		.offloaded = test_bit(BR_FDB_OFFLOADED, &fdb->flags),
	पूर्ण;

	अगर (!fdb->dst)
		वापस;

	चयन (type) अणु
	हाल RTM_DELNEIGH:
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_DEL_TO_DEVICE,
					 fdb->dst->dev, &info.info, शून्य);
		अवरोध;
	हाल RTM_NEWNEIGH:
		call_चयनdev_notअगरiers(SWITCHDEV_FDB_ADD_TO_DEVICE,
					 fdb->dst->dev, &info.info, शून्य);
		अवरोध;
	पूर्ण
पूर्ण

पूर्णांक br_चयनdev_port_vlan_add(काष्ठा net_device *dev, u16 vid, u16 flags,
			       काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा चयनdev_obj_port_vlan v = अणु
		.obj.orig_dev = dev,
		.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
		.flags = flags,
		.vid = vid,
	पूर्ण;

	वापस चयनdev_port_obj_add(dev, &v.obj, extack);
पूर्ण

पूर्णांक br_चयनdev_port_vlan_del(काष्ठा net_device *dev, u16 vid)
अणु
	काष्ठा चयनdev_obj_port_vlan v = अणु
		.obj.orig_dev = dev,
		.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
		.vid = vid,
	पूर्ण;

	वापस चयनdev_port_obj_del(dev, &v.obj);
पूर्ण
