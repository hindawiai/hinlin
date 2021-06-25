<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Intel Corporation. */

#समावेश <linux/bpf_trace.h>
#समावेश <net/xdp_sock_drv.h>
#समावेश <net/xdp.h>
#समावेश "ice.h"
#समावेश "ice_base.h"
#समावेश "ice_type.h"
#समावेश "ice_xsk.h"
#समावेश "ice_txrx.h"
#समावेश "ice_txrx_lib.h"
#समावेश "ice_lib.h"

/**
 * ice_qp_reset_stats - Resets all stats क्रम rings of given index
 * @vsi: VSI that contains rings of पूर्णांकerest
 * @q_idx: ring index in array
 */
अटल व्योम ice_qp_reset_stats(काष्ठा ice_vsi *vsi, u16 q_idx)
अणु
	स_रखो(&vsi->rx_rings[q_idx]->rx_stats, 0,
	       माप(vsi->rx_rings[q_idx]->rx_stats));
	स_रखो(&vsi->tx_rings[q_idx]->stats, 0,
	       माप(vsi->tx_rings[q_idx]->stats));
	अगर (ice_is_xdp_ena_vsi(vsi))
		स_रखो(&vsi->xdp_rings[q_idx]->stats, 0,
		       माप(vsi->xdp_rings[q_idx]->stats));
पूर्ण

/**
 * ice_qp_clean_rings - Cleans all the rings of a given index
 * @vsi: VSI that contains rings of पूर्णांकerest
 * @q_idx: ring index in array
 */
अटल व्योम ice_qp_clean_rings(काष्ठा ice_vsi *vsi, u16 q_idx)
अणु
	ice_clean_tx_ring(vsi->tx_rings[q_idx]);
	अगर (ice_is_xdp_ena_vsi(vsi))
		ice_clean_tx_ring(vsi->xdp_rings[q_idx]);
	ice_clean_rx_ring(vsi->rx_rings[q_idx]);
पूर्ण

/**
 * ice_qvec_toggle_napi - Enables/disables NAPI क्रम a given q_vector
 * @vsi: VSI that has netdev
 * @q_vector: q_vector that has NAPI context
 * @enable: true क्रम enable, false क्रम disable
 */
अटल व्योम
ice_qvec_toggle_napi(काष्ठा ice_vsi *vsi, काष्ठा ice_q_vector *q_vector,
		     bool enable)
अणु
	अगर (!vsi->netdev || !q_vector)
		वापस;

	अगर (enable)
		napi_enable(&q_vector->napi);
	अन्यथा
		napi_disable(&q_vector->napi);
पूर्ण

/**
 * ice_qvec_dis_irq - Mask off queue पूर्णांकerrupt generation on given ring
 * @vsi: the VSI that contains queue vector being un-configured
 * @rx_ring: Rx ring that will have its IRQ disabled
 * @q_vector: queue vector
 */
अटल व्योम
ice_qvec_dis_irq(काष्ठा ice_vsi *vsi, काष्ठा ice_ring *rx_ring,
		 काष्ठा ice_q_vector *q_vector)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	पूर्णांक base = vsi->base_vector;
	u16 reg;
	u32 val;

	/* QINT_TQCTL is being cleared in ice_vsi_stop_tx_ring, so handle
	 * here only QINT_RQCTL
	 */
	reg = rx_ring->reg_idx;
	val = rd32(hw, QINT_RQCTL(reg));
	val &= ~QINT_RQCTL_CAUSE_ENA_M;
	wr32(hw, QINT_RQCTL(reg), val);

	अगर (q_vector) अणु
		u16 v_idx = q_vector->v_idx;

		wr32(hw, GLINT_DYN_CTL(q_vector->reg_idx), 0);
		ice_flush(hw);
		synchronize_irq(pf->msix_entries[v_idx + base].vector);
	पूर्ण
पूर्ण

/**
 * ice_qvec_cfg_msix - Enable IRQ क्रम given queue vector
 * @vsi: the VSI that contains queue vector
 * @q_vector: queue vector
 */
