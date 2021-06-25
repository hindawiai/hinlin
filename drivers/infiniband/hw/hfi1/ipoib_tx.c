<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2020 Intel Corporation.
 *
 */

/*
 * This file contains HFI1 support क्रम IPOIB SDMA functionality
 */

#समावेश <linux/log2.h>
#समावेश <linux/circ_buf.h>

#समावेश "sdma.h"
#समावेश "verbs.h"
#समावेश "trace_ibhdrs.h"
#समावेश "ipoib.h"
#समावेश "trace_tx.h"

/* Add a convenience helper */
#घोषणा CIRC_ADD(val, add, size) (((val) + (add)) & ((size) - 1))
#घोषणा CIRC_NEXT(val, size) CIRC_ADD(val, 1, size)
#घोषणा CIRC_PREV(val, size) CIRC_ADD(val, -1, size)

/**
 * काष्ठा ipoib_txreq - IPOIB transmit descriptor
 * @txreq: sdma transmit request
 * @sdma_hdr: 9b ib headers
 * @sdma_status: status वापसed by sdma engine
 * @priv: ipoib netdev निजी data
 * @txq: txq on which skb was output
 * @skb: skb to send
 */
काष्ठा ipoib_txreq अणु
	काष्ठा sdma_txreq           txreq;
	काष्ठा hfi1_sdma_header     sdma_hdr;
	पूर्णांक                         sdma_status;
	काष्ठा hfi1_ipoib_dev_priv *priv;
	काष्ठा hfi1_ipoib_txq      *txq;
	काष्ठा sk_buff             *skb;
पूर्ण;

काष्ठा ipoib_txparms अणु
	काष्ठा hfi1_devdata        *dd;
	काष्ठा rdma_ah_attr        *ah_attr;
	काष्ठा hfi1_ibport         *ibp;
	काष्ठा hfi1_ipoib_txq      *txq;
	जोड़ hfi1_ipoib_flow       flow;
	u32                         dqpn;
	u8                          hdr_dwords;
	u8                          entropy;
पूर्ण;

अटल u64 hfi1_ipoib_txreqs(स्थिर u64 sent, स्थिर u64 completed)
अणु
	वापस sent - completed;
पूर्ण

अटल u64 hfi1_ipoib_used(काष्ठा hfi1_ipoib_txq *txq)
अणु
	वापस hfi1_ipoib_txreqs(txq->sent_txreqs,
				 atomic64_पढ़ो(&txq->complete_txreqs));
पूर्ण

अटल व्योम hfi1_ipoib_stop_txq(काष्ठा hfi1_ipoib_txq *txq)
अणु
	trace_hfi1_txq_stop(txq);
	अगर (atomic_inc_वापस(&txq->stops) == 1)
		netअगर_stop_subqueue(txq->priv->netdev, txq->q_idx);
पूर्ण

अटल व्योम hfi1_ipoib_wake_txq(काष्ठा hfi1_ipoib_txq *txq)
अणु
	trace_hfi1_txq_wake(txq);
	अगर (atomic_dec_and_test(&txq->stops))
		netअगर_wake_subqueue(txq->priv->netdev, txq->q_idx);
पूर्ण

अटल uपूर्णांक hfi1_ipoib_ring_hwat(काष्ठा hfi1_ipoib_txq *txq)
अणु
	वापस min_t(uपूर्णांक, txq->priv->netdev->tx_queue_len,
		     txq->tx_ring.max_items - 1);
पूर्ण

अटल uपूर्णांक hfi1_ipoib_ring_lwat(काष्ठा hfi1_ipoib_txq *txq)
अणु
	वापस min_t(uपूर्णांक, txq->priv->netdev->tx_queue_len,
		     txq->tx_ring.max_items) >> 1;
पूर्ण

अटल व्योम hfi1_ipoib_check_queue_depth(काष्ठा hfi1_ipoib_txq *txq)
अणु
	++txq->sent_txreqs;
	अगर (hfi1_ipoib_used(txq) >= hfi1_ipoib_ring_hwat(txq) &&
	    !atomic_xchg(&txq->ring_full, 1)) अणु
		trace_hfi1_txq_full(txq);
		hfi1_ipoib_stop_txq(txq);
	पूर्ण
पूर्ण

