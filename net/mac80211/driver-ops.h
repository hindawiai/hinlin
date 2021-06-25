<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
* Portions of this file
* Copyright(c) 2016 Intel Deutschland GmbH
* Copyright (C) 2018 - 2019 Intel Corporation
*/

#अगर_अघोषित __MAC80211_DRIVER_OPS
#घोषणा __MAC80211_DRIVER_OPS

#समावेश <net/mac80211.h>
#समावेश "ieee80211_i.h"
#समावेश "trace.h"

#घोषणा check_sdata_in_driver(sdata)	(अणु					\
	!WARN_ONCE(!(sdata->flags & IEEE80211_SDATA_IN_DRIVER),			\
		   "%s: Failed check-sdata-in-driver check, flags: 0x%x\n",	\
		   sdata->dev ? sdata->dev->name : sdata->name, sdata->flags);	\
पूर्ण)

अटल अंतरभूत काष्ठा ieee80211_sub_अगर_data *
get_bss_sdata(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN)
		sdata = container_of(sdata->bss, काष्ठा ieee80211_sub_अगर_data,
				     u.ap);

	वापस sdata;
पूर्ण

अटल अंतरभूत व्योम drv_tx(काष्ठा ieee80211_local *local,
			  काष्ठा ieee80211_tx_control *control,
			  काष्ठा sk_buff *skb)
अणु
	local->ops->tx(&local->hw, control, skb);
पूर्ण

अटल अंतरभूत व्योम drv_sync_rx_queues(काष्ठा ieee80211_local *local,
				      काष्ठा sta_info *sta)
अणु
	अगर (local->ops->sync_rx_queues) अणु
		trace_drv_sync_rx_queues(local, sta->sdata, &sta->sta);
		local->ops->sync_rx_queues(&local->hw);
		trace_drv_वापस_व्योम(local);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम drv_get_et_strings(काष्ठा ieee80211_sub_अगर_data *sdata,
				      u32 sset, u8 *data)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	अगर (local->ops->get_et_strings) अणु
		trace_drv_get_et_strings(local, sset);
		local->ops->get_et_strings(&local->hw, &sdata->vअगर, sset, data);
		trace_drv_वापस_व्योम(local);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम drv_get_et_stats(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ethtool_stats *stats,
				    u64 *data)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	अगर (local->ops->get_et_stats) अणु
		trace_drv_get_et_stats(local);
		local->ops->get_et_stats(&local->hw, &sdata->vअगर, stats, data);
		trace_drv_वापस_व्योम(local);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक drv_get_et_sset_count(काष्ठा ieee80211_sub_अगर_data *sdata,
					पूर्णांक sset)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक rv = 0;
	अगर (local->ops->get_et_sset_count) अणु
		trace_drv_get_et_sset_count(local, sset);
		rv = local->ops->get_et_sset_count(&local->hw, &sdata->vअगर,
						   sset);
		trace_drv_वापस_पूर्णांक(local, rv);
	पूर्ण
	वापस rv;
पूर्ण

पूर्णांक drv_start(काष्ठा ieee80211_local *local);
व्योम drv_stop(काष्ठा ieee80211_local *local);

#अगर_घोषित CONFIG_PM
अटल अंतरभूत पूर्णांक drv_suspend(काष्ठा ieee80211_local *local,
			      काष्ठा cfg80211_wowlan *wowlan)
अणु
	पूर्णांक ret;

	might_sleep();

	trace_drv_suspend(local);
	ret = local->ops->suspend(&local->hw, wowlan);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_resume(काष्ठा ieee80211_local *local)
अणु
	पूर्णांक ret;

	might_sleep();

	trace_drv_resume(local);
	ret = local->ops->resume(&local->hw);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_set_wakeup(काष्ठा ieee80211_local *local,
				  bool enabled)
अणु
	might_sleep();

	अगर (!local->ops->set_wakeup)
		वापस;

	trace_drv_set_wakeup(local, enabled);
	local->ops->set_wakeup(&local->hw, enabled);
	trace_drv_वापस_व्योम(local);
पूर्ण
#पूर्ण_अगर

पूर्णांक drv_add_पूर्णांकerface(काष्ठा ieee80211_local *local,
		      काष्ठा ieee80211_sub_अगर_data *sdata);

पूर्णांक drv_change_पूर्णांकerface(काष्ठा ieee80211_local *local,
			 काष्ठा ieee80211_sub_अगर_data *sdata,
			 क्रमागत nl80211_अगरtype type, bool p2p);

व्योम drv_हटाओ_पूर्णांकerface(काष्ठा ieee80211_local *local,
			  काष्ठा ieee80211_sub_अगर_data *sdata);

अटल अंतरभूत पूर्णांक drv_config(काष्ठा ieee80211_local *local, u32 changed)
अणु
	पूर्णांक ret;

	might_sleep();

	trace_drv_config(local, changed);
	ret = local->ops->config(&local->hw, changed);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_bss_info_changed(काष्ठा ieee80211_local *local,
					काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा ieee80211_bss_conf *info,
					u32 changed)
