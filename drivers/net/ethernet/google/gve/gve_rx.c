<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

#समावेश "gve.h"
#समावेश "gve_adminq.h"
#समावेश <linux/etherdevice.h>

अटल व्योम gve_rx_हटाओ_from_block(काष्ठा gve_priv *priv, पूर्णांक queue_idx)
अणु
	काष्ठा gve_notअगरy_block *block =
			&priv->ntfy_blocks[gve_rx_idx_to_ntfy(priv, queue_idx)];

	block->rx = शून्य;
पूर्ण

अटल व्योम gve_rx_मुक्त_buffer(काष्ठा device *dev,
			       काष्ठा gve_rx_slot_page_info *page_info,
			       जोड़ gve_rx_data_slot *data_slot)
अणु
	dma_addr_t dma = (dma_addr_t)(be64_to_cpu(data_slot->addr) &
				      GVE_DATA_SLOT_ADDR_PAGE_MASK);

	gve_मुक्त_page(dev, page_info->page, dma, DMA_FROM_DEVICE);
पूर्ण

अटल व्योम gve_rx_unfill_pages(काष्ठा gve_priv *priv, काष्ठा gve_rx_ring *rx)
अणु
	अगर (rx->data.raw_addressing) अणु
		u32 slots = rx->mask + 1;
		पूर्णांक i;

		क्रम (i = 0; i < slots; i++)
			gve_rx_मुक्त_buffer(&priv->pdev->dev, &rx->data.page_info[i],
					   &rx->data.data_ring[i]);
	पूर्ण अन्यथा अणु
		gve_unassign_qpl(priv, rx->data.qpl->id);
		rx->data.qpl = शून्य;
	पूर्ण
	kvमुक्त(rx->data.page_info);
	rx->data.page_info = शून्य;
पूर्ण

अटल व्योम gve_rx_मुक्त_ring(काष्ठा gve_priv *priv, पूर्णांक idx)
अणु
	काष्ठा gve_rx_ring *rx = &priv->rx[idx];
	काष्ठा device *dev = &priv->pdev->dev;
	u32 slots = rx->mask + 1;
	माप_प्रकार bytes;

	gve_rx_हटाओ_from_block(priv, idx);

	bytes = माप(काष्ठा gve_rx_desc) * priv->rx_desc_cnt;
	dma_मुक्त_coherent(dev, bytes, rx->desc.desc_ring, rx->desc.bus);
	rx->desc.desc_ring = शून्य;

	dma_मुक्त_coherent(dev, माप(*rx->q_resources),
			  rx->q_resources, rx->q_resources_bus);
	rx->q_resources = शून्य;

	gve_rx_unfill_pages(priv, rx);

	bytes = माप(*rx->data.data_ring) * slots;
	dma_मुक्त_coherent(dev, bytes, rx->data.data_ring,
			  rx->data.data_bus);
	rx->data.data_ring = शून्य;
	netअगर_dbg(priv, drv, priv->dev, "freed rx ring %d\n", idx);
पूर्ण

अटल व्योम gve_setup_rx_buffer(काष्ठा gve_rx_slot_page_info *page_info,
			     dma_addr_t addr, काष्ठा page *page, __be64 *slot_addr)
अणु
	page_info->page = page;
	page_info->page_offset = 0;
	page_info->page_address = page_address(page);
	*slot_addr = cpu_to_be64(addr);
पूर्ण

अटल पूर्णांक gve_rx_alloc_buffer(काष्ठा gve_priv *priv, काष्ठा device *dev,
			       काष्ठा gve_rx_slot_page_info *page_info,
			       जोड़ gve_rx_data_slot *data_slot)
अणु
	काष्ठा page *page;
	dma_addr_t dma;
	पूर्णांक err;

	err = gve_alloc_page(priv, dev, &page, &dma, DMA_FROM_DEVICE);
	अगर (err)
		वापस err;

	gve_setup_rx_buffer(page_info, dma, page, &data_slot->addr);
	वापस 0;
पूर्ण

