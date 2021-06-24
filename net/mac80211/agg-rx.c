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
 * Copyright (C) 2018-2020 Intel Corporation
 */

/**
 * DOC: RX A-MPDU aggregation
 *
 * Aggregation on the RX side requires only implementing the
 * @ampdu_action callback that is invoked to start/stop any
 * block-ack sessions क्रम RX aggregation.
 *
 * When RX aggregation is started by the peer, the driver is
 * notअगरied via @ampdu_action function, with the
 * %IEEE80211_AMPDU_RX_START action, and may reject the request
 * in which हाल a negative response is sent to the peer, अगर it
 * accepts it a positive response is sent.
 *
 * While the session is active, the device/driver are required
 * to de-aggregate frames and pass them up one by one to mac80211,
 * which will handle the reorder buffer.
 *
 * When the aggregation session is stopped again by the peer or
 * ourselves, the driver's @ampdu_action function will be called
 * with the action %IEEE80211_AMPDU_RX_STOP. In this हाल, the
 * call must not fail.
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"

अटल व्योम ieee80211_मुक्त_tid_rx(काष्ठा rcu_head *h)
अणु
	काष्ठा tid_ampdu_rx *tid_rx =
		container_of(h, काष्ठा tid_ampdu_rx, rcu_head);
	पूर्णांक i;

	क्रम (i = 0; i < tid_rx->buf_size; i++)
		__skb_queue_purge(&tid_rx->reorder_buf[i]);
	kमुक्त(tid_rx->reorder_buf);
	kमुक्त(tid_rx->reorder_समय);
	kमुक्त(tid_rx);
पूर्ण

व्योम ___ieee80211_stop_rx_ba_session(काष्ठा sta_info *sta, u16 tid,
				     u16 initiator, u16 reason, bool tx)
अणु
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा tid_ampdu_rx *tid_rx;
	काष्ठा ieee80211_ampdu_params params = अणु
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_RX_STOP,
		.tid = tid,
		.amsdu = false,
		.समयout = 0,
		.ssn = 0,
	पूर्ण;

	lockdep_निश्चित_held(&sta->ampdu_mlme.mtx);

	tid_rx = rcu_dereference_रक्षित(sta->ampdu_mlme.tid_rx[tid],
					lockdep_is_held(&sta->ampdu_mlme.mtx));

	अगर (!test_bit(tid, sta->ampdu_mlme.agg_session_valid))
		वापस;

	RCU_INIT_POINTER(sta->ampdu_mlme.tid_rx[tid], शून्य);
	__clear_bit(tid, sta->ampdu_mlme.agg_session_valid);

	ht_dbg(sta->sdata,
	       "Rx BA session stop requested for %pM tid %u %s reason: %d\n",
	       sta->sta.addr, tid,
	       initiator == WLAN_BACK_RECIPIENT ? "recipient" : "initiator",
	       (पूर्णांक)reason);

	अगर (drv_ampdu_action(local, sta->sdata, &params))
		sdata_info(sta->sdata,
			   "HW problem - can not stop rx aggregation for %pM tid %d\n",
			   sta->sta.addr, tid);

	/* check अगर this is a self generated aggregation halt */
	अगर (initiator == WLAN_BACK_RECIPIENT && tx)
		ieee80211_send_delba(sta->sdata, sta->sta.addr,
				     tid, WLAN_BACK_RECIPIENT, reason);

	/*
	 * वापस here in हाल tid_rx is not asचिन्हित - which will happen अगर
	 * IEEE80211_HW_SUPPORTS_REORDERING_BUFFER is set.
	 */
	अगर (!tid_rx)
		वापस;

	del_समयr_sync(&tid_rx->session_समयr);

	/* make sure ieee80211_sta_reorder_release() करोesn't re-arm the समयr */
	spin_lock_bh(&tid_rx->reorder_lock);
	tid_rx->हटाओd = true;
	spin_unlock_bh(&tid_rx->reorder_lock);
	del_समयr_sync(&tid_rx->reorder_समयr);

	call_rcu(&tid_rx->rcu_head, ieee80211_मुक्त_tid_rx);
पूर्ण

व्योम __ieee80211_stop_rx_ba_session(काष्ठा sta_info *sta, u16 tid,
				    u16 initiator, u16 reason, bool tx)
अणु
	mutex_lock(&sta->ampdu_mlme.mtx);
	___ieee80211_stop_rx_ba_session(sta, tid, initiator, reason, tx);
	mutex_unlock(&sta->ampdu_mlme.mtx);
