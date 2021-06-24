<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * HT handling
 *
 * Copyright 2003, Jouni Malinen <jkmaline@cc.hut.fi>
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007, Michael Wu <flamingice@sourmilk.net>
 * Copyright 2007-2010, Intel Corporation
 * Copyright(c) 2015-2017 Intel Deutschland GmbH
 * Copyright (C) 2018 - 2020 Intel Corporation
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "wme.h"

/**
 * DOC: TX A-MPDU aggregation
 *
 * Aggregation on the TX side requires setting the hardware flag
 * %IEEE80211_HW_AMPDU_AGGREGATION. The driver will then be handed
 * packets with a flag indicating A-MPDU aggregation. The driver
 * or device is responsible क्रम actually aggregating the frames,
 * as well as deciding how many and which to aggregate.
 *
 * When TX aggregation is started by some subप्रणाली (usually the rate
 * control algorithm would be appropriate) by calling the
 * ieee80211_start_tx_ba_session() function, the driver will be
 * notअगरied via its @ampdu_action function, with the
 * %IEEE80211_AMPDU_TX_START action.
 *
 * In response to that, the driver is later required to call the
 * ieee80211_start_tx_ba_cb_irqsafe() function, which will really
 * start the aggregation session after the peer has also responded.
 * If the peer responds negatively, the session will be stopped
 * again right away. Note that it is possible क्रम the aggregation
 * session to be stopped beक्रमe the driver has indicated that it
 * is करोne setting it up, in which हाल it must not indicate the
 * setup completion.
 *
 * Also note that, since we also need to रुको क्रम a response from
 * the peer, the driver is notअगरied of the completion of the
 * handshake by the %IEEE80211_AMPDU_TX_OPERATIONAL action to the
 * @ampdu_action callback.
 *
 * Similarly, when the aggregation session is stopped by the peer
 * or something calling ieee80211_stop_tx_ba_session(), the driver's
 * @ampdu_action function will be called with the action
 * %IEEE80211_AMPDU_TX_STOP. In this हाल, the call must not fail,
 * and the driver must later call ieee80211_stop_tx_ba_cb_irqsafe().
 * Note that the sta can get destroyed beक्रमe the BA tear करोwn is
 * complete.
 */

अटल व्योम ieee80211_send_addba_request(काष्ठा ieee80211_sub_अगर_data *sdata,
					 स्थिर u8 *da, u16 tid,
					 u8 dialog_token, u16 start_seq_num,
					 u16 agg_size, u16 समयout)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	u16 capab;

	skb = dev_alloc_skb(माप(*mgmt) + local->hw.extra_tx_headroom);

	अगर (!skb)
		वापस;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	mgmt = skb_put_zero(skb, 24);
	स_नकल(mgmt->da, da, ETH_ALEN);
	स_नकल(mgmt->sa, sdata->vअगर.addr, ETH_ALEN);
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN ||
	    sdata->vअगर.type == NL80211_IFTYPE_MESH_POINT)
		स_नकल(mgmt->bssid, sdata->vअगर.addr, ETH_ALEN);
	अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION)
		स_नकल(mgmt->bssid, sdata->u.mgd.bssid, ETH_ALEN);
	अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC)
		स_नकल(mgmt->bssid, sdata->u.ibss.bssid, ETH_ALEN);

	mgmt->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
					  IEEE80211_STYPE_ACTION);

	skb_put(skb, 1 + माप(mgmt->u.action.u.addba_req));

	mgmt->u.action.category = WLAN_CATEGORY_BACK;
	mgmt->u.action.u.addba_req.action_code = WLAN_ACTION_ADDBA_REQ;

	mgmt->u.action.u.addba_req.dialog_token = dialog_token;
	capab = IEEE80211_ADDBA_PARAM_AMSDU_MASK;
	capab |= IEEE80211_ADDBA_PARAM_POLICY_MASK;
	capab |= u16_encode_bits(tid, IEEE80211_ADDBA_PARAM_TID_MASK);
	capab |= u16_encode_bits(agg_size, IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK);

	mgmt->u.action.u.addba_req.capab = cpu_to_le16(capab);

	mgmt->u.action.u.addba_req.समयout = cpu_to_le16(समयout);
	mgmt->u.action.u.addba_req.start_seq_num =
					cpu_to_le16(start_seq_num << 4);

	ieee80211_tx_skb(sdata, skb);
पूर्ण