अणु
	might_sleep();

	अगर (WARN_ON_ONCE(changed & (BSS_CHANGED_BEACON |
				    BSS_CHANGED_BEACON_ENABLED) &&
			 sdata->vअगर.type != NL80211_IFTYPE_AP &&
			 sdata->vअगर.type != NL80211_IFTYPE_ADHOC &&
			 sdata->vअगर.type != NL80211_IFTYPE_MESH_POINT &&
			 sdata->vअगर.type != NL80211_IFTYPE_OCB))
		वापस;

	अगर (WARN_ON_ONCE(sdata->vअगर.type == NL80211_IFTYPE_P2P_DEVICE ||
			 sdata->vअगर.type == NL80211_IFTYPE_न_अंक ||
			 (sdata->vअगर.type == NL80211_IFTYPE_MONITOR &&
			  !sdata->vअगर.mu_mimo_owner &&
			  !(changed & BSS_CHANGED_TXPOWER))))
		वापस;

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_bss_info_changed(local, sdata, info, changed);
	अगर (local->ops->bss_info_changed)
		local->ops->bss_info_changed(&local->hw, &sdata->vअगर, info, changed);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत u64 drv_prepare_multicast(काष्ठा ieee80211_local *local,
					काष्ठा netdev_hw_addr_list *mc_list)
