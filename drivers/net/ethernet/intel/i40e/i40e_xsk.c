<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2018 Intel Corporation. */

#समावेश <linux/bpf_trace.h>
#समावेश <linux/stringअगरy.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश <net/xdp.h>

#समावेश "i40e.h"
#समावेश "i40e_txrx_common.h"
#समावेश "i40e_xsk.h"

पूर्णांक i40e_alloc_rx_bi_zc(काष्ठा i40e_ring *rx_ring)
अणु
	अचिन्हित दीर्घ sz = माप(*rx_ring->rx_bi_zc) * rx_ring->count;

	rx_ring->rx_bi_zc = kzalloc(sz, GFP_KERNEL);
	वापस rx_ring->rx_bi_zc ? 0 : -ENOMEM;
पूर्ण

व्योम i40e_clear_rx_bi_zc(काष्ठा i40e_ring *rx_ring)
अणु
	स_रखो(rx_ring->rx_bi_zc, 0,
	       माप(*rx_ring->rx_bi_zc) * rx_ring->count);
पूर्ण

अटल काष्ठा xdp_buff **i40e_rx_bi(काष्ठा i40e_ring *rx_ring, u32 idx)
अणु
	वापस &rx_ring->rx_bi_zc[idx];
पूर्ण

/**
 * i40e_xsk_pool_enable - Enable/associate an AF_XDP buffer pool to a
 * certain ring/qid
 * @vsi: Current VSI
 * @pool: buffer pool
 * @qid: Rx ring to associate buffer pool with
 *
 * Returns 0 on success, <0 on failure
 **/
अटल पूर्णांक i40e_xsk_pool_enable(काष्ठा i40e_vsi *vsi,
				काष्ठा xsk_buff_pool *pool,
				u16 qid)
अणु
	काष्ठा net_device *netdev = vsi->netdev;
	bool अगर_running;
	पूर्णांक err;

	अगर (vsi->type != I40E_VSI_MAIN)
		वापस -EINVAL;

	अगर (qid >= vsi->num_queue_pairs)
		वापस -EINVAL;

	अगर (qid >= netdev->real_num_rx_queues ||
	    qid >= netdev->real_num_tx_queues)
		वापस -EINVAL;

	err = xsk_pool_dma_map(pool, &vsi->back->pdev->dev, I40E_RX_DMA_ATTR);
	अगर (err)
		वापस err;

	set_bit(qid, vsi->af_xdp_zc_qps);

	अगर_running = netअगर_running(vsi->netdev) && i40e_enabled_xdp_vsi(vsi);

	अगर (अगर_running) अणु
		err = i40e_queue_pair_disable(vsi, qid);
		अगर (err)
			वापस err;

		err = i40e_queue_pair_enable(vsi, qid);
		अगर (err)
			वापस err;

		/* Kick start the NAPI context so that receiving will start */
		err = i40e_xsk_wakeup(vsi->netdev, qid, XDP_WAKEUP_RX);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_xsk_pool_disable - Disassociate an AF_XDP buffer pool from a
 * certain ring/qid
 * @vsi: Current VSI
 * @qid: Rx ring to associate buffer pool with
 *
 * Returns 0 on success, <0 on failure
 **/
अटल पूर्णांक i40e_xsk_pool_disable(काष्ठा i40e_vsi *vsi, u16 qid)
अणु
	काष्ठा net_device *netdev = vsi->netdev;
	काष्ठा xsk_buff_pool *pool;
	bool अगर_running;
	पूर्णांक err;

	pool = xsk_get_pool_from_qid(netdev, qid);
	अगर (!pool)
		वापस -EINVAL;

	अगर_running = netअगर_running(vsi->netdev) && i40e_enabled_xdp_vsi(vsi);

	अगर (अगर_running) अणु
		err = i40e_queue_pair_disable(vsi, qid);
		अगर (err)
			वापस err;
	पूर्ण

	clear_bit(qid, vsi->af_xdp_zc_qps);
	xsk_pool_dma_unmap(pool, I40E_RX_DMA_ATTR);

	अगर (अगर_running) अणु
		err = i40e_queue_pair_enable(vsi, qid);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * i40e_xsk_pool_setup - Enable/disassociate an AF_XDP buffer pool to/from
 * a ring/qid
 * @vsi: Current VSI
 * @pool: Buffer pool to enable/associate to a ring, or शून्य to disable
 * @qid: Rx ring to (dis)associate buffer pool (from)to
 *
 * This function enables or disables a buffer pool to a certain ring.
 *
 * Returns 0 on success, <0 on failure
 **/
