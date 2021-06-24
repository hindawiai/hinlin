<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/etherdevice.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/moduleparam.h>
#समावेश <linux/ip.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/ipv6.h>
#समावेश <linux/prefetch.h>

#समावेश "wil6210.h"
#समावेश "wmi.h"
#समावेश "txrx.h"
#समावेश "trace.h"
#समावेश "txrx_edma.h"

bool rx_align_2;
module_param(rx_align_2, bool, 0444);
MODULE_PARM_DESC(rx_align_2, " align Rx buffers on 4*n+2, default - no");

bool rx_large_buf;
module_param(rx_large_buf, bool, 0444);
MODULE_PARM_DESC(rx_large_buf, " allocate 8KB RX buffers, default - no");

/* Drop Tx packets in हाल Tx ring is full */
bool drop_अगर_ring_full;

अटल अंतरभूत uपूर्णांक wil_rx_snaplen(व्योम)
अणु
	वापस rx_align_2 ? 6 : 0;
पूर्ण

/* wil_ring_wmark_low - low watermark क्रम available descriptor space */
अटल अंतरभूत पूर्णांक wil_ring_wmark_low(काष्ठा wil_ring *ring)
अणु
	वापस ring->size / 8;
पूर्ण

/* wil_ring_wmark_high - high watermark क्रम available descriptor space */
अटल अंतरभूत पूर्णांक wil_ring_wmark_high(काष्ठा wil_ring *ring)
अणु
	वापस ring->size / 4;
पूर्ण

/* वापसs true अगर num avail descriptors is lower than wmark_low */
अटल अंतरभूत पूर्णांक wil_ring_avail_low(काष्ठा wil_ring *ring)
अणु
	वापस wil_ring_avail_tx(ring) < wil_ring_wmark_low(ring);
पूर्ण

/* वापसs true अगर num avail descriptors is higher than wmark_high */
अटल अंतरभूत पूर्णांक wil_ring_avail_high(काष्ठा wil_ring *ring)
अणु
	वापस wil_ring_avail_tx(ring) > wil_ring_wmark_high(ring);
पूर्ण

