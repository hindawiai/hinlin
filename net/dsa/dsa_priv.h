<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * net/dsa/dsa_priv.h - Hardware चयन handling
 * Copyright (c) 2008-2009 Marvell Semiconductor
 */

#अगर_अघोषित __DSA_PRIV_H
#घोषणा __DSA_PRIV_H

#समावेश <linux/अगर_bridge.h>
#समावेश <linux/phy.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netpoll.h>
#समावेश <net/dsa.h>
#समावेश <net/gro_cells.h>

क्रमागत अणु
	DSA_NOTIFIER_AGEING_TIME,
	DSA_NOTIFIER_BRIDGE_JOIN,
	DSA_NOTIFIER_BRIDGE_LEAVE,
	DSA_NOTIFIER_FDB_ADD,
	DSA_NOTIFIER_FDB_DEL,
	DSA_NOTIFIER_HSR_JOIN,
	DSA_NOTIFIER_HSR_LEAVE,
	DSA_NOTIFIER_LAG_CHANGE,
	DSA_NOTIFIER_LAG_JOIN,
	DSA_NOTIFIER_LAG_LEAVE,
	DSA_NOTIFIER_MDB_ADD,
	DSA_NOTIFIER_MDB_DEL,
	DSA_NOTIFIER_VLAN_ADD,
	DSA_NOTIFIER_VLAN_DEL,
	DSA_NOTIFIER_MTU,
	DSA_NOTIFIER_TAG_PROTO,
	DSA_NOTIFIER_MRP_ADD,
	DSA_NOTIFIER_MRP_DEL,
	DSA_NOTIFIER_MRP_ADD_RING_ROLE,
	DSA_NOTIFIER_MRP_DEL_RING_ROLE,
पूर्ण;

/* DSA_NOTIFIER_AGEING_TIME */
काष्ठा dsa_notअगरier_ageing_समय_info अणु
	अचिन्हित पूर्णांक ageing_समय;
पूर्ण;

/* DSA_NOTIFIER_BRIDGE_* */
काष्ठा dsa_notअगरier_bridge_info अणु
	काष्ठा net_device *br;
	पूर्णांक tree_index;
	पूर्णांक sw_index;
	पूर्णांक port;
पूर्ण;

/* DSA_NOTIFIER_FDB_* */
काष्ठा dsa_notअगरier_fdb_info अणु
	पूर्णांक sw_index;
	पूर्णांक port;
	स्थिर अचिन्हित अक्षर *addr;
	u16 vid;
पूर्ण;

/* DSA_NOTIFIER_MDB_* */
काष्ठा dsa_notअगरier_mdb_info अणु
	स्थिर काष्ठा चयनdev_obj_port_mdb *mdb;
	पूर्णांक sw_index;
	पूर्णांक port;
पूर्ण;

/* DSA_NOTIFIER_LAG_* */
काष्ठा dsa_notअगरier_lag_info अणु
	काष्ठा net_device *lag;
	पूर्णांक sw_index;
	पूर्णांक port;

	काष्ठा netdev_lag_upper_info *info;
पूर्ण;

/* DSA_NOTIFIER_VLAN_* */
काष्ठा dsa_notअगरier_vlan_info अणु
	स्थिर काष्ठा चयनdev_obj_port_vlan *vlan;
	पूर्णांक sw_index;
	पूर्णांक port;
	काष्ठा netlink_ext_ack *extack;
पूर्ण;

/* DSA_NOTIFIER_MTU */
काष्ठा dsa_notअगरier_mtu_info अणु
	bool propagate_upstream;
	पूर्णांक sw_index;
	पूर्णांक port;
	पूर्णांक mtu;
पूर्ण;

/* DSA_NOTIFIER_TAG_PROTO_* */
काष्ठा dsa_notअगरier_tag_proto_info अणु
	स्थिर काष्ठा dsa_device_ops *tag_ops;
पूर्ण;

/* DSA_NOTIFIER_MRP_* */
काष्ठा dsa_notअगरier_mrp_info अणु
	स्थिर काष्ठा चयनdev_obj_mrp *mrp;
	पूर्णांक sw_index;
	पूर्णांक port;
पूर्ण;

/* DSA_NOTIFIER_MRP_* */
काष्ठा dsa_notअगरier_mrp_ring_role_info अणु
	स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp;
	पूर्णांक sw_index;
	पूर्णांक port;
पूर्ण;

