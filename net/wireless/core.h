<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Wireless configuration पूर्णांकerface पूर्णांकernals.
 *
 * Copyright 2006-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2018-2020 Intel Corporation
 */
#अगर_अघोषित __NET_WIRELESS_CORE_H
#घोषणा __NET_WIRELESS_CORE_H
#समावेश <linux/list.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/rbtree.h>
#समावेश <linux/debugfs.h>
#समावेश <linux/rfसमाप्त.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/rtnetlink.h>
#समावेश <net/genetlink.h>
#समावेश <net/cfg80211.h>
#समावेश "reg.h"


#घोषणा WIPHY_IDX_INVALID	-1

काष्ठा cfg80211_रेजिस्टरed_device अणु
	स्थिर काष्ठा cfg80211_ops *ops;
	काष्ठा list_head list;

	/* rfसमाप्त support */
	काष्ठा rfसमाप्त_ops rfसमाप्त_ops;
	काष्ठा rfसमाप्त *rfसमाप्त;
	काष्ठा work_काष्ठा rfसमाप्त_block;

	/* ISO / IEC 3166 alpha2 क्रम which this device is receiving
	 * country IEs on, this can help disregard country IEs from APs
	 * on the same alpha2 quickly. The alpha2 may dअगरfer from
	 * cfg80211_regकरोमुख्य's alpha2 when an पूर्णांकersection has occurred.
	 * If the AP is reconfigured this can also be used to tell us अगर
	 * the country on the country IE changed. */
	अक्षर country_ie_alpha2[2];

	/*
	 * the driver requests the regulatory core to set this regulatory
	 * करोमुख्य as the wiphy's. Only used क्रम %REGULATORY_WIPHY_SELF_MANAGED
	 * devices using the regulatory_set_wiphy_regd() API
	 */
	स्थिर काष्ठा ieee80211_regकरोमुख्य *requested_regd;

	/* If a Country IE has been received this tells us the environment
	 * which its telling us its in. This शेषs to ENVIRON_ANY */
	क्रमागत environment_cap env;

	/* wiphy index, पूर्णांकernal only */
	पूर्णांक wiphy_idx;

	/* रक्षित by RTNL */
	पूर्णांक devlist_generation, wdev_id;
	पूर्णांक खोलोcount;
	रुको_queue_head_t dev_रुको;

	काष्ठा list_head beacon_registrations;
	spinlock_t beacon_registrations_lock;

	/* रक्षित by RTNL only */
	पूर्णांक num_running_अगरaces;
	पूर्णांक num_running_monitor_अगरaces;
	u64 cookie_counter;

	/* BSSes/scanning */
	spinlock_t bss_lock;
	काष्ठा list_head bss_list;
	काष्ठा rb_root bss_tree;
	u32 bss_generation;
	u32 bss_entries;
	काष्ठा cfg80211_scan_request *scan_req; /* रक्षित by RTNL */
	काष्ठा cfg80211_scan_request *पूर्णांक_scan_req;
	काष्ठा sk_buff *scan_msg;
	काष्ठा list_head sched_scan_req_list;
	समय64_t suspend_at;
	काष्ठा work_काष्ठा scan_करोne_wk;

	काष्ठा genl_info *cur_cmd_info;

	काष्ठा work_काष्ठा conn_work;
	काष्ठा work_काष्ठा event_work;

	काष्ठा delayed_work dfs_update_channels_wk;

	/* netlink port which started critical protocol (0 means not started) */
	u32 crit_proto_nlportid;

	काष्ठा cfg80211_coalesce *coalesce;

	काष्ठा work_काष्ठा destroy_work;
	काष्ठा work_काष्ठा sched_scan_stop_wk;
	काष्ठा work_काष्ठा sched_scan_res_wk;

	काष्ठा cfg80211_chan_def radar_chandef;
	काष्ठा work_काष्ठा propagate_radar_detect_wk;

	काष्ठा cfg80211_chan_def cac_करोne_chandef;
	काष्ठा work_काष्ठा propagate_cac_करोne_wk;

	काष्ठा work_काष्ठा mgmt_registrations_update_wk;

	/* must be last because of the way we करो wiphy_priv(),
	 * and it should at least be aligned to NETDEV_ALIGN */
	काष्ठा wiphy wiphy __aligned(NETDEV_ALIGN);
