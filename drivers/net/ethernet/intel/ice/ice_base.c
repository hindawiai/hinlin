<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Intel Corporation. */

#समावेश <net/xdp_sock_drv.h>
#समावेश "ice_base.h"
#समावेश "ice_lib.h"
#समावेश "ice_dcb_lib.h"

/**
 * __ice_vsi_get_qs_contig - Assign a contiguous chunk of queues to VSI
 * @qs_cfg: gathered variables needed क्रम PF->VSI queues assignment
 *
 * Return 0 on success and -ENOMEM in हाल of no left space in PF queue biपंचांगap
 */
अटल पूर्णांक __ice_vsi_get_qs_contig(काष्ठा ice_qs_cfg *qs_cfg)
अणु
	अचिन्हित पूर्णांक offset, i;

	mutex_lock(qs_cfg->qs_mutex);
	offset = biपंचांगap_find_next_zero_area(qs_cfg->pf_map, qs_cfg->pf_map_size,
					    0, qs_cfg->q_count, 0);
	अगर (offset >= qs_cfg->pf_map_size) अणु
		mutex_unlock(qs_cfg->qs_mutex);
		वापस -ENOMEM;
	पूर्ण

	biपंचांगap_set(qs_cfg->pf_map, offset, qs_cfg->q_count);
	क्रम (i = 0; i < qs_cfg->q_count; i++)
		qs_cfg->vsi_map[i + qs_cfg->vsi_map_offset] = (u16)(i + offset);
	mutex_unlock(qs_cfg->qs_mutex);

	वापस 0;
पूर्ण

/**
 * __ice_vsi_get_qs_sc - Assign a scattered queues from PF to VSI
 * @qs_cfg: gathered variables needed क्रम pf->vsi queues assignment
 *
 * Return 0 on success and -ENOMEM in हाल of no left space in PF queue biपंचांगap
 */
अटल पूर्णांक __ice_vsi_get_qs_sc(काष्ठा ice_qs_cfg *qs_cfg)
अणु
	अचिन्हित पूर्णांक i, index = 0;

	mutex_lock(qs_cfg->qs_mutex);
	क्रम (i = 0; i < qs_cfg->q_count; i++) अणु
		index = find_next_zero_bit(qs_cfg->pf_map,
					   qs_cfg->pf_map_size, index);
		अगर (index >= qs_cfg->pf_map_size)
			जाओ err_scatter;
		set_bit(index, qs_cfg->pf_map);
		qs_cfg->vsi_map[i + qs_cfg->vsi_map_offset] = (u16)index;
	पूर्ण
	mutex_unlock(qs_cfg->qs_mutex);

	वापस 0;
err_scatter:
	क्रम (index = 0; index < i; index++) अणु
		clear_bit(qs_cfg->vsi_map[index], qs_cfg->pf_map);
		qs_cfg->vsi_map[index + qs_cfg->vsi_map_offset] = 0;
	पूर्ण
	mutex_unlock(qs_cfg->qs_mutex);

	वापस -ENOMEM;
पूर्ण

/**
 * ice_pf_rxq_रुको - Wait क्रम a PF's Rx queue to be enabled or disabled
 * @pf: the PF being configured
 * @pf_q: the PF queue
 * @ena: enable or disable state of the queue
 *
 * This routine will रुको क्रम the given Rx queue of the PF to reach the
 * enabled or disabled state.
 * Returns -ETIMEDOUT in हाल of failing to reach the requested state after
 * multiple retries; अन्यथा will वापस 0 in हाल of success.
 */
अटल पूर्णांक ice_pf_rxq_रुको(काष्ठा ice_pf *pf, पूर्णांक pf_q, bool ena)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ICE_Q_WAIT_MAX_RETRY; i++) अणु
		अगर (ena == !!(rd32(&pf->hw, QRX_CTRL(pf_q)) &
			      QRX_CTRL_QENA_STAT_M))
			वापस 0;

		usleep_range(20, 40);
	पूर्ण

	वापस -ETIMEDOUT;
पूर्ण

/**
 * ice_vsi_alloc_q_vector - Allocate memory क्रम a single पूर्णांकerrupt vector
 * @vsi: the VSI being configured
 * @v_idx: index of the vector in the VSI काष्ठा
 *
 * We allocate one q_vector and set शेष value क्रम ITR setting associated
 * with this q_vector. If allocation fails we वापस -ENOMEM.
 */
