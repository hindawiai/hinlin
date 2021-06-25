<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2005-2013 Solarflare Communications Inc.
 */

#समावेश <linux/socket.h>
#समावेश <linux/in.h>
#समावेश <linux/slab.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/tcp.h>
#समावेश <linux/udp.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/iommu.h>
#समावेश <net/ip.h>
#समावेश <net/checksum.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "filter.h"
#समावेश "nic.h"
#समावेश "selftest.h"
#समावेश "workarounds.h"

/* Preferred number of descriptors to fill at once */
#घोषणा EF4_RX_PREFERRED_BATCH 8U

/* Number of RX buffers to recycle pages क्रम.  When creating the RX page recycle
 * ring, this number is भागided by the number of buffers per page to calculate
 * the number of pages to store in the RX page recycle ring.
 */
#घोषणा EF4_RECYCLE_RING_SIZE_IOMMU 4096
#घोषणा EF4_RECYCLE_RING_SIZE_NOIOMMU (2 * EF4_RX_PREFERRED_BATCH)

/* Size of buffer allocated क्रम skb header area. */
#घोषणा EF4_SKB_HEADERS  128u

/* This is the percentage fill level below which new RX descriptors
 * will be added to the RX descriptor ring.
 */
अटल अचिन्हित पूर्णांक rx_refill_threshold;

/* Each packet can consume up to उच्चमान(max_frame_len / buffer_size) buffers */
#घोषणा EF4_RX_MAX_FRAGS DIV_ROUND_UP(EF4_MAX_FRAME_LEN(EF4_MAX_MTU), \
				      EF4_RX_USR_BUF_SIZE)

/*
 * RX maximum head room required.
 *
 * This must be at least 1 to prevent overflow, plus one packet-worth
 * to allow pipelined receives.
 */
#घोषणा EF4_RXD_HEAD_ROOM (1 + EF4_RX_MAX_FRAGS)

अटल अंतरभूत u8 *ef4_rx_buf_va(काष्ठा ef4_rx_buffer *buf)
अणु
	वापस page_address(buf->page) + buf->page_offset;
पूर्ण

अटल अंतरभूत u32 ef4_rx_buf_hash(काष्ठा ef4_nic *efx, स्थिर u8 *eh)
अणु
#अगर defined(CONFIG_HAVE_EFFICIENT_UNALIGNED_ACCESS)
	वापस __le32_to_cpup((स्थिर __le32 *)(eh + efx->rx_packet_hash_offset));
#अन्यथा
	स्थिर u8 *data = eh + efx->rx_packet_hash_offset;
	वापस (u32)data[0]	  |
	       (u32)data[1] << 8  |
	       (u32)data[2] << 16 |
	       (u32)data[3] << 24;
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत काष्ठा ef4_rx_buffer *
ef4_rx_buf_next(काष्ठा ef4_rx_queue *rx_queue, काष्ठा ef4_rx_buffer *rx_buf)
अणु
	अगर (unlikely(rx_buf == ef4_rx_buffer(rx_queue, rx_queue->ptr_mask)))
		वापस ef4_rx_buffer(rx_queue, 0);
	अन्यथा
		वापस rx_buf + 1;
पूर्ण

अटल अंतरभूत व्योम ef4_sync_rx_buffer(काष्ठा ef4_nic *efx,
				      काष्ठा ef4_rx_buffer *rx_buf,
				      अचिन्हित पूर्णांक len)
अणु
	dma_sync_single_क्रम_cpu(&efx->pci_dev->dev, rx_buf->dma_addr, len,
				DMA_FROM_DEVICE);
पूर्ण

व्योम ef4_rx_config_page_split(काष्ठा ef4_nic *efx)
अणु
	efx->rx_page_buf_step = ALIGN(efx->rx_dma_len + efx->rx_ip_align,
				      EF4_RX_BUF_ALIGNMENT);
	efx->rx_bufs_per_page = efx->rx_buffer_order ? 1 :
		((PAGE_SIZE - माप(काष्ठा ef4_rx_page_state)) /
		 efx->rx_page_buf_step);
	efx->rx_buffer_truesize = (PAGE_SIZE << efx->rx_buffer_order) /
		efx->rx_bufs_per_page;
	efx->rx_pages_per_batch = DIV_ROUND_UP(EF4_RX_PREFERRED_BATCH,
					       efx->rx_bufs_per_page);
पूर्ण

/* Check the RX page recycle ring क्रम a page that can be reused. */
अटल काष्ठा page *ef4_reuse_page(काष्ठा ef4_rx_queue *rx_queue)
अणु
	काष्ठा ef4_nic *efx = rx_queue->efx;
	काष्ठा page *page;
	काष्ठा ef4_rx_page_state *state;
	अचिन्हित index;

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

