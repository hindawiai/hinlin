<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/****************************************************************************
 * Driver क्रम Solarflare network controllers and boards
 * Copyright 2005-2006 Fen Systems Ltd.
 * Copyright 2005-2015 Solarflare Communications Inc.
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
#समावेश <linux/moduleparam.h>
#समावेश <linux/cache.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "io.h"
#समावेश "nic.h"
#समावेश "tx.h"
#समावेश "workarounds.h"
#समावेश "ef10_regs.h"

/* Efx legacy TCP segmentation acceleration.
 *
 * Utilises firmware support to go faster than GSO (but not as fast as TSOv2).
 *
 * Requires TX checksum offload support.
 */

#घोषणा PTR_DIFF(p1, p2)  ((u8 *)(p1) - (u8 *)(p2))

/**
 * काष्ठा tso_state - TSO state क्रम an SKB
 * @out_len: Reमुख्यing length in current segment
 * @seqnum: Current sequence number
 * @ipv4_id: Current IPv4 ID, host endian
 * @packet_space: Reमुख्यing space in current packet
 * @dma_addr: DMA address of current position
 * @in_len: Reमुख्यing length in current SKB fragment
 * @unmap_len: Length of SKB fragment
 * @unmap_addr: DMA address of SKB fragment
 * @protocol: Network protocol (after any VLAN header)
 * @ip_off: Offset of IP header
 * @tcp_off: Offset of TCP header
 * @header_len: Number of bytes of header
 * @ip_base_len: IPv4 tot_len or IPv6 payload_len, beक्रमe TCP payload
 * @header_dma_addr: Header DMA address
 * @header_unmap_len: Header DMA mapped length
 *
 * The state used during segmentation.  It is put पूर्णांकo this data काष्ठाure
 * just to make it easy to pass पूर्णांकo अंतरभूत functions.
 */
काष्ठा tso_state अणु
	/* Output position */
	अचिन्हित पूर्णांक out_len;
	अचिन्हित पूर्णांक seqnum;
	u16 ipv4_id;
	अचिन्हित पूर्णांक packet_space;

	/* Input position */
	dma_addr_t dma_addr;
	अचिन्हित पूर्णांक in_len;
	अचिन्हित पूर्णांक unmap_len;
	dma_addr_t unmap_addr;

	__be16 protocol;
	अचिन्हित पूर्णांक ip_off;
	अचिन्हित पूर्णांक tcp_off;
	अचिन्हित पूर्णांक header_len;
	अचिन्हित पूर्णांक ip_base_len;
	dma_addr_t header_dma_addr;
	अचिन्हित पूर्णांक header_unmap_len;
पूर्ण;

अटल अंतरभूत व्योम prefetch_ptr(काष्ठा efx_tx_queue *tx_queue)
अणु
	अचिन्हित पूर्णांक insert_ptr = efx_tx_queue_get_insert_index(tx_queue);
	अक्षर *ptr;

	ptr = (अक्षर *) (tx_queue->buffer + insert_ptr);
	prefetch(ptr);
	prefetch(ptr + 0x80);

	ptr = (अक्षर *) (((efx_qword_t *)tx_queue->txd.buf.addr) + insert_ptr);
	prefetch(ptr);
	prefetch(ptr + 0x80);
पूर्ण

/**
 * efx_tx_queue_insert - push descriptors onto the TX queue
 * @tx_queue:		Efx TX queue
 * @dma_addr:		DMA address of fragment
 * @len:		Length of fragment
 * @final_buffer:	The final buffer inserted पूर्णांकo the queue
 *
 * Push descriptors onto the TX queue.
 */
अटल व्योम efx_tx_queue_insert(काष्ठा efx_tx_queue *tx_queue,
				dma_addr_t dma_addr, अचिन्हित पूर्णांक len,
				काष्ठा efx_tx_buffer **final_buffer)
अणु
	काष्ठा efx_tx_buffer *buffer;
	अचिन्हित पूर्णांक dma_len;

	EFX_WARN_ON_ONCE_PARANOID(len <= 0);

	जबतक (1) अणु
		buffer = efx_tx_queue_get_insert_buffer(tx_queue);
		++tx_queue->insert_count;

		EFX_WARN_ON_ONCE_PARANOID(tx_queue->insert_count -
					  tx_queue->पढ़ो_count >=
					  tx_queue->efx->txq_entries);

		buffer->dma_addr = dma_addr;

		dma_len = tx_queue->efx->type->tx_limit_len(tx_queue,
				dma_addr, len);

		/* If there's space क्रम everything this is our last buffer. */
		अगर (dma_len >= len)
			अवरोध;

		buffer->len = dma_len;
		buffer->flags = EFX_TX_BUF_CONT;
		dma_addr += dma_len;
		len -= dma_len;
	पूर्ण

	EFX_WARN_ON_ONCE_PARANOID(!len);
	buffer->len = len;
	*final_buffer = buffer;
