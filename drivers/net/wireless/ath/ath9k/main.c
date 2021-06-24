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

#समावेश <linux/nl80211.h>
#समावेश <linux/delay.h>
#समावेश "ath9k.h"
#समावेश "btcoex.h"

अटल व्योम ath9k_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			u32 queues, bool drop);

u8 ath9k_parse_mpdudensity(u8 mpdudensity)
अणु
	/*
	 * 802.11n D2.0 defined values क्रम "Minimum MPDU Start Spacing":
	 *   0 क्रम no restriction
	 *   1 क्रम 1/4 us
	 *   2 क्रम 1/2 us
	 *   3 क्रम 1 us
	 *   4 क्रम 2 us
	 *   5 क्रम 4 us
	 *   6 क्रम 8 us
	 *   7 क्रम 16 us
	 */
	चयन (mpdudensity) अणु
	हाल 0:
		वापस 0;
	हाल 1:
	हाल 2:
	हाल 3:
		/* Our lower layer calculations limit our precision to
		   1 microsecond */
		वापस 1;
	हाल 4:
		वापस 2;
	हाल 5:
		वापस 4;
	हाल 6:
		वापस 8;
	हाल 7:
		वापस 16;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

अटल bool ath9k_has_pending_frames(काष्ठा ath_softc *sc, काष्ठा ath_txq *txq,
				     bool sw_pending)
अणु
	bool pending = false;

	spin_lock_bh(&txq->axq_lock);

	अगर (txq->axq_depth) अणु
		pending = true;
		जाओ out;
	पूर्ण

	अगर (!sw_pending)
		जाओ out;

	अगर (txq->mac80211_qnum >= 0) अणु
		काष्ठा ath_acq *acq;

		acq = &sc->cur_chan->acq[txq->mac80211_qnum];
		अगर (!list_empty(&acq->acq_new) || !list_empty(&acq->acq_old))
			pending = true;
	पूर्ण
out:
	spin_unlock_bh(&txq->axq_lock);
	वापस pending;
पूर्ण

अटल bool ath9k_setघातer(काष्ठा ath_softc *sc, क्रमागत ath9k_घातer_mode mode)
अणु
	अचिन्हित दीर्घ flags;
	bool ret;

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	ret = ath9k_hw_setघातer(sc->sc_ah, mode);
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

	वापस ret;
पूर्ण

व्योम ath_ps_full_sleep(काष्ठा समयr_list *t)
अणु
	काष्ठा ath_softc *sc = from_समयr(sc, t, sleep_समयr);
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	अचिन्हित दीर्घ flags;
	bool reset;

	spin_lock_irqsave(&common->cc_lock, flags);
	ath_hw_cycle_counters_update(common);
	spin_unlock_irqrestore(&common->cc_lock, flags);

	ath9k_hw_setrxपात(sc->sc_ah, 1);
	ath9k_hw_stopdmarecv(sc->sc_ah, &reset);

	ath9k_hw_setघातer(sc->sc_ah, ATH9K_PM_FULL_SLEEP);
पूर्ण