व्योम ieee80211_send_bar(काष्ठा ieee80211_vअगर *vअगर, u8 *ra, u16 tid, u16 ssn)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_bar *bar;
	u16 bar_control = 0;

	skb = dev_alloc_skb(माप(*bar) + local->hw.extra_tx_headroom);
	अगर (!skb)
		वापस;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	bar = skb_put_zero(skb, माप(*bar));
	bar->frame_control = cpu_to_le16(IEEE80211_FTYPE_CTL |
					 IEEE80211_STYPE_BACK_REQ);
	स_नकल(bar->ra, ra, ETH_ALEN);
	स_नकल(bar->ta, sdata->vअगर.addr, ETH_ALEN);
	bar_control |= (u16)IEEE80211_BAR_CTRL_ACK_POLICY_NORMAL;
	bar_control |= (u16)IEEE80211_BAR_CTRL_CBMTID_COMPRESSED_BA;
	bar_control |= (u16)(tid << IEEE80211_BAR_CTRL_TID_INFO_SHIFT);
	bar->control = cpu_to_le16(bar_control);
	bar->start_seq_num = cpu_to_le16(ssn);

	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_INTFL_DONT_ENCRYPT |
					IEEE80211_TX_CTL_REQ_TX_STATUS;
	ieee80211_tx_skb_tid(sdata, skb, tid);
पूर्ण
EXPORT_SYMBOL(ieee80211_send_bar);

व्योम ieee80211_assign_tid_tx(काष्ठा sta_info *sta, पूर्णांक tid,
			     काष्ठा tid_ampdu_tx *tid_tx)
अणु
	lockdep_निश्चित_held(&sta->ampdu_mlme.mtx);
	lockdep_निश्चित_held(&sta->lock);
	rcu_assign_poपूर्णांकer(sta->ampdu_mlme.tid_tx[tid], tid_tx);
पूर्ण

/*
 * When multiple aggregation sessions on multiple stations
 * are being created/destroyed simultaneously, we need to
 * refcount the global queue stop caused by that in order
 * to not get पूर्णांकo a situation where one of the aggregation
 * setup or tearकरोwn re-enables queues beक्रमe the other is
 * पढ़ोy to handle that.
 *
 * These two functions take care of this issue by keeping
 * a global "agg_queue_stop" refcount.
 */
अटल व्योम __acquires(agg_queue)
ieee80211_stop_queue_agg(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक tid)
अणु
	पूर्णांक queue = sdata->vअगर.hw_queue[ieee80211_ac_from_tid(tid)];

	/* we करो refcounting here, so करोn't use the queue reason refcounting */

	अगर (atomic_inc_वापस(&sdata->local->agg_queue_stop[queue]) == 1)
		ieee80211_stop_queue_by_reason(
			&sdata->local->hw, queue,
			IEEE80211_QUEUE_STOP_REASON_AGGREGATION,
			false);
	__acquire(agg_queue);
पूर्ण

अटल व्योम __releases(agg_queue)
ieee80211_wake_queue_agg(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक tid)
अणु
	पूर्णांक queue = sdata->vअगर.hw_queue[ieee80211_ac_from_tid(tid)];

	अगर (atomic_dec_वापस(&sdata->local->agg_queue_stop[queue]) == 0)
		ieee80211_wake_queue_by_reason(
			&sdata->local->hw, queue,
			IEEE80211_QUEUE_STOP_REASON_AGGREGATION,
			false);
	__release(agg_queue);
पूर्ण

अटल व्योम
ieee80211_agg_stop_txq(काष्ठा sta_info *sta, पूर्णांक tid)
अणु
	काष्ठा ieee80211_txq *txq = sta->sta.txq[tid];
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा fq *fq;
	काष्ठा txq_info *txqi;

	अगर (!txq)
		वापस;

	txqi = to_txq_info(txq);
	sdata = vअगर_to_sdata(txq->vअगर);
	fq = &sdata->local->fq;

	/* Lock here to protect against further seqno updates on dequeue */
	spin_lock_bh(&fq->lock);
	set_bit(IEEE80211_TXQ_STOP, &txqi->flags);
	spin_unlock_bh(&fq->lock);
पूर्ण

अटल व्योम
ieee80211_agg_start_txq(काष्ठा sta_info *sta, पूर्णांक tid, bool enable)
अणु
	काष्ठा ieee80211_txq *txq = sta->sta.txq[tid];
	काष्ठा txq_info *txqi;

	अगर (!txq)
		वापस;

	txqi = to_txq_info(txq);

	अगर (enable)
		set_bit(IEEE80211_TXQ_AMPDU, &txqi->flags);
	अन्यथा
		clear_bit(IEEE80211_TXQ_AMPDU, &txqi->flags);

	clear_bit(IEEE80211_TXQ_STOP, &txqi->flags);
	local_bh_disable();
	rcu_पढ़ो_lock();
	schedule_and_wake_txq(sta->sdata->local, txqi);
	rcu_पढ़ो_unlock();
	local_bh_enable();
पूर्ण

/*
 * splice packets from the STA's pending to the local pending,
 * requires a call to ieee80211_agg_splice_finish later
 */
अटल व्योम __acquires(agg_queue)
ieee80211_agg_splice_packets(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा tid_ampdu_tx *tid_tx, u16 tid)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक queue = sdata->vअगर.hw_queue[ieee80211_ac_from_tid(tid)];
	अचिन्हित दीर्घ flags;

	ieee80211_stop_queue_agg(sdata, tid);

	अगर (WARN(!tid_tx,
		 "TID %d gone but expected when splicing aggregates from the pending queue\n",
		 tid))
		वापस;

	अगर (!skb_queue_empty(&tid_tx->pending)) अणु
		spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
		/* copy over reमुख्यing packets */
		skb_queue_splice_tail_init(&tid_tx->pending,
					   &local->pending[queue]);
		spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम __releases(agg_queue)