अटल व्योम
ice_qvec_cfg_msix(काष्ठा ice_vsi *vsi, काष्ठा ice_q_vector *q_vector)
अणु
	u16 reg_idx = q_vector->reg_idx;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	काष्ठा ice_ring *ring;

	ice_cfg_itr(hw, q_vector);

	ice_क्रम_each_ring(ring, q_vector->tx)
		ice_cfg_txq_पूर्णांकerrupt(vsi, ring->reg_idx, reg_idx,
				      q_vector->tx.itr_idx);

	ice_क्रम_each_ring(ring, q_vector->rx)
		ice_cfg_rxq_पूर्णांकerrupt(vsi, ring->reg_idx, reg_idx,
				      q_vector->rx.itr_idx);

	ice_flush(hw);
पूर्ण

/**
 * ice_qvec_ena_irq - Enable IRQ क्रम given queue vector
 * @vsi: the VSI that contains queue vector
 * @q_vector: queue vector
 */
अटल व्योम ice_qvec_ena_irq(काष्ठा ice_vsi *vsi, काष्ठा ice_q_vector *q_vector)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;

	ice_irq_dynamic_ena(hw, vsi, q_vector);

	ice_flush(hw);
पूर्ण

/**
 * ice_qp_dis - Disables a queue pair
 * @vsi: VSI of पूर्णांकerest
 * @q_idx: ring index in array
 *
 * Returns 0 on success, negative on failure.
 */
अटल पूर्णांक ice_qp_dis(काष्ठा ice_vsi *vsi, u16 q_idx)
अणु
	काष्ठा ice_txq_meta txq_meta = अणु पूर्ण;
	काष्ठा ice_ring *tx_ring, *rx_ring;
	काष्ठा ice_q_vector *q_vector;
	पूर्णांक समयout = 50;
	पूर्णांक err;

	अगर (q_idx >= vsi->num_rxq || q_idx >= vsi->num_txq)
		वापस -EINVAL;

	tx_ring = vsi->tx_rings[q_idx];
	rx_ring = vsi->rx_rings[q_idx];
	q_vector = rx_ring->q_vector;

	जबतक (test_and_set_bit(ICE_CFG_BUSY, vsi->state)) अणु
		समयout--;
		अगर (!समयout)
			वापस -EBUSY;
		usleep_range(1000, 2000);
	पूर्ण
	netअगर_tx_stop_queue(netdev_get_tx_queue(vsi->netdev, q_idx));

	ice_qvec_dis_irq(vsi, rx_ring, q_vector);

	ice_fill_txq_meta(vsi, tx_ring, &txq_meta);
	err = ice_vsi_stop_tx_ring(vsi, ICE_NO_RESET, 0, tx_ring, &txq_meta);
	अगर (err)
		वापस err;
	अगर (ice_is_xdp_ena_vsi(vsi)) अणु
		काष्ठा ice_ring *xdp_ring = vsi->xdp_rings[q_idx];

		स_रखो(&txq_meta, 0, माप(txq_meta));
		ice_fill_txq_meta(vsi, xdp_ring, &txq_meta);
		err = ice_vsi_stop_tx_ring(vsi, ICE_NO_RESET, 0, xdp_ring,
					   &txq_meta);
		अगर (err)
			वापस err;
	पूर्ण
	err = ice_vsi_ctrl_one_rx_ring(vsi, false, q_idx, true);
	अगर (err)
		वापस err;

	ice_qvec_toggle_napi(vsi, q_vector, false);
	ice_qp_clean_rings(vsi, q_idx);
	ice_qp_reset_stats(vsi, q_idx);

	वापस 0;
पूर्ण

/**
 * ice_qp_ena - Enables a queue pair
 * @vsi: VSI of पूर्णांकerest
 * @q_idx: ring index in array
 *
 * Returns 0 on success, negative on failure.
 */