/**
 * ef4_init_rx_buffers - create EF4_RX_BATCH page-based RX buffers
 *
 * @rx_queue:		Efx RX queue
 * @atomic:		control memory allocation flags
 *
 * This allocates a batch of pages, maps them क्रम DMA, and populates
 * काष्ठा ef4_rx_buffers क्रम each one. Return a negative error code or
 * 0 on success. If a single page can be used क्रम multiple buffers,
 * then the page will either be inserted fully, or not at all.
 */
अटल पूर्णांक ef4_init_rx_buffers(काष्ठा ef4_rx_queue *rx_queue, bool atomic)
अणु
	काष्ठा ef4_nic *efx = rx_queue->efx;
	काष्ठा ef4_rx_buffer *rx_buf;
	काष्ठा page *page;
	अचिन्हित पूर्णांक page_offset;
	काष्ठा ef4_rx_page_state *state;
	dma_addr_t dma_addr;
	अचिन्हित index, count;

	count = 0;
	करो अणु
		page = ef4_reuse_page(rx_queue);
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

		dma_addr += माप(काष्ठा ef4_rx_page_state);
		page_offset = माप(काष्ठा ef4_rx_page_state);

		करो अणु
			index = rx_queue->added_count & rx_queue->ptr_mask;
			rx_buf = ef4_rx_buffer(rx_queue, index);
			rx_buf->dma_addr = dma_addr + efx->rx_ip_align;
			rx_buf->page = page;
			rx_buf->page_offset = page_offset + efx->rx_ip_align;
			rx_buf->len = efx->rx_dma_len;
			rx_buf->flags = 0;
			++rx_queue->added_count;
			get_page(page);
			dma_addr += efx->rx_page_buf_step;
			page_offset += efx->rx_page_buf_step;
		पूर्ण जबतक (page_offset + efx->rx_page_buf_step <= PAGE_SIZE);

		rx_buf->flags = EF4_RX_BUF_LAST_IN_PAGE;
	पूर्ण जबतक (++count < efx->rx_pages_per_batch);

	वापस 0;
पूर्ण

/* Unmap a DMA-mapped page.  This function is only called क्रम the final RX
 * buffer in a page.
 */
अटल व्योम ef4_unmap_rx_buffer(काष्ठा ef4_nic *efx,
				काष्ठा ef4_rx_buffer *rx_buf)
अणु
	काष्ठा page *page = rx_buf->page;

	अगर (page) अणु
		काष्ठा ef4_rx_page_state *state = page_address(page);
		dma_unmap_page(&efx->pci_dev->dev,
			       state->dma_addr,
			       PAGE_SIZE << efx->rx_buffer_order,
			       DMA_FROM_DEVICE);
	पूर्ण
पूर्ण

अटल व्योम ef4_मुक्त_rx_buffers(काष्ठा ef4_rx_queue *rx_queue,
				काष्ठा ef4_rx_buffer *rx_buf,
				अचिन्हित पूर्णांक num_bufs)
अणु
	करो अणु
		अगर (rx_buf->page) अणु
			put_page(rx_buf->page);
			rx_buf->page = शून्य;
		पूर्ण
		rx_buf = ef4_rx_buf_next(rx_queue, rx_buf);
	पूर्ण जबतक (--num_bufs);
पूर्ण

/* Attempt to recycle the page अगर there is an RX recycle ring; the page can
 * only be added अगर this is the final RX buffer, to prevent pages being used in
 * the descriptor ring and appearing in the recycle ring simultaneously.
 */
अटल व्योम ef4_recycle_rx_page(काष्ठा ef4_channel *channel,
				काष्ठा ef4_rx_buffer *rx_buf)
अणु
	काष्ठा page *page = rx_buf->page;
	काष्ठा ef4_rx_queue *rx_queue = ef4_channel_get_rx_queue(channel);
	काष्ठा ef4_nic *efx = rx_queue->efx;
	अचिन्हित index;

	/* Only recycle the page after processing the final buffer. */
	अगर (!(rx_buf->flags & EF4_RX_BUF_LAST_IN_PAGE))
		वापस;

	index = rx_queue->page_add & rx_queue->page_ptr_mask;
	अगर (rx_queue->page_ring[index] == शून्य) अणु
		अचिन्हित पढ़ो_index = rx_queue->page_हटाओ &
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
	ef4_unmap_rx_buffer(efx, rx_buf);
	put_page(rx_buf->page);
पूर्ण

अटल व्योम ef4_fini_rx_buffer(काष्ठा ef4_rx_queue *rx_queue,
			       काष्ठा ef4_rx_buffer *rx_buf)
अणु
	/* Release the page reference we hold क्रम the buffer. */
	अगर (rx_buf->page)
		put_page(rx_buf->page);

	/* If this is the last buffer in a page, unmap and मुक्त it. */
	अगर (rx_buf->flags & EF4_RX_BUF_LAST_IN_PAGE) अणु
		ef4_unmap_rx_buffer(rx_queue->efx, rx_buf);
		ef4_मुक्त_rx_buffers(rx_queue, rx_buf, 1);
	पूर्ण
	rx_buf->page = शून्य;
पूर्ण

