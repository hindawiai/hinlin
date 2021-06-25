<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Linux network driver क्रम QLogic BR-series Converged Network Adapter.
 */
/*
 * Copyright (c) 2005-2014 Brocade Communications Systems, Inc.
 * Copyright (c) 2014-2015 QLogic Corporation
 * All rights reserved
 * www.qlogic.com
 */
#समावेश <linux/bitops.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/in.h>
#समावेश <linux/ethtool.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ip.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/module.h>

#समावेश "bnad.h"
#समावेश "bna.h"
#समावेश "cna.h"

अटल DEFINE_MUTEX(bnad_fwimg_mutex);

/*
 * Module params
 */
अटल uपूर्णांक bnad_msix_disable;
module_param(bnad_msix_disable, uपूर्णांक, 0444);
MODULE_PARM_DESC(bnad_msix_disable, "Disable MSIX mode");

अटल uपूर्णांक bnad_ioc_स्वतः_recover = 1;
module_param(bnad_ioc_स्वतः_recover, uपूर्णांक, 0444);
MODULE_PARM_DESC(bnad_ioc_स्वतः_recover, "Enable / Disable auto recovery");

अटल uपूर्णांक bna_debugfs_enable = 1;
module_param(bna_debugfs_enable, uपूर्णांक, 0644);
MODULE_PARM_DESC(bna_debugfs_enable, "Enables debugfs feature, default=1,"
		 " Range[false:0|true:1]");

/*
 * Global variables
 */
अटल u32 bnad_rxqs_per_cq = 2;
अटल atomic_t bna_id;
अटल स्थिर u8 bnad_bcast_addr[] __aligned(2) =
	अणु 0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण;

/*
 * Local MACROS
 */
#घोषणा BNAD_GET_MBOX_IRQ(_bnad)				\
	(((_bnad)->cfg_flags & BNAD_CF_MSIX) ?			\
	 ((_bnad)->msix_table[BNAD_MAILBOX_MSIX_INDEX].vector) : \
	 ((_bnad)->pcidev->irq))

#घोषणा BNAD_FILL_UNMAPQ_MEM_REQ(_res_info, _num, _size)	\
करो अणु								\
	(_res_info)->res_type = BNA_RES_T_MEM;			\
	(_res_info)->res_u.mem_info.mem_type = BNA_MEM_T_KVA;	\
	(_res_info)->res_u.mem_info.num = (_num);		\
	(_res_info)->res_u.mem_info.len = (_size);		\
पूर्ण जबतक (0)

/*
 * Reinitialize completions in CQ, once Rx is taken करोwn
 */
अटल व्योम
bnad_cq_cleanup(काष्ठा bnad *bnad, काष्ठा bna_ccb *ccb)
अणु
	काष्ठा bna_cq_entry *cmpl;
	पूर्णांक i;

	क्रम (i = 0; i < ccb->q_depth; i++) अणु
		cmpl = &((काष्ठा bna_cq_entry *)ccb->sw_q)[i];
		cmpl->valid = 0;
	पूर्ण
पूर्ण

/* Tx Datapath functions */


/* Caller should ensure that the entry at unmap_q[index] is valid */
अटल u32
bnad_tx_buff_unmap(काष्ठा bnad *bnad,
			      काष्ठा bnad_tx_unmap *unmap_q,
			      u32 q_depth, u32 index)
अणु
	काष्ठा bnad_tx_unmap *unmap;
	काष्ठा sk_buff *skb;
	पूर्णांक vector, nvecs;

	unmap = &unmap_q[index];
	nvecs = unmap->nvecs;

	skb = unmap->skb;
	unmap->skb = शून्य;
	unmap->nvecs = 0;
	dma_unmap_single(&bnad->pcidev->dev,
		dma_unmap_addr(&unmap->vectors[0], dma_addr),
		skb_headlen(skb), DMA_TO_DEVICE);
	dma_unmap_addr_set(&unmap->vectors[0], dma_addr, 0);
	nvecs--;

	vector = 0;
	जबतक (nvecs) अणु
		vector++;
		अगर (vector == BFI_TX_MAX_VECTORS_PER_WI) अणु
			vector = 0;
			BNA_QE_INDX_INC(index, q_depth);
			unmap = &unmap_q[index];
		पूर्ण

		dma_unmap_page(&bnad->pcidev->dev,
			dma_unmap_addr(&unmap->vectors[vector], dma_addr),
			dma_unmap_len(&unmap->vectors[vector], dma_len),
			DMA_TO_DEVICE);
		dma_unmap_addr_set(&unmap->vectors[vector], dma_addr, 0);
		nvecs--;
	पूर्ण

	BNA_QE_INDX_INC(index, q_depth);

	वापस index;
पूर्ण

/*
 * Frees all pending Tx Bufs
 * At this poपूर्णांक no activity is expected on the Q,
 * so DMA unmap & मुक्तing is fine.
 */
अटल व्योम
bnad_txq_cleanup(काष्ठा bnad *bnad, काष्ठा bna_tcb *tcb)
अणु
	काष्ठा bnad_tx_unmap *unmap_q = tcb->unmap_q;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < tcb->q_depth; i++) अणु
		skb = unmap_q[i].skb;
		अगर (!skb)
			जारी;
		bnad_tx_buff_unmap(bnad, unmap_q, tcb->q_depth, i);

		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

/*
 * bnad_txcmpl_process : Frees the Tx bufs on Tx completion
 * Can be called in a) Interrupt context
 *		    b) Sending context
 */
अटल u32
bnad_txcmpl_process(काष्ठा bnad *bnad, काष्ठा bna_tcb *tcb)
अणु
	u32 sent_packets = 0, sent_bytes = 0;
	u32 wis, unmap_wis, hw_cons, cons, q_depth;
	काष्ठा bnad_tx_unmap *unmap_q = tcb->unmap_q;
	काष्ठा bnad_tx_unmap *unmap;
	काष्ठा sk_buff *skb;

	/* Just वापस अगर TX is stopped */
	अगर (!test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags))
		वापस 0;

	hw_cons = *(tcb->hw_consumer_index);
	rmb();
	cons = tcb->consumer_index;
	q_depth = tcb->q_depth;

	wis = BNA_Q_INDEX_CHANGE(cons, hw_cons, q_depth);
	BUG_ON(!(wis <= BNA_QE_IN_USE_CNT(tcb, tcb->q_depth)));

	जबतक (wis) अणु
		unmap = &unmap_q[cons];

		skb = unmap->skb;

		sent_packets++;
		sent_bytes += skb->len;

		unmap_wis = BNA_TXQ_WI_NEEDED(unmap->nvecs);
		wis -= unmap_wis;

		cons = bnad_tx_buff_unmap(bnad, unmap_q, q_depth, cons);
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	/* Update consumer poपूर्णांकers. */
	tcb->consumer_index = hw_cons;

	tcb->txq->tx_packets += sent_packets;
	tcb->txq->tx_bytes += sent_bytes;

	वापस sent_packets;
पूर्ण

अटल u32
bnad_tx_complete(काष्ठा bnad *bnad, काष्ठा bna_tcb *tcb)
अणु
	काष्ठा net_device *netdev = bnad->netdev;
	u32 sent = 0;

	अगर (test_and_set_bit(BNAD_TXQ_FREE_SENT, &tcb->flags))
		वापस 0;

	sent = bnad_txcmpl_process(bnad, tcb);
	अगर (sent) अणु
		अगर (netअगर_queue_stopped(netdev) &&
		    netअगर_carrier_ok(netdev) &&
		    BNA_QE_FREE_CNT(tcb, tcb->q_depth) >=
				    BNAD_NETIF_WAKE_THRESHOLD) अणु
			अगर (test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags)) अणु
				netअगर_wake_queue(netdev);
				BNAD_UPDATE_CTR(bnad, netअगर_queue_wakeup);
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (likely(test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags)))
		bna_ib_ack(tcb->i_dbell, sent);

	smp_mb__beक्रमe_atomic();
	clear_bit(BNAD_TXQ_FREE_SENT, &tcb->flags);

	वापस sent;
पूर्ण

/* MSIX Tx Completion Handler */
अटल irqवापस_t
bnad_msix_tx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bna_tcb *tcb = (काष्ठा bna_tcb *)data;
	काष्ठा bnad *bnad = tcb->bnad;

	bnad_tx_complete(bnad, tcb);

	वापस IRQ_HANDLED;
पूर्ण

अटल अंतरभूत व्योम
bnad_rxq_alloc_uninit(काष्ठा bnad *bnad, काष्ठा bna_rcb *rcb)
अणु
	काष्ठा bnad_rx_unmap_q *unmap_q = rcb->unmap_q;

	unmap_q->reuse_pi = -1;
	unmap_q->alloc_order = -1;
	unmap_q->map_size = 0;
	unmap_q->type = BNAD_RXBUF_NONE;
पूर्ण

/* Default is page-based allocation. Multi-buffer support - TBD */
अटल पूर्णांक
bnad_rxq_alloc_init(काष्ठा bnad *bnad, काष्ठा bna_rcb *rcb)
अणु
	काष्ठा bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	पूर्णांक order;

	bnad_rxq_alloc_uninit(bnad, rcb);

	order = get_order(rcb->rxq->buffer_size);

	unmap_q->type = BNAD_RXBUF_PAGE;

	अगर (bna_is_small_rxq(rcb->id)) अणु
		unmap_q->alloc_order = 0;
		unmap_q->map_size = rcb->rxq->buffer_size;
	पूर्ण अन्यथा अणु
		अगर (rcb->rxq->multi_buffer) अणु
			unmap_q->alloc_order = 0;
			unmap_q->map_size = rcb->rxq->buffer_size;
			unmap_q->type = BNAD_RXBUF_MULTI_BUFF;
		पूर्ण अन्यथा अणु
			unmap_q->alloc_order = order;
			unmap_q->map_size =
				(rcb->rxq->buffer_size > 2048) ?
				PAGE_SIZE << order : 2048;
		पूर्ण
	पूर्ण

	BUG_ON((PAGE_SIZE << order) % unmap_q->map_size);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
bnad_rxq_cleanup_page(काष्ठा bnad *bnad, काष्ठा bnad_rx_unmap *unmap)
अणु
	अगर (!unmap->page)
		वापस;

	dma_unmap_page(&bnad->pcidev->dev,
			dma_unmap_addr(&unmap->vector, dma_addr),
			unmap->vector.len, DMA_FROM_DEVICE);
	put_page(unmap->page);
	unmap->page = शून्य;
	dma_unmap_addr_set(&unmap->vector, dma_addr, 0);
	unmap->vector.len = 0;
पूर्ण

अटल अंतरभूत व्योम
bnad_rxq_cleanup_skb(काष्ठा bnad *bnad, काष्ठा bnad_rx_unmap *unmap)
अणु
	अगर (!unmap->skb)
		वापस;

	dma_unmap_single(&bnad->pcidev->dev,
			dma_unmap_addr(&unmap->vector, dma_addr),
			unmap->vector.len, DMA_FROM_DEVICE);
	dev_kमुक्त_skb_any(unmap->skb);
	unmap->skb = शून्य;
	dma_unmap_addr_set(&unmap->vector, dma_addr, 0);
	unmap->vector.len = 0;
पूर्ण

अटल व्योम
bnad_rxq_cleanup(काष्ठा bnad *bnad, काष्ठा bna_rcb *rcb)
अणु
	काष्ठा bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	पूर्णांक i;

	क्रम (i = 0; i < rcb->q_depth; i++) अणु
		काष्ठा bnad_rx_unmap *unmap = &unmap_q->unmap[i];

		अगर (BNAD_RXBUF_IS_SK_BUFF(unmap_q->type))
			bnad_rxq_cleanup_skb(bnad, unmap);
		अन्यथा
			bnad_rxq_cleanup_page(bnad, unmap);
	पूर्ण
	bnad_rxq_alloc_uninit(bnad, rcb);
पूर्ण

अटल u32
bnad_rxq_refill_page(काष्ठा bnad *bnad, काष्ठा bna_rcb *rcb, u32 nalloc)
अणु
	u32 alloced, prod, q_depth;
	काष्ठा bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	काष्ठा bnad_rx_unmap *unmap, *prev;
	काष्ठा bna_rxq_entry *rxent;
	काष्ठा page *page;
	u32 page_offset, alloc_size;
	dma_addr_t dma_addr;

	prod = rcb->producer_index;
	q_depth = rcb->q_depth;

	alloc_size = PAGE_SIZE << unmap_q->alloc_order;
	alloced = 0;

	जबतक (nalloc--) अणु
		unmap = &unmap_q->unmap[prod];

		अगर (unmap_q->reuse_pi < 0) अणु
			page = alloc_pages(GFP_ATOMIC | __GFP_COMP,
					unmap_q->alloc_order);
			page_offset = 0;
		पूर्ण अन्यथा अणु
			prev = &unmap_q->unmap[unmap_q->reuse_pi];
			page = prev->page;
			page_offset = prev->page_offset + unmap_q->map_size;
			get_page(page);
		पूर्ण

		अगर (unlikely(!page)) अणु
			BNAD_UPDATE_CTR(bnad, rxbuf_alloc_failed);
			rcb->rxq->rxbuf_alloc_failed++;
			जाओ finishing;
		पूर्ण

		dma_addr = dma_map_page(&bnad->pcidev->dev, page, page_offset,
					unmap_q->map_size, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&bnad->pcidev->dev, dma_addr)) अणु
			put_page(page);
			BNAD_UPDATE_CTR(bnad, rxbuf_map_failed);
			rcb->rxq->rxbuf_map_failed++;
			जाओ finishing;
		पूर्ण

		unmap->page = page;
		unmap->page_offset = page_offset;
		dma_unmap_addr_set(&unmap->vector, dma_addr, dma_addr);
		unmap->vector.len = unmap_q->map_size;
		page_offset += unmap_q->map_size;

		अगर (page_offset < alloc_size)
			unmap_q->reuse_pi = prod;
		अन्यथा
			unmap_q->reuse_pi = -1;

		rxent = &((काष्ठा bna_rxq_entry *)rcb->sw_q)[prod];
		BNA_SET_DMA_ADDR(dma_addr, &rxent->host_addr);
		BNA_QE_INDX_INC(prod, q_depth);
		alloced++;
	पूर्ण

finishing:
	अगर (likely(alloced)) अणु
		rcb->producer_index = prod;
		smp_mb();
		अगर (likely(test_bit(BNAD_RXQ_POST_OK, &rcb->flags)))
			bna_rxq_prod_indx_करोorbell(rcb);
	पूर्ण

	वापस alloced;
पूर्ण

अटल u32
bnad_rxq_refill_skb(काष्ठा bnad *bnad, काष्ठा bna_rcb *rcb, u32 nalloc)
अणु
	u32 alloced, prod, q_depth, buff_sz;
	काष्ठा bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	काष्ठा bnad_rx_unmap *unmap;
	काष्ठा bna_rxq_entry *rxent;
	काष्ठा sk_buff *skb;
	dma_addr_t dma_addr;

	buff_sz = rcb->rxq->buffer_size;
	prod = rcb->producer_index;
	q_depth = rcb->q_depth;

	alloced = 0;
	जबतक (nalloc--) अणु
		unmap = &unmap_q->unmap[prod];

		skb = netdev_alloc_skb_ip_align(bnad->netdev, buff_sz);

		अगर (unlikely(!skb)) अणु
			BNAD_UPDATE_CTR(bnad, rxbuf_alloc_failed);
			rcb->rxq->rxbuf_alloc_failed++;
			जाओ finishing;
		पूर्ण

		dma_addr = dma_map_single(&bnad->pcidev->dev, skb->data,
					  buff_sz, DMA_FROM_DEVICE);
		अगर (dma_mapping_error(&bnad->pcidev->dev, dma_addr)) अणु
			dev_kमुक्त_skb_any(skb);
			BNAD_UPDATE_CTR(bnad, rxbuf_map_failed);
			rcb->rxq->rxbuf_map_failed++;
			जाओ finishing;
		पूर्ण

		unmap->skb = skb;
		dma_unmap_addr_set(&unmap->vector, dma_addr, dma_addr);
		unmap->vector.len = buff_sz;

		rxent = &((काष्ठा bna_rxq_entry *)rcb->sw_q)[prod];
		BNA_SET_DMA_ADDR(dma_addr, &rxent->host_addr);
		BNA_QE_INDX_INC(prod, q_depth);
		alloced++;
	पूर्ण

finishing:
	अगर (likely(alloced)) अणु
		rcb->producer_index = prod;
		smp_mb();
		अगर (likely(test_bit(BNAD_RXQ_POST_OK, &rcb->flags)))
			bna_rxq_prod_indx_करोorbell(rcb);
	पूर्ण

	वापस alloced;
पूर्ण

अटल अंतरभूत व्योम
bnad_rxq_post(काष्ठा bnad *bnad, काष्ठा bna_rcb *rcb)
अणु
	काष्ठा bnad_rx_unmap_q *unmap_q = rcb->unmap_q;
	u32 to_alloc;

	to_alloc = BNA_QE_FREE_CNT(rcb, rcb->q_depth);
	अगर (!(to_alloc >> BNAD_RXQ_REFILL_THRESHOLD_SHIFT))
		वापस;

	अगर (BNAD_RXBUF_IS_SK_BUFF(unmap_q->type))
		bnad_rxq_refill_skb(bnad, rcb, to_alloc);
	अन्यथा
		bnad_rxq_refill_page(bnad, rcb, to_alloc);
पूर्ण

#घोषणा flags_cksum_prot_mask (BNA_CQ_EF_IPV4 | BNA_CQ_EF_L3_CKSUM_OK | \
					BNA_CQ_EF_IPV6 | \
					BNA_CQ_EF_TCP | BNA_CQ_EF_UDP | \
					BNA_CQ_EF_L4_CKSUM_OK)

