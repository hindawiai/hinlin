<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright (c) 2018, Intel Corporation. */

/* The driver transmit and receive code */

#समावेश <linux/prefetch.h>
#समावेश <linux/mm.h>
#समावेश <linux/bpf_trace.h>
#समावेश <net/xdp.h>
#समावेश "ice_txrx_lib.h"
#समावेश "ice_lib.h"
#समावेश "ice.h"
#समावेश "ice_dcb_lib.h"
#समावेश "ice_xsk.h"

#घोषणा ICE_RX_HDR_SIZE		256

#घोषणा Fसूची_DESC_RXDID 0x40
#घोषणा ICE_Fसूची_CLEAN_DELAY 10

/**
 * ice_prgm_fdir_fltr - Program a Flow Director filter
 * @vsi: VSI to send dummy packet
 * @fdir_desc: flow director descriptor
 * @raw_packet: allocated buffer क्रम flow director
 */
पूर्णांक
ice_prgm_fdir_fltr(काष्ठा ice_vsi *vsi, काष्ठा ice_fltr_desc *fdir_desc,
		   u8 *raw_packet)
अणु
	काष्ठा ice_tx_buf *tx_buf, *first;
	काष्ठा ice_fltr_desc *f_desc;
	काष्ठा ice_tx_desc *tx_desc;
	काष्ठा ice_ring *tx_ring;
	काष्ठा device *dev;
	dma_addr_t dma;
	u32 td_cmd;
	u16 i;

	/* VSI and Tx ring */
	अगर (!vsi)
		वापस -ENOENT;
	tx_ring = vsi->tx_rings[0];
	अगर (!tx_ring || !tx_ring->desc)
		वापस -ENOENT;
	dev = tx_ring->dev;

	/* we are using two descriptors to add/del a filter and we can रुको */
	क्रम (i = ICE_Fसूची_CLEAN_DELAY; ICE_DESC_UNUSED(tx_ring) < 2; i--) अणु
		अगर (!i)
			वापस -EAGAIN;
		msleep_पूर्णांकerruptible(1);
	पूर्ण

	dma = dma_map_single(dev, raw_packet, ICE_Fसूची_MAX_RAW_PKT_SIZE,
			     DMA_TO_DEVICE);

	अगर (dma_mapping_error(dev, dma))
		वापस -EINVAL;

	/* grab the next descriptor */
	i = tx_ring->next_to_use;
	first = &tx_ring->tx_buf[i];
	f_desc = ICE_TX_FसूचीDESC(tx_ring, i);
	स_नकल(f_desc, fdir_desc, माप(*f_desc));

	i++;
	i = (i < tx_ring->count) ? i : 0;
	tx_desc = ICE_TX_DESC(tx_ring, i);
	tx_buf = &tx_ring->tx_buf[i];

	i++;
	tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

	स_रखो(tx_buf, 0, माप(*tx_buf));
	dma_unmap_len_set(tx_buf, len, ICE_Fसूची_MAX_RAW_PKT_SIZE);
	dma_unmap_addr_set(tx_buf, dma, dma);

	tx_desc->buf_addr = cpu_to_le64(dma);
	td_cmd = ICE_TXD_LAST_DESC_CMD | ICE_TX_DESC_CMD_DUMMY |
		 ICE_TX_DESC_CMD_RE;

	tx_buf->tx_flags = ICE_TX_FLAGS_DUMMY_PKT;
	tx_buf->raw_buf = raw_packet;

	tx_desc->cmd_type_offset_bsz =
		ice_build_ctob(td_cmd, 0, ICE_Fसूची_MAX_RAW_PKT_SIZE, 0);

	/* Force memory ग_लिखो to complete beक्रमe letting h/w know
	 * there are new descriptors to fetch.
	 */
	wmb();

	/* mark the data descriptor to be watched */
	first->next_to_watch = tx_desc;

	ग_लिखोl(tx_ring->next_to_use, tx_ring->tail);

	वापस 0;
पूर्ण

/**
 * ice_unmap_and_मुक्त_tx_buf - Release a Tx buffer
 * @ring: the ring that owns the buffer
 * @tx_buf: the buffer to मुक्त
 */
अटल व्योम
ice_unmap_and_मुक्त_tx_buf(काष्ठा ice_ring *ring, काष्ठा ice_tx_buf *tx_buf)
अणु
	अगर (tx_buf->skb) अणु
		अगर (tx_buf->tx_flags & ICE_TX_FLAGS_DUMMY_PKT)
			devm_kमुक्त(ring->dev, tx_buf->raw_buf);
		अन्यथा अगर (ice_ring_is_xdp(ring))
			page_frag_मुक्त(tx_buf->raw_buf);
		अन्यथा
			dev_kमुक्त_skb_any(tx_buf->skb);
		अगर (dma_unmap_len(tx_buf, len))
			dma_unmap_single(ring->dev,
					 dma_unmap_addr(tx_buf, dma),
					 dma_unmap_len(tx_buf, len),
					 DMA_TO_DEVICE);
	पूर्ण अन्यथा अगर (dma_unmap_len(tx_buf, len)) अणु
		dma_unmap_page(ring->dev,
			       dma_unmap_addr(tx_buf, dma),
			       dma_unmap_len(tx_buf, len),
			       DMA_TO_DEVICE);
	पूर्ण

	tx_buf->next_to_watch = शून्य;
	tx_buf->skb = शून्य;
	dma_unmap_len_set(tx_buf, len, 0);
	/* tx_buf must be completely set up in the transmit path */
पूर्ण

अटल काष्ठा netdev_queue *txring_txq(स्थिर काष्ठा ice_ring *ring)
अणु
	वापस netdev_get_tx_queue(ring->netdev, ring->q_index);
पूर्ण

/**
 * ice_clean_tx_ring - Free any empty Tx buffers
 * @tx_ring: ring to be cleaned
 */
व्योम ice_clean_tx_ring(काष्ठा ice_ring *tx_ring)
अणु
	u16 i;

	अगर (ice_ring_is_xdp(tx_ring) && tx_ring->xsk_pool) अणु
		ice_xsk_clean_xdp_ring(tx_ring);
		जाओ tx_skip_मुक्त;
	पूर्ण

	/* ring alपढ़ोy cleared, nothing to करो */
	अगर (!tx_ring->tx_buf)
		वापस;

	/* Free all the Tx ring sk_buffs */
	क्रम (i = 0; i < tx_ring->count; i++)
		ice_unmap_and_मुक्त_tx_buf(tx_ring, &tx_ring->tx_buf[i]);

tx_skip_मुक्त:
	स_रखो(tx_ring->tx_buf, 0, माप(*tx_ring->tx_buf) * tx_ring->count);

	/* Zero out the descriptor ring */
	स_रखो(tx_ring->desc, 0, tx_ring->size);

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;

	अगर (!tx_ring->netdev)
		वापस;

	/* cleanup Tx queue statistics */
	netdev_tx_reset_queue(txring_txq(tx_ring));
पूर्ण

/**
 * ice_मुक्त_tx_ring - Free Tx resources per queue
 * @tx_ring: Tx descriptor ring क्रम a specअगरic queue
 *
 * Free all transmit software resources
 */
व्योम ice_मुक्त_tx_ring(काष्ठा ice_ring *tx_ring)
अणु
	ice_clean_tx_ring(tx_ring);
	devm_kमुक्त(tx_ring->dev, tx_ring->tx_buf);
	tx_ring->tx_buf = शून्य;

	अगर (tx_ring->desc) अणु
		dmam_मुक्त_coherent(tx_ring->dev, tx_ring->size,
				   tx_ring->desc, tx_ring->dma);
		tx_ring->desc = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_clean_tx_irq - Reclaim resources after transmit completes
 * @tx_ring: Tx ring to clean
 * @napi_budget: Used to determine अगर we are in netpoll
 *
 * Returns true अगर there's any budget left (e.g. the clean is finished)
 */
