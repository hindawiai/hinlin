<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * cfg80211 MLME SAP पूर्णांकerface
 *
 * Copyright (c) 2009, Jouni Malinen <j@w1.fi>
 * Copyright (c) 2015		Intel Deutschland GmbH
 * Copyright (C) 2019-2020 Intel Corporation
 */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/netdevice.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/slab.h>
#समावेश <linux/wireless.h>
#समावेश <net/cfg80211.h>
#समावेश <net/iw_handler.h>
#समावेश "core.h"
#समावेश "nl80211.h"
#समावेश "rdev-ops.h"


व्योम cfg80211_rx_assoc_resp(काष्ठा net_device *dev, काष्ठा cfg80211_bss *bss,
			    स्थिर u8 *buf, माप_प्रकार len, पूर्णांक uapsd_queues,
			    स्थिर u8 *req_ies, माप_प्रकार req_ies_len)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)buf;
	काष्ठा cfg80211_connect_resp_params cr;
	स्थिर u8 *resp_ie = mgmt->u.assoc_resp.variable;
	माप_प्रकार resp_ie_len = len - दुरत्व(काष्ठा ieee80211_mgmt,
					    u.assoc_resp.variable);

	अगर (bss->channel->band == NL80211_BAND_S1GHZ) अणु
		resp_ie = (u8 *)&mgmt->u.s1g_assoc_resp.variable;
		resp_ie_len = len - दुरत्व(काष्ठा ieee80211_mgmt,
					     u.s1g_assoc_resp.variable);
	पूर्ण

	स_रखो(&cr, 0, माप(cr));
	cr.status = (पूर्णांक)le16_to_cpu(mgmt->u.assoc_resp.status_code);
	cr.bssid = mgmt->bssid;
	cr.bss = bss;
	cr.req_ie = req_ies;
	cr.req_ie_len = req_ies_len;
	cr.resp_ie = resp_ie;
	cr.resp_ie_len = resp_ie_len;
	cr.समयout_reason = NL80211_TIMEOUT_UNSPECIFIED;

	trace_cfg80211_send_rx_assoc(dev, bss);

	/*
	 * This is a bit of a hack, we करोn't notअगरy userspace of
	 * a (re-)association reply अगर we tried to send a reassoc
	 * and got a reject -- we only try again with an assoc
	 * frame instead of reassoc.
	 */
	अगर (cfg80211_sme_rx_assoc_resp(wdev, cr.status)) अणु
		cfg80211_unhold_bss(bss_from_pub(bss));
		cfg80211_put_bss(wiphy, bss);
		वापस;
	पूर्ण

	nl80211_send_rx_assoc(rdev, dev, buf, len, GFP_KERNEL, uapsd_queues,
			      req_ies, req_ies_len);
	/* update current_bss etc., consumes the bss reference */
	__cfg80211_connect_result(dev, &cr, cr.status == WLAN_STATUS_SUCCESS);
पूर्ण
EXPORT_SYMBOL(cfg80211_rx_assoc_resp);

अटल व्योम cfg80211_process_auth(काष्ठा wireless_dev *wdev,
				  स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	nl80211_send_rx_auth(rdev, wdev->netdev, buf, len, GFP_KERNEL);
	cfg80211_sme_rx_auth(wdev, buf, len);
पूर्ण

अटल व्योम cfg80211_process_deauth(काष्ठा wireless_dev *wdev,
				    स्थिर u8 *buf, माप_प्रकार len,
				    bool reconnect)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)buf;
	स्थिर u8 *bssid = mgmt->bssid;
	u16 reason_code = le16_to_cpu(mgmt->u.deauth.reason_code);
	bool from_ap = !ether_addr_equal(mgmt->sa, wdev->netdev->dev_addr);

	nl80211_send_deauth(rdev, wdev->netdev, buf, len, reconnect, GFP_KERNEL);

	अगर (!wdev->current_bss ||
	    !ether_addr_equal(wdev->current_bss->pub.bssid, bssid))
		वापस;

	__cfg80211_disconnected(wdev->netdev, शून्य, 0, reason_code, from_ap);
	cfg80211_sme_deauth(wdev);
पूर्ण

