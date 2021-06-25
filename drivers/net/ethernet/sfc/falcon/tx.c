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
#समावेश "workarounds.h"

अटल अंतरभूत u8 *ef4_tx_get_copy_buffer(काष्ठा ef4_tx_queue *tx_queue,
					 काष्ठा ef4_tx_buffer *buffer)
अणु
	अचिन्हित पूर्णांक index = ef4_tx_queue_get_insert_index(tx_queue);
	काष्ठा ef4_buffer *page_buf =
		&tx_queue->cb_page[index >> (PAGE_SHIFT - EF4_TX_CB_ORDER)];
	अचिन्हित पूर्णांक offset =
		((index << EF4_TX_CB_ORDER) + NET_IP_ALIGN) & (PAGE_SIZE - 1);

	अगर (unlikely(!page_buf->addr) &&
	    ef4_nic_alloc_buffer(tx_queue->efx, page_buf, PAGE_SIZE,
				 GFP_ATOMIC))
		वापस शून्य;
	buffer->dma_addr = page_buf->dma_addr + offset;
	buffer->unmap_len = 0;
	वापस (u8 *)page_buf->addr + offset;
पूर्ण

u8 *ef4_tx_get_copy_buffer_limited(काष्ठा ef4_tx_queue *tx_queue,
				   काष्ठा ef4_tx_buffer *buffer, माप_प्रकार len)
अणु
	अगर (len > EF4_TX_CB_SIZE)
		वापस शून्य;
	वापस ef4_tx_get_copy_buffer(tx_queue, buffer);
पूर्ण

अटल व्योम ef4_dequeue_buffer(काष्ठा ef4_tx_queue *tx_queue,
			       काष्ठा ef4_tx_buffer *buffer,
			       अचिन्हित पूर्णांक *pkts_compl,
			       अचिन्हित पूर्णांक *bytes_compl)
अणु
	अगर (buffer->unmap_len) अणु
		काष्ठा device *dma_dev = &tx_queue->efx->pci_dev->dev;
		dma_addr_t unmap_addr = buffer->dma_addr - buffer->dma_offset;
		अगर (buffer->flags & EF4_TX_BUF_MAP_SINGLE)
			dma_unmap_single(dma_dev, unmap_addr, buffer->unmap_len,
					 DMA_TO_DEVICE);
		अन्यथा
			dma_unmap_page(dma_dev, unmap_addr, buffer->unmap_len,
				       DMA_TO_DEVICE);
		buffer->unmap_len = 0;
	पूर्ण

	अगर (buffer->flags & EF4_TX_BUF_SKB) अणु
		(*pkts_compl)++;
		(*bytes_compl) += buffer->skb->len;
		dev_consume_skb_any((काष्ठा sk_buff *)buffer->skb);
		netअगर_vdbg(tx_queue->efx, tx_करोne, tx_queue->efx->net_dev,
			   "TX queue %d transmission id %x complete\n",
			   tx_queue->queue, tx_queue->पढ़ो_count);
	पूर्ण

	buffer->len = 0;
	buffer->flags = 0;
पूर्ण

अचिन्हित पूर्णांक ef4_tx_max_skb_descs(काष्ठा ef4_nic *efx)
अणु
	/* This is probably too much since we करोn't have any TSO support;
	 * it's a left-over from when we had Software TSO.  But it's safer
	 * to leave it as-is than try to determine a new bound.
	 */
	/* Header and payload descriptor क्रम each output segment, plus
	 * one क्रम every input fragment boundary within a segment
	 */
	अचिन्हित पूर्णांक max_descs = EF4_TSO_MAX_SEGS * 2 + MAX_SKB_FRAGS;

	/* Possibly one more per segment क्रम the alignment workaround,
	 * or क्रम option descriptors
	 */
	अगर (EF4_WORKAROUND_5391(efx))
		max_descs += EF4_TSO_MAX_SEGS;

	/* Possibly more क्रम PCIe page boundaries within input fragments */
	अगर (PAGE_SIZE > EF4_PAGE_SIZE)
		max_descs += max_t(अचिन्हित पूर्णांक, MAX_SKB_FRAGS,
				   DIV_ROUND_UP(GSO_MAX_SIZE, EF4_PAGE_SIZE));

	वापस max_descs;
पूर्ण

