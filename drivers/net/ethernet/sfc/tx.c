<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2005-2013 Solarflare Communications Inc.
 */

#समावेश <linux/pci.h>
#समावेश <linux/tcp.h>
#समावेश <linux/ip.h>
#समावेश <linux/in.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/slab.h>
#समावेश <net/ipv6.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/highस्मृति.स>
#समावेश <linux/cache.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "io.h"
#समावेश "nic.h"
#समावेश "tx.h"
#समावेश "tx_common.h"
#समावेश "workarounds.h"
#समावेश "ef10_regs.h"

#अगर_घोषित EFX_USE_PIO

#घोषणा EFX_PIOBUF_SIZE_DEF ALIGN(256, L1_CACHE_BYTES)
अचिन्हित पूर्णांक efx_piobuf_size __पढ़ो_mostly = EFX_PIOBUF_SIZE_DEF;

#पूर्ण_अगर /* EFX_USE_PIO */

अटल अंतरभूत u8 *efx_tx_get_copy_buffer(काष्ठा efx_tx_queue *tx_queue,
					 काष्ठा efx_tx_buffer *buffer)
अणु
	अचिन्हित पूर्णांक index = efx_tx_queue_get_insert_index(tx_queue);
	काष्ठा efx_buffer *page_buf =
		&tx_queue->cb_page[index >> (PAGE_SHIFT - EFX_TX_CB_ORDER)];
	अचिन्हित पूर्णांक offset =
		((index << EFX_TX_CB_ORDER) + NET_IP_ALIGN) & (PAGE_SIZE - 1);

	अगर (unlikely(!page_buf->addr) &&
	    efx_nic_alloc_buffer(tx_queue->efx, page_buf, PAGE_SIZE,
				 GFP_ATOMIC))
		वापस शून्य;
	buffer->dma_addr = page_buf->dma_addr + offset;
	buffer->unmap_len = 0;
	वापस (u8 *)page_buf->addr + offset;
पूर्ण

u8 *efx_tx_get_copy_buffer_limited(काष्ठा efx_tx_queue *tx_queue,
				   काष्ठा efx_tx_buffer *buffer, माप_प्रकार len)
अणु
	अगर (len > EFX_TX_CB_SIZE)
		वापस शून्य;
	वापस efx_tx_get_copy_buffer(tx_queue, buffer);
पूर्ण

अटल व्योम efx_tx_maybe_stop_queue(काष्ठा efx_tx_queue *txq1)
अणु
	/* We need to consider all queues that the net core sees as one */
	काष्ठा efx_nic *efx = txq1->efx;
	काष्ठा efx_tx_queue *txq2;
	अचिन्हित पूर्णांक fill_level;

	fill_level = efx_channel_tx_old_fill_level(txq1->channel);
	अगर (likely(fill_level < efx->txq_stop_thresh))
		वापस;

	/* We used the stale old_पढ़ो_count above, which gives us a
	 * pessimistic estimate of the fill level (which may even
	 * validly be >= efx->txq_entries).  Now try again using
	 * पढ़ो_count (more likely to be a cache miss).
	 *
	 * If we पढ़ो पढ़ो_count and then conditionally stop the
	 * queue, it is possible क्रम the completion path to race with
	 * us and complete all outstanding descriptors in the middle,
	 * after which there will be no more completions to wake it.
	 * Thereक्रमe we stop the queue first, then पढ़ो पढ़ो_count
	 * (with a memory barrier to ensure the ordering), then
	 * restart the queue अगर the fill level turns out to be low
	 * enough.
	 */
	netअगर_tx_stop_queue(txq1->core_txq);
	smp_mb();
	efx_क्रम_each_channel_tx_queue(txq2, txq1->channel)
		txq2->old_पढ़ो_count = READ_ONCE(txq2->पढ़ो_count);

	fill_level = efx_channel_tx_old_fill_level(txq1->channel);
	EFX_WARN_ON_ONCE_PARANOID(fill_level >= efx->txq_entries);
	अगर (likely(fill_level < efx->txq_stop_thresh)) अणु
		smp_mb();
		अगर (likely(!efx->loopback_selftest))
			netअगर_tx_start_queue(txq1->core_txq);
	पूर्ण