पूर्णांक i40e_xsk_pool_setup(काष्ठा i40e_vsi *vsi, काष्ठा xsk_buff_pool *pool,
			u16 qid)
अणु
	वापस pool ? i40e_xsk_pool_enable(vsi, pool, qid) :
		i40e_xsk_pool_disable(vsi, qid);
पूर्ण

/**
 * i40e_run_xdp_zc - Executes an XDP program on an xdp_buff
 * @rx_ring: Rx ring
 * @xdp: xdp_buff used as input to the XDP program
 *
 * Returns any of I40E_XDP_अणुPASS, CONSUMED, TX, REसूचीपूर्ण
 **/
अटल पूर्णांक i40e_run_xdp_zc(काष्ठा i40e_ring *rx_ring, काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक err, result = I40E_XDP_PASS;
	काष्ठा i40e_ring *xdp_ring;
	काष्ठा bpf_prog *xdp_prog;
	u32 act;

	rcu_पढ़ो_lock();
	/* NB! xdp_prog will always be !शून्य, due to the fact that
	 * this path is enabled by setting an XDP program.
	 */
	xdp_prog = READ_ONCE(rx_ring->xdp_prog);
	act = bpf_prog_run_xdp(xdp_prog, xdp);

	अगर (likely(act == XDP_REसूचीECT)) अणु
		err = xdp_करो_redirect(rx_ring->netdev, xdp, xdp_prog);
		अगर (err)
			जाओ out_failure;
		rcu_पढ़ो_unlock();
		वापस I40E_XDP_REसूची;
	पूर्ण

	चयन (act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		xdp_ring = rx_ring->vsi->xdp_rings[rx_ring->queue_index];
		result = i40e_xmit_xdp_tx_ring(xdp, xdp_ring);
		अगर (result == I40E_XDP_CONSUMED)
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
		result = I40E_XDP_CONSUMED;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस result;
पूर्ण

bool i40e_alloc_rx_buffers_zc(काष्ठा i40e_ring *rx_ring, u16 count)
अणु
	u16 ntu = rx_ring->next_to_use;
	जोड़ i40e_rx_desc *rx_desc;
	काष्ठा xdp_buff **bi, *xdp;
	dma_addr_t dma;
	bool ok = true;

	rx_desc = I40E_RX_DESC(rx_ring, ntu);
	bi = i40e_rx_bi(rx_ring, ntu);
	करो अणु
		xdp = xsk_buff_alloc(rx_ring->xsk_pool);
		अगर (!xdp) अणु
			ok = false;
			जाओ no_buffers;
		पूर्ण
		*bi = xdp;
		dma = xsk_buff_xdp_get_dma(xdp);
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(dma);
		rx_desc->पढ़ो.hdr_addr = 0;

		rx_desc++;
		bi++;
		ntu++;

		अगर (unlikely(ntu == rx_ring->count)) अणु
			rx_desc = I40E_RX_DESC(rx_ring, 0);
			bi = i40e_rx_bi(rx_ring, 0);
			ntu = 0;
		पूर्ण
	पूर्ण जबतक (--count);

no_buffers:
	अगर (rx_ring->next_to_use != ntu) अणु
		/* clear the status bits क्रम the next_to_use descriptor */
		rx_desc->wb.qword1.status_error_len = 0;
		i40e_release_rx_desc(rx_ring, ntu);
	पूर्ण

	वापस ok;
पूर्ण

/**
 * i40e_स्थिरruct_skb_zc - Create skbuff from zero-copy Rx buffer
 * @rx_ring: Rx ring
 * @xdp: xdp_buff
 *
 * This functions allocates a new skb from a zero-copy Rx buffer.
 *
 * Returns the skb, or शून्य on failure.
 **/
अटल काष्ठा sk_buff *i40e_स्थिरruct_skb_zc(काष्ठा i40e_ring *rx_ring,
					     काष्ठा xdp_buff *xdp)
अणु
	अचिन्हित पूर्णांक metasize = xdp->data - xdp->data_meta;
	अचिन्हित पूर्णांक datasize = xdp->data_end - xdp->data;
	काष्ठा sk_buff *skb;

	/* allocate a skb to store the frags */
	skb = __napi_alloc_skb(&rx_ring->q_vector->napi,
			       xdp->data_end - xdp->data_hard_start,
			       GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!skb))
		जाओ out;

	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	स_नकल(__skb_put(skb, datasize), xdp->data, datasize);
	अगर (metasize)
		skb_metadata_set(skb, metasize);

out:
	xsk_buff_मुक्त(xdp);
	वापस skb;
पूर्ण

अटल व्योम i40e_handle_xdp_result_zc(काष्ठा i40e_ring *rx_ring,
				      काष्ठा xdp_buff *xdp_buff,
				      जोड़ i40e_rx_desc *rx_desc,
				      अचिन्हित पूर्णांक *rx_packets,
				      अचिन्हित पूर्णांक *rx_bytes,
				      अचिन्हित पूर्णांक size,
				      अचिन्हित पूर्णांक xdp_res)
अणु
	काष्ठा sk_buff *skb;

	*rx_packets = 1;
	*rx_bytes = size;

	अगर (likely(xdp_res == I40E_XDP_REसूची) || xdp_res == I40E_XDP_TX)
		वापस;

	अगर (xdp_res == I40E_XDP_CONSUMED) अणु
		xsk_buff_मुक्त(xdp_buff);
		वापस;
	पूर्ण

	अगर (xdp_res == I40E_XDP_PASS) अणु
		/* NB! We are not checking क्रम errors using
		 * i40e_test_staterr with
		 * BIT(I40E_RXD_QW1_ERROR_SHIFT). This is due to that
		 * SBP is *not* set in PRT_SBPVSI (शेष not set).
		 */
		skb = i40e_स्थिरruct_skb_zc(rx_ring, xdp_buff);
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_buff_failed++;
			*rx_packets = 0;
			*rx_bytes = 0;
			वापस;
		पूर्ण

		अगर (eth_skb_pad(skb)) अणु
			*rx_packets = 0;
			*rx_bytes = 0;
			वापस;
		पूर्ण

		*rx_bytes = skb->len;
		i40e_process_skb_fields(rx_ring, rx_desc, skb);
		napi_gro_receive(&rx_ring->q_vector->napi, skb);
		वापस;
	पूर्ण

	/* Should never get here, as all valid हालs have been handled alपढ़ोy.
	 */
	WARN_ON_ONCE(1);
पूर्ण

/**
 * i40e_clean_rx_irq_zc - Consumes Rx packets from the hardware ring
 * @rx_ring: Rx ring
 * @budget: NAPI budget
 *
 * Returns amount of work completed
 **/
पूर्णांक i40e_clean_rx_irq_zc(काष्ठा i40e_ring *rx_ring, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;
	u16 cleaned_count = I40E_DESC_UNUSED(rx_ring);
	u16 next_to_clean = rx_ring->next_to_clean;
	u16 count_mask = rx_ring->count - 1;
	अचिन्हित पूर्णांक xdp_res, xdp_xmit = 0;
	bool failure = false;

	जबतक (likely(total_rx_packets < (अचिन्हित पूर्णांक)budget)) अणु
		जोड़ i40e_rx_desc *rx_desc;
		अचिन्हित पूर्णांक rx_packets;
		अचिन्हित पूर्णांक rx_bytes;
		काष्ठा xdp_buff *bi;
		अचिन्हित पूर्णांक size;
		u64 qword;

		rx_desc = I40E_RX_DESC(rx_ring, next_to_clean);
		qword = le64_to_cpu(rx_desc->wb.qword1.status_error_len);

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we have
		 * verअगरied the descriptor has been written back.
		 */
		dma_rmb();

		अगर (i40e_rx_is_programming_status(qword)) अणु
			i40e_clean_programming_status(rx_ring,
						      rx_desc->raw.qword[0],
						      qword);
			bi = *i40e_rx_bi(rx_ring, next_to_clean);
			xsk_buff_मुक्त(bi);
			next_to_clean = (next_to_clean + 1) & count_mask;
			जारी;
		पूर्ण

		size = (qword & I40E_RXD_QW1_LENGTH_PBUF_MASK) >>
		       I40E_RXD_QW1_LENGTH_PBUF_SHIFT;
		अगर (!size)
			अवरोध;

		bi = *i40e_rx_bi(rx_ring, next_to_clean);
		bi->data_end = bi->data + size;
		xsk_buff_dma_sync_क्रम_cpu(bi, rx_ring->xsk_pool);

		xdp_res = i40e_run_xdp_zc(rx_ring, bi);
		i40e_handle_xdp_result_zc(rx_ring, bi, rx_desc, &rx_packets,
					  &rx_bytes, size, xdp_res);
		total_rx_packets += rx_packets;
		total_rx_bytes += rx_bytes;
		xdp_xmit |= xdp_res & (I40E_XDP_TX | I40E_XDP_REसूची);
		next_to_clean = (next_to_clean + 1) & count_mask;
	पूर्ण

	rx_ring->next_to_clean = next_to_clean;
	cleaned_count = (next_to_clean - rx_ring->next_to_use - 1) & count_mask;

	अगर (cleaned_count >= I40E_RX_BUFFER_WRITE)
		failure = !i40e_alloc_rx_buffers_zc(rx_ring, cleaned_count);

	i40e_finalize_xdp_rx(rx_ring, xdp_xmit);
	i40e_update_rx_stats(rx_ring, total_rx_bytes, total_rx_packets);

	अगर (xsk_uses_need_wakeup(rx_ring->xsk_pool)) अणु
		अगर (failure || next_to_clean == rx_ring->next_to_use)
			xsk_set_rx_need_wakeup(rx_ring->xsk_pool);
		अन्यथा
			xsk_clear_rx_need_wakeup(rx_ring->xsk_pool);

		वापस (पूर्णांक)total_rx_packets;
	पूर्ण
	वापस failure ? budget : (पूर्णांक)total_rx_packets;
पूर्ण

अटल व्योम i40e_xmit_pkt(काष्ठा i40e_ring *xdp_ring, काष्ठा xdp_desc *desc,
			  अचिन्हित पूर्णांक *total_bytes)
अणु
	काष्ठा i40e_tx_desc *tx_desc;
	dma_addr_t dma;

	dma = xsk_buff_raw_get_dma(xdp_ring->xsk_pool, desc->addr);
	xsk_buff_raw_dma_sync_क्रम_device(xdp_ring->xsk_pool, dma, desc->len);

	tx_desc = I40E_TX_DESC(xdp_ring, xdp_ring->next_to_use++);
	tx_desc->buffer_addr = cpu_to_le64(dma);
	tx_desc->cmd_type_offset_bsz = build_ctob(I40E_TX_DESC_CMD_ICRC | I40E_TX_DESC_CMD_EOP,
						  0, desc->len, 0);

	*total_bytes += desc->len;
पूर्ण

अटल व्योम i40e_xmit_pkt_batch(काष्ठा i40e_ring *xdp_ring, काष्ठा xdp_desc *desc,
				अचिन्हित पूर्णांक *total_bytes)
अणु
	u16 ntu = xdp_ring->next_to_use;
	काष्ठा i40e_tx_desc *tx_desc;
	dma_addr_t dma;
	u32 i;

	loop_unrolled_क्रम(i = 0; i < PKTS_PER_BATCH; i++) अणु
		dma = xsk_buff_raw_get_dma(xdp_ring->xsk_pool, desc[i].addr);
		xsk_buff_raw_dma_sync_क्रम_device(xdp_ring->xsk_pool, dma, desc[i].len);

		tx_desc = I40E_TX_DESC(xdp_ring, ntu++);
		tx_desc->buffer_addr = cpu_to_le64(dma);
		tx_desc->cmd_type_offset_bsz = build_ctob(I40E_TX_DESC_CMD_ICRC |
							  I40E_TX_DESC_CMD_EOP,
							  0, desc[i].len, 0);

		*total_bytes += desc[i].len;
	पूर्ण

	xdp_ring->next_to_use = ntu;
पूर्ण

अटल व्योम i40e_fill_tx_hw_ring(काष्ठा i40e_ring *xdp_ring, काष्ठा xdp_desc *descs, u32 nb_pkts,
				 अचिन्हित पूर्णांक *total_bytes)
अणु
	u32 batched, leftover, i;

	batched = nb_pkts & ~(PKTS_PER_BATCH - 1);
	leftover = nb_pkts & (PKTS_PER_BATCH - 1);
	क्रम (i = 0; i < batched; i += PKTS_PER_BATCH)
		i40e_xmit_pkt_batch(xdp_ring, &descs[i], total_bytes);
	क्रम (i = batched; i < batched + leftover; i++)
		i40e_xmit_pkt(xdp_ring, &descs[i], total_bytes);
पूर्ण

अटल व्योम i40e_set_rs_bit(काष्ठा i40e_ring *xdp_ring)
अणु
	u16 ntu = xdp_ring->next_to_use ? xdp_ring->next_to_use - 1 : xdp_ring->count - 1;
	काष्ठा i40e_tx_desc *tx_desc;

	tx_desc = I40E_TX_DESC(xdp_ring, ntu);
	tx_desc->cmd_type_offset_bsz |= cpu_to_le64(I40E_TX_DESC_CMD_RS << I40E_TXD_QW1_CMD_SHIFT);
पूर्ण

/**
 * i40e_xmit_zc - Perक्रमms zero-copy Tx AF_XDP
 * @xdp_ring: XDP Tx ring
 * @budget: NAPI budget
 *
 * Returns true अगर the work is finished.
 **/
अटल bool i40e_xmit_zc(काष्ठा i40e_ring *xdp_ring, अचिन्हित पूर्णांक budget)
अणु
	काष्ठा xdp_desc *descs = xdp_ring->xsk_descs;
	u32 nb_pkts, nb_processed = 0;
	अचिन्हित पूर्णांक total_bytes = 0;

	nb_pkts = xsk_tx_peek_release_desc_batch(xdp_ring->xsk_pool, descs, budget);
	अगर (!nb_pkts)
		वापस true;

	अगर (xdp_ring->next_to_use + nb_pkts >= xdp_ring->count) अणु
		nb_processed = xdp_ring->count - xdp_ring->next_to_use;
		i40e_fill_tx_hw_ring(xdp_ring, descs, nb_processed, &total_bytes);
		xdp_ring->next_to_use = 0;
	पूर्ण

	i40e_fill_tx_hw_ring(xdp_ring, &descs[nb_processed], nb_pkts - nb_processed,
			     &total_bytes);

	/* Request an पूर्णांकerrupt क्रम the last frame and bump tail ptr. */
	i40e_set_rs_bit(xdp_ring);
	i40e_xdp_ring_update_tail(xdp_ring);

	i40e_update_tx_stats(xdp_ring, nb_pkts, total_bytes);

	वापस nb_pkts < budget;
पूर्ण

/**
 * i40e_clean_xdp_tx_buffer - Frees and unmaps an XDP Tx entry
 * @tx_ring: XDP Tx ring
 * @tx_bi: Tx buffer info to clean
 **/
अटल व्योम i40e_clean_xdp_tx_buffer(काष्ठा i40e_ring *tx_ring,
				     काष्ठा i40e_tx_buffer *tx_bi)
अणु
	xdp_वापस_frame(tx_bi->xdpf);
	tx_ring->xdp_tx_active--;
	dma_unmap_single(tx_ring->dev,
			 dma_unmap_addr(tx_bi, dma),
			 dma_unmap_len(tx_bi, len), DMA_TO_DEVICE);
	dma_unmap_len_set(tx_bi, len, 0);
पूर्ण

/**
 * i40e_clean_xdp_tx_irq - Completes AF_XDP entries, and cleans XDP entries
 * @vsi: Current VSI
 * @tx_ring: XDP Tx ring
 *
 * Returns true अगर cleanup/tranmission is करोne.
 **/
bool i40e_clean_xdp_tx_irq(काष्ठा i40e_vsi *vsi, काष्ठा i40e_ring *tx_ring)
अणु
	काष्ठा xsk_buff_pool *bp = tx_ring->xsk_pool;
	u32 i, completed_frames, xsk_frames = 0;
	u32 head_idx = i40e_get_head(tx_ring);
	काष्ठा i40e_tx_buffer *tx_bi;
	अचिन्हित पूर्णांक ntc;

	अगर (head_idx < tx_ring->next_to_clean)
		head_idx += tx_ring->count;
	completed_frames = head_idx - tx_ring->next_to_clean;

	अगर (completed_frames == 0)
		जाओ out_xmit;

	अगर (likely(!tx_ring->xdp_tx_active)) अणु
		xsk_frames = completed_frames;
		जाओ skip;
	पूर्ण

	ntc = tx_ring->next_to_clean;

	क्रम (i = 0; i < completed_frames; i++) अणु
		tx_bi = &tx_ring->tx_bi[ntc];

		अगर (tx_bi->xdpf) अणु
			i40e_clean_xdp_tx_buffer(tx_ring, tx_bi);
			tx_bi->xdpf = शून्य;
		पूर्ण अन्यथा अणु
			xsk_frames++;
		पूर्ण

		अगर (++ntc >= tx_ring->count)
			ntc = 0;
	पूर्ण

skip:
	tx_ring->next_to_clean += completed_frames;
	अगर (unlikely(tx_ring->next_to_clean >= tx_ring->count))
		tx_ring->next_to_clean -= tx_ring->count;

	अगर (xsk_frames)
		xsk_tx_completed(bp, xsk_frames);

	i40e_arm_wb(tx_ring, vsi, completed_frames);

out_xmit:
	अगर (xsk_uses_need_wakeup(tx_ring->xsk_pool))
		xsk_set_tx_need_wakeup(tx_ring->xsk_pool);

	वापस i40e_xmit_zc(tx_ring, I40E_DESC_UNUSED(tx_ring));
पूर्ण

/**
 * i40e_xsk_wakeup - Implements the nकरो_xsk_wakeup
 * @dev: the netdevice
 * @queue_id: queue id to wake up
 * @flags: ignored in our हाल since we have Rx and Tx in the same NAPI.
 *
 * Returns <0 क्रम errors, 0 otherwise.
 **/
पूर्णांक i40e_xsk_wakeup(काष्ठा net_device *dev, u32 queue_id, u32 flags)
अणु
	काष्ठा i40e_netdev_priv *np = netdev_priv(dev);
	काष्ठा i40e_vsi *vsi = np->vsi;
	काष्ठा i40e_pf *pf = vsi->back;
	काष्ठा i40e_ring *ring;

	अगर (test_bit(__I40E_CONFIG_BUSY, pf->state))
		वापस -EAGAIN;

	अगर (test_bit(__I40E_VSI_DOWN, vsi->state))
		वापस -ENETDOWN;

	अगर (!i40e_enabled_xdp_vsi(vsi))
		वापस -ENXIO;

	अगर (queue_id >= vsi->num_queue_pairs)
		वापस -ENXIO;

	अगर (!vsi->xdp_rings[queue_id]->xsk_pool)
		वापस -ENXIO;

	ring = vsi->xdp_rings[queue_id];

	/* The idea here is that अगर NAPI is running, mark a miss, so
	 * it will run again. If not, trigger an पूर्णांकerrupt and
	 * schedule the NAPI from पूर्णांकerrupt context. If NAPI would be
	 * scheduled here, the पूर्णांकerrupt affinity would not be
	 * honored.
	 */
	अगर (!napi_अगर_scheduled_mark_missed(&ring->q_vector->napi))
		i40e_क्रमce_wb(vsi, ring->q_vector);

	वापस 0;
पूर्ण

व्योम i40e_xsk_clean_rx_ring(काष्ठा i40e_ring *rx_ring)
अणु
	u16 count_mask = rx_ring->count - 1;
	u16 ntc = rx_ring->next_to_clean;
	u16 ntu = rx_ring->next_to_use;

	क्रम ( ; ntc != ntu; ntc = (ntc + 1)  & count_mask) अणु
		काष्ठा xdp_buff *rx_bi = *i40e_rx_bi(rx_ring, ntc);

		xsk_buff_मुक्त(rx_bi);
	पूर्ण
पूर्ण

/**
 * i40e_xsk_clean_tx_ring - Clean the XDP Tx ring on shutकरोwn
 * @tx_ring: XDP Tx ring
 **/
व्योम i40e_xsk_clean_tx_ring(काष्ठा i40e_ring *tx_ring)
अणु
	u16 ntc = tx_ring->next_to_clean, ntu = tx_ring->next_to_use;
	काष्ठा xsk_buff_pool *bp = tx_ring->xsk_pool;
	काष्ठा i40e_tx_buffer *tx_bi;
	u32 xsk_frames = 0;

	जबतक (ntc != ntu) अणु
		tx_bi = &tx_ring->tx_bi[ntc];

		अगर (tx_bi->xdpf)
			i40e_clean_xdp_tx_buffer(tx_ring, tx_bi);
		अन्यथा
			xsk_frames++;

		tx_bi->xdpf = शून्य;

		ntc++;
		अगर (ntc >= tx_ring->count)
			ntc = 0;
	पूर्ण

	अगर (xsk_frames)
		xsk_tx_completed(bp, xsk_frames);
पूर्ण

/**
 * i40e_xsk_any_rx_ring_enabled - Checks अगर Rx rings have an AF_XDP
 * buffer pool attached
 * @vsi: vsi
 *
 * Returns true अगर any of the Rx rings has an AF_XDP buffer pool attached
 **/
bool i40e_xsk_any_rx_ring_enabled(काष्ठा i40e_vsi *vsi)
अणु
	काष्ठा net_device *netdev = vsi->netdev;
	पूर्णांक i;

	क्रम (i = 0; i < vsi->num_queue_pairs; i++) अणु
		अगर (xsk_get_pool_from_qid(netdev, i))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