अटल व्योम ef4_tx_maybe_stop_queue(काष्ठा ef4_tx_queue *txq1)
अणु
	/* We need to consider both queues that the net core sees as one */
	काष्ठा ef4_tx_queue *txq2 = ef4_tx_queue_partner(txq1);
	काष्ठा ef4_nic *efx = txq1->efx;
	अचिन्हित पूर्णांक fill_level;

	fill_level = max(txq1->insert_count - txq1->old_पढ़ो_count,
			 txq2->insert_count - txq2->old_पढ़ो_count);
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
	txq1->old_पढ़ो_count = READ_ONCE(txq1->पढ़ो_count);
	txq2->old_पढ़ो_count = READ_ONCE(txq2->पढ़ो_count);

	fill_level = max(txq1->insert_count - txq1->old_पढ़ो_count,
			 txq2->insert_count - txq2->old_पढ़ो_count);
	EF4_BUG_ON_PARANOID(fill_level >= efx->txq_entries);
	अगर (likely(fill_level < efx->txq_stop_thresh)) अणु
		smp_mb();
		अगर (likely(!efx->loopback_selftest))
			netअगर_tx_start_queue(txq1->core_txq);
	पूर्ण
पूर्ण

अटल पूर्णांक ef4_enqueue_skb_copy(काष्ठा ef4_tx_queue *tx_queue,
				काष्ठा sk_buff *skb)
अणु
	अचिन्हित पूर्णांक min_len = tx_queue->tx_min_size;
	अचिन्हित पूर्णांक copy_len = skb->len;
	काष्ठा ef4_tx_buffer *buffer;
	u8 *copy_buffer;
	पूर्णांक rc;

	EF4_BUG_ON_PARANOID(copy_len > EF4_TX_CB_SIZE);

	buffer = ef4_tx_queue_get_insert_buffer(tx_queue);

	copy_buffer = ef4_tx_get_copy_buffer(tx_queue, buffer);
	अगर (unlikely(!copy_buffer))
		वापस -ENOMEM;

	rc = skb_copy_bits(skb, 0, copy_buffer, copy_len);
	EF4_WARN_ON_PARANOID(rc);
	अगर (unlikely(copy_len < min_len)) अणु
		स_रखो(copy_buffer + copy_len, 0, min_len - copy_len);
		buffer->len = min_len;
	पूर्ण अन्यथा अणु
		buffer->len = copy_len;
	पूर्ण

	buffer->skb = skb;
	buffer->flags = EF4_TX_BUF_SKB;

	++tx_queue->insert_count;
	वापस rc;
पूर्ण

अटल काष्ठा ef4_tx_buffer *ef4_tx_map_chunk(काष्ठा ef4_tx_queue *tx_queue,
					      dma_addr_t dma_addr,
					      माप_प्रकार len)
अणु
	स्थिर काष्ठा ef4_nic_type *nic_type = tx_queue->efx->type;
	काष्ठा ef4_tx_buffer *buffer;
	अचिन्हित पूर्णांक dma_len;

	/* Map the fragment taking account of NIC-dependent DMA limits. */
	करो अणु
		buffer = ef4_tx_queue_get_insert_buffer(tx_queue);
		dma_len = nic_type->tx_limit_len(tx_queue, dma_addr, len);

		buffer->len = dma_len;
		buffer->dma_addr = dma_addr;
		buffer->flags = EF4_TX_BUF_CONT;
		len -= dma_len;
		dma_addr += dma_len;
		++tx_queue->insert_count;
	पूर्ण जबतक (len);

	वापस buffer;
पूर्ण

/* Map all data from an SKB क्रम DMA and create descriptors on the queue.
 */
