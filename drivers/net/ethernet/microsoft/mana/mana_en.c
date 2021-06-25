<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/* Copyright (c) 2021, Microsoft Corporation. */

#समावेश <linux/inetdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/mm.h>

#समावेश <net/checksum.h>
#समावेश <net/ip6_checksum.h>

#समावेश "mana.h"

/* Microsoft Azure Network Adapter (MANA) functions */

अटल पूर्णांक mana_खोलो(काष्ठा net_device *ndev)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	पूर्णांक err;

	err = mana_alloc_queues(ndev);
	अगर (err)
		वापस err;

	apc->port_is_up = true;

	/* Ensure port state updated beक्रमe txq state */
	smp_wmb();

	netअगर_carrier_on(ndev);
	netअगर_tx_wake_all_queues(ndev);

	वापस 0;
पूर्ण

अटल पूर्णांक mana_बंद(काष्ठा net_device *ndev)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);

	अगर (!apc->port_is_up)
		वापस 0;

	वापस mana_detach(ndev, true);
पूर्ण

अटल bool mana_can_tx(काष्ठा gdma_queue *wq)
अणु
	वापस mana_gd_wq_avail_space(wq) >= MAX_TX_WQE_SIZE;
पूर्ण

अटल अचिन्हित पूर्णांक mana_checksum_info(काष्ठा sk_buff *skb)
अणु
	अगर (skb->protocol == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *ip = ip_hdr(skb);

		अगर (ip->protocol == IPPROTO_TCP)
			वापस IPPROTO_TCP;

		अगर (ip->protocol == IPPROTO_UDP)
			वापस IPPROTO_UDP;
	पूर्ण अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6)) अणु
		काष्ठा ipv6hdr *ip6 = ipv6_hdr(skb);

		अगर (ip6->nexthdr == IPPROTO_TCP)
			वापस IPPROTO_TCP;

		अगर (ip6->nexthdr == IPPROTO_UDP)
			वापस IPPROTO_UDP;
	पूर्ण

	/* No csum offloading */
	वापस 0;
पूर्ण

अटल पूर्णांक mana_map_skb(काष्ठा sk_buff *skb, काष्ठा mana_port_context *apc,
			काष्ठा mana_tx_package *tp)
अणु
	काष्ठा mana_skb_head *ash = (काष्ठा mana_skb_head *)skb->head;
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;
	काष्ठा gdma_context *gc;
	काष्ठा device *dev;
	skb_frag_t *frag;
	dma_addr_t da;
	पूर्णांक i;

	gc = gd->gdma_context;
	dev = gc->dev;
	da = dma_map_single(dev, skb->data, skb_headlen(skb), DMA_TO_DEVICE);

	अगर (dma_mapping_error(dev, da))
		वापस -ENOMEM;

	ash->dma_handle[0] = da;
	ash->size[0] = skb_headlen(skb);

	tp->wqe_req.sgl[0].address = ash->dma_handle[0];
	tp->wqe_req.sgl[0].mem_key = gd->gpa_mkey;
	tp->wqe_req.sgl[0].size = ash->size[0];

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		da = skb_frag_dma_map(dev, frag, 0, skb_frag_size(frag),
				      DMA_TO_DEVICE);

		अगर (dma_mapping_error(dev, da))
			जाओ frag_err;

		ash->dma_handle[i + 1] = da;
		ash->size[i + 1] = skb_frag_size(frag);

		tp->wqe_req.sgl[i + 1].address = ash->dma_handle[i + 1];
		tp->wqe_req.sgl[i + 1].mem_key = gd->gpa_mkey;
		tp->wqe_req.sgl[i + 1].size = ash->size[i + 1];
	पूर्ण

	वापस 0;

frag_err:
	क्रम (i = i - 1; i >= 0; i--)
		dma_unmap_page(dev, ash->dma_handle[i + 1], ash->size[i + 1],
			       DMA_TO_DEVICE);

	dma_unmap_single(dev, ash->dma_handle[0], ash->size[0], DMA_TO_DEVICE);

	वापस -ENOMEM;
पूर्ण

अटल पूर्णांक mana_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	क्रमागत mana_tx_pkt_क्रमmat pkt_fmt = MANA_SHORT_PKT_FMT;
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	u16 txq_idx = skb_get_queue_mapping(skb);
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;
	bool ipv4 = false, ipv6 = false;
	काष्ठा mana_tx_package pkg = अणुपूर्ण;
	काष्ठा netdev_queue *net_txq;
	काष्ठा mana_stats *tx_stats;
	काष्ठा gdma_queue *gdma_sq;
	अचिन्हित पूर्णांक csum_type;
	काष्ठा mana_txq *txq;
	काष्ठा mana_cq *cq;
	पूर्णांक err, len;

	अगर (unlikely(!apc->port_is_up))
		जाओ tx_drop;

	अगर (skb_cow_head(skb, MANA_HEADROOM))
		जाओ tx_drop_count;

	txq = &apc->tx_qp[txq_idx].txq;
	gdma_sq = txq->gdma_sq;
	cq = &apc->tx_qp[txq_idx].tx_cq;

	pkg.tx_oob.s_oob.vcq_num = cq->gdma_id;
	pkg.tx_oob.s_oob.vsq_frame = txq->vsq_frame;

	अगर (txq->vp_offset > MANA_SHORT_VPORT_OFFSET_MAX) अणु
		pkg.tx_oob.l_oob.दीर्घ_vp_offset = txq->vp_offset;
		pkt_fmt = MANA_LONG_PKT_FMT;
	पूर्ण अन्यथा अणु
		pkg.tx_oob.s_oob.लघु_vp_offset = txq->vp_offset;
	पूर्ण

	pkg.tx_oob.s_oob.pkt_fmt = pkt_fmt;

	अगर (pkt_fmt == MANA_SHORT_PKT_FMT)
		pkg.wqe_req.अंतरभूत_oob_size = माप(काष्ठा mana_tx_लघु_oob);
	अन्यथा
		pkg.wqe_req.अंतरभूत_oob_size = माप(काष्ठा mana_tx_oob);

	pkg.wqe_req.अंतरभूत_oob_data = &pkg.tx_oob;
	pkg.wqe_req.flags = 0;
	pkg.wqe_req.client_data_unit = 0;

	pkg.wqe_req.num_sge = 1 + skb_shinfo(skb)->nr_frags;
	WARN_ON_ONCE(pkg.wqe_req.num_sge > 30);

	अगर (pkg.wqe_req.num_sge <= ARRAY_SIZE(pkg.sgl_array)) अणु
		pkg.wqe_req.sgl = pkg.sgl_array;
	पूर्ण अन्यथा अणु
		pkg.sgl_ptr = kदो_स्मृति_array(pkg.wqe_req.num_sge,
					    माप(काष्ठा gdma_sge),
					    GFP_ATOMIC);
		अगर (!pkg.sgl_ptr)
			जाओ tx_drop_count;

		pkg.wqe_req.sgl = pkg.sgl_ptr;
	पूर्ण

	अगर (skb->protocol == htons(ETH_P_IP))
		ipv4 = true;
	अन्यथा अगर (skb->protocol == htons(ETH_P_IPV6))
		ipv6 = true;

	अगर (skb_is_gso(skb)) अणु
		pkg.tx_oob.s_oob.is_outer_ipv4 = ipv4;
		pkg.tx_oob.s_oob.is_outer_ipv6 = ipv6;

		pkg.tx_oob.s_oob.comp_iphdr_csum = 1;
		pkg.tx_oob.s_oob.comp_tcp_csum = 1;
		pkg.tx_oob.s_oob.trans_off = skb_transport_offset(skb);

		pkg.wqe_req.client_data_unit = skb_shinfo(skb)->gso_size;
		pkg.wqe_req.flags = GDMA_WR_OOB_IN_SGL | GDMA_WR_PAD_BY_SGE0;
		अगर (ipv4) अणु
			ip_hdr(skb)->tot_len = 0;
			ip_hdr(skb)->check = 0;
			tcp_hdr(skb)->check =
				~csum_tcpudp_magic(ip_hdr(skb)->saddr,
						   ip_hdr(skb)->daddr, 0,
						   IPPROTO_TCP, 0);
		पूर्ण अन्यथा अणु
			ipv6_hdr(skb)->payload_len = 0;
			tcp_hdr(skb)->check =
				~csum_ipv6_magic(&ipv6_hdr(skb)->saddr,
						 &ipv6_hdr(skb)->daddr, 0,
						 IPPROTO_TCP, 0);
		पूर्ण
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
		csum_type = mana_checksum_info(skb);

		अगर (csum_type == IPPROTO_TCP) अणु
			pkg.tx_oob.s_oob.is_outer_ipv4 = ipv4;
			pkg.tx_oob.s_oob.is_outer_ipv6 = ipv6;

			pkg.tx_oob.s_oob.comp_tcp_csum = 1;
			pkg.tx_oob.s_oob.trans_off = skb_transport_offset(skb);

		पूर्ण अन्यथा अगर (csum_type == IPPROTO_UDP) अणु
			pkg.tx_oob.s_oob.is_outer_ipv4 = ipv4;
			pkg.tx_oob.s_oob.is_outer_ipv6 = ipv6;

			pkg.tx_oob.s_oob.comp_udp_csum = 1;
		पूर्ण अन्यथा अणु
			/* Can't करो offload of this type of checksum */
			अगर (skb_checksum_help(skb))
				जाओ मुक्त_sgl_ptr;
		पूर्ण
	पूर्ण

	अगर (mana_map_skb(skb, apc, &pkg))
		जाओ मुक्त_sgl_ptr;

	skb_queue_tail(&txq->pending_skbs, skb);

	len = skb->len;
	net_txq = netdev_get_tx_queue(ndev, txq_idx);

	err = mana_gd_post_work_request(gdma_sq, &pkg.wqe_req,
					(काष्ठा gdma_posted_wqe_info *)skb->cb);
	अगर (!mana_can_tx(gdma_sq)) अणु
		netअगर_tx_stop_queue(net_txq);
		apc->eth_stats.stop_queue++;
	पूर्ण

	अगर (err) अणु
		(व्योम)skb_dequeue_tail(&txq->pending_skbs);
		netdev_warn(ndev, "Failed to post TX OOB: %d\n", err);
		err = NETDEV_TX_BUSY;
		जाओ tx_busy;
	पूर्ण

	err = NETDEV_TX_OK;
	atomic_inc(&txq->pending_sends);

	mana_gd_wq_ring_करोorbell(gd->gdma_context, gdma_sq);

	/* skb may be मुक्तd after mana_gd_post_work_request. Do not use it. */
	skb = शून्य;

	tx_stats = &txq->stats;
	u64_stats_update_begin(&tx_stats->syncp);
	tx_stats->packets++;
	tx_stats->bytes += len;
	u64_stats_update_end(&tx_stats->syncp);

