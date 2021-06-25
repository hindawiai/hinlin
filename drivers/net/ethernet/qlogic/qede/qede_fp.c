<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0-only OR BSD-3-Clause)
/* QLogic qede NIC Driver
 * Copyright (c) 2015-2017  QLogic Corporation
 * Copyright (c) 2019-2020 Marvell International Ltd.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/bpf_trace.h>
#समावेश <net/udp_tunnel.h>
#समावेश <linux/ip.h>
#समावेश <net/ipv6.h>
#समावेश <net/tcp.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ip6_checksum.h>
#समावेश "qede_ptp.h"

#समावेश <linux/qed/qed_अगर.h>
#समावेश "qede.h"
/*********************************
 * Content also used by slowpath *
 *********************************/

पूर्णांक qede_alloc_rx_buffer(काष्ठा qede_rx_queue *rxq, bool allow_lazy)
अणु
	काष्ठा sw_rx_data *sw_rx_data;
	काष्ठा eth_rx_bd *rx_bd;
	dma_addr_t mapping;
	काष्ठा page *data;

	/* In हाल lazy-allocation is allowed, postpone allocation until the
	 * end of the NAPI run. We'd still need to make sure the Rx ring has
	 * sufficient buffers to guarantee an additional Rx पूर्णांकerrupt.
	 */
	अगर (allow_lazy && likely(rxq->filled_buffers > 12)) अणु
		rxq->filled_buffers--;
		वापस 0;
	पूर्ण

	data = alloc_pages(GFP_ATOMIC, 0);
	अगर (unlikely(!data))
		वापस -ENOMEM;

	/* Map the entire page as it would be used
	 * क्रम multiple RX buffer segment size mapping.
	 */
	mapping = dma_map_page(rxq->dev, data, 0,
			       PAGE_SIZE, rxq->data_direction);
	अगर (unlikely(dma_mapping_error(rxq->dev, mapping))) अणु
		__मुक्त_page(data);
		वापस -ENOMEM;
	पूर्ण

	sw_rx_data = &rxq->sw_rx_ring[rxq->sw_rx_prod & NUM_RX_BDS_MAX];
	sw_rx_data->page_offset = 0;
	sw_rx_data->data = data;
	sw_rx_data->mapping = mapping;

	/* Advance PROD and get BD poपूर्णांकer */
	rx_bd = (काष्ठा eth_rx_bd *)qed_chain_produce(&rxq->rx_bd_ring);
	WARN_ON(!rx_bd);
	rx_bd->addr.hi = cpu_to_le32(upper_32_bits(mapping));
	rx_bd->addr.lo = cpu_to_le32(lower_32_bits(mapping) +
				     rxq->rx_headroom);

	rxq->sw_rx_prod++;
	rxq->filled_buffers++;

	वापस 0;
पूर्ण

/* Unmap the data and मुक्त skb */
पूर्णांक qede_मुक्त_tx_pkt(काष्ठा qede_dev *edev, काष्ठा qede_tx_queue *txq, पूर्णांक *len)
अणु
	u16 idx = txq->sw_tx_cons;
	काष्ठा sk_buff *skb = txq->sw_tx_ring.skbs[idx].skb;
	काष्ठा eth_tx_1st_bd *first_bd;
	काष्ठा eth_tx_bd *tx_data_bd;
	पूर्णांक bds_consumed = 0;
	पूर्णांक nbds;
	bool data_split = txq->sw_tx_ring.skbs[idx].flags & QEDE_TSO_SPLIT_BD;
	पूर्णांक i, split_bd_len = 0;

	अगर (unlikely(!skb)) अणु
		DP_ERR(edev,
		       "skb is null for txq idx=%d txq->sw_tx_cons=%d txq->sw_tx_prod=%d\n",
		       idx, txq->sw_tx_cons, txq->sw_tx_prod);
		वापस -1;
	पूर्ण

	*len = skb->len;

	first_bd = (काष्ठा eth_tx_1st_bd *)qed_chain_consume(&txq->tx_pbl);

	bds_consumed++;

	nbds = first_bd->data.nbds;

	अगर (data_split) अणु
		काष्ठा eth_tx_bd *split = (काष्ठा eth_tx_bd *)
			qed_chain_consume(&txq->tx_pbl);
		split_bd_len = BD_UNMAP_LEN(split);
		bds_consumed++;
	पूर्ण
	dma_unmap_single(&edev->pdev->dev, BD_UNMAP_ADDR(first_bd),
			 BD_UNMAP_LEN(first_bd) + split_bd_len, DMA_TO_DEVICE);

	/* Unmap the data of the skb frags */
	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++, bds_consumed++) अणु
		tx_data_bd = (काष्ठा eth_tx_bd *)
			qed_chain_consume(&txq->tx_pbl);
		dma_unmap_page(&edev->pdev->dev, BD_UNMAP_ADDR(tx_data_bd),
			       BD_UNMAP_LEN(tx_data_bd), DMA_TO_DEVICE);
	पूर्ण

	जबतक (bds_consumed++ < nbds)
		qed_chain_consume(&txq->tx_pbl);

	/* Free skb */
	dev_kमुक्त_skb_any(skb);
	txq->sw_tx_ring.skbs[idx].skb = शून्य;
	txq->sw_tx_ring.skbs[idx].flags = 0;

	वापस 0;
पूर्ण

/* Unmap the data and मुक्त skb when mapping failed during start_xmit */
अटल व्योम qede_मुक्त_failed_tx_pkt(काष्ठा qede_tx_queue *txq,
				    काष्ठा eth_tx_1st_bd *first_bd,
				    पूर्णांक nbd, bool data_split)
अणु
	u16 idx = txq->sw_tx_prod;
	काष्ठा sk_buff *skb = txq->sw_tx_ring.skbs[idx].skb;
	काष्ठा eth_tx_bd *tx_data_bd;
	पूर्णांक i, split_bd_len = 0;

	/* Return prod to its position beक्रमe this skb was handled */
	qed_chain_set_prod(&txq->tx_pbl,
			   le16_to_cpu(txq->tx_db.data.bd_prod), first_bd);

	first_bd = (काष्ठा eth_tx_1st_bd *)qed_chain_produce(&txq->tx_pbl);

	अगर (data_split) अणु
		काष्ठा eth_tx_bd *split = (काष्ठा eth_tx_bd *)
					  qed_chain_produce(&txq->tx_pbl);
		split_bd_len = BD_UNMAP_LEN(split);
		nbd--;
	पूर्ण

	dma_unmap_single(txq->dev, BD_UNMAP_ADDR(first_bd),
			 BD_UNMAP_LEN(first_bd) + split_bd_len, DMA_TO_DEVICE);

	/* Unmap the data of the skb frags */
	क्रम (i = 0; i < nbd; i++) अणु
		tx_data_bd = (काष्ठा eth_tx_bd *)
			qed_chain_produce(&txq->tx_pbl);
		अगर (tx_data_bd->nbytes)
			dma_unmap_page(txq->dev,
				       BD_UNMAP_ADDR(tx_data_bd),
				       BD_UNMAP_LEN(tx_data_bd), DMA_TO_DEVICE);
	पूर्ण

	/* Return again prod to its position beक्रमe this skb was handled */
	qed_chain_set_prod(&txq->tx_pbl,
			   le16_to_cpu(txq->tx_db.data.bd_prod), first_bd);

	/* Free skb */
	dev_kमुक्त_skb_any(skb);
	txq->sw_tx_ring.skbs[idx].skb = शून्य;
	txq->sw_tx_ring.skbs[idx].flags = 0;
पूर्ण

अटल u32 qede_xmit_type(काष्ठा sk_buff *skb, पूर्णांक *ipv6_ext)
अणु
	u32 rc = XMIT_L4_CSUM;
	__be16 l3_proto;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस XMIT_PLAIN;

	l3_proto = vlan_get_protocol(skb);
	अगर (l3_proto == htons(ETH_P_IPV6) &&
	    (ipv6_hdr(skb)->nexthdr == NEXTHDR_IPV6))
		*ipv6_ext = 1;

	अगर (skb->encapsulation) अणु
		rc |= XMIT_ENC;
		अगर (skb_is_gso(skb)) अणु
			अचिन्हित लघु gso_type = skb_shinfo(skb)->gso_type;

			अगर ((gso_type & SKB_GSO_UDP_TUNNEL_CSUM) ||
			    (gso_type & SKB_GSO_GRE_CSUM))
				rc |= XMIT_ENC_GSO_L4_CSUM;

			rc |= XMIT_LSO;
			वापस rc;
		पूर्ण
	पूर्ण

	अगर (skb_is_gso(skb))
		rc |= XMIT_LSO;

	वापस rc;
पूर्ण

अटल व्योम qede_set_params_क्रम_ipv6_ext(काष्ठा sk_buff *skb,
					 काष्ठा eth_tx_2nd_bd *second_bd,
					 काष्ठा eth_tx_3rd_bd *third_bd)
