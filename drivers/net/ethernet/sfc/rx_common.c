<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2018 Solarflare Communications Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy it
 * under the terms of the GNU General Public License version 2 as published
 * by the Free Software Foundation, incorporated herein by reference.
 */

#समावेश "net_driver.h"
#समावेश <linux/module.h>
#समावेश <linux/iommu.h>
#समावेश "efx.h"
#समावेश "nic.h"
#समावेश "rx_common.h"

/* This is the percentage fill level below which new RX descriptors
 * will be added to the RX descriptor ring.
 */
अटल अचिन्हित पूर्णांक rx_refill_threshold;
module_param(rx_refill_threshold, uपूर्णांक, 0444);
MODULE_PARM_DESC(rx_refill_threshold,
		 "RX descriptor ring refill threshold (%)");

/* Number of RX buffers to recycle pages क्रम.  When creating the RX page recycle
 * ring, this number is भागided by the number of buffers per page to calculate
 * the number of pages to store in the RX page recycle ring.
 */
#घोषणा EFX_RECYCLE_RING_SIZE_IOMMU 4096
#घोषणा EFX_RECYCLE_RING_SIZE_NOIOMMU (2 * EFX_RX_PREFERRED_BATCH)

/* RX maximum head room required.
 *
 * This must be at least 1 to prevent overflow, plus one packet-worth
 * to allow pipelined receives.
 */
#घोषणा EFX_RXD_HEAD_ROOM (1 + EFX_RX_MAX_FRAGS)