tx_busy:
	अगर (netअगर_tx_queue_stopped(net_txq) && mana_can_tx(gdma_sq)) अणु
		netअगर_tx_wake_queue(net_txq);
		apc->eth_stats.wake_queue++;
	पूर्ण

	kमुक्त(pkg.sgl_ptr);
	वापस err;

मुक्त_sgl_ptr:
	kमुक्त(pkg.sgl_ptr);
tx_drop_count:
	ndev->stats.tx_dropped++;
tx_drop:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम mana_get_stats64(काष्ठा net_device *ndev,
			     काष्ठा rtnl_link_stats64 *st)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	अचिन्हित पूर्णांक num_queues = apc->num_queues;
	काष्ठा mana_stats *stats;
	अचिन्हित पूर्णांक start;
	u64 packets, bytes;
	पूर्णांक q;

	अगर (!apc->port_is_up)
		वापस;

	netdev_stats_to_stats64(st, &ndev->stats);

	क्रम (q = 0; q < num_queues; q++) अणु
		stats = &apc->rxqs[q]->stats;

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->packets;
			bytes = stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		st->rx_packets += packets;
		st->rx_bytes += bytes;
	पूर्ण

	क्रम (q = 0; q < num_queues; q++) अणु
		stats = &apc->tx_qp[q].txq.stats;

		करो अणु
			start = u64_stats_fetch_begin_irq(&stats->syncp);
			packets = stats->packets;
			bytes = stats->bytes;
		पूर्ण जबतक (u64_stats_fetch_retry_irq(&stats->syncp, start));

		st->tx_packets += packets;
		st->tx_bytes += bytes;
	पूर्ण
पूर्ण

अटल पूर्णांक mana_get_tx_queue(काष्ठा net_device *ndev, काष्ठा sk_buff *skb,
			     पूर्णांक old_q)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	u32 hash = skb_get_hash(skb);
	काष्ठा sock *sk = skb->sk;
	पूर्णांक txq;

	txq = apc->indir_table[hash & MANA_INसूचीECT_TABLE_MASK];

	अगर (txq != old_q && sk && sk_fullsock(sk) &&
	    rcu_access_poपूर्णांकer(sk->sk_dst_cache))
		sk_tx_queue_set(sk, txq);

	वापस txq;
पूर्ण

अटल u16 mana_select_queue(काष्ठा net_device *ndev, काष्ठा sk_buff *skb,
			     काष्ठा net_device *sb_dev)
अणु
	पूर्णांक txq;

	अगर (ndev->real_num_tx_queues == 1)
		वापस 0;

	txq = sk_tx_queue_get(skb->sk);

	अगर (txq < 0 || skb->ooo_okay || txq >= ndev->real_num_tx_queues) अणु
		अगर (skb_rx_queue_recorded(skb))
			txq = skb_get_rx_queue(skb);
		अन्यथा
			txq = mana_get_tx_queue(ndev, skb, txq);
	पूर्ण

	वापस txq;
पूर्ण

अटल स्थिर काष्ठा net_device_ops mana_devops = अणु
	.nकरो_खोलो		= mana_खोलो,
	.nकरो_stop		= mana_बंद,
	.nकरो_select_queue	= mana_select_queue,
	.nकरो_start_xmit		= mana_start_xmit,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_get_stats64	= mana_get_stats64,
पूर्ण;

अटल व्योम mana_cleanup_port_context(काष्ठा mana_port_context *apc)
अणु
	kमुक्त(apc->rxqs);
	apc->rxqs = शून्य;
पूर्ण

अटल पूर्णांक mana_init_port_context(काष्ठा mana_port_context *apc)
अणु
	apc->rxqs = kसुस्मृति(apc->num_queues, माप(काष्ठा mana_rxq *),
			    GFP_KERNEL);

	वापस !apc->rxqs ? -ENOMEM : 0;
पूर्ण

अटल पूर्णांक mana_send_request(काष्ठा mana_context *ac, व्योम *in_buf,
			     u32 in_len, व्योम *out_buf, u32 out_len)
अणु
	काष्ठा gdma_context *gc = ac->gdma_dev->gdma_context;
	काष्ठा gdma_resp_hdr *resp = out_buf;
	काष्ठा gdma_req_hdr *req = in_buf;
	काष्ठा device *dev = gc->dev;
	अटल atomic_t activity_id;
	पूर्णांक err;

	req->dev_id = gc->mana.dev_id;
	req->activity_id = atomic_inc_वापस(&activity_id);

	err = mana_gd_send_request(gc, in_len, in_buf, out_len,
				   out_buf);
	अगर (err || resp->status) अणु
		dev_err(dev, "Failed to send mana message: %d, 0x%x\n",
			err, resp->status);
		वापस err ? err : -EPROTO;
	पूर्ण

	अगर (req->dev_id.as_uपूर्णांक32 != resp->dev_id.as_uपूर्णांक32 ||
	    req->activity_id != resp->activity_id) अणु
		dev_err(dev, "Unexpected mana message response: %x,%x,%x,%x\n",
			req->dev_id.as_uपूर्णांक32, resp->dev_id.as_uपूर्णांक32,
			req->activity_id, resp->activity_id);
		वापस -EPROTO;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mana_verअगरy_resp_hdr(स्थिर काष्ठा gdma_resp_hdr *resp_hdr,
				स्थिर क्रमागत mana_command_code expected_code,
				स्थिर u32 min_size)
अणु
	अगर (resp_hdr->response.msg_type != expected_code)
		वापस -EPROTO;

	अगर (resp_hdr->response.msg_version < GDMA_MESSAGE_V1)
		वापस -EPROTO;

	अगर (resp_hdr->response.msg_size < min_size)
		वापस -EPROTO;

	वापस 0;
पूर्ण

अटल पूर्णांक mana_query_device_cfg(काष्ठा mana_context *ac, u32 proto_major_ver,
				 u32 proto_minor_ver, u32 proto_micro_ver,
				 u16 *max_num_vports)