अटल पूर्णांक ice_vsi_alloc_q_vector(काष्ठा ice_vsi *vsi, u16 v_idx)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_q_vector *q_vector;

	/* allocate q_vector */
	q_vector = devm_kzalloc(ice_pf_to_dev(pf), माप(*q_vector),
				GFP_KERNEL);
	अगर (!q_vector)
		वापस -ENOMEM;

	q_vector->vsi = vsi;
	q_vector->v_idx = v_idx;
	q_vector->tx.itr_setting = ICE_DFLT_TX_ITR;
	q_vector->rx.itr_setting = ICE_DFLT_RX_ITR;
	q_vector->tx.itr_mode = ITR_DYNAMIC;
	q_vector->rx.itr_mode = ITR_DYNAMIC;

	अगर (vsi->type == ICE_VSI_VF)
		जाओ out;
	/* only set affinity_mask अगर the CPU is online */
	अगर (cpu_online(v_idx))
		cpumask_set_cpu(v_idx, &q_vector->affinity_mask);

	/* This will not be called in the driver load path because the netdev
	 * will not be created yet. All other हालs with रेजिस्टर the NAPI
	 * handler here (i.e. resume, reset/rebuild, etc.)
	 */
	अगर (vsi->netdev)
		netअगर_napi_add(vsi->netdev, &q_vector->napi, ice_napi_poll,
			       NAPI_POLL_WEIGHT);

out:
	/* tie q_vector and VSI together */
	vsi->q_vectors[v_idx] = q_vector;

	वापस 0;
पूर्ण

/**
 * ice_मुक्त_q_vector - Free memory allocated क्रम a specअगरic पूर्णांकerrupt vector
 * @vsi: VSI having the memory मुक्तd
 * @v_idx: index of the vector to be मुक्तd
 */
अटल व्योम ice_मुक्त_q_vector(काष्ठा ice_vsi *vsi, पूर्णांक v_idx)
अणु
	काष्ठा ice_q_vector *q_vector;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_ring *ring;
	काष्ठा device *dev;

	dev = ice_pf_to_dev(pf);
	अगर (!vsi->q_vectors[v_idx]) अणु
		dev_dbg(dev, "Queue vector at index %d not found\n", v_idx);
		वापस;
	पूर्ण
	q_vector = vsi->q_vectors[v_idx];

	ice_क्रम_each_ring(ring, q_vector->tx)
		ring->q_vector = शून्य;
	ice_क्रम_each_ring(ring, q_vector->rx)
		ring->q_vector = शून्य;

	/* only VSI with an associated netdev is set up with NAPI */
	अगर (vsi->netdev)
		netअगर_napi_del(&q_vector->napi);

	devm_kमुक्त(dev, q_vector);
	vsi->q_vectors[v_idx] = शून्य;
पूर्ण

/**
 * ice_cfg_itr_gran - set the ITR granularity to 2 usecs अगर not alपढ़ोy set
 * @hw: board specअगरic काष्ठाure
 */
अटल व्योम ice_cfg_itr_gran(काष्ठा ice_hw *hw)
अणु
	u32 regval = rd32(hw, GLINT_CTL);

	/* no need to update global रेजिस्टर अगर ITR gran is alपढ़ोy set */
	अगर (!(regval & GLINT_CTL_DIS_AUTOMASK_M) &&
	    (((regval & GLINT_CTL_ITR_GRAN_200_M) >>
	     GLINT_CTL_ITR_GRAN_200_S) == ICE_ITR_GRAN_US) &&
	    (((regval & GLINT_CTL_ITR_GRAN_100_M) >>
	     GLINT_CTL_ITR_GRAN_100_S) == ICE_ITR_GRAN_US) &&
	    (((regval & GLINT_CTL_ITR_GRAN_50_M) >>
	     GLINT_CTL_ITR_GRAN_50_S) == ICE_ITR_GRAN_US) &&
	    (((regval & GLINT_CTL_ITR_GRAN_25_M) >>
	      GLINT_CTL_ITR_GRAN_25_S) == ICE_ITR_GRAN_US))
		वापस;

	regval = ((ICE_ITR_GRAN_US << GLINT_CTL_ITR_GRAN_200_S) &
		  GLINT_CTL_ITR_GRAN_200_M) |
		 ((ICE_ITR_GRAN_US << GLINT_CTL_ITR_GRAN_100_S) &
		  GLINT_CTL_ITR_GRAN_100_M) |
		 ((ICE_ITR_GRAN_US << GLINT_CTL_ITR_GRAN_50_S) &
		  GLINT_CTL_ITR_GRAN_50_M) |
		 ((ICE_ITR_GRAN_US << GLINT_CTL_ITR_GRAN_25_S) &
		  GLINT_CTL_ITR_GRAN_25_M);
	wr32(hw, GLINT_CTL, regval);
पूर्ण

/**
 * ice_calc_q_handle - calculate the queue handle
 * @vsi: VSI that ring beदीर्घs to
 * @ring: ring to get the असलolute queue index
 * @tc: traffic class number
 */
अटल u16 ice_calc_q_handle(काष्ठा ice_vsi *vsi, काष्ठा ice_ring *ring, u8 tc)
अणु
	WARN_ONCE(ice_ring_is_xdp(ring) && tc, "XDP ring can't belong to TC other than 0\n");

	/* Idea here क्रम calculation is that we subtract the number of queue
	 * count from TC that ring beदीर्घs to from it's असलolute queue index
	 * and as a result we get the queue's index within TC.
	 */
	वापस ring->q_index - vsi->tc_cfg.tc_info[tc].qoffset;
