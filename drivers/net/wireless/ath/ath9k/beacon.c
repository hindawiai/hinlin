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

#घोषणा FUDGE 2

अटल व्योम ath9k_reset_beacon_status(काष्ठा ath_softc *sc)
अणु
	sc->beacon.tx_processed = false;
	sc->beacon.tx_last = false;
पूर्ण

/*
 *  This function will modअगरy certain transmit queue properties depending on
 *  the operating mode of the station (AP or AdHoc).  Parameters are AIFS
 *  settings and channel width min/max
*/
अटल व्योम ath9k_beaconq_config(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_tx_queue_info qi, qi_be;
	काष्ठा ath_txq *txq;

	ath9k_hw_get_txq_props(ah, sc->beacon.beaconq, &qi);

	अगर (sc->sc_ah->opmode == NL80211_IFTYPE_AP ||
	    sc->sc_ah->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		/* Always burst out beacon and CAB traffic. */
		qi.tqi_aअगरs = 1;
		qi.tqi_cwmin = 0;
		qi.tqi_cwmax = 0;
	पूर्ण अन्यथा अणु
		/* Adhoc mode; important thing is to use 2x cwmin. */
		txq = sc->tx.txq_map[IEEE80211_AC_BE];
		ath9k_hw_get_txq_props(ah, txq->axq_qnum, &qi_be);
		qi.tqi_aअगरs = qi_be.tqi_aअगरs;
		अगर (ah->slotसमय == 20)
			qi.tqi_cwmin = 2*qi_be.tqi_cwmin;
		अन्यथा
			qi.tqi_cwmin = 4*qi_be.tqi_cwmin;
		qi.tqi_cwmax = qi_be.tqi_cwmax;
	पूर्ण

	अगर (!ath9k_hw_set_txq_props(ah, sc->beacon.beaconq, &qi)) अणु
		ath_err(common, "Unable to update h/w beacon queue parameters\n");
	पूर्ण अन्यथा अणु
		ath9k_hw_resettxqueue(ah, sc->beacon.beaconq);
	पूर्ण
पूर्ण

/*
 *  Associates the beacon frame buffer with a transmit descriptor.  Will set
 *  up rate codes, and channel flags. Beacons are always sent out at the
 *  lowest rate, and are not retried.
*/
अटल व्योम ath9k_beacon_setup(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ath_buf *bf, पूर्णांक rateidx)
अणु
	काष्ठा sk_buff *skb = bf->bf_mpdu;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_tx_info info;
	काष्ठा ieee80211_supported_band *sband;
	u8 chainmask = ah->txchainmask;
	u8 i, rate = 0;

	sband = &common->sbands[sc->cur_chandef.chan->band];
	rate = sband->bitrates[rateidx].hw_value;
	अगर (vअगर->bss_conf.use_लघु_preamble)
		rate |= sband->bitrates[rateidx].hw_value_लघु;

	स_रखो(&info, 0, माप(info));
	info.pkt_len = skb->len + FCS_LEN;
	info.type = ATH9K_PKT_TYPE_BEACON;
	क्रम (i = 0; i < 4; i++)
		info.txघातer[i] = MAX_RATE_POWER;
	info.keyix = ATH9K_TXKEYIX_INVALID;
	info.keytype = ATH9K_KEY_TYPE_CLEAR;
	info.flags = ATH9K_TXDESC_NOACK | ATH9K_TXDESC_CLRDMASK;

	info.buf_addr[0] = bf->bf_buf_addr;
	info.buf_len[0] = roundup(skb->len, 4);

	info.is_first = true;
	info.is_last = true;

	info.qcu = sc->beacon.beaconq;

	info.rates[0].Tries = 1;
	info.rates[0].Rate = rate;
	info.rates[0].ChSel = ath_txchainmask_reduction(sc, chainmask, rate);

	ath9k_hw_set_txdesc(ah, bf->bf_desc, &info);
पूर्ण

अटल काष्ठा ath_buf *ath9k_beacon_generate(काष्ठा ieee80211_hw *hw,
					     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_buf *bf;
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	काष्ठा sk_buff *skb;
	काष्ठा ath_txq *cabq = sc->beacon.cabq;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_mgmt *mgmt_hdr;
	पूर्णांक cabq_depth;

	अगर (avp->av_bcbuf == शून्य)
		वापस शून्य;

	bf = avp->av_bcbuf;
	skb = bf->bf_mpdu;
	अगर (skb) अणु
		dma_unmap_single(sc->dev, bf->bf_buf_addr,
				 skb->len, DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(skb);
		bf->bf_buf_addr = 0;
		bf->bf_mpdu = शून्य;
	पूर्ण

	skb = ieee80211_beacon_get(hw, vअगर);
	अगर (skb == शून्य)
		वापस शून्य;

	bf->bf_mpdu = skb;

	mgmt_hdr = (काष्ठा ieee80211_mgmt *)skb->data;
	mgmt_hdr->u.beacon.बारtamp = avp->tsf_adjust;

	info = IEEE80211_SKB_CB(skb);

	ath_assign_seq(common, skb);

	/* Always assign NOA attr when MCC enabled */
	अगर (ath9k_is_chanctx_enabled())
		ath9k_beacon_add_noa(sc, avp, skb);

	bf->bf_buf_addr = dma_map_single(sc->dev, skb->data,
					 skb->len, DMA_TO_DEVICE);
	अगर (unlikely(dma_mapping_error(sc->dev, bf->bf_buf_addr))) अणु
		dev_kमुक्त_skb_any(skb);
		bf->bf_mpdu = शून्य;
		bf->bf_buf_addr = 0;
		ath_err(common, "dma_mapping_error on beaconing\n");
		वापस शून्य;
	पूर्ण

	skb = ieee80211_get_buffered_bc(hw, vअगर);

	/*
	 * अगर the CABQ traffic from previous DTIM is pending and the current
	 *  beacon is also a DTIM.
	 *  1) अगर there is only one vअगर let the cab traffic जारी.
	 *  2) अगर there are more than one vअगर and we are using staggered
	 *     beacons, then drain the cabq by dropping all the frames in
	 *     the cabq so that the current vअगरs cab traffic can be scheduled.
	 */
	spin_lock_bh(&cabq->axq_lock);
	cabq_depth = cabq->axq_depth;
	spin_unlock_bh(&cabq->axq_lock);

	अगर (skb && cabq_depth) अणु
		अगर (sc->cur_chan->nvअगरs > 1) अणु
			ath_dbg(common, BEACON,
				"Flushing previous cabq traffic\n");
			ath_draपूर्णांकxq(sc, cabq);
		पूर्ण
	पूर्ण

	ath9k_beacon_setup(sc, vअगर, bf, info->control.rates[0].idx);

	अगर (skb)
		ath_tx_cabq(hw, vअगर, skb);

	वापस bf;
पूर्ण

व्योम ath9k_beacon_assign_slot(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	पूर्णांक slot;

	avp->av_bcbuf = list_first_entry(&sc->beacon.bbuf, काष्ठा ath_buf, list);
	list_del(&avp->av_bcbuf->list);

	क्रम (slot = 0; slot < ATH_BCBUF; slot++) अणु
		अगर (sc->beacon.bslot[slot] == शून्य) अणु
			avp->av_bslot = slot;
			अवरोध;
		पूर्ण
	पूर्ण

	sc->beacon.bslot[avp->av_bslot] = vअगर;

	ath_dbg(common, CONFIG, "Added interface at beacon slot: %d\n",
		avp->av_bslot);
पूर्ण

व्योम ath9k_beacon_हटाओ_slot(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	काष्ठा ath_buf *bf = avp->av_bcbuf;

	ath_dbg(common, CONFIG, "Removing interface at beacon slot: %d\n",
		avp->av_bslot);

	tasklet_disable(&sc->bcon_tasklet);

	अगर (bf && bf->bf_mpdu) अणु
		काष्ठा sk_buff *skb = bf->bf_mpdu;
		dma_unmap_single(sc->dev, bf->bf_buf_addr,
				 skb->len, DMA_TO_DEVICE);
		dev_kमुक्त_skb_any(skb);
		bf->bf_mpdu = शून्य;
		bf->bf_buf_addr = 0;
	पूर्ण

	avp->av_bcbuf = शून्य;
	sc->beacon.bslot[avp->av_bslot] = शून्य;
	list_add_tail(&bf->list, &sc->beacon.bbuf);

	tasklet_enable(&sc->bcon_tasklet);
पूर्ण

व्योम ath9k_beacon_ensure_primary_slot(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ath_vअगर *avp;
	s64 tsfadjust;
	u32 offset;
	पूर्णांक first_slot = ATH_BCBUF;
	पूर्णांक slot;

	tasklet_disable_in_atomic(&sc->bcon_tasklet);

	/* Find first taken slot. */
	क्रम (slot = 0; slot < ATH_BCBUF; slot++) अणु
		अगर (sc->beacon.bslot[slot]) अणु
			first_slot = slot;
			अवरोध;
		पूर्ण
	पूर्ण
	अगर (first_slot == 0)
		जाओ out;

	/* Re-क्रमागतarate all slots, moving them क्रमward. */
	क्रम (slot = 0; slot < ATH_BCBUF; slot++) अणु
		अगर (slot + first_slot < ATH_BCBUF) अणु
			vअगर = sc->beacon.bslot[slot + first_slot];
			sc->beacon.bslot[slot] = vअगर;

			अगर (vअगर) अणु
				avp = (व्योम *)vअगर->drv_priv;
				avp->av_bslot = slot;
			पूर्ण
		पूर्ण अन्यथा अणु
			sc->beacon.bslot[slot] = शून्य;
		पूर्ण
	पूर्ण

	vअगर = sc->beacon.bslot[0];
	अगर (WARN_ON(!vअगर))
		जाओ out;

	/* Get the tsf_adjust value क्रम the new first slot. */
	avp = (व्योम *)vअगर->drv_priv;
	tsfadjust = le64_to_cpu(avp->tsf_adjust);

	ath_dbg(common, CONFIG,
		"Adjusting global TSF after beacon slot reassignment: %lld\n",
		(चिन्हित दीर्घ दीर्घ)tsfadjust);

	/* Modअगरy TSF as required and update the HW. */
	avp->chanctx->tsf_val += tsfadjust;
	अगर (sc->cur_chan == avp->chanctx) अणु
		offset = ath9k_hw_get_tsf_offset(&avp->chanctx->tsf_ts, शून्य);
		ath9k_hw_settsf64(sc->sc_ah, avp->chanctx->tsf_val + offset);
	पूर्ण

	/* The slots tsf_adjust will be updated by ath9k_beacon_config later. */

out:
	tasklet_enable(&sc->bcon_tasklet);
पूर्ण

अटल पूर्णांक ath9k_beacon_choose_slot(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_beacon_config *cur_conf = &sc->cur_chan->beacon;
	u16 पूर्णांकval;
	u32 tsftu;
	u64 tsf;
	पूर्णांक slot;

	अगर (sc->sc_ah->opmode != NL80211_IFTYPE_AP &&
	    sc->sc_ah->opmode != NL80211_IFTYPE_MESH_POINT) अणु
		ath_dbg(common, BEACON, "slot 0, tsf: %llu\n",
			ath9k_hw_gettsf64(sc->sc_ah));
		वापस 0;
	पूर्ण

	पूर्णांकval = cur_conf->beacon_पूर्णांकerval ? : ATH_DEFAULT_BINTVAL;
	tsf = ath9k_hw_gettsf64(sc->sc_ah);
	tsf += TU_TO_USEC(sc->sc_ah->config.sw_beacon_response_समय);
	tsftu = TSF_TO_TU((tsf * ATH_BCBUF) >>32, tsf * ATH_BCBUF);
	slot = (tsftu % (पूर्णांकval * ATH_BCBUF)) / पूर्णांकval;

	ath_dbg(common, BEACON, "slot: %d tsf: %llu tsftu: %u\n",
		slot, tsf, tsftu / ATH_BCBUF);

	वापस slot;
पूर्ण

अटल व्योम ath9k_set_tsfadjust(काष्ठा ath_softc *sc,
				काष्ठा ath_beacon_config *cur_conf)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	s64 tsfadjust;
	पूर्णांक slot;

	क्रम (slot = 0; slot < ATH_BCBUF; slot++) अणु
		काष्ठा ath_vअगर *avp;

		अगर (!sc->beacon.bslot[slot])
			जारी;

		avp = (व्योम *)sc->beacon.bslot[slot]->drv_priv;

		/* tsf_adjust is added to the TSF value. We send out the
		 * beacon late, so need to adjust the TSF starting poपूर्णांक to be
		 * later in समय (i.e. the theoretical first beacon has a TSF
		 * of 0 after correction).
		 */
		tsfadjust = cur_conf->beacon_पूर्णांकerval * avp->av_bslot;
		tsfadjust = -TU_TO_USEC(tsfadjust) / ATH_BCBUF;
		avp->tsf_adjust = cpu_to_le64(tsfadjust);

		ath_dbg(common, CONFIG, "tsfadjust is: %lld for bslot: %d\n",
			(चिन्हित दीर्घ दीर्घ)tsfadjust, avp->av_bslot);
	पूर्ण
पूर्ण

bool ath9k_csa_is_finished(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (!vअगर || !vअगर->csa_active)
		वापस false;

	अगर (!ieee80211_beacon_cntdwn_is_complete(vअगर))
		वापस false;

	ieee80211_csa_finish(vअगर);
	वापस true;
पूर्ण

अटल व्योम ath9k_csa_update_vअगर(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = data;
	ath9k_csa_is_finished(sc, vअगर);
पूर्ण

व्योम ath9k_csa_update(काष्ठा ath_softc *sc)
अणु
	ieee80211_iterate_active_पूर्णांकerfaces_atomic(sc->hw,
						   IEEE80211_IFACE_ITER_NORMAL,
						   ath9k_csa_update_vअगर, sc);
पूर्ण

व्योम ath9k_beacon_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath_softc *sc = from_tasklet(sc, t, bcon_tasklet);
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_buf *bf = शून्य;
	काष्ठा ieee80211_vअगर *vअगर;
	bool edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	पूर्णांक slot;

	अगर (test_bit(ATH_OP_HW_RESET, &common->op_flags)) अणु
		ath_dbg(common, RESET,
			"reset work is pending, skip beaconing now\n");
		वापस;
	पूर्ण

	/*
	 * Check अगर the previous beacon has gone out.  If
	 * not करोn't try to post another, skip this period
	 * and रुको क्रम the next.  Missed beacons indicate
	 * a problem and should not occur.  If we miss too
	 * many consecutive beacons reset the device.
	 */
	अगर (ath9k_hw_numtxpending(ah, sc->beacon.beaconq) != 0) अणु
		sc->beacon.bmisscnt++;

		ath9k_hw_check_nav(ah);

		/*
		 * If the previous beacon has not been transmitted
		 * and a MAC/BB hang has been identअगरied, वापस
		 * here because a chip reset would have been
		 * initiated.
		 */
		अगर (!ath_hw_check(sc))
			वापस;

		अगर (sc->beacon.bmisscnt < BSTUCK_THRESH * sc->nbcnvअगरs) अणु
			ath_dbg(common, BSTUCK,
				"missed %u consecutive beacons\n",
				sc->beacon.bmisscnt);
			ath9k_hw_stop_dma_queue(ah, sc->beacon.beaconq);
			अगर (sc->beacon.bmisscnt > 3)
				ath9k_hw_bstuck_nfcal(ah);
		पूर्ण अन्यथा अगर (sc->beacon.bmisscnt >= BSTUCK_THRESH) अणु
			ath_dbg(common, BSTUCK, "beacon is officially stuck\n");
			sc->beacon.bmisscnt = 0;
			ath9k_queue_reset(sc, RESET_TYPE_BEACON_STUCK);
		पूर्ण

		वापस;
	पूर्ण

	slot = ath9k_beacon_choose_slot(sc);
	vअगर = sc->beacon.bslot[slot];

	/* EDMA devices check that in the tx completion function. */
	अगर (!edma) अणु
		अगर (ath9k_is_chanctx_enabled()) अणु
			ath_chanctx_beacon_sent_ev(sc,
					  ATH_CHANCTX_EVENT_BEACON_SENT);
		पूर्ण

		अगर (ath9k_csa_is_finished(sc, vअगर))
			वापस;
	पूर्ण

	अगर (!vअगर || !vअगर->bss_conf.enable_beacon)
		वापस;

	अगर (ath9k_is_chanctx_enabled()) अणु
		ath_chanctx_event(sc, vअगर, ATH_CHANCTX_EVENT_BEACON_PREPARE);
	पूर्ण

	bf = ath9k_beacon_generate(sc->hw, vअगर);

	अगर (sc->beacon.bmisscnt != 0) अणु
		ath_dbg(common, BSTUCK, "resume beacon xmit after %u misses\n",
			sc->beacon.bmisscnt);
		sc->beacon.bmisscnt = 0;
	पूर्ण

	/*
	 * Handle slot समय change when a non-ERP station joins/leaves
	 * an 11g network.  The 802.11 layer notअगरies us via callback,
	 * we mark updateslot, then रुको one beacon beक्रमe effecting
	 * the change.  This gives associated stations at least one
	 * beacon पूर्णांकerval to note the state change.
	 *
	 * NB: The slot समय change state machine is घड़ीed according
	 *     to whether we are bursting or staggering beacons.  We
	 *     recognize the request to update and record the current
	 *     slot then करोn't transition until that slot is reached
	 *     again.  If we miss a beacon क्रम that slot then we'll be
	 *     slow to transition but we'll be sure at least one beacon
	 *     पूर्णांकerval has passed.  When bursting slot is always left
	 *     set to ATH_BCBUF so this check is a noop.
	 */
	अगर (sc->beacon.updateslot == UPDATE) अणु
		sc->beacon.updateslot = COMMIT;
		sc->beacon.slotupdate = slot;
	पूर्ण अन्यथा अगर (sc->beacon.updateslot == COMMIT &&
		   sc->beacon.slotupdate == slot) अणु
		ah->slotसमय = sc->beacon.slotसमय;
		ath9k_hw_init_global_settings(ah);
		sc->beacon.updateslot = OK;
	पूर्ण

	अगर (bf) अणु
		ath9k_reset_beacon_status(sc);

		ath_dbg(common, BEACON,
			"Transmitting beacon for slot: %d\n", slot);

		/* NB: cabq traffic should alपढ़ोy be queued and primed */
		ath9k_hw_puttxbuf(ah, sc->beacon.beaconq, bf->bf_daddr);

		अगर (!edma)
			ath9k_hw_txstart(ah, sc->beacon.beaconq);
	पूर्ण
पूर्ण

/*
 * Both nexttbtt and पूर्णांकval have to be in usecs.
 */
अटल व्योम ath9k_beacon_init(काष्ठा ath_softc *sc, u32 nexttbtt,
			      u32 पूर्णांकval)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;

	ath9k_hw_disable_पूर्णांकerrupts(ah);
	ath9k_beaconq_config(sc);
	ath9k_hw_beaconinit(ah, nexttbtt, पूर्णांकval);
	ah->imask |= ATH9K_INT_SWBA;
	sc->beacon.bmisscnt = 0;
	ath9k_hw_set_पूर्णांकerrupts(ah);
	ath9k_hw_enable_पूर्णांकerrupts(ah);
पूर्ण

अटल व्योम ath9k_beacon_stop(काष्ठा ath_softc *sc)
अणु
	ath9k_hw_disable_पूर्णांकerrupts(sc->sc_ah);
	sc->sc_ah->imask &= ~(ATH9K_INT_SWBA | ATH9K_INT_BMISS);
	sc->beacon.bmisscnt = 0;
	ath9k_hw_set_पूर्णांकerrupts(sc->sc_ah);
	ath9k_hw_enable_पूर्णांकerrupts(sc->sc_ah);
पूर्ण

/*
 * For multi-bss ap support beacons are either staggered evenly over N slots or
 * burst together.  For the क्रमmer arrange क्रम the SWBA to be delivered क्रम each
 * slot. Slots that are not occupied will generate nothing.
 */
अटल व्योम ath9k_beacon_config_ap(काष्ठा ath_softc *sc,
				   काष्ठा ath_beacon_config *conf)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;

	ath9k_cmn_beacon_config_ap(ah, conf, ATH_BCBUF);
	ath9k_beacon_init(sc, conf->nexttbtt, conf->पूर्णांकval);
पूर्ण

अटल व्योम ath9k_beacon_config_sta(काष्ठा ath_hw *ah,
				    काष्ठा ath_beacon_config *conf)
अणु
	काष्ठा ath9k_beacon_state bs;

	अगर (ath9k_cmn_beacon_config_sta(ah, conf, &bs) == -EPERM)
		वापस;

	ath9k_hw_disable_पूर्णांकerrupts(ah);
	ath9k_hw_set_sta_beacon_समयrs(ah, &bs);
	ah->imask |= ATH9K_INT_BMISS;

	ath9k_hw_set_पूर्णांकerrupts(ah);
	ath9k_hw_enable_पूर्णांकerrupts(ah);
पूर्ण

अटल व्योम ath9k_beacon_config_adhoc(काष्ठा ath_softc *sc,
				      काष्ठा ath_beacon_config *conf)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	ath9k_reset_beacon_status(sc);

	ath9k_cmn_beacon_config_adhoc(ah, conf);

	ath9k_beacon_init(sc, conf->nexttbtt, conf->पूर्णांकval);

	/*
	 * Set the global 'beacon has been configured' flag क्रम the
	 * joiner हाल in IBSS mode.
	 */
	अगर (!conf->ibss_creator && conf->enable_beacon)
		set_bit(ATH_OP_BEACONS, &common->op_flags);
पूर्ण

अटल व्योम ath9k_cache_beacon_config(काष्ठा ath_softc *sc,
				      काष्ठा ath_chanctx *ctx,
				      काष्ठा ieee80211_bss_conf *bss_conf)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_beacon_config *cur_conf = &ctx->beacon;

	ath_dbg(common, BEACON,
		"Caching beacon data for BSS: %pM\n", bss_conf->bssid);

	cur_conf->beacon_पूर्णांकerval = bss_conf->beacon_पूर्णांक;
	cur_conf->dtim_period = bss_conf->dtim_period;
	cur_conf->dtim_count = 1;
	cur_conf->ibss_creator = bss_conf->ibss_creator;

	/*
	 * It looks like mac80211 may end up using beacon पूर्णांकerval of zero in
	 * some हालs (at least क्रम mesh poपूर्णांक). Aव्योम getting पूर्णांकo an
	 * infinite loop by using a bit safer value instead. To be safe,
	 * करो sanity check on beacon पूर्णांकerval क्रम all operating modes.
	 */
	अगर (cur_conf->beacon_पूर्णांकerval == 0)
		cur_conf->beacon_पूर्णांकerval = 100;

	cur_conf->bmiss_समयout =
		ATH_DEFAULT_BMISS_LIMIT * cur_conf->beacon_पूर्णांकerval;

	/*
	 * We करोn't parse dtim period from mac80211 during the driver
	 * initialization as it अवरोधs association with hidden-ssid
	 * AP and it causes latency in roaming
	 */
	अगर (cur_conf->dtim_period == 0)
		cur_conf->dtim_period = 1;

	ath9k_set_tsfadjust(sc, cur_conf);
पूर्ण

व्योम ath9k_beacon_config(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *मुख्य_vअगर,
			 bool beacons)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_vअगर *avp;
	काष्ठा ath_chanctx *ctx;
	काष्ठा ath_beacon_config *cur_conf;
	अचिन्हित दीर्घ flags;
	bool enabled;
	bool skip_beacon = false;

	अगर (!beacons) अणु
		clear_bit(ATH_OP_BEACONS, &common->op_flags);
		ath9k_beacon_stop(sc);
		वापस;
	पूर्ण

	अगर (WARN_ON(!मुख्य_vअगर))
		वापस;

	avp = (व्योम *)मुख्य_vअगर->drv_priv;
	ctx = avp->chanctx;
	cur_conf = &ctx->beacon;
	enabled = cur_conf->enable_beacon;
	cur_conf->enable_beacon = beacons;

	अगर (sc->sc_ah->opmode == NL80211_IFTYPE_STATION) अणु
		ath9k_cache_beacon_config(sc, ctx, &मुख्य_vअगर->bss_conf);

		ath9k_set_beacon(sc);
		set_bit(ATH_OP_BEACONS, &common->op_flags);
		वापस;
	पूर्ण

	/* Update the beacon configuration. */
	ath9k_cache_beacon_config(sc, ctx, &मुख्य_vअगर->bss_conf);

	/*
	 * Configure the HW beacon रेजिस्टरs only when we have a valid
	 * beacon पूर्णांकerval.
	 */
	अगर (cur_conf->beacon_पूर्णांकerval) अणु
		/* Special हाल to sync the TSF when joining an existing IBSS.
		 * This is only करोne अगर no AP पूर्णांकerface is active.
		 * Note that mac80211 always resets the TSF when creating a new
		 * IBSS पूर्णांकerface.
		 */
		अगर (sc->sc_ah->opmode == NL80211_IFTYPE_ADHOC &&
		    !enabled && beacons && !मुख्य_vअगर->bss_conf.ibss_creator) अणु
			spin_lock_irqsave(&sc->sc_pm_lock, flags);
			sc->ps_flags |= PS_BEACON_SYNC | PS_WAIT_FOR_BEACON;
			spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
			skip_beacon = true;
		पूर्ण

		/*
		 * Do not set the ATH_OP_BEACONS flag क्रम IBSS joiner mode
		 * here, it is करोne in ath9k_beacon_config_adhoc().
		 */
		अगर (beacons && !skip_beacon) अणु
			set_bit(ATH_OP_BEACONS, &common->op_flags);
			ath9k_set_beacon(sc);
		पूर्ण अन्यथा अणु
			clear_bit(ATH_OP_BEACONS, &common->op_flags);
			ath9k_beacon_stop(sc);
		पूर्ण
	पूर्ण अन्यथा अणु
		clear_bit(ATH_OP_BEACONS, &common->op_flags);
		ath9k_beacon_stop(sc);
	पूर्ण
पूर्ण

व्योम ath9k_set_beacon(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_beacon_config *cur_conf = &sc->cur_chan->beacon;

	चयन (sc->sc_ah->opmode) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_MESH_POINT:
		ath9k_beacon_config_ap(sc, cur_conf);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ath9k_beacon_config_adhoc(sc, cur_conf);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		ath9k_beacon_config_sta(sc->sc_ah, cur_conf);
		अवरोध;
	शेष:
		ath_dbg(common, CONFIG, "Unsupported beaconing mode\n");
		वापस;
	पूर्ण
पूर्ण