अटल पूर्णांक ef4_tx_map_data(काष्ठा ef4_tx_queue *tx_queue, काष्ठा sk_buff *skb)
अणु
	काष्ठा ef4_nic *efx = tx_queue->efx;
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
	dma_flags = EF4_TX_BUF_MAP_SINGLE;
	unmap_len = len;
	unmap_addr = dma_addr;

	अगर (unlikely(dma_mapping_error(dma_dev, dma_addr)))
		वापस -EIO;

	/* Add descriptors क्रम each fragment. */
	करो अणु
		काष्ठा ef4_tx_buffer *buffer;
		skb_frag_t *fragment;

		buffer = ef4_tx_map_chunk(tx_queue, dma_addr, len);

		/* The final descriptor क्रम a fragment is responsible क्रम
		 * unmapping the whole fragment.
		 */
		buffer->flags = EF4_TX_BUF_CONT | dma_flags;
		buffer->unmap_len = unmap_len;
		buffer->dma_offset = buffer->dma_addr - unmap_addr;

		अगर (frag_index >= nr_frags) अणु
			/* Store SKB details with the final buffer क्रम
			 * the completion.
			 */
			buffer->skb = skb;
			buffer->flags = EF4_TX_BUF_SKB | dma_flags;
			वापस 0;
		पूर्ण

		/* Move on to the next fragment. */
		fragment = &skb_shinfo(skb)->frags[frag_index++];
		len = skb_frag_size(fragment);
		dma_addr = skb_frag_dma_map(dma_dev, fragment,
				0, len, DMA_TO_DEVICE);
		dma_flags = 0;
		unmap_len = len;
		unmap_addr = dma_addr;

		अगर (unlikely(dma_mapping_error(dma_dev, dma_addr)))
			वापस -EIO;
	पूर्ण जबतक (1);
पूर्ण

/* Remove buffers put पूर्णांकo a tx_queue.  None of the buffers must have
 * an skb attached.
 */
अटल व्योम ef4_enqueue_unwind(काष्ठा ef4_tx_queue *tx_queue)
अणु
	काष्ठा ef4_tx_buffer *buffer;

	/* Work backwards until we hit the original insert poपूर्णांकer value */
	जबतक (tx_queue->insert_count != tx_queue->ग_लिखो_count) अणु
		--tx_queue->insert_count;
		buffer = __ef4_tx_queue_get_insert_buffer(tx_queue);
		ef4_dequeue_buffer(tx_queue, buffer, शून्य, शून्य);
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
 * This function is split out from ef4_hard_start_xmit to allow the
 * loopback test to direct packets via specअगरic TX queues.
 *
 * Returns NETDEV_TX_OK.
 * You must hold netअगर_tx_lock() to call this function.
 */
netdev_tx_t ef4_enqueue_skb(काष्ठा ef4_tx_queue *tx_queue, काष्ठा sk_buff *skb)
अणु
	bool data_mapped = false;
	अचिन्हित पूर्णांक skb_len;

	skb_len = skb->len;
	EF4_WARN_ON_PARANOID(skb_is_gso(skb));

	अगर (skb_len < tx_queue->tx_min_size ||
			(skb->data_len && skb_len <= EF4_TX_CB_SIZE)) अणु
		/* Pad लघु packets or coalesce लघु fragmented packets. */
		अगर (ef4_enqueue_skb_copy(tx_queue, skb))
			जाओ err;
		tx_queue->cb_packets++;
		data_mapped = true;
	पूर्ण

	/* Map क्रम DMA and create descriptors अगर we haven't करोne so alपढ़ोy. */
	अगर (!data_mapped && (ef4_tx_map_data(tx_queue, skb)))
		जाओ err;

	/* Update BQL */
	netdev_tx_sent_queue(tx_queue->core_txq, skb_len);

	/* Pass off to hardware */
	अगर (!netdev_xmit_more() || netअगर_xmit_stopped(tx_queue->core_txq)) अणु
		काष्ठा ef4_tx_queue *txq2 = ef4_tx_queue_partner(tx_queue);

		/* There could be packets left on the partner queue अगर those
		 * SKBs had skb->xmit_more set. If we करो not push those they
		 * could be left क्रम a दीर्घ समय and cause a netdev watchकरोg.
		 */
		अगर (txq2->xmit_more_available)
			ef4_nic_push_buffers(txq2);

		ef4_nic_push_buffers(tx_queue);
	पूर्ण अन्यथा अणु
		tx_queue->xmit_more_available = netdev_xmit_more();
	पूर्ण

	tx_queue->tx_packets++;

	ef4_tx_maybe_stop_queue(tx_queue);

	वापस NETDEV_TX_OK;


err:
	ef4_enqueue_unwind(tx_queue);
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/* Remove packets from the TX queue
 *
 * This हटाओs packets from the TX queue, up to and including the
 * specअगरied index.
 */
