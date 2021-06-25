<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright (C) 2015 - 2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/init.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/types.h>
#समावेश <linux/slab.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/समयr.h>
#समावेश <linux/rtnetlink.h>

#समावेश <net/codel.h>
#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"
#समावेश "sta_info.h"
#समावेश "debugfs_sta.h"
#समावेश "mesh.h"
#समावेश "wme.h"

/**
 * DOC: STA inक्रमmation lअगरeसमय rules
 *
 * STA info काष्ठाures (&काष्ठा sta_info) are managed in a hash table
 * क्रम faster lookup and a list क्रम iteration. They are managed using
 * RCU, i.e. access to the list and hash table is रक्षित by RCU.
 *
 * Upon allocating a STA info काष्ठाure with sta_info_alloc(), the caller
 * owns that काष्ठाure. It must then insert it पूर्णांकo the hash table using
 * either sta_info_insert() or sta_info_insert_rcu(); only in the latter
 * हाल (which acquires an rcu पढ़ो section but must not be called from
 * within one) will the poपूर्णांकer still be valid after the call. Note that
 * the caller may not करो much with the STA info beक्रमe inserting it, in
 * particular, it may not start any mesh peer link management or add
 * encryption keys.
 *
 * When the insertion fails (sta_info_insert()) वापसs non-zero), the
 * काष्ठाure will have been मुक्तd by sta_info_insert()!
 *
 * Station entries are added by mac80211 when you establish a link with a
 * peer. This means dअगरferent things क्रम the dअगरferent type of पूर्णांकerfaces
 * we support. For a regular station this mean we add the AP sta when we
 * receive an association response from the AP. For IBSS this occurs when
 * get to know about a peer on the same IBSS. For WDS we add the sta क्रम
 * the peer immediately upon device खोलो. When using AP mode we add stations
 * क्रम each respective station upon request from userspace through nl80211.
 *
 * In order to हटाओ a STA info काष्ठाure, various sta_info_destroy_*()
 * calls are available.
 *
 * There is no concept of ownership on a STA entry, each काष्ठाure is
 * owned by the global hash table/list until it is हटाओd. All users of
 * the काष्ठाure need to be RCU रक्षित so that the काष्ठाure won't be
 * मुक्तd beक्रमe they are करोne using it.
 */

अटल स्थिर काष्ठा rhashtable_params sta_rht_params = अणु
	.nelem_hपूर्णांक = 3, /* start small */
	.स्वतःmatic_shrinking = true,
	.head_offset = दुरत्व(काष्ठा sta_info, hash_node),
	.key_offset = दुरत्व(काष्ठा sta_info, addr),
	.key_len = ETH_ALEN,
	.max_size = CONFIG_MAC80211_STA_HASH_MAX_SIZE,
पूर्ण;

/* Caller must hold local->sta_mtx */
अटल पूर्णांक sta_info_hash_del(काष्ठा ieee80211_local *local,
			     काष्ठा sta_info *sta)
अणु
	वापस rhltable_हटाओ(&local->sta_hash, &sta->hash_node,
			       sta_rht_params);
पूर्ण

अटल व्योम __cleanup_single_sta(काष्ठा sta_info *sta)
अणु
	पूर्णांक ac, i;
	काष्ठा tid_ampdu_tx *tid_tx;
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ps_data *ps;

	अगर (test_sta_flag(sta, WLAN_STA_PS_STA) ||
	    test_sta_flag(sta, WLAN_STA_PS_DRIVER) ||
	    test_sta_flag(sta, WLAN_STA_PS_DELIVER)) अणु
		अगर (sta->sdata->vअगर.type == NL80211_IFTYPE_AP ||
		    sta->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
			ps = &sdata->bss->ps;
		अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
			ps = &sdata->u.mesh.ps;
		अन्यथा
			वापस;

		clear_sta_flag(sta, WLAN_STA_PS_STA);
		clear_sta_flag(sta, WLAN_STA_PS_DRIVER);
		clear_sta_flag(sta, WLAN_STA_PS_DELIVER);

		atomic_dec(&ps->num_sta_ps);
	पूर्ण

	अगर (sta->sta.txq[0]) अणु
		क्रम (i = 0; i < ARRAY_SIZE(sta->sta.txq); i++) अणु
			काष्ठा txq_info *txqi;

			अगर (!sta->sta.txq[i])
				जारी;

			txqi = to_txq_info(sta->sta.txq[i]);

			ieee80211_txq_purge(local, txqi);
		पूर्ण
	पूर्ण

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		local->total_ps_buffered -= skb_queue_len(&sta->ps_tx_buf[ac]);
		ieee80211_purge_tx_queue(&local->hw, &sta->ps_tx_buf[ac]);
		ieee80211_purge_tx_queue(&local->hw, &sta->tx_filtered[ac]);
	पूर्ण

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
		mesh_sta_cleanup(sta);

	cancel_work_sync(&sta->drv_deliver_wk);

	/*
	 * Destroy aggregation state here. It would be nice to रुको क्रम the
	 * driver to finish aggregation stop and then clean up, but क्रम now
	 * drivers have to handle aggregation stop being requested, followed
	 * directly by station deकाष्ठाion.
	 */
	क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++) अणु
		kमुक्त(sta->ampdu_mlme.tid_start_tx[i]);
		tid_tx = rcu_dereference_raw(sta->ampdu_mlme.tid_tx[i]);
		अगर (!tid_tx)
			जारी;
		ieee80211_purge_tx_queue(&local->hw, &tid_tx->pending);
		kमुक्त(tid_tx);
	पूर्ण
पूर्ण

अटल व्योम cleanup_single_sta(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;

	__cleanup_single_sta(sta);
	sta_info_मुक्त(local, sta);
पूर्ण

काष्ठा rhlist_head *sta_info_hash_lookup(काष्ठा ieee80211_local *local,
					 स्थिर u8 *addr)
अणु
	वापस rhltable_lookup(&local->sta_hash, addr, sta_rht_params);
पूर्ण

/* रक्षित by RCU */
काष्ठा sta_info *sta_info_get(काष्ठा ieee80211_sub_अगर_data *sdata,
			      स्थिर u8 *addr)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा rhlist_head *पंचांगp;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();
	क्रम_each_sta_info(local, addr, sta, पंचांगp) अणु
		अगर (sta->sdata == sdata) अणु
			rcu_पढ़ो_unlock();
			/* this is safe as the caller must alपढ़ोy hold
			 * another rcu पढ़ो section or the mutex
			 */
			वापस sta;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

/*
 * Get sta info either from the specअगरied पूर्णांकerface
 * or from one of its vlans
 */
काष्ठा sta_info *sta_info_get_bss(काष्ठा ieee80211_sub_अगर_data *sdata,
				  स्थिर u8 *addr)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा rhlist_head *पंचांगp;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();
	क्रम_each_sta_info(local, addr, sta, पंचांगp) अणु
		अगर (sta->sdata == sdata ||
		    (sta->sdata->bss && sta->sdata->bss == sdata->bss)) अणु
			rcu_पढ़ो_unlock();
			/* this is safe as the caller must alपढ़ोy hold
			 * another rcu पढ़ो section or the mutex
			 */
			वापस sta;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();
	वापस शून्य;
पूर्ण

काष्ठा sta_info *sta_info_get_by_addrs(काष्ठा ieee80211_local *local,
				       स्थिर u8 *sta_addr, स्थिर u8 *vअगर_addr)
अणु
	काष्ठा rhlist_head *पंचांगp;
	काष्ठा sta_info *sta;

	क्रम_each_sta_info(local, sta_addr, sta, पंचांगp) अणु
		अगर (ether_addr_equal(vअगर_addr, sta->sdata->vअगर.addr))
			वापस sta;
	पूर्ण

	वापस शून्य;
पूर्ण

काष्ठा sta_info *sta_info_get_by_idx(काष्ठा ieee80211_sub_अगर_data *sdata,
				     पूर्णांक idx)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	पूर्णांक i = 0;

	list_क्रम_each_entry_rcu(sta, &local->sta_list, list,
				lockdep_is_held(&local->sta_mtx)) अणु
		अगर (sdata != sta->sdata)
			जारी;
		अगर (i < idx) अणु
			++i;
			जारी;
		पूर्ण
		वापस sta;
	पूर्ण

	वापस शून्य;
पूर्ण

/**
 * sta_info_मुक्त - मुक्त STA
 *
 * @local: poपूर्णांकer to the global inक्रमmation
 * @sta: STA info to मुक्त
 *
 * This function must unकरो everything करोne by sta_info_alloc()
 * that may happen beक्रमe sta_info_insert(). It may only be
 * called when sta_info_insert() has not been attempted (and
 * अगर that fails, the station is मुक्तd anyway.)
 */
व्योम sta_info_मुक्त(काष्ठा ieee80211_local *local, काष्ठा sta_info *sta)
अणु
	/*
	 * If we had used sta_info_pre_move_state() then we might not
	 * have gone through the state transitions करोwn again, so करो
	 * it here now (and warn अगर it's inserted).
	 *
	 * This will clear state such as fast TX/RX that may have been
	 * allocated during state transitions.
	 */
	जबतक (sta->sta_state > IEEE80211_STA_NONE) अणु
		पूर्णांक ret;

		WARN_ON_ONCE(test_sta_flag(sta, WLAN_STA_INSERTED));

		ret = sta_info_move_state(sta, sta->sta_state - 1);
		अगर (WARN_ONCE(ret, "sta_info_move_state() returned %d\n", ret))
			अवरोध;
	पूर्ण

	अगर (sta->rate_ctrl)
		rate_control_मुक्त_sta(sta);

	sta_dbg(sta->sdata, "Destroyed STA %pM\n", sta->sta.addr);

	अगर (sta->sta.txq[0])
		kमुक्त(to_txq_info(sta->sta.txq[0]));
	kमुक्त(rcu_dereference_raw(sta->sta.rates));
#अगर_घोषित CONFIG_MAC80211_MESH
	kमुक्त(sta->mesh);
#पूर्ण_अगर
	मुक्त_percpu(sta->pcpu_rx_stats);
	kमुक्त(sta);
पूर्ण

/* Caller must hold local->sta_mtx */
अटल पूर्णांक sta_info_hash_add(काष्ठा ieee80211_local *local,
			     काष्ठा sta_info *sta)
अणु
	वापस rhltable_insert(&local->sta_hash, &sta->hash_node,
			       sta_rht_params);
पूर्ण

अटल व्योम sta_deliver_ps_frames(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा sta_info *sta;

	sta = container_of(wk, काष्ठा sta_info, drv_deliver_wk);

	अगर (sta->dead)
		वापस;

	local_bh_disable();
	अगर (!test_sta_flag(sta, WLAN_STA_PS_STA))
		ieee80211_sta_ps_deliver_wakeup(sta);
	अन्यथा अगर (test_and_clear_sta_flag(sta, WLAN_STA_PSPOLL))
		ieee80211_sta_ps_deliver_poll_response(sta);
	अन्यथा अगर (test_and_clear_sta_flag(sta, WLAN_STA_UAPSD))
		ieee80211_sta_ps_deliver_uapsd(sta);
	local_bh_enable();
पूर्ण

अटल पूर्णांक sta_prepare_rate_control(काष्ठा ieee80211_local *local,
				    काष्ठा sta_info *sta, gfp_t gfp)
अणु
	अगर (ieee80211_hw_check(&local->hw, HAS_RATE_CONTROL))
		वापस 0;

	sta->rate_ctrl = local->rate_ctrl;
	sta->rate_ctrl_priv = rate_control_alloc_sta(sta->rate_ctrl,
						     sta, gfp);
	अगर (!sta->rate_ctrl_priv)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

काष्ठा sta_info *sta_info_alloc(काष्ठा ieee80211_sub_अगर_data *sdata,
				स्थिर u8 *addr, gfp_t gfp)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_hw *hw = &local->hw;
	काष्ठा sta_info *sta;
	पूर्णांक i;

	sta = kzalloc(माप(*sta) + hw->sta_data_size, gfp);
	अगर (!sta)
		वापस शून्य;

	अगर (ieee80211_hw_check(hw, USES_RSS)) अणु
		sta->pcpu_rx_stats =
			alloc_percpu_gfp(काष्ठा ieee80211_sta_rx_stats, gfp);
		अगर (!sta->pcpu_rx_stats)
			जाओ मुक्त;
	पूर्ण

	spin_lock_init(&sta->lock);
	spin_lock_init(&sta->ps_lock);
	INIT_WORK(&sta->drv_deliver_wk, sta_deliver_ps_frames);
	INIT_WORK(&sta->ampdu_mlme.work, ieee80211_ba_session_work);
	mutex_init(&sta->ampdu_mlme.mtx);
#अगर_घोषित CONFIG_MAC80211_MESH
	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		sta->mesh = kzalloc(माप(*sta->mesh), gfp);
		अगर (!sta->mesh)
			जाओ मुक्त;
		sta->mesh->plink_sta = sta;
		spin_lock_init(&sta->mesh->plink_lock);
		अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर) &&
		    !sdata->u.mesh.user_mpm)
			समयr_setup(&sta->mesh->plink_समयr, mesh_plink_समयr,
				    0);
		sta->mesh->nonpeer_pm = NL80211_MESH_POWER_ACTIVE;
	पूर्ण
