<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
   Copyright (c) 2013-2014 Intel Corp.

*/

#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>
#समावेश <linux/debugfs.h>

#समावेश <net/ipv6.h>
#समावेश <net/ip6_route.h>
#समावेश <net/addrconf.h>
#समावेश <net/pkt_sched.h>

#समावेश <net/bluetooth/bluetooth.h>
#समावेश <net/bluetooth/hci_core.h>
#समावेश <net/bluetooth/l2cap.h>

#समावेश <net/6lowpan.h> /* क्रम the compression support */

#घोषणा VERSION "0.1"

अटल काष्ठा dentry *lowpan_enable_debugfs;
अटल काष्ठा dentry *lowpan_control_debugfs;

#घोषणा IFACE_NAME_TEMPLATE "bt%d"

काष्ठा skb_cb अणु
	काष्ठा in6_addr addr;
	काष्ठा in6_addr gw;
	काष्ठा l2cap_chan *chan;
पूर्ण;
#घोषणा lowpan_cb(skb) ((काष्ठा skb_cb *)((skb)->cb))

/* The devices list contains those devices that we are acting
 * as a proxy. The BT 6LoWPAN device is a भव device that
 * connects to the Bluetooth LE device. The real connection to
 * BT device is करोne via l2cap layer. There exists one
 * भव device / one BT 6LoWPAN network (=hciX device).
 * The list contains काष्ठा lowpan_dev elements.
 */
अटल LIST_HEAD(bt_6lowpan_devices);
अटल DEFINE_SPINLOCK(devices_lock);

अटल bool enable_6lowpan;

/* We are listening incoming connections via this channel
 */
अटल काष्ठा l2cap_chan *listen_chan;
अटल DEFINE_MUTEX(set_lock);

काष्ठा lowpan_peer अणु
	काष्ठा list_head list;
	काष्ठा rcu_head rcu;
	काष्ठा l2cap_chan *chan;

	/* peer addresses in various क्रमmats */
	अचिन्हित अक्षर lladdr[ETH_ALEN];
	काष्ठा in6_addr peer_addr;
पूर्ण;

काष्ठा lowpan_btle_dev अणु
	काष्ठा list_head list;

	काष्ठा hci_dev *hdev;
	काष्ठा net_device *netdev;
	काष्ठा list_head peers;
	atomic_t peer_count; /* number of items in peers list */

	काष्ठा work_काष्ठा delete_netdev;
	काष्ठा delayed_work notअगरy_peers;
पूर्ण;

अटल अंतरभूत काष्ठा lowpan_btle_dev *
lowpan_btle_dev(स्थिर काष्ठा net_device *netdev)
अणु
	वापस (काष्ठा lowpan_btle_dev *)lowpan_dev(netdev)->priv;
पूर्ण

अटल अंतरभूत व्योम peer_add(काष्ठा lowpan_btle_dev *dev,
			    काष्ठा lowpan_peer *peer)
अणु
	list_add_rcu(&peer->list, &dev->peers);
	atomic_inc(&dev->peer_count);
पूर्ण

अटल अंतरभूत bool peer_del(काष्ठा lowpan_btle_dev *dev,
			    काष्ठा lowpan_peer *peer)
अणु
	list_del_rcu(&peer->list);
	kमुक्त_rcu(peer, rcu);

	module_put(THIS_MODULE);

	अगर (atomic_dec_and_test(&dev->peer_count)) अणु
		BT_DBG("last peer");
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल अंतरभूत काष्ठा lowpan_peer *peer_lookup_ba(काष्ठा lowpan_btle_dev *dev,
						 bdaddr_t *ba, __u8 type)
अणु
	काष्ठा lowpan_peer *peer;

	BT_DBG("peers %d addr %pMR type %d", atomic_पढ़ो(&dev->peer_count),
	       ba, type);

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(peer, &dev->peers, list) अणु
		BT_DBG("dst addr %pMR dst type %d",
		       &peer->chan->dst, peer->chan->dst_type);

		अगर (bacmp(&peer->chan->dst, ba))
			जारी;

		अगर (type == peer->chan->dst_type) अणु
			rcu_पढ़ो_unlock();
			वापस peer;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा lowpan_peer *
__peer_lookup_chan(काष्ठा lowpan_btle_dev *dev, काष्ठा l2cap_chan *chan)
अणु
	काष्ठा lowpan_peer *peer;

	list_क्रम_each_entry_rcu(peer, &dev->peers, list) अणु
		अगर (peer->chan == chan)
			वापस peer;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा lowpan_peer *
__peer_lookup_conn(काष्ठा lowpan_btle_dev *dev, काष्ठा l2cap_conn *conn)
अणु
	काष्ठा lowpan_peer *peer;

	list_क्रम_each_entry_rcu(peer, &dev->peers, list) अणु
		अगर (peer->chan->conn == conn)
			वापस peer;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल अंतरभूत काष्ठा lowpan_peer *peer_lookup_dst(काष्ठा lowpan_btle_dev *dev,
						  काष्ठा in6_addr *daddr,
						  काष्ठा sk_buff *skb)
