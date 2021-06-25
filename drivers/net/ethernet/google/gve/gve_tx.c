<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR MIT)
/* Google भव Ethernet (gve) driver
 *
 * Copyright (C) 2015-2019 Google, Inc.
 */

#समावेश "gve.h"
#समावेश "gve_adminq.h"
#समावेश <linux/ip.h>
#समावेश <linux/tcp.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/skbuff.h>

अटल अंतरभूत व्योम gve_tx_put_करोorbell(काष्ठा gve_priv *priv,
				       काष्ठा gve_queue_resources *q_resources,
				       u32 val)
अणु
	ioग_लिखो32be(val, &priv->db_bar2[be32_to_cpu(q_resources->db_index)]);
पूर्ण

/* gvnic can only transmit from a Registered Segment.
 * We copy skb payloads पूर्णांकo the रेजिस्टरed segment beक्रमe writing Tx
 * descriptors and ringing the Tx करोorbell.
 *
 * gve_tx_fअगरo_* manages the Registered Segment as a FIFO - clients must
 * मुक्त allocations in the order they were allocated.
 */

अटल पूर्णांक gve_tx_fअगरo_init(काष्ठा gve_priv *priv, काष्ठा gve_tx_fअगरo *fअगरo)
अणु
	fअगरo->base = vmap(fअगरo->qpl->pages, fअगरo->qpl->num_entries, VM_MAP,
			  PAGE_KERNEL);
	अगर (unlikely(!fअगरo->base)) अणु
		netअगर_err(priv, drv, priv->dev, "Failed to vmap fifo, qpl_id = %d\n",
			  fअगरo->qpl->id);
		वापस -ENOMEM;
	पूर्ण

	fअगरo->size = fअगरo->qpl->num_entries * PAGE_SIZE;
	atomic_set(&fअगरo->available, fअगरo->size);
	fअगरo->head = 0;
	वापस 0;
पूर्ण

अटल व्योम gve_tx_fअगरo_release(काष्ठा gve_priv *priv, काष्ठा gve_tx_fअगरo *fअगरo)
अणु
	WARN(atomic_पढ़ो(&fअगरo->available) != fअगरo->size,
	     "Releasing non-empty fifo");

	vunmap(fअगरo->base);
पूर्ण

अटल पूर्णांक gve_tx_fअगरo_pad_alloc_one_frag(काष्ठा gve_tx_fअगरo *fअगरo,
					  माप_प्रकार bytes)
अणु
	वापस (fअगरo->head + bytes < fअगरo->size) ? 0 : fअगरo->size - fअगरo->head;
पूर्ण

अटल bool gve_tx_fअगरo_can_alloc(काष्ठा gve_tx_fअगरo *fअगरo, माप_प्रकार bytes)
अणु
	वापस (atomic_पढ़ो(&fअगरo->available) <= bytes) ? false : true;
पूर्ण

/* gve_tx_alloc_fअगरo - Allocate fragment(s) from Tx FIFO
 * @fअगरo: FIFO to allocate from
 * @bytes: Allocation size
 * @iov: Scatter-gather elements to fill with allocation fragment base/len
 *
 * Returns number of valid elements in iov[] or negative on error.
 *
 * Allocations from a given FIFO must be बाह्यally synchronized but concurrent
 * allocation and मुक्तs are allowed.
 */
अटल पूर्णांक gve_tx_alloc_fअगरo(काष्ठा gve_tx_fअगरo *fअगरo, माप_प्रकार bytes,
			     काष्ठा gve_tx_iovec iov[2])
