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
 * Copyright 2017	Intel Deutschland GmbH
 * Copyright(c) 2020 Intel Corporation
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "rate.h"

अटल व्योम __check_htcap_disable(काष्ठा ieee80211_ht_cap *ht_capa,
				  काष्ठा ieee80211_ht_cap *ht_capa_mask,
				  काष्ठा ieee80211_sta_ht_cap *ht_cap,
				  u16 flag)
अणु
	__le16 le_flag = cpu_to_le16(flag);
	अगर (ht_capa_mask->cap_info & le_flag) अणु
		अगर (!(ht_capa->cap_info & le_flag))
			ht_cap->cap &= ~flag;
	पूर्ण
पूर्ण

अटल व्योम __check_htcap_enable(काष्ठा ieee80211_ht_cap *ht_capa,
				  काष्ठा ieee80211_ht_cap *ht_capa_mask,
				  काष्ठा ieee80211_sta_ht_cap *ht_cap,
				  u16 flag)
अणु
	__le16 le_flag = cpu_to_le16(flag);

	अगर ((ht_capa_mask->cap_info & le_flag) &&
	    (ht_capa->cap_info & le_flag))
		ht_cap->cap |= flag;
पूर्ण

व्योम ieee80211_apply_htcap_overrides(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा ieee80211_sta_ht_cap *ht_cap)
अणु
	काष्ठा ieee80211_ht_cap *ht_capa, *ht_capa_mask;
	u8 *scaps, *smask;
	पूर्णांक i;

	अगर (!ht_cap->ht_supported)
		वापस;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
		ht_capa = &sdata->u.mgd.ht_capa;
		ht_capa_mask = &sdata->u.mgd.ht_capa_mask;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ht_capa = &sdata->u.ibss.ht_capa;
		ht_capa_mask = &sdata->u.ibss.ht_capa_mask;
		अवरोध;
	शेष:
		WARN_ON_ONCE(1);
		वापस;
	पूर्ण

	scaps = (u8 *)(&ht_capa->mcs.rx_mask);
	smask = (u8 *)(&ht_capa_mask->mcs.rx_mask);

	/* NOTE:  If you add more over-rides here, update रेजिस्टर_hw
	 * ht_capa_mod_mask logic in मुख्य.c as well.
	 * And, अगर this method can ever change ht_cap.ht_supported, fix
	 * the check in ieee80211_add_ht_ie.
	 */

	/* check क्रम HT over-rides, MCS rates first. */
	क्रम (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++) अणु
		u8 m = smask[i];
		ht_cap->mcs.rx_mask[i] &= ~m; /* turn off all masked bits */
		/* Add back rates that are supported */
		ht_cap->mcs.rx_mask[i] |= (m & scaps[i]);
	पूर्ण

	/* Force removal of HT-40 capabilities? */
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_SUP_WIDTH_20_40);
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_SGI_40);

	/* Allow user to disable SGI-20 (SGI-40 is handled above) */
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_SGI_20);

	/* Allow user to disable the max-AMSDU bit. */
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_MAX_AMSDU);

	/* Allow user to disable LDPC */
	__check_htcap_disable(ht_capa, ht_capa_mask, ht_cap,
			      IEEE80211_HT_CAP_LDPC_CODING);

	/* Allow user to enable 40 MHz पूर्णांकolerant bit. */
	__check_htcap_enable(ht_capa, ht_capa_mask, ht_cap,
			     IEEE80211_HT_CAP_40MHZ_INTOLERANT);

	/* Allow user to enable TX STBC bit  */
	__check_htcap_enable(ht_capa, ht_capa_mask, ht_cap,
			     IEEE80211_HT_CAP_TX_STBC);

	/* Allow user to configure RX STBC bits */
	अगर (ht_capa_mask->cap_info & cpu_to_le16(IEEE80211_HT_CAP_RX_STBC))
		ht_cap->cap |= le16_to_cpu(ht_capa->cap_info) &
					IEEE80211_HT_CAP_RX_STBC;

	/* Allow user to decrease AMPDU factor */
	अगर (ht_capa_mask->ampdu_params_info &
	    IEEE80211_HT_AMPDU_PARM_FACTOR) अणु
		u8 n = ht_capa->ampdu_params_info &
		       IEEE80211_HT_AMPDU_PARM_FACTOR;
		अगर (n < ht_cap->ampdu_factor)
			ht_cap->ampdu_factor = n;
	पूर्ण

	/* Allow the user to increase AMPDU density. */
	अगर (ht_capa_mask->ampdu_params_info &
	    IEEE80211_HT_AMPDU_PARM_DENSITY) अणु
		u8 n = (ht_capa->ampdu_params_info &
			IEEE80211_HT_AMPDU_PARM_DENSITY)
			>> IEEE80211_HT_AMPDU_PARM_DENSITY_SHIFT;
		अगर (n > ht_cap->ampdu_density)
			ht_cap->ampdu_density = n;
	पूर्ण
