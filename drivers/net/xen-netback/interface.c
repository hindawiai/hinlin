<शैली गुरु>
/*
 * Network-device पूर्णांकerface management.
 *
 * Copyright (c) 2004-2005, Keir Fraser
 *
 * This program is मुक्त software; you can redistribute it and/or
 * modअगरy it under the terms of the GNU General Public License version 2
 * as published by the Free Software Foundation; or, when distributed
 * separately from the Linux kernel or incorporated पूर्णांकo other
 * software packages, subject to the following license:
 *
 * Permission is hereby granted, मुक्त of अक्षरge, to any person obtaining a copy
 * of this source file (the "Software"), to deal in the Software without
 * restriction, including without limitation the rights to use, copy, modअगरy,
 * merge, publish, distribute, sublicense, and/or sell copies of the Software,
 * and to permit persons to whom the Software is furnished to करो so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#समावेश "common.h"

#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/sched/task.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/vदो_स्मृति.h>

#समावेश <xen/events.h>
#समावेश <यंत्र/xen/hypercall.h>
#समावेश <xen/balloon.h>

#घोषणा XENVIF_QUEUE_LENGTH 32
#घोषणा XENVIF_NAPI_WEIGHT  64

/* Number of bytes allowed on the पूर्णांकernal guest Rx queue. */
#घोषणा XENVIF_RX_QUEUE_BYTES (XEN_NETIF_RX_RING_SIZE/2 * PAGE_SIZE)

/* This function is used to set SKBFL_ZEROCOPY_ENABLE as well as
 * increasing the inflight counter. We need to increase the inflight
 * counter because core driver calls पूर्णांकo xenvअगर_zerocopy_callback
 * which calls xenvअगर_skb_zerocopy_complete.
 */
व्योम xenvअगर_skb_zerocopy_prepare(काष्ठा xenvअगर_queue *queue,
				 काष्ठा sk_buff *skb)
अणु
	skb_shinfo(skb)->flags |= SKBFL_ZEROCOPY_ENABLE;
	atomic_inc(&queue->inflight_packets);
पूर्ण

व्योम xenvअगर_skb_zerocopy_complete(काष्ठा xenvअगर_queue *queue)
अणु
	atomic_dec(&queue->inflight_packets);

	/* Wake the dealloc thपढ़ो _after_ decrementing inflight_packets so
	 * that अगर kthपढ़ो_stop() has alपढ़ोy been called, the dealloc thपढ़ो
	 * करोes not रुको क्रमever with nothing to wake it.
	 */
	wake_up(&queue->dealloc_wq);
पूर्ण

पूर्णांक xenvअगर_schedulable(काष्ठा xenvअगर *vअगर)
अणु
	वापस netअगर_running(vअगर->dev) &&
		test_bit(VIF_STATUS_CONNECTED, &vअगर->status) &&
		!vअगर->disabled;
पूर्ण

अटल bool xenvअगर_handle_tx_पूर्णांकerrupt(काष्ठा xenvअगर_queue *queue)
अणु
	bool rc;

	rc = RING_HAS_UNCONSUMED_REQUESTS(&queue->tx);
	अगर (rc)
		napi_schedule(&queue->napi);
	वापस rc;
पूर्ण

अटल irqवापस_t xenvअगर_tx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xenvअगर_queue *queue = dev_id;
	पूर्णांक old;

	old = atomic_fetch_or(NETBK_TX_EOI, &queue->eoi_pending);
	WARN(old & NETBK_TX_EOI, "Interrupt while EOI pending\n");

	अगर (!xenvअगर_handle_tx_पूर्णांकerrupt(queue)) अणु
		atomic_andnot(NETBK_TX_EOI, &queue->eoi_pending);
		xen_irq_lateeoi(irq, XEN_EOI_FLAG_SPURIOUS);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल पूर्णांक xenvअगर_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा xenvअगर_queue *queue =
		container_of(napi, काष्ठा xenvअगर_queue, napi);
	पूर्णांक work_करोne;

	/* This vअगर is rogue, we pretend we've there is nothing to करो
	 * क्रम this vअगर to deschedule it from NAPI. But this पूर्णांकerface
	 * will be turned off in thपढ़ो context later.
	 */
	अगर (unlikely(queue->vअगर->disabled)) अणु
		napi_complete(napi);
		वापस 0;
	पूर्ण

	work_करोne = xenvअगर_tx_action(queue, budget);

	अगर (work_करोne < budget) अणु
		napi_complete_करोne(napi, work_करोne);
		/* If the queue is rate-limited, it shall be
		 * rescheduled in the समयr callback.
		 */
		अगर (likely(!queue->rate_limited))
			xenvअगर_napi_schedule_or_enable_events(queue);
	पूर्ण

	वापस work_करोne;
