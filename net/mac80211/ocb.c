<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * OCB mode implementation
 *
 * Copyright: (c) 2014 Czech Technical University in Prague
 *            (c) 2014 Volkswagen Group Research
 * Author:    Rostislav Lisovy <rostislav.lisovy@fel.cvut.cz>
 * Funded by: Volkswagen Group Research
 */

#समावेश <linux/delay.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/skbuff.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/mac80211.h>
#समावेश <यंत्र/unaligned.h>

#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"

#घोषणा IEEE80211_OCB_HOUSEKEEPING_INTERVAL		(60 * HZ)
#घोषणा IEEE80211_OCB_PEER_INACTIVITY_LIMIT		(240 * HZ)
#घोषणा IEEE80211_OCB_MAX_STA_ENTRIES			128

/**
 * क्रमागत ocb_deferred_task_flags - mac80211 OCB deferred tasks
 * @OCB_WORK_HOUSEKEEPING: run the periodic OCB housekeeping tasks
 *
 * These flags are used in @wrkq_flags field of &काष्ठा ieee80211_अगर_ocb
 */
क्रमागत ocb_deferred_task_flags अणु
	OCB_WORK_HOUSEKEEPING,
पूर्ण;

व्योम ieee80211_ocb_rx_no_sta(काष्ठा ieee80211_sub_अगर_data *sdata,
			     स्थिर u8 *bssid, स्थिर u8 *addr,
			     u32 supp_rates)
अणु
	काष्ठा ieee80211_अगर_ocb *अगरocb = &sdata->u.ocb;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	काष्ठा ieee80211_supported_band *sband;
	क्रमागत nl80211_bss_scan_width scan_width;
	काष्ठा sta_info *sta;
	पूर्णांक band;

	/* XXX: Consider removing the least recently used entry and
	 *      allow new one to be added.
	 */
	अगर (local->num_sta >= IEEE80211_OCB_MAX_STA_ENTRIES) अणु
		net_info_ratelimited("%s: No room for a new OCB STA entry %pM\n",
				     sdata->name, addr);
		वापस;
	पूर्ण

	ocb_dbg(sdata, "Adding new OCB station %pM\n", addr);

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON_ONCE(!chanctx_conf)) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण
	band = chanctx_conf->def.chan->band;
	scan_width = cfg80211_chandef_to_scan_width(&chanctx_conf->def);
	rcu_पढ़ो_unlock();

	sta = sta_info_alloc(sdata, addr, GFP_ATOMIC);
	अगर (!sta)
		वापस;

	/* Add only mandatory rates क्रम now */
	sband = local->hw.wiphy->bands[band];
	sta->sta.supp_rates[band] =
		ieee80211_mandatory_rates(sband, scan_width);

	spin_lock(&अगरocb->incomplete_lock);
	list_add(&sta->list, &अगरocb->incomplete_stations);
	spin_unlock(&अगरocb->incomplete_lock);
	ieee80211_queue_work(&local->hw, &sdata->work);
पूर्ण

अटल काष्ठा sta_info *ieee80211_ocb_finish_sta(काष्ठा sta_info *sta)
	__acquires(RCU)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u8 addr[ETH_ALEN];

	स_नकल(addr, sta->sta.addr, ETH_ALEN);

	ocb_dbg(sdata, "Adding new IBSS station %pM (dev=%s)\n",
		addr, sdata->name);

	sta_info_move_state(sta, IEEE80211_STA_AUTH);
	sta_info_move_state(sta, IEEE80211_STA_ASSOC);
	sta_info_move_state(sta, IEEE80211_STA_AUTHORIZED);

	rate_control_rate_init(sta);

	/* If it fails, maybe we raced another insertion? */
	अगर (sta_info_insert_rcu(sta))
		वापस sta_info_get(sdata, addr);
	वापस sta;
पूर्ण