/* Recycle the pages that are used by buffers that have just been received. */
अटल व्योम ef4_recycle_rx_pages(काष्ठा ef4_channel *channel,
				 काष्ठा ef4_rx_buffer *rx_buf,
				 अचिन्हित पूर्णांक n_frags)
अणु
	काष्ठा ef4_rx_queue *rx_queue = ef4_channel_get_rx_queue(channel);

	करो अणु
		ef4_recycle_rx_page(channel, rx_buf);
		rx_buf = ef4_rx_buf_next(rx_queue, rx_buf);
	पूर्ण जबतक (--n_frags);
पूर्ण

अटल व्योम ef4_discard_rx_packet(काष्ठा ef4_channel *channel,
				  काष्ठा ef4_rx_buffer *rx_buf,
				  अचिन्हित पूर्णांक n_frags)
अणु
	काष्ठा ef4_rx_queue *rx_queue = ef4_channel_get_rx_queue(channel);

	ef4_recycle_rx_pages(channel, rx_buf, n_frags);

	ef4_मुक्त_rx_buffers(rx_queue, rx_buf, n_frags);
पूर्ण

/**
 * ef4_fast_push_rx_descriptors - push new RX descriptors quickly
 * @rx_queue:		RX descriptor queue
 *
 * This will aim to fill the RX descriptor queue up to
 * @rx_queue->@max_fill. If there is insufficient atomic
 * memory to करो so, a slow fill will be scheduled.
 * @atomic: control memory allocation flags
 *
 * The caller must provide serialisation (none is used here). In practise,
 * this means this function must run from the NAPI handler, or be called
 * when NAPI is disabled.
 */
व्योम ef4_fast_push_rx_descriptors(काष्ठा ef4_rx_queue *rx_queue, bool atomic)
अणु
	काष्ठा ef4_nic *efx = rx_queue->efx;
	अचिन्हित पूर्णांक fill_level, batch_size;
	पूर्णांक space, rc = 0;

	अगर (!rx_queue->refill_enabled)
		वापस;

	/* Calculate current fill level, and निकास अगर we करोn't need to fill */
	fill_level = (rx_queue->added_count - rx_queue->हटाओd_count);
	EF4_BUG_ON_PARANOID(fill_level > rx_queue->efx->rxq_entries);
	अगर (fill_level >= rx_queue->fast_fill_trigger)
		जाओ out;

	/* Record minimum fill level */
	अगर (unlikely(fill_level < rx_queue->min_fill)) अणु
		अगर (fill_level)
			rx_queue->min_fill = fill_level;
	पूर्ण

	batch_size = efx->rx_pages_per_batch * efx->rx_bufs_per_page;
	space = rx_queue->max_fill - fill_level;
	EF4_BUG_ON_PARANOID(space < batch_size);

	netअगर_vdbg(rx_queue->efx, rx_status, rx_queue->efx->net_dev,
		   "RX queue %d fast-filling descriptor ring from"
		   " level %d to level %d\n",
		   ef4_rx_queue_index(rx_queue), fill_level,
		   rx_queue->max_fill);


	करो अणु
		rc = ef4_init_rx_buffers(rx_queue, atomic);
		अगर (unlikely(rc)) अणु
			/* Ensure that we करोn't leave the rx queue empty */
			अगर (rx_queue->added_count == rx_queue->हटाओd_count)
				ef4_schedule_slow_fill(rx_queue);
			जाओ out;
		पूर्ण
	पूर्ण जबतक ((space -= batch_size) >= batch_size);

	netअगर_vdbg(rx_queue->efx, rx_status, rx_queue->efx->net_dev,
		   "RX queue %d fast-filled descriptor ring "
		   "to level %d\n", ef4_rx_queue_index(rx_queue),
		   rx_queue->added_count - rx_queue->हटाओd_count);

 out:
	अगर (rx_queue->notअगरied_count != rx_queue->added_count)
		ef4_nic_notअगरy_rx_desc(rx_queue);
पूर्ण

व्योम ef4_rx_slow_fill(काष्ठा समयr_list *t)
अणु
	काष्ठा ef4_rx_queue *rx_queue = from_समयr(rx_queue, t, slow_fill);

	/* Post an event to cause NAPI to run and refill the queue */
	ef4_nic_generate_fill_event(rx_queue);
	++rx_queue->slow_fill_count;
पूर्ण

अटल व्योम ef4_rx_packet__check_len(काष्ठा ef4_rx_queue *rx_queue,
				     काष्ठा ef4_rx_buffer *rx_buf,
				     पूर्णांक len)
