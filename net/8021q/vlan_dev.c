<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* -*- linux-c -*-
 * INET		802.1Q VLAN
 *		Ethernet-type device handling.
 *
 * Authors:	Ben Greear <greearb@candelatech.com>
 *              Please send support related email to: netdev@vger.kernel.org
 *              VLAN Home Page: http://www.candelatech.com/~greear/vlan.hपंचांगl
 *
 * Fixes:       Mar 22 2001: Martin Bokaemper <mbokaemper@unispherenetworks.com>
 *                - reset skb->pkt_type on incoming packets when MAC was changed
 *                - see that changed MAC is saddr क्रम outgoing packets
 *              Oct 20, 2001:  Ard van Breeman:
 *                - Fix MC-list, finally.
 *                - Flush MC-list on VLAN destroy.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/net_tstamp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/phy.h>
#समावेश <net/arp.h>

#समावेश "vlan.h"
#समावेश "vlanproc.h"
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/netpoll.h>

/*
 *	Create the VLAN header क्रम an arbitrary protocol layer
 *
 *	saddr=शून्य	means use device source address
 *	daddr=शून्य	means leave destination address (eg unresolved arp)
 *
 *  This is called when the SKB is moving करोwn the stack towards the
 *  physical devices.
 */
अटल पूर्णांक vlan_dev_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				अचिन्हित लघु type,
				स्थिर व्योम *daddr, स्थिर व्योम *saddr,
				अचिन्हित पूर्णांक len)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा vlan_hdr *vhdr;
	अचिन्हित पूर्णांक vhdrlen = 0;
	u16 vlan_tci = 0;
	पूर्णांक rc;

	अगर (!(vlan->flags & VLAN_FLAG_REORDER_HDR)) अणु
		vhdr = skb_push(skb, VLAN_HLEN);

		vlan_tci = vlan->vlan_id;
		vlan_tci |= vlan_dev_get_egress_qos_mask(dev, skb->priority);
		vhdr->h_vlan_TCI = htons(vlan_tci);

		/*
		 *  Set the protocol type. For a packet of type ETH_P_802_3/2 we
		 *  put the length in here instead.
		 */
		अगर (type != ETH_P_802_3 && type != ETH_P_802_2)
			vhdr->h_vlan_encapsulated_proto = htons(type);
		अन्यथा
			vhdr->h_vlan_encapsulated_proto = htons(len);

		skb->protocol = vlan->vlan_proto;
		type = ntohs(vlan->vlan_proto);
		vhdrlen = VLAN_HLEN;
	पूर्ण

	/* Beक्रमe delegating work to the lower layer, enter our MAC-address */
	अगर (saddr == शून्य)
		saddr = dev->dev_addr;

	/* Now make the underlying real hard header */
	dev = vlan->real_dev;
	rc = dev_hard_header(skb, dev, type, daddr, saddr, len + vhdrlen);
	अगर (rc > 0)
		rc += vhdrlen;
	वापस rc;
पूर्ण

अटल अंतरभूत netdev_tx_t vlan_netpoll_send_skb(काष्ठा vlan_dev_priv *vlan, काष्ठा sk_buff *skb)
अणु
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	वापस netpoll_send_skb(vlan->netpoll, skb);
#अन्यथा
	BUG();
	वापस NETDEV_TX_OK;
#पूर्ण_अगर
पूर्ण

