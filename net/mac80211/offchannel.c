<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Off-channel operation helpers
 *
 * Copyright 2003, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright 2004, Instant802 Networks, Inc.
 * Copyright 2005, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007, Michael Wu <flamingice@sourmilk.net>
 * Copyright 2009	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2019 Intel Corporation
 */
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"

/*
 * Tell our hardware to disable PS.
 * Optionally inक्रमm AP that we will go to sleep so that it will buffer
 * the frames जबतक we are करोing off-channel work.  This is optional
 * because we *may* be करोing work on-operating channel, and want our
 * hardware unconditionally awake, but still let the AP send us normal frames.
 */
अटल व्योम ieee80211_offchannel_ps_enable(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	bool offchannel_ps_enabled = false;

	/* FIXME: what to करो when local->pspolling is true? */

	del_समयr_sync(&local->dynamic_ps_समयr);
	del_समयr_sync(&अगरmgd->bcn_mon_समयr);
	del_समयr_sync(&अगरmgd->conn_mon_समयr);

	cancel_work_sync(&local->dynamic_ps_enable_work);

	अगर (local->hw.conf.flags & IEEE80211_CONF_PS) अणु
		offchannel_ps_enabled = true;
		local->hw.conf.flags &= ~IEEE80211_CONF_PS;
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);
	पूर्ण

	अगर (!offchannel_ps_enabled ||
	    !ieee80211_hw_check(&local->hw, PS_शून्यFUNC_STACK))
		/*
		 * If घातer save was enabled, no need to send a nullfunc
		 * frame because AP knows that we are sleeping. But अगर the
		 * hardware is creating the nullfunc frame क्रम घातer save
		 * status (ie. IEEE80211_HW_PS_शून्यFUNC_STACK is not
		 * enabled) and घातer save was enabled, the firmware just
		 * sent a null frame with घातer save disabled. So we need
		 * to send a new nullfunc frame to inक्रमm the AP that we
		 * are again sleeping.
		 */
		ieee80211_send_nullfunc(local, sdata, true);
पूर्ण

/* inक्रमm AP that we are awake again */
अटल व्योम ieee80211_offchannel_ps_disable(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	अगर (!local->ps_sdata)
		ieee80211_send_nullfunc(local, sdata, false);
	अन्यथा अगर (local->hw.conf.dynamic_ps_समयout > 0) अणु
		/*
		 * the dynamic_ps_समयr had been running beक्रमe leaving the
		 * operating channel, restart the समयr now and send a nullfunc
		 * frame to inक्रमm the AP that we are awake so that AP sends
		 * the buffered packets (अगर any).
		 */
		ieee80211_send_nullfunc(local, sdata, false);
		mod_समयr(&local->dynamic_ps_समयr, jअगरfies +
			  msecs_to_jअगरfies(local->hw.conf.dynamic_ps_समयout));
	पूर्ण

	ieee80211_sta_reset_beacon_monitor(sdata);
	ieee80211_sta_reset_conn_monitor(sdata);
पूर्ण

व्योम ieee80211_offchannel_stop_vअगरs(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	अगर (WARN_ON(local->use_chanctx))
		वापस;

	/*
	 * notअगरy the AP about us leaving the channel and stop all
	 * STA पूर्णांकerfaces.
	 */

	/*
	 * Stop queues and transmit all frames queued by the driver
	 * beक्रमe sending nullfunc to enable घातersave at the AP.
	 */
	ieee80211_stop_queues_by_reason(&local->hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_OFFCHANNEL,
					false);
	ieee80211_flush_queues(local, शून्य, false);

	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		अगर (sdata->vअगर.type == NL80211_IFTYPE_P2P_DEVICE ||
		    sdata->vअगर.type == NL80211_IFTYPE_न_अंक)
			जारी;

		अगर (sdata->vअगर.type != NL80211_IFTYPE_MONITOR)
			set_bit(SDATA_STATE_OFFCHANNEL, &sdata->state);

		/* Check to see अगर we should disable beaconing. */
		अगर (sdata->vअगर.bss_conf.enable_beacon) अणु
			set_bit(SDATA_STATE_OFFCHANNEL_BEACON_STOPPED,
				&sdata->state);
			sdata->vअगर.bss_conf.enable_beacon = false;
			ieee80211_bss_info_change_notअगरy(
				sdata, BSS_CHANGED_BEACON_ENABLED);
		पूर्ण

		अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
		    sdata->u.mgd.associated)
			ieee80211_offchannel_ps_enable(sdata);
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);
पूर्ण