अटल व्योम cfg80211_process_disassoc(काष्ठा wireless_dev *wdev,
				      स्थिर u8 *buf, माप_प्रकार len,
				      bool reconnect)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा ieee80211_mgmt *mgmt = (काष्ठा ieee80211_mgmt *)buf;
	स्थिर u8 *bssid = mgmt->bssid;
	u16 reason_code = le16_to_cpu(mgmt->u.disassoc.reason_code);
	bool from_ap = !ether_addr_equal(mgmt->sa, wdev->netdev->dev_addr);

	nl80211_send_disassoc(rdev, wdev->netdev, buf, len, reconnect,
			      GFP_KERNEL);

	अगर (WARN_ON(!wdev->current_bss ||
		    !ether_addr_equal(wdev->current_bss->pub.bssid, bssid)))
		वापस;

	__cfg80211_disconnected(wdev->netdev, शून्य, 0, reason_code, from_ap);
	cfg80211_sme_disassoc(wdev);
पूर्ण

व्योम cfg80211_rx_mlme_mgmt(काष्ठा net_device *dev, स्थिर u8 *buf, माप_प्रकार len)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)buf;

	ASSERT_WDEV_LOCK(wdev);

	trace_cfg80211_rx_mlme_mgmt(dev, buf, len);

	अगर (WARN_ON(len < 2))
		वापस;

	अगर (ieee80211_is_auth(mgmt->frame_control))
		cfg80211_process_auth(wdev, buf, len);
	अन्यथा अगर (ieee80211_is_deauth(mgmt->frame_control))
		cfg80211_process_deauth(wdev, buf, len, false);
	अन्यथा अगर (ieee80211_is_disassoc(mgmt->frame_control))
		cfg80211_process_disassoc(wdev, buf, len, false);
पूर्ण
EXPORT_SYMBOL(cfg80211_rx_mlme_mgmt);

व्योम cfg80211_auth_समयout(काष्ठा net_device *dev, स्थिर u8 *addr)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_send_auth_समयout(dev, addr);

	nl80211_send_auth_समयout(rdev, dev, addr, GFP_KERNEL);
	cfg80211_sme_auth_समयout(wdev);
पूर्ण
EXPORT_SYMBOL(cfg80211_auth_समयout);

व्योम cfg80211_assoc_समयout(काष्ठा net_device *dev, काष्ठा cfg80211_bss *bss)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_send_assoc_समयout(dev, bss->bssid);

	nl80211_send_assoc_समयout(rdev, dev, bss->bssid, GFP_KERNEL);
	cfg80211_sme_assoc_समयout(wdev);

	cfg80211_unhold_bss(bss_from_pub(bss));
	cfg80211_put_bss(wiphy, bss);
पूर्ण
EXPORT_SYMBOL(cfg80211_assoc_समयout);

व्योम cfg80211_abanकरोn_assoc(काष्ठा net_device *dev, काष्ठा cfg80211_bss *bss)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;

	cfg80211_sme_abanकरोn_assoc(wdev);

	cfg80211_unhold_bss(bss_from_pub(bss));
	cfg80211_put_bss(wiphy, bss);
पूर्ण
EXPORT_SYMBOL(cfg80211_abanकरोn_assoc);

व्योम cfg80211_tx_mlme_mgmt(काष्ठा net_device *dev, स्थिर u8 *buf, माप_प्रकार len,
			   bool reconnect)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)buf;

	ASSERT_WDEV_LOCK(wdev);

	trace_cfg80211_tx_mlme_mgmt(dev, buf, len, reconnect);

	अगर (WARN_ON(len < 2))
		वापस;

	अगर (ieee80211_is_deauth(mgmt->frame_control))
		cfg80211_process_deauth(wdev, buf, len, reconnect);
	अन्यथा
		cfg80211_process_disassoc(wdev, buf, len, reconnect);
पूर्ण
EXPORT_SYMBOL(cfg80211_tx_mlme_mgmt);