#पूर्ण_अगर

	स_नकल(sta->addr, addr, ETH_ALEN);
	स_नकल(sta->sta.addr, addr, ETH_ALEN);
	sta->sta.max_rx_aggregation_subframes =
		local->hw.max_rx_aggregation_subframes;

	/* Extended Key ID needs to install keys क्रम keyid 0 and 1 Rx-only.
	 * The Tx path starts to use a key as soon as the key slot ptk_idx
	 * references to is not शून्य. To not use the initial Rx-only key
	 * prematurely क्रम Tx initialize ptk_idx to an impossible PTK keyid
	 * which always will refer to a शून्य key.
	 */
	BUILD_BUG_ON(ARRAY_SIZE(sta->ptk) <= INVALID_PTK_KEYIDX);
	sta->ptk_idx = INVALID_PTK_KEYIDX;

	sta->local = local;
	sta->sdata = sdata;
	sta->rx_stats.last_rx = jअगरfies;

	u64_stats_init(&sta->rx_stats.syncp);

	ieee80211_init_frag_cache(&sta->frags);

	sta->sta_state = IEEE80211_STA_NONE;

	/* Mark TID as unreserved */
	sta->reserved_tid = IEEE80211_TID_UNRESERVED;

	sta->last_connected = kसमय_get_seconds();
	ewma_संकेत_init(&sta->rx_stats_avg.संकेत);
	ewma_avg_संकेत_init(&sta->status_stats.avg_ack_संकेत);
	क्रम (i = 0; i < ARRAY_SIZE(sta->rx_stats_avg.chain_संकेत); i++)
		ewma_संकेत_init(&sta->rx_stats_avg.chain_संकेत[i]);

	अगर (local->ops->wake_tx_queue) अणु
		व्योम *txq_data;
		पूर्णांक size = माप(काष्ठा txq_info) +
			   ALIGN(hw->txq_data_size, माप(व्योम *));

		txq_data = kसुस्मृति(ARRAY_SIZE(sta->sta.txq), size, gfp);
		अगर (!txq_data)
			जाओ मुक्त;

		क्रम (i = 0; i < ARRAY_SIZE(sta->sta.txq); i++) अणु
			काष्ठा txq_info *txq = txq_data + i * size;

			/* might not करो anything क्रम the bufferable MMPDU TXQ */
			ieee80211_txq_init(sdata, sta, txq, i);
		पूर्ण
	पूर्ण

	अगर (sta_prepare_rate_control(local, sta, gfp))
		जाओ मुक्त_txq;

	sta->airसमय_weight = IEEE80211_DEFAULT_AIRTIME_WEIGHT;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		skb_queue_head_init(&sta->ps_tx_buf[i]);
		skb_queue_head_init(&sta->tx_filtered[i]);
		sta->airसमय[i].deficit = sta->airसमय_weight;
		atomic_set(&sta->airसमय[i].aql_tx_pending, 0);
		sta->airसमय[i].aql_limit_low = local->aql_txq_limit_low[i];
		sta->airसमय[i].aql_limit_high = local->aql_txq_limit_high[i];
	पूर्ण

	क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++)
		sta->last_seq_ctrl[i] = cpu_to_le16(अच_लघु_उच्च);

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		u32 mandatory = 0;
		पूर्णांक r;

		अगर (!hw->wiphy->bands[i])
			जारी;

		चयन (i) अणु
		हाल NL80211_BAND_2GHZ:
			/*
			 * We use both here, even अगर we cannot really know क्रम
			 * sure the station will support both, but the only use
			 * क्रम this is when we करोn't know anything yet and send
			 * management frames, and then we'll pick the lowest
			 * possible rate anyway.
			 * If we करोn't include _G here, we cannot find a rate
			 * in P2P, and thus trigger the WARN_ONCE() in rate.c
			 */
			mandatory = IEEE80211_RATE_MANDATORY_B |
				    IEEE80211_RATE_MANDATORY_G;
			अवरोध;
		हाल NL80211_BAND_5GHZ:
			mandatory = IEEE80211_RATE_MANDATORY_A;
			अवरोध;
		हाल NL80211_BAND_60GHZ:
			WARN_ON(1);
			mandatory = 0;
			अवरोध;
		पूर्ण

		क्रम (r = 0; r < hw->wiphy->bands[i]->n_bitrates; r++) अणु
			काष्ठा ieee80211_rate *rate;

			rate = &hw->wiphy->bands[i]->bitrates[r];

			अगर (!(rate->flags & mandatory))
				जारी;
			sta->sta.supp_rates[i] |= BIT(r);
		पूर्ण
	पूर्ण

	sta->sta.smps_mode = IEEE80211_SMPS_OFF;
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		काष्ठा ieee80211_supported_band *sband;
		u8 smps;

		sband = ieee80211_get_sband(sdata);
		अगर (!sband)
			जाओ मुक्त_txq;

		smps = (sband->ht_cap.cap & IEEE80211_HT_CAP_SM_PS) >>
			IEEE80211_HT_CAP_SM_PS_SHIFT;
		/*
		 * Assume that hostapd advertises our caps in the beacon and
		 * this is the known_smps_mode क्रम a station that just assciated
		 */
		चयन (smps) अणु
		हाल WLAN_HT_SMPS_CONTROL_DISABLED:
			sta->known_smps_mode = IEEE80211_SMPS_OFF;
			अवरोध;
		हाल WLAN_HT_SMPS_CONTROL_STATIC:
			sta->known_smps_mode = IEEE80211_SMPS_STATIC;
			अवरोध;
		हाल WLAN_HT_SMPS_CONTROL_DYNAMIC:
			sta->known_smps_mode = IEEE80211_SMPS_DYNAMIC;
			अवरोध;
		शेष:
			WARN_ON(1);
		पूर्ण
	पूर्ण

	sta->sta.max_rc_amsdu_len = IEEE80211_MAX_MPDU_LEN_HT_BA;

	sta->cparams.ce_threshold = CODEL_DISABLED_THRESHOLD;
	sta->cparams.target = MS2TIME(20);
	sta->cparams.पूर्णांकerval = MS2TIME(100);
	sta->cparams.ecn = true;

	sta_dbg(sdata, "Allocated STA %pM\n", sta->sta.addr);

	वापस sta;

मुक्त_txq:
	अगर (sta->sta.txq[0])
		kमुक्त(to_txq_info(sta->sta.txq[0]));
मुक्त:
	मुक्त_percpu(sta->pcpu_rx_stats);
#अगर_घोषित CONFIG_MAC80211_MESH
	kमुक्त(sta->mesh);
#पूर्ण_अगर
	kमुक्त(sta);
	वापस शून्य;
पूर्ण

अटल पूर्णांक sta_info_insert_check(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;

	/*
	 * Can't be a WARN_ON because it can be triggered through a race:
	 * something inserts a STA (on one CPU) without holding the RTNL
	 * and another CPU turns off the net device.
	 */
	अगर (unlikely(!ieee80211_sdata_running(sdata)))
		वापस -ENETDOWN;

	अगर (WARN_ON(ether_addr_equal(sta->sta.addr, sdata->vअगर.addr) ||
		    is_multicast_ether_addr(sta->sta.addr)))
		वापस -EINVAL;

	/* The RCU पढ़ो lock is required by rhashtable due to
	 * asynchronous resize/rehash.  We also require the mutex
	 * क्रम correctness.
	 */
	rcu_पढ़ो_lock();
	lockdep_निश्चित_held(&sdata->local->sta_mtx);
	अगर (ieee80211_hw_check(&sdata->local->hw, NEEDS_UNIQUE_STA_ADDR) &&
	    ieee80211_find_sta_by_अगरaddr(&sdata->local->hw, sta->addr, शून्य)) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOTUNIQ;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक sta_info_insert_drv_state(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा sta_info *sta)
अणु
	क्रमागत ieee80211_sta_state state;
	पूर्णांक err = 0;

	क्रम (state = IEEE80211_STA_NOTEXIST; state < sta->sta_state; state++) अणु
		err = drv_sta_state(local, sdata, sta, state, state + 1);
		अगर (err)
			अवरोध;
	पूर्ण

	अगर (!err) अणु
		/*
		 * Drivers using legacy sta_add/sta_हटाओ callbacks only
		 * get uploaded set to true after sta_add is called.
		 */
		अगर (!local->ops->sta_add)
			sta->uploaded = true;
		वापस 0;
	पूर्ण

	अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC) अणु
		sdata_info(sdata,
			   "failed to move IBSS STA %pM to state %d (%d) - keeping it anyway\n",
			   sta->sta.addr, state + 1, err);
		err = 0;
	पूर्ण

	/* unwind on error */
	क्रम (; state > IEEE80211_STA_NOTEXIST; state--)
		WARN_ON(drv_sta_state(local, sdata, sta, state, state - 1));

	वापस err;
पूर्ण

अटल व्योम
ieee80211_recalc_p2p_go_ps_allowed(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	bool allow_p2p_go_ps = sdata->vअगर.p2p;
	काष्ठा sta_info *sta;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &local->sta_list, list) अणु
		अगर (sdata != sta->sdata ||
		    !test_sta_flag(sta, WLAN_STA_ASSOC))
			जारी;
		अगर (!sta->sta.support_p2p_ps) अणु
			allow_p2p_go_ps = false;
			अवरोध;
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (allow_p2p_go_ps != sdata->vअगर.bss_conf.allow_p2p_go_ps) अणु
		sdata->vअगर.bss_conf.allow_p2p_go_ps = allow_p2p_go_ps;
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_P2P_PS);
	पूर्ण
पूर्ण

/*
 * should be called with sta_mtx locked
 * this function replaces the mutex lock
 * with a RCU lock
 */