पूर्ण

/*
 * Verअगरy that our various assumptions about sk_buffs and the conditions
 * under which TSO will be attempted hold true.  Return the protocol number.
 */
अटल __be16 efx_tso_check_protocol(काष्ठा sk_buff *skb)
अणु
	__be16 protocol = skb->protocol;

	EFX_WARN_ON_ONCE_PARANOID(((काष्ठा ethhdr *)skb->data)->h_proto !=
				  protocol);
	अगर (protocol == htons(ETH_P_8021Q)) अणु
		काष्ठा vlan_ethhdr *veh = (काष्ठा vlan_ethhdr *)skb->data;

		protocol = veh->h_vlan_encapsulated_proto;
	पूर्ण

	अगर (protocol == htons(ETH_P_IP)) अणु
		EFX_WARN_ON_ONCE_PARANOID(ip_hdr(skb)->protocol != IPPROTO_TCP);
	पूर्ण अन्यथा अणु
		EFX_WARN_ON_ONCE_PARANOID(protocol != htons(ETH_P_IPV6));
		EFX_WARN_ON_ONCE_PARANOID(ipv6_hdr(skb)->nexthdr != NEXTHDR_TCP);
	पूर्ण
	EFX_WARN_ON_ONCE_PARANOID((PTR_DIFF(tcp_hdr(skb), skb->data) +
				   (tcp_hdr(skb)->करोff << 2u)) >
				  skb_headlen(skb));

	वापस protocol;
पूर्ण