अटल पूर्णांक gve_prefill_rx_pages(काष्ठा gve_rx_ring *rx)
अणु
	काष्ठा gve_priv *priv = rx->gve;
	u32 slots;
	पूर्णांक err;
	पूर्णांक i;

	/* Allocate one page per Rx queue slot. Each page is split पूर्णांकo two
	 * packet buffers, when possible we "page flip" between the two.
	 */
	slots = rx->mask + 1;

	rx->data.page_info = kvzalloc(slots *
				      माप(*rx->data.page_info), GFP_KERNEL);
	अगर (!rx->data.page_info)
		वापस -ENOMEM;

	अगर (!rx->data.raw_addressing)
		rx->data.qpl = gve_assign_rx_qpl(priv);
	क्रम (i = 0; i < slots; i++) अणु
		अगर (!rx->data.raw_addressing) अणु
			काष्ठा page *page = rx->data.qpl->pages[i];
			dma_addr_t addr = i * PAGE_SIZE;

			gve_setup_rx_buffer(&rx->data.page_info[i], addr, page,
					    &rx->data.data_ring[i].qpl_offset);
			जारी;
		पूर्ण
		err = gve_rx_alloc_buffer(priv, &priv->pdev->dev, &rx->data.page_info[i],
					  &rx->data.data_ring[i]);
		अगर (err)
			जाओ alloc_err;
	पूर्ण

	वापस slots;
alloc_err:
	जबतक (i--)
		gve_rx_मुक्त_buffer(&priv->pdev->dev,
				   &rx->data.page_info[i],
				   &rx->data.data_ring[i]);
	वापस err;
पूर्ण

अटल व्योम gve_rx_add_to_block(काष्ठा gve_priv *priv, पूर्णांक queue_idx)
अणु
	u32 ntfy_idx = gve_rx_idx_to_ntfy(priv, queue_idx);
	काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[ntfy_idx];
	काष्ठा gve_rx_ring *rx = &priv->rx[queue_idx];

	block->rx = rx;
	rx->ntfy_id = ntfy_idx;
पूर्ण

अटल पूर्णांक gve_rx_alloc_ring(काष्ठा gve_priv *priv, पूर्णांक idx)
अणु
	काष्ठा gve_rx_ring *rx = &priv->rx[idx];
	काष्ठा device *hdev = &priv->pdev->dev;
	u32 slots, npages;
	पूर्णांक filled_pages;
	माप_प्रकार bytes;
	पूर्णांक err;

	netअगर_dbg(priv, drv, priv->dev, "allocating rx ring\n");
	/* Make sure everything is zeroed to start with */
	स_रखो(rx, 0, माप(*rx));

	rx->gve = priv;
	rx->q_num = idx;

	slots = priv->rx_data_slot_cnt;
	rx->mask = slots - 1;
	rx->data.raw_addressing = priv->raw_addressing;

	/* alloc rx data ring */
	bytes = माप(*rx->data.data_ring) * slots;
	rx->data.data_ring = dma_alloc_coherent(hdev, bytes,
						&rx->data.data_bus,
						GFP_KERNEL);
	अगर (!rx->data.data_ring)
		वापस -ENOMEM;
	filled_pages = gve_prefill_rx_pages(rx);
	अगर (filled_pages < 0) अणु
		err = -ENOMEM;
		जाओ पात_with_slots;
	पूर्ण
	rx->fill_cnt = filled_pages;
	/* Ensure data ring slots (packet buffers) are visible. */
	dma_wmb();

	/* Alloc gve_queue_resources */
	rx->q_resources =
		dma_alloc_coherent(hdev,
				   माप(*rx->q_resources),
				   &rx->q_resources_bus,
				   GFP_KERNEL);
	अगर (!rx->q_resources) अणु
		err = -ENOMEM;
		जाओ पात_filled;
	पूर्ण
	netअगर_dbg(priv, drv, priv->dev, "rx[%d]->data.data_bus=%lx\n", idx,
		  (अचिन्हित दीर्घ)rx->data.data_bus);

	/* alloc rx desc ring */
	bytes = माप(काष्ठा gve_rx_desc) * priv->rx_desc_cnt;
	npages = bytes / PAGE_SIZE;
	अगर (npages * PAGE_SIZE != bytes) अणु
		err = -EIO;
		जाओ पात_with_q_resources;
	पूर्ण

	rx->desc.desc_ring = dma_alloc_coherent(hdev, bytes, &rx->desc.bus,
						GFP_KERNEL);
	अगर (!rx->desc.desc_ring) अणु
		err = -ENOMEM;
		जाओ पात_with_q_resources;
	पूर्ण
	rx->cnt = 0;
	rx->db_threshold = priv->rx_desc_cnt / 2;
	rx->desc.seqno = 1;
	gve_rx_add_to_block(priv, idx);

	वापस 0;

