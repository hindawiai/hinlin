<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211 configuration hooks क्रम cfg80211
 *
 * Copyright 2006-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2015  Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 * Copyright (C) 2018-2020 Intel Corporation
 */

#समावेश <linux/ieee80211.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <net/net_namespace.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/fips.h>
#समावेश <linux/अगर_ether.h>
#समावेश <net/cfg80211.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "rate.h"
#समावेश "mesh.h"
#समावेश "wme.h"

अटल व्योम ieee80211_set_mu_mimo_follow(काष्ठा ieee80211_sub_अगर_data *sdata,
					 काष्ठा vअगर_params *params)
अणु
	bool mu_mimo_groups = false;
	bool mu_mimo_follow = false;

	अगर (params->vht_mumimo_groups) अणु
		u64 membership;

		BUILD_BUG_ON(माप(membership) != WLAN_MEMBERSHIP_LEN);

		स_नकल(sdata->vअगर.bss_conf.mu_group.membership,
		       params->vht_mumimo_groups, WLAN_MEMBERSHIP_LEN);
		स_नकल(sdata->vअगर.bss_conf.mu_group.position,
		       params->vht_mumimo_groups + WLAN_MEMBERSHIP_LEN,
		       WLAN_USER_POSITION_LEN);
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_MU_GROUPS);
		/* करोn't care about endianness - just check क्रम 0 */
		स_नकल(&membership, params->vht_mumimo_groups,
		       WLAN_MEMBERSHIP_LEN);
		mu_mimo_groups = membership != 0;
	पूर्ण

	अगर (params->vht_mumimo_follow_addr) अणु
		mu_mimo_follow =
			is_valid_ether_addr(params->vht_mumimo_follow_addr);
		ether_addr_copy(sdata->u.mntr.mu_follow_addr,
				params->vht_mumimo_follow_addr);
	पूर्ण

	sdata->vअगर.mu_mimo_owner = mu_mimo_groups || mu_mimo_follow;
पूर्ण

अटल पूर्णांक ieee80211_set_mon_options(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा vअगर_params *params)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *monitor_sdata;

	/* check flags first */
	अगर (params->flags && ieee80211_sdata_running(sdata)) अणु
		u32 mask = MONITOR_FLAG_COOK_FRAMES | MONITOR_FLAG_ACTIVE;

		/*
		 * Prohibit MONITOR_FLAG_COOK_FRAMES and
		 * MONITOR_FLAG_ACTIVE to be changed जबतक the
		 * पूर्णांकerface is up.
		 * Else we would need to add a lot of cruft
		 * to update everything:
		 *	cooked_mntrs, monitor and all fअगर_* counters
		 *	reconfigure hardware
		 */
		अगर ((params->flags & mask) != (sdata->u.mntr.flags & mask))
			वापस -EBUSY;
	पूर्ण

	/* also validate MU-MIMO change */
	monitor_sdata = rtnl_dereference(local->monitor_sdata);

	अगर (!monitor_sdata &&
	    (params->vht_mumimo_groups || params->vht_mumimo_follow_addr))
		वापस -EOPNOTSUPP;

	/* apply all changes now - no failures allowed */

	अगर (monitor_sdata)
		ieee80211_set_mu_mimo_follow(monitor_sdata, params);

	अगर (params->flags) अणु
		अगर (ieee80211_sdata_running(sdata)) अणु
			ieee80211_adjust_monitor_flags(sdata, -1);
			sdata->u.mntr.flags = params->flags;
			ieee80211_adjust_monitor_flags(sdata, 1);

			ieee80211_configure_filter(local);
		पूर्ण अन्यथा अणु
			/*
			 * Because the पूर्णांकerface is करोwn, ieee80211_करो_stop
			 * and ieee80211_करो_खोलो take care of "everything"
			 * mentioned in the comment above.
			 */
			sdata->u.mntr.flags = params->flags;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा wireless_dev *ieee80211_add_अगरace(काष्ठा wiphy *wiphy,
						स्थिर अक्षर *name,
						अचिन्हित अक्षर name_assign_type,
						क्रमागत nl80211_अगरtype type,
						काष्ठा vअगर_params *params)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा wireless_dev *wdev;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक err;

	err = ieee80211_अगर_add(local, name, name_assign_type, &wdev, type, params);
	अगर (err)
		वापस ERR_PTR(err);

	sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

	अगर (type == NL80211_IFTYPE_MONITOR) अणु
		err = ieee80211_set_mon_options(sdata, params);
		अगर (err) अणु
			ieee80211_अगर_हटाओ(sdata);
			वापस शून्य;
		पूर्ण
	पूर्ण

	वापस wdev;
पूर्ण

