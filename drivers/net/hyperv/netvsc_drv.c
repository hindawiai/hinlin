<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright (c) 2009, Microsoft Corporation.
 *
 * Authors:
 *   Haiyang Zhang <haiyangz@microsoft.com>
 *   Hank Janssen  <hjanssen@microsoft.com>
 */
#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/init.h>
#समावेश <linux/atomic.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/module.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/device.h>
#समावेश <linux/पन.स>
#समावेश <linux/delay.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/inetdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/pci.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/netpoll.h>
#समावेश <linux/bpf.h>

#समावेश <net/arp.h>
#समावेश <net/route.h>
#समावेश <net/sock.h>
#समावेश <net/pkt_sched.h>
#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>

#समावेश "hyperv_net.h"

#घोषणा RING_SIZE_MIN	64

#घोषणा LINKCHANGE_INT (2 * HZ)
#घोषणा VF_TAKEOVER_INT (HZ / 10)

अटल अचिन्हित पूर्णांक ring_size __ro_after_init = 128;
module_param(ring_size, uपूर्णांक, 0444);
MODULE_PARM_DESC(ring_size, "Ring buffer size (# of pages)");
अचिन्हित पूर्णांक netvsc_ring_bytes __ro_after_init;

अटल स्थिर u32 शेष_msg = NETIF_MSG_DRV | NETIF_MSG_PROBE |
				NETIF_MSG_LINK | NETIF_MSG_IFUP |
				NETIF_MSG_IFDOWN | NETIF_MSG_RX_ERR |
				NETIF_MSG_TX_ERR;

अटल पूर्णांक debug = -1;
module_param(debug, पूर्णांक, 0444);
MODULE_PARM_DESC(debug, "Debug level (0=none,...,16=all)");

अटल LIST_HEAD(netvsc_dev_list);

अटल व्योम netvsc_change_rx_flags(काष्ठा net_device *net, पूर्णांक change)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(net);
	काष्ठा net_device *vf_netdev = rtnl_dereference(ndev_ctx->vf_netdev);
	पूर्णांक inc;

	अगर (!vf_netdev)
		वापस;

	अगर (change & IFF_PROMISC) अणु
		inc = (net->flags & IFF_PROMISC) ? 1 : -1;
		dev_set_promiscuity(vf_netdev, inc);
	पूर्ण

	अगर (change & IFF_ALLMULTI) अणु
		inc = (net->flags & IFF_ALLMULTI) ? 1 : -1;
		dev_set_allmulti(vf_netdev, inc);
	पूर्ण
पूर्ण

अटल व्योम netvsc_set_rx_mode(काष्ठा net_device *net)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(net);
	काष्ठा net_device *vf_netdev;
	काष्ठा netvsc_device *nvdev;

	rcu_पढ़ो_lock();
	vf_netdev = rcu_dereference(ndev_ctx->vf_netdev);
	अगर (vf_netdev) अणु
		dev_uc_sync(vf_netdev, net);
		dev_mc_sync(vf_netdev, net);
	पूर्ण

	nvdev = rcu_dereference(ndev_ctx->nvdev);
	अगर (nvdev)
		rndis_filter_update(nvdev);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम netvsc_tx_enable(काष्ठा netvsc_device *nvscdev,
			     काष्ठा net_device *ndev)
अणु
	nvscdev->tx_disable = false;
	virt_wmb(); /* ensure queue wake up mechanism is on */

	netअगर_tx_wake_all_queues(ndev);
पूर्ण

अटल पूर्णांक netvsc_खोलो(काष्ठा net_device *net)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(net);
	काष्ठा net_device *vf_netdev = rtnl_dereference(ndev_ctx->vf_netdev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndev_ctx->nvdev);
	काष्ठा rndis_device *rdev;
	पूर्णांक ret = 0;

	netअगर_carrier_off(net);

	/* Open up the device */
	ret = rndis_filter_खोलो(nvdev);
	अगर (ret != 0) अणु
		netdev_err(net, "unable to open device (ret %d).\n", ret);
		वापस ret;
	पूर्ण

	rdev = nvdev->extension;
	अगर (!rdev->link_state) अणु
		netअगर_carrier_on(net);
		netvsc_tx_enable(nvdev, net);
	पूर्ण

	अगर (vf_netdev) अणु
		/* Setting synthetic device up transparently sets
		 * slave as up. If खोलो fails, then slave will be
		 * still be offline (and not used).
		 */
		ret = dev_खोलो(vf_netdev, शून्य);
		अगर (ret)
			netdev_warn(net,
				    "unable to open slave: %s: %d\n",
				    vf_netdev->name, ret);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक netvsc_रुको_until_empty(काष्ठा netvsc_device *nvdev)
अणु
	अचिन्हित पूर्णांक retry = 0;
	पूर्णांक i;

	/* Ensure pending bytes in ring are पढ़ो */
	क्रम (;;) अणु
		u32 aपढ़ो = 0;

		क्रम (i = 0; i < nvdev->num_chn; i++) अणु
			काष्ठा vmbus_channel *chn
				= nvdev->chan_table[i].channel;

			अगर (!chn)
				जारी;

			/* make sure receive not running now */
			napi_synchronize(&nvdev->chan_table[i].napi);

			aपढ़ो = hv_get_bytes_to_पढ़ो(&chn->inbound);
			अगर (aपढ़ो)
				अवरोध;

			aपढ़ो = hv_get_bytes_to_पढ़ो(&chn->outbound);
			अगर (aपढ़ो)
				अवरोध;
		पूर्ण

		अगर (aपढ़ो == 0)
			वापस 0;

		अगर (++retry > RETRY_MAX)
			वापस -ETIMEDOUT;

		usleep_range(RETRY_US_LO, RETRY_US_HI);
	पूर्ण
पूर्ण

अटल व्योम netvsc_tx_disable(काष्ठा netvsc_device *nvscdev,
			      काष्ठा net_device *ndev)
अणु
	अगर (nvscdev) अणु
		nvscdev->tx_disable = true;
		virt_wmb(); /* ensure txq will not wake up after stop */
	पूर्ण

	netअगर_tx_disable(ndev);
पूर्ण