ieee80211_agg_splice_finish(काष्ठा ieee80211_sub_अगर_data *sdata, u16 tid)
अणु
	ieee80211_wake_queue_agg(sdata, tid);
पूर्ण

अटल व्योम ieee80211_हटाओ_tid_tx(काष्ठा sta_info *sta, पूर्णांक tid)
अणु
	काष्ठा tid_ampdu_tx *tid_tx;

	lockdep_निश्चित_held(&sta->ampdu_mlme.mtx);
	lockdep_निश्चित_held(&sta->lock);

	tid_tx = rcu_dereference_रक्षित_tid_tx(sta, tid);

	/*
	 * When we get here, the TX path will not be lockless any more wrt.
	 * aggregation, since the OPERATIONAL bit has दीर्घ been cleared.
	 * Thus it will block on getting the lock, अगर it occurs. So अगर we
	 * stop the queue now, we will not get any more packets, and any
	 * that might be being processed will रुको क्रम us here, thereby
	 * guaranteeing that no packets go to the tid_tx pending queue any
	 * more.
	 */

	ieee80211_agg_splice_packets(sta->sdata, tid_tx, tid);

	/* future packets must not find the tid_tx काष्ठा any more */
	ieee80211_assign_tid_tx(sta, tid, शून्य);

	ieee80211_agg_splice_finish(sta->sdata, tid);
	ieee80211_agg_start_txq(sta, tid, false);

	kमुक्त_rcu(tid_tx, rcu_head);
पूर्ण

पूर्णांक ___ieee80211_stop_tx_ba_session(काष्ठा sta_info *sta, u16 tid,
				    क्रमागत ieee80211_agg_stop_reason reason)
अणु
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा tid_ampdu_tx *tid_tx;
	काष्ठा ieee80211_ampdu_params params = अणु
		.sta = &sta->sta,
		.tid = tid,
		.buf_size = 0,
		.amsdu = false,
		.समयout = 0,
		.ssn = 0,
	पूर्ण;
	पूर्णांक ret;

	lockdep_निश्चित_held(&sta->ampdu_mlme.mtx);

	चयन (reason) अणु
	हाल AGG_STOP_DECLINED:
	हाल AGG_STOP_LOCAL_REQUEST:
	हाल AGG_STOP_PEER_REQUEST:
		params.action = IEEE80211_AMPDU_TX_STOP_CONT;
		अवरोध;
	हाल AGG_STOP_DESTROY_STA:
		params.action = IEEE80211_AMPDU_TX_STOP_FLUSH;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&sta->lock);

	/* मुक्त काष्ठा pending क्रम start, अगर present */
	tid_tx = sta->ampdu_mlme.tid_start_tx[tid];
	kमुक्त(tid_tx);
	sta->ampdu_mlme.tid_start_tx[tid] = शून्य;

	tid_tx = rcu_dereference_रक्षित_tid_tx(sta, tid);
	अगर (!tid_tx) अणु
		spin_unlock_bh(&sta->lock);
		वापस -ENOENT;
	पूर्ण

	/*
	 * अगर we're alपढ़ोy stopping ignore any new requests to stop
	 * unless we're destroying it in which हाल notअगरy the driver
	 */
	अगर (test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) अणु
		spin_unlock_bh(&sta->lock);
		अगर (reason != AGG_STOP_DESTROY_STA)
			वापस -EALREADY;
		params.action = IEEE80211_AMPDU_TX_STOP_FLUSH_CONT;
		ret = drv_ampdu_action(local, sta->sdata, &params);
		WARN_ON_ONCE(ret);
		वापस 0;
	पूर्ण

	अगर (test_bit(HT_AGG_STATE_WANT_START, &tid_tx->state)) अणु
		/* not even started yet! */
		ieee80211_assign_tid_tx(sta, tid, शून्य);
		spin_unlock_bh(&sta->lock);
		kमुक्त_rcu(tid_tx, rcu_head);
		वापस 0;
	पूर्ण

	set_bit(HT_AGG_STATE_STOPPING, &tid_tx->state);

	ieee80211_agg_stop_txq(sta, tid);

	spin_unlock_bh(&sta->lock);

	ht_dbg(sta->sdata, "Tx BA session stop requested for %pM tid %u\n",
	       sta->sta.addr, tid);

	del_समयr_sync(&tid_tx->addba_resp_समयr);
	del_समयr_sync(&tid_tx->session_समयr);

	/*
	 * After this packets are no दीर्घer handed right through
	 * to the driver but are put onto tid_tx->pending instead,
	 * with locking to ensure proper access.
	 */
	clear_bit(HT_AGG_STATE_OPERATIONAL, &tid_tx->state);

	/*
	 * There might be a few packets being processed right now (on
	 * another CPU) that have alपढ़ोy gotten past the aggregation
	 * check when it was still OPERATIONAL and consequently have
	 * IEEE80211_TX_CTL_AMPDU set. In that हाल, this code might
	 * call पूर्णांकo the driver at the same समय or even beक्रमe the
	 * TX paths calls पूर्णांकo it, which could confuse the driver.
	 *
	 * Wait क्रम all currently running TX paths to finish beक्रमe
	 * telling the driver. New packets will not go through since
	 * the aggregation session is no दीर्घer OPERATIONAL.
	 */
	अगर (!local->in_reconfig)
		synchronize_net();

	tid_tx->stop_initiator = reason == AGG_STOP_PEER_REQUEST ?
					WLAN_BACK_RECIPIENT :
					WLAN_BACK_INITIATOR;
	tid_tx->tx_stop = reason == AGG_STOP_LOCAL_REQUEST;

	ret = drv_ampdu_action(local, sta->sdata, &params);

	/* HW shall not deny going back to legacy */
	अगर (WARN_ON(ret)) अणु
		/*
		 * We may have pending packets get stuck in this हाल...
		 * Not bothering with a workaround क्रम now.
		 */
	पूर्ण

	/*
	 * In the हाल of AGG_STOP_DESTROY_STA, the driver won't
	 * necessarily call ieee80211_stop_tx_ba_cb(), so this may
	 * seem like we can leave the tid_tx data pending क्रमever.
	 * This is true, in a way, but "forever" is only until the
	 * station काष्ठा is actually destroyed. In the meanसमय,
	 * leaving it around ensures that we करोn't transmit packets
	 * to the driver on this TID which might confuse it.
	 */

	वापस 0;
