<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Marvell OcteonTx2 RVU Ethernet driver
 *
 * Copyright (C) 2020 Marvell International Ltd.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/pci.h>
#समावेश <net/tso.h>

#समावेश "otx2_reg.h"
#समावेश "otx2_common.h"
#समावेश "otx2_struct.h"
#समावेश "cn10k.h"

अटल व्योम otx2_nix_rq_op_stats(काष्ठा queue_stats *stats,
				 काष्ठा otx2_nic *pfvf, पूर्णांक qidx)
अणु
	u64 incr = (u64)qidx << 32;
	u64 *ptr;

	ptr = (u64 *)otx2_get_regaddr(pfvf, NIX_LF_RQ_OP_OCTS);
	stats->bytes = otx2_atomic64_add(incr, ptr);

	ptr = (u64 *)otx2_get_regaddr(pfvf, NIX_LF_RQ_OP_PKTS);
	stats->pkts = otx2_atomic64_add(incr, ptr);
पूर्ण

अटल व्योम otx2_nix_sq_op_stats(काष्ठा queue_stats *stats,
				 काष्ठा otx2_nic *pfvf, पूर्णांक qidx)
अणु
	u64 incr = (u64)qidx << 32;
	u64 *ptr;

	ptr = (u64 *)otx2_get_regaddr(pfvf, NIX_LF_SQ_OP_OCTS);
	stats->bytes = otx2_atomic64_add(incr, ptr);

	ptr = (u64 *)otx2_get_regaddr(pfvf, NIX_LF_SQ_OP_PKTS);
	stats->pkts = otx2_atomic64_add(incr, ptr);
पूर्ण