पूर्ण


bool ieee80211_ht_cap_ie_to_sta_ht_cap(काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_supported_band *sband,
				       स्थिर काष्ठा ieee80211_ht_cap *ht_cap_ie,
				       काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sta_ht_cap ht_cap, own_cap;
	u8 ampdu_info, tx_mcs_set_cap;
	पूर्णांक i, max_tx_streams;
	bool changed;
	क्रमागत ieee80211_sta_rx_bandwidth bw;

	स_रखो(&ht_cap, 0, माप(ht_cap));

	अगर (!ht_cap_ie || !sband->ht_cap.ht_supported)
		जाओ apply;

	ht_cap.ht_supported = true;

	own_cap = sband->ht_cap;

	/*
	 * If user has specअगरied capability over-rides, take care
	 * of that अगर the station we're setting up is the AP or TDLS peer that
	 * we advertised a restricted capability set to. Override
	 * our own capabilities and then use those below.
	 */
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION ||
	    sdata->vअगर.type == NL80211_IFTYPE_ADHOC)
		ieee80211_apply_htcap_overrides(sdata, &own_cap);

	/*
	 * The bits listed in this expression should be
	 * the same क्रम the peer and us, अगर the station
	 * advertises more then we can't use those thus
	 * we mask them out.
	 */
	ht_cap.cap = le16_to_cpu(ht_cap_ie->cap_info) &
		(own_cap.cap | ~(IEEE80211_HT_CAP_LDPC_CODING |
				 IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
				 IEEE80211_HT_CAP_GRN_FLD |
				 IEEE80211_HT_CAP_SGI_20 |
				 IEEE80211_HT_CAP_SGI_40 |
				 IEEE80211_HT_CAP_DSSSCCK40));

	/*
	 * The STBC bits are asymmetric -- अगर we करोn't have
	 * TX then mask out the peer's RX and vice versa.
	 */
	अगर (!(own_cap.cap & IEEE80211_HT_CAP_TX_STBC))
		ht_cap.cap &= ~IEEE80211_HT_CAP_RX_STBC;
	अगर (!(own_cap.cap & IEEE80211_HT_CAP_RX_STBC))
		ht_cap.cap &= ~IEEE80211_HT_CAP_TX_STBC;

	ampdu_info = ht_cap_ie->ampdu_params_info;
	ht_cap.ampdu_factor =
		ampdu_info & IEEE80211_HT_AMPDU_PARM_FACTOR;
	ht_cap.ampdu_density =
		(ampdu_info & IEEE80211_HT_AMPDU_PARM_DENSITY) >> 2;

	/* own MCS TX capabilities */
	tx_mcs_set_cap = own_cap.mcs.tx_params;

	/* Copy peer MCS TX capabilities, the driver might need them. */
	ht_cap.mcs.tx_params = ht_cap_ie->mcs.tx_params;

	/* can we TX with MCS rates? */
	अगर (!(tx_mcs_set_cap & IEEE80211_HT_MCS_TX_DEFINED))
		जाओ apply;

	/* Counting from 0, thereक्रमe +1 */
	अगर (tx_mcs_set_cap & IEEE80211_HT_MCS_TX_RX_DIFF)
		max_tx_streams =
			((tx_mcs_set_cap & IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK)
				>> IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT) + 1;
	अन्यथा
		max_tx_streams = IEEE80211_HT_MCS_TX_MAX_STREAMS;

	/*
	 * 802.11n-2009 20.3.5 / 20.6 says:
	 * - indices 0 to 7 and 32 are single spatial stream
	 * - 8 to 31 are multiple spatial streams using equal modulation
	 *   [8..15 क्रम two streams, 16..23 क्रम three and 24..31 क्रम four]
	 * - reमुख्यder are multiple spatial streams using unequal modulation
	 */
	क्रम (i = 0; i < max_tx_streams; i++)
		ht_cap.mcs.rx_mask[i] =
			own_cap.mcs.rx_mask[i] & ht_cap_ie->mcs.rx_mask[i];

	अगर (tx_mcs_set_cap & IEEE80211_HT_MCS_TX_UNEQUAL_MODULATION)
		क्रम (i = IEEE80211_HT_MCS_UNEQUAL_MODULATION_START_BYTE;
		     i < IEEE80211_HT_MCS_MASK_LEN; i++)
			ht_cap.mcs.rx_mask[i] =
				own_cap.mcs.rx_mask[i] &
					ht_cap_ie->mcs.rx_mask[i];

	/* handle MCS rate 32 too */
	अगर (own_cap.mcs.rx_mask[32/8] & ht_cap_ie->mcs.rx_mask[32/8] & 1)
		ht_cap.mcs.rx_mask[32/8] |= 1;

	/* set Rx highest rate */
	ht_cap.mcs.rx_highest = ht_cap_ie->mcs.rx_highest;

	अगर (ht_cap.cap & IEEE80211_HT_CAP_MAX_AMSDU)
		sta->sta.max_amsdu_len = IEEE80211_MAX_MPDU_LEN_HT_7935;
	अन्यथा
		sta->sta.max_amsdu_len = IEEE80211_MAX_MPDU_LEN_HT_3839;

 apply:
	changed = स_भेद(&sta->sta.ht_cap, &ht_cap, माप(ht_cap));

	स_नकल(&sta->sta.ht_cap, &ht_cap, माप(ht_cap));

	चयन (sdata->vअगर.bss_conf.chandef.width) अणु
	शेष:
		WARN_ON_ONCE(1);
		fallthrough;
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
		bw = IEEE80211_STA_RX_BW_20;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_40:
	हाल NL80211_CHAN_WIDTH_80:
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
		bw = ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 ?
				IEEE80211_STA_RX_BW_40 : IEEE80211_STA_RX_BW_20;
		अवरोध;
	पूर्ण

	sta->sta.bandwidth = bw;

	sta->cur_max_bandwidth =
		ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40 ?
				IEEE80211_STA_RX_BW_40 : IEEE80211_STA_RX_BW_20;

	अगर (sta->sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    sta->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		क्रमागत ieee80211_smps_mode smps_mode;

		चयन ((ht_cap.cap & IEEE80211_HT_CAP_SM_PS)
				>> IEEE80211_HT_CAP_SM_PS_SHIFT) अणु
		हाल WLAN_HT_CAP_SM_PS_INVALID:
		हाल WLAN_HT_CAP_SM_PS_STATIC:
			smps_mode = IEEE80211_SMPS_STATIC;
			अवरोध;
		हाल WLAN_HT_CAP_SM_PS_DYNAMIC:
			smps_mode = IEEE80211_SMPS_DYNAMIC;
			अवरोध;
		हाल WLAN_HT_CAP_SM_PS_DISABLED:
			smps_mode = IEEE80211_SMPS_OFF;
			अवरोध;
		पूर्ण

		अगर (smps_mode != sta->sta.smps_mode)
			changed = true;
		sta->sta.smps_mode = smps_mode;
	पूर्ण अन्यथा अणु
		sta->sta.smps_mode = IEEE80211_SMPS_OFF;
	पूर्ण
	वापस changed;
पूर्ण

व्योम ieee80211_sta_tear_करोwn_BA_sessions(काष्ठा sta_info *sta,
					 क्रमागत ieee80211_agg_stop_reason reason)
अणु
	पूर्णांक i;

	mutex_lock(&sta->ampdu_mlme.mtx);
	क्रम (i = 0; i <  IEEE80211_NUM_TIDS; i++)
		___ieee80211_stop_rx_ba_session(sta, i, WLAN_BACK_RECIPIENT,
						WLAN_REASON_QSTA_LEAVE_QBSS,
						reason != AGG_STOP_DESTROY_STA &&
						reason != AGG_STOP_PEER_REQUEST);

	क्रम (i = 0; i <  IEEE80211_NUM_TIDS; i++)
		___ieee80211_stop_tx_ba_session(sta, i, reason);
	mutex_unlock(&sta->ampdu_mlme.mtx);

	/*
	 * In हाल the tear करोwn is part of a reconfigure due to HW restart
	 * request, it is possible that the low level driver requested to stop
	 * the BA session, so handle it to properly clean tid_tx data.
	 */
	अगर(reason == AGG_STOP_DESTROY_STA) अणु
		cancel_work_sync(&sta->ampdu_mlme.work);

		mutex_lock(&sta->ampdu_mlme.mtx);
		क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++) अणु
			काष्ठा tid_ampdu_tx *tid_tx =
				rcu_dereference_रक्षित_tid_tx(sta, i);

			अगर (!tid_tx)
				जारी;

			अगर (test_and_clear_bit(HT_AGG_STATE_STOP_CB, &tid_tx->state))
				ieee80211_stop_tx_ba_cb(sta, i, tid_tx);
		पूर्ण
		mutex_unlock(&sta->ampdu_mlme.mtx);
	पूर्ण