पूर्ण

व्योम ieee80211_stop_rx_ba_session(काष्ठा ieee80211_vअगर *vअगर, u16 ba_rx_biपंचांगap,
				  स्थिर u8 *addr)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा sta_info *sta;
	पूर्णांक i;

	rcu_पढ़ो_lock();
	sta = sta_info_get_bss(sdata, addr);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++)
		अगर (ba_rx_biपंचांगap & BIT(i))
			set_bit(i, sta->ampdu_mlme.tid_rx_stop_requested);

	ieee80211_queue_work(&sta->local->hw, &sta->ampdu_mlme.work);
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_stop_rx_ba_session);

/*
 * After accepting the AddBA Request we activated a समयr,
 * resetting it after each frame that arrives from the originator.
 */
अटल व्योम sta_rx_agg_session_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा tid_ampdu_rx *tid_rx = from_समयr(tid_rx, t, session_समयr);
	काष्ठा sta_info *sta = tid_rx->sta;
	u8 tid = tid_rx->tid;
	अचिन्हित दीर्घ समयout;

	समयout = tid_rx->last_rx + TU_TO_JIFFIES(tid_rx->समयout);
	अगर (समय_is_after_jअगरfies(समयout)) अणु
		mod_समयr(&tid_rx->session_समयr, समयout);
		वापस;
	पूर्ण

	ht_dbg(sta->sdata, "RX session timer expired on %pM tid %d\n",
	       sta->sta.addr, tid);

	set_bit(tid, sta->ampdu_mlme.tid_rx_समयr_expired);
	ieee80211_queue_work(&sta->local->hw, &sta->ampdu_mlme.work);
पूर्ण

अटल व्योम sta_rx_agg_reorder_समयr_expired(काष्ठा समयr_list *t)
अणु
	काष्ठा tid_ampdu_rx *tid_rx = from_समयr(tid_rx, t, reorder_समयr);

	rcu_पढ़ो_lock();
	ieee80211_release_reorder_समयout(tid_rx->sta, tid_rx->tid);
	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम ieee80211_add_addbaext(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा sk_buff *skb,
				   स्थिर काष्ठा ieee80211_addba_ext_ie *req)
अणु
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_addba_ext_ie *resp;
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	u8 frag_level, cap_frag_level;
	u8 *pos;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस;
	he_cap = ieee80211_get_he_अगरtype_cap(sband, sdata->vअगर.type);
	अगर (!he_cap)
		वापस;

	pos = skb_put_zero(skb, 2 + माप(काष्ठा ieee80211_addba_ext_ie));
	*pos++ = WLAN_EID_ADDBA_EXT;
	*pos++ = माप(काष्ठा ieee80211_addba_ext_ie);
	resp = (काष्ठा ieee80211_addba_ext_ie *)pos;
	resp->data = req->data & IEEE80211_ADDBA_EXT_NO_FRAG;

	frag_level = u32_get_bits(req->data,
				  IEEE80211_ADDBA_EXT_FRAG_LEVEL_MASK);
	cap_frag_level = u32_get_bits(he_cap->he_cap_elem.mac_cap_info[0],
				      IEEE80211_HE_MAC_CAP0_DYNAMIC_FRAG_MASK);
	अगर (frag_level > cap_frag_level)
		frag_level = cap_frag_level;
	resp->data |= u8_encode_bits(frag_level,
				     IEEE80211_ADDBA_EXT_FRAG_LEVEL_MASK);
पूर्ण

अटल व्योम ieee80211_send_addba_resp(काष्ठा sta_info *sta, u8 *da, u16 tid,
				      u8 dialog_token, u16 status, u16 policy,
				      u16 buf_size, u16 समयout,
				      स्थिर काष्ठा ieee80211_addba_ext_ie *addbaext)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	bool amsdu = ieee80211_hw_check(&local->hw, SUPPORTS_AMSDU_IN_AMPDU);
	u16 capab;

	skb = dev_alloc_skb(माप(*mgmt) +
		    2 + माप(काष्ठा ieee80211_addba_ext_ie) +
		    local->hw.extra_tx_headroom);
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

	skb_put(skb, 1 + माप(mgmt->u.action.u.addba_resp));
	mgmt->u.action.category = WLAN_CATEGORY_BACK;
	mgmt->u.action.u.addba_resp.action_code = WLAN_ACTION_ADDBA_RESP;
	mgmt->u.action.u.addba_resp.dialog_token = dialog_token;

	capab = u16_encode_bits(amsdu, IEEE80211_ADDBA_PARAM_AMSDU_MASK);
	capab |= u16_encode_bits(policy, IEEE80211_ADDBA_PARAM_POLICY_MASK);
	capab |= u16_encode_bits(tid, IEEE80211_ADDBA_PARAM_TID_MASK);
	capab |= u16_encode_bits(buf_size, IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK);

	mgmt->u.action.u.addba_resp.capab = cpu_to_le16(capab);
	mgmt->u.action.u.addba_resp.समयout = cpu_to_le16(समयout);
	mgmt->u.action.u.addba_resp.status = cpu_to_le16(status);

	अगर (sta->sta.he_cap.has_he && addbaext)
		ieee80211_add_addbaext(sdata, skb, addbaext);

	ieee80211_tx_skb(sdata, skb);