व्योम ieee80211_offchannel_वापस(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	अगर (WARN_ON(local->use_chanctx))
		वापस;

	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata->vअगर.type == NL80211_IFTYPE_P2P_DEVICE)
			जारी;

		अगर (sdata->vअगर.type != NL80211_IFTYPE_MONITOR)
			clear_bit(SDATA_STATE_OFFCHANNEL, &sdata->state);

		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		/* Tell AP we're back */
		अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
		    sdata->u.mgd.associated)
			ieee80211_offchannel_ps_disable(sdata);

		अगर (test_and_clear_bit(SDATA_STATE_OFFCHANNEL_BEACON_STOPPED,
				       &sdata->state)) अणु
			sdata->vअगर.bss_conf.enable_beacon = true;
			ieee80211_bss_info_change_notअगरy(
				sdata, BSS_CHANGED_BEACON_ENABLED);
		पूर्ण
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);

	ieee80211_wake_queues_by_reason(&local->hw, IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_OFFCHANNEL,
					false);
पूर्ण

अटल व्योम ieee80211_roc_notअगरy_destroy(काष्ठा ieee80211_roc_work *roc)
अणु
	/* was never transmitted */
	अगर (roc->frame) अणु
		cfg80211_mgmt_tx_status(&roc->sdata->wdev, roc->mgmt_tx_cookie,
					roc->frame->data, roc->frame->len,
					false, GFP_KERNEL);
		ieee80211_मुक्त_txskb(&roc->sdata->local->hw, roc->frame);
	पूर्ण

	अगर (!roc->mgmt_tx_cookie)
		cfg80211_reमुख्य_on_channel_expired(&roc->sdata->wdev,
						   roc->cookie, roc->chan,
						   GFP_KERNEL);
	अन्यथा
		cfg80211_tx_mgmt_expired(&roc->sdata->wdev,
					 roc->mgmt_tx_cookie,
					 roc->chan, GFP_KERNEL);

	list_del(&roc->list);
	kमुक्त(roc);
पूर्ण

अटल अचिन्हित दीर्घ ieee80211_end_finished_rocs(काष्ठा ieee80211_local *local,
						 अचिन्हित दीर्घ now)
अणु
	काष्ठा ieee80211_roc_work *roc, *पंचांगp;
	दीर्घ reमुख्यing_dur_min = दीर्घ_उच्च;

	lockdep_निश्चित_held(&local->mtx);

	list_क्रम_each_entry_safe(roc, पंचांगp, &local->roc_list, list) अणु
		दीर्घ reमुख्यing;

		अगर (!roc->started)
			अवरोध;

		reमुख्यing = roc->start_समय +
			    msecs_to_jअगरfies(roc->duration) -
			    now;

		/* In हाल of HW ROC, it is possible that the HW finished the
		 * ROC session beक्रमe the actual requested समय. In such a हाल
		 * end the ROC session (disregarding the reमुख्यing समय).
		 */
		अगर (roc->पात || roc->hw_begun || reमुख्यing <= 0)
			ieee80211_roc_notअगरy_destroy(roc);
		अन्यथा
			reमुख्यing_dur_min = min(reमुख्यing_dur_min, reमुख्यing);
	पूर्ण

	वापस reमुख्यing_dur_min;
पूर्ण

अटल bool ieee80211_recalc_sw_work(काष्ठा ieee80211_local *local,
				     अचिन्हित दीर्घ now)
अणु
	दीर्घ dur = ieee80211_end_finished_rocs(local, now);

	अगर (dur == दीर्घ_उच्च)
		वापस false;

	mod_delayed_work(local->workqueue, &local->roc_work, dur);
	वापस true;
पूर्ण

अटल व्योम ieee80211_handle_roc_started(काष्ठा ieee80211_roc_work *roc,
					 अचिन्हित दीर्घ start_समय)