अटल पूर्णांक ieee80211_del_अगरace(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	ieee80211_अगर_हटाओ(IEEE80211_WDEV_TO_SUB_IF(wdev));

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_change_अगरace(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *dev,
				  क्रमागत nl80211_अगरtype type,
				  काष्ठा vअगर_params *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	पूर्णांक ret;

	ret = ieee80211_अगर_change_type(sdata, type);
	अगर (ret)
		वापस ret;

	अगर (type == NL80211_IFTYPE_AP_VLAN && params->use_4addr == 0) अणु
		RCU_INIT_POINTER(sdata->u.vlan.sta, शून्य);
		ieee80211_check_fast_rx_अगरace(sdata);
	पूर्ण अन्यथा अगर (type == NL80211_IFTYPE_STATION && params->use_4addr >= 0) अणु
		sdata->u.mgd.use_4addr = params->use_4addr;
	पूर्ण

	अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR) अणु
		ret = ieee80211_set_mon_options(sdata, params);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_start_p2p_device(काष्ठा wiphy *wiphy,
				      काष्ठा wireless_dev *wdev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	पूर्णांक ret;

	mutex_lock(&sdata->local->chanctx_mtx);
	ret = ieee80211_check_combinations(sdata, शून्य, 0, 0);
	mutex_unlock(&sdata->local->chanctx_mtx);
	अगर (ret < 0)
		वापस ret;

	वापस ieee80211_करो_खोलो(wdev, true);
पूर्ण

अटल व्योम ieee80211_stop_p2p_device(काष्ठा wiphy *wiphy,
				      काष्ठा wireless_dev *wdev)
अणु
	ieee80211_sdata_stop(IEEE80211_WDEV_TO_SUB_IF(wdev));
पूर्ण

अटल पूर्णांक ieee80211_start_nan(काष्ठा wiphy *wiphy,
			       काष्ठा wireless_dev *wdev,
			       काष्ठा cfg80211_nan_conf *conf)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	पूर्णांक ret;

	mutex_lock(&sdata->local->chanctx_mtx);
	ret = ieee80211_check_combinations(sdata, शून्य, 0, 0);
	mutex_unlock(&sdata->local->chanctx_mtx);
	अगर (ret < 0)
		वापस ret;

	ret = ieee80211_करो_खोलो(wdev, true);
	अगर (ret)
		वापस ret;

	ret = drv_start_nan(sdata->local, sdata, conf);
	अगर (ret)
		ieee80211_sdata_stop(sdata);

	sdata->u.nan.conf = *conf;

	वापस ret;
पूर्ण

अटल व्योम ieee80211_stop_nan(काष्ठा wiphy *wiphy,
			       काष्ठा wireless_dev *wdev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

	drv_stop_nan(sdata->local, sdata);
	ieee80211_sdata_stop(sdata);
पूर्ण

अटल पूर्णांक ieee80211_nan_change_conf(काष्ठा wiphy *wiphy,
				     काष्ठा wireless_dev *wdev,
				     काष्ठा cfg80211_nan_conf *conf,
				     u32 changes)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	काष्ठा cfg80211_nan_conf new_conf;
	पूर्णांक ret = 0;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	अगर (!ieee80211_sdata_running(sdata))
		वापस -ENETDOWN;

	new_conf = sdata->u.nan.conf;

	अगर (changes & CFG80211_न_अंक_CONF_CHANGED_PREF)
		new_conf.master_pref = conf->master_pref;

	अगर (changes & CFG80211_न_अंक_CONF_CHANGED_BANDS)
		new_conf.bands = conf->bands;

	ret = drv_nan_change_conf(sdata->local, sdata, &new_conf, changes);
	अगर (!ret)
		sdata->u.nan.conf = new_conf;

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_add_nan_func(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev,
				  काष्ठा cfg80211_nan_func *nan_func)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	पूर्णांक ret;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	अगर (!ieee80211_sdata_running(sdata))
		वापस -ENETDOWN;

	spin_lock_bh(&sdata->u.nan.func_lock);

	ret = idr_alloc(&sdata->u.nan.function_inst_ids,
			nan_func, 1, sdata->local->hw.max_nan_de_entries + 1,
			GFP_ATOMIC);
	spin_unlock_bh(&sdata->u.nan.func_lock);

	अगर (ret < 0)
		वापस ret;

	nan_func->instance_id = ret;

	WARN_ON(nan_func->instance_id == 0);

	ret = drv_add_nan_func(sdata->local, sdata, nan_func);
	अगर (ret) अणु
		spin_lock_bh(&sdata->u.nan.func_lock);
		idr_हटाओ(&sdata->u.nan.function_inst_ids,
			   nan_func->instance_id);
		spin_unlock_bh(&sdata->u.nan.func_lock);
	पूर्ण

	वापस ret;
पूर्ण

अटल काष्ठा cfg80211_nan_func *
ieee80211_find_nan_func_by_cookie(काष्ठा ieee80211_sub_अगर_data *sdata,
				  u64 cookie)
अणु
	काष्ठा cfg80211_nan_func *func;
	पूर्णांक id;

	lockdep_निश्चित_held(&sdata->u.nan.func_lock);

	idr_क्रम_each_entry(&sdata->u.nan.function_inst_ids, func, id) अणु
		अगर (func->cookie == cookie)
			वापस func;
	पूर्ण

	वापस शून्य;
पूर्ण

अटल व्योम ieee80211_del_nan_func(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev, u64 cookie)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	काष्ठा cfg80211_nan_func *func;
	u8 instance_id = 0;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_न_अंक ||
	    !ieee80211_sdata_running(sdata))
		वापस;

	spin_lock_bh(&sdata->u.nan.func_lock);

	func = ieee80211_find_nan_func_by_cookie(sdata, cookie);
	अगर (func)
		instance_id = func->instance_id;

	spin_unlock_bh(&sdata->u.nan.func_lock);

	अगर (instance_id)
		drv_del_nan_func(sdata->local, sdata, instance_id);
पूर्ण

अटल पूर्णांक ieee80211_set_noack_map(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *dev,
				  u16 noack_map)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	sdata->noack_map = noack_map;

	ieee80211_check_fast_xmit_अगरace(sdata);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_tx(काष्ठा ieee80211_sub_अगर_data *sdata,
			    स्थिर u8 *mac_addr, u8 key_idx)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_key *key;
	काष्ठा sta_info *sta;
	पूर्णांक ret = -EINVAL;

	अगर (!wiphy_ext_feature_isset(local->hw.wiphy,
				     NL80211_EXT_FEATURE_EXT_KEY_ID))
		वापस -EINVAL;

	sta = sta_info_get_bss(sdata, mac_addr);

	अगर (!sta)
		वापस -EINVAL;

	अगर (sta->ptk_idx == key_idx)
		वापस 0;

	mutex_lock(&local->key_mtx);
	key = key_mtx_dereference(local, sta->ptk[key_idx]);

	अगर (key && key->conf.flags & IEEE80211_KEY_FLAG_NO_AUTO_TX)
		ret = ieee80211_set_tx_key(key);

	mutex_unlock(&local->key_mtx);
	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u8 key_idx, bool pairwise, स्थिर u8 *mac_addr,
			     काष्ठा key_params *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta = शून्य;
	स्थिर काष्ठा ieee80211_cipher_scheme *cs = शून्य;
	काष्ठा ieee80211_key *key;
	पूर्णांक err;

	अगर (!ieee80211_sdata_running(sdata))
		वापस -ENETDOWN;

	अगर (pairwise && params->mode == NL80211_KEY_SET_TX)
		वापस ieee80211_set_tx(sdata, mac_addr, key_idx);

	/* reject WEP and TKIP keys अगर WEP failed to initialize */
	चयन (params->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_WEP104:
		अगर (WARN_ON_ONCE(fips_enabled))
			वापस -EINVAL;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		अवरोध;
	शेष:
		cs = ieee80211_cs_get(local, params->cipher, sdata->vअगर.type);
		अवरोध;
	पूर्ण

	key = ieee80211_key_alloc(params->cipher, key_idx, params->key_len,
				  params->key, params->seq_len, params->seq,
				  cs);
	अगर (IS_ERR(key))
		वापस PTR_ERR(key);

	अगर (pairwise)
		key->conf.flags |= IEEE80211_KEY_FLAG_PAIRWISE;

	अगर (params->mode == NL80211_KEY_NO_TX)
		key->conf.flags |= IEEE80211_KEY_FLAG_NO_AUTO_TX;

	mutex_lock(&local->sta_mtx);

	अगर (mac_addr) अणु
		sta = sta_info_get_bss(sdata, mac_addr);
		/*
		 * The ASSOC test makes sure the driver is पढ़ोy to
		 * receive the key. When wpa_supplicant has roamed
		 * using FT, it attempts to set the key beक्रमe
		 * association has completed, this rejects that attempt
		 * so it will set the key again after association.
		 *
		 * TODO: accept the key अगर we have a station entry and
		 *       add it to the device after the station.
		 */
		अगर (!sta || !test_sta_flag(sta, WLAN_STA_ASSOC)) अणु
			ieee80211_key_मुक्त_unused(key);
			err = -ENOENT;
			जाओ out_unlock;
		पूर्ण
	पूर्ण

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (sdata->u.mgd.mfp != IEEE80211_MFP_DISABLED)
			key->conf.flags |= IEEE80211_KEY_FLAG_RX_MGMT;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
		/* Keys without a station are used क्रम TX only */
		अगर (sta && test_sta_flag(sta, WLAN_STA_MFP))
			key->conf.flags |= IEEE80211_KEY_FLAG_RX_MGMT;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		/* no MFP (yet) */
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
#अगर_घोषित CONFIG_MAC80211_MESH
		अगर (sdata->u.mesh.security != IEEE80211_MESH_SEC_NONE)
			key->conf.flags |= IEEE80211_KEY_FLAG_RX_MGMT;
		अवरोध;
#पूर्ण_अगर
	हाल NL80211_IFTYPE_WDS:
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_P2P_DEVICE:
	हाल NL80211_IFTYPE_न_अंक:
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NUM_NL80211_IFTYPES:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_OCB:
		/* shouldn't happen */
		WARN_ON_ONCE(1);
		अवरोध;
	पूर्ण

	अगर (sta)
		sta->cipher_scheme = cs;

	err = ieee80211_key_link(key, sdata, sta);

 out_unlock:
	mutex_unlock(&local->sta_mtx);

	वापस err;
पूर्ण

अटल पूर्णांक ieee80211_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u8 key_idx, bool pairwise, स्थिर u8 *mac_addr)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_key *key = शून्य;
	पूर्णांक ret;

	mutex_lock(&local->sta_mtx);
	mutex_lock(&local->key_mtx);

	अगर (mac_addr) अणु
		ret = -ENOENT;

		sta = sta_info_get_bss(sdata, mac_addr);
		अगर (!sta)
			जाओ out_unlock;

		अगर (pairwise)
			key = key_mtx_dereference(local, sta->ptk[key_idx]);
		अन्यथा
			key = key_mtx_dereference(local, sta->gtk[key_idx]);
	पूर्ण अन्यथा
		key = key_mtx_dereference(local, sdata->keys[key_idx]);

	अगर (!key) अणु
		ret = -ENOENT;
		जाओ out_unlock;
	पूर्ण

	ieee80211_key_मुक्त(key, sdata->vअगर.type == NL80211_IFTYPE_STATION);

	ret = 0;
 out_unlock:
	mutex_unlock(&local->key_mtx);
	mutex_unlock(&local->sta_mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_get_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u8 key_idx, bool pairwise, स्थिर u8 *mac_addr,
			     व्योम *cookie,
			     व्योम (*callback)(व्योम *cookie,
					      काष्ठा key_params *params))
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info *sta = शून्य;
	u8 seq[6] = अणु0पूर्ण;
	काष्ठा key_params params;
	काष्ठा ieee80211_key *key = शून्य;
	u64 pn64;
	u32 iv32;
	u16 iv16;
	पूर्णांक err = -ENOENT;
	काष्ठा ieee80211_key_seq kseq = अणुपूर्ण;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	rcu_पढ़ो_lock();

	अगर (mac_addr) अणु
		sta = sta_info_get_bss(sdata, mac_addr);
		अगर (!sta)
			जाओ out;

		अगर (pairwise && key_idx < NUM_DEFAULT_KEYS)
			key = rcu_dereference(sta->ptk[key_idx]);
		अन्यथा अगर (!pairwise &&
			 key_idx < NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS +
			 NUM_DEFAULT_BEACON_KEYS)
			key = rcu_dereference(sta->gtk[key_idx]);
	पूर्ण अन्यथा
		key = rcu_dereference(sdata->keys[key_idx]);

	अगर (!key)
		जाओ out;

	स_रखो(&params, 0, माप(params));

	params.cipher = key->conf.cipher;

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		pn64 = atomic64_पढ़ो(&key->conf.tx_pn);
		iv32 = TKIP_PN_TO_IV32(pn64);
		iv16 = TKIP_PN_TO_IV16(pn64);

		अगर (key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE &&
		    !(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV)) अणु
			drv_get_key_seq(sdata->local, key, &kseq);
			iv32 = kseq.tkip.iv32;
			iv16 = kseq.tkip.iv16;
		पूर्ण

		seq[0] = iv16 & 0xff;
		seq[1] = (iv16 >> 8) & 0xff;
		seq[2] = iv32 & 0xff;
		seq[3] = (iv32 >> 8) & 0xff;
		seq[4] = (iv32 >> 16) & 0xff;
		seq[5] = (iv32 >> 24) & 0xff;
		params.seq = seq;
		params.seq_len = 6;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		BUILD_BUG_ON(दुरत्व(typeof(kseq), ccmp) !=
			     दुरत्व(typeof(kseq), aes_cmac));
		fallthrough;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		BUILD_BUG_ON(दुरत्व(typeof(kseq), ccmp) !=
			     दुरत्व(typeof(kseq), aes_gmac));
		fallthrough;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		BUILD_BUG_ON(दुरत्व(typeof(kseq), ccmp) !=
			     दुरत्व(typeof(kseq), gcmp));

		अगर (key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE &&
		    !(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV)) अणु
			drv_get_key_seq(sdata->local, key, &kseq);
			स_नकल(seq, kseq.ccmp.pn, 6);
		पूर्ण अन्यथा अणु
			pn64 = atomic64_पढ़ो(&key->conf.tx_pn);
			seq[0] = pn64;
			seq[1] = pn64 >> 8;
			seq[2] = pn64 >> 16;
			seq[3] = pn64 >> 24;
			seq[4] = pn64 >> 32;
			seq[5] = pn64 >> 40;
		पूर्ण
		params.seq = seq;
		params.seq_len = 6;
		अवरोध;
	शेष:
		अगर (!(key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE))
			अवरोध;
		अगर (WARN_ON(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV))
			अवरोध;
		drv_get_key_seq(sdata->local, key, &kseq);
		params.seq = kseq.hw.seq;
		params.seq_len = kseq.hw.seq_len;
		अवरोध;
	पूर्ण

	params.key = key->conf.key;
	params.key_len = key->conf.keylen;

	callback(cookie, &params);
	err = 0;

 out:
	rcu_पढ़ो_unlock();
	वापस err;
पूर्ण

अटल पूर्णांक ieee80211_config_शेष_key(काष्ठा wiphy *wiphy,
					काष्ठा net_device *dev,
					u8 key_idx, bool uni,
					bool multi)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	ieee80211_set_शेष_key(sdata, key_idx, uni, multi);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_config_शेष_mgmt_key(काष्ठा wiphy *wiphy,
					     काष्ठा net_device *dev,
					     u8 key_idx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	ieee80211_set_शेष_mgmt_key(sdata, key_idx);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_config_शेष_beacon_key(काष्ठा wiphy *wiphy,
					       काष्ठा net_device *dev,
					       u8 key_idx)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	ieee80211_set_शेष_beacon_key(sdata, key_idx);

	वापस 0;
पूर्ण

व्योम sta_set_rate_info_tx(काष्ठा sta_info *sta,
			  स्थिर काष्ठा ieee80211_tx_rate *rate,
			  काष्ठा rate_info *rinfo)
अणु
	rinfo->flags = 0;
	अगर (rate->flags & IEEE80211_TX_RC_MCS) अणु
		rinfo->flags |= RATE_INFO_FLAGS_MCS;
		rinfo->mcs = rate->idx;
	पूर्ण अन्यथा अगर (rate->flags & IEEE80211_TX_RC_VHT_MCS) अणु
		rinfo->flags |= RATE_INFO_FLAGS_VHT_MCS;
		rinfo->mcs = ieee80211_rate_get_vht_mcs(rate);
		rinfo->nss = ieee80211_rate_get_vht_nss(rate);
	पूर्ण अन्यथा अणु
		काष्ठा ieee80211_supported_band *sband;
		पूर्णांक shअगरt = ieee80211_vअगर_get_shअगरt(&sta->sdata->vअगर);
		u16 brate;

		sband = ieee80211_get_sband(sta->sdata);
		WARN_ON_ONCE(sband && !sband->bitrates);
		अगर (sband && sband->bitrates) अणु
			brate = sband->bitrates[rate->idx].bitrate;
			rinfo->legacy = DIV_ROUND_UP(brate, 1 << shअगरt);
		पूर्ण
	पूर्ण
	अगर (rate->flags & IEEE80211_TX_RC_40_MHZ_WIDTH)
		rinfo->bw = RATE_INFO_BW_40;
	अन्यथा अगर (rate->flags & IEEE80211_TX_RC_80_MHZ_WIDTH)
		rinfo->bw = RATE_INFO_BW_80;
	अन्यथा अगर (rate->flags & IEEE80211_TX_RC_160_MHZ_WIDTH)
		rinfo->bw = RATE_INFO_BW_160;
	अन्यथा
		rinfo->bw = RATE_INFO_BW_20;
	अगर (rate->flags & IEEE80211_TX_RC_SHORT_GI)
		rinfo->flags |= RATE_INFO_FLAGS_SHORT_GI;
पूर्ण

अटल पूर्णांक ieee80211_dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	पूर्णांक ret = -ENOENT;

	mutex_lock(&local->sta_mtx);

	sta = sta_info_get_by_idx(sdata, idx);
	अगर (sta) अणु
		ret = 0;
		स_नकल(mac, sta->sta.addr, ETH_ALEN);
		sta_set_sinfo(sta, sinfo, true);
	पूर्ण

	mutex_unlock(&local->sta_mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_dump_survey(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 पूर्णांक idx, काष्ठा survey_info *survey)
अणु
	काष्ठा ieee80211_local *local = wdev_priv(dev->ieee80211_ptr);

	वापस drv_get_survey(local, idx, survey);
पूर्ण

अटल पूर्णांक ieee80211_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा sta_info *sta;
	पूर्णांक ret = -ENOENT;

	mutex_lock(&local->sta_mtx);

	sta = sta_info_get_bss(sdata, mac);
	अगर (sta) अणु
		ret = 0;
		sta_set_sinfo(sta, sinfo, true);
	पूर्ण

	mutex_unlock(&local->sta_mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_set_monitor_channel(काष्ठा wiphy *wiphy,
					 काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक ret = 0;

	अगर (cfg80211_chandef_identical(&local->monitor_chandef, chandef))
		वापस 0;

	mutex_lock(&local->mtx);
	अगर (local->use_chanctx) अणु
		sdata = rtnl_dereference(local->monitor_sdata);
		अगर (sdata) अणु
			ieee80211_vअगर_release_channel(sdata);
			ret = ieee80211_vअगर_use_channel(sdata, chandef,
					IEEE80211_CHANCTX_EXCLUSIVE);
		पूर्ण
	पूर्ण अन्यथा अगर (local->खोलो_count == local->monitors) अणु
		local->_oper_chandef = *chandef;
		ieee80211_hw_config(local, 0);
	पूर्ण

	अगर (ret == 0)
		local->monitor_chandef = *chandef;
	mutex_unlock(&local->mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_set_probe_resp(काष्ठा ieee80211_sub_अगर_data *sdata,
				    स्थिर u8 *resp, माप_प्रकार resp_len,
				    स्थिर काष्ठा ieee80211_csa_settings *csa)
अणु
	काष्ठा probe_resp *new, *old;

	अगर (!resp || !resp_len)
		वापस 1;

	old = sdata_dereference(sdata->u.ap.probe_resp, sdata);

	new = kzalloc(माप(काष्ठा probe_resp) + resp_len, GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	new->len = resp_len;
	स_नकल(new->data, resp, resp_len);

	अगर (csa)
		स_नकल(new->cntdwn_counter_offsets, csa->counter_offsets_presp,
		       csa->n_counter_offsets_presp *
		       माप(new->cntdwn_counter_offsets[0]));

	rcu_assign_poपूर्णांकer(sdata->u.ap.probe_resp, new);
	अगर (old)
		kमुक्त_rcu(old, rcu_head);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_fils_discovery(काष्ठा ieee80211_sub_अगर_data *sdata,
					काष्ठा cfg80211_fils_discovery *params)
अणु
	काष्ठा fils_discovery_data *new, *old = शून्य;
	काष्ठा ieee80211_fils_discovery *fd;

	अगर (!params->पंचांगpl || !params->पंचांगpl_len)
		वापस -EINVAL;

	fd = &sdata->vअगर.bss_conf.fils_discovery;
	fd->min_पूर्णांकerval = params->min_पूर्णांकerval;
	fd->max_पूर्णांकerval = params->max_पूर्णांकerval;

	old = sdata_dereference(sdata->u.ap.fils_discovery, sdata);
	new = kzalloc(माप(*new) + params->पंचांगpl_len, GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;
	new->len = params->पंचांगpl_len;
	स_नकल(new->data, params->पंचांगpl, params->पंचांगpl_len);
	rcu_assign_poपूर्णांकer(sdata->u.ap.fils_discovery, new);

	अगर (old)
		kमुक्त_rcu(old, rcu_head);

	वापस 0;
पूर्ण

अटल पूर्णांक
ieee80211_set_unsol_bcast_probe_resp(काष्ठा ieee80211_sub_अगर_data *sdata,
				     काष्ठा cfg80211_unsol_bcast_probe_resp *params)
अणु
	काष्ठा unsol_bcast_probe_resp_data *new, *old = शून्य;

	अगर (!params->पंचांगpl || !params->पंचांगpl_len)
		वापस -EINVAL;

	old = sdata_dereference(sdata->u.ap.unsol_bcast_probe_resp, sdata);
	new = kzalloc(माप(*new) + params->पंचांगpl_len, GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;
	new->len = params->पंचांगpl_len;
	स_नकल(new->data, params->पंचांगpl, params->पंचांगpl_len);
	rcu_assign_poपूर्णांकer(sdata->u.ap.unsol_bcast_probe_resp, new);

	अगर (old)
		kमुक्त_rcu(old, rcu_head);

	sdata->vअगर.bss_conf.unsol_bcast_probe_resp_पूर्णांकerval =
							params->पूर्णांकerval;

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_fपंचांग_responder_params(
				काष्ठा ieee80211_sub_अगर_data *sdata,
				स्थिर u8 *lci, माप_प्रकार lci_len,
				स्थिर u8 *civicloc, माप_प्रकार civicloc_len)
अणु
	काष्ठा ieee80211_fपंचांग_responder_params *new, *old;
	काष्ठा ieee80211_bss_conf *bss_conf;
	u8 *pos;
	पूर्णांक len;

	अगर (!lci_len && !civicloc_len)
		वापस 0;

	bss_conf = &sdata->vअगर.bss_conf;
	old = bss_conf->fपंचांगr_params;
	len = lci_len + civicloc_len;

	new = kzalloc(माप(*new) + len, GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	pos = (u8 *)(new + 1);
	अगर (lci_len) अणु
		new->lci_len = lci_len;
		new->lci = pos;
		स_नकल(pos, lci, lci_len);
		pos += lci_len;
	पूर्ण

	अगर (civicloc_len) अणु
		new->civicloc_len = civicloc_len;
		new->civicloc = pos;
		स_नकल(pos, civicloc, civicloc_len);
		pos += civicloc_len;
	पूर्ण

	bss_conf->fपंचांगr_params = new;
	kमुक्त(old);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_assign_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
				   काष्ठा cfg80211_beacon_data *params,
				   स्थिर काष्ठा ieee80211_csa_settings *csa)
अणु
	काष्ठा beacon_data *new, *old;
	पूर्णांक new_head_len, new_tail_len;
	पूर्णांक size, err;
	u32 changed = BSS_CHANGED_BEACON;

	old = sdata_dereference(sdata->u.ap.beacon, sdata);


	/* Need to have a beacon head अगर we करोn't have one yet */
	अगर (!params->head && !old)
		वापस -EINVAL;

	/* new or old head? */
	अगर (params->head)
		new_head_len = params->head_len;
	अन्यथा
		new_head_len = old->head_len;

	/* new or old tail? */
	अगर (params->tail || !old)
		/* params->tail_len will be zero क्रम !params->tail */
		new_tail_len = params->tail_len;
	अन्यथा
		new_tail_len = old->tail_len;

	size = माप(*new) + new_head_len + new_tail_len;

	new = kzalloc(size, GFP_KERNEL);
	अगर (!new)
		वापस -ENOMEM;

	/* start filling the new info now */

	/*
	 * poपूर्णांकers go पूर्णांकo the block we allocated,
	 * memory is | beacon_data | head | tail |
	 */
	new->head = ((u8 *) new) + माप(*new);
	new->tail = new->head + new_head_len;
	new->head_len = new_head_len;
	new->tail_len = new_tail_len;

	अगर (csa) अणु
		new->cntdwn_current_counter = csa->count;
		स_नकल(new->cntdwn_counter_offsets, csa->counter_offsets_beacon,
		       csa->n_counter_offsets_beacon *
		       माप(new->cntdwn_counter_offsets[0]));
	पूर्ण

	/* copy in head */
	अगर (params->head)
		स_नकल(new->head, params->head, new_head_len);
	अन्यथा
		स_नकल(new->head, old->head, new_head_len);

	/* copy in optional tail */
	अगर (params->tail)
		स_नकल(new->tail, params->tail, new_tail_len);
	अन्यथा
		अगर (old)
			स_नकल(new->tail, old->tail, new_tail_len);

	err = ieee80211_set_probe_resp(sdata, params->probe_resp,
				       params->probe_resp_len, csa);
	अगर (err < 0) अणु
		kमुक्त(new);
		वापस err;
	पूर्ण
	अगर (err == 0)
		changed |= BSS_CHANGED_AP_PROBE_RESP;

	अगर (params->fपंचांग_responder != -1) अणु
		sdata->vअगर.bss_conf.fपंचांग_responder = params->fपंचांग_responder;
		err = ieee80211_set_fपंचांग_responder_params(sdata,
							 params->lci,
							 params->lci_len,
							 params->civicloc,
							 params->civicloc_len);

		अगर (err < 0) अणु
			kमुक्त(new);
			वापस err;
		पूर्ण

		changed |= BSS_CHANGED_FTM_RESPONDER;
	पूर्ण

	rcu_assign_poपूर्णांकer(sdata->u.ap.beacon, new);

	अगर (old)
		kमुक्त_rcu(old, rcu_head);

	वापस changed;
पूर्ण

अटल पूर्णांक ieee80211_start_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      काष्ठा cfg80211_ap_settings *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा beacon_data *old;
	काष्ठा ieee80211_sub_अगर_data *vlan;
	u32 changed = BSS_CHANGED_BEACON_INT |
		      BSS_CHANGED_BEACON_ENABLED |
		      BSS_CHANGED_BEACON |
		      BSS_CHANGED_SSID |
		      BSS_CHANGED_P2P_PS |
		      BSS_CHANGED_TXPOWER |
		      BSS_CHANGED_TWT;
	पूर्णांक i, err;
	पूर्णांक prev_beacon_पूर्णांक;

	old = sdata_dereference(sdata->u.ap.beacon, sdata);
	अगर (old)
		वापस -EALREADY;

	अगर (params->smps_mode != NL80211_SMPS_OFF)
		वापस -ENOTSUPP;

	sdata->smps_mode = IEEE80211_SMPS_OFF;

	sdata->needed_rx_chains = sdata->local->rx_chains;

	prev_beacon_पूर्णांक = sdata->vअगर.bss_conf.beacon_पूर्णांक;
	sdata->vअगर.bss_conf.beacon_पूर्णांक = params->beacon_पूर्णांकerval;

	अगर (params->he_cap && params->he_oper) अणु
		sdata->vअगर.bss_conf.he_support = true;
		sdata->vअगर.bss_conf.htc_trig_based_pkt_ext =
			le32_get_bits(params->he_oper->he_oper_params,
			      IEEE80211_HE_OPERATION_DFLT_PE_DURATION_MASK);
		sdata->vअगर.bss_conf.frame_समय_rts_th =
			le32_get_bits(params->he_oper->he_oper_params,
			      IEEE80211_HE_OPERATION_RTS_THRESHOLD_MASK);
		changed |= BSS_CHANGED_HE_OBSS_PD;

		अगर (params->he_bss_color.enabled)
			changed |= BSS_CHANGED_HE_BSS_COLOR;
	पूर्ण

	mutex_lock(&local->mtx);
	err = ieee80211_vअगर_use_channel(sdata, &params->chandef,
					IEEE80211_CHANCTX_SHARED);
	अगर (!err)
		ieee80211_vअगर_copy_chanctx_to_vlans(sdata, false);
	mutex_unlock(&local->mtx);
	अगर (err) अणु
		sdata->vअगर.bss_conf.beacon_पूर्णांक = prev_beacon_पूर्णांक;
		वापस err;
	पूर्ण

	/*
	 * Apply control port protocol, this allows us to
	 * not encrypt dynamic WEP control frames.
	 */
	sdata->control_port_protocol = params->crypto.control_port_ethertype;
	sdata->control_port_no_encrypt = params->crypto.control_port_no_encrypt;
	sdata->control_port_over_nl80211 =
				params->crypto.control_port_over_nl80211;
	sdata->control_port_no_preauth =
				params->crypto.control_port_no_preauth;
	sdata->encrypt_headroom = ieee80211_cs_headroom(sdata->local,
							&params->crypto,
							sdata->vअगर.type);

	list_क्रम_each_entry(vlan, &sdata->u.ap.vlans, u.vlan.list) अणु
		vlan->control_port_protocol =
			params->crypto.control_port_ethertype;
		vlan->control_port_no_encrypt =
			params->crypto.control_port_no_encrypt;
		vlan->control_port_over_nl80211 =
			params->crypto.control_port_over_nl80211;
		vlan->control_port_no_preauth =
			params->crypto.control_port_no_preauth;
		vlan->encrypt_headroom =
			ieee80211_cs_headroom(sdata->local,
					      &params->crypto,
					      vlan->vअगर.type);
	पूर्ण

	sdata->vअगर.bss_conf.dtim_period = params->dtim_period;
	sdata->vअगर.bss_conf.enable_beacon = true;
	sdata->vअगर.bss_conf.allow_p2p_go_ps = sdata->vअगर.p2p;
	sdata->vअगर.bss_conf.twt_responder = params->twt_responder;
	sdata->vअगर.bss_conf.he_obss_pd = params->he_obss_pd;
	sdata->vअगर.bss_conf.he_bss_color = params->he_bss_color;
	sdata->vअगर.bss_conf.s1g = params->chandef.chan->band ==
				  NL80211_BAND_S1GHZ;

	sdata->vअगर.bss_conf.ssid_len = params->ssid_len;
	अगर (params->ssid_len)
		स_नकल(sdata->vअगर.bss_conf.ssid, params->ssid,
		       params->ssid_len);
	sdata->vअगर.bss_conf.hidden_ssid =
		(params->hidden_ssid != NL80211_HIDDEN_SSID_NOT_IN_USE);

	स_रखो(&sdata->vअगर.bss_conf.p2p_noa_attr, 0,
	       माप(sdata->vअगर.bss_conf.p2p_noa_attr));
	sdata->vअगर.bss_conf.p2p_noa_attr.oppps_ctwinकरोw =
		params->p2p_ctwinकरोw & IEEE80211_P2P_OPPPS_CTWINDOW_MASK;
	अगर (params->p2p_opp_ps)
		sdata->vअगर.bss_conf.p2p_noa_attr.oppps_ctwinकरोw |=
					IEEE80211_P2P_OPPPS_ENABLE_BIT;

	sdata->beacon_rate_set = false;
	अगर (wiphy_ext_feature_isset(local->hw.wiphy,
				    NL80211_EXT_FEATURE_BEACON_RATE_LEGACY)) अणु
		क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
			sdata->beacon_rateidx_mask[i] =
				params->beacon_rate.control[i].legacy;
			अगर (sdata->beacon_rateidx_mask[i])
				sdata->beacon_rate_set = true;
		पूर्ण
	पूर्ण

	अगर (ieee80211_hw_check(&local->hw, HAS_RATE_CONTROL))
		sdata->vअगर.bss_conf.beacon_tx_rate = params->beacon_rate;

	err = ieee80211_assign_beacon(sdata, &params->beacon, शून्य);
	अगर (err < 0)
		जाओ error;
	changed |= err;

	अगर (params->fils_discovery.max_पूर्णांकerval) अणु
		err = ieee80211_set_fils_discovery(sdata,
						   &params->fils_discovery);
		अगर (err < 0)
			जाओ error;
		changed |= BSS_CHANGED_FILS_DISCOVERY;
	पूर्ण

	अगर (params->unsol_bcast_probe_resp.पूर्णांकerval) अणु
		err = ieee80211_set_unsol_bcast_probe_resp(sdata,
							   &params->unsol_bcast_probe_resp);
		अगर (err < 0)
			जाओ error;
		changed |= BSS_CHANGED_UNSOL_BCAST_PROBE_RESP;
	पूर्ण

	err = drv_start_ap(sdata->local, sdata);
	अगर (err) अणु
		old = sdata_dereference(sdata->u.ap.beacon, sdata);

		अगर (old)
			kमुक्त_rcu(old, rcu_head);
		RCU_INIT_POINTER(sdata->u.ap.beacon, शून्य);
		जाओ error;
	पूर्ण

	ieee80211_recalc_dtim(local, sdata);
	ieee80211_bss_info_change_notअगरy(sdata, changed);

	netअगर_carrier_on(dev);
	list_क्रम_each_entry(vlan, &sdata->u.ap.vlans, u.vlan.list)
		netअगर_carrier_on(vlan->dev);

	वापस 0;

error:
	ieee80211_vअगर_release_channel(sdata);
	वापस err;
पूर्ण

अटल पूर्णांक ieee80211_change_beacon(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				   काष्ठा cfg80211_beacon_data *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा beacon_data *old;
	पूर्णांक err;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	sdata_निश्चित_lock(sdata);

	/* करोn't allow changing the beacon जबतक CSA is in place - offset
	 * of channel चयन counter may change
	 */
	अगर (sdata->vअगर.csa_active)
		वापस -EBUSY;

	old = sdata_dereference(sdata->u.ap.beacon, sdata);
	अगर (!old)
		वापस -ENOENT;

	err = ieee80211_assign_beacon(sdata, params, शून्य);
	अगर (err < 0)
		वापस err;
	ieee80211_bss_info_change_notअगरy(sdata, err);
	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_stop_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_sub_अगर_data *vlan;
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा beacon_data *old_beacon;
	काष्ठा probe_resp *old_probe_resp;
	काष्ठा fils_discovery_data *old_fils_discovery;
	काष्ठा unsol_bcast_probe_resp_data *old_unsol_bcast_probe_resp;
	काष्ठा cfg80211_chan_def chandef;

	sdata_निश्चित_lock(sdata);

	old_beacon = sdata_dereference(sdata->u.ap.beacon, sdata);
	अगर (!old_beacon)
		वापस -ENOENT;
	old_probe_resp = sdata_dereference(sdata->u.ap.probe_resp, sdata);
	old_fils_discovery = sdata_dereference(sdata->u.ap.fils_discovery,
					       sdata);
	old_unsol_bcast_probe_resp =
		sdata_dereference(sdata->u.ap.unsol_bcast_probe_resp,
				  sdata);

	/* पात any running channel चयन */
	mutex_lock(&local->mtx);
	sdata->vअगर.csa_active = false;
	अगर (sdata->csa_block_tx) अणु
		ieee80211_wake_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
		sdata->csa_block_tx = false;
	पूर्ण

	mutex_unlock(&local->mtx);

	kमुक्त(sdata->u.ap.next_beacon);
	sdata->u.ap.next_beacon = शून्य;

	/* turn off carrier क्रम this पूर्णांकerface and dependent VLANs */
	list_क्रम_each_entry(vlan, &sdata->u.ap.vlans, u.vlan.list)
		netअगर_carrier_off(vlan->dev);
	netअगर_carrier_off(dev);

	/* हटाओ beacon and probe response */
	RCU_INIT_POINTER(sdata->u.ap.beacon, शून्य);
	RCU_INIT_POINTER(sdata->u.ap.probe_resp, शून्य);
	RCU_INIT_POINTER(sdata->u.ap.fils_discovery, शून्य);
	RCU_INIT_POINTER(sdata->u.ap.unsol_bcast_probe_resp, शून्य);
	kमुक्त_rcu(old_beacon, rcu_head);
	अगर (old_probe_resp)
		kमुक्त_rcu(old_probe_resp, rcu_head);
	अगर (old_fils_discovery)
		kमुक्त_rcu(old_fils_discovery, rcu_head);
	अगर (old_unsol_bcast_probe_resp)
		kमुक्त_rcu(old_unsol_bcast_probe_resp, rcu_head);

	kमुक्त(sdata->vअगर.bss_conf.fपंचांगr_params);
	sdata->vअगर.bss_conf.fपंचांगr_params = शून्य;

	__sta_info_flush(sdata, true);
	ieee80211_मुक्त_keys(sdata, true);

	sdata->vअगर.bss_conf.enable_beacon = false;
	sdata->beacon_rate_set = false;
	sdata->vअगर.bss_conf.ssid_len = 0;
	clear_bit(SDATA_STATE_OFFCHANNEL_BEACON_STOPPED, &sdata->state);
	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_BEACON_ENABLED);

	अगर (sdata->wdev.cac_started) अणु
		chandef = sdata->vअगर.bss_conf.chandef;
		cancel_delayed_work_sync(&sdata->dfs_cac_समयr_work);
		cfg80211_cac_event(sdata->dev, &chandef,
				   NL80211_RADAR_CAC_ABORTED,
				   GFP_KERNEL);
	पूर्ण

	drv_stop_ap(sdata->local, sdata);

	/* मुक्त all potentially still buffered bcast frames */
	local->total_ps_buffered -= skb_queue_len(&sdata->u.ap.ps.bc_buf);
	ieee80211_purge_tx_queue(&local->hw, &sdata->u.ap.ps.bc_buf);

	mutex_lock(&local->mtx);
	ieee80211_vअगर_copy_chanctx_to_vlans(sdata, true);
	ieee80211_vअगर_release_channel(sdata);
	mutex_unlock(&local->mtx);

	वापस 0;
पूर्ण

अटल पूर्णांक sta_apply_auth_flags(काष्ठा ieee80211_local *local,
				काष्ठा sta_info *sta,
				u32 mask, u32 set)
अणु
	पूर्णांक ret;

	अगर (mask & BIT(NL80211_STA_FLAG_AUTHENTICATED) &&
	    set & BIT(NL80211_STA_FLAG_AUTHENTICATED) &&
	    !test_sta_flag(sta, WLAN_STA_AUTH)) अणु
		ret = sta_info_move_state(sta, IEEE80211_STA_AUTH);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (mask & BIT(NL80211_STA_FLAG_ASSOCIATED) &&
	    set & BIT(NL80211_STA_FLAG_ASSOCIATED) &&
	    !test_sta_flag(sta, WLAN_STA_ASSOC)) अणु
		/*
		 * When peer becomes associated, init rate control as
		 * well. Some drivers require rate control initialized
		 * beक्रमe drv_sta_state() is called.
		 */
		अगर (!test_sta_flag(sta, WLAN_STA_RATE_CONTROL))
			rate_control_rate_init(sta);

		ret = sta_info_move_state(sta, IEEE80211_STA_ASSOC);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (mask & BIT(NL80211_STA_FLAG_AUTHORIZED)) अणु
		अगर (set & BIT(NL80211_STA_FLAG_AUTHORIZED))
			ret = sta_info_move_state(sta, IEEE80211_STA_AUTHORIZED);
		अन्यथा अगर (test_sta_flag(sta, WLAN_STA_AUTHORIZED))
			ret = sta_info_move_state(sta, IEEE80211_STA_ASSOC);
		अन्यथा
			ret = 0;
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (mask & BIT(NL80211_STA_FLAG_ASSOCIATED) &&
	    !(set & BIT(NL80211_STA_FLAG_ASSOCIATED)) &&
	    test_sta_flag(sta, WLAN_STA_ASSOC)) अणु
		ret = sta_info_move_state(sta, IEEE80211_STA_AUTH);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (mask & BIT(NL80211_STA_FLAG_AUTHENTICATED) &&
	    !(set & BIT(NL80211_STA_FLAG_AUTHENTICATED)) &&
	    test_sta_flag(sta, WLAN_STA_AUTH)) अणु
		ret = sta_info_move_state(sta, IEEE80211_STA_NONE);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम sta_apply_mesh_params(काष्ठा ieee80211_local *local,
				  काष्ठा sta_info *sta,
				  काष्ठा station_parameters *params)
अणु
#अगर_घोषित CONFIG_MAC80211_MESH
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u32 changed = 0;

	अगर (params->sta_modअगरy_mask & STATION_PARAM_APPLY_PLINK_STATE) अणु
		चयन (params->plink_state) अणु
		हाल NL80211_PLINK_ESTAB:
			अगर (sta->mesh->plink_state != NL80211_PLINK_ESTAB)
				changed = mesh_plink_inc_estab_count(sdata);
			sta->mesh->plink_state = params->plink_state;
			sta->mesh->aid = params->peer_aid;

			ieee80211_mps_sta_status_update(sta);
			changed |= ieee80211_mps_set_sta_local_pm(sta,
				      sdata->u.mesh.mshcfg.घातer_mode);

			ewma_mesh_tx_rate_avg_init(&sta->mesh->tx_rate_avg);
			/* init at low value */
			ewma_mesh_tx_rate_avg_add(&sta->mesh->tx_rate_avg, 10);

			अवरोध;
		हाल NL80211_PLINK_LISTEN:
		हाल NL80211_PLINK_BLOCKED:
		हाल NL80211_PLINK_OPN_SNT:
		हाल NL80211_PLINK_OPN_RCVD:
		हाल NL80211_PLINK_CNF_RCVD:
		हाल NL80211_PLINK_HOLDING:
			अगर (sta->mesh->plink_state == NL80211_PLINK_ESTAB)
				changed = mesh_plink_dec_estab_count(sdata);
			sta->mesh->plink_state = params->plink_state;

			ieee80211_mps_sta_status_update(sta);
			changed |= ieee80211_mps_set_sta_local_pm(sta,
					NL80211_MESH_POWER_UNKNOWN);
			अवरोध;
		शेष:
			/*  nothing  */
			अवरोध;
		पूर्ण
	पूर्ण

	चयन (params->plink_action) अणु
	हाल NL80211_PLINK_ACTION_NO_ACTION:
		/* nothing */
		अवरोध;
	हाल NL80211_PLINK_ACTION_OPEN:
		changed |= mesh_plink_खोलो(sta);
		अवरोध;
	हाल NL80211_PLINK_ACTION_BLOCK:
		changed |= mesh_plink_block(sta);
		अवरोध;
	पूर्ण

	अगर (params->local_pm)
		changed |= ieee80211_mps_set_sta_local_pm(sta,
							  params->local_pm);

	ieee80211_mbss_info_change_notअगरy(sdata, changed);
#पूर्ण_अगर
पूर्ण

अटल पूर्णांक sta_apply_parameters(काष्ठा ieee80211_local *local,
				काष्ठा sta_info *sta,
				काष्ठा station_parameters *params)
अणु
	पूर्णांक ret = 0;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_sub_अगर_data *sdata = sta->sdata;
	u32 mask, set;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस -EINVAL;

	mask = params->sta_flags_mask;
	set = params->sta_flags_set;

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर)) अणु
		/*
		 * In mesh mode, ASSOCIATED isn't part of the nl80211
		 * API but must follow AUTHENTICATED क्रम driver state.
		 */
		अगर (mask & BIT(NL80211_STA_FLAG_AUTHENTICATED))
			mask |= BIT(NL80211_STA_FLAG_ASSOCIATED);
		अगर (set & BIT(NL80211_STA_FLAG_AUTHENTICATED))
			set |= BIT(NL80211_STA_FLAG_ASSOCIATED);
	पूर्ण अन्यथा अगर (test_sta_flag(sta, WLAN_STA_TDLS_PEER)) अणु
		/*
		 * TDLS -- everything follows authorized, but
		 * only becoming authorized is possible, not
		 * going back
		 */
		अगर (set & BIT(NL80211_STA_FLAG_AUTHORIZED)) अणु
			set |= BIT(NL80211_STA_FLAG_AUTHENTICATED) |
			       BIT(NL80211_STA_FLAG_ASSOCIATED);
			mask |= BIT(NL80211_STA_FLAG_AUTHENTICATED) |
				BIT(NL80211_STA_FLAG_ASSOCIATED);
		पूर्ण
	पूर्ण

	अगर (mask & BIT(NL80211_STA_FLAG_WME) &&
	    local->hw.queues >= IEEE80211_NUM_ACS)
		sta->sta.wme = set & BIT(NL80211_STA_FLAG_WME);

	/* auth flags will be set later क्रम TDLS,
	 * and क्रम unassociated stations that move to associated */
	अगर (!test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    !((mask & BIT(NL80211_STA_FLAG_ASSOCIATED)) &&
	      (set & BIT(NL80211_STA_FLAG_ASSOCIATED)))) अणु
		ret = sta_apply_auth_flags(local, sta, mask, set);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (mask & BIT(NL80211_STA_FLAG_SHORT_PREAMBLE)) अणु
		अगर (set & BIT(NL80211_STA_FLAG_SHORT_PREAMBLE))
			set_sta_flag(sta, WLAN_STA_SHORT_PREAMBLE);
		अन्यथा
			clear_sta_flag(sta, WLAN_STA_SHORT_PREAMBLE);
	पूर्ण

	अगर (mask & BIT(NL80211_STA_FLAG_MFP)) अणु
		sta->sta.mfp = !!(set & BIT(NL80211_STA_FLAG_MFP));
		अगर (set & BIT(NL80211_STA_FLAG_MFP))
			set_sta_flag(sta, WLAN_STA_MFP);
		अन्यथा
			clear_sta_flag(sta, WLAN_STA_MFP);
	पूर्ण

	अगर (mask & BIT(NL80211_STA_FLAG_TDLS_PEER)) अणु
		अगर (set & BIT(NL80211_STA_FLAG_TDLS_PEER))
			set_sta_flag(sta, WLAN_STA_TDLS_PEER);
		अन्यथा
			clear_sta_flag(sta, WLAN_STA_TDLS_PEER);
	पूर्ण

	/* mark TDLS channel चयन support, अगर the AP allows it */
	अगर (test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    !sdata->u.mgd.tdls_chan_चयन_prohibited &&
	    params->ext_capab_len >= 4 &&
	    params->ext_capab[3] & WLAN_EXT_CAPA4_TDLS_CHAN_SWITCH)
		set_sta_flag(sta, WLAN_STA_TDLS_CHAN_SWITCH);

	अगर (test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    !sdata->u.mgd.tdls_wider_bw_prohibited &&
	    ieee80211_hw_check(&local->hw, TDLS_WIDER_BW) &&
	    params->ext_capab_len >= 8 &&
	    params->ext_capab[7] & WLAN_EXT_CAPA8_TDLS_WIDE_BW_ENABLED)
		set_sta_flag(sta, WLAN_STA_TDLS_WIDER_BW);

	अगर (params->sta_modअगरy_mask & STATION_PARAM_APPLY_UAPSD) अणु
		sta->sta.uapsd_queues = params->uapsd_queues;
		sta->sta.max_sp = params->max_sp;
	पूर्ण

	/* The sender might not have sent the last bit, consider it to be 0 */
	अगर (params->ext_capab_len >= 8) अणु
		u8 val = (params->ext_capab[7] &
			  WLAN_EXT_CAPA8_MAX_MSDU_IN_AMSDU_LSB) >> 7;

		/* we did get all the bits, take the MSB as well */
		अगर (params->ext_capab_len >= 9) अणु
			u8 val_msb = params->ext_capab[8] &
				WLAN_EXT_CAPA9_MAX_MSDU_IN_AMSDU_MSB;
			val_msb <<= 1;
			val |= val_msb;
		पूर्ण

		चयन (val) अणु
		हाल 1:
			sta->sta.max_amsdu_subframes = 32;
			अवरोध;
		हाल 2:
			sta->sta.max_amsdu_subframes = 16;
			अवरोध;
		हाल 3:
			sta->sta.max_amsdu_subframes = 8;
			अवरोध;
		शेष:
			sta->sta.max_amsdu_subframes = 0;
		पूर्ण
	पूर्ण

	/*
	 * cfg80211 validates this (1-2007) and allows setting the AID
	 * only when creating a new station entry
	 */
	अगर (params->aid)
		sta->sta.aid = params->aid;

	/*
	 * Some of the following updates would be racy अगर called on an
	 * existing station, via ieee80211_change_station(). However,
	 * all such changes are rejected by cfg80211 except क्रम updates
	 * changing the supported rates on an existing but not yet used
	 * TDLS peer.
	 */

	अगर (params->listen_पूर्णांकerval >= 0)
		sta->listen_पूर्णांकerval = params->listen_पूर्णांकerval;

	अगर (params->sta_modअगरy_mask & STATION_PARAM_APPLY_STA_TXPOWER) अणु
		sta->sta.txpwr.type = params->txpwr.type;
		अगर (params->txpwr.type == NL80211_TX_POWER_LIMITED)
			sta->sta.txpwr.घातer = params->txpwr.घातer;
		ret = drv_sta_set_txpwr(local, sdata, sta);
		अगर (ret)
			वापस ret;
	पूर्ण

	अगर (params->supported_rates && params->supported_rates_len) अणु
		ieee80211_parse_bitrates(&sdata->vअगर.bss_conf.chandef,
					 sband, params->supported_rates,
					 params->supported_rates_len,
					 &sta->sta.supp_rates[sband->band]);
	पूर्ण

	अगर (params->ht_capa)
		ieee80211_ht_cap_ie_to_sta_ht_cap(sdata, sband,
						  params->ht_capa, sta);

	/* VHT can override some HT caps such as the A-MSDU max length */
	अगर (params->vht_capa)
		ieee80211_vht_cap_ie_to_sta_vht_cap(sdata, sband,
						    params->vht_capa, sta);

	अगर (params->he_capa)
		ieee80211_he_cap_ie_to_sta_he_cap(sdata, sband,
						  (व्योम *)params->he_capa,
						  params->he_capa_len,
						  (व्योम *)params->he_6ghz_capa,
						  sta);

	अगर (params->opmode_notअगर_used) अणु
		/* वापसed value is only needed क्रम rc update, but the
		 * rc isn't initialized here yet, so ignore it
		 */
		__ieee80211_vht_handle_opmode(sdata, sta, params->opmode_notअगर,
					      sband->band);
	पूर्ण

	अगर (params->support_p2p_ps >= 0)
		sta->sta.support_p2p_ps = params->support_p2p_ps;

	अगर (ieee80211_vअगर_is_mesh(&sdata->vअगर))
		sta_apply_mesh_params(local, sta, params);

	अगर (params->airसमय_weight)
		sta->airसमय_weight = params->airसमय_weight;

	/* set the STA state after all sta info from usermode has been set */
	अगर (test_sta_flag(sta, WLAN_STA_TDLS_PEER) ||
	    set & BIT(NL80211_STA_FLAG_ASSOCIATED)) अणु
		ret = sta_apply_auth_flags(local, sta, mask, set);
		अगर (ret)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_add_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 स्थिर u8 *mac,
				 काष्ठा station_parameters *params)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक err;

	अगर (params->vlan) अणु
		sdata = IEEE80211_DEV_TO_SUB_IF(params->vlan);

		अगर (sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN &&
		    sdata->vअगर.type != NL80211_IFTYPE_AP)
			वापस -EINVAL;
	पूर्ण अन्यथा
		sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	अगर (ether_addr_equal(mac, sdata->vअगर.addr))
		वापस -EINVAL;

	अगर (!is_valid_ether_addr(mac))
		वापस -EINVAL;

	अगर (params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER) &&
	    sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    !sdata->u.mgd.associated)
		वापस -EINVAL;

	sta = sta_info_alloc(sdata, mac, GFP_KERNEL);
	अगर (!sta)
		वापस -ENOMEM;

	अगर (params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER))
		sta->sta.tdls = true;

	err = sta_apply_parameters(local, sta, params);
	अगर (err) अणु
		sta_info_मुक्त(local, sta);
		वापस err;
	पूर्ण

	/*
	 * क्रम TDLS and क्रम unassociated station, rate control should be
	 * initialized only when rates are known and station is marked
	 * authorized/associated
	 */
	अगर (!test_sta_flag(sta, WLAN_STA_TDLS_PEER) &&
	    test_sta_flag(sta, WLAN_STA_ASSOC))
		rate_control_rate_init(sta);

	err = sta_info_insert_rcu(sta);
	अगर (err) अणु
		rcu_पढ़ो_unlock();
		वापस err;
	पूर्ण

	rcu_पढ़ो_unlock();

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_del_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				 काष्ठा station_del_parameters *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	अगर (params->mac)
		वापस sta_info_destroy_addr_bss(sdata, params->mac);

	sta_info_flush(sdata);
	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_change_station(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *dev, स्थिर u8 *mac,
				    काष्ठा station_parameters *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_sub_अगर_data *vlansdata;
	क्रमागत cfg80211_station_type statype;
	पूर्णांक err;

	mutex_lock(&local->sta_mtx);

	sta = sta_info_get_bss(sdata, mac);
	अगर (!sta) अणु
		err = -ENOENT;
		जाओ out_err;
	पूर्ण

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (sdata->u.mesh.user_mpm)
			statype = CFG80211_STA_MESH_PEER_USER;
		अन्यथा
			statype = CFG80211_STA_MESH_PEER_KERNEL;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		statype = CFG80211_STA_IBSS;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (!test_sta_flag(sta, WLAN_STA_TDLS_PEER)) अणु
			statype = CFG80211_STA_AP_STA;
			अवरोध;
		पूर्ण
		अगर (test_sta_flag(sta, WLAN_STA_AUTHORIZED))
			statype = CFG80211_STA_TDLS_PEER_ACTIVE;
		अन्यथा
			statype = CFG80211_STA_TDLS_PEER_SETUP;
		अवरोध;
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
		अगर (test_sta_flag(sta, WLAN_STA_ASSOC))
			statype = CFG80211_STA_AP_CLIENT;
		अन्यथा
			statype = CFG80211_STA_AP_CLIENT_UNASSOC;
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण

	err = cfg80211_check_station_change(wiphy, params, statype);
	अगर (err)
		जाओ out_err;

	अगर (params->vlan && params->vlan != sta->sdata->dev) अणु
		vlansdata = IEEE80211_DEV_TO_SUB_IF(params->vlan);

		अगर (params->vlan->ieee80211_ptr->use_4addr) अणु
			अगर (vlansdata->u.vlan.sta) अणु
				err = -EBUSY;
				जाओ out_err;
			पूर्ण

			rcu_assign_poपूर्णांकer(vlansdata->u.vlan.sta, sta);
			__ieee80211_check_fast_rx_अगरace(vlansdata);
			drv_sta_set_4addr(local, sta->sdata, &sta->sta, true);
		पूर्ण

		अगर (sta->sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN &&
		    sta->sdata->u.vlan.sta) अणु
			ieee80211_clear_fast_rx(sta);
			RCU_INIT_POINTER(sta->sdata->u.vlan.sta, शून्य);
		पूर्ण

		अगर (test_sta_flag(sta, WLAN_STA_AUTHORIZED))
			ieee80211_vअगर_dec_num_mcast(sta->sdata);

		sta->sdata = vlansdata;
		ieee80211_check_fast_xmit(sta);

		अगर (test_sta_flag(sta, WLAN_STA_AUTHORIZED)) अणु
			ieee80211_vअगर_inc_num_mcast(sta->sdata);
			cfg80211_send_layer2_update(sta->sdata->dev,
						    sta->sta.addr);
		पूर्ण
	पूर्ण

	err = sta_apply_parameters(local, sta, params);
	अगर (err)
		जाओ out_err;

	mutex_unlock(&local->sta_mtx);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    params->sta_flags_mask & BIT(NL80211_STA_FLAG_AUTHORIZED)) अणु
		ieee80211_recalc_ps(local);
		ieee80211_recalc_ps_vअगर(sdata);
	पूर्ण

	वापस 0;
out_err:
	mutex_unlock(&local->sta_mtx);
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_MAC80211_MESH
अटल पूर्णांक ieee80211_add_mpath(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर u8 *dst, स्थिर u8 *next_hop)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा mesh_path *mpath;
	काष्ठा sta_info *sta;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	rcu_पढ़ो_lock();
	sta = sta_info_get(sdata, next_hop);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	mpath = mesh_path_add(sdata, dst);
	अगर (IS_ERR(mpath)) अणु
		rcu_पढ़ो_unlock();
		वापस PTR_ERR(mpath);
	पूर्ण

	mesh_path_fix_nexthop(mpath, sta);

	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_del_mpath(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर u8 *dst)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	अगर (dst)
		वापस mesh_path_del(sdata, dst);

	mesh_path_flush_by_अगरace(sdata);
	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_change_mpath(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  स्थिर u8 *dst, स्थिर u8 *next_hop)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा mesh_path *mpath;
	काष्ठा sta_info *sta;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	rcu_पढ़ो_lock();

	sta = sta_info_get(sdata, next_hop);
	अगर (!sta) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	mpath = mesh_path_lookup(sdata, dst);
	अगर (!mpath) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण

	mesh_path_fix_nexthop(mpath, sta);

	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल व्योम mpath_set_pinfo(काष्ठा mesh_path *mpath, u8 *next_hop,
			    काष्ठा mpath_info *pinfo)
अणु
	काष्ठा sta_info *next_hop_sta = rcu_dereference(mpath->next_hop);

	अगर (next_hop_sta)
		स_नकल(next_hop, next_hop_sta->sta.addr, ETH_ALEN);
	अन्यथा
		eth_zero_addr(next_hop);

	स_रखो(pinfo, 0, माप(*pinfo));

	pinfo->generation = mpath->sdata->u.mesh.mesh_paths_generation;

	pinfo->filled = MPATH_INFO_FRAME_QLEN |
			MPATH_INFO_SN |
			MPATH_INFO_METRIC |
			MPATH_INFO_EXPTIME |
			MPATH_INFO_DISCOVERY_TIMEOUT |
			MPATH_INFO_DISCOVERY_RETRIES |
			MPATH_INFO_FLAGS |
			MPATH_INFO_HOP_COUNT |
			MPATH_INFO_PATH_CHANGE;

	pinfo->frame_qlen = mpath->frame_queue.qlen;
	pinfo->sn = mpath->sn;
	pinfo->metric = mpath->metric;
	अगर (समय_beक्रमe(jअगरfies, mpath->exp_समय))
		pinfo->expसमय = jअगरfies_to_msecs(mpath->exp_समय - jअगरfies);
	pinfo->discovery_समयout =
			jअगरfies_to_msecs(mpath->discovery_समयout);
	pinfo->discovery_retries = mpath->discovery_retries;
	अगर (mpath->flags & MESH_PATH_ACTIVE)
		pinfo->flags |= NL80211_MPATH_FLAG_ACTIVE;
	अगर (mpath->flags & MESH_PATH_RESOLVING)
		pinfo->flags |= NL80211_MPATH_FLAG_RESOLVING;
	अगर (mpath->flags & MESH_PATH_SN_VALID)
		pinfo->flags |= NL80211_MPATH_FLAG_SN_VALID;
	अगर (mpath->flags & MESH_PATH_FIXED)
		pinfo->flags |= NL80211_MPATH_FLAG_FIXED;
	अगर (mpath->flags & MESH_PATH_RESOLVED)
		pinfo->flags |= NL80211_MPATH_FLAG_RESOLVED;
	pinfo->hop_count = mpath->hop_count;
	pinfo->path_change_count = mpath->path_change_count;
पूर्ण

अटल पूर्णांक ieee80211_get_mpath(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       u8 *dst, u8 *next_hop, काष्ठा mpath_info *pinfo)

अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा mesh_path *mpath;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	rcu_पढ़ो_lock();
	mpath = mesh_path_lookup(sdata, dst);
	अगर (!mpath) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण
	स_नकल(dst, mpath->dst, ETH_ALEN);
	mpath_set_pinfo(mpath, next_hop, pinfo);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_dump_mpath(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				पूर्णांक idx, u8 *dst, u8 *next_hop,
				काष्ठा mpath_info *pinfo)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा mesh_path *mpath;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	rcu_पढ़ो_lock();
	mpath = mesh_path_lookup_by_idx(sdata, idx);
	अगर (!mpath) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण
	स_नकल(dst, mpath->dst, ETH_ALEN);
	mpath_set_pinfo(mpath, next_hop, pinfo);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल व्योम mpp_set_pinfo(काष्ठा mesh_path *mpath, u8 *mpp,
			  काष्ठा mpath_info *pinfo)
अणु
	स_रखो(pinfo, 0, माप(*pinfo));
	स_नकल(mpp, mpath->mpp, ETH_ALEN);

	pinfo->generation = mpath->sdata->u.mesh.mpp_paths_generation;
पूर्ण

अटल पूर्णांक ieee80211_get_mpp(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u8 *dst, u8 *mpp, काष्ठा mpath_info *pinfo)

अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा mesh_path *mpath;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	rcu_पढ़ो_lock();
	mpath = mpp_path_lookup(sdata, dst);
	अगर (!mpath) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण
	स_नकल(dst, mpath->dst, ETH_ALEN);
	mpp_set_pinfo(mpath, mpp, pinfo);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_dump_mpp(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      पूर्णांक idx, u8 *dst, u8 *mpp,
			      काष्ठा mpath_info *pinfo)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा mesh_path *mpath;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	rcu_पढ़ो_lock();
	mpath = mpp_path_lookup_by_idx(sdata, idx);
	अगर (!mpath) अणु
		rcu_पढ़ो_unlock();
		वापस -ENOENT;
	पूर्ण
	स_नकल(dst, mpath->dst, ETH_ALEN);
	mpp_set_pinfo(mpath, mpp, pinfo);
	rcu_पढ़ो_unlock();
	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_get_mesh_config(काष्ठा wiphy *wiphy,
				काष्ठा net_device *dev,
				काष्ठा mesh_config *conf)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	स_नकल(conf, &(sdata->u.mesh.mshcfg), माप(काष्ठा mesh_config));
	वापस 0;
पूर्ण

अटल अंतरभूत bool _chg_mesh_attr(क्रमागत nl80211_meshconf_params parm, u32 mask)
अणु
	वापस (mask >> (parm-1)) & 0x1;
पूर्ण

अटल पूर्णांक copy_mesh_setup(काष्ठा ieee80211_अगर_mesh *अगरmsh,
		स्थिर काष्ठा mesh_setup *setup)
अणु
	u8 *new_ie;
	स्थिर u8 *old_ie;
	काष्ठा ieee80211_sub_अगर_data *sdata = container_of(अगरmsh,
					काष्ठा ieee80211_sub_अगर_data, u.mesh);
	पूर्णांक i;

	/* allocate inक्रमmation elements */
	new_ie = शून्य;
	old_ie = अगरmsh->ie;

	अगर (setup->ie_len) अणु
		new_ie = kmemdup(setup->ie, setup->ie_len,
				GFP_KERNEL);
		अगर (!new_ie)
			वापस -ENOMEM;
	पूर्ण
	अगरmsh->ie_len = setup->ie_len;
	अगरmsh->ie = new_ie;
	kमुक्त(old_ie);

	/* now copy the rest of the setup parameters */
	अगरmsh->mesh_id_len = setup->mesh_id_len;
	स_नकल(अगरmsh->mesh_id, setup->mesh_id, अगरmsh->mesh_id_len);
	अगरmsh->mesh_sp_id = setup->sync_method;
	अगरmsh->mesh_pp_id = setup->path_sel_proto;
	अगरmsh->mesh_pm_id = setup->path_metric;
	अगरmsh->user_mpm = setup->user_mpm;
	अगरmsh->mesh_auth_id = setup->auth_id;
	अगरmsh->security = IEEE80211_MESH_SEC_NONE;
	अगरmsh->userspace_handles_dfs = setup->userspace_handles_dfs;
	अगर (setup->is_authenticated)
		अगरmsh->security |= IEEE80211_MESH_SEC_AUTHED;
	अगर (setup->is_secure)
		अगरmsh->security |= IEEE80211_MESH_SEC_SECURED;

	/* mcast rate setting in Mesh Node */
	स_नकल(sdata->vअगर.bss_conf.mcast_rate, setup->mcast_rate,
						माप(setup->mcast_rate));
	sdata->vअगर.bss_conf.basic_rates = setup->basic_rates;

	sdata->vअगर.bss_conf.beacon_पूर्णांक = setup->beacon_पूर्णांकerval;
	sdata->vअगर.bss_conf.dtim_period = setup->dtim_period;

	sdata->beacon_rate_set = false;
	अगर (wiphy_ext_feature_isset(sdata->local->hw.wiphy,
				    NL80211_EXT_FEATURE_BEACON_RATE_LEGACY)) अणु
		क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
			sdata->beacon_rateidx_mask[i] =
				setup->beacon_rate.control[i].legacy;
			अगर (sdata->beacon_rateidx_mask[i])
				sdata->beacon_rate_set = true;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_update_mesh_config(काष्ठा wiphy *wiphy,
					काष्ठा net_device *dev, u32 mask,
					स्थिर काष्ठा mesh_config *nconf)
अणु
	काष्ठा mesh_config *conf;
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा ieee80211_अगर_mesh *अगरmsh;

	sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	अगरmsh = &sdata->u.mesh;

	/* Set the config options which we are पूर्णांकerested in setting */
	conf = &(sdata->u.mesh.mshcfg);
	अगर (_chg_mesh_attr(NL80211_MESHCONF_RETRY_TIMEOUT, mask))
		conf->करोt11MeshRetryTimeout = nconf->करोt11MeshRetryTimeout;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_CONFIRM_TIMEOUT, mask))
		conf->करोt11MeshConfirmTimeout = nconf->करोt11MeshConfirmTimeout;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HOLDING_TIMEOUT, mask))
		conf->करोt11MeshHoldingTimeout = nconf->करोt11MeshHoldingTimeout;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_MAX_PEER_LINKS, mask))
		conf->करोt11MeshMaxPeerLinks = nconf->करोt11MeshMaxPeerLinks;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_MAX_RETRIES, mask))
		conf->करोt11MeshMaxRetries = nconf->करोt11MeshMaxRetries;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_TTL, mask))
		conf->करोt11MeshTTL = nconf->करोt11MeshTTL;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_ELEMENT_TTL, mask))
		conf->element_ttl = nconf->element_ttl;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_AUTO_OPEN_PLINKS, mask)) अणु
		अगर (अगरmsh->user_mpm)
			वापस -EBUSY;
		conf->स्वतः_खोलो_plinks = nconf->स्वतः_खोलो_plinks;
	पूर्ण
	अगर (_chg_mesh_attr(NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR, mask))
		conf->करोt11MeshNbrOffsetMaxNeighbor =
			nconf->करोt11MeshNbrOffsetMaxNeighbor;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES, mask))
		conf->करोt11MeshHWMPmaxPREQretries =
			nconf->करोt11MeshHWMPmaxPREQretries;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_PATH_REFRESH_TIME, mask))
		conf->path_refresh_समय = nconf->path_refresh_समय;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT, mask))
		conf->min_discovery_समयout = nconf->min_discovery_समयout;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT, mask))
		conf->करोt11MeshHWMPactivePathTimeout =
			nconf->करोt11MeshHWMPactivePathTimeout;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL, mask))
		conf->करोt11MeshHWMPpreqMinInterval =
			nconf->करोt11MeshHWMPpreqMinInterval;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL, mask))
		conf->करोt11MeshHWMPperrMinInterval =
			nconf->करोt11MeshHWMPperrMinInterval;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME,
			   mask))
		conf->करोt11MeshHWMPnetDiameterTraversalTime =
			nconf->करोt11MeshHWMPnetDiameterTraversalTime;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_ROOTMODE, mask)) अणु
		conf->करोt11MeshHWMPRootMode = nconf->करोt11MeshHWMPRootMode;
		ieee80211_mesh_root_setup(अगरmsh);
	पूर्ण
	अगर (_chg_mesh_attr(NL80211_MESHCONF_GATE_ANNOUNCEMENTS, mask)) अणु
		/* our current gate announcement implementation rides on root
		 * announcements, so require this अगरmsh to also be a root node
		 * */
		अगर (nconf->करोt11MeshGateAnnouncementProtocol &&
		    !(conf->करोt11MeshHWMPRootMode > IEEE80211_ROOTMODE_ROOT)) अणु
			conf->करोt11MeshHWMPRootMode = IEEE80211_PROACTIVE_RANN;
			ieee80211_mesh_root_setup(अगरmsh);
		पूर्ण
		conf->करोt11MeshGateAnnouncementProtocol =
			nconf->करोt11MeshGateAnnouncementProtocol;
	पूर्ण
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_RANN_INTERVAL, mask))
		conf->करोt11MeshHWMPRannInterval =
			nconf->करोt11MeshHWMPRannInterval;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_FORWARDING, mask))
		conf->करोt11MeshForwarding = nconf->करोt11MeshForwarding;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_RSSI_THRESHOLD, mask)) अणु
		/* our RSSI threshold implementation is supported only क्रम
		 * devices that report संकेत in dBm.
		 */
		अगर (!ieee80211_hw_check(&sdata->local->hw, SIGNAL_DBM))
			वापस -ENOTSUPP;
		conf->rssi_threshold = nconf->rssi_threshold;
	पूर्ण
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HT_OPMODE, mask)) अणु
		conf->ht_opmode = nconf->ht_opmode;
		sdata->vअगर.bss_conf.ht_operation_mode = nconf->ht_opmode;
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_HT);
	पूर्ण
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT, mask))
		conf->करोt11MeshHWMPactivePathToRootTimeout =
			nconf->करोt11MeshHWMPactivePathToRootTimeout;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_ROOT_INTERVAL, mask))
		conf->करोt11MeshHWMProotInterval =
			nconf->करोt11MeshHWMProotInterval;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL, mask))
		conf->करोt11MeshHWMPconfirmationInterval =
			nconf->करोt11MeshHWMPconfirmationInterval;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_POWER_MODE, mask)) अणु
		conf->घातer_mode = nconf->घातer_mode;
		ieee80211_mps_local_status_update(sdata);
	पूर्ण
	अगर (_chg_mesh_attr(NL80211_MESHCONF_AWAKE_WINDOW, mask))
		conf->करोt11MeshAwakeWinकरोwDuration =
			nconf->करोt11MeshAwakeWinकरोwDuration;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_PLINK_TIMEOUT, mask))
		conf->plink_समयout = nconf->plink_समयout;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_CONNECTED_TO_GATE, mask))
		conf->करोt11MeshConnectedToMeshGate =
			nconf->करोt11MeshConnectedToMeshGate;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_NOLEARN, mask))
		conf->करोt11MeshNolearn = nconf->करोt11MeshNolearn;
	अगर (_chg_mesh_attr(NL80211_MESHCONF_CONNECTED_TO_AS, mask))
		conf->करोt11MeshConnectedToAuthServer =
			nconf->करोt11MeshConnectedToAuthServer;
	ieee80211_mbss_info_change_notअगरy(sdata, BSS_CHANGED_BEACON);
	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_join_mesh(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       स्थिर काष्ठा mesh_config *conf,
			       स्थिर काष्ठा mesh_setup *setup)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;
	पूर्णांक err;

	स_नकल(&अगरmsh->mshcfg, conf, माप(काष्ठा mesh_config));
	err = copy_mesh_setup(अगरmsh, setup);
	अगर (err)
		वापस err;

	sdata->control_port_over_nl80211 = setup->control_port_over_nl80211;

	/* can mesh use other SMPS modes? */
	sdata->smps_mode = IEEE80211_SMPS_OFF;
	sdata->needed_rx_chains = sdata->local->rx_chains;

	mutex_lock(&sdata->local->mtx);
	err = ieee80211_vअगर_use_channel(sdata, &setup->chandef,
					IEEE80211_CHANCTX_SHARED);
	mutex_unlock(&sdata->local->mtx);
	अगर (err)
		वापस err;

	वापस ieee80211_start_mesh(sdata);