अटल पूर्णांक netvsc_बंद(काष्ठा net_device *net)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(net);
	काष्ठा net_device *vf_netdev
		= rtnl_dereference(net_device_ctx->vf_netdev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(net_device_ctx->nvdev);
	पूर्णांक ret;

	netvsc_tx_disable(nvdev, net);

	/* No need to बंद rndis filter अगर it is हटाओd alपढ़ोy */
	अगर (!nvdev)
		वापस 0;

	ret = rndis_filter_बंद(nvdev);
	अगर (ret != 0) अणु
		netdev_err(net, "unable to close device (ret %d).\n", ret);
		वापस ret;
	पूर्ण

	ret = netvsc_रुको_until_empty(nvdev);
	अगर (ret)
		netdev_err(net, "Ring buffer not empty after closing rndis\n");

	अगर (vf_netdev)
		dev_बंद(vf_netdev);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम *init_ppi_data(काष्ठा rndis_message *msg,
				  u32 ppi_size, u32 pkt_type)
अणु
	काष्ठा rndis_packet *rndis_pkt = &msg->msg.pkt;
	काष्ठा rndis_per_packet_info *ppi;

	rndis_pkt->data_offset += ppi_size;
	ppi = (व्योम *)rndis_pkt + rndis_pkt->per_pkt_info_offset
		+ rndis_pkt->per_pkt_info_len;

	ppi->size = ppi_size;
	ppi->type = pkt_type;
	ppi->पूर्णांकernal = 0;
	ppi->ppi_offset = माप(काष्ठा rndis_per_packet_info);

	rndis_pkt->per_pkt_info_len += ppi_size;

	वापस ppi + 1;
पूर्ण

/* Azure hosts करोn't support non-TCP port numbers in hashing क्रम fragmented
 * packets. We can use ethtool to change UDP hash level when necessary.
 */
अटल अंतरभूत u32 netvsc_get_hash(
	काष्ठा sk_buff *skb,
	स्थिर काष्ठा net_device_context *ndc)
अणु
	काष्ठा flow_keys flow;
	u32 hash, pkt_proto = 0;
	अटल u32 hashrnd __पढ़ो_mostly;

	net_get_अक्रमom_once(&hashrnd, माप(hashrnd));

	अगर (!skb_flow_dissect_flow_keys(skb, &flow, 0))
		वापस 0;

	चयन (flow.basic.ip_proto) अणु
	हाल IPPROTO_TCP:
		अगर (flow.basic.n_proto == htons(ETH_P_IP))
			pkt_proto = HV_TCP4_L4HASH;
		अन्यथा अगर (flow.basic.n_proto == htons(ETH_P_IPV6))
			pkt_proto = HV_TCP6_L4HASH;

		अवरोध;

	हाल IPPROTO_UDP:
		अगर (flow.basic.n_proto == htons(ETH_P_IP))
			pkt_proto = HV_UDP4_L4HASH;
		अन्यथा अगर (flow.basic.n_proto == htons(ETH_P_IPV6))
			pkt_proto = HV_UDP6_L4HASH;

		अवरोध;
	पूर्ण

	अगर (pkt_proto & ndc->l4_hash) अणु
		वापस skb_get_hash(skb);
	पूर्ण अन्यथा अणु
		अगर (flow.basic.n_proto == htons(ETH_P_IP))
			hash = jhash2((u32 *)&flow.addrs.v4addrs, 2, hashrnd);
		अन्यथा अगर (flow.basic.n_proto == htons(ETH_P_IPV6))
			hash = jhash2((u32 *)&flow.addrs.v6addrs, 8, hashrnd);
		अन्यथा
			वापस 0;

		__skb_set_sw_hash(skb, hash, false);
	पूर्ण

	वापस hash;
पूर्ण

अटल अंतरभूत पूर्णांक netvsc_get_tx_queue(काष्ठा net_device *ndev,
				      काष्ठा sk_buff *skb, पूर्णांक old_idx)
अणु
	स्थिर काष्ठा net_device_context *ndc = netdev_priv(ndev);
	काष्ठा sock *sk = skb->sk;
	पूर्णांक q_idx;

	q_idx = ndc->tx_table[netvsc_get_hash(skb, ndc) &
			      (VRSS_SEND_TAB_SIZE - 1)];

	/* If queue index changed record the new value */
	अगर (q_idx != old_idx &&
	    sk && sk_fullsock(sk) && rcu_access_poपूर्णांकer(sk->sk_dst_cache))
		sk_tx_queue_set(sk, q_idx);

	वापस q_idx;
पूर्ण

/*
 * Select queue क्रम transmit.
 *
 * If a valid queue has alपढ़ोy been asचिन्हित, then use that.
 * Otherwise compute tx queue based on hash and the send table.
 *
 * This is basically similar to शेष (netdev_pick_tx) with the added step
 * of using the host send_table when no other queue has been asचिन्हित.
 *
 * TODO support XPS - but get_xps_queue not exported
 */
अटल u16 netvsc_pick_tx(काष्ठा net_device *ndev, काष्ठा sk_buff *skb)
अणु
	पूर्णांक q_idx = sk_tx_queue_get(skb->sk);

	अगर (q_idx < 0 || skb->ooo_okay || q_idx >= ndev->real_num_tx_queues) अणु
		/* If क्रमwarding a packet, we use the recorded queue when
		 * available क्रम better cache locality.
		 */
		अगर (skb_rx_queue_recorded(skb))
			q_idx = skb_get_rx_queue(skb);
		अन्यथा
			q_idx = netvsc_get_tx_queue(ndev, skb, q_idx);
	पूर्ण

	वापस q_idx;
पूर्ण

अटल u16 netvsc_select_queue(काष्ठा net_device *ndev, काष्ठा sk_buff *skb,
			       काष्ठा net_device *sb_dev)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(ndev);
	काष्ठा net_device *vf_netdev;
	u16 txq;

	rcu_पढ़ो_lock();
	vf_netdev = rcu_dereference(ndc->vf_netdev);
	अगर (vf_netdev) अणु
		स्थिर काष्ठा net_device_ops *vf_ops = vf_netdev->netdev_ops;

		अगर (vf_ops->nकरो_select_queue)
			txq = vf_ops->nकरो_select_queue(vf_netdev, skb, sb_dev);
		अन्यथा
			txq = netdev_pick_tx(vf_netdev, skb, शून्य);

		/* Record the queue selected by VF so that it can be
		 * used क्रम common हाल where VF has more queues than
		 * the synthetic device.
		 */
		qdisc_skb_cb(skb)->slave_dev_queue_mapping = txq;
	पूर्ण अन्यथा अणु
		txq = netvsc_pick_tx(ndev, skb);
	पूर्ण
	rcu_पढ़ो_unlock();

	जबतक (txq >= ndev->real_num_tx_queues)
		txq -= ndev->real_num_tx_queues;

	वापस txq;
पूर्ण

अटल u32 fill_pg_buf(अचिन्हित दीर्घ hvpfn, u32 offset, u32 len,
		       काष्ठा hv_page_buffer *pb)
अणु
	पूर्णांक j = 0;

	hvpfn += offset >> HV_HYP_PAGE_SHIFT;
	offset = offset & ~HV_HYP_PAGE_MASK;

	जबतक (len > 0) अणु
		अचिन्हित दीर्घ bytes;

		bytes = HV_HYP_PAGE_SIZE - offset;
		अगर (bytes > len)
			bytes = len;
		pb[j].pfn = hvpfn;
		pb[j].offset = offset;
		pb[j].len = bytes;

		offset += bytes;
		len -= bytes;

		अगर (offset == HV_HYP_PAGE_SIZE && len) अणु
			hvpfn++;
			offset = 0;
			j++;
		पूर्ण
	पूर्ण

	वापस j + 1;
पूर्ण

अटल u32 init_page_array(व्योम *hdr, u32 len, काष्ठा sk_buff *skb,
			   काष्ठा hv_netvsc_packet *packet,
			   काष्ठा hv_page_buffer *pb)
अणु
	u32 slots_used = 0;
	अक्षर *data = skb->data;
	पूर्णांक frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक i;

	/* The packet is laid out thus:
	 * 1. hdr: RNDIS header and PPI
	 * 2. skb linear data
	 * 3. skb fragment data
	 */
	slots_used += fill_pg_buf(virt_to_hvpfn(hdr),
				  offset_in_hvpage(hdr),
				  len,
				  &pb[slots_used]);

	packet->rmsg_size = len;
	packet->rmsg_pgcnt = slots_used;

	slots_used += fill_pg_buf(virt_to_hvpfn(data),
				  offset_in_hvpage(data),
				  skb_headlen(skb),
				  &pb[slots_used]);

	क्रम (i = 0; i < frags; i++) अणु
		skb_frag_t *frag = skb_shinfo(skb)->frags + i;

		slots_used += fill_pg_buf(page_to_hvpfn(skb_frag_page(frag)),
					  skb_frag_off(frag),
					  skb_frag_size(frag),
					  &pb[slots_used]);
	पूर्ण
	वापस slots_used;
पूर्ण

अटल पूर्णांक count_skb_frag_slots(काष्ठा sk_buff *skb)
अणु
	पूर्णांक i, frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक pages = 0;

	क्रम (i = 0; i < frags; i++) अणु
		skb_frag_t *frag = skb_shinfo(skb)->frags + i;
		अचिन्हित दीर्घ size = skb_frag_size(frag);
		अचिन्हित दीर्घ offset = skb_frag_off(frag);

		/* Skip unused frames from start of page */
		offset &= ~HV_HYP_PAGE_MASK;
		pages += HVPFN_UP(offset + size);
	पूर्ण
	वापस pages;
पूर्ण

अटल पूर्णांक netvsc_get_slots(काष्ठा sk_buff *skb)
अणु
	अक्षर *data = skb->data;
	अचिन्हित पूर्णांक offset = offset_in_hvpage(data);
	अचिन्हित पूर्णांक len = skb_headlen(skb);
	पूर्णांक slots;
	पूर्णांक frag_slots;

	slots = DIV_ROUND_UP(offset + len, HV_HYP_PAGE_SIZE);
	frag_slots = count_skb_frag_slots(skb);
	वापस slots + frag_slots;
पूर्ण

अटल u32 net_checksum_info(काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *ip = ip_hdr(skb);

		अगर (ip->protocol == IPPROTO_TCP)
			वापस TRANSPORT_INFO_IPV4_TCP;
		अन्यथा अगर (ip->protocol == IPPROTO_UDP)
			वापस TRANSPORT_INFO_IPV4_UDP;
	पूर्ण अन्यथा अणु
		काष्ठा ipv6hdr *ip6 = ipv6_hdr(skb);

		अगर (ip6->nexthdr == IPPROTO_TCP)
			वापस TRANSPORT_INFO_IPV6_TCP;
		अन्यथा अगर (ip6->nexthdr == IPPROTO_UDP)
			वापस TRANSPORT_INFO_IPV6_UDP;
	पूर्ण

	वापस TRANSPORT_INFO_NOT_IP;
पूर्ण

/* Send skb on the slave VF device. */
अटल पूर्णांक netvsc_vf_xmit(काष्ठा net_device *net, काष्ठा net_device *vf_netdev,
			  काष्ठा sk_buff *skb)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(net);
	अचिन्हित पूर्णांक len = skb->len;
	पूर्णांक rc;

	skb->dev = vf_netdev;
	skb_record_rx_queue(skb, qdisc_skb_cb(skb)->slave_dev_queue_mapping);

	rc = dev_queue_xmit(skb);
	अगर (likely(rc == NET_XMIT_SUCCESS || rc == NET_XMIT_CN)) अणु
		काष्ठा netvsc_vf_pcpu_stats *pcpu_stats
			= this_cpu_ptr(ndev_ctx->vf_stats);

		u64_stats_update_begin(&pcpu_stats->syncp);
		pcpu_stats->tx_packets++;
		pcpu_stats->tx_bytes += len;
		u64_stats_update_end(&pcpu_stats->syncp);
	पूर्ण अन्यथा अणु
		this_cpu_inc(ndev_ctx->vf_stats->tx_dropped);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक netvsc_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *net, bool xdp_tx)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(net);
	काष्ठा hv_netvsc_packet *packet = शून्य;
	पूर्णांक ret;
	अचिन्हित पूर्णांक num_data_pgs;
	काष्ठा rndis_message *rndis_msg;
	काष्ठा net_device *vf_netdev;
	u32 rndis_msg_size;
	u32 hash;
	काष्ठा hv_page_buffer pb[MAX_PAGE_BUFFER_COUNT];

	/* If VF is present and up then redirect packets to it.
	 * Skip the VF अगर it is marked करोwn or has no carrier.
	 * If netpoll is in uses, then VF can not be used either.
	 */
	vf_netdev = rcu_dereference_bh(net_device_ctx->vf_netdev);
	अगर (vf_netdev && netअगर_running(vf_netdev) &&
	    netअगर_carrier_ok(vf_netdev) && !netpoll_tx_running(net) &&
	    net_device_ctx->data_path_is_vf)
		वापस netvsc_vf_xmit(net, vf_netdev, skb);

	/* We will aपंचांगost need two pages to describe the rndis
	 * header. We can only transmit MAX_PAGE_BUFFER_COUNT number
	 * of pages in a single packet. If skb is scattered around
	 * more pages we try linearizing it.
	 */

	num_data_pgs = netvsc_get_slots(skb) + 2;

	अगर (unlikely(num_data_pgs > MAX_PAGE_BUFFER_COUNT)) अणु
		++net_device_ctx->eth_stats.tx_scattered;

		अगर (skb_linearize(skb))
			जाओ no_memory;

		num_data_pgs = netvsc_get_slots(skb) + 2;
		अगर (num_data_pgs > MAX_PAGE_BUFFER_COUNT) अणु
			++net_device_ctx->eth_stats.tx_too_big;
			जाओ drop;
		पूर्ण
	पूर्ण

	/*
	 * Place the rndis header in the skb head room and
	 * the skb->cb will be used क्रम hv_netvsc_packet
	 * काष्ठाure.
	 */
	ret = skb_cow_head(skb, RNDIS_AND_PPI_SIZE);
	अगर (ret)
		जाओ no_memory;

	/* Use the skb control buffer क्रम building up the packet */
	BUILD_BUG_ON(माप(काष्ठा hv_netvsc_packet) >
			माप_field(काष्ठा sk_buff, cb));
	packet = (काष्ठा hv_netvsc_packet *)skb->cb;

	packet->q_idx = skb_get_queue_mapping(skb);

	packet->total_data_buflen = skb->len;
	packet->total_bytes = skb->len;
	packet->total_packets = 1;

	rndis_msg = (काष्ठा rndis_message *)skb->head;

	/* Add the rndis header */
	rndis_msg->ndis_msg_type = RNDIS_MSG_PACKET;
	rndis_msg->msg_len = packet->total_data_buflen;

	rndis_msg->msg.pkt = (काष्ठा rndis_packet) अणु
		.data_offset = माप(काष्ठा rndis_packet),
		.data_len = packet->total_data_buflen,
		.per_pkt_info_offset = माप(काष्ठा rndis_packet),
	पूर्ण;

	rndis_msg_size = RNDIS_MESSAGE_SIZE(काष्ठा rndis_packet);

	hash = skb_get_hash_raw(skb);
	अगर (hash != 0 && net->real_num_tx_queues > 1) अणु
		u32 *hash_info;

		rndis_msg_size += NDIS_HASH_PPI_SIZE;
		hash_info = init_ppi_data(rndis_msg, NDIS_HASH_PPI_SIZE,
					  NBL_HASH_VALUE);
		*hash_info = hash;
	पूर्ण

	/* When using AF_PACKET we need to drop VLAN header from
	 * the frame and update the SKB to allow the HOST OS
	 * to transmit the 802.1Q packet
	 */
	अगर (skb->protocol == htons(ETH_P_8021Q)) अणु
		u16 vlan_tci;

		skb_reset_mac_header(skb);
		अगर (eth_type_vlan(eth_hdr(skb)->h_proto)) अणु
			अगर (unlikely(__skb_vlan_pop(skb, &vlan_tci) != 0)) अणु
				++net_device_ctx->eth_stats.vlan_error;
				जाओ drop;
			पूर्ण

			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tci);
			/* Update the NDIS header pkt lengths */
			packet->total_data_buflen -= VLAN_HLEN;
			packet->total_bytes -= VLAN_HLEN;
			rndis_msg->msg_len = packet->total_data_buflen;
			rndis_msg->msg.pkt.data_len = packet->total_data_buflen;
		पूर्ण
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		काष्ठा ndis_pkt_8021q_info *vlan;

		rndis_msg_size += NDIS_VLAN_PPI_SIZE;
		vlan = init_ppi_data(rndis_msg, NDIS_VLAN_PPI_SIZE,
				     IEEE_8021Q_INFO);

		vlan->value = 0;
		vlan->vlanid = skb_vlan_tag_get_id(skb);
		vlan->cfi = skb_vlan_tag_get_cfi(skb);
		vlan->pri = skb_vlan_tag_get_prio(skb);
	पूर्ण

	अगर (skb_is_gso(skb)) अणु
		काष्ठा ndis_tcp_lso_info *lso_info;

		rndis_msg_size += NDIS_LSO_PPI_SIZE;
		lso_info = init_ppi_data(rndis_msg, NDIS_LSO_PPI_SIZE,
					 TCP_LARGESEND_PKTINFO);

		lso_info->value = 0;
		lso_info->lso_v2_transmit.type = NDIS_TCP_LARGE_SEND_OFFLOAD_V2_TYPE;
		अगर (skb->protocol == htons(ETH_P_IP)) अणु
			lso_info->lso_v2_transmit.ip_version =
				NDIS_TCP_LARGE_SEND_OFFLOAD_IPV4;
			ip_hdr(skb)->tot_len = 0;
			ip_hdr(skb)->check = 0;
			tcp_hdr(skb)->check =
				~csum_tcpudp_magic(ip_hdr(skb)->saddr,
						   ip_hdr(skb)->daddr, 0, IPPROTO_TCP, 0);
		पूर्ण अन्यथा अणु
			lso_info->lso_v2_transmit.ip_version =
				NDIS_TCP_LARGE_SEND_OFFLOAD_IPV6;
			tcp_v6_gso_csum_prep(skb);
		पूर्ण
		lso_info->lso_v2_transmit.tcp_header_offset = skb_transport_offset(skb);
		lso_info->lso_v2_transmit.mss = skb_shinfo(skb)->gso_size;
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		अगर (net_checksum_info(skb) & net_device_ctx->tx_checksum_mask) अणु
			काष्ठा ndis_tcp_ip_checksum_info *csum_info;

			rndis_msg_size += NDIS_CSUM_PPI_SIZE;
			csum_info = init_ppi_data(rndis_msg, NDIS_CSUM_PPI_SIZE,
						  TCPIP_CHKSUM_PKTINFO);

			csum_info->value = 0;
			csum_info->transmit.tcp_header_offset = skb_transport_offset(skb);

			अगर (skb->protocol == htons(ETH_P_IP)) अणु
				csum_info->transmit.is_ipv4 = 1;

				अगर (ip_hdr(skb)->protocol == IPPROTO_TCP)
					csum_info->transmit.tcp_checksum = 1;
				अन्यथा
					csum_info->transmit.udp_checksum = 1;
			पूर्ण अन्यथा अणु
				csum_info->transmit.is_ipv6 = 1;

				अगर (ipv6_hdr(skb)->nexthdr == IPPROTO_TCP)
					csum_info->transmit.tcp_checksum = 1;
				अन्यथा
					csum_info->transmit.udp_checksum = 1;
			पूर्ण
		पूर्ण अन्यथा अणु
			/* Can't करो offload of this type of checksum */
			अगर (skb_checksum_help(skb))
				जाओ drop;
		पूर्ण
	पूर्ण

	/* Start filling in the page buffers with the rndis hdr */
	rndis_msg->msg_len += rndis_msg_size;
	packet->total_data_buflen = rndis_msg->msg_len;
	packet->page_buf_cnt = init_page_array(rndis_msg, rndis_msg_size,
					       skb, packet, pb);

	/* बारtamp packet in software */
	skb_tx_बारtamp(skb);

	ret = netvsc_send(net, packet, rndis_msg, pb, skb, xdp_tx);
	अगर (likely(ret == 0))
		वापस NETDEV_TX_OK;

	अगर (ret == -EAGAIN) अणु
		++net_device_ctx->eth_stats.tx_busy;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	अगर (ret == -ENOSPC)
		++net_device_ctx->eth_stats.tx_no_space;

