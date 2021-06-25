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
#समावेश <net/xdp.h>
#समावेश <linux/bpf_trace.h>
#समावेश "net_driver.h"
#समावेश "efx.h"
#समावेश "rx_common.h"
#समावेश "filter.h"
#समावेश "nic.h"
#समावेश "selftest.h"
#समावेश "workarounds.h"

/* Preferred number of descriptors to fill at once */
#घोषणा EFX_RX_PREFERRED_BATCH 8U

/* Maximum rx prefix used by any architecture. */
#घोषणा EFX_MAX_RX_PREFIX_SIZE 16

/* Size of buffer allocated क्रम skb header area. */
#घोषणा EFX_SKB_HEADERS  128u

/* Each packet can consume up to उच्चमान(max_frame_len / buffer_size) buffers */
#घोषणा EFX_RX_MAX_FRAGS DIV_ROUND_UP(EFX_MAX_FRAME_LEN(EFX_MAX_MTU), \
				      EFX_RX_USR_BUF_SIZE)

अटल व्योम efx_rx_packet__check_len(काष्ठा efx_rx_queue *rx_queue,
				     काष्ठा efx_rx_buffer *rx_buf,
				     पूर्णांक len)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	अचिन्हित max_len = rx_buf->len - efx->type->rx_buffer_padding;

	अगर (likely(len <= max_len))
		वापस;

	/* The packet must be discarded, but this is only a fatal error
	 * अगर the caller indicated it was
	 */
	rx_buf->flags |= EFX_RX_PKT_DISCARD;

	अगर (net_ratelimit())
		netअगर_err(efx, rx_err, efx->net_dev,
			  "RX queue %d overlength RX event (%#x > %#x)\n",
			  efx_rx_queue_index(rx_queue), len, max_len);

	efx_rx_queue_channel(rx_queue)->n_rx_overlength++;
पूर्ण

/* Allocate and स्थिरruct an SKB around page fragments */
अटल काष्ठा sk_buff *efx_rx_mk_skb(काष्ठा efx_channel *channel,
				     काष्ठा efx_rx_buffer *rx_buf,
				     अचिन्हित पूर्णांक n_frags,
				     u8 *eh, पूर्णांक hdr_len)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा sk_buff *skb;

	/* Allocate an SKB to store the headers */
	skb = netdev_alloc_skb(efx->net_dev,
			       efx->rx_ip_align + efx->rx_prefix_size +
			       hdr_len);
	अगर (unlikely(skb == शून्य)) अणु
		atomic_inc(&efx->n_rx_noskb_drops);
		वापस शून्य;
	पूर्ण

	EFX_WARN_ON_ONCE_PARANOID(rx_buf->len < hdr_len);

	स_नकल(skb->data + efx->rx_ip_align, eh - efx->rx_prefix_size,
	       efx->rx_prefix_size + hdr_len);
	skb_reserve(skb, efx->rx_ip_align + efx->rx_prefix_size);
	__skb_put(skb, hdr_len);

	/* Append the reमुख्यing page(s) onto the frag list */
	अगर (rx_buf->len > hdr_len) अणु
		rx_buf->page_offset += hdr_len;
		rx_buf->len -= hdr_len;

		क्रम (;;) अणु
			skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags,
					rx_buf->page, rx_buf->page_offset,
					rx_buf->len, efx->rx_buffer_truesize);
			rx_buf->page = शून्य;

			अगर (skb_shinfo(skb)->nr_frags == n_frags)
				अवरोध;

			rx_buf = efx_rx_buf_next(&channel->rx_queue, rx_buf);
		पूर्ण
	पूर्ण अन्यथा अणु
		__मुक्त_pages(rx_buf->page, efx->rx_buffer_order);
		rx_buf->page = शून्य;
		n_frags = 0;
	पूर्ण

	/* Move past the ethernet header */
	skb->protocol = eth_type_trans(skb, efx->net_dev);

	skb_mark_napi_id(skb, &channel->napi_str);

	वापस skb;
पूर्ण

व्योम efx_rx_packet(काष्ठा efx_rx_queue *rx_queue, अचिन्हित पूर्णांक index,
		   अचिन्हित पूर्णांक n_frags, अचिन्हित पूर्णांक len, u16 flags)
