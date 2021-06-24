<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0+
/* Copyright (c) 2015-2016 Quantenna Communications. All rights reserved. */

#समावेश <linux/kernel.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <linux/ieee80211.h>
#समावेश <net/cfg80211.h>
#समावेश <net/netlink.h>

#समावेश "cfg80211.h"
#समावेश "commands.h"
#समावेश "core.h"
#समावेश "util.h"
#समावेश "bus.h"

/* Supported rates to be advertised to the cfg80211 */
अटल काष्ठा ieee80211_rate qtnf_rates_2g[] = अणु
	अणु.bitrate = 10, .hw_value = 2, पूर्ण,
	अणु.bitrate = 20, .hw_value = 4, पूर्ण,
	अणु.bitrate = 55, .hw_value = 11, पूर्ण,
	अणु.bitrate = 110, .hw_value = 22, पूर्ण,
	अणु.bitrate = 60, .hw_value = 12, पूर्ण,
	अणु.bitrate = 90, .hw_value = 18, पूर्ण,
	अणु.bitrate = 120, .hw_value = 24, पूर्ण,
	अणु.bitrate = 180, .hw_value = 36, पूर्ण,
	अणु.bitrate = 240, .hw_value = 48, पूर्ण,
	अणु.bitrate = 360, .hw_value = 72, पूर्ण,
	अणु.bitrate = 480, .hw_value = 96, पूर्ण,
	अणु.bitrate = 540, .hw_value = 108, पूर्ण,
पूर्ण;

/* Supported rates to be advertised to the cfg80211 */
अटल काष्ठा ieee80211_rate qtnf_rates_5g[] = अणु
	अणु.bitrate = 60, .hw_value = 12, पूर्ण,
	अणु.bitrate = 90, .hw_value = 18, पूर्ण,
	अणु.bitrate = 120, .hw_value = 24, पूर्ण,
	अणु.bitrate = 180, .hw_value = 36, पूर्ण,
	अणु.bitrate = 240, .hw_value = 48, पूर्ण,
	अणु.bitrate = 360, .hw_value = 72, पूर्ण,
	अणु.bitrate = 480, .hw_value = 96, पूर्ण,
	अणु.bitrate = 540, .hw_value = 108, पूर्ण,
पूर्ण;

/* Supported crypto cipher suits to be advertised to cfg80211 */
अटल स्थिर u32 qtnf_cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_TKIP,
	WLAN_CIPHER_SUITE_CCMP,
	WLAN_CIPHER_SUITE_AES_CMAC,
पूर्ण;

/* Supported mgmt frame types to be advertised to cfg80211 */
अटल स्थिर काष्ठा ieee80211_txrx_stypes
qtnf_mgmt_stypes[NUM_NL80211_IFTYPES] = अणु
	[NL80211_IFTYPE_STATION] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4),
	पूर्ण,
	[NL80211_IFTYPE_AP] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		      BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
		      BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
		      BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
		      BIT(IEEE80211_STYPE_AUTH >> 4),
	पूर्ण,
पूर्ण;

अटल पूर्णांक
qtnf_validate_अगरace_combinations(काष्ठा wiphy *wiphy,
				 काष्ठा qtnf_vअगर *change_vअगर,
				 क्रमागत nl80211_अगरtype new_type)
अणु
	काष्ठा qtnf_wmac *mac;
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक i;
	पूर्णांक ret = 0;
	काष्ठा अगरace_combination_params params = अणु
		.num_dअगरferent_channels = 1,
	पूर्ण;

	mac = wiphy_priv(wiphy);
	अगर (!mac)
		वापस -EFAULT;

	क्रम (i = 0; i < QTNF_MAX_INTF; i++) अणु
		vअगर = &mac->अगरlist[i];
		अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_UNSPECIFIED)
			params.अगरtype_num[vअगर->wdev.अगरtype]++;
	पूर्ण

	अगर (change_vअगर) अणु
		params.अगरtype_num[new_type]++;
		params.अगरtype_num[change_vअगर->wdev.अगरtype]--;
	पूर्ण अन्यथा अणु
		params.अगरtype_num[new_type]++;
	पूर्ण

	ret = cfg80211_check_combinations(wiphy, &params);

	अगर (ret)
		वापस ret;

	/* Check repeater पूर्णांकerface combination: primary VIF should be STA only.
	 * STA (primary) + AP (secondary) is OK.
	 * AP (primary) + STA (secondary) is not supported.
	 */
	vअगर = qtnf_mac_get_base_vअगर(mac);
	अगर (vअगर && vअगर->wdev.अगरtype == NL80211_IFTYPE_AP &&
	    vअगर != change_vअगर && new_type == NL80211_IFTYPE_STATION) अणु
		ret = -EINVAL;
		pr_err("MAC%u invalid combination: AP as primary repeater interface is not supported\n",
		       mac->macid);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_change_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
			 काष्ठा net_device *dev,
			 क्रमागत nl80211_अगरtype type,
			 काष्ठा vअगर_params *params)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	u8 *mac_addr = शून्य;
	पूर्णांक use4addr = 0;
	पूर्णांक ret;

	ret = qtnf_validate_अगरace_combinations(wiphy, vअगर, type);
	अगर (ret) अणु
		pr_err("VIF%u.%u combination check: failed to set type %d\n",
		       vअगर->mac->macid, vअगर->vअगरid, type);
		वापस ret;
	पूर्ण

	अगर (params) अणु
		mac_addr = params->macaddr;
		use4addr = params->use_4addr;
	पूर्ण

	qtnf_scan_करोne(vअगर->mac, true);

	ret = qtnf_cmd_send_change_पूर्णांकf_type(vअगर, type, use4addr, mac_addr);
	अगर (ret) अणु
		pr_err("VIF%u.%u: failed to change type to %d\n",
		       vअगर->mac->macid, vअगर->vअगरid, type);
		वापस ret;
	पूर्ण

	vअगर->wdev.अगरtype = type;
	वापस 0;