#घोषणा flags_tcp4 (BNA_CQ_EF_IPV4 | BNA_CQ_EF_L3_CKSUM_OK | \
				BNA_CQ_EF_TCP | BNA_CQ_EF_L4_CKSUM_OK)
#घोषणा flags_tcp6 (BNA_CQ_EF_IPV6 | \
				BNA_CQ_EF_TCP | BNA_CQ_EF_L4_CKSUM_OK)
#घोषणा flags_udp4 (BNA_CQ_EF_IPV4 | BNA_CQ_EF_L3_CKSUM_OK | \
				BNA_CQ_EF_UDP | BNA_CQ_EF_L4_CKSUM_OK)
#घोषणा flags_udp6 (BNA_CQ_EF_IPV6 | \
				BNA_CQ_EF_UDP | BNA_CQ_EF_L4_CKSUM_OK)

अटल व्योम
bnad_cq_drop_packet(काष्ठा bnad *bnad, काष्ठा bna_rcb *rcb,
		    u32 sop_ci, u32 nvecs)
अणु
	काष्ठा bnad_rx_unmap_q *unmap_q;
	काष्ठा bnad_rx_unmap *unmap;
	u32 ci, vec;

	unmap_q = rcb->unmap_q;
	क्रम (vec = 0, ci = sop_ci; vec < nvecs; vec++) अणु
		unmap = &unmap_q->unmap[ci];
		BNA_QE_INDX_INC(ci, rcb->q_depth);

		अगर (BNAD_RXBUF_IS_SK_BUFF(unmap_q->type))
			bnad_rxq_cleanup_skb(bnad, unmap);
		अन्यथा
			bnad_rxq_cleanup_page(bnad, unmap);
	पूर्ण
पूर्ण

अटल व्योम
bnad_cq_setup_skb_frags(काष्ठा bna_ccb *ccb, काष्ठा sk_buff *skb, u32 nvecs)
अणु
	काष्ठा bna_rcb *rcb;
	काष्ठा bnad *bnad;
	काष्ठा bnad_rx_unmap_q *unmap_q;
	काष्ठा bna_cq_entry *cq, *cmpl;
	u32 ci, pi, totlen = 0;

	cq = ccb->sw_q;
	pi = ccb->producer_index;
	cmpl = &cq[pi];

	rcb = bna_is_small_rxq(cmpl->rxq_id) ? ccb->rcb[1] : ccb->rcb[0];
	unmap_q = rcb->unmap_q;
	bnad = rcb->bnad;
	ci = rcb->consumer_index;

	/* prefetch header */
	prefetch(page_address(unmap_q->unmap[ci].page) +
		 unmap_q->unmap[ci].page_offset);

	जबतक (nvecs--) अणु
		काष्ठा bnad_rx_unmap *unmap;
		u32 len;

		unmap = &unmap_q->unmap[ci];
		BNA_QE_INDX_INC(ci, rcb->q_depth);

		dma_unmap_page(&bnad->pcidev->dev,
			       dma_unmap_addr(&unmap->vector, dma_addr),
			       unmap->vector.len, DMA_FROM_DEVICE);

		len = ntohs(cmpl->length);
		skb->truesize += unmap->vector.len;
		totlen += len;

		skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
				   unmap->page, unmap->page_offset, len);

		unmap->page = शून्य;
		unmap->vector.len = 0;

		BNA_QE_INDX_INC(pi, ccb->q_depth);
		cmpl = &cq[pi];
	पूर्ण

	skb->len += totlen;
	skb->data_len += totlen;
पूर्ण

अटल अंतरभूत व्योम
bnad_cq_setup_skb(काष्ठा bnad *bnad, काष्ठा sk_buff *skb,
		  काष्ठा bnad_rx_unmap *unmap, u32 len)
अणु
	prefetch(skb->data);

	dma_unmap_single(&bnad->pcidev->dev,
			dma_unmap_addr(&unmap->vector, dma_addr),
			unmap->vector.len, DMA_FROM_DEVICE);

	skb_put(skb, len);
	skb->protocol = eth_type_trans(skb, bnad->netdev);

	unmap->skb = शून्य;
	unmap->vector.len = 0;
पूर्ण

अटल u32
bnad_cq_process(काष्ठा bnad *bnad, काष्ठा bna_ccb *ccb, पूर्णांक budget)
अणु
	काष्ठा bna_cq_entry *cq, *cmpl, *next_cmpl;
	काष्ठा bna_rcb *rcb = शून्य;
	काष्ठा bnad_rx_unmap_q *unmap_q;
	काष्ठा bnad_rx_unmap *unmap = शून्य;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा bna_pkt_rate *pkt_rt = &ccb->pkt_rate;
	काष्ठा bnad_rx_ctrl *rx_ctrl = ccb->ctrl;
	u32 packets = 0, len = 0, totlen = 0;
	u32 pi, vec, sop_ci = 0, nvecs = 0;
	u32 flags, masked_flags;

	prefetch(bnad->netdev);

	cq = ccb->sw_q;

	जबतक (packets < budget) अणु
		cmpl = &cq[ccb->producer_index];
		अगर (!cmpl->valid)
			अवरोध;
		/* The 'valid' field is set by the adapter, only after writing
		 * the other fields of completion entry. Hence, करो not load
		 * other fields of completion entry *beक्रमe* the 'valid' is
		 * loaded. Adding the rmb() here prevents the compiler and/or
		 * CPU from reordering the पढ़ोs which would potentially result
		 * in पढ़ोing stale values in completion entry.
		 */
		rmb();

		BNA_UPDATE_PKT_CNT(pkt_rt, ntohs(cmpl->length));

		अगर (bna_is_small_rxq(cmpl->rxq_id))
			rcb = ccb->rcb[1];
		अन्यथा
			rcb = ccb->rcb[0];

		unmap_q = rcb->unmap_q;

		/* start of packet ci */
		sop_ci = rcb->consumer_index;

		अगर (BNAD_RXBUF_IS_SK_BUFF(unmap_q->type)) अणु
			unmap = &unmap_q->unmap[sop_ci];
			skb = unmap->skb;
		पूर्ण अन्यथा अणु
			skb = napi_get_frags(&rx_ctrl->napi);
			अगर (unlikely(!skb))
				अवरोध;
		पूर्ण
		prefetch(skb);

		flags = ntohl(cmpl->flags);
		len = ntohs(cmpl->length);
		totlen = len;
		nvecs = 1;

		/* Check all the completions क्रम this frame.
		 * busy-रुको करोesn't help much, अवरोध here.
		 */
		अगर (BNAD_RXBUF_IS_MULTI_BUFF(unmap_q->type) &&
		    (flags & BNA_CQ_EF_EOP) == 0) अणु
			pi = ccb->producer_index;
			करो अणु
				BNA_QE_INDX_INC(pi, ccb->q_depth);
				next_cmpl = &cq[pi];

				अगर (!next_cmpl->valid)
					अवरोध;
				/* The 'valid' field is set by the adapter, only
				 * after writing the other fields of completion
				 * entry. Hence, करो not load other fields of
				 * completion entry *beक्रमe* the 'valid' is
				 * loaded. Adding the rmb() here prevents the
				 * compiler and/or CPU from reordering the पढ़ोs
				 * which would potentially result in पढ़ोing
				 * stale values in completion entry.
				 */
				rmb();

				len = ntohs(next_cmpl->length);
				flags = ntohl(next_cmpl->flags);

				nvecs++;
				totlen += len;
			पूर्ण जबतक ((flags & BNA_CQ_EF_EOP) == 0);

			अगर (!next_cmpl->valid)
				अवरोध;
		पूर्ण
		packets++;

		/* TODO: BNA_CQ_EF_LOCAL ? */
		अगर (unlikely(flags & (BNA_CQ_EF_MAC_ERROR |
						BNA_CQ_EF_FCS_ERROR |
						BNA_CQ_EF_TOO_LONG))) अणु
			bnad_cq_drop_packet(bnad, rcb, sop_ci, nvecs);
			rcb->rxq->rx_packets_with_error++;

			जाओ next;
		पूर्ण

		अगर (BNAD_RXBUF_IS_SK_BUFF(unmap_q->type))
			bnad_cq_setup_skb(bnad, skb, unmap, len);
		अन्यथा
			bnad_cq_setup_skb_frags(ccb, skb, nvecs);

		rcb->rxq->rx_packets++;
		rcb->rxq->rx_bytes += totlen;
		ccb->bytes_per_पूर्णांकr += totlen;

		masked_flags = flags & flags_cksum_prot_mask;

		अगर (likely
		    ((bnad->netdev->features & NETIF_F_RXCSUM) &&
		     ((masked_flags == flags_tcp4) ||
		      (masked_flags == flags_udp4) ||
		      (masked_flags == flags_tcp6) ||
		      (masked_flags == flags_udp6))))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		अन्यथा
			skb_checksum_none_निश्चित(skb);

		अगर ((flags & BNA_CQ_EF_VLAN) &&
		    (bnad->netdev->features & NETIF_F_HW_VLAN_CTAG_RX))
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), ntohs(cmpl->vlan_tag));

		अगर (BNAD_RXBUF_IS_SK_BUFF(unmap_q->type))
			netअगर_receive_skb(skb);
		अन्यथा
			napi_gro_frags(&rx_ctrl->napi);

next:
		BNA_QE_INDX_ADD(rcb->consumer_index, nvecs, rcb->q_depth);
		क्रम (vec = 0; vec < nvecs; vec++) अणु
			cmpl = &cq[ccb->producer_index];
			cmpl->valid = 0;
			BNA_QE_INDX_INC(ccb->producer_index, ccb->q_depth);
		पूर्ण
	पूर्ण

	napi_gro_flush(&rx_ctrl->napi, false);
	अगर (likely(test_bit(BNAD_RXQ_STARTED, &ccb->rcb[0]->flags)))
		bna_ib_ack_disable_irq(ccb->i_dbell, packets);

	bnad_rxq_post(bnad, ccb->rcb[0]);
	अगर (ccb->rcb[1])
		bnad_rxq_post(bnad, ccb->rcb[1]);

	वापस packets;
पूर्ण

अटल व्योम
bnad_netअगर_rx_schedule_poll(काष्ठा bnad *bnad, काष्ठा bna_ccb *ccb)
अणु
	काष्ठा bnad_rx_ctrl *rx_ctrl = (काष्ठा bnad_rx_ctrl *)(ccb->ctrl);
	काष्ठा napi_काष्ठा *napi = &rx_ctrl->napi;

	अगर (likely(napi_schedule_prep(napi))) अणु
		__napi_schedule(napi);
		rx_ctrl->rx_schedule++;
	पूर्ण
पूर्ण

/* MSIX Rx Path Handler */
अटल irqवापस_t
bnad_msix_rx(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा bna_ccb *ccb = (काष्ठा bna_ccb *)data;

	अगर (ccb) अणु
		((काष्ठा bnad_rx_ctrl *)ccb->ctrl)->rx_पूर्णांकr_ctr++;
		bnad_netअगर_rx_schedule_poll(ccb->bnad, ccb);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

/* Interrupt handlers */

/* Mbox Interrupt Handlers */
अटल irqवापस_t
bnad_msix_mbox_handler(पूर्णांक irq, व्योम *data)
अणु
	u32 पूर्णांकr_status;
	अचिन्हित दीर्घ flags;
	काष्ठा bnad *bnad = (काष्ठा bnad *)data;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (unlikely(test_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags))) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		वापस IRQ_HANDLED;
	पूर्ण

	bna_पूर्णांकr_status_get(&bnad->bna, पूर्णांकr_status);

	अगर (BNA_IS_MBOX_ERR_INTR(&bnad->bna, पूर्णांकr_status))
		bna_mbox_handler(&bnad->bna, पूर्णांकr_status);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t
bnad_isr(पूर्णांक irq, व्योम *data)
अणु
	पूर्णांक i, j;
	u32 पूर्णांकr_status;
	अचिन्हित दीर्घ flags;
	काष्ठा bnad *bnad = (काष्ठा bnad *)data;
	काष्ठा bnad_rx_info *rx_info;
	काष्ठा bnad_rx_ctrl *rx_ctrl;
	काष्ठा bna_tcb *tcb = शून्य;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (unlikely(test_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags))) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	bna_पूर्णांकr_status_get(&bnad->bna, पूर्णांकr_status);

	अगर (unlikely(!पूर्णांकr_status)) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		वापस IRQ_NONE;
	पूर्ण

	अगर (BNA_IS_MBOX_ERR_INTR(&bnad->bna, पूर्णांकr_status))
		bna_mbox_handler(&bnad->bna, पूर्णांकr_status);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	अगर (!BNA_IS_INTX_DATA_INTR(पूर्णांकr_status))
		वापस IRQ_HANDLED;

	/* Process data पूर्णांकerrupts */
	/* Tx processing */
	क्रम (i = 0; i < bnad->num_tx; i++) अणु
		क्रम (j = 0; j < bnad->num_txq_per_tx; j++) अणु
			tcb = bnad->tx_info[i].tcb[j];
			अगर (tcb && test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags))
				bnad_tx_complete(bnad, bnad->tx_info[i].tcb[j]);
		पूर्ण
	पूर्ण
	/* Rx processing */
	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		rx_info = &bnad->rx_info[i];
		अगर (!rx_info->rx)
			जारी;
		क्रम (j = 0; j < bnad->num_rxp_per_rx; j++) अणु
			rx_ctrl = &rx_info->rx_ctrl[j];
			अगर (rx_ctrl->ccb)
				bnad_netअगर_rx_schedule_poll(bnad,
							    rx_ctrl->ccb);
		पूर्ण
	पूर्ण
	वापस IRQ_HANDLED;
पूर्ण

/*
 * Called in पूर्णांकerrupt / callback context
 * with bna_lock held, so cfg_flags access is OK
 */
अटल व्योम
bnad_enable_mbox_irq(काष्ठा bnad *bnad)
अणु
	clear_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags);

	BNAD_UPDATE_CTR(bnad, mbox_पूर्णांकr_enabled);
पूर्ण

/*
 * Called with bnad->bna_lock held b'cos of
 * bnad->cfg_flags access.
 */
अटल व्योम
bnad_disable_mbox_irq(काष्ठा bnad *bnad)
अणु
	set_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags);

	BNAD_UPDATE_CTR(bnad, mbox_पूर्णांकr_disabled);
पूर्ण

अटल व्योम
bnad_set_netdev_perm_addr(काष्ठा bnad *bnad)
अणु
	काष्ठा net_device *netdev = bnad->netdev;

	ether_addr_copy(netdev->perm_addr, bnad->perm_addr);
	अगर (is_zero_ether_addr(netdev->dev_addr))
		ether_addr_copy(netdev->dev_addr, bnad->perm_addr);
पूर्ण

/* Control Path Handlers */

/* Callbacks */
व्योम
bnad_cb_mbox_पूर्णांकr_enable(काष्ठा bnad *bnad)
अणु
	bnad_enable_mbox_irq(bnad);
पूर्ण

व्योम
bnad_cb_mbox_पूर्णांकr_disable(काष्ठा bnad *bnad)
अणु
	bnad_disable_mbox_irq(bnad);
पूर्ण

व्योम
bnad_cb_ioceth_पढ़ोy(काष्ठा bnad *bnad)
अणु
	bnad->bnad_completions.ioc_comp_status = BNA_CB_SUCCESS;
	complete(&bnad->bnad_completions.ioc_comp);
पूर्ण

व्योम
bnad_cb_ioceth_failed(काष्ठा bnad *bnad)
अणु
	bnad->bnad_completions.ioc_comp_status = BNA_CB_FAIL;
	complete(&bnad->bnad_completions.ioc_comp);
पूर्ण

व्योम
bnad_cb_ioceth_disabled(काष्ठा bnad *bnad)
अणु
	bnad->bnad_completions.ioc_comp_status = BNA_CB_SUCCESS;
	complete(&bnad->bnad_completions.ioc_comp);
पूर्ण

अटल व्योम
bnad_cb_enet_disabled(व्योम *arg)
अणु
	काष्ठा bnad *bnad = (काष्ठा bnad *)arg;

	netअगर_carrier_off(bnad->netdev);
	complete(&bnad->bnad_completions.enet_comp);
पूर्ण

व्योम
bnad_cb_ethport_link_status(काष्ठा bnad *bnad,
			क्रमागत bna_link_status link_status)
अणु
	bool link_up = false;

	link_up = (link_status == BNA_LINK_UP) || (link_status == BNA_CEE_UP);

	अगर (link_status == BNA_CEE_UP) अणु
		अगर (!test_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags))
			BNAD_UPDATE_CTR(bnad, cee_toggle);
		set_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags);
	पूर्ण अन्यथा अणु
		अगर (test_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags))
			BNAD_UPDATE_CTR(bnad, cee_toggle);
		clear_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags);
	पूर्ण

	अगर (link_up) अणु
		अगर (!netअगर_carrier_ok(bnad->netdev)) अणु
			uपूर्णांक tx_id, tcb_id;
			netdev_info(bnad->netdev, "link up\n");
			netअगर_carrier_on(bnad->netdev);
			BNAD_UPDATE_CTR(bnad, link_toggle);
			क्रम (tx_id = 0; tx_id < bnad->num_tx; tx_id++) अणु
				क्रम (tcb_id = 0; tcb_id < bnad->num_txq_per_tx;
				      tcb_id++) अणु
					काष्ठा bna_tcb *tcb =
					bnad->tx_info[tx_id].tcb[tcb_id];
					u32 txq_id;
					अगर (!tcb)
						जारी;

					txq_id = tcb->id;

					अगर (test_bit(BNAD_TXQ_TX_STARTED,
						     &tcb->flags)) अणु
						/*
						 * Force an immediate
						 * Transmit Schedule */
						netअगर_wake_subqueue(
								bnad->netdev,
								txq_id);
						BNAD_UPDATE_CTR(bnad,
							netअगर_queue_wakeup);
					पूर्ण अन्यथा अणु
						netअगर_stop_subqueue(
								bnad->netdev,
								txq_id);
						BNAD_UPDATE_CTR(bnad,
							netअगर_queue_stop);
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (netअगर_carrier_ok(bnad->netdev)) अणु
			netdev_info(bnad->netdev, "link down\n");
			netअगर_carrier_off(bnad->netdev);
			BNAD_UPDATE_CTR(bnad, link_toggle);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