पूर्ण

अटल bool xenvअगर_handle_rx_पूर्णांकerrupt(काष्ठा xenvअगर_queue *queue)
अणु
	bool rc;

	rc = xenvअगर_have_rx_work(queue, false);
	अगर (rc)
		xenvअगर_kick_thपढ़ो(queue);
	वापस rc;
पूर्ण

अटल irqवापस_t xenvअगर_rx_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xenvअगर_queue *queue = dev_id;
	पूर्णांक old;

	old = atomic_fetch_or(NETBK_RX_EOI, &queue->eoi_pending);
	WARN(old & NETBK_RX_EOI, "Interrupt while EOI pending\n");

	अगर (!xenvअगर_handle_rx_पूर्णांकerrupt(queue)) अणु
		atomic_andnot(NETBK_RX_EOI, &queue->eoi_pending);
		xen_irq_lateeoi(irq, XEN_EOI_FLAG_SPURIOUS);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

irqवापस_t xenvअगर_पूर्णांकerrupt(पूर्णांक irq, व्योम *dev_id)
अणु
	काष्ठा xenvअगर_queue *queue = dev_id;
	पूर्णांक old;
	bool has_rx, has_tx;

	old = atomic_fetch_or(NETBK_COMMON_EOI, &queue->eoi_pending);
	WARN(old, "Interrupt while EOI pending\n");

	has_tx = xenvअगर_handle_tx_पूर्णांकerrupt(queue);
	has_rx = xenvअगर_handle_rx_पूर्णांकerrupt(queue);

	अगर (!has_rx && !has_tx) अणु
		atomic_andnot(NETBK_COMMON_EOI, &queue->eoi_pending);
		xen_irq_lateeoi(irq, XEN_EOI_FLAG_SPURIOUS);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

पूर्णांक xenvअगर_queue_stopped(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा net_device *dev = queue->vअगर->dev;
	अचिन्हित पूर्णांक id = queue->id;
	वापस netअगर_tx_queue_stopped(netdev_get_tx_queue(dev, id));
पूर्ण

व्योम xenvअगर_wake_queue(काष्ठा xenvअगर_queue *queue)
अणु
	काष्ठा net_device *dev = queue->vअगर->dev;
	अचिन्हित पूर्णांक id = queue->id;
	netअगर_tx_wake_queue(netdev_get_tx_queue(dev, id));
पूर्ण

अटल u16 xenvअगर_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
			       काष्ठा net_device *sb_dev)
अणु
	काष्ठा xenvअगर *vअगर = netdev_priv(dev);
	अचिन्हित पूर्णांक size = vअगर->hash.size;
	अचिन्हित पूर्णांक num_queues;

	/* If queues are not set up पूर्णांकernally - always वापस 0
	 * as the packet going to be dropped anyway */
	num_queues = READ_ONCE(vअगर->num_queues);
	अगर (num_queues < 1)
		वापस 0;

	अगर (vअगर->hash.alg == XEN_NETIF_CTRL_HASH_ALGORITHM_NONE)
		वापस netdev_pick_tx(dev, skb, शून्य) %
		       dev->real_num_tx_queues;

	xenvअगर_set_skb_hash(vअगर, skb);

	अगर (size == 0)
		वापस skb_get_hash_raw(skb) % dev->real_num_tx_queues;

	वापस vअगर->hash.mapping[vअगर->hash.mapping_sel]
				[skb_get_hash_raw(skb) % size];
पूर्ण