पूर्ण

पूर्णांक qtnf_del_भव_पूर्णांकf(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev)
अणु
	काष्ठा net_device *netdev =  wdev->netdev;
	काष्ठा qtnf_vअगर *vअगर;
	काष्ठा sk_buff *skb;

	अगर (WARN_ON(!netdev))
		वापस -EFAULT;

	vअगर = qtnf_netdev_get_priv(wdev->netdev);

	qtnf_scan_करोne(vअगर->mac, true);

	/* Stop data */
	netअगर_tx_stop_all_queues(netdev);
	अगर (netअगर_carrier_ok(netdev))
		netअगर_carrier_off(netdev);

	जबतक ((skb = skb_dequeue(&vअगर->high_pri_tx_queue)))
		dev_kमुक्त_skb_any(skb);

	cancel_work_sync(&vअगर->high_pri_tx_work);

	अगर (netdev->reg_state == NETREG_REGISTERED)
		cfg80211_unरेजिस्टर_netdevice(netdev);

	अगर (qtnf_cmd_send_del_पूर्णांकf(vअगर))
		pr_err("VIF%u.%u: failed to delete VIF\n", vअगर->mac->macid,
		       vअगर->vअगरid);

	vअगर->netdev->ieee80211_ptr = शून्य;
	vअगर->netdev = शून्य;
	vअगर->wdev.अगरtype = NL80211_IFTYPE_UNSPECIFIED;

	वापस 0;
पूर्ण

अटल काष्ठा wireless_dev *qtnf_add_भव_पूर्णांकf(काष्ठा wiphy *wiphy,
						  स्थिर अक्षर *name,
						  अचिन्हित अक्षर name_assign_t,
						  क्रमागत nl80211_अगरtype type,
						  काष्ठा vअगर_params *params)
अणु
	काष्ठा qtnf_wmac *mac;
	काष्ठा qtnf_vअगर *vअगर;
	u8 *mac_addr = शून्य;
	पूर्णांक use4addr = 0;
	पूर्णांक ret;

	mac = wiphy_priv(wiphy);

	अगर (!mac)
		वापस ERR_PTR(-EFAULT);

	ret = qtnf_validate_अगरace_combinations(wiphy, शून्य, type);
	अगर (ret) अणु
		pr_err("MAC%u invalid combination: failed to add type %d\n",
		       mac->macid, type);
		वापस ERR_PTR(ret);
	पूर्ण

	चयन (type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_AP:
		vअगर = qtnf_mac_get_मुक्त_vअगर(mac);
		अगर (!vअगर) अणु
			pr_err("MAC%u: no free VIF available\n", mac->macid);
			वापस ERR_PTR(-EFAULT);
		पूर्ण

		eth_zero_addr(vअगर->mac_addr);
		eth_zero_addr(vअगर->bssid);
		vअगर->bss_priority = QTNF_DEF_BSS_PRIORITY;
		स_रखो(&vअगर->wdev, 0, माप(vअगर->wdev));
		vअगर->wdev.wiphy = wiphy;
		vअगर->wdev.अगरtype = type;
		अवरोध;
	शेष:
		pr_err("MAC%u: unsupported IF type %d\n", mac->macid, type);
		वापस ERR_PTR(-ENOTSUPP);
	पूर्ण

	अगर (params) अणु
		mac_addr = params->macaddr;
		use4addr = params->use_4addr;
	पूर्ण

	ret = qtnf_cmd_send_add_पूर्णांकf(vअगर, type, use4addr, mac_addr);
	अगर (ret) अणु
		pr_err("VIF%u.%u: failed to add VIF %pM\n",
		       mac->macid, vअगर->vअगरid, mac_addr);
		जाओ err_cmd;
	पूर्ण

	अगर (!is_valid_ether_addr(vअगर->mac_addr)) अणु
		pr_err("VIF%u.%u: FW reported bad MAC: %pM\n",
		       mac->macid, vअगर->vअगरid, vअगर->mac_addr);
		ret = -EINVAL;
		जाओ error_del_vअगर;
	पूर्ण

	ret = qtnf_core_net_attach(mac, vअगर, name, name_assign_t);
	अगर (ret) अणु
		pr_err("VIF%u.%u: failed to attach netdev\n", mac->macid,
		       vअगर->vअगरid);
		जाओ error_del_vअगर;
	पूर्ण

	अगर (qtnf_hwcap_is_set(&mac->bus->hw_info, QLINK_HW_CAPAB_HW_BRIDGE)) अणु
		ret = qtnf_cmd_netdev_changeupper(vअगर, vअगर->netdev->अगरindex);
		अगर (ret) अणु
			cfg80211_unरेजिस्टर_netdevice(vअगर->netdev);
			vअगर->netdev = शून्य;
			जाओ error_del_vअगर;
		पूर्ण
	पूर्ण

	vअगर->wdev.netdev = vअगर->netdev;
	वापस &vअगर->wdev;

error_del_vअगर:
	qtnf_cmd_send_del_पूर्णांकf(vअगर);
err_cmd:
	vअगर->wdev.अगरtype = NL80211_IFTYPE_UNSPECIFIED;

	वापस ERR_PTR(ret);
पूर्ण

अटल पूर्णांक qtnf_mgmt_set_appie(काष्ठा qtnf_vअगर *vअगर,
			       स्थिर काष्ठा cfg80211_beacon_data *info)
अणु
	पूर्णांक ret = 0;

	अगर (!info->beacon_ies || !info->beacon_ies_len) अणु
		ret = qtnf_cmd_send_mgmt_set_appie(vअगर, QLINK_IE_SET_BEACON_IES,
						   शून्य, 0);
	पूर्ण अन्यथा अणु
		ret = qtnf_cmd_send_mgmt_set_appie(vअगर, QLINK_IE_SET_BEACON_IES,
						   info->beacon_ies,
						   info->beacon_ies_len);
	पूर्ण

	अगर (ret)
		जाओ out;

	अगर (!info->proberesp_ies || !info->proberesp_ies_len) अणु
		ret = qtnf_cmd_send_mgmt_set_appie(vअगर,
						   QLINK_IE_SET_PROBE_RESP_IES,
						   शून्य, 0);
	पूर्ण अन्यथा अणु
		ret = qtnf_cmd_send_mgmt_set_appie(vअगर,
						   QLINK_IE_SET_PROBE_RESP_IES,
						   info->proberesp_ies,
						   info->proberesp_ies_len);
	पूर्ण

	अगर (ret)
		जाओ out;

	अगर (!info->assocresp_ies || !info->assocresp_ies_len) अणु
		ret = qtnf_cmd_send_mgmt_set_appie(vअगर,
						   QLINK_IE_SET_ASSOC_RESP,
						   शून्य, 0);
	पूर्ण अन्यथा अणु
		ret = qtnf_cmd_send_mgmt_set_appie(vअगर,
						   QLINK_IE_SET_ASSOC_RESP,
						   info->assocresp_ies,
						   info->assocresp_ies_len);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_change_beacon(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			      काष्ठा cfg80211_beacon_data *info)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);

	वापस qtnf_mgmt_set_appie(vअगर, info);