व्योम cfg80211_michael_mic_failure(काष्ठा net_device *dev, स्थिर u8 *addr,
				  क्रमागत nl80211_key_type key_type, पूर्णांक key_id,
				  स्थिर u8 *tsc, gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = dev->ieee80211_ptr->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
#अगर_घोषित CONFIG_CFG80211_WEXT
	जोड़ iwreq_data wrqu;
	अक्षर *buf = kदो_स्मृति(128, gfp);

	अगर (buf) अणु
		प्र_लिखो(buf, "MLME-MICHAELMICFAILURE.indication("
			"keyid=%d %scast addr=%pM)", key_id,
			key_type == NL80211_KEYTYPE_GROUP ? "broad" : "uni",
			addr);
		स_रखो(&wrqu, 0, माप(wrqu));
		wrqu.data.length = म_माप(buf);
		wireless_send_event(dev, IWEVCUSTOM, &wrqu, buf);
		kमुक्त(buf);
	पूर्ण
#पूर्ण_अगर

	trace_cfg80211_michael_mic_failure(dev, addr, key_type, key_id, tsc);
	nl80211_michael_mic_failure(rdev, dev, addr, key_type, key_id, tsc, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_michael_mic_failure);

/* some MLME handling क्रम userspace SME */
पूर्णांक cfg80211_mlme_auth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा net_device *dev,
		       काष्ठा ieee80211_channel *chan,
		       क्रमागत nl80211_auth_type auth_type,
		       स्थिर u8 *bssid,
		       स्थिर u8 *ssid, पूर्णांक ssid_len,
		       स्थिर u8 *ie, पूर्णांक ie_len,
		       स्थिर u8 *key, पूर्णांक key_len, पूर्णांक key_idx,
		       स्थिर u8 *auth_data, पूर्णांक auth_data_len)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_auth_request req = अणु
		.ie = ie,
		.ie_len = ie_len,
		.auth_data = auth_data,
		.auth_data_len = auth_data_len,
		.auth_type = auth_type,
		.key = key,
		.key_len = key_len,
		.key_idx = key_idx,
	पूर्ण;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (auth_type == NL80211_AUTHTYPE_SHARED_KEY)
		अगर (!key || !key_len || key_idx < 0 || key_idx > 3)
			वापस -EINVAL;

	अगर (wdev->current_bss &&
	    ether_addr_equal(bssid, wdev->current_bss->pub.bssid))
		वापस -EALREADY;

	req.bss = cfg80211_get_bss(&rdev->wiphy, chan, bssid, ssid, ssid_len,
				   IEEE80211_BSS_TYPE_ESS,
				   IEEE80211_PRIVACY_ANY);
	अगर (!req.bss)
		वापस -ENOENT;

	err = rdev_auth(rdev, dev, &req);

	cfg80211_put_bss(&rdev->wiphy, req.bss);
	वापस err;
पूर्ण

/*  Do a logical ht_capa &= ht_capa_mask.  */
व्योम cfg80211_oper_and_ht_capa(काष्ठा ieee80211_ht_cap *ht_capa,
			       स्थिर काष्ठा ieee80211_ht_cap *ht_capa_mask)
अणु
	पूर्णांक i;
	u8 *p1, *p2;
	अगर (!ht_capa_mask) अणु
		स_रखो(ht_capa, 0, माप(*ht_capa));
		वापस;
	पूर्ण

	p1 = (u8*)(ht_capa);
	p2 = (u8*)(ht_capa_mask);
	क्रम (i = 0; i < माप(*ht_capa); i++)
		p1[i] &= p2[i];
पूर्ण

/*  Do a logical vht_capa &= vht_capa_mask.  */
व्योम cfg80211_oper_and_vht_capa(काष्ठा ieee80211_vht_cap *vht_capa,
				स्थिर काष्ठा ieee80211_vht_cap *vht_capa_mask)
अणु
	पूर्णांक i;
	u8 *p1, *p2;
	अगर (!vht_capa_mask) अणु
		स_रखो(vht_capa, 0, माप(*vht_capa));
		वापस;
	पूर्ण

	p1 = (u8*)(vht_capa);
	p2 = (u8*)(vht_capa_mask);
	क्रम (i = 0; i < माप(*vht_capa); i++)
		p1[i] &= p2[i];
पूर्ण

पूर्णांक cfg80211_mlme_assoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev,
			काष्ठा ieee80211_channel *chan,
			स्थिर u8 *bssid,
			स्थिर u8 *ssid, पूर्णांक ssid_len,
			काष्ठा cfg80211_assoc_request *req)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (wdev->current_bss &&
	    (!req->prev_bssid || !ether_addr_equal(wdev->current_bss->pub.bssid,
						   req->prev_bssid)))
		वापस -EALREADY;

	cfg80211_oper_and_ht_capa(&req->ht_capa_mask,
				  rdev->wiphy.ht_capa_mod_mask);
	cfg80211_oper_and_vht_capa(&req->vht_capa_mask,
				   rdev->wiphy.vht_capa_mod_mask);

	req->bss = cfg80211_get_bss(&rdev->wiphy, chan, bssid, ssid, ssid_len,
				    IEEE80211_BSS_TYPE_ESS,
				    IEEE80211_PRIVACY_ANY);
	अगर (!req->bss)
		वापस -ENOENT;

	err = rdev_assoc(rdev, dev, req);
	अगर (!err)
		cfg80211_hold_bss(bss_from_pub(req->bss));
	अन्यथा
		cfg80211_put_bss(&rdev->wiphy, req->bss);

	वापस err;