अटल पूर्णांक ice_qp_ena(काष्ठा ice_vsi *vsi, u16 q_idx)
अणु
	काष्ठा ice_aqc_add_tx_qgrp *qg_buf;
	काष्ठा ice_ring *tx_ring, *rx_ring;
	काष्ठा ice_q_vector *q_vector;
	u16 size;
	पूर्णांक err;

	अगर (q_idx >= vsi->num_rxq || q_idx >= vsi->num_txq)
		वापस -EINVAL;

	size = काष्ठा_size(qg_buf, txqs, 1);
	qg_buf = kzalloc(size, GFP_KERNEL);
	अगर (!qg_buf)
		वापस -ENOMEM;

	qg_buf->num_txqs = 1;

	tx_ring = vsi->tx_rings[q_idx];
	rx_ring = vsi->rx_rings[q_idx];
	q_vector = rx_ring->q_vector;

	err = ice_vsi_cfg_txq(vsi, tx_ring, qg_buf);
	अगर (err)
		जाओ मुक्त_buf;

	अगर (ice_is_xdp_ena_vsi(vsi)) अणु
		काष्ठा ice_ring *xdp_ring = vsi->xdp_rings[q_idx];

		स_रखो(qg_buf, 0, size);
		qg_buf->num_txqs = 1;
		err = ice_vsi_cfg_txq(vsi, xdp_ring, qg_buf);
		अगर (err)
			जाओ मुक्त_buf;
		ice_set_ring_xdp(xdp_ring);
		xdp_ring->xsk_pool = ice_xsk_pool(xdp_ring);
	पूर्ण

	err = ice_setup_rx_ctx(rx_ring);
	अगर (err)
		जाओ मुक्त_buf;

	ice_qvec_cfg_msix(vsi, q_vector);

	err = ice_vsi_ctrl_one_rx_ring(vsi, true, q_idx, true);
	अगर (err)
		जाओ मुक्त_buf;

	clear_bit(ICE_CFG_BUSY, vsi->state);
	ice_qvec_toggle_napi(vsi, q_vector, true);
	ice_qvec_ena_irq(vsi, q_vector);

	netअगर_tx_start_queue(netdev_get_tx_queue(vsi->netdev, q_idx));
मुक्त_buf:
	kमुक्त(qg_buf);
	वापस err;
पूर्ण

/**
 * ice_xsk_pool_disable - disable a buffer pool region
 * @vsi: Current VSI
 * @qid: queue ID
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक ice_xsk_pool_disable(काष्ठा ice_vsi *vsi, u16 qid)
अणु
	काष्ठा xsk_buff_pool *pool = xsk_get_pool_from_qid(vsi->netdev, qid);

	अगर (!pool)
		वापस -EINVAL;

	clear_bit(qid, vsi->af_xdp_zc_qps);
	xsk_pool_dma_unmap(pool, ICE_RX_DMA_ATTR);

	वापस 0;
पूर्ण

/**
 * ice_xsk_pool_enable - enable a buffer pool region
 * @vsi: Current VSI
 * @pool: poपूर्णांकer to a requested buffer pool region
 * @qid: queue ID
 *
 * Returns 0 on success, negative on failure
 */
अटल पूर्णांक
ice_xsk_pool_enable(काष्ठा ice_vsi *vsi, काष्ठा xsk_buff_pool *pool, u16 qid)
अणु
	पूर्णांक err;

	अगर (vsi->type != ICE_VSI_PF)
		वापस -EINVAL;

	अगर (qid >= vsi->netdev->real_num_rx_queues ||
	    qid >= vsi->netdev->real_num_tx_queues)
		वापस -EINVAL;

	err = xsk_pool_dma_map(pool, ice_pf_to_dev(vsi->back),
			       ICE_RX_DMA_ATTR);
	अगर (err)
		वापस err;

	set_bit(qid, vsi->af_xdp_zc_qps);

	वापस 0;
पूर्ण

