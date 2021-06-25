<शैली गुरु>
/* Synopsys DesignWare Core Enterprise Ethernet (XLGMAC) Driver
 *
 * Copyright (c) 2017 Synopsys, Inc. (www.synopsys.com)
 *
 * This program is dual-licensed; you may select either version 2 of
 * the GNU General Public License ("GPL") or BSD license ("BSD").
 *
 * This Synopsys DWC XLGMAC software driver and associated करोcumentation
 * (hereinafter the "Software") is an unsupported proprietary work of
 * Synopsys, Inc. unless otherwise expressly agreed to in writing between
 * Synopsys and you. The Software IS NOT an item of Licensed Software or a
 * Licensed Product under any End User Software License Agreement or
 * Agreement क्रम Licensed Products with Synopsys or any supplement thereto.
 * Synopsys is a रेजिस्टरed trademark of Synopsys, Inc. Other names included
 * in the SOFTWARE may be the trademarks of their respective owners.
 */

#समावेश <linux/netdevice.h>
#समावेश <linux/tcp.h>
#समावेश <linux/पूर्णांकerrupt.h>

#समावेश "dwc-xlgmac.h"
#समावेश "dwc-xlgmac-reg.h"

अटल पूर्णांक xlgmac_one_poll(काष्ठा napi_काष्ठा *, पूर्णांक);
अटल पूर्णांक xlgmac_all_poll(काष्ठा napi_काष्ठा *, पूर्णांक);

अटल अंतरभूत अचिन्हित पूर्णांक xlgmac_tx_avail_desc(काष्ठा xlgmac_ring *ring)
अणु
	वापस (ring->dma_desc_count - (ring->cur - ring->dirty));
पूर्ण

अटल अंतरभूत अचिन्हित पूर्णांक xlgmac_rx_dirty_desc(काष्ठा xlgmac_ring *ring)
अणु
	वापस (ring->cur - ring->dirty);
पूर्ण

अटल पूर्णांक xlgmac_maybe_stop_tx_queue(
			काष्ठा xlgmac_channel *channel,
			काष्ठा xlgmac_ring *ring,
			अचिन्हित पूर्णांक count)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;

	अगर (count > xlgmac_tx_avail_desc(ring)) अणु
		netअगर_info(pdata, drv, pdata->netdev,
			   "Tx queue stopped, not enough descriptors available\n");
		netअगर_stop_subqueue(pdata->netdev, channel->queue_index);
		ring->tx.queue_stopped = 1;

		/* If we haven't notअगरied the hardware because of xmit_more
		 * support, tell it now
		 */
		अगर (ring->tx.xmit_more)
			pdata->hw_ops.tx_start_xmit(channel, ring);

		वापस NETDEV_TX_BUSY;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम xlgmac_prep_vlan(काष्ठा sk_buff *skb,
			     काष्ठा xlgmac_pkt_info *pkt_info)
अणु
	अगर (skb_vlan_tag_present(skb))
		pkt_info->vlan_ctag = skb_vlan_tag_get(skb);
पूर्ण

अटल पूर्णांक xlgmac_prep_tso(काष्ठा sk_buff *skb,
			   काष्ठा xlgmac_pkt_info *pkt_info)
अणु
	पूर्णांक ret;

	अगर (!XLGMAC_GET_REG_BITS(pkt_info->attributes,
				 TX_PACKET_ATTRIBUTES_TSO_ENABLE_POS,
				 TX_PACKET_ATTRIBUTES_TSO_ENABLE_LEN))
		वापस 0;

	ret = skb_cow_head(skb, 0);
	अगर (ret)
		वापस ret;

	pkt_info->header_len = skb_transport_offset(skb) + tcp_hdrlen(skb);
	pkt_info->tcp_header_len = tcp_hdrlen(skb);
	pkt_info->tcp_payload_len = skb->len - pkt_info->header_len;
	pkt_info->mss = skb_shinfo(skb)->gso_size;

	XLGMAC_PR("header_len=%u\n", pkt_info->header_len);
	XLGMAC_PR("tcp_header_len=%u, tcp_payload_len=%u\n",
		  pkt_info->tcp_header_len, pkt_info->tcp_payload_len);
	XLGMAC_PR("mss=%u\n", pkt_info->mss);

	/* Update the number of packets that will ultimately be transmitted
	 * aदीर्घ with the extra bytes क्रम each extra packet
	 */
	pkt_info->tx_packets = skb_shinfo(skb)->gso_segs;
	pkt_info->tx_bytes += (pkt_info->tx_packets - 1) * pkt_info->header_len;

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_is_tso(काष्ठा sk_buff *skb)
अणु
	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	वापस 1;
पूर्ण

अटल व्योम xlgmac_prep_tx_pkt(काष्ठा xlgmac_pdata *pdata,
			       काष्ठा xlgmac_ring *ring,
			       काष्ठा sk_buff *skb,
			       काष्ठा xlgmac_pkt_info *pkt_info)
