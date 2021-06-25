<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2017 - 2019 Pensanकरो Systems, Inc */

#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ip6_checksum.h>

#समावेश "ionic.h"
#समावेश "ionic_lif.h"
#समावेश "ionic_txrx.h"


अटल अंतरभूत व्योम ionic_txq_post(काष्ठा ionic_queue *q, bool ring_dbell,
				  ionic_desc_cb cb_func, व्योम *cb_arg)
अणु
	DEBUG_STATS_TXQ_POST(q, ring_dbell);

	ionic_q_post(q, ring_dbell, cb_func, cb_arg);
पूर्ण

अटल अंतरभूत व्योम ionic_rxq_post(काष्ठा ionic_queue *q, bool ring_dbell,
				  ionic_desc_cb cb_func, व्योम *cb_arg)
अणु
	ionic_q_post(q, ring_dbell, cb_func, cb_arg);

	DEBUG_STATS_RX_BUFF_CNT(q);
पूर्ण

अटल अंतरभूत काष्ठा netdev_queue *q_to_ndq(काष्ठा ionic_queue *q)
अणु
	वापस netdev_get_tx_queue(q->lअगर->netdev, q->index);
पूर्ण

अटल व्योम ionic_rx_buf_reset(काष्ठा ionic_buf_info *buf_info)
अणु
	buf_info->page = शून्य;
	buf_info->page_offset = 0;
	buf_info->dma_addr = 0;
पूर्ण

अटल पूर्णांक ionic_rx_page_alloc(काष्ठा ionic_queue *q,
			       काष्ठा ionic_buf_info *buf_info)
अणु
	काष्ठा net_device *netdev = q->lअगर->netdev;
	काष्ठा ionic_rx_stats *stats;
	काष्ठा device *dev;

	dev = q->dev;
	stats = q_to_rx_stats(q);

	अगर (unlikely(!buf_info)) अणु
		net_err_ratelimited("%s: %s invalid buf_info in alloc\n",
				    netdev->name, q->name);
		वापस -EINVAL;
	पूर्ण

	buf_info->page = alloc_pages(IONIC_PAGE_GFP_MASK, 0);
	अगर (unlikely(!buf_info->page)) अणु
		net_err_ratelimited("%s: %s page alloc failed\n",
				    netdev->name, q->name);
		stats->alloc_err++;
		वापस -ENOMEM;
	पूर्ण
	buf_info->page_offset = 0;

	buf_info->dma_addr = dma_map_page(dev, buf_info->page, buf_info->page_offset,
					  IONIC_PAGE_SIZE, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, buf_info->dma_addr))) अणु
		__मुक्त_pages(buf_info->page, 0);
		ionic_rx_buf_reset(buf_info);
		net_err_ratelimited("%s: %s dma map failed\n",
				    netdev->name, q->name);
		stats->dma_map_err++;
		वापस -EIO;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ionic_rx_page_मुक्त(काष्ठा ionic_queue *q,
			       काष्ठा ionic_buf_info *buf_info)
अणु
	काष्ठा net_device *netdev = q->lअगर->netdev;
	काष्ठा device *dev = q->dev;

	अगर (unlikely(!buf_info)) अणु
		net_err_ratelimited("%s: %s invalid buf_info in free\n",
				    netdev->name, q->name);
		वापस;
	पूर्ण

	अगर (!buf_info->page)
		वापस;

	dma_unmap_page(dev, buf_info->dma_addr, IONIC_PAGE_SIZE, DMA_FROM_DEVICE);
	__मुक्त_pages(buf_info->page, 0);
	ionic_rx_buf_reset(buf_info);
पूर्ण

अटल bool ionic_rx_buf_recycle(काष्ठा ionic_queue *q,
				 काष्ठा ionic_buf_info *buf_info, u32 used)
अणु
	u32 size;

	/* करोn't re-use pages allocated in low-mem condition */
	अगर (page_is_pfmeदो_स्मृति(buf_info->page))
		वापस false;

	/* करोn't re-use buffers from non-local numa nodes */
	अगर (page_to_nid(buf_info->page) != numa_mem_id())
		वापस false;

	size = ALIGN(used, IONIC_PAGE_SPLIT_SZ);
	buf_info->page_offset += size;
	अगर (buf_info->page_offset >= IONIC_PAGE_SIZE)
		वापस false;

	get_page(buf_info->page);

	वापस true;
पूर्ण

अटल काष्ठा sk_buff *ionic_rx_frags(काष्ठा ionic_queue *q,
				      काष्ठा ionic_desc_info *desc_info,
				      काष्ठा ionic_rxq_comp *comp)
अणु
	काष्ठा net_device *netdev = q->lअगर->netdev;
	काष्ठा ionic_buf_info *buf_info;
	काष्ठा ionic_rx_stats *stats;
	काष्ठा device *dev = q->dev;
	काष्ठा sk_buff *skb;
	अचिन्हित पूर्णांक i;
	u16 frag_len;
	u16 len;

	stats = q_to_rx_stats(q);

	buf_info = &desc_info->bufs[0];
	len = le16_to_cpu(comp->len);

	prefetch(buf_info->page);

	skb = napi_get_frags(&q_to_qcq(q)->napi);
	अगर (unlikely(!skb)) अणु
		net_warn_ratelimited("%s: SKB alloc failed on %s!\n",
				     netdev->name, q->name);
		stats->alloc_err++;
		वापस शून्य;
	पूर्ण

	i = comp->num_sg_elems + 1;
	करो अणु
		अगर (unlikely(!buf_info->page)) अणु
			dev_kमुक्त_skb(skb);
			वापस शून्य;
		पूर्ण

		frag_len = min_t(u16, len, IONIC_PAGE_SIZE - buf_info->page_offset);
		len -= frag_len;

		dma_sync_single_क्रम_cpu(dev,
					buf_info->dma_addr + buf_info->page_offset,
					frag_len, DMA_FROM_DEVICE);

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				buf_info->page, buf_info->page_offset, frag_len,
				IONIC_PAGE_SIZE);

		अगर (!ionic_rx_buf_recycle(q, buf_info, frag_len)) अणु
			dma_unmap_page(dev, buf_info->dma_addr,
				       IONIC_PAGE_SIZE, DMA_FROM_DEVICE);
			ionic_rx_buf_reset(buf_info);
		पूर्ण

		buf_info++;

		i--;
	पूर्ण जबतक (i > 0);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *ionic_rx_copyअवरोध(काष्ठा ionic_queue *q,
					  काष्ठा ionic_desc_info *desc_info,
					  काष्ठा ionic_rxq_comp *comp)