पूर्ण

अटल पूर्णांक ieee80211_leave_mesh(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	ieee80211_stop_mesh(sdata);
	mutex_lock(&sdata->local->mtx);
	ieee80211_vअगर_release_channel(sdata);
	kमुक्त(sdata->u.mesh.ie);
	mutex_unlock(&sdata->local->mtx);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ieee80211_change_bss(काष्ठा wiphy *wiphy,
				काष्ठा net_device *dev,
				काष्ठा bss_parameters *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_supported_band *sband;
	u32 changed = 0;

	अगर (!sdata_dereference(sdata->u.ap.beacon, sdata))
		वापस -ENOENT;

	sband = ieee80211_get_sband(sdata);
	अगर (!sband)
		वापस -EINVAL;

	अगर (params->use_cts_prot >= 0) अणु
		sdata->vअगर.bss_conf.use_cts_prot = params->use_cts_prot;
		changed |= BSS_CHANGED_ERP_CTS_PROT;
	पूर्ण
	अगर (params->use_लघु_preamble >= 0) अणु
		sdata->vअगर.bss_conf.use_लघु_preamble =
			params->use_लघु_preamble;
		changed |= BSS_CHANGED_ERP_PREAMBLE;
	पूर्ण

	अगर (!sdata->vअगर.bss_conf.use_लघु_slot &&
	    (sband->band == NL80211_BAND_5GHZ ||
	     sband->band == NL80211_BAND_6GHZ)) अणु
		sdata->vअगर.bss_conf.use_लघु_slot = true;
		changed |= BSS_CHANGED_ERP_SLOT;
	पूर्ण

	अगर (params->use_लघु_slot_समय >= 0) अणु
		sdata->vअगर.bss_conf.use_लघु_slot =
			params->use_लघु_slot_समय;
		changed |= BSS_CHANGED_ERP_SLOT;
	पूर्ण

	अगर (params->basic_rates) अणु
		ieee80211_parse_bitrates(&sdata->vअगर.bss_conf.chandef,
					 wiphy->bands[sband->band],
					 params->basic_rates,
					 params->basic_rates_len,
					 &sdata->vअगर.bss_conf.basic_rates);
		changed |= BSS_CHANGED_BASIC_RATES;
		ieee80211_check_rate_mask(sdata);
	पूर्ण

	अगर (params->ap_isolate >= 0) अणु
		अगर (params->ap_isolate)
			sdata->flags |= IEEE80211_SDATA_DONT_BRIDGE_PACKETS;
		अन्यथा
			sdata->flags &= ~IEEE80211_SDATA_DONT_BRIDGE_PACKETS;
		ieee80211_check_fast_rx_अगरace(sdata);
	पूर्ण

	अगर (params->ht_opmode >= 0) अणु
		sdata->vअगर.bss_conf.ht_operation_mode =
			(u16) params->ht_opmode;
		changed |= BSS_CHANGED_HT;
	पूर्ण

	अगर (params->p2p_ctwinकरोw >= 0) अणु
		sdata->vअगर.bss_conf.p2p_noa_attr.oppps_ctwinकरोw &=
					~IEEE80211_P2P_OPPPS_CTWINDOW_MASK;
		sdata->vअगर.bss_conf.p2p_noa_attr.oppps_ctwinकरोw |=
			params->p2p_ctwinकरोw & IEEE80211_P2P_OPPPS_CTWINDOW_MASK;
		changed |= BSS_CHANGED_P2P_PS;
	पूर्ण

	अगर (params->p2p_opp_ps > 0) अणु
		sdata->vअगर.bss_conf.p2p_noa_attr.oppps_ctwinकरोw |=
					IEEE80211_P2P_OPPPS_ENABLE_BIT;
		changed |= BSS_CHANGED_P2P_PS;
	पूर्ण अन्यथा अगर (params->p2p_opp_ps == 0) अणु
		sdata->vअगर.bss_conf.p2p_noa_attr.oppps_ctwinकरोw &=
					~IEEE80211_P2P_OPPPS_ENABLE_BIT;
		changed |= BSS_CHANGED_P2P_PS;
	पूर्ण

	ieee80211_bss_info_change_notअगरy(sdata, changed);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_txq_params(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *dev,
				    काष्ठा ieee80211_txq_params *params)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_tx_queue_params p;

	अगर (!local->ops->conf_tx)
		वापस -EOPNOTSUPP;

	अगर (local->hw.queues < IEEE80211_NUM_ACS)
		वापस -EOPNOTSUPP;

	स_रखो(&p, 0, माप(p));
	p.aअगरs = params->aअगरs;
	p.cw_max = params->cwmax;
	p.cw_min = params->cwmin;
	p.txop = params->txop;

	/*
	 * Setting tx queue params disables u-apsd because it's only
	 * called in master mode.
	 */
	p.uapsd = false;

	ieee80211_regulatory_limit_wmm_params(sdata, &p, params->ac);

	sdata->tx_conf[params->ac] = p;
	अगर (drv_conf_tx(local, sdata, params->ac, &p)) अणु
		wiphy_debug(local->hw.wiphy,
			    "failed to set TX queue parameters for AC %d\n",
			    params->ac);
		वापस -EINVAL;
	पूर्ण

	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_QOS);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक ieee80211_suspend(काष्ठा wiphy *wiphy,
			     काष्ठा cfg80211_wowlan *wowlan)
अणु
	वापस __ieee80211_suspend(wiphy_priv(wiphy), wowlan);
पूर्ण

अटल पूर्णांक ieee80211_resume(काष्ठा wiphy *wiphy)
अणु
	वापस __ieee80211_resume(wiphy_priv(wiphy));
पूर्ण
#अन्यथा
#घोषणा ieee80211_suspend शून्य
#घोषणा ieee80211_resume शून्य
#पूर्ण_अगर

अटल पूर्णांक ieee80211_scan(काष्ठा wiphy *wiphy,
			  काष्ठा cfg80211_scan_request *req)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	sdata = IEEE80211_WDEV_TO_SUB_IF(req->wdev);

	चयन (ieee80211_vअगर_type_p2p(&sdata->vअगर)) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		अवरोध;
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (sdata->local->ops->hw_scan)
			अवरोध;
		/*
		 * FIXME: implement NoA जबतक scanning in software,
		 * क्रम now fall through to allow scanning only when
		 * beaconing hasn't been configured yet
		 */
		fallthrough;
	हाल NL80211_IFTYPE_AP:
		/*
		 * If the scan has been क्रमced (and the driver supports
		 * क्रमcing), करोn't care about being beaconing alपढ़ोy.
		 * This will create problems to the attached stations (e.g. all
		 * the  frames sent जबतक scanning on other channel will be
		 * lost)
		 */
		अगर (sdata->u.ap.beacon &&
		    (!(wiphy->features & NL80211_FEATURE_AP_SCAN) ||
		     !(req->flags & NL80211_SCAN_FLAG_AP)))
			वापस -EOPNOTSUPP;
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस ieee80211_request_scan(sdata, req);
पूर्ण

अटल व्योम ieee80211_पात_scan(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	ieee80211_scan_cancel(wiphy_priv(wiphy));
पूर्ण

अटल पूर्णांक
ieee80211_sched_scan_start(काष्ठा wiphy *wiphy,
			   काष्ठा net_device *dev,
			   काष्ठा cfg80211_sched_scan_request *req)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	अगर (!sdata->local->ops->sched_scan_start)
		वापस -EOPNOTSUPP;

	वापस ieee80211_request_sched_scan_start(sdata, req);
पूर्ण

अटल पूर्णांक
ieee80211_sched_scan_stop(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  u64 reqid)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);

	अगर (!local->ops->sched_scan_stop)
		वापस -EOPNOTSUPP;

	वापस ieee80211_request_sched_scan_stop(local);
पूर्ण

अटल पूर्णांक ieee80211_auth(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  काष्ठा cfg80211_auth_request *req)
अणु
	वापस ieee80211_mgd_auth(IEEE80211_DEV_TO_SUB_IF(dev), req);
पूर्ण

अटल पूर्णांक ieee80211_assoc(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   काष्ठा cfg80211_assoc_request *req)
अणु
	वापस ieee80211_mgd_assoc(IEEE80211_DEV_TO_SUB_IF(dev), req);
पूर्ण

अटल पूर्णांक ieee80211_deauth(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			    काष्ठा cfg80211_deauth_request *req)
अणु
	वापस ieee80211_mgd_deauth(IEEE80211_DEV_TO_SUB_IF(dev), req);
पूर्ण

अटल पूर्णांक ieee80211_disassoc(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      काष्ठा cfg80211_disassoc_request *req)
अणु
	वापस ieee80211_mgd_disassoc(IEEE80211_DEV_TO_SUB_IF(dev), req);
पूर्ण

अटल पूर्णांक ieee80211_join_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       काष्ठा cfg80211_ibss_params *params)
अणु
	वापस ieee80211_ibss_join(IEEE80211_DEV_TO_SUB_IF(dev), params);