अणु
	काष्ठा ef4_nic *efx = rx_queue->efx;
	अचिन्हित max_len = rx_buf->len - efx->type->rx_buffer_padding;

	अगर (likely(len <= max_len))
		वापस;

	/* The packet must be discarded, but this is only a fatal error
	 * अगर the caller indicated it was
	 */
	rx_buf->flags |= EF4_RX_PKT_DISCARD;

	अगर ((len > rx_buf->len) && EF4_WORKAROUND_8071(efx)) अणु
		अगर (net_ratelimit())
			netअगर_err(efx, rx_err, efx->net_dev,
				  " RX queue %d seriously overlength "
				  "RX event (0x%x > 0x%x+0x%x). Leaking\n",
				  ef4_rx_queue_index(rx_queue), len, max_len,
				  efx->type->rx_buffer_padding);
		ef4_schedule_reset(efx, RESET_TYPE_RX_RECOVERY);
	पूर्ण अन्यथा अणु
		अगर (net_ratelimit())
			netअगर_err(efx, rx_err, efx->net_dev,
				  " RX queue %d overlength RX event "
				  "(0x%x > 0x%x)\n",
				  ef4_rx_queue_index(rx_queue), len, max_len);
	पूर्ण

	ef4_rx_queue_channel(rx_queue)->n_rx_overlength++;
पूर्ण

/* Pass a received packet up through GRO.  GRO can handle pages
 * regardless of checksum state and skbs with a good checksum.
 */
अटल व्योम
ef4_rx_packet_gro(काष्ठा ef4_channel *channel, काष्ठा ef4_rx_buffer *rx_buf,
		  अचिन्हित पूर्णांक n_frags, u8 *eh)
अणु
	काष्ठा napi_काष्ठा *napi = &channel->napi_str;
	काष्ठा ef4_nic *efx = channel->efx;
	काष्ठा sk_buff *skb;

	skb = napi_get_frags(napi);
	अगर (unlikely(!skb)) अणु
		काष्ठा ef4_rx_queue *rx_queue;

		rx_queue = ef4_channel_get_rx_queue(channel);
		ef4_मुक्त_rx_buffers(rx_queue, rx_buf, n_frags);
		वापस;
	पूर्ण

	अगर (efx->net_dev->features & NETIF_F_RXHASH)
		skb_set_hash(skb, ef4_rx_buf_hash(efx, eh),
			     PKT_HASH_TYPE_L3);
	skb->ip_summed = ((rx_buf->flags & EF4_RX_PKT_CSUMMED) ?
			  CHECKSUM_UNNECESSARY : CHECKSUM_NONE);

	क्रम (;;) अणु
		skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
				   rx_buf->page, rx_buf->page_offset,
				   rx_buf->len);
		rx_buf->page = शून्य;
		skb->len += rx_buf->len;
		अगर (skb_shinfo(skb)->nr_frags == n_frags)
			अवरोध;

		rx_buf = ef4_rx_buf_next(&channel->rx_queue, rx_buf);
	पूर्ण

	skb->data_len = skb->len;
	skb->truesize += n_frags * efx->rx_buffer_truesize;

	skb_record_rx_queue(skb, channel->rx_queue.core_index);

	napi_gro_frags(napi);
पूर्ण

/* Allocate and स्थिरruct an SKB around page fragments */
अटल काष्ठा sk_buff *ef4_rx_mk_skb(काष्ठा ef4_channel *channel,
				     काष्ठा ef4_rx_buffer *rx_buf,
				     अचिन्हित पूर्णांक n_frags,
				     u8 *eh, पूर्णांक hdr_len)
अणु
	काष्ठा ef4_nic *efx = channel->efx;
	काष्ठा sk_buff *skb;

	/* Allocate an SKB to store the headers */
	skb = netdev_alloc_skb(efx->net_dev,
			       efx->rx_ip_align + efx->rx_prefix_size +
			       hdr_len);
	अगर (unlikely(skb == शून्य)) अणु
		atomic_inc(&efx->n_rx_noskb_drops);
		वापस शून्य;
	पूर्ण

	EF4_BUG_ON_PARANOID(rx_buf->len < hdr_len);

	स_नकल(skb->data + efx->rx_ip_align, eh - efx->rx_prefix_size,
	       efx->rx_prefix_size + hdr_len);
	skb_reserve(skb, efx->rx_ip_align + efx->rx_prefix_size);
	__skb_put(skb, hdr_len);

	/* Append the reमुख्यing page(s) onto the frag list */
	अगर (rx_buf->len > hdr_len) अणु
		rx_buf->page_offset += hdr_len;
		rx_buf->len -= hdr_len;

		क्रम (;;) अणु
			skb_fill_page_desc(skb, skb_shinfo(skb)->nr_frags,
					   rx_buf->page, rx_buf->page_offset,
					   rx_buf->len);
			rx_buf->page = शून्य;
			skb->len += rx_buf->len;
			skb->data_len += rx_buf->len;
			अगर (skb_shinfo(skb)->nr_frags == n_frags)
				अवरोध;

			rx_buf = ef4_rx_buf_next(&channel->rx_queue, rx_buf);
		पूर्ण
	पूर्ण अन्यथा अणु
		__मुक्त_pages(rx_buf->page, efx->rx_buffer_order);
		rx_buf->page = शून्य;
		n_frags = 0;
	पूर्ण

	skb->truesize += n_frags * efx->rx_buffer_truesize;

	/* Move past the ethernet header */
	skb->protocol = eth_type_trans(skb, efx->net_dev);

	skb_mark_napi_id(skb, &channel->napi_str);

	वापस skb;
