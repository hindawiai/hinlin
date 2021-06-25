<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * Copyright 2002-2005, Instant802 Networks, Inc.
 * Copyright 2005-2006, Devicescape Software, Inc.
 * Copyright 2006-2007	Jiri Benc <jbenc@suse.cz>
 * Copyright 2007-2008	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright 2015-2017	Intel Deutschland GmbH
 * Copyright 2018-2020  Intel Corporation
 */

#समावेश <linux/अगर_ether.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/list.h>
#समावेश <linux/rcupdate.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/mac80211.h>
#समावेश <crypto/algapi.h>
#समावेश <यंत्र/unaligned.h>
#समावेश "ieee80211_i.h"
#समावेश "driver-ops.h"
#समावेश "debugfs_key.h"
#समावेश "aes_ccm.h"
#समावेश "aes_cmac.h"
#समावेश "aes_gmac.h"
#समावेश "aes_gcm.h"


/**
 * DOC: Key handling basics
 *
 * Key handling in mac80211 is करोne based on per-पूर्णांकerface (sub_अगर_data)
 * keys and per-station keys. Since each station beदीर्घs to an पूर्णांकerface,
 * each station key also beदीर्घs to that पूर्णांकerface.
 *
 * Hardware acceleration is करोne on a best-efक्रमt basis क्रम algorithms
 * that are implemented in software,  क्रम each key the hardware is asked
 * to enable that key क्रम offloading but अगर it cannot करो that the key is
 * simply kept क्रम software encryption (unless it is क्रम an algorithm
 * that isn't implemented in software).
 * There is currently no way of knowing whether a key is handled in SW
 * or HW except by looking पूर्णांकo debugfs.
 *
 * All key management is पूर्णांकernally रक्षित by a mutex. Within all
 * other parts of mac80211, key references are, just as STA काष्ठाure
 * references, रक्षित by RCU. Note, however, that some things are
 * unरक्षित, namely the key->sta dereferences within the hardware
 * acceleration functions. This means that sta_info_destroy() must
 * हटाओ the key which रुकोs क्रम an RCU grace period.
 */

अटल स्थिर u8 bcast_addr[ETH_ALEN] = अणु 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF पूर्ण;

अटल व्योम निश्चित_key_lock(काष्ठा ieee80211_local *local)
अणु
	lockdep_निश्चित_held(&local->key_mtx);
पूर्ण

अटल व्योम
update_vlan_tailroom_need_count(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक delta)
अणु
	काष्ठा ieee80211_sub_अगर_data *vlan;

	अगर (sdata->vअगर.type != NL80211_IFTYPE_AP)
		वापस;

	/* crypto_tx_tailroom_needed_cnt is रक्षित by this */
	निश्चित_key_lock(sdata->local);

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(vlan, &sdata->u.ap.vlans, u.vlan.list)
		vlan->crypto_tx_tailroom_needed_cnt += delta;

	rcu_पढ़ो_unlock();
पूर्ण