अटल netdev_tx_t
xenvअगर_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा xenvअगर *vअगर = netdev_priv(dev);
	काष्ठा xenvअगर_queue *queue = शून्य;
	अचिन्हित पूर्णांक num_queues;
	u16 index;
	काष्ठा xenvअगर_rx_cb *cb;

	BUG_ON(skb->dev != dev);

	/* Drop the packet अगर queues are not set up.
	 * This handler should be called inside an RCU पढ़ो section
	 * so we करोn't need to enter it here explicitly.
	 */
	num_queues = READ_ONCE(vअगर->num_queues);
	अगर (num_queues < 1)
		जाओ drop;

	/* Obtain the queue to be used to transmit this packet */
	index = skb_get_queue_mapping(skb);
	अगर (index >= num_queues) अणु
		pr_warn_ratelimited("Invalid queue %hu for packet on interface %s\n",
				    index, vअगर->dev->name);
		index %= num_queues;
	पूर्ण
	queue = &vअगर->queues[index];

	/* Drop the packet अगर queue is not पढ़ोy */
	अगर (queue->task == शून्य ||
	    queue->dealloc_task == शून्य ||
	    !xenvअगर_schedulable(vअगर))
		जाओ drop;

	अगर (vअगर->multicast_control && skb->pkt_type == PACKET_MULTICAST) अणु
		काष्ठा ethhdr *eth = (काष्ठा ethhdr *)skb->data;

		अगर (!xenvअगर_mcast_match(vअगर, eth->h_dest))
			जाओ drop;
	पूर्ण

	cb = XENVIF_RX_CB(skb);
	cb->expires = jअगरfies + vअगर->drain_समयout;

	/* If there is no hash algorithm configured then make sure there
	 * is no hash inक्रमmation in the socket buffer otherwise it
	 * would be incorrectly क्रमwarded to the frontend.
	 */
	अगर (vअगर->hash.alg == XEN_NETIF_CTRL_HASH_ALGORITHM_NONE)
		skb_clear_hash(skb);

	xenvअगर_rx_queue_tail(queue, skb);
	xenvअगर_kick_thपढ़ो(queue);

	वापस NETDEV_TX_OK;

 drop:
	vअगर->dev->stats.tx_dropped++;
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल काष्ठा net_device_stats *xenvअगर_get_stats(काष्ठा net_device *dev)
अणु
	काष्ठा xenvअगर *vअगर = netdev_priv(dev);
	काष्ठा xenvअगर_queue *queue = शून्य;
	अचिन्हित पूर्णांक num_queues;
	u64 rx_bytes = 0;
	u64 rx_packets = 0;
	u64 tx_bytes = 0;
	u64 tx_packets = 0;
	अचिन्हित पूर्णांक index;

	rcu_पढ़ो_lock();
	num_queues = READ_ONCE(vअगर->num_queues);

	/* Aggregate tx and rx stats from each queue */
	क्रम (index = 0; index < num_queues; ++index) अणु
		queue = &vअगर->queues[index];
		rx_bytes += queue->stats.rx_bytes;
		rx_packets += queue->stats.rx_packets;
		tx_bytes += queue->stats.tx_bytes;
		tx_packets += queue->stats.tx_packets;
	पूर्ण

	rcu_पढ़ो_unlock();

	vअगर->dev->stats.rx_bytes = rx_bytes;
	vअगर->dev->stats.rx_packets = rx_packets;
	vअगर->dev->stats.tx_bytes = tx_bytes;
	vअगर->dev->stats.tx_packets = tx_packets;

	वापस &vअगर->dev->stats;
पूर्ण

अटल व्योम xenvअगर_up(काष्ठा xenvअगर *vअगर)
अणु
	काष्ठा xenvअगर_queue *queue = शून्य;
	अचिन्हित पूर्णांक num_queues = vअगर->num_queues;
	अचिन्हित पूर्णांक queue_index;

	क्रम (queue_index = 0; queue_index < num_queues; ++queue_index) अणु
		queue = &vअगर->queues[queue_index];
		napi_enable(&queue->napi);
		enable_irq(queue->tx_irq);
		अगर (queue->tx_irq != queue->rx_irq)
			enable_irq(queue->rx_irq);
		xenvअगर_napi_schedule_or_enable_events(queue);
	पूर्ण
पूर्ण

अटल व्योम xenvअगर_करोwn(काष्ठा xenvअगर *vअगर)
अणु
	काष्ठा xenvअगर_queue *queue = शून्य;
	अचिन्हित पूर्णांक num_queues = vअगर->num_queues;
	अचिन्हित पूर्णांक queue_index;

	क्रम (queue_index = 0; queue_index < num_queues; ++queue_index) अणु
		queue = &vअगर->queues[queue_index];
		disable_irq(queue->tx_irq);
		अगर (queue->tx_irq != queue->rx_irq)
			disable_irq(queue->rx_irq);
		napi_disable(&queue->napi);
		del_समयr_sync(&queue->credit_समयout);
	पूर्ण