पूर्ण

/**
 * ice_cfg_xps_tx_ring - Configure XPS क्रम a Tx ring
 * @ring: The Tx ring to configure
 *
 * This enables/disables XPS क्रम a given Tx descriptor ring
 * based on the TCs enabled क्रम the VSI that ring beदीर्घs to.
 */
अटल व्योम ice_cfg_xps_tx_ring(काष्ठा ice_ring *ring)
अणु
	अगर (!ring->q_vector || !ring->netdev)
		वापस;

	/* We only initialize XPS once, so as not to overग_लिखो user settings */
	अगर (test_and_set_bit(ICE_TX_XPS_INIT_DONE, ring->xps_state))
		वापस;

	netअगर_set_xps_queue(ring->netdev, &ring->q_vector->affinity_mask,
			    ring->q_index);
पूर्ण

/**
 * ice_setup_tx_ctx - setup a काष्ठा ice_tlan_ctx instance
 * @ring: The Tx ring to configure
 * @tlan_ctx: Poपूर्णांकer to the Tx LAN queue context काष्ठाure to be initialized
 * @pf_q: queue index in the PF space
 *
 * Configure the Tx descriptor ring in TLAN context.
 */
अटल व्योम
ice_setup_tx_ctx(काष्ठा ice_ring *ring, काष्ठा ice_tlan_ctx *tlan_ctx, u16 pf_q)
अणु
	काष्ठा ice_vsi *vsi = ring->vsi;
	काष्ठा ice_hw *hw = &vsi->back->hw;

	tlan_ctx->base = ring->dma >> ICE_TLAN_CTX_BASE_S;

	tlan_ctx->port_num = vsi->port_info->lport;

	/* Transmit Queue Length */
	tlan_ctx->qlen = ring->count;

	ice_set_cgd_num(tlan_ctx, ring);

	/* PF number */
	tlan_ctx->pf_num = hw->pf_id;

	/* queue beदीर्घs to a specअगरic VSI type
	 * VF / VM index should be programmed per vmvf_type setting:
	 * क्रम vmvf_type = VF, it is VF number between 0-256
	 * क्रम vmvf_type = VM, it is VM number between 0-767
	 * क्रम PF or EMP this field should be set to zero
	 */
	चयन (vsi->type) अणु
	हाल ICE_VSI_LB:
	हाल ICE_VSI_CTRL:
	हाल ICE_VSI_PF:
		tlan_ctx->vmvf_type = ICE_TLAN_CTX_VMVF_TYPE_PF;
		अवरोध;
	हाल ICE_VSI_VF:
		/* Firmware expects vmvf_num to be असलolute VF ID */
		tlan_ctx->vmvf_num = hw->func_caps.vf_base_id + vsi->vf_id;
		tlan_ctx->vmvf_type = ICE_TLAN_CTX_VMVF_TYPE_VF;
		अवरोध;
	शेष:
		वापस;
	पूर्ण

	/* make sure the context is associated with the right VSI */
	tlan_ctx->src_vsi = ice_get_hw_vsi_num(hw, vsi->idx);

	tlan_ctx->tso_ena = ICE_TX_LEGACY;
	tlan_ctx->tso_qnum = pf_q;

	/* Legacy or Advanced Host Interface:
	 * 0: Advanced Host Interface
	 * 1: Legacy Host Interface
	 */
	tlan_ctx->legacy_पूर्णांक = ICE_TX_LEGACY;
पूर्ण

/**
 * ice_rx_offset - Return expected offset पूर्णांकo page to access data
 * @rx_ring: Ring we are requesting offset of
 *
 * Returns the offset value क्रम ring पूर्णांकo the data buffer.
 */
अटल अचिन्हित पूर्णांक ice_rx_offset(काष्ठा ice_ring *rx_ring)
अणु
	अगर (ice_ring_uses_build_skb(rx_ring))
		वापस ICE_SKB_PAD;
	अन्यथा अगर (ice_is_xdp_ena_vsi(rx_ring->vsi))
		वापस XDP_PACKET_HEADROOM;

	वापस 0;
पूर्ण

/**
 * ice_setup_rx_ctx - Configure a receive ring context
 * @ring: The Rx ring to configure
 *
 * Configure the Rx descriptor ring in RLAN context.
 */
