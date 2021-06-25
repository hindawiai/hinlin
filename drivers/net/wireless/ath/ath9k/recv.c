<शैली गुरु>
/*
 * Copyright (c) 2008-2011 Atheros Communications Inc.
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#समावेश <linux/dma-mapping.h>
#समावेश "ath9k.h"
#समावेश "ar9003_mac.h"

#घोषणा SKB_CB_ATHBUF(__skb)	(*((काष्ठा ath_rxbuf **)__skb->cb))

अटल अंतरभूत bool ath9k_check_स्वतः_sleep(काष्ठा ath_softc *sc)
अणु
	वापस sc->ps_enabled &&
	       (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSLEEP);
पूर्ण

/*
 * Setup and link descriptors.
 *
 * 11N: we can no दीर्घer afक्रमd to self link the last descriptor.
 * MAC acknowledges BA status as दीर्घ as it copies frames to host
 * buffer (or rx fअगरo). This can incorrectly acknowledge packets
 * to a sender अगर last desc is self-linked.
 */
अटल व्योम ath_rx_buf_link(काष्ठा ath_softc *sc, काष्ठा ath_rxbuf *bf,
			    bool flush)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_desc *ds;
	काष्ठा sk_buff *skb;

	ds = bf->bf_desc;
	ds->ds_link = 0; /* link to null */
	ds->ds_data = bf->bf_buf_addr;

	/* भव addr of the beginning of the buffer. */
	skb = bf->bf_mpdu;
	BUG_ON(skb == शून्य);
	ds->ds_vdata = skb->data;

	/*
	 * setup rx descriptors. The rx_bufsize here tells the hardware
	 * how much data it can DMA to us and that we are prepared
	 * to process
	 */
	ath9k_hw_setuprxdesc(ah, ds,
			     common->rx_bufsize,
			     0);

	अगर (sc->rx.rxlink)
		*sc->rx.rxlink = bf->bf_daddr;
	अन्यथा अगर (!flush)
		ath9k_hw_putrxbuf(ah, bf->bf_daddr);

	sc->rx.rxlink = &ds->ds_link;
पूर्ण

अटल व्योम ath_rx_buf_relink(काष्ठा ath_softc *sc, काष्ठा ath_rxbuf *bf,
			      bool flush)
अणु
	अगर (sc->rx.buf_hold)
		ath_rx_buf_link(sc, sc->rx.buf_hold, flush);

	sc->rx.buf_hold = bf;
पूर्ण

अटल व्योम ath_setdefantenna(काष्ठा ath_softc *sc, u32 antenna)
अणु
	/* XXX block beacon पूर्णांकerrupts */
	ath9k_hw_setantenna(sc->sc_ah, antenna);
	sc->rx.defant = antenna;
	sc->rx.rxotherant = 0;
पूर्ण