पूर्ण

अटल पूर्णांक xenvअगर_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा xenvअगर *vअगर = netdev_priv(dev);
	अगर (test_bit(VIF_STATUS_CONNECTED, &vअगर->status))
		xenvअगर_up(vअगर);
	netअगर_tx_start_all_queues(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक xenvअगर_बंद(काष्ठा net_device *dev)
अणु
	काष्ठा xenvअगर *vअगर = netdev_priv(dev);
	अगर (test_bit(VIF_STATUS_CONNECTED, &vअगर->status))
		xenvअगर_करोwn(vअगर);
	netअगर_tx_stop_all_queues(dev);
	वापस 0;
पूर्ण

अटल पूर्णांक xenvअगर_change_mtu(काष्ठा net_device *dev, पूर्णांक mtu)
अणु
	काष्ठा xenvअगर *vअगर = netdev_priv(dev);
	पूर्णांक max = vअगर->can_sg ? ETH_MAX_MTU - VLAN_ETH_HLEN : ETH_DATA_LEN;

	अगर (mtu > max)
		वापस -EINVAL;
	dev->mtu = mtu;
	वापस 0;
पूर्ण

अटल netdev_features_t xenvअगर_fix_features(काष्ठा net_device *dev,
	netdev_features_t features)
अणु
	काष्ठा xenvअगर *vअगर = netdev_priv(dev);

	अगर (!vअगर->can_sg)
		features &= ~NETIF_F_SG;
	अगर (~(vअगर->gso_mask) & GSO_BIT(TCPV4))
		features &= ~NETIF_F_TSO;
	अगर (~(vअगर->gso_mask) & GSO_BIT(TCPV6))
		features &= ~NETIF_F_TSO6;
	अगर (!vअगर->ip_csum)
		features &= ~NETIF_F_IP_CSUM;
	अगर (!vअगर->ipv6_csum)
		features &= ~NETIF_F_IPV6_CSUM;

	वापस features;
पूर्ण

अटल स्थिर काष्ठा xenvअगर_stat अणु
	अक्षर name[ETH_GSTRING_LEN];
	u16 offset;
पूर्ण xenvअगर_stats[] = अणु
	अणु
		"rx_gso_checksum_fixup",
		दुरत्व(काष्ठा xenvअगर_stats, rx_gso_checksum_fixup)
	पूर्ण,
	/* If (sent != success + fail), there are probably packets never
	 * मुक्तd up properly!
	 */
	अणु
		"tx_zerocopy_sent",
		दुरत्व(काष्ठा xenvअगर_stats, tx_zerocopy_sent),
	पूर्ण,
	अणु
		"tx_zerocopy_success",
		दुरत्व(काष्ठा xenvअगर_stats, tx_zerocopy_success),
	पूर्ण,
	अणु
		"tx_zerocopy_fail",
		दुरत्व(काष्ठा xenvअगर_stats, tx_zerocopy_fail)
	पूर्ण,
	/* Number of packets exceeding MAX_SKB_FRAG slots. You should use
	 * a guest with the same MAX_SKB_FRAG
	 */
	अणु
		"tx_frag_overflow",
		दुरत्व(काष्ठा xenvअगर_stats, tx_frag_overflow)
	पूर्ण,
पूर्ण;

अटल पूर्णांक xenvअगर_get_sset_count(काष्ठा net_device *dev, पूर्णांक string_set)
अणु
	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस ARRAY_SIZE(xenvअगर_stats);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम xenvअगर_get_ethtool_stats(काष्ठा net_device *dev,
				     काष्ठा ethtool_stats *stats, u64 * data)
अणु
	काष्ठा xenvअगर *vअगर = netdev_priv(dev);
	अचिन्हित पूर्णांक num_queues;
	पूर्णांक i;
	अचिन्हित पूर्णांक queue_index;

	rcu_पढ़ो_lock();
	num_queues = READ_ONCE(vअगर->num_queues);

	क्रम (i = 0; i < ARRAY_SIZE(xenvअगर_stats); i++) अणु
		अचिन्हित दीर्घ accum = 0;
		क्रम (queue_index = 0; queue_index < num_queues; ++queue_index) अणु
			व्योम *vअगर_stats = &vअगर->queues[queue_index].stats;
			accum += *(अचिन्हित दीर्घ *)(vअगर_stats + xenvअगर_stats[i].offset);
		पूर्ण
		data[i] = accum;
	पूर्ण

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम xenvअगर_get_strings(काष्ठा net_device *dev, u32 stringset, u8 * data)
अणु
	पूर्णांक i;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(xenvअगर_stats); i++)
			स_नकल(data + i * ETH_GSTRING_LEN,
			       xenvअगर_stats[i].name, ETH_GSTRING_LEN);
		अवरोध;
	पूर्ण