पूर्णांक ice_setup_rx_ctx(काष्ठा ice_ring *ring)
अणु
	काष्ठा device *dev = ice_pf_to_dev(ring->vsi->back);
	पूर्णांक chain_len = ICE_MAX_CHAINED_RX_BUFS;
	u16 num_bufs = ICE_DESC_UNUSED(ring);
	काष्ठा ice_vsi *vsi = ring->vsi;
	u32 rxdid = ICE_RXDID_FLEX_NIC;
	काष्ठा ice_rlan_ctx rlan_ctx;
	काष्ठा ice_hw *hw;
	u16 pf_q;
	पूर्णांक err;

	hw = &vsi->back->hw;

	/* what is Rx queue number in global space of 2K Rx queues */
	pf_q = vsi->rxq_map[ring->q_index];

	/* clear the context काष्ठाure first */
	स_रखो(&rlan_ctx, 0, माप(rlan_ctx));

	ring->rx_buf_len = vsi->rx_buf_len;

	अगर (ring->vsi->type == ICE_VSI_PF) अणु
		अगर (!xdp_rxq_info_is_reg(&ring->xdp_rxq))
			/* coverity[check_वापस] */
			xdp_rxq_info_reg(&ring->xdp_rxq, ring->netdev,
					 ring->q_index, ring->q_vector->napi.napi_id);

		ring->xsk_pool = ice_xsk_pool(ring);
		अगर (ring->xsk_pool) अणु
			xdp_rxq_info_unreg_mem_model(&ring->xdp_rxq);

			ring->rx_buf_len =
				xsk_pool_get_rx_frame_size(ring->xsk_pool);
			/* For AF_XDP ZC, we disallow packets to span on
			 * multiple buffers, thus letting us skip that
			 * handling in the fast-path.
			 */
			chain_len = 1;
			err = xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
							 MEM_TYPE_XSK_BUFF_POOL,
							 शून्य);
			अगर (err)
				वापस err;
			xsk_pool_set_rxq_info(ring->xsk_pool, &ring->xdp_rxq);

			dev_info(dev, "Registered XDP mem model MEM_TYPE_XSK_BUFF_POOL on Rx ring %d\n",
				 ring->q_index);
		पूर्ण अन्यथा अणु
			अगर (!xdp_rxq_info_is_reg(&ring->xdp_rxq))
				/* coverity[check_वापस] */
				xdp_rxq_info_reg(&ring->xdp_rxq,
						 ring->netdev,
						 ring->q_index, ring->q_vector->napi.napi_id);

			err = xdp_rxq_info_reg_mem_model(&ring->xdp_rxq,
							 MEM_TYPE_PAGE_SHARED,
							 शून्य);
			अगर (err)
				वापस err;
		पूर्ण
	पूर्ण
	/* Receive Queue Base Address.
	 * Indicates the starting address of the descriptor queue defined in
	 * 128 Byte units.
	 */
	rlan_ctx.base = ring->dma >> 7;

	rlan_ctx.qlen = ring->count;

	/* Receive Packet Data Buffer Size.
	 * The Packet Data Buffer Size is defined in 128 byte units.
	 */
	rlan_ctx.dbuf = ring->rx_buf_len >> ICE_RLAN_CTX_DBUF_S;

	/* use 32 byte descriptors */
	rlan_ctx.dsize = 1;

	/* Strip the Ethernet CRC bytes beक्रमe the packet is posted to host
	 * memory.
	 */
	rlan_ctx.crcstrip = 1;

	/* L2TSEL flag defines the reported L2 Tags in the receive descriptor */
	rlan_ctx.l2tsel = 1;

	rlan_ctx.dtype = ICE_RX_DTYPE_NO_SPLIT;
	rlan_ctx.hsplit_0 = ICE_RLAN_RX_HSPLIT_0_NO_SPLIT;
	rlan_ctx.hsplit_1 = ICE_RLAN_RX_HSPLIT_1_NO_SPLIT;

	/* This controls whether VLAN is stripped from inner headers
	 * The VLAN in the inner L2 header is stripped to the receive
	 * descriptor अगर enabled by this flag.
	 */
	rlan_ctx.showiv = 0;

	/* Max packet size क्रम this queue - must not be set to a larger value
	 * than 5 x DBUF
	 */
	rlan_ctx.rxmax = min_t(u32, vsi->max_frame,
			       chain_len * ring->rx_buf_len);

	/* Rx queue threshold in units of 64 */
	rlan_ctx.lrxqthresh = 1;

	/* Enable Flexible Descriptors in the queue context which
	 * allows this driver to select a specअगरic receive descriptor क्रमmat
	 * increasing context priority to pick up profile ID; शेष is 0x01;
	 * setting to 0x03 to ensure profile is programming अगर prev context is
	 * of same priority
	 */
	अगर (vsi->type != ICE_VSI_VF)
		ice_ग_लिखो_qrxflxp_cntxt(hw, pf_q, rxdid, 0x3);
	अन्यथा
		ice_ग_लिखो_qrxflxp_cntxt(hw, pf_q, ICE_RXDID_LEGACY_1, 0x3);

	/* Absolute queue number out of 2K needs to be passed */
	err = ice_ग_लिखो_rxq_ctx(hw, &rlan_ctx, pf_q);
	अगर (err) अणु
		dev_err(dev, "Failed to set LAN Rx queue context for absolute Rx queue %d error: %d\n",
			pf_q, err);
		वापस -EIO;
	पूर्ण

	अगर (vsi->type == ICE_VSI_VF)
		वापस 0;

	/* configure Rx buffer alignment */
	अगर (!vsi->netdev || test_bit(ICE_FLAG_LEGACY_RX, vsi->back->flags))
		ice_clear_ring_build_skb_ena(ring);
	अन्यथा
		ice_set_ring_build_skb_ena(ring);

	ring->rx_offset = ice_rx_offset(ring);

	/* init queue specअगरic tail रेजिस्टर */
	ring->tail = hw->hw_addr + QRX_TAIL(pf_q);
	ग_लिखोl(0, ring->tail);

	अगर (ring->xsk_pool) अणु
		bool ok;

		अगर (!xsk_buff_can_alloc(ring->xsk_pool, num_bufs)) अणु
			dev_warn(dev, "XSK buffer pool does not provide enough addresses to fill %d buffers on Rx ring %d\n",
				 num_bufs, ring->q_index);
			dev_warn(dev, "Change Rx ring/fill queue size to avoid performance issues\n");

			वापस 0;
		पूर्ण

		ok = ice_alloc_rx_bufs_zc(ring, num_bufs);
		अगर (!ok)
			dev_info(dev, "Failed to allocate some buffers on XSK buffer pool enabled Rx ring %d (pf_q %d)\n",
				 ring->q_index, pf_q);
		वापस 0;
	पूर्ण

	ice_alloc_rx_bufs(ring, num_bufs);

	वापस 0;
