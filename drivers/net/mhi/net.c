<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-or-later
/* MHI Network driver - Network over MHI bus
 *
 * Copyright (C) 2020 Linaro Ltd <loic.poulain@linaro.org>
 */

#समावेश <linux/अगर_arp.h>
#समावेश <linux/mhi.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/module.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/u64_stats_sync.h>

#समावेश "mhi.h"

#घोषणा MHI_NET_MIN_MTU		ETH_MIN_MTU
#घोषणा MHI_NET_MAX_MTU		0xffff
#घोषणा MHI_NET_DEFAULT_MTU	0x4000

काष्ठा mhi_device_info अणु
	स्थिर अक्षर *netname;
	स्थिर काष्ठा mhi_net_proto *proto;
पूर्ण;

अटल पूर्णांक mhi_nकरो_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा mhi_net_dev *mhi_netdev = netdev_priv(ndev);

	/* Feed the rx buffer pool */
	schedule_delayed_work(&mhi_netdev->rx_refill, 0);

	/* Carrier is established via out-of-band channel (e.g. qmi) */
	netअगर_carrier_on(ndev);

	netअगर_start_queue(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक mhi_nकरो_stop(काष्ठा net_device *ndev)
अणु
	काष्ठा mhi_net_dev *mhi_netdev = netdev_priv(ndev);

	netअगर_stop_queue(ndev);
	netअगर_carrier_off(ndev);
	cancel_delayed_work_sync(&mhi_netdev->rx_refill);

	वापस 0;
पूर्ण

अटल netdev_tx_t mhi_nकरो_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा mhi_net_dev *mhi_netdev = netdev_priv(ndev);
	स्थिर काष्ठा mhi_net_proto *proto = mhi_netdev->proto;
	काष्ठा mhi_device *mdev = mhi_netdev->mdev;
	पूर्णांक err;

	अगर (proto && proto->tx_fixup) अणु
		skb = proto->tx_fixup(mhi_netdev, skb);
		अगर (unlikely(!skb))
			जाओ निकास_drop;
	पूर्ण

	err = mhi_queue_skb(mdev, DMA_TO_DEVICE, skb, skb->len, MHI_EOT);
	अगर (unlikely(err)) अणु
		net_err_ratelimited("%s: Failed to queue TX buf (%d)\n",
				    ndev->name, err);
		dev_kमुक्त_skb_any(skb);
		जाओ निकास_drop;
	पूर्ण

	अगर (mhi_queue_is_full(mdev, DMA_TO_DEVICE))
		netअगर_stop_queue(ndev);

	वापस NETDEV_TX_OK;

निकास_drop:
	u64_stats_update_begin(&mhi_netdev->stats.tx_syncp);
	u64_stats_inc(&mhi_netdev->stats.tx_dropped);
	u64_stats_update_end(&mhi_netdev->stats.tx_syncp);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम mhi_nकरो_get_stats64(काष्ठा net_device *ndev,
				काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा mhi_net_dev *mhi_netdev = netdev_priv(ndev);
	अचिन्हित पूर्णांक start;

	करो अणु
		start = u64_stats_fetch_begin_irq(&mhi_netdev->stats.rx_syncp);
		stats->rx_packets = u64_stats_पढ़ो(&mhi_netdev->stats.rx_packets);
		stats->rx_bytes = u64_stats_पढ़ो(&mhi_netdev->stats.rx_bytes);
		stats->rx_errors = u64_stats_पढ़ो(&mhi_netdev->stats.rx_errors);
		stats->rx_dropped = u64_stats_पढ़ो(&mhi_netdev->stats.rx_dropped);
		stats->rx_length_errors = u64_stats_पढ़ो(&mhi_netdev->stats.rx_length_errors);
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&mhi_netdev->stats.rx_syncp, start));

	करो अणु
		start = u64_stats_fetch_begin_irq(&mhi_netdev->stats.tx_syncp);
		stats->tx_packets = u64_stats_पढ़ो(&mhi_netdev->stats.tx_packets);
		stats->tx_bytes = u64_stats_पढ़ो(&mhi_netdev->stats.tx_bytes);
		stats->tx_errors = u64_stats_पढ़ो(&mhi_netdev->stats.tx_errors);
		stats->tx_dropped = u64_stats_पढ़ो(&mhi_netdev->stats.tx_dropped);
	पूर्ण जबतक (u64_stats_fetch_retry_irq(&mhi_netdev->stats.tx_syncp, start));