पूर्ण

अटल स्थिर काष्ठा ethtool_ops xenvअगर_ethtool_ops = अणु
	.get_link	= ethtool_op_get_link,

	.get_sset_count = xenvअगर_get_sset_count,
	.get_ethtool_stats = xenvअगर_get_ethtool_stats,
	.get_strings = xenvअगर_get_strings,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops xenvअगर_netdev_ops = अणु
	.nकरो_select_queue = xenvअगर_select_queue,
	.nकरो_start_xmit	= xenvअगर_start_xmit,
	.nकरो_get_stats	= xenvअगर_get_stats,
	.nकरो_खोलो	= xenvअगर_खोलो,
	.nकरो_stop	= xenvअगर_बंद,
	.nकरो_change_mtu	= xenvअगर_change_mtu,
	.nकरो_fix_features = xenvअगर_fix_features,
	.nकरो_set_mac_address = eth_mac_addr,
	.nकरो_validate_addr   = eth_validate_addr,
पूर्ण;

काष्ठा xenvअगर *xenvअगर_alloc(काष्ठा device *parent, करोmid_t करोmid,
			    अचिन्हित पूर्णांक handle)
अणु
	पूर्णांक err;
	काष्ठा net_device *dev;
	काष्ठा xenvअगर *vअगर;
	अक्षर name[IFNAMSIZ] = अणुपूर्ण;

	snम_लिखो(name, IFNAMSIZ - 1, "vif%u.%u", करोmid, handle);
	/* Allocate a netdev with the max. supported number of queues.
	 * When the guest selects the desired number, it will be updated
	 * via netअगर_set_real_num_*_queues().
	 */
	dev = alloc_netdev_mq(माप(काष्ठा xenvअगर), name, NET_NAME_UNKNOWN,
			      ether_setup, xenvअगर_max_queues);
	अगर (dev == शून्य) अणु
		pr_warn("Could not allocate netdev for %s\n", name);
		वापस ERR_PTR(-ENOMEM);
	पूर्ण

	SET_NETDEV_DEV(dev, parent);

	vअगर = netdev_priv(dev);

	vअगर->करोmid  = करोmid;
	vअगर->handle = handle;
	vअगर->can_sg = 1;
	vअगर->ip_csum = 1;
	vअगर->dev = dev;
	vअगर->disabled = false;
	vअगर->drain_समयout = msecs_to_jअगरfies(rx_drain_समयout_msecs);
	vअगर->stall_समयout = msecs_to_jअगरfies(rx_stall_समयout_msecs);

	/* Start out with no queues. */
	vअगर->queues = शून्य;
	vअगर->num_queues = 0;

	vअगर->xdp_headroom = 0;

	spin_lock_init(&vअगर->lock);
	INIT_LIST_HEAD(&vअगर->fe_mcast_addr);

	dev->netdev_ops	= &xenvअगर_netdev_ops;
	dev->hw_features = NETIF_F_SG |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_FRAGLIST;
	dev->features = dev->hw_features | NETIF_F_RXCSUM;
	dev->ethtool_ops = &xenvअगर_ethtool_ops;

	dev->tx_queue_len = XENVIF_QUEUE_LENGTH;

	dev->min_mtu = ETH_MIN_MTU;
	dev->max_mtu = ETH_MAX_MTU - VLAN_ETH_HLEN;

	/*
	 * Initialise a dummy MAC address. We choose the numerically
	 * largest non-broadcast address to prevent the address getting
	 * stolen by an Ethernet bridge क्रम STP purposes.
	 * (FE:FF:FF:FF:FF:FF)
	 */
	eth_broadcast_addr(dev->dev_addr);
	dev->dev_addr[0] &= ~0x01;

	netअगर_carrier_off(dev);

	err = रेजिस्टर_netdev(dev);
	अगर (err) अणु
		netdev_warn(dev, "Could not register device: err=%d\n", err);
		मुक्त_netdev(dev);
		वापस ERR_PTR(err);
	पूर्ण

	netdev_dbg(dev, "Successfully created xenvif\n");

	__module_get(THIS_MODULE);

	वापस vअगर;