अटल व्योम increment_tailroom_need_count(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	/*
	 * When this count is zero, SKB resizing क्रम allocating tailroom
	 * क्रम IV or MMIC is skipped. But, this check has created two race
	 * हालs in xmit path जबतक transiting from zero count to one:
	 *
	 * 1. SKB resize was skipped because no key was added but just beक्रमe
	 * the xmit key is added and SW encryption kicks off.
	 *
	 * 2. SKB resize was skipped because all the keys were hw planted but
	 * just beक्रमe xmit one of the key is deleted and SW encryption kicks
	 * off.
	 *
	 * In both the above हाल SW encryption will find not enough space क्रम
	 * tailroom and निकासs with WARN_ON. (See WARN_ONs at wpa.c)
	 *
	 * Solution has been explained at
	 * http://mid.gmane.org/1308590980.4322.19.camel@jlt3.sipsolutions.net
	 */

	निश्चित_key_lock(sdata->local);

	update_vlan_tailroom_need_count(sdata, 1);

	अगर (!sdata->crypto_tx_tailroom_needed_cnt++) अणु
		/*
		 * Flush all XMIT packets currently using HW encryption or no
		 * encryption at all अगर the count transition is from 0 -> 1.
		 */
		synchronize_net();
	पूर्ण
पूर्ण

अटल व्योम decrease_tailroom_need_count(काष्ठा ieee80211_sub_अगर_data *sdata,
					 पूर्णांक delta)
अणु
	निश्चित_key_lock(sdata->local);

	WARN_ON_ONCE(sdata->crypto_tx_tailroom_needed_cnt < delta);

	update_vlan_tailroom_need_count(sdata, -delta);
	sdata->crypto_tx_tailroom_needed_cnt -= delta;
पूर्ण

अटल पूर्णांक ieee80211_key_enable_hw_accel(काष्ठा ieee80211_key *key)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = key->sdata;
	काष्ठा sta_info *sta;
	पूर्णांक ret = -EOPNOTSUPP;

	might_sleep();

	अगर (key->flags & KEY_FLAG_TAINTED) अणु
		/* If we get here, it's during resume and the key is
		 * taपूर्णांकed so shouldn't be used/programmed any more.
		 * However, its flags may still indicate that it was
		 * programmed पूर्णांकo the device (since we're in resume)
		 * so clear that flag now to aव्योम trying to हटाओ
		 * it again later.
		 */
		अगर (key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE &&
		    !(key->conf.flags & (IEEE80211_KEY_FLAG_GENERATE_MMIC |
					 IEEE80211_KEY_FLAG_PUT_MIC_SPACE |
					 IEEE80211_KEY_FLAG_RESERVE_TAILROOM)))
			increment_tailroom_need_count(sdata);

		key->flags &= ~KEY_FLAG_UPLOADED_TO_HARDWARE;
		वापस -EINVAL;
	पूर्ण

	अगर (!key->local->ops->set_key)
		जाओ out_unsupported;

	निश्चित_key_lock(key->local);

	sta = key->sta;

	/*
	 * If this is a per-STA GTK, check अगर it
	 * is supported; अगर not, वापस.
	 */
	अगर (sta && !(key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE) &&
	    !ieee80211_hw_check(&key->local->hw, SUPPORTS_PER_STA_GTK))
		जाओ out_unsupported;

	अगर (sta && !sta->uploaded)
		जाओ out_unsupported;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		/*
		 * The driver करोesn't know anything about VLAN पूर्णांकerfaces.
		 * Hence, करोn't send GTKs क्रम VLAN पूर्णांकerfaces to the driver.
		 */
		अगर (!(key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
			ret = 1;
			जाओ out_unsupported;
		पूर्ण
	पूर्ण

	ret = drv_set_key(key->local, SET_KEY, sdata,
			  sta ? &sta->sta : शून्य, &key->conf);

	अगर (!ret) अणु
		key->flags |= KEY_FLAG_UPLOADED_TO_HARDWARE;

		अगर (!(key->conf.flags & (IEEE80211_KEY_FLAG_GENERATE_MMIC |
					 IEEE80211_KEY_FLAG_PUT_MIC_SPACE |
					 IEEE80211_KEY_FLAG_RESERVE_TAILROOM)))
			decrease_tailroom_need_count(sdata, 1);

		WARN_ON((key->conf.flags & IEEE80211_KEY_FLAG_PUT_IV_SPACE) &&
			(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_IV));

		WARN_ON((key->conf.flags & IEEE80211_KEY_FLAG_PUT_MIC_SPACE) &&
			(key->conf.flags & IEEE80211_KEY_FLAG_GENERATE_MMIC));

		वापस 0;
	पूर्ण

	अगर (ret != -ENOSPC && ret != -EOPNOTSUPP && ret != 1)
		sdata_err(sdata,
			  "failed to set key (%d, %pM) to hardware (%d)\n",
			  key->conf.keyidx,
			  sta ? sta->sta.addr : bcast_addr, ret);

 out_unsupported:
	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
	हाल WLAN_CIPHER_SUITE_TKIP:
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		/* all of these we can करो in software - अगर driver can */
		अगर (ret == 1)
			वापस 0;
		अगर (ieee80211_hw_check(&key->local->hw, SW_CRYPTO_CONTROL))
			वापस -EINVAL;
		वापस 0;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल व्योम ieee80211_key_disable_hw_accel(काष्ठा ieee80211_key *key)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;
	काष्ठा sta_info *sta;
	पूर्णांक ret;

	might_sleep();

	अगर (!key || !key->local->ops->set_key)
		वापस;

	निश्चित_key_lock(key->local);

	अगर (!(key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE))
		वापस;

	sta = key->sta;
	sdata = key->sdata;

	अगर (!(key->conf.flags & (IEEE80211_KEY_FLAG_GENERATE_MMIC |
				 IEEE80211_KEY_FLAG_PUT_MIC_SPACE |
				 IEEE80211_KEY_FLAG_RESERVE_TAILROOM)))
		increment_tailroom_need_count(sdata);

	key->flags &= ~KEY_FLAG_UPLOADED_TO_HARDWARE;
	ret = drv_set_key(key->local, DISABLE_KEY, sdata,
			  sta ? &sta->sta : शून्य, &key->conf);

	अगर (ret)
		sdata_err(sdata,
			  "failed to remove key (%d, %pM) from hardware (%d)\n",
			  key->conf.keyidx,
			  sta ? sta->sta.addr : bcast_addr, ret);
पूर्ण

अटल पूर्णांक _ieee80211_set_tx_key(काष्ठा ieee80211_key *key, bool क्रमce)
अणु
	काष्ठा sta_info *sta = key->sta;
	काष्ठा ieee80211_local *local = key->local;

	निश्चित_key_lock(local);

	set_sta_flag(sta, WLAN_STA_USES_ENCRYPTION);

	sta->ptk_idx = key->conf.keyidx;

	अगर (क्रमce || !ieee80211_hw_check(&local->hw, AMPDU_KEYBORDER_SUPPORT))
		clear_sta_flag(sta, WLAN_STA_BLOCK_BA);
	ieee80211_check_fast_xmit(sta);

	वापस 0;
पूर्ण

पूर्णांक ieee80211_set_tx_key(काष्ठा ieee80211_key *key)
अणु
	वापस _ieee80211_set_tx_key(key, false);
पूर्ण

अटल व्योम ieee80211_pairwise_rekey(काष्ठा ieee80211_key *old,
				     काष्ठा ieee80211_key *new)
अणु
	काष्ठा ieee80211_local *local = new->local;
	काष्ठा sta_info *sta = new->sta;
	पूर्णांक i;

	निश्चित_key_lock(local);

	अगर (new->conf.flags & IEEE80211_KEY_FLAG_NO_AUTO_TX) अणु
		/* Extended Key ID key install, initial one or rekey */

		अगर (sta->ptk_idx != INVALID_PTK_KEYIDX &&
		    !ieee80211_hw_check(&local->hw, AMPDU_KEYBORDER_SUPPORT)) अणु
			/* Aggregation Sessions with Extended Key ID must not
			 * mix MPDUs with dअगरferent keyIDs within one A-MPDU.
			 * Tear करोwn running Tx aggregation sessions and block
			 * new Rx/Tx aggregation requests during rekey to
			 * ensure there are no A-MPDUs when the driver is not
			 * supporting A-MPDU key borders. (Blocking Tx only
			 * would be sufficient but WLAN_STA_BLOCK_BA माला_लो the
			 * job करोne क्रम the few ms we need it.)
			 */
			set_sta_flag(sta, WLAN_STA_BLOCK_BA);
			mutex_lock(&sta->ampdu_mlme.mtx);
			क्रम (i = 0; i <  IEEE80211_NUM_TIDS; i++)
				___ieee80211_stop_tx_ba_session(sta, i,
								AGG_STOP_LOCAL_REQUEST);
			mutex_unlock(&sta->ampdu_mlme.mtx);
		पूर्ण
	पूर्ण अन्यथा अगर (old) अणु
		/* Rekey without Extended Key ID.
		 * Aggregation sessions are OK when running on SW crypto.
		 * A broken remote STA may cause issues not observed with HW
		 * crypto, though.
		 */
		अगर (!(old->flags & KEY_FLAG_UPLOADED_TO_HARDWARE))
			वापस;

		/* Stop Tx till we are on the new key */
		old->flags |= KEY_FLAG_TAINTED;
		ieee80211_clear_fast_xmit(sta);
		अगर (ieee80211_hw_check(&local->hw, AMPDU_AGGREGATION)) अणु
			set_sta_flag(sta, WLAN_STA_BLOCK_BA);
			ieee80211_sta_tear_करोwn_BA_sessions(sta,
							    AGG_STOP_LOCAL_REQUEST);
		पूर्ण
		अगर (!wiphy_ext_feature_isset(local->hw.wiphy,
					     NL80211_EXT_FEATURE_CAN_REPLACE_PTK0)) अणु
			pr_warn_ratelimited("Rekeying PTK for STA %pM but driver can't safely do that.",
					    sta->sta.addr);
			/* Flushing the driver queues *may* help prevent
			 * the clear text leaks and मुक्तzes.
			 */
			ieee80211_flush_queues(local, old->sdata, false);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम __ieee80211_set_शेष_key(काष्ठा ieee80211_sub_अगर_data *sdata,
					पूर्णांक idx, bool uni, bool multi)
अणु
	काष्ठा ieee80211_key *key = शून्य;

	निश्चित_key_lock(sdata->local);

	अगर (idx >= 0 && idx < NUM_DEFAULT_KEYS)
		key = key_mtx_dereference(sdata->local, sdata->keys[idx]);

	अगर (uni) अणु
		rcu_assign_poपूर्णांकer(sdata->शेष_unicast_key, key);
		ieee80211_check_fast_xmit_अगरace(sdata);
		अगर (sdata->vअगर.type != NL80211_IFTYPE_AP_VLAN)
			drv_set_शेष_unicast_key(sdata->local, sdata, idx);
	पूर्ण

	अगर (multi)
		rcu_assign_poपूर्णांकer(sdata->शेष_multicast_key, key);

	ieee80211_debugfs_key_update_शेष(sdata);
पूर्ण

व्योम ieee80211_set_शेष_key(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक idx,
			       bool uni, bool multi)
अणु
	mutex_lock(&sdata->local->key_mtx);
	__ieee80211_set_शेष_key(sdata, idx, uni, multi);
	mutex_unlock(&sdata->local->key_mtx);
पूर्ण

अटल व्योम
__ieee80211_set_शेष_mgmt_key(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक idx)
अणु
	काष्ठा ieee80211_key *key = शून्य;

	निश्चित_key_lock(sdata->local);

	अगर (idx >= NUM_DEFAULT_KEYS &&
	    idx < NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS)
		key = key_mtx_dereference(sdata->local, sdata->keys[idx]);

	rcu_assign_poपूर्णांकer(sdata->शेष_mgmt_key, key);

	ieee80211_debugfs_key_update_शेष(sdata);
पूर्ण

व्योम ieee80211_set_शेष_mgmt_key(काष्ठा ieee80211_sub_अगर_data *sdata,
				    पूर्णांक idx)
अणु
	mutex_lock(&sdata->local->key_mtx);
	__ieee80211_set_शेष_mgmt_key(sdata, idx);
	mutex_unlock(&sdata->local->key_mtx);
पूर्ण

अटल व्योम
__ieee80211_set_शेष_beacon_key(काष्ठा ieee80211_sub_अगर_data *sdata, पूर्णांक idx)
अणु
	काष्ठा ieee80211_key *key = शून्य;

	निश्चित_key_lock(sdata->local);

	अगर (idx >= NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS &&
	    idx < NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS +
	    NUM_DEFAULT_BEACON_KEYS)
		key = key_mtx_dereference(sdata->local, sdata->keys[idx]);

	rcu_assign_poपूर्णांकer(sdata->शेष_beacon_key, key);

	ieee80211_debugfs_key_update_शेष(sdata);
पूर्ण

व्योम ieee80211_set_शेष_beacon_key(काष्ठा ieee80211_sub_अगर_data *sdata,
				      पूर्णांक idx)
अणु
	mutex_lock(&sdata->local->key_mtx);
	__ieee80211_set_शेष_beacon_key(sdata, idx);
	mutex_unlock(&sdata->local->key_mtx);
पूर्ण

अटल पूर्णांक ieee80211_key_replace(काष्ठा ieee80211_sub_अगर_data *sdata,
				  काष्ठा sta_info *sta,
				  bool pairwise,
				  काष्ठा ieee80211_key *old,
				  काष्ठा ieee80211_key *new)
अणु
	पूर्णांक idx;
	पूर्णांक ret = 0;
	bool defunikey, defmultikey, defmgmtkey, defbeaconkey;

	/* caller must provide at least one old/new */
	अगर (WARN_ON(!new && !old))
		वापस 0;

	अगर (new)
		list_add_tail_rcu(&new->list, &sdata->key_list);

	WARN_ON(new && old && new->conf.keyidx != old->conf.keyidx);

	अगर (new && sta && pairwise) अणु
		/* Unicast rekey needs special handling. With Extended Key ID
		 * old is still शून्य क्रम the first rekey.
		 */
		ieee80211_pairwise_rekey(old, new);
	पूर्ण

	अगर (old) अणु
		idx = old->conf.keyidx;

		अगर (old->flags & KEY_FLAG_UPLOADED_TO_HARDWARE) अणु
			ieee80211_key_disable_hw_accel(old);

			अगर (new)
				ret = ieee80211_key_enable_hw_accel(new);
		पूर्ण
	पूर्ण अन्यथा अणु
		/* new must be provided in हाल old is not */
		idx = new->conf.keyidx;
		अगर (!new->local->wowlan)
			ret = ieee80211_key_enable_hw_accel(new);
	पूर्ण

	अगर (ret)
		वापस ret;

	अगर (sta) अणु
		अगर (pairwise) अणु
			rcu_assign_poपूर्णांकer(sta->ptk[idx], new);
			अगर (new &&
			    !(new->conf.flags & IEEE80211_KEY_FLAG_NO_AUTO_TX))
				_ieee80211_set_tx_key(new, true);
		पूर्ण अन्यथा अणु
			rcu_assign_poपूर्णांकer(sta->gtk[idx], new);
		पूर्ण
		/* Only needed क्रम transition from no key -> key.
		 * Still triggers unnecessary when using Extended Key ID
		 * and installing the second key ID the first समय.
		 */
		अगर (new && !old)
			ieee80211_check_fast_rx(sta);
	पूर्ण अन्यथा अणु
		defunikey = old &&
			old == key_mtx_dereference(sdata->local,
						sdata->शेष_unicast_key);
		defmultikey = old &&
			old == key_mtx_dereference(sdata->local,
						sdata->शेष_multicast_key);
		defmgmtkey = old &&
			old == key_mtx_dereference(sdata->local,
						sdata->शेष_mgmt_key);
		defbeaconkey = old &&
			old == key_mtx_dereference(sdata->local,
						   sdata->शेष_beacon_key);

		अगर (defunikey && !new)
			__ieee80211_set_शेष_key(sdata, -1, true, false);
		अगर (defmultikey && !new)
			__ieee80211_set_शेष_key(sdata, -1, false, true);
		अगर (defmgmtkey && !new)
			__ieee80211_set_शेष_mgmt_key(sdata, -1);
		अगर (defbeaconkey && !new)
			__ieee80211_set_शेष_beacon_key(sdata, -1);

		rcu_assign_poपूर्णांकer(sdata->keys[idx], new);
		अगर (defunikey && new)
			__ieee80211_set_शेष_key(sdata, new->conf.keyidx,
						    true, false);
		अगर (defmultikey && new)
			__ieee80211_set_शेष_key(sdata, new->conf.keyidx,
						    false, true);
		अगर (defmgmtkey && new)
			__ieee80211_set_शेष_mgmt_key(sdata,
							 new->conf.keyidx);
		अगर (defbeaconkey && new)
			__ieee80211_set_शेष_beacon_key(sdata,
							   new->conf.keyidx);
	पूर्ण

	अगर (old)
		list_del_rcu(&old->list);

	वापस 0;
पूर्ण

काष्ठा ieee80211_key *
ieee80211_key_alloc(u32 cipher, पूर्णांक idx, माप_प्रकार key_len,
		    स्थिर u8 *key_data,
		    माप_प्रकार seq_len, स्थिर u8 *seq,
		    स्थिर काष्ठा ieee80211_cipher_scheme *cs)
अणु
	काष्ठा ieee80211_key *key;
	पूर्णांक i, j, err;

	अगर (WARN_ON(idx < 0 ||
		    idx >= NUM_DEFAULT_KEYS + NUM_DEFAULT_MGMT_KEYS +
		    NUM_DEFAULT_BEACON_KEYS))
		वापस ERR_PTR(-EINVAL);

	key = kzalloc(माप(काष्ठा ieee80211_key) + key_len, GFP_KERNEL);
	अगर (!key)
		वापस ERR_PTR(-ENOMEM);

	/*
	 * Default to software encryption; we'll later upload the
	 * key to the hardware अगर possible.
	 */
	key->conf.flags = 0;
	key->flags = 0;

	key->conf.cipher = cipher;
	key->conf.keyidx = idx;
	key->conf.keylen = key_len;
	चयन (cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
	हाल WLAN_CIPHER_SUITE_WEP104:
		key->conf.iv_len = IEEE80211_WEP_IV_LEN;
		key->conf.icv_len = IEEE80211_WEP_ICV_LEN;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		key->conf.iv_len = IEEE80211_TKIP_IV_LEN;
		key->conf.icv_len = IEEE80211_TKIP_ICV_LEN;
		अगर (seq) अणु
			क्रम (i = 0; i < IEEE80211_NUM_TIDS; i++) अणु
				key->u.tkip.rx[i].iv32 =
					get_unaligned_le32(&seq[2]);
				key->u.tkip.rx[i].iv16 =
					get_unaligned_le16(seq);
			पूर्ण
		पूर्ण
		spin_lock_init(&key->u.tkip.txlock);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		key->conf.iv_len = IEEE80211_CCMP_HDR_LEN;
		key->conf.icv_len = IEEE80211_CCMP_MIC_LEN;
		अगर (seq) अणु
			क्रम (i = 0; i < IEEE80211_NUM_TIDS + 1; i++)
				क्रम (j = 0; j < IEEE80211_CCMP_PN_LEN; j++)
					key->u.ccmp.rx_pn[i][j] =
						seq[IEEE80211_CCMP_PN_LEN - j - 1];
		पूर्ण
		/*
		 * Initialize AES key state here as an optimization so that
		 * it करोes not need to be initialized क्रम every packet.
		 */
		key->u.ccmp.tfm = ieee80211_aes_key_setup_encrypt(
			key_data, key_len, IEEE80211_CCMP_MIC_LEN);
		अगर (IS_ERR(key->u.ccmp.tfm)) अणु
			err = PTR_ERR(key->u.ccmp.tfm);
			kमुक्त(key);
			वापस ERR_PTR(err);
		पूर्ण
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		key->conf.iv_len = IEEE80211_CCMP_256_HDR_LEN;
		key->conf.icv_len = IEEE80211_CCMP_256_MIC_LEN;
		क्रम (i = 0; seq && i < IEEE80211_NUM_TIDS + 1; i++)
			क्रम (j = 0; j < IEEE80211_CCMP_256_PN_LEN; j++)
				key->u.ccmp.rx_pn[i][j] =
					seq[IEEE80211_CCMP_256_PN_LEN - j - 1];
		/* Initialize AES key state here as an optimization so that
		 * it करोes not need to be initialized क्रम every packet.
		 */
		key->u.ccmp.tfm = ieee80211_aes_key_setup_encrypt(
			key_data, key_len, IEEE80211_CCMP_256_MIC_LEN);
		अगर (IS_ERR(key->u.ccmp.tfm)) अणु
			err = PTR_ERR(key->u.ccmp.tfm);
			kमुक्त(key);
			वापस ERR_PTR(err);
		पूर्ण
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		key->conf.iv_len = 0;
		अगर (cipher == WLAN_CIPHER_SUITE_AES_CMAC)
			key->conf.icv_len = माप(काष्ठा ieee80211_mmie);
		अन्यथा
			key->conf.icv_len = माप(काष्ठा ieee80211_mmie_16);
		अगर (seq)
			क्रम (j = 0; j < IEEE80211_CMAC_PN_LEN; j++)
				key->u.aes_cmac.rx_pn[j] =
					seq[IEEE80211_CMAC_PN_LEN - j - 1];
		/*
		 * Initialize AES key state here as an optimization so that
		 * it करोes not need to be initialized क्रम every packet.
		 */
		key->u.aes_cmac.tfm =
			ieee80211_aes_cmac_key_setup(key_data, key_len);
		अगर (IS_ERR(key->u.aes_cmac.tfm)) अणु
			err = PTR_ERR(key->u.aes_cmac.tfm);
			kमुक्त(key);
			वापस ERR_PTR(err);
		पूर्ण
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		key->conf.iv_len = 0;
		key->conf.icv_len = माप(काष्ठा ieee80211_mmie_16);
		अगर (seq)
			क्रम (j = 0; j < IEEE80211_GMAC_PN_LEN; j++)
				key->u.aes_gmac.rx_pn[j] =
					seq[IEEE80211_GMAC_PN_LEN - j - 1];
		/* Initialize AES key state here as an optimization so that
		 * it करोes not need to be initialized क्रम every packet.
		 */
		key->u.aes_gmac.tfm =
			ieee80211_aes_gmac_key_setup(key_data, key_len);
		अगर (IS_ERR(key->u.aes_gmac.tfm)) अणु
			err = PTR_ERR(key->u.aes_gmac.tfm);
			kमुक्त(key);
			वापस ERR_PTR(err);
		पूर्ण
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		key->conf.iv_len = IEEE80211_GCMP_HDR_LEN;
		key->conf.icv_len = IEEE80211_GCMP_MIC_LEN;
		क्रम (i = 0; seq && i < IEEE80211_NUM_TIDS + 1; i++)
			क्रम (j = 0; j < IEEE80211_GCMP_PN_LEN; j++)
				key->u.gcmp.rx_pn[i][j] =
					seq[IEEE80211_GCMP_PN_LEN - j - 1];
		/* Initialize AES key state here as an optimization so that
		 * it करोes not need to be initialized क्रम every packet.
		 */
		key->u.gcmp.tfm = ieee80211_aes_gcm_key_setup_encrypt(key_data,
								      key_len);
		अगर (IS_ERR(key->u.gcmp.tfm)) अणु
			err = PTR_ERR(key->u.gcmp.tfm);
			kमुक्त(key);
			वापस ERR_PTR(err);
		पूर्ण
		अवरोध;
	शेष:
		अगर (cs) अणु
			अगर (seq_len && seq_len != cs->pn_len) अणु
				kमुक्त(key);
				वापस ERR_PTR(-EINVAL);
			पूर्ण

			key->conf.iv_len = cs->hdr_len;
			key->conf.icv_len = cs->mic_len;
			क्रम (i = 0; i < IEEE80211_NUM_TIDS + 1; i++)
				क्रम (j = 0; j < seq_len; j++)
					key->u.gen.rx_pn[i][j] =
							seq[seq_len - j - 1];
			key->flags |= KEY_FLAG_CIPHER_SCHEME;
		पूर्ण
	पूर्ण
	स_नकल(key->conf.key, key_data, key_len);
	INIT_LIST_HEAD(&key->list);

	वापस key;
पूर्ण

अटल व्योम ieee80211_key_मुक्त_common(काष्ठा ieee80211_key *key)
अणु
	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		ieee80211_aes_key_मुक्त(key->u.ccmp.tfm);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		ieee80211_aes_cmac_key_मुक्त(key->u.aes_cmac.tfm);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		ieee80211_aes_gmac_key_मुक्त(key->u.aes_gmac.tfm);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		ieee80211_aes_gcm_key_मुक्त(key->u.gcmp.tfm);
		अवरोध;
	पूर्ण
	kमुक्त_sensitive(key);
पूर्ण

अटल व्योम __ieee80211_key_destroy(काष्ठा ieee80211_key *key,
				    bool delay_tailroom)
अणु
	अगर (key->local) अणु
		काष्ठा ieee80211_sub_अगर_data *sdata = key->sdata;

		ieee80211_debugfs_key_हटाओ(key);

		अगर (delay_tailroom) अणु
			/* see ieee80211_delayed_tailroom_dec */
			sdata->crypto_tx_tailroom_pending_dec++;
			schedule_delayed_work(&sdata->dec_tailroom_needed_wk,
					      HZ/2);
		पूर्ण अन्यथा अणु
			decrease_tailroom_need_count(sdata, 1);
		पूर्ण
	पूर्ण

	ieee80211_key_मुक्त_common(key);
पूर्ण

अटल व्योम ieee80211_key_destroy(काष्ठा ieee80211_key *key,
				  bool delay_tailroom)
अणु
	अगर (!key)
		वापस;

	/*
	 * Synchronize so the TX path and rcu key iterators
	 * can no दीर्घer be using this key beक्रमe we मुक्त/हटाओ it.
	 */
	synchronize_net();

	__ieee80211_key_destroy(key, delay_tailroom);
पूर्ण

व्योम ieee80211_key_मुक्त_unused(काष्ठा ieee80211_key *key)
अणु
	WARN_ON(key->sdata || key->local);
	ieee80211_key_मुक्त_common(key);
पूर्ण

अटल bool ieee80211_key_identical(काष्ठा ieee80211_sub_अगर_data *sdata,
				    काष्ठा ieee80211_key *old,
				    काष्ठा ieee80211_key *new)
अणु
	u8 tkip_old[WLAN_KEY_LEN_TKIP], tkip_new[WLAN_KEY_LEN_TKIP];
	u8 *tk_old, *tk_new;

	अगर (!old || new->conf.keylen != old->conf.keylen)
		वापस false;

	tk_old = old->conf.key;
	tk_new = new->conf.key;

	/*
	 * In station mode, करोn't compare the TX MIC key, as it's never used
	 * and offloaded rekeying may not care to send it to the host. This
	 * is the हाल in iwlwअगरi, क्रम example.
	 */
	अगर (sdata->vअगर.type == NL80211_IFTYPE_STATION &&
	    new->conf.cipher == WLAN_CIPHER_SUITE_TKIP &&
	    new->conf.keylen == WLAN_KEY_LEN_TKIP &&
	    !(new->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE)) अणु
		स_नकल(tkip_old, tk_old, WLAN_KEY_LEN_TKIP);
		स_नकल(tkip_new, tk_new, WLAN_KEY_LEN_TKIP);
		स_रखो(tkip_old + NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY, 0, 8);
		स_रखो(tkip_new + NL80211_TKIP_DATA_OFFSET_TX_MIC_KEY, 0, 8);
		tk_old = tkip_old;
		tk_new = tkip_new;
	पूर्ण

	वापस !crypto_memneq(tk_old, tk_new, new->conf.keylen);
पूर्ण

पूर्णांक ieee80211_key_link(काष्ठा ieee80211_key *key,
		       काष्ठा ieee80211_sub_अगर_data *sdata,
		       काष्ठा sta_info *sta)
अणु
	अटल atomic_t key_color = ATOMIC_INIT(0);
	काष्ठा ieee80211_key *old_key;
	पूर्णांक idx = key->conf.keyidx;
	bool pairwise = key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE;
	/*
	 * We want to delay tailroom updates only क्रम station - in that
	 * हाल it helps roaming speed, but in other हालs it hurts and
	 * can cause warnings to appear.
	 */
	bool delay_tailroom = sdata->vअगर.type == NL80211_IFTYPE_STATION;
	पूर्णांक ret = -EOPNOTSUPP;

	mutex_lock(&sdata->local->key_mtx);

	अगर (sta && pairwise) अणु
		काष्ठा ieee80211_key *alt_key;

		old_key = key_mtx_dereference(sdata->local, sta->ptk[idx]);
		alt_key = key_mtx_dereference(sdata->local, sta->ptk[idx ^ 1]);

		/* The rekey code assumes that the old and new key are using
		 * the same cipher. Enक्रमce the assumption क्रम pairwise keys.
		 */
		अगर ((alt_key && alt_key->conf.cipher != key->conf.cipher) ||
		    (old_key && old_key->conf.cipher != key->conf.cipher))
			जाओ out;
	पूर्ण अन्यथा अगर (sta) अणु
		old_key = key_mtx_dereference(sdata->local, sta->gtk[idx]);
	पूर्ण अन्यथा अणु
		old_key = key_mtx_dereference(sdata->local, sdata->keys[idx]);
	पूर्ण

	/* Non-pairwise keys must also not चयन the cipher on rekey */
	अगर (!pairwise) अणु
		अगर (old_key && old_key->conf.cipher != key->conf.cipher)
			जाओ out;
	पूर्ण

	/*
	 * Silently accept key re-installation without really installing the
	 * new version of the key to aव्योम nonce reuse or replay issues.
	 */
	अगर (ieee80211_key_identical(sdata, old_key, key)) अणु
		ieee80211_key_मुक्त_unused(key);
		ret = 0;
		जाओ out;
	पूर्ण

	key->local = sdata->local;
	key->sdata = sdata;
	key->sta = sta;

	/*
	 * Assign a unique ID to every key so we can easily prevent mixed
	 * key and fragment cache attacks.
	 */
	key->color = atomic_inc_वापस(&key_color);

	increment_tailroom_need_count(sdata);

	ret = ieee80211_key_replace(sdata, sta, pairwise, old_key, key);

	अगर (!ret) अणु
		ieee80211_debugfs_key_add(key);
		ieee80211_key_destroy(old_key, delay_tailroom);
	पूर्ण अन्यथा अणु
		ieee80211_key_मुक्त(key, delay_tailroom);
	पूर्ण

 out:
	mutex_unlock(&sdata->local->key_mtx);

	वापस ret;
पूर्ण

व्योम ieee80211_key_मुक्त(काष्ठा ieee80211_key *key, bool delay_tailroom)
अणु
	अगर (!key)
		वापस;

	/*
	 * Replace key with nothingness अगर it was ever used.
	 */
	अगर (key->sdata)
		ieee80211_key_replace(key->sdata, key->sta,
				key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE,
				key, शून्य);
	ieee80211_key_destroy(key, delay_tailroom);
पूर्ण

व्योम ieee80211_reenable_keys(काष्ठा ieee80211_sub_अगर_data *sdata)
अणु
	काष्ठा ieee80211_key *key;
	काष्ठा ieee80211_sub_अगर_data *vlan;

	lockdep_निश्चित_wiphy(sdata->local->hw.wiphy);

	mutex_lock(&sdata->local->key_mtx);

	sdata->crypto_tx_tailroom_needed_cnt = 0;
	sdata->crypto_tx_tailroom_pending_dec = 0;

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		list_क्रम_each_entry(vlan, &sdata->u.ap.vlans, u.vlan.list) अणु
			vlan->crypto_tx_tailroom_needed_cnt = 0;
			vlan->crypto_tx_tailroom_pending_dec = 0;
		पूर्ण
	पूर्ण

	अगर (ieee80211_sdata_running(sdata)) अणु
		list_क्रम_each_entry(key, &sdata->key_list, list) अणु
			increment_tailroom_need_count(sdata);
			ieee80211_key_enable_hw_accel(key);
		पूर्ण
	पूर्ण

	mutex_unlock(&sdata->local->key_mtx);
पूर्ण

व्योम ieee80211_iter_keys(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_vअगर *vअगर,
			 व्योम (*iter)(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा ieee80211_key_conf *key,
				      व्योम *data),
			 व्योम *iter_data)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_key *key, *पंचांगp;
	काष्ठा ieee80211_sub_अगर_data *sdata;

	lockdep_निश्चित_wiphy(hw->wiphy);

	mutex_lock(&local->key_mtx);
	अगर (vअगर) अणु
		sdata = vअगर_to_sdata(vअगर);
		list_क्रम_each_entry_safe(key, पंचांगp, &sdata->key_list, list)
			iter(hw, &sdata->vअगर,
			     key->sta ? &key->sta->sta : शून्य,
			     &key->conf, iter_data);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry(sdata, &local->पूर्णांकerfaces, list)
			list_क्रम_each_entry_safe(key, पंचांगp,
						 &sdata->key_list, list)
				iter(hw, &sdata->vअगर,
				     key->sta ? &key->sta->sta : शून्य,
				     &key->conf, iter_data);
	पूर्ण
	mutex_unlock(&local->key_mtx);
पूर्ण
EXPORT_SYMBOL(ieee80211_iter_keys);

अटल व्योम
_ieee80211_iter_keys_rcu(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_sub_अगर_data *sdata,
			 व्योम (*iter)(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा ieee80211_key_conf *key,
				      व्योम *data),
			 व्योम *iter_data)
अणु
	काष्ठा ieee80211_key *key;

	list_क्रम_each_entry_rcu(key, &sdata->key_list, list) अणु
		/* skip keys of station in removal process */
		अगर (key->sta && key->sta->हटाओd)
			जारी;
		अगर (!(key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE))
			जारी;

		iter(hw, &sdata->vअगर,
		     key->sta ? &key->sta->sta : शून्य,
		     &key->conf, iter_data);
	पूर्ण
पूर्ण

व्योम ieee80211_iter_keys_rcu(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     व्योम (*iter)(काष्ठा ieee80211_hw *hw,
					  काष्ठा ieee80211_vअगर *vअगर,
					  काष्ठा ieee80211_sta *sta,
					  काष्ठा ieee80211_key_conf *key,
					  व्योम *data),
			     व्योम *iter_data)
अणु
	काष्ठा ieee80211_local *local = hw_to_local(hw);
	काष्ठा ieee80211_sub_अगर_data *sdata;

	अगर (vअगर) अणु
		sdata = vअगर_to_sdata(vअगर);
		_ieee80211_iter_keys_rcu(hw, sdata, iter, iter_data);
	पूर्ण अन्यथा अणु
		list_क्रम_each_entry_rcu(sdata, &local->पूर्णांकerfaces, list)
			_ieee80211_iter_keys_rcu(hw, sdata, iter, iter_data);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ieee80211_iter_keys_rcu);

अटल व्योम ieee80211_मुक्त_keys_अगरace(काष्ठा ieee80211_sub_अगर_data *sdata,
				      काष्ठा list_head *keys)
अणु
	काष्ठा ieee80211_key *key, *पंचांगp;

	decrease_tailroom_need_count(sdata,
				     sdata->crypto_tx_tailroom_pending_dec);
	sdata->crypto_tx_tailroom_pending_dec = 0;

	ieee80211_debugfs_key_हटाओ_mgmt_शेष(sdata);
	ieee80211_debugfs_key_हटाओ_beacon_शेष(sdata);

	list_क्रम_each_entry_safe(key, पंचांगp, &sdata->key_list, list) अणु
		ieee80211_key_replace(key->sdata, key->sta,
				key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE,
				key, शून्य);
		list_add_tail(&key->list, keys);
	पूर्ण

	ieee80211_debugfs_key_update_शेष(sdata);
पूर्ण

व्योम ieee80211_मुक्त_keys(काष्ठा ieee80211_sub_अगर_data *sdata,
			 bool क्रमce_synchronize)
अणु
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_sub_अगर_data *vlan;
	काष्ठा ieee80211_sub_अगर_data *master;
	काष्ठा ieee80211_key *key, *पंचांगp;
	LIST_HEAD(keys);

	cancel_delayed_work_sync(&sdata->dec_tailroom_needed_wk);

	mutex_lock(&local->key_mtx);

	ieee80211_मुक्त_keys_अगरace(sdata, &keys);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		list_क्रम_each_entry(vlan, &sdata->u.ap.vlans, u.vlan.list)
			ieee80211_मुक्त_keys_अगरace(vlan, &keys);
	पूर्ण

	अगर (!list_empty(&keys) || क्रमce_synchronize)
		synchronize_net();
	list_क्रम_each_entry_safe(key, पंचांगp, &keys, list)
		__ieee80211_key_destroy(key, false);

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP_VLAN) अणु
		अगर (sdata->bss) अणु
			master = container_of(sdata->bss,
					      काष्ठा ieee80211_sub_अगर_data,
					      u.ap);

			WARN_ON_ONCE(sdata->crypto_tx_tailroom_needed_cnt !=
				     master->crypto_tx_tailroom_needed_cnt);
		पूर्ण
	पूर्ण अन्यथा अणु
		WARN_ON_ONCE(sdata->crypto_tx_tailroom_needed_cnt ||
			     sdata->crypto_tx_tailroom_pending_dec);
	पूर्ण

	अगर (sdata->vअगर.type == NL80211_IFTYPE_AP) अणु
		list_क्रम_each_entry(vlan, &sdata->u.ap.vlans, u.vlan.list)
			WARN_ON_ONCE(vlan->crypto_tx_tailroom_needed_cnt ||
				     vlan->crypto_tx_tailroom_pending_dec);
	पूर्ण

	mutex_unlock(&local->key_mtx);
पूर्ण

व्योम ieee80211_मुक्त_sta_keys(काष्ठा ieee80211_local *local,
			     काष्ठा sta_info *sta)
अणु
	काष्ठा ieee80211_key *key;
	पूर्णांक i;

	mutex_lock(&local->key_mtx);
	क्रम (i = 0; i < ARRAY_SIZE(sta->gtk); i++) अणु
		key = key_mtx_dereference(local, sta->gtk[i]);
		अगर (!key)
			जारी;
		ieee80211_key_replace(key->sdata, key->sta,
				key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE,
				key, शून्य);
		__ieee80211_key_destroy(key, key->sdata->vअगर.type ==
					NL80211_IFTYPE_STATION);
	पूर्ण

	क्रम (i = 0; i < NUM_DEFAULT_KEYS; i++) अणु
		key = key_mtx_dereference(local, sta->ptk[i]);
		अगर (!key)
			जारी;
		ieee80211_key_replace(key->sdata, key->sta,
				key->conf.flags & IEEE80211_KEY_FLAG_PAIRWISE,
				key, शून्य);
		__ieee80211_key_destroy(key, key->sdata->vअगर.type ==
					NL80211_IFTYPE_STATION);
	पूर्ण

	mutex_unlock(&local->key_mtx);
पूर्ण

व्योम ieee80211_delayed_tailroom_dec(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata;

	sdata = container_of(wk, काष्ठा ieee80211_sub_अगर_data,
			     dec_tailroom_needed_wk.work);

	/*
	 * The reason क्रम the delayed tailroom needed decrementing is to
	 * make roaming faster: during roaming, all keys are first deleted
	 * and then new keys are installed. The first new key causes the
	 * crypto_tx_tailroom_needed_cnt to go from 0 to 1, which invokes
	 * the cost of synchronize_net() (which can be slow). Aव्योम this
	 * by deferring the crypto_tx_tailroom_needed_cnt decrementing on
	 * key removal क्रम a जबतक, so अगर we roam the value is larger than
	 * zero and no 0->1 transition happens.
	 *
	 * The cost is that अगर the AP चयनing was from an AP with keys
	 * to one without, we still allocate tailroom जबतक it would no
	 * दीर्घer be needed. However, in the typical (fast) roaming हाल
	 * within an ESS this usually won't happen.
	 */

	mutex_lock(&sdata->local->key_mtx);
	decrease_tailroom_need_count(sdata,
				     sdata->crypto_tx_tailroom_pending_dec);
	sdata->crypto_tx_tailroom_pending_dec = 0;
	mutex_unlock(&sdata->local->key_mtx);
पूर्ण

व्योम ieee80211_gtk_rekey_notअगरy(काष्ठा ieee80211_vअगर *vअगर, स्थिर u8 *bssid,
				स्थिर u8 *replay_ctr, gfp_t gfp)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);

	trace_api_gtk_rekey_notअगरy(sdata, bssid, replay_ctr);

	cfg80211_gtk_rekey_notअगरy(sdata->dev, bssid, replay_ctr, gfp);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_gtk_rekey_notअगरy);

व्योम ieee80211_get_key_rx_seq(काष्ठा ieee80211_key_conf *keyconf,
			      पूर्णांक tid, काष्ठा ieee80211_key_seq *seq)
अणु
	काष्ठा ieee80211_key *key;
	स्थिर u8 *pn;

	key = container_of(keyconf, काष्ठा ieee80211_key, conf);

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (WARN_ON(tid < 0 || tid >= IEEE80211_NUM_TIDS))
			वापस;
		seq->tkip.iv32 = key->u.tkip.rx[tid].iv32;
		seq->tkip.iv16 = key->u.tkip.rx[tid].iv16;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		अगर (WARN_ON(tid < -1 || tid >= IEEE80211_NUM_TIDS))
			वापस;
		अगर (tid < 0)
			pn = key->u.ccmp.rx_pn[IEEE80211_NUM_TIDS];
		अन्यथा
			pn = key->u.ccmp.rx_pn[tid];
		स_नकल(seq->ccmp.pn, pn, IEEE80211_CCMP_PN_LEN);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		अगर (WARN_ON(tid != 0))
			वापस;
		pn = key->u.aes_cmac.rx_pn;
		स_नकल(seq->aes_cmac.pn, pn, IEEE80211_CMAC_PN_LEN);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		अगर (WARN_ON(tid != 0))
			वापस;
		pn = key->u.aes_gmac.rx_pn;
		स_नकल(seq->aes_gmac.pn, pn, IEEE80211_GMAC_PN_LEN);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		अगर (WARN_ON(tid < -1 || tid >= IEEE80211_NUM_TIDS))
			वापस;
		अगर (tid < 0)
			pn = key->u.gcmp.rx_pn[IEEE80211_NUM_TIDS];
		अन्यथा
			pn = key->u.gcmp.rx_pn[tid];
		स_नकल(seq->gcmp.pn, pn, IEEE80211_GCMP_PN_LEN);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL(ieee80211_get_key_rx_seq);

व्योम ieee80211_set_key_rx_seq(काष्ठा ieee80211_key_conf *keyconf,
			      पूर्णांक tid, काष्ठा ieee80211_key_seq *seq)
अणु
	काष्ठा ieee80211_key *key;
	u8 *pn;

	key = container_of(keyconf, काष्ठा ieee80211_key, conf);

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_TKIP:
		अगर (WARN_ON(tid < 0 || tid >= IEEE80211_NUM_TIDS))
			वापस;
		key->u.tkip.rx[tid].iv32 = seq->tkip.iv32;
		key->u.tkip.rx[tid].iv16 = seq->tkip.iv16;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		अगर (WARN_ON(tid < -1 || tid >= IEEE80211_NUM_TIDS))
			वापस;
		अगर (tid < 0)
			pn = key->u.ccmp.rx_pn[IEEE80211_NUM_TIDS];
		अन्यथा
			pn = key->u.ccmp.rx_pn[tid];
		स_नकल(pn, seq->ccmp.pn, IEEE80211_CCMP_PN_LEN);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		अगर (WARN_ON(tid != 0))
			वापस;
		pn = key->u.aes_cmac.rx_pn;
		स_नकल(pn, seq->aes_cmac.pn, IEEE80211_CMAC_PN_LEN);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		अगर (WARN_ON(tid != 0))
			वापस;
		pn = key->u.aes_gmac.rx_pn;
		स_नकल(pn, seq->aes_gmac.pn, IEEE80211_GMAC_PN_LEN);
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		अगर (WARN_ON(tid < -1 || tid >= IEEE80211_NUM_TIDS))
			वापस;
		अगर (tid < 0)
			pn = key->u.gcmp.rx_pn[IEEE80211_NUM_TIDS];
		अन्यथा
			pn = key->u.gcmp.rx_pn[tid];
		स_नकल(pn, seq->gcmp.pn, IEEE80211_GCMP_PN_LEN);
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_set_key_rx_seq);