पूर्ण

व्योम ef4_rx_packet(काष्ठा ef4_rx_queue *rx_queue, अचिन्हित पूर्णांक index,
		   अचिन्हित पूर्णांक n_frags, अचिन्हित पूर्णांक len, u16 flags)
अणु
	काष्ठा ef4_nic *efx = rx_queue->efx;
	काष्ठा ef4_channel *channel = ef4_rx_queue_channel(rx_queue);
	काष्ठा ef4_rx_buffer *rx_buf;

	rx_queue->rx_packets++;

	rx_buf = ef4_rx_buffer(rx_queue, index);
	rx_buf->flags |= flags;

	/* Validate the number of fragments and completed length */
	अगर (n_frags == 1) अणु
		अगर (!(flags & EF4_RX_PKT_PREFIX_LEN))
			ef4_rx_packet__check_len(rx_queue, rx_buf, len);
	पूर्ण अन्यथा अगर (unlikely(n_frags > EF4_RX_MAX_FRAGS) ||
		   unlikely(len <= (n_frags - 1) * efx->rx_dma_len) ||
		   unlikely(len > n_frags * efx->rx_dma_len) ||
		   unlikely(!efx->rx_scatter)) अणु
		/* If this isn't an explicit discard request, either
		 * the hardware or the driver is broken.
		 */
		WARN_ON(!(len == 0 && rx_buf->flags & EF4_RX_PKT_DISCARD));
		rx_buf->flags |= EF4_RX_PKT_DISCARD;
	पूर्ण

	netअगर_vdbg(efx, rx_status, efx->net_dev,
		   "RX queue %d received ids %x-%x len %d %s%s\n",
		   ef4_rx_queue_index(rx_queue), index,
		   (index + n_frags - 1) & rx_queue->ptr_mask, len,
		   (rx_buf->flags & EF4_RX_PKT_CSUMMED) ? " [SUMMED]" : "",
		   (rx_buf->flags & EF4_RX_PKT_DISCARD) ? " [DISCARD]" : "");

	/* Discard packet, अगर inकाष्ठाed to करो so.  Process the
	 * previous receive first.
	 */
	अगर (unlikely(rx_buf->flags & EF4_RX_PKT_DISCARD)) अणु
		ef4_rx_flush_packet(channel);
		ef4_discard_rx_packet(channel, rx_buf, n_frags);
		वापस;
	पूर्ण

	अगर (n_frags == 1 && !(flags & EF4_RX_PKT_PREFIX_LEN))
		rx_buf->len = len;

	/* Release and/or sync the DMA mapping - assumes all RX buffers
	 * consumed in-order per RX queue.
	 */
	ef4_sync_rx_buffer(efx, rx_buf, rx_buf->len);

	/* Prefetch nice and early so data will (hopefully) be in cache by
	 * the समय we look at it.
	 */
	prefetch(ef4_rx_buf_va(rx_buf));

	rx_buf->page_offset += efx->rx_prefix_size;
	rx_buf->len -= efx->rx_prefix_size;

	अगर (n_frags > 1) अणु
		/* Release/sync DMA mapping क्रम additional fragments.
		 * Fix length क्रम last fragment.
		 */
		अचिन्हित पूर्णांक tail_frags = n_frags - 1;

		क्रम (;;) अणु
			rx_buf = ef4_rx_buf_next(rx_queue, rx_buf);
			अगर (--tail_frags == 0)
				अवरोध;
			ef4_sync_rx_buffer(efx, rx_buf, efx->rx_dma_len);
		पूर्ण
		rx_buf->len = len - (n_frags - 1) * efx->rx_dma_len;
		ef4_sync_rx_buffer(efx, rx_buf, rx_buf->len);
	पूर्ण

	/* All fragments have been DMA-synced, so recycle pages. */
	rx_buf = ef4_rx_buffer(rx_queue, index);
	ef4_recycle_rx_pages(channel, rx_buf, n_frags);

	/* Pipeline receives so that we give समय क्रम packet headers to be
	 * prefetched पूर्णांकo cache.
	 */
	ef4_rx_flush_packet(channel);
	channel->rx_pkt_n_frags = n_frags;
	channel->rx_pkt_index = index;
पूर्ण

अटल व्योम ef4_rx_deliver(काष्ठा ef4_channel *channel, u8 *eh,
			   काष्ठा ef4_rx_buffer *rx_buf,
			   अचिन्हित पूर्णांक n_frags)