पूर्ण

पूर्णांक xenvअगर_init_queue(काष्ठा xenvअगर_queue *queue)
अणु
	पूर्णांक err, i;

	queue->credit_bytes = queue->reमुख्यing_credit = ~0UL;
	queue->credit_usec  = 0UL;
	समयr_setup(&queue->credit_समयout, xenvअगर_tx_credit_callback, 0);
	queue->credit_winकरोw_start = get_jअगरfies_64();

	queue->rx_queue_max = XENVIF_RX_QUEUE_BYTES;

	skb_queue_head_init(&queue->rx_queue);
	skb_queue_head_init(&queue->tx_queue);

	queue->pending_cons = 0;
	queue->pending_prod = MAX_PENDING_REQS;
	क्रम (i = 0; i < MAX_PENDING_REQS; ++i)
		queue->pending_ring[i] = i;

	spin_lock_init(&queue->callback_lock);
	spin_lock_init(&queue->response_lock);

	/* If ballooning is disabled, this will consume real memory, so you
	 * better enable it. The दीर्घ term solution would be to use just a
	 * bunch of valid page descriptors, without dependency on ballooning
	 */
	err = gnttab_alloc_pages(MAX_PENDING_REQS,
				 queue->mmap_pages);
	अगर (err) अणु
		netdev_err(queue->vअगर->dev, "Could not reserve mmap_pages\n");
		वापस -ENOMEM;
	पूर्ण

	क्रम (i = 0; i < MAX_PENDING_REQS; i++) अणु
		queue->pending_tx_info[i].callback_काष्ठा = (काष्ठा ubuf_info)
			अणु .callback = xenvअगर_zerocopy_callback,
			  अणु अणु .ctx = शून्य,
			      .desc = i पूर्ण पूर्ण पूर्ण;
		queue->grant_tx_handle[i] = NETBACK_INVALID_HANDLE;
	पूर्ण

	वापस 0;
पूर्ण

व्योम xenvअगर_carrier_on(काष्ठा xenvअगर *vअगर)
अणु
	rtnl_lock();
	अगर (!vअगर->can_sg && vअगर->dev->mtu > ETH_DATA_LEN)
		dev_set_mtu(vअगर->dev, ETH_DATA_LEN);
	netdev_update_features(vअगर->dev);
	set_bit(VIF_STATUS_CONNECTED, &vअगर->status);
	अगर (netअगर_running(vअगर->dev))
		xenvअगर_up(vअगर);
	rtnl_unlock();
पूर्ण

पूर्णांक xenvअगर_connect_ctrl(काष्ठा xenvअगर *vअगर, grant_ref_t ring_ref,
			अचिन्हित पूर्णांक evtchn)
अणु
	काष्ठा net_device *dev = vअगर->dev;
	काष्ठा xenbus_device *xendev = xenvअगर_to_xenbus_device(vअगर);
	व्योम *addr;
	काष्ठा xen_netअगर_ctrl_sring *shared;
	RING_IDX rsp_prod, req_prod;
	पूर्णांक err;

	err = xenbus_map_ring_valloc(xendev, &ring_ref, 1, &addr);
	अगर (err)
		जाओ err;

	shared = (काष्ठा xen_netअगर_ctrl_sring *)addr;
	rsp_prod = READ_ONCE(shared->rsp_prod);
	req_prod = READ_ONCE(shared->req_prod);

	BACK_RING_ATTACH(&vअगर->ctrl, shared, rsp_prod, XEN_PAGE_SIZE);

	err = -EIO;
	अगर (req_prod - rsp_prod > RING_SIZE(&vअगर->ctrl))
		जाओ err_unmap;

	err = bind_पूर्णांकerकरोमुख्य_evtchn_to_irq_lateeoi(xendev, evtchn);
	अगर (err < 0)
		जाओ err_unmap;

	vअगर->ctrl_irq = err;

	xenvअगर_init_hash(vअगर);

	err = request_thपढ़ोed_irq(vअगर->ctrl_irq, शून्य, xenvअगर_ctrl_irq_fn,
				   IRQF_ONESHOT, "xen-netback-ctrl", vअगर);
	अगर (err) अणु
		pr_warn("Could not setup irq handler for %s\n", dev->name);
		जाओ err_deinit;
	पूर्ण

	वापस 0;

