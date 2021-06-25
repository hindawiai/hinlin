<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश <linux/kernel.h>
#समावेश <linux/module.h>
#समावेश <linux/slab.h>
#समावेश <linux/nospec.h>

#समावेश "cfg80211.h"
#समावेश "core.h"
#समावेश "qlink.h"
#समावेश "bus.h"
#समावेश "trans.h"
#समावेश "util.h"
#समावेश "event.h"
#समावेश "qlink_util.h"

अटल पूर्णांक
qtnf_event_handle_sta_assoc(काष्ठा qtnf_wmac *mac, काष्ठा qtnf_vअगर *vअगर,
			    स्थिर काष्ठा qlink_event_sta_assoc *sta_assoc,
			    u16 len)
अणु
	स्थिर u8 *sta_addr;
	u16 frame_control;
	काष्ठा station_info *sinfo;
	माप_प्रकार payload_len;
	u16 tlv_type;
	u16 tlv_value_len;
	स्थिर काष्ठा qlink_tlv_hdr *tlv;
	पूर्णांक ret = 0;

	अगर (unlikely(len < माप(*sta_assoc))) अणु
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       mac->macid, vअगर->vअगरid, len, माप(*sta_assoc));
		वापस -EINVAL;
	पूर्ण

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_AP) अणु
		pr_err("VIF%u.%u: STA_ASSOC event when not in AP mode\n",
		       mac->macid, vअगर->vअगरid);
		वापस -EPROTO;
	पूर्ण

	sinfo = kzalloc(माप(*sinfo), GFP_KERNEL);
	अगर (!sinfo)
		वापस -ENOMEM;

	sta_addr = sta_assoc->sta_addr;
	frame_control = le16_to_cpu(sta_assoc->frame_control);

	pr_debug("VIF%u.%u: MAC:%pM FC:%x\n", mac->macid, vअगर->vअगरid, sta_addr,
		 frame_control);

	qtnf_sta_list_add(vअगर, sta_addr);

	sinfo->assoc_req_ies = शून्य;
	sinfo->assoc_req_ies_len = 0;
	sinfo->generation = vअगर->generation;

	payload_len = len - माप(*sta_assoc);

	qlink_क्रम_each_tlv(tlv, sta_assoc->ies, payload_len) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);

		अगर (tlv_type == QTN_TLV_ID_IE_SET) अणु
			स्थिर काष्ठा qlink_tlv_ie_set *ie_set;
			अचिन्हित पूर्णांक ie_len;

			अगर (tlv_value_len <
			    (माप(*ie_set) - माप(ie_set->hdr))) अणु
				ret = -EINVAL;
				जाओ out;
			पूर्ण

			ie_set = (स्थिर काष्ठा qlink_tlv_ie_set *)tlv;
			ie_len = tlv_value_len -
				(माप(*ie_set) - माप(ie_set->hdr));

			अगर (ie_set->type == QLINK_IE_SET_ASSOC_REQ && ie_len) अणु
				sinfo->assoc_req_ies = ie_set->ie_data;
				sinfo->assoc_req_ies_len = ie_len;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!qlink_tlv_parsing_ok(tlv, sta_assoc->ies, payload_len)) अणु
		pr_err("Malformed TLV buffer\n");
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	cfg80211_new_sta(vअगर->netdev, sta_assoc->sta_addr, sinfo,
			 GFP_KERNEL);

out:
	kमुक्त(sinfo);
	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_sta_deauth(काष्ठा qtnf_wmac *mac, काष्ठा qtnf_vअगर *vअगर,
			     स्थिर काष्ठा qlink_event_sta_deauth *sta_deauth,
			     u16 len)