अणु
	skb_frag_t *frag;
	अचिन्हित पूर्णांक context_desc;
	अचिन्हित पूर्णांक len;
	अचिन्हित पूर्णांक i;

	pkt_info->skb = skb;

	context_desc = 0;
	pkt_info->desc_count = 0;

	pkt_info->tx_packets = 1;
	pkt_info->tx_bytes = skb->len;

	अगर (xlgmac_is_tso(skb)) अणु
		/* TSO requires an extra descriptor अगर mss is dअगरferent */
		अगर (skb_shinfo(skb)->gso_size != ring->tx.cur_mss) अणु
			context_desc = 1;
			pkt_info->desc_count++;
		पूर्ण

		/* TSO requires an extra descriptor क्रम TSO header */
		pkt_info->desc_count++;

		pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					TX_PACKET_ATTRIBUTES_TSO_ENABLE_POS,
					TX_PACKET_ATTRIBUTES_TSO_ENABLE_LEN,
					1);
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					TX_PACKET_ATTRIBUTES_CSUM_ENABLE_POS,
					TX_PACKET_ATTRIBUTES_CSUM_ENABLE_LEN,
					1);
	पूर्ण अन्यथा अगर (skb->ip_summed == CHECKSUM_PARTIAL)
		pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					TX_PACKET_ATTRIBUTES_CSUM_ENABLE_POS,
					TX_PACKET_ATTRIBUTES_CSUM_ENABLE_LEN,
					1);

	अगर (skb_vlan_tag_present(skb)) अणु
		/* VLAN requires an extra descriptor अगर tag is dअगरferent */
		अगर (skb_vlan_tag_get(skb) != ring->tx.cur_vlan_ctag)
			/* We can share with the TSO context descriptor */
			अगर (!context_desc) अणु
				context_desc = 1;
				pkt_info->desc_count++;
			पूर्ण

		pkt_info->attributes = XLGMAC_SET_REG_BITS(
					pkt_info->attributes,
					TX_PACKET_ATTRIBUTES_VLAN_CTAG_POS,
					TX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN,
					1);
	पूर्ण

	क्रम (len = skb_headlen(skb); len;) अणु
		pkt_info->desc_count++;
		len -= min_t(अचिन्हित पूर्णांक, len, XLGMAC_TX_MAX_BUF_SIZE);
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		frag = &skb_shinfo(skb)->frags[i];
		क्रम (len = skb_frag_size(frag); len; ) अणु
			pkt_info->desc_count++;
			len -= min_t(अचिन्हित पूर्णांक, len, XLGMAC_TX_MAX_BUF_SIZE);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_calc_rx_buf_size(काष्ठा net_device *netdev, अचिन्हित पूर्णांक mtu)
अणु
	अचिन्हित पूर्णांक rx_buf_size;

	अगर (mtu > XLGMAC_JUMBO_PACKET_MTU) अणु
		netdev_alert(netdev, "MTU exceeds maximum supported value\n");
		वापस -EINVAL;
	पूर्ण

	rx_buf_size = mtu + ETH_HLEN + ETH_FCS_LEN + VLAN_HLEN;
	rx_buf_size = clamp_val(rx_buf_size, XLGMAC_RX_MIN_BUF_SIZE, PAGE_SIZE);

	rx_buf_size = (rx_buf_size + XLGMAC_RX_BUF_ALIGN - 1) &
		      ~(XLGMAC_RX_BUF_ALIGN - 1);

	वापस rx_buf_size;
पूर्ण

अटल व्योम xlgmac_enable_rx_tx_पूर्णांकs(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	काष्ठा xlgmac_channel *channel;
	क्रमागत xlgmac_पूर्णांक पूर्णांक_id;
	अचिन्हित पूर्णांक i;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (channel->tx_ring && channel->rx_ring)
			पूर्णांक_id = XLGMAC_INT_DMA_CH_SR_TI_RI;
		अन्यथा अगर (channel->tx_ring)
			पूर्णांक_id = XLGMAC_INT_DMA_CH_SR_TI;
		अन्यथा अगर (channel->rx_ring)
			पूर्णांक_id = XLGMAC_INT_DMA_CH_SR_RI;
		अन्यथा
			जारी;

		hw_ops->enable_पूर्णांक(channel, पूर्णांक_id);
	पूर्ण
पूर्ण

अटल व्योम xlgmac_disable_rx_tx_पूर्णांकs(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	काष्ठा xlgmac_channel *channel;
	क्रमागत xlgmac_पूर्णांक पूर्णांक_id;
	अचिन्हित पूर्णांक i;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (channel->tx_ring && channel->rx_ring)
			पूर्णांक_id = XLGMAC_INT_DMA_CH_SR_TI_RI;
		अन्यथा अगर (channel->tx_ring)
			पूर्णांक_id = XLGMAC_INT_DMA_CH_SR_TI;
		अन्यथा अगर (channel->rx_ring)
			पूर्णांक_id = XLGMAC_INT_DMA_CH_SR_RI;
		अन्यथा
			जारी;

		hw_ops->disable_पूर्णांक(channel, पूर्णांक_id);
	पूर्ण
पूर्ण

अटल irqवापस_t xlgmac_isr(पूर्णांक irq, व्योम *data)
अणु
	अचिन्हित पूर्णांक dma_isr, dma_ch_isr, mac_isr;
	काष्ठा xlgmac_pdata *pdata = data;
	काष्ठा xlgmac_channel *channel;
	काष्ठा xlgmac_hw_ops *hw_ops;
	अचिन्हित पूर्णांक i, ti, ri;

	hw_ops = &pdata->hw_ops;

	/* The DMA पूर्णांकerrupt status रेजिस्टर also reports MAC and MTL
	 * पूर्णांकerrupts. So क्रम polling mode, we just need to check क्रम
	 * this रेजिस्टर to be non-zero
	 */
	dma_isr = पढ़ोl(pdata->mac_regs + DMA_ISR);
	अगर (!dma_isr)
		वापस IRQ_HANDLED;

	netअगर_dbg(pdata, पूर्णांकr, pdata->netdev, "DMA_ISR=%#010x\n", dma_isr);

	क्रम (i = 0; i < pdata->channel_count; i++) अणु
		अगर (!(dma_isr & (1 << i)))
			जारी;

		channel = pdata->channel_head + i;

		dma_ch_isr = पढ़ोl(XLGMAC_DMA_REG(channel, DMA_CH_SR));
		netअगर_dbg(pdata, पूर्णांकr, pdata->netdev, "DMA_CH%u_ISR=%#010x\n",
			  i, dma_ch_isr);

		/* The TI or RI पूर्णांकerrupt bits may still be set even अगर using
		 * per channel DMA पूर्णांकerrupts. Check to be sure those are not
		 * enabled beक्रमe using the निजी data napi काष्ठाure.
		 */
		ti = XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_TI_POS,
					 DMA_CH_SR_TI_LEN);
		ri = XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_RI_POS,
					 DMA_CH_SR_RI_LEN);
		अगर (!pdata->per_channel_irq && (ti || ri)) अणु
			अगर (napi_schedule_prep(&pdata->napi)) अणु
				/* Disable Tx and Rx पूर्णांकerrupts */
				xlgmac_disable_rx_tx_पूर्णांकs(pdata);

				pdata->stats.napi_poll_isr++;
				/* Turn on polling */
				__napi_schedule_irqoff(&pdata->napi);
			पूर्ण
		पूर्ण

		अगर (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_TPS_POS,
					DMA_CH_SR_TPS_LEN))
			pdata->stats.tx_process_stopped++;

		अगर (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_RPS_POS,
					DMA_CH_SR_RPS_LEN))
			pdata->stats.rx_process_stopped++;

		अगर (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_TBU_POS,
					DMA_CH_SR_TBU_LEN))
			pdata->stats.tx_buffer_unavailable++;

		अगर (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_RBU_POS,
					DMA_CH_SR_RBU_LEN))
			pdata->stats.rx_buffer_unavailable++;

		/* Restart the device on a Fatal Bus Error */
		अगर (XLGMAC_GET_REG_BITS(dma_ch_isr, DMA_CH_SR_FBE_POS,
					DMA_CH_SR_FBE_LEN)) अणु
			pdata->stats.fatal_bus_error++;
			schedule_work(&pdata->restart_work);
		पूर्ण

		/* Clear all पूर्णांकerrupt संकेतs */
		ग_लिखोl(dma_ch_isr, XLGMAC_DMA_REG(channel, DMA_CH_SR));
	पूर्ण

	अगर (XLGMAC_GET_REG_BITS(dma_isr, DMA_ISR_MACIS_POS,
				DMA_ISR_MACIS_LEN)) अणु
		mac_isr = पढ़ोl(pdata->mac_regs + MAC_ISR);

		अगर (XLGMAC_GET_REG_BITS(mac_isr, MAC_ISR_MMCTXIS_POS,
					MAC_ISR_MMCTXIS_LEN))
			hw_ops->tx_mmc_पूर्णांक(pdata);

		अगर (XLGMAC_GET_REG_BITS(mac_isr, MAC_ISR_MMCRXIS_POS,
					MAC_ISR_MMCRXIS_LEN))
			hw_ops->rx_mmc_पूर्णांक(pdata);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल irqवापस_t xlgmac_dma_isr(पूर्णांक irq, व्योम *data)