पूर्ण

अटल पूर्णांक qtnf_start_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			 काष्ठा cfg80211_ap_settings *settings)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	ret = qtnf_cmd_send_start_ap(vअगर, settings);
	अगर (ret)
		pr_err("VIF%u.%u: failed to start AP\n", vअगर->mac->macid,
		       vअगर->vअगरid);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_stop_ap(काष्ठा wiphy *wiphy, काष्ठा net_device *dev)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	qtnf_scan_करोne(vअगर->mac, true);

	ret = qtnf_cmd_send_stop_ap(vअगर);
	अगर (ret)
		pr_err("VIF%u.%u: failed to stop AP operation in FW\n",
		       vअगर->mac->macid, vअगर->vअगरid);

	netअगर_carrier_off(vअगर->netdev);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक ret;

	vअगर = qtnf_mac_get_base_vअगर(mac);
	अगर (!vअगर) अणु
		pr_err("MAC%u: primary VIF is not configured\n", mac->macid);
		वापस -EFAULT;
	पूर्ण

	ret = qtnf_cmd_send_update_phy_params(mac, changed);
	अगर (ret)
		pr_err("MAC%u: failed to update PHY params\n", mac->macid);

	वापस ret;
पूर्ण

अटल व्योम
qtnf_update_mgmt_frame_registrations(काष्ठा wiphy *wiphy,
				     काष्ठा wireless_dev *wdev,
				     काष्ठा mgmt_frame_regs *upd)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(wdev->netdev);
	u16 new_mask = upd->पूर्णांकerface_stypes;
	u16 old_mask = vअगर->mgmt_frames_biपंचांगask;
	अटल स्थिर काष्ठा अणु
		u16 mask, qlink_type;
	पूर्ण updates[] = अणु
		अणु
			.mask = BIT(IEEE80211_STYPE_REASSOC_REQ >> 4) |
				BIT(IEEE80211_STYPE_ASSOC_REQ >> 4),
			.qlink_type = QLINK_MGMT_FRAME_ASSOC_REQ,
		पूर्ण,
		अणु
			.mask = BIT(IEEE80211_STYPE_AUTH >> 4),
			.qlink_type = QLINK_MGMT_FRAME_AUTH,
		पूर्ण,
		अणु
			.mask = BIT(IEEE80211_STYPE_PROBE_REQ >> 4),
			.qlink_type = QLINK_MGMT_FRAME_PROBE_REQ,
		पूर्ण,
		अणु
			.mask = BIT(IEEE80211_STYPE_ACTION >> 4),
			.qlink_type = QLINK_MGMT_FRAME_ACTION,
		पूर्ण,
	पूर्ण;
	अचिन्हित पूर्णांक i;

	अगर (new_mask == old_mask)
		वापस;

	क्रम (i = 0; i < ARRAY_SIZE(updates); i++) अणु
		u16 mask = updates[i].mask;
		u16 qlink_frame_type = updates[i].qlink_type;
		bool reg;

		/* the ! are here due to the assoc/reassoc merge */
		अगर (!(new_mask & mask) == !(old_mask & mask))
			जारी;

		reg = new_mask & mask;

		अगर (qtnf_cmd_send_रेजिस्टर_mgmt(vअगर, qlink_frame_type, reg))
			pr_warn("VIF%u.%u: failed to %sregister qlink frame type 0x%x\n",
				vअगर->mac->macid, vअगर->vअगरid, reg ? "" : "un",
				qlink_frame_type);
	पूर्ण

	vअगर->mgmt_frames_biपंचांगask = new_mask;
पूर्ण