पूर्ण;

अटल अंतरभूत
काष्ठा cfg80211_रेजिस्टरed_device *wiphy_to_rdev(काष्ठा wiphy *wiphy)
अणु
	BUG_ON(!wiphy);
	वापस container_of(wiphy, काष्ठा cfg80211_रेजिस्टरed_device, wiphy);
पूर्ण

अटल अंतरभूत व्योम
cfg80211_rdev_मुक्त_wowlan(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
#अगर_घोषित CONFIG_PM
	पूर्णांक i;

	अगर (!rdev->wiphy.wowlan_config)
		वापस;
	क्रम (i = 0; i < rdev->wiphy.wowlan_config->n_patterns; i++)
		kमुक्त(rdev->wiphy.wowlan_config->patterns[i].mask);
	kमुक्त(rdev->wiphy.wowlan_config->patterns);
	अगर (rdev->wiphy.wowlan_config->tcp &&
	    rdev->wiphy.wowlan_config->tcp->sock)
		sock_release(rdev->wiphy.wowlan_config->tcp->sock);
	kमुक्त(rdev->wiphy.wowlan_config->tcp);
	kमुक्त(rdev->wiphy.wowlan_config->nd_config);
	kमुक्त(rdev->wiphy.wowlan_config);
#पूर्ण_अगर
पूर्ण

अटल अंतरभूत u64 cfg80211_assign_cookie(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	u64 r = ++rdev->cookie_counter;

	अगर (WARN_ON(r == 0))
		r = ++rdev->cookie_counter;

	वापस r;
पूर्ण

बाह्य काष्ठा workqueue_काष्ठा *cfg80211_wq;
बाह्य काष्ठा list_head cfg80211_rdev_list;
बाह्य पूर्णांक cfg80211_rdev_list_generation;

काष्ठा cfg80211_पूर्णांकernal_bss अणु
	काष्ठा list_head list;
	काष्ठा list_head hidden_list;
	काष्ठा rb_node rbn;
	u64 ts_bootसमय;
	अचिन्हित दीर्घ ts;
	अचिन्हित दीर्घ refcount;
	atomic_t hold;

	/* समय at the start of the reception of the first octet of the
	 * बारtamp field of the last beacon/probe received क्रम this BSS.
	 * The समय is the TSF of the BSS specअगरied by %parent_bssid.
	 */
	u64 parent_tsf;

	/* the BSS according to which %parent_tsf is set. This is set to
	 * the BSS that the पूर्णांकerface that requested the scan was connected to
	 * when the beacon/probe was received.
	 */
	u8 parent_bssid[ETH_ALEN] __aligned(2);

	/* must be last because of priv member */
	काष्ठा cfg80211_bss pub;
पूर्ण;

अटल अंतरभूत काष्ठा cfg80211_पूर्णांकernal_bss *bss_from_pub(काष्ठा cfg80211_bss *pub)
अणु
	वापस container_of(pub, काष्ठा cfg80211_पूर्णांकernal_bss, pub);
पूर्ण

अटल अंतरभूत व्योम cfg80211_hold_bss(काष्ठा cfg80211_पूर्णांकernal_bss *bss)
अणु
	atomic_inc(&bss->hold);
	अगर (bss->pub.transmitted_bss) अणु
		bss = container_of(bss->pub.transmitted_bss,
				   काष्ठा cfg80211_पूर्णांकernal_bss, pub);
		atomic_inc(&bss->hold);
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम cfg80211_unhold_bss(काष्ठा cfg80211_पूर्णांकernal_bss *bss)
अणु
	पूर्णांक r = atomic_dec_वापस(&bss->hold);
	WARN_ON(r < 0);
	अगर (bss->pub.transmitted_bss) अणु
		bss = container_of(bss->pub.transmitted_bss,
				   काष्ठा cfg80211_पूर्णांकernal_bss, pub);
		r = atomic_dec_वापस(&bss->hold);
		WARN_ON(r < 0);
	पूर्ण
पूर्ण


काष्ठा cfg80211_रेजिस्टरed_device *cfg80211_rdev_by_wiphy_idx(पूर्णांक wiphy_idx);
पूर्णांक get_wiphy_idx(काष्ठा wiphy *wiphy);

काष्ठा wiphy *wiphy_idx_to_wiphy(पूर्णांक wiphy_idx);

पूर्णांक cfg80211_चयन_netns(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net *net);

व्योम cfg80211_init_wdev(काष्ठा wireless_dev *wdev);
व्योम cfg80211_रेजिस्टर_wdev(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा wireless_dev *wdev);

अटल अंतरभूत व्योम wdev_lock(काष्ठा wireless_dev *wdev)
	__acquires(wdev)
अणु
	mutex_lock(&wdev->mtx);
	__acquire(wdev->mtx);
पूर्ण

अटल अंतरभूत व्योम wdev_unlock(काष्ठा wireless_dev *wdev)
	__releases(wdev)
अणु
	__release(wdev->mtx);
	mutex_unlock(&wdev->mtx);
पूर्ण

#घोषणा ASSERT_WDEV_LOCK(wdev) lockdep_निश्चित_held(&(wdev)->mtx)

अटल अंतरभूत bool cfg80211_has_monitors_only(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	वापस rdev->num_running_अगरaces == rdev->num_running_monitor_अगरaces &&
	       rdev->num_running_अगरaces > 0;
पूर्ण

क्रमागत cfg80211_event_type अणु
	EVENT_CONNECT_RESULT,
	EVENT_ROAMED,
	EVENT_DISCONNECTED,
	EVENT_IBSS_JOINED,
	EVENT_STOPPED,
	EVENT_PORT_AUTHORIZED,
पूर्ण;

काष्ठा cfg80211_event अणु
	काष्ठा list_head list;
	क्रमागत cfg80211_event_type type;

	जोड़ अणु
		काष्ठा cfg80211_connect_resp_params cr;
		काष्ठा cfg80211_roam_info rm;
		काष्ठा अणु
			स्थिर u8 *ie;
			माप_प्रकार ie_len;
			u16 reason;
			bool locally_generated;
		पूर्ण dc;
		काष्ठा अणु
			u8 bssid[ETH_ALEN];
			काष्ठा ieee80211_channel *channel;
		पूर्ण ij;
		काष्ठा अणु
			u8 bssid[ETH_ALEN];
		पूर्ण pa;
	पूर्ण;
पूर्ण;

काष्ठा cfg80211_cached_keys अणु
	काष्ठा key_params params[CFG80211_MAX_WEP_KEYS];
	u8 data[CFG80211_MAX_WEP_KEYS][WLAN_KEY_LEN_WEP104];
	पूर्णांक def;
पूर्ण;

क्रमागत cfg80211_chan_mode अणु
	CHAN_MODE_UNDEFINED,
	CHAN_MODE_SHARED,
	CHAN_MODE_EXCLUSIVE,
पूर्ण;

काष्ठा cfg80211_beacon_registration अणु
	काष्ठा list_head list;
	u32 nlportid;
पूर्ण;

काष्ठा cfg80211_cqm_config अणु
	u32 rssi_hyst;
	s32 last_rssi_event_value;
	पूर्णांक n_rssi_thresholds;
	s32 rssi_thresholds[];
पूर्ण;

व्योम cfg80211_destroy_अगरaces(काष्ठा cfg80211_रेजिस्टरed_device *rdev);

/* मुक्त object */
व्योम cfg80211_dev_मुक्त(काष्ठा cfg80211_रेजिस्टरed_device *rdev);

पूर्णांक cfg80211_dev_नाम(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			अक्षर *newname);

व्योम ieee80211_set_bitrate_flags(काष्ठा wiphy *wiphy);

व्योम cfg80211_bss_expire(काष्ठा cfg80211_रेजिस्टरed_device *rdev);
व्योम cfg80211_bss_age(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
                      अचिन्हित दीर्घ age_secs);
व्योम cfg80211_update_assoc_bss_entry(काष्ठा wireless_dev *wdev,
				     काष्ठा ieee80211_channel *channel);

/* IBSS */
पूर्णांक __cfg80211_join_ibss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev,
			 काष्ठा cfg80211_ibss_params *params,
			 काष्ठा cfg80211_cached_keys *connkeys);
व्योम cfg80211_clear_ibss(काष्ठा net_device *dev, bool nowext);
पूर्णांक __cfg80211_leave_ibss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *dev, bool nowext);
पूर्णांक cfg80211_leave_ibss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev, bool nowext);
व्योम __cfg80211_ibss_joined(काष्ठा net_device *dev, स्थिर u8 *bssid,
			    काष्ठा ieee80211_channel *channel);