पूर्ण

अटल पूर्णांक efx_enqueue_skb_copy(काष्ठा efx_tx_queue *tx_queue,
				काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक copy_len = skb->len;
	काष्ठा efx_tx_buffer *buffer;
	u8 *copy_buffer;
	पूर्णांक rc;

	EFX_WARN_ON_ONCE_PARANOID(copy_len > EFX_TX_CB_SIZE);

	buffer = efx_tx_queue_get_insert_buffer(tx_queue);

	copy_buffer = efx_tx_get_copy_buffer(tx_queue, buffer);
	अगर (unlikely(!copy_buffer))
		वापस -ENOMEM;

	rc = skb_copy_bits(skb, 0, copy_buffer, copy_len);
	EFX_WARN_ON_PARANOID(rc);
	buffer->len = copy_len;

	buffer->skb = skb;
	buffer->flags = EFX_TX_BUF_SKB;

	++tx_queue->insert_count;
	वापस rc;
पूर्ण

#अगर_घोषित EFX_USE_PIO

काष्ठा efx_लघु_copy_buffer अणु
	पूर्णांक used;
	u8 buf[L1_CACHE_BYTES];
पूर्ण;

/* Copy to PIO, respecting that ग_लिखोs to PIO buffers must be dword aligned.
 * Advances piobuf poपूर्णांकer. Leaves additional data in the copy buffer.
 */
अटल व्योम efx_स_नकल_toio_aligned(काष्ठा efx_nic *efx, u8 __iomem **piobuf,
				    u8 *data, पूर्णांक len,
				    काष्ठा efx_लघु_copy_buffer *copy_buf)
अणु
	पूर्णांक block_len = len & ~(माप(copy_buf->buf) - 1);

	__ioग_लिखो64_copy(*piobuf, data, block_len >> 3);
	*piobuf += block_len;
	len -= block_len;

	अगर (len) अणु
		data += block_len;
		BUG_ON(copy_buf->used);
		BUG_ON(len > माप(copy_buf->buf));
		स_नकल(copy_buf->buf, data, len);
		copy_buf->used = len;
	पूर्ण
पूर्ण

/* Copy to PIO, respecting dword alignment, popping data from copy buffer first.
 * Advances piobuf poपूर्णांकer. Leaves additional data in the copy buffer.
 */
अटल व्योम efx_स_नकल_toio_aligned_cb(काष्ठा efx_nic *efx, u8 __iomem **piobuf,
				       u8 *data, पूर्णांक len,
				       काष्ठा efx_लघु_copy_buffer *copy_buf)
अणु
	अगर (copy_buf->used) अणु
		/* अगर the copy buffer is partially full, fill it up and ग_लिखो */
		पूर्णांक copy_to_buf =
			min_t(पूर्णांक, माप(copy_buf->buf) - copy_buf->used, len);

		स_नकल(copy_buf->buf + copy_buf->used, data, copy_to_buf);
		copy_buf->used += copy_to_buf;

		/* अगर we didn't fill it up then we're करोne क्रम now */
		अगर (copy_buf->used < माप(copy_buf->buf))
			वापस;

		__ioग_लिखो64_copy(*piobuf, copy_buf->buf,
				 माप(copy_buf->buf) >> 3);
		*piobuf += माप(copy_buf->buf);
		data += copy_to_buf;
		len -= copy_to_buf;
		copy_buf->used = 0;
	पूर्ण

	efx_स_नकल_toio_aligned(efx, piobuf, data, len, copy_buf);
पूर्ण

अटल व्योम efx_flush_copy_buffer(काष्ठा efx_nic *efx, u8 __iomem *piobuf,
				  काष्ठा efx_लघु_copy_buffer *copy_buf)
अणु
	/* अगर there's anything in it, ग_लिखो the whole buffer, including junk */
	अगर (copy_buf->used)
		__ioग_लिखो64_copy(piobuf, copy_buf->buf,
				 माप(copy_buf->buf) >> 3);
पूर्ण

/* Traverse skb काष्ठाure and copy fragments in to PIO buffer.
 * Advances piobuf poपूर्णांकer.
 */
अटल व्योम efx_skb_copy_bits_to_pio(काष्ठा efx_nic *efx, काष्ठा sk_buff *skb,
				     u8 __iomem **piobuf,
				     काष्ठा efx_लघु_copy_buffer *copy_buf)
अणु
	पूर्णांक i;

	efx_स_नकल_toio_aligned(efx, piobuf, skb->data, skb_headlen(skb),
				copy_buf);

	क्रम (i = 0; i < skb_shinfo(skb)->nr_frags; ++i) अणु
		skb_frag_t *f = &skb_shinfo(skb)->frags[i];
		u8 *vaddr;

		vaddr = kmap_atomic(skb_frag_page(f));

		efx_स_नकल_toio_aligned_cb(efx, piobuf, vaddr + skb_frag_off(f),
					   skb_frag_size(f), copy_buf);
		kunmap_atomic(vaddr);
	पूर्ण

	EFX_WARN_ON_ONCE_PARANOID(skb_shinfo(skb)->frag_list);
पूर्ण

अटल पूर्णांक efx_enqueue_skb_pio(काष्ठा efx_tx_queue *tx_queue,
			       काष्ठा sk_buff *skb)
अणु
	काष्ठा efx_tx_buffer *buffer =
		efx_tx_queue_get_insert_buffer(tx_queue);
	u8 __iomem *piobuf = tx_queue->piobuf;

	/* Copy to PIO buffer. Ensure the ग_लिखोs are padded to the end
	 * of a cache line, as this is required क्रम ग_लिखो-combining to be
	 * effective on at least x86.
	 */

	अगर (skb_shinfo(skb)->nr_frags) अणु
		/* The size of the copy buffer will ensure all ग_लिखोs
		 * are the size of a cache line.
		 */
		काष्ठा efx_लघु_copy_buffer copy_buf;

		copy_buf.used = 0;

		efx_skb_copy_bits_to_pio(tx_queue->efx, skb,
					 &piobuf, &copy_buf);
		efx_flush_copy_buffer(tx_queue->efx, piobuf, &copy_buf);
	पूर्ण अन्यथा अणु
		/* Pad the ग_लिखो to the size of a cache line.
		 * We can करो this because we know the skb_shared_info काष्ठा is
		 * after the source, and the destination buffer is big enough.
		 */
		BUILD_BUG_ON(L1_CACHE_BYTES >
			     SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)));
		__ioग_लिखो64_copy(tx_queue->piobuf, skb->data,
				 ALIGN(skb->len, L1_CACHE_BYTES) >> 3);
	पूर्ण

	buffer->skb = skb;
	buffer->flags = EFX_TX_BUF_SKB | EFX_TX_BUF_OPTION;

	EFX_POPULATE_QWORD_5(buffer->option,
			     ESF_DZ_TX_DESC_IS_OPT, 1,
			     ESF_DZ_TX_OPTION_TYPE, ESE_DZ_TX_OPTION_DESC_PIO,
			     ESF_DZ_TX_PIO_CONT, 0,
			     ESF_DZ_TX_PIO_BYTE_CNT, skb->len,
			     ESF_DZ_TX_PIO_BUF_ADDR,
			     tx_queue->piobuf_offset);
	++tx_queue->insert_count;
	वापस 0;