अणु
	काष्ठा net_device *netdev = q->lअगर->netdev;
	काष्ठा ionic_buf_info *buf_info;
	काष्ठा ionic_rx_stats *stats;
	काष्ठा device *dev = q->dev;
	काष्ठा sk_buff *skb;
	u16 len;

	stats = q_to_rx_stats(q);

	buf_info = &desc_info->bufs[0];
	len = le16_to_cpu(comp->len);

	skb = napi_alloc_skb(&q_to_qcq(q)->napi, len);
	अगर (unlikely(!skb)) अणु
		net_warn_ratelimited("%s: SKB alloc failed on %s!\n",
				     netdev->name, q->name);
		stats->alloc_err++;
		वापस शून्य;
	पूर्ण

	अगर (unlikely(!buf_info->page)) अणु
		dev_kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	dma_sync_single_क्रम_cpu(dev, buf_info->dma_addr + buf_info->page_offset,
				len, DMA_FROM_DEVICE);
	skb_copy_to_linear_data(skb, page_address(buf_info->page) + buf_info->page_offset, len);
	dma_sync_single_क्रम_device(dev, buf_info->dma_addr + buf_info->page_offset,
				   len, DMA_FROM_DEVICE);

	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, q->lअगर->netdev);

	वापस skb;
पूर्ण

अटल व्योम ionic_rx_clean(काष्ठा ionic_queue *q,
			   काष्ठा ionic_desc_info *desc_info,
			   काष्ठा ionic_cq_info *cq_info,
			   व्योम *cb_arg)
अणु
	काष्ठा net_device *netdev = q->lअगर->netdev;
	काष्ठा ionic_qcq *qcq = q_to_qcq(q);
	काष्ठा ionic_rx_stats *stats;
	काष्ठा ionic_rxq_comp *comp;
	काष्ठा sk_buff *skb;

	comp = cq_info->cq_desc + qcq->cq.desc_size - माप(*comp);

	stats = q_to_rx_stats(q);

	अगर (comp->status) अणु
		stats->dropped++;
		वापस;
	पूर्ण

	stats->pkts++;
	stats->bytes += le16_to_cpu(comp->len);

	अगर (le16_to_cpu(comp->len) <= q->lअगर->rx_copyअवरोध)
		skb = ionic_rx_copyअवरोध(q, desc_info, comp);
	अन्यथा
		skb = ionic_rx_frags(q, desc_info, comp);

	अगर (unlikely(!skb)) अणु
		stats->dropped++;
		वापस;
	पूर्ण

	skb_record_rx_queue(skb, q->index);

	अगर (likely(netdev->features & NETIF_F_RXHASH)) अणु
		चयन (comp->pkt_type_color & IONIC_RXQ_COMP_PKT_TYPE_MASK) अणु
		हाल IONIC_PKT_TYPE_IPV4:
		हाल IONIC_PKT_TYPE_IPV6:
			skb_set_hash(skb, le32_to_cpu(comp->rss_hash),
				     PKT_HASH_TYPE_L3);
			अवरोध;
		हाल IONIC_PKT_TYPE_IPV4_TCP:
		हाल IONIC_PKT_TYPE_IPV6_TCP:
		हाल IONIC_PKT_TYPE_IPV4_UDP:
		हाल IONIC_PKT_TYPE_IPV6_UDP:
			skb_set_hash(skb, le32_to_cpu(comp->rss_hash),
				     PKT_HASH_TYPE_L4);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (likely(netdev->features & NETIF_F_RXCSUM)) अणु
		अगर (comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_CALC) अणु
			skb->ip_summed = CHECKSUM_COMPLETE;
			skb->csum = (__क्रमce __wsum)le16_to_cpu(comp->csum);
			stats->csum_complete++;
		पूर्ण
	पूर्ण अन्यथा अणु
		stats->csum_none++;
	पूर्ण

	अगर (unlikely((comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_TCP_BAD) ||
		     (comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_UDP_BAD) ||
		     (comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_IP_BAD)))
		stats->csum_error++;

	अगर (likely(netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    (comp->csum_flags & IONIC_RXQ_COMP_CSUM_F_VLAN)) अणु
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
				       le16_to_cpu(comp->vlan_tci));
		stats->vlan_stripped++;
	पूर्ण

	अगर (unlikely(q->features & IONIC_RXQ_F_HWSTAMP)) अणु
		__le64 *cq_desc_hwstamp;
		u64 hwstamp;

		cq_desc_hwstamp =
			cq_info->cq_desc +
			qcq->cq.desc_size -
			माप(काष्ठा ionic_rxq_comp) -
			IONIC_HWSTAMP_CQ_NEGOFFSET;

		hwstamp = le64_to_cpu(*cq_desc_hwstamp);

		अगर (hwstamp != IONIC_HWSTAMP_INVALID) अणु
			skb_hwtstamps(skb)->hwtstamp = ionic_lअगर_phc_kसमय(q->lअगर, hwstamp);
			stats->hwstamp_valid++;
		पूर्ण अन्यथा अणु
			stats->hwstamp_invalid++;
		पूर्ण
	पूर्ण

	अगर (le16_to_cpu(comp->len) <= q->lअगर->rx_copyअवरोध)
		napi_gro_receive(&qcq->napi, skb);
	अन्यथा
		napi_gro_frags(&qcq->napi);
पूर्ण