पूर्ण

/*
 * After sending add Block Ack request we activated a समयr until
 * add Block Ack response will arrive from the recipient.
 * If this समयr expires sta_addba_resp_समयr_expired will be executed.
 */
अटल व्योम sta_addba_resp_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा tid_ampdu_tx *tid_tx = from_समयr(tid_tx, t, addba_resp_समयr);
	काष्ठा sta_info *sta = tid_tx->sta;
	u8 tid = tid_tx->tid;

	/* check अगर the TID रुकोs क्रम addBA response */
	अगर (test_bit(HT_AGG_STATE_RESPONSE_RECEIVED, &tid_tx->state)) अणु
		ht_dbg(sta->sdata,
		       "timer expired on %pM tid %d not expecting addBA response\n",
		       sta->sta.addr, tid);
		वापस;
	पूर्ण

	ht_dbg(sta->sdata, "addBA response timer expired on %pM tid %d\n",
	       sta->sta.addr, tid);

	ieee80211_stop_tx_ba_session(&sta->sta, tid);
पूर्ण

अटल व्योम ieee80211_send_addba_with_समयout(काष्ठा sta_info *sta,
					      काष्ठा tid_ampdu_tx *tid_tx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sta->local;
	u8 tid = tid_tx->tid;
	u16 buf_size;

	/* activate the समयr क्रम the recipient's addBA response */
	mod_समयr(&tid_tx->addba_resp_समयr, jअगरfies + ADDBA_RESP_INTERVAL);
	ht_dbg(sdata, "activated addBA response timer on %pM tid %d\n",
	       sta->sta.addr, tid);

	spin_lock_bh(&sta->lock);
	sta->ampdu_mlme.last_addba_req_समय[tid] = jअगरfies;
	sta->ampdu_mlme.addba_req_num[tid]++;
	spin_unlock_bh(&sta->lock);

	अगर (sta->sta.he_cap.has_he) अणु
		buf_size = local->hw.max_tx_aggregation_subframes;
	पूर्ण अन्यथा अणु
		/*
		 * We really should use what the driver told us it will
		 * transmit as the maximum, but certain APs (e.g. the
		 * LinkSys WRT120N with FW v1.0.07 build 002 Jun 18 2012)
		 * will crash when we use a lower number.
		 */
		buf_size = IEEE80211_MAX_AMPDU_BUF_HT;
	पूर्ण

	/* send AddBA request */
	ieee80211_send_addba_request(sdata, sta->sta.addr, tid,
				     tid_tx->dialog_token,
				     sta->tid_seq[tid] >> 4,
				     buf_size, tid_tx->समयout);

	WARN_ON(test_and_set_bit(HT_AGG_STATE_SENT_ADDBA, &tid_tx->state));
पूर्ण

व्योम ieee80211_tx_ba_session_handle_start(काष्ठा sta_info *sta, पूर्णांक tid)
अणु
	काष्ठा tid_ampdu_tx *tid_tx;
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_ampdu_params params = अणु
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_TX_START,
		.tid = tid,
		.buf_size = 0,
		.amsdu = false,
		.समयout = 0,
	पूर्ण;
	पूर्णांक ret;

	tid_tx = rcu_dereference_रक्षित_tid_tx(sta, tid);

	/*
	 * Start queuing up packets क्रम this aggregation session.
	 * We're going to release them once the driver is OK with
	 * that.
	 */
	clear_bit(HT_AGG_STATE_WANT_START, &tid_tx->state);

	ieee80211_agg_stop_txq(sta, tid);

	/*
	 * Make sure no packets are being processed. This ensures that
	 * we have a valid starting sequence number and that in-flight
	 * packets have been flushed out and no packets क्रम this TID
	 * will go पूर्णांकo the driver during the ampdu_action call.
	 */
	synchronize_net();

	params.ssn = sta->tid_seq[tid] >> 4;
	ret = drv_ampdu_action(local, sdata, &params);
	अगर (ret == IEEE80211_AMPDU_TX_START_DELAY_ADDBA) अणु
		वापस;
	पूर्ण अन्यथा अगर (ret == IEEE80211_AMPDU_TX_START_IMMEDIATE) अणु
		/*
		 * We didn't send the request yet, so don't need to check
		 * here अगर we alपढ़ोy got a response, just mark as driver
		 * पढ़ोy immediately.
		 */
		set_bit(HT_AGG_STATE_DRV_READY, &tid_tx->state);
	पूर्ण अन्यथा अगर (ret) अणु
		ht_dbg(sdata,
		       "BA request denied - HW unavailable for %pM tid %d\n",
		       sta->sta.addr, tid);
		spin_lock_bh(&sta->lock);
		ieee80211_agg_splice_packets(sdata, tid_tx, tid);
		ieee80211_assign_tid_tx(sta, tid, शून्य);
		ieee80211_agg_splice_finish(sdata, tid);
		spin_unlock_bh(&sta->lock);

		ieee80211_agg_start_txq(sta, tid, false);

		kमुक्त_rcu(tid_tx, rcu_head);
		वापस;
	पूर्ण

	ieee80211_send_addba_with_समयout(sta, tid_tx);
पूर्ण

/*
 * After accepting the AddBA Response we activated a समयr,
 * resetting it after each frame that we send.
 */
अटल व्योम sta_tx_agg_session_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा tid_ampdu_tx *tid_tx = from_समयr(tid_tx, t, session_समयr);
	काष्ठा sta_info *sta = tid_tx->sta;
	u8 tid = tid_tx->tid;
	अचिन्हित दीर्घ समयout;

	अगर (test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) अणु
		वापस;
	पूर्ण

	समयout = tid_tx->last_tx + TU_TO_JIFFIES(tid_tx->समयout);
	अगर (समय_is_after_jअगरfies(समयout)) अणु
		mod_समयr(&tid_tx->session_समयr, समयout);
		वापस;
	पूर्ण

	ht_dbg(sta->sdata, "tx session timer expired on %pM tid %d\n",
	       sta->sta.addr, tid);

	ieee80211_stop_tx_ba_session(&sta->sta, tid);
पूर्ण

पूर्णांक ieee80211_start_tx_ba_session(काष्ठा ieee80211_sta *pubsta, u16 tid,
				  u16 समयout)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा tid_ampdu_tx *tid_tx;
	पूर्णांक ret = 0;

	trace_api_start_tx_ba_session(pubsta, tid);

	अगर (WARN(sta->reserved_tid == tid,
		 "Requested to start BA session on reserved tid=%d", tid))
		वापस -EINVAL;

	अगर (!pubsta->ht_cap.ht_supported &&
	    sta->sdata->vअगर.bss_conf.chandef.chan->band != NL80211_BAND_6GHZ)
		वापस -EINVAL;

	अगर (WARN_ON_ONCE(!local->ops->ampdu_action))
		वापस -EINVAL;

	अगर ((tid >= IEEE80211_NUM_TIDS) ||
	    !ieee80211_hw_check(&local->hw, AMPDU_AGGREGATION) ||
	    ieee80211_hw_check(&local->hw, TX_AMPDU_SETUP_IN_HW))
		वापस -EINVAL;

	अगर (WARN_ON(tid >= IEEE80211_FIRST_TSPEC_TSID))
		वापस -EINVAL;

	ht_dbg(sdata, "Open BA session requested for %pM tid %u\n",
	       pubsta->addr, tid);

	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION &&
	    sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT &&
	    sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN &&
	    sdata->vअगर.type != NL80211_IFTYPE_AP &&
	    sdata->vअगर.type != NL80211_IFTYPE_ADHOC)
		वापस -EINVAL;

	अगर (test_sta_flag(sta, WLAN_STA_BLOCK_BA)) अणु
		ht_dbg(sdata,
		       "BA sessions blocked - Denying BA session request %pM tid %d\n",
		       sta->sta.addr, tid);
		वापस -EINVAL;
	पूर्ण

	/*
	 * 802.11n-2009 11.5.1.1: If the initiating STA is an HT STA, is a
	 * member of an IBSS, and has no other existing Block Ack agreement
	 * with the recipient STA, then the initiating STA shall transmit a
	 * Probe Request frame to the recipient STA and shall not transmit an
	 * ADDBA Request frame unless it receives a Probe Response frame
	 * from the recipient within करोt11ADDBAFailureTimeout.
	 *
	 * The probe request mechanism क्रम ADDBA is currently not implemented,
	 * but we only build up Block Ack session with HT STAs. This inक्रमmation
	 * is set when we receive a bss info from a probe response or a beacon.
	 */
	अगर (sta->sdata->vअगर.type == NL80211_IFTYPE_ADHOC &&
	    !sta->sta.ht_cap.ht_supported) अणु
		ht_dbg(sdata,
		       "BA request denied - IBSS STA %pM does not advertise HT support\n",
		       pubsta->addr);
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&sta->lock);

	/* we have tried too many बार, receiver करोes not want A-MPDU */
	अगर (sta->ampdu_mlme.addba_req_num[tid] > HT_AGG_MAX_RETRIES) अणु
		ret = -EBUSY;
		जाओ err_unlock_sta;
	पूर्ण

	/*
	 * अगर we have tried more than HT_AGG_BURST_RETRIES बार we
	 * will spपढ़ो our requests in समय to aव्योम stalling connection
	 * क्रम too दीर्घ
	 */
	अगर (sta->ampdu_mlme.addba_req_num[tid] > HT_AGG_BURST_RETRIES &&
	    समय_beक्रमe(jअगरfies, sta->ampdu_mlme.last_addba_req_समय[tid] +
			HT_AGG_RETRIES_PERIOD)) अणु
		ht_dbg(sdata,
		       "BA request denied - %d failed requests on %pM tid %u\n",
		       sta->ampdu_mlme.addba_req_num[tid], sta->sta.addr, tid);
		ret = -EBUSY;
		जाओ err_unlock_sta;
	पूर्ण

	tid_tx = rcu_dereference_रक्षित_tid_tx(sta, tid);
	/* check अगर the TID is not in aggregation flow alपढ़ोy */
	अगर (tid_tx || sta->ampdu_mlme.tid_start_tx[tid]) अणु
		ht_dbg(sdata,
		       "BA request denied - session is not idle on %pM tid %u\n",
		       sta->sta.addr, tid);
		ret = -EAGAIN;
		जाओ err_unlock_sta;
	पूर्ण

	/* prepare A-MPDU MLME क्रम Tx aggregation */
	tid_tx = kzalloc(माप(काष्ठा tid_ampdu_tx), GFP_ATOMIC);
	अगर (!tid_tx) अणु
		ret = -ENOMEM;
		जाओ err_unlock_sta;
	पूर्ण

	skb_queue_head_init(&tid_tx->pending);
	__set_bit(HT_AGG_STATE_WANT_START, &tid_tx->state);

	tid_tx->समयout = समयout;
	tid_tx->sta = sta;
	tid_tx->tid = tid;

	/* response समयr */
	समयr_setup(&tid_tx->addba_resp_समयr, sta_addba_resp_समयr_expired, 0);

	/* tx समयr */
	समयr_setup(&tid_tx->session_समयr,
		    sta_tx_agg_session_समयr_expired, TIMER_DEFERRABLE);

	/* assign a dialog token */
	sta->ampdu_mlme.dialog_token_allocator++;
	tid_tx->dialog_token = sta->ampdu_mlme.dialog_token_allocator;

	/*
	 * Finally, assign it to the start array; the work item will
	 * collect it and move it to the normal array.
	 */
	sta->ampdu_mlme.tid_start_tx[tid] = tid_tx;

	ieee80211_queue_work(&local->hw, &sta->ampdu_mlme.work);

	/* this flow जारीs off the work */
 err_unlock_sta:
	spin_unlock_bh(&sta->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_start_tx_ba_session);