अटल पूर्णांक sta_info_insert_finish(काष्ठा sta_info *sta) __acquires(RCU)
अणु
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा station_info *sinfo = शून्य;
	पूर्णांक err = 0;

	lockdep_निश्चित_held(&local->sta_mtx);

	/* check अगर STA exists alपढ़ोy */
	अगर (sta_info_get_bss(sdata, sta->sta.addr)) अणु
		err = -EEXIST;
		जाओ out_err;
	पूर्ण

	sinfo = kzalloc(माप(काष्ठा station_info), GFP_KERNEL);
	अगर (!sinfo) अणु
		err = -ENOMEM;
		जाओ out_err;
	पूर्ण

	local->num_sta++;
	local->sta_generation++;
	smp_mb();

	/* simplअगरy things and करोn't accept BA sessions yet */
	set_sta_flag(sta, WLAN_STA_BLOCK_BA);

	/* make the station visible */
	err = sta_info_hash_add(local, sta);
	अगर (err)
		जाओ out_drop_sta;

	list_add_tail_rcu(&sta->list, &local->sta_list);

	/* notअगरy driver */
	err = sta_info_insert_drv_state(local, sdata, sta);
	अगर (err)
		जाओ out_हटाओ;

	set_sta_flag(sta, WLAN_STA_INSERTED);

	अगर (sta->sta_state >= IEEE80211_STA_ASSOC) अणु
		ieee80211_recalc_min_chandef(sta->sdata);
		अगर (!sta->sta.support_p2p_ps)
			ieee80211_recalc_p2p_go_ps_allowed(sta->sdata);
	पूर्ण

	/* accept BA sessions now */
	clear_sta_flag(sta, WLAN_STA_BLOCK_BA);

	ieee80211_sta_debugfs_add(sta);
	rate_control_add_sta_debugfs(sta);

	sinfo->generation = local->sta_generation;
	cfg80211_new_sta(sdata->dev, sta->sta.addr, sinfo, GFP_KERNEL);
	kमुक्त(sinfo);

	sta_dbg(sdata, "Inserted STA %pM\n", sta->sta.addr);

	/* move reference to rcu-रक्षित */
	rcu_पढ़ो_lock();
	mutex_unlock(&local->sta_mtx);

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
		mesh_accept_plinks_update(sdata);

	वापस 0;
 out_हटाओ:
	sta_info_hash_del(local, sta);
	list_del_rcu(&sta->list);
 out_drop_sta:
	local->num_sta--;
	synchronize_net();
	cleanup_single_sta(sta);
 out_err:
	mutex_unlock(&local->sta_mtx);
	kमुक्त(sinfo);
	rcu_पढ़ो_lock();
	वापस err;
पूर्ण

पूर्णांक sta_info_insert_rcu(काष्ठा sta_info *sta) __acquires(RCU)
अणु
	काष्ठा ieee80211_local *local = sta->local;
	पूर्णांक err;

	might_sleep();

	mutex_lock(&local->sta_mtx);

	err = sta_info_insert_check(sta);
	अगर (err) अणु
		sta_info_मुक्त(local, sta);
		mutex_unlock(&local->sta_mtx);
		rcu_पढ़ो_lock();
		वापस err;
	पूर्ण

	वापस sta_info_insert_finish(sta);
पूर्ण

पूर्णांक sta_info_insert(काष्ठा sta_info *sta)
अणु
	पूर्णांक err = sta_info_insert_rcu(sta);

	rcu_पढ़ो_unlock();

	वापस err;
पूर्ण

अटल अंतरभूत व्योम __bss_tim_set(u8 *tim, u16 id)
अणु
	/*
	 * This क्रमmat has been mandated by the IEEE specअगरications,
	 * so this line may not be changed to use the __set_bit() क्रमmat.
	 */
	tim[id / 8] |= (1 << (id % 8));
पूर्ण

अटल अंतरभूत व्योम __bss_tim_clear(u8 *tim, u16 id)
अणु
	/*
	 * This क्रमmat has been mandated by the IEEE specअगरications,
	 * so this line may not be changed to use the __clear_bit() क्रमmat.
	 */
	tim[id / 8] &= ~(1 << (id % 8));
पूर्ण

अटल अंतरभूत bool __bss_tim_get(u8 *tim, u16 id)
अणु
	/*
	 * This क्रमmat has been mandated by the IEEE specअगरications,
	 * so this line may not be changed to use the test_bit() क्रमmat.
	 */
	वापस tim[id / 8] & (1 << (id % 8));
पूर्ण

अटल अचिन्हित दीर्घ ieee80211_tids_क्रम_ac(पूर्णांक ac)
अणु
	/* If we ever support TIDs > 7, this obviously needs to be adjusted */
	चयन (ac) अणु
	हाल IEEE80211_AC_VO:
		वापस BIT(6) | BIT(7);
	हाल IEEE80211_AC_VI:
		वापस BIT(4) | BIT(5);
	हाल IEEE80211_AC_BE:
		वापस BIT(0) | BIT(3);
	हाल IEEE80211_AC_BK:
		वापस BIT(1) | BIT(2);
	शेष:
		WARN_ON(1);
		वापस 0;
	पूर्ण
पूर्ण

अटल व्योम __sta_info_recalc_tim(काष्ठा sta_info *sta, bool ignore_pending)
अणु
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा ps_data *ps;
	bool indicate_tim = false;
	u8 ignore_क्रम_tim = sta->sta.uapsd_queues;
	पूर्णांक ac;
	u16 id = sta->sta.aid;

	अगर (sta->sdata->vअगर.type == NL80211_IFTYPE_AP ||
	    sta->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		अगर (WARN_ON_ONCE(!sta->sdata->bss))
			वापस;

		ps = &sta->sdata->bss->ps;
#अगर_घोषित CONFIG_MAC80211_MESH
	पूर्ण अन्यथा अगर (ieee80211_vअगर_is_mesh(&sta->sdata->vअगर)) अणु
		ps = &sta->sdata->u.mesh.ps;
#पूर्ण_अगर
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	/* No need to करो anything अगर the driver करोes all */
	अगर (ieee80211_hw_check(&local->hw, AP_LINK_PS) && !local->ops->set_tim)
		वापस;

	अगर (sta->dead)
		जाओ करोne;

	/*
	 * If all ACs are delivery-enabled then we should build
	 * the TIM bit क्रम all ACs anyway; अगर only some are then
	 * we ignore those and build the TIM bit using only the
	 * non-enabled ones.
	 */
	अगर (ignore_क्रम_tim == BIT(IEEE80211_NUM_ACS) - 1)
		ignore_क्रम_tim = 0;

	अगर (ignore_pending)
		ignore_क्रम_tim = BIT(IEEE80211_NUM_ACS) - 1;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		अचिन्हित दीर्घ tids;

		अगर (ignore_क्रम_tim & ieee80211_ac_to_qos_mask[ac])
			जारी;

		indicate_tim |= !skb_queue_empty(&sta->tx_filtered[ac]) ||
				!skb_queue_empty(&sta->ps_tx_buf[ac]);
		अगर (indicate_tim)
			अवरोध;

		tids = ieee80211_tids_क्रम_ac(ac);

		indicate_tim |=
			sta->driver_buffered_tids & tids;
		indicate_tim |=
			sta->txq_buffered_tids & tids;
	पूर्ण

 करोne:
	spin_lock_bh(&local->tim_lock);

	अगर (indicate_tim == __bss_tim_get(ps->tim, id))
		जाओ out_unlock;

	अगर (indicate_tim)
		__bss_tim_set(ps->tim, id);
	अन्यथा
		__bss_tim_clear(ps->tim, id);

	अगर (local->ops->set_tim && !WARN_ON(sta->dead)) अणु
		local->tim_in_locked_section = true;
		drv_set_tim(local, &sta->sta, indicate_tim);
		local->tim_in_locked_section = false;
	पूर्ण

out_unlock:
	spin_unlock_bh(&local->tim_lock);
पूर्ण

व्योम sta_info_recalc_tim(काष्ठा sta_info *sta)
अणु
	__sta_info_recalc_tim(sta, false);
पूर्ण

अटल bool sta_info_buffer_expired(काष्ठा sta_info *sta, काष्ठा sk_buff *skb)
अणु
	काष्ठा ieee80211_tx_info *info;
	पूर्णांक समयout;

	अगर (!skb)
		वापस false;

	info = IEEE80211_SKB_CB(skb);

	/* Timeout: (2 * listen_पूर्णांकerval * beacon_पूर्णांक * 1024 / 1000000) sec */
	समयout = (sta->listen_पूर्णांकerval *
		   sta->sdata->vअगर.bss_conf.beacon_पूर्णांक *
		   32 / 15625) * HZ;
	अगर (समयout < STA_TX_BUFFER_EXPIRE)
		समयout = STA_TX_BUFFER_EXPIRE;
	वापस समय_after(jअगरfies, info->control.jअगरfies + समयout);
पूर्ण


अटल bool sta_info_cleanup_expire_buffered_ac(काष्ठा ieee80211_local *local,
						काष्ठा sta_info *sta, पूर्णांक ac)
अणु
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb;

	/*
	 * First check क्रम frames that should expire on the filtered
	 * queue. Frames here were rejected by the driver and are on
	 * a separate queue to aव्योम reordering with normal PS-buffered
	 * frames. They also aren't accounted क्रम right now in the
	 * total_ps_buffered counter.
	 */
	क्रम (;;) अणु
		spin_lock_irqsave(&sta->tx_filtered[ac].lock, flags);
		skb = skb_peek(&sta->tx_filtered[ac]);
		अगर (sta_info_buffer_expired(sta, skb))
			skb = __skb_dequeue(&sta->tx_filtered[ac]);
		अन्यथा
			skb = शून्य;
		spin_unlock_irqrestore(&sta->tx_filtered[ac].lock, flags);

		/*
		 * Frames are queued in order, so अगर this one
		 * hasn't expired yet we can stop testing. If
		 * we actually reached the end of the queue we
		 * also need to stop, of course.
		 */
		अगर (!skb)
			अवरोध;
		ieee80211_मुक्त_txskb(&local->hw, skb);
	पूर्ण

	/*
	 * Now also check the normal PS-buffered queue, this will
	 * only find something अगर the filtered queue was emptied
	 * since the filtered frames are all beक्रमe the normal PS
	 * buffered frames.
	 */
	क्रम (;;) अणु
		spin_lock_irqsave(&sta->ps_tx_buf[ac].lock, flags);
		skb = skb_peek(&sta->ps_tx_buf[ac]);
		अगर (sta_info_buffer_expired(sta, skb))
			skb = __skb_dequeue(&sta->ps_tx_buf[ac]);
		अन्यथा
			skb = शून्य;
		spin_unlock_irqrestore(&sta->ps_tx_buf[ac].lock, flags);

		/*
		 * frames are queued in order, so अगर this one
		 * hasn't expired yet (or we reached the end of
		 * the queue) we can stop testing
		 */
		अगर (!skb)
			अवरोध;

		local->total_ps_buffered--;
		ps_dbg(sta->sdata, "Buffered frame expired (STA %pM)\n",
		       sta->sta.addr);
		ieee80211_मुक्त_txskb(&local->hw, skb);
	पूर्ण

	/*
	 * Finally, recalculate the TIM bit क्रम this station -- it might
	 * now be clear because the station was too slow to retrieve its
	 * frames.
	 */
	sta_info_recalc_tim(sta);

	/*
	 * Return whether there are any frames still buffered, this is
	 * used to check whether the cleanup समयr still needs to run,
	 * अगर there are no frames we करोn't need to rearm the समयr.
	 */
	वापस !(skb_queue_empty(&sta->ps_tx_buf[ac]) &&
		 skb_queue_empty(&sta->tx_filtered[ac]));
पूर्ण

अटल bool sta_info_cleanup_expire_buffered(काष्ठा ieee80211_local *local,
					     काष्ठा sta_info *sta)
अणु
	bool have_buffered = false;
	पूर्णांक ac;

	/* This is only necessary क्रम stations on BSS/MBSS पूर्णांकerfaces */
	अगर (!sta->sdata->bss &&
	    !ieee80211_vअगर_is_mesh(&sta->sdata->vअगर))
		वापस false;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
		have_buffered |=
			sta_info_cleanup_expire_buffered_ac(local, sta, ac);

	वापस have_buffered;
पूर्ण

अटल पूर्णांक __must_check __sta_info_destroy_part1(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_local *local;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक ret;

	might_sleep();

	अगर (!sta)
		वापस -ENOENT;

	local = sta->local;
	sdata = sta->sdata;

	lockdep_निश्चित_held(&local->sta_mtx);

	/*
	 * Beक्रमe removing the station from the driver and
	 * rate control, it might still start new aggregation
	 * sessions -- block that to make sure the tear-करोwn
	 * will be sufficient.
	 */
	set_sta_flag(sta, WLAN_STA_BLOCK_BA);
	ieee80211_sta_tear_करोwn_BA_sessions(sta, AGG_STOP_DESTROY_STA);

	/*
	 * Beक्रमe removing the station from the driver there might be pending
	 * rx frames on RSS queues sent prior to the disassociation - रुको क्रम
	 * all such frames to be processed.
	 */
	drv_sync_rx_queues(local, sta);

	ret = sta_info_hash_del(local, sta);
	अगर (WARN_ON(ret))
		वापस ret;

	/*
	 * क्रम TDLS peers, make sure to वापस to the base channel beक्रमe
	 * removal.
	 */
	अगर (test_sta_flag(sta, WLAN_STA_TDLS_OFF_CHANNEL)) अणु
		drv_tdls_cancel_channel_चयन(local, sdata, &sta->sta);
		clear_sta_flag(sta, WLAN_STA_TDLS_OFF_CHANNEL);
	पूर्ण

	list_del_rcu(&sta->list);
	sta->हटाओd = true;

	drv_sta_pre_rcu_हटाओ(local, sta->sdata, sta);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN &&
	    rcu_access_poपूर्णांकer(sdata->u.vlan.sta) == sta)
		RCU_INIT_POINTER(sdata->u.vlan.sta, शून्य);

	वापस 0;
पूर्ण

अटल व्योम __sta_info_destroy_part2(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_local *local = sta->local;
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा station_info *sinfo;
	पूर्णांक ret;

	/*
	 * NOTE: This assumes at least synchronize_net() was करोne
	 *	 after _part1 and beक्रमe _part2!
	 */

	might_sleep();
	lockdep_निश्चित_held(&local->sta_mtx);

	अगर (sta->sta_state == IEEE80211_STA_AUTHORIZED) अणु
		ret = sta_info_move_state(sta, IEEE80211_STA_ASSOC);
		WARN_ON_ONCE(ret);
	पूर्ण

	/* now keys can no दीर्घer be reached */
	ieee80211_मुक्त_sta_keys(local, sta);

	/* disable TIM bit - last chance to tell driver */
	__sta_info_recalc_tim(sta, true);

	sta->dead = true;

	local->num_sta--;
	local->sta_generation++;

	जबतक (sta->sta_state > IEEE80211_STA_NONE) अणु
		ret = sta_info_move_state(sta, sta->sta_state - 1);
		अगर (ret) अणु
			WARN_ON_ONCE(1);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (sta->uploaded) अणु
		ret = drv_sta_state(local, sdata, sta, IEEE80211_STA_NONE,
				    IEEE80211_STA_NOTEXIST);
		WARN_ON_ONCE(ret != 0);
	पूर्ण

	sta_dbg(sdata, "Removed STA %pM\n", sta->sta.addr);

	sinfo = kzalloc(माप(*sinfo), GFP_KERNEL);
	अगर (sinfo)
		sta_set_sinfo(sta, sinfo, true);
	cfg80211_del_sta_sinfo(sdata->dev, sta->sta.addr, sinfo, GFP_KERNEL);
	kमुक्त(sinfo);

	ieee80211_sta_debugfs_हटाओ(sta);

	ieee80211_destroy_frag_cache(&sta->frags);

	cleanup_single_sta(sta);
पूर्ण

पूर्णांक __must_check __sta_info_destroy(काष्ठा sta_info *sta)
अणु
	पूर्णांक err = __sta_info_destroy_part1(sta);

	अगर (err)
		वापस err;

	synchronize_net();

	__sta_info_destroy_part2(sta);

	वापस 0;
पूर्ण

पूर्णांक sta_info_destroy_addr(काष्ठा ieee80211_sub_अगर_data *sdata, स्थिर u8 *addr)
अणु
	काष्ठा sta_info *sta;
	पूर्णांक ret;

	mutex_lock(&sdata->local->sta_mtx);
	sta = sta_info_get(sdata, addr);
	ret = __sta_info_destroy(sta);
	mutex_unlock(&sdata->local->sta_mtx);

	वापस ret;
पूर्ण

पूर्णांक sta_info_destroy_addr_bss(काष्ठा ieee80211_sub_अगर_data *sdata,
			      स्थिर u8 *addr)
अणु
	काष्ठा sta_info *sta;
	पूर्णांक ret;

	mutex_lock(&sdata->local->sta_mtx);
	sta = sta_info_get_bss(sdata, addr);
	ret = __sta_info_destroy(sta);
	mutex_unlock(&sdata->local->sta_mtx);

	वापस ret;
पूर्ण

अटल व्योम sta_info_cleanup(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_local *local = from_समयr(local, t, sta_cleanup);
	काष्ठा sta_info *sta;
	bool समयr_needed = false;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &local->sta_list, list)
		अगर (sta_info_cleanup_expire_buffered(local, sta))
			समयr_needed = true;
	rcu_पढ़ो_unlock();

	अगर (local->quiescing)
		वापस;

	अगर (!समयr_needed)
		वापस;

	mod_समयr(&local->sta_cleanup,
		  round_jअगरfies(jअगरfies + STA_INFO_CLEANUP_INTERVAL));
पूर्ण

पूर्णांक sta_info_init(काष्ठा ieee80211_local *local)
अणु
	पूर्णांक err;

	err = rhltable_init(&local->sta_hash, &sta_rht_params);
	अगर (err)
		वापस err;

	spin_lock_init(&local->tim_lock);
	mutex_init(&local->sta_mtx);
	INIT_LIST_HEAD(&local->sta_list);

	समयr_setup(&local->sta_cleanup, sta_info_cleanup, 0);
	वापस 0;
पूर्ण

व्योम sta_info_stop(काष्ठा ieee80211_local *local)
अणु
	del_समयr_sync(&local->sta_cleanup);
	rhltable_destroy(&local->sta_hash);
पूर्ण


पूर्णांक __sta_info_flush(काष्ठा ieee80211_sub_अगर_data *sdata, bool vlans)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta, *पंचांगp;
	LIST_HEAD(मुक्त_list);
	पूर्णांक ret = 0;

	might_sleep();

	WARN_ON(vlans && sdata->vअगर.type != NL80211_IFTYPE_AP);
	WARN_ON(vlans && !sdata->bss);

	mutex_lock(&local->sta_mtx);
	list_क्रम_each_entry_safe(sta, पंचांगp, &local->sta_list, list) अणु
		अगर (sdata == sta->sdata ||
		    (vlans && sdata->bss == sta->sdata->bss)) अणु
			अगर (!WARN_ON(__sta_info_destroy_part1(sta)))
				list_add(&sta->मुक्त_list, &मुक्त_list);
			ret++;
		पूर्ण
	पूर्ण

	अगर (!list_empty(&मुक्त_list)) अणु
		synchronize_net();
		list_क्रम_each_entry_safe(sta, पंचांगp, &मुक्त_list, मुक्त_list)
			__sta_info_destroy_part2(sta);
	पूर्ण
	mutex_unlock(&local->sta_mtx);

	वापस ret;
पूर्ण

व्योम ieee80211_sta_expire(काष्ठा ieee80211_sub_अगर_data *sdata,
			  अचिन्हित दीर्घ exp_समय)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta, *पंचांगp;

	mutex_lock(&local->sta_mtx);

	list_क्रम_each_entry_safe(sta, पंचांगp, &local->sta_list, list) अणु
		अचिन्हित दीर्घ last_active = ieee80211_sta_last_active(sta);

		अगर (sdata != sta->sdata)
			जारी;

		अगर (समय_is_beक्रमe_jअगरfies(last_active + exp_समय)) अणु
			sta_dbg(sta->sdata, "expiring inactive STA %pM\n",
				sta->sta.addr);

			अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर) &&
			    test_sta_flag(sta, WLAN_STA_PS_STA))
				atomic_dec(&sdata->u.mesh.ps.num_sta_ps);

			WARN_ON(__sta_info_destroy(sta));
		पूर्ण
	पूर्ण

	mutex_unlock(&local->sta_mtx);