पूर्ण

अटल पूर्णांक ieee80211_leave_ibss(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	वापस ieee80211_ibss_leave(IEEE80211_DEV_TO_SUB_IF(dev));
पूर्ण

अटल पूर्णांक ieee80211_join_ocb(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      काष्ठा ocb_setup *setup)
अणु
	वापस ieee80211_ocb_join(IEEE80211_DEV_TO_SUB_IF(dev), setup);
पूर्ण

अटल पूर्णांक ieee80211_leave_ocb(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	वापस ieee80211_ocb_leave(IEEE80211_DEV_TO_SUB_IF(dev));
पूर्ण

अटल पूर्णांक ieee80211_set_mcast_rate(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				    पूर्णांक rate[NUM_NL80211_BANDS])
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	स_नकल(sdata->vअगर.bss_conf.mcast_rate, rate,
	       माप(पूर्णांक) * NUM_NL80211_BANDS);

	ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_MCAST_RATE);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	पूर्णांक err;

	अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD) अणु
		ieee80211_check_fast_xmit_all(local);

		err = drv_set_frag_threshold(local, wiphy->frag_threshold);

		अगर (err) अणु
			ieee80211_check_fast_xmit_all(local);
			वापस err;
		पूर्ण
	पूर्ण

	अगर ((changed & WIPHY_PARAM_COVERAGE_CLASS) ||
	    (changed & WIPHY_PARAM_DYN_ACK)) अणु
		s16 coverage_class;

		coverage_class = changed & WIPHY_PARAM_COVERAGE_CLASS ?
					wiphy->coverage_class : -1;
		err = drv_set_coverage_class(local, coverage_class);

		अगर (err)
			वापस err;
	पूर्ण

	अगर (changed & WIPHY_PARAM_RTS_THRESHOLD) अणु
		err = drv_set_rts_threshold(local, wiphy->rts_threshold);

		अगर (err)
			वापस err;
	पूर्ण

	अगर (changed & WIPHY_PARAM_RETRY_SHORT) अणु
		अगर (wiphy->retry_लघु > IEEE80211_MAX_TX_RETRY)
			वापस -EINVAL;
		local->hw.conf.लघु_frame_max_tx_count = wiphy->retry_लघु;
	पूर्ण
	अगर (changed & WIPHY_PARAM_RETRY_LONG) अणु
		अगर (wiphy->retry_दीर्घ > IEEE80211_MAX_TX_RETRY)
			वापस -EINVAL;
		local->hw.conf.दीर्घ_frame_max_tx_count = wiphy->retry_दीर्घ;
	पूर्ण
	अगर (changed &
	    (WIPHY_PARAM_RETRY_SHORT | WIPHY_PARAM_RETRY_LONG))
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_RETRY_LIMITS);

	अगर (changed & (WIPHY_PARAM_TXQ_LIMIT |
		       WIPHY_PARAM_TXQ_MEMORY_LIMIT |
		       WIPHY_PARAM_TXQ_QUANTUM))
		ieee80211_txq_set_params(local);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_tx_घातer(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev,
				  क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	क्रमागत nl80211_tx_घातer_setting txp_type = type;
	bool update_txp_type = false;
	bool has_monitor = false;

	अगर (wdev) अणु
		sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

		अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR) अणु
			sdata = rtnl_dereference(local->monitor_sdata);
			अगर (!sdata)
				वापस -EOPNOTSUPP;
		पूर्ण

		चयन (type) अणु
		हाल NL80211_TX_POWER_AUTOMATIC:
			sdata->user_घातer_level = IEEE80211_UNSET_POWER_LEVEL;
			txp_type = NL80211_TX_POWER_LIMITED;
			अवरोध;
		हाल NL80211_TX_POWER_LIMITED:
		हाल NL80211_TX_POWER_FIXED:
			अगर (mbm < 0 || (mbm % 100))
				वापस -EOPNOTSUPP;
			sdata->user_घातer_level = MBM_TO_DBM(mbm);
			अवरोध;
		पूर्ण

		अगर (txp_type != sdata->vअगर.bss_conf.txघातer_type) अणु
			update_txp_type = true;
			sdata->vअगर.bss_conf.txघातer_type = txp_type;
		पूर्ण

		ieee80211_recalc_txघातer(sdata, update_txp_type);

		वापस 0;
	पूर्ण

	चयन (type) अणु
	हाल NL80211_TX_POWER_AUTOMATIC:
		local->user_घातer_level = IEEE80211_UNSET_POWER_LEVEL;
		txp_type = NL80211_TX_POWER_LIMITED;
		अवरोध;
	हाल NL80211_TX_POWER_LIMITED:
	हाल NL80211_TX_POWER_FIXED:
		अगर (mbm < 0 || (mbm % 100))
			वापस -EOPNOTSUPP;
		local->user_घातer_level = MBM_TO_DBM(mbm);
		अवरोध;
	पूर्ण

	mutex_lock(&local->अगरlist_mtx);
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR) अणु
			has_monitor = true;
			जारी;
		पूर्ण
		sdata->user_घातer_level = local->user_घातer_level;
		अगर (txp_type != sdata->vअगर.bss_conf.txघातer_type)
			update_txp_type = true;
		sdata->vअगर.bss_conf.txघातer_type = txp_type;
	पूर्ण
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		अगर (sdata->vअगर.type == NL80211_IFTYPE_MONITOR)
			जारी;
		ieee80211_recalc_txघातer(sdata, update_txp_type);
	पूर्ण
	mutex_unlock(&local->अगरlist_mtx);

	अगर (has_monitor) अणु
		sdata = rtnl_dereference(local->monitor_sdata);
		अगर (sdata) अणु
			sdata->user_घातer_level = local->user_घातer_level;
			अगर (txp_type != sdata->vअगर.bss_conf.txघातer_type)
				update_txp_type = true;
			sdata->vअगर.bss_conf.txघातer_type = txp_type;

			ieee80211_recalc_txघातer(sdata, update_txp_type);
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_get_tx_घातer(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev,
				  पूर्णांक *dbm)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);

	अगर (local->ops->get_txघातer)
		वापस drv_get_txघातer(local, sdata, dbm);

	अगर (!local->use_chanctx)
		*dbm = local->hw.conf.घातer_level;
	अन्यथा
		*dbm = sdata->vअगर.bss_conf.txघातer;

	वापस 0;