पूर्ण

/**
 * __ice_vsi_get_qs - helper function क्रम assigning queues from PF to VSI
 * @qs_cfg: gathered variables needed क्रम pf->vsi queues assignment
 *
 * This function first tries to find contiguous space. If it is not successful,
 * it tries with the scatter approach.
 *
 * Return 0 on success and -ENOMEM in हाल of no left space in PF queue biपंचांगap
 */
पूर्णांक __ice_vsi_get_qs(काष्ठा ice_qs_cfg *qs_cfg)
अणु
	पूर्णांक ret = 0;

	ret = __ice_vsi_get_qs_contig(qs_cfg);
	अगर (ret) अणु
		/* contig failed, so try with scatter approach */
		qs_cfg->mapping_mode = ICE_VSI_MAP_SCATTER;
		qs_cfg->q_count = min_t(अचिन्हित पूर्णांक, qs_cfg->q_count,
					qs_cfg->scatter_count);
		ret = __ice_vsi_get_qs_sc(qs_cfg);
	पूर्ण
	वापस ret;
पूर्ण

/**
 * ice_vsi_ctrl_one_rx_ring - start/stop VSI's Rx ring with no busy रुको
 * @vsi: the VSI being configured
 * @ena: start or stop the Rx ring
 * @rxq_idx: 0-based Rx queue index क्रम the VSI passed in
 * @रुको: रुको or करोn't रुको क्रम configuration to finish in hardware
 *
 * Return 0 on success and negative on error.
 */
पूर्णांक
ice_vsi_ctrl_one_rx_ring(काष्ठा ice_vsi *vsi, bool ena, u16 rxq_idx, bool रुको)
अणु
	पूर्णांक pf_q = vsi->rxq_map[rxq_idx];
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	u32 rx_reg;

	rx_reg = rd32(hw, QRX_CTRL(pf_q));

	/* Skip अगर the queue is alपढ़ोy in the requested state */
	अगर (ena == !!(rx_reg & QRX_CTRL_QENA_STAT_M))
		वापस 0;

	/* turn on/off the queue */
	अगर (ena)
		rx_reg |= QRX_CTRL_QENA_REQ_M;
	अन्यथा
		rx_reg &= ~QRX_CTRL_QENA_REQ_M;
	wr32(hw, QRX_CTRL(pf_q), rx_reg);

	अगर (!रुको)
		वापस 0;

	ice_flush(hw);
	वापस ice_pf_rxq_रुको(pf, pf_q, ena);
पूर्ण

/**
 * ice_vsi_रुको_one_rx_ring - रुको क्रम a VSI's Rx ring to be stopped/started
 * @vsi: the VSI being configured
 * @ena: true/false to verअगरy Rx ring has been enabled/disabled respectively
 * @rxq_idx: 0-based Rx queue index क्रम the VSI passed in
 *
 * This routine will रुको क्रम the given Rx queue of the VSI to reach the
 * enabled or disabled state. Returns -ETIMEDOUT in हाल of failing to reach
 * the requested state after multiple retries; अन्यथा will वापस 0 in हाल of
 * success.
 */
पूर्णांक ice_vsi_रुको_one_rx_ring(काष्ठा ice_vsi *vsi, bool ena, u16 rxq_idx)
अणु
	पूर्णांक pf_q = vsi->rxq_map[rxq_idx];
	काष्ठा ice_pf *pf = vsi->back;

	वापस ice_pf_rxq_रुको(pf, pf_q, ena);
पूर्ण

/**
 * ice_vsi_alloc_q_vectors - Allocate memory क्रम पूर्णांकerrupt vectors
 * @vsi: the VSI being configured
 *
 * We allocate one q_vector per queue पूर्णांकerrupt. If allocation fails we
 * वापस -ENOMEM.
 */