bool ionic_rx_service(काष्ठा ionic_cq *cq, काष्ठा ionic_cq_info *cq_info)
अणु
	काष्ठा ionic_queue *q = cq->bound_q;
	काष्ठा ionic_desc_info *desc_info;
	काष्ठा ionic_rxq_comp *comp;

	comp = cq_info->cq_desc + cq->desc_size - माप(*comp);

	अगर (!color_match(comp->pkt_type_color, cq->करोne_color))
		वापस false;

	/* check क्रम empty queue */
	अगर (q->tail_idx == q->head_idx)
		वापस false;

	अगर (q->tail_idx != le16_to_cpu(comp->comp_index))
		वापस false;

	desc_info = &q->info[q->tail_idx];
	q->tail_idx = (q->tail_idx + 1) & (q->num_descs - 1);

	/* clean the related q entry, only one per qc completion */
	ionic_rx_clean(q, desc_info, cq_info, desc_info->cb_arg);

	desc_info->cb = शून्य;
	desc_info->cb_arg = शून्य;

	वापस true;
पूर्ण

व्योम ionic_rx_fill(काष्ठा ionic_queue *q)
अणु
	काष्ठा net_device *netdev = q->lअगर->netdev;
	काष्ठा ionic_desc_info *desc_info;
	काष्ठा ionic_rxq_sg_desc *sg_desc;
	काष्ठा ionic_rxq_sg_elem *sg_elem;
	काष्ठा ionic_buf_info *buf_info;
	काष्ठा ionic_rxq_desc *desc;
	अचिन्हित पूर्णांक reमुख्य_len;
	अचिन्हित पूर्णांक frag_len;
	अचिन्हित पूर्णांक nfrags;
	अचिन्हित पूर्णांक i, j;
	अचिन्हित पूर्णांक len;

	len = netdev->mtu + ETH_HLEN + VLAN_HLEN;

	क्रम (i = ionic_q_space_avail(q); i; i--) अणु
		nfrags = 0;
		reमुख्य_len = len;
		desc_info = &q->info[q->head_idx];
		desc = desc_info->desc;
		buf_info = &desc_info->bufs[0];

		अगर (!buf_info->page) अणु /* alloc a new buffer? */
			अगर (unlikely(ionic_rx_page_alloc(q, buf_info))) अणु
				desc->addr = 0;
				desc->len = 0;
				वापस;
			पूर्ण
		पूर्ण

		/* fill मुख्य descriptor - buf[0] */
		desc->addr = cpu_to_le64(buf_info->dma_addr + buf_info->page_offset);
		frag_len = min_t(u16, len, IONIC_PAGE_SIZE - buf_info->page_offset);
		desc->len = cpu_to_le16(frag_len);
		reमुख्य_len -= frag_len;
		buf_info++;
		nfrags++;

		/* fill sg descriptors - buf[1..n] */
		sg_desc = desc_info->sg_desc;
		क्रम (j = 0; reमुख्य_len > 0 && j < q->max_sg_elems; j++) अणु
			sg_elem = &sg_desc->elems[j];
			अगर (!buf_info->page) अणु /* alloc a new sg buffer? */
				अगर (unlikely(ionic_rx_page_alloc(q, buf_info))) अणु
					sg_elem->addr = 0;
					sg_elem->len = 0;
					वापस;
				पूर्ण
			पूर्ण

			sg_elem->addr = cpu_to_le64(buf_info->dma_addr + buf_info->page_offset);
			frag_len = min_t(u16, reमुख्य_len, IONIC_PAGE_SIZE - buf_info->page_offset);
			sg_elem->len = cpu_to_le16(frag_len);
			reमुख्य_len -= frag_len;
			buf_info++;
			nfrags++;
		पूर्ण

		/* clear end sg element as a sentinel */
		अगर (j < q->max_sg_elems) अणु
			sg_elem = &sg_desc->elems[j];
			स_रखो(sg_elem, 0, माप(*sg_elem));
		पूर्ण

		desc->opcode = (nfrags > 1) ? IONIC_RXQ_DESC_OPCODE_SG :
					      IONIC_RXQ_DESC_OPCODE_SIMPLE;
		desc_info->nbufs = nfrags;

		ionic_rxq_post(q, false, ionic_rx_clean, शून्य);
	पूर्ण

	ionic_dbell_ring(q->lअगर->kern_dbpage, q->hw_type,
			 q->dbval | q->head_idx);
पूर्ण

व्योम ionic_rx_empty(काष्ठा ionic_queue *q)
अणु
	काष्ठा ionic_desc_info *desc_info;
	काष्ठा ionic_buf_info *buf_info;
	अचिन्हित पूर्णांक i, j;

	क्रम (i = 0; i < q->num_descs; i++) अणु
		desc_info = &q->info[i];
		क्रम (j = 0; j < IONIC_RX_MAX_SG_ELEMS + 1; j++) अणु
			buf_info = &desc_info->bufs[j];
			अगर (buf_info->page)
				ionic_rx_page_मुक्त(q, buf_info);
		पूर्ण

		desc_info->nbufs = 0;
		desc_info->cb = शून्य;
		desc_info->cb_arg = शून्य;
	पूर्ण

	q->head_idx = 0;
	q->tail_idx = 0;
पूर्ण

अटल व्योम ionic_dim_update(काष्ठा ionic_qcq *qcq)
अणु
	काष्ठा dim_sample dim_sample;
	काष्ठा ionic_lअगर *lअगर;
	अचिन्हित पूर्णांक qi;

	अगर (!qcq->पूर्णांकr.dim_coal_hw)
		वापस;

	lअगर = qcq->q.lअगर;
	qi = qcq->cq.bound_q->index;

	ionic_पूर्णांकr_coal_init(lअगर->ionic->idev.पूर्णांकr_ctrl,
			     lअगर->rxqcqs[qi]->पूर्णांकr.index,
			     qcq->पूर्णांकr.dim_coal_hw);

	dim_update_sample(qcq->cq.bound_पूर्णांकr->rearm_count,
			  lअगर->txqstats[qi].pkts,
			  lअगर->txqstats[qi].bytes,
			  &dim_sample);

	net_dim(&qcq->dim, dim_sample);
पूर्ण