अणु
	काष्ठा gdma_context *gc = ac->gdma_dev->gdma_context;
	काष्ठा mana_query_device_cfg_resp resp = अणुपूर्ण;
	काष्ठा mana_query_device_cfg_req req = अणुपूर्ण;
	काष्ठा device *dev = gc->dev;
	पूर्णांक err = 0;

	mana_gd_init_req_hdr(&req.hdr, MANA_QUERY_DEV_CONFIG,
			     माप(req), माप(resp));
	req.proto_major_ver = proto_major_ver;
	req.proto_minor_ver = proto_minor_ver;
	req.proto_micro_ver = proto_micro_ver;

	err = mana_send_request(ac, &req, माप(req), &resp, माप(resp));
	अगर (err) अणु
		dev_err(dev, "Failed to query config: %d", err);
		वापस err;
	पूर्ण

	err = mana_verअगरy_resp_hdr(&resp.hdr, MANA_QUERY_DEV_CONFIG,
				   माप(resp));
	अगर (err || resp.hdr.status) अणु
		dev_err(dev, "Invalid query result: %d, 0x%x\n", err,
			resp.hdr.status);
		अगर (!err)
			err = -EPROTO;
		वापस err;
	पूर्ण

	*max_num_vports = resp.max_num_vports;

	वापस 0;
पूर्ण

अटल पूर्णांक mana_query_vport_cfg(काष्ठा mana_port_context *apc, u32 vport_index,
				u32 *max_sq, u32 *max_rq, u32 *num_indir_entry)