अणु
	u8 l4_proto;
	u16 bd2_bits1 = 0, bd2_bits2 = 0;

	bd2_bits1 |= (1 << ETH_TX_DATA_2ND_BD_IPV6_EXT_SHIFT);

	bd2_bits2 |= ((((u8 *)skb_transport_header(skb) - skb->data) >> 1) &
		     ETH_TX_DATA_2ND_BD_L4_HDR_START_OFFSET_W_MASK)
		    << ETH_TX_DATA_2ND_BD_L4_HDR_START_OFFSET_W_SHIFT;

	bd2_bits1 |= (ETH_L4_PSEUDO_CSUM_CORRECT_LENGTH <<
		      ETH_TX_DATA_2ND_BD_L4_PSEUDO_CSUM_MODE_SHIFT);

	अगर (vlan_get_protocol(skb) == htons(ETH_P_IPV6))
		l4_proto = ipv6_hdr(skb)->nexthdr;
	अन्यथा
		l4_proto = ip_hdr(skb)->protocol;

	अगर (l4_proto == IPPROTO_UDP)
		bd2_bits1 |= 1 << ETH_TX_DATA_2ND_BD_L4_UDP_SHIFT;

	अगर (third_bd)
		third_bd->data.bitfields |=
			cpu_to_le16(((tcp_hdrlen(skb) / 4) &
				ETH_TX_DATA_3RD_BD_TCP_HDR_LEN_DW_MASK) <<
				ETH_TX_DATA_3RD_BD_TCP_HDR_LEN_DW_SHIFT);

	second_bd->data.bitfields1 = cpu_to_le16(bd2_bits1);
	second_bd->data.bitfields2 = cpu_to_le16(bd2_bits2);
पूर्ण

अटल पूर्णांक map_frag_to_bd(काष्ठा qede_tx_queue *txq,
			  skb_frag_t *frag, काष्ठा eth_tx_bd *bd)
अणु
	dma_addr_t mapping;

	/* Map skb non-linear frag data क्रम DMA */
	mapping = skb_frag_dma_map(txq->dev, frag, 0,
				   skb_frag_size(frag), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(txq->dev, mapping)))
		वापस -ENOMEM;

	/* Setup the data poपूर्णांकer of the frag data */
	BD_SET_UNMAP_ADDR_LEN(bd, mapping, skb_frag_size(frag));

	वापस 0;
पूर्ण

अटल u16 qede_get_skb_hlen(काष्ठा sk_buff *skb, bool is_encap_pkt)
अणु
	अगर (is_encap_pkt)
		वापस (skb_inner_transport_header(skb) +
			inner_tcp_hdrlen(skb) - skb->data);
	अन्यथा
		वापस (skb_transport_header(skb) +
			tcp_hdrlen(skb) - skb->data);
पूर्ण

/* +2 क्रम 1st BD क्रम headers and 2nd BD क्रम headlen (अगर required) */
#अगर ((MAX_SKB_FRAGS + 2) > ETH_TX_MAX_BDS_PER_NON_LSO_PACKET)
अटल bool qede_pkt_req_lin(काष्ठा sk_buff *skb, u8 xmit_type)
अणु
	पूर्णांक allowed_frags = ETH_TX_MAX_BDS_PER_NON_LSO_PACKET - 1;

	अगर (xmit_type & XMIT_LSO) अणु
		पूर्णांक hlen;

		hlen = qede_get_skb_hlen(skb, xmit_type & XMIT_ENC);

		/* linear payload would require its own BD */
		अगर (skb_headlen(skb) > hlen)
			allowed_frags--;
	पूर्ण

	वापस (skb_shinfo(skb)->nr_frags > allowed_frags);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम qede_update_tx_producer(काष्ठा qede_tx_queue *txq)
अणु
	/* wmb makes sure that the BDs data is updated beक्रमe updating the
	 * producer, otherwise FW may पढ़ो old data from the BDs.
	 */
	wmb();
	barrier();
	ग_लिखोl(txq->tx_db.raw, txq->करोorbell_addr);

	/* Fence required to flush the ग_लिखो combined buffer, since another
	 * CPU may ग_लिखो to the same करोorbell address and data may be lost
	 * due to relaxed order nature of ग_लिखो combined bar.
	 */
	wmb();
पूर्ण

अटल पूर्णांक qede_xdp_xmit(काष्ठा qede_tx_queue *txq, dma_addr_t dma, u16 pad,
			 u16 len, काष्ठा page *page, काष्ठा xdp_frame *xdpf)
अणु
	काष्ठा eth_tx_1st_bd *bd;
	काष्ठा sw_tx_xdp *xdp;
	u16 val;

	अगर (unlikely(qed_chain_get_elem_used(&txq->tx_pbl) >=
		     txq->num_tx_buffers)) अणु
		txq->stopped_cnt++;
		वापस -ENOMEM;
	पूर्ण

	bd = qed_chain_produce(&txq->tx_pbl);
	bd->data.nbds = 1;
	bd->data.bd_flags.bitfields = BIT(ETH_TX_1ST_BD_FLAGS_START_BD_SHIFT);

	val = (len & ETH_TX_DATA_1ST_BD_PKT_LEN_MASK) <<
	       ETH_TX_DATA_1ST_BD_PKT_LEN_SHIFT;

	bd->data.bitfields = cpu_to_le16(val);

	/* We can safely ignore the offset, as it's 0 क्रम XDP */
	BD_SET_UNMAP_ADDR_LEN(bd, dma + pad, len);

	xdp = txq->sw_tx_ring.xdp + txq->sw_tx_prod;
	xdp->mapping = dma;
	xdp->page = page;
	xdp->xdpf = xdpf;

	txq->sw_tx_prod = (txq->sw_tx_prod + 1) % txq->num_tx_buffers;

	वापस 0;
पूर्ण

पूर्णांक qede_xdp_transmit(काष्ठा net_device *dev, पूर्णांक n_frames,
		      काष्ठा xdp_frame **frames, u32 flags)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	काष्ठा device *dmadev = &edev->pdev->dev;
	काष्ठा qede_tx_queue *xdp_tx;
	काष्ठा xdp_frame *xdpf;
	dma_addr_t mapping;
	पूर्णांक i, nxmit = 0;
	u16 xdp_prod;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	अगर (unlikely(!netअगर_running(dev)))
		वापस -ENETDOWN;

	i = smp_processor_id() % edev->total_xdp_queues;
	xdp_tx = edev->fp_array[i].xdp_tx;

	spin_lock(&xdp_tx->xdp_tx_lock);

	क्रम (i = 0; i < n_frames; i++) अणु
		xdpf = frames[i];

		mapping = dma_map_single(dmadev, xdpf->data, xdpf->len,
					 DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(dmadev, mapping)))
			अवरोध;

		अगर (unlikely(qede_xdp_xmit(xdp_tx, mapping, 0, xdpf->len,
					   शून्य, xdpf)))
			अवरोध;
		nxmit++;
	पूर्ण

	अगर (flags & XDP_XMIT_FLUSH) अणु
		xdp_prod = qed_chain_get_prod_idx(&xdp_tx->tx_pbl);

		xdp_tx->tx_db.data.bd_prod = cpu_to_le16(xdp_prod);
		qede_update_tx_producer(xdp_tx);
	पूर्ण

	spin_unlock(&xdp_tx->xdp_tx_lock);

	वापस nxmit;
पूर्ण

पूर्णांक qede_txq_has_work(काष्ठा qede_tx_queue *txq)
अणु
	u16 hw_bd_cons;

	/* Tell compiler that consumer and producer can change */
	barrier();
	hw_bd_cons = le16_to_cpu(*txq->hw_cons_ptr);
	अगर (qed_chain_get_cons_idx(&txq->tx_pbl) == hw_bd_cons + 1)
		वापस 0;

	वापस hw_bd_cons != qed_chain_get_cons_idx(&txq->tx_pbl);
पूर्ण

अटल व्योम qede_xdp_tx_पूर्णांक(काष्ठा qede_dev *edev, काष्ठा qede_tx_queue *txq)
अणु
	काष्ठा sw_tx_xdp *xdp_info, *xdp_arr = txq->sw_tx_ring.xdp;
	काष्ठा device *dev = &edev->pdev->dev;
	काष्ठा xdp_frame *xdpf;
	u16 hw_bd_cons;

	hw_bd_cons = le16_to_cpu(*txq->hw_cons_ptr);
	barrier();

	जबतक (hw_bd_cons != qed_chain_get_cons_idx(&txq->tx_pbl)) अणु
		xdp_info = xdp_arr + txq->sw_tx_cons;
		xdpf = xdp_info->xdpf;

		अगर (xdpf) अणु
			dma_unmap_single(dev, xdp_info->mapping, xdpf->len,
					 DMA_TO_DEVICE);
			xdp_वापस_frame(xdpf);

			xdp_info->xdpf = शून्य;
		पूर्ण अन्यथा अणु
			dma_unmap_page(dev, xdp_info->mapping, PAGE_SIZE,
				       DMA_BIसूचीECTIONAL);
			__मुक्त_page(xdp_info->page);
		पूर्ण

		qed_chain_consume(&txq->tx_pbl);
		txq->sw_tx_cons = (txq->sw_tx_cons + 1) % txq->num_tx_buffers;
		txq->xmit_pkts++;
	पूर्ण
पूर्ण