पूर्ण

व्योम ieee80211_ba_session_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा sta_info *sta =
		container_of(work, काष्ठा sta_info, ampdu_mlme.work);
	काष्ठा tid_ampdu_tx *tid_tx;
	bool blocked;
	पूर्णांक tid;

	/* When this flag is set, new sessions should be blocked. */
	blocked = test_sta_flag(sta, WLAN_STA_BLOCK_BA);

	mutex_lock(&sta->ampdu_mlme.mtx);
	क्रम (tid = 0; tid < IEEE80211_NUM_TIDS; tid++) अणु
		अगर (test_and_clear_bit(tid, sta->ampdu_mlme.tid_rx_समयr_expired))
			___ieee80211_stop_rx_ba_session(
				sta, tid, WLAN_BACK_RECIPIENT,
				WLAN_REASON_QSTA_TIMEOUT, true);

		अगर (test_and_clear_bit(tid,
				       sta->ampdu_mlme.tid_rx_stop_requested))
			___ieee80211_stop_rx_ba_session(
				sta, tid, WLAN_BACK_RECIPIENT,
				WLAN_REASON_UNSPECIFIED, true);

		अगर (!blocked &&
		    test_and_clear_bit(tid,
				       sta->ampdu_mlme.tid_rx_manage_offl))
			___ieee80211_start_rx_ba_session(sta, 0, 0, 0, 1, tid,
							 IEEE80211_MAX_AMPDU_BUF_HT,
							 false, true, शून्य);

		अगर (test_and_clear_bit(tid + IEEE80211_NUM_TIDS,
				       sta->ampdu_mlme.tid_rx_manage_offl))
			___ieee80211_stop_rx_ba_session(
				sta, tid, WLAN_BACK_RECIPIENT,
				0, false);

		spin_lock_bh(&sta->lock);

		tid_tx = sta->ampdu_mlme.tid_start_tx[tid];
		अगर (!blocked && tid_tx) अणु
			/*
			 * Assign it over to the normal tid_tx array
			 * where it "goes live".
			 */

			sta->ampdu_mlme.tid_start_tx[tid] = शून्य;
			/* could there be a race? */
			अगर (sta->ampdu_mlme.tid_tx[tid])
				kमुक्त(tid_tx);
			अन्यथा
				ieee80211_assign_tid_tx(sta, tid, tid_tx);
			spin_unlock_bh(&sta->lock);

			ieee80211_tx_ba_session_handle_start(sta, tid);
			जारी;
		पूर्ण
		spin_unlock_bh(&sta->lock);

		tid_tx = rcu_dereference_रक्षित_tid_tx(sta, tid);
		अगर (!tid_tx)
			जारी;

		अगर (!blocked &&
		    test_and_clear_bit(HT_AGG_STATE_START_CB, &tid_tx->state))
			ieee80211_start_tx_ba_cb(sta, tid, tid_tx);
		अगर (test_and_clear_bit(HT_AGG_STATE_WANT_STOP, &tid_tx->state))
			___ieee80211_stop_tx_ba_session(sta, tid,
							AGG_STOP_LOCAL_REQUEST);
		अगर (test_and_clear_bit(HT_AGG_STATE_STOP_CB, &tid_tx->state))
			ieee80211_stop_tx_ba_cb(sta, tid, tid_tx);
	पूर्ण
	mutex_unlock(&sta->ampdu_mlme.mtx);
