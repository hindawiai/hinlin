<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2019, Intel Corporation. */

#समावेश "ice_txrx_lib.h"

/**
 * ice_release_rx_desc - Store the new tail and head values
 * @rx_ring: ring to bump
 * @val: new head index
 */
व्योम ice_release_rx_desc(काष्ठा ice_ring *rx_ring, u16 val)
अणु
	u16 prev_ntu = rx_ring->next_to_use & ~0x7;

	rx_ring->next_to_use = val;

	/* update next to alloc since we have filled the ring */
	rx_ring->next_to_alloc = val;

	/* QRX_TAIL will be updated with any tail value, but hardware ignores
	 * the lower 3 bits. This makes it so we only bump tail on meaningful
	 * boundaries. Also, this allows us to bump tail on पूर्णांकervals of 8 up to
	 * the budget depending on the current traffic load.
	 */
	val &= ~0x7;
	अगर (prev_ntu != val) अणु
		/* Force memory ग_लिखोs to complete beक्रमe letting h/w
		 * know there are new descriptors to fetch. (Only
		 * applicable क्रम weak-ordered memory model archs,
		 * such as IA-64).
		 */
		wmb();
		ग_लिखोl(val, rx_ring->tail);
	पूर्ण
पूर्ण

/**
 * ice_ptype_to_htype - get a hash type
 * @ptype: the ptype value from the descriptor
 *
 * Returns a hash type to be used by skb_set_hash
 */
अटल क्रमागत pkt_hash_types ice_ptype_to_htype(u8 __always_unused ptype)
अणु
	वापस PKT_HASH_TYPE_NONE;
पूर्ण

/**
 * ice_rx_hash - set the hash value in the skb
 * @rx_ring: descriptor ring
 * @rx_desc: specअगरic descriptor
 * @skb: poपूर्णांकer to current skb
 * @rx_ptype: the ptype value from the descriptor
 */
अटल व्योम
ice_rx_hash(काष्ठा ice_ring *rx_ring, जोड़ ice_32b_rx_flex_desc *rx_desc,
	    काष्ठा sk_buff *skb, u8 rx_ptype)
अणु
	काष्ठा ice_32b_rx_flex_desc_nic *nic_mdid;
	u32 hash;

	अगर (!(rx_ring->netdev->features & NETIF_F_RXHASH))
		वापस;

	अगर (rx_desc->wb.rxdid != ICE_RXDID_FLEX_NIC)
		वापस;

	nic_mdid = (काष्ठा ice_32b_rx_flex_desc_nic *)rx_desc;
	hash = le32_to_cpu(nic_mdid->rss_hash);
	skb_set_hash(skb, hash, ice_ptype_to_htype(rx_ptype));
पूर्ण

/**
 * ice_rx_csum - Indicate in skb अगर checksum is good
 * @ring: the ring we care about
 * @skb: skb currently being received and modअगरied
 * @rx_desc: the receive descriptor
 * @ptype: the packet type decoded by hardware
 *
 * skb->protocol must be set beक्रमe this function is called
 */
अटल व्योम
ice_rx_csum(काष्ठा ice_ring *ring, काष्ठा sk_buff *skb,
	    जोड़ ice_32b_rx_flex_desc *rx_desc, u8 ptype)