अणु
	माप_प्रकार overflow, padding;
	u32 aligned_head;
	पूर्णांक nfrags = 0;

	अगर (!bytes)
		वापस 0;

	/* This check happens beक्रमe we know how much padding is needed to
	 * align to a cacheline boundary क्रम the payload, but that is fine,
	 * because the FIFO head always start aligned, and the FIFO's boundaries
	 * are aligned, so अगर there is space क्रम the data, there is space क्रम
	 * the padding to the next alignment.
	 */
	WARN(!gve_tx_fअगरo_can_alloc(fअगरo, bytes),
	     "Reached %s when there's not enough space in the fifo", __func__);

	nfrags++;

	iov[0].iov_offset = fअगरo->head;
	iov[0].iov_len = bytes;
	fअगरo->head += bytes;

	अगर (fअगरo->head > fअगरo->size) अणु
		/* If the allocation did not fit in the tail fragment of the
		 * FIFO, also use the head fragment.
		 */
		nfrags++;
		overflow = fअगरo->head - fअगरo->size;
		iov[0].iov_len -= overflow;
		iov[1].iov_offset = 0;	/* Start of fअगरo*/
		iov[1].iov_len = overflow;

		fअगरo->head = overflow;
	पूर्ण

	/* Re-align to a cacheline boundary */
	aligned_head = L1_CACHE_ALIGN(fअगरo->head);
	padding = aligned_head - fअगरo->head;
	iov[nfrags - 1].iov_padding = padding;
	atomic_sub(bytes + padding, &fअगरo->available);
	fअगरo->head = aligned_head;

	अगर (fअगरo->head == fअगरo->size)
		fअगरo->head = 0;

	वापस nfrags;
पूर्ण

/* gve_tx_मुक्त_fअगरo - Return space to Tx FIFO
 * @fअगरo: FIFO to वापस fragments to
 * @bytes: Bytes to मुक्त
 */
अटल व्योम gve_tx_मुक्त_fअगरo(काष्ठा gve_tx_fअगरo *fअगरo, माप_प्रकार bytes)
अणु
	atomic_add(bytes, &fअगरo->available);
पूर्ण

अटल व्योम gve_tx_हटाओ_from_block(काष्ठा gve_priv *priv, पूर्णांक queue_idx)
अणु
	काष्ठा gve_notअगरy_block *block =
			&priv->ntfy_blocks[gve_tx_idx_to_ntfy(priv, queue_idx)];

	block->tx = शून्य;
पूर्ण

अटल पूर्णांक gve_clean_tx_करोne(काष्ठा gve_priv *priv, काष्ठा gve_tx_ring *tx,
			     u32 to_करो, bool try_to_wake);

अटल व्योम gve_tx_मुक्त_ring(काष्ठा gve_priv *priv, पूर्णांक idx)
अणु
	काष्ठा gve_tx_ring *tx = &priv->tx[idx];
	काष्ठा device *hdev = &priv->pdev->dev;
	माप_प्रकार bytes;
	u32 slots;

	gve_tx_हटाओ_from_block(priv, idx);
	slots = tx->mask + 1;
	gve_clean_tx_करोne(priv, tx, tx->req, false);
	netdev_tx_reset_queue(tx->netdev_txq);

	dma_मुक्त_coherent(hdev, माप(*tx->q_resources),
			  tx->q_resources, tx->q_resources_bus);
	tx->q_resources = शून्य;

	अगर (!tx->raw_addressing) अणु
		gve_tx_fअगरo_release(priv, &tx->tx_fअगरo);
		gve_unassign_qpl(priv, tx->tx_fअगरo.qpl->id);
		tx->tx_fअगरo.qpl = शून्य;
	पूर्ण

	bytes = माप(*tx->desc) * slots;
	dma_मुक्त_coherent(hdev, bytes, tx->desc, tx->bus);
	tx->desc = शून्य;

	vमुक्त(tx->info);
	tx->info = शून्य;

	netअगर_dbg(priv, drv, priv->dev, "freed tx queue %d\n", idx);
पूर्ण

अटल व्योम gve_tx_add_to_block(काष्ठा gve_priv *priv, पूर्णांक queue_idx)
अणु
	पूर्णांक ntfy_idx = gve_tx_idx_to_ntfy(priv, queue_idx);
	काष्ठा gve_notअगरy_block *block = &priv->ntfy_blocks[ntfy_idx];
	काष्ठा gve_tx_ring *tx = &priv->tx[queue_idx];

	block->tx = tx;
	tx->ntfy_id = ntfy_idx;