अणु
	अगर (WARN_ON(roc->notअगरied))
		वापस;

	roc->start_समय = start_समय;
	roc->started = true;

	अगर (roc->mgmt_tx_cookie) अणु
		अगर (!WARN_ON(!roc->frame)) अणु
			ieee80211_tx_skb_tid_band(roc->sdata, roc->frame, 7,
						  roc->chan->band);
			roc->frame = शून्य;
		पूर्ण
	पूर्ण अन्यथा अणु
		cfg80211_पढ़ोy_on_channel(&roc->sdata->wdev, roc->cookie,
					  roc->chan, roc->req_duration,
					  GFP_KERNEL);
	पूर्ण

	roc->notअगरied = true;
पूर्ण

अटल व्योम ieee80211_hw_roc_start(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local, hw_roc_start);
	काष्ठा ieee80211_roc_work *roc;

	mutex_lock(&local->mtx);

	list_क्रम_each_entry(roc, &local->roc_list, list) अणु
		अगर (!roc->started)
			अवरोध;

		roc->hw_begun = true;
		ieee80211_handle_roc_started(roc, local->hw_roc_start_समय);
	पूर्ण

	mutex_unlock(&local->mtx);
पूर्ण

व्योम ieee80211_पढ़ोy_on_channel(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	local->hw_roc_start_समय = jअगरfies;

	trace_api_पढ़ोy_on_channel(local);

	ieee80211_queue_work(hw, &local->hw_roc_start);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_पढ़ोy_on_channel);