अणु
	काष्ठा xlgmac_channel *channel = data;

	/* Per channel DMA पूर्णांकerrupts are enabled, so we use the per
	 * channel napi काष्ठाure and not the निजी data napi काष्ठाure
	 */
	अगर (napi_schedule_prep(&channel->napi)) अणु
		/* Disable Tx and Rx पूर्णांकerrupts */
		disable_irq_nosync(channel->dma_irq);

		/* Turn on polling */
		__napi_schedule_irqoff(&channel->napi);
	पूर्ण

	वापस IRQ_HANDLED;
पूर्ण

अटल व्योम xlgmac_tx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा xlgmac_channel *channel = from_समयr(channel, t, tx_समयr);
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा napi_काष्ठा *napi;

	napi = (pdata->per_channel_irq) ? &channel->napi : &pdata->napi;

	अगर (napi_schedule_prep(napi)) अणु
		/* Disable Tx and Rx पूर्णांकerrupts */
		अगर (pdata->per_channel_irq)
			disable_irq_nosync(channel->dma_irq);
		अन्यथा
			xlgmac_disable_rx_tx_पूर्णांकs(pdata);

		pdata->stats.napi_poll_txसमयr++;
		/* Turn on polling */
		__napi_schedule(napi);
	पूर्ण

	channel->tx_समयr_active = 0;
पूर्ण

