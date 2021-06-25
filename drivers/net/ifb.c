<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* drivers/net/अगरb.c:

	The purpose of this driver is to provide a device that allows
	क्रम sharing of resources:

	1) qdiscs/policies that are per device as opposed to प्रणाली wide.
	अगरb allows क्रम a device which can be redirected to thus providing
	an impression of sharing.

	2) Allows क्रम queueing incoming traffic क्रम shaping instead of
	dropping.

	The original concept is based on what is known as the IMQ
	driver initially written by Martin Devera, later rewritten
	by Patrick McHardy and then मुख्यtained by Andre Correa.

	You need the tc action  mirror or redirect to feed this device
       	packets.


  	Authors:	Jamal Hadi Salim (2005)

*/


#समावेश <linux/module.h>
#समावेश <linux/kernel.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/init.h>
#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/moduleparam.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/net_namespace.h>

#घोषणा TX_Q_LIMIT    32
काष्ठा अगरb_q_निजी अणु
	काष्ठा net_device	*dev;
	काष्ठा tasklet_काष्ठा   अगरb_tasklet;
	पूर्णांक			tasklet_pending;
	पूर्णांक			txqnum;
	काष्ठा sk_buff_head     rq;
	u64			rx_packets;
	u64			rx_bytes;
	काष्ठा u64_stats_sync	rsync;

	काष्ठा u64_stats_sync	tsync;
	u64			tx_packets;
	u64			tx_bytes;
	काष्ठा sk_buff_head     tq;
पूर्ण ____cacheline_aligned_in_smp;

काष्ठा अगरb_dev_निजी अणु
	काष्ठा अगरb_q_निजी *tx_निजी;
पूर्ण;

अटल netdev_tx_t अगरb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev);
अटल पूर्णांक अगरb_खोलो(काष्ठा net_device *dev);
अटल पूर्णांक अगरb_बंद(काष्ठा net_device *dev);

अटल व्योम अगरb_ri_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा अगरb_q_निजी *txp = from_tasklet(txp, t, अगरb_tasklet);
	काष्ठा netdev_queue *txq;
	काष्ठा sk_buff *skb;

	txq = netdev_get_tx_queue(txp->dev, txp->txqnum);
	skb = skb_peek(&txp->tq);
	अगर (!skb) अणु
		अगर (!__netअगर_tx_trylock(txq))
			जाओ resched;
		skb_queue_splice_tail_init(&txp->rq, &txp->tq);
		__netअगर_tx_unlock(txq);
	पूर्ण

	जबतक ((skb = __skb_dequeue(&txp->tq)) != शून्य) अणु
		skb->redirected = 0;
		skb->tc_skip_classअगरy = 1;

		u64_stats_update_begin(&txp->tsync);
		txp->tx_packets++;
		txp->tx_bytes += skb->len;
		u64_stats_update_end(&txp->tsync);

		rcu_पढ़ो_lock();
		skb->dev = dev_get_by_index_rcu(dev_net(txp->dev), skb->skb_iअगर);
		अगर (!skb->dev) अणु
			rcu_पढ़ो_unlock();
			dev_kमुक्त_skb(skb);
			txp->dev->stats.tx_dropped++;
			अगर (skb_queue_len(&txp->tq) != 0)
				जाओ resched;
			अवरोध;
		पूर्ण
		rcu_पढ़ो_unlock();
		skb->skb_iअगर = txp->dev->अगरindex;

		अगर (!skb->from_ingress) अणु
			dev_queue_xmit(skb);
		पूर्ण अन्यथा अणु
			skb_pull_rcsum(skb, skb->mac_len);
			netअगर_receive_skb(skb);
		पूर्ण
	पूर्ण

	अगर (__netअगर_tx_trylock(txq)) अणु
		skb = skb_peek(&txp->rq);
		अगर (!skb) अणु
			txp->tasklet_pending = 0;
			अगर (netअगर_tx_queue_stopped(txq))
				netअगर_tx_wake_queue(txq);
		पूर्ण अन्यथा अणु
			__netअगर_tx_unlock(txq);
			जाओ resched;
		पूर्ण
		__netअगर_tx_unlock(txq);
	पूर्ण अन्यथा अणु
resched:
		txp->tasklet_pending = 1;
		tasklet_schedule(&txp->अगरb_tasklet);
	पूर्ण

पूर्ण