/* Check the RX page recycle ring क्रम a page that can be reused. */
अटल काष्ठा page *efx_reuse_page(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	काष्ठा efx_rx_page_state *state;
	अचिन्हित पूर्णांक index;
	काष्ठा page *page;

	index = rx_queue->page_हटाओ & rx_queue->page_ptr_mask;
	page = rx_queue->page_ring[index];
	अगर (page == शून्य)
		वापस शून्य;

	rx_queue->page_ring[index] = शून्य;
	/* page_हटाओ cannot exceed page_add. */
	अगर (rx_queue->page_हटाओ != rx_queue->page_add)
		++rx_queue->page_हटाओ;

	/* If page_count is 1 then we hold the only reference to this page. */
	अगर (page_count(page) == 1) अणु
		++rx_queue->page_recycle_count;
		वापस page;
	पूर्ण अन्यथा अणु
		state = page_address(page);
		dma_unmap_page(&efx->pci_dev->dev, state->dma_addr,
			       PAGE_SIZE << efx->rx_buffer_order,
			       DMA_FROM_DEVICE);
		put_page(page);
		++rx_queue->page_recycle_failed;
	पूर्ण

	वापस शून्य;
पूर्ण

/* Attempt to recycle the page अगर there is an RX recycle ring; the page can
 * only be added अगर this is the final RX buffer, to prevent pages being used in
 * the descriptor ring and appearing in the recycle ring simultaneously.
 */
अटल व्योम efx_recycle_rx_page(काष्ठा efx_channel *channel,
				काष्ठा efx_rx_buffer *rx_buf)
अणु
	काष्ठा efx_rx_queue *rx_queue = efx_channel_get_rx_queue(channel);
	काष्ठा efx_nic *efx = rx_queue->efx;
	काष्ठा page *page = rx_buf->page;
	अचिन्हित पूर्णांक index;

	/* Only recycle the page after processing the final buffer. */
	अगर (!(rx_buf->flags & EFX_RX_BUF_LAST_IN_PAGE))
		वापस;

	index = rx_queue->page_add & rx_queue->page_ptr_mask;
	अगर (rx_queue->page_ring[index] == शून्य) अणु
		अचिन्हित पूर्णांक पढ़ो_index = rx_queue->page_हटाओ &
			rx_queue->page_ptr_mask;

		/* The next slot in the recycle ring is available, but
		 * increment page_हटाओ अगर the पढ़ो poपूर्णांकer currently
		 * poपूर्णांकs here.
		 */
		अगर (पढ़ो_index == index)
			++rx_queue->page_हटाओ;
		rx_queue->page_ring[index] = page;
		++rx_queue->page_add;
		वापस;
	पूर्ण
	++rx_queue->page_recycle_full;
	efx_unmap_rx_buffer(efx, rx_buf);
	put_page(rx_buf->page);
पूर्ण

/* Recycle the pages that are used by buffers that have just been received. */
व्योम efx_recycle_rx_pages(काष्ठा efx_channel *channel,
			  काष्ठा efx_rx_buffer *rx_buf,
			  अचिन्हित पूर्णांक n_frags)
अणु
	काष्ठा efx_rx_queue *rx_queue = efx_channel_get_rx_queue(channel);

	करो अणु
		efx_recycle_rx_page(channel, rx_buf);
		rx_buf = efx_rx_buf_next(rx_queue, rx_buf);
	पूर्ण जबतक (--n_frags);
पूर्ण

व्योम efx_discard_rx_packet(काष्ठा efx_channel *channel,
			   काष्ठा efx_rx_buffer *rx_buf,
			   अचिन्हित पूर्णांक n_frags)
अणु
	काष्ठा efx_rx_queue *rx_queue = efx_channel_get_rx_queue(channel);

	efx_recycle_rx_pages(channel, rx_buf, n_frags);

	efx_मुक्त_rx_buffers(rx_queue, rx_buf, n_frags);
पूर्ण

अटल व्योम efx_init_rx_recycle_ring(काष्ठा efx_rx_queue *rx_queue)
अणु
	अचिन्हित पूर्णांक bufs_in_recycle_ring, page_ring_size;
	काष्ठा efx_nic *efx = rx_queue->efx;

	/* Set the RX recycle ring size */
#अगर_घोषित CONFIG_PPC64
	bufs_in_recycle_ring = EFX_RECYCLE_RING_SIZE_IOMMU;
#अन्यथा
	अगर (iommu_present(&pci_bus_type))
		bufs_in_recycle_ring = EFX_RECYCLE_RING_SIZE_IOMMU;
	अन्यथा
		bufs_in_recycle_ring = EFX_RECYCLE_RING_SIZE_NOIOMMU;
#पूर्ण_अगर /* CONFIG_PPC64 */

	page_ring_size = roundup_घात_of_two(bufs_in_recycle_ring /
					    efx->rx_bufs_per_page);
	rx_queue->page_ring = kसुस्मृति(page_ring_size,
				      माप(*rx_queue->page_ring), GFP_KERNEL);
	rx_queue->page_ptr_mask = page_ring_size - 1;
पूर्ण

अटल व्योम efx_fini_rx_recycle_ring(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	पूर्णांक i;

	/* Unmap and release the pages in the recycle ring. Remove the ring. */
	क्रम (i = 0; i <= rx_queue->page_ptr_mask; i++) अणु
		काष्ठा page *page = rx_queue->page_ring[i];
		काष्ठा efx_rx_page_state *state;

		अगर (page == शून्य)
			जारी;

		state = page_address(page);
		dma_unmap_page(&efx->pci_dev->dev, state->dma_addr,
			       PAGE_SIZE << efx->rx_buffer_order,
			       DMA_FROM_DEVICE);
		put_page(page);
	पूर्ण
	kमुक्त(rx_queue->page_ring);
	rx_queue->page_ring = शून्य;
पूर्ण

अटल व्योम efx_fini_rx_buffer(काष्ठा efx_rx_queue *rx_queue,
			       काष्ठा efx_rx_buffer *rx_buf)
अणु
	/* Release the page reference we hold क्रम the buffer. */
	अगर (rx_buf->page)
		put_page(rx_buf->page);

	/* If this is the last buffer in a page, unmap and मुक्त it. */
	अगर (rx_buf->flags & EFX_RX_BUF_LAST_IN_PAGE) अणु
		efx_unmap_rx_buffer(rx_queue->efx, rx_buf);
		efx_मुक्त_rx_buffers(rx_queue, rx_buf, 1);
	पूर्ण
	rx_buf->page = शून्य;
पूर्ण

पूर्णांक efx_probe_rx_queue(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	अचिन्हित पूर्णांक entries;
	पूर्णांक rc;

	/* Create the smallest घातer-of-two aligned ring */
	entries = max(roundup_घात_of_two(efx->rxq_entries), EFX_MIN_DMAQ_SIZE);
	EFX_WARN_ON_PARANOID(entries > EFX_MAX_DMAQ_SIZE);
	rx_queue->ptr_mask = entries - 1;

	netअगर_dbg(efx, probe, efx->net_dev,
		  "creating RX queue %d size %#x mask %#x\n",
		  efx_rx_queue_index(rx_queue), efx->rxq_entries,
		  rx_queue->ptr_mask);

	/* Allocate RX buffers */
	rx_queue->buffer = kसुस्मृति(entries, माप(*rx_queue->buffer),
				   GFP_KERNEL);
	अगर (!rx_queue->buffer)
		वापस -ENOMEM;

	rc = efx_nic_probe_rx(rx_queue);
	अगर (rc) अणु
		kमुक्त(rx_queue->buffer);
		rx_queue->buffer = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

व्योम efx_init_rx_queue(काष्ठा efx_rx_queue *rx_queue)
अणु
	अचिन्हित पूर्णांक max_fill, trigger, max_trigger;
	काष्ठा efx_nic *efx = rx_queue->efx;
	पूर्णांक rc = 0;

	netअगर_dbg(rx_queue->efx, drv, rx_queue->efx->net_dev,
		  "initialising RX queue %d\n", efx_rx_queue_index(rx_queue));

	/* Initialise ptr fields */
	rx_queue->added_count = 0;
	rx_queue->notअगरied_count = 0;
	rx_queue->हटाओd_count = 0;
	rx_queue->min_fill = -1U;
	efx_init_rx_recycle_ring(rx_queue);

	rx_queue->page_हटाओ = 0;
	rx_queue->page_add = rx_queue->page_ptr_mask + 1;
	rx_queue->page_recycle_count = 0;
	rx_queue->page_recycle_failed = 0;
	rx_queue->page_recycle_full = 0;

	/* Initialise limit fields */
	max_fill = efx->rxq_entries - EFX_RXD_HEAD_ROOM;
	max_trigger =
		max_fill - efx->rx_pages_per_batch * efx->rx_bufs_per_page;
	अगर (rx_refill_threshold != 0) अणु
		trigger = max_fill * min(rx_refill_threshold, 100U) / 100U;
		अगर (trigger > max_trigger)
			trigger = max_trigger;
	पूर्ण अन्यथा अणु
		trigger = max_trigger;
	पूर्ण

	rx_queue->max_fill = max_fill;
	rx_queue->fast_fill_trigger = trigger;
	rx_queue->refill_enabled = true;

	/* Initialise XDP queue inक्रमmation */
	rc = xdp_rxq_info_reg(&rx_queue->xdp_rxq_info, efx->net_dev,
			      rx_queue->core_index, 0);

	अगर (rc) अणु
		netअगर_err(efx, rx_err, efx->net_dev,
			  "Failure to initialise XDP queue information rc=%d\n",
			  rc);
		efx->xdp_rxq_info_failed = true;
	पूर्ण अन्यथा अणु
		rx_queue->xdp_rxq_info_valid = true;
	पूर्ण

	/* Set up RX descriptor ring */
	efx_nic_init_rx(rx_queue);
पूर्ण

व्योम efx_fini_rx_queue(काष्ठा efx_rx_queue *rx_queue)
अणु
	काष्ठा efx_rx_buffer *rx_buf;
	पूर्णांक i;

	netअगर_dbg(rx_queue->efx, drv, rx_queue->efx->net_dev,
		  "shutting down RX queue %d\n", efx_rx_queue_index(rx_queue));

	del_समयr_sync(&rx_queue->slow_fill);

	/* Release RX buffers from the current पढ़ो ptr to the ग_लिखो ptr */
	अगर (rx_queue->buffer) अणु
		क्रम (i = rx_queue->हटाओd_count; i < rx_queue->added_count;
		     i++) अणु
			अचिन्हित पूर्णांक index = i & rx_queue->ptr_mask;

			rx_buf = efx_rx_buffer(rx_queue, index);
			efx_fini_rx_buffer(rx_queue, rx_buf);
		पूर्ण
	पूर्ण

	efx_fini_rx_recycle_ring(rx_queue);

	अगर (rx_queue->xdp_rxq_info_valid)
		xdp_rxq_info_unreg(&rx_queue->xdp_rxq_info);

	rx_queue->xdp_rxq_info_valid = false;
पूर्ण

व्योम efx_हटाओ_rx_queue(काष्ठा efx_rx_queue *rx_queue)
अणु
	netअगर_dbg(rx_queue->efx, drv, rx_queue->efx->net_dev,
		  "destroying RX queue %d\n", efx_rx_queue_index(rx_queue));

	efx_nic_हटाओ_rx(rx_queue);

	kमुक्त(rx_queue->buffer);
	rx_queue->buffer = शून्य;
पूर्ण

/* Unmap a DMA-mapped page.  This function is only called क्रम the final RX
 * buffer in a page.
 */
व्योम efx_unmap_rx_buffer(काष्ठा efx_nic *efx,
			 काष्ठा efx_rx_buffer *rx_buf)
अणु
	काष्ठा page *page = rx_buf->page;

	अगर (page) अणु
		काष्ठा efx_rx_page_state *state = page_address(page);

		dma_unmap_page(&efx->pci_dev->dev,
			       state->dma_addr,
			       PAGE_SIZE << efx->rx_buffer_order,
			       DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

व्योम efx_मुक्त_rx_buffers(काष्ठा efx_rx_queue *rx_queue,
			 काष्ठा efx_rx_buffer *rx_buf,
			 अचिन्हित पूर्णांक num_bufs)
अणु
	करो अणु
		अगर (rx_buf->page) अणु
			put_page(rx_buf->page);
			rx_buf->page = शून्य;
		पूर्ण
		rx_buf = efx_rx_buf_next(rx_queue, rx_buf);
	पूर्ण जबतक (--num_bufs);
पूर्ण

व्योम efx_rx_slow_fill(काष्ठा समयr_list *t)
अणु
	काष्ठा efx_rx_queue *rx_queue = from_समयr(rx_queue, t, slow_fill);

	/* Post an event to cause NAPI to run and refill the queue */
	efx_nic_generate_fill_event(rx_queue);
	++rx_queue->slow_fill_count;
पूर्ण

व्योम efx_schedule_slow_fill(काष्ठा efx_rx_queue *rx_queue)
अणु
	mod_समयr(&rx_queue->slow_fill, jअगरfies + msecs_to_jअगरfies(10));
पूर्ण

/* efx_init_rx_buffers - create EFX_RX_BATCH page-based RX buffers
 *
 * @rx_queue:		Efx RX queue
 *
 * This allocates a batch of pages, maps them क्रम DMA, and populates
 * काष्ठा efx_rx_buffers क्रम each one. Return a negative error code or
 * 0 on success. If a single page can be used क्रम multiple buffers,
 * then the page will either be inserted fully, or not at all.
 */
अटल पूर्णांक efx_init_rx_buffers(काष्ठा efx_rx_queue *rx_queue, bool atomic)
अणु
	अचिन्हित पूर्णांक page_offset, index, count;
	काष्ठा efx_nic *efx = rx_queue->efx;
	काष्ठा efx_rx_page_state *state;
	काष्ठा efx_rx_buffer *rx_buf;
	dma_addr_t dma_addr;
	काष्ठा page *page;

	count = 0;
	करो अणु
		page = efx_reuse_page(rx_queue);
		अगर (page == शून्य) अणु
			page = alloc_pages(__GFP_COMP |
					   (atomic ? GFP_ATOMIC : GFP_KERNEL),
					   efx->rx_buffer_order);
			अगर (unlikely(page == शून्य))
				वापस -ENOMEM;
			dma_addr =
				dma_map_page(&efx->pci_dev->dev, page, 0,
					     PAGE_SIZE << efx->rx_buffer_order,
					     DMA_FROM_DEVICE);
			अगर (unlikely(dma_mapping_error(&efx->pci_dev->dev,
						       dma_addr))) अणु
				__मुक्त_pages(page, efx->rx_buffer_order);
				वापस -EIO;
			पूर्ण
			state = page_address(page);
			state->dma_addr = dma_addr;
		पूर्ण अन्यथा अणु
			state = page_address(page);
			dma_addr = state->dma_addr;
		पूर्ण

		dma_addr += माप(काष्ठा efx_rx_page_state);
		page_offset = माप(काष्ठा efx_rx_page_state);

		करो अणु
			index = rx_queue->added_count & rx_queue->ptr_mask;
			rx_buf = efx_rx_buffer(rx_queue, index);
			rx_buf->dma_addr = dma_addr + efx->rx_ip_align +
					   EFX_XDP_HEADROOM;
			rx_buf->page = page;
			rx_buf->page_offset = page_offset + efx->rx_ip_align +
					      EFX_XDP_HEADROOM;
			rx_buf->len = efx->rx_dma_len;
			rx_buf->flags = 0;
			++rx_queue->added_count;
			get_page(page);
			dma_addr += efx->rx_page_buf_step;
			page_offset += efx->rx_page_buf_step;
		पूर्ण जबतक (page_offset + efx->rx_page_buf_step <= PAGE_SIZE);

		rx_buf->flags = EFX_RX_BUF_LAST_IN_PAGE;
	पूर्ण जबतक (++count < efx->rx_pages_per_batch);

	वापस 0;
पूर्ण

व्योम efx_rx_config_page_split(काष्ठा efx_nic *efx)
अणु
	efx->rx_page_buf_step = ALIGN(efx->rx_dma_len + efx->rx_ip_align +
				      EFX_XDP_HEADROOM + EFX_XDP_TAILROOM,
				      EFX_RX_BUF_ALIGNMENT);
	efx->rx_bufs_per_page = efx->rx_buffer_order ? 1 :
		((PAGE_SIZE - माप(काष्ठा efx_rx_page_state)) /
		efx->rx_page_buf_step);
	efx->rx_buffer_truesize = (PAGE_SIZE << efx->rx_buffer_order) /
		efx->rx_bufs_per_page;
	efx->rx_pages_per_batch = DIV_ROUND_UP(EFX_RX_PREFERRED_BATCH,
					       efx->rx_bufs_per_page);
पूर्ण

/* efx_fast_push_rx_descriptors - push new RX descriptors quickly
 * @rx_queue:		RX descriptor queue
 *
 * This will aim to fill the RX descriptor queue up to
 * @rx_queue->@max_fill. If there is insufficient atomic
 * memory to करो so, a slow fill will be scheduled.
 *
 * The caller must provide serialisation (none is used here). In practise,
 * this means this function must run from the NAPI handler, or be called
 * when NAPI is disabled.
 */
व्योम efx_fast_push_rx_descriptors(काष्ठा efx_rx_queue *rx_queue, bool atomic)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	अचिन्हित पूर्णांक fill_level, batch_size;
	पूर्णांक space, rc = 0;

	अगर (!rx_queue->refill_enabled)
		वापस;

	/* Calculate current fill level, and निकास अगर we करोn't need to fill */
	fill_level = (rx_queue->added_count - rx_queue->हटाओd_count);
	EFX_WARN_ON_ONCE_PARANOID(fill_level > rx_queue->efx->rxq_entries);
	अगर (fill_level >= rx_queue->fast_fill_trigger)
		जाओ out;

	/* Record minimum fill level */
	अगर (unlikely(fill_level < rx_queue->min_fill)) अणु
		अगर (fill_level)
			rx_queue->min_fill = fill_level;
	पूर्ण

	batch_size = efx->rx_pages_per_batch * efx->rx_bufs_per_page;
	space = rx_queue->max_fill - fill_level;
	EFX_WARN_ON_ONCE_PARANOID(space < batch_size);

	netअगर_vdbg(rx_queue->efx, rx_status, rx_queue->efx->net_dev,
		   "RX queue %d fast-filling descriptor ring from"
		   " level %d to level %d\n",
		   efx_rx_queue_index(rx_queue), fill_level,
		   rx_queue->max_fill);

	करो अणु
		rc = efx_init_rx_buffers(rx_queue, atomic);
		अगर (unlikely(rc)) अणु
			/* Ensure that we करोn't leave the rx queue empty */
			efx_schedule_slow_fill(rx_queue);
			जाओ out;
		पूर्ण
	पूर्ण जबतक ((space -= batch_size) >= batch_size);

	netअगर_vdbg(rx_queue->efx, rx_status, rx_queue->efx->net_dev,
		   "RX queue %d fast-filled descriptor ring "
		   "to level %d\n", efx_rx_queue_index(rx_queue),
		   rx_queue->added_count - rx_queue->हटाओd_count);

 out:
	अगर (rx_queue->notअगरied_count != rx_queue->added_count)
		efx_nic_notअगरy_rx_desc(rx_queue);
पूर्ण

/* Pass a received packet up through GRO.  GRO can handle pages
 * regardless of checksum state and skbs with a good checksum.
 */
व्योम
efx_rx_packet_gro(काष्ठा efx_channel *channel, काष्ठा efx_rx_buffer *rx_buf,
		  अचिन्हित पूर्णांक n_frags, u8 *eh, __wsum csum)
अणु
	काष्ठा napi_काष्ठा *napi = &channel->napi_str;
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा sk_buff *skb;

	skb = napi_get_frags(napi);
	अगर (unlikely(!skb)) अणु
		काष्ठा efx_rx_queue *rx_queue;

		rx_queue = efx_channel_get_rx_queue(channel);
		efx_मुक्त_rx_buffers(rx_queue, rx_buf, n_frags);
		वापस;
	पूर्ण

	अगर (efx->net_dev->features & NETIF_F_RXHASH &&
	    efx_rx_buf_hash_valid(efx, eh))
		skb_set_hash(skb, efx_rx_buf_hash(efx, eh),
			     PKT_HASH_TYPE_L3);
	अगर (csum) अणु
		skb->csum = csum;
		skb->ip_summed = CHECKSUM_COMPLETE;
	पूर्ण अन्यथा अणु
		skb->ip_summed = ((rx_buf->flags & EFX_RX_PKT_CSUMMED) ?
				  CHECKSUM_UNNECESSARY : CHECKSUM_NONE);
	पूर्ण
	skb->csum_level = !!(rx_buf->flags & EFX_RX_PKT_CSUM_LEVEL);

	क्रम (;;) अणु
		skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
				   rx_buf->page, rx_buf->page_offset,
				   rx_buf->len);
		rx_buf->page = शून्य;
		skb->len += rx_buf->len;
		अगर (skb_shinfo(skb)->nr_frags == n_frags)
			अवरोध;

		rx_buf = efx_rx_buf_next(&channel->rx_queue, rx_buf);
	पूर्ण

	skb->data_len = skb->len;
	skb->truesize += n_frags * efx->rx_buffer_truesize;

	skb_record_rx_queue(skb, channel->rx_queue.core_index);

	napi_gro_frags(napi);
पूर्ण

/* RSS contexts.  We're using linked lists and crappy O(n) algorithms, because
 * (a) this is an infrequent control-plane operation and (b) n is small (max 64)
 */
काष्ठा efx_rss_context *efx_alloc_rss_context_entry(काष्ठा efx_nic *efx)
अणु
	काष्ठा list_head *head = &efx->rss_context.list;
	काष्ठा efx_rss_context *ctx, *new;
	u32 id = 1; /* Don't use zero, that refers to the master RSS context */

	WARN_ON(!mutex_is_locked(&efx->rss_lock));

	/* Search क्रम first gap in the numbering */
	list_क्रम_each_entry(ctx, head, list) अणु
		अगर (ctx->user_id != id)
			अवरोध;
		id++;
		/* Check क्रम wrap.  If this happens, we have nearly 2^32
		 * allocated RSS contexts, which seems unlikely.
		 */
		अगर (WARN_ON_ONCE(!id))
			वापस शून्य;
	पूर्ण

	/* Create the new entry */
	new = kदो_स्मृति(माप(*new), GFP_KERNEL);
	अगर (!new)
		वापस शून्य;
	new->context_id = EFX_MCDI_RSS_CONTEXT_INVALID;
	new->rx_hash_udp_4tuple = false;

	/* Insert the new entry पूर्णांकo the gap */
	new->user_id = id;
	list_add_tail(&new->list, &ctx->list);
	वापस new;
पूर्ण

काष्ठा efx_rss_context *efx_find_rss_context_entry(काष्ठा efx_nic *efx, u32 id)
अणु
	काष्ठा list_head *head = &efx->rss_context.list;
	काष्ठा efx_rss_context *ctx;

	WARN_ON(!mutex_is_locked(&efx->rss_lock));

	list_क्रम_each_entry(ctx, head, list)
		अगर (ctx->user_id == id)
			वापस ctx;
	वापस शून्य;
पूर्ण

व्योम efx_मुक्त_rss_context_entry(काष्ठा efx_rss_context *ctx)
अणु
	list_del(&ctx->list);
	kमुक्त(ctx);
पूर्ण

व्योम efx_set_शेष_rx_indir_table(काष्ठा efx_nic *efx,
				    काष्ठा efx_rss_context *ctx)
अणु
	माप_प्रकार i;

	क्रम (i = 0; i < ARRAY_SIZE(ctx->rx_indir_table); i++)
		ctx->rx_indir_table[i] =
			ethtool_rxfh_indir_शेष(i, efx->rss_spपढ़ो);
पूर्ण

/**
 * efx_filter_is_mc_recipient - test whether spec is a multicast recipient
 * @spec: Specअगरication to test
 *
 * Return: %true अगर the specअगरication is a non-drop RX filter that
 * matches a local MAC address I/G bit value of 1 or matches a local
 * IPv4 or IPv6 address value in the respective multicast address
 * range.  Otherwise %false.
 */
bool efx_filter_is_mc_recipient(स्थिर काष्ठा efx_filter_spec *spec)
अणु
	अगर (!(spec->flags & EFX_FILTER_FLAG_RX) ||
	    spec->dmaq_id == EFX_FILTER_RX_DMAQ_ID_DROP)
		वापस false;

	अगर (spec->match_flags &
	    (EFX_FILTER_MATCH_LOC_MAC | EFX_FILTER_MATCH_LOC_MAC_IG) &&
	    is_multicast_ether_addr(spec->loc_mac))
		वापस true;

	अगर ((spec->match_flags &
	     (EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_LOC_HOST)) ==
	    (EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_LOC_HOST)) अणु
		अगर (spec->ether_type == htons(ETH_P_IP) &&
		    ipv4_is_multicast(spec->loc_host[0]))
			वापस true;
		अगर (spec->ether_type == htons(ETH_P_IPV6) &&
		    ((स्थिर u8 *)spec->loc_host)[0] == 0xff)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

bool efx_filter_spec_equal(स्थिर काष्ठा efx_filter_spec *left,
			   स्थिर काष्ठा efx_filter_spec *right)
अणु
	अगर ((left->match_flags ^ right->match_flags) |
	    ((left->flags ^ right->flags) &
	     (EFX_FILTER_FLAG_RX | EFX_FILTER_FLAG_TX)))
		वापस false;

	वापस स_भेद(&left->outer_vid, &right->outer_vid,
		      माप(काष्ठा efx_filter_spec) -
		      दुरत्व(काष्ठा efx_filter_spec, outer_vid)) == 0;
पूर्ण

u32 efx_filter_spec_hash(स्थिर काष्ठा efx_filter_spec *spec)
अणु
	BUILD_BUG_ON(दुरत्व(काष्ठा efx_filter_spec, outer_vid) & 3);
	वापस jhash2((स्थिर u32 *)&spec->outer_vid,
		      (माप(काष्ठा efx_filter_spec) -
		       दुरत्व(काष्ठा efx_filter_spec, outer_vid)) / 4,
		      0);
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL
bool efx_rps_check_rule(काष्ठा efx_arfs_rule *rule, अचिन्हित पूर्णांक filter_idx,
			bool *क्रमce)
अणु
	अगर (rule->filter_id == EFX_ARFS_FILTER_ID_PENDING) अणु
		/* ARFS is currently updating this entry, leave it */
		वापस false;
	पूर्ण
	अगर (rule->filter_id == EFX_ARFS_FILTER_ID_ERROR) अणु
		/* ARFS tried and failed to update this, so it's probably out
		 * of date.  Remove the filter and the ARFS rule entry.
		 */
		rule->filter_id = EFX_ARFS_FILTER_ID_REMOVING;
		*क्रमce = true;
		वापस true;
	पूर्ण अन्यथा अगर (WARN_ON(rule->filter_id != filter_idx)) अणु /* can't happen */
		/* ARFS has moved on, so old filter is not needed.  Since we did
		 * not mark the rule with EFX_ARFS_FILTER_ID_REMOVING, it will
		 * not be हटाओd by efx_rps_hash_del() subsequently.
		 */
		*क्रमce = true;
		वापस true;
	पूर्ण
	/* Remove it अगरf ARFS wants to. */
	वापस true;
पूर्ण

अटल
काष्ठा hlist_head *efx_rps_hash_bucket(काष्ठा efx_nic *efx,
				       स्थिर काष्ठा efx_filter_spec *spec)
अणु
	u32 hash = efx_filter_spec_hash(spec);

	lockdep_निश्चित_held(&efx->rps_hash_lock);
	अगर (!efx->rps_hash_table)
		वापस शून्य;
	वापस &efx->rps_hash_table[hash % EFX_ARFS_HASH_TABLE_SIZE];
पूर्ण

काष्ठा efx_arfs_rule *efx_rps_hash_find(काष्ठा efx_nic *efx,
					स्थिर काष्ठा efx_filter_spec *spec)
अणु
	काष्ठा efx_arfs_rule *rule;
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *node;

	head = efx_rps_hash_bucket(efx, spec);
	अगर (!head)
		वापस शून्य;
	hlist_क्रम_each(node, head) अणु
		rule = container_of(node, काष्ठा efx_arfs_rule, node);
		अगर (efx_filter_spec_equal(spec, &rule->spec))
			वापस rule;
	पूर्ण
	वापस शून्य;
पूर्ण

काष्ठा efx_arfs_rule *efx_rps_hash_add(काष्ठा efx_nic *efx,
				       स्थिर काष्ठा efx_filter_spec *spec,
				       bool *new)
अणु
	काष्ठा efx_arfs_rule *rule;
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *node;

	head = efx_rps_hash_bucket(efx, spec);
	अगर (!head)
		वापस शून्य;
	hlist_क्रम_each(node, head) अणु
		rule = container_of(node, काष्ठा efx_arfs_rule, node);
		अगर (efx_filter_spec_equal(spec, &rule->spec)) अणु
			*new = false;
			वापस rule;
		पूर्ण
	पूर्ण
	rule = kदो_स्मृति(माप(*rule), GFP_ATOMIC);
	*new = true;
	अगर (rule) अणु
		स_नकल(&rule->spec, spec, माप(rule->spec));
		hlist_add_head(&rule->node, head);
	पूर्ण
	वापस rule;
पूर्ण

व्योम efx_rps_hash_del(काष्ठा efx_nic *efx, स्थिर काष्ठा efx_filter_spec *spec)
अणु
	काष्ठा efx_arfs_rule *rule;
	काष्ठा hlist_head *head;
	काष्ठा hlist_node *node;

	head = efx_rps_hash_bucket(efx, spec);
	अगर (WARN_ON(!head))
		वापस;
	hlist_क्रम_each(node, head) अणु
		rule = container_of(node, काष्ठा efx_arfs_rule, node);
		अगर (efx_filter_spec_equal(spec, &rule->spec)) अणु
			/* Someone alपढ़ोy reused the entry.  We know that अगर
			 * this check करोesn't fire (i.e. filter_id == REMOVING)
			 * then the REMOVING mark was put there by our caller,
			 * because caller is holding a lock on filter table and
			 * only holders of that lock set REMOVING.
			 */
			अगर (rule->filter_id != EFX_ARFS_FILTER_ID_REMOVING)
				वापस;
			hlist_del(node);
			kमुक्त(rule);
			वापस;
		पूर्ण
	पूर्ण
	/* We didn't find it. */
	WARN_ON(1);
पूर्ण
#पूर्ण_अगर

पूर्णांक efx_probe_filters(काष्ठा efx_nic *efx)
अणु
	पूर्णांक rc;

	mutex_lock(&efx->mac_lock);
	करोwn_ग_लिखो(&efx->filter_sem);
	rc = efx->type->filter_table_probe(efx);
	अगर (rc)
		जाओ out_unlock;

#अगर_घोषित CONFIG_RFS_ACCEL
	अगर (efx->type->offload_features & NETIF_F_NTUPLE) अणु
		काष्ठा efx_channel *channel;
		पूर्णांक i, success = 1;

		efx_क्रम_each_channel(channel, efx) अणु
			channel->rps_flow_id =
				kसुस्मृति(efx->type->max_rx_ip_filters,
					माप(*channel->rps_flow_id),
					GFP_KERNEL);
			अगर (!channel->rps_flow_id)
				success = 0;
			अन्यथा
				क्रम (i = 0;
				     i < efx->type->max_rx_ip_filters;
				     ++i)
					channel->rps_flow_id[i] =
						RPS_FLOW_ID_INVALID;
			channel->rfs_expire_index = 0;
			channel->rfs_filter_count = 0;
		पूर्ण

		अगर (!success) अणु
			efx_क्रम_each_channel(channel, efx)
				kमुक्त(channel->rps_flow_id);
			efx->type->filter_table_हटाओ(efx);
			rc = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
	पूर्ण
#पूर्ण_अगर
out_unlock:
	up_ग_लिखो(&efx->filter_sem);
	mutex_unlock(&efx->mac_lock);
	वापस rc;
पूर्ण

व्योम efx_हटाओ_filters(काष्ठा efx_nic *efx)
अणु
#अगर_घोषित CONFIG_RFS_ACCEL
	काष्ठा efx_channel *channel;

	efx_क्रम_each_channel(channel, efx) अणु
		cancel_delayed_work_sync(&channel->filter_work);
		kमुक्त(channel->rps_flow_id);
		channel->rps_flow_id = शून्य;
	पूर्ण
#पूर्ण_अगर
	करोwn_ग_लिखो(&efx->filter_sem);
	efx->type->filter_table_हटाओ(efx);
	up_ग_लिखो(&efx->filter_sem);
पूर्ण

#अगर_घोषित CONFIG_RFS_ACCEL

अटल व्योम efx_filter_rfs_work(काष्ठा work_काष्ठा *data)
अणु
	काष्ठा efx_async_filter_insertion *req = container_of(data, काष्ठा efx_async_filter_insertion,
							      work);
	काष्ठा efx_nic *efx = netdev_priv(req->net_dev);
	काष्ठा efx_channel *channel = efx_get_channel(efx, req->rxq_index);
	पूर्णांक slot_idx = req - efx->rps_slot;
	काष्ठा efx_arfs_rule *rule;
	u16 arfs_id = 0;
	पूर्णांक rc;

	rc = efx->type->filter_insert(efx, &req->spec, true);
	अगर (rc >= 0)
		/* Discard 'priority' part of EF10+ filter ID (mcdi_filters) */
		rc %= efx->type->max_rx_ip_filters;
	अगर (efx->rps_hash_table) अणु
		spin_lock_bh(&efx->rps_hash_lock);
		rule = efx_rps_hash_find(efx, &req->spec);
		/* The rule might have alपढ़ोy gone, अगर someone अन्यथा's request
		 * क्रम the same spec was alपढ़ोy worked and then expired beक्रमe
		 * we got around to our work.  In that हाल we have nothing
		 * tying us to an arfs_id, meaning that as soon as the filter
		 * is considered क्रम expiry it will be हटाओd.
		 */
		अगर (rule) अणु
			अगर (rc < 0)
				rule->filter_id = EFX_ARFS_FILTER_ID_ERROR;
			अन्यथा
				rule->filter_id = rc;
			arfs_id = rule->arfs_id;
		पूर्ण
		spin_unlock_bh(&efx->rps_hash_lock);
	पूर्ण
	अगर (rc >= 0) अणु
		/* Remember this so we can check whether to expire the filter
		 * later.
		 */
		mutex_lock(&efx->rps_mutex);
		अगर (channel->rps_flow_id[rc] == RPS_FLOW_ID_INVALID)
			channel->rfs_filter_count++;
		channel->rps_flow_id[rc] = req->flow_id;
		mutex_unlock(&efx->rps_mutex);

		अगर (req->spec.ether_type == htons(ETH_P_IP))
			netअगर_info(efx, rx_status, efx->net_dev,
				   "steering %s %pI4:%u:%pI4:%u to queue %u [flow %u filter %d id %u]\n",
				   (req->spec.ip_proto == IPPROTO_TCP) ? "TCP" : "UDP",
				   req->spec.rem_host, ntohs(req->spec.rem_port),
				   req->spec.loc_host, ntohs(req->spec.loc_port),
				   req->rxq_index, req->flow_id, rc, arfs_id);
		अन्यथा
			netअगर_info(efx, rx_status, efx->net_dev,
				   "steering %s [%pI6]:%u:[%pI6]:%u to queue %u [flow %u filter %d id %u]\n",
				   (req->spec.ip_proto == IPPROTO_TCP) ? "TCP" : "UDP",
				   req->spec.rem_host, ntohs(req->spec.rem_port),
				   req->spec.loc_host, ntohs(req->spec.loc_port),
				   req->rxq_index, req->flow_id, rc, arfs_id);
		channel->n_rfs_succeeded++;
	पूर्ण अन्यथा अणु
		अगर (req->spec.ether_type == htons(ETH_P_IP))
			netअगर_dbg(efx, rx_status, efx->net_dev,
				  "failed to steer %s %pI4:%u:%pI4:%u to queue %u [flow %u rc %d id %u]\n",
				  (req->spec.ip_proto == IPPROTO_TCP) ? "TCP" : "UDP",
				  req->spec.rem_host, ntohs(req->spec.rem_port),
				  req->spec.loc_host, ntohs(req->spec.loc_port),
				  req->rxq_index, req->flow_id, rc, arfs_id);
		अन्यथा
			netअगर_dbg(efx, rx_status, efx->net_dev,
				  "failed to steer %s [%pI6]:%u:[%pI6]:%u to queue %u [flow %u rc %d id %u]\n",
				  (req->spec.ip_proto == IPPROTO_TCP) ? "TCP" : "UDP",
				  req->spec.rem_host, ntohs(req->spec.rem_port),
				  req->spec.loc_host, ntohs(req->spec.loc_port),
				  req->rxq_index, req->flow_id, rc, arfs_id);
		channel->n_rfs_failed++;
		/* We're overloading the NIC's filter tables, so let's करो a
		 * chunk of extra expiry work.
		 */
		__efx_filter_rfs_expire(channel, min(channel->rfs_filter_count,
						     100u));
	पूर्ण

	/* Release references */
	clear_bit(slot_idx, &efx->rps_slot_map);
	dev_put(req->net_dev);
पूर्ण

पूर्णांक efx_filter_rfs(काष्ठा net_device *net_dev, स्थिर काष्ठा sk_buff *skb,
		   u16 rxq_index, u32 flow_id)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा efx_async_filter_insertion *req;
	काष्ठा efx_arfs_rule *rule;
	काष्ठा flow_keys fk;
	पूर्णांक slot_idx;
	bool new;
	पूर्णांक rc;

	/* find a मुक्त slot */
	क्रम (slot_idx = 0; slot_idx < EFX_RPS_MAX_IN_FLIGHT; slot_idx++)
		अगर (!test_and_set_bit(slot_idx, &efx->rps_slot_map))
			अवरोध;
	अगर (slot_idx >= EFX_RPS_MAX_IN_FLIGHT)
		वापस -EBUSY;

	अगर (flow_id == RPS_FLOW_ID_INVALID) अणु
		rc = -EINVAL;
		जाओ out_clear;
	पूर्ण

	अगर (!skb_flow_dissect_flow_keys(skb, &fk, 0)) अणु
		rc = -EPROTONOSUPPORT;
		जाओ out_clear;
	पूर्ण

	अगर (fk.basic.n_proto != htons(ETH_P_IP) && fk.basic.n_proto != htons(ETH_P_IPV6)) अणु
		rc = -EPROTONOSUPPORT;
		जाओ out_clear;
	पूर्ण
	अगर (fk.control.flags & FLOW_DIS_IS_FRAGMENT) अणु
		rc = -EPROTONOSUPPORT;
		जाओ out_clear;
	पूर्ण

	req = efx->rps_slot + slot_idx;
	efx_filter_init_rx(&req->spec, EFX_FILTER_PRI_HINT,
			   efx->rx_scatter ? EFX_FILTER_FLAG_RX_SCATTER : 0,
			   rxq_index);
	req->spec.match_flags =
		EFX_FILTER_MATCH_ETHER_TYPE | EFX_FILTER_MATCH_IP_PROTO |
		EFX_FILTER_MATCH_LOC_HOST | EFX_FILTER_MATCH_LOC_PORT |
		EFX_FILTER_MATCH_REM_HOST | EFX_FILTER_MATCH_REM_PORT;
	req->spec.ether_type = fk.basic.n_proto;
	req->spec.ip_proto = fk.basic.ip_proto;

	अगर (fk.basic.n_proto == htons(ETH_P_IP)) अणु
		req->spec.rem_host[0] = fk.addrs.v4addrs.src;
		req->spec.loc_host[0] = fk.addrs.v4addrs.dst;
	पूर्ण अन्यथा अणु
		स_नकल(req->spec.rem_host, &fk.addrs.v6addrs.src,
		       माप(काष्ठा in6_addr));
		स_नकल(req->spec.loc_host, &fk.addrs.v6addrs.dst,
		       माप(काष्ठा in6_addr));
	पूर्ण

	req->spec.rem_port = fk.ports.src;
	req->spec.loc_port = fk.ports.dst;

	अगर (efx->rps_hash_table) अणु
		/* Add it to ARFS hash table */
		spin_lock(&efx->rps_hash_lock);
		rule = efx_rps_hash_add(efx, &req->spec, &new);
		अगर (!rule) अणु
			rc = -ENOMEM;
			जाओ out_unlock;
		पूर्ण
		अगर (new)
			rule->arfs_id = efx->rps_next_id++ % RPS_NO_FILTER;
		rc = rule->arfs_id;
		/* Skip अगर existing or pending filter alपढ़ोy करोes the right thing */
		अगर (!new && rule->rxq_index == rxq_index &&
		    rule->filter_id >= EFX_ARFS_FILTER_ID_PENDING)
			जाओ out_unlock;
		rule->rxq_index = rxq_index;
		rule->filter_id = EFX_ARFS_FILTER_ID_PENDING;
		spin_unlock(&efx->rps_hash_lock);
	पूर्ण अन्यथा अणु
		/* Without an ARFS hash table, we just use arfs_id 0 क्रम all
		 * filters.  This means अगर multiple flows hash to the same
		 * flow_id, all but the most recently touched will be eligible
		 * क्रम expiry.
		 */
		rc = 0;
	पूर्ण

	/* Queue the request */
	dev_hold(req->net_dev = net_dev);
	INIT_WORK(&req->work, efx_filter_rfs_work);
	req->rxq_index = rxq_index;
	req->flow_id = flow_id;
	schedule_work(&req->work);
	वापस rc;
out_unlock:
	spin_unlock(&efx->rps_hash_lock);
out_clear:
	clear_bit(slot_idx, &efx->rps_slot_map);
	वापस rc;
पूर्ण

bool __efx_filter_rfs_expire(काष्ठा efx_channel *channel, अचिन्हित पूर्णांक quota)
अणु
	bool (*expire_one)(काष्ठा efx_nic *efx, u32 flow_id, अचिन्हित पूर्णांक index);
	काष्ठा efx_nic *efx = channel->efx;
	अचिन्हित पूर्णांक index, size, start;
	u32 flow_id;

	अगर (!mutex_trylock(&efx->rps_mutex))
		वापस false;
	expire_one = efx->type->filter_rfs_expire_one;
	index = channel->rfs_expire_index;
	start = index;
	size = efx->type->max_rx_ip_filters;
	जबतक (quota) अणु
		flow_id = channel->rps_flow_id[index];

		अगर (flow_id != RPS_FLOW_ID_INVALID) अणु
			quota--;
			अगर (expire_one(efx, flow_id, index)) अणु
				netअगर_info(efx, rx_status, efx->net_dev,
					   "expired filter %d [channel %u flow %u]\n",
					   index, channel->channel, flow_id);
				channel->rps_flow_id[index] = RPS_FLOW_ID_INVALID;
				channel->rfs_filter_count--;
			पूर्ण
		पूर्ण
		अगर (++index == size)
			index = 0;
		/* If we were called with a quota that exceeds the total number
		 * of filters in the table (which shouldn't happen, but could
		 * अगर two callers race), ensure that we करोn't loop क्रमever -
		 * stop when we've examined every row of the table.
		 */
		अगर (index == start)
			अवरोध;
	पूर्ण

	channel->rfs_expire_index = index;
	mutex_unlock(&efx->rps_mutex);
	वापस true;
पूर्ण

#पूर्ण_अगर /* CONFIG_RFS_ACCEL */