अटल व्योम ieee80211_agg_tx_operational(काष्ठा ieee80211_local *local,
					 काष्ठा sta_info *sta, u16 tid)
अणु
	काष्ठा tid_ampdu_tx *tid_tx;
	काष्ठा ieee80211_ampdu_params params = अणु
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_TX_OPERATIONAL,
		.tid = tid,
		.समयout = 0,
		.ssn = 0,
	पूर्ण;

	lockdep_निश्चित_held(&sta->ampdu_mlme.mtx);

	tid_tx = rcu_dereference_रक्षित_tid_tx(sta, tid);
	params.buf_size = tid_tx->buf_size;
	params.amsdu = tid_tx->amsdu;

	ht_dbg(sta->sdata, "Aggregation is on for %pM tid %d\n",
	       sta->sta.addr, tid);

	drv_ampdu_action(local, sta->sdata, &params);

	/*
	 * synchronize with TX path, जबतक splicing the TX path
	 * should block so it won't put more packets onto pending.
	 */
	spin_lock_bh(&sta->lock);

	ieee80211_agg_splice_packets(sta->sdata, tid_tx, tid);
	/*
	 * Now mark as operational. This will be visible
	 * in the TX path, and lets it go lock-मुक्त in
	 * the common हाल.
	 */
	set_bit(HT_AGG_STATE_OPERATIONAL, &tid_tx->state);
	ieee80211_agg_splice_finish(sta->sdata, tid);

	spin_unlock_bh(&sta->lock);

	ieee80211_agg_start_txq(sta, tid, true);