अटल bool ice_clean_tx_irq(काष्ठा ice_ring *tx_ring, पूर्णांक napi_budget)
अणु
	अचिन्हित पूर्णांक total_bytes = 0, total_pkts = 0;
	अचिन्हित पूर्णांक budget = ICE_DFLT_IRQ_WORK;
	काष्ठा ice_vsi *vsi = tx_ring->vsi;
	s16 i = tx_ring->next_to_clean;
	काष्ठा ice_tx_desc *tx_desc;
	काष्ठा ice_tx_buf *tx_buf;

	tx_buf = &tx_ring->tx_buf[i];
	tx_desc = ICE_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	prefetch(&vsi->state);

	करो अणु
		काष्ठा ice_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* अगर next_to_watch is not set then there is no work pending */
		अगर (!eop_desc)
			अवरोध;

		smp_rmb();	/* prevent any other पढ़ोs prior to eop_desc */

		/* अगर the descriptor isn't करोne, no work yet to करो */
		अगर (!(eop_desc->cmd_type_offset_bsz &
		      cpu_to_le64(ICE_TX_DESC_DTYPE_DESC_DONE)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buf->next_to_watch = शून्य;

		/* update the statistics क्रम this packet */
		total_bytes += tx_buf->bytecount;
		total_pkts += tx_buf->gso_segs;

		अगर (ice_ring_is_xdp(tx_ring))
			page_frag_मुक्त(tx_buf->raw_buf);
		अन्यथा
			/* मुक्त the skb */
			napi_consume_skb(tx_buf->skb, napi_budget);

		/* unmap skb header data */
		dma_unmap_single(tx_ring->dev,
				 dma_unmap_addr(tx_buf, dma),
				 dma_unmap_len(tx_buf, len),
				 DMA_TO_DEVICE);

		/* clear tx_buf data */
		tx_buf->skb = शून्य;
		dma_unmap_len_set(tx_buf, len, 0);

		/* unmap reमुख्यing buffers */
		जबतक (tx_desc != eop_desc) अणु
			tx_buf++;
			tx_desc++;
			i++;
			अगर (unlikely(!i)) अणु
				i -= tx_ring->count;
				tx_buf = tx_ring->tx_buf;
				tx_desc = ICE_TX_DESC(tx_ring, 0);
			पूर्ण

			/* unmap any reमुख्यing paged data */
			अगर (dma_unmap_len(tx_buf, len)) अणु
				dma_unmap_page(tx_ring->dev,
					       dma_unmap_addr(tx_buf, dma),
					       dma_unmap_len(tx_buf, len),
					       DMA_TO_DEVICE);
				dma_unmap_len_set(tx_buf, len, 0);
			पूर्ण
		पूर्ण

		/* move us one more past the eop_desc क्रम start of next pkt */
		tx_buf++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_buf;
			tx_desc = ICE_TX_DESC(tx_ring, 0);
		पूर्ण

		prefetch(tx_desc);

		/* update budget accounting */
		budget--;
	पूर्ण जबतक (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;

	ice_update_tx_ring_stats(tx_ring, total_pkts, total_bytes);

	अगर (ice_ring_is_xdp(tx_ring))
		वापस !!budget;

	netdev_tx_completed_queue(txring_txq(tx_ring), total_pkts,
				  total_bytes);

#घोषणा TX_WAKE_THRESHOLD ((s16)(DESC_NEEDED * 2))
	अगर (unlikely(total_pkts && netअगर_carrier_ok(tx_ring->netdev) &&
		     (ICE_DESC_UNUSED(tx_ring) >= TX_WAKE_THRESHOLD))) अणु
		/* Make sure that anybody stopping the queue after this
		 * sees the new next_to_clean.
		 */
		smp_mb();
		अगर (__netअगर_subqueue_stopped(tx_ring->netdev,
					     tx_ring->q_index) &&
		    !test_bit(ICE_VSI_DOWN, vsi->state)) अणु
			netअगर_wake_subqueue(tx_ring->netdev,
					    tx_ring->q_index);
			++tx_ring->tx_stats.restart_q;
		पूर्ण
	पूर्ण

	वापस !!budget;
पूर्ण

/**
 * ice_setup_tx_ring - Allocate the Tx descriptors
 * @tx_ring: the Tx ring to set up
 *
 * Return 0 on success, negative on error
 */
पूर्णांक ice_setup_tx_ring(काष्ठा ice_ring *tx_ring)
अणु
	काष्ठा device *dev = tx_ring->dev;

	अगर (!dev)
		वापस -ENOMEM;

	/* warn अगर we are about to overग_लिखो the poपूर्णांकer */
	WARN_ON(tx_ring->tx_buf);
	tx_ring->tx_buf =
		devm_kzalloc(dev, माप(*tx_ring->tx_buf) * tx_ring->count,
			     GFP_KERNEL);
	अगर (!tx_ring->tx_buf)
		वापस -ENOMEM;

	/* round up to nearest page */
	tx_ring->size = ALIGN(tx_ring->count * माप(काष्ठा ice_tx_desc),
			      PAGE_SIZE);
	tx_ring->desc = dmam_alloc_coherent(dev, tx_ring->size, &tx_ring->dma,
					    GFP_KERNEL);
	अगर (!tx_ring->desc) अणु
		dev_err(dev, "Unable to allocate memory for the Tx descriptor ring, size=%d\n",
			tx_ring->size);
		जाओ err;
	पूर्ण

	tx_ring->next_to_use = 0;
	tx_ring->next_to_clean = 0;
	tx_ring->tx_stats.prev_pkt = -1;
	वापस 0;

err:
	devm_kमुक्त(dev, tx_ring->tx_buf);
	tx_ring->tx_buf = शून्य;
	वापस -ENOMEM;
पूर्ण

/**
 * ice_clean_rx_ring - Free Rx buffers
 * @rx_ring: ring to be cleaned
 */
व्योम ice_clean_rx_ring(काष्ठा ice_ring *rx_ring)
अणु
	काष्ठा device *dev = rx_ring->dev;
	u16 i;

	/* ring alपढ़ोy cleared, nothing to करो */
	अगर (!rx_ring->rx_buf)
		वापस;

	अगर (rx_ring->skb) अणु
		dev_kमुक्त_skb(rx_ring->skb);
		rx_ring->skb = शून्य;
	पूर्ण

	अगर (rx_ring->xsk_pool) अणु
		ice_xsk_clean_rx_ring(rx_ring);
		जाओ rx_skip_मुक्त;
	पूर्ण

	/* Free all the Rx ring sk_buffs */
	क्रम (i = 0; i < rx_ring->count; i++) अणु
		काष्ठा ice_rx_buf *rx_buf = &rx_ring->rx_buf[i];

		अगर (!rx_buf->page)
			जारी;

		/* Invalidate cache lines that may have been written to by
		 * device so that we aव्योम corrupting memory.
		 */
		dma_sync_single_range_क्रम_cpu(dev, rx_buf->dma,
					      rx_buf->page_offset,
					      rx_ring->rx_buf_len,
					      DMA_FROM_DEVICE);

		/* मुक्त resources associated with mapping */
		dma_unmap_page_attrs(dev, rx_buf->dma, ice_rx_pg_size(rx_ring),
				     DMA_FROM_DEVICE, ICE_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buf->page, rx_buf->pagecnt_bias);

		rx_buf->page = शून्य;
		rx_buf->page_offset = 0;
	पूर्ण

rx_skip_मुक्त:
	स_रखो(rx_ring->rx_buf, 0, माप(*rx_ring->rx_buf) * rx_ring->count);

	/* Zero out the descriptor ring */
	स_रखो(rx_ring->desc, 0, rx_ring->size);

	rx_ring->next_to_alloc = 0;
	rx_ring->next_to_clean = 0;
	rx_ring->next_to_use = 0;
पूर्ण

/**
 * ice_मुक्त_rx_ring - Free Rx resources
 * @rx_ring: ring to clean the resources from
 *
 * Free all receive software resources
 */
व्योम ice_मुक्त_rx_ring(काष्ठा ice_ring *rx_ring)
अणु
	ice_clean_rx_ring(rx_ring);
	अगर (rx_ring->vsi->type == ICE_VSI_PF)
		अगर (xdp_rxq_info_is_reg(&rx_ring->xdp_rxq))
			xdp_rxq_info_unreg(&rx_ring->xdp_rxq);
	rx_ring->xdp_prog = शून्य;
	devm_kमुक्त(rx_ring->dev, rx_ring->rx_buf);
	rx_ring->rx_buf = शून्य;

	अगर (rx_ring->desc) अणु
		dmam_मुक्त_coherent(rx_ring->dev, rx_ring->size,
				   rx_ring->desc, rx_ring->dma);
		rx_ring->desc = शून्य;
	पूर्ण
पूर्ण

/**
 * ice_setup_rx_ring - Allocate the Rx descriptors
 * @rx_ring: the Rx ring to set up
 *
 * Return 0 on success, negative on error
 */
पूर्णांक ice_setup_rx_ring(काष्ठा ice_ring *rx_ring)
अणु
	काष्ठा device *dev = rx_ring->dev;

	अगर (!dev)
		वापस -ENOMEM;

	/* warn अगर we are about to overग_लिखो the poपूर्णांकer */
	WARN_ON(rx_ring->rx_buf);
	rx_ring->rx_buf =
		devm_kzalloc(dev, माप(*rx_ring->rx_buf) * rx_ring->count,
			     GFP_KERNEL);
	अगर (!rx_ring->rx_buf)
		वापस -ENOMEM;

	/* round up to nearest page */
	rx_ring->size = ALIGN(rx_ring->count * माप(जोड़ ice_32byte_rx_desc),
			      PAGE_SIZE);
	rx_ring->desc = dmam_alloc_coherent(dev, rx_ring->size, &rx_ring->dma,
					    GFP_KERNEL);
	अगर (!rx_ring->desc) अणु
		dev_err(dev, "Unable to allocate memory for the Rx descriptor ring, size=%d\n",
			rx_ring->size);
		जाओ err;
	पूर्ण

	rx_ring->next_to_use = 0;
	rx_ring->next_to_clean = 0;

	अगर (ice_is_xdp_ena_vsi(rx_ring->vsi))
		WRITE_ONCE(rx_ring->xdp_prog, rx_ring->vsi->xdp_prog);

	अगर (rx_ring->vsi->type == ICE_VSI_PF &&
	    !xdp_rxq_info_is_reg(&rx_ring->xdp_rxq))
		अगर (xdp_rxq_info_reg(&rx_ring->xdp_rxq, rx_ring->netdev,
				     rx_ring->q_index, rx_ring->q_vector->napi.napi_id))
			जाओ err;
	वापस 0;

err:
	devm_kमुक्त(dev, rx_ring->rx_buf);
	rx_ring->rx_buf = शून्य;
	वापस -ENOMEM;
पूर्ण

अटल अचिन्हित पूर्णांक
ice_rx_frame_truesize(काष्ठा ice_ring *rx_ring, अचिन्हित पूर्णांक __maybe_unused size)
अणु
	अचिन्हित पूर्णांक truesize;

#अगर (PAGE_SIZE < 8192)
	truesize = ice_rx_pg_size(rx_ring) / 2; /* Must be घातer-of-2 */
#अन्यथा
	truesize = rx_ring->rx_offset ?
		SKB_DATA_ALIGN(rx_ring->rx_offset + size) +
		SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) :
		SKB_DATA_ALIGN(size);
#पूर्ण_अगर
	वापस truesize;
पूर्ण

/**
 * ice_run_xdp - Executes an XDP program on initialized xdp_buff
 * @rx_ring: Rx ring
 * @xdp: xdp_buff used as input to the XDP program
 * @xdp_prog: XDP program to run
 *
 * Returns any of ICE_XDP_अणुPASS, CONSUMED, TX, REसूचीपूर्ण
 */
अटल पूर्णांक
ice_run_xdp(काष्ठा ice_ring *rx_ring, काष्ठा xdp_buff *xdp,
	    काष्ठा bpf_prog *xdp_prog)
अणु
	काष्ठा ice_ring *xdp_ring;
	पूर्णांक err, result;
	u32 act;

	act = bpf_prog_run_xdp(xdp_prog, xdp);
	चयन (act) अणु
	हाल XDP_PASS:
		वापस ICE_XDP_PASS;
	हाल XDP_TX:
		xdp_ring = rx_ring->vsi->xdp_rings[smp_processor_id()];
		result = ice_xmit_xdp_buff(xdp, xdp_ring);
		अगर (result == ICE_XDP_CONSUMED)
			जाओ out_failure;
		वापस result;
	हाल XDP_REसूचीECT:
		err = xdp_करो_redirect(rx_ring->netdev, xdp, xdp_prog);
		अगर (err)
			जाओ out_failure;
		वापस ICE_XDP_REसूची;
	शेष:
		bpf_warn_invalid_xdp_action(act);
		fallthrough;
	हाल XDP_ABORTED:
out_failure:
		trace_xdp_exception(rx_ring->netdev, xdp_prog, act);
		fallthrough;
	हाल XDP_DROP:
		वापस ICE_XDP_CONSUMED;
	पूर्ण
पूर्ण

/**
 * ice_xdp_xmit - submit packets to XDP ring क्रम transmission
 * @dev: netdev
 * @n: number of XDP frames to be transmitted
 * @frames: XDP frames to be transmitted
 * @flags: transmit flags
 *
 * Returns number of frames successfully sent. Failed frames
 * will be मुक्त'ed by XDP core.
 * For error हालs, a negative त्रुटि_सं code is वापसed and no-frames
 * are transmitted (caller must handle मुक्तing frames).
 */
पूर्णांक
ice_xdp_xmit(काष्ठा net_device *dev, पूर्णांक n, काष्ठा xdp_frame **frames,
	     u32 flags)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(dev);
	अचिन्हित पूर्णांक queue_index = smp_processor_id();
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_ring *xdp_ring;
	पूर्णांक nxmit = 0, i;

	अगर (test_bit(ICE_VSI_DOWN, vsi->state))
		वापस -ENETDOWN;

	अगर (!ice_is_xdp_ena_vsi(vsi) || queue_index >= vsi->num_xdp_txq)
		वापस -ENXIO;

	अगर (unlikely(flags & ~XDP_XMIT_FLAGS_MASK))
		वापस -EINVAL;

	xdp_ring = vsi->xdp_rings[queue_index];
	क्रम (i = 0; i < n; i++) अणु
		काष्ठा xdp_frame *xdpf = frames[i];
		पूर्णांक err;

		err = ice_xmit_xdp_ring(xdpf->data, xdpf->len, xdp_ring);
		अगर (err != ICE_XDP_TX)
			अवरोध;
		nxmit++;
	पूर्ण

	अगर (unlikely(flags & XDP_XMIT_FLUSH))
		ice_xdp_ring_update_tail(xdp_ring);

	वापस nxmit;
पूर्ण

/**
 * ice_alloc_mapped_page - recycle or make a new page
 * @rx_ring: ring to use
 * @bi: rx_buf काष्ठा to modअगरy
 *
 * Returns true अगर the page was successfully allocated or
 * reused.
 */
अटल bool
ice_alloc_mapped_page(काष्ठा ice_ring *rx_ring, काष्ठा ice_rx_buf *bi)
अणु
	काष्ठा page *page = bi->page;
	dma_addr_t dma;

	/* since we are recycling buffers we should selकरोm need to alloc */
	अगर (likely(page))
		वापस true;

	/* alloc new page क्रम storage */
	page = dev_alloc_pages(ice_rx_pg_order(rx_ring));
	अगर (unlikely(!page)) अणु
		rx_ring->rx_stats.alloc_page_failed++;
		वापस false;
	पूर्ण

	/* map page क्रम use */
	dma = dma_map_page_attrs(rx_ring->dev, page, 0, ice_rx_pg_size(rx_ring),
				 DMA_FROM_DEVICE, ICE_RX_DMA_ATTR);

	/* अगर mapping failed मुक्त memory back to प्रणाली since
	 * there isn't much point in holding memory we can't use
	 */
	अगर (dma_mapping_error(rx_ring->dev, dma)) अणु
		__मुक्त_pages(page, ice_rx_pg_order(rx_ring));
		rx_ring->rx_stats.alloc_page_failed++;
		वापस false;
	पूर्ण

	bi->dma = dma;
	bi->page = page;
	bi->page_offset = rx_ring->rx_offset;
	page_ref_add(page, अच_लघु_उच्च - 1);
	bi->pagecnt_bias = अच_लघु_उच्च;

	वापस true;
पूर्ण

/**
 * ice_alloc_rx_bufs - Replace used receive buffers
 * @rx_ring: ring to place buffers on
 * @cleaned_count: number of buffers to replace
 *
 * Returns false अगर all allocations were successful, true अगर any fail. Returning
 * true संकेतs to the caller that we didn't replace cleaned_count buffers and
 * there is more work to करो.
 *
 * First, try to clean "cleaned_count" Rx buffers. Then refill the cleaned Rx
 * buffers. Then bump tail at most one समय. Grouping like this lets us aव्योम
 * multiple tail ग_लिखोs per call.
 */
bool ice_alloc_rx_bufs(काष्ठा ice_ring *rx_ring, u16 cleaned_count)
अणु
	जोड़ ice_32b_rx_flex_desc *rx_desc;
	u16 ntu = rx_ring->next_to_use;
	काष्ठा ice_rx_buf *bi;

	/* करो nothing अगर no valid netdev defined */
	अगर ((!rx_ring->netdev && rx_ring->vsi->type != ICE_VSI_CTRL) ||
	    !cleaned_count)
		वापस false;

	/* get the Rx descriptor and buffer based on next_to_use */
	rx_desc = ICE_RX_DESC(rx_ring, ntu);
	bi = &rx_ring->rx_buf[ntu];

	करो अणु
		/* अगर we fail here, we have work reमुख्यing */
		अगर (!ice_alloc_mapped_page(rx_ring, bi))
			अवरोध;

		/* sync the buffer क्रम use by the device */
		dma_sync_single_range_क्रम_device(rx_ring->dev, bi->dma,
						 bi->page_offset,
						 rx_ring->rx_buf_len,
						 DMA_FROM_DEVICE);

		/* Refresh the desc even अगर buffer_addrs didn't change
		 * because each ग_लिखो-back erases this info.
		 */
		rx_desc->पढ़ो.pkt_addr = cpu_to_le64(bi->dma + bi->page_offset);

		rx_desc++;
		bi++;
		ntu++;
		अगर (unlikely(ntu == rx_ring->count)) अणु
			rx_desc = ICE_RX_DESC(rx_ring, 0);
			bi = rx_ring->rx_buf;
			ntu = 0;
		पूर्ण

		/* clear the status bits क्रम the next_to_use descriptor */
		rx_desc->wb.status_error0 = 0;

		cleaned_count--;
	पूर्ण जबतक (cleaned_count);

	अगर (rx_ring->next_to_use != ntu)
		ice_release_rx_desc(rx_ring, ntu);

	वापस !!cleaned_count;
पूर्ण

/**
 * ice_rx_buf_adjust_pg_offset - Prepare Rx buffer क्रम reuse
 * @rx_buf: Rx buffer to adjust
 * @size: Size of adjusपंचांगent
 *
 * Update the offset within page so that Rx buf will be पढ़ोy to be reused.
 * For प्रणालीs with PAGE_SIZE < 8192 this function will flip the page offset
 * so the second half of page asचिन्हित to Rx buffer will be used, otherwise
 * the offset is moved by "size" bytes
 */
अटल व्योम
ice_rx_buf_adjust_pg_offset(काष्ठा ice_rx_buf *rx_buf, अचिन्हित पूर्णांक size)
अणु
#अगर (PAGE_SIZE < 8192)
	/* flip page offset to other buffer */
	rx_buf->page_offset ^= size;
#अन्यथा
	/* move offset up to the next cache line */
	rx_buf->page_offset += size;
#पूर्ण_अगर
पूर्ण

/**
 * ice_can_reuse_rx_page - Determine अगर page can be reused क्रम another Rx
 * @rx_buf: buffer containing the page
 * @rx_buf_pgcnt: rx_buf page refcount pre xdp_करो_redirect() call
 *
 * If page is reusable, we have a green light क्रम calling ice_reuse_rx_page,
 * which will assign the current buffer to the buffer that next_to_alloc is
 * poपूर्णांकing to; otherwise, the DMA mapping needs to be destroyed and
 * page मुक्तd
 */
अटल bool
ice_can_reuse_rx_page(काष्ठा ice_rx_buf *rx_buf, पूर्णांक rx_buf_pgcnt)
अणु
	अचिन्हित पूर्णांक pagecnt_bias = rx_buf->pagecnt_bias;
	काष्ठा page *page = rx_buf->page;

	/* aव्योम re-using remote and pfmeदो_स्मृति pages */
	अगर (!dev_page_is_reusable(page))
		वापस false;

#अगर (PAGE_SIZE < 8192)
	/* अगर we are only owner of page we can reuse it */
	अगर (unlikely((rx_buf_pgcnt - pagecnt_bias) > 1))
		वापस false;
#अन्यथा
#घोषणा ICE_LAST_OFFSET \
	(SKB_WITH_OVERHEAD(PAGE_SIZE) - ICE_RXBUF_2048)
	अगर (rx_buf->page_offset > ICE_LAST_OFFSET)
		वापस false;
#पूर्ण_अगर /* PAGE_SIZE < 8192) */

	/* If we have drained the page fragment pool we need to update
	 * the pagecnt_bias and page count so that we fully restock the
	 * number of references the driver holds.
	 */
	अगर (unlikely(pagecnt_bias == 1)) अणु
		page_ref_add(page, अच_लघु_उच्च - 1);
		rx_buf->pagecnt_bias = अच_लघु_उच्च;
	पूर्ण

	वापस true;
पूर्ण

/**
 * ice_add_rx_frag - Add contents of Rx buffer to sk_buff as a frag
 * @rx_ring: Rx descriptor ring to transact packets on
 * @rx_buf: buffer containing page to add
 * @skb: sk_buff to place the data पूर्णांकo
 * @size: packet length from rx_desc
 *
 * This function will add the data contained in rx_buf->page to the skb.
 * It will just attach the page as a frag to the skb.
 * The function will then update the page offset.
 */
अटल व्योम
ice_add_rx_frag(काष्ठा ice_ring *rx_ring, काष्ठा ice_rx_buf *rx_buf,
		काष्ठा sk_buff *skb, अचिन्हित पूर्णांक size)
अणु
#अगर (PAGE_SIZE >= 8192)
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(size + rx_ring->rx_offset);
#अन्यथा
	अचिन्हित पूर्णांक truesize = ice_rx_pg_size(rx_ring) / 2;
#पूर्ण_अगर

	अगर (!size)
		वापस;
	skb_add_rx_frag(skb, skb_shinfo(skb)->nr_frags, rx_buf->page,
			rx_buf->page_offset, size, truesize);

	/* page is being used so we must update the page offset */
	ice_rx_buf_adjust_pg_offset(rx_buf, truesize);
पूर्ण

/**
 * ice_reuse_rx_page - page flip buffer and store it back on the ring
 * @rx_ring: Rx descriptor ring to store buffers on
 * @old_buf: करोnor buffer to have page reused
 *
 * Synchronizes page क्रम reuse by the adapter
 */
अटल व्योम
ice_reuse_rx_page(काष्ठा ice_ring *rx_ring, काष्ठा ice_rx_buf *old_buf)
अणु
	u16 nta = rx_ring->next_to_alloc;
	काष्ठा ice_rx_buf *new_buf;

	new_buf = &rx_ring->rx_buf[nta];

	/* update, and store next to alloc */
	nta++;
	rx_ring->next_to_alloc = (nta < rx_ring->count) ? nta : 0;

	/* Transfer page from old buffer to new buffer.
	 * Move each member inभागidually to aव्योम possible store
	 * क्रमwarding stalls and unnecessary copy of skb.
	 */
	new_buf->dma = old_buf->dma;
	new_buf->page = old_buf->page;
	new_buf->page_offset = old_buf->page_offset;
	new_buf->pagecnt_bias = old_buf->pagecnt_bias;
पूर्ण

/**
 * ice_get_rx_buf - Fetch Rx buffer and synchronize data क्रम use
 * @rx_ring: Rx descriptor ring to transact packets on
 * @size: size of buffer to add to skb
 * @rx_buf_pgcnt: rx_buf page refcount
 *
 * This function will pull an Rx buffer from the ring and synchronize it
 * क्रम use by the CPU.
 */
अटल काष्ठा ice_rx_buf *
ice_get_rx_buf(काष्ठा ice_ring *rx_ring, स्थिर अचिन्हित पूर्णांक size,
	       पूर्णांक *rx_buf_pgcnt)
अणु
	काष्ठा ice_rx_buf *rx_buf;

	rx_buf = &rx_ring->rx_buf[rx_ring->next_to_clean];
	*rx_buf_pgcnt =
#अगर (PAGE_SIZE < 8192)
		page_count(rx_buf->page);
#अन्यथा
		0;
#पूर्ण_अगर
	prefetchw(rx_buf->page);

	अगर (!size)
		वापस rx_buf;
	/* we are reusing so sync this buffer क्रम CPU use */
	dma_sync_single_range_क्रम_cpu(rx_ring->dev, rx_buf->dma,
				      rx_buf->page_offset, size,
				      DMA_FROM_DEVICE);

	/* We have pulled a buffer क्रम use, so decrement pagecnt_bias */
	rx_buf->pagecnt_bias--;

	वापस rx_buf;
पूर्ण

/**
 * ice_build_skb - Build skb around an existing buffer
 * @rx_ring: Rx descriptor ring to transact packets on
 * @rx_buf: Rx buffer to pull data from
 * @xdp: xdp_buff poपूर्णांकing to the data
 *
 * This function builds an skb around an existing Rx buffer, taking care
 * to set up the skb correctly and aव्योम any स_नकल overhead.
 */
अटल काष्ठा sk_buff *
ice_build_skb(काष्ठा ice_ring *rx_ring, काष्ठा ice_rx_buf *rx_buf,
	      काष्ठा xdp_buff *xdp)
अणु
	u8 metasize = xdp->data - xdp->data_meta;
#अगर (PAGE_SIZE < 8192)
	अचिन्हित पूर्णांक truesize = ice_rx_pg_size(rx_ring) / 2;
#अन्यथा
	अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(माप(काष्ठा skb_shared_info)) +
				SKB_DATA_ALIGN(xdp->data_end -
					       xdp->data_hard_start);
#पूर्ण_अगर
	काष्ठा sk_buff *skb;

	/* Prefetch first cache line of first page. If xdp->data_meta
	 * is unused, this poपूर्णांकs exactly as xdp->data, otherwise we
	 * likely have a consumer accessing first few bytes of meta
	 * data, and then actual data.
	 */
	net_prefetch(xdp->data_meta);
	/* build an skb around the page buffer */
	skb = build_skb(xdp->data_hard_start, truesize);
	अगर (unlikely(!skb))
		वापस शून्य;

	/* must to record Rx queue, otherwise OS features such as
	 * symmetric queue won't work
	 */
	skb_record_rx_queue(skb, rx_ring->q_index);

	/* update poपूर्णांकers within the skb to store the data */
	skb_reserve(skb, xdp->data - xdp->data_hard_start);
	__skb_put(skb, xdp->data_end - xdp->data);
	अगर (metasize)
		skb_metadata_set(skb, metasize);

	/* buffer is used by skb, update page_offset */
	ice_rx_buf_adjust_pg_offset(rx_buf, truesize);

	वापस skb;
पूर्ण

/**
 * ice_स्थिरruct_skb - Allocate skb and populate it
 * @rx_ring: Rx descriptor ring to transact packets on
 * @rx_buf: Rx buffer to pull data from
 * @xdp: xdp_buff poपूर्णांकing to the data
 *
 * This function allocates an skb. It then populates it with the page
 * data from the current receive descriptor, taking care to set up the
 * skb correctly.
 */
अटल काष्ठा sk_buff *
ice_स्थिरruct_skb(काष्ठा ice_ring *rx_ring, काष्ठा ice_rx_buf *rx_buf,
		  काष्ठा xdp_buff *xdp)
अणु
	अचिन्हित पूर्णांक size = xdp->data_end - xdp->data;
	अचिन्हित पूर्णांक headlen;
	काष्ठा sk_buff *skb;

	/* prefetch first cache line of first page */
	net_prefetch(xdp->data);

	/* allocate a skb to store the frags */
	skb = __napi_alloc_skb(&rx_ring->q_vector->napi, ICE_RX_HDR_SIZE,
			       GFP_ATOMIC | __GFP_NOWARN);
	अगर (unlikely(!skb))
		वापस शून्य;

	skb_record_rx_queue(skb, rx_ring->q_index);
	/* Determine available headroom क्रम copy */
	headlen = size;
	अगर (headlen > ICE_RX_HDR_SIZE)
		headlen = eth_get_headlen(skb->dev, xdp->data, ICE_RX_HDR_SIZE);

	/* align pull length to size of दीर्घ to optimize स_नकल perक्रमmance */
	स_नकल(__skb_put(skb, headlen), xdp->data, ALIGN(headlen,
							 माप(दीर्घ)));

	/* अगर we exhaust the linear part then add what is left as a frag */
	size -= headlen;
	अगर (size) अणु
#अगर (PAGE_SIZE >= 8192)
		अचिन्हित पूर्णांक truesize = SKB_DATA_ALIGN(size);
#अन्यथा
		अचिन्हित पूर्णांक truesize = ice_rx_pg_size(rx_ring) / 2;
#पूर्ण_अगर
		skb_add_rx_frag(skb, 0, rx_buf->page,
				rx_buf->page_offset + headlen, size, truesize);
		/* buffer is used by skb, update page_offset */
		ice_rx_buf_adjust_pg_offset(rx_buf, truesize);
	पूर्ण अन्यथा अणु
		/* buffer is unused, reset bias back to rx_buf; data was copied
		 * onto skb's linear part so there's no need क्रम adjusting
		 * page offset and we can reuse this buffer as-is
		 */
		rx_buf->pagecnt_bias++;
	पूर्ण

	वापस skb;
पूर्ण

/**
 * ice_put_rx_buf - Clean up used buffer and either recycle or मुक्त
 * @rx_ring: Rx descriptor ring to transact packets on
 * @rx_buf: Rx buffer to pull data from
 * @rx_buf_pgcnt: Rx buffer page count pre xdp_करो_redirect()
 *
 * This function will update next_to_clean and then clean up the contents
 * of the rx_buf. It will either recycle the buffer or unmap it and मुक्त
 * the associated resources.
 */
अटल व्योम
ice_put_rx_buf(काष्ठा ice_ring *rx_ring, काष्ठा ice_rx_buf *rx_buf,
	       पूर्णांक rx_buf_pgcnt)
अणु
	u16 ntc = rx_ring->next_to_clean + 1;

	/* fetch, update, and store next to clean */
	ntc = (ntc < rx_ring->count) ? ntc : 0;
	rx_ring->next_to_clean = ntc;

	अगर (!rx_buf)
		वापस;

	अगर (ice_can_reuse_rx_page(rx_buf, rx_buf_pgcnt)) अणु
		/* hand second half of page back to the ring */
		ice_reuse_rx_page(rx_ring, rx_buf);
	पूर्ण अन्यथा अणु
		/* we are not reusing the buffer so unmap it */
		dma_unmap_page_attrs(rx_ring->dev, rx_buf->dma,
				     ice_rx_pg_size(rx_ring), DMA_FROM_DEVICE,
				     ICE_RX_DMA_ATTR);
		__page_frag_cache_drain(rx_buf->page, rx_buf->pagecnt_bias);
	पूर्ण

	/* clear contents of buffer_info */
	rx_buf->page = शून्य;
पूर्ण

/**
 * ice_is_non_eop - process handling of non-EOP buffers
 * @rx_ring: Rx ring being processed
 * @rx_desc: Rx descriptor क्रम current buffer
 *
 * If the buffer is an EOP buffer, this function निकासs वापसing false,
 * otherwise वापस true indicating that this is in fact a non-EOP buffer.
 */
अटल bool
ice_is_non_eop(काष्ठा ice_ring *rx_ring, जोड़ ice_32b_rx_flex_desc *rx_desc)
अणु
	/* अगर we are the last buffer then there is nothing अन्यथा to करो */
#घोषणा ICE_RXD_खातापूर्ण BIT(ICE_RX_FLEX_DESC_STATUS0_खातापूर्ण_S)
	अगर (likely(ice_test_staterr(rx_desc, ICE_RXD_खातापूर्ण)))
		वापस false;

	rx_ring->rx_stats.non_eop_descs++;

	वापस true;
पूर्ण

/**
 * ice_clean_rx_irq - Clean completed descriptors from Rx ring - bounce buf
 * @rx_ring: Rx descriptor ring to transact packets on
 * @budget: Total limit on number of packets to process
 *
 * This function provides a "bounce buffer" approach to Rx पूर्णांकerrupt
 * processing. The advantage to this is that on प्रणालीs that have
 * expensive overhead क्रम IOMMU access this provides a means of aव्योमing
 * it by मुख्यtaining the mapping of the page to the प्रणाली.
 *
 * Returns amount of work completed
 */
पूर्णांक ice_clean_rx_irq(काष्ठा ice_ring *rx_ring, पूर्णांक budget)
अणु
	अचिन्हित पूर्णांक total_rx_bytes = 0, total_rx_pkts = 0, frame_sz = 0;
	u16 cleaned_count = ICE_DESC_UNUSED(rx_ring);
	अचिन्हित पूर्णांक offset = rx_ring->rx_offset;
	अचिन्हित पूर्णांक xdp_res, xdp_xmit = 0;
	काष्ठा sk_buff *skb = rx_ring->skb;
	काष्ठा bpf_prog *xdp_prog = शून्य;
	काष्ठा xdp_buff xdp;
	bool failure;

	/* Frame size depend on rx_ring setup when PAGE_SIZE=4K */
#अगर (PAGE_SIZE < 8192)
	frame_sz = ice_rx_frame_truesize(rx_ring, 0);
#पूर्ण_अगर
	xdp_init_buff(&xdp, frame_sz, &rx_ring->xdp_rxq);

	/* start the loop to process Rx packets bounded by 'budget' */
	जबतक (likely(total_rx_pkts < (अचिन्हित पूर्णांक)budget)) अणु
		जोड़ ice_32b_rx_flex_desc *rx_desc;
		काष्ठा ice_rx_buf *rx_buf;
		अचिन्हित अक्षर *hard_start;
		अचिन्हित पूर्णांक size;
		u16 stat_err_bits;
		पूर्णांक rx_buf_pgcnt;
		u16 vlan_tag = 0;
		u8 rx_ptype;

		/* get the Rx desc from Rx ring based on 'next_to_clean' */
		rx_desc = ICE_RX_DESC(rx_ring, rx_ring->next_to_clean);

		/* status_error_len will always be zero क्रम unused descriptors
		 * because it's cleared in cleanup, and overlaps with hdr_addr
		 * which is always zero because packet split isn't used, अगर the
		 * hardware wrote DD then it will be non-zero
		 */
		stat_err_bits = BIT(ICE_RX_FLEX_DESC_STATUS0_DD_S);
		अगर (!ice_test_staterr(rx_desc, stat_err_bits))
			अवरोध;

		/* This memory barrier is needed to keep us from पढ़ोing
		 * any other fields out of the rx_desc until we know the
		 * DD bit is set.
		 */
		dma_rmb();

		अगर (rx_desc->wb.rxdid == Fसूची_DESC_RXDID || !rx_ring->netdev) अणु
			काष्ठा ice_vsi *ctrl_vsi = rx_ring->vsi;

			अगर (rx_desc->wb.rxdid == Fसूची_DESC_RXDID &&
			    ctrl_vsi->vf_id != ICE_INVAL_VFID)
				ice_vc_fdir_irq_handler(ctrl_vsi, rx_desc);
			ice_put_rx_buf(rx_ring, शून्य, 0);
			cleaned_count++;
			जारी;
		पूर्ण

		size = le16_to_cpu(rx_desc->wb.pkt_len) &
			ICE_RX_FLX_DESC_PKT_LEN_M;

		/* retrieve a buffer from the ring */
		rx_buf = ice_get_rx_buf(rx_ring, size, &rx_buf_pgcnt);

		अगर (!size) अणु
			xdp.data = शून्य;
			xdp.data_end = शून्य;
			xdp.data_hard_start = शून्य;
			xdp.data_meta = शून्य;
			जाओ स्थिरruct_skb;
		पूर्ण

		hard_start = page_address(rx_buf->page) + rx_buf->page_offset -
			     offset;
		xdp_prepare_buff(&xdp, hard_start, offset, size, true);
#अगर (PAGE_SIZE > 4096)
		/* At larger PAGE_SIZE, frame_sz depend on len size */
		xdp.frame_sz = ice_rx_frame_truesize(rx_ring, size);
#पूर्ण_अगर

		rcu_पढ़ो_lock();
		xdp_prog = READ_ONCE(rx_ring->xdp_prog);
		अगर (!xdp_prog) अणु
			rcu_पढ़ो_unlock();
			जाओ स्थिरruct_skb;
		पूर्ण

		xdp_res = ice_run_xdp(rx_ring, &xdp, xdp_prog);
		rcu_पढ़ो_unlock();
		अगर (!xdp_res)
			जाओ स्थिरruct_skb;
		अगर (xdp_res & (ICE_XDP_TX | ICE_XDP_REसूची)) अणु
			xdp_xmit |= xdp_res;
			ice_rx_buf_adjust_pg_offset(rx_buf, xdp.frame_sz);
		पूर्ण अन्यथा अणु
			rx_buf->pagecnt_bias++;
		पूर्ण
		total_rx_bytes += size;
		total_rx_pkts++;

		cleaned_count++;
		ice_put_rx_buf(rx_ring, rx_buf, rx_buf_pgcnt);
		जारी;
स्थिरruct_skb:
		अगर (skb) अणु
			ice_add_rx_frag(rx_ring, rx_buf, skb, size);
		पूर्ण अन्यथा अगर (likely(xdp.data)) अणु
			अगर (ice_ring_uses_build_skb(rx_ring))
				skb = ice_build_skb(rx_ring, rx_buf, &xdp);
			अन्यथा
				skb = ice_स्थिरruct_skb(rx_ring, rx_buf, &xdp);
		पूर्ण
		/* निकास अगर we failed to retrieve a buffer */
		अगर (!skb) अणु
			rx_ring->rx_stats.alloc_buf_failed++;
			अगर (rx_buf)
				rx_buf->pagecnt_bias++;
			अवरोध;
		पूर्ण

		ice_put_rx_buf(rx_ring, rx_buf, rx_buf_pgcnt);
		cleaned_count++;

		/* skip अगर it is NOP desc */
		अगर (ice_is_non_eop(rx_ring, rx_desc))
			जारी;

		stat_err_bits = BIT(ICE_RX_FLEX_DESC_STATUS0_RXE_S);
		अगर (unlikely(ice_test_staterr(rx_desc, stat_err_bits))) अणु
			dev_kमुक्त_skb_any(skb);
			जारी;
		पूर्ण

		stat_err_bits = BIT(ICE_RX_FLEX_DESC_STATUS0_L2TAG1P_S);
		अगर (ice_test_staterr(rx_desc, stat_err_bits))
			vlan_tag = le16_to_cpu(rx_desc->wb.l2tag1);

		/* pad the skb अगर needed, to make a valid ethernet frame */
		अगर (eth_skb_pad(skb)) अणु
			skb = शून्य;
			जारी;
		पूर्ण

		/* probably a little skewed due to removing CRC */
		total_rx_bytes += skb->len;

		/* populate checksum, VLAN, and protocol */
		rx_ptype = le16_to_cpu(rx_desc->wb.ptype_flex_flags0) &
			ICE_RX_FLEX_DESC_PTYPE_M;

		ice_process_skb_fields(rx_ring, rx_desc, skb, rx_ptype);

		/* send completed skb up the stack */
		ice_receive_skb(rx_ring, skb, vlan_tag);
		skb = शून्य;

		/* update budget accounting */
		total_rx_pkts++;
	पूर्ण

	/* वापस up to cleaned_count buffers to hardware */
	failure = ice_alloc_rx_bufs(rx_ring, cleaned_count);

	अगर (xdp_prog)
		ice_finalize_xdp_rx(rx_ring, xdp_xmit);
	rx_ring->skb = skb;

	ice_update_rx_ring_stats(rx_ring, total_rx_pkts, total_rx_bytes);

	/* guarantee a trip back through this routine अगर there was a failure */
	वापस failure ? budget : (पूर्णांक)total_rx_pkts;
पूर्ण

/**
 * ice_net_dim - Update net DIM algorithm
 * @q_vector: the vector associated with the पूर्णांकerrupt
 *
 * Create a DIM sample and notअगरy net_dim() so that it can possibly decide
 * a new ITR value based on incoming packets, bytes, and पूर्णांकerrupts.
 *
 * This function is a no-op अगर the ring is not configured to dynamic ITR.
 */
अटल व्योम ice_net_dim(काष्ठा ice_q_vector *q_vector)
अणु
	काष्ठा ice_ring_container *tx = &q_vector->tx;
	काष्ठा ice_ring_container *rx = &q_vector->rx;

	अगर (ITR_IS_DYNAMIC(tx)) अणु
		काष्ठा dim_sample dim_sample = अणुपूर्ण;
		u64 packets = 0, bytes = 0;
		काष्ठा ice_ring *ring;

		ice_क्रम_each_ring(ring, q_vector->tx) अणु
			packets += ring->stats.pkts;
			bytes += ring->stats.bytes;
		पूर्ण

		dim_update_sample(q_vector->total_events, packets, bytes,
				  &dim_sample);

		net_dim(&tx->dim, dim_sample);
	पूर्ण

	अगर (ITR_IS_DYNAMIC(rx)) अणु
		काष्ठा dim_sample dim_sample = अणुपूर्ण;
		u64 packets = 0, bytes = 0;
		काष्ठा ice_ring *ring;

		ice_क्रम_each_ring(ring, q_vector->rx) अणु
			packets += ring->stats.pkts;
			bytes += ring->stats.bytes;
		पूर्ण

		dim_update_sample(q_vector->total_events, packets, bytes,
				  &dim_sample);

		net_dim(&rx->dim, dim_sample);
	पूर्ण
पूर्ण

/**
 * ice_buildreg_itr - build value क्रम writing to the GLINT_DYN_CTL रेजिस्टर
 * @itr_idx: पूर्णांकerrupt throttling index
 * @itr: पूर्णांकerrupt throttling value in usecs
 */
अटल u32 ice_buildreg_itr(u16 itr_idx, u16 itr)
अणु
	/* The ITR value is reported in microseconds, and the रेजिस्टर value is
	 * recorded in 2 microsecond units. For this reason we only need to
	 * shअगरt by the GLINT_DYN_CTL_INTERVAL_S - ICE_ITR_GRAN_S to apply this
	 * granularity as a shअगरt instead of भागision. The mask makes sure the
	 * ITR value is never odd so we करोn't accidentally ग_लिखो पूर्णांकo the field
	 * prior to the ITR field.
	 */
	itr &= ICE_ITR_MASK;

	वापस GLINT_DYN_CTL_INTENA_M | GLINT_DYN_CTL_CLEARPBA_M |
		(itr_idx << GLINT_DYN_CTL_ITR_INDX_S) |
		(itr << (GLINT_DYN_CTL_INTERVAL_S - ICE_ITR_GRAN_S));
पूर्ण

/**
 * ice_update_ena_itr - Update ITR moderation and re-enable MSI-X पूर्णांकerrupt
 * @q_vector: the vector associated with the पूर्णांकerrupt to enable
 *
 * Update the net_dim() algorithm and re-enable the पूर्णांकerrupt associated with
 * this vector.
 *
 * If the VSI is करोwn, the पूर्णांकerrupt will not be re-enabled.
 */
अटल व्योम ice_update_ena_itr(काष्ठा ice_q_vector *q_vector)
अणु
	काष्ठा ice_vsi *vsi = q_vector->vsi;
	bool wb_en = q_vector->wb_on_itr;
	u32 itr_val;

	अगर (test_bit(ICE_DOWN, vsi->state))
		वापस;

	/* When निकासing WB_ON_ITR, let ITR resume its normal
	 * पूर्णांकerrupts-enabled path.
	 */
	अगर (wb_en)
		q_vector->wb_on_itr = false;

	/* This will करो nothing अगर dynamic updates are not enabled. */
	ice_net_dim(q_vector);

	/* net_dim() updates ITR out-of-band using a work item */
	itr_val = ice_buildreg_itr(ICE_ITR_NONE, 0);
	/* trigger an immediate software पूर्णांकerrupt when निकासing
	 * busy poll, to make sure to catch any pending cleanups
	 * that might have been missed due to पूर्णांकerrupt state
	 * transition.
	 */
	अगर (wb_en) अणु
		itr_val |= GLINT_DYN_CTL_SWINT_TRIG_M |
			   GLINT_DYN_CTL_SW_ITR_INDX_M |
			   GLINT_DYN_CTL_SW_ITR_INDX_ENA_M;
	पूर्ण
	wr32(&vsi->back->hw, GLINT_DYN_CTL(q_vector->reg_idx), itr_val);
पूर्ण

/**
 * ice_set_wb_on_itr - set WB_ON_ITR क्रम this q_vector
 * @q_vector: q_vector to set WB_ON_ITR on
 *
 * We need to tell hardware to ग_लिखो-back completed descriptors even when
 * पूर्णांकerrupts are disabled. Descriptors will be written back on cache line
 * boundaries without WB_ON_ITR enabled, but अगर we करोn't enable WB_ON_ITR
 * descriptors may not be written back अगर they करोn't fill a cache line until
 * the next पूर्णांकerrupt.
 *
 * This sets the ग_लिखो-back frequency to whatever was set previously क्रम the
 * ITR indices. Also, set the INTENA_MSK bit to make sure hardware knows we
 * aren't meddling with the INTENA_M bit.
 */
अटल व्योम ice_set_wb_on_itr(काष्ठा ice_q_vector *q_vector)
अणु
	काष्ठा ice_vsi *vsi = q_vector->vsi;

	/* alपढ़ोy in wb_on_itr mode no need to change it */
	अगर (q_vector->wb_on_itr)
		वापस;

	/* use previously set ITR values क्रम all of the ITR indices by
	 * specअगरying ICE_ITR_NONE, which will vary in adaptive (AIM) mode and
	 * be अटल in non-adaptive mode (user configured)
	 */
	wr32(&vsi->back->hw, GLINT_DYN_CTL(q_vector->reg_idx),
	     ((ICE_ITR_NONE << GLINT_DYN_CTL_ITR_INDX_S) &
	      GLINT_DYN_CTL_ITR_INDX_M) | GLINT_DYN_CTL_INTENA_MSK_M |
	     GLINT_DYN_CTL_WB_ON_ITR_M);

	q_vector->wb_on_itr = true;
पूर्ण

/**
 * ice_napi_poll - NAPI polling Rx/Tx cleanup routine
 * @napi: napi काष्ठा with our devices info in it
 * @budget: amount of work driver is allowed to करो this pass, in packets
 *
 * This function will clean all queues associated with a q_vector.
 *
 * Returns the amount of work करोne
 */
पूर्णांक ice_napi_poll(काष्ठा napi_काष्ठा *napi, पूर्णांक budget)
अणु
	काष्ठा ice_q_vector *q_vector =
				container_of(napi, काष्ठा ice_q_vector, napi);
	bool clean_complete = true;
	काष्ठा ice_ring *ring;
	पूर्णांक budget_per_ring;
	पूर्णांक work_करोne = 0;

	/* Since the actual Tx work is minimal, we can give the Tx a larger
	 * budget and be more aggressive about cleaning up the Tx descriptors.
	 */
	ice_क्रम_each_ring(ring, q_vector->tx) अणु
		bool wd = ring->xsk_pool ?
			  ice_clean_tx_irq_zc(ring, budget) :
			  ice_clean_tx_irq(ring, budget);

		अगर (!wd)
			clean_complete = false;
	पूर्ण

	/* Handle हाल where we are called by netpoll with a budget of 0 */
	अगर (unlikely(budget <= 0))
		वापस budget;

	/* normally we have 1 Rx ring per q_vector */
	अगर (unlikely(q_vector->num_ring_rx > 1))
		/* We attempt to distribute budget to each Rx queue fairly, but
		 * करोn't allow the budget to go below 1 because that would निकास
		 * polling early.
		 */
		budget_per_ring = max_t(पूर्णांक, budget / q_vector->num_ring_rx, 1);
	अन्यथा
		/* Max of 1 Rx ring in this q_vector so give it the budget */
		budget_per_ring = budget;

	ice_क्रम_each_ring(ring, q_vector->rx) अणु
		पूर्णांक cleaned;

		/* A dedicated path क्रम zero-copy allows making a single
		 * comparison in the irq context instead of many inside the
		 * ice_clean_rx_irq function and makes the codebase cleaner.
		 */
		cleaned = ring->xsk_pool ?
			  ice_clean_rx_irq_zc(ring, budget_per_ring) :
			  ice_clean_rx_irq(ring, budget_per_ring);
		work_करोne += cleaned;
		/* अगर we clean as many as budgeted, we must not be करोne */
		अगर (cleaned >= budget_per_ring)
			clean_complete = false;
	पूर्ण

	/* If work not completed, वापस budget and polling will वापस */
	अगर (!clean_complete) अणु
		/* Set the ग_लिखोback on ITR so partial completions of
		 * cache-lines will still जारी even अगर we're polling.
		 */
		ice_set_wb_on_itr(q_vector);
		वापस budget;
	पूर्ण

	/* Exit the polling mode, but करोn't re-enable पूर्णांकerrupts अगर stack might
	 * poll us due to busy-polling
	 */
	अगर (likely(napi_complete_करोne(napi, work_करोne)))
		ice_update_ena_itr(q_vector);
	अन्यथा
		ice_set_wb_on_itr(q_vector);

	वापस min_t(पूर्णांक, work_करोne, budget - 1);
पूर्ण

/**
 * __ice_maybe_stop_tx - 2nd level check क्रम Tx stop conditions
 * @tx_ring: the ring to be checked
 * @size: the size buffer we want to assure is available
 *
 * Returns -EBUSY अगर a stop is needed, अन्यथा 0
 */
अटल पूर्णांक __ice_maybe_stop_tx(काष्ठा ice_ring *tx_ring, अचिन्हित पूर्णांक size)
अणु
	netअगर_stop_subqueue(tx_ring->netdev, tx_ring->q_index);
	/* Memory barrier beक्रमe checking head and tail */
	smp_mb();

	/* Check again in a हाल another CPU has just made room available. */
	अगर (likely(ICE_DESC_UNUSED(tx_ring) < size))
		वापस -EBUSY;

	/* A reprieve! - use start_subqueue because it करोesn't call schedule */
	netअगर_start_subqueue(tx_ring->netdev, tx_ring->q_index);
	++tx_ring->tx_stats.restart_q;
	वापस 0;
पूर्ण

/**
 * ice_maybe_stop_tx - 1st level check क्रम Tx stop conditions
 * @tx_ring: the ring to be checked
 * @size:    the size buffer we want to assure is available
 *
 * Returns 0 अगर stop is not needed
 */
अटल पूर्णांक ice_maybe_stop_tx(काष्ठा ice_ring *tx_ring, अचिन्हित पूर्णांक size)
अणु
	अगर (likely(ICE_DESC_UNUSED(tx_ring) >= size))
		वापस 0;

	वापस __ice_maybe_stop_tx(tx_ring, size);
पूर्ण

/**
 * ice_tx_map - Build the Tx descriptor
 * @tx_ring: ring to send buffer on
 * @first: first buffer info buffer to use
 * @off: poपूर्णांकer to काष्ठा that holds offload parameters
 *
 * This function loops over the skb data poपूर्णांकed to by *first
 * and माला_लो a physical address क्रम each memory location and programs
 * it and the length पूर्णांकo the transmit descriptor.
 */
अटल व्योम
ice_tx_map(काष्ठा ice_ring *tx_ring, काष्ठा ice_tx_buf *first,
	   काष्ठा ice_tx_offload_params *off)
अणु
	u64 td_offset, td_tag, td_cmd;
	u16 i = tx_ring->next_to_use;
	अचिन्हित पूर्णांक data_len, size;
	काष्ठा ice_tx_desc *tx_desc;
	काष्ठा ice_tx_buf *tx_buf;
	काष्ठा sk_buff *skb;
	skb_frag_t *frag;
	dma_addr_t dma;

	td_tag = off->td_l2tag1;
	td_cmd = off->td_cmd;
	td_offset = off->td_offset;
	skb = first->skb;

	data_len = skb->data_len;
	size = skb_headlen(skb);

	tx_desc = ICE_TX_DESC(tx_ring, i);

	अगर (first->tx_flags & ICE_TX_FLAGS_HW_VLAN) अणु
		td_cmd |= (u64)ICE_TX_DESC_CMD_IL2TAG1;
		td_tag = (first->tx_flags & ICE_TX_FLAGS_VLAN_M) >>
			  ICE_TX_FLAGS_VLAN_S;
	पूर्ण

	dma = dma_map_single(tx_ring->dev, skb->data, size, DMA_TO_DEVICE);

	tx_buf = first;

	क्रम (frag = &skb_shinfo(skb)->frags[0];; frag++) अणु
		अचिन्हित पूर्णांक max_data = ICE_MAX_DATA_PER_TXD_ALIGNED;

		अगर (dma_mapping_error(tx_ring->dev, dma))
			जाओ dma_error;

		/* record length, and DMA address */
		dma_unmap_len_set(tx_buf, len, size);
		dma_unmap_addr_set(tx_buf, dma, dma);

		/* align size to end of page */
		max_data += -dma & (ICE_MAX_READ_REQ_SIZE - 1);
		tx_desc->buf_addr = cpu_to_le64(dma);

		/* account क्रम data chunks larger than the hardware
		 * can handle
		 */
		जबतक (unlikely(size > ICE_MAX_DATA_PER_TXD)) अणु
			tx_desc->cmd_type_offset_bsz =
				ice_build_ctob(td_cmd, td_offset, max_data,
					       td_tag);

			tx_desc++;
			i++;

			अगर (i == tx_ring->count) अणु
				tx_desc = ICE_TX_DESC(tx_ring, 0);
				i = 0;
			पूर्ण

			dma += max_data;
			size -= max_data;

			max_data = ICE_MAX_DATA_PER_TXD_ALIGNED;
			tx_desc->buf_addr = cpu_to_le64(dma);
		पूर्ण

		अगर (likely(!data_len))
			अवरोध;

		tx_desc->cmd_type_offset_bsz = ice_build_ctob(td_cmd, td_offset,
							      size, td_tag);

		tx_desc++;
		i++;

		अगर (i == tx_ring->count) अणु
			tx_desc = ICE_TX_DESC(tx_ring, 0);
			i = 0;
		पूर्ण

		size = skb_frag_size(frag);
		data_len -= size;

		dma = skb_frag_dma_map(tx_ring->dev, frag, 0, size,
				       DMA_TO_DEVICE);

		tx_buf = &tx_ring->tx_buf[i];
	पूर्ण

	/* record bytecount क्रम BQL */
	netdev_tx_sent_queue(txring_txq(tx_ring), first->bytecount);

	/* record SW बारtamp अगर HW बारtamp is not available */
	skb_tx_बारtamp(first->skb);

	i++;
	अगर (i == tx_ring->count)
		i = 0;

	/* ग_लिखो last descriptor with RS and EOP bits */
	td_cmd |= (u64)ICE_TXD_LAST_DESC_CMD;
	tx_desc->cmd_type_offset_bsz =
			ice_build_ctob(td_cmd, td_offset, size, td_tag);

	/* Force memory ग_लिखोs to complete beक्रमe letting h/w know there
	 * are new descriptors to fetch.
	 *
	 * We also use this memory barrier to make certain all of the
	 * status bits have been updated beक्रमe next_to_watch is written.
	 */
	wmb();

	/* set next_to_watch value indicating a packet is present */
	first->next_to_watch = tx_desc;

	tx_ring->next_to_use = i;

	ice_maybe_stop_tx(tx_ring, DESC_NEEDED);

	/* notअगरy HW of packet */
	अगर (netअगर_xmit_stopped(txring_txq(tx_ring)) || !netdev_xmit_more())
		ग_लिखोl(i, tx_ring->tail);

	वापस;

dma_error:
	/* clear DMA mappings क्रम failed tx_buf map */
	क्रम (;;) अणु
		tx_buf = &tx_ring->tx_buf[i];
		ice_unmap_and_मुक्त_tx_buf(tx_ring, tx_buf);
		अगर (tx_buf == first)
			अवरोध;
		अगर (i == 0)
			i = tx_ring->count;
		i--;
	पूर्ण

	tx_ring->next_to_use = i;
पूर्ण

/**
 * ice_tx_csum - Enable Tx checksum offloads
 * @first: poपूर्णांकer to the first descriptor
 * @off: poपूर्णांकer to काष्ठा that holds offload parameters
 *
 * Returns 0 or error (negative) अगर checksum offload can't happen, 1 otherwise.
 */
अटल
पूर्णांक ice_tx_csum(काष्ठा ice_tx_buf *first, काष्ठा ice_tx_offload_params *off)
अणु
	u32 l4_len = 0, l3_len = 0, l2_len = 0;
	काष्ठा sk_buff *skb = first->skb;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	__be16 frag_off, protocol;
	अचिन्हित अक्षर *exthdr;
	u32 offset, cmd = 0;
	u8 l4_proto = 0;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* compute outer L2 header size */
	l2_len = ip.hdr - skb->data;
	offset = (l2_len / 2) << ICE_TX_DESC_LEN_MACLEN_S;

	protocol = vlan_get_protocol(skb);

	अगर (protocol == htons(ETH_P_IP))
		first->tx_flags |= ICE_TX_FLAGS_IPV4;
	अन्यथा अगर (protocol == htons(ETH_P_IPV6))
		first->tx_flags |= ICE_TX_FLAGS_IPV6;

	अगर (skb->encapsulation) अणु
		bool gso_ena = false;
		u32 tunnel = 0;

		/* define outer network header type */
		अगर (first->tx_flags & ICE_TX_FLAGS_IPV4) अणु
			tunnel |= (first->tx_flags & ICE_TX_FLAGS_TSO) ?
				  ICE_TX_CTX_EIPT_IPV4 :
				  ICE_TX_CTX_EIPT_IPV4_NO_CSUM;
			l4_proto = ip.v4->protocol;
		पूर्ण अन्यथा अगर (first->tx_flags & ICE_TX_FLAGS_IPV6) अणु
			पूर्णांक ret;

			tunnel |= ICE_TX_CTX_EIPT_IPV6;
			exthdr = ip.hdr + माप(*ip.v6);
			l4_proto = ip.v6->nexthdr;
			ret = ipv6_skip_exthdr(skb, exthdr - skb->data,
					       &l4_proto, &frag_off);
			अगर (ret < 0)
				वापस -1;
		पूर्ण

		/* define outer transport */
		चयन (l4_proto) अणु
		हाल IPPROTO_UDP:
			tunnel |= ICE_TXD_CTX_UDP_TUNNELING;
			first->tx_flags |= ICE_TX_FLAGS_TUNNEL;
			अवरोध;
		हाल IPPROTO_GRE:
			tunnel |= ICE_TXD_CTX_GRE_TUNNELING;
			first->tx_flags |= ICE_TX_FLAGS_TUNNEL;
			अवरोध;
		हाल IPPROTO_IPIP:
		हाल IPPROTO_IPV6:
			first->tx_flags |= ICE_TX_FLAGS_TUNNEL;
			l4.hdr = skb_inner_network_header(skb);
			अवरोध;
		शेष:
			अगर (first->tx_flags & ICE_TX_FLAGS_TSO)
				वापस -1;

			skb_checksum_help(skb);
			वापस 0;
		पूर्ण

		/* compute outer L3 header size */
		tunnel |= ((l4.hdr - ip.hdr) / 4) <<
			  ICE_TXD_CTX_QW0_EIPLEN_S;

		/* चयन IP header poपूर्णांकer from outer to inner header */
		ip.hdr = skb_inner_network_header(skb);

		/* compute tunnel header size */
		tunnel |= ((ip.hdr - l4.hdr) / 2) <<
			   ICE_TXD_CTX_QW0_NATLEN_S;

		gso_ena = skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL;
		/* indicate अगर we need to offload outer UDP header */
		अगर ((first->tx_flags & ICE_TX_FLAGS_TSO) && !gso_ena &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM))
			tunnel |= ICE_TXD_CTX_QW0_L4T_CS_M;

		/* record tunnel offload values */
		off->cd_tunnel_params |= tunnel;

		/* set DTYP=1 to indicate that it's an Tx context descriptor
		 * in IPsec tunnel mode with Tx offloads in Quad word 1
		 */
		off->cd_qw1 |= (u64)ICE_TX_DESC_DTYPE_CTX;

		/* चयन L4 header poपूर्णांकer from outer to inner */
		l4.hdr = skb_inner_transport_header(skb);
		l4_proto = 0;

		/* reset type as we transition from outer to inner headers */
		first->tx_flags &= ~(ICE_TX_FLAGS_IPV4 | ICE_TX_FLAGS_IPV6);
		अगर (ip.v4->version == 4)
			first->tx_flags |= ICE_TX_FLAGS_IPV4;
		अगर (ip.v6->version == 6)
			first->tx_flags |= ICE_TX_FLAGS_IPV6;
	पूर्ण

	/* Enable IP checksum offloads */
	अगर (first->tx_flags & ICE_TX_FLAGS_IPV4) अणु
		l4_proto = ip.v4->protocol;
		/* the stack computes the IP header alपढ़ोy, the only समय we
		 * need the hardware to recompute it is in the हाल of TSO.
		 */
		अगर (first->tx_flags & ICE_TX_FLAGS_TSO)
			cmd |= ICE_TX_DESC_CMD_IIPT_IPV4_CSUM;
		अन्यथा
			cmd |= ICE_TX_DESC_CMD_IIPT_IPV4;

	पूर्ण अन्यथा अगर (first->tx_flags & ICE_TX_FLAGS_IPV6) अणु
		cmd |= ICE_TX_DESC_CMD_IIPT_IPV6;
		exthdr = ip.hdr + माप(*ip.v6);
		l4_proto = ip.v6->nexthdr;
		अगर (l4.hdr != exthdr)
			ipv6_skip_exthdr(skb, exthdr - skb->data, &l4_proto,
					 &frag_off);
	पूर्ण अन्यथा अणु
		वापस -1;
	पूर्ण

	/* compute inner L3 header size */
	l3_len = l4.hdr - ip.hdr;
	offset |= (l3_len / 4) << ICE_TX_DESC_LEN_IPLEN_S;

	/* Enable L4 checksum offloads */
	चयन (l4_proto) अणु
	हाल IPPROTO_TCP:
		/* enable checksum offloads */
		cmd |= ICE_TX_DESC_CMD_L4T_खातापूर्णT_TCP;
		l4_len = l4.tcp->करोff;
		offset |= l4_len << ICE_TX_DESC_LEN_L4_LEN_S;
		अवरोध;
	हाल IPPROTO_UDP:
		/* enable UDP checksum offload */
		cmd |= ICE_TX_DESC_CMD_L4T_खातापूर्णT_UDP;
		l4_len = (माप(काष्ठा udphdr) >> 2);
		offset |= l4_len << ICE_TX_DESC_LEN_L4_LEN_S;
		अवरोध;
	हाल IPPROTO_SCTP:
		/* enable SCTP checksum offload */
		cmd |= ICE_TX_DESC_CMD_L4T_खातापूर्णT_SCTP;
		l4_len = माप(काष्ठा sctphdr) >> 2;
		offset |= l4_len << ICE_TX_DESC_LEN_L4_LEN_S;
		अवरोध;

	शेष:
		अगर (first->tx_flags & ICE_TX_FLAGS_TSO)
			वापस -1;
		skb_checksum_help(skb);
		वापस 0;
	पूर्ण

	off->td_cmd |= cmd;
	off->td_offset |= offset;
	वापस 1;
पूर्ण

/**
 * ice_tx_prepare_vlan_flags - prepare generic Tx VLAN tagging flags क्रम HW
 * @tx_ring: ring to send buffer on
 * @first: poपूर्णांकer to काष्ठा ice_tx_buf
 *
 * Checks the skb and set up correspondingly several generic transmit flags
 * related to VLAN tagging क्रम the HW, such as VLAN, DCB, etc.
 */
अटल व्योम
ice_tx_prepare_vlan_flags(काष्ठा ice_ring *tx_ring, काष्ठा ice_tx_buf *first)
अणु
	काष्ठा sk_buff *skb = first->skb;

	/* nothing left to करो, software offloaded VLAN */
	अगर (!skb_vlan_tag_present(skb) && eth_type_vlan(skb->protocol))
		वापस;

	/* currently, we always assume 802.1Q क्रम VLAN insertion as VLAN
	 * insertion क्रम 802.1AD is not supported
	 */
	अगर (skb_vlan_tag_present(skb)) अणु
		first->tx_flags |= skb_vlan_tag_get(skb) << ICE_TX_FLAGS_VLAN_S;
		first->tx_flags |= ICE_TX_FLAGS_HW_VLAN;
	पूर्ण

	ice_tx_prepare_vlan_flags_dcb(tx_ring, first);
पूर्ण

/**
 * ice_tso - computes mss and TSO length to prepare क्रम TSO
 * @first: poपूर्णांकer to काष्ठा ice_tx_buf
 * @off: poपूर्णांकer to काष्ठा that holds offload parameters
 *
 * Returns 0 or error (negative) अगर TSO can't happen, 1 otherwise.
 */
अटल
पूर्णांक ice_tso(काष्ठा ice_tx_buf *first, काष्ठा ice_tx_offload_params *off)
अणु
	काष्ठा sk_buff *skb = first->skb;
	जोड़ अणु
		काष्ठा iphdr *v4;
		काष्ठा ipv6hdr *v6;
		अचिन्हित अक्षर *hdr;
	पूर्ण ip;
	जोड़ अणु
		काष्ठा tcphdr *tcp;
		काष्ठा udphdr *udp;
		अचिन्हित अक्षर *hdr;
	पूर्ण l4;
	u64 cd_mss, cd_tso_len;
	u32 paylen;
	u8 l4_start;
	पूर्णांक err;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	अगर (!skb_is_gso(skb))
		वापस 0;

	err = skb_cow_head(skb, 0);
	अगर (err < 0)
		वापस err;

	/* cppcheck-suppress unपढ़ोVariable */
	ip.hdr = skb_network_header(skb);
	l4.hdr = skb_transport_header(skb);

	/* initialize outer IP header fields */
	अगर (ip.v4->version == 4) अणु
		ip.v4->tot_len = 0;
		ip.v4->check = 0;
	पूर्ण अन्यथा अणु
		ip.v6->payload_len = 0;
	पूर्ण

	अगर (skb_shinfo(skb)->gso_type & (SKB_GSO_GRE |
					 SKB_GSO_GRE_CSUM |
					 SKB_GSO_IPXIP4 |
					 SKB_GSO_IPXIP6 |
					 SKB_GSO_UDP_TUNNEL |
					 SKB_GSO_UDP_TUNNEL_CSUM)) अणु
		अगर (!(skb_shinfo(skb)->gso_type & SKB_GSO_PARTIAL) &&
		    (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_TUNNEL_CSUM)) अणु
			l4.udp->len = 0;

			/* determine offset of outer transport header */
			l4_start = (u8)(l4.hdr - skb->data);

			/* हटाओ payload length from outer checksum */
			paylen = skb->len - l4_start;
			csum_replace_by_dअगरf(&l4.udp->check,
					     (__क्रमce __wsum)htonl(paylen));
		पूर्ण

		/* reset poपूर्णांकers to inner headers */

		/* cppcheck-suppress unपढ़ोVariable */
		ip.hdr = skb_inner_network_header(skb);
		l4.hdr = skb_inner_transport_header(skb);

		/* initialize inner IP header fields */
		अगर (ip.v4->version == 4) अणु
			ip.v4->tot_len = 0;
			ip.v4->check = 0;
		पूर्ण अन्यथा अणु
			ip.v6->payload_len = 0;
		पूर्ण
	पूर्ण

	/* determine offset of transport header */
	l4_start = (u8)(l4.hdr - skb->data);

	/* हटाओ payload length from checksum */
	paylen = skb->len - l4_start;

	अगर (skb_shinfo(skb)->gso_type & SKB_GSO_UDP_L4) अणु
		csum_replace_by_dअगरf(&l4.udp->check,
				     (__क्रमce __wsum)htonl(paylen));
		/* compute length of UDP segmentation header */
		off->header_len = (u8)माप(l4.udp) + l4_start;
	पूर्ण अन्यथा अणु
		csum_replace_by_dअगरf(&l4.tcp->check,
				     (__क्रमce __wsum)htonl(paylen));
		/* compute length of TCP segmentation header */
		off->header_len = (u8)((l4.tcp->करोff * 4) + l4_start);
	पूर्ण

	/* update gso_segs and bytecount */
	first->gso_segs = skb_shinfo(skb)->gso_segs;
	first->bytecount += (first->gso_segs - 1) * off->header_len;

	cd_tso_len = skb->len - off->header_len;
	cd_mss = skb_shinfo(skb)->gso_size;

	/* record cdesc_qw1 with TSO parameters */
	off->cd_qw1 |= (u64)(ICE_TX_DESC_DTYPE_CTX |
			     (ICE_TX_CTX_DESC_TSO << ICE_TXD_CTX_QW1_CMD_S) |
			     (cd_tso_len << ICE_TXD_CTX_QW1_TSO_LEN_S) |
			     (cd_mss << ICE_TXD_CTX_QW1_MSS_S));
	first->tx_flags |= ICE_TX_FLAGS_TSO;
	वापस 1;
पूर्ण

/**
 * ice_txd_use_count  - estimate the number of descriptors needed क्रम Tx
 * @size: transmit request size in bytes
 *
 * Due to hardware alignment restrictions (4K alignment), we need to
 * assume that we can have no more than 12K of data per descriptor, even
 * though each descriptor can take up to 16K - 1 bytes of aligned memory.
 * Thus, we need to भागide by 12K. But भागision is slow! Instead,
 * we decompose the operation पूर्णांकo shअगरts and one relatively cheap
 * multiply operation.
 *
 * To भागide by 12K, we first भागide by 4K, then भागide by 3:
 *     To भागide by 4K, shअगरt right by 12 bits
 *     To भागide by 3, multiply by 85, then भागide by 256
 *     (Divide by 256 is करोne by shअगरting right by 8 bits)
 * Finally, we add one to round up. Because 256 isn't an exact multiple of
 * 3, we'll underestimate near each multiple of 12K. This is actually more
 * accurate as we have 4K - 1 of wiggle room that we can fit पूर्णांकo the last
 * segment. For our purposes this is accurate out to 1M which is orders of
 * magnitude greater than our largest possible GSO size.
 *
 * This would then be implemented as:
 *     वापस (((size >> 12) * 85) >> 8) + ICE_DESCS_FOR_SKB_DATA_PTR;
 *
 * Since multiplication and भागision are commutative, we can reorder
 * operations पूर्णांकo:
 *     वापस ((size * 85) >> 20) + ICE_DESCS_FOR_SKB_DATA_PTR;
 */
अटल अचिन्हित पूर्णांक ice_txd_use_count(अचिन्हित पूर्णांक size)
अणु
	वापस ((size * 85) >> 20) + ICE_DESCS_FOR_SKB_DATA_PTR;
पूर्ण

/**
 * ice_xmit_desc_count - calculate number of Tx descriptors needed
 * @skb: send buffer
 *
 * Returns number of data descriptors needed क्रम this skb.
 */
अटल अचिन्हित पूर्णांक ice_xmit_desc_count(काष्ठा sk_buff *skb)
अणु
	स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[0];
	अचिन्हित पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	अचिन्हित पूर्णांक count = 0, size = skb_headlen(skb);

	क्रम (;;) अणु
		count += ice_txd_use_count(size);

		अगर (!nr_frags--)
			अवरोध;

		size = skb_frag_size(frag++);
	पूर्ण

	वापस count;
पूर्ण

/**
 * __ice_chk_linearize - Check अगर there are more than 8 buffers per packet
 * @skb: send buffer
 *
 * Note: This HW can't DMA more than 8 buffers to build a packet on the wire
 * and so we need to figure out the हालs where we need to linearize the skb.
 *
 * For TSO we need to count the TSO header and segment payload separately.
 * As such we need to check हालs where we have 7 fragments or more as we
 * can potentially require 9 DMA transactions, 1 क्रम the TSO header, 1 क्रम
 * the segment payload in the first descriptor, and another 7 क्रम the
 * fragments.
 */
अटल bool __ice_chk_linearize(काष्ठा sk_buff *skb)
अणु
	स्थिर skb_frag_t *frag, *stale;
	पूर्णांक nr_frags, sum;

	/* no need to check अगर number of frags is less than 7 */
	nr_frags = skb_shinfo(skb)->nr_frags;
	अगर (nr_frags < (ICE_MAX_BUF_TXD - 1))
		वापस false;

	/* We need to walk through the list and validate that each group
	 * of 6 fragments totals at least gso_size.
	 */
	nr_frags -= ICE_MAX_BUF_TXD - 2;
	frag = &skb_shinfo(skb)->frags[0];

	/* Initialize size to the negative value of gso_size minus 1. We
	 * use this as the worst हाल scenario in which the frag ahead
	 * of us only provides one byte which is why we are limited to 6
	 * descriptors क्रम a single transmit as the header and previous
	 * fragment are alपढ़ोy consuming 2 descriptors.
	 */
	sum = 1 - skb_shinfo(skb)->gso_size;

	/* Add size of frags 0 through 4 to create our initial sum */
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);
	sum += skb_frag_size(frag++);

	/* Walk through fragments adding latest fragment, testing it, and
	 * then removing stale fragments from the sum.
	 */
	क्रम (stale = &skb_shinfo(skb)->frags[0];; stale++) अणु
		पूर्णांक stale_size = skb_frag_size(stale);

		sum += skb_frag_size(frag++);

		/* The stale fragment may present us with a smaller
		 * descriptor than the actual fragment size. To account
		 * क्रम that we need to हटाओ all the data on the front and
		 * figure out what the reमुख्यder would be in the last
		 * descriptor associated with the fragment.
		 */
		अगर (stale_size > ICE_MAX_DATA_PER_TXD) अणु
			पूर्णांक align_pad = -(skb_frag_off(stale)) &
					(ICE_MAX_READ_REQ_SIZE - 1);

			sum -= align_pad;
			stale_size -= align_pad;

			करो अणु
				sum -= ICE_MAX_DATA_PER_TXD_ALIGNED;
				stale_size -= ICE_MAX_DATA_PER_TXD_ALIGNED;
			पूर्ण जबतक (stale_size > ICE_MAX_DATA_PER_TXD);
		पूर्ण

		/* अगर sum is negative we failed to make sufficient progress */
		अगर (sum < 0)
			वापस true;

		अगर (!nr_frags--)
			अवरोध;

		sum -= stale_size;
	पूर्ण

	वापस false;