पात_with_q_resources:
	dma_मुक्त_coherent(hdev, माप(*rx->q_resources),
			  rx->q_resources, rx->q_resources_bus);
	rx->q_resources = शून्य;
पात_filled:
	gve_rx_unfill_pages(priv, rx);
पात_with_slots:
	bytes = माप(*rx->data.data_ring) * slots;
	dma_मुक्त_coherent(hdev, bytes, rx->data.data_ring, rx->data.data_bus);
	rx->data.data_ring = शून्य;

	वापस err;
पूर्ण

पूर्णांक gve_rx_alloc_rings(काष्ठा gve_priv *priv)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < priv->rx_cfg.num_queues; i++) अणु
		err = gve_rx_alloc_ring(priv, i);
		अगर (err) अणु
			netअगर_err(priv, drv, priv->dev,
				  "Failed to alloc rx ring=%d: err=%d\n",
				  i, err);
			अवरोध;
		पूर्ण
	पूर्ण
	/* Unallocate अगर there was an error */
	अगर (err) अणु
		पूर्णांक j;

		क्रम (j = 0; j < i; j++)
			gve_rx_मुक्त_ring(priv, j);
	पूर्ण
	वापस err;
पूर्ण

व्योम gve_rx_मुक्त_rings(काष्ठा gve_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->rx_cfg.num_queues; i++)
		gve_rx_मुक्त_ring(priv, i);
पूर्ण

व्योम gve_rx_ग_लिखो_करोorbell(काष्ठा gve_priv *priv, काष्ठा gve_rx_ring *rx)
अणु
	u32 db_idx = be32_to_cpu(rx->q_resources->db_index);

	ioग_लिखो32be(rx->fill_cnt, &priv->db_bar2[db_idx]);
पूर्ण

अटल क्रमागत pkt_hash_types gve_rss_type(__be16 pkt_flags)
अणु
	अगर (likely(pkt_flags & (GVE_RXF_TCP | GVE_RXF_UDP)))
		वापस PKT_HASH_TYPE_L4;
	अगर (pkt_flags & (GVE_RXF_IPV4 | GVE_RXF_IPV6))
		वापस PKT_HASH_TYPE_L3;
	वापस PKT_HASH_TYPE_L2;
पूर्ण

अटल काष्ठा sk_buff *gve_rx_copy(काष्ठा net_device *dev,
				   काष्ठा napi_काष्ठा *napi,
				   काष्ठा gve_rx_slot_page_info *page_info,
				   u16 len)
अणु
	काष्ठा sk_buff *skb = napi_alloc_skb(napi, len);
	व्योम *va = page_info->page_address + GVE_RX_PAD +
		   (page_info->page_offset ? PAGE_SIZE / 2 : 0);

	अगर (unlikely(!skb))
		वापस शून्य;

	__skb_put(skb, len);

	skb_copy_to_linear_data(skb, va, len);

	skb->protocol = eth_type_trans(skb, dev);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *gve_rx_add_frags(काष्ठा napi_काष्ठा *napi,
					काष्ठा gve_rx_slot_page_info *page_info,
					u16 len)
अणु
	काष्ठा sk_buff *skb = napi_get_frags(napi);

	अगर (unlikely(!skb))
		वापस शून्य;

	skb_add_rx_frag(skb, 0, page_info->page,
			(page_info->page_offset ? PAGE_SIZE / 2 : 0) +
			GVE_RX_PAD, len, PAGE_SIZE / 2);

	वापस skb;
पूर्ण

अटल व्योम gve_rx_flip_buff(काष्ठा gve_rx_slot_page_info *page_info, __be64 *slot_addr)
अणु
	स्थिर __be64 offset = cpu_to_be64(PAGE_SIZE / 2);

	/* "flip" to other packet buffer on this page */
	page_info->page_offset ^= 0x1;
	*(slot_addr) ^= offset;
पूर्ण