अणु
	काष्ठा mana_query_vport_cfg_resp resp = अणुपूर्ण;
	काष्ठा mana_query_vport_cfg_req req = अणुपूर्ण;
	पूर्णांक err;

	mana_gd_init_req_hdr(&req.hdr, MANA_QUERY_VPORT_CONFIG,
			     माप(req), माप(resp));

	req.vport_index = vport_index;

	err = mana_send_request(apc->ac, &req, माप(req), &resp,
				माप(resp));
	अगर (err)
		वापस err;

	err = mana_verअगरy_resp_hdr(&resp.hdr, MANA_QUERY_VPORT_CONFIG,
				   माप(resp));
	अगर (err)
		वापस err;

	अगर (resp.hdr.status)
		वापस -EPROTO;

	*max_sq = resp.max_num_sq;
	*max_rq = resp.max_num_rq;
	*num_indir_entry = resp.num_indirection_ent;

	apc->port_handle = resp.vport;
	ether_addr_copy(apc->mac_addr, resp.mac_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक mana_cfg_vport(काष्ठा mana_port_context *apc, u32 protection_करोm_id,
			  u32 करोorbell_pg_id)
अणु
	काष्ठा mana_config_vport_resp resp = अणुपूर्ण;
	काष्ठा mana_config_vport_req req = अणुपूर्ण;
	पूर्णांक err;

	mana_gd_init_req_hdr(&req.hdr, MANA_CONFIG_VPORT_TX,
			     माप(req), माप(resp));
	req.vport = apc->port_handle;
	req.pdid = protection_करोm_id;
	req.करोorbell_pageid = करोorbell_pg_id;

	err = mana_send_request(apc->ac, &req, माप(req), &resp,
				माप(resp));
	अगर (err) अणु
		netdev_err(apc->ndev, "Failed to configure vPort: %d\n", err);
		जाओ out;
	पूर्ण

	err = mana_verअगरy_resp_hdr(&resp.hdr, MANA_CONFIG_VPORT_TX,
				   माप(resp));
	अगर (err || resp.hdr.status) अणु
		netdev_err(apc->ndev, "Failed to configure vPort: %d, 0x%x\n",
			   err, resp.hdr.status);
		अगर (!err)
			err = -EPROTO;

		जाओ out;
	पूर्ण

	apc->tx_लघुक्रमm_allowed = resp.लघु_क्रमm_allowed;
	apc->tx_vp_offset = resp.tx_vport_offset;
out:
	वापस err;
पूर्ण

अटल पूर्णांक mana_cfg_vport_steering(काष्ठा mana_port_context *apc,
				   क्रमागत TRI_STATE rx,
				   bool update_शेष_rxobj, bool update_key,
				   bool update_tab)
अणु
	u16 num_entries = MANA_INसूचीECT_TABLE_SIZE;
	काष्ठा mana_cfg_rx_steer_req *req = शून्य;
	काष्ठा mana_cfg_rx_steer_resp resp = अणुपूर्ण;
	काष्ठा net_device *ndev = apc->ndev;
	mana_handle_t *req_indir_tab;
	u32 req_buf_size;
	पूर्णांक err;

	req_buf_size = माप(*req) + माप(mana_handle_t) * num_entries;
	req = kzalloc(req_buf_size, GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	mana_gd_init_req_hdr(&req->hdr, MANA_CONFIG_VPORT_RX, req_buf_size,
			     माप(resp));

	req->vport = apc->port_handle;
	req->num_indir_entries = num_entries;
	req->indir_tab_offset = माप(*req);
	req->rx_enable = rx;
	req->rss_enable = apc->rss_state;
	req->update_शेष_rxobj = update_शेष_rxobj;
	req->update_hashkey = update_key;
	req->update_indir_tab = update_tab;
	req->शेष_rxobj = apc->शेष_rxobj;

	अगर (update_key)
		स_नकल(&req->hashkey, apc->hashkey, MANA_HASH_KEY_SIZE);

	अगर (update_tab) अणु
		req_indir_tab = (mana_handle_t *)(req + 1);
		स_नकल(req_indir_tab, apc->rxobj_table,
		       req->num_indir_entries * माप(mana_handle_t));
	पूर्ण

	err = mana_send_request(apc->ac, req, req_buf_size, &resp,
				माप(resp));
	अगर (err) अणु
		netdev_err(ndev, "Failed to configure vPort RX: %d\n", err);
		जाओ out;
	पूर्ण

	err = mana_verअगरy_resp_hdr(&resp.hdr, MANA_CONFIG_VPORT_RX,
				   माप(resp));
	अगर (err) अणु
		netdev_err(ndev, "vPort RX configuration failed: %d\n", err);
		जाओ out;
	पूर्ण

	अगर (resp.hdr.status) अणु
		netdev_err(ndev, "vPort RX configuration failed: 0x%x\n",
			   resp.hdr.status);
		err = -EPROTO;
	पूर्ण
out:
	kमुक्त(req);
	वापस err;
पूर्ण

अटल पूर्णांक mana_create_wq_obj(काष्ठा mana_port_context *apc,
			      mana_handle_t vport,
			      u32 wq_type, काष्ठा mana_obj_spec *wq_spec,
			      काष्ठा mana_obj_spec *cq_spec,
			      mana_handle_t *wq_obj)
अणु
	काष्ठा mana_create_wqobj_resp resp = अणुपूर्ण;
	काष्ठा mana_create_wqobj_req req = अणुपूर्ण;
	काष्ठा net_device *ndev = apc->ndev;
	पूर्णांक err;

	mana_gd_init_req_hdr(&req.hdr, MANA_CREATE_WQ_OBJ,
			     माप(req), माप(resp));
	req.vport = vport;
	req.wq_type = wq_type;
	req.wq_gdma_region = wq_spec->gdma_region;
	req.cq_gdma_region = cq_spec->gdma_region;
	req.wq_size = wq_spec->queue_size;
	req.cq_size = cq_spec->queue_size;
	req.cq_moderation_ctx_id = cq_spec->modr_ctx_id;
	req.cq_parent_qid = cq_spec->attached_eq;

	err = mana_send_request(apc->ac, &req, माप(req), &resp,
				माप(resp));
	अगर (err) अणु
		netdev_err(ndev, "Failed to create WQ object: %d\n", err);
		जाओ out;
	पूर्ण

	err = mana_verअगरy_resp_hdr(&resp.hdr, MANA_CREATE_WQ_OBJ,
				   माप(resp));
	अगर (err || resp.hdr.status) अणु
		netdev_err(ndev, "Failed to create WQ object: %d, 0x%x\n", err,
			   resp.hdr.status);
		अगर (!err)
			err = -EPROTO;
		जाओ out;
	पूर्ण

	अगर (resp.wq_obj == INVALID_MANA_HANDLE) अणु
		netdev_err(ndev, "Got an invalid WQ object handle\n");
		err = -EPROTO;
		जाओ out;
	पूर्ण

	*wq_obj = resp.wq_obj;
	wq_spec->queue_index = resp.wq_id;
	cq_spec->queue_index = resp.cq_id;

	वापस 0;
out:
	वापस err;
पूर्ण

अटल व्योम mana_destroy_wq_obj(काष्ठा mana_port_context *apc, u32 wq_type,
				mana_handle_t wq_obj)
अणु
	काष्ठा mana_destroy_wqobj_resp resp = अणुपूर्ण;
	काष्ठा mana_destroy_wqobj_req req = अणुपूर्ण;
	काष्ठा net_device *ndev = apc->ndev;
	पूर्णांक err;

	mana_gd_init_req_hdr(&req.hdr, MANA_DESTROY_WQ_OBJ,
			     माप(req), माप(resp));
	req.wq_type = wq_type;
	req.wq_obj_handle = wq_obj;

	err = mana_send_request(apc->ac, &req, माप(req), &resp,
				माप(resp));
	अगर (err) अणु
		netdev_err(ndev, "Failed to destroy WQ object: %d\n", err);
		वापस;
	पूर्ण

	err = mana_verअगरy_resp_hdr(&resp.hdr, MANA_DESTROY_WQ_OBJ,
				   माप(resp));
	अगर (err || resp.hdr.status)
		netdev_err(ndev, "Failed to destroy WQ object: %d, 0x%x\n", err,
			   resp.hdr.status);
पूर्ण

अटल व्योम mana_init_cqe_poll_buf(काष्ठा gdma_comp *cqe_poll_buf)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < CQE_POLLING_BUFFER; i++)
		स_रखो(&cqe_poll_buf[i], 0, माप(काष्ठा gdma_comp));
पूर्ण

अटल व्योम mana_destroy_eq(काष्ठा gdma_context *gc,
			    काष्ठा mana_port_context *apc)
अणु
	काष्ठा gdma_queue *eq;
	पूर्णांक i;

	अगर (!apc->eqs)
		वापस;

	क्रम (i = 0; i < apc->num_queues; i++) अणु
		eq = apc->eqs[i].eq;
		अगर (!eq)
			जारी;

		mana_gd_destroy_queue(gc, eq);
	पूर्ण

	kमुक्त(apc->eqs);
	apc->eqs = शून्य;
पूर्ण

अटल पूर्णांक mana_create_eq(काष्ठा mana_port_context *apc)
अणु
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;
	काष्ठा gdma_queue_spec spec = अणुपूर्ण;
	पूर्णांक err;
	पूर्णांक i;

	apc->eqs = kसुस्मृति(apc->num_queues, माप(काष्ठा mana_eq),
			   GFP_KERNEL);
	अगर (!apc->eqs)
		वापस -ENOMEM;

	spec.type = GDMA_EQ;
	spec.monitor_avl_buf = false;
	spec.queue_size = EQ_SIZE;
	spec.eq.callback = शून्य;
	spec.eq.context = apc->eqs;
	spec.eq.log2_throttle_limit = LOG2_EQ_THROTTLE;
	spec.eq.ndev = apc->ndev;

	क्रम (i = 0; i < apc->num_queues; i++) अणु
		mana_init_cqe_poll_buf(apc->eqs[i].cqe_poll);

		err = mana_gd_create_mana_eq(gd, &spec, &apc->eqs[i].eq);
		अगर (err)
			जाओ out;
	पूर्ण

	वापस 0;
out:
	mana_destroy_eq(gd->gdma_context, apc);
	वापस err;
पूर्ण

अटल पूर्णांक mana_move_wq_tail(काष्ठा gdma_queue *wq, u32 num_units)
अणु
	u32 used_space_old;
	u32 used_space_new;

	used_space_old = wq->head - wq->tail;
	used_space_new = wq->head - (wq->tail + num_units);

	अगर (WARN_ON_ONCE(used_space_new > used_space_old))
		वापस -दुस्फल;

	wq->tail += num_units;
	वापस 0;
पूर्ण

अटल व्योम mana_unmap_skb(काष्ठा sk_buff *skb, काष्ठा mana_port_context *apc)
अणु
	काष्ठा mana_skb_head *ash = (काष्ठा mana_skb_head *)skb->head;
	काष्ठा gdma_context *gc = apc->ac->gdma_dev->gdma_context;
	काष्ठा device *dev = gc->dev;
	पूर्णांक i;

	dma_unmap_single(dev, ash->dma_handle[0], ash->size[0], DMA_TO_DEVICE);

	क्रम (i = 1; i < skb_shinfo(skb)->nr_frags + 1; i++)
		dma_unmap_page(dev, ash->dma_handle[i], ash->size[i],
			       DMA_TO_DEVICE);
पूर्ण

अटल व्योम mana_poll_tx_cq(काष्ठा mana_cq *cq)
अणु
	काष्ठा gdma_queue *gdma_eq = cq->gdma_cq->cq.parent;
	काष्ठा gdma_comp *completions = cq->gdma_comp_buf;
	काष्ठा gdma_posted_wqe_info *wqe_info;
	अचिन्हित पूर्णांक pkt_transmitted = 0;
	अचिन्हित पूर्णांक wqe_unit_cnt = 0;
	काष्ठा mana_txq *txq = cq->txq;
	काष्ठा mana_port_context *apc;
	काष्ठा netdev_queue *net_txq;
	काष्ठा gdma_queue *gdma_wq;
	अचिन्हित पूर्णांक avail_space;
	काष्ठा net_device *ndev;
	काष्ठा sk_buff *skb;
	bool txq_stopped;
	पूर्णांक comp_पढ़ो;
	पूर्णांक i;

	ndev = txq->ndev;
	apc = netdev_priv(ndev);

	comp_पढ़ो = mana_gd_poll_cq(cq->gdma_cq, completions,
				    CQE_POLLING_BUFFER);

	क्रम (i = 0; i < comp_पढ़ो; i++) अणु
		काष्ठा mana_tx_comp_oob *cqe_oob;

		अगर (WARN_ON_ONCE(!completions[i].is_sq))
			वापस;

		cqe_oob = (काष्ठा mana_tx_comp_oob *)completions[i].cqe_data;
		अगर (WARN_ON_ONCE(cqe_oob->cqe_hdr.client_type !=
				 MANA_CQE_COMPLETION))
			वापस;

		चयन (cqe_oob->cqe_hdr.cqe_type) अणु
		हाल CQE_TX_OKAY:
			अवरोध;

		हाल CQE_TX_SA_DROP:
		हाल CQE_TX_MTU_DROP:
		हाल CQE_TX_INVALID_OOB:
		हाल CQE_TX_INVALID_ETH_TYPE:
		हाल CQE_TX_HDR_PROCESSING_ERROR:
		हाल CQE_TX_VF_DISABLED:
		हाल CQE_TX_VPORT_IDX_OUT_OF_RANGE:
		हाल CQE_TX_VPORT_DISABLED:
		हाल CQE_TX_VLAN_TAGGING_VIOLATION:
			WARN_ONCE(1, "TX: CQE error %d: ignored.\n",
				  cqe_oob->cqe_hdr.cqe_type);
			अवरोध;

		शेष:
			/* If the CQE type is unexpected, log an error, निश्चित,
			 * and go through the error path.
			 */
			WARN_ONCE(1, "TX: Unexpected CQE type %d: HW BUG?\n",
				  cqe_oob->cqe_hdr.cqe_type);
			वापस;
		पूर्ण

		अगर (WARN_ON_ONCE(txq->gdma_txq_id != completions[i].wq_num))
			वापस;

		skb = skb_dequeue(&txq->pending_skbs);
		अगर (WARN_ON_ONCE(!skb))
			वापस;

		wqe_info = (काष्ठा gdma_posted_wqe_info *)skb->cb;
		wqe_unit_cnt += wqe_info->wqe_size_in_bu;

		mana_unmap_skb(skb, apc);

		napi_consume_skb(skb, gdma_eq->eq.budget);

		pkt_transmitted++;
	पूर्ण

	अगर (WARN_ON_ONCE(wqe_unit_cnt == 0))
		वापस;

	mana_move_wq_tail(txq->gdma_sq, wqe_unit_cnt);

	gdma_wq = txq->gdma_sq;
	avail_space = mana_gd_wq_avail_space(gdma_wq);

	/* Ensure tail updated beक्रमe checking q stop */
	smp_mb();

	net_txq = txq->net_txq;
	txq_stopped = netअगर_tx_queue_stopped(net_txq);

	/* Ensure checking txq_stopped beक्रमe apc->port_is_up. */
	smp_rmb();

	अगर (txq_stopped && apc->port_is_up && avail_space >= MAX_TX_WQE_SIZE) अणु
		netअगर_tx_wake_queue(net_txq);
		apc->eth_stats.wake_queue++;
	पूर्ण

	अगर (atomic_sub_वापस(pkt_transmitted, &txq->pending_sends) < 0)
		WARN_ON_ONCE(1);
पूर्ण

अटल व्योम mana_post_pkt_rxq(काष्ठा mana_rxq *rxq)
अणु
	काष्ठा mana_recv_buf_oob *recv_buf_oob;
	u32 curr_index;
	पूर्णांक err;

	curr_index = rxq->buf_index++;
	अगर (rxq->buf_index == rxq->num_rx_buf)
		rxq->buf_index = 0;

	recv_buf_oob = &rxq->rx_oobs[curr_index];

	err = mana_gd_post_and_ring(rxq->gdma_rq, &recv_buf_oob->wqe_req,
				    &recv_buf_oob->wqe_inf);
	अगर (WARN_ON_ONCE(err))
		वापस;

	WARN_ON_ONCE(recv_buf_oob->wqe_inf.wqe_size_in_bu != 1);
पूर्ण

अटल व्योम mana_rx_skb(व्योम *buf_va, काष्ठा mana_rxcomp_oob *cqe,
			काष्ठा mana_rxq *rxq)
अणु
	काष्ठा mana_stats *rx_stats = &rxq->stats;
	काष्ठा net_device *ndev = rxq->ndev;
	uपूर्णांक pkt_len = cqe->ppi[0].pkt_len;
	काष्ठा mana_port_context *apc;
	u16 rxq_idx = rxq->rxq_idx;
	काष्ठा napi_काष्ठा *napi;
	काष्ठा gdma_queue *eq;
	काष्ठा sk_buff *skb;
	u32 hash_value;

	apc = netdev_priv(ndev);
	eq = apc->eqs[rxq_idx].eq;
	eq->eq.work_करोne++;
	napi = &eq->eq.napi;

	अगर (!buf_va) अणु
		++ndev->stats.rx_dropped;
		वापस;
	पूर्ण

	skb = build_skb(buf_va, PAGE_SIZE);

	अगर (!skb) अणु
		मुक्त_page((अचिन्हित दीर्घ)buf_va);
		++ndev->stats.rx_dropped;
		वापस;
	पूर्ण

	skb_put(skb, pkt_len);
	skb->dev = napi->dev;

	skb->protocol = eth_type_trans(skb, ndev);
	skb_checksum_none_निश्चित(skb);
	skb_record_rx_queue(skb, rxq_idx);

	अगर ((ndev->features & NETIF_F_RXCSUM) && cqe->rx_iphdr_csum_succeed) अणु
		अगर (cqe->rx_tcp_csum_succeed || cqe->rx_udp_csum_succeed)
			skb->ip_summed = CHECKSUM_UNNECESSARY;
	पूर्ण

	अगर (cqe->rx_hashtype != 0 && (ndev->features & NETIF_F_RXHASH)) अणु
		hash_value = cqe->ppi[0].pkt_hash;

		अगर (cqe->rx_hashtype & MANA_HASH_L4)
			skb_set_hash(skb, hash_value, PKT_HASH_TYPE_L4);
		अन्यथा
			skb_set_hash(skb, hash_value, PKT_HASH_TYPE_L3);
	पूर्ण

	napi_gro_receive(napi, skb);

	u64_stats_update_begin(&rx_stats->syncp);
	rx_stats->packets++;
	rx_stats->bytes += pkt_len;
	u64_stats_update_end(&rx_stats->syncp);
पूर्ण

अटल व्योम mana_process_rx_cqe(काष्ठा mana_rxq *rxq, काष्ठा mana_cq *cq,
				काष्ठा gdma_comp *cqe)
अणु
	काष्ठा mana_rxcomp_oob *oob = (काष्ठा mana_rxcomp_oob *)cqe->cqe_data;
	काष्ठा gdma_context *gc = rxq->gdma_rq->gdma_dev->gdma_context;
	काष्ठा net_device *ndev = rxq->ndev;
	काष्ठा mana_recv_buf_oob *rxbuf_oob;
	काष्ठा device *dev = gc->dev;
	व्योम *new_buf, *old_buf;
	काष्ठा page *new_page;
	u32 curr, pktlen;
	dma_addr_t da;

	चयन (oob->cqe_hdr.cqe_type) अणु
	हाल CQE_RX_OKAY:
		अवरोध;

	हाल CQE_RX_TRUNCATED:
		netdev_err(ndev, "Dropped a truncated packet\n");
		वापस;

	हाल CQE_RX_COALESCED_4:
		netdev_err(ndev, "RX coalescing is unsupported\n");
		वापस;

	हाल CQE_RX_OBJECT_FENCE:
		netdev_err(ndev, "RX Fencing is unsupported\n");
		वापस;

	शेष:
		netdev_err(ndev, "Unknown RX CQE type = %d\n",
			   oob->cqe_hdr.cqe_type);
		वापस;
	पूर्ण

	अगर (oob->cqe_hdr.cqe_type != CQE_RX_OKAY)
		वापस;

	pktlen = oob->ppi[0].pkt_len;

	अगर (pktlen == 0) अणु
		/* data packets should never have packetlength of zero */
		netdev_err(ndev, "RX pkt len=0, rq=%u, cq=%u, rxobj=0x%llx\n",
			   rxq->gdma_id, cq->gdma_id, rxq->rxobj);
		वापस;
	पूर्ण

	curr = rxq->buf_index;
	rxbuf_oob = &rxq->rx_oobs[curr];
	WARN_ON_ONCE(rxbuf_oob->wqe_inf.wqe_size_in_bu != 1);

	new_page = alloc_page(GFP_ATOMIC);

	अगर (new_page) अणु
		da = dma_map_page(dev, new_page, 0, rxq->datasize,
				  DMA_FROM_DEVICE);

		अगर (dma_mapping_error(dev, da)) अणु
			__मुक्त_page(new_page);
			new_page = शून्य;
		पूर्ण
	पूर्ण

	new_buf = new_page ? page_to_virt(new_page) : शून्य;

	अगर (new_buf) अणु
		dma_unmap_page(dev, rxbuf_oob->buf_dma_addr, rxq->datasize,
			       DMA_FROM_DEVICE);

		old_buf = rxbuf_oob->buf_va;

		/* refresh the rxbuf_oob with the new page */
		rxbuf_oob->buf_va = new_buf;
		rxbuf_oob->buf_dma_addr = da;
		rxbuf_oob->sgl[0].address = rxbuf_oob->buf_dma_addr;
	पूर्ण अन्यथा अणु
		old_buf = शून्य; /* drop the packet अगर no memory */
	पूर्ण

	mana_rx_skb(old_buf, oob, rxq);

	mana_move_wq_tail(rxq->gdma_rq, rxbuf_oob->wqe_inf.wqe_size_in_bu);

	mana_post_pkt_rxq(rxq);
पूर्ण

अटल व्योम mana_poll_rx_cq(काष्ठा mana_cq *cq)
अणु
	काष्ठा gdma_comp *comp = cq->gdma_comp_buf;
	पूर्णांक comp_पढ़ो, i;

	comp_पढ़ो = mana_gd_poll_cq(cq->gdma_cq, comp, CQE_POLLING_BUFFER);
	WARN_ON_ONCE(comp_पढ़ो > CQE_POLLING_BUFFER);

	क्रम (i = 0; i < comp_पढ़ो; i++) अणु
		अगर (WARN_ON_ONCE(comp[i].is_sq))
			वापस;

		/* verअगरy recv cqe references the right rxq */
		अगर (WARN_ON_ONCE(comp[i].wq_num != cq->rxq->gdma_id))
			वापस;

		mana_process_rx_cqe(cq->rxq, cq, &comp[i]);
	पूर्ण
पूर्ण

अटल व्योम mana_cq_handler(व्योम *context, काष्ठा gdma_queue *gdma_queue)
अणु
	काष्ठा mana_cq *cq = context;

	WARN_ON_ONCE(cq->gdma_cq != gdma_queue);

	अगर (cq->type == MANA_CQ_TYPE_RX)
		mana_poll_rx_cq(cq);
	अन्यथा
		mana_poll_tx_cq(cq);

	mana_gd_arm_cq(gdma_queue);
पूर्ण

अटल व्योम mana_deinit_cq(काष्ठा mana_port_context *apc, काष्ठा mana_cq *cq)
अणु
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;

	अगर (!cq->gdma_cq)
		वापस;

	mana_gd_destroy_queue(gd->gdma_context, cq->gdma_cq);
पूर्ण

अटल व्योम mana_deinit_txq(काष्ठा mana_port_context *apc, काष्ठा mana_txq *txq)
अणु
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;

	अगर (!txq->gdma_sq)
		वापस;

	mana_gd_destroy_queue(gd->gdma_context, txq->gdma_sq);
पूर्ण

अटल व्योम mana_destroy_txq(काष्ठा mana_port_context *apc)
अणु
	पूर्णांक i;

	अगर (!apc->tx_qp)
		वापस;

	क्रम (i = 0; i < apc->num_queues; i++) अणु
		mana_destroy_wq_obj(apc, GDMA_SQ, apc->tx_qp[i].tx_object);

		mana_deinit_cq(apc, &apc->tx_qp[i].tx_cq);

		mana_deinit_txq(apc, &apc->tx_qp[i].txq);
	पूर्ण

	kमुक्त(apc->tx_qp);
	apc->tx_qp = शून्य;
पूर्ण

अटल पूर्णांक mana_create_txq(काष्ठा mana_port_context *apc,
			   काष्ठा net_device *net)
अणु
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;
	काष्ठा mana_obj_spec wq_spec;
	काष्ठा mana_obj_spec cq_spec;
	काष्ठा gdma_queue_spec spec;
	काष्ठा gdma_context *gc;
	काष्ठा mana_txq *txq;
	काष्ठा mana_cq *cq;
	u32 txq_size;
	u32 cq_size;
	पूर्णांक err;
	पूर्णांक i;

	apc->tx_qp = kसुस्मृति(apc->num_queues, माप(काष्ठा mana_tx_qp),
			     GFP_KERNEL);
	अगर (!apc->tx_qp)
		वापस -ENOMEM;

	/*  The minimum size of the WQE is 32 bytes, hence
	 *  MAX_SEND_BUFFERS_PER_QUEUE represents the maximum number of WQEs
	 *  the SQ can store. This value is then used to size other queues
	 *  to prevent overflow.
	 */
	txq_size = MAX_SEND_BUFFERS_PER_QUEUE * 32;
	BUILD_BUG_ON(!PAGE_ALIGNED(txq_size));

	cq_size = MAX_SEND_BUFFERS_PER_QUEUE * COMP_ENTRY_SIZE;
	cq_size = PAGE_ALIGN(cq_size);

	gc = gd->gdma_context;

	क्रम (i = 0; i < apc->num_queues; i++) अणु
		apc->tx_qp[i].tx_object = INVALID_MANA_HANDLE;

		/* Create SQ */
		txq = &apc->tx_qp[i].txq;

		u64_stats_init(&txq->stats.syncp);
		txq->ndev = net;
		txq->net_txq = netdev_get_tx_queue(net, i);
		txq->vp_offset = apc->tx_vp_offset;
		skb_queue_head_init(&txq->pending_skbs);

		स_रखो(&spec, 0, माप(spec));
		spec.type = GDMA_SQ;
		spec.monitor_avl_buf = true;
		spec.queue_size = txq_size;
		err = mana_gd_create_mana_wq_cq(gd, &spec, &txq->gdma_sq);
		अगर (err)
			जाओ out;

		/* Create SQ's CQ */
		cq = &apc->tx_qp[i].tx_cq;
		cq->gdma_comp_buf = apc->eqs[i].cqe_poll;
		cq->type = MANA_CQ_TYPE_TX;

		cq->txq = txq;

		स_रखो(&spec, 0, माप(spec));
		spec.type = GDMA_CQ;
		spec.monitor_avl_buf = false;
		spec.queue_size = cq_size;
		spec.cq.callback = mana_cq_handler;
		spec.cq.parent_eq = apc->eqs[i].eq;
		spec.cq.context = cq;
		err = mana_gd_create_mana_wq_cq(gd, &spec, &cq->gdma_cq);
		अगर (err)
			जाओ out;

		स_रखो(&wq_spec, 0, माप(wq_spec));
		स_रखो(&cq_spec, 0, माप(cq_spec));

		wq_spec.gdma_region = txq->gdma_sq->mem_info.gdma_region;
		wq_spec.queue_size = txq->gdma_sq->queue_size;

		cq_spec.gdma_region = cq->gdma_cq->mem_info.gdma_region;
		cq_spec.queue_size = cq->gdma_cq->queue_size;
		cq_spec.modr_ctx_id = 0;
		cq_spec.attached_eq = cq->gdma_cq->cq.parent->id;

		err = mana_create_wq_obj(apc, apc->port_handle, GDMA_SQ,
					 &wq_spec, &cq_spec,
					 &apc->tx_qp[i].tx_object);

		अगर (err)
			जाओ out;

		txq->gdma_sq->id = wq_spec.queue_index;
		cq->gdma_cq->id = cq_spec.queue_index;

		txq->gdma_sq->mem_info.gdma_region = GDMA_INVALID_DMA_REGION;
		cq->gdma_cq->mem_info.gdma_region = GDMA_INVALID_DMA_REGION;

		txq->gdma_txq_id = txq->gdma_sq->id;

		cq->gdma_id = cq->gdma_cq->id;

		अगर (WARN_ON(cq->gdma_id >= gc->max_num_cqs))
			वापस -EINVAL;

		gc->cq_table[cq->gdma_id] = cq->gdma_cq;

		mana_gd_arm_cq(cq->gdma_cq);
	पूर्ण

	वापस 0;
out:
	mana_destroy_txq(apc);
	वापस err;
पूर्ण

अटल व्योम mana_napi_sync_क्रम_rx(काष्ठा mana_rxq *rxq)
अणु
	काष्ठा net_device *ndev = rxq->ndev;
	काष्ठा mana_port_context *apc;
	u16 rxq_idx = rxq->rxq_idx;
	काष्ठा napi_काष्ठा *napi;
	काष्ठा gdma_queue *eq;

	apc = netdev_priv(ndev);
	eq = apc->eqs[rxq_idx].eq;
	napi = &eq->eq.napi;

	napi_synchronize(napi);
पूर्ण

अटल व्योम mana_destroy_rxq(काष्ठा mana_port_context *apc,
			     काष्ठा mana_rxq *rxq, bool validate_state)

अणु
	काष्ठा gdma_context *gc = apc->ac->gdma_dev->gdma_context;
	काष्ठा mana_recv_buf_oob *rx_oob;
	काष्ठा device *dev = gc->dev;
	पूर्णांक i;

	अगर (!rxq)
		वापस;

	अगर (validate_state)
		mana_napi_sync_क्रम_rx(rxq);

	mana_destroy_wq_obj(apc, GDMA_RQ, rxq->rxobj);

	mana_deinit_cq(apc, &rxq->rx_cq);

	क्रम (i = 0; i < rxq->num_rx_buf; i++) अणु
		rx_oob = &rxq->rx_oobs[i];

		अगर (!rx_oob->buf_va)
			जारी;

		dma_unmap_page(dev, rx_oob->buf_dma_addr, rxq->datasize,
			       DMA_FROM_DEVICE);

		मुक्त_page((अचिन्हित दीर्घ)rx_oob->buf_va);
		rx_oob->buf_va = शून्य;
	पूर्ण

	अगर (rxq->gdma_rq)
		mana_gd_destroy_queue(gc, rxq->gdma_rq);

	kमुक्त(rxq);
पूर्ण

#घोषणा MANA_WQE_HEADER_SIZE 16
#घोषणा MANA_WQE_SGE_SIZE 16

अटल पूर्णांक mana_alloc_rx_wqe(काष्ठा mana_port_context *apc,
			     काष्ठा mana_rxq *rxq, u32 *rxq_size, u32 *cq_size)
अणु
	काष्ठा gdma_context *gc = apc->ac->gdma_dev->gdma_context;
	काष्ठा mana_recv_buf_oob *rx_oob;
	काष्ठा device *dev = gc->dev;
	काष्ठा page *page;
	dma_addr_t da;
	u32 buf_idx;

	WARN_ON(rxq->datasize == 0 || rxq->datasize > PAGE_SIZE);

	*rxq_size = 0;
	*cq_size = 0;

	क्रम (buf_idx = 0; buf_idx < rxq->num_rx_buf; buf_idx++) अणु
		rx_oob = &rxq->rx_oobs[buf_idx];
		स_रखो(rx_oob, 0, माप(*rx_oob));

		page = alloc_page(GFP_KERNEL);
		अगर (!page)
			वापस -ENOMEM;

		da = dma_map_page(dev, page, 0, rxq->datasize, DMA_FROM_DEVICE);

		अगर (dma_mapping_error(dev, da)) अणु
			__मुक्त_page(page);
			वापस -ENOMEM;
		पूर्ण

		rx_oob->buf_va = page_to_virt(page);
		rx_oob->buf_dma_addr = da;

		rx_oob->num_sge = 1;
		rx_oob->sgl[0].address = rx_oob->buf_dma_addr;
		rx_oob->sgl[0].size = rxq->datasize;
		rx_oob->sgl[0].mem_key = apc->ac->gdma_dev->gpa_mkey;

		rx_oob->wqe_req.sgl = rx_oob->sgl;
		rx_oob->wqe_req.num_sge = rx_oob->num_sge;
		rx_oob->wqe_req.अंतरभूत_oob_size = 0;
		rx_oob->wqe_req.अंतरभूत_oob_data = शून्य;
		rx_oob->wqe_req.flags = 0;
		rx_oob->wqe_req.client_data_unit = 0;

		*rxq_size += ALIGN(MANA_WQE_HEADER_SIZE +
				   MANA_WQE_SGE_SIZE * rx_oob->num_sge, 32);
		*cq_size += COMP_ENTRY_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mana_push_wqe(काष्ठा mana_rxq *rxq)
अणु
	काष्ठा mana_recv_buf_oob *rx_oob;
	u32 buf_idx;
	पूर्णांक err;

	क्रम (buf_idx = 0; buf_idx < rxq->num_rx_buf; buf_idx++) अणु
		rx_oob = &rxq->rx_oobs[buf_idx];

		err = mana_gd_post_and_ring(rxq->gdma_rq, &rx_oob->wqe_req,
					    &rx_oob->wqe_inf);
		अगर (err)
			वापस -ENOSPC;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा mana_rxq *mana_create_rxq(काष्ठा mana_port_context *apc,
					u32 rxq_idx, काष्ठा mana_eq *eq,
					काष्ठा net_device *ndev)
अणु
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;
	काष्ठा mana_obj_spec wq_spec;
	काष्ठा mana_obj_spec cq_spec;
	काष्ठा gdma_queue_spec spec;
	काष्ठा mana_cq *cq = शून्य;
	काष्ठा gdma_context *gc;
	u32 cq_size, rq_size;
	काष्ठा mana_rxq *rxq;
	पूर्णांक err;

	gc = gd->gdma_context;

	rxq = kzalloc(माप(*rxq) +
		      RX_BUFFERS_PER_QUEUE * माप(काष्ठा mana_recv_buf_oob),
		      GFP_KERNEL);
	अगर (!rxq)
		वापस शून्य;

	rxq->ndev = ndev;
	rxq->num_rx_buf = RX_BUFFERS_PER_QUEUE;
	rxq->rxq_idx = rxq_idx;
	rxq->datasize = ALIGN(MAX_FRAME_SIZE, 64);
	rxq->rxobj = INVALID_MANA_HANDLE;

	err = mana_alloc_rx_wqe(apc, rxq, &rq_size, &cq_size);
	अगर (err)
		जाओ out;

	rq_size = PAGE_ALIGN(rq_size);
	cq_size = PAGE_ALIGN(cq_size);

	/* Create RQ */
	स_रखो(&spec, 0, माप(spec));
	spec.type = GDMA_RQ;
	spec.monitor_avl_buf = true;
	spec.queue_size = rq_size;
	err = mana_gd_create_mana_wq_cq(gd, &spec, &rxq->gdma_rq);
	अगर (err)
		जाओ out;

	/* Create RQ's CQ */
	cq = &rxq->rx_cq;
	cq->gdma_comp_buf = eq->cqe_poll;
	cq->type = MANA_CQ_TYPE_RX;
	cq->rxq = rxq;

	स_रखो(&spec, 0, माप(spec));
	spec.type = GDMA_CQ;
	spec.monitor_avl_buf = false;
	spec.queue_size = cq_size;
	spec.cq.callback = mana_cq_handler;
	spec.cq.parent_eq = eq->eq;
	spec.cq.context = cq;
	err = mana_gd_create_mana_wq_cq(gd, &spec, &cq->gdma_cq);
	अगर (err)
		जाओ out;

	स_रखो(&wq_spec, 0, माप(wq_spec));
	स_रखो(&cq_spec, 0, माप(cq_spec));
	wq_spec.gdma_region = rxq->gdma_rq->mem_info.gdma_region;
	wq_spec.queue_size = rxq->gdma_rq->queue_size;

	cq_spec.gdma_region = cq->gdma_cq->mem_info.gdma_region;
	cq_spec.queue_size = cq->gdma_cq->queue_size;
	cq_spec.modr_ctx_id = 0;
	cq_spec.attached_eq = cq->gdma_cq->cq.parent->id;

	err = mana_create_wq_obj(apc, apc->port_handle, GDMA_RQ,
				 &wq_spec, &cq_spec, &rxq->rxobj);
	अगर (err)
		जाओ out;

	rxq->gdma_rq->id = wq_spec.queue_index;
	cq->gdma_cq->id = cq_spec.queue_index;

	rxq->gdma_rq->mem_info.gdma_region = GDMA_INVALID_DMA_REGION;
	cq->gdma_cq->mem_info.gdma_region = GDMA_INVALID_DMA_REGION;

	rxq->gdma_id = rxq->gdma_rq->id;
	cq->gdma_id = cq->gdma_cq->id;

	err = mana_push_wqe(rxq);
	अगर (err)
		जाओ out;

	अगर (cq->gdma_id >= gc->max_num_cqs)
		जाओ out;

	gc->cq_table[cq->gdma_id] = cq->gdma_cq;

	mana_gd_arm_cq(cq->gdma_cq);
out:
	अगर (!err)
		वापस rxq;

	netdev_err(ndev, "Failed to create RXQ: err = %d\n", err);

	mana_destroy_rxq(apc, rxq, false);

	अगर (cq)
		mana_deinit_cq(apc, cq);

	वापस शून्य;
पूर्ण

अटल पूर्णांक mana_add_rx_queues(काष्ठा mana_port_context *apc,
			      काष्ठा net_device *ndev)
अणु
	काष्ठा mana_rxq *rxq;
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < apc->num_queues; i++) अणु
		rxq = mana_create_rxq(apc, i, &apc->eqs[i], ndev);
		अगर (!rxq) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण

		u64_stats_init(&rxq->stats.syncp);

		apc->rxqs[i] = rxq;
	पूर्ण

	apc->शेष_rxobj = apc->rxqs[0]->rxobj;