अटल netdev_tx_t vlan_dev_hard_start_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *dev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा vlan_ethhdr *veth = (काष्ठा vlan_ethhdr *)(skb->data);
	अचिन्हित पूर्णांक len;
	पूर्णांक ret;

	/* Handle non-VLAN frames अगर they are sent to us, क्रम example by DHCP.
	 *
	 * NOTE: THIS ASSUMES DIX ETHERNET, SPECIFICALLY NOT SUPPORTING
	 * OTHER THINGS LIKE FDDI/TokenRing/802.3 SNAPs...
	 */
	अगर (veth->h_vlan_proto != vlan->vlan_proto ||
	    vlan->flags & VLAN_FLAG_REORDER_HDR) अणु
		u16 vlan_tci;
		vlan_tci = vlan->vlan_id;
		vlan_tci |= vlan_dev_get_egress_qos_mask(dev, skb->priority);
		__vlan_hwaccel_put_tag(skb, vlan->vlan_proto, vlan_tci);
	पूर्ण

	skb->dev = vlan->real_dev;
	len = skb->len;
	अगर (unlikely(netpoll_tx_running(dev)))
		वापस vlan_netpoll_send_skb(vlan, skb);

	ret = dev_queue_xmit(skb);

	अगर (likely(ret == NET_XMIT_SUCCESS || ret == NET_XMIT_CN)) अणु
		काष्ठा vlan_pcpu_stats *stats;

		stats = this_cpu_ptr(vlan->vlan_pcpu_stats);
		u64_stats_update_begin(&stats->syncp);
		stats->tx_packets++;
		stats->tx_bytes += len;
		u64_stats_update_end(&stats->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(vlan->vlan_pcpu_stats->tx_dropped);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक vlan_dev_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	अचिन्हित पूर्णांक max_mtu = real_dev->mtu;

	अगर (netअगर_reduces_vlan_mtu(real_dev))
		max_mtu -= VLAN_HLEN;
	अगर (max_mtu < new_mtu)
		वापस -दुस्फल;

	dev->mtu = new_mtu;

	वापस 0;
पूर्ण

व्योम vlan_dev_set_ingress_priority(स्थिर काष्ठा net_device *dev,
				   u32 skb_prio, u16 vlan_prio)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);

	अगर (vlan->ingress_priority_map[vlan_prio & 0x7] && !skb_prio)
		vlan->nr_ingress_mappings--;
	अन्यथा अगर (!vlan->ingress_priority_map[vlan_prio & 0x7] && skb_prio)
		vlan->nr_ingress_mappings++;

	vlan->ingress_priority_map[vlan_prio & 0x7] = skb_prio;
पूर्ण

पूर्णांक vlan_dev_set_egress_priority(स्थिर काष्ठा net_device *dev,
				 u32 skb_prio, u16 vlan_prio)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा vlan_priority_tci_mapping *mp = शून्य;
	काष्ठा vlan_priority_tci_mapping *np;
	u32 vlan_qos = (vlan_prio << VLAN_PRIO_SHIFT) & VLAN_PRIO_MASK;

	/* See अगर a priority mapping exists.. */
	mp = vlan->egress_priority_map[skb_prio & 0xF];
	जबतक (mp) अणु
		अगर (mp->priority == skb_prio) अणु
			अगर (mp->vlan_qos && !vlan_qos)
				vlan->nr_egress_mappings--;
			अन्यथा अगर (!mp->vlan_qos && vlan_qos)
				vlan->nr_egress_mappings++;
			mp->vlan_qos = vlan_qos;
			वापस 0;
		पूर्ण
		mp = mp->next;
	पूर्ण

	/* Create a new mapping then. */
	mp = vlan->egress_priority_map[skb_prio & 0xF];
	np = kदो_स्मृति(माप(काष्ठा vlan_priority_tci_mapping), GFP_KERNEL);
	अगर (!np)
		वापस -ENOBUFS;

	np->next = mp;
	np->priority = skb_prio;
	np->vlan_qos = vlan_qos;
	/* Beक्रमe inserting this element in hash table, make sure all its fields
	 * are committed to memory.
	 * coupled with smp_rmb() in vlan_dev_get_egress_qos_mask()
	 */
	smp_wmb();
	vlan->egress_priority_map[skb_prio & 0xF] = np;
	अगर (vlan_qos)
		vlan->nr_egress_mappings++;
	वापस 0;
पूर्ण

/* Flags are defined in the vlan_flags क्रमागत in
 * include/uapi/linux/अगर_vlan.h file.
 */