अणु
	स्थिर u8 *sta_addr;
	u16 reason;

	अगर (unlikely(len < माप(*sta_deauth))) अणु
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       mac->macid, vअगर->vअगरid, len,
		       माप(काष्ठा qlink_event_sta_deauth));
		वापस -EINVAL;
	पूर्ण

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_AP) अणु
		pr_err("VIF%u.%u: STA_DEAUTH event when not in AP mode\n",
		       mac->macid, vअगर->vअगरid);
		वापस -EPROTO;
	पूर्ण

	sta_addr = sta_deauth->sta_addr;
	reason = le16_to_cpu(sta_deauth->reason);

	pr_debug("VIF%u.%u: MAC:%pM reason:%x\n", mac->macid, vअगर->vअगरid,
		 sta_addr, reason);

	अगर (qtnf_sta_list_del(vअगर, sta_addr))
		cfg80211_del_sta(vअगर->netdev, sta_deauth->sta_addr,
				 GFP_KERNEL);

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_bss_join(काष्ठा qtnf_vअगर *vअगर,
			   स्थिर काष्ठा qlink_event_bss_join *join_info,
			   u16 len)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(vअगर->mac);
	क्रमागत ieee80211_statuscode status = le16_to_cpu(join_info->status);
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा cfg80211_bss *bss = शून्य;
	u8 *ie = शून्य;
	माप_प्रकार payload_len;
	u16 tlv_type;
	u16 tlv_value_len;
	स्थिर काष्ठा qlink_tlv_hdr *tlv;
	स्थिर u8 *rsp_ies = शून्य;
	माप_प्रकार rsp_ies_len = 0;

	अगर (unlikely(len < माप(*join_info))) अणु
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       vअगर->mac->macid, vअगर->vअगरid, len,
		       माप(काष्ठा qlink_event_bss_join));
		वापस -EINVAL;
	पूर्ण

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_STATION) अणु
		pr_err("VIF%u.%u: BSS_JOIN event when not in STA mode\n",
		       vअगर->mac->macid, vअगर->vअगरid);
		वापस -EPROTO;
	पूर्ण

	pr_debug("VIF%u.%u: BSSID:%pM chan:%u status:%u\n",
		 vअगर->mac->macid, vअगर->vअगरid, join_info->bssid,
		 le16_to_cpu(join_info->chan.chan.center_freq), status);

	अगर (status != WLAN_STATUS_SUCCESS)
		जाओ करोne;

	qlink_chandef_q2cfg(wiphy, &join_info->chan, &chandef);
	अगर (!cfg80211_chandef_valid(&chandef)) अणु
		pr_warn("MAC%u.%u: bad channel freq=%u cf1=%u cf2=%u bw=%u\n",
			vअगर->mac->macid, vअगर->vअगरid,
			chandef.chan ? chandef.chan->center_freq : 0,
			chandef.center_freq1,
			chandef.center_freq2,
			chandef.width);
		status = WLAN_STATUS_UNSPECIFIED_FAILURE;
		जाओ करोne;
	पूर्ण

	bss = cfg80211_get_bss(wiphy, chandef.chan, join_info->bssid,
			       शून्य, 0, IEEE80211_BSS_TYPE_ESS,
			       IEEE80211_PRIVACY_ANY);
	अगर (!bss) अणु
		pr_warn("VIF%u.%u: add missing BSS:%pM chan:%u\n",
			vअगर->mac->macid, vअगर->vअगरid,
			join_info->bssid, chandef.chan->hw_value);

		अगर (!vअगर->wdev.ssid_len) अणु
			pr_warn("VIF%u.%u: SSID unknown for BSS:%pM\n",
				vअगर->mac->macid, vअगर->vअगरid,
				join_info->bssid);
			status = WLAN_STATUS_UNSPECIFIED_FAILURE;
			जाओ करोne;
		पूर्ण

		ie = kzalloc(2 + vअगर->wdev.ssid_len, GFP_KERNEL);
		अगर (!ie) अणु
			pr_warn("VIF%u.%u: IE alloc failed for BSS:%pM\n",
				vअगर->mac->macid, vअगर->vअगरid,
				join_info->bssid);
			status = WLAN_STATUS_UNSPECIFIED_FAILURE;
			जाओ करोne;
		पूर्ण

		ie[0] = WLAN_EID_SSID;
		ie[1] = vअगर->wdev.ssid_len;
		स_नकल(ie + 2, vअगर->wdev.ssid, vअगर->wdev.ssid_len);

		bss = cfg80211_inक्रमm_bss(wiphy, chandef.chan,
					  CFG80211_BSS_FTYPE_UNKNOWN,
					  join_info->bssid, 0,
					  WLAN_CAPABILITY_ESS, 100,
					  ie, 2 + vअगर->wdev.ssid_len,
					  0, GFP_KERNEL);
		अगर (!bss) अणु
			pr_warn("VIF%u.%u: can't connect to unknown BSS: %pM\n",
				vअगर->mac->macid, vअगर->vअगरid,
				join_info->bssid);
			status = WLAN_STATUS_UNSPECIFIED_FAILURE;
			जाओ करोne;
		पूर्ण
	पूर्ण

	payload_len = len - माप(*join_info);

	qlink_क्रम_each_tlv(tlv, join_info->ies, payload_len) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);

		अगर (tlv_type == QTN_TLV_ID_IE_SET) अणु
			स्थिर काष्ठा qlink_tlv_ie_set *ie_set;
			अचिन्हित पूर्णांक ie_len;

			अगर (tlv_value_len <
			    (माप(*ie_set) - माप(ie_set->hdr))) अणु
				pr_warn("invalid IE_SET TLV\n");
				status = WLAN_STATUS_UNSPECIFIED_FAILURE;
				जाओ करोne;
			पूर्ण

			ie_set = (स्थिर काष्ठा qlink_tlv_ie_set *)tlv;
			ie_len = tlv_value_len -
				(माप(*ie_set) - माप(ie_set->hdr));

			चयन (ie_set->type) अणु
			हाल QLINK_IE_SET_ASSOC_RESP:
				अगर (ie_len) अणु
					rsp_ies = ie_set->ie_data;
					rsp_ies_len = ie_len;
				पूर्ण
				अवरोध;
			शेष:
				pr_warn("unexpected IE type: %u\n",
					ie_set->type);
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!qlink_tlv_parsing_ok(tlv, join_info->ies, payload_len))
		pr_warn("Malformed TLV buffer\n");