पूर्णांक ionic_tx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ionic_qcq *qcq = napi_to_qcq(napi);
	काष्ठा ionic_cq *cq = napi_to_cq(napi);
	काष्ठा ionic_dev *idev;
	काष्ठा ionic_lअगर *lअगर;
	u32 work_करोne = 0;
	u32 flags = 0;

	lअगर = cq->bound_q->lअगर;
	idev = &lअगर->ionic->idev;

	work_करोne = ionic_cq_service(cq, budget,
				     ionic_tx_service, शून्य, शून्य);

	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		ionic_dim_update(qcq);
		flags |= IONIC_INTR_CRED_UNMASK;
		cq->bound_पूर्णांकr->rearm_count++;
	पूर्ण

	अगर (work_करोne || flags) अणु
		flags |= IONIC_INTR_CRED_RESET_COALESCE;
		ionic_पूर्णांकr_credits(idev->पूर्णांकr_ctrl,
				   cq->bound_पूर्णांकr->index,
				   work_करोne, flags);
	पूर्ण

	DEBUG_STATS_NAPI_POLL(qcq, work_करोne);

	वापस work_करोne;
पूर्ण

पूर्णांक ionic_rx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ionic_qcq *qcq = napi_to_qcq(napi);
	काष्ठा ionic_cq *cq = napi_to_cq(napi);
	काष्ठा ionic_dev *idev;
	काष्ठा ionic_lअगर *lअगर;
	u16 rx_fill_threshold;
	u32 work_करोne = 0;
	u32 flags = 0;

	lअगर = cq->bound_q->lअगर;
	idev = &lअगर->ionic->idev;

	work_करोne = ionic_cq_service(cq, budget,
				     ionic_rx_service, शून्य, शून्य);

	rx_fill_threshold = min_t(u16, IONIC_RX_FILL_THRESHOLD,
				  cq->num_descs / IONIC_RX_FILL_DIV);
	अगर (work_करोne && ionic_q_space_avail(cq->bound_q) >= rx_fill_threshold)
		ionic_rx_fill(cq->bound_q);

	अगर (work_करोne < budget && napi_complete_करोne(napi, work_करोne)) अणु
		ionic_dim_update(qcq);
		flags |= IONIC_INTR_CRED_UNMASK;
		cq->bound_पूर्णांकr->rearm_count++;
	पूर्ण

	अगर (work_करोne || flags) अणु
		flags |= IONIC_INTR_CRED_RESET_COALESCE;
		ionic_पूर्णांकr_credits(idev->पूर्णांकr_ctrl,
				   cq->bound_पूर्णांकr->index,
				   work_करोne, flags);
	पूर्ण

	DEBUG_STATS_NAPI_POLL(qcq, work_करोne);

	वापस work_करोne;
पूर्ण

पूर्णांक ionic_txrx_napi(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ionic_qcq *qcq = napi_to_qcq(napi);
	काष्ठा ionic_cq *rxcq = napi_to_cq(napi);
	अचिन्हित पूर्णांक qi = rxcq->bound_q->index;
	काष्ठा ionic_dev *idev;
	काष्ठा ionic_lअगर *lअगर;
	काष्ठा ionic_cq *txcq;
	u16 rx_fill_threshold;
	u32 rx_work_करोne = 0;
	u32 tx_work_करोne = 0;
	u32 flags = 0;

	lअगर = rxcq->bound_q->lअगर;
	idev = &lअगर->ionic->idev;
	txcq = &lअगर->txqcqs[qi]->cq;

	tx_work_करोne = ionic_cq_service(txcq, IONIC_TX_BUDGET_DEFAULT,
					ionic_tx_service, शून्य, शून्य);

	rx_work_करोne = ionic_cq_service(rxcq, budget,
					ionic_rx_service, शून्य, शून्य);

	rx_fill_threshold = min_t(u16, IONIC_RX_FILL_THRESHOLD,
				  rxcq->num_descs / IONIC_RX_FILL_DIV);
	अगर (rx_work_करोne && ionic_q_space_avail(rxcq->bound_q) >= rx_fill_threshold)
		ionic_rx_fill(rxcq->bound_q);

	अगर (rx_work_करोne < budget && napi_complete_करोne(napi, rx_work_करोne)) अणु
		ionic_dim_update(qcq);
		flags |= IONIC_INTR_CRED_UNMASK;
		rxcq->bound_पूर्णांकr->rearm_count++;
	पूर्ण

	अगर (rx_work_करोne || flags) अणु
		flags |= IONIC_INTR_CRED_RESET_COALESCE;
		ionic_पूर्णांकr_credits(idev->पूर्णांकr_ctrl, rxcq->bound_पूर्णांकr->index,
				   tx_work_करोne + rx_work_करोne, flags);
	पूर्ण

	DEBUG_STATS_NAPI_POLL(qcq, rx_work_करोne);
	DEBUG_STATS_NAPI_POLL(qcq, tx_work_करोne);

	वापस rx_work_करोne;
पूर्ण

अटल dma_addr_t ionic_tx_map_single(काष्ठा ionic_queue *q,
				      व्योम *data, माप_प्रकार len)
अणु
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	काष्ठा device *dev = q->dev;
	dma_addr_t dma_addr;

	dma_addr = dma_map_single(dev, data, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma_addr)) अणु
		net_warn_ratelimited("%s: DMA single map failed on %s!\n",
				     q->lअगर->netdev->name, q->name);
		stats->dma_map_err++;
		वापस 0;
	पूर्ण
	वापस dma_addr;
पूर्ण

अटल dma_addr_t ionic_tx_map_frag(काष्ठा ionic_queue *q,
				    स्थिर skb_frag_t *frag,
				    माप_प्रकार offset, माप_प्रकार len)
अणु
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	काष्ठा device *dev = q->dev;
	dma_addr_t dma_addr;

	dma_addr = skb_frag_dma_map(dev, frag, offset, len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(dev, dma_addr)) अणु
		net_warn_ratelimited("%s: DMA frag map failed on %s!\n",
				     q->lअगर->netdev->name, q->name);
		stats->dma_map_err++;
	पूर्ण
	वापस dma_addr;