अटल व्योम _ieee80211_start_next_roc(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_roc_work *roc, *पंचांगp;
	क्रमागत ieee80211_roc_type type;
	u32 min_dur, max_dur;

	lockdep_निश्चित_held(&local->mtx);

	अगर (WARN_ON(list_empty(&local->roc_list)))
		वापस;

	roc = list_first_entry(&local->roc_list, काष्ठा ieee80211_roc_work,
			       list);

	अगर (WARN_ON(roc->started))
		वापस;

	min_dur = roc->duration;
	max_dur = roc->duration;
	type = roc->type;

	list_क्रम_each_entry(पंचांगp, &local->roc_list, list) अणु
		अगर (पंचांगp == roc)
			जारी;
		अगर (पंचांगp->sdata != roc->sdata || पंचांगp->chan != roc->chan)
			अवरोध;
		max_dur = max(पंचांगp->duration, max_dur);
		min_dur = min(पंचांगp->duration, min_dur);
		type = max(पंचांगp->type, type);
	पूर्ण

	अगर (local->ops->reमुख्य_on_channel) अणु
		पूर्णांक ret = drv_reमुख्य_on_channel(local, roc->sdata, roc->chan,
						max_dur, type);

		अगर (ret) अणु
			wiphy_warn(local->hw.wiphy,
				   "failed to start next HW ROC (%d)\n", ret);
			/*
			 * queue the work काष्ठा again to aव्योम recursion
			 * when multiple failures occur
			 */
			list_क्रम_each_entry(पंचांगp, &local->roc_list, list) अणु
				अगर (पंचांगp->sdata != roc->sdata ||
				    पंचांगp->chan != roc->chan)
					अवरोध;
				पंचांगp->started = true;
				पंचांगp->पात = true;
			पूर्ण
			ieee80211_queue_work(&local->hw, &local->hw_roc_करोne);
			वापस;
		पूर्ण

		/* we'll notअगरy about the start once the HW calls back */
		list_क्रम_each_entry(पंचांगp, &local->roc_list, list) अणु
			अगर (पंचांगp->sdata != roc->sdata || पंचांगp->chan != roc->chan)
				अवरोध;
			पंचांगp->started = true;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* If actually operating on the desired channel (with at least
		 * 20 MHz channel width) करोn't stop all the operations but still
		 * treat it as though the ROC operation started properly, so
		 * other ROC operations won't पूर्णांकerfere with this one.
		 */
		roc->on_channel = roc->chan == local->_oper_chandef.chan &&
				  local->_oper_chandef.width != NL80211_CHAN_WIDTH_5 &&
				  local->_oper_chandef.width != NL80211_CHAN_WIDTH_10;

		/* start this ROC */
		ieee80211_recalc_idle(local);

		अगर (!roc->on_channel) अणु
			ieee80211_offchannel_stop_vअगरs(local);

			local->पंचांगp_channel = roc->chan;
			ieee80211_hw_config(local, 0);
		पूर्ण

		ieee80211_queue_delayed_work(&local->hw, &local->roc_work,
					     msecs_to_jअगरfies(min_dur));

		/* tell userspace or send frame(s) */
		list_क्रम_each_entry(पंचांगp, &local->roc_list, list) अणु
			अगर (पंचांगp->sdata != roc->sdata || पंचांगp->chan != roc->chan)
				अवरोध;

			पंचांगp->on_channel = roc->on_channel;
			ieee80211_handle_roc_started(पंचांगp, jअगरfies);
		पूर्ण
	पूर्ण
पूर्ण

व्योम ieee80211_start_next_roc(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_roc_work *roc;

	lockdep_निश्चित_held(&local->mtx);

	अगर (list_empty(&local->roc_list)) अणु
		ieee80211_run_deferred_scan(local);
		वापस;
	पूर्ण

	/* defer roc अगर driver is not started (i.e. during reconfig) */
	अगर (local->in_reconfig)
		वापस;

	roc = list_first_entry(&local->roc_list, काष्ठा ieee80211_roc_work,
			       list);

	अगर (WARN_ON_ONCE(roc->started))
		वापस;

	अगर (local->ops->reमुख्य_on_channel) अणु
		_ieee80211_start_next_roc(local);
	पूर्ण अन्यथा अणु
		/* delay it a bit */
		ieee80211_queue_delayed_work(&local->hw, &local->roc_work,
					     round_jअगरfies_relative(HZ/2));
	पूर्ण
पूर्ण

अटल व्योम __ieee80211_roc_work(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_roc_work *roc;
	bool on_channel;

	lockdep_निश्चित_held(&local->mtx);

	अगर (WARN_ON(local->ops->reमुख्य_on_channel))
		वापस;

	roc = list_first_entry_or_null(&local->roc_list,
				       काष्ठा ieee80211_roc_work, list);
	अगर (!roc)
		वापस;

	अगर (!roc->started) अणु
		WARN_ON(local->use_chanctx);
		_ieee80211_start_next_roc(local);
	पूर्ण अन्यथा अणु
		on_channel = roc->on_channel;
		अगर (ieee80211_recalc_sw_work(local, jअगरfies))
			वापस;

		/* careful - roc poपूर्णांकer became invalid during recalc */

		अगर (!on_channel) अणु
			ieee80211_flush_queues(local, शून्य, false);

			local->पंचांगp_channel = शून्य;
			ieee80211_hw_config(local, 0);

			ieee80211_offchannel_वापस(local);
		पूर्ण

		ieee80211_recalc_idle(local);
		ieee80211_start_next_roc(local);
	पूर्ण
पूर्ण

अटल व्योम ieee80211_roc_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local, roc_work.work);

	mutex_lock(&local->mtx);
	__ieee80211_roc_work(local);
	mutex_unlock(&local->mtx);
पूर्ण

अटल व्योम ieee80211_hw_roc_करोne(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_local *local =
		container_of(work, काष्ठा ieee80211_local, hw_roc_करोne);

	mutex_lock(&local->mtx);

	ieee80211_end_finished_rocs(local, jअगरfies);

	/* अगर there's another roc, start it now */
	ieee80211_start_next_roc(local);

	mutex_unlock(&local->mtx);
पूर्ण

व्योम ieee80211_reमुख्य_on_channel_expired(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);

	trace_api_reमुख्य_on_channel_expired(local);

	ieee80211_queue_work(hw, &local->hw_roc_करोne);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_reमुख्य_on_channel_expired);

अटल bool
ieee80211_coalesce_hw_started_roc(काष्ठा ieee80211_local *local,
				  काष्ठा ieee80211_roc_work *new_roc,
				  काष्ठा ieee80211_roc_work *cur_roc)
अणु
	अचिन्हित दीर्घ now = jअगरfies;
	अचिन्हित दीर्घ reमुख्यing;

	अगर (WARN_ON(!cur_roc->started))
		वापस false;

	/* अगर it was scheduled in the hardware, but not started yet,
	 * we can only combine अगर the older one had a दीर्घer duration
	 */
	अगर (!cur_roc->hw_begun && new_roc->duration > cur_roc->duration)
		वापस false;

	reमुख्यing = cur_roc->start_समय +
		    msecs_to_jअगरfies(cur_roc->duration) -
		    now;

	/* अगर it करोesn't fit entirely, schedule a new one */
	अगर (new_roc->duration > jअगरfies_to_msecs(reमुख्यing))
		वापस false;

	/* add just after the current one so we combine their finish later */
	list_add(&new_roc->list, &cur_roc->list);

	/* अगर the existing one has alपढ़ोy begun then let this one also
	 * begin, otherwise they'll both be marked properly by the work
	 * काष्ठा that runs once the driver notअगरies us of the beginning
	 */
	अगर (cur_roc->hw_begun) अणु
		new_roc->hw_begun = true;
		ieee80211_handle_roc_started(new_roc, now);
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक ieee80211_start_roc_work(काष्ठा ieee80211_local *local,
				    काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_channel *channel,
				    अचिन्हित पूर्णांक duration, u64 *cookie,
				    काष्ठा sk_buff *txskb,
				    क्रमागत ieee80211_roc_type type)
अणु
	काष्ठा ieee80211_roc_work *roc, *पंचांगp;
	bool queued = false, combine_started = true;
	पूर्णांक ret;

	lockdep_निश्चित_held(&local->mtx);

	अगर (channel->freq_offset)
		/* this may work, but is untested */
		वापस -EOPNOTSUPP;

	अगर (local->use_chanctx && !local->ops->reमुख्य_on_channel)
		वापस -EOPNOTSUPP;

	roc = kzalloc(माप(*roc), GFP_KERNEL);
	अगर (!roc)
		वापस -ENOMEM;

	/*
	 * If the duration is zero, then the driver
	 * wouldn't actually करो anything. Set it to
	 * 10 क्रम now.
	 *
	 * TODO: cancel the off-channel operation
	 *       when we get the SKB's TX status and
	 *       the रुको समय was zero beक्रमe.
	 */
	अगर (!duration)
		duration = 10;

	roc->chan = channel;
	roc->duration = duration;
	roc->req_duration = duration;
	roc->frame = txskb;
	roc->type = type;
	roc->sdata = sdata;

	/*
	 * cookie is either the roc cookie (क्रम normal roc)
	 * or the SKB (क्रम mgmt TX)
	 */
	अगर (!txskb) अणु
		roc->cookie = ieee80211_mgmt_tx_cookie(local);
		*cookie = roc->cookie;
	पूर्ण अन्यथा अणु
		roc->mgmt_tx_cookie = *cookie;
	पूर्ण

	/* अगर there's no need to queue, handle it immediately */
	अगर (list_empty(&local->roc_list) &&
	    !local->scanning && !ieee80211_is_radar_required(local)) अणु
		/* अगर not HW assist, just queue & schedule work */
		अगर (!local->ops->reमुख्य_on_channel) अणु
			list_add_tail(&roc->list, &local->roc_list);
			ieee80211_queue_delayed_work(&local->hw,
						     &local->roc_work, 0);
		पूर्ण अन्यथा अणु
			/* otherwise actually kick it off here
			 * (क्रम error handling)
			 */
			ret = drv_reमुख्य_on_channel(local, sdata, channel,
						    duration, type);
			अगर (ret) अणु
				kमुक्त(roc);
				वापस ret;
			पूर्ण
			roc->started = true;
			list_add_tail(&roc->list, &local->roc_list);
		पूर्ण

		वापस 0;
	पूर्ण

	/* otherwise handle queueing */

	list_क्रम_each_entry(पंचांगp, &local->roc_list, list) अणु
		अगर (पंचांगp->chan != channel || पंचांगp->sdata != sdata)
			जारी;

		/*
		 * Extend this ROC अगर possible: If it hasn't started, add
		 * just after the new one to combine.
		 */
		अगर (!पंचांगp->started) अणु
			list_add(&roc->list, &पंचांगp->list);
			queued = true;
			अवरोध;
		पूर्ण

		अगर (!combine_started)
			जारी;

		अगर (!local->ops->reमुख्य_on_channel) अणु
			/* If there's no hardware reमुख्य-on-channel, and
			 * करोing so won't push us over the maximum r-o-c
			 * we allow, then we can just add the new one to
			 * the list and mark it as having started now.
			 * If it would push over the limit, करोn't try to
			 * combine with other started ones (that haven't
			 * been running as दीर्घ) but potentially sort it
			 * with others that had the same fate.
			 */
			अचिन्हित दीर्घ now = jअगरfies;
			u32 elapsed = jअगरfies_to_msecs(now - पंचांगp->start_समय);
			काष्ठा wiphy *wiphy = local->hw.wiphy;
			u32 max_roc = wiphy->max_reमुख्य_on_channel_duration;

			अगर (elapsed + roc->duration > max_roc) अणु
				combine_started = false;
				जारी;
			पूर्ण

			list_add(&roc->list, &पंचांगp->list);
			queued = true;
			roc->on_channel = पंचांगp->on_channel;
			ieee80211_handle_roc_started(roc, now);
			ieee80211_recalc_sw_work(local, now);
			अवरोध;
		पूर्ण

		queued = ieee80211_coalesce_hw_started_roc(local, roc, पंचांगp);
		अगर (queued)
			अवरोध;
		/* अगर it wasn't queued, perhaps it can be combined with
		 * another that also couldn't get combined previously,
		 * but no need to check क्रम alपढ़ोy started ones, since
		 * that can't work.
		 */
		combine_started = false;
	पूर्ण

	अगर (!queued)
		list_add_tail(&roc->list, &local->roc_list);

	वापस 0;
पूर्ण

पूर्णांक ieee80211_reमुख्य_on_channel(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
				काष्ठा ieee80211_channel *chan,
				अचिन्हित पूर्णांक duration, u64 *cookie)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ret;

	mutex_lock(&local->mtx);
	ret = ieee80211_start_roc_work(local, sdata, chan,
				       duration, cookie, शून्य,
				       IEEE80211_ROC_TYPE_NORMAL);
	mutex_unlock(&local->mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_cancel_roc(काष्ठा ieee80211_local *local,
				u64 cookie, bool mgmt_tx)
अणु
	काष्ठा ieee80211_roc_work *roc, *पंचांगp, *found = शून्य;
	पूर्णांक ret;

	अगर (!cookie)
		वापस -ENOENT;

	flush_work(&local->hw_roc_start);

	mutex_lock(&local->mtx);
	list_क्रम_each_entry_safe(roc, पंचांगp, &local->roc_list, list) अणु
		अगर (!mgmt_tx && roc->cookie != cookie)
			जारी;
		अन्यथा अगर (mgmt_tx && roc->mgmt_tx_cookie != cookie)
			जारी;

		found = roc;
		अवरोध;
	पूर्ण

	अगर (!found) अणु
		mutex_unlock(&local->mtx);
		वापस -ENOENT;
	पूर्ण

	अगर (!found->started) अणु
		ieee80211_roc_notअगरy_destroy(found);
		जाओ out_unlock;
	पूर्ण

	अगर (local->ops->reमुख्य_on_channel) अणु
		ret = drv_cancel_reमुख्य_on_channel(local, roc->sdata);
		अगर (WARN_ON_ONCE(ret)) अणु
			mutex_unlock(&local->mtx);
			वापस ret;
		पूर्ण

		/* TODO:
		 * अगर multiple items were combined here then we really shouldn't
		 * cancel them all - we should रुको क्रम as much समय as needed
		 * क्रम the दीर्घest reमुख्यing one, and only then cancel ...
		 */
		list_क्रम_each_entry_safe(roc, पंचांगp, &local->roc_list, list) अणु
			अगर (!roc->started)
				अवरोध;
			अगर (roc == found)
				found = शून्य;
			ieee80211_roc_notअगरy_destroy(roc);
		पूर्ण

		/* that really must not happen - it was started */
		WARN_ON(found);

		ieee80211_start_next_roc(local);
	पूर्ण अन्यथा अणु
		/* go through work काष्ठा to वापस to the operating channel */
		found->पात = true;
		mod_delayed_work(local->workqueue, &local->roc_work, 0);
	पूर्ण

 out_unlock:
	mutex_unlock(&local->mtx);

	वापस 0;
पूर्ण

पूर्णांक ieee80211_cancel_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
				       काष्ठा wireless_dev *wdev, u64 cookie)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	काष्ठा ieee80211_local *local = sdata->local;

	वापस ieee80211_cancel_roc(local, cookie, false);
पूर्ण

पूर्णांक ieee80211_mgmt_tx(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		      काष्ठा cfg80211_mgmt_tx_params *params, u64 *cookie)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा sta_info *sta;
	स्थिर काष्ठा ieee80211_mgmt *mgmt = (व्योम *)params->buf;
	bool need_offchan = false;
	u32 flags;
	पूर्णांक ret;
	u8 *data;

	अगर (params->करोnt_रुको_क्रम_ack)
		flags = IEEE80211_TX_CTL_NO_ACK;
	अन्यथा
		flags = IEEE80211_TX_INTFL_NL80211_FRAME_TX |
			IEEE80211_TX_CTL_REQ_TX_STATUS;

	अगर (params->no_cck)
		flags |= IEEE80211_TX_CTL_NO_CCK_RATE;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_ADHOC:
		अगर (!sdata->vअगर.bss_conf.ibss_joined)
			need_offchan = true;
#अगर_घोषित CONFIG_MAC80211_MESH
		fallthrough;
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर) &&
		    !sdata->u.mesh.mesh_id_len)
			need_offchan = true;