/**
 * ice_xsk_pool_setup - enable/disable a buffer pool region depending on its state
 * @vsi: Current VSI
 * @pool: buffer pool to enable/associate to a ring, शून्य to disable
 * @qid: queue ID
 *
 * Returns 0 on success, negative on failure
 */
पूर्णांक ice_xsk_pool_setup(काष्ठा ice_vsi *vsi, काष्ठा xsk_buff_pool *pool, u16 qid)
अणु
	bool अगर_running, pool_present = !!pool;
	पूर्णांक ret = 0, pool_failure = 0;

	अगर_running = netअगर_running(vsi->netdev) && ice_is_xdp_ena_vsi(vsi);

	अगर (अगर_running) अणु
		ret = ice_qp_dis(vsi, qid);
		अगर (ret) अणु
			netdev_err(vsi->netdev, "ice_qp_dis error = %d\n", ret);
			जाओ xsk_pool_अगर_up;
		पूर्ण
	पूर्ण

	pool_failure = pool_present ? ice_xsk_pool_enable(vsi, pool, qid) :
				      ice_xsk_pool_disable(vsi, qid);

xsk_pool_अगर_up:
	अगर (अगर_running) अणु
		ret = ice_qp_ena(vsi, qid);
		अगर (!ret && pool_present)
			napi_schedule(&vsi->xdp_rings[qid]->q_vector->napi);
		अन्यथा अगर (ret)
			netdev_err(vsi->netdev, "ice_qp_ena error = %d\n", ret);
	पूर्ण

	अगर (pool_failure) अणु
		netdev_err(vsi->netdev, "Could not %sable buffer pool, error = %d\n",
			   pool_present ? "en" : "dis", pool_failure);
		वापस pool_failure;
	पूर्ण

	वापस ret;
पूर्ण

/**
 * ice_alloc_rx_bufs_zc - allocate a number of Rx buffers
 * @rx_ring: Rx ring
 * @count: The number of buffers to allocate
 *
 * This function allocates a number of Rx buffers from the fill ring
 * or the पूर्णांकernal recycle mechanism and places them on the Rx ring.
 *
 * Returns true अगर all allocations were successful, false अगर any fail.
 */
bool ice_alloc_rx_bufs_zc(काष्ठा ice_ring *rx_ring, u16 count)
अणु
	जोड़ ice_32b_rx_flex_desc *rx_desc;
	u16 ntu = rx_ring->next_to_use;
	काष्ठा ice_rx_buf *rx_buf;
	bool ok = true;
	dma_addr_t dma;

	अगर (!count)
		वापस true;

	rx_desc = ICE_RX_DESC(rx_ring, ntu);
	rx_buf = &rx_ring->rx_buf[ntu];

	करो अणु
		rx_buf->xdp = xsk_buff_alloc(rx_ring->xsk_pool);
		अगर (!rx_buf->xdp) अणु
			ok = false;
			अवरोध;
		पूर्ण

		dma = xsk_buff_xdp_get_dma(rx_buf->xdp);
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(dma);
		rx_desc->wb.status_error0 = 0;

		rx_desc++;
		rx_buf++;
		ntu++;

		अगर (unlikely(ntu == rx_ring->count)) अणु
			rx_desc = ICE_RX_DESC(rx_ring, 0);
			rx_buf = rx_ring->rx_buf;
			ntu = 0;
		पूर्ण
	पूर्ण जबतक (--count);

	अगर (rx_ring->next_to_use != ntu) अणु
		/* clear the status bits क्रम the next_to_use descriptor */
		rx_desc->wb.status_error0 = 0;
		ice_release_rx_desc(rx_ring, ntu);
	पूर्ण

	वापस ok;
पूर्ण

/**
 * ice_bump_ntc - Bump the next_to_clean counter of an Rx ring
 * @rx_ring: Rx ring
 */
अटल व्योम ice_bump_ntc(काष्ठा ice_ring *rx_ring)
अणु
	पूर्णांक ntc = rx_ring->next_to_clean + 1;

	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;
	prefetch(ICE_RX_DESC(rx_ring, ntc));