अटल व्योम ath_opmode_init(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	u32 rfilt, mfilt[2];

	/* configure rx filter */
	rfilt = ath_calcrxfilter(sc);
	ath9k_hw_setrxfilter(ah, rfilt);

	/* configure bssid mask */
	ath_hw_setbssidmask(common);

	/* configure operational mode */
	ath9k_hw_setopmode(ah);

	/* calculate and install multicast filter */
	mfilt[0] = mfilt[1] = ~0;
	ath9k_hw_seपंचांगcastfilter(ah, mfilt[0], mfilt[1]);
पूर्ण

अटल bool ath_rx_edma_buf_link(काष्ठा ath_softc *sc,
				 क्रमागत ath9k_rx_qtype qtype)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_rx_edma *rx_edma;
	काष्ठा sk_buff *skb;
	काष्ठा ath_rxbuf *bf;

	rx_edma = &sc->rx.rx_edma[qtype];
	अगर (skb_queue_len(&rx_edma->rx_fअगरo) >= rx_edma->rx_fअगरo_hwsize)
		वापस false;

	bf = list_first_entry(&sc->rx.rxbuf, काष्ठा ath_rxbuf, list);
	list_del_init(&bf->list);

	skb = bf->bf_mpdu;

	स_रखो(skb->data, 0, ah->caps.rx_status_len);
	dma_sync_single_क्रम_device(sc->dev, bf->bf_buf_addr,
				ah->caps.rx_status_len, DMA_TO_DEVICE);

	SKB_CB_ATHBUF(skb) = bf;
	ath9k_hw_addrxbuf_edma(ah, bf->bf_buf_addr, qtype);
	__skb_queue_tail(&rx_edma->rx_fअगरo, skb);

	वापस true;
पूर्ण

अटल व्योम ath_rx_addbuffer_edma(काष्ठा ath_softc *sc,
				  क्रमागत ath9k_rx_qtype qtype)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_rxbuf *bf, *tbf;

	अगर (list_empty(&sc->rx.rxbuf)) अणु
		ath_dbg(common, QUEUE, "No free rx buf available\n");
		वापस;
	पूर्ण

	list_क्रम_each_entry_safe(bf, tbf, &sc->rx.rxbuf, list)
		अगर (!ath_rx_edma_buf_link(sc, qtype))
			अवरोध;

पूर्ण

अटल व्योम ath_rx_हटाओ_buffer(काष्ठा ath_softc *sc,
				 क्रमागत ath9k_rx_qtype qtype)
अणु
	काष्ठा ath_rxbuf *bf;
	काष्ठा ath_rx_edma *rx_edma;
	काष्ठा sk_buff *skb;

	rx_edma = &sc->rx.rx_edma[qtype];

	जबतक ((skb = __skb_dequeue(&rx_edma->rx_fअगरo)) != शून्य) अणु
		bf = SKB_CB_ATHBUF(skb);
		BUG_ON(!bf);
		list_add_tail(&bf->list, &sc->rx.rxbuf);
	पूर्ण
पूर्ण

अटल व्योम ath_rx_edma_cleanup(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_rxbuf *bf;

	ath_rx_हटाओ_buffer(sc, ATH9K_RX_QUEUE_LP);
	ath_rx_हटाओ_buffer(sc, ATH9K_RX_QUEUE_HP);

	list_क्रम_each_entry(bf, &sc->rx.rxbuf, list) अणु
		अगर (bf->bf_mpdu) अणु
			dma_unmap_single(sc->dev, bf->bf_buf_addr,
					common->rx_bufsize,
					DMA_BIसूचीECTIONAL);
			dev_kमुक्त_skb_any(bf->bf_mpdu);
			bf->bf_buf_addr = 0;
			bf->bf_mpdu = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम ath_rx_edma_init_queue(काष्ठा ath_rx_edma *rx_edma, पूर्णांक size)
अणु
	__skb_queue_head_init(&rx_edma->rx_fअगरo);
	rx_edma->rx_fअगरo_hwsize = size;
पूर्ण

अटल पूर्णांक ath_rx_edma_init(काष्ठा ath_softc *sc, पूर्णांक nbufs)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा sk_buff *skb;
	काष्ठा ath_rxbuf *bf;
	पूर्णांक error = 0, i;
	u32 size;

	ath9k_hw_set_rx_bufsize(ah, common->rx_bufsize -
				    ah->caps.rx_status_len);

	ath_rx_edma_init_queue(&sc->rx.rx_edma[ATH9K_RX_QUEUE_LP],
			       ah->caps.rx_lp_qdepth);
	ath_rx_edma_init_queue(&sc->rx.rx_edma[ATH9K_RX_QUEUE_HP],
			       ah->caps.rx_hp_qdepth);

	size = माप(काष्ठा ath_rxbuf) * nbufs;
	bf = devm_kzalloc(sc->dev, size, GFP_KERNEL);
	अगर (!bf)
		वापस -ENOMEM;

	INIT_LIST_HEAD(&sc->rx.rxbuf);

	क्रम (i = 0; i < nbufs; i++, bf++) अणु
		skb = ath_rxbuf_alloc(common, common->rx_bufsize, GFP_KERNEL);
		अगर (!skb) अणु
			error = -ENOMEM;
			जाओ rx_init_fail;
		पूर्ण

		स_रखो(skb->data, 0, common->rx_bufsize);
		bf->bf_mpdu = skb;

		bf->bf_buf_addr = dma_map_single(sc->dev, skb->data,
						 common->rx_bufsize,
						 DMA_BIसूचीECTIONAL);
		अगर (unlikely(dma_mapping_error(sc->dev,
						bf->bf_buf_addr))) अणु
				dev_kमुक्त_skb_any(skb);
				bf->bf_mpdu = शून्य;
				bf->bf_buf_addr = 0;
				ath_err(common,
					"dma_mapping_error() on RX init\n");
				error = -ENOMEM;
				जाओ rx_init_fail;
		पूर्ण

		list_add_tail(&bf->list, &sc->rx.rxbuf);
	पूर्ण

	वापस 0;

rx_init_fail:
	ath_rx_edma_cleanup(sc);
	वापस error;
पूर्ण

अटल व्योम ath_edma_start_recv(काष्ठा ath_softc *sc)
अणु
	ath9k_hw_rxena(sc->sc_ah);
	ath_rx_addbuffer_edma(sc, ATH9K_RX_QUEUE_HP);
	ath_rx_addbuffer_edma(sc, ATH9K_RX_QUEUE_LP);
	ath_opmode_init(sc);
	ath9k_hw_startpcureceive(sc->sc_ah, sc->cur_chan->offchannel);
पूर्ण

अटल व्योम ath_edma_stop_recv(काष्ठा ath_softc *sc)
अणु
	ath_rx_हटाओ_buffer(sc, ATH9K_RX_QUEUE_HP);
	ath_rx_हटाओ_buffer(sc, ATH9K_RX_QUEUE_LP);
पूर्ण

पूर्णांक ath_rx_init(काष्ठा ath_softc *sc, पूर्णांक nbufs)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा sk_buff *skb;
	काष्ठा ath_rxbuf *bf;
	पूर्णांक error = 0;

	spin_lock_init(&sc->sc_pcu_lock);

	common->rx_bufsize = IEEE80211_MAX_MPDU_LEN / 2 +
			     sc->sc_ah->caps.rx_status_len;

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		वापस ath_rx_edma_init(sc, nbufs);

	ath_dbg(common, CONFIG, "cachelsz %u rxbufsize %u\n",
		common->cachelsz, common->rx_bufsize);

	/* Initialize rx descriptors */

	error = ath_descdma_setup(sc, &sc->rx.rxdma, &sc->rx.rxbuf,
				  "rx", nbufs, 1, 0);
	अगर (error != 0) अणु
		ath_err(common,
			"failed to allocate rx descriptors: %d\n",
			error);
		जाओ err;
	पूर्ण

	list_क्रम_each_entry(bf, &sc->rx.rxbuf, list) अणु
		skb = ath_rxbuf_alloc(common, common->rx_bufsize,
				      GFP_KERNEL);
		अगर (skb == शून्य) अणु
			error = -ENOMEM;
			जाओ err;
		पूर्ण

		bf->bf_mpdu = skb;
		bf->bf_buf_addr = dma_map_single(sc->dev, skb->data,
						 common->rx_bufsize,
						 DMA_FROM_DEVICE);
		अगर (unlikely(dma_mapping_error(sc->dev,
					       bf->bf_buf_addr))) अणु
			dev_kमुक्त_skb_any(skb);
			bf->bf_mpdu = शून्य;
			bf->bf_buf_addr = 0;
			ath_err(common,
				"dma_mapping_error() on RX init\n");
			error = -ENOMEM;
			जाओ err;
		पूर्ण
	पूर्ण
	sc->rx.rxlink = शून्य;
err:
	अगर (error)
		ath_rx_cleanup(sc);

	वापस error;
पूर्ण

व्योम ath_rx_cleanup(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा sk_buff *skb;
	काष्ठा ath_rxbuf *bf;

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) अणु
		ath_rx_edma_cleanup(sc);
		वापस;
	पूर्ण

	list_क्रम_each_entry(bf, &sc->rx.rxbuf, list) अणु
		skb = bf->bf_mpdu;
		अगर (skb) अणु
			dma_unmap_single(sc->dev, bf->bf_buf_addr,
					 common->rx_bufsize,
					 DMA_FROM_DEVICE);
			dev_kमुक्त_skb(skb);
			bf->bf_buf_addr = 0;
			bf->bf_mpdu = शून्य;
		पूर्ण
	पूर्ण
पूर्ण

/*
 * Calculate the receive filter according to the
 * operating mode and state:
 *
 * o always accept unicast, broadcast, and multicast traffic
 * o मुख्यtain current state of phy error reception (the hal
 *   may enable phy error frames क्रम noise immunity work)
 * o probe request frames are accepted only when operating in
 *   hostap, adhoc, or monitor modes
 * o enable promiscuous mode according to the पूर्णांकerface state
 * o accept beacons:
 *   - when operating in adhoc mode so the 802.11 layer creates
 *     node table entries क्रम peers,
 *   - when operating in station mode क्रम collecting rssi data when
 *     the station is otherwise quiet, or
 *   - when operating as a repeater so we see repeater-sta beacons
 *   - when scanning
 */

u32 ath_calcrxfilter(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	u32 rfilt;

	अगर (IS_ENABLED(CONFIG_ATH9K_TX99))
		वापस 0;

	rfilt = ATH9K_RX_FILTER_UCAST | ATH9K_RX_FILTER_BCAST
		| ATH9K_RX_FILTER_MCAST;

	/* अगर operating on a DFS channel, enable radar pulse detection */
	अगर (sc->hw->conf.radar_enabled)
		rfilt |= ATH9K_RX_FILTER_PHYRADAR | ATH9K_RX_FILTER_PHYERR;

	spin_lock_bh(&sc->chan_lock);

	अगर (sc->cur_chan->rxfilter & FIF_PROBE_REQ)
		rfilt |= ATH9K_RX_FILTER_PROBEREQ;

	अगर (sc->sc_ah->is_monitoring)
		rfilt |= ATH9K_RX_FILTER_PROM;

	अगर ((sc->cur_chan->rxfilter & FIF_CONTROL) ||
	    sc->sc_ah->dynack.enabled)
		rfilt |= ATH9K_RX_FILTER_CONTROL;

	अगर ((sc->sc_ah->opmode == NL80211_IFTYPE_STATION) &&
	    (sc->cur_chan->nvअगरs <= 1) &&
	    !(sc->cur_chan->rxfilter & FIF_BCN_PRBRESP_PROMISC))
		rfilt |= ATH9K_RX_FILTER_MYBEACON;
	अन्यथा अगर (sc->sc_ah->opmode != NL80211_IFTYPE_OCB)
		rfilt |= ATH9K_RX_FILTER_BEACON;

	अगर ((sc->sc_ah->opmode == NL80211_IFTYPE_AP) ||
	    (sc->cur_chan->rxfilter & FIF_PSPOLL))
		rfilt |= ATH9K_RX_FILTER_PSPOLL;

	अगर (sc->cur_chandef.width != NL80211_CHAN_WIDTH_20_NOHT)
		rfilt |= ATH9K_RX_FILTER_COMP_BAR;

	अगर (sc->cur_chan->nvअगरs > 1 ||
	    (sc->cur_chan->rxfilter & (FIF_OTHER_BSS | FIF_MCAST_ACTION))) अणु
		/* This is needed क्रम older chips */
		अगर (sc->sc_ah->hw_version.macVersion <= AR_SREV_VERSION_9160)
			rfilt |= ATH9K_RX_FILTER_PROM;
		rfilt |= ATH9K_RX_FILTER_MCAST_BCAST_ALL;
	पूर्ण

	अगर (AR_SREV_9550(sc->sc_ah) || AR_SREV_9531(sc->sc_ah) ||
	    AR_SREV_9561(sc->sc_ah))
		rfilt |= ATH9K_RX_FILTER_4ADDRESS;

	अगर (AR_SREV_9462(sc->sc_ah) || AR_SREV_9565(sc->sc_ah))
		rfilt |= ATH9K_RX_FILTER_CONTROL_WRAPPER;

	अगर (ath9k_is_chanctx_enabled() &&
	    test_bit(ATH_OP_SCANNING, &common->op_flags))
		rfilt |= ATH9K_RX_FILTER_BEACON;

	spin_unlock_bh(&sc->chan_lock);

	वापस rfilt;

पूर्ण

व्योम ath_startrecv(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_rxbuf *bf, *tbf;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) अणु
		ath_edma_start_recv(sc);
		वापस;
	पूर्ण

	अगर (list_empty(&sc->rx.rxbuf))
		जाओ start_recv;

	sc->rx.buf_hold = शून्य;
	sc->rx.rxlink = शून्य;
	list_क्रम_each_entry_safe(bf, tbf, &sc->rx.rxbuf, list) अणु
		ath_rx_buf_link(sc, bf, false);
	पूर्ण

	/* We could have deleted elements so the list may be empty now */
	अगर (list_empty(&sc->rx.rxbuf))
		जाओ start_recv;

	bf = list_first_entry(&sc->rx.rxbuf, काष्ठा ath_rxbuf, list);
	ath9k_hw_putrxbuf(ah, bf->bf_daddr);
	ath9k_hw_rxena(ah);

start_recv:
	ath_opmode_init(sc);
	ath9k_hw_startpcureceive(ah, sc->cur_chan->offchannel);
पूर्ण

अटल व्योम ath_flushrecv(काष्ठा ath_softc *sc)
अणु
	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ath_rx_tasklet(sc, 1, true);
	ath_rx_tasklet(sc, 1, false);
पूर्ण

bool ath_stoprecv(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	bool stopped, reset = false;

	ath9k_hw_पातpcurecv(ah);
	ath9k_hw_setrxfilter(ah, 0);
	stopped = ath9k_hw_stopdmarecv(ah, &reset);

	ath_flushrecv(sc);

	अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ath_edma_stop_recv(sc);
	अन्यथा
		sc->rx.rxlink = शून्य;

	अगर (!(ah->ah_flags & AH_UNPLUGGED) &&
	    unlikely(!stopped)) अणु
		ath_dbg(ath9k_hw_common(sc->sc_ah), RESET,
			"Failed to stop Rx DMA\n");
		RESET_STAT_INC(sc, RESET_RX_DMA_ERROR);
	पूर्ण
	वापस stopped && !reset;
पूर्ण

अटल bool ath_beacon_dtim_pending_cab(काष्ठा sk_buff *skb)
अणु
	/* Check whether the Beacon frame has DTIM indicating buffered bc/mc */
	काष्ठा ieee80211_mgmt *mgmt;
	u8 *pos, *end, id, elen;
	काष्ठा ieee80211_tim_ie *tim;

	mgmt = (काष्ठा ieee80211_mgmt *)skb->data;
	pos = mgmt->u.beacon.variable;
	end = skb->data + skb->len;

	जबतक (pos + 2 < end) अणु
		id = *pos++;
		elen = *pos++;
		अगर (pos + elen > end)
			अवरोध;

		अगर (id == WLAN_EID_TIM) अणु
			अगर (elen < माप(*tim))
				अवरोध;
			tim = (काष्ठा ieee80211_tim_ie *) pos;
			अगर (tim->dtim_count != 0)
				अवरोध;
			वापस tim->biपंचांगap_ctrl & 0x01;
		पूर्ण

		pos += elen;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम ath_rx_ps_beacon(काष्ठा ath_softc *sc, काष्ठा sk_buff *skb)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	bool skip_beacon = false;

	अगर (skb->len < 24 + 8 + 2 + 2)
		वापस;

	sc->ps_flags &= ~PS_WAIT_FOR_BEACON;

	अगर (sc->ps_flags & PS_BEACON_SYNC) अणु
		sc->ps_flags &= ~PS_BEACON_SYNC;
		ath_dbg(common, PS,
			"Reconfigure beacon timers based on synchronized timestamp\n");

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT
		अगर (ath9k_is_chanctx_enabled()) अणु
			अगर (sc->cur_chan == &sc->offchannel.chan)
				skip_beacon = true;
		पूर्ण
#पूर्ण_अगर

		अगर (!skip_beacon &&
		    !(WARN_ON_ONCE(sc->cur_chan->beacon.beacon_पूर्णांकerval == 0)))
			ath9k_set_beacon(sc);

		ath9k_p2p_beacon_sync(sc);
	पूर्ण

	अगर (ath_beacon_dtim_pending_cab(skb)) अणु
		/*
		 * Reमुख्य awake रुकोing क्रम buffered broadcast/multicast
		 * frames. If the last broadcast/multicast frame is not
		 * received properly, the next beacon frame will work as
		 * a backup trigger क्रम वापसing पूर्णांकo NETWORK SLEEP state,
		 * so we are रुकोing क्रम it as well.
		 */
		ath_dbg(common, PS,
			"Received DTIM beacon indicating buffered broadcast/multicast frame(s)\n");
		sc->ps_flags |= PS_WAIT_FOR_CAB | PS_WAIT_FOR_BEACON;
		वापस;
	पूर्ण

	अगर (sc->ps_flags & PS_WAIT_FOR_CAB) अणु
		/*
		 * This can happen अगर a broadcast frame is dropped or the AP
		 * fails to send a frame indicating that all CAB frames have
		 * been delivered.
		 */
		sc->ps_flags &= ~PS_WAIT_FOR_CAB;
		ath_dbg(common, PS, "PS wait for CAB frames timed out\n");
	पूर्ण
पूर्ण

अटल व्योम ath_rx_ps(काष्ठा ath_softc *sc, काष्ठा sk_buff *skb, bool mybeacon)
अणु
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	hdr = (काष्ठा ieee80211_hdr *)skb->data;

	/* Process Beacon and CAB receive in PS state */
	अगर (((sc->ps_flags & PS_WAIT_FOR_BEACON) || ath9k_check_स्वतः_sleep(sc))
	    && mybeacon) अणु
		ath_rx_ps_beacon(sc, skb);
	पूर्ण अन्यथा अगर ((sc->ps_flags & PS_WAIT_FOR_CAB) &&
		   (ieee80211_is_data(hdr->frame_control) ||
		    ieee80211_is_action(hdr->frame_control)) &&
		   is_multicast_ether_addr(hdr->addr1) &&
		   !ieee80211_has_moredata(hdr->frame_control)) अणु
		/*
		 * No more broadcast/multicast frames to be received at this
		 * poपूर्णांक.
		 */
		sc->ps_flags &= ~(PS_WAIT_FOR_CAB | PS_WAIT_FOR_BEACON);
		ath_dbg(common, PS,
			"All PS CAB frames received, back to sleep\n");
	पूर्ण अन्यथा अगर ((sc->ps_flags & PS_WAIT_FOR_PSPOLL_DATA) &&
		   !is_multicast_ether_addr(hdr->addr1) &&
		   !ieee80211_has_morefrags(hdr->frame_control)) अणु
		sc->ps_flags &= ~PS_WAIT_FOR_PSPOLL_DATA;
		ath_dbg(common, PS,
			"Going back to sleep after having received PS-Poll data (0x%lx)\n",
			sc->ps_flags & (PS_WAIT_FOR_BEACON |
					PS_WAIT_FOR_CAB |
					PS_WAIT_FOR_PSPOLL_DATA |
					PS_WAIT_FOR_TX_ACK));
	पूर्ण
पूर्ण

अटल bool ath_edma_get_buffers(काष्ठा ath_softc *sc,
				 क्रमागत ath9k_rx_qtype qtype,
				 काष्ठा ath_rx_status *rs,
				 काष्ठा ath_rxbuf **dest)
अणु
	काष्ठा ath_rx_edma *rx_edma = &sc->rx.rx_edma[qtype];
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा sk_buff *skb;
	काष्ठा ath_rxbuf *bf;
	पूर्णांक ret;

	skb = skb_peek(&rx_edma->rx_fअगरo);
	अगर (!skb)
		वापस false;

	bf = SKB_CB_ATHBUF(skb);
	BUG_ON(!bf);

	dma_sync_single_क्रम_cpu(sc->dev, bf->bf_buf_addr,
				common->rx_bufsize, DMA_FROM_DEVICE);

	ret = ath9k_hw_process_rxdesc_edma(ah, rs, skb->data);
	अगर (ret == -EINPROGRESS) अणु
		/*let device gain the buffer again*/
		dma_sync_single_क्रम_device(sc->dev, bf->bf_buf_addr,
				common->rx_bufsize, DMA_FROM_DEVICE);
		वापस false;
	पूर्ण

	__skb_unlink(skb, &rx_edma->rx_fअगरo);
	अगर (ret == -EINVAL) अणु
		/* corrupt descriptor, skip this one and the following one */
		list_add_tail(&bf->list, &sc->rx.rxbuf);
		ath_rx_edma_buf_link(sc, qtype);

		skb = skb_peek(&rx_edma->rx_fअगरo);
		अगर (skb) अणु
			bf = SKB_CB_ATHBUF(skb);
			BUG_ON(!bf);

			__skb_unlink(skb, &rx_edma->rx_fअगरo);
			list_add_tail(&bf->list, &sc->rx.rxbuf);
			ath_rx_edma_buf_link(sc, qtype);
		पूर्ण

		bf = शून्य;
	पूर्ण

	*dest = bf;
	वापस true;
पूर्ण

अटल काष्ठा ath_rxbuf *ath_edma_get_next_rx_buf(काष्ठा ath_softc *sc,
						काष्ठा ath_rx_status *rs,
						क्रमागत ath9k_rx_qtype qtype)
अणु
	काष्ठा ath_rxbuf *bf = शून्य;

	जबतक (ath_edma_get_buffers(sc, qtype, rs, &bf)) अणु
		अगर (!bf)
			जारी;

		वापस bf;
	पूर्ण
	वापस शून्य;
पूर्ण

अटल काष्ठा ath_rxbuf *ath_get_next_rx_buf(काष्ठा ath_softc *sc,
					   काष्ठा ath_rx_status *rs)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_desc *ds;
	काष्ठा ath_rxbuf *bf;
	पूर्णांक ret;

	अगर (list_empty(&sc->rx.rxbuf)) अणु
		sc->rx.rxlink = शून्य;
		वापस शून्य;
	पूर्ण

	bf = list_first_entry(&sc->rx.rxbuf, काष्ठा ath_rxbuf, list);
	अगर (bf == sc->rx.buf_hold)
		वापस शून्य;

	ds = bf->bf_desc;

	/*
	 * Must provide the भव address of the current
	 * descriptor, the physical address, and the भव
	 * address of the next descriptor in the h/w chain.
	 * This allows the HAL to look ahead to see अगर the
	 * hardware is करोne with a descriptor by checking the
	 * करोne bit in the following descriptor and the address
	 * of the current descriptor the DMA engine is working
	 * on.  All this is necessary because of our use of
	 * a self-linked list to aव्योम rx overruns.
	 */
	ret = ath9k_hw_rxprocdesc(ah, ds, rs);
	अगर (ret == -EINPROGRESS) अणु
		काष्ठा ath_rx_status trs;
		काष्ठा ath_rxbuf *tbf;
		काष्ठा ath_desc *tds;

		स_रखो(&trs, 0, माप(trs));
		अगर (list_is_last(&bf->list, &sc->rx.rxbuf)) अणु
			sc->rx.rxlink = शून्य;
			वापस शून्य;
		पूर्ण

		tbf = list_entry(bf->list.next, काष्ठा ath_rxbuf, list);

		/*
		 * On some hardware the descriptor status words could
		 * get corrupted, including the करोne bit. Because of
		 * this, check अगर the next descriptor's करोne bit is
		 * set or not.
		 *
		 * If the next descriptor's करोne bit is set, the current
		 * descriptor has been corrupted. Force s/w to discard
		 * this descriptor and जारी...
		 */

		tds = tbf->bf_desc;
		ret = ath9k_hw_rxprocdesc(ah, tds, &trs);
		अगर (ret == -EINPROGRESS)
			वापस शून्य;

		/*
		 * Re-check previous descriptor, in हाल it has been filled
		 * in the mean समय.
		 */
		ret = ath9k_hw_rxprocdesc(ah, ds, rs);
		अगर (ret == -EINPROGRESS) अणु
			/*
			 * mark descriptor as zero-length and set the 'more'
			 * flag to ensure that both buffers get discarded
			 */
			rs->rs_datalen = 0;
			rs->rs_more = true;
		पूर्ण
	पूर्ण

	list_del(&bf->list);
	अगर (!bf->bf_mpdu)
		वापस bf;

	/*
	 * Synchronize the DMA transfer with CPU beक्रमe
	 * 1. accessing the frame
	 * 2. requeueing the same buffer to h/w
	 */
	dma_sync_single_क्रम_cpu(sc->dev, bf->bf_buf_addr,
			common->rx_bufsize,
			DMA_FROM_DEVICE);

	वापस bf;
पूर्ण

अटल व्योम ath9k_process_tsf(काष्ठा ath_rx_status *rs,
			      काष्ठा ieee80211_rx_status *rxs,
			      u64 tsf)
अणु
	u32 tsf_lower = tsf & 0xffffffff;

	rxs->maस_समय = (tsf & ~0xffffffffULL) | rs->rs_tstamp;
	अगर (rs->rs_tstamp > tsf_lower &&
	    unlikely(rs->rs_tstamp - tsf_lower > 0x10000000))
		rxs->maस_समय -= 0x100000000ULL;

	अगर (rs->rs_tstamp < tsf_lower &&
	    unlikely(tsf_lower - rs->rs_tstamp > 0x10000000))
		rxs->maस_समय += 0x100000000ULL;
पूर्ण

/*
 * For Decrypt or Demic errors, we only mark packet status here and always push
 * up the frame up to let mac80211 handle the actual error हाल, be it no
 * decryption key or real decryption error. This let us keep statistics there.
 */
अटल पूर्णांक ath9k_rx_skb_preprocess(काष्ठा ath_softc *sc,
				   काष्ठा sk_buff *skb,
				   काष्ठा ath_rx_status *rx_stats,
				   काष्ठा ieee80211_rx_status *rx_status,
				   bool *decrypt_error, u64 tsf)
अणु
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_hdr *hdr;
	bool discard_current = sc->rx.discard_next;
	bool is_phyerr;

	/*
	 * Discard corrupt descriptors which are marked in
	 * ath_get_next_rx_buf().
	 */
	अगर (discard_current)
		जाओ corrupt;

	sc->rx.discard_next = false;

	/*
	 * Discard zero-length packets and packets smaller than an ACK
	 * which are not PHY_ERROR (लघु radar pulses have a length of 3)
	 */
	is_phyerr = rx_stats->rs_status & ATH9K_RXERR_PHY;
	अगर (!rx_stats->rs_datalen ||
	    (rx_stats->rs_datalen < 10 && !is_phyerr)) अणु
		RX_STAT_INC(sc, rx_len_err);
		जाओ corrupt;
	पूर्ण

	/*
	 * rs_status follows rs_datalen so अगर rs_datalen is too large
	 * we can take a hपूर्णांक that hardware corrupted it, so ignore
	 * those frames.
	 */
	अगर (rx_stats->rs_datalen > (common->rx_bufsize - ah->caps.rx_status_len)) अणु
		RX_STAT_INC(sc, rx_len_err);
		जाओ corrupt;
	पूर्ण

	/* Only use status info from the last fragment */
	अगर (rx_stats->rs_more)
		वापस 0;

	/*
	 * Return immediately अगर the RX descriptor has been marked
	 * as corrupt based on the various error bits.
	 *
	 * This is dअगरferent from the other corrupt descriptor
	 * condition handled above.
	 */
	अगर (rx_stats->rs_status & ATH9K_RXERR_CORRUPT_DESC)
		जाओ corrupt;

	hdr = (काष्ठा ieee80211_hdr *) (skb->data + ah->caps.rx_status_len);

	ath9k_process_tsf(rx_stats, rx_status, tsf);
	ath_debug_stat_rx(sc, rx_stats);

	/*
	 * Process PHY errors and वापस so that the packet
	 * can be dropped.
	 */
	अगर (rx_stats->rs_status & ATH9K_RXERR_PHY) अणु
		/*
		 * DFS and spectral are mutually exclusive
		 *
		 * Since some chips use PHYERR_RADAR as indication क्रम both, we
		 * need to द्विगुन check which feature is enabled to prevent
		 * feeding spectral or dfs-detector with wrong frames.
		 */
		अगर (hw->conf.radar_enabled) अणु
			ath9k_dfs_process_phyerr(sc, hdr, rx_stats,
						 rx_status->maस_समय);
		पूर्ण अन्यथा अगर (sc->spec_priv.spectral_mode != SPECTRAL_DISABLED &&
			   ath_cmn_process_fft(&sc->spec_priv, hdr, rx_stats,
					       rx_status->maस_समय)) अणु
			RX_STAT_INC(sc, rx_spectral);
		पूर्ण
		वापस -EINVAL;
	पूर्ण

	/*
	 * everything but the rate is checked here, the rate check is करोne
	 * separately to aव्योम करोing two lookups क्रम a rate क्रम each frame.
	 */
	spin_lock_bh(&sc->chan_lock);
	अगर (!ath9k_cmn_rx_accept(common, hdr, rx_status, rx_stats, decrypt_error,
				 sc->cur_chan->rxfilter)) अणु
		spin_unlock_bh(&sc->chan_lock);
		वापस -EINVAL;
	पूर्ण
	spin_unlock_bh(&sc->chan_lock);

	अगर (ath_is_mybeacon(common, hdr)) अणु
		RX_STAT_INC(sc, rx_beacons);
		rx_stats->is_mybeacon = true;
	पूर्ण

	/*
	 * This shouldn't happen, but have a safety check anyway.
	 */
	अगर (WARN_ON(!ah->curchan))
		वापस -EINVAL;

	अगर (ath9k_cmn_process_rate(common, hw, rx_stats, rx_status)) अणु
		/*
		 * No valid hardware bitrate found -- we should not get here
		 * because hardware has alपढ़ोy validated this frame as OK.
		 */
		ath_dbg(common, ANY, "unsupported hw bitrate detected 0x%02x using 1 Mbit\n",
			rx_stats->rs_rate);
		RX_STAT_INC(sc, rx_rate_err);
		वापस -EINVAL;
	पूर्ण

	अगर (ath9k_is_chanctx_enabled()) अणु
		अगर (rx_stats->is_mybeacon)
			ath_chanctx_beacon_recv_ev(sc,
					   ATH_CHANCTX_EVENT_BEACON_RECEIVED);
	पूर्ण

	ath9k_cmn_process_rssi(common, hw, rx_stats, rx_status);

	rx_status->band = ah->curchan->chan->band;
	rx_status->freq = ah->curchan->chan->center_freq;
	rx_status->antenna = rx_stats->rs_antenna;
	rx_status->flag |= RX_FLAG_MACTIME_END;

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	अगर (ieee80211_is_data_present(hdr->frame_control) &&
	    !ieee80211_is_qos_nullfunc(hdr->frame_control))
		sc->rx.num_pkts++;
#पूर्ण_अगर

	वापस 0;

corrupt:
	sc->rx.discard_next = rx_stats->rs_more;
	वापस -EINVAL;
पूर्ण

/*
 * Run the LNA combining algorithm only in these हालs:
 *
 * Standalone WLAN cards with both LNA/Antenna भागersity
 * enabled in the EEPROM.
 *
 * WLAN+BT cards which are in the supported card list
 * in ath_pci_id_table and the user has loaded the
 * driver with "bt_ant_diversity" set to true.
 */
अटल व्योम ath9k_antenna_check(काष्ठा ath_softc *sc,
				काष्ठा ath_rx_status *rs)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_hw_capabilities *pCap = &ah->caps;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!(ah->caps.hw_caps & ATH9K_HW_CAP_ANT_DIV_COMB))
		वापस;

	/*
	 * Change the शेष rx antenna अगर rx भागersity
	 * chooses the other antenna 3 बार in a row.
	 */
	अगर (sc->rx.defant != rs->rs_antenna) अणु
		अगर (++sc->rx.rxotherant >= 3)
			ath_setdefantenna(sc, rs->rs_antenna);
	पूर्ण अन्यथा अणु
		sc->rx.rxotherant = 0;
	पूर्ण

	अगर (pCap->hw_caps & ATH9K_HW_CAP_BT_ANT_DIV) अणु
		अगर (common->bt_ant_भागersity)
			ath_ant_comb_scan(sc, rs);
	पूर्ण अन्यथा अणु
		ath_ant_comb_scan(sc, rs);
	पूर्ण
पूर्ण

अटल व्योम ath9k_apply_ampdu_details(काष्ठा ath_softc *sc,
	काष्ठा ath_rx_status *rs, काष्ठा ieee80211_rx_status *rxs)
अणु
	अगर (rs->rs_isaggr) अणु
		rxs->flag |= RX_FLAG_AMPDU_DETAILS | RX_FLAG_AMPDU_LAST_KNOWN;

		rxs->ampdu_reference = sc->rx.ampdu_ref;

		अगर (!rs->rs_moreaggr) अणु
			rxs->flag |= RX_FLAG_AMPDU_IS_LAST;
			sc->rx.ampdu_ref++;
		पूर्ण

		अगर (rs->rs_flags & ATH9K_RX_DELIM_CRC_PRE)
			rxs->flag |= RX_FLAG_AMPDU_DELIM_CRC_ERROR;
	पूर्ण
पूर्ण

अटल व्योम ath_rx_count_airसमय(काष्ठा ath_softc *sc,
				 काष्ठा ath_rx_status *rs,
				 काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_sta *sta;
	काष्ठा ieee80211_rx_status *rxs;
	स्थिर काष्ठा ieee80211_rate *rate;
	bool is_sgi, is_40, is_sp;
	पूर्णांक phy;
	u16 len = rs->rs_datalen;
	u32 airसमय = 0;
	u8 tidno;

	अगर (!ieee80211_is_data(hdr->frame_control))
		वापस;

	rcu_पढ़ो_lock();

	sta = ieee80211_find_sta_by_अगरaddr(sc->hw, hdr->addr2, शून्य);
	अगर (!sta)
		जाओ निकास;
	tidno = skb->priority & IEEE80211_QOS_CTL_TID_MASK;

	rxs = IEEE80211_SKB_RXCB(skb);

	is_sgi = !!(rxs->enc_flags & RX_ENC_FLAG_SHORT_GI);
	is_40 = !!(rxs->bw == RATE_INFO_BW_40);
	is_sp = !!(rxs->enc_flags & RX_ENC_FLAG_SHORTPRE);

	अगर (!!(rxs->encoding == RX_ENC_HT)) अणु
		/* MCS rates */

		airसमय += ath_pkt_duration(sc, rxs->rate_idx, len,
					is_40, is_sgi, is_sp);
	पूर्ण अन्यथा अणु

		phy = IS_CCK_RATE(rs->rs_rate) ? WLAN_RC_PHY_CCK : WLAN_RC_PHY_OFDM;
		rate = &common->sbands[rxs->band].bitrates[rxs->rate_idx];
		airसमय += ath9k_hw_computetxसमय(ah, phy, rate->bitrate * 100,
						len, rxs->rate_idx, is_sp);
	पूर्ण

	ieee80211_sta_रेजिस्टर_airसमय(sta, tidno, 0, airसमय);
निकास:
	rcu_पढ़ो_unlock();
पूर्ण

पूर्णांक ath_rx_tasklet(काष्ठा ath_softc *sc, पूर्णांक flush, bool hp)
अणु
	काष्ठा ath_rxbuf *bf;
	काष्ठा sk_buff *skb = शून्य, *requeue_skb, *hdr_skb;
	काष्ठा ieee80211_rx_status *rxs;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_hw *hw = sc->hw;
	पूर्णांक retval;
	काष्ठा ath_rx_status rs;
	क्रमागत ath9k_rx_qtype qtype;
	bool edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	पूर्णांक dma_type;
	u64 tsf = 0;
	अचिन्हित दीर्घ flags;
	dma_addr_t new_buf_addr;
	अचिन्हित पूर्णांक budget = 512;
	काष्ठा ieee80211_hdr *hdr;

	अगर (edma)
		dma_type = DMA_BIसूचीECTIONAL;
	अन्यथा
		dma_type = DMA_FROM_DEVICE;

	qtype = hp ? ATH9K_RX_QUEUE_HP : ATH9K_RX_QUEUE_LP;

	tsf = ath9k_hw_gettsf64(ah);

	करो अणु
		bool decrypt_error = false;

		स_रखो(&rs, 0, माप(rs));
		अगर (edma)
			bf = ath_edma_get_next_rx_buf(sc, &rs, qtype);
		अन्यथा
			bf = ath_get_next_rx_buf(sc, &rs);

		अगर (!bf)
			अवरोध;

		skb = bf->bf_mpdu;
		अगर (!skb)
			जारी;

		/*
		 * Take frame header from the first fragment and RX status from
		 * the last one.
		 */
		अगर (sc->rx.frag)
			hdr_skb = sc->rx.frag;
		अन्यथा
			hdr_skb = skb;

		rxs = IEEE80211_SKB_RXCB(hdr_skb);
		स_रखो(rxs, 0, माप(काष्ठा ieee80211_rx_status));

		retval = ath9k_rx_skb_preprocess(sc, hdr_skb, &rs, rxs,
						 &decrypt_error, tsf);
		अगर (retval)
			जाओ requeue_drop_frag;

		/* Ensure we always have an skb to requeue once we are करोne
		 * processing the current buffer's skb */
		requeue_skb = ath_rxbuf_alloc(common, common->rx_bufsize, GFP_ATOMIC);

		/* If there is no memory we ignore the current RX'd frame,
		 * tell hardware it can give us a new frame using the old
		 * skb and put it at the tail of the sc->rx.rxbuf list क्रम
		 * processing. */
		अगर (!requeue_skb) अणु
			RX_STAT_INC(sc, rx_oom_err);
			जाओ requeue_drop_frag;
		पूर्ण

		/* We will now give hardware our shiny new allocated skb */
		new_buf_addr = dma_map_single(sc->dev, requeue_skb->data,
					      common->rx_bufsize, dma_type);
		अगर (unlikely(dma_mapping_error(sc->dev, new_buf_addr))) अणु
			dev_kमुक्त_skb_any(requeue_skb);
			जाओ requeue_drop_frag;
		पूर्ण

		/* Unmap the frame */
		dma_unmap_single(sc->dev, bf->bf_buf_addr,
				 common->rx_bufsize, dma_type);

		bf->bf_mpdu = requeue_skb;
		bf->bf_buf_addr = new_buf_addr;

		skb_put(skb, rs.rs_datalen + ah->caps.rx_status_len);
		अगर (ah->caps.rx_status_len)
			skb_pull(skb, ah->caps.rx_status_len);

		अगर (!rs.rs_more)
			ath9k_cmn_rx_skb_postprocess(common, hdr_skb, &rs,
						     rxs, decrypt_error);

		अगर (rs.rs_more) अणु
			RX_STAT_INC(sc, rx_frags);
			/*
			 * rs_more indicates chained descriptors which can be
			 * used to link buffers together क्रम a sort of
			 * scatter-gather operation.
			 */
			अगर (sc->rx.frag) अणु
				/* too many fragments - cannot handle frame */
				dev_kमुक्त_skb_any(sc->rx.frag);
				dev_kमुक्त_skb_any(skb);
				RX_STAT_INC(sc, rx_too_many_frags_err);
				skb = शून्य;
			पूर्ण
			sc->rx.frag = skb;
			जाओ requeue;
		पूर्ण

		अगर (sc->rx.frag) अणु
			पूर्णांक space = skb->len - skb_tailroom(hdr_skb);

			अगर (pskb_expand_head(hdr_skb, 0, space, GFP_ATOMIC) < 0) अणु
				dev_kमुक्त_skb(skb);
				RX_STAT_INC(sc, rx_oom_err);
				जाओ requeue_drop_frag;
			पूर्ण

			sc->rx.frag = शून्य;

			skb_copy_from_linear_data(skb, skb_put(hdr_skb, skb->len),
						  skb->len);
			dev_kमुक्त_skb_any(skb);
			skb = hdr_skb;
		पूर्ण

		अगर (rxs->flag & RX_FLAG_MMIC_STRIPPED)
			skb_trim(skb, skb->len - 8);

		spin_lock_irqsave(&sc->sc_pm_lock, flags);
		अगर ((sc->ps_flags & (PS_WAIT_FOR_BEACON |
				     PS_WAIT_FOR_CAB |
				     PS_WAIT_FOR_PSPOLL_DATA)) ||
		    ath9k_check_स्वतः_sleep(sc))
			ath_rx_ps(sc, skb, rs.is_mybeacon);
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

		ath9k_antenna_check(sc, &rs);
		ath9k_apply_ampdu_details(sc, &rs, rxs);
		ath_debug_rate_stats(sc, &rs, skb);
		ath_rx_count_airसमय(sc, &rs, skb);

		hdr = (काष्ठा ieee80211_hdr *)skb->data;
		अगर (ieee80211_is_ack(hdr->frame_control))
			ath_dynack_sample_ack_ts(sc->sc_ah, skb, rs.rs_tstamp);

		ieee80211_rx(hw, skb);

requeue_drop_frag:
		अगर (sc->rx.frag) अणु
			dev_kमुक्त_skb_any(sc->rx.frag);
			sc->rx.frag = शून्य;
		पूर्ण
requeue:
		list_add_tail(&bf->list, &sc->rx.rxbuf);

		अगर (!edma) अणु
			ath_rx_buf_relink(sc, bf, flush);
			अगर (!flush)
				ath9k_hw_rxena(ah);
		पूर्ण अन्यथा अगर (!flush) अणु
			ath_rx_edma_buf_link(sc, qtype);
		पूर्ण

		अगर (!budget--)
			अवरोध;
	पूर्ण जबतक (1);

	अगर (!(ah->imask & ATH9K_INT_RXEOL)) अणु
		ah->imask |= (ATH9K_INT_RXEOL | ATH9K_INT_RXORN);
		ath9k_hw_set_पूर्णांकerrupts(ah);
	पूर्ण

	वापस 0;
पूर्ण
