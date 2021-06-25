<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * mac80211 glue code क्रम mac80211 Prism54 drivers
 *
 * Copyright (c) 2006, Michael Wu <flamingice@sourmilk.net>
 * Copyright (c) 2007-2009, Christian Lamparter <chunkeey@web.de>
 * Copyright 2008, Johannes Berg <johannes@sipsolutions.net>
 *
 * Based on:
 * - the islsm (sofपंचांगac prism54) driver, which is:
 *   Copyright 2004-2006 Jean-Baptiste Note <jbnote@gmail.com>, et al.
 * - stlc45xx driver
 *   Copyright (C) 2008 Nokia Corporation and/or its subsidiary(-ies).
 */

#समावेश <linux/slab.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/module.h>

#समावेश <net/mac80211.h>

#समावेश "p54.h"
#समावेश "lmac.h"

अटल bool modparam_nohwcrypt;
module_param_named(nohwcrypt, modparam_nohwcrypt, bool, 0444);
MODULE_PARM_DESC(nohwcrypt, "Disable hardware encryption.");
MODULE_AUTHOR("Michael Wu <flamingice@sourmilk.net>");
MODULE_DESCRIPTION("Softmac Prism54 common code");
MODULE_LICENSE("GPL");
MODULE_ALIAS("prism54common");