अटल व्योम hfi1_ipoib_check_queue_stopped(काष्ठा hfi1_ipoib_txq *txq)
अणु
	काष्ठा net_device *dev = txq->priv->netdev;

	/* If shutting करोwn just वापस as queue state is irrelevant */
	अगर (unlikely(dev->reg_state != NETREG_REGISTERED))
		वापस;

	/*
	 * When the queue has been drained to less than half full it will be
	 * restarted.
	 * The size of the txreq ring is fixed at initialization.
	 * The tx queue len can be adjusted upward जबतक the पूर्णांकerface is
	 * running.
	 * The tx queue len can be large enough to overflow the txreq_ring.
	 * Use the minimum of the current tx_queue_len or the rings max txreqs
	 * to protect against ring overflow.
	 */
	अगर (hfi1_ipoib_used(txq) < hfi1_ipoib_ring_lwat(txq) &&
	    atomic_xchg(&txq->ring_full, 0)) अणु
		trace_hfi1_txq_xmit_unstopped(txq);
		hfi1_ipoib_wake_txq(txq);
	पूर्ण
पूर्ण

अटल व्योम hfi1_ipoib_मुक्त_tx(काष्ठा ipoib_txreq *tx, पूर्णांक budget)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = tx->priv;

	अगर (likely(!tx->sdma_status)) अणु
		dev_sw_netstats_tx_add(priv->netdev, 1, tx->skb->len);
	पूर्ण अन्यथा अणु
		++priv->netdev->stats.tx_errors;
		dd_dev_warn(priv->dd,
			    "%s: Status = 0x%x pbc 0x%llx txq = %d sde = %d\n",
			    __func__, tx->sdma_status,
			    le64_to_cpu(tx->sdma_hdr.pbc), tx->txq->q_idx,
			    tx->txq->sde->this_idx);
	पूर्ण

	napi_consume_skb(tx->skb, budget);
	sdma_txclean(priv->dd, &tx->txreq);
	kmem_cache_मुक्त(priv->txreq_cache, tx);
पूर्ण

अटल पूर्णांक hfi1_ipoib_drain_tx_ring(काष्ठा hfi1_ipoib_txq *txq, पूर्णांक budget)
अणु
	काष्ठा hfi1_ipoib_circ_buf *tx_ring = &txq->tx_ring;
	अचिन्हित दीर्घ head;
	अचिन्हित दीर्घ tail;
	अचिन्हित पूर्णांक max_tx;
	पूर्णांक work_करोne;
	पूर्णांक tx_count;

	spin_lock_bh(&tx_ring->consumer_lock);

	/* Read index beक्रमe पढ़ोing contents at that index. */
	head = smp_load_acquire(&tx_ring->head);
	tail = tx_ring->tail;
	max_tx = tx_ring->max_items;

	work_करोne = min_t(पूर्णांक, CIRC_CNT(head, tail, max_tx), budget);

	क्रम (tx_count = work_करोne; tx_count; tx_count--) अणु
		hfi1_ipoib_मुक्त_tx(tx_ring->items[tail], budget);
		tail = CIRC_NEXT(tail, max_tx);
	पूर्ण

	atomic64_add(work_करोne, &txq->complete_txreqs);

	/* Finished मुक्तing tx items so store the tail value. */
	smp_store_release(&tx_ring->tail, tail);

	spin_unlock_bh(&tx_ring->consumer_lock);

	hfi1_ipoib_check_queue_stopped(txq);

	वापस work_करोne;
पूर्ण