drop:
	dev_kमुक्त_skb_any(skb);
	net->stats.tx_dropped++;

	वापस NETDEV_TX_OK;

no_memory:
	++net_device_ctx->eth_stats.tx_no_memory;
	जाओ drop;
पूर्ण

अटल netdev_tx_t netvsc_start_xmit(काष्ठा sk_buff *skb,
				     काष्ठा net_device *ndev)
अणु
	वापस netvsc_xmit(skb, ndev, false);
पूर्ण

/*
 * netvsc_linkstatus_callback - Link up/करोwn notअगरication
 */
व्योम netvsc_linkstatus_callback(काष्ठा net_device *net,
				काष्ठा rndis_message *resp,
				व्योम *data, u32 data_buflen)
अणु
	काष्ठा rndis_indicate_status *indicate = &resp->msg.indicate_status;
	काष्ठा net_device_context *ndev_ctx = netdev_priv(net);
	काष्ठा netvsc_reconfig *event;
	अचिन्हित दीर्घ flags;

	/* Ensure the packet is big enough to access its fields */
	अगर (resp->msg_len - RNDIS_HEADER_SIZE < माप(काष्ठा rndis_indicate_status)) अणु
		netdev_err(net, "invalid rndis_indicate_status packet, len: %u\n",
			   resp->msg_len);
		वापस;
	पूर्ण

	/* Copy the RNDIS indicate status पूर्णांकo nvchan->recv_buf */
	स_नकल(indicate, data + RNDIS_HEADER_SIZE, माप(*indicate));

	/* Update the physical link speed when changing to another vSwitch */
	अगर (indicate->status == RNDIS_STATUS_LINK_SPEED_CHANGE) अणु
		u32 speed;

		/* Validate status_buf_offset and status_buflen.
		 *
		 * Certain (pre-Fe) implementations of Hyper-V's vSwitch didn't account
		 * क्रम the status buffer field in resp->msg_len; perक्रमm the validation
		 * using data_buflen (>= resp->msg_len).
		 */
		अगर (indicate->status_buflen < माप(speed) ||
		    indicate->status_buf_offset < माप(*indicate) ||
		    data_buflen - RNDIS_HEADER_SIZE < indicate->status_buf_offset ||
		    data_buflen - RNDIS_HEADER_SIZE - indicate->status_buf_offset
				< indicate->status_buflen) अणु
			netdev_err(net, "invalid rndis_indicate_status packet\n");
			वापस;
		पूर्ण

		speed = *(u32 *)(data + RNDIS_HEADER_SIZE + indicate->status_buf_offset) / 10000;
		ndev_ctx->speed = speed;
		वापस;
	पूर्ण

	/* Handle these link change statuses below */
	अगर (indicate->status != RNDIS_STATUS_NETWORK_CHANGE &&
	    indicate->status != RNDIS_STATUS_MEDIA_CONNECT &&
	    indicate->status != RNDIS_STATUS_MEDIA_DISCONNECT)
		वापस;

	अगर (net->reg_state != NETREG_REGISTERED)
		वापस;

	event = kzalloc(माप(*event), GFP_ATOMIC);
	अगर (!event)
		वापस;
	event->event = indicate->status;

	spin_lock_irqsave(&ndev_ctx->lock, flags);
	list_add_tail(&event->list, &ndev_ctx->reconfig_events);
	spin_unlock_irqrestore(&ndev_ctx->lock, flags);

	schedule_delayed_work(&ndev_ctx->dwork, 0);
पूर्ण

अटल व्योम netvsc_xdp_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	पूर्णांक rc;

	skb->queue_mapping = skb_get_rx_queue(skb);
	__skb_push(skb, ETH_HLEN);

	rc = netvsc_xmit(skb, ndev, true);

	अगर (dev_xmit_complete(rc))
		वापस;

	dev_kमुक्त_skb_any(skb);
	ndev->stats.tx_dropped++;
पूर्ण

अटल व्योम netvsc_comp_ipcsum(काष्ठा sk_buff *skb)
अणु
	काष्ठा iphdr *iph = (काष्ठा iphdr *)skb->data;

	iph->check = 0;
	iph->check = ip_fast_csum(iph, iph->ihl);
पूर्ण

अटल काष्ठा sk_buff *netvsc_alloc_recv_skb(काष्ठा net_device *net,
					     काष्ठा netvsc_channel *nvchan,
					     काष्ठा xdp_buff *xdp)
अणु
	काष्ठा napi_काष्ठा *napi = &nvchan->napi;
	स्थिर काष्ठा ndis_pkt_8021q_info *vlan = &nvchan->rsc.vlan;
	स्थिर काष्ठा ndis_tcp_ip_checksum_info *csum_info =
						&nvchan->rsc.csum_info;
	स्थिर u32 *hash_info = &nvchan->rsc.hash_info;
	u8 ppi_flags = nvchan->rsc.ppi_flags;
	काष्ठा sk_buff *skb;
	व्योम *xbuf = xdp->data_hard_start;
	पूर्णांक i;

	अगर (xbuf) अणु
		अचिन्हित पूर्णांक hdroom = xdp->data - xdp->data_hard_start;
		अचिन्हित पूर्णांक xlen = xdp->data_end - xdp->data;
		अचिन्हित पूर्णांक frag_size = xdp->frame_sz;

		skb = build_skb(xbuf, frag_size);

		अगर (!skb) अणु
			__मुक्त_page(virt_to_page(xbuf));
			वापस शून्य;
		पूर्ण

		skb_reserve(skb, hdroom);
		skb_put(skb, xlen);
		skb->dev = napi->dev;
	पूर्ण अन्यथा अणु
		skb = napi_alloc_skb(napi, nvchan->rsc.pktlen);

		अगर (!skb)
			वापस शून्य;

		/* Copy to skb. This copy is needed here since the memory
		 * poपूर्णांकed by hv_netvsc_packet cannot be deallocated.
		 */
		क्रम (i = 0; i < nvchan->rsc.cnt; i++)
			skb_put_data(skb, nvchan->rsc.data[i],
				     nvchan->rsc.len[i]);
	पूर्ण

	skb->protocol = eth_type_trans(skb, net);

	/* skb is alपढ़ोy created with CHECKSUM_NONE */
	skb_checksum_none_निश्चित(skb);

	/* Incoming packets may have IP header checksum verअगरied by the host.
	 * They may not have IP header checksum computed after coalescing.
	 * We compute it here अगर the flags are set, because on Linux, the IP
	 * checksum is always checked.
	 */
	अगर ((ppi_flags & NVSC_RSC_CSUM_INFO) && csum_info->receive.ip_checksum_value_invalid &&
	    csum_info->receive.ip_checksum_succeeded &&
	    skb->protocol == htons(ETH_P_IP)) अणु
		/* Check that there is enough space to hold the IP header. */
		अगर (skb_headlen(skb) < माप(काष्ठा iphdr)) अणु
			kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण
		netvsc_comp_ipcsum(skb);
	पूर्ण

	/* Do L4 checksum offload अगर enabled and present. */
	अगर ((ppi_flags & NVSC_RSC_CSUM_INFO) && (net->features & NETIF_F_RXCSUM)) अणु
		अगर (csum_info->receive.tcp_checksum_succeeded ||
		    csum_info->receive.udp_checksum_succeeded)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	अगर ((ppi_flags & NVSC_RSC_HASH_INFO) && (net->features & NETIF_F_RXHASH))
		skb_set_hash(skb, *hash_info, PKT_HASH_TYPE_L4);

	अगर (ppi_flags & NVSC_RSC_VLAN) अणु
		u16 vlan_tci = vlan->vlanid | (vlan->pri << VLAN_PRIO_SHIFT) |
			(vlan->cfi ? VLAN_CFI_MASK : 0);

		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       vlan_tci);
	पूर्ण

	वापस skb;
पूर्ण

/*
 * netvsc_recv_callback -  Callback when we receive a packet from the
 * "wire" on the specअगरied device.
 */
पूर्णांक netvsc_recv_callback(काष्ठा net_device *net,
			 काष्ठा netvsc_device *net_device,
			 काष्ठा netvsc_channel *nvchan)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(net);
	काष्ठा vmbus_channel *channel = nvchan->channel;
	u16 q_idx = channel->offermsg.offer.sub_channel_index;
	काष्ठा sk_buff *skb;
	काष्ठा netvsc_stats *rx_stats = &nvchan->rx_stats;
	काष्ठा xdp_buff xdp;
	u32 act;

	अगर (net->reg_state != NETREG_REGISTERED)
		वापस NVSP_STAT_FAIL;

	act = netvsc_run_xdp(net, nvchan, &xdp);

	अगर (act != XDP_PASS && act != XDP_TX) अणु
		u64_stats_update_begin(&rx_stats->syncp);
		rx_stats->xdp_drop++;
		u64_stats_update_end(&rx_stats->syncp);

		वापस NVSP_STAT_SUCCESS; /* consumed by XDP */
	पूर्ण

	/* Allocate a skb - TODO direct I/O to pages? */
	skb = netvsc_alloc_recv_skb(net, nvchan, &xdp);

	अगर (unlikely(!skb)) अणु
		++net_device_ctx->eth_stats.rx_no_memory;
		वापस NVSP_STAT_FAIL;
	पूर्ण

	skb_record_rx_queue(skb, q_idx);

	/*
	 * Even अगर injecting the packet, record the statistics
	 * on the synthetic device because modअगरying the VF device
	 * statistics will not work correctly.
	 */
	u64_stats_update_begin(&rx_stats->syncp);
	rx_stats->packets++;
	rx_stats->bytes += nvchan->rsc.pktlen;

	अगर (skb->pkt_type == PACKET_BROADCAST)
		++rx_stats->broadcast;
	अन्यथा अगर (skb->pkt_type == PACKET_MULTICAST)
		++rx_stats->multicast;
	u64_stats_update_end(&rx_stats->syncp);

	अगर (act == XDP_TX) अणु
		netvsc_xdp_xmit(skb, net);
		वापस NVSP_STAT_SUCCESS;
	पूर्ण

	napi_gro_receive(&nvchan->napi, skb);
	वापस NVSP_STAT_SUCCESS;
पूर्ण

अटल व्योम netvsc_get_drvinfo(काष्ठा net_device *net,
			       काष्ठा ethtool_drvinfo *info)
अणु
	strlcpy(info->driver, KBUILD_MODNAME, माप(info->driver));
	strlcpy(info->fw_version, "N/A", माप(info->fw_version));
पूर्ण

अटल व्योम netvsc_get_channels(काष्ठा net_device *net,
				काष्ठा ethtool_channels *channel)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(net);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(net_device_ctx->nvdev);

	अगर (nvdev) अणु
		channel->max_combined	= nvdev->max_chn;
		channel->combined_count = nvdev->num_chn;
	पूर्ण
पूर्ण

/* Alloc काष्ठा netvsc_device_info, and initialize it from either existing
 * काष्ठा netvsc_device, or from शेष values.
 */
अटल
काष्ठा netvsc_device_info *netvsc_devinfo_get(काष्ठा netvsc_device *nvdev)
अणु
	काष्ठा netvsc_device_info *dev_info;
	काष्ठा bpf_prog *prog;

	dev_info = kzalloc(माप(*dev_info), GFP_ATOMIC);

	अगर (!dev_info)
		वापस शून्य;

	अगर (nvdev) अणु
		ASSERT_RTNL();

		dev_info->num_chn = nvdev->num_chn;
		dev_info->send_sections = nvdev->send_section_cnt;
		dev_info->send_section_size = nvdev->send_section_size;
		dev_info->recv_sections = nvdev->recv_section_cnt;
		dev_info->recv_section_size = nvdev->recv_section_size;

		स_नकल(dev_info->rss_key, nvdev->extension->rss_key,
		       NETVSC_HASH_KEYLEN);

		prog = netvsc_xdp_get(nvdev);
		अगर (prog) अणु
			bpf_prog_inc(prog);
			dev_info->bprog = prog;
		पूर्ण
	पूर्ण अन्यथा अणु
		dev_info->num_chn = VRSS_CHANNEL_DEFAULT;
		dev_info->send_sections = NETVSC_DEFAULT_TX;
		dev_info->send_section_size = NETVSC_SEND_SECTION_SIZE;
		dev_info->recv_sections = NETVSC_DEFAULT_RX;
		dev_info->recv_section_size = NETVSC_RECV_SECTION_SIZE;
	पूर्ण

	वापस dev_info;