पूर्णांक vlan_dev_change_flags(स्थिर काष्ठा net_device *dev, u32 flags, u32 mask)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	u32 old_flags = vlan->flags;

	अगर (mask & ~(VLAN_FLAG_REORDER_HDR | VLAN_FLAG_GVRP |
		     VLAN_FLAG_LOOSE_BINDING | VLAN_FLAG_MVRP |
		     VLAN_FLAG_BRIDGE_BINDING))
		वापस -EINVAL;

	vlan->flags = (old_flags & ~mask) | (flags & mask);

	अगर (netअगर_running(dev) && (vlan->flags ^ old_flags) & VLAN_FLAG_GVRP) अणु
		अगर (vlan->flags & VLAN_FLAG_GVRP)
			vlan_gvrp_request_join(dev);
		अन्यथा
			vlan_gvrp_request_leave(dev);
	पूर्ण

	अगर (netअगर_running(dev) && (vlan->flags ^ old_flags) & VLAN_FLAG_MVRP) अणु
		अगर (vlan->flags & VLAN_FLAG_MVRP)
			vlan_mvrp_request_join(dev);
		अन्यथा
			vlan_mvrp_request_leave(dev);
	पूर्ण
	वापस 0;
पूर्ण

व्योम vlan_dev_get_realdev_name(स्थिर काष्ठा net_device *dev, अक्षर *result)
अणु
	म_नकलन(result, vlan_dev_priv(dev)->real_dev->name, 23);
पूर्ण

bool vlan_dev_inherit_address(काष्ठा net_device *dev,
			      काष्ठा net_device *real_dev)
अणु
	अगर (dev->addr_assign_type != NET_ADDR_STOLEN)
		वापस false;

	ether_addr_copy(dev->dev_addr, real_dev->dev_addr);
	call_netdevice_notअगरiers(NETDEV_CHANGEADDR, dev);
	वापस true;
पूर्ण

अटल पूर्णांक vlan_dev_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा net_device *real_dev = vlan->real_dev;
	पूर्णांक err;

	अगर (!(real_dev->flags & IFF_UP) &&
	    !(vlan->flags & VLAN_FLAG_LOOSE_BINDING))
		वापस -ENETDOWN;

	अगर (!ether_addr_equal(dev->dev_addr, real_dev->dev_addr) &&
	    !vlan_dev_inherit_address(dev, real_dev)) अणु
		err = dev_uc_add(real_dev, dev->dev_addr);
		अगर (err < 0)
			जाओ out;
	पूर्ण

	अगर (dev->flags & IFF_ALLMULTI) अणु
		err = dev_set_allmulti(real_dev, 1);
		अगर (err < 0)
			जाओ del_unicast;
	पूर्ण
	अगर (dev->flags & IFF_PROMISC) अणु
		err = dev_set_promiscuity(real_dev, 1);
		अगर (err < 0)
			जाओ clear_allmulti;
	पूर्ण

	ether_addr_copy(vlan->real_dev_addr, real_dev->dev_addr);

	अगर (vlan->flags & VLAN_FLAG_GVRP)
		vlan_gvrp_request_join(dev);

	अगर (vlan->flags & VLAN_FLAG_MVRP)
		vlan_mvrp_request_join(dev);

	अगर (netअगर_carrier_ok(real_dev) &&
	    !(vlan->flags & VLAN_FLAG_BRIDGE_BINDING))
		netअगर_carrier_on(dev);
	वापस 0;

clear_allmulti:
	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(real_dev, -1);
del_unicast:
	अगर (!ether_addr_equal(dev->dev_addr, real_dev->dev_addr))
		dev_uc_del(real_dev, dev->dev_addr);
out:
	netअगर_carrier_off(dev);
	वापस err;
पूर्ण