अटल पूर्णांक p54_sta_add_हटाओ(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा p54_common *priv = hw->priv;

	/*
	 * Notअगरy the firmware that we करोn't want or we don't
	 * need to buffer frames क्रम this station anymore.
	 */

	p54_sta_unlock(priv, sta->addr);

	वापस 0;
पूर्ण

अटल व्योम p54_sta_notअगरy(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_vअगर *vअगर,
			      क्रमागत sta_notअगरy_cmd notअगरy_cmd,
			      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा p54_common *priv = dev->priv;

	चयन (notअगरy_cmd) अणु
	हाल STA_NOTIFY_AWAKE:
		/* update the firmware's filter table */
		p54_sta_unlock(priv, sta->addr);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक p54_set_tim(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_sta *sta,
			bool set)
अणु
	काष्ठा p54_common *priv = dev->priv;

	वापस p54_update_beacon_tim(priv, sta->aid, set);
पूर्ण

u8 *p54_find_ie(काष्ठा sk_buff *skb, u8 ie)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;
	u8 *pos, *end;

	अगर (skb->len <= माप(mgmt))
		वापस शून्य;

	pos = (u8 *)mgmt->u.beacon.variable;
	end = skb->data + skb->len;
	जबतक (pos < end) अणु
		अगर (pos + 2 + pos[1] > end)
			वापस शून्य;

		अगर (pos[0] == ie)
			वापस pos;

		pos += 2 + pos[1];
	पूर्ण
	वापस शून्य;
पूर्ण

अटल पूर्णांक p54_beacon_क्रमmat_ie_tim(काष्ठा sk_buff *skb)
अणु
	/*
	 * the good excuse क्रम this mess is ... the firmware.
	 * The dummy TIM MUST be at the end of the beacon frame,
	 * because it'll be overwritten!
	 */
	u8 *tim;
	u8 dtim_len;
	u8 dtim_period;
	u8 *next;

	tim = p54_find_ie(skb, WLAN_EID_TIM);
	अगर (!tim)
		वापस 0;

	dtim_len = tim[1];
	dtim_period = tim[3];
	next = tim + 2 + dtim_len;

	अगर (dtim_len < 3)
		वापस -EINVAL;

	स_हटाओ(tim, next, skb_tail_poपूर्णांकer(skb) - next);
	tim = skb_tail_poपूर्णांकer(skb) - (dtim_len + 2);

	/* add the dummy at the end */
	tim[0] = WLAN_EID_TIM;
	tim[1] = 3;
	tim[2] = 0;
	tim[3] = dtim_period;
	tim[4] = 0;

	अगर (dtim_len > 3)
		skb_trim(skb, skb->len - (dtim_len - 3));

	वापस 0;
पूर्ण

अटल पूर्णांक p54_beacon_update(काष्ठा p54_common *priv,
			काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा ieee80211_tx_control control = अणु पूर्ण;
	काष्ठा sk_buff *beacon;
	पूर्णांक ret;

	beacon = ieee80211_beacon_get(priv->hw, vअगर);
	अगर (!beacon)
		वापस -ENOMEM;
	ret = p54_beacon_क्रमmat_ie_tim(beacon);
	अगर (ret)
		वापस ret;

	/*
	 * During operation, the firmware takes care of beaconing.
	 * The driver only needs to upload a new beacon ढाँचा, once
	 * the ढाँचा was changed by the stack or userspace.
	 *
	 * LMAC API 3.2.2 also specअगरies that the driver करोes not need
	 * to cancel the old beacon ढाँचा by hand, instead the firmware
	 * will release the previous one through the feedback mechanism.
	 */
	p54_tx_80211(priv->hw, &control, beacon);
	priv->tsf_high32 = 0;
	priv->tsf_low32 = 0;

	वापस 0;
पूर्ण

अटल पूर्णांक p54_start(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54_common *priv = dev->priv;
	पूर्णांक err;

	mutex_lock(&priv->conf_mutex);
	err = priv->खोलो(dev);
	अगर (err)
		जाओ out;
	P54_SET_QUEUE(priv->qos_params[0], 0x0002, 0x0003, 0x0007, 47);
	P54_SET_QUEUE(priv->qos_params[1], 0x0002, 0x0007, 0x000f, 94);
	P54_SET_QUEUE(priv->qos_params[2], 0x0003, 0x000f, 0x03ff, 0);
	P54_SET_QUEUE(priv->qos_params[3], 0x0007, 0x000f, 0x03ff, 0);
	err = p54_set_edcf(priv);
	अगर (err)
		जाओ out;

	eth_broadcast_addr(priv->bssid);
	priv->mode = NL80211_IFTYPE_MONITOR;
	err = p54_setup_mac(priv);
	अगर (err) अणु
		priv->mode = NL80211_IFTYPE_UNSPECIFIED;
		जाओ out;
	पूर्ण

	ieee80211_queue_delayed_work(dev, &priv->work, 0);

	priv->softled_state = 0;
	err = p54_set_leds(priv);

out:
	mutex_unlock(&priv->conf_mutex);
	वापस err;
पूर्ण

अटल व्योम p54_stop(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54_common *priv = dev->priv;
	पूर्णांक i;

	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->softled_state = 0;
	cancel_delayed_work_sync(&priv->work);
	mutex_lock(&priv->conf_mutex);
	p54_set_leds(priv);
	priv->stop(dev);
	skb_queue_purge(&priv->tx_pending);
	skb_queue_purge(&priv->tx_queue);
	क्रम (i = 0; i < P54_QUEUE_NUM; i++) अणु
		priv->tx_stats[i].count = 0;
		priv->tx_stats[i].len = 0;
	पूर्ण

	priv->beacon_req_id = cpu_to_le32(0);
	priv->tsf_high32 = priv->tsf_low32 = 0;
	mutex_unlock(&priv->conf_mutex);
पूर्ण

अटल पूर्णांक p54_add_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
			     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा p54_common *priv = dev->priv;
	पूर्णांक err;

	vअगर->driver_flags |= IEEE80211_VIF_BEACON_FILTER;

	mutex_lock(&priv->conf_mutex);
	अगर (priv->mode != NL80211_IFTYPE_MONITOR) अणु
		mutex_unlock(&priv->conf_mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	priv->vअगर = vअगर;

	चयन (vअगर->type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_MESH_POINT:
		priv->mode = vअगर->type;
		अवरोध;
	शेष:
		mutex_unlock(&priv->conf_mutex);
		वापस -EOPNOTSUPP;
	पूर्ण

	स_नकल(priv->mac_addr, vअगर->addr, ETH_ALEN);
	err = p54_setup_mac(priv);
	mutex_unlock(&priv->conf_mutex);
	वापस err;
पूर्ण

अटल व्योम p54_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *dev,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा p54_common *priv = dev->priv;

	mutex_lock(&priv->conf_mutex);
	priv->vअगर = शून्य;

	/*
	 * LMAC API 3.2.2 states that any active beacon ढाँचा must be
	 * canceled by the driver beक्रमe attempting a mode transition.
	 */
	अगर (le32_to_cpu(priv->beacon_req_id) != 0) अणु
		p54_tx_cancel(priv, priv->beacon_req_id);
		रुको_क्रम_completion_पूर्णांकerruptible_समयout(&priv->beacon_comp, HZ);
	पूर्ण
	priv->mode = NL80211_IFTYPE_MONITOR;
	eth_zero_addr(priv->mac_addr);
	eth_zero_addr(priv->bssid);
	p54_setup_mac(priv);
	mutex_unlock(&priv->conf_mutex);
पूर्ण

अटल पूर्णांक p54_रुको_क्रम_stats(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54_common *priv = dev->priv;
	पूर्णांक ret;

	priv->update_stats = true;
	ret = p54_fetch_statistics(priv);
	अगर (ret)
		वापस ret;

	ret = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&priv->stat_comp, HZ);
	अगर (ret == 0)
		वापस -ETIMEDOUT;

	वापस 0;
पूर्ण

अटल व्योम p54_reset_stats(काष्ठा p54_common *priv)
अणु
	काष्ठा ieee80211_channel *chan = priv->curchan;

	अगर (chan) अणु
		काष्ठा survey_info *info = &priv->survey[chan->hw_value];

		/* only reset channel statistics, करोn't touch .filled, etc. */
		info->समय = 0;
		info->समय_busy = 0;
		info->समय_प्रकारx = 0;
	पूर्ण

	priv->update_stats = true;
	priv->survey_raw.active = 0;
	priv->survey_raw.cca = 0;
	priv->survey_raw.tx = 0;
पूर्ण

अटल पूर्णांक p54_config(काष्ठा ieee80211_hw *dev, u32 changed)
अणु
	पूर्णांक ret = 0;
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा ieee80211_conf *conf = &dev->conf;

	mutex_lock(&priv->conf_mutex);
	अगर (changed & IEEE80211_CONF_CHANGE_POWER)
		priv->output_घातer = conf->घातer_level << 2;
	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		काष्ठा ieee80211_channel *oldchan;
		WARN_ON(p54_रुको_क्रम_stats(dev));
		oldchan = priv->curchan;
		priv->curchan = शून्य;
		ret = p54_scan(priv, P54_SCAN_EXIT, 0);
		अगर (ret) अणु
			priv->curchan = oldchan;
			जाओ out;
		पूर्ण
		/*
		 * TODO: Use the LM_SCAN_TRAP to determine the current
		 * operating channel.
		 */
		priv->curchan = priv->hw->conf.chandef.chan;
		p54_reset_stats(priv);
		WARN_ON(p54_fetch_statistics(priv));
	पूर्ण
	अगर (changed & IEEE80211_CONF_CHANGE_PS) अणु
		WARN_ON(p54_रुको_क्रम_stats(dev));
		ret = p54_set_ps(priv);
		अगर (ret)
			जाओ out;
		WARN_ON(p54_रुको_क्रम_stats(dev));
	पूर्ण
	अगर (changed & IEEE80211_CONF_CHANGE_IDLE) अणु
		WARN_ON(p54_रुको_क्रम_stats(dev));
		ret = p54_setup_mac(priv);
		अगर (ret)
			जाओ out;
		WARN_ON(p54_रुको_क्रम_stats(dev));
	पूर्ण

out:
	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

अटल u64 p54_prepare_multicast(काष्ठा ieee80211_hw *dev,
				 काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा netdev_hw_addr *ha;
	पूर्णांक i;

	BUILD_BUG_ON(ARRAY_SIZE(priv->mc_maclist) !=
		ARRAY_SIZE(((काष्ठा p54_group_address_table *)शून्य)->mac_list));
	/*
	 * The first entry is reserved क्रम the global broadcast MAC.
	 * Otherwise the firmware will drop it and ARP will no दीर्घer work.
	 */
	i = 1;
	priv->mc_maclist_num = netdev_hw_addr_list_count(mc_list) + i;
	netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
		स_नकल(&priv->mc_maclist[i], ha->addr, ETH_ALEN);
		i++;
		अगर (i >= ARRAY_SIZE(priv->mc_maclist))
			अवरोध;
	पूर्ण

	वापस 1; /* update */
पूर्ण

अटल व्योम p54_configure_filter(काष्ठा ieee80211_hw *dev,
				 अचिन्हित पूर्णांक changed_flags,
				 अचिन्हित पूर्णांक *total_flags,
				 u64 multicast)
अणु
	काष्ठा p54_common *priv = dev->priv;

	*total_flags &= FIF_ALLMULTI | FIF_OTHER_BSS;

	priv->filter_flags = *total_flags;

	अगर (changed_flags & FIF_OTHER_BSS)
		p54_setup_mac(priv);

	अगर (changed_flags & FIF_ALLMULTI || multicast)
		p54_set_groupfilter(priv);
पूर्ण

अटल पूर्णांक p54_conf_tx(काष्ठा ieee80211_hw *dev,
		       काष्ठा ieee80211_vअगर *vअगर, u16 queue,
		       स्थिर काष्ठा ieee80211_tx_queue_params *params)
अणु
	काष्ठा p54_common *priv = dev->priv;
	पूर्णांक ret;

	mutex_lock(&priv->conf_mutex);
	P54_SET_QUEUE(priv->qos_params[queue], params->aअगरs,
		      params->cw_min, params->cw_max, params->txop);
	ret = p54_set_edcf(priv);
	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

अटल व्योम p54_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा p54_common *priv = container_of(work, काष्ठा p54_common,
					       work.work);

	अगर (unlikely(priv->mode == NL80211_IFTYPE_UNSPECIFIED))
		वापस ;

	/*
	 * TODO: walk through tx_queue and करो the following tasks
	 * 	1. initiate bursts.
	 *      2. cancel stuck frames / reset the device अगर necessary.
	 */

	mutex_lock(&priv->conf_mutex);
	WARN_ON_ONCE(p54_fetch_statistics(priv));
	mutex_unlock(&priv->conf_mutex);
पूर्ण

अटल पूर्णांक p54_get_stats(काष्ठा ieee80211_hw *dev,
			 काष्ठा ieee80211_low_level_stats *stats)
अणु
	काष्ठा p54_common *priv = dev->priv;

	स_नकल(stats, &priv->stats, माप(*stats));
	वापस 0;
पूर्ण

अटल व्योम p54_bss_info_changed(काष्ठा ieee80211_hw *dev,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा ieee80211_bss_conf *info,
				 u32 changed)
अणु
	काष्ठा p54_common *priv = dev->priv;

	mutex_lock(&priv->conf_mutex);
	अगर (changed & BSS_CHANGED_BSSID) अणु
		स_नकल(priv->bssid, info->bssid, ETH_ALEN);
		p54_setup_mac(priv);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON) अणु
		p54_scan(priv, P54_SCAN_EXIT, 0);
		p54_setup_mac(priv);
		p54_beacon_update(priv, vअगर);
		p54_set_edcf(priv);
	पूर्ण

	अगर (changed & (BSS_CHANGED_ERP_SLOT | BSS_CHANGED_BEACON)) अणु
		priv->use_लघु_slot = info->use_लघु_slot;
		p54_set_edcf(priv);
	पूर्ण
	अगर (changed & BSS_CHANGED_BASIC_RATES) अणु
		अगर (dev->conf.chandef.chan->band == NL80211_BAND_5GHZ)
			priv->basic_rate_mask = (info->basic_rates << 4);
		अन्यथा
			priv->basic_rate_mask = info->basic_rates;
		p54_setup_mac(priv);
		अगर (priv->fw_var >= 0x500)
			p54_scan(priv, P54_SCAN_EXIT, 0);
	पूर्ण
	अगर (changed & BSS_CHANGED_ASSOC) अणु
		अगर (info->assoc) अणु
			priv->aid = info->aid;
			priv->wakeup_समयr = info->beacon_पूर्णांक *
					     info->dtim_period * 5;
			p54_setup_mac(priv);
		पूर्ण अन्यथा अणु
			priv->wakeup_समयr = 500;
			priv->aid = 0;
		पूर्ण
	पूर्ण

	mutex_unlock(&priv->conf_mutex);
पूर्ण

अटल पूर्णांक p54_set_key(काष्ठा ieee80211_hw *dev, क्रमागत set_key_cmd cmd,
		       काष्ठा ieee80211_vअगर *vअगर, काष्ठा ieee80211_sta *sta,
		       काष्ठा ieee80211_key_conf *key)
अणु
	काष्ठा p54_common *priv = dev->priv;
	पूर्णांक slot, ret = 0;
	u8 algo = 0;
	u8 *addr = शून्य;

	अगर (modparam_nohwcrypt)
		वापस -EOPNOTSUPP;

	अगर (key->flags & IEEE80211_KEY_FLAG_RX_MGMT) अणु
		/*
		 * Unक्रमtunately most/all firmwares are trying to decrypt
		 * incoming management frames अगर a suitable key can be found.
		 * However, in करोing so the data in these frames माला_लो
		 * corrupted. So, we can't have firmware supported crypto
		 * offload in this हाल.
		 */
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&priv->conf_mutex);
	अगर (cmd == SET_KEY) अणु
		चयन (key->cipher) अणु
		हाल WLAN_CIPHER_SUITE_TKIP:
			अगर (!(priv->privacy_caps & (BR_DESC_PRIV_CAP_MICHAEL |
			      BR_DESC_PRIV_CAP_TKIP))) अणु
				ret = -EOPNOTSUPP;
				जाओ out_unlock;
			पूर्ण
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			algo = P54_CRYPTO_TKIPMICHAEL;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_WEP40:
		हाल WLAN_CIPHER_SUITE_WEP104:
			अगर (!(priv->privacy_caps & BR_DESC_PRIV_CAP_WEP)) अणु
				ret = -EOPNOTSUPP;
				जाओ out_unlock;
			पूर्ण
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			algo = P54_CRYPTO_WEP;
			अवरोध;
		हाल WLAN_CIPHER_SUITE_CCMP:
			अगर (!(priv->privacy_caps & BR_DESC_PRIV_CAP_AESCCMP)) अणु
				ret = -EOPNOTSUPP;
				जाओ out_unlock;
			पूर्ण
			key->flags |= IEEE80211_KEY_FLAG_GENERATE_IV;
			algo = P54_CRYPTO_AESCCMP;
			अवरोध;
		शेष:
			ret = -EOPNOTSUPP;
			जाओ out_unlock;
		पूर्ण
		slot = biपंचांगap_find_मुक्त_region(priv->used_rxkeys,
					       priv->rx_keycache_size, 0);

		अगर (slot < 0) अणु
			/*
			 * The device supports the chosen algorithm, but the
			 * firmware करोes not provide enough key slots to store
			 * all of them.
			 * But encryption offload क्रम outgoing frames is always
			 * possible, so we just pretend that the upload was
			 * successful and करो the decryption in software.
			 */

			/* mark the key as invalid. */
			key->hw_key_idx = 0xff;
			जाओ out_unlock;
		पूर्ण

		key->flags |= IEEE80211_KEY_FLAG_RESERVE_TAILROOM;
	पूर्ण अन्यथा अणु
		slot = key->hw_key_idx;

		अगर (slot == 0xff) अणु
			/* This key was not uploaded पूर्णांकo the rx key cache. */

			जाओ out_unlock;
		पूर्ण

		biपंचांगap_release_region(priv->used_rxkeys, slot, 0);
		algo = 0;
	पूर्ण

	अगर (sta)
		addr = sta->addr;

	ret = p54_upload_key(priv, algo, slot, key->keyidx,
			     key->keylen, addr, key->key);
	अगर (ret) अणु
		biपंचांगap_release_region(priv->used_rxkeys, slot, 0);
		ret = -EOPNOTSUPP;
		जाओ out_unlock;
	पूर्ण

	key->hw_key_idx = slot;

out_unlock:
	mutex_unlock(&priv->conf_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक p54_get_survey(काष्ठा ieee80211_hw *dev, पूर्णांक idx,
				काष्ठा survey_info *survey)
अणु
	काष्ठा p54_common *priv = dev->priv;
	काष्ठा ieee80211_channel *chan;
	पूर्णांक err, tries;
	bool in_use = false;

	अगर (idx >= priv->chan_num)
		वापस -ENOENT;

#घोषणा MAX_TRIES 1
	क्रम (tries = 0; tries < MAX_TRIES; tries++) अणु
		chan = priv->curchan;
		अगर (chan && chan->hw_value == idx) अणु
			mutex_lock(&priv->conf_mutex);
			err = p54_रुको_क्रम_stats(dev);
			mutex_unlock(&priv->conf_mutex);
			अगर (err)
				वापस err;

			in_use = true;
		पूर्ण

		स_नकल(survey, &priv->survey[idx], माप(*survey));

		अगर (in_use) अणु
			/* test अगर the reported statistics are valid. */
			अगर  (survey->समय != 0) अणु
				survey->filled |= SURVEY_INFO_IN_USE;
			पूर्ण अन्यथा अणु
				/*
				 * hw/fw has not accumulated enough sample sets.
				 * Wait क्रम 100ms, this ought to be enough to
				 * to get at least one non-null set of channel
				 * usage statistics.
				 */
				msleep(100);
				जारी;
			पूर्ण
		पूर्ण
		वापस 0;
	पूर्ण
	वापस -ETIMEDOUT;
#अघोषित MAX_TRIES
पूर्ण

अटल अचिन्हित पूर्णांक p54_flush_count(काष्ठा p54_common *priv)
अणु
	अचिन्हित पूर्णांक total = 0, i;

	BUILD_BUG_ON(P54_QUEUE_NUM > ARRAY_SIZE(priv->tx_stats));

	/*
	 * Because the firmware has the sole control over any frames
	 * in the P54_QUEUE_BEACON or P54_QUEUE_SCAN queues, they
	 * करोn't really count as pending or active.
	 */
	क्रम (i = P54_QUEUE_MGMT; i < P54_QUEUE_NUM; i++)
		total += priv->tx_stats[i].len;
	वापस total;
पूर्ण

अटल व्योम p54_flush(काष्ठा ieee80211_hw *dev, काष्ठा ieee80211_vअगर *vअगर,
		      u32 queues, bool drop)
अणु
	काष्ठा p54_common *priv = dev->priv;
	अचिन्हित पूर्णांक total, i;

	/*
	 * Currently, it wouldn't really matter अगर we रुको क्रम one second
	 * or 15 minutes. But once someone माला_लो around and completes the
	 * TODOs [ancel stuck frames / reset device] in p54_work, it will
	 * suddenly make sense to रुको that दीर्घ.
	 */
	i = P54_STATISTICS_UPDATE * 2 / 20;

	/*
	 * In this हाल no locking is required because as we speak the
	 * queues have alपढ़ोy been stopped and no new frames can sneak
	 * up from behind.
	 */
	जबतक ((total = p54_flush_count(priv) && i--)) अणु
		/* waste समय */
		msleep(20);
	पूर्ण

	WARN(total, "tx flush timeout, unresponsive firmware");
पूर्ण

अटल व्योम p54_set_coverage_class(काष्ठा ieee80211_hw *dev,
				   s16 coverage_class)
अणु
	काष्ठा p54_common *priv = dev->priv;

	mutex_lock(&priv->conf_mutex);
	/* support all coverage class values as in 802.11-2007 Table 7-27 */
	priv->coverage_class = clamp_t(u8, coverage_class, 0, 31);
	p54_set_edcf(priv);
	mutex_unlock(&priv->conf_mutex);
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops p54_ops = अणु
	.tx			= p54_tx_80211,
	.start			= p54_start,
	.stop			= p54_stop,
	.add_पूर्णांकerface		= p54_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= p54_हटाओ_पूर्णांकerface,
	.set_tim		= p54_set_tim,
	.sta_notअगरy		= p54_sta_notअगरy,
	.sta_add		= p54_sta_add_हटाओ,
	.sta_हटाओ		= p54_sta_add_हटाओ,
	.set_key		= p54_set_key,
	.config			= p54_config,
	.flush			= p54_flush,
	.bss_info_changed	= p54_bss_info_changed,
	.prepare_multicast	= p54_prepare_multicast,
	.configure_filter	= p54_configure_filter,
	.conf_tx		= p54_conf_tx,
	.get_stats		= p54_get_stats,
	.get_survey		= p54_get_survey,
	.set_coverage_class	= p54_set_coverage_class,
पूर्ण;

काष्ठा ieee80211_hw *p54_init_common(माप_प्रकार priv_data_len)
अणु
	काष्ठा ieee80211_hw *dev;
	काष्ठा p54_common *priv;

	dev = ieee80211_alloc_hw(priv_data_len, &p54_ops);
	अगर (!dev)
		वापस शून्य;

	priv = dev->priv;
	priv->hw = dev;
	priv->mode = NL80211_IFTYPE_UNSPECIFIED;
	priv->basic_rate_mask = 0x15f;
	spin_lock_init(&priv->tx_stats_lock);
	skb_queue_head_init(&priv->tx_queue);
	skb_queue_head_init(&priv->tx_pending);
	ieee80211_hw_set(dev, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(dev, MFP_CAPABLE);
	ieee80211_hw_set(dev, PS_शून्यFUNC_STACK);
	ieee80211_hw_set(dev, SUPPORTS_PS);
	ieee80211_hw_set(dev, RX_INCLUDES_FCS);
	ieee80211_hw_set(dev, SIGNAL_DBM);

	dev->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				      BIT(NL80211_IFTYPE_ADHOC) |
				      BIT(NL80211_IFTYPE_AP) |
				      BIT(NL80211_IFTYPE_MESH_POINT);

	priv->beacon_req_id = cpu_to_le32(0);
	priv->tx_stats[P54_QUEUE_BEACON].limit = 1;
	priv->tx_stats[P54_QUEUE_FWSCAN].limit = 1;
	priv->tx_stats[P54_QUEUE_MGMT].limit = 3;
	priv->tx_stats[P54_QUEUE_CAB].limit = 3;
	priv->tx_stats[P54_QUEUE_DATA].limit = 5;
	dev->queues = 1;
	priv->noise = -94;
	/*
	 * We support at most 8 tries no matter which rate they're at,
	 * we cannot support max_rates * max_rate_tries as we set it
	 * here, but setting it correctly to 4/2 or so would limit us
	 * artअगरicially अगर the RC algorithm wants just two rates, so
	 * let's say 4/7, we'll redistribute it at TX समय, see the
	 * comments there.
	 */
	dev->max_rates = 4;
	dev->max_rate_tries = 7;
	dev->extra_tx_headroom = माप(काष्ठा p54_hdr) + 4 +
				 माप(काष्ठा p54_tx_data);

	/*
	 * For now, disable PS by शेष because it affects
	 * link stability signअगरicantly.
	 */
	dev->wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	mutex_init(&priv->conf_mutex);
	mutex_init(&priv->eeprom_mutex);
	init_completion(&priv->stat_comp);
	init_completion(&priv->eeprom_comp);
	init_completion(&priv->beacon_comp);
	INIT_DELAYED_WORK(&priv->work, p54_work);

	eth_broadcast_addr(priv->mc_maclist[0]);
	priv->curchan = शून्य;
	p54_reset_stats(priv);
	वापस dev;
पूर्ण
EXPORT_SYMBOL_GPL(p54_init_common);

पूर्णांक p54_रेजिस्टर_common(काष्ठा ieee80211_hw *dev, काष्ठा device *pdev)
अणु
	काष्ठा p54_common __maybe_unused *priv = dev->priv;
	पूर्णांक err;

	err = ieee80211_रेजिस्टर_hw(dev);
	अगर (err) अणु
		dev_err(pdev, "Cannot register device (%d).\n", err);
		वापस err;
	पूर्ण
	priv->रेजिस्टरed = true;

#अगर_घोषित CONFIG_P54_LEDS
	err = p54_init_leds(priv);
	अगर (err) अणु
		p54_unरेजिस्टर_common(dev);
		वापस err;
	पूर्ण
#पूर्ण_अगर /* CONFIG_P54_LEDS */

	dev_info(pdev, "is registered as '%s'\n", wiphy_name(dev->wiphy));
	वापस 0;
पूर्ण
EXPORT_SYMBOL_GPL(p54_रेजिस्टर_common);

व्योम p54_मुक्त_common(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54_common *priv = dev->priv;
	अचिन्हित पूर्णांक i;

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++)
		kमुक्त(priv->band_table[i]);

	kमुक्त(priv->iq_स्वतःcal);
	kमुक्त(priv->output_limit);
	kमुक्त(priv->curve_data);
	kमुक्त(priv->rssi_db);
	kमुक्त(priv->used_rxkeys);
	kमुक्त(priv->survey);
	priv->iq_स्वतःcal = शून्य;
	priv->output_limit = शून्य;
	priv->curve_data = शून्य;
	priv->rssi_db = शून्य;
	priv->used_rxkeys = शून्य;
	priv->survey = शून्य;
	ieee80211_मुक्त_hw(dev);
पूर्ण
EXPORT_SYMBOL_GPL(p54_मुक्त_common);

व्योम p54_unरेजिस्टर_common(काष्ठा ieee80211_hw *dev)
अणु
	काष्ठा p54_common *priv = dev->priv;

	अगर (priv->रेजिस्टरed) अणु
		priv->रेजिस्टरed = false;
#अगर_घोषित CONFIG_P54_LEDS
		p54_unरेजिस्टर_leds(priv);
#पूर्ण_अगर /* CONFIG_P54_LEDS */
		ieee80211_unरेजिस्टर_hw(dev);
	पूर्ण

	mutex_destroy(&priv->conf_mutex);
	mutex_destroy(&priv->eeprom_mutex);
पूर्ण
EXPORT_SYMBOL_GPL(p54_unरेजिस्टर_common);