पूर्ण

व्योम ieee80211_start_tx_ba_cb(काष्ठा sta_info *sta, पूर्णांक tid,
			      काष्ठा tid_ampdu_tx *tid_tx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;

	अगर (WARN_ON(test_and_set_bit(HT_AGG_STATE_DRV_READY, &tid_tx->state)))
		वापस;

	अगर (!test_bit(HT_AGG_STATE_SENT_ADDBA, &tid_tx->state)) अणु
		ieee80211_send_addba_with_समयout(sta, tid_tx);
		/* RESPONSE_RECEIVED state whould trigger the flow again */
		वापस;
	पूर्ण

	अगर (test_bit(HT_AGG_STATE_RESPONSE_RECEIVED, &tid_tx->state))
		ieee80211_agg_tx_operational(local, sta, tid);
पूर्ण

अटल काष्ठा tid_ampdu_tx *
ieee80211_lookup_tid_tx(काष्ठा ieee80211_sub_अगर_data *sdata,
			स्थिर u8 *ra, u16 tid, काष्ठा sta_info **sta)
अणु
	काष्ठा tid_ampdu_tx *tid_tx;

	अगर (tid >= IEEE80211_NUM_TIDS) अणु
		ht_dbg(sdata, "Bad TID value: tid = %d (>= %d)\n",
		       tid, IEEE80211_NUM_TIDS);
		वापस शून्य;
	पूर्ण

	*sta = sta_info_get_bss(sdata, ra);
	अगर (!*sta) अणु
		ht_dbg(sdata, "Could not find station: %pM\n", ra);
		वापस शून्य;
	पूर्ण

	tid_tx = rcu_dereference((*sta)->ampdu_mlme.tid_tx[tid]);

	अगर (WARN_ON(!tid_tx))
		ht_dbg(sdata, "addBA was not requested!\n");

	वापस tid_tx;
पूर्ण

व्योम ieee80211_start_tx_ba_cb_irqsafe(काष्ठा ieee80211_vअगर *vअगर,
				      स्थिर u8 *ra, u16 tid)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा tid_ampdu_tx *tid_tx;

	trace_api_start_tx_ba_cb(sdata, ra, tid);

	rcu_पढ़ो_lock();
	tid_tx = ieee80211_lookup_tid_tx(sdata, ra, tid, &sta);
	अगर (!tid_tx)
		जाओ out;

	set_bit(HT_AGG_STATE_START_CB, &tid_tx->state);
	ieee80211_queue_work(&local->hw, &sta->ampdu_mlme.work);
 out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_start_tx_ba_cb_irqsafe);