पूर्ण

पूर्णांक cfg80211_mlme_deauth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *dev, स्थिर u8 *bssid,
			 स्थिर u8 *ie, पूर्णांक ie_len, u16 reason,
			 bool local_state_change)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_deauth_request req = अणु
		.bssid = bssid,
		.reason_code = reason,
		.ie = ie,
		.ie_len = ie_len,
		.local_state_change = local_state_change,
	पूर्ण;

	ASSERT_WDEV_LOCK(wdev);

	अगर (local_state_change &&
	    (!wdev->current_bss ||
	     !ether_addr_equal(wdev->current_bss->pub.bssid, bssid)))
		वापस 0;

	अगर (ether_addr_equal(wdev->disconnect_bssid, bssid) ||
	    (wdev->current_bss &&
	     ether_addr_equal(wdev->current_bss->pub.bssid, bssid)))
		wdev->conn_owner_nlportid = 0;

	वापस rdev_deauth(rdev, dev, &req);
पूर्ण

पूर्णांक cfg80211_mlme_disassoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net_device *dev, स्थिर u8 *bssid,
			   स्थिर u8 *ie, पूर्णांक ie_len, u16 reason,
			   bool local_state_change)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_disassoc_request req = अणु
		.reason_code = reason,
		.local_state_change = local_state_change,
		.ie = ie,
		.ie_len = ie_len,
	पूर्ण;
	पूर्णांक err;

	ASSERT_WDEV_LOCK(wdev);

	अगर (!wdev->current_bss)
		वापस -ENOTCONN;

	अगर (ether_addr_equal(wdev->current_bss->pub.bssid, bssid))
		req.bss = &wdev->current_bss->pub;
	अन्यथा
		वापस -ENOTCONN;

	err = rdev_disassoc(rdev, dev, &req);
	अगर (err)
		वापस err;

	/* driver should have reported the disassoc */
	WARN_ON(wdev->current_bss);
	वापस 0;
पूर्ण