पूर्ण

/* Free काष्ठा netvsc_device_info */
अटल व्योम netvsc_devinfo_put(काष्ठा netvsc_device_info *dev_info)
अणु
	अगर (dev_info->bprog) अणु
		ASSERT_RTNL();
		bpf_prog_put(dev_info->bprog);
	पूर्ण

	kमुक्त(dev_info);
पूर्ण

अटल पूर्णांक netvsc_detach(काष्ठा net_device *ndev,
			 काष्ठा netvsc_device *nvdev)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	काष्ठा hv_device *hdev = ndev_ctx->device_ctx;
	पूर्णांक ret;

	/* Don't try continuing to try and setup sub channels */
	अगर (cancel_work_sync(&nvdev->subchan_work))
		nvdev->num_chn = 1;

	netvsc_xdp_set(ndev, शून्य, शून्य, nvdev);

	/* If device was up (receiving) then shutकरोwn */
	अगर (netअगर_running(ndev)) अणु
		netvsc_tx_disable(nvdev, ndev);

		ret = rndis_filter_बंद(nvdev);
		अगर (ret) अणु
			netdev_err(ndev,
				   "unable to close device (ret %d).\n", ret);
			वापस ret;
		पूर्ण

		ret = netvsc_रुको_until_empty(nvdev);
		अगर (ret) अणु
			netdev_err(ndev,
				   "Ring buffer not empty after closing rndis\n");
			वापस ret;
		पूर्ण
	पूर्ण

	netअगर_device_detach(ndev);

	rndis_filter_device_हटाओ(hdev, nvdev);

	वापस 0;
पूर्ण

अटल पूर्णांक netvsc_attach(काष्ठा net_device *ndev,
			 काष्ठा netvsc_device_info *dev_info)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	काष्ठा hv_device *hdev = ndev_ctx->device_ctx;
	काष्ठा netvsc_device *nvdev;
	काष्ठा rndis_device *rdev;
	काष्ठा bpf_prog *prog;
	पूर्णांक ret = 0;

	nvdev = rndis_filter_device_add(hdev, dev_info);
	अगर (IS_ERR(nvdev))
		वापस PTR_ERR(nvdev);

	अगर (nvdev->num_chn > 1) अणु
		ret = rndis_set_subchannel(ndev, nvdev, dev_info);

		/* अगर unavailable, just proceed with one queue */
		अगर (ret) अणु
			nvdev->max_chn = 1;
			nvdev->num_chn = 1;
		पूर्ण
	पूर्ण

	prog = dev_info->bprog;
	अगर (prog) अणु
		bpf_prog_inc(prog);
		ret = netvsc_xdp_set(ndev, prog, शून्य, nvdev);
		अगर (ret) अणु
			bpf_prog_put(prog);
			जाओ err1;
		पूर्ण
	पूर्ण

	/* In any हाल device is now पढ़ोy */
	nvdev->tx_disable = false;
	netअगर_device_attach(ndev);

	/* Note: enable and attach happen when sub-channels setup */
	netअगर_carrier_off(ndev);

	अगर (netअगर_running(ndev)) अणु
		ret = rndis_filter_खोलो(nvdev);
		अगर (ret)
			जाओ err2;

		rdev = nvdev->extension;
		अगर (!rdev->link_state)
			netअगर_carrier_on(ndev);
	पूर्ण

	वापस 0;

err2:
	netअगर_device_detach(ndev);

err1:
	rndis_filter_device_हटाओ(hdev, nvdev);

	वापस ret;
पूर्ण

अटल पूर्णांक netvsc_set_channels(काष्ठा net_device *net,
			       काष्ठा ethtool_channels *channels)
अणु
	काष्ठा net_device_context *net_device_ctx = netdev_priv(net);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(net_device_ctx->nvdev);
	अचिन्हित पूर्णांक orig, count = channels->combined_count;
	काष्ठा netvsc_device_info *device_info;
	पूर्णांक ret;

	/* We करो not support separate count क्रम rx, tx, or other */
	अगर (count == 0 ||
	    channels->rx_count || channels->tx_count || channels->other_count)
		वापस -EINVAL;

	अगर (!nvdev || nvdev->destroy)
		वापस -ENODEV;

	अगर (nvdev->nvsp_version < NVSP_PROTOCOL_VERSION_5)
		वापस -EINVAL;

	अगर (count > nvdev->max_chn)
		वापस -EINVAL;

	orig = nvdev->num_chn;

	device_info = netvsc_devinfo_get(nvdev);

	अगर (!device_info)
		वापस -ENOMEM;

	device_info->num_chn = count;

	ret = netvsc_detach(net, nvdev);
	अगर (ret)
		जाओ out;

	ret = netvsc_attach(net, device_info);
	अगर (ret) अणु
		device_info->num_chn = orig;
		अगर (netvsc_attach(net, device_info))
			netdev_err(net, "restoring channel setting failed\n");
	पूर्ण

out:
	netvsc_devinfo_put(device_info);
	वापस ret;
पूर्ण

अटल व्योम netvsc_init_settings(काष्ठा net_device *dev)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);

	ndc->l4_hash = HV_DEFAULT_L4HASH;

	ndc->speed = SPEED_UNKNOWN;
	ndc->duplex = DUPLEX_FULL;

	dev->features = NETIF_F_LRO;
पूर्ण

अटल पूर्णांक netvsc_get_link_ksettings(काष्ठा net_device *dev,
				     काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);
	काष्ठा net_device *vf_netdev;

	vf_netdev = rtnl_dereference(ndc->vf_netdev);

	अगर (vf_netdev)
		वापस __ethtool_get_link_ksettings(vf_netdev, cmd);

	cmd->base.speed = ndc->speed;
	cmd->base.duplex = ndc->duplex;
	cmd->base.port = PORT_OTHER;

	वापस 0;
पूर्ण

अटल पूर्णांक netvsc_set_link_ksettings(काष्ठा net_device *dev,
				     स्थिर काष्ठा ethtool_link_ksettings *cmd)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);
	काष्ठा net_device *vf_netdev = rtnl_dereference(ndc->vf_netdev);

	अगर (vf_netdev) अणु
		अगर (!vf_netdev->ethtool_ops->set_link_ksettings)
			वापस -EOPNOTSUPP;

		वापस vf_netdev->ethtool_ops->set_link_ksettings(vf_netdev,
								  cmd);
	पूर्ण

	वापस ethtool_virtdev_set_link_ksettings(dev, cmd,
						  &ndc->speed, &ndc->duplex);
पूर्ण

अटल पूर्णांक netvsc_change_mtu(काष्ठा net_device *ndev, पूर्णांक mtu)
अणु
	काष्ठा net_device_context *ndevctx = netdev_priv(ndev);
	काष्ठा net_device *vf_netdev = rtnl_dereference(ndevctx->vf_netdev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndevctx->nvdev);
	पूर्णांक orig_mtu = ndev->mtu;
	काष्ठा netvsc_device_info *device_info;
	पूर्णांक ret = 0;

	अगर (!nvdev || nvdev->destroy)
		वापस -ENODEV;

	device_info = netvsc_devinfo_get(nvdev);

	अगर (!device_info)
		वापस -ENOMEM;

	/* Change MTU of underlying VF netdev first. */
	अगर (vf_netdev) अणु
		ret = dev_set_mtu(vf_netdev, mtu);
		अगर (ret)
			जाओ out;
	पूर्ण

	ret = netvsc_detach(ndev, nvdev);
	अगर (ret)
		जाओ rollback_vf;

	ndev->mtu = mtu;

	ret = netvsc_attach(ndev, device_info);
	अगर (!ret)
		जाओ out;

	/* Attempt rollback to original MTU */
	ndev->mtu = orig_mtu;

	अगर (netvsc_attach(ndev, device_info))
		netdev_err(ndev, "restoring mtu failed\n");
rollback_vf:
	अगर (vf_netdev)
		dev_set_mtu(vf_netdev, orig_mtu);

out:
	netvsc_devinfo_put(device_info);
	वापस ret;
पूर्ण

अटल व्योम netvsc_get_vf_stats(काष्ठा net_device *net,
				काष्ठा netvsc_vf_pcpu_stats *tot)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(net);
	पूर्णांक i;

	स_रखो(tot, 0, माप(*tot));

	क्रम_each_possible_cpu(i) अणु
		स्थिर काष्ठा netvsc_vf_pcpu_stats *stats
			= per_cpu_ptr(ndev_ctx->vf_stats, i);
		u64 rx_packets, rx_bytes, tx_packets, tx_bytes;
		अचिन्हित पूर्णांक start;

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			rx_packets = stats->rx_packets;
			tx_packets = stats->tx_packets;
			rx_bytes = stats->rx_bytes;
			tx_bytes = stats->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		tot->rx_packets += rx_packets;
		tot->tx_packets += tx_packets;
		tot->rx_bytes   += rx_bytes;
		tot->tx_bytes   += tx_bytes;
		tot->tx_dropped += stats->tx_dropped;
	पूर्ण
पूर्ण

अटल व्योम netvsc_get_pcpu_stats(काष्ठा net_device *net,
				  काष्ठा netvsc_ethtool_pcpu_stats *pcpu_tot)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(net);
	काष्ठा netvsc_device *nvdev = rcu_dereference_rtnl(ndev_ctx->nvdev);
	पूर्णांक i;

	/* fetch percpu stats of vf */
	क्रम_each_possible_cpu(i) अणु
		स्थिर काष्ठा netvsc_vf_pcpu_stats *stats =
			per_cpu_ptr(ndev_ctx->vf_stats, i);
		काष्ठा netvsc_ethtool_pcpu_stats *this_tot = &pcpu_tot[i];
		अचिन्हित पूर्णांक start;

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			this_tot->vf_rx_packets = stats->rx_packets;
			this_tot->vf_tx_packets = stats->tx_packets;
			this_tot->vf_rx_bytes = stats->rx_bytes;
			this_tot->vf_tx_bytes = stats->tx_bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));
		this_tot->rx_packets = this_tot->vf_rx_packets;
		this_tot->tx_packets = this_tot->vf_tx_packets;
		this_tot->rx_bytes   = this_tot->vf_rx_bytes;
		this_tot->tx_bytes   = this_tot->vf_tx_bytes;
	पूर्ण

	/* fetch percpu stats of netvsc */
	क्रम (i = 0; i < nvdev->num_chn; i++) अणु
		स्थिर काष्ठा netvsc_channel *nvchan = &nvdev->chan_table[i];
		स्थिर काष्ठा netvsc_stats *stats;
		काष्ठा netvsc_ethtool_pcpu_stats *this_tot =
			&pcpu_tot[nvchan->channel->target_cpu];
		u64 packets, bytes;
		अचिन्हित पूर्णांक start;

		stats = &nvchan->tx_stats;
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->packets;
			bytes = stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		this_tot->tx_bytes	+= bytes;
		this_tot->tx_packets	+= packets;

		stats = &nvchan->rx_stats;
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->packets;
			bytes = stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		this_tot->rx_bytes	+= bytes;
		this_tot->rx_packets	+= packets;
	पूर्ण
पूर्ण

अटल व्योम netvsc_get_stats64(काष्ठा net_device *net,
			       काष्ठा rtnl_link_stats64 *t)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(net);
	काष्ठा netvsc_device *nvdev;
	काष्ठा netvsc_vf_pcpu_stats vf_tot;
	पूर्णांक i;

	rcu_पढ़ो_lock();

	nvdev = rcu_dereference(ndev_ctx->nvdev);
	अगर (!nvdev)
		जाओ out;

	netdev_stats_to_stats64(t, &net->stats);

	netvsc_get_vf_stats(net, &vf_tot);
	t->rx_packets += vf_tot.rx_packets;
	t->tx_packets += vf_tot.tx_packets;
	t->rx_bytes   += vf_tot.rx_bytes;
	t->tx_bytes   += vf_tot.tx_bytes;
	t->tx_dropped += vf_tot.tx_dropped;

	क्रम (i = 0; i < nvdev->num_chn; i++) अणु
		स्थिर काष्ठा netvsc_channel *nvchan = &nvdev->chan_table[i];
		स्थिर काष्ठा netvsc_stats *stats;
		u64 packets, bytes, multicast;
		अचिन्हित पूर्णांक start;

		stats = &nvchan->tx_stats;
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->packets;
			bytes = stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		t->tx_bytes	+= bytes;
		t->tx_packets	+= packets;

		stats = &nvchan->rx_stats;
		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->packets;
			bytes = stats->bytes;
			multicast = stats->multicast + stats->broadcast;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		t->rx_bytes	+= bytes;
		t->rx_packets	+= packets;
		t->multicast	+= multicast;
	पूर्ण