bnad_cb_tx_disabled(व्योम *arg, काष्ठा bna_tx *tx)
अणु
	काष्ठा bnad *bnad = (काष्ठा bnad *)arg;

	complete(&bnad->bnad_completions.tx_comp);
पूर्ण

अटल व्योम
bnad_cb_tcb_setup(काष्ठा bnad *bnad, काष्ठा bna_tcb *tcb)
अणु
	काष्ठा bnad_tx_info *tx_info =
			(काष्ठा bnad_tx_info *)tcb->txq->tx->priv;

	tcb->priv = tcb;
	tx_info->tcb[tcb->id] = tcb;
पूर्ण

अटल व्योम
bnad_cb_tcb_destroy(काष्ठा bnad *bnad, काष्ठा bna_tcb *tcb)
अणु
	काष्ठा bnad_tx_info *tx_info =
			(काष्ठा bnad_tx_info *)tcb->txq->tx->priv;

	tx_info->tcb[tcb->id] = शून्य;
	tcb->priv = शून्य;
पूर्ण

अटल व्योम
bnad_cb_ccb_setup(काष्ठा bnad *bnad, काष्ठा bna_ccb *ccb)
अणु
	काष्ठा bnad_rx_info *rx_info =
			(काष्ठा bnad_rx_info *)ccb->cq->rx->priv;

	rx_info->rx_ctrl[ccb->id].ccb = ccb;
	ccb->ctrl = &rx_info->rx_ctrl[ccb->id];
पूर्ण

अटल व्योम
bnad_cb_ccb_destroy(काष्ठा bnad *bnad, काष्ठा bna_ccb *ccb)
अणु
	काष्ठा bnad_rx_info *rx_info =
			(काष्ठा bnad_rx_info *)ccb->cq->rx->priv;

	rx_info->rx_ctrl[ccb->id].ccb = शून्य;
पूर्ण

अटल व्योम
bnad_cb_tx_stall(काष्ठा bnad *bnad, काष्ठा bna_tx *tx)
अणु
	काष्ठा bnad_tx_info *tx_info =
			(काष्ठा bnad_tx_info *)tx->priv;
	काष्ठा bna_tcb *tcb;
	u32 txq_id;
	पूर्णांक i;

	क्रम (i = 0; i < BNAD_MAX_TXQ_PER_TX; i++) अणु
		tcb = tx_info->tcb[i];
		अगर (!tcb)
			जारी;
		txq_id = tcb->id;
		clear_bit(BNAD_TXQ_TX_STARTED, &tcb->flags);
		netअगर_stop_subqueue(bnad->netdev, txq_id);
	पूर्ण
पूर्ण

अटल व्योम
bnad_cb_tx_resume(काष्ठा bnad *bnad, काष्ठा bna_tx *tx)
अणु
	काष्ठा bnad_tx_info *tx_info = (काष्ठा bnad_tx_info *)tx->priv;
	काष्ठा bna_tcb *tcb;
	u32 txq_id;
	पूर्णांक i;

	क्रम (i = 0; i < BNAD_MAX_TXQ_PER_TX; i++) अणु
		tcb = tx_info->tcb[i];
		अगर (!tcb)
			जारी;
		txq_id = tcb->id;

		BUG_ON(test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags));
		set_bit(BNAD_TXQ_TX_STARTED, &tcb->flags);
		BUG_ON(*(tcb->hw_consumer_index) != 0);

		अगर (netअगर_carrier_ok(bnad->netdev)) अणु
			netअगर_wake_subqueue(bnad->netdev, txq_id);
			BNAD_UPDATE_CTR(bnad, netअगर_queue_wakeup);
		पूर्ण
	पूर्ण

	/*
	 * Workaround क्रम first ioceth enable failure & we
	 * get a 0 MAC address. We try to get the MAC address
	 * again here.
	 */
	अगर (is_zero_ether_addr(bnad->perm_addr)) अणु
		bna_enet_perm_mac_get(&bnad->bna.enet, bnad->perm_addr);
		bnad_set_netdev_perm_addr(bnad);
	पूर्ण
पूर्ण

/*
 * Free all TxQs buffers and then notअगरy TX_E_CLEANUP_DONE to Tx fsm.
 */
अटल व्योम
bnad_tx_cleanup(काष्ठा delayed_work *work)
अणु
	काष्ठा bnad_tx_info *tx_info =
		container_of(work, काष्ठा bnad_tx_info, tx_cleanup_work);
	काष्ठा bnad *bnad = शून्य;
	काष्ठा bna_tcb *tcb;
	अचिन्हित दीर्घ flags;
	u32 i, pending = 0;

	क्रम (i = 0; i < BNAD_MAX_TXQ_PER_TX; i++) अणु
		tcb = tx_info->tcb[i];
		अगर (!tcb)
			जारी;

		bnad = tcb->bnad;

		अगर (test_and_set_bit(BNAD_TXQ_FREE_SENT, &tcb->flags)) अणु
			pending++;
			जारी;
		पूर्ण

		bnad_txq_cleanup(bnad, tcb);

		smp_mb__beक्रमe_atomic();
		clear_bit(BNAD_TXQ_FREE_SENT, &tcb->flags);
	पूर्ण

	अगर (pending) अणु
		queue_delayed_work(bnad->work_q, &tx_info->tx_cleanup_work,
			msecs_to_jअगरfies(1));
		वापस;
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_tx_cleanup_complete(tx_info->tx);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

अटल व्योम
bnad_cb_tx_cleanup(काष्ठा bnad *bnad, काष्ठा bna_tx *tx)
अणु
	काष्ठा bnad_tx_info *tx_info = (काष्ठा bnad_tx_info *)tx->priv;
	काष्ठा bna_tcb *tcb;
	पूर्णांक i;

	क्रम (i = 0; i < BNAD_MAX_TXQ_PER_TX; i++) अणु
		tcb = tx_info->tcb[i];
		अगर (!tcb)
			जारी;
	पूर्ण

	queue_delayed_work(bnad->work_q, &tx_info->tx_cleanup_work, 0);
पूर्ण

अटल व्योम
bnad_cb_rx_stall(काष्ठा bnad *bnad, काष्ठा bna_rx *rx)
अणु
	काष्ठा bnad_rx_info *rx_info = (काष्ठा bnad_rx_info *)rx->priv;
	काष्ठा bna_ccb *ccb;
	काष्ठा bnad_rx_ctrl *rx_ctrl;
	पूर्णांक i;

	क्रम (i = 0; i < BNAD_MAX_RXP_PER_RX; i++) अणु
		rx_ctrl = &rx_info->rx_ctrl[i];
		ccb = rx_ctrl->ccb;
		अगर (!ccb)
			जारी;

		clear_bit(BNAD_RXQ_POST_OK, &ccb->rcb[0]->flags);

		अगर (ccb->rcb[1])
			clear_bit(BNAD_RXQ_POST_OK, &ccb->rcb[1]->flags);
	पूर्ण
पूर्ण

/*
 * Free all RxQs buffers and then notअगरy RX_E_CLEANUP_DONE to Rx fsm.
 */
अटल व्योम
bnad_rx_cleanup(व्योम *work)
अणु
	काष्ठा bnad_rx_info *rx_info =
		container_of(work, काष्ठा bnad_rx_info, rx_cleanup_work);
	काष्ठा bnad_rx_ctrl *rx_ctrl;
	काष्ठा bnad *bnad = शून्य;
	अचिन्हित दीर्घ flags;
	u32 i;

	क्रम (i = 0; i < BNAD_MAX_RXP_PER_RX; i++) अणु
		rx_ctrl = &rx_info->rx_ctrl[i];

		अगर (!rx_ctrl->ccb)
			जारी;

		bnad = rx_ctrl->ccb->bnad;

		/*
		 * Wait till the poll handler has निकासed
		 * and nothing can be scheduled anymore
		 */
		napi_disable(&rx_ctrl->napi);

		bnad_cq_cleanup(bnad, rx_ctrl->ccb);
		bnad_rxq_cleanup(bnad, rx_ctrl->ccb->rcb[0]);
		अगर (rx_ctrl->ccb->rcb[1])
			bnad_rxq_cleanup(bnad, rx_ctrl->ccb->rcb[1]);
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_rx_cleanup_complete(rx_info->rx);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

अटल व्योम
bnad_cb_rx_cleanup(काष्ठा bnad *bnad, काष्ठा bna_rx *rx)
अणु
	काष्ठा bnad_rx_info *rx_info = (काष्ठा bnad_rx_info *)rx->priv;
	काष्ठा bna_ccb *ccb;
	काष्ठा bnad_rx_ctrl *rx_ctrl;
	पूर्णांक i;

	क्रम (i = 0; i < BNAD_MAX_RXP_PER_RX; i++) अणु
		rx_ctrl = &rx_info->rx_ctrl[i];
		ccb = rx_ctrl->ccb;
		अगर (!ccb)
			जारी;

		clear_bit(BNAD_RXQ_STARTED, &ccb->rcb[0]->flags);

		अगर (ccb->rcb[1])
			clear_bit(BNAD_RXQ_STARTED, &ccb->rcb[1]->flags);
	पूर्ण

	queue_work(bnad->work_q, &rx_info->rx_cleanup_work);
पूर्ण

अटल व्योम
bnad_cb_rx_post(काष्ठा bnad *bnad, काष्ठा bna_rx *rx)
अणु
	काष्ठा bnad_rx_info *rx_info = (काष्ठा bnad_rx_info *)rx->priv;
	काष्ठा bna_ccb *ccb;
	काष्ठा bna_rcb *rcb;
	काष्ठा bnad_rx_ctrl *rx_ctrl;
	पूर्णांक i, j;

	क्रम (i = 0; i < BNAD_MAX_RXP_PER_RX; i++) अणु
		rx_ctrl = &rx_info->rx_ctrl[i];
		ccb = rx_ctrl->ccb;
		अगर (!ccb)
			जारी;

		napi_enable(&rx_ctrl->napi);

		क्रम (j = 0; j < BNAD_MAX_RXQ_PER_RXP; j++) अणु
			rcb = ccb->rcb[j];
			अगर (!rcb)
				जारी;

			bnad_rxq_alloc_init(bnad, rcb);
			set_bit(BNAD_RXQ_STARTED, &rcb->flags);
			set_bit(BNAD_RXQ_POST_OK, &rcb->flags);
			bnad_rxq_post(bnad, rcb);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम
bnad_cb_rx_disabled(व्योम *arg, काष्ठा bna_rx *rx)
अणु
	काष्ठा bnad *bnad = (काष्ठा bnad *)arg;

	complete(&bnad->bnad_completions.rx_comp);
पूर्ण

अटल व्योम
bnad_cb_rx_mcast_add(काष्ठा bnad *bnad, काष्ठा bna_rx *rx)
अणु
	bnad->bnad_completions.mcast_comp_status = BNA_CB_SUCCESS;
	complete(&bnad->bnad_completions.mcast_comp);
पूर्ण

व्योम
bnad_cb_stats_get(काष्ठा bnad *bnad, क्रमागत bna_cb_status status,
		       काष्ठा bna_stats *stats)
अणु
	अगर (status == BNA_CB_SUCCESS)
		BNAD_UPDATE_CTR(bnad, hw_stats_updates);

	अगर (!netअगर_running(bnad->netdev) ||
		!test_bit(BNAD_RF_STATS_TIMER_RUNNING, &bnad->run_flags))
		वापस;

	mod_समयr(&bnad->stats_समयr,
		  jअगरfies + msecs_to_jअगरfies(BNAD_STATS_TIMER_FREQ));
पूर्ण

अटल व्योम
bnad_cb_enet_mtu_set(काष्ठा bnad *bnad)
अणु
	bnad->bnad_completions.mtu_comp_status = BNA_CB_SUCCESS;
	complete(&bnad->bnad_completions.mtu_comp);
पूर्ण

व्योम
bnad_cb_completion(व्योम *arg, क्रमागत bfa_status status)
अणु
	काष्ठा bnad_iocmd_comp *iocmd_comp =
			(काष्ठा bnad_iocmd_comp *)arg;

	iocmd_comp->comp_status = (u32) status;
	complete(&iocmd_comp->comp);
पूर्ण

/* Resource allocation, मुक्त functions */

अटल व्योम
bnad_mem_मुक्त(काष्ठा bnad *bnad,
	      काष्ठा bna_mem_info *mem_info)
अणु
	पूर्णांक i;
	dma_addr_t dma_pa;

	अगर (mem_info->mdl == शून्य)
		वापस;

	क्रम (i = 0; i < mem_info->num; i++) अणु
		अगर (mem_info->mdl[i].kva != शून्य) अणु
			अगर (mem_info->mem_type == BNA_MEM_T_DMA) अणु
				BNA_GET_DMA_ADDR(&(mem_info->mdl[i].dma),
						dma_pa);
				dma_मुक्त_coherent(&bnad->pcidev->dev,
						  mem_info->mdl[i].len,
						  mem_info->mdl[i].kva, dma_pa);
			पूर्ण अन्यथा
				kमुक्त(mem_info->mdl[i].kva);
		पूर्ण
	पूर्ण
	kमुक्त(mem_info->mdl);
	mem_info->mdl = शून्य;
पूर्ण

अटल पूर्णांक
bnad_mem_alloc(काष्ठा bnad *bnad,
	       काष्ठा bna_mem_info *mem_info)
अणु
	पूर्णांक i;
	dma_addr_t dma_pa;

	अगर ((mem_info->num == 0) || (mem_info->len == 0)) अणु
		mem_info->mdl = शून्य;
		वापस 0;
	पूर्ण

	mem_info->mdl = kसुस्मृति(mem_info->num, माप(काष्ठा bna_mem_descr),
				GFP_KERNEL);
	अगर (mem_info->mdl == शून्य)
		वापस -ENOMEM;

	अगर (mem_info->mem_type == BNA_MEM_T_DMA) अणु
		क्रम (i = 0; i < mem_info->num; i++) अणु
			mem_info->mdl[i].len = mem_info->len;
			mem_info->mdl[i].kva =
				dma_alloc_coherent(&bnad->pcidev->dev,
						   mem_info->len, &dma_pa,
						   GFP_KERNEL);
			अगर (mem_info->mdl[i].kva == शून्य)
				जाओ err_वापस;

			BNA_SET_DMA_ADDR(dma_pa,
					 &(mem_info->mdl[i].dma));
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < mem_info->num; i++) अणु
			mem_info->mdl[i].len = mem_info->len;
			mem_info->mdl[i].kva = kzalloc(mem_info->len,
							GFP_KERNEL);
			अगर (mem_info->mdl[i].kva == शून्य)
				जाओ err_वापस;
		पूर्ण
	पूर्ण

	वापस 0;

err_वापस:
	bnad_mem_मुक्त(bnad, mem_info);
	वापस -ENOMEM;
पूर्ण

/* Free IRQ क्रम Mailbox */
अटल व्योम
bnad_mbox_irq_मुक्त(काष्ठा bnad *bnad)
अणु
	पूर्णांक irq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bnad_disable_mbox_irq(bnad);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	irq = BNAD_GET_MBOX_IRQ(bnad);
	मुक्त_irq(irq, bnad);
पूर्ण

/*
 * Allocates IRQ क्रम Mailbox, but keep it disabled
 * This will be enabled once we get the mbox enable callback
 * from bna
 */
अटल पूर्णांक
bnad_mbox_irq_alloc(काष्ठा bnad *bnad)
अणु
	पूर्णांक		err = 0;
	अचिन्हित दीर्घ	irq_flags, flags;
	u32	irq;
	irq_handler_t	irq_handler;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (bnad->cfg_flags & BNAD_CF_MSIX) अणु
		irq_handler = (irq_handler_t)bnad_msix_mbox_handler;
		irq = bnad->msix_table[BNAD_MAILBOX_MSIX_INDEX].vector;
		irq_flags = 0;
	पूर्ण अन्यथा अणु
		irq_handler = (irq_handler_t)bnad_isr;
		irq = bnad->pcidev->irq;
		irq_flags = IRQF_SHARED;
	पूर्ण

	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	प्र_लिखो(bnad->mbox_irq_name, "%s", BNAD_NAME);

	/*
	 * Set the Mbox IRQ disable flag, so that the IRQ handler
	 * called from request_irq() क्रम SHARED IRQs करो not execute
	 */
	set_bit(BNAD_RF_MBOX_IRQ_DISABLED, &bnad->run_flags);

	BNAD_UPDATE_CTR(bnad, mbox_पूर्णांकr_disabled);

	err = request_irq(irq, irq_handler, irq_flags,
			  bnad->mbox_irq_name, bnad);

	वापस err;
पूर्ण

अटल व्योम
bnad_txrx_irq_मुक्त(काष्ठा bnad *bnad, काष्ठा bna_पूर्णांकr_info *पूर्णांकr_info)
अणु
	kमुक्त(पूर्णांकr_info->idl);
	पूर्णांकr_info->idl = शून्य;