पूर्ण

काष्ठा ieee80211_sta *ieee80211_find_sta_by_अगरaddr(काष्ठा ieee80211_hw *hw,
						   स्थिर u8 *addr,
						   स्थिर u8 *localaddr)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा rhlist_head *पंचांगp;
	काष्ठा sta_info *sta;

	/*
	 * Just वापस a अक्रमom station अगर localaddr is शून्य
	 * ... first in list.
	 */
	क्रम_each_sta_info(local, addr, sta, पंचांगp) अणु
		अगर (localaddr &&
		    !ether_addr_equal(sta->sdata->vअगर.addr, localaddr))
			जारी;
		अगर (!sta->uploaded)
			वापस शून्य;
		वापस &sta->sta;
	पूर्ण

	वापस शून्य;
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_find_sta_by_अगरaddr);

काष्ठा ieee80211_sta *ieee80211_find_sta(काष्ठा ieee80211_vअगर *vअगर,
					 स्थिर u8 *addr)
अणु
	काष्ठा sta_info *sta;

	अगर (!vअगर)
		वापस शून्य;

	sta = sta_info_get_bss(vअगर_to_sdata(vअगर), addr);
	अगर (!sta)
		वापस शून्य;

	अगर (!sta->uploaded)
		वापस शून्य;

	वापस &sta->sta;
पूर्ण
EXPORT_SYMBOL(ieee80211_find_sta);