अणु
	काष्ठा rt6_info *rt = (काष्ठा rt6_info *)skb_dst(skb);
	पूर्णांक count = atomic_पढ़ो(&dev->peer_count);
	स्थिर काष्ठा in6_addr *nexthop;
	काष्ठा lowpan_peer *peer;
	काष्ठा neighbour *neigh;

	BT_DBG("peers %d addr %pI6c rt %p", count, daddr, rt);

	अगर (!rt) अणु
		अगर (ipv6_addr_any(&lowpan_cb(skb)->gw)) अणु
			/* There is neither route nor gateway,
			 * probably the destination is a direct peer.
			 */
			nexthop = daddr;
		पूर्ण अन्यथा अणु
			/* There is a known gateway
			 */
			nexthop = &lowpan_cb(skb)->gw;
		पूर्ण
	पूर्ण अन्यथा अणु
		nexthop = rt6_nexthop(rt, daddr);

		/* We need to remember the address because it is needed
		 * by bt_xmit() when sending the packet. In bt_xmit(), the
		 * destination routing info is not set.
		 */
		स_नकल(&lowpan_cb(skb)->gw, nexthop, माप(काष्ठा in6_addr));
	पूर्ण

	BT_DBG("gw %pI6c", nexthop);

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(peer, &dev->peers, list) अणु
		BT_DBG("dst addr %pMR dst type %d ip %pI6c",
		       &peer->chan->dst, peer->chan->dst_type,
		       &peer->peer_addr);

		अगर (!ipv6_addr_cmp(&peer->peer_addr, nexthop)) अणु
			rcu_पढ़ो_unlock();
			वापस peer;
		पूर्ण
	पूर्ण

	/* use the neighbour cache क्रम matching addresses asचिन्हित by SLAAC */
	neigh = __ipv6_neigh_lookup(dev->netdev, nexthop);
	अगर (neigh) अणु
		list_क्रम_each_entry_rcu(peer, &dev->peers, list) अणु
			अगर (!स_भेद(neigh->ha, peer->lladdr, ETH_ALEN)) अणु
				neigh_release(neigh);
				rcu_पढ़ो_unlock();
				वापस peer;
			पूर्ण
		पूर्ण
		neigh_release(neigh);
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस शून्य;
पूर्ण