अटल पूर्णांक qede_tx_पूर्णांक(काष्ठा qede_dev *edev, काष्ठा qede_tx_queue *txq)
अणु
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;
	काष्ठा netdev_queue *netdev_txq;
	u16 hw_bd_cons;
	पूर्णांक rc;

	netdev_txq = netdev_get_tx_queue(edev->ndev, txq->ndev_txq_id);

	hw_bd_cons = le16_to_cpu(*txq->hw_cons_ptr);
	barrier();

	जबतक (hw_bd_cons != qed_chain_get_cons_idx(&txq->tx_pbl)) अणु
		पूर्णांक len = 0;

		rc = qede_मुक्त_tx_pkt(edev, txq, &len);
		अगर (rc) अणु
			DP_NOTICE(edev, "hw_bd_cons = %d, chain_cons=%d\n",
				  hw_bd_cons,
				  qed_chain_get_cons_idx(&txq->tx_pbl));
			अवरोध;
		पूर्ण

		bytes_compl += len;
		pkts_compl++;
		txq->sw_tx_cons = (txq->sw_tx_cons + 1) % txq->num_tx_buffers;
		txq->xmit_pkts++;
	पूर्ण

	netdev_tx_completed_queue(netdev_txq, pkts_compl, bytes_compl);

	/* Need to make the tx_bd_cons update visible to start_xmit()
	 * beक्रमe checking क्रम netअगर_tx_queue_stopped().  Without the
	 * memory barrier, there is a small possibility that
	 * start_xmit() will miss it and cause the queue to be stopped
	 * क्रमever.
	 * On the other hand we need an rmb() here to ensure the proper
	 * ordering of bit testing in the following
	 * netअगर_tx_queue_stopped(txq) call.
	 */
	smp_mb();

	अगर (unlikely(netअगर_tx_queue_stopped(netdev_txq))) अणु
		/* Taking tx_lock is needed to prevent reenabling the queue
		 * जबतक it's empty. This could have happen अगर rx_action() माला_लो
		 * suspended in qede_tx_पूर्णांक() after the condition beक्रमe
		 * netअगर_tx_wake_queue(), जबतक tx_action (qede_start_xmit()):
		 *
		 * stops the queue->sees fresh tx_bd_cons->releases the queue->
		 * sends some packets consuming the whole queue again->
		 * stops the queue
		 */

		__netअगर_tx_lock(netdev_txq, smp_processor_id());

		अगर ((netअगर_tx_queue_stopped(netdev_txq)) &&
		    (edev->state == QEDE_STATE_OPEN) &&
		    (qed_chain_get_elem_left(&txq->tx_pbl)
		      >= (MAX_SKB_FRAGS + 1))) अणु
			netअगर_tx_wake_queue(netdev_txq);
			DP_VERBOSE(edev, NETIF_MSG_TX_DONE,
				   "Wake queue was called\n");
		पूर्ण

		__netअगर_tx_unlock(netdev_txq);
	पूर्ण

	वापस 0;
पूर्ण

bool qede_has_rx_work(काष्ठा qede_rx_queue *rxq)
अणु
	u16 hw_comp_cons, sw_comp_cons;

	/* Tell compiler that status block fields can change */
	barrier();

	hw_comp_cons = le16_to_cpu(*rxq->hw_cons_ptr);
	sw_comp_cons = qed_chain_get_cons_idx(&rxq->rx_comp_ring);

	वापस hw_comp_cons != sw_comp_cons;
पूर्ण

अटल अंतरभूत व्योम qede_rx_bd_ring_consume(काष्ठा qede_rx_queue *rxq)
अणु
	qed_chain_consume(&rxq->rx_bd_ring);
	rxq->sw_rx_cons++;
पूर्ण

/* This function reuses the buffer(from an offset) from
 * consumer index to producer index in the bd ring
 */
अटल अंतरभूत व्योम qede_reuse_page(काष्ठा qede_rx_queue *rxq,
				   काष्ठा sw_rx_data *curr_cons)
अणु
	काष्ठा eth_rx_bd *rx_bd_prod = qed_chain_produce(&rxq->rx_bd_ring);
	काष्ठा sw_rx_data *curr_prod;
	dma_addr_t new_mapping;

	curr_prod = &rxq->sw_rx_ring[rxq->sw_rx_prod & NUM_RX_BDS_MAX];
	*curr_prod = *curr_cons;

	new_mapping = curr_prod->mapping + curr_prod->page_offset;

	rx_bd_prod->addr.hi = cpu_to_le32(upper_32_bits(new_mapping));
	rx_bd_prod->addr.lo = cpu_to_le32(lower_32_bits(new_mapping) +
					  rxq->rx_headroom);

	rxq->sw_rx_prod++;
	curr_cons->data = शून्य;
पूर्ण

/* In हाल of allocation failures reuse buffers
 * from consumer index to produce buffers क्रम firmware
 */
व्योम qede_recycle_rx_bd_ring(काष्ठा qede_rx_queue *rxq, u8 count)
अणु
	काष्ठा sw_rx_data *curr_cons;

	क्रम (; count > 0; count--) अणु
		curr_cons = &rxq->sw_rx_ring[rxq->sw_rx_cons & NUM_RX_BDS_MAX];
		qede_reuse_page(rxq, curr_cons);
		qede_rx_bd_ring_consume(rxq);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक qede_पुनः_स्मृति_rx_buffer(काष्ठा qede_rx_queue *rxq,
					 काष्ठा sw_rx_data *curr_cons)
अणु
	/* Move to the next segment in the page */
	curr_cons->page_offset += rxq->rx_buf_seg_size;

	अगर (curr_cons->page_offset == PAGE_SIZE) अणु
		अगर (unlikely(qede_alloc_rx_buffer(rxq, true))) अणु
			/* Since we failed to allocate new buffer
			 * current buffer can be used again.
			 */
			curr_cons->page_offset -= rxq->rx_buf_seg_size;

			वापस -ENOMEM;
		पूर्ण

		dma_unmap_page(rxq->dev, curr_cons->mapping,
			       PAGE_SIZE, rxq->data_direction);
	पूर्ण अन्यथा अणु
		/* Increment refcount of the page as we करोn't want
		 * network stack to take the ownership of the page
		 * which can be recycled multiple बार by the driver.
		 */
		page_ref_inc(curr_cons->data);
		qede_reuse_page(rxq, curr_cons);
	पूर्ण

	वापस 0;
पूर्ण

व्योम qede_update_rx_prod(काष्ठा qede_dev *edev, काष्ठा qede_rx_queue *rxq)
अणु
	u16 bd_prod = qed_chain_get_prod_idx(&rxq->rx_bd_ring);
	u16 cqe_prod = qed_chain_get_prod_idx(&rxq->rx_comp_ring);
	काष्ठा eth_rx_prod_data rx_prods = अणु0पूर्ण;

	/* Update producers */
	rx_prods.bd_prod = cpu_to_le16(bd_prod);
	rx_prods.cqe_prod = cpu_to_le16(cqe_prod);

	/* Make sure that the BD and SGE data is updated beक्रमe updating the
	 * producers since FW might पढ़ो the BD/SGE right after the producer
	 * is updated.
	 */
	wmb();

	पूर्णांकernal_ram_wr(rxq->hw_rxq_prod_addr, माप(rx_prods),
			(u32 *)&rx_prods);
पूर्ण

अटल व्योम qede_get_rxhash(काष्ठा sk_buff *skb, u8 bitfields, __le32 rss_hash)
अणु
	क्रमागत pkt_hash_types hash_type = PKT_HASH_TYPE_NONE;
	क्रमागत rss_hash_type htype;
	u32 hash = 0;

	htype = GET_FIELD(bitfields, ETH_FAST_PATH_RX_REG_CQE_RSS_HASH_TYPE);
	अगर (htype) अणु
		hash_type = ((htype == RSS_HASH_TYPE_IPV4) ||
			     (htype == RSS_HASH_TYPE_IPV6)) ?
			    PKT_HASH_TYPE_L3 : PKT_HASH_TYPE_L4;
		hash = le32_to_cpu(rss_hash);
	पूर्ण
	skb_set_hash(skb, hash, hash_type);
पूर्ण

अटल व्योम qede_set_skb_csum(काष्ठा sk_buff *skb, u8 csum_flag)
अणु
	skb_checksum_none_निश्चित(skb);

	अगर (csum_flag & QEDE_CSUM_UNNECESSARY)
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (csum_flag & QEDE_TUNN_CSUM_UNNECESSARY) अणु
		skb->csum_level = 1;
		skb->encapsulation = 1;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम qede_skb_receive(काष्ठा qede_dev *edev,
				    काष्ठा qede_fastpath *fp,
				    काष्ठा qede_rx_queue *rxq,
				    काष्ठा sk_buff *skb, u16 vlan_tag)
अणु
	अगर (vlan_tag)
		__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q), vlan_tag);

	napi_gro_receive(&fp->napi, skb);
पूर्ण

अटल व्योम qede_set_gro_params(काष्ठा qede_dev *edev,
				काष्ठा sk_buff *skb,
				काष्ठा eth_fast_path_rx_tpa_start_cqe *cqe)
अणु
	u16 parsing_flags = le16_to_cpu(cqe->pars_flags.flags);

	अगर (((parsing_flags >> PARSING_AND_ERR_FLAGS_L3TYPE_SHIFT) &
	    PARSING_AND_ERR_FLAGS_L3TYPE_MASK) == 2)
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV6;
	अन्यथा
		skb_shinfo(skb)->gso_type = SKB_GSO_TCPV4;

	skb_shinfo(skb)->gso_size = __le16_to_cpu(cqe->len_on_first_bd) -
				    cqe->header_len;
पूर्ण

अटल पूर्णांक qede_fill_frag_skb(काष्ठा qede_dev *edev,
			      काष्ठा qede_rx_queue *rxq,
			      u8 tpa_agg_index, u16 len_on_bd)