करोne:
	cfg80211_connect_result(vअगर->netdev, join_info->bssid, शून्य, 0, rsp_ies,
				rsp_ies_len, status, GFP_KERNEL);
	अगर (bss) अणु
		अगर (!ether_addr_equal(vअगर->bssid, join_info->bssid))
			ether_addr_copy(vअगर->bssid, join_info->bssid);
		cfg80211_put_bss(wiphy, bss);
	पूर्ण

	अगर (status == WLAN_STATUS_SUCCESS)
		netअगर_carrier_on(vअगर->netdev);

	kमुक्त(ie);
	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_bss_leave(काष्ठा qtnf_vअगर *vअगर,
			    स्थिर काष्ठा qlink_event_bss_leave *leave_info,
			    u16 len)
अणु
	अगर (unlikely(len < माप(*leave_info))) अणु
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       vअगर->mac->macid, vअगर->vअगरid, len,
		       माप(काष्ठा qlink_event_bss_leave));
		वापस -EINVAL;
	पूर्ण

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_STATION) अणु
		pr_err("VIF%u.%u: BSS_LEAVE event when not in STA mode\n",
		       vअगर->mac->macid, vअगर->vअगरid);
		वापस -EPROTO;
	पूर्ण

	pr_debug("VIF%u.%u: disconnected\n", vअगर->mac->macid, vअगर->vअगरid);

	cfg80211_disconnected(vअगर->netdev, le16_to_cpu(leave_info->reason),
			      शून्य, 0, 0, GFP_KERNEL);
	netअगर_carrier_off(vअगर->netdev);

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_mgmt_received(काष्ठा qtnf_vअगर *vअगर,
				स्थिर काष्ठा qlink_event_rxmgmt *rxmgmt,
				u16 len)
अणु
	स्थिर माप_प्रकार min_len = माप(*rxmgmt) +
			       माप(काष्ठा ieee80211_hdr_3addr);
	स्थिर काष्ठा ieee80211_hdr_3addr *frame = (व्योम *)rxmgmt->frame_data;
	स्थिर u16 frame_len = len - माप(*rxmgmt);
	क्रमागत nl80211_rxmgmt_flags flags = 0;

	अगर (unlikely(len < min_len)) अणु
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       vअगर->mac->macid, vअगर->vअगरid, len, min_len);
		वापस -EINVAL;
	पूर्ण

	अगर (le32_to_cpu(rxmgmt->flags) & QLINK_RXMGMT_FLAG_ANSWERED)
		flags |= NL80211_RXMGMT_FLAG_ANSWERED;

	pr_debug("%s LEN:%u FC:%.4X SA:%pM\n", vअगर->netdev->name, frame_len,
		 le16_to_cpu(frame->frame_control), frame->addr2);

	cfg80211_rx_mgmt(&vअगर->wdev, le32_to_cpu(rxmgmt->freq), rxmgmt->sig_dbm,
			 rxmgmt->frame_data, frame_len, flags);

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_scan_results(काष्ठा qtnf_vअगर *vअगर,
			       स्थिर काष्ठा qlink_event_scan_result *sr,
			       u16 len)
