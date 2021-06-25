<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/* Copyright(c) 2018 Intel Corporation. */

#अगर_अघोषित I40E_TXRX_COMMON_
#घोषणा I40E_TXRX_COMMON_

पूर्णांक i40e_xmit_xdp_tx_ring(काष्ठा xdp_buff *xdp, काष्ठा i40e_ring *xdp_ring);
व्योम i40e_clean_programming_status(काष्ठा i40e_ring *rx_ring, u64 qword0_raw,
				   u64 qword1);
व्योम i40e_process_skb_fields(काष्ठा i40e_ring *rx_ring,
			     जोड़ i40e_rx_desc *rx_desc, काष्ठा sk_buff *skb);
व्योम i40e_xdp_ring_update_tail(काष्ठा i40e_ring *xdp_ring);
व्योम i40e_update_rx_stats(काष्ठा i40e_ring *rx_ring,
			  अचिन्हित पूर्णांक total_rx_bytes,
			  अचिन्हित पूर्णांक total_rx_packets);
व्योम i40e_finalize_xdp_rx(काष्ठा i40e_ring *rx_ring, अचिन्हित पूर्णांक xdp_res);
व्योम i40e_release_rx_desc(काष्ठा i40e_ring *rx_ring, u32 val);

#घोषणा I40E_XDP_PASS		0
#घोषणा I40E_XDP_CONSUMED	BIT(0)
#घोषणा I40E_XDP_TX		BIT(1)
#घोषणा I40E_XDP_REसूची		BIT(2)

/*
 * build_ctob - Builds the Tx descriptor (cmd, offset and type) qword
 */
अटल अंतरभूत __le64 build_ctob(u32 td_cmd, u32 td_offset, अचिन्हित पूर्णांक size,
				u32 td_tag)
अणु
	वापस cpu_to_le64(I40E_TX_DESC_DTYPE_DATA |
			   ((u64)td_cmd  << I40E_TXD_QW1_CMD_SHIFT) |
			   ((u64)td_offset << I40E_TXD_QW1_OFFSET_SHIFT) |
			   ((u64)size  << I40E_TXD_QW1_TX_BUF_SZ_SHIFT) |
			   ((u64)td_tag  << I40E_TXD_QW1_L2TAG1_SHIFT));
पूर्ण

/**
 * i40e_update_tx_stats - Update the egress statistics क्रम the Tx ring
 * @tx_ring: Tx ring to update
 * @total_packets: total packets sent
 * @total_bytes: total bytes sent
 **/
अटल अंतरभूत व्योम i40e_update_tx_stats(काष्ठा i40e_ring *tx_ring,
					अचिन्हित पूर्णांक total_packets,
					अचिन्हित पूर्णांक total_bytes)
अणु
	u64_stats_update_begin(&tx_ring->syncp);
	tx_ring->stats.bytes += total_bytes;
	tx_ring->stats.packets += total_packets;
	u64_stats_update_end(&tx_ring->syncp);
	tx_ring->q_vector->tx.total_bytes += total_bytes;
	tx_ring->q_vector->tx.total_packets += total_packets;
पूर्ण

#घोषणा WB_STRIDE 4

/**
 * i40e_arm_wb - (Possibly) arms Tx ग_लिखो-back
 * @tx_ring: Tx ring to update
 * @vsi: the VSI
 * @budget: the NAPI budget left
 **/
अटल अंतरभूत व्योम i40e_arm_wb(काष्ठा i40e_ring *tx_ring,
			       काष्ठा i40e_vsi *vsi,
			       पूर्णांक budget)
अणु
	अगर (tx_ring->flags & I40E_TXR_FLAGS_WB_ON_ITR) अणु
		/* check to see अगर there are < 4 descriptors
		 * रुकोing to be written back, then kick the hardware to क्रमce
		 * them to be written back in हाल we stay in NAPI.
		 * In this mode on X722 we करो not enable Interrupt.
		 */
		अचिन्हित पूर्णांक j = i40e_get_tx_pending(tx_ring, false);

		अगर (budget &&
		    ((j / WB_STRIDE) == 0) && j > 0 &&
		    !test_bit(__I40E_VSI_DOWN, vsi->state) &&
		    (I40E_DESC_UNUSED(tx_ring) != tx_ring->count))
			tx_ring->arm_wb = true;
	पूर्ण
पूर्ण

/**
 * i40e_rx_is_programming_status - check क्रम programming status descriptor
 * @qword1: qword1 representing status_error_len in CPU ordering
 *
 * The value of in the descriptor length field indicate अगर this
 * is a programming status descriptor क्रम flow director or FCoE
 * by the value of I40E_RX_PROG_STATUS_DESC_LENGTH, otherwise
 * it is a packet descriptor.
 **/
अटल अंतरभूत bool i40e_rx_is_programming_status(u64 qword1)
अणु
	/* The Rx filter programming status and SPH bit occupy the same
	 * spot in the descriptor. Since we करोn't support packet split we
	 * can just reuse the bit as an indication that this is a
	 * programming status descriptor.
	 */
	वापस qword1 & I40E_RXD_QW1_LENGTH_SPH_MASK;
पूर्ण

व्योम i40e_xsk_clean_rx_ring(काष्ठा i40e_ring *rx_ring);
व्योम i40e_xsk_clean_tx_ring(काष्ठा i40e_ring *tx_ring);
bool i40e_xsk_any_rx_ring_enabled(काष्ठा i40e_vsi *vsi);

#पूर्ण_अगर /* I40E_TXRX_COMMON_ */