पूर्णांक cfg80211_ibss_wext_join(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा wireless_dev *wdev);

/* mesh */
बाह्य स्थिर काष्ठा mesh_config शेष_mesh_config;
बाह्य स्थिर काष्ठा mesh_setup शेष_mesh_setup;
पूर्णांक __cfg80211_join_mesh(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev,
			 काष्ठा mesh_setup *setup,
			 स्थिर काष्ठा mesh_config *conf);
पूर्णांक __cfg80211_leave_mesh(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *dev);
पूर्णांक cfg80211_leave_mesh(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev);
पूर्णांक cfg80211_set_mesh_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा wireless_dev *wdev,
			      काष्ठा cfg80211_chan_def *chandef);

/* OCB */
पूर्णांक __cfg80211_join_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev,
			काष्ठा ocb_setup *setup);
पूर्णांक cfg80211_join_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा net_device *dev,
		      काष्ठा ocb_setup *setup);
पूर्णांक __cfg80211_leave_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev);
पूर्णांक cfg80211_leave_ocb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा net_device *dev);

/* AP */
पूर्णांक __cfg80211_stop_ap(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा net_device *dev, bool notअगरy);
पूर्णांक cfg80211_stop_ap(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     काष्ठा net_device *dev, bool notअगरy);