अणु
	काष्ठा sw_rx_data *current_bd = &rxq->sw_rx_ring[rxq->sw_rx_cons &
							 NUM_RX_BDS_MAX];
	काष्ठा qede_agg_info *tpa_info = &rxq->tpa_info[tpa_agg_index];
	काष्ठा sk_buff *skb = tpa_info->skb;

	अगर (unlikely(tpa_info->state != QEDE_AGG_STATE_START))
		जाओ out;

	/* Add one frag and update the appropriate fields in the skb */
	skb_fill_page_desc(skb, tpa_info->frag_id++,
			   current_bd->data,
			   current_bd->page_offset + rxq->rx_headroom,
			   len_on_bd);

	अगर (unlikely(qede_पुनः_स्मृति_rx_buffer(rxq, current_bd))) अणु
		/* Incr page ref count to reuse on allocation failure
		 * so that it करोesn't get मुक्तd जबतक मुक्तing SKB.
		 */
		page_ref_inc(current_bd->data);
		जाओ out;
	पूर्ण

	qede_rx_bd_ring_consume(rxq);

	skb->data_len += len_on_bd;
	skb->truesize += rxq->rx_buf_seg_size;
	skb->len += len_on_bd;

	वापस 0;

out:
	tpa_info->state = QEDE_AGG_STATE_ERROR;
	qede_recycle_rx_bd_ring(rxq, 1);

	वापस -ENOMEM;
पूर्ण

अटल bool qede_tunn_exist(u16 flag)
अणु
	वापस !!(flag & (PARSING_AND_ERR_FLAGS_TUNNELEXIST_MASK <<
			  PARSING_AND_ERR_FLAGS_TUNNELEXIST_SHIFT));
पूर्ण

अटल u8 qede_check_tunn_csum(u16 flag)
अणु
	u16 csum_flag = 0;
	u8 tcsum = 0;

	अगर (flag & (PARSING_AND_ERR_FLAGS_TUNNELL4CHKSMWASCALCULATED_MASK <<
		    PARSING_AND_ERR_FLAGS_TUNNELL4CHKSMWASCALCULATED_SHIFT))
		csum_flag |= PARSING_AND_ERR_FLAGS_TUNNELL4CHKSMERROR_MASK <<
			     PARSING_AND_ERR_FLAGS_TUNNELL4CHKSMERROR_SHIFT;

	अगर (flag & (PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED_MASK <<
		    PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED_SHIFT)) अणु
		csum_flag |= PARSING_AND_ERR_FLAGS_L4CHKSMERROR_MASK <<
			     PARSING_AND_ERR_FLAGS_L4CHKSMERROR_SHIFT;
		tcsum = QEDE_TUNN_CSUM_UNNECESSARY;
	पूर्ण

	csum_flag |= PARSING_AND_ERR_FLAGS_TUNNELIPHDRERROR_MASK <<
		     PARSING_AND_ERR_FLAGS_TUNNELIPHDRERROR_SHIFT |
		     PARSING_AND_ERR_FLAGS_IPHDRERROR_MASK <<
		     PARSING_AND_ERR_FLAGS_IPHDRERROR_SHIFT;

	अगर (csum_flag & flag)
		वापस QEDE_CSUM_ERROR;

	वापस QEDE_CSUM_UNNECESSARY | tcsum;
पूर्ण

अटल अंतरभूत काष्ठा sk_buff *
qede_build_skb(काष्ठा qede_rx_queue *rxq,
	       काष्ठा sw_rx_data *bd, u16 len, u16 pad)
अणु
	काष्ठा sk_buff *skb;
	व्योम *buf;

	buf = page_address(bd->data) + bd->page_offset;
	skb = build_skb(buf, rxq->rx_buf_seg_size);

	skb_reserve(skb, pad);
	skb_put(skb, len);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
qede_tpa_rx_build_skb(काष्ठा qede_dev *edev,
		      काष्ठा qede_rx_queue *rxq,
		      काष्ठा sw_rx_data *bd, u16 len, u16 pad,
		      bool alloc_skb)
अणु
	काष्ठा sk_buff *skb;

	skb = qede_build_skb(rxq, bd, len, pad);
	bd->page_offset += rxq->rx_buf_seg_size;

	अगर (bd->page_offset == PAGE_SIZE) अणु
		अगर (unlikely(qede_alloc_rx_buffer(rxq, true))) अणु
			DP_NOTICE(edev,
				  "Failed to allocate RX buffer for tpa start\n");
			bd->page_offset -= rxq->rx_buf_seg_size;
			page_ref_inc(bd->data);
			dev_kमुक्त_skb_any(skb);
			वापस शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		page_ref_inc(bd->data);
		qede_reuse_page(rxq, bd);
	पूर्ण

	/* We've consumed the first BD and prepared an SKB */
	qede_rx_bd_ring_consume(rxq);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
qede_rx_build_skb(काष्ठा qede_dev *edev,
		  काष्ठा qede_rx_queue *rxq,
		  काष्ठा sw_rx_data *bd, u16 len, u16 pad)
अणु
	काष्ठा sk_buff *skb = शून्य;

	/* For smaller frames still need to allocate skb, स_नकल
	 * data and benefit in reusing the page segment instead of
	 * un-mapping it.
	 */
	अगर ((len + pad <= edev->rx_copyअवरोध)) अणु
		अचिन्हित पूर्णांक offset = bd->page_offset + pad;

		skb = netdev_alloc_skb(edev->ndev, QEDE_RX_HDR_SIZE);
		अगर (unlikely(!skb))
			वापस शून्य;

		skb_reserve(skb, pad);
		skb_put_data(skb, page_address(bd->data) + offset, len);
		qede_reuse_page(rxq, bd);
		जाओ out;
	पूर्ण

	skb = qede_build_skb(rxq, bd, len, pad);

	अगर (unlikely(qede_पुनः_स्मृति_rx_buffer(rxq, bd))) अणु
		/* Incr page ref count to reuse on allocation failure so
		 * that it करोesn't get मुक्तd जबतक मुक्तing SKB [as its
		 * alपढ़ोy mapped there].
		 */
		page_ref_inc(bd->data);
		dev_kमुक्त_skb_any(skb);
		वापस शून्य;
	पूर्ण
out:
	/* We've consumed the first BD and prepared an SKB */
	qede_rx_bd_ring_consume(rxq);

	वापस skb;
पूर्ण

अटल व्योम qede_tpa_start(काष्ठा qede_dev *edev,
			   काष्ठा qede_rx_queue *rxq,
			   काष्ठा eth_fast_path_rx_tpa_start_cqe *cqe)
अणु
	काष्ठा qede_agg_info *tpa_info = &rxq->tpa_info[cqe->tpa_agg_index];
	काष्ठा sw_rx_data *sw_rx_data_cons;
	u16 pad;

	sw_rx_data_cons = &rxq->sw_rx_ring[rxq->sw_rx_cons & NUM_RX_BDS_MAX];
	pad = cqe->placement_offset + rxq->rx_headroom;

	tpa_info->skb = qede_tpa_rx_build_skb(edev, rxq, sw_rx_data_cons,
					      le16_to_cpu(cqe->len_on_first_bd),
					      pad, false);
	tpa_info->buffer.page_offset = sw_rx_data_cons->page_offset;
	tpa_info->buffer.mapping = sw_rx_data_cons->mapping;

	अगर (unlikely(!tpa_info->skb)) अणु
		DP_NOTICE(edev, "Failed to allocate SKB for gro\n");

		/* Consume from ring but करो not produce since
		 * this might be used by FW still, it will be re-used
		 * at TPA end.
		 */
		tpa_info->tpa_start_fail = true;
		qede_rx_bd_ring_consume(rxq);
		tpa_info->state = QEDE_AGG_STATE_ERROR;
		जाओ cons_buf;
	पूर्ण

	tpa_info->frag_id = 0;
	tpa_info->state = QEDE_AGG_STATE_START;

	अगर ((le16_to_cpu(cqe->pars_flags.flags) >>
	     PARSING_AND_ERR_FLAGS_TAG8021QEXIST_SHIFT) &
	    PARSING_AND_ERR_FLAGS_TAG8021QEXIST_MASK)
		tpa_info->vlan_tag = le16_to_cpu(cqe->vlan_tag);
	अन्यथा
		tpa_info->vlan_tag = 0;

	qede_get_rxhash(tpa_info->skb, cqe->bitfields, cqe->rss_hash);

	/* This is needed in order to enable क्रमwarding support */
	qede_set_gro_params(edev, tpa_info->skb, cqe);

cons_buf: /* We still need to handle bd_len_list to consume buffers */
	अगर (likely(cqe->bw_ext_bd_len_list[0]))
		qede_fill_frag_skb(edev, rxq, cqe->tpa_agg_index,
				   le16_to_cpu(cqe->bw_ext_bd_len_list[0]));

	अगर (unlikely(cqe->bw_ext_bd_len_list[1])) अणु
		DP_ERR(edev,
		       "Unlikely - got a TPA aggregation with more than one bw_ext_bd_len_list entry in the TPA start\n");
		tpa_info->state = QEDE_AGG_STATE_ERROR;
	पूर्ण
पूर्ण

