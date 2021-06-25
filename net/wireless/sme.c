<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * SME code क्रम cfg80211
 * both driver SME event handling and the SME implementation
 * (क्रम nl80211's connect() and wext)
 *
 * Copyright 2009	Johannes Berg <johannes@sipsolutions.net>
 * Copyright (C) 2009, 2020 Intel Corporation. All rights reserved.
 * Copyright 2017	Intel Deutschland GmbH
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_arp.h>
#समावेश <linux/slab.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/wireless.h>
#समावेश <linux/export.h>
#समावेश <net/iw_handler.h>
#समावेश <net/cfg80211.h>
#समावेश <net/rtnetlink.h>
#समावेश "nl80211.h"
#समावेश "reg.h"
#समावेश "rdev-ops.h"

/*
 * Software SME in cfg80211, using auth/assoc/deauth calls to the
 * driver. This is क्रम implementing nl80211's connect/disconnect
 * and wireless extensions (अगर configured.)
 */

काष्ठा cfg80211_conn अणु
	काष्ठा cfg80211_connect_params params;
	/* these are sub-states of the _CONNECTING sme_state */
	क्रमागत अणु
		CFG80211_CONN_SCANNING,
		CFG80211_CONN_SCAN_AGAIN,
		CFG80211_CONN_AUTHENTICATE_NEXT,
		CFG80211_CONN_AUTHENTICATING,
		CFG80211_CONN_AUTH_FAILED_TIMEOUT,
		CFG80211_CONN_ASSOCIATE_NEXT,
		CFG80211_CONN_ASSOCIATING,
		CFG80211_CONN_ASSOC_FAILED,
		CFG80211_CONN_ASSOC_FAILED_TIMEOUT,
		CFG80211_CONN_DEAUTH,
		CFG80211_CONN_ABANDON,
		CFG80211_CONN_CONNECTED,
	पूर्ण state;
	u8 bssid[ETH_ALEN], prev_bssid[ETH_ALEN];
	स्थिर u8 *ie;
	माप_प्रकार ie_len;
	bool स्वतः_auth, prev_bssid_valid;
पूर्ण;

अटल व्योम cfg80211_sme_मुक्त(काष्ठा wireless_dev *wdev)
अणु
	अगर (!wdev->conn)
		वापस;

	kमुक्त(wdev->conn->ie);
	kमुक्त(wdev->conn);
	wdev->conn = शून्य;
पूर्ण

अटल पूर्णांक cfg80211_conn_scan(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_scan_request *request;
	पूर्णांक n_channels, err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (rdev->scan_req || rdev->scan_msg)
		वापस -EBUSY;

	अगर (wdev->conn->params.channel)
		n_channels = 1;
	अन्यथा
		n_channels = ieee80211_get_num_supported_channels(wdev->wiphy);

	request = kzalloc(माप(*request) + माप(request->ssids[0]) +
			  माप(request->channels[0]) * n_channels,
			  GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	अगर (wdev->conn->params.channel) अणु
		क्रमागत nl80211_band band = wdev->conn->params.channel->band;
		काष्ठा ieee80211_supported_band *sband =
			wdev->wiphy->bands[band];

		अगर (!sband) अणु
			kमुक्त(request);
			वापस -EINVAL;
		पूर्ण
		request->channels[0] = wdev->conn->params.channel;
		request->rates[band] = (1 << sband->n_bitrates) - 1;
	पूर्ण अन्यथा अणु
		पूर्णांक i = 0, j;
		क्रमागत nl80211_band band;
		काष्ठा ieee80211_supported_band *bands;
		काष्ठा ieee80211_channel *channel;

		क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
			bands = wdev->wiphy->bands[band];
			अगर (!bands)
				जारी;
			क्रम (j = 0; j < bands->n_channels; j++) अणु
				channel = &bands->channels[j];
				अगर (channel->flags & IEEE80211_CHAN_DISABLED)
					जारी;
				request->channels[i++] = channel;
			पूर्ण
			request->rates[band] = (1 << bands->n_bitrates) - 1;
		पूर्ण
		n_channels = i;
	पूर्ण
	request->n_channels = n_channels;
	request->ssids = (व्योम *)&request->channels[n_channels];
	request->n_ssids = 1;

	स_नकल(request->ssids[0].ssid, wdev->conn->params.ssid,
		wdev->conn->params.ssid_len);
	request->ssids[0].ssid_len = wdev->conn->params.ssid_len;

	eth_broadcast_addr(request->bssid);

	request->wdev = wdev;
	request->wiphy = &rdev->wiphy;
	request->scan_start = jअगरfies;

	rdev->scan_req = request;

	err = rdev_scan(rdev, request);
	अगर (!err) अणु
		wdev->conn->state = CFG80211_CONN_SCANNING;
		nl80211_send_scan_start(rdev, wdev);
		dev_hold(wdev->netdev);
	पूर्ण अन्यथा अणु
		rdev->scan_req = शून्य;
		kमुक्त(request);
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक cfg80211_conn_करो_work(काष्ठा wireless_dev *wdev,
				 क्रमागत nl80211_समयout_reason *treason)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_connect_params *params;
	काष्ठा cfg80211_assoc_request req = अणुपूर्ण;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (!wdev->conn)
		वापस 0;

	params = &wdev->conn->params;

	चयन (wdev->conn->state) अणु
	हाल CFG80211_CONN_SCANNING:
		/* didn't find it during scan ... */
		वापस -ENOENT;
	हाल CFG80211_CONN_SCAN_AGAIN:
		वापस cfg80211_conn_scan(wdev);
	हाल CFG80211_CONN_AUTHENTICATE_NEXT:
		अगर (WARN_ON(!rdev->ops->auth))
			वापस -EOPNOTSUPP;
		wdev->conn->state = CFG80211_CONN_AUTHENTICATING;
		वापस cfg80211_mlme_auth(rdev, wdev->netdev,
					  params->channel, params->auth_type,
					  params->bssid,
					  params->ssid, params->ssid_len,
					  शून्य, 0,
					  params->key, params->key_len,
					  params->key_idx, शून्य, 0);
	हाल CFG80211_CONN_AUTH_FAILED_TIMEOUT:
		*treason = NL80211_TIMEOUT_AUTH;
		वापस -ENOTCONN;
	हाल CFG80211_CONN_ASSOCIATE_NEXT:
		अगर (WARN_ON(!rdev->ops->assoc))
			वापस -EOPNOTSUPP;
		wdev->conn->state = CFG80211_CONN_ASSOCIATING;
		अगर (wdev->conn->prev_bssid_valid)
			req.prev_bssid = wdev->conn->prev_bssid;
		req.ie = params->ie;
		req.ie_len = params->ie_len;
		req.use_mfp = params->mfp != NL80211_MFP_NO;
		req.crypto = params->crypto;
		req.flags = params->flags;
		req.ht_capa = params->ht_capa;
		req.ht_capa_mask = params->ht_capa_mask;
		req.vht_capa = params->vht_capa;
		req.vht_capa_mask = params->vht_capa_mask;

		err = cfg80211_mlme_assoc(rdev, wdev->netdev, params->channel,
					  params->bssid, params->ssid,
					  params->ssid_len, &req);
		अगर (err)
			cfg80211_mlme_deauth(rdev, wdev->netdev, params->bssid,
					     शून्य, 0,
					     WLAN_REASON_DEAUTH_LEAVING,
					     false);
		वापस err;
	हाल CFG80211_CONN_ASSOC_FAILED_TIMEOUT:
		*treason = NL80211_TIMEOUT_ASSOC;
		fallthrough;
	हाल CFG80211_CONN_ASSOC_FAILED:
		cfg80211_mlme_deauth(rdev, wdev->netdev, params->bssid,
				     शून्य, 0,
				     WLAN_REASON_DEAUTH_LEAVING, false);
		वापस -ENOTCONN;
	हाल CFG80211_CONN_DEAUTH:
		cfg80211_mlme_deauth(rdev, wdev->netdev, params->bssid,
				     शून्य, 0,
				     WLAN_REASON_DEAUTH_LEAVING, false);
		fallthrough;
	हाल CFG80211_CONN_ABANDON:
		/* मुक्त directly, disconnected event alपढ़ोy sent */
		cfg80211_sme_मुक्त(wdev);
		वापस 0;
	शेष:
		वापस 0;
	पूर्ण
पूर्ण

व्योम cfg80211_conn_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev =
		container_of(work, काष्ठा cfg80211_रेजिस्टरed_device, conn_work);
	काष्ठा wireless_dev *wdev;
	u8 bssid_buf[ETH_ALEN], *bssid = शून्य;
	क्रमागत nl80211_समयout_reason treason;

	wiphy_lock(&rdev->wiphy);

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		अगर (!wdev->netdev)
			जारी;

		wdev_lock(wdev);
		अगर (!netअगर_running(wdev->netdev)) अणु
			wdev_unlock(wdev);
			जारी;
		पूर्ण
		अगर (!wdev->conn ||
		    wdev->conn->state == CFG80211_CONN_CONNECTED) अणु
			wdev_unlock(wdev);
			जारी;
		पूर्ण
		अगर (wdev->conn->params.bssid) अणु
			स_नकल(bssid_buf, wdev->conn->params.bssid, ETH_ALEN);
			bssid = bssid_buf;
		पूर्ण
		treason = NL80211_TIMEOUT_UNSPECIFIED;
		अगर (cfg80211_conn_करो_work(wdev, &treason)) अणु
			काष्ठा cfg80211_connect_resp_params cr;

			स_रखो(&cr, 0, माप(cr));
			cr.status = -1;
			cr.bssid = bssid;
			cr.समयout_reason = treason;
			__cfg80211_connect_result(wdev->netdev, &cr, false);
		पूर्ण
		wdev_unlock(wdev);
	पूर्ण

	wiphy_unlock(&rdev->wiphy);
पूर्ण

/* Returned bss is reference counted and must be cleaned up appropriately. */
अटल काष्ठा cfg80211_bss *cfg80211_get_conn_bss(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_bss *bss;

	ASSERT_WDEV_LOCK(wdev);

	bss = cfg80211_get_bss(wdev->wiphy, wdev->conn->params.channel,
			       wdev->conn->params.bssid,
			       wdev->conn->params.ssid,
			       wdev->conn->params.ssid_len,
			       wdev->conn_bss_type,
			       IEEE80211_PRIVACY(wdev->conn->params.privacy));
	अगर (!bss)
		वापस शून्य;

	स_नकल(wdev->conn->bssid, bss->bssid, ETH_ALEN);
	wdev->conn->params.bssid = wdev->conn->bssid;
	wdev->conn->params.channel = bss->channel;
	wdev->conn->state = CFG80211_CONN_AUTHENTICATE_NEXT;
	schedule_work(&rdev->conn_work);

	वापस bss;
पूर्ण

अटल व्योम __cfg80211_sme_scan_करोne(काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_bss *bss;

	ASSERT_WDEV_LOCK(wdev);

	अगर (!wdev->conn)
		वापस;

	अगर (wdev->conn->state != CFG80211_CONN_SCANNING &&
	    wdev->conn->state != CFG80211_CONN_SCAN_AGAIN)
		वापस;

	bss = cfg80211_get_conn_bss(wdev);
	अगर (bss)
		cfg80211_put_bss(&rdev->wiphy, bss);
	अन्यथा
		schedule_work(&rdev->conn_work);
पूर्ण

व्योम cfg80211_sme_scan_करोne(काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	wdev_lock(wdev);
	__cfg80211_sme_scan_करोne(dev);
	wdev_unlock(wdev);
पूर्ण

व्योम cfg80211_sme_rx_auth(काष्ठा wireless_dev *wdev, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)buf;
	u16 status_code = le16_to_cpu(mgmt->u.auth.status_code);

	ASSERT_WDEV_LOCK(wdev);

	अगर (!wdev->conn || wdev->conn->state == CFG80211_CONN_CONNECTED)
		वापस;

	अगर (status_code == WLAN_STATUS_NOT_SUPPORTED_AUTH_ALG &&
	    wdev->conn->स्वतः_auth &&
	    wdev->conn->params.auth_type != NL80211_AUTHTYPE_NETWORK_EAP) अणु
		/* select स्वतःmatically between only खोलो, shared, leap */
		चयन (wdev->conn->params.auth_type) अणु
		हाल NL80211_AUTHTYPE_OPEN_SYSTEM:
			अगर (wdev->connect_keys)
				wdev->conn->params.auth_type =
					NL80211_AUTHTYPE_SHARED_KEY;
			अन्यथा
				wdev->conn->params.auth_type =
					NL80211_AUTHTYPE_NETWORK_EAP;
			अवरोध;
		हाल NL80211_AUTHTYPE_SHARED_KEY:
			wdev->conn->params.auth_type =
				NL80211_AUTHTYPE_NETWORK_EAP;
			अवरोध;
		शेष:
			/* huh? */
			wdev->conn->params.auth_type =
				NL80211_AUTHTYPE_OPEN_SYSTEM;
			अवरोध;
		पूर्ण
		wdev->conn->state = CFG80211_CONN_AUTHENTICATE_NEXT;
		schedule_work(&rdev->conn_work);
	पूर्ण अन्यथा अगर (status_code != WLAN_STATUS_SUCCESS) अणु
		काष्ठा cfg80211_connect_resp_params cr;

		स_रखो(&cr, 0, माप(cr));
		cr.status = status_code;
		cr.bssid = mgmt->bssid;
		cr.समयout_reason = NL80211_TIMEOUT_UNSPECIFIED;
		__cfg80211_connect_result(wdev->netdev, &cr, false);
	पूर्ण अन्यथा अगर (wdev->conn->state == CFG80211_CONN_AUTHENTICATING) अणु
		wdev->conn->state = CFG80211_CONN_ASSOCIATE_NEXT;
		schedule_work(&rdev->conn_work);
	पूर्ण
पूर्ण

bool cfg80211_sme_rx_assoc_resp(काष्ठा wireless_dev *wdev, u16 status)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	अगर (!wdev->conn)
		वापस false;

	अगर (status == WLAN_STATUS_SUCCESS) अणु
		wdev->conn->state = CFG80211_CONN_CONNECTED;
		वापस false;
	पूर्ण

	अगर (wdev->conn->prev_bssid_valid) अणु
		/*
		 * Some stupid APs करोn't accept reassoc, so we
		 * need to fall back to trying regular assoc;
		 * वापस true so no event is sent to userspace.
		 */
		wdev->conn->prev_bssid_valid = false;
		wdev->conn->state = CFG80211_CONN_ASSOCIATE_NEXT;
		schedule_work(&rdev->conn_work);
		वापस true;
	पूर्ण

	wdev->conn->state = CFG80211_CONN_ASSOC_FAILED;
	schedule_work(&rdev->conn_work);
	वापस false;
पूर्ण

व्योम cfg80211_sme_deauth(काष्ठा wireless_dev *wdev)
अणु
	cfg80211_sme_मुक्त(wdev);
पूर्ण

व्योम cfg80211_sme_auth_समयout(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	अगर (!wdev->conn)
		वापस;

	wdev->conn->state = CFG80211_CONN_AUTH_FAILED_TIMEOUT;
	schedule_work(&rdev->conn_work);
पूर्ण

व्योम cfg80211_sme_disassoc(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	अगर (!wdev->conn)
		वापस;

	wdev->conn->state = CFG80211_CONN_DEAUTH;
	schedule_work(&rdev->conn_work);
पूर्ण

व्योम cfg80211_sme_assoc_समयout(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	अगर (!wdev->conn)
		वापस;

	wdev->conn->state = CFG80211_CONN_ASSOC_FAILED_TIMEOUT;
	schedule_work(&rdev->conn_work);
पूर्ण

व्योम cfg80211_sme_abanकरोn_assoc(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	अगर (!wdev->conn)
		वापस;

	wdev->conn->state = CFG80211_CONN_ABANDON;
	schedule_work(&rdev->conn_work);
पूर्ण

अटल पूर्णांक cfg80211_sme_get_conn_ies(काष्ठा wireless_dev *wdev,
				     स्थिर u8 *ies, माप_प्रकार ies_len,
				     स्थिर u8 **out_ies, माप_प्रकार *out_ies_len)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	u8 *buf;
	माप_प्रकार offs;

	अगर (!rdev->wiphy.extended_capabilities_len ||
	    (ies && cfg80211_find_ie(WLAN_EID_EXT_CAPABILITY, ies, ies_len))) अणु
		*out_ies = kmemdup(ies, ies_len, GFP_KERNEL);
		अगर (!*out_ies)
			वापस -ENOMEM;
		*out_ies_len = ies_len;
		वापस 0;
	पूर्ण

	buf = kदो_स्मृति(ies_len + rdev->wiphy.extended_capabilities_len + 2,
		      GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;

	अगर (ies_len) अणु
		अटल स्थिर u8 beक्रमe_extcapa[] = अणु
			/* not listing IEs expected to be created by driver */
			WLAN_EID_RSN,
			WLAN_EID_QOS_CAPA,
			WLAN_EID_RRM_ENABLED_CAPABILITIES,
			WLAN_EID_MOBILITY_DOMAIN,
			WLAN_EID_SUPPORTED_REGULATORY_CLASSES,
			WLAN_EID_BSS_COEX_2040,
		पूर्ण;

		offs = ieee80211_ie_split(ies, ies_len, beक्रमe_extcapa,
					  ARRAY_SIZE(beक्रमe_extcapa), 0);
		स_नकल(buf, ies, offs);
		/* leave a whole क्रम extended capabilities IE */
		स_नकल(buf + offs + rdev->wiphy.extended_capabilities_len + 2,
		       ies + offs, ies_len - offs);
	पूर्ण अन्यथा अणु
		offs = 0;
	पूर्ण

	/* place extended capabilities IE (with only driver capabilities) */
	buf[offs] = WLAN_EID_EXT_CAPABILITY;
	buf[offs + 1] = rdev->wiphy.extended_capabilities_len;
	स_नकल(buf + offs + 2,
	       rdev->wiphy.extended_capabilities,
	       rdev->wiphy.extended_capabilities_len);

	*out_ies = buf;
	*out_ies_len = ies_len + rdev->wiphy.extended_capabilities_len + 2;

	वापस 0;
पूर्ण

अटल पूर्णांक cfg80211_sme_connect(काष्ठा wireless_dev *wdev,
				काष्ठा cfg80211_connect_params *connect,
				स्थिर u8 *prev_bssid)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_bss *bss;
	पूर्णांक err;

	अगर (!rdev->ops->auth || !rdev->ops->assoc)
		वापस -EOPNOTSUPP;

	अगर (wdev->current_bss) अणु
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
		wdev->current_bss = शून्य;

		cfg80211_sme_मुक्त(wdev);
	पूर्ण

	अगर (wdev->conn)
		वापस -EINPROGRESS;

	wdev->conn = kzalloc(माप(*wdev->conn), GFP_KERNEL);
	अगर (!wdev->conn)
		वापस -ENOMEM;

	/*
	 * Copy all parameters, and treat explicitly IEs, BSSID, SSID.
	 */
	स_नकल(&wdev->conn->params, connect, माप(*connect));
	अगर (connect->bssid) अणु
		wdev->conn->params.bssid = wdev->conn->bssid;
		स_नकल(wdev->conn->bssid, connect->bssid, ETH_ALEN);
	पूर्ण

	अगर (cfg80211_sme_get_conn_ies(wdev, connect->ie, connect->ie_len,
				      &wdev->conn->ie,
				      &wdev->conn->params.ie_len)) अणु
		kमुक्त(wdev->conn);
		wdev->conn = शून्य;
		वापस -ENOMEM;
	पूर्ण
	wdev->conn->params.ie = wdev->conn->ie;

	अगर (connect->auth_type == NL80211_AUTHTYPE_AUTOMATIC) अणु
		wdev->conn->स्वतः_auth = true;
		/* start with खोलो प्रणाली ... should mostly work */
		wdev->conn->params.auth_type =
			NL80211_AUTHTYPE_OPEN_SYSTEM;
	पूर्ण अन्यथा अणु
		wdev->conn->स्वतः_auth = false;
	पूर्ण

	wdev->conn->params.ssid = wdev->ssid;
	wdev->conn->params.ssid_len = wdev->ssid_len;

	/* see अगर we have the bss alपढ़ोy */
	bss = cfg80211_get_conn_bss(wdev);

	अगर (prev_bssid) अणु
		स_नकल(wdev->conn->prev_bssid, prev_bssid, ETH_ALEN);
		wdev->conn->prev_bssid_valid = true;
	पूर्ण

	/* we're good अगर we have a matching bss काष्ठा */
	अगर (bss) अणु
		क्रमागत nl80211_समयout_reason treason;

		err = cfg80211_conn_करो_work(wdev, &treason);
		cfg80211_put_bss(wdev->wiphy, bss);
	पूर्ण अन्यथा अणु
		/* otherwise we'll need to scan क्रम the AP first */
		err = cfg80211_conn_scan(wdev);

		/*
		 * If we can't scan right now, then we need to scan again
		 * after the current scan finished, since the parameters
		 * changed (unless we find a good AP anyway).
		 */
		अगर (err == -EBUSY) अणु
			err = 0;
			wdev->conn->state = CFG80211_CONN_SCAN_AGAIN;
		पूर्ण
	पूर्ण

	अगर (err)
		cfg80211_sme_मुक्त(wdev);

	वापस err;
पूर्ण

अटल पूर्णांक cfg80211_sme_disconnect(काष्ठा wireless_dev *wdev, u16 reason)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक err;

	अगर (!wdev->conn)
		वापस 0;

	अगर (!rdev->ops->deauth)
		वापस -EOPNOTSUPP;

	अगर (wdev->conn->state == CFG80211_CONN_SCANNING ||
	    wdev->conn->state == CFG80211_CONN_SCAN_AGAIN) अणु
		err = 0;
		जाओ out;
	पूर्ण

	/* wdev->conn->params.bssid must be set अगर > SCANNING */
	err = cfg80211_mlme_deauth(rdev, wdev->netdev,
				   wdev->conn->params.bssid,
				   शून्य, 0, reason, false);
 out:
	cfg80211_sme_मुक्त(wdev);
	वापस err;
पूर्ण

/*
 * code shared क्रम in-device and software SME
 */

अटल bool cfg80211_is_all_idle(व्योम)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;
	bool is_all_idle = true;

	/*
	 * All devices must be idle as otherwise अगर you are actively
	 * scanning some new beacon hपूर्णांकs could be learned and would
	 * count as new regulatory hपूर्णांकs.
	 * Also अगर there is any other active beaconing पूर्णांकerface we
	 * need not issue a disconnect hपूर्णांक and reset any info such
	 * as chan dfs state, etc.
	 */
	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
			wdev_lock(wdev);
			अगर (wdev->conn || wdev->current_bss ||
			    cfg80211_beaconing_अगरace_active(wdev))
				is_all_idle = false;
			wdev_unlock(wdev);
		पूर्ण
	पूर्ण

	वापस is_all_idle;
पूर्ण

अटल व्योम disconnect_work(काष्ठा work_काष्ठा *work)
अणु
	rtnl_lock();
	अगर (cfg80211_is_all_idle())
		regulatory_hपूर्णांक_disconnect();
	rtnl_unlock();
पूर्ण

DECLARE_WORK(cfg80211_disconnect_work, disconnect_work);


/*
 * API calls क्रम drivers implementing connect/disconnect and
 * SME event handling
 */

/* This method must consume bss one way or another */
व्योम __cfg80211_connect_result(काष्ठा net_device *dev,
			       काष्ठा cfg80211_connect_resp_params *cr,
			       bool wextev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	स्थिर u8 *country_ie;
#अगर_घोषित CONFIG_CFG80211_WEXT
	जोड़ iwreq_data wrqu;
#पूर्ण_अगर

	ASSERT_WDEV_LOCK(wdev);

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION &&
		    wdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT)) अणु
		cfg80211_put_bss(wdev->wiphy, cr->bss);
		वापस;
	पूर्ण

	wdev->unprot_beacon_reported = 0;
	nl80211_send_connect_result(wiphy_to_rdev(wdev->wiphy), dev, cr,
				    GFP_KERNEL);

#अगर_घोषित CONFIG_CFG80211_WEXT
	अगर (wextev) अणु
		अगर (cr->req_ie && cr->status == WLAN_STATUS_SUCCESS) अणु
			स_रखो(&wrqu, 0, माप(wrqu));
			wrqu.data.length = cr->req_ie_len;
			wireless_send_event(dev, IWEVASSOCREQIE, &wrqu,
					    cr->req_ie);
		पूर्ण

		अगर (cr->resp_ie && cr->status == WLAN_STATUS_SUCCESS) अणु
			स_रखो(&wrqu, 0, माप(wrqu));
			wrqu.data.length = cr->resp_ie_len;
			wireless_send_event(dev, IWEVASSOCRESPIE, &wrqu,
					    cr->resp_ie);
		पूर्ण

		स_रखो(&wrqu, 0, माप(wrqu));
		wrqu.ap_addr.sa_family = ARPHRD_ETHER;
		अगर (cr->bssid && cr->status == WLAN_STATUS_SUCCESS) अणु
			स_नकल(wrqu.ap_addr.sa_data, cr->bssid, ETH_ALEN);
			स_नकल(wdev->wext.prev_bssid, cr->bssid, ETH_ALEN);
			wdev->wext.prev_bssid_valid = true;
		पूर्ण
		wireless_send_event(dev, SIOCGIWAP, &wrqu, शून्य);
	पूर्ण
#पूर्ण_अगर

	अगर (!cr->bss && (cr->status == WLAN_STATUS_SUCCESS)) अणु
		WARN_ON_ONCE(!wiphy_to_rdev(wdev->wiphy)->ops->connect);
		cr->bss = cfg80211_get_bss(wdev->wiphy, शून्य, cr->bssid,
					   wdev->ssid, wdev->ssid_len,
					   wdev->conn_bss_type,
					   IEEE80211_PRIVACY_ANY);
		अगर (cr->bss)
			cfg80211_hold_bss(bss_from_pub(cr->bss));
	पूर्ण

	अगर (wdev->current_bss) अणु
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
		wdev->current_bss = शून्य;
	पूर्ण

	अगर (cr->status != WLAN_STATUS_SUCCESS) अणु
		kमुक्त_sensitive(wdev->connect_keys);
		wdev->connect_keys = शून्य;
		wdev->ssid_len = 0;
		wdev->conn_owner_nlportid = 0;
		अगर (cr->bss) अणु
			cfg80211_unhold_bss(bss_from_pub(cr->bss));
			cfg80211_put_bss(wdev->wiphy, cr->bss);
		पूर्ण
		cfg80211_sme_मुक्त(wdev);
		वापस;
	पूर्ण

	अगर (WARN_ON(!cr->bss))
		वापस;

	wdev->current_bss = bss_from_pub(cr->bss);

	अगर (!(wdev->wiphy->flags & WIPHY_FLAG_HAS_STATIC_WEP))
		cfg80211_upload_connect_keys(wdev);

	rcu_पढ़ो_lock();
	country_ie = ieee80211_bss_get_ie(cr->bss, WLAN_EID_COUNTRY);
	अगर (!country_ie) अणु
		rcu_पढ़ो_unlock();
		वापस;
	पूर्ण

	country_ie = kmemdup(country_ie, 2 + country_ie[1], GFP_ATOMIC);
	rcu_पढ़ो_unlock();

	अगर (!country_ie)
		वापस;

	/*
	 * ieee80211_bss_get_ie() ensures we can access:
	 * - country_ie + 2, the start of the country ie data, and
	 * - and country_ie[1] which is the IE length
	 */
	regulatory_hपूर्णांक_country_ie(wdev->wiphy, cr->bss->channel->band,
				   country_ie + 2, country_ie[1]);
	kमुक्त(country_ie);
पूर्ण

/* Consumes bss object one way or another */
व्योम cfg80211_connect_करोne(काष्ठा net_device *dev,
			   काष्ठा cfg80211_connect_resp_params *params,
			   gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_event *ev;
	अचिन्हित दीर्घ flags;
	u8 *next;

	अगर (params->bss) अणु
		काष्ठा cfg80211_पूर्णांकernal_bss *ibss = bss_from_pub(params->bss);

		अगर (list_empty(&ibss->list)) अणु
			काष्ठा cfg80211_bss *found = शून्य, *पंचांगp = params->bss;

			found = cfg80211_get_bss(wdev->wiphy, शून्य,
						 params->bss->bssid,
						 wdev->ssid, wdev->ssid_len,
						 wdev->conn_bss_type,
						 IEEE80211_PRIVACY_ANY);
			अगर (found) अणु
				/* The same BSS is alपढ़ोy updated so use it
				 * instead, as it has latest info.
				 */
				params->bss = found;
			पूर्ण अन्यथा अणु
				/* Update with BSS provided by driver, it will
				 * be freshly added and ref cnted, we can मुक्त
				 * the old one.
				 *
				 * संकेत_valid can be false, as we are not
				 * expecting the BSS to be found.
				 *
				 * keep the old बारtamp to aव्योम confusion
				 */
				cfg80211_bss_update(rdev, ibss, false,
						    ibss->ts);
			पूर्ण

			cfg80211_put_bss(wdev->wiphy, पंचांगp);
		पूर्ण
	पूर्ण

	ev = kzalloc(माप(*ev) + (params->bssid ? ETH_ALEN : 0) +
		     params->req_ie_len + params->resp_ie_len +
		     params->fils.kek_len + params->fils.pmk_len +
		     (params->fils.pmkid ? WLAN_PMKID_LEN : 0), gfp);
	अगर (!ev) अणु
		cfg80211_put_bss(wdev->wiphy, params->bss);
		वापस;
	पूर्ण

	ev->type = EVENT_CONNECT_RESULT;
	next = ((u8 *)ev) + माप(*ev);
	अगर (params->bssid) अणु
		ev->cr.bssid = next;
		स_नकल((व्योम *)ev->cr.bssid, params->bssid, ETH_ALEN);
		next += ETH_ALEN;
	पूर्ण
	अगर (params->req_ie_len) अणु
		ev->cr.req_ie = next;
		ev->cr.req_ie_len = params->req_ie_len;
		स_नकल((व्योम *)ev->cr.req_ie, params->req_ie,
		       params->req_ie_len);
		next += params->req_ie_len;
	पूर्ण
	अगर (params->resp_ie_len) अणु
		ev->cr.resp_ie = next;
		ev->cr.resp_ie_len = params->resp_ie_len;
		स_नकल((व्योम *)ev->cr.resp_ie, params->resp_ie,
		       params->resp_ie_len);
		next += params->resp_ie_len;
	पूर्ण
	अगर (params->fils.kek_len) अणु
		ev->cr.fils.kek = next;
		ev->cr.fils.kek_len = params->fils.kek_len;
		स_नकल((व्योम *)ev->cr.fils.kek, params->fils.kek,
		       params->fils.kek_len);
		next += params->fils.kek_len;
	पूर्ण
	अगर (params->fils.pmk_len) अणु
		ev->cr.fils.pmk = next;
		ev->cr.fils.pmk_len = params->fils.pmk_len;
		स_नकल((व्योम *)ev->cr.fils.pmk, params->fils.pmk,
		       params->fils.pmk_len);
		next += params->fils.pmk_len;
	पूर्ण
	अगर (params->fils.pmkid) अणु
		ev->cr.fils.pmkid = next;
		स_नकल((व्योम *)ev->cr.fils.pmkid, params->fils.pmkid,
		       WLAN_PMKID_LEN);
		next += WLAN_PMKID_LEN;
	पूर्ण
	ev->cr.fils.update_erp_next_seq_num = params->fils.update_erp_next_seq_num;
	अगर (params->fils.update_erp_next_seq_num)
		ev->cr.fils.erp_next_seq_num = params->fils.erp_next_seq_num;
	अगर (params->bss)
		cfg80211_hold_bss(bss_from_pub(params->bss));
	ev->cr.bss = params->bss;
	ev->cr.status = params->status;
	ev->cr.समयout_reason = params->समयout_reason;

	spin_lock_irqsave(&wdev->event_lock, flags);
	list_add_tail(&ev->list, &wdev->event_list);
	spin_unlock_irqrestore(&wdev->event_lock, flags);
	queue_work(cfg80211_wq, &rdev->event_work);
पूर्ण
EXPORT_SYMBOL(cfg80211_connect_करोne);

/* Consumes bss object one way or another */
व्योम __cfg80211_roamed(काष्ठा wireless_dev *wdev,
		       काष्ठा cfg80211_roam_info *info)
अणु
#अगर_घोषित CONFIG_CFG80211_WEXT
	जोड़ iwreq_data wrqu;
#पूर्ण_अगर
	ASSERT_WDEV_LOCK(wdev);

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION &&
		    wdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT))
		जाओ out;

	अगर (WARN_ON(!wdev->current_bss))
		जाओ out;

	cfg80211_unhold_bss(wdev->current_bss);
	cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
	wdev->current_bss = शून्य;

	अगर (WARN_ON(!info->bss))
		वापस;

	cfg80211_hold_bss(bss_from_pub(info->bss));
	wdev->current_bss = bss_from_pub(info->bss);

	wdev->unprot_beacon_reported = 0;
	nl80211_send_roamed(wiphy_to_rdev(wdev->wiphy),
			    wdev->netdev, info, GFP_KERNEL);

#अगर_घोषित CONFIG_CFG80211_WEXT
	अगर (info->req_ie) अणु
		स_रखो(&wrqu, 0, माप(wrqu));
		wrqu.data.length = info->req_ie_len;
		wireless_send_event(wdev->netdev, IWEVASSOCREQIE,
				    &wrqu, info->req_ie);
	पूर्ण

	अगर (info->resp_ie) अणु
		स_रखो(&wrqu, 0, माप(wrqu));
		wrqu.data.length = info->resp_ie_len;
		wireless_send_event(wdev->netdev, IWEVASSOCRESPIE,
				    &wrqu, info->resp_ie);
	पूर्ण

	स_रखो(&wrqu, 0, माप(wrqu));
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	स_नकल(wrqu.ap_addr.sa_data, info->bss->bssid, ETH_ALEN);
	स_नकल(wdev->wext.prev_bssid, info->bss->bssid, ETH_ALEN);
	wdev->wext.prev_bssid_valid = true;
	wireless_send_event(wdev->netdev, SIOCGIWAP, &wrqu, शून्य);
#पूर्ण_अगर

	वापस;
out:
	cfg80211_put_bss(wdev->wiphy, info->bss);
पूर्ण

/* Consumes info->bss object one way or another */
व्योम cfg80211_roamed(काष्ठा net_device *dev, काष्ठा cfg80211_roam_info *info,
		     gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_event *ev;
	अचिन्हित दीर्घ flags;
	u8 *next;

	अगर (!info->bss) अणु
		info->bss = cfg80211_get_bss(wdev->wiphy, info->channel,
					     info->bssid, wdev->ssid,
					     wdev->ssid_len,
					     wdev->conn_bss_type,
					     IEEE80211_PRIVACY_ANY);
	पूर्ण

	अगर (WARN_ON(!info->bss))
		वापस;

	ev = kzalloc(माप(*ev) + info->req_ie_len + info->resp_ie_len +
		     info->fils.kek_len + info->fils.pmk_len +
		     (info->fils.pmkid ? WLAN_PMKID_LEN : 0), gfp);
	अगर (!ev) अणु
		cfg80211_put_bss(wdev->wiphy, info->bss);
		वापस;
	पूर्ण

	ev->type = EVENT_ROAMED;
	next = ((u8 *)ev) + माप(*ev);
	अगर (info->req_ie_len) अणु
		ev->rm.req_ie = next;
		ev->rm.req_ie_len = info->req_ie_len;
		स_नकल((व्योम *)ev->rm.req_ie, info->req_ie, info->req_ie_len);
		next += info->req_ie_len;
	पूर्ण
	अगर (info->resp_ie_len) अणु
		ev->rm.resp_ie = next;
		ev->rm.resp_ie_len = info->resp_ie_len;
		स_नकल((व्योम *)ev->rm.resp_ie, info->resp_ie,
		       info->resp_ie_len);
		next += info->resp_ie_len;
	पूर्ण
	अगर (info->fils.kek_len) अणु
		ev->rm.fils.kek = next;
		ev->rm.fils.kek_len = info->fils.kek_len;
		स_नकल((व्योम *)ev->rm.fils.kek, info->fils.kek,
		       info->fils.kek_len);
		next += info->fils.kek_len;
	पूर्ण
	अगर (info->fils.pmk_len) अणु
		ev->rm.fils.pmk = next;
		ev->rm.fils.pmk_len = info->fils.pmk_len;
		स_नकल((व्योम *)ev->rm.fils.pmk, info->fils.pmk,
		       info->fils.pmk_len);
		next += info->fils.pmk_len;
	पूर्ण
	अगर (info->fils.pmkid) अणु
		ev->rm.fils.pmkid = next;
		स_नकल((व्योम *)ev->rm.fils.pmkid, info->fils.pmkid,
		       WLAN_PMKID_LEN);
		next += WLAN_PMKID_LEN;
	पूर्ण
	ev->rm.fils.update_erp_next_seq_num = info->fils.update_erp_next_seq_num;
	अगर (info->fils.update_erp_next_seq_num)
		ev->rm.fils.erp_next_seq_num = info->fils.erp_next_seq_num;
	ev->rm.bss = info->bss;

	spin_lock_irqsave(&wdev->event_lock, flags);
	list_add_tail(&ev->list, &wdev->event_list);
	spin_unlock_irqrestore(&wdev->event_lock, flags);
	queue_work(cfg80211_wq, &rdev->event_work);
पूर्ण
EXPORT_SYMBOL(cfg80211_roamed);

व्योम __cfg80211_port_authorized(काष्ठा wireless_dev *wdev, स्थिर u8 *bssid)
अणु
	ASSERT_WDEV_LOCK(wdev);

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION))
		वापस;

	अगर (WARN_ON(!wdev->current_bss) ||
	    WARN_ON(!ether_addr_equal(wdev->current_bss->pub.bssid, bssid)))
		वापस;

	nl80211_send_port_authorized(wiphy_to_rdev(wdev->wiphy), wdev->netdev,
				     bssid);
पूर्ण

व्योम cfg80211_port_authorized(काष्ठा net_device *dev, स्थिर u8 *bssid,
			      gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_event *ev;
	अचिन्हित दीर्घ flags;

	अगर (WARN_ON(!bssid))
		वापस;

	ev = kzalloc(माप(*ev), gfp);
	अगर (!ev)
		वापस;

	ev->type = EVENT_PORT_AUTHORIZED;
	स_नकल(ev->pa.bssid, bssid, ETH_ALEN);

	/*
	 * Use the wdev event list so that अगर there are pending
	 * connected/roamed events, they will be reported first.
	 */
	spin_lock_irqsave(&wdev->event_lock, flags);
	list_add_tail(&ev->list, &wdev->event_list);
	spin_unlock_irqrestore(&wdev->event_lock, flags);
	queue_work(cfg80211_wq, &rdev->event_work);
पूर्ण
EXPORT_SYMBOL(cfg80211_port_authorized);

व्योम __cfg80211_disconnected(काष्ठा net_device *dev, स्थिर u8 *ie,
			     माप_प्रकार ie_len, u16 reason, bool from_ap)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	पूर्णांक i;
#अगर_घोषित CONFIG_CFG80211_WEXT
	जोड़ iwreq_data wrqu;
#पूर्ण_अगर

	ASSERT_WDEV_LOCK(wdev);

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_STATION &&
		    wdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT))
		वापस;

	अगर (wdev->current_bss) अणु
		cfg80211_unhold_bss(wdev->current_bss);
		cfg80211_put_bss(wdev->wiphy, &wdev->current_bss->pub);
	पूर्ण

	wdev->current_bss = शून्य;
	wdev->ssid_len = 0;
	wdev->conn_owner_nlportid = 0;
	kमुक्त_sensitive(wdev->connect_keys);
	wdev->connect_keys = शून्य;

	nl80211_send_disconnected(rdev, dev, reason, ie, ie_len, from_ap);

	/* stop critical protocol अगर supported */
	अगर (rdev->ops->crit_proto_stop && rdev->crit_proto_nlportid) अणु
		rdev->crit_proto_nlportid = 0;
		rdev_crit_proto_stop(rdev, wdev);
	पूर्ण

	/*
	 * Delete all the keys ... pairwise keys can't really
	 * exist any more anyway, but शेष keys might.
	 */
	अगर (rdev->ops->del_key) अणु
		पूर्णांक max_key_idx = 5;

		अगर (wiphy_ext_feature_isset(
			    wdev->wiphy,
			    NL80211_EXT_FEATURE_BEACON_PROTECTION) ||
		    wiphy_ext_feature_isset(
			    wdev->wiphy,
			    NL80211_EXT_FEATURE_BEACON_PROTECTION_CLIENT))
			max_key_idx = 7;
		क्रम (i = 0; i <= max_key_idx; i++)
			rdev_del_key(rdev, dev, i, false, शून्य);
	पूर्ण

	rdev_set_qos_map(rdev, dev, शून्य);

#अगर_घोषित CONFIG_CFG80211_WEXT
	स_रखो(&wrqu, 0, माप(wrqu));
	wrqu.ap_addr.sa_family = ARPHRD_ETHER;
	wireless_send_event(dev, SIOCGIWAP, &wrqu, शून्य);
	wdev->wext.connect.ssid_len = 0;
#पूर्ण_अगर

	schedule_work(&cfg80211_disconnect_work);
पूर्ण

व्योम cfg80211_disconnected(काष्ठा net_device *dev, u16 reason,
			   स्थिर u8 *ie, माप_प्रकार ie_len,
			   bool locally_generated, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा cfg80211_event *ev;
	अचिन्हित दीर्घ flags;

	ev = kzalloc(माप(*ev) + ie_len, gfp);
	अगर (!ev)
		वापस;

	ev->type = EVENT_DISCONNECTED;
	ev->dc.ie = ((u8 *)ev) + माप(*ev);
	ev->dc.ie_len = ie_len;
	स_नकल((व्योम *)ev->dc.ie, ie, ie_len);
	ev->dc.reason = reason;
	ev->dc.locally_generated = locally_generated;

	spin_lock_irqsave(&wdev->event_lock, flags);
	list_add_tail(&ev->list, &wdev->event_list);
	spin_unlock_irqrestore(&wdev->event_lock, flags);
	queue_work(cfg80211_wq, &rdev->event_work);
पूर्ण
EXPORT_SYMBOL(cfg80211_disconnected);

/*
 * API calls क्रम nl80211/wext compatibility code
 */
पूर्णांक cfg80211_connect(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     काष्ठा net_device *dev,
		     काष्ठा cfg80211_connect_params *connect,
		     काष्ठा cfg80211_cached_keys *connkeys,
		     स्थिर u8 *prev_bssid)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	/*
	 * If we have an ssid_len, we're trying to connect or are
	 * alपढ़ोy connected, so reject a new SSID unless it's the
	 * same (which is the हाल क्रम re-association.)
	 */
	अगर (wdev->ssid_len &&
	    (wdev->ssid_len != connect->ssid_len ||
	     स_भेद(wdev->ssid, connect->ssid, wdev->ssid_len)))
		वापस -EALREADY;

	/*
	 * If connected, reject (re-)association unless prev_bssid
	 * matches the current BSSID.
	 */
	अगर (wdev->current_bss) अणु
		अगर (!prev_bssid)
			वापस -EALREADY;
		अगर (!ether_addr_equal(prev_bssid, wdev->current_bss->pub.bssid))
			वापस -ENOTCONN;
	पूर्ण

	/*
	 * Reject अगर we're in the process of connecting with WEP,
	 * this हाल isn't very पूर्णांकeresting and trying to handle
	 * it would make the code much more complex.
	 */
	अगर (wdev->connect_keys)
		वापस -EINPROGRESS;

	cfg80211_oper_and_ht_capa(&connect->ht_capa_mask,
				  rdev->wiphy.ht_capa_mod_mask);
	cfg80211_oper_and_vht_capa(&connect->vht_capa_mask,
				   rdev->wiphy.vht_capa_mod_mask);

	अगर (connkeys && connkeys->def >= 0) अणु
		पूर्णांक idx;
		u32 cipher;

		idx = connkeys->def;
		cipher = connkeys->params[idx].cipher;
		/* If given a WEP key we may need it क्रम shared key auth */
		अगर (cipher == WLAN_CIPHER_SUITE_WEP40 ||
		    cipher == WLAN_CIPHER_SUITE_WEP104) अणु
			connect->key_idx = idx;
			connect->key = connkeys->params[idx].key;
			connect->key_len = connkeys->params[idx].key_len;

			/*
			 * If ciphers are not set (e.g. when going through
			 * iwconfig), we have to set them appropriately here.
			 */
			अगर (connect->crypto.cipher_group == 0)
				connect->crypto.cipher_group = cipher;

			अगर (connect->crypto.n_ciphers_pairwise == 0) अणु
				connect->crypto.n_ciphers_pairwise = 1;
				connect->crypto.ciphers_pairwise[0] = cipher;
			पूर्ण
		पूर्ण

		connect->crypto.wep_keys = connkeys->params;
		connect->crypto.wep_tx_key = connkeys->def;
	पूर्ण अन्यथा अणु
		अगर (WARN_ON(connkeys))
			वापस -EINVAL;
	पूर्ण

	wdev->connect_keys = connkeys;
	स_नकल(wdev->ssid, connect->ssid, connect->ssid_len);
	wdev->ssid_len = connect->ssid_len;

	wdev->conn_bss_type = connect->pbss ? IEEE80211_BSS_TYPE_PBSS :
					      IEEE80211_BSS_TYPE_ESS;

	अगर (!rdev->ops->connect)
		err = cfg80211_sme_connect(wdev, connect, prev_bssid);
	अन्यथा
		err = rdev_connect(rdev, dev, connect);

	अगर (err) अणु
		wdev->connect_keys = शून्य;
		/*
		 * This could be reassoc getting refused, करोn't clear
		 * ssid_len in that हाल.
		 */
		अगर (!wdev->current_bss)
			wdev->ssid_len = 0;
		वापस err;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक cfg80211_disconnect(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev, u16 reason, bool wextev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err = 0;

	ASSERT_WDEV_LOCK(wdev);

	kमुक्त_sensitive(wdev->connect_keys);
	wdev->connect_keys = शून्य;

	wdev->conn_owner_nlportid = 0;

	अगर (wdev->conn)
		err = cfg80211_sme_disconnect(wdev, reason);
	अन्यथा अगर (!rdev->ops->disconnect)
		cfg80211_mlme_करोwn(rdev, dev);
	अन्यथा अगर (wdev->ssid_len)
		err = rdev_disconnect(rdev, dev, reason);

	/*
	 * Clear ssid_len unless we actually were fully connected,
	 * in which हाल cfg80211_disconnected() will take care of
	 * this later.
	 */
	अगर (!wdev->current_bss)
		wdev->ssid_len = 0;

	वापस err;
पूर्ण

/*
 * Used to clean up after the connection / connection attempt owner socket
 * disconnects
 */
व्योम cfg80211_स्वतःdisconnect_wk(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wireless_dev *wdev =
		container_of(work, काष्ठा wireless_dev, disconnect_wk);
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	wdev_lock(wdev);

	अगर (wdev->conn_owner_nlportid) अणु
		चयन (wdev->अगरtype) अणु
		हाल NL80211_IFTYPE_ADHOC:
			__cfg80211_leave_ibss(rdev, wdev->netdev, false);
			अवरोध;
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_P2P_GO:
			__cfg80211_stop_ap(rdev, wdev->netdev, false);
			अवरोध;
		हाल NL80211_IFTYPE_MESH_POINT:
			__cfg80211_leave_mesh(rdev, wdev->netdev);
			अवरोध;
		हाल NL80211_IFTYPE_STATION:
		हाल NL80211_IFTYPE_P2P_CLIENT:
			/*
			 * Use disconnect_bssid अगर still connecting and
			 * ops->disconnect not implemented.  Otherwise we can
			 * use cfg80211_disconnect.
			 */
			अगर (rdev->ops->disconnect || wdev->current_bss)
				cfg80211_disconnect(rdev, wdev->netdev,
						    WLAN_REASON_DEAUTH_LEAVING,
						    true);
			अन्यथा
				cfg80211_mlme_deauth(rdev, wdev->netdev,
						     wdev->disconnect_bssid,
						     शून्य, 0,
						     WLAN_REASON_DEAUTH_LEAVING,
						     false);
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
	पूर्ण

	wdev_unlock(wdev);
पूर्ण