अटल व्योम ef4_dequeue_buffers(काष्ठा ef4_tx_queue *tx_queue,
				अचिन्हित पूर्णांक index,
				अचिन्हित पूर्णांक *pkts_compl,
				अचिन्हित पूर्णांक *bytes_compl)
अणु
	काष्ठा ef4_nic *efx = tx_queue->efx;
	अचिन्हित पूर्णांक stop_index, पढ़ो_ptr;

	stop_index = (index + 1) & tx_queue->ptr_mask;
	पढ़ो_ptr = tx_queue->पढ़ो_count & tx_queue->ptr_mask;

	जबतक (पढ़ो_ptr != stop_index) अणु
		काष्ठा ef4_tx_buffer *buffer = &tx_queue->buffer[पढ़ो_ptr];

		अगर (!(buffer->flags & EF4_TX_BUF_OPTION) &&
		    unlikely(buffer->len == 0)) अणु
			netअगर_err(efx, tx_err, efx->net_dev,
				  "TX queue %d spurious TX completion id %x\n",
				  tx_queue->queue, पढ़ो_ptr);
			ef4_schedule_reset(efx, RESET_TYPE_TX_SKIP);
			वापस;
		पूर्ण

		ef4_dequeue_buffer(tx_queue, buffer, pkts_compl, bytes_compl);

		++tx_queue->पढ़ो_count;
		पढ़ो_ptr = tx_queue->पढ़ो_count & tx_queue->ptr_mask;
	पूर्ण
पूर्ण

/* Initiate a packet transmission.  We use one channel per CPU
 * (sharing when we have more CPUs than channels).  On Falcon, the TX
 * completion events will be directed back to the CPU that transmitted
 * the packet, which should be cache-efficient.
 *
 * Context: non-blocking.
 * Note that वापसing anything other than NETDEV_TX_OK will cause the
 * OS to मुक्त the skb.
 */
netdev_tx_t ef4_hard_start_xmit(काष्ठा sk_buff *skb,
				काष्ठा net_device *net_dev)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा ef4_tx_queue *tx_queue;
	अचिन्हित index, type;

	EF4_WARN_ON_PARANOID(!netअगर_device_present(net_dev));

	index = skb_get_queue_mapping(skb);
	type = skb->ip_summed == CHECKSUM_PARTIAL ? EF4_TXQ_TYPE_OFFLOAD : 0;
	अगर (index >= efx->n_tx_channels) अणु
		index -= efx->n_tx_channels;
		type |= EF4_TXQ_TYPE_HIGHPRI;
	पूर्ण
	tx_queue = ef4_get_tx_queue(efx, index, type);

	वापस ef4_enqueue_skb(tx_queue, skb);
पूर्ण

व्योम ef4_init_tx_queue_core_txq(काष्ठा ef4_tx_queue *tx_queue)
अणु
	काष्ठा ef4_nic *efx = tx_queue->efx;

	/* Must be inverse of queue lookup in ef4_hard_start_xmit() */
	tx_queue->core_txq =
		netdev_get_tx_queue(efx->net_dev,
				    tx_queue->queue / EF4_TXQ_TYPES +
				    ((tx_queue->queue & EF4_TXQ_TYPE_HIGHPRI) ?
				     efx->n_tx_channels : 0));
पूर्ण

पूर्णांक ef4_setup_tc(काष्ठा net_device *net_dev, क्रमागत tc_setup_type type,
		 व्योम *type_data)