काष्ठा dsa_चयनdev_event_work अणु
	काष्ठा dsa_चयन *ds;
	पूर्णांक port;
	काष्ठा work_काष्ठा work;
	अचिन्हित दीर्घ event;
	/* Specअगरic क्रम SWITCHDEV_FDB_ADD_TO_DEVICE and
	 * SWITCHDEV_FDB_DEL_TO_DEVICE
	 */
	अचिन्हित अक्षर addr[ETH_ALEN];
	u16 vid;
पूर्ण;

/* DSA_NOTIFIER_HSR_* */
काष्ठा dsa_notअगरier_hsr_info अणु
	काष्ठा net_device *hsr;
	पूर्णांक sw_index;
	पूर्णांक port;
पूर्ण;

काष्ठा dsa_slave_priv अणु
	/* Copy of CPU port xmit क्रम faster access in slave transmit hot path */
	काष्ठा sk_buff *	(*xmit)(काष्ठा sk_buff *skb,
					काष्ठा net_device *dev);

	काष्ठा gro_cells	gcells;

	/* DSA port data, such as चयन, port index, etc. */
	काष्ठा dsa_port		*dp;

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	काष्ठा netpoll		*netpoll;
#पूर्ण_अगर

	/* TC context */
	काष्ठा list_head	mall_tc_list;
पूर्ण;

/* dsa.c */
स्थिर काष्ठा dsa_device_ops *dsa_tag_driver_get(पूर्णांक tag_protocol);
व्योम dsa_tag_driver_put(स्थिर काष्ठा dsa_device_ops *ops);
स्थिर काष्ठा dsa_device_ops *dsa_find_tagger_by_name(स्थिर अक्षर *buf);

bool dsa_schedule_work(काष्ठा work_काष्ठा *work);
स्थिर अक्षर *dsa_tag_protocol_to_str(स्थिर काष्ठा dsa_device_ops *ops);

/* master.c */
पूर्णांक dsa_master_setup(काष्ठा net_device *dev, काष्ठा dsa_port *cpu_dp);
व्योम dsa_master_tearकरोwn(काष्ठा net_device *dev);

अटल अंतरभूत काष्ठा net_device *dsa_master_find_slave(काष्ठा net_device *dev,
						       पूर्णांक device, पूर्णांक port)
अणु
	काष्ठा dsa_port *cpu_dp = dev->dsa_ptr;
	काष्ठा dsa_चयन_tree *dst = cpu_dp->dst;
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dp->ds->index == device && dp->index == port &&
		    dp->type == DSA_PORT_TYPE_USER)
			वापस dp->slave;

	वापस शून्य;
पूर्ण

/* port.c */
व्योम dsa_port_set_tag_protocol(काष्ठा dsa_port *cpu_dp,
			       स्थिर काष्ठा dsa_device_ops *tag_ops);
पूर्णांक dsa_port_set_state(काष्ठा dsa_port *dp, u8 state);
पूर्णांक dsa_port_enable_rt(काष्ठा dsa_port *dp, काष्ठा phy_device *phy);
पूर्णांक dsa_port_enable(काष्ठा dsa_port *dp, काष्ठा phy_device *phy);
व्योम dsa_port_disable_rt(काष्ठा dsa_port *dp);
व्योम dsa_port_disable(काष्ठा dsa_port *dp);
पूर्णांक dsa_port_bridge_join(काष्ठा dsa_port *dp, काष्ठा net_device *br,
			 काष्ठा netlink_ext_ack *extack);
व्योम dsa_port_bridge_leave(काष्ठा dsa_port *dp, काष्ठा net_device *br);
पूर्णांक dsa_port_lag_change(काष्ठा dsa_port *dp,
			काष्ठा netdev_lag_lower_state_info *linfo);
पूर्णांक dsa_port_lag_join(काष्ठा dsa_port *dp, काष्ठा net_device *lag_dev,
		      काष्ठा netdev_lag_upper_info *uinfo,
		      काष्ठा netlink_ext_ack *extack);
व्योम dsa_port_lag_leave(काष्ठा dsa_port *dp, काष्ठा net_device *lag_dev);
पूर्णांक dsa_port_vlan_filtering(काष्ठा dsa_port *dp, bool vlan_filtering,
			    काष्ठा netlink_ext_ack *extack);
