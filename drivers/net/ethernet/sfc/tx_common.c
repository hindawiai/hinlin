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
#समावेश "efx.h"
#समावेश "nic_common.h"
#समावेश "tx_common.h"

अटल अचिन्हित पूर्णांक efx_tx_cb_page_count(काष्ठा efx_tx_queue *tx_queue)
अणु
	वापस DIV_ROUND_UP(tx_queue->ptr_mask + 1,
			    PAGE_SIZE >> EFX_TX_CB_ORDER);
पूर्ण

पूर्णांक efx_probe_tx_queue(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	अचिन्हित पूर्णांक entries;
	पूर्णांक rc;

	/* Create the smallest घातer-of-two aligned ring */
	entries = max(roundup_घात_of_two(efx->txq_entries), EFX_MIN_DMAQ_SIZE);
	EFX_WARN_ON_PARANOID(entries > EFX_MAX_DMAQ_SIZE);
	tx_queue->ptr_mask = entries - 1;

	netअगर_dbg(efx, probe, efx->net_dev,
		  "creating TX queue %d size %#x mask %#x\n",
		  tx_queue->queue, efx->txq_entries, tx_queue->ptr_mask);

	/* Allocate software ring */
	tx_queue->buffer = kसुस्मृति(entries, माप(*tx_queue->buffer),
				   GFP_KERNEL);
	अगर (!tx_queue->buffer)
		वापस -ENOMEM;

	tx_queue->cb_page = kसुस्मृति(efx_tx_cb_page_count(tx_queue),
				    माप(tx_queue->cb_page[0]), GFP_KERNEL);
	अगर (!tx_queue->cb_page) अणु
		rc = -ENOMEM;
		जाओ fail1;
	पूर्ण

	/* Allocate hardware ring, determine TXQ type */
	rc = efx_nic_probe_tx(tx_queue);
	अगर (rc)
		जाओ fail2;

	tx_queue->channel->tx_queue_by_type[tx_queue->type] = tx_queue;
	वापस 0;

fail2:
	kमुक्त(tx_queue->cb_page);
	tx_queue->cb_page = शून्य;
fail1:
	kमुक्त(tx_queue->buffer);
	tx_queue->buffer = शून्य;
	वापस rc;
पूर्ण

व्योम efx_init_tx_queue(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;

	netअगर_dbg(efx, drv, efx->net_dev,
		  "initialising TX queue %d\n", tx_queue->queue);

	tx_queue->insert_count = 0;
	tx_queue->notअगरy_count = 0;
	tx_queue->ग_लिखो_count = 0;
	tx_queue->packet_ग_लिखो_count = 0;
	tx_queue->old_ग_लिखो_count = 0;
	tx_queue->पढ़ो_count = 0;
	tx_queue->old_पढ़ो_count = 0;
	tx_queue->empty_पढ़ो_count = 0 | EFX_EMPTY_COUNT_VALID;
	tx_queue->xmit_pending = false;
	tx_queue->बारtamping = (efx_ptp_use_mac_tx_बारtamps(efx) &&
				  tx_queue->channel == efx_ptp_channel(efx));
	tx_queue->completed_बारtamp_major = 0;
	tx_queue->completed_बारtamp_minor = 0;

	tx_queue->xdp_tx = efx_channel_is_xdp_tx(tx_queue->channel);
	tx_queue->tso_version = 0;

	/* Set up TX descriptor ring */
	efx_nic_init_tx(tx_queue);

	tx_queue->initialised = true;
पूर्ण

व्योम efx_fini_tx_queue(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_tx_buffer *buffer;

	netअगर_dbg(tx_queue->efx, drv, tx_queue->efx->net_dev,
		  "shutting down TX queue %d\n", tx_queue->queue);

	अगर (!tx_queue->buffer)
		वापस;

	/* Free any buffers left in the ring */
	जबतक (tx_queue->पढ़ो_count != tx_queue->ग_लिखो_count) अणु
		अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;

		buffer = &tx_queue->buffer[tx_queue->पढ़ो_count & tx_queue->ptr_mask];
		efx_dequeue_buffer(tx_queue, buffer, &pkts_compl, &bytes_compl);

		++tx_queue->पढ़ो_count;
	पूर्ण
	tx_queue->xmit_pending = false;
	netdev_tx_reset_queue(tx_queue->core_txq);
पूर्ण

व्योम efx_हटाओ_tx_queue(काष्ठा efx_tx_queue *tx_queue)
अणु
	पूर्णांक i;

	अगर (!tx_queue->buffer)
		वापस;

	netअगर_dbg(tx_queue->efx, drv, tx_queue->efx->net_dev,
		  "destroying TX queue %d\n", tx_queue->queue);
	efx_nic_हटाओ_tx(tx_queue);

	अगर (tx_queue->cb_page) अणु
		क्रम (i = 0; i < efx_tx_cb_page_count(tx_queue); i++)
			efx_nic_मुक्त_buffer(tx_queue->efx,
					    &tx_queue->cb_page[i]);
		kमुक्त(tx_queue->cb_page);
		tx_queue->cb_page = शून्य;
	पूर्ण

	kमुक्त(tx_queue->buffer);
	tx_queue->buffer = शून्य;
	tx_queue->channel->tx_queue_by_type[tx_queue->type] = शून्य;
पूर्ण

व्योम efx_dequeue_buffer(काष्ठा efx_tx_queue *tx_queue,
			काष्ठा efx_tx_buffer *buffer,
			अचिन्हित पूर्णांक *pkts_compl,
			अचिन्हित पूर्णांक *bytes_compl)
अणु
	अगर (buffer->unmap_len) अणु
		काष्ठा device *dma_dev = &tx_queue->efx->pci_dev->dev;
		dma_addr_t unmap_addr = buffer->dma_addr - buffer->dma_offset;

		अगर (buffer->flags & EFX_TX_BUF_MAP_SINGLE)
			dma_unmap_single(dma_dev, unmap_addr, buffer->unmap_len,
					 DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(dma_dev, unmap_addr, buffer->unmap_len,
				       DMA_TO_DEVICE);
		buffer->unmap_len = 0;
	पूर्ण

	अगर (buffer->flags & EFX_TX_BUF_SKB) अणु
		काष्ठा sk_buff *skb = (काष्ठा sk_buff *)buffer->skb;

		EFX_WARN_ON_PARANOID(!pkts_compl || !bytes_compl);
		(*pkts_compl)++;
		(*bytes_compl) += skb->len;
		अगर (tx_queue->बारtamping &&
		    (tx_queue->completed_बारtamp_major ||
		     tx_queue->completed_बारtamp_minor)) अणु
			काष्ठा skb_shared_hwtstamps hwtstamp;

			hwtstamp.hwtstamp =
				efx_ptp_nic_to_kernel_समय(tx_queue);
			skb_tstamp_tx(skb, &hwtstamp);

			tx_queue->completed_बारtamp_major = 0;
			tx_queue->completed_बारtamp_minor = 0;
		पूर्ण
		dev_consume_skb_any((काष्ठा sk_buff *)buffer->skb);
		netअगर_vdbg(tx_queue->efx, tx_करोne, tx_queue->efx->net_dev,
			   "TX queue %d transmission id %x complete\n",
			   tx_queue->queue, tx_queue->पढ़ो_count);
	पूर्ण अन्यथा अगर (buffer->flags & EFX_TX_BUF_XDP) अणु
		xdp_वापस_frame_rx_napi(buffer->xdpf);
	पूर्ण

	buffer->len = 0;
	buffer->flags = 0;
पूर्ण

/* Remove packets from the TX queue
 *
 * This हटाओs packets from the TX queue, up to and including the
 * specअगरied index.
 */
अटल व्योम efx_dequeue_buffers(काष्ठा efx_tx_queue *tx_queue,
				अचिन्हित पूर्णांक index,
				अचिन्हित पूर्णांक *pkts_compl,
				अचिन्हित पूर्णांक *bytes_compl)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	अचिन्हित पूर्णांक stop_index, पढ़ो_ptr;

	stop_index = (index + 1) & tx_queue->ptr_mask;
	पढ़ो_ptr = tx_queue->पढ़ो_count & tx_queue->ptr_mask;

	जबतक (पढ़ो_ptr != stop_index) अणु
		काष्ठा efx_tx_buffer *buffer = &tx_queue->buffer[पढ़ो_ptr];

		अगर (!efx_tx_buffer_in_use(buffer)) अणु
			netअगर_err(efx, tx_err, efx->net_dev,
				  "TX queue %d spurious TX completion id %d\n",
				  tx_queue->queue, पढ़ो_ptr);
			efx_schedule_reset(efx, RESET_TYPE_TX_SKIP);
			वापस;
		पूर्ण

		efx_dequeue_buffer(tx_queue, buffer, pkts_compl, bytes_compl);

		++tx_queue->पढ़ो_count;
		पढ़ो_ptr = tx_queue->पढ़ो_count & tx_queue->ptr_mask;
	पूर्ण
पूर्ण

व्योम efx_xmit_करोne_check_empty(काष्ठा efx_tx_queue *tx_queue)
अणु
	अगर ((पूर्णांक)(tx_queue->पढ़ो_count - tx_queue->old_ग_लिखो_count) >= 0) अणु
		tx_queue->old_ग_लिखो_count = READ_ONCE(tx_queue->ग_लिखो_count);
		अगर (tx_queue->पढ़ो_count == tx_queue->old_ग_लिखो_count) अणु
			/* Ensure that पढ़ो_count is flushed. */
			smp_mb();
			tx_queue->empty_पढ़ो_count =
				tx_queue->पढ़ो_count | EFX_EMPTY_COUNT_VALID;
		पूर्ण
	पूर्ण
पूर्ण

व्योम efx_xmit_करोne(काष्ठा efx_tx_queue *tx_queue, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित पूर्णांक fill_level, pkts_compl = 0, bytes_compl = 0;
	काष्ठा efx_nic *efx = tx_queue->efx;

	EFX_WARN_ON_ONCE_PARANOID(index > tx_queue->ptr_mask);

	efx_dequeue_buffers(tx_queue, index, &pkts_compl, &bytes_compl);
	tx_queue->pkts_compl += pkts_compl;
	tx_queue->bytes_compl += bytes_compl;

	अगर (pkts_compl > 1)
		++tx_queue->merge_events;

	/* See अगर we need to restart the netअगर queue.  This memory
	 * barrier ensures that we ग_लिखो पढ़ो_count (inside
	 * efx_dequeue_buffers()) beक्रमe पढ़ोing the queue status.
	 */
	smp_mb();
	अगर (unlikely(netअगर_tx_queue_stopped(tx_queue->core_txq)) &&
	    likely(efx->port_enabled) &&
	    likely(netअगर_device_present(efx->net_dev))) अणु
		fill_level = efx_channel_tx_fill_level(tx_queue->channel);
		अगर (fill_level <= efx->txq_wake_thresh)
			netअगर_tx_wake_queue(tx_queue->core_txq);
	पूर्ण

	efx_xmit_करोne_check_empty(tx_queue);
पूर्ण

/* Remove buffers put पूर्णांकo a tx_queue क्रम the current packet.
 * None of the buffers must have an skb attached.
 */
व्योम efx_enqueue_unwind(काष्ठा efx_tx_queue *tx_queue,
			अचिन्हित पूर्णांक insert_count)
अणु
	काष्ठा efx_tx_buffer *buffer;
	अचिन्हित पूर्णांक bytes_compl = 0;
	अचिन्हित पूर्णांक pkts_compl = 0;

	/* Work backwards until we hit the original insert poपूर्णांकer value */
	जबतक (tx_queue->insert_count != insert_count) अणु
		--tx_queue->insert_count;
		buffer = __efx_tx_queue_get_insert_buffer(tx_queue);
		efx_dequeue_buffer(tx_queue, buffer, &pkts_compl, &bytes_compl);
	पूर्ण
पूर्ण

काष्ठा efx_tx_buffer *efx_tx_map_chunk(काष्ठा efx_tx_queue *tx_queue,
				       dma_addr_t dma_addr, माप_प्रकार len)
अणु
	स्थिर काष्ठा efx_nic_type *nic_type = tx_queue->efx->type;
	काष्ठा efx_tx_buffer *buffer;
	अचिन्हित पूर्णांक dma_len;

	/* Map the fragment taking account of NIC-dependent DMA limits. */
	करो अणु
		buffer = efx_tx_queue_get_insert_buffer(tx_queue);

		अगर (nic_type->tx_limit_len)
			dma_len = nic_type->tx_limit_len(tx_queue, dma_addr, len);
		अन्यथा
			dma_len = len;

		buffer->len = dma_len;
		buffer->dma_addr = dma_addr;
		buffer->flags = EFX_TX_BUF_CONT;
		len -= dma_len;
		dma_addr += dma_len;
		++tx_queue->insert_count;
	पूर्ण जबतक (len);

	वापस buffer;
पूर्ण

पूर्णांक efx_tx_tso_header_length(काष्ठा sk_buff *skb)
अणु
	माप_प्रकार header_len;

	अगर (skb->encapsulation)
		header_len = skb_inner_transport_header(skb) -
				skb->data +
				(inner_tcp_hdr(skb)->करोff << 2u);
	अन्यथा
		header_len = skb_transport_header(skb) - skb->data +
				(tcp_hdr(skb)->करोff << 2u);
	वापस header_len;
पूर्ण

/* Map all data from an SKB क्रम DMA and create descriptors on the queue. */
पूर्णांक efx_tx_map_data(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb,
		    अचिन्हित पूर्णांक segment_count)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	काष्ठा device *dma_dev = &efx->pci_dev->dev;
	अचिन्हित पूर्णांक frag_index, nr_frags;
	dma_addr_t dma_addr, unmap_addr;
	अचिन्हित लघु dma_flags;
	माप_प्रकार len, unmap_len;

	nr_frags = skb_shinfo(skb)->nr_frags;
	frag_index = 0;

	/* Map header data. */
	len = skb_headlen(skb);
	dma_addr = dma_map_single(dma_dev, skb->data, len, DMA_TO_DEVICE);
	dma_flags = EFX_TX_BUF_MAP_SINGLE;
	unmap_len = len;
	unmap_addr = dma_addr;

	अगर (unlikely(dma_mapping_error(dma_dev, dma_addr)))
		वापस -EIO;

	अगर (segment_count) अणु
		/* For TSO we need to put the header in to a separate
		 * descriptor. Map this separately अगर necessary.
		 */
		माप_प्रकार header_len = efx_tx_tso_header_length(skb);

		अगर (header_len != len) अणु
			tx_queue->tso_दीर्घ_headers++;
			efx_tx_map_chunk(tx_queue, dma_addr, header_len);
			len -= header_len;
			dma_addr += header_len;
		पूर्ण
	पूर्ण

	/* Add descriptors क्रम each fragment. */
	करो अणु
		काष्ठा efx_tx_buffer *buffer;
		skb_frag_t *fragment;

		buffer = efx_tx_map_chunk(tx_queue, dma_addr, len);

		/* The final descriptor क्रम a fragment is responsible क्रम
		 * unmapping the whole fragment.
		 */
		buffer->flags = EFX_TX_BUF_CONT | dma_flags;
		buffer->unmap_len = unmap_len;
		buffer->dma_offset = buffer->dma_addr - unmap_addr;

		अगर (frag_index >= nr_frags) अणु
			/* Store SKB details with the final buffer क्रम
			 * the completion.
			 */
			buffer->skb = skb;
			buffer->flags = EFX_TX_BUF_SKB | dma_flags;
			वापस 0;
		पूर्ण

		/* Move on to the next fragment. */
		fragment = &skb_shinfo(skb)->frags[frag_index++];
		len = skb_frag_size(fragment);
		dma_addr = skb_frag_dma_map(dma_dev, fragment, 0, len,
					    DMA_TO_DEVICE);
		dma_flags = 0;
		unmap_len = len;
		unmap_addr = dma_addr;

		अगर (unlikely(dma_mapping_error(dma_dev, dma_addr)))
			वापस -EIO;
	पूर्ण जबतक (1);
पूर्ण

अचिन्हित पूर्णांक efx_tx_max_skb_descs(काष्ठा efx_nic *efx)
अणु
	/* Header and payload descriptor क्रम each output segment, plus
	 * one क्रम every input fragment boundary within a segment
	 */
	अचिन्हित पूर्णांक max_descs = EFX_TSO_MAX_SEGS * 2 + MAX_SKB_FRAGS;

	/* Possibly one more per segment क्रम option descriptors */
	अगर (efx_nic_rev(efx) >= EFX_REV_HUNT_A0)
		max_descs += EFX_TSO_MAX_SEGS;

	/* Possibly more क्रम PCIe page boundaries within input fragments */
	अगर (PAGE_SIZE > EFX_PAGE_SIZE)
		max_descs += max_t(अचिन्हित पूर्णांक, MAX_SKB_FRAGS,
				   DIV_ROUND_UP(GSO_MAX_SIZE, EFX_PAGE_SIZE));

	वापस max_descs;
पूर्ण

/*
 * Fallback to software TSO.
 *
 * This is used अगर we are unable to send a GSO packet through hardware TSO.
 * This should only ever happen due to per-queue restrictions - unsupported
 * packets should first be filtered by the feature flags.
 *
 * Returns 0 on success, error code otherwise.
 */
पूर्णांक efx_tx_tso_fallback(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb)
अणु
	काष्ठा sk_buff *segments, *next;

	segments = skb_gso_segment(skb, 0);
	अगर (IS_ERR(segments))
		वापस PTR_ERR(segments);

	dev_consume_skb_any(skb);

	skb_list_walk_safe(segments, skb, next) अणु
		skb_mark_not_on_list(skb);
		efx_enqueue_skb(tx_queue, skb);
	पूर्ण

	वापस 0;
पूर्ण