/* वापसs true when all tx vrings are empty */
bool wil_is_tx_idle(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक i;
	अचिन्हित दीर्घ data_comp_to;
	पूर्णांक min_ring_id = wil_get_min_tx_ring_id(wil);

	क्रम (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) अणु
		काष्ठा wil_ring *vring = &wil->ring_tx[i];
		पूर्णांक vring_index = vring - wil->ring_tx;
		काष्ठा wil_ring_tx_data *txdata =
			&wil->ring_tx_data[vring_index];

		spin_lock(&txdata->lock);

		अगर (!vring->va || !txdata->enabled) अणु
			spin_unlock(&txdata->lock);
			जारी;
		पूर्ण

		data_comp_to = jअगरfies + msecs_to_jअगरfies(
					WIL_DATA_COMPLETION_TO_MS);
		अगर (test_bit(wil_status_napi_en, wil->status)) अणु
			जबतक (!wil_ring_is_empty(vring)) अणु
				अगर (समय_after(jअगरfies, data_comp_to)) अणु
					wil_dbg_pm(wil,
						   "TO waiting for idle tx\n");
					spin_unlock(&txdata->lock);
					वापस false;
				पूर्ण
				wil_dbg_ratelimited(wil,
						    "tx vring is not empty -> NAPI\n");
				spin_unlock(&txdata->lock);
				napi_synchronize(&wil->napi_tx);
				msleep(20);
				spin_lock(&txdata->lock);
				अगर (!vring->va || !txdata->enabled)
					अवरोध;
			पूर्ण
		पूर्ण

		spin_unlock(&txdata->lock);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक wil_vring_alloc(काष्ठा wil6210_priv *wil, काष्ठा wil_ring *vring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	माप_प्रकार sz = vring->size * माप(vring->va[0]);
	uपूर्णांक i;

	wil_dbg_misc(wil, "vring_alloc:\n");

	BUILD_BUG_ON(माप(vring->va[0]) != 32);

	vring->swhead = 0;
	vring->swtail = 0;
	vring->ctx = kसुस्मृति(vring->size, माप(vring->ctx[0]), GFP_KERNEL);
	अगर (!vring->ctx) अणु
		vring->va = शून्य;
		वापस -ENOMEM;
	पूर्ण

	/* vring->va should be aligned on its size rounded up to घातer of 2
	 * This is granted by the dma_alloc_coherent.
	 *
	 * HW has limitation that all vrings addresses must share the same
	 * upper 16 msb bits part of 48 bits address. To workaround that,
	 * अगर we are using more than 32 bit addresses चयन to 32 bit
	 * allocation beक्रमe allocating vring memory.
	 *
	 * There's no check क्रम the वापस value of dma_set_mask_and_coherent,
	 * since we assume अगर we were able to set the mask during
	 * initialization in this प्रणाली it will not fail अगर we set it again
	 */
	अगर (wil->dma_addr_size > 32)
		dma_set_mask_and_coherent(dev, DMA_BIT_MASK(32));

	vring->va = dma_alloc_coherent(dev, sz, &vring->pa, GFP_KERNEL);
	अगर (!vring->va) अणु
		kमुक्त(vring->ctx);
		vring->ctx = शून्य;
		वापस -ENOMEM;
	पूर्ण

	अगर (wil->dma_addr_size > 32)
		dma_set_mask_and_coherent(dev,
					  DMA_BIT_MASK(wil->dma_addr_size));

	/* initially, all descriptors are SW owned
	 * For Tx and Rx, ownership bit is at the same location, thus
	 * we can use any
	 */
	क्रम (i = 0; i < vring->size; i++) अणु
		अस्थिर काष्ठा vring_tx_desc *_d =
			&vring->va[i].tx.legacy;

		_d->dma.status = TX_DMA_STATUS_DU;
	पूर्ण

	wil_dbg_misc(wil, "vring[%d] 0x%p:%pad 0x%p\n", vring->size,
		     vring->va, &vring->pa, vring->ctx);

	वापस 0;
पूर्ण

अटल व्योम wil_txdesc_unmap(काष्ठा device *dev, जोड़ wil_tx_desc *desc,
			     काष्ठा wil_ctx *ctx)
अणु
	काष्ठा vring_tx_desc *d = &desc->legacy;
	dma_addr_t pa = wil_desc_addr(&d->dma.addr);
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

अटल व्योम wil_vring_मुक्त(काष्ठा wil6210_priv *wil, काष्ठा wil_ring *vring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	माप_प्रकार sz = vring->size * माप(vring->va[0]);

	lockdep_निश्चित_held(&wil->mutex);
	अगर (!vring->is_rx) अणु
		पूर्णांक vring_index = vring - wil->ring_tx;

		wil_dbg_misc(wil, "free Tx vring %d [%d] 0x%p:%pad 0x%p\n",
			     vring_index, vring->size, vring->va,
			     &vring->pa, vring->ctx);
	पूर्ण अन्यथा अणु
		wil_dbg_misc(wil, "free Rx vring [%d] 0x%p:%pad 0x%p\n",
			     vring->size, vring->va,
			     &vring->pa, vring->ctx);
	पूर्ण

	जबतक (!wil_ring_is_empty(vring)) अणु
		dma_addr_t pa;
		u16 dmalen;
		काष्ठा wil_ctx *ctx;

		अगर (!vring->is_rx) अणु
			काष्ठा vring_tx_desc dd, *d = &dd;
			अस्थिर काष्ठा vring_tx_desc *_d =
					&vring->va[vring->swtail].tx.legacy;

			ctx = &vring->ctx[vring->swtail];
			अगर (!ctx) अणु
				wil_dbg_txrx(wil,
					     "ctx(%d) was already completed\n",
					     vring->swtail);
				vring->swtail = wil_ring_next_tail(vring);
				जारी;
			पूर्ण
			*d = *_d;
			wil_txdesc_unmap(dev, (जोड़ wil_tx_desc *)d, ctx);
			अगर (ctx->skb)
				dev_kमुक्त_skb_any(ctx->skb);
			vring->swtail = wil_ring_next_tail(vring);
		पूर्ण अन्यथा अणु /* rx */
			काष्ठा vring_rx_desc dd, *d = &dd;
			अस्थिर काष्ठा vring_rx_desc *_d =
				&vring->va[vring->swhead].rx.legacy;

			ctx = &vring->ctx[vring->swhead];
			*d = *_d;
			pa = wil_desc_addr(&d->dma.addr);
			dmalen = le16_to_cpu(d->dma.length);
			dma_unmap_single(dev, pa, dmalen, DMA_FROM_DEVICE);
			kमुक्त_skb(ctx->skb);
			wil_ring_advance_head(vring, 1);
		पूर्ण
	पूर्ण
	dma_मुक्त_coherent(dev, sz, (व्योम *)vring->va, vring->pa);
	kमुक्त(vring->ctx);
	vring->pa = 0;
	vring->va = शून्य;
	vring->ctx = शून्य;
पूर्ण

/* Allocate one skb क्रम Rx VRING
 *
 * Safe to call from IRQ
 */
अटल पूर्णांक wil_vring_alloc_skb(काष्ठा wil6210_priv *wil, काष्ठा wil_ring *vring,
			       u32 i, पूर्णांक headroom)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	अचिन्हित पूर्णांक sz = wil->rx_buf_len + ETH_HLEN + wil_rx_snaplen();
	काष्ठा vring_rx_desc dd, *d = &dd;
	अस्थिर काष्ठा vring_rx_desc *_d = &vring->va[i].rx.legacy;
	dma_addr_t pa;
	काष्ठा sk_buff *skb = dev_alloc_skb(sz + headroom);

	अगर (unlikely(!skb))
		वापस -ENOMEM;

	skb_reserve(skb, headroom);
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

	d->dma.d0 = RX_DMA_D0_CMD_DMA_RT | RX_DMA_D0_CMD_DMA_IT;
	wil_desc_addr_set(&d->dma.addr, pa);
	/* ip_length करोn't care */
	/* b11 करोn't care */
	/* error करोn't care */
	d->dma.status = 0; /* BIT(0) should be 0 क्रम HW_OWNED */
	d->dma.length = cpu_to_le16(sz);
	*_d = *d;
	vring->ctx[i].skb = skb;

	वापस 0;
पूर्ण

/* Adds radiotap header
 *
 * Any error indicated as "Bad FCS"
 *
 * Venकरोr data क्रम 04:ce:14-1 (Wilocity-1) consists of:
 *  - Rx descriptor: 32 bytes
 *  - Phy info
 */
अटल व्योम wil_rx_add_radiotap_header(काष्ठा wil6210_priv *wil,
				       काष्ठा sk_buff *skb)
अणु
	काष्ठा wil6210_rtap अणु
		काष्ठा ieee80211_radiotap_header rthdr;
		/* fields should be in the order of bits in rthdr.it_present */
		/* flags */
		u8 flags;
		/* channel */
		__le16 chnl_freq __aligned(2);
		__le16 chnl_flags;
		/* MCS */
		u8 mcs_present;
		u8 mcs_flags;
		u8 mcs_index;
	पूर्ण __packed;
	काष्ठा vring_rx_desc *d = wil_skb_rxdesc(skb);
	काष्ठा wil6210_rtap *rtap;
	पूर्णांक rtap_len = माप(काष्ठा wil6210_rtap);
	काष्ठा ieee80211_channel *ch = wil->monitor_chandef.chan;

	अगर (skb_headroom(skb) < rtap_len &&
	    pskb_expand_head(skb, rtap_len, 0, GFP_ATOMIC)) अणु
		wil_err(wil, "Unable to expand headroom to %d\n", rtap_len);
		वापस;
	पूर्ण

	rtap = skb_push(skb, rtap_len);
	स_रखो(rtap, 0, rtap_len);

	rtap->rthdr.it_version = PKTHDR_RADIOTAP_VERSION;
	rtap->rthdr.it_len = cpu_to_le16(rtap_len);
	rtap->rthdr.it_present = cpu_to_le32((1 << IEEE80211_RADIOTAP_FLAGS) |
			(1 << IEEE80211_RADIOTAP_CHANNEL) |
			(1 << IEEE80211_RADIOTAP_MCS));
	अगर (d->dma.status & RX_DMA_STATUS_ERROR)
		rtap->flags |= IEEE80211_RADIOTAP_F_BADFCS;

	rtap->chnl_freq = cpu_to_le16(ch ? ch->center_freq : 58320);
	rtap->chnl_flags = cpu_to_le16(0);

	rtap->mcs_present = IEEE80211_RADIOTAP_MCS_HAVE_MCS;
	rtap->mcs_flags = 0;
	rtap->mcs_index = wil_rxdesc_mcs(d);
पूर्ण

अटल bool wil_is_rx_idle(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा vring_rx_desc *_d;
	काष्ठा wil_ring *ring = &wil->ring_rx;

	_d = (काष्ठा vring_rx_desc *)&ring->va[ring->swhead].rx.legacy;
	अगर (_d->dma.status & RX_DMA_STATUS_DU)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक wil_rx_get_cid_by_skb(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb)
अणु
	काष्ठा vring_rx_desc *d = wil_skb_rxdesc(skb);
	पूर्णांक mid = wil_rxdesc_mid(d);
	काष्ठा wil6210_vअगर *vअगर = wil->vअगरs[mid];
	/* cid from DMA descriptor is limited to 3 bits.
	 * In हाल of cid>=8, the value would be cid modulo 8 and we need to
	 * find real cid by locating the transmitter (ta) inside sta array
	 */
	पूर्णांक cid = wil_rxdesc_cid(d);
	अचिन्हित पूर्णांक snaplen = wil_rx_snaplen();
	काष्ठा ieee80211_hdr_3addr *hdr;
	पूर्णांक i;
	अचिन्हित अक्षर *ta;
	u8 ftype;

	/* in monitor mode there are no connections */
	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_MONITOR)
		वापस cid;

	ftype = wil_rxdesc_ftype(d) << 2;
	अगर (likely(ftype == IEEE80211_FTYPE_DATA)) अणु
		अगर (unlikely(skb->len < ETH_HLEN + snaplen)) अणु
			wil_err_ratelimited(wil,
					    "Short data frame, len = %d\n",
					    skb->len);
			वापस -ENOENT;
		पूर्ण
		ta = wil_skb_get_sa(skb);
	पूर्ण अन्यथा अणु
		अगर (unlikely(skb->len < माप(काष्ठा ieee80211_hdr_3addr))) अणु
			wil_err_ratelimited(wil, "Short frame, len = %d\n",
					    skb->len);
			वापस -ENOENT;
		पूर्ण
		hdr = (व्योम *)skb->data;
		ta = hdr->addr2;
	पूर्ण

	अगर (wil->max_assoc_sta <= WIL6210_RX_DESC_MAX_CID)
		वापस cid;

	/* assuming no concurrency between AP पूर्णांकerfaces and STA पूर्णांकerfaces.
	 * multista is used only in P2P_GO or AP mode. In other modes वापस
	 * cid from the rx descriptor
	 */
	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_P2P_GO &&
	    vअगर->wdev.अगरtype != NL80211_IFTYPE_AP)
		वापस cid;

	/* For Rx packets cid from rx descriptor is limited to 3 bits (0..7),
	 * to find the real cid, compare transmitter address with the stored
	 * stations mac address in the driver sta array
	 */
	क्रम (i = cid; i < wil->max_assoc_sta; i += WIL6210_RX_DESC_MAX_CID) अणु
		अगर (wil->sta[i].status != wil_sta_unused &&
		    ether_addr_equal(wil->sta[i].addr, ta)) अणु
			cid = i;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (i >= wil->max_assoc_sta) अणु
		wil_err_ratelimited(wil, "Could not find cid for frame with transmit addr = %pM, iftype = %d, frametype = %d, len = %d\n",
				    ta, vअगर->wdev.अगरtype, ftype, skb->len);
		cid = -ENOENT;
	पूर्ण

	वापस cid;
पूर्ण

/* reap 1 frame from @swhead
 *
 * Rx descriptor copied to skb->cb
 *
 * Safe to call from IRQ
 */
अटल काष्ठा sk_buff *wil_vring_reap_rx(काष्ठा wil6210_priv *wil,
					 काष्ठा wil_ring *vring)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा wil6210_vअगर *vअगर;
	काष्ठा net_device *ndev;
	अस्थिर काष्ठा vring_rx_desc *_d;
	काष्ठा vring_rx_desc *d;
	काष्ठा sk_buff *skb;
	dma_addr_t pa;
	अचिन्हित पूर्णांक snaplen = wil_rx_snaplen();
	अचिन्हित पूर्णांक sz = wil->rx_buf_len + ETH_HLEN + snaplen;
	u16 dmalen;
	u8 ftype;
	पूर्णांक cid, mid;
	पूर्णांक i;
	काष्ठा wil_net_stats *stats;

	BUILD_BUG_ON(माप(काष्ठा skb_rx_info) > माप(skb->cb));

again:
	अगर (unlikely(wil_ring_is_empty(vring)))
		वापस शून्य;

	i = (पूर्णांक)vring->swhead;
	_d = &vring->va[i].rx.legacy;
	अगर (unlikely(!(_d->dma.status & RX_DMA_STATUS_DU))) अणु
		/* it is not error, we just reached end of Rx करोne area */
		वापस शून्य;
	पूर्ण

	skb = vring->ctx[i].skb;
	vring->ctx[i].skb = शून्य;
	wil_ring_advance_head(vring, 1);
	अगर (!skb) अणु
		wil_err(wil, "No Rx skb at [%d]\n", i);
		जाओ again;
	पूर्ण
	d = wil_skb_rxdesc(skb);
	*d = *_d;
	pa = wil_desc_addr(&d->dma.addr);

	dma_unmap_single(dev, pa, sz, DMA_FROM_DEVICE);
	dmalen = le16_to_cpu(d->dma.length);

	trace_wil6210_rx(i, d);
	wil_dbg_txrx(wil, "Rx[%3d] : %d bytes\n", i, dmalen);
	wil_hex_dump_txrx("RxD ", DUMP_PREFIX_NONE, 32, 4,
			  (स्थिर व्योम *)d, माप(*d), false);

	mid = wil_rxdesc_mid(d);
	vअगर = wil->vअगरs[mid];

	अगर (unlikely(!vअगर)) अणु
		wil_dbg_txrx(wil, "skipped RX descriptor with invalid mid %d",
			     mid);
		kमुक्त_skb(skb);
		जाओ again;
	पूर्ण
	ndev = vअगर_to_ndev(vअगर);
	अगर (unlikely(dmalen > sz)) अणु
		wil_err_ratelimited(wil, "Rx size too large: %d bytes!\n",
				    dmalen);
		kमुक्त_skb(skb);
		जाओ again;
	पूर्ण
	skb_trim(skb, dmalen);

	prefetch(skb->data);

	wil_hex_dump_txrx("Rx ", DUMP_PREFIX_OFFSET, 16, 1,
			  skb->data, skb_headlen(skb), false);

	cid = wil_rx_get_cid_by_skb(wil, skb);
	अगर (cid == -ENOENT) अणु
		kमुक्त_skb(skb);
		जाओ again;
	पूर्ण
	wil_skb_set_cid(skb, (u8)cid);
	stats = &wil->sta[cid].stats;

	stats->last_mcs_rx = wil_rxdesc_mcs(d);
	अगर (stats->last_mcs_rx < ARRAY_SIZE(stats->rx_per_mcs))
		stats->rx_per_mcs[stats->last_mcs_rx]++;

	/* use radiotap header only अगर required */
	अगर (ndev->type == ARPHRD_IEEE80211_RADIOTAP)
		wil_rx_add_radiotap_header(wil, skb);

	/* no extra checks अगर in snअगरfer mode */
	अगर (ndev->type != ARPHRD_ETHER)
		वापस skb;
	/* Non-data frames may be delivered through Rx DMA channel (ex: BAR)
	 * Driver should recognize it by frame type, that is found
	 * in Rx descriptor. If type is not data, it is 802.11 frame as is
	 */
	ftype = wil_rxdesc_ftype(d) << 2;
	अगर (unlikely(ftype != IEEE80211_FTYPE_DATA)) अणु
		u8 fc1 = wil_rxdesc_fc1(d);
		पूर्णांक tid = wil_rxdesc_tid(d);
		u16 seq = wil_rxdesc_seq(d);

		wil_dbg_txrx(wil,
			     "Non-data frame FC[7:0] 0x%02x MID %d CID %d TID %d Seq 0x%03x\n",
			     fc1, mid, cid, tid, seq);
		stats->rx_non_data_frame++;
		अगर (wil_is_back_req(fc1)) अणु
			wil_dbg_txrx(wil,
				     "BAR: MID %d CID %d TID %d Seq 0x%03x\n",
				     mid, cid, tid, seq);
			wil_rx_bar(wil, vअगर, cid, tid, seq);
		पूर्ण अन्यथा अणु
			/* prपूर्णांक again all info. One can enable only this
			 * without overhead क्रम prपूर्णांकing every Rx frame
			 */
			wil_dbg_txrx(wil,
				     "Unhandled non-data frame FC[7:0] 0x%02x MID %d CID %d TID %d Seq 0x%03x\n",
				     fc1, mid, cid, tid, seq);
			wil_hex_dump_txrx("RxD ", DUMP_PREFIX_NONE, 32, 4,
					  (स्थिर व्योम *)d, माप(*d), false);
			wil_hex_dump_txrx("Rx ", DUMP_PREFIX_OFFSET, 16, 1,
					  skb->data, skb_headlen(skb), false);
		पूर्ण
		kमुक्त_skb(skb);
		जाओ again;
	पूर्ण

	/* L4 IDENT is on when HW calculated checksum, check status
	 * and in हाल of error drop the packet
	 * higher stack layers will handle retransmission (अगर required)
	 */
	अगर (likely(d->dma.status & RX_DMA_STATUS_L4I)) अणु
		/* L4 protocol identअगरied, csum calculated */
		अगर (likely((d->dma.error & RX_DMA_ERROR_L4_ERR) == 0))
			skb->ip_summed = CHECKSUM_UNNECESSARY;
		/* If HW reports bad checksum, let IP stack re-check it
		 * For example, HW करोn't understand Microsoft IP stack that
		 * mis-calculates TCP checksum - अगर it should be 0x0,
		 * it ग_लिखोs 0xffff in violation of RFC 1624
		 */
		अन्यथा
			stats->rx_csum_err++;
	पूर्ण

	अगर (snaplen) अणु
		/* Packet layout
		 * +-------+-------+---------+------------+------+
		 * | SA(6) | DA(6) | SNAP(6) | ETHTYPE(2) | DATA |
		 * +-------+-------+---------+------------+------+
		 * Need to हटाओ SNAP, shअगरting SA and DA क्रमward
		 */
		स_हटाओ(skb->data + snaplen, skb->data, 2 * ETH_ALEN);
		skb_pull(skb, snaplen);
	पूर्ण

	वापस skb;
पूर्ण

/* allocate and fill up to @count buffers in rx ring
 * buffers posted at @swtail
 * Note: we have a single RX queue क्रम servicing all VIFs, but we
 * allocate skbs with headroom according to मुख्य पूर्णांकerface only. This
 * means it will not work with monitor पूर्णांकerface together with other VIFs.
 * Currently we only support monitor पूर्णांकerface on its own without other VIFs,
 * and we will need to fix this code once we add support.
 */
अटल पूर्णांक wil_rx_refill(काष्ठा wil6210_priv *wil, पूर्णांक count)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wil_ring *v = &wil->ring_rx;
	u32 next_tail;
	पूर्णांक rc = 0;
	पूर्णांक headroom = ndev->type == ARPHRD_IEEE80211_RADIOTAP ?
			WIL6210_RTAP_SIZE : 0;

	क्रम (; next_tail = wil_ring_next_tail(v),
	     (next_tail != v->swhead) && (count-- > 0);
	     v->swtail = next_tail) अणु
		rc = wil_vring_alloc_skb(wil, v, v->swtail, headroom);
		अगर (unlikely(rc)) अणु
			wil_err_ratelimited(wil, "Error %d in rx refill[%d]\n",
					    rc, v->swtail);
			अवरोध;
		पूर्ण
	पूर्ण

	/* make sure all ग_लिखोs to descriptors (shared memory) are करोne beक्रमe
	 * committing them to HW
	 */
	wmb();

	wil_w(wil, v->hwtail, v->swtail);

	वापस rc;
पूर्ण

/**
 * reverse_स_भेद - Compare two areas of memory, in reverse order
 * @cs: One area of memory
 * @ct: Another area of memory
 * @count: The size of the area.
 *
 * Cut'n'paste from original स_भेद (see lib/string.c)
 * with minimal modअगरications
 */
पूर्णांक reverse_स_भेद(स्थिर व्योम *cs, स्थिर व्योम *ct, माप_प्रकार count)
अणु
	स्थिर अचिन्हित अक्षर *su1, *su2;
	पूर्णांक res = 0;

	क्रम (su1 = cs + count - 1, su2 = ct + count - 1; count > 0;
	     --su1, --su2, count--) अणु
		res = *su1 - *su2;
		अगर (res)
			अवरोध;
	पूर्ण
	वापस res;
पूर्ण

अटल पूर्णांक wil_rx_crypto_check(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb)
अणु
	काष्ठा vring_rx_desc *d = wil_skb_rxdesc(skb);
	पूर्णांक cid = wil_skb_get_cid(skb);
	पूर्णांक tid = wil_rxdesc_tid(d);
	पूर्णांक key_id = wil_rxdesc_key_id(d);
	पूर्णांक mc = wil_rxdesc_mcast(d);
	काष्ठा wil_sta_info *s = &wil->sta[cid];
	काष्ठा wil_tid_crypto_rx *c = mc ? &s->group_crypto_rx :
				      &s->tid_crypto_rx[tid];
	काष्ठा wil_tid_crypto_rx_single *cc = &c->key_id[key_id];
	स्थिर u8 *pn = (u8 *)&d->mac.pn_15_0;

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

अटल पूर्णांक wil_rx_error_check(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb,
			      काष्ठा wil_net_stats *stats)
अणु
	काष्ठा vring_rx_desc *d = wil_skb_rxdesc(skb);

	अगर ((d->dma.status & RX_DMA_STATUS_ERROR) &&
	    (d->dma.error & RX_DMA_ERROR_MIC)) अणु
		stats->rx_mic_error++;
		wil_dbg_txrx(wil, "MIC error, dropping packet\n");
		वापस -EFAULT;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wil_get_netअगर_rx_params(काष्ठा sk_buff *skb, पूर्णांक *cid,
				    पूर्णांक *security)
अणु
	काष्ठा vring_rx_desc *d = wil_skb_rxdesc(skb);

	*cid = wil_skb_get_cid(skb);
	*security = wil_rxdesc_security(d);
पूर्ण

/*
 * Check अगर skb is ptk eapol key message
 *
 * वापसs a poपूर्णांकer to the start of the eapol key काष्ठाure, शून्य
 * अगर frame is not PTK eapol key
 */
अटल काष्ठा wil_eapol_key *wil_is_ptk_eapol_key(काष्ठा wil6210_priv *wil,
						  काष्ठा sk_buff *skb)
अणु
	u8 *buf;
	स्थिर काष्ठा wil_1x_hdr *hdr;
	काष्ठा wil_eapol_key *key;
	u16 key_info;
	पूर्णांक len = skb->len;

	अगर (!skb_mac_header_was_set(skb)) अणु
		wil_err(wil, "mac header was not set\n");
		वापस शून्य;
	पूर्ण

	len -= skb_mac_offset(skb);

	अगर (len < माप(काष्ठा ethhdr) + माप(काष्ठा wil_1x_hdr) +
	    माप(काष्ठा wil_eapol_key))
		वापस शून्य;

	buf = skb_mac_header(skb) + माप(काष्ठा ethhdr);

	hdr = (स्थिर काष्ठा wil_1x_hdr *)buf;
	अगर (hdr->type != WIL_1X_TYPE_EAPOL_KEY)
		वापस शून्य;

	key = (काष्ठा wil_eapol_key *)(buf + माप(काष्ठा wil_1x_hdr));
	अगर (key->type != WIL_EAPOL_KEY_TYPE_WPA &&
	    key->type != WIL_EAPOL_KEY_TYPE_RSN)
		वापस शून्य;

	key_info = be16_to_cpu(key->key_info);
	अगर (!(key_info & WIL_KEY_INFO_KEY_TYPE)) /* check अगर pairwise */
		वापस शून्य;

	वापस key;
पूर्ण

अटल bool wil_skb_is_eap_3(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb)
अणु
	काष्ठा wil_eapol_key *key;
	u16 key_info;

	key = wil_is_ptk_eapol_key(wil, skb);
	अगर (!key)
		वापस false;

	key_info = be16_to_cpu(key->key_info);
	अगर (key_info & (WIL_KEY_INFO_MIC |
			WIL_KEY_INFO_ENCR_KEY_DATA)) अणु
		/* 3/4 of 4-Way Handshake */
		wil_dbg_misc(wil, "EAPOL key message 3\n");
		वापस true;
	पूर्ण
	/* 1/4 of 4-Way Handshake */
	wil_dbg_misc(wil, "EAPOL key message 1\n");

	वापस false;
पूर्ण

अटल bool wil_skb_is_eap_4(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb)
अणु
	काष्ठा wil_eapol_key *key;
	u32 *nonce, i;

	key = wil_is_ptk_eapol_key(wil, skb);
	अगर (!key)
		वापस false;

	nonce = (u32 *)key->key_nonce;
	क्रम (i = 0; i < WIL_EAP_NONCE_LEN / माप(u32); i++, nonce++) अणु
		अगर (*nonce != 0) अणु
			/* message 2/4 */
			wil_dbg_misc(wil, "EAPOL key message 2\n");
			वापस false;
		पूर्ण
	पूर्ण
	wil_dbg_misc(wil, "EAPOL key message 4\n");

	वापस true;
पूर्ण

व्योम wil_enable_tx_key_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wil6210_vअगर *vअगर = container_of(work,
			काष्ठा wil6210_vअगर, enable_tx_key_worker);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc, cid;

	rtnl_lock();
	अगर (vअगर->ptk_rekey_state != WIL_REKEY_WAIT_M4_SENT) अणु
		wil_dbg_misc(wil, "Invalid rekey state = %d\n",
			     vअगर->ptk_rekey_state);
		rtnl_unlock();
		वापस;
	पूर्ण

	cid =  wil_find_cid_by_idx(wil, vअगर->mid, 0);
	अगर (!wil_cid_valid(wil, cid)) अणु
		wil_err(wil, "Invalid cid = %d\n", cid);
		rtnl_unlock();
		वापस;
	पूर्ण

	wil_dbg_misc(wil, "Apply PTK key after eapol was sent out\n");
	rc = wmi_add_cipher_key(vअगर, 0, wil->sta[cid].addr, 0, शून्य,
				WMI_KEY_USE_APPLY_PTK);

	vअगर->ptk_rekey_state = WIL_REKEY_IDLE;
	rtnl_unlock();

	अगर (rc)
		wil_err(wil, "Apply PTK key failed %d\n", rc);
पूर्ण

व्योम wil_tx_complete_handle_eapol(काष्ठा wil6210_vअगर *vअगर, काष्ठा sk_buff *skb)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	bool q = false;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION ||
	    !test_bit(WMI_FW_CAPABILITY_SPLIT_REKEY, wil->fw_capabilities))
		वापस;

	/* check अगर skb is an EAP message 4/4 */
	अगर (!wil_skb_is_eap_4(wil, skb))
		वापस;

	spin_lock_bh(&wil->eap_lock);
	चयन (vअगर->ptk_rekey_state) अणु
	हाल WIL_REKEY_IDLE:
		/* ignore idle state, can happen due to M4 retransmission */
		अवरोध;
	हाल WIL_REKEY_M3_RECEIVED:
		vअगर->ptk_rekey_state = WIL_REKEY_IDLE;
		अवरोध;
	हाल WIL_REKEY_WAIT_M4_SENT:
		q = true;
		अवरोध;
	शेष:
		wil_err(wil, "Unknown rekey state = %d",
			vअगर->ptk_rekey_state);
	पूर्ण
	spin_unlock_bh(&wil->eap_lock);

	अगर (q) अणु
		q = queue_work(wil->wmi_wq, &vअगर->enable_tx_key_worker);
		wil_dbg_misc(wil, "queue_work of enable_tx_key_worker -> %d\n",
			     q);
	पूर्ण
पूर्ण

अटल व्योम wil_rx_handle_eapol(काष्ठा wil6210_vअगर *vअगर, काष्ठा sk_buff *skb)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION ||
	    !test_bit(WMI_FW_CAPABILITY_SPLIT_REKEY, wil->fw_capabilities))
		वापस;

	/* check अगर skb is a EAP message 3/4 */
	अगर (!wil_skb_is_eap_3(wil, skb))
		वापस;

	अगर (vअगर->ptk_rekey_state == WIL_REKEY_IDLE)
		vअगर->ptk_rekey_state = WIL_REKEY_M3_RECEIVED;