व्योम ath9k_ps_wakeup(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	अचिन्हित दीर्घ flags;
	क्रमागत ath9k_घातer_mode घातer_mode;

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	अगर (++sc->ps_usecount != 1)
		जाओ unlock;

	del_समयr_sync(&sc->sleep_समयr);
	घातer_mode = sc->sc_ah->घातer_mode;
	ath9k_hw_setघातer(sc->sc_ah, ATH9K_PM_AWAKE);

	/*
	 * While the hardware is asleep, the cycle counters contain no
	 * useful data. Better clear them now so that they करोn't mess up
	 * survey data results.
	 */
	अगर (घातer_mode != ATH9K_PM_AWAKE) अणु
		spin_lock(&common->cc_lock);
		ath_hw_cycle_counters_update(common);
		स_रखो(&common->cc_survey, 0, माप(common->cc_survey));
		स_रखो(&common->cc_ani, 0, माप(common->cc_ani));
		spin_unlock(&common->cc_lock);
	पूर्ण

 unlock:
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
पूर्ण

व्योम ath9k_ps_restore(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	क्रमागत ath9k_घातer_mode mode;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	अगर (--sc->ps_usecount != 0)
		जाओ unlock;

	अगर (sc->ps_idle) अणु
		mod_समयr(&sc->sleep_समयr, jअगरfies + HZ / 10);
		जाओ unlock;
	पूर्ण

	अगर (sc->ps_enabled &&
		   !(sc->ps_flags & (PS_WAIT_FOR_BEACON |
				     PS_WAIT_FOR_CAB |
				     PS_WAIT_FOR_PSPOLL_DATA |
				     PS_WAIT_FOR_TX_ACK |
				     PS_WAIT_FOR_ANI))) अणु
		mode = ATH9K_PM_NETWORK_SLEEP;
		अगर (ath9k_hw_btcoex_is_enabled(sc->sc_ah))
			ath9k_btcoex_stop_gen_समयr(sc);
	पूर्ण अन्यथा अणु
		जाओ unlock;
	पूर्ण

	spin_lock(&common->cc_lock);
	ath_hw_cycle_counters_update(common);
	spin_unlock(&common->cc_lock);

	ath9k_hw_setघातer(sc->sc_ah, mode);

 unlock:
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
पूर्ण

अटल व्योम __ath_cancel_work(काष्ठा ath_softc *sc)
अणु
	cancel_work_sync(&sc->paprd_work);
	cancel_delayed_work_sync(&sc->hw_check_work);
	cancel_delayed_work_sync(&sc->hw_pll_work);

#अगर_घोषित CONFIG_ATH9K_BTCOEX_SUPPORT
	अगर (ath9k_hw_mci_is_enabled(sc->sc_ah))
		cancel_work_sync(&sc->mci_work);
#पूर्ण_अगर
पूर्ण

व्योम ath_cancel_work(काष्ठा ath_softc *sc)
अणु
	__ath_cancel_work(sc);
	cancel_work_sync(&sc->hw_reset_work);
पूर्ण

व्योम ath_restart_work(काष्ठा ath_softc *sc)
अणु
	ieee80211_queue_delayed_work(sc->hw, &sc->hw_check_work,
				     ATH_HW_CHECK_POLL_INT);

	अगर (AR_SREV_9340(sc->sc_ah) || AR_SREV_9330(sc->sc_ah))
		ieee80211_queue_delayed_work(sc->hw, &sc->hw_pll_work,
				     msecs_to_jअगरfies(ATH_PLL_WORK_INTERVAL));

	ath_start_ani(sc);
पूर्ण

अटल bool ath_prepare_reset(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	bool ret = true;

	ieee80211_stop_queues(sc->hw);
	ath_stop_ani(sc);
	ath9k_hw_disable_पूर्णांकerrupts(ah);

	अगर (AR_SREV_9300_20_OR_LATER(ah)) अणु
		ret &= ath_stoprecv(sc);
		ret &= ath_drain_all_txq(sc);
	पूर्ण अन्यथा अणु
		ret &= ath_drain_all_txq(sc);
		ret &= ath_stoprecv(sc);
	पूर्ण

	वापस ret;
पूर्ण

अटल bool ath_complete_reset(काष्ठा ath_softc *sc, bool start)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	अचिन्हित दीर्घ flags;

	ath9k_calculate_summary_state(sc, sc->cur_chan);
	ath_startrecv(sc);
	ath9k_cmn_update_txघात(ah, sc->cur_chan->cur_txघातer,
			       sc->cur_chan->txघातer,
			       &sc->cur_chan->cur_txघातer);
	clear_bit(ATH_OP_HW_RESET, &common->op_flags);

	अगर (!sc->cur_chan->offchannel && start) अणु
		/* restore per chanctx TSF समयr */
		अगर (sc->cur_chan->tsf_val) अणु
			u32 offset;

			offset = ath9k_hw_get_tsf_offset(&sc->cur_chan->tsf_ts,
							 शून्य);
			ath9k_hw_settsf64(ah, sc->cur_chan->tsf_val + offset);
		पूर्ण


		अगर (!test_bit(ATH_OP_BEACONS, &common->op_flags))
			जाओ work;

		अगर (ah->opmode == NL80211_IFTYPE_STATION &&
		    test_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags)) अणु
			spin_lock_irqsave(&sc->sc_pm_lock, flags);
			sc->ps_flags |= PS_BEACON_SYNC | PS_WAIT_FOR_BEACON;
			spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
		पूर्ण अन्यथा अणु
			ath9k_set_beacon(sc);
		पूर्ण
	work:
		ath_restart_work(sc);
		ath_txq_schedule_all(sc);
	पूर्ण

	sc->gtt_cnt = 0;

	ath9k_hw_set_पूर्णांकerrupts(ah);
	ath9k_hw_enable_पूर्णांकerrupts(ah);
	ieee80211_wake_queues(sc->hw);
	ath9k_p2p_ps_समयr(sc);

	वापस true;
पूर्ण

अटल पूर्णांक ath_reset_पूर्णांकernal(काष्ठा ath_softc *sc, काष्ठा ath9k_channel *hchan)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_hw_cal_data *caldata = शून्य;
	bool fastcc = true;
	पूर्णांक r;

	__ath_cancel_work(sc);

	disable_irq(sc->irq);
	tasklet_disable(&sc->पूर्णांकr_tq);
	tasklet_disable(&sc->bcon_tasklet);
	spin_lock_bh(&sc->sc_pcu_lock);

	अगर (!sc->cur_chan->offchannel) अणु
		fastcc = false;
		caldata = &sc->cur_chan->caldata;
	पूर्ण

	अगर (!hchan) अणु
		fastcc = false;
		hchan = ah->curchan;
	पूर्ण

	अगर (!ath_prepare_reset(sc))
		fastcc = false;

	अगर (ath9k_is_chanctx_enabled())
		fastcc = false;

	spin_lock_bh(&sc->chan_lock);
	sc->cur_chandef = sc->cur_chan->chandef;
	spin_unlock_bh(&sc->chan_lock);

	ath_dbg(common, CONFIG, "Reset to %u MHz, HT40: %d fastcc: %d\n",
		hchan->channel, IS_CHAN_HT40(hchan), fastcc);

	r = ath9k_hw_reset(ah, hchan, caldata, fastcc);
	अगर (r) अणु
		ath_err(common,
			"Unable to reset channel, reset status %d\n", r);

		ath9k_hw_enable_पूर्णांकerrupts(ah);
		ath9k_queue_reset(sc, RESET_TYPE_BB_HANG);

		जाओ out;
	पूर्ण

	अगर (ath9k_hw_mci_is_enabled(sc->sc_ah) &&
	    sc->cur_chan->offchannel)
		ath9k_mci_set_txघातer(sc, true, false);

	अगर (!ath_complete_reset(sc, true))
		r = -EIO;

out:
	enable_irq(sc->irq);
	spin_unlock_bh(&sc->sc_pcu_lock);
	tasklet_enable(&sc->bcon_tasklet);
	tasklet_enable(&sc->पूर्णांकr_tq);

	वापस r;
पूर्ण

अटल व्योम ath_node_attach(काष्ठा ath_softc *sc, काष्ठा ieee80211_sta *sta,
			    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_node *an;
	an = (काष्ठा ath_node *)sta->drv_priv;

	an->sc = sc;
	an->sta = sta;
	an->vअगर = vअगर;
	स_रखो(&an->key_idx, 0, माप(an->key_idx));

	ath_tx_node_init(sc, an);

	ath_dynack_node_init(sc->sc_ah, an);
पूर्ण

अटल व्योम ath_node_detach(काष्ठा ath_softc *sc, काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath_node *an = (काष्ठा ath_node *)sta->drv_priv;
	ath_tx_node_cleanup(sc, an);

	ath_dynack_node_deinit(sc->sc_ah, an);
पूर्ण

व्योम ath9k_tasklet(काष्ठा tasklet_काष्ठा *t)
अणु
	काष्ठा ath_softc *sc = from_tasklet(sc, t, पूर्णांकr_tq);
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	क्रमागत ath_reset_type type;
	अचिन्हित दीर्घ flags;
	u32 status;
	u32 rxmask;

	spin_lock_irqsave(&sc->पूर्णांकr_lock, flags);
	status = sc->पूर्णांकrstatus;
	sc->पूर्णांकrstatus = 0;
	spin_unlock_irqrestore(&sc->पूर्णांकr_lock, flags);

	ath9k_ps_wakeup(sc);
	spin_lock(&sc->sc_pcu_lock);

	अगर (status & ATH9K_INT_FATAL) अणु
		type = RESET_TYPE_FATAL_INT;
		ath9k_queue_reset(sc, type);
		ath_dbg(common, RESET, "FATAL: Skipping interrupts\n");
		जाओ out;
	पूर्ण

	अगर ((ah->config.hw_hang_checks & HW_BB_WATCHDOG) &&
	    (status & ATH9K_INT_BB_WATCHDOG)) अणु
		spin_lock_irqsave(&common->cc_lock, flags);
		ath_hw_cycle_counters_update(common);
		ar9003_hw_bb_watchकरोg_dbg_info(ah);
		spin_unlock_irqrestore(&common->cc_lock, flags);

		अगर (ar9003_hw_bb_watchकरोg_check(ah)) अणु
			type = RESET_TYPE_BB_WATCHDOG;
			ath9k_queue_reset(sc, type);

			ath_dbg(common, RESET,
				"BB_WATCHDOG: Skipping interrupts\n");
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (status & ATH9K_INT_GTT) अणु
		sc->gtt_cnt++;

		अगर ((sc->gtt_cnt >= MAX_GTT_CNT) && !ath9k_hw_check_alive(ah)) अणु
			type = RESET_TYPE_TX_GTT;
			ath9k_queue_reset(sc, type);
			ath_dbg(common, RESET,
				"GTT: Skipping interrupts\n");
			जाओ out;
		पूर्ण
	पूर्ण

	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	अगर ((status & ATH9K_INT_TSFOOR) && sc->ps_enabled) अणु
		/*
		 * TSF sync करोes not look correct; reमुख्य awake to sync with
		 * the next Beacon.
		 */
		ath_dbg(common, PS, "TSFOOR - Sync with next Beacon\n");
		sc->ps_flags |= PS_WAIT_FOR_BEACON | PS_BEACON_SYNC;
	पूर्ण
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		rxmask = (ATH9K_INT_RXHP | ATH9K_INT_RXLP | ATH9K_INT_RXEOL |
			  ATH9K_INT_RXORN);
	अन्यथा
		rxmask = (ATH9K_INT_RX | ATH9K_INT_RXEOL | ATH9K_INT_RXORN);

	अगर (status & rxmask) अणु
		/* Check क्रम high priority Rx first */
		अगर ((ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) &&
		    (status & ATH9K_INT_RXHP))
			ath_rx_tasklet(sc, 0, true);

		ath_rx_tasklet(sc, 0, false);
	पूर्ण

	अगर (status & ATH9K_INT_TX) अणु
		अगर (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) अणु
			/*
			 * For EDMA chips, TX completion is enabled क्रम the
			 * beacon queue, so अगर a beacon has been transmitted
			 * successfully after a GTT पूर्णांकerrupt, the GTT counter
			 * माला_लो reset to zero here.
			 */
			sc->gtt_cnt = 0;

			ath_tx_edma_tasklet(sc);
		पूर्ण अन्यथा अणु
			ath_tx_tasklet(sc);
		पूर्ण

		wake_up(&sc->tx_रुको);
	पूर्ण

	अगर (status & ATH9K_INT_GENTIMER)
		ath_gen_समयr_isr(sc->sc_ah);

	ath9k_btcoex_handle_पूर्णांकerrupt(sc, status);

	/* re-enable hardware पूर्णांकerrupt */
	ath9k_hw_resume_पूर्णांकerrupts(ah);
out:
	spin_unlock(&sc->sc_pcu_lock);
	ath9k_ps_restore(sc);
पूर्ण

irqवापस_t ath_isr(पूर्णांक irq, व्योम *dev)
अणु
#घोषणा SCHED_INTR (				\
		ATH9K_INT_FATAL |		\
		ATH9K_INT_BB_WATCHDOG |		\
		ATH9K_INT_RXORN |		\
		ATH9K_INT_RXEOL |		\
		ATH9K_INT_RX |			\
		ATH9K_INT_RXLP |		\
		ATH9K_INT_RXHP |		\
		ATH9K_INT_TX |			\
		ATH9K_INT_BMISS |		\
		ATH9K_INT_CST |			\
		ATH9K_INT_GTT |			\
		ATH9K_INT_TSFOOR |		\
		ATH9K_INT_GENTIMER |		\
		ATH9K_INT_MCI)

	काष्ठा ath_softc *sc = dev;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	क्रमागत ath9k_पूर्णांक status;
	u32 sync_cause = 0;
	bool sched = false;

	/*
	 * The hardware is not पढ़ोy/present, करोn't
	 * touch anything. Note this can happen early
	 * on अगर the IRQ is shared.
	 */
	अगर (!ah || test_bit(ATH_OP_INVALID, &common->op_flags))
		वापस IRQ_NONE;

	/* shared irq, not क्रम us */
	अगर (!ath9k_hw_पूर्णांकrpend(ah))
		वापस IRQ_NONE;

	/*
	 * Figure out the reason(s) क्रम the पूर्णांकerrupt.  Note
	 * that the hal वापसs a pseuकरो-ISR that may include
	 * bits we haven't explicitly enabled so we mask the
	 * value to insure we only process bits we requested.
	 */
	ath9k_hw_getisr(ah, &status, &sync_cause); /* NB: clears ISR too */
	ath9k_debug_sync_cause(sc, sync_cause);
	status &= ah->imask;	/* discard unasked-क्रम bits */

	अगर (test_bit(ATH_OP_HW_RESET, &common->op_flags))
		वापस IRQ_HANDLED;

	/*
	 * If there are no status bits set, then this पूर्णांकerrupt was not
	 * क्रम me (should have been caught above).
	 */
	अगर (!status)
		वापस IRQ_NONE;

	/* Cache the status */
	spin_lock(&sc->पूर्णांकr_lock);
	sc->पूर्णांकrstatus |= status;
	spin_unlock(&sc->पूर्णांकr_lock);

	अगर (status & SCHED_INTR)
		sched = true;

	/*
	 * If a FATAL पूर्णांकerrupt is received, we have to reset the chip
	 * immediately.
	 */
	अगर (status & ATH9K_INT_FATAL)
		जाओ chip_reset;

	अगर ((ah->config.hw_hang_checks & HW_BB_WATCHDOG) &&
	    (status & ATH9K_INT_BB_WATCHDOG))
		जाओ chip_reset;

	अगर (status & ATH9K_INT_SWBA)
		tasklet_schedule(&sc->bcon_tasklet);

	अगर (status & ATH9K_INT_TXURN)
		ath9k_hw_updatetxtriglevel(ah, true);

	अगर (status & ATH9K_INT_RXEOL) अणु
		ah->imask &= ~(ATH9K_INT_RXEOL | ATH9K_INT_RXORN);
		ath9k_hw_set_पूर्णांकerrupts(ah);
	पूर्ण

	अगर (!(ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSLEEP))
		अगर (status & ATH9K_INT_TIM_TIMER) अणु
			अगर (ATH_DBG_WARN_ON_ONCE(sc->ps_idle))
				जाओ chip_reset;
			/* Clear RxAbort bit so that we can
			 * receive frames */
			ath9k_setघातer(sc, ATH9K_PM_AWAKE);
			spin_lock(&sc->sc_pm_lock);
			ath9k_hw_setrxपात(sc->sc_ah, 0);
			sc->ps_flags |= PS_WAIT_FOR_BEACON;
			spin_unlock(&sc->sc_pm_lock);
		पूर्ण

chip_reset:

	ath_debug_stat_पूर्णांकerrupt(sc, status);

	अगर (sched) अणु
		/* turn off every पूर्णांकerrupt */
		ath9k_hw_समाप्त_पूर्णांकerrupts(ah);
		tasklet_schedule(&sc->पूर्णांकr_tq);
	पूर्ण

	वापस IRQ_HANDLED;

#अघोषित SCHED_INTR
पूर्ण

/*
 * This function is called when a HW reset cannot be deferred
 * and has to be immediate.
 */
पूर्णांक ath_reset(काष्ठा ath_softc *sc, काष्ठा ath9k_channel *hchan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	पूर्णांक r;

	ath9k_hw_समाप्त_पूर्णांकerrupts(sc->sc_ah);
	set_bit(ATH_OP_HW_RESET, &common->op_flags);

	ath9k_ps_wakeup(sc);
	r = ath_reset_पूर्णांकernal(sc, hchan);
	ath9k_ps_restore(sc);

	वापस r;
पूर्ण

/*
 * When a HW reset can be deferred, it is added to the
 * hw_reset_work workqueue, but we set ATH_OP_HW_RESET beक्रमe
 * queueing.
 */
व्योम ath9k_queue_reset(काष्ठा ath_softc *sc, क्रमागत ath_reset_type type)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
#अगर_घोषित CONFIG_ATH9K_DEBUGFS
	RESET_STAT_INC(sc, type);
#पूर्ण_अगर
	ath9k_hw_समाप्त_पूर्णांकerrupts(sc->sc_ah);
	set_bit(ATH_OP_HW_RESET, &common->op_flags);
	ieee80211_queue_work(sc->hw, &sc->hw_reset_work);
पूर्ण

व्योम ath_reset_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath_softc *sc = container_of(work, काष्ठा ath_softc, hw_reset_work);

	ath9k_ps_wakeup(sc);
	ath_reset_पूर्णांकernal(sc, शून्य);
	ath9k_ps_restore(sc);
पूर्ण

/**********************/
/* mac80211 callbacks */
/**********************/

अटल पूर्णांक ath9k_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_channel *curchan = sc->cur_chan->chandef.chan;
	काष्ठा ath_chanctx *ctx = sc->cur_chan;
	काष्ठा ath9k_channel *init_channel;
	पूर्णांक r;

	ath_dbg(common, CONFIG,
		"Starting driver with initial channel: %d MHz\n",
		curchan->center_freq);

	ath9k_ps_wakeup(sc);
	mutex_lock(&sc->mutex);

	init_channel = ath9k_cmn_get_channel(hw, ah, &ctx->chandef);
	sc->cur_chandef = hw->conf.chandef;

	/* Reset SERDES रेजिस्टरs */
	ath9k_hw_configpciघातersave(ah, false);

	/*
	 * The basic पूर्णांकerface to setting the hardware in a good
	 * state is ``reset''.  On वापस the hardware is known to
	 * be घातered up and with पूर्णांकerrupts disabled.  This must
	 * be followed by initialization of the appropriate bits
	 * and then setup of the पूर्णांकerrupt mask.
	 */
	spin_lock_bh(&sc->sc_pcu_lock);

	atomic_set(&ah->पूर्णांकr_ref_cnt, -1);

	r = ath9k_hw_reset(ah, init_channel, ah->caldata, false);
	अगर (r) अणु
		ath_err(common,
			"Unable to reset hardware; reset status %d (freq %u MHz)\n",
			r, curchan->center_freq);
		ah->reset_घातer_on = false;
	पूर्ण

	/* Setup our पूर्णांकr mask. */
	ah->imask = ATH9K_INT_TX | ATH9K_INT_RXEOL |
		    ATH9K_INT_RXORN | ATH9K_INT_FATAL |
		    ATH9K_INT_GLOBAL;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_EDMA)
		ah->imask |= ATH9K_INT_RXHP |
			     ATH9K_INT_RXLP;
	अन्यथा
		ah->imask |= ATH9K_INT_RX;

	अगर (ah->config.hw_hang_checks & HW_BB_WATCHDOG)
		ah->imask |= ATH9K_INT_BB_WATCHDOG;

	/*
	 * Enable GTT पूर्णांकerrupts only क्रम AR9003/AR9004 chips
	 * क्रम now.
	 */
	अगर (AR_SREV_9300_20_OR_LATER(ah))
		ah->imask |= ATH9K_INT_GTT;

	अगर (ah->caps.hw_caps & ATH9K_HW_CAP_HT)
		ah->imask |= ATH9K_INT_CST;

	ath_mci_enable(sc);

	clear_bit(ATH_OP_INVALID, &common->op_flags);
	sc->sc_ah->is_monitoring = false;

	अगर (!ath_complete_reset(sc, false))
		ah->reset_घातer_on = false;

	अगर (ah->led_pin >= 0) अणु
		ath9k_hw_set_gpio(ah, ah->led_pin,
				  (ah->config.led_active_high) ? 1 : 0);
		ath9k_hw_gpio_request_out(ah, ah->led_pin, शून्य,
					  AR_GPIO_OUTPUT_MUX_AS_OUTPUT);
	पूर्ण

	/*
	 * Reset key cache to sane शेषs (all entries cleared) instead of
	 * semi-अक्रमom values after suspend/resume.
	 */
	ath9k_cmn_init_crypto(sc->sc_ah);

	ath9k_hw_reset_tsf(ah);

	spin_unlock_bh(&sc->sc_pcu_lock);

	ath9k_rng_start(sc);

	mutex_unlock(&sc->mutex);

	ath9k_ps_restore(sc);

	वापस 0;
पूर्ण

अटल व्योम ath9k_tx(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_tx_control *control,
		     काष्ठा sk_buff *skb)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_tx_control txctl;
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *) skb->data;
	अचिन्हित दीर्घ flags;

	अगर (sc->ps_enabled) अणु
		/*
		 * mac80211 करोes not set PM field क्रम normal data frames, so we
		 * need to update that based on the current PS mode.
		 */
		अगर (ieee80211_is_data(hdr->frame_control) &&
		    !ieee80211_is_nullfunc(hdr->frame_control) &&
		    !ieee80211_has_pm(hdr->frame_control)) अणु
			ath_dbg(common, PS,
				"Add PM=1 for a TX frame while in PS mode\n");
			hdr->frame_control |= cpu_to_le16(IEEE80211_FCTL_PM);
		पूर्ण
	पूर्ण

	अगर (unlikely(sc->sc_ah->घातer_mode == ATH9K_PM_NETWORK_SLEEP)) अणु
		/*
		 * We are using PS-Poll and mac80211 can request TX जबतक in
		 * घातer save mode. Need to wake up hardware क्रम the TX to be
		 * completed and अगर needed, also क्रम RX of buffered frames.
		 */
		ath9k_ps_wakeup(sc);
		spin_lock_irqsave(&sc->sc_pm_lock, flags);
		अगर (!(sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSLEEP))
			ath9k_hw_setrxपात(sc->sc_ah, 0);
		अगर (ieee80211_is_pspoll(hdr->frame_control)) अणु
			ath_dbg(common, PS,
				"Sending PS-Poll to pick a buffered frame\n");
			sc->ps_flags |= PS_WAIT_FOR_PSPOLL_DATA;
		पूर्ण अन्यथा अणु
			ath_dbg(common, PS, "Wake up to complete TX\n");
			sc->ps_flags |= PS_WAIT_FOR_TX_ACK;
		पूर्ण
		/*
		 * The actual restore operation will happen only after
		 * the ps_flags bit is cleared. We are just dropping
		 * the ps_usecount here.
		 */
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
		ath9k_ps_restore(sc);
	पूर्ण

	/*
	 * Cannot tx जबतक the hardware is in full sleep, it first needs a full
	 * chip reset to recover from that
	 */
	अगर (unlikely(sc->sc_ah->घातer_mode == ATH9K_PM_FULL_SLEEP)) अणु
		ath_err(common, "TX while HW is in FULL_SLEEP mode\n");
		जाओ निकास;
	पूर्ण

	स_रखो(&txctl, 0, माप(काष्ठा ath_tx_control));
	txctl.txq = sc->tx.txq_map[skb_get_queue_mapping(skb)];
	txctl.sta = control->sta;

	ath_dbg(common, XMIT, "transmitting packet, skb: %p\n", skb);

	अगर (ath_tx_start(hw, skb, &txctl) != 0) अणु
		ath_dbg(common, XMIT, "TX failed\n");
		TX_STAT_INC(sc, txctl.txq->axq_qnum, txfailed);
		जाओ निकास;
	पूर्ण

	वापस;
निकास:
	ieee80211_मुक्त_txskb(hw, skb);
पूर्ण

अटल bool ath9k_txq_list_has_key(काष्ठा list_head *txq_list, u32 keyix)
अणु
	काष्ठा ath_buf *bf;
	काष्ठा ieee80211_tx_info *txinfo;
	काष्ठा ath_frame_info *fi;

	list_क्रम_each_entry(bf, txq_list, list) अणु
		अगर (bf->bf_state.stale || !bf->bf_mpdu)
			जारी;

		txinfo = IEEE80211_SKB_CB(bf->bf_mpdu);
		fi = (काष्ठा ath_frame_info *)&txinfo->rate_driver_data[0];
		अगर (fi->keyix == keyix)
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल bool ath9k_txq_has_key(काष्ठा ath_softc *sc, u32 keyix)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	पूर्णांक i;
	काष्ठा ath_txq *txq;
	bool key_in_use = false;

	क्रम (i = 0; !key_in_use && i < ATH9K_NUM_TX_QUEUES; i++) अणु
		अगर (!ATH_TXQ_SETUP(sc, i))
			जारी;
		txq = &sc->tx.txq[i];
		अगर (!txq->axq_depth)
			जारी;
		अगर (!ath9k_hw_numtxpending(ah, txq->axq_qnum))
			जारी;

		ath_txq_lock(sc, txq);
		key_in_use = ath9k_txq_list_has_key(&txq->axq_q, keyix);
		अगर (sc->sc_ah->caps.hw_caps & ATH9K_HW_CAP_EDMA) अणु
			पूर्णांक idx = txq->txq_tailidx;

			जबतक (!key_in_use &&
			       !list_empty(&txq->txq_fअगरo[idx])) अणु
				key_in_use = ath9k_txq_list_has_key(
					&txq->txq_fअगरo[idx], keyix);
				INCR(idx, ATH_TXFIFO_DEPTH);
			पूर्ण
		पूर्ण
		ath_txq_unlock(sc, txq);
	पूर्ण

	वापस key_in_use;
पूर्ण

अटल व्योम ath9k_pending_key_del(काष्ठा ath_softc *sc, u8 keyix)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (!test_bit(keyix, ah->pending_del_keymap) ||
	    ath9k_txq_has_key(sc, keyix))
		वापस;

	/* No more TXQ frames poपूर्णांक to this key cache entry, so delete it. */
	clear_bit(keyix, ah->pending_del_keymap);
	ath_key_delete(common, keyix);
पूर्ण

अटल व्योम ath9k_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	bool prev_idle;
	पूर्णांक i;

	ath9k_deinit_channel_context(sc);

	mutex_lock(&sc->mutex);

	ath9k_rng_stop(sc);

	ath_cancel_work(sc);

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags)) अणु
		ath_dbg(common, ANY, "Device not present\n");
		mutex_unlock(&sc->mutex);
		वापस;
	पूर्ण

	/* Ensure HW is awake when we try to shut it करोwn. */
	ath9k_ps_wakeup(sc);

	spin_lock_bh(&sc->sc_pcu_lock);

	/* prevent tasklets to enable पूर्णांकerrupts once we disable them */
	ah->imask &= ~ATH9K_INT_GLOBAL;

	/* make sure h/w will not generate any पूर्णांकerrupt
	 * beक्रमe setting the invalid flag. */
	ath9k_hw_disable_पूर्णांकerrupts(ah);

	spin_unlock_bh(&sc->sc_pcu_lock);

	/* we can now sync irq and समाप्त any running tasklets, since we alपढ़ोy
	 * disabled पूर्णांकerrupts and not holding a spin lock */
	synchronize_irq(sc->irq);
	tasklet_समाप्त(&sc->पूर्णांकr_tq);
	tasklet_समाप्त(&sc->bcon_tasklet);

	prev_idle = sc->ps_idle;
	sc->ps_idle = true;

	spin_lock_bh(&sc->sc_pcu_lock);

	अगर (ah->led_pin >= 0) अणु
		ath9k_hw_set_gpio(ah, ah->led_pin,
				  (ah->config.led_active_high) ? 0 : 1);
		ath9k_hw_gpio_request_in(ah, ah->led_pin, शून्य);
	पूर्ण

	ath_prepare_reset(sc);

	अगर (sc->rx.frag) अणु
		dev_kमुक्त_skb_any(sc->rx.frag);
		sc->rx.frag = शून्य;
	पूर्ण

	अगर (!ah->curchan)
		ah->curchan = ath9k_cmn_get_channel(hw, ah,
						    &sc->cur_chan->chandef);

	ath9k_hw_reset(ah, ah->curchan, ah->caldata, false);

	set_bit(ATH_OP_INVALID, &common->op_flags);

	ath9k_hw_phy_disable(ah);

	ath9k_hw_configpciघातersave(ah, true);

	spin_unlock_bh(&sc->sc_pcu_lock);

	क्रम (i = 0; i < ATH_KEYMAX; i++)
		ath9k_pending_key_del(sc, i);

	/* Clear key cache entries explicitly to get rid of any potentially
	 * reमुख्यing keys.
	 */
	ath9k_cmn_init_crypto(sc->sc_ah);

	ath9k_ps_restore(sc);

	sc->ps_idle = prev_idle;

	mutex_unlock(&sc->mutex);

	ath_dbg(common, CONFIG, "Driver halt\n");