पूर्ण

/* Allocates Interrupt Descriptor List क्रम MSIX/INT-X vectors */
अटल पूर्णांक
bnad_txrx_irq_alloc(काष्ठा bnad *bnad, क्रमागत bnad_पूर्णांकr_source src,
		    u32 txrx_id, काष्ठा bna_पूर्णांकr_info *पूर्णांकr_info)
अणु
	पूर्णांक i, vector_start = 0;
	u32 cfg_flags;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	cfg_flags = bnad->cfg_flags;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	अगर (cfg_flags & BNAD_CF_MSIX) अणु
		पूर्णांकr_info->पूर्णांकr_type = BNA_INTR_T_MSIX;
		पूर्णांकr_info->idl = kसुस्मृति(पूर्णांकr_info->num,
					माप(काष्ठा bna_पूर्णांकr_descr),
					GFP_KERNEL);
		अगर (!पूर्णांकr_info->idl)
			वापस -ENOMEM;

		चयन (src) अणु
		हाल BNAD_INTR_TX:
			vector_start = BNAD_MAILBOX_MSIX_VECTORS + txrx_id;
			अवरोध;

		हाल BNAD_INTR_RX:
			vector_start = BNAD_MAILBOX_MSIX_VECTORS +
					(bnad->num_tx * bnad->num_txq_per_tx) +
					txrx_id;
			अवरोध;

		शेष:
			BUG();
		पूर्ण

		क्रम (i = 0; i < पूर्णांकr_info->num; i++)
			पूर्णांकr_info->idl[i].vector = vector_start + i;
	पूर्ण अन्यथा अणु
		पूर्णांकr_info->पूर्णांकr_type = BNA_INTR_T_INTX;
		पूर्णांकr_info->num = 1;
		पूर्णांकr_info->idl = kसुस्मृति(पूर्णांकr_info->num,
					माप(काष्ठा bna_पूर्णांकr_descr),
					GFP_KERNEL);
		अगर (!पूर्णांकr_info->idl)
			वापस -ENOMEM;

		चयन (src) अणु
		हाल BNAD_INTR_TX:
			पूर्णांकr_info->idl[0].vector = BNAD_INTX_TX_IB_BITMASK;
			अवरोध;

		हाल BNAD_INTR_RX:
			पूर्णांकr_info->idl[0].vector = BNAD_INTX_RX_IB_BITMASK;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

/* NOTE: Should be called क्रम MSIX only
 * Unरेजिस्टरs Tx MSIX vector(s) from the kernel
 */
अटल व्योम
bnad_tx_msix_unरेजिस्टर(काष्ठा bnad *bnad, काष्ठा bnad_tx_info *tx_info,
			पूर्णांक num_txqs)
अणु
	पूर्णांक i;
	पूर्णांक vector_num;

	क्रम (i = 0; i < num_txqs; i++) अणु
		अगर (tx_info->tcb[i] == शून्य)
			जारी;

		vector_num = tx_info->tcb[i]->पूर्णांकr_vector;
		मुक्त_irq(bnad->msix_table[vector_num].vector, tx_info->tcb[i]);
	पूर्ण
पूर्ण

/* NOTE: Should be called क्रम MSIX only
 * Registers Tx MSIX vector(s) and ISR(s), cookie with the kernel
 */
अटल पूर्णांक
bnad_tx_msix_रेजिस्टर(काष्ठा bnad *bnad, काष्ठा bnad_tx_info *tx_info,
			u32 tx_id, पूर्णांक num_txqs)
अणु
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक vector_num;

	क्रम (i = 0; i < num_txqs; i++) अणु
		vector_num = tx_info->tcb[i]->पूर्णांकr_vector;
		प्र_लिखो(tx_info->tcb[i]->name, "%s TXQ %d", bnad->netdev->name,
				tx_id + tx_info->tcb[i]->id);
		err = request_irq(bnad->msix_table[vector_num].vector,
				  (irq_handler_t)bnad_msix_tx, 0,
				  tx_info->tcb[i]->name,
				  tx_info->tcb[i]);
		अगर (err)
			जाओ err_वापस;
	पूर्ण

	वापस 0;

err_वापस:
	अगर (i > 0)
		bnad_tx_msix_unरेजिस्टर(bnad, tx_info, (i - 1));
	वापस -1;
पूर्ण

/* NOTE: Should be called क्रम MSIX only
 * Unरेजिस्टरs Rx MSIX vector(s) from the kernel
 */
अटल व्योम
bnad_rx_msix_unरेजिस्टर(काष्ठा bnad *bnad, काष्ठा bnad_rx_info *rx_info,
			पूर्णांक num_rxps)
अणु
	पूर्णांक i;
	पूर्णांक vector_num;

	क्रम (i = 0; i < num_rxps; i++) अणु
		अगर (rx_info->rx_ctrl[i].ccb == शून्य)
			जारी;

		vector_num = rx_info->rx_ctrl[i].ccb->पूर्णांकr_vector;
		मुक्त_irq(bnad->msix_table[vector_num].vector,
			 rx_info->rx_ctrl[i].ccb);
	पूर्ण
पूर्ण

/* NOTE: Should be called क्रम MSIX only
 * Registers Tx MSIX vector(s) and ISR(s), cookie with the kernel
 */
अटल पूर्णांक
bnad_rx_msix_रेजिस्टर(काष्ठा bnad *bnad, काष्ठा bnad_rx_info *rx_info,
			u32 rx_id, पूर्णांक num_rxps)
अणु
	पूर्णांक i;
	पूर्णांक err;
	पूर्णांक vector_num;

	क्रम (i = 0; i < num_rxps; i++) अणु
		vector_num = rx_info->rx_ctrl[i].ccb->पूर्णांकr_vector;
		प्र_लिखो(rx_info->rx_ctrl[i].ccb->name, "%s CQ %d",
			bnad->netdev->name,
			rx_id + rx_info->rx_ctrl[i].ccb->id);
		err = request_irq(bnad->msix_table[vector_num].vector,
				  (irq_handler_t)bnad_msix_rx, 0,
				  rx_info->rx_ctrl[i].ccb->name,
				  rx_info->rx_ctrl[i].ccb);
		अगर (err)
			जाओ err_वापस;
	पूर्ण

	वापस 0;

err_वापस:
	अगर (i > 0)
		bnad_rx_msix_unरेजिस्टर(bnad, rx_info, (i - 1));
	वापस -1;
पूर्ण

/* Free Tx object Resources */
अटल व्योम
bnad_tx_res_मुक्त(काष्ठा bnad *bnad, काष्ठा bna_res_info *res_info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BNA_TX_RES_T_MAX; i++) अणु
		अगर (res_info[i].res_type == BNA_RES_T_MEM)
			bnad_mem_मुक्त(bnad, &res_info[i].res_u.mem_info);
		अन्यथा अगर (res_info[i].res_type == BNA_RES_T_INTR)
			bnad_txrx_irq_मुक्त(bnad, &res_info[i].res_u.पूर्णांकr_info);
	पूर्ण
पूर्ण

/* Allocates memory and पूर्णांकerrupt resources क्रम Tx object */
अटल पूर्णांक
bnad_tx_res_alloc(काष्ठा bnad *bnad, काष्ठा bna_res_info *res_info,
		  u32 tx_id)
अणु
	पूर्णांक i, err = 0;

	क्रम (i = 0; i < BNA_TX_RES_T_MAX; i++) अणु
		अगर (res_info[i].res_type == BNA_RES_T_MEM)
			err = bnad_mem_alloc(bnad,
					&res_info[i].res_u.mem_info);
		अन्यथा अगर (res_info[i].res_type == BNA_RES_T_INTR)
			err = bnad_txrx_irq_alloc(bnad, BNAD_INTR_TX, tx_id,
					&res_info[i].res_u.पूर्णांकr_info);
		अगर (err)
			जाओ err_वापस;
	पूर्ण
	वापस 0;

err_वापस:
	bnad_tx_res_मुक्त(bnad, res_info);
	वापस err;
पूर्ण

/* Free Rx object Resources */
अटल व्योम
bnad_rx_res_मुक्त(काष्ठा bnad *bnad, काष्ठा bna_res_info *res_info)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < BNA_RX_RES_T_MAX; i++) अणु
		अगर (res_info[i].res_type == BNA_RES_T_MEM)
			bnad_mem_मुक्त(bnad, &res_info[i].res_u.mem_info);
		अन्यथा अगर (res_info[i].res_type == BNA_RES_T_INTR)
			bnad_txrx_irq_मुक्त(bnad, &res_info[i].res_u.पूर्णांकr_info);
	पूर्ण
पूर्ण

/* Allocates memory and पूर्णांकerrupt resources क्रम Rx object */
अटल पूर्णांक
bnad_rx_res_alloc(काष्ठा bnad *bnad, काष्ठा bna_res_info *res_info,
		  uपूर्णांक rx_id)
अणु
	पूर्णांक i, err = 0;

	/* All memory needs to be allocated beक्रमe setup_ccbs */
	क्रम (i = 0; i < BNA_RX_RES_T_MAX; i++) अणु
		अगर (res_info[i].res_type == BNA_RES_T_MEM)
			err = bnad_mem_alloc(bnad,
					&res_info[i].res_u.mem_info);
		अन्यथा अगर (res_info[i].res_type == BNA_RES_T_INTR)
			err = bnad_txrx_irq_alloc(bnad, BNAD_INTR_RX, rx_id,
					&res_info[i].res_u.पूर्णांकr_info);
		अगर (err)
			जाओ err_वापस;
	पूर्ण
	वापस 0;

err_वापस:
	bnad_rx_res_मुक्त(bnad, res_info);
	वापस err;
पूर्ण

/* Timer callbacks */
/* a) IOC समयr */
अटल व्योम
bnad_ioc_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा bnad *bnad = from_समयr(bnad, t, bna.ioceth.ioc.ioc_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bfa_nw_ioc_समयout(&bnad->bna.ioceth.ioc);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

अटल व्योम
bnad_ioc_hb_check(काष्ठा समयr_list *t)
अणु
	काष्ठा bnad *bnad = from_समयr(bnad, t, bna.ioceth.ioc.hb_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bfa_nw_ioc_hb_check(&bnad->bna.ioceth.ioc);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

अटल व्योम
bnad_iocpf_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा bnad *bnad = from_समयr(bnad, t, bna.ioceth.ioc.iocpf_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bfa_nw_iocpf_समयout(&bnad->bna.ioceth.ioc);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

अटल व्योम
bnad_iocpf_sem_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा bnad *bnad = from_समयr(bnad, t, bna.ioceth.ioc.sem_समयr);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bfa_nw_iocpf_sem_समयout(&bnad->bna.ioceth.ioc);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

/*
 * All समयr routines use bnad->bna_lock to protect against
 * the following race, which may occur in हाल of no locking:
 *	Time	CPU m	CPU n
 *	0       1 = test_bit
 *	1			clear_bit
 *	2			del_समयr_sync
 *	3	mod_समयr
 */

/* b) Dynamic Interrupt Moderation Timer */
अटल व्योम
bnad_dim_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा bnad *bnad = from_समयr(bnad, t, dim_समयr);
	काष्ठा bnad_rx_info *rx_info;
	काष्ठा bnad_rx_ctrl *rx_ctrl;
	पूर्णांक i, j;
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_carrier_ok(bnad->netdev))
		वापस;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		rx_info = &bnad->rx_info[i];
		अगर (!rx_info->rx)
			जारी;
		क्रम (j = 0; j < bnad->num_rxp_per_rx; j++) अणु
			rx_ctrl = &rx_info->rx_ctrl[j];
			अगर (!rx_ctrl->ccb)
				जारी;
			bna_rx_dim_update(rx_ctrl->ccb);
		पूर्ण
	पूर्ण

	/* Check क्रम BNAD_CF_DIM_ENABLED, करोes not eliminate a race */
	अगर (test_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags))
		mod_समयr(&bnad->dim_समयr,
			  jअगरfies + msecs_to_jअगरfies(BNAD_DIM_TIMER_FREQ));
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

/* c)  Statistics Timer */
अटल व्योम
bnad_stats_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा bnad *bnad = from_समयr(bnad, t, stats_समयr);
	अचिन्हित दीर्घ flags;

	अगर (!netअगर_running(bnad->netdev) ||
		!test_bit(BNAD_RF_STATS_TIMER_RUNNING, &bnad->run_flags))
		वापस;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_hw_stats_get(&bnad->bna);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

/*
 * Set up समयr क्रम DIM
 * Called with bnad->bna_lock held
 */
व्योम
bnad_dim_समयr_start(काष्ठा bnad *bnad)
अणु
	अगर (bnad->cfg_flags & BNAD_CF_DIM_ENABLED &&
	    !test_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags)) अणु
		समयr_setup(&bnad->dim_समयr, bnad_dim_समयout, 0);
		set_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags);
		mod_समयr(&bnad->dim_समयr,
			  jअगरfies + msecs_to_jअगरfies(BNAD_DIM_TIMER_FREQ));
	पूर्ण
पूर्ण

/*
 * Set up समयr क्रम statistics
 * Called with mutex_lock(&bnad->conf_mutex) held
 */
अटल व्योम
bnad_stats_समयr_start(काष्ठा bnad *bnad)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (!test_and_set_bit(BNAD_RF_STATS_TIMER_RUNNING, &bnad->run_flags)) अणु
		समयr_setup(&bnad->stats_समयr, bnad_stats_समयout, 0);
		mod_समयr(&bnad->stats_समयr,
			  jअगरfies + msecs_to_jअगरfies(BNAD_STATS_TIMER_FREQ));
	पूर्ण
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

/*
 * Stops the stats समयr
 * Called with mutex_lock(&bnad->conf_mutex) held
 */
अटल व्योम
bnad_stats_समयr_stop(काष्ठा bnad *bnad)
अणु
	पूर्णांक to_del = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (test_and_clear_bit(BNAD_RF_STATS_TIMER_RUNNING, &bnad->run_flags))
		to_del = 1;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	अगर (to_del)
		del_समयr_sync(&bnad->stats_समयr);
पूर्ण

/* Utilities */

अटल व्योम
bnad_netdev_mc_list_get(काष्ठा net_device *netdev, u8 *mc_list)
अणु
	पूर्णांक i = 1; /* Index 0 has broadcast address */
	काष्ठा netdev_hw_addr *mc_addr;

	netdev_क्रम_each_mc_addr(mc_addr, netdev) अणु
		ether_addr_copy(&mc_list[i * ETH_ALEN], &mc_addr->addr[0]);
		i++;
	पूर्ण
पूर्ण