#पूर्ण_अगर
		fallthrough;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (sdata->vअगर.type != NL80211_IFTYPE_ADHOC &&
		    !ieee80211_vअगर_is_mesh(&sdata->vअगर) &&
		    !rcu_access_poपूर्णांकer(sdata->bss->beacon))
			need_offchan = true;
		अगर (!ieee80211_is_action(mgmt->frame_control) ||
		    mgmt->u.action.category == WLAN_CATEGORY_PUBLIC ||
		    mgmt->u.action.category == WLAN_CATEGORY_SELF_PROTECTED ||
		    mgmt->u.action.category == WLAN_CATEGORY_SPECTRUM_MGMT)
			अवरोध;
		rcu_पढ़ो_lock();
		sta = sta_info_get_bss(sdata, mgmt->da);
		rcu_पढ़ो_unlock();
		अगर (!sta)
			वापस -ENOLINK;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		sdata_lock(sdata);
		अगर (!sdata->u.mgd.associated ||
		    (params->offchan && params->रुको &&
		     local->ops->reमुख्य_on_channel &&
		     स_भेद(sdata->u.mgd.associated->bssid,
			    mgmt->bssid, ETH_ALEN)))
			need_offchan = true;
		sdata_unlock(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		need_offchan = true;
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* configurations requiring offchan cannot work अगर no channel has been
	 * specअगरied
	 */
	अगर (need_offchan && !params->chan)
		वापस -EINVAL;

	mutex_lock(&local->mtx);

	/* Check अगर the operating channel is the requested channel */
	अगर (!need_offchan) अणु
		काष्ठा ieee80211_chanctx_conf *chanctx_conf;

		rcu_पढ़ो_lock();
		chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);

		अगर (chanctx_conf) अणु
			need_offchan = params->chan &&
				       (params->chan !=
					chanctx_conf->def.chan);
		पूर्ण अन्यथा अगर (!params->chan) अणु
			ret = -EINVAL;
			rcu_पढ़ो_unlock();
			जाओ out_unlock;
		पूर्ण अन्यथा अणु
			need_offchan = true;
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण

	अगर (need_offchan && !params->offchan) अणु
		ret = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + params->len);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ out_unlock;
	पूर्ण
	skb_reserve(skb, local->hw.extra_tx_headroom);

	data = skb_put_data(skb, params->buf, params->len);

	/* Update CSA counters */
	अगर (sdata->vअगर.csa_active &&
	    (sdata->vअगर.type == NL80211_IFTYPE_AP ||
	     sdata->vअगर.type == NL80211_IFTYPE_MESH_POINT ||
	     sdata->vअगर.type == NL80211_IFTYPE_ADHOC) &&
	    params->n_csa_offsets) अणु
		पूर्णांक i;
		काष्ठा beacon_data *beacon = शून्य;

		rcu_पढ़ो_lock();

		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
			beacon = rcu_dereference(sdata->u.ap.beacon);
		अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC)
			beacon = rcu_dereference(sdata->u.ibss.presp);
		अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
			beacon = rcu_dereference(sdata->u.mesh.beacon);

		अगर (beacon)
			क्रम (i = 0; i < params->n_csa_offsets; i++)
				data[params->csa_offsets[i]] =
					beacon->cntdwn_current_counter;

		rcu_पढ़ो_unlock();
	पूर्ण

	IEEE80211_SKB_CB(skb)->flags = flags;

	skb->dev = sdata->dev;

	अगर (!params->करोnt_रुको_क्रम_ack) अणु
		/* make a copy to preserve the frame contents
		 * in हाल of encryption.
		 */
		ret = ieee80211_attach_ack_skb(local, skb, cookie, GFP_KERNEL);
		अगर (ret) अणु
			kमुक्त_skb(skb);
			जाओ out_unlock;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* Assign a dummy non-zero cookie, it's not sent to
		 * userspace in this हाल but we rely on its value
		 * पूर्णांकernally in the need_offchan हाल to distinguish
		 * mgmt-tx from reमुख्य-on-channel.
		 */
		*cookie = 0xffffffff;
	पूर्ण

	अगर (!need_offchan) अणु
		ieee80211_tx_skb(sdata, skb);
		ret = 0;
		जाओ out_unlock;
	पूर्ण

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_TX_OFFCHAN |
					IEEE80211_TX_INTFL_OFFCHAN_TX_OK;
	अगर (ieee80211_hw_check(&local->hw, QUEUE_CONTROL))
		IEEE80211_SKB_CB(skb)->hw_queue =
			local->hw.offchannel_tx_hw_queue;

	/* This will handle all kinds of coalescing and immediate TX */
	ret = ieee80211_start_roc_work(local, sdata, params->chan,
				       params->रुको, cookie, skb,
				       IEEE80211_ROC_TYPE_MGMT_TX);
	अगर (ret)
		ieee80211_मुक्त_txskb(&local->hw, skb);
 out_unlock:
	mutex_unlock(&local->mtx);
	वापस ret;