out:
	वापस err;
पूर्ण

अटल व्योम mana_destroy_vport(काष्ठा mana_port_context *apc)
अणु
	काष्ठा mana_rxq *rxq;
	u32 rxq_idx;

	क्रम (rxq_idx = 0; rxq_idx < apc->num_queues; rxq_idx++) अणु
		rxq = apc->rxqs[rxq_idx];
		अगर (!rxq)
			जारी;

		mana_destroy_rxq(apc, rxq, true);
		apc->rxqs[rxq_idx] = शून्य;
	पूर्ण

	mana_destroy_txq(apc);
पूर्ण

अटल पूर्णांक mana_create_vport(काष्ठा mana_port_context *apc,
			     काष्ठा net_device *net)
अणु
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;
	पूर्णांक err;

	apc->शेष_rxobj = INVALID_MANA_HANDLE;

	err = mana_cfg_vport(apc, gd->pdid, gd->करोorbell);
	अगर (err)
		वापस err;

	वापस mana_create_txq(apc, net);
पूर्ण

अटल व्योम mana_rss_table_init(काष्ठा mana_port_context *apc)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MANA_INसूचीECT_TABLE_SIZE; i++)
		apc->indir_table[i] =
			ethtool_rxfh_indir_शेष(i, apc->num_queues);