अणु
	काष्ठा cfg80211_bss *bss;
	काष्ठा ieee80211_channel *channel;
	काष्ठा wiphy *wiphy = priv_to_wiphy(vअगर->mac);
	क्रमागत cfg80211_bss_frame_type frame_type = CFG80211_BSS_FTYPE_UNKNOWN;
	माप_प्रकार payload_len;
	u16 tlv_type;
	u16 tlv_value_len;
	स्थिर काष्ठा qlink_tlv_hdr *tlv;
	स्थिर u8 *ies = शून्य;
	माप_प्रकार ies_len = 0;

	अगर (len < माप(*sr)) अणु
		pr_err("VIF%u.%u: payload is too short\n", vअगर->mac->macid,
		       vअगर->vअगरid);
		वापस -EINVAL;
	पूर्ण

	channel = ieee80211_get_channel(wiphy, le16_to_cpu(sr->freq));
	अगर (!channel) अणु
		pr_err("VIF%u.%u: channel at %u MHz not found\n",
		       vअगर->mac->macid, vअगर->vअगरid, le16_to_cpu(sr->freq));
		वापस -EINVAL;
	पूर्ण

	payload_len = len - माप(*sr);

	qlink_क्रम_each_tlv(tlv, sr->payload, payload_len) अणु
		tlv_type = le16_to_cpu(tlv->type);
		tlv_value_len = le16_to_cpu(tlv->len);

		अगर (tlv_type == QTN_TLV_ID_IE_SET) अणु
			स्थिर काष्ठा qlink_tlv_ie_set *ie_set;
			अचिन्हित पूर्णांक ie_len;

			अगर (tlv_value_len <
			    (माप(*ie_set) - माप(ie_set->hdr)))
				वापस -EINVAL;

			ie_set = (स्थिर काष्ठा qlink_tlv_ie_set *)tlv;
			ie_len = tlv_value_len -
				(माप(*ie_set) - माप(ie_set->hdr));

			चयन (ie_set->type) अणु
			हाल QLINK_IE_SET_BEACON_IES:
				frame_type = CFG80211_BSS_FTYPE_BEACON;
				अवरोध;
			हाल QLINK_IE_SET_PROBE_RESP_IES:
				frame_type = CFG80211_BSS_FTYPE_PRESP;
				अवरोध;
			शेष:
				frame_type = CFG80211_BSS_FTYPE_UNKNOWN;
			पूर्ण

			अगर (ie_len) अणु
				ies = ie_set->ie_data;
				ies_len = ie_len;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!qlink_tlv_parsing_ok(tlv, sr->payload, payload_len))
		वापस -EINVAL;

	bss = cfg80211_inक्रमm_bss(wiphy, channel, frame_type,
				  sr->bssid, get_unaligned_le64(&sr->tsf),
				  le16_to_cpu(sr->capab),
				  le16_to_cpu(sr->bपूर्णांकval), ies, ies_len,
				  DBM_TO_MBM(sr->sig_dbm), GFP_KERNEL);
	अगर (!bss)
		वापस -ENOMEM;

	cfg80211_put_bss(wiphy, bss);

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_scan_complete(काष्ठा qtnf_wmac *mac,
				स्थिर काष्ठा qlink_event_scan_complete *status,
				u16 len)