#अगर_घोषित CONFIG_INET
अटल व्योम qede_gro_ip_csum(काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा iphdr *iph = ip_hdr(skb);
	काष्ठा tcphdr *th;

	skb_set_transport_header(skb, माप(काष्ठा iphdr));
	th = tcp_hdr(skb);

	th->check = ~tcp_v4_check(skb->len - skb_transport_offset(skb),
				  iph->saddr, iph->daddr, 0);

	tcp_gro_complete(skb);
पूर्ण

अटल व्योम qede_gro_ipv6_csum(काष्ठा sk_buff *skb)
अणु
	काष्ठा ipv6hdr *iph = ipv6_hdr(skb);
	काष्ठा tcphdr *th;

	skb_set_transport_header(skb, माप(काष्ठा ipv6hdr));
	th = tcp_hdr(skb);

	th->check = ~tcp_v6_check(skb->len - skb_transport_offset(skb),
				  &iph->saddr, &iph->daddr, 0);
	tcp_gro_complete(skb);
पूर्ण
#पूर्ण_अगर

अटल व्योम qede_gro_receive(काष्ठा qede_dev *edev,
			     काष्ठा qede_fastpath *fp,
			     काष्ठा sk_buff *skb,
			     u16 vlan_tag)
अणु
	/* FW can send a single MTU sized packet from gro flow
	 * due to aggregation समयout/last segment etc. which
	 * is not expected to be a gro packet. If a skb has zero
	 * frags then simply push it in the stack as non gso skb.
	 */
	अगर (unlikely(!skb->data_len)) अणु
		skb_shinfo(skb)->gso_type = 0;
		skb_shinfo(skb)->gso_size = 0;
		जाओ send_skb;
	पूर्ण

#अगर_घोषित CONFIG_INET
	अगर (skb_shinfo(skb)->gso_size) अणु
		skb_reset_network_header(skb);

		चयन (skb->protocol) अणु
		हाल htons(ETH_P_IP):
			qede_gro_ip_csum(skb);
			अवरोध;
		हाल htons(ETH_P_IPV6):
			qede_gro_ipv6_csum(skb);
			अवरोध;
		शेष:
			DP_ERR(edev,
			       "Error: FW GRO supports only IPv4/IPv6, not 0x%04x\n",
			       ntohs(skb->protocol));
		पूर्ण
	पूर्ण
#पूर्ण_अगर

send_skb:
	skb_record_rx_queue(skb, fp->rxq->rxq_id);
	qede_skb_receive(edev, fp, fp->rxq, skb, vlan_tag);
पूर्ण

अटल अंतरभूत व्योम qede_tpa_cont(काष्ठा qede_dev *edev,
				 काष्ठा qede_rx_queue *rxq,
				 काष्ठा eth_fast_path_rx_tpa_cont_cqe *cqe)
अणु
	पूर्णांक i;

	क्रम (i = 0; cqe->len_list[i]; i++)
		qede_fill_frag_skb(edev, rxq, cqe->tpa_agg_index,
				   le16_to_cpu(cqe->len_list[i]));

	अगर (unlikely(i > 1))
		DP_ERR(edev,
		       "Strange - TPA cont with more than a single len_list entry\n");
पूर्ण

अटल पूर्णांक qede_tpa_end(काष्ठा qede_dev *edev,
			काष्ठा qede_fastpath *fp,
			काष्ठा eth_fast_path_rx_tpa_end_cqe *cqe)
अणु
	काष्ठा qede_rx_queue *rxq = fp->rxq;
	काष्ठा qede_agg_info *tpa_info;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	tpa_info = &rxq->tpa_info[cqe->tpa_agg_index];
	skb = tpa_info->skb;

	अगर (tpa_info->buffer.page_offset == PAGE_SIZE)
		dma_unmap_page(rxq->dev, tpa_info->buffer.mapping,
			       PAGE_SIZE, rxq->data_direction);

	क्रम (i = 0; cqe->len_list[i]; i++)
		qede_fill_frag_skb(edev, rxq, cqe->tpa_agg_index,
				   le16_to_cpu(cqe->len_list[i]));
	अगर (unlikely(i > 1))
		DP_ERR(edev,
		       "Strange - TPA emd with more than a single len_list entry\n");

	अगर (unlikely(tpa_info->state != QEDE_AGG_STATE_START))
		जाओ err;

	/* Sanity */
	अगर (unlikely(cqe->num_of_bds != tpa_info->frag_id + 1))
		DP_ERR(edev,
		       "Strange - TPA had %02x BDs, but SKB has only %d frags\n",
		       cqe->num_of_bds, tpa_info->frag_id);
	अगर (unlikely(skb->len != le16_to_cpu(cqe->total_packet_len)))
		DP_ERR(edev,
		       "Strange - total packet len [cqe] is %4x but SKB has len %04x\n",
		       le16_to_cpu(cqe->total_packet_len), skb->len);

	/* Finalize the SKB */
	skb->protocol = eth_type_trans(skb, edev->ndev);
	skb->ip_summed = CHECKSUM_UNNECESSARY;

	/* tcp_gro_complete() will copy NAPI_GRO_CB(skb)->count
	 * to skb_shinfo(skb)->gso_segs
	 */
	NAPI_GRO_CB(skb)->count = le16_to_cpu(cqe->num_of_coalesced_segs);

	qede_gro_receive(edev, fp, skb, tpa_info->vlan_tag);

	tpa_info->state = QEDE_AGG_STATE_NONE;

	वापस 1;
err:
	tpa_info->state = QEDE_AGG_STATE_NONE;

	अगर (tpa_info->tpa_start_fail) अणु
		qede_reuse_page(rxq, &tpa_info->buffer);
		tpa_info->tpa_start_fail = false;
	पूर्ण

	dev_kमुक्त_skb_any(tpa_info->skb);
	tpa_info->skb = शून्य;
	वापस 0;
पूर्ण

अटल u8 qede_check_notunn_csum(u16 flag)
अणु
	u16 csum_flag = 0;
	u8 csum = 0;

	अगर (flag & (PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED_MASK <<
		    PARSING_AND_ERR_FLAGS_L4CHKSMWASCALCULATED_SHIFT)) अणु
		csum_flag |= PARSING_AND_ERR_FLAGS_L4CHKSMERROR_MASK <<
			     PARSING_AND_ERR_FLAGS_L4CHKSMERROR_SHIFT;
		csum = QEDE_CSUM_UNNECESSARY;
	पूर्ण

	csum_flag |= PARSING_AND_ERR_FLAGS_IPHDRERROR_MASK <<
		     PARSING_AND_ERR_FLAGS_IPHDRERROR_SHIFT;

	अगर (csum_flag & flag)
		वापस QEDE_CSUM_ERROR;

	वापस csum;
पूर्ण

अटल u8 qede_check_csum(u16 flag)
अणु
	अगर (!qede_tunn_exist(flag))
		वापस qede_check_notunn_csum(flag);
	अन्यथा
		वापस qede_check_tunn_csum(flag);
पूर्ण

अटल bool qede_pkt_is_ip_fragmented(काष्ठा eth_fast_path_rx_reg_cqe *cqe,
				      u16 flag)
अणु
	u8 tun_pars_flg = cqe->tunnel_pars_flags.flags;

	अगर ((tun_pars_flg & (ETH_TUNNEL_PARSING_FLAGS_IPV4_FRAGMENT_MASK <<
			     ETH_TUNNEL_PARSING_FLAGS_IPV4_FRAGMENT_SHIFT)) ||
	    (flag & (PARSING_AND_ERR_FLAGS_IPV4FRAG_MASK <<
		     PARSING_AND_ERR_FLAGS_IPV4FRAG_SHIFT)))
		वापस true;

	वापस false;
पूर्ण

/* Return true अगरf packet is to be passed to stack */
अटल bool qede_rx_xdp(काष्ठा qede_dev *edev,
			काष्ठा qede_fastpath *fp,
			काष्ठा qede_rx_queue *rxq,
			काष्ठा bpf_prog *prog,
			काष्ठा sw_rx_data *bd,
			काष्ठा eth_fast_path_rx_reg_cqe *cqe,
			u16 *data_offset, u16 *len)
अणु
	काष्ठा xdp_buff xdp;
	क्रमागत xdp_action act;

	xdp_init_buff(&xdp, rxq->rx_buf_seg_size, &rxq->xdp_rxq);
	xdp_prepare_buff(&xdp, page_address(bd->data), *data_offset,
			 *len, false);

	/* Queues always have a full reset currently, so क्रम the समय
	 * being until there's atomic program replace just mark पढ़ो
	 * side क्रम map helpers.
	 */
	rcu_पढ़ो_lock();
	act = bpf_prog_run_xdp(prog, &xdp);
	rcu_पढ़ो_unlock();

	/* Recalculate, as XDP might have changed the headers */
	*data_offset = xdp.data - xdp.data_hard_start;
	*len = xdp.data_end - xdp.data;

	अगर (act == XDP_PASS)
		वापस true;

	/* Count number of packets not to be passed to stack */
	rxq->xdp_no_pass++;

	चयन (act) अणु
	हाल XDP_TX:
		/* We need the replacement buffer beक्रमe transmit. */
		अगर (unlikely(qede_alloc_rx_buffer(rxq, true))) अणु
			qede_recycle_rx_bd_ring(rxq, 1);

			trace_xdp_exception(edev->ndev, prog, act);
			अवरोध;
		पूर्ण

		/* Now अगर there's a transmission problem, we'd still have to
		 * throw current buffer, as replacement was alपढ़ोy allocated.
		 */
		अगर (unlikely(qede_xdp_xmit(fp->xdp_tx, bd->mapping,
					   *data_offset, *len, bd->data,
					   शून्य))) अणु
			dma_unmap_page(rxq->dev, bd->mapping, PAGE_SIZE,
				       rxq->data_direction);
			__मुक्त_page(bd->data);

			trace_xdp_exception(edev->ndev, prog, act);
		पूर्ण अन्यथा अणु
			dma_sync_single_क्रम_device(rxq->dev,
						   bd->mapping + *data_offset,
						   *len, rxq->data_direction);
			fp->xdp_xmit |= QEDE_XDP_TX;
		पूर्ण

		/* Regardless, we've consumed an Rx BD */
		qede_rx_bd_ring_consume(rxq);
		अवरोध;
	हाल XDP_REसूचीECT:
		/* We need the replacement buffer beक्रमe transmit. */
		अगर (unlikely(qede_alloc_rx_buffer(rxq, true))) अणु
			qede_recycle_rx_bd_ring(rxq, 1);

			trace_xdp_exception(edev->ndev, prog, act);
			अवरोध;
		पूर्ण

		dma_unmap_page(rxq->dev, bd->mapping, PAGE_SIZE,
			       rxq->data_direction);

		अगर (unlikely(xdp_करो_redirect(edev->ndev, &xdp, prog)))
			DP_NOTICE(edev, "Failed to redirect the packet\n");
		अन्यथा
			fp->xdp_xmit |= QEDE_XDP_REसूचीECT;

		qede_rx_bd_ring_consume(rxq);
		अवरोध;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
		trace_xdp_exception(edev->ndev, prog, act);
		fallthrough;
	हाल XDP_DROP:
		qede_recycle_rx_bd_ring(rxq, cqe->bd_num);
	पूर्ण

	वापस false;
पूर्ण

अटल पूर्णांक qede_rx_build_jumbo(काष्ठा qede_dev *edev,
			       काष्ठा qede_rx_queue *rxq,
			       काष्ठा sk_buff *skb,
			       काष्ठा eth_fast_path_rx_reg_cqe *cqe,
			       u16 first_bd_len)
अणु
	u16 pkt_len = le16_to_cpu(cqe->pkt_len);
	काष्ठा sw_rx_data *bd;
	u16 bd_cons_idx;
	u8 num_frags;

	pkt_len -= first_bd_len;

	/* We've alपढ़ोy used one BD क्रम the SKB. Now take care of the rest */
	क्रम (num_frags = cqe->bd_num - 1; num_frags > 0; num_frags--) अणु
		u16 cur_size = pkt_len > rxq->rx_buf_size ? rxq->rx_buf_size :
		    pkt_len;

		अगर (unlikely(!cur_size)) अणु
			DP_ERR(edev,
			       "Still got %d BDs for mapping jumbo, but length became 0\n",
			       num_frags);
			जाओ out;
		पूर्ण

		/* We need a replacement buffer क्रम each BD */
		अगर (unlikely(qede_alloc_rx_buffer(rxq, true)))
			जाओ out;

		/* Now that we've allocated the replacement buffer,
		 * we can safely consume the next BD and map it to the SKB.
		 */
		bd_cons_idx = rxq->sw_rx_cons & NUM_RX_BDS_MAX;
		bd = &rxq->sw_rx_ring[bd_cons_idx];
		qede_rx_bd_ring_consume(rxq);

		dma_unmap_page(rxq->dev, bd->mapping,
			       PAGE_SIZE, DMA_FROM_DEVICE);

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, bd->data,
				rxq->rx_headroom, cur_size, PAGE_SIZE);

		pkt_len -= cur_size;
	पूर्ण

	अगर (unlikely(pkt_len))
		DP_ERR(edev,
		       "Mapped all BDs of jumbo, but still have %d bytes\n",
		       pkt_len);