पूर्ण

पूर्णांक mana_config_rss(काष्ठा mana_port_context *apc, क्रमागत TRI_STATE rx,
		    bool update_hash, bool update_tab)
अणु
	u32 queue_idx;
	पूर्णांक i;

	अगर (update_tab) अणु
		क्रम (i = 0; i < MANA_INसूचीECT_TABLE_SIZE; i++) अणु
			queue_idx = apc->indir_table[i];
			apc->rxobj_table[i] = apc->rxqs[queue_idx]->rxobj;
		पूर्ण
	पूर्ण

	वापस mana_cfg_vport_steering(apc, rx, true, update_hash, update_tab);
पूर्ण

अटल पूर्णांक mana_init_port(काष्ठा net_device *ndev)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	u32 max_txq, max_rxq, max_queues;
	पूर्णांक port_idx = apc->port_idx;
	u32 num_indirect_entries;
	पूर्णांक err;

	err = mana_init_port_context(apc);
	अगर (err)
		वापस err;

	err = mana_query_vport_cfg(apc, port_idx, &max_txq, &max_rxq,
				   &num_indirect_entries);
	अगर (err) अणु
		netdev_err(ndev, "Failed to query info for vPort 0\n");
		जाओ reset_apc;
	पूर्ण

	max_queues = min_t(u32, max_txq, max_rxq);
	अगर (apc->max_queues > max_queues)
		apc->max_queues = max_queues;

	अगर (apc->num_queues > apc->max_queues)
		apc->num_queues = apc->max_queues;

	ether_addr_copy(ndev->dev_addr, apc->mac_addr);

	वापस 0;