अटल पूर्णांक
bnad_napi_poll_rx(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा bnad_rx_ctrl *rx_ctrl =
		container_of(napi, काष्ठा bnad_rx_ctrl, napi);
	काष्ठा bnad *bnad = rx_ctrl->bnad;
	पूर्णांक rcvd = 0;

	rx_ctrl->rx_poll_ctr++;

	अगर (!netअगर_carrier_ok(bnad->netdev))
		जाओ poll_निकास;

	rcvd = bnad_cq_process(bnad, rx_ctrl->ccb, budget);
	अगर (rcvd >= budget)
		वापस rcvd;

poll_निकास:
	napi_complete_करोne(napi, rcvd);

	rx_ctrl->rx_complete++;

	अगर (rx_ctrl->ccb)
		bnad_enable_rx_irq_unsafe(rx_ctrl->ccb);

	वापस rcvd;
पूर्ण

#घोषणा BNAD_NAPI_POLL_QUOTA		64
अटल व्योम
bnad_napi_add(काष्ठा bnad *bnad, u32 rx_id)
अणु
	काष्ठा bnad_rx_ctrl *rx_ctrl;
	पूर्णांक i;

	/* Initialize & enable NAPI */
	क्रम (i = 0; i <	bnad->num_rxp_per_rx; i++) अणु
		rx_ctrl = &bnad->rx_info[rx_id].rx_ctrl[i];
		netअगर_napi_add(bnad->netdev, &rx_ctrl->napi,
			       bnad_napi_poll_rx, BNAD_NAPI_POLL_QUOTA);
	पूर्ण
पूर्ण

अटल व्योम
bnad_napi_delete(काष्ठा bnad *bnad, u32 rx_id)
अणु
	पूर्णांक i;

	/* First disable and then clean up */
	क्रम (i = 0; i < bnad->num_rxp_per_rx; i++)
		netअगर_napi_del(&bnad->rx_info[rx_id].rx_ctrl[i].napi);
पूर्ण

/* Should be held with conf_lock held */
व्योम
bnad_destroy_tx(काष्ठा bnad *bnad, u32 tx_id)
अणु
	काष्ठा bnad_tx_info *tx_info = &bnad->tx_info[tx_id];
	काष्ठा bna_res_info *res_info = &bnad->tx_res_info[tx_id].res_info[0];
	अचिन्हित दीर्घ flags;

	अगर (!tx_info->tx)
		वापस;

	init_completion(&bnad->bnad_completions.tx_comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_tx_disable(tx_info->tx, BNA_HARD_CLEANUP, bnad_cb_tx_disabled);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	रुको_क्रम_completion(&bnad->bnad_completions.tx_comp);

	अगर (tx_info->tcb[0]->पूर्णांकr_type == BNA_INTR_T_MSIX)
		bnad_tx_msix_unरेजिस्टर(bnad, tx_info,
			bnad->num_txq_per_tx);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_tx_destroy(tx_info->tx);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	tx_info->tx = शून्य;
	tx_info->tx_id = 0;

	bnad_tx_res_मुक्त(bnad, res_info);
पूर्ण

/* Should be held with conf_lock held */
पूर्णांक
bnad_setup_tx(काष्ठा bnad *bnad, u32 tx_id)
अणु
	पूर्णांक err;
	काष्ठा bnad_tx_info *tx_info = &bnad->tx_info[tx_id];
	काष्ठा bna_res_info *res_info = &bnad->tx_res_info[tx_id].res_info[0];
	काष्ठा bna_पूर्णांकr_info *पूर्णांकr_info =
			&res_info[BNA_TX_RES_INTR_T_TXCMPL].res_u.पूर्णांकr_info;
	काष्ठा bna_tx_config *tx_config = &bnad->tx_config[tx_id];
	अटल स्थिर काष्ठा bna_tx_event_cbfn tx_cbfn = अणु
		.tcb_setup_cbfn = bnad_cb_tcb_setup,
		.tcb_destroy_cbfn = bnad_cb_tcb_destroy,
		.tx_stall_cbfn = bnad_cb_tx_stall,
		.tx_resume_cbfn = bnad_cb_tx_resume,
		.tx_cleanup_cbfn = bnad_cb_tx_cleanup,
	पूर्ण;

	काष्ठा bna_tx *tx;
	अचिन्हित दीर्घ flags;

	tx_info->tx_id = tx_id;

	/* Initialize the Tx object configuration */
	tx_config->num_txq = bnad->num_txq_per_tx;
	tx_config->txq_depth = bnad->txq_depth;
	tx_config->tx_type = BNA_TX_T_REGULAR;
	tx_config->coalescing_समयo = bnad->tx_coalescing_समयo;

	/* Get BNA's resource requirement क्रम one tx object */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_tx_res_req(bnad->num_txq_per_tx,
		bnad->txq_depth, res_info);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Fill Unmap Q memory requirements */
	BNAD_FILL_UNMAPQ_MEM_REQ(&res_info[BNA_TX_RES_MEM_T_UNMAPQ],
			bnad->num_txq_per_tx, (माप(काष्ठा bnad_tx_unmap) *
			bnad->txq_depth));

	/* Allocate resources */
	err = bnad_tx_res_alloc(bnad, res_info, tx_id);
	अगर (err)
		वापस err;

	/* Ask BNA to create one Tx object, supplying required resources */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	tx = bna_tx_create(&bnad->bna, bnad, tx_config, &tx_cbfn, res_info,
			tx_info);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	अगर (!tx) अणु
		err = -ENOMEM;
		जाओ err_वापस;
	पूर्ण
	tx_info->tx = tx;

	INIT_DELAYED_WORK(&tx_info->tx_cleanup_work,
			(work_func_t)bnad_tx_cleanup);

	/* Register ISR क्रम the Tx object */
	अगर (पूर्णांकr_info->पूर्णांकr_type == BNA_INTR_T_MSIX) अणु
		err = bnad_tx_msix_रेजिस्टर(bnad, tx_info,
			tx_id, bnad->num_txq_per_tx);
		अगर (err)
			जाओ cleanup_tx;
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_tx_enable(tx);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	वापस 0;

cleanup_tx:
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_tx_destroy(tx_info->tx);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	tx_info->tx = शून्य;
	tx_info->tx_id = 0;
err_वापस:
	bnad_tx_res_मुक्त(bnad, res_info);
	वापस err;
पूर्ण

/* Setup the rx config क्रम bna_rx_create */
/* bnad decides the configuration */
अटल व्योम
bnad_init_rx_config(काष्ठा bnad *bnad, काष्ठा bna_rx_config *rx_config)
अणु
	स_रखो(rx_config, 0, माप(*rx_config));
	rx_config->rx_type = BNA_RX_T_REGULAR;
	rx_config->num_paths = bnad->num_rxp_per_rx;
	rx_config->coalescing_समयo = bnad->rx_coalescing_समयo;

	अगर (bnad->num_rxp_per_rx > 1) अणु
		rx_config->rss_status = BNA_STATUS_T_ENABLED;
		rx_config->rss_config.hash_type =
				(BFI_ENET_RSS_IPV6 |
				 BFI_ENET_RSS_IPV6_TCP |
				 BFI_ENET_RSS_IPV4 |
				 BFI_ENET_RSS_IPV4_TCP);
		rx_config->rss_config.hash_mask =
				bnad->num_rxp_per_rx - 1;
		netdev_rss_key_fill(rx_config->rss_config.toeplitz_hash_key,
			माप(rx_config->rss_config.toeplitz_hash_key));
	पूर्ण अन्यथा अणु
		rx_config->rss_status = BNA_STATUS_T_DISABLED;
		स_रखो(&rx_config->rss_config, 0,
		       माप(rx_config->rss_config));
	पूर्ण

	rx_config->frame_size = BNAD_FRAME_SIZE(bnad->netdev->mtu);
	rx_config->q0_multi_buf = BNA_STATUS_T_DISABLED;

	/* BNA_RXP_SINGLE - one data-buffer queue
	 * BNA_RXP_SLR - one small-buffer and one large-buffer queues
	 * BNA_RXP_HDS - one header-buffer and one data-buffer queues
	 */
	/* TODO: configurable param क्रम queue type */
	rx_config->rxp_type = BNA_RXP_SLR;

	अगर (BNAD_PCI_DEV_IS_CAT2(bnad) &&
	    rx_config->frame_size > 4096) अणु
		/* though size_routing_enable is set in SLR,
		 * small packets may get routed to same rxq.
		 * set buf_size to 2048 instead of PAGE_SIZE.
		 */
		rx_config->q0_buf_size = 2048;
		/* this should be in multiples of 2 */
		rx_config->q0_num_vecs = 4;
		rx_config->q0_depth = bnad->rxq_depth * rx_config->q0_num_vecs;
		rx_config->q0_multi_buf = BNA_STATUS_T_ENABLED;
	पूर्ण अन्यथा अणु
		rx_config->q0_buf_size = rx_config->frame_size;
		rx_config->q0_num_vecs = 1;
		rx_config->q0_depth = bnad->rxq_depth;
	पूर्ण

	/* initialize क्रम q1 क्रम BNA_RXP_SLR/BNA_RXP_HDS */
	अगर (rx_config->rxp_type == BNA_RXP_SLR) अणु
		rx_config->q1_depth = bnad->rxq_depth;
		rx_config->q1_buf_size = BFI_SMALL_RXBUF_SIZE;
	पूर्ण

	rx_config->vlan_strip_status =
		(bnad->netdev->features & NETIF_F_HW_VLAN_CTAG_RX) ?
		BNA_STATUS_T_ENABLED : BNA_STATUS_T_DISABLED;
पूर्ण

अटल व्योम
bnad_rx_ctrl_init(काष्ठा bnad *bnad, u32 rx_id)
अणु
	काष्ठा bnad_rx_info *rx_info = &bnad->rx_info[rx_id];
	पूर्णांक i;

	क्रम (i = 0; i < bnad->num_rxp_per_rx; i++)
		rx_info->rx_ctrl[i].bnad = bnad;
पूर्ण

/* Called with mutex_lock(&bnad->conf_mutex) held */
अटल u32
bnad_reinit_rx(काष्ठा bnad *bnad)
अणु
	काष्ठा net_device *netdev = bnad->netdev;
	u32 err = 0, current_err = 0;
	u32 rx_id = 0, count = 0;
	अचिन्हित दीर्घ flags;

	/* destroy and create new rx objects */
	क्रम (rx_id = 0; rx_id < bnad->num_rx; rx_id++) अणु
		अगर (!bnad->rx_info[rx_id].rx)
			जारी;
		bnad_destroy_rx(bnad, rx_id);
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_enet_mtu_set(&bnad->bna.enet,
			 BNAD_FRAME_SIZE(bnad->netdev->mtu), शून्य);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	क्रम (rx_id = 0; rx_id < bnad->num_rx; rx_id++) अणु
		count++;
		current_err = bnad_setup_rx(bnad, rx_id);
		अगर (current_err && !err) अणु
			err = current_err;
			netdev_err(netdev, "RXQ:%u setup failed\n", rx_id);
		पूर्ण
	पूर्ण

	/* restore rx configuration */
	अगर (bnad->rx_info[0].rx && !err) अणु
		bnad_restore_vlans(bnad, 0);
		bnad_enable_शेष_bcast(bnad);
		spin_lock_irqsave(&bnad->bna_lock, flags);
		bnad_mac_addr_set_locked(bnad, netdev->dev_addr);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		bnad_set_rx_mode(netdev);
	पूर्ण

	वापस count;
पूर्ण

/* Called with bnad_conf_lock() held */
व्योम
bnad_destroy_rx(काष्ठा bnad *bnad, u32 rx_id)
अणु
	काष्ठा bnad_rx_info *rx_info = &bnad->rx_info[rx_id];
	काष्ठा bna_rx_config *rx_config = &bnad->rx_config[rx_id];
	काष्ठा bna_res_info *res_info = &bnad->rx_res_info[rx_id].res_info[0];
	अचिन्हित दीर्घ flags;
	पूर्णांक to_del = 0;

	अगर (!rx_info->rx)
		वापस;

	अगर (0 == rx_id) अणु
		spin_lock_irqsave(&bnad->bna_lock, flags);
		अगर (bnad->cfg_flags & BNAD_CF_DIM_ENABLED &&
		    test_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags)) अणु
			clear_bit(BNAD_RF_DIM_TIMER_RUNNING, &bnad->run_flags);
			to_del = 1;
		पूर्ण
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		अगर (to_del)
			del_समयr_sync(&bnad->dim_समयr);
	पूर्ण

	init_completion(&bnad->bnad_completions.rx_comp);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_rx_disable(rx_info->rx, BNA_HARD_CLEANUP, bnad_cb_rx_disabled);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	रुको_क्रम_completion(&bnad->bnad_completions.rx_comp);

	अगर (rx_info->rx_ctrl[0].ccb->पूर्णांकr_type == BNA_INTR_T_MSIX)
		bnad_rx_msix_unरेजिस्टर(bnad, rx_info, rx_config->num_paths);

	bnad_napi_delete(bnad, rx_id);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_rx_destroy(rx_info->rx);

	rx_info->rx = शून्य;
	rx_info->rx_id = 0;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	bnad_rx_res_मुक्त(bnad, res_info);
पूर्ण

/* Called with mutex_lock(&bnad->conf_mutex) held */
पूर्णांक
bnad_setup_rx(काष्ठा bnad *bnad, u32 rx_id)
अणु
	पूर्णांक err;
	काष्ठा bnad_rx_info *rx_info = &bnad->rx_info[rx_id];
	काष्ठा bna_res_info *res_info = &bnad->rx_res_info[rx_id].res_info[0];
	काष्ठा bna_पूर्णांकr_info *पूर्णांकr_info =
			&res_info[BNA_RX_RES_T_INTR].res_u.पूर्णांकr_info;
	काष्ठा bna_rx_config *rx_config = &bnad->rx_config[rx_id];
	अटल स्थिर काष्ठा bna_rx_event_cbfn rx_cbfn = अणु
		.rcb_setup_cbfn = शून्य,
		.rcb_destroy_cbfn = शून्य,
		.ccb_setup_cbfn = bnad_cb_ccb_setup,
		.ccb_destroy_cbfn = bnad_cb_ccb_destroy,
		.rx_stall_cbfn = bnad_cb_rx_stall,
		.rx_cleanup_cbfn = bnad_cb_rx_cleanup,
		.rx_post_cbfn = bnad_cb_rx_post,
	पूर्ण;
	काष्ठा bna_rx *rx;
	अचिन्हित दीर्घ flags;

	rx_info->rx_id = rx_id;

	/* Initialize the Rx object configuration */
	bnad_init_rx_config(bnad, rx_config);

	/* Get BNA's resource requirement क्रम one Rx object */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_rx_res_req(rx_config, res_info);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Fill Unmap Q memory requirements */
	BNAD_FILL_UNMAPQ_MEM_REQ(&res_info[BNA_RX_RES_MEM_T_UNMAPDQ],
				 rx_config->num_paths,
			(rx_config->q0_depth *
			 माप(काष्ठा bnad_rx_unmap)) +
			 माप(काष्ठा bnad_rx_unmap_q));

	अगर (rx_config->rxp_type != BNA_RXP_SINGLE) अणु
		BNAD_FILL_UNMAPQ_MEM_REQ(&res_info[BNA_RX_RES_MEM_T_UNMAPHQ],
					 rx_config->num_paths,
				(rx_config->q1_depth *
				 माप(काष्ठा bnad_rx_unmap) +
				 माप(काष्ठा bnad_rx_unmap_q)));
	पूर्ण
	/* Allocate resource */
	err = bnad_rx_res_alloc(bnad, res_info, rx_id);
	अगर (err)
		वापस err;

	bnad_rx_ctrl_init(bnad, rx_id);

	/* Ask BNA to create one Rx object, supplying required resources */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	rx = bna_rx_create(&bnad->bna, bnad, rx_config, &rx_cbfn, res_info,
			rx_info);
	अगर (!rx) अणु
		err = -ENOMEM;
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		जाओ err_वापस;
	पूर्ण
	rx_info->rx = rx;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	INIT_WORK(&rx_info->rx_cleanup_work,
			(work_func_t)(bnad_rx_cleanup));

	/*
	 * Init NAPI, so that state is set to NAPI_STATE_SCHED,
	 * so that IRQ handler cannot schedule NAPI at this poपूर्णांक.
	 */
	bnad_napi_add(bnad, rx_id);

	/* Register ISR क्रम the Rx object */
	अगर (पूर्णांकr_info->पूर्णांकr_type == BNA_INTR_T_MSIX) अणु
		err = bnad_rx_msix_रेजिस्टर(bnad, rx_info, rx_id,
						rx_config->num_paths);
		अगर (err)
			जाओ err_वापस;
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (0 == rx_id) अणु
		/* Set up Dynamic Interrupt Moderation Vector */
		अगर (bnad->cfg_flags & BNAD_CF_DIM_ENABLED)
			bna_rx_dim_reconfig(&bnad->bna, bna_napi_dim_vector);

		/* Enable VLAN filtering only on the शेष Rx */
		bna_rx_vlanfilter_enable(rx);

		/* Start the DIM समयr */
		bnad_dim_समयr_start(bnad);
	पूर्ण

	bna_rx_enable(rx);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	वापस 0;

err_वापस:
	bnad_destroy_rx(bnad, rx_id);
	वापस err;
पूर्ण

/* Called with conf_lock & bnad->bna_lock held */
व्योम
bnad_tx_coalescing_समयo_set(काष्ठा bnad *bnad)
अणु
	काष्ठा bnad_tx_info *tx_info;

	tx_info = &bnad->tx_info[0];
	अगर (!tx_info->tx)
		वापस;

	bna_tx_coalescing_समयo_set(tx_info->tx, bnad->tx_coalescing_समयo);
पूर्ण

/* Called with conf_lock & bnad->bna_lock held */
व्योम
bnad_rx_coalescing_समयo_set(काष्ठा bnad *bnad)
अणु
	काष्ठा bnad_rx_info *rx_info;
	पूर्णांक	i;

	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		rx_info = &bnad->rx_info[i];
		अगर (!rx_info->rx)
			जारी;
		bna_rx_coalescing_समयo_set(rx_info->rx,
				bnad->rx_coalescing_समयo);
	पूर्ण
पूर्ण

/*
 * Called with bnad->bna_lock held
 */
पूर्णांक
bnad_mac_addr_set_locked(काष्ठा bnad *bnad, स्थिर u8 *mac_addr)
अणु
	पूर्णांक ret;

	अगर (!is_valid_ether_addr(mac_addr))
		वापस -EADDRNOTAVAIL;

	/* If datapath is करोwn, pretend everything went through */
	अगर (!bnad->rx_info[0].rx)
		वापस 0;

	ret = bna_rx_ucast_set(bnad->rx_info[0].rx, mac_addr);
	अगर (ret != BNA_CB_SUCCESS)
		वापस -EADDRNOTAVAIL;

	वापस 0;
पूर्ण

/* Should be called with conf_lock held */
पूर्णांक
bnad_enable_शेष_bcast(काष्ठा bnad *bnad)
अणु
	काष्ठा bnad_rx_info *rx_info = &bnad->rx_info[0];
	पूर्णांक ret;
	अचिन्हित दीर्घ flags;

	init_completion(&bnad->bnad_completions.mcast_comp);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	ret = bna_rx_mcast_add(rx_info->rx, bnad_bcast_addr,
			       bnad_cb_rx_mcast_add);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	अगर (ret == BNA_CB_SUCCESS)
		रुको_क्रम_completion(&bnad->bnad_completions.mcast_comp);
	अन्यथा
		वापस -ENODEV;

	अगर (bnad->bnad_completions.mcast_comp_status != BNA_CB_SUCCESS)
		वापस -ENODEV;

	वापस 0;
पूर्ण

/* Called with mutex_lock(&bnad->conf_mutex) held */
व्योम
bnad_restore_vlans(काष्ठा bnad *bnad, u32 rx_id)
अणु
	u16 vid;
	अचिन्हित दीर्घ flags;

	क्रम_each_set_bit(vid, bnad->active_vlans, VLAN_N_VID) अणु
		spin_lock_irqsave(&bnad->bna_lock, flags);
		bna_rx_vlan_add(bnad->rx_info[rx_id].rx, vid);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
	पूर्ण
पूर्ण

/* Statistics utilities */
व्योम
bnad_netdev_qstats_fill(काष्ठा bnad *bnad, काष्ठा rtnl_link_stats64 *stats)
अणु
	पूर्णांक i, j;

	क्रम (i = 0; i < bnad->num_rx; i++) अणु
		क्रम (j = 0; j < bnad->num_rxp_per_rx; j++) अणु
			अगर (bnad->rx_info[i].rx_ctrl[j].ccb) अणु
				stats->rx_packets += bnad->rx_info[i].
				rx_ctrl[j].ccb->rcb[0]->rxq->rx_packets;
				stats->rx_bytes += bnad->rx_info[i].
					rx_ctrl[j].ccb->rcb[0]->rxq->rx_bytes;
				अगर (bnad->rx_info[i].rx_ctrl[j].ccb->rcb[1] &&
					bnad->rx_info[i].rx_ctrl[j].ccb->
					rcb[1]->rxq) अणु
					stats->rx_packets +=
						bnad->rx_info[i].rx_ctrl[j].
						ccb->rcb[1]->rxq->rx_packets;
					stats->rx_bytes +=
						bnad->rx_info[i].rx_ctrl[j].
						ccb->rcb[1]->rxq->rx_bytes;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण
	क्रम (i = 0; i < bnad->num_tx; i++) अणु
		क्रम (j = 0; j < bnad->num_txq_per_tx; j++) अणु
			अगर (bnad->tx_info[i].tcb[j]) अणु
				stats->tx_packets +=
				bnad->tx_info[i].tcb[j]->txq->tx_packets;
				stats->tx_bytes +=
					bnad->tx_info[i].tcb[j]->txq->tx_bytes;
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Must be called with the bna_lock held.
 */
व्योम
bnad_netdev_hwstats_fill(काष्ठा bnad *bnad, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा bfi_enet_stats_mac *mac_stats;
	u32 bmap;
	पूर्णांक i;

	mac_stats = &bnad->stats.bna_stats->hw_stats.mac_stats;
	stats->rx_errors =
		mac_stats->rx_fcs_error + mac_stats->rx_alignment_error +
		mac_stats->rx_frame_length_error + mac_stats->rx_code_error +
		mac_stats->rx_undersize;
	stats->tx_errors = mac_stats->tx_fcs_error +
					mac_stats->tx_undersize;
	stats->rx_dropped = mac_stats->rx_drop;
	stats->tx_dropped = mac_stats->tx_drop;
	stats->multicast = mac_stats->rx_multicast;
	stats->collisions = mac_stats->tx_total_collision;

	stats->rx_length_errors = mac_stats->rx_frame_length_error;

	/* receive ring buffer overflow  ?? */

	stats->rx_crc_errors = mac_stats->rx_fcs_error;
	stats->rx_frame_errors = mac_stats->rx_alignment_error;
	/* recv'r fअगरo overrun */
	bmap = bna_rx_rid_mask(&bnad->bna);
	क्रम (i = 0; bmap; i++) अणु
		अगर (bmap & 1) अणु
			stats->rx_fअगरo_errors +=
				bnad->stats.bna_stats->
					hw_stats.rxf_stats[i].frame_drops;
			अवरोध;
		पूर्ण
		bmap >>= 1;
	पूर्ण
पूर्ण

अटल व्योम
bnad_mbox_irq_sync(काष्ठा bnad *bnad)
अणु
	u32 irq;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (bnad->cfg_flags & BNAD_CF_MSIX)
		irq = bnad->msix_table[BNAD_MAILBOX_MSIX_INDEX].vector;
	अन्यथा
		irq = bnad->pcidev->irq;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	synchronize_irq(irq);
पूर्ण

/* Utility used by bnad_start_xmit, क्रम करोing TSO */
अटल पूर्णांक
bnad_tso_prepare(काष्ठा bnad *bnad, काष्ठा sk_buff *skb)
अणु
	पूर्णांक err;

	err = skb_cow_head(skb, 0);
	अगर (err < 0) अणु
		BNAD_UPDATE_CTR(bnad, tso_err);
		वापस err;
	पूर्ण

	/*
	 * For TSO, the TCP checksum field is seeded with pseuकरो-header sum
	 * excluding the length field.
	 */
	अगर (vlan_get_protocol(skb) == htons(ETH_P_IP)) अणु
		काष्ठा iphdr *iph = ip_hdr(skb);

		/* Do we really need these? */
		iph->tot_len = 0;
		iph->check = 0;

		tcp_hdr(skb)->check =
			~csum_tcpudp_magic(iph->saddr, iph->daddr, 0,
					   IPPROTO_TCP, 0);
		BNAD_UPDATE_CTR(bnad, tso4);
	पूर्ण अन्यथा अणु
		tcp_v6_gso_csum_prep(skb);
		BNAD_UPDATE_CTR(bnad, tso6);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Initialize Q numbers depending on Rx Paths
 * Called with bnad->bna_lock held, because of cfg_flags
 * access.
 */
अटल व्योम
bnad_q_num_init(काष्ठा bnad *bnad)
अणु
	पूर्णांक rxps;

	rxps = min((uपूर्णांक)num_online_cpus(),
			(uपूर्णांक)(BNAD_MAX_RX * BNAD_MAX_RXP_PER_RX));

	अगर (!(bnad->cfg_flags & BNAD_CF_MSIX))
		rxps = 1;	/* INTx */

	bnad->num_rx = 1;
	bnad->num_tx = 1;
	bnad->num_rxp_per_rx = rxps;
	bnad->num_txq_per_tx = BNAD_TXQ_NUM;
पूर्ण

/*
 * Adjusts the Q numbers, given a number of msix vectors
 * Give preference to RSS as opposed to Tx priority Queues,
 * in such a हाल, just use 1 Tx Q
 * Called with bnad->bna_lock held b'cos of cfg_flags access
 */
अटल व्योम
bnad_q_num_adjust(काष्ठा bnad *bnad, पूर्णांक msix_vectors, पूर्णांक temp)
अणु
	bnad->num_txq_per_tx = 1;
	अगर ((msix_vectors >= (bnad->num_tx * bnad->num_txq_per_tx)  +
	     bnad_rxqs_per_cq + BNAD_MAILBOX_MSIX_VECTORS) &&
	    (bnad->cfg_flags & BNAD_CF_MSIX)) अणु
		bnad->num_rxp_per_rx = msix_vectors -
			(bnad->num_tx * bnad->num_txq_per_tx) -
			BNAD_MAILBOX_MSIX_VECTORS;
	पूर्ण अन्यथा
		bnad->num_rxp_per_rx = 1;
पूर्ण

/* Enable / disable ioceth */
अटल पूर्णांक
bnad_ioceth_disable(काष्ठा bnad *bnad)
अणु
	अचिन्हित दीर्घ flags;
	पूर्णांक err = 0;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	init_completion(&bnad->bnad_completions.ioc_comp);
	bna_ioceth_disable(&bnad->bna.ioceth, BNA_HARD_CLEANUP);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	रुको_क्रम_completion_समयout(&bnad->bnad_completions.ioc_comp,
		msecs_to_jअगरfies(BNAD_IOCETH_TIMEOUT));

	err = bnad->bnad_completions.ioc_comp_status;
	वापस err;
पूर्ण

अटल पूर्णांक
bnad_ioceth_enable(काष्ठा bnad *bnad)
अणु
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	init_completion(&bnad->bnad_completions.ioc_comp);
	bnad->bnad_completions.ioc_comp_status = BNA_CB_WAITING;
	bna_ioceth_enable(&bnad->bna.ioceth);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	रुको_क्रम_completion_समयout(&bnad->bnad_completions.ioc_comp,
		msecs_to_jअगरfies(BNAD_IOCETH_TIMEOUT));

	err = bnad->bnad_completions.ioc_comp_status;

	वापस err;
पूर्ण

/* Free BNA resources */
अटल व्योम
bnad_res_मुक्त(काष्ठा bnad *bnad, काष्ठा bna_res_info *res_info,
		u32 res_val_max)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < res_val_max; i++)
		bnad_mem_मुक्त(bnad, &res_info[i].res_u.mem_info);
पूर्ण

/* Allocates memory and पूर्णांकerrupt resources क्रम BNA */
अटल पूर्णांक
bnad_res_alloc(काष्ठा bnad *bnad, काष्ठा bna_res_info *res_info,
		u32 res_val_max)
अणु
	पूर्णांक i, err;

	क्रम (i = 0; i < res_val_max; i++) अणु
		err = bnad_mem_alloc(bnad, &res_info[i].res_u.mem_info);
		अगर (err)
			जाओ err_वापस;
	पूर्ण
	वापस 0;

err_वापस:
	bnad_res_मुक्त(bnad, res_info, res_val_max);
	वापस err;
पूर्ण

/* Interrupt enable / disable */
अटल व्योम
bnad_enable_msix(काष्ठा bnad *bnad)
अणु
	पूर्णांक i, ret;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (!(bnad->cfg_flags & BNAD_CF_MSIX)) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		वापस;
	पूर्ण
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	अगर (bnad->msix_table)
		वापस;

	bnad->msix_table =
		kसुस्मृति(bnad->msix_num, माप(काष्ठा msix_entry), GFP_KERNEL);

	अगर (!bnad->msix_table)
		जाओ पूर्णांकx_mode;

	क्रम (i = 0; i < bnad->msix_num; i++)
		bnad->msix_table[i].entry = i;

	ret = pci_enable_msix_range(bnad->pcidev, bnad->msix_table,
				    1, bnad->msix_num);
	अगर (ret < 0) अणु
		जाओ पूर्णांकx_mode;
	पूर्ण अन्यथा अगर (ret < bnad->msix_num) अणु
		dev_warn(&bnad->pcidev->dev,
			 "%d MSI-X vectors allocated < %d requested\n",
			 ret, bnad->msix_num);

		spin_lock_irqsave(&bnad->bna_lock, flags);
		/* ret = #of vectors that we got */
		bnad_q_num_adjust(bnad, (ret - BNAD_MAILBOX_MSIX_VECTORS) / 2,
			(ret - BNAD_MAILBOX_MSIX_VECTORS) / 2);
		spin_unlock_irqrestore(&bnad->bna_lock, flags);

		bnad->msix_num = BNAD_NUM_TXQ + BNAD_NUM_RXP +
			 BNAD_MAILBOX_MSIX_VECTORS;

		अगर (bnad->msix_num > ret) अणु
			pci_disable_msix(bnad->pcidev);
			जाओ पूर्णांकx_mode;
		पूर्ण
	पूर्ण

	pci_पूर्णांकx(bnad->pcidev, 0);

	वापस;

पूर्णांकx_mode:
	dev_warn(&bnad->pcidev->dev,
		 "MSI-X enable failed - operating in INTx mode\n");

	kमुक्त(bnad->msix_table);
	bnad->msix_table = शून्य;
	bnad->msix_num = 0;
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bnad->cfg_flags &= ~BNAD_CF_MSIX;
	bnad_q_num_init(bnad);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

अटल व्योम
bnad_disable_msix(काष्ठा bnad *bnad)
अणु
	u32 cfg_flags;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	cfg_flags = bnad->cfg_flags;
	अगर (bnad->cfg_flags & BNAD_CF_MSIX)
		bnad->cfg_flags &= ~BNAD_CF_MSIX;
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	अगर (cfg_flags & BNAD_CF_MSIX) अणु
		pci_disable_msix(bnad->pcidev);
		kमुक्त(bnad->msix_table);
		bnad->msix_table = शून्य;
	पूर्ण
पूर्ण

/* Netdev entry poपूर्णांकs */
अटल पूर्णांक
bnad_खोलो(काष्ठा net_device *netdev)
अणु
	पूर्णांक err;
	काष्ठा bnad *bnad = netdev_priv(netdev);
	काष्ठा bna_छोड़ो_config छोड़ो_config;
	अचिन्हित दीर्घ flags;

	mutex_lock(&bnad->conf_mutex);

	/* Tx */
	err = bnad_setup_tx(bnad, 0);
	अगर (err)
		जाओ err_वापस;

	/* Rx */
	err = bnad_setup_rx(bnad, 0);
	अगर (err)
		जाओ cleanup_tx;

	/* Port */
	छोड़ो_config.tx_छोड़ो = 0;
	छोड़ो_config.rx_छोड़ो = 0;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_enet_mtu_set(&bnad->bna.enet,
			 BNAD_FRAME_SIZE(bnad->netdev->mtu), शून्य);
	bna_enet_छोड़ो_config(&bnad->bna.enet, &छोड़ो_config);
	bna_enet_enable(&bnad->bna.enet);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Enable broadcast */
	bnad_enable_शेष_bcast(bnad);

	/* Restore VLANs, अगर any */
	bnad_restore_vlans(bnad, 0);

	/* Set the UCAST address */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bnad_mac_addr_set_locked(bnad, netdev->dev_addr);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Start the stats समयr */
	bnad_stats_समयr_start(bnad);

	mutex_unlock(&bnad->conf_mutex);

	वापस 0;

cleanup_tx:
	bnad_destroy_tx(bnad, 0);

err_वापस:
	mutex_unlock(&bnad->conf_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक
bnad_stop(काष्ठा net_device *netdev)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	mutex_lock(&bnad->conf_mutex);

	/* Stop the stats समयr */
	bnad_stats_समयr_stop(bnad);

	init_completion(&bnad->bnad_completions.enet_comp);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_enet_disable(&bnad->bna.enet, BNA_HARD_CLEANUP,
			bnad_cb_enet_disabled);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	रुको_क्रम_completion(&bnad->bnad_completions.enet_comp);

	bnad_destroy_tx(bnad, 0);
	bnad_destroy_rx(bnad, 0);

	/* Synchronize mailbox IRQ */
	bnad_mbox_irq_sync(bnad);

	mutex_unlock(&bnad->conf_mutex);

	वापस 0;
पूर्ण

/* TX */
/* Returns 0 क्रम success */
अटल पूर्णांक
bnad_txq_wi_prepare(काष्ठा bnad *bnad, काष्ठा bna_tcb *tcb,
		    काष्ठा sk_buff *skb, काष्ठा bna_txq_entry *txqent)
अणु
	u16 flags = 0;
	u32 gso_size;
	u16 vlan_tag = 0;

	अगर (skb_vlan_tag_present(skb)) अणु
		vlan_tag = (u16)skb_vlan_tag_get(skb);
		flags |= (BNA_TXQ_WI_CF_INS_PRIO | BNA_TXQ_WI_CF_INS_VLAN);
	पूर्ण
	अगर (test_bit(BNAD_RF_CEE_RUNNING, &bnad->run_flags)) अणु
		vlan_tag = ((tcb->priority & 0x7) << VLAN_PRIO_SHIFT)
				| (vlan_tag & 0x1fff);
		flags |= (BNA_TXQ_WI_CF_INS_PRIO | BNA_TXQ_WI_CF_INS_VLAN);
	पूर्ण
	txqent->hdr.wi.vlan_tag = htons(vlan_tag);

	अगर (skb_is_gso(skb)) अणु
		gso_size = skb_shinfo(skb)->gso_size;
		अगर (unlikely(gso_size > bnad->netdev->mtu)) अणु
			BNAD_UPDATE_CTR(bnad, tx_skb_mss_too_दीर्घ);
			वापस -EINVAL;
		पूर्ण
		अगर (unlikely((gso_size + skb_transport_offset(skb) +
			      tcp_hdrlen(skb)) >= skb->len)) अणु
			txqent->hdr.wi.opcode = htons(BNA_TXQ_WI_SEND);
			txqent->hdr.wi.lso_mss = 0;
			BNAD_UPDATE_CTR(bnad, tx_skb_tso_too_लघु);
		पूर्ण अन्यथा अणु
			txqent->hdr.wi.opcode = htons(BNA_TXQ_WI_SEND_LSO);
			txqent->hdr.wi.lso_mss = htons(gso_size);
		पूर्ण

		अगर (bnad_tso_prepare(bnad, skb)) अणु
			BNAD_UPDATE_CTR(bnad, tx_skb_tso_prepare);
			वापस -EINVAL;
		पूर्ण

		flags |= (BNA_TXQ_WI_CF_IP_CKSUM | BNA_TXQ_WI_CF_TCP_CKSUM);
		txqent->hdr.wi.l4_hdr_size_n_offset =
			htons(BNA_TXQ_WI_L4_HDR_N_OFFSET(
			tcp_hdrlen(skb) >> 2, skb_transport_offset(skb)));
	पूर्ण अन्यथा  अणु
		txqent->hdr.wi.opcode =	htons(BNA_TXQ_WI_SEND);
		txqent->hdr.wi.lso_mss = 0;

		अगर (unlikely(skb->len > (bnad->netdev->mtu + VLAN_ETH_HLEN))) अणु
			BNAD_UPDATE_CTR(bnad, tx_skb_non_tso_too_दीर्घ);
			वापस -EINVAL;
		पूर्ण

		अगर (skb->ip_summed == CHECKSUM_PARTIAL) अणु
			__be16 net_proto = vlan_get_protocol(skb);
			u8 proto = 0;

			अगर (net_proto == htons(ETH_P_IP))
				proto = ip_hdr(skb)->protocol;
#अगर_घोषित NETIF_F_IPV6_CSUM
			अन्यथा अगर (net_proto == htons(ETH_P_IPV6)) अणु
				/* nexthdr may not be TCP immediately. */
				proto = ipv6_hdr(skb)->nexthdr;
			पूर्ण
#पूर्ण_अगर
			अगर (proto == IPPROTO_TCP) अणु
				flags |= BNA_TXQ_WI_CF_TCP_CKSUM;
				txqent->hdr.wi.l4_hdr_size_n_offset =
					htons(BNA_TXQ_WI_L4_HDR_N_OFFSET
					      (0, skb_transport_offset(skb)));

				BNAD_UPDATE_CTR(bnad, tcpcsum_offload);

				अगर (unlikely(skb_headlen(skb) <
					    skb_transport_offset(skb) +
				    tcp_hdrlen(skb))) अणु
					BNAD_UPDATE_CTR(bnad, tx_skb_tcp_hdr);
					वापस -EINVAL;
				पूर्ण
			पूर्ण अन्यथा अगर (proto == IPPROTO_UDP) अणु
				flags |= BNA_TXQ_WI_CF_UDP_CKSUM;
				txqent->hdr.wi.l4_hdr_size_n_offset =
					htons(BNA_TXQ_WI_L4_HDR_N_OFFSET
					      (0, skb_transport_offset(skb)));

				BNAD_UPDATE_CTR(bnad, udpcsum_offload);
				अगर (unlikely(skb_headlen(skb) <
					    skb_transport_offset(skb) +
				    माप(काष्ठा udphdr))) अणु
					BNAD_UPDATE_CTR(bnad, tx_skb_udp_hdr);
					वापस -EINVAL;
				पूर्ण
			पूर्ण अन्यथा अणु

				BNAD_UPDATE_CTR(bnad, tx_skb_csum_err);
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा
			txqent->hdr.wi.l4_hdr_size_n_offset = 0;
	पूर्ण

	txqent->hdr.wi.flags = htons(flags);
	txqent->hdr.wi.frame_length = htonl(skb->len);

	वापस 0;
पूर्ण

/*
 * bnad_start_xmit : Netdev entry poपूर्णांक क्रम Transmit
 *		     Called under lock held by net_device
 */
अटल netdev_tx_t
bnad_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	u32 txq_id = 0;
	काष्ठा bna_tcb *tcb = शून्य;
	काष्ठा bnad_tx_unmap *unmap_q, *unmap, *head_unmap;
	u32		prod, q_depth, vect_id;
	u32		wis, vectors, len;
	पूर्णांक		i;
	dma_addr_t		dma_addr;
	काष्ठा bna_txq_entry *txqent;

	len = skb_headlen(skb);

	/* Sanity checks क्रम the skb */

	अगर (unlikely(skb->len <= ETH_HLEN)) अणु
		dev_kमुक्त_skb_any(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_too_लघु);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (unlikely(len > BFI_TX_MAX_DATA_PER_VECTOR)) अणु
		dev_kमुक्त_skb_any(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_headlen_zero);
		वापस NETDEV_TX_OK;
	पूर्ण
	अगर (unlikely(len == 0)) अणु
		dev_kमुक्त_skb_any(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_headlen_zero);
		वापस NETDEV_TX_OK;
	पूर्ण

	tcb = bnad->tx_info[0].tcb[txq_id];

	/*
	 * Takes care of the Tx that is scheduled between clearing the flag
	 * and the netअगर_tx_stop_all_queues() call.
	 */
	अगर (unlikely(!tcb || !test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags))) अणु
		dev_kमुक्त_skb_any(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_stopping);
		वापस NETDEV_TX_OK;
	पूर्ण

	q_depth = tcb->q_depth;
	prod = tcb->producer_index;
	unmap_q = tcb->unmap_q;

	vectors = 1 + skb_shinfo(skb)->nr_frags;
	wis = BNA_TXQ_WI_NEEDED(vectors);	/* 4 vectors per work item */

	अगर (unlikely(vectors > BFI_TX_MAX_VECTORS_PER_PKT)) अणु
		dev_kमुक्त_skb_any(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_max_vectors);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Check क्रम available TxQ resources */
	अगर (unlikely(wis > BNA_QE_FREE_CNT(tcb, q_depth))) अणु
		अगर ((*tcb->hw_consumer_index != tcb->consumer_index) &&
		    !test_and_set_bit(BNAD_TXQ_FREE_SENT, &tcb->flags)) अणु
			u32 sent;
			sent = bnad_txcmpl_process(bnad, tcb);
			अगर (likely(test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags)))
				bna_ib_ack(tcb->i_dbell, sent);
			smp_mb__beक्रमe_atomic();
			clear_bit(BNAD_TXQ_FREE_SENT, &tcb->flags);
		पूर्ण अन्यथा अणु
			netअगर_stop_queue(netdev);
			BNAD_UPDATE_CTR(bnad, netअगर_queue_stop);
		पूर्ण

		smp_mb();
		/*
		 * Check again to deal with race condition between
		 * netअगर_stop_queue here, and netअगर_wake_queue in
		 * पूर्णांकerrupt handler which is not inside netअगर tx lock.
		 */
		अगर (likely(wis > BNA_QE_FREE_CNT(tcb, q_depth))) अणु
			BNAD_UPDATE_CTR(bnad, netअगर_queue_stop);
			वापस NETDEV_TX_BUSY;
		पूर्ण अन्यथा अणु
			netअगर_wake_queue(netdev);
			BNAD_UPDATE_CTR(bnad, netअगर_queue_wakeup);
		पूर्ण
	पूर्ण

	txqent = &((काष्ठा bna_txq_entry *)tcb->sw_q)[prod];
	head_unmap = &unmap_q[prod];

	/* Program the opcode, flags, frame_len, num_vectors in WI */
	अगर (bnad_txq_wi_prepare(bnad, tcb, skb, txqent)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण
	txqent->hdr.wi.reserved = 0;
	txqent->hdr.wi.num_vectors = vectors;

	head_unmap->skb = skb;
	head_unmap->nvecs = 0;

	/* Program the vectors */
	unmap = head_unmap;
	dma_addr = dma_map_single(&bnad->pcidev->dev, skb->data,
				  len, DMA_TO_DEVICE);
	अगर (dma_mapping_error(&bnad->pcidev->dev, dma_addr)) अणु
		dev_kमुक्त_skb_any(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_map_failed);
		वापस NETDEV_TX_OK;
	पूर्ण
	BNA_SET_DMA_ADDR(dma_addr, &txqent->vector[0].host_addr);
	txqent->vector[0].length = htons(len);
	dma_unmap_addr_set(&unmap->vectors[0], dma_addr, dma_addr);
	head_unmap->nvecs++;

	क्रम (i = 0, vect_id = 0; i < vectors - 1; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];
		u32		size = skb_frag_size(frag);

		अगर (unlikely(size == 0)) अणु
			/* Unकरो the changes starting at tcb->producer_index */
			bnad_tx_buff_unmap(bnad, unmap_q, q_depth,
				tcb->producer_index);
			dev_kमुक्त_skb_any(skb);
			BNAD_UPDATE_CTR(bnad, tx_skb_frag_zero);
			वापस NETDEV_TX_OK;
		पूर्ण

		len += size;

		vect_id++;
		अगर (vect_id == BFI_TX_MAX_VECTORS_PER_WI) अणु
			vect_id = 0;
			BNA_QE_INDX_INC(prod, q_depth);
			txqent = &((काष्ठा bna_txq_entry *)tcb->sw_q)[prod];
			txqent->hdr.wi_ext.opcode = htons(BNA_TXQ_WI_EXTENSION);
			unmap = &unmap_q[prod];
		पूर्ण

		dma_addr = skb_frag_dma_map(&bnad->pcidev->dev, frag,
					    0, size, DMA_TO_DEVICE);
		अगर (dma_mapping_error(&bnad->pcidev->dev, dma_addr)) अणु
			/* Unकरो the changes starting at tcb->producer_index */
			bnad_tx_buff_unmap(bnad, unmap_q, q_depth,
					   tcb->producer_index);
			dev_kमुक्त_skb_any(skb);
			BNAD_UPDATE_CTR(bnad, tx_skb_map_failed);
			वापस NETDEV_TX_OK;
		पूर्ण

		dma_unmap_len_set(&unmap->vectors[vect_id], dma_len, size);
		BNA_SET_DMA_ADDR(dma_addr, &txqent->vector[vect_id].host_addr);
		txqent->vector[vect_id].length = htons(size);
		dma_unmap_addr_set(&unmap->vectors[vect_id], dma_addr,
				   dma_addr);
		head_unmap->nvecs++;
	पूर्ण

	अगर (unlikely(len != skb->len)) अणु
		/* Unकरो the changes starting at tcb->producer_index */
		bnad_tx_buff_unmap(bnad, unmap_q, q_depth, tcb->producer_index);
		dev_kमुक्त_skb_any(skb);
		BNAD_UPDATE_CTR(bnad, tx_skb_len_mismatch);
		वापस NETDEV_TX_OK;
	पूर्ण

	BNA_QE_INDX_INC(prod, q_depth);
	tcb->producer_index = prod;

	wmb();

	अगर (unlikely(!test_bit(BNAD_TXQ_TX_STARTED, &tcb->flags)))
		वापस NETDEV_TX_OK;

	skb_tx_बारtamp(skb);

	bna_txq_prod_indx_करोorbell(tcb);

	वापस NETDEV_TX_OK;
पूर्ण

/*
 * Used spin_lock to synchronize पढ़ोing of stats काष्ठाures, which
 * is written by BNA under the same lock.
 */
अटल व्योम
bnad_get_stats64(काष्ठा net_device *netdev, काष्ठा rtnl_link_stats64 *stats)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);

	bnad_netdev_qstats_fill(bnad, stats);
	bnad_netdev_hwstats_fill(bnad, stats);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