अटल bool gve_rx_can_flip_buffers(काष्ठा net_device *netdev)
अणु
	वापस PAGE_SIZE == 4096
		? netdev->mtu + GVE_RX_PAD + ETH_HLEN <= PAGE_SIZE / 2 : false;
पूर्ण

अटल पूर्णांक gve_rx_can_recycle_buffer(काष्ठा page *page)
अणु
	पूर्णांक pagecount = page_count(page);

	/* This page is not being used by any SKBs - reuse */
	अगर (pagecount == 1)
		वापस 1;
	/* This page is still being used by an SKB - we can't reuse */
	अन्यथा अगर (pagecount >= 2)
		वापस 0;
	WARN(pagecount < 1, "Pagecount should never be < 1");
	वापस -1;
पूर्ण

अटल काष्ठा sk_buff *
gve_rx_raw_addressing(काष्ठा device *dev, काष्ठा net_device *netdev,
		      काष्ठा gve_rx_slot_page_info *page_info, u16 len,
		      काष्ठा napi_काष्ठा *napi,
		      जोड़ gve_rx_data_slot *data_slot)
अणु
	काष्ठा sk_buff *skb;

	skb = gve_rx_add_frags(napi, page_info, len);
	अगर (!skb)
		वापस शून्य;

	/* Optimistically stop the kernel from मुक्तing the page by increasing
	 * the page bias. We will check the refcount in refill to determine अगर
	 * we need to alloc a new page.
	 */
	get_page(page_info->page);

	वापस skb;
पूर्ण

अटल काष्ठा sk_buff *
gve_rx_qpl(काष्ठा device *dev, काष्ठा net_device *netdev,
	   काष्ठा gve_rx_ring *rx, काष्ठा gve_rx_slot_page_info *page_info,
	   u16 len, काष्ठा napi_काष्ठा *napi,
	   जोड़ gve_rx_data_slot *data_slot)
अणु
	काष्ठा sk_buff *skb;

	/* अगर raw_addressing mode is not enabled gvnic can only receive पूर्णांकo
	 * रेजिस्टरed segments. If the buffer can't be recycled, our only
	 * choice is to copy the data out of it so that we can वापस it to the
	 * device.
	 */
	अगर (page_info->can_flip) अणु
		skb = gve_rx_add_frags(napi, page_info, len);
		/* No poपूर्णांक in recycling अगर we didn't get the skb */
		अगर (skb) अणु
			/* Make sure that the page isn't मुक्तd. */
			get_page(page_info->page);
			gve_rx_flip_buff(page_info, &data_slot->qpl_offset);
		पूर्ण
	पूर्ण अन्यथा अणु
		skb = gve_rx_copy(netdev, napi, page_info, len);
		अगर (skb) अणु
			u64_stats_update_begin(&rx->statss);
			rx->rx_copied_pkt++;
			u64_stats_update_end(&rx->statss);
		पूर्ण
	पूर्ण
	वापस skb;
पूर्ण

अटल bool gve_rx(काष्ठा gve_rx_ring *rx, काष्ठा gve_rx_desc *rx_desc,
		   netdev_features_t feat, u32 idx)