अणु
	u64 ret = 0;

	trace_drv_prepare_multicast(local, mc_list->count);

	अगर (local->ops->prepare_multicast)
		ret = local->ops->prepare_multicast(&local->hw, mc_list);

	trace_drv_वापस_u64(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_configure_filter(काष्ठा ieee80211_local *local,
					अचिन्हित पूर्णांक changed_flags,
					अचिन्हित पूर्णांक *total_flags,
					u64 multicast)
अणु
	might_sleep();

	trace_drv_configure_filter(local, changed_flags, total_flags,
				   multicast);
	local->ops->configure_filter(&local->hw, changed_flags, total_flags,
				     multicast);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_config_अगरace_filter(काष्ठा ieee80211_local *local,
					   काष्ठा ieee80211_sub_अगर_data *sdata,
					   अचिन्हित पूर्णांक filter_flags,
					   अचिन्हित पूर्णांक changed_flags)
अणु
	might_sleep();

	trace_drv_config_अगरace_filter(local, sdata, filter_flags,
				      changed_flags);
	अगर (local->ops->config_अगरace_filter)
		local->ops->config_अगरace_filter(&local->hw, &sdata->vअगर,
						filter_flags,
						changed_flags);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_tim(काष्ठा ieee80211_local *local,
			      काष्ठा ieee80211_sta *sta, bool set)
अणु
	पूर्णांक ret = 0;
	trace_drv_set_tim(local, sta, set);
	अगर (local->ops->set_tim)
		ret = local->ops->set_tim(&local->hw, sta, set);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_key(काष्ठा ieee80211_local *local,
			      क्रमागत set_key_cmd cmd,
			      काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा ieee80211_sta *sta,
			      काष्ठा ieee80211_key_conf *key)
अणु
	पूर्णांक ret;

	might_sleep();

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_set_key(local, cmd, sdata, sta, key);
	ret = local->ops->set_key(&local->hw, cmd, &sdata->vअगर, sta, key);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_update_tkip_key(काष्ठा ieee80211_local *local,
				       काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_key_conf *conf,
				       काष्ठा sta_info *sta, u32 iv32,
				       u16 *phase1key)
अणु
	काष्ठा ieee80211_sta *ista = शून्य;

	अगर (sta)
		ista = &sta->sta;

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_update_tkip_key(local, sdata, conf, ista, iv32);
	अगर (local->ops->update_tkip_key)
		local->ops->update_tkip_key(&local->hw, &sdata->vअगर, conf,
					    ista, iv32, phase1key);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_hw_scan(काष्ठा ieee80211_local *local,
			      काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा ieee80211_scan_request *req)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_hw_scan(local, sdata);
	ret = local->ops->hw_scan(&local->hw, &sdata->vअगर, req);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_cancel_hw_scan(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_cancel_hw_scan(local, sdata);
	local->ops->cancel_hw_scan(&local->hw, &sdata->vअगर);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक
drv_sched_scan_start(काष्ठा ieee80211_local *local,
		     काष्ठा ieee80211_sub_अगर_data *sdata,
		     काष्ठा cfg80211_sched_scan_request *req,
		     काष्ठा ieee80211_scan_ies *ies)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_sched_scan_start(local, sdata);
	ret = local->ops->sched_scan_start(&local->hw, &sdata->vअगर,
					      req, ies);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_sched_scan_stop(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	पूर्णांक ret;

	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_sched_scan_stop(local, sdata);
	ret = local->ops->sched_scan_stop(&local->hw, &sdata->vअगर);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_sw_scan_start(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_sub_अगर_data *sdata,
				     स्थिर u8 *mac_addr)
अणु
	might_sleep();

	trace_drv_sw_scan_start(local, sdata, mac_addr);
	अगर (local->ops->sw_scan_start)
		local->ops->sw_scan_start(&local->hw, &sdata->vअगर, mac_addr);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_sw_scan_complete(काष्ठा ieee80211_local *local,
					काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	might_sleep();

	trace_drv_sw_scan_complete(local, sdata);
	अगर (local->ops->sw_scan_complete)
		local->ops->sw_scan_complete(&local->hw, &sdata->vअगर);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_get_stats(काष्ठा ieee80211_local *local,
				काष्ठा ieee80211_low_level_stats *stats)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	अगर (local->ops->get_stats)
		ret = local->ops->get_stats(&local->hw, stats);
	trace_drv_get_stats(local, stats, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_get_key_seq(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_key *key,
				   काष्ठा ieee80211_key_seq *seq)
अणु
	अगर (local->ops->get_key_seq)
		local->ops->get_key_seq(&local->hw, &key->conf, seq);
	trace_drv_get_key_seq(local, &key->conf);
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_frag_threshold(काष्ठा ieee80211_local *local,
					u32 value)
अणु
	पूर्णांक ret = 0;

	might_sleep();

	trace_drv_set_frag_threshold(local, value);
	अगर (local->ops->set_frag_threshold)
		ret = local->ops->set_frag_threshold(&local->hw, value);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_rts_threshold(काष्ठा ieee80211_local *local,
					u32 value)
अणु
	पूर्णांक ret = 0;

	might_sleep();

	trace_drv_set_rts_threshold(local, value);
	अगर (local->ops->set_rts_threshold)
		ret = local->ops->set_rts_threshold(&local->hw, value);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_coverage_class(काष्ठा ieee80211_local *local,
					 s16 value)
अणु
	पूर्णांक ret = 0;
	might_sleep();

	trace_drv_set_coverage_class(local, value);
	अगर (local->ops->set_coverage_class)
		local->ops->set_coverage_class(&local->hw, value);
	अन्यथा
		ret = -EOPNOTSUPP;

	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_sta_notअगरy(काष्ठा ieee80211_local *local,
				  काष्ठा ieee80211_sub_अगर_data *sdata,
				  क्रमागत sta_notअगरy_cmd cmd,
				  काष्ठा ieee80211_sta *sta)
अणु
	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_sta_notअगरy(local, sdata, cmd, sta);
	अगर (local->ops->sta_notअगरy)
		local->ops->sta_notअगरy(&local->hw, &sdata->vअगर, cmd, sta);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_sta_add(काष्ठा ieee80211_local *local,
			      काष्ठा ieee80211_sub_अगर_data *sdata,
			      काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक ret = 0;

	might_sleep();

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_sta_add(local, sdata, sta);
	अगर (local->ops->sta_add)
		ret = local->ops->sta_add(&local->hw, &sdata->vअगर, sta);

	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_sta_हटाओ(काष्ठा ieee80211_local *local,
				  काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा ieee80211_sta *sta)
अणु
	might_sleep();

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_sta_हटाओ(local, sdata, sta);
	अगर (local->ops->sta_हटाओ)
		local->ops->sta_हटाओ(&local->hw, &sdata->vअगर, sta);

	trace_drv_वापस_व्योम(local);
पूर्ण

#अगर_घोषित CONFIG_MAC80211_DEBUGFS
अटल अंतरभूत व्योम drv_sta_add_debugfs(काष्ठा ieee80211_local *local,
				       काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_sta *sta,
				       काष्ठा dentry *dir)
अणु
	might_sleep();

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	अगर (local->ops->sta_add_debugfs)
		local->ops->sta_add_debugfs(&local->hw, &sdata->vअगर,
					    sta, dir);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम drv_sta_pre_rcu_हटाओ(काष्ठा ieee80211_local *local,
					  काष्ठा ieee80211_sub_अगर_data *sdata,
					  काष्ठा sta_info *sta)
अणु
	might_sleep();

	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_sta_pre_rcu_हटाओ(local, sdata, &sta->sta);
	अगर (local->ops->sta_pre_rcu_हटाओ)
		local->ops->sta_pre_rcu_हटाओ(&local->hw, &sdata->vअगर,
					       &sta->sta);
	trace_drv_वापस_व्योम(local);
पूर्ण

__must_check
पूर्णांक drv_sta_state(काष्ठा ieee80211_local *local,
		  काष्ठा ieee80211_sub_अगर_data *sdata,
		  काष्ठा sta_info *sta,
		  क्रमागत ieee80211_sta_state old_state,
		  क्रमागत ieee80211_sta_state new_state);

__must_check
पूर्णांक drv_sta_set_txpwr(काष्ठा ieee80211_local *local,
		      काष्ठा ieee80211_sub_अगर_data *sdata,
		      काष्ठा sta_info *sta);

व्योम drv_sta_rc_update(काष्ठा ieee80211_local *local,
		       काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा ieee80211_sta *sta, u32 changed);

अटल अंतरभूत व्योम drv_sta_rate_tbl_update(काष्ठा ieee80211_local *local,
					   काष्ठा ieee80211_sub_अगर_data *sdata,
					   काष्ठा ieee80211_sta *sta)
अणु
	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_sta_rate_tbl_update(local, sdata, sta);
	अगर (local->ops->sta_rate_tbl_update)
		local->ops->sta_rate_tbl_update(&local->hw, &sdata->vअगर, sta);

	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_sta_statistics(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा station_info *sinfo)
अणु
	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_sta_statistics(local, sdata, sta);
	अगर (local->ops->sta_statistics)
		local->ops->sta_statistics(&local->hw, &sdata->vअगर, sta, sinfo);
	trace_drv_वापस_व्योम(local);
पूर्ण

पूर्णांक drv_conf_tx(काष्ठा ieee80211_local *local,
		काष्ठा ieee80211_sub_अगर_data *sdata, u16 ac,
		स्थिर काष्ठा ieee80211_tx_queue_params *params);

u64 drv_get_tsf(काष्ठा ieee80211_local *local,
		काष्ठा ieee80211_sub_अगर_data *sdata);
व्योम drv_set_tsf(काष्ठा ieee80211_local *local,
		 काष्ठा ieee80211_sub_अगर_data *sdata,
		 u64 tsf);
व्योम drv_offset_tsf(काष्ठा ieee80211_local *local,
		    काष्ठा ieee80211_sub_अगर_data *sdata,
		    s64 offset);
व्योम drv_reset_tsf(काष्ठा ieee80211_local *local,
		   काष्ठा ieee80211_sub_अगर_data *sdata);

अटल अंतरभूत पूर्णांक drv_tx_last_beacon(काष्ठा ieee80211_local *local)
अणु
	पूर्णांक ret = 0; /* शेष unsupported op क्रम less congestion */

	might_sleep();

	trace_drv_tx_last_beacon(local);
	अगर (local->ops->tx_last_beacon)
		ret = local->ops->tx_last_beacon(&local->hw);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

पूर्णांक drv_ampdu_action(काष्ठा ieee80211_local *local,
		     काष्ठा ieee80211_sub_अगर_data *sdata,
		     काष्ठा ieee80211_ampdu_params *params);

अटल अंतरभूत पूर्णांक drv_get_survey(काष्ठा ieee80211_local *local, पूर्णांक idx,
				काष्ठा survey_info *survey)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	trace_drv_get_survey(local, idx, survey);

	अगर (local->ops->get_survey)
		ret = local->ops->get_survey(&local->hw, idx, survey);

	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_rfसमाप्त_poll(काष्ठा ieee80211_local *local)
अणु
	might_sleep();

	अगर (local->ops->rfसमाप्त_poll)
		local->ops->rfसमाप्त_poll(&local->hw);
पूर्ण

अटल अंतरभूत व्योम drv_flush(काष्ठा ieee80211_local *local,
			     काष्ठा ieee80211_sub_अगर_data *sdata,
			     u32 queues, bool drop)
अणु
	काष्ठा ieee80211_vअगर *vअगर = sdata ? &sdata->vअगर : शून्य;

	might_sleep();

	अगर (sdata && !check_sdata_in_driver(sdata))
		वापस;

	trace_drv_flush(local, queues, drop);
	अगर (local->ops->flush)
		local->ops->flush(&local->hw, vअगर, queues, drop);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_channel_चयन(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	might_sleep();

	trace_drv_channel_चयन(local, sdata, ch_चयन);
	local->ops->channel_चयन(&local->hw, &sdata->vअगर, ch_चयन);
	trace_drv_वापस_व्योम(local);
पूर्ण


अटल अंतरभूत पूर्णांक drv_set_antenna(काष्ठा ieee80211_local *local,
				  u32 tx_ant, u32 rx_ant)
अणु
	पूर्णांक ret = -EOPNOTSUPP;
	might_sleep();
	अगर (local->ops->set_antenna)
		ret = local->ops->set_antenna(&local->hw, tx_ant, rx_ant);
	trace_drv_set_antenna(local, tx_ant, rx_ant, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_get_antenna(काष्ठा ieee80211_local *local,
				  u32 *tx_ant, u32 *rx_ant)
अणु
	पूर्णांक ret = -EOPNOTSUPP;
	might_sleep();
	अगर (local->ops->get_antenna)
		ret = local->ops->get_antenna(&local->hw, tx_ant, rx_ant);
	trace_drv_get_antenna(local, *tx_ant, *rx_ant, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_reमुख्य_on_channel(काष्ठा ieee80211_local *local,
					काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा ieee80211_channel *chan,
					अचिन्हित पूर्णांक duration,
					क्रमागत ieee80211_roc_type type)
अणु
	पूर्णांक ret;

	might_sleep();

	trace_drv_reमुख्य_on_channel(local, sdata, chan, duration, type);
	ret = local->ops->reमुख्य_on_channel(&local->hw, &sdata->vअगर,
					    chan, duration, type);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_cancel_reमुख्य_on_channel(काष्ठा ieee80211_local *local,
			     काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	पूर्णांक ret;

	might_sleep();

	trace_drv_cancel_reमुख्य_on_channel(local, sdata);
	ret = local->ops->cancel_reमुख्य_on_channel(&local->hw, &sdata->vअगर);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_ringparam(काष्ठा ieee80211_local *local,
				    u32 tx, u32 rx)
अणु
	पूर्णांक ret = -ENOTSUPP;

	might_sleep();

	trace_drv_set_ringparam(local, tx, rx);
	अगर (local->ops->set_ringparam)
		ret = local->ops->set_ringparam(&local->hw, tx, rx);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_get_ringparam(काष्ठा ieee80211_local *local,
				     u32 *tx, u32 *tx_max, u32 *rx, u32 *rx_max)
अणु
	might_sleep();

	trace_drv_get_ringparam(local, tx, tx_max, rx, rx_max);
	अगर (local->ops->get_ringparam)
		local->ops->get_ringparam(&local->hw, tx, tx_max, rx, rx_max);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत bool drv_tx_frames_pending(काष्ठा ieee80211_local *local)
अणु
	bool ret = false;

	might_sleep();

	trace_drv_tx_frames_pending(local);
	अगर (local->ops->tx_frames_pending)
		ret = local->ops->tx_frames_pending(&local->hw);
	trace_drv_वापस_bool(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_bitrate_mask(काष्ठा ieee80211_local *local,
				       काष्ठा ieee80211_sub_अगर_data *sdata,
				       स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_set_bitrate_mask(local, sdata, mask);
	अगर (local->ops->set_bitrate_mask)
		ret = local->ops->set_bitrate_mask(&local->hw,
						   &sdata->vअगर, mask);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_set_rekey_data(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_set_rekey_data(local, sdata, data);
	अगर (local->ops->set_rekey_data)
		local->ops->set_rekey_data(&local->hw, &sdata->vअगर, data);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_event_callback(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_sub_अगर_data *sdata,
				      स्थिर काष्ठा ieee80211_event *event)
अणु
	trace_drv_event_callback(local, sdata, event);
	अगर (local->ops->event_callback)
		local->ops->event_callback(&local->hw, &sdata->vअगर, event);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम
drv_release_buffered_frames(काष्ठा ieee80211_local *local,
			    काष्ठा sta_info *sta, u16 tids, पूर्णांक num_frames,
			    क्रमागत ieee80211_frame_release_type reason,
			    bool more_data)
अणु
	trace_drv_release_buffered_frames(local, &sta->sta, tids, num_frames,
					  reason, more_data);
	अगर (local->ops->release_buffered_frames)
		local->ops->release_buffered_frames(&local->hw, &sta->sta, tids,
						    num_frames, reason,
						    more_data);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम
drv_allow_buffered_frames(काष्ठा ieee80211_local *local,
			  काष्ठा sta_info *sta, u16 tids, पूर्णांक num_frames,
			  क्रमागत ieee80211_frame_release_type reason,
			  bool more_data)
अणु
	trace_drv_allow_buffered_frames(local, &sta->sta, tids, num_frames,
					reason, more_data);
	अगर (local->ops->allow_buffered_frames)
		local->ops->allow_buffered_frames(&local->hw, &sta->sta,
						  tids, num_frames, reason,
						  more_data);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_mgd_prepare_tx(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_sub_अगर_data *sdata,
				      u16 duration)
अणु
	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस;
	WARN_ON_ONCE(sdata->vअगर.type != NL80211_IFTYPE_STATION);

	trace_drv_mgd_prepare_tx(local, sdata, duration);
	अगर (local->ops->mgd_prepare_tx)
		local->ops->mgd_prepare_tx(&local->hw, &sdata->vअगर, duration);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम
drv_mgd_protect_tdls_discover(काष्ठा ieee80211_local *local,
			      काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस;
	WARN_ON_ONCE(sdata->vअगर.type != NL80211_IFTYPE_STATION);

	trace_drv_mgd_protect_tdls_discover(local, sdata);
	अगर (local->ops->mgd_protect_tdls_discover)
		local->ops->mgd_protect_tdls_discover(&local->hw, &sdata->vअगर);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_add_chanctx(काष्ठा ieee80211_local *local,
				  काष्ठा ieee80211_chanctx *ctx)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	trace_drv_add_chanctx(local, ctx);
	अगर (local->ops->add_chanctx)
		ret = local->ops->add_chanctx(&local->hw, &ctx->conf);
	trace_drv_वापस_पूर्णांक(local, ret);
	अगर (!ret)
		ctx->driver_present = true;

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_हटाओ_chanctx(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_chanctx *ctx)
अणु
	might_sleep();

	अगर (WARN_ON(!ctx->driver_present))
		वापस;

	trace_drv_हटाओ_chanctx(local, ctx);
	अगर (local->ops->हटाओ_chanctx)
		local->ops->हटाओ_chanctx(&local->hw, &ctx->conf);
	trace_drv_वापस_व्योम(local);
	ctx->driver_present = false;
पूर्ण

अटल अंतरभूत व्योम drv_change_chanctx(काष्ठा ieee80211_local *local,
				      काष्ठा ieee80211_chanctx *ctx,
				      u32 changed)
अणु
	might_sleep();

	trace_drv_change_chanctx(local, ctx, changed);
	अगर (local->ops->change_chanctx) अणु
		WARN_ON_ONCE(!ctx->driver_present);
		local->ops->change_chanctx(&local->hw, &ctx->conf, changed);
	पूर्ण
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_assign_vअगर_chanctx(काष्ठा ieee80211_local *local,
					 काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा ieee80211_chanctx *ctx)
अणु
	पूर्णांक ret = 0;

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_assign_vअगर_chanctx(local, sdata, ctx);
	अगर (local->ops->assign_vअगर_chanctx) अणु
		WARN_ON_ONCE(!ctx->driver_present);
		ret = local->ops->assign_vअगर_chanctx(&local->hw,
						     &sdata->vअगर,
						     &ctx->conf);
	पूर्ण
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_unassign_vअगर_chanctx(काष्ठा ieee80211_local *local,
					    काष्ठा ieee80211_sub_अगर_data *sdata,
					    काष्ठा ieee80211_chanctx *ctx)
अणु
	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_unassign_vअगर_chanctx(local, sdata, ctx);
	अगर (local->ops->unassign_vअगर_chanctx) अणु
		WARN_ON_ONCE(!ctx->driver_present);
		local->ops->unassign_vअगर_chanctx(&local->hw,
						 &sdata->vअगर,
						 &ctx->conf);
	पूर्ण
	trace_drv_वापस_व्योम(local);
पूर्ण

पूर्णांक drv_चयन_vअगर_chanctx(काष्ठा ieee80211_local *local,
			   काष्ठा ieee80211_vअगर_chanctx_चयन *vअगरs,
			   पूर्णांक n_vअगरs, क्रमागत ieee80211_chanctx_चयन_mode mode);

अटल अंतरभूत पूर्णांक drv_start_ap(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	पूर्णांक ret = 0;

	might_sleep();

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_start_ap(local, sdata, &sdata->vअगर.bss_conf);
	अगर (local->ops->start_ap)
		ret = local->ops->start_ap(&local->hw, &sdata->vअगर);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_stop_ap(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_stop_ap(local, sdata);
	अगर (local->ops->stop_ap)
		local->ops->stop_ap(&local->hw, &sdata->vअगर);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम
drv_reconfig_complete(काष्ठा ieee80211_local *local,
		      क्रमागत ieee80211_reconfig_type reconfig_type)
अणु
	might_sleep();

	trace_drv_reconfig_complete(local, reconfig_type);
	अगर (local->ops->reconfig_complete)
		local->ops->reconfig_complete(&local->hw, reconfig_type);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम
drv_set_शेष_unicast_key(काष्ठा ieee80211_local *local,
			    काष्ठा ieee80211_sub_अगर_data *sdata,
			    पूर्णांक key_idx)
अणु
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	WARN_ON_ONCE(key_idx < -1 || key_idx > 3);

	trace_drv_set_शेष_unicast_key(local, sdata, key_idx);
	अगर (local->ops->set_शेष_unicast_key)
		local->ops->set_शेष_unicast_key(&local->hw, &sdata->vअगर,
						    key_idx);
	trace_drv_वापस_व्योम(local);
पूर्ण

#अगर IS_ENABLED(CONFIG_IPV6)
अटल अंतरभूत व्योम drv_ipv6_addr_change(काष्ठा ieee80211_local *local,
					काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा inet6_dev *idev)
अणु
	trace_drv_ipv6_addr_change(local, sdata);
	अगर (local->ops->ipv6_addr_change)
		local->ops->ipv6_addr_change(&local->hw, &sdata->vअगर, idev);
	trace_drv_वापस_व्योम(local);
पूर्ण
#पूर्ण_अगर

अटल अंतरभूत व्योम
drv_channel_चयन_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
			  काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	अगर (local->ops->channel_चयन_beacon) अणु
		trace_drv_channel_चयन_beacon(local, sdata, chandef);
		local->ops->channel_चयन_beacon(&local->hw, &sdata->vअगर,
						  chandef);
	पूर्ण
पूर्ण

अटल अंतरभूत पूर्णांक
drv_pre_channel_चयन(काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ret = 0;

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_pre_channel_चयन(local, sdata, ch_चयन);
	अगर (local->ops->pre_channel_चयन)
		ret = local->ops->pre_channel_चयन(&local->hw, &sdata->vअगर,
						     ch_चयन);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_post_channel_चयन(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक ret = 0;

	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_post_channel_चयन(local, sdata);
	अगर (local->ops->post_channel_चयन)
		ret = local->ops->post_channel_चयन(&local->hw, &sdata->vअगर);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
drv_पात_channel_चयन(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_पात_channel_चयन(local, sdata);

	अगर (local->ops->पात_channel_चयन)
		local->ops->पात_channel_चयन(&local->hw, &sdata->vअगर);
पूर्ण

अटल अंतरभूत व्योम
drv_channel_चयन_rx_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा ieee80211_channel_चयन *ch_चयन)
अणु
	काष्ठा ieee80211_local *local = sdata->local;

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_channel_चयन_rx_beacon(local, sdata, ch_चयन);
	अगर (local->ops->channel_चयन_rx_beacon)
		local->ops->channel_चयन_rx_beacon(&local->hw, &sdata->vअगर,
						     ch_चयन);
पूर्ण

अटल अंतरभूत पूर्णांक drv_join_ibss(काष्ठा ieee80211_local *local,
				काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	पूर्णांक ret = 0;

	might_sleep();
	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_join_ibss(local, sdata, &sdata->vअगर.bss_conf);
	अगर (local->ops->join_ibss)
		ret = local->ops->join_ibss(&local->hw, &sdata->vअगर);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_leave_ibss(काष्ठा ieee80211_local *local,
				  काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	might_sleep();
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_leave_ibss(local, sdata);
	अगर (local->ops->leave_ibss)
		local->ops->leave_ibss(&local->hw, &sdata->vअगर);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत u32 drv_get_expected_throughput(काष्ठा ieee80211_local *local,
					      काष्ठा sta_info *sta)
अणु
	u32 ret = 0;

	trace_drv_get_expected_throughput(&sta->sta);
	अगर (local->ops->get_expected_throughput && sta->uploaded)
		ret = local->ops->get_expected_throughput(&local->hw, &sta->sta);
	trace_drv_वापस_u32(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_get_txघातer(काष्ठा ieee80211_local *local,
				  काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक *dbm)
अणु
	पूर्णांक ret;

	अगर (!local->ops->get_txघातer)
		वापस -EOPNOTSUPP;

	ret = local->ops->get_txघातer(&local->hw, &sdata->vअगर, dbm);
	trace_drv_get_txघातer(local, sdata, *dbm, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक
drv_tdls_channel_चयन(काष्ठा ieee80211_local *local,
			काष्ठा ieee80211_sub_अगर_data *sdata,
			काष्ठा ieee80211_sta *sta, u8 oper_class,
			काष्ठा cfg80211_chan_def *chandef,
			काष्ठा sk_buff *पंचांगpl_skb, u32 ch_sw_पंचांग_ie)
अणु
	पूर्णांक ret;

	might_sleep();
	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	अगर (!local->ops->tdls_channel_चयन)
		वापस -EOPNOTSUPP;

	trace_drv_tdls_channel_चयन(local, sdata, sta, oper_class, chandef);
	ret = local->ops->tdls_channel_चयन(&local->hw, &sdata->vअगर, sta,
					      oper_class, chandef, पंचांगpl_skb,
					      ch_sw_पंचांग_ie);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम
drv_tdls_cancel_channel_चयन(काष्ठा ieee80211_local *local,
			       काष्ठा ieee80211_sub_अगर_data *sdata,
			       काष्ठा ieee80211_sta *sta)
अणु
	might_sleep();
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	अगर (!local->ops->tdls_cancel_channel_चयन)
		वापस;

	trace_drv_tdls_cancel_channel_चयन(local, sdata, sta);
	local->ops->tdls_cancel_channel_चयन(&local->hw, &sdata->vअगर, sta);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम
drv_tdls_recv_channel_चयन(काष्ठा ieee80211_local *local,
			     काष्ठा ieee80211_sub_अगर_data *sdata,
			     काष्ठा ieee80211_tdls_ch_sw_params *params)
अणु
	trace_drv_tdls_recv_channel_चयन(local, sdata, params);
	अगर (local->ops->tdls_recv_channel_चयन)
		local->ops->tdls_recv_channel_चयन(&local->hw, &sdata->vअगर,
						     params);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_wake_tx_queue(काष्ठा ieee80211_local *local,
				     काष्ठा txq_info *txq)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(txq->txq.vअगर);

	अगर (local->in_reconfig)
		वापस;

	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_wake_tx_queue(local, sdata, txq);
	local->ops->wake_tx_queue(&local->hw, &txq->txq);
पूर्ण

अटल अंतरभूत व्योम schedule_and_wake_txq(काष्ठा ieee80211_local *local,
					 काष्ठा txq_info *txqi)
अणु
	ieee80211_schedule_txq(&local->hw, &txqi->txq);
	drv_wake_tx_queue(local, txqi);
पूर्ण

अटल अंतरभूत पूर्णांक drv_can_aggregate_in_amsdu(काष्ठा ieee80211_local *local,
					     काष्ठा sk_buff *head,
					     काष्ठा sk_buff *skb)
अणु
	अगर (!local->ops->can_aggregate_in_amsdu)
		वापस true;

	वापस local->ops->can_aggregate_in_amsdu(&local->hw, head, skb);
पूर्ण

अटल अंतरभूत पूर्णांक
drv_get_fपंचांग_responder_stats(काष्ठा ieee80211_local *local,
			    काष्ठा ieee80211_sub_अगर_data *sdata,
			    काष्ठा cfg80211_fपंचांग_responder_stats *fपंचांग_stats)
अणु
	u32 ret = -EOPNOTSUPP;

	अगर (local->ops->get_fपंचांग_responder_stats)
		ret = local->ops->get_fपंचांग_responder_stats(&local->hw,
							 &sdata->vअगर,
							 fपंचांग_stats);
	trace_drv_get_fपंचांग_responder_stats(local, sdata, fपंचांग_stats);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_start_pmsr(काष्ठा ieee80211_local *local,
				 काष्ठा ieee80211_sub_अगर_data *sdata,
				 काष्ठा cfg80211_pmsr_request *request)
अणु
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();
	अगर (!check_sdata_in_driver(sdata))
		वापस -EIO;

	trace_drv_start_pmsr(local, sdata);

	अगर (local->ops->start_pmsr)
		ret = local->ops->start_pmsr(&local->hw, &sdata->vअगर, request);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_पात_pmsr(काष्ठा ieee80211_local *local,
				  काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा cfg80211_pmsr_request *request)
अणु
	trace_drv_पात_pmsr(local, sdata);

	might_sleep();
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	अगर (local->ops->पात_pmsr)
		local->ops->पात_pmsr(&local->hw, &sdata->vअगर, request);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_start_nan(काष्ठा ieee80211_local *local,
				काष्ठा ieee80211_sub_अगर_data *sdata,
				काष्ठा cfg80211_nan_conf *conf)
अणु
	पूर्णांक ret;

	might_sleep();
	check_sdata_in_driver(sdata);

	trace_drv_start_nan(local, sdata, conf);
	ret = local->ops->start_nan(&local->hw, &sdata->vअगर, conf);
	trace_drv_वापस_पूर्णांक(local, ret);
	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_stop_nan(काष्ठा ieee80211_local *local,
				काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	might_sleep();
	check_sdata_in_driver(sdata);

	trace_drv_stop_nan(local, sdata);
	local->ops->stop_nan(&local->hw, &sdata->vअगर);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_nan_change_conf(काष्ठा ieee80211_local *local,
				       काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा cfg80211_nan_conf *conf,
				       u32 changes)
अणु
	पूर्णांक ret;

	might_sleep();
	check_sdata_in_driver(sdata);

	अगर (!local->ops->nan_change_conf)
		वापस -EOPNOTSUPP;

	trace_drv_nan_change_conf(local, sdata, conf, changes);
	ret = local->ops->nan_change_conf(&local->hw, &sdata->vअगर, conf,
					  changes);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_add_nan_func(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_sub_अगर_data *sdata,
				   स्थिर काष्ठा cfg80211_nan_func *nan_func)
अणु
	पूर्णांक ret;

	might_sleep();
	check_sdata_in_driver(sdata);

	अगर (!local->ops->add_nan_func)
		वापस -EOPNOTSUPP;

	trace_drv_add_nan_func(local, sdata, nan_func);
	ret = local->ops->add_nan_func(&local->hw, &sdata->vअगर, nan_func);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_del_nan_func(काष्ठा ieee80211_local *local,
				   काष्ठा ieee80211_sub_अगर_data *sdata,
				   u8 instance_id)
अणु
	might_sleep();
	check_sdata_in_driver(sdata);

	trace_drv_del_nan_func(local, sdata, instance_id);
	अगर (local->ops->del_nan_func)
		local->ops->del_nan_func(&local->hw, &sdata->vअगर, instance_id);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत पूर्णांक drv_set_tid_config(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा ieee80211_sta *sta,
				     काष्ठा cfg80211_tid_config *tid_conf)
अणु
	पूर्णांक ret;

	might_sleep();
	ret = local->ops->set_tid_config(&local->hw, &sdata->vअगर, sta,
					 tid_conf);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत पूर्णांक drv_reset_tid_config(काष्ठा ieee80211_local *local,
				       काष्ठा ieee80211_sub_अगर_data *sdata,
				       काष्ठा ieee80211_sta *sta, u8 tids)
अणु
	पूर्णांक ret;

	might_sleep();
	ret = local->ops->reset_tid_config(&local->hw, &sdata->vअगर, sta, tids);
	trace_drv_वापस_पूर्णांक(local, ret);

	वापस ret;
पूर्ण

अटल अंतरभूत व्योम drv_update_vअगर_offload(काष्ठा ieee80211_local *local,
					  काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	might_sleep();
	check_sdata_in_driver(sdata);

	अगर (!local->ops->update_vअगर_offload)
		वापस;

	trace_drv_update_vअगर_offload(local, sdata);
	local->ops->update_vअगर_offload(&local->hw, &sdata->vअगर);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_sta_set_4addr(काष्ठा ieee80211_local *local,
				     काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा ieee80211_sta *sta, bool enabled)
अणु
	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_sta_set_4addr(local, sdata, sta, enabled);
	अगर (local->ops->sta_set_4addr)
		local->ops->sta_set_4addr(&local->hw, &sdata->vअगर, sta, enabled);
	trace_drv_वापस_व्योम(local);
पूर्ण

अटल अंतरभूत व्योम drv_sta_set_decap_offload(काष्ठा ieee80211_local *local,
					     काष्ठा ieee80211_sub_अगर_data *sdata,
					     काष्ठा ieee80211_sta *sta,
					     bool enabled)
अणु
	sdata = get_bss_sdata(sdata);
	अगर (!check_sdata_in_driver(sdata))
		वापस;

	trace_drv_sta_set_decap_offload(local, sdata, sta, enabled);
	अगर (local->ops->sta_set_decap_offload)
		local->ops->sta_set_decap_offload(&local->hw, &sdata->vअगर, sta,
						  enabled);
	trace_drv_वापस_व्योम(local);
पूर्ण

#पूर्ण_अगर /* __MAC80211_DRIVER_OPS */
