<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Portions
 * Copyright (C) 2020-2021 Intel Corporation
 */
#समावेश <net/mac80211.h>
#समावेश <net/rtnetlink.h>

#समावेश "ieee80211_i.h"
#समावेश "mesh.h"
#समावेश "driver-ops.h"
#समावेश "led.h"

अटल व्योम ieee80211_sched_scan_cancel(काष्ठा ieee80211_local *local)
अणु
	अगर (ieee80211_request_sched_scan_stop(local))
		वापस;
	cfg80211_sched_scan_stopped_locked(local->hw.wiphy, 0);
पूर्ण

पूर्णांक __ieee80211_suspend(काष्ठा ieee80211_hw *hw, काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info *sta;

	अगर (!local->खोलो_count)
		जाओ suspend;

	ieee80211_scan_cancel(local);

	ieee80211_dfs_cac_cancel(local);

	ieee80211_roc_purge(local, शून्य);

	ieee80211_del_भव_monitor(local);

	अगर (ieee80211_hw_check(hw, AMPDU_AGGREGATION) &&
	    !(wowlan && wowlan->any)) अणु
		mutex_lock(&local->sta_mtx);
		list_क्रम_each_entry(sta, &local->sta_list, list) अणु
			set_sta_flag(sta, WLAN_STA_BLOCK_BA);
			ieee80211_sta_tear_करोwn_BA_sessions(
					sta, AGG_STOP_LOCAL_REQUEST);
		पूर्ण
		mutex_unlock(&local->sta_mtx);
	पूर्ण

	/* keep sched_scan only in हाल of 'any' trigger */
	अगर (!(wowlan && wowlan->any))
		ieee80211_sched_scan_cancel(local);

	ieee80211_stop_queues_by_reason(hw,
					IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_SUSPEND,
					false);

	/* flush out all packets */
	synchronize_net();

	ieee80211_flush_queues(local, शून्य, true);

	local->quiescing = true;
	/* make quiescing visible to समयrs everywhere */
	mb();

	flush_workqueue(local->workqueue);

	/* Don't try to run समयrs जबतक suspended. */
	del_समयr_sync(&local->sta_cleanup);

	 /*
	 * Note that this particular समयr करोesn't need to be
	 * restarted at resume.
	 */
	cancel_work_sync(&local->dynamic_ps_enable_work);
	del_समयr_sync(&local->dynamic_ps_समयr);

	local->wowlan = wowlan;
	अगर (local->wowlan) अणु
		पूर्णांक err;

		/* Drivers करोn't expect to suspend जबतक some operations like
		 * authenticating or associating are in progress. It करोesn't
		 * make sense anyway to accept that, since the authentication
		 * or association would never finish since the driver can't करो
		 * that on its own.
		 * Thus, clean up in-progress auth/assoc first.
		 */
		list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
			अगर (!ieee80211_sdata_running(sdata))
				जारी;
			अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
				जारी;
			ieee80211_mgd_quiesce(sdata);
			/* If suspended during TX in progress, and wowlan
			 * is enabled (connection will be active) there
			 * can be a race where the driver is put out
			 * of घातer-save due to TX and during suspend
			 * dynamic_ps_समयr is cancelled and TX packet
			 * is flushed, leaving the driver in ACTIVE even
			 * after resuming until dynamic_ps_समयr माला_दो
			 * driver back in DOZE.
			 */
			अगर (sdata->u.mgd.associated &&
			    sdata->u.mgd.घातersave &&
			     !(local->hw.conf.flags & IEEE80211_CONF_PS)) अणु
				local->hw.conf.flags |= IEEE80211_CONF_PS;
				ieee80211_hw_config(local,
						    IEEE80211_CONF_CHANGE_PS);
			पूर्ण
		पूर्ण

		err = drv_suspend(local, wowlan);
		अगर (err < 0) अणु
			local->quiescing = false;
			local->wowlan = false;
			अगर (ieee80211_hw_check(hw, AMPDU_AGGREGATION)) अणु
				mutex_lock(&local->sta_mtx);
				list_क्रम_each_entry(sta,
						    &local->sta_list, list) अणु
					clear_sta_flag(sta, WLAN_STA_BLOCK_BA);
				पूर्ण
				mutex_unlock(&local->sta_mtx);
			पूर्ण
			ieee80211_wake_queues_by_reason(hw,
					IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_SUSPEND,
					false);
			वापस err;
		पूर्ण अन्यथा अगर (err > 0) अणु
			WARN_ON(err != 1);
			/* cfg80211 will call back पूर्णांकo mac80211 to disconnect
			 * all पूर्णांकerfaces, allow that to proceed properly
			 */
			ieee80211_wake_queues_by_reason(hw,
					IEEE80211_MAX_QUEUE_MAP,
					IEEE80211_QUEUE_STOP_REASON_SUSPEND,
					false);
			वापस err;
		पूर्ण अन्यथा अणु
			जाओ suspend;
		पूर्ण
	पूर्ण

	/* हटाओ all पूर्णांकerfaces that were created in the driver */
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (!ieee80211_sdata_running(sdata))
			जारी;
		चयन (sdata->vअगर.type) अणु
		हाल NL80211_IFTYPE_AP_VLAN:
		हाल NL80211_IFTYPE_MONITOR:
			जारी;
		हाल NL80211_IFTYPE_STATION:
			ieee80211_mgd_quiesce(sdata);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण

		flush_delayed_work(&sdata->dec_tailroom_needed_wk);
		drv_हटाओ_पूर्णांकerface(local, sdata);
	पूर्ण

	/*
	 * We disconnected on all पूर्णांकerfaces beक्रमe suspend, all channel
	 * contexts should be released.
	 */
	WARN_ON(!list_empty(&local->chanctx_list));

	/* stop hardware - this must stop RX */
	ieee80211_stop_device(local);

 suspend:
	local->suspended = true;
	/* need suspended to be visible beक्रमe quiescing is false */
	barrier();
	local->quiescing = false;

	वापस 0;
पूर्ण

/*
 * __ieee80211_resume() is a अटल अंतरभूत which just calls
 * ieee80211_reconfig(), which is also needed क्रम hardware
 * hang/firmware failure/etc. recovery.
 */

व्योम ieee80211_report_wowlan_wakeup(काष्ठा ieee80211_vअगर *vअगर,
				    काष्ठा cfg80211_wowlan_wakeup *wakeup,
				    gfp_t gfp)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	cfg80211_report_wowlan_wakeup(&sdata->wdev, wakeup, gfp);
पूर्ण
EXPORT_SYMBOL(ieee80211_report_wowlan_wakeup);