अटल पूर्णांक
qtnf_mgmt_tx(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
	     काष्ठा cfg80211_mgmt_tx_params *params, u64 *cookie)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(wdev->netdev);
	स्थिर काष्ठा ieee80211_mgmt *mgmt_frame = (व्योम *)params->buf;
	u32 लघु_cookie = pअक्रमom_u32();
	u16 flags = 0;
	u16 freq;

	*cookie = लघु_cookie;

	अगर (params->offchan)
		flags |= QLINK_FRAME_TX_FLAG_OFFCHAN;

	अगर (params->no_cck)
		flags |= QLINK_FRAME_TX_FLAG_NO_CCK;

	अगर (params->करोnt_रुको_क्रम_ack)
		flags |= QLINK_FRAME_TX_FLAG_ACK_NOWAIT;

	/* If channel is not specअगरied, pass "freq = 0" to tell device
	 * firmware to use current channel.
	 */
	अगर (params->chan)
		freq = params->chan->center_freq;
	अन्यथा
		freq = 0;

	pr_debug("%s freq:%u; FC:%.4X; DA:%pM; len:%zu; C:%.8X; FL:%.4X\n",
		 wdev->netdev->name, freq,
		 le16_to_cpu(mgmt_frame->frame_control), mgmt_frame->da,
		 params->len, लघु_cookie, flags);

	वापस qtnf_cmd_send_frame(vअगर, लघु_cookie, flags,
				   freq, params->buf, params->len);
पूर्ण

अटल पूर्णांक
qtnf_get_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		 स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);

	sinfo->generation = vअगर->generation;
	वापस qtnf_cmd_get_sta_info(vअगर, mac, sinfo);
पूर्ण

अटल पूर्णांक
qtnf_dump_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		  पूर्णांक idx, u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	स्थिर काष्ठा qtnf_sta_node *sta_node;
	पूर्णांक ret;

	चयन (vअगर->wdev.अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
		अगर (idx != 0 || !vअगर->wdev.current_bss)
			वापस -ENOENT;

		ether_addr_copy(mac, vअगर->bssid);
		अवरोध;
	हाल NL80211_IFTYPE_AP:
		sta_node = qtnf_sta_list_lookup_index(&vअगर->sta_list, idx);
		अगर (unlikely(!sta_node))
			वापस -ENOENT;

		ether_addr_copy(mac, sta_node->mac_addr);
		अवरोध;
	शेष:
		वापस -ENOTSUPP;
	पूर्ण

	ret = qtnf_cmd_get_sta_info(vअगर, mac, sinfo);

	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_AP) अणु
		अगर (ret == -ENOENT) अणु
			cfg80211_del_sta(vअगर->netdev, mac, GFP_KERNEL);
			sinfo->filled = 0;
		पूर्ण
	पूर्ण

	sinfo->generation = vअगर->generation;

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_add_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			u8 key_index, bool pairwise, स्थिर u8 *mac_addr,
			काष्ठा key_params *params)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	ret = qtnf_cmd_send_add_key(vअगर, key_index, pairwise, mac_addr, params);
	अगर (ret)
		pr_err("VIF%u.%u: failed to add key: cipher=%x idx=%u pw=%u\n",
		       vअगर->mac->macid, vअगर->vअगरid, params->cipher, key_index,
		       pairwise);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_del_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			u8 key_index, bool pairwise, स्थिर u8 *mac_addr)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	ret = qtnf_cmd_send_del_key(vअगर, key_index, pairwise, mac_addr);
	अगर (ret) अणु
		अगर (ret == -ENOENT) अणु
			pr_debug("VIF%u.%u: key index %d out of bounds\n",
				 vअगर->mac->macid, vअगर->vअगरid, key_index);
		पूर्ण अन्यथा अणु
			pr_err("VIF%u.%u: failed to delete key: idx=%u pw=%u\n",
			       vअगर->mac->macid, vअगर->vअगरid,
			       key_index, pairwise);
		पूर्ण
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_set_शेष_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				u8 key_index, bool unicast, bool multicast)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	ret = qtnf_cmd_send_set_शेष_key(vअगर, key_index, unicast, multicast);
	अगर (ret)
		pr_err("VIF%u.%u: failed to set dflt key: idx=%u uc=%u mc=%u\n",
		       vअगर->mac->macid, vअगर->vअगरid, key_index, unicast,
		       multicast);

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_set_शेष_mgmt_key(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			  u8 key_index)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	ret = qtnf_cmd_send_set_शेष_mgmt_key(vअगर, key_index);
	अगर (ret)
		pr_err("VIF%u.%u: failed to set default MGMT key: idx=%u\n",
		       vअगर->mac->macid, vअगर->vअगरid, key_index);

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_change_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		    स्थिर u8 *mac, काष्ठा station_parameters *params)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	ret = qtnf_cmd_send_change_sta(vअगर, mac, params);
	अगर (ret)
		pr_err("VIF%u.%u: failed to change STA %pM\n",
		       vअगर->mac->macid, vअगर->vअगरid, mac);

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_del_station(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		 काष्ठा station_del_parameters *params)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	अगर (params->mac &&
	    (vअगर->wdev.अगरtype == NL80211_IFTYPE_AP) &&
	    !is_broadcast_ether_addr(params->mac) &&
	    !qtnf_sta_list_lookup(&vअगर->sta_list, params->mac))
		वापस 0;

	ret = qtnf_cmd_send_del_sta(vअगर, params);
	अगर (ret)
		pr_err("VIF%u.%u: failed to delete STA %pM\n",
		       vअगर->mac->macid, vअगर->vअगरid, params->mac);

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_scan(काष्ठा wiphy *wiphy, काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);
	पूर्णांक ret;

	cancel_delayed_work_sync(&mac->scan_समयout);

	mac->scan_req = request;

	ret = qtnf_cmd_send_scan(mac);
	अगर (ret) अणु
		pr_err("MAC%u: failed to start scan\n", mac->macid);
		mac->scan_req = शून्य;
		जाओ out;
	पूर्ण

	pr_debug("MAC%u: scan started\n", mac->macid);
	queue_delayed_work(mac->bus->workqueue, &mac->scan_समयout,
			   QTNF_SCAN_TIMEOUT_SEC * HZ);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_connect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
	     काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_STATION)
		वापस -EOPNOTSUPP;

	अगर (sme->auth_type == NL80211_AUTHTYPE_SAE &&
	    !(sme->flags & CONNECT_REQ_EXTERNAL_AUTH_SUPPORT)) अणु
		pr_err("can not offload authentication to userspace\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (sme->bssid)
		ether_addr_copy(vअगर->bssid, sme->bssid);
	अन्यथा
		eth_zero_addr(vअगर->bssid);

	ret = qtnf_cmd_send_connect(vअगर, sme);
	अगर (ret)
		pr_err("VIF%u.%u: failed to connect\n",
		       vअगर->mac->macid, vअगर->vअगरid);

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_बाह्यal_auth(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		   काष्ठा cfg80211_बाह्यal_auth_params *auth)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_STATION &&
	    !ether_addr_equal(vअगर->bssid, auth->bssid))
		pr_warn("unexpected bssid: %pM", auth->bssid);

	ret = qtnf_cmd_send_बाह्यal_auth(vअगर, auth);
	अगर (ret)
		pr_err("VIF%u.%u: failed to report external auth\n",
		       vअगर->mac->macid, vअगर->vअगरid);

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_disconnect(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		u16 reason_code)
अणु
	काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक ret = 0;

	vअगर = qtnf_mac_get_base_vअगर(mac);
	अगर (!vअगर) अणु
		pr_err("MAC%u: primary VIF is not configured\n", mac->macid);
		वापस -EFAULT;
	पूर्ण

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_STATION) अणु
		वापस -EOPNOTSUPP;
	पूर्ण

	ret = qtnf_cmd_send_disconnect(vअगर, reason_code);
	अगर (ret)
		pr_err("VIF%u.%u: failed to disconnect\n",
		       mac->macid, vअगर->vअगरid);

	अगर (vअगर->wdev.current_bss) अणु
		netअगर_carrier_off(vअगर->netdev);
		cfg80211_disconnected(vअगर->netdev, reason_code,
				      शून्य, 0, true, GFP_KERNEL);
	पूर्ण

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_dump_survey(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
		 पूर्णांक idx, काष्ठा survey_info *survey)