out:
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक netvsc_set_mac_addr(काष्ठा net_device *ndev, व्योम *p)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(ndev);
	काष्ठा net_device *vf_netdev = rtnl_dereference(ndc->vf_netdev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndc->nvdev);
	काष्ठा sockaddr *addr = p;
	पूर्णांक err;

	err = eth_prepare_mac_addr_change(ndev, p);
	अगर (err)
		वापस err;

	अगर (!nvdev)
		वापस -ENODEV;

	अगर (vf_netdev) अणु
		err = dev_set_mac_address(vf_netdev, addr, शून्य);
		अगर (err)
			वापस err;
	पूर्ण

	err = rndis_filter_set_device_mac(nvdev, addr->sa_data);
	अगर (!err) अणु
		eth_commit_mac_addr_change(ndev, p);
	पूर्ण अन्यथा अगर (vf_netdev) अणु
		/* rollback change on VF */
		स_नकल(addr->sa_data, ndev->dev_addr, ETH_ALEN);
		dev_set_mac_address(vf_netdev, addr, शून्य);
	पूर्ण

	वापस err;
पूर्ण

अटल स्थिर काष्ठा अणु
	अक्षर name[ETH_GSTRING_LEN];
	u16 offset;
पूर्ण netvsc_stats[] = अणु
	अणु "tx_scattered", दुरत्व(काष्ठा netvsc_ethtool_stats, tx_scattered) पूर्ण,
	अणु "tx_no_memory", दुरत्व(काष्ठा netvsc_ethtool_stats, tx_no_memory) पूर्ण,
	अणु "tx_no_space",  दुरत्व(काष्ठा netvsc_ethtool_stats, tx_no_space) पूर्ण,
	अणु "tx_too_big",	  दुरत्व(काष्ठा netvsc_ethtool_stats, tx_too_big) पूर्ण,
	अणु "tx_busy",	  दुरत्व(काष्ठा netvsc_ethtool_stats, tx_busy) पूर्ण,
	अणु "tx_send_full", दुरत्व(काष्ठा netvsc_ethtool_stats, tx_send_full) पूर्ण,
	अणु "rx_comp_busy", दुरत्व(काष्ठा netvsc_ethtool_stats, rx_comp_busy) पूर्ण,
	अणु "rx_no_memory", दुरत्व(काष्ठा netvsc_ethtool_stats, rx_no_memory) पूर्ण,
	अणु "stop_queue", दुरत्व(काष्ठा netvsc_ethtool_stats, stop_queue) पूर्ण,
	अणु "wake_queue", दुरत्व(काष्ठा netvsc_ethtool_stats, wake_queue) पूर्ण,
	अणु "vlan_error", दुरत्व(काष्ठा netvsc_ethtool_stats, vlan_error) पूर्ण,
पूर्ण, pcpu_stats[] = अणु
	अणु "cpu%u_rx_packets",
		दुरत्व(काष्ठा netvsc_ethtool_pcpu_stats, rx_packets) पूर्ण,
	अणु "cpu%u_rx_bytes",
		दुरत्व(काष्ठा netvsc_ethtool_pcpu_stats, rx_bytes) पूर्ण,
	अणु "cpu%u_tx_packets",
		दुरत्व(काष्ठा netvsc_ethtool_pcpu_stats, tx_packets) पूर्ण,
	अणु "cpu%u_tx_bytes",
		दुरत्व(काष्ठा netvsc_ethtool_pcpu_stats, tx_bytes) पूर्ण,
	अणु "cpu%u_vf_rx_packets",
		दुरत्व(काष्ठा netvsc_ethtool_pcpu_stats, vf_rx_packets) पूर्ण,
	अणु "cpu%u_vf_rx_bytes",
		दुरत्व(काष्ठा netvsc_ethtool_pcpu_stats, vf_rx_bytes) पूर्ण,
	अणु "cpu%u_vf_tx_packets",
		दुरत्व(काष्ठा netvsc_ethtool_pcpu_stats, vf_tx_packets) पूर्ण,
	अणु "cpu%u_vf_tx_bytes",
		दुरत्व(काष्ठा netvsc_ethtool_pcpu_stats, vf_tx_bytes) पूर्ण,
पूर्ण, vf_stats[] = अणु
	अणु "vf_rx_packets", दुरत्व(काष्ठा netvsc_vf_pcpu_stats, rx_packets) पूर्ण,
	अणु "vf_rx_bytes",   दुरत्व(काष्ठा netvsc_vf_pcpu_stats, rx_bytes) पूर्ण,
	अणु "vf_tx_packets", दुरत्व(काष्ठा netvsc_vf_pcpu_stats, tx_packets) पूर्ण,
	अणु "vf_tx_bytes",   दुरत्व(काष्ठा netvsc_vf_pcpu_stats, tx_bytes) पूर्ण,
	अणु "vf_tx_dropped", दुरत्व(काष्ठा netvsc_vf_pcpu_stats, tx_dropped) पूर्ण,
पूर्ण;

#घोषणा NETVSC_GLOBAL_STATS_LEN	ARRAY_SIZE(netvsc_stats)
#घोषणा NETVSC_VF_STATS_LEN	ARRAY_SIZE(vf_stats)

/* statistics per queue (rx/tx packets/bytes) */
#घोषणा NETVSC_PCPU_STATS_LEN (num_present_cpus() * ARRAY_SIZE(pcpu_stats))

/* 5 statistics per queue (rx/tx packets/bytes, rx xdp_drop) */
#घोषणा NETVSC_QUEUE_STATS_LEN(dev) ((dev)->num_chn * 5)

अटल पूर्णांक netvsc_get_sset_count(काष्ठा net_device *dev, पूर्णांक string_set)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndc->nvdev);

	अगर (!nvdev)
		वापस -ENODEV;

	चयन (string_set) अणु
	हाल ETH_SS_STATS:
		वापस NETVSC_GLOBAL_STATS_LEN
			+ NETVSC_VF_STATS_LEN
			+ NETVSC_QUEUE_STATS_LEN(nvdev)
			+ NETVSC_PCPU_STATS_LEN;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम netvsc_get_ethtool_stats(काष्ठा net_device *dev,
				     काष्ठा ethtool_stats *stats, u64 *data)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndc->nvdev);
	स्थिर व्योम *nds = &ndc->eth_stats;
	स्थिर काष्ठा netvsc_stats *qstats;
	काष्ठा netvsc_vf_pcpu_stats sum;
	काष्ठा netvsc_ethtool_pcpu_stats *pcpu_sum;
	अचिन्हित पूर्णांक start;
	u64 packets, bytes;
	u64 xdp_drop;
	पूर्णांक i, j, cpu;

	अगर (!nvdev)
		वापस;

	क्रम (i = 0; i < NETVSC_GLOBAL_STATS_LEN; i++)
		data[i] = *(अचिन्हित दीर्घ *)(nds + netvsc_stats[i].offset);

	netvsc_get_vf_stats(dev, &sum);
	क्रम (j = 0; j < NETVSC_VF_STATS_LEN; j++)
		data[i++] = *(u64 *)((व्योम *)&sum + vf_stats[j].offset);

	क्रम (j = 0; j < nvdev->num_chn; j++) अणु
		qstats = &nvdev->chan_table[j].tx_stats;

		करो अणु
			start = u64_stats_fetch_begin_irq(&qstats->syncp);
			packets = qstats->packets;
			bytes = qstats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&qstats->syncp, start));
		data[i++] = packets;
		data[i++] = bytes;

		qstats = &nvdev->chan_table[j].rx_stats;
		करो अणु
			start = u64_stats_fetch_begin_irq(&qstats->syncp);
			packets = qstats->packets;
			bytes = qstats->bytes;
			xdp_drop = qstats->xdp_drop;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&qstats->syncp, start));
		data[i++] = packets;
		data[i++] = bytes;
		data[i++] = xdp_drop;
	पूर्ण

	pcpu_sum = kvदो_स्मृति_array(num_possible_cpus(),
				  माप(काष्ठा netvsc_ethtool_pcpu_stats),
				  GFP_KERNEL);
	netvsc_get_pcpu_stats(dev, pcpu_sum);
	क्रम_each_present_cpu(cpu) अणु
		काष्ठा netvsc_ethtool_pcpu_stats *this_sum = &pcpu_sum[cpu];

		क्रम (j = 0; j < ARRAY_SIZE(pcpu_stats); j++)
			data[i++] = *(u64 *)((व्योम *)this_sum
					     + pcpu_stats[j].offset);
	पूर्ण
	kvमुक्त(pcpu_sum);
पूर्ण

अटल व्योम netvsc_get_strings(काष्ठा net_device *dev, u32 stringset, u8 *data)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndc->nvdev);
	u8 *p = data;
	पूर्णांक i, cpu;

	अगर (!nvdev)
		वापस;

	चयन (stringset) अणु
	हाल ETH_SS_STATS:
		क्रम (i = 0; i < ARRAY_SIZE(netvsc_stats); i++)
			ethtool_प्र_लिखो(&p, netvsc_stats[i].name);

		क्रम (i = 0; i < ARRAY_SIZE(vf_stats); i++)
			ethtool_प्र_लिखो(&p, vf_stats[i].name);

		क्रम (i = 0; i < nvdev->num_chn; i++) अणु
			ethtool_प्र_लिखो(&p, "tx_queue_%u_packets", i);
			ethtool_प्र_लिखो(&p, "tx_queue_%u_bytes", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_packets", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_bytes", i);
			ethtool_प्र_लिखो(&p, "rx_queue_%u_xdp_drop", i);
		पूर्ण

		क्रम_each_present_cpu(cpu) अणु
			क्रम (i = 0; i < ARRAY_SIZE(pcpu_stats); i++)
				ethtool_प्र_लिखो(&p, pcpu_stats[i].name, cpu);
		पूर्ण

		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक
netvsc_get_rss_hash_opts(काष्ठा net_device_context *ndc,
			 काष्ठा ethtool_rxnfc *info)
अणु
	स्थिर u32 l4_flag = RXH_L4_B_0_1 | RXH_L4_B_2_3;

	info->data = RXH_IP_SRC | RXH_IP_DST;

	चयन (info->flow_type) अणु
	हाल TCP_V4_FLOW:
		अगर (ndc->l4_hash & HV_TCP4_L4HASH)
			info->data |= l4_flag;

		अवरोध;

	हाल TCP_V6_FLOW:
		अगर (ndc->l4_hash & HV_TCP6_L4HASH)
			info->data |= l4_flag;

		अवरोध;

	हाल UDP_V4_FLOW:
		अगर (ndc->l4_hash & HV_UDP4_L4HASH)
			info->data |= l4_flag;

		अवरोध;

	हाल UDP_V6_FLOW:
		अगर (ndc->l4_hash & HV_UDP6_L4HASH)
			info->data |= l4_flag;

		अवरोध;

	हाल IPV4_FLOW:
	हाल IPV6_FLOW:
		अवरोध;
	शेष:
		info->data = 0;
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
netvsc_get_rxnfc(काष्ठा net_device *dev, काष्ठा ethtool_rxnfc *info,
		 u32 *rules)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndc->nvdev);

	अगर (!nvdev)
		वापस -ENODEV;

	चयन (info->cmd) अणु
	हाल ETHTOOL_GRXRINGS:
		info->data = nvdev->num_chn;
		वापस 0;

	हाल ETHTOOL_GRXFH:
		वापस netvsc_get_rss_hash_opts(ndc, info);
	पूर्ण
	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक netvsc_set_rss_hash_opts(काष्ठा net_device_context *ndc,
				    काष्ठा ethtool_rxnfc *info)
अणु
	अगर (info->data == (RXH_IP_SRC | RXH_IP_DST |
			   RXH_L4_B_0_1 | RXH_L4_B_2_3)) अणु
		चयन (info->flow_type) अणु
		हाल TCP_V4_FLOW:
			ndc->l4_hash |= HV_TCP4_L4HASH;
			अवरोध;

		हाल TCP_V6_FLOW:
			ndc->l4_hash |= HV_TCP6_L4HASH;
			अवरोध;

		हाल UDP_V4_FLOW:
			ndc->l4_hash |= HV_UDP4_L4HASH;
			अवरोध;

		हाल UDP_V6_FLOW:
			ndc->l4_hash |= HV_UDP6_L4HASH;
			अवरोध;

		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (info->data == (RXH_IP_SRC | RXH_IP_DST)) अणु
		चयन (info->flow_type) अणु
		हाल TCP_V4_FLOW:
			ndc->l4_hash &= ~HV_TCP4_L4HASH;
			अवरोध;

		हाल TCP_V6_FLOW:
			ndc->l4_hash &= ~HV_TCP6_L4HASH;
			अवरोध;

		हाल UDP_V4_FLOW:
			ndc->l4_hash &= ~HV_UDP4_L4HASH;
			अवरोध;

		हाल UDP_V6_FLOW:
			ndc->l4_hash &= ~HV_UDP6_L4HASH;
			अवरोध;

		शेष:
			वापस -EOPNOTSUPP;
		पूर्ण

		वापस 0;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक
netvsc_set_rxnfc(काष्ठा net_device *ndev, काष्ठा ethtool_rxnfc *info)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(ndev);

	अगर (info->cmd == ETHTOOL_SRXFH)
		वापस netvsc_set_rss_hash_opts(ndc, info);

	वापस -EOPNOTSUPP;
पूर्ण

अटल u32 netvsc_get_rxfh_key_size(काष्ठा net_device *dev)
अणु
	वापस NETVSC_HASH_KEYLEN;
पूर्ण

अटल u32 netvsc_rss_indir_size(काष्ठा net_device *dev)
अणु
	वापस ITAB_NUM;
पूर्ण

अटल पूर्णांक netvsc_get_rxfh(काष्ठा net_device *dev, u32 *indir, u8 *key,
			   u8 *hfunc)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);
	काष्ठा netvsc_device *ndev = rtnl_dereference(ndc->nvdev);
	काष्ठा rndis_device *rndis_dev;
	पूर्णांक i;

	अगर (!ndev)
		वापस -ENODEV;

	अगर (hfunc)
		*hfunc = ETH_RSS_HASH_TOP;	/* Toeplitz */

	rndis_dev = ndev->extension;
	अगर (indir) अणु
		क्रम (i = 0; i < ITAB_NUM; i++)
			indir[i] = ndc->rx_table[i];
	पूर्ण

	अगर (key)
		स_नकल(key, rndis_dev->rss_key, NETVSC_HASH_KEYLEN);

	वापस 0;
पूर्ण

अटल पूर्णांक netvsc_set_rxfh(काष्ठा net_device *dev, स्थिर u32 *indir,
			   स्थिर u8 *key, स्थिर u8 hfunc)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(dev);
	काष्ठा netvsc_device *ndev = rtnl_dereference(ndc->nvdev);
	काष्ठा rndis_device *rndis_dev;
	पूर्णांक i;

	अगर (!ndev)
		वापस -ENODEV;

	अगर (hfunc != ETH_RSS_HASH_NO_CHANGE && hfunc != ETH_RSS_HASH_TOP)
		वापस -EOPNOTSUPP;

	rndis_dev = ndev->extension;
	अगर (indir) अणु
		क्रम (i = 0; i < ITAB_NUM; i++)
			अगर (indir[i] >= ndev->num_chn)
				वापस -EINVAL;

		क्रम (i = 0; i < ITAB_NUM; i++)
			ndc->rx_table[i] = indir[i];
	पूर्ण

	अगर (!key) अणु
		अगर (!indir)
			वापस 0;

		key = rndis_dev->rss_key;
	पूर्ण

	वापस rndis_filter_set_rss_param(rndis_dev, key);
पूर्ण

/* Hyper-V RNDIS protocol करोes not have ring in the HW sense.
 * It करोes have pre-allocated receive area which is भागided पूर्णांकo sections.
 */
अटल व्योम __netvsc_get_ringparam(काष्ठा netvsc_device *nvdev,
				   काष्ठा ethtool_ringparam *ring)
अणु
	u32 max_buf_size;

	ring->rx_pending = nvdev->recv_section_cnt;
	ring->tx_pending = nvdev->send_section_cnt;

	अगर (nvdev->nvsp_version <= NVSP_PROTOCOL_VERSION_2)
		max_buf_size = NETVSC_RECEIVE_BUFFER_SIZE_LEGACY;
	अन्यथा
		max_buf_size = NETVSC_RECEIVE_BUFFER_SIZE;

	ring->rx_max_pending = max_buf_size / nvdev->recv_section_size;
	ring->tx_max_pending = NETVSC_SEND_BUFFER_SIZE
		/ nvdev->send_section_size;
पूर्ण

अटल व्योम netvsc_get_ringparam(काष्ठा net_device *ndev,
				 काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा net_device_context *ndevctx = netdev_priv(ndev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndevctx->nvdev);

	अगर (!nvdev)
		वापस;

	__netvsc_get_ringparam(nvdev, ring);
पूर्ण

अटल पूर्णांक netvsc_set_ringparam(काष्ठा net_device *ndev,
				काष्ठा ethtool_ringparam *ring)
अणु
	काष्ठा net_device_context *ndevctx = netdev_priv(ndev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndevctx->nvdev);
	काष्ठा netvsc_device_info *device_info;
	काष्ठा ethtool_ringparam orig;
	u32 new_tx, new_rx;
	पूर्णांक ret = 0;

	अगर (!nvdev || nvdev->destroy)
		वापस -ENODEV;

	स_रखो(&orig, 0, माप(orig));
	__netvsc_get_ringparam(nvdev, &orig);

	new_tx = clamp_t(u32, ring->tx_pending,
			 NETVSC_MIN_TX_SECTIONS, orig.tx_max_pending);
	new_rx = clamp_t(u32, ring->rx_pending,
			 NETVSC_MIN_RX_SECTIONS, orig.rx_max_pending);

	अगर (new_tx == orig.tx_pending &&
	    new_rx == orig.rx_pending)
		वापस 0;	 /* no change */

	device_info = netvsc_devinfo_get(nvdev);

	अगर (!device_info)
		वापस -ENOMEM;

	device_info->send_sections = new_tx;
	device_info->recv_sections = new_rx;

	ret = netvsc_detach(ndev, nvdev);
	अगर (ret)
		जाओ out;

	ret = netvsc_attach(ndev, device_info);
	अगर (ret) अणु
		device_info->send_sections = orig.tx_pending;
		device_info->recv_sections = orig.rx_pending;

		अगर (netvsc_attach(ndev, device_info))
			netdev_err(ndev, "restoring ringparam failed");
	पूर्ण

out:
	netvsc_devinfo_put(device_info);
	वापस ret;
पूर्ण

अटल netdev_features_t netvsc_fix_features(काष्ठा net_device *ndev,
					     netdev_features_t features)
अणु
	काष्ठा net_device_context *ndevctx = netdev_priv(ndev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndevctx->nvdev);

	अगर (!nvdev || nvdev->destroy)
		वापस features;

	अगर ((features & NETIF_F_LRO) && netvsc_xdp_get(nvdev)) अणु
		features ^= NETIF_F_LRO;
		netdev_info(ndev, "Skip LRO - unsupported with XDP\n");
	पूर्ण

	वापस features;
पूर्ण

अटल पूर्णांक netvsc_set_features(काष्ठा net_device *ndev,
			       netdev_features_t features)
अणु
	netdev_features_t change = features ^ ndev->features;
	काष्ठा net_device_context *ndevctx = netdev_priv(ndev);
	काष्ठा netvsc_device *nvdev = rtnl_dereference(ndevctx->nvdev);
	काष्ठा net_device *vf_netdev = rtnl_dereference(ndevctx->vf_netdev);
	काष्ठा ndis_offload_params offloads;
	पूर्णांक ret = 0;

	अगर (!nvdev || nvdev->destroy)
		वापस -ENODEV;

	अगर (!(change & NETIF_F_LRO))
		जाओ syncvf;

	स_रखो(&offloads, 0, माप(काष्ठा ndis_offload_params));

	अगर (features & NETIF_F_LRO) अणु
		offloads.rsc_ip_v4 = NDIS_OFFLOAD_PARAMETERS_RSC_ENABLED;
		offloads.rsc_ip_v6 = NDIS_OFFLOAD_PARAMETERS_RSC_ENABLED;
	पूर्ण अन्यथा अणु
		offloads.rsc_ip_v4 = NDIS_OFFLOAD_PARAMETERS_RSC_DISABLED;
		offloads.rsc_ip_v6 = NDIS_OFFLOAD_PARAMETERS_RSC_DISABLED;
	पूर्ण

	ret = rndis_filter_set_offload_params(ndev, nvdev, &offloads);

	अगर (ret) अणु
		features ^= NETIF_F_LRO;
		ndev->features = features;
	पूर्ण

syncvf:
	अगर (!vf_netdev)
		वापस ret;

	vf_netdev->wanted_features = features;
	netdev_update_features(vf_netdev);

	वापस ret;
पूर्ण

अटल पूर्णांक netvsc_get_regs_len(काष्ठा net_device *netdev)
अणु
	वापस VRSS_SEND_TAB_SIZE * माप(u32);
पूर्ण

अटल व्योम netvsc_get_regs(काष्ठा net_device *netdev,
			    काष्ठा ethtool_regs *regs, व्योम *p)
अणु
	काष्ठा net_device_context *ndc = netdev_priv(netdev);
	u32 *regs_buff = p;

	/* increase the version, अगर buffer क्रमmat is changed. */
	regs->version = 1;

	स_नकल(regs_buff, ndc->tx_table, VRSS_SEND_TAB_SIZE * माप(u32));
पूर्ण

अटल u32 netvsc_get_msglevel(काष्ठा net_device *ndev)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);

	वापस ndev_ctx->msg_enable;
पूर्ण

अटल व्योम netvsc_set_msglevel(काष्ठा net_device *ndev, u32 val)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);

	ndev_ctx->msg_enable = val;
पूर्ण

अटल स्थिर काष्ठा ethtool_ops ethtool_ops = अणु
	.get_drvinfo	= netvsc_get_drvinfo,
	.get_regs_len	= netvsc_get_regs_len,
	.get_regs	= netvsc_get_regs,
	.get_msglevel	= netvsc_get_msglevel,
	.set_msglevel	= netvsc_set_msglevel,
	.get_link	= ethtool_op_get_link,
	.get_ethtool_stats = netvsc_get_ethtool_stats,
	.get_sset_count = netvsc_get_sset_count,
	.get_strings	= netvsc_get_strings,
	.get_channels   = netvsc_get_channels,
	.set_channels   = netvsc_set_channels,
	.get_ts_info	= ethtool_op_get_ts_info,
	.get_rxnfc	= netvsc_get_rxnfc,
	.set_rxnfc	= netvsc_set_rxnfc,
	.get_rxfh_key_size = netvsc_get_rxfh_key_size,
	.get_rxfh_indir_size = netvsc_rss_indir_size,
	.get_rxfh	= netvsc_get_rxfh,
	.set_rxfh	= netvsc_set_rxfh,
	.get_link_ksettings = netvsc_get_link_ksettings,
	.set_link_ksettings = netvsc_set_link_ksettings,
	.get_ringparam	= netvsc_get_ringparam,
	.set_ringparam	= netvsc_set_ringparam,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops device_ops = अणु
	.nकरो_खोलो =			netvsc_खोलो,
	.nकरो_stop =			netvsc_बंद,
	.nकरो_start_xmit =		netvsc_start_xmit,
	.nकरो_change_rx_flags =		netvsc_change_rx_flags,
	.nकरो_set_rx_mode =		netvsc_set_rx_mode,
	.nकरो_fix_features =		netvsc_fix_features,
	.nकरो_set_features =		netvsc_set_features,
	.nकरो_change_mtu =		netvsc_change_mtu,
	.nकरो_validate_addr =		eth_validate_addr,
	.nकरो_set_mac_address =		netvsc_set_mac_addr,
	.nकरो_select_queue =		netvsc_select_queue,
	.nकरो_get_stats64 =		netvsc_get_stats64,
	.nकरो_bpf =			netvsc_bpf,
पूर्ण;

/*
 * Handle link status changes. For RNDIS_STATUS_NETWORK_CHANGE emulate link
 * करोwn/up sequence. In हाल of RNDIS_STATUS_MEDIA_CONNECT when carrier is
 * present send GARP packet to network peers with netअगर_notअगरy_peers().
 */