पूर्णांक __ieee80211_stop_tx_ba_session(काष्ठा sta_info *sta, u16 tid,
				   क्रमागत ieee80211_agg_stop_reason reason)
अणु
	पूर्णांक ret;

	mutex_lock(&sta->ampdu_mlme.mtx);

	ret = ___ieee80211_stop_tx_ba_session(sta, tid, reason);

	mutex_unlock(&sta->ampdu_mlme.mtx);

	वापस ret;
पूर्ण

पूर्णांक ieee80211_stop_tx_ba_session(काष्ठा ieee80211_sta *pubsta, u16 tid)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा tid_ampdu_tx *tid_tx;
	पूर्णांक ret = 0;

	trace_api_stop_tx_ba_session(pubsta, tid);

	अगर (!local->ops->ampdu_action)
		वापस -EINVAL;

	अगर (tid >= IEEE80211_NUM_TIDS)
		वापस -EINVAL;

	spin_lock_bh(&sta->lock);
	tid_tx = rcu_dereference_रक्षित_tid_tx(sta, tid);

	अगर (!tid_tx) अणु
		ret = -ENOENT;
		जाओ unlock;
	पूर्ण

	WARN(sta->reserved_tid == tid,
	     "Requested to stop BA session on reserved tid=%d", tid);

	अगर (test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) अणु
		/* alपढ़ोy in progress stopping it */
		ret = 0;
		जाओ unlock;
	पूर्ण

	set_bit(HT_AGG_STATE_WANT_STOP, &tid_tx->state);
	ieee80211_queue_work(&local->hw, &sta->ampdu_mlme.work);

 unlock:
	spin_unlock_bh(&sta->lock);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(ieee80211_stop_tx_ba_session);