/* घातersave support code */
व्योम ieee80211_sta_ps_deliver_wakeup(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff_head pending;
	पूर्णांक filtered = 0, buffered = 0, ac, i;
	अचिन्हित दीर्घ flags;
	काष्ठा ps_data *ps;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		sdata = container_of(sdata->bss, काष्ठा ieee80211_sub_अगर_data,
				     u.ap);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		ps = &sdata->bss->ps;
	अन्यथा अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
		ps = &sdata->u.mesh.ps;
	अन्यथा
		वापस;

	clear_sta_flag(sta, WLAN_STA_SP);

	BUILD_BUG_ON(BITS_TO_LONGS(IEEE80211_NUM_TIDS) > 1);
	sta->driver_buffered_tids = 0;
	sta->txq_buffered_tids = 0;

	अगर (!ieee80211_hw_check(&local->hw, AP_LINK_PS))
		drv_sta_notअगरy(local, sdata, STA_NOTIFY_AWAKE, &sta->sta);

	क्रम (i = 0; i < ARRAY_SIZE(sta->sta.txq); i++) अणु
		अगर (!sta->sta.txq[i] || !txq_has_queue(sta->sta.txq[i]))
			जारी;

		schedule_and_wake_txq(local, to_txq_info(sta->sta.txq[i]));
	पूर्ण

	skb_queue_head_init(&pending);

	/* sync with ieee80211_tx_h_unicast_ps_buf */
	spin_lock(&sta->ps_lock);
	/* Send all buffered frames to the station */
	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		पूर्णांक count = skb_queue_len(&pending), पंचांगp;

		spin_lock_irqsave(&sta->tx_filtered[ac].lock, flags);
		skb_queue_splice_tail_init(&sta->tx_filtered[ac], &pending);
		spin_unlock_irqrestore(&sta->tx_filtered[ac].lock, flags);
		पंचांगp = skb_queue_len(&pending);
		filtered += पंचांगp - count;
		count = पंचांगp;

		spin_lock_irqsave(&sta->ps_tx_buf[ac].lock, flags);
		skb_queue_splice_tail_init(&sta->ps_tx_buf[ac], &pending);
		spin_unlock_irqrestore(&sta->ps_tx_buf[ac].lock, flags);
		पंचांगp = skb_queue_len(&pending);
		buffered += पंचांगp - count;
	पूर्ण

	ieee80211_add_pending_skbs(local, &pending);

	/* now we're no दीर्घer in the deliver code */
	clear_sta_flag(sta, WLAN_STA_PS_DELIVER);

	/* The station might have polled and then woken up beक्रमe we responded,
	 * so clear these flags now to aव्योम them sticking around.
	 */
	clear_sta_flag(sta, WLAN_STA_PSPOLL);
	clear_sta_flag(sta, WLAN_STA_UAPSD);
	spin_unlock(&sta->ps_lock);

	atomic_dec(&ps->num_sta_ps);

	local->total_ps_buffered -= buffered;

	sta_info_recalc_tim(sta);

	ps_dbg(sdata,
	       "STA %pM aid %d sending %d filtered/%d PS frames since STA woke up\n",
	       sta->sta.addr, sta->sta.aid, filtered, buffered);

	ieee80211_check_fast_xmit(sta);
पूर्ण

अटल व्योम ieee80211_send_null_response(काष्ठा sta_info *sta, पूर्णांक tid,
					 क्रमागत ieee80211_frame_release_type reason,
					 bool call_driver, bool more_data)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_qos_hdr *nullfunc;
	काष्ठा sk_buff *skb;
	पूर्णांक size = माप(*nullfunc);
	__le16 fc;
	bool qos = sta->sta.wme;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;

	/* Don't send NDPs when STA is connected HE */
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    !(sdata->u.mgd.flags & IEEE80211_STA_DISABLE_HE))
		वापस;

	अगर (qos) अणु
		fc = cpu_to_le16(IEEE80211_FTYPE_DATA |
				 IEEE80211_STYPE_QOS_शून्यFUNC |
				 IEEE80211_FCTL_FROMDS);
	पूर्ण अन्यथा अणु
		size -= 2;
		fc = cpu_to_le16(IEEE80211_FTYPE_DATA |
				 IEEE80211_STYPE_शून्यFUNC |
				 IEEE80211_FCTL_FROMDS);
	पूर्ण

	skb = dev_alloc_skb(local->hw.extra_tx_headroom + size);
	अगर (!skb)
		वापस;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	nullfunc = skb_put(skb, size);
	nullfunc->frame_control = fc;
	nullfunc->duration_id = 0;
	स_नकल(nullfunc->addr1, sta->sta.addr, ETH_ALEN);
	स_नकल(nullfunc->addr2, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(nullfunc->addr3, sdata->vअगर.addr, ETH_ALEN);
	nullfunc->seq_ctrl = 0;

	skb->priority = tid;
	skb_set_queue_mapping(skb, ieee802_1d_to_ac[tid]);
	अगर (qos) अणु
		nullfunc->qos_ctrl = cpu_to_le16(tid);

		अगर (reason == IEEE80211_FRAME_RELEASE_UAPSD) अणु
			nullfunc->qos_ctrl |=
				cpu_to_le16(IEEE80211_QOS_CTL_EOSP);
			अगर (more_data)
				nullfunc->frame_control |=
					cpu_to_le16(IEEE80211_FCTL_MOREDATA);
		पूर्ण
	पूर्ण

	info = IEEE80211_SKB_CB(skb);

	/*
	 * Tell TX path to send this frame even though the
	 * STA may still reमुख्य is PS mode after this frame
	 * exchange. Also set EOSP to indicate this packet
	 * ends the poll/service period.
	 */
	info->flags |= IEEE80211_TX_CTL_NO_PS_BUFFER |
		       IEEE80211_TX_STATUS_EOSP |
		       IEEE80211_TX_CTL_REQ_TX_STATUS;

	info->control.flags |= IEEE80211_TX_CTRL_PS_RESPONSE;

	अगर (call_driver)
		drv_allow_buffered_frames(local, sta, BIT(tid), 1,
					  reason, false);

	skb->dev = sdata->dev;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	info->band = chanctx_conf->def.chan->band;
	ieee80211_xmit(sdata, sta, skb);
	rcu_पढ़ो_unlock();
पूर्ण

अटल पूर्णांक find_highest_prio_tid(अचिन्हित दीर्घ tids)
अणु
	/* lower 3 TIDs aren't ordered perfectly */
	अगर (tids & 0xF8)
		वापस fls(tids) - 1;
	/* TID 0 is BE just like TID 3 */
	अगर (tids & BIT(0))
		वापस 0;
	वापस fls(tids) - 1;
पूर्ण

/* Indicates अगर the MORE_DATA bit should be set in the last
 * frame obtained by ieee80211_sta_ps_get_frames.
 * Note that driver_release_tids is relevant only अगर
 * reason = IEEE80211_FRAME_RELEASE_PSPOLL
 */
अटल bool
ieee80211_sta_ps_more_data(काष्ठा sta_info *sta, u8 ignored_acs,
			   क्रमागत ieee80211_frame_release_type reason,
			   अचिन्हित दीर्घ driver_release_tids)
अणु
	पूर्णांक ac;

	/* If the driver has data on more than one TID then
	 * certainly there's more data अगर we release just a
	 * single frame now (from a single TID). This will
	 * only happen क्रम PS-Poll.
	 */
	अगर (reason == IEEE80211_FRAME_RELEASE_PSPOLL &&
	    hweight16(driver_release_tids) > 1)
		वापस true;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		अगर (ignored_acs & ieee80211_ac_to_qos_mask[ac])
			जारी;

		अगर (!skb_queue_empty(&sta->tx_filtered[ac]) ||
		    !skb_queue_empty(&sta->ps_tx_buf[ac]))
			वापस true;
	पूर्ण

	वापस false;
पूर्ण

अटल व्योम
ieee80211_sta_ps_get_frames(काष्ठा sta_info *sta, पूर्णांक n_frames, u8 ignored_acs,
			    क्रमागत ieee80211_frame_release_type reason,
			    काष्ठा sk_buff_head *frames,
			    अचिन्हित दीर्घ *driver_release_tids)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ac;

	/* Get response frame(s) and more data bit क्रम the last one. */
	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		अचिन्हित दीर्घ tids;

		अगर (ignored_acs & ieee80211_ac_to_qos_mask[ac])
			जारी;

		tids = ieee80211_tids_क्रम_ac(ac);

		/* अगर we alपढ़ोy have frames from software, then we can't also
		 * release from hardware queues
		 */
		अगर (skb_queue_empty(frames)) अणु
			*driver_release_tids |=
				sta->driver_buffered_tids & tids;
			*driver_release_tids |= sta->txq_buffered_tids & tids;
		पूर्ण

		अगर (!*driver_release_tids) अणु
			काष्ठा sk_buff *skb;

			जबतक (n_frames > 0) अणु
				skb = skb_dequeue(&sta->tx_filtered[ac]);
				अगर (!skb) अणु
					skb = skb_dequeue(
						&sta->ps_tx_buf[ac]);
					अगर (skb)
						local->total_ps_buffered--;
				पूर्ण
				अगर (!skb)
					अवरोध;
				n_frames--;
				__skb_queue_tail(frames, skb);
			पूर्ण
		पूर्ण

		/* If we have more frames buffered on this AC, then पात the
		 * loop since we can't send more data from other ACs beक्रमe
		 * the buffered frames from this.
		 */
		अगर (!skb_queue_empty(&sta->tx_filtered[ac]) ||
		    !skb_queue_empty(&sta->ps_tx_buf[ac]))
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम
ieee80211_sta_ps_deliver_response(काष्ठा sta_info *sta,
				  पूर्णांक n_frames, u8 ignored_acs,
				  क्रमागत ieee80211_frame_release_type reason)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	अचिन्हित दीर्घ driver_release_tids = 0;
	काष्ठा sk_buff_head frames;
	bool more_data;

	/* Service or PS-Poll period starts */
	set_sta_flag(sta, WLAN_STA_SP);

	__skb_queue_head_init(&frames);

	ieee80211_sta_ps_get_frames(sta, n_frames, ignored_acs, reason,
				    &frames, &driver_release_tids);

	more_data = ieee80211_sta_ps_more_data(sta, ignored_acs, reason, driver_release_tids);

	अगर (driver_release_tids && reason == IEEE80211_FRAME_RELEASE_PSPOLL)
		driver_release_tids =
			BIT(find_highest_prio_tid(driver_release_tids));

	अगर (skb_queue_empty(&frames) && !driver_release_tids) अणु
		पूर्णांक tid, ac;

		/*
		 * For PS-Poll, this can only happen due to a race condition
		 * when we set the TIM bit and the station notices it, but
		 * beक्रमe it can poll क्रम the frame we expire it.
		 *
		 * For uAPSD, this is said in the standard (11.2.1.5 h):
		 *	At each unscheduled SP क्रम a non-AP STA, the AP shall
		 *	attempt to transmit at least one MSDU or MMPDU, but no
		 *	more than the value specअगरied in the Max SP Length field
		 *	in the QoS Capability element from delivery-enabled ACs,
		 *	that are destined क्रम the non-AP STA.
		 *
		 * Since we have no other MSDU/MMPDU, transmit a QoS null frame.
		 */

		/* This will evaluate to 1, 3, 5 or 7. */
		क्रम (ac = IEEE80211_AC_VO; ac < IEEE80211_NUM_ACS; ac++)
			अगर (!(ignored_acs & ieee80211_ac_to_qos_mask[ac]))
				अवरोध;
		tid = 7 - 2 * ac;

		ieee80211_send_null_response(sta, tid, reason, true, false);
	पूर्ण अन्यथा अगर (!driver_release_tids) अणु
		काष्ठा sk_buff_head pending;
		काष्ठा sk_buff *skb;
		पूर्णांक num = 0;
		u16 tids = 0;
		bool need_null = false;

		skb_queue_head_init(&pending);

		जबतक ((skb = __skb_dequeue(&frames))) अणु
			काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
			काष्ठा ieee80211_hdr *hdr = (व्योम *) skb->data;
			u8 *qoshdr = शून्य;

			num++;

			/*
			 * Tell TX path to send this frame even though the
			 * STA may still reमुख्य is PS mode after this frame
			 * exchange.
			 */
			info->flags |= IEEE80211_TX_CTL_NO_PS_BUFFER;
			info->control.flags |= IEEE80211_TX_CTRL_PS_RESPONSE;

			/*
			 * Use MoreData flag to indicate whether there are
			 * more buffered frames क्रम this STA
			 */
			अगर (more_data || !skb_queue_empty(&frames))
				hdr->frame_control |=
					cpu_to_le16(IEEE80211_FCTL_MOREDATA);
			अन्यथा
				hdr->frame_control &=
					cpu_to_le16(~IEEE80211_FCTL_MOREDATA);

			अगर (ieee80211_is_data_qos(hdr->frame_control) ||
			    ieee80211_is_qos_nullfunc(hdr->frame_control))
				qoshdr = ieee80211_get_qos_ctl(hdr);

			tids |= BIT(skb->priority);

			__skb_queue_tail(&pending, skb);

			/* end service period after last frame or add one */
			अगर (!skb_queue_empty(&frames))
				जारी;

			अगर (reason != IEEE80211_FRAME_RELEASE_UAPSD) अणु
				/* क्रम PS-Poll, there's only one frame */
				info->flags |= IEEE80211_TX_STATUS_EOSP |
					       IEEE80211_TX_CTL_REQ_TX_STATUS;
				अवरोध;
			पूर्ण

			/* For uAPSD, things are a bit more complicated. If the
			 * last frame has a QoS header (i.e. is a QoS-data or
			 * QoS-nulldata frame) then just set the EOSP bit there
			 * and be करोne.
			 * If the frame करोesn't have a QoS header (which means
			 * it should be a bufferable MMPDU) then we can't set
			 * the EOSP bit in the QoS header; add a QoS-nulldata
			 * frame to the list to send it after the MMPDU.
			 *
			 * Note that this code is only in the mac80211-release
			 * code path, we assume that the driver will not buffer
			 * anything but QoS-data frames, or अगर it करोes, will
			 * create the QoS-nulldata frame by itself अगर needed.
			 *
			 * Cf. 802.11-2012 10.2.1.10 (c).
			 */
			अगर (qoshdr) अणु
				*qoshdr |= IEEE80211_QOS_CTL_EOSP;

				info->flags |= IEEE80211_TX_STATUS_EOSP |
					       IEEE80211_TX_CTL_REQ_TX_STATUS;
			पूर्ण अन्यथा अणु
				/* The standard isn't completely clear on this
				 * as it says the more-data bit should be set
				 * अगर there are more BUs. The QoS-Null frame
				 * we're about to send isn't buffered yet, we
				 * only create it below, but let's pretend it
				 * was buffered just in हाल some clients only
				 * expect more-data=0 when eosp=1.
				 */
				hdr->frame_control |=
					cpu_to_le16(IEEE80211_FCTL_MOREDATA);
				need_null = true;
				num++;
			पूर्ण
			अवरोध;
		पूर्ण

		drv_allow_buffered_frames(local, sta, tids, num,
					  reason, more_data);

		ieee80211_add_pending_skbs(local, &pending);

		अगर (need_null)
			ieee80211_send_null_response(
				sta, find_highest_prio_tid(tids),
				reason, false, false);

		sta_info_recalc_tim(sta);
	पूर्ण अन्यथा अणु
		पूर्णांक tid;

		/*
		 * We need to release a frame that is buffered somewhere in the
		 * driver ... it'll have to handle that.
		 * Note that the driver also has to check the number of frames
		 * on the TIDs we're releasing from - अगर there are more than
		 * n_frames it has to set the more-data bit (अगर we didn't ask
		 * it to set it anyway due to other buffered frames); अगर there
		 * are fewer than n_frames it has to make sure to adjust that
		 * to allow the service period to end properly.
		 */
		drv_release_buffered_frames(local, sta, driver_release_tids,
					    n_frames, reason, more_data);

		/*
		 * Note that we करोn't recalculate the TIM bit here as it would
		 * most likely have no effect at all unless the driver told us
		 * that the TID(s) became empty beक्रमe वापसing here from the
		 * release function.
		 * Either way, however, when the driver tells us that the TID(s)
		 * became empty or we find that a txq became empty, we'll करो the
		 * TIM recalculation.
		 */

		अगर (!sta->sta.txq[0])
			वापस;

		क्रम (tid = 0; tid < ARRAY_SIZE(sta->sta.txq); tid++) अणु
			अगर (!sta->sta.txq[tid] ||
			    !(driver_release_tids & BIT(tid)) ||
			    txq_has_queue(sta->sta.txq[tid]))
				जारी;

			sta_info_recalc_tim(sta);
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण

व्योम ieee80211_sta_ps_deliver_poll_response(काष्ठा sta_info *sta)
अणु
	u8 ignore_क्रम_response = sta->sta.uapsd_queues;

	/*
	 * If all ACs are delivery-enabled then we should reply
	 * from any of them, अगर only some are enabled we reply
	 * only from the non-enabled ones.
	 */
	अगर (ignore_क्रम_response == BIT(IEEE80211_NUM_ACS) - 1)
		ignore_क्रम_response = 0;

	ieee80211_sta_ps_deliver_response(sta, 1, ignore_क्रम_response,
					  IEEE80211_FRAME_RELEASE_PSPOLL);
पूर्ण

व्योम ieee80211_sta_ps_deliver_uapsd(काष्ठा sta_info *sta)
अणु
	पूर्णांक n_frames = sta->sta.max_sp;
	u8 delivery_enabled = sta->sta.uapsd_queues;

	/*
	 * If we ever grow support क्रम TSPEC this might happen अगर
	 * the TSPEC update from hostapd comes in between a trigger
	 * frame setting WLAN_STA_UAPSD in the RX path and this
	 * actually getting called.
	 */
	अगर (!delivery_enabled)
		वापस;

	चयन (sta->sta.max_sp) अणु
	हाल 1:
		n_frames = 2;
		अवरोध;
	हाल 2:
		n_frames = 4;
		अवरोध;
	हाल 3:
		n_frames = 6;
		अवरोध;
	हाल 0:
		/* XXX: what is a good value? */
		n_frames = 128;
		अवरोध;
	पूर्ण

	ieee80211_sta_ps_deliver_response(sta, n_frames, ~delivery_enabled,
					  IEEE80211_FRAME_RELEASE_UAPSD);
पूर्ण

व्योम ieee80211_sta_block_awake(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_sta *pubsta, bool block)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);

	trace_api_sta_block_awake(sta->local, pubsta, block);

	अगर (block) अणु
		set_sta_flag(sta, WLAN_STA_PS_DRIVER);
		ieee80211_clear_fast_xmit(sta);
		वापस;
	पूर्ण

	अगर (!test_sta_flag(sta, WLAN_STA_PS_DRIVER))
		वापस;

	अगर (!test_sta_flag(sta, WLAN_STA_PS_STA)) अणु
		set_sta_flag(sta, WLAN_STA_PS_DELIVER);
		clear_sta_flag(sta, WLAN_STA_PS_DRIVER);
		ieee80211_queue_work(hw, &sta->drv_deliver_wk);
	पूर्ण अन्यथा अगर (test_sta_flag(sta, WLAN_STA_PSPOLL) ||
		   test_sta_flag(sta, WLAN_STA_UAPSD)) अणु
		/* must be asleep in this हाल */
		clear_sta_flag(sta, WLAN_STA_PS_DRIVER);
		ieee80211_queue_work(hw, &sta->drv_deliver_wk);
	पूर्ण अन्यथा अणु
		clear_sta_flag(sta, WLAN_STA_PS_DRIVER);
		ieee80211_check_fast_xmit(sta);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ieee80211_sta_block_awake);

