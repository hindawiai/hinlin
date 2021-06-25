<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * net/dsa/slave.c - Slave device handling
 * Copyright (c) 2008-2009 Marvell Semiconductor
 */

#समावेश <linux/list.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/phy.h>
#समावेश <linux/phy_fixed.h>
#समावेश <linux/phylink.h>
#समावेश <linux/of_net.h>
#समावेश <linux/of_mdपन.स>
#समावेश <linux/mdपन.स>
#समावेश <net/rtnetlink.h>
#समावेश <net/pkt_cls.h>
#समावेश <net/selftests.h>
#समावेश <net/tc_act/tc_mirred.h>
#समावेश <linux/अगर_bridge.h>
#समावेश <linux/अगर_hsr.h>
#समावेश <linux/netpoll.h>

#समावेश "dsa_priv.h"

/* slave mii_bus handling ***************************************************/
अटल पूर्णांक dsa_slave_phy_पढ़ो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक reg)
अणु
	काष्ठा dsa_चयन *ds = bus->priv;

	अगर (ds->phys_mii_mask & (1 << addr))
		वापस ds->ops->phy_पढ़ो(ds, addr, reg);

	वापस 0xffff;
पूर्ण

अटल पूर्णांक dsa_slave_phy_ग_लिखो(काष्ठा mii_bus *bus, पूर्णांक addr, पूर्णांक reg, u16 val)
अणु
	काष्ठा dsa_चयन *ds = bus->priv;

	अगर (ds->phys_mii_mask & (1 << addr))
		वापस ds->ops->phy_ग_लिखो(ds, addr, reg, val);

	वापस 0;
पूर्ण

व्योम dsa_slave_mii_bus_init(काष्ठा dsa_चयन *ds)
अणु
	ds->slave_mii_bus->priv = (व्योम *)ds;
	ds->slave_mii_bus->name = "dsa slave smi";
	ds->slave_mii_bus->पढ़ो = dsa_slave_phy_पढ़ो;
	ds->slave_mii_bus->ग_लिखो = dsa_slave_phy_ग_लिखो;
	snम_लिखो(ds->slave_mii_bus->id, MII_BUS_ID_SIZE, "dsa-%d.%d",
		 ds->dst->index, ds->index);
	ds->slave_mii_bus->parent = ds->dev;
	ds->slave_mii_bus->phy_mask = ~ds->phys_mii_mask;
पूर्ण


/* slave device handling ****************************************************/
अटल पूर्णांक dsa_slave_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	वापस dsa_slave_to_master(dev)->अगरindex;
पूर्ण

अटल पूर्णांक dsa_slave_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	पूर्णांक err;

	err = dev_खोलो(master, शून्य);
	अगर (err < 0) अणु
		netdev_err(dev, "failed to open master %s\n", master->name);
		जाओ out;
	पूर्ण

	अगर (!ether_addr_equal(dev->dev_addr, master->dev_addr)) अणु
		err = dev_uc_add(master, dev->dev_addr);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI) अणु
		err = dev_set_allmulti(master, 1);
		अगर (err < 0)
			जाओ del_unicast;
	पूर्ण
	अगर (dev->flags & IFF_PROMISC) अणु
		err = dev_set_promiscuity(master, 1);
		अगर (err < 0)
			जाओ clear_allmulti;
	पूर्ण

	err = dsa_port_enable_rt(dp, dev->phydev);
	अगर (err)
		जाओ clear_promisc;

	वापस 0;

