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

#समावेश "dwc-xlgmac.h"
#समावेश "dwc-xlgmac-reg.h"

अटल व्योम xlgmac_unmap_desc_data(काष्ठा xlgmac_pdata *pdata,
				   काष्ठा xlgmac_desc_data *desc_data)
अणु
	अगर (desc_data->skb_dma) अणु
		अगर (desc_data->mapped_as_page) अणु
			dma_unmap_page(pdata->dev, desc_data->skb_dma,
				       desc_data->skb_dma_len, DMA_TO_DEVICE);
		पूर्ण अन्यथा अणु
			dma_unmap_single(pdata->dev, desc_data->skb_dma,
					 desc_data->skb_dma_len, DMA_TO_DEVICE);
		पूर्ण
		desc_data->skb_dma = 0;
		desc_data->skb_dma_len = 0;
	पूर्ण

	अगर (desc_data->skb) अणु
		dev_kमुक्त_skb_any(desc_data->skb);
		desc_data->skb = शून्य;
	पूर्ण

	अगर (desc_data->rx.hdr.pa.pages)
		put_page(desc_data->rx.hdr.pa.pages);

	अगर (desc_data->rx.hdr.pa_unmap.pages) अणु
		dma_unmap_page(pdata->dev, desc_data->rx.hdr.pa_unmap.pages_dma,
			       desc_data->rx.hdr.pa_unmap.pages_len,
			       DMA_FROM_DEVICE);
		put_page(desc_data->rx.hdr.pa_unmap.pages);
	पूर्ण

	अगर (desc_data->rx.buf.pa.pages)
		put_page(desc_data->rx.buf.pa.pages);

	अगर (desc_data->rx.buf.pa_unmap.pages) अणु
		dma_unmap_page(pdata->dev, desc_data->rx.buf.pa_unmap.pages_dma,
			       desc_data->rx.buf.pa_unmap.pages_len,
			       DMA_FROM_DEVICE);
		put_page(desc_data->rx.buf.pa_unmap.pages);
	पूर्ण

	स_रखो(&desc_data->tx, 0, माप(desc_data->tx));
	स_रखो(&desc_data->rx, 0, माप(desc_data->rx));

	desc_data->mapped_as_page = 0;

	अगर (desc_data->state_saved) अणु
		desc_data->state_saved = 0;
		desc_data->state.skb = शून्य;
		desc_data->state.len = 0;
		desc_data->state.error = 0;
	पूर्ण
पूर्ण

अटल व्योम xlgmac_मुक्त_ring(काष्ठा xlgmac_pdata *pdata,
			     काष्ठा xlgmac_ring *ring)
अणु
	काष्ठा xlgmac_desc_data *desc_data;
	अचिन्हित पूर्णांक i;

	अगर (!ring)
		वापस;

	अगर (ring->desc_data_head) अणु
		क्रम (i = 0; i < ring->dma_desc_count; i++) अणु
			desc_data = XLGMAC_GET_DESC_DATA(ring, i);
			xlgmac_unmap_desc_data(pdata, desc_data);
		पूर्ण

		kमुक्त(ring->desc_data_head);
		ring->desc_data_head = शून्य;
	पूर्ण

	अगर (ring->rx_hdr_pa.pages) अणु
		dma_unmap_page(pdata->dev, ring->rx_hdr_pa.pages_dma,
			       ring->rx_hdr_pa.pages_len, DMA_FROM_DEVICE);
		put_page(ring->rx_hdr_pa.pages);

		ring->rx_hdr_pa.pages = शून्य;
		ring->rx_hdr_pa.pages_len = 0;
		ring->rx_hdr_pa.pages_offset = 0;
		ring->rx_hdr_pa.pages_dma = 0;
	पूर्ण

	अगर (ring->rx_buf_pa.pages) अणु
		dma_unmap_page(pdata->dev, ring->rx_buf_pa.pages_dma,
			       ring->rx_buf_pa.pages_len, DMA_FROM_DEVICE);
		put_page(ring->rx_buf_pa.pages);

		ring->rx_buf_pa.pages = शून्य;
		ring->rx_buf_pa.pages_len = 0;
		ring->rx_buf_pa.pages_offset = 0;
		ring->rx_buf_pa.pages_dma = 0;
	पूर्ण

	अगर (ring->dma_desc_head) अणु
		dma_मुक्त_coherent(pdata->dev,
				  (माप(काष्ठा xlgmac_dma_desc) *
				  ring->dma_desc_count),
				  ring->dma_desc_head,
				  ring->dma_desc_head_addr);
		ring->dma_desc_head = शून्य;
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_init_ring(काष्ठा xlgmac_pdata *pdata,
			    काष्ठा xlgmac_ring *ring,
			    अचिन्हित पूर्णांक dma_desc_count)