reset_apc:
	kमुक्त(apc->rxqs);
	apc->rxqs = शून्य;
	वापस err;
पूर्ण

पूर्णांक mana_alloc_queues(काष्ठा net_device *ndev)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	काष्ठा gdma_dev *gd = apc->ac->gdma_dev;
	पूर्णांक err;

	err = mana_create_eq(apc);
	अगर (err)
		वापस err;

	err = mana_create_vport(apc, ndev);
	अगर (err)
		जाओ destroy_eq;

	err = netअगर_set_real_num_tx_queues(ndev, apc->num_queues);
	अगर (err)
		जाओ destroy_vport;

	err = mana_add_rx_queues(apc, ndev);
	अगर (err)
		जाओ destroy_vport;

	apc->rss_state = apc->num_queues > 1 ? TRI_STATE_TRUE : TRI_STATE_FALSE;

	err = netअगर_set_real_num_rx_queues(ndev, apc->num_queues);
	अगर (err)
		जाओ destroy_vport;

	mana_rss_table_init(apc);

	err = mana_config_rss(apc, TRI_STATE_TRUE, true, true);
	अगर (err)
		जाओ destroy_vport;

	वापस 0;

destroy_vport:
	mana_destroy_vport(apc);
destroy_eq:
	mana_destroy_eq(gd->gdma_context, apc);
	वापस err;
