<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Interface handling
 *
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright (c) 2006 Jiri Benc <jbenc@suse.cz>
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright (c) 2016        Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */
#समावेश <linux/slab.h>
#समावेश <linux/kernel.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/kcov.h>
#समावेश <net/mac80211.h>
#समावेश <net/ieee80211_radiotap.h>
#समावेश "ieee80211_i.h"
#समावेश "sta_info.h"
#समावेश "debugfs_netdev.h"
#समावेश "mesh.h"
#समावेश "led.h"
#समावेश "driver-ops.h"
#समावेश "wme.h"
#समावेश "rate.h"

/**
 * DOC: Interface list locking
 *
 * The पूर्णांकerface list in each काष्ठा ieee80211_local is रक्षित
 * three-fold:
 *
 * (1) modअगरications may only be करोne under the RTNL
 * (2) modअगरications and पढ़ोers are रक्षित against each other by
 *     the अगरlist_mtx.
 * (3) modअगरications are करोne in an RCU manner so atomic पढ़ोers
 *     can traverse the list in RCU-safe blocks.
 *
 * As a consequence, पढ़ोs (traversals) of the list can be रक्षित
 * by either the RTNL, the अगरlist_mtx or RCU.
 */

अटल व्योम ieee80211_अगरace_work(काष्ठा work_काष्ठा *work);

bool __ieee80211_recalc_txघातer(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	पूर्णांक घातer;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (!chanctx_conf) अणु
		rcu_पढ़ो_unlock();
		वापस false;
	पूर्ण

	घातer = ieee80211_chandef_max_घातer(&chanctx_conf->def);
	rcu_पढ़ो_unlock();

	अगर (sdata->user_घातer_level != IEEE80211_UNSET_POWER_LEVEL)
		घातer = min(घातer, sdata->user_घातer_level);

	अगर (sdata->ap_घातer_level != IEEE80211_UNSET_POWER_LEVEL)
		घातer = min(घातer, sdata->ap_घातer_level);

	अगर (घातer != sdata->vअगर.bss_conf.txघातer) अणु
		sdata->vअगर.bss_conf.txघातer = घातer;
		ieee80211_hw_config(sdata->local, 0);
		वापस true;
	पूर्ण

	वापस false;
पूर्ण

व्योम ieee80211_recalc_txघातer(काष्ठा ieee80211_sub_अगर_data *sdata,
			      bool update_bss)
अणु
	अगर (__ieee80211_recalc_txघातer(sdata) ||
	    (update_bss && ieee80211_sdata_running(sdata)))
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_TXPOWER);
पूर्ण

अटल u32 __ieee80211_idle_off(काष्ठा ieee80211_local *local)
अणु
	अगर (!(local->hw.conf.flags & IEEE80211_CONF_IDLE))
		वापस 0;

	local->hw.conf.flags &= ~IEEE80211_CONF_IDLE;
	वापस IEEE80211_CONF_CHANGE_IDLE;
पूर्ण

अटल u32 __ieee80211_idle_on(काष्ठा ieee80211_local *local)
अणु
	अगर (local->hw.conf.flags & IEEE80211_CONF_IDLE)
		वापस 0;

	ieee80211_flush_queues(local, शून्य, false);

	local->hw.conf.flags |= IEEE80211_CONF_IDLE;
	वापस IEEE80211_CONF_CHANGE_IDLE;
पूर्ण

अटल u32 __ieee80211_recalc_idle(काष्ठा ieee80211_local *local,
				   bool क्रमce_active)
अणु
	bool working, scanning, active;
	अचिन्हित पूर्णांक led_trig_start = 0, led_trig_stop = 0;

	lockdep_निश्चित_held(&local->mtx);

	active = क्रमce_active ||
		 !list_empty(&local->chanctx_list) ||
		 local->monitors;

	working = !local->ops->reमुख्य_on_channel &&
		  !list_empty(&local->roc_list);

	scanning = test_bit(SCAN_SW_SCANNING, &local->scanning) ||
		   test_bit(SCAN_ONCHANNEL_SCANNING, &local->scanning);

	अगर (working || scanning)
		led_trig_start |= IEEE80211_TPT_LEDTRIG_FL_WORK;
	अन्यथा
		led_trig_stop |= IEEE80211_TPT_LEDTRIG_FL_WORK;

	अगर (active)
		led_trig_start |= IEEE80211_TPT_LEDTRIG_FL_CONNECTED;
	अन्यथा
		led_trig_stop |= IEEE80211_TPT_LEDTRIG_FL_CONNECTED;

	ieee80211_mod_tpt_led_trig(local, led_trig_start, led_trig_stop);

	अगर (working || scanning || active)
		वापस __ieee80211_idle_off(local);
	वापस __ieee80211_idle_on(local);
पूर्ण

u32 ieee80211_idle_off(काष्ठा ieee80211_local *local)
अणु
	वापस __ieee80211_recalc_idle(local, true);
पूर्ण

व्योम ieee80211_recalc_idle(काष्ठा ieee80211_local *local)
अणु
	u32 change = __ieee80211_recalc_idle(local, false);
	अगर (change)
		ieee80211_hw_config(local, change);
पूर्ण

अटल पूर्णांक ieee80211_verअगरy_mac(काष्ठा ieee80211_sub_अगर_data *sdata, u8 *addr,
				bool check_dup)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *iter;
	u64 new, mask, पंचांगp;
	u8 *m;
	पूर्णांक ret = 0;

	अगर (is_zero_ether_addr(local->hw.wiphy->addr_mask))
		वापस 0;

	m = addr;
	new =	((u64)m[0] << 5*8) | ((u64)m[1] << 4*8) |
		((u64)m[2] << 3*8) | ((u64)m[3] << 2*8) |
		((u64)m[4] << 1*8) | ((u64)m[5] << 0*8);

	m = local->hw.wiphy->addr_mask;
	mask =	((u64)m[0] << 5*8) | ((u64)m[1] << 4*8) |
		((u64)m[2] << 3*8) | ((u64)m[3] << 2*8) |
		((u64)m[4] << 1*8) | ((u64)m[5] << 0*8);

	अगर (!check_dup)
		वापस ret;

	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry(iter, &local->पूर्णांकerfaces, list) अणु
		अगर (iter == sdata)
			जारी;

		अगर (iter->vअगर.type == NL80211_IFTYPE_MONITOR &&
		    !(iter->u.mntr.flags & MONITOR_FLAG_ACTIVE))
			जारी;

		m = iter->vअगर.addr;
		पंचांगp =	((u64)m[0] << 5*8) | ((u64)m[1] << 4*8) |
			((u64)m[2] << 3*8) | ((u64)m[3] << 2*8) |
			((u64)m[4] << 1*8) | ((u64)m[5] << 0*8);

		अगर ((new & ~mask) != (पंचांगp & ~mask)) अणु
			ret = -EINVAL;
			अवरोध;
		पूर्ण
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_change_mac(काष्ठा net_device *dev, व्योम *addr)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा sockaddr *sa = addr;
	bool check_dup = true;
	पूर्णांक ret;

	अगर (ieee80211_sdata_running(sdata))
		वापस -EBUSY;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR &&
	    !(sdata->u.mntr.flags & MONITOR_FLAG_ACTIVE))
		check_dup = false;

	ret = ieee80211_verअगरy_mac(sdata, sa->sa_data, check_dup);
	अगर (ret)
		वापस ret;

	ret = eth_mac_addr(dev, sa);

	अगर (ret == 0)
		स_नकल(sdata->vअगर.addr, sa->sa_data, ETH_ALEN);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक identical_mac_addr_allowed(पूर्णांक type1, पूर्णांक type2)
अणु
	वापस type1 == NL80211_IFTYPE_MONITOR ||
		type2 == NL80211_IFTYPE_MONITOR ||
		type1 == NL80211_IFTYPE_P2P_DEVICE ||
		type2 == NL80211_IFTYPE_P2P_DEVICE ||
		(type1 == NL80211_IFTYPE_AP && type2 == NL80211_IFTYPE_AP_VLAN) ||
		(type1 == NL80211_IFTYPE_AP_VLAN &&
			(type2 == NL80211_IFTYPE_AP ||
			 type2 == NL80211_IFTYPE_AP_VLAN));
पूर्ण

अटल पूर्णांक ieee80211_check_concurrent_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata,
					    क्रमागत nl80211_अगरtype अगरtype)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *nsdata;
	पूर्णांक ret;

	ASSERT_RTNL();

	/* we hold the RTNL here so can safely walk the list */
	list_क्रम_each_entry(nsdata, &local->पूर्णांकerfaces, list) अणु
		अगर (nsdata != sdata && ieee80211_sdata_running(nsdata)) अणु
			/*
			 * Only OCB and monitor mode may coexist
			 */
			अगर ((sdata->vअगर.type == NL80211_IFTYPE_OCB &&
			     nsdata->vअगर.type != NL80211_IFTYPE_MONITOR) ||
			    (sdata->vअगर.type != NL80211_IFTYPE_MONITOR &&
			     nsdata->vअगर.type == NL80211_IFTYPE_OCB))
				वापस -EBUSY;

			/*
			 * Allow only a single IBSS पूर्णांकerface to be up at any
			 * समय. This is restricted because beacon distribution
			 * cannot work properly अगर both are in the same IBSS.
			 *
			 * To हटाओ this restriction we'd have to disallow them
			 * from setting the same SSID on dअगरferent IBSS पूर्णांकerfaces
			 * beदीर्घing to the same hardware. Then, however, we're
			 * faced with having to aकरोpt two dअगरferent TSF समयrs...
			 */
			अगर (अगरtype == NL80211_IFTYPE_ADHOC &&
			    nsdata->vअगर.type == NL80211_IFTYPE_ADHOC)
				वापस -EBUSY;
			/*
			 * will not add another पूर्णांकerface जबतक any channel
			 * चयन is active.
			 */
			अगर (nsdata->vअगर.csa_active)
				वापस -EBUSY;

			/*
			 * The reमुख्यing checks are only perक्रमmed क्रम पूर्णांकerfaces
			 * with the same MAC address.
			 */
			अगर (!ether_addr_equal(sdata->vअगर.addr,
					      nsdata->vअगर.addr))
				जारी;

			/*
			 * check whether it may have the same address
			 */
			अगर (!identical_mac_addr_allowed(अगरtype,
							nsdata->vअगर.type))
				वापस -ENOTUNIQ;

			/*
			 * can only add VLANs to enabled APs
			 */
			अगर (अगरtype == NL80211_IFTYPE_AP_VLAN &&
			    nsdata->vअगर.type == NL80211_IFTYPE_AP)
				sdata->bss = &nsdata->u.ap;
		पूर्ण
	पूर्ण

	mutex_lock(&local->chanctx_mtx);
	ret = ieee80211_check_combinations(sdata, शून्य, 0, 0);
	mutex_unlock(&local->chanctx_mtx);
	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_check_queues(काष्ठा ieee80211_sub_अगर_data *sdata,
				  क्रमागत nl80211_अगरtype अगरtype)