पूर्ण

/* Decide whether we can use TX PIO, ie. ग_लिखो packet data directly पूर्णांकo
 * a buffer on the device.  This can reduce latency at the expense of
 * throughput, so we only करो this अगर both hardware and software TX rings
 * are empty, including all queues क्रम the channel.  This also ensures that
 * only one packet at a समय can be using the PIO buffer. If the xmit_more
 * flag is set then we करोn't use this - there'll be another packet aदीर्घ
 * लघुly and we want to hold off the करोorbell.
 */
अटल bool efx_tx_may_pio(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_channel *channel = tx_queue->channel;

	अगर (!tx_queue->piobuf)
		वापस false;

	EFX_WARN_ON_ONCE_PARANOID(!channel->efx->type->option_descriptors);

	efx_क्रम_each_channel_tx_queue(tx_queue, channel)
		अगर (!efx_nic_tx_is_empty(tx_queue, tx_queue->packet_ग_लिखो_count))
			वापस false;

	वापस true;
पूर्ण
#पूर्ण_अगर /* EFX_USE_PIO */

/* Send any pending traffic क्रम a channel. xmit_more is shared across all
 * queues क्रम a channel, so we must check all of them.
 */
अटल व्योम efx_tx_send_pending(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_tx_queue *q;

	efx_क्रम_each_channel_tx_queue(q, channel) अणु
		अगर (q->xmit_pending)
			efx_nic_push_buffers(q);
	पूर्ण
पूर्ण

/*
 * Add a socket buffer to a TX queue
 *
 * This maps all fragments of a socket buffer क्रम DMA and adds them to
 * the TX queue.  The queue's insert poपूर्णांकer will be incremented by
 * the number of fragments in the socket buffer.
 *
 * If any DMA mapping fails, any mapped fragments will be unmapped,
 * the queue's insert poपूर्णांकer will be restored to its original value.
 *
 * This function is split out from efx_hard_start_xmit to allow the
 * loopback test to direct packets via specअगरic TX queues.
 *
 * Returns NETDEV_TX_OK.
 * You must hold netअगर_tx_lock() to call this function.
 */
netdev_tx_t __efx_enqueue_skb(काष्ठा efx_tx_queue *tx_queue, काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक old_insert_count = tx_queue->insert_count;
	bool xmit_more = netdev_xmit_more();
	bool data_mapped = false;
	अचिन्हित पूर्णांक segments;
	अचिन्हित पूर्णांक skb_len;
	पूर्णांक rc;

	skb_len = skb->len;
	segments = skb_is_gso(skb) ? skb_shinfo(skb)->gso_segs : 0;
	अगर (segments == 1)
		segments = 0; /* Don't use TSO क्रम a single segment. */

	/* Handle TSO first - it's *possible* (although unlikely) that we might
	 * be passed a packet to segment that's smaller than the copyअवरोध/PIO
	 * size limit.
	 */
	अगर (segments) अणु
		चयन (tx_queue->tso_version) अणु
		हाल 1:
			rc = efx_enqueue_skb_tso(tx_queue, skb, &data_mapped);
			अवरोध;
		हाल 2:
			rc = efx_ef10_tx_tso_desc(tx_queue, skb, &data_mapped);
			अवरोध;
		हाल 0: /* No TSO on this queue, SW fallback needed */
		शेष:
			rc = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (rc == -EINVAL) अणु
			rc = efx_tx_tso_fallback(tx_queue, skb);
			tx_queue->tso_fallbacks++;
			अगर (rc == 0)
				वापस 0;
		पूर्ण
		अगर (rc)
			जाओ err;
#अगर_घोषित EFX_USE_PIO
	पूर्ण अन्यथा अगर (skb_len <= efx_piobuf_size && !xmit_more &&
		   efx_tx_may_pio(tx_queue)) अणु
		/* Use PIO क्रम लघु packets with an empty queue. */
		अगर (efx_enqueue_skb_pio(tx_queue, skb))
			जाओ err;
		tx_queue->pio_packets++;
		data_mapped = true;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (skb->data_len && skb_len <= EFX_TX_CB_SIZE) अणु
		/* Pad लघु packets or coalesce लघु fragmented packets. */
		अगर (efx_enqueue_skb_copy(tx_queue, skb))
			जाओ err;
		tx_queue->cb_packets++;
		data_mapped = true;
	पूर्ण

	/* Map क्रम DMA and create descriptors अगर we haven't करोne so alपढ़ोy. */
	अगर (!data_mapped && (efx_tx_map_data(tx_queue, skb, segments)))
		जाओ err;

	efx_tx_maybe_stop_queue(tx_queue);

	tx_queue->xmit_pending = true;

	/* Pass off to hardware */
	अगर (__netdev_tx_sent_queue(tx_queue->core_txq, skb_len, xmit_more))
		efx_tx_send_pending(tx_queue->channel);

	अगर (segments) अणु
		tx_queue->tso_bursts++;
		tx_queue->tso_packets += segments;
		tx_queue->tx_packets  += segments;
	पूर्ण अन्यथा अणु
		tx_queue->tx_packets++;
	पूर्ण

	वापस NETDEV_TX_OK;


err:
	efx_enqueue_unwind(tx_queue, old_insert_count);
	dev_kमुक्त_skb_any(skb);

	/* If we're not expecting another transmit and we had something to push
	 * on this queue or a partner queue then we need to push here to get the
	 * previous packets out.
	 */
	अगर (!xmit_more)
		efx_tx_send_pending(tx_queue->channel);

	वापस NETDEV_TX_OK;
पूर्ण

/* Transmit a packet from an XDP buffer
 *
 * Returns number of packets sent on success, error code otherwise.
 * Runs in NAPI context, either in our poll (क्रम XDP TX) or a dअगरferent NIC
 * (क्रम XDP redirect).
 */
पूर्णांक efx_xdp_tx_buffers(काष्ठा efx_nic *efx, पूर्णांक n, काष्ठा xdp_frame **xdpfs,
		       bool flush)
अणु
	काष्ठा efx_tx_buffer *tx_buffer;
	काष्ठा efx_tx_queue *tx_queue;
	काष्ठा xdp_frame *xdpf;
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक len;
	पूर्णांक space;
	पूर्णांक cpu;
	पूर्णांक i;

	cpu = raw_smp_processor_id();

	अगर (!efx->xdp_tx_queue_count ||
	    unlikely(cpu >= efx->xdp_tx_queue_count))
		वापस -EINVAL;

	tx_queue = efx->xdp_tx_queues[cpu];
	अगर (unlikely(!tx_queue))
		वापस -EINVAL;

	अगर (unlikely(n && !xdpfs))
		वापस -EINVAL;

	अगर (!n)
		वापस 0;

	/* Check क्रम available space. We should never need multiple
	 * descriptors per frame.
	 */
	space = efx->txq_entries +
		tx_queue->पढ़ो_count - tx_queue->insert_count;

	क्रम (i = 0; i < n; i++) अणु
		xdpf = xdpfs[i];

		अगर (i >= space)
			अवरोध;

		/* We'll want a descriptor क्रम this tx. */
		prefetchw(__efx_tx_queue_get_insert_buffer(tx_queue));

		len = xdpf->len;

		/* Map क्रम DMA. */
		dma_addr = dma_map_single(&efx->pci_dev->dev,
					  xdpf->data, len,
					  DMA_TO_DEVICE);
		अगर (dma_mapping_error(&efx->pci_dev->dev, dma_addr))
			अवरोध;

		/*  Create descriptor and set up क्रम unmapping DMA. */
		tx_buffer = efx_tx_map_chunk(tx_queue, dma_addr, len);
		tx_buffer->xdpf = xdpf;
		tx_buffer->flags = EFX_TX_BUF_XDP |
				   EFX_TX_BUF_MAP_SINGLE;
		tx_buffer->dma_offset = 0;
		tx_buffer->unmap_len = len;
		tx_queue->tx_packets++;
	पूर्ण

	/* Pass mapped frames to hardware. */
	अगर (flush && i > 0)
		efx_nic_push_buffers(tx_queue);

	वापस i == 0 ? -EIO : i;
पूर्ण

/* Initiate a packet transmission.  We use one channel per CPU
 * (sharing when we have more CPUs than channels).
 *
 * Context: non-blocking.
 * Should always वापस NETDEV_TX_OK and consume the skb.
 */
netdev_tx_t efx_hard_start_xmit(काष्ठा sk_buff *skb,
				काष्ठा net_device *net_dev)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा efx_tx_queue *tx_queue;
	अचिन्हित index, type;

	EFX_WARN_ON_PARANOID(!netअगर_device_present(net_dev));

	index = skb_get_queue_mapping(skb);
	type = efx_tx_csum_type_skb(skb);
	अगर (index >= efx->n_tx_channels) अणु
		index -= efx->n_tx_channels;
		type |= EFX_TXQ_TYPE_HIGHPRI;
	पूर्ण

	/* PTP "event" packet */
	अगर (unlikely(efx_xmit_with_hwtstamp(skb)) &&
	    unlikely(efx_ptp_is_ptp_tx(efx, skb))) अणु
		/* There may be existing transmits on the channel that are
		 * रुकोing क्रम this packet to trigger the करोorbell ग_लिखो.
		 * We need to send the packets at this poपूर्णांक.
		 */
		efx_tx_send_pending(efx_get_tx_channel(efx, index));
		वापस efx_ptp_tx(efx, skb);
	पूर्ण

	tx_queue = efx_get_tx_queue(efx, index, type);
	अगर (WARN_ON_ONCE(!tx_queue)) अणु
		/* We करोn't have a TXQ of the right type.
		 * This should never happen, as we करोn't advertise offload
		 * features unless we can support them.
		 */
		dev_kमुक्त_skb_any(skb);
		/* If we're not expecting another transmit and we had something to push
		 * on this queue or a partner queue then we need to push here to get the
		 * previous packets out.
		 */
		अगर (!netdev_xmit_more())
			efx_tx_send_pending(tx_queue->channel);
		वापस NETDEV_TX_OK;
	पूर्ण

	वापस __efx_enqueue_skb(tx_queue, skb);
पूर्ण

व्योम efx_xmit_करोne_single(काष्ठा efx_tx_queue *tx_queue)
अणु
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;
	अचिन्हित पूर्णांक पढ़ो_ptr;
	bool finished = false;

	पढ़ो_ptr = tx_queue->पढ़ो_count & tx_queue->ptr_mask;

	जबतक (!finished) अणु
		काष्ठा efx_tx_buffer *buffer = &tx_queue->buffer[पढ़ो_ptr];

		अगर (!efx_tx_buffer_in_use(buffer)) अणु
			काष्ठा efx_nic *efx = tx_queue->efx;

			netअगर_err(efx, hw, efx->net_dev,
				  "TX queue %d spurious single TX completion\n",
				  tx_queue->queue);
			efx_schedule_reset(efx, RESET_TYPE_TX_SKIP);
			वापस;
		पूर्ण

		/* Need to check the flag beक्रमe dequeueing. */
		अगर (buffer->flags & EFX_TX_BUF_SKB)
			finished = true;
		efx_dequeue_buffer(tx_queue, buffer, &pkts_compl, &bytes_compl);

		++tx_queue->पढ़ो_count;
		पढ़ो_ptr = tx_queue->पढ़ो_count & tx_queue->ptr_mask;
	पूर्ण

	tx_queue->pkts_compl += pkts_compl;
	tx_queue->bytes_compl += bytes_compl;

	EFX_WARN_ON_PARANOID(pkts_compl != 1);

	efx_xmit_करोne_check_empty(tx_queue);
पूर्ण

व्योम efx_init_tx_queue_core_txq(काष्ठा efx_tx_queue *tx_queue)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;

	/* Must be inverse of queue lookup in efx_hard_start_xmit() */
	tx_queue->core_txq =
		netdev_get_tx_queue(efx->net_dev,
				    tx_queue->channel->channel +
				    ((tx_queue->type & EFX_TXQ_TYPE_HIGHPRI) ?
				     efx->n_tx_channels : 0));
पूर्ण

पूर्णांक efx_setup_tc(काष्ठा net_device *net_dev, क्रमागत tc_setup_type type,
		 व्योम *type_data)
अणु
	काष्ठा efx_nic *efx = netdev_priv(net_dev);
	काष्ठा tc_mqprio_qopt *mqprio = type_data;
	अचिन्हित tc, num_tc;

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	/* Only Siena supported highpri queues */
	अगर (efx_nic_rev(efx) > EFX_REV_SIENA_A0)
		वापस -EOPNOTSUPP;

	num_tc = mqprio->num_tc;

	अगर (num_tc > EFX_MAX_TX_TC)
		वापस -EINVAL;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

	अगर (num_tc == net_dev->num_tc)
		वापस 0;

	क्रम (tc = 0; tc < num_tc; tc++) अणु
		net_dev->tc_to_txq[tc].offset = tc * efx->n_tx_channels;
		net_dev->tc_to_txq[tc].count = efx->n_tx_channels;
	पूर्ण

	net_dev->num_tc = num_tc;

	वापस netअगर_set_real_num_tx_queues(net_dev,
					    max_t(पूर्णांक, num_tc, 1) *
					    efx->n_tx_channels);
पूर्ण
