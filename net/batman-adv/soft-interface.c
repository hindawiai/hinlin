<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (C) B.A.T.M.A.N. contributors:
 *
 * Marek Lindner, Simon Wunderlich
 */

#समावेश "soft-interface.h"
#समावेश "main.h"

#समावेश <linux/atomic.h>
#समावेश <linux/byteorder/generic.h>
#समावेश <linux/cache.h>
#समावेश <linux/compiler.h>
#समावेश <linux/cpumask.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/gfp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/kernel.h>
#समावेश <linux/kref.h>
#समावेश <linux/list.h>
#समावेश <linux/lockdep.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/netlink.h>
#समावेश <linux/percpu.h>
#समावेश <linux/prपूर्णांकk.h>
#समावेश <linux/अक्रमom.h>
#समावेश <linux/rculist.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/slab.h>
#समावेश <linux/socket.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/मानकघोष.स>
#समावेश <linux/माला.स>
#समावेश <linux/types.h>
#समावेश <net/netlink.h>
#समावेश <uapi/linux/batadv_packet.h>
#समावेश <uapi/linux/baपंचांगan_adv.h>

#समावेश "bat_algo.h"
#समावेश "bridge_loop_avoidance.h"
#समावेश "distributed-arp-table.h"
#समावेश "gateway_client.h"
#समावेश "hard-interface.h"
#समावेश "multicast.h"
#समावेश "network-coding.h"
#समावेश "originator.h"
#समावेश "send.h"
#समावेश "translation-table.h"

/**
 * batadv_skb_head_push() - Increase header size and move (push) head poपूर्णांकer
 * @skb: packet buffer which should be modअगरied
 * @len: number of bytes to add
 *
 * Return: 0 on success or negative error number in हाल of failure
 */
पूर्णांक batadv_skb_head_push(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक len)
अणु
	पूर्णांक result;

	/* TODO: We must check अगर we can release all references to non-payload
	 * data using __skb_header_release in our skbs to allow skb_cow_header
	 * to work optimally. This means that those skbs are not allowed to पढ़ो
	 * or ग_लिखो any data which is beक्रमe the current position of skb->data
	 * after that call and thus allow other skbs with the same data buffer
	 * to ग_लिखो मुक्तly in that area.
	 */
	result = skb_cow_head(skb, len);
	अगर (result < 0)
		वापस result;

	skb_push(skb, len);
	वापस 0;
पूर्ण