अणु
	काष्ठा sk_buff *skb;
	u16 hdr_len = min_t(u16, rx_buf->len, EF4_SKB_HEADERS);

	skb = ef4_rx_mk_skb(channel, rx_buf, n_frags, eh, hdr_len);
	अगर (unlikely(skb == शून्य)) अणु
		काष्ठा ef4_rx_queue *rx_queue;

		rx_queue = ef4_channel_get_rx_queue(channel);
		ef4_मुक्त_rx_buffers(rx_queue, rx_buf, n_frags);
		वापस;
	पूर्ण
	skb_record_rx_queue(skb, channel->rx_queue.core_index);

	/* Set the SKB flags */
	skb_checksum_none_निश्चित(skb);
	अगर (likely(rx_buf->flags & EF4_RX_PKT_CSUMMED))
		skb->ip_summed = CHECKSUM_UNNECESSARY;

	अगर (channel->type->receive_skb)
		अगर (channel->type->receive_skb(channel, skb))
			वापस;

	/* Pass the packet up */
	netअगर_receive_skb(skb);
पूर्ण

/* Handle a received packet.  Second half: Touches packet payload. */
व्योम __ef4_rx_packet(काष्ठा ef4_channel *channel)
अणु
	काष्ठा ef4_nic *efx = channel->efx;
	काष्ठा ef4_rx_buffer *rx_buf =
		ef4_rx_buffer(&channel->rx_queue, channel->rx_pkt_index);
	u8 *eh = ef4_rx_buf_va(rx_buf);

	/* Read length from the prefix अगर necessary.  This alपढ़ोy
	 * excludes the length of the prefix itself.
	 */
	अगर (rx_buf->flags & EF4_RX_PKT_PREFIX_LEN)
		rx_buf->len = le16_to_cpup((__le16 *)
					   (eh + efx->rx_packet_len_offset));

	/* If we're in loopback test, then pass the packet directly to the
	 * loopback layer, and मुक्त the rx_buf here
	 */
	अगर (unlikely(efx->loopback_selftest)) अणु
		काष्ठा ef4_rx_queue *rx_queue;

		ef4_loopback_rx_packet(efx, eh, rx_buf->len);
		rx_queue = ef4_channel_get_rx_queue(channel);
		ef4_मुक्त_rx_buffers(rx_queue, rx_buf,
				    channel->rx_pkt_n_frags);
		जाओ out;
	पूर्ण

	अगर (unlikely(!(efx->net_dev->features & NETIF_F_RXCSUM)))
		rx_buf->flags &= ~EF4_RX_PKT_CSUMMED;

	अगर ((rx_buf->flags & EF4_RX_PKT_TCP) && !channel->type->receive_skb)
		ef4_rx_packet_gro(channel, rx_buf, channel->rx_pkt_n_frags, eh);
	अन्यथा
		ef4_rx_deliver(channel, eh, rx_buf, channel->rx_pkt_n_frags);
out:
	channel->rx_pkt_n_frags = 0;
पूर्ण

पूर्णांक ef4_probe_rx_queue(काष्ठा ef4_rx_queue *rx_queue)
अणु
	काष्ठा ef4_nic *efx = rx_queue->efx;
	अचिन्हित पूर्णांक entries;
	पूर्णांक rc;

	/* Create the smallest घातer-of-two aligned ring */
	entries = max(roundup_घात_of_two(efx->rxq_entries), EF4_MIN_DMAQ_SIZE);
	EF4_BUG_ON_PARANOID(entries > EF4_MAX_DMAQ_SIZE);
	rx_queue->ptr_mask = entries - 1;

	netअगर_dbg(efx, probe, efx->net_dev,
		  "creating RX queue %d size %#x mask %#x\n",
		  ef4_rx_queue_index(rx_queue), efx->rxq_entries,
		  rx_queue->ptr_mask);

	/* Allocate RX buffers */
	rx_queue->buffer = kसुस्मृति(entries, माप(*rx_queue->buffer),
				   GFP_KERNEL);
	अगर (!rx_queue->buffer)
		वापस -ENOMEM;

	rc = ef4_nic_probe_rx(rx_queue);
	अगर (rc) अणु
		kमुक्त(rx_queue->buffer);
		rx_queue->buffer = शून्य;
	पूर्ण

	वापस rc;
पूर्ण

अटल व्योम ef4_init_rx_recycle_ring(काष्ठा ef4_nic *efx,
				     काष्ठा ef4_rx_queue *rx_queue)
अणु
	अचिन्हित पूर्णांक bufs_in_recycle_ring, page_ring_size;

	/* Set the RX recycle ring size */
#अगर_घोषित CONFIG_PPC64
	bufs_in_recycle_ring = EF4_RECYCLE_RING_SIZE_IOMMU;
#अन्यथा
	अगर (iommu_present(&pci_bus_type))
		bufs_in_recycle_ring = EF4_RECYCLE_RING_SIZE_IOMMU;
	अन्यथा
		bufs_in_recycle_ring = EF4_RECYCLE_RING_SIZE_NOIOMMU;
#पूर्ण_अगर /* CONFIG_PPC64 */

	page_ring_size = roundup_घात_of_two(bufs_in_recycle_ring /
					    efx->rx_bufs_per_page);
	rx_queue->page_ring = kसुस्मृति(page_ring_size,
				      माप(*rx_queue->page_ring), GFP_KERNEL);
	rx_queue->page_ptr_mask = page_ring_size - 1;