/* MLME */
पूर्णांक cfg80211_mlme_auth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा net_device *dev,
		       काष्ठा ieee80211_channel *chan,
		       क्रमागत nl80211_auth_type auth_type,
		       स्थिर u8 *bssid,
		       स्थिर u8 *ssid, पूर्णांक ssid_len,
		       स्थिर u8 *ie, पूर्णांक ie_len,
		       स्थिर u8 *key, पूर्णांक key_len, पूर्णांक key_idx,
		       स्थिर u8 *auth_data, पूर्णांक auth_data_len);
पूर्णांक cfg80211_mlme_assoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev,
			काष्ठा ieee80211_channel *chan,
			स्थिर u8 *bssid,
			स्थिर u8 *ssid, पूर्णांक ssid_len,
			काष्ठा cfg80211_assoc_request *req);
पूर्णांक cfg80211_mlme_deauth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev, स्थिर u8 *bssid,
			 स्थिर u8 *ie, पूर्णांक ie_len, u16 reason,
			 bool local_state_change);
पूर्णांक cfg80211_mlme_disassoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net_device *dev, स्थिर u8 *bssid,
			   स्थिर u8 *ie, पूर्णांक ie_len, u16 reason,
			   bool local_state_change);
व्योम cfg80211_mlme_करोwn(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev);
पूर्णांक cfg80211_mlme_रेजिस्टर_mgmt(काष्ठा wireless_dev *wdev, u32 snd_pid,
				u16 frame_type, स्थिर u8 *match_data,
				पूर्णांक match_len, bool multicast_rx,
				काष्ठा netlink_ext_ack *extack);
व्योम cfg80211_mgmt_registrations_update_wk(काष्ठा work_काष्ठा *wk);
व्योम cfg80211_mlme_unरेजिस्टर_socket(काष्ठा wireless_dev *wdev, u32 nlpid);
व्योम cfg80211_mlme_purge_registrations(काष्ठा wireless_dev *wdev);
पूर्णांक cfg80211_mlme_mgmt_tx(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा wireless_dev *wdev,
			  काष्ठा cfg80211_mgmt_tx_params *params,
			  u64 *cookie);
व्योम cfg80211_oper_and_ht_capa(काष्ठा ieee80211_ht_cap *ht_capa,
			       स्थिर काष्ठा ieee80211_ht_cap *ht_capa_mask);
व्योम cfg80211_oper_and_vht_capa(काष्ठा ieee80211_vht_cap *vht_capa,
				स्थिर काष्ठा ieee80211_vht_cap *vht_capa_mask);