अणु
	अगर (!ring)
		वापस 0;

	/* Descriptors */
	ring->dma_desc_count = dma_desc_count;
	ring->dma_desc_head = dma_alloc_coherent(pdata->dev,
					(माप(काष्ठा xlgmac_dma_desc) *
					 dma_desc_count),
					&ring->dma_desc_head_addr,
					GFP_KERNEL);
	अगर (!ring->dma_desc_head)
		वापस -ENOMEM;

	/* Array of descriptor data */
	ring->desc_data_head = kसुस्मृति(dma_desc_count,
					माप(काष्ठा xlgmac_desc_data),
					GFP_KERNEL);
	अगर (!ring->desc_data_head)
		वापस -ENOMEM;

	netअगर_dbg(pdata, drv, pdata->netdev,
		  "dma_desc_head=%p, dma_desc_head_addr=%pad, desc_data_head=%p\n",
		ring->dma_desc_head,
		&ring->dma_desc_head_addr,
		ring->desc_data_head);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_मुक्त_rings(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;

	अगर (!pdata->channel_head)
		वापस;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		xlgmac_मुक्त_ring(pdata, channel->tx_ring);
		xlgmac_मुक्त_ring(pdata, channel->rx_ring);
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_alloc_rings(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel;
	अचिन्हित पूर्णांक i;
	पूर्णांक ret;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		netअगर_dbg(pdata, drv, pdata->netdev, "%s - Tx ring:\n",
			  channel->name);

		ret = xlgmac_init_ring(pdata, channel->tx_ring,
				       pdata->tx_desc_count);

		अगर (ret) अणु
			netdev_alert(pdata->netdev,
				     "error initializing Tx ring");
			जाओ err_init_ring;
		पूर्ण

		netअगर_dbg(pdata, drv, pdata->netdev, "%s - Rx ring:\n",
			  channel->name);

		ret = xlgmac_init_ring(pdata, channel->rx_ring,
				       pdata->rx_desc_count);
		अगर (ret) अणु
			netdev_alert(pdata->netdev,
				     "error initializing Rx ring\n");
			जाओ err_init_ring;
		पूर्ण
	पूर्ण

	वापस 0;

err_init_ring:
	xlgmac_मुक्त_rings(pdata);

	वापस ret;
पूर्ण

अटल व्योम xlgmac_मुक्त_channels(काष्ठा xlgmac_pdata *pdata)
अणु
	अगर (!pdata->channel_head)
		वापस;

	kमुक्त(pdata->channel_head->tx_ring);
	pdata->channel_head->tx_ring = शून्य;

	kमुक्त(pdata->channel_head->rx_ring);
	pdata->channel_head->rx_ring = शून्य;

	kमुक्त(pdata->channel_head);

	pdata->channel_head = शून्य;
	pdata->channel_count = 0;
पूर्ण

अटल पूर्णांक xlgmac_alloc_channels(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_channel *channel_head, *channel;
	काष्ठा xlgmac_ring *tx_ring, *rx_ring;
	पूर्णांक ret = -ENOMEM;
	अचिन्हित पूर्णांक i;

	channel_head = kसुस्मृति(pdata->channel_count,
			       माप(काष्ठा xlgmac_channel), GFP_KERNEL);
	अगर (!channel_head)
		वापस ret;

	netअगर_dbg(pdata, drv, pdata->netdev,
		  "channel_head=%p\n", channel_head);

	tx_ring = kसुस्मृति(pdata->tx_ring_count, माप(काष्ठा xlgmac_ring),
			  GFP_KERNEL);
	अगर (!tx_ring)
		जाओ err_tx_ring;

	rx_ring = kसुस्मृति(pdata->rx_ring_count, माप(काष्ठा xlgmac_ring),
			  GFP_KERNEL);
	अगर (!rx_ring)
		जाओ err_rx_ring;

	क्रम (i = 0, channel = channel_head; i < pdata->channel_count;
		i++, channel++) अणु
		snम_लिखो(channel->name, माप(channel->name), "channel-%u", i);
		channel->pdata = pdata;
		channel->queue_index = i;
		channel->dma_regs = pdata->mac_regs + DMA_CH_BASE +
				    (DMA_CH_INC * i);

		अगर (pdata->per_channel_irq) अणु
			/* Get the per DMA पूर्णांकerrupt */
			ret = pdata->channel_irq[i];
			अगर (ret < 0) अणु
				netdev_err(pdata->netdev,
					   "get_irq %u failed\n",
					   i + 1);
				जाओ err_irq;
			पूर्ण
			channel->dma_irq = ret;
		पूर्ण

		अगर (i < pdata->tx_ring_count)
			channel->tx_ring = tx_ring++;

		अगर (i < pdata->rx_ring_count)
			channel->rx_ring = rx_ring++;

		netअगर_dbg(pdata, drv, pdata->netdev,
			  "%s: dma_regs=%p, tx_ring=%p, rx_ring=%p\n",
			  channel->name, channel->dma_regs,
			  channel->tx_ring, channel->rx_ring);
	पूर्ण

	pdata->channel_head = channel_head;

	वापस 0;

err_irq:
	kमुक्त(rx_ring);

err_rx_ring:
	kमुक्त(tx_ring);

err_tx_ring:
	kमुक्त(channel_head);

	वापस ret;
पूर्ण

अटल व्योम xlgmac_मुक्त_channels_and_rings(काष्ठा xlgmac_pdata *pdata)
अणु
	xlgmac_मुक्त_rings(pdata);

	xlgmac_मुक्त_channels(pdata);
पूर्ण

अटल पूर्णांक xlgmac_alloc_channels_and_rings(काष्ठा xlgmac_pdata *pdata)
अणु
	पूर्णांक ret;

	ret = xlgmac_alloc_channels(pdata);
	अगर (ret)
		जाओ err_alloc;

	ret = xlgmac_alloc_rings(pdata);
	अगर (ret)
		जाओ err_alloc;

	वापस 0;

err_alloc:
	xlgmac_मुक्त_channels_and_rings(pdata);

	वापस ret;
पूर्ण

अटल पूर्णांक xlgmac_alloc_pages(काष्ठा xlgmac_pdata *pdata,
			      काष्ठा xlgmac_page_alloc *pa,
			      gfp_t gfp, पूर्णांक order)
अणु
	काष्ठा page *pages = शून्य;
	dma_addr_t pages_dma;

	/* Try to obtain pages, decreasing order अगर necessary */
	gfp |= __GFP_COMP | __GFP_NOWARN;
	जबतक (order >= 0) अणु
		pages = alloc_pages(gfp, order);
		अगर (pages)
			अवरोध;

		order--;
	पूर्ण
	अगर (!pages)
		वापस -ENOMEM;

	/* Map the pages */
	pages_dma = dma_map_page(pdata->dev, pages, 0,
				 PAGE_SIZE << order, DMA_FROM_DEVICE);
	अगर (dma_mapping_error(pdata->dev, pages_dma)) अणु
		put_page(pages);
		वापस -ENOMEM;
	पूर्ण

	pa->pages = pages;
	pa->pages_len = PAGE_SIZE << order;
	pa->pages_offset = 0;
	pa->pages_dma = pages_dma;

	वापस 0;
पूर्ण

अटल व्योम xlgmac_set_buffer_data(काष्ठा xlgmac_buffer_data *bd,
				   काष्ठा xlgmac_page_alloc *pa,
				   अचिन्हित पूर्णांक len)
अणु
	get_page(pa->pages);
	bd->pa = *pa;

	bd->dma_base = pa->pages_dma;
	bd->dma_off = pa->pages_offset;
	bd->dma_len = len;

	pa->pages_offset += len;
	अगर ((pa->pages_offset + len) > pa->pages_len) अणु
		/* This data descriptor is responsible क्रम unmapping page(s) */
		bd->pa_unmap = *pa;

		/* Get a new allocation next समय */
		pa->pages = शून्य;
		pa->pages_len = 0;
		pa->pages_offset = 0;
		pa->pages_dma = 0;
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_map_rx_buffer(काष्ठा xlgmac_pdata *pdata,
				काष्ठा xlgmac_ring *ring,
				काष्ठा xlgmac_desc_data *desc_data)
अणु
	पूर्णांक order, ret;

	अगर (!ring->rx_hdr_pa.pages) अणु
		ret = xlgmac_alloc_pages(pdata, &ring->rx_hdr_pa,
					 GFP_ATOMIC, 0);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (!ring->rx_buf_pa.pages) अणु
		order = max_t(पूर्णांक, PAGE_ALLOC_COSTLY_ORDER - 1, 0);
		ret = xlgmac_alloc_pages(pdata, &ring->rx_buf_pa,
					 GFP_ATOMIC, order);
		अगर (ret)
			वापस ret;
	पूर्ण

	/* Set up the header page info */
	xlgmac_set_buffer_data(&desc_data->rx.hdr, &ring->rx_hdr_pa,
			       XLGMAC_SKB_ALLOC_SIZE);

	/* Set up the buffer page info */
	xlgmac_set_buffer_data(&desc_data->rx.buf, &ring->rx_buf_pa,
			       pdata->rx_buf_size);

	वापस 0;
पूर्ण

अटल व्योम xlgmac_tx_desc_init(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_dma_desc *dma_desc;
	काष्ठा xlgmac_channel *channel;
	काष्ठा xlgmac_ring *ring;
	dma_addr_t dma_desc_addr;
	अचिन्हित पूर्णांक i, j;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		ring = channel->tx_ring;
		अगर (!ring)
			अवरोध;

		dma_desc = ring->dma_desc_head;
		dma_desc_addr = ring->dma_desc_head_addr;

		क्रम (j = 0; j < ring->dma_desc_count; j++) अणु
			desc_data = XLGMAC_GET_DESC_DATA(ring, j);

			desc_data->dma_desc = dma_desc;
			desc_data->dma_desc_addr = dma_desc_addr;

			dma_desc++;
			dma_desc_addr += माप(काष्ठा xlgmac_dma_desc);
		पूर्ण

		ring->cur = 0;
		ring->dirty = 0;
		स_रखो(&ring->tx, 0, माप(ring->tx));

		hw_ops->tx_desc_init(channel);
	पूर्ण
पूर्ण

अटल व्योम xlgmac_rx_desc_init(काष्ठा xlgmac_pdata *pdata)
अणु
	काष्ठा xlgmac_hw_ops *hw_ops = &pdata->hw_ops;
	काष्ठा xlgmac_desc_data *desc_data;
	काष्ठा xlgmac_dma_desc *dma_desc;
	काष्ठा xlgmac_channel *channel;
	काष्ठा xlgmac_ring *ring;
	dma_addr_t dma_desc_addr;
	अचिन्हित पूर्णांक i, j;

	channel = pdata->channel_head;
	क्रम (i = 0; i < pdata->channel_count; i++, channel++) अणु
		ring = channel->rx_ring;
		अगर (!ring)
			अवरोध;

		dma_desc = ring->dma_desc_head;
		dma_desc_addr = ring->dma_desc_head_addr;

		क्रम (j = 0; j < ring->dma_desc_count; j++) अणु
			desc_data = XLGMAC_GET_DESC_DATA(ring, j);

			desc_data->dma_desc = dma_desc;
			desc_data->dma_desc_addr = dma_desc_addr;

			अगर (xlgmac_map_rx_buffer(pdata, ring, desc_data))
				अवरोध;

			dma_desc++;
			dma_desc_addr += माप(काष्ठा xlgmac_dma_desc);
		पूर्ण

		ring->cur = 0;
		ring->dirty = 0;

		hw_ops->rx_desc_init(channel);
	पूर्ण
पूर्ण

अटल पूर्णांक xlgmac_map_tx_skb(काष्ठा xlgmac_channel *channel,
			     काष्ठा sk_buff *skb)
अणु
	काष्ठा xlgmac_pdata *pdata = channel->pdata;
	काष्ठा xlgmac_ring *ring = channel->tx_ring;
	अचिन्हित पूर्णांक start_index, cur_index;
	काष्ठा xlgmac_desc_data *desc_data;
	अचिन्हित पूर्णांक offset, datalen, len;
	काष्ठा xlgmac_pkt_info *pkt_info;
	skb_frag_t *frag;
	अचिन्हित पूर्णांक tso, vlan;
	dma_addr_t skb_dma;
	अचिन्हित पूर्णांक i;

	offset = 0;
	start_index = ring->cur;
	cur_index = ring->cur;

	pkt_info = &ring->pkt_info;
	pkt_info->desc_count = 0;
	pkt_info->length = 0;

	tso = XLGMAC_GET_REG_BITS(pkt_info->attributes,
				  TX_PACKET_ATTRIBUTES_TSO_ENABLE_POS,
				  TX_PACKET_ATTRIBUTES_TSO_ENABLE_LEN);
	vlan = XLGMAC_GET_REG_BITS(pkt_info->attributes,
				   TX_PACKET_ATTRIBUTES_VLAN_CTAG_POS,
				   TX_PACKET_ATTRIBUTES_VLAN_CTAG_LEN);

	/* Save space क्रम a context descriptor अगर needed */
	अगर ((tso && (pkt_info->mss != ring->tx.cur_mss)) ||
	    (vlan && (pkt_info->vlan_ctag != ring->tx.cur_vlan_ctag)))
		cur_index++;
	desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);

	अगर (tso) अणु
		/* Map the TSO header */
		skb_dma = dma_map_single(pdata->dev, skb->data,
					 pkt_info->header_len, DMA_TO_DEVICE);
		अगर (dma_mapping_error(pdata->dev, skb_dma)) अणु
			netdev_alert(pdata->netdev, "dma_map_single failed\n");
			जाओ err_out;
		पूर्ण
		desc_data->skb_dma = skb_dma;
		desc_data->skb_dma_len = pkt_info->header_len;
		netअगर_dbg(pdata, tx_queued, pdata->netdev,
			  "skb header: index=%u, dma=%pad, len=%u\n",
			  cur_index, &skb_dma, pkt_info->header_len);

		offset = pkt_info->header_len;

		pkt_info->length += pkt_info->header_len;

		cur_index++;
		desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
	पूर्ण

	/* Map the (reमुख्यder of the) packet */
	क्रम (datalen = skb_headlen(skb) - offset; datalen; ) अणु
		len = min_t(अचिन्हित पूर्णांक, datalen, XLGMAC_TX_MAX_BUF_SIZE);

		skb_dma = dma_map_single(pdata->dev, skb->data + offset, len,
					 DMA_TO_DEVICE);
		अगर (dma_mapping_error(pdata->dev, skb_dma)) अणु
			netdev_alert(pdata->netdev, "dma_map_single failed\n");
			जाओ err_out;
		पूर्ण
		desc_data->skb_dma = skb_dma;
		desc_data->skb_dma_len = len;
		netअगर_dbg(pdata, tx_queued, pdata->netdev,
			  "skb data: index=%u, dma=%pad, len=%u\n",
			  cur_index, &skb_dma, len);

		datalen -= len;
		offset += len;

		pkt_info->length += len;

		cur_index++;
		desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
	पूर्ण

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; i++) अणु
		netअगर_dbg(pdata, tx_queued, pdata->netdev,
			  "mapping frag %u\n", i);

		frag = &skb_shinfo(skb)->frags[i];
		offset = 0;

		क्रम (datalen = skb_frag_size(frag); datalen; ) अणु
			len = min_t(अचिन्हित पूर्णांक, datalen,
				    XLGMAC_TX_MAX_BUF_SIZE);

			skb_dma = skb_frag_dma_map(pdata->dev, frag, offset,
						   len, DMA_TO_DEVICE);
			अगर (dma_mapping_error(pdata->dev, skb_dma)) अणु
				netdev_alert(pdata->netdev,
					     "skb_frag_dma_map failed\n");
				जाओ err_out;
			पूर्ण
			desc_data->skb_dma = skb_dma;
			desc_data->skb_dma_len = len;
			desc_data->mapped_as_page = 1;
			netअगर_dbg(pdata, tx_queued, pdata->netdev,
				  "skb frag: index=%u, dma=%pad, len=%u\n",
				  cur_index, &skb_dma, len);

			datalen -= len;
			offset += len;

			pkt_info->length += len;

			cur_index++;
			desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index);
		पूर्ण
	पूर्ण

	/* Save the skb address in the last entry. We always have some data
	 * that has been mapped so desc_data is always advanced past the last
	 * piece of mapped data - use the entry poपूर्णांकed to by cur_index - 1.
	 */
	desc_data = XLGMAC_GET_DESC_DATA(ring, cur_index - 1);
	desc_data->skb = skb;

	/* Save the number of descriptor entries used */
	pkt_info->desc_count = cur_index - start_index;

	वापस pkt_info->desc_count;

err_out:
	जबतक (start_index < cur_index) अणु
		desc_data = XLGMAC_GET_DESC_DATA(ring, start_index++);
		xlgmac_unmap_desc_data(pdata, desc_data);
	पूर्ण

	वापस 0;
पूर्ण

व्योम xlgmac_init_desc_ops(काष्ठा xlgmac_desc_ops *desc_ops)
अणु
	desc_ops->alloc_channels_and_rings = xlgmac_alloc_channels_and_rings;
	desc_ops->मुक्त_channels_and_rings = xlgmac_मुक्त_channels_and_rings;
	desc_ops->map_tx_skb = xlgmac_map_tx_skb;
	desc_ops->map_rx_buffer = xlgmac_map_rx_buffer;
	desc_ops->unmap_desc_data = xlgmac_unmap_desc_data;
	desc_ops->tx_desc_init = xlgmac_tx_desc_init;
	desc_ops->rx_desc_init = xlgmac_rx_desc_init;
पूर्ण