पूर्ण

अटल व्योम ieee80211_rfसमाप्त_poll(काष्ठा wiphy *wiphy)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);

	drv_rfसमाप्त_poll(local);
पूर्ण

#अगर_घोषित CONFIG_NL80211_TESTMODE
अटल पूर्णांक ieee80211_tesपंचांगode_cmd(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev,
				  व्योम *data, पूर्णांक len)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_vअगर *vअगर = शून्य;

	अगर (!local->ops->tesपंचांगode_cmd)
		वापस -EOPNOTSUPP;

	अगर (wdev) अणु
		काष्ठा ieee80211_sub_अगर_data *sdata;

		sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
		अगर (sdata->flags & IEEE80211_SDATA_IN_DRIVER)
			vअगर = &sdata->vअगर;
	पूर्ण

	वापस local->ops->tesपंचांगode_cmd(&local->hw, vअगर, data, len);
पूर्ण

अटल पूर्णांक ieee80211_tesपंचांगode_dump(काष्ठा wiphy *wiphy,
				   काष्ठा sk_buff *skb,
				   काष्ठा netlink_callback *cb,
				   व्योम *data, पूर्णांक len)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);

	अगर (!local->ops->tesपंचांगode_dump)
		वापस -EOPNOTSUPP;

	वापस local->ops->tesपंचांगode_dump(&local->hw, skb, cb, data, len);