/* SME events */
पूर्णांक cfg80211_connect(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     काष्ठा net_device *dev,
		     काष्ठा cfg80211_connect_params *connect,
		     काष्ठा cfg80211_cached_keys *connkeys,
		     स्थिर u8 *prev_bssid);
व्योम __cfg80211_connect_result(काष्ठा net_device *dev,
			       काष्ठा cfg80211_connect_resp_params *params,
			       bool wextev);
व्योम __cfg80211_disconnected(काष्ठा net_device *dev, स्थिर u8 *ie,
			     माप_प्रकार ie_len, u16 reason, bool from_ap);
पूर्णांक cfg80211_disconnect(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev, u16 reason,
			bool wextev);
व्योम __cfg80211_roamed(काष्ठा wireless_dev *wdev,
		       काष्ठा cfg80211_roam_info *info);
व्योम __cfg80211_port_authorized(काष्ठा wireless_dev *wdev, स्थिर u8 *bssid);
पूर्णांक cfg80211_mgd_wext_connect(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा wireless_dev *wdev);
व्योम cfg80211_स्वतःdisconnect_wk(काष्ठा work_काष्ठा *work);

/* SME implementation */
व्योम cfg80211_conn_work(काष्ठा work_काष्ठा *work);
व्योम cfg80211_sme_scan_करोne(काष्ठा net_device *dev);
bool cfg80211_sme_rx_assoc_resp(काष्ठा wireless_dev *wdev, u16 status);
व्योम cfg80211_sme_rx_auth(काष्ठा wireless_dev *wdev, स्थिर u8 *buf, माप_प्रकार len);
व्योम cfg80211_sme_disassoc(काष्ठा wireless_dev *wdev);
व्योम cfg80211_sme_deauth(काष्ठा wireless_dev *wdev);
व्योम cfg80211_sme_auth_समयout(काष्ठा wireless_dev *wdev);
व्योम cfg80211_sme_assoc_समयout(काष्ठा wireless_dev *wdev);
व्योम cfg80211_sme_abanकरोn_assoc(काष्ठा wireless_dev *wdev);

/* पूर्णांकernal helpers */
bool cfg80211_supported_cipher_suite(काष्ठा wiphy *wiphy, u32 cipher);
bool cfg80211_valid_key_idx(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    पूर्णांक key_idx, bool pairwise);
पूर्णांक cfg80211_validate_key_settings(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा key_params *params, पूर्णांक key_idx,
				   bool pairwise, स्थिर u8 *mac_addr);
व्योम __cfg80211_scan_करोne(काष्ठा work_काष्ठा *wk);
व्योम ___cfg80211_scan_करोne(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   bool send_message);
व्योम cfg80211_add_sched_scan_req(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा cfg80211_sched_scan_request *req);
पूर्णांक cfg80211_sched_scan_req_possible(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     bool want_multi);
व्योम cfg80211_sched_scan_results_wk(काष्ठा work_काष्ठा *work);
पूर्णांक cfg80211_stop_sched_scan_req(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा cfg80211_sched_scan_request *req,
				 bool driver_initiated);
पूर्णांक __cfg80211_stop_sched_scan(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       u64 reqid, bool driver_initiated);
व्योम cfg80211_upload_connect_keys(काष्ठा wireless_dev *wdev);
पूर्णांक cfg80211_change_अगरace(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *dev, क्रमागत nl80211_अगरtype ntype,
			  काष्ठा vअगर_params *params);
व्योम cfg80211_process_rdev_events(काष्ठा cfg80211_रेजिस्टरed_device *rdev);
व्योम cfg80211_process_wdev_events(काष्ठा wireless_dev *wdev);

bool cfg80211_करोes_bw_fit_range(स्थिर काष्ठा ieee80211_freq_range *freq_range,
				u32 center_freq_khz, u32 bw_khz);

पूर्णांक cfg80211_scan(काष्ठा cfg80211_रेजिस्टरed_device *rdev);

बाह्य काष्ठा work_काष्ठा cfg80211_disconnect_work;