पूर्ण

/**
 * ice_स्थिरruct_skb_zc - Create an sk_buff from zero-copy buffer
 * @rx_ring: Rx ring
 * @rx_buf: zero-copy Rx buffer
 *
 * This function allocates a new skb from a zero-copy Rx buffer.
 *
 * Returns the skb on success, शून्य on failure.
 */
अटल काष्ठा sk_buff *
ice_स्थिरruct_skb_zc(काष्ठा ice_ring *rx_ring, काष्ठा ice_rx_buf *rx_buf)
अणु
	अचिन्हित पूर्णांक metasize = rx_buf->xdp->data - rx_buf->xdp->data_meta;
	अचिन्हित पूर्णांक datasize = rx_buf->xdp->data_end - rx_buf->xdp->data;
	अचिन्हित पूर्णांक datasize_hard = rx_buf->xdp->data_end -
				     rx_buf->xdp->data_hard_start;
	काष्ठा sk_buff *skb;

	skb = __napi_alloc_skb(&rx_ring->q_vector->napi, datasize_hard,
			       GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!skb))
		वापस शून्य;

	skb_reserve(skb, rx_buf->xdp->data - rx_buf->xdp->data_hard_start);
	स_नकल(__skb_put(skb, datasize), rx_buf->xdp->data, datasize);
	अगर (metasize)
		skb_metadata_set(skb, metasize);

	xsk_buff_मुक्त(rx_buf->xdp);
	rx_buf->xdp = शून्य;
	वापस skb;
पूर्ण

/**
 * ice_run_xdp_zc - Executes an XDP program in zero-copy path
 * @rx_ring: Rx ring
 * @xdp: xdp_buff used as input to the XDP program
 *
 * Returns any of ICE_XDP_अणुPASS, CONSUMED, TX, REसूचीपूर्ण
 */
अटल पूर्णांक
ice_run_xdp_zc(काष्ठा ice_ring *rx_ring, काष्ठा xdp_buff *xdp)
अणु
	पूर्णांक err, result = ICE_XDP_PASS;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा ice_ring *xdp_ring;
	u32 act;

	rcu_पढ़ो_lock();
	/* ZC patch is enabled only when XDP program is set,
	 * so here it can not be शून्य
	 */
	xdp_prog = READ_ONCE(rx_ring->xdp_prog);

	act = bpf_prog_run_xdp(xdp_prog, xdp);

	अगर (likely(act == XDP_REसूचीECT)) अणु
		err = xdp_करो_redirect(rx_ring->netdev, xdp, xdp_prog);
		अगर (err)
			जाओ out_failure;
		rcu_पढ़ो_unlock();
		वापस ICE_XDP_REसूची;
	पूर्ण

	चयन (act) अणु
	हाल XDP_PASS:
		अवरोध;
	हाल XDP_TX:
		xdp_ring = rx_ring->vsi->xdp_rings[rx_ring->q_index];
		result = ice_xmit_xdp_buff(xdp, xdp_ring);
		अगर (result == ICE_XDP_CONSUMED)
			जाओ out_failure;
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
out_failure:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, act);
		fallthrough;
	हाल XDP_DROP:
		result = ICE_XDP_CONSUMED;
		अवरोध;
	पूर्ण

	rcu_पढ़ो_unlock();
	वापस result;
पूर्ण

/**
 * ice_clean_rx_irq_zc - consumes packets from the hardware ring
 * @rx_ring: AF_XDP Rx ring
 * @budget: NAPI budget
 *
 * Returns number of processed packets on success, reमुख्यing budget on failure.
 */