पूर्ण

/*
 * Pass Rx packet to the netअगर. Update statistics.
 * Called in softirq context (NAPI poll).
 */
व्योम wil_netअगर_rx(काष्ठा sk_buff *skb, काष्ठा net_device *ndev, पूर्णांक cid,
		  काष्ठा wil_net_stats *stats, bool gro)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wil6210_priv *wil = ndev_to_wil(ndev);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	अचिन्हित पूर्णांक len = skb->len;
	u8 *sa, *da = wil_skb_get_da(skb);
	/* here looking क्रम DA, not A1, thus Rxdesc's 'mcast' indication
	 * is not suitable, need to look at data
	 */
	पूर्णांक mcast = is_multicast_ether_addr(da);
	काष्ठा sk_buff *xmit_skb = शून्य;

	अगर (wdev->अगरtype == NL80211_IFTYPE_STATION) अणु
		sa = wil_skb_get_sa(skb);
		अगर (mcast && ether_addr_equal(sa, ndev->dev_addr)) अणु
			/* mcast packet looped back to us */
			dev_kमुक्त_skb(skb);
			ndev->stats.rx_dropped++;
			stats->rx_dropped++;
			wil_dbg_txrx(wil, "Rx drop %d bytes\n", len);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अगर (wdev->अगरtype == NL80211_IFTYPE_AP && !vअगर->ap_isolate) अणु
		अगर (mcast) अणु
			/* send multicast frames both to higher layers in
			 * local net stack and back to the wireless medium
			 */
			xmit_skb = skb_copy(skb, GFP_ATOMIC);
		पूर्ण अन्यथा अणु
			पूर्णांक xmit_cid = wil_find_cid(wil, vअगर->mid, da);

			अगर (xmit_cid >= 0) अणु
				/* The destination station is associated to
				 * this AP (in this VLAN), so send the frame
				 * directly to it and करो not pass it to local
				 * net stack.
				 */
				xmit_skb = skb;
				skb = शून्य;
			पूर्ण
		पूर्ण
	पूर्ण
	अगर (xmit_skb) अणु
		/* Send to wireless media and increase priority by 256 to
		 * keep the received priority instead of reclassअगरying
		 * the frame (see cfg80211_classअगरy8021d).
		 */
		xmit_skb->dev = ndev;
		xmit_skb->priority += 256;
		xmit_skb->protocol = htons(ETH_P_802_3);
		skb_reset_network_header(xmit_skb);
		skb_reset_mac_header(xmit_skb);
		wil_dbg_txrx(wil, "Rx -> Tx %d bytes\n", len);
		dev_queue_xmit(xmit_skb);
	पूर्ण

	अगर (skb) अणु /* deliver to local stack */
		skb->protocol = eth_type_trans(skb, ndev);
		skb->dev = ndev;

		अगर (skb->protocol == cpu_to_be16(ETH_P_PAE))
			wil_rx_handle_eapol(vअगर, skb);

		अगर (gro)
			napi_gro_receive(&wil->napi_rx, skb);
		अन्यथा
			netअगर_rx_ni(skb);
	पूर्ण
	ndev->stats.rx_packets++;
	stats->rx_packets++;
	ndev->stats.rx_bytes += len;
	stats->rx_bytes += len;
	अगर (mcast)
		ndev->stats.multicast++;
पूर्ण

