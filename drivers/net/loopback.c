<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/*
 * INET		An implementation of the TCP/IP protocol suite क्रम the LINUX
 *		operating प्रणाली.  INET is implemented using the  BSD Socket
 *		पूर्णांकerface as the means of communication with the user level.
 *
 *		Pseuकरो-driver क्रम the loopback पूर्णांकerface.
 *
 * Version:	@(#)loopback.c	1.0.4b	08/16/93
 *
 * Authors:	Ross Biro
 *		Fred N. van Kempen, <waltje@uWalt.NL.Mugnet.ORG>
 *		Donald Becker, <becker@scyld.com>
 *
 *		Alan Cox	:	Fixed oddments क्रम NET3.014
 *		Alan Cox	:	Rejig क्रम NET3.029 snap #3
 *		Alan Cox	:	Fixed NET3.029 bugs and sped up
 *		Larry McVoy	:	Tiny tweak to द्विगुन perक्रमmance
 *		Alan Cox	:	Backed out LMV's tweak - the linux mm
 *					can't take it...
 *              Michael Grअगरfith:       Don't bother computing the checksums
 *                                      on packets received on the loopback
 *                                      पूर्णांकerface.
 *		Alexey Kuznetsov:	Potential hang under some extreme
 *					हालs हटाओd.
 */
#समावेश <linux/kernel.h>
#समावेश <linux/jअगरfies.h>
#समावेश <linux/module.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/fs.h>
#समावेश <linux/types.h>
#समावेश <linux/माला.स>
#समावेश <linux/socket.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/fcntl.h>
#समावेश <linux/in.h>

#समावेश <linux/uaccess.h>
#समावेश <linux/पन.स>

#समावेश <linux/inet.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/ethtool.h>
#समावेश <net/sock.h>
#समावेश <net/checksum.h>
#समावेश <linux/अगर_ether.h>	/* For the statistics काष्ठाure. */
#समावेश <linux/अगर_arp.h>	/* For ARPHRD_ETHER */
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/percpu.h>
#समावेश <linux/net_tstamp.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/u64_stats_sync.h>

/* blackhole_netdev - a device used क्रम dsts that are marked expired!
 * This is global device (instead of per-net-ns) since it's not needed
 * to be per-ns and माला_लो initialized at boot समय.
 */
काष्ठा net_device *blackhole_netdev;
EXPORT_SYMBOL(blackhole_netdev);

/* The higher levels take care of making this non-reentrant (it's
 * called with bh's disabled).
 */
अटल netdev_tx_t loopback_xmit(काष्ठा sk_buff *skb,
				 काष्ठा net_device *dev)
अणु
	पूर्णांक len;

	skb_tx_बारtamp(skb);

	/* करो not fool net_बारtamp_check() with various घड़ी bases */
	skb->tstamp = 0;

	skb_orphan(skb);

	/* Beक्रमe queueing this packet to netअगर_rx(),
	 * make sure dst is refcounted.
	 */
	skb_dst_क्रमce(skb);

	skb->protocol = eth_type_trans(skb, dev);

	len = skb->len;
	अगर (likely(netअगर_rx(skb) == NET_RX_SUCCESS))
		dev_lstats_add(dev, len);

	वापस NETDEV_TX_OK;
पूर्ण

व्योम dev_lstats_पढ़ो(काष्ठा net_device *dev, u64 *packets, u64 *bytes)
अणु
	पूर्णांक i;

	*packets = 0;
	*bytes = 0;

	क्रम_each_possible_cpu(i) अणु
		स्थिर काष्ठा pcpu_lstats *lb_stats;
		u64 tbytes, tpackets;
		अचिन्हित पूर्णांक start;

		lb_stats = per_cpu_ptr(dev->lstats, i);
		करो अणु
			start = u64_stats_fetch_begin_irq(&lb_stats->syncp);
			tpackets = u64_stats_पढ़ो(&lb_stats->packets);
			tbytes = u64_stats_पढ़ो(&lb_stats->bytes);
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&lb_stats->syncp, start));
		*bytes   += tbytes;
		*packets += tpackets;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(dev_lstats_पढ़ो);

अटल व्योम loopback_get_stats64(काष्ठा net_device *dev,
				 काष्ठा rtnl_link_stats64 *stats)
अणु
	u64 packets, bytes;

	dev_lstats_पढ़ो(dev, &packets, &bytes);

	stats->rx_packets = packets;
	stats->tx_packets = packets;
	stats->rx_bytes   = bytes;
	stats->tx_bytes   = bytes;
पूर्ण

अटल u32 always_on(काष्ठा net_device *dev)
अणु
	वापस 1;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops loopback_ethtool_ops = अणु
	.get_link		= always_on,
	.get_ts_info		= ethtool_op_get_ts_info,
पूर्ण;

अटल पूर्णांक loopback_dev_init(काष्ठा net_device *dev)
अणु
	dev->lstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_lstats);
	अगर (!dev->lstats)
		वापस -ENOMEM;
	वापस 0;
पूर्ण

अटल व्योम loopback_dev_मुक्त(काष्ठा net_device *dev)
अणु
	dev_net(dev)->loopback_dev = शून्य;
	मुक्त_percpu(dev->lstats);
पूर्ण