पूर्ण

अटल पूर्णांक gve_tx_alloc_ring(काष्ठा gve_priv *priv, पूर्णांक idx)
अणु
	काष्ठा gve_tx_ring *tx = &priv->tx[idx];
	काष्ठा device *hdev = &priv->pdev->dev;
	u32 slots = priv->tx_desc_cnt;
	माप_प्रकार bytes;

	/* Make sure everything is zeroed to start */
	स_रखो(tx, 0, माप(*tx));
	tx->q_num = idx;

	tx->mask = slots - 1;

	/* alloc metadata */
	tx->info = vzalloc(माप(*tx->info) * slots);
	अगर (!tx->info)
		वापस -ENOMEM;

	/* alloc tx queue */
	bytes = माप(*tx->desc) * slots;
	tx->desc = dma_alloc_coherent(hdev, bytes, &tx->bus, GFP_KERNEL);
	अगर (!tx->desc)
		जाओ पात_with_info;

	tx->raw_addressing = priv->raw_addressing;
	tx->dev = &priv->pdev->dev;
	अगर (!tx->raw_addressing) अणु
		tx->tx_fअगरo.qpl = gve_assign_tx_qpl(priv);
		अगर (!tx->tx_fअगरo.qpl)
			जाओ पात_with_desc;
		/* map Tx FIFO */
		अगर (gve_tx_fअगरo_init(priv, &tx->tx_fअगरo))
			जाओ पात_with_qpl;
	पूर्ण

	tx->q_resources =
		dma_alloc_coherent(hdev,
				   माप(*tx->q_resources),
				   &tx->q_resources_bus,
				   GFP_KERNEL);
	अगर (!tx->q_resources)
		जाओ पात_with_fअगरo;

	netअगर_dbg(priv, drv, priv->dev, "tx[%d]->bus=%lx\n", idx,
		  (अचिन्हित दीर्घ)tx->bus);
	tx->netdev_txq = netdev_get_tx_queue(priv->dev, idx);
	gve_tx_add_to_block(priv, idx);

	वापस 0;

पात_with_fअगरo:
	अगर (!tx->raw_addressing)
		gve_tx_fअगरo_release(priv, &tx->tx_fअगरo);
पात_with_qpl:
	अगर (!tx->raw_addressing)
		gve_unassign_qpl(priv, tx->tx_fअगरo.qpl->id);
पात_with_desc:
	dma_मुक्त_coherent(hdev, bytes, tx->desc, tx->bus);
	tx->desc = शून्य;
पात_with_info:
	vमुक्त(tx->info);
	tx->info = शून्य;
	वापस -ENOMEM;
पूर्ण

पूर्णांक gve_tx_alloc_rings(काष्ठा gve_priv *priv)
अणु
	पूर्णांक err = 0;
	पूर्णांक i;

	क्रम (i = 0; i < priv->tx_cfg.num_queues; i++) अणु
		err = gve_tx_alloc_ring(priv, i);
		अगर (err) अणु
			netअगर_err(priv, drv, priv->dev,
				  "Failed to alloc tx ring=%d: err=%d\n",
				  i, err);
			अवरोध;
		पूर्ण
	पूर्ण
	/* Unallocate अगर there was an error */
	अगर (err) अणु
		पूर्णांक j;

		क्रम (j = 0; j < i; j++)
			gve_tx_मुक्त_ring(priv, j);
	पूर्ण
	वापस err;
पूर्ण

व्योम gve_tx_मुक्त_rings(काष्ठा gve_priv *priv)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < priv->tx_cfg.num_queues; i++)
		gve_tx_मुक्त_ring(priv, i);
पूर्ण

/* gve_tx_avail - Calculates the number of slots available in the ring
 * @tx: tx ring to check
 *
 * Returns the number of slots available
 *
 * The capacity of the queue is mask + 1. We करोn't need to reserve an entry.
 **/
अटल अंतरभूत u32 gve_tx_avail(काष्ठा gve_tx_ring *tx)
अणु
	वापस tx->mask + 1 - (tx->req - tx->करोne);