व्योम ieee80211_sta_eosp(काष्ठा ieee80211_sta *pubsta)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	काष्ठा ieee80211_local *local = sta->local;

	trace_api_eosp(local, pubsta);

	clear_sta_flag(sta, WLAN_STA_SP);
पूर्ण
EXPORT_SYMBOL(ieee80211_sta_eosp);

व्योम ieee80211_send_eosp_nullfunc(काष्ठा ieee80211_sta *pubsta, पूर्णांक tid)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	क्रमागत ieee80211_frame_release_type reason;
	bool more_data;

	trace_api_send_eosp_nullfunc(sta->local, pubsta, tid);

	reason = IEEE80211_FRAME_RELEASE_UAPSD;
	more_data = ieee80211_sta_ps_more_data(sta, ~sta->sta.uapsd_queues,
					       reason, 0);

	ieee80211_send_null_response(sta, tid, reason, false, more_data);
पूर्ण
EXPORT_SYMBOL(ieee80211_send_eosp_nullfunc);

व्योम ieee80211_sta_set_buffered(काष्ठा ieee80211_sta *pubsta,
				u8 tid, bool buffered)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);

	अगर (WARN_ON(tid >= IEEE80211_NUM_TIDS))
		वापस;

	trace_api_sta_set_buffered(sta->local, pubsta, tid, buffered);

	अगर (buffered)
		set_bit(tid, &sta->driver_buffered_tids);
	अन्यथा
		clear_bit(tid, &sta->driver_buffered_tids);

	sta_info_recalc_tim(sta);
पूर्ण
EXPORT_SYMBOL(ieee80211_sta_set_buffered);

व्योम ieee80211_sta_रेजिस्टर_airसमय(काष्ठा ieee80211_sta *pubsta, u8 tid,
				    u32 tx_airसमय, u32 rx_airसमय)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);
	काष्ठा ieee80211_local *local = sta->sdata->local;
	u8 ac = ieee80211_ac_from_tid(tid);
	u32 airसमय = 0;

	अगर (sta->local->airसमय_flags & AIRTIME_USE_TX)
		airसमय += tx_airसमय;
	अगर (sta->local->airसमय_flags & AIRTIME_USE_RX)
		airसमय += rx_airसमय;

	spin_lock_bh(&local->active_txq_lock[ac]);
	sta->airसमय[ac].tx_airसमय += tx_airसमय;
	sta->airसमय[ac].rx_airसमय += rx_airसमय;
	sta->airसमय[ac].deficit -= airसमय;
	spin_unlock_bh(&local->active_txq_lock[ac]);
पूर्ण
EXPORT_SYMBOL(ieee80211_sta_रेजिस्टर_airसमय);

व्योम ieee80211_sta_update_pending_airसमय(काष्ठा ieee80211_local *local,
					  काष्ठा sta_info *sta, u8 ac,
					  u16 tx_airसमय, bool tx_completed)
अणु
	पूर्णांक tx_pending;

	अगर (!wiphy_ext_feature_isset(local->hw.wiphy, NL80211_EXT_FEATURE_AQL))
		वापस;

	अगर (!tx_completed) अणु
		अगर (sta)
			atomic_add(tx_airसमय,
				   &sta->airसमय[ac].aql_tx_pending);

		atomic_add(tx_airसमय, &local->aql_total_pending_airसमय);
		वापस;
	पूर्ण

	अगर (sta) अणु
		tx_pending = atomic_sub_वापस(tx_airसमय,
					       &sta->airसमय[ac].aql_tx_pending);
		अगर (tx_pending < 0)
			atomic_cmpxchg(&sta->airसमय[ac].aql_tx_pending,
				       tx_pending, 0);
	पूर्ण

	tx_pending = atomic_sub_वापस(tx_airसमय,
				       &local->aql_total_pending_airसमय);
	अगर (WARN_ONCE(tx_pending < 0,
		      "Device %s AC %d pending airtime underflow: %u, %u",
		      wiphy_name(local->hw.wiphy), ac, tx_pending,
		      tx_airसमय))
		atomic_cmpxchg(&local->aql_total_pending_airसमय,
			       tx_pending, 0);
पूर्ण

पूर्णांक sta_info_move_state(काष्ठा sta_info *sta,
			क्रमागत ieee80211_sta_state new_state)