अणु
	काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा ieee80211_supported_band *sband;
	स्थिर काष्ठा cfg80211_chan_def *chandef = &wdev->chandef;
	काष्ठा ieee80211_channel *chan;
	पूर्णांक ret;

	sband = wiphy->bands[NL80211_BAND_2GHZ];
	अगर (sband && idx >= sband->n_channels) अणु
		idx -= sband->n_channels;
		sband = शून्य;
	पूर्ण

	अगर (!sband)
		sband = wiphy->bands[NL80211_BAND_5GHZ];

	अगर (!sband || idx >= sband->n_channels)
		वापस -ENOENT;

	chan = &sband->channels[idx];
	survey->channel = chan;
	survey->filled = 0x0;

	अगर (chan == chandef->chan)
		survey->filled = SURVEY_INFO_IN_USE;

	ret = qtnf_cmd_get_chan_stats(mac, chan->center_freq, survey);
	अगर (ret)
		pr_debug("failed to get chan(%d) stats from card\n",
			 chan->hw_value);

	वापस ret;
पूर्ण

अटल पूर्णांक
qtnf_get_channel(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
		 काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा net_device *ndev = wdev->netdev;
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक ret;

	अगर (!ndev)
		वापस -ENODEV;

	vअगर = qtnf_netdev_get_priv(wdev->netdev);

	ret = qtnf_cmd_get_channel(vअगर, chandef);
	अगर (ret) अणु
		pr_err("%s: failed to get channel: %d\n", ndev->name, ret);
		ret = -ENODATA;
		जाओ out;
	पूर्ण

	अगर (!cfg80211_chandef_valid(chandef)) अणु
		pr_err("%s: bad channel freq=%u cf1=%u cf2=%u bw=%u\n",
		       ndev->name, chandef->chan->center_freq,
		       chandef->center_freq1, chandef->center_freq2,
		       chandef->width);
		ret = -ENODATA;
		जाओ out;
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_channel_चयन(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       काष्ठा cfg80211_csa_settings *params)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	pr_debug("%s: chan(%u) count(%u) radar(%u) block_tx(%u)\n", dev->name,
		 params->chandef.chan->hw_value, params->count,
		 params->radar_required, params->block_tx);

	अगर (!cfg80211_chandef_valid(&params->chandef)) अणु
		pr_err("%s: invalid channel\n", dev->name);
		वापस -EINVAL;
	पूर्ण

	ret = qtnf_cmd_send_chan_चयन(vअगर, params);
	अगर (ret)
		pr_warn("%s: failed to switch to channel (%u)\n",
			dev->name, params->chandef.chan->hw_value);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_start_radar_detection(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *ndev,
				      काष्ठा cfg80211_chan_def *chandef,
				      u32 cac_समय_ms)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(ndev);
	पूर्णांक ret;

	अगर (wiphy_ext_feature_isset(wiphy, NL80211_EXT_FEATURE_DFS_OFFLOAD))
		वापस -ENOTSUPP;

	ret = qtnf_cmd_start_cac(vअगर, chandef, cac_समय_ms);
	अगर (ret)
		pr_err("%s: failed to start CAC ret=%d\n", ndev->name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_set_mac_acl(काष्ठा wiphy *wiphy,
			    काष्ठा net_device *dev,
			    स्थिर काष्ठा cfg80211_acl_data *params)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	ret = qtnf_cmd_set_mac_acl(vअगर, params);
	अगर (ret)
		pr_err("%s: failed to set mac ACL ret=%d\n", dev->name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_set_घातer_mgmt(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			       bool enabled, पूर्णांक समयout)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	ret = qtnf_cmd_send_pm_set(vअगर, enabled ? QLINK_PM_AUTO_STANDBY :
				   QLINK_PM_OFF, समयout);
	अगर (ret)
		pr_err("%s: failed to set PM mode ret=%d\n", dev->name, ret);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_get_tx_घातer(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			     पूर्णांक *dbm)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(wdev->netdev);
	पूर्णांक ret;

	ret = qtnf_cmd_get_tx_घातer(vअगर, dbm);
	अगर (ret)
		pr_err("MAC%u: failed to get Tx power\n", vअगर->mac->macid);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_set_tx_घातer(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			     क्रमागत nl80211_tx_घातer_setting type, पूर्णांक mbm)
अणु
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक ret;

	अगर (wdev) अणु
		vअगर = qtnf_netdev_get_priv(wdev->netdev);
	पूर्ण अन्यथा अणु
		काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);

		vअगर = qtnf_mac_get_base_vअगर(mac);
		अगर (!vअगर) अणु
			pr_err("MAC%u: primary VIF is not configured\n",
			       mac->macid);
			वापस -EFAULT;
		पूर्ण
	पूर्ण

	ret = qtnf_cmd_set_tx_घातer(vअगर, type, mbm);
	अगर (ret)
		pr_err("MAC%u: failed to set Tx power\n", vअगर->mac->macid);

	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_update_owe_info(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
				काष्ठा cfg80211_update_owe_info *owe_info)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(dev);
	पूर्णांक ret;

	अगर (vअगर->wdev.अगरtype != NL80211_IFTYPE_AP)
		वापस -EOPNOTSUPP;

	ret = qtnf_cmd_send_update_owe(vअगर, owe_info);
	अगर (ret)
		pr_err("VIF%u.%u: failed to update owe info\n",
		       vअगर->mac->macid, vअगर->vअगरid);

	वापस ret;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक qtnf_suspend(काष्ठा wiphy *wiphy, काष्ठा cfg80211_wowlan *wowlan)
अणु
	काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक ret = 0;

	vअगर = qtnf_mac_get_base_vअगर(mac);
	अगर (!vअगर) अणु
		pr_err("MAC%u: primary VIF is not configured\n", mac->macid);
		ret = -EFAULT;
		जाओ निकास;
	पूर्ण

	अगर (!wowlan) अणु
		pr_debug("WoWLAN triggers are not enabled\n");
		qtnf_भव_पूर्णांकf_cleanup(vअगर->netdev);
		जाओ निकास;
	पूर्ण

	qtnf_scan_करोne(vअगर->mac, true);

	ret = qtnf_cmd_send_wowlan_set(vअगर, wowlan);
	अगर (ret) अणु
		pr_err("MAC%u: failed to set WoWLAN triggers\n",
		       mac->macid);
		जाओ निकास;
	पूर्ण

निकास:
	वापस ret;
पूर्ण

अटल पूर्णांक qtnf_resume(काष्ठा wiphy *wiphy)
अणु
	काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);
	काष्ठा qtnf_vअगर *vअगर;
	पूर्णांक ret = 0;

	vअगर = qtnf_mac_get_base_vअगर(mac);
	अगर (!vअगर) अणु
		pr_err("MAC%u: primary VIF is not configured\n", mac->macid);
		वापस -EFAULT;
	पूर्ण

	ret = qtnf_cmd_send_wowlan_set(vअगर, शून्य);
	अगर (ret)
		pr_err("MAC%u: failed to reset WoWLAN triggers\n",
		       mac->macid);

	वापस ret;
पूर्ण

अटल व्योम qtnf_set_wakeup(काष्ठा wiphy *wiphy, bool enabled)
अणु
	काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);
	काष्ठा qtnf_bus *bus = mac->bus;

	device_set_wakeup_enable(bus->dev, enabled);