व्योम wil_netअगर_rx_any(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	पूर्णांक cid, security;
	काष्ठा wil6210_priv *wil = ndev_to_wil(ndev);
	काष्ठा wil_net_stats *stats;

	wil->txrx_ops.get_netअगर_rx_params(skb, &cid, &security);

	stats = &wil->sta[cid].stats;

	skb_orphan(skb);

	अगर (security && (wil->txrx_ops.rx_crypto_check(wil, skb) != 0)) अणु
		wil_dbg_txrx(wil, "Rx drop %d bytes\n", skb->len);
		dev_kमुक्त_skb(skb);
		ndev->stats.rx_dropped++;
		stats->rx_replay++;
		stats->rx_dropped++;
		वापस;
	पूर्ण

	/* check errors reported by HW and update statistics */
	अगर (unlikely(wil->txrx_ops.rx_error_check(wil, skb, stats))) अणु
		dev_kमुक्त_skb(skb);
		वापस;
	पूर्ण

	wil_netअगर_rx(skb, ndev, cid, stats, true);
पूर्ण

/* Proceed all completed skb's from Rx VRING
 *
 * Safe to call from NAPI poll, i.e. softirq with पूर्णांकerrupts enabled
 */
व्योम wil_rx_handle(काष्ठा wil6210_priv *wil, पूर्णांक *quota)
अणु
	काष्ठा net_device *ndev = wil->मुख्य_ndev;
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	काष्ठा wil_ring *v = &wil->ring_rx;
	काष्ठा sk_buff *skb;

	अगर (unlikely(!v->va)) अणु
		wil_err(wil, "Rx IRQ while Rx not yet initialized\n");
		वापस;
	पूर्ण
	wil_dbg_txrx(wil, "rx_handle\n");
	जबतक ((*quota > 0) && (शून्य != (skb = wil_vring_reap_rx(wil, v)))) अणु
		(*quota)--;

		/* monitor is currently supported on मुख्य पूर्णांकerface only */
		अगर (wdev->अगरtype == NL80211_IFTYPE_MONITOR) अणु
			skb->dev = ndev;
			skb_reset_mac_header(skb);
			skb->ip_summed = CHECKSUM_UNNECESSARY;
			skb->pkt_type = PACKET_OTHERHOST;
			skb->protocol = htons(ETH_P_802_2);
			wil_netअगर_rx_any(skb, ndev);
		पूर्ण अन्यथा अणु
			wil_rx_reorder(wil, skb);
		पूर्ण
	पूर्ण
	wil_rx_refill(wil, v->size);
पूर्ण

अटल व्योम wil_rx_buf_len_init(काष्ठा wil6210_priv *wil)
अणु
	wil->rx_buf_len = rx_large_buf ?
		WIL_MAX_ETH_MTU : TXRX_BUF_LEN_DEFAULT - WIL_MAX_MPDU_OVERHEAD;
	अगर (mtu_max > wil->rx_buf_len) अणु
		/* करो not allow RX buffers to be smaller than mtu_max, क्रम
		 * backward compatibility (mtu_max parameter was also used
		 * to support receiving large packets)
		 */
		wil_info(wil, "Override RX buffer to mtu_max(%d)\n", mtu_max);
		wil->rx_buf_len = mtu_max;
	पूर्ण
पूर्ण

अटल पूर्णांक wil_rx_init(काष्ठा wil6210_priv *wil, uपूर्णांक order)
अणु
	काष्ठा wil_ring *vring = &wil->ring_rx;
	पूर्णांक rc;

	wil_dbg_misc(wil, "rx_init\n");

	अगर (vring->va) अणु
		wil_err(wil, "Rx ring already allocated\n");
		वापस -EINVAL;
	पूर्ण

	wil_rx_buf_len_init(wil);

	vring->size = 1 << order;
	vring->is_rx = true;
	rc = wil_vring_alloc(wil, vring);
	अगर (rc)
		वापस rc;

	rc = wmi_rx_chain_add(wil, vring);
	अगर (rc)
		जाओ err_मुक्त;

	rc = wil_rx_refill(wil, vring->size);
	अगर (rc)
		जाओ err_मुक्त;

	वापस 0;
 err_मुक्त:
	wil_vring_मुक्त(wil, vring);

	वापस rc;
पूर्ण

अटल व्योम wil_rx_fini(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wil_ring *vring = &wil->ring_rx;

	wil_dbg_misc(wil, "rx_fini\n");

	अगर (vring->va)
		wil_vring_मुक्त(wil, vring);
पूर्ण

अटल पूर्णांक wil_tx_desc_map(जोड़ wil_tx_desc *desc, dma_addr_t pa,
			   u32 len, पूर्णांक vring_index)
अणु
	काष्ठा vring_tx_desc *d = &desc->legacy;

	wil_desc_addr_set(&d->dma.addr, pa);
	d->dma.ip_length = 0;
	/* 0..6: mac_length; 7:ip_version 0-IP6 1-IP4*/
	d->dma.b11 = 0/*14 | BIT(7)*/;
	d->dma.error = 0;
	d->dma.status = 0; /* BIT(0) should be 0 क्रम HW_OWNED */
	d->dma.length = cpu_to_le16((u16)len);
	d->dma.d0 = (vring_index << DMA_CFG_DESC_TX_0_QID_POS);
	d->mac.d[0] = 0;
	d->mac.d[1] = 0;
	d->mac.d[2] = 0;
	d->mac.ucode_cmd = 0;
	/* translation type:  0 - bypass; 1 - 802.3; 2 - native wअगरi */
	d->mac.d[2] = BIT(MAC_CFG_DESC_TX_2_SNAP_HDR_INSERTION_EN_POS) |
		      (1 << MAC_CFG_DESC_TX_2_L2_TRANSLATION_TYPE_POS);

	वापस 0;
पूर्ण

व्योम wil_tx_data_init(काष्ठा wil_ring_tx_data *txdata)
अणु
	spin_lock_bh(&txdata->lock);
	txdata->करोt1x_खोलो = false;
	txdata->enabled = 0;
	txdata->idle = 0;
	txdata->last_idle = 0;
	txdata->begin = 0;
	txdata->agg_wsize = 0;
	txdata->agg_समयout = 0;
	txdata->agg_amsdu = 0;
	txdata->addba_in_progress = false;
	txdata->mid = U8_MAX;
	spin_unlock_bh(&txdata->lock);
पूर्ण

अटल पूर्णांक wil_vring_init_tx(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, पूर्णांक size,
			     पूर्णांक cid, पूर्णांक tid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा wmi_vring_cfg_cmd cmd = अणु
		.action = cpu_to_le32(WMI_VRING_CMD_ADD),
		.vring_cfg = अणु
			.tx_sw_ring = अणु
				.max_mpdu_size =
					cpu_to_le16(wil_mtu2macbuf(mtu_max)),
				.ring_size = cpu_to_le16(size),
			पूर्ण,
			.ringid = id,
			.encap_trans_type = WMI_VRING_ENC_TYPE_802_3,
			.mac_ctrl = 0,
			.to_resolution = 0,
			.agg_max_wsize = 0,
			.schd_params = अणु
				.priority = cpu_to_le16(0),
				.बारlot_us = cpu_to_le16(0xfff),
			पूर्ण,
		पूर्ण,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_vring_cfg_करोne_event cmd;
	पूर्ण __packed reply = अणु
		.cmd = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;
	काष्ठा wil_ring *vring = &wil->ring_tx[id];
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[id];

	अगर (cid >= WIL6210_RX_DESC_MAX_CID) अणु
		cmd.vring_cfg.cidxtid = CIDXTID_EXTENDED_CID_TID;
		cmd.vring_cfg.cid = cid;
		cmd.vring_cfg.tid = tid;
	पूर्ण अन्यथा अणु
		cmd.vring_cfg.cidxtid = mk_cidxtid(cid, tid);
	पूर्ण

	wil_dbg_misc(wil, "vring_init_tx: max_mpdu_size %d\n",
		     cmd.vring_cfg.tx_sw_ring.max_mpdu_size);
	lockdep_निश्चित_held(&wil->mutex);

	अगर (vring->va) अणु
		wil_err(wil, "Tx ring [%d] already allocated\n", id);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	wil_tx_data_init(txdata);
	vring->is_rx = false;
	vring->size = size;
	rc = wil_vring_alloc(wil, vring);
	अगर (rc)
		जाओ out;

	wil->ring2cid_tid[id][0] = cid;
	wil->ring2cid_tid[id][1] = tid;

	cmd.vring_cfg.tx_sw_ring.ring_mem_base = cpu_to_le64(vring->pa);

	अगर (!vअगर->privacy)
		txdata->करोt1x_खोलो = true;
	rc = wmi_call(wil, WMI_VRING_CFG_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_VRING_CFG_DONE_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		जाओ out_मुक्त;

	अगर (reply.cmd.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "Tx config failed, status 0x%02x\n",
			reply.cmd.status);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	spin_lock_bh(&txdata->lock);
	vring->hwtail = le32_to_cpu(reply.cmd.tx_vring_tail_ptr);
	txdata->mid = vअगर->mid;
	txdata->enabled = 1;
	spin_unlock_bh(&txdata->lock);

	अगर (txdata->करोt1x_खोलो && (agg_wsize >= 0))
		wil_addba_tx_request(wil, id, agg_wsize);

	वापस 0;
 out_मुक्त:
	spin_lock_bh(&txdata->lock);
	txdata->करोt1x_खोलो = false;
	txdata->enabled = 0;
	spin_unlock_bh(&txdata->lock);
	wil_vring_मुक्त(wil, vring);
	wil->ring2cid_tid[id][0] = wil->max_assoc_sta;
	wil->ring2cid_tid[id][1] = 0;

 out:

	वापस rc;
पूर्ण

अटल पूर्णांक wil_tx_vring_modअगरy(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ring_id, पूर्णांक cid,
			       पूर्णांक tid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा wmi_vring_cfg_cmd cmd = अणु
		.action = cpu_to_le32(WMI_VRING_CMD_MODIFY),
		.vring_cfg = अणु
			.tx_sw_ring = अणु
				.max_mpdu_size =
					cpu_to_le16(wil_mtu2macbuf(mtu_max)),
				.ring_size = 0,
			पूर्ण,
			.ringid = ring_id,
			.cidxtid = mk_cidxtid(cid, tid),
			.encap_trans_type = WMI_VRING_ENC_TYPE_802_3,
			.mac_ctrl = 0,
			.to_resolution = 0,
			.agg_max_wsize = 0,
			.schd_params = अणु
				.priority = cpu_to_le16(0),
				.बारlot_us = cpu_to_le16(0xfff),
			पूर्ण,
		पूर्ण,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_vring_cfg_करोne_event cmd;
	पूर्ण __packed reply = अणु
		.cmd = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;
	काष्ठा wil_ring *vring = &wil->ring_tx[ring_id];
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_id];

	wil_dbg_misc(wil, "vring_modify: ring %d cid %d tid %d\n", ring_id,
		     cid, tid);
	lockdep_निश्चित_held(&wil->mutex);

	अगर (!vring->va) अणु
		wil_err(wil, "Tx ring [%d] not allocated\n", ring_id);
		वापस -EINVAL;
	पूर्ण

	अगर (wil->ring2cid_tid[ring_id][0] != cid ||
	    wil->ring2cid_tid[ring_id][1] != tid) अणु
		wil_err(wil, "ring info does not match cid=%u tid=%u\n",
			wil->ring2cid_tid[ring_id][0],
			wil->ring2cid_tid[ring_id][1]);
	पूर्ण

	cmd.vring_cfg.tx_sw_ring.ring_mem_base = cpu_to_le64(vring->pa);

	rc = wmi_call(wil, WMI_VRING_CFG_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_VRING_CFG_DONE_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		जाओ fail;

	अगर (reply.cmd.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "Tx modify failed, status 0x%02x\n",
			reply.cmd.status);
		rc = -EINVAL;
		जाओ fail;
	पूर्ण

	/* set BA aggregation winकरोw size to 0 to क्रमce a new BA with the
	 * new AP
	 */
	txdata->agg_wsize = 0;
	अगर (txdata->करोt1x_खोलो && agg_wsize >= 0)
		wil_addba_tx_request(wil, ring_id, agg_wsize);

	वापस 0;
fail:
	spin_lock_bh(&txdata->lock);
	txdata->करोt1x_खोलो = false;
	txdata->enabled = 0;
	spin_unlock_bh(&txdata->lock);
	wil->ring2cid_tid[ring_id][0] = wil->max_assoc_sta;
	wil->ring2cid_tid[ring_id][1] = 0;
	वापस rc;
पूर्ण

पूर्णांक wil_vring_init_bcast(काष्ठा wil6210_vअगर *vअगर, पूर्णांक id, पूर्णांक size)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	पूर्णांक rc;
	काष्ठा wmi_bcast_vring_cfg_cmd cmd = अणु
		.action = cpu_to_le32(WMI_VRING_CMD_ADD),
		.vring_cfg = अणु
			.tx_sw_ring = अणु
				.max_mpdu_size =
					cpu_to_le16(wil_mtu2macbuf(mtu_max)),
				.ring_size = cpu_to_le16(size),
			पूर्ण,
			.ringid = id,
			.encap_trans_type = WMI_VRING_ENC_TYPE_802_3,
		पूर्ण,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_vring_cfg_करोne_event cmd;
	पूर्ण __packed reply = अणु
		.cmd = अणु.status = WMI_FW_STATUS_FAILUREपूर्ण,
	पूर्ण;
	काष्ठा wil_ring *vring = &wil->ring_tx[id];
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[id];

	wil_dbg_misc(wil, "vring_init_bcast: max_mpdu_size %d\n",
		     cmd.vring_cfg.tx_sw_ring.max_mpdu_size);
	lockdep_निश्चित_held(&wil->mutex);

	अगर (vring->va) अणु
		wil_err(wil, "Tx ring [%d] already allocated\n", id);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	wil_tx_data_init(txdata);
	vring->is_rx = false;
	vring->size = size;
	rc = wil_vring_alloc(wil, vring);
	अगर (rc)
		जाओ out;

	wil->ring2cid_tid[id][0] = wil->max_assoc_sta; /* CID */
	wil->ring2cid_tid[id][1] = 0; /* TID */

	cmd.vring_cfg.tx_sw_ring.ring_mem_base = cpu_to_le64(vring->pa);

	अगर (!vअगर->privacy)
		txdata->करोt1x_खोलो = true;
	rc = wmi_call(wil, WMI_BCAST_VRING_CFG_CMDID, vअगर->mid,
		      &cmd, माप(cmd),
		      WMI_VRING_CFG_DONE_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		जाओ out_मुक्त;

	अगर (reply.cmd.status != WMI_FW_STATUS_SUCCESS) अणु
		wil_err(wil, "Tx config failed, status 0x%02x\n",
			reply.cmd.status);
		rc = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	spin_lock_bh(&txdata->lock);
	vring->hwtail = le32_to_cpu(reply.cmd.tx_vring_tail_ptr);
	txdata->mid = vअगर->mid;
	txdata->enabled = 1;
	spin_unlock_bh(&txdata->lock);

	वापस 0;
 out_मुक्त:
	spin_lock_bh(&txdata->lock);
	txdata->enabled = 0;
	txdata->करोt1x_खोलो = false;
	spin_unlock_bh(&txdata->lock);
	wil_vring_मुक्त(wil, vring);
 out:

	वापस rc;
पूर्ण

अटल काष्ठा wil_ring *wil_find_tx_ucast(काष्ठा wil6210_priv *wil,
					  काष्ठा wil6210_vअगर *vअगर,
					  काष्ठा sk_buff *skb)
अणु
	पूर्णांक i, cid;
	स्थिर u8 *da = wil_skb_get_da(skb);
	पूर्णांक min_ring_id = wil_get_min_tx_ring_id(wil);

	cid = wil_find_cid(wil, vअगर->mid, da);

	अगर (cid < 0 || cid >= wil->max_assoc_sta)
		वापस शून्य;

	/* TODO: fix क्रम multiple TID */
	क्रम (i = min_ring_id; i < ARRAY_SIZE(wil->ring2cid_tid); i++) अणु
		अगर (!wil->ring_tx_data[i].करोt1x_खोलो &&
		    skb->protocol != cpu_to_be16(ETH_P_PAE))
			जारी;
		अगर (wil->ring2cid_tid[i][0] == cid) अणु
			काष्ठा wil_ring *v = &wil->ring_tx[i];
			काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[i];

			wil_dbg_txrx(wil, "find_tx_ucast: (%pM) -> [%d]\n",
				     da, i);
			अगर (v->va && txdata->enabled) अणु
				वापस v;
			पूर्ण अन्यथा अणु
				wil_dbg_txrx(wil,
					     "find_tx_ucast: vring[%d] not valid\n",
					     i);
				वापस शून्य;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस शून्य;
पूर्ण

अटल पूर्णांक wil_tx_ring(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
		       काष्ठा wil_ring *ring, काष्ठा sk_buff *skb);

अटल काष्ठा wil_ring *wil_find_tx_ring_sta(काष्ठा wil6210_priv *wil,
					     काष्ठा wil6210_vअगर *vअगर,
					     काष्ठा sk_buff *skb)
अणु
	काष्ठा wil_ring *ring;
	पूर्णांक i;
	u8 cid;
	काष्ठा wil_ring_tx_data  *txdata;
	पूर्णांक min_ring_id = wil_get_min_tx_ring_id(wil);

	/* In the STA mode, it is expected to have only 1 VRING
	 * क्रम the AP we connected to.
	 * find 1-st vring eligible क्रम this skb and use it.
	 */
	क्रम (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) अणु
		ring = &wil->ring_tx[i];
		txdata = &wil->ring_tx_data[i];
		अगर (!ring->va || !txdata->enabled || txdata->mid != vअगर->mid)
			जारी;

		cid = wil->ring2cid_tid[i][0];
		अगर (cid >= wil->max_assoc_sta) /* skip BCAST */
			जारी;

		अगर (!wil->ring_tx_data[i].करोt1x_खोलो &&
		    skb->protocol != cpu_to_be16(ETH_P_PAE))
			जारी;

		wil_dbg_txrx(wil, "Tx -> ring %d\n", i);

		वापस ring;
	पूर्ण

	wil_dbg_txrx(wil, "Tx while no rings active?\n");

	वापस शून्य;
पूर्ण

/* Use one of 2 strategies:
 *
 * 1. New (real broadcast):
 *    use dedicated broadcast vring
 * 2. Old (pseuकरो-DMS):
 *    Find 1-st vring and वापस it;
 *    duplicate skb and send it to other active vrings;
 *    in all हालs override dest address to unicast peer's address
 * Use old strategy when new is not supported yet:
 *  - क्रम PBSS
 */
अटल काष्ठा wil_ring *wil_find_tx_bcast_1(काष्ठा wil6210_priv *wil,
					    काष्ठा wil6210_vअगर *vअगर,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा wil_ring *v;
	काष्ठा wil_ring_tx_data *txdata;
	पूर्णांक i = vअगर->bcast_ring;

	अगर (i < 0)
		वापस शून्य;
	v = &wil->ring_tx[i];
	txdata = &wil->ring_tx_data[i];
	अगर (!v->va || !txdata->enabled)
		वापस शून्य;
	अगर (!wil->ring_tx_data[i].करोt1x_खोलो &&
	    skb->protocol != cpu_to_be16(ETH_P_PAE))
		वापस शून्य;

	वापस v;
पूर्ण

/* apply multicast to unicast only क्रम ARP and IP packets
 * (see NL80211_CMD_SET_MULTICAST_TO_UNICAST क्रम more info)
 */
अटल bool wil_check_multicast_to_unicast(काष्ठा wil6210_priv *wil,
					   काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा ethhdr *eth = (व्योम *)skb->data;
	स्थिर काष्ठा vlan_ethhdr *ethvlan = (व्योम *)skb->data;
	__be16 ethertype;

	अगर (!wil->multicast_to_unicast)
		वापस false;

	/* multicast to unicast conversion only क्रम some payload */
	ethertype = eth->h_proto;
	अगर (ethertype == htons(ETH_P_8021Q) && skb->len >= VLAN_ETH_HLEN)
		ethertype = ethvlan->h_vlan_encapsulated_proto;
	चयन (ethertype) अणु
	हाल htons(ETH_P_ARP):
	हाल htons(ETH_P_IP):
	हाल htons(ETH_P_IPV6):
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम wil_set_da_क्रम_vring(काष्ठा wil6210_priv *wil,
				 काष्ठा sk_buff *skb, पूर्णांक vring_index)
अणु
	u8 *da = wil_skb_get_da(skb);
	पूर्णांक cid = wil->ring2cid_tid[vring_index][0];

	ether_addr_copy(da, wil->sta[cid].addr);
पूर्ण

अटल काष्ठा wil_ring *wil_find_tx_bcast_2(काष्ठा wil6210_priv *wil,
					    काष्ठा wil6210_vअगर *vअगर,
					    काष्ठा sk_buff *skb)
अणु
	काष्ठा wil_ring *v, *v2;
	काष्ठा sk_buff *skb2;
	पूर्णांक i;
	u8 cid;
	स्थिर u8 *src = wil_skb_get_sa(skb);
	काष्ठा wil_ring_tx_data *txdata, *txdata2;
	पूर्णांक min_ring_id = wil_get_min_tx_ring_id(wil);

	/* find 1-st vring eligible क्रम data */
	क्रम (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) अणु
		v = &wil->ring_tx[i];
		txdata = &wil->ring_tx_data[i];
		अगर (!v->va || !txdata->enabled || txdata->mid != vअगर->mid)
			जारी;

		cid = wil->ring2cid_tid[i][0];
		अगर (cid >= wil->max_assoc_sta) /* skip BCAST */
			जारी;
		अगर (!wil->ring_tx_data[i].करोt1x_खोलो &&
		    skb->protocol != cpu_to_be16(ETH_P_PAE))
			जारी;

		/* करोn't Tx back to source when re-routing Rx->Tx at the AP */
		अगर (0 == स_भेद(wil->sta[cid].addr, src, ETH_ALEN))
			जारी;

		जाओ found;
	पूर्ण

	wil_dbg_txrx(wil, "Tx while no vrings active?\n");

	वापस शून्य;

found:
	wil_dbg_txrx(wil, "BCAST -> ring %d\n", i);
	wil_set_da_क्रम_vring(wil, skb, i);

	/* find other active vrings and duplicate skb क्रम each */
	क्रम (i++; i < WIL6210_MAX_TX_RINGS; i++) अणु
		v2 = &wil->ring_tx[i];
		txdata2 = &wil->ring_tx_data[i];
		अगर (!v2->va || txdata2->mid != vअगर->mid)
			जारी;
		cid = wil->ring2cid_tid[i][0];
		अगर (cid >= wil->max_assoc_sta) /* skip BCAST */
			जारी;
		अगर (!wil->ring_tx_data[i].करोt1x_खोलो &&
		    skb->protocol != cpu_to_be16(ETH_P_PAE))
			जारी;

		अगर (0 == स_भेद(wil->sta[cid].addr, src, ETH_ALEN))
			जारी;

		skb2 = skb_copy(skb, GFP_ATOMIC);
		अगर (skb2) अणु
			wil_dbg_txrx(wil, "BCAST DUP -> ring %d\n", i);
			wil_set_da_क्रम_vring(wil, skb2, i);
			wil_tx_ring(wil, vअगर, v2, skb2);
			/* successful call to wil_tx_ring takes skb2 ref */
			dev_kमुक्त_skb_any(skb2);
		पूर्ण अन्यथा अणु
			wil_err(wil, "skb_copy failed\n");
		पूर्ण
	पूर्ण

	वापस v;
पूर्ण

अटल अंतरभूत
व्योम wil_tx_desc_set_nr_frags(काष्ठा vring_tx_desc *d, पूर्णांक nr_frags)
अणु
	d->mac.d[2] |= (nr_frags << MAC_CFG_DESC_TX_2_NUM_OF_DESCRIPTORS_POS);
पूर्ण

/* Sets the descriptor @d up क्रम csum and/or TSO offloading. The corresponding
 * @skb is used to obtain the protocol and headers length.
 * @tso_desc_type is a descriptor type क्रम TSO: 0 - a header, 1 - first data,
 * 2 - middle, 3 - last descriptor.
 */

अटल व्योम wil_tx_desc_offload_setup_tso(काष्ठा vring_tx_desc *d,
					  काष्ठा sk_buff *skb,
					  पूर्णांक tso_desc_type, bool is_ipv4,
					  पूर्णांक tcp_hdr_len, पूर्णांक skb_net_hdr_len)
अणु
	d->dma.b11 = ETH_HLEN; /* MAC header length */
	d->dma.b11 |= is_ipv4 << DMA_CFG_DESC_TX_OFFLOAD_CFG_L3T_IPV4_POS;

	d->dma.d0 |= (2 << DMA_CFG_DESC_TX_0_L4_TYPE_POS);
	/* L4 header len: TCP header length */
	d->dma.d0 |= (tcp_hdr_len & DMA_CFG_DESC_TX_0_L4_LENGTH_MSK);

	/* Setup TSO: bit and desc type */
	d->dma.d0 |= (BIT(DMA_CFG_DESC_TX_0_TCP_SEG_EN_POS)) |
		(tso_desc_type << DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAILS_POS);
	d->dma.d0 |= (is_ipv4 << DMA_CFG_DESC_TX_0_IPV4_CHECKSUM_EN_POS);

	d->dma.ip_length = skb_net_hdr_len;
	/* Enable TCP/UDP checksum */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_POS);
	/* Calculate pseuकरो-header */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_PSEUDO_HEADER_CALC_EN_POS);
पूर्ण

/* Sets the descriptor @d up क्रम csum. The corresponding
 * @skb is used to obtain the protocol and headers length.
 * Returns the protocol: 0 - not TCP, 1 - TCPv4, 2 - TCPv6.
 * Note, अगर d==शून्य, the function only वापसs the protocol result.
 *
 * It is very similar to previous wil_tx_desc_offload_setup_tso. This
 * is "if unrolling" to optimize the critical path.
 */

अटल पूर्णांक wil_tx_desc_offload_setup(काष्ठा vring_tx_desc *d,
				     काष्ठा sk_buff *skb)अणु
	पूर्णांक protocol;

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस 0;

	d->dma.b11 = ETH_HLEN; /* MAC header length */

	चयन (skb->protocol) अणु
	हाल cpu_to_be16(ETH_P_IP):
		protocol = ip_hdr(skb)->protocol;
		d->dma.b11 |= BIT(DMA_CFG_DESC_TX_OFFLOAD_CFG_L3T_IPV4_POS);
		अवरोध;
	हाल cpu_to_be16(ETH_P_IPV6):
		protocol = ipv6_hdr(skb)->nexthdr;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	चयन (protocol) अणु
	हाल IPPROTO_TCP:
		d->dma.d0 |= (2 << DMA_CFG_DESC_TX_0_L4_TYPE_POS);
		/* L4 header len: TCP header length */
		d->dma.d0 |=
		(tcp_hdrlen(skb) & DMA_CFG_DESC_TX_0_L4_LENGTH_MSK);
		अवरोध;
	हाल IPPROTO_UDP:
		/* L4 header len: UDP header length */
		d->dma.d0 |=
		(माप(काष्ठा udphdr) & DMA_CFG_DESC_TX_0_L4_LENGTH_MSK);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	d->dma.ip_length = skb_network_header_len(skb);
	/* Enable TCP/UDP checksum */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_TCP_UDP_CHECKSUM_EN_POS);
	/* Calculate pseuकरो-header */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_PSEUDO_HEADER_CALC_EN_POS);

	वापस 0;
पूर्ण

अटल अंतरभूत व्योम wil_tx_last_desc(काष्ठा vring_tx_desc *d)
अणु
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_CMD_EOP_POS) |
	      BIT(DMA_CFG_DESC_TX_0_CMD_MARK_WB_POS) |
	      BIT(DMA_CFG_DESC_TX_0_CMD_DMA_IT_POS);
पूर्ण

अटल अंतरभूत व्योम wil_set_tx_desc_last_tso(अस्थिर काष्ठा vring_tx_desc *d)
अणु
	d->dma.d0 |= wil_tso_type_lst <<
		  DMA_CFG_DESC_TX_0_SEGMENT_BUF_DETAILS_POS;
पूर्ण

अटल पूर्णांक __wil_tx_vring_tso(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
			      काष्ठा wil_ring *vring, काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dev = wil_to_dev(wil);

	/* poपूर्णांक to descriptors in shared memory */
	अस्थिर काष्ठा vring_tx_desc *_desc = शून्य, *_hdr_desc,
				      *_first_desc = शून्य;

	/* poपूर्णांकers to shaकरोw descriptors */
	काष्ठा vring_tx_desc desc_mem, hdr_desc_mem, first_desc_mem,
			     *d = &hdr_desc_mem, *hdr_desc = &hdr_desc_mem,
			     *first_desc = &first_desc_mem;

	/* poपूर्णांकer to shaकरोw descriptors' context */
	काष्ठा wil_ctx *hdr_ctx, *first_ctx = शून्य;

	पूर्णांक descs_used = 0; /* total number of used descriptors */
	पूर्णांक sg_desc_cnt = 0; /* number of descriptors क्रम current mss*/

	u32 swhead = vring->swhead;
	पूर्णांक used, avail = wil_ring_avail_tx(vring);
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	पूर्णांक min_desc_required = nr_frags + 1;
	पूर्णांक mss = skb_shinfo(skb)->gso_size;	/* payload size w/o headers */
	पूर्णांक f, len, hdrlen, headlen;
	पूर्णांक vring_index = vring - wil->ring_tx;
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[vring_index];
	uपूर्णांक i = swhead;
	dma_addr_t pa;
	स्थिर skb_frag_t *frag = शून्य;
	पूर्णांक rem_data = mss;
	पूर्णांक lenmss;
	पूर्णांक hdr_compensation_need = true;
	पूर्णांक desc_tso_type = wil_tso_type_first;
	bool is_ipv4;
	पूर्णांक tcp_hdr_len;
	पूर्णांक skb_net_hdr_len;
	पूर्णांक gso_type;
	पूर्णांक rc = -EINVAL;

	wil_dbg_txrx(wil, "tx_vring_tso: %d bytes to vring %d\n", skb->len,
		     vring_index);

	अगर (unlikely(!txdata->enabled))
		वापस -EINVAL;

	/* A typical page 4K is 3-4 payloads, we assume each fragment
	 * is a full payload, that's how min_desc_required has been
	 * calculated. In real we might need more or less descriptors,
	 * this is the initial check only.
	 */
	अगर (unlikely(avail < min_desc_required)) अणु
		wil_err_ratelimited(wil,
				    "TSO: Tx ring[%2d] full. No space for %d fragments\n",
				    vring_index, min_desc_required);
		वापस -ENOMEM;
	पूर्ण

	/* Header Length = MAC header len + IP header len + TCP header len*/
	hdrlen = ETH_HLEN +
		(पूर्णांक)skb_network_header_len(skb) +
		tcp_hdrlen(skb);

	gso_type = skb_shinfo(skb)->gso_type & (SKB_GSO_TCPV6 | SKB_GSO_TCPV4);
	चयन (gso_type) अणु
	हाल SKB_GSO_TCPV4:
		/* TCP v4, zero out the IP length and IPv4 checksum fields
		 * as required by the offloading करोc
		 */
		ip_hdr(skb)->tot_len = 0;
		ip_hdr(skb)->check = 0;
		is_ipv4 = true;
		अवरोध;
	हाल SKB_GSO_TCPV6:
		/* TCP v6, zero out the payload length */
		ipv6_hdr(skb)->payload_len = 0;
		is_ipv4 = false;
		अवरोध;
	शेष:
		/* other than TCPv4 or TCPv6 types are not supported क्रम TSO.
		 * It is also illegal क्रम both to be set simultaneously
		 */
		वापस -EINVAL;
	पूर्ण

	अगर (skb->ip_summed != CHECKSUM_PARTIAL)
		वापस -EINVAL;

	/* tcp header length and skb network header length are fixed क्रम all
	 * packet's descriptors - पढ़ो then once here
	 */
	tcp_hdr_len = tcp_hdrlen(skb);
	skb_net_hdr_len = skb_network_header_len(skb);

	_hdr_desc = &vring->va[i].tx.legacy;

	pa = dma_map_single(dev, skb->data, hdrlen, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(dev, pa))) अणु
		wil_err(wil, "TSO: Skb head DMA map error\n");
		जाओ err_निकास;
	पूर्ण

	wil->txrx_ops.tx_desc_map((जोड़ wil_tx_desc *)hdr_desc, pa,
				  hdrlen, vring_index);
	wil_tx_desc_offload_setup_tso(hdr_desc, skb, wil_tso_type_hdr, is_ipv4,
				      tcp_hdr_len, skb_net_hdr_len);
	wil_tx_last_desc(hdr_desc);

	vring->ctx[i].mapped_as = wil_mapped_as_single;
	hdr_ctx = &vring->ctx[i];

	descs_used++;
	headlen = skb_headlen(skb) - hdrlen;

	क्रम (f = headlen ? -1 : 0; f < nr_frags; f++)  अणु
		अगर (headlen) अणु
			len = headlen;
			wil_dbg_txrx(wil, "TSO: process skb head, len %u\n",
				     len);
		पूर्ण अन्यथा अणु
			frag = &skb_shinfo(skb)->frags[f];
			len = skb_frag_size(frag);
			wil_dbg_txrx(wil, "TSO: frag[%d]: len %u\n", f, len);
		पूर्ण

		जबतक (len) अणु
			wil_dbg_txrx(wil,
				     "TSO: len %d, rem_data %d, descs_used %d\n",
				     len, rem_data, descs_used);

			अगर (descs_used == avail)  अणु
				wil_err_ratelimited(wil, "TSO: ring overflow\n");
				rc = -ENOMEM;
				जाओ mem_error;
			पूर्ण

			lenmss = min_t(पूर्णांक, rem_data, len);
			i = (swhead + descs_used) % vring->size;
			wil_dbg_txrx(wil, "TSO: lenmss %d, i %d\n", lenmss, i);

			अगर (!headlen) अणु
				pa = skb_frag_dma_map(dev, frag,
						      skb_frag_size(frag) - len,
						      lenmss, DMA_TO_DEVICE);
				vring->ctx[i].mapped_as = wil_mapped_as_page;
			पूर्ण अन्यथा अणु
				pa = dma_map_single(dev,
						    skb->data +
						    skb_headlen(skb) - headlen,
						    lenmss,
						    DMA_TO_DEVICE);
				vring->ctx[i].mapped_as = wil_mapped_as_single;
				headlen -= lenmss;
			पूर्ण

			अगर (unlikely(dma_mapping_error(dev, pa))) अणु
				wil_err(wil, "TSO: DMA map page error\n");
				जाओ mem_error;
			पूर्ण

			_desc = &vring->va[i].tx.legacy;

			अगर (!_first_desc) अणु
				_first_desc = _desc;
				first_ctx = &vring->ctx[i];
				d = first_desc;
			पूर्ण अन्यथा अणु
				d = &desc_mem;
			पूर्ण

			wil->txrx_ops.tx_desc_map((जोड़ wil_tx_desc *)d,
						  pa, lenmss, vring_index);
			wil_tx_desc_offload_setup_tso(d, skb, desc_tso_type,
						      is_ipv4, tcp_hdr_len,
						      skb_net_hdr_len);

			/* use tso_type_first only once */
			desc_tso_type = wil_tso_type_mid;

			descs_used++;  /* desc used so far */
			sg_desc_cnt++; /* desc used क्रम this segment */
			len -= lenmss;
			rem_data -= lenmss;

			wil_dbg_txrx(wil,
				     "TSO: len %d, rem_data %d, descs_used %d, sg_desc_cnt %d,\n",
				     len, rem_data, descs_used, sg_desc_cnt);

			/* Close the segment अगर reached mss size or last frag*/
			अगर (rem_data == 0 || (f == nr_frags - 1 && len == 0)) अणु
				अगर (hdr_compensation_need) अणु
					/* first segment include hdr desc क्रम
					 * release
					 */
					hdr_ctx->nr_frags = sg_desc_cnt;
					wil_tx_desc_set_nr_frags(first_desc,
								 sg_desc_cnt +
								 1);
					hdr_compensation_need = false;
				पूर्ण अन्यथा अणु
					wil_tx_desc_set_nr_frags(first_desc,
								 sg_desc_cnt);
				पूर्ण
				first_ctx->nr_frags = sg_desc_cnt - 1;

				wil_tx_last_desc(d);

				/* first descriptor may also be the last
				 * क्रम this mss - make sure not to copy
				 * it twice
				 */
				अगर (first_desc != d)
					*_first_desc = *first_desc;

				/*last descriptor will be copied at the end
				 * of this TS processing
				 */
				अगर (f < nr_frags - 1 || len > 0)
					*_desc = *d;

				rem_data = mss;
				_first_desc = शून्य;
				sg_desc_cnt = 0;
			पूर्ण अन्यथा अगर (first_desc != d) /* update mid descriptor */
					*_desc = *d;
		पूर्ण
	पूर्ण

	अगर (!_desc)
		जाओ mem_error;

	/* first descriptor may also be the last.
	 * in this हाल d poपूर्णांकer is invalid
	 */
	अगर (_first_desc == _desc)
		d = first_desc;

	/* Last data descriptor */
	wil_set_tx_desc_last_tso(d);
	*_desc = *d;

	/* Fill the total number of descriptors in first desc (hdr)*/
	wil_tx_desc_set_nr_frags(hdr_desc, descs_used);
	*_hdr_desc = *hdr_desc;

	/* hold reference to skb
	 * to prevent skb release beक्रमe accounting
	 * in हाल of immediate "tx done"
	 */
	vring->ctx[i].skb = skb_get(skb);

	/* perक्रमmance monitoring */
	used = wil_ring_used_tx(vring);
	अगर (wil_val_in_range(wil->ring_idle_trsh,
			     used, used + descs_used)) अणु
		txdata->idle += get_cycles() - txdata->last_idle;
		wil_dbg_txrx(wil,  "Ring[%2d] not idle %d -> %d\n",
			     vring_index, used, used + descs_used);
	पूर्ण

	/* Make sure to advance the head only after descriptor update is करोne.
	 * This will prevent a race condition where the completion thपढ़ो
	 * will see the DU bit set from previous run and will handle the
	 * skb beक्रमe it was completed.
	 */
	wmb();

	/* advance swhead */
	wil_ring_advance_head(vring, descs_used);
	wil_dbg_txrx(wil, "TSO: Tx swhead %d -> %d\n", swhead, vring->swhead);

	/* make sure all ग_लिखोs to descriptors (shared memory) are करोne beक्रमe
	 * committing them to HW
	 */
	wmb();

	अगर (wil->tx_latency)
		*(kसमय_प्रकार *)&skb->cb = kसमय_get();
	अन्यथा
		स_रखो(skb->cb, 0, माप(kसमय_प्रकार));

	wil_w(wil, vring->hwtail, vring->swhead);
	वापस 0;

mem_error:
	जबतक (descs_used > 0) अणु
		काष्ठा wil_ctx *ctx;

		i = (swhead + descs_used - 1) % vring->size;
		d = (काष्ठा vring_tx_desc *)&vring->va[i].tx.legacy;
		_desc = &vring->va[i].tx.legacy;
		*d = *_desc;
		_desc->dma.status = TX_DMA_STATUS_DU;
		ctx = &vring->ctx[i];
		wil_txdesc_unmap(dev, (जोड़ wil_tx_desc *)d, ctx);
		स_रखो(ctx, 0, माप(*ctx));
		descs_used--;
	पूर्ण
err_निकास:
	वापस rc;
पूर्ण

अटल पूर्णांक __wil_tx_ring(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
			 काष्ठा wil_ring *ring, काष्ठा sk_buff *skb)
अणु
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा vring_tx_desc dd, *d = &dd;
	अस्थिर काष्ठा vring_tx_desc *_d;
	u32 swhead = ring->swhead;
	पूर्णांक avail = wil_ring_avail_tx(ring);
	पूर्णांक nr_frags = skb_shinfo(skb)->nr_frags;
	uपूर्णांक f = 0;
	पूर्णांक ring_index = ring - wil->ring_tx;
	काष्ठा wil_ring_tx_data  *txdata = &wil->ring_tx_data[ring_index];
	uपूर्णांक i = swhead;
	dma_addr_t pa;
	पूर्णांक used;
	bool mcast = (ring_index == vअगर->bcast_ring);
	uपूर्णांक len = skb_headlen(skb);

	wil_dbg_txrx(wil, "tx_ring: %d bytes to ring %d, nr_frags %d\n",
		     skb->len, ring_index, nr_frags);

	अगर (unlikely(!txdata->enabled))
		वापस -EINVAL;

	अगर (unlikely(avail < 1 + nr_frags)) अणु
		wil_err_ratelimited(wil,
				    "Tx ring[%2d] full. No space for %d fragments\n",
				    ring_index, 1 + nr_frags);
		वापस -ENOMEM;
	पूर्ण
	_d = &ring->va[i].tx.legacy;

	pa = dma_map_single(dev, skb->data, skb_headlen(skb), DMA_TO_DEVICE);

	wil_dbg_txrx(wil, "Tx[%2d] skb %d bytes 0x%p -> %pad\n", ring_index,
		     skb_headlen(skb), skb->data, &pa);
	wil_hex_dump_txrx("Tx ", DUMP_PREFIX_OFFSET, 16, 1,
			  skb->data, skb_headlen(skb), false);

	अगर (unlikely(dma_mapping_error(dev, pa)))
		वापस -EINVAL;
	ring->ctx[i].mapped_as = wil_mapped_as_single;
	/* 1-st segment */
	wil->txrx_ops.tx_desc_map((जोड़ wil_tx_desc *)d, pa, len,
				   ring_index);
	अगर (unlikely(mcast)) अणु
		d->mac.d[0] |= BIT(MAC_CFG_DESC_TX_0_MCS_EN_POS); /* MCS 0 */
		अगर (unlikely(len > WIL_BCAST_MCS0_LIMIT)) /* set MCS 1 */
			d->mac.d[0] |= (1 << MAC_CFG_DESC_TX_0_MCS_INDEX_POS);
	पूर्ण
	/* Process TCP/UDP checksum offloading */
	अगर (unlikely(wil_tx_desc_offload_setup(d, skb))) अणु
		wil_err(wil, "Tx[%2d] Failed to set cksum, drop packet\n",
			ring_index);
		जाओ dma_error;
	पूर्ण

	ring->ctx[i].nr_frags = nr_frags;
	wil_tx_desc_set_nr_frags(d, nr_frags + 1);

	/* middle segments */
	क्रम (; f < nr_frags; f++) अणु
		स्थिर skb_frag_t *frag = &skb_shinfo(skb)->frags[f];
		पूर्णांक len = skb_frag_size(frag);

		*_d = *d;
		wil_dbg_txrx(wil, "Tx[%2d] desc[%4d]\n", ring_index, i);
		wil_hex_dump_txrx("TxD ", DUMP_PREFIX_NONE, 32, 4,
				  (स्थिर व्योम *)d, माप(*d), false);
		i = (swhead + f + 1) % ring->size;
		_d = &ring->va[i].tx.legacy;
		pa = skb_frag_dma_map(dev, frag, 0, skb_frag_size(frag),
				      DMA_TO_DEVICE);
		अगर (unlikely(dma_mapping_error(dev, pa))) अणु
			wil_err(wil, "Tx[%2d] failed to map fragment\n",
				ring_index);
			जाओ dma_error;
		पूर्ण
		ring->ctx[i].mapped_as = wil_mapped_as_page;
		wil->txrx_ops.tx_desc_map((जोड़ wil_tx_desc *)d,
					   pa, len, ring_index);
		/* no need to check वापस code -
		 * अगर it succeeded क्रम 1-st descriptor,
		 * it will succeed here too
		 */
		wil_tx_desc_offload_setup(d, skb);
	पूर्ण
	/* क्रम the last seg only */
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_CMD_EOP_POS);
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_CMD_MARK_WB_POS);
	d->dma.d0 |= BIT(DMA_CFG_DESC_TX_0_CMD_DMA_IT_POS);
	*_d = *d;
	wil_dbg_txrx(wil, "Tx[%2d] desc[%4d]\n", ring_index, i);
	wil_hex_dump_txrx("TxD ", DUMP_PREFIX_NONE, 32, 4,
			  (स्थिर व्योम *)d, माप(*d), false);

	/* hold reference to skb
	 * to prevent skb release beक्रमe accounting
	 * in हाल of immediate "tx done"
	 */
	ring->ctx[i].skb = skb_get(skb);

	/* perक्रमmance monitoring */
	used = wil_ring_used_tx(ring);
	अगर (wil_val_in_range(wil->ring_idle_trsh,
			     used, used + nr_frags + 1)) अणु
		txdata->idle += get_cycles() - txdata->last_idle;
		wil_dbg_txrx(wil,  "Ring[%2d] not idle %d -> %d\n",
			     ring_index, used, used + nr_frags + 1);
	पूर्ण

	/* Make sure to advance the head only after descriptor update is करोne.
	 * This will prevent a race condition where the completion thपढ़ो
	 * will see the DU bit set from previous run and will handle the
	 * skb beक्रमe it was completed.
	 */
	wmb();

	/* advance swhead */
	wil_ring_advance_head(ring, nr_frags + 1);
	wil_dbg_txrx(wil, "Tx[%2d] swhead %d -> %d\n", ring_index, swhead,
		     ring->swhead);
	trace_wil6210_tx(ring_index, swhead, skb->len, nr_frags);

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
 dma_error:
	/* unmap what we have mapped */
	nr_frags = f + 1; /* frags mapped + one क्रम skb head */
	क्रम (f = 0; f < nr_frags; f++) अणु
		काष्ठा wil_ctx *ctx;

		i = (swhead + f) % ring->size;
		ctx = &ring->ctx[i];
		_d = &ring->va[i].tx.legacy;
		*d = *_d;
		_d->dma.status = TX_DMA_STATUS_DU;
		wil->txrx_ops.tx_desc_unmap(dev,
					    (जोड़ wil_tx_desc *)d,
					    ctx);

		स_रखो(ctx, 0, माप(*ctx));
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wil_tx_ring(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
		       काष्ठा wil_ring *ring, काष्ठा sk_buff *skb)
अणु
	पूर्णांक ring_index = ring - wil->ring_tx;
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ring_index];
	पूर्णांक rc;

	spin_lock(&txdata->lock);

	अगर (test_bit(wil_status_suspending, wil->status) ||
	    test_bit(wil_status_suspended, wil->status) ||
	    test_bit(wil_status_resuming, wil->status)) अणु
		wil_dbg_txrx(wil,
			     "suspend/resume in progress. drop packet\n");
		spin_unlock(&txdata->lock);
		वापस -EINVAL;
	पूर्ण

	rc = (skb_is_gso(skb) ? wil->txrx_ops.tx_ring_tso : __wil_tx_ring)
	     (wil, vअगर, ring, skb);

	spin_unlock(&txdata->lock);

	वापस rc;