पूर्ण

अटल bool ath9k_uses_beacons(पूर्णांक type)
अणु
	चयन (type) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_MESH_POINT:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल व्योम ath9k_vअगर_iter_set_beacon(काष्ठा ath9k_vअगर_iter_data *iter_data,
				      काष्ठा ieee80211_vअगर *vअगर)
अणु
	/* Use the first (configured) पूर्णांकerface, but prefering AP पूर्णांकerfaces. */
	अगर (!iter_data->primary_beacon_vअगर) अणु
		iter_data->primary_beacon_vअगर = vअगर;
	पूर्ण अन्यथा अणु
		अगर (iter_data->primary_beacon_vअगर->type != NL80211_IFTYPE_AP &&
		    vअगर->type == NL80211_IFTYPE_AP)
			iter_data->primary_beacon_vअगर = vअगर;
	पूर्ण

	iter_data->beacons = true;
	iter_data->nbcnvअगरs += 1;
पूर्ण

अटल व्योम ath9k_vअगर_iter(काष्ठा ath9k_vअगर_iter_data *iter_data,
			   u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_vअगर *avp = (काष्ठा ath_vअगर *)vअगर->drv_priv;
	पूर्णांक i;

	अगर (iter_data->has_hw_macaddr) अणु
		क्रम (i = 0; i < ETH_ALEN; i++)
			iter_data->mask[i] &=
				~(iter_data->hw_macaddr[i] ^ mac[i]);
	पूर्ण अन्यथा अणु
		स_नकल(iter_data->hw_macaddr, mac, ETH_ALEN);
		iter_data->has_hw_macaddr = true;
	पूर्ण

	अगर (!vअगर->bss_conf.use_लघु_slot)
		iter_data->slotसमय = 20;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_AP:
		iter_data->naps++;
		अगर (vअगर->bss_conf.enable_beacon)
			ath9k_vअगर_iter_set_beacon(iter_data, vअगर);
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		iter_data->nstations++;
		अगर (avp->assoc && !iter_data->primary_sta)
			iter_data->primary_sta = vअगर;
		अवरोध;
	हाल NL80211_IFTYPE_OCB:
		iter_data->nocbs++;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		iter_data->nadhocs++;
		अगर (vअगर->bss_conf.enable_beacon)
			ath9k_vअगर_iter_set_beacon(iter_data, vअगर);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		iter_data->nmeshes++;
		अगर (vअगर->bss_conf.enable_beacon)
			ath9k_vअगर_iter_set_beacon(iter_data, vअगर);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ath9k_update_bssid_mask(काष्ठा ath_softc *sc,
				    काष्ठा ath_chanctx *ctx,
				    काष्ठा ath9k_vअगर_iter_data *iter_data)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp;
	पूर्णांक i;

	अगर (!ath9k_is_chanctx_enabled())
		वापस;

	list_क्रम_each_entry(avp, &ctx->vअगरs, list) अणु
		अगर (ctx->nvअगरs_asचिन्हित != 1)
			जारी;

		अगर (!iter_data->has_hw_macaddr)
			जारी;

		ether_addr_copy(common->curbssid, avp->bssid);

		/* perm_addr will be used as the p2p device address. */
		क्रम (i = 0; i < ETH_ALEN; i++)
			iter_data->mask[i] &=
				~(iter_data->hw_macaddr[i] ^
				  sc->hw->wiphy->perm_addr[i]);
	पूर्ण
पूर्ण

/* Called with sc->mutex held. */
व्योम ath9k_calculate_iter_data(काष्ठा ath_softc *sc,
			       काष्ठा ath_chanctx *ctx,
			       काष्ठा ath9k_vअगर_iter_data *iter_data)
अणु
	काष्ठा ath_vअगर *avp;

	/*
	 * The hardware will use primary station addr together with the
	 * BSSID mask when matching addresses.
	 */
	स_रखो(iter_data, 0, माप(*iter_data));
	eth_broadcast_addr(iter_data->mask);
	iter_data->slotसमय = 9;

	list_क्रम_each_entry(avp, &ctx->vअगरs, list)
		ath9k_vअगर_iter(iter_data, avp->vअगर->addr, avp->vअगर);

	ath9k_update_bssid_mask(sc, ctx, iter_data);
पूर्ण

अटल व्योम ath9k_set_assoc_state(काष्ठा ath_softc *sc,
				  काष्ठा ieee80211_vअगर *vअगर, bool changed)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp = (काष्ठा ath_vअगर *)vअगर->drv_priv;
	अचिन्हित दीर्घ flags;

	set_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags);

	ether_addr_copy(common->curbssid, avp->bssid);
	common->curaid = avp->aid;
	ath9k_hw_ग_लिखो_associd(sc->sc_ah);

	अगर (changed) अणु
		common->last_rssi = ATH_RSSI_DUMMY_MARKER;
		sc->sc_ah->stats.avgbrssi = ATH_RSSI_DUMMY_MARKER;

		spin_lock_irqsave(&sc->sc_pm_lock, flags);
		sc->ps_flags |= PS_BEACON_SYNC | PS_WAIT_FOR_BEACON;
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
	पूर्ण

	अगर (ath9k_hw_mci_is_enabled(sc->sc_ah))
		ath9k_mci_update_wlan_channels(sc, false);

	ath_dbg(common, CONFIG,
		"Primary Station interface: %pM, BSSID: %pM\n",
		vअगर->addr, common->curbssid);