अणु
	अगर (len < माप(*status)) अणु
		pr_err("MAC%u: payload is too short\n", mac->macid);
		वापस -EINVAL;
	पूर्ण

	qtnf_scan_करोne(mac, le32_to_cpu(status->flags) & QLINK_SCAN_ABORTED);

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_freq_change(काष्ठा qtnf_wmac *mac,
			      स्थिर काष्ठा qlink_event_freq_change *data,
			      u16 len)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(mac);
	काष्ठा cfg80211_chan_def chandef;
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक i;

	अगर (len < माप(*data)) अणु
		pr_err("MAC%u: payload is too short\n", mac->macid);
		वापस -EINVAL;
	पूर्ण

	अगर (!wiphy->रेजिस्टरed)
		वापस 0;

	qlink_chandef_q2cfg(wiphy, &data->chan, &chandef);

	अगर (!cfg80211_chandef_valid(&chandef)) अणु
		pr_err("MAC%u: bad channel freq=%u cf1=%u cf2=%u bw=%u\n",
		       mac->macid, chandef.chan->center_freq,
		       chandef.center_freq1, chandef.center_freq2,
		       chandef.width);
		वापस -EINVAL;
	पूर्ण

	pr_debug("MAC%d: new channel ieee=%u freq1=%u freq2=%u bw=%u\n",
		 mac->macid, chandef.chan->hw_value, chandef.center_freq1,
		 chandef.center_freq2, chandef.width);

	क्रम (i = 0; i < QTNF_MAX_INTF; i++) अणु
		vअगर = &mac->अगरlist[i];

		अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_UNSPECIFIED)
			जारी;

		अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_STATION &&
		    !vअगर->wdev.current_bss)
			जारी;

		अगर (!vअगर->netdev)
			जारी;

		mutex_lock(&vअगर->wdev.mtx);
		cfg80211_ch_चयन_notअगरy(vअगर->netdev, &chandef);
		mutex_unlock(&vअगर->wdev.mtx);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_event_handle_radar(काष्ठा qtnf_vअगर *vअगर,
				   स्थिर काष्ठा qlink_event_radar *ev,
				   u16 len)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(vअगर->mac);
	काष्ठा cfg80211_chan_def chandef;

	अगर (len < माप(*ev)) अणु
		pr_err("MAC%u: payload is too short\n", vअगर->mac->macid);
		वापस -EINVAL;
	पूर्ण

	अगर (!wiphy->रेजिस्टरed || !vअगर->netdev)
		वापस 0;

	qlink_chandef_q2cfg(wiphy, &ev->chan, &chandef);

	अगर (!cfg80211_chandef_valid(&chandef)) अणु
		pr_err("MAC%u: bad channel f1=%u f2=%u bw=%u\n",
		       vअगर->mac->macid,
		       chandef.center_freq1, chandef.center_freq2,
		       chandef.width);
		वापस -EINVAL;
	पूर्ण

	pr_info("%s: radar event=%u f1=%u f2=%u bw=%u\n",
		vअगर->netdev->name, ev->event,
		chandef.center_freq1, chandef.center_freq2,
		chandef.width);

	चयन (ev->event) अणु
	हाल QLINK_RADAR_DETECTED:
		cfg80211_radar_event(wiphy, &chandef, GFP_KERNEL);
		अवरोध;
	हाल QLINK_RADAR_CAC_FINISHED:
		अगर (!vअगर->wdev.cac_started)
			अवरोध;

		cfg80211_cac_event(vअगर->netdev, &chandef,
				   NL80211_RADAR_CAC_FINISHED, GFP_KERNEL);
		अवरोध;
	हाल QLINK_RADAR_CAC_ABORTED:
		अगर (!vअगर->wdev.cac_started)
			अवरोध;

		cfg80211_cac_event(vअगर->netdev, &chandef,
				   NL80211_RADAR_CAC_ABORTED, GFP_KERNEL);
		अवरोध;
	हाल QLINK_RADAR_CAC_STARTED:
		अगर (vअगर->wdev.cac_started)
			अवरोध;

		अगर (!wiphy_ext_feature_isset(wiphy,
					     NL80211_EXT_FEATURE_DFS_OFFLOAD))
			अवरोध;

		cfg80211_cac_event(vअगर->netdev, &chandef,
				   NL80211_RADAR_CAC_STARTED, GFP_KERNEL);
		अवरोध;
	शेष:
		pr_warn("%s: unhandled radar event %u\n",
			vअगर->netdev->name, ev->event);
		अवरोध;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_बाह्यal_auth(काष्ठा qtnf_vअगर *vअगर,
				स्थिर काष्ठा qlink_event_बाह्यal_auth *ev,
				u16 len)