पूर्ण

अटल पूर्णांक ionic_tx_map_skb(काष्ठा ionic_queue *q, काष्ठा sk_buff *skb,
			    काष्ठा ionic_desc_info *desc_info)
अणु
	काष्ठा ionic_buf_info *buf_info = desc_info->bufs;
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	काष्ठा device *dev = q->dev;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक nfrags;
	skb_frag_t *frag;
	पूर्णांक frag_idx;

	dma_addr = ionic_tx_map_single(q, skb->data, skb_headlen(skb));
	अगर (dma_mapping_error(dev, dma_addr)) अणु
		stats->dma_map_err++;
		वापस -EIO;
	पूर्ण
	buf_info->dma_addr = dma_addr;
	buf_info->len = skb_headlen(skb);
	buf_info++;

	frag = skb_shinfo(skb)->frags;
	nfrags = skb_shinfo(skb)->nr_frags;
	क्रम (frag_idx = 0; frag_idx < nfrags; frag_idx++, frag++) अणु
		dma_addr = ionic_tx_map_frag(q, frag, 0, skb_frag_size(frag));
		अगर (dma_mapping_error(dev, dma_addr)) अणु
			stats->dma_map_err++;
			जाओ dma_fail;
		पूर्ण
		buf_info->dma_addr = dma_addr;
		buf_info->len = skb_frag_size(frag);
		buf_info++;
	पूर्ण

	desc_info->nbufs = 1 + nfrags;

	वापस 0;

dma_fail:
	/* unwind the frag mappings and the head mapping */
	जबतक (frag_idx > 0) अणु
		frag_idx--;
		buf_info--;
		dma_unmap_page(dev, buf_info->dma_addr,
			       buf_info->len, DMA_TO_DEVICE);
	पूर्ण
	dma_unmap_single(dev, buf_info->dma_addr, buf_info->len, DMA_TO_DEVICE);
	वापस -EIO;
पूर्ण

अटल व्योम ionic_tx_clean(काष्ठा ionic_queue *q,
			   काष्ठा ionic_desc_info *desc_info,
			   काष्ठा ionic_cq_info *cq_info,
			   व्योम *cb_arg)
अणु
	काष्ठा ionic_buf_info *buf_info = desc_info->bufs;
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	काष्ठा ionic_qcq *qcq = q_to_qcq(q);
	काष्ठा sk_buff *skb = cb_arg;
	काष्ठा device *dev = q->dev;
	अचिन्हित पूर्णांक i;
	u16 qi;

	अगर (desc_info->nbufs) अणु
		dma_unmap_single(dev, (dma_addr_t)buf_info->dma_addr,
				 buf_info->len, DMA_TO_DEVICE);
		buf_info++;
		क्रम (i = 1; i < desc_info->nbufs; i++, buf_info++)
			dma_unmap_page(dev, (dma_addr_t)buf_info->dma_addr,
				       buf_info->len, DMA_TO_DEVICE);
	पूर्ण

	अगर (!skb)
		वापस;

	qi = skb_get_queue_mapping(skb);

	अगर (unlikely(q->features & IONIC_TXQ_F_HWSTAMP)) अणु
		अगर (cq_info) अणु
			काष्ठा skb_shared_hwtstamps hwts = अणुपूर्ण;
			__le64 *cq_desc_hwstamp;
			u64 hwstamp;

			cq_desc_hwstamp =
				cq_info->cq_desc +
				qcq->cq.desc_size -
				माप(काष्ठा ionic_txq_comp) -
				IONIC_HWSTAMP_CQ_NEGOFFSET;

			hwstamp = le64_to_cpu(*cq_desc_hwstamp);

			अगर (hwstamp != IONIC_HWSTAMP_INVALID) अणु
				hwts.hwtstamp = ionic_lअगर_phc_kसमय(q->lअगर, hwstamp);

				skb_shinfo(skb)->tx_flags |= SKBTX_IN_PROGRESS;
				skb_tstamp_tx(skb, &hwts);

				stats->hwstamp_valid++;
			पूर्ण अन्यथा अणु
				stats->hwstamp_invalid++;
			पूर्ण
		पूर्ण

	पूर्ण अन्यथा अगर (unlikely(__netअगर_subqueue_stopped(q->lअगर->netdev, qi))) अणु
		netअगर_wake_subqueue(q->lअगर->netdev, qi);
		q->wake++;
	पूर्ण

	desc_info->bytes = skb->len;
	stats->clean++;

	dev_consume_skb_any(skb);
पूर्ण

bool ionic_tx_service(काष्ठा ionic_cq *cq, काष्ठा ionic_cq_info *cq_info)
अणु
	काष्ठा ionic_queue *q = cq->bound_q;
	काष्ठा ionic_desc_info *desc_info;
	काष्ठा ionic_txq_comp *comp;
	पूर्णांक bytes = 0;
	पूर्णांक pkts = 0;
	u16 index;

	comp = cq_info->cq_desc + cq->desc_size - माप(*comp);

	अगर (!color_match(comp->color, cq->करोne_color))
		वापस false;

	/* clean the related q entries, there could be
	 * several q entries completed क्रम each cq completion
	 */
	करो अणु
		desc_info = &q->info[q->tail_idx];
		desc_info->bytes = 0;
		index = q->tail_idx;
		q->tail_idx = (q->tail_idx + 1) & (q->num_descs - 1);
		ionic_tx_clean(q, desc_info, cq_info, desc_info->cb_arg);
		अगर (desc_info->cb_arg) अणु
			pkts++;
			bytes += desc_info->bytes;
		पूर्ण
		desc_info->cb = शून्य;
		desc_info->cb_arg = शून्य;
	पूर्ण जबतक (index != le16_to_cpu(comp->comp_index));

	अगर (pkts && bytes && !unlikely(q->features & IONIC_TXQ_F_HWSTAMP))
		netdev_tx_completed_queue(q_to_ndq(q), pkts, bytes);

	वापस true;
पूर्ण