/**
 * cfg80211_chandef_dfs_usable - checks अगर chandef is DFS usable
 * @wiphy: the wiphy to validate against
 * @chandef: the channel definition to check
 *
 * Checks अगर chandef is usable and we can/need start CAC on such channel.
 *
 * Return: true अगर all channels available and at least
 *	   one channel requires CAC (NL80211_DFS_USABLE)
 */
bool cfg80211_chandef_dfs_usable(काष्ठा wiphy *wiphy,
				 स्थिर काष्ठा cfg80211_chan_def *chandef);

व्योम cfg80211_set_dfs_state(काष्ठा wiphy *wiphy,
			    स्थिर काष्ठा cfg80211_chan_def *chandef,
			    क्रमागत nl80211_dfs_state dfs_state);

व्योम cfg80211_dfs_channels_update_work(काष्ठा work_काष्ठा *work);

अचिन्हित पूर्णांक
cfg80211_chandef_dfs_cac_समय(काष्ठा wiphy *wiphy,
			      स्थिर काष्ठा cfg80211_chan_def *chandef);

व्योम cfg80211_sched_dfs_chan_update(काष्ठा cfg80211_रेजिस्टरed_device *rdev);

bool cfg80211_any_wiphy_oper_chan(काष्ठा wiphy *wiphy,
				  काष्ठा ieee80211_channel *chan);

bool cfg80211_beaconing_अगरace_active(काष्ठा wireless_dev *wdev);

bool cfg80211_is_sub_chan(काष्ठा cfg80211_chan_def *chandef,
			  काष्ठा ieee80211_channel *chan);

अटल अंतरभूत अचिन्हित पूर्णांक elapsed_jअगरfies_msecs(अचिन्हित दीर्घ start)
अणु
	अचिन्हित दीर्घ end = jअगरfies;

	अगर (end >= start)
		वापस jअगरfies_to_msecs(end - start);

	वापस jअगरfies_to_msecs(end + (अच_दीर्घ_उच्च - start) + 1);
पूर्ण

व्योम
cfg80211_get_chan_state(काष्ठा wireless_dev *wdev,
		        काष्ठा ieee80211_channel **chan,
		        क्रमागत cfg80211_chan_mode *chanmode,
		        u8 *radar_detect);

पूर्णांक cfg80211_set_monitor_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा cfg80211_chan_def *chandef);

पूर्णांक ieee80211_get_ratemask(काष्ठा ieee80211_supported_band *sband,
			   स्थिर u8 *rates, अचिन्हित पूर्णांक n_rates,
			   u32 *mask);

पूर्णांक cfg80211_validate_beacon_पूर्णांक(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 क्रमागत nl80211_अगरtype अगरtype, u32 beacon_पूर्णांक);

व्योम cfg80211_update_अगरace_num(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       क्रमागत nl80211_अगरtype अगरtype, पूर्णांक num);

व्योम __cfg80211_leave(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा wireless_dev *wdev);
व्योम cfg80211_leave(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		    काष्ठा wireless_dev *wdev);

व्योम cfg80211_stop_p2p_device(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा wireless_dev *wdev);

व्योम cfg80211_stop_nan(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा wireless_dev *wdev);

काष्ठा cfg80211_पूर्णांकernal_bss *
cfg80211_bss_update(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		    काष्ठा cfg80211_पूर्णांकernal_bss *पंचांगp,
		    bool संकेत_valid, अचिन्हित दीर्घ ts);
#अगर_घोषित CONFIG_CFG80211_DEVELOPER_WARNINGS
#घोषणा CFG80211_DEV_WARN_ON(cond)	WARN_ON(cond)
#अन्यथा
/*
 * Trick to enable using it as a condition,
 * and also not give a warning when it's
 * not used that way.
 */
#घोषणा CFG80211_DEV_WARN_ON(cond)	(अणुbool __r = (cond); __r; पूर्ण)
#पूर्ण_अगर

व्योम cfg80211_cqm_config_मुक्त(काष्ठा wireless_dev *wdev);

व्योम cfg80211_release_pmsr(काष्ठा wireless_dev *wdev, u32 portid);
व्योम cfg80211_pmsr_wdev_करोwn(काष्ठा wireless_dev *wdev);
व्योम cfg80211_pmsr_मुक्त_wk(काष्ठा work_काष्ठा *work);

#पूर्ण_अगर /* __NET_WIRELESS_CORE_H */