पूर्ण

/**
 * ice_chk_linearize - Check अगर there are more than 8 fragments per packet
 * @skb:      send buffer
 * @count:    number of buffers used
 *
 * Note: Our HW can't scatter-gather more than 8 fragments to build
 * a packet on the wire and so we need to figure out the हालs where we
 * need to linearize the skb.
 */
अटल bool ice_chk_linearize(काष्ठा sk_buff *skb, अचिन्हित पूर्णांक count)
अणु
	/* Both TSO and single send will work अगर count is less than 8 */
	अगर (likely(count < ICE_MAX_BUF_TXD))
		वापस false;

	अगर (skb_is_gso(skb))
		वापस __ice_chk_linearize(skb);

	/* we can support up to 8 data buffers क्रम a single send */
	वापस count != ICE_MAX_BUF_TXD;
पूर्ण

/**
 * ice_xmit_frame_ring - Sends buffer on Tx ring
 * @skb: send buffer
 * @tx_ring: ring to send buffer on
 *
 * Returns NETDEV_TX_OK अगर sent, अन्यथा an error code
 */
अटल netdev_tx_t
ice_xmit_frame_ring(काष्ठा sk_buff *skb, काष्ठा ice_ring *tx_ring)
अणु
	काष्ठा ice_tx_offload_params offload = अणु 0 पूर्ण;
	काष्ठा ice_vsi *vsi = tx_ring->vsi;
	काष्ठा ice_tx_buf *first;
	काष्ठा ethhdr *eth;
	अचिन्हित पूर्णांक count;
	पूर्णांक tso, csum;

	count = ice_xmit_desc_count(skb);
	अगर (ice_chk_linearize(skb, count)) अणु
		अगर (__skb_linearize(skb))
			जाओ out_drop;
		count = ice_txd_use_count(skb->len);
		tx_ring->tx_stats.tx_linearize++;
	पूर्ण

	/* need: 1 descriptor per page * PAGE_SIZE/ICE_MAX_DATA_PER_TXD,
	 *       + 1 desc क्रम skb_head_len/ICE_MAX_DATA_PER_TXD,
	 *       + 4 desc gap to aव्योम the cache line where head is,
	 *       + 1 desc क्रम context descriptor,
	 * otherwise try next समय
	 */
	अगर (ice_maybe_stop_tx(tx_ring, count + ICE_DESCS_PER_CACHE_LINE +
			      ICE_DESCS_FOR_CTX_DESC)) अणु
		tx_ring->tx_stats.tx_busy++;
		वापस NETDEV_TX_BUSY;
	पूर्ण

	offload.tx_ring = tx_ring;

	/* record the location of the first descriptor क्रम this packet */
	first = &tx_ring->tx_buf[tx_ring->next_to_use];
	first->skb = skb;
	first->bytecount = max_t(अचिन्हित पूर्णांक, skb->len, ETH_ZLEN);
	first->gso_segs = 1;
	first->tx_flags = 0;

	/* prepare the VLAN tagging flags क्रम Tx */
	ice_tx_prepare_vlan_flags(tx_ring, first);

	/* set up TSO offload */
	tso = ice_tso(first, &offload);
	अगर (tso < 0)
		जाओ out_drop;

	/* always set up Tx checksum offload */
	csum = ice_tx_csum(first, &offload);
	अगर (csum < 0)
		जाओ out_drop;

	/* allow CONTROL frames egress from मुख्य VSI अगर FW LLDP disabled */
	eth = (काष्ठा ethhdr *)skb_mac_header(skb);
	अगर (unlikely((skb->priority == TC_PRIO_CONTROL ||
		      eth->h_proto == htons(ETH_P_LLDP)) &&
		     vsi->type == ICE_VSI_PF &&
		     vsi->port_info->qos_cfg.is_sw_lldp))
		offload.cd_qw1 |= (u64)(ICE_TX_DESC_DTYPE_CTX |
					ICE_TX_CTX_DESC_SWTCH_UPLINK <<
					ICE_TXD_CTX_QW1_CMD_S);

	अगर (offload.cd_qw1 & ICE_TX_DESC_DTYPE_CTX) अणु
		काष्ठा ice_tx_ctx_desc *cdesc;
		u16 i = tx_ring->next_to_use;

		/* grab the next descriptor */
		cdesc = ICE_TX_CTX_DESC(tx_ring, i);
		i++;
		tx_ring->next_to_use = (i < tx_ring->count) ? i : 0;

		/* setup context descriptor */
		cdesc->tunneling_params = cpu_to_le32(offload.cd_tunnel_params);
		cdesc->l2tag2 = cpu_to_le16(offload.cd_l2tag2);
		cdesc->rsvd = cpu_to_le16(0);
		cdesc->qw1 = cpu_to_le64(offload.cd_qw1);
	पूर्ण

	ice_tx_map(tx_ring, first, &offload);
	वापस NETDEV_TX_OK;