अणु
	काष्ठा ef4_nic *efx = netdev_priv(net_dev);
	काष्ठा tc_mqprio_qopt *mqprio = type_data;
	काष्ठा ef4_channel *channel;
	काष्ठा ef4_tx_queue *tx_queue;
	अचिन्हित tc, num_tc;
	पूर्णांक rc;

	अगर (type != TC_SETUP_QDISC_MQPRIO)
		वापस -EOPNOTSUPP;

	num_tc = mqprio->num_tc;

	अगर (ef4_nic_rev(efx) < EF4_REV_FALCON_B0 || num_tc > EF4_MAX_TX_TC)
		वापस -EINVAL;

	mqprio->hw = TC_MQPRIO_HW_OFFLOAD_TCS;

	अगर (num_tc == net_dev->num_tc)
		वापस 0;

	क्रम (tc = 0; tc < num_tc; tc++) अणु
		net_dev->tc_to_txq[tc].offset = tc * efx->n_tx_channels;
		net_dev->tc_to_txq[tc].count = efx->n_tx_channels;
	पूर्ण

	अगर (num_tc > net_dev->num_tc) अणु
		/* Initialise high-priority queues as necessary */
		ef4_क्रम_each_channel(channel, efx) अणु
			ef4_क्रम_each_possible_channel_tx_queue(tx_queue,
							       channel) अणु
				अगर (!(tx_queue->queue & EF4_TXQ_TYPE_HIGHPRI))
					जारी;
				अगर (!tx_queue->buffer) अणु
					rc = ef4_probe_tx_queue(tx_queue);
					अगर (rc)
						वापस rc;
				पूर्ण
				अगर (!tx_queue->initialised)
					ef4_init_tx_queue(tx_queue);
				ef4_init_tx_queue_core_txq(tx_queue);
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Reduce number of classes beक्रमe number of queues */
		net_dev->num_tc = num_tc;
	पूर्ण

	rc = netअगर_set_real_num_tx_queues(net_dev,
					  max_t(पूर्णांक, num_tc, 1) *
					  efx->n_tx_channels);
	अगर (rc)
		वापस rc;

	/* Do not destroy high-priority queues when they become
	 * unused.  We would have to flush them first, and it is
	 * fairly dअगरficult to flush a subset of TX queues.  Leave
	 * it to ef4_fini_channels().
	 */

	net_dev->num_tc = num_tc;
	वापस 0;
पूर्ण

व्योम ef4_xmit_करोne(काष्ठा ef4_tx_queue *tx_queue, अचिन्हित पूर्णांक index)
अणु
	अचिन्हित fill_level;
	काष्ठा ef4_nic *efx = tx_queue->efx;
	काष्ठा ef4_tx_queue *txq2;
	अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;

	EF4_BUG_ON_PARANOID(index > tx_queue->ptr_mask);

	ef4_dequeue_buffers(tx_queue, index, &pkts_compl, &bytes_compl);
	tx_queue->pkts_compl += pkts_compl;
	tx_queue->bytes_compl += bytes_compl;

	अगर (pkts_compl > 1)
		++tx_queue->merge_events;

	/* See अगर we need to restart the netअगर queue.  This memory
	 * barrier ensures that we ग_लिखो पढ़ो_count (inside
	 * ef4_dequeue_buffers()) beक्रमe पढ़ोing the queue status.
	 */
	smp_mb();
	अगर (unlikely(netअगर_tx_queue_stopped(tx_queue->core_txq)) &&
	    likely(efx->port_enabled) &&
	    likely(netअगर_device_present(efx->net_dev))) अणु
		txq2 = ef4_tx_queue_partner(tx_queue);
		fill_level = max(tx_queue->insert_count - tx_queue->पढ़ो_count,
				 txq2->insert_count - txq2->पढ़ो_count);
		अगर (fill_level <= efx->txq_wake_thresh)
			netअगर_tx_wake_queue(tx_queue->core_txq);
	पूर्ण

	/* Check whether the hardware queue is now empty */
	अगर ((पूर्णांक)(tx_queue->पढ़ो_count - tx_queue->old_ग_लिखो_count) >= 0) अणु
		tx_queue->old_ग_लिखो_count = READ_ONCE(tx_queue->ग_लिखो_count);
		अगर (tx_queue->पढ़ो_count == tx_queue->old_ग_लिखो_count) अणु
			smp_mb();
			tx_queue->empty_पढ़ो_count =
				tx_queue->पढ़ो_count | EF4_EMPTY_COUNT_VALID;
		पूर्ण
	पूर्ण
पूर्ण

अटल अचिन्हित पूर्णांक ef4_tx_cb_page_count(काष्ठा ef4_tx_queue *tx_queue)
अणु
	वापस DIV_ROUND_UP(tx_queue->ptr_mask + 1, PAGE_SIZE >> EF4_TX_CB_ORDER);
पूर्ण