अटल काष्ठा lowpan_peer *lookup_peer(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा lowpan_btle_dev *entry;
	काष्ठा lowpan_peer *peer = शून्य;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(entry, &bt_6lowpan_devices, list) अणु
		peer = __peer_lookup_conn(entry, conn);
		अगर (peer)
			अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस peer;
पूर्ण

अटल काष्ठा lowpan_btle_dev *lookup_dev(काष्ठा l2cap_conn *conn)
अणु
	काष्ठा lowpan_btle_dev *entry;
	काष्ठा lowpan_btle_dev *dev = शून्य;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(entry, &bt_6lowpan_devices, list) अणु
		अगर (conn->hcon->hdev == entry->hdev) अणु
			dev = entry;
			अवरोध;
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस dev;
पूर्ण

अटल पूर्णांक give_skb_to_upper(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा sk_buff *skb_cp;

	skb_cp = skb_copy(skb, GFP_ATOMIC);
	अगर (!skb_cp)
		वापस NET_RX_DROP;

	वापस netअगर_rx_ni(skb_cp);
पूर्ण

अटल पूर्णांक iphc_decompress(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			   काष्ठा lowpan_peer *peer)
अणु
	स्थिर u8 *saddr;

	saddr = peer->lladdr;

	वापस lowpan_header_decompress(skb, netdev, netdev->dev_addr, saddr);
पूर्ण

अटल पूर्णांक recv_pkt(काष्ठा sk_buff *skb, काष्ठा net_device *dev,
		    काष्ठा lowpan_peer *peer)
अणु
	काष्ठा sk_buff *local_skb;
	पूर्णांक ret;

	अगर (!netअगर_running(dev))
		जाओ drop;

	अगर (dev->type != ARPHRD_6LOWPAN || !skb->len)
		जाओ drop;

	skb_reset_network_header(skb);

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (!skb)
		जाओ drop;

	/* check that it's our buffer */
	अगर (lowpan_is_ipv6(*skb_network_header(skb))) अणु
		/* Pull off the 1-byte of 6lowpan header. */
		skb_pull(skb, 1);

		/* Copy the packet so that the IPv6 header is
		 * properly aligned.
		 */
		local_skb = skb_copy_expand(skb, NET_SKB_PAD - 1,
					    skb_tailroom(skb), GFP_ATOMIC);
		अगर (!local_skb)
			जाओ drop;

		local_skb->protocol = htons(ETH_P_IPV6);
		local_skb->pkt_type = PACKET_HOST;
		local_skb->dev = dev;

		skb_set_transport_header(local_skb, माप(काष्ठा ipv6hdr));

		अगर (give_skb_to_upper(local_skb, dev) != NET_RX_SUCCESS) अणु
			kमुक्त_skb(local_skb);
			जाओ drop;
		पूर्ण

		dev->stats.rx_bytes += skb->len;
		dev->stats.rx_packets++;

		consume_skb(local_skb);
		consume_skb(skb);
	पूर्ण अन्यथा अगर (lowpan_is_iphc(*skb_network_header(skb))) अणु
		local_skb = skb_clone(skb, GFP_ATOMIC);
		अगर (!local_skb)
			जाओ drop;

		local_skb->dev = dev;

		ret = iphc_decompress(local_skb, dev, peer);
		अगर (ret < 0) अणु
			BT_DBG("iphc_decompress failed: %d", ret);
			kमुक्त_skb(local_skb);
			जाओ drop;
		पूर्ण

		local_skb->protocol = htons(ETH_P_IPV6);
		local_skb->pkt_type = PACKET_HOST;

		अगर (give_skb_to_upper(local_skb, dev)
				!= NET_RX_SUCCESS) अणु
			kमुक्त_skb(local_skb);
			जाओ drop;
		पूर्ण

		dev->stats.rx_bytes += skb->len;
		dev->stats.rx_packets++;

		consume_skb(local_skb);
		consume_skb(skb);
	पूर्ण अन्यथा अणु
		BT_DBG("unknown packet type");
		जाओ drop;
	पूर्ण

	वापस NET_RX_SUCCESS;

drop:
	dev->stats.rx_dropped++;
	वापस NET_RX_DROP;
पूर्ण

/* Packet from BT LE device */
अटल पूर्णांक chan_recv_cb(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb)
अणु
	काष्ठा lowpan_btle_dev *dev;
	काष्ठा lowpan_peer *peer;
	पूर्णांक err;

	peer = lookup_peer(chan->conn);
	अगर (!peer)
		वापस -ENOENT;

	dev = lookup_dev(chan->conn);
	अगर (!dev || !dev->netdev)
		वापस -ENOENT;

	err = recv_pkt(skb, dev->netdev, peer);
	अगर (err) अणु
		BT_DBG("recv pkt %d", err);
		err = -EAGAIN;
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक setup_header(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			bdaddr_t *peer_addr, u8 *peer_addr_type)
अणु
	काष्ठा in6_addr ipv6_daddr;
	काष्ठा ipv6hdr *hdr;
	काष्ठा lowpan_btle_dev *dev;
	काष्ठा lowpan_peer *peer;
	u8 *daddr;
	पूर्णांक err, status = 0;

	hdr = ipv6_hdr(skb);

	dev = lowpan_btle_dev(netdev);

	स_नकल(&ipv6_daddr, &hdr->daddr, माप(ipv6_daddr));

	अगर (ipv6_addr_is_multicast(&ipv6_daddr)) अणु
		lowpan_cb(skb)->chan = शून्य;
		daddr = शून्य;
	पूर्ण अन्यथा अणु
		BT_DBG("dest IP %pI6c", &ipv6_daddr);

		/* The packet might be sent to 6lowpan पूर्णांकerface
		 * because of routing (either via शेष route
		 * or user set route) so get peer according to
		 * the destination address.
		 */
		peer = peer_lookup_dst(dev, &ipv6_daddr, skb);
		अगर (!peer) अणु
			BT_DBG("no such peer");
			वापस -ENOENT;
		पूर्ण

		daddr = peer->lladdr;
		*peer_addr = peer->chan->dst;
		*peer_addr_type = peer->chan->dst_type;
		lowpan_cb(skb)->chan = peer->chan;

		status = 1;
	पूर्ण

	lowpan_header_compress(skb, netdev, daddr, dev->netdev->dev_addr);

	err = dev_hard_header(skb, netdev, ETH_P_IPV6, शून्य, शून्य, 0);
	अगर (err < 0)
		वापस err;

	वापस status;
पूर्ण

अटल पूर्णांक header_create(काष्ठा sk_buff *skb, काष्ठा net_device *netdev,
			 अचिन्हित लघु type, स्थिर व्योम *_daddr,
			 स्थिर व्योम *_saddr, अचिन्हित पूर्णांक len)
अणु
	अगर (type != ETH_P_IPV6)
		वापस -EINVAL;

	वापस 0;
पूर्ण

/* Packet to BT LE device */
अटल पूर्णांक send_pkt(काष्ठा l2cap_chan *chan, काष्ठा sk_buff *skb,
		    काष्ठा net_device *netdev)
अणु
	काष्ठा msghdr msg;
	काष्ठा kvec iv;
	पूर्णांक err;

	/* Remember the skb so that we can send EAGAIN to the caller अगर
	 * we run out of credits.
	 */
	chan->data = skb;

	iv.iov_base = skb->data;
	iv.iov_len = skb->len;

	स_रखो(&msg, 0, माप(msg));
	iov_iter_kvec(&msg.msg_iter, WRITE, &iv, 1, skb->len);

	err = l2cap_chan_send(chan, &msg, skb->len);
	अगर (err > 0) अणु
		netdev->stats.tx_bytes += err;
		netdev->stats.tx_packets++;
		वापस 0;
	पूर्ण

	अगर (err < 0)
		netdev->stats.tx_errors++;

	वापस err;
पूर्ण

अटल पूर्णांक send_mcast_pkt(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा sk_buff *local_skb;
	काष्ठा lowpan_btle_dev *entry;
	पूर्णांक err = 0;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(entry, &bt_6lowpan_devices, list) अणु
		काष्ठा lowpan_peer *pentry;
		काष्ठा lowpan_btle_dev *dev;

		अगर (entry->netdev != netdev)
			जारी;

		dev = lowpan_btle_dev(entry->netdev);

		list_क्रम_each_entry_rcu(pentry, &dev->peers, list) अणु
			पूर्णांक ret;

			local_skb = skb_clone(skb, GFP_ATOMIC);

			BT_DBG("xmit %s to %pMR type %d IP %pI6c chan %p",
			       netdev->name,
			       &pentry->chan->dst, pentry->chan->dst_type,
			       &pentry->peer_addr, pentry->chan);
			ret = send_pkt(pentry->chan, local_skb, netdev);
			अगर (ret < 0)
				err = ret;

			kमुक्त_skb(local_skb);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल netdev_tx_t bt_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	पूर्णांक err = 0;
	bdaddr_t addr;
	u8 addr_type;

	/* We must take a copy of the skb beक्रमe we modअगरy/replace the ipv6
	 * header as the header could be used अन्यथाwhere
	 */
	skb = skb_unshare(skb, GFP_ATOMIC);
	अगर (!skb)
		वापस NET_XMIT_DROP;

	/* Return values from setup_header()
	 *  <0 - error, packet is dropped
	 *   0 - this is a multicast packet
	 *   1 - this is unicast packet
	 */
	err = setup_header(skb, netdev, &addr, &addr_type);
	अगर (err < 0) अणु
		kमुक्त_skb(skb);
		वापस NET_XMIT_DROP;
	पूर्ण

	अगर (err) अणु
		अगर (lowpan_cb(skb)->chan) अणु
			BT_DBG("xmit %s to %pMR type %d IP %pI6c chan %p",
			       netdev->name, &addr, addr_type,
			       &lowpan_cb(skb)->addr, lowpan_cb(skb)->chan);
			err = send_pkt(lowpan_cb(skb)->chan, skb, netdev);
		पूर्ण अन्यथा अणु
			err = -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* We need to send the packet to every device behind this
		 * पूर्णांकerface.
		 */
		err = send_mcast_pkt(skb, netdev);
	पूर्ण

	dev_kमुक्त_skb(skb);

	अगर (err)
		BT_DBG("ERROR: xmit failed (%d)", err);

	वापस err < 0 ? NET_XMIT_DROP : err;
पूर्ण

अटल पूर्णांक bt_dev_init(काष्ठा net_device *dev)
अणु
	netdev_lockdep_set_classes(dev);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops netdev_ops = अणु
	.nकरो_init		= bt_dev_init,
	.nकरो_start_xmit		= bt_xmit,
पूर्ण;

अटल स्थिर काष्ठा header_ops header_ops = अणु
	.create	= header_create,
पूर्ण;

अटल व्योम netdev_setup(काष्ठा net_device *dev)
अणु
	dev->hard_header_len	= 0;
	dev->needed_tailroom	= 0;
	dev->flags		= IFF_RUNNING | IFF_MULTICAST;
	dev->watchकरोg_समयo	= 0;
	dev->tx_queue_len	= DEFAULT_TX_QUEUE_LEN;

	dev->netdev_ops		= &netdev_ops;
	dev->header_ops		= &header_ops;
	dev->needs_मुक्त_netdev	= true;
पूर्ण

अटल काष्ठा device_type bt_type = अणु
	.name	= "bluetooth",
पूर्ण;

अटल व्योम अगरup(काष्ठा net_device *netdev)
अणु
	पूर्णांक err;

	rtnl_lock();
	err = dev_खोलो(netdev, शून्य);
	अगर (err < 0)
		BT_INFO("iface %s cannot be opened (%d)", netdev->name, err);
	rtnl_unlock();
पूर्ण

अटल व्योम अगरकरोwn(काष्ठा net_device *netdev)
अणु
	rtnl_lock();
	dev_बंद(netdev);
	rtnl_unlock();
पूर्ण

अटल व्योम करो_notअगरy_peers(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lowpan_btle_dev *dev = container_of(work, काष्ठा lowpan_btle_dev,
						   notअगरy_peers.work);

	netdev_notअगरy_peers(dev->netdev); /* send neighbour adv at startup */
पूर्ण

अटल bool is_bt_6lowpan(काष्ठा hci_conn *hcon)
अणु
	अगर (hcon->type != LE_LINK)
		वापस false;

	अगर (!enable_6lowpan)
		वापस false;

	वापस true;
पूर्ण

अटल काष्ठा l2cap_chan *chan_create(व्योम)
अणु
	काष्ठा l2cap_chan *chan;

	chan = l2cap_chan_create();
	अगर (!chan)
		वापस शून्य;

	l2cap_chan_set_शेषs(chan);

	chan->chan_type = L2CAP_CHAN_CONN_ORIENTED;
	chan->mode = L2CAP_MODE_LE_FLOWCTL;
	chan->imtu = 1280;

	वापस chan;
पूर्ण

अटल काष्ठा l2cap_chan *add_peer_chan(काष्ठा l2cap_chan *chan,
					काष्ठा lowpan_btle_dev *dev,
					bool new_netdev)
अणु
	काष्ठा lowpan_peer *peer;

	peer = kzalloc(माप(*peer), GFP_ATOMIC);
	अगर (!peer)
		वापस शून्य;

	peer->chan = chan;
	स_रखो(&peer->peer_addr, 0, माप(काष्ठा in6_addr));

	baswap((व्योम *)peer->lladdr, &chan->dst);

	lowpan_iphc_uncompress_eui48_lladdr(&peer->peer_addr, peer->lladdr);

	spin_lock(&devices_lock);
	INIT_LIST_HEAD(&peer->list);
	peer_add(dev, peer);
	spin_unlock(&devices_lock);

	/* Notअगरying peers about us needs to be करोne without locks held */
	अगर (new_netdev)
		INIT_DELAYED_WORK(&dev->notअगरy_peers, करो_notअगरy_peers);
	schedule_delayed_work(&dev->notअगरy_peers, msecs_to_jअगरfies(100));

	वापस peer->chan;
पूर्ण

अटल पूर्णांक setup_netdev(काष्ठा l2cap_chan *chan, काष्ठा lowpan_btle_dev **dev)
अणु
	काष्ठा net_device *netdev;
	पूर्णांक err = 0;

	netdev = alloc_netdev(LOWPAN_PRIV_SIZE(माप(काष्ठा lowpan_btle_dev)),
			      IFACE_NAME_TEMPLATE, NET_NAME_UNKNOWN,
			      netdev_setup);
	अगर (!netdev)
		वापस -ENOMEM;

	netdev->addr_assign_type = NET_ADDR_PERM;
	baswap((व्योम *)netdev->dev_addr, &chan->src);

	netdev->netdev_ops = &netdev_ops;
	SET_NETDEV_DEV(netdev, &chan->conn->hcon->hdev->dev);
	SET_NETDEV_DEVTYPE(netdev, &bt_type);

	*dev = lowpan_btle_dev(netdev);
	(*dev)->netdev = netdev;
	(*dev)->hdev = chan->conn->hcon->hdev;
	INIT_LIST_HEAD(&(*dev)->peers);

	spin_lock(&devices_lock);
	INIT_LIST_HEAD(&(*dev)->list);
	list_add_rcu(&(*dev)->list, &bt_6lowpan_devices);
	spin_unlock(&devices_lock);

	err = lowpan_रेजिस्टर_netdev(netdev, LOWPAN_LLTYPE_BTLE);
	अगर (err < 0) अणु
		BT_INFO("register_netdev failed %d", err);
		spin_lock(&devices_lock);
		list_del_rcu(&(*dev)->list);
		spin_unlock(&devices_lock);
		मुक्त_netdev(netdev);
		जाओ out;
	पूर्ण

	BT_DBG("ifindex %d peer bdaddr %pMR type %d my addr %pMR type %d",
	       netdev->अगरindex, &chan->dst, chan->dst_type,
	       &chan->src, chan->src_type);
	set_bit(__LINK_STATE_PRESENT, &netdev->state);

	वापस 0;

out:
	वापस err;
पूर्ण

अटल अंतरभूत व्योम chan_पढ़ोy_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा lowpan_btle_dev *dev;
	bool new_netdev = false;

	dev = lookup_dev(chan->conn);

	BT_DBG("chan %p conn %p dev %p", chan, chan->conn, dev);

	अगर (!dev) अणु
		अगर (setup_netdev(chan, &dev) < 0) अणु
			l2cap_chan_del(chan, -ENOENT);
			वापस;
		पूर्ण
		new_netdev = true;
	पूर्ण

	अगर (!try_module_get(THIS_MODULE))
		वापस;

	add_peer_chan(chan, dev, new_netdev);
	अगरup(dev->netdev);
पूर्ण

अटल अंतरभूत काष्ठा l2cap_chan *chan_new_conn_cb(काष्ठा l2cap_chan *pchan)
अणु
	काष्ठा l2cap_chan *chan;

	chan = chan_create();
	अगर (!chan)
		वापस शून्य;

	chan->ops = pchan->ops;

	BT_DBG("chan %p pchan %p", chan, pchan);

	वापस chan;
पूर्ण

अटल व्योम delete_netdev(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा lowpan_btle_dev *entry = container_of(work,
						     काष्ठा lowpan_btle_dev,
						     delete_netdev);

	lowpan_unरेजिस्टर_netdev(entry->netdev);

	/* The entry poपूर्णांकer is deleted by the netdev deकाष्ठाor. */
पूर्ण

अटल व्योम chan_बंद_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा lowpan_btle_dev *entry;
	काष्ठा lowpan_btle_dev *dev = शून्य;
	काष्ठा lowpan_peer *peer;
	पूर्णांक err = -ENOENT;
	bool last = false, हटाओ = true;

	BT_DBG("chan %p conn %p", chan, chan->conn);

	अगर (chan->conn && chan->conn->hcon) अणु
		अगर (!is_bt_6lowpan(chan->conn->hcon))
			वापस;

		/* If conn is set, then the netdev is also there and we should
		 * not हटाओ it.
		 */
		हटाओ = false;
	पूर्ण

	spin_lock(&devices_lock);

	list_क्रम_each_entry_rcu(entry, &bt_6lowpan_devices, list) अणु
		dev = lowpan_btle_dev(entry->netdev);
		peer = __peer_lookup_chan(dev, chan);
		अगर (peer) अणु
			last = peer_del(dev, peer);
			err = 0;

			BT_DBG("dev %p removing %speer %p", dev,
			       last ? "last " : "1 ", peer);
			BT_DBG("chan %p orig refcnt %d", chan,
			       kref_पढ़ो(&chan->kref));

			l2cap_chan_put(chan);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!err && last && dev && !atomic_पढ़ो(&dev->peer_count)) अणु
		spin_unlock(&devices_lock);

		cancel_delayed_work_sync(&dev->notअगरy_peers);

		अगरकरोwn(dev->netdev);

		अगर (हटाओ) अणु
			INIT_WORK(&entry->delete_netdev, delete_netdev);
			schedule_work(&entry->delete_netdev);
		पूर्ण
	पूर्ण अन्यथा अणु
		spin_unlock(&devices_lock);
	पूर्ण
पूर्ण

अटल व्योम chan_state_change_cb(काष्ठा l2cap_chan *chan, पूर्णांक state, पूर्णांक err)
अणु
	BT_DBG("chan %p conn %p state %s err %d", chan, chan->conn,
	       state_to_string(state), err);
पूर्ण

अटल काष्ठा sk_buff *chan_alloc_skb_cb(काष्ठा l2cap_chan *chan,
					 अचिन्हित दीर्घ hdr_len,
					 अचिन्हित दीर्घ len, पूर्णांक nb)
अणु
	/* Note that we must allocate using GFP_ATOMIC here as
	 * this function is called originally from netdev hard xmit
	 * function in atomic context.
	 */
	वापस bt_skb_alloc(hdr_len + len, GFP_ATOMIC);
पूर्ण

अटल व्योम chan_suspend_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा lowpan_btle_dev *dev;

	BT_DBG("chan %p suspend", chan);

	dev = lookup_dev(chan->conn);
	अगर (!dev || !dev->netdev)
		वापस;

	netअगर_stop_queue(dev->netdev);
पूर्ण

अटल व्योम chan_resume_cb(काष्ठा l2cap_chan *chan)
अणु
	काष्ठा lowpan_btle_dev *dev;

	BT_DBG("chan %p resume", chan);

	dev = lookup_dev(chan->conn);
	अगर (!dev || !dev->netdev)
		वापस;

	netअगर_wake_queue(dev->netdev);
पूर्ण

अटल दीर्घ chan_get_sndसमयo_cb(काष्ठा l2cap_chan *chan)
अणु
	वापस L2CAP_CONN_TIMEOUT;
पूर्ण

अटल स्थिर काष्ठा l2cap_ops bt_6lowpan_chan_ops = अणु
	.name			= "L2CAP 6LoWPAN channel",
	.new_connection		= chan_new_conn_cb,
	.recv			= chan_recv_cb,
	.बंद			= chan_बंद_cb,
	.state_change		= chan_state_change_cb,
	.पढ़ोy			= chan_पढ़ोy_cb,
	.resume			= chan_resume_cb,
	.suspend		= chan_suspend_cb,
	.get_sndसमयo		= chan_get_sndसमयo_cb,
	.alloc_skb		= chan_alloc_skb_cb,

	.tearकरोwn		= l2cap_chan_no_tearकरोwn,
	.defer			= l2cap_chan_no_defer,
	.set_shutकरोwn		= l2cap_chan_no_set_shutकरोwn,
पूर्ण;

अटल अंतरभूत __u8 bdaddr_type(__u8 type)
अणु
	अगर (type == ADDR_LE_DEV_PUBLIC)
		वापस BDADDR_LE_PUBLIC;
	अन्यथा
		वापस BDADDR_LE_RANDOM;
पूर्ण

अटल पूर्णांक bt_6lowpan_connect(bdaddr_t *addr, u8 dst_type)
अणु
	काष्ठा l2cap_chan *chan;
	पूर्णांक err;

	chan = chan_create();
	अगर (!chan)
		वापस -EINVAL;

	chan->ops = &bt_6lowpan_chan_ops;

	err = l2cap_chan_connect(chan, cpu_to_le16(L2CAP_PSM_IPSP), 0,
				 addr, dst_type);

	BT_DBG("chan %p err %d", chan, err);
	अगर (err < 0)
		l2cap_chan_put(chan);

	वापस err;
पूर्ण

अटल पूर्णांक bt_6lowpan_disconnect(काष्ठा l2cap_conn *conn, u8 dst_type)
अणु
	काष्ठा lowpan_peer *peer;

	BT_DBG("conn %p dst type %d", conn, dst_type);

	peer = lookup_peer(conn);
	अगर (!peer)
		वापस -ENOENT;

	BT_DBG("peer %p chan %p", peer, peer->chan);

	l2cap_chan_बंद(peer->chan, ENOENT);

	वापस 0;
पूर्ण

अटल काष्ठा l2cap_chan *bt_6lowpan_listen(व्योम)
अणु
	bdaddr_t *addr = BDADDR_ANY;
	काष्ठा l2cap_chan *chan;
	पूर्णांक err;

	अगर (!enable_6lowpan)
		वापस शून्य;

	chan = chan_create();
	अगर (!chan)
		वापस शून्य;

	chan->ops = &bt_6lowpan_chan_ops;
	chan->state = BT_LISTEN;
	chan->src_type = BDADDR_LE_PUBLIC;

	atomic_set(&chan->nesting, L2CAP_NESTING_PARENT);

	BT_DBG("chan %p src type %d", chan, chan->src_type);

	err = l2cap_add_psm(chan, addr, cpu_to_le16(L2CAP_PSM_IPSP));
	अगर (err) अणु
		l2cap_chan_put(chan);
		BT_ERR("psm cannot be added err %d", err);
		वापस शून्य;
	पूर्ण

	वापस chan;
पूर्ण

अटल पूर्णांक get_l2cap_conn(अक्षर *buf, bdaddr_t *addr, u8 *addr_type,
			  काष्ठा l2cap_conn **conn)
अणु
	काष्ठा hci_conn *hcon;
	काष्ठा hci_dev *hdev;
	पूर्णांक n;

	n = माला_पूछो(buf, "%hhx:%hhx:%hhx:%hhx:%hhx:%hhx %hhu",
		   &addr->b[5], &addr->b[4], &addr->b[3],
		   &addr->b[2], &addr->b[1], &addr->b[0],
		   addr_type);

	अगर (n < 7)
		वापस -EINVAL;

	/* The LE_PUBLIC address type is ignored because of BDADDR_ANY */
	hdev = hci_get_route(addr, BDADDR_ANY, BDADDR_LE_PUBLIC);
	अगर (!hdev)
		वापस -ENOENT;

	hci_dev_lock(hdev);
	hcon = hci_conn_hash_lookup_le(hdev, addr, *addr_type);
	hci_dev_unlock(hdev);

	अगर (!hcon)
		वापस -ENOENT;

	*conn = (काष्ठा l2cap_conn *)hcon->l2cap_data;

	BT_DBG("conn %p dst %pMR type %d", *conn, &hcon->dst, hcon->dst_type);

	वापस 0;
पूर्ण

अटल व्योम disconnect_all_peers(व्योम)
अणु
	काष्ठा lowpan_btle_dev *entry;
	काष्ठा lowpan_peer *peer, *पंचांगp_peer, *new_peer;
	काष्ठा list_head peers;

	INIT_LIST_HEAD(&peers);

	/* We make a separate list of peers as the बंद_cb() will
	 * modअगरy the device peers list so it is better not to mess
	 * with the same list at the same समय.
	 */

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(entry, &bt_6lowpan_devices, list) अणु
		list_क्रम_each_entry_rcu(peer, &entry->peers, list) अणु
			new_peer = kदो_स्मृति(माप(*new_peer), GFP_ATOMIC);
			अगर (!new_peer)
				अवरोध;

			new_peer->chan = peer->chan;
			INIT_LIST_HEAD(&new_peer->list);

			list_add(&new_peer->list, &peers);
		पूर्ण
	पूर्ण

	rcu_पढ़ो_unlock();

	spin_lock(&devices_lock);
	list_क्रम_each_entry_safe(peer, पंचांगp_peer, &peers, list) अणु
		l2cap_chan_बंद(peer->chan, ENOENT);

		list_del_rcu(&peer->list);
		kमुक्त_rcu(peer, rcu);
	पूर्ण
	spin_unlock(&devices_lock);
पूर्ण

काष्ठा set_enable अणु
	काष्ठा work_काष्ठा work;
	bool flag;
पूर्ण;

अटल व्योम करो_enable_set(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा set_enable *set_enable = container_of(work,
						     काष्ठा set_enable, work);

	अगर (!set_enable->flag || enable_6lowpan != set_enable->flag)
		/* Disconnect existing connections अगर 6lowpan is
		 * disabled
		 */
		disconnect_all_peers();

	enable_6lowpan = set_enable->flag;

	mutex_lock(&set_lock);
	अगर (listen_chan) अणु
		l2cap_chan_बंद(listen_chan, 0);
		l2cap_chan_put(listen_chan);
	पूर्ण

	listen_chan = bt_6lowpan_listen();
	mutex_unlock(&set_lock);

	kमुक्त(set_enable);
पूर्ण

अटल पूर्णांक lowpan_enable_set(व्योम *data, u64 val)
अणु
	काष्ठा set_enable *set_enable;

	set_enable = kzalloc(माप(*set_enable), GFP_KERNEL);
	अगर (!set_enable)
		वापस -ENOMEM;

	set_enable->flag = !!val;
	INIT_WORK(&set_enable->work, करो_enable_set);

	schedule_work(&set_enable->work);

	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_enable_get(व्योम *data, u64 *val)
अणु
	*val = enable_6lowpan;
	वापस 0;
पूर्ण

DEFINE_DEBUGFS_ATTRIBUTE(lowpan_enable_fops, lowpan_enable_get,
			 lowpan_enable_set, "%llu\n");

अटल sमाप_प्रकार lowpan_control_ग_लिखो(काष्ठा file *fp,
				    स्थिर अक्षर __user *user_buffer,
				    माप_प्रकार count,
				    loff_t *position)
अणु
	अक्षर buf[32];
	माप_प्रकार buf_size = min(count, माप(buf) - 1);
	पूर्णांक ret;
	bdaddr_t addr;
	u8 addr_type;
	काष्ठा l2cap_conn *conn = शून्य;

	अगर (copy_from_user(buf, user_buffer, buf_size))
		वापस -EFAULT;

	buf[buf_size] = '\0';

	अगर (स_भेद(buf, "connect ", 8) == 0) अणु
		ret = get_l2cap_conn(&buf[8], &addr, &addr_type, &conn);
		अगर (ret == -EINVAL)
			वापस ret;

		mutex_lock(&set_lock);
		अगर (listen_chan) अणु
			l2cap_chan_बंद(listen_chan, 0);
			l2cap_chan_put(listen_chan);
			listen_chan = शून्य;
		पूर्ण
		mutex_unlock(&set_lock);

		अगर (conn) अणु
			काष्ठा lowpan_peer *peer;

			अगर (!is_bt_6lowpan(conn->hcon))
				वापस -EINVAL;

			peer = lookup_peer(conn);
			अगर (peer) अणु
				BT_DBG("6LoWPAN connection already exists");
				वापस -EALREADY;
			पूर्ण

			BT_DBG("conn %p dst %pMR type %d user %d", conn,
			       &conn->hcon->dst, conn->hcon->dst_type,
			       addr_type);
		पूर्ण

		ret = bt_6lowpan_connect(&addr, addr_type);
		अगर (ret < 0)
			वापस ret;

		वापस count;
	पूर्ण

	अगर (स_भेद(buf, "disconnect ", 11) == 0) अणु
		ret = get_l2cap_conn(&buf[11], &addr, &addr_type, &conn);
		अगर (ret < 0)
			वापस ret;

		ret = bt_6lowpan_disconnect(conn, addr_type);
		अगर (ret < 0)
			वापस ret;

		वापस count;
	पूर्ण

	वापस count;
पूर्ण

अटल पूर्णांक lowpan_control_show(काष्ठा seq_file *f, व्योम *ptr)
अणु
	काष्ठा lowpan_btle_dev *entry;
	काष्ठा lowpan_peer *peer;

	spin_lock(&devices_lock);

	list_क्रम_each_entry(entry, &bt_6lowpan_devices, list) अणु
		list_क्रम_each_entry(peer, &entry->peers, list)
			seq_म_लिखो(f, "%pMR (type %u)\n",
				   &peer->chan->dst, peer->chan->dst_type);
	पूर्ण

	spin_unlock(&devices_lock);

	वापस 0;
पूर्ण

अटल पूर्णांक lowpan_control_खोलो(काष्ठा inode *inode, काष्ठा file *file)
अणु
	वापस single_खोलो(file, lowpan_control_show, inode->i_निजी);
पूर्ण

अटल स्थिर काष्ठा file_operations lowpan_control_fops = अणु
	.खोलो		= lowpan_control_खोलो,
	.पढ़ो		= seq_पढ़ो,
	.ग_लिखो		= lowpan_control_ग_लिखो,
	.llseek		= seq_lseek,
	.release	= single_release,
पूर्ण;

अटल व्योम disconnect_devices(व्योम)
अणु
	काष्ठा lowpan_btle_dev *entry, *पंचांगp, *new_dev;
	काष्ठा list_head devices;

	INIT_LIST_HEAD(&devices);

	/* We make a separate list of devices because the unरेजिस्टर_netdev()
	 * will call device_event() which will also want to modअगरy the same
	 * devices list.
	 */

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(entry, &bt_6lowpan_devices, list) अणु
		new_dev = kदो_स्मृति(माप(*new_dev), GFP_ATOMIC);
		अगर (!new_dev)
			अवरोध;

		new_dev->netdev = entry->netdev;
		INIT_LIST_HEAD(&new_dev->list);

		list_add_rcu(&new_dev->list, &devices);
	पूर्ण

	rcu_पढ़ो_unlock();

	list_क्रम_each_entry_safe(entry, पंचांगp, &devices, list) अणु
		अगरकरोwn(entry->netdev);
		BT_DBG("Unregistering netdev %s %p",
		       entry->netdev->name, entry->netdev);
		lowpan_unरेजिस्टर_netdev(entry->netdev);
		kमुक्त(entry);
	पूर्ण
पूर्ण

अटल पूर्णांक device_event(काष्ठा notअगरier_block *unused,
			अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *netdev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा lowpan_btle_dev *entry;

	अगर (netdev->type != ARPHRD_6LOWPAN)
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_UNREGISTER:
		spin_lock(&devices_lock);
		list_क्रम_each_entry(entry, &bt_6lowpan_devices, list) अणु
			अगर (entry->netdev == netdev) अणु
				BT_DBG("Unregistered netdev %s %p",
				       netdev->name, netdev);
				list_del(&entry->list);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock(&devices_lock);
		अवरोध;
	पूर्ण

	वापस NOTIFY_DONE;
पूर्ण

अटल काष्ठा notअगरier_block bt_6lowpan_dev_notअगरier = अणु
	.notअगरier_call = device_event,
पूर्ण;

अटल पूर्णांक __init bt_6lowpan_init(व्योम)
अणु
	lowpan_enable_debugfs = debugfs_create_file_unsafe("6lowpan_enable",
							   0644, bt_debugfs,
							   शून्य,
							   &lowpan_enable_fops);
	lowpan_control_debugfs = debugfs_create_file("6lowpan_control", 0644,
						     bt_debugfs, शून्य,
						     &lowpan_control_fops);

	वापस रेजिस्टर_netdevice_notअगरier(&bt_6lowpan_dev_notअगरier);
पूर्ण

अटल व्योम __निकास bt_6lowpan_निकास(व्योम)
अणु
	debugfs_हटाओ(lowpan_enable_debugfs);
	debugfs_हटाओ(lowpan_control_debugfs);

	अगर (listen_chan) अणु
		l2cap_chan_बंद(listen_chan, 0);
		l2cap_chan_put(listen_chan);
	पूर्ण

	disconnect_devices();

	unरेजिस्टर_netdevice_notअगरier(&bt_6lowpan_dev_notअगरier);
पूर्ण

module_init(bt_6lowpan_init);
module_निकास(bt_6lowpan_निकास);

MODULE_AUTHOR("Jukka Rissanen <jukka.rissanen@linux.intel.com>");
MODULE_DESCRIPTION("Bluetooth 6LoWPAN");
MODULE_VERSION(VERSION);
MODULE_LICENSE("GPL");