अटल व्योम netvsc_link_change(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा net_device_context *ndev_ctx =
		container_of(w, काष्ठा net_device_context, dwork.work);
	काष्ठा hv_device *device_obj = ndev_ctx->device_ctx;
	काष्ठा net_device *net = hv_get_drvdata(device_obj);
	अचिन्हित दीर्घ flags, next_reconfig, delay;
	काष्ठा netvsc_reconfig *event = शून्य;
	काष्ठा netvsc_device *net_device;
	काष्ठा rndis_device *rdev;
	bool reschedule = false;

	/* अगर changes are happening, comeback later */
	अगर (!rtnl_trylock()) अणु
		schedule_delayed_work(&ndev_ctx->dwork, LINKCHANGE_INT);
		वापस;
	पूर्ण

	net_device = rtnl_dereference(ndev_ctx->nvdev);
	अगर (!net_device)
		जाओ out_unlock;

	rdev = net_device->extension;

	next_reconfig = ndev_ctx->last_reconfig + LINKCHANGE_INT;
	अगर (समय_is_after_jअगरfies(next_reconfig)) अणु
		/* link_watch only sends one notअगरication with current state
		 * per second, aव्योम करोing reconfig more frequently. Handle
		 * wrap around.
		 */
		delay = next_reconfig - jअगरfies;
		delay = delay < LINKCHANGE_INT ? delay : LINKCHANGE_INT;
		schedule_delayed_work(&ndev_ctx->dwork, delay);
		जाओ out_unlock;
	पूर्ण
	ndev_ctx->last_reconfig = jअगरfies;

	spin_lock_irqsave(&ndev_ctx->lock, flags);
	अगर (!list_empty(&ndev_ctx->reconfig_events)) अणु
		event = list_first_entry(&ndev_ctx->reconfig_events,
					 काष्ठा netvsc_reconfig, list);
		list_del(&event->list);
		reschedule = !list_empty(&ndev_ctx->reconfig_events);
	पूर्ण
	spin_unlock_irqrestore(&ndev_ctx->lock, flags);

	अगर (!event)
		जाओ out_unlock;

	चयन (event->event) अणु
		/* Only the following events are possible due to the check in
		 * netvsc_linkstatus_callback()
		 */
	हाल RNDIS_STATUS_MEDIA_CONNECT:
		अगर (rdev->link_state) अणु
			rdev->link_state = false;
			netअगर_carrier_on(net);
			netvsc_tx_enable(net_device, net);
		पूर्ण अन्यथा अणु
			__netdev_notअगरy_peers(net);
		पूर्ण
		kमुक्त(event);
		अवरोध;
	हाल RNDIS_STATUS_MEDIA_DISCONNECT:
		अगर (!rdev->link_state) अणु
			rdev->link_state = true;
			netअगर_carrier_off(net);
			netvsc_tx_disable(net_device, net);
		पूर्ण
		kमुक्त(event);
		अवरोध;
	हाल RNDIS_STATUS_NETWORK_CHANGE:
		/* Only makes sense अगर carrier is present */
		अगर (!rdev->link_state) अणु
			rdev->link_state = true;
			netअगर_carrier_off(net);
			netvsc_tx_disable(net_device, net);
			event->event = RNDIS_STATUS_MEDIA_CONNECT;
			spin_lock_irqsave(&ndev_ctx->lock, flags);
			list_add(&event->list, &ndev_ctx->reconfig_events);
			spin_unlock_irqrestore(&ndev_ctx->lock, flags);
			reschedule = true;
		पूर्ण
		अवरोध;
	पूर्ण

	rtnl_unlock();

	/* link_watch only sends one notअगरication with current state per
	 * second, handle next reconfig event in 2 seconds.
	 */
	अगर (reschedule)
		schedule_delayed_work(&ndev_ctx->dwork, LINKCHANGE_INT);

	वापस;

out_unlock:
	rtnl_unlock();
पूर्ण

अटल काष्ठा net_device *get_netvsc_byref(काष्ठा net_device *vf_netdev)
अणु
	काष्ठा net_device_context *net_device_ctx;
	काष्ठा net_device *dev;

	dev = netdev_master_upper_dev_get(vf_netdev);
	अगर (!dev || dev->netdev_ops != &device_ops)
		वापस शून्य;	/* not a netvsc device */

	net_device_ctx = netdev_priv(dev);
	अगर (!rtnl_dereference(net_device_ctx->nvdev))
		वापस शून्य;	/* device is हटाओd */

	वापस dev;
पूर्ण

/* Called when VF is injecting data पूर्णांकo network stack.
 * Change the associated network device from VF to netvsc.
 * note: alपढ़ोy called with rcu_पढ़ो_lock
 */
अटल rx_handler_result_t netvsc_vf_handle_frame(काष्ठा sk_buff **pskb)
अणु
	काष्ठा sk_buff *skb = *pskb;
	काष्ठा net_device *ndev = rcu_dereference(skb->dev->rx_handler_data);
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	काष्ठा netvsc_vf_pcpu_stats *pcpu_stats
		 = this_cpu_ptr(ndev_ctx->vf_stats);

	skb = skb_share_check(skb, GFP_ATOMIC);
	अगर (unlikely(!skb))
		वापस RX_HANDLER_CONSUMED;

	*pskb = skb;

	skb->dev = ndev;

	u64_stats_update_begin(&pcpu_stats->syncp);
	pcpu_stats->rx_packets++;
	pcpu_stats->rx_bytes += skb->len;
	u64_stats_update_end(&pcpu_stats->syncp);

	वापस RX_HANDLER_ANOTHER;
पूर्ण

अटल पूर्णांक netvsc_vf_join(काष्ठा net_device *vf_netdev,
			  काष्ठा net_device *ndev)
अणु
	काष्ठा net_device_context *ndev_ctx = netdev_priv(ndev);
	पूर्णांक ret;

	ret = netdev_rx_handler_रेजिस्टर(vf_netdev,
					 netvsc_vf_handle_frame, ndev);
	अगर (ret != 0) अणु
		netdev_err(vf_netdev,
			   "can not register netvsc VF receive handler (err = %d)\n",
			   ret);
		जाओ rx_handler_failed;
	पूर्ण

	ret = netdev_master_upper_dev_link(vf_netdev, ndev,
					   शून्य, शून्य, शून्य);
	अगर (ret != 0) अणु
		netdev_err(vf_netdev,
			   "can not set master device %s (err = %d)\n",
			   ndev->name, ret);
		जाओ upper_link_failed;
	पूर्ण

	/* set slave flag beक्रमe खोलो to prevent IPv6 addrconf */
	vf_netdev->flags |= IFF_SLAVE;

	schedule_delayed_work(&ndev_ctx->vf_takeover, VF_TAKEOVER_INT);

	call_netdevice_notअगरiers(NETDEV_JOIN, vf_netdev);

	netdev_info(vf_netdev, "joined to %s\n", ndev->name);
	वापस 0;

upper_link_failed:
	netdev_rx_handler_unरेजिस्टर(vf_netdev);
rx_handler_failed:
	वापस ret;
पूर्ण

अटल व्योम __netvsc_vf_setup(काष्ठा net_device *ndev,
			      काष्ठा net_device *vf_netdev)
अणु
	पूर्णांक ret;

	/* Align MTU of VF with master */
	ret = dev_set_mtu(vf_netdev, ndev->mtu);
	अगर (ret)
		netdev_warn(vf_netdev,
			    "unable to change mtu to %u\n", ndev->mtu);

	/* set multicast etc flags on VF */
	dev_change_flags(vf_netdev, ndev->flags | IFF_SLAVE, शून्य);

	/* sync address list from ndev to VF */
	netअगर_addr_lock_bh(ndev);
	dev_uc_sync(vf_netdev, ndev);
	dev_mc_sync(vf_netdev, ndev);
	netअगर_addr_unlock_bh(ndev);

	अगर (netअगर_running(ndev)) अणु
		ret = dev_खोलो(vf_netdev, शून्य);
		अगर (ret)
			netdev_warn(vf_netdev,
				    "unable to open: %d\n", ret);
	पूर्ण
पूर्ण

/* Setup VF as slave of the synthetic device.
 * Runs in workqueue to aव्योम recursion in netlink callbacks.
 */
अटल व्योम netvsc_vf_setup(काष्ठा work_काष्ठा *w)
अणु
	काष्ठा net_device_context *ndev_ctx
		= container_of(w, काष्ठा net_device_context, vf_takeover.work);
	काष्ठा net_device *ndev = hv_get_drvdata(ndev_ctx->device_ctx);
	काष्ठा net_device *vf_netdev;

	अगर (!rtnl_trylock()) अणु
		schedule_delayed_work(&ndev_ctx->vf_takeover, 0);
		वापस;
	पूर्ण

	vf_netdev = rtnl_dereference(ndev_ctx->vf_netdev);
	अगर (vf_netdev)
		__netvsc_vf_setup(ndev, vf_netdev);

	rtnl_unlock();
पूर्ण

/* Find netvsc by VF serial number.
 * The PCI hyperv controller records the serial number as the slot kobj name.
 */
अटल काष्ठा net_device *get_netvsc_byslot(स्थिर काष्ठा net_device *vf_netdev)
अणु
	काष्ठा device *parent = vf_netdev->dev.parent;
	काष्ठा net_device_context *ndev_ctx;
	काष्ठा net_device *ndev;
	काष्ठा pci_dev *pdev;
	u32 serial;

	अगर (!parent || !dev_is_pci(parent))
		वापस शून्य; /* not a PCI device */

	pdev = to_pci_dev(parent);
	अगर (!pdev->slot) अणु
		netdev_notice(vf_netdev, "no PCI slot information\n");
		वापस शून्य;
	पूर्ण

	अगर (kstrtou32(pci_slot_name(pdev->slot), 10, &serial)) अणु
		netdev_notice(vf_netdev, "Invalid vf serial:%s\n",
			      pci_slot_name(pdev->slot));
		वापस शून्य;
	पूर्ण

	list_क्रम_each_entry(ndev_ctx, &netvsc_dev_list, list) अणु
		अगर (!ndev_ctx->vf_alloc)
			जारी;

		अगर (ndev_ctx->vf_serial != serial)
			जारी;

		ndev = hv_get_drvdata(ndev_ctx->device_ctx);
		अगर (ndev->addr_len != vf_netdev->addr_len ||
		    स_भेद(ndev->perm_addr, vf_netdev->perm_addr,
			   ndev->addr_len) != 0)
			जारी;

		वापस ndev;

	पूर्ण

	netdev_notice(vf_netdev,
		      "no netdev found for vf serial:%u\n", serial);
	वापस शून्य;
पूर्ण

अटल पूर्णांक netvsc_रेजिस्टर_vf(काष्ठा net_device *vf_netdev)
अणु
	काष्ठा net_device_context *net_device_ctx;
	काष्ठा netvsc_device *netvsc_dev;
	काष्ठा bpf_prog *prog;
	काष्ठा net_device *ndev;
	पूर्णांक ret;

	अगर (vf_netdev->addr_len != ETH_ALEN)
		वापस NOTIFY_DONE;

	ndev = get_netvsc_byslot(vf_netdev);
	अगर (!ndev)
		वापस NOTIFY_DONE;

	net_device_ctx = netdev_priv(ndev);
	netvsc_dev = rtnl_dereference(net_device_ctx->nvdev);
	अगर (!netvsc_dev || rtnl_dereference(net_device_ctx->vf_netdev))
		वापस NOTIFY_DONE;

	/* अगर synthetic पूर्णांकerface is a dअगरferent namespace,
	 * then move the VF to that namespace; join will be
	 * करोne again in that context.
	 */
	अगर (!net_eq(dev_net(ndev), dev_net(vf_netdev))) अणु
		ret = dev_change_net_namespace(vf_netdev,
					       dev_net(ndev), "eth%d");
		अगर (ret)
			netdev_err(vf_netdev,
				   "could not move to same namespace as %s: %d\n",
				   ndev->name, ret);
		अन्यथा
			netdev_info(vf_netdev,
				    "VF moved to namespace with: %s\n",
				    ndev->name);
		वापस NOTIFY_DONE;
	पूर्ण

	netdev_info(ndev, "VF registering: %s\n", vf_netdev->name);

	अगर (netvsc_vf_join(vf_netdev, ndev) != 0)
		वापस NOTIFY_DONE;

	dev_hold(vf_netdev);
	rcu_assign_poपूर्णांकer(net_device_ctx->vf_netdev, vf_netdev);

	vf_netdev->wanted_features = ndev->features;
	netdev_update_features(vf_netdev);

	prog = netvsc_xdp_get(netvsc_dev);
	netvsc_vf_setxdp(vf_netdev, prog);

	वापस NOTIFY_OK;
पूर्ण

/* Change the data path when VF UP/DOWN/CHANGE are detected.
 *
 * Typically a UP or DOWN event is followed by a CHANGE event, so
 * net_device_ctx->data_path_is_vf is used to cache the current data path
 * to aव्योम the duplicate call of netvsc_चयन_datapath() and the duplicate
 * message.
 *
 * During hibernation, अगर a VF NIC driver (e.g. mlx5) preserves the network
 * पूर्णांकerface, there is only the CHANGE event and no UP or DOWN event.
 */
अटल पूर्णांक netvsc_vf_changed(काष्ठा net_device *vf_netdev, अचिन्हित दीर्घ event)
अणु
	काष्ठा net_device_context *net_device_ctx;
	काष्ठा netvsc_device *netvsc_dev;
	काष्ठा net_device *ndev;
	bool vf_is_up = false;
	पूर्णांक ret;

	अगर (event != NETDEV_GOING_DOWN)
		vf_is_up = netअगर_running(vf_netdev);

	ndev = get_netvsc_byref(vf_netdev);
	अगर (!ndev)
		वापस NOTIFY_DONE;

	net_device_ctx = netdev_priv(ndev);
	netvsc_dev = rtnl_dereference(net_device_ctx->nvdev);
	अगर (!netvsc_dev)
		वापस NOTIFY_DONE;

	अगर (net_device_ctx->data_path_is_vf == vf_is_up)
		वापस NOTIFY_OK;

	ret = netvsc_चयन_datapath(ndev, vf_is_up);

	अगर (ret) अणु
		netdev_err(ndev,
			   "Data path failed to switch %s VF: %s, err: %d\n",
			   vf_is_up ? "to" : "from", vf_netdev->name, ret);
		वापस NOTIFY_DONE;
	पूर्ण अन्यथा अणु
		netdev_info(ndev, "Data path switched %s VF: %s\n",
			    vf_is_up ? "to" : "from", vf_netdev->name);
	पूर्ण

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक netvsc_unरेजिस्टर_vf(काष्ठा net_device *vf_netdev)
अणु
	काष्ठा net_device *ndev;
	काष्ठा net_device_context *net_device_ctx;

	ndev = get_netvsc_byref(vf_netdev);
	अगर (!ndev)
		वापस NOTIFY_DONE;

	net_device_ctx = netdev_priv(ndev);
	cancel_delayed_work_sync(&net_device_ctx->vf_takeover);

	netdev_info(ndev, "VF unregistering: %s\n", vf_netdev->name);

	netvsc_vf_setxdp(vf_netdev, शून्य);

	netdev_rx_handler_unरेजिस्टर(vf_netdev);
	netdev_upper_dev_unlink(vf_netdev, ndev);
	RCU_INIT_POINTER(net_device_ctx->vf_netdev, शून्य);
	dev_put(vf_netdev);

	वापस NOTIFY_OK;
पूर्ण

अटल पूर्णांक netvsc_probe(काष्ठा hv_device *dev,
			स्थिर काष्ठा hv_vmbus_device_id *dev_id)
अणु
	काष्ठा net_device *net = शून्य;
	काष्ठा net_device_context *net_device_ctx;
	काष्ठा netvsc_device_info *device_info = शून्य;
	काष्ठा netvsc_device *nvdev;
	पूर्णांक ret = -ENOMEM;

	net = alloc_etherdev_mq(माप(काष्ठा net_device_context),
				VRSS_CHANNEL_MAX);
	अगर (!net)
		जाओ no_net;

	netअगर_carrier_off(net);

	netvsc_init_settings(net);

	net_device_ctx = netdev_priv(net);
	net_device_ctx->device_ctx = dev;
	net_device_ctx->msg_enable = netअगर_msg_init(debug, शेष_msg);
	अगर (netअगर_msg_probe(net_device_ctx))
		netdev_dbg(net, "netvsc msg_enable: %d\n",
			   net_device_ctx->msg_enable);

	hv_set_drvdata(dev, net);

	INIT_DELAYED_WORK(&net_device_ctx->dwork, netvsc_link_change);

	spin_lock_init(&net_device_ctx->lock);
	INIT_LIST_HEAD(&net_device_ctx->reconfig_events);
	INIT_DELAYED_WORK(&net_device_ctx->vf_takeover, netvsc_vf_setup);

	net_device_ctx->vf_stats
		= netdev_alloc_pcpu_stats(काष्ठा netvsc_vf_pcpu_stats);
	अगर (!net_device_ctx->vf_stats)
		जाओ no_stats;

	net->netdev_ops = &device_ops;
	net->ethtool_ops = &ethtool_ops;
	SET_NETDEV_DEV(net, &dev->device);

	/* We always need headroom क्रम rndis header */
	net->needed_headroom = RNDIS_AND_PPI_SIZE;

	/* Initialize the number of queues to be 1, we may change it अगर more
	 * channels are offered later.
	 */
	netअगर_set_real_num_tx_queues(net, 1);
	netअगर_set_real_num_rx_queues(net, 1);

	/* Notअगरy the netvsc driver of the new device */
	device_info = netvsc_devinfo_get(शून्य);

	अगर (!device_info) अणु
		ret = -ENOMEM;
		जाओ devinfo_failed;
	पूर्ण

	nvdev = rndis_filter_device_add(dev, device_info);
	अगर (IS_ERR(nvdev)) अणु
		ret = PTR_ERR(nvdev);
		netdev_err(net, "unable to add netvsc device (ret %d)\n", ret);
		जाओ rndis_failed;
	पूर्ण

	स_नकल(net->dev_addr, device_info->mac_adr, ETH_ALEN);

	/* We must get rtnl lock beक्रमe scheduling nvdev->subchan_work,
	 * otherwise netvsc_subchan_work() can get rtnl lock first and रुको
	 * all subchannels to show up, but that may not happen because
	 * netvsc_probe() can't get rtnl lock and as a result vmbus_onoffer()
	 * -> ... -> device_add() -> ... -> __device_attach() can't get
	 * the device lock, so all the subchannels can't be processed --
	 * finally netvsc_subchan_work() hangs क्रमever.
	 */
	rtnl_lock();

	अगर (nvdev->num_chn > 1)
		schedule_work(&nvdev->subchan_work);

	/* hw_features computed in rndis_netdev_set_hwcaps() */
	net->features = net->hw_features |
		NETIF_F_HIGHDMA | NETIF_F_HW_VLAN_CTAG_TX |
		NETIF_F_HW_VLAN_CTAG_RX;
	net->vlan_features = net->features;

	netdev_lockdep_set_classes(net);

	/* MTU range: 68 - 1500 or 65521 */
	net->min_mtu = NETVSC_MTU_MIN;
	अगर (nvdev->nvsp_version >= NVSP_PROTOCOL_VERSION_2)
		net->max_mtu = NETVSC_MTU - ETH_HLEN;
	अन्यथा
		net->max_mtu = ETH_DATA_LEN;

	nvdev->tx_disable = false;

	ret = रेजिस्टर_netdevice(net);
	अगर (ret != 0) अणु
		pr_err("Unable to register netdev.\n");
		जाओ रेजिस्टर_failed;
	पूर्ण

	list_add(&net_device_ctx->list, &netvsc_dev_list);
	rtnl_unlock();

	netvsc_devinfo_put(device_info);
	वापस 0;

रेजिस्टर_failed:
	rtnl_unlock();
	rndis_filter_device_हटाओ(dev, nvdev);
rndis_failed:
	netvsc_devinfo_put(device_info);
devinfo_failed:
	मुक्त_percpu(net_device_ctx->vf_stats);
no_stats:
	hv_set_drvdata(dev, शून्य);
	मुक्त_netdev(net);
no_net:
	वापस ret;
पूर्ण

अटल पूर्णांक netvsc_हटाओ(काष्ठा hv_device *dev)
अणु
	काष्ठा net_device_context *ndev_ctx;
	काष्ठा net_device *vf_netdev, *net;
	काष्ठा netvsc_device *nvdev;

	net = hv_get_drvdata(dev);
	अगर (net == शून्य) अणु
		dev_err(&dev->device, "No net device to remove\n");
		वापस 0;
	पूर्ण

	ndev_ctx = netdev_priv(net);

	cancel_delayed_work_sync(&ndev_ctx->dwork);

	rtnl_lock();
	nvdev = rtnl_dereference(ndev_ctx->nvdev);
	अगर (nvdev) अणु
		cancel_work_sync(&nvdev->subchan_work);
		netvsc_xdp_set(net, शून्य, शून्य, nvdev);
	पूर्ण

	/*
	 * Call to the vsc driver to let it know that the device is being
	 * हटाओd. Also blocks mtu and channel changes.
	 */
	vf_netdev = rtnl_dereference(ndev_ctx->vf_netdev);
	अगर (vf_netdev)
		netvsc_unरेजिस्टर_vf(vf_netdev);

	अगर (nvdev)
		rndis_filter_device_हटाओ(dev, nvdev);

	unरेजिस्टर_netdevice(net);
	list_del(&ndev_ctx->list);

	rtnl_unlock();

	hv_set_drvdata(dev, शून्य);

	मुक्त_percpu(ndev_ctx->vf_stats);
	मुक्त_netdev(net);
	वापस 0;
पूर्ण

अटल पूर्णांक netvsc_suspend(काष्ठा hv_device *dev)
अणु
	काष्ठा net_device_context *ndev_ctx;
	काष्ठा netvsc_device *nvdev;
	काष्ठा net_device *net;
	पूर्णांक ret;

	net = hv_get_drvdata(dev);

	ndev_ctx = netdev_priv(net);
	cancel_delayed_work_sync(&ndev_ctx->dwork);

	rtnl_lock();

	nvdev = rtnl_dereference(ndev_ctx->nvdev);
	अगर (nvdev == शून्य) अणु
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	/* Save the current config info */
	ndev_ctx->saved_netvsc_dev_info = netvsc_devinfo_get(nvdev);

	ret = netvsc_detach(net, nvdev);
out:
	rtnl_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक netvsc_resume(काष्ठा hv_device *dev)
अणु
	काष्ठा net_device *net = hv_get_drvdata(dev);
	काष्ठा net_device_context *net_device_ctx;
	काष्ठा netvsc_device_info *device_info;
	पूर्णांक ret;

	rtnl_lock();

	net_device_ctx = netdev_priv(net);

	/* Reset the data path to the netvsc NIC beक्रमe re-खोलोing the vmbus
	 * channel. Later netvsc_netdev_event() will चयन the data path to
	 * the VF upon the UP or CHANGE event.
	 */
	net_device_ctx->data_path_is_vf = false;
	device_info = net_device_ctx->saved_netvsc_dev_info;

	ret = netvsc_attach(net, device_info);

	netvsc_devinfo_put(device_info);
	net_device_ctx->saved_netvsc_dev_info = शून्य;

	rtnl_unlock();

	वापस ret;
पूर्ण
अटल स्थिर काष्ठा hv_vmbus_device_id id_table[] = अणु
	/* Network guid */
	अणु HV_NIC_GUID, पूर्ण,
	अणु पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(vmbus, id_table);

/* The one and only one */
अटल काष्ठा  hv_driver netvsc_drv = अणु
	.name = KBUILD_MODNAME,
	.id_table = id_table,
	.probe = netvsc_probe,
	.हटाओ = netvsc_हटाओ,
	.suspend = netvsc_suspend,
	.resume = netvsc_resume,
	.driver = अणु
		.probe_type = PROBE_FORCE_SYNCHRONOUS,
	पूर्ण,
पूर्ण;

/*
 * On Hyper-V, every VF पूर्णांकerface is matched with a corresponding
 * synthetic पूर्णांकerface. The synthetic पूर्णांकerface is presented first
 * to the guest. When the corresponding VF instance is रेजिस्टरed,
 * we will take care of चयनing the data path.
 */
अटल पूर्णांक netvsc_netdev_event(काष्ठा notअगरier_block *this,
			       अचिन्हित दीर्घ event, व्योम *ptr)
अणु
	काष्ठा net_device *event_dev = netdev_notअगरier_info_to_dev(ptr);

	/* Skip our own events */
	अगर (event_dev->netdev_ops == &device_ops)
		वापस NOTIFY_DONE;

	/* Aव्योम non-Ethernet type devices */
	अगर (event_dev->type != ARPHRD_ETHER)
		वापस NOTIFY_DONE;

	/* Aव्योम Vlan dev with same MAC रेजिस्टरing as VF */
	अगर (is_vlan_dev(event_dev))
		वापस NOTIFY_DONE;

	/* Aव्योम Bonding master dev with same MAC रेजिस्टरing as VF */
	अगर ((event_dev->priv_flags & IFF_BONDING) &&
	    (event_dev->flags & IFF_MASTER))
		वापस NOTIFY_DONE;

	चयन (event) अणु
	हाल NETDEV_REGISTER:
		वापस netvsc_रेजिस्टर_vf(event_dev);
	हाल NETDEV_UNREGISTER:
		वापस netvsc_unरेजिस्टर_vf(event_dev);
	हाल NETDEV_UP:
	हाल NETDEV_DOWN:
	हाल NETDEV_CHANGE:
	हाल NETDEV_GOING_DOWN:
		वापस netvsc_vf_changed(event_dev, event);
	शेष:
		वापस NOTIFY_DONE;
	पूर्ण
पूर्ण

अटल काष्ठा notअगरier_block netvsc_netdev_notअगरier = अणु
	.notअगरier_call = netvsc_netdev_event,
पूर्ण;

अटल व्योम __निकास netvsc_drv_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&netvsc_netdev_notअगरier);
	vmbus_driver_unरेजिस्टर(&netvsc_drv);
पूर्ण

अटल पूर्णांक __init netvsc_drv_init(व्योम)
अणु
	पूर्णांक ret;

	अगर (ring_size < RING_SIZE_MIN) अणु
		ring_size = RING_SIZE_MIN;
		pr_info("Increased ring_size to %u (min allowed)\n",
			ring_size);
	पूर्ण
	netvsc_ring_bytes = ring_size * PAGE_SIZE;

	ret = vmbus_driver_रेजिस्टर(&netvsc_drv);
	अगर (ret)
		वापस ret;

	रेजिस्टर_netdevice_notअगरier(&netvsc_netdev_notअगरier);
	वापस 0;
पूर्ण

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Microsoft Hyper-V network driver");

module_init(netvsc_drv_init);
module_निकास(netvsc_drv_निकास);