पूर्ण
#पूर्ण_अगर

पूर्णांक __ieee80211_request_smps_mgd(काष्ठा ieee80211_sub_अगर_data *sdata,
				 क्रमागत ieee80211_smps_mode smps_mode)
अणु
	स्थिर u8 *ap;
	क्रमागत ieee80211_smps_mode old_req;
	पूर्णांक err;
	काष्ठा sta_info *sta;
	bool tdls_peer_found = false;

	lockdep_निश्चित_held(&sdata->wdev.mtx);

	अगर (WARN_ON_ONCE(sdata->vअगर.type != NL80211_IFTYPE_STATION))
		वापस -EINVAL;

	old_req = sdata->u.mgd.req_smps;
	sdata->u.mgd.req_smps = smps_mode;

	अगर (old_req == smps_mode &&
	    smps_mode != IEEE80211_SMPS_AUTOMATIC)
		वापस 0;

	/*
	 * If not associated, or current association is not an HT
	 * association, there's no need to करो anything, just store
	 * the new value until we associate.
	 */
	अगर (!sdata->u.mgd.associated ||
	    sdata->vअगर.bss_conf.chandef.width == NL80211_CHAN_WIDTH_20_NOHT)
		वापस 0;

	ap = sdata->u.mgd.associated->bssid;

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(sta, &sdata->local->sta_list, list) अणु
		अगर (!sta->sta.tdls || sta->sdata != sdata || !sta->uploaded ||
		    !test_sta_flag(sta, WLAN_STA_AUTHORIZED))
			जारी;

		tdls_peer_found = true;
		अवरोध;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (smps_mode == IEEE80211_SMPS_AUTOMATIC) अणु
		अगर (tdls_peer_found || !sdata->u.mgd.घातersave)
			smps_mode = IEEE80211_SMPS_OFF;
		अन्यथा
			smps_mode = IEEE80211_SMPS_DYNAMIC;
	पूर्ण

	/* send SM PS frame to AP */
	err = ieee80211_send_smps_action(sdata, smps_mode,
					 ap, ap);
	अगर (err)
		sdata->u.mgd.req_smps = old_req;
	अन्यथा अगर (smps_mode != IEEE80211_SMPS_OFF && tdls_peer_found)
		ieee80211_tearकरोwn_tdls_peers(sdata);

	वापस err;
पूर्ण

अटल पूर्णांक ieee80211_set_घातer_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				    bool enabled, पूर्णांक समयout)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = wdev_priv(dev->ieee80211_ptr);

	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	अगर (!ieee80211_hw_check(&local->hw, SUPPORTS_PS))
		वापस -EOPNOTSUPP;

	अगर (enabled == sdata->u.mgd.घातersave &&
	    समयout == local->dynamic_ps_क्रमced_समयout)
		वापस 0;

	sdata->u.mgd.घातersave = enabled;
	local->dynamic_ps_क्रमced_समयout = समयout;

	/* no change, but अगर स्वतःmatic follow घातersave */
	sdata_lock(sdata);
	__ieee80211_request_smps_mgd(sdata, sdata->u.mgd.req_smps);
	sdata_unlock(sdata);

	अगर (ieee80211_hw_check(&local->hw, SUPPORTS_DYNAMIC_PS))
		ieee80211_hw_config(local, IEEE80211_CONF_CHANGE_PS);

	ieee80211_recalc_ps(local);
	ieee80211_recalc_ps_vअगर(sdata);
	ieee80211_check_fast_rx_अगरace(sdata);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_cqm_rssi_config(काष्ठा wiphy *wiphy,
					 काष्ठा net_device *dev,
					 s32 rssi_thold, u32 rssi_hyst)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_vअगर *vअगर = &sdata->vअगर;
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;

	अगर (rssi_thold == bss_conf->cqm_rssi_thold &&
	    rssi_hyst == bss_conf->cqm_rssi_hyst)
		वापस 0;

	अगर (sdata->vअगर.driver_flags & IEEE80211_VIF_BEACON_FILTER &&
	    !(sdata->vअगर.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI))
		वापस -EOPNOTSUPP;

	bss_conf->cqm_rssi_thold = rssi_thold;
	bss_conf->cqm_rssi_hyst = rssi_hyst;
	bss_conf->cqm_rssi_low = 0;
	bss_conf->cqm_rssi_high = 0;
	sdata->u.mgd.last_cqm_event_संकेत = 0;

	/* tell the driver upon association, unless alपढ़ोy associated */
	अगर (sdata->u.mgd.associated &&
	    sdata->vअगर.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI)
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_CQM);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_cqm_rssi_range_config(काष्ठा wiphy *wiphy,
					       काष्ठा net_device *dev,
					       s32 rssi_low, s32 rssi_high)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_vअगर *vअगर = &sdata->vअगर;
	काष्ठा ieee80211_bss_conf *bss_conf = &vअगर->bss_conf;

	अगर (sdata->vअगर.driver_flags & IEEE80211_VIF_BEACON_FILTER)
		वापस -EOPNOTSUPP;

	bss_conf->cqm_rssi_low = rssi_low;
	bss_conf->cqm_rssi_high = rssi_high;
	bss_conf->cqm_rssi_thold = 0;
	bss_conf->cqm_rssi_hyst = 0;
	sdata->u.mgd.last_cqm_event_संकेत = 0;

	/* tell the driver upon association, unless alपढ़ोy associated */
	अगर (sdata->u.mgd.associated &&
	    sdata->vअगर.driver_flags & IEEE80211_VIF_SUPPORTS_CQM_RSSI)
		ieee80211_bss_info_change_notअगरy(sdata, BSS_CHANGED_CQM);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_bitrate_mask(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev,
				      स्थिर u8 *addr,
				      स्थिर काष्ठा cfg80211_bitrate_mask *mask)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = wdev_priv(dev->ieee80211_ptr);
	पूर्णांक i, ret;

	अगर (!ieee80211_sdata_running(sdata))
		वापस -ENETDOWN;

	/*
	 * If active validate the setting and reject it अगर it करोesn't leave
	 * at least one basic rate usable, since we really have to be able
	 * to send something, and अगर we're an AP we have to be able to करो
	 * so at a basic rate so that all clients can receive it.
	 */
	अगर (rcu_access_poपूर्णांकer(sdata->vअगर.chanctx_conf) &&
	    sdata->vअगर.bss_conf.chandef.chan) अणु
		u32 basic_rates = sdata->vअगर.bss_conf.basic_rates;
		क्रमागत nl80211_band band = sdata->vअगर.bss_conf.chandef.chan->band;

		अगर (!(mask->control[band].legacy & basic_rates))
			वापस -EINVAL;
	पूर्ण

	अगर (ieee80211_hw_check(&local->hw, HAS_RATE_CONTROL)) अणु
		ret = drv_set_bitrate_mask(local, sdata, mask);
		अगर (ret)
			वापस ret;
	पूर्ण

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		काष्ठा ieee80211_supported_band *sband = wiphy->bands[i];
		पूर्णांक j;

		sdata->rc_rateidx_mask[i] = mask->control[i].legacy;
		स_नकल(sdata->rc_rateidx_mcs_mask[i], mask->control[i].ht_mcs,
		       माप(mask->control[i].ht_mcs));
		स_नकल(sdata->rc_rateidx_vht_mcs_mask[i],
		       mask->control[i].vht_mcs,
		       माप(mask->control[i].vht_mcs));

		sdata->rc_has_mcs_mask[i] = false;
		sdata->rc_has_vht_mcs_mask[i] = false;
		अगर (!sband)
			जारी;

		क्रम (j = 0; j < IEEE80211_HT_MCS_MASK_LEN; j++) अणु
			अगर (sdata->rc_rateidx_mcs_mask[i][j] != 0xff) अणु
				sdata->rc_has_mcs_mask[i] = true;
				अवरोध;
			पूर्ण
		पूर्ण

		क्रम (j = 0; j < NL80211_VHT_NSS_MAX; j++) अणु
			अगर (sdata->rc_rateidx_vht_mcs_mask[i][j] != 0xffff) अणु
				sdata->rc_has_vht_mcs_mask[i] = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_start_radar_detection(काष्ठा wiphy *wiphy,
					   काष्ठा net_device *dev,
					   काष्ठा cfg80211_chan_def *chandef,
					   u32 cac_समय_ms)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक err;

	mutex_lock(&local->mtx);
	अगर (!list_empty(&local->roc_list) || local->scanning) अणु
		err = -EBUSY;
		जाओ out_unlock;
	पूर्ण

	/* whatever, but channel contexts should not complain about that one */
	sdata->smps_mode = IEEE80211_SMPS_OFF;
	sdata->needed_rx_chains = local->rx_chains;

	err = ieee80211_vअगर_use_channel(sdata, chandef,
					IEEE80211_CHANCTX_SHARED);
	अगर (err)
		जाओ out_unlock;

	ieee80211_queue_delayed_work(&sdata->local->hw,
				     &sdata->dfs_cac_समयr_work,
				     msecs_to_jअगरfies(cac_समय_ms));

 out_unlock:
	mutex_unlock(&local->mtx);
	वापस err;
पूर्ण

अटल व्योम ieee80211_end_cac(काष्ठा wiphy *wiphy,
			      काष्ठा net_device *dev)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;

	mutex_lock(&local->mtx);
	list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list) अणु
		/* it might be रुकोing क्रम the local->mtx, but then
		 * by the समय it माला_लो it, sdata->wdev.cac_started
		 * will no दीर्घer be true
		 */
		cancel_delayed_work(&sdata->dfs_cac_समयr_work);

		अगर (sdata->wdev.cac_started) अणु
			ieee80211_vअगर_release_channel(sdata);
			sdata->wdev.cac_started = false;
		पूर्ण
	पूर्ण
	mutex_unlock(&local->mtx);
पूर्ण

अटल काष्ठा cfg80211_beacon_data *
cfg80211_beacon_dup(काष्ठा cfg80211_beacon_data *beacon)
अणु
	काष्ठा cfg80211_beacon_data *new_beacon;
	u8 *pos;
	पूर्णांक len;

	len = beacon->head_len + beacon->tail_len + beacon->beacon_ies_len +
	      beacon->proberesp_ies_len + beacon->assocresp_ies_len +
	      beacon->probe_resp_len + beacon->lci_len + beacon->civicloc_len;

	new_beacon = kzalloc(माप(*new_beacon) + len, GFP_KERNEL);
	अगर (!new_beacon)
		वापस शून्य;

	pos = (u8 *)(new_beacon + 1);
	अगर (beacon->head_len) अणु
		new_beacon->head_len = beacon->head_len;
		new_beacon->head = pos;
		स_नकल(pos, beacon->head, beacon->head_len);
		pos += beacon->head_len;
	पूर्ण
	अगर (beacon->tail_len) अणु
		new_beacon->tail_len = beacon->tail_len;
		new_beacon->tail = pos;
		स_नकल(pos, beacon->tail, beacon->tail_len);
		pos += beacon->tail_len;
	पूर्ण
	अगर (beacon->beacon_ies_len) अणु
		new_beacon->beacon_ies_len = beacon->beacon_ies_len;
		new_beacon->beacon_ies = pos;
		स_नकल(pos, beacon->beacon_ies, beacon->beacon_ies_len);
		pos += beacon->beacon_ies_len;
	पूर्ण
	अगर (beacon->proberesp_ies_len) अणु
		new_beacon->proberesp_ies_len = beacon->proberesp_ies_len;
		new_beacon->proberesp_ies = pos;
		स_नकल(pos, beacon->proberesp_ies, beacon->proberesp_ies_len);
		pos += beacon->proberesp_ies_len;
	पूर्ण
	अगर (beacon->assocresp_ies_len) अणु
		new_beacon->assocresp_ies_len = beacon->assocresp_ies_len;
		new_beacon->assocresp_ies = pos;
		स_नकल(pos, beacon->assocresp_ies, beacon->assocresp_ies_len);
		pos += beacon->assocresp_ies_len;
	पूर्ण
	अगर (beacon->probe_resp_len) अणु
		new_beacon->probe_resp_len = beacon->probe_resp_len;
		new_beacon->probe_resp = pos;
		स_नकल(pos, beacon->probe_resp, beacon->probe_resp_len);
		pos += beacon->probe_resp_len;
	पूर्ण

	/* might copy -1, meaning no changes requested */
	new_beacon->fपंचांग_responder = beacon->fपंचांग_responder;
	अगर (beacon->lci) अणु
		new_beacon->lci_len = beacon->lci_len;
		new_beacon->lci = pos;
		स_नकल(pos, beacon->lci, beacon->lci_len);
		pos += beacon->lci_len;
	पूर्ण
	अगर (beacon->civicloc) अणु
		new_beacon->civicloc_len = beacon->civicloc_len;
		new_beacon->civicloc = pos;
		स_नकल(pos, beacon->civicloc, beacon->civicloc_len);
		pos += beacon->civicloc_len;
	पूर्ण

	वापस new_beacon;
पूर्ण

व्योम ieee80211_csa_finish(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	ieee80211_queue_work(&sdata->local->hw,
			     &sdata->csa_finalize_work);
पूर्ण
EXPORT_SYMBOL(ieee80211_csa_finish);

अटल पूर्णांक ieee80211_set_after_csa_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
					  u32 *changed)
अणु
	पूर्णांक err;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP:
		err = ieee80211_assign_beacon(sdata, sdata->u.ap.next_beacon,
					      शून्य);
		kमुक्त(sdata->u.ap.next_beacon);
		sdata->u.ap.next_beacon = शून्य;

		अगर (err < 0)
			वापस err;
		*changed |= err;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		err = ieee80211_ibss_finish_csa(sdata);
		अगर (err < 0)
			वापस err;
		*changed |= err;
		अवरोध;
#अगर_घोषित CONFIG_MAC80211_MESH
	हाल NL80211_IFTYPE_MESH_POINT:
		err = ieee80211_mesh_finish_csa(sdata);
		अगर (err < 0)
			वापस err;
		*changed |= err;
		अवरोध;