व्योम ieee80211_stop_tx_ba_cb(काष्ठा sta_info *sta, पूर्णांक tid,
			     काष्ठा tid_ampdu_tx *tid_tx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	bool send_delba = false;

	ht_dbg(sdata, "Stopping Tx BA session for %pM tid %d\n",
	       sta->sta.addr, tid);

	spin_lock_bh(&sta->lock);

	अगर (!test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) अणु
		ht_dbg(sdata,
		       "unexpected callback to A-MPDU stop for %pM tid %d\n",
		       sta->sta.addr, tid);
		जाओ unlock_sta;
	पूर्ण

	अगर (tid_tx->stop_initiator == WLAN_BACK_INITIATOR && tid_tx->tx_stop)
		send_delba = true;

	ieee80211_हटाओ_tid_tx(sta, tid);

 unlock_sta:
	spin_unlock_bh(&sta->lock);

	अगर (send_delba)
		ieee80211_send_delba(sdata, sta->sta.addr, tid,
			WLAN_BACK_INITIATOR, WLAN_REASON_QSTA_NOT_USE);
पूर्ण

व्योम ieee80211_stop_tx_ba_cb_irqsafe(काष्ठा ieee80211_vअगर *vअगर,
				     स्थिर u8 *ra, u16 tid)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा tid_ampdu_tx *tid_tx;

	trace_api_stop_tx_ba_cb(sdata, ra, tid);

	rcu_पढ़ो_lock();
	tid_tx = ieee80211_lookup_tid_tx(sdata, ra, tid, &sta);
	अगर (!tid_tx)
		जाओ out;

	set_bit(HT_AGG_STATE_STOP_CB, &tid_tx->state);
	ieee80211_queue_work(&local->hw, &sta->ampdu_mlme.work);
 out:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_stop_tx_ba_cb_irqsafe);


व्योम ieee80211_process_addba_resp(काष्ठा ieee80211_local *local,
				  काष्ठा sta_info *sta,
				  काष्ठा ieee80211_mgmt *mgmt,
				  माप_प्रकार len)
अणु
	काष्ठा tid_ampdu_tx *tid_tx;
	काष्ठा ieee80211_txq *txq;
	u16 capab, tid, buf_size;
	bool amsdu;

	capab = le16_to_cpu(mgmt->u.action.u.addba_resp.capab);
	amsdu = capab & IEEE80211_ADDBA_PARAM_AMSDU_MASK;
	tid = u16_get_bits(capab, IEEE80211_ADDBA_PARAM_TID_MASK);
	buf_size = u16_get_bits(capab, IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK);
	buf_size = min(buf_size, local->hw.max_tx_aggregation_subframes);

	txq = sta->sta.txq[tid];
	अगर (!amsdu && txq)
		set_bit(IEEE80211_TXQ_NO_AMSDU, &to_txq_info(txq)->flags);

	mutex_lock(&sta->ampdu_mlme.mtx);

	tid_tx = rcu_dereference_रक्षित_tid_tx(sta, tid);
	अगर (!tid_tx)
		जाओ out;

	अगर (mgmt->u.action.u.addba_resp.dialog_token != tid_tx->dialog_token) अणु
		ht_dbg(sta->sdata, "wrong addBA response token, %pM tid %d\n",
		       sta->sta.addr, tid);
		जाओ out;
	पूर्ण

	del_समयr_sync(&tid_tx->addba_resp_समयr);

	ht_dbg(sta->sdata, "switched off addBA timer for %pM tid %d\n",
	       sta->sta.addr, tid);

	/*
	 * addba_resp_समयr may have fired beक्रमe we got here, and
	 * caused WANT_STOP to be set. If the stop then was alपढ़ोy
	 * processed further, STOPPING might be set.
	 */
	अगर (test_bit(HT_AGG_STATE_WANT_STOP, &tid_tx->state) ||
	    test_bit(HT_AGG_STATE_STOPPING, &tid_tx->state)) अणु
		ht_dbg(sta->sdata,
		       "got addBA resp for %pM tid %d but we already gave up\n",
		       sta->sta.addr, tid);
		जाओ out;
	पूर्ण

	/*
	 * IEEE 802.11-2007 7.3.1.14:
	 * In an ADDBA Response frame, when the Status Code field
	 * is set to 0, the Buffer Size subfield is set to a value
	 * of at least 1.
	 */
	अगर (le16_to_cpu(mgmt->u.action.u.addba_resp.status)
			== WLAN_STATUS_SUCCESS && buf_size) अणु
		अगर (test_and_set_bit(HT_AGG_STATE_RESPONSE_RECEIVED,
				     &tid_tx->state)) अणु
			/* ignore duplicate response */
			जाओ out;
		पूर्ण

		tid_tx->buf_size = buf_size;
		tid_tx->amsdu = amsdu;

		अगर (test_bit(HT_AGG_STATE_DRV_READY, &tid_tx->state))
			ieee80211_agg_tx_operational(local, sta, tid);

		sta->ampdu_mlme.addba_req_num[tid] = 0;

		tid_tx->समयout =
			le16_to_cpu(mgmt->u.action.u.addba_resp.समयout);

		अगर (tid_tx->समयout) अणु
			mod_समयr(&tid_tx->session_समयr,
				  TU_TO_EXP_TIME(tid_tx->समयout));
			tid_tx->last_tx = jअगरfies;
		पूर्ण

	पूर्ण अन्यथा अणु
		___ieee80211_stop_tx_ba_session(sta, tid, AGG_STOP_DECLINED);
	पूर्ण

 out:
	mutex_unlock(&sta->ampdu_mlme.mtx);
पूर्ण