अटल पूर्णांक hfi1_ipoib_process_tx_ring(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(napi->dev);
	काष्ठा hfi1_ipoib_txq *txq = &priv->txqs[napi - priv->tx_napis];

	पूर्णांक work_करोne = hfi1_ipoib_drain_tx_ring(txq, budget);

	अगर (work_करोne < budget)
		napi_complete_करोne(napi, work_करोne);

	वापस work_करोne;
पूर्ण

अटल व्योम hfi1_ipoib_add_tx(काष्ठा ipoib_txreq *tx)
अणु
	काष्ठा hfi1_ipoib_circ_buf *tx_ring = &tx->txq->tx_ring;
	अचिन्हित दीर्घ head;
	अचिन्हित दीर्घ tail;
	माप_प्रकार max_tx;

	spin_lock(&tx_ring->producer_lock);

	head = tx_ring->head;
	tail = READ_ONCE(tx_ring->tail);
	max_tx = tx_ring->max_items;

	अगर (likely(CIRC_SPACE(head, tail, max_tx))) अणु
		tx_ring->items[head] = tx;

		/* Finish storing txreq beक्रमe incrementing head. */
		smp_store_release(&tx_ring->head, CIRC_ADD(head, 1, max_tx));
		napi_schedule_irqoff(tx->txq->napi);
	पूर्ण अन्यथा अणु
		काष्ठा hfi1_ipoib_txq *txq = tx->txq;
		काष्ठा hfi1_ipoib_dev_priv *priv = tx->priv;

		/* Ring was full */
		hfi1_ipoib_मुक्त_tx(tx, 0);
		atomic64_inc(&txq->complete_txreqs);
		dd_dev_dbg(priv->dd, "txq %d full.\n", txq->q_idx);
	पूर्ण

	spin_unlock(&tx_ring->producer_lock);
पूर्ण

अटल व्योम hfi1_ipoib_sdma_complete(काष्ठा sdma_txreq *txreq, पूर्णांक status)
अणु
	काष्ठा ipoib_txreq *tx = container_of(txreq, काष्ठा ipoib_txreq, txreq);

	tx->sdma_status = status;

	hfi1_ipoib_add_tx(tx);
पूर्ण

अटल पूर्णांक hfi1_ipoib_build_ulp_payload(काष्ठा ipoib_txreq *tx,
					काष्ठा ipoib_txparms *txp)
अणु
	काष्ठा hfi1_devdata *dd = txp->dd;
	काष्ठा sdma_txreq *txreq = &tx->txreq;
	काष्ठा sk_buff *skb = tx->skb;
	पूर्णांक ret = 0;
	पूर्णांक i;

	अगर (skb_headlen(skb)) अणु
		ret = sdma_txadd_kvaddr(dd, txreq, skb->data, skb_headlen(skb));
		अगर (unlikely(ret))
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[i];

		ret = sdma_txadd_page(dd,
				      txreq,
				      skb_frag_page(frag),
				      frag->bv_offset,
				      skb_frag_size(frag));
		अगर (unlikely(ret))
			अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_ipoib_build_tx_desc(काष्ठा ipoib_txreq *tx,
				    काष्ठा ipoib_txparms *txp)
अणु
	काष्ठा hfi1_devdata *dd = txp->dd;
	काष्ठा sdma_txreq *txreq = &tx->txreq;
	काष्ठा hfi1_sdma_header *sdma_hdr = &tx->sdma_hdr;
	u16 pkt_bytes =
		माप(sdma_hdr->pbc) + (txp->hdr_dwords << 2) + tx->skb->len;
	पूर्णांक ret;

	ret = sdma_txinit(txreq, 0, pkt_bytes, hfi1_ipoib_sdma_complete);
	अगर (unlikely(ret))
		वापस ret;

	/* add pbc + headers */
	ret = sdma_txadd_kvaddr(dd,
				txreq,
				sdma_hdr,
				माप(sdma_hdr->pbc) + (txp->hdr_dwords << 2));
	अगर (unlikely(ret))
		वापस ret;

	/* add the ulp payload */
	वापस hfi1_ipoib_build_ulp_payload(tx, txp);
पूर्ण

अटल व्योम hfi1_ipoib_build_ib_tx_headers(काष्ठा ipoib_txreq *tx,
					   काष्ठा ipoib_txparms *txp)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = tx->priv;
	काष्ठा hfi1_sdma_header *sdma_hdr = &tx->sdma_hdr;
	काष्ठा sk_buff *skb = tx->skb;
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(txp->ibp);
	काष्ठा rdma_ah_attr *ah_attr = txp->ah_attr;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा ib_grh *grh;
	u16 dwords;
	u16 slid;
	u16 dlid;
	u16 lrh0;
	u32 bth0;
	u32 sqpn = (u32)(priv->netdev->dev_addr[1] << 16 |
			 priv->netdev->dev_addr[2] << 8 |
			 priv->netdev->dev_addr[3]);
	u16 payload_dwords;
	u8 pad_cnt;

	pad_cnt = -skb->len & 3;

	/* Includes ICRC */
	payload_dwords = ((skb->len + pad_cnt) >> 2) + SIZE_OF_CRC;

	/* header size in dwords LRH+BTH+DETH = (8+12+8)/4. */
	txp->hdr_dwords = 7;

	अगर (rdma_ah_get_ah_flags(ah_attr) & IB_AH_GRH) अणु
		grh = &sdma_hdr->hdr.ibh.u.l.grh;
		txp->hdr_dwords +=
			hfi1_make_grh(txp->ibp,
				      grh,
				      rdma_ah_पढ़ो_grh(ah_attr),
				      txp->hdr_dwords - LRH_9B_DWORDS,
				      payload_dwords);
		lrh0 = HFI1_LRH_GRH;
		ohdr = &sdma_hdr->hdr.ibh.u.l.oth;
	पूर्ण अन्यथा अणु
		lrh0 = HFI1_LRH_BTH;
		ohdr = &sdma_hdr->hdr.ibh.u.oth;
	पूर्ण

	lrh0 |= (rdma_ah_get_sl(ah_attr) & 0xf) << 4;
	lrh0 |= (txp->flow.sc5 & 0xf) << 12;

	dlid = opa_get_lid(rdma_ah_get_dlid(ah_attr), 9B);
	अगर (dlid == be16_to_cpu(IB_LID_PERMISSIVE)) अणु
		slid = be16_to_cpu(IB_LID_PERMISSIVE);
	पूर्ण अन्यथा अणु
		u16 lid = (u16)ppd->lid;

		अगर (lid) अणु
			lid |= rdma_ah_get_path_bits(ah_attr) &
				((1 << ppd->lmc) - 1);
			slid = lid;
		पूर्ण अन्यथा अणु
			slid = be16_to_cpu(IB_LID_PERMISSIVE);
		पूर्ण
	पूर्ण

	/* Includes ICRC */
	dwords = txp->hdr_dwords + payload_dwords;

	/* Build the lrh */
	sdma_hdr->hdr.hdr_type = HFI1_PKT_TYPE_9B;
	hfi1_make_ib_hdr(&sdma_hdr->hdr.ibh, lrh0, dwords, dlid, slid);

	/* Build the bth */
	bth0 = (IB_OPCODE_UD_SEND_ONLY << 24) | (pad_cnt << 20) | priv->pkey;

	ohdr->bth[0] = cpu_to_be32(bth0);
	ohdr->bth[1] = cpu_to_be32(txp->dqpn);
	ohdr->bth[2] = cpu_to_be32(mask_psn((u32)txp->txq->sent_txreqs));

	/* Build the deth */
	ohdr->u.ud.deth[0] = cpu_to_be32(priv->qkey);
	ohdr->u.ud.deth[1] = cpu_to_be32((txp->entropy <<
					  HFI1_IPOIB_ENTROPY_SHIFT) | sqpn);

	/* Conकाष्ठा the pbc. */
	sdma_hdr->pbc =
		cpu_to_le64(create_pbc(ppd,
				       ib_is_sc5(txp->flow.sc5) <<
							      PBC_DC_INFO_SHIFT,
				       0,
				       sc_to_vlt(priv->dd, txp->flow.sc5),
				       dwords - SIZE_OF_CRC +
						(माप(sdma_hdr->pbc) >> 2)));
पूर्ण

अटल काष्ठा ipoib_txreq *hfi1_ipoib_send_dma_common(काष्ठा net_device *dev,
						      काष्ठा sk_buff *skb,
						      काष्ठा ipoib_txparms *txp)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	काष्ठा ipoib_txreq *tx;
	पूर्णांक ret;

	tx = kmem_cache_alloc_node(priv->txreq_cache,
				   GFP_ATOMIC,
				   priv->dd->node);
	अगर (unlikely(!tx))
		वापस ERR_PTR(-ENOMEM);

	/* so that we can test अगर the sdma descriptors are there */
	tx->txreq.num_desc = 0;
	tx->priv = priv;
	tx->txq = txp->txq;
	tx->skb = skb;
	INIT_LIST_HEAD(&tx->txreq.list);

	hfi1_ipoib_build_ib_tx_headers(tx, txp);

	ret = hfi1_ipoib_build_tx_desc(tx, txp);
	अगर (likely(!ret)) अणु
		अगर (txp->txq->flow.as_पूर्णांक != txp->flow.as_पूर्णांक) अणु
			txp->txq->flow.tx_queue = txp->flow.tx_queue;
			txp->txq->flow.sc5 = txp->flow.sc5;
			txp->txq->sde =
				sdma_select_engine_sc(priv->dd,
						      txp->flow.tx_queue,
						      txp->flow.sc5);
			trace_hfi1_flow_चयन(txp->txq);
		पूर्ण

		वापस tx;
	पूर्ण

	sdma_txclean(priv->dd, &tx->txreq);
	kmem_cache_मुक्त(priv->txreq_cache, tx);

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक hfi1_ipoib_submit_tx_list(काष्ठा net_device *dev,
				     काष्ठा hfi1_ipoib_txq *txq)
अणु
	पूर्णांक ret;
	u16 count_out;

	ret = sdma_send_txlist(txq->sde,
			       ioरुको_get_ib_work(&txq->रुको),
			       &txq->tx_list,
			       &count_out);
	अगर (likely(!ret) || ret == -EBUSY || ret == -ECOMM)
		वापस ret;

	dd_dev_warn(txq->priv->dd, "cannot send skb tx list, err %d.\n", ret);

	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_ipoib_flush_tx_list(काष्ठा net_device *dev,
				    काष्ठा hfi1_ipoib_txq *txq)
अणु
	पूर्णांक ret = 0;

	अगर (!list_empty(&txq->tx_list)) अणु
		/* Flush the current list */
		ret = hfi1_ipoib_submit_tx_list(dev, txq);

		अगर (unlikely(ret))
			अगर (ret != -EBUSY)
				++dev->stats.tx_carrier_errors;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_ipoib_submit_tx(काष्ठा hfi1_ipoib_txq *txq,
				काष्ठा ipoib_txreq *tx)
अणु
	पूर्णांक ret;

	ret = sdma_send_txreq(txq->sde,
			      ioरुको_get_ib_work(&txq->रुको),
			      &tx->txreq,
			      txq->pkts_sent);
	अगर (likely(!ret)) अणु
		txq->pkts_sent = true;
		ioरुको_starve_clear(txq->pkts_sent, &txq->रुको);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक hfi1_ipoib_send_dma_single(काष्ठा net_device *dev,
				      काष्ठा sk_buff *skb,
				      काष्ठा ipoib_txparms *txp)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	काष्ठा hfi1_ipoib_txq *txq = txp->txq;
	काष्ठा ipoib_txreq *tx;
	पूर्णांक ret;

	tx = hfi1_ipoib_send_dma_common(dev, skb, txp);
	अगर (IS_ERR(tx)) अणु
		पूर्णांक ret = PTR_ERR(tx);

		dev_kमुक्त_skb_any(skb);

		अगर (ret == -ENOMEM)
			++dev->stats.tx_errors;
		अन्यथा
			++dev->stats.tx_carrier_errors;

		वापस NETDEV_TX_OK;
	पूर्ण

	ret = hfi1_ipoib_submit_tx(txq, tx);
	अगर (likely(!ret)) अणु
tx_ok:
		trace_sdma_output_ibhdr(tx->priv->dd,
					&tx->sdma_hdr.hdr,
					ib_is_sc5(txp->flow.sc5));
		hfi1_ipoib_check_queue_depth(txq);
		वापस NETDEV_TX_OK;
	पूर्ण

	txq->pkts_sent = false;

	अगर (ret == -EBUSY || ret == -ECOMM)
		जाओ tx_ok;

	sdma_txclean(priv->dd, &tx->txreq);
	dev_kमुक्त_skb_any(skb);
	kmem_cache_मुक्त(priv->txreq_cache, tx);
	++dev->stats.tx_carrier_errors;

	वापस NETDEV_TX_OK;
पूर्ण

अटल पूर्णांक hfi1_ipoib_send_dma_list(काष्ठा net_device *dev,
				    काष्ठा sk_buff *skb,
				    काष्ठा ipoib_txparms *txp)
अणु
	काष्ठा hfi1_ipoib_txq *txq = txp->txq;
	काष्ठा ipoib_txreq *tx;

	/* Has the flow change ? */
	अगर (txq->flow.as_पूर्णांक != txp->flow.as_पूर्णांक) अणु
		पूर्णांक ret;

		trace_hfi1_flow_flush(txq);
		ret = hfi1_ipoib_flush_tx_list(dev, txq);
		अगर (unlikely(ret)) अणु
			अगर (ret == -EBUSY)
				++dev->stats.tx_dropped;
			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण
	tx = hfi1_ipoib_send_dma_common(dev, skb, txp);
	अगर (IS_ERR(tx)) अणु
		पूर्णांक ret = PTR_ERR(tx);

		dev_kमुक्त_skb_any(skb);

		अगर (ret == -ENOMEM)
			++dev->stats.tx_errors;
		अन्यथा
			++dev->stats.tx_carrier_errors;

		वापस NETDEV_TX_OK;
	पूर्ण

	list_add_tail(&tx->txreq.list, &txq->tx_list);

	hfi1_ipoib_check_queue_depth(txq);

	trace_sdma_output_ibhdr(tx->priv->dd,
				&tx->sdma_hdr.hdr,
				ib_is_sc5(txp->flow.sc5));

	अगर (!netdev_xmit_more())
		(व्योम)hfi1_ipoib_flush_tx_list(dev, txq);

	वापस NETDEV_TX_OK;
पूर्ण

अटल u8 hfi1_ipoib_calc_entropy(काष्ठा sk_buff *skb)
अणु
	अगर (skb_transport_header_was_set(skb)) अणु
		u8 *hdr = (u8 *)skb_transport_header(skb);

		वापस (hdr[0] ^ hdr[1] ^ hdr[2] ^ hdr[3]);
	पूर्ण

	वापस (u8)skb_get_queue_mapping(skb);
पूर्ण

पूर्णांक hfi1_ipoib_send(काष्ठा net_device *dev,
		    काष्ठा sk_buff *skb,
		    काष्ठा ib_ah *address,
		    u32 dqpn)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	काष्ठा ipoib_txparms txp;
	काष्ठा rdma_netdev *rn = netdev_priv(dev);

	अगर (unlikely(skb->len > rn->mtu + HFI1_IPOIB_ENCAP_LEN)) अणु
		dd_dev_warn(priv->dd, "packet len %d (> %d) too long to send, dropping\n",
			    skb->len,
			    rn->mtu + HFI1_IPOIB_ENCAP_LEN);
		++dev->stats.tx_dropped;
		++dev->stats.tx_errors;
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	txp.dd = priv->dd;
	txp.ah_attr = &ibah_to_rvtah(address)->attr;
	txp.ibp = to_iport(priv->device, priv->port_num);
	txp.txq = &priv->txqs[skb_get_queue_mapping(skb)];
	txp.dqpn = dqpn;
	txp.flow.sc5 = txp.ibp->sl_to_sc[rdma_ah_get_sl(txp.ah_attr)];
	txp.flow.tx_queue = (u8)skb_get_queue_mapping(skb);
	txp.entropy = hfi1_ipoib_calc_entropy(skb);

	अगर (netdev_xmit_more() || !list_empty(&txp.txq->tx_list))
		वापस hfi1_ipoib_send_dma_list(dev, skb, &txp);

	वापस hfi1_ipoib_send_dma_single(dev, skb,  &txp);
पूर्ण

/*
 * hfi1_ipoib_sdma_sleep - ipoib sdma sleep function
 *
 * This function माला_लो called from sdma_send_txreq() when there are not enough
 * sdma descriptors available to send the packet. It adds Tx queue's रुको
 * काष्ठाure to sdma engine's dmaरुको list to be woken up when descriptors
 * become available.
 */
अटल पूर्णांक hfi1_ipoib_sdma_sleep(काष्ठा sdma_engine *sde,
				 काष्ठा ioरुको_work *रुको,
				 काष्ठा sdma_txreq *txreq,
				 uपूर्णांक seq,
				 bool pkts_sent)
अणु
	काष्ठा hfi1_ipoib_txq *txq =
		container_of(रुको->iow, काष्ठा hfi1_ipoib_txq, रुको);

	ग_लिखो_seqlock(&sde->रुकोlock);

	अगर (likely(txq->priv->netdev->reg_state == NETREG_REGISTERED)) अणु
		अगर (sdma_progress(sde, seq, txreq)) अणु
			ग_लिखो_sequnlock(&sde->रुकोlock);
			वापस -EAGAIN;
		पूर्ण

		अगर (list_empty(&txreq->list))
			/* came from non-list submit */
			list_add_tail(&txreq->list, &txq->tx_list);
		अगर (list_empty(&txq->रुको.list)) अणु
			अगर (!atomic_xchg(&txq->no_desc, 1)) अणु
				trace_hfi1_txq_queued(txq);
				hfi1_ipoib_stop_txq(txq);
			पूर्ण
			ioरुको_queue(pkts_sent, रुको->iow, &sde->dmaरुको);
		पूर्ण

		ग_लिखो_sequnlock(&sde->रुकोlock);
		वापस -EBUSY;
	पूर्ण

	ग_लिखो_sequnlock(&sde->रुकोlock);
	वापस -EINVAL;
पूर्ण

/*
 * hfi1_ipoib_sdma_wakeup - ipoib sdma wakeup function
 *
 * This function माला_लो called when SDMA descriptors becomes available and Tx
 * queue's wait structure was previously added to sdma engine's dmaरुको list.
 */
अटल व्योम hfi1_ipoib_sdma_wakeup(काष्ठा ioरुको *रुको, पूर्णांक reason)
अणु
	काष्ठा hfi1_ipoib_txq *txq =
		container_of(रुको, काष्ठा hfi1_ipoib_txq, रुको);

	trace_hfi1_txq_wakeup(txq);
	अगर (likely(txq->priv->netdev->reg_state == NETREG_REGISTERED))
		ioरुको_schedule(रुको, प्रणाली_highpri_wq, WORK_CPU_UNBOUND);
पूर्ण

अटल व्योम hfi1_ipoib_flush_txq(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ioरुको_work *ioww =
		container_of(work, काष्ठा ioरुको_work, iowork);
	काष्ठा ioरुको *रुको = ioरुको_ioww_to_iow(ioww);
	काष्ठा hfi1_ipoib_txq *txq =
		container_of(रुको, काष्ठा hfi1_ipoib_txq, रुको);
	काष्ठा net_device *dev = txq->priv->netdev;

	अगर (likely(dev->reg_state == NETREG_REGISTERED) &&
	    likely(!hfi1_ipoib_flush_tx_list(dev, txq)))
		अगर (atomic_xchg(&txq->no_desc, 0))
			hfi1_ipoib_wake_txq(txq);
पूर्ण

पूर्णांक hfi1_ipoib_txreq_init(काष्ठा hfi1_ipoib_dev_priv *priv)
अणु
	काष्ठा net_device *dev = priv->netdev;
	अक्षर buf[HFI1_IPOIB_TXREQ_NAME_LEN];
	अचिन्हित दीर्घ tx_ring_size;
	पूर्णांक i;

	/*
	 * Ring holds 1 less than tx_ring_size
	 * Round up to next घातer of 2 in order to hold at least tx_queue_len
	 */
	tx_ring_size = roundup_घात_of_two((अचिन्हित दीर्घ)dev->tx_queue_len + 1);

	snम_लिखो(buf, माप(buf), "hfi1_%u_ipoib_txreq_cache", priv->dd->unit);
	priv->txreq_cache = kmem_cache_create(buf,
					      माप(काष्ठा ipoib_txreq),
					      0,
					      0,
					      शून्य);
	अगर (!priv->txreq_cache)
		वापस -ENOMEM;

	priv->tx_napis = kसुस्मृति_node(dev->num_tx_queues,
				      माप(काष्ठा napi_काष्ठा),
				      GFP_KERNEL,
				      priv->dd->node);
	अगर (!priv->tx_napis)
		जाओ मुक्त_txreq_cache;

	priv->txqs = kसुस्मृति_node(dev->num_tx_queues,
				  माप(काष्ठा hfi1_ipoib_txq),
				  GFP_KERNEL,
				  priv->dd->node);
	अगर (!priv->txqs)
		जाओ मुक्त_tx_napis;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा hfi1_ipoib_txq *txq = &priv->txqs[i];

		ioरुको_init(&txq->रुको,
			    0,
			    hfi1_ipoib_flush_txq,
			    शून्य,
			    hfi1_ipoib_sdma_sleep,
			    hfi1_ipoib_sdma_wakeup,
			    शून्य,
			    शून्य);
		txq->priv = priv;
		txq->sde = शून्य;
		INIT_LIST_HEAD(&txq->tx_list);
		atomic64_set(&txq->complete_txreqs, 0);
		atomic_set(&txq->stops, 0);
		atomic_set(&txq->ring_full, 0);
		atomic_set(&txq->no_desc, 0);
		txq->q_idx = i;
		txq->flow.tx_queue = 0xff;
		txq->flow.sc5 = 0xff;
		txq->pkts_sent = false;

		netdev_queue_numa_node_ग_लिखो(netdev_get_tx_queue(dev, i),
					     priv->dd->node);

		txq->tx_ring.items =
			kसुस्मृति_node(tx_ring_size,
				     माप(काष्ठा ipoib_txreq *),
				     GFP_KERNEL, priv->dd->node);
		अगर (!txq->tx_ring.items)
			जाओ मुक्त_txqs;

		spin_lock_init(&txq->tx_ring.producer_lock);
		spin_lock_init(&txq->tx_ring.consumer_lock);
		txq->tx_ring.max_items = tx_ring_size;

		txq->napi = &priv->tx_napis[i];
		netअगर_tx_napi_add(dev, txq->napi,
				  hfi1_ipoib_process_tx_ring,
				  NAPI_POLL_WEIGHT);
	पूर्ण

	वापस 0;

मुक्त_txqs:
	क्रम (i--; i >= 0; i--) अणु
		काष्ठा hfi1_ipoib_txq *txq = &priv->txqs[i];

		netअगर_napi_del(txq->napi);
		kमुक्त(txq->tx_ring.items);
	पूर्ण

	kमुक्त(priv->txqs);
	priv->txqs = शून्य;

मुक्त_tx_napis:
	kमुक्त(priv->tx_napis);
	priv->tx_napis = शून्य;

मुक्त_txreq_cache:
	kmem_cache_destroy(priv->txreq_cache);
	priv->txreq_cache = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल व्योम hfi1_ipoib_drain_tx_list(काष्ठा hfi1_ipoib_txq *txq)
अणु
	काष्ठा sdma_txreq *txreq;
	काष्ठा sdma_txreq *txreq_पंचांगp;
	atomic64_t *complete_txreqs = &txq->complete_txreqs;

	list_क्रम_each_entry_safe(txreq, txreq_पंचांगp, &txq->tx_list, list) अणु
		काष्ठा ipoib_txreq *tx =
			container_of(txreq, काष्ठा ipoib_txreq, txreq);

		list_del(&txreq->list);
		sdma_txclean(txq->priv->dd, &tx->txreq);
		dev_kमुक्त_skb_any(tx->skb);
		kmem_cache_मुक्त(txq->priv->txreq_cache, tx);
		atomic64_inc(complete_txreqs);
	पूर्ण

	अगर (hfi1_ipoib_used(txq))
		dd_dev_warn(txq->priv->dd,
			    "txq %d not empty found %llu requests\n",
			    txq->q_idx,
			    hfi1_ipoib_txreqs(txq->sent_txreqs,
					      atomic64_पढ़ो(complete_txreqs)));
पूर्ण

व्योम hfi1_ipoib_txreq_deinit(काष्ठा hfi1_ipoib_dev_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->netdev->num_tx_queues; i++) अणु
		काष्ठा hfi1_ipoib_txq *txq = &priv->txqs[i];

		ioरुको_cancel_work(&txq->रुको);
		ioरुको_sdma_drain(&txq->रुको);
		hfi1_ipoib_drain_tx_list(txq);
		netअगर_napi_del(txq->napi);
		(व्योम)hfi1_ipoib_drain_tx_ring(txq, txq->tx_ring.max_items);
		kमुक्त(txq->tx_ring.items);
	पूर्ण

	kमुक्त(priv->txqs);
	priv->txqs = शून्य;

	kमुक्त(priv->tx_napis);
	priv->tx_napis = शून्य;

	kmem_cache_destroy(priv->txreq_cache);
	priv->txreq_cache = शून्य;
पूर्ण

व्योम hfi1_ipoib_napi_tx_enable(काष्ठा net_device *dev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा hfi1_ipoib_txq *txq = &priv->txqs[i];

		napi_enable(txq->napi);
	पूर्ण
पूर्ण

व्योम hfi1_ipoib_napi_tx_disable(काष्ठा net_device *dev)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	पूर्णांक i;

	क्रम (i = 0; i < dev->num_tx_queues; i++) अणु
		काष्ठा hfi1_ipoib_txq *txq = &priv->txqs[i];

		napi_disable(txq->napi);
		(व्योम)hfi1_ipoib_drain_tx_ring(txq, txq->tx_ring.max_items);
	पूर्ण
पूर्ण

व्योम hfi1_ipoib_tx_समयout(काष्ठा net_device *dev, अचिन्हित पूर्णांक q)
अणु
	काष्ठा hfi1_ipoib_dev_priv *priv = hfi1_ipoib_priv(dev);
	काष्ठा hfi1_ipoib_txq *txq = &priv->txqs[q];
	u64 completed = atomic64_पढ़ो(&txq->complete_txreqs);

	dd_dev_info(priv->dd, "timeout txq %llx q %u stopped %u stops %d no_desc %d ring_full %d\n",
		    (अचिन्हित दीर्घ दीर्घ)txq, q,
		    __netअगर_subqueue_stopped(dev, txq->q_idx),
		    atomic_पढ़ो(&txq->stops),
		    atomic_पढ़ो(&txq->no_desc),
		    atomic_पढ़ो(&txq->ring_full));
	dd_dev_info(priv->dd, "sde %llx engine %u\n",
		    (अचिन्हित दीर्घ दीर्घ)txq->sde,
		    txq->sde ? txq->sde->this_idx : 0);
	dd_dev_info(priv->dd, "flow %x\n", txq->flow.as_पूर्णांक);
	dd_dev_info(priv->dd, "sent %llu completed %llu used %llu\n",
		    txq->sent_txreqs, completed, hfi1_ipoib_used(txq));
	dd_dev_info(priv->dd, "tx_queue_len %u max_items %lu\n",
		    dev->tx_queue_len, txq->tx_ring.max_items);
	dd_dev_info(priv->dd, "head %lu tail %lu\n",
		    txq->tx_ring.head, txq->tx_ring.tail);
	dd_dev_info(priv->dd, "wait queued %u\n",
		    !list_empty(&txq->रुको.list));
	dd_dev_info(priv->dd, "tx_list empty %u\n",
		    list_empty(&txq->tx_list));
पूर्ण

