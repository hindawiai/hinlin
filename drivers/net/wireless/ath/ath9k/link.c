<शैली गुरु>
/*
 * Copyright (c) 2012 Qualcomm Atheros, Inc.
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

#समावेश "ath9k.h"

/*
 * TX polling - checks अगर the TX engine is stuck somewhere
 * and issues a chip reset अगर so.
 */
अटल bool ath_tx_complete_check(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_txq *txq;
	पूर्णांक i;

	अगर (sc->tx99_state)
		वापस true;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		txq = sc->tx.txq_map[i];

		ath_txq_lock(sc, txq);
		अगर (txq->axq_depth) अणु
			अगर (txq->axq_tx_inprogress) अणु
				ath_txq_unlock(sc, txq);
				जाओ reset;
			पूर्ण

			txq->axq_tx_inprogress = true;
		पूर्ण
		ath_txq_unlock(sc, txq);
	पूर्ण

	वापस true;

reset:
	ath_dbg(ath9k_hw_common(sc->sc_ah), RESET,
		"tx hung, resetting the chip\n");
	ath9k_queue_reset(sc, RESET_TYPE_TX_HANG);
	वापस false;

पूर्ण

व्योम ath_hw_check_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath_softc *sc = container_of(work, काष्ठा ath_softc,
					    hw_check_work.work);

	अगर (!ath_hw_check(sc) ||
	    !ath_tx_complete_check(sc))
		वापस;

	ieee80211_queue_delayed_work(sc->hw, &sc->hw_check_work,
				     msecs_to_jअगरfies(ATH_HW_CHECK_POLL_INT));
पूर्ण

/*
 * Checks अगर the BB/MAC is hung.
 */
bool ath_hw_check(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	क्रमागत ath_reset_type type;
	bool is_alive;

	ath9k_ps_wakeup(sc);

	is_alive = ath9k_hw_check_alive(sc->sc_ah);

	अगर (!is_alive) अणु
		ath_dbg(common, RESET,
			"HW hang detected, schedule chip reset\n");
		type = RESET_TYPE_MAC_HANG;
		ath9k_queue_reset(sc, type);
	पूर्ण

	ath9k_ps_restore(sc);

	वापस is_alive;
पूर्ण

/*
 * PLL-WAR क्रम AR9485/AR9340
 */
अटल bool ath_hw_pll_rx_hang_check(काष्ठा ath_softc *sc, u32 pll_sqsum)
अणु
	अटल पूर्णांक count;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	अगर (pll_sqsum >= 0x40000) अणु
		count++;
		अगर (count == 3) अणु
			ath_dbg(common, RESET, "PLL WAR, resetting the chip\n");
			ath9k_queue_reset(sc, RESET_TYPE_PLL_HANG);
			count = 0;
			वापस true;
		पूर्ण
	पूर्ण अन्यथा अणु
		count = 0;
	पूर्ण

	वापस false;
पूर्ण

व्योम ath_hw_pll_work(काष्ठा work_काष्ठा *work)
अणु
	u32 pll_sqsum;
	काष्ठा ath_softc *sc = container_of(work, काष्ठा ath_softc,
					    hw_pll_work.work);
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	/*
	 * ensure that the PLL WAR is executed only
	 * after the STA is associated (or) अगर the
	 * beaconing had started in पूर्णांकerfaces that
	 * uses beacons.
	 */
	अगर (!test_bit(ATH_OP_BEACONS, &common->op_flags))
		वापस;

	अगर (sc->tx99_state)
		वापस;

	ath9k_ps_wakeup(sc);
	pll_sqsum = ar9003_get_pll_sqsum_dvc(sc->sc_ah);
	ath9k_ps_restore(sc);
	अगर (ath_hw_pll_rx_hang_check(sc, pll_sqsum))
		वापस;

	ieee80211_queue_delayed_work(sc->hw, &sc->hw_pll_work,
				     msecs_to_jअगरfies(ATH_PLL_WORK_INTERVAL));
पूर्ण

/*
 * PA Pre-distortion.
 */
अटल व्योम ath_paprd_activate(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	पूर्णांक chain;

	अगर (!caldata || !test_bit(PAPRD_DONE, &caldata->cal_flags)) अणु
		ath_dbg(common, CALIBRATE, "Failed to activate PAPRD\n");
		वापस;
	पूर्ण

	ar9003_paprd_enable(ah, false);
	क्रम (chain = 0; chain < AR9300_MAX_CHAINS; chain++) अणु
		अगर (!(ah->txchainmask & BIT(chain)))
			जारी;

		ar9003_paprd_populate_single_table(ah, caldata, chain);
	पूर्ण

	ath_dbg(common, CALIBRATE, "Activating PAPRD\n");
	ar9003_paprd_enable(ah, true);
पूर्ण

अटल bool ath_paprd_send_frame(काष्ठा ath_softc *sc, काष्ठा sk_buff *skb, पूर्णांक chain)
अणु
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ieee80211_tx_info *tx_info = IEEE80211_SKB_CB(skb);
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_tx_control txctl;
	अचिन्हित दीर्घ समय_left;

	स_रखो(&txctl, 0, माप(txctl));
	txctl.txq = sc->tx.txq_map[IEEE80211_AC_BE];

	स_रखो(tx_info, 0, माप(*tx_info));
	tx_info->band = sc->cur_chandef.chan->band;
	tx_info->flags |= IEEE80211_TX_CTL_NO_ACK;
	tx_info->control.rates[0].idx = 0;
	tx_info->control.rates[0].count = 1;
	tx_info->control.rates[0].flags = IEEE80211_TX_RC_MCS;
	tx_info->control.rates[1].idx = -1;

	init_completion(&sc->paprd_complete);
	txctl.paprd = BIT(chain);

	अगर (ath_tx_start(hw, skb, &txctl) != 0) अणु
		ath_dbg(common, CALIBRATE, "PAPRD TX failed\n");
		dev_kमुक्त_skb_any(skb);
		वापस false;
	पूर्ण

	समय_left = रुको_क्रम_completion_समयout(&sc->paprd_complete,
			msecs_to_jअगरfies(ATH_PAPRD_TIMEOUT));

	अगर (!समय_left)
		ath_dbg(common, CALIBRATE,
			"Timeout waiting for paprd training on TX chain %d\n",
			chain);

	वापस !!समय_left;
पूर्ण

व्योम ath_paprd_calibrate(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath_softc *sc = container_of(work, काष्ठा ath_softc, paprd_work);
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ieee80211_hdr *hdr;
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा ath9k_hw_cal_data *caldata = ah->caldata;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक ftype;
	पूर्णांक chain_ok = 0;
	पूर्णांक chain;
	पूर्णांक len = 1800;
	पूर्णांक ret;

	अगर (!caldata ||
	    !test_bit(PAPRD_PACKET_SENT, &caldata->cal_flags) ||
	    test_bit(PAPRD_DONE, &caldata->cal_flags)) अणु
		ath_dbg(common, CALIBRATE, "Skipping PAPRD calibration\n");
		वापस;
	पूर्ण

	ath9k_ps_wakeup(sc);

	अगर (ar9003_paprd_init_table(ah) < 0)
		जाओ fail_paprd;

	skb = alloc_skb(len, GFP_KERNEL);
	अगर (!skb)
		जाओ fail_paprd;

	skb_put(skb, len);
	स_रखो(skb->data, 0, len);
	hdr = (काष्ठा ieee80211_hdr *)skb->data;
	ftype = IEEE80211_FTYPE_DATA | IEEE80211_STYPE_शून्यFUNC;
	hdr->frame_control = cpu_to_le16(ftype);
	hdr->duration_id = cpu_to_le16(10);
	स_नकल(hdr->addr1, hw->wiphy->perm_addr, ETH_ALEN);
	स_नकल(hdr->addr2, hw->wiphy->perm_addr, ETH_ALEN);
	स_नकल(hdr->addr3, hw->wiphy->perm_addr, ETH_ALEN);

	क्रम (chain = 0; chain < AR9300_MAX_CHAINS; chain++) अणु
		अगर (!(ah->txchainmask & BIT(chain)))
			जारी;

		chain_ok = 0;
		ar9003_paprd_setup_gain_table(ah, chain);

		ath_dbg(common, CALIBRATE,
			"Sending PAPRD training frame on chain %d\n", chain);
		अगर (!ath_paprd_send_frame(sc, skb, chain))
			जाओ fail_paprd;

		अगर (!ar9003_paprd_is_करोne(ah)) अणु
			ath_dbg(common, CALIBRATE,
				"PAPRD not yet done on chain %d\n", chain);
			अवरोध;
		पूर्ण

		ret = ar9003_paprd_create_curve(ah, caldata, chain);
		अगर (ret == -EINPROGRESS) अणु
			ath_dbg(common, CALIBRATE,
				"PAPRD curve on chain %d needs to be re-trained\n",
				chain);
			अवरोध;
		पूर्ण अन्यथा अगर (ret) अणु
			ath_dbg(common, CALIBRATE,
				"PAPRD create curve failed on chain %d\n",
				chain);
			अवरोध;
		पूर्ण

		chain_ok = 1;
	पूर्ण
	kमुक्त_skb(skb);

	अगर (chain_ok) अणु
		set_bit(PAPRD_DONE, &caldata->cal_flags);
		ath_paprd_activate(sc);
	पूर्ण

fail_paprd:
	ath9k_ps_restore(sc);
पूर्ण

/*
 *  ANI perक्रमms periodic noise न्यूनमान calibration
 *  that is used to adjust and optimize the chip perक्रमmance.  This
 *  takes environmental changes (location, temperature) पूर्णांकo account.
 *  When the task is complete, it reschedules itself depending on the
 *  appropriate पूर्णांकerval that was calculated.
 */
व्योम ath_ani_calibrate(काष्ठा समयr_list *t)
अणु
	काष्ठा ath_common *common = from_समयr(common, t, ani.समयr);
	काष्ठा ath_softc *sc = (काष्ठा ath_softc *)common->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	bool दीर्घcal = false;
	bool लघुcal = false;
	bool anअगरlag = false;
	अचिन्हित पूर्णांक बारtamp = jअगरfies_to_msecs(jअगरfies);
	u32 cal_पूर्णांकerval, लघु_cal_पूर्णांकerval, दीर्घ_cal_पूर्णांकerval;
	अचिन्हित दीर्घ flags;

	अगर (ah->caldata && test_bit(NFCAL_INTF, &ah->caldata->cal_flags))
		दीर्घ_cal_पूर्णांकerval = ATH_LONG_CALINTERVAL_INT;
	अन्यथा
		दीर्घ_cal_पूर्णांकerval = ATH_LONG_CALINTERVAL;

	लघु_cal_पूर्णांकerval = (ah->opmode == NL80211_IFTYPE_AP) ?
		ATH_AP_SHORT_CALINTERVAL : ATH_STA_SHORT_CALINTERVAL;

	/* Only calibrate अगर awake */
	अगर (sc->sc_ah->घातer_mode != ATH9K_PM_AWAKE) अणु
		अगर (++ah->ani_skip_count >= ATH_ANI_MAX_SKIP_COUNT) अणु
			spin_lock_irqsave(&sc->sc_pm_lock, flags);
			sc->ps_flags |= PS_WAIT_FOR_ANI;
			spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
		पूर्ण
		जाओ set_समयr;
	पूर्ण
	ah->ani_skip_count = 0;
	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	sc->ps_flags &= ~PS_WAIT_FOR_ANI;
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

	ath9k_ps_wakeup(sc);

	/* Long calibration runs independently of लघु calibration. */
	अगर ((बारtamp - common->ani.दीर्घcal_समयr) >= दीर्घ_cal_पूर्णांकerval) अणु
		दीर्घcal = true;
		common->ani.दीर्घcal_समयr = बारtamp;
	पूर्ण

	/* Short calibration applies only जबतक calकरोne is false */
	अगर (!common->ani.calकरोne) अणु
		अगर ((बारtamp - common->ani.लघुcal_समयr) >= लघु_cal_पूर्णांकerval) अणु
			लघुcal = true;
			common->ani.लघुcal_समयr = बारtamp;
			common->ani.resetcal_समयr = बारtamp;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर ((बारtamp - common->ani.resetcal_समयr) >=
		    ATH_RESTART_CALINTERVAL) अणु
			common->ani.calकरोne = ath9k_hw_reset_calvalid(ah);
			अगर (common->ani.calकरोne)
				common->ani.resetcal_समयr = बारtamp;
		पूर्ण
	पूर्ण

	/* Verअगरy whether we must check ANI */
	अगर ((बारtamp - common->ani.checkani_समयr) >= ah->config.ani_poll_पूर्णांकerval) अणु
		anअगरlag = true;
		common->ani.checkani_समयr = बारtamp;
	पूर्ण

	/* Call ANI routine अगर necessary */
	अगर (anअगरlag) अणु
		spin_lock_irqsave(&common->cc_lock, flags);
		ath9k_hw_ani_monitor(ah, ah->curchan);
		ath_update_survey_stats(sc);
		spin_unlock_irqrestore(&common->cc_lock, flags);
	पूर्ण

	/* Perक्रमm calibration अगर necessary */
	अगर (दीर्घcal || लघुcal) अणु
		पूर्णांक ret = ath9k_hw_calibrate(ah, ah->curchan, ah->rxchainmask,
					     दीर्घcal);
		अगर (ret < 0) अणु
			common->ani.calकरोne = 0;
			ath9k_queue_reset(sc, RESET_TYPE_CALIBRATION);
			वापस;
		पूर्ण

		common->ani.calकरोne = ret;
	पूर्ण

	ath_dbg(common, ANI,
		"Calibration @%lu finished: %s %s %s, caldone: %s\n",
		jअगरfies,
		दीर्घcal ? "long" : "", लघुcal ? "short" : "",
		anअगरlag ? "ani" : "", common->ani.calकरोne ? "true" : "false");

	ath9k_ps_restore(sc);

set_समयr:
	/*
	* Set समयr पूर्णांकerval based on previous results.
	* The पूर्णांकerval must be the लघुest necessary to satisfy ANI,
	* लघु calibration and दीर्घ calibration.
	*/
	cal_पूर्णांकerval = ATH_LONG_CALINTERVAL;
	cal_पूर्णांकerval = min(cal_पूर्णांकerval, (u32)ah->config.ani_poll_पूर्णांकerval);
	अगर (!common->ani.calकरोne)
		cal_पूर्णांकerval = min(cal_पूर्णांकerval, (u32)लघु_cal_पूर्णांकerval);

	mod_समयr(&common->ani.समयr, jअगरfies + msecs_to_jअगरfies(cal_पूर्णांकerval));

	अगर (ar9003_is_paprd_enabled(ah) && ah->caldata) अणु
		अगर (!test_bit(PAPRD_DONE, &ah->caldata->cal_flags)) अणु
			ieee80211_queue_work(sc->hw, &sc->paprd_work);
		पूर्ण अन्यथा अगर (!ah->paprd_table_ग_लिखो_करोne) अणु
			ath9k_ps_wakeup(sc);
			ath_paprd_activate(sc);
			ath9k_ps_restore(sc);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ath_start_ani(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	अचिन्हित दीर्घ बारtamp = jअगरfies_to_msecs(jअगरfies);

	अगर (common->disable_ani ||
	    !test_bit(ATH_OP_ANI_RUN, &common->op_flags) ||
	    sc->cur_chan->offchannel)
		वापस;

	common->ani.दीर्घcal_समयr = बारtamp;
	common->ani.लघुcal_समयr = बारtamp;
	common->ani.checkani_समयr = बारtamp;

	ath_dbg(common, ANI, "Starting ANI\n");
	mod_समयr(&common->ani.समयr,
		  jअगरfies + msecs_to_jअगरfies((u32)ah->config.ani_poll_पूर्णांकerval));
पूर्ण

व्योम ath_stop_ani(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, ANI, "Stopping ANI\n");
	del_समयr_sync(&common->ani.समयr);
पूर्ण

व्योम ath_check_ani(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_beacon_config *cur_conf = &sc->cur_chan->beacon;

	/*
	 * Check क्रम the various conditions in which ANI has to
	 * be stopped.
	 */
	अगर (ah->opmode == NL80211_IFTYPE_ADHOC) अणु
		अगर (!cur_conf->enable_beacon)
			जाओ stop_ani;
	पूर्ण अन्यथा अगर (ah->opmode == NL80211_IFTYPE_AP) अणु
		अगर (!cur_conf->enable_beacon) अणु
			/*
			 * Disable ANI only when there are no
			 * associated stations.
			 */
			अगर (!test_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags))
				जाओ stop_ani;
		पूर्ण
	पूर्ण अन्यथा अगर (ah->opmode == NL80211_IFTYPE_STATION) अणु
		अगर (!test_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags))
			जाओ stop_ani;
	पूर्ण

	अगर (!test_bit(ATH_OP_ANI_RUN, &common->op_flags)) अणु
		set_bit(ATH_OP_ANI_RUN, &common->op_flags);
		ath_start_ani(sc);
	पूर्ण

	वापस;

stop_ani:
	clear_bit(ATH_OP_ANI_RUN, &common->op_flags);
	ath_stop_ani(sc);
पूर्ण

व्योम ath_update_survey_nf(काष्ठा ath_softc *sc, पूर्णांक channel)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_channel *chan = &ah->channels[channel];
	काष्ठा survey_info *survey = &sc->survey[channel];

	अगर (chan->noiseन्यूनमान) अणु
		survey->filled |= SURVEY_INFO_NOISE_DBM;
		survey->noise = ath9k_hw_अ_लोhan_noise(ah, chan,
						       chan->noiseन्यूनमान);
	पूर्ण
पूर्ण

/*
 * Updates the survey statistics and वापसs the busy समय since last
 * update in %, अगर the measurement duration was दीर्घ enough क्रम the
 * result to be useful, -1 otherwise.
 */
पूर्णांक ath_update_survey_stats(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक pos = ah->curchan - &ah->channels[0];
	काष्ठा survey_info *survey = &sc->survey[pos];
	काष्ठा ath_cycle_counters *cc = &common->cc_survey;
	अचिन्हित पूर्णांक भाग = common->घड़ीrate * 1000;
	पूर्णांक ret = 0;

	अगर (!ah->curchan)
		वापस -1;

	अगर (ah->घातer_mode == ATH9K_PM_AWAKE)
		ath_hw_cycle_counters_update(common);

	अगर (cc->cycles > 0) अणु
		survey->filled |= SURVEY_INFO_TIME |
			SURVEY_INFO_TIME_BUSY |
			SURVEY_INFO_TIME_RX |
			SURVEY_INFO_TIME_TX;
		survey->समय += cc->cycles / भाग;
		survey->समय_busy += cc->rx_busy / भाग;
		survey->समय_rx += cc->rx_frame / भाग;
		survey->समय_प्रकारx += cc->tx_frame / भाग;
	पूर्ण

	अगर (cc->cycles < भाग)
		वापस -1;

	अगर (cc->cycles > 0)
		ret = cc->rx_busy * 100 / cc->cycles;

	स_रखो(cc, 0, माप(*cc));

	ath_update_survey_nf(sc, pos);

	वापस ret;
पूर्ण
