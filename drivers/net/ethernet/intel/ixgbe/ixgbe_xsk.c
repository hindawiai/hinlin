<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2018 Intel Corporation. */

#समावेश <linux/bpf_trace.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश <net/xdp.h>

#समावेश "ixgbe.h"
#समावेश "ixgbe_txrx_common.h"

काष्ठा xsk_buff_pool *ixgbe_xsk_pool(काष्ठा ixgbe_adapter *adapter,
				     काष्ठा ixgbe_ring *ring)
अणु
	bool xdp_on = READ_ONCE(adapter->xdp_prog);
	पूर्णांक qid = ring->ring_idx;

	अगर (!xdp_on || !test_bit(qid, adapter->af_xdp_zc_qps))
		वापस शून्य;

	वापस xsk_get_pool_from_qid(adapter->netdev, qid);
पूर्ण

अटल पूर्णांक ixgbe_xsk_pool_enable(काष्ठा ixgbe_adapter *adapter,
				 काष्ठा xsk_buff_pool *pool,
				 u16 qid)
अणु
	काष्ठा net_device *netdev = adapter->netdev;
	bool अगर_running;
	पूर्णांक err;

	अगर (qid >= adapter->num_rx_queues)
		वापस -EINVAL;

	अगर (qid >= netdev->real_num_rx_queues ||
	    qid >= netdev->real_num_tx_queues)
		वापस -EINVAL;

	err = xsk_pool_dma_map(pool, &adapter->pdev->dev, IXGBE_RX_DMA_ATTR);
	अगर (err)
		वापस err;

	अगर_running = netअगर_running(adapter->netdev) &&
		     ixgbe_enabled_xdp_adapter(adapter);

	अगर (अगर_running)
		ixgbe_txrx_ring_disable(adapter, qid);

	set_bit(qid, adapter->af_xdp_zc_qps);

	अगर (अगर_running) अणु
		ixgbe_txrx_ring_enable(adapter, qid);

		/* Kick start the NAPI context so that receiving will start */
		err = ixgbe_xsk_wakeup(adapter->netdev, qid, XDP_WAKEUP_RX);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ixgbe_xsk_pool_disable(काष्ठा ixgbe_adapter *adapter, u16 qid)
अणु
	काष्ठा xsk_buff_pool *pool;
	bool अगर_running;

	pool = xsk_get_pool_from_qid(adapter->netdev, qid);
	अगर (!pool)
		वापस -EINVAL;

	अगर_running = netअगर_running(adapter->netdev) &&
		     ixgbe_enabled_xdp_adapter(adapter);

	अगर (अगर_running)
		ixgbe_txrx_ring_disable(adapter, qid);

	clear_bit(qid, adapter->af_xdp_zc_qps);
	xsk_pool_dma_unmap(pool, IXGBE_RX_DMA_ATTR);

	अगर (अगर_running)
		ixgbe_txrx_ring_enable(adapter, qid);

	वापस 0;
पूर्ण

पूर्णांक ixgbe_xsk_pool_setup(काष्ठा ixgbe_adapter *adapter,
			 काष्ठा xsk_buff_pool *pool,
			 u16 qid)
अणु
	वापस pool ? ixgbe_xsk_pool_enable(adapter, pool, qid) :
		ixgbe_xsk_pool_disable(adapter, qid);
पूर्ण