पूर्ण

व्योम ___ieee80211_start_rx_ba_session(काष्ठा sta_info *sta,
				      u8 dialog_token, u16 समयout,
				      u16 start_seq_num, u16 ba_policy, u16 tid,
				      u16 buf_size, bool tx, bool स्वतः_seq,
				      स्थिर काष्ठा ieee80211_addba_ext_ie *addbaext)
अणु
	काष्ठा ieee80211_local *local = sta->sdata->local;
	काष्ठा tid_ampdu_rx *tid_agg_rx;
	काष्ठा ieee80211_ampdu_params params = अणु
		.sta = &sta->sta,
		.action = IEEE80211_AMPDU_RX_START,
		.tid = tid,
		.amsdu = false,
		.समयout = समयout,
		.ssn = start_seq_num,
	पूर्ण;
	पूर्णांक i, ret = -EOPNOTSUPP;
	u16 status = WLAN_STATUS_REQUEST_DECLINED;
	u16 max_buf_size;

	अगर (tid >= IEEE80211_FIRST_TSPEC_TSID) अणु
		ht_dbg(sta->sdata,
		       "STA %pM requests BA session on unsupported tid %d\n",
		       sta->sta.addr, tid);
		जाओ end;
	पूर्ण

	अगर (!sta->sta.ht_cap.ht_supported &&
	    sta->sdata->vअगर.bss_conf.chandef.chan->band != NL80211_BAND_6GHZ) अणु
		ht_dbg(sta->sdata,
		       "STA %pM erroneously requests BA session on tid %d w/o QoS\n",
		       sta->sta.addr, tid);
		/* send a response anyway, it's an error हाल अगर we get here */
		जाओ end;
	पूर्ण

	अगर (test_sta_flag(sta, WLAN_STA_BLOCK_BA)) अणु
		ht_dbg(sta->sdata,
		       "Suspend in progress - Denying ADDBA request (%pM tid %d)\n",
		       sta->sta.addr, tid);
		जाओ end;
	पूर्ण

	अगर (sta->sta.he_cap.has_he)
		max_buf_size = IEEE80211_MAX_AMPDU_BUF;
	अन्यथा
		max_buf_size = IEEE80211_MAX_AMPDU_BUF_HT;

	/* sanity check क्रम incoming parameters:
	 * check अगर configuration can support the BA policy
	 * and अगर buffer size करोes not exceeds max value */
	/* XXX: check own ht delayed BA capability?? */
	अगर (((ba_policy != 1) &&
	     (!(sta->sta.ht_cap.cap & IEEE80211_HT_CAP_DELAY_BA))) ||
	    (buf_size > max_buf_size)) अणु
		status = WLAN_STATUS_INVALID_QOS_PARAM;
		ht_dbg_ratelimited(sta->sdata,
				   "AddBA Req with bad params from %pM on tid %u. policy %d, buffer size %d\n",
				   sta->sta.addr, tid, ba_policy, buf_size);
		जाओ end;
	पूर्ण
	/* determine शेष buffer size */
	अगर (buf_size == 0)
		buf_size = max_buf_size;

	/* make sure the size करोesn't exceed the maximum supported by the hw */
	अगर (buf_size > sta->sta.max_rx_aggregation_subframes)
		buf_size = sta->sta.max_rx_aggregation_subframes;
	params.buf_size = buf_size;

	ht_dbg(sta->sdata, "AddBA Req buf_size=%d for %pM\n",
	       buf_size, sta->sta.addr);

	/* examine state machine */
	lockdep_निश्चित_held(&sta->ampdu_mlme.mtx);

	अगर (test_bit(tid, sta->ampdu_mlme.agg_session_valid)) अणु
		अगर (sta->ampdu_mlme.tid_rx_token[tid] == dialog_token) अणु
			काष्ठा tid_ampdu_rx *tid_rx;

			ht_dbg_ratelimited(sta->sdata,
					   "updated AddBA Req from %pM on tid %u\n",
					   sta->sta.addr, tid);
			/* We have no API to update the समयout value in the
			 * driver so reject the समयout update अगर the समयout
			 * changed. If it did not change, i.e., no real update,
			 * just reply with success.
			 */
			rcu_पढ़ो_lock();
			tid_rx = rcu_dereference(sta->ampdu_mlme.tid_rx[tid]);
			अगर (tid_rx && tid_rx->समयout == समयout)
				status = WLAN_STATUS_SUCCESS;
			अन्यथा
				status = WLAN_STATUS_REQUEST_DECLINED;
			rcu_पढ़ो_unlock();
			जाओ end;
		पूर्ण

		ht_dbg_ratelimited(sta->sdata,
				   "unexpected AddBA Req from %pM on tid %u\n",
				   sta->sta.addr, tid);

		/* delete existing Rx BA session on the same tid */
		___ieee80211_stop_rx_ba_session(sta, tid, WLAN_BACK_RECIPIENT,
						WLAN_STATUS_UNSPECIFIED_QOS,
						false);
	पूर्ण

	अगर (ieee80211_hw_check(&local->hw, SUPPORTS_REORDERING_BUFFER)) अणु
		ret = drv_ampdu_action(local, sta->sdata, &params);
		ht_dbg(sta->sdata,
		       "Rx A-MPDU request on %pM tid %d result %d\n",
		       sta->sta.addr, tid, ret);
		अगर (!ret)
			status = WLAN_STATUS_SUCCESS;
		जाओ end;
	पूर्ण

	/* prepare A-MPDU MLME क्रम Rx aggregation */
	tid_agg_rx = kzalloc(माप(*tid_agg_rx), GFP_KERNEL);
	अगर (!tid_agg_rx)
		जाओ end;

	spin_lock_init(&tid_agg_rx->reorder_lock);

	/* rx समयr */
	समयr_setup(&tid_agg_rx->session_समयr,
		    sta_rx_agg_session_समयr_expired, TIMER_DEFERRABLE);

	/* rx reorder समयr */
	समयr_setup(&tid_agg_rx->reorder_समयr,
		    sta_rx_agg_reorder_समयr_expired, 0);

	/* prepare reordering buffer */
	tid_agg_rx->reorder_buf =
		kसुस्मृति(buf_size, माप(काष्ठा sk_buff_head), GFP_KERNEL);
	tid_agg_rx->reorder_समय =
		kसुस्मृति(buf_size, माप(अचिन्हित दीर्घ), GFP_KERNEL);
	अगर (!tid_agg_rx->reorder_buf || !tid_agg_rx->reorder_समय) अणु
		kमुक्त(tid_agg_rx->reorder_buf);
		kमुक्त(tid_agg_rx->reorder_समय);
		kमुक्त(tid_agg_rx);
		जाओ end;
	पूर्ण

	क्रम (i = 0; i < buf_size; i++)
		__skb_queue_head_init(&tid_agg_rx->reorder_buf[i]);

	ret = drv_ampdu_action(local, sta->sdata, &params);
	ht_dbg(sta->sdata, "Rx A-MPDU request on %pM tid %d result %d\n",
	       sta->sta.addr, tid, ret);
	अगर (ret) अणु
		kमुक्त(tid_agg_rx->reorder_buf);
		kमुक्त(tid_agg_rx->reorder_समय);
		kमुक्त(tid_agg_rx);
		जाओ end;
	पूर्ण

	/* update data */
	tid_agg_rx->ssn = start_seq_num;
	tid_agg_rx->head_seq_num = start_seq_num;
	tid_agg_rx->buf_size = buf_size;
	tid_agg_rx->समयout = समयout;
	tid_agg_rx->stored_mpdu_num = 0;
	tid_agg_rx->स्वतः_seq = स्वतः_seq;
	tid_agg_rx->started = false;
	tid_agg_rx->reorder_buf_filtered = 0;
	tid_agg_rx->tid = tid;
	tid_agg_rx->sta = sta;
	status = WLAN_STATUS_SUCCESS;

	/* activate it क्रम RX */
	rcu_assign_poपूर्णांकer(sta->ampdu_mlme.tid_rx[tid], tid_agg_rx);

	अगर (समयout) अणु
		mod_समयr(&tid_agg_rx->session_समयr, TU_TO_EXP_TIME(समयout));
		tid_agg_rx->last_rx = jअगरfies;
	पूर्ण