अटल व्योम xlgmac_init_समयrs(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			अवरोध;

		समयr_setup(&channel->tx_समयr, xlgmac_tx_समयr, 0);
	पूर्ण
पूर्ण

अटल व्योम xlgmac_stop_समयrs(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			अवरोध;

		del_समयr_sync(&channel->tx_समयr);
	पूर्ण
पूर्ण

अटल व्योम xlgmac_napi_enable(काष्ठा xlgmac_pdata *pdata, अचिन्हित पूर्णांक add)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;

	अगर (pdata->per_channel_irq) अणु
		channel = pdata->channel_head;
		क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
			अगर (add)
				netअगर_napi_add(pdata->netdev, &channel->napi,
					       xlgmac_one_poll,
					       NAPI_POLL_WEIGHT);

			napi_enable(&channel->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (add)
			netअगर_napi_add(pdata->netdev, &pdata->napi,
				       xlgmac_all_poll, NAPI_POLL_WEIGHT);

		napi_enable(&pdata->napi);
	पूर्ण
पूर्ण

अटल व्योम xlgmac_napi_disable(काष्ठा xlgmac_pdata *pdata, अचिन्हित पूर्णांक del)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;

	अगर (pdata->per_channel_irq) अणु
		channel = pdata->channel_head;
		क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
			napi_disable(&channel->napi);

			अगर (del)
				netअगर_napi_del(&channel->napi);
		पूर्ण
	पूर्ण अन्यथा अणु
		napi_disable(&pdata->napi);

		अगर (del)
			netअगर_napi_del(&pdata->napi);
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_request_irqs(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	ret = devm_request_irq(pdata->dev, pdata->dev_irq, xlgmac_isr,
			       IRQF_SHARED, netdev->name, pdata);
	अगर (ret) अणु
		netdev_alert(netdev, "error requesting irq %d\n",
			     pdata->dev_irq);
		वापस ret;
	पूर्ण

	अगर (!pdata->per_channel_irq)
		वापस 0;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		snम_लिखो(channel->dma_irq_name,
			 माप(channel->dma_irq_name) - 1,
			 "%s-TxRx-%u", netdev_name(netdev),
			 channel->queue_index);

		ret = devm_request_irq(pdata->dev, channel->dma_irq,
				       xlgmac_dma_isr, 0,
				       channel->dma_irq_name, channel);
		अगर (ret) अणु
			netdev_alert(netdev, "error requesting irq %d\n",
				     channel->dma_irq);
			जाओ err_irq;
		पूर्ण
	पूर्ण

	वापस 0;

err_irq:
	/* Using an अचिन्हित पूर्णांक, 'i' will go to अच_पूर्णांक_उच्च and निकास */
	क्रम (i--, channel--; i < pdata->channel_count; i--, channel--)
		devm_मुक्त_irq(pdata->dev, channel->dma_irq, channel);

	devm_मुक्त_irq(pdata->dev, pdata->dev_irq, pdata);

	वापस ret;
पूर्ण

अटल व्योम xlgmac_मुक्त_irqs(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;

	devm_मुक्त_irq(pdata->dev, pdata->dev_irq, pdata);

	अगर (!pdata->per_channel_irq)
		वापस;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++)
		devm_मुक्त_irq(pdata->dev, channel->dma_irq, channel);
पूर्ण

अटल व्योम xlgmac_मुक्त_tx_data(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_desc_ops *desc_ops = &pdata->desc_ops;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_channel *channel;
	काष्ठा xlgmac_ring *ring;
	अचिन्हित पूर्णांक i, j;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		ring = channel->tx_ring;
		अगर (!ring)
			अवरोध;

		क्रम (j = 0; j < ring->dma_desc_count; j++) अणु
			desc_data = XLGMAC_GET_DESC_DATA(ring, j);
			desc_ops->unmap_desc_data(pdata, desc_data);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम xlgmac_मुक्त_rx_data(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_desc_ops *desc_ops = &pdata->desc_ops;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_channel *channel;
	काष्ठा xlgmac_ring *ring;
	अचिन्हित पूर्णांक i, j;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		ring = channel->rx_ring;
		अगर (!ring)
			अवरोध;

		क्रम (j = 0; j < ring->dma_desc_count; j++) अणु
			desc_data = XLGMAC_GET_DESC_DATA(ring, j);
			desc_ops->unmap_desc_data(pdata, desc_data);
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_start(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	काष्ठा net_device *netdev = pdata->netdev;
	पूर्णांक ret;

	hw_ops->init(pdata);
	xlgmac_napi_enable(pdata, 1);

	ret = xlgmac_request_irqs(pdata);
	अगर (ret)
		जाओ err_napi;

	hw_ops->enable_tx(pdata);
	hw_ops->enable_rx(pdata);
	netअगर_tx_start_all_queues(netdev);

	वापस 0;

err_napi:
	xlgmac_napi_disable(pdata, 1);
	hw_ops->निकास(pdata);

	वापस ret;
पूर्ण

अटल व्योम xlgmac_stop(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	काष्ठा net_device *netdev = pdata->netdev;
	काष्ठा xlgmac_channel *channel;
	काष्ठा netdev_queue *txq;
	अचिन्हित पूर्णांक i;

	netअगर_tx_stop_all_queues(netdev);
	xlgmac_stop_समयrs(pdata);
	hw_ops->disable_tx(pdata);
	hw_ops->disable_rx(pdata);
	xlgmac_मुक्त_irqs(pdata);
	xlgmac_napi_disable(pdata, 1);
	hw_ops->निकास(pdata);

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		अगर (!channel->tx_ring)
			जारी;

		txq = netdev_get_tx_queue(netdev, channel->queue_index);
		netdev_tx_reset_queue(txq);
	पूर्ण
पूर्ण

अटल व्योम xlgmac_restart_dev(काष्ठा xlgmac_pdata *pdata)
अणु
	/* If not running, "restart" will happen on खोलो */
	अगर (!netअगर_running(pdata->netdev))
		वापस;

	xlgmac_stop(pdata);

	xlgmac_मुक्त_tx_data(pdata);
	xlgmac_मुक्त_rx_data(pdata);

	xlgmac_start(pdata);
पूर्ण

अटल व्योम xlgmac_restart(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा xlgmac_pdata *pdata = container_of(work,
						   काष्ठा xlgmac_pdata,
						   restart_work);

	rtnl_lock();

	xlgmac_restart_dev(pdata);

	rtnl_unlock();
पूर्ण

अटल पूर्णांक xlgmac_खोलो(काष्ठा net_device *netdev)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_desc_ops *desc_ops;
	पूर्णांक ret;

	desc_ops = &pdata->desc_ops;

	/* TODO: Initialize the phy */

	/* Calculate the Rx buffer size beक्रमe allocating rings */
	ret = xlgmac_calc_rx_buf_size(netdev, netdev->mtu);
	अगर (ret < 0)
		वापस ret;
	pdata->rx_buf_size = ret;

	/* Allocate the channels and rings */
	ret = desc_ops->alloc_channels_and_rings(pdata);
	अगर (ret)
		वापस ret;

	INIT_WORK(&pdata->restart_work, xlgmac_restart);
	xlgmac_init_समयrs(pdata);

	ret = xlgmac_start(pdata);
	अगर (ret)
		जाओ err_channels_and_rings;

	वापस 0;

err_channels_and_rings:
	desc_ops->मुक्त_channels_and_rings(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xlgmac_बंद(काष्ठा net_device *netdev)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_desc_ops *desc_ops;

	desc_ops = &pdata->desc_ops;

	/* Stop the device */
	xlgmac_stop(pdata);

	/* Free the channels and rings */
	desc_ops->मुक्त_channels_and_rings(pdata);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_tx_समयout(काष्ठा net_device *netdev, अचिन्हित पूर्णांक txqueue)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);

	netdev_warn(netdev, "tx timeout, device restarting\n");
	schedule_work(&pdata->restart_work);
पूर्ण

अटल netdev_tx_t xlgmac_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_pkt_info *tx_pkt_info;
	काष्ठा xlgmac_desc_ops *desc_ops;
	काष्ठा xlgmac_channel *channel;
	काष्ठा xlgmac_hw_ops *hw_ops;
	काष्ठा netdev_queue *txq;
	काष्ठा xlgmac_ring *ring;
	पूर्णांक ret;

	desc_ops = &pdata->desc_ops;
	hw_ops = &pdata->hw_ops;

	XLGMAC_PR("skb->len = %d\n", skb->len);

	channel = pdata->channel_head + skb->queue_mapping;
	txq = netdev_get_tx_queue(netdev, channel->queue_index);
	ring = channel->tx_ring;
	tx_pkt_info = &ring->pkt_info;

	अगर (skb->len == 0) अणु
		netअगर_err(pdata, tx_err, netdev,
			  "empty skb received from stack\n");
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Prepare preliminary packet info क्रम TX */
	स_रखो(tx_pkt_info, 0, माप(*tx_pkt_info));
	xlgmac_prep_tx_pkt(pdata, ring, skb, tx_pkt_info);

	/* Check that there are enough descriptors available */
	ret = xlgmac_maybe_stop_tx_queue(channel, ring,
					 tx_pkt_info->desc_count);
	अगर (ret)
		वापस ret;

	ret = xlgmac_prep_tso(skb, tx_pkt_info);
	अगर (ret) अणु
		netअगर_err(pdata, tx_err, netdev,
			  "error processing TSO packet\n");
		dev_kमुक्त_skb_any(skb);
		वापस ret;
	पूर्ण
	xlgmac_prep_vlan(skb, tx_pkt_info);

	अगर (!desc_ops->map_tx_skb(channel, skb)) अणु
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	पूर्ण

	/* Report on the actual number of bytes (to be) sent */
	netdev_tx_sent_queue(txq, tx_pkt_info->tx_bytes);

	/* Configure required descriptor fields क्रम transmission */
	hw_ops->dev_xmit(channel);

	अगर (netअगर_msg_pktdata(pdata))
		xlgmac_prपूर्णांक_pkt(netdev, skb, true);

	/* Stop the queue in advance अगर there may not be enough descriptors */
	xlgmac_maybe_stop_tx_queue(channel, ring, XLGMAC_TX_MAX_DESC_NR);

	वापस NETDEV_TX_OK;
पूर्ण

अटल व्योम xlgmac_get_stats64(काष्ठा net_device *netdev,
			       काष्ठा rtnl_link_stats64 *s)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_stats *pstats = &pdata->stats;

	pdata->hw_ops.पढ़ो_mmc_stats(pdata);

	s->rx_packets = pstats->rxframecount_gb;
	s->rx_bytes = pstats->rxoctetcount_gb;
	s->rx_errors = pstats->rxframecount_gb -
		       pstats->rxbroadcastframes_g -
		       pstats->rxmulticastframes_g -
		       pstats->rxunicastframes_g;
	s->multicast = pstats->rxmulticastframes_g;
	s->rx_length_errors = pstats->rxlengtherror;
	s->rx_crc_errors = pstats->rxcrcerror;
	s->rx_fअगरo_errors = pstats->rxfअगरooverflow;

	s->tx_packets = pstats->txframecount_gb;
	s->tx_bytes = pstats->txoctetcount_gb;
	s->tx_errors = pstats->txframecount_gb - pstats->txframecount_g;
	s->tx_dropped = netdev->stats.tx_dropped;
पूर्ण

अटल पूर्णांक xlgmac_set_mac_address(काष्ठा net_device *netdev, व्योम *addr)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	काष्ठा sockaddr *saddr = addr;

	अगर (!is_valid_ether_addr(saddr->sa_data))
		वापस -EADDRNOTAVAIL;

	स_नकल(netdev->dev_addr, saddr->sa_data, netdev->addr_len);

	hw_ops->set_mac_address(pdata, netdev->dev_addr);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_ioctl(काष्ठा net_device *netdev,
			काष्ठा अगरreq *अगरreq, पूर्णांक cmd)
अणु
	अगर (!netअगर_running(netdev))
		वापस -ENODEV;

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_change_mtu(काष्ठा net_device *netdev, पूर्णांक mtu)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	पूर्णांक ret;

	ret = xlgmac_calc_rx_buf_size(netdev, mtu);
	अगर (ret < 0)
		वापस ret;

	pdata->rx_buf_size = ret;
	netdev->mtu = mtu;

	xlgmac_restart_dev(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_vlan_rx_add_vid(काष्ठा net_device *netdev,
				  __be16 proto,
				  u16 vid)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;

	set_bit(vid, pdata->active_vlans);
	hw_ops->update_vlan_hash_table(pdata);

	वापस 0;
पूर्ण

अटल पूर्णांक xlgmac_vlan_rx_समाप्त_vid(काष्ठा net_device *netdev,
				   __be16 proto,
				   u16 vid)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;

	clear_bit(vid, pdata->active_vlans);
	hw_ops->update_vlan_hash_table(pdata);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
अटल व्योम xlgmac_poll_controller(काष्ठा net_device *netdev)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;

	अगर (pdata->per_channel_irq) अणु
		channel = pdata->channel_head;
		क्रम (i = 0; i < pdata->channel_count; i++, channel++)
			xlgmac_dma_isr(channel->dma_irq, channel);
	पूर्ण अन्यथा अणु
		disable_irq(pdata->dev_irq);
		xlgmac_isr(pdata->dev_irq, pdata);
		enable_irq(pdata->dev_irq);
	पूर्ण
पूर्ण
#पूर्ण_अगर /* CONFIG_NET_POLL_CONTROLLER */

अटल पूर्णांक xlgmac_set_features(काष्ठा net_device *netdev,
			       netdev_features_t features)
अणु
	netdev_features_t rxhash, rxcsum, rxvlan, rxvlan_filter;
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	पूर्णांक ret = 0;

	rxhash = pdata->netdev_features & NETIF_F_RXHASH;
	rxcsum = pdata->netdev_features & NETIF_F_RXCSUM;
	rxvlan = pdata->netdev_features & NETIF_F_HW_VLAN_CTAG_RX;
	rxvlan_filter = pdata->netdev_features & NETIF_F_HW_VLAN_CTAG_FILTER;

	अगर ((features & NETIF_F_RXHASH) && !rxhash)
		ret = hw_ops->enable_rss(pdata);
	अन्यथा अगर (!(features & NETIF_F_RXHASH) && rxhash)
		ret = hw_ops->disable_rss(pdata);
	अगर (ret)
		वापस ret;

	अगर ((features & NETIF_F_RXCSUM) && !rxcsum)
		hw_ops->enable_rx_csum(pdata);
	अन्यथा अगर (!(features & NETIF_F_RXCSUM) && rxcsum)
		hw_ops->disable_rx_csum(pdata);

	अगर ((features & NETIF_F_HW_VLAN_CTAG_RX) && !rxvlan)
		hw_ops->enable_rx_vlan_stripping(pdata);
	अन्यथा अगर (!(features & NETIF_F_HW_VLAN_CTAG_RX) && rxvlan)
		hw_ops->disable_rx_vlan_stripping(pdata);

	अगर ((features & NETIF_F_HW_VLAN_CTAG_FILTER) && !rxvlan_filter)
		hw_ops->enable_rx_vlan_filtering(pdata);
	अन्यथा अगर (!(features & NETIF_F_HW_VLAN_CTAG_FILTER) && rxvlan_filter)
		hw_ops->disable_rx_vlan_filtering(pdata);

	pdata->netdev_features = features;

	वापस 0;
पूर्ण

अटल व्योम xlgmac_set_rx_mode(काष्ठा net_device *netdev)
अणु
	काष्ठा xlgmac_pdata *pdata = netdev_priv(netdev);
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;

	hw_ops->config_rx_mode(pdata);
पूर्ण

अटल स्थिर काष्ठा net_device_ops xlgmac_netdev_ops = अणु
	.nकरो_खोलो		= xlgmac_खोलो,
	.nकरो_stop		= xlgmac_बंद,
	.nकरो_start_xmit		= xlgmac_xmit,
	.nकरो_tx_समयout		= xlgmac_tx_समयout,
	.nकरो_get_stats64	= xlgmac_get_stats64,
	.nकरो_change_mtu		= xlgmac_change_mtu,
	.nकरो_set_mac_address	= xlgmac_set_mac_address,
	.nकरो_validate_addr	= eth_validate_addr,
	.nकरो_करो_ioctl		= xlgmac_ioctl,
	.nकरो_vlan_rx_add_vid	= xlgmac_vlan_rx_add_vid,
	.nकरो_vlan_rx_समाप्त_vid	= xlgmac_vlan_rx_समाप्त_vid,
#अगर_घोषित CONFIG_NET_POLL_CONTROLLER
	.nकरो_poll_controller	= xlgmac_poll_controller,
#पूर्ण_अगर
	.nकरो_set_features	= xlgmac_set_features,
	.nकरो_set_rx_mode	= xlgmac_set_rx_mode,
पूर्ण;

स्थिर काष्ठा net_device_ops *xlgmac_get_netdev_ops(व्योम)
अणु
	वापस &xlgmac_netdev_ops;
पूर्ण

अटल व्योम xlgmac_rx_refresh(काष्ठा xlgmac_channel *channel)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा xlgmac_ring *ring = channel->rx_ring;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_desc_ops *desc_ops;
	काष्ठा xlgmac_hw_ops *hw_ops;

	desc_ops = &pdata->desc_ops;
	hw_ops = &pdata->hw_ops;

	जबतक (ring->dirty != ring->cur) अणु
		desc_data = XLGMAC_GET_DESC_DATA(ring, ring->dirty);

		/* Reset desc_data values */
		desc_ops->unmap_desc_data(pdata, desc_data);

		अगर (desc_ops->map_rx_buffer(pdata, ring, desc_data))
			अवरोध;

		hw_ops->rx_desc_reset(pdata, desc_data, ring->dirty);

		ring->dirty++;
	पूर्ण

	/* Make sure everything is written beक्रमe the रेजिस्टर ग_लिखो */
	wmb();

	/* Update the Rx Tail Poपूर्णांकer Register with address of
	 * the last cleaned entry
	 */
	desc_data = XLGMAC_GET_DESC_DATA(ring, ring->dirty - 1);
	ग_लिखोl(lower_32_bits(desc_data->dma_desc_addr),
	       XLGMAC_DMA_REG(channel, DMA_CH_RDTR_LO));
पूर्ण

अटल काष्ठा sk_buff *xlgmac_create_skb(काष्ठा xlgmac_pdata *pdata,
					 काष्ठा napi_काष्ठा *napi,
					 काष्ठा xlgmac_desc_data *desc_data,
					 अचिन्हित पूर्णांक len)
अणु
	अचिन्हित पूर्णांक copy_len;
	काष्ठा sk_buff *skb;
	u8 *packet;

	skb = napi_alloc_skb(napi, desc_data->rx.hdr.dma_len);
	अगर (!skb)
		वापस शून्य;

	/* Start with the header buffer which may contain just the header
	 * or the header plus data
	 */
	dma_sync_single_range_क्रम_cpu(pdata->dev, desc_data->rx.hdr.dma_base,
				      desc_data->rx.hdr.dma_off,
				      desc_data->rx.hdr.dma_len,
				      DMA_FROM_DEVICE);

	packet = page_address(desc_data->rx.hdr.pa.pages) +
		 desc_data->rx.hdr.pa.pages_offset;
	copy_len = (desc_data->rx.hdr_len) ? desc_data->rx.hdr_len : len;
	copy_len = min(desc_data->rx.hdr.dma_len, copy_len);
	skb_copy_to_linear_data(skb, packet, copy_len);
	skb_put(skb, copy_len);

	len -= copy_len;
	अगर (len) अणु
		/* Add the reमुख्यing data as a frag */
		dma_sync_single_range_क्रम_cpu(pdata->dev,
					      desc_data->rx.buf.dma_base,
					      desc_data->rx.buf.dma_off,
					      desc_data->rx.buf.dma_len,
					      DMA_FROM_DEVICE);

		skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
				desc_data->rx.buf.pa.pages,
				desc_data->rx.buf.pa.pages_offset,
				len, desc_data->rx.buf.dma_len);
		desc_data->rx.buf.pa.pages = शून्य;
	पूर्ण

	वापस skb;
पूर्ण

अटल पूर्णांक xlgmac_tx_poll(काष्ठा xlgmac_channel *channel)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा xlgmac_ring *ring = channel->tx_ring;
	काष्ठा net_device *netdev = pdata->netdev;
	अचिन्हित पूर्णांक tx_packets = 0, tx_bytes = 0;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_dma_desc *dma_desc;
	काष्ठा xlgmac_desc_ops *desc_ops;
	काष्ठा xlgmac_hw_ops *hw_ops;
	काष्ठा netdev_queue *txq;
	पूर्णांक processed = 0;
	अचिन्हित पूर्णांक cur;

	desc_ops = &pdata->desc_ops;
	hw_ops = &pdata->hw_ops;

	/* Nothing to करो अगर there isn't a Tx ring क्रम this channel */
	अगर (!ring)
		वापस 0;

	cur = ring->cur;

	/* Be sure we get ring->cur beक्रमe accessing descriptor data */
	smp_rmb();

	txq = netdev_get_tx_queue(netdev, channel->queue_index);

	जबतक ((processed < XLGMAC_TX_DESC_MAX_PROC) &&
	       (ring->dirty != cur)) अणु
		desc_data = XLGMAC_GET_DESC_DATA(ring, ring->dirty);
		dma_desc = desc_data->dma_desc;

		अगर (!hw_ops->tx_complete(dma_desc))
			अवरोध;

		/* Make sure descriptor fields are पढ़ो after पढ़ोing
		 * the OWN bit
		 */
		dma_rmb();

		अगर (netअगर_msg_tx_करोne(pdata))
			xlgmac_dump_tx_desc(pdata, ring, ring->dirty, 1, 0);

		अगर (hw_ops->is_last_desc(dma_desc)) अणु
			tx_packets += desc_data->tx.packets;
			tx_bytes += desc_data->tx.bytes;
		पूर्ण

		/* Free the SKB and reset the descriptor क्रम re-use */
		desc_ops->unmap_desc_data(pdata, desc_data);
		hw_ops->tx_desc_reset(desc_data);

		processed++;
		ring->dirty++;
	पूर्ण

	अगर (!processed)
		वापस 0;

	netdev_tx_completed_queue(txq, tx_packets, tx_bytes);

	अगर ((ring->tx.queue_stopped == 1) &&
	    (xlgmac_tx_avail_desc(ring) > XLGMAC_TX_DESC_MIN_FREE)) अणु
		ring->tx.queue_stopped = 0;
		netअगर_tx_wake_queue(txq);
	पूर्ण

	XLGMAC_PR("processed=%d\n", processed);

	वापस processed;
पूर्ण

अटल पूर्णांक xlgmac_rx_poll(काष्ठा xlgmac_channel *channel, पूर्णांक budget)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा xlgmac_ring *ring = channel->rx_ring;
	काष्ठा net_device *netdev = pdata->netdev;
	अचिन्हित पूर्णांक len, dma_desc_len, max_len;
	अचिन्हित पूर्णांक context_next, context;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_pkt_info *pkt_info;
	अचिन्हित पूर्णांक incomplete, error;
	काष्ठा xlgmac_hw_ops *hw_ops;
	अचिन्हित पूर्णांक received = 0;
	काष्ठा napi_काष्ठा *napi;
	काष्ठा sk_buff *skb;
	पूर्णांक packet_count = 0;

	hw_ops = &pdata->hw_ops;

	/* Nothing to करो अगर there isn't a Rx ring क्रम this channel */
	अगर (!ring)
		वापस 0;

	incomplete = 0;
	context_next = 0;

	napi = (pdata->per_channel_irq) ? &channel->napi : &pdata->napi;

	desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);
	pkt_info = &ring->pkt_info;
	जबतक (packet_count < budget) अणु
		/* First समय in loop see अगर we need to restore state */
		अगर (!received && desc_data->state_saved) अणु
			skb = desc_data->state.skb;
			error = desc_data->state.error;
			len = desc_data->state.len;
		पूर्ण अन्यथा अणु
			स_रखो(pkt_info, 0, माप(*pkt_info));
			skb = शून्य;
			error = 0;
			len = 0;
		पूर्ण

पढ़ो_again:
		desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);

		अगर (xlgmac_rx_dirty_desc(ring) > XLGMAC_RX_DESC_MAX_सूचीTY)
			xlgmac_rx_refresh(channel);

		अगर (hw_ops->dev_पढ़ो(channel))
			अवरोध;

		received++;
		ring->cur++;

		incomplete = XLGMAC_GET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_INCOMPLETE_POS,
					RX_PACKET_ATTRIBUTES_INCOMPLETE_LEN);
		context_next = XLGMAC_GET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_POS,
					RX_PACKET_ATTRIBUTES_CONTEXT_NEXT_LEN);
		context = XLGMAC_GET_REG_BITS(
					pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CONTEXT_POS,
					RX_PACKET_ATTRIBUTES_CONTEXT_LEN);

		/* Earlier error, just drain the reमुख्यing data */
		अगर ((incomplete || context_next) && error)
			जाओ पढ़ो_again;

		अगर (error || pkt_info->errors) अणु
			अगर (pkt_info->errors)
				netअगर_err(pdata, rx_err, netdev,
					  "error in received packet\n");
			dev_kमुक्त_skb(skb);
			जाओ next_packet;
		पूर्ण

		अगर (!context) अणु
			/* Length is cumulative, get this descriptor's length */
			dma_desc_len = desc_data->rx.len - len;
			len += dma_desc_len;

			अगर (dma_desc_len && !skb) अणु
				skb = xlgmac_create_skb(pdata, napi, desc_data,
							dma_desc_len);
				अगर (!skb)
					error = 1;
			पूर्ण अन्यथा अगर (dma_desc_len) अणु
				dma_sync_single_range_क्रम_cpu(
						pdata->dev,
						desc_data->rx.buf.dma_base,
						desc_data->rx.buf.dma_off,
						desc_data->rx.buf.dma_len,
						DMA_FROM_DEVICE);

				skb_add_rx_frag(
					skb, skb_shinfo(skb)->nr_frags,
					desc_data->rx.buf.pa.pages,
					desc_data->rx.buf.pa.pages_offset,
					dma_desc_len,
					desc_data->rx.buf.dma_len);
				desc_data->rx.buf.pa.pages = शून्य;
			पूर्ण
		पूर्ण

		अगर (incomplete || context_next)
			जाओ पढ़ो_again;

		अगर (!skb)
			जाओ next_packet;

		/* Be sure we करोn't exceed the configured MTU */
		max_len = netdev->mtu + ETH_HLEN;
		अगर (!(netdev->features & NETIF_F_HW_VLAN_CTAG_RX) &&
		    (skb->protocol == htons(ETH_P_8021Q)))
			max_len += VLAN_HLEN;

		अगर (skb->len > max_len) अणु
			netअगर_err(pdata, rx_err, netdev,
				  "packet length exceeds configured MTU\n");
			dev_kमुक्त_skb(skb);
			जाओ next_packet;
		पूर्ण

		अगर (netअगर_msg_pktdata(pdata))
			xlgmac_prपूर्णांक_pkt(netdev, skb, false);

		skb_checksum_none_निश्चित(skb);
		अगर (XLGMAC_GET_REG_BITS(pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_CSUM_DONE_POS,
				    RX_PACKET_ATTRIBUTES_CSUM_DONE_LEN))
			skb->ip_summed = CHECKSUM_UNNECESSARY;

		अगर (XLGMAC_GET_REG_BITS(pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_VLAN_CTAG_POS,
				    RX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN)) अणु
			__vlan_hwaccel_put_tag(skb, htons(ETH_P_8021Q),
					       pkt_info->vlan_ctag);
			pdata->stats.rx_vlan_packets++;
		पूर्ण

		अगर (XLGMAC_GET_REG_BITS(pkt_info->attributes,
					RX_PACKET_ATTRIBUTES_RSS_HASH_POS,
				    RX_PACKET_ATTRIBUTES_RSS_HASH_LEN))
			skb_set_hash(skb, pkt_info->rss_hash,
				     pkt_info->rss_hash_type);

		skb->dev = netdev;
		skb->protocol = eth_type_trans(skb, netdev);
		skb_record_rx_queue(skb, channel->queue_index);

		napi_gro_receive(napi, skb);

next_packet:
		packet_count++;
	पूर्ण

	/* Check अगर we need to save state beक्रमe leaving */
	अगर (received && (incomplete || context_next)) अणु
		desc_data = XLGMAC_GET_DESC_DATA(ring, ring->cur);
		desc_data->state_saved = 1;
		desc_data->state.skb = skb;
		desc_data->state.len = len;
		desc_data->state.error = error;
	पूर्ण

	XLGMAC_PR("packet_count = %d\n", packet_count);

	वापस packet_count;
पूर्ण

अटल पूर्णांक xlgmac_one_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा xlgmac_channel *channel = container_of(napi,
						काष्ठा xlgmac_channel,
						napi);
	पूर्णांक processed = 0;

	XLGMAC_PR("budget=%d\n", budget);

	/* Cleanup Tx ring first */
	xlgmac_tx_poll(channel);

	/* Process Rx ring next */
	processed = xlgmac_rx_poll(channel, budget);

	/* If we processed everything, we are करोne */
	अगर (processed < budget) अणु
		/* Turn off polling */
		napi_complete_करोne(napi, processed);

		/* Enable Tx and Rx पूर्णांकerrupts */
		enable_irq(channel->dma_irq);
	पूर्ण

	XLGMAC_PR("received = %d\n", processed);

	वापस processed;
पूर्ण

अटल पूर्णांक xlgmac_all_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा xlgmac_pdata *pdata = container_of(napi,
						   काष्ठा xlgmac_pdata,
						   napi);
	काष्ठा xlgmac_channel *channel;
	पूर्णांक processed, last_processed;
	पूर्णांक ring_budget;
	अचिन्हित पूर्णांक i;

	XLGMAC_PR("budget=%d\n", budget);

	processed = 0;
	ring_budget = budget / pdata->rx_ring_count;
	करो अणु
		last_processed = processed;

		channel = pdata->channel_head;
		क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
			/* Cleanup Tx ring first */
			xlgmac_tx_poll(channel);

			/* Process Rx ring next */
			अगर (ring_budget > (budget - processed))
				ring_budget = budget - processed;
			processed += xlgmac_rx_poll(channel, ring_budget);
		पूर्ण
	पूर्ण जबतक ((processed < budget) && (processed != last_processed));

	/* If we processed everything, we are करोne */
	अगर (processed < budget) अणु
		/* Turn off polling */
		napi_complete_करोne(napi, processed);

		/* Enable Tx and Rx पूर्णांकerrupts */
		xlgmac_enable_rx_tx_पूर्णांकs(pdata);
	पूर्ण

	XLGMAC_PR("received = %d\n", processed);

	वापस processed;
पूर्ण