out:
	वापस num_frags;
पूर्ण

अटल पूर्णांक qede_rx_process_tpa_cqe(काष्ठा qede_dev *edev,
				   काष्ठा qede_fastpath *fp,
				   काष्ठा qede_rx_queue *rxq,
				   जोड़ eth_rx_cqe *cqe,
				   क्रमागत eth_rx_cqe_type type)
अणु
	चयन (type) अणु
	हाल ETH_RX_CQE_TYPE_TPA_START:
		qede_tpa_start(edev, rxq, &cqe->fast_path_tpa_start);
		वापस 0;
	हाल ETH_RX_CQE_TYPE_TPA_CONT:
		qede_tpa_cont(edev, rxq, &cqe->fast_path_tpa_cont);
		वापस 0;
	हाल ETH_RX_CQE_TYPE_TPA_END:
		वापस qede_tpa_end(edev, fp, &cqe->fast_path_tpa_end);
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल पूर्णांक qede_rx_process_cqe(काष्ठा qede_dev *edev,
			       काष्ठा qede_fastpath *fp,
			       काष्ठा qede_rx_queue *rxq)
अणु
	काष्ठा bpf_prog *xdp_prog = READ_ONCE(rxq->xdp_prog);
	काष्ठा eth_fast_path_rx_reg_cqe *fp_cqe;
	u16 len, pad, bd_cons_idx, parse_flag;
	क्रमागत eth_rx_cqe_type cqe_type;
	जोड़ eth_rx_cqe *cqe;
	काष्ठा sw_rx_data *bd;
	काष्ठा sk_buff *skb;
	__le16 flags;
	u8 csum_flag;

	/* Get the CQE from the completion ring */
	cqe = (जोड़ eth_rx_cqe *)qed_chain_consume(&rxq->rx_comp_ring);
	cqe_type = cqe->fast_path_regular.type;

	/* Process an unlikely slowpath event */
	अगर (unlikely(cqe_type == ETH_RX_CQE_TYPE_SLOW_PATH)) अणु
		काष्ठा eth_slow_path_rx_cqe *sp_cqe;

		sp_cqe = (काष्ठा eth_slow_path_rx_cqe *)cqe;
		edev->ops->eth_cqe_completion(edev->cdev, fp->id, sp_cqe);
		वापस 0;
	पूर्ण

	/* Handle TPA cqes */
	अगर (cqe_type != ETH_RX_CQE_TYPE_REGULAR)
		वापस qede_rx_process_tpa_cqe(edev, fp, rxq, cqe, cqe_type);

	/* Get the data from the SW ring; Consume it only after it's evident
	 * we wouldn't recycle it.
	 */
	bd_cons_idx = rxq->sw_rx_cons & NUM_RX_BDS_MAX;
	bd = &rxq->sw_rx_ring[bd_cons_idx];

	fp_cqe = &cqe->fast_path_regular;
	len = le16_to_cpu(fp_cqe->len_on_first_bd);
	pad = fp_cqe->placement_offset + rxq->rx_headroom;

	/* Run eBPF program अगर one is attached */
	अगर (xdp_prog)
		अगर (!qede_rx_xdp(edev, fp, rxq, xdp_prog, bd, fp_cqe,
				 &pad, &len))
			वापस 0;

	/* If this is an error packet then drop it */
	flags = cqe->fast_path_regular.pars_flags.flags;
	parse_flag = le16_to_cpu(flags);

	csum_flag = qede_check_csum(parse_flag);
	अगर (unlikely(csum_flag == QEDE_CSUM_ERROR)) अणु
		अगर (qede_pkt_is_ip_fragmented(fp_cqe, parse_flag))
			rxq->rx_ip_frags++;
		अन्यथा
			rxq->rx_hw_errors++;
	पूर्ण

	/* Basic validation passed; Need to prepare an SKB. This would also
	 * guarantee to finally consume the first BD upon success.
	 */
	skb = qede_rx_build_skb(edev, rxq, bd, len, pad);
	अगर (!skb) अणु
		rxq->rx_alloc_errors++;
		qede_recycle_rx_bd_ring(rxq, fp_cqe->bd_num);
		वापस 0;
	पूर्ण

	/* In हाल of Jumbo packet, several PAGE_SIZEd buffers will be poपूर्णांकed
	 * by a single cqe.
	 */
	अगर (fp_cqe->bd_num > 1) अणु
		u16 unmapped_frags = qede_rx_build_jumbo(edev, rxq, skb,
							 fp_cqe, len);

		अगर (unlikely(unmapped_frags > 0)) अणु
			qede_recycle_rx_bd_ring(rxq, unmapped_frags);
			dev_kमुक्त_skb_any(skb);
			वापस 0;
		पूर्ण
	पूर्ण

	/* The SKB contains all the data. Now prepare meta-magic */
	skb->protocol = eth_type_trans(skb, edev->ndev);
	qede_get_rxhash(skb, fp_cqe->bitfields, fp_cqe->rss_hash);
	qede_set_skb_csum(skb, csum_flag);
	skb_record_rx_queue(skb, rxq->rxq_id);
	qede_ptp_record_rx_ts(edev, cqe, skb);

	/* SKB is prepared - pass it to stack */
	qede_skb_receive(edev, fp, rxq, skb, le16_to_cpu(fp_cqe->vlan_tag));

	वापस 1;
पूर्ण

अटल पूर्णांक qede_rx_पूर्णांक(काष्ठा qede_fastpath *fp, पूर्णांक budget)
अणु
	काष्ठा qede_rx_queue *rxq = fp->rxq;
	काष्ठा qede_dev *edev = fp->edev;
	पूर्णांक work_करोne = 0, rcv_pkts = 0;
	u16 hw_comp_cons, sw_comp_cons;

	hw_comp_cons = le16_to_cpu(*rxq->hw_cons_ptr);
	sw_comp_cons = qed_chain_get_cons_idx(&rxq->rx_comp_ring);

	/* Memory barrier to prevent the CPU from करोing speculative पढ़ोs of CQE
	 * / BD in the जबतक-loop beक्रमe पढ़ोing hw_comp_cons. If the CQE is
	 * पढ़ो beक्रमe it is written by FW, then FW ग_लिखोs CQE and SB, and then
	 * the CPU पढ़ोs the hw_comp_cons, it will use an old CQE.
	 */
	rmb();

	/* Loop to complete all indicated BDs */
	जबतक ((sw_comp_cons != hw_comp_cons) && (work_करोne < budget)) अणु
		rcv_pkts += qede_rx_process_cqe(edev, fp, rxq);
		qed_chain_recycle_consumed(&rxq->rx_comp_ring);
		sw_comp_cons = qed_chain_get_cons_idx(&rxq->rx_comp_ring);
		work_करोne++;
	पूर्ण

	rxq->rcv_pkts += rcv_pkts;

	/* Allocate replacement buffers */
	जबतक (rxq->num_rx_buffers - rxq->filled_buffers)
		अगर (qede_alloc_rx_buffer(rxq, false))
			अवरोध;

	/* Update producers */
	qede_update_rx_prod(edev, rxq);

	वापस work_करोne;
