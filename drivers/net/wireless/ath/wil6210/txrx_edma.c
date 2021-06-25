<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2019 The Linux Foundation. All rights reserved.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/prefetch.h>
#समावेश <linux/types.h>
#समावेश <linux/list.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश "wil6210.h"
#समावेश "txrx_edma.h"
#समावेश "txrx.h"
#समावेश "trace.h"

/* Max number of entries (packets to complete) to update the hwtail of tx
 * status ring. Should be घातer of 2
 */
#घोषणा WIL_EDMA_TX_SRING_UPDATE_HW_TAIL 128
#घोषणा WIL_EDMA_MAX_DATA_OFFSET (2)
/* RX buffer size must be aligned to 4 bytes */
#घोषणा WIL_EDMA_RX_BUF_LEN_DEFAULT (2048)
#घोषणा MAX_INVALID_BUFF_ID_RETRY (3)

अटल व्योम wil_tx_desc_unmap_edma(काष्ठा device *dev,
				   जोड़ wil_tx_desc *desc,
				   काष्ठा wil_ctx *ctx)
अणु
	काष्ठा wil_tx_enhanced_desc *d = (काष्ठा wil_tx_enhanced_desc *)desc;
	dma_addr_t pa = wil_tx_desc_get_addr_edma(&d->dma);
	u16 dmalen = le16_to_cpu(d->dma.length);

	चयन (ctx->mapped_as) अणु
	हाल wil_mapped_as_single:
		dma_unmap_single(dev, pa, dmalen, DMA_TO_DEVICE);
		अवरोध;
	हाल wil_mapped_as_page:
		dma_unmap_page(dev, pa, dmalen, DMA_TO_DEVICE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक wil_find_मुक्त_sring(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < WIL6210_MAX_STATUS_RINGS; i++) अणु
		अगर (!wil->srings[i].va)
			वापस i;
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल व्योम wil_sring_मुक्त(काष्ठा wil6210_priv *wil,
			   काष्ठा wil_status_ring *sring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	माप_प्रकार sz;

	अगर (!sring || !sring->va)
		वापस;

	sz = sring->elem_size * sring->size;

	wil_dbg_misc(wil, "status_ring_free, size(bytes)=%zu, 0x%p:%pad\n",
		     sz, sring->va, &sring->pa);

	dma_मुक्त_coherent(dev, sz, (व्योम *)sring->va, sring->pa);
	sring->pa = 0;
	sring->va = शून्य;
पूर्ण

अटल पूर्णांक wil_sring_alloc(काष्ठा wil6210_priv *wil,
			   काष्ठा wil_status_ring *sring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	माप_प्रकार sz = sring->elem_size * sring->size;

	wil_dbg_misc(wil, "status_ring_alloc: size=%zu\n", sz);

	अगर (sz == 0) अणु
		wil_err(wil, "Cannot allocate a zero size status ring\n");
		वापस -EINVAL;
	पूर्ण

	sring->swhead = 0;

	/* Status messages are allocated and initialized to 0. This is necessary
	 * since DR bit should be initialized to 0.
	 */
	sring->va = dma_alloc_coherent(dev, sz, &sring->pa, GFP_KERNEL);
	अगर (!sring->va)
		वापस -ENOMEM;

	wil_dbg_misc(wil, "status_ring[%d] 0x%p:%pad\n", sring->size, sring->va,
		     &sring->pa);

	वापस 0;
पूर्ण

अटल पूर्णांक wil_tx_init_edma(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक ring_id = wil_find_मुक्त_sring(wil);
	काष्ठा wil_status_ring *sring;
	पूर्णांक rc;
	u16 status_ring_size;

	अगर (wil->tx_status_ring_order < WIL_SRING_SIZE_ORDER_MIN ||
	    wil->tx_status_ring_order > WIL_SRING_SIZE_ORDER_MAX)
		wil->tx_status_ring_order = WIL_TX_SRING_SIZE_ORDER_DEFAULT;

	status_ring_size = 1 << wil->tx_status_ring_order;

	wil_dbg_misc(wil, "init TX sring: size=%u, ring_id=%u\n",
		     status_ring_size, ring_id);

	अगर (ring_id < 0)
		वापस ring_id;

	/* Allocate Tx status ring. Tx descriptor rings will be
	 * allocated on WMI connect event
	 */
	sring = &wil->srings[ring_id];

	sring->is_rx = false;
	sring->size = status_ring_size;
	sring->elem_size = माप(काष्ठा wil_ring_tx_status);
	rc = wil_sring_alloc(wil, sring);
	अगर (rc)
		वापस rc;

	rc = wil_wmi_tx_sring_cfg(wil, ring_id);
	अगर (rc)
		जाओ out_मुक्त;

	sring->desc_rdy_pol = 1;
	wil->tx_sring_idx = ring_id;

	वापस 0;
out_मुक्त:
	wil_sring_मुक्त(wil, sring);
	वापस rc;
पूर्ण

/* Allocate one skb क्रम Rx descriptor RING */
अटल पूर्णांक wil_ring_alloc_skb_edma(काष्ठा wil6210_priv *wil,
				   काष्ठा wil_ring *ring, u32 i)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	अचिन्हित पूर्णांक sz = wil->rx_buf_len;
	dma_addr_t pa;
	u16 buff_id;
	काष्ठा list_head *active = &wil->rx_buff_mgmt.active;
	काष्ठा list_head *मुक्त = &wil->rx_buff_mgmt.मुक्त;
	काष्ठा wil_rx_buff *rx_buff;
	काष्ठा wil_rx_buff *buff_arr = wil->rx_buff_mgmt.buff_arr;
	काष्ठा sk_buff *skb;
	काष्ठा wil_rx_enhanced_desc dd, *d = &dd;
	काष्ठा wil_rx_enhanced_desc *_d = (काष्ठा wil_rx_enhanced_desc *)
		&ring->va[i].rx.enhanced;

	अगर (unlikely(list_empty(मुक्त))) अणु
		wil->rx_buff_mgmt.मुक्त_list_empty_cnt++;
		वापस -EAGAIN;
	पूर्ण

	skb = dev_alloc_skb(sz);
	अगर (unlikely(!skb))
		वापस -ENOMEM;

	skb_put(skb, sz);

	/**
	 * Make sure that the network stack calculates checksum क्रम packets
	 * which failed the HW checksum calculation
	 */
	skb->ip_summed = CHECKSUM_NONE;

	pa = dma_map_single(dev, skb->data, skb->len, DMA_FROM_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, pa))) अणु
		kमुक्त_skb(skb);
		वापस -ENOMEM;
	पूर्ण

	/* Get the buffer ID - the index of the rx buffer in the buff_arr */
	rx_buff = list_first_entry(मुक्त, काष्ठा wil_rx_buff, list);
	buff_id = rx_buff->id;

	/* Move a buffer from the मुक्त list to the active list */
	list_move(&rx_buff->list, active);

	buff_arr[buff_id].skb = skb;

	wil_desc_set_addr_edma(&d->dma.addr, &d->dma.addr_high_high, pa);
	d->dma.length = cpu_to_le16(sz);
	d->mac.buff_id = cpu_to_le16(buff_id);
	*_d = *d;

	/* Save the physical address in skb->cb क्रम later use in dma_unmap */
	स_नकल(skb->cb, &pa, माप(pa));

	वापस 0;
पूर्ण

अटल अंतरभूत
व्योम wil_get_next_rx_status_msg(काष्ठा wil_status_ring *sring, u8 *dr_bit,
				व्योम *msg)
अणु
	काष्ठा wil_rx_status_compressed *_msg;

	_msg = (काष्ठा wil_rx_status_compressed *)
		(sring->va + (sring->elem_size * sring->swhead));
	*dr_bit = WIL_GET_BITS(_msg->d0, 31, 31);
	/* make sure dr_bit is पढ़ो beक्रमe the rest of status msg */
	rmb();
	स_नकल(msg, (व्योम *)_msg, sring->elem_size);
पूर्ण

अटल अंतरभूत व्योम wil_sring_advance_swhead(काष्ठा wil_status_ring *sring)
अणु
	sring->swhead = (sring->swhead + 1) % sring->size;
	अगर (sring->swhead == 0)
		sring->desc_rdy_pol = 1 - sring->desc_rdy_pol;
पूर्ण

अटल पूर्णांक wil_rx_refill_edma(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil_ring *ring = &wil->ring_rx;
	u32 next_head;
	पूर्णांक rc = 0;
	ring->swtail = *ring->edma_rx_swtail.va;

	क्रम (; next_head = wil_ring_next_head(ring),
	     (next_head != ring->swtail);
	     ring->swhead = next_head) अणु
		rc = wil_ring_alloc_skb_edma(wil, ring, ring->swhead);
		अगर (unlikely(rc)) अणु
			अगर (rc == -EAGAIN)
				wil_dbg_txrx(wil, "No free buffer ID found\n");
			अन्यथा
				wil_err_ratelimited(wil,
						    "Error %d in refill desc[%d]\n",
						    rc, ring->swhead);
			अवरोध;
		पूर्ण
	पूर्ण

	/* make sure all ग_लिखोs to descriptors (shared memory) are करोne beक्रमe
	 * committing them to HW
	 */
	wmb();

	wil_w(wil, ring->hwtail, ring->swhead);

	वापस rc;
पूर्ण

अटल व्योम wil_move_all_rx_buff_to_मुक्त_list(काष्ठा wil6210_priv *wil,
					      काष्ठा wil_ring *ring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा list_head *active = &wil->rx_buff_mgmt.active;
	dma_addr_t pa;

	अगर (!wil->rx_buff_mgmt.buff_arr)
		वापस;

	जबतक (!list_empty(active)) अणु
		काष्ठा wil_rx_buff *rx_buff =
			list_first_entry(active, काष्ठा wil_rx_buff, list);
		काष्ठा sk_buff *skb = rx_buff->skb;

		अगर (unlikely(!skb)) अणु
			wil_err(wil, "No Rx skb at buff_id %d\n", rx_buff->id);
		पूर्ण अन्यथा अणु
			rx_buff->skb = शून्य;
			स_नकल(&pa, skb->cb, माप(pa));
			dma_unmap_single(dev, pa, wil->rx_buf_len,
					 DMA_FROM_DEVICE);
			kमुक्त_skb(skb);
		पूर्ण

		/* Move the buffer from the active to the मुक्त list */
		list_move(&rx_buff->list, &wil->rx_buff_mgmt.मुक्त);
	पूर्ण
पूर्ण

अटल व्योम wil_मुक्त_rx_buff_arr(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil_ring *ring = &wil->ring_rx;

	अगर (!wil->rx_buff_mgmt.buff_arr)
		वापस;

	/* Move all the buffers to the मुक्त list in हाल active list is
	 * not empty in order to release all SKBs beक्रमe deleting the array
	 */
	wil_move_all_rx_buff_to_मुक्त_list(wil, ring);

	kमुक्त(wil->rx_buff_mgmt.buff_arr);
	wil->rx_buff_mgmt.buff_arr = शून्य;
पूर्ण

अटल पूर्णांक wil_init_rx_buff_arr(काष्ठा wil6210_priv *wil,
				माप_प्रकार size)
अणु
	काष्ठा wil_rx_buff *buff_arr;
	काष्ठा list_head *active = &wil->rx_buff_mgmt.active;
	काष्ठा list_head *मुक्त = &wil->rx_buff_mgmt.मुक्त;
	पूर्णांक i;

	wil->rx_buff_mgmt.buff_arr = kसुस्मृति(size + 1,
					     माप(काष्ठा wil_rx_buff),
					     GFP_KERNEL);
	अगर (!wil->rx_buff_mgmt.buff_arr)
		वापस -ENOMEM;

	/* Set list heads */
	INIT_LIST_HEAD(active);
	INIT_LIST_HEAD(मुक्त);

	/* Linkअगरy the list.
	 * buffer id 0 should not be used (marks invalid id).
	 */
	buff_arr = wil->rx_buff_mgmt.buff_arr;
	क्रम (i = 1; i <= size; i++) अणु
		list_add(&buff_arr[i].list, मुक्त);
		buff_arr[i].id = i;
	पूर्ण

	wil->rx_buff_mgmt.size = size + 1;

	वापस 0;
पूर्ण

अटल पूर्णांक wil_init_rx_sring(काष्ठा wil6210_priv *wil,
			     u16 status_ring_size,
			     माप_प्रकार elem_size,
			     u16 ring_id)
अणु
	काष्ठा wil_status_ring *sring = &wil->srings[ring_id];
	पूर्णांक rc;

	wil_dbg_misc(wil, "init RX sring: size=%u, ring_id=%u\n",
		     status_ring_size, ring_id);

	स_रखो(&sring->rx_data, 0, माप(sring->rx_data));

	sring->is_rx = true;
	sring->size = status_ring_size;
	sring->elem_size = elem_size;
	rc = wil_sring_alloc(wil, sring);
	अगर (rc)
		वापस rc;

	rc = wil_wmi_rx_sring_add(wil, ring_id);
	अगर (rc)
		जाओ out_मुक्त;

	sring->desc_rdy_pol = 1;

	वापस 0;
out_मुक्त:
	wil_sring_मुक्त(wil, sring);
	वापस rc;
पूर्ण

अटल पूर्णांक wil_ring_alloc_desc_ring(काष्ठा wil6210_priv *wil,
				    काष्ठा wil_ring *ring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	माप_प्रकार sz = ring->size * माप(ring->va[0]);

	wil_dbg_misc(wil, "alloc_desc_ring:\n");

	BUILD_BUG_ON(माप(ring->va[0]) != 32);

	ring->swhead = 0;
	ring->swtail = 0;
	ring->ctx = kसुस्मृति(ring->size, माप(ring->ctx[0]), GFP_KERNEL);
	अगर (!ring->ctx)
		जाओ err;

	ring->va = dma_alloc_coherent(dev, sz, &ring->pa, GFP_KERNEL);
	अगर (!ring->va)
		जाओ err_मुक्त_ctx;

	अगर (ring->is_rx) अणु
		sz = माप(*ring->edma_rx_swtail.va);
		ring->edma_rx_swtail.va =
			dma_alloc_coherent(dev, sz, &ring->edma_rx_swtail.pa,
					   GFP_KERNEL);
		अगर (!ring->edma_rx_swtail.va)
			जाओ err_मुक्त_va;
	पूर्ण

	wil_dbg_misc(wil, "%s ring[%d] 0x%p:%pad 0x%p\n",
		     ring->is_rx ? "RX" : "TX",
		     ring->size, ring->va, &ring->pa, ring->ctx);

	वापस 0;
err_मुक्त_va:
	dma_मुक्त_coherent(dev, ring->size * माप(ring->va[0]),
			  (व्योम *)ring->va, ring->pa);
	ring->va = शून्य;
err_मुक्त_ctx:
	kमुक्त(ring->ctx);
	ring->ctx = शून्य;
err:
	वापस -ENOMEM;
पूर्ण

अटल व्योम wil_ring_मुक्त_edma(काष्ठा wil6210_priv *wil, काष्ठा wil_ring *ring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	माप_प्रकार sz;
	पूर्णांक ring_index = 0;

	अगर (!ring->va)
		वापस;

	sz = ring->size * माप(ring->va[0]);

	lockdep_निश्चित_held(&wil->mutex);
	अगर (ring->is_rx) अणु
		wil_dbg_misc(wil, "free Rx ring [%d] 0x%p:%pad 0x%p\n",
			     ring->size, ring->va,
			     &ring->pa, ring->ctx);

		wil_move_all_rx_buff_to_मुक्त_list(wil, ring);
		dma_मुक्त_coherent(dev, माप(*ring->edma_rx_swtail.va),
				  ring->edma_rx_swtail.va,
				  ring->edma_rx_swtail.pa);
		जाओ out;
	पूर्ण

	/* TX ring */
	ring_index = ring - wil->ring_tx;

	wil_dbg_misc(wil, "free Tx ring %d [%d] 0x%p:%pad 0x%p\n",
		     ring_index, ring->size, ring->va,
		     &ring->pa, ring->ctx);

	जबतक (!wil_ring_is_empty(ring)) अणु
		काष्ठा wil_ctx *ctx;

		काष्ठा wil_tx_enhanced_desc dd, *d = &dd;
		काष्ठा wil_tx_enhanced_desc *_d =
			(काष्ठा wil_tx_enhanced_desc *)
			&ring->va[ring->swtail].tx.enhanced;

		ctx = &ring->ctx[ring->swtail];
		अगर (!ctx) अणु
			wil_dbg_txrx(wil,
				     "ctx(%d) was already completed\n",
				     ring->swtail);
			ring->swtail = wil_ring_next_tail(ring);
			जारी;
		पूर्ण
		*d = *_d;
		wil_tx_desc_unmap_edma(dev, (जोड़ wil_tx_desc *)d, ctx);
		अगर (ctx->skb)
			dev_kमुक्त_skb_any(ctx->skb);
		ring->swtail = wil_ring_next_tail(ring);
	पूर्ण

out:
	dma_मुक्त_coherent(dev, sz, (व्योम *)ring->va, ring->pa);
	kमुक्त(ring->ctx);
	ring->pa = 0;
	ring->va = शून्य;
	ring->ctx = शून्य;
पूर्ण

अटल पूर्णांक wil_init_rx_desc_ring(काष्ठा wil6210_priv *wil, u16 desc_ring_size,
				 पूर्णांक status_ring_id)
अणु
	काष्ठा wil_ring *ring = &wil->ring_rx;
	पूर्णांक rc;

	wil_dbg_misc(wil, "init RX desc ring\n");

	ring->size = desc_ring_size;
	ring->is_rx = true;
	rc = wil_ring_alloc_desc_ring(wil, ring);
	अगर (rc)
		वापस rc;

	rc = wil_wmi_rx_desc_ring_add(wil, status_ring_id);
	अगर (rc)
		जाओ out_मुक्त;

	वापस 0;
out_मुक्त:
	wil_ring_मुक्त_edma(wil, ring);
	वापस rc;
पूर्ण

अटल व्योम wil_get_reorder_params_edma(काष्ठा wil6210_priv *wil,
					काष्ठा sk_buff *skb, पूर्णांक *tid,
					पूर्णांक *cid, पूर्णांक *mid, u16 *seq,
					पूर्णांक *mcast, पूर्णांक *retry)
अणु
	काष्ठा wil_rx_status_extended *s = wil_skb_rxstatus(skb);

	*tid = wil_rx_status_get_tid(s);
	*cid = wil_rx_status_get_cid(s);
	*mid = wil_rx_status_get_mid(s);
	*seq = le16_to_cpu(wil_rx_status_get_seq(wil, s));
	*mcast = wil_rx_status_get_mcast(s);
	*retry = wil_rx_status_get_retry(s);
पूर्ण

अटल व्योम wil_get_netअगर_rx_params_edma(काष्ठा sk_buff *skb, पूर्णांक *cid,
					 पूर्णांक *security)
अणु
	काष्ठा wil_rx_status_extended *s = wil_skb_rxstatus(skb);

	*cid = wil_rx_status_get_cid(s);
	*security = wil_rx_status_get_security(s);
पूर्ण

अटल पूर्णांक wil_rx_crypto_check_edma(काष्ठा wil6210_priv *wil,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा wil_rx_status_extended *st;
	पूर्णांक cid, tid, key_id, mc;
	काष्ठा wil_sta_info *s;
	काष्ठा wil_tid_crypto_rx *c;
	काष्ठा wil_tid_crypto_rx_single *cc;
	स्थिर u8 *pn;

	/* In HW reorder, HW is responsible क्रम crypto check */
	अगर (wil->use_rx_hw_reordering)
		वापस 0;

	st = wil_skb_rxstatus(skb);

	cid = wil_rx_status_get_cid(st);
	tid = wil_rx_status_get_tid(st);
	key_id = wil_rx_status_get_key_id(st);
	mc = wil_rx_status_get_mcast(st);
	s = &wil->sta[cid];
	c = mc ? &s->group_crypto_rx : &s->tid_crypto_rx[tid];
	cc = &c->key_id[key_id];
	pn = (u8 *)&st->ext.pn_15_0;

	अगर (!cc->key_set) अणु
		wil_err_ratelimited(wil,
				    "Key missing. CID %d TID %d MCast %d KEY_ID %d\n",
				    cid, tid, mc, key_id);
		वापस -EINVAL;
	पूर्ण

	अगर (reverse_स_भेद(pn, cc->pn, IEEE80211_GCMP_PN_LEN) <= 0) अणु
		wil_err_ratelimited(wil,
				    "Replay attack. CID %d TID %d MCast %d KEY_ID %d PN %6phN last %6phN\n",
				    cid, tid, mc, key_id, pn, cc->pn);
		वापस -EINVAL;
	पूर्ण
	स_नकल(cc->pn, pn, IEEE80211_GCMP_PN_LEN);

	वापस 0;
पूर्ण

अटल bool wil_is_rx_idle_edma(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil_status_ring *sring;
	काष्ठा wil_rx_status_extended msg1;
	व्योम *msg = &msg1;
	u8 dr_bit;
	पूर्णांक i;

	क्रम (i = 0; i < wil->num_rx_status_rings; i++) अणु
		sring = &wil->srings[i];
		अगर (!sring->va)
			जारी;

		wil_get_next_rx_status_msg(sring, &dr_bit, msg);

		/* Check अगर there are unhandled RX status messages */
		अगर (dr_bit == sring->desc_rdy_pol)
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम wil_rx_buf_len_init_edma(काष्ठा wil6210_priv *wil)
अणु
	/* RX buffer size must be aligned to 4 bytes */
	wil->rx_buf_len = rx_large_buf ?
		WIL_MAX_ETH_MTU : WIL_EDMA_RX_BUF_LEN_DEFAULT;
पूर्ण

अटल पूर्णांक wil_rx_init_edma(काष्ठा wil6210_priv *wil, uपूर्णांक desc_ring_order)
अणु
	u16 status_ring_size, desc_ring_size = 1 << desc_ring_order;
	काष्ठा wil_ring *ring = &wil->ring_rx;
	पूर्णांक rc;
	माप_प्रकार elem_size = wil->use_compressed_rx_status ?
		माप(काष्ठा wil_rx_status_compressed) :
		माप(काष्ठा wil_rx_status_extended);
	पूर्णांक i;

	/* In SW reorder one must use extended status messages */
	अगर (wil->use_compressed_rx_status && !wil->use_rx_hw_reordering) अणु
		wil_err(wil,
			"compressed RX status cannot be used with SW reorder\n");
		वापस -EINVAL;
	पूर्ण
	अगर (wil->rx_status_ring_order <= desc_ring_order)
		/* make sure sring is larger than desc ring */
		wil->rx_status_ring_order = desc_ring_order + 1;
	अगर (wil->rx_buff_id_count <= desc_ring_size)
		/* make sure we will not run out of buff_ids */
		wil->rx_buff_id_count = desc_ring_size + 512;
	अगर (wil->rx_status_ring_order < WIL_SRING_SIZE_ORDER_MIN ||
	    wil->rx_status_ring_order > WIL_SRING_SIZE_ORDER_MAX)
		wil->rx_status_ring_order = WIL_RX_SRING_SIZE_ORDER_DEFAULT;

	status_ring_size = 1 << wil->rx_status_ring_order;

	wil_dbg_misc(wil,
		     "rx_init, desc_ring_size=%u, status_ring_size=%u, elem_size=%zu\n",
		     desc_ring_size, status_ring_size, elem_size);

	wil_rx_buf_len_init_edma(wil);

	/* Use debugfs dbg_num_rx_srings अगर set, reserve one sring क्रम TX */
	अगर (wil->num_rx_status_rings > WIL6210_MAX_STATUS_RINGS - 1)
		wil->num_rx_status_rings = WIL6210_MAX_STATUS_RINGS - 1;

	wil_dbg_misc(wil, "rx_init: allocate %d status rings\n",
		     wil->num_rx_status_rings);

	rc = wil_wmi_cfg_def_rx_offload(wil, wil->rx_buf_len);
	अगर (rc)
		वापस rc;

	/* Allocate status ring */
	क्रम (i = 0; i < wil->num_rx_status_rings; i++) अणु
		पूर्णांक sring_id = wil_find_मुक्त_sring(wil);

		अगर (sring_id < 0) अणु
			rc = -EFAULT;
			जाओ err_मुक्त_status;
		पूर्ण
		rc = wil_init_rx_sring(wil, status_ring_size, elem_size,
				       sring_id);
		अगर (rc)
			जाओ err_मुक्त_status;
	पूर्ण

	/* Allocate descriptor ring */
	rc = wil_init_rx_desc_ring(wil, desc_ring_size,
				   WIL_DEFAULT_RX_STATUS_RING_ID);
	अगर (rc)
		जाओ err_मुक्त_status;

	अगर (wil->rx_buff_id_count >= status_ring_size) अणु
		wil_info(wil,
			 "rx_buff_id_count %d exceeds sring_size %d. set it to %d\n",
			 wil->rx_buff_id_count, status_ring_size,
			 status_ring_size - 1);
		wil->rx_buff_id_count = status_ring_size - 1;
	पूर्ण

	/* Allocate Rx buffer array */
	rc = wil_init_rx_buff_arr(wil, wil->rx_buff_id_count);
	अगर (rc)
		जाओ err_मुक्त_desc;

	/* Fill descriptor ring with credits */
	rc = wil_rx_refill_edma(wil);
	अगर (rc)
		जाओ err_मुक्त_rx_buff_arr;

	वापस 0;
err_मुक्त_rx_buff_arr:
	wil_मुक्त_rx_buff_arr(wil);
err_मुक्त_desc:
	wil_ring_मुक्त_edma(wil, ring);
err_मुक्त_status:
	क्रम (i = 0; i < wil->num_rx_status_rings; i++)
		wil_sring_मुक्त(wil, &wil->srings[i]);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_ring_init_tx_edma(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id,
				 पूर्णांक size, पूर्णांक cid, पूर्णांक tid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा wil_ring *ring = &wil->ring_tx[ring_id];
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_id];

	lockdep_निश्चित_held(&wil->mutex);

	wil_dbg_misc(wil,
		     "init TX ring: ring_id=%u, cid=%u, tid=%u, sring_id=%u\n",
		     ring_id, cid, tid, wil->tx_sring_idx);

	wil_tx_data_init(txdata);
	ring->size = size;
	rc = wil_ring_alloc_desc_ring(wil, ring);
	अगर (rc)
		जाओ out;

	wil->ring2cid_tid[ring_id][0] = cid;
	wil->ring2cid_tid[ring_id][1] = tid;
	अगर (!vअगर->privacy)
		txdata->करोt1x_खोलो = true;

	rc = wil_wmi_tx_desc_ring_add(vअगर, ring_id, cid, tid);
	अगर (rc) अणु
		wil_err(wil, "WMI_TX_DESC_RING_ADD_CMD failed\n");
		जाओ out_मुक्त;
	पूर्ण

	अगर (txdata->करोt1x_खोलो && agg_wsize >= 0)
		wil_addba_tx_request(wil, ring_id, agg_wsize);

	वापस 0;
 out_मुक्त:
	spin_lock_bh(&txdata->lock);
	txdata->करोt1x_खोलो = false;
	txdata->enabled = 0;
	spin_unlock_bh(&txdata->lock);
	wil_ring_मुक्त_edma(wil, ring);
	wil->ring2cid_tid[ring_id][0] = wil->max_assoc_sta;
	wil->ring2cid_tid[ring_id][1] = 0;

 out:
	वापस rc;
पूर्ण

अटल पूर्णांक wil_tx_ring_modअगरy_edma(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id,
				   पूर्णांक cid, पूर्णांक tid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	wil_err(wil, "ring modify is not supported for EDMA\n");

	वापस -EOPNOTSUPP;
पूर्ण

/* This function is used only क्रम RX SW reorder */
अटल पूर्णांक wil_check_bar(काष्ठा wil6210_priv *wil, व्योम *msg, पूर्णांक cid,
			 काष्ठा sk_buff *skb, काष्ठा wil_net_stats *stats)
अणु
	u8 ftype;
	u8 fc1;
	पूर्णांक mid;
	पूर्णांक tid;
	u16 seq;
	काष्ठा wil6210_vअगर *vअगर;

	ftype = wil_rx_status_get_frame_type(wil, msg);
	अगर (ftype == IEEE80211_FTYPE_DATA)
		वापस 0;

	fc1 = wil_rx_status_get_fc1(wil, msg);
	mid = wil_rx_status_get_mid(msg);
	tid = wil_rx_status_get_tid(msg);
	seq = le16_to_cpu(wil_rx_status_get_seq(wil, msg));
	vअगर = wil->vअगरs[mid];

	अगर (unlikely(!vअगर)) अणु
		wil_dbg_txrx(wil, "RX descriptor with invalid mid %d", mid);
		वापस -EAGAIN;
	पूर्ण

	wil_dbg_txrx(wil,
		     "Non-data frame FC[7:0] 0x%02x MID %d CID %d TID %d Seq 0x%03x\n",
		     fc1, mid, cid, tid, seq);
	अगर (stats)
		stats->rx_non_data_frame++;
	अगर (wil_is_back_req(fc1)) अणु
		wil_dbg_txrx(wil,
			     "BAR: MID %d CID %d TID %d Seq 0x%03x\n",
			     mid, cid, tid, seq);
		wil_rx_bar(wil, vअगर, cid, tid, seq);
	पूर्ण अन्यथा अणु
		u32 sz = wil->use_compressed_rx_status ?
			माप(काष्ठा wil_rx_status_compressed) :
			माप(काष्ठा wil_rx_status_extended);

		/* prपूर्णांक again all info. One can enable only this
		 * without overhead क्रम prपूर्णांकing every Rx frame
		 */
		wil_dbg_txrx(wil,
			     "Unhandled non-data frame FC[7:0] 0x%02x MID %d CID %d TID %d Seq 0x%03x\n",
			     fc1, mid, cid, tid, seq);
		wil_hex_dump_txrx("RxS ", DUMP_PREFIX_NONE, 32, 4,
				  (स्थिर व्योम *)msg, sz, false);
		wil_hex_dump_txrx("Rx ", DUMP_PREFIX_OFFSET, 16, 1,
				  skb->data, skb_headlen(skb), false);
	पूर्ण

	वापस -EAGAIN;
पूर्ण

अटल पूर्णांक wil_rx_error_check_edma(काष्ठा wil6210_priv *wil,
				   काष्ठा sk_buff *skb,
				   काष्ठा wil_net_stats *stats)
अणु
	पूर्णांक l2_rx_status;
	व्योम *msg = wil_skb_rxstatus(skb);

	l2_rx_status = wil_rx_status_get_l2_rx_status(msg);
	अगर (l2_rx_status != 0) अणु
		wil_dbg_txrx(wil, "L2 RX error, l2_rx_status=0x%x\n",
			     l2_rx_status);
		/* Due to HW issue, KEY error will trigger a MIC error */
		अगर (l2_rx_status == WIL_RX_EDMA_ERROR_MIC) अणु
			wil_err_ratelimited(wil,
					    "L2 MIC/KEY error, dropping packet\n");
			stats->rx_mic_error++;
		पूर्ण
		अगर (l2_rx_status == WIL_RX_EDMA_ERROR_KEY) अणु
			wil_err_ratelimited(wil,
					    "L2 KEY error, dropping packet\n");
			stats->rx_key_error++;
		पूर्ण
		अगर (l2_rx_status == WIL_RX_EDMA_ERROR_REPLAY) अणु
			wil_err_ratelimited(wil,
					    "L2 REPLAY error, dropping packet\n");
			stats->rx_replay++;
		पूर्ण
		अगर (l2_rx_status == WIL_RX_EDMA_ERROR_AMSDU) अणु
			wil_err_ratelimited(wil,
					    "L2 AMSDU error, dropping packet\n");
			stats->rx_amsdu_error++;
		पूर्ण
		वापस -EFAULT;
	पूर्ण

	skb->ip_summed = wil_rx_status_get_checksum(msg, stats);

	वापस 0;
पूर्ण

अटल काष्ठा sk_buff *wil_sring_reap_rx_edma(काष्ठा wil6210_priv *wil,
					      काष्ठा wil_status_ring *sring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा wil_rx_status_extended msg1;
	व्योम *msg = &msg1;
	u16 buff_id;
	काष्ठा sk_buff *skb;
	dma_addr_t pa;
	काष्ठा wil_ring_rx_data *rxdata = &sring->rx_data;
	अचिन्हित पूर्णांक sz = wil->rx_buf_len;
	काष्ठा wil_net_stats *stats = शून्य;
	u16 dmalen;
	पूर्णांक cid;
	bool eop, headstolen;
	पूर्णांक delta;
	u8 dr_bit;
	u8 data_offset;
	काष्ठा wil_rx_status_extended *s;
	u16 sring_idx = sring - wil->srings;
	पूर्णांक invalid_buff_id_retry;

	BUILD_BUG_ON(माप(काष्ठा wil_rx_status_extended) > माप(skb->cb));

again:
	wil_get_next_rx_status_msg(sring, &dr_bit, msg);

	/* Completed handling all the पढ़ोy status messages */
	अगर (dr_bit != sring->desc_rdy_pol)
		वापस शून्य;

	/* Extract the buffer ID from the status message */
	buff_id = le16_to_cpu(wil_rx_status_get_buff_id(msg));

	invalid_buff_id_retry = 0;
	जबतक (!buff_id) अणु
		काष्ठा wil_rx_status_extended *s;

		wil_dbg_txrx(wil,
			     "buff_id is not updated yet by HW, (swhead 0x%x)\n",
			     sring->swhead);
		अगर (++invalid_buff_id_retry > MAX_INVALID_BUFF_ID_RETRY)
			अवरोध;

		/* Read the status message again */
		s = (काष्ठा wil_rx_status_extended *)
			(sring->va + (sring->elem_size * sring->swhead));
		*(काष्ठा wil_rx_status_extended *)msg = *s;
		buff_id = le16_to_cpu(wil_rx_status_get_buff_id(msg));
	पूर्ण

	अगर (unlikely(!wil_val_in_range(buff_id, 1, wil->rx_buff_mgmt.size))) अणु
		wil_err(wil, "Corrupt buff_id=%d, sring->swhead=%d\n",
			buff_id, sring->swhead);
		prपूर्णांक_hex_dump(KERN_ERR, "RxS ", DUMP_PREFIX_OFFSET, 16, 1,
			       msg, wil->use_compressed_rx_status ?
			       माप(काष्ठा wil_rx_status_compressed) :
			       माप(काष्ठा wil_rx_status_extended), false);

		wil_rx_status_reset_buff_id(sring);
		wil_sring_advance_swhead(sring);
		sring->invalid_buff_id_cnt++;
		जाओ again;
	पूर्ण

	/* Extract the SKB from the rx_buff management array */
	skb = wil->rx_buff_mgmt.buff_arr[buff_id].skb;
	wil->rx_buff_mgmt.buff_arr[buff_id].skb = शून्य;
	अगर (!skb) अणु
		wil_err(wil, "No Rx skb at buff_id %d\n", buff_id);
		wil_rx_status_reset_buff_id(sring);
		/* Move the buffer from the active list to the मुक्त list */
		list_move_tail(&wil->rx_buff_mgmt.buff_arr[buff_id].list,
			       &wil->rx_buff_mgmt.मुक्त);
		wil_sring_advance_swhead(sring);
		sring->invalid_buff_id_cnt++;
		जाओ again;
	पूर्ण

	wil_rx_status_reset_buff_id(sring);
	wil_sring_advance_swhead(sring);

	स_नकल(&pa, skb->cb, माप(pa));
	dma_unmap_single(dev, pa, sz, DMA_FROM_DEVICE);
	dmalen = le16_to_cpu(wil_rx_status_get_length(msg));

	trace_wil6210_rx_status(wil, wil->use_compressed_rx_status, buff_id,
				msg);
	wil_dbg_txrx(wil, "Rx, buff_id=%u, sring_idx=%u, dmalen=%u bytes\n",
		     buff_id, sring_idx, dmalen);
	wil_hex_dump_txrx("RxS ", DUMP_PREFIX_NONE, 32, 4,
			  (स्थिर व्योम *)msg, wil->use_compressed_rx_status ?
			  माप(काष्ठा wil_rx_status_compressed) :
			  माप(काष्ठा wil_rx_status_extended), false);

	/* Move the buffer from the active list to the मुक्त list */
	list_move_tail(&wil->rx_buff_mgmt.buff_arr[buff_id].list,
		       &wil->rx_buff_mgmt.मुक्त);

	eop = wil_rx_status_get_eop(msg);

	cid = wil_rx_status_get_cid(msg);
	अगर (unlikely(!wil_val_in_range(cid, 0, wil->max_assoc_sta))) अणु
		wil_err(wil, "Corrupt cid=%d, sring->swhead=%d\n",
			cid, sring->swhead);
		rxdata->skipping = true;
		जाओ skipping;
	पूर्ण
	stats = &wil->sta[cid].stats;

	अगर (unlikely(dmalen < ETH_HLEN)) अणु
		wil_dbg_txrx(wil, "Short frame, len = %d\n", dmalen);
		stats->rx_लघु_frame++;
		rxdata->skipping = true;
		जाओ skipping;
	पूर्ण

	अगर (unlikely(dmalen > sz)) अणु
		wil_err(wil, "Rx size too large: %d bytes!\n", dmalen);
		prपूर्णांक_hex_dump(KERN_ERR, "RxS ", DUMP_PREFIX_OFFSET, 16, 1,
			       msg, wil->use_compressed_rx_status ?
			       माप(काष्ठा wil_rx_status_compressed) :
			       माप(काष्ठा wil_rx_status_extended), false);

		stats->rx_large_frame++;
		rxdata->skipping = true;
	पूर्ण

skipping:
	/* skipping indicates अगर a certain SKB should be dropped.
	 * It is set in हाल there is an error on the current SKB or in हाल
	 * of RX chaining: as दीर्घ as we manage to merge the SKBs it will
	 * be false. once we have a bad SKB or we करोn't manage to merge SKBs
	 * it will be set to the !EOP value of the current SKB.
	 * This guarantees that all the following SKBs until EOP will also
	 * get dropped.
	 */
	अगर (unlikely(rxdata->skipping)) अणु
		kमुक्त_skb(skb);
		अगर (rxdata->skb) अणु
			kमुक्त_skb(rxdata->skb);
			rxdata->skb = शून्य;
		पूर्ण
		rxdata->skipping = !eop;
		जाओ again;
	पूर्ण

	skb_trim(skb, dmalen);

	prefetch(skb->data);

	अगर (!rxdata->skb) अणु
		rxdata->skb = skb;
	पूर्ण अन्यथा अणु
		अगर (likely(skb_try_coalesce(rxdata->skb, skb, &headstolen,
					    &delta))) अणु
			kमुक्त_skb_partial(skb, headstolen);
		पूर्ण अन्यथा अणु
			wil_err(wil, "failed to merge skbs!\n");
			kमुक्त_skb(skb);
			kमुक्त_skb(rxdata->skb);
			rxdata->skb = शून्य;
			rxdata->skipping = !eop;
			जाओ again;
		पूर्ण
	पूर्ण

	अगर (!eop)
		जाओ again;

	/* reaching here rxdata->skb always contains a full packet */
	skb = rxdata->skb;
	rxdata->skb = शून्य;
	rxdata->skipping = false;

	अगर (stats) अणु
		stats->last_mcs_rx = wil_rx_status_get_mcs(msg);
		अगर (stats->last_mcs_rx < ARRAY_SIZE(stats->rx_per_mcs))
			stats->rx_per_mcs[stats->last_mcs_rx]++;
		अन्यथा अगर (stats->last_mcs_rx == WIL_EXTENDED_MCS_26)
			stats->rx_per_mcs[WIL_BASE_MCS_FOR_EXTENDED_26]++;

		stats->last_cb_mode_rx  = wil_rx_status_get_cb_mode(msg);
	पूर्ण

	अगर (!wil->use_rx_hw_reordering && !wil->use_compressed_rx_status &&
	    wil_check_bar(wil, msg, cid, skb, stats) == -EAGAIN) अणु
		kमुक्त_skb(skb);
		जाओ again;
	पूर्ण

	/* Compensate क्रम the HW data alignment according to the status
	 * message
	 */
	data_offset = wil_rx_status_get_data_offset(msg);
	अगर (data_offset == 0xFF ||
	    data_offset > WIL_EDMA_MAX_DATA_OFFSET) अणु
		wil_err(wil, "Unexpected data offset %d\n", data_offset);
		kमुक्त_skb(skb);
		जाओ again;
	पूर्ण

	skb_pull(skb, data_offset);

	wil_hex_dump_txrx("Rx ", DUMP_PREFIX_OFFSET, 16, 1,
			  skb->data, skb_headlen(skb), false);

	/* Has to be करोne after dma_unmap_single as skb->cb is also
	 * used क्रम holding the pa
	 */
	s = wil_skb_rxstatus(skb);
	स_नकल(s, msg, sring->elem_size);

	वापस skb;
पूर्ण

व्योम wil_rx_handle_edma(काष्ठा wil6210_priv *wil, पूर्णांक *quota)
अणु
	काष्ठा net_device *ndev;
	काष्ठा wil_ring *ring = &wil->ring_rx;
	काष्ठा wil_status_ring *sring;
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	अगर (unlikely(!ring->va)) अणु
		wil_err(wil, "Rx IRQ while Rx not yet initialized\n");
		वापस;
	पूर्ण
	wil_dbg_txrx(wil, "rx_handle\n");

	क्रम (i = 0; i < wil->num_rx_status_rings; i++) अणु
		sring = &wil->srings[i];
		अगर (unlikely(!sring->va)) अणु
			wil_err(wil,
				"Rx IRQ while Rx status ring %d not yet initialized\n",
				i);
			जारी;
		पूर्ण

		जबतक ((*quota > 0) &&
		       (शून्य != (skb =
			wil_sring_reap_rx_edma(wil, sring)))) अणु
			(*quota)--;
			अगर (wil->use_rx_hw_reordering) अणु
				व्योम *msg = wil_skb_rxstatus(skb);
				पूर्णांक mid = wil_rx_status_get_mid(msg);
				काष्ठा wil6210_vअगर *vअगर = wil->vअगरs[mid];

				अगर (unlikely(!vअगर)) अणु
					wil_dbg_txrx(wil,
						     "RX desc invalid mid %d",
						     mid);
					kमुक्त_skb(skb);
					जारी;
				पूर्ण
				ndev = vअगर_to_ndev(vअगर);
				wil_netअगर_rx_any(skb, ndev);
			पूर्ण अन्यथा अणु
				wil_rx_reorder(wil, skb);
			पूर्ण
		पूर्ण

		wil_w(wil, sring->hwtail, (sring->swhead - 1) % sring->size);
	पूर्ण

	wil_rx_refill_edma(wil);
पूर्ण

अटल पूर्णांक wil_tx_desc_map_edma(जोड़ wil_tx_desc *desc,
				dma_addr_t pa,
				u32 len,
				पूर्णांक ring_index)
अणु
	काष्ठा wil_tx_enhanced_desc *d =
		(काष्ठा wil_tx_enhanced_desc *)&desc->enhanced;

	स_रखो(d, 0, माप(काष्ठा wil_tx_enhanced_desc));

	wil_desc_set_addr_edma(&d->dma.addr, &d->dma.addr_high_high, pa);

	/* 0..6: mac_length; 7:ip_version 0-IP6 1-IP4*/
	d->dma.length = cpu_to_le16((u16)len);
	d->mac.d[0] = (ring_index << WIL_EDMA_DESC_TX_MAC_CFG_0_QID_POS);
	/* translation type:  0 - bypass; 1 - 802.3; 2 - native wअगरi;
	 * 3 - eth mode
	 */
	d->mac.d[2] = BIT(MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_POS) |
		      (0x3 << MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_POS);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम
wil_get_next_tx_status_msg(काष्ठा wil_status_ring *sring, u8 *dr_bit,
			   काष्ठा wil_ring_tx_status *msg)
अणु
	काष्ठा wil_ring_tx_status *_msg = (काष्ठा wil_ring_tx_status *)
		(sring->va + (sring->elem_size * sring->swhead));

	*dr_bit = _msg->desc_पढ़ोy >> TX_STATUS_DESC_READY_POS;
	/* make sure dr_bit is पढ़ो beक्रमe the rest of status msg */
	rmb();
	*msg = *_msg;
पूर्ण

/* Clean up transmitted skb's from the Tx descriptor RING.
 * Return number of descriptors cleared.
 */
पूर्णांक wil_tx_sring_handler(काष्ठा wil6210_priv *wil,
			 काष्ठा wil_status_ring *sring)
अणु
	काष्ठा net_device *ndev;
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा wil_ring *ring = शून्य;
	काष्ठा wil_ring_tx_data *txdata;
	/* Total number of completed descriptors in all descriptor rings */
	पूर्णांक desc_cnt = 0;
	पूर्णांक cid;
	काष्ठा wil_net_stats *stats;
	काष्ठा wil_tx_enhanced_desc *_d;
	अचिन्हित पूर्णांक ring_id;
	अचिन्हित पूर्णांक num_descs, num_statuses = 0;
	पूर्णांक i;
	u8 dr_bit; /* Descriptor Ready bit */
	काष्ठा wil_ring_tx_status msg;
	काष्ठा wil6210_vअगर *vअगर;
	पूर्णांक used_beक्रमe_complete;
	पूर्णांक used_new;

	wil_get_next_tx_status_msg(sring, &dr_bit, &msg);

	/* Process completion messages जबतक DR bit has the expected polarity */
	जबतक (dr_bit == sring->desc_rdy_pol) अणु
		num_descs = msg.num_descriptors;
		अगर (!num_descs) अणु
			wil_err(wil, "invalid num_descs 0\n");
			जाओ again;
		पूर्ण

		/* Find the corresponding descriptor ring */
		ring_id = msg.ring_id;

		अगर (unlikely(ring_id >= WIL6210_MAX_TX_RINGS)) अणु
			wil_err(wil, "invalid ring id %d\n", ring_id);
			जाओ again;
		पूर्ण
		ring = &wil->ring_tx[ring_id];
		अगर (unlikely(!ring->va)) अणु
			wil_err(wil, "Tx irq[%d]: ring not initialized\n",
				ring_id);
			जाओ again;
		पूर्ण
		txdata = &wil->ring_tx_data[ring_id];
		अगर (unlikely(!txdata->enabled)) अणु
			wil_info(wil, "Tx irq[%d]: ring disabled\n", ring_id);
			जाओ again;
		पूर्ण
		vअगर = wil->vअगरs[txdata->mid];
		अगर (unlikely(!vअगर)) अणु
			wil_dbg_txrx(wil, "invalid MID %d for ring %d\n",
				     txdata->mid, ring_id);
			जाओ again;
		पूर्ण

		ndev = vअगर_to_ndev(vअगर);

		cid = wil->ring2cid_tid[ring_id][0];
		stats = (cid < wil->max_assoc_sta) ? &wil->sta[cid].stats :
						     शून्य;

		wil_dbg_txrx(wil,
			     "tx_status: completed desc_ring (%d), num_descs (%d)\n",
			     ring_id, num_descs);

		used_beक्रमe_complete = wil_ring_used_tx(ring);

		क्रम (i = 0 ; i < num_descs; ++i) अणु
			काष्ठा wil_ctx *ctx = &ring->ctx[ring->swtail];
			काष्ठा wil_tx_enhanced_desc dd, *d = &dd;
			u16 dmalen;
			काष्ठा sk_buff *skb = ctx->skb;

			_d = (काष्ठा wil_tx_enhanced_desc *)
				&ring->va[ring->swtail].tx.enhanced;
			*d = *_d;

			dmalen = le16_to_cpu(d->dma.length);
			trace_wil6210_tx_status(&msg, ring->swtail, dmalen);
			wil_dbg_txrx(wil,
				     "TxC[%2d][%3d] : %d bytes, status 0x%02x\n",
				     ring_id, ring->swtail, dmalen,
				     msg.status);
			wil_hex_dump_txrx("TxS ", DUMP_PREFIX_NONE, 32, 4,
					  (स्थिर व्योम *)&msg, माप(msg),
					  false);

			wil_tx_desc_unmap_edma(dev,
					       (जोड़ wil_tx_desc *)d,
					       ctx);

			अगर (skb) अणु
				अगर (likely(msg.status == 0)) अणु
					ndev->stats.tx_packets++;
					ndev->stats.tx_bytes += skb->len;
					अगर (stats) अणु
						stats->tx_packets++;
						stats->tx_bytes += skb->len;

						wil_tx_latency_calc(wil, skb,
							&wil->sta[cid]);
					पूर्ण
				पूर्ण अन्यथा अणु
					ndev->stats.tx_errors++;
					अगर (stats)
						stats->tx_errors++;
				पूर्ण

				अगर (skb->protocol == cpu_to_be16(ETH_P_PAE))
					wil_tx_complete_handle_eapol(vअगर, skb);

				wil_consume_skb(skb, msg.status == 0);
			पूर्ण
			स_रखो(ctx, 0, माप(*ctx));
			/* Make sure the ctx is zeroed beक्रमe updating the tail
			 * to prevent a हाल where wil_tx_ring will see
			 * this descriptor as used and handle it beक्रमe ctx zero
			 * is completed.
			 */
			wmb();

			ring->swtail = wil_ring_next_tail(ring);

			desc_cnt++;
		पूर्ण

		/* perक्रमmance monitoring */
		used_new = wil_ring_used_tx(ring);
		अगर (wil_val_in_range(wil->ring_idle_trsh,
				     used_new, used_beक्रमe_complete)) अणु
			wil_dbg_txrx(wil, "Ring[%2d] idle %d -> %d\n",
				     ring_id, used_beक्रमe_complete, used_new);
			txdata->last_idle = get_cycles();
		पूर्ण

again:
		num_statuses++;
		अगर (num_statuses % WIL_EDMA_TX_SRING_UPDATE_HW_TAIL == 0)
			/* update HW tail to allow HW to push new statuses */
			wil_w(wil, sring->hwtail, sring->swhead);

		wil_sring_advance_swhead(sring);

		wil_get_next_tx_status_msg(sring, &dr_bit, &msg);
	पूर्ण

	/* shall we wake net queues? */
	अगर (desc_cnt)
		wil_update_net_queues(wil, vअगर, शून्य, false);

	अगर (num_statuses % WIL_EDMA_TX_SRING_UPDATE_HW_TAIL != 0)
		/* Update the HW tail ptr (RD ptr) */
		wil_w(wil, sring->hwtail, (sring->swhead - 1) % sring->size);

	वापस desc_cnt;
पूर्ण

/* Sets the descriptor @d up क्रम csum and/or TSO offloading. The corresponding
 * @skb is used to obtain the protocol and headers length.
 * @tso_desc_type is a descriptor type क्रम TSO: 0 - a header, 1 - first data,
 * 2 - middle, 3 - last descriptor.
 */
अटल व्योम wil_tx_desc_offload_setup_tso_edma(काष्ठा wil_tx_enhanced_desc *d,
					       पूर्णांक tso_desc_type, bool is_ipv4,
					       पूर्णांक tcp_hdr_len,
					       पूर्णांक skb_net_hdr_len,
					       पूर्णांक mss)
अणु
	/* Number of descriptors */
	d->mac.d[2] |= 1;
	/* Maximum Segment Size */
	d->mac.tso_mss |= cpu_to_le16(mss >> 2);
	/* L4 header len: TCP header length */
	d->dma.l4_hdr_len |= tcp_hdr_len & DMA_CFG_DESC_TX_0_L4_LENGTH_MSK;
	/* EOP, TSO desc type, Segmentation enable,
	 * Insert IPv4 and TCP / UDP Checksum
	 */
	d->dma.cmd |= BIT(WIL_EDMA_DESC_TX_CFG_EOP_POS) |
		      tso_desc_type << WIL_EDMA_DESC_TX_CFG_TSO_DESC_TYPE_POS |
		      BIT(WIL_EDMA_DESC_TX_CFG_SEG_EN_POS) |
		      BIT(WIL_EDMA_DESC_TX_CFG_INSERT_IP_CHKSUM_POS) |
		      BIT(WIL_EDMA_DESC_TX_CFG_INSERT_TCP_CHKSUM_POS);
	/* Calculate pseuकरो-header */
	d->dma.w1 |= BIT(WIL_EDMA_DESC_TX_CFG_PSEUDO_HEADER_CALC_EN_POS) |
		     BIT(WIL_EDMA_DESC_TX_CFG_L4_TYPE_POS);
	/* IP Header Length */
	d->dma.ip_length |= skb_net_hdr_len;
	/* MAC header length and IP address family*/
	d->dma.b11 |= ETH_HLEN |
		      is_ipv4 << DMA_CFG_DESC_TX_OFFLOAD_CFG_L3T_IPV4_POS;
पूर्ण

अटल पूर्णांक wil_tx_tso_gen_desc(काष्ठा wil6210_priv *wil, व्योम *buff_addr,
			       पूर्णांक len, uपूर्णांक i, पूर्णांक tso_desc_type,
			       skb_frag_t *frag, काष्ठा wil_ring *ring,
			       काष्ठा sk_buff *skb, bool is_ipv4,
			       पूर्णांक tcp_hdr_len, पूर्णांक skb_net_hdr_len,
			       पूर्णांक mss, पूर्णांक *descs_used)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा wil_tx_enhanced_desc *_desc = (काष्ठा wil_tx_enhanced_desc *)
		&ring->va[i].tx.enhanced;
	काष्ठा wil_tx_enhanced_desc desc_mem, *d = &desc_mem;
	पूर्णांक ring_index = ring - wil->ring_tx;
	dma_addr_t pa;

	अगर (len == 0)
		वापस 0;

	अगर (!frag) अणु
		pa = dma_map_single(dev, buff_addr, len, DMA_TO_DEVICE);
		ring->ctx[i].mapped_as = wil_mapped_as_single;
	पूर्ण अन्यथा अणु
		pa = skb_frag_dma_map(dev, frag, 0, len, DMA_TO_DEVICE);
		ring->ctx[i].mapped_as = wil_mapped_as_page;
	पूर्ण
	अगर (unlikely(dma_mapping_error(dev, pa))) अणु
		wil_err(wil, "TSO: Skb DMA map error\n");
		वापस -EINVAL;
	पूर्ण

	wil->txrx_ops.tx_desc_map((जोड़ wil_tx_desc *)d, pa,
				   len, ring_index);
	wil_tx_desc_offload_setup_tso_edma(d, tso_desc_type, is_ipv4,
					   tcp_hdr_len,
					   skb_net_hdr_len, mss);

	/* hold reference to skb
	 * to prevent skb release beक्रमe accounting
	 * in हाल of immediate "tx done"
	 */
	अगर (tso_desc_type == wil_tso_type_lst)
		ring->ctx[i].skb = skb_get(skb);

	wil_hex_dump_txrx("TxD ", DUMP_PREFIX_NONE, 32, 4,
			  (स्थिर व्योम *)d, माप(*d), false);

	*_desc = *d;
	(*descs_used)++;

	वापस 0;
पूर्ण

अटल पूर्णांक __wil_tx_ring_tso_edma(काष्ठा wil6210_priv *wil,
				  काष्ठा wil6210_vअगर *vअगर,
				  काष्ठा wil_ring *ring,
				  काष्ठा sk_buff *skb)
अणु
	पूर्णांक ring_index = ring - wil->ring_tx;
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_index];
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक min_desc_required = nr_frags + 2; /* Headers, Head, Fragments */
	पूर्णांक used, avail = wil_ring_avail_tx(ring);
	पूर्णांक f, hdrlen, headlen;
	पूर्णांक gso_type;
	bool is_ipv4;
	u32 swhead = ring->swhead;
	पूर्णांक descs_used = 0; /* total number of used descriptors */
	पूर्णांक rc = -EINVAL;
	पूर्णांक tcp_hdr_len;
	पूर्णांक skb_net_hdr_len;
	पूर्णांक mss = skb_shinfo(skb)->gso_size;

	wil_dbg_txrx(wil, "tx_ring_tso: %d bytes to ring %d\n", skb->len,
		     ring_index);

	अगर (unlikely(!txdata->enabled))
		वापस -EINVAL;

	अगर (unlikely(avail < min_desc_required)) अणु
		wil_err_ratelimited(wil,
				    "TSO: Tx ring[%2d] full. No space for %d fragments\n",
				    ring_index, min_desc_required);
		वापस -ENOMEM;
	पूर्ण

	gso_type = skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV6 | SKB_GSO_TCPV4);
	चयन (gso_type) अणु
	हाल SKB_GSO_TCPV4:
		is_ipv4 = true;
		अवरोध;
	हाल SKB_GSO_TCPV6:
		is_ipv4 = false;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस -EINVAL;

	/* tcp header length and skb network header length are fixed क्रम all
	 * packet's descriptors - पढ़ो them once here
	 */
	tcp_hdr_len = tcp_hdrlen(skb);
	skb_net_hdr_len = skb_network_header_len(skb);

	/* First descriptor must contain the header only
	 * Header Length = MAC header len + IP header len + TCP header len
	 */
	hdrlen = ETH_HLEN + tcp_hdr_len + skb_net_hdr_len;
	wil_dbg_txrx(wil, "TSO: process header descriptor, hdrlen %u\n",
		     hdrlen);
	rc = wil_tx_tso_gen_desc(wil, skb->data, hdrlen, swhead,
				 wil_tso_type_hdr, शून्य, ring, skb,
				 is_ipv4, tcp_hdr_len, skb_net_hdr_len,
				 mss, &descs_used);
	अगर (rc)
		वापस -EINVAL;

	/* Second descriptor contains the head */
	headlen = skb_headlen(skb) - hdrlen;
	wil_dbg_txrx(wil, "TSO: process skb head, headlen %u\n", headlen);
	rc = wil_tx_tso_gen_desc(wil, skb->data + hdrlen, headlen,
				 (swhead + descs_used) % ring->size,
				 (nr_frags != 0) ? wil_tso_type_first :
				 wil_tso_type_lst, शून्य, ring, skb,
				 is_ipv4, tcp_hdr_len, skb_net_hdr_len,
				 mss, &descs_used);
	अगर (rc)
		जाओ mem_error;

	/* Rest of the descriptors are from the SKB fragments */
	क्रम (f = 0; f < nr_frags; f++) अणु
		skb_frag_t *frag = &skb_shinfo(skb)->frags[f];
		पूर्णांक len = skb_frag_size(frag);

		wil_dbg_txrx(wil, "TSO: frag[%d]: len %u, descs_used %d\n", f,
			     len, descs_used);

		rc = wil_tx_tso_gen_desc(wil, शून्य, len,
					 (swhead + descs_used) % ring->size,
					 (f != nr_frags - 1) ?
					 wil_tso_type_mid : wil_tso_type_lst,
					 frag, ring, skb, is_ipv4,
					 tcp_hdr_len, skb_net_hdr_len,
					 mss, &descs_used);
		अगर (rc)
			जाओ mem_error;
	पूर्ण

	/* perक्रमmance monitoring */
	used = wil_ring_used_tx(ring);
	अगर (wil_val_in_range(wil->ring_idle_trsh,
			     used, used + descs_used)) अणु
		txdata->idle += get_cycles() - txdata->last_idle;
		wil_dbg_txrx(wil,  "Ring[%2d] not idle %d -> %d\n",
			     ring_index, used, used + descs_used);
	पूर्ण

	/* advance swhead */
	wil_ring_advance_head(ring, descs_used);
	wil_dbg_txrx(wil, "TSO: Tx swhead %d -> %d\n", swhead, ring->swhead);

	/* make sure all ग_लिखोs to descriptors (shared memory) are करोne beक्रमe
	 * committing them to HW
	 */
	wmb();

	अगर (wil->tx_latency)
		*(kसमय_प्रकार *)&skb->cb = kसमय_get();
	अन्यथा
		स_रखो(skb->cb, 0, माप(kसमय_प्रकार));

	wil_w(wil, ring->hwtail, ring->swhead);

	वापस 0;

mem_error:
	जबतक (descs_used > 0) अणु
		काष्ठा device *dev = wil_to_dev(wil);
		काष्ठा wil_ctx *ctx;
		पूर्णांक i = (swhead + descs_used - 1) % ring->size;
		काष्ठा wil_tx_enhanced_desc dd, *d = &dd;
		काष्ठा wil_tx_enhanced_desc *_desc =
			(काष्ठा wil_tx_enhanced_desc *)
			&ring->va[i].tx.enhanced;

		*d = *_desc;
		ctx = &ring->ctx[i];
		wil_tx_desc_unmap_edma(dev, (जोड़ wil_tx_desc *)d, ctx);
		स_रखो(ctx, 0, माप(*ctx));
		descs_used--;
	पूर्ण
	वापस rc;
पूर्ण

अटल पूर्णांक wil_ring_init_bcast_edma(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id,
				    पूर्णांक size)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wil_ring *ring = &wil->ring_tx[ring_id];
	पूर्णांक rc;
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_id];

	wil_dbg_misc(wil, "init bcast: ring_id=%d, sring_id=%d\n",
		     ring_id, wil->tx_sring_idx);

	lockdep_निश्चित_held(&wil->mutex);

	wil_tx_data_init(txdata);
	ring->size = size;
	ring->is_rx = false;
	rc = wil_ring_alloc_desc_ring(wil, ring);
	अगर (rc)
		जाओ out;

	wil->ring2cid_tid[ring_id][0] = WIL6210_MAX_CID; /* CID */
	wil->ring2cid_tid[ring_id][1] = 0; /* TID */
	अगर (!vअगर->privacy)
		txdata->करोt1x_खोलो = true;

	rc = wil_wmi_bcast_desc_ring_add(vअगर, ring_id);
	अगर (rc)
		जाओ out_मुक्त;

	वापस 0;

 out_मुक्त:
	spin_lock_bh(&txdata->lock);
	txdata->enabled = 0;
	txdata->करोt1x_खोलो = false;
	spin_unlock_bh(&txdata->lock);
	wil_ring_मुक्त_edma(wil, ring);

out:
	वापस rc;
पूर्ण

अटल व्योम wil_tx_fini_edma(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil_status_ring *sring = &wil->srings[wil->tx_sring_idx];

	wil_dbg_misc(wil, "free TX sring\n");

	wil_sring_मुक्त(wil, sring);
पूर्ण

अटल व्योम wil_rx_data_मुक्त(काष्ठा wil_status_ring *sring)
अणु
	अगर (!sring)
		वापस;

	kमुक्त_skb(sring->rx_data.skb);
	sring->rx_data.skb = शून्य;
पूर्ण

अटल व्योम wil_rx_fini_edma(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil_ring *ring = &wil->ring_rx;
	पूर्णांक i;

	wil_dbg_misc(wil, "rx_fini_edma\n");

	wil_ring_मुक्त_edma(wil, ring);

	क्रम (i = 0; i < wil->num_rx_status_rings; i++) अणु
		wil_rx_data_मुक्त(&wil->srings[i]);
		wil_sring_मुक्त(wil, &wil->srings[i]);
	पूर्ण

	wil_मुक्त_rx_buff_arr(wil);
पूर्ण

व्योम wil_init_txrx_ops_edma(काष्ठा wil6210_priv *wil)
अणु
	wil->txrx_ops.configure_पूर्णांकerrupt_moderation =
		wil_configure_पूर्णांकerrupt_moderation_edma;
	/* TX ops */
	wil->txrx_ops.ring_init_tx = wil_ring_init_tx_edma;
	wil->txrx_ops.ring_fini_tx = wil_ring_मुक्त_edma;
	wil->txrx_ops.ring_init_bcast = wil_ring_init_bcast_edma;
	wil->txrx_ops.tx_init = wil_tx_init_edma;
	wil->txrx_ops.tx_fini = wil_tx_fini_edma;
	wil->txrx_ops.tx_desc_map = wil_tx_desc_map_edma;
	wil->txrx_ops.tx_desc_unmap = wil_tx_desc_unmap_edma;
	wil->txrx_ops.tx_ring_tso = __wil_tx_ring_tso_edma;
	wil->txrx_ops.tx_ring_modअगरy = wil_tx_ring_modअगरy_edma;
	/* RX ops */
	wil->txrx_ops.rx_init = wil_rx_init_edma;
	wil->txrx_ops.wmi_addba_rx_resp = wmi_addba_rx_resp_edma;
	wil->txrx_ops.get_reorder_params = wil_get_reorder_params_edma;
	wil->txrx_ops.get_netअगर_rx_params = wil_get_netअगर_rx_params_edma;
	wil->txrx_ops.rx_crypto_check = wil_rx_crypto_check_edma;
	wil->txrx_ops.rx_error_check = wil_rx_error_check_edma;
	wil->txrx_ops.is_rx_idle = wil_is_rx_idle_edma;
	wil->txrx_ops.rx_fini = wil_rx_fini_edma;
पूर्ण