पूर्ण

अटल स्थिर काष्ठा net_device_ops mhi_netdev_ops = अणु
	.nकरो_खोलो               = mhi_nकरो_खोलो,
	.nकरो_stop               = mhi_nकरो_stop,
	.nकरो_start_xmit         = mhi_nकरो_xmit,
	.nकरो_get_stats64	= mhi_nकरो_get_stats64,
पूर्ण;

अटल व्योम mhi_net_setup(काष्ठा net_device *ndev)
अणु
	ndev->header_ops = शून्य;  /* No header */
	ndev->type = ARPHRD_RAWIP;
	ndev->hard_header_len = 0;
	ndev->addr_len = 0;
	ndev->flags = IFF_POINTOPOINT | IFF_NOARP;
	ndev->netdev_ops = &mhi_netdev_ops;
	ndev->mtu = MHI_NET_DEFAULT_MTU;
	ndev->min_mtu = MHI_NET_MIN_MTU;
	ndev->max_mtu = MHI_NET_MAX_MTU;
	ndev->tx_queue_len = 1000;
पूर्ण

अटल काष्ठा sk_buff *mhi_net_skb_agg(काष्ठा mhi_net_dev *mhi_netdev,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *head = mhi_netdev->skbagg_head;
	काष्ठा sk_buff *tail = mhi_netdev->skbagg_tail;

	/* This is non-paged skb chaining using frag_list */
	अगर (!head) अणु
		mhi_netdev->skbagg_head = skb;
		वापस skb;
	पूर्ण

	अगर (!skb_shinfo(head)->frag_list)
		skb_shinfo(head)->frag_list = skb;
	अन्यथा
		tail->next = skb;

	head->len += skb->len;
	head->data_len += skb->len;
	head->truesize += skb->truesize;

	mhi_netdev->skbagg_tail = skb;

	वापस mhi_netdev->skbagg_head;
पूर्ण

अटल व्योम mhi_net_dl_callback(काष्ठा mhi_device *mhi_dev,
				काष्ठा mhi_result *mhi_res)
अणु
	काष्ठा mhi_net_dev *mhi_netdev = dev_get_drvdata(&mhi_dev->dev);
	स्थिर काष्ठा mhi_net_proto *proto = mhi_netdev->proto;
	काष्ठा sk_buff *skb = mhi_res->buf_addr;
	पूर्णांक मुक्त_desc_count;

	मुक्त_desc_count = mhi_get_मुक्त_desc_count(mhi_dev, DMA_FROM_DEVICE);

	अगर (unlikely(mhi_res->transaction_status)) अणु
		चयन (mhi_res->transaction_status) अणु
		हाल -EOVERFLOW:
			/* Packet can not fit in one MHI buffer and has been
			 * split over multiple MHI transfers, करो re-aggregation.
			 * That usually means the device side MTU is larger than
			 * the host side MTU/MRU. Since this is not optimal,
			 * prपूर्णांक a warning (once).
			 */
			netdev_warn_once(mhi_netdev->ndev,
					 "Fragmented packets received, fix MTU?\n");
			skb_put(skb, mhi_res->bytes_xferd);
			mhi_net_skb_agg(mhi_netdev, skb);
			अवरोध;
		हाल -ENOTCONN:
			/* MHI layer stopping/resetting the DL channel */
			dev_kमुक्त_skb_any(skb);
			वापस;
		शेष:
			/* Unknown error, simply drop */
			dev_kमुक्त_skb_any(skb);
			u64_stats_update_begin(&mhi_netdev->stats.rx_syncp);
			u64_stats_inc(&mhi_netdev->stats.rx_errors);
			u64_stats_update_end(&mhi_netdev->stats.rx_syncp);
		पूर्ण
	पूर्ण अन्यथा अणु
		skb_put(skb, mhi_res->bytes_xferd);

		अगर (mhi_netdev->skbagg_head) अणु
			/* Aggregate the final fragment */
			skb = mhi_net_skb_agg(mhi_netdev, skb);
			mhi_netdev->skbagg_head = शून्य;
		पूर्ण

		u64_stats_update_begin(&mhi_netdev->stats.rx_syncp);
		u64_stats_inc(&mhi_netdev->stats.rx_packets);
		u64_stats_add(&mhi_netdev->stats.rx_bytes, skb->len);
		u64_stats_update_end(&mhi_netdev->stats.rx_syncp);

		चयन (skb->data[0] & 0xf0) अणु
		हाल 0x40:
			skb->protocol = htons(ETH_P_IP);
			अवरोध;
		हाल 0x60:
			skb->protocol = htons(ETH_P_IPV6);
			अवरोध;
		शेष:
			skb->protocol = htons(ETH_P_MAP);
			अवरोध;
		पूर्ण

		अगर (proto && proto->rx)
			proto->rx(mhi_netdev, skb);
		अन्यथा
			netअगर_rx(skb);
	पूर्ण

	/* Refill अगर RX buffers queue becomes low */
	अगर (मुक्त_desc_count >= mhi_netdev->rx_queue_sz / 2)
		schedule_delayed_work(&mhi_netdev->rx_refill, 0);
पूर्ण

अटल व्योम mhi_net_ul_callback(काष्ठा mhi_device *mhi_dev,
				काष्ठा mhi_result *mhi_res)
अणु
	काष्ठा mhi_net_dev *mhi_netdev = dev_get_drvdata(&mhi_dev->dev);
	काष्ठा net_device *ndev = mhi_netdev->ndev;
	काष्ठा mhi_device *mdev = mhi_netdev->mdev;
	काष्ठा sk_buff *skb = mhi_res->buf_addr;

	/* Hardware has consumed the buffer, so मुक्त the skb (which is not
	 * मुक्तd by the MHI stack) and perक्रमm accounting.
	 */
	dev_consume_skb_any(skb);

	u64_stats_update_begin(&mhi_netdev->stats.tx_syncp);
	अगर (unlikely(mhi_res->transaction_status)) अणु

		/* MHI layer stopping/resetting the UL channel */
		अगर (mhi_res->transaction_status == -ENOTCONN) अणु
			u64_stats_update_end(&mhi_netdev->stats.tx_syncp);
			वापस;
		पूर्ण

		u64_stats_inc(&mhi_netdev->stats.tx_errors);
	पूर्ण अन्यथा अणु
		u64_stats_inc(&mhi_netdev->stats.tx_packets);
		u64_stats_add(&mhi_netdev->stats.tx_bytes, mhi_res->bytes_xferd);
	पूर्ण
	u64_stats_update_end(&mhi_netdev->stats.tx_syncp);

	अगर (netअगर_queue_stopped(ndev) && !mhi_queue_is_full(mdev, DMA_TO_DEVICE))
		netअगर_wake_queue(ndev);
पूर्ण

अटल व्योम mhi_net_rx_refill_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा mhi_net_dev *mhi_netdev = container_of(work, काष्ठा mhi_net_dev,
						      rx_refill.work);
	काष्ठा net_device *ndev = mhi_netdev->ndev;
	काष्ठा mhi_device *mdev = mhi_netdev->mdev;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक size;
	पूर्णांक err;

	size = mhi_netdev->mru ? mhi_netdev->mru : READ_ONCE(ndev->mtu);

	जबतक (!mhi_queue_is_full(mdev, DMA_FROM_DEVICE)) अणु
		skb = netdev_alloc_skb(ndev, size);
		अगर (unlikely(!skb))
			अवरोध;

		err = mhi_queue_skb(mdev, DMA_FROM_DEVICE, skb, size, MHI_EOT);
		अगर (unlikely(err)) अणु
			net_err_ratelimited("%s: Failed to queue RX buf (%d)\n",
					    ndev->name, err);
			kमुक्त_skb(skb);
			अवरोध;
		पूर्ण

		/* Do not hog the CPU अगर rx buffers are consumed faster than
		 * queued (unlikely).
		 */
		cond_resched();
	पूर्ण

	/* If we're still starved of rx buffers, reschedule later */
	अगर (mhi_get_मुक्त_desc_count(mdev, DMA_FROM_DEVICE) == mhi_netdev->rx_queue_sz)
		schedule_delayed_work(&mhi_netdev->rx_refill, HZ / 2);
पूर्ण

अटल काष्ठा device_type wwan_type = अणु
	.name = "wwan",
पूर्ण;

अटल पूर्णांक mhi_net_probe(काष्ठा mhi_device *mhi_dev,
			 स्थिर काष्ठा mhi_device_id *id)
अणु
	स्थिर काष्ठा mhi_device_info *info = (काष्ठा mhi_device_info *)id->driver_data;
	काष्ठा device *dev = &mhi_dev->dev;
	काष्ठा mhi_net_dev *mhi_netdev;
	काष्ठा net_device *ndev;
	पूर्णांक err;

	ndev = alloc_netdev(माप(*mhi_netdev), info->netname,
			    NET_NAME_PREDICTABLE, mhi_net_setup);
	अगर (!ndev)
		वापस -ENOMEM;

	mhi_netdev = netdev_priv(ndev);
	dev_set_drvdata(dev, mhi_netdev);
	mhi_netdev->ndev = ndev;
	mhi_netdev->mdev = mhi_dev;
	mhi_netdev->skbagg_head = शून्य;
	mhi_netdev->proto = info->proto;
	SET_NETDEV_DEV(ndev, &mhi_dev->dev);
	SET_NETDEV_DEVTYPE(ndev, &wwan_type);

	INIT_DELAYED_WORK(&mhi_netdev->rx_refill, mhi_net_rx_refill_work);
	u64_stats_init(&mhi_netdev->stats.rx_syncp);
	u64_stats_init(&mhi_netdev->stats.tx_syncp);

	/* Start MHI channels */
	err = mhi_prepare_क्रम_transfer(mhi_dev);
	अगर (err)
		जाओ out_err;

	/* Number of transfer descriptors determines size of the queue */
	mhi_netdev->rx_queue_sz = mhi_get_मुक्त_desc_count(mhi_dev, DMA_FROM_DEVICE);

	err = रेजिस्टर_netdev(ndev);
	अगर (err)
		जाओ out_err;

	अगर (mhi_netdev->proto) अणु
		err = mhi_netdev->proto->init(mhi_netdev);
		अगर (err)
			जाओ out_err_proto;
	पूर्ण

	वापस 0;

out_err_proto:
	unरेजिस्टर_netdev(ndev);
out_err:
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

अटल व्योम mhi_net_हटाओ(काष्ठा mhi_device *mhi_dev)
अणु
	काष्ठा mhi_net_dev *mhi_netdev = dev_get_drvdata(&mhi_dev->dev);

	unरेजिस्टर_netdev(mhi_netdev->ndev);

	mhi_unprepare_from_transfer(mhi_netdev->mdev);

	kमुक्त_skb(mhi_netdev->skbagg_head);

	मुक्त_netdev(mhi_netdev->ndev);
पूर्ण

अटल स्थिर काष्ठा mhi_device_info mhi_hwip0 = अणु
	.netname = "mhi_hwip%d",
पूर्ण;

अटल स्थिर काष्ठा mhi_device_info mhi_swip0 = अणु
	.netname = "mhi_swip%d",
पूर्ण;

अटल स्थिर काष्ठा mhi_device_info mhi_hwip0_mbim = अणु
	.netname = "mhi_mbim%d",
	.proto = &proto_mbim,
पूर्ण;

अटल स्थिर काष्ठा mhi_device_id mhi_net_id_table[] = अणु
	/* Hardware accelerated data PATH (to modem IPA), protocol agnostic */
	अणु .chan = "IP_HW0", .driver_data = (kernel_uदीर्घ_t)&mhi_hwip0 पूर्ण,
	/* Software data PATH (to modem CPU) */
	अणु .chan = "IP_SW0", .driver_data = (kernel_uदीर्घ_t)&mhi_swip0 पूर्ण,
	/* Hardware accelerated data PATH (to modem IPA), MBIM protocol */
	अणु .chan = "IP_HW0_MBIM", .driver_data = (kernel_uदीर्घ_t)&mhi_hwip0_mbim पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(mhi, mhi_net_id_table);

अटल काष्ठा mhi_driver mhi_net_driver = अणु
	.probe = mhi_net_probe,
	.हटाओ = mhi_net_हटाओ,
	.dl_xfer_cb = mhi_net_dl_callback,
	.ul_xfer_cb = mhi_net_ul_callback,
	.id_table = mhi_net_id_table,
	.driver = अणु
		.name = "mhi_net",
		.owner = THIS_MODULE,
	पूर्ण,
पूर्ण;

module_mhi_driver(mhi_net_driver);

MODULE_AUTHOR("Loic Poulain <loic.poulain@linaro.org>");
MODULE_DESCRIPTION("Network over MHI");
MODULE_LICENSE("GPL v2");