अणु
	might_sleep();

	अगर (sta->sta_state == new_state)
		वापस 0;

	/* check allowed transitions first */

	चयन (new_state) अणु
	हाल IEEE80211_STA_NONE:
		अगर (sta->sta_state != IEEE80211_STA_AUTH)
			वापस -EINVAL;
		अवरोध;
	हाल IEEE80211_STA_AUTH:
		अगर (sta->sta_state != IEEE80211_STA_NONE &&
		    sta->sta_state != IEEE80211_STA_ASSOC)
			वापस -EINVAL;
		अवरोध;
	हाल IEEE80211_STA_ASSOC:
		अगर (sta->sta_state != IEEE80211_STA_AUTH &&
		    sta->sta_state != IEEE80211_STA_AUTHORIZED)
			वापस -EINVAL;
		अवरोध;
	हाल IEEE80211_STA_AUTHORIZED:
		अगर (sta->sta_state != IEEE80211_STA_ASSOC)
			वापस -EINVAL;
		अवरोध;
	शेष:
		WARN(1, "invalid state %d", new_state);
		वापस -EINVAL;
	पूर्ण

	sta_dbg(sta->sdata, "moving STA %pM to state %d\n",
		sta->sta.addr, new_state);

	/*
	 * notअगरy the driver beक्रमe the actual changes so it can
	 * fail the transition
	 */
	अगर (test_sta_flag(sta, WLAN_STA_INSERTED)) अणु
		पूर्णांक err = drv_sta_state(sta->local, sta->sdata, sta,
					sta->sta_state, new_state);
		अगर (err)
			वापस err;
	पूर्ण

	/* reflect the change in all state variables */

	चयन (new_state) अणु
	हाल IEEE80211_STA_NONE:
		अगर (sta->sta_state == IEEE80211_STA_AUTH)
			clear_bit(WLAN_STA_AUTH, &sta->_flags);
		अवरोध;
	हाल IEEE80211_STA_AUTH:
		अगर (sta->sta_state == IEEE80211_STA_NONE) अणु
			set_bit(WLAN_STA_AUTH, &sta->_flags);
		पूर्ण अन्यथा अगर (sta->sta_state == IEEE80211_STA_ASSOC) अणु
			clear_bit(WLAN_STA_ASSOC, &sta->_flags);
			ieee80211_recalc_min_chandef(sta->sdata);
			अगर (!sta->sta.support_p2p_ps)
				ieee80211_recalc_p2p_go_ps_allowed(sta->sdata);
		पूर्ण
		अवरोध;
	हाल IEEE80211_STA_ASSOC:
		अगर (sta->sta_state == IEEE80211_STA_AUTH) अणु
			set_bit(WLAN_STA_ASSOC, &sta->_flags);
			sta->assoc_at = kसमय_get_bootसमय_ns();
			ieee80211_recalc_min_chandef(sta->sdata);
			अगर (!sta->sta.support_p2p_ps)
				ieee80211_recalc_p2p_go_ps_allowed(sta->sdata);
		पूर्ण अन्यथा अगर (sta->sta_state == IEEE80211_STA_AUTHORIZED) अणु
			ieee80211_vअगर_dec_num_mcast(sta->sdata);
			clear_bit(WLAN_STA_AUTHORIZED, &sta->_flags);
			ieee80211_clear_fast_xmit(sta);
			ieee80211_clear_fast_rx(sta);
		पूर्ण
		अवरोध;
	हाल IEEE80211_STA_AUTHORIZED:
		अगर (sta->sta_state == IEEE80211_STA_ASSOC) अणु
			ieee80211_vअगर_inc_num_mcast(sta->sdata);
			set_bit(WLAN_STA_AUTHORIZED, &sta->_flags);
			ieee80211_check_fast_xmit(sta);
			ieee80211_check_fast_rx(sta);
		पूर्ण
		अगर (sta->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN ||
		    sta->sdata->vअगर.type == NL80211_IFTYPE_AP)
			cfg80211_send_layer2_update(sta->sdata->dev,
						    sta->sta.addr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	sta->sta_state = new_state;

	वापस 0;
पूर्ण

u8 sta_info_tx_streams(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sta_ht_cap *ht_cap = &sta->sta.ht_cap;
	u8 rx_streams;

	अगर (!sta->sta.ht_cap.ht_supported)
		वापस 1;

	अगर (sta->sta.vht_cap.vht_supported) अणु
		पूर्णांक i;
		u16 tx_mcs_map =
			le16_to_cpu(sta->sta.vht_cap.vht_mcs.tx_mcs_map);

		क्रम (i = 7; i >= 0; i--)
			अगर ((tx_mcs_map & (0x3 << (i * 2))) !=
			    IEEE80211_VHT_MCS_NOT_SUPPORTED)
				वापस i + 1;
	पूर्ण

	अगर (ht_cap->mcs.rx_mask[3])
		rx_streams = 4;
	अन्यथा अगर (ht_cap->mcs.rx_mask[2])
		rx_streams = 3;
	अन्यथा अगर (ht_cap->mcs.rx_mask[1])
		rx_streams = 2;
	अन्यथा
		rx_streams = 1;

	अगर (!(ht_cap->mcs.tx_params & IEEE80211_HT_MCS_TX_RX_DIFF))
		वापस rx_streams;

	वापस ((ht_cap->mcs.tx_params & IEEE80211_HT_MCS_TX_MAX_STREAMS_MASK)
			>> IEEE80211_HT_MCS_TX_MAX_STREAMS_SHIFT) + 1;
पूर्ण

अटल काष्ठा ieee80211_sta_rx_stats *
sta_get_last_rx_stats(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sta_rx_stats *stats = &sta->rx_stats;
	काष्ठा ieee80211_local *local = sta->local;
	पूर्णांक cpu;

	अगर (!ieee80211_hw_check(&local->hw, USES_RSS))
		वापस stats;

	क्रम_each_possible_cpu(cpu) अणु
		काष्ठा ieee80211_sta_rx_stats *cpustats;

		cpustats = per_cpu_ptr(sta->pcpu_rx_stats, cpu);

		अगर (समय_after(cpustats->last_rx, stats->last_rx))
			stats = cpustats;
	पूर्ण

	वापस stats;
पूर्ण

अटल व्योम sta_stats_decode_rate(काष्ठा ieee80211_local *local, u32 rate,
				  काष्ठा rate_info *rinfo)
अणु
	rinfo->bw = STA_STATS_GET(BW, rate);

	चयन (STA_STATS_GET(TYPE, rate)) अणु
	हाल STA_STATS_RATE_TYPE_VHT:
		rinfo->flags = RATE_INFO_FLAGS_VHT_MCS;
		rinfo->mcs = STA_STATS_GET(VHT_MCS, rate);
		rinfo->nss = STA_STATS_GET(VHT_NSS, rate);
		अगर (STA_STATS_GET(SGI, rate))
			rinfo->flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल STA_STATS_RATE_TYPE_HT:
		rinfo->flags = RATE_INFO_FLAGS_MCS;
		rinfo->mcs = STA_STATS_GET(HT_MCS, rate);
		अगर (STA_STATS_GET(SGI, rate))
			rinfo->flags |= RATE_INFO_FLAGS_SHORT_GI;
		अवरोध;
	हाल STA_STATS_RATE_TYPE_LEGACY: अणु
		काष्ठा ieee80211_supported_band *sband;
		u16 brate;
		अचिन्हित पूर्णांक shअगरt;
		पूर्णांक band = STA_STATS_GET(LEGACY_BAND, rate);
		पूर्णांक rate_idx = STA_STATS_GET(LEGACY_IDX, rate);

		sband = local->hw.wiphy->bands[band];

		अगर (WARN_ON_ONCE(!sband->bitrates))
			अवरोध;

		brate = sband->bitrates[rate_idx].bitrate;
		अगर (rinfo->bw == RATE_INFO_BW_5)
			shअगरt = 2;
		अन्यथा अगर (rinfo->bw == RATE_INFO_BW_10)
			shअगरt = 1;
		अन्यथा
			shअगरt = 0;
		rinfo->legacy = DIV_ROUND_UP(brate, 1 << shअगरt);
		अवरोध;
		पूर्ण
	हाल STA_STATS_RATE_TYPE_HE:
		rinfo->flags = RATE_INFO_FLAGS_HE_MCS;
		rinfo->mcs = STA_STATS_GET(HE_MCS, rate);
		rinfo->nss = STA_STATS_GET(HE_NSS, rate);
		rinfo->he_gi = STA_STATS_GET(HE_GI, rate);
		rinfo->he_ru_alloc = STA_STATS_GET(HE_RU, rate);
		rinfo->he_dcm = STA_STATS_GET(HE_DCM, rate);
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक sta_set_rate_info_rx(काष्ठा sta_info *sta, काष्ठा rate_info *rinfo)
अणु
	u16 rate = READ_ONCE(sta_get_last_rx_stats(sta)->last_rate);

	अगर (rate == STA_STATS_RATE_INVALID)
		वापस -EINVAL;

	sta_stats_decode_rate(sta->local, rate, rinfo);
	वापस 0;
पूर्ण

अटल अंतरभूत u64 sta_get_tidstats_msdu(काष्ठा ieee80211_sta_rx_stats *rxstats,
					पूर्णांक tid)
अणु
	अचिन्हित पूर्णांक start;
	u64 value;

	करो अणु
		start = u64_stats_fetch_begin(&rxstats->syncp);
		value = rxstats->msdu[tid];
	पूर्ण जबतक (u64_stats_fetch_retry(&rxstats->syncp, start));

	वापस value;
पूर्ण

अटल व्योम sta_set_tidstats(काष्ठा sta_info *sta,
			     काष्ठा cfg80211_tid_stats *tidstats,
			     पूर्णांक tid)
अणु
	काष्ठा ieee80211_local *local = sta->local;
	पूर्णांक cpu;

	अगर (!(tidstats->filled & BIT(NL80211_TID_STATS_RX_MSDU))) अणु
		अगर (!ieee80211_hw_check(&local->hw, USES_RSS))
			tidstats->rx_msdu +=
				sta_get_tidstats_msdu(&sta->rx_stats, tid);

		अगर (sta->pcpu_rx_stats) अणु
			क्रम_each_possible_cpu(cpu) अणु
				काष्ठा ieee80211_sta_rx_stats *cpurxs;

				cpurxs = per_cpu_ptr(sta->pcpu_rx_stats, cpu);
				tidstats->rx_msdu +=
					sta_get_tidstats_msdu(cpurxs, tid);
			पूर्ण
		पूर्ण

		tidstats->filled |= BIT(NL80211_TID_STATS_RX_MSDU);
	पूर्ण

	अगर (!(tidstats->filled & BIT(NL80211_TID_STATS_TX_MSDU))) अणु
		tidstats->filled |= BIT(NL80211_TID_STATS_TX_MSDU);
		tidstats->tx_msdu = sta->tx_stats.msdu[tid];
	पूर्ण

	अगर (!(tidstats->filled & BIT(NL80211_TID_STATS_TX_MSDU_RETRIES)) &&
	    ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS)) अणु
		tidstats->filled |= BIT(NL80211_TID_STATS_TX_MSDU_RETRIES);
		tidstats->tx_msdu_retries = sta->status_stats.msdu_retries[tid];
	पूर्ण

	अगर (!(tidstats->filled & BIT(NL80211_TID_STATS_TX_MSDU_FAILED)) &&
	    ieee80211_hw_check(&local->hw, REPORTS_TX_ACK_STATUS)) अणु
		tidstats->filled |= BIT(NL80211_TID_STATS_TX_MSDU_FAILED);
		tidstats->tx_msdu_failed = sta->status_stats.msdu_failed[tid];
	पूर्ण

	अगर (local->ops->wake_tx_queue && tid < IEEE80211_NUM_TIDS) अणु
		spin_lock_bh(&local->fq.lock);
		rcu_पढ़ो_lock();

		tidstats->filled |= BIT(NL80211_TID_STATS_TXQ_STATS);
		ieee80211_fill_txq_stats(&tidstats->txq_stats,
					 to_txq_info(sta->sta.txq[tid]));

		rcu_पढ़ो_unlock();
		spin_unlock_bh(&local->fq.lock);
	पूर्ण
पूर्ण

अटल अंतरभूत u64 sta_get_stats_bytes(काष्ठा ieee80211_sta_rx_stats *rxstats)
अणु
	अचिन्हित पूर्णांक start;
	u64 value;

	करो अणु
		start = u64_stats_fetch_begin(&rxstats->syncp);
		value = rxstats->bytes;
	पूर्ण जबतक (u64_stats_fetch_retry(&rxstats->syncp, start));

	वापस value;
पूर्ण

व्योम sta_set_sinfo(काष्ठा sta_info *sta, काष्ठा station_info *sinfo,
		   bool tidstats)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	u32 thr = 0;
	पूर्णांक i, ac, cpu;
	काष्ठा ieee80211_sta_rx_stats *last_rxstats;

	last_rxstats = sta_get_last_rx_stats(sta);

	sinfo->generation = sdata->local->sta_generation;

	/* करो beक्रमe driver, so beacon filtering drivers have a
	 * chance to e.g. just add the number of filtered beacons
	 * (or just modअगरy the value entirely, of course)
	 */
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION)
		sinfo->rx_beacon = sdata->u.mgd.count_beacon_संकेत;

	drv_sta_statistics(local, sdata, &sta->sta, sinfo);

	sinfo->filled |= BIT_ULL(NL80211_STA_INFO_INACTIVE_TIME) |
			 BIT_ULL(NL80211_STA_INFO_STA_FLAGS) |
			 BIT_ULL(NL80211_STA_INFO_BSS_PARAM) |
			 BIT_ULL(NL80211_STA_INFO_CONNECTED_TIME) |
			 BIT_ULL(NL80211_STA_INFO_ASSOC_AT_BOOTTIME) |
			 BIT_ULL(NL80211_STA_INFO_RX_DROP_MISC);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION) अणु
		sinfo->beacon_loss_count = sdata->u.mgd.beacon_loss_count;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_BEACON_LOSS);
	पूर्ण

	sinfo->connected_समय = kसमय_get_seconds() - sta->last_connected;
	sinfo->assoc_at = sta->assoc_at;
	sinfo->inactive_समय =
		jअगरfies_to_msecs(jअगरfies - ieee80211_sta_last_active(sta));

	अगर (!(sinfo->filled & (BIT_ULL(NL80211_STA_INFO_TX_BYTES64) |
			       BIT_ULL(NL80211_STA_INFO_TX_BYTES)))) अणु
		sinfo->tx_bytes = 0;
		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			sinfo->tx_bytes += sta->tx_stats.bytes[ac];
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BYTES64);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_TX_PACKETS))) अणु
		sinfo->tx_packets = 0;
		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			sinfo->tx_packets += sta->tx_stats.packets[ac];
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_PACKETS);
	पूर्ण

	अगर (!(sinfo->filled & (BIT_ULL(NL80211_STA_INFO_RX_BYTES64) |
			       BIT_ULL(NL80211_STA_INFO_RX_BYTES)))) अणु
		अगर (!ieee80211_hw_check(&local->hw, USES_RSS))
			sinfo->rx_bytes += sta_get_stats_bytes(&sta->rx_stats);

		अगर (sta->pcpu_rx_stats) अणु
			क्रम_each_possible_cpu(cpu) अणु
				काष्ठा ieee80211_sta_rx_stats *cpurxs;

				cpurxs = per_cpu_ptr(sta->pcpu_rx_stats, cpu);
				sinfo->rx_bytes += sta_get_stats_bytes(cpurxs);
			पूर्ण
		पूर्ण

		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BYTES64);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_RX_PACKETS))) अणु
		sinfo->rx_packets = sta->rx_stats.packets;
		अगर (sta->pcpu_rx_stats) अणु
			क्रम_each_possible_cpu(cpu) अणु
				काष्ठा ieee80211_sta_rx_stats *cpurxs;

				cpurxs = per_cpu_ptr(sta->pcpu_rx_stats, cpu);
				sinfo->rx_packets += cpurxs->packets;
			पूर्ण
		पूर्ण
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_PACKETS);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_TX_RETRIES))) अणु
		sinfo->tx_retries = sta->status_stats.retry_count;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_RETRIES);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_TX_FAILED))) अणु
		sinfo->tx_failed = sta->status_stats.retry_failed;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_FAILED);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_RX_DURATION))) अणु
		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			sinfo->rx_duration += sta->airसमय[ac].rx_airसमय;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_DURATION);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_TX_DURATION))) अणु
		क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++)
			sinfo->tx_duration += sta->airसमय[ac].tx_airसमय;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_DURATION);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_AIRTIME_WEIGHT))) अणु
		sinfo->airसमय_weight = sta->airसमय_weight;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_AIRTIME_WEIGHT);
	पूर्ण

	sinfo->rx_dropped_misc = sta->rx_stats.dropped;
	अगर (sta->pcpu_rx_stats) अणु
		क्रम_each_possible_cpu(cpu) अणु
			काष्ठा ieee80211_sta_rx_stats *cpurxs;

			cpurxs = per_cpu_ptr(sta->pcpu_rx_stats, cpu);
			sinfo->rx_dropped_misc += cpurxs->dropped;
		पूर्ण
	पूर्ण

	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    !(sdata->vअगर.driver_flags & IEEE80211_VIF_BEACON_FILTER)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_BEACON_RX) |
				 BIT_ULL(NL80211_STA_INFO_BEACON_SIGNAL_AVG);
		sinfo->rx_beacon_संकेत_avg = ieee80211_ave_rssi(&sdata->vअगर);
	पूर्ण

	अगर (ieee80211_hw_check(&sta->local->hw, SIGNAL_DBM) ||
	    ieee80211_hw_check(&sta->local->hw, SIGNAL_UNSPEC)) अणु
		अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_SIGNAL))) अणु
			sinfo->संकेत = (s8)last_rxstats->last_संकेत;
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
		पूर्ण

		अगर (!sta->pcpu_rx_stats &&
		    !(sinfo->filled & BIT_ULL(NL80211_STA_INFO_SIGNAL_AVG))) अणु
			sinfo->संकेत_avg =
				-ewma_संकेत_पढ़ो(&sta->rx_stats_avg.संकेत);
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL_AVG);
		पूर्ण
	पूर्ण

	/* क्रम the average - अगर pcpu_rx_stats isn't set - rxstats must poपूर्णांक to
	 * the sta->rx_stats काष्ठा, so the check here is fine with and without
	 * pcpu statistics
	 */
	अगर (last_rxstats->chains &&
	    !(sinfo->filled & (BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL) |
			       BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL_AVG)))) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL);
		अगर (!sta->pcpu_rx_stats)
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL_AVG);

		sinfo->chains = last_rxstats->chains;

		क्रम (i = 0; i < ARRAY_SIZE(sinfo->chain_संकेत); i++) अणु
			sinfo->chain_संकेत[i] =
				last_rxstats->chain_संकेत_last[i];
			sinfo->chain_संकेत_avg[i] =
				-ewma_संकेत_पढ़ो(&sta->rx_stats_avg.chain_संकेत[i]);
		पूर्ण
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_TX_BITRATE))) अणु
		sta_set_rate_info_tx(sta, &sta->tx_stats.last_rate,
				     &sinfo->txrate);
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_TX_BITRATE);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_RX_BITRATE))) अणु
		अगर (sta_set_rate_info_rx(sta, &sinfo->rxrate) == 0)
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_RX_BITRATE);
	पूर्ण

	अगर (tidstats && !cfg80211_sinfo_alloc_tid_stats(sinfo, GFP_KERNEL)) अणु
		क्रम (i = 0; i < IEEE80211_NUM_TIDS + 1; i++)
			sta_set_tidstats(sta, &sinfo->pertid[i], i);
	पूर्ण

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
#अगर_घोषित CONFIG_MAC80211_MESH
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_LLID) |
				 BIT_ULL(NL80211_STA_INFO_PLID) |
				 BIT_ULL(NL80211_STA_INFO_PLINK_STATE) |
				 BIT_ULL(NL80211_STA_INFO_LOCAL_PM) |
				 BIT_ULL(NL80211_STA_INFO_PEER_PM) |
				 BIT_ULL(NL80211_STA_INFO_NONPEER_PM) |
				 BIT_ULL(NL80211_STA_INFO_CONNECTED_TO_GATE) |
				 BIT_ULL(NL80211_STA_INFO_CONNECTED_TO_AS);

		sinfo->llid = sta->mesh->llid;
		sinfo->plid = sta->mesh->plid;
		sinfo->plink_state = sta->mesh->plink_state;
		अगर (test_sta_flag(sta, WLAN_STA_TOFFSET_KNOWN)) अणु
			sinfo->filled |= BIT_ULL(NL80211_STA_INFO_T_OFFSET);
			sinfo->t_offset = sta->mesh->t_offset;
		पूर्ण
		sinfo->local_pm = sta->mesh->local_pm;
		sinfo->peer_pm = sta->mesh->peer_pm;
		sinfo->nonpeer_pm = sta->mesh->nonpeer_pm;
		sinfo->connected_to_gate = sta->mesh->connected_to_gate;
		sinfo->connected_to_as = sta->mesh->connected_to_as;