अटल स्थिर काष्ठा net_device_ops loopback_ops = अणु
	.nकरो_init        = loopback_dev_init,
	.nकरो_start_xmit  = loopback_xmit,
	.nकरो_get_stats64 = loopback_get_stats64,
	.nकरो_set_mac_address = eth_mac_addr,
पूर्ण;

अटल व्योम gen_lo_setup(काष्ठा net_device *dev,
			 अचिन्हित पूर्णांक mtu,
			 स्थिर काष्ठा ethtool_ops *eth_ops,
			 स्थिर काष्ठा header_ops *hdr_ops,
			 स्थिर काष्ठा net_device_ops *dev_ops,
			 व्योम (*dev_deकाष्ठाor)(काष्ठा net_device *dev))
अणु
	dev->mtu		= mtu;
	dev->hard_header_len	= ETH_HLEN;	/* 14	*/
	dev->min_header_len	= ETH_HLEN;	/* 14	*/
	dev->addr_len		= ETH_ALEN;	/* 6	*/
	dev->type		= ARPHRD_LOOPBACK;	/* 0x0001*/
	dev->flags		= IFF_LOOPBACK;
	dev->priv_flags		|= IFF_LIVE_ADDR_CHANGE | IFF_NO_QUEUE;
	netअगर_keep_dst(dev);
	dev->hw_features	= NETIF_F_GSO_SOFTWARE;
	dev->features		= NETIF_F_SG | NETIF_F_FRAGLIST
		| NETIF_F_GSO_SOFTWARE
		| NETIF_F_HW_CSUM
		| NETIF_F_RXCSUM
		| NETIF_F_SCTP_CRC
		| NETIF_F_HIGHDMA
		| NETIF_F_LLTX
		| NETIF_F_NETNS_LOCAL
		| NETIF_F_VLAN_CHALLENGED
		| NETIF_F_LOOPBACK;
	dev->ethtool_ops	= eth_ops;
	dev->header_ops		= hdr_ops;
	dev->netdev_ops		= dev_ops;
	dev->needs_मुक्त_netdev	= true;
	dev->priv_deकाष्ठाor	= dev_deकाष्ठाor;
पूर्ण

/* The loopback device is special. There is only one instance
 * per network namespace.
 */
अटल व्योम loopback_setup(काष्ठा net_device *dev)
अणु
	gen_lo_setup(dev, (64 * 1024), &loopback_ethtool_ops, &eth_header_ops,
		     &loopback_ops, loopback_dev_मुक्त);
पूर्ण

/* Setup and रेजिस्टर the loopback device. */
अटल __net_init पूर्णांक loopback_net_init(काष्ठा net *net)
अणु
	काष्ठा net_device *dev;
	पूर्णांक err;

	err = -ENOMEM;
	dev = alloc_netdev(0, "lo", NET_NAME_UNKNOWN, loopback_setup);
	अगर (!dev)
		जाओ out;

	dev_net_set(dev, net);
	err = रेजिस्टर_netdev(dev);
	अगर (err)
		जाओ out_मुक्त_netdev;

	BUG_ON(dev->अगरindex != LOOPBACK_IFINDEX);
	net->loopback_dev = dev;
	वापस 0;

out_मुक्त_netdev:
	मुक्त_netdev(dev);
out:
	अगर (net_eq(net, &init_net))
		panic("loopback: Failed to register netdevice: %d\n", err);
	वापस err;
पूर्ण

/* Registered in net/core/dev.c */
काष्ठा pernet_operations __net_initdata loopback_net_ops = अणु
	.init = loopback_net_init,
पूर्ण;

/* blackhole netdevice */
अटल netdev_tx_t blackhole_netdev_xmit(काष्ठा sk_buff *skb,
					 काष्ठा net_device *dev)
अणु
	kमुक्त_skb(skb);
	net_warn_ratelimited("%s(): Dropping skb.\n", __func__);
	वापस NETDEV_TX_OK;
पूर्ण

अटल स्थिर काष्ठा net_device_ops blackhole_netdev_ops = अणु
	.nकरो_start_xmit = blackhole_netdev_xmit,
पूर्ण;

/* This is a dst-dummy device used specअगरically क्रम invalidated
 * DSTs and unlike loopback, this is not per-ns.
 */
अटल व्योम blackhole_netdev_setup(काष्ठा net_device *dev)
अणु
	gen_lo_setup(dev, ETH_MIN_MTU, शून्य, शून्य, &blackhole_netdev_ops, शून्य);
पूर्ण

/* Setup and रेजिस्टर the blackhole_netdev. */
अटल पूर्णांक __init blackhole_netdev_init(व्योम)
अणु
	blackhole_netdev = alloc_netdev(0, "blackhole_dev", NET_NAME_UNKNOWN,
					blackhole_netdev_setup);
	अगर (!blackhole_netdev)
		वापस -ENOMEM;

	rtnl_lock();
	dev_init_scheduler(blackhole_netdev);
	dev_activate(blackhole_netdev);
	rtnl_unlock();

	blackhole_netdev->flags |= IFF_UP | IFF_RUNNING;
	dev_net_set(blackhole_netdev, &init_net);

	वापस 0;
पूर्ण

device_initcall(blackhole_netdev_init);