अटल पूर्णांक batadv_पूर्णांकerface_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_start_queue(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक batadv_पूर्णांकerface_release(काष्ठा net_device *dev)
अणु
	netअगर_stop_queue(dev);
	वापस 0;
पूर्ण

/**
 * batadv_sum_counter() - Sum the cpu-local counters क्रम index 'idx'
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @idx: index of counter to sum up
 *
 * Return: sum of all cpu-local counters
 */
अटल u64 batadv_sum_counter(काष्ठा batadv_priv *bat_priv,  माप_प्रकार idx)
अणु
	u64 *counters, sum = 0;
	पूर्णांक cpu;

	क्रम_each_possible_cpu(cpu) अणु
		counters = per_cpu_ptr(bat_priv->bat_counters, cpu);
		sum += counters[idx];
	पूर्ण

	वापस sum;
पूर्ण

अटल काष्ठा net_device_stats *batadv_पूर्णांकerface_stats(काष्ठा net_device *dev)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(dev);
	काष्ठा net_device_stats *stats = &dev->stats;

	stats->tx_packets = batadv_sum_counter(bat_priv, BATADV_CNT_TX);
	stats->tx_bytes = batadv_sum_counter(bat_priv, BATADV_CNT_TX_BYTES);
	stats->tx_dropped = batadv_sum_counter(bat_priv, BATADV_CNT_TX_DROPPED);
	stats->rx_packets = batadv_sum_counter(bat_priv, BATADV_CNT_RX);
	stats->rx_bytes = batadv_sum_counter(bat_priv, BATADV_CNT_RX_BYTES);
	वापस stats;
पूर्ण

अटल पूर्णांक batadv_पूर्णांकerface_set_mac_addr(काष्ठा net_device *dev, व्योम *p)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(dev);
	काष्ठा batadv_softअगर_vlan *vlan;
	काष्ठा sockaddr *addr = p;
	u8 old_addr[ETH_ALEN];

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	ether_addr_copy(old_addr, dev->dev_addr);
	ether_addr_copy(dev->dev_addr, addr->sa_data);

	/* only modअगरy transtable अगर it has been initialized beक्रमe */
	अगर (atomic_पढ़ो(&bat_priv->mesh_state) != BATADV_MESH_ACTIVE)
		वापस 0;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(vlan, &bat_priv->softअगर_vlan_list, list) अणु
		batadv_tt_local_हटाओ(bat_priv, old_addr, vlan->vid,
				       "mac address changed", false);
		batadv_tt_local_add(dev, addr->sa_data, vlan->vid,
				    BATADV_शून्य_IFINDEX, BATADV_NO_MARK);
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक batadv_पूर्णांकerface_change_mtu(काष्ठा net_device *dev, पूर्णांक new_mtu)
अणु
	/* check ranges */
	अगर (new_mtu < 68 || new_mtu > batadv_hardअगर_min_mtu(dev))
		वापस -EINVAL;

	dev->mtu = new_mtu;

	वापस 0;
पूर्ण

/**
 * batadv_पूर्णांकerface_set_rx_mode() - set the rx mode of a device
 * @dev: रेजिस्टरed network device to modअगरy
 *
 * We करो not actually need to set any rx filters क्रम the भव baपंचांगan
 * soft पूर्णांकerface. However a dummy handler enables a user to set अटल
 * multicast listeners क्रम instance.
 */
अटल व्योम batadv_पूर्णांकerface_set_rx_mode(काष्ठा net_device *dev)
अणु
पूर्ण

अटल netdev_tx_t batadv_पूर्णांकerface_tx(काष्ठा sk_buff *skb,
				       काष्ठा net_device *soft_अगरace)
अणु
	काष्ठा ethhdr *ethhdr;
	काष्ठा batadv_priv *bat_priv = netdev_priv(soft_अगरace);
	काष्ठा batadv_hard_अगरace *primary_अगर = शून्य;
	काष्ठा batadv_bcast_packet *bcast_packet;
	अटल स्थिर u8 stp_addr[ETH_ALEN] = अणु0x01, 0x80, 0xC2, 0x00,
					      0x00, 0x00पूर्ण;
	अटल स्थिर u8 ectp_addr[ETH_ALEN] = अणु0xCF, 0x00, 0x00, 0x00,
					       0x00, 0x00पूर्ण;
	क्रमागत batadv_dhcp_recipient dhcp_rcp = BATADV_DHCP_NO;
	u8 *dst_hपूर्णांक = शून्य, chaddr[ETH_ALEN];
	काष्ठा vlan_ethhdr *vhdr;
	अचिन्हित पूर्णांक header_len = 0;
	पूर्णांक data_len = skb->len, ret;
	अचिन्हित दीर्घ brd_delay = 1;
	bool करो_bcast = false, client_added;
	अचिन्हित लघु vid;
	u32 seqno;
	पूर्णांक gw_mode;
	क्रमागत batadv_क्रमw_mode क्रमw_mode = BATADV_FORW_SINGLE;
	काष्ठा batadv_orig_node *mcast_single_orig = शून्य;
	पूर्णांक network_offset = ETH_HLEN;
	__be16 proto;

	अगर (atomic_पढ़ो(&bat_priv->mesh_state) != BATADV_MESH_ACTIVE)
		जाओ dropped;

	/* reset control block to aव्योम left overs from previous users */
	स_रखो(skb->cb, 0, माप(काष्ठा batadv_skb_cb));

	netअगर_trans_update(soft_अगरace);
	vid = batadv_get_vid(skb, 0);

	skb_reset_mac_header(skb);
	ethhdr = eth_hdr(skb);

	proto = ethhdr->h_proto;

	चयन (ntohs(proto)) अणु
	हाल ETH_P_8021Q:
		अगर (!pskb_may_pull(skb, माप(*vhdr)))
			जाओ dropped;
		vhdr = vlan_eth_hdr(skb);
		proto = vhdr->h_vlan_encapsulated_proto;

		/* drop baपंचांगan-in-baपंचांगan packets to prevent loops */
		अगर (proto != htons(ETH_P_BATMAN)) अणु
			network_offset += VLAN_HLEN;
			अवरोध;
		पूर्ण

		fallthrough;
	हाल ETH_P_BATMAN:
		जाओ dropped;
	पूर्ण

	skb_set_network_header(skb, network_offset);

	अगर (batadv_bla_tx(bat_priv, skb, vid))
		जाओ dropped;

	/* skb->data might have been पुनः_स्मृतिated by batadv_bla_tx() */
	ethhdr = eth_hdr(skb);

	/* Register the client MAC in the transtable */
	अगर (!is_multicast_ether_addr(ethhdr->h_source) &&
	    !batadv_bla_is_loopdetect_mac(ethhdr->h_source)) अणु
		client_added = batadv_tt_local_add(soft_अगरace, ethhdr->h_source,
						   vid, skb->skb_iअगर,
						   skb->mark);
		अगर (!client_added)
			जाओ dropped;
	पूर्ण

	/* Snoop address candidates from DHCPACKs क्रम early DAT filling */
	batadv_dat_snoop_outgoing_dhcp_ack(bat_priv, skb, proto, vid);

	/* करोn't accept stp packets. STP करोes not help in meshes.
	 * better use the bridge loop aव्योमance ...
	 *
	 * The same goes क्रम ECTP sent at least by some Cisco Switches,
	 * it might confuse the mesh when used with bridge loop aव्योमance.
	 */
	अगर (batadv_compare_eth(ethhdr->h_dest, stp_addr))
		जाओ dropped;

	अगर (batadv_compare_eth(ethhdr->h_dest, ectp_addr))
		जाओ dropped;

	gw_mode = atomic_पढ़ो(&bat_priv->gw.mode);
	अगर (is_multicast_ether_addr(ethhdr->h_dest)) अणु
		/* अगर gw mode is off, broadcast every packet */
		अगर (gw_mode == BATADV_GW_MODE_OFF) अणु
			करो_bcast = true;
			जाओ send;
		पूर्ण

		dhcp_rcp = batadv_gw_dhcp_recipient_get(skb, &header_len,
							chaddr);
		/* skb->data may have been modअगरied by
		 * batadv_gw_dhcp_recipient_get()
		 */
		ethhdr = eth_hdr(skb);
		/* अगर gw_mode is on, broadcast any non-DHCP message.
		 * All the DHCP packets are going to be sent as unicast
		 */
		अगर (dhcp_rcp == BATADV_DHCP_NO) अणु
			करो_bcast = true;
			जाओ send;
		पूर्ण

		अगर (dhcp_rcp == BATADV_DHCP_TO_CLIENT)
			dst_hपूर्णांक = chaddr;
		अन्यथा अगर ((gw_mode == BATADV_GW_MODE_SERVER) &&
			 (dhcp_rcp == BATADV_DHCP_TO_SERVER))
			/* gateways should not क्रमward any DHCP message अगर
			 * directed to a DHCP server
			 */
			जाओ dropped;

send:
		अगर (करो_bcast && !is_broadcast_ether_addr(ethhdr->h_dest)) अणु
			क्रमw_mode = batadv_mcast_क्रमw_mode(bat_priv, skb,
							   &mcast_single_orig);
			अगर (क्रमw_mode == BATADV_FORW_NONE)
				जाओ dropped;

			अगर (क्रमw_mode == BATADV_FORW_SINGLE ||
			    क्रमw_mode == BATADV_FORW_SOME)
				करो_bcast = false;
		पूर्ण
	पूर्ण

	batadv_skb_set_priority(skb, 0);

	/* ethernet packet should be broadcasted */
	अगर (करो_bcast) अणु
		primary_अगर = batadv_primary_अगर_get_selected(bat_priv);
		अगर (!primary_अगर)
			जाओ dropped;

		/* in हाल of ARP request, we करो not immediately broadcasti the
		 * packet, instead we first रुको क्रम DAT to try to retrieve the
		 * correct ARP entry
		 */
		अगर (batadv_dat_snoop_outgoing_arp_request(bat_priv, skb))
			brd_delay = msecs_to_jअगरfies(ARP_REQ_DELAY);

		अगर (batadv_skb_head_push(skb, माप(*bcast_packet)) < 0)
			जाओ dropped;

		bcast_packet = (काष्ठा batadv_bcast_packet *)skb->data;
		bcast_packet->version = BATADV_COMPAT_VERSION;
		bcast_packet->ttl = BATADV_TTL;

		/* baपंचांगan packet type: broadcast */
		bcast_packet->packet_type = BATADV_BCAST;
		bcast_packet->reserved = 0;

		/* hw address of first पूर्णांकerface is the orig mac because only
		 * this mac is known throughout the mesh
		 */
		ether_addr_copy(bcast_packet->orig,
				primary_अगर->net_dev->dev_addr);

		/* set broadcast sequence number */
		seqno = atomic_inc_वापस(&bat_priv->bcast_seqno);
		bcast_packet->seqno = htonl(seqno);

		batadv_add_bcast_packet_to_list(bat_priv, skb, brd_delay, true);

		/* a copy is stored in the bcast list, thereक्रमe removing
		 * the original skb.
		 */
		consume_skb(skb);

	/* unicast packet */
	पूर्ण अन्यथा अणु
		/* DHCP packets going to a server will use the GW feature */
		अगर (dhcp_rcp == BATADV_DHCP_TO_SERVER) अणु
			ret = batadv_gw_out_of_range(bat_priv, skb);
			अगर (ret)
				जाओ dropped;
			ret = batadv_send_skb_via_gw(bat_priv, skb, vid);
		पूर्ण अन्यथा अगर (mcast_single_orig) अणु
			ret = batadv_mcast_क्रमw_send_orig(bat_priv, skb, vid,
							  mcast_single_orig);
		पूर्ण अन्यथा अगर (क्रमw_mode == BATADV_FORW_SOME) अणु
			ret = batadv_mcast_क्रमw_send(bat_priv, skb, vid);
		पूर्ण अन्यथा अणु
			अगर (batadv_dat_snoop_outgoing_arp_request(bat_priv,
								  skb))
				जाओ dropped;

			batadv_dat_snoop_outgoing_arp_reply(bat_priv, skb);

			ret = batadv_send_skb_via_tt(bat_priv, skb, dst_hपूर्णांक,
						     vid);
		पूर्ण
		अगर (ret != NET_XMIT_SUCCESS)
			जाओ dropped_मुक्तd;
	पूर्ण

	batadv_inc_counter(bat_priv, BATADV_CNT_TX);
	batadv_add_counter(bat_priv, BATADV_CNT_TX_BYTES, data_len);
	जाओ end;

dropped:
	kमुक्त_skb(skb);
dropped_मुक्तd:
	batadv_inc_counter(bat_priv, BATADV_CNT_TX_DROPPED);
end:
	अगर (mcast_single_orig)
		batadv_orig_node_put(mcast_single_orig);
	अगर (primary_अगर)
		batadv_hardअगर_put(primary_अगर);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * batadv_पूर्णांकerface_rx() - receive ethernet frame on local baपंचांगan-adv पूर्णांकerface
 * @soft_अगरace: local पूर्णांकerface which will receive the ethernet frame
 * @skb: ethernet frame क्रम @soft_अगरace
 * @hdr_size: size of alपढ़ोy parsed baपंचांगan-adv header
 * @orig_node: originator from which the baपंचांगan-adv packet was sent
 *
 * Sends an ethernet frame to the receive path of the local @soft_अगरace.
 * skb->data has still poपूर्णांक to the baपंचांगan-adv header with the size @hdr_size.
 * The caller has to have parsed this header alपढ़ोy and made sure that at least
 * @hdr_size bytes are still available क्रम pull in @skb.
 *
 * The packet may still get dropped. This can happen when the encapsulated
 * ethernet frame is invalid or contains again an baपंचांगan-adv packet. Also
 * unicast packets will be dropped directly when it was sent between two
 * isolated clients.
 */
व्योम batadv_पूर्णांकerface_rx(काष्ठा net_device *soft_अगरace,
			 काष्ठा sk_buff *skb, पूर्णांक hdr_size,
			 काष्ठा batadv_orig_node *orig_node)
अणु
	काष्ठा batadv_bcast_packet *batadv_bcast_packet;
	काष्ठा batadv_priv *bat_priv = netdev_priv(soft_अगरace);
	काष्ठा vlan_ethhdr *vhdr;
	काष्ठा ethhdr *ethhdr;
	अचिन्हित लघु vid;
	पूर्णांक packet_type;

	batadv_bcast_packet = (काष्ठा batadv_bcast_packet *)skb->data;
	packet_type = batadv_bcast_packet->packet_type;

	skb_pull_rcsum(skb, hdr_size);
	skb_reset_mac_header(skb);

	/* clean the netfilter state now that the baपंचांगan-adv header has been
	 * हटाओd
	 */
	nf_reset_ct(skb);

	अगर (unlikely(!pskb_may_pull(skb, ETH_HLEN)))
		जाओ dropped;

	vid = batadv_get_vid(skb, 0);
	ethhdr = eth_hdr(skb);

	चयन (ntohs(ethhdr->h_proto)) अणु
	हाल ETH_P_8021Q:
		अगर (!pskb_may_pull(skb, VLAN_ETH_HLEN))
			जाओ dropped;

		vhdr = (काष्ठा vlan_ethhdr *)skb->data;

		/* drop baपंचांगan-in-baपंचांगan packets to prevent loops */
		अगर (vhdr->h_vlan_encapsulated_proto != htons(ETH_P_BATMAN))
			अवरोध;

		fallthrough;
	हाल ETH_P_BATMAN:
		जाओ dropped;
	पूर्ण

	/* skb->dev & skb->pkt_type are set here */
	skb->protocol = eth_type_trans(skb, soft_अगरace);
	skb_postpull_rcsum(skb, eth_hdr(skb), ETH_HLEN);

	batadv_inc_counter(bat_priv, BATADV_CNT_RX);
	batadv_add_counter(bat_priv, BATADV_CNT_RX_BYTES,
			   skb->len + ETH_HLEN);

	/* Let the bridge loop aव्योमance check the packet. If will
	 * not handle it, we can safely push it up.
	 */
	अगर (batadv_bla_rx(bat_priv, skb, vid, packet_type))
		जाओ out;

	अगर (orig_node)
		batadv_tt_add_temporary_global_entry(bat_priv, orig_node,
						     ethhdr->h_source, vid);

	अगर (is_multicast_ether_addr(ethhdr->h_dest)) अणु
		/* set the mark on broadcast packets अगर AP isolation is ON and
		 * the packet is coming from an "isolated" client
		 */
		अगर (batadv_vlan_ap_isola_get(bat_priv, vid) &&
		    batadv_tt_global_is_isolated(bat_priv, ethhdr->h_source,
						 vid)) अणु
			/* save bits in skb->mark not covered by the mask and
			 * apply the mark on the rest
			 */
			skb->mark &= ~bat_priv->isolation_mark_mask;
			skb->mark |= bat_priv->isolation_mark;
		पूर्ण
	पूर्ण अन्यथा अगर (batadv_is_ap_isolated(bat_priv, ethhdr->h_source,
					 ethhdr->h_dest, vid)) अणु
		जाओ dropped;
	पूर्ण

	netअगर_rx(skb);
	जाओ out;

dropped:
	kमुक्त_skb(skb);
out:
	वापस;
पूर्ण

/**
 * batadv_softअगर_vlan_release() - release vlan from lists and queue क्रम मुक्त
 *  after rcu grace period
 * @ref: kref poपूर्णांकer of the vlan object
 */
अटल व्योम batadv_softअगर_vlan_release(काष्ठा kref *ref)
अणु
	काष्ठा batadv_softअगर_vlan *vlan;

	vlan = container_of(ref, काष्ठा batadv_softअगर_vlan, refcount);

	spin_lock_bh(&vlan->bat_priv->softअगर_vlan_list_lock);
	hlist_del_rcu(&vlan->list);
	spin_unlock_bh(&vlan->bat_priv->softअगर_vlan_list_lock);

	kमुक्त_rcu(vlan, rcu);
पूर्ण

/**
 * batadv_softअगर_vlan_put() - decrease the vlan object refcounter and
 *  possibly release it
 * @vlan: the vlan object to release
 */
व्योम batadv_softअगर_vlan_put(काष्ठा batadv_softअगर_vlan *vlan)
अणु
	अगर (!vlan)
		वापस;

	kref_put(&vlan->refcount, batadv_softअगर_vlan_release);
पूर्ण

/**
 * batadv_softअगर_vlan_get() - get the vlan object क्रम a specअगरic vid
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vid: the identअगरier of the vlan object to retrieve
 *
 * Return: the निजी data of the vlan matching the vid passed as argument or
 * शून्य otherwise. The refcounter of the वापसed object is incremented by 1.
 */
काष्ठा batadv_softअगर_vlan *batadv_softअगर_vlan_get(काष्ठा batadv_priv *bat_priv,
						  अचिन्हित लघु vid)
अणु
	काष्ठा batadv_softअगर_vlan *vlan_पंचांगp, *vlan = शून्य;

	rcu_पढ़ो_lock();
	hlist_क्रम_each_entry_rcu(vlan_पंचांगp, &bat_priv->softअगर_vlan_list, list) अणु
		अगर (vlan_पंचांगp->vid != vid)
			जारी;

		अगर (!kref_get_unless_zero(&vlan_पंचांगp->refcount))
			जारी;

		vlan = vlan_पंचांगp;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस vlan;
पूर्ण

/**
 * batadv_softअगर_create_vlan() - allocate the needed resources क्रम a new vlan
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vid: the VLAN identअगरier
 *
 * Return: 0 on success, a negative error otherwise.
 */
पूर्णांक batadv_softअगर_create_vlan(काष्ठा batadv_priv *bat_priv, अचिन्हित लघु vid)
अणु
	काष्ठा batadv_softअगर_vlan *vlan;

	spin_lock_bh(&bat_priv->softअगर_vlan_list_lock);

	vlan = batadv_softअगर_vlan_get(bat_priv, vid);
	अगर (vlan) अणु
		batadv_softअगर_vlan_put(vlan);
		spin_unlock_bh(&bat_priv->softअगर_vlan_list_lock);
		वापस -EEXIST;
	पूर्ण

	vlan = kzalloc(माप(*vlan), GFP_ATOMIC);
	अगर (!vlan) अणु
		spin_unlock_bh(&bat_priv->softअगर_vlan_list_lock);
		वापस -ENOMEM;
	पूर्ण

	vlan->bat_priv = bat_priv;
	vlan->vid = vid;
	kref_init(&vlan->refcount);

	atomic_set(&vlan->ap_isolation, 0);

	kref_get(&vlan->refcount);
	hlist_add_head_rcu(&vlan->list, &bat_priv->softअगर_vlan_list);
	spin_unlock_bh(&bat_priv->softअगर_vlan_list_lock);

	/* add a new TT local entry. This one will be marked with the NOPURGE
	 * flag
	 */
	batadv_tt_local_add(bat_priv->soft_अगरace,
			    bat_priv->soft_अगरace->dev_addr, vid,
			    BATADV_शून्य_IFINDEX, BATADV_NO_MARK);

	/* करोn't वापस reference to new softअगर_vlan */
	batadv_softअगर_vlan_put(vlan);

	वापस 0;
पूर्ण

/**
 * batadv_softअगर_destroy_vlan() - हटाओ and destroy a softअगर_vlan object
 * @bat_priv: the bat priv with all the soft पूर्णांकerface inक्रमmation
 * @vlan: the object to हटाओ
 */
अटल व्योम batadv_softअगर_destroy_vlan(काष्ठा batadv_priv *bat_priv,
				       काष्ठा batadv_softअगर_vlan *vlan)
अणु
	/* explicitly हटाओ the associated TT local entry because it is marked
	 * with the NOPURGE flag
	 */
	batadv_tt_local_हटाओ(bat_priv, bat_priv->soft_अगरace->dev_addr,
			       vlan->vid, "vlan interface destroyed", false);

	batadv_softअगर_vlan_put(vlan);
पूर्ण

/**
 * batadv_पूर्णांकerface_add_vid() - nकरो_add_vid API implementation
 * @dev: the netdev of the mesh पूर्णांकerface
 * @proto: protocol of the vlan id
 * @vid: identअगरier of the new vlan
 *
 * Set up all the पूर्णांकernal काष्ठाures क्रम handling the new vlan on top of the
 * mesh पूर्णांकerface
 *
 * Return: 0 on success or a negative error code in हाल of failure.
 */
अटल पूर्णांक batadv_पूर्णांकerface_add_vid(काष्ठा net_device *dev, __be16 proto,
				    अचिन्हित लघु vid)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(dev);
	काष्ठा batadv_softअगर_vlan *vlan;

	/* only 802.1Q vlans are supported.
	 * baपंचांगan-adv करोes not know how to handle other types
	 */
	अगर (proto != htons(ETH_P_8021Q))
		वापस -EINVAL;

	vid |= BATADV_VLAN_HAS_TAG;

	/* अगर a new vlan is getting created and it alपढ़ोy exists, it means that
	 * it was not deleted yet. batadv_softअगर_vlan_get() increases the
	 * refcount in order to revive the object.
	 *
	 * अगर it करोes not exist then create it.
	 */
	vlan = batadv_softअगर_vlan_get(bat_priv, vid);
	अगर (!vlan)
		वापस batadv_softअगर_create_vlan(bat_priv, vid);

	/* add a new TT local entry. This one will be marked with the NOPURGE
	 * flag. This must be added again, even अगर the vlan object alपढ़ोy
	 * exists, because the entry was deleted by समाप्त_vid()
	 */
	batadv_tt_local_add(bat_priv->soft_अगरace,
			    bat_priv->soft_अगरace->dev_addr, vid,
			    BATADV_शून्य_IFINDEX, BATADV_NO_MARK);

	वापस 0;
पूर्ण

/**
 * batadv_पूर्णांकerface_समाप्त_vid() - nकरो_समाप्त_vid API implementation
 * @dev: the netdev of the mesh पूर्णांकerface
 * @proto: protocol of the vlan id
 * @vid: identअगरier of the deleted vlan
 *
 * Destroy all the पूर्णांकernal काष्ठाures used to handle the vlan identअगरied by vid
 * on top of the mesh पूर्णांकerface
 *
 * Return: 0 on success, -EINVAL अगर the specअगरied prototype is not ETH_P_8021Q
 * or -ENOENT अगर the specअगरied vlan id wasn't रेजिस्टरed.
 */
अटल पूर्णांक batadv_पूर्णांकerface_समाप्त_vid(काष्ठा net_device *dev, __be16 proto,
				     अचिन्हित लघु vid)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(dev);
	काष्ठा batadv_softअगर_vlan *vlan;

	/* only 802.1Q vlans are supported. baपंचांगan-adv करोes not know how to
	 * handle other types
	 */
	अगर (proto != htons(ETH_P_8021Q))
		वापस -EINVAL;

	vlan = batadv_softअगर_vlan_get(bat_priv, vid | BATADV_VLAN_HAS_TAG);
	अगर (!vlan)
		वापस -ENOENT;

	batadv_softअगर_destroy_vlan(bat_priv, vlan);

	/* finally मुक्त the vlan object */
	batadv_softअगर_vlan_put(vlan);

	वापस 0;
पूर्ण

/* baपंचांगan-adv network devices have devices nesting below it and are a special
 * "super class" of normal network devices; split their locks off पूर्णांकo a
 * separate class since they always nest.
 */
अटल काष्ठा lock_class_key batadv_netdev_xmit_lock_key;
अटल काष्ठा lock_class_key batadv_netdev_addr_lock_key;

/**
 * batadv_set_lockdep_class_one() - Set lockdep class क्रम a single tx queue
 * @dev: device which owns the tx queue
 * @txq: tx queue to modअगरy
 * @_unused: always शून्य
 */
अटल व्योम batadv_set_lockdep_class_one(काष्ठा net_device *dev,
					 काष्ठा netdev_queue *txq,
					 व्योम *_unused)
अणु
	lockdep_set_class(&txq->_xmit_lock, &batadv_netdev_xmit_lock_key);
पूर्ण

/**
 * batadv_set_lockdep_class() - Set txq and addr_list lockdep class
 * @dev: network device to modअगरy
 */
अटल व्योम batadv_set_lockdep_class(काष्ठा net_device *dev)
अणु
	lockdep_set_class(&dev->addr_list_lock, &batadv_netdev_addr_lock_key);
	netdev_क्रम_each_tx_queue(dev, batadv_set_lockdep_class_one, शून्य);
पूर्ण

/**
 * batadv_softअगर_init_late() - late stage initialization of soft पूर्णांकerface
 * @dev: रेजिस्टरed network device to modअगरy
 *
 * Return: error code on failures
 */
अटल पूर्णांक batadv_softअगर_init_late(काष्ठा net_device *dev)
अणु
	काष्ठा batadv_priv *bat_priv;
	u32 अक्रमom_seqno;
	पूर्णांक ret;
	माप_प्रकार cnt_len = माप(u64) * BATADV_CNT_NUM;

	batadv_set_lockdep_class(dev);

	bat_priv = netdev_priv(dev);
	bat_priv->soft_अगरace = dev;

	/* batadv_पूर्णांकerface_stats() needs to be available as soon as
	 * रेजिस्टर_netdevice() has been called
	 */
	bat_priv->bat_counters = __alloc_percpu(cnt_len, __alignof__(u64));
	अगर (!bat_priv->bat_counters)
		वापस -ENOMEM;

	atomic_set(&bat_priv->aggregated_ogms, 1);
	atomic_set(&bat_priv->bonding, 0);
#अगर_घोषित CONFIG_BATMAN_ADV_BLA
	atomic_set(&bat_priv->bridge_loop_aव्योमance, 1);
#पूर्ण_अगर
#अगर_घोषित CONFIG_BATMAN_ADV_DAT
	atomic_set(&bat_priv->distributed_arp_table, 1);
#पूर्ण_अगर
#अगर_घोषित CONFIG_BATMAN_ADV_MCAST
	atomic_set(&bat_priv->multicast_mode, 1);
	atomic_set(&bat_priv->multicast_fanout, 16);
	atomic_set(&bat_priv->mcast.num_want_all_unsnoopables, 0);
	atomic_set(&bat_priv->mcast.num_want_all_ipv4, 0);
	atomic_set(&bat_priv->mcast.num_want_all_ipv6, 0);
#पूर्ण_अगर
	atomic_set(&bat_priv->gw.mode, BATADV_GW_MODE_OFF);
	atomic_set(&bat_priv->gw.bandwidth_करोwn, 100);
	atomic_set(&bat_priv->gw.bandwidth_up, 20);
	atomic_set(&bat_priv->orig_पूर्णांकerval, 1000);
	atomic_set(&bat_priv->hop_penalty, 30);
#अगर_घोषित CONFIG_BATMAN_ADV_DEBUG
	atomic_set(&bat_priv->log_level, 0);
#पूर्ण_अगर
	atomic_set(&bat_priv->fragmentation, 1);
	atomic_set(&bat_priv->packet_size_max, ETH_DATA_LEN);
	atomic_set(&bat_priv->bcast_queue_left, BATADV_BCAST_QUEUE_LEN);
	atomic_set(&bat_priv->baपंचांगan_queue_left, BATADV_BATMAN_QUEUE_LEN);

	atomic_set(&bat_priv->mesh_state, BATADV_MESH_INACTIVE);
	atomic_set(&bat_priv->bcast_seqno, 1);
	atomic_set(&bat_priv->tt.vn, 0);
	atomic_set(&bat_priv->tt.local_changes, 0);
	atomic_set(&bat_priv->tt.ogm_append_cnt, 0);
#अगर_घोषित CONFIG_BATMAN_ADV_BLA
	atomic_set(&bat_priv->bla.num_requests, 0);
#पूर्ण_अगर
	atomic_set(&bat_priv->tp_num, 0);

	bat_priv->tt.last_changeset = शून्य;
	bat_priv->tt.last_changeset_len = 0;
	bat_priv->isolation_mark = 0;
	bat_priv->isolation_mark_mask = 0;

	/* अक्रमomize initial seqno to aव्योम collision */
	get_अक्रमom_bytes(&अक्रमom_seqno, माप(अक्रमom_seqno));
	atomic_set(&bat_priv->frag_seqno, अक्रमom_seqno);

	bat_priv->primary_अगर = शून्य;

	batadv_nc_init_bat_priv(bat_priv);

	अगर (!bat_priv->algo_ops) अणु
		ret = batadv_algo_select(bat_priv, batadv_routing_algo);
		अगर (ret < 0)
			जाओ मुक्त_bat_counters;
	पूर्ण

	ret = batadv_mesh_init(dev);
	अगर (ret < 0)
		जाओ मुक्त_bat_counters;

	वापस 0;

मुक्त_bat_counters:
	मुक्त_percpu(bat_priv->bat_counters);
	bat_priv->bat_counters = शून्य;

	वापस ret;
पूर्ण

/**
 * batadv_softअगर_slave_add() - Add a slave पूर्णांकerface to a batadv_soft_पूर्णांकerface
 * @dev: batadv_soft_पूर्णांकerface used as master पूर्णांकerface
 * @slave_dev: net_device which should become the slave पूर्णांकerface
 * @extack: extended ACK report काष्ठा
 *
 * Return: 0 अगर successful or error otherwise.
 */
अटल पूर्णांक batadv_softअगर_slave_add(काष्ठा net_device *dev,
				   काष्ठा net_device *slave_dev,
				   काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा net *net = dev_net(dev);
	पूर्णांक ret = -EINVAL;

	hard_अगरace = batadv_hardअगर_get_by_netdev(slave_dev);
	अगर (!hard_अगरace || hard_अगरace->soft_अगरace)
		जाओ out;

	ret = batadv_hardअगर_enable_पूर्णांकerface(hard_अगरace, net, dev->name);

out:
	अगर (hard_अगरace)
		batadv_hardअगर_put(hard_अगरace);
	वापस ret;
पूर्ण

/**
 * batadv_softअगर_slave_del() - Delete a slave अगरace from a batadv_soft_पूर्णांकerface
 * @dev: batadv_soft_पूर्णांकerface used as master पूर्णांकerface
 * @slave_dev: net_device which should be हटाओd from the master पूर्णांकerface
 *
 * Return: 0 अगर successful or error otherwise.
 */
अटल पूर्णांक batadv_softअगर_slave_del(काष्ठा net_device *dev,
				   काष्ठा net_device *slave_dev)
अणु
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	पूर्णांक ret = -EINVAL;

	hard_अगरace = batadv_hardअगर_get_by_netdev(slave_dev);

	अगर (!hard_अगरace || hard_अगरace->soft_अगरace != dev)
		जाओ out;

	batadv_hardअगर_disable_पूर्णांकerface(hard_अगरace);
	ret = 0;

out:
	अगर (hard_अगरace)
		batadv_hardअगर_put(hard_अगरace);
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा net_device_ops batadv_netdev_ops = अणु
	.nकरो_init = batadv_softअगर_init_late,
	.nकरो_खोलो = batadv_पूर्णांकerface_खोलो,
	.nकरो_stop = batadv_पूर्णांकerface_release,
	.nकरो_get_stats = batadv_पूर्णांकerface_stats,
	.nकरो_vlan_rx_add_vid = batadv_पूर्णांकerface_add_vid,
	.nकरो_vlan_rx_समाप्त_vid = batadv_पूर्णांकerface_समाप्त_vid,
	.nकरो_set_mac_address = batadv_पूर्णांकerface_set_mac_addr,
	.nकरो_change_mtu = batadv_पूर्णांकerface_change_mtu,
	.nकरो_set_rx_mode = batadv_पूर्णांकerface_set_rx_mode,
	.nकरो_start_xmit = batadv_पूर्णांकerface_tx,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_add_slave = batadv_softअगर_slave_add,
	.nकरो_del_slave = batadv_softअगर_slave_del,
पूर्ण;

अटल व्योम batadv_get_drvinfo(काष्ठा net_device *dev,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strscpy(info->driver, "B.A.T.M.A.N. advanced", माप(info->driver));
	strscpy(info->version, BATADV_SOURCE_VERSION, माप(info->version));
	strscpy(info->fw_version, "N/A", माप(info->fw_version));
	strscpy(info->bus_info, "batman", माप(info->bus_info));
पूर्ण

/* Inspired by drivers/net/ethernet/dlink/sundance.c:1702
 * Declare each description string in काष्ठा.name[] to get fixed sized buffer
 * and compile समय checking क्रम strings दीर्घer than ETH_GSTRING_LEN.
 */
अटल स्थिर काष्ठा अणु
	स्थिर अक्षर name[ETH_GSTRING_LEN];
पूर्ण batadv_counters_strings[] = अणु
	अणु "tx" पूर्ण,
	अणु "tx_bytes" पूर्ण,
	अणु "tx_dropped" पूर्ण,
	अणु "rx" पूर्ण,
	अणु "rx_bytes" पूर्ण,
	अणु "forward" पूर्ण,
	अणु "forward_bytes" पूर्ण,
	अणु "mgmt_tx" पूर्ण,
	अणु "mgmt_tx_bytes" पूर्ण,
	अणु "mgmt_rx" पूर्ण,
	अणु "mgmt_rx_bytes" पूर्ण,
	अणु "frag_tx" पूर्ण,
	अणु "frag_tx_bytes" पूर्ण,
	अणु "frag_rx" पूर्ण,
	अणु "frag_rx_bytes" पूर्ण,
	अणु "frag_fwd" पूर्ण,
	अणु "frag_fwd_bytes" पूर्ण,
	अणु "tt_request_tx" पूर्ण,
	अणु "tt_request_rx" पूर्ण,
	अणु "tt_response_tx" पूर्ण,
	अणु "tt_response_rx" पूर्ण,
	अणु "tt_roam_adv_tx" पूर्ण,
	अणु "tt_roam_adv_rx" पूर्ण,
#अगर_घोषित CONFIG_BATMAN_ADV_DAT
	अणु "dat_get_tx" पूर्ण,
	अणु "dat_get_rx" पूर्ण,
	अणु "dat_put_tx" पूर्ण,
	अणु "dat_put_rx" पूर्ण,
	अणु "dat_cached_reply_tx" पूर्ण,
#पूर्ण_अगर
#अगर_घोषित CONFIG_BATMAN_ADV_NC
	अणु "nc_code" पूर्ण,
	अणु "nc_code_bytes" पूर्ण,
	अणु "nc_recode" पूर्ण,
	अणु "nc_recode_bytes" पूर्ण,
	अणु "nc_buffer" पूर्ण,
	अणु "nc_decode" पूर्ण,
	अणु "nc_decode_bytes" पूर्ण,
	अणु "nc_decode_failed" पूर्ण,
	अणु "nc_sniffed" पूर्ण,
#पूर्ण_अगर
पूर्ण;

अटल व्योम batadv_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	अगर (stringset == ETH_SS_STATS)
		स_नकल(data, batadv_counters_strings,
		       माप(batadv_counters_strings));
पूर्ण

अटल व्योम batadv_get_ethtool_stats(काष्ठा net_device *dev,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < BATADV_CNT_NUM; i++)
		data[i] = batadv_sum_counter(bat_priv, i);
पूर्ण

अटल पूर्णांक batadv_get_sset_count(काष्ठा net_device *dev, पूर्णांक stringset)
अणु
	अगर (stringset == ETH_SS_STATS)
		वापस BATADV_CNT_NUM;

	वापस -EOPNOTSUPP;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops batadv_ethtool_ops = अणु
	.get_drvinfo = batadv_get_drvinfo,
	.get_link = ethtool_op_get_link,
	.get_strings = batadv_get_strings,
	.get_ethtool_stats = batadv_get_ethtool_stats,
	.get_sset_count = batadv_get_sset_count,
पूर्ण;

/**
 * batadv_softअगर_मुक्त() - Deस्थिरructor of batadv_soft_पूर्णांकerface
 * @dev: Device to cleanup and हटाओ
 */
अटल व्योम batadv_softअगर_मुक्त(काष्ठा net_device *dev)
अणु
	batadv_mesh_मुक्त(dev);

	/* some scheduled RCU callbacks need the bat_priv काष्ठा to accomplish
	 * their tasks. Wait क्रम them all to be finished beक्रमe मुक्तing the
	 * netdev and its निजी data (bat_priv)
	 */
	rcu_barrier();
पूर्ण

/**
 * batadv_softअगर_init_early() - early stage initialization of soft पूर्णांकerface
 * @dev: रेजिस्टरed network device to modअगरy
 */
अटल व्योम batadv_softअगर_init_early(काष्ठा net_device *dev)
अणु
	ether_setup(dev);

	dev->netdev_ops = &batadv_netdev_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = batadv_softअगर_मुक्त;
	dev->features |= NETIF_F_HW_VLAN_CTAG_FILTER | NETIF_F_NETNS_LOCAL;
	dev->features |= NETIF_F_LLTX;
	dev->priv_flags |= IFF_NO_QUEUE;

	/* can't call min_mtu, because the needed variables
	 * have not been initialized yet
	 */
	dev->mtu = ETH_DATA_LEN;

	/* generate अक्रमom address */
	eth_hw_addr_अक्रमom(dev);

	dev->ethtool_ops = &batadv_ethtool_ops;
पूर्ण

/**
 * batadv_softअगर_validate() - validate configuration of new batadv link
 * @tb: IFLA_INFO_DATA netlink attributes
 * @data: क्रमागत batadv_अगरla_attrs attributes
 * @extack: extended ACK report काष्ठा
 *
 * Return: 0 अगर successful or error otherwise.
 */
अटल पूर्णांक batadv_softअगर_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				  काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा batadv_algo_ops *algo_ops;

	अगर (!data)
		वापस 0;

	अगर (data[IFLA_BATADV_ALGO_NAME]) अणु
		algo_ops = batadv_algo_get(nla_data(data[IFLA_BATADV_ALGO_NAME]));
		अगर (!algo_ops)
			वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * batadv_softअगर_newlink() - pre-initialize and रेजिस्टर new batadv link
 * @src_net: the applicable net namespace
 * @dev: network device to रेजिस्टर
 * @tb: IFLA_INFO_DATA netlink attributes
 * @data: क्रमागत batadv_अगरla_attrs attributes
 * @extack: extended ACK report काष्ठा
 *
 * Return: 0 अगर successful or error otherwise.
 */
अटल पूर्णांक batadv_softअगर_newlink(काष्ठा net *src_net, काष्ठा net_device *dev,
				 काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
				 काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(dev);
	स्थिर अक्षर *algo_name;
	पूर्णांक err;

	अगर (data && data[IFLA_BATADV_ALGO_NAME]) अणु
		algo_name = nla_data(data[IFLA_BATADV_ALGO_NAME]);
		err = batadv_algo_select(bat_priv, algo_name);
		अगर (err)
			वापस -EINVAL;
	पूर्ण

	वापस रेजिस्टर_netdevice(dev);
पूर्ण

/**
 * batadv_softअगर_create() - Create and रेजिस्टर soft पूर्णांकerface
 * @net: the applicable net namespace
 * @name: name of the new soft पूर्णांकerface
 *
 * Return: newly allocated soft_पूर्णांकerface, शून्य on errors
 */
काष्ठा net_device *batadv_softअगर_create(काष्ठा net *net, स्थिर अक्षर *name)
अणु
	काष्ठा net_device *soft_अगरace;
	पूर्णांक ret;

	soft_अगरace = alloc_netdev(माप(काष्ठा batadv_priv), name,
				  NET_NAME_UNKNOWN, batadv_softअगर_init_early);
	अगर (!soft_अगरace)
		वापस शून्य;

	dev_net_set(soft_अगरace, net);

	soft_अगरace->rtnl_link_ops = &batadv_link_ops;

	ret = रेजिस्टर_netdevice(soft_अगरace);
	अगर (ret < 0) अणु
		pr_err("Unable to register the batman interface '%s': %i\n",
		       name, ret);
		मुक्त_netdev(soft_अगरace);
		वापस शून्य;
	पूर्ण

	वापस soft_अगरace;
पूर्ण

/**
 * batadv_softअगर_destroy_netlink() - deletion of batadv_soft_पूर्णांकerface via
 *  netlink
 * @soft_अगरace: the to-be-हटाओd baपंचांगan-adv पूर्णांकerface
 * @head: list poपूर्णांकer
 */
अटल व्योम batadv_softअगर_destroy_netlink(काष्ठा net_device *soft_अगरace,
					  काष्ठा list_head *head)
अणु
	काष्ठा batadv_priv *bat_priv = netdev_priv(soft_अगरace);
	काष्ठा batadv_hard_अगरace *hard_अगरace;
	काष्ठा batadv_softअगर_vlan *vlan;

	list_क्रम_each_entry(hard_अगरace, &batadv_hardअगर_list, list) अणु
		अगर (hard_अगरace->soft_अगरace == soft_अगरace)
			batadv_hardअगर_disable_पूर्णांकerface(hard_अगरace);
	पूर्ण

	/* destroy the "untagged" VLAN */
	vlan = batadv_softअगर_vlan_get(bat_priv, BATADV_NO_FLAGS);
	अगर (vlan) अणु
		batadv_softअगर_destroy_vlan(bat_priv, vlan);
		batadv_softअगर_vlan_put(vlan);
	पूर्ण

	unरेजिस्टर_netdevice_queue(soft_अगरace, head);
पूर्ण

/**
 * batadv_softअगर_is_valid() - Check whether device is a batadv soft पूर्णांकerface
 * @net_dev: device which should be checked
 *
 * Return: true when net_dev is a baपंचांगan-adv पूर्णांकerface, false otherwise
 */
bool batadv_softअगर_is_valid(स्थिर काष्ठा net_device *net_dev)
अणु
	अगर (net_dev->netdev_ops->nकरो_start_xmit == batadv_पूर्णांकerface_tx)
		वापस true;

	वापस false;
पूर्ण

अटल स्थिर काष्ठा nla_policy batadv_अगरla_policy[IFLA_BATADV_MAX + 1] = अणु
	[IFLA_BATADV_ALGO_NAME]	= अणु .type = NLA_NUL_STRING पूर्ण,
पूर्ण;

काष्ठा rtnl_link_ops batadv_link_ops __पढ़ो_mostly = अणु
	.kind		= "batadv",
	.priv_size	= माप(काष्ठा batadv_priv),
	.setup		= batadv_softअगर_init_early,
	.maxtype	= IFLA_BATADV_MAX,
	.policy		= batadv_अगरla_policy,
	.validate	= batadv_softअगर_validate,
	.newlink	= batadv_softअगर_newlink,
	.dellink	= batadv_softअगर_destroy_netlink,
पूर्ण;