अणु
	काष्ठा ice_rx_ptype_decoded decoded;
	u16 rx_status0, rx_status1;
	bool ipv4, ipv6;

	rx_status0 = le16_to_cpu(rx_desc->wb.status_error0);
	rx_status1 = le16_to_cpu(rx_desc->wb.status_error1);

	decoded = ice_decode_rx_desc_ptype(ptype);

	/* Start with CHECKSUM_NONE and by शेष csum_level = 0 */
	skb->ip_summed = CHECKSUM_NONE;
	skb_checksum_none_निश्चित(skb);

	/* check अगर Rx checksum is enabled */
	अगर (!(ring->netdev->features & NETIF_F_RXCSUM))
		वापस;

	/* check अगर HW has decoded the packet and checksum */
	अगर (!(rx_status0 & BIT(ICE_RX_FLEX_DESC_STATUS0_L3L4P_S)))
		वापस;

	अगर (!(decoded.known && decoded.outer_ip))
		वापस;

	ipv4 = (decoded.outer_ip == ICE_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == ICE_RX_PTYPE_OUTER_IPV4);
	ipv6 = (decoded.outer_ip == ICE_RX_PTYPE_OUTER_IP) &&
	       (decoded.outer_ip_ver == ICE_RX_PTYPE_OUTER_IPV6);

	अगर (ipv4 && (rx_status0 & (BIT(ICE_RX_FLEX_DESC_STATUS0_XSUM_IPE_S) |
				   BIT(ICE_RX_FLEX_DESC_STATUS0_XSUM_EIPE_S))))
		जाओ checksum_fail;

	अगर (ipv6 && (rx_status0 & (BIT(ICE_RX_FLEX_DESC_STATUS0_IPV6EXADD_S))))
		जाओ checksum_fail;

	/* check क्रम L4 errors and handle packets that were not able to be
	 * checksummed due to arrival speed
	 */
	अगर (rx_status0 & BIT(ICE_RX_FLEX_DESC_STATUS0_XSUM_L4E_S))
		जाओ checksum_fail;

	/* check क्रम outer UDP checksum error in tunneled packets */
	अगर ((rx_status1 & BIT(ICE_RX_FLEX_DESC_STATUS1_NAT_S)) &&
	    (rx_status0 & BIT(ICE_RX_FLEX_DESC_STATUS0_XSUM_EUDPE_S)))
		जाओ checksum_fail;

	/* If there is an outer header present that might contain a checksum
	 * we need to bump the checksum level by 1 to reflect the fact that
	 * we are indicating we validated the inner checksum.
	 */
	अगर (decoded.tunnel_type >= ICE_RX_PTYPE_TUNNEL_IP_GRENAT)
		skb->csum_level = 1;

	/* Only report checksum unnecessary क्रम TCP, UDP, or SCTP */
	चयन (decoded.inner_prot) अणु
	हाल ICE_RX_PTYPE_INNER_PROT_TCP:
	हाल ICE_RX_PTYPE_INNER_PROT_UDP:
	हाल ICE_RX_PTYPE_INNER_PROT_SCTP:
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस;

checksum_fail:
	ring->vsi->back->hw_csum_rx_error++;
पूर्ण

/**
 * ice_process_skb_fields - Populate skb header fields from Rx descriptor
 * @rx_ring: Rx descriptor ring packet is being transacted on
 * @rx_desc: poपूर्णांकer to the EOP Rx descriptor
 * @skb: poपूर्णांकer to current skb being populated
 * @ptype: the packet type decoded by hardware
 *
 * This function checks the ring, descriptor, and packet inक्रमmation in
 * order to populate the hash, checksum, VLAN, protocol, and
 * other fields within the skb.
 */
व्योम
ice_process_skb_fields(काष्ठा ice_ring *rx_ring,
		       जोड़ ice_32b_rx_flex_desc *rx_desc,
		       काष्ठा sk_buff *skb, u8 ptype)
अणु
	ice_rx_hash(rx_ring, rx_desc, skb, ptype);

	/* modअगरies the skb - consumes the enet header */
	skb->protocol = eth_type_trans(skb, rx_ring->netdev);

	ice_rx_csum(rx_ring, skb, rx_desc, ptype);
पूर्ण

/**
 * ice_receive_skb - Send a completed packet up the stack
 * @rx_ring: Rx ring in play
 * @skb: packet to send up
 * @vlan_tag: VLAN tag क्रम packet
 *
 * This function sends the completed packet (via. skb) up the stack using
 * gro receive functions (with/without VLAN tag)
 */