अटल पूर्णांक vlan_dev_stop(काष्ठा net_device *dev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा net_device *real_dev = vlan->real_dev;

	dev_mc_unsync(real_dev, dev);
	dev_uc_unsync(real_dev, dev);
	अगर (dev->flags & IFF_ALLMULTI)
		dev_set_allmulti(real_dev, -1);
	अगर (dev->flags & IFF_PROMISC)
		dev_set_promiscuity(real_dev, -1);

	अगर (!ether_addr_equal(dev->dev_addr, real_dev->dev_addr))
		dev_uc_del(real_dev, dev->dev_addr);

	अगर (!(vlan->flags & VLAN_FLAG_BRIDGE_BINDING))
		netअगर_carrier_off(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक vlan_dev_set_mac_address(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	काष्ठा sockaddr *addr = p;
	पूर्णांक err;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (!(dev->flags & IFF_UP))
		जाओ out;

	अगर (!ether_addr_equal(addr->sa_data, real_dev->dev_addr)) अणु
		err = dev_uc_add(real_dev, addr->sa_data);
		अगर (err < 0)
			वापस err;
	पूर्ण

	अगर (!ether_addr_equal(dev->dev_addr, real_dev->dev_addr))
		dev_uc_del(real_dev, dev->dev_addr);

out:
	ether_addr_copy(dev->dev_addr, addr->sa_data);
	वापस 0;
पूर्ण

अटल पूर्णांक vlan_dev_ioctl(काष्ठा net_device *dev, काष्ठा अगरreq *अगरr, पूर्णांक cmd)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	काष्ठा अगरreq अगरrr;
	पूर्णांक err = -EOPNOTSUPP;

	म_नकलन(अगरrr.अगरr_name, real_dev->name, IFNAMSIZ);
	अगरrr.अगरr_अगरru = अगरr->अगरr_अगरru;

	चयन (cmd) अणु
	हाल SIOCSHWTSTAMP:
		अगर (!net_eq(dev_net(dev), &init_net))
			अवरोध;
		fallthrough;
	हाल SIOCGMIIPHY:
	हाल SIOCGMIIREG:
	हाल SIOCSMIIREG:
	हाल SIOCGHWTSTAMP:
		अगर (netअगर_device_present(real_dev) && ops->nकरो_करो_ioctl)
			err = ops->nकरो_करो_ioctl(real_dev, &अगरrr, cmd);
		अवरोध;
	पूर्ण

	अगर (!err)
		अगरr->अगरr_अगरru = अगरrr.अगरr_अगरru;

	वापस err;
पूर्ण

अटल पूर्णांक vlan_dev_neigh_setup(काष्ठा net_device *dev, काष्ठा neigh_parms *pa)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	पूर्णांक err = 0;

	अगर (netअगर_device_present(real_dev) && ops->nकरो_neigh_setup)
		err = ops->nकरो_neigh_setup(real_dev, pa);

	वापस err;
पूर्ण

#अगर IS_ENABLED(CONFIG_FCOE)
अटल पूर्णांक vlan_dev_fcoe_ddp_setup(काष्ठा net_device *dev, u16 xid,
				   काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	पूर्णांक rc = 0;

	अगर (ops->nकरो_fcoe_ddp_setup)
		rc = ops->nकरो_fcoe_ddp_setup(real_dev, xid, sgl, sgc);

	वापस rc;
पूर्ण

अटल पूर्णांक vlan_dev_fcoe_ddp_करोne(काष्ठा net_device *dev, u16 xid)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	पूर्णांक len = 0;

	अगर (ops->nकरो_fcoe_ddp_करोne)
		len = ops->nकरो_fcoe_ddp_करोne(real_dev, xid);

	वापस len;
पूर्ण

अटल पूर्णांक vlan_dev_fcoe_enable(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	पूर्णांक rc = -EINVAL;

	अगर (ops->nकरो_fcoe_enable)
		rc = ops->nकरो_fcoe_enable(real_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक vlan_dev_fcoe_disable(काष्ठा net_device *dev)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	पूर्णांक rc = -EINVAL;

	अगर (ops->nकरो_fcoe_disable)
		rc = ops->nकरो_fcoe_disable(real_dev);
	वापस rc;
पूर्ण

अटल पूर्णांक vlan_dev_fcoe_ddp_target(काष्ठा net_device *dev, u16 xid,
				    काष्ठा scatterlist *sgl, अचिन्हित पूर्णांक sgc)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	पूर्णांक rc = 0;

	अगर (ops->nकरो_fcoe_ddp_target)
		rc = ops->nकरो_fcoe_ddp_target(real_dev, xid, sgl, sgc);

	वापस rc;
पूर्ण
#पूर्ण_अगर

#अगर_घोषित NETDEV_FCOE_WWNN
अटल पूर्णांक vlan_dev_fcoe_get_wwn(काष्ठा net_device *dev, u64 *wwn, पूर्णांक type)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	स्थिर काष्ठा net_device_ops *ops = real_dev->netdev_ops;
	पूर्णांक rc = -EINVAL;

	अगर (ops->nकरो_fcoe_get_wwn)
		rc = ops->nकरो_fcoe_get_wwn(real_dev, wwn, type);
	वापस rc;
पूर्ण
#पूर्ण_अगर

अटल व्योम vlan_dev_change_rx_flags(काष्ठा net_device *dev, पूर्णांक change)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;

	अगर (dev->flags & IFF_UP) अणु
		अगर (change & IFF_ALLMULTI)
			dev_set_allmulti(real_dev, dev->flags & IFF_ALLMULTI ? 1 : -1);
		अगर (change & IFF_PROMISC)
			dev_set_promiscuity(real_dev, dev->flags & IFF_PROMISC ? 1 : -1);
	पूर्ण
पूर्ण

अटल व्योम vlan_dev_set_rx_mode(काष्ठा net_device *vlan_dev)
अणु
	dev_mc_sync(vlan_dev_priv(vlan_dev)->real_dev, vlan_dev);
	dev_uc_sync(vlan_dev_priv(vlan_dev)->real_dev, vlan_dev);
पूर्ण

/*
 * vlan network devices have devices nesting below it, and are a special
 * "super class" of normal network devices; split their locks off पूर्णांकo a
 * separate class since they always nest.
 */
अटल काष्ठा lock_class_key vlan_netdev_xmit_lock_key;
अटल काष्ठा lock_class_key vlan_netdev_addr_lock_key;

अटल व्योम vlan_dev_set_lockdep_one(काष्ठा net_device *dev,
				     काष्ठा netdev_queue *txq,
				     व्योम *unused)
अणु
	lockdep_set_class(&txq->_xmit_lock, &vlan_netdev_xmit_lock_key);
पूर्ण

अटल व्योम vlan_dev_set_lockdep_class(काष्ठा net_device *dev)
अणु
	lockdep_set_class(&dev->addr_list_lock,
			  &vlan_netdev_addr_lock_key);
	netdev_क्रम_each_tx_queue(dev, vlan_dev_set_lockdep_one, शून्य);
पूर्ण

अटल __be16 vlan_parse_protocol(स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा vlan_ethhdr *veth = (काष्ठा vlan_ethhdr *)(skb->data);

	वापस __vlan_get_protocol(skb, veth->h_vlan_proto, शून्य);
पूर्ण

अटल स्थिर काष्ठा header_ops vlan_header_ops = अणु
	.create	 = vlan_dev_hard_header,
	.parse	 = eth_header_parse,
	.parse_protocol = vlan_parse_protocol,
पूर्ण;

अटल पूर्णांक vlan_passthru_hard_header(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
				     अचिन्हित लघु type,
				     स्थिर व्योम *daddr, स्थिर व्योम *saddr,
				     अचिन्हित पूर्णांक len)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा net_device *real_dev = vlan->real_dev;

	अगर (saddr == शून्य)
		saddr = dev->dev_addr;

	वापस dev_hard_header(skb, real_dev, type, daddr, saddr, len);
पूर्ण

अटल स्थिर काष्ठा header_ops vlan_passthru_header_ops = अणु
	.create	 = vlan_passthru_hard_header,
	.parse	 = eth_header_parse,
	.parse_protocol = vlan_parse_protocol,
पूर्ण;

अटल काष्ठा device_type vlan_type = अणु
	.name	= "vlan",
पूर्ण;

अटल स्थिर काष्ठा net_device_ops vlan_netdev_ops;

अटल पूर्णांक vlan_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा net_device *real_dev = vlan->real_dev;

	netअगर_carrier_off(dev);

	/* IFF_BROADCAST|IFF_MULTICAST; ??? */
	dev->flags  = real_dev->flags & ~(IFF_UP | IFF_PROMISC | IFF_ALLMULTI |
					  IFF_MASTER | IFF_SLAVE);
	dev->state  = (real_dev->state & ((1<<__LINK_STATE_NOCARRIER) |
					  (1<<__LINK_STATE_DORMANT))) |
		      (1<<__LINK_STATE_PRESENT);

	अगर (vlan->flags & VLAN_FLAG_BRIDGE_BINDING)
		dev->state |= (1 << __LINK_STATE_NOCARRIER);

	dev->hw_features = NETIF_F_HW_CSUM | NETIF_F_SG |
			   NETIF_F_FRAGLIST | NETIF_F_GSO_SOFTWARE |
			   NETIF_F_GSO_ENCAP_ALL |
			   NETIF_F_HIGHDMA | NETIF_F_SCTP_CRC |
			   NETIF_F_ALL_FCOE;

	dev->features |= dev->hw_features | NETIF_F_LLTX;
	dev->gso_max_size = real_dev->gso_max_size;
	dev->gso_max_segs = real_dev->gso_max_segs;
	अगर (dev->features & NETIF_F_VLAN_FEATURES)
		netdev_warn(real_dev, "VLAN features are set incorrectly.  Q-in-Q configurations may not work correctly.\n");

	dev->vlan_features = real_dev->vlan_features & ~NETIF_F_ALL_FCOE;
	dev->hw_enc_features = vlan_tnl_features(real_dev);
	dev->mpls_features = real_dev->mpls_features;

	/* ipv6 shared card related stuff */
	dev->dev_id = real_dev->dev_id;

	अगर (is_zero_ether_addr(dev->dev_addr)) अणु
		ether_addr_copy(dev->dev_addr, real_dev->dev_addr);
		dev->addr_assign_type = NET_ADDR_STOLEN;
	पूर्ण
	अगर (is_zero_ether_addr(dev->broadcast))
		स_नकल(dev->broadcast, real_dev->broadcast, dev->addr_len);

#अगर IS_ENABLED(CONFIG_FCOE)
	dev->fcoe_ddp_xid = real_dev->fcoe_ddp_xid;
#पूर्ण_अगर

	dev->needed_headroom = real_dev->needed_headroom;
	अगर (vlan_hw_offload_capable(real_dev->features, vlan->vlan_proto)) अणु
		dev->header_ops      = &vlan_passthru_header_ops;
		dev->hard_header_len = real_dev->hard_header_len;
	पूर्ण अन्यथा अणु
		dev->header_ops      = &vlan_header_ops;
		dev->hard_header_len = real_dev->hard_header_len + VLAN_HLEN;
	पूर्ण

	dev->netdev_ops = &vlan_netdev_ops;

	SET_NETDEV_DEVTYPE(dev, &vlan_type);

	vlan_dev_set_lockdep_class(dev);

	vlan->vlan_pcpu_stats = netdev_alloc_pcpu_stats(काष्ठा vlan_pcpu_stats);
	अगर (!vlan->vlan_pcpu_stats)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/* Note: this function might be called multiple बार क्रम the same device. */
व्योम vlan_dev_uninit(काष्ठा net_device *dev)
अणु
	काष्ठा vlan_priority_tci_mapping *pm;
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(vlan->egress_priority_map); i++) अणु
		जबतक ((pm = vlan->egress_priority_map[i]) != शून्य) अणु
			vlan->egress_priority_map[i] = pm->next;
			kमुक्त(pm);
		पूर्ण
	पूर्ण
पूर्ण

अटल netdev_features_t vlan_dev_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;
	netdev_features_t old_features = features;
	netdev_features_t lower_features;

	lower_features = netdev_पूर्णांकersect_features((real_dev->vlan_features |
						    NETIF_F_RXCSUM),
						   real_dev->features);

	/* Add HW_CSUM setting to preserve user ability to control
	 * checksum offload on the vlan device.
	 */
	अगर (lower_features & (NETIF_F_IP_CSUM|NETIF_F_IPV6_CSUM))
		lower_features |= NETIF_F_HW_CSUM;
	features = netdev_पूर्णांकersect_features(features, lower_features);
	features |= old_features & (NETIF_F_SOFT_FEATURES | NETIF_F_GSO_SOFTWARE);
	features |= NETIF_F_LLTX;

	वापस features;
पूर्ण

अटल पूर्णांक vlan_ethtool_get_link_ksettings(काष्ठा net_device *dev,
					   काष्ठा ethtool_link_ksettings *cmd)
अणु
	स्थिर काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);

	वापस __ethtool_get_link_ksettings(vlan->real_dev, cmd);
पूर्ण

अटल व्योम vlan_ethtool_get_drvinfo(काष्ठा net_device *dev,
				     काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, vlan_fullname, माप(info->driver));
	strlcpy(info->version, vlan_version, माप(info->version));
	strlcpy(info->fw_version, "N/A", माप(info->fw_version));
पूर्ण

अटल पूर्णांक vlan_ethtool_get_ts_info(काष्ठा net_device *dev,
				    काष्ठा ethtool_ts_info *info)
अणु
	स्थिर काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	स्थिर काष्ठा ethtool_ops *ops = vlan->real_dev->ethtool_ops;
	काष्ठा phy_device *phydev = vlan->real_dev->phydev;

	अगर (phy_has_tsinfo(phydev)) अणु
		वापस phy_ts_info(phydev, info);
	पूर्ण अन्यथा अगर (ops->get_ts_info) अणु
		वापस ops->get_ts_info(vlan->real_dev, info);
	पूर्ण अन्यथा अणु
		info->so_बारtamping = SOF_TIMESTAMPING_RX_SOFTWARE |
			SOF_TIMESTAMPING_SOFTWARE;
		info->phc_index = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम vlan_dev_get_stats64(काष्ठा net_device *dev,
				 काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा vlan_pcpu_stats *p;
	u32 rx_errors = 0, tx_dropped = 0;
	पूर्णांक i;

	क्रम_each_possible_cpu(i) अणु
		u64 rxpackets, rxbytes, rxmulticast, txpackets, txbytes;
		अचिन्हित पूर्णांक start;

		p = per_cpu_ptr(vlan_dev_priv(dev)->vlan_pcpu_stats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&p->syncp);
			rxpackets	= p->rx_packets;
			rxbytes		= p->rx_bytes;
			rxmulticast	= p->rx_multicast;
			txpackets	= p->tx_packets;
			txbytes		= p->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&p->syncp, start));

		stats->rx_packets	+= rxpackets;
		stats->rx_bytes		+= rxbytes;
		stats->multicast	+= rxmulticast;
		stats->tx_packets	+= txpackets;
		stats->tx_bytes		+= txbytes;
		/* rx_errors & tx_dropped are u32 */
		rx_errors	+= p->rx_errors;
		tx_dropped	+= p->tx_dropped;
	पूर्ण
	stats->rx_errors  = rx_errors;
	stats->tx_dropped = tx_dropped;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम vlan_dev_poll_controller(काष्ठा net_device *dev)
अणु
	वापस;
पूर्ण

अटल पूर्णांक vlan_dev_netpoll_setup(काष्ठा net_device *dev, काष्ठा netpoll_info *npinfo)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);
	काष्ठा net_device *real_dev = vlan->real_dev;
	काष्ठा netpoll *netpoll;
	पूर्णांक err = 0;

	netpoll = kzalloc(माप(*netpoll), GFP_KERNEL);
	err = -ENOMEM;
	अगर (!netpoll)
		जाओ out;

	err = __netpoll_setup(netpoll, real_dev);
	अगर (err) अणु
		kमुक्त(netpoll);
		जाओ out;
	पूर्ण

	vlan->netpoll = netpoll;

out:
	वापस err;
पूर्ण

अटल व्योम vlan_dev_netpoll_cleanup(काष्ठा net_device *dev)
अणु
	काष्ठा vlan_dev_priv *vlan= vlan_dev_priv(dev);
	काष्ठा netpoll *netpoll = vlan->netpoll;

	अगर (!netpoll)
		वापस;

	vlan->netpoll = शून्य;
	__netpoll_मुक्त(netpoll);
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_POLL_CONTROLLER */

अटल पूर्णांक vlan_dev_get_अगरlink(स्थिर काष्ठा net_device *dev)
अणु
	काष्ठा net_device *real_dev = vlan_dev_priv(dev)->real_dev;

	वापस real_dev->अगरindex;
पूर्ण

अटल पूर्णांक vlan_dev_fill_क्रमward_path(काष्ठा net_device_path_ctx *ctx,
				      काष्ठा net_device_path *path)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(ctx->dev);

	path->type = DEV_PATH_VLAN;
	path->encap.id = vlan->vlan_id;
	path->encap.proto = vlan->vlan_proto;
	path->dev = ctx->dev;
	ctx->dev = vlan->real_dev;
	अगर (ctx->num_vlans >= ARRAY_SIZE(ctx->vlan))
		वापस -ENOSPC;

	ctx->vlan[ctx->num_vlans].id = vlan->vlan_id;
	ctx->vlan[ctx->num_vlans].proto = vlan->vlan_proto;
	ctx->num_vlans++;

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops vlan_ethtool_ops = अणु
	.get_link_ksettings	= vlan_ethtool_get_link_ksettings,
	.get_drvinfo	        = vlan_ethtool_get_drvinfo,
	.get_link		= ethtool_op_get_link,
	.get_ts_info		= vlan_ethtool_get_ts_info,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops vlan_netdev_ops = अणु
	.nकरो_change_mtu		= vlan_dev_change_mtu,
	.nकरो_init		= vlan_dev_init,
	.nकरो_uninit		= vlan_dev_uninit,
	.nकरो_खोलो		= vlan_dev_खोलो,
	.nकरो_stop		= vlan_dev_stop,
	.nकरो_start_xmit =  vlan_dev_hard_start_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_set_mac_address	= vlan_dev_set_mac_address,
	.nकरो_set_rx_mode	= vlan_dev_set_rx_mode,
	.nकरो_change_rx_flags	= vlan_dev_change_rx_flags,
	.nकरो_करो_ioctl		= vlan_dev_ioctl,
	.nकरो_neigh_setup	= vlan_dev_neigh_setup,
	.nकरो_get_stats64	= vlan_dev_get_stats64,
#अगर IS_ENABLED(CONFIG_FCOE)
	.nकरो_fcoe_ddp_setup	= vlan_dev_fcoe_ddp_setup,
	.nकरो_fcoe_ddp_करोne	= vlan_dev_fcoe_ddp_करोne,
	.nकरो_fcoe_enable	= vlan_dev_fcoe_enable,
	.nकरो_fcoe_disable	= vlan_dev_fcoe_disable,
	.nकरो_fcoe_ddp_target	= vlan_dev_fcoe_ddp_target,
#पूर्ण_अगर
#अगर_घोषित NETDEV_FCOE_WWNN
	.nकरो_fcoe_get_wwn	= vlan_dev_fcoe_get_wwn,
#पूर्ण_अगर
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= vlan_dev_poll_controller,
	.nकरो_netpoll_setup	= vlan_dev_netpoll_setup,
	.nकरो_netpoll_cleanup	= vlan_dev_netpoll_cleanup,
#पूर्ण_अगर
	.nकरो_fix_features	= vlan_dev_fix_features,
	.nकरो_get_अगरlink		= vlan_dev_get_अगरlink,
	.nकरो_fill_क्रमward_path	= vlan_dev_fill_क्रमward_path,
पूर्ण;

अटल व्योम vlan_dev_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा vlan_dev_priv *vlan = vlan_dev_priv(dev);

	मुक्त_percpu(vlan->vlan_pcpu_stats);
	vlan->vlan_pcpu_stats = शून्य;
पूर्ण

व्योम vlan_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	dev->priv_flags		|= IFF_802_1Q_VLAN | IFF_NO_QUEUE;
	dev->priv_flags		|= IFF_UNICAST_FLT;
	dev->priv_flags		&= ~IFF_TX_SKB_SHARING;
	netअगर_keep_dst(dev);

	dev->netdev_ops		= &vlan_netdev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->priv_deकाष्ठाor	= vlan_dev_मुक्त;
	dev->ethtool_ops	= &vlan_ethtool_ops;

	dev->min_mtu		= 0;
	dev->max_mtu		= ETH_MAX_MTU;

	eth_zero_addr(dev->broadcast);
पूर्ण