अणु
	काष्ठा efx_nic *efx = rx_queue->efx;
	काष्ठा efx_channel *channel = efx_rx_queue_channel(rx_queue);
	काष्ठा efx_rx_buffer *rx_buf;

	rx_queue->rx_packets++;

	rx_buf = efx_rx_buffer(rx_queue, index);
	rx_buf->flags |= flags;

	/* Validate the number of fragments and completed length */
	अगर (n_frags == 1) अणु
		अगर (!(flags & EFX_RX_PKT_PREFIX_LEN))
			efx_rx_packet__check_len(rx_queue, rx_buf, len);
	पूर्ण अन्यथा अगर (unlikely(n_frags > EFX_RX_MAX_FRAGS) ||
		   unlikely(len <= (n_frags - 1) * efx->rx_dma_len) ||
		   unlikely(len > n_frags * efx->rx_dma_len) ||
		   unlikely(!efx->rx_scatter)) अणु
		/* If this isn't an explicit discard request, either
		 * the hardware or the driver is broken.
		 */
		WARN_ON(!(len == 0 && rx_buf->flags & EFX_RX_PKT_DISCARD));
		rx_buf->flags |= EFX_RX_PKT_DISCARD;
	पूर्ण

	netअगर_vdbg(efx, rx_status, efx->net_dev,
		   "RX queue %d received ids %x-%x len %d %s%s\n",
		   efx_rx_queue_index(rx_queue), index,
		   (index + n_frags - 1) & rx_queue->ptr_mask, len,
		   (rx_buf->flags & EFX_RX_PKT_CSUMMED) ? " [SUMMED]" : "",
		   (rx_buf->flags & EFX_RX_PKT_DISCARD) ? " [DISCARD]" : "");

	/* Discard packet, अगर inकाष्ठाed to करो so.  Process the
	 * previous receive first.
	 */
	अगर (unlikely(rx_buf->flags & EFX_RX_PKT_DISCARD)) अणु
		efx_rx_flush_packet(channel);
		efx_discard_rx_packet(channel, rx_buf, n_frags);
		वापस;
	पूर्ण

	अगर (n_frags == 1 && !(flags & EFX_RX_PKT_PREFIX_LEN))
		rx_buf->len = len;

	/* Release and/or sync the DMA mapping - assumes all RX buffers
	 * consumed in-order per RX queue.
	 */
	efx_sync_rx_buffer(efx, rx_buf, rx_buf->len);

	/* Prefetch nice and early so data will (hopefully) be in cache by
	 * the समय we look at it.
	 */
	prefetch(efx_rx_buf_va(rx_buf));

	rx_buf->page_offset += efx->rx_prefix_size;
	rx_buf->len -= efx->rx_prefix_size;

	अगर (n_frags > 1) अणु
		/* Release/sync DMA mapping क्रम additional fragments.
		 * Fix length क्रम last fragment.
		 */
		अचिन्हित पूर्णांक tail_frags = n_frags - 1;

		क्रम (;;) अणु
			rx_buf = efx_rx_buf_next(rx_queue, rx_buf);
			अगर (--tail_frags == 0)
				अवरोध;
			efx_sync_rx_buffer(efx, rx_buf, efx->rx_dma_len);
		पूर्ण
		rx_buf->len = len - (n_frags - 1) * efx->rx_dma_len;
		efx_sync_rx_buffer(efx, rx_buf, rx_buf->len);
	पूर्ण

	/* All fragments have been DMA-synced, so recycle pages. */
	rx_buf = efx_rx_buffer(rx_queue, index);
	efx_recycle_rx_pages(channel, rx_buf, n_frags);

	/* Pipeline receives so that we give समय क्रम packet headers to be
	 * prefetched पूर्णांकo cache.
	 */
	efx_rx_flush_packet(channel);
	channel->rx_pkt_n_frags = n_frags;
	channel->rx_pkt_index = index;
पूर्ण

अटल व्योम efx_rx_deliver(काष्ठा efx_channel *channel, u8 *eh,
			   काष्ठा efx_rx_buffer *rx_buf,
			   अचिन्हित पूर्णांक n_frags)