पूर्णांक ef4_probe_tx_queue(काष्ठा ef4_tx_queue *tx_queue)
अणु
	काष्ठा ef4_nic *efx = tx_queue->efx;
	अचिन्हित पूर्णांक entries;
	पूर्णांक rc;

	/* Create the smallest घातer-of-two aligned ring */
	entries = max(roundup_घात_of_two(efx->txq_entries), EF4_MIN_DMAQ_SIZE);
	EF4_BUG_ON_PARANOID(entries > EF4_MAX_DMAQ_SIZE);
	tx_queue->ptr_mask = entries - 1;

	netअगर_dbg(efx, probe, efx->net_dev,
		  "creating TX queue %d size %#x mask %#x\n",
		  tx_queue->queue, efx->txq_entries, tx_queue->ptr_mask);

	/* Allocate software ring */
	tx_queue->buffer = kसुस्मृति(entries, माप(*tx_queue->buffer),
				   GFP_KERNEL);
	अगर (!tx_queue->buffer)
		वापस -ENOMEM;

	tx_queue->cb_page = kसुस्मृति(ef4_tx_cb_page_count(tx_queue),
				    माप(tx_queue->cb_page[0]), GFP_KERNEL);
	अगर (!tx_queue->cb_page) अणु
		rc = -ENOMEM;
		जाओ fail1;
	पूर्ण

	/* Allocate hardware ring */
	rc = ef4_nic_probe_tx(tx_queue);
	अगर (rc)
		जाओ fail2;

	वापस 0;

fail2:
	kमुक्त(tx_queue->cb_page);
	tx_queue->cb_page = शून्य;
fail1:
	kमुक्त(tx_queue->buffer);
	tx_queue->buffer = शून्य;
	वापस rc;
पूर्ण

व्योम ef4_init_tx_queue(काष्ठा ef4_tx_queue *tx_queue)
अणु
	काष्ठा ef4_nic *efx = tx_queue->efx;

	netअगर_dbg(efx, drv, efx->net_dev,
		  "initialising TX queue %d\n", tx_queue->queue);

	tx_queue->insert_count = 0;
	tx_queue->ग_लिखो_count = 0;
	tx_queue->old_ग_लिखो_count = 0;
	tx_queue->पढ़ो_count = 0;
	tx_queue->old_पढ़ो_count = 0;
	tx_queue->empty_पढ़ो_count = 0 | EF4_EMPTY_COUNT_VALID;
	tx_queue->xmit_more_available = false;

	/* Some older hardware requires Tx ग_लिखोs larger than 32. */
	tx_queue->tx_min_size = EF4_WORKAROUND_15592(efx) ? 33 : 0;

	/* Set up TX descriptor ring */
	ef4_nic_init_tx(tx_queue);

	tx_queue->initialised = true;
पूर्ण

व्योम ef4_fini_tx_queue(काष्ठा ef4_tx_queue *tx_queue)
अणु
	काष्ठा ef4_tx_buffer *buffer;

	netअगर_dbg(tx_queue->efx, drv, tx_queue->efx->net_dev,
		  "shutting down TX queue %d\n", tx_queue->queue);

	अगर (!tx_queue->buffer)
		वापस;

	/* Free any buffers left in the ring */
	जबतक (tx_queue->पढ़ो_count != tx_queue->ग_लिखो_count) अणु
		अचिन्हित पूर्णांक pkts_compl = 0, bytes_compl = 0;
		buffer = &tx_queue->buffer[tx_queue->पढ़ो_count & tx_queue->ptr_mask];
		ef4_dequeue_buffer(tx_queue, buffer, &pkts_compl, &bytes_compl);

		++tx_queue->पढ़ो_count;
	पूर्ण
	tx_queue->xmit_more_available = false;
	netdev_tx_reset_queue(tx_queue->core_txq);
पूर्ण

व्योम ef4_हटाओ_tx_queue(काष्ठा ef4_tx_queue *tx_queue)
अणु
	पूर्णांक i;

	अगर (!tx_queue->buffer)
		वापस;

	netअगर_dbg(tx_queue->efx, drv, tx_queue->efx->net_dev,
		  "destroying TX queue %d\n", tx_queue->queue);
	ef4_nic_हटाओ_tx(tx_queue);

	अगर (tx_queue->cb_page) अणु
		क्रम (i = 0; i < ef4_tx_cb_page_count(tx_queue); i++)
			ef4_nic_मुक्त_buffer(tx_queue->efx,
					    &tx_queue->cb_page[i]);
		kमुक्त(tx_queue->cb_page);
		tx_queue->cb_page = शून्य;
	पूर्ण

	kमुक्त(tx_queue->buffer);
	tx_queue->buffer = शून्य;
पूर्ण