#पूर्ण_अगर
	शेष:
		WARN_ON(1);
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __ieee80211_csa_finalize(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	u32 changed = 0;
	पूर्णांक err;

	sdata_निश्चित_lock(sdata);
	lockdep_निश्चित_held(&local->mtx);
	lockdep_निश्चित_held(&local->chanctx_mtx);

	/*
	 * using reservation isn't immediate as it may be deferred until later
	 * with multi-vअगर. once reservation is complete it will re-schedule the
	 * work with no reserved_chanctx so verअगरy chandef to check अगर it
	 * completed successfully
	 */

	अगर (sdata->reserved_chanctx) अणु
		/*
		 * with multi-vअगर csa driver may call ieee80211_csa_finish()
		 * many बार जबतक रुकोing क्रम other पूर्णांकerfaces to use their
		 * reservations
		 */
		अगर (sdata->reserved_पढ़ोy)
			वापस 0;

		वापस ieee80211_vअगर_use_reserved_context(sdata);
	पूर्ण

	अगर (!cfg80211_chandef_identical(&sdata->vअगर.bss_conf.chandef,
					&sdata->csa_chandef))
		वापस -EINVAL;

	sdata->vअगर.csa_active = false;

	err = ieee80211_set_after_csa_beacon(sdata, &changed);
	अगर (err)
		वापस err;

	ieee80211_bss_info_change_notअगरy(sdata, changed);

	अगर (sdata->csa_block_tx) अणु
		ieee80211_wake_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);
		sdata->csa_block_tx = false;
	पूर्ण

	err = drv_post_channel_चयन(sdata);
	अगर (err)
		वापस err;

	cfg80211_ch_चयन_notअगरy(sdata->dev, &sdata->csa_chandef);

	वापस 0;
पूर्ण

अटल व्योम ieee80211_csa_finalize(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	अगर (__ieee80211_csa_finalize(sdata)) अणु
		sdata_info(sdata, "failed to finalize CSA, disconnecting\n");
		cfg80211_stop_अगरace(sdata->local->hw.wiphy, &sdata->wdev,
				    GFP_KERNEL);
	पूर्ण
पूर्ण

व्योम ieee80211_csa_finalize_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata =
		container_of(work, काष्ठा ieee80211_sub_अगर_data,
			     csa_finalize_work);
	काष्ठा ieee80211_local *local = sdata->local;

	sdata_lock(sdata);
	mutex_lock(&local->mtx);
	mutex_lock(&local->chanctx_mtx);

	/* AP might have been stopped जबतक रुकोing क्रम the lock. */
	अगर (!sdata->vअगर.csa_active)
		जाओ unlock;

	अगर (!ieee80211_sdata_running(sdata))
		जाओ unlock;

	ieee80211_csa_finalize(sdata);

unlock:
	mutex_unlock(&local->chanctx_mtx);
	mutex_unlock(&local->mtx);
	sdata_unlock(sdata);
पूर्ण

अटल पूर्णांक ieee80211_set_csa_beacon(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा cfg80211_csa_settings *params,
				    u32 *changed)
अणु
	काष्ठा ieee80211_csa_settings csa = अणुपूर्ण;
	पूर्णांक err;

	चयन (sdata->vअगर.type) अणु
	हाल NL80211_IFTYPE_AP:
		sdata->u.ap.next_beacon =
			cfg80211_beacon_dup(&params->beacon_after);
		अगर (!sdata->u.ap.next_beacon)
			वापस -ENOMEM;

		/*
		 * With a count of 0, we करोn't have to रुको क्रम any
		 * TBTT beक्रमe चयनing, so complete the CSA
		 * immediately.  In theory, with a count == 1 we
		 * should delay the चयन until just beक्रमe the next
		 * TBTT, but that would complicate things so we चयन
		 * immediately too.  If we would delay the चयन
		 * until the next TBTT, we would have to set the probe
		 * response here.
		 *
		 * TODO: A channel चयन with count <= 1 without
		 * sending a CSA action frame is kind of useless,
		 * because the clients won't know we're changing
		 * channels.  The action frame must be implemented
		 * either here or in the userspace.
		 */
		अगर (params->count <= 1)
			अवरोध;

		अगर ((params->n_counter_offsets_beacon >
		     IEEE80211_MAX_CNTDWN_COUNTERS_NUM) ||
		    (params->n_counter_offsets_presp >
		     IEEE80211_MAX_CNTDWN_COUNTERS_NUM))
			वापस -EINVAL;

		csa.counter_offsets_beacon = params->counter_offsets_beacon;
		csa.counter_offsets_presp = params->counter_offsets_presp;
		csa.n_counter_offsets_beacon = params->n_counter_offsets_beacon;
		csa.n_counter_offsets_presp = params->n_counter_offsets_presp;
		csa.count = params->count;

		err = ieee80211_assign_beacon(sdata, &params->beacon_csa, &csa);
		अगर (err < 0) अणु
			kमुक्त(sdata->u.ap.next_beacon);
			वापस err;
		पूर्ण
		*changed |= err;

		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		अगर (!sdata->vअगर.bss_conf.ibss_joined)
			वापस -EINVAL;

		अगर (params->chandef.width != sdata->u.ibss.chandef.width)
			वापस -EINVAL;

		चयन (params->chandef.width) अणु
		हाल NL80211_CHAN_WIDTH_40:
			अगर (cfg80211_get_chandef_type(&params->chandef) !=
			    cfg80211_get_chandef_type(&sdata->u.ibss.chandef))
				वापस -EINVAL;
			अवरोध;
		हाल NL80211_CHAN_WIDTH_5:
		हाल NL80211_CHAN_WIDTH_10:
		हाल NL80211_CHAN_WIDTH_20_NOHT:
		हाल NL80211_CHAN_WIDTH_20:
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण

		/* changes पूर्णांकo another band are not supported */
		अगर (sdata->u.ibss.chandef.chan->band !=
		    params->chandef.chan->band)
			वापस -EINVAL;

		/* see comments in the NL80211_IFTYPE_AP block */
		अगर (params->count > 1) अणु
			err = ieee80211_ibss_csa_beacon(sdata, params);
			अगर (err < 0)
				वापस err;
			*changed |= err;
		पूर्ण

		ieee80211_send_action_csa(sdata, params);

		अवरोध;
#अगर_घोषित CONFIG_MAC80211_MESH
	हाल NL80211_IFTYPE_MESH_POINT: अणु
		काष्ठा ieee80211_अगर_mesh *अगरmsh = &sdata->u.mesh;

		अगर (params->chandef.width != sdata->vअगर.bss_conf.chandef.width)
			वापस -EINVAL;

		/* changes पूर्णांकo another band are not supported */
		अगर (sdata->vअगर.bss_conf.chandef.chan->band !=
		    params->chandef.chan->band)
			वापस -EINVAL;

		अगर (अगरmsh->csa_role == IEEE80211_MESH_CSA_ROLE_NONE) अणु
			अगरmsh->csa_role = IEEE80211_MESH_CSA_ROLE_INIT;
			अगर (!अगरmsh->pre_value)
				अगरmsh->pre_value = 1;
			अन्यथा
				अगरmsh->pre_value++;
		पूर्ण

		/* see comments in the NL80211_IFTYPE_AP block */
		अगर (params->count > 1) अणु
			err = ieee80211_mesh_csa_beacon(sdata, params);
			अगर (err < 0) अणु
				अगरmsh->csa_role = IEEE80211_MESH_CSA_ROLE_NONE;
				वापस err;
			पूर्ण
			*changed |= err;
		पूर्ण

		अगर (अगरmsh->csa_role == IEEE80211_MESH_CSA_ROLE_INIT)
			ieee80211_send_action_csa(sdata, params);

		अवरोध;
		पूर्ण
#पूर्ण_अगर
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
__ieee80211_channel_चयन(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   काष्ठा cfg80211_csa_settings *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_channel_चयन ch_चयन;
	काष्ठा ieee80211_chanctx_conf *conf;
	काष्ठा ieee80211_chanctx *chanctx;
	u32 changed = 0;
	पूर्णांक err;

	sdata_निश्चित_lock(sdata);
	lockdep_निश्चित_held(&local->mtx);

	अगर (!list_empty(&local->roc_list) || local->scanning)
		वापस -EBUSY;

	अगर (sdata->wdev.cac_started)
		वापस -EBUSY;

	अगर (cfg80211_chandef_identical(&params->chandef,
				       &sdata->vअगर.bss_conf.chandef))
		वापस -EINVAL;

	/* करोn't allow another channel चयन अगर one is alपढ़ोy active. */
	अगर (sdata->vअगर.csa_active)
		वापस -EBUSY;

	mutex_lock(&local->chanctx_mtx);
	conf = rcu_dereference_रक्षित(sdata->vअगर.chanctx_conf,
					 lockdep_is_held(&local->chanctx_mtx));
	अगर (!conf) अणु
		err = -EBUSY;
		जाओ out;
	पूर्ण

	अगर (params->chandef.chan->freq_offset) अणु
		/* this may work, but is untested */
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	chanctx = container_of(conf, काष्ठा ieee80211_chanctx, conf);

	ch_चयन.बारtamp = 0;
	ch_चयन.device_बारtamp = 0;
	ch_चयन.block_tx = params->block_tx;
	ch_चयन.chandef = params->chandef;
	ch_चयन.count = params->count;

	err = drv_pre_channel_चयन(sdata, &ch_चयन);
	अगर (err)
		जाओ out;

	err = ieee80211_vअगर_reserve_chanctx(sdata, &params->chandef,
					    chanctx->mode,
					    params->radar_required);
	अगर (err)
		जाओ out;

	/* अगर reservation is invalid then this will fail */
	err = ieee80211_check_combinations(sdata, शून्य, chanctx->mode, 0);
	अगर (err) अणु
		ieee80211_vअगर_unreserve_chanctx(sdata);
		जाओ out;
	पूर्ण

	err = ieee80211_set_csa_beacon(sdata, params, &changed);
	अगर (err) अणु
		ieee80211_vअगर_unreserve_chanctx(sdata);
		जाओ out;
	पूर्ण

	sdata->csa_chandef = params->chandef;
	sdata->csa_block_tx = params->block_tx;
	sdata->vअगर.csa_active = true;

	अगर (sdata->csa_block_tx)
		ieee80211_stop_vअगर_queues(local, sdata,
					  IEEE80211_QUEUE_STOP_REASON_CSA);

	cfg80211_ch_चयन_started_notअगरy(sdata->dev, &sdata->csa_chandef,
					  params->count, params->block_tx);

	अगर (changed) अणु
		ieee80211_bss_info_change_notअगरy(sdata, changed);
		drv_channel_चयन_beacon(sdata, &params->chandef);
	पूर्ण अन्यथा अणु
		/* अगर the beacon didn't change, we can finalize immediately */
		ieee80211_csa_finalize(sdata);
	पूर्ण

out:
	mutex_unlock(&local->chanctx_mtx);
	वापस err;
पूर्ण

पूर्णांक ieee80211_channel_चयन(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     काष्ठा cfg80211_csa_settings *params)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	पूर्णांक err;

	mutex_lock(&local->mtx);
	err = __ieee80211_channel_चयन(wiphy, dev, params);
	mutex_unlock(&local->mtx);

	वापस err;
पूर्ण

u64 ieee80211_mgmt_tx_cookie(काष्ठा ieee80211_local *local)
अणु
	lockdep_निश्चित_held(&local->mtx);

	local->roc_cookie_counter++;

	/* wow, you wrapped 64 bits ... more likely a bug */
	अगर (WARN_ON(local->roc_cookie_counter == 0))
		local->roc_cookie_counter++;

	वापस local->roc_cookie_counter;
पूर्ण

पूर्णांक ieee80211_attach_ack_skb(काष्ठा ieee80211_local *local, काष्ठा sk_buff *skb,
			     u64 *cookie, gfp_t gfp)
अणु
	अचिन्हित दीर्घ spin_flags;
	काष्ठा sk_buff *ack_skb;
	पूर्णांक id;

	ack_skb = skb_copy(skb, gfp);
	अगर (!ack_skb)
		वापस -ENOMEM;

	spin_lock_irqsave(&local->ack_status_lock, spin_flags);
	id = idr_alloc(&local->ack_status_frames, ack_skb,
		       1, 0x2000, GFP_ATOMIC);
	spin_unlock_irqrestore(&local->ack_status_lock, spin_flags);

	अगर (id < 0) अणु
		kमुक्त_skb(ack_skb);
		वापस -ENOMEM;
	पूर्ण

	IEEE80211_SKB_CB(skb)->ack_frame_id = id;

	*cookie = ieee80211_mgmt_tx_cookie(local);
	IEEE80211_SKB_CB(ack_skb)->ack.cookie = *cookie;

	वापस 0;
पूर्ण

अटल व्योम
ieee80211_update_mgmt_frame_registrations(काष्ठा wiphy *wiphy,
					  काष्ठा wireless_dev *wdev,
					  काष्ठा mgmt_frame_regs *upd)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	u32 preq_mask = BIT(IEEE80211_STYPE_PROBE_REQ >> 4);
	u32 action_mask = BIT(IEEE80211_STYPE_ACTION >> 4);
	bool global_change, पूर्णांकf_change;

	global_change =
		(local->probe_req_reg != !!(upd->global_stypes & preq_mask)) ||
		(local->rx_mcast_action_reg !=
		 !!(upd->global_mcast_stypes & action_mask));
	local->probe_req_reg = upd->global_stypes & preq_mask;
	local->rx_mcast_action_reg = upd->global_mcast_stypes & action_mask;

	पूर्णांकf_change = (sdata->vअगर.probe_req_reg !=
		       !!(upd->पूर्णांकerface_stypes & preq_mask)) ||
		(sdata->vअगर.rx_mcast_action_reg !=
		 !!(upd->पूर्णांकerface_mcast_stypes & action_mask));
	sdata->vअगर.probe_req_reg = upd->पूर्णांकerface_stypes & preq_mask;
	sdata->vअगर.rx_mcast_action_reg =
		upd->पूर्णांकerface_mcast_stypes & action_mask;

	अगर (!local->खोलो_count)
		वापस;

	अगर (पूर्णांकf_change && ieee80211_sdata_running(sdata))
		drv_config_अगरace_filter(local, sdata,
					sdata->vअगर.probe_req_reg ?
						FIF_PROBE_REQ : 0,
					FIF_PROBE_REQ);

	अगर (global_change)
		ieee80211_configure_filter(local);
पूर्ण

अटल पूर्णांक ieee80211_set_antenna(काष्ठा wiphy *wiphy, u32 tx_ant, u32 rx_ant)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);

	अगर (local->started)
		वापस -EOPNOTSUPP;

	वापस drv_set_antenna(local, tx_ant, rx_ant);
पूर्ण

अटल पूर्णांक ieee80211_get_antenna(काष्ठा wiphy *wiphy, u32 *tx_ant, u32 *rx_ant)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);

	वापस drv_get_antenna(local, tx_ant, rx_ant);
पूर्ण

अटल पूर्णांक ieee80211_set_rekey_data(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *dev,
				    काष्ठा cfg80211_gtk_rekey_data *data)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	अगर (!local->ops->set_rekey_data)
		वापस -EOPNOTSUPP;

	drv_set_rekey_data(local, sdata, data);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_probe_client(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				  स्थिर u8 *peer, u64 *cookie)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_qos_hdr *nullfunc;
	काष्ठा sk_buff *skb;
	पूर्णांक size = माप(*nullfunc);
	__le16 fc;
	bool qos;
	काष्ठा ieee80211_tx_info *info;
	काष्ठा sta_info *sta;
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	क्रमागत nl80211_band band;
	पूर्णांक ret;

	/* the lock is needed to assign the cookie later */
	mutex_lock(&local->mtx);

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (WARN_ON(!chanctx_conf)) अणु
		ret = -EINVAL;
		जाओ unlock;
	पूर्ण
	band = chanctx_conf->def.chan->band;
	sta = sta_info_get_bss(sdata, peer);
	अगर (sta) अणु
		qos = sta->sta.wme;
	पूर्ण अन्यथा अणु
		ret = -ENOLINK;
		जाओ unlock;
	पूर्ण

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
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ unlock;
	पूर्ण

	skb->dev = dev;

	skb_reserve(skb, local->hw.extra_tx_headroom);

	nullfunc = skb_put(skb, size);
	nullfunc->frame_control = fc;
	nullfunc->duration_id = 0;
	स_नकल(nullfunc->addr1, sta->sta.addr, ETH_ALEN);
	स_नकल(nullfunc->addr2, sdata->vअगर.addr, ETH_ALEN);
	स_नकल(nullfunc->addr3, sdata->vअगर.addr, ETH_ALEN);
	nullfunc->seq_ctrl = 0;

	info = IEEE80211_SKB_CB(skb);

	info->flags |= IEEE80211_TX_CTL_REQ_TX_STATUS |
		       IEEE80211_TX_INTFL_NL80211_FRAME_TX;
	info->band = band;

	skb_set_queue_mapping(skb, IEEE80211_AC_VO);
	skb->priority = 7;
	अगर (qos)
		nullfunc->qos_ctrl = cpu_to_le16(7);

	ret = ieee80211_attach_ack_skb(local, skb, cookie, GFP_ATOMIC);
	अगर (ret) अणु
		kमुक्त_skb(skb);
		जाओ unlock;
	पूर्ण

	local_bh_disable();
	ieee80211_xmit(sdata, sta, skb);
	local_bh_enable();

	ret = 0;