पूर्ण

अटल अंतरभूत पूर्णांक gve_skb_fअगरo_bytes_required(काष्ठा gve_tx_ring *tx,
					      काष्ठा sk_buff *skb)
अणु
	पूर्णांक pad_bytes, align_hdr_pad;
	पूर्णांक bytes;
	पूर्णांक hlen;

	hlen = skb_is_gso(skb) ? skb_checksum_start_offset(skb) +
				 tcp_hdrlen(skb) : skb_headlen(skb);

	pad_bytes = gve_tx_fअगरo_pad_alloc_one_frag(&tx->tx_fअगरo,
						   hlen);
	/* We need to take पूर्णांकo account the header alignment padding. */
	align_hdr_pad = L1_CACHE_ALIGN(hlen) - hlen;
	bytes = align_hdr_pad + pad_bytes + skb->len;

	वापस bytes;
पूर्ण

/* The most descriptors we could need is MAX_SKB_FRAGS + 3 : 1 क्रम each skb frag,
 * +1 क्रम the skb linear portion, +1 क्रम when tcp hdr needs to be in separate descriptor,
 * and +1 अगर the payload wraps to the beginning of the FIFO.
 */
#घोषणा MAX_TX_DESC_NEEDED	(MAX_SKB_FRAGS + 3)
अटल व्योम gve_tx_unmap_buf(काष्ठा device *dev, काष्ठा gve_tx_buffer_state *info)
अणु
	अगर (info->skb) अणु
		dma_unmap_single(dev, dma_unmap_addr(&info->buf, dma),
				 dma_unmap_len(&info->buf, len),
				 DMA_TO_DEVICE);
		dma_unmap_len_set(&info->buf, len, 0);
	पूर्ण अन्यथा अणु
		dma_unmap_page(dev, dma_unmap_addr(&info->buf, dma),
			       dma_unmap_len(&info->buf, len),
			       DMA_TO_DEVICE);
		dma_unmap_len_set(&info->buf, len, 0);
	पूर्ण
पूर्ण

/* Check अगर sufficient resources (descriptor ring space, FIFO space) are
 * available to transmit the given number of bytes.
 */
अटल अंतरभूत bool gve_can_tx(काष्ठा gve_tx_ring *tx, पूर्णांक bytes_required)
अणु
	bool can_alloc = true;

	अगर (!tx->raw_addressing)
		can_alloc = gve_tx_fअगरo_can_alloc(&tx->tx_fअगरo, bytes_required);

	वापस (gve_tx_avail(tx) >= MAX_TX_DESC_NEEDED && can_alloc);
पूर्ण

/* Stops the queue अगर the skb cannot be transmitted. */
अटल पूर्णांक gve_maybe_stop_tx(काष्ठा gve_tx_ring *tx, काष्ठा sk_buff *skb)
अणु
	पूर्णांक bytes_required = 0;

	अगर (!tx->raw_addressing)
		bytes_required = gve_skb_fअगरo_bytes_required(tx, skb);

	अगर (likely(gve_can_tx(tx, bytes_required)))
		वापस 0;

	/* No space, so stop the queue */
	tx->stop_queue++;
	netअगर_tx_stop_queue(tx->netdev_txq);
	smp_mb();	/* sync with restarting queue in gve_clean_tx_करोne() */

	/* Now check क्रम resources again, in हाल gve_clean_tx_करोne() मुक्तd
	 * resources after we checked and we stopped the queue after
	 * gve_clean_tx_करोne() checked.
	 *
	 * gve_maybe_stop_tx()			gve_clean_tx_करोne()
	 *   nsegs/can_alloc test failed
	 *					  gve_tx_मुक्त_fअगरo()
	 *					  अगर (tx queue stopped)
	 *					    netअगर_tx_queue_wake()
	 *   netअगर_tx_stop_queue()
	 *   Need to check again क्रम space here!
	 */
	अगर (likely(!gve_can_tx(tx, bytes_required)))
		वापस -EBUSY;

	netअगर_tx_start_queue(tx->netdev_txq);
	tx->wake_queue++;
	वापस 0;