clear_promisc:
	अगर (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(master, -1);
clear_allmulti:
	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(master, -1);
del_unicast:
	अगर (!ether_addr_equal(dev->dev_addr, master->dev_addr))
		dev_uc_del(master, dev->dev_addr);
out:
	वापस err;
पूर्ण

अटल पूर्णांक dsa_slave_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	dsa_port_disable_rt(dp);

	dev_mc_unsync(master, dev);
	dev_uc_unsync(master, dev);
	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(master, -1);
	अगर (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(master, -1);

	अगर (!ether_addr_equal(dev->dev_addr, master->dev_addr))
		dev_uc_del(master, dev->dev_addr);

	वापस 0;
पूर्ण

अटल व्योम dsa_slave_change_rx_flags(काष्ठा net_device *dev, पूर्णांक change)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	अगर (dev->flags & IFF_UP) अणु
		अगर (change & IFF_ALLMULTI)
			dev_set_allmulti(master,
					 dev->flags & IFF_ALLMULTI ? 1 : -1);
		अगर (change & IFF_PROMISC)
			dev_set_promiscuity(master,
					    dev->flags & IFF_PROMISC ? 1 : -1);
	पूर्ण
पूर्ण

अटल व्योम dsa_slave_set_rx_mode(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);

	dev_mc_sync(master, dev);
	dev_uc_sync(master, dev);
पूर्ण

अटल पूर्णांक dsa_slave_set_mac_address(काष्ठा net_device *dev, व्योम *a)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा sockaddr *addr = a;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (!(dev->flags & IFF_UP))
		जाओ out;

	अगर (!ether_addr_equal(addr->sa_data, master->dev_addr)) अणु
		err = dev_uc_add(master, addr->sa_data);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!ether_addr_equal(dev->dev_addr, master->dev_addr))
		dev_uc_del(master, dev->dev_addr);

out:
	ether_addr_copy(dev->dev_addr, addr->sa_data);

	वापस 0;
पूर्ण

काष्ठा dsa_slave_dump_ctx अणु
	काष्ठा net_device *dev;
	काष्ठा sk_buff *skb;
	काष्ठा netlink_callback *cb;
	पूर्णांक idx;
पूर्ण;

अटल पूर्णांक
dsa_slave_port_fdb_करो_dump(स्थिर अचिन्हित अक्षर *addr, u16 vid,
			   bool is_अटल, व्योम *data)
अणु
	काष्ठा dsa_slave_dump_ctx *dump = data;
	u32 portid = NETLINK_CB(dump->cb->skb).portid;
	u32 seq = dump->cb->nlh->nlmsg_seq;
	काष्ठा nlmsghdr *nlh;
	काष्ठा ndmsg *ndm;

	अगर (dump->idx < dump->cb->args[2])
		जाओ skip;

	nlh = nlmsg_put(dump->skb, portid, seq, RTM_NEWNEIGH,
			माप(*ndm), NLM_F_MULTI);
	अगर (!nlh)
		वापस -EMSGSIZE;

	ndm = nlmsg_data(nlh);
	ndm->ndm_family  = AF_BRIDGE;
	ndm->ndm_pad1    = 0;
	ndm->ndm_pad2    = 0;
	ndm->ndm_flags   = NTF_SELF;
	ndm->ndm_type    = 0;
	ndm->ndm_अगरindex = dump->dev->अगरindex;
	ndm->ndm_state   = is_अटल ? NUD_NOARP : NUD_REACHABLE;

	अगर (nla_put(dump->skb, NDA_LLADDR, ETH_ALEN, addr))
		जाओ nla_put_failure;

	अगर (vid && nla_put_u16(dump->skb, NDA_VLAN, vid))
		जाओ nla_put_failure;

	nlmsg_end(dump->skb, nlh);

skip:
	dump->idx++;
	वापस 0;

nla_put_failure:
	nlmsg_cancel(dump->skb, nlh);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
dsa_slave_fdb_dump(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb,
		   काष्ठा net_device *dev, काष्ठा net_device *filter_dev,
		   पूर्णांक *idx)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_slave_dump_ctx dump = अणु
		.dev = dev,
		.skb = skb,
		.cb = cb,
		.idx = *idx,
	पूर्ण;
	पूर्णांक err;

	err = dsa_port_fdb_dump(dp, dsa_slave_port_fdb_करो_dump, &dump);
	*idx = dump.idx;

	वापस err;
पूर्ण

अटल पूर्णांक dsa_slave_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा dsa_चयन *ds = p->dp->ds;
	पूर्णांक port = p->dp->index;

	/* Pass through to चयन driver अगर it supports बारtamping */
	चयन (cmd) अणु
	हाल SIOCGHWTSTAMP:
		अगर (ds->ops->port_hwtstamp_get)
			वापस ds->ops->port_hwtstamp_get(ds, port, अगरr);
		अवरोध;
	हाल SIOCSHWTSTAMP:
		अगर (ds->ops->port_hwtstamp_set)
			वापस ds->ops->port_hwtstamp_set(ds, port, अगरr);
		अवरोध;
	पूर्ण

	वापस phylink_mii_ioctl(p->dp->pl, अगरr, cmd);
पूर्ण

अटल पूर्णांक dsa_slave_port_attr_set(काष्ठा net_device *dev,
				   स्थिर काष्ठा चयनdev_attr *attr,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	पूर्णांक ret;

	चयन (attr->id) अणु
	हाल SWITCHDEV_ATTR_ID_PORT_STP_STATE:
		अगर (!dsa_port_offloads_bridge_port(dp, attr->orig_dev))
			वापस -EOPNOTSUPP;

		ret = dsa_port_set_state(dp, attr->u.stp_state);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_VLAN_FILTERING:
		अगर (!dsa_port_offloads_bridge(dp, attr->orig_dev))
			वापस -EOPNOTSUPP;

		ret = dsa_port_vlan_filtering(dp, attr->u.vlan_filtering,
					      extack);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_AGEING_TIME:
		अगर (!dsa_port_offloads_bridge(dp, attr->orig_dev))
			वापस -EOPNOTSUPP;

		ret = dsa_port_ageing_समय(dp, attr->u.ageing_समय);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_PRE_BRIDGE_FLAGS:
		अगर (!dsa_port_offloads_bridge_port(dp, attr->orig_dev))
			वापस -EOPNOTSUPP;

		ret = dsa_port_pre_bridge_flags(dp, attr->u.brport_flags,
						extack);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_PORT_BRIDGE_FLAGS:
		अगर (!dsa_port_offloads_bridge_port(dp, attr->orig_dev))
			वापस -EOPNOTSUPP;

		ret = dsa_port_bridge_flags(dp, attr->u.brport_flags, extack);
		अवरोध;
	हाल SWITCHDEV_ATTR_ID_BRIDGE_MROUTER:
		अगर (!dsa_port_offloads_bridge(dp, attr->orig_dev))
			वापस -EOPNOTSUPP;

		ret = dsa_port_mrouter(dp->cpu_dp, attr->u.mrouter, extack);
		अवरोध;
	शेष:
		ret = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

/* Must be called under rcu_पढ़ो_lock() */
अटल पूर्णांक
dsa_slave_vlan_check_क्रम_8021q_uppers(काष्ठा net_device *slave,
				      स्थिर काष्ठा चयनdev_obj_port_vlan *vlan)
अणु
	काष्ठा net_device *upper_dev;
	काष्ठा list_head *iter;

	netdev_क्रम_each_upper_dev_rcu(slave, upper_dev, iter) अणु
		u16 vid;

		अगर (!is_vlan_dev(upper_dev))
			जारी;

		vid = vlan_dev_vlan_id(upper_dev);
		अगर (vid == vlan->vid)
			वापस -EBUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_slave_vlan_add(काष्ठा net_device *dev,
			      स्थिर काष्ठा चयनdev_obj *obj,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा चयनdev_obj_port_vlan vlan;
	पूर्णांक err;

	अगर (dsa_port_skip_vlan_configuration(dp)) अणु
		NL_SET_ERR_MSG_MOD(extack, "skipping configuration of VLAN");
		वापस 0;
	पूर्ण

	vlan = *SWITCHDEV_OBJ_PORT_VLAN(obj);

	/* Deny adding a bridge VLAN when there is alपढ़ोy an 802.1Q upper with
	 * the same VID.
	 */
	अगर (br_vlan_enabled(dp->bridge_dev)) अणु
		rcu_पढ़ो_lock();
		err = dsa_slave_vlan_check_क्रम_8021q_uppers(dev, &vlan);
		rcu_पढ़ो_unlock();
		अगर (err) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Port already has a VLAN upper with this VID");
			वापस err;
		पूर्ण
	पूर्ण

	err = dsa_port_vlan_add(dp, &vlan, extack);
	अगर (err)
		वापस err;

	/* We need the dedicated CPU port to be a member of the VLAN as well.
	 * Even though drivers often handle CPU membership in special ways,
	 * it करोesn't make sense to program a PVID, so clear this flag.
	 */
	vlan.flags &= ~BRIDGE_VLAN_INFO_PVID;

	err = dsa_port_vlan_add(dp->cpu_dp, &vlan, extack);
	अगर (err)
		वापस err;

	वापस vlan_vid_add(master, htons(ETH_P_8021Q), vlan.vid);
पूर्ण

अटल पूर्णांक dsa_slave_port_obj_add(काष्ठा net_device *dev,
				  स्थिर काष्ठा चयनdev_obj *obj,
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	पूर्णांक err;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		अगर (!dsa_port_offloads_bridge_port(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		err = dsa_port_mdb_add(dp, SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_HOST_MDB:
		अगर (!dsa_port_offloads_bridge(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		/* DSA can directly translate this to a normal MDB add,
		 * but on the CPU port.
		 */
		err = dsa_port_mdb_add(dp->cpu_dp, SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		अगर (!dsa_port_offloads_bridge_port(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		err = dsa_slave_vlan_add(dev, obj, extack);
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_MRP:
		अगर (!dsa_port_offloads_bridge(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		err = dsa_port_mrp_add(dp, SWITCHDEV_OBJ_MRP(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_RING_ROLE_MRP:
		अगर (!dsa_port_offloads_bridge(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		err = dsa_port_mrp_add_ring_role(dp,
						 SWITCHDEV_OBJ_RING_ROLE_MRP(obj));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dsa_slave_vlan_del(काष्ठा net_device *dev,
			      स्थिर काष्ठा चयनdev_obj *obj)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा चयनdev_obj_port_vlan *vlan;
	पूर्णांक err;

	अगर (dsa_port_skip_vlan_configuration(dp))
		वापस 0;

	vlan = SWITCHDEV_OBJ_PORT_VLAN(obj);

	/* Do not deprogram the CPU port as it may be shared with other user
	 * ports which can be members of this VLAN as well.
	 */
	err = dsa_port_vlan_del(dp, vlan);
	अगर (err)
		वापस err;

	vlan_vid_del(master, htons(ETH_P_8021Q), vlan->vid);

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_slave_port_obj_del(काष्ठा net_device *dev,
				  स्थिर काष्ठा चयनdev_obj *obj)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	पूर्णांक err;

	चयन (obj->id) अणु
	हाल SWITCHDEV_OBJ_ID_PORT_MDB:
		अगर (!dsa_port_offloads_bridge_port(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		err = dsa_port_mdb_del(dp, SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_HOST_MDB:
		अगर (!dsa_port_offloads_bridge(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		/* DSA can directly translate this to a normal MDB add,
		 * but on the CPU port.
		 */
		err = dsa_port_mdb_del(dp->cpu_dp, SWITCHDEV_OBJ_PORT_MDB(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_PORT_VLAN:
		अगर (!dsa_port_offloads_bridge_port(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		err = dsa_slave_vlan_del(dev, obj);
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_MRP:
		अगर (!dsa_port_offloads_bridge(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		err = dsa_port_mrp_del(dp, SWITCHDEV_OBJ_MRP(obj));
		अवरोध;
	हाल SWITCHDEV_OBJ_ID_RING_ROLE_MRP:
		अगर (!dsa_port_offloads_bridge(dp, obj->orig_dev))
			वापस -EOPNOTSUPP;

		err = dsa_port_mrp_del_ring_role(dp,
						 SWITCHDEV_OBJ_RING_ROLE_MRP(obj));
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक dsa_slave_get_port_parent_id(काष्ठा net_device *dev,
					काष्ठा netdev_phys_item_id *ppid)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा dsa_चयन_tree *dst = ds->dst;

	/* For non-legacy ports, devlink is used and it takes
	 * care of the name generation. This nकरो implementation
	 * should be हटाओd with legacy support.
	 */
	अगर (dp->ds->devlink)
		वापस -EOPNOTSUPP;

	ppid->id_len = माप(dst->index);
	स_नकल(&ppid->id, &dst->index, ppid->id_len);

	वापस 0;
पूर्ण

अटल अंतरभूत netdev_tx_t dsa_slave_netpoll_send_skb(काष्ठा net_device *dev,
						     काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);

	वापस netpoll_send_skb(p->netpoll, skb);
#अन्यथा
	BUG();
	वापस NETDEV_TX_OK;
#पूर्ण_अगर
पूर्ण

अटल व्योम dsa_skb_tx_बारtamp(काष्ठा dsa_slave_priv *p,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा dsa_चयन *ds = p->dp->ds;

	अगर (!(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		वापस;

	अगर (!ds->ops->port_txtstamp)
		वापस;

	ds->ops->port_txtstamp(ds, p->dp->index, skb);
पूर्ण

netdev_tx_t dsa_enqueue_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	/* SKB क्रम netpoll still need to be mangled with the protocol-specअगरic
	 * tag to be successfully transmitted
	 */
	अगर (unlikely(netpoll_tx_running(dev)))
		वापस dsa_slave_netpoll_send_skb(dev, skb);

	/* Queue the SKB क्रम transmission on the parent पूर्णांकerface, but
	 * करो not modअगरy its EtherType
	 */
	skb->dev = dsa_slave_to_master(dev);
	dev_queue_xmit(skb);

	वापस NETDEV_TX_OK;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_enqueue_skb);

अटल पूर्णांक dsa_पुनः_स्मृति_skb(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	पूर्णांक needed_headroom = dev->needed_headroom;
	पूर्णांक needed_tailroom = dev->needed_tailroom;

	/* For tail taggers, we need to pad लघु frames ourselves, to ensure
	 * that the tail tag करोes not fail at its role of being at the end of
	 * the packet, once the master पूर्णांकerface pads the frame. Account क्रम
	 * that pad length here, and pad later.
	 */
	अगर (unlikely(needed_tailroom && skb->len < ETH_ZLEN))
		needed_tailroom += ETH_ZLEN - skb->len;
	/* skb_headroom() वापसs अचिन्हित पूर्णांक... */
	needed_headroom = max_t(पूर्णांक, needed_headroom - skb_headroom(skb), 0);
	needed_tailroom = max_t(पूर्णांक, needed_tailroom - skb_tailroom(skb), 0);

	अगर (likely(!needed_headroom && !needed_tailroom && !skb_cloned(skb)))
		/* No पुनः_स्मृतिation needed, yay! */
		वापस 0;

	वापस pskb_expand_head(skb, needed_headroom, needed_tailroom,
				GFP_ATOMIC);
पूर्ण

अटल netdev_tx_t dsa_slave_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा sk_buff *nskb;

	dev_sw_netstats_tx_add(dev, 1, skb->len);

	स_रखो(skb->cb, 0, माप(skb->cb));

	/* Handle tx बारtamp अगर any */
	dsa_skb_tx_बारtamp(p, skb);

	अगर (dsa_पुनः_स्मृति_skb(skb, dev)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* needed_tailroom should still be 'warm' in the cache line from
	 * dsa_पुनः_स्मृति_skb(), which has also ensured that padding is safe.
	 */
	अगर (dev->needed_tailroom)
		eth_skb_pad(skb);

	/* Transmit function may have to पुनः_स्मृतिate the original SKB,
	 * in which हाल it must have मुक्तd it. Only मुक्त it here on error.
	 */
	nskb = p->xmit(skb, dev);
	अगर (!nskb) अणु
		kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	वापस dsa_enqueue_skb(nskb, dev);
पूर्ण

/* ethtool operations *******************************************************/

अटल व्योम dsa_slave_get_drvinfo(काष्ठा net_device *dev,
				  काष्ठा ethtool_drvinfo *drvinfo)
अणु
	strlcpy(drvinfo->driver, "dsa", माप(drvinfo->driver));
	strlcpy(drvinfo->fw_version, "N/A", माप(drvinfo->fw_version));
	strlcpy(drvinfo->bus_info, "platform", माप(drvinfo->bus_info));
पूर्ण

अटल पूर्णांक dsa_slave_get_regs_len(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (ds->ops->get_regs_len)
		वापस ds->ops->get_regs_len(ds, dp->index);

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम
dsa_slave_get_regs(काष्ठा net_device *dev, काष्ठा ethtool_regs *regs, व्योम *_p)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (ds->ops->get_regs)
		ds->ops->get_regs(ds, dp->index, regs, _p);
पूर्ण

अटल पूर्णांक dsa_slave_nway_reset(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	वापस phylink_ethtool_nway_reset(dp->pl);
पूर्ण

अटल पूर्णांक dsa_slave_get_eeprom_len(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (ds->cd && ds->cd->eeprom_len)
		वापस ds->cd->eeprom_len;

	अगर (ds->ops->get_eeprom_len)
		वापस ds->ops->get_eeprom_len(ds);

	वापस 0;
पूर्ण

अटल पूर्णांक dsa_slave_get_eeprom(काष्ठा net_device *dev,
				काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (ds->ops->get_eeprom)
		वापस ds->ops->get_eeprom(ds, eeprom, data);

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक dsa_slave_set_eeprom(काष्ठा net_device *dev,
				काष्ठा ethtool_eeprom *eeprom, u8 *data)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (ds->ops->set_eeprom)
		वापस ds->ops->set_eeprom(ds, eeprom, data);

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम dsa_slave_get_strings(काष्ठा net_device *dev,
				  uपूर्णांक32_t stringset, uपूर्णांक8_t *data)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (stringset == ETH_SS_STATS) अणु
		पूर्णांक len = ETH_GSTRING_LEN;

		म_नकलन(data, "tx_packets", len);
		म_नकलन(data + len, "tx_bytes", len);
		म_नकलन(data + 2 * len, "rx_packets", len);
		म_नकलन(data + 3 * len, "rx_bytes", len);
		अगर (ds->ops->get_strings)
			ds->ops->get_strings(ds, dp->index, stringset,
					     data + 4 * len);
	पूर्ण अन्यथा अगर (stringset ==  ETH_SS_TEST) अणु
		net_selftest_get_strings(data);
	पूर्ण

पूर्ण

अटल व्योम dsa_slave_get_ethtool_stats(काष्ठा net_device *dev,
					काष्ठा ethtool_stats *stats,
					uपूर्णांक64_t *data)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा pcpu_sw_netstats *s;
	अचिन्हित पूर्णांक start;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		u64 tx_packets, tx_bytes, rx_packets, rx_bytes;

		s = per_cpu_ptr(dev->tstats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&s->syncp);
			tx_packets = s->tx_packets;
			tx_bytes = s->tx_bytes;
			rx_packets = s->rx_packets;
			rx_bytes = s->rx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&s->syncp, start));
		data[0] += tx_packets;
		data[1] += tx_bytes;
		data[2] += rx_packets;
		data[3] += rx_bytes;
	पूर्ण
	अगर (ds->ops->get_ethtool_stats)
		ds->ops->get_ethtool_stats(ds, dp->index, data + 4);
पूर्ण

अटल पूर्णांक dsa_slave_get_sset_count(काष्ठा net_device *dev, पूर्णांक sset)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (sset == ETH_SS_STATS) अणु
		पूर्णांक count = 0;

		अगर (ds->ops->get_sset_count) अणु
			count = ds->ops->get_sset_count(ds, dp->index, sset);
			अगर (count < 0)
				वापस count;
		पूर्ण

		वापस count + 4;
	पूर्ण अन्यथा अगर (sset ==  ETH_SS_TEST) अणु
		वापस net_selftest_get_count();
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल व्योम dsa_slave_net_selftest(काष्ठा net_device *ndev,
				   काष्ठा ethtool_test *etest, u64 *buf)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(ndev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (ds->ops->self_test) अणु
		ds->ops->self_test(ds, dp->index, etest, buf);
		वापस;
	पूर्ण

	net_selftest(ndev, etest, buf);
पूर्ण

अटल व्योम dsa_slave_get_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *w)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	phylink_ethtool_get_wol(dp->pl, w);

	अगर (ds->ops->get_wol)
		ds->ops->get_wol(ds, dp->index, w);
पूर्ण

अटल पूर्णांक dsa_slave_set_wol(काष्ठा net_device *dev, काष्ठा ethtool_wolinfo *w)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक ret = -EOPNOTSUPP;

	phylink_ethtool_set_wol(dp->pl, w);

	अगर (ds->ops->set_wol)
		ret = ds->ops->set_wol(ds, dp->index, w);

	वापस ret;
पूर्ण

अटल पूर्णांक dsa_slave_set_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *e)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक ret;

	/* Port's PHY and MAC both need to be EEE capable */
	अगर (!dev->phydev || !dp->pl)
		वापस -ENODEV;

	अगर (!ds->ops->set_mac_eee)
		वापस -EOPNOTSUPP;

	ret = ds->ops->set_mac_eee(ds, dp->index, e);
	अगर (ret)
		वापस ret;

	वापस phylink_ethtool_set_eee(dp->pl, e);
पूर्ण

अटल पूर्णांक dsa_slave_get_eee(काष्ठा net_device *dev, काष्ठा ethtool_eee *e)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक ret;

	/* Port's PHY and MAC both need to be EEE capable */
	अगर (!dev->phydev || !dp->pl)
		वापस -ENODEV;

	अगर (!ds->ops->get_mac_eee)
		वापस -EOPNOTSUPP;

	ret = ds->ops->get_mac_eee(ds, dp->index, e);
	अगर (ret)
		वापस ret;

	वापस phylink_ethtool_get_eee(dp->pl, e);
पूर्ण

अटल पूर्णांक dsa_slave_get_link_ksettings(काष्ठा net_device *dev,
					काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	वापस phylink_ethtool_ksettings_get(dp->pl, cmd);
पूर्ण

अटल पूर्णांक dsa_slave_set_link_ksettings(काष्ठा net_device *dev,
					स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	वापस phylink_ethtool_ksettings_set(dp->pl, cmd);
पूर्ण

अटल व्योम dsa_slave_get_छोड़ोparam(काष्ठा net_device *dev,
				     काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	phylink_ethtool_get_छोड़ोparam(dp->pl, छोड़ो);
पूर्ण

अटल पूर्णांक dsa_slave_set_छोड़ोparam(काष्ठा net_device *dev,
				    काष्ठा ethtool_छोड़ोparam *छोड़ो)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	वापस phylink_ethtool_set_छोड़ोparam(dp->pl, छोड़ो);
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल पूर्णांक dsa_slave_netpoll_setup(काष्ठा net_device *dev,
				   काष्ठा netpoll_info *ni)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा netpoll *netpoll;
	पूर्णांक err = 0;

	netpoll = kzalloc(माप(*netpoll), GFP_KERNEL);
	अगर (!netpoll)
		वापस -ENOMEM;

	err = __netpoll_setup(netpoll, master);
	अगर (err) अणु
		kमुक्त(netpoll);
		जाओ out;
	पूर्ण

	p->netpoll = netpoll;
out:
	वापस err;
पूर्ण

अटल व्योम dsa_slave_netpoll_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा netpoll *netpoll = p->netpoll;

	अगर (!netpoll)
		वापस;

	p->netpoll = शून्य;

	__netpoll_मुक्त(netpoll);
पूर्ण

अटल व्योम dsa_slave_poll_controller(काष्ठा net_device *dev)
अणु
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक dsa_slave_get_phys_port_name(काष्ठा net_device *dev,
					अक्षर *name, माप_प्रकार len)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	/* For non-legacy ports, devlink is used and it takes
	 * care of the name generation. This nकरो implementation
	 * should be हटाओd with legacy support.
	 */
	अगर (dp->ds->devlink)
		वापस -EOPNOTSUPP;

	अगर (snम_लिखो(name, len, "p%d", dp->index) >= len)
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल काष्ठा dsa_mall_tc_entry *
dsa_slave_mall_tc_entry_find(काष्ठा net_device *dev, अचिन्हित दीर्घ cookie)
अणु
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा dsa_mall_tc_entry *mall_tc_entry;

	list_क्रम_each_entry(mall_tc_entry, &p->mall_tc_list, list)
		अगर (mall_tc_entry->cookie == cookie)
			वापस mall_tc_entry;

	वापस शून्य;
पूर्ण

अटल पूर्णांक
dsa_slave_add_cls_matchall_mirred(काष्ठा net_device *dev,
				  काष्ठा tc_cls_matchall_offload *cls,
				  bool ingress)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा dsa_mall_mirror_tc_entry *mirror;
	काष्ठा dsa_mall_tc_entry *mall_tc_entry;
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा flow_action_entry *act;
	काष्ठा dsa_port *to_dp;
	पूर्णांक err;

	अगर (!ds->ops->port_mirror_add)
		वापस -EOPNOTSUPP;

	अगर (!flow_action_basic_hw_stats_check(&cls->rule->action,
					      cls->common.extack))
		वापस -EOPNOTSUPP;

	act = &cls->rule->action.entries[0];

	अगर (!act->dev)
		वापस -EINVAL;

	अगर (!dsa_slave_dev_check(act->dev))
		वापस -EOPNOTSUPP;

	mall_tc_entry = kzalloc(माप(*mall_tc_entry), GFP_KERNEL);
	अगर (!mall_tc_entry)
		वापस -ENOMEM;

	mall_tc_entry->cookie = cls->cookie;
	mall_tc_entry->type = DSA_PORT_MALL_MIRROR;
	mirror = &mall_tc_entry->mirror;

	to_dp = dsa_slave_to_port(act->dev);

	mirror->to_local_port = to_dp->index;
	mirror->ingress = ingress;

	err = ds->ops->port_mirror_add(ds, dp->index, mirror, ingress);
	अगर (err) अणु
		kमुक्त(mall_tc_entry);
		वापस err;
	पूर्ण

	list_add_tail(&mall_tc_entry->list, &p->mall_tc_list);

	वापस err;
पूर्ण

अटल पूर्णांक
dsa_slave_add_cls_matchall_police(काष्ठा net_device *dev,
				  काष्ठा tc_cls_matchall_offload *cls,
				  bool ingress)
अणु
	काष्ठा netlink_ext_ack *extack = cls->common.extack;
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा dsa_mall_policer_tc_entry *policer;
	काष्ठा dsa_mall_tc_entry *mall_tc_entry;
	काष्ठा dsa_चयन *ds = dp->ds;
	काष्ठा flow_action_entry *act;
	पूर्णांक err;

	अगर (!ds->ops->port_policer_add) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Policing offload not implemented");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!ingress) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "Only supported on ingress qdisc");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!flow_action_basic_hw_stats_check(&cls->rule->action,
					      cls->common.extack))
		वापस -EOPNOTSUPP;

	list_क्रम_each_entry(mall_tc_entry, &p->mall_tc_list, list) अणु
		अगर (mall_tc_entry->type == DSA_PORT_MALL_POLICER) अणु
			NL_SET_ERR_MSG_MOD(extack,
					   "Only one port policer allowed");
			वापस -EEXIST;
		पूर्ण
	पूर्ण

	act = &cls->rule->action.entries[0];

	mall_tc_entry = kzalloc(माप(*mall_tc_entry), GFP_KERNEL);
	अगर (!mall_tc_entry)
		वापस -ENOMEM;

	mall_tc_entry->cookie = cls->cookie;
	mall_tc_entry->type = DSA_PORT_MALL_POLICER;
	policer = &mall_tc_entry->policer;
	policer->rate_bytes_per_sec = act->police.rate_bytes_ps;
	policer->burst = act->police.burst;

	err = ds->ops->port_policer_add(ds, dp->index, policer);
	अगर (err) अणु
		kमुक्त(mall_tc_entry);
		वापस err;
	पूर्ण

	list_add_tail(&mall_tc_entry->list, &p->mall_tc_list);

	वापस err;
पूर्ण

अटल पूर्णांक dsa_slave_add_cls_matchall(काष्ठा net_device *dev,
				      काष्ठा tc_cls_matchall_offload *cls,
				      bool ingress)
अणु
	पूर्णांक err = -EOPNOTSUPP;

	अगर (cls->common.protocol == htons(ETH_P_ALL) &&
	    flow_offload_has_one_action(&cls->rule->action) &&
	    cls->rule->action.entries[0].id == FLOW_ACTION_MIRRED)
		err = dsa_slave_add_cls_matchall_mirred(dev, cls, ingress);
	अन्यथा अगर (flow_offload_has_one_action(&cls->rule->action) &&
		 cls->rule->action.entries[0].id == FLOW_ACTION_POLICE)
		err = dsa_slave_add_cls_matchall_police(dev, cls, ingress);

	वापस err;
पूर्ण

अटल व्योम dsa_slave_del_cls_matchall(काष्ठा net_device *dev,
				       काष्ठा tc_cls_matchall_offload *cls)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_mall_tc_entry *mall_tc_entry;
	काष्ठा dsa_चयन *ds = dp->ds;

	mall_tc_entry = dsa_slave_mall_tc_entry_find(dev, cls->cookie);
	अगर (!mall_tc_entry)
		वापस;

	list_del(&mall_tc_entry->list);

	चयन (mall_tc_entry->type) अणु
	हाल DSA_PORT_MALL_MIRROR:
		अगर (ds->ops->port_mirror_del)
			ds->ops->port_mirror_del(ds, dp->index,
						 &mall_tc_entry->mirror);
		अवरोध;
	हाल DSA_PORT_MALL_POLICER:
		अगर (ds->ops->port_policer_del)
			ds->ops->port_policer_del(ds, dp->index);
		अवरोध;
	शेष:
		WARN_ON(1);
	पूर्ण

	kमुक्त(mall_tc_entry);
पूर्ण

अटल पूर्णांक dsa_slave_setup_tc_cls_matchall(काष्ठा net_device *dev,
					   काष्ठा tc_cls_matchall_offload *cls,
					   bool ingress)
अणु
	अगर (cls->common.chain_index)
		वापस -EOPNOTSUPP;

	चयन (cls->command) अणु
	हाल TC_CLSMATCHALL_REPLACE:
		वापस dsa_slave_add_cls_matchall(dev, cls, ingress);
	हाल TC_CLSMATCHALL_DESTROY:
		dsa_slave_del_cls_matchall(dev, cls);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dsa_slave_add_cls_flower(काष्ठा net_device *dev,
				    काष्ठा flow_cls_offload *cls,
				    bool ingress)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक port = dp->index;

	अगर (!ds->ops->cls_flower_add)
		वापस -EOPNOTSUPP;

	वापस ds->ops->cls_flower_add(ds, port, cls, ingress);
पूर्ण

अटल पूर्णांक dsa_slave_del_cls_flower(काष्ठा net_device *dev,
				    काष्ठा flow_cls_offload *cls,
				    bool ingress)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक port = dp->index;

	अगर (!ds->ops->cls_flower_del)
		वापस -EOPNOTSUPP;

	वापस ds->ops->cls_flower_del(ds, port, cls, ingress);
पूर्ण

अटल पूर्णांक dsa_slave_stats_cls_flower(काष्ठा net_device *dev,
				      काष्ठा flow_cls_offload *cls,
				      bool ingress)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;
	पूर्णांक port = dp->index;

	अगर (!ds->ops->cls_flower_stats)
		वापस -EOPNOTSUPP;

	वापस ds->ops->cls_flower_stats(ds, port, cls, ingress);
पूर्ण

अटल पूर्णांक dsa_slave_setup_tc_cls_flower(काष्ठा net_device *dev,
					 काष्ठा flow_cls_offload *cls,
					 bool ingress)
अणु
	चयन (cls->command) अणु
	हाल FLOW_CLS_REPLACE:
		वापस dsa_slave_add_cls_flower(dev, cls, ingress);
	हाल FLOW_CLS_DESTROY:
		वापस dsa_slave_del_cls_flower(dev, cls, ingress);
	हाल FLOW_CLS_STATS:
		वापस dsa_slave_stats_cls_flower(dev, cls, ingress);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dsa_slave_setup_tc_block_cb(क्रमागत tc_setup_type type, व्योम *type_data,
				       व्योम *cb_priv, bool ingress)
अणु
	काष्ठा net_device *dev = cb_priv;

	अगर (!tc_can_offload(dev))
		वापस -EOPNOTSUPP;

	चयन (type) अणु
	हाल TC_SETUP_CLSMATCHALL:
		वापस dsa_slave_setup_tc_cls_matchall(dev, type_data, ingress);
	हाल TC_SETUP_CLSFLOWER:
		वापस dsa_slave_setup_tc_cls_flower(dev, type_data, ingress);
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dsa_slave_setup_tc_block_cb_ig(क्रमागत tc_setup_type type,
					  व्योम *type_data, व्योम *cb_priv)
अणु
	वापस dsa_slave_setup_tc_block_cb(type, type_data, cb_priv, true);
पूर्ण

अटल पूर्णांक dsa_slave_setup_tc_block_cb_eg(क्रमागत tc_setup_type type,
					  व्योम *type_data, व्योम *cb_priv)
अणु
	वापस dsa_slave_setup_tc_block_cb(type, type_data, cb_priv, false);
पूर्ण

अटल LIST_HEAD(dsa_slave_block_cb_list);

अटल पूर्णांक dsa_slave_setup_tc_block(काष्ठा net_device *dev,
				    काष्ठा flow_block_offload *f)
अणु
	काष्ठा flow_block_cb *block_cb;
	flow_setup_cb_t *cb;

	अगर (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_INGRESS)
		cb = dsa_slave_setup_tc_block_cb_ig;
	अन्यथा अगर (f->binder_type == FLOW_BLOCK_BINDER_TYPE_CLSACT_EGRESS)
		cb = dsa_slave_setup_tc_block_cb_eg;
	अन्यथा
		वापस -EOPNOTSUPP;

	f->driver_block_list = &dsa_slave_block_cb_list;

	चयन (f->command) अणु
	हाल FLOW_BLOCK_BIND:
		अगर (flow_block_cb_is_busy(cb, dev, &dsa_slave_block_cb_list))
			वापस -EBUSY;

		block_cb = flow_block_cb_alloc(cb, dev, dev, शून्य);
		अगर (IS_ERR(block_cb))
			वापस PTR_ERR(block_cb);

		flow_block_cb_add(block_cb, f);
		list_add_tail(&block_cb->driver_list, &dsa_slave_block_cb_list);
		वापस 0;
	हाल FLOW_BLOCK_UNBIND:
		block_cb = flow_block_cb_lookup(f->block, cb, dev);
		अगर (!block_cb)
			वापस -ENOENT;

		flow_block_cb_हटाओ(block_cb, f);
		list_del(&block_cb->driver_list);
		वापस 0;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण
पूर्ण

अटल पूर्णांक dsa_slave_setup_ft_block(काष्ठा dsa_चयन *ds, पूर्णांक port,
				    व्योम *type_data)
अणु
	काष्ठा dsa_port *cpu_dp = dsa_to_port(ds, port)->cpu_dp;
	काष्ठा net_device *master = cpu_dp->master;

	अगर (!master->netdev_ops->nकरो_setup_tc)
		वापस -EOPNOTSUPP;

	वापस master->netdev_ops->nकरो_setup_tc(master, TC_SETUP_FT, type_data);
पूर्ण

अटल पूर्णांक dsa_slave_setup_tc(काष्ठा net_device *dev, क्रमागत tc_setup_type type,
			      व्योम *type_data)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	चयन (type) अणु
	हाल TC_SETUP_BLOCK:
		वापस dsa_slave_setup_tc_block(dev, type_data);
	हाल TC_SETUP_FT:
		वापस dsa_slave_setup_ft_block(ds, dp->index, type_data);
	शेष:
		अवरोध;
	पूर्ण

	अगर (!ds->ops->port_setup_tc)
		वापस -EOPNOTSUPP;

	वापस ds->ops->port_setup_tc(ds, dp->index, type, type_data);
पूर्ण

अटल पूर्णांक dsa_slave_get_rxnfc(काष्ठा net_device *dev,
			       काष्ठा ethtool_rxnfc *nfc, u32 *rule_locs)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->get_rxnfc)
		वापस -EOPNOTSUPP;

	वापस ds->ops->get_rxnfc(ds, dp->index, nfc, rule_locs);
पूर्ण

अटल पूर्णांक dsa_slave_set_rxnfc(काष्ठा net_device *dev,
			       काष्ठा ethtool_rxnfc *nfc)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (!ds->ops->set_rxnfc)
		वापस -EOPNOTSUPP;

	वापस ds->ops->set_rxnfc(ds, dp->index, nfc);
पूर्ण

अटल पूर्णांक dsa_slave_get_ts_info(काष्ठा net_device *dev,
				 काष्ठा ethtool_ts_info *ts)
अणु
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा dsa_चयन *ds = p->dp->ds;

	अगर (!ds->ops->get_ts_info)
		वापस -EOPNOTSUPP;

	वापस ds->ops->get_ts_info(ds, p->dp->index, ts);
पूर्ण

अटल पूर्णांक dsa_slave_vlan_rx_add_vid(काष्ठा net_device *dev, __be16 proto,
				     u16 vid)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा चयनdev_obj_port_vlan vlan = अणु
		.obj.id = SWITCHDEV_OBJ_ID_PORT_VLAN,
		.vid = vid,
		/* This API only allows programming tagged, non-PVID VIDs */
		.flags = 0,
	पूर्ण;
	काष्ठा netlink_ext_ack extack = अणु0पूर्ण;
	पूर्णांक ret;

	/* User port... */
	ret = dsa_port_vlan_add(dp, &vlan, &extack);
	अगर (ret) अणु
		अगर (extack._msg)
			netdev_err(dev, "%s\n", extack._msg);
		वापस ret;
	पूर्ण

	/* And CPU port... */
	ret = dsa_port_vlan_add(dp->cpu_dp, &vlan, &extack);
	अगर (ret) अणु
		अगर (extack._msg)
			netdev_err(dev, "CPU port %d: %s\n", dp->cpu_dp->index,
				   extack._msg);
		वापस ret;
	पूर्ण

	वापस vlan_vid_add(master, proto, vid);
पूर्ण

अटल पूर्णांक dsa_slave_vlan_rx_समाप्त_vid(काष्ठा net_device *dev, __be16 proto,
				      u16 vid)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा चयनdev_obj_port_vlan vlan = अणु
		.vid = vid,
		/* This API only allows programming tagged, non-PVID VIDs */
		.flags = 0,
	पूर्ण;
	पूर्णांक err;

	/* Do not deprogram the CPU port as it may be shared with other user
	 * ports which can be members of this VLAN as well.
	 */
	err = dsa_port_vlan_del(dp, &vlan);
	अगर (err)
		वापस err;

	vlan_vid_del(master, proto, vid);

	वापस 0;
पूर्ण

काष्ठा dsa_hw_port अणु
	काष्ठा list_head list;
	काष्ठा net_device *dev;
	पूर्णांक old_mtu;
पूर्ण;

अटल पूर्णांक dsa_hw_port_list_set_mtu(काष्ठा list_head *hw_port_list, पूर्णांक mtu)
अणु
	स्थिर काष्ठा dsa_hw_port *p;
	पूर्णांक err;

	list_क्रम_each_entry(p, hw_port_list, list) अणु
		अगर (p->dev->mtu == mtu)
			जारी;

		err = dev_set_mtu(p->dev, mtu);
		अगर (err)
			जाओ rollback;
	पूर्ण

	वापस 0;

rollback:
	list_क्रम_each_entry_जारी_reverse(p, hw_port_list, list) अणु
		अगर (p->dev->mtu == p->old_mtu)
			जारी;

		अगर (dev_set_mtu(p->dev, p->old_mtu))
			netdev_err(p->dev, "Failed to restore MTU\n");
	पूर्ण

	वापस err;
पूर्ण

अटल व्योम dsa_hw_port_list_मुक्त(काष्ठा list_head *hw_port_list)
अणु
	काष्ठा dsa_hw_port *p, *n;

	list_क्रम_each_entry_safe(p, n, hw_port_list, list)
		kमुक्त(p);
पूर्ण

/* Make the hardware datapath to/from @dev limited to a common MTU */
अटल व्योम dsa_bridge_mtu_normalization(काष्ठा dsa_port *dp)
अणु
	काष्ठा list_head hw_port_list;
	काष्ठा dsa_चयन_tree *dst;
	पूर्णांक min_mtu = ETH_MAX_MTU;
	काष्ठा dsa_port *other_dp;
	पूर्णांक err;

	अगर (!dp->ds->mtu_enक्रमcement_ingress)
		वापस;

	अगर (!dp->bridge_dev)
		वापस;

	INIT_LIST_HEAD(&hw_port_list);

	/* Populate the list of ports that are part of the same bridge
	 * as the newly added/modअगरied port
	 */
	list_क्रम_each_entry(dst, &dsa_tree_list, list) अणु
		list_क्रम_each_entry(other_dp, &dst->ports, list) अणु
			काष्ठा dsa_hw_port *hw_port;
			काष्ठा net_device *slave;

			अगर (other_dp->type != DSA_PORT_TYPE_USER)
				जारी;

			अगर (other_dp->bridge_dev != dp->bridge_dev)
				जारी;

			अगर (!other_dp->ds->mtu_enक्रमcement_ingress)
				जारी;

			slave = other_dp->slave;

			अगर (min_mtu > slave->mtu)
				min_mtu = slave->mtu;

			hw_port = kzalloc(माप(*hw_port), GFP_KERNEL);
			अगर (!hw_port)
				जाओ out;

			hw_port->dev = slave;
			hw_port->old_mtu = slave->mtu;

			list_add(&hw_port->list, &hw_port_list);
		पूर्ण
	पूर्ण

	/* Attempt to configure the entire hardware bridge to the newly added
	 * पूर्णांकerface's MTU first, regardless of whether the पूर्णांकention of the
	 * user was to उठाओ or lower it.
	 */
	err = dsa_hw_port_list_set_mtu(&hw_port_list, dp->slave->mtu);
	अगर (!err)
		जाओ out;

	/* Clearly that didn't work out so well, so just set the minimum MTU on
	 * all hardware bridge ports now. If this fails too, then all ports will
	 * still have their old MTU rolled back anyway.
	 */
	dsa_hw_port_list_set_mtu(&hw_port_list, min_mtu);

out:
	dsa_hw_port_list_मुक्त(&hw_port_list);
पूर्ण

पूर्णांक dsa_slave_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(dev);
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_slave_priv *p = netdev_priv(dev);
	काष्ठा dsa_चयन *ds = p->dp->ds;
	काष्ठा dsa_port *cpu_dp;
	पूर्णांक port = p->dp->index;
	पूर्णांक largest_mtu = 0;
	पूर्णांक new_master_mtu;
	पूर्णांक old_master_mtu;
	पूर्णांक mtu_limit;
	पूर्णांक cpu_mtu;
	पूर्णांक err, i;

	अगर (!ds->ops->port_change_mtu)
		वापस -EOPNOTSUPP;

	क्रम (i = 0; i < ds->num_ports; i++) अणु
		पूर्णांक slave_mtu;

		अगर (!dsa_is_user_port(ds, i))
			जारी;

		/* During probe, this function will be called क्रम each slave
		 * device, जबतक not all of them have been allocated. That's
		 * ok, it करोesn't change what the maximum is, so ignore it.
		 */
		अगर (!dsa_to_port(ds, i)->slave)
			जारी;

		/* Pretend that we alपढ़ोy applied the setting, which we
		 * actually haven't (still haven't करोne all पूर्णांकegrity checks)
		 */
		अगर (i == port)
			slave_mtu = new_mtu;
		अन्यथा
			slave_mtu = dsa_to_port(ds, i)->slave->mtu;

		अगर (largest_mtu < slave_mtu)
			largest_mtu = slave_mtu;
	पूर्ण

	cpu_dp = dsa_to_port(ds, port)->cpu_dp;

	mtu_limit = min_t(पूर्णांक, master->max_mtu, dev->max_mtu);
	old_master_mtu = master->mtu;
	new_master_mtu = largest_mtu + cpu_dp->tag_ops->overhead;
	अगर (new_master_mtu > mtu_limit)
		वापस -दुस्फल;

	/* If the master MTU isn't over limit, there's no need to check the CPU
	 * MTU, since that surely isn't either.
	 */
	cpu_mtu = largest_mtu;

	/* Start applying stuff */
	अगर (new_master_mtu != old_master_mtu) अणु
		err = dev_set_mtu(master, new_master_mtu);
		अगर (err < 0)
			जाओ out_master_failed;

		/* We only need to propagate the MTU of the CPU port to
		 * upstream चयनes.
		 */
		err = dsa_port_mtu_change(cpu_dp, cpu_mtu, true);
		अगर (err)
			जाओ out_cpu_failed;
	पूर्ण

	err = dsa_port_mtu_change(dp, new_mtu, false);
	अगर (err)
		जाओ out_port_failed;

	dev->mtu = new_mtu;

	dsa_bridge_mtu_normalization(dp);

	वापस 0;

out_port_failed:
	अगर (new_master_mtu != old_master_mtu)
		dsa_port_mtu_change(cpu_dp, old_master_mtu -
				    cpu_dp->tag_ops->overhead,
				    true);
out_cpu_failed:
	अगर (new_master_mtu != old_master_mtu)
		dev_set_mtu(master, old_master_mtu);
out_master_failed:
	वापस err;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops dsa_slave_ethtool_ops = अणु
	.get_drvinfo		= dsa_slave_get_drvinfo,
	.get_regs_len		= dsa_slave_get_regs_len,
	.get_regs		= dsa_slave_get_regs,
	.nway_reset		= dsa_slave_nway_reset,
	.get_link		= ethtool_op_get_link,
	.get_eeprom_len		= dsa_slave_get_eeprom_len,
	.get_eeprom		= dsa_slave_get_eeprom,
	.set_eeprom		= dsa_slave_set_eeprom,
	.get_strings		= dsa_slave_get_strings,
	.get_ethtool_stats	= dsa_slave_get_ethtool_stats,
	.get_sset_count		= dsa_slave_get_sset_count,
	.set_wol		= dsa_slave_set_wol,
	.get_wol		= dsa_slave_get_wol,
	.set_eee		= dsa_slave_set_eee,
	.get_eee		= dsa_slave_get_eee,
	.get_link_ksettings	= dsa_slave_get_link_ksettings,
	.set_link_ksettings	= dsa_slave_set_link_ksettings,
	.get_छोड़ोparam		= dsa_slave_get_छोड़ोparam,
	.set_छोड़ोparam		= dsa_slave_set_छोड़ोparam,
	.get_rxnfc		= dsa_slave_get_rxnfc,
	.set_rxnfc		= dsa_slave_set_rxnfc,
	.get_ts_info		= dsa_slave_get_ts_info,
	.self_test		= dsa_slave_net_selftest,
पूर्ण;

/* legacy way, bypassing the bridge *****************************************/
अटल पूर्णांक dsa_legacy_fdb_add(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			      काष्ठा net_device *dev,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid,
			      u16 flags,
			      काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	वापस dsa_port_fdb_add(dp, addr, vid);
पूर्ण

अटल पूर्णांक dsa_legacy_fdb_del(काष्ठा ndmsg *ndm, काष्ठा nlattr *tb[],
			      काष्ठा net_device *dev,
			      स्थिर अचिन्हित अक्षर *addr, u16 vid)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	वापस dsa_port_fdb_del(dp, addr, vid);
पूर्ण

अटल काष्ठा devlink_port *dsa_slave_get_devlink_port(काष्ठा net_device *dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);

	वापस dp->ds->devlink ? &dp->devlink_port : शून्य;
पूर्ण

अटल व्योम dsa_slave_get_stats64(काष्ठा net_device *dev,
				  काष्ठा rtnl_link_stats64 *s)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	अगर (ds->ops->get_stats64)
		ds->ops->get_stats64(ds, dp->index, s);
	अन्यथा
		dev_get_tstats64(dev, s);
पूर्ण

अटल पूर्णांक dsa_slave_fill_क्रमward_path(काष्ठा net_device_path_ctx *ctx,
				       काष्ठा net_device_path *path)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(ctx->dev);
	काष्ठा dsa_port *cpu_dp = dp->cpu_dp;

	path->dev = ctx->dev;
	path->type = DEV_PATH_DSA;
	path->dsa.proto = cpu_dp->tag_ops->proto;
	path->dsa.port = dp->index;
	ctx->dev = cpu_dp->master;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops dsa_slave_netdev_ops = अणु
	.nकरो_खोलो	 	= dsa_slave_खोलो,
	.nकरो_stop		= dsa_slave_बंद,
	.nकरो_start_xmit		= dsa_slave_xmit,
	.nकरो_change_rx_flags	= dsa_slave_change_rx_flags,
	.nकरो_set_rx_mode	= dsa_slave_set_rx_mode,
	.nकरो_set_mac_address	= dsa_slave_set_mac_address,
	.nकरो_fdb_add		= dsa_legacy_fdb_add,
	.nकरो_fdb_del		= dsa_legacy_fdb_del,
	.nकरो_fdb_dump		= dsa_slave_fdb_dump,
	.nकरो_करो_ioctl		= dsa_slave_ioctl,
	.nकरो_get_अगरlink		= dsa_slave_get_अगरlink,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_netpoll_setup	= dsa_slave_netpoll_setup,
	.nकरो_netpoll_cleanup	= dsa_slave_netpoll_cleanup,
	.nकरो_poll_controller	= dsa_slave_poll_controller,
#पूर्ण_अगर
	.nकरो_get_phys_port_name	= dsa_slave_get_phys_port_name,
	.nकरो_setup_tc		= dsa_slave_setup_tc,
	.nकरो_get_stats64	= dsa_slave_get_stats64,
	.nकरो_get_port_parent_id	= dsa_slave_get_port_parent_id,
	.nकरो_vlan_rx_add_vid	= dsa_slave_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= dsa_slave_vlan_rx_समाप्त_vid,
	.nकरो_get_devlink_port	= dsa_slave_get_devlink_port,
	.nकरो_change_mtu		= dsa_slave_change_mtu,
	.nकरो_fill_क्रमward_path	= dsa_slave_fill_क्रमward_path,
पूर्ण;

अटल काष्ठा device_type dsa_type = अणु
	.name	= "dsa",
पूर्ण;

व्योम dsa_port_phylink_mac_change(काष्ठा dsa_चयन *ds, पूर्णांक port, bool up)
अणु
	स्थिर काष्ठा dsa_port *dp = dsa_to_port(ds, port);

	अगर (dp->pl)
		phylink_mac_change(dp->pl, up);
पूर्ण
EXPORT_SYMBOL_GPL(dsa_port_phylink_mac_change);

अटल व्योम dsa_slave_phylink_fixed_state(काष्ठा phylink_config *config,
					  काष्ठा phylink_link_state *state)
अणु
	काष्ठा dsa_port *dp = container_of(config, काष्ठा dsa_port, pl_config);
	काष्ठा dsa_चयन *ds = dp->ds;

	/* No need to check that this operation is valid, the callback would
	 * not be called अगर it was not.
	 */
	ds->ops->phylink_fixed_state(ds, dp->index, state);
पूर्ण

/* slave device setup *******************************************************/
अटल पूर्णांक dsa_slave_phy_connect(काष्ठा net_device *slave_dev, पूर्णांक addr)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(slave_dev);
	काष्ठा dsa_चयन *ds = dp->ds;

	slave_dev->phydev = mdiobus_get_phy(ds->slave_mii_bus, addr);
	अगर (!slave_dev->phydev) अणु
		netdev_err(slave_dev, "no phy at %d\n", addr);
		वापस -ENODEV;
	पूर्ण

	वापस phylink_connect_phy(dp->pl, slave_dev->phydev);
पूर्ण

अटल पूर्णांक dsa_slave_phy_setup(काष्ठा net_device *slave_dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(slave_dev);
	काष्ठा device_node *port_dn = dp->dn;
	काष्ठा dsa_चयन *ds = dp->ds;
	phy_पूर्णांकerface_t mode;
	u32 phy_flags = 0;
	पूर्णांक ret;

	ret = of_get_phy_mode(port_dn, &mode);
	अगर (ret)
		mode = PHY_INTERFACE_MODE_NA;

	dp->pl_config.dev = &slave_dev->dev;
	dp->pl_config.type = PHYLINK_NETDEV;

	/* The get_fixed_state callback takes precedence over polling the
	 * link GPIO in PHYLINK (see phylink_get_fixed_state).  Only set
	 * this अगर the चयन provides such a callback.
	 */
	अगर (ds->ops->phylink_fixed_state) अणु
		dp->pl_config.get_fixed_state = dsa_slave_phylink_fixed_state;
		dp->pl_config.poll_fixed_state = true;
	पूर्ण

	dp->pl = phylink_create(&dp->pl_config, of_fwnode_handle(port_dn), mode,
				&dsa_port_phylink_mac_ops);
	अगर (IS_ERR(dp->pl)) अणु
		netdev_err(slave_dev,
			   "error creating PHYLINK: %ld\n", PTR_ERR(dp->pl));
		वापस PTR_ERR(dp->pl);
	पूर्ण

	अगर (ds->ops->get_phy_flags)
		phy_flags = ds->ops->get_phy_flags(ds, dp->index);

	ret = phylink_of_phy_connect(dp->pl, port_dn, phy_flags);
	अगर (ret == -ENODEV && ds->slave_mii_bus) अणु
		/* We could not connect to a designated PHY or SFP, so try to
		 * use the चयन पूर्णांकernal MDIO bus instead
		 */
		ret = dsa_slave_phy_connect(slave_dev, dp->index);
		अगर (ret) अणु
			netdev_err(slave_dev,
				   "failed to connect to port %d: %d\n",
				   dp->index, ret);
			phylink_destroy(dp->pl);
			वापस ret;
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

व्योम dsa_slave_setup_tagger(काष्ठा net_device *slave)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(slave);
	काष्ठा dsa_slave_priv *p = netdev_priv(slave);
	स्थिर काष्ठा dsa_port *cpu_dp = dp->cpu_dp;
	काष्ठा net_device *master = cpu_dp->master;

	अगर (cpu_dp->tag_ops->tail_tag)
		slave->needed_tailroom = cpu_dp->tag_ops->overhead;
	अन्यथा
		slave->needed_headroom = cpu_dp->tag_ops->overhead;
	/* Try to save one extra पुनः_स्मृति later in the TX path (in the master)
	 * by also inheriting the master's needed headroom and tailroom.
	 * The 8021q driver also करोes this.
	 */
	slave->needed_headroom += master->needed_headroom;
	slave->needed_tailroom += master->needed_tailroom;

	p->xmit = cpu_dp->tag_ops->xmit;
पूर्ण

अटल काष्ठा lock_class_key dsa_slave_netdev_xmit_lock_key;
अटल व्योम dsa_slave_set_lockdep_class_one(काष्ठा net_device *dev,
					    काष्ठा netdev_queue *txq,
					    व्योम *_unused)
अणु
	lockdep_set_class(&txq->_xmit_lock,
			  &dsa_slave_netdev_xmit_lock_key);
पूर्ण

पूर्णांक dsa_slave_suspend(काष्ठा net_device *slave_dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(slave_dev);

	अगर (!netअगर_running(slave_dev))
		वापस 0;

	netअगर_device_detach(slave_dev);

	rtnl_lock();
	phylink_stop(dp->pl);
	rtnl_unlock();

	वापस 0;
पूर्ण

पूर्णांक dsa_slave_resume(काष्ठा net_device *slave_dev)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(slave_dev);

	अगर (!netअगर_running(slave_dev))
		वापस 0;

	netअगर_device_attach(slave_dev);

	rtnl_lock();
	phylink_start(dp->pl);
	rtnl_unlock();

	वापस 0;
पूर्ण

पूर्णांक dsa_slave_create(काष्ठा dsa_port *port)
अणु
	स्थिर काष्ठा dsa_port *cpu_dp = port->cpu_dp;
	काष्ठा net_device *master = cpu_dp->master;
	काष्ठा dsa_चयन *ds = port->ds;
	स्थिर अक्षर *name = port->name;
	काष्ठा net_device *slave_dev;
	काष्ठा dsa_slave_priv *p;
	पूर्णांक ret;

	अगर (!ds->num_tx_queues)
		ds->num_tx_queues = 1;

	slave_dev = alloc_netdev_mqs(माप(काष्ठा dsa_slave_priv), name,
				     NET_NAME_UNKNOWN, ether_setup,
				     ds->num_tx_queues, 1);
	अगर (slave_dev == शून्य)
		वापस -ENOMEM;

	slave_dev->features = master->vlan_features | NETIF_F_HW_TC;
	अगर (ds->ops->port_vlan_add && ds->ops->port_vlan_del)
		slave_dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER;
	slave_dev->hw_features |= NETIF_F_HW_TC;
	slave_dev->features |= NETIF_F_LLTX;
	slave_dev->ethtool_ops = &dsa_slave_ethtool_ops;
	अगर (!is_zero_ether_addr(port->mac))
		ether_addr_copy(slave_dev->dev_addr, port->mac);
	अन्यथा
		eth_hw_addr_inherit(slave_dev, master);
	slave_dev->priv_flags |= IFF_NO_QUEUE;
	slave_dev->netdev_ops = &dsa_slave_netdev_ops;
	अगर (ds->ops->port_max_mtu)
		slave_dev->max_mtu = ds->ops->port_max_mtu(ds, port->index);
	SET_NETDEV_DEVTYPE(slave_dev, &dsa_type);

	netdev_क्रम_each_tx_queue(slave_dev, dsa_slave_set_lockdep_class_one,
				 शून्य);

	SET_NETDEV_DEV(slave_dev, port->ds->dev);
	slave_dev->dev.of_node = port->dn;
	slave_dev->vlan_features = master->vlan_features;

	p = netdev_priv(slave_dev);
	slave_dev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
	अगर (!slave_dev->tstats) अणु
		मुक्त_netdev(slave_dev);
		वापस -ENOMEM;
	पूर्ण

	ret = gro_cells_init(&p->gcells, slave_dev);
	अगर (ret)
		जाओ out_मुक्त;

	p->dp = port;
	INIT_LIST_HEAD(&p->mall_tc_list);
	port->slave = slave_dev;
	dsa_slave_setup_tagger(slave_dev);

	rtnl_lock();
	ret = dsa_slave_change_mtu(slave_dev, ETH_DATA_LEN);
	rtnl_unlock();
	अगर (ret && ret != -EOPNOTSUPP)
		dev_warn(ds->dev, "nonfatal error %d setting MTU to %d on port %d\n",
			 ret, ETH_DATA_LEN, port->index);

	netअगर_carrier_off(slave_dev);

	ret = dsa_slave_phy_setup(slave_dev);
	अगर (ret) अणु
		netdev_err(slave_dev,
			   "error %d setting up PHY for tree %d, switch %d, port %d\n",
			   ret, ds->dst->index, ds->index, port->index);
		जाओ out_gcells;
	पूर्ण

	rtnl_lock();

	ret = रेजिस्टर_netdevice(slave_dev);
	अगर (ret) अणु
		netdev_err(master, "error %d registering interface %s\n",
			   ret, slave_dev->name);
		rtnl_unlock();
		जाओ out_phy;
	पूर्ण

	ret = netdev_upper_dev_link(master, slave_dev, शून्य);

	rtnl_unlock();

	अगर (ret)
		जाओ out_unरेजिस्टर;

	वापस 0;

out_unरेजिस्टर:
	unरेजिस्टर_netdev(slave_dev);
out_phy:
	rtnl_lock();
	phylink_disconnect_phy(p->dp->pl);
	rtnl_unlock();
	phylink_destroy(p->dp->pl);
out_gcells:
	gro_cells_destroy(&p->gcells);
out_मुक्त:
	मुक्त_percpu(slave_dev->tstats);
	मुक्त_netdev(slave_dev);
	port->slave = शून्य;
	वापस ret;
पूर्ण

व्योम dsa_slave_destroy(काष्ठा net_device *slave_dev)
अणु
	काष्ठा net_device *master = dsa_slave_to_master(slave_dev);
	काष्ठा dsa_port *dp = dsa_slave_to_port(slave_dev);
	काष्ठा dsa_slave_priv *p = netdev_priv(slave_dev);

	netअगर_carrier_off(slave_dev);
	rtnl_lock();
	netdev_upper_dev_unlink(master, slave_dev);
	unरेजिस्टर_netdevice(slave_dev);
	phylink_disconnect_phy(dp->pl);
	rtnl_unlock();

	phylink_destroy(dp->pl);
	gro_cells_destroy(&p->gcells);
	मुक्त_percpu(slave_dev->tstats);
	मुक्त_netdev(slave_dev);
पूर्ण

bool dsa_slave_dev_check(स्थिर काष्ठा net_device *dev)
अणु
	वापस dev->netdev_ops == &dsa_slave_netdev_ops;
पूर्ण
EXPORT_SYMBOL_GPL(dsa_slave_dev_check);

अटल पूर्णांक dsa_slave_changeupper(काष्ठा net_device *dev,
				 काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा netlink_ext_ack *extack;
	पूर्णांक err = NOTIFY_DONE;

	extack = netdev_notअगरier_info_to_extack(&info->info);

	अगर (netअगर_is_bridge_master(info->upper_dev)) अणु
		अगर (info->linking) अणु
			err = dsa_port_bridge_join(dp, info->upper_dev, extack);
			अगर (!err)
				dsa_bridge_mtu_normalization(dp);
			err = notअगरier_from_त्रुटि_सं(err);
		पूर्ण अन्यथा अणु
			dsa_port_bridge_leave(dp, info->upper_dev);
			err = NOTIFY_OK;
		पूर्ण
	पूर्ण अन्यथा अगर (netअगर_is_lag_master(info->upper_dev)) अणु
		अगर (info->linking) अणु
			err = dsa_port_lag_join(dp, info->upper_dev,
						info->upper_info, extack);
			अगर (err == -EOPNOTSUPP) अणु
				NL_SET_ERR_MSG_MOD(info->info.extack,
						   "Offloading not supported");
				err = 0;
			पूर्ण
			err = notअगरier_from_त्रुटि_सं(err);
		पूर्ण अन्यथा अणु
			dsa_port_lag_leave(dp, info->upper_dev);
			err = NOTIFY_OK;
		पूर्ण
	पूर्ण अन्यथा अगर (is_hsr_master(info->upper_dev)) अणु
		अगर (info->linking) अणु
			err = dsa_port_hsr_join(dp, info->upper_dev);
			अगर (err == -EOPNOTSUPP) अणु
				NL_SET_ERR_MSG_MOD(info->info.extack,
						   "Offloading not supported");
				err = 0;
			पूर्ण
			err = notअगरier_from_त्रुटि_सं(err);
		पूर्ण अन्यथा अणु
			dsa_port_hsr_leave(dp, info->upper_dev);
			err = NOTIFY_OK;
		पूर्ण
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
dsa_slave_lag_changeupper(काष्ठा net_device *dev,
			  काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा net_device *lower;
	काष्ठा list_head *iter;
	पूर्णांक err = NOTIFY_DONE;
	काष्ठा dsa_port *dp;

	netdev_क्रम_each_lower_dev(dev, lower, iter) अणु
		अगर (!dsa_slave_dev_check(lower))
			जारी;

		dp = dsa_slave_to_port(lower);
		अगर (!dp->lag_dev)
			/* Software LAG */
			जारी;

		err = dsa_slave_changeupper(lower, info);
		अगर (notअगरier_to_त्रुटि_सं(err))
			अवरोध;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक
dsa_prevent_bridging_8021q_upper(काष्ठा net_device *dev,
				 काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा netlink_ext_ack *ext_ack;
	काष्ठा net_device *slave;
	काष्ठा dsa_port *dp;

	ext_ack = netdev_notअगरier_info_to_extack(&info->info);

	अगर (!is_vlan_dev(dev))
		वापस NOTIFY_DONE;

	slave = vlan_dev_real_dev(dev);
	अगर (!dsa_slave_dev_check(slave))
		वापस NOTIFY_DONE;

	dp = dsa_slave_to_port(slave);
	अगर (!dp->bridge_dev)
		वापस NOTIFY_DONE;

	/* Deny enslaving a VLAN device पूर्णांकo a VLAN-aware bridge */
	अगर (br_vlan_enabled(dp->bridge_dev) &&
	    netअगर_is_bridge_master(info->upper_dev) && info->linking) अणु
		NL_SET_ERR_MSG_MOD(ext_ack,
				   "Cannot enslave VLAN device into VLAN aware bridge");
		वापस notअगरier_from_त्रुटि_सं(-EINVAL);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक
dsa_slave_check_8021q_upper(काष्ठा net_device *dev,
			    काष्ठा netdev_notअगरier_changeupper_info *info)
अणु
	काष्ठा dsa_port *dp = dsa_slave_to_port(dev);
	काष्ठा net_device *br = dp->bridge_dev;
	काष्ठा bridge_vlan_info br_info;
	काष्ठा netlink_ext_ack *extack;
	पूर्णांक err = NOTIFY_DONE;
	u16 vid;

	अगर (!br || !br_vlan_enabled(br))
		वापस NOTIFY_DONE;

	extack = netdev_notअगरier_info_to_extack(&info->info);
	vid = vlan_dev_vlan_id(info->upper_dev);

	/* br_vlan_get_info() वापसs -EINVAL or -ENOENT अगर the
	 * device, respectively the VID is not found, वापसing
	 * 0 means success, which is a failure क्रम us here.
	 */
	err = br_vlan_get_info(br, vid, &br_info);
	अगर (err == 0) अणु
		NL_SET_ERR_MSG_MOD(extack,
				   "This VLAN is already configured by the bridge");
		वापस notअगरier_from_त्रुटि_सं(-EBUSY);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल पूर्णांक dsa_slave_netdevice_event(काष्ठा notअगरier_block *nb,
				     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);

	चयन (event) अणु
	हाल NETDEV_PRECHANGEUPPER: अणु
		काष्ठा netdev_notअगरier_changeupper_info *info = ptr;
		काष्ठा dsa_चयन *ds;
		काष्ठा dsa_port *dp;
		पूर्णांक err;

		अगर (!dsa_slave_dev_check(dev))
			वापस dsa_prevent_bridging_8021q_upper(dev, ptr);

		dp = dsa_slave_to_port(dev);
		ds = dp->ds;

		अगर (ds->ops->port_prechangeupper) अणु
			err = ds->ops->port_prechangeupper(ds, dp->index, info);
			अगर (err)
				वापस notअगरier_from_त्रुटि_सं(err);
		पूर्ण

		अगर (is_vlan_dev(info->upper_dev))
			वापस dsa_slave_check_8021q_upper(dev, ptr);
		अवरोध;
	पूर्ण
	हाल NETDEV_CHANGEUPPER:
		अगर (dsa_slave_dev_check(dev))
			वापस dsa_slave_changeupper(dev, ptr);

		अगर (netअगर_is_lag_master(dev))
			वापस dsa_slave_lag_changeupper(dev, ptr);

		अवरोध;
	हाल NETDEV_CHANGELOWERSTATE: अणु
		काष्ठा netdev_notअगरier_changelowerstate_info *info = ptr;
		काष्ठा dsa_port *dp;
		पूर्णांक err;

		अगर (!dsa_slave_dev_check(dev))
			अवरोध;

		dp = dsa_slave_to_port(dev);

		err = dsa_port_lag_change(dp, info->lower_state_info);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण
	हाल NETDEV_GOING_DOWN: अणु
		काष्ठा dsa_port *dp, *cpu_dp;
		काष्ठा dsa_चयन_tree *dst;
		LIST_HEAD(बंद_list);

		अगर (!netdev_uses_dsa(dev))
			वापस NOTIFY_DONE;

		cpu_dp = dev->dsa_ptr;
		dst = cpu_dp->ds->dst;

		list_क्रम_each_entry(dp, &dst->ports, list) अणु
			अगर (!dsa_is_user_port(dp->ds, dp->index))
				जारी;

			list_add(&dp->slave->बंद_list, &बंद_list);
		पूर्ण

		dev_बंद_many(&बंद_list, true);

		वापस NOTIFY_OK;
	पूर्ण
	शेष:
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल व्योम
dsa_fdb_offload_notअगरy(काष्ठा dsa_चयनdev_event_work *चयनdev_work)
अणु
	काष्ठा dsa_चयन *ds = चयनdev_work->ds;
	काष्ठा चयनdev_notअगरier_fdb_info info;
	काष्ठा dsa_port *dp;

	अगर (!dsa_is_user_port(ds, चयनdev_work->port))
		वापस;

	info.addr = चयनdev_work->addr;
	info.vid = चयनdev_work->vid;
	info.offloaded = true;
	dp = dsa_to_port(ds, चयनdev_work->port);
	call_चयनdev_notअगरiers(SWITCHDEV_FDB_OFFLOADED,
				 dp->slave, &info.info, शून्य);
पूर्ण

अटल व्योम dsa_slave_चयनdev_event_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा dsa_चयनdev_event_work *चयनdev_work =
		container_of(work, काष्ठा dsa_चयनdev_event_work, work);
	काष्ठा dsa_चयन *ds = चयनdev_work->ds;
	काष्ठा dsa_port *dp;
	पूर्णांक err;

	dp = dsa_to_port(ds, चयनdev_work->port);

	rtnl_lock();
	चयन (चयनdev_work->event) अणु
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
		err = dsa_port_fdb_add(dp, चयनdev_work->addr,
				       चयनdev_work->vid);
		अगर (err) अणु
			dev_err(ds->dev,
				"port %d failed to add %pM vid %d to fdb: %d\n",
				dp->index, चयनdev_work->addr,
				चयनdev_work->vid, err);
			अवरोध;
		पूर्ण
		dsa_fdb_offload_notअगरy(चयनdev_work);
		अवरोध;

	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		err = dsa_port_fdb_del(dp, चयनdev_work->addr,
				       चयनdev_work->vid);
		अगर (err) अणु
			dev_err(ds->dev,
				"port %d failed to delete %pM vid %d from fdb: %d\n",
				dp->index, चयनdev_work->addr,
				चयनdev_work->vid, err);
		पूर्ण

		अवरोध;
	पूर्ण
	rtnl_unlock();

	kमुक्त(चयनdev_work);
	अगर (dsa_is_user_port(ds, dp->index))
		dev_put(dp->slave);
पूर्ण

अटल पूर्णांक dsa_lower_dev_walk(काष्ठा net_device *lower_dev,
			      काष्ठा netdev_nested_priv *priv)
अणु
	अगर (dsa_slave_dev_check(lower_dev)) अणु
		priv->data = (व्योम *)netdev_priv(lower_dev);
		वापस 1;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा dsa_slave_priv *dsa_slave_dev_lower_find(काष्ठा net_device *dev)
अणु
	काष्ठा netdev_nested_priv priv = अणु
		.data = शून्य,
	पूर्ण;

	netdev_walk_all_lower_dev_rcu(dev, dsa_lower_dev_walk, &priv);

	वापस (काष्ठा dsa_slave_priv *)priv.data;
पूर्ण

/* Called under rcu_पढ़ो_lock() */
अटल पूर्णांक dsa_slave_चयनdev_event(काष्ठा notअगरier_block *unused,
				     अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	स्थिर काष्ठा चयनdev_notअगरier_fdb_info *fdb_info;
	काष्ठा dsa_चयनdev_event_work *चयनdev_work;
	काष्ठा dsa_port *dp;
	पूर्णांक err;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_ATTR_SET:
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     dsa_slave_dev_check,
						     dsa_slave_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_FDB_ADD_TO_DEVICE:
	हाल SWITCHDEV_FDB_DEL_TO_DEVICE:
		fdb_info = ptr;

		अगर (dsa_slave_dev_check(dev)) अणु
			अगर (!fdb_info->added_by_user || fdb_info->is_local)
				वापस NOTIFY_OK;

			dp = dsa_slave_to_port(dev);
		पूर्ण अन्यथा अणु
			/* Snoop addresses learnt on क्रमeign पूर्णांकerfaces
			 * bridged with us, क्रम चयनes that करोn't
			 * स्वतःmatically learn SA from CPU-injected traffic
			 */
			काष्ठा net_device *br_dev;
			काष्ठा dsa_slave_priv *p;

			br_dev = netdev_master_upper_dev_get_rcu(dev);
			अगर (!br_dev)
				वापस NOTIFY_DONE;

			अगर (!netअगर_is_bridge_master(br_dev))
				वापस NOTIFY_DONE;

			p = dsa_slave_dev_lower_find(br_dev);
			अगर (!p)
				वापस NOTIFY_DONE;

			dp = p->dp->cpu_dp;

			अगर (!dp->ds->assisted_learning_on_cpu_port)
				वापस NOTIFY_DONE;

			/* When the bridge learns an address on an offloaded
			 * LAG we करोn't want to send traffic to the CPU, the
			 * other ports bridged with the LAG should be able to
			 * स्वतःnomously क्रमward towards it.
			 */
			अगर (dsa_tree_offloads_bridge_port(dp->ds->dst, dev))
				वापस NOTIFY_DONE;
		पूर्ण

		अगर (!dp->ds->ops->port_fdb_add || !dp->ds->ops->port_fdb_del)
			वापस NOTIFY_DONE;

		चयनdev_work = kzalloc(माप(*चयनdev_work), GFP_ATOMIC);
		अगर (!चयनdev_work)
			वापस NOTIFY_BAD;

		INIT_WORK(&चयनdev_work->work,
			  dsa_slave_चयनdev_event_work);
		चयनdev_work->ds = dp->ds;
		चयनdev_work->port = dp->index;
		चयनdev_work->event = event;

		ether_addr_copy(चयनdev_work->addr,
				fdb_info->addr);
		चयनdev_work->vid = fdb_info->vid;

		/* Hold a reference on the slave क्रम dsa_fdb_offload_notअगरy */
		अगर (dsa_is_user_port(dp->ds, dp->index))
			dev_hold(dev);
		dsa_schedule_work(&चयनdev_work->work);
		अवरोध;
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक dsa_slave_चयनdev_blocking_event(काष्ठा notअगरier_block *unused,
					      अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *dev = चयनdev_notअगरier_info_to_dev(ptr);
	पूर्णांक err;

	चयन (event) अणु
	हाल SWITCHDEV_PORT_OBJ_ADD:
		err = चयनdev_handle_port_obj_add(dev, ptr,
						    dsa_slave_dev_check,
						    dsa_slave_port_obj_add);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_OBJ_DEL:
		err = चयनdev_handle_port_obj_del(dev, ptr,
						    dsa_slave_dev_check,
						    dsa_slave_port_obj_del);
		वापस notअगरier_from_त्रुटि_सं(err);
	हाल SWITCHDEV_PORT_ATTR_SET:
		err = चयनdev_handle_port_attr_set(dev, ptr,
						     dsa_slave_dev_check,
						     dsa_slave_port_attr_set);
		वापस notअगरier_from_त्रुटि_सं(err);
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block dsa_slave_nb __पढ़ो_mostly = अणु
	.notअगरier_call  = dsa_slave_netdevice_event,
पूर्ण;

काष्ठा notअगरier_block dsa_slave_चयनdev_notअगरier = अणु
	.notअगरier_call = dsa_slave_चयनdev_event,
पूर्ण;

काष्ठा notअगरier_block dsa_slave_चयनdev_blocking_notअगरier = अणु
	.notअगरier_call = dsa_slave_चयनdev_blocking_event,
पूर्ण;

पूर्णांक dsa_slave_रेजिस्टर_notअगरier(व्योम)
अणु
	काष्ठा notअगरier_block *nb;
	पूर्णांक err;

	err = रेजिस्टर_netdevice_notअगरier(&dsa_slave_nb);
	अगर (err)
		वापस err;

	err = रेजिस्टर_चयनdev_notअगरier(&dsa_slave_चयनdev_notअगरier);
	अगर (err)
		जाओ err_चयनdev_nb;

	nb = &dsa_slave_चयनdev_blocking_notअगरier;
	err = रेजिस्टर_चयनdev_blocking_notअगरier(nb);
	अगर (err)
		जाओ err_चयनdev_blocking_nb;

	वापस 0;

err_चयनdev_blocking_nb:
	unरेजिस्टर_चयनdev_notअगरier(&dsa_slave_चयनdev_notअगरier);
err_चयनdev_nb:
	unरेजिस्टर_netdevice_notअगरier(&dsa_slave_nb);
	वापस err;
पूर्ण

व्योम dsa_slave_unरेजिस्टर_notअगरier(व्योम)
अणु
	काष्ठा notअगरier_block *nb;
	पूर्णांक err;

	nb = &dsa_slave_चयनdev_blocking_notअगरier;
	err = unरेजिस्टर_चयनdev_blocking_notअगरier(nb);
	अगर (err)
		pr_err("DSA: failed to unregister switchdev blocking notifier (%d)\n", err);

	err = unरेजिस्टर_चयनdev_notअगरier(&dsa_slave_चयनdev_notअगरier);
	अगर (err)
		pr_err("DSA: failed to unregister switchdev notifier (%d)\n", err);

	err = unरेजिस्टर_netdevice_notअगरier(&dsa_slave_nb);
	अगर (err)
		pr_err("DSA: failed to unregister slave notifier (%d)\n", err);
पूर्ण