पूर्ण

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT
अटल व्योम ath9k_set_offchannel_state(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_vअगर *vअगर = शून्य;

	ath9k_ps_wakeup(sc);

	अगर (sc->offchannel.state < ATH_OFFCHANNEL_ROC_START)
		vअगर = sc->offchannel.scan_vअगर;
	अन्यथा
		vअगर = sc->offchannel.roc_vअगर;

	अगर (WARN_ON(!vअगर))
		जाओ निकास;

	eth_zero_addr(common->curbssid);
	eth_broadcast_addr(common->bssidmask);
	स_नकल(common->macaddr, vअगर->addr, ETH_ALEN);
	common->curaid = 0;
	ah->opmode = vअगर->type;
	ah->imask &= ~ATH9K_INT_SWBA;
	ah->imask &= ~ATH9K_INT_TSFOOR;
	ah->slotसमय = 9;

	ath_hw_setbssidmask(common);
	ath9k_hw_setopmode(ah);
	ath9k_hw_ग_लिखो_associd(sc->sc_ah);
	ath9k_hw_set_पूर्णांकerrupts(ah);
	ath9k_hw_init_global_settings(ah);

निकास:
	ath9k_ps_restore(sc);
पूर्ण
#पूर्ण_अगर

/* Called with sc->mutex held. */
व्योम ath9k_calculate_summary_state(काष्ठा ath_softc *sc,
				   काष्ठा ath_chanctx *ctx)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath9k_vअगर_iter_data iter_data;

	ath_chanctx_check_active(sc, ctx);

	अगर (ctx != sc->cur_chan)
		वापस;

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT
	अगर (ctx == &sc->offchannel.chan)
		वापस ath9k_set_offchannel_state(sc);
#पूर्ण_अगर

	ath9k_ps_wakeup(sc);
	ath9k_calculate_iter_data(sc, ctx, &iter_data);

	अगर (iter_data.has_hw_macaddr)
		स_नकल(common->macaddr, iter_data.hw_macaddr, ETH_ALEN);

	स_नकल(common->bssidmask, iter_data.mask, ETH_ALEN);
	ath_hw_setbssidmask(common);

	अगर (iter_data.naps > 0) अणु
		ath9k_hw_set_tsfadjust(ah, true);
		ah->opmode = NL80211_IFTYPE_AP;
	पूर्ण अन्यथा अणु
		ath9k_hw_set_tsfadjust(ah, false);
		अगर (iter_data.beacons)
			ath9k_beacon_ensure_primary_slot(sc);

		अगर (iter_data.nmeshes)
			ah->opmode = NL80211_IFTYPE_MESH_POINT;
		अन्यथा अगर (iter_data.nocbs)
			ah->opmode = NL80211_IFTYPE_OCB;
		अन्यथा अगर (iter_data.nadhocs)
			ah->opmode = NL80211_IFTYPE_ADHOC;
		अन्यथा
			ah->opmode = NL80211_IFTYPE_STATION;
	पूर्ण

	ath9k_hw_setopmode(ah);

	ctx->चयन_after_beacon = false;
	अगर ((iter_data.nstations + iter_data.nadhocs + iter_data.nmeshes) > 0)
		ah->imask |= ATH9K_INT_TSFOOR;
	अन्यथा अणु
		ah->imask &= ~ATH9K_INT_TSFOOR;
		अगर (iter_data.naps == 1 && iter_data.beacons)
			ctx->चयन_after_beacon = true;
	पूर्ण

	अगर (ah->opmode == NL80211_IFTYPE_STATION) अणु
		bool changed = (iter_data.primary_sta != ctx->primary_sta);

		अगर (iter_data.primary_sta) अणु
			iter_data.primary_beacon_vअगर = iter_data.primary_sta;
			iter_data.beacons = true;
			ath9k_set_assoc_state(sc, iter_data.primary_sta,
					      changed);
			ctx->primary_sta = iter_data.primary_sta;
		पूर्ण अन्यथा अणु
			ctx->primary_sta = शून्य;
			eth_zero_addr(common->curbssid);
			common->curaid = 0;
			ath9k_hw_ग_लिखो_associd(sc->sc_ah);
			अगर (ath9k_hw_mci_is_enabled(sc->sc_ah))
				ath9k_mci_update_wlan_channels(sc, true);
		पूर्ण
	पूर्ण
	sc->nbcnvअगरs = iter_data.nbcnvअगरs;
	ath9k_beacon_config(sc, iter_data.primary_beacon_vअगर,
			    iter_data.beacons);
	ath9k_hw_set_पूर्णांकerrupts(ah);

	अगर (ah->slotसमय != iter_data.slotसमय) अणु
		ah->slotसमय = iter_data.slotसमय;
		ath9k_hw_init_global_settings(ah);
	पूर्ण

	अगर (iter_data.primary_sta)
		set_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags);
	अन्यथा
		clear_bit(ATH_OP_PRIM_STA_VIF, &common->op_flags);

	ath_dbg(common, CONFIG,
		"macaddr: %pM, bssid: %pM, bssidmask: %pM\n",
		common->macaddr, common->curbssid, common->bssidmask);

	ath9k_ps_restore(sc);
पूर्ण