पूर्ण

पूर्णांक mana_attach(काष्ठा net_device *ndev)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	पूर्णांक err;

	ASSERT_RTNL();

	err = mana_init_port(ndev);
	अगर (err)
		वापस err;

	err = mana_alloc_queues(ndev);
	अगर (err) अणु
		kमुक्त(apc->rxqs);
		apc->rxqs = शून्य;
		वापस err;
	पूर्ण

	netअगर_device_attach(ndev);

	apc->port_is_up = apc->port_st_save;

	/* Ensure port state updated beक्रमe txq state */
	smp_wmb();

	अगर (apc->port_is_up) अणु
		netअगर_carrier_on(ndev);
		netअगर_tx_wake_all_queues(ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mana_dealloc_queues(काष्ठा net_device *ndev)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	काष्ठा mana_txq *txq;
	पूर्णांक i, err;

	अगर (apc->port_is_up)
		वापस -EINVAL;

	/* No packet can be transmitted now since apc->port_is_up is false.
	 * There is still a tiny chance that mana_poll_tx_cq() can re-enable
	 * a txq because it may not समयly see apc->port_is_up being cleared
	 * to false, but it करोesn't matter since mana_start_xmit() drops any
	 * new packets due to apc->port_is_up being false.
	 *
	 * Drain all the in-flight TX packets
	 */
	क्रम (i = 0; i < apc->num_queues; i++) अणु
		txq = &apc->tx_qp[i].txq;

		जबतक (atomic_पढ़ो(&txq->pending_sends) > 0)
			usleep_range(1000, 2000);
	पूर्ण

	/* We're 100% sure the queues can no दीर्घer be woken up, because
	 * we're sure now mana_poll_tx_cq() can't be running.
	 */

	apc->rss_state = TRI_STATE_FALSE;
	err = mana_config_rss(apc, TRI_STATE_FALSE, false, false);
	अगर (err) अणु
		netdev_err(ndev, "Failed to disable vPort: %d\n", err);
		वापस err;
	पूर्ण

	/* TODO: Implement RX fencing */
	ssleep(1);

	mana_destroy_vport(apc);

	mana_destroy_eq(apc->ac->gdma_dev->gdma_context, apc);

	वापस 0;
पूर्ण

पूर्णांक mana_detach(काष्ठा net_device *ndev, bool from_बंद)
अणु
	काष्ठा mana_port_context *apc = netdev_priv(ndev);
	पूर्णांक err;

	ASSERT_RTNL();

	apc->port_st_save = apc->port_is_up;
	apc->port_is_up = false;

	/* Ensure port state updated beक्रमe txq state */
	smp_wmb();

	netअगर_tx_disable(ndev);
	netअगर_carrier_off(ndev);

	अगर (apc->port_st_save) अणु
		err = mana_dealloc_queues(ndev);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!from_बंद) अणु
		netअगर_device_detach(ndev);
		mana_cleanup_port_context(apc);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक mana_probe_port(काष्ठा mana_context *ac, पूर्णांक port_idx,
			   काष्ठा net_device **ndev_storage)
अणु
	काष्ठा gdma_context *gc = ac->gdma_dev->gdma_context;
	काष्ठा mana_port_context *apc;
	काष्ठा net_device *ndev;
	पूर्णांक err;

	ndev = alloc_etherdev_mq(माप(काष्ठा mana_port_context),
				 gc->max_num_queues);
	अगर (!ndev)
		वापस -ENOMEM;

	*ndev_storage = ndev;

	apc = netdev_priv(ndev);
	apc->ac = ac;
	apc->ndev = ndev;
	apc->max_queues = gc->max_num_queues;
	apc->num_queues = min_t(uपूर्णांक, gc->max_num_queues, MANA_MAX_NUM_QUEUES);
	apc->port_handle = INVALID_MANA_HANDLE;
	apc->port_idx = port_idx;

	ndev->netdev_ops = &mana_devops;
	ndev->ethtool_ops = &mana_ethtool_ops;
	ndev->mtu = ETH_DATA_LEN;
	ndev->max_mtu = ndev->mtu;
	ndev->min_mtu = ndev->mtu;
	ndev->needed_headroom = MANA_HEADROOM;
	SET_NETDEV_DEV(ndev, gc->dev);

	netअगर_carrier_off(ndev);

	netdev_rss_key_fill(apc->hashkey, MANA_HASH_KEY_SIZE);

	err = mana_init_port(ndev);
	अगर (err)
		जाओ मुक्त_net;

	netdev_lockdep_set_classes(ndev);

	ndev->hw_features = NETIF_F_SG | NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM;
	ndev->hw_features |= NETIF_F_RXCSUM;
	ndev->hw_features |= NETIF_F_TSO | NETIF_F_TSO6;
	ndev->hw_features |= NETIF_F_RXHASH;
	ndev->features = ndev->hw_features;
	ndev->vlan_features = 0;

	err = रेजिस्टर_netdev(ndev);
	अगर (err) अणु
		netdev_err(ndev, "Unable to register netdev.\n");
		जाओ reset_apc;
	पूर्ण

	वापस 0;

reset_apc:
	kमुक्त(apc->rxqs);
	apc->rxqs = शून्य;
मुक्त_net:
	*ndev_storage = शून्य;
	netdev_err(ndev, "Failed to probe vPort %d: %d\n", port_idx, err);
	मुक्त_netdev(ndev);
	वापस err;
पूर्ण

पूर्णांक mana_probe(काष्ठा gdma_dev *gd)
अणु
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा device *dev = gc->dev;
	काष्ठा mana_context *ac;
	पूर्णांक err;
	पूर्णांक i;

	dev_info(dev,
		 "Microsoft Azure Network Adapter protocol version: %d.%d.%d\n",
		 MANA_MAJOR_VERSION, MANA_MINOR_VERSION, MANA_MICRO_VERSION);

	err = mana_gd_रेजिस्टर_device(gd);
	अगर (err)
		वापस err;

	ac = kzalloc(माप(*ac), GFP_KERNEL);
	अगर (!ac)
		वापस -ENOMEM;

	ac->gdma_dev = gd;
	ac->num_ports = 1;
	gd->driver_data = ac;

	err = mana_query_device_cfg(ac, MANA_MAJOR_VERSION, MANA_MINOR_VERSION,
				    MANA_MICRO_VERSION, &ac->num_ports);
	अगर (err)
		जाओ out;

	अगर (ac->num_ports > MAX_PORTS_IN_MANA_DEV)
		ac->num_ports = MAX_PORTS_IN_MANA_DEV;

	क्रम (i = 0; i < ac->num_ports; i++) अणु
		err = mana_probe_port(ac, i, &ac->ports[i]);
		अगर (err)
			अवरोध;
	पूर्ण
out:
	अगर (err)
		mana_हटाओ(gd);

	वापस err;
पूर्ण

व्योम mana_हटाओ(काष्ठा gdma_dev *gd)
अणु
	काष्ठा gdma_context *gc = gd->gdma_context;
	काष्ठा mana_context *ac = gd->driver_data;
	काष्ठा device *dev = gc->dev;
	काष्ठा net_device *ndev;
	पूर्णांक i;

	क्रम (i = 0; i < ac->num_ports; i++) अणु
		ndev = ac->ports[i];
		अगर (!ndev) अणु
			अगर (i == 0)
				dev_err(dev, "No net device to remove\n");
			जाओ out;
		पूर्ण

		/* All cleanup actions should stay after rtnl_lock(), otherwise
		 * other functions may access partially cleaned up data.
		 */
		rtnl_lock();

		mana_detach(ndev, false);

		unरेजिस्टर_netdevice(ndev);

		rtnl_unlock();

		मुक्त_netdev(ndev);
	पूर्ण
out:
	mana_gd_deरेजिस्टर_device(gd);
	gd->driver_data = शून्य;
	gd->gdma_context = शून्य;
	kमुक्त(ac);
पूर्ण