पूर्ण

/* Check status of tx vrings and stop/wake net queues अगर needed
 * It will start/stop net queues of a specअगरic VIF net_device.
 *
 * This function करोes one of two checks:
 * In हाल check_stop is true, will check अगर net queues need to be stopped. If
 * the conditions क्रम stopping are met, netअगर_tx_stop_all_queues() is called.
 * In हाल check_stop is false, will check अगर net queues need to be waked. If
 * the conditions क्रम waking are met, netअगर_tx_wake_all_queues() is called.
 * vring is the vring which is currently being modअगरied by either adding
 * descriptors (tx) पूर्णांकo it or removing descriptors (tx complete) from it. Can
 * be null when irrelevant (e.g. connect/disconnect events).
 *
 * The implementation is to stop net queues अगर modअगरied vring has low
 * descriptor availability. Wake अगर all vrings are not in low descriptor
 * availability and modअगरied vring has high descriptor availability.
 */
अटल अंतरभूत व्योम __wil_update_net_queues(काष्ठा wil6210_priv *wil,
					   काष्ठा wil6210_vअगर *vअगर,
					   काष्ठा wil_ring *ring,
					   bool check_stop)
अणु
	पूर्णांक i;
	पूर्णांक min_ring_id = wil_get_min_tx_ring_id(wil);

	अगर (unlikely(!vअगर))
		वापस;

	अगर (ring)
		wil_dbg_txrx(wil, "vring %d, mid %d, check_stop=%d, stopped=%d",
			     (पूर्णांक)(ring - wil->ring_tx), vअगर->mid, check_stop,
			     vअगर->net_queue_stopped);
	अन्यथा
		wil_dbg_txrx(wil, "check_stop=%d, mid=%d, stopped=%d",
			     check_stop, vअगर->mid, vअगर->net_queue_stopped);

	अगर (ring && drop_अगर_ring_full)
		/* no need to stop/wake net queues */
		वापस;

	अगर (check_stop == vअगर->net_queue_stopped)
		/* net queues alपढ़ोy in desired state */
		वापस;

	अगर (check_stop) अणु
		अगर (!ring || unlikely(wil_ring_avail_low(ring))) अणु
			/* not enough room in the vring */
			netअगर_tx_stop_all_queues(vअगर_to_ndev(vअगर));
			vअगर->net_queue_stopped = true;
			wil_dbg_txrx(wil, "netif_tx_stop called\n");
		पूर्ण
		वापस;
	पूर्ण

	/* Do not wake the queues in suspend flow */
	अगर (test_bit(wil_status_suspending, wil->status) ||
	    test_bit(wil_status_suspended, wil->status))
		वापस;

	/* check wake */
	क्रम (i = min_ring_id; i < WIL6210_MAX_TX_RINGS; i++) अणु
		काष्ठा wil_ring *cur_ring = &wil->ring_tx[i];
		काष्ठा wil_ring_tx_data  *txdata = &wil->ring_tx_data[i];

		अगर (txdata->mid != vअगर->mid || !cur_ring->va ||
		    !txdata->enabled || cur_ring == ring)
			जारी;

		अगर (wil_ring_avail_low(cur_ring)) अणु
			wil_dbg_txrx(wil, "ring %d full, can't wake\n",
				     (पूर्णांक)(cur_ring - wil->ring_tx));
			वापस;
		पूर्ण
	पूर्ण

	अगर (!ring || wil_ring_avail_high(ring)) अणु
		/* enough room in the ring */
		wil_dbg_txrx(wil, "calling netif_tx_wake\n");
		netअगर_tx_wake_all_queues(vअगर_to_ndev(vअगर));
		vअगर->net_queue_stopped = false;
	पूर्ण