पूर्ण

व्योम ef4_init_rx_queue(काष्ठा ef4_rx_queue *rx_queue)
अणु
	काष्ठा ef4_nic *efx = rx_queue->efx;
	अचिन्हित पूर्णांक max_fill, trigger, max_trigger;

	netअगर_dbg(rx_queue->efx, drv, rx_queue->efx->net_dev,
		  "initialising RX queue %d\n", ef4_rx_queue_index(rx_queue));

	/* Initialise ptr fields */
	rx_queue->added_count = 0;
	rx_queue->notअगरied_count = 0;
	rx_queue->हटाओd_count = 0;
	rx_queue->min_fill = -1U;
	ef4_init_rx_recycle_ring(efx, rx_queue);

	rx_queue->page_हटाओ = 0;
	rx_queue->page_add = rx_queue->page_ptr_mask + 1;
	rx_queue->page_recycle_count = 0;
	rx_queue->page_recycle_failed = 0;
	rx_queue->page_recycle_full = 0;

	/* Initialise limit fields */
	max_fill = efx->rxq_entries - EF4_RXD_HEAD_ROOM;
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

	/* Set up RX descriptor ring */
	ef4_nic_init_rx(rx_queue);
पूर्ण

व्योम ef4_fini_rx_queue(काष्ठा ef4_rx_queue *rx_queue)
अणु
	पूर्णांक i;
	काष्ठा ef4_nic *efx = rx_queue->efx;
	काष्ठा ef4_rx_buffer *rx_buf;

	netअगर_dbg(rx_queue->efx, drv, rx_queue->efx->net_dev,
		  "shutting down RX queue %d\n", ef4_rx_queue_index(rx_queue));

	del_समयr_sync(&rx_queue->slow_fill);

	/* Release RX buffers from the current पढ़ो ptr to the ग_लिखो ptr */
	अगर (rx_queue->buffer) अणु
		क्रम (i = rx_queue->हटाओd_count; i < rx_queue->added_count;
		     i++) अणु
			अचिन्हित index = i & rx_queue->ptr_mask;
			rx_buf = ef4_rx_buffer(rx_queue, index);
			ef4_fini_rx_buffer(rx_queue, rx_buf);
		पूर्ण
	पूर्ण

	/* Unmap and release the pages in the recycle ring. Remove the ring. */
	क्रम (i = 0; i <= rx_queue->page_ptr_mask; i++) अणु
		काष्ठा page *page = rx_queue->page_ring[i];
		काष्ठा ef4_rx_page_state *state;

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

व्योम ef4_हटाओ_rx_queue(काष्ठा ef4_rx_queue *rx_queue)
अणु
	netअगर_dbg(rx_queue->efx, drv, rx_queue->efx->net_dev,
		  "destroying RX queue %d\n", ef4_rx_queue_index(rx_queue));

	ef4_nic_हटाओ_rx(rx_queue);

	kमुक्त(rx_queue->buffer);
	rx_queue->buffer = शून्य;
पूर्ण


module_param(rx_refill_threshold, uपूर्णांक, 0444);
MODULE_PARM_DESC(rx_refill_threshold,
		 "RX descriptor ring refill threshold (%)");

#अगर_घोषित CONFIG_RFS_ACCEL