पूर्ण

अटल व्योम gve_tx_fill_pkt_desc(जोड़ gve_tx_desc *pkt_desc,
				 काष्ठा sk_buff *skb, bool is_gso,
				 पूर्णांक l4_hdr_offset, u32 desc_cnt,
				 u16 hlen, u64 addr)
अणु
	/* l4_hdr_offset and csum_offset are in units of 16-bit words */
	अगर (is_gso) अणु
		pkt_desc->pkt.type_flags = GVE_TXD_TSO | GVE_TXF_L4CSUM;
		pkt_desc->pkt.l4_csum_offset = skb->csum_offset >> 1;
		pkt_desc->pkt.l4_hdr_offset = l4_hdr_offset >> 1;
	पूर्ण अन्यथा अगर (likely(skb->ip_summed == CHECKSUM_PARTIAL)) अणु
		pkt_desc->pkt.type_flags = GVE_TXD_STD | GVE_TXF_L4CSUM;
		pkt_desc->pkt.l4_csum_offset = skb->csum_offset >> 1;
		pkt_desc->pkt.l4_hdr_offset = l4_hdr_offset >> 1;
	पूर्ण अन्यथा अणु
		pkt_desc->pkt.type_flags = GVE_TXD_STD;
		pkt_desc->pkt.l4_csum_offset = 0;
		pkt_desc->pkt.l4_hdr_offset = 0;
	पूर्ण
	pkt_desc->pkt.desc_cnt = desc_cnt;
	pkt_desc->pkt.len = cpu_to_be16(skb->len);
	pkt_desc->pkt.seg_len = cpu_to_be16(hlen);
	pkt_desc->pkt.seg_addr = cpu_to_be64(addr);
पूर्ण

अटल व्योम gve_tx_fill_seg_desc(जोड़ gve_tx_desc *seg_desc,
				 काष्ठा sk_buff *skb, bool is_gso,
				 u16 len, u64 addr)
अणु
	seg_desc->seg.type_flags = GVE_TXD_SEG;
	अगर (is_gso) अणु
		अगर (skb_is_gso_v6(skb))
			seg_desc->seg.type_flags |= GVE_TXSF_IPV6;
		seg_desc->seg.l3_offset = skb_network_offset(skb) >> 1;
		seg_desc->seg.mss = cpu_to_be16(skb_shinfo(skb)->gso_size);
	पूर्ण
	seg_desc->seg.seg_len = cpu_to_be16(len);
	seg_desc->seg.seg_addr = cpu_to_be64(addr);
पूर्ण

अटल व्योम gve_dma_sync_क्रम_device(काष्ठा device *dev, dma_addr_t *page_buses,
				    u64 iov_offset, u64 iov_len)
अणु
	u64 last_page = (iov_offset + iov_len - 1) / PAGE_SIZE;
	u64 first_page = iov_offset / PAGE_SIZE;
	u64 page;

	क्रम (page = first_page; page <= last_page; page++)
		dma_sync_single_क्रम_device(dev, page_buses[page], PAGE_SIZE, DMA_TO_DEVICE);
पूर्ण