अणु
	काष्ठा cfg80211_बाह्यal_auth_params auth = अणु0पूर्ण;
	काष्ठा wiphy *wiphy = priv_to_wiphy(vअगर->mac);
	पूर्णांक ret;

	अगर (len < माप(*ev)) अणु
		pr_err("MAC%u: payload is too short\n", vअगर->mac->macid);
		वापस -EINVAL;
	पूर्ण

	अगर (!wiphy->रेजिस्टरed || !vअगर->netdev)
		वापस 0;

	अगर (ev->ssid_len) अणु
		पूर्णांक len = clamp_val(ev->ssid_len, 0, IEEE80211_MAX_SSID_LEN);

		स_नकल(auth.ssid.ssid, ev->ssid, len);
		auth.ssid.ssid_len = len;
	पूर्ण

	auth.key_mgmt_suite = le32_to_cpu(ev->akm_suite);
	ether_addr_copy(auth.bssid, ev->bssid);
	auth.action = ev->action;

	pr_debug("%s: external SAE processing: bss=%pM action=%u akm=%u\n",
		 vअगर->netdev->name, auth.bssid, auth.action,
		 auth.key_mgmt_suite);

	ret = cfg80211_बाह्यal_auth_request(vअगर->netdev, &auth, GFP_KERNEL);
	अगर (ret)
		pr_warn("failed to offload external auth request\n");

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_mic_failure(काष्ठा qtnf_vअगर *vअगर,
			      स्थिर काष्ठा qlink_event_mic_failure *mic_ev,
			      u16 len)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(vअगर->mac);
	u8 pairwise;

	अगर (len < माप(*mic_ev)) अणु
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       vअगर->mac->macid, vअगर->vअगरid, len,
		       माप(काष्ठा qlink_event_mic_failure));
		वापस -EINVAL;
	पूर्ण

	अगर (!wiphy->रेजिस्टरed || !vअगर->netdev)
		वापस 0;

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_STATION) अणु
		pr_err("VIF%u.%u: MIC_FAILURE event when not in STA mode\n",
		       vअगर->mac->macid, vअगर->vअगरid);
		वापस -EPROTO;
	पूर्ण

	pairwise = mic_ev->pairwise ?
		NL80211_KEYTYPE_PAIRWISE : NL80211_KEYTYPE_GROUP;

	pr_info("%s: MIC error: src=%pM key_index=%u pairwise=%u\n",
		vअगर->netdev->name, mic_ev->src, mic_ev->key_index, pairwise);

	cfg80211_michael_mic_failure(vअगर->netdev, mic_ev->src, pairwise,
				     mic_ev->key_index, शून्य, GFP_KERNEL);

	वापस 0;
पूर्ण

अटल पूर्णांक
qtnf_event_handle_update_owe(काष्ठा qtnf_vअगर *vअगर,
			     स्थिर काष्ठा qlink_event_update_owe *owe_ev,
			     u16 len)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(vअगर->mac);
	काष्ठा cfg80211_update_owe_info owe_info = अणुपूर्ण;
	स्थिर u16 ie_len = len - माप(*owe_ev);
	u8 *ie;

	अगर (len < माप(*owe_ev)) अणु
		pr_err("VIF%u.%u: payload is too short (%u < %zu)\n",
		       vअगर->mac->macid, vअगर->vअगरid, len,
		       माप(काष्ठा qlink_event_update_owe));
		वापस -EINVAL;
	पूर्ण

	अगर (!wiphy->रेजिस्टरed || !vअगर->netdev)
		वापस 0;

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_AP) अणु
		pr_err("VIF%u.%u: UPDATE_OWE event when not in AP mode\n",
		       vअगर->mac->macid, vअगर->vअगरid);
		वापस -EPROTO;
	पूर्ण

	ie = kzalloc(ie_len, GFP_KERNEL);
	अगर (!ie)
		वापस -ENOMEM;

	स_नकल(owe_info.peer, owe_ev->peer, ETH_ALEN);
	स_नकल(ie, owe_ev->ies, ie_len);
	owe_info.ie_len = ie_len;
	owe_info.ie = ie;

	pr_info("%s: external OWE processing: peer=%pM\n",
		vअगर->netdev->name, owe_ev->peer);

	cfg80211_update_owe_info_event(vअगर->netdev, &owe_info, GFP_KERNEL);
	kमुक्त(ie);

	वापस 0;
पूर्ण

अटल पूर्णांक qtnf_event_parse(काष्ठा qtnf_wmac *mac,
			    स्थिर काष्ठा sk_buff *event_skb)