अणु
	काष्ठा sk_buff *skb;
	u16 hdr_len = min_t(u16, rx_buf->len, EFX_SKB_HEADERS);

	skb = efx_rx_mk_skb(channel, rx_buf, n_frags, eh, hdr_len);
	अगर (unlikely(skb == शून्य)) अणु
		काष्ठा efx_rx_queue *rx_queue;

		rx_queue = efx_channel_get_rx_queue(channel);
		efx_मुक्त_rx_buffers(rx_queue, rx_buf, n_frags);
		वापस;
	पूर्ण
	skb_record_rx_queue(skb, channel->rx_queue.core_index);

	/* Set the SKB flags */
	skb_checksum_none_निश्चित(skb);
	अगर (likely(rx_buf->flags & EFX_RX_PKT_CSUMMED)) अणु
		skb->ip_summed = CHECKSUM_UNNECESSARY;
		skb->csum_level = !!(rx_buf->flags & EFX_RX_PKT_CSUM_LEVEL);
	पूर्ण

	efx_rx_skb_attach_बारtamp(channel, skb);

	अगर (channel->type->receive_skb)
		अगर (channel->type->receive_skb(channel, skb))
			वापस;

	/* Pass the packet up */
	अगर (channel->rx_list != शून्य)
		/* Add to list, will pass up later */
		list_add_tail(&skb->list, channel->rx_list);
	अन्यथा
		/* No list, so pass it up now */
		netअगर_receive_skb(skb);
पूर्ण

/** efx_करो_xdp: perक्रमm XDP processing on a received packet
 *
 * Returns true अगर packet should still be delivered.
 */
अटल bool efx_करो_xdp(काष्ठा efx_nic *efx, काष्ठा efx_channel *channel,
		       काष्ठा efx_rx_buffer *rx_buf, u8 **ehp)
अणु
	u8 rx_prefix[EFX_MAX_RX_PREFIX_SIZE];
	काष्ठा efx_rx_queue *rx_queue;
	काष्ठा bpf_prog *xdp_prog;
	काष्ठा xdp_frame *xdpf;
	काष्ठा xdp_buff xdp;
	u32 xdp_act;
	s16 offset;
	पूर्णांक err;

	rcu_पढ़ो_lock();
	xdp_prog = rcu_dereference(efx->xdp_prog);
	अगर (!xdp_prog) अणु
		rcu_पढ़ो_unlock();
		वापस true;
	पूर्ण

	rx_queue = efx_channel_get_rx_queue(channel);

	अगर (unlikely(channel->rx_pkt_n_frags > 1)) अणु
		/* We can't करो XDP on fragmented packets - drop. */
		rcu_पढ़ो_unlock();
		efx_मुक्त_rx_buffers(rx_queue, rx_buf,
				    channel->rx_pkt_n_frags);
		अगर (net_ratelimit())
			netअगर_err(efx, rx_err, efx->net_dev,
				  "XDP is not possible with multiple receive fragments (%d)\n",
				  channel->rx_pkt_n_frags);
		channel->n_rx_xdp_bad_drops++;
		वापस false;
	पूर्ण

	dma_sync_single_क्रम_cpu(&efx->pci_dev->dev, rx_buf->dma_addr,
				rx_buf->len, DMA_FROM_DEVICE);

	/* Save the rx prefix. */
	EFX_WARN_ON_PARANOID(efx->rx_prefix_size > EFX_MAX_RX_PREFIX_SIZE);
	स_नकल(rx_prefix, *ehp - efx->rx_prefix_size,
	       efx->rx_prefix_size);

	xdp_init_buff(&xdp, efx->rx_page_buf_step, &rx_queue->xdp_rxq_info);
	/* No support yet क्रम XDP metadata */
	xdp_prepare_buff(&xdp, *ehp - EFX_XDP_HEADROOM, EFX_XDP_HEADROOM,
			 rx_buf->len, false);

	xdp_act = bpf_prog_run_xdp(xdp_prog, &xdp);
	rcu_पढ़ो_unlock();

	offset = (u8 *)xdp.data - *ehp;

	चयन (xdp_act) अणु
	हाल XDP_PASS:
		/* Fix up rx prefix. */
		अगर (offset) अणु
			*ehp += offset;
			rx_buf->page_offset += offset;
			rx_buf->len -= offset;
			स_नकल(*ehp - efx->rx_prefix_size, rx_prefix,
			       efx->rx_prefix_size);
		पूर्ण
		अवरोध;

	हाल XDP_TX:
		/* Buffer ownership passes to tx on success. */
		xdpf = xdp_convert_buff_to_frame(&xdp);
		err = efx_xdp_tx_buffers(efx, 1, &xdpf, true);
		अगर (unlikely(err != 1)) अणु
			efx_मुक्त_rx_buffers(rx_queue, rx_buf, 1);
			अगर (net_ratelimit())
				netअगर_err(efx, rx_err, efx->net_dev,
					  "XDP TX failed (%d)\n", err);
			channel->n_rx_xdp_bad_drops++;
			trace_xdp_exception(efx->net_dev, xdp_prog, xdp_act);
		पूर्ण अन्यथा अणु
			channel->n_rx_xdp_tx++;
		पूर्ण
		अवरोध;

	हाल XDP_REसूचीECT:
		err = xdp_करो_redirect(efx->net_dev, &xdp, xdp_prog);
		अगर (unlikely(err)) अणु
			efx_मुक्त_rx_buffers(rx_queue, rx_buf, 1);
			अगर (net_ratelimit())
				netअगर_err(efx, rx_err, efx->net_dev,
					  "XDP redirect failed (%d)\n", err);
			channel->n_rx_xdp_bad_drops++;
			trace_xdp_exception(efx->net_dev, xdp_prog, xdp_act);
		पूर्ण अन्यथा अणु
			channel->n_rx_xdp_redirect++;
		पूर्ण
		अवरोध;

	शेष:
		bpf_warn_invalid_xdp_action(xdp_act);
		efx_मुक्त_rx_buffers(rx_queue, rx_buf, 1);
		channel->n_rx_xdp_bad_drops++;
		trace_xdp_exception(efx->net_dev, xdp_prog, xdp_act);
		अवरोध;

	हाल XDP_ABORTED:
		trace_xdp_exception(efx->net_dev, xdp_prog, xdp_act);
		fallthrough;
	हाल XDP_DROP:
		efx_मुक्त_rx_buffers(rx_queue, rx_buf, 1);
		channel->n_rx_xdp_drops++;
		अवरोध;
	पूर्ण

	वापस xdp_act == XDP_PASS;