अटल व्योम अगरb_stats64(काष्ठा net_device *dev,
			काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा अगरb_dev_निजी *dp = netdev_priv(dev);
	काष्ठा अगरb_q_निजी *txp = dp->tx_निजी;
	अचिन्हित पूर्णांक start;
	u64 packets, bytes;
	पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++,txp++) अणु
		करो अणु
			start = u64_stats_fetch_begin_irq(&txp->rsync);
			packets = txp->rx_packets;
			bytes = txp->rx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&txp->rsync, start));
		stats->rx_packets += packets;
		stats->rx_bytes += bytes;

		करो अणु
			start = u64_stats_fetch_begin_irq(&txp->tsync);
			packets = txp->tx_packets;
			bytes = txp->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&txp->tsync, start));
		stats->tx_packets += packets;
		stats->tx_bytes += bytes;
	पूर्ण
	stats->rx_dropped = dev->stats.rx_dropped;
	stats->tx_dropped = dev->stats.tx_dropped;
पूर्ण

अटल पूर्णांक अगरb_dev_init(काष्ठा net_device *dev)
अणु
	काष्ठा अगरb_dev_निजी *dp = netdev_priv(dev);
	काष्ठा अगरb_q_निजी *txp;
	पूर्णांक i;

	txp = kसुस्मृति(dev->num_tx_queues, माप(*txp), GFP_KERNEL);
	अगर (!txp)
		वापस -ENOMEM;
	dp->tx_निजी = txp;
	क्रम (i = 0; i < dev->num_tx_queues; i++,txp++) अणु
		txp->txqnum = i;
		txp->dev = dev;
		__skb_queue_head_init(&txp->rq);
		__skb_queue_head_init(&txp->tq);
		u64_stats_init(&txp->rsync);
		u64_stats_init(&txp->tsync);
		tasklet_setup(&txp->अगरb_tasklet, अगरb_ri_tasklet);
		netअगर_tx_start_queue(netdev_get_tx_queue(dev, i));
	पूर्ण
	वापस 0;
पूर्ण

अटल स्थिर काष्ठा net_device_ops अगरb_netdev_ops = अणु
	.nकरो_खोलो	= अगरb_खोलो,
	.nकरो_stop	= अगरb_बंद,
	.nकरो_get_stats64 = अगरb_stats64,
	.nकरो_start_xmit	= अगरb_xmit,
	.nकरो_validate_addr = eth_validate_addr,
	.nकरो_init	= अगरb_dev_init,
पूर्ण;

#घोषणा IFB_FEATURES (NETIF_F_HW_CSUM | NETIF_F_SG  | NETIF_F_FRAGLIST	| \
		      NETIF_F_GSO_SOFTWARE | NETIF_F_GSO_ENCAP_ALL	| \
		      NETIF_F_HIGHDMA | NETIF_F_HW_VLAN_CTAG_TX		| \
		      NETIF_F_HW_VLAN_STAG_TX)

अटल व्योम अगरb_dev_मुक्त(काष्ठा net_device *dev)
अणु
	काष्ठा अगरb_dev_निजी *dp = netdev_priv(dev);
	काष्ठा अगरb_q_निजी *txp = dp->tx_निजी;
	पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++,txp++) अणु
		tasklet_समाप्त(&txp->अगरb_tasklet);
		__skb_queue_purge(&txp->rq);
		__skb_queue_purge(&txp->tq);
	पूर्ण
	kमुक्त(dp->tx_निजी);
पूर्ण

अटल व्योम अगरb_setup(काष्ठा net_device *dev)
अणु
	/* Initialize the device काष्ठाure. */
	dev->netdev_ops = &अगरb_netdev_ops;

	/* Fill in device काष्ठाure with ethernet-generic values. */
	ether_setup(dev);
	dev->tx_queue_len = TX_Q_LIMIT;

	dev->features |= IFB_FEATURES;
	dev->hw_features |= dev->features;
	dev->hw_enc_features |= dev->features;
	dev->vlan_features |= IFB_FEATURES & ~(NETIF_F_HW_VLAN_CTAG_TX |
					       NETIF_F_HW_VLAN_STAG_TX);

	dev->flags |= IFF_NOARP;
	dev->flags &= ~IFF_MULTICAST;
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	netअगर_keep_dst(dev);
	eth_hw_addr_अक्रमom(dev);
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = अगरb_dev_मुक्त;

	dev->min_mtu = 0;
	dev->max_mtu = 0;