अटल पूर्णांक ixgbe_run_xdp_zc(काष्ठा ixgbe_adapter *adapter,
			    काष्ठा ixgbe_ring *rx_ring,
			    काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक err, result = IXGBE_XDP_PASS;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xdp_frame *xdpf;
	u32 act;

	rcu_पढ़ो_lock();
	xdp_prog = READ_ONCE(rx_ring->xdp_prog);
	act = bpf_prog_run_xdp(xdp_prog, xdp);

	अगर (likely(act == XDP_REसूचीECT)) अणु
		err = xdp_करो_redirect(rx_ring->netdev, xdp, xdp_prog);
		अगर (err)
			जाओ out_failure;
		rcu_पढ़ो_unlock();
		वापस IXGBE_XDP_REसूची;
	पूर्ण

	चयन (act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		xdpf = xdp_convert_buff_to_frame(xdp);
		अगर (unlikely(!xdpf))
			जाओ out_failure;
		result = ixgbe_xmit_xdp_ring(adapter, xdpf);
		अगर (result == IXGBE_XDP_CONSUMED)
			जाओ out_failure;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
out_failure:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, act);
		fallthrough; /* handle पातs by dropping packet */
	हाल XDP_DROP:
		result = IXGBE_XDP_CONSUMED;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस result;
पूर्ण

bool ixgbe_alloc_rx_buffers_zc(काष्ठा ixgbe_ring *rx_ring, u16 count)
अणु
	जोड़ ixgbe_adv_rx_desc *rx_desc;
	काष्ठा ixgbe_rx_buffer *bi;
	u16 i = rx_ring->next_to_use;
	dma_addr_t dma;
	bool ok = true;

	/* nothing to करो */
	अगर (!count)
		वापस true;

	rx_desc = IXGBE_RX_DESC(rx_ring, i);
	bi = &rx_ring->rx_buffer_info[i];
	i -= rx_ring->count;

	करो अणु
		bi->xdp = xsk_buff_alloc(rx_ring->xsk_pool);
		अगर (!bi->xdp) अणु
			ok = false;
			अवरोध;
		पूर्ण

		dma = xsk_buff_xdp_get_dma(bi->xdp);

		/* Refresh the desc even अगर buffer_addrs didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(dma);

		rx_desc++;
		bi++;
		i++;
		अगर (unlikely(!i)) अणु
			rx_desc = IXGBE_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buffer_info;
			i -= rx_ring->count;
		पूर्ण

		/* clear the length क्रम the next_to_use descriptor */
		rx_desc->wb.upper.length = 0;

		count--;
	पूर्ण जबतक (count);

	i += rx_ring->count;

	अगर (rx_ring->next_to_use != i) अणु
		rx_ring->next_to_use = i;

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.  (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		ग_लिखोl(i, rx_ring->tail);
	पूर्ण

	वापस ok;
पूर्ण

अटल काष्ठा sk_buff *ixgbe_स्थिरruct_skb_zc(काष्ठा ixgbe_ring *rx_ring,
					      काष्ठा ixgbe_rx_buffer *bi)
अणु
	अचिन्हित पूर्णांक metasize = bi->xdp->data - bi->xdp->data_meta;
	अचिन्हित पूर्णांक datasize = bi->xdp->data_end - bi->xdp->data;
	काष्ठा sk_buff *skb;

	/* allocate a skb to store the frags */
	skb = __napi_alloc_skb(&rx_ring->q_vector->napi,
			       bi->xdp->data_end - bi->xdp->data_hard_start,
			       GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!skb))
		वापस शून्य;

	skb_reserve(skb, bi->xdp->data - bi->xdp->data_hard_start);
	स_नकल(__skb_put(skb, datasize), bi->xdp->data, datasize);
	अगर (metasize)
		skb_metadata_set(skb, metasize);

	xsk_buff_मुक्त(bi->xdp);
	bi->xdp = शून्य;
	वापस skb;
पूर्ण

अटल व्योम ixgbe_inc_ntc(काष्ठा ixgbe_ring *rx_ring)
अणु
	u32 ntc = rx_ring->next_to_clean + 1;

	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;
	prefetch(IXGBE_RX_DESC(rx_ring, ntc));
पूर्ण

पूर्णांक ixgbe_clean_rx_irq_zc(काष्ठा ixgbe_q_vector *q_vector,
			  काष्ठा ixgbe_ring *rx_ring,
			  स्थिर पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;
	काष्ठा ixgbe_adapter *adapter = q_vector->adapter;
	u16 cleaned_count = ixgbe_desc_unused(rx_ring);
	अचिन्हित पूर्णांक xdp_res, xdp_xmit = 0;
	bool failure = false;
	काष्ठा sk_buff *skb;

	जबतक (likely(total_rx_packets < budget)) अणु
		जोड़ ixgbe_adv_rx_desc *rx_desc;
		काष्ठा ixgbe_rx_buffer *bi;
		अचिन्हित पूर्णांक size;

		/* वापस some buffers to hardware, one at a समय is too slow */
		अगर (cleaned_count >= IXGBE_RX_BUFFER_WRITE) अणु
			failure = failure ||
				  !ixgbe_alloc_rx_buffers_zc(rx_ring,
							     cleaned_count);
			cleaned_count = 0;
		पूर्ण

		rx_desc = IXGBE_RX_DESC(rx_ring, rx_ring->next_to_clean);
		size = le16_to_cpu(rx_desc->wb.upper.length);
		अगर (!size)
			अवरोध;

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we know the
		 * descriptor has been written back
		 */
		dma_rmb();

		bi = &rx_ring->rx_buffer_info[rx_ring->next_to_clean];

		अगर (unlikely(!ixgbe_test_staterr(rx_desc,
						 IXGBE_RXD_STAT_EOP))) अणु
			काष्ठा ixgbe_rx_buffer *next_bi;

			xsk_buff_मुक्त(bi->xdp);
			bi->xdp = शून्य;
			ixgbe_inc_ntc(rx_ring);
			next_bi =
			       &rx_ring->rx_buffer_info[rx_ring->next_to_clean];
			next_bi->discard = true;
			जारी;
		पूर्ण

		अगर (unlikely(bi->discard)) अणु
			xsk_buff_मुक्त(bi->xdp);
			bi->xdp = शून्य;
			bi->discard = false;
			ixgbe_inc_ntc(rx_ring);
			जारी;
		पूर्ण

		bi->xdp->data_end = bi->xdp->data + size;
		xsk_buff_dma_sync_क्रम_cpu(bi->xdp, rx_ring->xsk_pool);
		xdp_res = ixgbe_run_xdp_zc(adapter, rx_ring, bi->xdp);

		अगर (xdp_res) अणु
			अगर (xdp_res & (IXGBE_XDP_TX | IXGBE_XDP_REसूची))
				xdp_xmit |= xdp_res;
			अन्यथा
				xsk_buff_मुक्त(bi->xdp);

			bi->xdp = शून्य;
			total_rx_packets++;
			total_rx_bytes += size;

			cleaned_count++;
			ixgbe_inc_ntc(rx_ring);
			जारी;
		पूर्ण

		/* XDP_PASS path */
		skb = ixgbe_स्थिरruct_skb_zc(rx_ring, bi);
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_rx_buff_failed++;
			अवरोध;
		पूर्ण

		cleaned_count++;
		ixgbe_inc_ntc(rx_ring);

		अगर (eth_skb_pad(skb))
			जारी;

		total_rx_bytes += skb->len;
		total_rx_packets++;

		ixgbe_process_skb_fields(rx_ring, rx_desc, skb);
		ixgbe_rx_skb(q_vector, skb);
	पूर्ण

	अगर (xdp_xmit & IXGBE_XDP_REसूची)
		xdp_करो_flush_map();

	अगर (xdp_xmit & IXGBE_XDP_TX) अणु
		काष्ठा ixgbe_ring *ring = adapter->xdp_ring[smp_processor_id()];

		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch.
		 */
		wmb();
		ग_लिखोl(ring->next_to_use, ring->tail);
	पूर्ण

	u64_stats_update_begin(&rx_ring->syncp);
	rx_ring->stats.packets += total_rx_packets;
	rx_ring->stats.bytes += total_rx_bytes;
	u64_stats_update_end(&rx_ring->syncp);
	q_vector->rx.total_packets += total_rx_packets;
	q_vector->rx.total_bytes += total_rx_bytes;

	अगर (xsk_uses_need_wakeup(rx_ring->xsk_pool)) अणु
		अगर (failure || rx_ring->next_to_clean == rx_ring->next_to_use)
			xsk_set_rx_need_wakeup(rx_ring->xsk_pool);
		अन्यथा
			xsk_clear_rx_need_wakeup(rx_ring->xsk_pool);

		वापस (पूर्णांक)total_rx_packets;
	पूर्ण
	वापस failure ? budget : (पूर्णांक)total_rx_packets;
पूर्ण

व्योम ixgbe_xsk_clean_rx_ring(काष्ठा ixgbe_ring *rx_ring)
अणु
	काष्ठा ixgbe_rx_buffer *bi;
	u16 i;

	क्रम (i = 0; i < rx_ring->count; i++) अणु
		bi = &rx_ring->rx_buffer_info[i];

		अगर (!bi->xdp)
			जारी;

		xsk_buff_मुक्त(bi->xdp);
		bi->xdp = शून्य;
	पूर्ण
पूर्ण

अटल bool ixgbe_xmit_zc(काष्ठा ixgbe_ring *xdp_ring, अचिन्हित पूर्णांक budget)
अणु
	काष्ठा xsk_buff_pool *pool = xdp_ring->xsk_pool;
	जोड़ ixgbe_adv_tx_desc *tx_desc = शून्य;
	काष्ठा ixgbe_tx_buffer *tx_bi;
	bool work_करोne = true;
	काष्ठा xdp_desc desc;
	dma_addr_t dma;
	u32 cmd_type;

	जबतक (budget-- > 0) अणु
		अगर (unlikely(!ixgbe_desc_unused(xdp_ring)) ||
		    !netअगर_carrier_ok(xdp_ring->netdev)) अणु
			work_करोne = false;
			अवरोध;
		पूर्ण

		अगर (!xsk_tx_peek_desc(pool, &desc))
			अवरोध;

		dma = xsk_buff_raw_get_dma(pool, desc.addr);
		xsk_buff_raw_dma_sync_क्रम_device(pool, dma, desc.len);

		tx_bi = &xdp_ring->tx_buffer_info[xdp_ring->next_to_use];
		tx_bi->bytecount = desc.len;
		tx_bi->xdpf = शून्य;
		tx_bi->gso_segs = 1;

		tx_desc = IXGBE_TX_DESC(xdp_ring, xdp_ring->next_to_use);
		tx_desc->पढ़ो.buffer_addr = cpu_to_le64(dma);

		/* put descriptor type bits */
		cmd_type = IXGBE_ADVTXD_DTYP_DATA |
			   IXGBE_ADVTXD_DCMD_DEXT |
			   IXGBE_ADVTXD_DCMD_IFCS;
		cmd_type |= desc.len | IXGBE_TXD_CMD;
		tx_desc->पढ़ो.cmd_type_len = cpu_to_le32(cmd_type);
		tx_desc->पढ़ो.olinfo_status =
			cpu_to_le32(desc.len << IXGBE_ADVTXD_PAYLEN_SHIFT);

		xdp_ring->next_to_use++;
		अगर (xdp_ring->next_to_use == xdp_ring->count)
			xdp_ring->next_to_use = 0;
	पूर्ण

	अगर (tx_desc) अणु
		ixgbe_xdp_ring_update_tail(xdp_ring);
		xsk_tx_release(pool);
	पूर्ण

	वापस !!budget && work_करोne;
पूर्ण

अटल व्योम ixgbe_clean_xdp_tx_buffer(काष्ठा ixgbe_ring *tx_ring,
				      काष्ठा ixgbe_tx_buffer *tx_bi)
अणु
	xdp_वापस_frame(tx_bi->xdpf);
	dma_unmap_single(tx_ring->dev,
			 dma_unmap_addr(tx_bi, dma),
			 dma_unmap_len(tx_bi, len), DMA_TO_DEVICE);
	dma_unmap_len_set(tx_bi, len, 0);
पूर्ण

bool ixgbe_clean_xdp_tx_irq(काष्ठा ixgbe_q_vector *q_vector,
			    काष्ठा ixgbe_ring *tx_ring, पूर्णांक napi_budget)
अणु
	u16 ntc = tx_ring->next_to_clean, ntu = tx_ring->next_to_use;
	अचिन्हित पूर्णांक total_packets = 0, total_bytes = 0;
	काष्ठा xsk_buff_pool *pool = tx_ring->xsk_pool;
	जोड़ ixgbe_adv_tx_desc *tx_desc;
	काष्ठा ixgbe_tx_buffer *tx_bi;
	u32 xsk_frames = 0;

	tx_bi = &tx_ring->tx_buffer_info[ntc];
	tx_desc = IXGBE_TX_DESC(tx_ring, ntc);

	जबतक (ntc != ntu) अणु
		अगर (!(tx_desc->wb.status & cpu_to_le32(IXGBE_TXD_STAT_DD)))
			अवरोध;

		total_bytes += tx_bi->bytecount;
		total_packets += tx_bi->gso_segs;

		अगर (tx_bi->xdpf)
			ixgbe_clean_xdp_tx_buffer(tx_ring, tx_bi);
		अन्यथा
			xsk_frames++;

		tx_bi->xdpf = शून्य;

		tx_bi++;
		tx_desc++;
		ntc++;
		अगर (unlikely(ntc == tx_ring->count)) अणु
			ntc = 0;
			tx_bi = tx_ring->tx_buffer_info;
			tx_desc = IXGBE_TX_DESC(tx_ring, 0);
		पूर्ण

		/* issue prefetch क्रम next Tx descriptor */
		prefetch(tx_desc);
	पूर्ण

	tx_ring->next_to_clean = ntc;

	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->stats.bytes += total_bytes;
	tx_ring->stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->syncp);
	q_vector->tx.total_bytes += total_bytes;
	q_vector->tx.total_packets += total_packets;

	अगर (xsk_frames)
		xsk_tx_completed(pool, xsk_frames);

	अगर (xsk_uses_need_wakeup(pool))
		xsk_set_tx_need_wakeup(pool);

	वापस ixgbe_xmit_zc(tx_ring, q_vector->tx.work_limit);
पूर्ण

पूर्णांक ixgbe_xsk_wakeup(काष्ठा net_device *dev, u32 qid, u32 flags)
अणु
	काष्ठा ixgbe_adapter *adapter = netdev_priv(dev);
	काष्ठा ixgbe_ring *ring;

	अगर (test_bit(__IXGBE_DOWN, &adapter->state))
		वापस -ENETDOWN;

	अगर (!READ_ONCE(adapter->xdp_prog))
		वापस -ENXIO;

	अगर (qid >= adapter->num_xdp_queues)
		वापस -ENXIO;

	ring = adapter->xdp_ring[qid];

	अगर (test_bit(__IXGBE_TX_DISABLED, &ring->state))
		वापस -ENETDOWN;

	अगर (!ring->xsk_pool)
		वापस -ENXIO;

	अगर (!napi_अगर_scheduled_mark_missed(&ring->q_vector->napi)) अणु
		u64 eics = BIT_ULL(ring->q_vector->v_idx);

		ixgbe_irq_rearm_queues(adapter, eics);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ixgbe_xsk_clean_tx_ring(काष्ठा ixgbe_ring *tx_ring)
अणु
	u16 ntc = tx_ring->next_to_clean, ntu = tx_ring->next_to_use;
	काष्ठा xsk_buff_pool *pool = tx_ring->xsk_pool;
	काष्ठा ixgbe_tx_buffer *tx_bi;
	u32 xsk_frames = 0;

	जबतक (ntc != ntu) अणु
		tx_bi = &tx_ring->tx_buffer_info[ntc];

		अगर (tx_bi->xdpf)
			ixgbe_clean_xdp_tx_buffer(tx_ring, tx_bi);
		अन्यथा
			xsk_frames++;

		tx_bi->xdpf = शून्य;

		ntc++;
		अगर (ntc == tx_ring->count)
			ntc = 0;
	पूर्ण

	अगर (xsk_frames)
		xsk_tx_completed(pool, xsk_frames);
पूर्ण