व्योम
ice_receive_skb(काष्ठा ice_ring *rx_ring, काष्ठा sk_buff *skb, u16 vlan_tag)
अणु
	अगर ((rx_ring->netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
	    (vlan_tag & VLAN_VID_MASK))
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);
	napi_gro_receive(&rx_ring->q_vector->napi, skb);
पूर्ण

/**
 * ice_xmit_xdp_ring - submit single packet to XDP ring क्रम transmission
 * @data: packet data poपूर्णांकer
 * @size: packet data size
 * @xdp_ring: XDP ring क्रम transmission
 */
पूर्णांक ice_xmit_xdp_ring(व्योम *data, u16 size, काष्ठा ice_ring *xdp_ring)
अणु
	u16 i = xdp_ring->next_to_use;
	काष्ठा ice_tx_desc *tx_desc;
	काष्ठा ice_tx_buf *tx_buf;
	dma_addr_t dma;

	अगर (!unlikely(ICE_DESC_UNUSED(xdp_ring))) अणु
		xdp_ring->tx_stats.tx_busy++;
		वापस ICE_XDP_CONSUMED;
	पूर्ण

	dma = dma_map_single(xdp_ring->dev, data, size, DMA_TO_DEVICE);
	अगर (dma_mapping_error(xdp_ring->dev, dma))
		वापस ICE_XDP_CONSUMED;

	tx_buf = &xdp_ring->tx_buf[i];
	tx_buf->bytecount = size;
	tx_buf->gso_segs = 1;
	tx_buf->raw_buf = data;

	/* record length, and DMA address */
	dma_unmap_len_set(tx_buf, len, size);
	dma_unmap_addr_set(tx_buf, dma, dma);

	tx_desc = ICE_TX_DESC(xdp_ring, i);
	tx_desc->buf_addr = cpu_to_le64(dma);
	tx_desc->cmd_type_offset_bsz = ice_build_ctob(ICE_TXD_LAST_DESC_CMD, 0,
						      size, 0);

	/* Make certain all of the status bits have been updated
	 * beक्रमe next_to_watch is written.
	 */
	smp_wmb();

	i++;
	अगर (i == xdp_ring->count)
		i = 0;

	tx_buf->next_to_watch = tx_desc;
	xdp_ring->next_to_use = i;

	वापस ICE_XDP_TX;
पूर्ण

/**
 * ice_xmit_xdp_buff - convert an XDP buffer to an XDP frame and send it
 * @xdp: XDP buffer
 * @xdp_ring: XDP Tx ring
 *
 * Returns negative on failure, 0 on success.
 */
पूर्णांक ice_xmit_xdp_buff(काष्ठा xdp_buff *xdp, काष्ठा ice_ring *xdp_ring)
अणु
	काष्ठा xdp_frame *xdpf = xdp_convert_buff_to_frame(xdp);

	अगर (unlikely(!xdpf))
		वापस ICE_XDP_CONSUMED;

	वापस ice_xmit_xdp_ring(xdpf->data, xdpf->len, xdp_ring);
पूर्ण

/**
 * ice_finalize_xdp_rx - Bump XDP Tx tail and/or flush redirect map
 * @rx_ring: Rx ring
 * @xdp_res: Result of the receive batch
 *
 * This function bumps XDP Tx tail and/or flush redirect map, and
 * should be called when a batch of packets has been processed in the
 * napi loop.
 */
व्योम ice_finalize_xdp_rx(काष्ठा ice_ring *rx_ring, अचिन्हित पूर्णांक xdp_res)
अणु
	अगर (xdp_res & ICE_XDP_REसूची)
		xdp_करो_flush_map();

	अगर (xdp_res & ICE_XDP_TX) अणु
		काष्ठा ice_ring *xdp_ring =
			rx_ring->vsi->xdp_rings[rx_ring->q_index];

		ice_xdp_ring_update_tail(xdp_ring);
	पूर्ण
पूर्ण