पूर्ण

व्योम ieee80211_send_delba(काष्ठा ieee80211_sub_अगर_data *sdata,
			  स्थिर u8 *da, u16 tid,
			  u16 initiator, u16 reason_code)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *mgmt;
	u16 params;

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

	skb_put(skb, 1 + माप(mgmt->u.action.u.delba));

	mgmt->u.action.category = WLAN_CATEGORY_BACK;
	mgmt->u.action.u.delba.action_code = WLAN_ACTION_DELBA;
	params = (u16)(initiator << 11); 	/* bit 11 initiator */
	params |= (u16)(tid << 12); 		/* bit 15:12 TID number */

	mgmt->u.action.u.delba.params = cpu_to_le16(params);
	mgmt->u.action.u.delba.reason_code = cpu_to_le16(reason_code);

	ieee80211_tx_skb(sdata, skb);
पूर्ण

व्योम ieee80211_process_delba(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा sta_info *sta,
			     काष्ठा ieee80211_mgmt *mgmt, माप_प्रकार len)
अणु
	u16 tid, params;
	u16 initiator;

	params = le16_to_cpu(mgmt->u.action.u.delba.params);
	tid = (params & IEEE80211_DELBA_PARAM_TID_MASK) >> 12;
	initiator = (params & IEEE80211_DELBA_PARAM_INITIATOR_MASK) >> 11;

	ht_dbg_ratelimited(sdata, "delba from %pM (%s) tid %d reason code %d\n",
			   mgmt->sa, initiator ? "initiator" : "recipient",
			   tid,
			   le16_to_cpu(mgmt->u.action.u.delba.reason_code));

	अगर (initiator == WLAN_BACK_INITIATOR)
		__ieee80211_stop_rx_ba_session(sta, tid, WLAN_BACK_INITIATOR, 0,
					       true);
	अन्यथा
		__ieee80211_stop_tx_ba_session(sta, tid, AGG_STOP_PEER_REQUEST);