पूर्ण

/* Handle a received packet.  Second half: Touches packet payload. */
व्योम __efx_rx_packet(काष्ठा efx_channel *channel)
अणु
	काष्ठा efx_nic *efx = channel->efx;
	काष्ठा efx_rx_buffer *rx_buf =
		efx_rx_buffer(&channel->rx_queue, channel->rx_pkt_index);
	u8 *eh = efx_rx_buf_va(rx_buf);

	/* Read length from the prefix अगर necessary.  This alपढ़ोy
	 * excludes the length of the prefix itself.
	 */
	अगर (rx_buf->flags & EFX_RX_PKT_PREFIX_LEN)
		rx_buf->len = le16_to_cpup((__le16 *)
					   (eh + efx->rx_packet_len_offset));

	/* If we're in loopback test, then pass the packet directly to the
	 * loopback layer, and मुक्त the rx_buf here
	 */
	अगर (unlikely(efx->loopback_selftest)) अणु
		काष्ठा efx_rx_queue *rx_queue;

		efx_loopback_rx_packet(efx, eh, rx_buf->len);
		rx_queue = efx_channel_get_rx_queue(channel);
		efx_मुक्त_rx_buffers(rx_queue, rx_buf,
				    channel->rx_pkt_n_frags);
		जाओ out;
	पूर्ण

	अगर (!efx_करो_xdp(efx, channel, rx_buf, &eh))
		जाओ out;

	अगर (unlikely(!(efx->net_dev->features & NETIF_F_RXCSUM)))
		rx_buf->flags &= ~EFX_RX_PKT_CSUMMED;

	अगर ((rx_buf->flags & EFX_RX_PKT_TCP) && !channel->type->receive_skb)
		efx_rx_packet_gro(channel, rx_buf, channel->rx_pkt_n_frags, eh, 0);
	अन्यथा
		efx_rx_deliver(channel, eh, rx_buf, channel->rx_pkt_n_frags);
out:
	channel->rx_pkt_n_frags = 0;
पूर्ण