पूर्णांक ice_clean_rx_irq_zc(काष्ठा ice_ring *rx_ring, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_packets = 0;
	u16 cleaned_count = ICE_DESC_UNUSED(rx_ring);
	अचिन्हित पूर्णांक xdp_xmit = 0;
	bool failure = false;

	जबतक (likely(total_rx_packets < (अचिन्हित पूर्णांक)budget)) अणु
		जोड़ ice_32b_rx_flex_desc *rx_desc;
		अचिन्हित पूर्णांक size, xdp_res = 0;
		काष्ठा ice_rx_buf *rx_buf;
		काष्ठा sk_buff *skb;
		u16 stat_err_bits;
		u16 vlan_tag = 0;
		u8 rx_ptype;

		rx_desc = ICE_RX_DESC(rx_ring, rx_ring->next_to_clean);

		stat_err_bits = BIT(ICE_RX_FLEX_DESC_STATUS0_DD_S);
		अगर (!ice_test_staterr(rx_desc, stat_err_bits))
			अवरोध;

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we have
		 * verअगरied the descriptor has been written back.
		 */
		dma_rmb();

		size = le16_to_cpu(rx_desc->wb.pkt_len) &
				   ICE_RX_FLX_DESC_PKT_LEN_M;
		अगर (!size)
			अवरोध;

		rx_buf = &rx_ring->rx_buf[rx_ring->next_to_clean];
		rx_buf->xdp->data_end = rx_buf->xdp->data + size;
		xsk_buff_dma_sync_क्रम_cpu(rx_buf->xdp, rx_ring->xsk_pool);

		xdp_res = ice_run_xdp_zc(rx_ring, rx_buf->xdp);
		अगर (xdp_res) अणु
			अगर (xdp_res & (ICE_XDP_TX | ICE_XDP_REसूची))
				xdp_xmit |= xdp_res;
			अन्यथा
				xsk_buff_मुक्त(rx_buf->xdp);

			rx_buf->xdp = शून्य;
			total_rx_bytes += size;
			total_rx_packets++;
			cleaned_count++;

			ice_bump_ntc(rx_ring);
			जारी;
		पूर्ण

		/* XDP_PASS path */
		skb = ice_स्थिरruct_skb_zc(rx_ring, rx_buf);
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_buf_failed++;
			अवरोध;
		पूर्ण

		cleaned_count++;
		ice_bump_ntc(rx_ring);

		अगर (eth_skb_pad(skb)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		total_rx_bytes += skb->len;
		total_rx_packets++;

		stat_err_bits = BIT(ICE_RX_FLEX_DESC_STATUS0_L2TAG1P_S);
		अगर (ice_test_staterr(rx_desc, stat_err_bits))
			vlan_tag = le16_to_cpu(rx_desc->wb.l2tag1);

		rx_ptype = le16_to_cpu(rx_desc->wb.ptype_flex_flags0) &
				       ICE_RX_FLEX_DESC_PTYPE_M;

		ice_process_skb_fields(rx_ring, rx_desc, skb, rx_ptype);
		ice_receive_skb(rx_ring, skb, vlan_tag);
	पूर्ण

	अगर (cleaned_count >= ICE_RX_BUF_WRITE)
		failure = !ice_alloc_rx_bufs_zc(rx_ring, cleaned_count);

	ice_finalize_xdp_rx(rx_ring, xdp_xmit);
	ice_update_rx_ring_stats(rx_ring, total_rx_packets, total_rx_bytes);

	अगर (xsk_uses_need_wakeup(rx_ring->xsk_pool)) अणु
		अगर (failure || rx_ring->next_to_clean == rx_ring->next_to_use)
			xsk_set_rx_need_wakeup(rx_ring->xsk_pool);
		अन्यथा
			xsk_clear_rx_need_wakeup(rx_ring->xsk_pool);

		वापस (पूर्णांक)total_rx_packets;
	पूर्ण

	वापस failure ? budget : (पूर्णांक)total_rx_packets;
पूर्ण

/**
 * ice_xmit_zc - Completes AF_XDP entries, and cleans XDP entries
 * @xdp_ring: XDP Tx ring
 * @budget: max number of frames to xmit
 *
 * Returns true अगर cleanup/transmission is करोne.
 */
अटल bool ice_xmit_zc(काष्ठा ice_ring *xdp_ring, पूर्णांक budget)
अणु
	काष्ठा ice_tx_desc *tx_desc = शून्य;
	bool work_करोne = true;
	काष्ठा xdp_desc desc;
	dma_addr_t dma;

	जबतक (likely(budget-- > 0)) अणु
		काष्ठा ice_tx_buf *tx_buf;

		अगर (unlikely(!ICE_DESC_UNUSED(xdp_ring))) अणु
			xdp_ring->tx_stats.tx_busy++;
			work_करोne = false;
			अवरोध;
		पूर्ण

		tx_buf = &xdp_ring->tx_buf[xdp_ring->next_to_use];

		अगर (!xsk_tx_peek_desc(xdp_ring->xsk_pool, &desc))
			अवरोध;

		dma = xsk_buff_raw_get_dma(xdp_ring->xsk_pool, desc.addr);
		xsk_buff_raw_dma_sync_क्रम_device(xdp_ring->xsk_pool, dma,
						 desc.len);

		tx_buf->bytecount = desc.len;

		tx_desc = ICE_TX_DESC(xdp_ring, xdp_ring->next_to_use);
		tx_desc->buf_addr = cpu_to_le64(dma);
		tx_desc->cmd_type_offset_bsz =
			ice_build_ctob(ICE_TXD_LAST_DESC_CMD, 0, desc.len, 0);

		xdp_ring->next_to_use++;
		अगर (xdp_ring->next_to_use == xdp_ring->count)
			xdp_ring->next_to_use = 0;
	पूर्ण

	अगर (tx_desc) अणु
		ice_xdp_ring_update_tail(xdp_ring);
		xsk_tx_release(xdp_ring->xsk_pool);
	पूर्ण

	वापस budget > 0 && work_करोne;
पूर्ण

/**
 * ice_clean_xdp_tx_buf - Free and unmap XDP Tx buffer
 * @xdp_ring: XDP Tx ring
 * @tx_buf: Tx buffer to clean
 */
अटल व्योम
ice_clean_xdp_tx_buf(काष्ठा ice_ring *xdp_ring, काष्ठा ice_tx_buf *tx_buf)
अणु
	xdp_वापस_frame((काष्ठा xdp_frame *)tx_buf->raw_buf);
	dma_unmap_single(xdp_ring->dev, dma_unmap_addr(tx_buf, dma),
			 dma_unmap_len(tx_buf, len), DMA_TO_DEVICE);
	dma_unmap_len_set(tx_buf, len, 0);
पूर्ण

/**
 * ice_clean_tx_irq_zc - Completes AF_XDP entries, and cleans XDP entries
 * @xdp_ring: XDP Tx ring
 * @budget: NAPI budget
 *
 * Returns true अगर cleanup/tranmission is करोne.
 */
bool ice_clean_tx_irq_zc(काष्ठा ice_ring *xdp_ring, पूर्णांक budget)
अणु
	पूर्णांक total_packets = 0, total_bytes = 0;
	s16 ntc = xdp_ring->next_to_clean;
	काष्ठा ice_tx_desc *tx_desc;
	काष्ठा ice_tx_buf *tx_buf;
	u32 xsk_frames = 0;
	bool xmit_करोne;

	tx_desc = ICE_TX_DESC(xdp_ring, ntc);
	tx_buf = &xdp_ring->tx_buf[ntc];
	ntc -= xdp_ring->count;

	करो अणु
		अगर (!(tx_desc->cmd_type_offset_bsz &
		      cpu_to_le64(ICE_TX_DESC_DTYPE_DESC_DONE)))
			अवरोध;

		total_bytes += tx_buf->bytecount;
		total_packets++;

		अगर (tx_buf->raw_buf) अणु
			ice_clean_xdp_tx_buf(xdp_ring, tx_buf);
			tx_buf->raw_buf = शून्य;
		पूर्ण अन्यथा अणु
			xsk_frames++;
		पूर्ण

		tx_desc->cmd_type_offset_bsz = 0;
		tx_buf++;
		tx_desc++;
		ntc++;

		अगर (unlikely(!ntc)) अणु
			ntc -= xdp_ring->count;
			tx_buf = xdp_ring->tx_buf;
			tx_desc = ICE_TX_DESC(xdp_ring, 0);
		पूर्ण

		prefetch(tx_desc);

	पूर्ण जबतक (likely(--budget));

	ntc += xdp_ring->count;
	xdp_ring->next_to_clean = ntc;

	अगर (xsk_frames)
		xsk_tx_completed(xdp_ring->xsk_pool, xsk_frames);

	अगर (xsk_uses_need_wakeup(xdp_ring->xsk_pool))
		xsk_set_tx_need_wakeup(xdp_ring->xsk_pool);

	ice_update_tx_ring_stats(xdp_ring, total_packets, total_bytes);
	xmit_करोne = ice_xmit_zc(xdp_ring, ICE_DFLT_IRQ_WORK);

	वापस budget > 0 && xmit_करोne;
पूर्ण

/**
 * ice_xsk_wakeup - Implements nकरो_xsk_wakeup
 * @netdev: net_device
 * @queue_id: queue to wake up
 * @flags: ignored in our हाल, since we have Rx and Tx in the same NAPI
 *
 * Returns negative on error, zero otherwise.
 */
पूर्णांक
ice_xsk_wakeup(काष्ठा net_device *netdev, u32 queue_id,
	       u32 __always_unused flags)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_q_vector *q_vector;
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_ring *ring;

	अगर (test_bit(ICE_DOWN, vsi->state))
		वापस -ENETDOWN;

	अगर (!ice_is_xdp_ena_vsi(vsi))
		वापस -ENXIO;

	अगर (queue_id >= vsi->num_txq)
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
	q_vector = ring->q_vector;
	अगर (!napi_अगर_scheduled_mark_missed(&q_vector->napi))
		ice_trigger_sw_पूर्णांकr(&vsi->back->hw, q_vector);

	वापस 0;
पूर्ण

/**
 * ice_xsk_any_rx_ring_ena - Checks अगर Rx rings have AF_XDP buff pool attached
 * @vsi: VSI to be checked
 *
 * Returns true अगर any of the Rx rings has an AF_XDP buff pool attached
 */
bool ice_xsk_any_rx_ring_ena(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक i;

	ice_क्रम_each_rxq(vsi, i) अणु
		अगर (xsk_get_pool_from_qid(vsi->netdev, i))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ice_xsk_clean_rx_ring - clean buffer pool queues connected to a given Rx ring
 * @rx_ring: ring to be cleaned
 */
व्योम ice_xsk_clean_rx_ring(काष्ठा ice_ring *rx_ring)
अणु
	u16 i;

	क्रम (i = 0; i < rx_ring->count; i++) अणु
		काष्ठा ice_rx_buf *rx_buf = &rx_ring->rx_buf[i];

		अगर (!rx_buf->xdp)
			जारी;

		rx_buf->xdp = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_xsk_clean_xdp_ring - Clean the XDP Tx ring and its buffer pool queues
 * @xdp_ring: XDP_Tx ring
 */
व्योम ice_xsk_clean_xdp_ring(काष्ठा ice_ring *xdp_ring)
अणु
	u16 ntc = xdp_ring->next_to_clean, ntu = xdp_ring->next_to_use;
	u32 xsk_frames = 0;

	जबतक (ntc != ntu) अणु
		काष्ठा ice_tx_buf *tx_buf = &xdp_ring->tx_buf[ntc];

		अगर (tx_buf->raw_buf)
			ice_clean_xdp_tx_buf(xdp_ring, tx_buf);
		अन्यथा
			xsk_frames++;

		tx_buf->raw_buf = शून्य;

		ntc++;
		अगर (ntc >= xdp_ring->count)
			ntc = 0;
	पूर्ण

	अगर (xsk_frames)
		xsk_tx_completed(xdp_ring->xsk_pool, xsk_frames);
पूर्ण