/* Parse the SKB header and initialise state. */
अटल पूर्णांक tso_start(काष्ठा tso_state *st, काष्ठा efx_nic *efx,
		     काष्ठा efx_tx_queue *tx_queue,
		     स्थिर काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dma_dev = &efx->pci_dev->dev;
	अचिन्हित पूर्णांक header_len, in_len;
	dma_addr_t dma_addr;

	st->ip_off = skb_network_header(skb) - skb->data;
	st->tcp_off = skb_transport_header(skb) - skb->data;
	header_len = st->tcp_off + (tcp_hdr(skb)->करोff << 2u);
	in_len = skb_headlen(skb) - header_len;
	st->header_len = header_len;
	st->in_len = in_len;
	अगर (st->protocol == htons(ETH_P_IP)) अणु
		st->ip_base_len = st->header_len - st->ip_off;
		st->ipv4_id = ntohs(ip_hdr(skb)->id);
	पूर्ण अन्यथा अणु
		st->ip_base_len = st->header_len - st->tcp_off;
		st->ipv4_id = 0;
	पूर्ण
	st->seqnum = ntohl(tcp_hdr(skb)->seq);

	EFX_WARN_ON_ONCE_PARANOID(tcp_hdr(skb)->urg);
	EFX_WARN_ON_ONCE_PARANOID(tcp_hdr(skb)->syn);
	EFX_WARN_ON_ONCE_PARANOID(tcp_hdr(skb)->rst);

	st->out_len = skb->len - header_len;

	dma_addr = dma_map_single(dma_dev, skb->data,
				  skb_headlen(skb), DMA_TO_DEVICE);
	st->header_dma_addr = dma_addr;
	st->header_unmap_len = skb_headlen(skb);
	st->dma_addr = dma_addr + header_len;
	st->unmap_len = 0;

	वापस unlikely(dma_mapping_error(dma_dev, dma_addr)) ? -ENOMEM : 0;
पूर्ण

अटल पूर्णांक tso_get_fragment(काष्ठा tso_state *st, काष्ठा efx_nic *efx,
			    skb_frag_t *frag)
अणु
	st->unmap_addr = skb_frag_dma_map(&efx->pci_dev->dev, frag, 0,
					  skb_frag_size(frag), DMA_TO_DEVICE);
	अगर (likely(!dma_mapping_error(&efx->pci_dev->dev, st->unmap_addr))) अणु
		st->unmap_len = skb_frag_size(frag);
		st->in_len = skb_frag_size(frag);
		st->dma_addr = st->unmap_addr;
		वापस 0;
	पूर्ण
	वापस -ENOMEM;
पूर्ण


/**
 * tso_fill_packet_with_fragment - क्रमm descriptors क्रम the current fragment
 * @tx_queue:		Efx TX queue
 * @skb:		Socket buffer
 * @st:			TSO state
 *
 * Form descriptors क्रम the current fragment, until we reach the end
 * of fragment or end-of-packet.
 */
अटल व्योम tso_fill_packet_with_fragment(काष्ठा efx_tx_queue *tx_queue,
					  स्थिर काष्ठा sk_buff *skb,
					  काष्ठा tso_state *st)
अणु
	काष्ठा efx_tx_buffer *buffer;
	पूर्णांक n;

	अगर (st->in_len == 0)
		वापस;
	अगर (st->packet_space == 0)
		वापस;

	EFX_WARN_ON_ONCE_PARANOID(st->in_len <= 0);
	EFX_WARN_ON_ONCE_PARANOID(st->packet_space <= 0);

	n = min(st->in_len, st->packet_space);

	st->packet_space -= n;
	st->out_len -= n;
	st->in_len -= n;

	efx_tx_queue_insert(tx_queue, st->dma_addr, n, &buffer);

	अगर (st->out_len == 0) अणु
		/* Transfer ownership of the skb */
		buffer->skb = skb;
		buffer->flags = EFX_TX_BUF_SKB;
	पूर्ण अन्यथा अगर (st->packet_space != 0) अणु
		buffer->flags = EFX_TX_BUF_CONT;
	पूर्ण

	अगर (st->in_len == 0) अणु
		/* Transfer ownership of the DMA mapping */
		buffer->unmap_len = st->unmap_len;
		buffer->dma_offset = buffer->unmap_len - buffer->len;
		st->unmap_len = 0;
	पूर्ण

	st->dma_addr += n;
पूर्ण


#घोषणा TCP_FLAGS_OFFSET 13

/**
 * tso_start_new_packet - generate a new header and prepare क्रम the new packet
 * @tx_queue:		Efx TX queue
 * @skb:		Socket buffer
 * @st:			TSO state
 *
 * Generate a new header and prepare क्रम the new packet.  Return 0 on
 * success, or -%ENOMEM अगर failed to alloc header, or other negative error.
 */
अटल पूर्णांक tso_start_new_packet(काष्ठा efx_tx_queue *tx_queue,
				स्थिर काष्ठा sk_buff *skb,
				काष्ठा tso_state *st)
अणु
	काष्ठा efx_tx_buffer *buffer =
		efx_tx_queue_get_insert_buffer(tx_queue);
	bool is_last = st->out_len <= skb_shinfo(skb)->gso_size;
	u8 tcp_flags_mask, tcp_flags;

	अगर (!is_last) अणु
		st->packet_space = skb_shinfo(skb)->gso_size;
		tcp_flags_mask = 0x09; /* mask out FIN and PSH */
	पूर्ण अन्यथा अणु
		st->packet_space = st->out_len;
		tcp_flags_mask = 0x00;
	पूर्ण

	अगर (WARN_ON(!st->header_unmap_len))
		वापस -EINVAL;
	/* Send the original headers with a TSO option descriptor
	 * in front
	 */
	tcp_flags = ((u8 *)tcp_hdr(skb))[TCP_FLAGS_OFFSET] & ~tcp_flags_mask;

	buffer->flags = EFX_TX_BUF_OPTION;
	buffer->len = 0;
	buffer->unmap_len = 0;
	EFX_POPULATE_QWORD_5(buffer->option,
			     ESF_DZ_TX_DESC_IS_OPT, 1,
			     ESF_DZ_TX_OPTION_TYPE,
			     ESE_DZ_TX_OPTION_DESC_TSO,
			     ESF_DZ_TX_TSO_TCP_FLAGS, tcp_flags,
			     ESF_DZ_TX_TSO_IP_ID, st->ipv4_id,
			     ESF_DZ_TX_TSO_TCP_SEQNO, st->seqnum);
	++tx_queue->insert_count;

	/* We mapped the headers in tso_start().  Unmap them
	 * when the last segment is completed.
	 */
	buffer = efx_tx_queue_get_insert_buffer(tx_queue);
	buffer->dma_addr = st->header_dma_addr;
	buffer->len = st->header_len;
	अगर (is_last) अणु
		buffer->flags = EFX_TX_BUF_CONT | EFX_TX_BUF_MAP_SINGLE;
		buffer->unmap_len = st->header_unmap_len;
		buffer->dma_offset = 0;
		/* Ensure we only unmap them once in हाल of a
		 * later DMA mapping error and rollback
		 */
		st->header_unmap_len = 0;
	पूर्ण अन्यथा अणु
		buffer->flags = EFX_TX_BUF_CONT;
		buffer->unmap_len = 0;
	पूर्ण
	++tx_queue->insert_count;

	st->seqnum += skb_shinfo(skb)->gso_size;

	/* Linux leaves suitable gaps in the IP ID space क्रम us to fill. */
	++st->ipv4_id;

	वापस 0;
पूर्ण

/**
 * efx_enqueue_skb_tso - segment and transmit a TSO socket buffer
 * @tx_queue:		Efx TX queue
 * @skb:		Socket buffer
 * @data_mapped:        Did we map the data? Always set to true
 *                      by this on success.
 *
 * Context: You must hold netअगर_tx_lock() to call this function.
 *
 * Add socket buffer @skb to @tx_queue, करोing TSO or वापस != 0 अगर
 * @skb was not enqueued.  @skb is consumed unless वापस value is
 * %EINVAL.
 */
पूर्णांक efx_enqueue_skb_tso(काष्ठा efx_tx_queue *tx_queue,
			काष्ठा sk_buff *skb,
			bool *data_mapped)
अणु
	काष्ठा efx_nic *efx = tx_queue->efx;
	पूर्णांक frag_i, rc;
	काष्ठा tso_state state;

	अगर (tx_queue->tso_version != 1)
		वापस -EINVAL;

	prefetch(skb->data);

	/* Find the packet protocol and sanity-check it */
	state.protocol = efx_tso_check_protocol(skb);

	EFX_WARN_ON_ONCE_PARANOID(tx_queue->ग_लिखो_count != tx_queue->insert_count);

	rc = tso_start(&state, efx, tx_queue, skb);
	अगर (rc)
		जाओ fail;

	अगर (likely(state.in_len == 0)) अणु
		/* Grab the first payload fragment. */
		EFX_WARN_ON_ONCE_PARANOID(skb_shinfo(skb)->nr_frags < 1);
		frag_i = 0;
		rc = tso_get_fragment(&state, efx,
				      skb_shinfo(skb)->frags + frag_i);
		अगर (rc)
			जाओ fail;
	पूर्ण अन्यथा अणु
		/* Payload starts in the header area. */
		frag_i = -1;
	पूर्ण

	rc = tso_start_new_packet(tx_queue, skb, &state);
	अगर (rc)
		जाओ fail;

	prefetch_ptr(tx_queue);

	जबतक (1) अणु
		tso_fill_packet_with_fragment(tx_queue, skb, &state);

		/* Move onto the next fragment? */
		अगर (state.in_len == 0) अणु
			अगर (++frag_i >= skb_shinfo(skb)->nr_frags)
				/* End of payload reached. */
				अवरोध;
			rc = tso_get_fragment(&state, efx,
					      skb_shinfo(skb)->frags + frag_i);
			अगर (rc)
				जाओ fail;
		पूर्ण

		/* Start at new packet? */
		अगर (state.packet_space == 0) अणु
			rc = tso_start_new_packet(tx_queue, skb, &state);
			अगर (rc)
				जाओ fail;
		पूर्ण
	पूर्ण

	*data_mapped = true;

	वापस 0;

fail:
	अगर (rc == -ENOMEM)
		netअगर_err(efx, tx_err, efx->net_dev,
			  "Out of memory for TSO headers, or DMA mapping error\n");
	अन्यथा
		netअगर_err(efx, tx_err, efx->net_dev, "TSO failed, rc = %d\n", rc);

	/* Free the DMA mapping we were in the process of writing out */
	अगर (state.unmap_len) अणु
		dma_unmap_page(&efx->pci_dev->dev, state.unmap_addr,
			       state.unmap_len, DMA_TO_DEVICE);
	पूर्ण

	/* Free the header DMA mapping */
	अगर (state.header_unmap_len)
		dma_unmap_single(&efx->pci_dev->dev, state.header_dma_addr,
				 state.header_unmap_len, DMA_TO_DEVICE);

	वापस rc;
पूर्ण