unlock:
	rcu_पढ़ो_unlock();
	mutex_unlock(&local->mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_cfg_get_channel(काष्ठा wiphy *wiphy,
				     काष्ठा wireless_dev *wdev,
				     काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_chanctx_conf *chanctx_conf;
	पूर्णांक ret = -ENODATA;

	rcu_पढ़ो_lock();
	chanctx_conf = rcu_dereference(sdata->vअगर.chanctx_conf);
	अगर (chanctx_conf) अणु
		*chandef = sdata->vअगर.bss_conf.chandef;
		ret = 0;
	पूर्ण अन्यथा अगर (local->खोलो_count > 0 &&
		   local->खोलो_count == local->monitors &&
		   sdata->vअगर.type == NL80211_IFTYPE_MONITOR) अणु
		अगर (local->use_chanctx)
			*chandef = local->monitor_chandef;
		अन्यथा
			*chandef = local->_oper_chandef;
		ret = 0;
	पूर्ण
	rcu_पढ़ो_unlock();

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल व्योम ieee80211_set_wakeup(काष्ठा wiphy *wiphy, bool enabled)
अणु
	drv_set_wakeup(wiphy_priv(wiphy), enabled);
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक ieee80211_set_qos_map(काष्ठा wiphy *wiphy,
				 काष्ठा net_device *dev,
				 काष्ठा cfg80211_qos_map *qos_map)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा mac80211_qos_map *new_qos_map, *old_qos_map;

	अगर (qos_map) अणु
		new_qos_map = kzalloc(माप(*new_qos_map), GFP_KERNEL);
		अगर (!new_qos_map)
			वापस -ENOMEM;
		स_नकल(&new_qos_map->qos_map, qos_map, माप(*qos_map));
	पूर्ण अन्यथा अणु
		/* A शून्य qos_map was passed to disable QoS mapping */
		new_qos_map = शून्य;
	पूर्ण

	old_qos_map = sdata_dereference(sdata->qos_map, sdata);
	rcu_assign_poपूर्णांकer(sdata->qos_map, new_qos_map);
	अगर (old_qos_map)
		kमुक्त_rcu(old_qos_map, rcu_head);

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_set_ap_chanwidth(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev,
				      काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	पूर्णांक ret;
	u32 changed = 0;

	ret = ieee80211_vअगर_change_bandwidth(sdata, chandef, &changed);
	अगर (ret == 0)
		ieee80211_bss_info_change_notअगरy(sdata, changed);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_add_tx_ts(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       u8 tsid, स्थिर u8 *peer, u8 up,
			       u16 admitted_समय)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	पूर्णांक ac = ieee802_1d_to_ac[up];

	अगर (sdata->vअगर.type != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	अगर (!(sdata->wmm_acm & BIT(up)))
		वापस -EINVAL;

	अगर (अगरmgd->tx_tspec[ac].admitted_समय)
		वापस -EBUSY;

	अगर (admitted_समय) अणु
		अगरmgd->tx_tspec[ac].admitted_समय = 32 * admitted_समय;
		अगरmgd->tx_tspec[ac].tsid = tsid;
		अगरmgd->tx_tspec[ac].up = up;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक ieee80211_del_tx_ts(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       u8 tsid, स्थिर u8 *peer)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा ieee80211_अगर_managed *अगरmgd = &sdata->u.mgd;
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	पूर्णांक ac;

	क्रम (ac = 0; ac < IEEE80211_NUM_ACS; ac++) अणु
		काष्ठा ieee80211_sta_tx_tspec *tx_tspec = &अगरmgd->tx_tspec[ac];

		/* skip unused entries */
		अगर (!tx_tspec->admitted_समय)
			जारी;

		अगर (tx_tspec->tsid != tsid)
			जारी;

		/* due to this new packets will be reasचिन्हित to non-ACM ACs */
		tx_tspec->up = -1;

		/* Make sure that all packets have been sent to aव्योम to
		 * restore the QoS params on packets that are still on the
		 * queues.
		 */
		synchronize_net();
		ieee80211_flush_queues(local, sdata, false);

		/* restore the normal QoS parameters
		 * (unconditionally to aव्योम races)
		 */
		tx_tspec->action = TX_TSPEC_ACTION_STOP_DOWNGRADE;
		tx_tspec->करोwngraded = false;
		ieee80211_sta_handle_tspec_ac_params(sdata);

		/* finally clear all the data */
		स_रखो(tx_tspec, 0, माप(*tx_tspec));

		वापस 0;
	पूर्ण

	वापस -ENOENT;
पूर्ण

व्योम ieee80211_nan_func_terminated(काष्ठा ieee80211_vअगर *vअगर,
				   u8 inst_id,
				   क्रमागत nl80211_nan_func_term_reason reason,
				   gfp_t gfp)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा cfg80211_nan_func *func;
	u64 cookie;

	अगर (WARN_ON(vअगर->type != NL80211_IFTYPE_न_अंक))
		वापस;

	spin_lock_bh(&sdata->u.nan.func_lock);

	func = idr_find(&sdata->u.nan.function_inst_ids, inst_id);
	अगर (WARN_ON(!func)) अणु
		spin_unlock_bh(&sdata->u.nan.func_lock);
		वापस;
	पूर्ण

	cookie = func->cookie;
	idr_हटाओ(&sdata->u.nan.function_inst_ids, inst_id);

	spin_unlock_bh(&sdata->u.nan.func_lock);

	cfg80211_मुक्त_nan_func(func);

	cfg80211_nan_func_terminated(ieee80211_vअगर_to_wdev(vअगर), inst_id,
				     reason, cookie, gfp);
पूर्ण
EXPORT_SYMBOL(ieee80211_nan_func_terminated);

व्योम ieee80211_nan_func_match(काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा cfg80211_nan_match_params *match,
			      gfp_t gfp)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा cfg80211_nan_func *func;

	अगर (WARN_ON(vअगर->type != NL80211_IFTYPE_न_अंक))
		वापस;

	spin_lock_bh(&sdata->u.nan.func_lock);

	func = idr_find(&sdata->u.nan.function_inst_ids,  match->inst_id);
	अगर (WARN_ON(!func)) अणु
		spin_unlock_bh(&sdata->u.nan.func_lock);
		वापस;
	पूर्ण
	match->cookie = func->cookie;

	spin_unlock_bh(&sdata->u.nan.func_lock);

	cfg80211_nan_match(ieee80211_vअगर_to_wdev(vअगर), match, gfp);
पूर्ण
EXPORT_SYMBOL(ieee80211_nan_func_match);

अटल पूर्णांक ieee80211_set_multicast_to_unicast(काष्ठा wiphy *wiphy,
					      काष्ठा net_device *dev,
					      स्थिर bool enabled)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	sdata->u.ap.multicast_to_unicast = enabled;

	वापस 0;
पूर्ण

व्योम ieee80211_fill_txq_stats(काष्ठा cfg80211_txq_stats *txqstats,
			      काष्ठा txq_info *txqi)
अणु
	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_BACKLOG_BYTES))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_BACKLOG_BYTES);
		txqstats->backlog_bytes = txqi->tin.backlog_bytes;
	पूर्ण

	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_BACKLOG_PACKETS))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_BACKLOG_PACKETS);
		txqstats->backlog_packets = txqi->tin.backlog_packets;
	पूर्ण

	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_FLOWS))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_FLOWS);
		txqstats->flows = txqi->tin.flows;
	पूर्ण

	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_DROPS))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_DROPS);
		txqstats->drops = txqi->cstats.drop_count;
	पूर्ण

	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_ECN_MARKS))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_ECN_MARKS);
		txqstats->ecn_marks = txqi->cstats.ecn_mark;
	पूर्ण

	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_OVERLIMIT))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_OVERLIMIT);
		txqstats->overlimit = txqi->tin.overlimit;
	पूर्ण

	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_COLLISIONS))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_COLLISIONS);
		txqstats->collisions = txqi->tin.collisions;
	पूर्ण

	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_TX_BYTES))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_TX_BYTES);
		txqstats->tx_bytes = txqi->tin.tx_bytes;
	पूर्ण

	अगर (!(txqstats->filled & BIT(NL80211_TXQ_STATS_TX_PACKETS))) अणु
		txqstats->filled |= BIT(NL80211_TXQ_STATS_TX_PACKETS);
		txqstats->tx_packets = txqi->tin.tx_packets;
	पूर्ण
पूर्ण

अटल पूर्णांक ieee80211_get_txq_stats(काष्ठा wiphy *wiphy,
				   काष्ठा wireless_dev *wdev,
				   काष्ठा cfg80211_txq_stats *txqstats)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata;
	पूर्णांक ret = 0;

	अगर (!local->ops->wake_tx_queue)
		वापस 1;

	spin_lock_bh(&local->fq.lock);
	rcu_पढ़ो_lock();

	अगर (wdev) अणु
		sdata = IEEE80211_WDEV_TO_SUB_IF(wdev);
		अगर (!sdata->vअगर.txq) अणु
			ret = 1;
			जाओ out;
		पूर्ण
		ieee80211_fill_txq_stats(txqstats, to_txq_info(sdata->vअगर.txq));
	पूर्ण अन्यथा अणु
		/* phy stats */
		txqstats->filled |= BIT(NL80211_TXQ_STATS_BACKLOG_PACKETS) |
				    BIT(NL80211_TXQ_STATS_BACKLOG_BYTES) |
				    BIT(NL80211_TXQ_STATS_OVERLIMIT) |
				    BIT(NL80211_TXQ_STATS_OVERMEMORY) |
				    BIT(NL80211_TXQ_STATS_COLLISIONS) |
				    BIT(NL80211_TXQ_STATS_MAX_FLOWS);
		txqstats->backlog_packets = local->fq.backlog;
		txqstats->backlog_bytes = local->fq.memory_usage;
		txqstats->overlimit = local->fq.overlimit;
		txqstats->overmemory = local->fq.overmemory;
		txqstats->collisions = local->fq.collisions;
		txqstats->max_flows = local->fq.flows_cnt;
	पूर्ण

out:
	rcu_पढ़ो_unlock();
	spin_unlock_bh(&local->fq.lock);

	वापस ret;
पूर्ण

अटल पूर्णांक
ieee80211_get_fपंचांग_responder_stats(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *dev,
				  काष्ठा cfg80211_fपंचांग_responder_stats *fपंचांग_stats)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);

	वापस drv_get_fपंचांग_responder_stats(local, sdata, fपंचांग_stats);
पूर्ण

अटल पूर्णांक
ieee80211_start_pmsr(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *dev,
		     काष्ठा cfg80211_pmsr_request *request)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(dev);

	वापस drv_start_pmsr(local, sdata, request);
पूर्ण

अटल व्योम
ieee80211_पात_pmsr(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *dev,
		     काष्ठा cfg80211_pmsr_request *request)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_WDEV_TO_SUB_IF(dev);

	वापस drv_पात_pmsr(local, sdata, request);
पूर्ण

अटल पूर्णांक ieee80211_set_tid_config(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *dev,
				    काष्ठा cfg80211_tid_config *tid_conf)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा sta_info *sta;
	पूर्णांक ret;

	अगर (!sdata->local->ops->set_tid_config)
		वापस -EOPNOTSUPP;

	अगर (!tid_conf->peer)
		वापस drv_set_tid_config(sdata->local, sdata, शून्य, tid_conf);

	mutex_lock(&sdata->local->sta_mtx);
	sta = sta_info_get_bss(sdata, tid_conf->peer);
	अगर (!sta) अणु
		mutex_unlock(&sdata->local->sta_mtx);
		वापस -ENOENT;
	पूर्ण

	ret = drv_set_tid_config(sdata->local, sdata, &sta->sta, tid_conf);
	mutex_unlock(&sdata->local->sta_mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_reset_tid_config(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *dev,
				      स्थिर u8 *peer, u8 tids)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = IEEE80211_DEV_TO_SUB_IF(dev);
	काष्ठा sta_info *sta;
	पूर्णांक ret;

	अगर (!sdata->local->ops->reset_tid_config)
		वापस -EOPNOTSUPP;

	अगर (!peer)
		वापस drv_reset_tid_config(sdata->local, sdata, शून्य, tids);

	mutex_lock(&sdata->local->sta_mtx);
	sta = sta_info_get_bss(sdata, peer);
	अगर (!sta) अणु
		mutex_unlock(&sdata->local->sta_mtx);
		वापस -ENOENT;
	पूर्ण

	ret = drv_reset_tid_config(sdata->local, sdata, &sta->sta, tids);
	mutex_unlock(&sdata->local->sta_mtx);

	वापस ret;
पूर्ण

अटल पूर्णांक ieee80211_set_sar_specs(काष्ठा wiphy *wiphy,
				   काष्ठा cfg80211_sar_specs *sar)
अणु
	काष्ठा ieee80211_local *local = wiphy_priv(wiphy);

	अगर (!local->ops->set_sar_specs)
		वापस -EOPNOTSUPP;

	वापस local->ops->set_sar_specs(&local->hw, sar);
पूर्ण

स्थिर काष्ठा cfg80211_ops mac80211_config_ops = अणु
	.add_भव_पूर्णांकf = ieee80211_add_अगरace,
	.del_भव_पूर्णांकf = ieee80211_del_अगरace,
	.change_भव_पूर्णांकf = ieee80211_change_अगरace,
	.start_p2p_device = ieee80211_start_p2p_device,
	.stop_p2p_device = ieee80211_stop_p2p_device,
	.add_key = ieee80211_add_key,
	.del_key = ieee80211_del_key,
	.get_key = ieee80211_get_key,
	.set_शेष_key = ieee80211_config_शेष_key,
	.set_शेष_mgmt_key = ieee80211_config_शेष_mgmt_key,
	.set_शेष_beacon_key = ieee80211_config_शेष_beacon_key,
	.start_ap = ieee80211_start_ap,
	.change_beacon = ieee80211_change_beacon,
	.stop_ap = ieee80211_stop_ap,
	.add_station = ieee80211_add_station,
	.del_station = ieee80211_del_station,
	.change_station = ieee80211_change_station,
	.get_station = ieee80211_get_station,
	.dump_station = ieee80211_dump_station,
	.dump_survey = ieee80211_dump_survey,
#अगर_घोषित CONFIG_MAC80211_MESH
	.add_mpath = ieee80211_add_mpath,
	.del_mpath = ieee80211_del_mpath,
	.change_mpath = ieee80211_change_mpath,
	.get_mpath = ieee80211_get_mpath,
	.dump_mpath = ieee80211_dump_mpath,
	.get_mpp = ieee80211_get_mpp,
	.dump_mpp = ieee80211_dump_mpp,
	.update_mesh_config = ieee80211_update_mesh_config,
	.get_mesh_config = ieee80211_get_mesh_config,
	.join_mesh = ieee80211_join_mesh,
	.leave_mesh = ieee80211_leave_mesh,
#पूर्ण_अगर
	.join_ocb = ieee80211_join_ocb,
	.leave_ocb = ieee80211_leave_ocb,
	.change_bss = ieee80211_change_bss,
	.set_txq_params = ieee80211_set_txq_params,
	.set_monitor_channel = ieee80211_set_monitor_channel,
	.suspend = ieee80211_suspend,
	.resume = ieee80211_resume,
	.scan = ieee80211_scan,
	.पात_scan = ieee80211_पात_scan,
	.sched_scan_start = ieee80211_sched_scan_start,
	.sched_scan_stop = ieee80211_sched_scan_stop,
	.auth = ieee80211_auth,
	.assoc = ieee80211_assoc,
	.deauth = ieee80211_deauth,
	.disassoc = ieee80211_disassoc,
	.join_ibss = ieee80211_join_ibss,
	.leave_ibss = ieee80211_leave_ibss,
	.set_mcast_rate = ieee80211_set_mcast_rate,
	.set_wiphy_params = ieee80211_set_wiphy_params,
	.set_tx_घातer = ieee80211_set_tx_घातer,
	.get_tx_घातer = ieee80211_get_tx_घातer,
	.rfसमाप्त_poll = ieee80211_rfसमाप्त_poll,
	CFG80211_TESTMODE_CMD(ieee80211_tesपंचांगode_cmd)
	CFG80211_TESTMODE_DUMP(ieee80211_tesपंचांगode_dump)
	.set_घातer_mgmt = ieee80211_set_घातer_mgmt,
	.set_bitrate_mask = ieee80211_set_bitrate_mask,
	.reमुख्य_on_channel = ieee80211_reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel = ieee80211_cancel_reमुख्य_on_channel,
	.mgmt_tx = ieee80211_mgmt_tx,
	.mgmt_tx_cancel_रुको = ieee80211_mgmt_tx_cancel_रुको,
	.set_cqm_rssi_config = ieee80211_set_cqm_rssi_config,
	.set_cqm_rssi_range_config = ieee80211_set_cqm_rssi_range_config,
	.update_mgmt_frame_registrations =
		ieee80211_update_mgmt_frame_registrations,
	.set_antenna = ieee80211_set_antenna,
	.get_antenna = ieee80211_get_antenna,
	.set_rekey_data = ieee80211_set_rekey_data,
	.tdls_oper = ieee80211_tdls_oper,
	.tdls_mgmt = ieee80211_tdls_mgmt,
	.tdls_channel_चयन = ieee80211_tdls_channel_चयन,
	.tdls_cancel_channel_चयन = ieee80211_tdls_cancel_channel_चयन,
	.probe_client = ieee80211_probe_client,
	.set_noack_map = ieee80211_set_noack_map,
#अगर_घोषित CONFIG_PM
	.set_wakeup = ieee80211_set_wakeup,
#पूर्ण_अगर
	.get_channel = ieee80211_cfg_get_channel,
	.start_radar_detection = ieee80211_start_radar_detection,
	.end_cac = ieee80211_end_cac,
	.channel_चयन = ieee80211_channel_चयन,
	.set_qos_map = ieee80211_set_qos_map,
	.set_ap_chanwidth = ieee80211_set_ap_chanwidth,
	.add_tx_ts = ieee80211_add_tx_ts,
	.del_tx_ts = ieee80211_del_tx_ts,
	.start_nan = ieee80211_start_nan,
	.stop_nan = ieee80211_stop_nan,
	.nan_change_conf = ieee80211_nan_change_conf,
	.add_nan_func = ieee80211_add_nan_func,
	.del_nan_func = ieee80211_del_nan_func,
	.set_multicast_to_unicast = ieee80211_set_multicast_to_unicast,
	.tx_control_port = ieee80211_tx_control_port,
	.get_txq_stats = ieee80211_get_txq_stats,
	.get_fपंचांग_responder_stats = ieee80211_get_fपंचांग_responder_stats,
	.start_pmsr = ieee80211_start_pmsr,
	.पात_pmsr = ieee80211_पात_pmsr,
	.probe_mesh_link = ieee80211_probe_mesh_link,
	.set_tid_config = ieee80211_set_tid_config,
	.reset_tid_config = ieee80211_reset_tid_config,
	.set_sar_specs = ieee80211_set_sar_specs,
पूर्ण;