err_deinit:
	xenvअगर_deinit_hash(vअगर);
	unbind_from_irqhandler(vअगर->ctrl_irq, vअगर);
	vअगर->ctrl_irq = 0;

err_unmap:
	xenbus_unmap_ring_vमुक्त(xendev, vअगर->ctrl.sring);
	vअगर->ctrl.sring = शून्य;

err:
	वापस err;
पूर्ण

अटल व्योम xenvअगर_disconnect_queue(काष्ठा xenvअगर_queue *queue)
अणु
	अगर (queue->task) अणु
		kthपढ़ो_stop(queue->task);
		put_task_काष्ठा(queue->task);
		queue->task = शून्य;
	पूर्ण

	अगर (queue->dealloc_task) अणु
		kthपढ़ो_stop(queue->dealloc_task);
		queue->dealloc_task = शून्य;
	पूर्ण

	अगर (queue->napi.poll) अणु
		netअगर_napi_del(&queue->napi);
		queue->napi.poll = शून्य;
	पूर्ण

	अगर (queue->tx_irq) अणु
		unbind_from_irqhandler(queue->tx_irq, queue);
		अगर (queue->tx_irq == queue->rx_irq)
			queue->rx_irq = 0;
		queue->tx_irq = 0;
	पूर्ण

	अगर (queue->rx_irq) अणु
		unbind_from_irqhandler(queue->rx_irq, queue);
		queue->rx_irq = 0;
	पूर्ण

	xenvअगर_unmap_frontend_data_rings(queue);
पूर्ण

पूर्णांक xenvअगर_connect_data(काष्ठा xenvअगर_queue *queue,
			अचिन्हित दीर्घ tx_ring_ref,
			अचिन्हित दीर्घ rx_ring_ref,
			अचिन्हित पूर्णांक tx_evtchn,
			अचिन्हित पूर्णांक rx_evtchn)
अणु
	काष्ठा xenbus_device *dev = xenvअगर_to_xenbus_device(queue->vअगर);
	काष्ठा task_काष्ठा *task;
	पूर्णांक err;

	BUG_ON(queue->tx_irq);
	BUG_ON(queue->task);
	BUG_ON(queue->dealloc_task);

	err = xenvअगर_map_frontend_data_rings(queue, tx_ring_ref,
					     rx_ring_ref);
	अगर (err < 0)
		जाओ err;

	init_रुकोqueue_head(&queue->wq);
	init_रुकोqueue_head(&queue->dealloc_wq);
	atomic_set(&queue->inflight_packets, 0);

	netअगर_napi_add(queue->vअगर->dev, &queue->napi, xenvअगर_poll,
			XENVIF_NAPI_WEIGHT);

	queue->stalled = true;

	task = kthपढ़ो_run(xenvअगर_kthपढ़ो_guest_rx, queue,
			   "%s-guest-rx", queue->name);
	अगर (IS_ERR(task))
		जाओ kthपढ़ो_err;
	queue->task = task;
	/*
	 * Take a reference to the task in order to prevent it from being मुक्तd
	 * अगर the thपढ़ो function वापसs beक्रमe kthपढ़ो_stop is called.
	 */
	get_task_काष्ठा(task);

	task = kthपढ़ो_run(xenvअगर_dealloc_kthपढ़ो, queue,
			   "%s-dealloc", queue->name);
	अगर (IS_ERR(task))
		जाओ kthपढ़ो_err;
	queue->dealloc_task = task;

	अगर (tx_evtchn == rx_evtchn) अणु
		/* feature-split-event-channels == 0 */
		err = bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi(
			dev, tx_evtchn, xenvअगर_पूर्णांकerrupt, 0,
			queue->name, queue);
		अगर (err < 0)
			जाओ err;
		queue->tx_irq = queue->rx_irq = err;
		disable_irq(queue->tx_irq);
	पूर्ण अन्यथा अणु
		/* feature-split-event-channels == 1 */
		snम_लिखो(queue->tx_irq_name, माप(queue->tx_irq_name),
			 "%s-tx", queue->name);
		err = bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi(
			dev, tx_evtchn, xenvअगर_tx_पूर्णांकerrupt, 0,
			queue->tx_irq_name, queue);
		अगर (err < 0)
			जाओ err;
		queue->tx_irq = err;
		disable_irq(queue->tx_irq);

		snम_लिखो(queue->rx_irq_name, माप(queue->rx_irq_name),
			 "%s-rx", queue->name);
		err = bind_पूर्णांकerकरोमुख्य_evtchn_to_irqhandler_lateeoi(
			dev, rx_evtchn, xenvअगर_rx_पूर्णांकerrupt, 0,
			queue->rx_irq_name, queue);
		अगर (err < 0)
			जाओ err;
		queue->rx_irq = err;
		disable_irq(queue->rx_irq);
	पूर्ण

	वापस 0;