out_drop:
	dev_kमुक्त_skb_any(skb);
	वापस NETDEV_TX_OK;
पूर्ण

/**
 * ice_start_xmit - Selects the correct VSI and Tx queue to send buffer
 * @skb: send buffer
 * @netdev: network पूर्णांकerface device काष्ठाure
 *
 * Returns NETDEV_TX_OK अगर sent, अन्यथा an error code
 */
netdev_tx_t ice_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *netdev)
अणु
	काष्ठा ice_netdev_priv *np = netdev_priv(netdev);
	काष्ठा ice_vsi *vsi = np->vsi;
	काष्ठा ice_ring *tx_ring;

	tx_ring = vsi->tx_rings[skb->queue_mapping];

	/* hardware can't handle really लघु frames, hardware padding works
	 * beyond this poपूर्णांक
	 */
	अगर (skb_put_padto(skb, ICE_MIN_TX_LEN))
		वापस NETDEV_TX_OK;

	वापस ice_xmit_frame_ring(skb, tx_ring);
पूर्ण

/**
 * ice_clean_ctrl_tx_irq - पूर्णांकerrupt handler क्रम flow director Tx queue
 * @tx_ring: tx_ring to clean
 */
व्योम ice_clean_ctrl_tx_irq(काष्ठा ice_ring *tx_ring)
अणु
	काष्ठा ice_vsi *vsi = tx_ring->vsi;
	s16 i = tx_ring->next_to_clean;
	पूर्णांक budget = ICE_DFLT_IRQ_WORK;
	काष्ठा ice_tx_desc *tx_desc;
	काष्ठा ice_tx_buf *tx_buf;

	tx_buf = &tx_ring->tx_buf[i];
	tx_desc = ICE_TX_DESC(tx_ring, i);
	i -= tx_ring->count;

	करो अणु
		काष्ठा ice_tx_desc *eop_desc = tx_buf->next_to_watch;

		/* अगर next_to_watch is not set then there is no pending work */
		अगर (!eop_desc)
			अवरोध;

		/* prevent any other पढ़ोs prior to eop_desc */
		smp_rmb();

		/* अगर the descriptor isn't करोne, no work to करो */
		अगर (!(eop_desc->cmd_type_offset_bsz &
		      cpu_to_le64(ICE_TX_DESC_DTYPE_DESC_DONE)))
			अवरोध;

		/* clear next_to_watch to prevent false hangs */
		tx_buf->next_to_watch = शून्य;
		tx_desc->buf_addr = 0;
		tx_desc->cmd_type_offset_bsz = 0;

		/* move past filter desc */
		tx_buf++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_buf;
			tx_desc = ICE_TX_DESC(tx_ring, 0);
		पूर्ण

		/* unmap the data header */
		अगर (dma_unmap_len(tx_buf, len))
			dma_unmap_single(tx_ring->dev,
					 dma_unmap_addr(tx_buf, dma),
					 dma_unmap_len(tx_buf, len),
					 DMA_TO_DEVICE);
		अगर (tx_buf->tx_flags & ICE_TX_FLAGS_DUMMY_PKT)
			devm_kमुक्त(tx_ring->dev, tx_buf->raw_buf);

		/* clear next_to_watch to prevent false hangs */
		tx_buf->raw_buf = शून्य;
		tx_buf->tx_flags = 0;
		tx_buf->next_to_watch = शून्य;
		dma_unmap_len_set(tx_buf, len, 0);
		tx_desc->buf_addr = 0;
		tx_desc->cmd_type_offset_bsz = 0;

		/* move past eop_desc क्रम start of next FD desc */
		tx_buf++;
		tx_desc++;
		i++;
		अगर (unlikely(!i)) अणु
			i -= tx_ring->count;
			tx_buf = tx_ring->tx_buf;
			tx_desc = ICE_TX_DESC(tx_ring, 0);
		पूर्ण

		budget--;
	पूर्ण जबतक (likely(budget));

	i += tx_ring->count;
	tx_ring->next_to_clean = i;

	/* re-enable पूर्णांकerrupt अगर needed */
	ice_irq_dynamic_ena(&vsi->back->hw, vsi, vsi->q_vectors[0]);
पूर्ण