पूर्णांक ice_vsi_alloc_q_vectors(काष्ठा ice_vsi *vsi)
अणु
	काष्ठा device *dev = ice_pf_to_dev(vsi->back);
	u16 v_idx;
	पूर्णांक err;

	अगर (vsi->q_vectors[0]) अणु
		dev_dbg(dev, "VSI %d has existing q_vectors\n", vsi->vsi_num);
		वापस -EEXIST;
	पूर्ण

	क्रम (v_idx = 0; v_idx < vsi->num_q_vectors; v_idx++) अणु
		err = ice_vsi_alloc_q_vector(vsi, v_idx);
		अगर (err)
			जाओ err_out;
	पूर्ण

	वापस 0;

err_out:
	जबतक (v_idx--)
		ice_मुक्त_q_vector(vsi, v_idx);

	dev_err(dev, "Failed to allocate %d q_vector for VSI %d, ret=%d\n",
		vsi->num_q_vectors, vsi->vsi_num, err);
	vsi->num_q_vectors = 0;
	वापस err;
पूर्ण

/**
 * ice_vsi_map_rings_to_vectors - Map VSI rings to पूर्णांकerrupt vectors
 * @vsi: the VSI being configured
 *
 * This function maps descriptor rings to the queue-specअगरic vectors allotted
 * through the MSI-X enabling code. On a स्थिरrained vector budget, we map Tx
 * and Rx rings to the vector as "efficiently" as possible.
 */