पूर्ण

अटल netdev_tx_t अगरb_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा अगरb_dev_निजी *dp = netdev_priv(dev);
	काष्ठा अगरb_q_निजी *txp = dp->tx_निजी + skb_get_queue_mapping(skb);

	u64_stats_update_begin(&txp->rsync);
	txp->rx_packets++;
	txp->rx_bytes += skb->len;
	u64_stats_update_end(&txp->rsync);

	अगर (!skb->redirected || !skb->skb_iअगर) अणु
		dev_kमुक्त_skb(skb);
		dev->stats.rx_dropped++;
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (skb_queue_len(&txp->rq) >= dev->tx_queue_len)
		netअगर_tx_stop_queue(netdev_get_tx_queue(dev, txp->txqnum));

	__skb_queue_tail(&txp->rq, skb);
	अगर (!txp->tasklet_pending) अणु
		txp->tasklet_pending = 1;
		tasklet_schedule(&txp->अगरb_tasklet);
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक अगरb_बंद(काष्ठा net_device *dev)
अणु
	netअगर_tx_stop_all_queues(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक अगरb_खोलो(काष्ठा net_device *dev)
अणु
	netअगर_tx_start_all_queues(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक अगरb_validate(काष्ठा nlattr *tb[], काष्ठा nlattr *data[],
			काष्ठा netlink_ext_ack *extack)
अणु
	अगर (tb[IFLA_ADDRESS]) अणु
		अगर (nla_len(tb[IFLA_ADDRESS]) != ETH_ALEN)
			वापस -EINVAL;
		अगर (!is_valid_ether_addr(nla_data(tb[IFLA_ADDRESS])))
			वापस -EADDRNOTAVAIL;
	पूर्ण
	वापस 0;
पूर्ण

अटल काष्ठा rtnl_link_ops अगरb_link_ops __पढ़ो_mostly = अणु
	.kind		= "ifb",
	.priv_size	= माप(काष्ठा अगरb_dev_निजी),
	.setup		= अगरb_setup,
	.validate	= अगरb_validate,
पूर्ण;

/* Number of अगरb devices to be set up by this module.
 * Note that these legacy devices have one queue.
 * Prefer something like : ip link add अगरb10 numtxqueues 8 type अगरb
 */
अटल पूर्णांक numअगरbs = 2;
module_param(numअगरbs, पूर्णांक, 0);
MODULE_PARM_DESC(numअगरbs, "Number of ifb devices");

अटल पूर्णांक __init अगरb_init_one(पूर्णांक index)
अणु
	काष्ठा net_device *dev_अगरb;
	पूर्णांक err;

	dev_अगरb = alloc_netdev(माप(काष्ठा अगरb_dev_निजी), "ifb%d",
			       NET_NAME_UNKNOWN, अगरb_setup);

	अगर (!dev_अगरb)
		वापस -ENOMEM;

	dev_अगरb->rtnl_link_ops = &अगरb_link_ops;
	err = रेजिस्टर_netdevice(dev_अगरb);
	अगर (err < 0)
		जाओ err;

	वापस 0;

err:
	मुक्त_netdev(dev_अगरb);
	वापस err;
पूर्ण

अटल पूर्णांक __init अगरb_init_module(व्योम)
अणु
	पूर्णांक i, err;

	करोwn_ग_लिखो(&pernet_ops_rwsem);
	rtnl_lock();
	err = __rtnl_link_रेजिस्टर(&अगरb_link_ops);
	अगर (err < 0)
		जाओ out;

	क्रम (i = 0; i < numअगरbs && !err; i++) अणु
		err = अगरb_init_one(i);
		cond_resched();
	पूर्ण
	अगर (err)
		__rtnl_link_unरेजिस्टर(&अगरb_link_ops);

out:
	rtnl_unlock();
	up_ग_लिखो(&pernet_ops_rwsem);

	वापस err;
पूर्ण

अटल व्योम __निकास अगरb_cleanup_module(व्योम)
अणु
	rtnl_link_unरेजिस्टर(&अगरb_link_ops);
पूर्ण

module_init(अगरb_init_module);
module_निकास(अगरb_cleanup_module);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Jamal Hadi Salim");
MODULE_ALIAS_RTNL_LINK("ifb");