व्योम ieee80211_हटाओ_key(काष्ठा ieee80211_key_conf *keyconf)
अणु
	काष्ठा ieee80211_key *key;

	key = container_of(keyconf, काष्ठा ieee80211_key, conf);

	निश्चित_key_lock(key->local);

	/*
	 * अगर key was uploaded, we assume the driver will/has हटाओ(d)
	 * it, so adjust bookkeeping accordingly
	 */
	अगर (key->flags & KEY_FLAG_UPLOADED_TO_HARDWARE) अणु
		key->flags &= ~KEY_FLAG_UPLOADED_TO_HARDWARE;

		अगर (!(key->conf.flags & (IEEE80211_KEY_FLAG_GENERATE_MMIC |
					 IEEE80211_KEY_FLAG_PUT_MIC_SPACE |
					 IEEE80211_KEY_FLAG_RESERVE_TAILROOM)))
			increment_tailroom_need_count(key->sdata);
	पूर्ण

	ieee80211_key_मुक्त(key, false);
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_हटाओ_key);

काष्ठा ieee80211_key_conf *
ieee80211_gtk_rekey_add(काष्ठा ieee80211_vअगर *vअगर,
			काष्ठा ieee80211_key_conf *keyconf)
अणु
	काष्ठा ieee80211_sub_अगर_data *sdata = vअगर_to_sdata(vअगर);
	काष्ठा ieee80211_local *local = sdata->local;
	काष्ठा ieee80211_key *key;
	पूर्णांक err;

	अगर (WARN_ON(!local->wowlan))
		वापस ERR_PTR(-EINVAL);

	अगर (WARN_ON(vअगर->type != NL80211_IFTYPE_STATION))
		वापस ERR_PTR(-EINVAL);

	key = ieee80211_key_alloc(keyconf->cipher, keyconf->keyidx,
				  keyconf->keylen, keyconf->key,
				  0, शून्य, शून्य);
	अगर (IS_ERR(key))
		वापस ERR_CAST(key);

	अगर (sdata->u.mgd.mfp != IEEE80211_MFP_DISABLED)
		key->conf.flags |= IEEE80211_KEY_FLAG_RX_MGMT;

	err = ieee80211_key_link(key, sdata, शून्य);
	अगर (err)
		वापस ERR_PTR(err);

	वापस &key->conf;
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_gtk_rekey_add);

व्योम ieee80211_key_mic_failure(काष्ठा ieee80211_key_conf *keyconf)
अणु
	काष्ठा ieee80211_key *key;

	key = container_of(keyconf, काष्ठा ieee80211_key, conf);

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		key->u.aes_cmac.icverrors++;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		key->u.aes_gmac.icverrors++;
		अवरोध;
	शेष:
		/* ignore the others क्रम now, we करोn't keep counters now */
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_key_mic_failure);

व्योम ieee80211_key_replay(काष्ठा ieee80211_key_conf *keyconf)
अणु
	काष्ठा ieee80211_key *key;

	key = container_of(keyconf, काष्ठा ieee80211_key, conf);

	चयन (key->conf.cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
	हाल WLAN_CIPHER_SUITE_CCMP_256:
		key->u.ccmp.replays++;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_AES_CMAC:
	हाल WLAN_CIPHER_SUITE_BIP_CMAC_256:
		key->u.aes_cmac.replays++;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_128:
	हाल WLAN_CIPHER_SUITE_BIP_GMAC_256:
		key->u.aes_gmac.replays++;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_GCMP:
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		key->u.gcmp.replays++;
		अवरोध;
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(ieee80211_key_replay);