व्योम otx2_update_lmac_stats(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा msg_req *req;

	अगर (!netअगर_running(pfvf->netdev))
		वापस;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_cgx_stats(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस;
	पूर्ण

	otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
पूर्ण

व्योम otx2_update_lmac_fec_stats(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा msg_req *req;

	अगर (!netअगर_running(pfvf->netdev))
		वापस;
	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_cgx_fec_stats(&pfvf->mbox);
	अगर (req)
		otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
पूर्ण

पूर्णांक otx2_update_rq_stats(काष्ठा otx2_nic *pfvf, पूर्णांक qidx)
अणु
	काष्ठा otx2_rcv_queue *rq = &pfvf->qset.rq[qidx];

	अगर (!pfvf->qset.rq)
		वापस 0;

	otx2_nix_rq_op_stats(&rq->stats, pfvf, qidx);
	वापस 1;
पूर्ण

पूर्णांक otx2_update_sq_stats(काष्ठा otx2_nic *pfvf, पूर्णांक qidx)
अणु
	काष्ठा otx2_snd_queue *sq = &pfvf->qset.sq[qidx];

	अगर (!pfvf->qset.sq)
		वापस 0;

	otx2_nix_sq_op_stats(&sq->stats, pfvf, qidx);
	वापस 1;
पूर्ण

व्योम otx2_get_dev_stats(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_dev_stats *dev_stats = &pfvf->hw.dev_stats;

#घोषणा OTX2_GET_RX_STATS(reg) \
	 otx2_पढ़ो64(pfvf, NIX_LF_RX_STATX(reg))
#घोषणा OTX2_GET_TX_STATS(reg) \
	 otx2_पढ़ो64(pfvf, NIX_LF_TX_STATX(reg))

	dev_stats->rx_bytes = OTX2_GET_RX_STATS(RX_OCTS);
	dev_stats->rx_drops = OTX2_GET_RX_STATS(RX_DROP);
	dev_stats->rx_bcast_frames = OTX2_GET_RX_STATS(RX_BCAST);
	dev_stats->rx_mcast_frames = OTX2_GET_RX_STATS(RX_MCAST);
	dev_stats->rx_ucast_frames = OTX2_GET_RX_STATS(RX_UCAST);
	dev_stats->rx_frames = dev_stats->rx_bcast_frames +
			       dev_stats->rx_mcast_frames +
			       dev_stats->rx_ucast_frames;

	dev_stats->tx_bytes = OTX2_GET_TX_STATS(TX_OCTS);
	dev_stats->tx_drops = OTX2_GET_TX_STATS(TX_DROP);
	dev_stats->tx_bcast_frames = OTX2_GET_TX_STATS(TX_BCAST);
	dev_stats->tx_mcast_frames = OTX2_GET_TX_STATS(TX_MCAST);
	dev_stats->tx_ucast_frames = OTX2_GET_TX_STATS(TX_UCAST);
	dev_stats->tx_frames = dev_stats->tx_bcast_frames +
			       dev_stats->tx_mcast_frames +
			       dev_stats->tx_ucast_frames;
पूर्ण

व्योम otx2_get_stats64(काष्ठा net_device *netdev,
		      काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा otx2_dev_stats *dev_stats;

	otx2_get_dev_stats(pfvf);

	dev_stats = &pfvf->hw.dev_stats;
	stats->rx_bytes = dev_stats->rx_bytes;
	stats->rx_packets = dev_stats->rx_frames;
	stats->rx_dropped = dev_stats->rx_drops;
	stats->multicast = dev_stats->rx_mcast_frames;

	stats->tx_bytes = dev_stats->tx_bytes;
	stats->tx_packets = dev_stats->tx_frames;
	stats->tx_dropped = dev_stats->tx_drops;
पूर्ण
EXPORT_SYMBOL(otx2_get_stats64);

/* Sync MAC address with RVU AF */
अटल पूर्णांक otx2_hw_set_mac_addr(काष्ठा otx2_nic *pfvf, u8 *mac)
अणु
	काष्ठा nix_set_mac_addr *req;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_nix_set_mac_addr(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	ether_addr_copy(req->mac_addr, mac);

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण

अटल पूर्णांक otx2_hw_get_mac_addr(काष्ठा otx2_nic *pfvf,
				काष्ठा net_device *netdev)
अणु
	काष्ठा nix_get_mac_addr_rsp *rsp;
	काष्ठा mbox_msghdr *msghdr;
	काष्ठा msg_req *req;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_nix_get_mac_addr(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस err;
	पूर्ण

	msghdr = otx2_mbox_get_rsp(&pfvf->mbox.mbox, 0, &req->hdr);
	अगर (IS_ERR(msghdr)) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस PTR_ERR(msghdr);
	पूर्ण
	rsp = (काष्ठा nix_get_mac_addr_rsp *)msghdr;
	ether_addr_copy(netdev->dev_addr, rsp->mac_addr);
	mutex_unlock(&pfvf->mbox.lock);

	वापस 0;
पूर्ण

पूर्णांक otx2_set_mac_address(काष्ठा net_device *netdev, व्योम *p)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	काष्ठा sockaddr *addr = p;

	अगर (!is_valid_ether_addr(addr->sa_data))
		वापस -EADDRNOTAVAIL;

	अगर (!otx2_hw_set_mac_addr(pfvf, addr->sa_data)) अणु
		स_नकल(netdev->dev_addr, addr->sa_data, netdev->addr_len);
		/* update dmac field in vlan offload rule */
		अगर (pfvf->flags & OTX2_FLAG_RX_VLAN_SUPPORT)
			otx2_install_rxvlan_offload_flow(pfvf);
	पूर्ण अन्यथा अणु
		वापस -EPERM;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(otx2_set_mac_address);

पूर्णांक otx2_hw_set_mtu(काष्ठा otx2_nic *pfvf, पूर्णांक mtu)
अणु
	काष्ठा nix_frs_cfg *req;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_nix_set_hw_frs(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	req->maxlen = pfvf->max_frs;

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण

पूर्णांक otx2_config_छोड़ो_frm(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा cgx_छोड़ो_frm_cfg *req;
	पूर्णांक err;

	अगर (is_otx2_lbkvf(pfvf->pdev))
		वापस 0;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_cgx_cfg_छोड़ो_frm(&pfvf->mbox);
	अगर (!req) अणु
		err = -ENOMEM;
		जाओ unlock;
	पूर्ण

	req->rx_छोड़ो = !!(pfvf->flags & OTX2_FLAG_RX_PAUSE_ENABLED);
	req->tx_छोड़ो = !!(pfvf->flags & OTX2_FLAG_TX_PAUSE_ENABLED);
	req->set = 1;

	err = otx2_sync_mbox_msg(&pfvf->mbox);
unlock:
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण

पूर्णांक otx2_set_flowkey_cfg(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_rss_info *rss = &pfvf->hw.rss_info;
	काष्ठा nix_rss_flowkey_cfg *req;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	req = otx2_mbox_alloc_msg_nix_rss_flowkey_cfg(&pfvf->mbox);
	अगर (!req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण
	req->mcam_index = -1; /* Default or reserved index */
	req->flowkey_cfg = rss->flowkey_cfg;
	req->group = DEFAULT_RSS_CONTEXT_GROUP;

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);
	वापस err;
पूर्ण

पूर्णांक otx2_set_rss_table(काष्ठा otx2_nic *pfvf, पूर्णांक ctx_id)
अणु
	काष्ठा otx2_rss_info *rss = &pfvf->hw.rss_info;
	स्थिर पूर्णांक index = rss->rss_size * ctx_id;
	काष्ठा mbox *mbox = &pfvf->mbox;
	काष्ठा otx2_rss_ctx *rss_ctx;
	काष्ठा nix_aq_enq_req *aq;
	पूर्णांक idx, err;

	mutex_lock(&mbox->lock);
	rss_ctx = rss->rss_ctx[ctx_id];
	/* Get memory to put this msg */
	क्रम (idx = 0; idx < rss->rss_size; idx++) अणु
		aq = otx2_mbox_alloc_msg_nix_aq_enq(mbox);
		अगर (!aq) अणु
			/* The shared memory buffer can be full.
			 * Flush it and retry
			 */
			err = otx2_sync_mbox_msg(mbox);
			अगर (err) अणु
				mutex_unlock(&mbox->lock);
				वापस err;
			पूर्ण
			aq = otx2_mbox_alloc_msg_nix_aq_enq(mbox);
			अगर (!aq) अणु
				mutex_unlock(&mbox->lock);
				वापस -ENOMEM;
			पूर्ण
		पूर्ण

		aq->rss.rq = rss_ctx->ind_tbl[idx];

		/* Fill AQ info */
		aq->qidx = index + idx;
		aq->ctype = NIX_AQ_CTYPE_RSS;
		aq->op = NIX_AQ_INSTOP_INIT;
	पूर्ण
	err = otx2_sync_mbox_msg(mbox);
	mutex_unlock(&mbox->lock);
	वापस err;
पूर्ण

व्योम otx2_set_rss_key(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_rss_info *rss = &pfvf->hw.rss_info;
	u64 *key = (u64 *)&rss->key[4];
	पूर्णांक idx;

	/* 352bit or 44byte key needs to be configured as below
	 * NIX_LF_RX_SECRETX0 = key<351:288>
	 * NIX_LF_RX_SECRETX1 = key<287:224>
	 * NIX_LF_RX_SECRETX2 = key<223:160>
	 * NIX_LF_RX_SECRETX3 = key<159:96>
	 * NIX_LF_RX_SECRETX4 = key<95:32>
	 * NIX_LF_RX_SECRETX5<63:32> = key<31:0>
	 */
	otx2_ग_लिखो64(pfvf, NIX_LF_RX_SECRETX(5),
		     (u64)(*((u32 *)&rss->key)) << 32);
	idx = माप(rss->key) / माप(u64);
	जबतक (idx > 0) अणु
		idx--;
		otx2_ग_लिखो64(pfvf, NIX_LF_RX_SECRETX(idx), *key++);
	पूर्ण
पूर्ण

पूर्णांक otx2_rss_init(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_rss_info *rss = &pfvf->hw.rss_info;
	काष्ठा otx2_rss_ctx *rss_ctx;
	पूर्णांक idx, ret = 0;

	rss->rss_size = माप(*rss->rss_ctx[DEFAULT_RSS_CONTEXT_GROUP]);

	/* Init RSS key अगर it is not setup alपढ़ोy */
	अगर (!rss->enable)
		netdev_rss_key_fill(rss->key, माप(rss->key));
	otx2_set_rss_key(pfvf);

	अगर (!netअगर_is_rxfh_configured(pfvf->netdev)) अणु
		/* Set RSS group 0 as शेष indirection table */
		rss->rss_ctx[DEFAULT_RSS_CONTEXT_GROUP] = kzalloc(rss->rss_size,
								  GFP_KERNEL);
		अगर (!rss->rss_ctx[DEFAULT_RSS_CONTEXT_GROUP])
			वापस -ENOMEM;

		rss_ctx = rss->rss_ctx[DEFAULT_RSS_CONTEXT_GROUP];
		क्रम (idx = 0; idx < rss->rss_size; idx++)
			rss_ctx->ind_tbl[idx] =
				ethtool_rxfh_indir_शेष(idx,
							   pfvf->hw.rx_queues);
	पूर्ण
	ret = otx2_set_rss_table(pfvf, DEFAULT_RSS_CONTEXT_GROUP);
	अगर (ret)
		वापस ret;

	/* Flowkey or hash config to be used क्रम generating flow tag */
	rss->flowkey_cfg = rss->enable ? rss->flowkey_cfg :
			   NIX_FLOW_KEY_TYPE_IPV4 | NIX_FLOW_KEY_TYPE_IPV6 |
			   NIX_FLOW_KEY_TYPE_TCP | NIX_FLOW_KEY_TYPE_UDP |
			   NIX_FLOW_KEY_TYPE_SCTP | NIX_FLOW_KEY_TYPE_VLAN |
			   NIX_FLOW_KEY_TYPE_IPV4_PROTO;

	ret = otx2_set_flowkey_cfg(pfvf);
	अगर (ret)
		वापस ret;

	rss->enable = true;
	वापस 0;
पूर्ण

/* Setup UDP segmentation algorithm in HW */
अटल व्योम otx2_setup_udp_segmentation(काष्ठा nix_lso_क्रमmat_cfg *lso, bool v4)
अणु
	काष्ठा nix_lso_क्रमmat *field;

	field = (काष्ठा nix_lso_क्रमmat *)&lso->fields[0];
	lso->field_mask = GENMASK(18, 0);

	/* IP's Length field */
	field->layer = NIX_TXLAYER_OL3;
	/* In ipv4, length field is at offset 2 bytes, क्रम ipv6 it's 4 */
	field->offset = v4 ? 2 : 4;
	field->sizem1 = 1; /* i.e 2 bytes */
	field->alg = NIX_LSOALG_ADD_PAYLEN;
	field++;

	/* No ID field in IPv6 header */
	अगर (v4) अणु
		/* Increment IPID */
		field->layer = NIX_TXLAYER_OL3;
		field->offset = 4;
		field->sizem1 = 1; /* i.e 2 bytes */
		field->alg = NIX_LSOALG_ADD_SEGNUM;
		field++;
	पूर्ण

	/* Update length in UDP header */
	field->layer = NIX_TXLAYER_OL4;
	field->offset = 4;
	field->sizem1 = 1;
	field->alg = NIX_LSOALG_ADD_PAYLEN;
पूर्ण

/* Setup segmentation algorithms in HW and retrieve algorithm index */
व्योम otx2_setup_segmentation(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा nix_lso_क्रमmat_cfg_rsp *rsp;
	काष्ठा nix_lso_क्रमmat_cfg *lso;
	काष्ठा otx2_hw *hw = &pfvf->hw;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);

	/* UDPv4 segmentation */
	lso = otx2_mbox_alloc_msg_nix_lso_क्रमmat_cfg(&pfvf->mbox);
	अगर (!lso)
		जाओ fail;

	/* Setup UDP/IP header fields that HW should update per segment */
	otx2_setup_udp_segmentation(lso, true);

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err)
		जाओ fail;

	rsp = (काष्ठा nix_lso_क्रमmat_cfg_rsp *)
			otx2_mbox_get_rsp(&pfvf->mbox.mbox, 0, &lso->hdr);
	अगर (IS_ERR(rsp))
		जाओ fail;

	hw->lso_udpv4_idx = rsp->lso_क्रमmat_idx;

	/* UDPv6 segmentation */
	lso = otx2_mbox_alloc_msg_nix_lso_क्रमmat_cfg(&pfvf->mbox);
	अगर (!lso)
		जाओ fail;

	/* Setup UDP/IP header fields that HW should update per segment */
	otx2_setup_udp_segmentation(lso, false);

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err)
		जाओ fail;

	rsp = (काष्ठा nix_lso_क्रमmat_cfg_rsp *)
			otx2_mbox_get_rsp(&pfvf->mbox.mbox, 0, &lso->hdr);
	अगर (IS_ERR(rsp))
		जाओ fail;

	hw->lso_udpv6_idx = rsp->lso_क्रमmat_idx;
	mutex_unlock(&pfvf->mbox.lock);
	वापस;
fail:
	mutex_unlock(&pfvf->mbox.lock);
	netdev_info(pfvf->netdev,
		    "Failed to get LSO index for UDP GSO offload, disabling\n");
	pfvf->netdev->hw_features &= ~NETIF_F_GSO_UDP_L4;
पूर्ण

व्योम otx2_config_irq_coalescing(काष्ठा otx2_nic *pfvf, पूर्णांक qidx)
अणु
	/* Configure CQE पूर्णांकerrupt coalescing parameters
	 *
	 * HW triggers an irq when ECOUNT > cq_ecount_रुको, hence
	 * set 1 less than cq_ecount_रुको. And cq_समय_रुको is in
	 * usecs, convert that to 100ns count.
	 */
	otx2_ग_लिखो64(pfvf, NIX_LF_CINTX_WAIT(qidx),
		     ((u64)(pfvf->hw.cq_समय_रुको * 10) << 48) |
		     ((u64)pfvf->hw.cq_qcount_रुको << 32) |
		     (pfvf->hw.cq_ecount_रुको - 1));
पूर्ण

पूर्णांक __otx2_alloc_rbuf(काष्ठा otx2_nic *pfvf, काष्ठा otx2_pool *pool,
		      dma_addr_t *dma)
अणु
	u8 *buf;

	buf = napi_alloc_frag_align(pool->rbsize, OTX2_ALIGN);
	अगर (unlikely(!buf))
		वापस -ENOMEM;

	*dma = dma_map_single_attrs(pfvf->dev, buf, pool->rbsize,
				    DMA_FROM_DEVICE, DMA_ATTR_SKIP_CPU_SYNC);
	अगर (unlikely(dma_mapping_error(pfvf->dev, *dma))) अणु
		page_frag_मुक्त(buf);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_alloc_rbuf(काष्ठा otx2_nic *pfvf, काष्ठा otx2_pool *pool,
			   dma_addr_t *dma)
अणु
	पूर्णांक ret;

	local_bh_disable();
	ret = __otx2_alloc_rbuf(pfvf, pool, dma);
	local_bh_enable();
	वापस ret;
पूर्ण

पूर्णांक otx2_alloc_buffer(काष्ठा otx2_nic *pfvf, काष्ठा otx2_cq_queue *cq,
		      dma_addr_t *dma)
अणु
	अगर (unlikely(__otx2_alloc_rbuf(pfvf, cq->rbpool, dma))) अणु
		काष्ठा refill_work *work;
		काष्ठा delayed_work *dwork;

		work = &pfvf->refill_wrk[cq->cq_idx];
		dwork = &work->pool_refill_work;
		/* Schedule a task अगर no other task is running */
		अगर (!cq->refill_task_sched) अणु
			cq->refill_task_sched = true;
			schedule_delayed_work(dwork,
					      msecs_to_jअगरfies(100));
		पूर्ण
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

व्योम otx2_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txq)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);

	schedule_work(&pfvf->reset_task);
पूर्ण
EXPORT_SYMBOL(otx2_tx_समयout);

व्योम otx2_get_mac_from_af(काष्ठा net_device *netdev)
अणु
	काष्ठा otx2_nic *pfvf = netdev_priv(netdev);
	पूर्णांक err;

	err = otx2_hw_get_mac_addr(pfvf, netdev);
	अगर (err)
		dev_warn(pfvf->dev, "Failed to read mac from hardware\n");

	/* If AF करोesn't provide a valid MAC, generate a अक्रमom one */
	अगर (!is_valid_ether_addr(netdev->dev_addr))
		eth_hw_addr_अक्रमom(netdev);
पूर्ण
EXPORT_SYMBOL(otx2_get_mac_from_af);

अटल पूर्णांक otx2_get_link(काष्ठा otx2_nic *pfvf)
अणु
	पूर्णांक link = 0;
	u16 map;

	/* cgx lmac link */
	अगर (pfvf->hw.tx_chan_base >= CGX_CHAN_BASE) अणु
		map = pfvf->hw.tx_chan_base & 0x7FF;
		link = 4 * ((map >> 8) & 0xF) + ((map >> 4) & 0xF);
	पूर्ण
	/* LBK channel */
	अगर (pfvf->hw.tx_chan_base < SDP_CHAN_BASE) अणु
		map = pfvf->hw.tx_chan_base & 0x7FF;
		link = pfvf->hw.cgx_links | ((map >> 8) & 0xF);
	पूर्ण

	वापस link;
पूर्ण

पूर्णांक otx2_txschq_config(काष्ठा otx2_nic *pfvf, पूर्णांक lvl)
अणु
	काष्ठा otx2_hw *hw = &pfvf->hw;
	काष्ठा nix_txschq_config *req;
	u64 schq, parent;

	req = otx2_mbox_alloc_msg_nix_txschq_cfg(&pfvf->mbox);
	अगर (!req)
		वापस -ENOMEM;

	req->lvl = lvl;
	req->num_regs = 1;

	schq = hw->txschq_list[lvl][0];
	/* Set topology e.t.c configuration */
	अगर (lvl == NIX_TXSCH_LVL_SMQ) अणु
		req->reg[0] = NIX_AF_SMQX_CFG(schq);
		req->regval[0] = ((pfvf->netdev->max_mtu + OTX2_ETH_HLEN) << 8)
				  | OTX2_MIN_MTU;

		req->regval[0] |= (0x20ULL << 51) | (0x80ULL << 39) |
				  (0x2ULL << 36);
		req->num_regs++;
		/* MDQ config */
		parent =  hw->txschq_list[NIX_TXSCH_LVL_TL4][0];
		req->reg[1] = NIX_AF_MDQX_PARENT(schq);
		req->regval[1] = parent << 16;
		req->num_regs++;
		/* Set DWRR quantum */
		req->reg[2] = NIX_AF_MDQX_SCHEDULE(schq);
		req->regval[2] =  DFLT_RR_QTM;
	पूर्ण अन्यथा अगर (lvl == NIX_TXSCH_LVL_TL4) अणु
		parent =  hw->txschq_list[NIX_TXSCH_LVL_TL3][0];
		req->reg[0] = NIX_AF_TL4X_PARENT(schq);
		req->regval[0] = parent << 16;
		req->num_regs++;
		req->reg[1] = NIX_AF_TL4X_SCHEDULE(schq);
		req->regval[1] = DFLT_RR_QTM;
	पूर्ण अन्यथा अगर (lvl == NIX_TXSCH_LVL_TL3) अणु
		parent = hw->txschq_list[NIX_TXSCH_LVL_TL2][0];
		req->reg[0] = NIX_AF_TL3X_PARENT(schq);
		req->regval[0] = parent << 16;
		req->num_regs++;
		req->reg[1] = NIX_AF_TL3X_SCHEDULE(schq);
		req->regval[1] = DFLT_RR_QTM;
	पूर्ण अन्यथा अगर (lvl == NIX_TXSCH_LVL_TL2) अणु
		parent =  hw->txschq_list[NIX_TXSCH_LVL_TL1][0];
		req->reg[0] = NIX_AF_TL2X_PARENT(schq);
		req->regval[0] = parent << 16;

		req->num_regs++;
		req->reg[1] = NIX_AF_TL2X_SCHEDULE(schq);
		req->regval[1] = TXSCH_TL1_DFLT_RR_PRIO << 24 | DFLT_RR_QTM;

		req->num_regs++;
		req->reg[2] = NIX_AF_TL3_TL2X_LINKX_CFG(schq,
							otx2_get_link(pfvf));
		/* Enable this queue and backpressure */
		req->regval[2] = BIT_ULL(13) | BIT_ULL(12);

	पूर्ण अन्यथा अगर (lvl == NIX_TXSCH_LVL_TL1) अणु
		/* Default config क्रम TL1.
		 * For VF this is always ignored.
		 */

		/* Set DWRR quantum */
		req->reg[0] = NIX_AF_TL1X_SCHEDULE(schq);
		req->regval[0] = TXSCH_TL1_DFLT_RR_QTM;

		req->num_regs++;
		req->reg[1] = NIX_AF_TL1X_TOPOLOGY(schq);
		req->regval[1] = (TXSCH_TL1_DFLT_RR_PRIO << 1);

		req->num_regs++;
		req->reg[2] = NIX_AF_TL1X_CIR(schq);
		req->regval[2] = 0;
	पूर्ण

	वापस otx2_sync_mbox_msg(&pfvf->mbox);
पूर्ण

पूर्णांक otx2_txsch_alloc(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा nix_txsch_alloc_req *req;
	पूर्णांक lvl;

	/* Get memory to put this msg */
	req = otx2_mbox_alloc_msg_nix_txsch_alloc(&pfvf->mbox);
	अगर (!req)
		वापस -ENOMEM;

	/* Request one schq per level */
	क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++)
		req->schq[lvl] = 1;

	वापस otx2_sync_mbox_msg(&pfvf->mbox);
पूर्ण

पूर्णांक otx2_txschq_stop(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा nix_txsch_मुक्त_req *मुक्त_req;
	पूर्णांक lvl, schq, err;

	mutex_lock(&pfvf->mbox.lock);
	/* Free the transmit schedulers */
	मुक्त_req = otx2_mbox_alloc_msg_nix_txsch_मुक्त(&pfvf->mbox);
	अगर (!मुक्त_req) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	मुक्त_req->flags = TXSCHQ_FREE_ALL;
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	mutex_unlock(&pfvf->mbox.lock);

	/* Clear the txschq list */
	क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++) अणु
		क्रम (schq = 0; schq < MAX_TXSCHQ_PER_FUNC; schq++)
			pfvf->hw.txschq_list[lvl][schq] = 0;
	पूर्ण
	वापस err;
पूर्ण

व्योम otx2_sqb_flush(काष्ठा otx2_nic *pfvf)
अणु
	पूर्णांक qidx, sqe_tail, sqe_head;
	u64 incr, *ptr, val;
	पूर्णांक समयout = 1000;

	ptr = (u64 *)otx2_get_regaddr(pfvf, NIX_LF_SQ_OP_STATUS);
	क्रम (qidx = 0; qidx < pfvf->hw.tx_queues; qidx++) अणु
		incr = (u64)qidx << 32;
		जबतक (समयout) अणु
			val = otx2_atomic64_add(incr, ptr);
			sqe_head = (val >> 20) & 0x3F;
			sqe_tail = (val >> 28) & 0x3F;
			अगर (sqe_head == sqe_tail)
				अवरोध;
			usleep_range(1, 3);
			समयout--;
		पूर्ण
	पूर्ण
पूर्ण

/* RED and drop levels of CQ on packet reception.
 * For CQ level is measure of emptiness ( 0x0 = full, 255 = empty).
 */
#घोषणा RQ_PASS_LVL_CQ(skid, qsize)	((((skid) + 16) * 256) / (qsize))
#घोषणा RQ_DROP_LVL_CQ(skid, qsize)	(((skid) * 256) / (qsize))

/* RED and drop levels of AURA क्रम packet reception.
 * For AURA level is measure of fullness (0x0 = empty, 255 = full).
 * Eg: For RQ length 1K, क्रम pass/drop level 204/230.
 * RED accepts pkts अगर मुक्त poपूर्णांकers > 102 & <= 205.
 * Drops pkts अगर मुक्त poपूर्णांकers < 102.
 */
#घोषणा RQ_BP_LVL_AURA   (255 - ((85 * 256) / 100)) /* BP when 85% is full */
#घोषणा RQ_PASS_LVL_AURA (255 - ((95 * 256) / 100)) /* RED when 95% is full */
#घोषणा RQ_DROP_LVL_AURA (255 - ((99 * 256) / 100)) /* Drop when 99% is full */

अटल पूर्णांक otx2_rq_init(काष्ठा otx2_nic *pfvf, u16 qidx, u16 lpb_aura)
अणु
	काष्ठा otx2_qset *qset = &pfvf->qset;
	काष्ठा nix_aq_enq_req *aq;

	/* Get memory to put this msg */
	aq = otx2_mbox_alloc_msg_nix_aq_enq(&pfvf->mbox);
	अगर (!aq)
		वापस -ENOMEM;

	aq->rq.cq = qidx;
	aq->rq.ena = 1;
	aq->rq.pb_caching = 1;
	aq->rq.lpb_aura = lpb_aura; /* Use large packet buffer aura */
	aq->rq.lpb_sizem1 = (DMA_BUFFER_LEN(pfvf->rbsize) / 8) - 1;
	aq->rq.xqe_imm_size = 0; /* Copying of packet to CQE not needed */
	aq->rq.flow_tagw = 32; /* Copy full 32bit flow_tag to CQE header */
	aq->rq.qपूर्णांक_idx = 0;
	aq->rq.lpb_drop_ena = 1; /* Enable RED dropping क्रम AURA */
	aq->rq.xqe_drop_ena = 1; /* Enable RED dropping क्रम CQ/SSO */
	aq->rq.xqe_pass = RQ_PASS_LVL_CQ(pfvf->hw.rq_skid, qset->rqe_cnt);
	aq->rq.xqe_drop = RQ_DROP_LVL_CQ(pfvf->hw.rq_skid, qset->rqe_cnt);
	aq->rq.lpb_aura_pass = RQ_PASS_LVL_AURA;
	aq->rq.lpb_aura_drop = RQ_DROP_LVL_AURA;

	/* Fill AQ info */
	aq->qidx = qidx;
	aq->ctype = NIX_AQ_CTYPE_RQ;
	aq->op = NIX_AQ_INSTOP_INIT;

	वापस otx2_sync_mbox_msg(&pfvf->mbox);
पूर्ण

पूर्णांक otx2_sq_aq_init(व्योम *dev, u16 qidx, u16 sqb_aura)
अणु
	काष्ठा otx2_nic *pfvf = dev;
	काष्ठा otx2_snd_queue *sq;
	काष्ठा nix_aq_enq_req *aq;

	sq = &pfvf->qset.sq[qidx];
	sq->lmt_addr = (__क्रमce u64 *)(pfvf->reg_base + LMT_LF_LMTLINEX(qidx));
	/* Get memory to put this msg */
	aq = otx2_mbox_alloc_msg_nix_aq_enq(&pfvf->mbox);
	अगर (!aq)
		वापस -ENOMEM;

	aq->sq.cq = pfvf->hw.rx_queues + qidx;
	aq->sq.max_sqe_size = NIX_MAXSQESZ_W16; /* 128 byte */
	aq->sq.cq_ena = 1;
	aq->sq.ena = 1;
	/* Only one SMQ is allocated, map all SQ's to that SMQ  */
	aq->sq.smq = pfvf->hw.txschq_list[NIX_TXSCH_LVL_SMQ][0];
	aq->sq.smq_rr_quantum = DFLT_RR_QTM;
	aq->sq.शेष_chan = pfvf->hw.tx_chan_base;
	aq->sq.sqe_stype = NIX_STYPE_STF; /* Cache SQB */
	aq->sq.sqb_aura = sqb_aura;
	aq->sq.sq_पूर्णांक_ena = NIX_SQINT_BITS;
	aq->sq.qपूर्णांक_idx = 0;
	/* Due pipelining impact minimum 2000 unused SQ CQE's
	 * need to मुख्यtain to aव्योम CQ overflow.
	 */
	aq->sq.cq_limit = ((SEND_CQ_SKID * 256) / (pfvf->qset.sqe_cnt));

	/* Fill AQ info */
	aq->qidx = qidx;
	aq->ctype = NIX_AQ_CTYPE_SQ;
	aq->op = NIX_AQ_INSTOP_INIT;

	वापस otx2_sync_mbox_msg(&pfvf->mbox);
पूर्ण

अटल पूर्णांक otx2_sq_init(काष्ठा otx2_nic *pfvf, u16 qidx, u16 sqb_aura)
अणु
	काष्ठा otx2_qset *qset = &pfvf->qset;
	काष्ठा otx2_snd_queue *sq;
	काष्ठा otx2_pool *pool;
	पूर्णांक err;

	pool = &pfvf->qset.pool[sqb_aura];
	sq = &qset->sq[qidx];
	sq->sqe_size = NIX_SQESZ_W16 ? 64 : 128;
	sq->sqe_cnt = qset->sqe_cnt;

	err = qmem_alloc(pfvf->dev, &sq->sqe, 1, sq->sqe_size);
	अगर (err)
		वापस err;

	err = qmem_alloc(pfvf->dev, &sq->tso_hdrs, qset->sqe_cnt,
			 TSO_HEADER_SIZE);
	अगर (err)
		वापस err;

	sq->sqe_base = sq->sqe->base;
	sq->sg = kसुस्मृति(qset->sqe_cnt, माप(काष्ठा sg_list), GFP_KERNEL);
	अगर (!sq->sg)
		वापस -ENOMEM;

	अगर (pfvf->ptp) अणु
		err = qmem_alloc(pfvf->dev, &sq->बारtamps, qset->sqe_cnt,
				 माप(*sq->बारtamps));
		अगर (err)
			वापस err;
	पूर्ण

	sq->head = 0;
	sq->sqe_per_sqb = (pfvf->hw.sqb_size / sq->sqe_size) - 1;
	sq->num_sqbs = (qset->sqe_cnt + sq->sqe_per_sqb) / sq->sqe_per_sqb;
	/* Set SQE threshold to 10% of total SQEs */
	sq->sqe_thresh = ((sq->num_sqbs * sq->sqe_per_sqb) * 10) / 100;
	sq->aura_id = sqb_aura;
	sq->aura_fc_addr = pool->fc_addr->base;
	sq->io_addr = (__क्रमce u64)otx2_get_regaddr(pfvf, NIX_LF_OP_SENDX(0));

	sq->stats.bytes = 0;
	sq->stats.pkts = 0;

	वापस pfvf->hw_ops->sq_aq_init(pfvf, qidx, sqb_aura);

पूर्ण

अटल पूर्णांक otx2_cq_init(काष्ठा otx2_nic *pfvf, u16 qidx)
अणु
	काष्ठा otx2_qset *qset = &pfvf->qset;
	काष्ठा nix_aq_enq_req *aq;
	काष्ठा otx2_cq_queue *cq;
	पूर्णांक err, pool_id;

	cq = &qset->cq[qidx];
	cq->cq_idx = qidx;
	अगर (qidx < pfvf->hw.rx_queues) अणु
		cq->cq_type = CQ_RX;
		cq->cपूर्णांक_idx = qidx;
		cq->cqe_cnt = qset->rqe_cnt;
	पूर्ण अन्यथा अणु
		cq->cq_type = CQ_TX;
		cq->cपूर्णांक_idx = qidx - pfvf->hw.rx_queues;
		cq->cqe_cnt = qset->sqe_cnt;
	पूर्ण
	cq->cqe_size = pfvf->qset.xqe_size;

	/* Allocate memory क्रम CQEs */
	err = qmem_alloc(pfvf->dev, &cq->cqe, cq->cqe_cnt, cq->cqe_size);
	अगर (err)
		वापस err;

	/* Save CQE CPU base क्रम faster reference */
	cq->cqe_base = cq->cqe->base;
	/* In हाल where all RQs auras poपूर्णांक to single pool,
	 * all CQs receive buffer pool also poपूर्णांक to same pool.
	 */
	pool_id = ((cq->cq_type == CQ_RX) &&
		   (pfvf->hw.rqpool_cnt != pfvf->hw.rx_queues)) ? 0 : qidx;
	cq->rbpool = &qset->pool[pool_id];
	cq->refill_task_sched = false;

	/* Get memory to put this msg */
	aq = otx2_mbox_alloc_msg_nix_aq_enq(&pfvf->mbox);
	अगर (!aq)
		वापस -ENOMEM;

	aq->cq.ena = 1;
	aq->cq.qsize = Q_SIZE(cq->cqe_cnt, 4);
	aq->cq.caching = 1;
	aq->cq.base = cq->cqe->iova;
	aq->cq.cपूर्णांक_idx = cq->cपूर्णांक_idx;
	aq->cq.cq_err_पूर्णांक_ena = NIX_CQERRINT_BITS;
	aq->cq.qपूर्णांक_idx = 0;
	aq->cq.avg_level = 255;

	अगर (qidx < pfvf->hw.rx_queues) अणु
		aq->cq.drop = RQ_DROP_LVL_CQ(pfvf->hw.rq_skid, cq->cqe_cnt);
		aq->cq.drop_ena = 1;

		/* Enable receive CQ backpressure */
		aq->cq.bp_ena = 1;
		aq->cq.bpid = pfvf->bpid[0];

		/* Set backpressure level is same as cq pass level */
		aq->cq.bp = RQ_PASS_LVL_CQ(pfvf->hw.rq_skid, qset->rqe_cnt);
	पूर्ण

	/* Fill AQ info */
	aq->qidx = qidx;
	aq->ctype = NIX_AQ_CTYPE_CQ;
	aq->op = NIX_AQ_INSTOP_INIT;

	वापस otx2_sync_mbox_msg(&pfvf->mbox);
पूर्ण

अटल व्योम otx2_pool_refill_task(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा otx2_cq_queue *cq;
	काष्ठा otx2_pool *rbpool;
	काष्ठा refill_work *wrk;
	पूर्णांक qidx, मुक्त_ptrs = 0;
	काष्ठा otx2_nic *pfvf;
	dma_addr_t bufptr;

	wrk = container_of(work, काष्ठा refill_work, pool_refill_work.work);
	pfvf = wrk->pf;
	qidx = wrk - pfvf->refill_wrk;
	cq = &pfvf->qset.cq[qidx];
	rbpool = cq->rbpool;
	मुक्त_ptrs = cq->pool_ptrs;

	जबतक (cq->pool_ptrs) अणु
		अगर (otx2_alloc_rbuf(pfvf, rbpool, &bufptr)) अणु
			/* Schedule a WQ अगर we fails to मुक्त atleast half of the
			 * poपूर्णांकers अन्यथा enable napi क्रम this RQ.
			 */
			अगर (!((मुक्त_ptrs - cq->pool_ptrs) > मुक्त_ptrs / 2)) अणु
				काष्ठा delayed_work *dwork;

				dwork = &wrk->pool_refill_work;
				schedule_delayed_work(dwork,
						      msecs_to_jअगरfies(100));
			पूर्ण अन्यथा अणु
				cq->refill_task_sched = false;
			पूर्ण
			वापस;
		पूर्ण
		pfvf->hw_ops->aura_मुक्तptr(pfvf, qidx, bufptr + OTX2_HEAD_ROOM);
		cq->pool_ptrs--;
	पूर्ण
	cq->refill_task_sched = false;
पूर्ण

पूर्णांक otx2_config_nix_queues(काष्ठा otx2_nic *pfvf)
अणु
	पूर्णांक qidx, err;

	/* Initialize RX queues */
	क्रम (qidx = 0; qidx < pfvf->hw.rx_queues; qidx++) अणु
		u16 lpb_aura = otx2_get_pool_idx(pfvf, AURA_NIX_RQ, qidx);

		err = otx2_rq_init(pfvf, qidx, lpb_aura);
		अगर (err)
			वापस err;
	पूर्ण

	/* Initialize TX queues */
	क्रम (qidx = 0; qidx < pfvf->hw.tx_queues; qidx++) अणु
		u16 sqb_aura = otx2_get_pool_idx(pfvf, AURA_NIX_SQ, qidx);

		err = otx2_sq_init(pfvf, qidx, sqb_aura);
		अगर (err)
			वापस err;
	पूर्ण

	/* Initialize completion queues */
	क्रम (qidx = 0; qidx < pfvf->qset.cq_cnt; qidx++) अणु
		err = otx2_cq_init(pfvf, qidx);
		अगर (err)
			वापस err;
	पूर्ण

	/* Initialize work queue क्रम receive buffer refill */
	pfvf->refill_wrk = devm_kसुस्मृति(pfvf->dev, pfvf->qset.cq_cnt,
					माप(काष्ठा refill_work), GFP_KERNEL);
	अगर (!pfvf->refill_wrk)
		वापस -ENOMEM;

	क्रम (qidx = 0; qidx < pfvf->qset.cq_cnt; qidx++) अणु
		pfvf->refill_wrk[qidx].pf = pfvf;
		INIT_DELAYED_WORK(&pfvf->refill_wrk[qidx].pool_refill_work,
				  otx2_pool_refill_task);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक otx2_config_nix(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा nix_lf_alloc_req  *nixlf;
	काष्ठा nix_lf_alloc_rsp *rsp;
	पूर्णांक err;

	pfvf->qset.xqe_size = NIX_XQESZ_W16 ? 128 : 512;

	/* Get memory to put this msg */
	nixlf = otx2_mbox_alloc_msg_nix_lf_alloc(&pfvf->mbox);
	अगर (!nixlf)
		वापस -ENOMEM;

	/* Set RQ/SQ/CQ counts */
	nixlf->rq_cnt = pfvf->hw.rx_queues;
	nixlf->sq_cnt = pfvf->hw.tx_queues;
	nixlf->cq_cnt = pfvf->qset.cq_cnt;
	nixlf->rss_sz = MAX_RSS_INसूची_TBL_SIZE;
	nixlf->rss_grps = MAX_RSS_GROUPS;
	nixlf->xqe_sz = NIX_XQESZ_W16;
	/* We करोn't know असलolute NPA LF idx attached.
	 * AF will replace 'RVU_DEFAULT_PF_FUNC' with
	 * NPA LF attached to this RVU PF/VF.
	 */
	nixlf->npa_func = RVU_DEFAULT_PF_FUNC;
	/* Disable alignment pad, enable L2 length check,
	 * enable L4 TCP/UDP checksum verअगरication.
	 */
	nixlf->rx_cfg = BIT_ULL(33) | BIT_ULL(35) | BIT_ULL(37);

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err)
		वापस err;

	rsp = (काष्ठा nix_lf_alloc_rsp *)otx2_mbox_get_rsp(&pfvf->mbox.mbox, 0,
							   &nixlf->hdr);
	अगर (IS_ERR(rsp))
		वापस PTR_ERR(rsp);

	अगर (rsp->qपूर्णांकs < 1)
		वापस -ENXIO;

	वापस rsp->hdr.rc;
पूर्ण

व्योम otx2_sq_मुक्त_sqbs(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_qset *qset = &pfvf->qset;
	काष्ठा otx2_hw *hw = &pfvf->hw;
	काष्ठा otx2_snd_queue *sq;
	पूर्णांक sqb, qidx;
	u64 iova, pa;

	क्रम (qidx = 0; qidx < hw->tx_queues; qidx++) अणु
		sq = &qset->sq[qidx];
		अगर (!sq->sqb_ptrs)
			जारी;
		क्रम (sqb = 0; sqb < sq->sqb_count; sqb++) अणु
			अगर (!sq->sqb_ptrs[sqb])
				जारी;
			iova = sq->sqb_ptrs[sqb];
			pa = otx2_iova_to_phys(pfvf->iommu_करोमुख्य, iova);
			dma_unmap_page_attrs(pfvf->dev, iova, hw->sqb_size,
					     DMA_FROM_DEVICE,
					     DMA_ATTR_SKIP_CPU_SYNC);
			put_page(virt_to_page(phys_to_virt(pa)));
		पूर्ण
		sq->sqb_count = 0;
	पूर्ण
पूर्ण

व्योम otx2_मुक्त_aura_ptr(काष्ठा otx2_nic *pfvf, पूर्णांक type)
अणु
	पूर्णांक pool_id, pool_start = 0, pool_end = 0, size = 0;
	u64 iova, pa;

	अगर (type == AURA_NIX_SQ) अणु
		pool_start = otx2_get_pool_idx(pfvf, type, 0);
		pool_end =  pool_start + pfvf->hw.sqpool_cnt;
		size = pfvf->hw.sqb_size;
	पूर्ण
	अगर (type == AURA_NIX_RQ) अणु
		pool_start = otx2_get_pool_idx(pfvf, type, 0);
		pool_end = pfvf->hw.rqpool_cnt;
		size = pfvf->rbsize;
	पूर्ण

	/* Free SQB and RQB poपूर्णांकers from the aura pool */
	क्रम (pool_id = pool_start; pool_id < pool_end; pool_id++) अणु
		iova = otx2_aura_allocptr(pfvf, pool_id);
		जबतक (iova) अणु
			अगर (type == AURA_NIX_RQ)
				iova -= OTX2_HEAD_ROOM;

			pa = otx2_iova_to_phys(pfvf->iommu_करोमुख्य, iova);
			dma_unmap_page_attrs(pfvf->dev, iova, size,
					     DMA_FROM_DEVICE,
					     DMA_ATTR_SKIP_CPU_SYNC);
			put_page(virt_to_page(phys_to_virt(pa)));
			iova = otx2_aura_allocptr(pfvf, pool_id);
		पूर्ण
	पूर्ण
पूर्ण

व्योम otx2_aura_pool_मुक्त(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_pool *pool;
	पूर्णांक pool_id;

	अगर (!pfvf->qset.pool)
		वापस;

	क्रम (pool_id = 0; pool_id < pfvf->hw.pool_cnt; pool_id++) अणु
		pool = &pfvf->qset.pool[pool_id];
		qmem_मुक्त(pfvf->dev, pool->stack);
		qmem_मुक्त(pfvf->dev, pool->fc_addr);
	पूर्ण
	devm_kमुक्त(pfvf->dev, pfvf->qset.pool);
	pfvf->qset.pool = शून्य;
पूर्ण

अटल पूर्णांक otx2_aura_init(काष्ठा otx2_nic *pfvf, पूर्णांक aura_id,
			  पूर्णांक pool_id, पूर्णांक numptrs)
अणु
	काष्ठा npa_aq_enq_req *aq;
	काष्ठा otx2_pool *pool;
	पूर्णांक err;

	pool = &pfvf->qset.pool[pool_id];

	/* Allocate memory क्रम HW to update Aura count.
	 * Alloc one cache line, so that it fits all FC_STYPE modes.
	 */
	अगर (!pool->fc_addr) अणु
		err = qmem_alloc(pfvf->dev, &pool->fc_addr, 1, OTX2_ALIGN);
		अगर (err)
			वापस err;
	पूर्ण

	/* Initialize this aura's context via AF */
	aq = otx2_mbox_alloc_msg_npa_aq_enq(&pfvf->mbox);
	अगर (!aq) अणु
		/* Shared mbox memory buffer is full, flush it and retry */
		err = otx2_sync_mbox_msg(&pfvf->mbox);
		अगर (err)
			वापस err;
		aq = otx2_mbox_alloc_msg_npa_aq_enq(&pfvf->mbox);
		अगर (!aq)
			वापस -ENOMEM;
	पूर्ण

	aq->aura_id = aura_id;
	/* Will be filled by AF with correct pool context address */
	aq->aura.pool_addr = pool_id;
	aq->aura.pool_caching = 1;
	aq->aura.shअगरt = ilog2(numptrs) - 8;
	aq->aura.count = numptrs;
	aq->aura.limit = numptrs;
	aq->aura.avg_level = 255;
	aq->aura.ena = 1;
	aq->aura.fc_ena = 1;
	aq->aura.fc_addr = pool->fc_addr->iova;
	aq->aura.fc_hyst_bits = 0; /* Store count on all updates */

	/* Enable backpressure क्रम RQ aura */
	अगर (aura_id < pfvf->hw.rqpool_cnt) अणु
		aq->aura.bp_ena = 0;
		aq->aura.nix0_bpid = pfvf->bpid[0];
		/* Set backpressure level क्रम RQ's Aura */
		aq->aura.bp = RQ_BP_LVL_AURA;
	पूर्ण

	/* Fill AQ info */
	aq->ctype = NPA_AQ_CTYPE_AURA;
	aq->op = NPA_AQ_INSTOP_INIT;

	वापस 0;
पूर्ण

अटल पूर्णांक otx2_pool_init(काष्ठा otx2_nic *pfvf, u16 pool_id,
			  पूर्णांक stack_pages, पूर्णांक numptrs, पूर्णांक buf_size)
अणु
	काष्ठा npa_aq_enq_req *aq;
	काष्ठा otx2_pool *pool;
	पूर्णांक err;

	pool = &pfvf->qset.pool[pool_id];
	/* Alloc memory क्रम stack which is used to store buffer poपूर्णांकers */
	err = qmem_alloc(pfvf->dev, &pool->stack,
			 stack_pages, pfvf->hw.stack_pg_bytes);
	अगर (err)
		वापस err;

	pool->rbsize = buf_size;

	/* Set LMTST addr क्रम NPA batch मुक्त */
	अगर (test_bit(CN10K_LMTST, &pfvf->hw.cap_flag))
		pool->lmt_addr = (__क्रमce u64 *)((u64)pfvf->hw.npa_lmt_base +
						 (pool_id * LMT_LINE_SIZE));

	/* Initialize this pool's context via AF */
	aq = otx2_mbox_alloc_msg_npa_aq_enq(&pfvf->mbox);
	अगर (!aq) अणु
		/* Shared mbox memory buffer is full, flush it and retry */
		err = otx2_sync_mbox_msg(&pfvf->mbox);
		अगर (err) अणु
			qmem_मुक्त(pfvf->dev, pool->stack);
			वापस err;
		पूर्ण
		aq = otx2_mbox_alloc_msg_npa_aq_enq(&pfvf->mbox);
		अगर (!aq) अणु
			qmem_मुक्त(pfvf->dev, pool->stack);
			वापस -ENOMEM;
		पूर्ण
	पूर्ण

	aq->aura_id = pool_id;
	aq->pool.stack_base = pool->stack->iova;
	aq->pool.stack_caching = 1;
	aq->pool.ena = 1;
	aq->pool.buf_size = buf_size / 128;
	aq->pool.stack_max_pages = stack_pages;
	aq->pool.shअगरt = ilog2(numptrs) - 8;
	aq->pool.ptr_start = 0;
	aq->pool.ptr_end = ~0ULL;

	/* Fill AQ info */
	aq->ctype = NPA_AQ_CTYPE_POOL;
	aq->op = NPA_AQ_INSTOP_INIT;

	वापस 0;
पूर्ण

पूर्णांक otx2_sq_aura_pool_init(काष्ठा otx2_nic *pfvf)
अणु
	पूर्णांक qidx, pool_id, stack_pages, num_sqbs;
	काष्ठा otx2_qset *qset = &pfvf->qset;
	काष्ठा otx2_hw *hw = &pfvf->hw;
	काष्ठा otx2_snd_queue *sq;
	काष्ठा otx2_pool *pool;
	dma_addr_t bufptr;
	पूर्णांक err, ptr;

	/* Calculate number of SQBs needed.
	 *
	 * For a 128byte SQE, and 4K size SQB, 31 SQEs will fit in one SQB.
	 * Last SQE is used क्रम poपूर्णांकing to next SQB.
	 */
	num_sqbs = (hw->sqb_size / 128) - 1;
	num_sqbs = (qset->sqe_cnt + num_sqbs) / num_sqbs;

	/* Get no of stack pages needed */
	stack_pages =
		(num_sqbs + hw->stack_pg_ptrs - 1) / hw->stack_pg_ptrs;

	क्रम (qidx = 0; qidx < hw->tx_queues; qidx++) अणु
		pool_id = otx2_get_pool_idx(pfvf, AURA_NIX_SQ, qidx);
		/* Initialize aura context */
		err = otx2_aura_init(pfvf, pool_id, pool_id, num_sqbs);
		अगर (err)
			जाओ fail;

		/* Initialize pool context */
		err = otx2_pool_init(pfvf, pool_id, stack_pages,
				     num_sqbs, hw->sqb_size);
		अगर (err)
			जाओ fail;
	पूर्ण

	/* Flush accumulated messages */
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err)
		जाओ fail;

	/* Allocate poपूर्णांकers and मुक्त them to aura/pool */
	क्रम (qidx = 0; qidx < hw->tx_queues; qidx++) अणु
		pool_id = otx2_get_pool_idx(pfvf, AURA_NIX_SQ, qidx);
		pool = &pfvf->qset.pool[pool_id];

		sq = &qset->sq[qidx];
		sq->sqb_count = 0;
		sq->sqb_ptrs = kसुस्मृति(num_sqbs, माप(*sq->sqb_ptrs), GFP_KERNEL);
		अगर (!sq->sqb_ptrs)
			वापस -ENOMEM;

		क्रम (ptr = 0; ptr < num_sqbs; ptr++) अणु
			अगर (otx2_alloc_rbuf(pfvf, pool, &bufptr))
				वापस -ENOMEM;
			pfvf->hw_ops->aura_मुक्तptr(pfvf, pool_id, bufptr);
			sq->sqb_ptrs[sq->sqb_count++] = (u64)bufptr;
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	otx2_mbox_reset(&pfvf->mbox.mbox, 0);
	otx2_aura_pool_मुक्त(pfvf);
	वापस err;
पूर्ण

पूर्णांक otx2_rq_aura_pool_init(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_hw *hw = &pfvf->hw;
	पूर्णांक stack_pages, pool_id, rq;
	काष्ठा otx2_pool *pool;
	पूर्णांक err, ptr, num_ptrs;
	dma_addr_t bufptr;

	num_ptrs = pfvf->qset.rqe_cnt;

	stack_pages =
		(num_ptrs + hw->stack_pg_ptrs - 1) / hw->stack_pg_ptrs;

	क्रम (rq = 0; rq < hw->rx_queues; rq++) अणु
		pool_id = otx2_get_pool_idx(pfvf, AURA_NIX_RQ, rq);
		/* Initialize aura context */
		err = otx2_aura_init(pfvf, pool_id, pool_id, num_ptrs);
		अगर (err)
			जाओ fail;
	पूर्ण
	क्रम (pool_id = 0; pool_id < hw->rqpool_cnt; pool_id++) अणु
		err = otx2_pool_init(pfvf, pool_id, stack_pages,
				     num_ptrs, pfvf->rbsize);
		अगर (err)
			जाओ fail;
	पूर्ण

	/* Flush accumulated messages */
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err)
		जाओ fail;

	/* Allocate poपूर्णांकers and मुक्त them to aura/pool */
	क्रम (pool_id = 0; pool_id < hw->rqpool_cnt; pool_id++) अणु
		pool = &pfvf->qset.pool[pool_id];
		क्रम (ptr = 0; ptr < num_ptrs; ptr++) अणु
			अगर (otx2_alloc_rbuf(pfvf, pool, &bufptr))
				वापस -ENOMEM;
			pfvf->hw_ops->aura_मुक्तptr(pfvf, pool_id,
						   bufptr + OTX2_HEAD_ROOM);
		पूर्ण
	पूर्ण

	वापस 0;
fail:
	otx2_mbox_reset(&pfvf->mbox.mbox, 0);
	otx2_aura_pool_मुक्त(pfvf);
	वापस err;
पूर्ण

पूर्णांक otx2_config_npa(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_qset *qset = &pfvf->qset;
	काष्ठा npa_lf_alloc_req  *npalf;
	काष्ठा otx2_hw *hw = &pfvf->hw;
	पूर्णांक aura_cnt;

	/* Pool - Stack of मुक्त buffer poपूर्णांकers
	 * Aura - Alloc/मुक्तs poपूर्णांकers from/to pool क्रम NIX DMA.
	 */

	अगर (!hw->pool_cnt)
		वापस -EINVAL;

	qset->pool = devm_kसुस्मृति(pfvf->dev, hw->pool_cnt,
				  माप(काष्ठा otx2_pool), GFP_KERNEL);
	अगर (!qset->pool)
		वापस -ENOMEM;

	/* Get memory to put this msg */
	npalf = otx2_mbox_alloc_msg_npa_lf_alloc(&pfvf->mbox);
	अगर (!npalf)
		वापस -ENOMEM;

	/* Set aura and pool counts */
	npalf->nr_pools = hw->pool_cnt;
	aura_cnt = ilog2(roundup_घात_of_two(hw->pool_cnt));
	npalf->aura_sz = (aura_cnt >= ilog2(128)) ? (aura_cnt - 6) : 1;

	वापस otx2_sync_mbox_msg(&pfvf->mbox);
पूर्ण

पूर्णांक otx2_detach_resources(काष्ठा mbox *mbox)
अणु
	काष्ठा rsrc_detach *detach;

	mutex_lock(&mbox->lock);
	detach = otx2_mbox_alloc_msg_detach_resources(mbox);
	अगर (!detach) अणु
		mutex_unlock(&mbox->lock);
		वापस -ENOMEM;
	पूर्ण

	/* detach all */
	detach->partial = false;

	/* Send detach request to AF */
	otx2_mbox_msg_send(&mbox->mbox, 0);
	mutex_unlock(&mbox->lock);
	वापस 0;
पूर्ण
EXPORT_SYMBOL(otx2_detach_resources);

पूर्णांक otx2_attach_npa_nix(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा rsrc_attach *attach;
	काष्ठा msg_req *msix;
	पूर्णांक err;

	mutex_lock(&pfvf->mbox.lock);
	/* Get memory to put this msg */
	attach = otx2_mbox_alloc_msg_attach_resources(&pfvf->mbox);
	अगर (!attach) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	attach->npalf = true;
	attach->nixlf = true;

	/* Send attach request to AF */
	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस err;
	पूर्ण

	pfvf->nix_blkaddr = BLKADDR_NIX0;

	/* If the platक्रमm has two NIX blocks then LF may be
	 * allocated from NIX1.
	 */
	अगर (otx2_पढ़ो64(pfvf, RVU_PF_BLOCK_ADDRX_DISC(BLKADDR_NIX1)) & 0x1FFULL)
		pfvf->nix_blkaddr = BLKADDR_NIX1;

	/* Get NPA and NIX MSIX vector offsets */
	msix = otx2_mbox_alloc_msg_msix_offset(&pfvf->mbox);
	अगर (!msix) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस -ENOMEM;
	पूर्ण

	err = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (err) अणु
		mutex_unlock(&pfvf->mbox.lock);
		वापस err;
	पूर्ण
	mutex_unlock(&pfvf->mbox.lock);

	अगर (pfvf->hw.npa_msixoff == MSIX_VECTOR_INVALID ||
	    pfvf->hw.nix_msixoff == MSIX_VECTOR_INVALID) अणु
		dev_err(pfvf->dev,
			"RVUPF: Invalid MSIX vector offset for NPA/NIX\n");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण
EXPORT_SYMBOL(otx2_attach_npa_nix);

व्योम otx2_ctx_disable(काष्ठा mbox *mbox, पूर्णांक type, bool npa)
अणु
	काष्ठा hwctx_disable_req *req;

	mutex_lock(&mbox->lock);
	/* Request AQ to disable this context */
	अगर (npa)
		req = otx2_mbox_alloc_msg_npa_hwctx_disable(mbox);
	अन्यथा
		req = otx2_mbox_alloc_msg_nix_hwctx_disable(mbox);

	अगर (!req) अणु
		mutex_unlock(&mbox->lock);
		वापस;
	पूर्ण

	req->ctype = type;

	अगर (otx2_sync_mbox_msg(mbox))
		dev_err(mbox->pfvf->dev, "%s failed to disable context\n",
			__func__);

	mutex_unlock(&mbox->lock);
पूर्ण

पूर्णांक otx2_nix_config_bp(काष्ठा otx2_nic *pfvf, bool enable)
अणु
	काष्ठा nix_bp_cfg_req *req;

	अगर (enable)
		req = otx2_mbox_alloc_msg_nix_bp_enable(&pfvf->mbox);
	अन्यथा
		req = otx2_mbox_alloc_msg_nix_bp_disable(&pfvf->mbox);

	अगर (!req)
		वापस -ENOMEM;

	req->chan_base = 0;
	req->chan_cnt = 1;
	req->bpid_per_chan = 0;

	वापस otx2_sync_mbox_msg(&pfvf->mbox);
पूर्ण

/* Mbox message handlers */
व्योम mbox_handler_cgx_stats(काष्ठा otx2_nic *pfvf,
			    काष्ठा cgx_stats_rsp *rsp)
अणु
	पूर्णांक id;

	क्रम (id = 0; id < CGX_RX_STATS_COUNT; id++)
		pfvf->hw.cgx_rx_stats[id] = rsp->rx_stats[id];
	क्रम (id = 0; id < CGX_TX_STATS_COUNT; id++)
		pfvf->hw.cgx_tx_stats[id] = rsp->tx_stats[id];
पूर्ण

व्योम mbox_handler_cgx_fec_stats(काष्ठा otx2_nic *pfvf,
				काष्ठा cgx_fec_stats_rsp *rsp)
अणु
	pfvf->hw.cgx_fec_corr_blks += rsp->fec_corr_blks;
	pfvf->hw.cgx_fec_uncorr_blks += rsp->fec_uncorr_blks;
पूर्ण

व्योम mbox_handler_nix_txsch_alloc(काष्ठा otx2_nic *pf,
				  काष्ठा nix_txsch_alloc_rsp *rsp)
अणु
	पूर्णांक lvl, schq;

	/* Setup transmit scheduler list */
	क्रम (lvl = 0; lvl < NIX_TXSCH_LVL_CNT; lvl++)
		क्रम (schq = 0; schq < rsp->schq[lvl]; schq++)
			pf->hw.txschq_list[lvl][schq] =
				rsp->schq_list[lvl][schq];
पूर्ण
EXPORT_SYMBOL(mbox_handler_nix_txsch_alloc);

व्योम mbox_handler_npa_lf_alloc(काष्ठा otx2_nic *pfvf,
			       काष्ठा npa_lf_alloc_rsp *rsp)
अणु
	pfvf->hw.stack_pg_ptrs = rsp->stack_pg_ptrs;
	pfvf->hw.stack_pg_bytes = rsp->stack_pg_bytes;
पूर्ण
EXPORT_SYMBOL(mbox_handler_npa_lf_alloc);

व्योम mbox_handler_nix_lf_alloc(काष्ठा otx2_nic *pfvf,
			       काष्ठा nix_lf_alloc_rsp *rsp)
अणु
	pfvf->hw.sqb_size = rsp->sqb_size;
	pfvf->hw.rx_chan_base = rsp->rx_chan_base;
	pfvf->hw.tx_chan_base = rsp->tx_chan_base;
	pfvf->hw.lso_tsov4_idx = rsp->lso_tsov4_idx;
	pfvf->hw.lso_tsov6_idx = rsp->lso_tsov6_idx;
	pfvf->hw.cgx_links = rsp->cgx_links;
	pfvf->hw.lbk_links = rsp->lbk_links;
पूर्ण
EXPORT_SYMBOL(mbox_handler_nix_lf_alloc);

व्योम mbox_handler_msix_offset(काष्ठा otx2_nic *pfvf,
			      काष्ठा msix_offset_rsp *rsp)
अणु
	pfvf->hw.npa_msixoff = rsp->npa_msixoff;
	pfvf->hw.nix_msixoff = rsp->nix_msixoff;
पूर्ण
EXPORT_SYMBOL(mbox_handler_msix_offset);

व्योम mbox_handler_nix_bp_enable(काष्ठा otx2_nic *pfvf,
				काष्ठा nix_bp_cfg_rsp *rsp)
अणु
	पूर्णांक chan, chan_id;

	क्रम (chan = 0; chan < rsp->chan_cnt; chan++) अणु
		chan_id = ((rsp->chan_bpid[chan] >> 10) & 0x7F);
		pfvf->bpid[chan_id] = rsp->chan_bpid[chan] & 0x3FF;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(mbox_handler_nix_bp_enable);

व्योम otx2_मुक्त_cपूर्णांकs(काष्ठा otx2_nic *pfvf, पूर्णांक n)
अणु
	काष्ठा otx2_qset *qset = &pfvf->qset;
	काष्ठा otx2_hw *hw = &pfvf->hw;
	पूर्णांक irq, qidx;

	क्रम (qidx = 0, irq = hw->nix_msixoff + NIX_LF_CINT_VEC_START;
	     qidx < n;
	     qidx++, irq++) अणु
		पूर्णांक vector = pci_irq_vector(pfvf->pdev, irq);

		irq_set_affinity_hपूर्णांक(vector, शून्य);
		मुक्त_cpumask_var(hw->affinity_mask[irq]);
		मुक्त_irq(vector, &qset->napi[qidx]);
	पूर्ण
पूर्ण

व्योम otx2_set_cपूर्णांकs_affinity(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा otx2_hw *hw = &pfvf->hw;
	पूर्णांक vec, cpu, irq, cपूर्णांक;

	vec = hw->nix_msixoff + NIX_LF_CINT_VEC_START;
	cpu = cpumask_first(cpu_online_mask);

	/* CQ पूर्णांकerrupts */
	क्रम (cपूर्णांक = 0; cपूर्णांक < pfvf->hw.cपूर्णांक_cnt; cपूर्णांक++, vec++) अणु
		अगर (!alloc_cpumask_var(&hw->affinity_mask[vec], GFP_KERNEL))
			वापस;

		cpumask_set_cpu(cpu, hw->affinity_mask[vec]);

		irq = pci_irq_vector(pfvf->pdev, vec);
		irq_set_affinity_hपूर्णांक(irq, hw->affinity_mask[vec]);

		cpu = cpumask_next(cpu, cpu_online_mask);
		अगर (unlikely(cpu >= nr_cpu_ids))
			cpu = 0;
	पूर्ण
पूर्ण

u16 otx2_get_max_mtu(काष्ठा otx2_nic *pfvf)
अणु
	काष्ठा nix_hw_info *rsp;
	काष्ठा msg_req *req;
	u16 max_mtu;
	पूर्णांक rc;

	mutex_lock(&pfvf->mbox.lock);

	req = otx2_mbox_alloc_msg_nix_get_hw_info(&pfvf->mbox);
	अगर (!req) अणु
		rc =  -ENOMEM;
		जाओ out;
	पूर्ण

	rc = otx2_sync_mbox_msg(&pfvf->mbox);
	अगर (!rc) अणु
		rsp = (काष्ठा nix_hw_info *)
		       otx2_mbox_get_rsp(&pfvf->mbox.mbox, 0, &req->hdr);

		/* HW counts VLAN insertion bytes (8 क्रम द्विगुन tag)
		 * irrespective of whether SQE is requesting to insert VLAN
		 * in the packet or not. Hence these 8 bytes have to be
		 * discounted from max packet size otherwise HW will throw
		 * SMQ errors
		 */
		max_mtu = rsp->max_mtu - 8 - OTX2_ETH_HLEN;
	पूर्ण

out:
	mutex_unlock(&pfvf->mbox.lock);
	अगर (rc) अणु
		dev_warn(pfvf->dev,
			 "Failed to get MTU from hardware setting default value(1500)\n");
		max_mtu = 1500;
	पूर्ण
	वापस max_mtu;
पूर्ण
EXPORT_SYMBOL(otx2_get_max_mtu);

#घोषणा M(_name, _id, _fn_name, _req_type, _rsp_type)			\
पूर्णांक __weak								\
otx2_mbox_up_handler_ ## _fn_name(काष्ठा otx2_nic *pfvf,		\
				काष्ठा _req_type *req,			\
				काष्ठा _rsp_type *rsp)			\
अणु									\
	/* Nothing to करो here */					\
	वापस 0;							\
पूर्ण									\
EXPORT_SYMBOL(otx2_mbox_up_handler_ ## _fn_name);
MBOX_UP_CGX_MESSAGES
#अघोषित M