bool dsa_port_skip_vlan_configuration(काष्ठा dsa_port *dp);
पूर्णांक dsa_port_ageing_समय(काष्ठा dsa_port *dp, घड़ी_प्रकार ageing_घड़ी);
पूर्णांक dsa_port_mtu_change(काष्ठा dsa_port *dp, पूर्णांक new_mtu,
			bool propagate_upstream);
पूर्णांक dsa_port_fdb_add(काष्ठा dsa_port *dp, स्थिर अचिन्हित अक्षर *addr,
		     u16 vid);
पूर्णांक dsa_port_fdb_del(काष्ठा dsa_port *dp, स्थिर अचिन्हित अक्षर *addr,
		     u16 vid);
पूर्णांक dsa_port_fdb_dump(काष्ठा dsa_port *dp, dsa_fdb_dump_cb_t *cb, व्योम *data);
पूर्णांक dsa_port_mdb_add(स्थिर काष्ठा dsa_port *dp,
		     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
पूर्णांक dsa_port_mdb_del(स्थिर काष्ठा dsa_port *dp,
		     स्थिर काष्ठा चयनdev_obj_port_mdb *mdb);
पूर्णांक dsa_port_pre_bridge_flags(स्थिर काष्ठा dsa_port *dp,
			      काष्ठा चयनdev_brport_flags flags,
			      काष्ठा netlink_ext_ack *extack);
पूर्णांक dsa_port_bridge_flags(स्थिर काष्ठा dsa_port *dp,
			  काष्ठा चयनdev_brport_flags flags,
			  काष्ठा netlink_ext_ack *extack);
पूर्णांक dsa_port_mrouter(काष्ठा dsa_port *dp, bool mrouter,
		     काष्ठा netlink_ext_ack *extack);
पूर्णांक dsa_port_vlan_add(काष्ठा dsa_port *dp,
		      स्थिर काष्ठा चयनdev_obj_port_vlan *vlan,
		      काष्ठा netlink_ext_ack *extack);
पूर्णांक dsa_port_vlan_del(काष्ठा dsa_port *dp,
		      स्थिर काष्ठा चयनdev_obj_port_vlan *vlan);
पूर्णांक dsa_port_mrp_add(स्थिर काष्ठा dsa_port *dp,
		     स्थिर काष्ठा चयनdev_obj_mrp *mrp);
पूर्णांक dsa_port_mrp_del(स्थिर काष्ठा dsa_port *dp,
		     स्थिर काष्ठा चयनdev_obj_mrp *mrp);
पूर्णांक dsa_port_mrp_add_ring_role(स्थिर काष्ठा dsa_port *dp,
			       स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp);
पूर्णांक dsa_port_mrp_del_ring_role(स्थिर काष्ठा dsa_port *dp,
			       स्थिर काष्ठा चयनdev_obj_ring_role_mrp *mrp);
पूर्णांक dsa_port_link_रेजिस्टर_of(काष्ठा dsa_port *dp);
व्योम dsa_port_link_unरेजिस्टर_of(काष्ठा dsa_port *dp);
पूर्णांक dsa_port_hsr_join(काष्ठा dsa_port *dp, काष्ठा net_device *hsr);
व्योम dsa_port_hsr_leave(काष्ठा dsa_port *dp, काष्ठा net_device *hsr);
बाह्य स्थिर काष्ठा phylink_mac_ops dsa_port_phylink_mac_ops;

अटल अंतरभूत bool dsa_port_offloads_bridge_port(काष्ठा dsa_port *dp,
						 काष्ठा net_device *dev)
अणु
	वापस dsa_port_to_bridge_port(dp) == dev;
पूर्ण

अटल अंतरभूत bool dsa_port_offloads_bridge(काष्ठा dsa_port *dp,
					    काष्ठा net_device *bridge_dev)
अणु
	/* DSA ports connected to a bridge, and event was emitted
	 * क्रम the bridge.
	 */
	वापस dp->bridge_dev == bridge_dev;
पूर्ण

/* Returns true अगर any port of this tree offloads the given net_device */
अटल अंतरभूत bool dsa_tree_offloads_bridge_port(काष्ठा dsa_चयन_tree *dst,
						 काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp;

	list_क्रम_each_entry(dp, &dst->ports, list)
		अगर (dsa_port_offloads_bridge_port(dp, dev))
			वापस true;

	वापस false;
पूर्ण

/* slave.c */
बाह्य स्थिर काष्ठा dsa_device_ops notag_netdev_ops;
बाह्य काष्ठा notअगरier_block dsa_slave_चयनdev_notअगरier;
बाह्य काष्ठा notअगरier_block dsa_slave_चयनdev_blocking_notअगरier;

व्योम dsa_slave_mii_bus_init(काष्ठा dsa_चयन *ds);
पूर्णांक dsa_slave_create(काष्ठा dsa_port *dp);
व्योम dsa_slave_destroy(काष्ठा net_device *slave_dev);
पूर्णांक dsa_slave_suspend(काष्ठा net_device *slave_dev);
पूर्णांक dsa_slave_resume(काष्ठा net_device *slave_dev);
पूर्णांक dsa_slave_रेजिस्टर_notअगरier(व्योम);
व्योम dsa_slave_unरेजिस्टर_notअगरier(व्योम);
व्योम dsa_slave_setup_tagger(काष्ठा net_device *slave);
पूर्णांक dsa_slave_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu);

अटल अंतरभूत काष्ठा dsa_port *dsa_slave_to_port(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);

	वापस p->dp;
पूर्ण

अटल अंतरभूत काष्ठा net_device *
dsa_slave_to_master(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	वापस dp->cpu_dp->master;
पूर्ण

/* If under a bridge with vlan_filtering=0, make sure to send pvid-tagged
 * frames as untagged, since the bridge will not untag them.
 */
अटल अंतरभूत काष्ठा sk_buff *dsa_untag_bridge_pvid(काष्ठा sk_buff *skb)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(skb->dev);
	काष्ठा net_device *br = dp->bridge_dev;
	काष्ठा net_device *dev = skb->dev;
	काष्ठा net_device *upper_dev;
	u16 vid, pvid, proto;
	पूर्णांक err;

	अगर (!br || br_vlan_enabled(br))
		वापस skb;

	err = br_vlan_get_proto(br, &proto);
	अगर (err)
		वापस skb;

	/* Move VLAN tag from data to hwaccel */
	अगर (!skb_vlan_tag_present(skb) && skb->protocol == htons(proto)) अणु
		skb = skb_vlan_untag(skb);
		अगर (!skb)
			वापस शून्य;
	पूर्ण

	अगर (!skb_vlan_tag_present(skb))
		वापस skb;

	vid = skb_vlan_tag_get_id(skb);

	/* We alपढ़ोy run under an RCU पढ़ो-side critical section since
	 * we are called from netअगर_receive_skb_list_पूर्णांकernal().
	 */
	err = br_vlan_get_pvid_rcu(dev, &pvid);
	अगर (err)
		वापस skb;

	अगर (vid != pvid)
		वापस skb;

	/* The sad part about attempting to untag from DSA is that we
	 * करोn't know, unless we check, अगर the skb will end up in
	 * the bridge's data path - br_allowed_ingress() - or not.
	 * For example, there might be an 8021q upper क्रम the
	 * शेष_pvid of the bridge, which will steal VLAN-tagged traffic
	 * from the bridge's data path. This is a configuration that DSA
	 * supports because vlan_filtering is 0. In that हाल, we should
	 * definitely keep the tag, to make sure it keeps working.
	 */
	upper_dev = __vlan_find_dev_deep_rcu(br, htons(proto), vid);
	अगर (upper_dev)
		वापस skb;

	__vlan_hwaccel_clear_tag(skb);

	वापस skb;
पूर्ण

/* चयन.c */
पूर्णांक dsa_चयन_रेजिस्टर_notअगरier(काष्ठा dsa_चयन *ds);
व्योम dsa_चयन_unरेजिस्टर_notअगरier(काष्ठा dsa_चयन *ds);

/* dsa2.c */
व्योम dsa_lag_map(काष्ठा dsa_चयन_tree *dst, काष्ठा net_device *lag);
व्योम dsa_lag_unmap(काष्ठा dsa_चयन_tree *dst, काष्ठा net_device *lag);
पूर्णांक dsa_tree_notअगरy(काष्ठा dsa_चयन_tree *dst, अचिन्हित दीर्घ e, व्योम *v);
पूर्णांक dsa_broadcast(अचिन्हित दीर्घ e, व्योम *v);
पूर्णांक dsa_tree_change_tag_proto(काष्ठा dsa_चयन_tree *dst,
			      काष्ठा net_device *master,
			      स्थिर काष्ठा dsa_device_ops *tag_ops,
			      स्थिर काष्ठा dsa_device_ops *old_tag_ops);

बाह्य काष्ठा list_head dsa_tree_list;

#पूर्ण_अगर