अटल व्योम
bnad_set_rx_ucast_fltr(काष्ठा bnad *bnad)
अणु
	काष्ठा net_device *netdev = bnad->netdev;
	पूर्णांक uc_count = netdev_uc_count(netdev);
	क्रमागत bna_cb_status ret;
	u8 *mac_list;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक entry;

	अगर (netdev_uc_empty(bnad->netdev)) अणु
		bna_rx_ucast_listset(bnad->rx_info[0].rx, 0, शून्य);
		वापस;
	पूर्ण

	अगर (uc_count > bna_attr(&bnad->bna)->num_ucmac)
		जाओ mode_शेष;

	mac_list = kसुस्मृति(ETH_ALEN, uc_count, GFP_ATOMIC);
	अगर (mac_list == शून्य)
		जाओ mode_शेष;

	entry = 0;
	netdev_क्रम_each_uc_addr(ha, netdev) अणु
		ether_addr_copy(&mac_list[entry * ETH_ALEN], &ha->addr[0]);
		entry++;
	पूर्ण

	ret = bna_rx_ucast_listset(bnad->rx_info[0].rx, entry, mac_list);
	kमुक्त(mac_list);

	अगर (ret != BNA_CB_SUCCESS)
		जाओ mode_शेष;

	वापस;

	/* ucast packets not in UCAM are routed to शेष function */