#पूर्ण_अगर
	पूर्ण

	sinfo->bss_param.flags = 0;
	अगर (sdata->vअगर.bss_conf.use_cts_prot)
		sinfo->bss_param.flags |= BSS_PARAM_FLAGS_CTS_PROT;
	अगर (sdata->vअगर.bss_conf.use_लघु_preamble)
		sinfo->bss_param.flags |= BSS_PARAM_FLAGS_SHORT_PREAMBLE;
	अगर (sdata->vअगर.bss_conf.use_लघु_slot)
		sinfo->bss_param.flags |= BSS_PARAM_FLAGS_SHORT_SLOT_TIME;
	sinfo->bss_param.dtim_period = sdata->vअगर.bss_conf.dtim_period;
	sinfo->bss_param.beacon_पूर्णांकerval = sdata->vअगर.bss_conf.beacon_पूर्णांक;

	sinfo->sta_flags.set = 0;
	sinfo->sta_flags.mask = BIT(NL80211_STA_FLAG_AUTHORIZED) |
				BIT(NL80211_STA_FLAG_SHORT_PREAMBLE) |
				BIT(NL80211_STA_FLAG_WME) |
				BIT(NL80211_STA_FLAG_MFP) |
				BIT(NL80211_STA_FLAG_AUTHENTICATED) |
				BIT(NL80211_STA_FLAG_ASSOCIATED) |
				BIT(NL80211_STA_FLAG_TDLS_PEER);
	अगर (test_sta_flag(sta, WLAN_STA_AUTHORIZED))
		sinfo->sta_flags.set |= BIT(NL80211_STA_FLAG_AUTHORIZED);
	अगर (test_sta_flag(sta, WLAN_STA_SHORT_PREAMBLE))
		sinfo->sta_flags.set |= BIT(NL80211_STA_FLAG_SHORT_PREAMBLE);
	अगर (sta->sta.wme)
		sinfo->sta_flags.set |= BIT(NL80211_STA_FLAG_WME);
	अगर (test_sta_flag(sta, WLAN_STA_MFP))
		sinfo->sta_flags.set |= BIT(NL80211_STA_FLAG_MFP);
	अगर (test_sta_flag(sta, WLAN_STA_AUTH))
		sinfo->sta_flags.set |= BIT(NL80211_STA_FLAG_AUTHENTICATED);
	अगर (test_sta_flag(sta, WLAN_STA_ASSOC))
		sinfo->sta_flags.set |= BIT(NL80211_STA_FLAG_ASSOCIATED);
	अगर (test_sta_flag(sta, WLAN_STA_TDLS_PEER))
		sinfo->sta_flags.set |= BIT(NL80211_STA_FLAG_TDLS_PEER);

	thr = sta_get_expected_throughput(sta);

	अगर (thr != 0) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_EXPECTED_THROUGHPUT);
		sinfo->expected_throughput = thr;
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_ACK_SIGNAL)) &&
	    sta->status_stats.ack_संकेत_filled) अणु
		sinfo->ack_संकेत = sta->status_stats.last_ack_संकेत;
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_ACK_SIGNAL);
	पूर्ण

	अगर (!(sinfo->filled & BIT_ULL(NL80211_STA_INFO_ACK_SIGNAL_AVG)) &&
	    sta->status_stats.ack_संकेत_filled) अणु
		sinfo->avg_ack_संकेत =
			-(s8)ewma_avg_संकेत_पढ़ो(
				&sta->status_stats.avg_ack_संकेत);
		sinfo->filled |=
			BIT_ULL(NL80211_STA_INFO_ACK_SIGNAL_AVG);
	पूर्ण

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_AIRTIME_LINK_METRIC);
		sinfo->airसमय_link_metric =
			airसमय_link_metric_get(local, sta);
	पूर्ण
पूर्ण

u32 sta_get_expected_throughput(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा rate_control_ref *ref = शून्य;
	u32 thr = 0;

	अगर (test_sta_flag(sta, WLAN_STA_RATE_CONTROL))
		ref = local->rate_ctrl;

	/* check अगर the driver has a SW RC implementation */
	अगर (ref && ref->ops->get_expected_throughput)
		thr = ref->ops->get_expected_throughput(sta->rate_ctrl_priv);
	अन्यथा
		thr = drv_get_expected_throughput(local, sta);

	वापस thr;
पूर्ण

अचिन्हित दीर्घ ieee80211_sta_last_active(काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_sta_rx_stats *stats = sta_get_last_rx_stats(sta);

	अगर (!sta->status_stats.last_ack ||
	    समय_after(stats->last_rx, sta->status_stats.last_ack))
		वापस stats->last_rx;
	वापस sta->status_stats.last_ack;
पूर्ण

अटल व्योम sta_update_codel_params(काष्ठा sta_info *sta, u32 thr)
अणु
	अगर (!sta->sdata->local->ops->wake_tx_queue)
		वापस;

	अगर (thr && thr < STA_SLOW_THRESHOLD * sta->local->num_sta) अणु
		sta->cparams.target = MS2TIME(50);
		sta->cparams.पूर्णांकerval = MS2TIME(300);
		sta->cparams.ecn = false;
	पूर्ण अन्यथा अणु
		sta->cparams.target = MS2TIME(20);
		sta->cparams.पूर्णांकerval = MS2TIME(100);
		sta->cparams.ecn = true;
	पूर्ण
पूर्ण

व्योम ieee80211_sta_set_expected_throughput(काष्ठा ieee80211_sta *pubsta,
					   u32 thr)
अणु
	काष्ठा sta_info *sta = container_of(pubsta, काष्ठा sta_info, sta);

	sta_update_codel_params(sta, thr);
पूर्ण