अणु
	पूर्णांक n_queues = sdata->local->hw.queues;
	पूर्णांक i;

	अगर (अगरtype == NL80211_IFTYPE_न_अंक)
		वापस 0;

	अगर (अगरtype != NL80211_IFTYPE_P2P_DEVICE) अणु
		क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
			अगर (WARN_ON_ONCE(sdata->vअगर.hw_queue[i] ==
					 IEEE80211_INVAL_HW_QUEUE))
				वापस -EINVAL;
			अगर (WARN_ON_ONCE(sdata->vअगर.hw_queue[i] >=
					 n_queues))
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर ((अगरtype != NL80211_IFTYPE_AP &&
	     अगरtype != NL80211_IFTYPE_P2P_GO &&
	     अगरtype != NL80211_IFTYPE_MESH_POINT) ||
	    !ieee80211_hw_check(&sdata->local->hw, QUEUE_CONTROL)) अणु
		sdata->vअगर.cab_queue = IEEE80211_INVAL_HW_QUEUE;
		वापस 0;
	पूर्ण

	अगर (WARN_ON_ONCE(sdata->vअगर.cab_queue == IEEE80211_INVAL_HW_QUEUE))
		वापस -EINVAL;

	अगर (WARN_ON_ONCE(sdata->vअगर.cab_queue >= n_queues))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_खोलो(काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	पूर्णांक err;

	/* fail early अगर user set an invalid address */
	अगर (!is_valid_ether_addr(dev->dev_addr))
		वापस -EADDRNOTAVAIL;

	err = ieee80211_check_concurrent_अगरace(sdata, sdata->vअगर.type);
	अगर (err)
		वापस err;

	wiphy_lock(sdata->local->hw.wiphy);
	err = ieee80211_करो_खोलो(&sdata->wdev, true);
	wiphy_unlock(sdata->local->hw.wiphy);

	वापस err;
पूर्ण

अटल व्योम ieee80211_करो_stop(काष्ठा ieee80211_sub_अगर_data *sdata, bool going_करोwn)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	अचिन्हित दीर्घ flags;
	काष्ठा sk_buff *skb, *पंचांगp;
	u32 hw_reconf_flags = 0;
	पूर्णांक i, flushed;
	काष्ठा ps_data *ps;
	काष्ठा cfg80211_chan_def chandef;
	bool cancel_scan;
	काष्ठा cfg80211_nan_func *func;

	clear_bit(SDATA_STATE_RUNNING, &sdata->state);

	cancel_scan = rcu_access_poपूर्णांकer(local->scan_sdata) == sdata;
	अगर (cancel_scan)
		ieee80211_scan_cancel(local);

	/*
	 * Stop TX on this पूर्णांकerface first.
	 */
	अगर (sdata->dev)
		netअगर_tx_stop_all_queues(sdata->dev);

	ieee80211_roc_purge(local, sdata);

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
		ieee80211_mgd_stop(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ieee80211_ibss_stop(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (sdata->u.mntr.flags & MONITOR_FLAG_COOK_FRAMES)
			अवरोध;
		list_del_rcu(&sdata->u.mntr.list);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * Remove all stations associated with this पूर्णांकerface.
	 *
	 * This must be करोne beक्रमe calling ops->हटाओ_पूर्णांकerface()
	 * because otherwise we can later invoke ops->sta_notअगरy()
	 * whenever the STAs are हटाओd, and that invalidates driver
	 * assumptions about always getting a vअगर poपूर्णांकer that is valid
	 * (because अगर we हटाओ a STA after ops->हटाओ_पूर्णांकerface()
	 * the driver will have हटाओd the vअगर info alपढ़ोy!)
	 *
	 * For AP_VLANs stations may exist since there's nothing अन्यथा that
	 * would have हटाओd them, but in other modes there shouldn't
	 * be any stations.
	 */
	flushed = sta_info_flush(sdata);
	WARN_ON_ONCE(sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN && flushed > 0);

	/* करोn't count this पूर्णांकerface क्रम allmulti जबतक it is करोwn */
	अगर (sdata->flags & IEEE80211_SDATA_ALLMULTI)
		atomic_dec(&local->अगरf_allmultis);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		local->fअगर_pspoll--;
		local->fअगर_probe_req--;
	पूर्ण अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC) अणु
		local->fअगर_probe_req--;
	पूर्ण

	अगर (sdata->dev) अणु
		netअगर_addr_lock_bh(sdata->dev);
		spin_lock_bh(&local->filter_lock);
		__hw_addr_unsync(&local->mc_list, &sdata->dev->mc,
				 sdata->dev->addr_len);
		spin_unlock_bh(&local->filter_lock);
		netअगर_addr_unlock_bh(sdata->dev);
	पूर्ण

	del_समयr_sync(&local->dynamic_ps_समयr);
	cancel_work_sync(&local->dynamic_ps_enable_work);

	cancel_work_sync(&sdata->recalc_smps);
	sdata_lock(sdata);
	mutex_lock(&local->mtx);
	sdata->vअगर.csa_active = false;
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION)
		sdata->u.mgd.csa_रुकोing_bcn = false;
	अगर (sdata->csa_block_tx) अणु
		ieee80211_wake_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
		sdata->csa_block_tx = false;
	पूर्ण
	mutex_unlock(&local->mtx);
	sdata_unlock(sdata);

	cancel_work_sync(&sdata->csa_finalize_work);

	cancel_delayed_work_sync(&sdata->dfs_cac_समयr_work);

	अगर (sdata->wdev.cac_started) अणु
		chandef = sdata->vअगर.bss_conf.chandef;
		WARN_ON(local->suspended);
		mutex_lock(&local->mtx);
		ieee80211_vअगर_release_channel(sdata);
		mutex_unlock(&local->mtx);
		cfg80211_cac_event(sdata->dev, &chandef,
				   NL80211_RADAR_CAC_ABORTED,
				   GFP_KERNEL);
	पूर्ण

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		WARN_ON(!list_empty(&sdata->u.ap.vlans));
	पूर्ण अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		/* हटाओ all packets in parent bc_buf poपूर्णांकing to this dev */
		ps = &sdata->bss->ps;

		spin_lock_irqsave(&ps->bc_buf.lock, flags);
		skb_queue_walk_safe(&ps->bc_buf, skb, पंचांगp) अणु
			अगर (skb->dev == sdata->dev) अणु
				__skb_unlink(skb, &ps->bc_buf);
				local->total_ps_buffered--;
				ieee80211_मुक्त_txskb(&local->hw, skb);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&ps->bc_buf.lock, flags);
	पूर्ण

	अगर (going_करोwn)
		local->खोलो_count--;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP_VLAN:
		mutex_lock(&local->mtx);
		list_del(&sdata->u.vlan.list);
		mutex_unlock(&local->mtx);
		RCU_INIT_POINTER(sdata->vअगर.chanctx_conf, शून्य);
		/* see comment in the शेष हाल below */
		ieee80211_मुक्त_keys(sdata, true);
		/* no need to tell driver */
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (sdata->u.mntr.flags & MONITOR_FLAG_COOK_FRAMES) अणु
			local->cooked_mntrs--;
			अवरोध;
		पूर्ण

		local->monitors--;
		अगर (local->monitors == 0) अणु
			local->hw.conf.flags &= ~IEEE80211_CONF_MONITOR;
			hw_reconf_flags |= IEEE80211_CONF_CHANGE_MONITOR;
		पूर्ण

		ieee80211_adjust_monitor_flags(sdata, -1);
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
		/* clean all the functions */
		spin_lock_bh(&sdata->u.nan.func_lock);

		idr_क्रम_each_entry(&sdata->u.nan.function_inst_ids, func, i) अणु
			idr_हटाओ(&sdata->u.nan.function_inst_ids, i);
			cfg80211_मुक्त_nan_func(func);
		पूर्ण
		idr_destroy(&sdata->u.nan.function_inst_ids);

		spin_unlock_bh(&sdata->u.nan.func_lock);
		अवरोध;
	हाल NL80211_IFTYPE_P2P_DEVICE:
		/* relies on synchronize_rcu() below */
		RCU_INIT_POINTER(local->p2p_sdata, शून्य);
		fallthrough;
	शेष:
		cancel_work_sync(&sdata->work);
		/*
		 * When we get here, the पूर्णांकerface is marked करोwn.
		 * Free the reमुख्यing keys, अगर there are any
		 * (which can happen in AP mode अगर userspace sets
		 * keys beक्रमe the पूर्णांकerface is operating)
		 *
		 * Force the key मुक्तing to always synchronize_net()
		 * to रुको क्रम the RX path in हाल it is using this
		 * पूर्णांकerface enqueuing frames at this very समय on
		 * another CPU.
		 */
		ieee80211_मुक्त_keys(sdata, true);
		skb_queue_purge(&sdata->skb_queue);
	पूर्ण

	spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
	क्रम (i = 0; i < IEEE80211_MAX_QUEUES; i++) अणु
		skb_queue_walk_safe(&local->pending[i], skb, पंचांगp) अणु
			काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
			अगर (info->control.vअगर == &sdata->vअगर) अणु
				__skb_unlink(skb, &local->pending[i]);
				ieee80211_मुक्त_txskb(&local->hw, skb);
			पूर्ण
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		ieee80211_txq_हटाओ_vlan(local, sdata);

	sdata->bss = शून्य;

	अगर (local->खोलो_count == 0)
		ieee80211_clear_tx_pending(local);

	sdata->vअगर.bss_conf.beacon_पूर्णांक = 0;

	/*
	 * If the पूर्णांकerface goes करोwn जबतक suspended, presumably because
	 * the device was unplugged and that happens beक्रमe our resume,
	 * then the driver is alपढ़ोy unconfigured and the reमुख्यder of
	 * this function isn't needed.
	 * XXX: what about WoWLAN? If the device has software state, e.g.
	 *	memory allocated, it might expect tearकरोwn commands from
	 *	mac80211 here?
	 */
	अगर (local->suspended) अणु
		WARN_ON(local->wowlan);
		WARN_ON(rtnl_dereference(local->monitor_sdata));
		वापस;
	पूर्ण

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP_VLAN:
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (local->monitors == 0)
			ieee80211_del_भव_monitor(local);

		mutex_lock(&local->mtx);
		ieee80211_recalc_idle(local);
		mutex_unlock(&local->mtx);

		अगर (!(sdata->u.mntr.flags & MONITOR_FLAG_ACTIVE))
			अवरोध;

		fallthrough;
	शेष:
		अगर (going_करोwn)
			drv_हटाओ_पूर्णांकerface(local, sdata);
	पूर्ण

	ieee80211_recalc_ps(local);

	अगर (cancel_scan)
		flush_delayed_work(&local->scan_work);

	अगर (local->खोलो_count == 0) अणु
		ieee80211_stop_device(local);

		/* no reconfiguring after stop! */
		वापस;
	पूर्ण

	/* करो after stop to aव्योम reconfiguring when we stop anyway */
	ieee80211_configure_filter(local);
	ieee80211_hw_config(local, hw_reconf_flags);

	अगर (local->monitors == local->खोलो_count)
		ieee80211_add_भव_monitor(local);
