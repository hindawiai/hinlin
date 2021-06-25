<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cfg80211 wext compat क्रम managed mode.
 *
 * Copyright 2009	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2009, 2020-2021 Intel Corporation.
 */

#समावेश <linux/export.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <net/cfg80211.h>
#समावेश <net/cfg80211-wext.h>
#समावेश "wext-compat.h"
#समावेश "nl80211.h"

पूर्णांक cfg80211_mgd_wext_connect(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_cached_keys *ck = शून्य;
	स्थिर u8 *prev_bssid = शून्य;
	पूर्णांक err, i;

	ASSERT_RTNL();
	ASSERT_WDEV_LOCK(wdev);

	अगर (!netअगर_running(wdev->netdev))
		वापस 0;

	wdev->wext.connect.ie = wdev->wext.ie;
	wdev->wext.connect.ie_len = wdev->wext.ie_len;

	/* Use शेष background scan period */
	wdev->wext.connect.bg_scan_period = -1;

	अगर (wdev->wext.keys) अणु
		wdev->wext.keys->def = wdev->wext.शेष_key;
		अगर (wdev->wext.शेष_key != -1)
			wdev->wext.connect.privacy = true;
	पूर्ण

	अगर (!wdev->wext.connect.ssid_len)
		वापस 0;

	अगर (wdev->wext.keys && wdev->wext.keys->def != -1) अणु
		ck = kmemdup(wdev->wext.keys, माप(*ck), GFP_KERNEL);
		अगर (!ck)
			वापस -ENOMEM;
		क्रम (i = 0; i < CFG80211_MAX_WEP_KEYS; i++)
			ck->params[i].key = ck->data[i];
	पूर्ण

	अगर (wdev->wext.prev_bssid_valid)
		prev_bssid = wdev->wext.prev_bssid;

	err = cfg80211_connect(rdev, wdev->netdev,
			       &wdev->wext.connect, ck, prev_bssid);
	अगर (err)
		kमुक्त_sensitive(ck);

	वापस err;
पूर्ण

पूर्णांक cfg80211_mgd_wext_siwfreq(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      काष्ठा iw_freq *wextfreq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा ieee80211_channel *chan = शून्य;
	पूर्णांक err, freq;

	/* call only क्रम station! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION))
		वापस -EINVAL;

	freq = cfg80211_wext_freq(wextfreq);
	अगर (freq < 0)
		वापस freq;

	अगर (freq) अणु
		chan = ieee80211_get_channel(wdev->wiphy, freq);
		अगर (!chan)
			वापस -EINVAL;
		अगर (chan->flags & IEEE80211_CHAN_DISABLED)
			वापस -EINVAL;
	पूर्ण

	wdev_lock(wdev);

	अगर (wdev->conn) अणु
		bool event = true;

		अगर (wdev->wext.connect.channel == chan) अणु
			err = 0;
			जाओ out;
		पूर्ण

		/* अगर SSID set, we'll try right again, aव्योम event */
		अगर (wdev->wext.connect.ssid_len)
			event = false;
		err = cfg80211_disconnect(rdev, dev,
					  WLAN_REASON_DEAUTH_LEAVING, event);
		अगर (err)
			जाओ out;
	पूर्ण

	wdev->wext.connect.channel = chan;
	err = cfg80211_mgd_wext_connect(rdev, wdev);
 out:
	wdev_unlock(wdev);
	वापस err;
पूर्ण

पूर्णांक cfg80211_mgd_wext_giwfreq(काष्ठा net_device *dev,
			      काष्ठा iw_request_info *info,
			      काष्ठा iw_freq *freq, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा ieee80211_channel *chan = शून्य;

	/* call only क्रम station! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION))
		वापस -EINVAL;

	wdev_lock(wdev);
	अगर (wdev->current_bss)
		chan = wdev->current_bss->pub.channel;
	अन्यथा अगर (wdev->wext.connect.channel)
		chan = wdev->wext.connect.channel;
	wdev_unlock(wdev);

	अगर (chan) अणु
		freq->m = chan->center_freq;
		freq->e = 6;
		वापस 0;
	पूर्ण

	/* no channel अगर not joining */
	वापस -EINVAL;
पूर्ण

पूर्णांक cfg80211_mgd_wext_siwessid(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_poपूर्णांक *data, अक्षर *ssid)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	माप_प्रकार len = data->length;
	पूर्णांक err;

	/* call only क्रम station! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION))
		वापस -EINVAL;

	अगर (!data->flags)
		len = 0;

	/* iwconfig uses nul termination in SSID.. */
	अगर (len > 0 && ssid[len - 1] == '\0')
		len--;

	wdev_lock(wdev);

	err = 0;

	अगर (wdev->conn) अणु
		bool event = true;

		अगर (wdev->wext.connect.ssid && len &&
		    len == wdev->wext.connect.ssid_len &&
		    स_भेद(wdev->wext.connect.ssid, ssid, len) == 0)
			जाओ out;

		/* अगर SSID set now, we'll try to connect, aव्योम event */
		अगर (len)
			event = false;
		err = cfg80211_disconnect(rdev, dev,
					  WLAN_REASON_DEAUTH_LEAVING, event);
		अगर (err)
			जाओ out;
	पूर्ण

	wdev->wext.prev_bssid_valid = false;
	wdev->wext.connect.ssid = wdev->wext.ssid;
	स_नकल(wdev->wext.ssid, ssid, len);
	wdev->wext.connect.ssid_len = len;

	wdev->wext.connect.crypto.control_port = false;
	wdev->wext.connect.crypto.control_port_ethertype =
					cpu_to_be16(ETH_P_PAE);

	err = cfg80211_mgd_wext_connect(rdev, wdev);
 out:
	wdev_unlock(wdev);
	वापस err;
पूर्ण

पूर्णांक cfg80211_mgd_wext_giwessid(काष्ठा net_device *dev,
			       काष्ठा iw_request_info *info,
			       काष्ठा iw_poपूर्णांक *data, अक्षर *ssid)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक ret = 0;

	/* call only क्रम station! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION))
		वापस -EINVAL;

	data->flags = 0;

	wdev_lock(wdev);
	अगर (wdev->current_bss) अणु
		स्थिर u8 *ie;

		rcu_पढ़ो_lock();
		ie = ieee80211_bss_get_ie(&wdev->current_bss->pub,
					  WLAN_EID_SSID);
		अगर (ie) अणु
			data->flags = 1;
			data->length = ie[1];
			अगर (data->length > IW_ESSID_MAX_SIZE)
				ret = -EINVAL;
			अन्यथा
				स_नकल(ssid, ie + 2, data->length);
		पूर्ण
		rcu_पढ़ो_unlock();
	पूर्ण अन्यथा अगर (wdev->wext.connect.ssid && wdev->wext.connect.ssid_len) अणु
		data->flags = 1;
		data->length = wdev->wext.connect.ssid_len;
		स_नकल(ssid, wdev->wext.connect.ssid, data->length);
	पूर्ण
	wdev_unlock(wdev);

	वापस ret;
पूर्ण

पूर्णांक cfg80211_mgd_wext_siwap(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u8 *bssid = ap_addr->sa_data;
	पूर्णांक err;

	/* call only क्रम station! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION))
		वापस -EINVAL;

	अगर (ap_addr->sa_family != ARPHRD_ETHER)
		वापस -EINVAL;

	/* स्वतःmatic mode */
	अगर (is_zero_ether_addr(bssid) || is_broadcast_ether_addr(bssid))
		bssid = शून्य;

	wdev_lock(wdev);

	अगर (wdev->conn) अणु
		err = 0;
		/* both स्वतःmatic */
		अगर (!bssid && !wdev->wext.connect.bssid)
			जाओ out;

		/* fixed alपढ़ोy - and no change */
		अगर (wdev->wext.connect.bssid && bssid &&
		    ether_addr_equal(bssid, wdev->wext.connect.bssid))
			जाओ out;

		err = cfg80211_disconnect(rdev, dev,
					  WLAN_REASON_DEAUTH_LEAVING, false);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (bssid) अणु
		स_नकल(wdev->wext.bssid, bssid, ETH_ALEN);
		wdev->wext.connect.bssid = wdev->wext.bssid;
	पूर्ण अन्यथा
		wdev->wext.connect.bssid = शून्य;

	err = cfg80211_mgd_wext_connect(rdev, wdev);
 out:
	wdev_unlock(wdev);
	वापस err;
पूर्ण

पूर्णांक cfg80211_mgd_wext_giwap(काष्ठा net_device *dev,
			    काष्ठा iw_request_info *info,
			    काष्ठा sockaddr *ap_addr, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	/* call only क्रम station! */
	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION))
		वापस -EINVAL;

	ap_addr->sa_family = ARPHRD_ETHER;

	wdev_lock(wdev);
	अगर (wdev->current_bss)
		स_नकल(ap_addr->sa_data, wdev->current_bss->pub.bssid, ETH_ALEN);
	अन्यथा
		eth_zero_addr(ap_addr->sa_data);
	wdev_unlock(wdev);

	वापस 0;
पूर्ण

पूर्णांक cfg80211_wext_siwgenie(काष्ठा net_device *dev,
			   काष्ठा iw_request_info *info,
			   काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u8 *ie = extra;
	पूर्णांक ie_len = data->length, err;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	अगर (!ie_len)
		ie = शून्य;

	wdev_lock(wdev);

	/* no change */
	err = 0;
	अगर (wdev->wext.ie_len == ie_len &&
	    स_भेद(wdev->wext.ie, ie, ie_len) == 0)
		जाओ out;

	अगर (ie_len) अणु
		ie = kmemdup(extra, ie_len, GFP_KERNEL);
		अगर (!ie) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा
		ie = शून्य;

	kमुक्त(wdev->wext.ie);
	wdev->wext.ie = ie;
	wdev->wext.ie_len = ie_len;

	अगर (wdev->conn) अणु
		err = cfg80211_disconnect(rdev, dev,
					  WLAN_REASON_DEAUTH_LEAVING, false);
		अगर (err)
			जाओ out;
	पूर्ण

	/* userspace better not think we'll reconnect */
	err = 0;
 out:
	wdev_unlock(wdev);
	वापस err;
पूर्ण

पूर्णांक cfg80211_wext_siwmlme(काष्ठा net_device *dev,
			  काष्ठा iw_request_info *info,
			  काष्ठा iw_poपूर्णांक *data, अक्षर *extra)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा iw_mlme *mlme = (काष्ठा iw_mlme *)extra;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	पूर्णांक err;

	अगर (!wdev)
		वापस -EOPNOTSUPP;

	rdev = wiphy_to_rdev(wdev->wiphy);

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION)
		वापस -EINVAL;

	अगर (mlme->addr.sa_family != ARPHRD_ETHER)
		वापस -EINVAL;

	wiphy_lock(&rdev->wiphy);
	wdev_lock(wdev);
	चयन (mlme->cmd) अणु
	हाल IW_MLME_DEAUTH:
	हाल IW_MLME_DISASSOC:
		err = cfg80211_disconnect(rdev, dev, mlme->reason_code, true);
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		अवरोध;
	पूर्ण
	wdev_unlock(wdev);
	wiphy_unlock(&rdev->wiphy);

	वापस err;
पूर्ण