end:
	अगर (status == WLAN_STATUS_SUCCESS) अणु
		__set_bit(tid, sta->ampdu_mlme.agg_session_valid);
		__clear_bit(tid, sta->ampdu_mlme.unexpected_agg);
		sta->ampdu_mlme.tid_rx_token[tid] = dialog_token;
	पूर्ण

	अगर (tx)
		ieee80211_send_addba_resp(sta, sta->sta.addr, tid,
					  dialog_token, status, 1, buf_size,
					  समयout, addbaext);
पूर्ण

अटल व्योम __ieee80211_start_rx_ba_session(काष्ठा sta_info *sta,
					    u8 dialog_token, u16 समयout,
					    u16 start_seq_num, u16 ba_policy,
					    u16 tid, u16 buf_size, bool tx,
					    bool स्वतः_seq,
					    स्थिर काष्ठा ieee80211_addba_ext_ie *addbaext)
अणु
	mutex_lock(&sta->ampdu_mlme.mtx);
	___ieee80211_start_rx_ba_session(sta, dialog_token, समयout,
					 start_seq_num, ba_policy, tid,
					 buf_size, tx, स्वतः_seq, addbaext);
	mutex_unlock(&sta->ampdu_mlme.mtx);
पूर्ण

व्योम ieee80211_process_addba_request(काष्ठा ieee80211_local *local,
				     काष्ठा sta_info *sta,
				     काष्ठा ieee80211_mgmt *mgmt,
				     माप_प्रकार len)