पूर्ण

व्योम wil_update_net_queues(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
			   काष्ठा wil_ring *ring, bool check_stop)
अणु
	spin_lock(&wil->net_queue_lock);
	__wil_update_net_queues(wil, vअगर, ring, check_stop);
	spin_unlock(&wil->net_queue_lock);
पूर्ण

व्योम wil_update_net_queues_bh(काष्ठा wil6210_priv *wil, काष्ठा wil6210_vअगर *vअगर,
			      काष्ठा wil_ring *ring, bool check_stop)
अणु
	spin_lock_bh(&wil->net_queue_lock);
	__wil_update_net_queues(wil, vअगर, ring, check_stop);
	spin_unlock_bh(&wil->net_queue_lock);
पूर्ण

netdev_tx_t wil_start_xmit(काष्ठा sk_buff *skb, काष्ठा net_device *ndev)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	स्थिर u8 *da = wil_skb_get_da(skb);
	bool bcast = is_multicast_ether_addr(da);
	काष्ठा wil_ring *ring;
	अटल bool pr_once_fw;
	पूर्णांक rc;

	wil_dbg_txrx(wil, "start_xmit\n");
	अगर (unlikely(!test_bit(wil_status_fwपढ़ोy, wil->status))) अणु
		अगर (!pr_once_fw) अणु
			wil_err(wil, "FW not ready\n");
			pr_once_fw = true;
		पूर्ण
		जाओ drop;
	पूर्ण
	अगर (unlikely(!test_bit(wil_vअगर_fwconnected, vअगर->status))) अणु
		wil_dbg_ratelimited(wil,
				    "VIF not connected, packet dropped\n");
		जाओ drop;
	पूर्ण
	अगर (unlikely(vअगर->wdev.अगरtype == NL80211_IFTYPE_MONITOR)) अणु
		wil_err(wil, "Xmit in monitor mode not supported\n");
		जाओ drop;
	पूर्ण
	pr_once_fw = false;

	/* find vring */
	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_STATION && !vअगर->pbss) अणु
		/* in STA mode (ESS), all to same VRING (to AP) */
		ring = wil_find_tx_ring_sta(wil, vअगर, skb);
	पूर्ण अन्यथा अगर (bcast) अणु
		अगर (vअगर->pbss || wil_check_multicast_to_unicast(wil, skb))
			/* in pbss, no bcast VRING - duplicate skb in
			 * all stations VRINGs
			 */
			ring = wil_find_tx_bcast_2(wil, vअगर, skb);
		अन्यथा अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_AP)
			/* AP has a dedicated bcast VRING */
			ring = wil_find_tx_bcast_1(wil, vअगर, skb);
		अन्यथा
			/* unexpected combination, fallback to duplicating
			 * the skb in all stations VRINGs
			 */
			ring = wil_find_tx_bcast_2(wil, vअगर, skb);
	पूर्ण अन्यथा अणु
		/* unicast, find specअगरic VRING by dest. address */
		ring = wil_find_tx_ucast(wil, vअगर, skb);
	पूर्ण
	अगर (unlikely(!ring)) अणु
		wil_dbg_txrx(wil, "No Tx RING found for %pM\n", da);
		जाओ drop;
	पूर्ण
	/* set up vring entry */
	rc = wil_tx_ring(wil, vअगर, ring, skb);

	चयन (rc) अणु
	हाल 0:
		/* shall we stop net queues? */
		wil_update_net_queues_bh(wil, vअगर, ring, true);
		/* statistics will be updated on the tx_complete */
		dev_kमुक्त_skb_any(skb);
		वापस NETDEV_TX_OK;
	हाल -ENOMEM:
		अगर (drop_अगर_ring_full)
			जाओ drop;
		वापस NETDEV_TX_BUSY;
	शेष:
		अवरोध; /* जाओ drop; */
	पूर्ण
 drop:
	ndev->stats.tx_dropped++;
	dev_kमुक्त_skb_any(skb);

	वापस NET_XMIT_DROP;