पूर्णांक ef4_filter_rfs(काष्ठा net_device *net_dev, स्थिर काष्ठा sk_buff *skb,
		   u16 rxq_index, u32 flow_id)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा ef4_channel *channel;
	काष्ठा ef4_filter_spec spec;
	काष्ठा flow_keys fk;
	पूर्णांक rc;

	अगर (flow_id == RPS_FLOW_ID_INVALID)
		वापस -EINVAL;

	अगर (!skb_flow_dissect_flow_keys(skb, &fk, 0))
		वापस -EPROTONOSUPPORT;

	अगर (fk.basic.n_proto != htons(ETH_P_IP) && fk.basic.n_proto != htons(ETH_P_IPV6))
		वापस -EPROTONOSUPPORT;
	अगर (fk.control.flags & FLOW_DIS_IS_FRAGMENT)
		वापस -EPROTONOSUPPORT;

	ef4_filter_init_rx(&spec, EF4_FILTER_PRI_HINT,
			   efx->rx_scatter ? EF4_FILTER_FLAG_RX_SCATTER : 0,
			   rxq_index);
	spec.match_flags =
		EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_IP_PROTO |
		EF4_FILTER_MATCH_LOC_HOST | EF4_FILTER_MATCH_LOC_PORT |
		EF4_FILTER_MATCH_REM_HOST | EF4_FILTER_MATCH_REM_PORT;
	spec.ether_type = fk.basic.n_proto;
	spec.ip_proto = fk.basic.ip_proto;

	अगर (fk.basic.n_proto == htons(ETH_P_IP)) अणु
		spec.rem_host[0] = fk.addrs.v4addrs.src;
		spec.loc_host[0] = fk.addrs.v4addrs.dst;
	पूर्ण अन्यथा अणु
		स_नकल(spec.rem_host, &fk.addrs.v6addrs.src, माप(काष्ठा in6_addr));
		स_नकल(spec.loc_host, &fk.addrs.v6addrs.dst, माप(काष्ठा in6_addr));
	पूर्ण

	spec.rem_port = fk.ports.src;
	spec.loc_port = fk.ports.dst;

	rc = efx->type->filter_rfs_insert(efx, &spec);
	अगर (rc < 0)
		वापस rc;

	/* Remember this so we can check whether to expire the filter later */
	channel = ef4_get_channel(efx, rxq_index);
	channel->rps_flow_id[rc] = flow_id;
	++channel->rfs_filters_added;

	अगर (spec.ether_type == htons(ETH_P_IP))
		netअगर_info(efx, rx_status, efx->net_dev,
			   "steering %s %pI4:%u:%pI4:%u to queue %u [flow %u filter %d]\n",
			   (spec.ip_proto == IPPROTO_TCP) ? "TCP" : "UDP",
			   spec.rem_host, ntohs(spec.rem_port), spec.loc_host,
			   ntohs(spec.loc_port), rxq_index, flow_id, rc);
	अन्यथा
		netअगर_info(efx, rx_status, efx->net_dev,
			   "steering %s [%pI6]:%u:[%pI6]:%u to queue %u [flow %u filter %d]\n",
			   (spec.ip_proto == IPPROTO_TCP) ? "TCP" : "UDP",
			   spec.rem_host, ntohs(spec.rem_port), spec.loc_host,
			   ntohs(spec.loc_port), rxq_index, flow_id, rc);

	वापस rc;
पूर्ण

bool __ef4_filter_rfs_expire(काष्ठा ef4_nic *efx, अचिन्हित पूर्णांक quota)
अणु
	bool (*expire_one)(काष्ठा ef4_nic *efx, u32 flow_id, अचिन्हित पूर्णांक index);
	अचिन्हित पूर्णांक channel_idx, index, size;
	u32 flow_id;

	अगर (!spin_trylock_bh(&efx->filter_lock))
		वापस false;

	expire_one = efx->type->filter_rfs_expire_one;
	channel_idx = efx->rps_expire_channel;
	index = efx->rps_expire_index;
	size = efx->type->max_rx_ip_filters;
	जबतक (quota--) अणु
		काष्ठा ef4_channel *channel = ef4_get_channel(efx, channel_idx);
		flow_id = channel->rps_flow_id[index];

		अगर (flow_id != RPS_FLOW_ID_INVALID &&
		    expire_one(efx, flow_id, index)) अणु
			netअगर_info(efx, rx_status, efx->net_dev,
				   "expired filter %d [queue %u flow %u]\n",
				   index, channel_idx, flow_id);
			channel->rps_flow_id[index] = RPS_FLOW_ID_INVALID;
		पूर्ण
		अगर (++index == size) अणु
			अगर (++channel_idx == efx->n_channels)
				channel_idx = 0;
			index = 0;
		पूर्ण
	पूर्ण
	efx->rps_expire_channel = channel_idx;
	efx->rps_expire_index = index;

	spin_unlock_bh(&efx->filter_lock);
	वापस true;
पूर्ण

#पूर्ण_अगर /* CONFIG_RFS_ACCEL */

/**
 * ef4_filter_is_mc_recipient - test whether spec is a multicast recipient
 * @spec: Specअगरication to test
 *
 * Return: %true अगर the specअगरication is a non-drop RX filter that
 * matches a local MAC address I/G bit value of 1 or matches a local
 * IPv4 or IPv6 address value in the respective multicast address
 * range.  Otherwise %false.
 */
bool ef4_filter_is_mc_recipient(स्थिर काष्ठा ef4_filter_spec *spec)
अणु
	अगर (!(spec->flags & EF4_FILTER_FLAG_RX) ||
	    spec->dmaq_id == EF4_FILTER_RX_DMAQ_ID_DROP)
		वापस false;

	अगर (spec->match_flags &
	    (EF4_FILTER_MATCH_LOC_MAC | EF4_FILTER_MATCH_LOC_MAC_IG) &&
	    is_multicast_ether_addr(spec->loc_mac))
		वापस true;

	अगर ((spec->match_flags &
	     (EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_LOC_HOST)) ==
	    (EF4_FILTER_MATCH_ETHER_TYPE | EF4_FILTER_MATCH_LOC_HOST)) अणु
		अगर (spec->ether_type == htons(ETH_P_IP) &&
		    ipv4_is_multicast(spec->loc_host[0]))
			वापस true;
		अगर (spec->ether_type == htons(ETH_P_IPV6) &&
		    ((स्थिर u8 *)spec->loc_host)[0] == 0xff)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण
