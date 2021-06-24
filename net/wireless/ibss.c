<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Some IBSS support code क्रम cfg80211.
 *
 * Copyright 2009	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2020-2021 Intel Corporation
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <linux/export.h>
#समावेश <net/cfg80211.h>
#समावेश "wext-compat.h"
#समावेश "nl80211.h"
#समावेश "rdev-ops.h"


व्योम __cfg80211_ibss_joined(काष्ठा net_device *dev, स्थिर u8 *bssid,
			    काष्ठा ieee80211_channel *channel)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_bss *bss;
#अगर_घोषित CONFIG_CFG80211_WEXT
	जोड़ iwreq_data wrqu;
#पूर्ण_अगर

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_ADHOC))
		वापस;

	अगर (!wdev->ssid_len)
		वापस;

	bss = cfg80211_get_bss(wdev->wiphy, channel, bssid, शून्य, 0,
			       IEEE80211_BSS_TYPE_IBSS, IEEE80211_PRIVACY_ANY);

	अगर (WARN_ON(!bss))
		वापस;

	अगर (wdev->current_bss) अणु
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
	पूर्ण

	cfg80211_hold_bss(bss_from_pub(bss));
	wdev->current_bss = bss_from_pub(bss);

	अगर (!(wdev->wiphy->flags & WIPHY_FLAG_HAS_STATIC_WEP))
		cfg80211_upload_connect_keys(wdev);

	nl80211_send_ibss_bssid(wiphy_to_rdev(wdev->wiphy), dev, bssid,
				GFP_KERNEL);
#अगर_घोषित CONFIG_CFG80211_WEXT
	स_रखो(&wrqu, 0, माप(wrqu));
	स_नकल(wrqu.ap_addr.sa_data, bssid, ETH_ALEN);
	wireless_send_event(dev, SIOCGIWAP, &wrqu, शून्य);
#पूर्ण_अगर
पूर्ण

व्योम cfg80211_ibss_joined(काष्ठा net_device *dev, स्थिर u8 *bssid,
			  काष्ठा ieee80211_channel *channel, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_event *ev;
	अचिन्हित दीर्घ flags;

	trace_cfg80211_ibss_joined(dev, bssid, channel);

	अगर (WARN_ON(!channel))
		वापस;

	ev = kzalloc(माप(*ev), gfp);
	अगर (!ev)
		वापस;

	ev->type = EVENT_IBSS_JOINED;
	स_नकल(ev->ij.bssid, bssid, ETH_ALEN);
	ev->ij.channel = channel;

	spin_lock_irqsave(&wdev->event_lock, flags);
	list_add_tail(&ev->list, &wdev->event_list);
	spin_unlock_irqrestore(&wdev->event_lock, flags);
	queue_work(cfg80211_wq, &rdev->event_work);
पूर्ण
EXPORT_SYMBOL(cfg80211_ibss_joined);

पूर्णांक __cfg80211_join_ibss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev,
			 काष्ठा cfg80211_ibss_params *params,
			 काष्ठा cfg80211_cached_keys *connkeys)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	lockdep_निश्चित_held(&rdev->wiphy.mtx);
	ASSERT_WDEV_LOCK(wdev);

	अगर (wdev->ssid_len)
		वापस -EALREADY;

	अगर (!params->basic_rates) अणु
		/*
		* If no rates were explicitly configured,
		* use the mandatory rate set क्रम 11b or
		* 11a क्रम maximum compatibility.
		*/
		काष्ठा ieee80211_supported_band *sband;
		क्रमागत nl80211_band band;
		u32 flag;
		पूर्णांक j;

		band = params->chandef.chan->band;
		अगर (band == NL80211_BAND_5GHZ ||
		    band == NL80211_BAND_6GHZ)
			flag = IEEE80211_RATE_MANDATORY_A;
		अन्यथा
			flag = IEEE80211_RATE_MANDATORY_B;

		sband = rdev->wiphy.bands[band];
		क्रम (j = 0; j < sband->n_bitrates; j++) अणु
			अगर (sband->bitrates[j].flags & flag)
				params->basic_rates |= BIT(j);
		पूर्ण
	पूर्ण

	अगर (WARN_ON(connkeys && connkeys->def < 0))
		वापस -EINVAL;

	अगर (WARN_ON(wdev->connect_keys))
		kमुक्त_sensitive(wdev->connect_keys);
	wdev->connect_keys = connkeys;

	wdev->ibss_fixed = params->channel_fixed;
	wdev->ibss_dfs_possible = params->userspace_handles_dfs;
	wdev->chandef = params->chandef;
	अगर (connkeys) अणु
		params->wep_keys = connkeys->params;
		params->wep_tx_key = connkeys->def;
	पूर्ण

#अगर_घोषित CONFIG_CFG80211_WEXT
	wdev->wext.ibss.chandef = params->chandef;
#पूर्ण_अगर
	err = rdev_join_ibss(rdev, dev, params);
	अगर (err) अणु
		wdev->connect_keys = शून्य;
		वापस err;
	पूर्ण

	स_नकल(wdev->ssid, params->ssid, params->ssid_len);
	wdev->ssid_len = params->ssid_len;

	वापस 0;
पूर्ण

अटल व्योम __cfg80211_clear_ibss(काष्ठा net_device *dev, bool nowext)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक i;

	ASSERT_WDEV_LOCK(wdev);

	kमुक्त_sensitive(wdev->connect_keys);
	wdev->connect_keys = शून्य;

	rdev_set_qos_map(rdev, dev, शून्य);

	/*
	 * Delete all the keys ... pairwise keys can't really
	 * exist any more anyway, but शेष keys might.
	 */
	अगर (rdev->ops->del_key)
		क्रम (i = 0; i < 6; i++)
			rdev_del_key(rdev, dev, i, false, शून्य);

	अगर (wdev->current_bss) अणु
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
	पूर्ण

	wdev->current_bss = शून्य;
	wdev->ssid_len = 0;
	स_रखो(&wdev->chandef, 0, माप(wdev->chandef));
#अगर_घोषित CONFIG_CFG80211_WEXT
	अगर (!nowext)
		wdev->wext.ibss.ssid_len = 0;
#पूर्ण_अगर
	cfg80211_sched_dfs_chan_update(rdev);
पूर्ण

व्योम cfg80211_clear_ibss(काष्ठा net_device *dev, bool nowext)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	wdev_lock(wdev);
	__cfg80211_clear_ibss(dev, nowext);
	wdev_unlock(wdev);
पूर्ण

पूर्णांक __cfg80211_leave_ibss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *dev, bool nowext)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (!wdev->ssid_len)
		वापस -ENOLINK;

	err = rdev_leave_ibss(rdev, dev);

	अगर (err)
		वापस err;

	wdev->conn_owner_nlportid = 0;
	__cfg80211_clear_ibss(dev, nowext);

	वापस 0;
पूर्ण

पूर्णांक cfg80211_leave_ibss(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev, bool nowext)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	wdev_lock(wdev);
	err = __cfg80211_leave_ibss(rdev, dev, nowext);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

#अगर_घोषित CONFIG_CFG80211_WEXT
पूर्णांक cfg80211_ibss_wext_join(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_cached_keys *ck = शून्य;
	क्रमागत nl80211_band band;
	पूर्णांक i, err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (!wdev->wext.ibss.beacon_पूर्णांकerval)
		wdev->wext.ibss.beacon_पूर्णांकerval = 100;

	/* try to find an IBSS channel अगर none requested ... */
	अगर (!wdev->wext.ibss.chandef.chan) अणु
		काष्ठा ieee80211_channel *new_chan = शून्य;

		क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
			काष्ठा ieee80211_supported_band *sband;
			काष्ठा ieee80211_channel *chan;

			sband = rdev->wiphy.bands[band];
			अगर (!sband)
				जारी;

			क्रम (i = 0; i < sband->n_channels; i++) अणु
				chan = &sband->channels[i];
				अगर (chan->flags & IEEE80211_CHAN_NO_IR)
					जारी;
				अगर (chan->flags & IEEE80211_CHAN_DISABLED)
					जारी;
				new_chan = chan;
				अवरोध;
			पूर्ण

			अगर (new_chan)
				अवरोध;
		पूर्ण

		अगर (!new_chan)
			वापस -EINVAL;

		cfg80211_chandef_create(&wdev->wext.ibss.chandef, new_chan,
					NL80211_CHAN_NO_HT);
	पूर्ण

	/* करोn't join -- SSID is not there */
	अगर (!wdev->wext.ibss.ssid_len)
		वापस 0;

	अगर (!netअगर_running(wdev->netdev))
		वापस 0;

	अगर (wdev->wext.keys)
		wdev->wext.keys->def = wdev->wext.शेष_key;

	wdev->wext.ibss.privacy = wdev->wext.शेष_key != -1;

	अगर (wdev->wext.keys && wdev->wext.keys->def != -1) अणु
		ck = kmemdup(wdev->wext.keys, माप(*ck), GFP_KERNEL);
		अगर (!ck)
			वापस -ENOMEM;
		क्रम (i = 0; i < CFG80211_MAX_WEP_KEYS; i++)
			ck->params[i].key = ck->data[i];
	पूर्ण
	err = __cfg80211_join_ibss(rdev, wdev->netdev,
				   &wdev->wext.ibss, ck);
	अगर (err)
		kमुक्त(ck);

	वापस err;
पूर्ण

पूर्णांक cfg80211_ibss_wext_siwfreq(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_freq *wextfreq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा ieee80211_channel *chan = शून्य;
	पूर्णांक err, freq;

	/* call only क्रम ibss! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_ADHOC))
		वापस -EINVAL;

	अगर (!rdev->ops->join_ibss)
		वापस -EOPNOTSUPP;

	freq = cfg80211_wext_freq(wextfreq);
	अगर (freq < 0)
		वापस freq;

	अगर (freq) अणु
		chan = ieee80211_get_channel(wdev->wiphy, freq);
		अगर (!chan)
			वापस -EINVAL;
		अगर (chan->flags & IEEE80211_CHAN_NO_IR ||
		    chan->flags & IEEE80211_CHAN_DISABLED)
			वापस -EINVAL;
	पूर्ण

	अगर (wdev->wext.ibss.chandef.chan == chan)
		वापस 0;

	wdev_lock(wdev);
	err = 0;
	अगर (wdev->ssid_len)
		err = __cfg80211_leave_ibss(rdev, dev, true);
	wdev_unlock(wdev);

	अगर (err)
		वापस err;

	अगर (chan) अणु
		cfg80211_chandef_create(&wdev->wext.ibss.chandef, chan,
					NL80211_CHAN_NO_HT);
		wdev->wext.ibss.channel_fixed = true;
	पूर्ण अन्यथा अणु
		/* cfg80211_ibss_wext_join will pick one अगर needed */
		wdev->wext.ibss.channel_fixed = false;
	पूर्ण

	wdev_lock(wdev);
	err = cfg80211_ibss_wext_join(rdev, wdev);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

पूर्णांक cfg80211_ibss_wext_giwfreq(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_freq *freq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा ieee80211_channel *chan = शून्य;

	/* call only क्रम ibss! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_ADHOC))
		वापस -EINVAL;

	wdev_lock(wdev);
	अगर (wdev->current_bss)
		chan = wdev->current_bss->pub.channel;
	अन्यथा अगर (wdev->wext.ibss.chandef.chan)
		chan = wdev->wext.ibss.chandef.chan;
	wdev_unlock(wdev);

	अगर (chan) अणु
		freq->m = chan->center_freq;
		freq->e = 6;
		वापस 0;
	पूर्ण

	/* no channel अगर not joining */
	वापस -EINVAL;
पूर्ण

पूर्णांक cfg80211_ibss_wext_siwessid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_poपूर्णांक *data, अक्षर *ssid)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	माप_प्रकार len = data->length;
	पूर्णांक err;

	/* call only क्रम ibss! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_ADHOC))
		वापस -EINVAL;

	अगर (!rdev->ops->join_ibss)
		वापस -EOPNOTSUPP;

	wdev_lock(wdev);
	err = 0;
	अगर (wdev->ssid_len)
		err = __cfg80211_leave_ibss(rdev, dev, true);
	wdev_unlock(wdev);

	अगर (err)
		वापस err;

	/* iwconfig uses nul termination in SSID.. */
	अगर (len > 0 && ssid[len - 1] == '\0')
		len--;

	स_नकल(wdev->ssid, ssid, len);
	wdev->wext.ibss.ssid = wdev->ssid;
	wdev->wext.ibss.ssid_len = len;

	wdev_lock(wdev);
	err = cfg80211_ibss_wext_join(rdev, wdev);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

पूर्णांक cfg80211_ibss_wext_giwessid(काष्ठा net_device *dev,
				काष्ठा iw_request_info *info,
				काष्ठा iw_poपूर्णांक *data, अक्षर *ssid)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	/* call only क्रम ibss! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_ADHOC))
		वापस -EINVAL;

	data->flags = 0;

	wdev_lock(wdev);
	अगर (wdev->ssid_len) अणु
		data->flags = 1;
		data->length = wdev->ssid_len;
		स_नकल(ssid, wdev->ssid, data->length);
	पूर्ण अन्यथा अगर (wdev->wext.ibss.ssid && wdev->wext.ibss.ssid_len) अणु
		data->flags = 1;
		data->length = wdev->wext.ibss.ssid_len;
		स_नकल(ssid, wdev->wext.ibss.ssid, data->length);
	पूर्ण
	wdev_unlock(wdev);

	वापस 0;
पूर्ण

पूर्णांक cfg80211_ibss_wext_siwap(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u8 *bssid = ap_addr->sa_data;
	पूर्णांक err;

	/* call only क्रम ibss! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_ADHOC))
		वापस -EINVAL;

	अगर (!rdev->ops->join_ibss)
		वापस -EOPNOTSUPP;

	अगर (ap_addr->sa_family != ARPHRD_ETHER)
		वापस -EINVAL;

	/* स्वतःmatic mode */
	अगर (is_zero_ether_addr(bssid) || is_broadcast_ether_addr(bssid))
		bssid = शून्य;

	अगर (bssid && !is_valid_ether_addr(bssid))
		वापस -EINVAL;

	/* both स्वतःmatic */
	अगर (!bssid && !wdev->wext.ibss.bssid)
		वापस 0;

	/* fixed alपढ़ोy - and no change */
	अगर (wdev->wext.ibss.bssid && bssid &&
	    ether_addr_equal(bssid, wdev->wext.ibss.bssid))
		वापस 0;

	wdev_lock(wdev);
	err = 0;
	अगर (wdev->ssid_len)
		err = __cfg80211_leave_ibss(rdev, dev, true);
	wdev_unlock(wdev);

	अगर (err)
		वापस err;

	अगर (bssid) अणु
		स_नकल(wdev->wext.bssid, bssid, ETH_ALEN);
		wdev->wext.ibss.bssid = wdev->wext.bssid;
	पूर्ण अन्यथा
		wdev->wext.ibss.bssid = शून्य;

	wdev_lock(wdev);
	err = cfg80211_ibss_wext_join(rdev, wdev);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

पूर्णांक cfg80211_ibss_wext_giwap(काष्ठा net_device *dev,
			     काष्ठा iw_request_info *info,
			     काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	/* call only क्रम ibss! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_ADHOC))
		वापस -EINVAL;

	ap_addr->sa_family = ARPHRD_ETHER;

	wdev_lock(wdev);
	अगर (wdev->current_bss)
		स_नकल(ap_addr->sa_data, wdev->current_bss->pub.bssid, ETH_ALEN);
	अन्यथा अगर (wdev->wext.ibss.bssid)
		स_नकल(ap_addr->sa_data, wdev->wext.ibss.bssid, ETH_ALEN);
	अन्यथा
		eth_zero_addr(ap_addr->sa_data);

	wdev_unlock(wdev);

	वापस 0;
पूर्ण
#पूर्ण_अगर