पूर्ण

अटल पूर्णांक ieee80211_stop(काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	/* बंद all dependent VLAN पूर्णांकerfaces beक्रमe locking wiphy */
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		काष्ठा ieee80211_sub_अगर_data *vlan, *पंचांगpsdata;

		list_क्रम_each_entry_safe(vlan, पंचांगpsdata, &sdata->u.ap.vlans,
					 u.vlan.list)
			dev_बंद(vlan->dev);
	पूर्ण

	wiphy_lock(sdata->local->hw.wiphy);
	ieee80211_करो_stop(sdata, true);
	wiphy_unlock(sdata->local->hw.wiphy);

	वापस 0;
पूर्ण

अटल व्योम ieee80211_set_multicast_list(काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक allmulti, sdata_allmulti;

	allmulti = !!(dev->flags & IFF_ALLMULTI);
	sdata_allmulti = !!(sdata->flags & IEEE80211_SDATA_ALLMULTI);

	अगर (allmulti != sdata_allmulti) अणु
		अगर (dev->flags & IFF_ALLMULTI)
			atomic_inc(&local->अगरf_allmultis);
		अन्यथा
			atomic_dec(&local->अगरf_allmultis);
		sdata->flags ^= IEEE80211_SDATA_ALLMULTI;
	पूर्ण

	spin_lock_bh(&local->filter_lock);
	__hw_addr_sync(&local->mc_list, &dev->mc, dev->addr_len);
	spin_unlock_bh(&local->filter_lock);
	ieee80211_queue_work(&local->hw, &local->reconfig_filter);
पूर्ण

/*
 * Called when the netdev is हटाओd or, by the code below, beक्रमe
 * the पूर्णांकerface type changes.
 */
अटल व्योम ieee80211_tearकरोwn_sdata(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	/* मुक्त extra data */
	ieee80211_मुक्त_keys(sdata, false);

	ieee80211_debugfs_हटाओ_netdev(sdata);

	ieee80211_destroy_frag_cache(&sdata->frags);

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
		ieee80211_mesh_tearकरोwn_sdata(sdata);
पूर्ण

अटल व्योम ieee80211_uninit(काष्ठा net_device *dev)
अणु
	ieee80211_tearकरोwn_sdata(IEEE80211_DEV_TO_SUB_IF(dev));
पूर्ण

अटल u16 ieee80211_netdev_select_queue(काष्ठा net_device *dev,
					 काष्ठा sk_buff *skb,
					 काष्ठा net_device *sb_dev)
अणु
	वापस ieee80211_select_queue(IEEE80211_DEV_TO_SUB_IF(dev), skb);
पूर्ण

अटल व्योम
ieee80211_get_stats64(काष्ठा net_device *dev, काष्ठा rtnl_link_stats64 *stats)
अणु
	dev_fetch_sw_netstats(stats, dev->tstats);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ieee80211_dataअगर_ops = अणु
	.nकरो_खोलो		= ieee80211_खोलो,
	.nकरो_stop		= ieee80211_stop,
	.nकरो_uninit		= ieee80211_uninit,
	.nकरो_start_xmit		= ieee80211_subअगर_start_xmit,
	.nकरो_set_rx_mode	= ieee80211_set_multicast_list,
	.nकरो_set_mac_address 	= ieee80211_change_mac,
	.nकरो_select_queue	= ieee80211_netdev_select_queue,
	.nकरो_get_stats64	= ieee80211_get_stats64,
पूर्ण;

अटल u16 ieee80211_monitor_select_queue(काष्ठा net_device *dev,
					  काष्ठा sk_buff *skb,
					  काष्ठा net_device *sb_dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	काष्ठा ieee80211_hdr *hdr;
	पूर्णांक len_rthdr;

	अगर (local->hw.queues < IEEE80211_NUM_ACS)
		वापस 0;

	/* reset flags and info beक्रमe parsing radiotap header */
	स_रखो(info, 0, माप(*info));

	अगर (!ieee80211_parse_tx_radiotap(skb, dev))
		वापस 0; /* करोesn't matter, frame will be dropped */

	len_rthdr = ieee80211_get_radiotap_len(skb->data);
	hdr = (काष्ठा ieee80211_hdr *)(skb->data + len_rthdr);
	अगर (skb->len < len_rthdr + 2 ||
	    skb->len < len_rthdr + ieee80211_hdrlen(hdr->frame_control))
		वापस 0; /* करोesn't matter, frame will be dropped */

	वापस ieee80211_select_queue_80211(sdata, skb, hdr);
पूर्ण

अटल स्थिर काष्ठा net_device_ops ieee80211_monitorअगर_ops = अणु
	.nकरो_खोलो		= ieee80211_खोलो,
	.nकरो_stop		= ieee80211_stop,
	.nकरो_uninit		= ieee80211_uninit,
	.nकरो_start_xmit		= ieee80211_monitor_start_xmit,
	.nकरो_set_rx_mode	= ieee80211_set_multicast_list,
	.nकरो_set_mac_address 	= ieee80211_change_mac,
	.nकरो_select_queue	= ieee80211_monitor_select_queue,
	.nकरो_get_stats64	= ieee80211_get_stats64,
पूर्ण;

अटल स्थिर काष्ठा net_device_ops ieee80211_dataअगर_8023_ops = अणु
	.nकरो_खोलो		= ieee80211_खोलो,
	.nकरो_stop		= ieee80211_stop,
	.nकरो_uninit		= ieee80211_uninit,
	.nकरो_start_xmit		= ieee80211_subअगर_start_xmit_8023,
	.nकरो_set_rx_mode	= ieee80211_set_multicast_list,
	.nकरो_set_mac_address	= ieee80211_change_mac,
	.nकरो_select_queue	= ieee80211_netdev_select_queue,
	.nकरो_get_stats64	= ieee80211_get_stats64,
पूर्ण;

अटल bool ieee80211_अगरtype_supports_hdr_offload(क्रमागत nl80211_अगरtype अगरtype)
अणु
	चयन (अगरtype) अणु
	/* P2P GO and client are mapped to AP/STATION types */
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_STATION:
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल bool ieee80211_set_sdata_offload_flags(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	u32 flags;

	flags = sdata->vअगर.offload_flags;

	अगर (ieee80211_hw_check(&local->hw, SUPPORTS_TX_ENCAP_OFFLOAD) &&
	    ieee80211_अगरtype_supports_hdr_offload(sdata->vअगर.type)) अणु
		flags |= IEEE80211_OFFLOAD_ENCAP_ENABLED;

		अगर (!ieee80211_hw_check(&local->hw, SUPPORTS_TX_FRAG) &&
		    local->hw.wiphy->frag_threshold != (u32)-1)
			flags &= ~IEEE80211_OFFLOAD_ENCAP_ENABLED;

		अगर (local->monitors)
			flags &= ~IEEE80211_OFFLOAD_ENCAP_ENABLED;
	पूर्ण अन्यथा अणु
		flags &= ~IEEE80211_OFFLOAD_ENCAP_ENABLED;
	पूर्ण

	अगर (ieee80211_hw_check(&local->hw, SUPPORTS_RX_DECAP_OFFLOAD) &&
	    ieee80211_अगरtype_supports_hdr_offload(sdata->vअगर.type)) अणु
		flags |= IEEE80211_OFFLOAD_DECAP_ENABLED;

		अगर (local->monitors &&
		    !ieee80211_hw_check(&local->hw, SUPPORTS_CONC_MON_RX_DECAP))
			flags &= ~IEEE80211_OFFLOAD_DECAP_ENABLED;
	पूर्ण अन्यथा अणु
		flags &= ~IEEE80211_OFFLOAD_DECAP_ENABLED;
	पूर्ण

	अगर (sdata->vअगर.offload_flags == flags)
		वापस false;

	sdata->vअगर.offload_flags = flags;
	ieee80211_check_fast_rx_अगरace(sdata);
	वापस true;
पूर्ण

अटल व्योम ieee80211_set_vअगर_encap_ops(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *bss = sdata;
	bool enabled;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		अगर (!sdata->bss)
			वापस;

		bss = container_of(sdata->bss, काष्ठा ieee80211_sub_अगर_data, u.ap);
	पूर्ण

	अगर (!ieee80211_hw_check(&local->hw, SUPPORTS_TX_ENCAP_OFFLOAD) ||
	    !ieee80211_अगरtype_supports_hdr_offload(bss->vअगर.type))
		वापस;

	enabled = bss->vअगर.offload_flags & IEEE80211_OFFLOAD_ENCAP_ENABLED;
	अगर (sdata->wdev.use_4addr &&
	    !(bss->vअगर.offload_flags & IEEE80211_OFFLOAD_ENCAP_4ADDR))
		enabled = false;

	sdata->dev->netdev_ops = enabled ? &ieee80211_dataअगर_8023_ops :
					   &ieee80211_dataअगर_ops;
पूर्ण

अटल व्योम ieee80211_recalc_sdata_offload(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *vsdata;

	अगर (ieee80211_set_sdata_offload_flags(sdata)) अणु
		drv_update_vअगर_offload(local, sdata);
		ieee80211_set_vअगर_encap_ops(sdata);
	पूर्ण

	list_क्रम_each_entry(vsdata, &local->पूर्णांकerfaces, list) अणु
		अगर (vsdata->vअगर.type != NL80211_IFTYPE_AP_VLAN ||
		    vsdata->bss != &sdata->u.ap)
			जारी;

		ieee80211_set_vअगर_encap_ops(vsdata);
	पूर्ण
पूर्ण

व्योम ieee80211_recalc_offload(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	अगर (!ieee80211_hw_check(&local->hw, SUPPORTS_TX_ENCAP_OFFLOAD))
		वापस;

	mutex_lock(&local->अगरlist_mtx);

	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;

		ieee80211_recalc_sdata_offload(sdata);
	पूर्ण

	mutex_unlock(&local->अगरlist_mtx);
पूर्ण

व्योम ieee80211_adjust_monitor_flags(काष्ठा ieee80211_sub_अगर_data *sdata,
				    स्थिर पूर्णांक offset)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	u32 flags = sdata->u.mntr.flags;

#घोषणा ADJUST(_f, _s)	करो अणु					\
	अगर (flags & MONITOR_FLAG_##_f)				\
		local->fअगर_##_s += offset;			\
	पूर्ण जबतक (0)

	ADJUST(FCSFAIL, fcsfail);
	ADJUST(PLCPFAIL, plcpfail);
	ADJUST(CONTROL, control);
	ADJUST(CONTROL, pspoll);
	ADJUST(OTHER_BSS, other_bss);

#अघोषित ADJUST
पूर्ण

अटल व्योम ieee80211_set_शेष_queues(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक i;

	क्रम (i = 0; i < IEEE80211_NUM_ACS; i++) अणु
		अगर (ieee80211_hw_check(&local->hw, QUEUE_CONTROL))
			sdata->vअगर.hw_queue[i] = IEEE80211_INVAL_HW_QUEUE;
		अन्यथा अगर (local->hw.queues >= IEEE80211_NUM_ACS)
			sdata->vअगर.hw_queue[i] = i;
		अन्यथा
			sdata->vअगर.hw_queue[i] = 0;
	पूर्ण
	sdata->vअगर.cab_queue = IEEE80211_INVAL_HW_QUEUE;
पूर्ण

पूर्णांक ieee80211_add_भव_monitor(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक ret;

	अगर (!ieee80211_hw_check(&local->hw, WANT_MONITOR_VIF))
		वापस 0;

	ASSERT_RTNL();

	अगर (local->monitor_sdata)
		वापस 0;

	sdata = kzalloc(माप(*sdata) + local->hw.vअगर_data_size, GFP_KERNEL);
	अगर (!sdata)
		वापस -ENOMEM;

	/* set up data */
	sdata->local = local;
	sdata->vअगर.type = NL80211_IFTYPE_MONITOR;
	snम_लिखो(sdata->name, IFNAMSIZ, "%s-monitor",
		 wiphy_name(local->hw.wiphy));
	sdata->wdev.अगरtype = NL80211_IFTYPE_MONITOR;

	sdata->encrypt_headroom = IEEE80211_ENCRYPT_HEADROOM;

	ieee80211_set_शेष_queues(sdata);

	ret = drv_add_पूर्णांकerface(local, sdata);
	अगर (WARN_ON(ret)) अणु
		/* ok .. stupid driver, it asked क्रम this! */
		kमुक्त(sdata);
		वापस ret;
	पूर्ण

	set_bit(SDATA_STATE_RUNNING, &sdata->state);

	ret = ieee80211_check_queues(sdata, NL80211_IFTYPE_MONITOR);
	अगर (ret) अणु
		kमुक्त(sdata);
		वापस ret;
	पूर्ण

	mutex_lock(&local->अगरlist_mtx);
	rcu_assign_poपूर्णांकer(local->monitor_sdata, sdata);
	mutex_unlock(&local->अगरlist_mtx);

	mutex_lock(&local->mtx);
	ret = ieee80211_vअगर_use_channel(sdata, &local->monitor_chandef,
					IEEE80211_CHANCTX_EXCLUSIVE);
	mutex_unlock(&local->mtx);
	अगर (ret) अणु
		mutex_lock(&local->अगरlist_mtx);
		RCU_INIT_POINTER(local->monitor_sdata, शून्य);
		mutex_unlock(&local->अगरlist_mtx);
		synchronize_net();
		drv_हटाओ_पूर्णांकerface(local, sdata);
		kमुक्त(sdata);
		वापस ret;
	पूर्ण

	skb_queue_head_init(&sdata->skb_queue);
	INIT_WORK(&sdata->work, ieee80211_अगरace_work);

	वापस 0;
पूर्ण

व्योम ieee80211_del_भव_monitor(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	अगर (!ieee80211_hw_check(&local->hw, WANT_MONITOR_VIF))
		वापस;

	ASSERT_RTNL();

	mutex_lock(&local->अगरlist_mtx);

	sdata = rcu_dereference_रक्षित(local->monitor_sdata,
					  lockdep_is_held(&local->अगरlist_mtx));
	अगर (!sdata) अणु
		mutex_unlock(&local->अगरlist_mtx);
		वापस;
	पूर्ण

	RCU_INIT_POINTER(local->monitor_sdata, शून्य);
	mutex_unlock(&local->अगरlist_mtx);

	synchronize_net();

	mutex_lock(&local->mtx);
	ieee80211_vअगर_release_channel(sdata);
	mutex_unlock(&local->mtx);

	drv_हटाओ_पूर्णांकerface(local, sdata);

	kमुक्त(sdata);
पूर्ण

/*
 * NOTE: Be very careful when changing this function, it must NOT वापस
 * an error on पूर्णांकerface type changes that have been pre-checked, so most
 * checks should be in ieee80211_check_concurrent_अगरace.
 */
पूर्णांक ieee80211_करो_खोलो(काष्ठा wireless_dev *wdev, bool coming_up)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	काष्ठा net_device *dev = wdev->netdev;
	काष्ठा ieee80211_local *local = sdata->local;
	u32 changed = 0;
	पूर्णांक res;
	u32 hw_reconf_flags = 0;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP_VLAN: अणु
		काष्ठा ieee80211_sub_अगर_data *master;

		अगर (!sdata->bss)
			वापस -ENOLINK;

		mutex_lock(&local->mtx);
		list_add(&sdata->u.vlan.list, &sdata->bss->vlans);
		mutex_unlock(&local->mtx);

		master = container_of(sdata->bss,
				      काष्ठा ieee80211_sub_अगर_data, u.ap);
		sdata->control_port_protocol =
			master->control_port_protocol;
		sdata->control_port_no_encrypt =
			master->control_port_no_encrypt;
		sdata->control_port_over_nl80211 =
			master->control_port_over_nl80211;
		sdata->control_port_no_preauth =
			master->control_port_no_preauth;
		sdata->vअगर.cab_queue = master->vअगर.cab_queue;
		स_नकल(sdata->vअगर.hw_queue, master->vअगर.hw_queue,
		       माप(sdata->vअगर.hw_queue));
		sdata->vअगर.bss_conf.chandef = master->vअगर.bss_conf.chandef;

		mutex_lock(&local->key_mtx);
		sdata->crypto_tx_tailroom_needed_cnt +=
			master->crypto_tx_tailroom_needed_cnt;
		mutex_unlock(&local->key_mtx);

		अवरोध;
		पूर्ण
	हाल NL80211_IFTYPE_AP:
		sdata->bss = &sdata->u.ap;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_P2P_DEVICE:
	हाल NL80211_IFTYPE_OCB:
	हाल NL80211_IFTYPE_न_अंक:
		/* no special treaपंचांगent */
		अवरोध;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NUM_NL80211_IFTYPES:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_WDS:
		/* cannot happen */
		WARN_ON(1);
		अवरोध;
	पूर्ण

	अगर (local->खोलो_count == 0) अणु
		res = drv_start(local);
		अगर (res)
			जाओ err_del_bss;
		/* we're brought up, everything changes */
		hw_reconf_flags = ~0;
		ieee80211_led_radio(local, true);
		ieee80211_mod_tpt_led_trig(local,
					   IEEE80211_TPT_LEDTRIG_FL_RADIO, 0);
	पूर्ण

	/*
	 * Copy the hopefully now-present MAC address to
	 * this पूर्णांकerface, अगर it has the special null one.
	 */
	अगर (dev && is_zero_ether_addr(dev->dev_addr)) अणु
		स_नकल(dev->dev_addr,
		       local->hw.wiphy->perm_addr,
		       ETH_ALEN);
		स_नकल(dev->perm_addr, dev->dev_addr, ETH_ALEN);

		अगर (!is_valid_ether_addr(dev->dev_addr)) अणु
			res = -EADDRNOTAVAIL;
			जाओ err_stop;
		पूर्ण
	पूर्ण

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP_VLAN:
		/* no need to tell driver, but set carrier and chanctx */
		अगर (rtnl_dereference(sdata->bss->beacon)) अणु
			ieee80211_vअगर_vlan_copy_chanctx(sdata);
			netअगर_carrier_on(dev);
			ieee80211_set_vअगर_encap_ops(sdata);
		पूर्ण अन्यथा अणु
			netअगर_carrier_off(dev);
		पूर्ण
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (sdata->u.mntr.flags & MONITOR_FLAG_COOK_FRAMES) अणु
			local->cooked_mntrs++;
			अवरोध;
		पूर्ण

		अगर (sdata->u.mntr.flags & MONITOR_FLAG_ACTIVE) अणु
			res = drv_add_पूर्णांकerface(local, sdata);
			अगर (res)
				जाओ err_stop;
		पूर्ण अन्यथा अगर (local->monitors == 0 && local->खोलो_count == 0) अणु
			res = ieee80211_add_भव_monitor(local);
			अगर (res)
				जाओ err_stop;
		पूर्ण

		/* must be beक्रमe the call to ieee80211_configure_filter */
		local->monitors++;
		अगर (local->monitors == 1) अणु
			local->hw.conf.flags |= IEEE80211_CONF_MONITOR;
			hw_reconf_flags |= IEEE80211_CONF_CHANGE_MONITOR;
		पूर्ण

		ieee80211_adjust_monitor_flags(sdata, 1);
		ieee80211_configure_filter(local);
		ieee80211_recalc_offload(local);
		mutex_lock(&local->mtx);
		ieee80211_recalc_idle(local);
		mutex_unlock(&local->mtx);

		netअगर_carrier_on(dev);
		अवरोध;
	शेष:
		अगर (coming_up) अणु
			ieee80211_del_भव_monitor(local);
			ieee80211_set_sdata_offload_flags(sdata);

			res = drv_add_पूर्णांकerface(local, sdata);
			अगर (res)
				जाओ err_stop;

			ieee80211_set_vअगर_encap_ops(sdata);
			res = ieee80211_check_queues(sdata,
				ieee80211_vअगर_type_p2p(&sdata->vअगर));
			अगर (res)
				जाओ err_del_पूर्णांकerface;
		पूर्ण

		अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
			local->fअगर_pspoll++;
			local->fअगर_probe_req++;

			ieee80211_configure_filter(local);
		पूर्ण अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_ADHOC) अणु
			local->fअगर_probe_req++;
		पूर्ण

		अगर (sdata->vअगर.probe_req_reg)
			drv_config_अगरace_filter(local, sdata,
						FIF_PROBE_REQ,
						FIF_PROBE_REQ);

		अगर (sdata->vअगर.type != NL80211_IFTYPE_P2P_DEVICE &&
		    sdata->vअगर.type != NL80211_IFTYPE_न_अंक)
			changed |= ieee80211_reset_erp_info(sdata);
		ieee80211_bss_info_change_notअगरy(sdata, changed);

		चयन (sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_STATION:
		हाल NL80211_IFTYPE_ADHOC:
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_MESH_POINT:
		हाल NL80211_IFTYPE_OCB:
			netअगर_carrier_off(dev);
			अवरोध;
		हाल NL80211_IFTYPE_P2P_DEVICE:
		हाल NL80211_IFTYPE_न_अंक:
			अवरोध;
		शेष:
			/* not reached */
			WARN_ON(1);
		पूर्ण

		/*
		 * Set शेष queue parameters so drivers करोn't
		 * need to initialise the hardware अगर the hardware
		 * करोesn't start up with sane शेषs.
		 * Enable QoS क्रम anything but station पूर्णांकerfaces.
		 */
		ieee80211_set_wmm_शेष(sdata, true,
			sdata->vअगर.type != NL80211_IFTYPE_STATION);
	पूर्ण

	set_bit(SDATA_STATE_RUNNING, &sdata->state);

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_P2P_DEVICE:
		rcu_assign_poपूर्णांकer(local->p2p_sdata, sdata);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (sdata->u.mntr.flags & MONITOR_FLAG_COOK_FRAMES)
			अवरोध;
		list_add_tail_rcu(&sdata->u.mntr.list, &local->mon_list);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	/*
	 * set_multicast_list will be invoked by the networking core
	 * which will check whether any increments here were करोne in
	 * error and sync them करोwn to the hardware as filter flags.
	 */
	अगर (sdata->flags & IEEE80211_SDATA_ALLMULTI)
		atomic_inc(&local->अगरf_allmultis);

	अगर (coming_up)
		local->खोलो_count++;

	अगर (hw_reconf_flags)
		ieee80211_hw_config(local, hw_reconf_flags);

	ieee80211_recalc_ps(local);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR ||
	    sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN ||
	    local->ops->wake_tx_queue) अणु
		/* XXX: क्रम AP_VLAN, actually track AP queues */
		अगर (dev)
			netअगर_tx_start_all_queues(dev);
	पूर्ण अन्यथा अगर (dev) अणु
		अचिन्हित दीर्घ flags;
		पूर्णांक n_acs = IEEE80211_NUM_ACS;
		पूर्णांक ac;

		अगर (local->hw.queues < IEEE80211_NUM_ACS)
			n_acs = 1;

		spin_lock_irqsave(&local->queue_stop_reason_lock, flags);
		अगर (sdata->vअगर.cab_queue == IEEE80211_INVAL_HW_QUEUE ||
		    (local->queue_stop_reasons[sdata->vअगर.cab_queue] == 0 &&
		     skb_queue_empty(&local->pending[sdata->vअगर.cab_queue]))) अणु
			क्रम (ac = 0; ac < n_acs; ac++) अणु
				पूर्णांक ac_queue = sdata->vअगर.hw_queue[ac];

				अगर (local->queue_stop_reasons[ac_queue] == 0 &&
				    skb_queue_empty(&local->pending[ac_queue]))
					netअगर_start_subqueue(dev, ac);
			पूर्ण
		पूर्ण
		spin_unlock_irqrestore(&local->queue_stop_reason_lock, flags);
	पूर्ण

	वापस 0;
 err_del_पूर्णांकerface:
	drv_हटाओ_पूर्णांकerface(local, sdata);
 err_stop:
	अगर (!local->खोलो_count)
		drv_stop(local);
 err_del_bss:
	sdata->bss = शून्य;
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		mutex_lock(&local->mtx);
		list_del(&sdata->u.vlan.list);
		mutex_unlock(&local->mtx);
	पूर्ण
	/* might alपढ़ोy be clear but that करोesn't matter */
	clear_bit(SDATA_STATE_RUNNING, &sdata->state);
	वापस res;
पूर्ण

अटल व्योम ieee80211_अगर_मुक्त(काष्ठा net_device *dev)
अणु
	मुक्त_percpu(dev->tstats);
पूर्ण

अटल व्योम ieee80211_अगर_setup(काष्ठा net_device *dev)
अणु
	ether_setup(dev);
	dev->priv_flags &= ~IFF_TX_SKB_SHARING;
	dev->netdev_ops = &ieee80211_dataअगर_ops;
	dev->needs_मुक्त_netdev = true;
	dev->priv_deकाष्ठाor = ieee80211_अगर_मुक्त;
पूर्ण

अटल व्योम ieee80211_अगर_setup_no_queue(काष्ठा net_device *dev)
अणु
	ieee80211_अगर_setup(dev);
	dev->priv_flags |= IFF_NO_QUEUE;
पूर्ण

अटल व्योम ieee80211_अगरace_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data, work);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sk_buff *skb;
	काष्ठा sta_info *sta;

	अगर (!ieee80211_sdata_running(sdata))
		वापस;

	अगर (test_bit(SCAN_SW_SCANNING, &local->scanning))
		वापस;

	अगर (!ieee80211_can_run_worker(local))
		वापस;

	/* first process frames */
	जबतक ((skb = skb_dequeue(&sdata->skb_queue))) अणु
		काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;

		kcov_remote_start_common(skb_get_kcov_handle(skb));
		अगर (ieee80211_is_action(mgmt->frame_control) &&
		    mgmt->u.action.category == WLAN_CATEGORY_BACK) अणु
			पूर्णांक len = skb->len;

			mutex_lock(&local->sta_mtx);
			sta = sta_info_get_bss(sdata, mgmt->sa);
			अगर (sta) अणु
				चयन (mgmt->u.action.u.addba_req.action_code) अणु
				हाल WLAN_ACTION_ADDBA_REQ:
					ieee80211_process_addba_request(
							local, sta, mgmt, len);
					अवरोध;
				हाल WLAN_ACTION_ADDBA_RESP:
					ieee80211_process_addba_resp(local, sta,
								     mgmt, len);
					अवरोध;
				हाल WLAN_ACTION_DELBA:
					ieee80211_process_delba(sdata, sta,
								mgmt, len);
					अवरोध;
				शेष:
					WARN_ON(1);
					अवरोध;
				पूर्ण
			पूर्ण
			mutex_unlock(&local->sta_mtx);
		पूर्ण अन्यथा अगर (ieee80211_is_action(mgmt->frame_control) &&
			   mgmt->u.action.category == WLAN_CATEGORY_VHT) अणु
			चयन (mgmt->u.action.u.vht_group_notअगर.action_code) अणु
			हाल WLAN_VHT_ACTION_OPMODE_NOTIF: अणु
				काष्ठा ieee80211_rx_status *status;
				क्रमागत nl80211_band band;
				u8 opmode;

				status = IEEE80211_SKB_RXCB(skb);
				band = status->band;
				opmode = mgmt->u.action.u.vht_opmode_notअगर.operating_mode;

				mutex_lock(&local->sta_mtx);
				sta = sta_info_get_bss(sdata, mgmt->sa);

				अगर (sta)
					ieee80211_vht_handle_opmode(sdata, sta,
								    opmode,
								    band);

				mutex_unlock(&local->sta_mtx);
				अवरोध;
			पूर्ण
			हाल WLAN_VHT_ACTION_GROUPID_MGMT:
				ieee80211_process_mu_groups(sdata, mgmt);
				अवरोध;
			शेष:
				WARN_ON(1);
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अगर (ieee80211_is_ext(mgmt->frame_control)) अणु
			अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION)
				ieee80211_sta_rx_queued_ext(sdata, skb);
			अन्यथा
				WARN_ON(1);
		पूर्ण अन्यथा अगर (ieee80211_is_data_qos(mgmt->frame_control)) अणु
			काष्ठा ieee80211_hdr *hdr = (व्योम *)mgmt;
			/*
			 * So the frame isn't mgmt, but frame_control
			 * is at the right place anyway, of course, so
			 * the अगर statement is correct.
			 *
			 * Warn अगर we have other data frame types here,
			 * they must not get here.
			 */
			WARN_ON(hdr->frame_control &
					cpu_to_le16(IEEE80211_STYPE_शून्यFUNC));
			WARN_ON(!(hdr->seq_ctrl &
					cpu_to_le16(IEEE80211_SCTL_FRAG)));
			/*
			 * This was a fragment of a frame, received जबतक
			 * a block-ack session was active. That cannot be
			 * right, so terminate the session.
			 */
			mutex_lock(&local->sta_mtx);
			sta = sta_info_get_bss(sdata, mgmt->sa);
			अगर (sta) अणु
				u16 tid = ieee80211_get_tid(hdr);

				__ieee80211_stop_rx_ba_session(
					sta, tid, WLAN_BACK_RECIPIENT,
					WLAN_REASON_QSTA_REQUIRE_SETUP,
					true);
			पूर्ण
			mutex_unlock(&local->sta_mtx);
		पूर्ण अन्यथा चयन (sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_STATION:
			ieee80211_sta_rx_queued_mgmt(sdata, skb);
			अवरोध;
		हाल NL80211_IFTYPE_ADHOC:
			ieee80211_ibss_rx_queued_mgmt(sdata, skb);
			अवरोध;
		हाल NL80211_IFTYPE_MESH_POINT:
			अगर (!ieee80211_vअगर_is_mesh(&sdata->vअगर))
				अवरोध;
			ieee80211_mesh_rx_queued_mgmt(sdata, skb);
			अवरोध;
		शेष:
			WARN(1, "frame for unexpected interface type");
			अवरोध;
		पूर्ण

		kमुक्त_skb(skb);
		kcov_remote_stop();
	पूर्ण

	/* then other type-dependent work */
	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
		ieee80211_sta_work(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		ieee80211_ibss_work(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (!ieee80211_vअगर_is_mesh(&sdata->vअगर))
			अवरोध;
		ieee80211_mesh_work(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_OCB:
		ieee80211_ocb_work(sdata);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम ieee80211_recalc_smps_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data, recalc_smps);

	ieee80211_recalc_smps(sdata);
पूर्ण

/*
 * Helper function to initialise an पूर्णांकerface to a specअगरic type.
 */
अटल व्योम ieee80211_setup_sdata(काष्ठा ieee80211_sub_अगर_data *sdata,
				  क्रमागत nl80211_अगरtype type)
अणु
	अटल स्थिर u8 bssid_wildcard[ETH_ALEN] = अणु0xff, 0xff, 0xff,
						    0xff, 0xff, 0xffपूर्ण;

	/* clear type-dependent जोड़ */
	स_रखो(&sdata->u, 0, माप(sdata->u));

	/* and set some type-dependent values */
	sdata->vअगर.type = type;
	sdata->vअगर.p2p = false;
	sdata->wdev.अगरtype = type;

	sdata->control_port_protocol = cpu_to_be16(ETH_P_PAE);
	sdata->control_port_no_encrypt = false;
	sdata->control_port_over_nl80211 = false;
	sdata->control_port_no_preauth = false;
	sdata->encrypt_headroom = IEEE80211_ENCRYPT_HEADROOM;
	sdata->vअगर.bss_conf.idle = true;
	sdata->vअगर.bss_conf.txघातer = पूर्णांक_न्यून; /* unset */

	sdata->noack_map = 0;

	/* only monitor/p2p-device dअगरfer */
	अगर (sdata->dev) अणु
		sdata->dev->netdev_ops = &ieee80211_dataअगर_ops;
		sdata->dev->type = ARPHRD_ETHER;
	पूर्ण

	skb_queue_head_init(&sdata->skb_queue);
	INIT_WORK(&sdata->work, ieee80211_अगरace_work);
	INIT_WORK(&sdata->recalc_smps, ieee80211_recalc_smps_work);
	INIT_WORK(&sdata->csa_finalize_work, ieee80211_csa_finalize_work);
	INIT_LIST_HEAD(&sdata->asचिन्हित_chanctx_list);
	INIT_LIST_HEAD(&sdata->reserved_chanctx_list);

	चयन (type) अणु
	हाल NL80211_IFTYPE_P2P_GO:
		type = NL80211_IFTYPE_AP;
		sdata->vअगर.type = type;
		sdata->vअगर.p2p = true;
		fallthrough;
	हाल NL80211_IFTYPE_AP:
		skb_queue_head_init(&sdata->u.ap.ps.bc_buf);
		INIT_LIST_HEAD(&sdata->u.ap.vlans);
		sdata->vअगर.bss_conf.bssid = sdata->vअगर.addr;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		type = NL80211_IFTYPE_STATION;
		sdata->vअगर.type = type;
		sdata->vअगर.p2p = true;
		fallthrough;
	हाल NL80211_IFTYPE_STATION:
		sdata->vअगर.bss_conf.bssid = sdata->u.mgd.bssid;
		ieee80211_sta_setup_sdata(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_OCB:
		sdata->vअगर.bss_conf.bssid = bssid_wildcard;
		ieee80211_ocb_setup_sdata(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		sdata->vअगर.bss_conf.bssid = sdata->u.ibss.bssid;
		ieee80211_ibss_setup_sdata(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
			ieee80211_mesh_init_sdata(sdata);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		sdata->dev->type = ARPHRD_IEEE80211_RADIOTAP;
		sdata->dev->netdev_ops = &ieee80211_monitorअगर_ops;
		sdata->u.mntr.flags = MONITOR_FLAG_CONTROL |
				      MONITOR_FLAG_OTHER_BSS;
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
		idr_init(&sdata->u.nan.function_inst_ids);
		spin_lock_init(&sdata->u.nan.func_lock);
		sdata->vअगर.bss_conf.bssid = sdata->vअगर.addr;
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		sdata->vअगर.bss_conf.bssid = sdata->vअगर.addr;
		अवरोध;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_WDS:
	हाल NUM_NL80211_IFTYPES:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	ieee80211_debugfs_add_netdev(sdata);
पूर्ण

अटल पूर्णांक ieee80211_runसमय_change_अगरtype(काष्ठा ieee80211_sub_अगर_data *sdata,
					   क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ret, err;
	क्रमागत nl80211_अगरtype पूर्णांकernal_type = type;
	bool p2p = false;

	ASSERT_RTNL();

	अगर (!local->ops->change_पूर्णांकerface)
		वापस -EBUSY;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP:
		अगर (!list_empty(&sdata->u.ap.vlans))
			वापस -EBUSY;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_OCB:
		/*
		 * Could maybe also all others here?
		 * Just not sure how that पूर्णांकeracts
		 * with the RX/config path e.g. क्रम
		 * mesh.
		 */
		अवरोध;
	शेष:
		वापस -EBUSY;
	पूर्ण

	चयन (type) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_OCB:
		/*
		 * Could probably support everything
		 * but here.
		 */
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
		p2p = true;
		पूर्णांकernal_type = NL80211_IFTYPE_STATION;
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		p2p = true;
		पूर्णांकernal_type = NL80211_IFTYPE_AP;
		अवरोध;
	शेष:
		वापस -EBUSY;
	पूर्ण

	ret = ieee80211_check_concurrent_अगरace(sdata, पूर्णांकernal_type);
	अगर (ret)
		वापस ret;

	ieee80211_stop_vअगर_queues(local, sdata,
				  IEEE80211_QUEUE_STOP_REASON_IFTYPE_CHANGE);
	synchronize_net();

	ieee80211_करो_stop(sdata, false);

	ieee80211_tearकरोwn_sdata(sdata);

	ieee80211_set_sdata_offload_flags(sdata);
	ret = drv_change_पूर्णांकerface(local, sdata, पूर्णांकernal_type, p2p);
	अगर (ret)
		type = ieee80211_vअगर_type_p2p(&sdata->vअगर);

	/*
	 * Ignore वापस value here, there's not much we can करो since
	 * the driver changed the पूर्णांकerface type पूर्णांकernally alपढ़ोy.
	 * The warnings will hopefully make driver authors fix it :-)
	 */
	ieee80211_check_queues(sdata, type);

	ieee80211_setup_sdata(sdata, type);
	ieee80211_set_vअगर_encap_ops(sdata);

	err = ieee80211_करो_खोलो(&sdata->wdev, false);
	WARN(err, "type change: do_open returned %d", err);

	ieee80211_wake_vअगर_queues(local, sdata,
				  IEEE80211_QUEUE_STOP_REASON_IFTYPE_CHANGE);
	वापस ret;
पूर्ण

पूर्णांक ieee80211_अगर_change_type(काष्ठा ieee80211_sub_अगर_data *sdata,
			     क्रमागत nl80211_अगरtype type)
अणु
	पूर्णांक ret;

	ASSERT_RTNL();

	अगर (type == ieee80211_vअगर_type_p2p(&sdata->vअगर))
		वापस 0;

	अगर (ieee80211_sdata_running(sdata)) अणु
		ret = ieee80211_runसमय_change_अगरtype(sdata, type);
		अगर (ret)
			वापस ret;
	पूर्ण अन्यथा अणु
		/* Purge and reset type-dependent state. */
		ieee80211_tearकरोwn_sdata(sdata);
		ieee80211_setup_sdata(sdata, type);
	पूर्ण

	/* reset some values that shouldn't be kept across type changes */
	अगर (type == NL80211_IFTYPE_STATION)
		sdata->u.mgd.use_4addr = false;

	वापस 0;
पूर्ण

अटल व्योम ieee80211_assign_perm_addr(काष्ठा ieee80211_local *local,
				       u8 *perm_addr, क्रमागत nl80211_अगरtype type)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	u64 mask, start, addr, val, inc;
	u8 *m;
	u8 पंचांगp_addr[ETH_ALEN];
	पूर्णांक i;

	/* शेष ... something at least */
	स_नकल(perm_addr, local->hw.wiphy->perm_addr, ETH_ALEN);

	अगर (is_zero_ether_addr(local->hw.wiphy->addr_mask) &&
	    local->hw.wiphy->n_addresses <= 1)
		वापस;

	mutex_lock(&local->अगरlist_mtx);

	चयन (type) अणु
	हाल NL80211_IFTYPE_MONITOR:
		/* करोesn't matter */
		अवरोध;
	हाल NL80211_IFTYPE_AP_VLAN:
		/* match up with an AP पूर्णांकerface */
		list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
			अगर (sdata->vअगर.type != NL80211_IFTYPE_AP)
				जारी;
			स_नकल(perm_addr, sdata->vअगर.addr, ETH_ALEN);
			अवरोध;
		पूर्ण
		/* keep शेष अगर no AP पूर्णांकerface present */
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (ieee80211_hw_check(&local->hw, P2P_DEV_ADDR_FOR_INTF)) अणु
			list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
				अगर (sdata->vअगर.type != NL80211_IFTYPE_P2P_DEVICE)
					जारी;
				अगर (!ieee80211_sdata_running(sdata))
					जारी;
				स_नकल(perm_addr, sdata->vअगर.addr, ETH_ALEN);
				जाओ out_unlock;
			पूर्ण
		पूर्ण
		fallthrough;
	शेष:
		/* assign a new address अगर possible -- try n_addresses first */
		क्रम (i = 0; i < local->hw.wiphy->n_addresses; i++) अणु
			bool used = false;

			list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
				अगर (ether_addr_equal(local->hw.wiphy->addresses[i].addr,
						     sdata->vअगर.addr)) अणु
					used = true;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!used) अणु
				स_नकल(perm_addr,
				       local->hw.wiphy->addresses[i].addr,
				       ETH_ALEN);
				अवरोध;
			पूर्ण
		पूर्ण

		/* try mask अगर available */
		अगर (is_zero_ether_addr(local->hw.wiphy->addr_mask))
			अवरोध;

		m = local->hw.wiphy->addr_mask;
		mask =	((u64)m[0] << 5*8) | ((u64)m[1] << 4*8) |
			((u64)m[2] << 3*8) | ((u64)m[3] << 2*8) |
			((u64)m[4] << 1*8) | ((u64)m[5] << 0*8);

		अगर (__ffs64(mask) + hweight64(mask) != fls64(mask)) अणु
			/* not a contiguous mask ... not handled now! */
			pr_info("not contiguous\n");
			अवरोध;
		पूर्ण

		/*
		 * Pick address of existing पूर्णांकerface in हाल user changed
		 * MAC address manually, शेष to perm_addr.
		 */
		m = local->hw.wiphy->perm_addr;
		list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
			अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR)
				जारी;
			m = sdata->vअगर.addr;
			अवरोध;
		पूर्ण
		start = ((u64)m[0] << 5*8) | ((u64)m[1] << 4*8) |
			((u64)m[2] << 3*8) | ((u64)m[3] << 2*8) |
			((u64)m[4] << 1*8) | ((u64)m[5] << 0*8);

		inc = 1ULL<<__ffs64(mask);
		val = (start & mask);
		addr = (start & ~mask) | (val & mask);
		करो अणु
			bool used = false;

			पंचांगp_addr[5] = addr >> 0*8;
			पंचांगp_addr[4] = addr >> 1*8;
			पंचांगp_addr[3] = addr >> 2*8;
			पंचांगp_addr[2] = addr >> 3*8;
			पंचांगp_addr[1] = addr >> 4*8;
			पंचांगp_addr[0] = addr >> 5*8;

			val += inc;

			list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
				अगर (ether_addr_equal(पंचांगp_addr, sdata->vअगर.addr)) अणु
					used = true;
					अवरोध;
				पूर्ण
			पूर्ण

			अगर (!used) अणु
				स_नकल(perm_addr, पंचांगp_addr, ETH_ALEN);
				अवरोध;
			पूर्ण
			addr = (start & ~mask) | (val & mask);
		पूर्ण जबतक (addr != start);

		अवरोध;
	पूर्ण

 out_unlock:
	mutex_unlock(&local->अगरlist_mtx);
पूर्ण

पूर्णांक ieee80211_अगर_add(काष्ठा ieee80211_local *local, स्थिर अक्षर *name,
		     अचिन्हित अक्षर name_assign_type,
		     काष्ठा wireless_dev **new_wdev, क्रमागत nl80211_अगरtype type,
		     काष्ठा vअगर_params *params)
अणु
	काष्ठा net_device *ndev = शून्य;
	काष्ठा ieee80211_sub_अगर_data *sdata = शून्य;
	काष्ठा txq_info *txqi;
	व्योम (*अगर_setup)(काष्ठा net_device *dev);
	पूर्णांक ret, i;
	पूर्णांक txqs = 1;

	ASSERT_RTNL();

	अगर (type == NL80211_IFTYPE_P2P_DEVICE || type == NL80211_IFTYPE_न_अंक) अणु
		काष्ठा wireless_dev *wdev;

		sdata = kzalloc(माप(*sdata) + local->hw.vअगर_data_size,
				GFP_KERNEL);
		अगर (!sdata)
			वापस -ENOMEM;
		wdev = &sdata->wdev;

		sdata->dev = शून्य;
		strlcpy(sdata->name, name, IFNAMSIZ);
		ieee80211_assign_perm_addr(local, wdev->address, type);
		स_नकल(sdata->vअगर.addr, wdev->address, ETH_ALEN);
	पूर्ण अन्यथा अणु
		पूर्णांक size = ALIGN(माप(*sdata) + local->hw.vअगर_data_size,
				 माप(व्योम *));
		पूर्णांक txq_size = 0;

		अगर (local->ops->wake_tx_queue &&
		    type != NL80211_IFTYPE_AP_VLAN &&
		    (type != NL80211_IFTYPE_MONITOR ||
		     (params->flags & MONITOR_FLAG_ACTIVE)))
			txq_size += माप(काष्ठा txq_info) +
				    local->hw.txq_data_size;

		अगर (local->ops->wake_tx_queue) अणु
			अगर_setup = ieee80211_अगर_setup_no_queue;
		पूर्ण अन्यथा अणु
			अगर_setup = ieee80211_अगर_setup;
			अगर (local->hw.queues >= IEEE80211_NUM_ACS)
				txqs = IEEE80211_NUM_ACS;
		पूर्ण

		ndev = alloc_netdev_mqs(size + txq_size,
					name, name_assign_type,
					अगर_setup, txqs, 1);
		अगर (!ndev)
			वापस -ENOMEM;

		अगर (!local->ops->wake_tx_queue && local->hw.wiphy->tx_queue_len)
			ndev->tx_queue_len = local->hw.wiphy->tx_queue_len;

		dev_net_set(ndev, wiphy_net(local->hw.wiphy));

		ndev->tstats = netdev_alloc_pcpu_stats(काष्ठा pcpu_sw_netstats);
		अगर (!ndev->tstats) अणु
			मुक्त_netdev(ndev);
			वापस -ENOMEM;
		पूर्ण

		ndev->needed_headroom = local->tx_headroom +
					4*6 /* four MAC addresses */
					+ 2 + 2 + 2 + 2 /* ctl, dur, seq, qos */
					+ 6 /* mesh */
					+ 8 /* rfc1042/bridge tunnel */
					- ETH_HLEN /* ethernet hard_header_len */
					+ IEEE80211_ENCRYPT_HEADROOM;
		ndev->needed_tailroom = IEEE80211_ENCRYPT_TAILROOM;

		ret = dev_alloc_name(ndev, ndev->name);
		अगर (ret < 0) अणु
			ieee80211_अगर_मुक्त(ndev);
			मुक्त_netdev(ndev);
			वापस ret;
		पूर्ण

		ieee80211_assign_perm_addr(local, ndev->perm_addr, type);
		अगर (is_valid_ether_addr(params->macaddr))
			स_नकल(ndev->dev_addr, params->macaddr, ETH_ALEN);
		अन्यथा
			स_नकल(ndev->dev_addr, ndev->perm_addr, ETH_ALEN);
		SET_NETDEV_DEV(ndev, wiphy_dev(local->hw.wiphy));

		/* करोn't use IEEE80211_DEV_TO_SUB_IF -- it checks too much */
		sdata = netdev_priv(ndev);
		ndev->ieee80211_ptr = &sdata->wdev;
		स_नकल(sdata->vअगर.addr, ndev->dev_addr, ETH_ALEN);
		स_नकल(sdata->name, ndev->name, IFNAMSIZ);

		अगर (txq_size) अणु
			txqi = netdev_priv(ndev) + size;
			ieee80211_txq_init(sdata, शून्य, txqi, 0);
		पूर्ण

		sdata->dev = ndev;
	पूर्ण

	/* initialise type-independent data */
	sdata->wdev.wiphy = local->hw.wiphy;
	sdata->local = local;

	ieee80211_init_frag_cache(&sdata->frags);

	INIT_LIST_HEAD(&sdata->key_list);

	INIT_DELAYED_WORK(&sdata->dfs_cac_समयr_work,
			  ieee80211_dfs_cac_समयr_work);
	INIT_DELAYED_WORK(&sdata->dec_tailroom_needed_wk,
			  ieee80211_delayed_tailroom_dec);

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		काष्ठा ieee80211_supported_band *sband;
		sband = local->hw.wiphy->bands[i];
		sdata->rc_rateidx_mask[i] =
			sband ? (1 << sband->n_bitrates) - 1 : 0;
		अगर (sband) अणु
			__le16 cap;
			u16 *vht_rate_mask;

			स_नकल(sdata->rc_rateidx_mcs_mask[i],
			       sband->ht_cap.mcs.rx_mask,
			       माप(sdata->rc_rateidx_mcs_mask[i]));

			cap = sband->vht_cap.vht_mcs.rx_mcs_map;
			vht_rate_mask = sdata->rc_rateidx_vht_mcs_mask[i];
			ieee80211_get_vht_mask_from_cap(cap, vht_rate_mask);
		पूर्ण अन्यथा अणु
			स_रखो(sdata->rc_rateidx_mcs_mask[i], 0,
			       माप(sdata->rc_rateidx_mcs_mask[i]));
			स_रखो(sdata->rc_rateidx_vht_mcs_mask[i], 0,
			       माप(sdata->rc_rateidx_vht_mcs_mask[i]));
		पूर्ण
	पूर्ण

	ieee80211_set_शेष_queues(sdata);

	sdata->ap_घातer_level = IEEE80211_UNSET_POWER_LEVEL;
	sdata->user_घातer_level = local->user_घातer_level;

	sdata->encrypt_headroom = IEEE80211_ENCRYPT_HEADROOM;

	/* setup type-dependent data */
	ieee80211_setup_sdata(sdata, type);

	अगर (ndev) अणु
		ndev->ieee80211_ptr->use_4addr = params->use_4addr;
		अगर (type == NL80211_IFTYPE_STATION)
			sdata->u.mgd.use_4addr = params->use_4addr;

		ndev->features |= local->hw.netdev_features;
		ndev->hw_features |= ndev->features &
					MAC80211_SUPPORTED_FEATURES_TX;

		netdev_set_शेष_ethtool_ops(ndev, &ieee80211_ethtool_ops);

		/* MTU range: 256 - 2304 */
		ndev->min_mtu = 256;
		ndev->max_mtu = local->hw.max_mtu;

		ret = cfg80211_रेजिस्टर_netdevice(ndev);
		अगर (ret) अणु
			मुक्त_netdev(ndev);
			वापस ret;
		पूर्ण
	पूर्ण

	mutex_lock(&local->अगरlist_mtx);
	list_add_tail_rcu(&sdata->list, &local->पूर्णांकerfaces);
	mutex_unlock(&local->अगरlist_mtx);

	अगर (new_wdev)
		*new_wdev = &sdata->wdev;

	वापस 0;
पूर्ण

व्योम ieee80211_अगर_हटाओ(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	ASSERT_RTNL();

	mutex_lock(&sdata->local->अगरlist_mtx);
	list_del_rcu(&sdata->list);
	mutex_unlock(&sdata->local->अगरlist_mtx);

	अगर (sdata->vअगर.txq)
		ieee80211_txq_purge(sdata->local, to_txq_info(sdata->vअगर.txq));

	synchronize_rcu();

	cfg80211_unरेजिस्टर_wdev(&sdata->wdev);

	अगर (!sdata->dev) अणु
		ieee80211_tearकरोwn_sdata(sdata);
		kमुक्त(sdata);
	पूर्ण
पूर्ण

व्योम ieee80211_sdata_stop(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (WARN_ON_ONCE(!test_bit(SDATA_STATE_RUNNING, &sdata->state)))
		वापस;
	ieee80211_करो_stop(sdata, true);
पूर्ण

व्योम ieee80211_हटाओ_पूर्णांकerfaces(काष्ठा ieee80211_local *local)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata, *पंचांगp;
	LIST_HEAD(unreg_list);
	LIST_HEAD(wdev_list);

	ASSERT_RTNL();

	/* Beक्रमe destroying the पूर्णांकerfaces, make sure they're all stopped so
	 * that the hardware is stopped. Otherwise, the driver might still be
	 * iterating the पूर्णांकerfaces during the shutकरोwn, e.g. from a worker
	 * or from RX processing or similar, and अगर it करोes so (using atomic
	 * iteration) जबतक we're manipulating the list, the iteration will
	 * crash.
	 *
	 * After this, the hardware should be stopped and the driver should
	 * have stopped all of its activities, so that we can करो RCU-unaware
	 * manipulations of the पूर्णांकerface list below.
	 */
	cfg80211_shutकरोwn_all_पूर्णांकerfaces(local->hw.wiphy);

	WARN(local->खोलो_count, "%s: open count remains %d\n",
	     wiphy_name(local->hw.wiphy), local->खोलो_count);

	ieee80211_txq_tearकरोwn_flows(local);

	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry_safe(sdata, पंचांगp, &local->पूर्णांकerfaces, list) अणु
		list_del(&sdata->list);

		अगर (sdata->dev)
			unरेजिस्टर_netdevice_queue(sdata->dev, &unreg_list);
		अन्यथा
			list_add(&sdata->list, &wdev_list);
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);

	unरेजिस्टर_netdevice_many(&unreg_list);

	wiphy_lock(local->hw.wiphy);
	list_क्रम_each_entry_safe(sdata, पंचांगp, &wdev_list, list) अणु
		list_del(&sdata->list);
		cfg80211_unरेजिस्टर_wdev(&sdata->wdev);
		kमुक्त(sdata);
	पूर्ण
	wiphy_unlock(local->hw.wiphy);
पूर्ण

अटल पूर्णांक netdev_notअगरy(काष्ठा notअगरier_block *nb,
			 अचिन्हित दीर्घ state, व्योम *ptr)
अणु
	काष्ठा net_device *dev = netdev_notअगरier_info_to_dev(ptr);
	काष्ठा ieee80211_sub_अगर_data *sdata;

	अगर (state != NETDEV_CHANGENAME)
		वापस NOTIFY_DONE;

	अगर (!dev->ieee80211_ptr || !dev->ieee80211_ptr->wiphy)
		वापस NOTIFY_DONE;

	अगर (dev->ieee80211_ptr->wiphy->privid != mac80211_wiphy_privid)
		वापस NOTIFY_DONE;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	स_नकल(sdata->name, dev->name, IFNAMSIZ);
	ieee80211_debugfs_नाम_netdev(sdata);

	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block mac80211_netdev_notअगरier = अणु
	.notअगरier_call = netdev_notअगरy,
पूर्ण;

पूर्णांक ieee80211_अगरace_init(व्योम)
अणु
	वापस रेजिस्टर_netdevice_notअगरier(&mac80211_netdev_notअगरier);
पूर्ण

व्योम ieee80211_अगरace_निकास(व्योम)
अणु
	unरेजिस्टर_netdevice_notअगरier(&mac80211_netdev_notअगरier);
पूर्ण

व्योम ieee80211_vअगर_inc_num_mcast(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		atomic_inc(&sdata->u.ap.num_mcast_sta);
	अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		atomic_inc(&sdata->u.vlan.num_mcast_sta);
पूर्ण

व्योम ieee80211_vअगर_dec_num_mcast(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP)
		atomic_dec(&sdata->u.ap.num_mcast_sta);
	अन्यथा अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		atomic_dec(&sdata->u.vlan.num_mcast_sta);
पूर्ण