अटल व्योम ieee80211_ocb_housekeeping(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ocb *अगरocb = &sdata->u.ocb;

	ocb_dbg(sdata, "Running ocb housekeeping\n");

	ieee80211_sta_expire(sdata, IEEE80211_OCB_PEER_INACTIVITY_LIMIT);

	mod_समयr(&अगरocb->housekeeping_समयr,
		  round_jअगरfies(jअगरfies + IEEE80211_OCB_HOUSEKEEPING_INTERVAL));
पूर्ण

व्योम ieee80211_ocb_work(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ocb *अगरocb = &sdata->u.ocb;
	काष्ठा sta_info *sta;

	अगर (अगरocb->joined != true)
		वापस;

	sdata_lock(sdata);

	spin_lock_bh(&अगरocb->incomplete_lock);
	जबतक (!list_empty(&अगरocb->incomplete_stations)) अणु
		sta = list_first_entry(&अगरocb->incomplete_stations,
				       काष्ठा sta_info, list);
		list_del(&sta->list);
		spin_unlock_bh(&अगरocb->incomplete_lock);

		ieee80211_ocb_finish_sta(sta);
		rcu_पढ़ो_unlock();
		spin_lock_bh(&अगरocb->incomplete_lock);
	पूर्ण
	spin_unlock_bh(&अगरocb->incomplete_lock);

	अगर (test_and_clear_bit(OCB_WORK_HOUSEKEEPING, &अगरocb->wrkq_flags))
		ieee80211_ocb_housekeeping(sdata);

	sdata_unlock(sdata);
पूर्ण

अटल व्योम ieee80211_ocb_housekeeping_समयr(काष्ठा समयr_list *t)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		from_समयr(sdata, t, u.ocb.housekeeping_समयr);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_ocb *अगरocb = &sdata->u.ocb;

	set_bit(OCB_WORK_HOUSEKEEPING, &अगरocb->wrkq_flags);

	ieee80211_queue_work(&local->hw, &sdata->work);
पूर्ण

व्योम ieee80211_ocb_setup_sdata(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ocb *अगरocb = &sdata->u.ocb;

	समयr_setup(&अगरocb->housekeeping_समयr,
		    ieee80211_ocb_housekeeping_समयr, 0);
	INIT_LIST_HEAD(&अगरocb->incomplete_stations);
	spin_lock_init(&अगरocb->incomplete_lock);
पूर्ण

पूर्णांक ieee80211_ocb_join(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा ocb_setup *setup)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_अगर_ocb *अगरocb = &sdata->u.ocb;
	u32 changed = BSS_CHANGED_OCB | BSS_CHANGED_BSSID;
	पूर्णांक err;

	अगर (अगरocb->joined == true)
		वापस -EINVAL;

	sdata->flags |= IEEE80211_SDATA_OPERATING_GMODE;
	sdata->smps_mode = IEEE80211_SMPS_OFF;
	sdata->needed_rx_chains = sdata->local->rx_chains;

	mutex_lock(&sdata->local->mtx);
	err = ieee80211_vअगर_use_channel(sdata, &setup->chandef,
					IEEE80211_CHANCTX_SHARED);
	mutex_unlock(&sdata->local->mtx);
	अगर (err)
		वापस err;

	ieee80211_bss_info_change_notअगरy(sdata, changed);

	अगरocb->joined = true;

	set_bit(OCB_WORK_HOUSEKEEPING, &अगरocb->wrkq_flags);
	ieee80211_queue_work(&local->hw, &sdata->work);

	netअगर_carrier_on(sdata->dev);
	वापस 0;
पूर्ण

पूर्णांक ieee80211_ocb_leave(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_अगर_ocb *अगरocb = &sdata->u.ocb;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;

	अगरocb->joined = false;
	sta_info_flush(sdata);

	spin_lock_bh(&अगरocb->incomplete_lock);
	जबतक (!list_empty(&अगरocb->incomplete_stations)) अणु
		sta = list_first_entry(&अगरocb->incomplete_stations,
				       काष्ठा sta_info, list);
		list_del(&sta->list);
		spin_unlock_bh(&अगरocb->incomplete_lock);

		sta_info_मुक्त(local, sta);
		spin_lock_bh(&अगरocb->incomplete_lock);
	पूर्ण
	spin_unlock_bh(&अगरocb->incomplete_lock);

	netअगर_carrier_off(sdata->dev);
	clear_bit(SDATA_STATE_OFFCHANNEL, &sdata->state);
	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_OCB);

	mutex_lock(&sdata->local->mtx);
	ieee80211_vअगर_release_channel(sdata);
	mutex_unlock(&sdata->local->mtx);

	skb_queue_purge(&sdata->skb_queue);

	del_समयr_sync(&sdata->u.ocb.housekeeping_समयr);
	/* If the समयr fired जबतक we रुकोed क्रम it, it will have
	 * requeued the work. Now the work will be running again
	 * but will not rearm the समयr again because it checks
	 * whether we are connected to the network or not -- at this
	 * poपूर्णांक we shouldn't be anymore.
	 */

	वापस 0;
पूर्ण