अटल पूर्णांक gve_tx_add_skb_copy(काष्ठा gve_priv *priv, काष्ठा gve_tx_ring *tx, काष्ठा sk_buff *skb)
अणु
	पूर्णांक pad_bytes, hlen, hdr_nfrags, payload_nfrags, l4_hdr_offset;
	जोड़ gve_tx_desc *pkt_desc, *seg_desc;
	काष्ठा gve_tx_buffer_state *info;
	bool is_gso = skb_is_gso(skb);
	u32 idx = tx->req & tx->mask;
	पूर्णांक payload_iov = 2;
	पूर्णांक copy_offset;
	u32 next_idx;
	पूर्णांक i;

	info = &tx->info[idx];
	pkt_desc = &tx->desc[idx];

	l4_hdr_offset = skb_checksum_start_offset(skb);
	/* If the skb is gso, then we want the tcp header in the first segment
	 * otherwise we want the linear portion of the skb (which will contain
	 * the checksum because skb->csum_start and skb->csum_offset are given
	 * relative to skb->head) in the first segment.
	 */
	hlen = is_gso ? l4_hdr_offset + tcp_hdrlen(skb) :
			skb_headlen(skb);

	info->skb =  skb;
	/* We करोn't want to split the header, so अगर necessary, pad to the end
	 * of the fअगरo and then put the header at the beginning of the fअगरo.
	 */
	pad_bytes = gve_tx_fअगरo_pad_alloc_one_frag(&tx->tx_fअगरo, hlen);
	hdr_nfrags = gve_tx_alloc_fअगरo(&tx->tx_fअगरo, hlen + pad_bytes,
				       &info->iov[0]);
	WARN(!hdr_nfrags, "hdr_nfrags should never be 0!");
	payload_nfrags = gve_tx_alloc_fअगरo(&tx->tx_fअगरo, skb->len - hlen,
					   &info->iov[payload_iov]);

	gve_tx_fill_pkt_desc(pkt_desc, skb, is_gso, l4_hdr_offset,
			     1 + payload_nfrags, hlen,
			     info->iov[hdr_nfrags - 1].iov_offset);

	skb_copy_bits(skb, 0,
		      tx->tx_fअगरo.base + info->iov[hdr_nfrags - 1].iov_offset,
		      hlen);
	gve_dma_sync_क्रम_device(&priv->pdev->dev, tx->tx_fअगरo.qpl->page_buses,
				info->iov[hdr_nfrags - 1].iov_offset,
				info->iov[hdr_nfrags - 1].iov_len);
	copy_offset = hlen;

	क्रम (i = payload_iov; i < payload_nfrags + payload_iov; i++) अणु
		next_idx = (tx->req + 1 + i - payload_iov) & tx->mask;
		seg_desc = &tx->desc[next_idx];

		gve_tx_fill_seg_desc(seg_desc, skb, is_gso,
				     info->iov[i].iov_len,
				     info->iov[i].iov_offset);

		skb_copy_bits(skb, copy_offset,
			      tx->tx_fअगरo.base + info->iov[i].iov_offset,
			      info->iov[i].iov_len);
		gve_dma_sync_क्रम_device(&priv->pdev->dev, tx->tx_fअगरo.qpl->page_buses,
					info->iov[i].iov_offset,
					info->iov[i].iov_len);
		copy_offset += info->iov[i].iov_len;
	पूर्ण

	वापस 1 + payload_nfrags;
पूर्ण

अटल पूर्णांक gve_tx_add_skb_no_copy(काष्ठा gve_priv *priv, काष्ठा gve_tx_ring *tx,
				  काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा skb_shared_info *shinfo = skb_shinfo(skb);
	पूर्णांक hlen, payload_nfrags, l4_hdr_offset;
	जोड़ gve_tx_desc *pkt_desc, *seg_desc;
	काष्ठा gve_tx_buffer_state *info;
	bool is_gso = skb_is_gso(skb);
	u32 idx = tx->req & tx->mask;
	काष्ठा gve_tx_dma_buf *buf;
	u64 addr;
	u32 len;
	पूर्णांक i;

	info = &tx->info[idx];
	pkt_desc = &tx->desc[idx];

	l4_hdr_offset = skb_checksum_start_offset(skb);
	/* If the skb is gso, then we want only up to the tcp header in the first segment
	 * to efficiently replicate on each segment otherwise we want the linear portion
	 * of the skb (which will contain the checksum because skb->csum_start and
	 * skb->csum_offset are given relative to skb->head) in the first segment.
	 */
	hlen = is_gso ? l4_hdr_offset + tcp_hdrlen(skb) : skb_headlen(skb);
	len = skb_headlen(skb);

	info->skb =  skb;

	addr = dma_map_single(tx->dev, skb->data, len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(tx->dev, addr))) अणु
		tx->dma_mapping_error++;
		जाओ drop;
	पूर्ण
	buf = &info->buf;
	dma_unmap_len_set(buf, len, len);
	dma_unmap_addr_set(buf, dma, addr);

	payload_nfrags = shinfo->nr_frags;
	अगर (hlen < len) अणु
		/* For gso the rest of the linear portion of the skb needs to
		 * be in its own descriptor.
		 */
		payload_nfrags++;
		gve_tx_fill_pkt_desc(pkt_desc, skb, is_gso, l4_hdr_offset,
				     1 + payload_nfrags, hlen, addr);

		len -= hlen;
		addr += hlen;
		idx = (tx->req + 1) & tx->mask;
		seg_desc = &tx->desc[idx];
		gve_tx_fill_seg_desc(seg_desc, skb, is_gso, len, addr);
	पूर्ण अन्यथा अणु
		gve_tx_fill_pkt_desc(pkt_desc, skb, is_gso, l4_hdr_offset,
				     1 + payload_nfrags, hlen, addr);
	पूर्ण

	क्रम (i = 0; i < shinfo->nr_frags; i++) अणु
		स्थिर skb_frag_t *frag = &shinfo->frags[i];

		idx = (idx + 1) & tx->mask;
		seg_desc = &tx->desc[idx];
		len = skb_frag_size(frag);
		addr = skb_frag_dma_map(tx->dev, frag, 0, len, DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(tx->dev, addr))) अणु
			tx->dma_mapping_error++;
			जाओ unmap_drop;
		पूर्ण
		buf = &tx->info[idx].buf;
		tx->info[idx].skb = शून्य;
		dma_unmap_len_set(buf, len, len);
		dma_unmap_addr_set(buf, dma, addr);

		gve_tx_fill_seg_desc(seg_desc, skb, is_gso, len, addr);
	पूर्ण

	वापस 1 + payload_nfrags;

unmap_drop:
	i += (payload_nfrags == shinfo->nr_frags ? 1 : 2);
	जबतक (i--) अणु
		idx--;
		gve_tx_unmap_buf(tx->dev, &tx->info[idx & tx->mask]);
	पूर्ण
drop:
	tx->dropped_pkt++;
	वापस 0;
पूर्ण

netdev_tx_t gve_tx(काष्ठा sk_buff *skb, काष्ठा net_device *dev)
अणु
	काष्ठा gve_priv *priv = netdev_priv(dev);
	काष्ठा gve_tx_ring *tx;
	पूर्णांक nsegs;

	WARN(skb_get_queue_mapping(skb) >= priv->tx_cfg.num_queues,
	     "skb queue index out of range");
	tx = &priv->tx[skb_get_queue_mapping(skb)];
	अगर (unlikely(gve_maybe_stop_tx(tx, skb))) अणु
		/* We need to ring the txq करोorbell -- we have stopped the Tx
		 * queue क्रम want of resources, but prior calls to gve_tx()
		 * may have added descriptors without ringing the करोorbell.
		 */

		gve_tx_put_करोorbell(priv, tx->q_resources, tx->req);
		वापस NETDEV_TX_BUSY;
	पूर्ण
	अगर (tx->raw_addressing)
		nsegs = gve_tx_add_skb_no_copy(priv, tx, skb);
	अन्यथा
		nsegs = gve_tx_add_skb_copy(priv, tx, skb);

	/* If the packet is getting sent, we need to update the skb */
	अगर (nsegs) अणु
		netdev_tx_sent_queue(tx->netdev_txq, skb->len);
		skb_tx_बारtamp(skb);
		tx->req += nsegs;
	पूर्ण अन्यथा अणु
		dev_kमुक्त_skb_any(skb);
	पूर्ण

	अगर (!netअगर_xmit_stopped(tx->netdev_txq) && netdev_xmit_more())
		वापस NETDEV_TX_OK;

	/* Give packets to NIC. Even अगर this packet failed to send the करोorbell
	 * might need to be rung because of xmit_more.
	 */
	gve_tx_put_करोorbell(priv, tx->q_resources, tx->req);
	वापस NETDEV_TX_OK;