पूर्ण

अटल bool qede_poll_is_more_work(काष्ठा qede_fastpath *fp)
अणु
	qed_sb_update_sb_idx(fp->sb_info);

	/* *_has_*_work() पढ़ोs the status block, thus we need to ensure that
	 * status block indices have been actually पढ़ो (qed_sb_update_sb_idx)
	 * prior to this check (*_has_*_work) so that we won't ग_लिखो the
	 * "newer" value of the status block to HW (अगर there was a DMA right
	 * after qede_has_rx_work and अगर there is no rmb, the memory पढ़ोing
	 * (qed_sb_update_sb_idx) may be postponed to right beक्रमe *_ack_sb).
	 * In this हाल there will never be another पूर्णांकerrupt until there is
	 * another update of the status block, जबतक there is still unhandled
	 * work.
	 */
	rmb();

	अगर (likely(fp->type & QEDE_FASTPATH_RX))
		अगर (qede_has_rx_work(fp->rxq))
			वापस true;

	अगर (fp->type & QEDE_FASTPATH_XDP)
		अगर (qede_txq_has_work(fp->xdp_tx))
			वापस true;

	अगर (likely(fp->type & QEDE_FASTPATH_TX)) अणु
		पूर्णांक cos;

		क्रम_each_cos_in_txq(fp->edev, cos) अणु
			अगर (qede_txq_has_work(&fp->txq[cos]))
				वापस true;
		पूर्ण
	पूर्ण

	वापस false;
पूर्ण

/*********************
 * NDO & API related *
 *********************/
पूर्णांक qede_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा qede_fastpath *fp = container_of(napi, काष्ठा qede_fastpath,
						napi);
	काष्ठा qede_dev *edev = fp->edev;
	पूर्णांक rx_work_करोne = 0;
	u16 xdp_prod;

	fp->xdp_xmit = 0;

	अगर (likely(fp->type & QEDE_FASTPATH_TX)) अणु
		पूर्णांक cos;

		क्रम_each_cos_in_txq(fp->edev, cos) अणु
			अगर (qede_txq_has_work(&fp->txq[cos]))
				qede_tx_पूर्णांक(edev, &fp->txq[cos]);
		पूर्ण
	पूर्ण

	अगर ((fp->type & QEDE_FASTPATH_XDP) && qede_txq_has_work(fp->xdp_tx))
		qede_xdp_tx_पूर्णांक(edev, fp->xdp_tx);

	rx_work_करोne = (likely(fp->type & QEDE_FASTPATH_RX) &&
			qede_has_rx_work(fp->rxq)) ?
			qede_rx_पूर्णांक(fp, budget) : 0;
	/* Handle हाल where we are called by netpoll with a budget of 0 */
	अगर (rx_work_करोne < budget || !budget) अणु
		अगर (!qede_poll_is_more_work(fp)) अणु
			napi_complete_करोne(napi, rx_work_करोne);

			/* Update and reenable पूर्णांकerrupts */
			qed_sb_ack(fp->sb_info, IGU_INT_ENABLE, 1);
		पूर्ण अन्यथा अणु
			rx_work_करोne = budget;
		पूर्ण
	पूर्ण

	अगर (fp->xdp_xmit & QEDE_XDP_TX) अणु
		xdp_prod = qed_chain_get_prod_idx(&fp->xdp_tx->tx_pbl);

		fp->xdp_tx->tx_db.data.bd_prod = cpu_to_le16(xdp_prod);
		qede_update_tx_producer(fp->xdp_tx);
	पूर्ण

	अगर (fp->xdp_xmit & QEDE_XDP_REसूचीECT)
		xdp_करो_flush_map();

	वापस rx_work_करोne;
पूर्ण

irqवापस_t qede_msix_fp_पूर्णांक(पूर्णांक irq, व्योम *fp_cookie)
अणु
	काष्ठा qede_fastpath *fp = fp_cookie;

	qed_sb_ack(fp->sb_info, IGU_INT_DISABLE, 0 /*करो not update*/);

	napi_schedule_irqoff(&fp->napi);
	वापस IRQ_HANDLED;
पूर्ण

/* Main transmit function */
netdev_tx_t qede_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(ndev);
	काष्ठा netdev_queue *netdev_txq;
	काष्ठा qede_tx_queue *txq;
	काष्ठा eth_tx_1st_bd *first_bd;
	काष्ठा eth_tx_2nd_bd *second_bd = शून्य;
	काष्ठा eth_tx_3rd_bd *third_bd = शून्य;
	काष्ठा eth_tx_bd *tx_data_bd = शून्य;
	u16 txq_index, val = 0;
	u8 nbd = 0;
	dma_addr_t mapping;
	पूर्णांक rc, frag_idx = 0, ipv6_ext = 0;
	u8 xmit_type;
	u16 idx;
	u16 hlen;
	bool data_split = false;

	/* Get tx-queue context and netdev index */
	txq_index = skb_get_queue_mapping(skb);
	WARN_ON(txq_index >= QEDE_TSS_COUNT(edev) * edev->dev_info.num_tc);
	txq = QEDE_NDEV_TXQ_ID_TO_TXQ(edev, txq_index);
	netdev_txq = netdev_get_tx_queue(ndev, txq_index);

	WARN_ON(qed_chain_get_elem_left(&txq->tx_pbl) < (MAX_SKB_FRAGS + 1));

	xmit_type = qede_xmit_type(skb, &ipv6_ext);

#अगर ((MAX_SKB_FRAGS + 2) > ETH_TX_MAX_BDS_PER_NON_LSO_PACKET)
	अगर (qede_pkt_req_lin(skb, xmit_type)) अणु
		अगर (skb_linearize(skb)) अणु
			txq->tx_mem_alloc_err++;

			dev_kमुक्त_skb_any(skb);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण
#पूर्ण_अगर

	/* Fill the entry in the SW ring and the BDs in the FW ring */
	idx = txq->sw_tx_prod;
	txq->sw_tx_ring.skbs[idx].skb = skb;
	first_bd = (काष्ठा eth_tx_1st_bd *)
		   qed_chain_produce(&txq->tx_pbl);
	स_रखो(first_bd, 0, माप(*first_bd));
	first_bd->data.bd_flags.bitfields =
		1 << ETH_TX_1ST_BD_FLAGS_START_BD_SHIFT;

	अगर (unlikely(skb_shinfo(skb)->tx_flags & SKBTX_HW_TSTAMP))
		qede_ptp_tx_ts(edev, skb);

	/* Map skb linear data क्रम DMA and set in the first BD */
	mapping = dma_map_single(txq->dev, skb->data,
				 skb_headlen(skb), DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(txq->dev, mapping))) अणु
		DP_NOTICE(edev, "SKB mapping failed\n");
		qede_मुक्त_failed_tx_pkt(txq, first_bd, 0, false);
		qede_update_tx_producer(txq);
		वापस NETDEV_TX_OK;
	पूर्ण
	nbd++;
	BD_SET_UNMAP_ADDR_LEN(first_bd, mapping, skb_headlen(skb));

	/* In हाल there is IPv6 with extension headers or LSO we need 2nd and
	 * 3rd BDs.
	 */
	अगर (unlikely((xmit_type & XMIT_LSO) | ipv6_ext)) अणु
		second_bd = (काष्ठा eth_tx_2nd_bd *)
			qed_chain_produce(&txq->tx_pbl);
		स_रखो(second_bd, 0, माप(*second_bd));

		nbd++;
		third_bd = (काष्ठा eth_tx_3rd_bd *)
			qed_chain_produce(&txq->tx_pbl);
		स_रखो(third_bd, 0, माप(*third_bd));

		nbd++;
		/* We need to fill in additional data in second_bd... */
		tx_data_bd = (काष्ठा eth_tx_bd *)second_bd;
	पूर्ण

	अगर (skb_vlan_tag_present(skb)) अणु
		first_bd->data.vlan = cpu_to_le16(skb_vlan_tag_get(skb));
		first_bd->data.bd_flags.bitfields |=
			1 << ETH_TX_1ST_BD_FLAGS_VLAN_INSERTION_SHIFT;
	पूर्ण

	/* Fill the parsing flags & params according to the requested offload */
	अगर (xmit_type & XMIT_L4_CSUM) अणु
		/* We करोn't re-calculate IP checksum as it is alपढ़ोy करोne by
		 * the upper stack
		 */
		first_bd->data.bd_flags.bitfields |=
			1 << ETH_TX_1ST_BD_FLAGS_L4_CSUM_SHIFT;

		अगर (xmit_type & XMIT_ENC) अणु
			first_bd->data.bd_flags.bitfields |=
				1 << ETH_TX_1ST_BD_FLAGS_IP_CSUM_SHIFT;

			val |= (1 << ETH_TX_DATA_1ST_BD_TUNN_FLAG_SHIFT);
		पूर्ण

		/* Legacy FW had flipped behavior in regard to this bit -
		 * I.e., needed to set to prevent FW from touching encapsulated
		 * packets when it didn't need to.
		 */
		अगर (unlikely(txq->is_legacy))
			val ^= (1 << ETH_TX_DATA_1ST_BD_TUNN_FLAG_SHIFT);

		/* If the packet is IPv6 with extension header, indicate that
		 * to FW and pass few params, since the device cracker करोesn't
		 * support parsing IPv6 with extension header/s.
		 */
		अगर (unlikely(ipv6_ext))
			qede_set_params_क्रम_ipv6_ext(skb, second_bd, third_bd);
	पूर्ण

	अगर (xmit_type & XMIT_LSO) अणु
		first_bd->data.bd_flags.bitfields |=
			(1 << ETH_TX_1ST_BD_FLAGS_LSO_SHIFT);
		third_bd->data.lso_mss =
			cpu_to_le16(skb_shinfo(skb)->gso_size);

		अगर (unlikely(xmit_type & XMIT_ENC)) अणु
			first_bd->data.bd_flags.bitfields |=
				1 << ETH_TX_1ST_BD_FLAGS_TUNN_IP_CSUM_SHIFT;

			अगर (xmit_type & XMIT_ENC_GSO_L4_CSUM) अणु
				u8 पंचांगp = ETH_TX_1ST_BD_FLAGS_TUNN_L4_CSUM_SHIFT;

				first_bd->data.bd_flags.bitfields |= 1 << पंचांगp;
			पूर्ण
			hlen = qede_get_skb_hlen(skb, true);
		पूर्ण अन्यथा अणु
			first_bd->data.bd_flags.bitfields |=
				1 << ETH_TX_1ST_BD_FLAGS_IP_CSUM_SHIFT;
			hlen = qede_get_skb_hlen(skb, false);
		पूर्ण

		/* @@@TBD - अगर will not be हटाओd need to check */
		third_bd->data.bitfields |=
			cpu_to_le16(1 << ETH_TX_DATA_3RD_BD_HDR_NBD_SHIFT);

		/* Make lअगरe easier क्रम FW guys who can't deal with header and
		 * data on same BD. If we need to split, use the second bd...
		 */
		अगर (unlikely(skb_headlen(skb) > hlen)) अणु
			DP_VERBOSE(edev, NETIF_MSG_TX_QUEUED,
				   "TSO split header size is %d (%x:%x)\n",
				   first_bd->nbytes, first_bd->addr.hi,
				   first_bd->addr.lo);

			mapping = HILO_U64(le32_to_cpu(first_bd->addr.hi),
					   le32_to_cpu(first_bd->addr.lo)) +
					   hlen;

			BD_SET_UNMAP_ADDR_LEN(tx_data_bd, mapping,
					      le16_to_cpu(first_bd->nbytes) -
					      hlen);

			/* this marks the BD as one that has no
			 * inभागidual mapping
			 */
			txq->sw_tx_ring.skbs[idx].flags |= QEDE_TSO_SPLIT_BD;

			first_bd->nbytes = cpu_to_le16(hlen);

			tx_data_bd = (काष्ठा eth_tx_bd *)third_bd;
			data_split = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		val |= ((skb->len & ETH_TX_DATA_1ST_BD_PKT_LEN_MASK) <<
			 ETH_TX_DATA_1ST_BD_PKT_LEN_SHIFT);
	पूर्ण

	first_bd->data.bitfields = cpu_to_le16(val);

	/* Handle fragmented skb */
	/* special handle क्रम frags inside 2nd and 3rd bds.. */
	जबतक (tx_data_bd && frag_idx < skb_shinfo(skb)->nr_frags) अणु
		rc = map_frag_to_bd(txq,
				    &skb_shinfo(skb)->frags[frag_idx],
				    tx_data_bd);
		अगर (rc) अणु
			qede_मुक्त_failed_tx_pkt(txq, first_bd, nbd, data_split);
			qede_update_tx_producer(txq);
			वापस NETDEV_TX_OK;
		पूर्ण

		अगर (tx_data_bd == (काष्ठा eth_tx_bd *)second_bd)
			tx_data_bd = (काष्ठा eth_tx_bd *)third_bd;
		अन्यथा
			tx_data_bd = शून्य;

		frag_idx++;
	पूर्ण

	/* map last frags पूर्णांकo 4th, 5th .... */
	क्रम (; frag_idx < skb_shinfo(skb)->nr_frags; frag_idx++, nbd++) अणु
		tx_data_bd = (काष्ठा eth_tx_bd *)
			     qed_chain_produce(&txq->tx_pbl);

		स_रखो(tx_data_bd, 0, माप(*tx_data_bd));

		rc = map_frag_to_bd(txq,
				    &skb_shinfo(skb)->frags[frag_idx],
				    tx_data_bd);
		अगर (rc) अणु
			qede_मुक्त_failed_tx_pkt(txq, first_bd, nbd, data_split);
			qede_update_tx_producer(txq);
			वापस NETDEV_TX_OK;
		पूर्ण
	पूर्ण

	/* update the first BD with the actual num BDs */
	first_bd->data.nbds = nbd;

	netdev_tx_sent_queue(netdev_txq, skb->len);

	skb_tx_बारtamp(skb);

	/* Advance packet producer only beक्रमe sending the packet since mapping
	 * of pages may fail.
	 */
	txq->sw_tx_prod = (txq->sw_tx_prod + 1) % txq->num_tx_buffers;

	/* 'next page' entries are counted in the producer value */
	txq->tx_db.data.bd_prod =
		cpu_to_le16(qed_chain_get_prod_idx(&txq->tx_pbl));

	अगर (!netdev_xmit_more() || netअगर_xmit_stopped(netdev_txq))
		qede_update_tx_producer(txq);

	अगर (unlikely(qed_chain_get_elem_left(&txq->tx_pbl)
		      < (MAX_SKB_FRAGS + 1))) अणु
		अगर (netdev_xmit_more())
			qede_update_tx_producer(txq);

		netअगर_tx_stop_queue(netdev_txq);
		txq->stopped_cnt++;
		DP_VERBOSE(edev, NETIF_MSG_TX_QUEUED,
			   "Stop queue was called\n");
		/* paired memory barrier is in qede_tx_पूर्णांक(), we have to keep
		 * ordering of set_bit() in netअगर_tx_stop_queue() and पढ़ो of
		 * fp->bd_tx_cons
		 */
		smp_mb();

		अगर ((qed_chain_get_elem_left(&txq->tx_pbl) >=
		     (MAX_SKB_FRAGS + 1)) &&
		    (edev->state == QEDE_STATE_OPEN)) अणु
			netअगर_tx_wake_queue(netdev_txq);
			DP_VERBOSE(edev, NETIF_MSG_TX_QUEUED,
				   "Wake queue was called\n");
		पूर्ण
	पूर्ण

	वापस NETDEV_TX_OK;
पूर्ण

u16 qede_select_queue(काष्ठा net_device *dev, काष्ठा sk_buff *skb,
		      काष्ठा net_device *sb_dev)
अणु
	काष्ठा qede_dev *edev = netdev_priv(dev);
	पूर्णांक total_txq;

	total_txq = QEDE_TSS_COUNT(edev) * edev->dev_info.num_tc;

	वापस QEDE_TSS_COUNT(edev) ?
		netdev_pick_tx(dev, skb, शून्य) % total_txq :  0;
पूर्ण

/* 8B udp header + 8B base tunnel header + 32B option length */
#घोषणा QEDE_MAX_TUN_HDR_LEN 48

netdev_features_t qede_features_check(काष्ठा sk_buff *skb,
				      काष्ठा net_device *dev,
				      netdev_features_t features)
अणु
	अगर (skb->encapsulation) अणु
		u8 l4_proto = 0;

		चयन (vlan_get_protocol(skb)) अणु
		हाल htons(ETH_P_IP):
			l4_proto = ip_hdr(skb)->protocol;
			अवरोध;
		हाल htons(ETH_P_IPV6):
			l4_proto = ipv6_hdr(skb)->nexthdr;
			अवरोध;
		शेष:
			वापस features;
		पूर्ण

		/* Disable offloads क्रम geneve tunnels, as HW can't parse
		 * the geneve header which has option length greater than 32b
		 * and disable offloads क्रम the ports which are not offloaded.
		 */
		अगर (l4_proto == IPPROTO_UDP) अणु
			काष्ठा qede_dev *edev = netdev_priv(dev);
			u16 hdrlen, vxln_port, gnv_port;

			hdrlen = QEDE_MAX_TUN_HDR_LEN;
			vxln_port = edev->vxlan_dst_port;
			gnv_port = edev->geneve_dst_port;

			अगर ((skb_inner_mac_header(skb) -
			     skb_transport_header(skb)) > hdrlen ||
			     (ntohs(udp_hdr(skb)->dest) != vxln_port &&
			      ntohs(udp_hdr(skb)->dest) != gnv_port))
				वापस features & ~(NETIF_F_CSUM_MASK |
						    NETIF_F_GSO_MASK);
		पूर्ण अन्यथा अगर (l4_proto == IPPROTO_IPIP) अणु
			/* IPIP tunnels are unknown to the device or at least unsupported natively,
			 * offloads क्रम them can't be करोne trivially, so disable them क्रम such skb.
			 */
			वापस features & ~(NETIF_F_CSUM_MASK | NETIF_F_GSO_MASK);
		पूर्ण
	पूर्ण

	वापस features;
पूर्ण