kthपढ़ो_err:
	pr_warn("Could not allocate kthread for %s\n", queue->name);
	err = PTR_ERR(task);
err:
	xenvअगर_disconnect_queue(queue);
	वापस err;
पूर्ण

व्योम xenvअगर_carrier_off(काष्ठा xenvअगर *vअगर)
अणु
	काष्ठा net_device *dev = vअगर->dev;

	rtnl_lock();
	अगर (test_and_clear_bit(VIF_STATUS_CONNECTED, &vअगर->status)) अणु
		netअगर_carrier_off(dev); /* discard queued packets */
		अगर (netअगर_running(dev))
			xenvअगर_करोwn(vअगर);
	पूर्ण
	rtnl_unlock();
पूर्ण

व्योम xenvअगर_disconnect_data(काष्ठा xenvअगर *vअगर)
अणु
	काष्ठा xenvअगर_queue *queue = शून्य;
	अचिन्हित पूर्णांक num_queues = vअगर->num_queues;
	अचिन्हित पूर्णांक queue_index;

	xenvअगर_carrier_off(vअगर);

	क्रम (queue_index = 0; queue_index < num_queues; ++queue_index) अणु
		queue = &vअगर->queues[queue_index];

		xenvअगर_disconnect_queue(queue);
	पूर्ण

	xenvअगर_mcast_addr_list_मुक्त(vअगर);
पूर्ण

व्योम xenvअगर_disconnect_ctrl(काष्ठा xenvअगर *vअगर)
अणु
	अगर (vअगर->ctrl_irq) अणु
		xenvअगर_deinit_hash(vअगर);
		unbind_from_irqhandler(vअगर->ctrl_irq, vअगर);
		vअगर->ctrl_irq = 0;
	पूर्ण

	अगर (vअगर->ctrl.sring) अणु
		xenbus_unmap_ring_vमुक्त(xenvअगर_to_xenbus_device(vअगर),
					vअगर->ctrl.sring);
		vअगर->ctrl.sring = शून्य;
	पूर्ण
पूर्ण

/* Reverse the relevant parts of xenvअगर_init_queue().
 * Used क्रम queue tearकरोwn from xenvअगर_मुक्त(), and on the
 * error handling paths in xenbus.c:connect().
 */
व्योम xenvअगर_deinit_queue(काष्ठा xenvअगर_queue *queue)
अणु
	gnttab_मुक्त_pages(MAX_PENDING_REQS, queue->mmap_pages);
पूर्ण

व्योम xenvअगर_मुक्त(काष्ठा xenvअगर *vअगर)
अणु
	काष्ठा xenvअगर_queue *queues = vअगर->queues;
	अचिन्हित पूर्णांक num_queues = vअगर->num_queues;
	अचिन्हित पूर्णांक queue_index;

	unरेजिस्टर_netdev(vअगर->dev);
	मुक्त_netdev(vअगर->dev);

	क्रम (queue_index = 0; queue_index < num_queues; ++queue_index)
		xenvअगर_deinit_queue(&queues[queue_index]);
	vमुक्त(queues);

	module_put(THIS_MODULE);
पूर्ण