अटल व्योम ath9k_tpc_vअगर_iter(व्योम *data, u8 *mac, काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक *घातer = data;

	अगर (vअगर->bss_conf.txघातer == पूर्णांक_न्यून)
		वापस;

	अगर (*घातer < vअगर->bss_conf.txघातer)
		*घातer = vअगर->bss_conf.txघातer;
पूर्ण

/* Called with sc->mutex held. */
व्योम ath9k_set_txघातer(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक घातer;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_regulatory *reg = ath9k_hw_regulatory(ah);

	ath9k_ps_wakeup(sc);
	अगर (ah->tpc_enabled) अणु
		घातer = (vअगर) ? vअगर->bss_conf.txघातer : -1;
		ieee80211_iterate_active_पूर्णांकerfaces_atomic(
				sc->hw, IEEE80211_IFACE_ITER_RESUME_ALL,
				ath9k_tpc_vअगर_iter, &घातer);
		अगर (घातer == -1)
			घातer = sc->hw->conf.घातer_level;
	पूर्ण अन्यथा अणु
		घातer = sc->hw->conf.घातer_level;
	पूर्ण
	sc->cur_chan->txघातer = 2 * घातer;
	ath9k_hw_set_txघातerlimit(ah, sc->cur_chan->txघातer, false);
	sc->cur_chan->cur_txघातer = reg->max_घातer_level;
	ath9k_ps_restore(sc);
पूर्ण

अटल व्योम ath9k_assign_hw_queues(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	पूर्णांक i;

	अगर (!ath9k_is_chanctx_enabled())
		वापस;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++)
		vअगर->hw_queue[i] = i;

	अगर (vअगर->type == NL80211_IFTYPE_AP ||
	    vअगर->type == NL80211_IFTYPE_MESH_POINT)
		vअगर->cab_queue = hw->queues - 2;
	अन्यथा
		vअगर->cab_queue = IEEE80211_INVAL_HW_QUEUE;
पूर्ण

अटल पूर्णांक ath9k_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	काष्ठा ath_node *an = &avp->mcast_node;

	mutex_lock(&sc->mutex);
	अगर (IS_ENABLED(CONFIG_ATH9K_TX99)) अणु
		अगर (sc->cur_chan->nvअगरs >= 1) अणु
			mutex_unlock(&sc->mutex);
			वापस -EOPNOTSUPP;
		पूर्ण
		sc->tx99_vअगर = vअगर;
	पूर्ण

	ath_dbg(common, CONFIG, "Attach a VIF of type: %d\n", vअगर->type);
	sc->cur_chan->nvअगरs++;

	अगर (vअगर->type == NL80211_IFTYPE_STATION && ath9k_is_chanctx_enabled())
		vअगर->driver_flags |= IEEE80211_VIF_GET_NOA_UPDATE;

	अगर (ath9k_uses_beacons(vअगर->type))
		ath9k_beacon_assign_slot(sc, vअगर);

	avp->vअगर = vअगर;
	अगर (!ath9k_is_chanctx_enabled()) अणु
		avp->chanctx = sc->cur_chan;
		list_add_tail(&avp->list, &avp->chanctx->vअगरs);
	पूर्ण

	ath9k_calculate_summary_state(sc, avp->chanctx);

	ath9k_assign_hw_queues(hw, vअगर);

	ath9k_set_txघातer(sc, vअगर);

	an->sc = sc;
	an->sta = शून्य;
	an->vअगर = vअगर;
	an->no_ps_filter = true;
	ath_tx_node_init(sc, an);

	mutex_unlock(&sc->mutex);
	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_change_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  क्रमागत nl80211_अगरtype new_type,
				  bool p2p)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;

	mutex_lock(&sc->mutex);

	अगर (IS_ENABLED(CONFIG_ATH9K_TX99)) अणु
		mutex_unlock(&sc->mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	ath_dbg(common, CONFIG, "Change Interface\n");

	अगर (ath9k_uses_beacons(vअगर->type))
		ath9k_beacon_हटाओ_slot(sc, vअगर);

	vअगर->type = new_type;
	vअगर->p2p = p2p;

	अगर (ath9k_uses_beacons(vअगर->type))
		ath9k_beacon_assign_slot(sc, vअगर);

	ath9k_assign_hw_queues(hw, vअगर);
	ath9k_calculate_summary_state(sc, avp->chanctx);

	ath9k_set_txघातer(sc, vअगर);

	mutex_unlock(&sc->mutex);
	वापस 0;
पूर्ण

अटल व्योम ath9k_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;

	ath_dbg(common, CONFIG, "Detach Interface\n");

	mutex_lock(&sc->mutex);

	ath9k_p2p_हटाओ_vअगर(sc, vअगर);

	sc->cur_chan->nvअगरs--;
	sc->tx99_vअगर = शून्य;
	अगर (!ath9k_is_chanctx_enabled())
		list_del(&avp->list);

	अगर (ath9k_uses_beacons(vअगर->type))
		ath9k_beacon_हटाओ_slot(sc, vअगर);

	ath_tx_node_cleanup(sc, &avp->mcast_node);

	ath9k_calculate_summary_state(sc, avp->chanctx);

	ath9k_set_txघातer(sc, शून्य);

	mutex_unlock(&sc->mutex);
पूर्ण

अटल व्योम ath9k_enable_ps(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (IS_ENABLED(CONFIG_ATH9K_TX99))
		वापस;

	sc->ps_enabled = true;
	अगर (!(ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSLEEP)) अणु
		अगर ((ah->imask & ATH9K_INT_TIM_TIMER) == 0) अणु
			ah->imask |= ATH9K_INT_TIM_TIMER;
			ath9k_hw_set_पूर्णांकerrupts(ah);
		पूर्ण
		ath9k_hw_setrxपात(ah, 1);
	पूर्ण
	ath_dbg(common, PS, "PowerSave enabled\n");
पूर्ण

अटल व्योम ath9k_disable_ps(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);

	अगर (IS_ENABLED(CONFIG_ATH9K_TX99))
		वापस;

	sc->ps_enabled = false;
	ath9k_hw_setघातer(ah, ATH9K_PM_AWAKE);
	अगर (!(ah->caps.hw_caps & ATH9K_HW_CAP_AUTOSLEEP)) अणु
		ath9k_hw_setrxपात(ah, 0);
		sc->ps_flags &= ~(PS_WAIT_FOR_BEACON |
				  PS_WAIT_FOR_CAB |
				  PS_WAIT_FOR_PSPOLL_DATA |
				  PS_WAIT_FOR_TX_ACK);
		अगर (ah->imask & ATH9K_INT_TIM_TIMER) अणु
			ah->imask &= ~ATH9K_INT_TIM_TIMER;
			ath9k_hw_set_पूर्णांकerrupts(ah);
		पूर्ण
	पूर्ण
	ath_dbg(common, PS, "PowerSave disabled\n");
पूर्ण

अटल पूर्णांक ath9k_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_conf *conf = &hw->conf;
	काष्ठा ath_chanctx *ctx = sc->cur_chan;

	ath9k_ps_wakeup(sc);
	mutex_lock(&sc->mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_IDLE) अणु
		sc->ps_idle = !!(conf->flags & IEEE80211_CONF_IDLE);
		अगर (sc->ps_idle) अणु
			ath_cancel_work(sc);
			ath9k_stop_btcoex(sc);
		पूर्ण अन्यथा अणु
			ath9k_start_btcoex(sc);
			/*
			 * The chip needs a reset to properly wake up from
			 * full sleep
			 */
			ath_chanctx_set_channel(sc, ctx, &ctx->chandef);
		पूर्ण
	पूर्ण

	/*
	 * We just prepare to enable PS. We have to रुको until our AP has
	 * ACK'd our null data frame to disable RX otherwise we'll ignore
	 * those ACKs and end up retransmitting the same null data frames.
	 * IEEE80211_CONF_CHANGE_PS is only passed by mac80211 क्रम STA mode.
	 */
	अगर (changed & IEEE80211_CONF_CHANGE_PS) अणु
		अचिन्हित दीर्घ flags;
		spin_lock_irqsave(&sc->sc_pm_lock, flags);
		अगर (conf->flags & IEEE80211_CONF_PS)
			ath9k_enable_ps(sc);
		अन्यथा
			ath9k_disable_ps(sc);
		spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_MONITOR) अणु
		अगर (conf->flags & IEEE80211_CONF_MONITOR) अणु
			ath_dbg(common, CONFIG, "Monitor mode is enabled\n");
			sc->sc_ah->is_monitoring = true;
		पूर्ण अन्यथा अणु
			ath_dbg(common, CONFIG, "Monitor mode is disabled\n");
			sc->sc_ah->is_monitoring = false;
		पूर्ण
	पूर्ण

	अगर (!ath9k_is_chanctx_enabled() && (changed & IEEE80211_CONF_CHANGE_CHANNEL)) अणु
		ctx->offchannel = !!(conf->flags & IEEE80211_CONF_OFFCHANNEL);
		ath_chanctx_set_channel(sc, ctx, &hw->conf.chandef);
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_POWER)
		ath9k_set_txघातer(sc, शून्य);

	mutex_unlock(&sc->mutex);
	ath9k_ps_restore(sc);

	वापस 0;
पूर्ण

#घोषणा SUPPORTED_FILTERS			\
	(FIF_ALLMULTI |				\
	FIF_CONTROL |				\
	FIF_PSPOLL |				\
	FIF_OTHER_BSS |				\
	FIF_BCN_PRBRESP_PROMISC |		\
	FIF_PROBE_REQ |				\
	FIF_MCAST_ACTION |			\
	FIF_FCSFAIL)

/* FIXME: sc->sc_full_reset ? */
अटल व्योम ath9k_configure_filter(काष्ठा ieee80211_hw *hw,
				   अचिन्हित पूर्णांक changed_flags,
				   अचिन्हित पूर्णांक *total_flags,
				   u64 multicast)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_chanctx *ctx;
	u32 rfilt;

	changed_flags &= SUPPORTED_FILTERS;
	*total_flags &= SUPPORTED_FILTERS;

	spin_lock_bh(&sc->chan_lock);
	ath_क्रम_each_chanctx(sc, ctx)
		ctx->rxfilter = *total_flags;
#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT
	sc->offchannel.chan.rxfilter = *total_flags;
#पूर्ण_अगर
	spin_unlock_bh(&sc->chan_lock);

	ath9k_ps_wakeup(sc);
	rfilt = ath_calcrxfilter(sc);
	ath9k_hw_setrxfilter(sc->sc_ah, rfilt);
	ath9k_ps_restore(sc);

	ath_dbg(ath9k_hw_common(sc->sc_ah), CONFIG, "Set HW RX filter: 0x%x\n",
		rfilt);
पूर्ण

अटल पूर्णांक ath9k_sta_add(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_node *an = (काष्ठा ath_node *) sta->drv_priv;
	काष्ठा ieee80211_key_conf ps_key = अणु पूर्ण;
	पूर्णांक key;

	ath_node_attach(sc, sta, vअगर);

	अगर (vअगर->type != NL80211_IFTYPE_AP &&
	    vअगर->type != NL80211_IFTYPE_AP_VLAN)
		वापस 0;

	key = ath_key_config(common, vअगर, sta, &ps_key);
	अगर (key > 0) अणु
		an->ps_key = key;
		an->key_idx[0] = key;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम ath9k_del_ps_key(काष्ठा ath_softc *sc,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_node *an = (काष्ठा ath_node *) sta->drv_priv;

	अगर (!an->ps_key)
	    वापस;

	ath_key_delete(common, an->ps_key);
	an->ps_key = 0;
	an->key_idx[0] = 0;
पूर्ण

अटल पूर्णांक ath9k_sta_हटाओ(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath_softc *sc = hw->priv;

	ath9k_del_ps_key(sc, vअगर, sta);
	ath_node_detach(sc, sta);

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_sta_state(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta,
			   क्रमागत ieee80211_sta_state old_state,
			   क्रमागत ieee80211_sta_state new_state)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	पूर्णांक ret = 0;

	अगर (old_state == IEEE80211_STA_NOTEXIST &&
	    new_state == IEEE80211_STA_NONE) अणु
		ret = ath9k_sta_add(hw, vअगर, sta);
		ath_dbg(common, CONFIG,
			"Add station: %pM\n", sta->addr);
	पूर्ण अन्यथा अगर (old_state == IEEE80211_STA_NONE &&
		   new_state == IEEE80211_STA_NOTEXIST) अणु
		ret = ath9k_sta_हटाओ(hw, vअगर, sta);
		ath_dbg(common, CONFIG,
			"Remove station: %pM\n", sta->addr);
	पूर्ण

	अगर (ath9k_is_chanctx_enabled()) अणु
		अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
			अगर (old_state == IEEE80211_STA_ASSOC &&
			    new_state == IEEE80211_STA_AUTHORIZED)
				ath_chanctx_event(sc, vअगर,
						  ATH_CHANCTX_EVENT_AUTHORIZED);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम ath9k_sta_set_tx_filter(काष्ठा ath_hw *ah,
				    काष्ठा ath_node *an,
				    bool set)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(an->key_idx); i++) अणु
		अगर (!an->key_idx[i])
			जारी;
		ath9k_hw_set_tx_filter(ah, an->key_idx[i], set);
	पूर्ण
पूर्ण

अटल व्योम ath9k_sta_notअगरy(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 क्रमागत sta_notअगरy_cmd cmd,
			 काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_node *an = (काष्ठा ath_node *) sta->drv_priv;

	चयन (cmd) अणु
	हाल STA_NOTIFY_SLEEP:
		an->sleeping = true;
		ath_tx_aggr_sleep(sta, sc, an);
		ath9k_sta_set_tx_filter(sc->sc_ah, an, true);
		अवरोध;
	हाल STA_NOTIFY_AWAKE:
		ath9k_sta_set_tx_filter(sc->sc_ah, an, false);
		an->sleeping = false;
		ath_tx_aggr_wakeup(sc, an);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक ath9k_conf_tx(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर, u16 queue,
			 स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_txq *txq;
	काष्ठा ath9k_tx_queue_info qi;
	पूर्णांक ret = 0;

	अगर (queue >= IEEE80211_NUM_ACS)
		वापस 0;

	txq = sc->tx.txq_map[queue];

	ath9k_ps_wakeup(sc);
	mutex_lock(&sc->mutex);

	स_रखो(&qi, 0, माप(काष्ठा ath9k_tx_queue_info));

	qi.tqi_aअगरs = params->aअगरs;
	qi.tqi_cwmin = params->cw_min;
	qi.tqi_cwmax = params->cw_max;
	qi.tqi_burstTime = params->txop * 32;

	ath_dbg(common, CONFIG,
		"Configure tx [queue/halq] [%d/%d], aifs: %d, cw_min: %d, cw_max: %d, txop: %d\n",
		queue, txq->axq_qnum, params->aअगरs, params->cw_min,
		params->cw_max, params->txop);

	ath_update_max_aggr_framelen(sc, queue, qi.tqi_burstTime);
	ret = ath_txq_update(sc, txq->axq_qnum, &qi);
	अगर (ret)
		ath_err(common, "TXQ Update failed\n");

	mutex_unlock(&sc->mutex);
	ath9k_ps_restore(sc);

	वापस ret;
पूर्ण

अटल पूर्णांक ath9k_set_key(काष्ठा ieee80211_hw *hw,
			 क्रमागत set_key_cmd cmd,
			 काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_sta *sta,
			 काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_node *an = शून्य;
	पूर्णांक ret = 0, i;

	अगर (ath9k_modparam_nohwcrypt)
		वापस -ENOSPC;

	अगर ((vअगर->type == NL80211_IFTYPE_ADHOC ||
	     vअगर->type == NL80211_IFTYPE_MESH_POINT) &&
	    (key->cipher == WLAN_CIPHER_SUITE_TKIP ||
	     key->cipher == WLAN_CIPHER_SUITE_CCMP) &&
	    !(key->flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		/*
		 * For now, disable hw crypto क्रम the RSN IBSS group keys. This
		 * could be optimized in the future to use a modअगरied key cache
		 * design to support per-STA RX GTK, but until that माला_लो
		 * implemented, use of software crypto क्रम group addressed
		 * frames is a acceptable to allow RSN IBSS to be used.
		 */
		वापस -EOPNOTSUPP;
	पूर्ण

	/* There may be MPDUs queued क्रम the outgoing PTK key. Flush queues to
	 * make sure these are not send unencrypted or with a wrong (new) key
	 */
	अगर (cmd == DISABLE_KEY && key->flags & IEEE80211_KEY_FLAG_PAIRWISE) अणु
		ieee80211_stop_queues(hw);
		ath9k_flush(hw, vअगर, 0, true);
		ieee80211_wake_queues(hw);
	पूर्ण

	mutex_lock(&sc->mutex);
	ath9k_ps_wakeup(sc);
	ath_dbg(common, CONFIG, "Set HW Key %d\n", cmd);
	अगर (sta)
		an = (काष्ठा ath_node *)sta->drv_priv;

	/* Delete pending key cache entries अगर no more frames are poपूर्णांकing to
	 * them in TXQs.
	 */
	क्रम (i = 0; i < ATH_KEYMAX; i++)
		ath9k_pending_key_del(sc, i);

	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (sta)
			ath9k_del_ps_key(sc, vअगर, sta);

		key->hw_key_idx = 0;
		ret = ath_key_config(common, vअगर, sta, key);
		अगर (ret >= 0) अणु
			key->hw_key_idx = ret;
			/* push IV and Michael MIC generation to stack */
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			अगर (key->cipher == WLAN_CIPHER_SUITE_TKIP)
				key->flags |= IEEE80211_KEY_FLAG_GENERATE_MMIC;
			अगर (sc->sc_ah->sw_mgmt_crypto_tx &&
			    key->cipher == WLAN_CIPHER_SUITE_CCMP)
				key->flags |= IEEE80211_KEY_FLAG_SW_MGMT_TX;
			ret = 0;
		पूर्ण
		अगर (an && key->hw_key_idx) अणु
			क्रम (i = 0; i < ARRAY_SIZE(an->key_idx); i++) अणु
				अगर (an->key_idx[i])
					जारी;
				an->key_idx[i] = key->hw_key_idx;
				अवरोध;
			पूर्ण
			WARN_ON(i == ARRAY_SIZE(an->key_idx));
		पूर्ण
		अवरोध;
	हाल DISABLE_KEY:
		अगर (ath9k_txq_has_key(sc, key->hw_key_idx)) अणु
			/* Delay key cache entry deletion until there are no
			 * reमुख्यing TXQ frames poपूर्णांकing to this entry.
			 */
			set_bit(key->hw_key_idx, sc->sc_ah->pending_del_keymap);
			ath_hw_keyseपंचांगac(common, key->hw_key_idx, शून्य);
		पूर्ण अन्यथा अणु
			ath_key_delete(common, key->hw_key_idx);
		पूर्ण
		अगर (an) अणु
			क्रम (i = 0; i < ARRAY_SIZE(an->key_idx); i++) अणु
				अगर (an->key_idx[i] != key->hw_key_idx)
					जारी;
				an->key_idx[i] = 0;
				अवरोध;
			पूर्ण
		पूर्ण
		key->hw_key_idx = 0;
		अवरोध;
	शेष:
		ret = -EINVAL;
	पूर्ण

	ath9k_ps_restore(sc);
	mutex_unlock(&sc->mutex);

	वापस ret;
पूर्ण

अटल व्योम ath9k_bss_info_changed(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_bss_conf *bss_conf,
				   u32 changed)
अणु
#घोषणा CHECK_ANI				\
	(BSS_CHANGED_ASSOC |			\
	 BSS_CHANGED_IBSS |			\
	 BSS_CHANGED_BEACON_ENABLED)

	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	पूर्णांक slotसमय;

	ath9k_ps_wakeup(sc);
	mutex_lock(&sc->mutex);

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		ath_dbg(common, CONFIG, "BSSID %pM Changed ASSOC %d\n",
			bss_conf->bssid, bss_conf->assoc);

		स_नकल(avp->bssid, bss_conf->bssid, ETH_ALEN);
		avp->aid = bss_conf->aid;
		avp->assoc = bss_conf->assoc;

		ath9k_calculate_summary_state(sc, avp->chanctx);
	पूर्ण

	अगर ((changed & BSS_CHANGED_IBSS) ||
	      (changed & BSS_CHANGED_OCB)) अणु
		स_नकल(common->curbssid, bss_conf->bssid, ETH_ALEN);
		common->curaid = bss_conf->aid;
		ath9k_hw_ग_लिखो_associd(sc->sc_ah);
	पूर्ण

	अगर ((changed & BSS_CHANGED_BEACON_ENABLED) ||
	    (changed & BSS_CHANGED_BEACON_INT) ||
	    (changed & BSS_CHANGED_BEACON_INFO)) अणु
		ath9k_calculate_summary_state(sc, avp->chanctx);
	पूर्ण

	अगर ((avp->chanctx == sc->cur_chan) &&
	    (changed & BSS_CHANGED_ERP_SLOT)) अणु
		अगर (bss_conf->use_लघु_slot)
			slotसमय = 9;
		अन्यथा
			slotसमय = 20;

		अगर (vअगर->type == NL80211_IFTYPE_AP) अणु
			/*
			 * Defer update, so that connected stations can adjust
			 * their settings at the same समय.
			 * See beacon.c क्रम more details
			 */
			sc->beacon.slotसमय = slotसमय;
			sc->beacon.updateslot = UPDATE;
		पूर्ण अन्यथा अणु
			ah->slotसमय = slotसमय;
			ath9k_hw_init_global_settings(ah);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_P2P_PS)
		ath9k_p2p_bss_info_changed(sc, vअगर);

	अगर (changed & CHECK_ANI)
		ath_check_ani(sc);

	अगर (changed & BSS_CHANGED_TXPOWER) अणु
		ath_dbg(common, CONFIG, "vif %pM power %d dbm power_type %d\n",
			vअगर->addr, bss_conf->txघातer, bss_conf->txघातer_type);
		ath9k_set_txघातer(sc, vअगर);
	पूर्ण

	mutex_unlock(&sc->mutex);
	ath9k_ps_restore(sc);

#अघोषित CHECK_ANI
पूर्ण

अटल u64 ath9k_get_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	u64 tsf;

	mutex_lock(&sc->mutex);
	ath9k_ps_wakeup(sc);
	/* Get current TSF either from HW or kernel समय. */
	अगर (sc->cur_chan == avp->chanctx) अणु
		tsf = ath9k_hw_gettsf64(sc->sc_ah);
	पूर्ण अन्यथा अणु
		tsf = sc->cur_chan->tsf_val +
		      ath9k_hw_get_tsf_offset(&sc->cur_chan->tsf_ts, शून्य);
	पूर्ण
	tsf += le64_to_cpu(avp->tsf_adjust);
	ath9k_ps_restore(sc);
	mutex_unlock(&sc->mutex);

	वापस tsf;
पूर्ण

अटल व्योम ath9k_set_tsf(काष्ठा ieee80211_hw *hw,
			  काष्ठा ieee80211_vअगर *vअगर,
			  u64 tsf)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;

	mutex_lock(&sc->mutex);
	ath9k_ps_wakeup(sc);
	tsf -= le64_to_cpu(avp->tsf_adjust);
	kसमय_get_raw_ts64(&avp->chanctx->tsf_ts);
	अगर (sc->cur_chan == avp->chanctx)
		ath9k_hw_settsf64(sc->sc_ah, tsf);
	avp->chanctx->tsf_val = tsf;
	ath9k_ps_restore(sc);
	mutex_unlock(&sc->mutex);
पूर्ण

अटल व्योम ath9k_reset_tsf(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;

	mutex_lock(&sc->mutex);

	ath9k_ps_wakeup(sc);
	kसमय_get_raw_ts64(&avp->chanctx->tsf_ts);
	अगर (sc->cur_chan == avp->chanctx)
		ath9k_hw_reset_tsf(sc->sc_ah);
	avp->chanctx->tsf_val = 0;
	ath9k_ps_restore(sc);

	mutex_unlock(&sc->mutex);
पूर्ण

अटल पूर्णांक ath9k_ampdu_action(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	bool flush = false;
	पूर्णांक ret = 0;
	काष्ठा ieee80211_sta *sta = params->sta;
	काष्ठा ath_node *an = (काष्ठा ath_node *)sta->drv_priv;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;
	काष्ठा ath_atx_tid *atid;

	mutex_lock(&sc->mutex);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		अगर (ath9k_is_chanctx_enabled()) अणु
			अगर (test_bit(ATH_OP_SCANNING, &common->op_flags)) अणु
				ret = -EBUSY;
				अवरोध;
			पूर्ण
		पूर्ण
		ath9k_ps_wakeup(sc);
		ret = ath_tx_aggr_start(sc, sta, tid, ssn);
		अगर (!ret)
			ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		ath9k_ps_restore(sc);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
		flush = true;
		fallthrough;
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		ath9k_ps_wakeup(sc);
		ath_tx_aggr_stop(sc, sta, tid);
		अगर (!flush)
			ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		ath9k_ps_restore(sc);
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		atid = ath_node_to_tid(an, tid);
		atid->baw_size = IEEE80211_MIN_AMPDU_BUF <<
			        sta->ht_cap.ampdu_factor;
		अवरोध;
	शेष:
		ath_err(ath9k_hw_common(sc->sc_ah), "Unknown AMPDU action\n");
	पूर्ण

	mutex_unlock(&sc->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath9k_get_survey(काष्ठा ieee80211_hw *hw, पूर्णांक idx,
			     काष्ठा survey_info *survey)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *chan;
	अचिन्हित दीर्घ flags;
	पूर्णांक pos;

	अगर (IS_ENABLED(CONFIG_ATH9K_TX99))
		वापस -EOPNOTSUPP;

	spin_lock_irqsave(&common->cc_lock, flags);
	अगर (idx == 0)
		ath_update_survey_stats(sc);

	sband = hw->wiphy->bands[NL80211_BAND_2GHZ];
	अगर (sband && idx >= sband->n_channels) अणु
		idx -= sband->n_channels;
		sband = शून्य;
	पूर्ण

	अगर (!sband)
		sband = hw->wiphy->bands[NL80211_BAND_5GHZ];

	अगर (!sband || idx >= sband->n_channels) अणु
		spin_unlock_irqrestore(&common->cc_lock, flags);
		वापस -ENOENT;
	पूर्ण

	chan = &sband->channels[idx];
	pos = chan->hw_value;
	स_नकल(survey, &sc->survey[pos], माप(*survey));
	survey->channel = chan;
	spin_unlock_irqrestore(&common->cc_lock, flags);

	वापस 0;
पूर्ण

अटल व्योम ath9k_enable_dynack(काष्ठा ath_softc *sc)
अणु
#अगर_घोषित CONFIG_ATH9K_DYNACK
	u32 rfilt;
	काष्ठा ath_hw *ah = sc->sc_ah;

	ath_dynack_reset(ah);

	ah->dynack.enabled = true;
	rfilt = ath_calcrxfilter(sc);
	ath9k_hw_setrxfilter(ah, rfilt);
#पूर्ण_अगर
पूर्ण

अटल व्योम ath9k_set_coverage_class(काष्ठा ieee80211_hw *hw,
				     s16 coverage_class)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (IS_ENABLED(CONFIG_ATH9K_TX99))
		वापस;

	mutex_lock(&sc->mutex);

	अगर (coverage_class >= 0) अणु
		ah->coverage_class = coverage_class;
		अगर (ah->dynack.enabled) अणु
			u32 rfilt;

			ah->dynack.enabled = false;
			rfilt = ath_calcrxfilter(sc);
			ath9k_hw_setrxfilter(ah, rfilt);
		पूर्ण
		ath9k_ps_wakeup(sc);
		ath9k_hw_init_global_settings(ah);
		ath9k_ps_restore(sc);
	पूर्ण अन्यथा अगर (!ah->dynack.enabled) अणु
		ath9k_enable_dynack(sc);
	पूर्ण

	mutex_unlock(&sc->mutex);
पूर्ण

अटल bool ath9k_has_tx_pending(काष्ठा ath_softc *sc,
				 bool sw_pending)
अणु
	पूर्णांक i, npend = 0;

	क्रम (i = 0; i < ATH9K_NUM_TX_QUEUES; i++) अणु
		अगर (!ATH_TXQ_SETUP(sc, i))
			जारी;

		npend = ath9k_has_pending_frames(sc, &sc->tx.txq[i],
						 sw_pending);
		अगर (npend)
			अवरोध;
	पूर्ण

	वापस !!npend;
पूर्ण

अटल व्योम ath9k_flush(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			u32 queues, bool drop)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	अगर (ath9k_is_chanctx_enabled()) अणु
		अगर (!test_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags))
			जाओ flush;

		/*
		 * If MCC is active, extend the flush समयout
		 * and रुको क्रम the HW/SW queues to become
		 * empty. This needs to be करोne outside the
		 * sc->mutex lock to allow the channel scheduler
		 * to चयन channel contexts.
		 *
		 * The vअगर queues have been stopped in mac80211,
		 * so there won't be any incoming frames.
		 */
		__ath9k_flush(hw, queues, drop, true, true);
		वापस;
	पूर्ण
flush:
	mutex_lock(&sc->mutex);
	__ath9k_flush(hw, queues, drop, true, false);
	mutex_unlock(&sc->mutex);
पूर्ण

व्योम __ath9k_flush(काष्ठा ieee80211_hw *hw, u32 queues, bool drop,
		   bool sw_pending, bool समयout_override)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	पूर्णांक समयout;
	bool drain_txq;

	cancel_delayed_work_sync(&sc->hw_check_work);

	अगर (ah->ah_flags & AH_UNPLUGGED) अणु
		ath_dbg(common, ANY, "Device has been unplugged!\n");
		वापस;
	पूर्ण

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags)) अणु
		ath_dbg(common, ANY, "Device not present\n");
		वापस;
	पूर्ण

	spin_lock_bh(&sc->chan_lock);
	अगर (समयout_override)
		समयout = HZ / 5;
	अन्यथा
		समयout = sc->cur_chan->flush_समयout;
	spin_unlock_bh(&sc->chan_lock);

	ath_dbg(common, CHAN_CTX,
		"Flush timeout: %d\n", jअगरfies_to_msecs(समयout));

	अगर (रुको_event_समयout(sc->tx_रुको, !ath9k_has_tx_pending(sc, sw_pending),
			       समयout) > 0)
		drop = false;

	अगर (drop) अणु
		ath9k_ps_wakeup(sc);
		spin_lock_bh(&sc->sc_pcu_lock);
		drain_txq = ath_drain_all_txq(sc);
		spin_unlock_bh(&sc->sc_pcu_lock);

		अगर (!drain_txq)
			ath_reset(sc, शून्य);

		ath9k_ps_restore(sc);
	पूर्ण

	ieee80211_queue_delayed_work(hw, &sc->hw_check_work,
				     ATH_HW_CHECK_POLL_INT);
पूर्ण

अटल bool ath9k_tx_frames_pending(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_softc *sc = hw->priv;

	वापस ath9k_has_tx_pending(sc, true);
पूर्ण

अटल पूर्णांक ath9k_tx_last_beacon(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ath_vअगर *avp;
	काष्ठा ath_buf *bf;
	काष्ठा ath_tx_status ts;
	bool edma = !!(ah->caps.hw_caps & ATH9K_HW_CAP_EDMA);
	पूर्णांक status;

	vअगर = sc->beacon.bslot[0];
	अगर (!vअगर)
		वापस 0;

	अगर (!vअगर->bss_conf.enable_beacon)
		वापस 0;

	avp = (व्योम *)vअगर->drv_priv;

	अगर (!sc->beacon.tx_processed && !edma) अणु
		tasklet_disable(&sc->bcon_tasklet);

		bf = avp->av_bcbuf;
		अगर (!bf || !bf->bf_mpdu)
			जाओ skip;

		status = ath9k_hw_txprocdesc(ah, bf->bf_desc, &ts);
		अगर (status == -EINPROGRESS)
			जाओ skip;

		sc->beacon.tx_processed = true;
		sc->beacon.tx_last = !(ts.ts_status & ATH9K_TXERR_MASK);

skip:
		tasklet_enable(&sc->bcon_tasklet);
	पूर्ण

	वापस sc->beacon.tx_last;
पूर्ण

अटल पूर्णांक ath9k_get_stats(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath9k_mib_stats *mib_stats = &ah->ah_mibStats;

	stats->करोt11ACKFailureCount = mib_stats->ackrcv_bad;
	stats->करोt11RTSFailureCount = mib_stats->rts_bad;
	stats->करोt11FCSErrorCount = mib_stats->fcs_bad;
	stats->करोt11RTSSuccessCount = mib_stats->rts_good;
	वापस 0;
पूर्ण

अटल u32 fill_chainmask(u32 cap, u32 new)
अणु
	u32 filled = 0;
	पूर्णांक i;

	क्रम (i = 0; cap && new; i++, cap >>= 1) अणु
		अगर (!(cap & BIT(0)))
			जारी;

		अगर (new & BIT(0))
			filled |= BIT(i);

		new >>= 1;
	पूर्ण

	वापस filled;
पूर्ण

अटल bool validate_antenna_mask(काष्ठा ath_hw *ah, u32 val)
अणु
	अगर (AR_SREV_9300_20_OR_LATER(ah))
		वापस true;

	चयन (val & 0x7) अणु
	हाल 0x1:
	हाल 0x3:
	हाल 0x7:
		वापस true;
	हाल 0x2:
		वापस (ah->caps.rx_chainmask == 1);
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक ath9k_set_antenna(काष्ठा ieee80211_hw *hw, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_hw *ah = sc->sc_ah;

	अगर (ah->caps.rx_chainmask != 1)
		rx_ant |= tx_ant;

	अगर (!validate_antenna_mask(ah, rx_ant) || !tx_ant)
		वापस -EINVAL;

	sc->ant_rx = rx_ant;
	sc->ant_tx = tx_ant;

	अगर (ah->caps.rx_chainmask == 1)
		वापस 0;

	/* AR9100 runs पूर्णांकo calibration issues अगर not all rx chains are enabled */
	अगर (AR_SREV_9100(ah))
		ah->rxchainmask = 0x7;
	अन्यथा
		ah->rxchainmask = fill_chainmask(ah->caps.rx_chainmask, rx_ant);

	ah->txchainmask = fill_chainmask(ah->caps.tx_chainmask, tx_ant);
	ath9k_cmn_reload_chainmask(ah);

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_get_antenna(काष्ठा ieee80211_hw *hw, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा ath_softc *sc = hw->priv;

	*tx_ant = sc->ant_tx;
	*rx_ant = sc->ant_rx;
	वापस 0;
पूर्ण

अटल व्योम ath9k_sw_scan_start(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				स्थिर u8 *mac_addr)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	set_bit(ATH_OP_SCANNING, &common->op_flags);
पूर्ण

अटल व्योम ath9k_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	clear_bit(ATH_OP_SCANNING, &common->op_flags);
पूर्ण

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT

अटल व्योम ath9k_cancel_pending_offchannel(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	अगर (sc->offchannel.roc_vअगर) अणु
		ath_dbg(common, CHAN_CTX,
			"%s: Aborting RoC\n", __func__);

		del_समयr_sync(&sc->offchannel.समयr);
		अगर (sc->offchannel.state >= ATH_OFFCHANNEL_ROC_START)
			ath_roc_complete(sc, ATH_ROC_COMPLETE_ABORT);
	पूर्ण

	अगर (test_bit(ATH_OP_SCANNING, &common->op_flags)) अणु
		ath_dbg(common, CHAN_CTX,
			"%s: Aborting HW scan\n", __func__);

		del_समयr_sync(&sc->offchannel.समयr);
		ath_scan_complete(sc, true);
	पूर्ण
पूर्ण

अटल पूर्णांक ath9k_hw_scan(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			 काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा cfg80211_scan_request *req = &hw_req->req;
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	पूर्णांक ret = 0;

	mutex_lock(&sc->mutex);

	अगर (WARN_ON(sc->offchannel.scan_req)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ath9k_ps_wakeup(sc);
	set_bit(ATH_OP_SCANNING, &common->op_flags);
	sc->offchannel.scan_vअगर = vअगर;
	sc->offchannel.scan_req = req;
	sc->offchannel.scan_idx = 0;

	ath_dbg(common, CHAN_CTX, "HW scan request received on vif: %pM\n",
		vअगर->addr);

	अगर (sc->offchannel.state == ATH_OFFCHANNEL_IDLE) अणु
		ath_dbg(common, CHAN_CTX, "Starting HW scan\n");
		ath_offchannel_next(sc);
	पूर्ण

out:
	mutex_unlock(&sc->mutex);

	वापस ret;
पूर्ण

अटल व्योम ath9k_cancel_hw_scan(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, CHAN_CTX, "Cancel HW scan on vif: %pM\n", vअगर->addr);

	mutex_lock(&sc->mutex);
	del_समयr_sync(&sc->offchannel.समयr);
	ath_scan_complete(sc, true);
	mutex_unlock(&sc->mutex);
पूर्ण

अटल पूर्णांक ath9k_reमुख्य_on_channel(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर,
				   काष्ठा ieee80211_channel *chan, पूर्णांक duration,
				   क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	पूर्णांक ret = 0;

	mutex_lock(&sc->mutex);

	अगर (WARN_ON(sc->offchannel.roc_vअगर)) अणु
		ret = -EBUSY;
		जाओ out;
	पूर्ण

	ath9k_ps_wakeup(sc);
	sc->offchannel.roc_vअगर = vअगर;
	sc->offchannel.roc_chan = chan;
	sc->offchannel.roc_duration = duration;

	ath_dbg(common, CHAN_CTX,
		"RoC request on vif: %pM, type: %d duration: %d\n",
		vअगर->addr, type, duration);

	अगर (sc->offchannel.state == ATH_OFFCHANNEL_IDLE) अणु
		ath_dbg(common, CHAN_CTX, "Starting RoC period\n");
		ath_offchannel_next(sc);
	पूर्ण

out:
	mutex_unlock(&sc->mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक ath9k_cancel_reमुख्य_on_channel(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	mutex_lock(&sc->mutex);

	ath_dbg(common, CHAN_CTX, "Cancel RoC\n");
	del_समयr_sync(&sc->offchannel.समयr);

	अगर (sc->offchannel.roc_vअगर) अणु
		अगर (sc->offchannel.state >= ATH_OFFCHANNEL_ROC_START)
			ath_roc_complete(sc, ATH_ROC_COMPLETE_CANCEL);
	पूर्ण

	mutex_unlock(&sc->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक ath9k_add_chanctx(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_chanctx_conf *conf)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_chanctx *ctx, **ptr;
	पूर्णांक pos;

	mutex_lock(&sc->mutex);

	ath_क्रम_each_chanctx(sc, ctx) अणु
		अगर (ctx->asचिन्हित)
			जारी;

		ptr = (व्योम *) conf->drv_priv;
		*ptr = ctx;
		ctx->asचिन्हित = true;
		pos = ctx - &sc->chanctx[0];
		ctx->hw_queue_base = pos * IEEE80211_NUM_ACS;

		ath_dbg(common, CHAN_CTX,
			"Add channel context: %d MHz\n",
			conf->def.chan->center_freq);

		ath_chanctx_set_channel(sc, ctx, &conf->def);

		mutex_unlock(&sc->mutex);
		वापस 0;
	पूर्ण

	mutex_unlock(&sc->mutex);
	वापस -ENOSPC;
पूर्ण


अटल व्योम ath9k_हटाओ_chanctx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_chanctx_conf *conf)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_chanctx *ctx = ath_chanctx_get(conf);

	mutex_lock(&sc->mutex);

	ath_dbg(common, CHAN_CTX,
		"Remove channel context: %d MHz\n",
		conf->def.chan->center_freq);

	ctx->asचिन्हित = false;
	ctx->hw_queue_base = 0;
	ath_chanctx_event(sc, शून्य, ATH_CHANCTX_EVENT_UNASSIGN);

	mutex_unlock(&sc->mutex);
पूर्ण

अटल व्योम ath9k_change_chanctx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_chanctx_conf *conf,
				 u32 changed)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_chanctx *ctx = ath_chanctx_get(conf);

	mutex_lock(&sc->mutex);
	ath_dbg(common, CHAN_CTX,
		"Change channel context: %d MHz\n",
		conf->def.chan->center_freq);
	ath_chanctx_set_channel(sc, ctx, &conf->def);
	mutex_unlock(&sc->mutex);
पूर्ण

अटल पूर्णांक ath9k_assign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				    काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा ieee80211_chanctx_conf *conf)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	काष्ठा ath_chanctx *ctx = ath_chanctx_get(conf);
	पूर्णांक i;

	ath9k_cancel_pending_offchannel(sc);

	mutex_lock(&sc->mutex);

	ath_dbg(common, CHAN_CTX,
		"Assign VIF (addr: %pM, type: %d, p2p: %d) to channel context: %d MHz\n",
		vअगर->addr, vअगर->type, vअगर->p2p,
		conf->def.chan->center_freq);

	avp->chanctx = ctx;
	ctx->nvअगरs_asचिन्हित++;
	list_add_tail(&avp->list, &ctx->vअगरs);
	ath9k_calculate_summary_state(sc, ctx);
	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++)
		vअगर->hw_queue[i] = ctx->hw_queue_base + i;

	mutex_unlock(&sc->mutex);

	वापस 0;
पूर्ण

अटल व्योम ath9k_unassign_vअगर_chanctx(काष्ठा ieee80211_hw *hw,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_chanctx_conf *conf)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	काष्ठा ath_chanctx *ctx = ath_chanctx_get(conf);
	पूर्णांक ac;

	ath9k_cancel_pending_offchannel(sc);

	mutex_lock(&sc->mutex);

	ath_dbg(common, CHAN_CTX,
		"Remove VIF (addr: %pM, type: %d, p2p: %d) from channel context: %d MHz\n",
		vअगर->addr, vअगर->type, vअगर->p2p,
		conf->def.chan->center_freq);

	avp->chanctx = शून्य;
	ctx->nvअगरs_asचिन्हित--;
	list_del(&avp->list);
	ath9k_calculate_summary_state(sc, ctx);
	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		vअगर->hw_queue[ac] = IEEE80211_INVAL_HW_QUEUE;

	mutex_unlock(&sc->mutex);
पूर्ण

अटल व्योम ath9k_mgd_prepare_tx(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर,
				 u16 duration)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_vअगर *avp = (काष्ठा ath_vअगर *) vअगर->drv_priv;
	काष्ठा ath_beacon_config *cur_conf;
	काष्ठा ath_chanctx *go_ctx;
	अचिन्हित दीर्घ समयout;
	bool changed = false;
	u32 beacon_पूर्णांक;

	अगर (!test_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags))
		वापस;

	अगर (!avp->chanctx)
		वापस;

	mutex_lock(&sc->mutex);

	spin_lock_bh(&sc->chan_lock);
	अगर (sc->next_chan || (sc->cur_chan != avp->chanctx))
		changed = true;
	spin_unlock_bh(&sc->chan_lock);

	अगर (!changed)
		जाओ out;

	ath9k_cancel_pending_offchannel(sc);

	go_ctx = ath_is_go_chanctx_present(sc);

	अगर (go_ctx) अणु
		/*
		 * Wait till the GO पूर्णांकerface माला_लो a chance
		 * to send out an NoA.
		 */
		spin_lock_bh(&sc->chan_lock);
		sc->sched.mgd_prepare_tx = true;
		cur_conf = &go_ctx->beacon;
		beacon_पूर्णांक = TU_TO_USEC(cur_conf->beacon_पूर्णांकerval);
		spin_unlock_bh(&sc->chan_lock);

		समयout = usecs_to_jअगरfies(beacon_पूर्णांक * 2);
		init_completion(&sc->go_beacon);

		mutex_unlock(&sc->mutex);

		अगर (रुको_क्रम_completion_समयout(&sc->go_beacon,
						समयout) == 0) अणु
			ath_dbg(common, CHAN_CTX,
				"Failed to send new NoA\n");

			spin_lock_bh(&sc->chan_lock);
			sc->sched.mgd_prepare_tx = false;
			spin_unlock_bh(&sc->chan_lock);
		पूर्ण

		mutex_lock(&sc->mutex);
	पूर्ण

	ath_dbg(common, CHAN_CTX,
		"%s: Set chanctx state to FORCE_ACTIVE for vif: %pM\n",
		__func__, vअगर->addr);

	spin_lock_bh(&sc->chan_lock);
	sc->next_chan = avp->chanctx;
	sc->sched.state = ATH_CHANCTX_STATE_FORCE_ACTIVE;
	spin_unlock_bh(&sc->chan_lock);

	ath_chanctx_set_next(sc, true);
out:
	mutex_unlock(&sc->mutex);
पूर्ण

व्योम ath9k_fill_chanctx_ops(व्योम)
अणु
	अगर (!ath9k_is_chanctx_enabled())
		वापस;

	ath9k_ops.hw_scan                  = ath9k_hw_scan;
	ath9k_ops.cancel_hw_scan           = ath9k_cancel_hw_scan;
	ath9k_ops.reमुख्य_on_channel        = ath9k_reमुख्य_on_channel;
	ath9k_ops.cancel_reमुख्य_on_channel = ath9k_cancel_reमुख्य_on_channel;
	ath9k_ops.add_chanctx              = ath9k_add_chanctx;
	ath9k_ops.हटाओ_chanctx           = ath9k_हटाओ_chanctx;
	ath9k_ops.change_chanctx           = ath9k_change_chanctx;
	ath9k_ops.assign_vअगर_chanctx       = ath9k_assign_vअगर_chanctx;
	ath9k_ops.unassign_vअगर_chanctx     = ath9k_unassign_vअगर_chanctx;
	ath9k_ops.mgd_prepare_tx           = ath9k_mgd_prepare_tx;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक ath9k_get_txघातer(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			     पूर्णांक *dbm)
अणु
	काष्ठा ath_softc *sc = hw->priv;
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;

	mutex_lock(&sc->mutex);
	अगर (avp->chanctx)
		*dbm = avp->chanctx->cur_txघातer;
	अन्यथा
		*dbm = sc->cur_chan->cur_txघातer;
	mutex_unlock(&sc->mutex);

	*dbm /= 2;

	वापस 0;
पूर्ण

काष्ठा ieee80211_ops ath9k_ops = अणु
	.tx 		    = ath9k_tx,
	.start 		    = ath9k_start,
	.stop 		    = ath9k_stop,
	.add_पूर्णांकerface 	    = ath9k_add_पूर्णांकerface,
	.change_पूर्णांकerface   = ath9k_change_पूर्णांकerface,
	.हटाओ_पूर्णांकerface   = ath9k_हटाओ_पूर्णांकerface,
	.config 	    = ath9k_config,
	.configure_filter   = ath9k_configure_filter,
	.sta_state          = ath9k_sta_state,
	.sta_notअगरy         = ath9k_sta_notअगरy,
	.conf_tx 	    = ath9k_conf_tx,
	.bss_info_changed   = ath9k_bss_info_changed,
	.set_key            = ath9k_set_key,
	.get_tsf 	    = ath9k_get_tsf,
	.set_tsf 	    = ath9k_set_tsf,
	.reset_tsf 	    = ath9k_reset_tsf,
	.ampdu_action       = ath9k_ampdu_action,
	.get_survey	    = ath9k_get_survey,
	.rfसमाप्त_poll        = ath9k_rfसमाप्त_poll_state,
	.set_coverage_class = ath9k_set_coverage_class,
	.flush		    = ath9k_flush,
	.tx_frames_pending  = ath9k_tx_frames_pending,
	.tx_last_beacon     = ath9k_tx_last_beacon,
	.release_buffered_frames = ath9k_release_buffered_frames,
	.get_stats	    = ath9k_get_stats,
	.set_antenna	    = ath9k_set_antenna,
	.get_antenna	    = ath9k_get_antenna,

#अगर_घोषित CONFIG_ATH9K_WOW
	.suspend	    = ath9k_suspend,
	.resume		    = ath9k_resume,
	.set_wakeup	    = ath9k_set_wakeup,
#पूर्ण_अगर

#अगर_घोषित CONFIG_ATH9K_DEBUGFS
	.get_et_sset_count  = ath9k_get_et_sset_count,
	.get_et_stats       = ath9k_get_et_stats,
	.get_et_strings     = ath9k_get_et_strings,
#पूर्ण_अगर

#अगर defined(CONFIG_MAC80211_DEBUGFS) && defined(CONFIG_ATH9K_STATION_STATISTICS)
	.sta_add_debugfs    = ath9k_sta_add_debugfs,
#पूर्ण_अगर
	.sw_scan_start	    = ath9k_sw_scan_start,
	.sw_scan_complete   = ath9k_sw_scan_complete,
	.get_txघातer        = ath9k_get_txघातer,
	.wake_tx_queue      = ath9k_wake_tx_queue,
पूर्ण;
