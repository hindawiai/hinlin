<शैली गुरु>
/*
 * Copyright (c) 2014 Qualcomm Atheros, Inc.
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

/* Set/change channels.  If the channel is really being changed, it's करोne
 * by reseting the chip.  To accomplish this we must first cleanup any pending
 * DMA, then restart stuff.
 */
अटल पूर्णांक ath_set_channel(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ieee80211_hw *hw = sc->hw;
	काष्ठा ath9k_channel *hchan;
	काष्ठा cfg80211_chan_def *chandef = &sc->cur_chan->chandef;
	काष्ठा ieee80211_channel *chan = chandef->chan;
	पूर्णांक pos = chan->hw_value;
	अचिन्हित दीर्घ flags;
	पूर्णांक old_pos = -1;
	पूर्णांक r;

	अगर (test_bit(ATH_OP_INVALID, &common->op_flags))
		वापस -EIO;

	अगर (ah->curchan)
		old_pos = ah->curchan - &ah->channels[0];

	ath_dbg(common, CONFIG, "Set channel: %d MHz width: %d\n",
		chan->center_freq, chandef->width);

	/* update survey stats क्रम the old channel beक्रमe चयनing */
	spin_lock_irqsave(&common->cc_lock, flags);
	ath_update_survey_stats(sc);
	spin_unlock_irqrestore(&common->cc_lock, flags);

	ath9k_cmn_get_channel(hw, ah, chandef);

	/* If the operating channel changes, change the survey in-use flags
	 * aदीर्घ with it.
	 * Reset the survey data क्रम the new channel, unless we're चयनing
	 * back to the operating channel from an off-channel operation.
	 */
	अगर (!sc->cur_chan->offchannel && sc->cur_survey != &sc->survey[pos]) अणु
		अगर (sc->cur_survey)
			sc->cur_survey->filled &= ~SURVEY_INFO_IN_USE;

		sc->cur_survey = &sc->survey[pos];

		स_रखो(sc->cur_survey, 0, माप(काष्ठा survey_info));
		sc->cur_survey->filled |= SURVEY_INFO_IN_USE;
	पूर्ण अन्यथा अगर (!(sc->survey[pos].filled & SURVEY_INFO_IN_USE)) अणु
		स_रखो(&sc->survey[pos], 0, माप(काष्ठा survey_info));
	पूर्ण

	hchan = &sc->sc_ah->channels[pos];
	r = ath_reset(sc, hchan);
	अगर (r)
		वापस r;

	/* The most recent snapshot of channel->noiseन्यूनमान क्रम the old
	 * channel is only available after the hardware reset. Copy it to
	 * the survey stats now.
	 */
	अगर (old_pos >= 0)
		ath_update_survey_nf(sc, old_pos);

	/* Enable radar pulse detection अगर on a DFS channel. Spectral
	 * scanning and radar detection can not be used concurrently.
	 */
	अगर (hw->conf.radar_enabled) अणु
		u32 rxfilter;

		rxfilter = ath9k_hw_getrxfilter(ah);
		rxfilter |= ATH9K_RX_FILTER_PHYRADAR |
				ATH9K_RX_FILTER_PHYERR;
		ath9k_hw_setrxfilter(ah, rxfilter);
		ath_dbg(common, DFS, "DFS enabled at freq %d\n",
			chan->center_freq);
	पूर्ण अन्यथा अणु
		/* perक्रमm spectral scan अगर requested. */
		अगर (test_bit(ATH_OP_SCANNING, &common->op_flags) &&
			sc->spec_priv.spectral_mode == SPECTRAL_CHANSCAN)
			ath9k_cmn_spectral_scan_trigger(common, &sc->spec_priv);
	पूर्ण

	वापस 0;
पूर्ण

व्योम ath_chanctx_init(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_chanctx *ctx;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *chan;
	पूर्णांक i, j;

	sband = &common->sbands[NL80211_BAND_2GHZ];
	अगर (!sband->n_channels)
		sband = &common->sbands[NL80211_BAND_5GHZ];

	chan = &sband->channels[0];
	क्रम (i = 0; i < ATH9K_NUM_CHANCTX; i++) अणु
		ctx = &sc->chanctx[i];
		cfg80211_chandef_create(&ctx->chandef, chan, NL80211_CHAN_HT20);
		INIT_LIST_HEAD(&ctx->vअगरs);
		ctx->txघातer = ATH_TXPOWER_MAX;
		ctx->flush_समयout = HZ / 5; /* 200ms */
		क्रम (j = 0; j < ARRAY_SIZE(ctx->acq); j++) अणु
			INIT_LIST_HEAD(&ctx->acq[j].acq_new);
			INIT_LIST_HEAD(&ctx->acq[j].acq_old);
			spin_lock_init(&ctx->acq[j].lock);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ath_chanctx_set_channel(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx,
			     काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	bool cur_chan;

	spin_lock_bh(&sc->chan_lock);
	अगर (chandef)
		स_नकल(&ctx->chandef, chandef, माप(*chandef));
	cur_chan = sc->cur_chan == ctx;
	spin_unlock_bh(&sc->chan_lock);

	अगर (!cur_chan) अणु
		ath_dbg(common, CHAN_CTX,
			"Current context differs from the new context\n");
		वापस;
	पूर्ण

	ath_set_channel(sc);
पूर्ण

#अगर_घोषित CONFIG_ATH9K_CHANNEL_CONTEXT

/*************/
/* Utilities */
/*************/

काष्ठा ath_chanctx* ath_is_go_chanctx_present(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_chanctx *ctx;
	काष्ठा ath_vअगर *avp;
	काष्ठा ieee80211_vअगर *vअगर;

	spin_lock_bh(&sc->chan_lock);

	ath_क्रम_each_chanctx(sc, ctx) अणु
		अगर (!ctx->active)
			जारी;

		list_क्रम_each_entry(avp, &ctx->vअगरs, list) अणु
			vअगर = avp->vअगर;

			अगर (ieee80211_vअगर_type_p2p(vअगर) == NL80211_IFTYPE_P2P_GO) अणु
				spin_unlock_bh(&sc->chan_lock);
				वापस ctx;
			पूर्ण
		पूर्ण
	पूर्ण

	spin_unlock_bh(&sc->chan_lock);
	वापस शून्य;
पूर्ण

/**********************************************************/
/* Functions to handle the channel context state machine. */
/**********************************************************/

अटल स्थिर अक्षर *offchannel_state_string(क्रमागत ath_offchannel_state state)
अणु
	चयन (state) अणु
		हाल_rtn_string(ATH_OFFCHANNEL_IDLE);
		हाल_rtn_string(ATH_OFFCHANNEL_PROBE_SEND);
		हाल_rtn_string(ATH_OFFCHANNEL_PROBE_WAIT);
		हाल_rtn_string(ATH_OFFCHANNEL_SUSPEND);
		हाल_rtn_string(ATH_OFFCHANNEL_ROC_START);
		हाल_rtn_string(ATH_OFFCHANNEL_ROC_WAIT);
		हाल_rtn_string(ATH_OFFCHANNEL_ROC_DONE);
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *chanctx_event_string(क्रमागत ath_chanctx_event ev)
अणु
	चयन (ev) अणु
		हाल_rtn_string(ATH_CHANCTX_EVENT_BEACON_PREPARE);
		हाल_rtn_string(ATH_CHANCTX_EVENT_BEACON_SENT);
		हाल_rtn_string(ATH_CHANCTX_EVENT_TSF_TIMER);
		हाल_rtn_string(ATH_CHANCTX_EVENT_BEACON_RECEIVED);
		हाल_rtn_string(ATH_CHANCTX_EVENT_AUTHORIZED);
		हाल_rtn_string(ATH_CHANCTX_EVENT_SWITCH);
		हाल_rtn_string(ATH_CHANCTX_EVENT_ASSIGN);
		हाल_rtn_string(ATH_CHANCTX_EVENT_UNASSIGN);
		हाल_rtn_string(ATH_CHANCTX_EVENT_CHANGE);
		हाल_rtn_string(ATH_CHANCTX_EVENT_ENABLE_MULTICHANNEL);
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *chanctx_state_string(क्रमागत ath_chanctx_state state)
अणु
	चयन (state) अणु
		हाल_rtn_string(ATH_CHANCTX_STATE_IDLE);
		हाल_rtn_string(ATH_CHANCTX_STATE_WAIT_FOR_BEACON);
		हाल_rtn_string(ATH_CHANCTX_STATE_WAIT_FOR_TIMER);
		हाल_rtn_string(ATH_CHANCTX_STATE_SWITCH);
		हाल_rtn_string(ATH_CHANCTX_STATE_FORCE_ACTIVE);
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण

अटल u32 chanctx_event_delta(काष्ठा ath_softc *sc)
अणु
	u64 ms;
	काष्ठा बारpec64 ts, *old;

	kसमय_get_raw_ts64(&ts);
	old = &sc->last_event_समय;
	ms = ts.tv_sec * 1000 + ts.tv_nsec / 1000000;
	ms -= old->tv_sec * 1000 + old->tv_nsec / 1000000;
	sc->last_event_समय = ts;

	वापस (u32)ms;
पूर्ण

व्योम ath_chanctx_check_active(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_chanctx *ictx;
	काष्ठा ath_vअगर *avp;
	bool active = false;
	u8 n_active = 0;

	अगर (!ctx)
		वापस;

	अगर (ctx == &sc->offchannel.chan) अणु
		spin_lock_bh(&sc->chan_lock);

		अगर (likely(sc->sched.channel_चयन_समय))
			ctx->flush_समयout =
				usecs_to_jअगरfies(sc->sched.channel_चयन_समय);
		अन्यथा
			ctx->flush_समयout =
				msecs_to_jअगरfies(10);

		spin_unlock_bh(&sc->chan_lock);

		/*
		 * There is no need to iterate over the
		 * active/asचिन्हित channel contexts अगर
		 * the current context is offchannel.
		 */
		वापस;
	पूर्ण

	ictx = ctx;

	list_क्रम_each_entry(avp, &ctx->vअगरs, list) अणु
		काष्ठा ieee80211_vअगर *vअगर = avp->vअगर;

		चयन (vअगर->type) अणु
		हाल NL80211_IFTYPE_P2P_CLIENT:
		हाल NL80211_IFTYPE_STATION:
			अगर (avp->assoc)
				active = true;
			अवरोध;
		शेष:
			active = true;
			अवरोध;
		पूर्ण
	पूर्ण
	ctx->active = active;

	ath_क्रम_each_chanctx(sc, ctx) अणु
		अगर (!ctx->asचिन्हित || list_empty(&ctx->vअगरs))
			जारी;
		n_active++;
	पूर्ण

	spin_lock_bh(&sc->chan_lock);

	अगर (n_active <= 1) अणु
		ictx->flush_समयout = HZ / 5;
		clear_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags);
		spin_unlock_bh(&sc->chan_lock);
		वापस;
	पूर्ण

	ictx->flush_समयout = usecs_to_jअगरfies(sc->sched.channel_चयन_समय);

	अगर (test_and_set_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags)) अणु
		spin_unlock_bh(&sc->chan_lock);
		वापस;
	पूर्ण

	spin_unlock_bh(&sc->chan_lock);

	अगर (ath9k_is_chanctx_enabled()) अणु
		ath_chanctx_event(sc, शून्य,
				  ATH_CHANCTX_EVENT_ENABLE_MULTICHANNEL);
	पूर्ण
पूर्ण

अटल काष्ठा ath_chanctx *
ath_chanctx_get_next(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx)
अणु
	पूर्णांक idx = ctx - &sc->chanctx[0];

	वापस &sc->chanctx[!idx];
पूर्ण

अटल व्योम ath_chanctx_adjust_tbtt_delta(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_chanctx *prev, *cur;
	काष्ठा बारpec64 ts;
	u32 cur_tsf, prev_tsf, beacon_पूर्णांक;
	s32 offset;

	beacon_पूर्णांक = TU_TO_USEC(sc->cur_chan->beacon.beacon_पूर्णांकerval);

	cur = sc->cur_chan;
	prev = ath_chanctx_get_next(sc, cur);

	अगर (!prev->चयन_after_beacon)
		वापस;

	kसमय_get_raw_ts64(&ts);
	cur_tsf = (u32) cur->tsf_val +
		  ath9k_hw_get_tsf_offset(&cur->tsf_ts, &ts);

	prev_tsf = prev->last_beacon - (u32) prev->tsf_val + cur_tsf;
	prev_tsf -= ath9k_hw_get_tsf_offset(&prev->tsf_ts, &ts);

	/* Adjust the TSF समय of the AP chanctx to keep its beacons
	 * at half beacon पूर्णांकerval offset relative to the STA chanctx.
	 */
	offset = cur_tsf - prev_tsf;

	/* Ignore stale data or spurious बारtamps */
	अगर (offset < 0 || offset > 3 * beacon_पूर्णांक)
		वापस;

	offset = beacon_पूर्णांक / 2 - (offset % beacon_पूर्णांक);
	prev->tsf_val += offset;
पूर्ण

/* Configure the TSF based hardware समयr क्रम a channel चयन.
 * Also set up backup software समयr, in हाल the gen समयr fails.
 * This could be caused by a hardware reset.
 */
अटल व्योम ath_chanctx_setup_समयr(काष्ठा ath_softc *sc, u32 tsf_समय)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_hw *ah = sc->sc_ah;
	अचिन्हित दीर्घ समयout;

	ath9k_hw_gen_समयr_start(ah, sc->p2p_ps_समयr, tsf_समय, 1000000);
	tsf_समय -= ath9k_hw_gettsf32(ah);
	समयout = msecs_to_jअगरfies(tsf_समय / 1000) + 1;
	mod_समयr(&sc->sched.समयr, jअगरfies + समयout);

	ath_dbg(common, CHAN_CTX,
		"Setup chanctx timer with timeout: %d (%d) ms\n",
		tsf_समय / 1000, jअगरfies_to_msecs(समयout));
पूर्ण

अटल व्योम ath_chanctx_handle_bmiss(काष्ठा ath_softc *sc,
				     काष्ठा ath_chanctx *ctx,
				     काष्ठा ath_vअगर *avp)
अणु
	/*
	 * Clear the extend_असलence flag अगर it had been
	 * set during the previous beacon transmission,
	 * since we need to revert to the normal NoA
	 * schedule.
	 */
	अगर (ctx->active && sc->sched.extend_असलence) अणु
		avp->noa_duration = 0;
		sc->sched.extend_असलence = false;
	पूर्ण

	/* If at least two consecutive beacons were missed on the STA
	 * chanctx, stay on the STA channel क्रम one extra beacon period,
	 * to resync the समयr properly.
	 */
	अगर (ctx->active && sc->sched.beacon_miss >= 2) अणु
		avp->noa_duration = 0;
		sc->sched.extend_असलence = true;
	पूर्ण
पूर्ण

अटल व्योम ath_chanctx_offchannel_noa(काष्ठा ath_softc *sc,
				       काष्ठा ath_chanctx *ctx,
				       काष्ठा ath_vअगर *avp,
				       u32 tsf_समय)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	avp->noa_index++;
	avp->offchannel_start = tsf_समय;
	avp->offchannel_duration = sc->sched.offchannel_duration;

	ath_dbg(common, CHAN_CTX,
		"offchannel noa_duration: %d, noa_start: %u, noa_index: %d\n",
		avp->offchannel_duration,
		avp->offchannel_start,
		avp->noa_index);

	/*
	 * When multiple contexts are active, the NoA
	 * has to be recalculated and advertised after
	 * an offchannel operation.
	 */
	अगर (ctx->active && avp->noa_duration)
		avp->noa_duration = 0;
पूर्ण

अटल व्योम ath_chanctx_set_periodic_noa(काष्ठा ath_softc *sc,
					 काष्ठा ath_vअगर *avp,
					 काष्ठा ath_beacon_config *cur_conf,
					 u32 tsf_समय,
					 u32 beacon_पूर्णांक)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	avp->noa_index++;
	avp->noa_start = tsf_समय;

	अगर (sc->sched.extend_असलence)
		avp->noa_duration = (3 * beacon_पूर्णांक / 2) +
			sc->sched.channel_चयन_समय;
	अन्यथा
		avp->noa_duration =
			TU_TO_USEC(cur_conf->beacon_पूर्णांकerval) / 2 +
			sc->sched.channel_चयन_समय;

	अगर (test_bit(ATH_OP_SCANNING, &common->op_flags) ||
	    sc->sched.extend_असलence)
		avp->periodic_noa = false;
	अन्यथा
		avp->periodic_noa = true;

	ath_dbg(common, CHAN_CTX,
		"noa_duration: %d, noa_start: %u, noa_index: %d, periodic: %d\n",
		avp->noa_duration,
		avp->noa_start,
		avp->noa_index,
		avp->periodic_noa);
पूर्ण

अटल व्योम ath_chanctx_set_oneshot_noa(काष्ठा ath_softc *sc,
					काष्ठा ath_vअगर *avp,
					u32 tsf_समय,
					u32 duration)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	avp->noa_index++;
	avp->noa_start = tsf_समय;
	avp->periodic_noa = false;
	avp->oneshot_noa = true;
	avp->noa_duration = duration + sc->sched.channel_चयन_समय;

	ath_dbg(common, CHAN_CTX,
		"oneshot noa_duration: %d, noa_start: %u, noa_index: %d, periodic: %d\n",
		avp->noa_duration,
		avp->noa_start,
		avp->noa_index,
		avp->periodic_noa);
पूर्ण

व्योम ath_chanctx_event(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर,
		       क्रमागत ath_chanctx_event ev)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	काष्ठा ath_common *common = ath9k_hw_common(ah);
	काष्ठा ath_beacon_config *cur_conf;
	काष्ठा ath_vअगर *avp = शून्य;
	काष्ठा ath_chanctx *ctx;
	u32 tsf_समय;
	u32 beacon_पूर्णांक;

	अगर (vअगर)
		avp = (काष्ठा ath_vअगर *) vअगर->drv_priv;

	spin_lock_bh(&sc->chan_lock);

	ath_dbg(common, CHAN_CTX, "cur_chan: %d MHz, event: %s, state: %s, delta: %u ms\n",
		sc->cur_chan->chandef.center_freq1,
		chanctx_event_string(ev),
		chanctx_state_string(sc->sched.state),
		chanctx_event_delta(sc));

	चयन (ev) अणु
	हाल ATH_CHANCTX_EVENT_BEACON_PREPARE:
		अगर (avp->offchannel_duration)
			avp->offchannel_duration = 0;

		अगर (avp->oneshot_noa) अणु
			avp->noa_duration = 0;
			avp->oneshot_noa = false;

			ath_dbg(common, CHAN_CTX,
				"Clearing oneshot NoA\n");
		पूर्ण

		अगर (avp->chanctx != sc->cur_chan) अणु
			ath_dbg(common, CHAN_CTX,
				"Contexts differ, not preparing beacon\n");
			अवरोध;
		पूर्ण

		अगर (sc->sched.offchannel_pending && !sc->sched.रुको_चयन) अणु
			sc->sched.offchannel_pending = false;
			sc->next_chan = &sc->offchannel.chan;
			sc->sched.state = ATH_CHANCTX_STATE_WAIT_FOR_BEACON;
			ath_dbg(common, CHAN_CTX,
				"Setting offchannel_pending to false\n");
		पूर्ण

		ctx = ath_chanctx_get_next(sc, sc->cur_chan);
		अगर (ctx->active && sc->sched.state == ATH_CHANCTX_STATE_IDLE) अणु
			sc->next_chan = ctx;
			sc->sched.state = ATH_CHANCTX_STATE_WAIT_FOR_BEACON;
			ath_dbg(common, CHAN_CTX,
				"Set next context, move chanctx state to WAIT_FOR_BEACON\n");
		पूर्ण

		/* अगर the समयr missed its winकरोw, use the next पूर्णांकerval */
		अगर (sc->sched.state == ATH_CHANCTX_STATE_WAIT_FOR_TIMER) अणु
			sc->sched.state = ATH_CHANCTX_STATE_WAIT_FOR_BEACON;
			ath_dbg(common, CHAN_CTX,
				"Move chanctx state from WAIT_FOR_TIMER to WAIT_FOR_BEACON\n");
		पूर्ण

		अगर (sc->sched.mgd_prepare_tx)
			sc->sched.state = ATH_CHANCTX_STATE_WAIT_FOR_BEACON;

		/*
		 * When a context becomes inactive, क्रम example,
		 * disassociation of a station context, the NoA
		 * attribute needs to be हटाओd from subsequent
		 * beacons.
		 */
		अगर (!ctx->active && avp->noa_duration &&
		    sc->sched.state != ATH_CHANCTX_STATE_WAIT_FOR_BEACON) अणु
			avp->noa_duration = 0;
			avp->periodic_noa = false;

			ath_dbg(common, CHAN_CTX,
				"Clearing NoA schedule\n");
		पूर्ण

		अगर (sc->sched.state != ATH_CHANCTX_STATE_WAIT_FOR_BEACON)
			अवरोध;

		ath_dbg(common, CHAN_CTX, "Preparing beacon for vif: %pM\n", vअगर->addr);

		sc->sched.beacon_pending = true;
		sc->sched.next_tbtt = REG_READ(ah, AR_NEXT_TBTT_TIMER);

		cur_conf = &sc->cur_chan->beacon;
		beacon_पूर्णांक = TU_TO_USEC(cur_conf->beacon_पूर्णांकerval);

		/* defer channel चयन by a quarter beacon पूर्णांकerval */
		tsf_समय = sc->sched.next_tbtt + beacon_पूर्णांक / 4;
		sc->sched.चयन_start_समय = tsf_समय;
		sc->cur_chan->last_beacon = sc->sched.next_tbtt;

		/*
		 * If an offchannel चयन is scheduled to happen after
		 * a beacon transmission, update the NoA with one-shot
		 * values and increment the index.
		 */
		अगर (sc->next_chan == &sc->offchannel.chan) अणु
			ath_chanctx_offchannel_noa(sc, ctx, avp, tsf_समय);
			अवरोध;
		पूर्ण

		ath_chanctx_handle_bmiss(sc, ctx, avp);

		/*
		 * If a mgd_prepare_tx() has been called by mac80211,
		 * a one-shot NoA needs to be sent. This can happen
		 * with one or more active channel contexts - in both
		 * हालs, a new NoA schedule has to be advertised.
		 */
		अगर (sc->sched.mgd_prepare_tx) अणु
			ath_chanctx_set_oneshot_noa(sc, avp, tsf_समय,
						    jअगरfies_to_usecs(HZ / 5));
			अवरोध;
		पूर्ण

		/* Prevent wrap-around issues */
		अगर (avp->noa_duration && tsf_समय - avp->noa_start > BIT(30))
			avp->noa_duration = 0;

		/*
		 * If multiple contexts are active, start periodic
		 * NoA and increment the index क्रम the first
		 * announcement.
		 */
		अगर (ctx->active &&
		    (!avp->noa_duration || sc->sched.क्रमce_noa_update))
			ath_chanctx_set_periodic_noa(sc, avp, cur_conf,
						     tsf_समय, beacon_पूर्णांक);

		अगर (ctx->active && sc->sched.क्रमce_noa_update)
			sc->sched.क्रमce_noa_update = false;

		अवरोध;
	हाल ATH_CHANCTX_EVENT_BEACON_SENT:
		अगर (!sc->sched.beacon_pending) अणु
			ath_dbg(common, CHAN_CTX,
				"No pending beacon\n");
			अवरोध;
		पूर्ण

		sc->sched.beacon_pending = false;

		अगर (sc->sched.mgd_prepare_tx) अणु
			sc->sched.mgd_prepare_tx = false;
			complete(&sc->go_beacon);
			ath_dbg(common, CHAN_CTX,
				"Beacon sent, complete go_beacon\n");
			अवरोध;
		पूर्ण

		अगर (sc->sched.state != ATH_CHANCTX_STATE_WAIT_FOR_BEACON)
			अवरोध;

		ath_dbg(common, CHAN_CTX,
			"Move chanctx state to WAIT_FOR_TIMER\n");

		sc->sched.state = ATH_CHANCTX_STATE_WAIT_FOR_TIMER;
		ath_chanctx_setup_समयr(sc, sc->sched.चयन_start_समय);
		अवरोध;
	हाल ATH_CHANCTX_EVENT_TSF_TIMER:
		अगर (sc->sched.state != ATH_CHANCTX_STATE_WAIT_FOR_TIMER)
			अवरोध;

		अगर (!sc->cur_chan->चयन_after_beacon &&
		    sc->sched.beacon_pending)
			sc->sched.beacon_miss++;

		ath_dbg(common, CHAN_CTX,
			"Move chanctx state to SWITCH\n");

		sc->sched.state = ATH_CHANCTX_STATE_SWITCH;
		ieee80211_queue_work(sc->hw, &sc->chanctx_work);
		अवरोध;
	हाल ATH_CHANCTX_EVENT_BEACON_RECEIVED:
		अगर (!test_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags) ||
		    sc->cur_chan == &sc->offchannel.chan)
			अवरोध;

		sc->sched.beacon_pending = false;
		sc->sched.beacon_miss = 0;

		अगर (sc->sched.state == ATH_CHANCTX_STATE_FORCE_ACTIVE ||
		    !sc->sched.beacon_adjust ||
		    !sc->cur_chan->tsf_val)
			अवरोध;

		ath_chanctx_adjust_tbtt_delta(sc);

		/* TSF समय might have been updated by the incoming beacon,
		 * need update the channel चयन समयr to reflect the change.
		 */
		tsf_समय = sc->sched.चयन_start_समय;
		tsf_समय -= (u32) sc->cur_chan->tsf_val +
			ath9k_hw_get_tsf_offset(&sc->cur_chan->tsf_ts, शून्य);
		tsf_समय += ath9k_hw_gettsf32(ah);

		sc->sched.beacon_adjust = false;
		ath_chanctx_setup_समयr(sc, tsf_समय);
		अवरोध;
	हाल ATH_CHANCTX_EVENT_AUTHORIZED:
		अगर (sc->sched.state != ATH_CHANCTX_STATE_FORCE_ACTIVE ||
		    avp->chanctx != sc->cur_chan)
			अवरोध;

		ath_dbg(common, CHAN_CTX,
			"Move chanctx state from FORCE_ACTIVE to IDLE\n");

		sc->sched.state = ATH_CHANCTX_STATE_IDLE;
		fallthrough;
	हाल ATH_CHANCTX_EVENT_SWITCH:
		अगर (!test_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags) ||
		    sc->sched.state == ATH_CHANCTX_STATE_FORCE_ACTIVE ||
		    sc->cur_chan->चयन_after_beacon ||
		    sc->cur_chan == &sc->offchannel.chan)
			अवरोध;

		/* If this is a station chanctx, stay active क्रम a half
		 * beacon period (minus channel चयन समय)
		 */
		sc->next_chan = ath_chanctx_get_next(sc, sc->cur_chan);
		cur_conf = &sc->cur_chan->beacon;

		ath_dbg(common, CHAN_CTX,
			"Move chanctx state to WAIT_FOR_TIMER (event SWITCH)\n");

		sc->sched.state = ATH_CHANCTX_STATE_WAIT_FOR_TIMER;
		sc->sched.रुको_चयन = false;

		tsf_समय = TU_TO_USEC(cur_conf->beacon_पूर्णांकerval) / 2;

		अगर (sc->sched.extend_असलence) अणु
			sc->sched.beacon_miss = 0;
			tsf_समय *= 3;
		पूर्ण

		tsf_समय -= sc->sched.channel_चयन_समय;
		tsf_समय += ath9k_hw_gettsf32(sc->sc_ah);
		sc->sched.चयन_start_समय = tsf_समय;

		ath_chanctx_setup_समयr(sc, tsf_समय);
		sc->sched.beacon_pending = true;
		sc->sched.beacon_adjust = true;
		अवरोध;
	हाल ATH_CHANCTX_EVENT_ENABLE_MULTICHANNEL:
		अगर (sc->cur_chan == &sc->offchannel.chan ||
		    sc->cur_chan->चयन_after_beacon)
			अवरोध;

		sc->next_chan = ath_chanctx_get_next(sc, sc->cur_chan);
		ieee80211_queue_work(sc->hw, &sc->chanctx_work);
		अवरोध;
	हाल ATH_CHANCTX_EVENT_UNASSIGN:
		अगर (sc->cur_chan->asचिन्हित) अणु
			अगर (sc->next_chan && !sc->next_chan->asचिन्हित &&
			    sc->next_chan != &sc->offchannel.chan)
				sc->sched.state = ATH_CHANCTX_STATE_IDLE;
			अवरोध;
		पूर्ण

		ctx = ath_chanctx_get_next(sc, sc->cur_chan);
		sc->sched.state = ATH_CHANCTX_STATE_IDLE;
		अगर (!ctx->asचिन्हित)
			अवरोध;

		sc->next_chan = ctx;
		ieee80211_queue_work(sc->hw, &sc->chanctx_work);
		अवरोध;
	हाल ATH_CHANCTX_EVENT_ASSIGN:
		अवरोध;
	हाल ATH_CHANCTX_EVENT_CHANGE:
		अवरोध;
	पूर्ण

	spin_unlock_bh(&sc->chan_lock);
पूर्ण

व्योम ath_chanctx_beacon_sent_ev(काष्ठा ath_softc *sc,
				क्रमागत ath_chanctx_event ev)
अणु
	अगर (sc->sched.beacon_pending)
		ath_chanctx_event(sc, शून्य, ev);
पूर्ण

व्योम ath_chanctx_beacon_recv_ev(काष्ठा ath_softc *sc,
				क्रमागत ath_chanctx_event ev)
अणु
	ath_chanctx_event(sc, शून्य, ev);
पूर्ण

अटल पूर्णांक ath_scan_channel_duration(काष्ठा ath_softc *sc,
				     काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा cfg80211_scan_request *req = sc->offchannel.scan_req;

	अगर (!req->n_ssids || (chan->flags & IEEE80211_CHAN_NO_IR))
		वापस (HZ / 9); /* ~110 ms */

	वापस (HZ / 16); /* ~60 ms */
पूर्ण

अटल व्योम ath_chanctx_चयन(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx,
			       काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	spin_lock_bh(&sc->chan_lock);

	अगर (test_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags) &&
	    (sc->cur_chan != ctx) && (ctx == &sc->offchannel.chan)) अणु
		अगर (chandef)
			ctx->chandef = *chandef;

		sc->sched.offchannel_pending = true;
		sc->sched.रुको_चयन = true;
		sc->sched.offchannel_duration =
			jअगरfies_to_usecs(sc->offchannel.duration) +
			sc->sched.channel_चयन_समय;

		spin_unlock_bh(&sc->chan_lock);
		ath_dbg(common, CHAN_CTX,
			"Set offchannel_pending to true\n");
		वापस;
	पूर्ण

	sc->next_chan = ctx;
	अगर (chandef) अणु
		ctx->chandef = *chandef;
		ath_dbg(common, CHAN_CTX,
			"Assigned next_chan to %d MHz\n", chandef->center_freq1);
	पूर्ण

	अगर (sc->next_chan == &sc->offchannel.chan) अणु
		sc->sched.offchannel_duration =
			jअगरfies_to_usecs(sc->offchannel.duration) +
			sc->sched.channel_चयन_समय;

		अगर (chandef) अणु
			ath_dbg(common, CHAN_CTX,
				"Offchannel duration for chan %d MHz : %u\n",
				chandef->center_freq1,
				sc->sched.offchannel_duration);
		पूर्ण
	पूर्ण
	spin_unlock_bh(&sc->chan_lock);
	ieee80211_queue_work(sc->hw, &sc->chanctx_work);
पूर्ण

अटल व्योम ath_chanctx_offchan_चयन(काष्ठा ath_softc *sc,
				       काष्ठा ieee80211_channel *chan)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा cfg80211_chan_def chandef;

	cfg80211_chandef_create(&chandef, chan, NL80211_CHAN_NO_HT);
	ath_dbg(common, CHAN_CTX,
		"Channel definition created: %d MHz\n", chandef.center_freq1);

	ath_chanctx_चयन(sc, &sc->offchannel.chan, &chandef);
पूर्ण

अटल काष्ठा ath_chanctx *ath_chanctx_get_oper_chan(काष्ठा ath_softc *sc,
						     bool active)
अणु
	काष्ठा ath_chanctx *ctx;

	ath_क्रम_each_chanctx(sc, ctx) अणु
		अगर (!ctx->asचिन्हित || list_empty(&ctx->vअगरs))
			जारी;
		अगर (active && !ctx->active)
			जारी;

		अगर (ctx->चयन_after_beacon)
			वापस ctx;
	पूर्ण

	वापस &sc->chanctx[0];
पूर्ण

अटल व्योम
ath_scan_next_channel(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा cfg80211_scan_request *req = sc->offchannel.scan_req;
	काष्ठा ieee80211_channel *chan;

	अगर (sc->offchannel.scan_idx >= req->n_channels) अणु
		ath_dbg(common, CHAN_CTX,
			"Moving offchannel state to ATH_OFFCHANNEL_IDLE, "
			"scan_idx: %d, n_channels: %d\n",
			sc->offchannel.scan_idx,
			req->n_channels);

		sc->offchannel.state = ATH_OFFCHANNEL_IDLE;
		ath_chanctx_चयन(sc, ath_chanctx_get_oper_chan(sc, false),
				   शून्य);
		वापस;
	पूर्ण

	ath_dbg(common, CHAN_CTX,
		"Moving offchannel state to ATH_OFFCHANNEL_PROBE_SEND, scan_idx: %d\n",
		sc->offchannel.scan_idx);

	chan = req->channels[sc->offchannel.scan_idx++];
	sc->offchannel.duration = ath_scan_channel_duration(sc, chan);
	sc->offchannel.state = ATH_OFFCHANNEL_PROBE_SEND;

	ath_chanctx_offchan_चयन(sc, chan);
पूर्ण

व्योम ath_offchannel_next(काष्ठा ath_softc *sc)
अणु
	काष्ठा ieee80211_vअगर *vअगर;

	अगर (sc->offchannel.scan_req) अणु
		vअगर = sc->offchannel.scan_vअगर;
		sc->offchannel.chan.txघातer = vअगर->bss_conf.txघातer;
		ath_scan_next_channel(sc);
	पूर्ण अन्यथा अगर (sc->offchannel.roc_vअगर) अणु
		vअगर = sc->offchannel.roc_vअगर;
		sc->offchannel.chan.txघातer = vअगर->bss_conf.txघातer;
		sc->offchannel.duration =
			msecs_to_jअगरfies(sc->offchannel.roc_duration);
		sc->offchannel.state = ATH_OFFCHANNEL_ROC_START;
		ath_chanctx_offchan_चयन(sc, sc->offchannel.roc_chan);
	पूर्ण अन्यथा अणु
		spin_lock_bh(&sc->chan_lock);
		sc->sched.offchannel_pending = false;
		sc->sched.रुको_चयन = false;
		spin_unlock_bh(&sc->chan_lock);

		ath_chanctx_चयन(sc, ath_chanctx_get_oper_chan(sc, false),
				   शून्य);
		sc->offchannel.state = ATH_OFFCHANNEL_IDLE;
		अगर (sc->ps_idle)
			ath_cancel_work(sc);
	पूर्ण
पूर्ण

व्योम ath_roc_complete(काष्ठा ath_softc *sc, क्रमागत ath_roc_complete_reason reason)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	sc->offchannel.roc_vअगर = शून्य;
	sc->offchannel.roc_chan = शून्य;

	चयन (reason) अणु
	हाल ATH_ROC_COMPLETE_ABORT:
		ath_dbg(common, CHAN_CTX, "RoC aborted\n");
		ieee80211_reमुख्य_on_channel_expired(sc->hw);
		अवरोध;
	हाल ATH_ROC_COMPLETE_EXPIRE:
		ath_dbg(common, CHAN_CTX, "RoC expired\n");
		ieee80211_reमुख्य_on_channel_expired(sc->hw);
		अवरोध;
	हाल ATH_ROC_COMPLETE_CANCEL:
		ath_dbg(common, CHAN_CTX, "RoC canceled\n");
		अवरोध;
	पूर्ण

	ath_offchannel_next(sc);
	ath9k_ps_restore(sc);
पूर्ण

व्योम ath_scan_complete(काष्ठा ath_softc *sc, bool पात)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा cfg80211_scan_info info = अणु
		.पातed = पात,
	पूर्ण;

	अगर (पात)
		ath_dbg(common, CHAN_CTX, "HW scan aborted\n");
	अन्यथा
		ath_dbg(common, CHAN_CTX, "HW scan complete\n");

	sc->offchannel.scan_req = शून्य;
	sc->offchannel.scan_vअगर = शून्य;
	sc->offchannel.state = ATH_OFFCHANNEL_IDLE;
	ieee80211_scan_completed(sc->hw, &info);
	clear_bit(ATH_OP_SCANNING, &common->op_flags);
	spin_lock_bh(&sc->chan_lock);
	अगर (test_bit(ATH_OP_MULTI_CHANNEL, &common->op_flags))
		sc->sched.क्रमce_noa_update = true;
	spin_unlock_bh(&sc->chan_lock);
	ath_offchannel_next(sc);
	ath9k_ps_restore(sc);
पूर्ण

अटल व्योम ath_scan_send_probe(काष्ठा ath_softc *sc,
				काष्ठा cfg80211_ssid *ssid)
अणु
	काष्ठा cfg80211_scan_request *req = sc->offchannel.scan_req;
	काष्ठा ieee80211_vअगर *vअगर = sc->offchannel.scan_vअगर;
	काष्ठा ath_tx_control txctl = अणुपूर्ण;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_tx_info *info;
	पूर्णांक band = sc->offchannel.chan.chandef.chan->band;

	skb = ieee80211_probereq_get(sc->hw, vअगर->addr,
			ssid->ssid, ssid->ssid_len, req->ie_len);
	अगर (!skb)
		वापस;

	info = IEEE80211_SKB_CB(skb);
	अगर (req->no_cck)
		info->flags |= IEEE80211_TX_CTL_NO_CCK_RATE;

	अगर (req->ie_len)
		skb_put_data(skb, req->ie, req->ie_len);

	skb_set_queue_mapping(skb, IEEE80211_AC_VO);

	अगर (!ieee80211_tx_prepare_skb(sc->hw, vअगर, skb, band, शून्य))
		जाओ error;

	txctl.txq = sc->tx.txq_map[IEEE80211_AC_VO];
	अगर (ath_tx_start(sc->hw, skb, &txctl))
		जाओ error;

	वापस;

error:
	ieee80211_मुक्त_txskb(sc->hw, skb);
पूर्ण

अटल व्योम ath_scan_channel_start(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा cfg80211_scan_request *req = sc->offchannel.scan_req;
	पूर्णांक i;

	अगर (!(sc->cur_chan->chandef.chan->flags & IEEE80211_CHAN_NO_IR) &&
	    req->n_ssids) अणु
		क्रम (i = 0; i < req->n_ssids; i++)
			ath_scan_send_probe(sc, &req->ssids[i]);

	पूर्ण

	ath_dbg(common, CHAN_CTX,
		"Moving offchannel state to ATH_OFFCHANNEL_PROBE_WAIT\n");

	sc->offchannel.state = ATH_OFFCHANNEL_PROBE_WAIT;
	mod_समयr(&sc->offchannel.समयr, jअगरfies + sc->offchannel.duration);
पूर्ण

अटल व्योम ath_chanctx_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ath_softc *sc = from_समयr(sc, t, sched.समयr);
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, CHAN_CTX,
		"Channel context timer invoked\n");

	ath_chanctx_event(sc, शून्य, ATH_CHANCTX_EVENT_TSF_TIMER);
पूर्ण

अटल व्योम ath_offchannel_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ath_softc *sc = from_समयr(sc, t, offchannel.समयr);
	काष्ठा ath_chanctx *ctx;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, CHAN_CTX, "%s: offchannel state: %s\n",
		__func__, offchannel_state_string(sc->offchannel.state));

	चयन (sc->offchannel.state) अणु
	हाल ATH_OFFCHANNEL_PROBE_WAIT:
		अगर (!sc->offchannel.scan_req)
			वापस;

		/* get first active channel context */
		ctx = ath_chanctx_get_oper_chan(sc, true);
		अगर (ctx->active) अणु
			ath_dbg(common, CHAN_CTX,
				"Switch to oper/active context, "
				"move offchannel state to ATH_OFFCHANNEL_SUSPEND\n");

			sc->offchannel.state = ATH_OFFCHANNEL_SUSPEND;
			ath_chanctx_चयन(sc, ctx, शून्य);
			mod_समयr(&sc->offchannel.समयr, jअगरfies + HZ / 10);
			अवरोध;
		पूर्ण
		fallthrough;
	हाल ATH_OFFCHANNEL_SUSPEND:
		अगर (!sc->offchannel.scan_req)
			वापस;

		ath_scan_next_channel(sc);
		अवरोध;
	हाल ATH_OFFCHANNEL_ROC_START:
	हाल ATH_OFFCHANNEL_ROC_WAIT:
		sc->offchannel.state = ATH_OFFCHANNEL_ROC_DONE;
		ath_roc_complete(sc, ATH_ROC_COMPLETE_EXPIRE);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल bool
ath_chanctx_send_vअगर_ps_frame(काष्ठा ath_softc *sc, काष्ठा ath_vअगर *avp,
			      bool घातersave)
अणु
	काष्ठा ieee80211_vअगर *vअगर = avp->vअगर;
	काष्ठा ieee80211_sta *sta = शून्य;
	काष्ठा ieee80211_hdr_3addr *nullfunc;
	काष्ठा ath_tx_control txctl;
	काष्ठा sk_buff *skb;
	पूर्णांक band = sc->cur_chan->chandef.chan->band;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (!avp->assoc)
			वापस false;

		skb = ieee80211_nullfunc_get(sc->hw, vअगर, false);
		अगर (!skb)
			वापस false;

		nullfunc = (काष्ठा ieee80211_hdr_3addr *) skb->data;
		अगर (घातersave)
			nullfunc->frame_control |=
				cpu_to_le16(IEEE80211_FCTL_PM);

		skb->priority = 7;
		skb_set_queue_mapping(skb, IEEE80211_AC_VO);
		अगर (!ieee80211_tx_prepare_skb(sc->hw, vअगर, skb, band, &sta)) अणु
			dev_kमुक्त_skb_any(skb);
			वापस false;
		पूर्ण
		अवरोध;
	शेष:
		वापस false;
	पूर्ण

	स_रखो(&txctl, 0, माप(txctl));
	txctl.txq = sc->tx.txq_map[IEEE80211_AC_VO];
	txctl.sta = sta;
	अगर (ath_tx_start(sc->hw, skb, &txctl)) अणु
		ieee80211_मुक्त_txskb(sc->hw, skb);
		वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल bool
ath_chanctx_send_ps_frame(काष्ठा ath_softc *sc, bool घातersave)
अणु
	काष्ठा ath_vअगर *avp;
	bool sent = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry(avp, &sc->cur_chan->vअगरs, list) अणु
		अगर (ath_chanctx_send_vअगर_ps_frame(sc, avp, घातersave))
			sent = true;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस sent;
पूर्ण

अटल bool ath_chanctx_defer_चयन(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	अगर (sc->cur_chan == &sc->offchannel.chan)
		वापस false;

	चयन (sc->sched.state) अणु
	हाल ATH_CHANCTX_STATE_SWITCH:
		वापस false;
	हाल ATH_CHANCTX_STATE_IDLE:
		अगर (!sc->cur_chan->चयन_after_beacon)
			वापस false;

		ath_dbg(common, CHAN_CTX,
			"Defer switch, set chanctx state to WAIT_FOR_BEACON\n");

		sc->sched.state = ATH_CHANCTX_STATE_WAIT_FOR_BEACON;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण

अटल व्योम ath_offchannel_channel_change(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);

	ath_dbg(common, CHAN_CTX, "%s: offchannel state: %s\n",
		__func__, offchannel_state_string(sc->offchannel.state));

	चयन (sc->offchannel.state) अणु
	हाल ATH_OFFCHANNEL_PROBE_SEND:
		अगर (!sc->offchannel.scan_req)
			वापस;

		अगर (sc->cur_chan->chandef.chan !=
		    sc->offchannel.chan.chandef.chan)
			वापस;

		ath_scan_channel_start(sc);
		अवरोध;
	हाल ATH_OFFCHANNEL_IDLE:
		अगर (!sc->offchannel.scan_req)
			वापस;

		ath_scan_complete(sc, false);
		अवरोध;
	हाल ATH_OFFCHANNEL_ROC_START:
		अगर (sc->cur_chan != &sc->offchannel.chan)
			अवरोध;

		sc->offchannel.state = ATH_OFFCHANNEL_ROC_WAIT;
		mod_समयr(&sc->offchannel.समयr,
			  jअगरfies + sc->offchannel.duration);
		ieee80211_पढ़ोy_on_channel(sc->hw);
		अवरोध;
	हाल ATH_OFFCHANNEL_ROC_DONE:
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

व्योम ath_chanctx_set_next(काष्ठा ath_softc *sc, bool क्रमce)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_chanctx *old_ctx;
	काष्ठा बारpec64 ts;
	bool measure_समय = false;
	bool send_ps = false;
	bool queues_stopped = false;

	spin_lock_bh(&sc->chan_lock);
	अगर (!sc->next_chan) अणु
		spin_unlock_bh(&sc->chan_lock);
		वापस;
	पूर्ण

	अगर (!क्रमce && ath_chanctx_defer_चयन(sc)) अणु
		spin_unlock_bh(&sc->chan_lock);
		वापस;
	पूर्ण

	ath_dbg(common, CHAN_CTX,
		"%s: current: %d MHz, next: %d MHz\n",
		__func__,
		sc->cur_chan->chandef.center_freq1,
		sc->next_chan->chandef.center_freq1);

	अगर (sc->cur_chan != sc->next_chan) अणु
		ath_dbg(common, CHAN_CTX,
			"Stopping current chanctx: %d\n",
			sc->cur_chan->chandef.center_freq1);
		sc->cur_chan->stopped = true;
		spin_unlock_bh(&sc->chan_lock);

		अगर (sc->next_chan == &sc->offchannel.chan) अणु
			kसमय_get_raw_ts64(&ts);
			measure_समय = true;
		पूर्ण

		ath9k_chanctx_stop_queues(sc, sc->cur_chan);
		queues_stopped = true;

		__ath9k_flush(sc->hw, ~0, true, false, false);

		अगर (ath_chanctx_send_ps_frame(sc, true))
			__ath9k_flush(sc->hw, BIT(IEEE80211_AC_VO),
				      false, false, false);

		send_ps = true;
		spin_lock_bh(&sc->chan_lock);

		अगर (sc->cur_chan != &sc->offchannel.chan) अणु
			kसमय_get_raw_ts64(&sc->cur_chan->tsf_ts);
			sc->cur_chan->tsf_val = ath9k_hw_gettsf64(sc->sc_ah);
		पूर्ण
	पूर्ण
	old_ctx = sc->cur_chan;
	sc->cur_chan = sc->next_chan;
	sc->cur_chan->stopped = false;
	sc->next_chan = शून्य;

	अगर (!sc->sched.offchannel_pending)
		sc->sched.offchannel_duration = 0;

	अगर (sc->sched.state != ATH_CHANCTX_STATE_FORCE_ACTIVE)
		sc->sched.state = ATH_CHANCTX_STATE_IDLE;

	spin_unlock_bh(&sc->chan_lock);

	अगर (sc->sc_ah->chip_fullsleep ||
	    स_भेद(&sc->cur_chandef, &sc->cur_chan->chandef,
		   माप(sc->cur_chandef))) अणु
		ath_dbg(common, CHAN_CTX,
			"%s: Set channel %d MHz\n",
			__func__, sc->cur_chan->chandef.center_freq1);
		ath_set_channel(sc);
		अगर (measure_समय)
			sc->sched.channel_चयन_समय =
				ath9k_hw_get_tsf_offset(&ts, शून्य);
		/*
		 * A reset will ensure that all queues are woken up,
		 * so there is no need to awaken them again.
		 */
		जाओ out;
	पूर्ण

	अगर (queues_stopped)
		ath9k_chanctx_wake_queues(sc, old_ctx);
out:
	अगर (send_ps)
		ath_chanctx_send_ps_frame(sc, false);

	ath_offchannel_channel_change(sc);
	ath_chanctx_event(sc, शून्य, ATH_CHANCTX_EVENT_SWITCH);
पूर्ण

अटल व्योम ath_chanctx_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ath_softc *sc = container_of(work, काष्ठा ath_softc,
					    chanctx_work);
	mutex_lock(&sc->mutex);
	ath_chanctx_set_next(sc, false);
	mutex_unlock(&sc->mutex);
पूर्ण

व्योम ath9k_offchannel_init(काष्ठा ath_softc *sc)
अणु
	काष्ठा ath_chanctx *ctx;
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *chan;
	पूर्णांक i;

	sband = &common->sbands[NL80211_BAND_2GHZ];
	अगर (!sband->n_channels)
		sband = &common->sbands[NL80211_BAND_5GHZ];

	chan = &sband->channels[0];

	ctx = &sc->offchannel.chan;
	INIT_LIST_HEAD(&ctx->vअगरs);
	ctx->txघातer = ATH_TXPOWER_MAX;
	cfg80211_chandef_create(&ctx->chandef, chan, NL80211_CHAN_HT20);

	क्रम (i = 0; i < ARRAY_SIZE(ctx->acq); i++) अणु
		INIT_LIST_HEAD(&ctx->acq[i].acq_new);
		INIT_LIST_HEAD(&ctx->acq[i].acq_old);
		spin_lock_init(&ctx->acq[i].lock);
	पूर्ण

	sc->offchannel.chan.offchannel = true;
पूर्ण

व्योम ath9k_init_channel_context(काष्ठा ath_softc *sc)
अणु
	INIT_WORK(&sc->chanctx_work, ath_chanctx_work);

	समयr_setup(&sc->offchannel.समयr, ath_offchannel_समयr, 0);
	समयr_setup(&sc->sched.समयr, ath_chanctx_समयr, 0);

	init_completion(&sc->go_beacon);
पूर्ण

व्योम ath9k_deinit_channel_context(काष्ठा ath_softc *sc)
अणु
	cancel_work_sync(&sc->chanctx_work);
पूर्ण

bool ath9k_is_chanctx_enabled(व्योम)
अणु
	वापस (ath9k_use_chanctx == 1);
पूर्ण

/********************/
/* Queue management */
/********************/

व्योम ath9k_chanctx_stop_queues(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	पूर्णांक i;

	अगर (ctx == &sc->offchannel.chan) अणु
		ieee80211_stop_queue(sc->hw,
				     sc->hw->offchannel_tx_hw_queue);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++)
			ieee80211_stop_queue(sc->hw,
					     ctx->hw_queue_base + i);
	पूर्ण

	अगर (ah->opmode == NL80211_IFTYPE_AP)
		ieee80211_stop_queue(sc->hw, sc->hw->queues - 2);
पूर्ण


व्योम ath9k_chanctx_wake_queues(काष्ठा ath_softc *sc, काष्ठा ath_chanctx *ctx)
अणु
	काष्ठा ath_hw *ah = sc->sc_ah;
	पूर्णांक i;

	अगर (ctx == &sc->offchannel.chan) अणु
		ieee80211_wake_queue(sc->hw,
				     sc->hw->offchannel_tx_hw_queue);
	पूर्ण अन्यथा अणु
		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++)
			ieee80211_wake_queue(sc->hw,
					     ctx->hw_queue_base + i);
	पूर्ण

	अगर (ah->opmode == NL80211_IFTYPE_AP)
		ieee80211_wake_queue(sc->hw, sc->hw->queues - 2);
पूर्ण

/*****************/
/* P2P Powersave */
/*****************/

अटल व्योम ath9k_update_p2p_ps_समयr(काष्ठा ath_softc *sc, काष्ठा ath_vअगर *avp)
अणु
	काष्ठा ath_common *common = ath9k_hw_common(sc->sc_ah);
	काष्ठा ath_hw *ah = sc->sc_ah;
	u32 tsf, target_tsf;

	अगर (!avp || !avp->noa.has_next_tsf)
		वापस;

	ath9k_hw_gen_समयr_stop(ah, sc->p2p_ps_समयr);

	tsf = ath9k_hw_gettsf32(sc->sc_ah);

	target_tsf = avp->noa.next_tsf;
	अगर (!avp->noa.असलent)
		target_tsf -= ATH_P2P_PS_STOP_TIME;
	अन्यथा
		target_tsf += ATH_P2P_PS_STOP_TIME;

	अगर (target_tsf - tsf < ATH_P2P_PS_STOP_TIME)
		target_tsf = tsf + ATH_P2P_PS_STOP_TIME;

	ath_dbg(common, CHAN_CTX, "%s absent %d tsf 0x%08X next_tsf 0x%08X (%dms)\n",
		__func__, avp->noa.असलent, tsf, target_tsf,
		(target_tsf - tsf) / 1000);

	ath9k_hw_gen_समयr_start(ah, sc->p2p_ps_समयr, target_tsf, 1000000);
पूर्ण

अटल व्योम ath9k_update_p2p_ps(काष्ठा ath_softc *sc, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;
	u32 tsf;

	अगर (!sc->p2p_ps_समयr)
		वापस;

	अगर (vअगर->type != NL80211_IFTYPE_STATION)
		वापस;

	sc->p2p_ps_vअगर = avp;

	अगर (sc->ps_flags & PS_BEACON_SYNC)
		वापस;

	tsf = ath9k_hw_gettsf32(sc->sc_ah);
	ieee80211_parse_p2p_noa(&vअगर->bss_conf.p2p_noa_attr, &avp->noa, tsf);
	ath9k_update_p2p_ps_समयr(sc, avp);
पूर्ण

अटल u8 ath9k_get_ctwin(काष्ठा ath_softc *sc, काष्ठा ath_vअगर *avp)
अणु
	काष्ठा ath_beacon_config *cur_conf = &sc->cur_chan->beacon;
	u8 चयन_समय, ctwin;

	/*
	 * Channel चयन in multi-channel mode is deferred
	 * by a quarter beacon पूर्णांकerval when handling
	 * ATH_CHANCTX_EVENT_BEACON_PREPARE, so the P2P-GO
	 * पूर्णांकerface is guaranteed to be discoverable
	 * क्रम that duration after a TBTT.
	 */
	चयन_समय = cur_conf->beacon_पूर्णांकerval / 4;

	ctwin = avp->vअगर->bss_conf.p2p_noa_attr.oppps_ctwinकरोw;
	अगर (ctwin && (ctwin < चयन_समय))
		वापस ctwin;

	अगर (चयन_समय < P2P_DEFAULT_CTWIN)
		वापस 0;

	वापस P2P_DEFAULT_CTWIN;
पूर्ण

व्योम ath9k_beacon_add_noa(काष्ठा ath_softc *sc, काष्ठा ath_vअगर *avp,
			  काष्ठा sk_buff *skb)
अणु
	अटल स्थिर u8 noa_ie_hdr[] = अणु
		WLAN_EID_VENDOR_SPECIFIC,	/* type */
		0,				/* length */
		0x50, 0x6f, 0x9a,		/* WFA OUI */
		0x09,				/* P2P subtype */
		0x0c,				/* Notice of Absence */
		0x00,				/* LSB of little-endian len */
		0x00,				/* MSB of little-endian len */
	पूर्ण;

	काष्ठा ieee80211_p2p_noa_attr *noa;
	पूर्णांक noa_len, noa_desc, i = 0;
	u8 *hdr;

	अगर (!avp->offchannel_duration && !avp->noa_duration)
		वापस;

	noa_desc = !!avp->offchannel_duration + !!avp->noa_duration;
	noa_len = 2 + माप(काष्ठा ieee80211_p2p_noa_desc) * noa_desc;

	hdr = skb_put_data(skb, noa_ie_hdr, माप(noa_ie_hdr));
	hdr[1] = माप(noa_ie_hdr) + noa_len - 2;
	hdr[7] = noa_len;

	noa = skb_put_zero(skb, noa_len);

	noa->index = avp->noa_index;
	noa->oppps_ctwinकरोw = ath9k_get_ctwin(sc, avp);
	अगर (noa->oppps_ctwinकरोw)
		noa->oppps_ctwinकरोw |= BIT(7);

	अगर (avp->noa_duration) अणु
		अगर (avp->periodic_noa) अणु
			u32 पूर्णांकerval = TU_TO_USEC(sc->cur_chan->beacon.beacon_पूर्णांकerval);
			noa->desc[i].count = 255;
			noa->desc[i].पूर्णांकerval = cpu_to_le32(पूर्णांकerval);
		पूर्ण अन्यथा अणु
			noa->desc[i].count = 1;
		पूर्ण

		noa->desc[i].start_समय = cpu_to_le32(avp->noa_start);
		noa->desc[i].duration = cpu_to_le32(avp->noa_duration);
		i++;
	पूर्ण

	अगर (avp->offchannel_duration) अणु
		noa->desc[i].count = 1;
		noa->desc[i].start_समय = cpu_to_le32(avp->offchannel_start);
		noa->desc[i].duration = cpu_to_le32(avp->offchannel_duration);
	पूर्ण
पूर्ण

व्योम ath9k_p2p_ps_समयr(व्योम *priv)
अणु
	काष्ठा ath_softc *sc = priv;
	काष्ठा ath_vअगर *avp = sc->p2p_ps_vअगर;
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा ieee80211_sta *sta;
	काष्ठा ath_node *an;
	u32 tsf;

	del_समयr_sync(&sc->sched.समयr);
	ath9k_hw_gen_समयr_stop(sc->sc_ah, sc->p2p_ps_समयr);
	ath_chanctx_event(sc, शून्य, ATH_CHANCTX_EVENT_TSF_TIMER);

	अगर (!avp || avp->chanctx != sc->cur_chan)
		वापस;

	tsf = ath9k_hw_gettsf32(sc->sc_ah);
	अगर (!avp->noa.असलent)
		tsf += ATH_P2P_PS_STOP_TIME;
	अन्यथा
		tsf -= ATH_P2P_PS_STOP_TIME;

	अगर (!avp->noa.has_next_tsf ||
	    avp->noa.next_tsf - tsf > BIT(31))
		ieee80211_update_p2p_noa(&avp->noa, tsf);

	ath9k_update_p2p_ps_समयr(sc, avp);

	rcu_पढ़ो_lock();

	vअगर = avp->vअगर;
	sta = ieee80211_find_sta(vअगर, avp->bssid);
	अगर (!sta)
		जाओ out;

	an = (व्योम *) sta->drv_priv;
	अगर (an->sleeping == !!avp->noa.असलent)
		जाओ out;

	an->sleeping = avp->noa.असलent;
	अगर (an->sleeping)
		ath_tx_aggr_sleep(sta, sc, an);
	अन्यथा
		ath_tx_aggr_wakeup(sc, an);

out:
	rcu_पढ़ो_unlock();
पूर्ण

व्योम ath9k_p2p_bss_info_changed(काष्ठा ath_softc *sc,
				काष्ठा ieee80211_vअगर *vअगर)
अणु
	अचिन्हित दीर्घ flags;

	spin_lock_bh(&sc->sc_pcu_lock);
	spin_lock_irqsave(&sc->sc_pm_lock, flags);
	ath9k_update_p2p_ps(sc, vअगर);
	spin_unlock_irqrestore(&sc->sc_pm_lock, flags);
	spin_unlock_bh(&sc->sc_pcu_lock);
पूर्ण

व्योम ath9k_p2p_beacon_sync(काष्ठा ath_softc *sc)
अणु
	अगर (sc->p2p_ps_vअगर)
		ath9k_update_p2p_ps(sc, sc->p2p_ps_vअगर->vअगर);
पूर्ण

व्योम ath9k_p2p_हटाओ_vअगर(काष्ठा ath_softc *sc,
			  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ath_vअगर *avp = (व्योम *)vअगर->drv_priv;

	spin_lock_bh(&sc->sc_pcu_lock);
	अगर (avp == sc->p2p_ps_vअगर) अणु
		sc->p2p_ps_vअगर = शून्य;
		ath9k_update_p2p_ps_समयr(sc, शून्य);
	पूर्ण
	spin_unlock_bh(&sc->sc_pcu_lock);
पूर्ण

पूर्णांक ath9k_init_p2p(काष्ठा ath_softc *sc)
अणु
	sc->p2p_ps_समयr = ath_gen_समयr_alloc(sc->sc_ah, ath9k_p2p_ps_समयr,
					       शून्य, sc, AR_FIRST_NDP_TIMER);
	अगर (!sc->p2p_ps_समयr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम ath9k_deinit_p2p(काष्ठा ath_softc *sc)
अणु
	अगर (sc->p2p_ps_समयr)
		ath_gen_समयr_मुक्त(sc->sc_ah, sc->p2p_ps_समयr);
पूर्ण

#पूर्ण_अगर /* CONFIG_ATH9K_CHANNEL_CONTEXT */