व्योम ionic_tx_flush(काष्ठा ionic_cq *cq)
अणु
	काष्ठा ionic_dev *idev = &cq->lअगर->ionic->idev;
	u32 work_करोne;

	work_करोne = ionic_cq_service(cq, cq->num_descs,
				     ionic_tx_service, शून्य, शून्य);
	अगर (work_करोne)
		ionic_पूर्णांकr_credits(idev->पूर्णांकr_ctrl, cq->bound_पूर्णांकr->index,
				   work_करोne, IONIC_INTR_CRED_RESET_COALESCE);
पूर्ण

व्योम ionic_tx_empty(काष्ठा ionic_queue *q)
अणु
	काष्ठा ionic_desc_info *desc_info;
	पूर्णांक bytes = 0;
	पूर्णांक pkts = 0;

	/* walk the not completed tx entries, अगर any */
	जबतक (q->head_idx != q->tail_idx) अणु
		desc_info = &q->info[q->tail_idx];
		desc_info->bytes = 0;
		q->tail_idx = (q->tail_idx + 1) & (q->num_descs - 1);
		ionic_tx_clean(q, desc_info, शून्य, desc_info->cb_arg);
		अगर (desc_info->cb_arg) अणु
			pkts++;
			bytes += desc_info->bytes;
		पूर्ण
		desc_info->cb = शून्य;
		desc_info->cb_arg = शून्य;
	पूर्ण

	अगर (pkts && bytes && !unlikely(q->features & IONIC_TXQ_F_HWSTAMP))
		netdev_tx_completed_queue(q_to_ndq(q), pkts, bytes);
पूर्ण