पूर्ण

व्योम wil_tx_latency_calc(काष्ठा wil6210_priv *wil, काष्ठा sk_buff *skb,
			 काष्ठा wil_sta_info *sta)
अणु
	पूर्णांक skb_समय_us;
	पूर्णांक bin;

	अगर (!wil->tx_latency)
		वापस;

	अगर (kसमय_प्रकारo_ms(*(kसमय_प्रकार *)&skb->cb) == 0)
		वापस;

	skb_समय_us = kसमय_us_delta(kसमय_get(), *(kसमय_प्रकार *)&skb->cb);
	bin = skb_समय_us / wil->tx_latency_res;
	bin = min_t(पूर्णांक, bin, WIL_NUM_LATENCY_BINS - 1);

	wil_dbg_txrx(wil, "skb time %dus => bin %d\n", skb_समय_us, bin);
	sta->tx_latency_bins[bin]++;
	sta->stats.tx_latency_total_us += skb_समय_us;
	अगर (skb_समय_us < sta->stats.tx_latency_min_us)
		sta->stats.tx_latency_min_us = skb_समय_us;
	अगर (skb_समय_us > sta->stats.tx_latency_max_us)
		sta->stats.tx_latency_max_us = skb_समय_us;
पूर्ण

/* Clean up transmitted skb's from the Tx VRING
 *
 * Return number of descriptors cleared
 *
 * Safe to call from IRQ
 */