अणु
	काष्ठा gve_rx_slot_page_info *page_info;
	काष्ठा gve_priv *priv = rx->gve;
	काष्ठा napi_काष्ठा *napi = &priv->ntfy_blocks[rx->ntfy_id].napi;
	काष्ठा net_device *dev = priv->dev;
	जोड़ gve_rx_data_slot *data_slot;
	काष्ठा sk_buff *skb = शून्य;
	dma_addr_t page_bus;
	u16 len;

	/* drop this packet */
	अगर (unlikely(rx_desc->flags_seq & GVE_RXF_ERR)) अणु
		u64_stats_update_begin(&rx->statss);
		rx->rx_desc_err_dropped_pkt++;
		u64_stats_update_end(&rx->statss);
		वापस false;
	पूर्ण

	len = be16_to_cpu(rx_desc->len) - GVE_RX_PAD;
	page_info = &rx->data.page_info[idx];

	data_slot = &rx->data.data_ring[idx];
	page_bus = (rx->data.raw_addressing) ?
			be64_to_cpu(data_slot->addr) & GVE_DATA_SLOT_ADDR_PAGE_MASK :
			rx->data.qpl->page_buses[idx];
	dma_sync_single_क्रम_cpu(&priv->pdev->dev, page_bus,
				PAGE_SIZE, DMA_FROM_DEVICE);

	अगर (len <= priv->rx_copyअवरोध) अणु
		/* Just copy small packets */
		skb = gve_rx_copy(dev, napi, page_info, len);
		u64_stats_update_begin(&rx->statss);
		rx->rx_copied_pkt++;
		rx->rx_copyअवरोध_pkt++;
		u64_stats_update_end(&rx->statss);
	पूर्ण अन्यथा अणु
		u8 can_flip = gve_rx_can_flip_buffers(dev);
		पूर्णांक recycle = 0;

		अगर (can_flip) अणु
			recycle = gve_rx_can_recycle_buffer(page_info->page);
			अगर (recycle < 0) अणु
				अगर (!rx->data.raw_addressing)
					gve_schedule_reset(priv);
				वापस false;
			पूर्ण
		पूर्ण

		page_info->can_flip = can_flip && recycle;
		अगर (rx->data.raw_addressing) अणु
			skb = gve_rx_raw_addressing(&priv->pdev->dev, dev,
						    page_info, len, napi,
						    data_slot);
		पूर्ण अन्यथा अणु
			skb = gve_rx_qpl(&priv->pdev->dev, dev, rx,
					 page_info, len, napi, data_slot);
		पूर्ण
	पूर्ण

	अगर (!skb) अणु
		u64_stats_update_begin(&rx->statss);
		rx->rx_skb_alloc_fail++;
		u64_stats_update_end(&rx->statss);
		वापस false;
	पूर्ण

	अगर (likely(feat & NETIF_F_RXCSUM)) अणु
		/* NIC passes up the partial sum */
		अगर (rx_desc->csum)
			skb->ip_summed = CHECKSUM_COMPLETE;
		अन्यथा
			skb->ip_summed = CHECKSUM_NONE;
		skb->csum = csum_unfold(rx_desc->csum);
	पूर्ण

	/* parse flags & pass relevant info up */
	अगर (likely(feat & NETIF_F_RXHASH) &&
	    gve_needs_rss(rx_desc->flags_seq))
		skb_set_hash(skb, be32_to_cpu(rx_desc->rss_hash),
			     gve_rss_type(rx_desc->flags_seq));

	अगर (skb_is_nonlinear(skb))
		napi_gro_frags(napi);
	अन्यथा
		napi_gro_receive(napi, skb);
	वापस true;
पूर्ण

अटल bool gve_rx_work_pending(काष्ठा gve_rx_ring *rx)
अणु
	काष्ठा gve_rx_desc *desc;
	__be16 flags_seq;
	u32 next_idx;

	next_idx = rx->cnt & rx->mask;
	desc = rx->desc.desc_ring + next_idx;

	flags_seq = desc->flags_seq;
	/* Make sure we have synchronized the seq no with the device */
	smp_rmb();

	वापस (GVE_SEQNO(flags_seq) == rx->desc.seqno);
पूर्ण

अटल bool gve_rx_refill_buffers(काष्ठा gve_priv *priv, काष्ठा gve_rx_ring *rx)
अणु
	पूर्णांक refill_target = rx->mask + 1;
	u32 fill_cnt = rx->fill_cnt;

	जबतक (fill_cnt - rx->cnt < refill_target) अणु
		काष्ठा gve_rx_slot_page_info *page_info;
		u32 idx = fill_cnt & rx->mask;

		page_info = &rx->data.page_info[idx];
		अगर (page_info->can_flip) अणु
			/* The other half of the page is मुक्त because it was
			 * मुक्त when we processed the descriptor. Flip to it.
			 */
			जोड़ gve_rx_data_slot *data_slot =
						&rx->data.data_ring[idx];

			gve_rx_flip_buff(page_info, &data_slot->addr);
			page_info->can_flip = 0;
		पूर्ण अन्यथा अणु
			/* It is possible that the networking stack has alपढ़ोy
			 * finished processing all outstanding packets in the buffer
			 * and it can be reused.
			 * Flipping is unnecessary here - अगर the networking stack still
			 * owns half the page it is impossible to tell which half. Either
			 * the whole page is मुक्त or it needs to be replaced.
			 */
			पूर्णांक recycle = gve_rx_can_recycle_buffer(page_info->page);

			अगर (recycle < 0) अणु
				अगर (!rx->data.raw_addressing)
					gve_schedule_reset(priv);
				वापस false;
			पूर्ण
			अगर (!recycle) अणु
				/* We can't reuse the buffer - alloc a new one*/
				जोड़ gve_rx_data_slot *data_slot =
						&rx->data.data_ring[idx];
				काष्ठा device *dev = &priv->pdev->dev;

				gve_rx_मुक्त_buffer(dev, page_info, data_slot);
				page_info->page = शून्य;
				अगर (gve_rx_alloc_buffer(priv, dev, page_info, data_slot))
					अवरोध;
			पूर्ण
		पूर्ण
		fill_cnt++;
	पूर्ण
	rx->fill_cnt = fill_cnt;
	वापस true;