अणु
	स्थिर काष्ठा qlink_event *event;
	काष्ठा qtnf_vअगर *vअगर = शून्य;
	पूर्णांक ret = -1;
	u16 event_id;
	u16 event_len;
	u8 vअगरid;

	event = (स्थिर काष्ठा qlink_event *)event_skb->data;
	event_id = le16_to_cpu(event->event_id);
	event_len = le16_to_cpu(event->mhdr.len);

	अगर (event->vअगरid >= QTNF_MAX_INTF) अणु
		pr_err("invalid vif(%u)\n", event->vअगरid);
		वापस -EINVAL;
	पूर्ण

	vअगरid = array_index_nospec(event->vअगरid, QTNF_MAX_INTF);
	vअगर = &mac->अगरlist[vअगरid];

	चयन (event_id) अणु
	हाल QLINK_EVENT_STA_ASSOCIATED:
		ret = qtnf_event_handle_sta_assoc(mac, vअगर, (स्थिर व्योम *)event,
						  event_len);
		अवरोध;
	हाल QLINK_EVENT_STA_DEAUTH:
		ret = qtnf_event_handle_sta_deauth(mac, vअगर,
						   (स्थिर व्योम *)event,
						   event_len);
		अवरोध;
	हाल QLINK_EVENT_MGMT_RECEIVED:
		ret = qtnf_event_handle_mgmt_received(vअगर, (स्थिर व्योम *)event,
						      event_len);
		अवरोध;
	हाल QLINK_EVENT_SCAN_RESULTS:
		ret = qtnf_event_handle_scan_results(vअगर, (स्थिर व्योम *)event,
						     event_len);
		अवरोध;
	हाल QLINK_EVENT_SCAN_COMPLETE:
		ret = qtnf_event_handle_scan_complete(mac, (स्थिर व्योम *)event,
						      event_len);
		अवरोध;
	हाल QLINK_EVENT_BSS_JOIN:
		ret = qtnf_event_handle_bss_join(vअगर, (स्थिर व्योम *)event,
						 event_len);
		अवरोध;
	हाल QLINK_EVENT_BSS_LEAVE:
		ret = qtnf_event_handle_bss_leave(vअगर, (स्थिर व्योम *)event,
						  event_len);
		अवरोध;
	हाल QLINK_EVENT_FREQ_CHANGE:
		ret = qtnf_event_handle_freq_change(mac, (स्थिर व्योम *)event,
						    event_len);
		अवरोध;
	हाल QLINK_EVENT_RADAR:
		ret = qtnf_event_handle_radar(vअगर, (स्थिर व्योम *)event,
					      event_len);
		अवरोध;
	हाल QLINK_EVENT_EXTERNAL_AUTH:
		ret = qtnf_event_handle_बाह्यal_auth(vअगर, (स्थिर व्योम *)event,
						      event_len);
		अवरोध;
	हाल QLINK_EVENT_MIC_FAILURE:
		ret = qtnf_event_handle_mic_failure(vअगर, (स्थिर व्योम *)event,
						    event_len);
		अवरोध;
	हाल QLINK_EVENT_UPDATE_OWE:
		ret = qtnf_event_handle_update_owe(vअगर, (स्थिर व्योम *)event,
						   event_len);
		अवरोध;
	शेष:
		pr_warn("unknown event type: %x\n", event_id);
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_event_process_skb(काष्ठा qtnf_bus *bus,
				  स्थिर काष्ठा sk_buff *skb)
अणु
	स्थिर काष्ठा qlink_event *event;
	काष्ठा qtnf_wmac *mac;
	पूर्णांक res;

	अगर (unlikely(!skb || skb->len < माप(*event))) अणु
		pr_err("invalid event buffer\n");
		वापस -EINVAL;
	पूर्ण

	event = (काष्ठा qlink_event *)skb->data;

	mac = qtnf_core_get_mac(bus, event->macid);

	pr_debug("new event id:%x len:%u mac:%u vif:%u\n",
		 le16_to_cpu(event->event_id), le16_to_cpu(event->mhdr.len),
		 event->macid, event->vअगरid);

	अगर (unlikely(!mac))
		वापस -ENXIO;

	rtnl_lock();
	res = qtnf_event_parse(mac, skb);
	rtnl_unlock();

	वापस res;
पूर्ण

व्योम qtnf_event_work_handler(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा qtnf_bus *bus = container_of(work, काष्ठा qtnf_bus, event_work);
	काष्ठा sk_buff_head *event_queue = &bus->trans.event_queue;
	काष्ठा sk_buff *current_event_skb = skb_dequeue(event_queue);

	जबतक (current_event_skb) अणु
		qtnf_event_process_skb(bus, current_event_skb);
		dev_kमुक्त_skb_any(current_event_skb);
		current_event_skb = skb_dequeue(event_queue);
	पूर्ण
पूर्ण