पूर्ण

#घोषणा GVE_TX_START_THRESH	PAGE_SIZE

अटल पूर्णांक gve_clean_tx_करोne(काष्ठा gve_priv *priv, काष्ठा gve_tx_ring *tx,
			     u32 to_करो, bool try_to_wake)
अणु
	काष्ठा gve_tx_buffer_state *info;
	u64 pkts = 0, bytes = 0;
	माप_प्रकार space_मुक्तd = 0;
	काष्ठा sk_buff *skb;
	पूर्णांक i, j;
	u32 idx;

	क्रम (j = 0; j < to_करो; j++) अणु
		idx = tx->करोne & tx->mask;
		netअगर_info(priv, tx_करोne, priv->dev,
			   "[%d] %s: idx=%d (req=%u done=%u)\n",
			   tx->q_num, __func__, idx, tx->req, tx->करोne);
		info = &tx->info[idx];
		skb = info->skb;

		/* Unmap the buffer */
		अगर (tx->raw_addressing)
			gve_tx_unmap_buf(tx->dev, info);
		tx->करोne++;
		/* Mark as मुक्त */
		अगर (skb) अणु
			info->skb = शून्य;
			bytes += skb->len;
			pkts++;
			dev_consume_skb_any(skb);
			अगर (tx->raw_addressing)
				जारी;
			/* FIFO मुक्त */
			क्रम (i = 0; i < ARRAY_SIZE(info->iov); i++) अणु
				space_मुक्तd += info->iov[i].iov_len + info->iov[i].iov_padding;
				info->iov[i].iov_len = 0;
				info->iov[i].iov_padding = 0;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!tx->raw_addressing)
		gve_tx_मुक्त_fअगरo(&tx->tx_fअगरo, space_मुक्तd);
	u64_stats_update_begin(&tx->statss);
	tx->bytes_करोne += bytes;
	tx->pkt_करोne += pkts;
	u64_stats_update_end(&tx->statss);
	netdev_tx_completed_queue(tx->netdev_txq, pkts, bytes);

	/* start the queue अगर we've stopped it */
#अगर_अघोषित CONFIG_BQL
	/* Make sure that the करोorbells are synced */
	smp_mb();
#पूर्ण_अगर
	अगर (try_to_wake && netअगर_tx_queue_stopped(tx->netdev_txq) &&
	    likely(gve_can_tx(tx, GVE_TX_START_THRESH))) अणु
		tx->wake_queue++;
		netअगर_tx_wake_queue(tx->netdev_txq);
	पूर्ण

	वापस pkts;
पूर्ण

__be32 gve_tx_load_event_counter(काष्ठा gve_priv *priv,
				 काष्ठा gve_tx_ring *tx)
अणु
	u32 counter_index = be32_to_cpu((tx->q_resources->counter_index));

	वापस READ_ONCE(priv->counter_array[counter_index]);
पूर्ण

bool gve_tx_poll(काष्ठा gve_notअगरy_block *block, पूर्णांक budget)
अणु
	काष्ठा gve_priv *priv = block->priv;
	काष्ठा gve_tx_ring *tx = block->tx;
	bool repoll = false;
	u32 nic_करोne;
	u32 to_करो;

	/* If budget is 0, करो all the work */
	अगर (budget == 0)
		budget = पूर्णांक_उच्च;

	/* Find out how much work there is to be करोne */
	tx->last_nic_करोne = gve_tx_load_event_counter(priv, tx);
	nic_करोne = be32_to_cpu(tx->last_nic_करोne);
	अगर (budget > 0) अणु
		/* Do as much work as we have that the budget will
		 * allow
		 */
		to_करो = min_t(u32, (nic_करोne - tx->करोne), budget);
		gve_clean_tx_करोne(priv, tx, to_करो, true);
	पूर्ण
	/* If we still have work we want to repoll */
	repoll |= (nic_करोne != tx->करोne);
	वापस repoll;
पूर्ण