व्योम cfg80211_mlme_करोwn(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	u8 bssid[ETH_ALEN];

	ASSERT_WDEV_LOCK(wdev);

	अगर (!rdev->ops->deauth)
		वापस;

	अगर (!wdev->current_bss)
		वापस;

	स_नकल(bssid, wdev->current_bss->pub.bssid, ETH_ALEN);
	cfg80211_mlme_deauth(rdev, dev, bssid, शून्य, 0,
			     WLAN_REASON_DEAUTH_LEAVING, false);
पूर्ण

काष्ठा cfg80211_mgmt_registration अणु
	काष्ठा list_head list;
	काष्ठा wireless_dev *wdev;

	u32 nlportid;

	पूर्णांक match_len;

	__le16 frame_type;

	bool multicast_rx;

	u8 match[];
पूर्ण;

अटल व्योम cfg80211_mgmt_registrations_update(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा wireless_dev *पंचांगp;
	काष्ठा cfg80211_mgmt_registration *reg;
	काष्ठा mgmt_frame_regs upd = अणुपूर्ण;

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	spin_lock_bh(&wdev->mgmt_registrations_lock);
	अगर (!wdev->mgmt_registrations_need_update) अणु
		spin_unlock_bh(&wdev->mgmt_registrations_lock);
		वापस;
	पूर्ण

	rcu_पढ़ो_lock();
	list_क्रम_each_entry_rcu(पंचांगp, &rdev->wiphy.wdev_list, list) अणु
		list_क्रम_each_entry(reg, &पंचांगp->mgmt_registrations, list) अणु
			u32 mask = BIT(le16_to_cpu(reg->frame_type) >> 4);
			u32 mcast_mask = 0;

			अगर (reg->multicast_rx)
				mcast_mask = mask;

			upd.global_stypes |= mask;
			upd.global_mcast_stypes |= mcast_mask;

			अगर (पंचांगp == wdev) अणु
				upd.पूर्णांकerface_stypes |= mask;
				upd.पूर्णांकerface_mcast_stypes |= mcast_mask;
			पूर्ण
		पूर्ण
	पूर्ण
	rcu_पढ़ो_unlock();

	wdev->mgmt_registrations_need_update = 0;
	spin_unlock_bh(&wdev->mgmt_registrations_lock);

	rdev_update_mgmt_frame_registrations(rdev, wdev, &upd);
पूर्ण

व्योम cfg80211_mgmt_registrations_update_wk(काष्ठा work_काष्ठा *wk)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;

	rdev = container_of(wk, काष्ठा cfg80211_रेजिस्टरed_device,
			    mgmt_registrations_update_wk);

	wiphy_lock(&rdev->wiphy);
	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list)
		cfg80211_mgmt_registrations_update(wdev);
	wiphy_unlock(&rdev->wiphy);
पूर्ण

पूर्णांक cfg80211_mlme_रेजिस्टर_mgmt(काष्ठा wireless_dev *wdev, u32 snd_portid,
				u16 frame_type, स्थिर u8 *match_data,
				पूर्णांक match_len, bool multicast_rx,
				काष्ठा netlink_ext_ack *extack)
अणु
	काष्ठा cfg80211_mgmt_registration *reg, *nreg;
	पूर्णांक err = 0;
	u16 mgmt_type;
	bool update_multicast = false;

	अगर (!wdev->wiphy->mgmt_stypes)
		वापस -EOPNOTSUPP;

	अगर ((frame_type & IEEE80211_FCTL_FTYPE) != IEEE80211_FTYPE_MGMT) अणु
		NL_SET_ERR_MSG(extack, "frame type not management");
		वापस -EINVAL;
	पूर्ण

	अगर (frame_type & ~(IEEE80211_FCTL_FTYPE | IEEE80211_FCTL_STYPE)) अणु
		NL_SET_ERR_MSG(extack, "Invalid frame type");
		वापस -EINVAL;
	पूर्ण

	mgmt_type = (frame_type & IEEE80211_FCTL_STYPE) >> 4;
	अगर (!(wdev->wiphy->mgmt_stypes[wdev->अगरtype].rx & BIT(mgmt_type))) अणु
		NL_SET_ERR_MSG(extack,
			       "Registration to specific type not supported");
		वापस -EINVAL;
	पूर्ण

	/*
	 * To support Pre Association Security Negotiation (PASN), registration
	 * क्रम authentication frames should be supported. However, as some
	 * versions of the user space daemons wrongly रेजिस्टर to all types of
	 * authentication frames (which might result in unexpected behavior)
	 * allow such registration अगर the request is क्रम a specअगरic
	 * authentication algorithm number.
	 */
	अगर (wdev->अगरtype == NL80211_IFTYPE_STATION &&
	    (frame_type & IEEE80211_FCTL_STYPE) == IEEE80211_STYPE_AUTH &&
	    !(match_data && match_len >= 2)) अणु
		NL_SET_ERR_MSG(extack,
			       "Authentication algorithm number required");
		वापस -EINVAL;
	पूर्ण

	nreg = kzalloc(माप(*reg) + match_len, GFP_KERNEL);
	अगर (!nreg)
		वापस -ENOMEM;

	spin_lock_bh(&wdev->mgmt_registrations_lock);

	list_क्रम_each_entry(reg, &wdev->mgmt_registrations, list) अणु
		पूर्णांक mlen = min(match_len, reg->match_len);

		अगर (frame_type != le16_to_cpu(reg->frame_type))
			जारी;

		अगर (स_भेद(reg->match, match_data, mlen) == 0) अणु
			अगर (reg->multicast_rx != multicast_rx) अणु
				update_multicast = true;
				reg->multicast_rx = multicast_rx;
				अवरोध;
			पूर्ण
			NL_SET_ERR_MSG(extack, "Match already configured");
			err = -EALREADY;
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (err)
		जाओ out;

	अगर (update_multicast) अणु
		kमुक्त(nreg);
	पूर्ण अन्यथा अणु
		स_नकल(nreg->match, match_data, match_len);
		nreg->match_len = match_len;
		nreg->nlportid = snd_portid;
		nreg->frame_type = cpu_to_le16(frame_type);
		nreg->wdev = wdev;
		nreg->multicast_rx = multicast_rx;
		list_add(&nreg->list, &wdev->mgmt_registrations);
	पूर्ण
	wdev->mgmt_registrations_need_update = 1;
	spin_unlock_bh(&wdev->mgmt_registrations_lock);

	cfg80211_mgmt_registrations_update(wdev);

	वापस 0;

 out:
	kमुक्त(nreg);
	spin_unlock_bh(&wdev->mgmt_registrations_lock);

	वापस err;
पूर्ण

व्योम cfg80211_mlme_unरेजिस्टर_socket(काष्ठा wireless_dev *wdev, u32 nlportid)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_mgmt_registration *reg, *पंचांगp;

	spin_lock_bh(&wdev->mgmt_registrations_lock);

	list_क्रम_each_entry_safe(reg, पंचांगp, &wdev->mgmt_registrations, list) अणु
		अगर (reg->nlportid != nlportid)
			जारी;

		list_del(&reg->list);
		kमुक्त(reg);

		wdev->mgmt_registrations_need_update = 1;
		schedule_work(&rdev->mgmt_registrations_update_wk);
	पूर्ण

	spin_unlock_bh(&wdev->mgmt_registrations_lock);

	अगर (nlportid && rdev->crit_proto_nlportid == nlportid) अणु
		rdev->crit_proto_nlportid = 0;
		rdev_crit_proto_stop(rdev, wdev);
	पूर्ण

	अगर (nlportid == wdev->ap_unexpected_nlportid)
		wdev->ap_unexpected_nlportid = 0;
पूर्ण

व्योम cfg80211_mlme_purge_registrations(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा cfg80211_mgmt_registration *reg, *पंचांगp;

	spin_lock_bh(&wdev->mgmt_registrations_lock);
	list_क्रम_each_entry_safe(reg, पंचांगp, &wdev->mgmt_registrations, list) अणु
		list_del(&reg->list);
		kमुक्त(reg);
	पूर्ण
	wdev->mgmt_registrations_need_update = 1;
	spin_unlock_bh(&wdev->mgmt_registrations_lock);

	cfg80211_mgmt_registrations_update(wdev);
पूर्ण

पूर्णांक cfg80211_mlme_mgmt_tx(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा wireless_dev *wdev,
			  काष्ठा cfg80211_mgmt_tx_params *params, u64 *cookie)
अणु
	स्थिर काष्ठा ieee80211_mgmt *mgmt;
	u16 stype;

	अगर (!wdev->wiphy->mgmt_stypes)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->mgmt_tx)
		वापस -EOPNOTSUPP;

	अगर (params->len < 24 + 1)
		वापस -EINVAL;

	mgmt = (स्थिर काष्ठा ieee80211_mgmt *)params->buf;

	अगर (!ieee80211_is_mgmt(mgmt->frame_control))
		वापस -EINVAL;

	stype = le16_to_cpu(mgmt->frame_control) & IEEE80211_FCTL_STYPE;
	अगर (!(wdev->wiphy->mgmt_stypes[wdev->अगरtype].tx & BIT(stype >> 4)))
		वापस -EINVAL;

	अगर (ieee80211_is_action(mgmt->frame_control) &&
	    mgmt->u.action.category != WLAN_CATEGORY_PUBLIC) अणु
		पूर्णांक err = 0;

		wdev_lock(wdev);

		चयन (wdev->अगरtype) अणु
		हाल NL80211_IFTYPE_ADHOC:
		हाल NL80211_IFTYPE_STATION:
		हाल NL80211_IFTYPE_P2P_CLIENT:
			अगर (!wdev->current_bss) अणु
				err = -ENOTCONN;
				अवरोध;
			पूर्ण

			अगर (!ether_addr_equal(wdev->current_bss->pub.bssid,
					      mgmt->bssid)) अणु
				err = -ENOTCONN;
				अवरोध;
			पूर्ण

			/*
			 * check क्रम IBSS DA must be करोne by driver as
			 * cfg80211 करोesn't track the stations
			 */
			अगर (wdev->अगरtype == NL80211_IFTYPE_ADHOC)
				अवरोध;

			/* क्रम station, check that DA is the AP */
			अगर (!ether_addr_equal(wdev->current_bss->pub.bssid,
					      mgmt->da)) अणु
				err = -ENOTCONN;
				अवरोध;
			पूर्ण
			अवरोध;
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_P2P_GO:
		हाल NL80211_IFTYPE_AP_VLAN:
			अगर (!ether_addr_equal(mgmt->bssid, wdev_address(wdev)))
				err = -EINVAL;
			अवरोध;
		हाल NL80211_IFTYPE_MESH_POINT:
			अगर (!ether_addr_equal(mgmt->sa, mgmt->bssid)) अणु
				err = -EINVAL;
				अवरोध;
			पूर्ण
			/*
			 * check क्रम mesh DA must be करोne by driver as
			 * cfg80211 करोesn't track the stations
			 */
			अवरोध;
		हाल NL80211_IFTYPE_P2P_DEVICE:
			/*
			 * fall through, P2P device only supports
			 * खुला action frames
			 */
		हाल NL80211_IFTYPE_न_अंक:
		शेष:
			err = -EOPNOTSUPP;
			अवरोध;
		पूर्ण
		wdev_unlock(wdev);

		अगर (err)
			वापस err;
	पूर्ण

	अगर (!ether_addr_equal(mgmt->sa, wdev_address(wdev))) अणु
		/* Allow अक्रमom TA to be used with Public Action frames अगर the
		 * driver has indicated support क्रम this. Otherwise, only allow
		 * the local address to be used.
		 */
		अगर (!ieee80211_is_action(mgmt->frame_control) ||
		    mgmt->u.action.category != WLAN_CATEGORY_PUBLIC)
			वापस -EINVAL;
		अगर (!wdev->current_bss &&
		    !wiphy_ext_feature_isset(
			    &rdev->wiphy,
			    NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA))
			वापस -EINVAL;
		अगर (wdev->current_bss &&
		    !wiphy_ext_feature_isset(
			    &rdev->wiphy,
			    NL80211_EXT_FEATURE_MGMT_TX_RANDOM_TA_CONNECTED))
			वापस -EINVAL;
	पूर्ण

	/* Transmit the Action frame as requested by user space */
	वापस rdev_mgmt_tx(rdev, wdev, params, cookie);
पूर्ण

bool cfg80211_rx_mgmt_khz(काष्ठा wireless_dev *wdev, पूर्णांक freq, पूर्णांक sig_dbm,
			  स्थिर u8 *buf, माप_प्रकार len, u32 flags)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा cfg80211_mgmt_registration *reg;
	स्थिर काष्ठा ieee80211_txrx_stypes *stypes =
		&wiphy->mgmt_stypes[wdev->अगरtype];
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)buf;
	स्थिर u8 *data;
	पूर्णांक data_len;
	bool result = false;
	__le16 ftype = mgmt->frame_control &
		cpu_to_le16(IEEE80211_FCTL_FTYPE | IEEE80211_FCTL_STYPE);
	u16 stype;

	trace_cfg80211_rx_mgmt(wdev, freq, sig_dbm);
	stype = (le16_to_cpu(mgmt->frame_control) & IEEE80211_FCTL_STYPE) >> 4;

	अगर (!(stypes->rx & BIT(stype))) अणु
		trace_cfg80211_वापस_bool(false);
		वापस false;
	पूर्ण

	data = buf + ieee80211_hdrlen(mgmt->frame_control);
	data_len = len - ieee80211_hdrlen(mgmt->frame_control);

	spin_lock_bh(&wdev->mgmt_registrations_lock);

	list_क्रम_each_entry(reg, &wdev->mgmt_registrations, list) अणु
		अगर (reg->frame_type != ftype)
			जारी;

		अगर (reg->match_len > data_len)
			जारी;

		अगर (स_भेद(reg->match, data, reg->match_len))
			जारी;

		/* found match! */

		/* Indicate the received Action frame to user space */
		अगर (nl80211_send_mgmt(rdev, wdev, reg->nlportid,
				      freq, sig_dbm,
				      buf, len, flags, GFP_ATOMIC))
			जारी;

		result = true;
		अवरोध;
	पूर्ण

	spin_unlock_bh(&wdev->mgmt_registrations_lock);

	trace_cfg80211_वापस_bool(result);
	वापस result;