पूर्णांक wil_tx_complete(काष्ठा wil6210_vअगर *vअगर, पूर्णांक ringid)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा device *dev = wil_to_dev(wil);
	काष्ठा wil_ring *vring = &wil->ring_tx[ringid];
	काष्ठा wil_ring_tx_data *txdata = &wil->ring_tx_data[ringid];
	पूर्णांक करोne = 0;
	पूर्णांक cid = wil->ring2cid_tid[ringid][0];
	काष्ठा wil_net_stats *stats = शून्य;
	अस्थिर काष्ठा vring_tx_desc *_d;
	पूर्णांक used_beक्रमe_complete;
	पूर्णांक used_new;

	अगर (unlikely(!vring->va)) अणु
		wil_err(wil, "Tx irq[%d]: vring not initialized\n", ringid);
		वापस 0;
	पूर्ण

	अगर (unlikely(!txdata->enabled)) अणु
		wil_info(wil, "Tx irq[%d]: vring disabled\n", ringid);
		वापस 0;
	पूर्ण

	wil_dbg_txrx(wil, "tx_complete: (%d)\n", ringid);

	used_beक्रमe_complete = wil_ring_used_tx(vring);

	अगर (cid < wil->max_assoc_sta)
		stats = &wil->sta[cid].stats;

	जबतक (!wil_ring_is_empty(vring)) अणु
		पूर्णांक new_swtail;
		काष्ठा wil_ctx *ctx = &vring->ctx[vring->swtail];
		/* For the fragmented skb, HW will set DU bit only क्रम the
		 * last fragment. look क्रम it.
		 * In TSO the first DU will include hdr desc
		 */
		पूर्णांक lf = (vring->swtail + ctx->nr_frags) % vring->size;
		/* TODO: check we are not past head */

		_d = &vring->va[lf].tx.legacy;
		अगर (unlikely(!(_d->dma.status & TX_DMA_STATUS_DU)))
			अवरोध;

		new_swtail = (lf + 1) % vring->size;
		जबतक (vring->swtail != new_swtail) अणु
			काष्ठा vring_tx_desc dd, *d = &dd;
			u16 dmalen;
			काष्ठा sk_buff *skb;

			ctx = &vring->ctx[vring->swtail];
			skb = ctx->skb;
			_d = &vring->va[vring->swtail].tx.legacy;

			*d = *_d;

			dmalen = le16_to_cpu(d->dma.length);
			trace_wil6210_tx_करोne(ringid, vring->swtail, dmalen,
					      d->dma.error);
			wil_dbg_txrx(wil,
				     "TxC[%2d][%3d] : %d bytes, status 0x%02x err 0x%02x\n",
				     ringid, vring->swtail, dmalen,
				     d->dma.status, d->dma.error);
			wil_hex_dump_txrx("TxCD ", DUMP_PREFIX_NONE, 32, 4,
					  (स्थिर व्योम *)d, माप(*d), false);

			wil->txrx_ops.tx_desc_unmap(dev,
						    (जोड़ wil_tx_desc *)d,
						    ctx);

			अगर (skb) अणु
				अगर (likely(d->dma.error == 0)) अणु
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

				wil_consume_skb(skb, d->dma.error == 0);
			पूर्ण
			स_रखो(ctx, 0, माप(*ctx));
			/* Make sure the ctx is zeroed beक्रमe updating the tail
			 * to prevent a हाल where wil_tx_ring will see
			 * this descriptor as used and handle it beक्रमe ctx zero
			 * is completed.
			 */
			wmb();
			/* There is no need to touch HW descriptor:
			 * - ststus bit TX_DMA_STATUS_DU is set by design,
			 *   so hardware will not try to process this desc.,
			 * - rest of descriptor will be initialized on Tx.
			 */
			vring->swtail = wil_ring_next_tail(vring);
			करोne++;
		पूर्ण
	पूर्ण

	/* perक्रमmance monitoring */
	used_new = wil_ring_used_tx(vring);
	अगर (wil_val_in_range(wil->ring_idle_trsh,
			     used_new, used_beक्रमe_complete)) अणु
		wil_dbg_txrx(wil, "Ring[%2d] idle %d -> %d\n",
			     ringid, used_beक्रमe_complete, used_new);
		txdata->last_idle = get_cycles();
	पूर्ण

	/* shall we wake net queues? */
	अगर (करोne)
		wil_update_net_queues(wil, vअगर, vring, false);

	वापस करोne;
पूर्ण

अटल अंतरभूत पूर्णांक wil_tx_init(काष्ठा wil6210_priv *wil)
अणु
	वापस 0;
पूर्ण

अटल अंतरभूत व्योम wil_tx_fini(काष्ठा wil6210_priv *wil) अणुपूर्ण

अटल व्योम wil_get_reorder_params(काष्ठा wil6210_priv *wil,
				   काष्ठा sk_buff *skb, पूर्णांक *tid, पूर्णांक *cid,
				   पूर्णांक *mid, u16 *seq, पूर्णांक *mcast, पूर्णांक *retry)
अणु
	काष्ठा vring_rx_desc *d = wil_skb_rxdesc(skb);

	*tid = wil_rxdesc_tid(d);
	*cid = wil_skb_get_cid(skb);
	*mid = wil_rxdesc_mid(d);
	*seq = wil_rxdesc_seq(d);
	*mcast = wil_rxdesc_mcast(d);
	*retry = wil_rxdesc_retry(d);
पूर्ण

व्योम wil_init_txrx_ops_legacy_dma(काष्ठा wil6210_priv *wil)
अणु
	wil->txrx_ops.configure_पूर्णांकerrupt_moderation =
		wil_configure_पूर्णांकerrupt_moderation;
	/* TX ops */
	wil->txrx_ops.tx_desc_map = wil_tx_desc_map;
	wil->txrx_ops.tx_desc_unmap = wil_txdesc_unmap;
	wil->txrx_ops.tx_ring_tso =  __wil_tx_vring_tso;
	wil->txrx_ops.ring_init_tx = wil_vring_init_tx;
	wil->txrx_ops.ring_fini_tx = wil_vring_मुक्त;
	wil->txrx_ops.ring_init_bcast = wil_vring_init_bcast;
	wil->txrx_ops.tx_init = wil_tx_init;
	wil->txrx_ops.tx_fini = wil_tx_fini;
	wil->txrx_ops.tx_ring_modअगरy = wil_tx_vring_modअगरy;
	/* RX ops */
	wil->txrx_ops.rx_init = wil_rx_init;
	wil->txrx_ops.wmi_addba_rx_resp = wmi_addba_rx_resp;
	wil->txrx_ops.get_reorder_params = wil_get_reorder_params;
	wil->txrx_ops.get_netअगर_rx_params =
		wil_get_netअगर_rx_params;
	wil->txrx_ops.rx_crypto_check = wil_rx_crypto_check;
	wil->txrx_ops.rx_error_check = wil_rx_error_check;
	wil->txrx_ops.is_rx_idle = wil_is_rx_idle;
	wil->txrx_ops.rx_fini = wil_rx_fini;
पूर्ण