पूर्ण

क्रमागत nl80211_smps_mode
ieee80211_smps_mode_to_smps_mode(क्रमागत ieee80211_smps_mode smps)
अणु
	चयन (smps) अणु
	हाल IEEE80211_SMPS_OFF:
		वापस NL80211_SMPS_OFF;
	हाल IEEE80211_SMPS_STATIC:
		वापस NL80211_SMPS_STATIC;
	हाल IEEE80211_SMPS_DYNAMIC:
		वापस NL80211_SMPS_DYNAMIC;
	शेष:
		वापस NL80211_SMPS_OFF;
	पूर्ण
पूर्ण

पूर्णांक ieee80211_send_smps_action(काष्ठा ieee80211_sub_अगर_data *sdata,
			       क्रमागत ieee80211_smps_mode smps, स्थिर u8 *da,
			       स्थिर u8 *bssid)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *action_frame;

	/* 27 = header + category + action + smps mode */
	skb = dev_alloc_skb(27 + local->hw.extra_tx_headroom);
	अगर (!skb)
		वापस -ENOMEM;

	skb_reserve(skb, local->hw.extra_tx_headroom);
	action_frame = skb_put(skb, 27);
	स_नकल(action_frame->da, da, ETH_ALEN);
	स_नकल(action_frame->sa, sdata->dev->dev_addr, ETH_ALEN);
	स_नकल(action_frame->bssid, bssid, ETH_ALEN);
	action_frame->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						  IEEE80211_STYPE_ACTION);
	action_frame->u.action.category = WLAN_CATEGORY_HT;
	action_frame->u.action.u.ht_smps.action = WLAN_HT_ACTION_SMPS;
	चयन (smps) अणु
	हाल IEEE80211_SMPS_AUTOMATIC:
	हाल IEEE80211_SMPS_NUM_MODES:
		WARN_ON(1);
		fallthrough;
	हाल IEEE80211_SMPS_OFF:
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_DISABLED;
		अवरोध;
	हाल IEEE80211_SMPS_STATIC:
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_STATIC;
		अवरोध;
	हाल IEEE80211_SMPS_DYNAMIC:
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_DYNAMIC;
		अवरोध;
	पूर्ण

	/* we'll करो more on status of this frame */
	IEEE80211_SKB_CB(skb)->flags |= IEEE80211_TX_CTL_REQ_TX_STATUS;
	ieee80211_tx_skb(sdata, skb);

	वापस 0;
पूर्ण

व्योम ieee80211_request_smps_mgd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data,
			     u.mgd.request_smps_work);

	sdata_lock(sdata);
	__ieee80211_request_smps_mgd(sdata, sdata->u.mgd.driver_smps_mode);
	sdata_unlock(sdata);
पूर्ण

व्योम ieee80211_request_smps(काष्ठा ieee80211_vअगर *vअगर,
			    क्रमागत ieee80211_smps_mode smps_mode)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	अगर (WARN_ON_ONCE(vअगर->type != NL80211_IFTYPE_STATION &&
			 vअगर->type != NL80211_IFTYPE_AP))
		वापस;

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		अगर (sdata->u.mgd.driver_smps_mode == smps_mode)
			वापस;
		sdata->u.mgd.driver_smps_mode = smps_mode;
		ieee80211_queue_work(&sdata->local->hw,
				     &sdata->u.mgd.request_smps_work);
	पूर्ण
पूर्ण
/* this might change ... करोn't want non-खोलो drivers using it */
EXPORT_SYMBOL_GPL(ieee80211_request_smps);