पूर्ण
EXPORT_SYMBOL(cfg80211_rx_mgmt_khz);

व्योम cfg80211_sched_dfs_chan_update(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	cancel_delayed_work(&rdev->dfs_update_channels_wk);
	queue_delayed_work(cfg80211_wq, &rdev->dfs_update_channels_wk, 0);
पूर्ण

व्योम cfg80211_dfs_channels_update_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा delayed_work *delayed_work = to_delayed_work(work);
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा ieee80211_supported_band *sband;
	काष्ठा ieee80211_channel *c;
	काष्ठा wiphy *wiphy;
	bool check_again = false;
	अचिन्हित दीर्घ समयout, next_समय = 0;
	अचिन्हित दीर्घ समय_dfs_update;
	क्रमागत nl80211_radar_event radar_event;
	पूर्णांक bandid, i;

	rdev = container_of(delayed_work, काष्ठा cfg80211_रेजिस्टरed_device,
			    dfs_update_channels_wk);
	wiphy = &rdev->wiphy;

	rtnl_lock();
	क्रम (bandid = 0; bandid < NUM_NL80211_BANDS; bandid++) अणु
		sband = wiphy->bands[bandid];
		अगर (!sband)
			जारी;

		क्रम (i = 0; i < sband->n_channels; i++) अणु
			c = &sband->channels[i];

			अगर (!(c->flags & IEEE80211_CHAN_RADAR))
				जारी;

			अगर (c->dfs_state != NL80211_DFS_UNAVAILABLE &&
			    c->dfs_state != NL80211_DFS_AVAILABLE)
				जारी;

			अगर (c->dfs_state == NL80211_DFS_UNAVAILABLE) अणु
				समय_dfs_update = IEEE80211_DFS_MIN_NOP_TIME_MS;
				radar_event = NL80211_RADAR_NOP_FINISHED;
			पूर्ण अन्यथा अणु
				अगर (regulatory_pre_cac_allowed(wiphy) ||
				    cfg80211_any_wiphy_oper_chan(wiphy, c))
					जारी;

				समय_dfs_update = REG_PRE_CAC_EXPIRY_GRACE_MS;
				radar_event = NL80211_RADAR_PRE_CAC_EXPIRED;
			पूर्ण

			समयout = c->dfs_state_entered +
				  msecs_to_jअगरfies(समय_dfs_update);

			अगर (समय_after_eq(jअगरfies, समयout)) अणु
				c->dfs_state = NL80211_DFS_USABLE;
				c->dfs_state_entered = jअगरfies;

				cfg80211_chandef_create(&chandef, c,
							NL80211_CHAN_NO_HT);

				nl80211_radar_notअगरy(rdev, &chandef,
						     radar_event, शून्य,
						     GFP_ATOMIC);

				regulatory_propagate_dfs_state(wiphy, &chandef,
							       c->dfs_state,
							       radar_event);
				जारी;
			पूर्ण

			अगर (!check_again)
				next_समय = समयout - jअगरfies;
			अन्यथा
				next_समय = min(next_समय, समयout - jअगरfies);
			check_again = true;
		पूर्ण
	पूर्ण
	rtnl_unlock();

	/* reschedule अगर there are other channels रुकोing to be cleared again */
	अगर (check_again)
		queue_delayed_work(cfg80211_wq, &rdev->dfs_update_channels_wk,
				   next_समय);
पूर्ण


व्योम cfg80211_radar_event(काष्ठा wiphy *wiphy,
			  काष्ठा cfg80211_chan_def *chandef,
			  gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_radar_event(wiphy, chandef);

	/* only set the chandef supplied channel to unavailable, in
	 * हाल the radar is detected on only one of multiple channels
	 * spanned by the chandef.
	 */
	cfg80211_set_dfs_state(wiphy, chandef, NL80211_DFS_UNAVAILABLE);

	cfg80211_sched_dfs_chan_update(rdev);

	nl80211_radar_notअगरy(rdev, chandef, NL80211_RADAR_DETECTED, शून्य, gfp);

	स_नकल(&rdev->radar_chandef, chandef, माप(काष्ठा cfg80211_chan_def));
	queue_work(cfg80211_wq, &rdev->propagate_radar_detect_wk);
पूर्ण
EXPORT_SYMBOL(cfg80211_radar_event);

व्योम cfg80211_cac_event(काष्ठा net_device *netdev,
			स्थिर काष्ठा cfg80211_chan_def *chandef,
			क्रमागत nl80211_radar_event event, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = netdev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	अचिन्हित दीर्घ समयout;

	trace_cfg80211_cac_event(netdev, event);

	अगर (WARN_ON(!wdev->cac_started && event != NL80211_RADAR_CAC_STARTED))
		वापस;

	अगर (WARN_ON(!wdev->chandef.chan))
		वापस;

	चयन (event) अणु
	हाल NL80211_RADAR_CAC_FINISHED:
		समयout = wdev->cac_start_समय +
			  msecs_to_jअगरfies(wdev->cac_समय_ms);
		WARN_ON(!समय_after_eq(jअगरfies, समयout));
		cfg80211_set_dfs_state(wiphy, chandef, NL80211_DFS_AVAILABLE);
		स_नकल(&rdev->cac_करोne_chandef, chandef,
		       माप(काष्ठा cfg80211_chan_def));
		queue_work(cfg80211_wq, &rdev->propagate_cac_करोne_wk);
		cfg80211_sched_dfs_chan_update(rdev);
		fallthrough;
	हाल NL80211_RADAR_CAC_ABORTED:
		wdev->cac_started = false;
		अवरोध;
	हाल NL80211_RADAR_CAC_STARTED:
		wdev->cac_started = true;
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस;
	पूर्ण

	nl80211_radar_notअगरy(rdev, chandef, event, netdev, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_cac_event);