पूर्ण

bool gve_clean_rx_करोne(काष्ठा gve_rx_ring *rx, पूर्णांक budget,
		       netdev_features_t feat)
अणु
	काष्ठा gve_priv *priv = rx->gve;
	u32 work_करोne = 0, packets = 0;
	काष्ठा gve_rx_desc *desc;
	u32 cnt = rx->cnt;
	u32 idx = cnt & rx->mask;
	u64 bytes = 0;

	desc = rx->desc.desc_ring + idx;
	जबतक ((GVE_SEQNO(desc->flags_seq) == rx->desc.seqno) &&
	       work_करोne < budget) अणु
		bool dropped;

		netअगर_info(priv, rx_status, priv->dev,
			   "[%d] idx=%d desc=%p desc->flags_seq=0x%x\n",
			   rx->q_num, idx, desc, desc->flags_seq);
		netअगर_info(priv, rx_status, priv->dev,
			   "[%d] seqno=%d rx->desc.seqno=%d\n",
			   rx->q_num, GVE_SEQNO(desc->flags_seq),
			   rx->desc.seqno);
		dropped = !gve_rx(rx, desc, feat, idx);
		अगर (!dropped) अणु
			bytes += be16_to_cpu(desc->len) - GVE_RX_PAD;
			packets++;
		पूर्ण
		cnt++;
		idx = cnt & rx->mask;
		desc = rx->desc.desc_ring + idx;
		rx->desc.seqno = gve_next_seqno(rx->desc.seqno);
		work_करोne++;
	पूर्ण

	अगर (!work_करोne && rx->fill_cnt - cnt > rx->db_threshold)
		वापस false;

	u64_stats_update_begin(&rx->statss);
	rx->rpackets += packets;
	rx->rbytes += bytes;
	u64_stats_update_end(&rx->statss);
	rx->cnt = cnt;

	/* restock ring slots */
	अगर (!rx->data.raw_addressing) अणु
		/* In QPL mode buffs are refilled as the desc are processed */
		rx->fill_cnt += work_करोne;
	पूर्ण अन्यथा अगर (rx->fill_cnt - cnt <= rx->db_threshold) अणु
		/* In raw addressing mode buffs are only refilled अगर the avail
		 * falls below a threshold.
		 */
		अगर (!gve_rx_refill_buffers(priv, rx))
			वापस false;

		/* If we were not able to completely refill buffers, we'll want
		 * to schedule this queue क्रम work again to refill buffers.
		 */
		अगर (rx->fill_cnt - cnt <= rx->db_threshold) अणु
			gve_rx_ग_लिखो_करोorbell(priv, rx);
			वापस true;
		पूर्ण
	पूर्ण

	gve_rx_ग_लिखो_करोorbell(priv, rx);
	वापस gve_rx_work_pending(rx);
पूर्ण

bool gve_rx_poll(काष्ठा gve_notअगरy_block *block, पूर्णांक budget)
अणु
	काष्ठा gve_rx_ring *rx = block->rx;
	netdev_features_t feat;
	bool repoll = false;

	feat = block->napi.dev->features;

	/* If budget is 0, करो all the work */
	अगर (budget == 0)
		budget = पूर्णांक_उच्च;

	अगर (budget > 0)
		repoll |= gve_clean_rx_करोne(rx, budget, feat);
	अन्यथा
		repoll |= gve_rx_work_pending(rx);
	वापस repoll;
पूर्ण