अणु
	u16 capab, tid, समयout, ba_policy, buf_size, start_seq_num;
	काष्ठा ieee802_11_elems elems = अणु पूर्ण;
	u8 dialog_token;
	पूर्णांक ies_len;

	/* extract session parameters from addba request frame */
	dialog_token = mgmt->u.action.u.addba_req.dialog_token;
	समयout = le16_to_cpu(mgmt->u.action.u.addba_req.समयout);
	start_seq_num =
		le16_to_cpu(mgmt->u.action.u.addba_req.start_seq_num) >> 4;

	capab = le16_to_cpu(mgmt->u.action.u.addba_req.capab);
	ba_policy = (capab & IEEE80211_ADDBA_PARAM_POLICY_MASK) >> 1;
	tid = (capab & IEEE80211_ADDBA_PARAM_TID_MASK) >> 2;
	buf_size = (capab & IEEE80211_ADDBA_PARAM_BUF_SIZE_MASK) >> 6;

	ies_len = len - दुरत्व(काष्ठा ieee80211_mgmt,
				 u.action.u.addba_req.variable);
	अगर (ies_len) अणु
		ieee802_11_parse_elems(mgmt->u.action.u.addba_req.variable,
                                ies_len, true, &elems, mgmt->bssid, शून्य);
		अगर (elems.parse_error)
			वापस;
	पूर्ण

	__ieee80211_start_rx_ba_session(sta, dialog_token, समयout,
					start_seq_num, ba_policy, tid,
					buf_size, true, false,
					elems.addba_ext_ie);
पूर्ण

व्योम ieee80211_manage_rx_ba_offl(काष्ठा ieee80211_vअगर *vअगर,
				 स्थिर u8 *addr, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();
	sta = sta_info_get_bss(sdata, addr);
	अगर (!sta)
		जाओ unlock;

	set_bit(tid, sta->ampdu_mlme.tid_rx_manage_offl);
	ieee80211_queue_work(&local->hw, &sta->ampdu_mlme.work);
 unlock:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_manage_rx_ba_offl);

व्योम ieee80211_rx_ba_समयr_expired(काष्ठा ieee80211_vअगर *vअगर,
				   स्थिर u8 *addr, अचिन्हित पूर्णांक tid)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();
	sta = sta_info_get_bss(sdata, addr);
	अगर (!sta)
		जाओ unlock;

	set_bit(tid, sta->ampdu_mlme.tid_rx_समयr_expired);
	ieee80211_queue_work(&local->hw, &sta->ampdu_mlme.work);

 unlock:
	rcu_पढ़ो_unlock();
पूर्ण
EXPORT_SYMBOL(ieee80211_rx_ba_समयr_expired);