अटल पूर्णांक ionic_tx_tcp_inner_pseuकरो_csum(काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = skb_cow_head(skb, 0);
	अगर (err)
		वापस err;

	अगर (skb->protocol == cpu_to_be16(ETH_P_IP)) अणु
		inner_ip_hdr(skb)->check = 0;
		inner_tcp_hdr(skb)->check =
			~csum_tcpudp_magic(inner_ip_hdr(skb)->saddr,
					   inner_ip_hdr(skb)->daddr,
					   0, IPPROTO_TCP, 0);
	पूर्ण अन्यथा अगर (skb->protocol == cpu_to_be16(ETH_P_IPV6)) अणु
		inner_tcp_hdr(skb)->check =
			~csum_ipv6_magic(&inner_ipv6_hdr(skb)->saddr,
					 &inner_ipv6_hdr(skb)->daddr,
					 0, IPPROTO_TCP, 0);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_tx_tcp_pseuकरो_csum(काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = skb_cow_head(skb, 0);
	अगर (err)
		वापस err;

	अगर (skb->protocol == cpu_to_be16(ETH_P_IP)) अणु
		ip_hdr(skb)->check = 0;
		tcp_hdr(skb)->check =
			~csum_tcpudp_magic(ip_hdr(skb)->saddr,
					   ip_hdr(skb)->daddr,
					   0, IPPROTO_TCP, 0);
	पूर्ण अन्यथा अगर (skb->protocol == cpu_to_be16(ETH_P_IPV6)) अणु
		tcp_v6_gso_csum_prep(skb);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ionic_tx_tso_post(काष्ठा ionic_queue *q, काष्ठा ionic_txq_desc *desc,
			      काष्ठा sk_buff *skb,
			      dma_addr_t addr, u8 nsge, u16 len,
			      अचिन्हित पूर्णांक hdrlen, अचिन्हित पूर्णांक mss,
			      bool outer_csum,
			      u16 vlan_tci, bool has_vlan,
			      bool start, bool करोne)
अणु
	u8 flags = 0;
	u64 cmd;

	flags |= has_vlan ? IONIC_TXQ_DESC_FLAG_VLAN : 0;
	flags |= outer_csum ? IONIC_TXQ_DESC_FLAG_ENCAP : 0;
	flags |= start ? IONIC_TXQ_DESC_FLAG_TSO_SOT : 0;
	flags |= करोne ? IONIC_TXQ_DESC_FLAG_TSO_EOT : 0;

	cmd = encode_txq_desc_cmd(IONIC_TXQ_DESC_OPCODE_TSO, flags, nsge, addr);
	desc->cmd = cpu_to_le64(cmd);
	desc->len = cpu_to_le16(len);
	desc->vlan_tci = cpu_to_le16(vlan_tci);
	desc->hdr_len = cpu_to_le16(hdrlen);
	desc->mss = cpu_to_le16(mss);

	अगर (start) अणु
		skb_tx_बारtamp(skb);
		अगर (!unlikely(q->features & IONIC_TXQ_F_HWSTAMP))
			netdev_tx_sent_queue(q_to_ndq(q), skb->len);
		ionic_txq_post(q, false, ionic_tx_clean, skb);
	पूर्ण अन्यथा अणु
		ionic_txq_post(q, करोne, शून्य, शून्य);
	पूर्ण
पूर्ण

अटल पूर्णांक ionic_tx_tso(काष्ठा ionic_queue *q, काष्ठा sk_buff *skb)
अणु
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	काष्ठा ionic_desc_info *desc_info;
	काष्ठा ionic_buf_info *buf_info;
	काष्ठा ionic_txq_sg_elem *elem;
	काष्ठा ionic_txq_desc *desc;
	अचिन्हित पूर्णांक chunk_len;
	अचिन्हित पूर्णांक frag_rem;
	अचिन्हित पूर्णांक tso_rem;
	अचिन्हित पूर्णांक seg_rem;
	dma_addr_t desc_addr;
	dma_addr_t frag_addr;
	अचिन्हित पूर्णांक hdrlen;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक mss;
	bool start, करोne;
	bool outer_csum;
	bool has_vlan;
	u16 desc_len;
	u8 desc_nsge;
	u16 vlan_tci;
	bool encap;
	पूर्णांक err;

	desc_info = &q->info[q->head_idx];
	buf_info = desc_info->bufs;

	अगर (unlikely(ionic_tx_map_skb(q, skb, desc_info)))
		वापस -EIO;

	len = skb->len;
	mss = skb_shinfo(skb)->gso_size;
	outer_csum = (skb_shinfo(skb)->gso_type & SKB_GSO_GRE_CSUM) ||
		     (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM);
	has_vlan = !!skb_vlan_tag_present(skb);
	vlan_tci = skb_vlan_tag_get(skb);
	encap = skb->encapsulation;

	/* Preload inner-most TCP csum field with IP pseuकरो hdr
	 * calculated with IP length set to zero.  HW will later
	 * add in length to each TCP segment resulting from the TSO.
	 */

	अगर (encap)
		err = ionic_tx_tcp_inner_pseuकरो_csum(skb);
	अन्यथा
		err = ionic_tx_tcp_pseuकरो_csum(skb);
	अगर (err)
		वापस err;

	अगर (encap)
		hdrlen = skb_inner_transport_header(skb) - skb->data +
			 inner_tcp_hdrlen(skb);
	अन्यथा
		hdrlen = skb_transport_offset(skb) + tcp_hdrlen(skb);

	tso_rem = len;
	seg_rem = min(tso_rem, hdrlen + mss);

	frag_addr = 0;
	frag_rem = 0;

	start = true;

	जबतक (tso_rem > 0) अणु
		desc = शून्य;
		elem = शून्य;
		desc_addr = 0;
		desc_len = 0;
		desc_nsge = 0;
		/* use fragments until we have enough to post a single descriptor */
		जबतक (seg_rem > 0) अणु
			/* अगर the fragment is exhausted then move to the next one */
			अगर (frag_rem == 0) अणु
				/* grab the next fragment */
				frag_addr = buf_info->dma_addr;
				frag_rem = buf_info->len;
				buf_info++;
			पूर्ण
			chunk_len = min(frag_rem, seg_rem);
			अगर (!desc) अणु
				/* fill मुख्य descriptor */
				desc = desc_info->txq_desc;
				elem = desc_info->txq_sg_desc->elems;
				desc_addr = frag_addr;
				desc_len = chunk_len;
			पूर्ण अन्यथा अणु
				/* fill sg descriptor */
				elem->addr = cpu_to_le64(frag_addr);
				elem->len = cpu_to_le16(chunk_len);
				elem++;
				desc_nsge++;
			पूर्ण
			frag_addr += chunk_len;
			frag_rem -= chunk_len;
			tso_rem -= chunk_len;
			seg_rem -= chunk_len;
		पूर्ण
		seg_rem = min(tso_rem, mss);
		करोne = (tso_rem == 0);
		/* post descriptor */
		ionic_tx_tso_post(q, desc, skb,
				  desc_addr, desc_nsge, desc_len,
				  hdrlen, mss, outer_csum, vlan_tci, has_vlan,
				  start, करोne);
		start = false;
		/* Buffer inक्रमmation is stored with the first tso descriptor */
		desc_info = &q->info[q->head_idx];
		desc_info->nbufs = 0;
	पूर्ण

	stats->pkts += DIV_ROUND_UP(len - hdrlen, mss);
	stats->bytes += len;
	stats->tso++;
	stats->tso_bytes = len;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_tx_calc_csum(काष्ठा ionic_queue *q, काष्ठा sk_buff *skb,
			      काष्ठा ionic_desc_info *desc_info)
अणु
	काष्ठा ionic_txq_desc *desc = desc_info->txq_desc;
	काष्ठा ionic_buf_info *buf_info = desc_info->bufs;
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	bool has_vlan;
	u8 flags = 0;
	bool encap;
	u64 cmd;

	has_vlan = !!skb_vlan_tag_present(skb);
	encap = skb->encapsulation;

	flags |= has_vlan ? IONIC_TXQ_DESC_FLAG_VLAN : 0;
	flags |= encap ? IONIC_TXQ_DESC_FLAG_ENCAP : 0;

	cmd = encode_txq_desc_cmd(IONIC_TXQ_DESC_OPCODE_CSUM_PARTIAL,
				  flags, skb_shinfo(skb)->nr_frags,
				  buf_info->dma_addr);
	desc->cmd = cpu_to_le64(cmd);
	desc->len = cpu_to_le16(buf_info->len);
	अगर (has_vlan) अणु
		desc->vlan_tci = cpu_to_le16(skb_vlan_tag_get(skb));
		stats->vlan_inserted++;
	पूर्ण अन्यथा अणु
		desc->vlan_tci = 0;
	पूर्ण
	desc->csum_start = cpu_to_le16(skb_checksum_start_offset(skb));
	desc->csum_offset = cpu_to_le16(skb->csum_offset);

	अगर (skb_csum_is_sctp(skb))
		stats->crc32_csum++;
	अन्यथा
		stats->csum++;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_tx_calc_no_csum(काष्ठा ionic_queue *q, काष्ठा sk_buff *skb,
				 काष्ठा ionic_desc_info *desc_info)
अणु
	काष्ठा ionic_txq_desc *desc = desc_info->txq_desc;
	काष्ठा ionic_buf_info *buf_info = desc_info->bufs;
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	bool has_vlan;
	u8 flags = 0;
	bool encap;
	u64 cmd;

	has_vlan = !!skb_vlan_tag_present(skb);
	encap = skb->encapsulation;

	flags |= has_vlan ? IONIC_TXQ_DESC_FLAG_VLAN : 0;
	flags |= encap ? IONIC_TXQ_DESC_FLAG_ENCAP : 0;

	cmd = encode_txq_desc_cmd(IONIC_TXQ_DESC_OPCODE_CSUM_NONE,
				  flags, skb_shinfo(skb)->nr_frags,
				  buf_info->dma_addr);
	desc->cmd = cpu_to_le64(cmd);
	desc->len = cpu_to_le16(buf_info->len);
	अगर (has_vlan) अणु
		desc->vlan_tci = cpu_to_le16(skb_vlan_tag_get(skb));
		stats->vlan_inserted++;
	पूर्ण अन्यथा अणु
		desc->vlan_tci = 0;
	पूर्ण
	desc->csum_start = 0;
	desc->csum_offset = 0;

	stats->csum_none++;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_tx_skb_frags(काष्ठा ionic_queue *q, काष्ठा sk_buff *skb,
			      काष्ठा ionic_desc_info *desc_info)
अणु
	काष्ठा ionic_txq_sg_desc *sg_desc = desc_info->txq_sg_desc;
	काष्ठा ionic_buf_info *buf_info = &desc_info->bufs[1];
	काष्ठा ionic_txq_sg_elem *elem = sg_desc->elems;
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++, buf_info++, elem++) अणु
		elem->addr = cpu_to_le64(buf_info->dma_addr);
		elem->len = cpu_to_le16(buf_info->len);
	पूर्ण

	stats->frags += skb_shinfo(skb)->nr_frags;

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_tx(काष्ठा ionic_queue *q, काष्ठा sk_buff *skb)
अणु
	काष्ठा ionic_desc_info *desc_info = &q->info[q->head_idx];
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	पूर्णांक err;

	अगर (unlikely(ionic_tx_map_skb(q, skb, desc_info)))
		वापस -EIO;

	/* set up the initial descriptor */
	अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		err = ionic_tx_calc_csum(q, skb, desc_info);
	अन्यथा
		err = ionic_tx_calc_no_csum(q, skb, desc_info);
	अगर (err)
		वापस err;

	/* add frags */
	err = ionic_tx_skb_frags(q, skb, desc_info);
	अगर (err)
		वापस err;

	skb_tx_बारtamp(skb);
	stats->pkts++;
	stats->bytes += skb->len;

	अगर (!unlikely(q->features & IONIC_TXQ_F_HWSTAMP))
		netdev_tx_sent_queue(q_to_ndq(q), skb->len);
	ionic_txq_post(q, !netdev_xmit_more(), ionic_tx_clean, skb);

	वापस 0;
पूर्ण

अटल पूर्णांक ionic_tx_descs_needed(काष्ठा ionic_queue *q, काष्ठा sk_buff *skb)
अणु
	काष्ठा ionic_tx_stats *stats = q_to_tx_stats(q);
	पूर्णांक ndescs;
	पूर्णांक err;

	/* Each desc is mss दीर्घ max, so a descriptor क्रम each gso_seg */
	अगर (skb_is_gso(skb))
		ndescs = skb_shinfo(skb)->gso_segs;
	अन्यथा
		ndescs = 1;

	/* If non-TSO, just need 1 desc and nr_frags sg elems */
	अगर (skb_shinfo(skb)->nr_frags <= q->max_sg_elems)
		वापस ndescs;

	/* Too many frags, so linearize */
	err = skb_linearize(skb);
	अगर (err)
		वापस err;

	stats->linearize++;

	वापस ndescs;
पूर्ण

अटल पूर्णांक ionic_maybe_stop_tx(काष्ठा ionic_queue *q, पूर्णांक ndescs)
अणु
	पूर्णांक stopped = 0;

	अगर (unlikely(!ionic_q_has_space(q, ndescs))) अणु
		netअगर_stop_subqueue(q->lअगर->netdev, q->index);
		q->stop++;
		stopped = 1;

		/* Might race with ionic_tx_clean, check again */
		smp_rmb();
		अगर (ionic_q_has_space(q, ndescs)) अणु
			netअगर_wake_subqueue(q->lअगर->netdev, q->index);
			stopped = 0;
		पूर्ण
	पूर्ण

	वापस stopped;
पूर्ण

अटल netdev_tx_t ionic_start_hwstamp_xmit(काष्ठा sk_buff *skb,
					    काष्ठा net_device *netdev)
अणु
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_queue *q = &lअगर->hwstamp_txq->q;
	पूर्णांक err, ndescs;

	/* Does not stop/start txq, because we post to a separate tx queue
	 * क्रम बारtamping, and अगर a packet can't be posted immediately to
	 * the बारtamping queue, it is dropped.
	 */

	ndescs = ionic_tx_descs_needed(q, skb);
	अगर (unlikely(ndescs < 0))
		जाओ err_out_drop;

	अगर (unlikely(!ionic_q_has_space(q, ndescs)))
		जाओ err_out_drop;

	skb_shinfo(skb)->tx_flags |= SKBTX_HW_TSTAMP;
	अगर (skb_is_gso(skb))
		err = ionic_tx_tso(q, skb);
	अन्यथा
		err = ionic_tx(q, skb);

	अगर (err)
		जाओ err_out_drop;

	वापस NETDEV_TX_OK;

err_out_drop:
	q->drop++;
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण

netdev_tx_t ionic_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	u16 queue_index = skb_get_queue_mapping(skb);
	काष्ठा ionic_lअगर *lअगर = netdev_priv(netdev);
	काष्ठा ionic_queue *q;
	पूर्णांक ndescs;
	पूर्णांक err;

	अगर (unlikely(!test_bit(IONIC_LIF_F_UP, lअगर->state))) अणु
		dev_kमुक्त_skb(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		अगर (lअगर->hwstamp_txq && lअगर->phc->ts_config_tx_mode)
			वापस ionic_start_hwstamp_xmit(skb, netdev);

	अगर (unlikely(queue_index >= lअगर->nxqs))
		queue_index = 0;
	q = &lअगर->txqcqs[queue_index]->q;

	ndescs = ionic_tx_descs_needed(q, skb);
	अगर (ndescs < 0)
		जाओ err_out_drop;

	अगर (unlikely(ionic_maybe_stop_tx(q, ndescs)))
		वापस NETDEV_TX_BUSY;

	अगर (skb_is_gso(skb))
		err = ionic_tx_tso(q, skb);
	अन्यथा
		err = ionic_tx(q, skb);

	अगर (err)
		जाओ err_out_drop;

	/* Stop the queue अगर there aren't descriptors क्रम the next packet.
	 * Since our SG lists per descriptor take care of most of the possible
	 * fragmentation, we करोn't need to have many descriptors available.
	 */
	ionic_maybe_stop_tx(q, 4);

	वापस NETDEV_TX_OK;

err_out_drop:
	q->stop++;
	q->drop++;
	dev_kमुक्त_skb(skb);
	वापस NETDEV_TX_OK;
पूर्ण