पूर्ण
#पूर्ण_अगर

अटल काष्ठा cfg80211_ops qtn_cfg80211_ops = अणु
	.add_भव_पूर्णांकf	= qtnf_add_भव_पूर्णांकf,
	.change_भव_पूर्णांकf	= qtnf_change_भव_पूर्णांकf,
	.del_भव_पूर्णांकf	= qtnf_del_भव_पूर्णांकf,
	.start_ap		= qtnf_start_ap,
	.change_beacon		= qtnf_change_beacon,
	.stop_ap		= qtnf_stop_ap,
	.set_wiphy_params	= qtnf_set_wiphy_params,
	.update_mgmt_frame_registrations =
		qtnf_update_mgmt_frame_registrations,
	.mgmt_tx		= qtnf_mgmt_tx,
	.change_station		= qtnf_change_station,
	.del_station		= qtnf_del_station,
	.get_station		= qtnf_get_station,
	.dump_station		= qtnf_dump_station,
	.add_key		= qtnf_add_key,
	.del_key		= qtnf_del_key,
	.set_शेष_key	= qtnf_set_शेष_key,
	.set_शेष_mgmt_key	= qtnf_set_शेष_mgmt_key,
	.scan			= qtnf_scan,
	.connect		= qtnf_connect,
	.बाह्यal_auth		= qtnf_बाह्यal_auth,
	.disconnect		= qtnf_disconnect,
	.dump_survey		= qtnf_dump_survey,
	.get_channel		= qtnf_get_channel,
	.channel_चयन		= qtnf_channel_चयन,
	.start_radar_detection	= qtnf_start_radar_detection,
	.set_mac_acl		= qtnf_set_mac_acl,
	.set_घातer_mgmt		= qtnf_set_घातer_mgmt,
	.get_tx_घातer		= qtnf_get_tx_घातer,
	.set_tx_घातer		= qtnf_set_tx_घातer,
	.update_owe_info	= qtnf_update_owe_info,
#अगर_घोषित CONFIG_PM
	.suspend		= qtnf_suspend,
	.resume			= qtnf_resume,
	.set_wakeup		= qtnf_set_wakeup,
#पूर्ण_अगर
पूर्ण;