पूर्ण

पूर्णांक ieee80211_mgmt_tx_cancel_रुको(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev, u64 cookie)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);

	वापस ieee80211_cancel_roc(local, cookie, true);
पूर्ण

व्योम ieee80211_roc_setup(काष्ठा ieee80211_local *local)
अणु
	INIT_WORK(&local->hw_roc_start, ieee80211_hw_roc_start);
	INIT_WORK(&local->hw_roc_करोne, ieee80211_hw_roc_करोne);
	INIT_DELAYED_WORK(&local->roc_work, ieee80211_roc_work);
	INIT_LIST_HEAD(&local->roc_list);
पूर्ण

व्योम ieee80211_roc_purge(काष्ठा ieee80211_local *local,
			 काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_roc_work *roc, *पंचांगp;
	bool work_to_करो = false;

	mutex_lock(&local->mtx);
	list_क्रम_each_entry_safe(roc, पंचांगp, &local->roc_list, list) अणु
		अगर (sdata && roc->sdata != sdata)
			जारी;

		अगर (roc->started) अणु
			अगर (local->ops->reमुख्य_on_channel) अणु
				/* can race, so ignore वापस value */
				drv_cancel_reमुख्य_on_channel(local, sdata);
				ieee80211_roc_notअगरy_destroy(roc);
			पूर्ण अन्यथा अणु
				roc->पात = true;
				work_to_करो = true;
			पूर्ण
		पूर्ण अन्यथा अणु
			ieee80211_roc_notअगरy_destroy(roc);
		पूर्ण
	पूर्ण
	अगर (work_to_करो)
		__ieee80211_roc_work(local);
	mutex_unlock(&local->mtx);
पूर्ण