mode_शेष:
	bnad->cfg_flags |= BNAD_CF_DEFAULT;
	bna_rx_ucast_listset(bnad->rx_info[0].rx, 0, शून्य);
पूर्ण

अटल व्योम
bnad_set_rx_mcast_fltr(काष्ठा bnad *bnad)
अणु
	काष्ठा net_device *netdev = bnad->netdev;
	पूर्णांक mc_count = netdev_mc_count(netdev);
	क्रमागत bna_cb_status ret;
	u8 *mac_list;

	अगर (netdev->flags & IFF_ALLMULTI)
		जाओ mode_allmulti;

	अगर (netdev_mc_empty(netdev))
		वापस;

	अगर (mc_count > bna_attr(&bnad->bna)->num_mcmac)
		जाओ mode_allmulti;

	mac_list = kसुस्मृति(mc_count + 1, ETH_ALEN, GFP_ATOMIC);

	अगर (mac_list == शून्य)
		जाओ mode_allmulti;

	ether_addr_copy(&mac_list[0], &bnad_bcast_addr[0]);

	/* copy rest of the MCAST addresses */
	bnad_netdev_mc_list_get(netdev, mac_list);
	ret = bna_rx_mcast_listset(bnad->rx_info[0].rx, mc_count + 1, mac_list);
	kमुक्त(mac_list);

	अगर (ret != BNA_CB_SUCCESS)
		जाओ mode_allmulti;

	वापस;

mode_allmulti:
	bnad->cfg_flags |= BNAD_CF_ALLMULTI;
	bna_rx_mcast_delall(bnad->rx_info[0].rx);
पूर्ण

व्योम
bnad_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	क्रमागत bna_rxmode new_mode, mode_mask;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);

	अगर (bnad->rx_info[0].rx == शून्य) अणु
		spin_unlock_irqrestore(&bnad->bna_lock, flags);
		वापस;
	पूर्ण

	/* clear bnad flags to update it with new settings */
	bnad->cfg_flags &= ~(BNAD_CF_PROMISC | BNAD_CF_DEFAULT |
			BNAD_CF_ALLMULTI);

	new_mode = 0;
	अगर (netdev->flags & IFF_PROMISC) अणु
		new_mode |= BNAD_RXMODE_PROMISC_DEFAULT;
		bnad->cfg_flags |= BNAD_CF_PROMISC;
	पूर्ण अन्यथा अणु
		bnad_set_rx_mcast_fltr(bnad);

		अगर (bnad->cfg_flags & BNAD_CF_ALLMULTI)
			new_mode |= BNA_RXMODE_ALLMULTI;

		bnad_set_rx_ucast_fltr(bnad);

		अगर (bnad->cfg_flags & BNAD_CF_DEFAULT)
			new_mode |= BNA_RXMODE_DEFAULT;
	पूर्ण

	mode_mask = BNA_RXMODE_PROMISC | BNA_RXMODE_DEFAULT |
			BNA_RXMODE_ALLMULTI;
	bna_rx_mode_set(bnad->rx_info[0].rx, new_mode, mode_mask);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);
पूर्ण

/*
 * bna_lock is used to sync ग_लिखोs to netdev->addr
 * conf_lock cannot be used since this call may be made
 * in a non-blocking context.
 */
अटल पूर्णांक
bnad_set_mac_address(काष्ठा net_device *netdev, व्योम *addr)
अणु
	पूर्णांक err;
	काष्ठा bnad *bnad = netdev_priv(netdev);
	काष्ठा sockaddr *sa = (काष्ठा sockaddr *)addr;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&bnad->bna_lock, flags);

	err = bnad_mac_addr_set_locked(bnad, sa->sa_data);
	अगर (!err)
		ether_addr_copy(netdev->dev_addr, sa->sa_data);

	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	वापस err;
पूर्ण

अटल पूर्णांक
bnad_mtu_set(काष्ठा bnad *bnad, पूर्णांक frame_size)
अणु
	अचिन्हित दीर्घ flags;

	init_completion(&bnad->bnad_completions.mtu_comp);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_enet_mtu_set(&bnad->bna.enet, frame_size, bnad_cb_enet_mtu_set);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	रुको_क्रम_completion(&bnad->bnad_completions.mtu_comp);

	वापस bnad->bnad_completions.mtu_comp_status;
पूर्ण

अटल पूर्णांक
bnad_change_mtu(काष्ठा net_device *netdev, पूर्णांक new_mtu)
अणु
	पूर्णांक err, mtu;
	काष्ठा bnad *bnad = netdev_priv(netdev);
	u32 frame, new_frame;

	mutex_lock(&bnad->conf_mutex);

	mtu = netdev->mtu;
	netdev->mtu = new_mtu;

	frame = BNAD_FRAME_SIZE(mtu);
	new_frame = BNAD_FRAME_SIZE(new_mtu);

	/* check अगर multi-buffer needs to be enabled */
	अगर (BNAD_PCI_DEV_IS_CAT2(bnad) &&
	    netअगर_running(bnad->netdev)) अणु
		/* only when transition is over 4K */
		अगर ((frame <= 4096 && new_frame > 4096) ||
		    (frame > 4096 && new_frame <= 4096))
			bnad_reinit_rx(bnad);
	पूर्ण

	err = bnad_mtu_set(bnad, new_frame);
	अगर (err)
		err = -EBUSY;

	mutex_unlock(&bnad->conf_mutex);
	वापस err;
पूर्ण

अटल पूर्णांक
bnad_vlan_rx_add_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	अगर (!bnad->rx_info[0].rx)
		वापस 0;

	mutex_lock(&bnad->conf_mutex);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_rx_vlan_add(bnad->rx_info[0].rx, vid);
	set_bit(vid, bnad->active_vlans);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	mutex_unlock(&bnad->conf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक
bnad_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev, __be16 proto, u16 vid)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	अचिन्हित दीर्घ flags;

	अगर (!bnad->rx_info[0].rx)
		वापस 0;

	mutex_lock(&bnad->conf_mutex);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	clear_bit(vid, bnad->active_vlans);
	bna_rx_vlan_del(bnad->rx_info[0].rx, vid);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	mutex_unlock(&bnad->conf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक bnad_set_features(काष्ठा net_device *dev, netdev_features_t features)
अणु
	काष्ठा bnad *bnad = netdev_priv(dev);
	netdev_features_t changed = features ^ dev->features;

	अगर ((changed & NETIF_F_HW_VLAN_CTAG_RX) && netअगर_running(dev)) अणु
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&bnad->bna_lock, flags);

		अगर (features & NETIF_F_HW_VLAN_CTAG_RX)
			bna_rx_vlan_strip_enable(bnad->rx_info[0].rx);
		अन्यथा
			bna_rx_vlan_strip_disable(bnad->rx_info[0].rx);

		spin_unlock_irqrestore(&bnad->bna_lock, flags);
	पूर्ण

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम
bnad_netpoll(काष्ठा net_device *netdev)
अणु
	काष्ठा bnad *bnad = netdev_priv(netdev);
	काष्ठा bnad_rx_info *rx_info;
	काष्ठा bnad_rx_ctrl *rx_ctrl;
	u32 curr_mask;
	पूर्णांक i, j;

	अगर (!(bnad->cfg_flags & BNAD_CF_MSIX)) अणु
		bna_पूर्णांकx_disable(&bnad->bna, curr_mask);
		bnad_isr(bnad->pcidev->irq, netdev);
		bna_पूर्णांकx_enable(&bnad->bna, curr_mask);
	पूर्ण अन्यथा अणु
		/*
		 * Tx processing may happen in sending context, so no need
		 * to explicitly process completions here
		 */

		/* Rx processing */
		क्रम (i = 0; i < bnad->num_rx; i++) अणु
			rx_info = &bnad->rx_info[i];
			अगर (!rx_info->rx)
				जारी;
			क्रम (j = 0; j < bnad->num_rxp_per_rx; j++) अणु
				rx_ctrl = &rx_info->rx_ctrl[j];
				अगर (rx_ctrl->ccb)
					bnad_netअगर_rx_schedule_poll(bnad,
							    rx_ctrl->ccb);
			पूर्ण
		पूर्ण
	पूर्ण