अटल व्योम qtnf_cfg80211_reg_notअगरier(काष्ठा wiphy *wiphy,
				       काष्ठा regulatory_request *req)
अणु
	काष्ठा qtnf_wmac *mac = wiphy_priv(wiphy);
	क्रमागत nl80211_band band;
	पूर्णांक ret;

	pr_debug("MAC%u: initiator=%d alpha=%c%c\n", mac->macid, req->initiator,
		 req->alpha2[0], req->alpha2[1]);

	ret = qtnf_cmd_reg_notअगरy(mac, req, qtnf_slave_radar_get(),
				  qtnf_dfs_offload_get());
	अगर (ret) अणु
		pr_err("MAC%u: failed to update region to %c%c: %d\n",
		       mac->macid, req->alpha2[0], req->alpha2[1], ret);
		वापस;
	पूर्ण

	क्रम (band = 0; band < NUM_NL80211_BANDS; ++band) अणु
		अगर (!wiphy->bands[band])
			जारी;

		ret = qtnf_cmd_band_info_get(mac, wiphy->bands[band]);
		अगर (ret)
			pr_err("MAC%u: failed to update band %u\n",
			       mac->macid, band);
	पूर्ण
पूर्ण

काष्ठा wiphy *qtnf_wiphy_allocate(काष्ठा qtnf_bus *bus,
				  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wiphy *wiphy;

	अगर (qtnf_dfs_offload_get() &&
	    qtnf_hwcap_is_set(&bus->hw_info, QLINK_HW_CAPAB_DFS_OFFLOAD))
		qtn_cfg80211_ops.start_radar_detection = शून्य;

	अगर (!qtnf_hwcap_is_set(&bus->hw_info, QLINK_HW_CAPAB_PWR_MGMT))
		qtn_cfg80211_ops.set_घातer_mgmt	= शून्य;

	wiphy = wiphy_new(&qtn_cfg80211_ops, माप(काष्ठा qtnf_wmac));
	अगर (!wiphy)
		वापस शून्य;

	अगर (pdev)
		set_wiphy_dev(wiphy, &pdev->dev);
	अन्यथा
		set_wiphy_dev(wiphy, bus->dev);

	वापस wiphy;
पूर्ण

अटल पूर्णांक
qtnf_wiphy_setup_अगर_comb(काष्ठा wiphy *wiphy, काष्ठा qtnf_mac_info *mac_info)
अणु
	काष्ठा ieee80211_अगरace_combination *अगर_comb;
	माप_प्रकार n_अगर_comb;
	u16 पूर्णांकerface_modes = 0;
	माप_प्रकार i, j;

	अगर_comb = mac_info->अगर_comb;
	n_अगर_comb = mac_info->n_अगर_comb;

	अगर (!अगर_comb || !n_अगर_comb)
		वापस -ENOENT;

	क्रम (i = 0; i < n_अगर_comb; i++) अणु
		अगर_comb[i].radar_detect_widths = mac_info->radar_detect_widths;

		क्रम (j = 0; j < अगर_comb[i].n_limits; j++)
			पूर्णांकerface_modes |= अगर_comb[i].limits[j].types;
	पूर्ण

	wiphy->अगरace_combinations = अगर_comb;
	wiphy->n_अगरace_combinations = n_अगर_comb;
	wiphy->पूर्णांकerface_modes = पूर्णांकerface_modes;

	वापस 0;
पूर्ण

पूर्णांक qtnf_wiphy_रेजिस्टर(काष्ठा qtnf_hw_info *hw_info, काष्ठा qtnf_wmac *mac)
अणु
	काष्ठा wiphy *wiphy = priv_to_wiphy(mac);
	काष्ठा qtnf_mac_info *macinfo = &mac->macinfo;
	पूर्णांक ret;
	bool regकरोमुख्य_is_known;

	अगर (!wiphy) अणु
		pr_err("invalid wiphy pointer\n");
		वापस -EFAULT;
	पूर्ण

	wiphy->frag_threshold = macinfo->frag_thr;
	wiphy->rts_threshold = macinfo->rts_thr;
	wiphy->retry_लघु = macinfo->sretry_limit;
	wiphy->retry_दीर्घ = macinfo->lretry_limit;
	wiphy->coverage_class = macinfo->coverage_class;

	wiphy->max_scan_ssids =
		(macinfo->max_scan_ssids) ? macinfo->max_scan_ssids : 1;
	wiphy->max_scan_ie_len = QTNF_MAX_VSIE_LEN;
	wiphy->mgmt_stypes = qtnf_mgmt_stypes;
	wiphy->max_reमुख्य_on_channel_duration = 5000;
	wiphy->max_acl_mac_addrs = macinfo->max_acl_mac_addrs;
	wiphy->max_num_csa_counters = 2;

	ret = qtnf_wiphy_setup_अगर_comb(wiphy, macinfo);
	अगर (ret)
		जाओ out;

	/* Initialize cipher suits */
	wiphy->cipher_suites = qtnf_cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(qtnf_cipher_suites);
	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_MBM;
	wiphy->flags |= WIPHY_FLAG_HAVE_AP_SME |
			WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD |
			WIPHY_FLAG_AP_UAPSD |
			WIPHY_FLAG_HAS_CHANNEL_SWITCH |
			WIPHY_FLAG_4ADDR_STATION |
			WIPHY_FLAG_NETNS_OK;
	wiphy->flags &= ~WIPHY_FLAG_PS_ON_BY_DEFAULT;

	अगर (qtnf_dfs_offload_get() &&
	    qtnf_hwcap_is_set(hw_info, QLINK_HW_CAPAB_DFS_OFFLOAD))
		wiphy_ext_feature_set(wiphy, NL80211_EXT_FEATURE_DFS_OFFLOAD);

	अगर (qtnf_hwcap_is_set(hw_info, QLINK_HW_CAPAB_SCAN_DWELL))
		wiphy_ext_feature_set(wiphy,
				      NL80211_EXT_FEATURE_SET_SCAN_DWELL);

	wiphy->probe_resp_offload = NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
				    NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2;

	wiphy->available_antennas_tx = macinfo->num_tx_chain;
	wiphy->available_antennas_rx = macinfo->num_rx_chain;

	wiphy->max_ap_assoc_sta = macinfo->max_ap_assoc_sta;
	wiphy->ht_capa_mod_mask = &macinfo->ht_cap_mod_mask;
	wiphy->vht_capa_mod_mask = &macinfo->vht_cap_mod_mask;

	ether_addr_copy(wiphy->perm_addr, mac->macaddr);

	अगर (qtnf_hwcap_is_set(hw_info, QLINK_HW_CAPAB_STA_INACT_TIMEOUT))
		wiphy->features |= NL80211_FEATURE_INACTIVITY_TIMER;

	अगर (qtnf_hwcap_is_set(hw_info, QLINK_HW_CAPAB_SCAN_RANDOM_MAC_ADDR))
		wiphy->features |= NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;

	अगर (!qtnf_hwcap_is_set(hw_info, QLINK_HW_CAPAB_OBSS_SCAN))
		wiphy->features |= NL80211_FEATURE_NEED_OBSS_SCAN;

	अगर (qtnf_hwcap_is_set(hw_info, QLINK_HW_CAPAB_SAE))
		wiphy->features |= NL80211_FEATURE_SAE;

#अगर_घोषित CONFIG_PM
	अगर (macinfo->wowlan)
		wiphy->wowlan = macinfo->wowlan;
#पूर्ण_अगर

	regकरोमुख्य_is_known = है_अक्षर(mac->rd->alpha2[0]) &&
				है_अक्षर(mac->rd->alpha2[1]);

	अगर (qtnf_hwcap_is_set(hw_info, QLINK_HW_CAPAB_REG_UPDATE)) अणु
		wiphy->reg_notअगरier = qtnf_cfg80211_reg_notअगरier;

		अगर (mac->rd->alpha2[0] == '9' && mac->rd->alpha2[1] == '9') अणु
			wiphy->regulatory_flags |= REGULATORY_CUSTOM_REG |
				REGULATORY_STRICT_REG;
			wiphy_apply_custom_regulatory(wiphy, mac->rd);
		पूर्ण अन्यथा अगर (regकरोमुख्य_is_known) अणु
			wiphy->regulatory_flags |= REGULATORY_STRICT_REG;
		पूर्ण
	पूर्ण अन्यथा अणु
		wiphy->regulatory_flags |= REGULATORY_WIPHY_SELF_MANAGED;
	पूर्ण

	अगर (mac->macinfo.extended_capabilities_len) अणु
		wiphy->extended_capabilities =
			mac->macinfo.extended_capabilities;
		wiphy->extended_capabilities_mask =
			mac->macinfo.extended_capabilities_mask;
		wiphy->extended_capabilities_len =
			mac->macinfo.extended_capabilities_len;
	पूर्ण

	strlcpy(wiphy->fw_version, hw_info->fw_version,
		माप(wiphy->fw_version));
	wiphy->hw_version = hw_info->hw_version;

	ret = wiphy_रेजिस्टर(wiphy);
	अगर (ret < 0)
		जाओ out;

	अगर (wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED)
		ret = regulatory_set_wiphy_regd(wiphy, mac->rd);
	अन्यथा अगर (regकरोमुख्य_is_known)
		ret = regulatory_hपूर्णांक(wiphy, mac->rd->alpha2);

out:
	वापस ret;
पूर्ण

व्योम qtnf_netdev_upकरोwn(काष्ठा net_device *ndev, bool up)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(ndev);

	अगर (qtnf_cmd_send_upकरोwn_पूर्णांकf(vअगर, up))
		pr_err("failed to send %s command to VIF%u.%u\n",
		       up ? "UP" : "DOWN", vअगर->mac->macid, vअगर->vअगरid);
पूर्ण

व्योम qtnf_भव_पूर्णांकf_cleanup(काष्ठा net_device *ndev)
अणु
	काष्ठा qtnf_vअगर *vअगर = qtnf_netdev_get_priv(ndev);
	काष्ठा qtnf_wmac *mac = wiphy_priv(vअगर->wdev.wiphy);

	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_STATION)
		qtnf_disconnect(vअगर->wdev.wiphy, ndev,
				WLAN_REASON_DEAUTH_LEAVING);

	qtnf_scan_करोne(mac, true);
पूर्ण

व्योम qtnf_cfg80211_vअगर_reset(काष्ठा qtnf_vअगर *vअगर)
अणु
	अगर (vअगर->wdev.अगरtype == NL80211_IFTYPE_STATION)
		cfg80211_disconnected(vअगर->netdev, WLAN_REASON_DEAUTH_LEAVING,
				      शून्य, 0, 1, GFP_KERNEL);

	cfg80211_shutकरोwn_all_पूर्णांकerfaces(vअगर->wdev.wiphy);
पूर्ण

व्योम qtnf_band_init_rates(काष्ठा ieee80211_supported_band *band)
अणु
	चयन (band->band) अणु
	हाल NL80211_BAND_2GHZ:
		band->bitrates = qtnf_rates_2g;
		band->n_bitrates = ARRAY_SIZE(qtnf_rates_2g);
		अवरोध;
	हाल NL80211_BAND_5GHZ:
		band->bitrates = qtnf_rates_5g;
		band->n_bitrates = ARRAY_SIZE(qtnf_rates_5g);
		अवरोध;
	शेष:
		band->bitrates = शून्य;
		band->n_bitrates = 0;
		अवरोध;
	पूर्ण
पूर्ण