व्योम ice_vsi_map_rings_to_vectors(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक q_vectors = vsi->num_q_vectors;
	u16 tx_rings_rem, rx_rings_rem;
	पूर्णांक v_id;

	/* initially assigning reमुख्यing rings count to VSIs num queue value */
	tx_rings_rem = vsi->num_txq;
	rx_rings_rem = vsi->num_rxq;

	क्रम (v_id = 0; v_id < q_vectors; v_id++) अणु
		काष्ठा ice_q_vector *q_vector = vsi->q_vectors[v_id];
		u8 tx_rings_per_v, rx_rings_per_v;
		u16 q_id, q_base;

		/* Tx rings mapping to vector */
		tx_rings_per_v = (u8)DIV_ROUND_UP(tx_rings_rem,
						  q_vectors - v_id);
		q_vector->num_ring_tx = tx_rings_per_v;
		q_vector->tx.ring = शून्य;
		q_vector->tx.itr_idx = ICE_TX_ITR;
		q_base = vsi->num_txq - tx_rings_rem;

		क्रम (q_id = q_base; q_id < (q_base + tx_rings_per_v); q_id++) अणु
			काष्ठा ice_ring *tx_ring = vsi->tx_rings[q_id];

			tx_ring->q_vector = q_vector;
			tx_ring->next = q_vector->tx.ring;
			q_vector->tx.ring = tx_ring;
		पूर्ण
		tx_rings_rem -= tx_rings_per_v;

		/* Rx rings mapping to vector */
		rx_rings_per_v = (u8)DIV_ROUND_UP(rx_rings_rem,
						  q_vectors - v_id);
		q_vector->num_ring_rx = rx_rings_per_v;
		q_vector->rx.ring = शून्य;
		q_vector->rx.itr_idx = ICE_RX_ITR;
		q_base = vsi->num_rxq - rx_rings_rem;

		क्रम (q_id = q_base; q_id < (q_base + rx_rings_per_v); q_id++) अणु
			काष्ठा ice_ring *rx_ring = vsi->rx_rings[q_id];

			rx_ring->q_vector = q_vector;
			rx_ring->next = q_vector->rx.ring;
			q_vector->rx.ring = rx_ring;
		पूर्ण
		rx_rings_rem -= rx_rings_per_v;
	पूर्ण
पूर्ण

/**
 * ice_vsi_मुक्त_q_vectors - Free memory allocated क्रम पूर्णांकerrupt vectors
 * @vsi: the VSI having memory मुक्तd
 */
व्योम ice_vsi_मुक्त_q_vectors(काष्ठा ice_vsi *vsi)
अणु
	पूर्णांक v_idx;

	ice_क्रम_each_q_vector(vsi, v_idx)
		ice_मुक्त_q_vector(vsi, v_idx);
पूर्ण

/**
 * ice_vsi_cfg_txq - Configure single Tx queue
 * @vsi: the VSI that queue beदीर्घs to
 * @ring: Tx ring to be configured
 * @qg_buf: queue group buffer
 */
पूर्णांक
ice_vsi_cfg_txq(काष्ठा ice_vsi *vsi, काष्ठा ice_ring *ring,
		काष्ठा ice_aqc_add_tx_qgrp *qg_buf)
अणु
	u8 buf_len = काष्ठा_size(qg_buf, txqs, 1);
	काष्ठा ice_tlan_ctx tlan_ctx = अणु 0 पूर्ण;
	काष्ठा ice_aqc_add_txqs_perq *txq;
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u16 pf_q;
	u8 tc;

	/* Configure XPS */
	ice_cfg_xps_tx_ring(ring);

	pf_q = ring->reg_idx;
	ice_setup_tx_ctx(ring, &tlan_ctx, pf_q);
	/* copy context contents पूर्णांकo the qg_buf */
	qg_buf->txqs[0].txq_id = cpu_to_le16(pf_q);
	ice_set_ctx(hw, (u8 *)&tlan_ctx, qg_buf->txqs[0].txq_ctx,
		    ice_tlan_ctx_info);

	/* init queue specअगरic tail reg. It is referred as
	 * transmit comm scheduler queue करोorbell.
	 */
	ring->tail = hw->hw_addr + QTX_COMM_DBELL(pf_q);

	अगर (IS_ENABLED(CONFIG_DCB))
		tc = ring->dcb_tc;
	अन्यथा
		tc = 0;

	/* Add unique software queue handle of the Tx queue per
	 * TC पूर्णांकo the VSI Tx ring
	 */
	ring->q_handle = ice_calc_q_handle(vsi, ring, tc);

	status = ice_ena_vsi_txq(vsi->port_info, vsi->idx, tc, ring->q_handle,
				 1, qg_buf, buf_len, शून्य);
	अगर (status) अणु
		dev_err(ice_pf_to_dev(pf), "Failed to set LAN Tx queue context, error: %s\n",
			ice_stat_str(status));
		वापस -ENODEV;
	पूर्ण

	/* Add Tx Queue TEID पूर्णांकo the VSI Tx ring from the
	 * response. This will complete configuring and
	 * enabling the queue.
	 */
	txq = &qg_buf->txqs[0];
	अगर (pf_q == le16_to_cpu(txq->txq_id))
		ring->txq_teid = le32_to_cpu(txq->q_teid);

	वापस 0;
पूर्ण

/**
 * ice_cfg_itr - configure the initial पूर्णांकerrupt throttle values
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @q_vector: पूर्णांकerrupt vector that's being configured
 *
 * Configure पूर्णांकerrupt throttling values क्रम the ring containers that are
 * associated with the पूर्णांकerrupt vector passed in.
 */
व्योम ice_cfg_itr(काष्ठा ice_hw *hw, काष्ठा ice_q_vector *q_vector)
अणु
	ice_cfg_itr_gran(hw);

	अगर (q_vector->num_ring_rx)
		ice_ग_लिखो_itr(&q_vector->rx, q_vector->rx.itr_setting);

	अगर (q_vector->num_ring_tx)
		ice_ग_लिखो_itr(&q_vector->tx, q_vector->tx.itr_setting);

	ice_ग_लिखो_पूर्णांकrl(q_vector, q_vector->पूर्णांकrl);
पूर्ण

/**
 * ice_cfg_txq_पूर्णांकerrupt - configure पूर्णांकerrupt on Tx queue
 * @vsi: the VSI being configured
 * @txq: Tx queue being mapped to MSI-X vector
 * @msix_idx: MSI-X vector index within the function
 * @itr_idx: ITR index of the पूर्णांकerrupt cause
 *
 * Configure पूर्णांकerrupt on Tx queue by associating Tx queue to MSI-X vector
 * within the function space.
 */
व्योम
ice_cfg_txq_पूर्णांकerrupt(काष्ठा ice_vsi *vsi, u16 txq, u16 msix_idx, u16 itr_idx)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	u32 val;

	itr_idx = (itr_idx << QINT_TQCTL_ITR_INDX_S) & QINT_TQCTL_ITR_INDX_M;

	val = QINT_TQCTL_CAUSE_ENA_M | itr_idx |
	      ((msix_idx << QINT_TQCTL_MSIX_INDX_S) & QINT_TQCTL_MSIX_INDX_M);

	wr32(hw, QINT_TQCTL(vsi->txq_map[txq]), val);
	अगर (ice_is_xdp_ena_vsi(vsi)) अणु
		u32 xdp_txq = txq + vsi->num_xdp_txq;

		wr32(hw, QINT_TQCTL(vsi->txq_map[xdp_txq]),
		     val);
	पूर्ण
	ice_flush(hw);
पूर्ण

/**
 * ice_cfg_rxq_पूर्णांकerrupt - configure पूर्णांकerrupt on Rx queue
 * @vsi: the VSI being configured
 * @rxq: Rx queue being mapped to MSI-X vector
 * @msix_idx: MSI-X vector index within the function
 * @itr_idx: ITR index of the पूर्णांकerrupt cause
 *
 * Configure पूर्णांकerrupt on Rx queue by associating Rx queue to MSI-X vector
 * within the function space.
 */
व्योम
ice_cfg_rxq_पूर्णांकerrupt(काष्ठा ice_vsi *vsi, u16 rxq, u16 msix_idx, u16 itr_idx)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_hw *hw = &pf->hw;
	u32 val;

	itr_idx = (itr_idx << QINT_RQCTL_ITR_INDX_S) & QINT_RQCTL_ITR_INDX_M;

	val = QINT_RQCTL_CAUSE_ENA_M | itr_idx |
	      ((msix_idx << QINT_RQCTL_MSIX_INDX_S) & QINT_RQCTL_MSIX_INDX_M);

	wr32(hw, QINT_RQCTL(vsi->rxq_map[rxq]), val);

	ice_flush(hw);
पूर्ण

/**
 * ice_trigger_sw_पूर्णांकr - trigger a software पूर्णांकerrupt
 * @hw: poपूर्णांकer to the HW काष्ठाure
 * @q_vector: पूर्णांकerrupt vector to trigger the software पूर्णांकerrupt क्रम
 */
व्योम ice_trigger_sw_पूर्णांकr(काष्ठा ice_hw *hw, काष्ठा ice_q_vector *q_vector)
अणु
	wr32(hw, GLINT_DYN_CTL(q_vector->reg_idx),
	     (ICE_ITR_NONE << GLINT_DYN_CTL_ITR_INDX_S) |
	     GLINT_DYN_CTL_SWINT_TRIG_M |
	     GLINT_DYN_CTL_INTENA_M);
पूर्ण

/**
 * ice_vsi_stop_tx_ring - Disable single Tx ring
 * @vsi: the VSI being configured
 * @rst_src: reset source
 * @rel_vmvf_num: Relative ID of VF/VM
 * @ring: Tx ring to be stopped
 * @txq_meta: Meta data of Tx ring to be stopped
 */
पूर्णांक
ice_vsi_stop_tx_ring(काष्ठा ice_vsi *vsi, क्रमागत ice_disq_rst_src rst_src,
		     u16 rel_vmvf_num, काष्ठा ice_ring *ring,
		     काष्ठा ice_txq_meta *txq_meta)
अणु
	काष्ठा ice_pf *pf = vsi->back;
	काष्ठा ice_q_vector *q_vector;
	काष्ठा ice_hw *hw = &pf->hw;
	क्रमागत ice_status status;
	u32 val;

	/* clear cause_ena bit क्रम disabled queues */
	val = rd32(hw, QINT_TQCTL(ring->reg_idx));
	val &= ~QINT_TQCTL_CAUSE_ENA_M;
	wr32(hw, QINT_TQCTL(ring->reg_idx), val);

	/* software is expected to रुको क्रम 100 ns */
	ndelay(100);

	/* trigger a software पूर्णांकerrupt क्रम the vector
	 * associated to the queue to schedule NAPI handler
	 */
	q_vector = ring->q_vector;
	अगर (q_vector)
		ice_trigger_sw_पूर्णांकr(hw, q_vector);

	status = ice_dis_vsi_txq(vsi->port_info, txq_meta->vsi_idx,
				 txq_meta->tc, 1, &txq_meta->q_handle,
				 &txq_meta->q_id, &txq_meta->q_teid, rst_src,
				 rel_vmvf_num, शून्य);

	/* अगर the disable queue command was exercised during an
	 * active reset flow, ICE_ERR_RESET_ONGOING is वापसed.
	 * This is not an error as the reset operation disables
	 * queues at the hardware level anyway.
	 */
	अगर (status == ICE_ERR_RESET_ONGOING) अणु
		dev_dbg(ice_pf_to_dev(vsi->back), "Reset in progress. LAN Tx queues already disabled\n");
	पूर्ण अन्यथा अगर (status == ICE_ERR_DOES_NOT_EXIST) अणु
		dev_dbg(ice_pf_to_dev(vsi->back), "LAN Tx queues do not exist, nothing to disable\n");
	पूर्ण अन्यथा अगर (status) अणु
		dev_err(ice_pf_to_dev(vsi->back), "Failed to disable LAN Tx queues, error: %s\n",
			ice_stat_str(status));
		वापस -ENODEV;
	पूर्ण

	वापस 0;
पूर्ण

/**
 * ice_fill_txq_meta - Prepare the Tx queue's meta data
 * @vsi: VSI that ring beदीर्घs to
 * @ring: ring that txq_meta will be based on
 * @txq_meta: a helper काष्ठा that wraps Tx queue's inक्रमmation
 *
 * Set up a helper काष्ठा that will contain all the necessary fields that
 * are needed क्रम stopping Tx queue
 */
व्योम
ice_fill_txq_meta(काष्ठा ice_vsi *vsi, काष्ठा ice_ring *ring,
		  काष्ठा ice_txq_meta *txq_meta)
अणु
	u8 tc;

	अगर (IS_ENABLED(CONFIG_DCB))
		tc = ring->dcb_tc;
	अन्यथा
		tc = 0;

	txq_meta->q_id = ring->reg_idx;
	txq_meta->q_teid = ring->txq_teid;
	txq_meta->q_handle = ring->q_handle;
	txq_meta->vsi_idx = vsi->idx;
	txq_meta->tc = tc;
पूर्ण