पूर्ण
#पूर्ण_अगर

अटल स्थिर काष्ठा net_device_ops bnad_netdev_ops = अणु
	.nकरो_खोलो		= bnad_खोलो,
	.nकरो_stop		= bnad_stop,
	.nकरो_start_xmit		= bnad_start_xmit,
	.nकरो_get_stats64	= bnad_get_stats64,
	.nकरो_set_rx_mode	= bnad_set_rx_mode,
	.nकरो_validate_addr      = eth_validate_addr,
	.nकरो_set_mac_address    = bnad_set_mac_address,
	.nकरो_change_mtu		= bnad_change_mtu,
	.nकरो_vlan_rx_add_vid    = bnad_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid   = bnad_vlan_rx_समाप्त_vid,
	.nकरो_set_features	= bnad_set_features,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller    = bnad_netpoll
#पूर्ण_अगर
पूर्ण;

अटल व्योम
bnad_netdev_init(काष्ठा bnad *bnad, bool using_dac)
अणु
	काष्ठा net_device *netdev = bnad->netdev;

	netdev->hw_features = NETIF_F_SG | NETIF_F_RXCSUM |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_TSO | NETIF_F_TSO6 | NETIF_F_HW_VLAN_CTAG_TX |
		NETIF_F_HW_VLAN_CTAG_RX;

	netdev->vlan_features = NETIF_F_SG | NETIF_F_HIGHDMA |
		NETIF_F_IP_CSUM | NETIF_F_IPV6_CSUM |
		NETIF_F_TSO | NETIF_F_TSO6;

	netdev->features |= netdev->hw_features | NETIF_F_HW_VLAN_CTAG_FILTER;

	अगर (using_dac)
		netdev->features |= NETIF_F_HIGHDMA;

	netdev->mem_start = bnad->mmio_start;
	netdev->mem_end = bnad->mmio_start + bnad->mmio_len - 1;

	/* MTU range: 46 - 9000 */
	netdev->min_mtu = ETH_ZLEN - ETH_HLEN;
	netdev->max_mtu = BNAD_JUMBO_MTU;

	netdev->netdev_ops = &bnad_netdev_ops;
	bnad_set_ethtool_ops(netdev);
पूर्ण

/*
 * 1. Initialize the bnad काष्ठाure
 * 2. Setup netdev poपूर्णांकer in pci_dev
 * 3. Initialize no. of TxQ & CQs & MSIX vectors
 * 4. Initialize work queue.
 */
अटल पूर्णांक
bnad_init(काष्ठा bnad *bnad,
	  काष्ठा pci_dev *pdev, काष्ठा net_device *netdev)
अणु
	अचिन्हित दीर्घ flags;

	SET_NETDEV_DEV(netdev, &pdev->dev);
	pci_set_drvdata(pdev, netdev);

	bnad->netdev = netdev;
	bnad->pcidev = pdev;
	bnad->mmio_start = pci_resource_start(pdev, 0);
	bnad->mmio_len = pci_resource_len(pdev, 0);
	bnad->bar0 = ioremap(bnad->mmio_start, bnad->mmio_len);
	अगर (!bnad->bar0) अणु
		dev_err(&pdev->dev, "ioremap for bar0 failed\n");
		वापस -ENOMEM;
	पूर्ण
	dev_info(&pdev->dev, "bar0 mapped to %p, len %llu\n", bnad->bar0,
		 (अचिन्हित दीर्घ दीर्घ) bnad->mmio_len);

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (!bnad_msix_disable)
		bnad->cfg_flags = BNAD_CF_MSIX;

	bnad->cfg_flags |= BNAD_CF_DIM_ENABLED;

	bnad_q_num_init(bnad);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	bnad->msix_num = (bnad->num_tx * bnad->num_txq_per_tx) +
		(bnad->num_rx * bnad->num_rxp_per_rx) +
			 BNAD_MAILBOX_MSIX_VECTORS;

	bnad->txq_depth = BNAD_TXQ_DEPTH;
	bnad->rxq_depth = BNAD_RXQ_DEPTH;

	bnad->tx_coalescing_समयo = BFI_TX_COALESCING_TIMEO;
	bnad->rx_coalescing_समयo = BFI_RX_COALESCING_TIMEO;

	प्र_लिखो(bnad->wq_name, "%s_wq_%d", BNAD_NAME, bnad->id);
	bnad->work_q = create_singlethपढ़ो_workqueue(bnad->wq_name);
	अगर (!bnad->work_q) अणु
		iounmap(bnad->bar0);
		वापस -ENOMEM;
	पूर्ण

	वापस 0;
पूर्ण

/*
 * Must be called after bnad_pci_uninit()
 * so that iounmap() and pci_set_drvdata(शून्य)
 * happens only after PCI uninitialization.
 */
अटल व्योम
bnad_uninit(काष्ठा bnad *bnad)
अणु
	अगर (bnad->work_q) अणु
		flush_workqueue(bnad->work_q);
		destroy_workqueue(bnad->work_q);
		bnad->work_q = शून्य;
	पूर्ण

	अगर (bnad->bar0)
		iounmap(bnad->bar0);
पूर्ण

/*
 * Initialize locks
	a) Per ioceth mutes used क्रम serializing configuration
	   changes from OS पूर्णांकerface
	b) spin lock used to protect bna state machine
 */
अटल व्योम
bnad_lock_init(काष्ठा bnad *bnad)
अणु
	spin_lock_init(&bnad->bna_lock);
	mutex_init(&bnad->conf_mutex);
पूर्ण

अटल व्योम
bnad_lock_uninit(काष्ठा bnad *bnad)
अणु
	mutex_destroy(&bnad->conf_mutex);
पूर्ण

/* PCI Initialization */
अटल पूर्णांक
bnad_pci_init(काष्ठा bnad *bnad,
	      काष्ठा pci_dev *pdev, bool *using_dac)
अणु
	पूर्णांक err;

	err = pci_enable_device(pdev);
	अगर (err)
		वापस err;
	err = pci_request_regions(pdev, BNAD_NAME);
	अगर (err)
		जाओ disable_device;
	अगर (!dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(64))) अणु
		*using_dac = true;
	पूर्ण अन्यथा अणु
		err = dma_set_mask_and_coherent(&pdev->dev, DMA_BIT_MASK(32));
		अगर (err)
			जाओ release_regions;
		*using_dac = false;
	पूर्ण
	pci_set_master(pdev);
	वापस 0;

release_regions:
	pci_release_regions(pdev);
disable_device:
	pci_disable_device(pdev);

	वापस err;
पूर्ण

अटल व्योम
bnad_pci_uninit(काष्ठा pci_dev *pdev)
अणु
	pci_release_regions(pdev);
	pci_disable_device(pdev);
पूर्ण

अटल पूर्णांक
bnad_pci_probe(काष्ठा pci_dev *pdev,
		स्थिर काष्ठा pci_device_id *pcidev_id)
अणु
	bool	using_dac;
	पूर्णांक	err;
	काष्ठा bnad *bnad;
	काष्ठा bna *bna;
	काष्ठा net_device *netdev;
	काष्ठा bfa_pcidev pcidev_info;
	अचिन्हित दीर्घ flags;

	mutex_lock(&bnad_fwimg_mutex);
	अगर (!cna_get_firmware_buf(pdev)) अणु
		mutex_unlock(&bnad_fwimg_mutex);
		dev_err(&pdev->dev, "failed to load firmware image!\n");
		वापस -ENODEV;
	पूर्ण
	mutex_unlock(&bnad_fwimg_mutex);

	/*
	 * Allocates माप(काष्ठा net_device + काष्ठा bnad)
	 * bnad = netdev->priv
	 */
	netdev = alloc_etherdev(माप(काष्ठा bnad));
	अगर (!netdev) अणु
		err = -ENOMEM;
		वापस err;
	पूर्ण
	bnad = netdev_priv(netdev);
	bnad_lock_init(bnad);
	bnad->id = atomic_inc_वापस(&bna_id) - 1;

	mutex_lock(&bnad->conf_mutex);
	/*
	 * PCI initialization
	 *	Output : using_dac = 1 क्रम 64 bit DMA
	 *			   = 0 क्रम 32 bit DMA
	 */
	using_dac = false;
	err = bnad_pci_init(bnad, pdev, &using_dac);
	अगर (err)
		जाओ unlock_mutex;

	/*
	 * Initialize bnad काष्ठाure
	 * Setup relation between pci_dev & netdev
	 */
	err = bnad_init(bnad, pdev, netdev);
	अगर (err)
		जाओ pci_uninit;

	/* Initialize netdev काष्ठाure, set up ethtool ops */
	bnad_netdev_init(bnad, using_dac);

	/* Set link to करोwn state */
	netअगर_carrier_off(netdev);

	/* Setup the debugfs node क्रम this bfad */
	अगर (bna_debugfs_enable)
		bnad_debugfs_init(bnad);

	/* Get resource requirement क्रमm bna */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_res_req(&bnad->res_info[0]);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Allocate resources from bna */
	err = bnad_res_alloc(bnad, &bnad->res_info[0], BNA_RES_T_MAX);
	अगर (err)
		जाओ drv_uninit;

	bna = &bnad->bna;

	/* Setup pcidev_info क्रम bna_init() */
	pcidev_info.pci_slot = PCI_SLOT(bnad->pcidev->devfn);
	pcidev_info.pci_func = PCI_FUNC(bnad->pcidev->devfn);
	pcidev_info.device_id = bnad->pcidev->device;
	pcidev_info.pci_bar_kva = bnad->bar0;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_init(bna, bnad, &pcidev_info, &bnad->res_info[0]);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	bnad->stats.bna_stats = &bna->stats;

	bnad_enable_msix(bnad);
	err = bnad_mbox_irq_alloc(bnad);
	अगर (err)
		जाओ res_मुक्त;

	/* Set up समयrs */
	समयr_setup(&bnad->bna.ioceth.ioc.ioc_समयr, bnad_ioc_समयout, 0);
	समयr_setup(&bnad->bna.ioceth.ioc.hb_समयr, bnad_ioc_hb_check, 0);
	समयr_setup(&bnad->bna.ioceth.ioc.iocpf_समयr, bnad_iocpf_समयout, 0);
	समयr_setup(&bnad->bna.ioceth.ioc.sem_समयr, bnad_iocpf_sem_समयout,
		    0);

	/*
	 * Start the chip
	 * If the call back comes with error, we bail out.
	 * This is a catastrophic error.
	 */
	err = bnad_ioceth_enable(bnad);
	अगर (err) अणु
		dev_err(&pdev->dev, "initialization failed err=%d\n", err);
		जाओ probe_success;
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	अगर (bna_num_txq_set(bna, BNAD_NUM_TXQ + 1) ||
		bna_num_rxp_set(bna, BNAD_NUM_RXP + 1)) अणु
		bnad_q_num_adjust(bnad, bna_attr(bna)->num_txq - 1,
			bna_attr(bna)->num_rxp - 1);
		अगर (bna_num_txq_set(bna, BNAD_NUM_TXQ + 1) ||
			bna_num_rxp_set(bna, BNAD_NUM_RXP + 1))
			err = -EIO;
	पूर्ण
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	अगर (err)
		जाओ disable_ioceth;

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_mod_res_req(&bnad->bna, &bnad->mod_res_info[0]);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	err = bnad_res_alloc(bnad, &bnad->mod_res_info[0], BNA_MOD_RES_T_MAX);
	अगर (err) अणु
		err = -EIO;
		जाओ disable_ioceth;
	पूर्ण

	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_mod_init(&bnad->bna, &bnad->mod_res_info[0]);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	/* Get the burnt-in mac */
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_enet_perm_mac_get(&bna->enet, bnad->perm_addr);
	bnad_set_netdev_perm_addr(bnad);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	mutex_unlock(&bnad->conf_mutex);

	/* Finally, reguister with net_device layer */
	err = रेजिस्टर_netdev(netdev);
	अगर (err) अणु
		dev_err(&pdev->dev, "registering net device failed\n");
		जाओ probe_uninit;
	पूर्ण
	set_bit(BNAD_RF_NETDEV_REGISTERED, &bnad->run_flags);

	वापस 0;

probe_success:
	mutex_unlock(&bnad->conf_mutex);
	वापस 0;

probe_uninit:
	mutex_lock(&bnad->conf_mutex);
	bnad_res_मुक्त(bnad, &bnad->mod_res_info[0], BNA_MOD_RES_T_MAX);
disable_ioceth:
	bnad_ioceth_disable(bnad);
	del_समयr_sync(&bnad->bna.ioceth.ioc.ioc_समयr);
	del_समयr_sync(&bnad->bna.ioceth.ioc.sem_समयr);
	del_समयr_sync(&bnad->bna.ioceth.ioc.hb_समयr);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_uninit(bna);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);
	bnad_mbox_irq_मुक्त(bnad);
	bnad_disable_msix(bnad);
res_मुक्त:
	bnad_res_मुक्त(bnad, &bnad->res_info[0], BNA_RES_T_MAX);
drv_uninit:
	/* Remove the debugfs node क्रम this bnad */
	kमुक्त(bnad->regdata);
	bnad_debugfs_uninit(bnad);
	bnad_uninit(bnad);
pci_uninit:
	bnad_pci_uninit(pdev);
unlock_mutex:
	mutex_unlock(&bnad->conf_mutex);
	bnad_lock_uninit(bnad);
	मुक्त_netdev(netdev);
	वापस err;
पूर्ण

अटल व्योम
bnad_pci_हटाओ(काष्ठा pci_dev *pdev)
अणु
	काष्ठा net_device *netdev = pci_get_drvdata(pdev);
	काष्ठा bnad *bnad;
	काष्ठा bna *bna;
	अचिन्हित दीर्घ flags;

	अगर (!netdev)
		वापस;

	bnad = netdev_priv(netdev);
	bna = &bnad->bna;

	अगर (test_and_clear_bit(BNAD_RF_NETDEV_REGISTERED, &bnad->run_flags))
		unरेजिस्टर_netdev(netdev);

	mutex_lock(&bnad->conf_mutex);
	bnad_ioceth_disable(bnad);
	del_समयr_sync(&bnad->bna.ioceth.ioc.ioc_समयr);
	del_समयr_sync(&bnad->bna.ioceth.ioc.sem_समयr);
	del_समयr_sync(&bnad->bna.ioceth.ioc.hb_समयr);
	spin_lock_irqsave(&bnad->bna_lock, flags);
	bna_uninit(bna);
	spin_unlock_irqrestore(&bnad->bna_lock, flags);

	bnad_res_मुक्त(bnad, &bnad->mod_res_info[0], BNA_MOD_RES_T_MAX);
	bnad_res_मुक्त(bnad, &bnad->res_info[0], BNA_RES_T_MAX);
	bnad_mbox_irq_मुक्त(bnad);
	bnad_disable_msix(bnad);
	bnad_pci_uninit(pdev);
	mutex_unlock(&bnad->conf_mutex);
	bnad_lock_uninit(bnad);
	/* Remove the debugfs node क्रम this bnad */
	kमुक्त(bnad->regdata);
	bnad_debugfs_uninit(bnad);
	bnad_uninit(bnad);
	मुक्त_netdev(netdev);
पूर्ण

अटल स्थिर काष्ठा pci_device_id bnad_pci_id_table[] = अणु
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_BROCADE,
			PCI_DEVICE_ID_BROCADE_CT),
		.class = PCI_CLASS_NETWORK_ETHERNET << 8,
		.class_mask =  0xffff00
	पूर्ण,
	अणु
		PCI_DEVICE(PCI_VENDOR_ID_BROCADE,
			BFA_PCI_DEVICE_ID_CT2),
		.class = PCI_CLASS_NETWORK_ETHERNET << 8,
		.class_mask =  0xffff00
	पूर्ण,
	अणु0,  पूर्ण,
पूर्ण;

MODULE_DEVICE_TABLE(pci, bnad_pci_id_table);

अटल काष्ठा pci_driver bnad_pci_driver = अणु
	.name = BNAD_NAME,
	.id_table = bnad_pci_id_table,
	.probe = bnad_pci_probe,
	.हटाओ = bnad_pci_हटाओ,
पूर्ण;

अटल पूर्णांक __init
bnad_module_init(व्योम)
अणु
	पूर्णांक err;

	bfa_nw_ioc_स्वतः_recover(bnad_ioc_स्वतः_recover);

	err = pci_रेजिस्टर_driver(&bnad_pci_driver);
	अगर (err < 0) अणु
		pr_err("bna: PCI driver registration failed err=%d\n", err);
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम __निकास
bnad_module_निकास(व्योम)
अणु
	pci_unरेजिस्टर_driver(&bnad_pci_driver);
	release_firmware(bfi_fw);
पूर्ण

module_init(bnad_module_init);
module_निकास(bnad_module_निकास);

MODULE_AUTHOR("Brocade");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("QLogic BR-series 10G PCIe Ethernet driver");
MODULE_FIRMWARE(CNA_FW_खाता_CT);
MODULE_FIRMWARE(CNA_FW_खाता_CT2);
