<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This is the new netlink-based wireless configuration पूर्णांकerface.
 *
 * Copyright 2006-2010	Johannes Berg <johannes@sipsolutions.net>
 * Copyright 2013-2014  Intel Mobile Communications GmbH
 * Copyright 2015-2017	Intel Deutschland GmbH
 * Copyright (C) 2018-2021 Intel Corporation
 */

#समावेश <linux/अगर.h>
#समावेश <linux/module.h>
#समावेश <linux/err.h>
#समावेश <linux/slab.h>
#समावेश <linux/list.h>
#समावेश <linux/अगर_ether.h>
#समावेश <linux/ieee80211.h>
#समावेश <linux/nl80211.h>
#समावेश <linux/rtnetlink.h>
#समावेश <linux/netlink.h>
#समावेश <linux/nospec.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/अगर_vlan.h>
#समावेश <net/net_namespace.h>
#समावेश <net/genetlink.h>
#समावेश <net/cfg80211.h>
#समावेश <net/sock.h>
#समावेश <net/inet_connection_sock.h>
#समावेश "core.h"
#समावेश "nl80211.h"
#समावेश "reg.h"
#समावेश "rdev-ops.h"

अटल पूर्णांक nl80211_crypto_settings(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा genl_info *info,
				   काष्ठा cfg80211_crypto_settings *settings,
				   पूर्णांक cipher_limit);

/* the netlink family */
अटल काष्ठा genl_family nl80211_fam;

/* multicast groups */
क्रमागत nl80211_multicast_groups अणु
	NL80211_MCGRP_CONFIG,
	NL80211_MCGRP_SCAN,
	NL80211_MCGRP_REGULATORY,
	NL80211_MCGRP_MLME,
	NL80211_MCGRP_VENDOR,
	NL80211_MCGRP_न_अंक,
	NL80211_MCGRP_TESTMODE /* keep last - अगरdef! */
पूर्ण;

अटल स्थिर काष्ठा genl_multicast_group nl80211_mcgrps[] = अणु
	[NL80211_MCGRP_CONFIG] = अणु .name = NL80211_MULTICAST_GROUP_CONFIG पूर्ण,
	[NL80211_MCGRP_SCAN] = अणु .name = NL80211_MULTICAST_GROUP_SCAN पूर्ण,
	[NL80211_MCGRP_REGULATORY] = अणु .name = NL80211_MULTICAST_GROUP_REG पूर्ण,
	[NL80211_MCGRP_MLME] = अणु .name = NL80211_MULTICAST_GROUP_MLME पूर्ण,
	[NL80211_MCGRP_VENDOR] = अणु .name = NL80211_MULTICAST_GROUP_VENDOR पूर्ण,
	[NL80211_MCGRP_न_अंक] = अणु .name = NL80211_MULTICAST_GROUP_न_अंक पूर्ण,
#अगर_घोषित CONFIG_NL80211_TESTMODE
	[NL80211_MCGRP_TESTMODE] = अणु .name = NL80211_MULTICAST_GROUP_TESTMODE पूर्ण
#पूर्ण_अगर
पूर्ण;

/* वापसs ERR_PTR values */
अटल काष्ठा wireless_dev *
__cfg80211_wdev_from_attrs(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net *netns, काष्ठा nlattr **attrs)
अणु
	काष्ठा wireless_dev *result = शून्य;
	bool have_अगरidx = attrs[NL80211_ATTR_IFINDEX];
	bool have_wdev_id = attrs[NL80211_ATTR_WDEV];
	u64 wdev_id = 0;
	पूर्णांक wiphy_idx = -1;
	पूर्णांक अगरidx = -1;

	अगर (!have_अगरidx && !have_wdev_id)
		वापस ERR_PTR(-EINVAL);

	अगर (have_अगरidx)
		अगरidx = nla_get_u32(attrs[NL80211_ATTR_IFINDEX]);
	अगर (have_wdev_id) अणु
		wdev_id = nla_get_u64(attrs[NL80211_ATTR_WDEV]);
		wiphy_idx = wdev_id >> 32;
	पूर्ण

	अगर (rdev) अणु
		काष्ठा wireless_dev *wdev;

		lockdep_निश्चित_held(&rdev->wiphy.mtx);

		list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
			अगर (have_अगरidx && wdev->netdev &&
			    wdev->netdev->अगरindex == अगरidx) अणु
				result = wdev;
				अवरोध;
			पूर्ण
			अगर (have_wdev_id && wdev->identअगरier == (u32)wdev_id) अणु
				result = wdev;
				अवरोध;
			पूर्ण
		पूर्ण

		वापस result ?: ERR_PTR(-ENODEV);
	पूर्ण

	ASSERT_RTNL();

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		काष्ठा wireless_dev *wdev;

		अगर (wiphy_net(&rdev->wiphy) != netns)
			जारी;

		अगर (have_wdev_id && rdev->wiphy_idx != wiphy_idx)
			जारी;

		list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
			अगर (have_अगरidx && wdev->netdev &&
			    wdev->netdev->अगरindex == अगरidx) अणु
				result = wdev;
				अवरोध;
			पूर्ण
			अगर (have_wdev_id && wdev->identअगरier == (u32)wdev_id) अणु
				result = wdev;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (result)
			अवरोध;
	पूर्ण

	अगर (result)
		वापस result;
	वापस ERR_PTR(-ENODEV);
पूर्ण

अटल काष्ठा cfg80211_रेजिस्टरed_device *
__cfg80211_rdev_from_attrs(काष्ठा net *netns, काष्ठा nlattr **attrs)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = शून्य, *पंचांगp;
	काष्ठा net_device *netdev;

	ASSERT_RTNL();

	अगर (!attrs[NL80211_ATTR_WIPHY] &&
	    !attrs[NL80211_ATTR_IFINDEX] &&
	    !attrs[NL80211_ATTR_WDEV])
		वापस ERR_PTR(-EINVAL);

	अगर (attrs[NL80211_ATTR_WIPHY])
		rdev = cfg80211_rdev_by_wiphy_idx(
				nla_get_u32(attrs[NL80211_ATTR_WIPHY]));

	अगर (attrs[NL80211_ATTR_WDEV]) अणु
		u64 wdev_id = nla_get_u64(attrs[NL80211_ATTR_WDEV]);
		काष्ठा wireless_dev *wdev;
		bool found = false;

		पंचांगp = cfg80211_rdev_by_wiphy_idx(wdev_id >> 32);
		अगर (पंचांगp) अणु
			/* make sure wdev exists */
			list_क्रम_each_entry(wdev, &पंचांगp->wiphy.wdev_list, list) अणु
				अगर (wdev->identअगरier != (u32)wdev_id)
					जारी;
				found = true;
				अवरोध;
			पूर्ण

			अगर (!found)
				पंचांगp = शून्य;

			अगर (rdev && पंचांगp != rdev)
				वापस ERR_PTR(-EINVAL);
			rdev = पंचांगp;
		पूर्ण
	पूर्ण

	अगर (attrs[NL80211_ATTR_IFINDEX]) अणु
		पूर्णांक अगरindex = nla_get_u32(attrs[NL80211_ATTR_IFINDEX]);

		netdev = __dev_get_by_index(netns, अगरindex);
		अगर (netdev) अणु
			अगर (netdev->ieee80211_ptr)
				पंचांगp = wiphy_to_rdev(
					netdev->ieee80211_ptr->wiphy);
			अन्यथा
				पंचांगp = शून्य;

			/* not wireless device -- वापस error */
			अगर (!पंचांगp)
				वापस ERR_PTR(-EINVAL);

			/* mismatch -- वापस error */
			अगर (rdev && पंचांगp != rdev)
				वापस ERR_PTR(-EINVAL);

			rdev = पंचांगp;
		पूर्ण
	पूर्ण

	अगर (!rdev)
		वापस ERR_PTR(-ENODEV);

	अगर (netns != wiphy_net(&rdev->wiphy))
		वापस ERR_PTR(-ENODEV);

	वापस rdev;
पूर्ण

/*
 * This function वापसs a poपूर्णांकer to the driver
 * that the genl_info item that is passed refers to.
 *
 * The result of this can be a PTR_ERR and hence must
 * be checked with IS_ERR() क्रम errors.
 */
अटल काष्ठा cfg80211_रेजिस्टरed_device *
cfg80211_get_dev_from_info(काष्ठा net *netns, काष्ठा genl_info *info)
अणु
	वापस __cfg80211_rdev_from_attrs(netns, info->attrs);
पूर्ण

अटल पूर्णांक validate_beacon_head(स्थिर काष्ठा nlattr *attr,
				काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर u8 *data = nla_data(attr);
	अचिन्हित पूर्णांक len = nla_len(attr);
	स्थिर काष्ठा element *elem;
	स्थिर काष्ठा ieee80211_mgmt *mgmt = (व्योम *)data;
	अचिन्हित पूर्णांक fixedlen, hdrlen;
	bool s1g_bcn;

	अगर (len < दुरत्वend(typeof(*mgmt), frame_control))
		जाओ err;

	s1g_bcn = ieee80211_is_s1g_beacon(mgmt->frame_control);
	अगर (s1g_bcn) अणु
		fixedlen = दुरत्व(काष्ठा ieee80211_ext,
				    u.s1g_beacon.variable);
		hdrlen = दुरत्व(काष्ठा ieee80211_ext, u.s1g_beacon);
	पूर्ण अन्यथा अणु
		fixedlen = दुरत्व(काष्ठा ieee80211_mgmt,
				    u.beacon.variable);
		hdrlen = दुरत्व(काष्ठा ieee80211_mgmt, u.beacon);
	पूर्ण

	अगर (len < fixedlen)
		जाओ err;

	अगर (ieee80211_hdrlen(mgmt->frame_control) != hdrlen)
		जाओ err;

	data += fixedlen;
	len -= fixedlen;

	क्रम_each_element(elem, data, len) अणु
		/* nothing */
	पूर्ण

	अगर (क्रम_each_element_completed(elem, data, len))
		वापस 0;

err:
	NL_SET_ERR_MSG_ATTR(extack, attr, "malformed beacon head");
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक validate_ie_attr(स्थिर काष्ठा nlattr *attr,
			    काष्ठा netlink_ext_ack *extack)
अणु
	स्थिर u8 *data = nla_data(attr);
	अचिन्हित पूर्णांक len = nla_len(attr);
	स्थिर काष्ठा element *elem;

	क्रम_each_element(elem, data, len) अणु
		/* nothing */
	पूर्ण

	अगर (क्रम_each_element_completed(elem, data, len))
		वापस 0;

	NL_SET_ERR_MSG_ATTR(extack, attr, "malformed information elements");
	वापस -EINVAL;
पूर्ण

/* policy क्रम the attributes */
अटल स्थिर काष्ठा nla_policy nl80211_policy[NUM_NL80211_ATTR];

अटल स्थिर काष्ठा nla_policy
nl80211_fपंचांग_responder_policy[NL80211_FTM_RESP_ATTR_MAX + 1] = अणु
	[NL80211_FTM_RESP_ATTR_ENABLED] = अणु .type = NLA_FLAG, पूर्ण,
	[NL80211_FTM_RESP_ATTR_LCI] = अणु .type = NLA_BINARY,
					.len = U8_MAX पूर्ण,
	[NL80211_FTM_RESP_ATTR_CIVICLOC] = अणु .type = NLA_BINARY,
					     .len = U8_MAX पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_pmsr_fपंचांग_req_attr_policy[NL80211_PMSR_FTM_REQ_ATTR_MAX + 1] = अणु
	[NL80211_PMSR_FTM_REQ_ATTR_ASAP] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_PMSR_FTM_REQ_ATTR_PREAMBLE] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_PMSR_FTM_REQ_ATTR_NUM_BURSTS_EXP] =
		NLA_POLICY_MAX(NLA_U8, 15),
	[NL80211_PMSR_FTM_REQ_ATTR_BURST_PERIOD] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_PMSR_FTM_REQ_ATTR_BURST_DURATION] =
		NLA_POLICY_MAX(NLA_U8, 15),
	[NL80211_PMSR_FTM_REQ_ATTR_FTMS_PER_BURST] =
		NLA_POLICY_MAX(NLA_U8, 31),
	[NL80211_PMSR_FTM_REQ_ATTR_NUM_FTMR_RETRIES] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_PMSR_FTM_REQ_ATTR_REQUEST_LCI] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_PMSR_FTM_REQ_ATTR_REQUEST_CIVICLOC] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_PMSR_FTM_REQ_ATTR_TRIGGER_BASED] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_PMSR_FTM_REQ_ATTR_NON_TRIGGER_BASED] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_PMSR_FTM_REQ_ATTR_LMR_FEEDBACK] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_pmsr_req_data_policy[NL80211_PMSR_TYPE_MAX + 1] = अणु
	[NL80211_PMSR_TYPE_FTM] =
		NLA_POLICY_NESTED(nl80211_pmsr_fपंचांग_req_attr_policy),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_pmsr_req_attr_policy[NL80211_PMSR_REQ_ATTR_MAX + 1] = अणु
	[NL80211_PMSR_REQ_ATTR_DATA] =
		NLA_POLICY_NESTED(nl80211_pmsr_req_data_policy),
	[NL80211_PMSR_REQ_ATTR_GET_AP_TSF] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_psmr_peer_attr_policy[NL80211_PMSR_PEER_ATTR_MAX + 1] = अणु
	[NL80211_PMSR_PEER_ATTR_ADDR] = NLA_POLICY_ETH_ADDR,
	[NL80211_PMSR_PEER_ATTR_CHAN] = NLA_POLICY_NESTED(nl80211_policy),
	[NL80211_PMSR_PEER_ATTR_REQ] =
		NLA_POLICY_NESTED(nl80211_pmsr_req_attr_policy),
	[NL80211_PMSR_PEER_ATTR_RESP] = अणु .type = NLA_REJECT पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_pmsr_attr_policy[NL80211_PMSR_ATTR_MAX + 1] = अणु
	[NL80211_PMSR_ATTR_MAX_PEERS] = अणु .type = NLA_REJECT पूर्ण,
	[NL80211_PMSR_ATTR_REPORT_AP_TSF] = अणु .type = NLA_REJECT पूर्ण,
	[NL80211_PMSR_ATTR_RANDOMIZE_MAC_ADDR] = अणु .type = NLA_REJECT पूर्ण,
	[NL80211_PMSR_ATTR_TYPE_CAPA] = अणु .type = NLA_REJECT पूर्ण,
	[NL80211_PMSR_ATTR_PEERS] =
		NLA_POLICY_NESTED_ARRAY(nl80211_psmr_peer_attr_policy),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
he_obss_pd_policy[NL80211_HE_OBSS_PD_ATTR_MAX + 1] = अणु
	[NL80211_HE_OBSS_PD_ATTR_MIN_OFFSET] =
		NLA_POLICY_RANGE(NLA_U8, 1, 20),
	[NL80211_HE_OBSS_PD_ATTR_MAX_OFFSET] =
		NLA_POLICY_RANGE(NLA_U8, 1, 20),
	[NL80211_HE_OBSS_PD_ATTR_NON_SRG_MAX_OFFSET] =
		NLA_POLICY_RANGE(NLA_U8, 1, 20),
	[NL80211_HE_OBSS_PD_ATTR_BSS_COLOR_BITMAP] =
		NLA_POLICY_EXACT_LEN(8),
	[NL80211_HE_OBSS_PD_ATTR_PARTIAL_BSSID_BITMAP] =
		NLA_POLICY_EXACT_LEN(8),
	[NL80211_HE_OBSS_PD_ATTR_SR_CTRL] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
he_bss_color_policy[NL80211_HE_BSS_COLOR_ATTR_MAX + 1] = अणु
	[NL80211_HE_BSS_COLOR_ATTR_COLOR] = NLA_POLICY_RANGE(NLA_U8, 1, 63),
	[NL80211_HE_BSS_COLOR_ATTR_DISABLED] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_HE_BSS_COLOR_ATTR_PARTIAL] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy nl80211_txattr_policy[NL80211_TXRATE_MAX + 1] = अणु
	[NL80211_TXRATE_LEGACY] = अणु .type = NLA_BINARY,
				    .len = NL80211_MAX_SUPP_RATES पूर्ण,
	[NL80211_TXRATE_HT] = अणु .type = NLA_BINARY,
				.len = NL80211_MAX_SUPP_HT_RATES पूर्ण,
	[NL80211_TXRATE_VHT] = NLA_POLICY_EXACT_LEN_WARN(माप(काष्ठा nl80211_txrate_vht)),
	[NL80211_TXRATE_GI] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_TXRATE_HE] = NLA_POLICY_EXACT_LEN(माप(काष्ठा nl80211_txrate_he)),
	[NL80211_TXRATE_HE_GI] =  NLA_POLICY_RANGE(NLA_U8,
						   NL80211_RATE_INFO_HE_GI_0_8,
						   NL80211_RATE_INFO_HE_GI_3_2),
	[NL80211_TXRATE_HE_LTF] = NLA_POLICY_RANGE(NLA_U8,
						   NL80211_RATE_INFO_HE_1XLTF,
						   NL80211_RATE_INFO_HE_4XLTF),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_tid_config_attr_policy[NL80211_TID_CONFIG_ATTR_MAX + 1] = अणु
	[NL80211_TID_CONFIG_ATTR_VIF_SUPP] = अणु .type = NLA_U64 पूर्ण,
	[NL80211_TID_CONFIG_ATTR_PEER_SUPP] = अणु .type = NLA_U64 पूर्ण,
	[NL80211_TID_CONFIG_ATTR_OVERRIDE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_TID_CONFIG_ATTR_TIDS] = NLA_POLICY_RANGE(NLA_U16, 1, 0xff),
	[NL80211_TID_CONFIG_ATTR_NOACK] =
			NLA_POLICY_MAX(NLA_U8, NL80211_TID_CONFIG_DISABLE),
	[NL80211_TID_CONFIG_ATTR_RETRY_SHORT] = NLA_POLICY_MIN(NLA_U8, 1),
	[NL80211_TID_CONFIG_ATTR_RETRY_LONG] = NLA_POLICY_MIN(NLA_U8, 1),
	[NL80211_TID_CONFIG_ATTR_AMPDU_CTRL] =
			NLA_POLICY_MAX(NLA_U8, NL80211_TID_CONFIG_DISABLE),
	[NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL] =
			NLA_POLICY_MAX(NLA_U8, NL80211_TID_CONFIG_DISABLE),
	[NL80211_TID_CONFIG_ATTR_AMSDU_CTRL] =
			NLA_POLICY_MAX(NLA_U8, NL80211_TID_CONFIG_DISABLE),
	[NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE] =
			NLA_POLICY_MAX(NLA_U8, NL80211_TX_RATE_FIXED),
	[NL80211_TID_CONFIG_ATTR_TX_RATE] =
			NLA_POLICY_NESTED(nl80211_txattr_policy),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_fils_discovery_policy[NL80211_FILS_DISCOVERY_ATTR_MAX + 1] = अणु
	[NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_न्यून] = NLA_POLICY_MAX(NLA_U32, 10000),
	[NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_उच्च] = NLA_POLICY_MAX(NLA_U32, 10000),
	[NL80211_FILS_DISCOVERY_ATTR_TMPL] =
			NLA_POLICY_RANGE(NLA_BINARY,
					 NL80211_FILS_DISCOVERY_TMPL_MIN_LEN,
					 IEEE80211_MAX_DATA_LEN),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_unsol_bcast_probe_resp_policy[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_MAX + 1] = अणु
	[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_INT] = NLA_POLICY_MAX(NLA_U32, 20),
	[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_TMPL] = अणु .type = NLA_BINARY,
						       .len = IEEE80211_MAX_DATA_LEN पूर्ण
पूर्ण;

अटल स्थिर काष्ठा nla_policy
sar_specs_policy[NL80211_SAR_ATTR_SPECS_MAX + 1] = अणु
	[NL80211_SAR_ATTR_SPECS_POWER] = अणु .type = NLA_S32 पूर्ण,
	[NL80211_SAR_ATTR_SPECS_RANGE_INDEX] = अणु.type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
sar_policy[NL80211_SAR_ATTR_MAX + 1] = अणु
	[NL80211_SAR_ATTR_TYPE] = NLA_POLICY_MAX(NLA_U32, NUM_NL80211_SAR_TYPE),
	[NL80211_SAR_ATTR_SPECS] = NLA_POLICY_NESTED_ARRAY(sar_specs_policy),
पूर्ण;

अटल स्थिर काष्ठा nla_policy nl80211_policy[NUM_NL80211_ATTR] = अणु
	[0] = अणु .strict_start_type = NL80211_ATTR_HE_OBSS_PD पूर्ण,
	[NL80211_ATTR_WIPHY] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_WIPHY_NAME] = अणु .type = NLA_NUL_STRING,
				      .len = 20-1 पूर्ण,
	[NL80211_ATTR_WIPHY_TXQ_PARAMS] = अणु .type = NLA_NESTED पूर्ण,

	[NL80211_ATTR_WIPHY_FREQ] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_WIPHY_CHANNEL_TYPE] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_WIPHY_EDMG_CHANNELS] = NLA_POLICY_RANGE(NLA_U8,
						NL80211_EDMG_CHANNELS_MIN,
						NL80211_EDMG_CHANNELS_MAX),
	[NL80211_ATTR_WIPHY_EDMG_BW_CONFIG] = NLA_POLICY_RANGE(NLA_U8,
						NL80211_EDMG_BW_CONFIG_MIN,
						NL80211_EDMG_BW_CONFIG_MAX),

	[NL80211_ATTR_CHANNEL_WIDTH] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_CENTER_FREQ1] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_CENTER_FREQ1_OFFSET] = NLA_POLICY_RANGE(NLA_U32, 0, 999),
	[NL80211_ATTR_CENTER_FREQ2] = अणु .type = NLA_U32 पूर्ण,

	[NL80211_ATTR_WIPHY_RETRY_SHORT] = NLA_POLICY_MIN(NLA_U8, 1),
	[NL80211_ATTR_WIPHY_RETRY_LONG] = NLA_POLICY_MIN(NLA_U8, 1),
	[NL80211_ATTR_WIPHY_FRAG_THRESHOLD] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_WIPHY_RTS_THRESHOLD] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_WIPHY_COVERAGE_CLASS] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_WIPHY_DYN_ACK] = अणु .type = NLA_FLAG पूर्ण,

	[NL80211_ATTR_IFTYPE] = NLA_POLICY_MAX(NLA_U32, NL80211_IFTYPE_MAX),
	[NL80211_ATTR_IFINDEX] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_IFNAME] = अणु .type = NLA_NUL_STRING, .len = IFNAMSIZ-1 पूर्ण,

	[NL80211_ATTR_MAC] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),
	[NL80211_ATTR_PREV_BSSID] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),

	[NL80211_ATTR_KEY] = अणु .type = NLA_NESTED, पूर्ण,
	[NL80211_ATTR_KEY_DATA] = अणु .type = NLA_BINARY,
				    .len = WLAN_MAX_KEY_LEN पूर्ण,
	[NL80211_ATTR_KEY_IDX] = NLA_POLICY_MAX(NLA_U8, 7),
	[NL80211_ATTR_KEY_CIPHER] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_KEY_DEFAULT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_KEY_SEQ] = अणु .type = NLA_BINARY, .len = 16 पूर्ण,
	[NL80211_ATTR_KEY_TYPE] =
		NLA_POLICY_MAX(NLA_U32, NUM_NL80211_KEYTYPES),

	[NL80211_ATTR_BEACON_INTERVAL] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_DTIM_PERIOD] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_BEACON_HEAD] =
		NLA_POLICY_VALIDATE_FN(NLA_BINARY, validate_beacon_head,
				       IEEE80211_MAX_DATA_LEN),
	[NL80211_ATTR_BEACON_TAIL] =
		NLA_POLICY_VALIDATE_FN(NLA_BINARY, validate_ie_attr,
				       IEEE80211_MAX_DATA_LEN),
	[NL80211_ATTR_STA_AID] =
		NLA_POLICY_RANGE(NLA_U16, 1, IEEE80211_MAX_AID),
	[NL80211_ATTR_STA_FLAGS] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_STA_LISTEN_INTERVAL] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_STA_SUPPORTED_RATES] = अणु .type = NLA_BINARY,
					       .len = NL80211_MAX_SUPP_RATES पूर्ण,
	[NL80211_ATTR_STA_PLINK_ACTION] =
		NLA_POLICY_MAX(NLA_U8, NUM_NL80211_PLINK_ACTIONS - 1),
	[NL80211_ATTR_STA_TX_POWER_SETTING] =
		NLA_POLICY_RANGE(NLA_U8,
				 NL80211_TX_POWER_AUTOMATIC,
				 NL80211_TX_POWER_FIXED),
	[NL80211_ATTR_STA_TX_POWER] = अणु .type = NLA_S16 पूर्ण,
	[NL80211_ATTR_STA_VLAN] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_MNTR_FLAGS] = अणु /* NLA_NESTED can't be empty */ पूर्ण,
	[NL80211_ATTR_MESH_ID] = अणु .type = NLA_BINARY,
				   .len = IEEE80211_MAX_MESH_ID_LEN पूर्ण,
	[NL80211_ATTR_MPATH_NEXT_HOP] = NLA_POLICY_ETH_ADDR_COMPAT,

	[NL80211_ATTR_REG_ALPHA2] = अणु .type = NLA_STRING, .len = 2 पूर्ण,
	[NL80211_ATTR_REG_RULES] = अणु .type = NLA_NESTED पूर्ण,

	[NL80211_ATTR_BSS_CTS_PROT] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_BSS_SHORT_PREAMBLE] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_BSS_SHORT_SLOT_TIME] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_BSS_BASIC_RATES] = अणु .type = NLA_BINARY,
					   .len = NL80211_MAX_SUPP_RATES पूर्ण,
	[NL80211_ATTR_BSS_HT_OPMODE] = अणु .type = NLA_U16 पूर्ण,

	[NL80211_ATTR_MESH_CONFIG] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_SUPPORT_MESH_AUTH] = अणु .type = NLA_FLAG पूर्ण,

	[NL80211_ATTR_HT_CAPABILITY] = NLA_POLICY_EXACT_LEN_WARN(NL80211_HT_CAPABILITY_LEN),

	[NL80211_ATTR_MGMT_SUBTYPE] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_IE] = NLA_POLICY_VALIDATE_FN(NLA_BINARY,
						   validate_ie_attr,
						   IEEE80211_MAX_DATA_LEN),
	[NL80211_ATTR_SCAN_FREQUENCIES] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_SCAN_SSIDS] = अणु .type = NLA_NESTED पूर्ण,

	[NL80211_ATTR_SSID] = अणु .type = NLA_BINARY,
				.len = IEEE80211_MAX_SSID_LEN पूर्ण,
	[NL80211_ATTR_AUTH_TYPE] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_REASON_CODE] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_FREQ_FIXED] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_TIMED_OUT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_USE_MFP] = NLA_POLICY_RANGE(NLA_U32,
						  NL80211_MFP_NO,
						  NL80211_MFP_OPTIONAL),
	[NL80211_ATTR_STA_FLAGS2] = अणु
		.len = माप(काष्ठा nl80211_sta_flag_update),
	पूर्ण,
	[NL80211_ATTR_CONTROL_PORT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_CONTROL_PORT_ETHERTYPE] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_CONTROL_PORT_OVER_NL80211] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_PRIVACY] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_STATUS_CODE] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_CIPHER_SUITE_GROUP] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_WPA_VERSIONS] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_PID] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_4ADDR] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_PMKID] = NLA_POLICY_EXACT_LEN_WARN(WLAN_PMKID_LEN),
	[NL80211_ATTR_DURATION] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_COOKIE] = अणु .type = NLA_U64 पूर्ण,
	[NL80211_ATTR_TX_RATES] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_FRAME] = अणु .type = NLA_BINARY,
				 .len = IEEE80211_MAX_DATA_LEN पूर्ण,
	[NL80211_ATTR_FRAME_MATCH] = अणु .type = NLA_BINARY, पूर्ण,
	[NL80211_ATTR_PS_STATE] = NLA_POLICY_RANGE(NLA_U32,
						   NL80211_PS_DISABLED,
						   NL80211_PS_ENABLED),
	[NL80211_ATTR_CQM] = अणु .type = NLA_NESTED, पूर्ण,
	[NL80211_ATTR_LOCAL_STATE_CHANGE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_AP_ISOLATE] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_WIPHY_TX_POWER_SETTING] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_WIPHY_TX_POWER_LEVEL] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_FRAME_TYPE] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_WIPHY_ANTENNA_TX] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_WIPHY_ANTENNA_RX] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_MCAST_RATE] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_OFFCHANNEL_TX_OK] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_KEY_DEFAULT_TYPES] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_WOWLAN_TRIGGERS] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_STA_PLINK_STATE] =
		NLA_POLICY_MAX(NLA_U8, NUM_NL80211_PLINK_STATES - 1),
	[NL80211_ATTR_MEASUREMENT_DURATION] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_MEASUREMENT_DURATION_MANDATORY] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_MESH_PEER_AID] =
		NLA_POLICY_RANGE(NLA_U16, 1, IEEE80211_MAX_AID),
	[NL80211_ATTR_SCHED_SCAN_INTERVAL] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_REKEY_DATA] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_SCAN_SUPP_RATES] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_HIDDEN_SSID] =
		NLA_POLICY_RANGE(NLA_U32,
				 NL80211_HIDDEN_SSID_NOT_IN_USE,
				 NL80211_HIDDEN_SSID_ZERO_CONTENTS),
	[NL80211_ATTR_IE_PROBE_RESP] =
		NLA_POLICY_VALIDATE_FN(NLA_BINARY, validate_ie_attr,
				       IEEE80211_MAX_DATA_LEN),
	[NL80211_ATTR_IE_ASSOC_RESP] =
		NLA_POLICY_VALIDATE_FN(NLA_BINARY, validate_ie_attr,
				       IEEE80211_MAX_DATA_LEN),
	[NL80211_ATTR_ROAM_SUPPORT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_SCHED_SCAN_MATCH] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_TX_NO_CCK_RATE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_TDLS_ACTION] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_TDLS_DIALOG_TOKEN] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_TDLS_OPERATION] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_TDLS_SUPPORT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_TDLS_EXTERNAL_SETUP] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_TDLS_INITIATOR] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_DONT_WAIT_FOR_ACK] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_PROBE_RESP] = अणु .type = NLA_BINARY,
				      .len = IEEE80211_MAX_DATA_LEN पूर्ण,
	[NL80211_ATTR_DFS_REGION] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_DISABLE_HT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_HT_CAPABILITY_MASK] = अणु
		.len = NL80211_HT_CAPABILITY_LEN
	पूर्ण,
	[NL80211_ATTR_NOACK_MAP] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_INACTIVITY_TIMEOUT] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_BG_SCAN_PERIOD] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_WDEV] = अणु .type = NLA_U64 पूर्ण,
	[NL80211_ATTR_USER_REG_HINT_TYPE] = अणु .type = NLA_U32 पूर्ण,

	/* need to include at least Auth Transaction and Status Code */
	[NL80211_ATTR_AUTH_DATA] = NLA_POLICY_MIN_LEN(4),

	[NL80211_ATTR_VHT_CAPABILITY] = NLA_POLICY_EXACT_LEN_WARN(NL80211_VHT_CAPABILITY_LEN),
	[NL80211_ATTR_SCAN_FLAGS] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_P2P_CTWINDOW] = NLA_POLICY_MAX(NLA_U8, 127),
	[NL80211_ATTR_P2P_OPPPS] = NLA_POLICY_MAX(NLA_U8, 1),
	[NL80211_ATTR_LOCAL_MESH_POWER_MODE] =
		NLA_POLICY_RANGE(NLA_U32,
				 NL80211_MESH_POWER_UNKNOWN + 1,
				 NL80211_MESH_POWER_MAX),
	[NL80211_ATTR_ACL_POLICY] = अणु. type = NLA_U32 पूर्ण,
	[NL80211_ATTR_MAC_ADDRS] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_STA_CAPABILITY] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_STA_EXT_CAPABILITY] = अणु .type = NLA_BINARY, पूर्ण,
	[NL80211_ATTR_SPLIT_WIPHY_DUMP] = अणु .type = NLA_FLAG, पूर्ण,
	[NL80211_ATTR_DISABLE_VHT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_VHT_CAPABILITY_MASK] = अणु
		.len = NL80211_VHT_CAPABILITY_LEN,
	पूर्ण,
	[NL80211_ATTR_MDID] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_IE_RIC] = अणु .type = NLA_BINARY,
				  .len = IEEE80211_MAX_DATA_LEN पूर्ण,
	[NL80211_ATTR_CRIT_PROT_ID] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_MAX_CRIT_PROT_DURATION] =
		NLA_POLICY_MAX(NLA_U16, NL80211_CRIT_PROTO_MAX_DURATION),
	[NL80211_ATTR_PEER_AID] =
		NLA_POLICY_RANGE(NLA_U16, 1, IEEE80211_MAX_AID),
	[NL80211_ATTR_CH_SWITCH_COUNT] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_CH_SWITCH_BLOCK_TX] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_CSA_IES] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_CNTDWN_OFFS_BEACON] = अणु .type = NLA_BINARY पूर्ण,
	[NL80211_ATTR_CNTDWN_OFFS_PRESP] = अणु .type = NLA_BINARY पूर्ण,
	[NL80211_ATTR_STA_SUPPORTED_CHANNELS] = NLA_POLICY_MIN_LEN(2),
	/*
	 * The value of the Length field of the Supported Operating
	 * Classes element is between 2 and 253.
	 */
	[NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES] =
		NLA_POLICY_RANGE(NLA_BINARY, 2, 253),
	[NL80211_ATTR_HANDLE_DFS] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_OPMODE_NOTIF] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_VENDOR_ID] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_VENDOR_SUBCMD] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_VENDOR_DATA] = अणु .type = NLA_BINARY पूर्ण,
	[NL80211_ATTR_QOS_MAP] = NLA_POLICY_RANGE(NLA_BINARY,
						  IEEE80211_QOS_MAP_LEN_MIN,
						  IEEE80211_QOS_MAP_LEN_MAX),
	[NL80211_ATTR_MAC_HINT] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),
	[NL80211_ATTR_WIPHY_FREQ_HINT] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_TDLS_PEER_CAPABILITY] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_SOCKET_OWNER] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_CSA_C_OFFSETS_TX] = अणु .type = NLA_BINARY पूर्ण,
	[NL80211_ATTR_USE_RRM] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_TSID] = NLA_POLICY_MAX(NLA_U8, IEEE80211_NUM_TIDS - 1),
	[NL80211_ATTR_USER_PRIO] =
		NLA_POLICY_MAX(NLA_U8, IEEE80211_NUM_UPS - 1),
	[NL80211_ATTR_ADMITTED_TIME] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_SMPS_MODE] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_OPER_CLASS] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_ATTR_MAC_MASK] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),
	[NL80211_ATTR_WIPHY_SELF_MANAGED_REG] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_NETNS_FD] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_SCHED_SCAN_DELAY] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_REG_INDOOR] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_PBSS] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_BSS_SELECT] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_STA_SUPPORT_P2P_PS] =
		NLA_POLICY_MAX(NLA_U8, NUM_NL80211_P2P_PS_STATUS - 1),
	[NL80211_ATTR_MU_MIMO_GROUP_DATA] = अणु
		.len = VHT_MUMIMO_GROUPS_DATA_LEN
	पूर्ण,
	[NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),
	[NL80211_ATTR_न_अंक_MASTER_PREF] = NLA_POLICY_MIN(NLA_U8, 1),
	[NL80211_ATTR_BANDS] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_न_अंक_FUNC] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_FILS_KEK] = अणु .type = NLA_BINARY,
				    .len = FILS_MAX_KEK_LEN पूर्ण,
	[NL80211_ATTR_FILS_NONCES] = NLA_POLICY_EXACT_LEN_WARN(2 * FILS_NONCE_LEN),
	[NL80211_ATTR_MULTICAST_TO_UNICAST_ENABLED] = अणु .type = NLA_FLAG, पूर्ण,
	[NL80211_ATTR_BSSID] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),
	[NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI] = अणु .type = NLA_S8 पूर्ण,
	[NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST] = अणु
		.len = माप(काष्ठा nl80211_bss_select_rssi_adjust)
	पूर्ण,
	[NL80211_ATTR_TIMEOUT_REASON] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_FILS_ERP_USERNAME] = अणु .type = NLA_BINARY,
					     .len = FILS_ERP_MAX_USERNAME_LEN पूर्ण,
	[NL80211_ATTR_FILS_ERP_REALM] = अणु .type = NLA_BINARY,
					  .len = FILS_ERP_MAX_REALM_LEN पूर्ण,
	[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_ATTR_FILS_ERP_RRK] = अणु .type = NLA_BINARY,
					.len = FILS_ERP_MAX_RRK_LEN पूर्ण,
	[NL80211_ATTR_FILS_CACHE_ID] = NLA_POLICY_EXACT_LEN_WARN(2),
	[NL80211_ATTR_PMK] = अणु .type = NLA_BINARY, .len = PMK_MAX_LEN पूर्ण,
	[NL80211_ATTR_PMKR0_NAME] = NLA_POLICY_EXACT_LEN(WLAN_PMK_NAME_LEN),
	[NL80211_ATTR_SCHED_SCAN_MULTI] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_EXTERNAL_AUTH_SUPPORT] = अणु .type = NLA_FLAG पूर्ण,

	[NL80211_ATTR_TXQ_LIMIT] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_TXQ_MEMORY_LIMIT] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_TXQ_QUANTUM] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_HE_CAPABILITY] =
		NLA_POLICY_RANGE(NLA_BINARY,
				 NL80211_HE_MIN_CAPABILITY_LEN,
				 NL80211_HE_MAX_CAPABILITY_LEN),
	[NL80211_ATTR_FTM_RESPONDER] =
		NLA_POLICY_NESTED(nl80211_fपंचांग_responder_policy),
	[NL80211_ATTR_TIMEOUT] = NLA_POLICY_MIN(NLA_U32, 1),
	[NL80211_ATTR_PEER_MEASUREMENTS] =
		NLA_POLICY_NESTED(nl80211_pmsr_attr_policy),
	[NL80211_ATTR_AIRTIME_WEIGHT] = NLA_POLICY_MIN(NLA_U16, 1),
	[NL80211_ATTR_SAE_PASSWORD] = अणु .type = NLA_BINARY,
					.len = SAE_PASSWORD_MAX_LEN पूर्ण,
	[NL80211_ATTR_TWT_RESPONDER] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_HE_OBSS_PD] = NLA_POLICY_NESTED(he_obss_pd_policy),
	[NL80211_ATTR_VLAN_ID] = NLA_POLICY_RANGE(NLA_U16, 1, VLAN_N_VID - 2),
	[NL80211_ATTR_HE_BSS_COLOR] = NLA_POLICY_NESTED(he_bss_color_policy),
	[NL80211_ATTR_TID_CONFIG] =
		NLA_POLICY_NESTED_ARRAY(nl80211_tid_config_attr_policy),
	[NL80211_ATTR_CONTROL_PORT_NO_PREAUTH] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_PMK_LIFETIME] = NLA_POLICY_MIN(NLA_U32, 1),
	[NL80211_ATTR_PMK_REAUTH_THRESHOLD] = NLA_POLICY_RANGE(NLA_U8, 1, 100),
	[NL80211_ATTR_RECEIVE_MULTICAST] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_ATTR_WIPHY_FREQ_OFFSET] = NLA_POLICY_RANGE(NLA_U32, 0, 999),
	[NL80211_ATTR_SCAN_FREQ_KHZ] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_ATTR_HE_6GHZ_CAPABILITY] =
		NLA_POLICY_EXACT_LEN(माप(काष्ठा ieee80211_he_6ghz_capa)),
	[NL80211_ATTR_FILS_DISCOVERY] =
		NLA_POLICY_NESTED(nl80211_fils_discovery_policy),
	[NL80211_ATTR_UNSOL_BCAST_PROBE_RESP] =
		NLA_POLICY_NESTED(nl80211_unsol_bcast_probe_resp_policy),
	[NL80211_ATTR_S1G_CAPABILITY] =
		NLA_POLICY_EXACT_LEN(IEEE80211_S1G_CAPABILITY_LEN),
	[NL80211_ATTR_S1G_CAPABILITY_MASK] =
		NLA_POLICY_EXACT_LEN(IEEE80211_S1G_CAPABILITY_LEN),
	[NL80211_ATTR_SAE_PWE] =
		NLA_POLICY_RANGE(NLA_U8, NL80211_SAE_PWE_HUNT_AND_PECK,
				 NL80211_SAE_PWE_BOTH),
	[NL80211_ATTR_RECONNECT_REQUESTED] = अणु .type = NLA_REJECT पूर्ण,
	[NL80211_ATTR_SAR_SPEC] = NLA_POLICY_NESTED(sar_policy),
	[NL80211_ATTR_DISABLE_HE] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

/* policy क्रम the key attributes */
अटल स्थिर काष्ठा nla_policy nl80211_key_policy[NL80211_KEY_MAX + 1] = अणु
	[NL80211_KEY_DATA] = अणु .type = NLA_BINARY, .len = WLAN_MAX_KEY_LEN पूर्ण,
	[NL80211_KEY_IDX] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_KEY_CIPHER] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_KEY_SEQ] = अणु .type = NLA_BINARY, .len = 16 पूर्ण,
	[NL80211_KEY_DEFAULT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_KEY_DEFAULT_MGMT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_KEY_TYPE] = NLA_POLICY_MAX(NLA_U32, NUM_NL80211_KEYTYPES - 1),
	[NL80211_KEY_DEFAULT_TYPES] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_KEY_MODE] = NLA_POLICY_RANGE(NLA_U8, 0, NL80211_KEY_SET_TX),
पूर्ण;

/* policy क्रम the key शेष flags */
अटल स्थिर काष्ठा nla_policy
nl80211_key_शेष_policy[NUM_NL80211_KEY_DEFAULT_TYPES] = अणु
	[NL80211_KEY_DEFAULT_TYPE_UNICAST] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_KEY_DEFAULT_TYPE_MULTICAST] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

#अगर_घोषित CONFIG_PM
/* policy क्रम WoWLAN attributes */
अटल स्थिर काष्ठा nla_policy
nl80211_wowlan_policy[NUM_NL80211_WOWLAN_TRIG] = अणु
	[NL80211_WOWLAN_TRIG_ANY] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_WOWLAN_TRIG_DISCONNECT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_WOWLAN_TRIG_MAGIC_PKT] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_WOWLAN_TRIG_PKT_PATTERN] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_WOWLAN_TRIG_EAP_IDENT_REQUEST] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_WOWLAN_TRIG_4WAY_HANDSHAKE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_WOWLAN_TRIG_RFKILL_RELEASE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_WOWLAN_TRIG_TCP_CONNECTION] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_WOWLAN_TRIG_NET_DETECT] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_wowlan_tcp_policy[NUM_NL80211_WOWLAN_TCP] = अणु
	[NL80211_WOWLAN_TCP_SRC_IPV4] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_WOWLAN_TCP_DST_IPV4] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_WOWLAN_TCP_DST_MAC] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),
	[NL80211_WOWLAN_TCP_SRC_PORT] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_WOWLAN_TCP_DST_PORT] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_WOWLAN_TCP_DATA_PAYLOAD] = NLA_POLICY_MIN_LEN(1),
	[NL80211_WOWLAN_TCP_DATA_PAYLOAD_SEQ] = अणु
		.len = माप(काष्ठा nl80211_wowlan_tcp_data_seq)
	पूर्ण,
	[NL80211_WOWLAN_TCP_DATA_PAYLOAD_TOKEN] = अणु
		.len = माप(काष्ठा nl80211_wowlan_tcp_data_token)
	पूर्ण,
	[NL80211_WOWLAN_TCP_DATA_INTERVAL] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_WOWLAN_TCP_WAKE_PAYLOAD] = NLA_POLICY_MIN_LEN(1),
	[NL80211_WOWLAN_TCP_WAKE_MASK] = NLA_POLICY_MIN_LEN(1),
पूर्ण;
#पूर्ण_अगर /* CONFIG_PM */

/* policy क्रम coalesce rule attributes */
अटल स्थिर काष्ठा nla_policy
nl80211_coalesce_policy[NUM_NL80211_ATTR_COALESCE_RULE] = अणु
	[NL80211_ATTR_COALESCE_RULE_DELAY] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_COALESCE_RULE_CONDITION] =
		NLA_POLICY_RANGE(NLA_U32,
				 NL80211_COALESCE_CONDITION_MATCH,
				 NL80211_COALESCE_CONDITION_NO_MATCH),
	[NL80211_ATTR_COALESCE_RULE_PKT_PATTERN] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

/* policy क्रम GTK rekey offload attributes */
अटल स्थिर काष्ठा nla_policy
nl80211_rekey_policy[NUM_NL80211_REKEY_DATA] = अणु
	[NL80211_REKEY_DATA_KEK] = अणु
		.type = NLA_BINARY,
		.len = NL80211_KEK_EXT_LEN
	पूर्ण,
	[NL80211_REKEY_DATA_KCK] = अणु
		.type = NLA_BINARY,
		.len = NL80211_KCK_EXT_LEN
	पूर्ण,
	[NL80211_REKEY_DATA_REPLAY_CTR] = NLA_POLICY_EXACT_LEN(NL80211_REPLAY_CTR_LEN),
	[NL80211_REKEY_DATA_AKM] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_match_band_rssi_policy[NUM_NL80211_BANDS] = अणु
	[NL80211_BAND_2GHZ] = अणु .type = NLA_S32 पूर्ण,
	[NL80211_BAND_5GHZ] = अणु .type = NLA_S32 पूर्ण,
	[NL80211_BAND_6GHZ] = अणु .type = NLA_S32 पूर्ण,
	[NL80211_BAND_60GHZ] = अणु .type = NLA_S32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_match_policy[NL80211_SCHED_SCAN_MATCH_ATTR_MAX + 1] = अणु
	[NL80211_SCHED_SCAN_MATCH_ATTR_SSID] = अणु .type = NLA_BINARY,
						 .len = IEEE80211_MAX_SSID_LEN पूर्ण,
	[NL80211_SCHED_SCAN_MATCH_ATTR_BSSID] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),
	[NL80211_SCHED_SCAN_MATCH_ATTR_RSSI] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_SCHED_SCAN_MATCH_PER_BAND_RSSI] =
		NLA_POLICY_NESTED(nl80211_match_band_rssi_policy),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_plan_policy[NL80211_SCHED_SCAN_PLAN_MAX + 1] = अणु
	[NL80211_SCHED_SCAN_PLAN_INTERVAL] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_SCHED_SCAN_PLAN_ITERATIONS] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा nla_policy
nl80211_bss_select_policy[NL80211_BSS_SELECT_ATTR_MAX + 1] = अणु
	[NL80211_BSS_SELECT_ATTR_RSSI] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_BSS_SELECT_ATTR_BAND_PREF] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_BSS_SELECT_ATTR_RSSI_ADJUST] = अणु
		.len = माप(काष्ठा nl80211_bss_select_rssi_adjust)
	पूर्ण,
पूर्ण;

/* policy क्रम न_अंक function attributes */
अटल स्थिर काष्ठा nla_policy
nl80211_nan_func_policy[NL80211_न_अंक_FUNC_ATTR_MAX + 1] = अणु
	[NL80211_न_अंक_FUNC_TYPE] =
		NLA_POLICY_MAX(NLA_U8, NL80211_न_अंक_FUNC_MAX_TYPE),
	[NL80211_न_अंक_FUNC_SERVICE_ID] = अणु
				    .len = NL80211_न_अंक_FUNC_SERVICE_ID_LEN पूर्ण,
	[NL80211_न_अंक_FUNC_PUBLISH_TYPE] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_न_अंक_FUNC_PUBLISH_BCAST] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_न_अंक_FUNC_SUBSCRIBE_ACTIVE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_न_अंक_FUNC_FOLLOW_UP_ID] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_न_अंक_FUNC_FOLLOW_UP_REQ_ID] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_न_अंक_FUNC_FOLLOW_UP_DEST] = NLA_POLICY_EXACT_LEN_WARN(ETH_ALEN),
	[NL80211_न_अंक_FUNC_CLOSE_RANGE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_न_अंक_FUNC_TTL] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_न_अंक_FUNC_SERVICE_INFO] = अणु .type = NLA_BINARY,
			.len = NL80211_न_अंक_FUNC_SERVICE_SPEC_INFO_MAX_LEN पूर्ण,
	[NL80211_न_अंक_FUNC_SRF] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_न_अंक_FUNC_RX_MATCH_FILTER] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_न_अंक_FUNC_TX_MATCH_FILTER] = अणु .type = NLA_NESTED पूर्ण,
	[NL80211_न_अंक_FUNC_INSTANCE_ID] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_न_अंक_FUNC_TERM_REASON] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

/* policy क्रम Service Response Filter attributes */
अटल स्थिर काष्ठा nla_policy
nl80211_nan_srf_policy[NL80211_न_अंक_SRF_ATTR_MAX + 1] = अणु
	[NL80211_न_अंक_SRF_INCLUDE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_न_अंक_SRF_BF] = अणु .type = NLA_BINARY,
				 .len =  NL80211_न_अंक_FUNC_SRF_MAX_LEN पूर्ण,
	[NL80211_न_अंक_SRF_BF_IDX] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_न_अंक_SRF_MAC_ADDRS] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

/* policy क्रम packet pattern attributes */
अटल स्थिर काष्ठा nla_policy
nl80211_packet_pattern_policy[MAX_NL80211_PKTPAT + 1] = अणु
	[NL80211_PKTPAT_MASK] = अणु .type = NLA_BINARY, पूर्ण,
	[NL80211_PKTPAT_PATTERN] = अणु .type = NLA_BINARY, पूर्ण,
	[NL80211_PKTPAT_OFFSET] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

पूर्णांक nl80211_prepare_wdev_dump(काष्ठा netlink_callback *cb,
			      काष्ठा cfg80211_रेजिस्टरed_device **rdev,
			      काष्ठा wireless_dev **wdev)
अणु
	पूर्णांक err;

	अगर (!cb->args[0]) अणु
		काष्ठा nlattr **attrbuf;

		attrbuf = kसुस्मृति(NUM_NL80211_ATTR, माप(*attrbuf),
				  GFP_KERNEL);
		अगर (!attrbuf)
			वापस -ENOMEM;

		err = nlmsg_parse_deprecated(cb->nlh,
					     GENL_HDRLEN + nl80211_fam.hdrsize,
					     attrbuf, nl80211_fam.maxattr,
					     nl80211_policy, शून्य);
		अगर (err) अणु
			kमुक्त(attrbuf);
			वापस err;
		पूर्ण

		rtnl_lock();
		*wdev = __cfg80211_wdev_from_attrs(शून्य, sock_net(cb->skb->sk),
						   attrbuf);
		kमुक्त(attrbuf);
		अगर (IS_ERR(*wdev)) अणु
			rtnl_unlock();
			वापस PTR_ERR(*wdev);
		पूर्ण
		*rdev = wiphy_to_rdev((*wdev)->wiphy);
		mutex_lock(&(*rdev)->wiphy.mtx);
		rtnl_unlock();
		/* 0 is the first index - add 1 to parse only once */
		cb->args[0] = (*rdev)->wiphy_idx + 1;
		cb->args[1] = (*wdev)->identअगरier;
	पूर्ण अन्यथा अणु
		/* subtract the 1 again here */
		काष्ठा wiphy *wiphy;
		काष्ठा wireless_dev *पंचांगp;

		rtnl_lock();
		wiphy = wiphy_idx_to_wiphy(cb->args[0] - 1);
		अगर (!wiphy) अणु
			rtnl_unlock();
			वापस -ENODEV;
		पूर्ण
		*rdev = wiphy_to_rdev(wiphy);
		*wdev = शून्य;

		list_क्रम_each_entry(पंचांगp, &(*rdev)->wiphy.wdev_list, list) अणु
			अगर (पंचांगp->identअगरier == cb->args[1]) अणु
				*wdev = पंचांगp;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (!*wdev) अणु
			rtnl_unlock();
			वापस -ENODEV;
		पूर्ण
		mutex_lock(&(*rdev)->wiphy.mtx);
		rtnl_unlock();
	पूर्ण

	वापस 0;
पूर्ण

/* message building helper */
व्योम *nl80211hdr_put(काष्ठा sk_buff *skb, u32 portid, u32 seq,
		     पूर्णांक flags, u8 cmd)
अणु
	/* since there is no निजी header just add the generic one */
	वापस genlmsg_put(skb, portid, seq, &nl80211_fam, flags, cmd);
पूर्ण

अटल पूर्णांक nl80211_msg_put_wmm_rules(काष्ठा sk_buff *msg,
				     स्थिर काष्ठा ieee80211_reg_rule *rule)
अणु
	पूर्णांक j;
	काष्ठा nlattr *nl_wmm_rules =
		nla_nest_start_noflag(msg, NL80211_FREQUENCY_ATTR_WMM);

	अगर (!nl_wmm_rules)
		जाओ nla_put_failure;

	क्रम (j = 0; j < IEEE80211_NUM_ACS; j++) अणु
		काष्ठा nlattr *nl_wmm_rule = nla_nest_start_noflag(msg, j);

		अगर (!nl_wmm_rule)
			जाओ nla_put_failure;

		अगर (nla_put_u16(msg, NL80211_WMMR_CW_MIN,
				rule->wmm_rule.client[j].cw_min) ||
		    nla_put_u16(msg, NL80211_WMMR_CW_MAX,
				rule->wmm_rule.client[j].cw_max) ||
		    nla_put_u8(msg, NL80211_WMMR_AIFSN,
			       rule->wmm_rule.client[j].aअगरsn) ||
		    nla_put_u16(msg, NL80211_WMMR_TXOP,
			        rule->wmm_rule.client[j].cot))
			जाओ nla_put_failure;

		nla_nest_end(msg, nl_wmm_rule);
	पूर्ण
	nla_nest_end(msg, nl_wmm_rules);

	वापस 0;

nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक nl80211_msg_put_channel(काष्ठा sk_buff *msg, काष्ठा wiphy *wiphy,
				   काष्ठा ieee80211_channel *chan,
				   bool large)
अणु
	/* Some channels must be completely excluded from the
	 * list to protect old user-space tools from अवरोधing
	 */
	अगर (!large && chan->flags &
	    (IEEE80211_CHAN_NO_10MHZ | IEEE80211_CHAN_NO_20MHZ))
		वापस 0;
	अगर (!large && chan->freq_offset)
		वापस 0;

	अगर (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_FREQ,
			chan->center_freq))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_OFFSET, chan->freq_offset))
		जाओ nla_put_failure;

	अगर ((chan->flags & IEEE80211_CHAN_DISABLED) &&
	    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_DISABLED))
		जाओ nla_put_failure;
	अगर (chan->flags & IEEE80211_CHAN_NO_IR) अणु
		अगर (nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_IR))
			जाओ nla_put_failure;
		अगर (nla_put_flag(msg, __NL80211_FREQUENCY_ATTR_NO_IBSS))
			जाओ nla_put_failure;
	पूर्ण
	अगर (chan->flags & IEEE80211_CHAN_RADAR) अणु
		अगर (nla_put_flag(msg, NL80211_FREQUENCY_ATTR_RADAR))
			जाओ nla_put_failure;
		अगर (large) अणु
			u32 समय;

			समय = elapsed_jअगरfies_msecs(chan->dfs_state_entered);

			अगर (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_DFS_STATE,
					chan->dfs_state))
				जाओ nla_put_failure;
			अगर (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_DFS_TIME,
					समय))
				जाओ nla_put_failure;
			अगर (nla_put_u32(msg,
					NL80211_FREQUENCY_ATTR_DFS_CAC_TIME,
					chan->dfs_cac_ms))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर (large) अणु
		अगर ((chan->flags & IEEE80211_CHAN_NO_HT40MINUS) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_HT40_MINUS))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_NO_HT40PLUS) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_HT40_PLUS))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_NO_80MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_80MHZ))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_NO_160MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_160MHZ))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_INDOOR_ONLY) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_INDOOR_ONLY))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_IR_CONCURRENT) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_IR_CONCURRENT))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_NO_20MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_20MHZ))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_NO_10MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_10MHZ))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_NO_HE) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_NO_HE))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_1MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_1MHZ))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_2MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_2MHZ))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_4MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_4MHZ))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_8MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_8MHZ))
			जाओ nla_put_failure;
		अगर ((chan->flags & IEEE80211_CHAN_16MHZ) &&
		    nla_put_flag(msg, NL80211_FREQUENCY_ATTR_16MHZ))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_FREQUENCY_ATTR_MAX_TX_POWER,
			DBM_TO_MBM(chan->max_घातer)))
		जाओ nla_put_failure;

	अगर (large) अणु
		स्थिर काष्ठा ieee80211_reg_rule *rule =
			freq_reg_info(wiphy, MHZ_TO_KHZ(chan->center_freq));

		अगर (!IS_ERR_OR_शून्य(rule) && rule->has_wmm) अणु
			अगर (nl80211_msg_put_wmm_rules(msg, rule))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	वापस 0;

 nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

अटल bool nl80211_put_txq_stats(काष्ठा sk_buff *msg,
				  काष्ठा cfg80211_txq_stats *txqstats,
				  पूर्णांक attrtype)
अणु
	काष्ठा nlattr *txqattr;

#घोषणा PUT_TXQVAL_U32(attr, memb) करो अणु					  \
	अगर (txqstats->filled & BIT(NL80211_TXQ_STATS_ ## attr) &&	  \
	    nla_put_u32(msg, NL80211_TXQ_STATS_ ## attr, txqstats->memb)) \
		वापस false;						  \
	पूर्ण जबतक (0)

	txqattr = nla_nest_start_noflag(msg, attrtype);
	अगर (!txqattr)
		वापस false;

	PUT_TXQVAL_U32(BACKLOG_BYTES, backlog_bytes);
	PUT_TXQVAL_U32(BACKLOG_PACKETS, backlog_packets);
	PUT_TXQVAL_U32(FLOWS, flows);
	PUT_TXQVAL_U32(DROPS, drops);
	PUT_TXQVAL_U32(ECN_MARKS, ecn_marks);
	PUT_TXQVAL_U32(OVERLIMIT, overlimit);
	PUT_TXQVAL_U32(OVERMEMORY, overmemory);
	PUT_TXQVAL_U32(COLLISIONS, collisions);
	PUT_TXQVAL_U32(TX_BYTES, tx_bytes);
	PUT_TXQVAL_U32(TX_PACKETS, tx_packets);
	PUT_TXQVAL_U32(MAX_FLOWS, max_flows);
	nla_nest_end(msg, txqattr);

#अघोषित PUT_TXQVAL_U32
	वापस true;
पूर्ण

/* netlink command implementations */

काष्ठा key_parse अणु
	काष्ठा key_params p;
	पूर्णांक idx;
	पूर्णांक type;
	bool def, defmgmt, defbeacon;
	bool def_uni, def_multi;
पूर्ण;

अटल पूर्णांक nl80211_parse_key_new(काष्ठा genl_info *info, काष्ठा nlattr *key,
				 काष्ठा key_parse *k)
अणु
	काष्ठा nlattr *tb[NL80211_KEY_MAX + 1];
	पूर्णांक err = nla_parse_nested_deprecated(tb, NL80211_KEY_MAX, key,
					      nl80211_key_policy,
					      info->extack);
	अगर (err)
		वापस err;

	k->def = !!tb[NL80211_KEY_DEFAULT];
	k->defmgmt = !!tb[NL80211_KEY_DEFAULT_MGMT];
	k->defbeacon = !!tb[NL80211_KEY_DEFAULT_BEACON];

	अगर (k->def) अणु
		k->def_uni = true;
		k->def_multi = true;
	पूर्ण
	अगर (k->defmgmt || k->defbeacon)
		k->def_multi = true;

	अगर (tb[NL80211_KEY_IDX])
		k->idx = nla_get_u8(tb[NL80211_KEY_IDX]);

	अगर (tb[NL80211_KEY_DATA]) अणु
		k->p.key = nla_data(tb[NL80211_KEY_DATA]);
		k->p.key_len = nla_len(tb[NL80211_KEY_DATA]);
	पूर्ण

	अगर (tb[NL80211_KEY_SEQ]) अणु
		k->p.seq = nla_data(tb[NL80211_KEY_SEQ]);
		k->p.seq_len = nla_len(tb[NL80211_KEY_SEQ]);
	पूर्ण

	अगर (tb[NL80211_KEY_CIPHER])
		k->p.cipher = nla_get_u32(tb[NL80211_KEY_CIPHER]);

	अगर (tb[NL80211_KEY_TYPE])
		k->type = nla_get_u32(tb[NL80211_KEY_TYPE]);

	अगर (tb[NL80211_KEY_DEFAULT_TYPES]) अणु
		काष्ठा nlattr *kdt[NUM_NL80211_KEY_DEFAULT_TYPES];

		err = nla_parse_nested_deprecated(kdt,
						  NUM_NL80211_KEY_DEFAULT_TYPES - 1,
						  tb[NL80211_KEY_DEFAULT_TYPES],
						  nl80211_key_शेष_policy,
						  info->extack);
		अगर (err)
			वापस err;

		k->def_uni = kdt[NL80211_KEY_DEFAULT_TYPE_UNICAST];
		k->def_multi = kdt[NL80211_KEY_DEFAULT_TYPE_MULTICAST];
	पूर्ण

	अगर (tb[NL80211_KEY_MODE])
		k->p.mode = nla_get_u8(tb[NL80211_KEY_MODE]);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_key_old(काष्ठा genl_info *info, काष्ठा key_parse *k)
अणु
	अगर (info->attrs[NL80211_ATTR_KEY_DATA]) अणु
		k->p.key = nla_data(info->attrs[NL80211_ATTR_KEY_DATA]);
		k->p.key_len = nla_len(info->attrs[NL80211_ATTR_KEY_DATA]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_KEY_SEQ]) अणु
		k->p.seq = nla_data(info->attrs[NL80211_ATTR_KEY_SEQ]);
		k->p.seq_len = nla_len(info->attrs[NL80211_ATTR_KEY_SEQ]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_KEY_IDX])
		k->idx = nla_get_u8(info->attrs[NL80211_ATTR_KEY_IDX]);

	अगर (info->attrs[NL80211_ATTR_KEY_CIPHER])
		k->p.cipher = nla_get_u32(info->attrs[NL80211_ATTR_KEY_CIPHER]);

	k->def = !!info->attrs[NL80211_ATTR_KEY_DEFAULT];
	k->defmgmt = !!info->attrs[NL80211_ATTR_KEY_DEFAULT_MGMT];

	अगर (k->def) अणु
		k->def_uni = true;
		k->def_multi = true;
	पूर्ण
	अगर (k->defmgmt)
		k->def_multi = true;

	अगर (info->attrs[NL80211_ATTR_KEY_TYPE])
		k->type = nla_get_u32(info->attrs[NL80211_ATTR_KEY_TYPE]);

	अगर (info->attrs[NL80211_ATTR_KEY_DEFAULT_TYPES]) अणु
		काष्ठा nlattr *kdt[NUM_NL80211_KEY_DEFAULT_TYPES];
		पूर्णांक err = nla_parse_nested_deprecated(kdt,
						      NUM_NL80211_KEY_DEFAULT_TYPES - 1,
						      info->attrs[NL80211_ATTR_KEY_DEFAULT_TYPES],
						      nl80211_key_शेष_policy,
						      info->extack);
		अगर (err)
			वापस err;

		k->def_uni = kdt[NL80211_KEY_DEFAULT_TYPE_UNICAST];
		k->def_multi = kdt[NL80211_KEY_DEFAULT_TYPE_MULTICAST];
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_key(काष्ठा genl_info *info, काष्ठा key_parse *k)
अणु
	पूर्णांक err;

	स_रखो(k, 0, माप(*k));
	k->idx = -1;
	k->type = -1;

	अगर (info->attrs[NL80211_ATTR_KEY])
		err = nl80211_parse_key_new(info, info->attrs[NL80211_ATTR_KEY], k);
	अन्यथा
		err = nl80211_parse_key_old(info, k);

	अगर (err)
		वापस err;

	अगर ((k->def ? 1 : 0) + (k->defmgmt ? 1 : 0) +
	    (k->defbeacon ? 1 : 0) > 1) अणु
		GENL_SET_ERR_MSG(info,
				 "key with multiple default flags is invalid");
		वापस -EINVAL;
	पूर्ण

	अगर (k->defmgmt || k->defbeacon) अणु
		अगर (k->def_uni || !k->def_multi) अणु
			GENL_SET_ERR_MSG(info,
					 "defmgmt/defbeacon key must be mcast");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (k->idx != -1) अणु
		अगर (k->defmgmt) अणु
			अगर (k->idx < 4 || k->idx > 5) अणु
				GENL_SET_ERR_MSG(info,
						 "defmgmt key idx not 4 or 5");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (k->defbeacon) अणु
			अगर (k->idx < 6 || k->idx > 7) अणु
				GENL_SET_ERR_MSG(info,
						 "defbeacon key idx not 6 or 7");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अगर (k->def) अणु
			अगर (k->idx < 0 || k->idx > 3) अणु
				GENL_SET_ERR_MSG(info, "def key idx not 0-3");
				वापस -EINVAL;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (k->idx < 0 || k->idx > 7) अणु
				GENL_SET_ERR_MSG(info, "key idx not 0-7");
				वापस -EINVAL;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा cfg80211_cached_keys *
nl80211_parse_connkeys(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		       काष्ठा genl_info *info, bool *no_ht)
अणु
	काष्ठा nlattr *keys = info->attrs[NL80211_ATTR_KEYS];
	काष्ठा key_parse parse;
	काष्ठा nlattr *key;
	काष्ठा cfg80211_cached_keys *result;
	पूर्णांक rem, err, def = 0;
	bool have_key = false;

	nla_क्रम_each_nested(key, keys, rem) अणु
		have_key = true;
		अवरोध;
	पूर्ण

	अगर (!have_key)
		वापस शून्य;

	result = kzalloc(माप(*result), GFP_KERNEL);
	अगर (!result)
		वापस ERR_PTR(-ENOMEM);

	result->def = -1;

	nla_क्रम_each_nested(key, keys, rem) अणु
		स_रखो(&parse, 0, माप(parse));
		parse.idx = -1;

		err = nl80211_parse_key_new(info, key, &parse);
		अगर (err)
			जाओ error;
		err = -EINVAL;
		अगर (!parse.p.key)
			जाओ error;
		अगर (parse.idx < 0 || parse.idx > 3) अणु
			GENL_SET_ERR_MSG(info, "key index out of range [0-3]");
			जाओ error;
		पूर्ण
		अगर (parse.def) अणु
			अगर (def) अणु
				GENL_SET_ERR_MSG(info,
						 "only one key can be default");
				जाओ error;
			पूर्ण
			def = 1;
			result->def = parse.idx;
			अगर (!parse.def_uni || !parse.def_multi)
				जाओ error;
		पूर्ण अन्यथा अगर (parse.defmgmt)
			जाओ error;
		err = cfg80211_validate_key_settings(rdev, &parse.p,
						     parse.idx, false, शून्य);
		अगर (err)
			जाओ error;
		अगर (parse.p.cipher != WLAN_CIPHER_SUITE_WEP40 &&
		    parse.p.cipher != WLAN_CIPHER_SUITE_WEP104) अणु
			GENL_SET_ERR_MSG(info, "connect key must be WEP");
			err = -EINVAL;
			जाओ error;
		पूर्ण
		result->params[parse.idx].cipher = parse.p.cipher;
		result->params[parse.idx].key_len = parse.p.key_len;
		result->params[parse.idx].key = result->data[parse.idx];
		स_नकल(result->data[parse.idx], parse.p.key, parse.p.key_len);

		/* must be WEP key अगर we got here */
		अगर (no_ht)
			*no_ht = true;
	पूर्ण

	अगर (result->def < 0) अणु
		err = -EINVAL;
		GENL_SET_ERR_MSG(info, "need a default/TX key");
		जाओ error;
	पूर्ण

	वापस result;
 error:
	kमुक्त(result);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक nl80211_key_allowed(काष्ठा wireless_dev *wdev)
अणु
	ASSERT_WDEV_LOCK(wdev);

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_MESH_POINT:
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (!wdev->current_bss)
			वापस -ENOLINK;
		अवरोध;
	हाल NL80211_IFTYPE_UNSPECIFIED:
	हाल NL80211_IFTYPE_OCB:
	हाल NL80211_IFTYPE_MONITOR:
	हाल NL80211_IFTYPE_न_अंक:
	हाल NL80211_IFTYPE_P2P_DEVICE:
	हाल NL80211_IFTYPE_WDS:
	हाल NUM_NL80211_IFTYPES:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा ieee80211_channel *nl80211_get_valid_chan(काष्ठा wiphy *wiphy,
							u32 freq)
अणु
	काष्ठा ieee80211_channel *chan;

	chan = ieee80211_get_channel_khz(wiphy, freq);
	अगर (!chan || chan->flags & IEEE80211_CHAN_DISABLED)
		वापस शून्य;
	वापस chan;
पूर्ण

अटल पूर्णांक nl80211_put_अगरtypes(काष्ठा sk_buff *msg, u32 attr, u16 अगरmodes)
अणु
	काष्ठा nlattr *nl_modes = nla_nest_start_noflag(msg, attr);
	पूर्णांक i;

	अगर (!nl_modes)
		जाओ nla_put_failure;

	i = 0;
	जबतक (अगरmodes) अणु
		अगर ((अगरmodes & 1) && nla_put_flag(msg, i))
			जाओ nla_put_failure;
		अगरmodes >>= 1;
		i++;
	पूर्ण

	nla_nest_end(msg, nl_modes);
	वापस 0;

nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक nl80211_put_अगरace_combinations(काष्ठा wiphy *wiphy,
					  काष्ठा sk_buff *msg,
					  bool large)
अणु
	काष्ठा nlattr *nl_combis;
	पूर्णांक i, j;

	nl_combis = nla_nest_start_noflag(msg,
					  NL80211_ATTR_INTERFACE_COMBINATIONS);
	अगर (!nl_combis)
		जाओ nla_put_failure;

	क्रम (i = 0; i < wiphy->n_अगरace_combinations; i++) अणु
		स्थिर काष्ठा ieee80211_अगरace_combination *c;
		काष्ठा nlattr *nl_combi, *nl_limits;

		c = &wiphy->अगरace_combinations[i];

		nl_combi = nla_nest_start_noflag(msg, i + 1);
		अगर (!nl_combi)
			जाओ nla_put_failure;

		nl_limits = nla_nest_start_noflag(msg,
						  NL80211_IFACE_COMB_LIMITS);
		अगर (!nl_limits)
			जाओ nla_put_failure;

		क्रम (j = 0; j < c->n_limits; j++) अणु
			काष्ठा nlattr *nl_limit;

			nl_limit = nla_nest_start_noflag(msg, j + 1);
			अगर (!nl_limit)
				जाओ nla_put_failure;
			अगर (nla_put_u32(msg, NL80211_IFACE_LIMIT_MAX,
					c->limits[j].max))
				जाओ nla_put_failure;
			अगर (nl80211_put_अगरtypes(msg, NL80211_IFACE_LIMIT_TYPES,
						c->limits[j].types))
				जाओ nla_put_failure;
			nla_nest_end(msg, nl_limit);
		पूर्ण

		nla_nest_end(msg, nl_limits);

		अगर (c->beacon_पूर्णांक_infra_match &&
		    nla_put_flag(msg, NL80211_IFACE_COMB_STA_AP_BI_MATCH))
			जाओ nla_put_failure;
		अगर (nla_put_u32(msg, NL80211_IFACE_COMB_NUM_CHANNELS,
				c->num_dअगरferent_channels) ||
		    nla_put_u32(msg, NL80211_IFACE_COMB_MAXNUM,
				c->max_पूर्णांकerfaces))
			जाओ nla_put_failure;
		अगर (large &&
		    (nla_put_u32(msg, NL80211_IFACE_COMB_RADAR_DETECT_WIDTHS,
				c->radar_detect_widths) ||
		     nla_put_u32(msg, NL80211_IFACE_COMB_RADAR_DETECT_REGIONS,
				c->radar_detect_regions)))
			जाओ nla_put_failure;
		अगर (c->beacon_पूर्णांक_min_gcd &&
		    nla_put_u32(msg, NL80211_IFACE_COMB_BI_MIN_GCD,
				c->beacon_पूर्णांक_min_gcd))
			जाओ nla_put_failure;

		nla_nest_end(msg, nl_combi);
	पूर्ण

	nla_nest_end(msg, nl_combis);

	वापस 0;
nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक nl80211_send_wowlan_tcp_caps(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
					काष्ठा sk_buff *msg)
अणु
	स्थिर काष्ठा wiphy_wowlan_tcp_support *tcp = rdev->wiphy.wowlan->tcp;
	काष्ठा nlattr *nl_tcp;

	अगर (!tcp)
		वापस 0;

	nl_tcp = nla_nest_start_noflag(msg,
				       NL80211_WOWLAN_TRIG_TCP_CONNECTION);
	अगर (!nl_tcp)
		वापस -ENOBUFS;

	अगर (nla_put_u32(msg, NL80211_WOWLAN_TCP_DATA_PAYLOAD,
			tcp->data_payload_max))
		वापस -ENOBUFS;

	अगर (nla_put_u32(msg, NL80211_WOWLAN_TCP_DATA_PAYLOAD,
			tcp->data_payload_max))
		वापस -ENOBUFS;

	अगर (tcp->seq && nla_put_flag(msg, NL80211_WOWLAN_TCP_DATA_PAYLOAD_SEQ))
		वापस -ENOBUFS;

	अगर (tcp->tok && nla_put(msg, NL80211_WOWLAN_TCP_DATA_PAYLOAD_TOKEN,
				माप(*tcp->tok), tcp->tok))
		वापस -ENOBUFS;

	अगर (nla_put_u32(msg, NL80211_WOWLAN_TCP_DATA_INTERVAL,
			tcp->data_पूर्णांकerval_max))
		वापस -ENOBUFS;

	अगर (nla_put_u32(msg, NL80211_WOWLAN_TCP_WAKE_PAYLOAD,
			tcp->wake_payload_max))
		वापस -ENOBUFS;

	nla_nest_end(msg, nl_tcp);
	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_send_wowlan(काष्ठा sk_buff *msg,
			       काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       bool large)
अणु
	काष्ठा nlattr *nl_wowlan;

	अगर (!rdev->wiphy.wowlan)
		वापस 0;

	nl_wowlan = nla_nest_start_noflag(msg,
					  NL80211_ATTR_WOWLAN_TRIGGERS_SUPPORTED);
	अगर (!nl_wowlan)
		वापस -ENOBUFS;

	अगर (((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_ANY) &&
	     nla_put_flag(msg, NL80211_WOWLAN_TRIG_ANY)) ||
	    ((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_DISCONNECT) &&
	     nla_put_flag(msg, NL80211_WOWLAN_TRIG_DISCONNECT)) ||
	    ((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_MAGIC_PKT) &&
	     nla_put_flag(msg, NL80211_WOWLAN_TRIG_MAGIC_PKT)) ||
	    ((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_SUPPORTS_GTK_REKEY) &&
	     nla_put_flag(msg, NL80211_WOWLAN_TRIG_GTK_REKEY_SUPPORTED)) ||
	    ((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_GTK_REKEY_FAILURE) &&
	     nla_put_flag(msg, NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE)) ||
	    ((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_EAP_IDENTITY_REQ) &&
	     nla_put_flag(msg, NL80211_WOWLAN_TRIG_EAP_IDENT_REQUEST)) ||
	    ((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_4WAY_HANDSHAKE) &&
	     nla_put_flag(msg, NL80211_WOWLAN_TRIG_4WAY_HANDSHAKE)) ||
	    ((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_RFKILL_RELEASE) &&
	     nla_put_flag(msg, NL80211_WOWLAN_TRIG_RFKILL_RELEASE)))
		वापस -ENOBUFS;

	अगर (rdev->wiphy.wowlan->n_patterns) अणु
		काष्ठा nl80211_pattern_support pat = अणु
			.max_patterns = rdev->wiphy.wowlan->n_patterns,
			.min_pattern_len = rdev->wiphy.wowlan->pattern_min_len,
			.max_pattern_len = rdev->wiphy.wowlan->pattern_max_len,
			.max_pkt_offset = rdev->wiphy.wowlan->max_pkt_offset,
		पूर्ण;

		अगर (nla_put(msg, NL80211_WOWLAN_TRIG_PKT_PATTERN,
			    माप(pat), &pat))
			वापस -ENOBUFS;
	पूर्ण

	अगर ((rdev->wiphy.wowlan->flags & WIPHY_WOWLAN_NET_DETECT) &&
	    nla_put_u32(msg, NL80211_WOWLAN_TRIG_NET_DETECT,
			rdev->wiphy.wowlan->max_nd_match_sets))
		वापस -ENOBUFS;

	अगर (large && nl80211_send_wowlan_tcp_caps(rdev, msg))
		वापस -ENOBUFS;

	nla_nest_end(msg, nl_wowlan);

	वापस 0;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nl80211_send_coalesce(काष्ठा sk_buff *msg,
				 काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा nl80211_coalesce_rule_support rule;

	अगर (!rdev->wiphy.coalesce)
		वापस 0;

	rule.max_rules = rdev->wiphy.coalesce->n_rules;
	rule.max_delay = rdev->wiphy.coalesce->max_delay;
	rule.pat.max_patterns = rdev->wiphy.coalesce->n_patterns;
	rule.pat.min_pattern_len = rdev->wiphy.coalesce->pattern_min_len;
	rule.pat.max_pattern_len = rdev->wiphy.coalesce->pattern_max_len;
	rule.pat.max_pkt_offset = rdev->wiphy.coalesce->max_pkt_offset;

	अगर (nla_put(msg, NL80211_ATTR_COALESCE_RULE, माप(rule), &rule))
		वापस -ENOBUFS;

	वापस 0;
पूर्ण

अटल पूर्णांक
nl80211_send_अगरtype_data(काष्ठा sk_buff *msg,
			 स्थिर काष्ठा ieee80211_supported_band *sband,
			 स्थिर काष्ठा ieee80211_sband_अगरtype_data *अगरtdata)
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap = &अगरtdata->he_cap;

	अगर (nl80211_put_अगरtypes(msg, NL80211_BAND_IFTYPE_ATTR_IFTYPES,
				अगरtdata->types_mask))
		वापस -ENOBUFS;

	अगर (he_cap->has_he) अणु
		अगर (nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_CAP_MAC,
			    माप(he_cap->he_cap_elem.mac_cap_info),
			    he_cap->he_cap_elem.mac_cap_info) ||
		    nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_CAP_PHY,
			    माप(he_cap->he_cap_elem.phy_cap_info),
			    he_cap->he_cap_elem.phy_cap_info) ||
		    nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_CAP_MCS_SET,
			    माप(he_cap->he_mcs_nss_supp),
			    &he_cap->he_mcs_nss_supp) ||
		    nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_CAP_PPE,
			    माप(he_cap->ppe_thres), he_cap->ppe_thres))
			वापस -ENOBUFS;
	पूर्ण

	अगर (sband->band == NL80211_BAND_6GHZ &&
	    nla_put(msg, NL80211_BAND_IFTYPE_ATTR_HE_6GHZ_CAPA,
		    माप(अगरtdata->he_6ghz_capa),
		    &अगरtdata->he_6ghz_capa))
		वापस -ENOBUFS;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_send_band_rateinfo(काष्ठा sk_buff *msg,
				      काष्ठा ieee80211_supported_band *sband,
				      bool large)
अणु
	काष्ठा nlattr *nl_rates, *nl_rate;
	काष्ठा ieee80211_rate *rate;
	पूर्णांक i;

	/* add HT info */
	अगर (sband->ht_cap.ht_supported &&
	    (nla_put(msg, NL80211_BAND_ATTR_HT_MCS_SET,
		     माप(sband->ht_cap.mcs),
		     &sband->ht_cap.mcs) ||
	     nla_put_u16(msg, NL80211_BAND_ATTR_HT_CAPA,
			 sband->ht_cap.cap) ||
	     nla_put_u8(msg, NL80211_BAND_ATTR_HT_AMPDU_FACTOR,
			sband->ht_cap.ampdu_factor) ||
	     nla_put_u8(msg, NL80211_BAND_ATTR_HT_AMPDU_DENSITY,
			sband->ht_cap.ampdu_density)))
		वापस -ENOBUFS;

	/* add VHT info */
	अगर (sband->vht_cap.vht_supported &&
	    (nla_put(msg, NL80211_BAND_ATTR_VHT_MCS_SET,
		     माप(sband->vht_cap.vht_mcs),
		     &sband->vht_cap.vht_mcs) ||
	     nla_put_u32(msg, NL80211_BAND_ATTR_VHT_CAPA,
			 sband->vht_cap.cap)))
		वापस -ENOBUFS;

	अगर (large && sband->n_अगरtype_data) अणु
		काष्ठा nlattr *nl_अगरtype_data =
			nla_nest_start_noflag(msg,
					      NL80211_BAND_ATTR_IFTYPE_DATA);
		पूर्णांक err;

		अगर (!nl_अगरtype_data)
			वापस -ENOBUFS;

		क्रम (i = 0; i < sband->n_अगरtype_data; i++) अणु
			काष्ठा nlattr *अगरtdata;

			अगरtdata = nla_nest_start_noflag(msg, i + 1);
			अगर (!अगरtdata)
				वापस -ENOBUFS;

			err = nl80211_send_अगरtype_data(msg, sband,
						       &sband->अगरtype_data[i]);
			अगर (err)
				वापस err;

			nla_nest_end(msg, अगरtdata);
		पूर्ण

		nla_nest_end(msg, nl_अगरtype_data);
	पूर्ण

	/* add EDMG info */
	अगर (large && sband->edmg_cap.channels &&
	    (nla_put_u8(msg, NL80211_BAND_ATTR_EDMG_CHANNELS,
		       sband->edmg_cap.channels) ||
	    nla_put_u8(msg, NL80211_BAND_ATTR_EDMG_BW_CONFIG,
		       sband->edmg_cap.bw_config)))

		वापस -ENOBUFS;

	/* add bitrates */
	nl_rates = nla_nest_start_noflag(msg, NL80211_BAND_ATTR_RATES);
	अगर (!nl_rates)
		वापस -ENOBUFS;

	क्रम (i = 0; i < sband->n_bitrates; i++) अणु
		nl_rate = nla_nest_start_noflag(msg, i);
		अगर (!nl_rate)
			वापस -ENOBUFS;

		rate = &sband->bitrates[i];
		अगर (nla_put_u32(msg, NL80211_BITRATE_ATTR_RATE,
				rate->bitrate))
			वापस -ENOBUFS;
		अगर ((rate->flags & IEEE80211_RATE_SHORT_PREAMBLE) &&
		    nla_put_flag(msg,
				 NL80211_BITRATE_ATTR_2GHZ_SHORTPREAMBLE))
			वापस -ENOBUFS;

		nla_nest_end(msg, nl_rate);
	पूर्ण

	nla_nest_end(msg, nl_rates);

	वापस 0;
पूर्ण

अटल पूर्णांक
nl80211_send_mgmt_stypes(काष्ठा sk_buff *msg,
			 स्थिर काष्ठा ieee80211_txrx_stypes *mgmt_stypes)
अणु
	u16 stypes;
	काष्ठा nlattr *nl_ftypes, *nl_अगरs;
	क्रमागत nl80211_अगरtype अगरt;
	पूर्णांक i;

	अगर (!mgmt_stypes)
		वापस 0;

	nl_अगरs = nla_nest_start_noflag(msg, NL80211_ATTR_TX_FRAME_TYPES);
	अगर (!nl_अगरs)
		वापस -ENOBUFS;

	क्रम (अगरt = 0; अगरt < NUM_NL80211_IFTYPES; अगरt++) अणु
		nl_ftypes = nla_nest_start_noflag(msg, अगरt);
		अगर (!nl_ftypes)
			वापस -ENOBUFS;
		i = 0;
		stypes = mgmt_stypes[अगरt].tx;
		जबतक (stypes) अणु
			अगर ((stypes & 1) &&
			    nla_put_u16(msg, NL80211_ATTR_FRAME_TYPE,
					(i << 4) | IEEE80211_FTYPE_MGMT))
				वापस -ENOBUFS;
			stypes >>= 1;
			i++;
		पूर्ण
		nla_nest_end(msg, nl_ftypes);
	पूर्ण

	nla_nest_end(msg, nl_अगरs);

	nl_अगरs = nla_nest_start_noflag(msg, NL80211_ATTR_RX_FRAME_TYPES);
	अगर (!nl_अगरs)
		वापस -ENOBUFS;

	क्रम (अगरt = 0; अगरt < NUM_NL80211_IFTYPES; अगरt++) अणु
		nl_ftypes = nla_nest_start_noflag(msg, अगरt);
		अगर (!nl_ftypes)
			वापस -ENOBUFS;
		i = 0;
		stypes = mgmt_stypes[अगरt].rx;
		जबतक (stypes) अणु
			अगर ((stypes & 1) &&
			    nla_put_u16(msg, NL80211_ATTR_FRAME_TYPE,
					(i << 4) | IEEE80211_FTYPE_MGMT))
				वापस -ENOBUFS;
			stypes >>= 1;
			i++;
		पूर्ण
		nla_nest_end(msg, nl_ftypes);
	पूर्ण
	nla_nest_end(msg, nl_अगरs);

	वापस 0;
पूर्ण

#घोषणा CMD(op, n)							\
	 करो अणु								\
		अगर (rdev->ops->op) अणु					\
			i++;						\
			अगर (nla_put_u32(msg, i, NL80211_CMD_ ## n)) 	\
				जाओ nla_put_failure;			\
		पूर्ण							\
	पूर्ण जबतक (0)

अटल पूर्णांक nl80211_add_commands_unsplit(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
					काष्ठा sk_buff *msg)
अणु
	पूर्णांक i = 0;

	/*
	 * करो *NOT* add anything पूर्णांकo this function, new things need to be
	 * advertised only to new versions of userspace that can deal with
	 * the split (and they can't possibly care about new features...
	 */
	CMD(add_भव_पूर्णांकf, NEW_INTERFACE);
	CMD(change_भव_पूर्णांकf, SET_INTERFACE);
	CMD(add_key, NEW_KEY);
	CMD(start_ap, START_AP);
	CMD(add_station, NEW_STATION);
	CMD(add_mpath, NEW_MPATH);
	CMD(update_mesh_config, SET_MESH_CONFIG);
	CMD(change_bss, SET_BSS);
	CMD(auth, AUTHENTICATE);
	CMD(assoc, ASSOCIATE);
	CMD(deauth, DEAUTHENTICATE);
	CMD(disassoc, DISASSOCIATE);
	CMD(join_ibss, JOIN_IBSS);
	CMD(join_mesh, JOIN_MESH);
	CMD(set_pmksa, SET_PMKSA);
	CMD(del_pmksa, DEL_PMKSA);
	CMD(flush_pmksa, FLUSH_PMKSA);
	अगर (rdev->wiphy.flags & WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL)
		CMD(reमुख्य_on_channel, REMAIN_ON_CHANNEL);
	CMD(set_bitrate_mask, SET_TX_BITRATE_MASK);
	CMD(mgmt_tx, FRAME);
	CMD(mgmt_tx_cancel_रुको, FRAME_WAIT_CANCEL);
	अगर (rdev->wiphy.flags & WIPHY_FLAG_NETNS_OK) अणु
		i++;
		अगर (nla_put_u32(msg, i, NL80211_CMD_SET_WIPHY_NETNS))
			जाओ nla_put_failure;
	पूर्ण
	अगर (rdev->ops->set_monitor_channel || rdev->ops->start_ap ||
	    rdev->ops->join_mesh) अणु
		i++;
		अगर (nla_put_u32(msg, i, NL80211_CMD_SET_CHANNEL))
			जाओ nla_put_failure;
	पूर्ण
	अगर (rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_TDLS) अणु
		CMD(tdls_mgmt, TDLS_MGMT);
		CMD(tdls_oper, TDLS_OPER);
	पूर्ण
	अगर (rdev->wiphy.max_sched_scan_reqs)
		CMD(sched_scan_start, START_SCHED_SCAN);
	CMD(probe_client, PROBE_CLIENT);
	CMD(set_noack_map, SET_NOACK_MAP);
	अगर (rdev->wiphy.flags & WIPHY_FLAG_REPORTS_OBSS) अणु
		i++;
		अगर (nla_put_u32(msg, i, NL80211_CMD_REGISTER_BEACONS))
			जाओ nla_put_failure;
	पूर्ण
	CMD(start_p2p_device, START_P2P_DEVICE);
	CMD(set_mcast_rate, SET_MCAST_RATE);
#अगर_घोषित CONFIG_NL80211_TESTMODE
	CMD(tesपंचांगode_cmd, TESTMODE);
#पूर्ण_अगर

	अगर (rdev->ops->connect || rdev->ops->auth) अणु
		i++;
		अगर (nla_put_u32(msg, i, NL80211_CMD_CONNECT))
			जाओ nla_put_failure;
	पूर्ण

	अगर (rdev->ops->disconnect || rdev->ops->deauth) अणु
		i++;
		अगर (nla_put_u32(msg, i, NL80211_CMD_DISCONNECT))
			जाओ nla_put_failure;
	पूर्ण

	वापस i;
 nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक
nl80211_send_pmsr_fपंचांग_capa(स्थिर काष्ठा cfg80211_pmsr_capabilities *cap,
			   काष्ठा sk_buff *msg)
अणु
	काष्ठा nlattr *fपंचांग;

	अगर (!cap->fपंचांग.supported)
		वापस 0;

	fपंचांग = nla_nest_start_noflag(msg, NL80211_PMSR_TYPE_FTM);
	अगर (!fपंचांग)
		वापस -ENOBUFS;

	अगर (cap->fपंचांग.asap && nla_put_flag(msg, NL80211_PMSR_FTM_CAPA_ATTR_ASAP))
		वापस -ENOBUFS;
	अगर (cap->fपंचांग.non_asap &&
	    nla_put_flag(msg, NL80211_PMSR_FTM_CAPA_ATTR_NON_ASAP))
		वापस -ENOBUFS;
	अगर (cap->fपंचांग.request_lci &&
	    nla_put_flag(msg, NL80211_PMSR_FTM_CAPA_ATTR_REQ_LCI))
		वापस -ENOBUFS;
	अगर (cap->fपंचांग.request_civicloc &&
	    nla_put_flag(msg, NL80211_PMSR_FTM_CAPA_ATTR_REQ_CIVICLOC))
		वापस -ENOBUFS;
	अगर (nla_put_u32(msg, NL80211_PMSR_FTM_CAPA_ATTR_PREAMBLES,
			cap->fपंचांग.preambles))
		वापस -ENOBUFS;
	अगर (nla_put_u32(msg, NL80211_PMSR_FTM_CAPA_ATTR_BANDWIDTHS,
			cap->fपंचांग.bandwidths))
		वापस -ENOBUFS;
	अगर (cap->fपंचांग.max_bursts_exponent >= 0 &&
	    nla_put_u32(msg, NL80211_PMSR_FTM_CAPA_ATTR_MAX_BURSTS_EXPONENT,
			cap->fपंचांग.max_bursts_exponent))
		वापस -ENOBUFS;
	अगर (cap->fपंचांग.max_fपंचांगs_per_burst &&
	    nla_put_u32(msg, NL80211_PMSR_FTM_CAPA_ATTR_MAX_FTMS_PER_BURST,
			cap->fपंचांग.max_fपंचांगs_per_burst))
		वापस -ENOBUFS;
	अगर (cap->fपंचांग.trigger_based &&
	    nla_put_flag(msg, NL80211_PMSR_FTM_CAPA_ATTR_TRIGGER_BASED))
		वापस -ENOBUFS;
	अगर (cap->fपंचांग.non_trigger_based &&
	    nla_put_flag(msg, NL80211_PMSR_FTM_CAPA_ATTR_NON_TRIGGER_BASED))
		वापस -ENOBUFS;

	nla_nest_end(msg, fपंचांग);
	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_send_pmsr_capa(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा sk_buff *msg)
अणु
	स्थिर काष्ठा cfg80211_pmsr_capabilities *cap = rdev->wiphy.pmsr_capa;
	काष्ठा nlattr *pmsr, *caps;

	अगर (!cap)
		वापस 0;

	/*
	 * we करोn't need to clean up anything here since the caller
	 * will genlmsg_cancel() अगर we fail
	 */

	pmsr = nla_nest_start_noflag(msg, NL80211_ATTR_PEER_MEASUREMENTS);
	अगर (!pmsr)
		वापस -ENOBUFS;

	अगर (nla_put_u32(msg, NL80211_PMSR_ATTR_MAX_PEERS, cap->max_peers))
		वापस -ENOBUFS;

	अगर (cap->report_ap_tsf &&
	    nla_put_flag(msg, NL80211_PMSR_ATTR_REPORT_AP_TSF))
		वापस -ENOBUFS;

	अगर (cap->अक्रमomize_mac_addr &&
	    nla_put_flag(msg, NL80211_PMSR_ATTR_RANDOMIZE_MAC_ADDR))
		वापस -ENOBUFS;

	caps = nla_nest_start_noflag(msg, NL80211_PMSR_ATTR_TYPE_CAPA);
	अगर (!caps)
		वापस -ENOBUFS;

	अगर (nl80211_send_pmsr_fपंचांग_capa(cap, msg))
		वापस -ENOBUFS;

	nla_nest_end(msg, caps);
	nla_nest_end(msg, pmsr);

	वापस 0;
पूर्ण

अटल पूर्णांक
nl80211_put_अगरtype_akm_suites(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा sk_buff *msg)
अणु
	पूर्णांक i;
	काष्ठा nlattr *nested, *nested_akms;
	स्थिर काष्ठा wiphy_अगरtype_akm_suites *अगरtype_akms;

	अगर (!rdev->wiphy.num_अगरtype_akm_suites ||
	    !rdev->wiphy.अगरtype_akm_suites)
		वापस 0;

	nested = nla_nest_start(msg, NL80211_ATTR_IFTYPE_AKM_SUITES);
	अगर (!nested)
		वापस -ENOBUFS;

	क्रम (i = 0; i < rdev->wiphy.num_अगरtype_akm_suites; i++) अणु
		nested_akms = nla_nest_start(msg, i + 1);
		अगर (!nested_akms)
			वापस -ENOBUFS;

		अगरtype_akms = &rdev->wiphy.अगरtype_akm_suites[i];

		अगर (nl80211_put_अगरtypes(msg, NL80211_IFTYPE_AKM_ATTR_IFTYPES,
					अगरtype_akms->अगरtypes_mask))
			वापस -ENOBUFS;

		अगर (nla_put(msg, NL80211_IFTYPE_AKM_ATTR_SUITES,
			    माप(u32) * अगरtype_akms->n_akm_suites,
			    अगरtype_akms->akm_suites)) अणु
			वापस -ENOBUFS;
		पूर्ण
		nla_nest_end(msg, nested_akms);
	पूर्ण

	nla_nest_end(msg, nested);

	वापस 0;
पूर्ण

अटल पूर्णांक
nl80211_put_tid_config_support(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा sk_buff *msg)
अणु
	काष्ठा nlattr *supp;

	अगर (!rdev->wiphy.tid_config_support.vअगर &&
	    !rdev->wiphy.tid_config_support.peer)
		वापस 0;

	supp = nla_nest_start(msg, NL80211_ATTR_TID_CONFIG);
	अगर (!supp)
		वापस -ENOSPC;

	अगर (rdev->wiphy.tid_config_support.vअगर &&
	    nla_put_u64_64bit(msg, NL80211_TID_CONFIG_ATTR_VIF_SUPP,
			      rdev->wiphy.tid_config_support.vअगर,
			      NL80211_TID_CONFIG_ATTR_PAD))
		जाओ fail;

	अगर (rdev->wiphy.tid_config_support.peer &&
	    nla_put_u64_64bit(msg, NL80211_TID_CONFIG_ATTR_PEER_SUPP,
			      rdev->wiphy.tid_config_support.peer,
			      NL80211_TID_CONFIG_ATTR_PAD))
		जाओ fail;

	/* क्रम now we just use the same value ... makes more sense */
	अगर (nla_put_u8(msg, NL80211_TID_CONFIG_ATTR_RETRY_SHORT,
		       rdev->wiphy.tid_config_support.max_retry))
		जाओ fail;
	अगर (nla_put_u8(msg, NL80211_TID_CONFIG_ATTR_RETRY_LONG,
		       rdev->wiphy.tid_config_support.max_retry))
		जाओ fail;

	nla_nest_end(msg, supp);

	वापस 0;
fail:
	nla_nest_cancel(msg, supp);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक
nl80211_put_sar_specs(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा sk_buff *msg)
अणु
	काष्ठा nlattr *sar_capa, *specs, *sub_freq_range;
	u8 num_freq_ranges;
	पूर्णांक i;

	अगर (!rdev->wiphy.sar_capa)
		वापस 0;

	num_freq_ranges = rdev->wiphy.sar_capa->num_freq_ranges;

	sar_capa = nla_nest_start(msg, NL80211_ATTR_SAR_SPEC);
	अगर (!sar_capa)
		वापस -ENOSPC;

	अगर (nla_put_u32(msg, NL80211_SAR_ATTR_TYPE, rdev->wiphy.sar_capa->type))
		जाओ fail;

	specs = nla_nest_start(msg, NL80211_SAR_ATTR_SPECS);
	अगर (!specs)
		जाओ fail;

	/* report supported freq_ranges */
	क्रम (i = 0; i < num_freq_ranges; i++) अणु
		sub_freq_range = nla_nest_start(msg, i + 1);
		अगर (!sub_freq_range)
			जाओ fail;

		अगर (nla_put_u32(msg, NL80211_SAR_ATTR_SPECS_START_FREQ,
				rdev->wiphy.sar_capa->freq_ranges[i].start_freq))
			जाओ fail;

		अगर (nla_put_u32(msg, NL80211_SAR_ATTR_SPECS_END_FREQ,
				rdev->wiphy.sar_capa->freq_ranges[i].end_freq))
			जाओ fail;

		nla_nest_end(msg, sub_freq_range);
	पूर्ण

	nla_nest_end(msg, specs);
	nla_nest_end(msg, sar_capa);

	वापस 0;
fail:
	nla_nest_cancel(msg, sar_capa);
	वापस -ENOBUFS;
पूर्ण

काष्ठा nl80211_dump_wiphy_state अणु
	s64 filter_wiphy;
	दीर्घ start;
	दीर्घ split_start, band_start, chan_start, capa_start;
	bool split;
पूर्ण;

अटल पूर्णांक nl80211_send_wiphy(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      क्रमागत nl80211_commands cmd,
			      काष्ठा sk_buff *msg, u32 portid, u32 seq,
			      पूर्णांक flags, काष्ठा nl80211_dump_wiphy_state *state)
अणु
	व्योम *hdr;
	काष्ठा nlattr *nl_bands, *nl_band;
	काष्ठा nlattr *nl_freqs, *nl_freq;
	काष्ठा nlattr *nl_cmds;
	क्रमागत nl80211_band band;
	काष्ठा ieee80211_channel *chan;
	पूर्णांक i;
	स्थिर काष्ठा ieee80211_txrx_stypes *mgmt_stypes =
				rdev->wiphy.mgmt_stypes;
	u32 features;

	hdr = nl80211hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr)
		वापस -ENOBUFS;

	अगर (WARN_ON(!state))
		वापस -EINVAL;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_string(msg, NL80211_ATTR_WIPHY_NAME,
			   wiphy_name(&rdev->wiphy)) ||
	    nla_put_u32(msg, NL80211_ATTR_GENERATION,
			cfg80211_rdev_list_generation))
		जाओ nla_put_failure;

	अगर (cmd != NL80211_CMD_NEW_WIPHY)
		जाओ finish;

	चयन (state->split_start) अणु
	हाल 0:
		अगर (nla_put_u8(msg, NL80211_ATTR_WIPHY_RETRY_SHORT,
			       rdev->wiphy.retry_लघु) ||
		    nla_put_u8(msg, NL80211_ATTR_WIPHY_RETRY_LONG,
			       rdev->wiphy.retry_दीर्घ) ||
		    nla_put_u32(msg, NL80211_ATTR_WIPHY_FRAG_THRESHOLD,
				rdev->wiphy.frag_threshold) ||
		    nla_put_u32(msg, NL80211_ATTR_WIPHY_RTS_THRESHOLD,
				rdev->wiphy.rts_threshold) ||
		    nla_put_u8(msg, NL80211_ATTR_WIPHY_COVERAGE_CLASS,
			       rdev->wiphy.coverage_class) ||
		    nla_put_u8(msg, NL80211_ATTR_MAX_NUM_SCAN_SSIDS,
			       rdev->wiphy.max_scan_ssids) ||
		    nla_put_u8(msg, NL80211_ATTR_MAX_NUM_SCHED_SCAN_SSIDS,
			       rdev->wiphy.max_sched_scan_ssids) ||
		    nla_put_u16(msg, NL80211_ATTR_MAX_SCAN_IE_LEN,
				rdev->wiphy.max_scan_ie_len) ||
		    nla_put_u16(msg, NL80211_ATTR_MAX_SCHED_SCAN_IE_LEN,
				rdev->wiphy.max_sched_scan_ie_len) ||
		    nla_put_u8(msg, NL80211_ATTR_MAX_MATCH_SETS,
			       rdev->wiphy.max_match_sets))
			जाओ nla_put_failure;

		अगर ((rdev->wiphy.flags & WIPHY_FLAG_IBSS_RSN) &&
		    nla_put_flag(msg, NL80211_ATTR_SUPPORT_IBSS_RSN))
			जाओ nla_put_failure;
		अगर ((rdev->wiphy.flags & WIPHY_FLAG_MESH_AUTH) &&
		    nla_put_flag(msg, NL80211_ATTR_SUPPORT_MESH_AUTH))
			जाओ nla_put_failure;
		अगर ((rdev->wiphy.flags & WIPHY_FLAG_AP_UAPSD) &&
		    nla_put_flag(msg, NL80211_ATTR_SUPPORT_AP_UAPSD))
			जाओ nla_put_failure;
		अगर ((rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_FW_ROAM) &&
		    nla_put_flag(msg, NL80211_ATTR_ROAM_SUPPORT))
			जाओ nla_put_failure;
		अगर ((rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_TDLS) &&
		    nla_put_flag(msg, NL80211_ATTR_TDLS_SUPPORT))
			जाओ nla_put_failure;
		अगर ((rdev->wiphy.flags & WIPHY_FLAG_TDLS_EXTERNAL_SETUP) &&
		    nla_put_flag(msg, NL80211_ATTR_TDLS_EXTERNAL_SETUP))
			जाओ nla_put_failure;
		state->split_start++;
		अगर (state->split)
			अवरोध;
		fallthrough;
	हाल 1:
		अगर (nla_put(msg, NL80211_ATTR_CIPHER_SUITES,
			    माप(u32) * rdev->wiphy.n_cipher_suites,
			    rdev->wiphy.cipher_suites))
			जाओ nla_put_failure;

		अगर (nla_put_u8(msg, NL80211_ATTR_MAX_NUM_PMKIDS,
			       rdev->wiphy.max_num_pmkids))
			जाओ nla_put_failure;

		अगर ((rdev->wiphy.flags & WIPHY_FLAG_CONTROL_PORT_PROTOCOL) &&
		    nla_put_flag(msg, NL80211_ATTR_CONTROL_PORT_ETHERTYPE))
			जाओ nla_put_failure;

		अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY_ANTENNA_AVAIL_TX,
				rdev->wiphy.available_antennas_tx) ||
		    nla_put_u32(msg, NL80211_ATTR_WIPHY_ANTENNA_AVAIL_RX,
				rdev->wiphy.available_antennas_rx))
			जाओ nla_put_failure;

		अगर ((rdev->wiphy.flags & WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD) &&
		    nla_put_u32(msg, NL80211_ATTR_PROBE_RESP_OFFLOAD,
				rdev->wiphy.probe_resp_offload))
			जाओ nla_put_failure;

		अगर ((rdev->wiphy.available_antennas_tx ||
		     rdev->wiphy.available_antennas_rx) &&
		    rdev->ops->get_antenna) अणु
			u32 tx_ant = 0, rx_ant = 0;
			पूर्णांक res;

			res = rdev_get_antenna(rdev, &tx_ant, &rx_ant);
			अगर (!res) अणु
				अगर (nla_put_u32(msg,
						NL80211_ATTR_WIPHY_ANTENNA_TX,
						tx_ant) ||
				    nla_put_u32(msg,
						NL80211_ATTR_WIPHY_ANTENNA_RX,
						rx_ant))
					जाओ nla_put_failure;
			पूर्ण
		पूर्ण

		state->split_start++;
		अगर (state->split)
			अवरोध;
		fallthrough;
	हाल 2:
		अगर (nl80211_put_अगरtypes(msg, NL80211_ATTR_SUPPORTED_IFTYPES,
					rdev->wiphy.पूर्णांकerface_modes))
				जाओ nla_put_failure;
		state->split_start++;
		अगर (state->split)
			अवरोध;
		fallthrough;
	हाल 3:
		nl_bands = nla_nest_start_noflag(msg,
						 NL80211_ATTR_WIPHY_BANDS);
		अगर (!nl_bands)
			जाओ nla_put_failure;

		क्रम (band = state->band_start;
		     band < NUM_NL80211_BANDS; band++) अणु
			काष्ठा ieee80211_supported_band *sband;

			/* omit higher bands क्रम ancient software */
			अगर (band > NL80211_BAND_5GHZ && !state->split)
				अवरोध;

			sband = rdev->wiphy.bands[band];

			अगर (!sband)
				जारी;

			nl_band = nla_nest_start_noflag(msg, band);
			अगर (!nl_band)
				जाओ nla_put_failure;

			चयन (state->chan_start) अणु
			हाल 0:
				अगर (nl80211_send_band_rateinfo(msg, sband,
							       state->split))
					जाओ nla_put_failure;
				state->chan_start++;
				अगर (state->split)
					अवरोध;
				fallthrough;
			शेष:
				/* add frequencies */
				nl_freqs = nla_nest_start_noflag(msg,
								 NL80211_BAND_ATTR_FREQS);
				अगर (!nl_freqs)
					जाओ nla_put_failure;

				क्रम (i = state->chan_start - 1;
				     i < sband->n_channels;
				     i++) अणु
					nl_freq = nla_nest_start_noflag(msg,
									i);
					अगर (!nl_freq)
						जाओ nla_put_failure;

					chan = &sband->channels[i];

					अगर (nl80211_msg_put_channel(
							msg, &rdev->wiphy, chan,
							state->split))
						जाओ nla_put_failure;

					nla_nest_end(msg, nl_freq);
					अगर (state->split)
						अवरोध;
				पूर्ण
				अगर (i < sband->n_channels)
					state->chan_start = i + 2;
				अन्यथा
					state->chan_start = 0;
				nla_nest_end(msg, nl_freqs);
			पूर्ण

			nla_nest_end(msg, nl_band);

			अगर (state->split) अणु
				/* start again here */
				अगर (state->chan_start)
					band--;
				अवरोध;
			पूर्ण
		पूर्ण
		nla_nest_end(msg, nl_bands);

		अगर (band < NUM_NL80211_BANDS)
			state->band_start = band + 1;
		अन्यथा
			state->band_start = 0;

		/* अगर bands & channels are करोne, जारी outside */
		अगर (state->band_start == 0 && state->chan_start == 0)
			state->split_start++;
		अगर (state->split)
			अवरोध;
		fallthrough;
	हाल 4:
		nl_cmds = nla_nest_start_noflag(msg,
						NL80211_ATTR_SUPPORTED_COMMANDS);
		अगर (!nl_cmds)
			जाओ nla_put_failure;

		i = nl80211_add_commands_unsplit(rdev, msg);
		अगर (i < 0)
			जाओ nla_put_failure;
		अगर (state->split) अणु
			CMD(crit_proto_start, CRIT_PROTOCOL_START);
			CMD(crit_proto_stop, CRIT_PROTOCOL_STOP);
			अगर (rdev->wiphy.flags & WIPHY_FLAG_HAS_CHANNEL_SWITCH)
				CMD(channel_चयन, CHANNEL_SWITCH);
			CMD(set_qos_map, SET_QOS_MAP);
			अगर (rdev->wiphy.features &
					NL80211_FEATURE_SUPPORTS_WMM_ADMISSION)
				CMD(add_tx_ts, ADD_TX_TS);
			CMD(set_multicast_to_unicast, SET_MULTICAST_TO_UNICAST);
			CMD(update_connect_params, UPDATE_CONNECT_PARAMS);
			CMD(update_ft_ies, UPDATE_FT_IES);
			अगर (rdev->wiphy.sar_capa)
				CMD(set_sar_specs, SET_SAR_SPECS);
		पूर्ण
#अघोषित CMD

		nla_nest_end(msg, nl_cmds);
		state->split_start++;
		अगर (state->split)
			अवरोध;
		fallthrough;
	हाल 5:
		अगर (rdev->ops->reमुख्य_on_channel &&
		    (rdev->wiphy.flags & WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL) &&
		    nla_put_u32(msg,
				NL80211_ATTR_MAX_REMAIN_ON_CHANNEL_DURATION,
				rdev->wiphy.max_reमुख्य_on_channel_duration))
			जाओ nla_put_failure;

		अगर ((rdev->wiphy.flags & WIPHY_FLAG_OFFCHAN_TX) &&
		    nla_put_flag(msg, NL80211_ATTR_OFFCHANNEL_TX_OK))
			जाओ nla_put_failure;

		state->split_start++;
		अगर (state->split)
			अवरोध;
		fallthrough;
	हाल 6:
#अगर_घोषित CONFIG_PM
		अगर (nl80211_send_wowlan(msg, rdev, state->split))
			जाओ nla_put_failure;
		state->split_start++;
		अगर (state->split)
			अवरोध;
#अन्यथा
		state->split_start++;
#पूर्ण_अगर
		fallthrough;
	हाल 7:
		अगर (nl80211_put_अगरtypes(msg, NL80211_ATTR_SOFTWARE_IFTYPES,
					rdev->wiphy.software_अगरtypes))
			जाओ nla_put_failure;

		अगर (nl80211_put_अगरace_combinations(&rdev->wiphy, msg,
						   state->split))
			जाओ nla_put_failure;

		state->split_start++;
		अगर (state->split)
			अवरोध;
		fallthrough;
	हाल 8:
		अगर ((rdev->wiphy.flags & WIPHY_FLAG_HAVE_AP_SME) &&
		    nla_put_u32(msg, NL80211_ATTR_DEVICE_AP_SME,
				rdev->wiphy.ap_sme_capa))
			जाओ nla_put_failure;

		features = rdev->wiphy.features;
		/*
		 * We can only add the per-channel limit inक्रमmation अगर the
		 * dump is split, otherwise it makes it too big. Thereक्रमe
		 * only advertise it in that हाल.
		 */
		अगर (state->split)
			features |= NL80211_FEATURE_ADVERTISE_CHAN_LIMITS;
		अगर (nla_put_u32(msg, NL80211_ATTR_FEATURE_FLAGS, features))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.ht_capa_mod_mask &&
		    nla_put(msg, NL80211_ATTR_HT_CAPABILITY_MASK,
			    माप(*rdev->wiphy.ht_capa_mod_mask),
			    rdev->wiphy.ht_capa_mod_mask))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.flags & WIPHY_FLAG_HAVE_AP_SME &&
		    rdev->wiphy.max_acl_mac_addrs &&
		    nla_put_u32(msg, NL80211_ATTR_MAC_ACL_MAX,
				rdev->wiphy.max_acl_mac_addrs))
			जाओ nla_put_failure;

		/*
		 * Any inक्रमmation below this poपूर्णांक is only available to
		 * applications that can deal with it being split. This
		 * helps ensure that newly added capabilities करोn't अवरोध
		 * older tools by overrunning their buffers.
		 *
		 * We still increment split_start so that in the split
		 * हाल we'll जारी with more data in the next round,
		 * but अवरोध unconditionally so unsplit data stops here.
		 */
		अगर (state->split)
			state->split_start++;
		अन्यथा
			state->split_start = 0;
		अवरोध;
	हाल 9:
		अगर (nl80211_send_mgmt_stypes(msg, mgmt_stypes))
			जाओ nla_put_failure;

		अगर (nla_put_u32(msg, NL80211_ATTR_MAX_NUM_SCHED_SCAN_PLANS,
				rdev->wiphy.max_sched_scan_plans) ||
		    nla_put_u32(msg, NL80211_ATTR_MAX_SCAN_PLAN_INTERVAL,
				rdev->wiphy.max_sched_scan_plan_पूर्णांकerval) ||
		    nla_put_u32(msg, NL80211_ATTR_MAX_SCAN_PLAN_ITERATIONS,
				rdev->wiphy.max_sched_scan_plan_iterations))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.extended_capabilities &&
		    (nla_put(msg, NL80211_ATTR_EXT_CAPA,
			     rdev->wiphy.extended_capabilities_len,
			     rdev->wiphy.extended_capabilities) ||
		     nla_put(msg, NL80211_ATTR_EXT_CAPA_MASK,
			     rdev->wiphy.extended_capabilities_len,
			     rdev->wiphy.extended_capabilities_mask)))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.vht_capa_mod_mask &&
		    nla_put(msg, NL80211_ATTR_VHT_CAPABILITY_MASK,
			    माप(*rdev->wiphy.vht_capa_mod_mask),
			    rdev->wiphy.vht_capa_mod_mask))
			जाओ nla_put_failure;

		अगर (nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN,
			    rdev->wiphy.perm_addr))
			जाओ nla_put_failure;

		अगर (!is_zero_ether_addr(rdev->wiphy.addr_mask) &&
		    nla_put(msg, NL80211_ATTR_MAC_MASK, ETH_ALEN,
			    rdev->wiphy.addr_mask))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.n_addresses > 1) अणु
			व्योम *attr;

			attr = nla_nest_start(msg, NL80211_ATTR_MAC_ADDRS);
			अगर (!attr)
				जाओ nla_put_failure;

			क्रम (i = 0; i < rdev->wiphy.n_addresses; i++)
				अगर (nla_put(msg, i + 1, ETH_ALEN,
					    rdev->wiphy.addresses[i].addr))
					जाओ nla_put_failure;

			nla_nest_end(msg, attr);
		पूर्ण

		state->split_start++;
		अवरोध;
	हाल 10:
		अगर (nl80211_send_coalesce(msg, rdev))
			जाओ nla_put_failure;

		अगर ((rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_5_10_MHZ) &&
		    (nla_put_flag(msg, NL80211_ATTR_SUPPORT_5_MHZ) ||
		     nla_put_flag(msg, NL80211_ATTR_SUPPORT_10_MHZ)))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.max_ap_assoc_sta &&
		    nla_put_u32(msg, NL80211_ATTR_MAX_AP_ASSOC_STA,
				rdev->wiphy.max_ap_assoc_sta))
			जाओ nla_put_failure;

		state->split_start++;
		अवरोध;
	हाल 11:
		अगर (rdev->wiphy.n_venकरोr_commands) अणु
			स्थिर काष्ठा nl80211_venकरोr_cmd_info *info;
			काष्ठा nlattr *nested;

			nested = nla_nest_start_noflag(msg,
						       NL80211_ATTR_VENDOR_DATA);
			अगर (!nested)
				जाओ nla_put_failure;

			क्रम (i = 0; i < rdev->wiphy.n_venकरोr_commands; i++) अणु
				info = &rdev->wiphy.venकरोr_commands[i].info;
				अगर (nla_put(msg, i + 1, माप(*info), info))
					जाओ nla_put_failure;
			पूर्ण
			nla_nest_end(msg, nested);
		पूर्ण

		अगर (rdev->wiphy.n_venकरोr_events) अणु
			स्थिर काष्ठा nl80211_venकरोr_cmd_info *info;
			काष्ठा nlattr *nested;

			nested = nla_nest_start_noflag(msg,
						       NL80211_ATTR_VENDOR_EVENTS);
			अगर (!nested)
				जाओ nla_put_failure;

			क्रम (i = 0; i < rdev->wiphy.n_venकरोr_events; i++) अणु
				info = &rdev->wiphy.venकरोr_events[i];
				अगर (nla_put(msg, i + 1, माप(*info), info))
					जाओ nla_put_failure;
			पूर्ण
			nla_nest_end(msg, nested);
		पूर्ण
		state->split_start++;
		अवरोध;
	हाल 12:
		अगर (rdev->wiphy.flags & WIPHY_FLAG_HAS_CHANNEL_SWITCH &&
		    nla_put_u8(msg, NL80211_ATTR_MAX_CSA_COUNTERS,
			       rdev->wiphy.max_num_csa_counters))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED &&
		    nla_put_flag(msg, NL80211_ATTR_WIPHY_SELF_MANAGED_REG))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.max_sched_scan_reqs &&
		    nla_put_u32(msg, NL80211_ATTR_SCHED_SCAN_MAX_REQS,
				rdev->wiphy.max_sched_scan_reqs))
			जाओ nla_put_failure;

		अगर (nla_put(msg, NL80211_ATTR_EXT_FEATURES,
			    माप(rdev->wiphy.ext_features),
			    rdev->wiphy.ext_features))
			जाओ nla_put_failure;

		अगर (rdev->wiphy.bss_select_support) अणु
			काष्ठा nlattr *nested;
			u32 bss_select_support = rdev->wiphy.bss_select_support;

			nested = nla_nest_start_noflag(msg,
						       NL80211_ATTR_BSS_SELECT);
			अगर (!nested)
				जाओ nla_put_failure;

			i = 0;
			जबतक (bss_select_support) अणु
				अगर ((bss_select_support & 1) &&
				    nla_put_flag(msg, i))
					जाओ nla_put_failure;
				i++;
				bss_select_support >>= 1;
			पूर्ण
			nla_nest_end(msg, nested);
		पूर्ण

		state->split_start++;
		अवरोध;
	हाल 13:
		अगर (rdev->wiphy.num_अगरtype_ext_capab &&
		    rdev->wiphy.अगरtype_ext_capab) अणु
			काष्ठा nlattr *nested_ext_capab, *nested;

			nested = nla_nest_start_noflag(msg,
						       NL80211_ATTR_IFTYPE_EXT_CAPA);
			अगर (!nested)
				जाओ nla_put_failure;

			क्रम (i = state->capa_start;
			     i < rdev->wiphy.num_अगरtype_ext_capab; i++) अणु
				स्थिर काष्ठा wiphy_अगरtype_ext_capab *capab;

				capab = &rdev->wiphy.अगरtype_ext_capab[i];

				nested_ext_capab = nla_nest_start_noflag(msg,
									 i);
				अगर (!nested_ext_capab ||
				    nla_put_u32(msg, NL80211_ATTR_IFTYPE,
						capab->अगरtype) ||
				    nla_put(msg, NL80211_ATTR_EXT_CAPA,
					    capab->extended_capabilities_len,
					    capab->extended_capabilities) ||
				    nla_put(msg, NL80211_ATTR_EXT_CAPA_MASK,
					    capab->extended_capabilities_len,
					    capab->extended_capabilities_mask))
					जाओ nla_put_failure;

				nla_nest_end(msg, nested_ext_capab);
				अगर (state->split)
					अवरोध;
			पूर्ण
			nla_nest_end(msg, nested);
			अगर (i < rdev->wiphy.num_अगरtype_ext_capab) अणु
				state->capa_start = i + 1;
				अवरोध;
			पूर्ण
		पूर्ण

		अगर (nla_put_u32(msg, NL80211_ATTR_BANDS,
				rdev->wiphy.nan_supported_bands))
			जाओ nla_put_failure;

		अगर (wiphy_ext_feature_isset(&rdev->wiphy,
					    NL80211_EXT_FEATURE_TXQS)) अणु
			काष्ठा cfg80211_txq_stats txqstats = अणुपूर्ण;
			पूर्णांक res;

			res = rdev_get_txq_stats(rdev, शून्य, &txqstats);
			अगर (!res &&
			    !nl80211_put_txq_stats(msg, &txqstats,
						   NL80211_ATTR_TXQ_STATS))
				जाओ nla_put_failure;

			अगर (nla_put_u32(msg, NL80211_ATTR_TXQ_LIMIT,
					rdev->wiphy.txq_limit))
				जाओ nla_put_failure;
			अगर (nla_put_u32(msg, NL80211_ATTR_TXQ_MEMORY_LIMIT,
					rdev->wiphy.txq_memory_limit))
				जाओ nla_put_failure;
			अगर (nla_put_u32(msg, NL80211_ATTR_TXQ_QUANTUM,
					rdev->wiphy.txq_quantum))
				जाओ nla_put_failure;
		पूर्ण

		state->split_start++;
		अवरोध;
	हाल 14:
		अगर (nl80211_send_pmsr_capa(rdev, msg))
			जाओ nla_put_failure;

		state->split_start++;
		अवरोध;
	हाल 15:
		अगर (rdev->wiphy.akm_suites &&
		    nla_put(msg, NL80211_ATTR_AKM_SUITES,
			    माप(u32) * rdev->wiphy.n_akm_suites,
			    rdev->wiphy.akm_suites))
			जाओ nla_put_failure;

		अगर (nl80211_put_अगरtype_akm_suites(rdev, msg))
			जाओ nla_put_failure;

		अगर (nl80211_put_tid_config_support(rdev, msg))
			जाओ nla_put_failure;
		state->split_start++;
		अवरोध;
	हाल 16:
		अगर (nl80211_put_sar_specs(rdev, msg))
			जाओ nla_put_failure;

		/* करोne */
		state->split_start = 0;
		अवरोध;
	पूर्ण
 finish:
	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_dump_wiphy_parse(काष्ठा sk_buff *skb,
				    काष्ठा netlink_callback *cb,
				    काष्ठा nl80211_dump_wiphy_state *state)
अणु
	काष्ठा nlattr **tb = kसुस्मृति(NUM_NL80211_ATTR, माप(*tb), GFP_KERNEL);
	पूर्णांक ret;

	अगर (!tb)
		वापस -ENOMEM;

	ret = nlmsg_parse_deprecated(cb->nlh,
				     GENL_HDRLEN + nl80211_fam.hdrsize,
				     tb, nl80211_fam.maxattr,
				     nl80211_policy, शून्य);
	/* ignore parse errors क्रम backward compatibility */
	अगर (ret) अणु
		ret = 0;
		जाओ out;
	पूर्ण

	state->split = tb[NL80211_ATTR_SPLIT_WIPHY_DUMP];
	अगर (tb[NL80211_ATTR_WIPHY])
		state->filter_wiphy = nla_get_u32(tb[NL80211_ATTR_WIPHY]);
	अगर (tb[NL80211_ATTR_WDEV])
		state->filter_wiphy = nla_get_u64(tb[NL80211_ATTR_WDEV]) >> 32;
	अगर (tb[NL80211_ATTR_IFINDEX]) अणु
		काष्ठा net_device *netdev;
		काष्ठा cfg80211_रेजिस्टरed_device *rdev;
		पूर्णांक अगरidx = nla_get_u32(tb[NL80211_ATTR_IFINDEX]);

		netdev = __dev_get_by_index(sock_net(skb->sk), अगरidx);
		अगर (!netdev) अणु
			ret = -ENODEV;
			जाओ out;
		पूर्ण
		अगर (netdev->ieee80211_ptr) अणु
			rdev = wiphy_to_rdev(
				netdev->ieee80211_ptr->wiphy);
			state->filter_wiphy = rdev->wiphy_idx;
		पूर्ण
	पूर्ण

	ret = 0;
out:
	kमुक्त(tb);
	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_dump_wiphy(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक idx = 0, ret;
	काष्ठा nl80211_dump_wiphy_state *state = (व्योम *)cb->args[0];
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;

	rtnl_lock();
	अगर (!state) अणु
		state = kzalloc(माप(*state), GFP_KERNEL);
		अगर (!state) अणु
			rtnl_unlock();
			वापस -ENOMEM;
		पूर्ण
		state->filter_wiphy = -1;
		ret = nl80211_dump_wiphy_parse(skb, cb, state);
		अगर (ret) अणु
			kमुक्त(state);
			rtnl_unlock();
			वापस ret;
		पूर्ण
		cb->args[0] = (दीर्घ)state;
	पूर्ण

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		अगर (!net_eq(wiphy_net(&rdev->wiphy), sock_net(skb->sk)))
			जारी;
		अगर (++idx <= state->start)
			जारी;
		अगर (state->filter_wiphy != -1 &&
		    state->filter_wiphy != rdev->wiphy_idx)
			जारी;
		/* attempt to fit multiple wiphy data chunks पूर्णांकo the skb */
		करो अणु
			ret = nl80211_send_wiphy(rdev, NL80211_CMD_NEW_WIPHY,
						 skb,
						 NETLINK_CB(cb->skb).portid,
						 cb->nlh->nlmsg_seq,
						 NLM_F_MULTI, state);
			अगर (ret < 0) अणु
				/*
				 * If sending the wiphy data didn't fit (ENOBUFS
				 * or EMSGSIZE वापसed), this SKB is still
				 * empty (so it's not too big because another
				 * wiphy dataset is alपढ़ोy in the skb) and
				 * we've not tried to adjust the dump allocation
				 * yet ... then adjust the alloc size to be
				 * bigger, and वापस 1 but with the empty skb.
				 * This results in an empty message being RX'ed
				 * in userspace, but that is ignored.
				 *
				 * We can then retry with the larger buffer.
				 */
				अगर ((ret == -ENOBUFS || ret == -EMSGSIZE) &&
				    !skb->len && !state->split &&
				    cb->min_dump_alloc < 4096) अणु
					cb->min_dump_alloc = 4096;
					state->split_start = 0;
					rtnl_unlock();
					वापस 1;
				पूर्ण
				idx--;
				अवरोध;
			पूर्ण
		पूर्ण जबतक (state->split_start > 0);
		अवरोध;
	पूर्ण
	rtnl_unlock();

	state->start = idx;

	वापस skb->len;
पूर्ण

अटल पूर्णांक nl80211_dump_wiphy_करोne(काष्ठा netlink_callback *cb)
अणु
	kमुक्त((व्योम *)cb->args[0]);
	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_get_wiphy(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा nl80211_dump_wiphy_state state = अणुपूर्ण;

	msg = nlmsg_new(4096, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nl80211_send_wiphy(rdev, NL80211_CMD_NEW_WIPHY, msg,
			       info->snd_portid, info->snd_seq, 0,
			       &state) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल स्थिर काष्ठा nla_policy txq_params_policy[NL80211_TXQ_ATTR_MAX + 1] = अणु
	[NL80211_TXQ_ATTR_QUEUE]		= अणु .type = NLA_U8 पूर्ण,
	[NL80211_TXQ_ATTR_TXOP]			= अणु .type = NLA_U16 पूर्ण,
	[NL80211_TXQ_ATTR_CWMIN]		= अणु .type = NLA_U16 पूर्ण,
	[NL80211_TXQ_ATTR_CWMAX]		= अणु .type = NLA_U16 पूर्ण,
	[NL80211_TXQ_ATTR_AIFS]			= अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक parse_txq_params(काष्ठा nlattr *tb[],
			    काष्ठा ieee80211_txq_params *txq_params)
अणु
	u8 ac;

	अगर (!tb[NL80211_TXQ_ATTR_AC] || !tb[NL80211_TXQ_ATTR_TXOP] ||
	    !tb[NL80211_TXQ_ATTR_CWMIN] || !tb[NL80211_TXQ_ATTR_CWMAX] ||
	    !tb[NL80211_TXQ_ATTR_AIFS])
		वापस -EINVAL;

	ac = nla_get_u8(tb[NL80211_TXQ_ATTR_AC]);
	txq_params->txop = nla_get_u16(tb[NL80211_TXQ_ATTR_TXOP]);
	txq_params->cwmin = nla_get_u16(tb[NL80211_TXQ_ATTR_CWMIN]);
	txq_params->cwmax = nla_get_u16(tb[NL80211_TXQ_ATTR_CWMAX]);
	txq_params->aअगरs = nla_get_u8(tb[NL80211_TXQ_ATTR_AIFS]);

	अगर (ac >= NL80211_NUM_ACS)
		वापस -EINVAL;
	txq_params->ac = array_index_nospec(ac, NL80211_NUM_ACS);
	वापस 0;
पूर्ण

अटल bool nl80211_can_set_dev_channel(काष्ठा wireless_dev *wdev)
अणु
	/*
	 * You can only set the channel explicitly क्रम some पूर्णांकerfaces,
	 * most have their channel managed via their respective
	 * "establish a connection" command (connect, join, ...)
	 *
	 * For AP/GO and mesh mode, the channel can be set with the
	 * channel userspace API, but is only stored and passed to the
	 * low-level driver when the AP starts or the mesh is joined.
	 * This is क्रम backward compatibility, userspace can also give
	 * the channel in the start-ap or join-mesh commands instead.
	 *
	 * Monitors are special as they are normally slaved to
	 * whatever अन्यथा is going on, so they have their own special
	 * operation to set the monitor channel अगर possible.
	 */
	वापस !wdev ||
		wdev->अगरtype == NL80211_IFTYPE_AP ||
		wdev->अगरtype == NL80211_IFTYPE_MESH_POINT ||
		wdev->अगरtype == NL80211_IFTYPE_MONITOR ||
		wdev->अगरtype == NL80211_IFTYPE_P2P_GO;
पूर्ण

पूर्णांक nl80211_parse_chandef(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा genl_info *info,
			  काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	काष्ठा nlattr **attrs = info->attrs;
	u32 control_freq;

	अगर (!attrs[NL80211_ATTR_WIPHY_FREQ])
		वापस -EINVAL;

	control_freq = MHZ_TO_KHZ(
			nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ]));
	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ_OFFSET])
		control_freq +=
		    nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ_OFFSET]);

	स_रखो(chandef, 0, माप(*chandef));
	chandef->chan = ieee80211_get_channel_khz(&rdev->wiphy, control_freq);
	chandef->width = NL80211_CHAN_WIDTH_20_NOHT;
	chandef->center_freq1 = KHZ_TO_MHZ(control_freq);
	chandef->freq1_offset = control_freq % 1000;
	chandef->center_freq2 = 0;

	/* Primary channel not allowed */
	अगर (!chandef->chan || chandef->chan->flags & IEEE80211_CHAN_DISABLED) अणु
		NL_SET_ERR_MSG_ATTR(extack, attrs[NL80211_ATTR_WIPHY_FREQ],
				    "Channel is disabled");
		वापस -EINVAL;
	पूर्ण

	अगर (attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]) अणु
		क्रमागत nl80211_channel_type chantype;

		chantype = nla_get_u32(attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE]);

		चयन (chantype) अणु
		हाल NL80211_CHAN_NO_HT:
		हाल NL80211_CHAN_HT20:
		हाल NL80211_CHAN_HT40PLUS:
		हाल NL80211_CHAN_HT40MINUS:
			cfg80211_chandef_create(chandef, chandef->chan,
						chantype);
			/* user input क्रम center_freq is incorrect */
			अगर (attrs[NL80211_ATTR_CENTER_FREQ1] &&
			    chandef->center_freq1 != nla_get_u32(attrs[NL80211_ATTR_CENTER_FREQ1])) अणु
				NL_SET_ERR_MSG_ATTR(extack,
						    attrs[NL80211_ATTR_CENTER_FREQ1],
						    "bad center frequency 1");
				वापस -EINVAL;
			पूर्ण
			/* center_freq2 must be zero */
			अगर (attrs[NL80211_ATTR_CENTER_FREQ2] &&
			    nla_get_u32(attrs[NL80211_ATTR_CENTER_FREQ2])) अणु
				NL_SET_ERR_MSG_ATTR(extack,
						    attrs[NL80211_ATTR_CENTER_FREQ2],
						    "center frequency 2 can't be used");
				वापस -EINVAL;
			पूर्ण
			अवरोध;
		शेष:
			NL_SET_ERR_MSG_ATTR(extack,
					    attrs[NL80211_ATTR_WIPHY_CHANNEL_TYPE],
					    "invalid channel type");
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अगर (attrs[NL80211_ATTR_CHANNEL_WIDTH]) अणु
		chandef->width =
			nla_get_u32(attrs[NL80211_ATTR_CHANNEL_WIDTH]);
		अगर (attrs[NL80211_ATTR_CENTER_FREQ1]) अणु
			chandef->center_freq1 =
				nla_get_u32(attrs[NL80211_ATTR_CENTER_FREQ1]);
			अगर (attrs[NL80211_ATTR_CENTER_FREQ1_OFFSET])
				chandef->freq1_offset = nla_get_u32(
				      attrs[NL80211_ATTR_CENTER_FREQ1_OFFSET]);
			अन्यथा
				chandef->freq1_offset = 0;
		पूर्ण
		अगर (attrs[NL80211_ATTR_CENTER_FREQ2])
			chandef->center_freq2 =
				nla_get_u32(attrs[NL80211_ATTR_CENTER_FREQ2]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_EDMG_CHANNELS]) अणु
		chandef->edmg.channels =
		      nla_get_u8(info->attrs[NL80211_ATTR_WIPHY_EDMG_CHANNELS]);

		अगर (info->attrs[NL80211_ATTR_WIPHY_EDMG_BW_CONFIG])
			chandef->edmg.bw_config =
		     nla_get_u8(info->attrs[NL80211_ATTR_WIPHY_EDMG_BW_CONFIG]);
	पूर्ण अन्यथा अणु
		chandef->edmg.bw_config = 0;
		chandef->edmg.channels = 0;
	पूर्ण

	अगर (!cfg80211_chandef_valid(chandef)) अणु
		NL_SET_ERR_MSG(extack, "invalid channel definition");
		वापस -EINVAL;
	पूर्ण

	अगर (!cfg80211_chandef_usable(&rdev->wiphy, chandef,
				     IEEE80211_CHAN_DISABLED)) अणु
		NL_SET_ERR_MSG(extack, "(extension) channel is disabled");
		वापस -EINVAL;
	पूर्ण

	अगर ((chandef->width == NL80211_CHAN_WIDTH_5 ||
	     chandef->width == NL80211_CHAN_WIDTH_10) &&
	    !(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_5_10_MHZ)) अणु
		NL_SET_ERR_MSG(extack, "5/10 MHz not supported");
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक __nl80211_set_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *dev,
				 काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_chan_def chandef;
	पूर्णांक result;
	क्रमागत nl80211_अगरtype अगरtype = NL80211_IFTYPE_MONITOR;
	काष्ठा wireless_dev *wdev = शून्य;

	अगर (dev)
		wdev = dev->ieee80211_ptr;
	अगर (!nl80211_can_set_dev_channel(wdev))
		वापस -EOPNOTSUPP;
	अगर (wdev)
		अगरtype = wdev->अगरtype;

	result = nl80211_parse_chandef(rdev, info, &chandef);
	अगर (result)
		वापस result;

	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		अगर (!cfg80211_reg_can_beacon_relax(&rdev->wiphy, &chandef,
						   अगरtype)) अणु
			result = -EINVAL;
			अवरोध;
		पूर्ण
		अगर (wdev->beacon_पूर्णांकerval) अणु
			अगर (!dev || !rdev->ops->set_ap_chanwidth ||
			    !(rdev->wiphy.features &
			      NL80211_FEATURE_AP_MODE_CHAN_WIDTH_CHANGE)) अणु
				result = -EBUSY;
				अवरोध;
			पूर्ण

			/* Only allow dynamic channel width changes */
			अगर (chandef.chan != wdev->preset_chandef.chan) अणु
				result = -EBUSY;
				अवरोध;
			पूर्ण
			result = rdev_set_ap_chanwidth(rdev, dev, &chandef);
			अगर (result)
				अवरोध;
		पूर्ण
		wdev->preset_chandef = chandef;
		result = 0;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		result = cfg80211_set_mesh_channel(rdev, wdev, &chandef);
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		result = cfg80211_set_monitor_channel(rdev, &chandef);
		अवरोध;
	शेष:
		result = -EINVAL;
	पूर्ण

	वापस result;
पूर्ण

अटल पूर्णांक nl80211_set_channel(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *netdev = info->user_ptr[1];

	वापस __nl80211_set_channel(rdev, netdev, info);
पूर्ण

अटल पूर्णांक nl80211_set_wiphy(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = शून्य;
	काष्ठा net_device *netdev = शून्य;
	काष्ठा wireless_dev *wdev;
	पूर्णांक result = 0, rem_txq_params = 0;
	काष्ठा nlattr *nl_txq_params;
	u32 changed;
	u8 retry_लघु = 0, retry_दीर्घ = 0;
	u32 frag_threshold = 0, rts_threshold = 0;
	u8 coverage_class = 0;
	u32 txq_limit = 0, txq_memory_limit = 0, txq_quantum = 0;

	rtnl_lock();
	/*
	 * Try to find the wiphy and netdev. Normally this
	 * function shouldn't need the netdev, but this is
	 * करोne क्रम backward compatibility -- previously
	 * setting the channel was करोne per wiphy, but now
	 * it is per netdev. Previous userland like hostapd
	 * also passed a netdev to set_wiphy, so that it is
	 * possible to let that go to the right netdev!
	 */

	अगर (info->attrs[NL80211_ATTR_IFINDEX]) अणु
		पूर्णांक अगरindex = nla_get_u32(info->attrs[NL80211_ATTR_IFINDEX]);

		netdev = __dev_get_by_index(genl_info_net(info), अगरindex);
		अगर (netdev && netdev->ieee80211_ptr)
			rdev = wiphy_to_rdev(netdev->ieee80211_ptr->wiphy);
		अन्यथा
			netdev = शून्य;
	पूर्ण

	अगर (!netdev) अणु
		rdev = __cfg80211_rdev_from_attrs(genl_info_net(info),
						  info->attrs);
		अगर (IS_ERR(rdev)) अणु
			rtnl_unlock();
			वापस PTR_ERR(rdev);
		पूर्ण
		wdev = शून्य;
		netdev = शून्य;
		result = 0;
	पूर्ण अन्यथा
		wdev = netdev->ieee80211_ptr;

	wiphy_lock(&rdev->wiphy);

	/*
	 * end workaround code, by now the rdev is available
	 * and locked, and wdev may or may not be शून्य.
	 */

	अगर (info->attrs[NL80211_ATTR_WIPHY_NAME])
		result = cfg80211_dev_नाम(
			rdev, nla_data(info->attrs[NL80211_ATTR_WIPHY_NAME]));
	rtnl_unlock();

	अगर (result)
		जाओ out;

	अगर (info->attrs[NL80211_ATTR_WIPHY_TXQ_PARAMS]) अणु
		काष्ठा ieee80211_txq_params txq_params;
		काष्ठा nlattr *tb[NL80211_TXQ_ATTR_MAX + 1];

		अगर (!rdev->ops->set_txq_params) अणु
			result = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		अगर (!netdev) अणु
			result = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (netdev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP &&
		    netdev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO) अणु
			result = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!netअगर_running(netdev)) अणु
			result = -ENETDOWN;
			जाओ out;
		पूर्ण

		nla_क्रम_each_nested(nl_txq_params,
				    info->attrs[NL80211_ATTR_WIPHY_TXQ_PARAMS],
				    rem_txq_params) अणु
			result = nla_parse_nested_deprecated(tb,
							     NL80211_TXQ_ATTR_MAX,
							     nl_txq_params,
							     txq_params_policy,
							     info->extack);
			अगर (result)
				जाओ out;
			result = parse_txq_params(tb, &txq_params);
			अगर (result)
				जाओ out;

			result = rdev_set_txq_params(rdev, netdev,
						     &txq_params);
			अगर (result)
				जाओ out;
		पूर्ण
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ]) अणु
		result = __nl80211_set_channel(
			rdev,
			nl80211_can_set_dev_channel(wdev) ? netdev : शून्य,
			info);
		अगर (result)
			जाओ out;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_TX_POWER_SETTING]) अणु
		काष्ठा wireless_dev *txp_wdev = wdev;
		क्रमागत nl80211_tx_घातer_setting type;
		पूर्णांक idx, mbm = 0;

		अगर (!(rdev->wiphy.features & NL80211_FEATURE_VIF_TXPOWER))
			txp_wdev = शून्य;

		अगर (!rdev->ops->set_tx_घातer) अणु
			result = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		idx = NL80211_ATTR_WIPHY_TX_POWER_SETTING;
		type = nla_get_u32(info->attrs[idx]);

		अगर (!info->attrs[NL80211_ATTR_WIPHY_TX_POWER_LEVEL] &&
		    (type != NL80211_TX_POWER_AUTOMATIC)) अणु
			result = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (type != NL80211_TX_POWER_AUTOMATIC) अणु
			idx = NL80211_ATTR_WIPHY_TX_POWER_LEVEL;
			mbm = nla_get_u32(info->attrs[idx]);
		पूर्ण

		result = rdev_set_tx_घातer(rdev, txp_wdev, type, mbm);
		अगर (result)
			जाओ out;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_ANTENNA_TX] &&
	    info->attrs[NL80211_ATTR_WIPHY_ANTENNA_RX]) अणु
		u32 tx_ant, rx_ant;

		अगर ((!rdev->wiphy.available_antennas_tx &&
		     !rdev->wiphy.available_antennas_rx) ||
		    !rdev->ops->set_antenna) अणु
			result = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		tx_ant = nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_ANTENNA_TX]);
		rx_ant = nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_ANTENNA_RX]);

		/* reject antenna configurations which करोn't match the
		 * available antenna masks, except क्रम the "all" mask */
		अगर ((~tx_ant && (tx_ant & ~rdev->wiphy.available_antennas_tx)) ||
		    (~rx_ant && (rx_ant & ~rdev->wiphy.available_antennas_rx))) अणु
			result = -EINVAL;
			जाओ out;
		पूर्ण

		tx_ant = tx_ant & rdev->wiphy.available_antennas_tx;
		rx_ant = rx_ant & rdev->wiphy.available_antennas_rx;

		result = rdev_set_antenna(rdev, tx_ant, rx_ant);
		अगर (result)
			जाओ out;
	पूर्ण

	changed = 0;

	अगर (info->attrs[NL80211_ATTR_WIPHY_RETRY_SHORT]) अणु
		retry_लघु = nla_get_u8(
			info->attrs[NL80211_ATTR_WIPHY_RETRY_SHORT]);

		changed |= WIPHY_PARAM_RETRY_SHORT;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_RETRY_LONG]) अणु
		retry_दीर्घ = nla_get_u8(
			info->attrs[NL80211_ATTR_WIPHY_RETRY_LONG]);

		changed |= WIPHY_PARAM_RETRY_LONG;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_FRAG_THRESHOLD]) अणु
		frag_threshold = nla_get_u32(
			info->attrs[NL80211_ATTR_WIPHY_FRAG_THRESHOLD]);
		अगर (frag_threshold < 256) अणु
			result = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (frag_threshold != (u32) -1) अणु
			/*
			 * Fragments (apart from the last one) are required to
			 * have even length. Make the fragmentation code
			 * simpler by stripping LSB should someone try to use
			 * odd threshold value.
			 */
			frag_threshold &= ~0x1;
		पूर्ण
		changed |= WIPHY_PARAM_FRAG_THRESHOLD;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_RTS_THRESHOLD]) अणु
		rts_threshold = nla_get_u32(
			info->attrs[NL80211_ATTR_WIPHY_RTS_THRESHOLD]);
		changed |= WIPHY_PARAM_RTS_THRESHOLD;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_COVERAGE_CLASS]) अणु
		अगर (info->attrs[NL80211_ATTR_WIPHY_DYN_ACK]) अणु
			result = -EINVAL;
			जाओ out;
		पूर्ण

		coverage_class = nla_get_u8(
			info->attrs[NL80211_ATTR_WIPHY_COVERAGE_CLASS]);
		changed |= WIPHY_PARAM_COVERAGE_CLASS;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_DYN_ACK]) अणु
		अगर (!(rdev->wiphy.features & NL80211_FEATURE_ACKTO_ESTIMATION)) अणु
			result = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		changed |= WIPHY_PARAM_DYN_ACK;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_TXQ_LIMIT]) अणु
		अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_TXQS)) अणु
			result = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		txq_limit = nla_get_u32(
			info->attrs[NL80211_ATTR_TXQ_LIMIT]);
		changed |= WIPHY_PARAM_TXQ_LIMIT;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_TXQ_MEMORY_LIMIT]) अणु
		अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_TXQS)) अणु
			result = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		txq_memory_limit = nla_get_u32(
			info->attrs[NL80211_ATTR_TXQ_MEMORY_LIMIT]);
		changed |= WIPHY_PARAM_TXQ_MEMORY_LIMIT;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_TXQ_QUANTUM]) अणु
		अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_TXQS)) अणु
			result = -EOPNOTSUPP;
			जाओ out;
		पूर्ण
		txq_quantum = nla_get_u32(
			info->attrs[NL80211_ATTR_TXQ_QUANTUM]);
		changed |= WIPHY_PARAM_TXQ_QUANTUM;
	पूर्ण

	अगर (changed) अणु
		u8 old_retry_लघु, old_retry_दीर्घ;
		u32 old_frag_threshold, old_rts_threshold;
		u8 old_coverage_class;
		u32 old_txq_limit, old_txq_memory_limit, old_txq_quantum;

		अगर (!rdev->ops->set_wiphy_params) अणु
			result = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		old_retry_लघु = rdev->wiphy.retry_लघु;
		old_retry_दीर्घ = rdev->wiphy.retry_दीर्घ;
		old_frag_threshold = rdev->wiphy.frag_threshold;
		old_rts_threshold = rdev->wiphy.rts_threshold;
		old_coverage_class = rdev->wiphy.coverage_class;
		old_txq_limit = rdev->wiphy.txq_limit;
		old_txq_memory_limit = rdev->wiphy.txq_memory_limit;
		old_txq_quantum = rdev->wiphy.txq_quantum;

		अगर (changed & WIPHY_PARAM_RETRY_SHORT)
			rdev->wiphy.retry_लघु = retry_लघु;
		अगर (changed & WIPHY_PARAM_RETRY_LONG)
			rdev->wiphy.retry_दीर्घ = retry_दीर्घ;
		अगर (changed & WIPHY_PARAM_FRAG_THRESHOLD)
			rdev->wiphy.frag_threshold = frag_threshold;
		अगर (changed & WIPHY_PARAM_RTS_THRESHOLD)
			rdev->wiphy.rts_threshold = rts_threshold;
		अगर (changed & WIPHY_PARAM_COVERAGE_CLASS)
			rdev->wiphy.coverage_class = coverage_class;
		अगर (changed & WIPHY_PARAM_TXQ_LIMIT)
			rdev->wiphy.txq_limit = txq_limit;
		अगर (changed & WIPHY_PARAM_TXQ_MEMORY_LIMIT)
			rdev->wiphy.txq_memory_limit = txq_memory_limit;
		अगर (changed & WIPHY_PARAM_TXQ_QUANTUM)
			rdev->wiphy.txq_quantum = txq_quantum;

		result = rdev_set_wiphy_params(rdev, changed);
		अगर (result) अणु
			rdev->wiphy.retry_लघु = old_retry_लघु;
			rdev->wiphy.retry_दीर्घ = old_retry_दीर्घ;
			rdev->wiphy.frag_threshold = old_frag_threshold;
			rdev->wiphy.rts_threshold = old_rts_threshold;
			rdev->wiphy.coverage_class = old_coverage_class;
			rdev->wiphy.txq_limit = old_txq_limit;
			rdev->wiphy.txq_memory_limit = old_txq_memory_limit;
			rdev->wiphy.txq_quantum = old_txq_quantum;
			जाओ out;
		पूर्ण
	पूर्ण

	result = 0;

out:
	wiphy_unlock(&rdev->wiphy);
	वापस result;
पूर्ण

अटल पूर्णांक nl80211_send_chandef(काष्ठा sk_buff *msg,
				स्थिर काष्ठा cfg80211_chan_def *chandef)
अणु
	अगर (WARN_ON(!cfg80211_chandef_valid(chandef)))
		वापस -EINVAL;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ,
			chandef->chan->center_freq))
		वापस -ENOBUFS;
	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ_OFFSET,
			chandef->chan->freq_offset))
		वापस -ENOBUFS;
	चयन (chandef->width) अणु
	हाल NL80211_CHAN_WIDTH_20_NOHT:
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_40:
		अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY_CHANNEL_TYPE,
				cfg80211_get_chandef_type(chandef)))
			वापस -ENOBUFS;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (nla_put_u32(msg, NL80211_ATTR_CHANNEL_WIDTH, chandef->width))
		वापस -ENOBUFS;
	अगर (nla_put_u32(msg, NL80211_ATTR_CENTER_FREQ1, chandef->center_freq1))
		वापस -ENOBUFS;
	अगर (chandef->center_freq2 &&
	    nla_put_u32(msg, NL80211_ATTR_CENTER_FREQ2, chandef->center_freq2))
		वापस -ENOBUFS;
	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_send_अगरace(काष्ठा sk_buff *msg, u32 portid, u32 seq, पूर्णांक flags,
			      काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			      काष्ठा wireless_dev *wdev,
			      क्रमागत nl80211_commands cmd)
अणु
	काष्ठा net_device *dev = wdev->netdev;
	व्योम *hdr;

	WARN_ON(cmd != NL80211_CMD_NEW_INTERFACE &&
		cmd != NL80211_CMD_DEL_INTERFACE &&
		cmd != NL80211_CMD_SET_INTERFACE);

	hdr = nl80211hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr)
		वापस -1;

	अगर (dev &&
	    (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	     nla_put_string(msg, NL80211_ATTR_IFNAME, dev->name)))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFTYPE, wdev->अगरtype) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, wdev_address(wdev)) ||
	    nla_put_u32(msg, NL80211_ATTR_GENERATION,
			rdev->devlist_generation ^
			(cfg80211_rdev_list_generation << 2)) ||
	    nla_put_u8(msg, NL80211_ATTR_4ADDR, wdev->use_4addr))
		जाओ nla_put_failure;

	अगर (rdev->ops->get_channel) अणु
		पूर्णांक ret;
		काष्ठा cfg80211_chan_def chandef = अणुपूर्ण;

		ret = rdev_get_channel(rdev, wdev, &chandef);
		अगर (ret == 0) अणु
			अगर (nl80211_send_chandef(msg, &chandef))
				जाओ nla_put_failure;
		पूर्ण
	पूर्ण

	अगर (rdev->ops->get_tx_घातer) अणु
		पूर्णांक dbm, ret;

		ret = rdev_get_tx_घातer(rdev, wdev, &dbm);
		अगर (ret == 0 &&
		    nla_put_u32(msg, NL80211_ATTR_WIPHY_TX_POWER_LEVEL,
				DBM_TO_MBM(dbm)))
			जाओ nla_put_failure;
	पूर्ण

	wdev_lock(wdev);
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
		अगर (wdev->ssid_len &&
		    nla_put(msg, NL80211_ATTR_SSID, wdev->ssid_len, wdev->ssid))
			जाओ nla_put_failure_locked;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_ADHOC: अणु
		स्थिर u8 *ssid_ie;
		अगर (!wdev->current_bss)
			अवरोध;
		rcu_पढ़ो_lock();
		ssid_ie = ieee80211_bss_get_ie(&wdev->current_bss->pub,
					       WLAN_EID_SSID);
		अगर (ssid_ie &&
		    nla_put(msg, NL80211_ATTR_SSID, ssid_ie[1], ssid_ie + 2))
			जाओ nla_put_failure_rcu_locked;
		rcu_पढ़ो_unlock();
		अवरोध;
		पूर्ण
	शेष:
		/* nothing */
		अवरोध;
	पूर्ण
	wdev_unlock(wdev);

	अगर (rdev->ops->get_txq_stats) अणु
		काष्ठा cfg80211_txq_stats txqstats = अणुपूर्ण;
		पूर्णांक ret = rdev_get_txq_stats(rdev, wdev, &txqstats);

		अगर (ret == 0 &&
		    !nl80211_put_txq_stats(msg, &txqstats,
					   NL80211_ATTR_TXQ_STATS))
			जाओ nla_put_failure;
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure_rcu_locked:
	rcu_पढ़ो_unlock();
 nla_put_failure_locked:
	wdev_unlock(wdev);
 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_dump_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	पूर्णांक wp_idx = 0;
	पूर्णांक अगर_idx = 0;
	पूर्णांक wp_start = cb->args[0];
	पूर्णांक अगर_start = cb->args[1];
	पूर्णांक filter_wiphy = -1;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;
	पूर्णांक ret;

	rtnl_lock();
	अगर (!cb->args[2]) अणु
		काष्ठा nl80211_dump_wiphy_state state = अणु
			.filter_wiphy = -1,
		पूर्ण;

		ret = nl80211_dump_wiphy_parse(skb, cb, &state);
		अगर (ret)
			जाओ out_unlock;

		filter_wiphy = state.filter_wiphy;

		/*
		 * अगर filtering, set cb->args[2] to +1 since 0 is the शेष
		 * value needed to determine that parsing is necessary.
		 */
		अगर (filter_wiphy >= 0)
			cb->args[2] = filter_wiphy + 1;
		अन्यथा
			cb->args[2] = -1;
	पूर्ण अन्यथा अगर (cb->args[2] > 0) अणु
		filter_wiphy = cb->args[2] - 1;
	पूर्ण

	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		अगर (!net_eq(wiphy_net(&rdev->wiphy), sock_net(skb->sk)))
			जारी;
		अगर (wp_idx < wp_start) अणु
			wp_idx++;
			जारी;
		पूर्ण

		अगर (filter_wiphy >= 0 && filter_wiphy != rdev->wiphy_idx)
			जारी;

		अगर_idx = 0;

		list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
			अगर (अगर_idx < अगर_start) अणु
				अगर_idx++;
				जारी;
			पूर्ण
			अगर (nl80211_send_अगरace(skb, NETLINK_CB(cb->skb).portid,
					       cb->nlh->nlmsg_seq, NLM_F_MULTI,
					       rdev, wdev,
					       NL80211_CMD_NEW_INTERFACE) < 0) अणु
				जाओ out;
			पूर्ण
			अगर_idx++;
		पूर्ण

		wp_idx++;
	पूर्ण
 out:
	cb->args[0] = wp_idx;
	cb->args[1] = अगर_idx;

	ret = skb->len;
 out_unlock:
	rtnl_unlock();

	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_get_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nl80211_send_अगरace(msg, info->snd_portid, info->snd_seq, 0,
			       rdev, wdev, NL80211_CMD_NEW_INTERFACE) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल स्थिर काष्ठा nla_policy mntr_flags_policy[NL80211_MNTR_FLAG_MAX + 1] = अणु
	[NL80211_MNTR_FLAG_FCSFAIL] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_MNTR_FLAG_PLCPFAIL] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_MNTR_FLAG_CONTROL] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_MNTR_FLAG_OTHER_BSS] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_MNTR_FLAG_COOK_FRAMES] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_MNTR_FLAG_ACTIVE] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल पूर्णांक parse_monitor_flags(काष्ठा nlattr *nla, u32 *mntrflags)
अणु
	काष्ठा nlattr *flags[NL80211_MNTR_FLAG_MAX + 1];
	पूर्णांक flag;

	*mntrflags = 0;

	अगर (!nla)
		वापस -EINVAL;

	अगर (nla_parse_nested_deprecated(flags, NL80211_MNTR_FLAG_MAX, nla, mntr_flags_policy, शून्य))
		वापस -EINVAL;

	क्रम (flag = 1; flag <= NL80211_MNTR_FLAG_MAX; flag++)
		अगर (flags[flag])
			*mntrflags |= (1<<flag);

	*mntrflags |= MONITOR_FLAG_CHANGED;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_mon_options(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     क्रमागत nl80211_अगरtype type,
				     काष्ठा genl_info *info,
				     काष्ठा vअगर_params *params)
अणु
	bool change = false;
	पूर्णांक err;

	अगर (info->attrs[NL80211_ATTR_MNTR_FLAGS]) अणु
		अगर (type != NL80211_IFTYPE_MONITOR)
			वापस -EINVAL;

		err = parse_monitor_flags(info->attrs[NL80211_ATTR_MNTR_FLAGS],
					  &params->flags);
		अगर (err)
			वापस err;

		change = true;
	पूर्ण

	अगर (params->flags & MONITOR_FLAG_ACTIVE &&
	    !(rdev->wiphy.features & NL80211_FEATURE_ACTIVE_MONITOR))
		वापस -EOPNOTSUPP;

	अगर (info->attrs[NL80211_ATTR_MU_MIMO_GROUP_DATA]) अणु
		स्थिर u8 *mumimo_groups;
		u32 cap_flag = NL80211_EXT_FEATURE_MU_MIMO_AIR_SNIFFER;

		अगर (type != NL80211_IFTYPE_MONITOR)
			वापस -EINVAL;

		अगर (!wiphy_ext_feature_isset(&rdev->wiphy, cap_flag))
			वापस -EOPNOTSUPP;

		mumimo_groups =
			nla_data(info->attrs[NL80211_ATTR_MU_MIMO_GROUP_DATA]);

		/* bits 0 and 63 are reserved and must be zero */
		अगर ((mumimo_groups[0] & BIT(0)) ||
		    (mumimo_groups[VHT_MUMIMO_GROUPS_DATA_LEN - 1] & BIT(7)))
			वापस -EINVAL;

		params->vht_mumimo_groups = mumimo_groups;
		change = true;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR]) अणु
		u32 cap_flag = NL80211_EXT_FEATURE_MU_MIMO_AIR_SNIFFER;

		अगर (type != NL80211_IFTYPE_MONITOR)
			वापस -EINVAL;

		अगर (!wiphy_ext_feature_isset(&rdev->wiphy, cap_flag))
			वापस -EOPNOTSUPP;

		params->vht_mumimo_follow_addr =
			nla_data(info->attrs[NL80211_ATTR_MU_MIMO_FOLLOW_MAC_ADDR]);
		change = true;
	पूर्ण

	वापस change ? 1 : 0;
पूर्ण

अटल पूर्णांक nl80211_valid_4addr(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *netdev, u8 use_4addr,
			       क्रमागत nl80211_अगरtype अगरtype)
अणु
	अगर (!use_4addr) अणु
		अगर (netdev && netअगर_is_bridge_port(netdev))
			वापस -EBUSY;
		वापस 0;
	पूर्ण

	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_AP_VLAN:
		अगर (rdev->wiphy.flags & WIPHY_FLAG_4ADDR_AP)
			वापस 0;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
		अगर (rdev->wiphy.flags & WIPHY_FLAG_4ADDR_STATION)
			वापस 0;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक nl80211_set_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा vअगर_params params;
	पूर्णांक err;
	क्रमागत nl80211_अगरtype otype, ntype;
	काष्ठा net_device *dev = info->user_ptr[1];
	bool change = false;

	स_रखो(&params, 0, माप(params));

	otype = ntype = dev->ieee80211_ptr->अगरtype;

	अगर (info->attrs[NL80211_ATTR_IFTYPE]) अणु
		ntype = nla_get_u32(info->attrs[NL80211_ATTR_IFTYPE]);
		अगर (otype != ntype)
			change = true;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_MESH_ID]) अणु
		काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

		अगर (ntype != NL80211_IFTYPE_MESH_POINT)
			वापस -EINVAL;
		अगर (netअगर_running(dev))
			वापस -EBUSY;

		wdev_lock(wdev);
		BUILD_BUG_ON(IEEE80211_MAX_SSID_LEN !=
			     IEEE80211_MAX_MESH_ID_LEN);
		wdev->mesh_id_up_len =
			nla_len(info->attrs[NL80211_ATTR_MESH_ID]);
		स_नकल(wdev->ssid, nla_data(info->attrs[NL80211_ATTR_MESH_ID]),
		       wdev->mesh_id_up_len);
		wdev_unlock(wdev);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_4ADDR]) अणु
		params.use_4addr = !!nla_get_u8(info->attrs[NL80211_ATTR_4ADDR]);
		change = true;
		err = nl80211_valid_4addr(rdev, dev, params.use_4addr, ntype);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		params.use_4addr = -1;
	पूर्ण

	err = nl80211_parse_mon_options(rdev, ntype, info, &params);
	अगर (err < 0)
		वापस err;
	अगर (err > 0)
		change = true;

	अगर (change)
		err = cfg80211_change_अगरace(rdev, dev, ntype, &params);
	अन्यथा
		err = 0;

	अगर (!err && params.use_4addr != -1)
		dev->ieee80211_ptr->use_4addr = params.use_4addr;

	अगर (change && !err) अणु
		काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

		nl80211_notअगरy_अगरace(rdev, wdev, NL80211_CMD_SET_INTERFACE);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक _nl80211_new_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा vअगर_params params;
	काष्ठा wireless_dev *wdev;
	काष्ठा sk_buff *msg;
	पूर्णांक err;
	क्रमागत nl80211_अगरtype type = NL80211_IFTYPE_UNSPECIFIED;

	स_रखो(&params, 0, माप(params));

	अगर (!info->attrs[NL80211_ATTR_IFNAME])
		वापस -EINVAL;

	अगर (info->attrs[NL80211_ATTR_IFTYPE])
		type = nla_get_u32(info->attrs[NL80211_ATTR_IFTYPE]);

	अगर (!rdev->ops->add_भव_पूर्णांकf)
		वापस -EOPNOTSUPP;

	अगर ((type == NL80211_IFTYPE_P2P_DEVICE || type == NL80211_IFTYPE_न_अंक ||
	     rdev->wiphy.features & NL80211_FEATURE_MAC_ON_CREATE) &&
	    info->attrs[NL80211_ATTR_MAC]) अणु
		nla_स_नकल(params.macaddr, info->attrs[NL80211_ATTR_MAC],
			   ETH_ALEN);
		अगर (!is_valid_ether_addr(params.macaddr))
			वापस -EADDRNOTAVAIL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_4ADDR]) अणु
		params.use_4addr = !!nla_get_u8(info->attrs[NL80211_ATTR_4ADDR]);
		err = nl80211_valid_4addr(rdev, शून्य, params.use_4addr, type);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!cfg80211_अगरtype_allowed(&rdev->wiphy, type, params.use_4addr, 0))
		वापस -EOPNOTSUPP;

	err = nl80211_parse_mon_options(rdev, type, info, &params);
	अगर (err < 0)
		वापस err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	wdev = rdev_add_भव_पूर्णांकf(rdev,
				nla_data(info->attrs[NL80211_ATTR_IFNAME]),
				NET_NAME_USER, type, &params);
	अगर (WARN_ON(!wdev)) अणु
		nlmsg_मुक्त(msg);
		वापस -EPROTO;
	पूर्ण अन्यथा अगर (IS_ERR(wdev)) अणु
		nlmsg_मुक्त(msg);
		वापस PTR_ERR(wdev);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_SOCKET_OWNER])
		wdev->owner_nlportid = info->snd_portid;

	चयन (type) अणु
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (!info->attrs[NL80211_ATTR_MESH_ID])
			अवरोध;
		wdev_lock(wdev);
		BUILD_BUG_ON(IEEE80211_MAX_SSID_LEN !=
			     IEEE80211_MAX_MESH_ID_LEN);
		wdev->mesh_id_up_len =
			nla_len(info->attrs[NL80211_ATTR_MESH_ID]);
		स_नकल(wdev->ssid, nla_data(info->attrs[NL80211_ATTR_MESH_ID]),
		       wdev->mesh_id_up_len);
		wdev_unlock(wdev);
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		/*
		 * P2P Device and न_अंक करो not have a netdev, so करोn't go
		 * through the netdev notअगरier and must be added here
		 */
		cfg80211_init_wdev(wdev);
		cfg80211_रेजिस्टर_wdev(rdev, wdev);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	अगर (nl80211_send_अगरace(msg, info->snd_portid, info->snd_seq, 0,
			       rdev, wdev, NL80211_CMD_NEW_INTERFACE) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक nl80211_new_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक ret;

	/* to aव्योम failing a new पूर्णांकerface creation due to pending removal */
	cfg80211_destroy_अगरaces(rdev);

	wiphy_lock(&rdev->wiphy);
	ret = _nl80211_new_पूर्णांकerface(skb, info);
	wiphy_unlock(&rdev->wiphy);

	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_del_पूर्णांकerface(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];

	अगर (!rdev->ops->del_भव_पूर्णांकf)
		वापस -EOPNOTSUPP;

	/*
	 * We hold RTNL, so this is safe, without RTNL खोलोcount cannot
	 * reach 0, and thus the rdev cannot be deleted.
	 *
	 * We need to करो it क्रम the dev_बंद(), since that will call
	 * the netdev notअगरiers, and we need to acquire the mutex there
	 * but करोn't know अगर we get there from here or from some other
	 * place (e.g. "ip link set ... down").
	 */
	mutex_unlock(&rdev->wiphy.mtx);

	/*
	 * If we हटाओ a wireless device without a netdev then clear
	 * user_ptr[1] so that nl80211_post_करोit won't dereference it
	 * to check अगर it needs to करो dev_put(). Otherwise it crashes
	 * since the wdev has been मुक्तd, unlike with a netdev where
	 * we need the dev_put() क्रम the netdev to really be मुक्तd.
	 */
	अगर (!wdev->netdev)
		info->user_ptr[1] = शून्य;
	अन्यथा
		dev_बंद(wdev->netdev);

	mutex_lock(&rdev->wiphy.mtx);

	वापस rdev_del_भव_पूर्णांकf(rdev, wdev);
पूर्ण

अटल पूर्णांक nl80211_set_noack_map(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	u16 noack_map;

	अगर (!info->attrs[NL80211_ATTR_NOACK_MAP])
		वापस -EINVAL;

	अगर (!rdev->ops->set_noack_map)
		वापस -EOPNOTSUPP;

	noack_map = nla_get_u16(info->attrs[NL80211_ATTR_NOACK_MAP]);

	वापस rdev_set_noack_map(rdev, dev, noack_map);
पूर्ण

काष्ठा get_key_cookie अणु
	काष्ठा sk_buff *msg;
	पूर्णांक error;
	पूर्णांक idx;
पूर्ण;

अटल व्योम get_key_callback(व्योम *c, काष्ठा key_params *params)
अणु
	काष्ठा nlattr *key;
	काष्ठा get_key_cookie *cookie = c;

	अगर ((params->key &&
	     nla_put(cookie->msg, NL80211_ATTR_KEY_DATA,
		     params->key_len, params->key)) ||
	    (params->seq &&
	     nla_put(cookie->msg, NL80211_ATTR_KEY_SEQ,
		     params->seq_len, params->seq)) ||
	    (params->cipher &&
	     nla_put_u32(cookie->msg, NL80211_ATTR_KEY_CIPHER,
			 params->cipher)))
		जाओ nla_put_failure;

	key = nla_nest_start_noflag(cookie->msg, NL80211_ATTR_KEY);
	अगर (!key)
		जाओ nla_put_failure;

	अगर ((params->key &&
	     nla_put(cookie->msg, NL80211_KEY_DATA,
		     params->key_len, params->key)) ||
	    (params->seq &&
	     nla_put(cookie->msg, NL80211_KEY_SEQ,
		     params->seq_len, params->seq)) ||
	    (params->cipher &&
	     nla_put_u32(cookie->msg, NL80211_KEY_CIPHER,
			 params->cipher)))
		जाओ nla_put_failure;

	अगर (nla_put_u8(cookie->msg, NL80211_KEY_IDX, cookie->idx))
		जाओ nla_put_failure;

	nla_nest_end(cookie->msg, key);

	वापस;
 nla_put_failure:
	cookie->error = 1;
पूर्ण

अटल पूर्णांक nl80211_get_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक err;
	काष्ठा net_device *dev = info->user_ptr[1];
	u8 key_idx = 0;
	स्थिर u8 *mac_addr = शून्य;
	bool pairwise;
	काष्ठा get_key_cookie cookie = अणु
		.error = 0,
	पूर्ण;
	व्योम *hdr;
	काष्ठा sk_buff *msg;
	bool bigtk_support = false;

	अगर (wiphy_ext_feature_isset(&rdev->wiphy,
				    NL80211_EXT_FEATURE_BEACON_PROTECTION))
		bigtk_support = true;

	अगर ((dev->ieee80211_ptr->अगरtype == NL80211_IFTYPE_STATION ||
	     dev->ieee80211_ptr->अगरtype == NL80211_IFTYPE_P2P_CLIENT) &&
	    wiphy_ext_feature_isset(&rdev->wiphy,
				    NL80211_EXT_FEATURE_BEACON_PROTECTION_CLIENT))
		bigtk_support = true;

	अगर (info->attrs[NL80211_ATTR_KEY_IDX]) अणु
		key_idx = nla_get_u8(info->attrs[NL80211_ATTR_KEY_IDX]);

		अगर (key_idx >= 6 && key_idx <= 7 && !bigtk_support) अणु
			GENL_SET_ERR_MSG(info, "BIGTK not supported");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_MAC])
		mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	pairwise = !!mac_addr;
	अगर (info->attrs[NL80211_ATTR_KEY_TYPE]) अणु
		u32 kt = nla_get_u32(info->attrs[NL80211_ATTR_KEY_TYPE]);

		अगर (kt != NL80211_KEYTYPE_GROUP &&
		    kt != NL80211_KEYTYPE_PAIRWISE)
			वापस -EINVAL;
		pairwise = kt == NL80211_KEYTYPE_PAIRWISE;
	पूर्ण

	अगर (!rdev->ops->get_key)
		वापस -EOPNOTSUPP;

	अगर (!pairwise && mac_addr && !(rdev->wiphy.flags & WIPHY_FLAG_IBSS_RSN))
		वापस -ENOENT;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_NEW_KEY);
	अगर (!hdr)
		जाओ nla_put_failure;

	cookie.msg = msg;
	cookie.idx = key_idx;

	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put_u8(msg, NL80211_ATTR_KEY_IDX, key_idx))
		जाओ nla_put_failure;
	अगर (mac_addr &&
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, mac_addr))
		जाओ nla_put_failure;

	err = rdev_get_key(rdev, dev, key_idx, pairwise, mac_addr, &cookie,
			   get_key_callback);

	अगर (err)
		जाओ मुक्त_msg;

	अगर (cookie.error)
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

 nla_put_failure:
	err = -ENOBUFS;
 मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_set_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा key_parse key;
	पूर्णांक err;
	काष्ठा net_device *dev = info->user_ptr[1];

	err = nl80211_parse_key(info, &key);
	अगर (err)
		वापस err;

	अगर (key.idx < 0)
		वापस -EINVAL;

	/* Only support setting शेष key and
	 * Extended Key ID action NL80211_KEY_SET_TX.
	 */
	अगर (!key.def && !key.defmgmt && !key.defbeacon &&
	    !(key.p.mode == NL80211_KEY_SET_TX))
		वापस -EINVAL;

	wdev_lock(dev->ieee80211_ptr);

	अगर (key.def) अणु
		अगर (!rdev->ops->set_शेष_key) अणु
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		err = nl80211_key_allowed(dev->ieee80211_ptr);
		अगर (err)
			जाओ out;

		err = rdev_set_शेष_key(rdev, dev, key.idx,
						 key.def_uni, key.def_multi);

		अगर (err)
			जाओ out;

#अगर_घोषित CONFIG_CFG80211_WEXT
		dev->ieee80211_ptr->wext.शेष_key = key.idx;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (key.defmgmt) अणु
		अगर (key.def_uni || !key.def_multi) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!rdev->ops->set_शेष_mgmt_key) अणु
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		err = nl80211_key_allowed(dev->ieee80211_ptr);
		अगर (err)
			जाओ out;

		err = rdev_set_शेष_mgmt_key(rdev, dev, key.idx);
		अगर (err)
			जाओ out;

#अगर_घोषित CONFIG_CFG80211_WEXT
		dev->ieee80211_ptr->wext.शेष_mgmt_key = key.idx;
#पूर्ण_अगर
	पूर्ण अन्यथा अगर (key.defbeacon) अणु
		अगर (key.def_uni || !key.def_multi) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (!rdev->ops->set_शेष_beacon_key) अणु
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		err = nl80211_key_allowed(dev->ieee80211_ptr);
		अगर (err)
			जाओ out;

		err = rdev_set_शेष_beacon_key(rdev, dev, key.idx);
		अगर (err)
			जाओ out;
	पूर्ण अन्यथा अगर (key.p.mode == NL80211_KEY_SET_TX &&
		   wiphy_ext_feature_isset(&rdev->wiphy,
					   NL80211_EXT_FEATURE_EXT_KEY_ID)) अणु
		u8 *mac_addr = शून्य;

		अगर (info->attrs[NL80211_ATTR_MAC])
			mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

		अगर (!mac_addr || key.idx < 0 || key.idx > 1) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		err = rdev_add_key(rdev, dev, key.idx,
				   NL80211_KEYTYPE_PAIRWISE,
				   mac_addr, &key.p);
	पूर्ण अन्यथा अणु
		err = -EINVAL;
	पूर्ण
 out:
	wdev_unlock(dev->ieee80211_ptr);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_new_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक err;
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा key_parse key;
	स्थिर u8 *mac_addr = शून्य;

	err = nl80211_parse_key(info, &key);
	अगर (err)
		वापस err;

	अगर (!key.p.key) अणु
		GENL_SET_ERR_MSG(info, "no key");
		वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_MAC])
		mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	अगर (key.type == -1) अणु
		अगर (mac_addr)
			key.type = NL80211_KEYTYPE_PAIRWISE;
		अन्यथा
			key.type = NL80211_KEYTYPE_GROUP;
	पूर्ण

	/* क्रम now */
	अगर (key.type != NL80211_KEYTYPE_PAIRWISE &&
	    key.type != NL80211_KEYTYPE_GROUP) अणु
		GENL_SET_ERR_MSG(info, "key type not pairwise or group");
		वापस -EINVAL;
	पूर्ण

	अगर (key.type == NL80211_KEYTYPE_GROUP &&
	    info->attrs[NL80211_ATTR_VLAN_ID])
		key.p.vlan_id = nla_get_u16(info->attrs[NL80211_ATTR_VLAN_ID]);

	अगर (!rdev->ops->add_key)
		वापस -EOPNOTSUPP;

	अगर (cfg80211_validate_key_settings(rdev, &key.p, key.idx,
					   key.type == NL80211_KEYTYPE_PAIRWISE,
					   mac_addr)) अणु
		GENL_SET_ERR_MSG(info, "key setting validation failed");
		वापस -EINVAL;
	पूर्ण

	wdev_lock(dev->ieee80211_ptr);
	err = nl80211_key_allowed(dev->ieee80211_ptr);
	अगर (err)
		GENL_SET_ERR_MSG(info, "key not allowed");
	अगर (!err) अणु
		err = rdev_add_key(rdev, dev, key.idx,
				   key.type == NL80211_KEYTYPE_PAIRWISE,
				    mac_addr, &key.p);
		अगर (err)
			GENL_SET_ERR_MSG(info, "key addition failed");
	पूर्ण
	wdev_unlock(dev->ieee80211_ptr);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_del_key(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक err;
	काष्ठा net_device *dev = info->user_ptr[1];
	u8 *mac_addr = शून्य;
	काष्ठा key_parse key;

	err = nl80211_parse_key(info, &key);
	अगर (err)
		वापस err;

	अगर (info->attrs[NL80211_ATTR_MAC])
		mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	अगर (key.type == -1) अणु
		अगर (mac_addr)
			key.type = NL80211_KEYTYPE_PAIRWISE;
		अन्यथा
			key.type = NL80211_KEYTYPE_GROUP;
	पूर्ण

	/* क्रम now */
	अगर (key.type != NL80211_KEYTYPE_PAIRWISE &&
	    key.type != NL80211_KEYTYPE_GROUP)
		वापस -EINVAL;

	अगर (!cfg80211_valid_key_idx(rdev, key.idx,
				    key.type == NL80211_KEYTYPE_PAIRWISE))
		वापस -EINVAL;

	अगर (!rdev->ops->del_key)
		वापस -EOPNOTSUPP;

	wdev_lock(dev->ieee80211_ptr);
	err = nl80211_key_allowed(dev->ieee80211_ptr);

	अगर (key.type == NL80211_KEYTYPE_GROUP && mac_addr &&
	    !(rdev->wiphy.flags & WIPHY_FLAG_IBSS_RSN))
		err = -ENOENT;

	अगर (!err)
		err = rdev_del_key(rdev, dev, key.idx,
				   key.type == NL80211_KEYTYPE_PAIRWISE,
				   mac_addr);

#अगर_घोषित CONFIG_CFG80211_WEXT
	अगर (!err) अणु
		अगर (key.idx == dev->ieee80211_ptr->wext.शेष_key)
			dev->ieee80211_ptr->wext.शेष_key = -1;
		अन्यथा अगर (key.idx == dev->ieee80211_ptr->wext.शेष_mgmt_key)
			dev->ieee80211_ptr->wext.शेष_mgmt_key = -1;
	पूर्ण
#पूर्ण_अगर
	wdev_unlock(dev->ieee80211_ptr);

	वापस err;
पूर्ण

/* This function वापसs an error or the number of nested attributes */
अटल पूर्णांक validate_acl_mac_addrs(काष्ठा nlattr *nl_attr)
अणु
	काष्ठा nlattr *attr;
	पूर्णांक n_entries = 0, पंचांगp;

	nla_क्रम_each_nested(attr, nl_attr, पंचांगp) अणु
		अगर (nla_len(attr) != ETH_ALEN)
			वापस -EINVAL;

		n_entries++;
	पूर्ण

	वापस n_entries;
पूर्ण

/*
 * This function parses ACL inक्रमmation and allocates memory क्रम ACL data.
 * On successful वापस, the calling function is responsible to मुक्त the
 * ACL buffer वापसed by this function.
 */
अटल काष्ठा cfg80211_acl_data *parse_acl_data(काष्ठा wiphy *wiphy,
						काष्ठा genl_info *info)
अणु
	क्रमागत nl80211_acl_policy acl_policy;
	काष्ठा nlattr *attr;
	काष्ठा cfg80211_acl_data *acl;
	पूर्णांक i = 0, n_entries, पंचांगp;

	अगर (!wiphy->max_acl_mac_addrs)
		वापस ERR_PTR(-EOPNOTSUPP);

	अगर (!info->attrs[NL80211_ATTR_ACL_POLICY])
		वापस ERR_PTR(-EINVAL);

	acl_policy = nla_get_u32(info->attrs[NL80211_ATTR_ACL_POLICY]);
	अगर (acl_policy != NL80211_ACL_POLICY_ACCEPT_UNLESS_LISTED &&
	    acl_policy != NL80211_ACL_POLICY_DENY_UNLESS_LISTED)
		वापस ERR_PTR(-EINVAL);

	अगर (!info->attrs[NL80211_ATTR_MAC_ADDRS])
		वापस ERR_PTR(-EINVAL);

	n_entries = validate_acl_mac_addrs(info->attrs[NL80211_ATTR_MAC_ADDRS]);
	अगर (n_entries < 0)
		वापस ERR_PTR(n_entries);

	अगर (n_entries > wiphy->max_acl_mac_addrs)
		वापस ERR_PTR(-ENOTSUPP);

	acl = kzalloc(काष्ठा_size(acl, mac_addrs, n_entries), GFP_KERNEL);
	अगर (!acl)
		वापस ERR_PTR(-ENOMEM);

	nla_क्रम_each_nested(attr, info->attrs[NL80211_ATTR_MAC_ADDRS], पंचांगp) अणु
		स_नकल(acl->mac_addrs[i].addr, nla_data(attr), ETH_ALEN);
		i++;
	पूर्ण

	acl->n_acl_entries = n_entries;
	acl->acl_policy = acl_policy;

	वापस acl;
पूर्ण

अटल पूर्णांक nl80211_set_mac_acl(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा cfg80211_acl_data *acl;
	पूर्णांक err;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EOPNOTSUPP;

	अगर (!dev->ieee80211_ptr->beacon_पूर्णांकerval)
		वापस -EINVAL;

	acl = parse_acl_data(&rdev->wiphy, info);
	अगर (IS_ERR(acl))
		वापस PTR_ERR(acl);

	err = rdev_set_mac_acl(rdev, dev, acl);

	kमुक्त(acl);

	वापस err;
पूर्ण

अटल u32 rateset_to_mask(काष्ठा ieee80211_supported_band *sband,
			   u8 *rates, u8 rates_len)
अणु
	u8 i;
	u32 mask = 0;

	क्रम (i = 0; i < rates_len; i++) अणु
		पूर्णांक rate = (rates[i] & 0x7f) * 5;
		पूर्णांक ridx;

		क्रम (ridx = 0; ridx < sband->n_bitrates; ridx++) अणु
			काष्ठा ieee80211_rate *srate =
				&sband->bitrates[ridx];
			अगर (rate == srate->bitrate) अणु
				mask |= 1 << ridx;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (ridx == sband->n_bitrates)
			वापस 0; /* rate not found */
	पूर्ण

	वापस mask;
पूर्ण

अटल bool ht_rateset_to_mask(काष्ठा ieee80211_supported_band *sband,
			       u8 *rates, u8 rates_len,
			       u8 mcs[IEEE80211_HT_MCS_MASK_LEN])
अणु
	u8 i;

	स_रखो(mcs, 0, IEEE80211_HT_MCS_MASK_LEN);

	क्रम (i = 0; i < rates_len; i++) अणु
		पूर्णांक ridx, rbit;

		ridx = rates[i] / 8;
		rbit = BIT(rates[i] % 8);

		/* check validity */
		अगर ((ridx < 0) || (ridx >= IEEE80211_HT_MCS_MASK_LEN))
			वापस false;

		/* check availability */
		ridx = array_index_nospec(ridx, IEEE80211_HT_MCS_MASK_LEN);
		अगर (sband->ht_cap.mcs.rx_mask[ridx] & rbit)
			mcs[ridx] |= rbit;
		अन्यथा
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल u16 vht_mcs_map_to_mcs_mask(u8 vht_mcs_map)
अणु
	u16 mcs_mask = 0;

	चयन (vht_mcs_map) अणु
	हाल IEEE80211_VHT_MCS_NOT_SUPPORTED:
		अवरोध;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_7:
		mcs_mask = 0x00FF;
		अवरोध;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_8:
		mcs_mask = 0x01FF;
		अवरोध;
	हाल IEEE80211_VHT_MCS_SUPPORT_0_9:
		mcs_mask = 0x03FF;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस mcs_mask;
पूर्ण

अटल व्योम vht_build_mcs_mask(u16 vht_mcs_map,
			       u16 vht_mcs_mask[NL80211_VHT_NSS_MAX])
अणु
	u8 nss;

	क्रम (nss = 0; nss < NL80211_VHT_NSS_MAX; nss++) अणु
		vht_mcs_mask[nss] = vht_mcs_map_to_mcs_mask(vht_mcs_map & 0x03);
		vht_mcs_map >>= 2;
	पूर्ण
पूर्ण

अटल bool vht_set_mcs_mask(काष्ठा ieee80211_supported_band *sband,
			     काष्ठा nl80211_txrate_vht *txrate,
			     u16 mcs[NL80211_VHT_NSS_MAX])
अणु
	u16 tx_mcs_map = le16_to_cpu(sband->vht_cap.vht_mcs.tx_mcs_map);
	u16 tx_mcs_mask[NL80211_VHT_NSS_MAX] = अणुपूर्ण;
	u8 i;

	अगर (!sband->vht_cap.vht_supported)
		वापस false;

	स_रखो(mcs, 0, माप(u16) * NL80211_VHT_NSS_MAX);

	/* Build vht_mcs_mask from VHT capabilities */
	vht_build_mcs_mask(tx_mcs_map, tx_mcs_mask);

	क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++) अणु
		अगर ((tx_mcs_mask[i] & txrate->mcs[i]) == txrate->mcs[i])
			mcs[i] = txrate->mcs[i];
		अन्यथा
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल u16 he_mcs_map_to_mcs_mask(u8 he_mcs_map)
अणु
	चयन (he_mcs_map) अणु
	हाल IEEE80211_HE_MCS_NOT_SUPPORTED:
		वापस 0;
	हाल IEEE80211_HE_MCS_SUPPORT_0_7:
		वापस 0x00FF;
	हाल IEEE80211_HE_MCS_SUPPORT_0_9:
		वापस 0x03FF;
	हाल IEEE80211_HE_MCS_SUPPORT_0_11:
		वापस 0xFFF;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम he_build_mcs_mask(u16 he_mcs_map,
			      u16 he_mcs_mask[NL80211_HE_NSS_MAX])
अणु
	u8 nss;

	क्रम (nss = 0; nss < NL80211_HE_NSS_MAX; nss++) अणु
		he_mcs_mask[nss] = he_mcs_map_to_mcs_mask(he_mcs_map & 0x03);
		he_mcs_map >>= 2;
	पूर्ण
पूर्ण

अटल u16 he_get_txmcsmap(काष्ठा genl_info *info,
			   स्थिर काष्ठा ieee80211_sta_he_cap *he_cap)
अणु
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	__le16	tx_mcs;

	चयन (wdev->chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_80P80:
		tx_mcs = he_cap->he_mcs_nss_supp.tx_mcs_80p80;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_160:
		tx_mcs = he_cap->he_mcs_nss_supp.tx_mcs_160;
		अवरोध;
	शेष:
		tx_mcs = he_cap->he_mcs_nss_supp.tx_mcs_80;
		अवरोध;
	पूर्ण
	वापस le16_to_cpu(tx_mcs);
पूर्ण

अटल bool he_set_mcs_mask(काष्ठा genl_info *info,
			    काष्ठा wireless_dev *wdev,
			    काष्ठा ieee80211_supported_band *sband,
			    काष्ठा nl80211_txrate_he *txrate,
			    u16 mcs[NL80211_HE_NSS_MAX])
अणु
	स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;
	u16 tx_mcs_mask[NL80211_HE_NSS_MAX] = अणुपूर्ण;
	u16 tx_mcs_map = 0;
	u8 i;

	he_cap = ieee80211_get_he_अगरtype_cap(sband, wdev->अगरtype);
	अगर (!he_cap)
		वापस false;

	स_रखो(mcs, 0, माप(u16) * NL80211_HE_NSS_MAX);

	tx_mcs_map = he_get_txmcsmap(info, he_cap);

	/* Build he_mcs_mask from HE capabilities */
	he_build_mcs_mask(tx_mcs_map, tx_mcs_mask);

	क्रम (i = 0; i < NL80211_HE_NSS_MAX; i++) अणु
		अगर ((tx_mcs_mask[i] & txrate->mcs[i]) == txrate->mcs[i])
			mcs[i] = txrate->mcs[i];
		अन्यथा
			वापस false;
	पूर्ण

	वापस true;
पूर्ण

अटल पूर्णांक nl80211_parse_tx_bitrate_mask(काष्ठा genl_info *info,
					 काष्ठा nlattr *attrs[],
					 क्रमागत nl80211_attrs attr,
					 काष्ठा cfg80211_bitrate_mask *mask,
					 काष्ठा net_device *dev,
					 bool शेष_all_enabled)
अणु
	काष्ठा nlattr *tb[NL80211_TXRATE_MAX + 1];
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक rem, i;
	काष्ठा nlattr *tx_rates;
	काष्ठा ieee80211_supported_band *sband;
	u16 vht_tx_mcs_map, he_tx_mcs_map;

	स_रखो(mask, 0, माप(*mask));
	/* Default to all rates enabled */
	क्रम (i = 0; i < NUM_NL80211_BANDS; i++) अणु
		स्थिर काष्ठा ieee80211_sta_he_cap *he_cap;

		अगर (!शेष_all_enabled)
			अवरोध;

		sband = rdev->wiphy.bands[i];

		अगर (!sband)
			जारी;

		mask->control[i].legacy = (1 << sband->n_bitrates) - 1;
		स_नकल(mask->control[i].ht_mcs,
		       sband->ht_cap.mcs.rx_mask,
		       माप(mask->control[i].ht_mcs));

		अगर (!sband->vht_cap.vht_supported)
			जारी;

		vht_tx_mcs_map = le16_to_cpu(sband->vht_cap.vht_mcs.tx_mcs_map);
		vht_build_mcs_mask(vht_tx_mcs_map, mask->control[i].vht_mcs);

		he_cap = ieee80211_get_he_अगरtype_cap(sband, wdev->अगरtype);
		अगर (!he_cap)
			जारी;

		he_tx_mcs_map = he_get_txmcsmap(info, he_cap);
		he_build_mcs_mask(he_tx_mcs_map, mask->control[i].he_mcs);

		mask->control[i].he_gi = 0xFF;
		mask->control[i].he_ltf = 0xFF;
	पूर्ण

	/* अगर no rates are given set it back to the शेषs */
	अगर (!attrs[attr])
		जाओ out;

	/* The nested attribute uses क्रमागत nl80211_band as the index. This maps
	 * directly to the क्रमागत nl80211_band values used in cfg80211.
	 */
	BUILD_BUG_ON(NL80211_MAX_SUPP_HT_RATES > IEEE80211_HT_MCS_MASK_LEN * 8);
	nla_क्रम_each_nested(tx_rates, attrs[attr], rem) अणु
		क्रमागत nl80211_band band = nla_type(tx_rates);
		पूर्णांक err;

		अगर (band < 0 || band >= NUM_NL80211_BANDS)
			वापस -EINVAL;
		sband = rdev->wiphy.bands[band];
		अगर (sband == शून्य)
			वापस -EINVAL;
		err = nla_parse_nested_deprecated(tb, NL80211_TXRATE_MAX,
						  tx_rates,
						  nl80211_txattr_policy,
						  info->extack);
		अगर (err)
			वापस err;
		अगर (tb[NL80211_TXRATE_LEGACY]) अणु
			mask->control[band].legacy = rateset_to_mask(
				sband,
				nla_data(tb[NL80211_TXRATE_LEGACY]),
				nla_len(tb[NL80211_TXRATE_LEGACY]));
			अगर ((mask->control[band].legacy == 0) &&
			    nla_len(tb[NL80211_TXRATE_LEGACY]))
				वापस -EINVAL;
		पूर्ण
		अगर (tb[NL80211_TXRATE_HT]) अणु
			अगर (!ht_rateset_to_mask(
					sband,
					nla_data(tb[NL80211_TXRATE_HT]),
					nla_len(tb[NL80211_TXRATE_HT]),
					mask->control[band].ht_mcs))
				वापस -EINVAL;
		पूर्ण

		अगर (tb[NL80211_TXRATE_VHT]) अणु
			अगर (!vht_set_mcs_mask(
					sband,
					nla_data(tb[NL80211_TXRATE_VHT]),
					mask->control[band].vht_mcs))
				वापस -EINVAL;
		पूर्ण

		अगर (tb[NL80211_TXRATE_GI]) अणु
			mask->control[band].gi =
				nla_get_u8(tb[NL80211_TXRATE_GI]);
			अगर (mask->control[band].gi > NL80211_TXRATE_FORCE_LGI)
				वापस -EINVAL;
		पूर्ण
		अगर (tb[NL80211_TXRATE_HE] &&
		    !he_set_mcs_mask(info, wdev, sband,
				     nla_data(tb[NL80211_TXRATE_HE]),
				     mask->control[band].he_mcs))
			वापस -EINVAL;

		अगर (tb[NL80211_TXRATE_HE_GI])
			mask->control[band].he_gi =
				nla_get_u8(tb[NL80211_TXRATE_HE_GI]);
		अगर (tb[NL80211_TXRATE_HE_LTF])
			mask->control[band].he_ltf =
				nla_get_u8(tb[NL80211_TXRATE_HE_LTF]);

		अगर (mask->control[band].legacy == 0) अणु
			/* करोn't allow empty legacy rates अगर HT, VHT or HE
			 * are not even supported.
			 */
			अगर (!(rdev->wiphy.bands[band]->ht_cap.ht_supported ||
			      rdev->wiphy.bands[band]->vht_cap.vht_supported ||
			      ieee80211_get_he_अगरtype_cap(sband, wdev->अगरtype)))
				वापस -EINVAL;

			क्रम (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++)
				अगर (mask->control[band].ht_mcs[i])
					जाओ out;

			क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++)
				अगर (mask->control[band].vht_mcs[i])
					जाओ out;

			क्रम (i = 0; i < NL80211_HE_NSS_MAX; i++)
				अगर (mask->control[band].he_mcs[i])
					जाओ out;

			/* legacy and mcs rates may not be both empty */
			वापस -EINVAL;
		पूर्ण
	पूर्ण

out:
	वापस 0;
पूर्ण

अटल पूर्णांक validate_beacon_tx_rate(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   क्रमागत nl80211_band band,
				   काष्ठा cfg80211_bitrate_mask *beacon_rate)
अणु
	u32 count_ht, count_vht, count_he, i;
	u32 rate = beacon_rate->control[band].legacy;

	/* Allow only one rate */
	अगर (hweight32(rate) > 1)
		वापस -EINVAL;

	count_ht = 0;
	क्रम (i = 0; i < IEEE80211_HT_MCS_MASK_LEN; i++) अणु
		अगर (hweight8(beacon_rate->control[band].ht_mcs[i]) > 1) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (beacon_rate->control[band].ht_mcs[i]) अणु
			count_ht++;
			अगर (count_ht > 1)
				वापस -EINVAL;
		पूर्ण
		अगर (count_ht && rate)
			वापस -EINVAL;
	पूर्ण

	count_vht = 0;
	क्रम (i = 0; i < NL80211_VHT_NSS_MAX; i++) अणु
		अगर (hweight16(beacon_rate->control[band].vht_mcs[i]) > 1) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (beacon_rate->control[band].vht_mcs[i]) अणु
			count_vht++;
			अगर (count_vht > 1)
				वापस -EINVAL;
		पूर्ण
		अगर (count_vht && rate)
			वापस -EINVAL;
	पूर्ण

	count_he = 0;
	क्रम (i = 0; i < NL80211_HE_NSS_MAX; i++) अणु
		अगर (hweight16(beacon_rate->control[band].he_mcs[i]) > 1) अणु
			वापस -EINVAL;
		पूर्ण अन्यथा अगर (beacon_rate->control[band].he_mcs[i]) अणु
			count_he++;
			अगर (count_he > 1)
				वापस -EINVAL;
		पूर्ण
		अगर (count_he && rate)
			वापस -EINVAL;
	पूर्ण

	अगर ((count_ht && count_vht && count_he) ||
	    (!rate && !count_ht && !count_vht && !count_he))
		वापस -EINVAL;

	अगर (rate &&
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_BEACON_RATE_LEGACY))
		वापस -EINVAL;
	अगर (count_ht &&
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_BEACON_RATE_HT))
		वापस -EINVAL;
	अगर (count_vht &&
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_BEACON_RATE_VHT))
		वापस -EINVAL;
	अगर (count_he &&
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_BEACON_RATE_HE))
		वापस -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_beacon(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा nlattr *attrs[],
				काष्ठा cfg80211_beacon_data *bcn)
अणु
	bool haveinfo = false;
	पूर्णांक err;

	स_रखो(bcn, 0, माप(*bcn));

	अगर (attrs[NL80211_ATTR_BEACON_HEAD]) अणु
		bcn->head = nla_data(attrs[NL80211_ATTR_BEACON_HEAD]);
		bcn->head_len = nla_len(attrs[NL80211_ATTR_BEACON_HEAD]);
		अगर (!bcn->head_len)
			वापस -EINVAL;
		haveinfo = true;
	पूर्ण

	अगर (attrs[NL80211_ATTR_BEACON_TAIL]) अणु
		bcn->tail = nla_data(attrs[NL80211_ATTR_BEACON_TAIL]);
		bcn->tail_len = nla_len(attrs[NL80211_ATTR_BEACON_TAIL]);
		haveinfo = true;
	पूर्ण

	अगर (!haveinfo)
		वापस -EINVAL;

	अगर (attrs[NL80211_ATTR_IE]) अणु
		bcn->beacon_ies = nla_data(attrs[NL80211_ATTR_IE]);
		bcn->beacon_ies_len = nla_len(attrs[NL80211_ATTR_IE]);
	पूर्ण

	अगर (attrs[NL80211_ATTR_IE_PROBE_RESP]) अणु
		bcn->proberesp_ies =
			nla_data(attrs[NL80211_ATTR_IE_PROBE_RESP]);
		bcn->proberesp_ies_len =
			nla_len(attrs[NL80211_ATTR_IE_PROBE_RESP]);
	पूर्ण

	अगर (attrs[NL80211_ATTR_IE_ASSOC_RESP]) अणु
		bcn->assocresp_ies =
			nla_data(attrs[NL80211_ATTR_IE_ASSOC_RESP]);
		bcn->assocresp_ies_len =
			nla_len(attrs[NL80211_ATTR_IE_ASSOC_RESP]);
	पूर्ण

	अगर (attrs[NL80211_ATTR_PROBE_RESP]) अणु
		bcn->probe_resp = nla_data(attrs[NL80211_ATTR_PROBE_RESP]);
		bcn->probe_resp_len = nla_len(attrs[NL80211_ATTR_PROBE_RESP]);
	पूर्ण

	अगर (attrs[NL80211_ATTR_FTM_RESPONDER]) अणु
		काष्ठा nlattr *tb[NL80211_FTM_RESP_ATTR_MAX + 1];

		err = nla_parse_nested_deprecated(tb,
						  NL80211_FTM_RESP_ATTR_MAX,
						  attrs[NL80211_ATTR_FTM_RESPONDER],
						  शून्य, शून्य);
		अगर (err)
			वापस err;

		अगर (tb[NL80211_FTM_RESP_ATTR_ENABLED] &&
		    wiphy_ext_feature_isset(&rdev->wiphy,
					    NL80211_EXT_FEATURE_ENABLE_FTM_RESPONDER))
			bcn->fपंचांग_responder = 1;
		अन्यथा
			वापस -EOPNOTSUPP;

		अगर (tb[NL80211_FTM_RESP_ATTR_LCI]) अणु
			bcn->lci = nla_data(tb[NL80211_FTM_RESP_ATTR_LCI]);
			bcn->lci_len = nla_len(tb[NL80211_FTM_RESP_ATTR_LCI]);
		पूर्ण

		अगर (tb[NL80211_FTM_RESP_ATTR_CIVICLOC]) अणु
			bcn->civicloc = nla_data(tb[NL80211_FTM_RESP_ATTR_CIVICLOC]);
			bcn->civicloc_len = nla_len(tb[NL80211_FTM_RESP_ATTR_CIVICLOC]);
		पूर्ण
	पूर्ण अन्यथा अणु
		bcn->fपंचांग_responder = -1;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_he_obss_pd(काष्ठा nlattr *attrs,
				    काष्ठा ieee80211_he_obss_pd *he_obss_pd)
अणु
	काष्ठा nlattr *tb[NL80211_HE_OBSS_PD_ATTR_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested(tb, NL80211_HE_OBSS_PD_ATTR_MAX, attrs,
			       he_obss_pd_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[NL80211_HE_OBSS_PD_ATTR_SR_CTRL])
		वापस -EINVAL;

	he_obss_pd->sr_ctrl = nla_get_u8(tb[NL80211_HE_OBSS_PD_ATTR_SR_CTRL]);

	अगर (tb[NL80211_HE_OBSS_PD_ATTR_MIN_OFFSET])
		he_obss_pd->min_offset =
			nla_get_u8(tb[NL80211_HE_OBSS_PD_ATTR_MIN_OFFSET]);
	अगर (tb[NL80211_HE_OBSS_PD_ATTR_MAX_OFFSET])
		he_obss_pd->max_offset =
			nla_get_u8(tb[NL80211_HE_OBSS_PD_ATTR_MAX_OFFSET]);
	अगर (tb[NL80211_HE_OBSS_PD_ATTR_NON_SRG_MAX_OFFSET])
		he_obss_pd->non_srg_max_offset =
			nla_get_u8(tb[NL80211_HE_OBSS_PD_ATTR_NON_SRG_MAX_OFFSET]);

	अगर (he_obss_pd->min_offset > he_obss_pd->max_offset)
		वापस -EINVAL;

	अगर (tb[NL80211_HE_OBSS_PD_ATTR_BSS_COLOR_BITMAP])
		स_नकल(he_obss_pd->bss_color_biपंचांगap,
		       nla_data(tb[NL80211_HE_OBSS_PD_ATTR_BSS_COLOR_BITMAP]),
		       माप(he_obss_pd->bss_color_biपंचांगap));

	अगर (tb[NL80211_HE_OBSS_PD_ATTR_PARTIAL_BSSID_BITMAP])
		स_नकल(he_obss_pd->partial_bssid_biपंचांगap,
		       nla_data(tb[NL80211_HE_OBSS_PD_ATTR_PARTIAL_BSSID_BITMAP]),
		       माप(he_obss_pd->partial_bssid_biपंचांगap));

	he_obss_pd->enable = true;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_he_bss_color(काष्ठा nlattr *attrs,
				      काष्ठा cfg80211_he_bss_color *he_bss_color)
अणु
	काष्ठा nlattr *tb[NL80211_HE_BSS_COLOR_ATTR_MAX + 1];
	पूर्णांक err;

	err = nla_parse_nested(tb, NL80211_HE_BSS_COLOR_ATTR_MAX, attrs,
			       he_bss_color_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[NL80211_HE_BSS_COLOR_ATTR_COLOR])
		वापस -EINVAL;

	he_bss_color->color =
		nla_get_u8(tb[NL80211_HE_BSS_COLOR_ATTR_COLOR]);
	he_bss_color->enabled =
		!nla_get_flag(tb[NL80211_HE_BSS_COLOR_ATTR_DISABLED]);
	he_bss_color->partial =
		nla_get_flag(tb[NL80211_HE_BSS_COLOR_ATTR_PARTIAL]);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_fils_discovery(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
					काष्ठा nlattr *attrs,
					काष्ठा cfg80211_ap_settings *params)
अणु
	काष्ठा nlattr *tb[NL80211_FILS_DISCOVERY_ATTR_MAX + 1];
	पूर्णांक ret;
	काष्ठा cfg80211_fils_discovery *fd = &params->fils_discovery;

	अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_FILS_DISCOVERY))
		वापस -EINVAL;

	ret = nla_parse_nested(tb, NL80211_FILS_DISCOVERY_ATTR_MAX, attrs,
			       शून्य, शून्य);
	अगर (ret)
		वापस ret;

	अगर (!tb[NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_न्यून] ||
	    !tb[NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_उच्च] ||
	    !tb[NL80211_FILS_DISCOVERY_ATTR_TMPL])
		वापस -EINVAL;

	fd->पंचांगpl_len = nla_len(tb[NL80211_FILS_DISCOVERY_ATTR_TMPL]);
	fd->पंचांगpl = nla_data(tb[NL80211_FILS_DISCOVERY_ATTR_TMPL]);
	fd->min_पूर्णांकerval = nla_get_u32(tb[NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_न्यून]);
	fd->max_पूर्णांकerval = nla_get_u32(tb[NL80211_FILS_DISCOVERY_ATTR_पूर्णांक_उच्च]);

	वापस 0;
पूर्ण

अटल पूर्णांक
nl80211_parse_unsol_bcast_probe_resp(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा nlattr *attrs,
				     काष्ठा cfg80211_ap_settings *params)
अणु
	काष्ठा nlattr *tb[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_MAX + 1];
	पूर्णांक ret;
	काष्ठा cfg80211_unsol_bcast_probe_resp *presp =
					&params->unsol_bcast_probe_resp;

	अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_UNSOL_BCAST_PROBE_RESP))
		वापस -EINVAL;

	ret = nla_parse_nested(tb, NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_MAX,
			       attrs, शून्य, शून्य);
	अगर (ret)
		वापस ret;

	अगर (!tb[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_INT] ||
	    !tb[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_TMPL])
		वापस -EINVAL;

	presp->पंचांगpl = nla_data(tb[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_TMPL]);
	presp->पंचांगpl_len = nla_len(tb[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_TMPL]);
	presp->पूर्णांकerval = nla_get_u32(tb[NL80211_UNSOL_BCAST_PROBE_RESP_ATTR_INT]);
	वापस 0;
पूर्ण

अटल व्योम nl80211_check_ap_rate_selectors(काष्ठा cfg80211_ap_settings *params,
					    स्थिर u8 *rates)
अणु
	पूर्णांक i;

	अगर (!rates)
		वापस;

	क्रम (i = 0; i < rates[1]; i++) अणु
		अगर (rates[2 + i] == BSS_MEMBERSHIP_SELECTOR_HT_PHY)
			params->ht_required = true;
		अगर (rates[2 + i] == BSS_MEMBERSHIP_SELECTOR_VHT_PHY)
			params->vht_required = true;
		अगर (rates[2 + i] == BSS_MEMBERSHIP_SELECTOR_HE_PHY)
			params->he_required = true;
		अगर (rates[2 + i] == BSS_MEMBERSHIP_SELECTOR_SAE_H2E)
			params->sae_h2e_required = true;
	पूर्ण
पूर्ण

/*
 * Since the nl80211 API didn't include, from the beginning, attributes about
 * HT/VHT requirements/capabilities, we parse them out of the IEs क्रम the
 * benefit of drivers that rebuild IEs in the firmware.
 */
अटल व्योम nl80211_calculate_ap_params(काष्ठा cfg80211_ap_settings *params)
अणु
	स्थिर काष्ठा cfg80211_beacon_data *bcn = &params->beacon;
	माप_प्रकार ies_len = bcn->tail_len;
	स्थिर u8 *ies = bcn->tail;
	स्थिर u8 *rates;
	स्थिर u8 *cap;

	rates = cfg80211_find_ie(WLAN_EID_SUPP_RATES, ies, ies_len);
	nl80211_check_ap_rate_selectors(params, rates);

	rates = cfg80211_find_ie(WLAN_EID_EXT_SUPP_RATES, ies, ies_len);
	nl80211_check_ap_rate_selectors(params, rates);

	cap = cfg80211_find_ie(WLAN_EID_HT_CAPABILITY, ies, ies_len);
	अगर (cap && cap[1] >= माप(*params->ht_cap))
		params->ht_cap = (व्योम *)(cap + 2);
	cap = cfg80211_find_ie(WLAN_EID_VHT_CAPABILITY, ies, ies_len);
	अगर (cap && cap[1] >= माप(*params->vht_cap))
		params->vht_cap = (व्योम *)(cap + 2);
	cap = cfg80211_find_ext_ie(WLAN_EID_EXT_HE_CAPABILITY, ies, ies_len);
	अगर (cap && cap[1] >= माप(*params->he_cap) + 1)
		params->he_cap = (व्योम *)(cap + 3);
	cap = cfg80211_find_ext_ie(WLAN_EID_EXT_HE_OPERATION, ies, ies_len);
	अगर (cap && cap[1] >= माप(*params->he_oper) + 1)
		params->he_oper = (व्योम *)(cap + 3);
पूर्ण

अटल bool nl80211_get_ap_channel(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा cfg80211_ap_settings *params)
अणु
	काष्ठा wireless_dev *wdev;
	bool ret = false;

	list_क्रम_each_entry(wdev, &rdev->wiphy.wdev_list, list) अणु
		अगर (wdev->अगरtype != NL80211_IFTYPE_AP &&
		    wdev->अगरtype != NL80211_IFTYPE_P2P_GO)
			जारी;

		अगर (!wdev->preset_chandef.chan)
			जारी;

		params->chandef = wdev->preset_chandef;
		ret = true;
		अवरोध;
	पूर्ण

	वापस ret;
पूर्ण

अटल bool nl80211_valid_auth_type(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    क्रमागत nl80211_auth_type auth_type,
				    क्रमागत nl80211_commands cmd)
अणु
	अगर (auth_type > NL80211_AUTHTYPE_MAX)
		वापस false;

	चयन (cmd) अणु
	हाल NL80211_CMD_AUTHENTICATE:
		अगर (!(rdev->wiphy.features & NL80211_FEATURE_SAE) &&
		    auth_type == NL80211_AUTHTYPE_SAE)
			वापस false;
		अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_FILS_STA) &&
		    (auth_type == NL80211_AUTHTYPE_FILS_SK ||
		     auth_type == NL80211_AUTHTYPE_FILS_SK_PFS ||
		     auth_type == NL80211_AUTHTYPE_FILS_PK))
			वापस false;
		वापस true;
	हाल NL80211_CMD_CONNECT:
		अगर (!(rdev->wiphy.features & NL80211_FEATURE_SAE) &&
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_SAE_OFFLOAD) &&
		    auth_type == NL80211_AUTHTYPE_SAE)
			वापस false;

		/* FILS with SK PFS or PK not supported yet */
		अगर (auth_type == NL80211_AUTHTYPE_FILS_SK_PFS ||
		    auth_type == NL80211_AUTHTYPE_FILS_PK)
			वापस false;
		अगर (!wiphy_ext_feature_isset(
			    &rdev->wiphy,
			    NL80211_EXT_FEATURE_FILS_SK_OFFLOAD) &&
		    auth_type == NL80211_AUTHTYPE_FILS_SK)
			वापस false;
		वापस true;
	हाल NL80211_CMD_START_AP:
		अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_SAE_OFFLOAD_AP) &&
		    auth_type == NL80211_AUTHTYPE_SAE)
			वापस false;
		/* FILS not supported yet */
		अगर (auth_type == NL80211_AUTHTYPE_FILS_SK ||
		    auth_type == NL80211_AUTHTYPE_FILS_SK_PFS ||
		    auth_type == NL80211_AUTHTYPE_FILS_PK)
			वापस false;
		वापस true;
	शेष:
		वापस false;
	पूर्ण
पूर्ण

अटल पूर्णांक nl80211_start_ap(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_ap_settings params;
	पूर्णांक err;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->start_ap)
		वापस -EOPNOTSUPP;

	अगर (wdev->beacon_पूर्णांकerval)
		वापस -EALREADY;

	स_रखो(&params, 0, माप(params));

	/* these are required क्रम START_AP */
	अगर (!info->attrs[NL80211_ATTR_BEACON_INTERVAL] ||
	    !info->attrs[NL80211_ATTR_DTIM_PERIOD] ||
	    !info->attrs[NL80211_ATTR_BEACON_HEAD])
		वापस -EINVAL;

	err = nl80211_parse_beacon(rdev, info->attrs, &params.beacon);
	अगर (err)
		वापस err;

	params.beacon_पूर्णांकerval =
		nla_get_u32(info->attrs[NL80211_ATTR_BEACON_INTERVAL]);
	params.dtim_period =
		nla_get_u32(info->attrs[NL80211_ATTR_DTIM_PERIOD]);

	err = cfg80211_validate_beacon_पूर्णांक(rdev, dev->ieee80211_ptr->अगरtype,
					   params.beacon_पूर्णांकerval);
	अगर (err)
		वापस err;

	/*
	 * In theory, some of these attributes should be required here
	 * but since they were not used when the command was originally
	 * added, keep them optional क्रम old user space programs to let
	 * them जारी to work with drivers that करो not need the
	 * additional inक्रमmation -- drivers must check!
	 */
	अगर (info->attrs[NL80211_ATTR_SSID]) अणु
		params.ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
		params.ssid_len =
			nla_len(info->attrs[NL80211_ATTR_SSID]);
		अगर (params.ssid_len == 0)
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_HIDDEN_SSID])
		params.hidden_ssid = nla_get_u32(
			info->attrs[NL80211_ATTR_HIDDEN_SSID]);

	params.privacy = !!info->attrs[NL80211_ATTR_PRIVACY];

	अगर (info->attrs[NL80211_ATTR_AUTH_TYPE]) अणु
		params.auth_type = nla_get_u32(
			info->attrs[NL80211_ATTR_AUTH_TYPE]);
		अगर (!nl80211_valid_auth_type(rdev, params.auth_type,
					     NL80211_CMD_START_AP))
			वापस -EINVAL;
	पूर्ण अन्यथा
		params.auth_type = NL80211_AUTHTYPE_AUTOMATIC;

	err = nl80211_crypto_settings(rdev, info, &params.crypto,
				      NL80211_MAX_NR_CIPHER_SUITES);
	अगर (err)
		वापस err;

	अगर (info->attrs[NL80211_ATTR_INACTIVITY_TIMEOUT]) अणु
		अगर (!(rdev->wiphy.features & NL80211_FEATURE_INACTIVITY_TIMER))
			वापस -EOPNOTSUPP;
		params.inactivity_समयout = nla_get_u16(
			info->attrs[NL80211_ATTR_INACTIVITY_TIMEOUT]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_P2P_CTWINDOW]) अणु
		अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
			वापस -EINVAL;
		params.p2p_ctwinकरोw =
			nla_get_u8(info->attrs[NL80211_ATTR_P2P_CTWINDOW]);
		अगर (params.p2p_ctwinकरोw != 0 &&
		    !(rdev->wiphy.features & NL80211_FEATURE_P2P_GO_CTWIN))
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_P2P_OPPPS]) अणु
		u8 पंचांगp;

		अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
			वापस -EINVAL;
		पंचांगp = nla_get_u8(info->attrs[NL80211_ATTR_P2P_OPPPS]);
		params.p2p_opp_ps = पंचांगp;
		अगर (params.p2p_opp_ps != 0 &&
		    !(rdev->wiphy.features & NL80211_FEATURE_P2P_GO_OPPPS))
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ]) अणु
		err = nl80211_parse_chandef(rdev, info, &params.chandef);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अगर (wdev->preset_chandef.chan) अणु
		params.chandef = wdev->preset_chandef;
	पूर्ण अन्यथा अगर (!nl80211_get_ap_channel(rdev, &params))
		वापस -EINVAL;

	अगर (!cfg80211_reg_can_beacon_relax(&rdev->wiphy, &params.chandef,
					   wdev->अगरtype))
		वापस -EINVAL;

	अगर (info->attrs[NL80211_ATTR_TX_RATES]) अणु
		err = nl80211_parse_tx_bitrate_mask(info, info->attrs,
						    NL80211_ATTR_TX_RATES,
						    &params.beacon_rate,
						    dev, false);
		अगर (err)
			वापस err;

		err = validate_beacon_tx_rate(rdev, params.chandef.chan->band,
					      &params.beacon_rate);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_SMPS_MODE]) अणु
		params.smps_mode =
			nla_get_u8(info->attrs[NL80211_ATTR_SMPS_MODE]);
		चयन (params.smps_mode) अणु
		हाल NL80211_SMPS_OFF:
			अवरोध;
		हाल NL80211_SMPS_STATIC:
			अगर (!(rdev->wiphy.features &
			      NL80211_FEATURE_STATIC_SMPS))
				वापस -EINVAL;
			अवरोध;
		हाल NL80211_SMPS_DYNAMIC:
			अगर (!(rdev->wiphy.features &
			      NL80211_FEATURE_DYNAMIC_SMPS))
				वापस -EINVAL;
			अवरोध;
		शेष:
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		params.smps_mode = NL80211_SMPS_OFF;
	पूर्ण

	params.pbss = nla_get_flag(info->attrs[NL80211_ATTR_PBSS]);
	अगर (params.pbss && !rdev->wiphy.bands[NL80211_BAND_60GHZ])
		वापस -EOPNOTSUPP;

	अगर (info->attrs[NL80211_ATTR_ACL_POLICY]) अणु
		params.acl = parse_acl_data(&rdev->wiphy, info);
		अगर (IS_ERR(params.acl))
			वापस PTR_ERR(params.acl);
	पूर्ण

	params.twt_responder =
		    nla_get_flag(info->attrs[NL80211_ATTR_TWT_RESPONDER]);

	अगर (info->attrs[NL80211_ATTR_HE_OBSS_PD]) अणु
		err = nl80211_parse_he_obss_pd(
					info->attrs[NL80211_ATTR_HE_OBSS_PD],
					&params.he_obss_pd);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_HE_BSS_COLOR]) अणु
		err = nl80211_parse_he_bss_color(
					info->attrs[NL80211_ATTR_HE_BSS_COLOR],
					&params.he_bss_color);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_FILS_DISCOVERY]) अणु
		err = nl80211_parse_fils_discovery(rdev,
						   info->attrs[NL80211_ATTR_FILS_DISCOVERY],
						   &params);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_UNSOL_BCAST_PROBE_RESP]) अणु
		err = nl80211_parse_unsol_bcast_probe_resp(
			rdev, info->attrs[NL80211_ATTR_UNSOL_BCAST_PROBE_RESP],
			&params);
		अगर (err)
			जाओ out;
	पूर्ण

	nl80211_calculate_ap_params(&params);

	अगर (info->attrs[NL80211_ATTR_EXTERNAL_AUTH_SUPPORT])
		params.flags |= AP_SETTINGS_EXTERNAL_AUTH_SUPPORT;

	wdev_lock(wdev);
	err = rdev_start_ap(rdev, dev, &params);
	अगर (!err) अणु
		wdev->preset_chandef = params.chandef;
		wdev->beacon_पूर्णांकerval = params.beacon_पूर्णांकerval;
		wdev->chandef = params.chandef;
		wdev->ssid_len = params.ssid_len;
		स_नकल(wdev->ssid, params.ssid, wdev->ssid_len);

		अगर (info->attrs[NL80211_ATTR_SOCKET_OWNER])
			wdev->conn_owner_nlportid = info->snd_portid;
	पूर्ण
	wdev_unlock(wdev);

out:
	kमुक्त(params.acl);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_set_beacon(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_beacon_data params;
	पूर्णांक err;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->change_beacon)
		वापस -EOPNOTSUPP;

	अगर (!wdev->beacon_पूर्णांकerval)
		वापस -EINVAL;

	err = nl80211_parse_beacon(rdev, info->attrs, &params);
	अगर (err)
		वापस err;

	wdev_lock(wdev);
	err = rdev_change_beacon(rdev, dev, &params);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_stop_ap(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];

	वापस cfg80211_stop_ap(rdev, dev, false);
पूर्ण

अटल स्थिर काष्ठा nla_policy sta_flags_policy[NL80211_STA_FLAG_MAX + 1] = अणु
	[NL80211_STA_FLAG_AUTHORIZED] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_STA_FLAG_SHORT_PREAMBLE] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_STA_FLAG_WME] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_STA_FLAG_MFP] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_STA_FLAG_AUTHENTICATED] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_STA_FLAG_TDLS_PEER] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल पूर्णांक parse_station_flags(काष्ठा genl_info *info,
			       क्रमागत nl80211_अगरtype अगरtype,
			       काष्ठा station_parameters *params)
अणु
	काष्ठा nlattr *flags[NL80211_STA_FLAG_MAX + 1];
	काष्ठा nlattr *nla;
	पूर्णांक flag;

	/*
	 * Try parsing the new attribute first so userspace
	 * can specअगरy both क्रम older kernels.
	 */
	nla = info->attrs[NL80211_ATTR_STA_FLAGS2];
	अगर (nla) अणु
		काष्ठा nl80211_sta_flag_update *sta_flags;

		sta_flags = nla_data(nla);
		params->sta_flags_mask = sta_flags->mask;
		params->sta_flags_set = sta_flags->set;
		params->sta_flags_set &= params->sta_flags_mask;
		अगर ((params->sta_flags_mask |
		     params->sta_flags_set) & BIT(__NL80211_STA_FLAG_INVALID))
			वापस -EINVAL;
		वापस 0;
	पूर्ण

	/* अगर present, parse the old attribute */

	nla = info->attrs[NL80211_ATTR_STA_FLAGS];
	अगर (!nla)
		वापस 0;

	अगर (nla_parse_nested_deprecated(flags, NL80211_STA_FLAG_MAX, nla, sta_flags_policy, info->extack))
		वापस -EINVAL;

	/*
	 * Only allow certain flags क्रम पूर्णांकerface types so that
	 * other attributes are silently ignored. Remember that
	 * this is backward compatibility code with old userspace
	 * and shouldn't be hit in other हालs anyway.
	 */
	चयन (अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_GO:
		params->sta_flags_mask = BIT(NL80211_STA_FLAG_AUTHORIZED) |
					 BIT(NL80211_STA_FLAG_SHORT_PREAMBLE) |
					 BIT(NL80211_STA_FLAG_WME) |
					 BIT(NL80211_STA_FLAG_MFP);
		अवरोध;
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_STATION:
		params->sta_flags_mask = BIT(NL80211_STA_FLAG_AUTHORIZED) |
					 BIT(NL80211_STA_FLAG_TDLS_PEER);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		params->sta_flags_mask = BIT(NL80211_STA_FLAG_AUTHENTICATED) |
					 BIT(NL80211_STA_FLAG_MFP) |
					 BIT(NL80211_STA_FLAG_AUTHORIZED);
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	क्रम (flag = 1; flag <= NL80211_STA_FLAG_MAX; flag++) अणु
		अगर (flags[flag]) अणु
			params->sta_flags_set |= (1<<flag);

			/* no दीर्घer support new API additions in old API */
			अगर (flag > NL80211_STA_FLAG_MAX_OLD_API)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

bool nl80211_put_sta_rate(काष्ठा sk_buff *msg, काष्ठा rate_info *info, पूर्णांक attr)
अणु
	काष्ठा nlattr *rate;
	u32 bitrate;
	u16 bitrate_compat;
	क्रमागत nl80211_rate_info rate_flg;

	rate = nla_nest_start_noflag(msg, attr);
	अगर (!rate)
		वापस false;

	/* cfg80211_calculate_bitrate will वापस 0 क्रम mcs >= 32 */
	bitrate = cfg80211_calculate_bitrate(info);
	/* report 16-bit bitrate only अगर we can */
	bitrate_compat = bitrate < (1UL << 16) ? bitrate : 0;
	अगर (bitrate > 0 &&
	    nla_put_u32(msg, NL80211_RATE_INFO_BITRATE32, bitrate))
		वापस false;
	अगर (bitrate_compat > 0 &&
	    nla_put_u16(msg, NL80211_RATE_INFO_BITRATE, bitrate_compat))
		वापस false;

	चयन (info->bw) अणु
	हाल RATE_INFO_BW_5:
		rate_flg = NL80211_RATE_INFO_5_MHZ_WIDTH;
		अवरोध;
	हाल RATE_INFO_BW_10:
		rate_flg = NL80211_RATE_INFO_10_MHZ_WIDTH;
		अवरोध;
	शेष:
		WARN_ON(1);
		fallthrough;
	हाल RATE_INFO_BW_20:
		rate_flg = 0;
		अवरोध;
	हाल RATE_INFO_BW_40:
		rate_flg = NL80211_RATE_INFO_40_MHZ_WIDTH;
		अवरोध;
	हाल RATE_INFO_BW_80:
		rate_flg = NL80211_RATE_INFO_80_MHZ_WIDTH;
		अवरोध;
	हाल RATE_INFO_BW_160:
		rate_flg = NL80211_RATE_INFO_160_MHZ_WIDTH;
		अवरोध;
	हाल RATE_INFO_BW_HE_RU:
		rate_flg = 0;
		WARN_ON(!(info->flags & RATE_INFO_FLAGS_HE_MCS));
	पूर्ण

	अगर (rate_flg && nla_put_flag(msg, rate_flg))
		वापस false;

	अगर (info->flags & RATE_INFO_FLAGS_MCS) अणु
		अगर (nla_put_u8(msg, NL80211_RATE_INFO_MCS, info->mcs))
			वापस false;
		अगर (info->flags & RATE_INFO_FLAGS_SHORT_GI &&
		    nla_put_flag(msg, NL80211_RATE_INFO_SHORT_GI))
			वापस false;
	पूर्ण अन्यथा अगर (info->flags & RATE_INFO_FLAGS_VHT_MCS) अणु
		अगर (nla_put_u8(msg, NL80211_RATE_INFO_VHT_MCS, info->mcs))
			वापस false;
		अगर (nla_put_u8(msg, NL80211_RATE_INFO_VHT_NSS, info->nss))
			वापस false;
		अगर (info->flags & RATE_INFO_FLAGS_SHORT_GI &&
		    nla_put_flag(msg, NL80211_RATE_INFO_SHORT_GI))
			वापस false;
	पूर्ण अन्यथा अगर (info->flags & RATE_INFO_FLAGS_HE_MCS) अणु
		अगर (nla_put_u8(msg, NL80211_RATE_INFO_HE_MCS, info->mcs))
			वापस false;
		अगर (nla_put_u8(msg, NL80211_RATE_INFO_HE_NSS, info->nss))
			वापस false;
		अगर (nla_put_u8(msg, NL80211_RATE_INFO_HE_GI, info->he_gi))
			वापस false;
		अगर (nla_put_u8(msg, NL80211_RATE_INFO_HE_DCM, info->he_dcm))
			वापस false;
		अगर (info->bw == RATE_INFO_BW_HE_RU &&
		    nla_put_u8(msg, NL80211_RATE_INFO_HE_RU_ALLOC,
			       info->he_ru_alloc))
			वापस false;
	पूर्ण

	nla_nest_end(msg, rate);
	वापस true;
पूर्ण

अटल bool nl80211_put_संकेत(काष्ठा sk_buff *msg, u8 mask, s8 *संकेत,
			       पूर्णांक id)
अणु
	व्योम *attr;
	पूर्णांक i = 0;

	अगर (!mask)
		वापस true;

	attr = nla_nest_start_noflag(msg, id);
	अगर (!attr)
		वापस false;

	क्रम (i = 0; i < IEEE80211_MAX_CHAINS; i++) अणु
		अगर (!(mask & BIT(i)))
			जारी;

		अगर (nla_put_u8(msg, i, संकेत[i]))
			वापस false;
	पूर्ण

	nla_nest_end(msg, attr);

	वापस true;
पूर्ण

अटल पूर्णांक nl80211_send_station(काष्ठा sk_buff *msg, u32 cmd, u32 portid,
				u32 seq, पूर्णांक flags,
				काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा net_device *dev,
				स्थिर u8 *mac_addr, काष्ठा station_info *sinfo)
अणु
	व्योम *hdr;
	काष्ठा nlattr *sinfoattr, *bss_param;

	hdr = nl80211hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr) अणु
		cfg80211_sinfo_release_content(sinfo);
		वापस -1;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, mac_addr) ||
	    nla_put_u32(msg, NL80211_ATTR_GENERATION, sinfo->generation))
		जाओ nla_put_failure;

	sinfoattr = nla_nest_start_noflag(msg, NL80211_ATTR_STA_INFO);
	अगर (!sinfoattr)
		जाओ nla_put_failure;

#घोषणा PUT_SINFO(attr, memb, type) करो अणु				\
	BUILD_BUG_ON(माप(type) == माप(u64));			\
	अगर (sinfo->filled & BIT_ULL(NL80211_STA_INFO_ ## attr) &&	\
	    nla_put_ ## type(msg, NL80211_STA_INFO_ ## attr,		\
			     sinfo->memb))				\
		जाओ nla_put_failure;					\
	पूर्ण जबतक (0)
#घोषणा PUT_SINFO_U64(attr, memb) करो अणु					\
	अगर (sinfo->filled & BIT_ULL(NL80211_STA_INFO_ ## attr) &&	\
	    nla_put_u64_64bit(msg, NL80211_STA_INFO_ ## attr,		\
			      sinfo->memb, NL80211_STA_INFO_PAD))	\
		जाओ nla_put_failure;					\
	पूर्ण जबतक (0)

	PUT_SINFO(CONNECTED_TIME, connected_समय, u32);
	PUT_SINFO(INACTIVE_TIME, inactive_समय, u32);
	PUT_SINFO_U64(ASSOC_AT_BOOTTIME, assoc_at);

	अगर (sinfo->filled & (BIT_ULL(NL80211_STA_INFO_RX_BYTES) |
			     BIT_ULL(NL80211_STA_INFO_RX_BYTES64)) &&
	    nla_put_u32(msg, NL80211_STA_INFO_RX_BYTES,
			(u32)sinfo->rx_bytes))
		जाओ nla_put_failure;

	अगर (sinfo->filled & (BIT_ULL(NL80211_STA_INFO_TX_BYTES) |
			     BIT_ULL(NL80211_STA_INFO_TX_BYTES64)) &&
	    nla_put_u32(msg, NL80211_STA_INFO_TX_BYTES,
			(u32)sinfo->tx_bytes))
		जाओ nla_put_failure;

	PUT_SINFO_U64(RX_BYTES64, rx_bytes);
	PUT_SINFO_U64(TX_BYTES64, tx_bytes);
	PUT_SINFO(LLID, llid, u16);
	PUT_SINFO(PLID, plid, u16);
	PUT_SINFO(PLINK_STATE, plink_state, u8);
	PUT_SINFO_U64(RX_DURATION, rx_duration);
	PUT_SINFO_U64(TX_DURATION, tx_duration);

	अगर (wiphy_ext_feature_isset(&rdev->wiphy,
				    NL80211_EXT_FEATURE_AIRTIME_FAIRNESS))
		PUT_SINFO(AIRTIME_WEIGHT, airसमय_weight, u16);

	चयन (rdev->wiphy.संकेत_type) अणु
	हाल CFG80211_SIGNAL_TYPE_MBM:
		PUT_SINFO(SIGNAL, संकेत, u8);
		PUT_SINFO(SIGNAL_AVG, संकेत_avg, u8);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	अगर (sinfo->filled & BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL)) अणु
		अगर (!nl80211_put_संकेत(msg, sinfo->chains,
					sinfo->chain_संकेत,
					NL80211_STA_INFO_CHAIN_SIGNAL))
			जाओ nla_put_failure;
	पूर्ण
	अगर (sinfo->filled & BIT_ULL(NL80211_STA_INFO_CHAIN_SIGNAL_AVG)) अणु
		अगर (!nl80211_put_संकेत(msg, sinfo->chains,
					sinfo->chain_संकेत_avg,
					NL80211_STA_INFO_CHAIN_SIGNAL_AVG))
			जाओ nla_put_failure;
	पूर्ण
	अगर (sinfo->filled & BIT_ULL(NL80211_STA_INFO_TX_BITRATE)) अणु
		अगर (!nl80211_put_sta_rate(msg, &sinfo->txrate,
					  NL80211_STA_INFO_TX_BITRATE))
			जाओ nla_put_failure;
	पूर्ण
	अगर (sinfo->filled & BIT_ULL(NL80211_STA_INFO_RX_BITRATE)) अणु
		अगर (!nl80211_put_sta_rate(msg, &sinfo->rxrate,
					  NL80211_STA_INFO_RX_BITRATE))
			जाओ nla_put_failure;
	पूर्ण

	PUT_SINFO(RX_PACKETS, rx_packets, u32);
	PUT_SINFO(TX_PACKETS, tx_packets, u32);
	PUT_SINFO(TX_RETRIES, tx_retries, u32);
	PUT_SINFO(TX_FAILED, tx_failed, u32);
	PUT_SINFO(EXPECTED_THROUGHPUT, expected_throughput, u32);
	PUT_SINFO(AIRTIME_LINK_METRIC, airसमय_link_metric, u32);
	PUT_SINFO(BEACON_LOSS, beacon_loss_count, u32);
	PUT_SINFO(LOCAL_PM, local_pm, u32);
	PUT_SINFO(PEER_PM, peer_pm, u32);
	PUT_SINFO(NONPEER_PM, nonpeer_pm, u32);
	PUT_SINFO(CONNECTED_TO_GATE, connected_to_gate, u8);
	PUT_SINFO(CONNECTED_TO_AS, connected_to_as, u8);

	अगर (sinfo->filled & BIT_ULL(NL80211_STA_INFO_BSS_PARAM)) अणु
		bss_param = nla_nest_start_noflag(msg,
						  NL80211_STA_INFO_BSS_PARAM);
		अगर (!bss_param)
			जाओ nla_put_failure;

		अगर (((sinfo->bss_param.flags & BSS_PARAM_FLAGS_CTS_PROT) &&
		     nla_put_flag(msg, NL80211_STA_BSS_PARAM_CTS_PROT)) ||
		    ((sinfo->bss_param.flags & BSS_PARAM_FLAGS_SHORT_PREAMBLE) &&
		     nla_put_flag(msg, NL80211_STA_BSS_PARAM_SHORT_PREAMBLE)) ||
		    ((sinfo->bss_param.flags & BSS_PARAM_FLAGS_SHORT_SLOT_TIME) &&
		     nla_put_flag(msg, NL80211_STA_BSS_PARAM_SHORT_SLOT_TIME)) ||
		    nla_put_u8(msg, NL80211_STA_BSS_PARAM_DTIM_PERIOD,
			       sinfo->bss_param.dtim_period) ||
		    nla_put_u16(msg, NL80211_STA_BSS_PARAM_BEACON_INTERVAL,
				sinfo->bss_param.beacon_पूर्णांकerval))
			जाओ nla_put_failure;

		nla_nest_end(msg, bss_param);
	पूर्ण
	अगर ((sinfo->filled & BIT_ULL(NL80211_STA_INFO_STA_FLAGS)) &&
	    nla_put(msg, NL80211_STA_INFO_STA_FLAGS,
		    माप(काष्ठा nl80211_sta_flag_update),
		    &sinfo->sta_flags))
		जाओ nla_put_failure;

	PUT_SINFO_U64(T_OFFSET, t_offset);
	PUT_SINFO_U64(RX_DROP_MISC, rx_dropped_misc);
	PUT_SINFO_U64(BEACON_RX, rx_beacon);
	PUT_SINFO(BEACON_SIGNAL_AVG, rx_beacon_संकेत_avg, u8);
	PUT_SINFO(RX_MPDUS, rx_mpdu_count, u32);
	PUT_SINFO(FCS_ERROR_COUNT, fcs_err_count, u32);
	अगर (wiphy_ext_feature_isset(&rdev->wiphy,
				    NL80211_EXT_FEATURE_ACK_SIGNAL_SUPPORT)) अणु
		PUT_SINFO(ACK_SIGNAL, ack_संकेत, u8);
		PUT_SINFO(ACK_SIGNAL_AVG, avg_ack_संकेत, s8);
	पूर्ण

#अघोषित PUT_SINFO
#अघोषित PUT_SINFO_U64

	अगर (sinfo->pertid) अणु
		काष्ठा nlattr *tidsattr;
		पूर्णांक tid;

		tidsattr = nla_nest_start_noflag(msg,
						 NL80211_STA_INFO_TID_STATS);
		अगर (!tidsattr)
			जाओ nla_put_failure;

		क्रम (tid = 0; tid < IEEE80211_NUM_TIDS + 1; tid++) अणु
			काष्ठा cfg80211_tid_stats *tidstats;
			काष्ठा nlattr *tidattr;

			tidstats = &sinfo->pertid[tid];

			अगर (!tidstats->filled)
				जारी;

			tidattr = nla_nest_start_noflag(msg, tid + 1);
			अगर (!tidattr)
				जाओ nla_put_failure;

#घोषणा PUT_TIDVAL_U64(attr, memb) करो अणु					\
	अगर (tidstats->filled & BIT(NL80211_TID_STATS_ ## attr) &&	\
	    nla_put_u64_64bit(msg, NL80211_TID_STATS_ ## attr,		\
			      tidstats->memb, NL80211_TID_STATS_PAD))	\
		जाओ nla_put_failure;					\
	पूर्ण जबतक (0)

			PUT_TIDVAL_U64(RX_MSDU, rx_msdu);
			PUT_TIDVAL_U64(TX_MSDU, tx_msdu);
			PUT_TIDVAL_U64(TX_MSDU_RETRIES, tx_msdu_retries);
			PUT_TIDVAL_U64(TX_MSDU_FAILED, tx_msdu_failed);

#अघोषित PUT_TIDVAL_U64
			अगर ((tidstats->filled &
			     BIT(NL80211_TID_STATS_TXQ_STATS)) &&
			    !nl80211_put_txq_stats(msg, &tidstats->txq_stats,
						   NL80211_TID_STATS_TXQ_STATS))
				जाओ nla_put_failure;

			nla_nest_end(msg, tidattr);
		पूर्ण

		nla_nest_end(msg, tidsattr);
	पूर्ण

	nla_nest_end(msg, sinfoattr);

	अगर (sinfo->assoc_req_ies_len &&
	    nla_put(msg, NL80211_ATTR_IE, sinfo->assoc_req_ies_len,
		    sinfo->assoc_req_ies))
		जाओ nla_put_failure;

	cfg80211_sinfo_release_content(sinfo);
	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	cfg80211_sinfo_release_content(sinfo);
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_dump_station(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	काष्ठा station_info sinfo;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;
	u8 mac_addr[ETH_ALEN];
	पूर्णांक sta_idx = cb->args[2];
	पूर्णांक err;

	err = nl80211_prepare_wdev_dump(cb, &rdev, &wdev);
	अगर (err)
		वापस err;
	/* nl80211_prepare_wdev_dump acquired it in the successful हाल */
	__acquire(&rdev->wiphy.mtx);

	अगर (!wdev->netdev) अणु
		err = -EINVAL;
		जाओ out_err;
	पूर्ण

	अगर (!rdev->ops->dump_station) अणु
		err = -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण

	जबतक (1) अणु
		स_रखो(&sinfo, 0, माप(sinfo));
		err = rdev_dump_station(rdev, wdev->netdev, sta_idx,
					mac_addr, &sinfo);
		अगर (err == -ENOENT)
			अवरोध;
		अगर (err)
			जाओ out_err;

		अगर (nl80211_send_station(skb, NL80211_CMD_NEW_STATION,
				NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				rdev, wdev->netdev, mac_addr,
				&sinfo) < 0)
			जाओ out;

		sta_idx++;
	पूर्ण

 out:
	cb->args[2] = sta_idx;
	err = skb->len;
 out_err:
	wiphy_unlock(&rdev->wiphy);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_get_station(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा station_info sinfo;
	काष्ठा sk_buff *msg;
	u8 *mac_addr = शून्य;
	पूर्णांक err;

	स_रखो(&sinfo, 0, माप(sinfo));

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	अगर (!rdev->ops->get_station)
		वापस -EOPNOTSUPP;

	err = rdev_get_station(rdev, dev, mac_addr, &sinfo);
	अगर (err)
		वापस err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		cfg80211_sinfo_release_content(&sinfo);
		वापस -ENOMEM;
	पूर्ण

	अगर (nl80211_send_station(msg, NL80211_CMD_NEW_STATION,
				 info->snd_portid, info->snd_seq, 0,
				 rdev, dev, mac_addr, &sinfo) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

पूर्णांक cfg80211_check_station_change(काष्ठा wiphy *wiphy,
				  काष्ठा station_parameters *params,
				  क्रमागत cfg80211_station_type statype)
अणु
	अगर (params->listen_पूर्णांकerval != -1 &&
	    statype != CFG80211_STA_AP_CLIENT_UNASSOC)
		वापस -EINVAL;

	अगर (params->support_p2p_ps != -1 &&
	    statype != CFG80211_STA_AP_CLIENT_UNASSOC)
		वापस -EINVAL;

	अगर (params->aid &&
	    !(params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER)) &&
	    statype != CFG80211_STA_AP_CLIENT_UNASSOC)
		वापस -EINVAL;

	/* When you run पूर्णांकo this, adjust the code below क्रम the new flag */
	BUILD_BUG_ON(NL80211_STA_FLAG_MAX != 7);

	चयन (statype) अणु
	हाल CFG80211_STA_MESH_PEER_KERNEL:
	हाल CFG80211_STA_MESH_PEER_USER:
		/*
		 * No ignoring the TDLS flag here -- the userspace mesh
		 * code करोesn't have the bug of including TDLS in the
		 * mask everywhere.
		 */
		अगर (params->sta_flags_mask &
				~(BIT(NL80211_STA_FLAG_AUTHENTICATED) |
				  BIT(NL80211_STA_FLAG_MFP) |
				  BIT(NL80211_STA_FLAG_AUTHORIZED)))
			वापस -EINVAL;
		अवरोध;
	हाल CFG80211_STA_TDLS_PEER_SETUP:
	हाल CFG80211_STA_TDLS_PEER_ACTIVE:
		अगर (!(params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER)))
			वापस -EINVAL;
		/* ignore since it can't change */
		params->sta_flags_mask &= ~BIT(NL80211_STA_FLAG_TDLS_PEER);
		अवरोध;
	शेष:
		/* disallow mesh-specअगरic things */
		अगर (params->plink_action != NL80211_PLINK_ACTION_NO_ACTION)
			वापस -EINVAL;
		अगर (params->local_pm)
			वापस -EINVAL;
		अगर (params->sta_modअगरy_mask & STATION_PARAM_APPLY_PLINK_STATE)
			वापस -EINVAL;
	पूर्ण

	अगर (statype != CFG80211_STA_TDLS_PEER_SETUP &&
	    statype != CFG80211_STA_TDLS_PEER_ACTIVE) अणु
		/* TDLS can't be set, ... */
		अगर (params->sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER))
			वापस -EINVAL;
		/*
		 * ... but करोn't bother the driver with it. This works around
		 * a hostapd/wpa_supplicant issue -- it always includes the
		 * TLDS_PEER flag in the mask even क्रम AP mode.
		 */
		params->sta_flags_mask &= ~BIT(NL80211_STA_FLAG_TDLS_PEER);
	पूर्ण

	अगर (statype != CFG80211_STA_TDLS_PEER_SETUP &&
	    statype != CFG80211_STA_AP_CLIENT_UNASSOC) अणु
		/* reject other things that can't change */
		अगर (params->sta_modअगरy_mask & STATION_PARAM_APPLY_UAPSD)
			वापस -EINVAL;
		अगर (params->sta_modअगरy_mask & STATION_PARAM_APPLY_CAPABILITY)
			वापस -EINVAL;
		अगर (params->supported_rates)
			वापस -EINVAL;
		अगर (params->ext_capab || params->ht_capa || params->vht_capa ||
		    params->he_capa)
			वापस -EINVAL;
	पूर्ण

	अगर (statype != CFG80211_STA_AP_CLIENT &&
	    statype != CFG80211_STA_AP_CLIENT_UNASSOC) अणु
		अगर (params->vlan)
			वापस -EINVAL;
	पूर्ण

	चयन (statype) अणु
	हाल CFG80211_STA_AP_MLME_CLIENT:
		/* Use this only क्रम authorizing/unauthorizing a station */
		अगर (!(params->sta_flags_mask & BIT(NL80211_STA_FLAG_AUTHORIZED)))
			वापस -EOPNOTSUPP;
		अवरोध;
	हाल CFG80211_STA_AP_CLIENT:
	हाल CFG80211_STA_AP_CLIENT_UNASSOC:
		/* accept only the listed bits */
		अगर (params->sta_flags_mask &
				~(BIT(NL80211_STA_FLAG_AUTHORIZED) |
				  BIT(NL80211_STA_FLAG_AUTHENTICATED) |
				  BIT(NL80211_STA_FLAG_ASSOCIATED) |
				  BIT(NL80211_STA_FLAG_SHORT_PREAMBLE) |
				  BIT(NL80211_STA_FLAG_WME) |
				  BIT(NL80211_STA_FLAG_MFP)))
			वापस -EINVAL;

		/* but authenticated/associated only अगर driver handles it */
		अगर (!(wiphy->features & NL80211_FEATURE_FULL_AP_CLIENT_STATE) &&
		    params->sta_flags_mask &
				(BIT(NL80211_STA_FLAG_AUTHENTICATED) |
				 BIT(NL80211_STA_FLAG_ASSOCIATED)))
			वापस -EINVAL;
		अवरोध;
	हाल CFG80211_STA_IBSS:
	हाल CFG80211_STA_AP_STA:
		/* reject any changes other than AUTHORIZED */
		अगर (params->sta_flags_mask & ~BIT(NL80211_STA_FLAG_AUTHORIZED))
			वापस -EINVAL;
		अवरोध;
	हाल CFG80211_STA_TDLS_PEER_SETUP:
		/* reject any changes other than AUTHORIZED or WME */
		अगर (params->sta_flags_mask & ~(BIT(NL80211_STA_FLAG_AUTHORIZED) |
					       BIT(NL80211_STA_FLAG_WME)))
			वापस -EINVAL;
		/* क्रमce (at least) rates when authorizing */
		अगर (params->sta_flags_set & BIT(NL80211_STA_FLAG_AUTHORIZED) &&
		    !params->supported_rates)
			वापस -EINVAL;
		अवरोध;
	हाल CFG80211_STA_TDLS_PEER_ACTIVE:
		/* reject any changes */
		वापस -EINVAL;
	हाल CFG80211_STA_MESH_PEER_KERNEL:
		अगर (params->sta_modअगरy_mask & STATION_PARAM_APPLY_PLINK_STATE)
			वापस -EINVAL;
		अवरोध;
	हाल CFG80211_STA_MESH_PEER_USER:
		अगर (params->plink_action != NL80211_PLINK_ACTION_NO_ACTION &&
		    params->plink_action != NL80211_PLINK_ACTION_BLOCK)
			वापस -EINVAL;
		अवरोध;
	पूर्ण

	/*
	 * Older kernel versions ignored this attribute entirely, so करोn't
	 * reject attempts to update it but mark it as unused instead so the
	 * driver won't look at the data.
	 */
	अगर (statype != CFG80211_STA_AP_CLIENT_UNASSOC &&
	    statype != CFG80211_STA_TDLS_PEER_SETUP)
		params->opmode_notअगर_used = false;

	वापस 0;
पूर्ण
EXPORT_SYMBOL(cfg80211_check_station_change);

/*
 * Get vlan पूर्णांकerface making sure it is running and on the right wiphy.
 */
अटल काष्ठा net_device *get_vlan(काष्ठा genl_info *info,
				   काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा nlattr *vlanattr = info->attrs[NL80211_ATTR_STA_VLAN];
	काष्ठा net_device *v;
	पूर्णांक ret;

	अगर (!vlanattr)
		वापस शून्य;

	v = dev_get_by_index(genl_info_net(info), nla_get_u32(vlanattr));
	अगर (!v)
		वापस ERR_PTR(-ENODEV);

	अगर (!v->ieee80211_ptr || v->ieee80211_ptr->wiphy != &rdev->wiphy) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (v->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP_VLAN &&
	    v->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP &&
	    v->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO) अणु
		ret = -EINVAL;
		जाओ error;
	पूर्ण

	अगर (!netअगर_running(v)) अणु
		ret = -ENETDOWN;
		जाओ error;
	पूर्ण

	वापस v;
 error:
	dev_put(v);
	वापस ERR_PTR(ret);
पूर्ण

अटल स्थिर काष्ठा nla_policy
nl80211_sta_wme_policy[NL80211_STA_WME_MAX + 1] = अणु
	[NL80211_STA_WME_UAPSD_QUEUES] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_STA_WME_MAX_SP] = अणु .type = NLA_U8 पूर्ण,
पूर्ण;

अटल पूर्णांक nl80211_parse_sta_wme(काष्ठा genl_info *info,
				 काष्ठा station_parameters *params)
अणु
	काष्ठा nlattr *tb[NL80211_STA_WME_MAX + 1];
	काष्ठा nlattr *nla;
	पूर्णांक err;

	/* parse WME attributes अगर present */
	अगर (!info->attrs[NL80211_ATTR_STA_WME])
		वापस 0;

	nla = info->attrs[NL80211_ATTR_STA_WME];
	err = nla_parse_nested_deprecated(tb, NL80211_STA_WME_MAX, nla,
					  nl80211_sta_wme_policy,
					  info->extack);
	अगर (err)
		वापस err;

	अगर (tb[NL80211_STA_WME_UAPSD_QUEUES])
		params->uapsd_queues = nla_get_u8(
			tb[NL80211_STA_WME_UAPSD_QUEUES]);
	अगर (params->uapsd_queues & ~IEEE80211_WMM_IE_STA_QOSINFO_AC_MASK)
		वापस -EINVAL;

	अगर (tb[NL80211_STA_WME_MAX_SP])
		params->max_sp = nla_get_u8(tb[NL80211_STA_WME_MAX_SP]);

	अगर (params->max_sp & ~IEEE80211_WMM_IE_STA_QOSINFO_SP_MASK)
		वापस -EINVAL;

	params->sta_modअगरy_mask |= STATION_PARAM_APPLY_UAPSD;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_sta_channel_info(काष्ठा genl_info *info,
				      काष्ठा station_parameters *params)
अणु
	अगर (info->attrs[NL80211_ATTR_STA_SUPPORTED_CHANNELS]) अणु
		params->supported_channels =
		     nla_data(info->attrs[NL80211_ATTR_STA_SUPPORTED_CHANNELS]);
		params->supported_channels_len =
		     nla_len(info->attrs[NL80211_ATTR_STA_SUPPORTED_CHANNELS]);
		/*
		 * Need to include at least one (first channel, number of
		 * channels) tuple क्रम each subband (checked in policy),
		 * and must have proper tuples क्रम the rest of the data as well.
		 */
		अगर (params->supported_channels_len % 2)
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES]) अणु
		params->supported_oper_classes =
		 nla_data(info->attrs[NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES]);
		params->supported_oper_classes_len =
		  nla_len(info->attrs[NL80211_ATTR_STA_SUPPORTED_OPER_CLASSES]);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_set_station_tdls(काष्ठा genl_info *info,
				    काष्ठा station_parameters *params)
अणु
	पूर्णांक err;
	/* Dummy STA entry माला_लो updated once the peer capabilities are known */
	अगर (info->attrs[NL80211_ATTR_PEER_AID])
		params->aid = nla_get_u16(info->attrs[NL80211_ATTR_PEER_AID]);
	अगर (info->attrs[NL80211_ATTR_HT_CAPABILITY])
		params->ht_capa =
			nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY]);
	अगर (info->attrs[NL80211_ATTR_VHT_CAPABILITY])
		params->vht_capa =
			nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY]);
	अगर (info->attrs[NL80211_ATTR_HE_CAPABILITY]) अणु
		params->he_capa =
			nla_data(info->attrs[NL80211_ATTR_HE_CAPABILITY]);
		params->he_capa_len =
			nla_len(info->attrs[NL80211_ATTR_HE_CAPABILITY]);
	पूर्ण

	err = nl80211_parse_sta_channel_info(info, params);
	अगर (err)
		वापस err;

	वापस nl80211_parse_sta_wme(info, params);
पूर्ण

अटल पूर्णांक nl80211_parse_sta_txघातer_setting(काष्ठा genl_info *info,
					     काष्ठा station_parameters *params)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक idx;

	अगर (info->attrs[NL80211_ATTR_STA_TX_POWER_SETTING]) अणु
		अगर (!rdev->ops->set_tx_घातer ||
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					 NL80211_EXT_FEATURE_STA_TX_PWR))
			वापस -EOPNOTSUPP;

		idx = NL80211_ATTR_STA_TX_POWER_SETTING;
		params->txpwr.type = nla_get_u8(info->attrs[idx]);

		अगर (params->txpwr.type == NL80211_TX_POWER_LIMITED) अणु
			idx = NL80211_ATTR_STA_TX_POWER;

			अगर (info->attrs[idx])
				params->txpwr.घातer =
					nla_get_s16(info->attrs[idx]);
			अन्यथा
				वापस -EINVAL;
		पूर्ण
		params->sta_modअगरy_mask |= STATION_PARAM_APPLY_STA_TXPOWER;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_set_station(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा station_parameters params;
	u8 *mac_addr;
	पूर्णांक err;

	स_रखो(&params, 0, माप(params));

	अगर (!rdev->ops->change_station)
		वापस -EOPNOTSUPP;

	/*
	 * AID and listen_पूर्णांकerval properties can be set only क्रम unassociated
	 * station. Include these parameters here and will check them in
	 * cfg80211_check_station_change().
	 */
	अगर (info->attrs[NL80211_ATTR_STA_AID])
		params.aid = nla_get_u16(info->attrs[NL80211_ATTR_STA_AID]);

	अगर (info->attrs[NL80211_ATTR_VLAN_ID])
		params.vlan_id = nla_get_u16(info->attrs[NL80211_ATTR_VLAN_ID]);

	अगर (info->attrs[NL80211_ATTR_STA_LISTEN_INTERVAL])
		params.listen_पूर्णांकerval =
		     nla_get_u16(info->attrs[NL80211_ATTR_STA_LISTEN_INTERVAL]);
	अन्यथा
		params.listen_पूर्णांकerval = -1;

	अगर (info->attrs[NL80211_ATTR_STA_SUPPORT_P2P_PS])
		params.support_p2p_ps =
			nla_get_u8(info->attrs[NL80211_ATTR_STA_SUPPORT_P2P_PS]);
	अन्यथा
		params.support_p2p_ps = -1;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	अगर (info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES]) अणु
		params.supported_rates =
			nla_data(info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES]);
		params.supported_rates_len =
			nla_len(info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_STA_CAPABILITY]) अणु
		params.capability =
			nla_get_u16(info->attrs[NL80211_ATTR_STA_CAPABILITY]);
		params.sta_modअगरy_mask |= STATION_PARAM_APPLY_CAPABILITY;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]) अणु
		params.ext_capab =
			nla_data(info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]);
		params.ext_capab_len =
			nla_len(info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]);
	पूर्ण

	अगर (parse_station_flags(info, dev->ieee80211_ptr->अगरtype, &params))
		वापस -EINVAL;

	अगर (info->attrs[NL80211_ATTR_STA_PLINK_ACTION])
		params.plink_action =
			nla_get_u8(info->attrs[NL80211_ATTR_STA_PLINK_ACTION]);

	अगर (info->attrs[NL80211_ATTR_STA_PLINK_STATE]) अणु
		params.plink_state =
			nla_get_u8(info->attrs[NL80211_ATTR_STA_PLINK_STATE]);
		अगर (info->attrs[NL80211_ATTR_MESH_PEER_AID])
			params.peer_aid = nla_get_u16(
				info->attrs[NL80211_ATTR_MESH_PEER_AID]);
		params.sta_modअगरy_mask |= STATION_PARAM_APPLY_PLINK_STATE;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_LOCAL_MESH_POWER_MODE])
		params.local_pm = nla_get_u32(
			info->attrs[NL80211_ATTR_LOCAL_MESH_POWER_MODE]);

	अगर (info->attrs[NL80211_ATTR_OPMODE_NOTIF]) अणु
		params.opmode_notअगर_used = true;
		params.opmode_notअगर =
			nla_get_u8(info->attrs[NL80211_ATTR_OPMODE_NOTIF]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_HE_6GHZ_CAPABILITY])
		params.he_6ghz_capa =
			nla_data(info->attrs[NL80211_ATTR_HE_6GHZ_CAPABILITY]);

	अगर (info->attrs[NL80211_ATTR_AIRTIME_WEIGHT])
		params.airसमय_weight =
			nla_get_u16(info->attrs[NL80211_ATTR_AIRTIME_WEIGHT]);

	अगर (params.airसमय_weight &&
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_AIRTIME_FAIRNESS))
		वापस -EOPNOTSUPP;

	err = nl80211_parse_sta_txघातer_setting(info, &params);
	अगर (err)
		वापस err;

	/* Include parameters क्रम TDLS peer (will check later) */
	err = nl80211_set_station_tdls(info, &params);
	अगर (err)
		वापस err;

	params.vlan = get_vlan(info, rdev);
	अगर (IS_ERR(params.vlan))
		वापस PTR_ERR(params.vlan);

	चयन (dev->ieee80211_ptr->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_MESH_POINT:
		अवरोध;
	शेष:
		err = -EOPNOTSUPP;
		जाओ out_put_vlan;
	पूर्ण

	/* driver will call cfg80211_check_station_change() */
	err = rdev_change_station(rdev, dev, mac_addr, &params);

 out_put_vlan:
	अगर (params.vlan)
		dev_put(params.vlan);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_new_station(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक err;
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा station_parameters params;
	u8 *mac_addr = शून्य;
	u32 auth_assoc = BIT(NL80211_STA_FLAG_AUTHENTICATED) |
			 BIT(NL80211_STA_FLAG_ASSOCIATED);

	स_रखो(&params, 0, माप(params));

	अगर (!rdev->ops->add_station)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_STA_LISTEN_INTERVAL])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_STA_AID] &&
	    !info->attrs[NL80211_ATTR_PEER_AID])
		वापस -EINVAL;

	mac_addr = nla_data(info->attrs[NL80211_ATTR_MAC]);
	params.supported_rates =
		nla_data(info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES]);
	params.supported_rates_len =
		nla_len(info->attrs[NL80211_ATTR_STA_SUPPORTED_RATES]);
	params.listen_पूर्णांकerval =
		nla_get_u16(info->attrs[NL80211_ATTR_STA_LISTEN_INTERVAL]);

	अगर (info->attrs[NL80211_ATTR_VLAN_ID])
		params.vlan_id = nla_get_u16(info->attrs[NL80211_ATTR_VLAN_ID]);

	अगर (info->attrs[NL80211_ATTR_STA_SUPPORT_P2P_PS]) अणु
		params.support_p2p_ps =
			nla_get_u8(info->attrs[NL80211_ATTR_STA_SUPPORT_P2P_PS]);
	पूर्ण अन्यथा अणु
		/*
		 * अगर not specअगरied, assume it's supported क्रम P2P GO पूर्णांकerface,
		 * and is NOT supported क्रम AP पूर्णांकerface
		 */
		params.support_p2p_ps =
			dev->ieee80211_ptr->अगरtype == NL80211_IFTYPE_P2P_GO;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_PEER_AID])
		params.aid = nla_get_u16(info->attrs[NL80211_ATTR_PEER_AID]);
	अन्यथा
		params.aid = nla_get_u16(info->attrs[NL80211_ATTR_STA_AID]);

	अगर (info->attrs[NL80211_ATTR_STA_CAPABILITY]) अणु
		params.capability =
			nla_get_u16(info->attrs[NL80211_ATTR_STA_CAPABILITY]);
		params.sta_modअगरy_mask |= STATION_PARAM_APPLY_CAPABILITY;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]) अणु
		params.ext_capab =
			nla_data(info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]);
		params.ext_capab_len =
			nla_len(info->attrs[NL80211_ATTR_STA_EXT_CAPABILITY]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_HT_CAPABILITY])
		params.ht_capa =
			nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY]);

	अगर (info->attrs[NL80211_ATTR_VHT_CAPABILITY])
		params.vht_capa =
			nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY]);

	अगर (info->attrs[NL80211_ATTR_HE_CAPABILITY]) अणु
		params.he_capa =
			nla_data(info->attrs[NL80211_ATTR_HE_CAPABILITY]);
		params.he_capa_len =
			nla_len(info->attrs[NL80211_ATTR_HE_CAPABILITY]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_HE_6GHZ_CAPABILITY])
		params.he_6ghz_capa =
			nla_data(info->attrs[NL80211_ATTR_HE_6GHZ_CAPABILITY]);

	अगर (info->attrs[NL80211_ATTR_OPMODE_NOTIF]) अणु
		params.opmode_notअगर_used = true;
		params.opmode_notअगर =
			nla_get_u8(info->attrs[NL80211_ATTR_OPMODE_NOTIF]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_STA_PLINK_ACTION])
		params.plink_action =
			nla_get_u8(info->attrs[NL80211_ATTR_STA_PLINK_ACTION]);

	अगर (info->attrs[NL80211_ATTR_AIRTIME_WEIGHT])
		params.airसमय_weight =
			nla_get_u16(info->attrs[NL80211_ATTR_AIRTIME_WEIGHT]);

	अगर (params.airसमय_weight &&
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_AIRTIME_FAIRNESS))
		वापस -EOPNOTSUPP;

	err = nl80211_parse_sta_txघातer_setting(info, &params);
	अगर (err)
		वापस err;

	err = nl80211_parse_sta_channel_info(info, &params);
	अगर (err)
		वापस err;

	err = nl80211_parse_sta_wme(info, &params);
	अगर (err)
		वापस err;

	अगर (parse_station_flags(info, dev->ieee80211_ptr->अगरtype, &params))
		वापस -EINVAL;

	/* HT/VHT requires QoS, but अगर we करोn't have that just ignore HT/VHT
	 * as userspace might just pass through the capabilities from the IEs
	 * directly, rather than enक्रमcing this restriction and वापसing an
	 * error in this हाल.
	 */
	अगर (!(params.sta_flags_set & BIT(NL80211_STA_FLAG_WME))) अणु
		params.ht_capa = शून्य;
		params.vht_capa = शून्य;

		/* HE requires WME */
		अगर (params.he_capa_len || params.he_6ghz_capa)
			वापस -EINVAL;
	पूर्ण

	/* Ensure that HT/VHT capabilities are not set क्रम 6 GHz HE STA */
	अगर (params.he_6ghz_capa && (params.ht_capa || params.vht_capa))
		वापस -EINVAL;

	/* When you run पूर्णांकo this, adjust the code below क्रम the new flag */
	BUILD_BUG_ON(NL80211_STA_FLAG_MAX != 7);

	चयन (dev->ieee80211_ptr->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_GO:
		/* ignore WME attributes अगर अगरace/sta is not capable */
		अगर (!(rdev->wiphy.flags & WIPHY_FLAG_AP_UAPSD) ||
		    !(params.sta_flags_set & BIT(NL80211_STA_FLAG_WME)))
			params.sta_modअगरy_mask &= ~STATION_PARAM_APPLY_UAPSD;

		/* TDLS peers cannot be added */
		अगर ((params.sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER)) ||
		    info->attrs[NL80211_ATTR_PEER_AID])
			वापस -EINVAL;
		/* but करोn't bother the driver with it */
		params.sta_flags_mask &= ~BIT(NL80211_STA_FLAG_TDLS_PEER);

		/* allow authenticated/associated only अगर driver handles it */
		अगर (!(rdev->wiphy.features &
				NL80211_FEATURE_FULL_AP_CLIENT_STATE) &&
		    params.sta_flags_mask & auth_assoc)
			वापस -EINVAL;

		/* Older userspace, or userspace wanting to be compatible with
		 * !NL80211_FEATURE_FULL_AP_CLIENT_STATE, will not set the auth
		 * and assoc flags in the mask, but assumes the station will be
		 * added as associated anyway since this was the required driver
		 * behaviour beक्रमe NL80211_FEATURE_FULL_AP_CLIENT_STATE was
		 * पूर्णांकroduced.
		 * In order to not bother drivers with this quirk in the API
		 * set the flags in both the mask and set क्रम new stations in
		 * this हाल.
		 */
		अगर (!(params.sta_flags_mask & auth_assoc)) अणु
			params.sta_flags_mask |= auth_assoc;
			params.sta_flags_set |= auth_assoc;
		पूर्ण

		/* must be last in here क्रम error handling */
		params.vlan = get_vlan(info, rdev);
		अगर (IS_ERR(params.vlan))
			वापस PTR_ERR(params.vlan);
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		/* ignore uAPSD data */
		params.sta_modअगरy_mask &= ~STATION_PARAM_APPLY_UAPSD;

		/* associated is disallowed */
		अगर (params.sta_flags_mask & BIT(NL80211_STA_FLAG_ASSOCIATED))
			वापस -EINVAL;
		/* TDLS peers cannot be added */
		अगर ((params.sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER)) ||
		    info->attrs[NL80211_ATTR_PEER_AID])
			वापस -EINVAL;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		/* ignore uAPSD data */
		params.sta_modअगरy_mask &= ~STATION_PARAM_APPLY_UAPSD;

		/* these are disallowed */
		अगर (params.sta_flags_mask &
				(BIT(NL80211_STA_FLAG_ASSOCIATED) |
				 BIT(NL80211_STA_FLAG_AUTHENTICATED)))
			वापस -EINVAL;
		/* Only TDLS peers can be added */
		अगर (!(params.sta_flags_set & BIT(NL80211_STA_FLAG_TDLS_PEER)))
			वापस -EINVAL;
		/* Can only add अगर TDLS ... */
		अगर (!(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_TDLS))
			वापस -EOPNOTSUPP;
		/* ... with बाह्यal setup is supported */
		अगर (!(rdev->wiphy.flags & WIPHY_FLAG_TDLS_EXTERNAL_SETUP))
			वापस -EOPNOTSUPP;
		/*
		 * Older wpa_supplicant versions always mark the TDLS peer
		 * as authorized, but it shouldn't yet be.
		 */
		params.sta_flags_mask &= ~BIT(NL80211_STA_FLAG_AUTHORIZED);
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* be aware of params.vlan when changing code here */

	err = rdev_add_station(rdev, dev, mac_addr, &params);

	अगर (params.vlan)
		dev_put(params.vlan);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_del_station(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा station_del_parameters params;

	स_रखो(&params, 0, माप(params));

	अगर (info->attrs[NL80211_ATTR_MAC])
		params.mac = nla_data(info->attrs[NL80211_ATTR_MAC]);

	चयन (dev->ieee80211_ptr->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_P2P_GO:
		/* always accept these */
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		/* conditionally accept */
		अगर (wiphy_ext_feature_isset(&rdev->wiphy,
					    NL80211_EXT_FEATURE_DEL_IBSS_STA))
			अवरोध;
		वापस -EINVAL;
	शेष:
		वापस -EINVAL;
	पूर्ण

	अगर (!rdev->ops->del_station)
		वापस -EOPNOTSUPP;

	अगर (info->attrs[NL80211_ATTR_MGMT_SUBTYPE]) अणु
		params.subtype =
			nla_get_u8(info->attrs[NL80211_ATTR_MGMT_SUBTYPE]);
		अगर (params.subtype != IEEE80211_STYPE_DISASSOC >> 4 &&
		    params.subtype != IEEE80211_STYPE_DEAUTH >> 4)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		/* Default to Deauthentication frame */
		params.subtype = IEEE80211_STYPE_DEAUTH >> 4;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_REASON_CODE]) अणु
		params.reason_code =
			nla_get_u16(info->attrs[NL80211_ATTR_REASON_CODE]);
		अगर (params.reason_code == 0)
			वापस -EINVAL; /* 0 is reserved */
	पूर्ण अन्यथा अणु
		/* Default to reason code 2 */
		params.reason_code = WLAN_REASON_PREV_AUTH_NOT_VALID;
	पूर्ण

	वापस rdev_del_station(rdev, dev, &params);
पूर्ण

अटल पूर्णांक nl80211_send_mpath(काष्ठा sk_buff *msg, u32 portid, u32 seq,
				पूर्णांक flags, काष्ठा net_device *dev,
				u8 *dst, u8 *next_hop,
				काष्ठा mpath_info *pinfo)
अणु
	व्योम *hdr;
	काष्ठा nlattr *pinfoattr;

	hdr = nl80211hdr_put(msg, portid, seq, flags, NL80211_CMD_NEW_MPATH);
	अगर (!hdr)
		वापस -1;

	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, dst) ||
	    nla_put(msg, NL80211_ATTR_MPATH_NEXT_HOP, ETH_ALEN, next_hop) ||
	    nla_put_u32(msg, NL80211_ATTR_GENERATION, pinfo->generation))
		जाओ nla_put_failure;

	pinfoattr = nla_nest_start_noflag(msg, NL80211_ATTR_MPATH_INFO);
	अगर (!pinfoattr)
		जाओ nla_put_failure;
	अगर ((pinfo->filled & MPATH_INFO_FRAME_QLEN) &&
	    nla_put_u32(msg, NL80211_MPATH_INFO_FRAME_QLEN,
			pinfo->frame_qlen))
		जाओ nla_put_failure;
	अगर (((pinfo->filled & MPATH_INFO_SN) &&
	     nla_put_u32(msg, NL80211_MPATH_INFO_SN, pinfo->sn)) ||
	    ((pinfo->filled & MPATH_INFO_METRIC) &&
	     nla_put_u32(msg, NL80211_MPATH_INFO_METRIC,
			 pinfo->metric)) ||
	    ((pinfo->filled & MPATH_INFO_EXPTIME) &&
	     nla_put_u32(msg, NL80211_MPATH_INFO_EXPTIME,
			 pinfo->expसमय)) ||
	    ((pinfo->filled & MPATH_INFO_FLAGS) &&
	     nla_put_u8(msg, NL80211_MPATH_INFO_FLAGS,
			pinfo->flags)) ||
	    ((pinfo->filled & MPATH_INFO_DISCOVERY_TIMEOUT) &&
	     nla_put_u32(msg, NL80211_MPATH_INFO_DISCOVERY_TIMEOUT,
			 pinfo->discovery_समयout)) ||
	    ((pinfo->filled & MPATH_INFO_DISCOVERY_RETRIES) &&
	     nla_put_u8(msg, NL80211_MPATH_INFO_DISCOVERY_RETRIES,
			pinfo->discovery_retries)) ||
	    ((pinfo->filled & MPATH_INFO_HOP_COUNT) &&
	     nla_put_u8(msg, NL80211_MPATH_INFO_HOP_COUNT,
			pinfo->hop_count)) ||
	    ((pinfo->filled & MPATH_INFO_PATH_CHANGE) &&
	     nla_put_u32(msg, NL80211_MPATH_INFO_PATH_CHANGE,
			 pinfo->path_change_count)))
		जाओ nla_put_failure;

	nla_nest_end(msg, pinfoattr);

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_dump_mpath(काष्ठा sk_buff *skb,
			      काष्ठा netlink_callback *cb)
अणु
	काष्ठा mpath_info pinfo;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;
	u8 dst[ETH_ALEN];
	u8 next_hop[ETH_ALEN];
	पूर्णांक path_idx = cb->args[2];
	पूर्णांक err;

	err = nl80211_prepare_wdev_dump(cb, &rdev, &wdev);
	अगर (err)
		वापस err;
	/* nl80211_prepare_wdev_dump acquired it in the successful हाल */
	__acquire(&rdev->wiphy.mtx);

	अगर (!rdev->ops->dump_mpath) अणु
		err = -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण

	अगर (wdev->अगरtype != NL80211_IFTYPE_MESH_POINT) अणु
		err = -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण

	जबतक (1) अणु
		err = rdev_dump_mpath(rdev, wdev->netdev, path_idx, dst,
				      next_hop, &pinfo);
		अगर (err == -ENOENT)
			अवरोध;
		अगर (err)
			जाओ out_err;

		अगर (nl80211_send_mpath(skb, NETLINK_CB(cb->skb).portid,
				       cb->nlh->nlmsg_seq, NLM_F_MULTI,
				       wdev->netdev, dst, next_hop,
				       &pinfo) < 0)
			जाओ out;

		path_idx++;
	पूर्ण

 out:
	cb->args[2] = path_idx;
	err = skb->len;
 out_err:
	wiphy_unlock(&rdev->wiphy);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_get_mpath(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक err;
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा mpath_info pinfo;
	काष्ठा sk_buff *msg;
	u8 *dst = शून्य;
	u8 next_hop[ETH_ALEN];

	स_रखो(&pinfo, 0, माप(pinfo));

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	dst = nla_data(info->attrs[NL80211_ATTR_MAC]);

	अगर (!rdev->ops->get_mpath)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	err = rdev_get_mpath(rdev, dev, dst, next_hop, &pinfo);
	अगर (err)
		वापस err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nl80211_send_mpath(msg, info->snd_portid, info->snd_seq, 0,
				 dev, dst, next_hop, &pinfo) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक nl80211_set_mpath(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	u8 *dst = शून्य;
	u8 *next_hop = शून्य;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_MPATH_NEXT_HOP])
		वापस -EINVAL;

	dst = nla_data(info->attrs[NL80211_ATTR_MAC]);
	next_hop = nla_data(info->attrs[NL80211_ATTR_MPATH_NEXT_HOP]);

	अगर (!rdev->ops->change_mpath)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	वापस rdev_change_mpath(rdev, dev, dst, next_hop);
पूर्ण

अटल पूर्णांक nl80211_new_mpath(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	u8 *dst = शून्य;
	u8 *next_hop = शून्य;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_MPATH_NEXT_HOP])
		वापस -EINVAL;

	dst = nla_data(info->attrs[NL80211_ATTR_MAC]);
	next_hop = nla_data(info->attrs[NL80211_ATTR_MPATH_NEXT_HOP]);

	अगर (!rdev->ops->add_mpath)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	वापस rdev_add_mpath(rdev, dev, dst, next_hop);
पूर्ण

अटल पूर्णांक nl80211_del_mpath(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	u8 *dst = शून्य;

	अगर (info->attrs[NL80211_ATTR_MAC])
		dst = nla_data(info->attrs[NL80211_ATTR_MAC]);

	अगर (!rdev->ops->del_mpath)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	वापस rdev_del_mpath(rdev, dev, dst);
पूर्ण

अटल पूर्णांक nl80211_get_mpp(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक err;
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा mpath_info pinfo;
	काष्ठा sk_buff *msg;
	u8 *dst = शून्य;
	u8 mpp[ETH_ALEN];

	स_रखो(&pinfo, 0, माप(pinfo));

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	dst = nla_data(info->attrs[NL80211_ATTR_MAC]);

	अगर (!rdev->ops->get_mpp)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	err = rdev_get_mpp(rdev, dev, dst, mpp, &pinfo);
	अगर (err)
		वापस err;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nl80211_send_mpath(msg, info->snd_portid, info->snd_seq, 0,
			       dev, dst, mpp, &pinfo) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	वापस genlmsg_reply(msg, info);
पूर्ण

अटल पूर्णांक nl80211_dump_mpp(काष्ठा sk_buff *skb,
			    काष्ठा netlink_callback *cb)
अणु
	काष्ठा mpath_info pinfo;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;
	u8 dst[ETH_ALEN];
	u8 mpp[ETH_ALEN];
	पूर्णांक path_idx = cb->args[2];
	पूर्णांक err;

	err = nl80211_prepare_wdev_dump(cb, &rdev, &wdev);
	अगर (err)
		वापस err;
	/* nl80211_prepare_wdev_dump acquired it in the successful हाल */
	__acquire(&rdev->wiphy.mtx);

	अगर (!rdev->ops->dump_mpp) अणु
		err = -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण

	अगर (wdev->अगरtype != NL80211_IFTYPE_MESH_POINT) अणु
		err = -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण

	जबतक (1) अणु
		err = rdev_dump_mpp(rdev, wdev->netdev, path_idx, dst,
				    mpp, &pinfo);
		अगर (err == -ENOENT)
			अवरोध;
		अगर (err)
			जाओ out_err;

		अगर (nl80211_send_mpath(skb, NETLINK_CB(cb->skb).portid,
				       cb->nlh->nlmsg_seq, NLM_F_MULTI,
				       wdev->netdev, dst, mpp,
				       &pinfo) < 0)
			जाओ out;

		path_idx++;
	पूर्ण

 out:
	cb->args[2] = path_idx;
	err = skb->len;
 out_err:
	wiphy_unlock(&rdev->wiphy);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_set_bss(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा bss_parameters params;
	पूर्णांक err;

	स_रखो(&params, 0, माप(params));
	/* शेष to not changing parameters */
	params.use_cts_prot = -1;
	params.use_लघु_preamble = -1;
	params.use_लघु_slot_समय = -1;
	params.ap_isolate = -1;
	params.ht_opmode = -1;
	params.p2p_ctwinकरोw = -1;
	params.p2p_opp_ps = -1;

	अगर (info->attrs[NL80211_ATTR_BSS_CTS_PROT])
		params.use_cts_prot =
		    nla_get_u8(info->attrs[NL80211_ATTR_BSS_CTS_PROT]);
	अगर (info->attrs[NL80211_ATTR_BSS_SHORT_PREAMBLE])
		params.use_लघु_preamble =
		    nla_get_u8(info->attrs[NL80211_ATTR_BSS_SHORT_PREAMBLE]);
	अगर (info->attrs[NL80211_ATTR_BSS_SHORT_SLOT_TIME])
		params.use_लघु_slot_समय =
		    nla_get_u8(info->attrs[NL80211_ATTR_BSS_SHORT_SLOT_TIME]);
	अगर (info->attrs[NL80211_ATTR_BSS_BASIC_RATES]) अणु
		params.basic_rates =
			nla_data(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		params.basic_rates_len =
			nla_len(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
	पूर्ण
	अगर (info->attrs[NL80211_ATTR_AP_ISOLATE])
		params.ap_isolate = !!nla_get_u8(info->attrs[NL80211_ATTR_AP_ISOLATE]);
	अगर (info->attrs[NL80211_ATTR_BSS_HT_OPMODE])
		params.ht_opmode =
			nla_get_u16(info->attrs[NL80211_ATTR_BSS_HT_OPMODE]);

	अगर (info->attrs[NL80211_ATTR_P2P_CTWINDOW]) अणु
		अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
			वापस -EINVAL;
		params.p2p_ctwinकरोw =
			nla_get_u8(info->attrs[NL80211_ATTR_P2P_CTWINDOW]);
		अगर (params.p2p_ctwinकरोw != 0 &&
		    !(rdev->wiphy.features & NL80211_FEATURE_P2P_GO_CTWIN))
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_P2P_OPPPS]) अणु
		u8 पंचांगp;

		अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
			वापस -EINVAL;
		पंचांगp = nla_get_u8(info->attrs[NL80211_ATTR_P2P_OPPPS]);
		params.p2p_opp_ps = पंचांगp;
		अगर (params.p2p_opp_ps &&
		    !(rdev->wiphy.features & NL80211_FEATURE_P2P_GO_OPPPS))
			वापस -EINVAL;
	पूर्ण

	अगर (!rdev->ops->change_bss)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EOPNOTSUPP;

	wdev_lock(wdev);
	err = rdev_change_bss(rdev, dev, &params);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_req_set_reg(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	अक्षर *data = शून्य;
	bool is_inकरोor;
	क्रमागत nl80211_user_reg_hपूर्णांक_type user_reg_hपूर्णांक_type;
	u32 owner_nlportid;

	/*
	 * You should only get this when cfg80211 hasn't yet initialized
	 * completely when built-in to the kernel right between the समय
	 * winकरोw between nl80211_init() and regulatory_init(), अगर that is
	 * even possible.
	 */
	अगर (unlikely(!rcu_access_poपूर्णांकer(cfg80211_regकरोमुख्य)))
		वापस -EINPROGRESS;

	अगर (info->attrs[NL80211_ATTR_USER_REG_HINT_TYPE])
		user_reg_hपूर्णांक_type =
		  nla_get_u32(info->attrs[NL80211_ATTR_USER_REG_HINT_TYPE]);
	अन्यथा
		user_reg_hपूर्णांक_type = NL80211_USER_REG_HINT_USER;

	चयन (user_reg_hपूर्णांक_type) अणु
	हाल NL80211_USER_REG_HINT_USER:
	हाल NL80211_USER_REG_HINT_CELL_BASE:
		अगर (!info->attrs[NL80211_ATTR_REG_ALPHA2])
			वापस -EINVAL;

		data = nla_data(info->attrs[NL80211_ATTR_REG_ALPHA2]);
		वापस regulatory_hपूर्णांक_user(data, user_reg_hपूर्णांक_type);
	हाल NL80211_USER_REG_HINT_INDOOR:
		अगर (info->attrs[NL80211_ATTR_SOCKET_OWNER]) अणु
			owner_nlportid = info->snd_portid;
			is_inकरोor = !!info->attrs[NL80211_ATTR_REG_INDOOR];
		पूर्ण अन्यथा अणु
			owner_nlportid = 0;
			is_inकरोor = true;
		पूर्ण

		वापस regulatory_hपूर्णांक_inकरोor(is_inकरोor, owner_nlportid);
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक nl80211_reload_regdb(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	वापस reg_reload_regdb();
पूर्ण

अटल पूर्णांक nl80211_get_mesh_config(काष्ठा sk_buff *skb,
				   काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा mesh_config cur_params;
	पूर्णांक err = 0;
	व्योम *hdr;
	काष्ठा nlattr *pinfoattr;
	काष्ठा sk_buff *msg;

	अगर (wdev->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->get_mesh_config)
		वापस -EOPNOTSUPP;

	wdev_lock(wdev);
	/* If not connected, get शेष parameters */
	अगर (!wdev->mesh_id_len)
		स_नकल(&cur_params, &शेष_mesh_config, माप(cur_params));
	अन्यथा
		err = rdev_get_mesh_config(rdev, dev, &cur_params);
	wdev_unlock(wdev);

	अगर (err)
		वापस err;

	/* Draw up a netlink message to send back */
	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;
	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_MESH_CONFIG);
	अगर (!hdr)
		जाओ out;
	pinfoattr = nla_nest_start_noflag(msg, NL80211_ATTR_MESH_CONFIG);
	अगर (!pinfoattr)
		जाओ nla_put_failure;
	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put_u16(msg, NL80211_MESHCONF_RETRY_TIMEOUT,
			cur_params.करोt11MeshRetryTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_CONFIRM_TIMEOUT,
			cur_params.करोt11MeshConfirmTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HOLDING_TIMEOUT,
			cur_params.करोt11MeshHoldingTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_MAX_PEER_LINKS,
			cur_params.करोt11MeshMaxPeerLinks) ||
	    nla_put_u8(msg, NL80211_MESHCONF_MAX_RETRIES,
		       cur_params.करोt11MeshMaxRetries) ||
	    nla_put_u8(msg, NL80211_MESHCONF_TTL,
		       cur_params.करोt11MeshTTL) ||
	    nla_put_u8(msg, NL80211_MESHCONF_ELEMENT_TTL,
		       cur_params.element_ttl) ||
	    nla_put_u8(msg, NL80211_MESHCONF_AUTO_OPEN_PLINKS,
		       cur_params.स्वतः_खोलो_plinks) ||
	    nla_put_u32(msg, NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR,
			cur_params.करोt11MeshNbrOffsetMaxNeighbor) ||
	    nla_put_u8(msg, NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES,
		       cur_params.करोt11MeshHWMPmaxPREQretries) ||
	    nla_put_u32(msg, NL80211_MESHCONF_PATH_REFRESH_TIME,
			cur_params.path_refresh_समय) ||
	    nla_put_u16(msg, NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT,
			cur_params.min_discovery_समयout) ||
	    nla_put_u32(msg, NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT,
			cur_params.करोt11MeshHWMPactivePathTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL,
			cur_params.करोt11MeshHWMPpreqMinInterval) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL,
			cur_params.करोt11MeshHWMPperrMinInterval) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME,
			cur_params.करोt11MeshHWMPnetDiameterTraversalTime) ||
	    nla_put_u8(msg, NL80211_MESHCONF_HWMP_ROOTMODE,
		       cur_params.करोt11MeshHWMPRootMode) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_RANN_INTERVAL,
			cur_params.करोt11MeshHWMPRannInterval) ||
	    nla_put_u8(msg, NL80211_MESHCONF_GATE_ANNOUNCEMENTS,
		       cur_params.करोt11MeshGateAnnouncementProtocol) ||
	    nla_put_u8(msg, NL80211_MESHCONF_FORWARDING,
		       cur_params.करोt11MeshForwarding) ||
	    nla_put_s32(msg, NL80211_MESHCONF_RSSI_THRESHOLD,
			cur_params.rssi_threshold) ||
	    nla_put_u32(msg, NL80211_MESHCONF_HT_OPMODE,
			cur_params.ht_opmode) ||
	    nla_put_u32(msg, NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT,
			cur_params.करोt11MeshHWMPactivePathToRootTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_ROOT_INTERVAL,
			cur_params.करोt11MeshHWMProotInterval) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL,
			cur_params.करोt11MeshHWMPconfirmationInterval) ||
	    nla_put_u32(msg, NL80211_MESHCONF_POWER_MODE,
			cur_params.घातer_mode) ||
	    nla_put_u16(msg, NL80211_MESHCONF_AWAKE_WINDOW,
			cur_params.करोt11MeshAwakeWinकरोwDuration) ||
	    nla_put_u32(msg, NL80211_MESHCONF_PLINK_TIMEOUT,
			cur_params.plink_समयout) ||
	    nla_put_u8(msg, NL80211_MESHCONF_CONNECTED_TO_GATE,
		       cur_params.करोt11MeshConnectedToMeshGate) ||
	    nla_put_u8(msg, NL80211_MESHCONF_NOLEARN,
		       cur_params.करोt11MeshNolearn) ||
	    nla_put_u8(msg, NL80211_MESHCONF_CONNECTED_TO_AS,
		       cur_params.करोt11MeshConnectedToAuthServer))
		जाओ nla_put_failure;
	nla_nest_end(msg, pinfoattr);
	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

 nla_put_failure:
 out:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण

अटल स्थिर काष्ठा nla_policy
nl80211_meshconf_params_policy[NL80211_MESHCONF_ATTR_MAX+1] = अणु
	[NL80211_MESHCONF_RETRY_TIMEOUT] =
		NLA_POLICY_RANGE(NLA_U16, 1, 255),
	[NL80211_MESHCONF_CONFIRM_TIMEOUT] =
		NLA_POLICY_RANGE(NLA_U16, 1, 255),
	[NL80211_MESHCONF_HOLDING_TIMEOUT] =
		NLA_POLICY_RANGE(NLA_U16, 1, 255),
	[NL80211_MESHCONF_MAX_PEER_LINKS] =
		NLA_POLICY_RANGE(NLA_U16, 0, 255),
	[NL80211_MESHCONF_MAX_RETRIES] = NLA_POLICY_MAX(NLA_U8, 16),
	[NL80211_MESHCONF_TTL] = NLA_POLICY_MIN(NLA_U8, 1),
	[NL80211_MESHCONF_ELEMENT_TTL] = NLA_POLICY_MIN(NLA_U8, 1),
	[NL80211_MESHCONF_AUTO_OPEN_PLINKS] = NLA_POLICY_MAX(NLA_U8, 1),
	[NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR] =
		NLA_POLICY_RANGE(NLA_U32, 1, 255),
	[NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_MESHCONF_PATH_REFRESH_TIME] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT] = NLA_POLICY_MIN(NLA_U16, 1),
	[NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL] =
		NLA_POLICY_MIN(NLA_U16, 1),
	[NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL] =
		NLA_POLICY_MIN(NLA_U16, 1),
	[NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME] =
		NLA_POLICY_MIN(NLA_U16, 1),
	[NL80211_MESHCONF_HWMP_ROOTMODE] = NLA_POLICY_MAX(NLA_U8, 4),
	[NL80211_MESHCONF_HWMP_RANN_INTERVAL] =
		NLA_POLICY_MIN(NLA_U16, 1),
	[NL80211_MESHCONF_GATE_ANNOUNCEMENTS] = NLA_POLICY_MAX(NLA_U8, 1),
	[NL80211_MESHCONF_FORWARDING] = NLA_POLICY_MAX(NLA_U8, 1),
	[NL80211_MESHCONF_RSSI_THRESHOLD] =
		NLA_POLICY_RANGE(NLA_S32, -255, 0),
	[NL80211_MESHCONF_HT_OPMODE] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_MESHCONF_HWMP_ROOT_INTERVAL] =
		NLA_POLICY_MIN(NLA_U16, 1),
	[NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL] =
		NLA_POLICY_MIN(NLA_U16, 1),
	[NL80211_MESHCONF_POWER_MODE] =
		NLA_POLICY_RANGE(NLA_U32,
				 NL80211_MESH_POWER_ACTIVE,
				 NL80211_MESH_POWER_MAX),
	[NL80211_MESHCONF_AWAKE_WINDOW] = अणु .type = NLA_U16 पूर्ण,
	[NL80211_MESHCONF_PLINK_TIMEOUT] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_MESHCONF_CONNECTED_TO_GATE] = NLA_POLICY_RANGE(NLA_U8, 0, 1),
	[NL80211_MESHCONF_NOLEARN] = NLA_POLICY_RANGE(NLA_U8, 0, 1),
	[NL80211_MESHCONF_CONNECTED_TO_AS] = NLA_POLICY_RANGE(NLA_U8, 0, 1),
पूर्ण;

अटल स्थिर काष्ठा nla_policy
	nl80211_mesh_setup_params_policy[NL80211_MESH_SETUP_ATTR_MAX+1] = अणु
	[NL80211_MESH_SETUP_ENABLE_VENDOR_SYNC] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_MESH_SETUP_ENABLE_VENDOR_PATH_SEL] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_MESH_SETUP_ENABLE_VENDOR_METRIC] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_MESH_SETUP_USERSPACE_AUTH] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_MESH_SETUP_AUTH_PROTOCOL] = अणु .type = NLA_U8 पूर्ण,
	[NL80211_MESH_SETUP_USERSPACE_MPM] = अणु .type = NLA_FLAG पूर्ण,
	[NL80211_MESH_SETUP_IE] =
		NLA_POLICY_VALIDATE_FN(NLA_BINARY, validate_ie_attr,
				       IEEE80211_MAX_DATA_LEN),
	[NL80211_MESH_SETUP_USERSPACE_AMPE] = अणु .type = NLA_FLAG पूर्ण,
पूर्ण;

अटल पूर्णांक nl80211_parse_mesh_config(काष्ठा genl_info *info,
				     काष्ठा mesh_config *cfg,
				     u32 *mask_out)
अणु
	काष्ठा nlattr *tb[NL80211_MESHCONF_ATTR_MAX + 1];
	u32 mask = 0;
	u16 ht_opmode;

#घोषणा FILL_IN_MESH_PARAM_IF_SET(tb, cfg, param, mask, attr, fn)	\
करो अणु									\
	अगर (tb[attr]) अणु							\
		cfg->param = fn(tb[attr]);				\
		mask |= BIT((attr) - 1);				\
	पूर्ण								\
पूर्ण जबतक (0)

	अगर (!info->attrs[NL80211_ATTR_MESH_CONFIG])
		वापस -EINVAL;
	अगर (nla_parse_nested_deprecated(tb, NL80211_MESHCONF_ATTR_MAX, info->attrs[NL80211_ATTR_MESH_CONFIG], nl80211_meshconf_params_policy, info->extack))
		वापस -EINVAL;

	/* This makes sure that there aren't more than 32 mesh config
	 * parameters (otherwise our bitfield scheme would not work.) */
	BUILD_BUG_ON(NL80211_MESHCONF_ATTR_MAX > 32);

	/* Fill in the params काष्ठा */
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshRetryTimeout, mask,
				  NL80211_MESHCONF_RETRY_TIMEOUT, nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshConfirmTimeout, mask,
				  NL80211_MESHCONF_CONFIRM_TIMEOUT,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHoldingTimeout, mask,
				  NL80211_MESHCONF_HOLDING_TIMEOUT,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshMaxPeerLinks, mask,
				  NL80211_MESHCONF_MAX_PEER_LINKS,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshMaxRetries, mask,
				  NL80211_MESHCONF_MAX_RETRIES, nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshTTL, mask,
				  NL80211_MESHCONF_TTL, nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, element_ttl, mask,
				  NL80211_MESHCONF_ELEMENT_TTL, nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, स्वतः_खोलो_plinks, mask,
				  NL80211_MESHCONF_AUTO_OPEN_PLINKS,
				  nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshNbrOffsetMaxNeighbor,
				  mask,
				  NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR,
				  nla_get_u32);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHWMPmaxPREQretries, mask,
				  NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES,
				  nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, path_refresh_समय, mask,
				  NL80211_MESHCONF_PATH_REFRESH_TIME,
				  nla_get_u32);
	अगर (mask & BIT(NL80211_MESHCONF_PATH_REFRESH_TIME) &&
	    (cfg->path_refresh_समय < 1 || cfg->path_refresh_समय > 65535))
		वापस -EINVAL;
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, min_discovery_समयout, mask,
				  NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHWMPactivePathTimeout,
				  mask,
				  NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT,
				  nla_get_u32);
	अगर (mask & BIT(NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT) &&
	    (cfg->करोt11MeshHWMPactivePathTimeout < 1 ||
	     cfg->करोt11MeshHWMPactivePathTimeout > 65535))
		वापस -EINVAL;
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHWMPpreqMinInterval, mask,
				  NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHWMPperrMinInterval, mask,
				  NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg,
				  करोt11MeshHWMPnetDiameterTraversalTime, mask,
				  NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHWMPRootMode, mask,
				  NL80211_MESHCONF_HWMP_ROOTMODE, nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHWMPRannInterval, mask,
				  NL80211_MESHCONF_HWMP_RANN_INTERVAL,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshGateAnnouncementProtocol,
				  mask, NL80211_MESHCONF_GATE_ANNOUNCEMENTS,
				  nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshForwarding, mask,
				  NL80211_MESHCONF_FORWARDING, nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, rssi_threshold, mask,
				  NL80211_MESHCONF_RSSI_THRESHOLD,
				  nla_get_s32);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshConnectedToMeshGate, mask,
				  NL80211_MESHCONF_CONNECTED_TO_GATE,
				  nla_get_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshConnectedToAuthServer, mask,
				  NL80211_MESHCONF_CONNECTED_TO_AS,
				  nla_get_u8);
	/*
	 * Check HT operation mode based on
	 * IEEE 802.11-2016 9.4.2.57 HT Operation element.
	 */
	अगर (tb[NL80211_MESHCONF_HT_OPMODE]) अणु
		ht_opmode = nla_get_u16(tb[NL80211_MESHCONF_HT_OPMODE]);

		अगर (ht_opmode & ~(IEEE80211_HT_OP_MODE_PROTECTION |
				  IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT |
				  IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT))
			वापस -EINVAL;

		/* NON_HT_STA bit is reserved, but some programs set it */
		ht_opmode &= ~IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT;

		cfg->ht_opmode = ht_opmode;
		mask |= (1 << (NL80211_MESHCONF_HT_OPMODE - 1));
	पूर्ण
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg,
				  करोt11MeshHWMPactivePathToRootTimeout, mask,
				  NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT,
				  nla_get_u32);
	अगर (mask & BIT(NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT) &&
	    (cfg->करोt11MeshHWMPactivePathToRootTimeout < 1 ||
	     cfg->करोt11MeshHWMPactivePathToRootTimeout > 65535))
		वापस -EINVAL;
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHWMProotInterval, mask,
				  NL80211_MESHCONF_HWMP_ROOT_INTERVAL,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshHWMPconfirmationInterval,
				  mask,
				  NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL,
				  nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, घातer_mode, mask,
				  NL80211_MESHCONF_POWER_MODE, nla_get_u32);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshAwakeWinकरोwDuration, mask,
				  NL80211_MESHCONF_AWAKE_WINDOW, nla_get_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, plink_समयout, mask,
				  NL80211_MESHCONF_PLINK_TIMEOUT, nla_get_u32);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, करोt11MeshNolearn, mask,
				  NL80211_MESHCONF_NOLEARN, nla_get_u8);
	अगर (mask_out)
		*mask_out = mask;

	वापस 0;

#अघोषित FILL_IN_MESH_PARAM_IF_SET
पूर्ण

अटल पूर्णांक nl80211_parse_mesh_setup(काष्ठा genl_info *info,
				     काष्ठा mesh_setup *setup)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा nlattr *tb[NL80211_MESH_SETUP_ATTR_MAX + 1];

	अगर (!info->attrs[NL80211_ATTR_MESH_SETUP])
		वापस -EINVAL;
	अगर (nla_parse_nested_deprecated(tb, NL80211_MESH_SETUP_ATTR_MAX, info->attrs[NL80211_ATTR_MESH_SETUP], nl80211_mesh_setup_params_policy, info->extack))
		वापस -EINVAL;

	अगर (tb[NL80211_MESH_SETUP_ENABLE_VENDOR_SYNC])
		setup->sync_method =
		(nla_get_u8(tb[NL80211_MESH_SETUP_ENABLE_VENDOR_SYNC])) ?
		 IEEE80211_SYNC_METHOD_VENDOR :
		 IEEE80211_SYNC_METHOD_NEIGHBOR_OFFSET;

	अगर (tb[NL80211_MESH_SETUP_ENABLE_VENDOR_PATH_SEL])
		setup->path_sel_proto =
		(nla_get_u8(tb[NL80211_MESH_SETUP_ENABLE_VENDOR_PATH_SEL])) ?
		 IEEE80211_PATH_PROTOCOL_VENDOR :
		 IEEE80211_PATH_PROTOCOL_HWMP;

	अगर (tb[NL80211_MESH_SETUP_ENABLE_VENDOR_METRIC])
		setup->path_metric =
		(nla_get_u8(tb[NL80211_MESH_SETUP_ENABLE_VENDOR_METRIC])) ?
		 IEEE80211_PATH_METRIC_VENDOR :
		 IEEE80211_PATH_METRIC_AIRTIME;

	अगर (tb[NL80211_MESH_SETUP_IE]) अणु
		काष्ठा nlattr *ieattr =
			tb[NL80211_MESH_SETUP_IE];
		setup->ie = nla_data(ieattr);
		setup->ie_len = nla_len(ieattr);
	पूर्ण
	अगर (tb[NL80211_MESH_SETUP_USERSPACE_MPM] &&
	    !(rdev->wiphy.features & NL80211_FEATURE_USERSPACE_MPM))
		वापस -EINVAL;
	setup->user_mpm = nla_get_flag(tb[NL80211_MESH_SETUP_USERSPACE_MPM]);
	setup->is_authenticated = nla_get_flag(tb[NL80211_MESH_SETUP_USERSPACE_AUTH]);
	setup->is_secure = nla_get_flag(tb[NL80211_MESH_SETUP_USERSPACE_AMPE]);
	अगर (setup->is_secure)
		setup->user_mpm = true;

	अगर (tb[NL80211_MESH_SETUP_AUTH_PROTOCOL]) अणु
		अगर (!setup->user_mpm)
			वापस -EINVAL;
		setup->auth_id =
			nla_get_u8(tb[NL80211_MESH_SETUP_AUTH_PROTOCOL]);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_update_mesh_config(काष्ठा sk_buff *skb,
				      काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा mesh_config cfg;
	u32 mask;
	पूर्णांक err;

	अगर (wdev->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->update_mesh_config)
		वापस -EOPNOTSUPP;

	err = nl80211_parse_mesh_config(info, &cfg, &mask);
	अगर (err)
		वापस err;

	wdev_lock(wdev);
	अगर (!wdev->mesh_id_len)
		err = -ENOLINK;

	अगर (!err)
		err = rdev_update_mesh_config(rdev, dev, mask, &cfg);

	wdev_unlock(wdev);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_put_regकरोm(स्थिर काष्ठा ieee80211_regकरोमुख्य *regकरोm,
			      काष्ठा sk_buff *msg)
अणु
	काष्ठा nlattr *nl_reg_rules;
	अचिन्हित पूर्णांक i;

	अगर (nla_put_string(msg, NL80211_ATTR_REG_ALPHA2, regकरोm->alpha2) ||
	    (regकरोm->dfs_region &&
	     nla_put_u8(msg, NL80211_ATTR_DFS_REGION, regकरोm->dfs_region)))
		जाओ nla_put_failure;

	nl_reg_rules = nla_nest_start_noflag(msg, NL80211_ATTR_REG_RULES);
	अगर (!nl_reg_rules)
		जाओ nla_put_failure;

	क्रम (i = 0; i < regकरोm->n_reg_rules; i++) अणु
		काष्ठा nlattr *nl_reg_rule;
		स्थिर काष्ठा ieee80211_reg_rule *reg_rule;
		स्थिर काष्ठा ieee80211_freq_range *freq_range;
		स्थिर काष्ठा ieee80211_घातer_rule *घातer_rule;
		अचिन्हित पूर्णांक max_bandwidth_khz;

		reg_rule = &regकरोm->reg_rules[i];
		freq_range = &reg_rule->freq_range;
		घातer_rule = &reg_rule->घातer_rule;

		nl_reg_rule = nla_nest_start_noflag(msg, i);
		अगर (!nl_reg_rule)
			जाओ nla_put_failure;

		max_bandwidth_khz = freq_range->max_bandwidth_khz;
		अगर (!max_bandwidth_khz)
			max_bandwidth_khz = reg_get_max_bandwidth(regकरोm,
								  reg_rule);

		अगर (nla_put_u32(msg, NL80211_ATTR_REG_RULE_FLAGS,
				reg_rule->flags) ||
		    nla_put_u32(msg, NL80211_ATTR_FREQ_RANGE_START,
				freq_range->start_freq_khz) ||
		    nla_put_u32(msg, NL80211_ATTR_FREQ_RANGE_END,
				freq_range->end_freq_khz) ||
		    nla_put_u32(msg, NL80211_ATTR_FREQ_RANGE_MAX_BW,
				max_bandwidth_khz) ||
		    nla_put_u32(msg, NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN,
				घातer_rule->max_antenna_gain) ||
		    nla_put_u32(msg, NL80211_ATTR_POWER_RULE_MAX_EIRP,
				घातer_rule->max_eirp) ||
		    nla_put_u32(msg, NL80211_ATTR_DFS_CAC_TIME,
				reg_rule->dfs_cac_ms))
			जाओ nla_put_failure;

		nla_nest_end(msg, nl_reg_rule);
	पूर्ण

	nla_nest_end(msg, nl_reg_rules);
	वापस 0;

nla_put_failure:
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_get_reg_करो(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regकरोm = शून्य;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wiphy *wiphy = शून्य;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOBUFS;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_REG);
	अगर (!hdr)
		जाओ put_failure;

	rtnl_lock();

	अगर (info->attrs[NL80211_ATTR_WIPHY]) अणु
		bool self_managed;

		rdev = cfg80211_get_dev_from_info(genl_info_net(info), info);
		अगर (IS_ERR(rdev)) अणु
			nlmsg_मुक्त(msg);
			rtnl_unlock();
			वापस PTR_ERR(rdev);
		पूर्ण

		wiphy = &rdev->wiphy;
		self_managed = wiphy->regulatory_flags &
			       REGULATORY_WIPHY_SELF_MANAGED;
		regकरोm = get_wiphy_regकरोm(wiphy);

		/* a self-managed-reg device must have a निजी regकरोm */
		अगर (WARN_ON(!regकरोm && self_managed)) अणु
			nlmsg_मुक्त(msg);
			rtnl_unlock();
			वापस -EINVAL;
		पूर्ण

		अगर (regकरोm &&
		    nla_put_u32(msg, NL80211_ATTR_WIPHY, get_wiphy_idx(wiphy)))
			जाओ nla_put_failure;
	पूर्ण

	अगर (!wiphy && reg_last_request_cell_base() &&
	    nla_put_u32(msg, NL80211_ATTR_USER_REG_HINT_TYPE,
			NL80211_USER_REG_HINT_CELL_BASE))
		जाओ nla_put_failure;

	rcu_पढ़ो_lock();

	अगर (!regकरोm)
		regकरोm = rcu_dereference(cfg80211_regकरोमुख्य);

	अगर (nl80211_put_regकरोm(regकरोm, msg))
		जाओ nla_put_failure_rcu;

	rcu_पढ़ो_unlock();

	genlmsg_end(msg, hdr);
	rtnl_unlock();
	वापस genlmsg_reply(msg, info);

nla_put_failure_rcu:
	rcu_पढ़ो_unlock();
nla_put_failure:
	rtnl_unlock();
put_failure:
	nlmsg_मुक्त(msg);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_send_regकरोm(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
			       u32 seq, पूर्णांक flags, काष्ठा wiphy *wiphy,
			       स्थिर काष्ठा ieee80211_regकरोमुख्य *regकरोm)
अणु
	व्योम *hdr = nl80211hdr_put(msg, NETLINK_CB(cb->skb).portid, seq, flags,
				   NL80211_CMD_GET_REG);

	अगर (!hdr)
		वापस -1;

	genl_dump_check_consistent(cb, hdr);

	अगर (nl80211_put_regकरोm(regकरोm, msg))
		जाओ nla_put_failure;

	अगर (!wiphy && reg_last_request_cell_base() &&
	    nla_put_u32(msg, NL80211_ATTR_USER_REG_HINT_TYPE,
			NL80211_USER_REG_HINT_CELL_BASE))
		जाओ nla_put_failure;

	अगर (wiphy &&
	    nla_put_u32(msg, NL80211_ATTR_WIPHY, get_wiphy_idx(wiphy)))
		जाओ nla_put_failure;

	अगर (wiphy && wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED &&
	    nla_put_flag(msg, NL80211_ATTR_WIPHY_SELF_MANAGED_REG))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_get_reg_dump(काष्ठा sk_buff *skb,
				काष्ठा netlink_callback *cb)
अणु
	स्थिर काष्ठा ieee80211_regकरोमुख्य *regकरोm = शून्य;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	पूर्णांक err, reg_idx, start = cb->args[2];

	rtnl_lock();

	अगर (cfg80211_regकरोमुख्य && start == 0) अणु
		err = nl80211_send_regकरोm(skb, cb, cb->nlh->nlmsg_seq,
					  NLM_F_MULTI, शून्य,
					  rtnl_dereference(cfg80211_regकरोमुख्य));
		अगर (err < 0)
			जाओ out_err;
	पूर्ण

	/* the global regकरोm is idx 0 */
	reg_idx = 1;
	list_क्रम_each_entry(rdev, &cfg80211_rdev_list, list) अणु
		regकरोm = get_wiphy_regकरोm(&rdev->wiphy);
		अगर (!regकरोm)
			जारी;

		अगर (++reg_idx <= start)
			जारी;

		err = nl80211_send_regकरोm(skb, cb, cb->nlh->nlmsg_seq,
					  NLM_F_MULTI, &rdev->wiphy, regकरोm);
		अगर (err < 0) अणु
			reg_idx--;
			अवरोध;
		पूर्ण
	पूर्ण

	cb->args[2] = reg_idx;
	err = skb->len;
out_err:
	rtnl_unlock();
	वापस err;
पूर्ण

#अगर_घोषित CONFIG_CFG80211_CRDA_SUPPORT
अटल स्थिर काष्ठा nla_policy reg_rule_policy[NL80211_REG_RULE_ATTR_MAX + 1] = अणु
	[NL80211_ATTR_REG_RULE_FLAGS]		= अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_FREQ_RANGE_START]		= अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_FREQ_RANGE_END]		= अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_FREQ_RANGE_MAX_BW]	= अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN]	= अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_POWER_RULE_MAX_EIRP]	= अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_DFS_CAC_TIME]		= अणु .type = NLA_U32 पूर्ण,
पूर्ण;

अटल पूर्णांक parse_reg_rule(काष्ठा nlattr *tb[],
	काष्ठा ieee80211_reg_rule *reg_rule)
अणु
	काष्ठा ieee80211_freq_range *freq_range = &reg_rule->freq_range;
	काष्ठा ieee80211_घातer_rule *घातer_rule = &reg_rule->घातer_rule;

	अगर (!tb[NL80211_ATTR_REG_RULE_FLAGS])
		वापस -EINVAL;
	अगर (!tb[NL80211_ATTR_FREQ_RANGE_START])
		वापस -EINVAL;
	अगर (!tb[NL80211_ATTR_FREQ_RANGE_END])
		वापस -EINVAL;
	अगर (!tb[NL80211_ATTR_FREQ_RANGE_MAX_BW])
		वापस -EINVAL;
	अगर (!tb[NL80211_ATTR_POWER_RULE_MAX_EIRP])
		वापस -EINVAL;

	reg_rule->flags = nla_get_u32(tb[NL80211_ATTR_REG_RULE_FLAGS]);

	freq_range->start_freq_khz =
		nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_START]);
	freq_range->end_freq_khz =
		nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_END]);
	freq_range->max_bandwidth_khz =
		nla_get_u32(tb[NL80211_ATTR_FREQ_RANGE_MAX_BW]);

	घातer_rule->max_eirp =
		nla_get_u32(tb[NL80211_ATTR_POWER_RULE_MAX_EIRP]);

	अगर (tb[NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN])
		घातer_rule->max_antenna_gain =
			nla_get_u32(tb[NL80211_ATTR_POWER_RULE_MAX_ANT_GAIN]);

	अगर (tb[NL80211_ATTR_DFS_CAC_TIME])
		reg_rule->dfs_cac_ms =
			nla_get_u32(tb[NL80211_ATTR_DFS_CAC_TIME]);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_set_reg(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *tb[NL80211_REG_RULE_ATTR_MAX + 1];
	काष्ठा nlattr *nl_reg_rule;
	अक्षर *alpha2;
	पूर्णांक rem_reg_rules, r;
	u32 num_rules = 0, rule_idx = 0;
	क्रमागत nl80211_dfs_regions dfs_region = NL80211_DFS_UNSET;
	काष्ठा ieee80211_regकरोमुख्य *rd;

	अगर (!info->attrs[NL80211_ATTR_REG_ALPHA2])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_REG_RULES])
		वापस -EINVAL;

	alpha2 = nla_data(info->attrs[NL80211_ATTR_REG_ALPHA2]);

	अगर (info->attrs[NL80211_ATTR_DFS_REGION])
		dfs_region = nla_get_u8(info->attrs[NL80211_ATTR_DFS_REGION]);

	nla_क्रम_each_nested(nl_reg_rule, info->attrs[NL80211_ATTR_REG_RULES],
			    rem_reg_rules) अणु
		num_rules++;
		अगर (num_rules > NL80211_MAX_SUPP_REG_RULES)
			वापस -EINVAL;
	पूर्ण

	rtnl_lock();
	अगर (!reg_is_valid_request(alpha2)) अणु
		r = -EINVAL;
		जाओ out;
	पूर्ण

	rd = kzalloc(काष्ठा_size(rd, reg_rules, num_rules), GFP_KERNEL);
	अगर (!rd) अणु
		r = -ENOMEM;
		जाओ out;
	पूर्ण

	rd->n_reg_rules = num_rules;
	rd->alpha2[0] = alpha2[0];
	rd->alpha2[1] = alpha2[1];

	/*
	 * Disable DFS master mode अगर the DFS region was
	 * not supported or known on this kernel.
	 */
	अगर (reg_supported_dfs_region(dfs_region))
		rd->dfs_region = dfs_region;

	nla_क्रम_each_nested(nl_reg_rule, info->attrs[NL80211_ATTR_REG_RULES],
			    rem_reg_rules) अणु
		r = nla_parse_nested_deprecated(tb, NL80211_REG_RULE_ATTR_MAX,
						nl_reg_rule, reg_rule_policy,
						info->extack);
		अगर (r)
			जाओ bad_reg;
		r = parse_reg_rule(tb, &rd->reg_rules[rule_idx]);
		अगर (r)
			जाओ bad_reg;

		rule_idx++;

		अगर (rule_idx > NL80211_MAX_SUPP_REG_RULES) अणु
			r = -EINVAL;
			जाओ bad_reg;
		पूर्ण
	पूर्ण

	r = set_regकरोm(rd, REGD_SOURCE_CRDA);
	/* set_regकरोm takes ownership of rd */
	rd = शून्य;
 bad_reg:
	kमुक्त(rd);
 out:
	rtnl_unlock();
	वापस r;
पूर्ण
#पूर्ण_अगर /* CONFIG_CFG80211_CRDA_SUPPORT */

अटल पूर्णांक validate_scan_freqs(काष्ठा nlattr *freqs)
अणु
	काष्ठा nlattr *attr1, *attr2;
	पूर्णांक n_channels = 0, पंचांगp1, पंचांगp2;

	nla_क्रम_each_nested(attr1, freqs, पंचांगp1)
		अगर (nla_len(attr1) != माप(u32))
			वापस 0;

	nla_क्रम_each_nested(attr1, freqs, पंचांगp1) अणु
		n_channels++;
		/*
		 * Some hardware has a limited channel list क्रम
		 * scanning, and it is pretty much nonsensical
		 * to scan क्रम a channel twice, so disallow that
		 * and करोn't require drivers to check that the
		 * channel list they get isn't दीर्घer than what
		 * they can scan, as दीर्घ as they can scan all
		 * the channels they रेजिस्टरed at once.
		 */
		nla_क्रम_each_nested(attr2, freqs, पंचांगp2)
			अगर (attr1 != attr2 &&
			    nla_get_u32(attr1) == nla_get_u32(attr2))
				वापस 0;
	पूर्ण

	वापस n_channels;
पूर्ण

अटल bool is_band_valid(काष्ठा wiphy *wiphy, क्रमागत nl80211_band b)
अणु
	वापस b < NUM_NL80211_BANDS && wiphy->bands[b];
पूर्ण

अटल पूर्णांक parse_bss_select(काष्ठा nlattr *nla, काष्ठा wiphy *wiphy,
			    काष्ठा cfg80211_bss_selection *bss_select)
अणु
	काष्ठा nlattr *attr[NL80211_BSS_SELECT_ATTR_MAX + 1];
	काष्ठा nlattr *nest;
	पूर्णांक err;
	bool found = false;
	पूर्णांक i;

	/* only process one nested attribute */
	nest = nla_data(nla);
	अगर (!nla_ok(nest, nla_len(nest)))
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attr, NL80211_BSS_SELECT_ATTR_MAX,
					  nest, nl80211_bss_select_policy,
					  शून्य);
	अगर (err)
		वापस err;

	/* only one attribute may be given */
	क्रम (i = 0; i <= NL80211_BSS_SELECT_ATTR_MAX; i++) अणु
		अगर (attr[i]) अणु
			अगर (found)
				वापस -EINVAL;
			found = true;
		पूर्ण
	पूर्ण

	bss_select->behaviour = __NL80211_BSS_SELECT_ATTR_INVALID;

	अगर (attr[NL80211_BSS_SELECT_ATTR_RSSI])
		bss_select->behaviour = NL80211_BSS_SELECT_ATTR_RSSI;

	अगर (attr[NL80211_BSS_SELECT_ATTR_BAND_PREF]) अणु
		bss_select->behaviour = NL80211_BSS_SELECT_ATTR_BAND_PREF;
		bss_select->param.band_pref =
			nla_get_u32(attr[NL80211_BSS_SELECT_ATTR_BAND_PREF]);
		अगर (!is_band_valid(wiphy, bss_select->param.band_pref))
			वापस -EINVAL;
	पूर्ण

	अगर (attr[NL80211_BSS_SELECT_ATTR_RSSI_ADJUST]) अणु
		काष्ठा nl80211_bss_select_rssi_adjust *adj_param;

		adj_param = nla_data(attr[NL80211_BSS_SELECT_ATTR_RSSI_ADJUST]);
		bss_select->behaviour = NL80211_BSS_SELECT_ATTR_RSSI_ADJUST;
		bss_select->param.adjust.band = adj_param->band;
		bss_select->param.adjust.delta = adj_param->delta;
		अगर (!is_band_valid(wiphy, bss_select->param.adjust.band))
			वापस -EINVAL;
	पूर्ण

	/* user-space did not provide behaviour attribute */
	अगर (bss_select->behaviour == __NL80211_BSS_SELECT_ATTR_INVALID)
		वापस -EINVAL;

	अगर (!(wiphy->bss_select_support & BIT(bss_select->behaviour)))
		वापस -EINVAL;

	वापस 0;
पूर्ण

पूर्णांक nl80211_parse_अक्रमom_mac(काष्ठा nlattr **attrs,
			     u8 *mac_addr, u8 *mac_addr_mask)
अणु
	पूर्णांक i;

	अगर (!attrs[NL80211_ATTR_MAC] && !attrs[NL80211_ATTR_MAC_MASK]) अणु
		eth_zero_addr(mac_addr);
		eth_zero_addr(mac_addr_mask);
		mac_addr[0] = 0x2;
		mac_addr_mask[0] = 0x3;

		वापस 0;
	पूर्ण

	/* need both or none */
	अगर (!attrs[NL80211_ATTR_MAC] || !attrs[NL80211_ATTR_MAC_MASK])
		वापस -EINVAL;

	स_नकल(mac_addr, nla_data(attrs[NL80211_ATTR_MAC]), ETH_ALEN);
	स_नकल(mac_addr_mask, nla_data(attrs[NL80211_ATTR_MAC_MASK]), ETH_ALEN);

	/* करोn't allow or configure an mcast address */
	अगर (!is_multicast_ether_addr(mac_addr_mask) ||
	    is_multicast_ether_addr(mac_addr))
		वापस -EINVAL;

	/*
	 * allow users to pass a MAC address that has bits set outside
	 * of the mask, but करोn't bother drivers with having to deal
	 * with such bits
	 */
	क्रम (i = 0; i < ETH_ALEN; i++)
		mac_addr[i] &= mac_addr_mask[i];

	वापस 0;
पूर्ण

अटल bool cfg80211_off_channel_oper_allowed(काष्ठा wireless_dev *wdev)
अणु
	ASSERT_WDEV_LOCK(wdev);

	अगर (!cfg80211_beaconing_अगरace_active(wdev))
		वापस true;

	अगर (!(wdev->chandef.chan->flags & IEEE80211_CHAN_RADAR))
		वापस true;

	वापस regulatory_pre_cac_allowed(wdev->wiphy);
पूर्ण

अटल bool nl80211_check_scan_feat(काष्ठा wiphy *wiphy, u32 flags, u32 flag,
				    क्रमागत nl80211_ext_feature_index feat)
अणु
	अगर (!(flags & flag))
		वापस true;
	अगर (wiphy_ext_feature_isset(wiphy, feat))
		वापस true;
	वापस false;
पूर्ण

अटल पूर्णांक
nl80211_check_scan_flags(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			 व्योम *request, काष्ठा nlattr **attrs,
			 bool is_sched_scan)
अणु
	u8 *mac_addr, *mac_addr_mask;
	u32 *flags;
	क्रमागत nl80211_feature_flags अक्रमomness_flag;

	अगर (!attrs[NL80211_ATTR_SCAN_FLAGS])
		वापस 0;

	अगर (is_sched_scan) अणु
		काष्ठा cfg80211_sched_scan_request *req = request;

		अक्रमomness_flag = wdev ?
				  NL80211_FEATURE_SCHED_SCAN_RANDOM_MAC_ADDR :
				  NL80211_FEATURE_ND_RANDOM_MAC_ADDR;
		flags = &req->flags;
		mac_addr = req->mac_addr;
		mac_addr_mask = req->mac_addr_mask;
	पूर्ण अन्यथा अणु
		काष्ठा cfg80211_scan_request *req = request;

		अक्रमomness_flag = NL80211_FEATURE_SCAN_RANDOM_MAC_ADDR;
		flags = &req->flags;
		mac_addr = req->mac_addr;
		mac_addr_mask = req->mac_addr_mask;
	पूर्ण

	*flags = nla_get_u32(attrs[NL80211_ATTR_SCAN_FLAGS]);

	अगर (((*flags & NL80211_SCAN_FLAG_LOW_PRIORITY) &&
	     !(wiphy->features & NL80211_FEATURE_LOW_PRIORITY_SCAN)) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_LOW_SPAN,
				     NL80211_EXT_FEATURE_LOW_SPAN_SCAN) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_LOW_POWER,
				     NL80211_EXT_FEATURE_LOW_POWER_SCAN) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_HIGH_ACCURACY,
				     NL80211_EXT_FEATURE_HIGH_ACCURACY_SCAN) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_FILS_MAX_CHANNEL_TIME,
				     NL80211_EXT_FEATURE_FILS_MAX_CHANNEL_TIME) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_ACCEPT_BCAST_PROBE_RESP,
				     NL80211_EXT_FEATURE_ACCEPT_BCAST_PROBE_RESP) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION,
				     NL80211_EXT_FEATURE_OCE_PROBE_REQ_DEFERRAL_SUPPRESSION) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_OCE_PROBE_REQ_HIGH_TX_RATE,
				     NL80211_EXT_FEATURE_OCE_PROBE_REQ_HIGH_TX_RATE) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_RANDOM_SN,
				     NL80211_EXT_FEATURE_SCAN_RANDOM_SN) ||
	    !nl80211_check_scan_feat(wiphy, *flags,
				     NL80211_SCAN_FLAG_MIN_PREQ_CONTENT,
				     NL80211_EXT_FEATURE_SCAN_MIN_PREQ_CONTENT))
		वापस -EOPNOTSUPP;

	अगर (*flags & NL80211_SCAN_FLAG_RANDOM_ADDR) अणु
		पूर्णांक err;

		अगर (!(wiphy->features & अक्रमomness_flag) ||
		    (wdev && wdev->current_bss))
			वापस -EOPNOTSUPP;

		err = nl80211_parse_अक्रमom_mac(attrs, mac_addr, mac_addr_mask);
		अगर (err)
			वापस err;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_trigger_scan(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	काष्ठा cfg80211_scan_request *request;
	काष्ठा nlattr *scan_freqs = शून्य;
	bool scan_freqs_khz = false;
	काष्ठा nlattr *attr;
	काष्ठा wiphy *wiphy;
	पूर्णांक err, पंचांगp, n_ssids = 0, n_channels, i;
	माप_प्रकार ie_len;

	wiphy = &rdev->wiphy;

	अगर (wdev->अगरtype == NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->scan)
		वापस -EOPNOTSUPP;

	अगर (rdev->scan_req || rdev->scan_msg)
		वापस -EBUSY;

	अगर (info->attrs[NL80211_ATTR_SCAN_FREQ_KHZ]) अणु
		अगर (!wiphy_ext_feature_isset(wiphy,
					     NL80211_EXT_FEATURE_SCAN_FREQ_KHZ))
			वापस -EOPNOTSUPP;
		scan_freqs = info->attrs[NL80211_ATTR_SCAN_FREQ_KHZ];
		scan_freqs_khz = true;
	पूर्ण अन्यथा अगर (info->attrs[NL80211_ATTR_SCAN_FREQUENCIES])
		scan_freqs = info->attrs[NL80211_ATTR_SCAN_FREQUENCIES];

	अगर (scan_freqs) अणु
		n_channels = validate_scan_freqs(scan_freqs);
		अगर (!n_channels)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		n_channels = ieee80211_get_num_supported_channels(wiphy);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_SCAN_SSIDS])
		nla_क्रम_each_nested(attr, info->attrs[NL80211_ATTR_SCAN_SSIDS], पंचांगp)
			n_ssids++;

	अगर (n_ssids > wiphy->max_scan_ssids)
		वापस -EINVAL;

	अगर (info->attrs[NL80211_ATTR_IE])
		ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	अन्यथा
		ie_len = 0;

	अगर (ie_len > wiphy->max_scan_ie_len)
		वापस -EINVAL;

	request = kzalloc(माप(*request)
			+ माप(*request->ssids) * n_ssids
			+ माप(*request->channels) * n_channels
			+ ie_len, GFP_KERNEL);
	अगर (!request)
		वापस -ENOMEM;

	अगर (n_ssids)
		request->ssids = (व्योम *)&request->channels[n_channels];
	request->n_ssids = n_ssids;
	अगर (ie_len) अणु
		अगर (n_ssids)
			request->ie = (व्योम *)(request->ssids + n_ssids);
		अन्यथा
			request->ie = (व्योम *)(request->channels + n_channels);
	पूर्ण

	i = 0;
	अगर (scan_freqs) अणु
		/* user specअगरied, bail out अगर channel not found */
		nla_क्रम_each_nested(attr, scan_freqs, पंचांगp) अणु
			काष्ठा ieee80211_channel *chan;
			पूर्णांक freq = nla_get_u32(attr);

			अगर (!scan_freqs_khz)
				freq = MHZ_TO_KHZ(freq);

			chan = ieee80211_get_channel_khz(wiphy, freq);
			अगर (!chan) अणु
				err = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण

			/* ignore disabled channels */
			अगर (chan->flags & IEEE80211_CHAN_DISABLED)
				जारी;

			request->channels[i] = chan;
			i++;
		पूर्ण
	पूर्ण अन्यथा अणु
		क्रमागत nl80211_band band;

		/* all channels */
		क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
			पूर्णांक j;

			अगर (!wiphy->bands[band])
				जारी;
			क्रम (j = 0; j < wiphy->bands[band]->n_channels; j++) अणु
				काष्ठा ieee80211_channel *chan;

				chan = &wiphy->bands[band]->channels[j];

				अगर (chan->flags & IEEE80211_CHAN_DISABLED)
					जारी;

				request->channels[i] = chan;
				i++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!i) अणु
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	request->n_channels = i;

	wdev_lock(wdev);
	अगर (!cfg80211_off_channel_oper_allowed(wdev)) अणु
		काष्ठा ieee80211_channel *chan;

		अगर (request->n_channels != 1) अणु
			wdev_unlock(wdev);
			err = -EBUSY;
			जाओ out_मुक्त;
		पूर्ण

		chan = request->channels[0];
		अगर (chan->center_freq != wdev->chandef.chan->center_freq) अणु
			wdev_unlock(wdev);
			err = -EBUSY;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण
	wdev_unlock(wdev);

	i = 0;
	अगर (n_ssids) अणु
		nla_क्रम_each_nested(attr, info->attrs[NL80211_ATTR_SCAN_SSIDS], पंचांगp) अणु
			अगर (nla_len(attr) > IEEE80211_MAX_SSID_LEN) अणु
				err = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
			request->ssids[i].ssid_len = nla_len(attr);
			स_नकल(request->ssids[i].ssid, nla_data(attr), nla_len(attr));
			i++;
		पूर्ण
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		request->ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
		स_नकल((व्योम *)request->ie,
		       nla_data(info->attrs[NL80211_ATTR_IE]),
		       request->ie_len);
	पूर्ण

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++)
		अगर (wiphy->bands[i])
			request->rates[i] =
				(1 << wiphy->bands[i]->n_bitrates) - 1;

	अगर (info->attrs[NL80211_ATTR_SCAN_SUPP_RATES]) अणु
		nla_क्रम_each_nested(attr,
				    info->attrs[NL80211_ATTR_SCAN_SUPP_RATES],
				    पंचांगp) अणु
			क्रमागत nl80211_band band = nla_type(attr);

			अगर (band < 0 || band >= NUM_NL80211_BANDS) अणु
				err = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण

			अगर (!wiphy->bands[band])
				जारी;

			err = ieee80211_get_ratemask(wiphy->bands[band],
						     nla_data(attr),
						     nla_len(attr),
						     &request->rates[band]);
			अगर (err)
				जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_MEASUREMENT_DURATION]) अणु
		request->duration =
			nla_get_u16(info->attrs[NL80211_ATTR_MEASUREMENT_DURATION]);
		request->duration_mandatory =
			nla_get_flag(info->attrs[NL80211_ATTR_MEASUREMENT_DURATION_MANDATORY]);
	पूर्ण

	err = nl80211_check_scan_flags(wiphy, wdev, request, info->attrs,
				       false);
	अगर (err)
		जाओ out_मुक्त;

	request->no_cck =
		nla_get_flag(info->attrs[NL80211_ATTR_TX_NO_CCK_RATE]);

	/* Initial implementation used NL80211_ATTR_MAC to set the specअगरic
	 * BSSID to scan क्रम. This was problematic because that same attribute
	 * was alपढ़ोy used क्रम another purpose (local अक्रमom MAC address). The
	 * NL80211_ATTR_BSSID attribute was added to fix this. For backwards
	 * compatibility with older userspace components, also use the
	 * NL80211_ATTR_MAC value here अगर it can be determined to be used क्रम
	 * the specअगरic BSSID use हाल instead of the अक्रमom MAC address
	 * (NL80211_ATTR_SCAN_FLAGS is used to enable अक्रमom MAC address use).
	 */
	अगर (info->attrs[NL80211_ATTR_BSSID])
		स_नकल(request->bssid,
		       nla_data(info->attrs[NL80211_ATTR_BSSID]), ETH_ALEN);
	अन्यथा अगर (!(request->flags & NL80211_SCAN_FLAG_RANDOM_ADDR) &&
		 info->attrs[NL80211_ATTR_MAC])
		स_नकल(request->bssid, nla_data(info->attrs[NL80211_ATTR_MAC]),
		       ETH_ALEN);
	अन्यथा
		eth_broadcast_addr(request->bssid);

	request->wdev = wdev;
	request->wiphy = &rdev->wiphy;
	request->scan_start = jअगरfies;

	rdev->scan_req = request;
	err = cfg80211_scan(rdev);

	अगर (err)
		जाओ out_मुक्त;

	nl80211_send_scan_start(rdev, wdev);
	अगर (wdev->netdev)
		dev_hold(wdev->netdev);

	वापस 0;

 out_मुक्त:
	rdev->scan_req = शून्य;
	kमुक्त(request);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_पात_scan(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];

	अगर (!rdev->ops->पात_scan)
		वापस -EOPNOTSUPP;

	अगर (rdev->scan_msg)
		वापस 0;

	अगर (!rdev->scan_req)
		वापस -ENOENT;

	rdev_पात_scan(rdev, wdev);
	वापस 0;
पूर्ण

अटल पूर्णांक
nl80211_parse_sched_scan_plans(काष्ठा wiphy *wiphy, पूर्णांक n_plans,
			       काष्ठा cfg80211_sched_scan_request *request,
			       काष्ठा nlattr **attrs)
अणु
	पूर्णांक पंचांगp, err, i = 0;
	काष्ठा nlattr *attr;

	अगर (!attrs[NL80211_ATTR_SCHED_SCAN_PLANS]) अणु
		u32 पूर्णांकerval;

		/*
		 * If scan plans are not specअगरied,
		 * %NL80211_ATTR_SCHED_SCAN_INTERVAL will be specअगरied. In this
		 * हाल one scan plan will be set with the specअगरied scan
		 * पूर्णांकerval and infinite number of iterations.
		 */
		पूर्णांकerval = nla_get_u32(attrs[NL80211_ATTR_SCHED_SCAN_INTERVAL]);
		अगर (!पूर्णांकerval)
			वापस -EINVAL;

		request->scan_plans[0].पूर्णांकerval =
			DIV_ROUND_UP(पूर्णांकerval, MSEC_PER_SEC);
		अगर (!request->scan_plans[0].पूर्णांकerval)
			वापस -EINVAL;

		अगर (request->scan_plans[0].पूर्णांकerval >
		    wiphy->max_sched_scan_plan_पूर्णांकerval)
			request->scan_plans[0].पूर्णांकerval =
				wiphy->max_sched_scan_plan_पूर्णांकerval;

		वापस 0;
	पूर्ण

	nla_क्रम_each_nested(attr, attrs[NL80211_ATTR_SCHED_SCAN_PLANS], पंचांगp) अणु
		काष्ठा nlattr *plan[NL80211_SCHED_SCAN_PLAN_MAX + 1];

		अगर (WARN_ON(i >= n_plans))
			वापस -EINVAL;

		err = nla_parse_nested_deprecated(plan,
						  NL80211_SCHED_SCAN_PLAN_MAX,
						  attr, nl80211_plan_policy,
						  शून्य);
		अगर (err)
			वापस err;

		अगर (!plan[NL80211_SCHED_SCAN_PLAN_INTERVAL])
			वापस -EINVAL;

		request->scan_plans[i].पूर्णांकerval =
			nla_get_u32(plan[NL80211_SCHED_SCAN_PLAN_INTERVAL]);
		अगर (!request->scan_plans[i].पूर्णांकerval ||
		    request->scan_plans[i].पूर्णांकerval >
		    wiphy->max_sched_scan_plan_पूर्णांकerval)
			वापस -EINVAL;

		अगर (plan[NL80211_SCHED_SCAN_PLAN_ITERATIONS]) अणु
			request->scan_plans[i].iterations =
				nla_get_u32(plan[NL80211_SCHED_SCAN_PLAN_ITERATIONS]);
			अगर (!request->scan_plans[i].iterations ||
			    (request->scan_plans[i].iterations >
			     wiphy->max_sched_scan_plan_iterations))
				वापस -EINVAL;
		पूर्ण अन्यथा अगर (i < n_plans - 1) अणु
			/*
			 * All scan plans but the last one must specअगरy
			 * a finite number of iterations
			 */
			वापस -EINVAL;
		पूर्ण

		i++;
	पूर्ण

	/*
	 * The last scan plan must not specअगरy the number of
	 * iterations, it is supposed to run infinitely
	 */
	अगर (request->scan_plans[n_plans - 1].iterations)
		वापस  -EINVAL;

	वापस 0;
पूर्ण

अटल पूर्णांक
nl80211_parse_sched_scan_per_band_rssi(काष्ठा wiphy *wiphy,
				       काष्ठा cfg80211_match_set *match_sets,
				       काष्ठा nlattr *tb_band_rssi,
				       s32 rssi_thold)
अणु
	काष्ठा nlattr *attr;
	पूर्णांक i, पंचांगp, ret = 0;

	अगर (!wiphy_ext_feature_isset(wiphy,
		    NL80211_EXT_FEATURE_SCHED_SCAN_BAND_SPECIFIC_RSSI_THOLD)) अणु
		अगर (tb_band_rssi)
			ret = -EOPNOTSUPP;
		अन्यथा
			क्रम (i = 0; i < NUM_NL80211_BANDS; i++)
				match_sets->per_band_rssi_thold[i] =
					NL80211_SCAN_RSSI_THOLD_OFF;
		वापस ret;
	पूर्ण

	क्रम (i = 0; i < NUM_NL80211_BANDS; i++)
		match_sets->per_band_rssi_thold[i] = rssi_thold;

	nla_क्रम_each_nested(attr, tb_band_rssi, पंचांगp) अणु
		क्रमागत nl80211_band band = nla_type(attr);

		अगर (band < 0 || band >= NUM_NL80211_BANDS)
			वापस -EINVAL;

		match_sets->per_band_rssi_thold[band] =	nla_get_s32(attr);
	पूर्ण

	वापस 0;
पूर्ण

अटल काष्ठा cfg80211_sched_scan_request *
nl80211_parse_sched_scan(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			 काष्ठा nlattr **attrs, पूर्णांक max_match_sets)
अणु
	काष्ठा cfg80211_sched_scan_request *request;
	काष्ठा nlattr *attr;
	पूर्णांक err, पंचांगp, n_ssids = 0, n_match_sets = 0, n_channels, i, n_plans = 0;
	क्रमागत nl80211_band band;
	माप_प्रकार ie_len;
	काष्ठा nlattr *tb[NL80211_SCHED_SCAN_MATCH_ATTR_MAX + 1];
	s32 शेष_match_rssi = NL80211_SCAN_RSSI_THOLD_OFF;

	अगर (attrs[NL80211_ATTR_SCAN_FREQUENCIES]) अणु
		n_channels = validate_scan_freqs(
				attrs[NL80211_ATTR_SCAN_FREQUENCIES]);
		अगर (!n_channels)
			वापस ERR_PTR(-EINVAL);
	पूर्ण अन्यथा अणु
		n_channels = ieee80211_get_num_supported_channels(wiphy);
	पूर्ण

	अगर (attrs[NL80211_ATTR_SCAN_SSIDS])
		nla_क्रम_each_nested(attr, attrs[NL80211_ATTR_SCAN_SSIDS],
				    पंचांगp)
			n_ssids++;

	अगर (n_ssids > wiphy->max_sched_scan_ssids)
		वापस ERR_PTR(-EINVAL);

	/*
	 * First, count the number of 'real' matchsets. Due to an issue with
	 * the old implementation, matchsets containing only the RSSI attribute
	 * (NL80211_SCHED_SCAN_MATCH_ATTR_RSSI) are considered as the 'default'
	 * RSSI क्रम all matchsets, rather than their own matchset क्रम reporting
	 * all APs with a strong RSSI. This is needed to be compatible with
	 * older userspace that treated a matchset with only the RSSI as the
	 * global RSSI क्रम all other matchsets - अगर there are other matchsets.
	 */
	अगर (attrs[NL80211_ATTR_SCHED_SCAN_MATCH]) अणु
		nla_क्रम_each_nested(attr,
				    attrs[NL80211_ATTR_SCHED_SCAN_MATCH],
				    पंचांगp) अणु
			काष्ठा nlattr *rssi;

			err = nla_parse_nested_deprecated(tb,
							  NL80211_SCHED_SCAN_MATCH_ATTR_MAX,
							  attr,
							  nl80211_match_policy,
							  शून्य);
			अगर (err)
				वापस ERR_PTR(err);

			/* SSID and BSSID are mutually exclusive */
			अगर (tb[NL80211_SCHED_SCAN_MATCH_ATTR_SSID] &&
			    tb[NL80211_SCHED_SCAN_MATCH_ATTR_BSSID])
				वापस ERR_PTR(-EINVAL);

			/* add other standalone attributes here */
			अगर (tb[NL80211_SCHED_SCAN_MATCH_ATTR_SSID] ||
			    tb[NL80211_SCHED_SCAN_MATCH_ATTR_BSSID]) अणु
				n_match_sets++;
				जारी;
			पूर्ण
			rssi = tb[NL80211_SCHED_SCAN_MATCH_ATTR_RSSI];
			अगर (rssi)
				शेष_match_rssi = nla_get_s32(rssi);
		पूर्ण
	पूर्ण

	/* However, अगर there's no other matchset, add the RSSI one */
	अगर (!n_match_sets && शेष_match_rssi != NL80211_SCAN_RSSI_THOLD_OFF)
		n_match_sets = 1;

	अगर (n_match_sets > max_match_sets)
		वापस ERR_PTR(-EINVAL);

	अगर (attrs[NL80211_ATTR_IE])
		ie_len = nla_len(attrs[NL80211_ATTR_IE]);
	अन्यथा
		ie_len = 0;

	अगर (ie_len > wiphy->max_sched_scan_ie_len)
		वापस ERR_PTR(-EINVAL);

	अगर (attrs[NL80211_ATTR_SCHED_SCAN_PLANS]) अणु
		/*
		 * NL80211_ATTR_SCHED_SCAN_INTERVAL must not be specअगरied since
		 * each scan plan alपढ़ोy specअगरies its own पूर्णांकerval
		 */
		अगर (attrs[NL80211_ATTR_SCHED_SCAN_INTERVAL])
			वापस ERR_PTR(-EINVAL);

		nla_क्रम_each_nested(attr,
				    attrs[NL80211_ATTR_SCHED_SCAN_PLANS], पंचांगp)
			n_plans++;
	पूर्ण अन्यथा अणु
		/*
		 * The scan पूर्णांकerval attribute is kept क्रम backward
		 * compatibility. If no scan plans are specअगरied and sched scan
		 * पूर्णांकerval is specअगरied, one scan plan will be set with this
		 * scan पूर्णांकerval and infinite number of iterations.
		 */
		अगर (!attrs[NL80211_ATTR_SCHED_SCAN_INTERVAL])
			वापस ERR_PTR(-EINVAL);

		n_plans = 1;
	पूर्ण

	अगर (!n_plans || n_plans > wiphy->max_sched_scan_plans)
		वापस ERR_PTR(-EINVAL);

	अगर (!wiphy_ext_feature_isset(
		    wiphy, NL80211_EXT_FEATURE_SCHED_SCAN_RELATIVE_RSSI) &&
	    (attrs[NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI] ||
	     attrs[NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST]))
		वापस ERR_PTR(-EINVAL);

	request = kzalloc(माप(*request)
			+ माप(*request->ssids) * n_ssids
			+ माप(*request->match_sets) * n_match_sets
			+ माप(*request->scan_plans) * n_plans
			+ माप(*request->channels) * n_channels
			+ ie_len, GFP_KERNEL);
	अगर (!request)
		वापस ERR_PTR(-ENOMEM);

	अगर (n_ssids)
		request->ssids = (व्योम *)&request->channels[n_channels];
	request->n_ssids = n_ssids;
	अगर (ie_len) अणु
		अगर (n_ssids)
			request->ie = (व्योम *)(request->ssids + n_ssids);
		अन्यथा
			request->ie = (व्योम *)(request->channels + n_channels);
	पूर्ण

	अगर (n_match_sets) अणु
		अगर (request->ie)
			request->match_sets = (व्योम *)(request->ie + ie_len);
		अन्यथा अगर (n_ssids)
			request->match_sets =
				(व्योम *)(request->ssids + n_ssids);
		अन्यथा
			request->match_sets =
				(व्योम *)(request->channels + n_channels);
	पूर्ण
	request->n_match_sets = n_match_sets;

	अगर (n_match_sets)
		request->scan_plans = (व्योम *)(request->match_sets +
					       n_match_sets);
	अन्यथा अगर (request->ie)
		request->scan_plans = (व्योम *)(request->ie + ie_len);
	अन्यथा अगर (n_ssids)
		request->scan_plans = (व्योम *)(request->ssids + n_ssids);
	अन्यथा
		request->scan_plans = (व्योम *)(request->channels + n_channels);

	request->n_scan_plans = n_plans;

	i = 0;
	अगर (attrs[NL80211_ATTR_SCAN_FREQUENCIES]) अणु
		/* user specअगरied, bail out अगर channel not found */
		nla_क्रम_each_nested(attr,
				    attrs[NL80211_ATTR_SCAN_FREQUENCIES],
				    पंचांगp) अणु
			काष्ठा ieee80211_channel *chan;

			chan = ieee80211_get_channel(wiphy, nla_get_u32(attr));

			अगर (!chan) अणु
				err = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण

			/* ignore disabled channels */
			अगर (chan->flags & IEEE80211_CHAN_DISABLED)
				जारी;

			request->channels[i] = chan;
			i++;
		पूर्ण
	पूर्ण अन्यथा अणु
		/* all channels */
		क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
			पूर्णांक j;

			अगर (!wiphy->bands[band])
				जारी;
			क्रम (j = 0; j < wiphy->bands[band]->n_channels; j++) अणु
				काष्ठा ieee80211_channel *chan;

				chan = &wiphy->bands[band]->channels[j];

				अगर (chan->flags & IEEE80211_CHAN_DISABLED)
					जारी;

				request->channels[i] = chan;
				i++;
			पूर्ण
		पूर्ण
	पूर्ण

	अगर (!i) अणु
		err = -EINVAL;
		जाओ out_मुक्त;
	पूर्ण

	request->n_channels = i;

	i = 0;
	अगर (n_ssids) अणु
		nla_क्रम_each_nested(attr, attrs[NL80211_ATTR_SCAN_SSIDS],
				    पंचांगp) अणु
			अगर (nla_len(attr) > IEEE80211_MAX_SSID_LEN) अणु
				err = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण
			request->ssids[i].ssid_len = nla_len(attr);
			स_नकल(request->ssids[i].ssid, nla_data(attr),
			       nla_len(attr));
			i++;
		पूर्ण
	पूर्ण

	i = 0;
	अगर (attrs[NL80211_ATTR_SCHED_SCAN_MATCH]) अणु
		nla_क्रम_each_nested(attr,
				    attrs[NL80211_ATTR_SCHED_SCAN_MATCH],
				    पंचांगp) अणु
			काष्ठा nlattr *ssid, *bssid, *rssi;

			err = nla_parse_nested_deprecated(tb,
							  NL80211_SCHED_SCAN_MATCH_ATTR_MAX,
							  attr,
							  nl80211_match_policy,
							  शून्य);
			अगर (err)
				जाओ out_मुक्त;
			ssid = tb[NL80211_SCHED_SCAN_MATCH_ATTR_SSID];
			bssid = tb[NL80211_SCHED_SCAN_MATCH_ATTR_BSSID];

			अगर (!ssid && !bssid) अणु
				i++;
				जारी;
			पूर्ण

			अगर (WARN_ON(i >= n_match_sets)) अणु
				/* this indicates a programming error,
				 * the loop above should have verअगरied
				 * things properly
				 */
				err = -EINVAL;
				जाओ out_मुक्त;
			पूर्ण

			अगर (ssid) अणु
				स_नकल(request->match_sets[i].ssid.ssid,
				       nla_data(ssid), nla_len(ssid));
				request->match_sets[i].ssid.ssid_len =
					nla_len(ssid);
			पूर्ण
			अगर (bssid)
				स_नकल(request->match_sets[i].bssid,
				       nla_data(bssid), ETH_ALEN);

			/* special attribute - old implementation w/a */
			request->match_sets[i].rssi_thold = शेष_match_rssi;
			rssi = tb[NL80211_SCHED_SCAN_MATCH_ATTR_RSSI];
			अगर (rssi)
				request->match_sets[i].rssi_thold =
					nla_get_s32(rssi);

			/* Parse per band RSSI attribute */
			err = nl80211_parse_sched_scan_per_band_rssi(wiphy,
				&request->match_sets[i],
				tb[NL80211_SCHED_SCAN_MATCH_PER_BAND_RSSI],
				request->match_sets[i].rssi_thold);
			अगर (err)
				जाओ out_मुक्त;

			i++;
		पूर्ण

		/* there was no other matchset, so the RSSI one is alone */
		अगर (i == 0 && n_match_sets)
			request->match_sets[0].rssi_thold = शेष_match_rssi;

		request->min_rssi_thold = पूर्णांक_उच्च;
		क्रम (i = 0; i < n_match_sets; i++)
			request->min_rssi_thold =
				min(request->match_sets[i].rssi_thold,
				    request->min_rssi_thold);
	पूर्ण अन्यथा अणु
		request->min_rssi_thold = NL80211_SCAN_RSSI_THOLD_OFF;
	पूर्ण

	अगर (ie_len) अणु
		request->ie_len = ie_len;
		स_नकल((व्योम *)request->ie,
		       nla_data(attrs[NL80211_ATTR_IE]),
		       request->ie_len);
	पूर्ण

	err = nl80211_check_scan_flags(wiphy, wdev, request, attrs, true);
	अगर (err)
		जाओ out_मुक्त;

	अगर (attrs[NL80211_ATTR_SCHED_SCAN_DELAY])
		request->delay =
			nla_get_u32(attrs[NL80211_ATTR_SCHED_SCAN_DELAY]);

	अगर (attrs[NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI]) अणु
		request->relative_rssi = nla_get_s8(
			attrs[NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI]);
		request->relative_rssi_set = true;
	पूर्ण

	अगर (request->relative_rssi_set &&
	    attrs[NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST]) अणु
		काष्ठा nl80211_bss_select_rssi_adjust *rssi_adjust;

		rssi_adjust = nla_data(
			attrs[NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST]);
		request->rssi_adjust.band = rssi_adjust->band;
		request->rssi_adjust.delta = rssi_adjust->delta;
		अगर (!is_band_valid(wiphy, request->rssi_adjust.band)) अणु
			err = -EINVAL;
			जाओ out_मुक्त;
		पूर्ण
	पूर्ण

	err = nl80211_parse_sched_scan_plans(wiphy, n_plans, request, attrs);
	अगर (err)
		जाओ out_मुक्त;

	request->scan_start = jअगरfies;

	वापस request;

out_मुक्त:
	kमुक्त(request);
	वापस ERR_PTR(err);
पूर्ण

अटल पूर्णांक nl80211_start_sched_scan(काष्ठा sk_buff *skb,
				    काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_sched_scan_request *sched_scan_req;
	bool want_multi;
	पूर्णांक err;

	अगर (!rdev->wiphy.max_sched_scan_reqs || !rdev->ops->sched_scan_start)
		वापस -EOPNOTSUPP;

	want_multi = info->attrs[NL80211_ATTR_SCHED_SCAN_MULTI];
	err = cfg80211_sched_scan_req_possible(rdev, want_multi);
	अगर (err)
		वापस err;

	sched_scan_req = nl80211_parse_sched_scan(&rdev->wiphy, wdev,
						  info->attrs,
						  rdev->wiphy.max_match_sets);

	err = PTR_ERR_OR_ZERO(sched_scan_req);
	अगर (err)
		जाओ out_err;

	/* leave request id zero क्रम legacy request
	 * or अगर driver करोes not support multi-scheduled scan
	 */
	अगर (want_multi && rdev->wiphy.max_sched_scan_reqs > 1)
		sched_scan_req->reqid = cfg80211_assign_cookie(rdev);

	err = rdev_sched_scan_start(rdev, dev, sched_scan_req);
	अगर (err)
		जाओ out_मुक्त;

	sched_scan_req->dev = dev;
	sched_scan_req->wiphy = &rdev->wiphy;

	अगर (info->attrs[NL80211_ATTR_SOCKET_OWNER])
		sched_scan_req->owner_nlportid = info->snd_portid;

	cfg80211_add_sched_scan_req(rdev, sched_scan_req);

	nl80211_send_sched_scan(sched_scan_req, NL80211_CMD_START_SCHED_SCAN);
	वापस 0;

out_मुक्त:
	kमुक्त(sched_scan_req);
out_err:
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_stop_sched_scan(काष्ठा sk_buff *skb,
				   काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_sched_scan_request *req;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	u64 cookie;

	अगर (!rdev->wiphy.max_sched_scan_reqs || !rdev->ops->sched_scan_stop)
		वापस -EOPNOTSUPP;

	अगर (info->attrs[NL80211_ATTR_COOKIE]) अणु
		cookie = nla_get_u64(info->attrs[NL80211_ATTR_COOKIE]);
		वापस __cfg80211_stop_sched_scan(rdev, cookie, false);
	पूर्ण

	req = list_first_or_null_rcu(&rdev->sched_scan_req_list,
				     काष्ठा cfg80211_sched_scan_request,
				     list);
	अगर (!req || req->reqid ||
	    (req->owner_nlportid &&
	     req->owner_nlportid != info->snd_portid))
		वापस -ENOENT;

	वापस cfg80211_stop_sched_scan_req(rdev, req, false);
पूर्ण

अटल पूर्णांक nl80211_start_radar_detection(काष्ठा sk_buff *skb,
					 काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_chan_def chandef;
	क्रमागत nl80211_dfs_regions dfs_region;
	अचिन्हित पूर्णांक cac_समय_ms;
	पूर्णांक err;

	dfs_region = reg_get_dfs_region(wiphy);
	अगर (dfs_region == NL80211_DFS_UNSET)
		वापस -EINVAL;

	err = nl80211_parse_chandef(rdev, info, &chandef);
	अगर (err)
		वापस err;

	अगर (netअगर_carrier_ok(dev))
		वापस -EBUSY;

	अगर (wdev->cac_started)
		वापस -EBUSY;

	err = cfg80211_chandef_dfs_required(wiphy, &chandef, wdev->अगरtype);
	अगर (err < 0)
		वापस err;

	अगर (err == 0)
		वापस -EINVAL;

	अगर (!cfg80211_chandef_dfs_usable(wiphy, &chandef))
		वापस -EINVAL;

	/* CAC start is offloaded to HW and can't be started manually */
	अगर (wiphy_ext_feature_isset(wiphy, NL80211_EXT_FEATURE_DFS_OFFLOAD))
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->start_radar_detection)
		वापस -EOPNOTSUPP;

	cac_समय_ms = cfg80211_chandef_dfs_cac_समय(&rdev->wiphy, &chandef);
	अगर (WARN_ON(!cac_समय_ms))
		cac_समय_ms = IEEE80211_DFS_MIN_CAC_TIME_MS;

	err = rdev_start_radar_detection(rdev, dev, &chandef, cac_समय_ms);
	अगर (!err) अणु
		wdev->chandef = chandef;
		wdev->cac_started = true;
		wdev->cac_start_समय = jअगरfies;
		wdev->cac_समय_ms = cac_समय_ms;
	पूर्ण
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_notअगरy_radar_detection(काष्ठा sk_buff *skb,
					  काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_chan_def chandef;
	क्रमागत nl80211_dfs_regions dfs_region;
	पूर्णांक err;

	dfs_region = reg_get_dfs_region(wiphy);
	अगर (dfs_region == NL80211_DFS_UNSET) अणु
		GENL_SET_ERR_MSG(info,
				 "DFS Region is not set. Unexpected Radar indication");
		वापस -EINVAL;
	पूर्ण

	err = nl80211_parse_chandef(rdev, info, &chandef);
	अगर (err) अणु
		GENL_SET_ERR_MSG(info, "Unable to extract chandef info");
		वापस err;
	पूर्ण

	err = cfg80211_chandef_dfs_required(wiphy, &chandef, wdev->अगरtype);
	अगर (err < 0) अणु
		GENL_SET_ERR_MSG(info, "chandef is invalid");
		वापस err;
	पूर्ण

	अगर (err == 0) अणु
		GENL_SET_ERR_MSG(info,
				 "Unexpected Radar indication for chandef/iftype");
		वापस -EINVAL;
	पूर्ण

	/* Do not process this notअगरication अगर radar is alपढ़ोy detected
	 * by kernel on this channel, and वापस success.
	 */
	अगर (chandef.chan->dfs_state == NL80211_DFS_UNAVAILABLE)
		वापस 0;

	cfg80211_set_dfs_state(wiphy, &chandef, NL80211_DFS_UNAVAILABLE);

	cfg80211_sched_dfs_chan_update(rdev);

	rdev->radar_chandef = chandef;

	/* Propagate this notअगरication to other radios as well */
	queue_work(cfg80211_wq, &rdev->propagate_radar_detect_wk);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_channel_चयन(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_csa_settings params;
	काष्ठा nlattr **csa_attrs = शून्य;
	पूर्णांक err;
	bool need_new_beacon = false;
	bool need_handle_dfs_flag = true;
	पूर्णांक len, i;
	u32 cs_count;

	अगर (!rdev->ops->channel_चयन ||
	    !(rdev->wiphy.flags & WIPHY_FLAG_HAS_CHANNEL_SWITCH))
		वापस -EOPNOTSUPP;

	चयन (dev->ieee80211_ptr->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
		need_new_beacon = true;
		/* For all modes except AP the handle_dfs flag needs to be
		 * supplied to tell the kernel that userspace will handle radar
		 * events when they happen. Otherwise a चयन to a channel
		 * requiring DFS will be rejected.
		 */
		need_handle_dfs_flag = false;

		/* useless अगर AP is not running */
		अगर (!wdev->beacon_पूर्णांकerval)
			वापस -ENOTCONN;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		अगर (!wdev->ssid_len)
			वापस -ENOTCONN;
		अवरोध;
	हाल NL80211_IFTYPE_MESH_POINT:
		अगर (!wdev->mesh_id_len)
			वापस -ENOTCONN;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	स_रखो(&params, 0, माप(params));
	params.beacon_csa.fपंचांग_responder = -1;

	अगर (!info->attrs[NL80211_ATTR_WIPHY_FREQ] ||
	    !info->attrs[NL80211_ATTR_CH_SWITCH_COUNT])
		वापस -EINVAL;

	/* only important क्रम AP, IBSS and mesh create IEs पूर्णांकernally */
	अगर (need_new_beacon && !info->attrs[NL80211_ATTR_CSA_IES])
		वापस -EINVAL;

	/* Even though the attribute is u32, the specअगरication says
	 * u8, so let's make sure we don't overflow.
	 */
	cs_count = nla_get_u32(info->attrs[NL80211_ATTR_CH_SWITCH_COUNT]);
	अगर (cs_count > 255)
		वापस -EINVAL;

	params.count = cs_count;

	अगर (!need_new_beacon)
		जाओ skip_beacons;

	err = nl80211_parse_beacon(rdev, info->attrs, &params.beacon_after);
	अगर (err)
		वापस err;

	csa_attrs = kसुस्मृति(NL80211_ATTR_MAX + 1, माप(*csa_attrs),
			    GFP_KERNEL);
	अगर (!csa_attrs)
		वापस -ENOMEM;

	err = nla_parse_nested_deprecated(csa_attrs, NL80211_ATTR_MAX,
					  info->attrs[NL80211_ATTR_CSA_IES],
					  nl80211_policy, info->extack);
	अगर (err)
		जाओ मुक्त;

	err = nl80211_parse_beacon(rdev, csa_attrs, &params.beacon_csa);
	अगर (err)
		जाओ मुक्त;

	अगर (!csa_attrs[NL80211_ATTR_CNTDWN_OFFS_BEACON]) अणु
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	len = nla_len(csa_attrs[NL80211_ATTR_CNTDWN_OFFS_BEACON]);
	अगर (!len || (len % माप(u16))) अणु
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	params.n_counter_offsets_beacon = len / माप(u16);
	अगर (rdev->wiphy.max_num_csa_counters &&
	    (params.n_counter_offsets_beacon >
	     rdev->wiphy.max_num_csa_counters)) अणु
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	params.counter_offsets_beacon =
		nla_data(csa_attrs[NL80211_ATTR_CNTDWN_OFFS_BEACON]);

	/* sanity checks - counters should fit and be the same */
	क्रम (i = 0; i < params.n_counter_offsets_beacon; i++) अणु
		u16 offset = params.counter_offsets_beacon[i];

		अगर (offset >= params.beacon_csa.tail_len) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण

		अगर (params.beacon_csa.tail[offset] != params.count) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	अगर (csa_attrs[NL80211_ATTR_CNTDWN_OFFS_PRESP]) अणु
		len = nla_len(csa_attrs[NL80211_ATTR_CNTDWN_OFFS_PRESP]);
		अगर (!len || (len % माप(u16))) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण

		params.n_counter_offsets_presp = len / माप(u16);
		अगर (rdev->wiphy.max_num_csa_counters &&
		    (params.n_counter_offsets_presp >
		     rdev->wiphy.max_num_csa_counters)) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण

		params.counter_offsets_presp =
			nla_data(csa_attrs[NL80211_ATTR_CNTDWN_OFFS_PRESP]);

		/* sanity checks - counters should fit and be the same */
		क्रम (i = 0; i < params.n_counter_offsets_presp; i++) अणु
			u16 offset = params.counter_offsets_presp[i];

			अगर (offset >= params.beacon_csa.probe_resp_len) अणु
				err = -EINVAL;
				जाओ मुक्त;
			पूर्ण

			अगर (params.beacon_csa.probe_resp[offset] !=
			    params.count) अणु
				err = -EINVAL;
				जाओ मुक्त;
			पूर्ण
		पूर्ण
	पूर्ण

skip_beacons:
	err = nl80211_parse_chandef(rdev, info, &params.chandef);
	अगर (err)
		जाओ मुक्त;

	अगर (!cfg80211_reg_can_beacon_relax(&rdev->wiphy, &params.chandef,
					   wdev->अगरtype)) अणु
		err = -EINVAL;
		जाओ मुक्त;
	पूर्ण

	err = cfg80211_chandef_dfs_required(wdev->wiphy,
					    &params.chandef,
					    wdev->अगरtype);
	अगर (err < 0)
		जाओ मुक्त;

	अगर (err > 0) अणु
		params.radar_required = true;
		अगर (need_handle_dfs_flag &&
		    !nla_get_flag(info->attrs[NL80211_ATTR_HANDLE_DFS])) अणु
			err = -EINVAL;
			जाओ मुक्त;
		पूर्ण
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_CH_SWITCH_BLOCK_TX])
		params.block_tx = true;

	wdev_lock(wdev);
	err = rdev_channel_चयन(rdev, dev, &params);
	wdev_unlock(wdev);

मुक्त:
	kमुक्त(csa_attrs);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_send_bss(काष्ठा sk_buff *msg, काष्ठा netlink_callback *cb,
			    u32 seq, पूर्णांक flags,
			    काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा wireless_dev *wdev,
			    काष्ठा cfg80211_पूर्णांकernal_bss *पूर्णांकbss)
अणु
	काष्ठा cfg80211_bss *res = &पूर्णांकbss->pub;
	स्थिर काष्ठा cfg80211_bss_ies *ies;
	व्योम *hdr;
	काष्ठा nlattr *bss;

	ASSERT_WDEV_LOCK(wdev);

	hdr = nl80211hdr_put(msg, NETLINK_CB(cb->skb).portid, seq, flags,
			     NL80211_CMD_NEW_SCAN_RESULTS);
	अगर (!hdr)
		वापस -1;

	genl_dump_check_consistent(cb, hdr);

	अगर (nla_put_u32(msg, NL80211_ATTR_GENERATION, rdev->bss_generation))
		जाओ nla_put_failure;
	अगर (wdev->netdev &&
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, wdev->netdev->अगरindex))
		जाओ nla_put_failure;
	अगर (nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	bss = nla_nest_start_noflag(msg, NL80211_ATTR_BSS);
	अगर (!bss)
		जाओ nla_put_failure;
	अगर ((!is_zero_ether_addr(res->bssid) &&
	     nla_put(msg, NL80211_BSS_BSSID, ETH_ALEN, res->bssid)))
		जाओ nla_put_failure;

	rcu_पढ़ो_lock();
	/* indicate whether we have probe response data or not */
	अगर (rcu_access_poपूर्णांकer(res->proberesp_ies) &&
	    nla_put_flag(msg, NL80211_BSS_PRESP_DATA))
		जाओ fail_unlock_rcu;

	/* this poपूर्णांकer prefers to be poपूर्णांकed to probe response data
	 * but is always valid
	 */
	ies = rcu_dereference(res->ies);
	अगर (ies) अणु
		अगर (nla_put_u64_64bit(msg, NL80211_BSS_TSF, ies->tsf,
				      NL80211_BSS_PAD))
			जाओ fail_unlock_rcu;
		अगर (ies->len && nla_put(msg, NL80211_BSS_INFORMATION_ELEMENTS,
					ies->len, ies->data))
			जाओ fail_unlock_rcu;
	पूर्ण

	/* and this poपूर्णांकer is always (unless driver didn't know) beacon data */
	ies = rcu_dereference(res->beacon_ies);
	अगर (ies && ies->from_beacon) अणु
		अगर (nla_put_u64_64bit(msg, NL80211_BSS_BEACON_TSF, ies->tsf,
				      NL80211_BSS_PAD))
			जाओ fail_unlock_rcu;
		अगर (ies->len && nla_put(msg, NL80211_BSS_BEACON_IES,
					ies->len, ies->data))
			जाओ fail_unlock_rcu;
	पूर्ण
	rcu_पढ़ो_unlock();

	अगर (res->beacon_पूर्णांकerval &&
	    nla_put_u16(msg, NL80211_BSS_BEACON_INTERVAL, res->beacon_पूर्णांकerval))
		जाओ nla_put_failure;
	अगर (nla_put_u16(msg, NL80211_BSS_CAPABILITY, res->capability) ||
	    nla_put_u32(msg, NL80211_BSS_FREQUENCY, res->channel->center_freq) ||
	    nla_put_u32(msg, NL80211_BSS_FREQUENCY_OFFSET,
			res->channel->freq_offset) ||
	    nla_put_u32(msg, NL80211_BSS_CHAN_WIDTH, res->scan_width) ||
	    nla_put_u32(msg, NL80211_BSS_SEEN_MS_AGO,
			jअगरfies_to_msecs(jअगरfies - पूर्णांकbss->ts)))
		जाओ nla_put_failure;

	अगर (पूर्णांकbss->parent_tsf &&
	    (nla_put_u64_64bit(msg, NL80211_BSS_PARENT_TSF,
			       पूर्णांकbss->parent_tsf, NL80211_BSS_PAD) ||
	     nla_put(msg, NL80211_BSS_PARENT_BSSID, ETH_ALEN,
		     पूर्णांकbss->parent_bssid)))
		जाओ nla_put_failure;

	अगर (पूर्णांकbss->ts_bootसमय &&
	    nla_put_u64_64bit(msg, NL80211_BSS_LAST_SEEN_BOOTTIME,
			      पूर्णांकbss->ts_bootसमय, NL80211_BSS_PAD))
		जाओ nla_put_failure;

	अगर (!nl80211_put_संकेत(msg, पूर्णांकbss->pub.chains,
				पूर्णांकbss->pub.chain_संकेत,
				NL80211_BSS_CHAIN_SIGNAL))
		जाओ nla_put_failure;

	चयन (rdev->wiphy.संकेत_type) अणु
	हाल CFG80211_SIGNAL_TYPE_MBM:
		अगर (nla_put_u32(msg, NL80211_BSS_SIGNAL_MBM, res->संकेत))
			जाओ nla_put_failure;
		अवरोध;
	हाल CFG80211_SIGNAL_TYPE_UNSPEC:
		अगर (nla_put_u8(msg, NL80211_BSS_SIGNAL_UNSPEC, res->संकेत))
			जाओ nla_put_failure;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_STATION:
		अगर (पूर्णांकbss == wdev->current_bss &&
		    nla_put_u32(msg, NL80211_BSS_STATUS,
				NL80211_BSS_STATUS_ASSOCIATED))
			जाओ nla_put_failure;
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
		अगर (पूर्णांकbss == wdev->current_bss &&
		    nla_put_u32(msg, NL80211_BSS_STATUS,
				NL80211_BSS_STATUS_IBSS_JOINED))
			जाओ nla_put_failure;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	nla_nest_end(msg, bss);

	genlmsg_end(msg, hdr);
	वापस 0;

 fail_unlock_rcu:
	rcu_पढ़ो_unlock();
 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_dump_scan(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा cfg80211_पूर्णांकernal_bss *scan;
	काष्ठा wireless_dev *wdev;
	पूर्णांक start = cb->args[2], idx = 0;
	पूर्णांक err;

	err = nl80211_prepare_wdev_dump(cb, &rdev, &wdev);
	अगर (err)
		वापस err;
	/* nl80211_prepare_wdev_dump acquired it in the successful हाल */
	__acquire(&rdev->wiphy.mtx);

	wdev_lock(wdev);
	spin_lock_bh(&rdev->bss_lock);

	/*
	 * dump_scan will be called multiple बार to अवरोध up the scan results
	 * पूर्णांकo multiple messages.  It is unlikely that any more bss-es will be
	 * expired after the first call, so only call only call this on the
	 * first dump_scan invocation.
	 */
	अगर (start == 0)
		cfg80211_bss_expire(rdev);

	cb->seq = rdev->bss_generation;

	list_क्रम_each_entry(scan, &rdev->bss_list, list) अणु
		अगर (++idx <= start)
			जारी;
		अगर (nl80211_send_bss(skb, cb,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				rdev, wdev, scan) < 0) अणु
			idx--;
			अवरोध;
		पूर्ण
	पूर्ण

	spin_unlock_bh(&rdev->bss_lock);
	wdev_unlock(wdev);

	cb->args[2] = idx;
	wiphy_unlock(&rdev->wiphy);

	वापस skb->len;
पूर्ण

अटल पूर्णांक nl80211_send_survey(काष्ठा sk_buff *msg, u32 portid, u32 seq,
			       पूर्णांक flags, काष्ठा net_device *dev,
			       bool allow_radio_stats,
			       काष्ठा survey_info *survey)
अणु
	व्योम *hdr;
	काष्ठा nlattr *infoattr;

	/* skip radio stats अगर userspace didn't request them */
	अगर (!survey->channel && !allow_radio_stats)
		वापस 0;

	hdr = nl80211hdr_put(msg, portid, seq, flags,
			     NL80211_CMD_NEW_SURVEY_RESULTS);
	अगर (!hdr)
		वापस -ENOMEM;

	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	infoattr = nla_nest_start_noflag(msg, NL80211_ATTR_SURVEY_INFO);
	अगर (!infoattr)
		जाओ nla_put_failure;

	अगर (survey->channel &&
	    nla_put_u32(msg, NL80211_SURVEY_INFO_FREQUENCY,
			survey->channel->center_freq))
		जाओ nla_put_failure;

	अगर (survey->channel && survey->channel->freq_offset &&
	    nla_put_u32(msg, NL80211_SURVEY_INFO_FREQUENCY_OFFSET,
			survey->channel->freq_offset))
		जाओ nla_put_failure;

	अगर ((survey->filled & SURVEY_INFO_NOISE_DBM) &&
	    nla_put_u8(msg, NL80211_SURVEY_INFO_NOISE, survey->noise))
		जाओ nla_put_failure;
	अगर ((survey->filled & SURVEY_INFO_IN_USE) &&
	    nla_put_flag(msg, NL80211_SURVEY_INFO_IN_USE))
		जाओ nla_put_failure;
	अगर ((survey->filled & SURVEY_INFO_TIME) &&
	    nla_put_u64_64bit(msg, NL80211_SURVEY_INFO_TIME,
			survey->समय, NL80211_SURVEY_INFO_PAD))
		जाओ nla_put_failure;
	अगर ((survey->filled & SURVEY_INFO_TIME_BUSY) &&
	    nla_put_u64_64bit(msg, NL80211_SURVEY_INFO_TIME_BUSY,
			      survey->समय_busy, NL80211_SURVEY_INFO_PAD))
		जाओ nla_put_failure;
	अगर ((survey->filled & SURVEY_INFO_TIME_EXT_BUSY) &&
	    nla_put_u64_64bit(msg, NL80211_SURVEY_INFO_TIME_EXT_BUSY,
			      survey->समय_ext_busy, NL80211_SURVEY_INFO_PAD))
		जाओ nla_put_failure;
	अगर ((survey->filled & SURVEY_INFO_TIME_RX) &&
	    nla_put_u64_64bit(msg, NL80211_SURVEY_INFO_TIME_RX,
			      survey->समय_rx, NL80211_SURVEY_INFO_PAD))
		जाओ nla_put_failure;
	अगर ((survey->filled & SURVEY_INFO_TIME_TX) &&
	    nla_put_u64_64bit(msg, NL80211_SURVEY_INFO_TIME_TX,
			      survey->समय_प्रकारx, NL80211_SURVEY_INFO_PAD))
		जाओ nla_put_failure;
	अगर ((survey->filled & SURVEY_INFO_TIME_SCAN) &&
	    nla_put_u64_64bit(msg, NL80211_SURVEY_INFO_TIME_SCAN,
			      survey->समय_scan, NL80211_SURVEY_INFO_PAD))
		जाओ nla_put_failure;
	अगर ((survey->filled & SURVEY_INFO_TIME_BSS_RX) &&
	    nla_put_u64_64bit(msg, NL80211_SURVEY_INFO_TIME_BSS_RX,
			      survey->समय_bss_rx, NL80211_SURVEY_INFO_PAD))
		जाओ nla_put_failure;

	nla_nest_end(msg, infoattr);

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक nl80211_dump_survey(काष्ठा sk_buff *skb, काष्ठा netlink_callback *cb)
अणु
	काष्ठा nlattr **attrbuf;
	काष्ठा survey_info survey;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;
	पूर्णांक survey_idx = cb->args[2];
	पूर्णांक res;
	bool radio_stats;

	attrbuf = kसुस्मृति(NUM_NL80211_ATTR, माप(*attrbuf), GFP_KERNEL);
	अगर (!attrbuf)
		वापस -ENOMEM;

	res = nl80211_prepare_wdev_dump(cb, &rdev, &wdev);
	अगर (res) अणु
		kमुक्त(attrbuf);
		वापस res;
	पूर्ण
	/* nl80211_prepare_wdev_dump acquired it in the successful हाल */
	__acquire(&rdev->wiphy.mtx);

	/* prepare_wdev_dump parsed the attributes */
	radio_stats = attrbuf[NL80211_ATTR_SURVEY_RADIO_STATS];

	अगर (!wdev->netdev) अणु
		res = -EINVAL;
		जाओ out_err;
	पूर्ण

	अगर (!rdev->ops->dump_survey) अणु
		res = -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण

	जबतक (1) अणु
		res = rdev_dump_survey(rdev, wdev->netdev, survey_idx, &survey);
		अगर (res == -ENOENT)
			अवरोध;
		अगर (res)
			जाओ out_err;

		/* करोn't send disabled channels, but करो send non-channel data */
		अगर (survey.channel &&
		    survey.channel->flags & IEEE80211_CHAN_DISABLED) अणु
			survey_idx++;
			जारी;
		पूर्ण

		अगर (nl80211_send_survey(skb,
				NETLINK_CB(cb->skb).portid,
				cb->nlh->nlmsg_seq, NLM_F_MULTI,
				wdev->netdev, radio_stats, &survey) < 0)
			जाओ out;
		survey_idx++;
	पूर्ण

 out:
	cb->args[2] = survey_idx;
	res = skb->len;
 out_err:
	kमुक्त(attrbuf);
	wiphy_unlock(&rdev->wiphy);
	वापस res;
पूर्ण

अटल bool nl80211_valid_wpa_versions(u32 wpa_versions)
अणु
	वापस !(wpa_versions & ~(NL80211_WPA_VERSION_1 |
				  NL80211_WPA_VERSION_2 |
				  NL80211_WPA_VERSION_3));
पूर्ण

अटल पूर्णांक nl80211_authenticate(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा ieee80211_channel *chan;
	स्थिर u8 *bssid, *ssid, *ie = शून्य, *auth_data = शून्य;
	पूर्णांक err, ssid_len, ie_len = 0, auth_data_len = 0;
	क्रमागत nl80211_auth_type auth_type;
	काष्ठा key_parse key;
	bool local_state_change;
	u32 freq;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_AUTH_TYPE])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_SSID])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_WIPHY_FREQ])
		वापस -EINVAL;

	err = nl80211_parse_key(info, &key);
	अगर (err)
		वापस err;

	अगर (key.idx >= 0) अणु
		अगर (key.type != -1 && key.type != NL80211_KEYTYPE_GROUP)
			वापस -EINVAL;
		अगर (!key.p.key || !key.p.key_len)
			वापस -EINVAL;
		अगर ((key.p.cipher != WLAN_CIPHER_SUITE_WEP40 ||
		     key.p.key_len != WLAN_KEY_LEN_WEP40) &&
		    (key.p.cipher != WLAN_CIPHER_SUITE_WEP104 ||
		     key.p.key_len != WLAN_KEY_LEN_WEP104))
			वापस -EINVAL;
		अगर (key.idx > 3)
			वापस -EINVAL;
	पूर्ण अन्यथा अणु
		key.p.key_len = 0;
		key.p.key = शून्य;
	पूर्ण

	अगर (key.idx >= 0) अणु
		पूर्णांक i;
		bool ok = false;

		क्रम (i = 0; i < rdev->wiphy.n_cipher_suites; i++) अणु
			अगर (key.p.cipher == rdev->wiphy.cipher_suites[i]) अणु
				ok = true;
				अवरोध;
			पूर्ण
		पूर्ण
		अगर (!ok)
			वापस -EINVAL;
	पूर्ण

	अगर (!rdev->ops->auth)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);
	freq = MHZ_TO_KHZ(nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ]));
	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ_OFFSET])
		freq +=
		    nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ_OFFSET]);

	chan = nl80211_get_valid_chan(&rdev->wiphy, freq);
	अगर (!chan)
		वापस -EINVAL;

	ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
	ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	पूर्ण

	auth_type = nla_get_u32(info->attrs[NL80211_ATTR_AUTH_TYPE]);
	अगर (!nl80211_valid_auth_type(rdev, auth_type, NL80211_CMD_AUTHENTICATE))
		वापस -EINVAL;

	अगर ((auth_type == NL80211_AUTHTYPE_SAE ||
	     auth_type == NL80211_AUTHTYPE_FILS_SK ||
	     auth_type == NL80211_AUTHTYPE_FILS_SK_PFS ||
	     auth_type == NL80211_AUTHTYPE_FILS_PK) &&
	    !info->attrs[NL80211_ATTR_AUTH_DATA])
		वापस -EINVAL;

	अगर (info->attrs[NL80211_ATTR_AUTH_DATA]) अणु
		अगर (auth_type != NL80211_AUTHTYPE_SAE &&
		    auth_type != NL80211_AUTHTYPE_FILS_SK &&
		    auth_type != NL80211_AUTHTYPE_FILS_SK_PFS &&
		    auth_type != NL80211_AUTHTYPE_FILS_PK)
			वापस -EINVAL;
		auth_data = nla_data(info->attrs[NL80211_ATTR_AUTH_DATA]);
		auth_data_len = nla_len(info->attrs[NL80211_ATTR_AUTH_DATA]);
	पूर्ण

	local_state_change = !!info->attrs[NL80211_ATTR_LOCAL_STATE_CHANGE];

	/*
	 * Since we no दीर्घer track auth state, ignore
	 * requests to only change local state.
	 */
	अगर (local_state_change)
		वापस 0;

	wdev_lock(dev->ieee80211_ptr);
	err = cfg80211_mlme_auth(rdev, dev, chan, auth_type, bssid,
				 ssid, ssid_len, ie, ie_len,
				 key.p.key, key.p.key_len, key.idx,
				 auth_data, auth_data_len);
	wdev_unlock(dev->ieee80211_ptr);
	वापस err;
पूर्ण

अटल पूर्णांक validate_pae_over_nl80211(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा genl_info *info)
अणु
	अगर (!info->attrs[NL80211_ATTR_SOCKET_OWNER]) अणु
		GENL_SET_ERR_MSG(info, "SOCKET_OWNER not set");
		वापस -EINVAL;
	पूर्ण

	अगर (!rdev->ops->tx_control_port ||
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211))
		वापस -EOPNOTSUPP;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_crypto_settings(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   काष्ठा genl_info *info,
				   काष्ठा cfg80211_crypto_settings *settings,
				   पूर्णांक cipher_limit)
अणु
	स_रखो(settings, 0, माप(*settings));

	settings->control_port = info->attrs[NL80211_ATTR_CONTROL_PORT];

	अगर (info->attrs[NL80211_ATTR_CONTROL_PORT_ETHERTYPE]) अणु
		u16 proto;

		proto = nla_get_u16(
			info->attrs[NL80211_ATTR_CONTROL_PORT_ETHERTYPE]);
		settings->control_port_ethertype = cpu_to_be16(proto);
		अगर (!(rdev->wiphy.flags & WIPHY_FLAG_CONTROL_PORT_PROTOCOL) &&
		    proto != ETH_P_PAE)
			वापस -EINVAL;
		अगर (info->attrs[NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT])
			settings->control_port_no_encrypt = true;
	पूर्ण अन्यथा
		settings->control_port_ethertype = cpu_to_be16(ETH_P_PAE);

	अगर (info->attrs[NL80211_ATTR_CONTROL_PORT_OVER_NL80211]) अणु
		पूर्णांक r = validate_pae_over_nl80211(rdev, info);

		अगर (r < 0)
			वापस r;

		settings->control_port_over_nl80211 = true;

		अगर (info->attrs[NL80211_ATTR_CONTROL_PORT_NO_PREAUTH])
			settings->control_port_no_preauth = true;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_CIPHER_SUITES_PAIRWISE]) अणु
		व्योम *data;
		पूर्णांक len, i;

		data = nla_data(info->attrs[NL80211_ATTR_CIPHER_SUITES_PAIRWISE]);
		len = nla_len(info->attrs[NL80211_ATTR_CIPHER_SUITES_PAIRWISE]);
		settings->n_ciphers_pairwise = len / माप(u32);

		अगर (len % माप(u32))
			वापस -EINVAL;

		अगर (settings->n_ciphers_pairwise > cipher_limit)
			वापस -EINVAL;

		स_नकल(settings->ciphers_pairwise, data, len);

		क्रम (i = 0; i < settings->n_ciphers_pairwise; i++)
			अगर (!cfg80211_supported_cipher_suite(
					&rdev->wiphy,
					settings->ciphers_pairwise[i]))
				वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_CIPHER_SUITE_GROUP]) अणु
		settings->cipher_group =
			nla_get_u32(info->attrs[NL80211_ATTR_CIPHER_SUITE_GROUP]);
		अगर (!cfg80211_supported_cipher_suite(&rdev->wiphy,
						     settings->cipher_group))
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WPA_VERSIONS]) अणु
		settings->wpa_versions =
			nla_get_u32(info->attrs[NL80211_ATTR_WPA_VERSIONS]);
		अगर (!nl80211_valid_wpa_versions(settings->wpa_versions))
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_AKM_SUITES]) अणु
		व्योम *data;
		पूर्णांक len;

		data = nla_data(info->attrs[NL80211_ATTR_AKM_SUITES]);
		len = nla_len(info->attrs[NL80211_ATTR_AKM_SUITES]);
		settings->n_akm_suites = len / माप(u32);

		अगर (len % माप(u32))
			वापस -EINVAL;

		अगर (settings->n_akm_suites > NL80211_MAX_NR_AKM_SUITES)
			वापस -EINVAL;

		स_नकल(settings->akm_suites, data, len);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_PMK]) अणु
		अगर (nla_len(info->attrs[NL80211_ATTR_PMK]) != WLAN_PMK_LEN)
			वापस -EINVAL;
		अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_PSK) &&
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_4WAY_HANDSHAKE_AP_PSK))
			वापस -EINVAL;
		settings->psk = nla_data(info->attrs[NL80211_ATTR_PMK]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_SAE_PASSWORD]) अणु
		अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_SAE_OFFLOAD) &&
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_SAE_OFFLOAD_AP))
			वापस -EINVAL;
		settings->sae_pwd =
			nla_data(info->attrs[NL80211_ATTR_SAE_PASSWORD]);
		settings->sae_pwd_len =
			nla_len(info->attrs[NL80211_ATTR_SAE_PASSWORD]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_SAE_PWE])
		settings->sae_pwe =
			nla_get_u8(info->attrs[NL80211_ATTR_SAE_PWE]);
	अन्यथा
		settings->sae_pwe = NL80211_SAE_PWE_UNSPECIFIED;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_associate(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा ieee80211_channel *chan;
	काष्ठा cfg80211_assoc_request req = अणुपूर्ण;
	स्थिर u8 *bssid, *ssid;
	पूर्णांक err, ssid_len = 0;
	u32 freq;

	अगर (dev->ieee80211_ptr->conn_owner_nlportid &&
	    dev->ieee80211_ptr->conn_owner_nlportid != info->snd_portid)
		वापस -EPERM;

	अगर (!info->attrs[NL80211_ATTR_MAC] ||
	    !info->attrs[NL80211_ATTR_SSID] ||
	    !info->attrs[NL80211_ATTR_WIPHY_FREQ])
		वापस -EINVAL;

	अगर (!rdev->ops->assoc)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);

	freq = MHZ_TO_KHZ(nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ]));
	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ_OFFSET])
		freq +=
		    nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ_OFFSET]);
	chan = nl80211_get_valid_chan(&rdev->wiphy, freq);
	अगर (!chan)
		वापस -EINVAL;

	ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
	ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		req.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		req.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_USE_MFP]) अणु
		क्रमागत nl80211_mfp mfp =
			nla_get_u32(info->attrs[NL80211_ATTR_USE_MFP]);
		अगर (mfp == NL80211_MFP_REQUIRED)
			req.use_mfp = true;
		अन्यथा अगर (mfp != NL80211_MFP_NO)
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_PREV_BSSID])
		req.prev_bssid = nla_data(info->attrs[NL80211_ATTR_PREV_BSSID]);

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_DISABLE_HT]))
		req.flags |= ASSOC_REQ_DISABLE_HT;

	अगर (info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK])
		स_नकल(&req.ht_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK]),
		       माप(req.ht_capa_mask));

	अगर (info->attrs[NL80211_ATTR_HT_CAPABILITY]) अणु
		अगर (!info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK])
			वापस -EINVAL;
		स_नकल(&req.ht_capa,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY]),
		       माप(req.ht_capa));
	पूर्ण

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_DISABLE_VHT]))
		req.flags |= ASSOC_REQ_DISABLE_VHT;

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_DISABLE_HE]))
		req.flags |= ASSOC_REQ_DISABLE_HE;

	अगर (info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK])
		स_नकल(&req.vht_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK]),
		       माप(req.vht_capa_mask));

	अगर (info->attrs[NL80211_ATTR_VHT_CAPABILITY]) अणु
		अगर (!info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK])
			वापस -EINVAL;
		स_नकल(&req.vht_capa,
		       nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY]),
		       माप(req.vht_capa));
	पूर्ण

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_USE_RRM])) अणु
		अगर (!((rdev->wiphy.features &
			NL80211_FEATURE_DS_PARAM_SET_IE_IN_PROBES) &&
		       (rdev->wiphy.features & NL80211_FEATURE_QUIET)) &&
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_RRM))
			वापस -EINVAL;
		req.flags |= ASSOC_REQ_USE_RRM;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_FILS_KEK]) अणु
		req.fils_kek = nla_data(info->attrs[NL80211_ATTR_FILS_KEK]);
		req.fils_kek_len = nla_len(info->attrs[NL80211_ATTR_FILS_KEK]);
		अगर (!info->attrs[NL80211_ATTR_FILS_NONCES])
			वापस -EINVAL;
		req.fils_nonces =
			nla_data(info->attrs[NL80211_ATTR_FILS_NONCES]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_S1G_CAPABILITY_MASK]) अणु
		अगर (!info->attrs[NL80211_ATTR_S1G_CAPABILITY])
			वापस -EINVAL;
		स_नकल(&req.s1g_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_S1G_CAPABILITY_MASK]),
		       माप(req.s1g_capa_mask));
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_S1G_CAPABILITY]) अणु
		अगर (!info->attrs[NL80211_ATTR_S1G_CAPABILITY_MASK])
			वापस -EINVAL;
		स_नकल(&req.s1g_capa,
		       nla_data(info->attrs[NL80211_ATTR_S1G_CAPABILITY]),
		       माप(req.s1g_capa));
	पूर्ण

	err = nl80211_crypto_settings(rdev, info, &req.crypto, 1);
	अगर (!err) अणु
		wdev_lock(dev->ieee80211_ptr);

		err = cfg80211_mlme_assoc(rdev, dev, chan, bssid,
					  ssid, ssid_len, &req);

		अगर (!err && info->attrs[NL80211_ATTR_SOCKET_OWNER]) अणु
			dev->ieee80211_ptr->conn_owner_nlportid =
				info->snd_portid;
			स_नकल(dev->ieee80211_ptr->disconnect_bssid,
			       bssid, ETH_ALEN);
		पूर्ण

		wdev_unlock(dev->ieee80211_ptr);
	पूर्ण

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_deauthenticate(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	स्थिर u8 *ie = शून्य, *bssid;
	पूर्णांक ie_len = 0, err;
	u16 reason_code;
	bool local_state_change;

	अगर (dev->ieee80211_ptr->conn_owner_nlportid &&
	    dev->ieee80211_ptr->conn_owner_nlportid != info->snd_portid)
		वापस -EPERM;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_REASON_CODE])
		वापस -EINVAL;

	अगर (!rdev->ops->deauth)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);

	reason_code = nla_get_u16(info->attrs[NL80211_ATTR_REASON_CODE]);
	अगर (reason_code == 0) अणु
		/* Reason Code 0 is reserved */
		वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	पूर्ण

	local_state_change = !!info->attrs[NL80211_ATTR_LOCAL_STATE_CHANGE];

	wdev_lock(dev->ieee80211_ptr);
	err = cfg80211_mlme_deauth(rdev, dev, bssid, ie, ie_len, reason_code,
				   local_state_change);
	wdev_unlock(dev->ieee80211_ptr);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_disassociate(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	स्थिर u8 *ie = शून्य, *bssid;
	पूर्णांक ie_len = 0, err;
	u16 reason_code;
	bool local_state_change;

	अगर (dev->ieee80211_ptr->conn_owner_nlportid &&
	    dev->ieee80211_ptr->conn_owner_nlportid != info->snd_portid)
		वापस -EPERM;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_REASON_CODE])
		वापस -EINVAL;

	अगर (!rdev->ops->disassoc)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);

	reason_code = nla_get_u16(info->attrs[NL80211_ATTR_REASON_CODE]);
	अगर (reason_code == 0) अणु
		/* Reason Code 0 is reserved */
		वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	पूर्ण

	local_state_change = !!info->attrs[NL80211_ATTR_LOCAL_STATE_CHANGE];

	wdev_lock(dev->ieee80211_ptr);
	err = cfg80211_mlme_disassoc(rdev, dev, bssid, ie, ie_len, reason_code,
				     local_state_change);
	wdev_unlock(dev->ieee80211_ptr);
	वापस err;
पूर्ण

अटल bool
nl80211_parse_mcast_rate(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 पूर्णांक mcast_rate[NUM_NL80211_BANDS],
			 पूर्णांक rateval)
अणु
	काष्ठा wiphy *wiphy = &rdev->wiphy;
	bool found = false;
	पूर्णांक band, i;

	क्रम (band = 0; band < NUM_NL80211_BANDS; band++) अणु
		काष्ठा ieee80211_supported_band *sband;

		sband = wiphy->bands[band];
		अगर (!sband)
			जारी;

		क्रम (i = 0; i < sband->n_bitrates; i++) अणु
			अगर (sband->bitrates[i].bitrate == rateval) अणु
				mcast_rate[band] = i + 1;
				found = true;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण

	वापस found;
पूर्ण

अटल पूर्णांक nl80211_join_ibss(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा cfg80211_ibss_params ibss;
	काष्ठा wiphy *wiphy;
	काष्ठा cfg80211_cached_keys *connkeys = शून्य;
	पूर्णांक err;

	स_रखो(&ibss, 0, माप(ibss));

	अगर (!info->attrs[NL80211_ATTR_SSID] ||
	    !nla_len(info->attrs[NL80211_ATTR_SSID]))
		वापस -EINVAL;

	ibss.beacon_पूर्णांकerval = 100;

	अगर (info->attrs[NL80211_ATTR_BEACON_INTERVAL])
		ibss.beacon_पूर्णांकerval =
			nla_get_u32(info->attrs[NL80211_ATTR_BEACON_INTERVAL]);

	err = cfg80211_validate_beacon_पूर्णांक(rdev, NL80211_IFTYPE_ADHOC,
					   ibss.beacon_पूर्णांकerval);
	अगर (err)
		वापस err;

	अगर (!rdev->ops->join_ibss)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_ADHOC)
		वापस -EOPNOTSUPP;

	wiphy = &rdev->wiphy;

	अगर (info->attrs[NL80211_ATTR_MAC]) अणु
		ibss.bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);

		अगर (!is_valid_ether_addr(ibss.bssid))
			वापस -EINVAL;
	पूर्ण
	ibss.ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
	ibss.ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		ibss.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		ibss.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	पूर्ण

	err = nl80211_parse_chandef(rdev, info, &ibss.chandef);
	अगर (err)
		वापस err;

	अगर (!cfg80211_reg_can_beacon(&rdev->wiphy, &ibss.chandef,
				     NL80211_IFTYPE_ADHOC))
		वापस -EINVAL;

	चयन (ibss.chandef.width) अणु
	हाल NL80211_CHAN_WIDTH_5:
	हाल NL80211_CHAN_WIDTH_10:
	हाल NL80211_CHAN_WIDTH_20_NOHT:
		अवरोध;
	हाल NL80211_CHAN_WIDTH_20:
	हाल NL80211_CHAN_WIDTH_40:
		अगर (!(rdev->wiphy.features & NL80211_FEATURE_HT_IBSS))
			वापस -EINVAL;
		अवरोध;
	हाल NL80211_CHAN_WIDTH_80:
	हाल NL80211_CHAN_WIDTH_80P80:
	हाल NL80211_CHAN_WIDTH_160:
		अगर (!(rdev->wiphy.features & NL80211_FEATURE_HT_IBSS))
			वापस -EINVAL;
		अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_VHT_IBSS))
			वापस -EINVAL;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	ibss.channel_fixed = !!info->attrs[NL80211_ATTR_FREQ_FIXED];
	ibss.privacy = !!info->attrs[NL80211_ATTR_PRIVACY];

	अगर (info->attrs[NL80211_ATTR_BSS_BASIC_RATES]) अणु
		u8 *rates =
			nla_data(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		पूर्णांक n_rates =
			nla_len(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		काष्ठा ieee80211_supported_band *sband =
			wiphy->bands[ibss.chandef.chan->band];

		err = ieee80211_get_ratemask(sband, rates, n_rates,
					     &ibss.basic_rates);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK])
		स_नकल(&ibss.ht_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK]),
		       माप(ibss.ht_capa_mask));

	अगर (info->attrs[NL80211_ATTR_HT_CAPABILITY]) अणु
		अगर (!info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK])
			वापस -EINVAL;
		स_नकल(&ibss.ht_capa,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY]),
		       माप(ibss.ht_capa));
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_MCAST_RATE] &&
	    !nl80211_parse_mcast_rate(rdev, ibss.mcast_rate,
			nla_get_u32(info->attrs[NL80211_ATTR_MCAST_RATE])))
		वापस -EINVAL;

	अगर (ibss.privacy && info->attrs[NL80211_ATTR_KEYS]) अणु
		bool no_ht = false;

		connkeys = nl80211_parse_connkeys(rdev, info, &no_ht);
		अगर (IS_ERR(connkeys))
			वापस PTR_ERR(connkeys);

		अगर ((ibss.chandef.width != NL80211_CHAN_WIDTH_20_NOHT) &&
		    no_ht) अणु
			kमुक्त_sensitive(connkeys);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	ibss.control_port =
		nla_get_flag(info->attrs[NL80211_ATTR_CONTROL_PORT]);

	अगर (info->attrs[NL80211_ATTR_CONTROL_PORT_OVER_NL80211]) अणु
		पूर्णांक r = validate_pae_over_nl80211(rdev, info);

		अगर (r < 0) अणु
			kमुक्त_sensitive(connkeys);
			वापस r;
		पूर्ण

		ibss.control_port_over_nl80211 = true;
	पूर्ण

	ibss.userspace_handles_dfs =
		nla_get_flag(info->attrs[NL80211_ATTR_HANDLE_DFS]);

	wdev_lock(dev->ieee80211_ptr);
	err = __cfg80211_join_ibss(rdev, dev, &ibss, connkeys);
	अगर (err)
		kमुक्त_sensitive(connkeys);
	अन्यथा अगर (info->attrs[NL80211_ATTR_SOCKET_OWNER])
		dev->ieee80211_ptr->conn_owner_nlportid = info->snd_portid;
	wdev_unlock(dev->ieee80211_ptr);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_leave_ibss(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];

	अगर (!rdev->ops->leave_ibss)
		वापस -EOPNOTSUPP;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_ADHOC)
		वापस -EOPNOTSUPP;

	वापस cfg80211_leave_ibss(rdev, dev, false);
पूर्ण

अटल पूर्णांक nl80211_set_mcast_rate(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	पूर्णांक mcast_rate[NUM_NL80211_BANDS];
	u32 nla_rate;
	पूर्णांक err;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_ADHOC &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_MESH_POINT &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_OCB)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->set_mcast_rate)
		वापस -EOPNOTSUPP;

	स_रखो(mcast_rate, 0, माप(mcast_rate));

	अगर (!info->attrs[NL80211_ATTR_MCAST_RATE])
		वापस -EINVAL;

	nla_rate = nla_get_u32(info->attrs[NL80211_ATTR_MCAST_RATE]);
	अगर (!nl80211_parse_mcast_rate(rdev, mcast_rate, nla_rate))
		वापस -EINVAL;

	err = rdev_set_mcast_rate(rdev, dev, mcast_rate);

	वापस err;
पूर्ण

अटल काष्ठा sk_buff *
__cfg80211_alloc_venकरोr_skb(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			    काष्ठा wireless_dev *wdev, पूर्णांक approxlen,
			    u32 portid, u32 seq, क्रमागत nl80211_commands cmd,
			    क्रमागत nl80211_attrs attr,
			    स्थिर काष्ठा nl80211_venकरोr_cmd_info *info,
			    gfp_t gfp)
अणु
	काष्ठा sk_buff *skb;
	व्योम *hdr;
	काष्ठा nlattr *data;

	skb = nlmsg_new(approxlen + 100, gfp);
	अगर (!skb)
		वापस शून्य;

	hdr = nl80211hdr_put(skb, portid, seq, 0, cmd);
	अगर (!hdr) अणु
		kमुक्त_skb(skb);
		वापस शून्य;
	पूर्ण

	अगर (nla_put_u32(skb, NL80211_ATTR_WIPHY, rdev->wiphy_idx))
		जाओ nla_put_failure;

	अगर (info) अणु
		अगर (nla_put_u32(skb, NL80211_ATTR_VENDOR_ID,
				info->venकरोr_id))
			जाओ nla_put_failure;
		अगर (nla_put_u32(skb, NL80211_ATTR_VENDOR_SUBCMD,
				info->subcmd))
			जाओ nla_put_failure;
	पूर्ण

	अगर (wdev) अणु
		अगर (nla_put_u64_64bit(skb, NL80211_ATTR_WDEV,
				      wdev_id(wdev), NL80211_ATTR_PAD))
			जाओ nla_put_failure;
		अगर (wdev->netdev &&
		    nla_put_u32(skb, NL80211_ATTR_IFINDEX,
				wdev->netdev->अगरindex))
			जाओ nla_put_failure;
	पूर्ण

	data = nla_nest_start_noflag(skb, attr);
	अगर (!data)
		जाओ nla_put_failure;

	((व्योम **)skb->cb)[0] = rdev;
	((व्योम **)skb->cb)[1] = hdr;
	((व्योम **)skb->cb)[2] = data;

	वापस skb;

 nla_put_failure:
	kमुक्त_skb(skb);
	वापस शून्य;
पूर्ण

काष्ठा sk_buff *__cfg80211_alloc_event_skb(काष्ठा wiphy *wiphy,
					   काष्ठा wireless_dev *wdev,
					   क्रमागत nl80211_commands cmd,
					   क्रमागत nl80211_attrs attr,
					   अचिन्हित पूर्णांक portid,
					   पूर्णांक venकरोr_event_idx,
					   पूर्णांक approxlen, gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	स्थिर काष्ठा nl80211_venकरोr_cmd_info *info;

	चयन (cmd) अणु
	हाल NL80211_CMD_TESTMODE:
		अगर (WARN_ON(venकरोr_event_idx != -1))
			वापस शून्य;
		info = शून्य;
		अवरोध;
	हाल NL80211_CMD_VENDOR:
		अगर (WARN_ON(venकरोr_event_idx < 0 ||
			    venकरोr_event_idx >= wiphy->n_venकरोr_events))
			वापस शून्य;
		info = &wiphy->venकरोr_events[venकरोr_event_idx];
		अवरोध;
	शेष:
		WARN_ON(1);
		वापस शून्य;
	पूर्ण

	वापस __cfg80211_alloc_venकरोr_skb(rdev, wdev, approxlen, portid, 0,
					   cmd, attr, info, gfp);
पूर्ण
EXPORT_SYMBOL(__cfg80211_alloc_event_skb);

व्योम __cfg80211_send_event_skb(काष्ठा sk_buff *skb, gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = ((व्योम **)skb->cb)[0];
	व्योम *hdr = ((व्योम **)skb->cb)[1];
	काष्ठा nlmsghdr *nlhdr = nlmsg_hdr(skb);
	काष्ठा nlattr *data = ((व्योम **)skb->cb)[2];
	क्रमागत nl80211_multicast_groups mcgrp = NL80211_MCGRP_TESTMODE;

	/* clear CB data क्रम netlink core to own from now on */
	स_रखो(skb->cb, 0, माप(skb->cb));

	nla_nest_end(skb, data);
	genlmsg_end(skb, hdr);

	अगर (nlhdr->nlmsg_pid) अणु
		genlmsg_unicast(wiphy_net(&rdev->wiphy), skb,
				nlhdr->nlmsg_pid);
	पूर्ण अन्यथा अणु
		अगर (data->nla_type == NL80211_ATTR_VENDOR_DATA)
			mcgrp = NL80211_MCGRP_VENDOR;

		genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy),
					skb, 0, mcgrp, gfp);
	पूर्ण
पूर्ण
EXPORT_SYMBOL(__cfg80211_send_event_skb);

#अगर_घोषित CONFIG_NL80211_TESTMODE
अटल पूर्णांक nl80211_tesपंचांगode_करो(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev;
	पूर्णांक err;

	lockdep_निश्चित_held(&rdev->wiphy.mtx);

	wdev = __cfg80211_wdev_from_attrs(rdev, genl_info_net(info),
					  info->attrs);

	अगर (!rdev->ops->tesपंचांगode_cmd)
		वापस -EOPNOTSUPP;

	अगर (IS_ERR(wdev)) अणु
		err = PTR_ERR(wdev);
		अगर (err != -EINVAL)
			वापस err;
		wdev = शून्य;
	पूर्ण अन्यथा अगर (wdev->wiphy != &rdev->wiphy) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (!info->attrs[NL80211_ATTR_TESTDATA])
		वापस -EINVAL;

	rdev->cur_cmd_info = info;
	err = rdev_tesपंचांगode_cmd(rdev, wdev,
				nla_data(info->attrs[NL80211_ATTR_TESTDATA]),
				nla_len(info->attrs[NL80211_ATTR_TESTDATA]));
	rdev->cur_cmd_info = शून्य;

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_tesपंचांगode_dump(काष्ठा sk_buff *skb,
				 काष्ठा netlink_callback *cb)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा nlattr **attrbuf = शून्य;
	पूर्णांक err;
	दीर्घ phy_idx;
	व्योम *data = शून्य;
	पूर्णांक data_len = 0;

	rtnl_lock();

	अगर (cb->args[0]) अणु
		/*
		 * 0 is a valid index, but not valid क्रम args[0],
		 * so we need to offset by 1.
		 */
		phy_idx = cb->args[0] - 1;

		rdev = cfg80211_rdev_by_wiphy_idx(phy_idx);
		अगर (!rdev) अणु
			err = -ENOENT;
			जाओ out_err;
		पूर्ण
	पूर्ण अन्यथा अणु
		attrbuf = kसुस्मृति(NUM_NL80211_ATTR, माप(*attrbuf),
				  GFP_KERNEL);
		अगर (!attrbuf) अणु
			err = -ENOMEM;
			जाओ out_err;
		पूर्ण

		err = nlmsg_parse_deprecated(cb->nlh,
					     GENL_HDRLEN + nl80211_fam.hdrsize,
					     attrbuf, nl80211_fam.maxattr,
					     nl80211_policy, शून्य);
		अगर (err)
			जाओ out_err;

		rdev = __cfg80211_rdev_from_attrs(sock_net(skb->sk), attrbuf);
		अगर (IS_ERR(rdev)) अणु
			err = PTR_ERR(rdev);
			जाओ out_err;
		पूर्ण
		phy_idx = rdev->wiphy_idx;

		अगर (attrbuf[NL80211_ATTR_TESTDATA])
			cb->args[1] = (दीर्घ)attrbuf[NL80211_ATTR_TESTDATA];
	पूर्ण

	अगर (cb->args[1]) अणु
		data = nla_data((व्योम *)cb->args[1]);
		data_len = nla_len((व्योम *)cb->args[1]);
	पूर्ण

	अगर (!rdev->ops->tesपंचांगode_dump) अणु
		err = -EOPNOTSUPP;
		जाओ out_err;
	पूर्ण

	जबतक (1) अणु
		व्योम *hdr = nl80211hdr_put(skb, NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
					   NL80211_CMD_TESTMODE);
		काष्ठा nlattr *पंचांगdata;

		अगर (!hdr)
			अवरोध;

		अगर (nla_put_u32(skb, NL80211_ATTR_WIPHY, phy_idx)) अणु
			genlmsg_cancel(skb, hdr);
			अवरोध;
		पूर्ण

		पंचांगdata = nla_nest_start_noflag(skb, NL80211_ATTR_TESTDATA);
		अगर (!पंचांगdata) अणु
			genlmsg_cancel(skb, hdr);
			अवरोध;
		पूर्ण
		err = rdev_tesपंचांगode_dump(rdev, skb, cb, data, data_len);
		nla_nest_end(skb, पंचांगdata);

		अगर (err == -ENOBUFS || err == -ENOENT) अणु
			genlmsg_cancel(skb, hdr);
			अवरोध;
		पूर्ण अन्यथा अगर (err) अणु
			genlmsg_cancel(skb, hdr);
			जाओ out_err;
		पूर्ण

		genlmsg_end(skb, hdr);
	पूर्ण

	err = skb->len;
	/* see above */
	cb->args[0] = phy_idx + 1;
 out_err:
	kमुक्त(attrbuf);
	rtnl_unlock();
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nl80211_connect(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा cfg80211_connect_params connect;
	काष्ठा wiphy *wiphy;
	काष्ठा cfg80211_cached_keys *connkeys = शून्य;
	u32 freq = 0;
	पूर्णांक err;

	स_रखो(&connect, 0, माप(connect));

	अगर (!info->attrs[NL80211_ATTR_SSID] ||
	    !nla_len(info->attrs[NL80211_ATTR_SSID]))
		वापस -EINVAL;

	अगर (info->attrs[NL80211_ATTR_AUTH_TYPE]) अणु
		connect.auth_type =
			nla_get_u32(info->attrs[NL80211_ATTR_AUTH_TYPE]);
		अगर (!nl80211_valid_auth_type(rdev, connect.auth_type,
					     NL80211_CMD_CONNECT))
			वापस -EINVAL;
	पूर्ण अन्यथा
		connect.auth_type = NL80211_AUTHTYPE_AUTOMATIC;

	connect.privacy = info->attrs[NL80211_ATTR_PRIVACY];

	अगर (info->attrs[NL80211_ATTR_WANT_1X_4WAY_HS] &&
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X))
		वापस -EINVAL;
	connect.want_1x = info->attrs[NL80211_ATTR_WANT_1X_4WAY_HS];

	err = nl80211_crypto_settings(rdev, info, &connect.crypto,
				      NL80211_MAX_NR_CIPHER_SUITES);
	अगर (err)
		वापस err;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	wiphy = &rdev->wiphy;

	connect.bg_scan_period = -1;
	अगर (info->attrs[NL80211_ATTR_BG_SCAN_PERIOD] &&
		(wiphy->flags & WIPHY_FLAG_SUPPORTS_FW_ROAM)) अणु
		connect.bg_scan_period =
			nla_get_u16(info->attrs[NL80211_ATTR_BG_SCAN_PERIOD]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_MAC])
		connect.bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);
	अन्यथा अगर (info->attrs[NL80211_ATTR_MAC_HINT])
		connect.bssid_hपूर्णांक =
			nla_data(info->attrs[NL80211_ATTR_MAC_HINT]);
	connect.ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
	connect.ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		connect.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		connect.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_USE_MFP]) अणु
		connect.mfp = nla_get_u32(info->attrs[NL80211_ATTR_USE_MFP]);
		अगर (connect.mfp == NL80211_MFP_OPTIONAL &&
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_MFP_OPTIONAL))
			वापस -EOPNOTSUPP;
	पूर्ण अन्यथा अणु
		connect.mfp = NL80211_MFP_NO;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_PREV_BSSID])
		connect.prev_bssid =
			nla_data(info->attrs[NL80211_ATTR_PREV_BSSID]);

	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ])
		freq = MHZ_TO_KHZ(nla_get_u32(
					info->attrs[NL80211_ATTR_WIPHY_FREQ]));
	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ_OFFSET])
		freq +=
		    nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ_OFFSET]);

	अगर (freq) अणु
		connect.channel = nl80211_get_valid_chan(wiphy, freq);
		अगर (!connect.channel)
			वापस -EINVAL;
	पूर्ण अन्यथा अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ_HINT]) अणु
		freq = nla_get_u32(info->attrs[NL80211_ATTR_WIPHY_FREQ_HINT]);
		freq = MHZ_TO_KHZ(freq);
		connect.channel_hपूर्णांक = nl80211_get_valid_chan(wiphy, freq);
		अगर (!connect.channel_hपूर्णांक)
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_WIPHY_EDMG_CHANNELS]) अणु
		connect.edmg.channels =
		      nla_get_u8(info->attrs[NL80211_ATTR_WIPHY_EDMG_CHANNELS]);

		अगर (info->attrs[NL80211_ATTR_WIPHY_EDMG_BW_CONFIG])
			connect.edmg.bw_config =
				nla_get_u8(info->attrs[NL80211_ATTR_WIPHY_EDMG_BW_CONFIG]);
	पूर्ण

	अगर (connect.privacy && info->attrs[NL80211_ATTR_KEYS]) अणु
		connkeys = nl80211_parse_connkeys(rdev, info, शून्य);
		अगर (IS_ERR(connkeys))
			वापस PTR_ERR(connkeys);
	पूर्ण

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_DISABLE_HT]))
		connect.flags |= ASSOC_REQ_DISABLE_HT;

	अगर (info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK])
		स_नकल(&connect.ht_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK]),
		       माप(connect.ht_capa_mask));

	अगर (info->attrs[NL80211_ATTR_HT_CAPABILITY]) अणु
		अगर (!info->attrs[NL80211_ATTR_HT_CAPABILITY_MASK]) अणु
			kमुक्त_sensitive(connkeys);
			वापस -EINVAL;
		पूर्ण
		स_नकल(&connect.ht_capa,
		       nla_data(info->attrs[NL80211_ATTR_HT_CAPABILITY]),
		       माप(connect.ht_capa));
	पूर्ण

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_DISABLE_VHT]))
		connect.flags |= ASSOC_REQ_DISABLE_VHT;

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_DISABLE_HE]))
		connect.flags |= ASSOC_REQ_DISABLE_HE;

	अगर (info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK])
		स_नकल(&connect.vht_capa_mask,
		       nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK]),
		       माप(connect.vht_capa_mask));

	अगर (info->attrs[NL80211_ATTR_VHT_CAPABILITY]) अणु
		अगर (!info->attrs[NL80211_ATTR_VHT_CAPABILITY_MASK]) अणु
			kमुक्त_sensitive(connkeys);
			वापस -EINVAL;
		पूर्ण
		स_नकल(&connect.vht_capa,
		       nla_data(info->attrs[NL80211_ATTR_VHT_CAPABILITY]),
		       माप(connect.vht_capa));
	पूर्ण

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_USE_RRM])) अणु
		अगर (!((rdev->wiphy.features &
			NL80211_FEATURE_DS_PARAM_SET_IE_IN_PROBES) &&
		       (rdev->wiphy.features & NL80211_FEATURE_QUIET)) &&
		    !wiphy_ext_feature_isset(&rdev->wiphy,
					     NL80211_EXT_FEATURE_RRM)) अणु
			kमुक्त_sensitive(connkeys);
			वापस -EINVAL;
		पूर्ण
		connect.flags |= ASSOC_REQ_USE_RRM;
	पूर्ण

	connect.pbss = nla_get_flag(info->attrs[NL80211_ATTR_PBSS]);
	अगर (connect.pbss && !rdev->wiphy.bands[NL80211_BAND_60GHZ]) अणु
		kमुक्त_sensitive(connkeys);
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_BSS_SELECT]) अणु
		/* bss selection makes no sense अगर bssid is set */
		अगर (connect.bssid) अणु
			kमुक्त_sensitive(connkeys);
			वापस -EINVAL;
		पूर्ण

		err = parse_bss_select(info->attrs[NL80211_ATTR_BSS_SELECT],
				       wiphy, &connect.bss_select);
		अगर (err) अणु
			kमुक्त_sensitive(connkeys);
			वापस err;
		पूर्ण
	पूर्ण

	अगर (wiphy_ext_feature_isset(&rdev->wiphy,
				    NL80211_EXT_FEATURE_FILS_SK_OFFLOAD) &&
	    info->attrs[NL80211_ATTR_FILS_ERP_USERNAME] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_REALM] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_RRK]) अणु
		connect.fils_erp_username =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_USERNAME]);
		connect.fils_erp_username_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_USERNAME]);
		connect.fils_erp_realm =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_REALM]);
		connect.fils_erp_realm_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_REALM]);
		connect.fils_erp_next_seq_num =
			nla_get_u16(
			   info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM]);
		connect.fils_erp_rrk =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_RRK]);
		connect.fils_erp_rrk_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_RRK]);
	पूर्ण अन्यथा अगर (info->attrs[NL80211_ATTR_FILS_ERP_USERNAME] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_REALM] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_RRK]) अणु
		kमुक्त_sensitive(connkeys);
		वापस -EINVAL;
	पूर्ण

	अगर (nla_get_flag(info->attrs[NL80211_ATTR_EXTERNAL_AUTH_SUPPORT])) अणु
		अगर (!info->attrs[NL80211_ATTR_SOCKET_OWNER]) अणु
			kमुक्त_sensitive(connkeys);
			GENL_SET_ERR_MSG(info,
					 "external auth requires connection ownership");
			वापस -EINVAL;
		पूर्ण
		connect.flags |= CONNECT_REQ_EXTERNAL_AUTH_SUPPORT;
	पूर्ण

	wdev_lock(dev->ieee80211_ptr);

	err = cfg80211_connect(rdev, dev, &connect, connkeys,
			       connect.prev_bssid);
	अगर (err)
		kमुक्त_sensitive(connkeys);

	अगर (!err && info->attrs[NL80211_ATTR_SOCKET_OWNER]) अणु
		dev->ieee80211_ptr->conn_owner_nlportid = info->snd_portid;
		अगर (connect.bssid)
			स_नकल(dev->ieee80211_ptr->disconnect_bssid,
			       connect.bssid, ETH_ALEN);
		अन्यथा
			eth_zero_addr(dev->ieee80211_ptr->disconnect_bssid);
	पूर्ण

	wdev_unlock(dev->ieee80211_ptr);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_update_connect_params(काष्ठा sk_buff *skb,
					 काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_connect_params connect = अणुपूर्ण;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	bool fils_sk_offload;
	u32 auth_type;
	u32 changed = 0;
	पूर्णांक ret;

	अगर (!rdev->ops->update_connect_params)
		वापस -EOPNOTSUPP;

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		connect.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		connect.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
		changed |= UPDATE_ASSOC_IES;
	पूर्ण

	fils_sk_offload = wiphy_ext_feature_isset(&rdev->wiphy,
						  NL80211_EXT_FEATURE_FILS_SK_OFFLOAD);

	/*
	 * when driver supports fils-sk offload all attributes must be
	 * provided. So the अन्यथा covers "fils-sk-not-all" and
	 * "no-fils-sk-any".
	 */
	अगर (fils_sk_offload &&
	    info->attrs[NL80211_ATTR_FILS_ERP_USERNAME] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_REALM] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] &&
	    info->attrs[NL80211_ATTR_FILS_ERP_RRK]) अणु
		connect.fils_erp_username =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_USERNAME]);
		connect.fils_erp_username_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_USERNAME]);
		connect.fils_erp_realm =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_REALM]);
		connect.fils_erp_realm_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_REALM]);
		connect.fils_erp_next_seq_num =
			nla_get_u16(
			   info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM]);
		connect.fils_erp_rrk =
			nla_data(info->attrs[NL80211_ATTR_FILS_ERP_RRK]);
		connect.fils_erp_rrk_len =
			nla_len(info->attrs[NL80211_ATTR_FILS_ERP_RRK]);
		changed |= UPDATE_FILS_ERP_INFO;
	पूर्ण अन्यथा अगर (info->attrs[NL80211_ATTR_FILS_ERP_USERNAME] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_REALM] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM] ||
		   info->attrs[NL80211_ATTR_FILS_ERP_RRK]) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_AUTH_TYPE]) अणु
		auth_type = nla_get_u32(info->attrs[NL80211_ATTR_AUTH_TYPE]);
		अगर (!nl80211_valid_auth_type(rdev, auth_type,
					     NL80211_CMD_CONNECT))
			वापस -EINVAL;

		अगर (auth_type == NL80211_AUTHTYPE_FILS_SK &&
		    fils_sk_offload && !(changed & UPDATE_FILS_ERP_INFO))
			वापस -EINVAL;

		connect.auth_type = auth_type;
		changed |= UPDATE_AUTH_TYPE;
	पूर्ण

	wdev_lock(dev->ieee80211_ptr);
	अगर (!wdev->current_bss)
		ret = -ENOLINK;
	अन्यथा
		ret = rdev_update_connect_params(rdev, dev, &connect, changed);
	wdev_unlock(dev->ieee80211_ptr);

	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_disconnect(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	u16 reason;
	पूर्णांक ret;

	अगर (dev->ieee80211_ptr->conn_owner_nlportid &&
	    dev->ieee80211_ptr->conn_owner_nlportid != info->snd_portid)
		वापस -EPERM;

	अगर (!info->attrs[NL80211_ATTR_REASON_CODE])
		reason = WLAN_REASON_DEAUTH_LEAVING;
	अन्यथा
		reason = nla_get_u16(info->attrs[NL80211_ATTR_REASON_CODE]);

	अगर (reason == 0)
		वापस -EINVAL;

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	wdev_lock(dev->ieee80211_ptr);
	ret = cfg80211_disconnect(rdev, dev, reason, true);
	wdev_unlock(dev->ieee80211_ptr);
	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_wiphy_netns(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net *net;
	पूर्णांक err;

	अगर (info->attrs[NL80211_ATTR_PID]) अणु
		u32 pid = nla_get_u32(info->attrs[NL80211_ATTR_PID]);

		net = get_net_ns_by_pid(pid);
	पूर्ण अन्यथा अगर (info->attrs[NL80211_ATTR_NETNS_FD]) अणु
		u32 fd = nla_get_u32(info->attrs[NL80211_ATTR_NETNS_FD]);

		net = get_net_ns_by_fd(fd);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण

	अगर (IS_ERR(net))
		वापस PTR_ERR(net);

	err = 0;

	/* check अगर anything to करो */
	अगर (!net_eq(wiphy_net(&rdev->wiphy), net))
		err = cfg80211_चयन_netns(rdev, net);

	put_net(net);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_setdel_pmksa(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	पूर्णांक (*rdev_ops)(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			काष्ठा cfg80211_pmksa *pmksa) = शून्य;
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा cfg80211_pmksa pmksa;

	स_रखो(&pmksa, 0, माप(काष्ठा cfg80211_pmksa));

	अगर (!info->attrs[NL80211_ATTR_PMKID])
		वापस -EINVAL;

	pmksa.pmkid = nla_data(info->attrs[NL80211_ATTR_PMKID]);

	अगर (info->attrs[NL80211_ATTR_MAC]) अणु
		pmksa.bssid = nla_data(info->attrs[NL80211_ATTR_MAC]);
	पूर्ण अन्यथा अगर (info->attrs[NL80211_ATTR_SSID] &&
		   info->attrs[NL80211_ATTR_FILS_CACHE_ID] &&
		   (info->genlhdr->cmd == NL80211_CMD_DEL_PMKSA ||
		    info->attrs[NL80211_ATTR_PMK])) अणु
		pmksa.ssid = nla_data(info->attrs[NL80211_ATTR_SSID]);
		pmksa.ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);
		pmksa.cache_id =
			nla_data(info->attrs[NL80211_ATTR_FILS_CACHE_ID]);
	पूर्ण अन्यथा अणु
		वापस -EINVAL;
	पूर्ण
	अगर (info->attrs[NL80211_ATTR_PMK]) अणु
		pmksa.pmk = nla_data(info->attrs[NL80211_ATTR_PMK]);
		pmksa.pmk_len = nla_len(info->attrs[NL80211_ATTR_PMK]);
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_PMK_LIFETIME])
		pmksa.pmk_lअगरeसमय =
			nla_get_u32(info->attrs[NL80211_ATTR_PMK_LIFETIME]);

	अगर (info->attrs[NL80211_ATTR_PMK_REAUTH_THRESHOLD])
		pmksa.pmk_reauth_threshold =
			nla_get_u8(
				info->attrs[NL80211_ATTR_PMK_REAUTH_THRESHOLD]);

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_CLIENT &&
	    !(dev->ieee80211_ptr->अगरtype == NL80211_IFTYPE_AP &&
	      wiphy_ext_feature_isset(&rdev->wiphy,
				      NL80211_EXT_FEATURE_AP_PMKSA_CACHING)))
		वापस -EOPNOTSUPP;

	चयन (info->genlhdr->cmd) अणु
	हाल NL80211_CMD_SET_PMKSA:
		rdev_ops = rdev->ops->set_pmksa;
		अवरोध;
	हाल NL80211_CMD_DEL_PMKSA:
		rdev_ops = rdev->ops->del_pmksa;
		अवरोध;
	शेष:
		WARN_ON(1);
		अवरोध;
	पूर्ण

	अगर (!rdev_ops)
		वापस -EOPNOTSUPP;

	वापस rdev_ops(&rdev->wiphy, dev, &pmksa);
पूर्ण

अटल पूर्णांक nl80211_flush_pmksa(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];

	अगर (dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_STATION &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->flush_pmksa)
		वापस -EOPNOTSUPP;

	वापस rdev_flush_pmksa(rdev, dev);
पूर्ण

अटल पूर्णांक nl80211_tdls_mgmt(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	u8 action_code, dialog_token;
	u32 peer_capability = 0;
	u16 status_code;
	u8 *peer;
	bool initiator;

	अगर (!(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_TDLS) ||
	    !rdev->ops->tdls_mgmt)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_TDLS_ACTION] ||
	    !info->attrs[NL80211_ATTR_STATUS_CODE] ||
	    !info->attrs[NL80211_ATTR_TDLS_DIALOG_TOKEN] ||
	    !info->attrs[NL80211_ATTR_IE] ||
	    !info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	peer = nla_data(info->attrs[NL80211_ATTR_MAC]);
	action_code = nla_get_u8(info->attrs[NL80211_ATTR_TDLS_ACTION]);
	status_code = nla_get_u16(info->attrs[NL80211_ATTR_STATUS_CODE]);
	dialog_token = nla_get_u8(info->attrs[NL80211_ATTR_TDLS_DIALOG_TOKEN]);
	initiator = nla_get_flag(info->attrs[NL80211_ATTR_TDLS_INITIATOR]);
	अगर (info->attrs[NL80211_ATTR_TDLS_PEER_CAPABILITY])
		peer_capability =
			nla_get_u32(info->attrs[NL80211_ATTR_TDLS_PEER_CAPABILITY]);

	वापस rdev_tdls_mgmt(rdev, dev, peer, action_code,
			      dialog_token, status_code, peer_capability,
			      initiator,
			      nla_data(info->attrs[NL80211_ATTR_IE]),
			      nla_len(info->attrs[NL80211_ATTR_IE]));
पूर्ण

अटल पूर्णांक nl80211_tdls_oper(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	क्रमागत nl80211_tdls_operation operation;
	u8 *peer;

	अगर (!(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_TDLS) ||
	    !rdev->ops->tdls_oper)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_TDLS_OPERATION] ||
	    !info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	operation = nla_get_u8(info->attrs[NL80211_ATTR_TDLS_OPERATION]);
	peer = nla_data(info->attrs[NL80211_ATTR_MAC]);

	वापस rdev_tdls_oper(rdev, dev, peer, operation);
पूर्ण

अटल पूर्णांक nl80211_reमुख्य_on_channel(काष्ठा sk_buff *skb,
				     काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	काष्ठा cfg80211_chan_def chandef;
	स्थिर काष्ठा cfg80211_chan_def *compat_chandef;
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	u64 cookie;
	u32 duration;
	पूर्णांक err;

	अगर (!info->attrs[NL80211_ATTR_WIPHY_FREQ] ||
	    !info->attrs[NL80211_ATTR_DURATION])
		वापस -EINVAL;

	duration = nla_get_u32(info->attrs[NL80211_ATTR_DURATION]);

	अगर (!rdev->ops->reमुख्य_on_channel ||
	    !(rdev->wiphy.flags & WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL))
		वापस -EOPNOTSUPP;

	/*
	 * We should be on that channel क्रम at least a minimum amount of
	 * समय (10ms) but no दीर्घer than the driver supports.
	 */
	अगर (duration < NL80211_MIN_REMAIN_ON_CHANNEL_TIME ||
	    duration > rdev->wiphy.max_reमुख्य_on_channel_duration)
		वापस -EINVAL;

	err = nl80211_parse_chandef(rdev, info, &chandef);
	अगर (err)
		वापस err;

	wdev_lock(wdev);
	अगर (!cfg80211_off_channel_oper_allowed(wdev) &&
	    !cfg80211_chandef_identical(&wdev->chandef, &chandef)) अणु
		compat_chandef = cfg80211_chandef_compatible(&wdev->chandef,
							     &chandef);
		अगर (compat_chandef != &chandef) अणु
			wdev_unlock(wdev);
			वापस -EBUSY;
		पूर्ण
	पूर्ण
	wdev_unlock(wdev);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_REMAIN_ON_CHANNEL);
	अगर (!hdr) अणु
		err = -ENOBUFS;
		जाओ मुक्त_msg;
	पूर्ण

	err = rdev_reमुख्य_on_channel(rdev, wdev, chandef.chan,
				     duration, &cookie);

	अगर (err)
		जाओ मुक्त_msg;

	अगर (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस genlmsg_reply(msg, info);

 nla_put_failure:
	err = -ENOBUFS;
 मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_cancel_reमुख्य_on_channel(काष्ठा sk_buff *skb,
					    काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	u64 cookie;

	अगर (!info->attrs[NL80211_ATTR_COOKIE])
		वापस -EINVAL;

	अगर (!rdev->ops->cancel_reमुख्य_on_channel)
		वापस -EOPNOTSUPP;

	cookie = nla_get_u64(info->attrs[NL80211_ATTR_COOKIE]);

	वापस rdev_cancel_reमुख्य_on_channel(rdev, wdev, cookie);
पूर्ण

अटल पूर्णांक nl80211_set_tx_bitrate_mask(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_bitrate_mask mask;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	पूर्णांक err;

	अगर (!rdev->ops->set_bitrate_mask)
		वापस -EOPNOTSUPP;

	err = nl80211_parse_tx_bitrate_mask(info, info->attrs,
					    NL80211_ATTR_TX_RATES, &mask,
					    dev, true);
	अगर (err)
		वापस err;

	वापस rdev_set_bitrate_mask(rdev, dev, शून्य, &mask);
पूर्ण

अटल पूर्णांक nl80211_रेजिस्टर_mgmt(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	u16 frame_type = IEEE80211_FTYPE_MGMT | IEEE80211_STYPE_ACTION;

	अगर (!info->attrs[NL80211_ATTR_FRAME_MATCH])
		वापस -EINVAL;

	अगर (info->attrs[NL80211_ATTR_FRAME_TYPE])
		frame_type = nla_get_u16(info->attrs[NL80211_ATTR_FRAME_TYPE]);

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* not much poपूर्णांक in रेजिस्टरing अगर we can't reply */
	अगर (!rdev->ops->mgmt_tx)
		वापस -EOPNOTSUPP;

	अगर (info->attrs[NL80211_ATTR_RECEIVE_MULTICAST] &&
	    !wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_MULTICAST_REGISTRATIONS)) अणु
		GENL_SET_ERR_MSG(info,
				 "multicast RX registrations are not supported");
		वापस -EOPNOTSUPP;
	पूर्ण

	वापस cfg80211_mlme_रेजिस्टर_mgmt(wdev, info->snd_portid, frame_type,
					   nla_data(info->attrs[NL80211_ATTR_FRAME_MATCH]),
					   nla_len(info->attrs[NL80211_ATTR_FRAME_MATCH]),
					   info->attrs[NL80211_ATTR_RECEIVE_MULTICAST],
					   info->extack);
पूर्ण

अटल पूर्णांक nl80211_tx_mgmt(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	काष्ठा cfg80211_chan_def chandef;
	पूर्णांक err;
	व्योम *hdr = शून्य;
	u64 cookie;
	काष्ठा sk_buff *msg = शून्य;
	काष्ठा cfg80211_mgmt_tx_params params = अणु
		.करोnt_रुको_क्रम_ack =
			info->attrs[NL80211_ATTR_DONT_WAIT_FOR_ACK],
	पूर्ण;

	अगर (!info->attrs[NL80211_ATTR_FRAME])
		वापस -EINVAL;

	अगर (!rdev->ops->mgmt_tx)
		वापस -EOPNOTSUPP;

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_P2P_DEVICE:
		अगर (!info->attrs[NL80211_ATTR_WIPHY_FREQ])
			वापस -EINVAL;
		अवरोध;
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_MESH_POINT:
	हाल NL80211_IFTYPE_P2P_GO:
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_DURATION]) अणु
		अगर (!(rdev->wiphy.flags & WIPHY_FLAG_OFFCHAN_TX))
			वापस -EINVAL;
		params.रुको = nla_get_u32(info->attrs[NL80211_ATTR_DURATION]);

		/*
		 * We should रुको on the channel क्रम at least a minimum amount
		 * of समय (10ms) but no दीर्घer than the driver supports.
		 */
		अगर (params.रुको < NL80211_MIN_REMAIN_ON_CHANNEL_TIME ||
		    params.रुको > rdev->wiphy.max_reमुख्य_on_channel_duration)
			वापस -EINVAL;
	पूर्ण

	params.offchan = info->attrs[NL80211_ATTR_OFFCHANNEL_TX_OK];

	अगर (params.offchan && !(rdev->wiphy.flags & WIPHY_FLAG_OFFCHAN_TX))
		वापस -EINVAL;

	params.no_cck = nla_get_flag(info->attrs[NL80211_ATTR_TX_NO_CCK_RATE]);

	/* get the channel अगर any has been specअगरied, otherwise pass शून्य to
	 * the driver. The latter will use the current one
	 */
	chandef.chan = शून्य;
	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ]) अणु
		err = nl80211_parse_chandef(rdev, info, &chandef);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!chandef.chan && params.offchan)
		वापस -EINVAL;

	wdev_lock(wdev);
	अगर (params.offchan && !cfg80211_off_channel_oper_allowed(wdev)) अणु
		wdev_unlock(wdev);
		वापस -EBUSY;
	पूर्ण
	wdev_unlock(wdev);

	params.buf = nla_data(info->attrs[NL80211_ATTR_FRAME]);
	params.len = nla_len(info->attrs[NL80211_ATTR_FRAME]);

	अगर (info->attrs[NL80211_ATTR_CSA_C_OFFSETS_TX]) अणु
		पूर्णांक len = nla_len(info->attrs[NL80211_ATTR_CSA_C_OFFSETS_TX]);
		पूर्णांक i;

		अगर (len % माप(u16))
			वापस -EINVAL;

		params.n_csa_offsets = len / माप(u16);
		params.csa_offsets =
			nla_data(info->attrs[NL80211_ATTR_CSA_C_OFFSETS_TX]);

		/* check that all the offsets fit the frame */
		क्रम (i = 0; i < params.n_csa_offsets; i++) अणु
			अगर (params.csa_offsets[i] >= params.len)
				वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!params.करोnt_रुको_क्रम_ack) अणु
		msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
		अगर (!msg)
			वापस -ENOMEM;

		hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
				     NL80211_CMD_FRAME);
		अगर (!hdr) अणु
			err = -ENOBUFS;
			जाओ मुक्त_msg;
		पूर्ण
	पूर्ण

	params.chan = chandef.chan;
	err = cfg80211_mlme_mgmt_tx(rdev, wdev, &params, &cookie);
	अगर (err)
		जाओ मुक्त_msg;

	अगर (msg) अणु
		अगर (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
				      NL80211_ATTR_PAD))
			जाओ nla_put_failure;

		genlmsg_end(msg, hdr);
		वापस genlmsg_reply(msg, info);
	पूर्ण

	वापस 0;

 nla_put_failure:
	err = -ENOBUFS;
 मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_tx_mgmt_cancel_रुको(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	u64 cookie;

	अगर (!info->attrs[NL80211_ATTR_COOKIE])
		वापस -EINVAL;

	अगर (!rdev->ops->mgmt_tx_cancel_रुको)
		वापस -EOPNOTSUPP;

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_AP_VLAN:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_P2P_DEVICE:
		अवरोध;
	हाल NL80211_IFTYPE_न_अंक:
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	cookie = nla_get_u64(info->attrs[NL80211_ATTR_COOKIE]);

	वापस rdev_mgmt_tx_cancel_रुको(rdev, wdev, cookie);
पूर्ण

अटल पूर्णांक nl80211_set_घातer_save(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev;
	काष्ठा net_device *dev = info->user_ptr[1];
	u8 ps_state;
	bool state;
	पूर्णांक err;

	अगर (!info->attrs[NL80211_ATTR_PS_STATE])
		वापस -EINVAL;

	ps_state = nla_get_u32(info->attrs[NL80211_ATTR_PS_STATE]);

	wdev = dev->ieee80211_ptr;

	अगर (!rdev->ops->set_घातer_mgmt)
		वापस -EOPNOTSUPP;

	state = (ps_state == NL80211_PS_ENABLED) ? true : false;

	अगर (state == wdev->ps)
		वापस 0;

	err = rdev_set_घातer_mgmt(rdev, dev, state, wdev->ps_समयout);
	अगर (!err)
		wdev->ps = state;
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_get_घातer_save(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	क्रमागत nl80211_ps_state ps_state;
	काष्ठा wireless_dev *wdev;
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	पूर्णांक err;

	wdev = dev->ieee80211_ptr;

	अगर (!rdev->ops->set_घातer_mgmt)
		वापस -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_POWER_SAVE);
	अगर (!hdr) अणु
		err = -ENOBUFS;
		जाओ मुक्त_msg;
	पूर्ण

	अगर (wdev->ps)
		ps_state = NL80211_PS_ENABLED;
	अन्यथा
		ps_state = NL80211_PS_DISABLED;

	अगर (nla_put_u32(msg, NL80211_ATTR_PS_STATE, ps_state))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

 nla_put_failure:
	err = -ENOBUFS;
 मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा nla_policy
nl80211_attr_cqm_policy[NL80211_ATTR_CQM_MAX + 1] = अणु
	[NL80211_ATTR_CQM_RSSI_THOLD] = अणु .type = NLA_BINARY पूर्ण,
	[NL80211_ATTR_CQM_RSSI_HYST] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_CQM_RSSI_THRESHOLD_EVENT] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_CQM_TXE_RATE] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_CQM_TXE_PKTS] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_CQM_TXE_INTVL] = अणु .type = NLA_U32 पूर्ण,
	[NL80211_ATTR_CQM_RSSI_LEVEL] = अणु .type = NLA_S32 पूर्ण,
पूर्ण;

अटल पूर्णांक nl80211_set_cqm_txe(काष्ठा genl_info *info,
			       u32 rate, u32 pkts, u32 पूर्णांकvl)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	अगर (rate > 100 || पूर्णांकvl > NL80211_CQM_TXE_MAX_INTVL)
		वापस -EINVAL;

	अगर (!rdev->ops->set_cqm_txe_config)
		वापस -EOPNOTSUPP;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION &&
	    wdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	वापस rdev_set_cqm_txe_config(rdev, dev, rate, pkts, पूर्णांकvl);
पूर्ण

अटल पूर्णांक cfg80211_cqm_rssi_update(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा net_device *dev)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	s32 last, low, high;
	u32 hyst;
	पूर्णांक i, n, low_index;
	पूर्णांक err;

	/* RSSI reporting disabled? */
	अगर (!wdev->cqm_config)
		वापस rdev_set_cqm_rssi_range_config(rdev, dev, 0, 0);

	/*
	 * Obtain current RSSI value अगर possible, अगर not and no RSSI threshold
	 * event has been received yet, we should receive an event after a
	 * connection is established and enough beacons received to calculate
	 * the average.
	 */
	अगर (!wdev->cqm_config->last_rssi_event_value && wdev->current_bss &&
	    rdev->ops->get_station) अणु
		काष्ठा station_info sinfo = अणुपूर्ण;
		u8 *mac_addr;

		mac_addr = wdev->current_bss->pub.bssid;

		err = rdev_get_station(rdev, dev, mac_addr, &sinfo);
		अगर (err)
			वापस err;

		cfg80211_sinfo_release_content(&sinfo);
		अगर (sinfo.filled & BIT_ULL(NL80211_STA_INFO_BEACON_SIGNAL_AVG))
			wdev->cqm_config->last_rssi_event_value =
				(s8) sinfo.rx_beacon_संकेत_avg;
	पूर्ण

	last = wdev->cqm_config->last_rssi_event_value;
	hyst = wdev->cqm_config->rssi_hyst;
	n = wdev->cqm_config->n_rssi_thresholds;

	क्रम (i = 0; i < n; i++) अणु
		i = array_index_nospec(i, n);
		अगर (last < wdev->cqm_config->rssi_thresholds[i])
			अवरोध;
	पूर्ण

	low_index = i - 1;
	अगर (low_index >= 0) अणु
		low_index = array_index_nospec(low_index, n);
		low = wdev->cqm_config->rssi_thresholds[low_index] - hyst;
	पूर्ण अन्यथा अणु
		low = S32_MIN;
	पूर्ण
	अगर (i < n) अणु
		i = array_index_nospec(i, n);
		high = wdev->cqm_config->rssi_thresholds[i] + hyst - 1;
	पूर्ण अन्यथा अणु
		high = S32_MAX;
	पूर्ण

	वापस rdev_set_cqm_rssi_range_config(rdev, dev, low, high);
पूर्ण

अटल पूर्णांक nl80211_set_cqm_rssi(काष्ठा genl_info *info,
				स्थिर s32 *thresholds, पूर्णांक n_thresholds,
				u32 hysteresis)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	पूर्णांक i, err;
	s32 prev = S32_MIN;

	/* Check all values negative and sorted */
	क्रम (i = 0; i < n_thresholds; i++) अणु
		अगर (thresholds[i] > 0 || thresholds[i] <= prev)
			वापस -EINVAL;

		prev = thresholds[i];
	पूर्ण

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION &&
	    wdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	wdev_lock(wdev);
	cfg80211_cqm_config_मुक्त(wdev);
	wdev_unlock(wdev);

	अगर (n_thresholds <= 1 && rdev->ops->set_cqm_rssi_config) अणु
		अगर (n_thresholds == 0 || thresholds[0] == 0) /* Disabling */
			वापस rdev_set_cqm_rssi_config(rdev, dev, 0, 0);

		वापस rdev_set_cqm_rssi_config(rdev, dev,
						thresholds[0], hysteresis);
	पूर्ण

	अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_CQM_RSSI_LIST))
		वापस -EOPNOTSUPP;

	अगर (n_thresholds == 1 && thresholds[0] == 0) /* Disabling */
		n_thresholds = 0;

	wdev_lock(wdev);
	अगर (n_thresholds) अणु
		काष्ठा cfg80211_cqm_config *cqm_config;

		cqm_config = kzalloc(माप(काष्ठा cfg80211_cqm_config) +
				     n_thresholds * माप(s32), GFP_KERNEL);
		अगर (!cqm_config) अणु
			err = -ENOMEM;
			जाओ unlock;
		पूर्ण

		cqm_config->rssi_hyst = hysteresis;
		cqm_config->n_rssi_thresholds = n_thresholds;
		स_नकल(cqm_config->rssi_thresholds, thresholds,
		       n_thresholds * माप(s32));

		wdev->cqm_config = cqm_config;
	पूर्ण

	err = cfg80211_cqm_rssi_update(rdev, dev);

unlock:
	wdev_unlock(wdev);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_set_cqm(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा nlattr *attrs[NL80211_ATTR_CQM_MAX + 1];
	काष्ठा nlattr *cqm;
	पूर्णांक err;

	cqm = info->attrs[NL80211_ATTR_CQM];
	अगर (!cqm)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(attrs, NL80211_ATTR_CQM_MAX, cqm,
					  nl80211_attr_cqm_policy,
					  info->extack);
	अगर (err)
		वापस err;

	अगर (attrs[NL80211_ATTR_CQM_RSSI_THOLD] &&
	    attrs[NL80211_ATTR_CQM_RSSI_HYST]) अणु
		स्थिर s32 *thresholds =
			nla_data(attrs[NL80211_ATTR_CQM_RSSI_THOLD]);
		पूर्णांक len = nla_len(attrs[NL80211_ATTR_CQM_RSSI_THOLD]);
		u32 hysteresis = nla_get_u32(attrs[NL80211_ATTR_CQM_RSSI_HYST]);

		अगर (len % 4)
			वापस -EINVAL;

		वापस nl80211_set_cqm_rssi(info, thresholds, len / 4,
					    hysteresis);
	पूर्ण

	अगर (attrs[NL80211_ATTR_CQM_TXE_RATE] &&
	    attrs[NL80211_ATTR_CQM_TXE_PKTS] &&
	    attrs[NL80211_ATTR_CQM_TXE_INTVL]) अणु
		u32 rate = nla_get_u32(attrs[NL80211_ATTR_CQM_TXE_RATE]);
		u32 pkts = nla_get_u32(attrs[NL80211_ATTR_CQM_TXE_PKTS]);
		u32 पूर्णांकvl = nla_get_u32(attrs[NL80211_ATTR_CQM_TXE_INTVL]);

		वापस nl80211_set_cqm_txe(info, rate, pkts, पूर्णांकvl);
	पूर्ण

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक nl80211_join_ocb(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा ocb_setup setup = अणुपूर्ण;
	पूर्णांक err;

	err = nl80211_parse_chandef(rdev, info, &setup.chandef);
	अगर (err)
		वापस err;

	वापस cfg80211_join_ocb(rdev, dev, &setup);
पूर्ण

अटल पूर्णांक nl80211_leave_ocb(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];

	वापस cfg80211_leave_ocb(rdev, dev);
पूर्ण

अटल पूर्णांक nl80211_join_mesh(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा mesh_config cfg;
	काष्ठा mesh_setup setup;
	पूर्णांक err;

	/* start with शेष */
	स_नकल(&cfg, &शेष_mesh_config, माप(cfg));
	स_नकल(&setup, &शेष_mesh_setup, माप(setup));

	अगर (info->attrs[NL80211_ATTR_MESH_CONFIG]) अणु
		/* and parse parameters अगर given */
		err = nl80211_parse_mesh_config(info, &cfg, शून्य);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (!info->attrs[NL80211_ATTR_MESH_ID] ||
	    !nla_len(info->attrs[NL80211_ATTR_MESH_ID]))
		वापस -EINVAL;

	setup.mesh_id = nla_data(info->attrs[NL80211_ATTR_MESH_ID]);
	setup.mesh_id_len = nla_len(info->attrs[NL80211_ATTR_MESH_ID]);

	अगर (info->attrs[NL80211_ATTR_MCAST_RATE] &&
	    !nl80211_parse_mcast_rate(rdev, setup.mcast_rate,
			    nla_get_u32(info->attrs[NL80211_ATTR_MCAST_RATE])))
			वापस -EINVAL;

	अगर (info->attrs[NL80211_ATTR_BEACON_INTERVAL]) अणु
		setup.beacon_पूर्णांकerval =
			nla_get_u32(info->attrs[NL80211_ATTR_BEACON_INTERVAL]);

		err = cfg80211_validate_beacon_पूर्णांक(rdev,
						   NL80211_IFTYPE_MESH_POINT,
						   setup.beacon_पूर्णांकerval);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_DTIM_PERIOD]) अणु
		setup.dtim_period =
			nla_get_u32(info->attrs[NL80211_ATTR_DTIM_PERIOD]);
		अगर (setup.dtim_period < 1 || setup.dtim_period > 100)
			वापस -EINVAL;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_MESH_SETUP]) अणु
		/* parse additional setup parameters अगर given */
		err = nl80211_parse_mesh_setup(info, &setup);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (setup.user_mpm)
		cfg.स्वतः_खोलो_plinks = false;

	अगर (info->attrs[NL80211_ATTR_WIPHY_FREQ]) अणु
		err = nl80211_parse_chandef(rdev, info, &setup.chandef);
		अगर (err)
			वापस err;
	पूर्ण अन्यथा अणु
		/* __cfg80211_join_mesh() will sort it out */
		setup.chandef.chan = शून्य;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_BSS_BASIC_RATES]) अणु
		u8 *rates = nla_data(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		पूर्णांक n_rates =
			nla_len(info->attrs[NL80211_ATTR_BSS_BASIC_RATES]);
		काष्ठा ieee80211_supported_band *sband;

		अगर (!setup.chandef.chan)
			वापस -EINVAL;

		sband = rdev->wiphy.bands[setup.chandef.chan->band];

		err = ieee80211_get_ratemask(sband, rates, n_rates,
					     &setup.basic_rates);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_TX_RATES]) अणु
		err = nl80211_parse_tx_bitrate_mask(info, info->attrs,
						    NL80211_ATTR_TX_RATES,
						    &setup.beacon_rate,
						    dev, false);
		अगर (err)
			वापस err;

		अगर (!setup.chandef.chan)
			वापस -EINVAL;

		err = validate_beacon_tx_rate(rdev, setup.chandef.chan->band,
					      &setup.beacon_rate);
		अगर (err)
			वापस err;
	पूर्ण

	setup.userspace_handles_dfs =
		nla_get_flag(info->attrs[NL80211_ATTR_HANDLE_DFS]);

	अगर (info->attrs[NL80211_ATTR_CONTROL_PORT_OVER_NL80211]) अणु
		पूर्णांक r = validate_pae_over_nl80211(rdev, info);

		अगर (r < 0)
			वापस r;

		setup.control_port_over_nl80211 = true;
	पूर्ण

	wdev_lock(dev->ieee80211_ptr);
	err = __cfg80211_join_mesh(rdev, dev, &setup, &cfg);
	अगर (!err && info->attrs[NL80211_ATTR_SOCKET_OWNER])
		dev->ieee80211_ptr->conn_owner_nlportid = info->snd_portid;
	wdev_unlock(dev->ieee80211_ptr);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_leave_mesh(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];

	वापस cfg80211_leave_mesh(rdev, dev);
पूर्ण

#अगर_घोषित CONFIG_PM
अटल पूर्णांक nl80211_send_wowlan_patterns(काष्ठा sk_buff *msg,
					काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा cfg80211_wowlan *wowlan = rdev->wiphy.wowlan_config;
	काष्ठा nlattr *nl_pats, *nl_pat;
	पूर्णांक i, pat_len;

	अगर (!wowlan->n_patterns)
		वापस 0;

	nl_pats = nla_nest_start_noflag(msg, NL80211_WOWLAN_TRIG_PKT_PATTERN);
	अगर (!nl_pats)
		वापस -ENOBUFS;

	क्रम (i = 0; i < wowlan->n_patterns; i++) अणु
		nl_pat = nla_nest_start_noflag(msg, i + 1);
		अगर (!nl_pat)
			वापस -ENOBUFS;
		pat_len = wowlan->patterns[i].pattern_len;
		अगर (nla_put(msg, NL80211_PKTPAT_MASK, DIV_ROUND_UP(pat_len, 8),
			    wowlan->patterns[i].mask) ||
		    nla_put(msg, NL80211_PKTPAT_PATTERN, pat_len,
			    wowlan->patterns[i].pattern) ||
		    nla_put_u32(msg, NL80211_PKTPAT_OFFSET,
				wowlan->patterns[i].pkt_offset))
			वापस -ENOBUFS;
		nla_nest_end(msg, nl_pat);
	पूर्ण
	nla_nest_end(msg, nl_pats);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_send_wowlan_tcp(काष्ठा sk_buff *msg,
				   काष्ठा cfg80211_wowlan_tcp *tcp)
अणु
	काष्ठा nlattr *nl_tcp;

	अगर (!tcp)
		वापस 0;

	nl_tcp = nla_nest_start_noflag(msg,
				       NL80211_WOWLAN_TRIG_TCP_CONNECTION);
	अगर (!nl_tcp)
		वापस -ENOBUFS;

	अगर (nla_put_in_addr(msg, NL80211_WOWLAN_TCP_SRC_IPV4, tcp->src) ||
	    nla_put_in_addr(msg, NL80211_WOWLAN_TCP_DST_IPV4, tcp->dst) ||
	    nla_put(msg, NL80211_WOWLAN_TCP_DST_MAC, ETH_ALEN, tcp->dst_mac) ||
	    nla_put_u16(msg, NL80211_WOWLAN_TCP_SRC_PORT, tcp->src_port) ||
	    nla_put_u16(msg, NL80211_WOWLAN_TCP_DST_PORT, tcp->dst_port) ||
	    nla_put(msg, NL80211_WOWLAN_TCP_DATA_PAYLOAD,
		    tcp->payload_len, tcp->payload) ||
	    nla_put_u32(msg, NL80211_WOWLAN_TCP_DATA_INTERVAL,
			tcp->data_पूर्णांकerval) ||
	    nla_put(msg, NL80211_WOWLAN_TCP_WAKE_PAYLOAD,
		    tcp->wake_len, tcp->wake_data) ||
	    nla_put(msg, NL80211_WOWLAN_TCP_WAKE_MASK,
		    DIV_ROUND_UP(tcp->wake_len, 8), tcp->wake_mask))
		वापस -ENOBUFS;

	अगर (tcp->payload_seq.len &&
	    nla_put(msg, NL80211_WOWLAN_TCP_DATA_PAYLOAD_SEQ,
		    माप(tcp->payload_seq), &tcp->payload_seq))
		वापस -ENOBUFS;

	अगर (tcp->payload_tok.len &&
	    nla_put(msg, NL80211_WOWLAN_TCP_DATA_PAYLOAD_TOKEN,
		    माप(tcp->payload_tok) + tcp->tokens_size,
		    &tcp->payload_tok))
		वापस -ENOBUFS;

	nla_nest_end(msg, nl_tcp);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_send_wowlan_nd(काष्ठा sk_buff *msg,
				  काष्ठा cfg80211_sched_scan_request *req)
अणु
	काष्ठा nlattr *nd, *freqs, *matches, *match, *scan_plans, *scan_plan;
	पूर्णांक i;

	अगर (!req)
		वापस 0;

	nd = nla_nest_start_noflag(msg, NL80211_WOWLAN_TRIG_NET_DETECT);
	अगर (!nd)
		वापस -ENOBUFS;

	अगर (req->n_scan_plans == 1 &&
	    nla_put_u32(msg, NL80211_ATTR_SCHED_SCAN_INTERVAL,
			req->scan_plans[0].पूर्णांकerval * 1000))
		वापस -ENOBUFS;

	अगर (nla_put_u32(msg, NL80211_ATTR_SCHED_SCAN_DELAY, req->delay))
		वापस -ENOBUFS;

	अगर (req->relative_rssi_set) अणु
		काष्ठा nl80211_bss_select_rssi_adjust rssi_adjust;

		अगर (nla_put_s8(msg, NL80211_ATTR_SCHED_SCAN_RELATIVE_RSSI,
			       req->relative_rssi))
			वापस -ENOBUFS;

		rssi_adjust.band = req->rssi_adjust.band;
		rssi_adjust.delta = req->rssi_adjust.delta;
		अगर (nla_put(msg, NL80211_ATTR_SCHED_SCAN_RSSI_ADJUST,
			    माप(rssi_adjust), &rssi_adjust))
			वापस -ENOBUFS;
	पूर्ण

	freqs = nla_nest_start_noflag(msg, NL80211_ATTR_SCAN_FREQUENCIES);
	अगर (!freqs)
		वापस -ENOBUFS;

	क्रम (i = 0; i < req->n_channels; i++) अणु
		अगर (nla_put_u32(msg, i, req->channels[i]->center_freq))
			वापस -ENOBUFS;
	पूर्ण

	nla_nest_end(msg, freqs);

	अगर (req->n_match_sets) अणु
		matches = nla_nest_start_noflag(msg,
						NL80211_ATTR_SCHED_SCAN_MATCH);
		अगर (!matches)
			वापस -ENOBUFS;

		क्रम (i = 0; i < req->n_match_sets; i++) अणु
			match = nla_nest_start_noflag(msg, i);
			अगर (!match)
				वापस -ENOBUFS;

			अगर (nla_put(msg, NL80211_SCHED_SCAN_MATCH_ATTR_SSID,
				    req->match_sets[i].ssid.ssid_len,
				    req->match_sets[i].ssid.ssid))
				वापस -ENOBUFS;
			nla_nest_end(msg, match);
		पूर्ण
		nla_nest_end(msg, matches);
	पूर्ण

	scan_plans = nla_nest_start_noflag(msg, NL80211_ATTR_SCHED_SCAN_PLANS);
	अगर (!scan_plans)
		वापस -ENOBUFS;

	क्रम (i = 0; i < req->n_scan_plans; i++) अणु
		scan_plan = nla_nest_start_noflag(msg, i + 1);
		अगर (!scan_plan)
			वापस -ENOBUFS;

		अगर (nla_put_u32(msg, NL80211_SCHED_SCAN_PLAN_INTERVAL,
				req->scan_plans[i].पूर्णांकerval) ||
		    (req->scan_plans[i].iterations &&
		     nla_put_u32(msg, NL80211_SCHED_SCAN_PLAN_ITERATIONS,
				 req->scan_plans[i].iterations)))
			वापस -ENOBUFS;
		nla_nest_end(msg, scan_plan);
	पूर्ण
	nla_nest_end(msg, scan_plans);

	nla_nest_end(msg, nd);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_get_wowlan(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	u32 size = NLMSG_DEFAULT_SIZE;

	अगर (!rdev->wiphy.wowlan)
		वापस -EOPNOTSUPP;

	अगर (rdev->wiphy.wowlan_config && rdev->wiphy.wowlan_config->tcp) अणु
		/* adjust size to have room क्रम all the data */
		size += rdev->wiphy.wowlan_config->tcp->tokens_size +
			rdev->wiphy.wowlan_config->tcp->payload_len +
			rdev->wiphy.wowlan_config->tcp->wake_len +
			rdev->wiphy.wowlan_config->tcp->wake_len / 8;
	पूर्ण

	msg = nlmsg_new(size, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_WOWLAN);
	अगर (!hdr)
		जाओ nla_put_failure;

	अगर (rdev->wiphy.wowlan_config) अणु
		काष्ठा nlattr *nl_wowlan;

		nl_wowlan = nla_nest_start_noflag(msg,
						  NL80211_ATTR_WOWLAN_TRIGGERS);
		अगर (!nl_wowlan)
			जाओ nla_put_failure;

		अगर ((rdev->wiphy.wowlan_config->any &&
		     nla_put_flag(msg, NL80211_WOWLAN_TRIG_ANY)) ||
		    (rdev->wiphy.wowlan_config->disconnect &&
		     nla_put_flag(msg, NL80211_WOWLAN_TRIG_DISCONNECT)) ||
		    (rdev->wiphy.wowlan_config->magic_pkt &&
		     nla_put_flag(msg, NL80211_WOWLAN_TRIG_MAGIC_PKT)) ||
		    (rdev->wiphy.wowlan_config->gtk_rekey_failure &&
		     nla_put_flag(msg, NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE)) ||
		    (rdev->wiphy.wowlan_config->eap_identity_req &&
		     nla_put_flag(msg, NL80211_WOWLAN_TRIG_EAP_IDENT_REQUEST)) ||
		    (rdev->wiphy.wowlan_config->four_way_handshake &&
		     nla_put_flag(msg, NL80211_WOWLAN_TRIG_4WAY_HANDSHAKE)) ||
		    (rdev->wiphy.wowlan_config->rfसमाप्त_release &&
		     nla_put_flag(msg, NL80211_WOWLAN_TRIG_RFKILL_RELEASE)))
			जाओ nla_put_failure;

		अगर (nl80211_send_wowlan_patterns(msg, rdev))
			जाओ nla_put_failure;

		अगर (nl80211_send_wowlan_tcp(msg,
					    rdev->wiphy.wowlan_config->tcp))
			जाओ nla_put_failure;

		अगर (nl80211_send_wowlan_nd(
			    msg,
			    rdev->wiphy.wowlan_config->nd_config))
			जाओ nla_put_failure;

		nla_nest_end(msg, nl_wowlan);
	पूर्ण

	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक nl80211_parse_wowlan_tcp(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा nlattr *attr,
				    काष्ठा cfg80211_wowlan *trig)
अणु
	काष्ठा nlattr *tb[NUM_NL80211_WOWLAN_TCP];
	काष्ठा cfg80211_wowlan_tcp *cfg;
	काष्ठा nl80211_wowlan_tcp_data_token *tok = शून्य;
	काष्ठा nl80211_wowlan_tcp_data_seq *seq = शून्य;
	u32 size;
	u32 data_size, wake_size, tokens_size = 0, wake_mask_size;
	पूर्णांक err, port;

	अगर (!rdev->wiphy.wowlan->tcp)
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, MAX_NL80211_WOWLAN_TCP, attr,
					  nl80211_wowlan_tcp_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (!tb[NL80211_WOWLAN_TCP_SRC_IPV4] ||
	    !tb[NL80211_WOWLAN_TCP_DST_IPV4] ||
	    !tb[NL80211_WOWLAN_TCP_DST_MAC] ||
	    !tb[NL80211_WOWLAN_TCP_DST_PORT] ||
	    !tb[NL80211_WOWLAN_TCP_DATA_PAYLOAD] ||
	    !tb[NL80211_WOWLAN_TCP_DATA_INTERVAL] ||
	    !tb[NL80211_WOWLAN_TCP_WAKE_PAYLOAD] ||
	    !tb[NL80211_WOWLAN_TCP_WAKE_MASK])
		वापस -EINVAL;

	data_size = nla_len(tb[NL80211_WOWLAN_TCP_DATA_PAYLOAD]);
	अगर (data_size > rdev->wiphy.wowlan->tcp->data_payload_max)
		वापस -EINVAL;

	अगर (nla_get_u32(tb[NL80211_WOWLAN_TCP_DATA_INTERVAL]) >
			rdev->wiphy.wowlan->tcp->data_पूर्णांकerval_max ||
	    nla_get_u32(tb[NL80211_WOWLAN_TCP_DATA_INTERVAL]) == 0)
		वापस -EINVAL;

	wake_size = nla_len(tb[NL80211_WOWLAN_TCP_WAKE_PAYLOAD]);
	अगर (wake_size > rdev->wiphy.wowlan->tcp->wake_payload_max)
		वापस -EINVAL;

	wake_mask_size = nla_len(tb[NL80211_WOWLAN_TCP_WAKE_MASK]);
	अगर (wake_mask_size != DIV_ROUND_UP(wake_size, 8))
		वापस -EINVAL;

	अगर (tb[NL80211_WOWLAN_TCP_DATA_PAYLOAD_TOKEN]) अणु
		u32 tokln = nla_len(tb[NL80211_WOWLAN_TCP_DATA_PAYLOAD_TOKEN]);

		tok = nla_data(tb[NL80211_WOWLAN_TCP_DATA_PAYLOAD_TOKEN]);
		tokens_size = tokln - माप(*tok);

		अगर (!tok->len || tokens_size % tok->len)
			वापस -EINVAL;
		अगर (!rdev->wiphy.wowlan->tcp->tok)
			वापस -EINVAL;
		अगर (tok->len > rdev->wiphy.wowlan->tcp->tok->max_len)
			वापस -EINVAL;
		अगर (tok->len < rdev->wiphy.wowlan->tcp->tok->min_len)
			वापस -EINVAL;
		अगर (tokens_size > rdev->wiphy.wowlan->tcp->tok->bufsize)
			वापस -EINVAL;
		अगर (tok->offset + tok->len > data_size)
			वापस -EINVAL;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TCP_DATA_PAYLOAD_SEQ]) अणु
		seq = nla_data(tb[NL80211_WOWLAN_TCP_DATA_PAYLOAD_SEQ]);
		अगर (!rdev->wiphy.wowlan->tcp->seq)
			वापस -EINVAL;
		अगर (seq->len == 0 || seq->len > 4)
			वापस -EINVAL;
		अगर (seq->len + seq->offset > data_size)
			वापस -EINVAL;
	पूर्ण

	size = माप(*cfg);
	size += data_size;
	size += wake_size + wake_mask_size;
	size += tokens_size;

	cfg = kzalloc(size, GFP_KERNEL);
	अगर (!cfg)
		वापस -ENOMEM;
	cfg->src = nla_get_in_addr(tb[NL80211_WOWLAN_TCP_SRC_IPV4]);
	cfg->dst = nla_get_in_addr(tb[NL80211_WOWLAN_TCP_DST_IPV4]);
	स_नकल(cfg->dst_mac, nla_data(tb[NL80211_WOWLAN_TCP_DST_MAC]),
	       ETH_ALEN);
	अगर (tb[NL80211_WOWLAN_TCP_SRC_PORT])
		port = nla_get_u16(tb[NL80211_WOWLAN_TCP_SRC_PORT]);
	अन्यथा
		port = 0;
#अगर_घोषित CONFIG_INET
	/* allocate a socket and port क्रम it and use it */
	err = __sock_create(wiphy_net(&rdev->wiphy), PF_INET, SOCK_STREAM,
			    IPPROTO_TCP, &cfg->sock, 1);
	अगर (err) अणु
		kमुक्त(cfg);
		वापस err;
	पूर्ण
	अगर (inet_csk_get_port(cfg->sock->sk, port)) अणु
		sock_release(cfg->sock);
		kमुक्त(cfg);
		वापस -EADDRINUSE;
	पूर्ण
	cfg->src_port = inet_sk(cfg->sock->sk)->inet_num;
#अन्यथा
	अगर (!port) अणु
		kमुक्त(cfg);
		वापस -EINVAL;
	पूर्ण
	cfg->src_port = port;
#पूर्ण_अगर

	cfg->dst_port = nla_get_u16(tb[NL80211_WOWLAN_TCP_DST_PORT]);
	cfg->payload_len = data_size;
	cfg->payload = (u8 *)cfg + माप(*cfg) + tokens_size;
	स_नकल((व्योम *)cfg->payload,
	       nla_data(tb[NL80211_WOWLAN_TCP_DATA_PAYLOAD]),
	       data_size);
	अगर (seq)
		cfg->payload_seq = *seq;
	cfg->data_पूर्णांकerval = nla_get_u32(tb[NL80211_WOWLAN_TCP_DATA_INTERVAL]);
	cfg->wake_len = wake_size;
	cfg->wake_data = (u8 *)cfg + माप(*cfg) + tokens_size + data_size;
	स_नकल((व्योम *)cfg->wake_data,
	       nla_data(tb[NL80211_WOWLAN_TCP_WAKE_PAYLOAD]),
	       wake_size);
	cfg->wake_mask = (u8 *)cfg + माप(*cfg) + tokens_size +
			 data_size + wake_size;
	स_नकल((व्योम *)cfg->wake_mask,
	       nla_data(tb[NL80211_WOWLAN_TCP_WAKE_MASK]),
	       wake_mask_size);
	अगर (tok) अणु
		cfg->tokens_size = tokens_size;
		स_नकल(&cfg->payload_tok, tok, माप(*tok) + tokens_size);
	पूर्ण

	trig->tcp = cfg;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_parse_wowlan_nd(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				   स्थिर काष्ठा wiphy_wowlan_support *wowlan,
				   काष्ठा nlattr *attr,
				   काष्ठा cfg80211_wowlan *trig)
अणु
	काष्ठा nlattr **tb;
	पूर्णांक err;

	tb = kसुस्मृति(NUM_NL80211_ATTR, माप(*tb), GFP_KERNEL);
	अगर (!tb)
		वापस -ENOMEM;

	अगर (!(wowlan->flags & WIPHY_WOWLAN_NET_DETECT)) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, NL80211_ATTR_MAX, attr,
					  nl80211_policy, शून्य);
	अगर (err)
		जाओ out;

	trig->nd_config = nl80211_parse_sched_scan(&rdev->wiphy, शून्य, tb,
						   wowlan->max_nd_match_sets);
	err = PTR_ERR_OR_ZERO(trig->nd_config);
	अगर (err)
		trig->nd_config = शून्य;

out:
	kमुक्त(tb);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_set_wowlan(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा nlattr *tb[NUM_NL80211_WOWLAN_TRIG];
	काष्ठा cfg80211_wowlan new_triggers = अणुपूर्ण;
	काष्ठा cfg80211_wowlan *ntrig;
	स्थिर काष्ठा wiphy_wowlan_support *wowlan = rdev->wiphy.wowlan;
	पूर्णांक err, i;
	bool prev_enabled = rdev->wiphy.wowlan_config;
	bool regular = false;

	अगर (!wowlan)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_WOWLAN_TRIGGERS]) अणु
		cfg80211_rdev_मुक्त_wowlan(rdev);
		rdev->wiphy.wowlan_config = शून्य;
		जाओ set_wakeup;
	पूर्ण

	err = nla_parse_nested_deprecated(tb, MAX_NL80211_WOWLAN_TRIG,
					  info->attrs[NL80211_ATTR_WOWLAN_TRIGGERS],
					  nl80211_wowlan_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (tb[NL80211_WOWLAN_TRIG_ANY]) अणु
		अगर (!(wowlan->flags & WIPHY_WOWLAN_ANY))
			वापस -EINVAL;
		new_triggers.any = true;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_DISCONNECT]) अणु
		अगर (!(wowlan->flags & WIPHY_WOWLAN_DISCONNECT))
			वापस -EINVAL;
		new_triggers.disconnect = true;
		regular = true;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_MAGIC_PKT]) अणु
		अगर (!(wowlan->flags & WIPHY_WOWLAN_MAGIC_PKT))
			वापस -EINVAL;
		new_triggers.magic_pkt = true;
		regular = true;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_GTK_REKEY_SUPPORTED])
		वापस -EINVAL;

	अगर (tb[NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE]) अणु
		अगर (!(wowlan->flags & WIPHY_WOWLAN_GTK_REKEY_FAILURE))
			वापस -EINVAL;
		new_triggers.gtk_rekey_failure = true;
		regular = true;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_EAP_IDENT_REQUEST]) अणु
		अगर (!(wowlan->flags & WIPHY_WOWLAN_EAP_IDENTITY_REQ))
			वापस -EINVAL;
		new_triggers.eap_identity_req = true;
		regular = true;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_4WAY_HANDSHAKE]) अणु
		अगर (!(wowlan->flags & WIPHY_WOWLAN_4WAY_HANDSHAKE))
			वापस -EINVAL;
		new_triggers.four_way_handshake = true;
		regular = true;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_RFKILL_RELEASE]) अणु
		अगर (!(wowlan->flags & WIPHY_WOWLAN_RFKILL_RELEASE))
			वापस -EINVAL;
		new_triggers.rfसमाप्त_release = true;
		regular = true;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_PKT_PATTERN]) अणु
		काष्ठा nlattr *pat;
		पूर्णांक n_patterns = 0;
		पूर्णांक rem, pat_len, mask_len, pkt_offset;
		काष्ठा nlattr *pat_tb[NUM_NL80211_PKTPAT];

		regular = true;

		nla_क्रम_each_nested(pat, tb[NL80211_WOWLAN_TRIG_PKT_PATTERN],
				    rem)
			n_patterns++;
		अगर (n_patterns > wowlan->n_patterns)
			वापस -EINVAL;

		new_triggers.patterns = kसुस्मृति(n_patterns,
						माप(new_triggers.patterns[0]),
						GFP_KERNEL);
		अगर (!new_triggers.patterns)
			वापस -ENOMEM;

		new_triggers.n_patterns = n_patterns;
		i = 0;

		nla_क्रम_each_nested(pat, tb[NL80211_WOWLAN_TRIG_PKT_PATTERN],
				    rem) अणु
			u8 *mask_pat;

			err = nla_parse_nested_deprecated(pat_tb,
							  MAX_NL80211_PKTPAT,
							  pat,
							  nl80211_packet_pattern_policy,
							  info->extack);
			अगर (err)
				जाओ error;

			err = -EINVAL;
			अगर (!pat_tb[NL80211_PKTPAT_MASK] ||
			    !pat_tb[NL80211_PKTPAT_PATTERN])
				जाओ error;
			pat_len = nla_len(pat_tb[NL80211_PKTPAT_PATTERN]);
			mask_len = DIV_ROUND_UP(pat_len, 8);
			अगर (nla_len(pat_tb[NL80211_PKTPAT_MASK]) != mask_len)
				जाओ error;
			अगर (pat_len > wowlan->pattern_max_len ||
			    pat_len < wowlan->pattern_min_len)
				जाओ error;

			अगर (!pat_tb[NL80211_PKTPAT_OFFSET])
				pkt_offset = 0;
			अन्यथा
				pkt_offset = nla_get_u32(
					pat_tb[NL80211_PKTPAT_OFFSET]);
			अगर (pkt_offset > wowlan->max_pkt_offset)
				जाओ error;
			new_triggers.patterns[i].pkt_offset = pkt_offset;

			mask_pat = kदो_स्मृति(mask_len + pat_len, GFP_KERNEL);
			अगर (!mask_pat) अणु
				err = -ENOMEM;
				जाओ error;
			पूर्ण
			new_triggers.patterns[i].mask = mask_pat;
			स_नकल(mask_pat, nla_data(pat_tb[NL80211_PKTPAT_MASK]),
			       mask_len);
			mask_pat += mask_len;
			new_triggers.patterns[i].pattern = mask_pat;
			new_triggers.patterns[i].pattern_len = pat_len;
			स_नकल(mask_pat,
			       nla_data(pat_tb[NL80211_PKTPAT_PATTERN]),
			       pat_len);
			i++;
		पूर्ण
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_TCP_CONNECTION]) अणु
		regular = true;
		err = nl80211_parse_wowlan_tcp(
			rdev, tb[NL80211_WOWLAN_TRIG_TCP_CONNECTION],
			&new_triggers);
		अगर (err)
			जाओ error;
	पूर्ण

	अगर (tb[NL80211_WOWLAN_TRIG_NET_DETECT]) अणु
		regular = true;
		err = nl80211_parse_wowlan_nd(
			rdev, wowlan, tb[NL80211_WOWLAN_TRIG_NET_DETECT],
			&new_triggers);
		अगर (err)
			जाओ error;
	पूर्ण

	/* The 'any' trigger means the device जारीs operating more or less
	 * as in its normal operation mode and wakes up the host on most of the
	 * normal पूर्णांकerrupts (like packet RX, ...)
	 * It thereक्रमe makes little sense to combine with the more स्थिरrained
	 * wakeup trigger modes.
	 */
	अगर (new_triggers.any && regular) अणु
		err = -EINVAL;
		जाओ error;
	पूर्ण

	ntrig = kmemdup(&new_triggers, माप(new_triggers), GFP_KERNEL);
	अगर (!ntrig) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	cfg80211_rdev_मुक्त_wowlan(rdev);
	rdev->wiphy.wowlan_config = ntrig;

 set_wakeup:
	अगर (rdev->ops->set_wakeup &&
	    prev_enabled != !!rdev->wiphy.wowlan_config)
		rdev_set_wakeup(rdev, rdev->wiphy.wowlan_config);

	वापस 0;
 error:
	क्रम (i = 0; i < new_triggers.n_patterns; i++)
		kमुक्त(new_triggers.patterns[i].mask);
	kमुक्त(new_triggers.patterns);
	अगर (new_triggers.tcp && new_triggers.tcp->sock)
		sock_release(new_triggers.tcp->sock);
	kमुक्त(new_triggers.tcp);
	kमुक्त(new_triggers.nd_config);
	वापस err;
पूर्ण
#पूर्ण_अगर

अटल पूर्णांक nl80211_send_coalesce_rules(काष्ठा sk_buff *msg,
				       काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा nlattr *nl_pats, *nl_pat, *nl_rule, *nl_rules;
	पूर्णांक i, j, pat_len;
	काष्ठा cfg80211_coalesce_rules *rule;

	अगर (!rdev->coalesce->n_rules)
		वापस 0;

	nl_rules = nla_nest_start_noflag(msg, NL80211_ATTR_COALESCE_RULE);
	अगर (!nl_rules)
		वापस -ENOBUFS;

	क्रम (i = 0; i < rdev->coalesce->n_rules; i++) अणु
		nl_rule = nla_nest_start_noflag(msg, i + 1);
		अगर (!nl_rule)
			वापस -ENOBUFS;

		rule = &rdev->coalesce->rules[i];
		अगर (nla_put_u32(msg, NL80211_ATTR_COALESCE_RULE_DELAY,
				rule->delay))
			वापस -ENOBUFS;

		अगर (nla_put_u32(msg, NL80211_ATTR_COALESCE_RULE_CONDITION,
				rule->condition))
			वापस -ENOBUFS;

		nl_pats = nla_nest_start_noflag(msg,
						NL80211_ATTR_COALESCE_RULE_PKT_PATTERN);
		अगर (!nl_pats)
			वापस -ENOBUFS;

		क्रम (j = 0; j < rule->n_patterns; j++) अणु
			nl_pat = nla_nest_start_noflag(msg, j + 1);
			अगर (!nl_pat)
				वापस -ENOBUFS;
			pat_len = rule->patterns[j].pattern_len;
			अगर (nla_put(msg, NL80211_PKTPAT_MASK,
				    DIV_ROUND_UP(pat_len, 8),
				    rule->patterns[j].mask) ||
			    nla_put(msg, NL80211_PKTPAT_PATTERN, pat_len,
				    rule->patterns[j].pattern) ||
			    nla_put_u32(msg, NL80211_PKTPAT_OFFSET,
					rule->patterns[j].pkt_offset))
				वापस -ENOBUFS;
			nla_nest_end(msg, nl_pat);
		पूर्ण
		nla_nest_end(msg, nl_pats);
		nla_nest_end(msg, nl_rule);
	पूर्ण
	nla_nest_end(msg, nl_rules);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_get_coalesce(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	अगर (!rdev->wiphy.coalesce)
		वापस -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_COALESCE);
	अगर (!hdr)
		जाओ nla_put_failure;

	अगर (rdev->coalesce && nl80211_send_coalesce_rules(msg, rdev))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण

व्योम cfg80211_rdev_मुक्त_coalesce(काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा cfg80211_coalesce *coalesce = rdev->coalesce;
	पूर्णांक i, j;
	काष्ठा cfg80211_coalesce_rules *rule;

	अगर (!coalesce)
		वापस;

	क्रम (i = 0; i < coalesce->n_rules; i++) अणु
		rule = &coalesce->rules[i];
		क्रम (j = 0; j < rule->n_patterns; j++)
			kमुक्त(rule->patterns[j].mask);
		kमुक्त(rule->patterns);
	पूर्ण
	kमुक्त(coalesce->rules);
	kमुक्त(coalesce);
	rdev->coalesce = शून्य;
पूर्ण

अटल पूर्णांक nl80211_parse_coalesce_rule(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				       काष्ठा nlattr *rule,
				       काष्ठा cfg80211_coalesce_rules *new_rule)
अणु
	पूर्णांक err, i;
	स्थिर काष्ठा wiphy_coalesce_support *coalesce = rdev->wiphy.coalesce;
	काष्ठा nlattr *tb[NUM_NL80211_ATTR_COALESCE_RULE], *pat;
	पूर्णांक rem, pat_len, mask_len, pkt_offset, n_patterns = 0;
	काष्ठा nlattr *pat_tb[NUM_NL80211_PKTPAT];

	err = nla_parse_nested_deprecated(tb, NL80211_ATTR_COALESCE_RULE_MAX,
					  rule, nl80211_coalesce_policy, शून्य);
	अगर (err)
		वापस err;

	अगर (tb[NL80211_ATTR_COALESCE_RULE_DELAY])
		new_rule->delay =
			nla_get_u32(tb[NL80211_ATTR_COALESCE_RULE_DELAY]);
	अगर (new_rule->delay > coalesce->max_delay)
		वापस -EINVAL;

	अगर (tb[NL80211_ATTR_COALESCE_RULE_CONDITION])
		new_rule->condition =
			nla_get_u32(tb[NL80211_ATTR_COALESCE_RULE_CONDITION]);

	अगर (!tb[NL80211_ATTR_COALESCE_RULE_PKT_PATTERN])
		वापस -EINVAL;

	nla_क्रम_each_nested(pat, tb[NL80211_ATTR_COALESCE_RULE_PKT_PATTERN],
			    rem)
		n_patterns++;
	अगर (n_patterns > coalesce->n_patterns)
		वापस -EINVAL;

	new_rule->patterns = kसुस्मृति(n_patterns, माप(new_rule->patterns[0]),
				     GFP_KERNEL);
	अगर (!new_rule->patterns)
		वापस -ENOMEM;

	new_rule->n_patterns = n_patterns;
	i = 0;

	nla_क्रम_each_nested(pat, tb[NL80211_ATTR_COALESCE_RULE_PKT_PATTERN],
			    rem) अणु
		u8 *mask_pat;

		err = nla_parse_nested_deprecated(pat_tb, MAX_NL80211_PKTPAT,
						  pat,
						  nl80211_packet_pattern_policy,
						  शून्य);
		अगर (err)
			वापस err;

		अगर (!pat_tb[NL80211_PKTPAT_MASK] ||
		    !pat_tb[NL80211_PKTPAT_PATTERN])
			वापस -EINVAL;
		pat_len = nla_len(pat_tb[NL80211_PKTPAT_PATTERN]);
		mask_len = DIV_ROUND_UP(pat_len, 8);
		अगर (nla_len(pat_tb[NL80211_PKTPAT_MASK]) != mask_len)
			वापस -EINVAL;
		अगर (pat_len > coalesce->pattern_max_len ||
		    pat_len < coalesce->pattern_min_len)
			वापस -EINVAL;

		अगर (!pat_tb[NL80211_PKTPAT_OFFSET])
			pkt_offset = 0;
		अन्यथा
			pkt_offset = nla_get_u32(pat_tb[NL80211_PKTPAT_OFFSET]);
		अगर (pkt_offset > coalesce->max_pkt_offset)
			वापस -EINVAL;
		new_rule->patterns[i].pkt_offset = pkt_offset;

		mask_pat = kदो_स्मृति(mask_len + pat_len, GFP_KERNEL);
		अगर (!mask_pat)
			वापस -ENOMEM;

		new_rule->patterns[i].mask = mask_pat;
		स_नकल(mask_pat, nla_data(pat_tb[NL80211_PKTPAT_MASK]),
		       mask_len);

		mask_pat += mask_len;
		new_rule->patterns[i].pattern = mask_pat;
		new_rule->patterns[i].pattern_len = pat_len;
		स_नकल(mask_pat, nla_data(pat_tb[NL80211_PKTPAT_PATTERN]),
		       pat_len);
		i++;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_set_coalesce(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	स्थिर काष्ठा wiphy_coalesce_support *coalesce = rdev->wiphy.coalesce;
	काष्ठा cfg80211_coalesce new_coalesce = अणुपूर्ण;
	काष्ठा cfg80211_coalesce *n_coalesce;
	पूर्णांक err, rem_rule, n_rules = 0, i, j;
	काष्ठा nlattr *rule;
	काष्ठा cfg80211_coalesce_rules *पंचांगp_rule;

	अगर (!rdev->wiphy.coalesce || !rdev->ops->set_coalesce)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_COALESCE_RULE]) अणु
		cfg80211_rdev_मुक्त_coalesce(rdev);
		rdev_set_coalesce(rdev, शून्य);
		वापस 0;
	पूर्ण

	nla_क्रम_each_nested(rule, info->attrs[NL80211_ATTR_COALESCE_RULE],
			    rem_rule)
		n_rules++;
	अगर (n_rules > coalesce->n_rules)
		वापस -EINVAL;

	new_coalesce.rules = kसुस्मृति(n_rules, माप(new_coalesce.rules[0]),
				     GFP_KERNEL);
	अगर (!new_coalesce.rules)
		वापस -ENOMEM;

	new_coalesce.n_rules = n_rules;
	i = 0;

	nla_क्रम_each_nested(rule, info->attrs[NL80211_ATTR_COALESCE_RULE],
			    rem_rule) अणु
		err = nl80211_parse_coalesce_rule(rdev, rule,
						  &new_coalesce.rules[i]);
		अगर (err)
			जाओ error;

		i++;
	पूर्ण

	err = rdev_set_coalesce(rdev, &new_coalesce);
	अगर (err)
		जाओ error;

	n_coalesce = kmemdup(&new_coalesce, माप(new_coalesce), GFP_KERNEL);
	अगर (!n_coalesce) अणु
		err = -ENOMEM;
		जाओ error;
	पूर्ण
	cfg80211_rdev_मुक्त_coalesce(rdev);
	rdev->coalesce = n_coalesce;

	वापस 0;
error:
	क्रम (i = 0; i < new_coalesce.n_rules; i++) अणु
		पंचांगp_rule = &new_coalesce.rules[i];
		क्रम (j = 0; j < पंचांगp_rule->n_patterns; j++)
			kमुक्त(पंचांगp_rule->patterns[j].mask);
		kमुक्त(पंचांगp_rule->patterns);
	पूर्ण
	kमुक्त(new_coalesce.rules);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_set_rekey_data(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा nlattr *tb[NUM_NL80211_REKEY_DATA];
	काष्ठा cfg80211_gtk_rekey_data rekey_data = अणुपूर्ण;
	पूर्णांक err;

	अगर (!info->attrs[NL80211_ATTR_REKEY_DATA])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, MAX_NL80211_REKEY_DATA,
					  info->attrs[NL80211_ATTR_REKEY_DATA],
					  nl80211_rekey_policy, info->extack);
	अगर (err)
		वापस err;

	अगर (!tb[NL80211_REKEY_DATA_REPLAY_CTR] || !tb[NL80211_REKEY_DATA_KEK] ||
	    !tb[NL80211_REKEY_DATA_KCK])
		वापस -EINVAL;
	अगर (nla_len(tb[NL80211_REKEY_DATA_KEK]) != NL80211_KEK_LEN &&
	    !(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_EXT_KEK_KCK &&
	      nla_len(tb[NL80211_REKEY_DATA_KEK]) == NL80211_KEK_EXT_LEN))
		वापस -दुस्फल;
	अगर (nla_len(tb[NL80211_REKEY_DATA_KCK]) != NL80211_KCK_LEN &&
	    !(rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_EXT_KEK_KCK &&
	      nla_len(tb[NL80211_REKEY_DATA_KEK]) == NL80211_KCK_EXT_LEN))
		वापस -दुस्फल;

	rekey_data.kek = nla_data(tb[NL80211_REKEY_DATA_KEK]);
	rekey_data.kck = nla_data(tb[NL80211_REKEY_DATA_KCK]);
	rekey_data.replay_ctr = nla_data(tb[NL80211_REKEY_DATA_REPLAY_CTR]);
	rekey_data.kek_len = nla_len(tb[NL80211_REKEY_DATA_KEK]);
	rekey_data.kck_len = nla_len(tb[NL80211_REKEY_DATA_KCK]);
	अगर (tb[NL80211_REKEY_DATA_AKM])
		rekey_data.akm = nla_get_u32(tb[NL80211_REKEY_DATA_AKM]);

	wdev_lock(wdev);
	अगर (!wdev->current_bss) अणु
		err = -ENOTCONN;
		जाओ out;
	पूर्ण

	अगर (!rdev->ops->set_rekey_data) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	err = rdev_set_rekey_data(rdev, dev, &rekey_data);
 out:
	wdev_unlock(wdev);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_रेजिस्टर_unexpected_frame(काष्ठा sk_buff *skb,
					     काष्ठा genl_info *info)
अणु
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;

	अगर (wdev->अगरtype != NL80211_IFTYPE_AP &&
	    wdev->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EINVAL;

	अगर (wdev->ap_unexpected_nlportid)
		वापस -EBUSY;

	wdev->ap_unexpected_nlportid = info->snd_portid;
	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_probe_client(काष्ठा sk_buff *skb,
				काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	स्थिर u8 *addr;
	u64 cookie;
	पूर्णांक err;

	अगर (wdev->अगरtype != NL80211_IFTYPE_AP &&
	    wdev->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	अगर (!rdev->ops->probe_client)
		वापस -EOPNOTSUPP;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_PROBE_CLIENT);
	अगर (!hdr) अणु
		err = -ENOBUFS;
		जाओ मुक्त_msg;
	पूर्ण

	addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	err = rdev_probe_client(rdev, dev, addr, &cookie);
	अगर (err)
		जाओ मुक्त_msg;

	अगर (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस genlmsg_reply(msg, info);

 nla_put_failure:
	err = -ENOBUFS;
 मुक्त_msg:
	nlmsg_मुक्त(msg);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_रेजिस्टर_beacons(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा cfg80211_beacon_registration *reg, *nreg;
	पूर्णांक rv;

	अगर (!(rdev->wiphy.flags & WIPHY_FLAG_REPORTS_OBSS))
		वापस -EOPNOTSUPP;

	nreg = kzalloc(माप(*nreg), GFP_KERNEL);
	अगर (!nreg)
		वापस -ENOMEM;

	/* First, check अगर alपढ़ोy रेजिस्टरed. */
	spin_lock_bh(&rdev->beacon_registrations_lock);
	list_क्रम_each_entry(reg, &rdev->beacon_registrations, list) अणु
		अगर (reg->nlportid == info->snd_portid) अणु
			rv = -EALREADY;
			जाओ out_err;
		पूर्ण
	पूर्ण
	/* Add it to the list */
	nreg->nlportid = info->snd_portid;
	list_add(&nreg->list, &rdev->beacon_registrations);

	spin_unlock_bh(&rdev->beacon_registrations_lock);

	वापस 0;
out_err:
	spin_unlock_bh(&rdev->beacon_registrations_lock);
	kमुक्त(nreg);
	वापस rv;
पूर्ण

अटल पूर्णांक nl80211_start_p2p_device(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	पूर्णांक err;

	अगर (!rdev->ops->start_p2p_device)
		वापस -EOPNOTSUPP;

	अगर (wdev->अगरtype != NL80211_IFTYPE_P2P_DEVICE)
		वापस -EOPNOTSUPP;

	अगर (wdev_running(wdev))
		वापस 0;

	अगर (rfसमाप्त_blocked(rdev->rfसमाप्त))
		वापस -ERFKILL;

	err = rdev_start_p2p_device(rdev, wdev);
	अगर (err)
		वापस err;

	wdev->is_running = true;
	rdev->खोलोcount++;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_stop_p2p_device(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];

	अगर (wdev->अगरtype != NL80211_IFTYPE_P2P_DEVICE)
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->stop_p2p_device)
		वापस -EOPNOTSUPP;

	cfg80211_stop_p2p_device(rdev, wdev);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_start_nan(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	काष्ठा cfg80211_nan_conf conf = अणुपूर्ण;
	पूर्णांक err;

	अगर (wdev->अगरtype != NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	अगर (wdev_running(wdev))
		वापस -EEXIST;

	अगर (rfसमाप्त_blocked(rdev->rfसमाप्त))
		वापस -ERFKILL;

	अगर (!info->attrs[NL80211_ATTR_न_अंक_MASTER_PREF])
		वापस -EINVAL;

	conf.master_pref =
		nla_get_u8(info->attrs[NL80211_ATTR_न_अंक_MASTER_PREF]);

	अगर (info->attrs[NL80211_ATTR_BANDS]) अणु
		u32 bands = nla_get_u32(info->attrs[NL80211_ATTR_BANDS]);

		अगर (bands & ~(u32)wdev->wiphy->nan_supported_bands)
			वापस -EOPNOTSUPP;

		अगर (bands && !(bands & BIT(NL80211_BAND_2GHZ)))
			वापस -EINVAL;

		conf.bands = bands;
	पूर्ण

	err = rdev_start_nan(rdev, wdev, &conf);
	अगर (err)
		वापस err;

	wdev->is_running = true;
	rdev->खोलोcount++;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_stop_nan(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];

	अगर (wdev->अगरtype != NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	cfg80211_stop_nan(rdev, wdev);

	वापस 0;
पूर्ण

अटल पूर्णांक validate_nan_filter(काष्ठा nlattr *filter_attr)
अणु
	काष्ठा nlattr *attr;
	पूर्णांक len = 0, n_entries = 0, rem;

	nla_क्रम_each_nested(attr, filter_attr, rem) अणु
		len += nla_len(attr);
		n_entries++;
	पूर्ण

	अगर (len >= U8_MAX)
		वापस -EINVAL;

	वापस n_entries;
पूर्ण

अटल पूर्णांक handle_nan_filter(काष्ठा nlattr *attr_filter,
			     काष्ठा cfg80211_nan_func *func,
			     bool tx)
अणु
	काष्ठा nlattr *attr;
	पूर्णांक n_entries, rem, i;
	काष्ठा cfg80211_nan_func_filter *filter;

	n_entries = validate_nan_filter(attr_filter);
	अगर (n_entries < 0)
		वापस n_entries;

	BUILD_BUG_ON(माप(*func->rx_filters) != माप(*func->tx_filters));

	filter = kसुस्मृति(n_entries, माप(*func->rx_filters), GFP_KERNEL);
	अगर (!filter)
		वापस -ENOMEM;

	i = 0;
	nla_क्रम_each_nested(attr, attr_filter, rem) अणु
		filter[i].filter = nla_memdup(attr, GFP_KERNEL);
		filter[i].len = nla_len(attr);
		i++;
	पूर्ण
	अगर (tx) अणु
		func->num_tx_filters = n_entries;
		func->tx_filters = filter;
	पूर्ण अन्यथा अणु
		func->num_rx_filters = n_entries;
		func->rx_filters = filter;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_nan_add_func(काष्ठा sk_buff *skb,
				काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	काष्ठा nlattr *tb[NUM_NL80211_न_अंक_FUNC_ATTR], *func_attr;
	काष्ठा cfg80211_nan_func *func;
	काष्ठा sk_buff *msg = शून्य;
	व्योम *hdr = शून्य;
	पूर्णांक err = 0;

	अगर (wdev->अगरtype != NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	अगर (!wdev_running(wdev))
		वापस -ENOTCONN;

	अगर (!info->attrs[NL80211_ATTR_न_अंक_FUNC])
		वापस -EINVAL;

	err = nla_parse_nested_deprecated(tb, NL80211_न_अंक_FUNC_ATTR_MAX,
					  info->attrs[NL80211_ATTR_न_अंक_FUNC],
					  nl80211_nan_func_policy,
					  info->extack);
	अगर (err)
		वापस err;

	func = kzalloc(माप(*func), GFP_KERNEL);
	अगर (!func)
		वापस -ENOMEM;

	func->cookie = cfg80211_assign_cookie(rdev);

	अगर (!tb[NL80211_न_अंक_FUNC_TYPE]) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण


	func->type = nla_get_u8(tb[NL80211_न_अंक_FUNC_TYPE]);

	अगर (!tb[NL80211_न_अंक_FUNC_SERVICE_ID]) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	स_नकल(func->service_id, nla_data(tb[NL80211_न_अंक_FUNC_SERVICE_ID]),
	       माप(func->service_id));

	func->बंद_range =
		nla_get_flag(tb[NL80211_न_अंक_FUNC_CLOSE_RANGE]);

	अगर (tb[NL80211_न_अंक_FUNC_SERVICE_INFO]) अणु
		func->serv_spec_info_len =
			nla_len(tb[NL80211_न_अंक_FUNC_SERVICE_INFO]);
		func->serv_spec_info =
			kmemdup(nla_data(tb[NL80211_न_अंक_FUNC_SERVICE_INFO]),
				func->serv_spec_info_len,
				GFP_KERNEL);
		अगर (!func->serv_spec_info) अणु
			err = -ENOMEM;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (tb[NL80211_न_अंक_FUNC_TTL])
		func->ttl = nla_get_u32(tb[NL80211_न_अंक_FUNC_TTL]);

	चयन (func->type) अणु
	हाल NL80211_न_अंक_FUNC_PUBLISH:
		अगर (!tb[NL80211_न_अंक_FUNC_PUBLISH_TYPE]) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		func->publish_type =
			nla_get_u8(tb[NL80211_न_अंक_FUNC_PUBLISH_TYPE]);
		func->publish_bcast =
			nla_get_flag(tb[NL80211_न_अंक_FUNC_PUBLISH_BCAST]);

		अगर ((!(func->publish_type & NL80211_न_अंक_SOLICITED_PUBLISH)) &&
			func->publish_bcast) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		अवरोध;
	हाल NL80211_न_अंक_FUNC_SUBSCRIBE:
		func->subscribe_active =
			nla_get_flag(tb[NL80211_न_अंक_FUNC_SUBSCRIBE_ACTIVE]);
		अवरोध;
	हाल NL80211_न_अंक_FUNC_FOLLOW_UP:
		अगर (!tb[NL80211_न_अंक_FUNC_FOLLOW_UP_ID] ||
		    !tb[NL80211_न_अंक_FUNC_FOLLOW_UP_REQ_ID] ||
		    !tb[NL80211_न_अंक_FUNC_FOLLOW_UP_DEST]) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		func->followup_id =
			nla_get_u8(tb[NL80211_न_अंक_FUNC_FOLLOW_UP_ID]);
		func->followup_reqid =
			nla_get_u8(tb[NL80211_न_अंक_FUNC_FOLLOW_UP_REQ_ID]);
		स_नकल(func->followup_dest.addr,
		       nla_data(tb[NL80211_न_अंक_FUNC_FOLLOW_UP_DEST]),
		       माप(func->followup_dest.addr));
		अगर (func->ttl) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		अवरोध;
	शेष:
		err = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (tb[NL80211_न_अंक_FUNC_SRF]) अणु
		काष्ठा nlattr *srf_tb[NUM_NL80211_न_अंक_SRF_ATTR];

		err = nla_parse_nested_deprecated(srf_tb,
						  NL80211_न_अंक_SRF_ATTR_MAX,
						  tb[NL80211_न_अंक_FUNC_SRF],
						  nl80211_nan_srf_policy,
						  info->extack);
		अगर (err)
			जाओ out;

		func->srf_include =
			nla_get_flag(srf_tb[NL80211_न_अंक_SRF_INCLUDE]);

		अगर (srf_tb[NL80211_न_अंक_SRF_BF]) अणु
			अगर (srf_tb[NL80211_न_अंक_SRF_MAC_ADDRS] ||
			    !srf_tb[NL80211_न_अंक_SRF_BF_IDX]) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			func->srf_bf_len =
				nla_len(srf_tb[NL80211_न_अंक_SRF_BF]);
			func->srf_bf =
				kmemdup(nla_data(srf_tb[NL80211_न_अंक_SRF_BF]),
					func->srf_bf_len, GFP_KERNEL);
			अगर (!func->srf_bf) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण

			func->srf_bf_idx =
				nla_get_u8(srf_tb[NL80211_न_अंक_SRF_BF_IDX]);
		पूर्ण अन्यथा अणु
			काष्ठा nlattr *attr, *mac_attr =
				srf_tb[NL80211_न_अंक_SRF_MAC_ADDRS];
			पूर्णांक n_entries, rem, i = 0;

			अगर (!mac_attr) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			n_entries = validate_acl_mac_addrs(mac_attr);
			अगर (n_entries <= 0) अणु
				err = -EINVAL;
				जाओ out;
			पूर्ण

			func->srf_num_macs = n_entries;
			func->srf_macs =
				kसुस्मृति(n_entries, माप(*func->srf_macs),
					GFP_KERNEL);
			अगर (!func->srf_macs) अणु
				err = -ENOMEM;
				जाओ out;
			पूर्ण

			nla_क्रम_each_nested(attr, mac_attr, rem)
				स_नकल(func->srf_macs[i++].addr, nla_data(attr),
				       माप(*func->srf_macs));
		पूर्ण
	पूर्ण

	अगर (tb[NL80211_न_अंक_FUNC_TX_MATCH_FILTER]) अणु
		err = handle_nan_filter(tb[NL80211_न_अंक_FUNC_TX_MATCH_FILTER],
					func, true);
		अगर (err)
			जाओ out;
	पूर्ण

	अगर (tb[NL80211_न_अंक_FUNC_RX_MATCH_FILTER]) अणु
		err = handle_nan_filter(tb[NL80211_न_अंक_FUNC_RX_MATCH_FILTER],
					func, false);
		अगर (err)
			जाओ out;
	पूर्ण

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_ADD_न_अंक_FUNCTION);
	/* This can't really happen - we just allocated 4KB */
	अगर (WARN_ON(!hdr)) अणु
		err = -ENOMEM;
		जाओ out;
	पूर्ण

	err = rdev_add_nan_func(rdev, wdev, func);
out:
	अगर (err < 0) अणु
		cfg80211_मुक्त_nan_func(func);
		nlmsg_मुक्त(msg);
		वापस err;
	पूर्ण

	/* propagate the instance id and cookie to userspace  */
	अगर (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, func->cookie,
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	func_attr = nla_nest_start_noflag(msg, NL80211_ATTR_न_अंक_FUNC);
	अगर (!func_attr)
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, NL80211_न_अंक_FUNC_INSTANCE_ID,
		       func->instance_id))
		जाओ nla_put_failure;

	nla_nest_end(msg, func_attr);

	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक nl80211_nan_del_func(काष्ठा sk_buff *skb,
			       काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	u64 cookie;

	अगर (wdev->अगरtype != NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	अगर (!wdev_running(wdev))
		वापस -ENOTCONN;

	अगर (!info->attrs[NL80211_ATTR_COOKIE])
		वापस -EINVAL;

	cookie = nla_get_u64(info->attrs[NL80211_ATTR_COOKIE]);

	rdev_del_nan_func(rdev, wdev, cookie);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_nan_change_config(काष्ठा sk_buff *skb,
				     काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	काष्ठा cfg80211_nan_conf conf = अणुपूर्ण;
	u32 changed = 0;

	अगर (wdev->अगरtype != NL80211_IFTYPE_न_अंक)
		वापस -EOPNOTSUPP;

	अगर (!wdev_running(wdev))
		वापस -ENOTCONN;

	अगर (info->attrs[NL80211_ATTR_न_अंक_MASTER_PREF]) अणु
		conf.master_pref =
			nla_get_u8(info->attrs[NL80211_ATTR_न_अंक_MASTER_PREF]);
		अगर (conf.master_pref <= 1 || conf.master_pref == 255)
			वापस -EINVAL;

		changed |= CFG80211_न_अंक_CONF_CHANGED_PREF;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_BANDS]) अणु
		u32 bands = nla_get_u32(info->attrs[NL80211_ATTR_BANDS]);

		अगर (bands & ~(u32)wdev->wiphy->nan_supported_bands)
			वापस -EOPNOTSUPP;

		अगर (bands && !(bands & BIT(NL80211_BAND_2GHZ)))
			वापस -EINVAL;

		conf.bands = bands;
		changed |= CFG80211_न_अंक_CONF_CHANGED_BANDS;
	पूर्ण

	अगर (!changed)
		वापस -EINVAL;

	वापस rdev_nan_change_conf(rdev, wdev, &conf, changed);
पूर्ण

व्योम cfg80211_nan_match(काष्ठा wireless_dev *wdev,
			काष्ठा cfg80211_nan_match_params *match, gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा nlattr *match_attr, *local_func_attr, *peer_func_attr;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	अगर (WARN_ON(!match->inst_id || !match->peer_inst_id || !match->addr))
		वापस;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_न_अंक_MATCH);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    (wdev->netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
					 wdev->netdev->अगरindex)) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, match->cookie,
			      NL80211_ATTR_PAD) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, match->addr))
		जाओ nla_put_failure;

	match_attr = nla_nest_start_noflag(msg, NL80211_ATTR_न_अंक_MATCH);
	अगर (!match_attr)
		जाओ nla_put_failure;

	local_func_attr = nla_nest_start_noflag(msg,
						NL80211_न_अंक_MATCH_FUNC_LOCAL);
	अगर (!local_func_attr)
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, NL80211_न_अंक_FUNC_INSTANCE_ID, match->inst_id))
		जाओ nla_put_failure;

	nla_nest_end(msg, local_func_attr);

	peer_func_attr = nla_nest_start_noflag(msg,
					       NL80211_न_अंक_MATCH_FUNC_PEER);
	अगर (!peer_func_attr)
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, NL80211_न_अंक_FUNC_TYPE, match->type) ||
	    nla_put_u8(msg, NL80211_न_अंक_FUNC_INSTANCE_ID, match->peer_inst_id))
		जाओ nla_put_failure;

	अगर (match->info && match->info_len &&
	    nla_put(msg, NL80211_न_अंक_FUNC_SERVICE_INFO, match->info_len,
		    match->info))
		जाओ nla_put_failure;

	nla_nest_end(msg, peer_func_attr);
	nla_nest_end(msg, match_attr);
	genlmsg_end(msg, hdr);

	अगर (!wdev->owner_nlportid)
		genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy),
					msg, 0, NL80211_MCGRP_न_अंक, gfp);
	अन्यथा
		genlmsg_unicast(wiphy_net(&rdev->wiphy), msg,
				wdev->owner_nlportid);

	वापस;

nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_nan_match);

व्योम cfg80211_nan_func_terminated(काष्ठा wireless_dev *wdev,
				  u8 inst_id,
				  क्रमागत nl80211_nan_func_term_reason reason,
				  u64 cookie, gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा sk_buff *msg;
	काष्ठा nlattr *func_attr;
	व्योम *hdr;

	अगर (WARN_ON(!inst_id))
		वापस;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_DEL_न_अंक_FUNCTION);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    (wdev->netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
					 wdev->netdev->अगरindex)) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	func_attr = nla_nest_start_noflag(msg, NL80211_ATTR_न_अंक_FUNC);
	अगर (!func_attr)
		जाओ nla_put_failure;

	अगर (nla_put_u8(msg, NL80211_न_अंक_FUNC_INSTANCE_ID, inst_id) ||
	    nla_put_u8(msg, NL80211_न_अंक_FUNC_TERM_REASON, reason))
		जाओ nla_put_failure;

	nla_nest_end(msg, func_attr);
	genlmsg_end(msg, hdr);

	अगर (!wdev->owner_nlportid)
		genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy),
					msg, 0, NL80211_MCGRP_न_अंक, gfp);
	अन्यथा
		genlmsg_unicast(wiphy_net(&rdev->wiphy), msg,
				wdev->owner_nlportid);

	वापस;

nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_nan_func_terminated);

अटल पूर्णांक nl80211_get_protocol_features(काष्ठा sk_buff *skb,
					 काष्ठा genl_info *info)
अणु
	व्योम *hdr;
	काष्ठा sk_buff *msg;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_PROTOCOL_FEATURES);
	अगर (!hdr)
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_PROTOCOL_FEATURES,
			NL80211_PROTOCOL_FEATURE_SPLIT_WIPHY_DUMP))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

 nla_put_failure:
	kमुक्त_skb(msg);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक nl80211_update_ft_ies(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा cfg80211_update_ft_ies_params ft_params;
	काष्ठा net_device *dev = info->user_ptr[1];

	अगर (!rdev->ops->update_ft_ies)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_MDID] ||
	    !info->attrs[NL80211_ATTR_IE])
		वापस -EINVAL;

	स_रखो(&ft_params, 0, माप(ft_params));
	ft_params.md = nla_get_u16(info->attrs[NL80211_ATTR_MDID]);
	ft_params.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
	ft_params.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);

	वापस rdev_update_ft_ies(rdev, dev, &ft_params);
पूर्ण

अटल पूर्णांक nl80211_crit_protocol_start(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];
	क्रमागत nl80211_crit_proto_id proto = NL80211_CRIT_PROTO_UNSPEC;
	u16 duration;
	पूर्णांक ret;

	अगर (!rdev->ops->crit_proto_start)
		वापस -EOPNOTSUPP;

	अगर (WARN_ON(!rdev->ops->crit_proto_stop))
		वापस -EINVAL;

	अगर (rdev->crit_proto_nlportid)
		वापस -EBUSY;

	/* determine protocol अगर provided */
	अगर (info->attrs[NL80211_ATTR_CRIT_PROT_ID])
		proto = nla_get_u16(info->attrs[NL80211_ATTR_CRIT_PROT_ID]);

	अगर (proto >= NUM_NL80211_CRIT_PROTO)
		वापस -EINVAL;

	/* समयout must be provided */
	अगर (!info->attrs[NL80211_ATTR_MAX_CRIT_PROT_DURATION])
		वापस -EINVAL;

	duration =
		nla_get_u16(info->attrs[NL80211_ATTR_MAX_CRIT_PROT_DURATION]);

	ret = rdev_crit_proto_start(rdev, wdev, proto, duration);
	अगर (!ret)
		rdev->crit_proto_nlportid = info->snd_portid;

	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_crit_protocol_stop(काष्ठा sk_buff *skb,
				      काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev = info->user_ptr[1];

	अगर (!rdev->ops->crit_proto_stop)
		वापस -EOPNOTSUPP;

	अगर (rdev->crit_proto_nlportid) अणु
		rdev->crit_proto_nlportid = 0;
		rdev_crit_proto_stop(rdev, wdev);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_venकरोr_check_policy(स्थिर काष्ठा wiphy_venकरोr_command *vcmd,
				       काष्ठा nlattr *attr,
				       काष्ठा netlink_ext_ack *extack)
अणु
	अगर (vcmd->policy == VENDOR_CMD_RAW_DATA) अणु
		अगर (attr->nla_type & NLA_F_NESTED) अणु
			NL_SET_ERR_MSG_ATTR(extack, attr,
					    "unexpected nested data");
			वापस -EINVAL;
		पूर्ण

		वापस 0;
	पूर्ण

	अगर (!(attr->nla_type & NLA_F_NESTED)) अणु
		NL_SET_ERR_MSG_ATTR(extack, attr, "expected nested data");
		वापस -EINVAL;
	पूर्ण

	वापस nla_validate_nested(attr, vcmd->maxattr, vcmd->policy, extack);
पूर्ण

अटल पूर्णांक nl80211_venकरोr_cmd(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा wireless_dev *wdev =
		__cfg80211_wdev_from_attrs(rdev, genl_info_net(info),
					   info->attrs);
	पूर्णांक i, err;
	u32 vid, subcmd;

	अगर (!rdev->wiphy.venकरोr_commands)
		वापस -EOPNOTSUPP;

	अगर (IS_ERR(wdev)) अणु
		err = PTR_ERR(wdev);
		अगर (err != -EINVAL)
			वापस err;
		wdev = शून्य;
	पूर्ण अन्यथा अगर (wdev->wiphy != &rdev->wiphy) अणु
		वापस -EINVAL;
	पूर्ण

	अगर (!info->attrs[NL80211_ATTR_VENDOR_ID] ||
	    !info->attrs[NL80211_ATTR_VENDOR_SUBCMD])
		वापस -EINVAL;

	vid = nla_get_u32(info->attrs[NL80211_ATTR_VENDOR_ID]);
	subcmd = nla_get_u32(info->attrs[NL80211_ATTR_VENDOR_SUBCMD]);
	क्रम (i = 0; i < rdev->wiphy.n_venकरोr_commands; i++) अणु
		स्थिर काष्ठा wiphy_venकरोr_command *vcmd;
		व्योम *data = शून्य;
		पूर्णांक len = 0;

		vcmd = &rdev->wiphy.venकरोr_commands[i];

		अगर (vcmd->info.venकरोr_id != vid || vcmd->info.subcmd != subcmd)
			जारी;

		अगर (vcmd->flags & (WIPHY_VENDOR_CMD_NEED_WDEV |
				   WIPHY_VENDOR_CMD_NEED_NETDEV)) अणु
			अगर (!wdev)
				वापस -EINVAL;
			अगर (vcmd->flags & WIPHY_VENDOR_CMD_NEED_NETDEV &&
			    !wdev->netdev)
				वापस -EINVAL;

			अगर (vcmd->flags & WIPHY_VENDOR_CMD_NEED_RUNNING) अणु
				अगर (!wdev_running(wdev))
					वापस -ENETDOWN;
			पूर्ण
		पूर्ण अन्यथा अणु
			wdev = शून्य;
		पूर्ण

		अगर (!vcmd->करोit)
			वापस -EOPNOTSUPP;

		अगर (info->attrs[NL80211_ATTR_VENDOR_DATA]) अणु
			data = nla_data(info->attrs[NL80211_ATTR_VENDOR_DATA]);
			len = nla_len(info->attrs[NL80211_ATTR_VENDOR_DATA]);

			err = nl80211_venकरोr_check_policy(vcmd,
					info->attrs[NL80211_ATTR_VENDOR_DATA],
					info->extack);
			अगर (err)
				वापस err;
		पूर्ण

		rdev->cur_cmd_info = info;
		err = vcmd->करोit(&rdev->wiphy, wdev, data, len);
		rdev->cur_cmd_info = शून्य;
		वापस err;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

अटल पूर्णांक nl80211_prepare_venकरोr_dump(काष्ठा sk_buff *skb,
				       काष्ठा netlink_callback *cb,
				       काष्ठा cfg80211_रेजिस्टरed_device **rdev,
				       काष्ठा wireless_dev **wdev)
अणु
	काष्ठा nlattr **attrbuf;
	u32 vid, subcmd;
	अचिन्हित पूर्णांक i;
	पूर्णांक vcmd_idx = -1;
	पूर्णांक err;
	व्योम *data = शून्य;
	अचिन्हित पूर्णांक data_len = 0;

	अगर (cb->args[0]) अणु
		/* subtract the 1 again here */
		काष्ठा wiphy *wiphy = wiphy_idx_to_wiphy(cb->args[0] - 1);
		काष्ठा wireless_dev *पंचांगp;

		अगर (!wiphy)
			वापस -ENODEV;
		*rdev = wiphy_to_rdev(wiphy);
		*wdev = शून्य;

		अगर (cb->args[1]) अणु
			list_क्रम_each_entry(पंचांगp, &wiphy->wdev_list, list) अणु
				अगर (पंचांगp->identअगरier == cb->args[1] - 1) अणु
					*wdev = पंचांगp;
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण

		/* keep rtnl locked in successful हाल */
		वापस 0;
	पूर्ण

	attrbuf = kसुस्मृति(NUM_NL80211_ATTR, माप(*attrbuf), GFP_KERNEL);
	अगर (!attrbuf)
		वापस -ENOMEM;

	err = nlmsg_parse_deprecated(cb->nlh,
				     GENL_HDRLEN + nl80211_fam.hdrsize,
				     attrbuf, nl80211_fam.maxattr,
				     nl80211_policy, शून्य);
	अगर (err)
		जाओ out;

	अगर (!attrbuf[NL80211_ATTR_VENDOR_ID] ||
	    !attrbuf[NL80211_ATTR_VENDOR_SUBCMD]) अणु
		err = -EINVAL;
		जाओ out;
	पूर्ण

	*wdev = __cfg80211_wdev_from_attrs(शून्य, sock_net(skb->sk), attrbuf);
	अगर (IS_ERR(*wdev))
		*wdev = शून्य;

	*rdev = __cfg80211_rdev_from_attrs(sock_net(skb->sk), attrbuf);
	अगर (IS_ERR(*rdev)) अणु
		err = PTR_ERR(*rdev);
		जाओ out;
	पूर्ण

	vid = nla_get_u32(attrbuf[NL80211_ATTR_VENDOR_ID]);
	subcmd = nla_get_u32(attrbuf[NL80211_ATTR_VENDOR_SUBCMD]);

	क्रम (i = 0; i < (*rdev)->wiphy.n_venकरोr_commands; i++) अणु
		स्थिर काष्ठा wiphy_venकरोr_command *vcmd;

		vcmd = &(*rdev)->wiphy.venकरोr_commands[i];

		अगर (vcmd->info.venकरोr_id != vid || vcmd->info.subcmd != subcmd)
			जारी;

		अगर (!vcmd->dumpit) अणु
			err = -EOPNOTSUPP;
			जाओ out;
		पूर्ण

		vcmd_idx = i;
		अवरोध;
	पूर्ण

	अगर (vcmd_idx < 0) अणु
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (attrbuf[NL80211_ATTR_VENDOR_DATA]) अणु
		data = nla_data(attrbuf[NL80211_ATTR_VENDOR_DATA]);
		data_len = nla_len(attrbuf[NL80211_ATTR_VENDOR_DATA]);

		err = nl80211_venकरोr_check_policy(
				&(*rdev)->wiphy.venकरोr_commands[vcmd_idx],
				attrbuf[NL80211_ATTR_VENDOR_DATA],
				cb->extack);
		अगर (err)
			जाओ out;
	पूर्ण

	/* 0 is the first index - add 1 to parse only once */
	cb->args[0] = (*rdev)->wiphy_idx + 1;
	/* add 1 to know अगर it was शून्य */
	cb->args[1] = *wdev ? (*wdev)->identअगरier + 1 : 0;
	cb->args[2] = vcmd_idx;
	cb->args[3] = (अचिन्हित दीर्घ)data;
	cb->args[4] = data_len;

	/* keep rtnl locked in successful हाल */
	err = 0;
out:
	kमुक्त(attrbuf);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_venकरोr_cmd_dump(काष्ठा sk_buff *skb,
				   काष्ठा netlink_callback *cb)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;
	अचिन्हित पूर्णांक vcmd_idx;
	स्थिर काष्ठा wiphy_venकरोr_command *vcmd;
	व्योम *data;
	पूर्णांक data_len;
	पूर्णांक err;
	काष्ठा nlattr *venकरोr_data;

	rtnl_lock();
	err = nl80211_prepare_venकरोr_dump(skb, cb, &rdev, &wdev);
	अगर (err)
		जाओ out;

	vcmd_idx = cb->args[2];
	data = (व्योम *)cb->args[3];
	data_len = cb->args[4];
	vcmd = &rdev->wiphy.venकरोr_commands[vcmd_idx];

	अगर (vcmd->flags & (WIPHY_VENDOR_CMD_NEED_WDEV |
			   WIPHY_VENDOR_CMD_NEED_NETDEV)) अणु
		अगर (!wdev) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण
		अगर (vcmd->flags & WIPHY_VENDOR_CMD_NEED_NETDEV &&
		    !wdev->netdev) अणु
			err = -EINVAL;
			जाओ out;
		पूर्ण

		अगर (vcmd->flags & WIPHY_VENDOR_CMD_NEED_RUNNING) अणु
			अगर (!wdev_running(wdev)) अणु
				err = -ENETDOWN;
				जाओ out;
			पूर्ण
		पूर्ण
	पूर्ण

	जबतक (1) अणु
		व्योम *hdr = nl80211hdr_put(skb, NETLINK_CB(cb->skb).portid,
					   cb->nlh->nlmsg_seq, NLM_F_MULTI,
					   NL80211_CMD_VENDOR);
		अगर (!hdr)
			अवरोध;

		अगर (nla_put_u32(skb, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
		    (wdev && nla_put_u64_64bit(skb, NL80211_ATTR_WDEV,
					       wdev_id(wdev),
					       NL80211_ATTR_PAD))) अणु
			genlmsg_cancel(skb, hdr);
			अवरोध;
		पूर्ण

		venकरोr_data = nla_nest_start_noflag(skb,
						    NL80211_ATTR_VENDOR_DATA);
		अगर (!venकरोr_data) अणु
			genlmsg_cancel(skb, hdr);
			अवरोध;
		पूर्ण

		err = vcmd->dumpit(&rdev->wiphy, wdev, skb, data, data_len,
				   (अचिन्हित दीर्घ *)&cb->args[5]);
		nla_nest_end(skb, venकरोr_data);

		अगर (err == -ENOBUFS || err == -ENOENT) अणु
			genlmsg_cancel(skb, hdr);
			अवरोध;
		पूर्ण अन्यथा अगर (err <= 0) अणु
			genlmsg_cancel(skb, hdr);
			जाओ out;
		पूर्ण

		genlmsg_end(skb, hdr);
	पूर्ण

	err = skb->len;
 out:
	rtnl_unlock();
	वापस err;
पूर्ण

काष्ठा sk_buff *__cfg80211_alloc_reply_skb(काष्ठा wiphy *wiphy,
					   क्रमागत nl80211_commands cmd,
					   क्रमागत nl80211_attrs attr,
					   पूर्णांक approxlen)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	अगर (WARN_ON(!rdev->cur_cmd_info))
		वापस शून्य;

	वापस __cfg80211_alloc_venकरोr_skb(rdev, शून्य, approxlen,
					   rdev->cur_cmd_info->snd_portid,
					   rdev->cur_cmd_info->snd_seq,
					   cmd, attr, शून्य, GFP_KERNEL);
पूर्ण
EXPORT_SYMBOL(__cfg80211_alloc_reply_skb);

पूर्णांक cfg80211_venकरोr_cmd_reply(काष्ठा sk_buff *skb)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = ((व्योम **)skb->cb)[0];
	व्योम *hdr = ((व्योम **)skb->cb)[1];
	काष्ठा nlattr *data = ((व्योम **)skb->cb)[2];

	/* clear CB data क्रम netlink core to own from now on */
	स_रखो(skb->cb, 0, माप(skb->cb));

	अगर (WARN_ON(!rdev->cur_cmd_info)) अणु
		kमुक्त_skb(skb);
		वापस -EINVAL;
	पूर्ण

	nla_nest_end(skb, data);
	genlmsg_end(skb, hdr);
	वापस genlmsg_reply(skb, rdev->cur_cmd_info);
पूर्ण
EXPORT_SYMBOL_GPL(cfg80211_venकरोr_cmd_reply);

अचिन्हित पूर्णांक cfg80211_venकरोr_cmd_get_sender(काष्ठा wiphy *wiphy)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	अगर (WARN_ON(!rdev->cur_cmd_info))
		वापस 0;

	वापस rdev->cur_cmd_info->snd_portid;
पूर्ण
EXPORT_SYMBOL_GPL(cfg80211_venकरोr_cmd_get_sender);

अटल पूर्णांक nl80211_set_qos_map(काष्ठा sk_buff *skb,
			       काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा cfg80211_qos_map *qos_map = शून्य;
	काष्ठा net_device *dev = info->user_ptr[1];
	u8 *pos, len, num_des, des_len, des;
	पूर्णांक ret;

	अगर (!rdev->ops->set_qos_map)
		वापस -EOPNOTSUPP;

	अगर (info->attrs[NL80211_ATTR_QOS_MAP]) अणु
		pos = nla_data(info->attrs[NL80211_ATTR_QOS_MAP]);
		len = nla_len(info->attrs[NL80211_ATTR_QOS_MAP]);

		अगर (len % 2)
			वापस -EINVAL;

		qos_map = kzalloc(माप(काष्ठा cfg80211_qos_map), GFP_KERNEL);
		अगर (!qos_map)
			वापस -ENOMEM;

		num_des = (len - IEEE80211_QOS_MAP_LEN_MIN) >> 1;
		अगर (num_des) अणु
			des_len = num_des *
				माप(काष्ठा cfg80211_dscp_exception);
			स_नकल(qos_map->dscp_exception, pos, des_len);
			qos_map->num_des = num_des;
			क्रम (des = 0; des < num_des; des++) अणु
				अगर (qos_map->dscp_exception[des].up > 7) अणु
					kमुक्त(qos_map);
					वापस -EINVAL;
				पूर्ण
			पूर्ण
			pos += des_len;
		पूर्ण
		स_नकल(qos_map->up, pos, IEEE80211_QOS_MAP_LEN_MIN);
	पूर्ण

	wdev_lock(dev->ieee80211_ptr);
	ret = nl80211_key_allowed(dev->ieee80211_ptr);
	अगर (!ret)
		ret = rdev_set_qos_map(rdev, dev, qos_map);
	wdev_unlock(dev->ieee80211_ptr);

	kमुक्त(qos_map);
	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_add_tx_ts(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	स्थिर u8 *peer;
	u8 tsid, up;
	u16 admitted_समय = 0;
	पूर्णांक err;

	अगर (!(rdev->wiphy.features & NL80211_FEATURE_SUPPORTS_WMM_ADMISSION))
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_TSID] || !info->attrs[NL80211_ATTR_MAC] ||
	    !info->attrs[NL80211_ATTR_USER_PRIO])
		वापस -EINVAL;

	tsid = nla_get_u8(info->attrs[NL80211_ATTR_TSID]);
	up = nla_get_u8(info->attrs[NL80211_ATTR_USER_PRIO]);

	/* WMM uses TIDs 0-7 even क्रम TSPEC */
	अगर (tsid >= IEEE80211_FIRST_TSPEC_TSID) अणु
		/* TODO: handle 802.11 TSPEC/admission control
		 * need more attributes क्रम that (e.g. BA session requirement);
		 * change the WMM adminssion test above to allow both then
		 */
		वापस -EINVAL;
	पूर्ण

	peer = nla_data(info->attrs[NL80211_ATTR_MAC]);

	अगर (info->attrs[NL80211_ATTR_ADMITTED_TIME]) अणु
		admitted_समय =
			nla_get_u16(info->attrs[NL80211_ATTR_ADMITTED_TIME]);
		अगर (!admitted_समय)
			वापस -EINVAL;
	पूर्ण

	wdev_lock(wdev);
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (wdev->current_bss)
			अवरोध;
		err = -ENOTCONN;
		जाओ out;
	शेष:
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	err = rdev_add_tx_ts(rdev, dev, tsid, peer, up, admitted_समय);

 out:
	wdev_unlock(wdev);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_del_tx_ts(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	स्थिर u8 *peer;
	u8 tsid;
	पूर्णांक err;

	अगर (!info->attrs[NL80211_ATTR_TSID] || !info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	tsid = nla_get_u8(info->attrs[NL80211_ATTR_TSID]);
	peer = nla_data(info->attrs[NL80211_ATTR_MAC]);

	wdev_lock(wdev);
	err = rdev_del_tx_ts(rdev, dev, tsid, peer);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_tdls_channel_चयन(काष्ठा sk_buff *skb,
				       काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_chan_def chandef = अणुपूर्ण;
	स्थिर u8 *addr;
	u8 oper_class;
	पूर्णांक err;

	अगर (!rdev->ops->tdls_channel_चयन ||
	    !(rdev->wiphy.features & NL80211_FEATURE_TDLS_CHANNEL_SWITCH))
		वापस -EOPNOTSUPP;

	चयन (dev->ieee80211_ptr->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!info->attrs[NL80211_ATTR_MAC] ||
	    !info->attrs[NL80211_ATTR_OPER_CLASS])
		वापस -EINVAL;

	err = nl80211_parse_chandef(rdev, info, &chandef);
	अगर (err)
		वापस err;

	/*
	 * Don't allow wide channels on the 2.4Ghz band, as per IEEE802.11-2012
	 * section 10.22.6.2.1. Disallow 5/10Mhz channels as well क्रम now, the
	 * specअगरication is not defined क्रम them.
	 */
	अगर (chandef.chan->band == NL80211_BAND_2GHZ &&
	    chandef.width != NL80211_CHAN_WIDTH_20_NOHT &&
	    chandef.width != NL80211_CHAN_WIDTH_20)
		वापस -EINVAL;

	/* we will be active on the TDLS link */
	अगर (!cfg80211_reg_can_beacon_relax(&rdev->wiphy, &chandef,
					   wdev->अगरtype))
		वापस -EINVAL;

	/* करोn't allow चयनing to DFS channels */
	अगर (cfg80211_chandef_dfs_required(wdev->wiphy, &chandef, wdev->अगरtype))
		वापस -EINVAL;

	addr = nla_data(info->attrs[NL80211_ATTR_MAC]);
	oper_class = nla_get_u8(info->attrs[NL80211_ATTR_OPER_CLASS]);

	wdev_lock(wdev);
	err = rdev_tdls_channel_चयन(rdev, dev, addr, oper_class, &chandef);
	wdev_unlock(wdev);

	वापस err;
पूर्ण

अटल पूर्णांक nl80211_tdls_cancel_channel_चयन(काष्ठा sk_buff *skb,
					      काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	स्थिर u8 *addr;

	अगर (!rdev->ops->tdls_channel_चयन ||
	    !rdev->ops->tdls_cancel_channel_चयन ||
	    !(rdev->wiphy.features & NL80211_FEATURE_TDLS_CHANNEL_SWITCH))
		वापस -EOPNOTSUPP;

	चयन (dev->ieee80211_ptr->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	addr = nla_data(info->attrs[NL80211_ATTR_MAC]);

	wdev_lock(wdev);
	rdev_tdls_cancel_channel_चयन(rdev, dev, addr);
	wdev_unlock(wdev);

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_set_multicast_to_unicast(काष्ठा sk_buff *skb,
					    काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	स्थिर काष्ठा nlattr *nla;
	bool enabled;

	अगर (!rdev->ops->set_multicast_to_unicast)
		वापस -EOPNOTSUPP;

	अगर (wdev->अगरtype != NL80211_IFTYPE_AP &&
	    wdev->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EOPNOTSUPP;

	nla = info->attrs[NL80211_ATTR_MULTICAST_TO_UNICAST_ENABLED];
	enabled = nla_get_flag(nla);

	वापस rdev_set_multicast_to_unicast(rdev, dev, enabled);
पूर्ण

अटल पूर्णांक nl80211_set_pmk(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_pmk_conf pmk_conf = अणुपूर्ण;
	पूर्णांक ret;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION &&
	    wdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X))
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_MAC] || !info->attrs[NL80211_ATTR_PMK])
		वापस -EINVAL;

	wdev_lock(wdev);
	अगर (!wdev->current_bss) अणु
		ret = -ENOTCONN;
		जाओ out;
	पूर्ण

	pmk_conf.aa = nla_data(info->attrs[NL80211_ATTR_MAC]);
	अगर (स_भेद(pmk_conf.aa, wdev->current_bss->pub.bssid, ETH_ALEN)) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	pmk_conf.pmk = nla_data(info->attrs[NL80211_ATTR_PMK]);
	pmk_conf.pmk_len = nla_len(info->attrs[NL80211_ATTR_PMK]);
	अगर (pmk_conf.pmk_len != WLAN_PMK_LEN &&
	    pmk_conf.pmk_len != WLAN_PMK_LEN_SUITE_B_192) अणु
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	अगर (info->attrs[NL80211_ATTR_PMKR0_NAME])
		pmk_conf.pmk_r0_name =
			nla_data(info->attrs[NL80211_ATTR_PMKR0_NAME]);

	ret = rdev_set_pmk(rdev, dev, &pmk_conf);
out:
	wdev_unlock(wdev);
	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_del_pmk(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	स्थिर u8 *aa;
	पूर्णांक ret;

	अगर (wdev->अगरtype != NL80211_IFTYPE_STATION &&
	    wdev->अगरtype != NL80211_IFTYPE_P2P_CLIENT)
		वापस -EOPNOTSUPP;

	अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_4WAY_HANDSHAKE_STA_1X))
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	wdev_lock(wdev);
	aa = nla_data(info->attrs[NL80211_ATTR_MAC]);
	ret = rdev_del_pmk(rdev, dev, aa);
	wdev_unlock(wdev);

	वापस ret;
पूर्ण

अटल पूर्णांक nl80211_बाह्यal_auth(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा cfg80211_बाह्यal_auth_params params;

	अगर (!rdev->ops->बाह्यal_auth)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_SSID] &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_AP &&
	    dev->ieee80211_ptr->अगरtype != NL80211_IFTYPE_P2P_GO)
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_BSSID])
		वापस -EINVAL;

	अगर (!info->attrs[NL80211_ATTR_STATUS_CODE])
		वापस -EINVAL;

	स_रखो(&params, 0, माप(params));

	अगर (info->attrs[NL80211_ATTR_SSID]) अणु
		params.ssid.ssid_len = nla_len(info->attrs[NL80211_ATTR_SSID]);
		अगर (params.ssid.ssid_len == 0)
			वापस -EINVAL;
		स_नकल(params.ssid.ssid,
		       nla_data(info->attrs[NL80211_ATTR_SSID]),
		       params.ssid.ssid_len);
	पूर्ण

	स_नकल(params.bssid, nla_data(info->attrs[NL80211_ATTR_BSSID]),
	       ETH_ALEN);

	params.status = nla_get_u16(info->attrs[NL80211_ATTR_STATUS_CODE]);

	अगर (info->attrs[NL80211_ATTR_PMKID])
		params.pmkid = nla_data(info->attrs[NL80211_ATTR_PMKID]);

	वापस rdev_बाह्यal_auth(rdev, dev, &params);
पूर्ण

अटल पूर्णांक nl80211_tx_control_port(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	bool करोnt_रुको_क्रम_ack = info->attrs[NL80211_ATTR_DONT_WAIT_FOR_ACK];
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	स्थिर u8 *buf;
	माप_प्रकार len;
	u8 *dest;
	u16 proto;
	bool noencrypt;
	u64 cookie = 0;
	पूर्णांक err;

	अगर (!wiphy_ext_feature_isset(&rdev->wiphy,
				     NL80211_EXT_FEATURE_CONTROL_PORT_OVER_NL80211))
		वापस -EOPNOTSUPP;

	अगर (!rdev->ops->tx_control_port)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_FRAME] ||
	    !info->attrs[NL80211_ATTR_MAC] ||
	    !info->attrs[NL80211_ATTR_CONTROL_PORT_ETHERTYPE]) अणु
		GENL_SET_ERR_MSG(info, "Frame, MAC or ethertype missing");
		वापस -EINVAL;
	पूर्ण

	wdev_lock(wdev);

	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_GO:
	हाल NL80211_IFTYPE_MESH_POINT:
		अवरोध;
	हाल NL80211_IFTYPE_ADHOC:
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
		अगर (wdev->current_bss)
			अवरोध;
		err = -ENOTCONN;
		जाओ out;
	शेष:
		err = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	wdev_unlock(wdev);

	buf = nla_data(info->attrs[NL80211_ATTR_FRAME]);
	len = nla_len(info->attrs[NL80211_ATTR_FRAME]);
	dest = nla_data(info->attrs[NL80211_ATTR_MAC]);
	proto = nla_get_u16(info->attrs[NL80211_ATTR_CONTROL_PORT_ETHERTYPE]);
	noencrypt =
		nla_get_flag(info->attrs[NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT]);

	err = rdev_tx_control_port(rdev, dev, buf, len,
				   dest, cpu_to_be16(proto), noencrypt,
				   करोnt_रुको_क्रम_ack ? शून्य : &cookie);
	अगर (!err && !करोnt_रुको_क्रम_ack)
		nl_set_extack_cookie_u64(info->extack, cookie);
	वापस err;
 out:
	wdev_unlock(wdev);
	वापस err;
पूर्ण

अटल पूर्णांक nl80211_get_fपंचांग_responder_stats(काष्ठा sk_buff *skb,
					   काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_fपंचांग_responder_stats fपंचांग_stats = अणुपूर्ण;
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	काष्ठा nlattr *fपंचांग_stats_attr;
	पूर्णांक err;

	अगर (wdev->अगरtype != NL80211_IFTYPE_AP || !wdev->beacon_पूर्णांकerval)
		वापस -EOPNOTSUPP;

	err = rdev_get_fपंचांग_responder_stats(rdev, dev, &fपंचांग_stats);
	अगर (err)
		वापस err;

	अगर (!fपंचांग_stats.filled)
		वापस -ENODATA;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_FTM_RESPONDER_STATS);
	अगर (!hdr)
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	fपंचांग_stats_attr = nla_nest_start_noflag(msg,
					       NL80211_ATTR_FTM_RESPONDER_STATS);
	अगर (!fपंचांग_stats_attr)
		जाओ nla_put_failure;

#घोषणा SET_FTM(field, name, type)					 \
	करो अणु अगर ((fपंचांग_stats.filled & BIT(NL80211_FTM_STATS_ ## name)) && \
	    nla_put_ ## type(msg, NL80211_FTM_STATS_ ## name,		 \
			     fपंचांग_stats.field))				 \
		जाओ nla_put_failure; पूर्ण जबतक (0)
#घोषणा SET_FTM_U64(field, name)					 \
	करो अणु अगर ((fपंचांग_stats.filled & BIT(NL80211_FTM_STATS_ ## name)) && \
	    nla_put_u64_64bit(msg, NL80211_FTM_STATS_ ## name,		 \
			      fपंचांग_stats.field, NL80211_FTM_STATS_PAD))	 \
		जाओ nla_put_failure; पूर्ण जबतक (0)

	SET_FTM(success_num, SUCCESS_NUM, u32);
	SET_FTM(partial_num, PARTIAL_NUM, u32);
	SET_FTM(failed_num, FAILED_NUM, u32);
	SET_FTM(asap_num, ASAP_NUM, u32);
	SET_FTM(non_asap_num, NON_ASAP_NUM, u32);
	SET_FTM_U64(total_duration_ms, TOTAL_DURATION_MSEC);
	SET_FTM(unknown_triggers_num, UNKNOWN_TRIGGERS_NUM, u32);
	SET_FTM(reschedule_requests_num, RESCHEDULE_REQUESTS_NUM, u32);
	SET_FTM(out_of_winकरोw_triggers_num, OUT_OF_WINDOW_TRIGGERS_NUM, u32);
#अघोषित SET_FTM

	nla_nest_end(msg, fपंचांग_stats_attr);

	genlmsg_end(msg, hdr);
	वापस genlmsg_reply(msg, info);

nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक nl80211_update_owe_info(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा cfg80211_update_owe_info owe_info;
	काष्ठा net_device *dev = info->user_ptr[1];

	अगर (!rdev->ops->update_owe_info)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_STATUS_CODE] ||
	    !info->attrs[NL80211_ATTR_MAC])
		वापस -EINVAL;

	स_रखो(&owe_info, 0, माप(owe_info));
	owe_info.status = nla_get_u16(info->attrs[NL80211_ATTR_STATUS_CODE]);
	nla_स_नकल(owe_info.peer, info->attrs[NL80211_ATTR_MAC], ETH_ALEN);

	अगर (info->attrs[NL80211_ATTR_IE]) अणु
		owe_info.ie = nla_data(info->attrs[NL80211_ATTR_IE]);
		owe_info.ie_len = nla_len(info->attrs[NL80211_ATTR_IE]);
	पूर्ण

	वापस rdev_update_owe_info(rdev, dev, &owe_info);
पूर्ण

अटल पूर्णांक nl80211_probe_mesh_link(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा station_info sinfo = अणुपूर्ण;
	स्थिर u8 *buf;
	माप_प्रकार len;
	u8 *dest;
	पूर्णांक err;

	अगर (!rdev->ops->probe_mesh_link || !rdev->ops->get_station)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_MAC] ||
	    !info->attrs[NL80211_ATTR_FRAME]) अणु
		GENL_SET_ERR_MSG(info, "Frame or MAC missing");
		वापस -EINVAL;
	पूर्ण

	अगर (wdev->अगरtype != NL80211_IFTYPE_MESH_POINT)
		वापस -EOPNOTSUPP;

	dest = nla_data(info->attrs[NL80211_ATTR_MAC]);
	buf = nla_data(info->attrs[NL80211_ATTR_FRAME]);
	len = nla_len(info->attrs[NL80211_ATTR_FRAME]);

	अगर (len < माप(काष्ठा ethhdr))
		वापस -EINVAL;

	अगर (!ether_addr_equal(buf, dest) || is_multicast_ether_addr(buf) ||
	    !ether_addr_equal(buf + ETH_ALEN, dev->dev_addr))
		वापस -EINVAL;

	err = rdev_get_station(rdev, dev, dest, &sinfo);
	अगर (err)
		वापस err;

	cfg80211_sinfo_release_content(&sinfo);

	वापस rdev_probe_mesh_link(rdev, dev, dest, buf, len);
पूर्ण

अटल पूर्णांक parse_tid_conf(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा nlattr *attrs[], काष्ठा net_device *dev,
			  काष्ठा cfg80211_tid_cfg *tid_conf,
			  काष्ठा genl_info *info, स्थिर u8 *peer)
अणु
	काष्ठा netlink_ext_ack *extack = info->extack;
	u64 mask;
	पूर्णांक err;

	अगर (!attrs[NL80211_TID_CONFIG_ATTR_TIDS])
		वापस -EINVAL;

	tid_conf->config_override =
			nla_get_flag(attrs[NL80211_TID_CONFIG_ATTR_OVERRIDE]);
	tid_conf->tids = nla_get_u16(attrs[NL80211_TID_CONFIG_ATTR_TIDS]);

	अगर (tid_conf->config_override) अणु
		अगर (rdev->ops->reset_tid_config) अणु
			err = rdev_reset_tid_config(rdev, dev, peer,
						    tid_conf->tids);
			अगर (err)
				वापस err;
		पूर्ण अन्यथा अणु
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (attrs[NL80211_TID_CONFIG_ATTR_NOACK]) अणु
		tid_conf->mask |= BIT(NL80211_TID_CONFIG_ATTR_NOACK);
		tid_conf->noack =
			nla_get_u8(attrs[NL80211_TID_CONFIG_ATTR_NOACK]);
	पूर्ण

	अगर (attrs[NL80211_TID_CONFIG_ATTR_RETRY_SHORT]) अणु
		tid_conf->mask |= BIT(NL80211_TID_CONFIG_ATTR_RETRY_SHORT);
		tid_conf->retry_लघु =
			nla_get_u8(attrs[NL80211_TID_CONFIG_ATTR_RETRY_SHORT]);

		अगर (tid_conf->retry_लघु > rdev->wiphy.max_data_retry_count)
			वापस -EINVAL;
	पूर्ण

	अगर (attrs[NL80211_TID_CONFIG_ATTR_RETRY_LONG]) अणु
		tid_conf->mask |= BIT(NL80211_TID_CONFIG_ATTR_RETRY_LONG);
		tid_conf->retry_दीर्घ =
			nla_get_u8(attrs[NL80211_TID_CONFIG_ATTR_RETRY_LONG]);

		अगर (tid_conf->retry_दीर्घ > rdev->wiphy.max_data_retry_count)
			वापस -EINVAL;
	पूर्ण

	अगर (attrs[NL80211_TID_CONFIG_ATTR_AMPDU_CTRL]) अणु
		tid_conf->mask |= BIT(NL80211_TID_CONFIG_ATTR_AMPDU_CTRL);
		tid_conf->ampdu =
			nla_get_u8(attrs[NL80211_TID_CONFIG_ATTR_AMPDU_CTRL]);
	पूर्ण

	अगर (attrs[NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL]) अणु
		tid_conf->mask |= BIT(NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL);
		tid_conf->rtscts =
			nla_get_u8(attrs[NL80211_TID_CONFIG_ATTR_RTSCTS_CTRL]);
	पूर्ण

	अगर (attrs[NL80211_TID_CONFIG_ATTR_AMSDU_CTRL]) अणु
		tid_conf->mask |= BIT(NL80211_TID_CONFIG_ATTR_AMSDU_CTRL);
		tid_conf->amsdu =
			nla_get_u8(attrs[NL80211_TID_CONFIG_ATTR_AMSDU_CTRL]);
	पूर्ण

	अगर (attrs[NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE]) अणु
		u32 idx = NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE, attr;

		tid_conf->txrate_type = nla_get_u8(attrs[idx]);

		अगर (tid_conf->txrate_type != NL80211_TX_RATE_AUTOMATIC) अणु
			attr = NL80211_TID_CONFIG_ATTR_TX_RATE;
			err = nl80211_parse_tx_bitrate_mask(info, attrs, attr,
						    &tid_conf->txrate_mask, dev,
						    true);
			अगर (err)
				वापस err;

			tid_conf->mask |= BIT(NL80211_TID_CONFIG_ATTR_TX_RATE);
		पूर्ण
		tid_conf->mask |= BIT(NL80211_TID_CONFIG_ATTR_TX_RATE_TYPE);
	पूर्ण

	अगर (peer)
		mask = rdev->wiphy.tid_config_support.peer;
	अन्यथा
		mask = rdev->wiphy.tid_config_support.vअगर;

	अगर (tid_conf->mask & ~mask) अणु
		NL_SET_ERR_MSG(extack, "unsupported TID configuration");
		वापस -ENOTSUPP;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_set_tid_config(काष्ठा sk_buff *skb,
				  काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा nlattr *attrs[NL80211_TID_CONFIG_ATTR_MAX + 1];
	काष्ठा net_device *dev = info->user_ptr[1];
	काष्ठा cfg80211_tid_config *tid_config;
	काष्ठा nlattr *tid;
	पूर्णांक conf_idx = 0, rem_conf;
	पूर्णांक ret = -EINVAL;
	u32 num_conf = 0;

	अगर (!info->attrs[NL80211_ATTR_TID_CONFIG])
		वापस -EINVAL;

	अगर (!rdev->ops->set_tid_config)
		वापस -EOPNOTSUPP;

	nla_क्रम_each_nested(tid, info->attrs[NL80211_ATTR_TID_CONFIG],
			    rem_conf)
		num_conf++;

	tid_config = kzalloc(काष्ठा_size(tid_config, tid_conf, num_conf),
			     GFP_KERNEL);
	अगर (!tid_config)
		वापस -ENOMEM;

	tid_config->n_tid_conf = num_conf;

	अगर (info->attrs[NL80211_ATTR_MAC])
		tid_config->peer = nla_data(info->attrs[NL80211_ATTR_MAC]);

	nla_क्रम_each_nested(tid, info->attrs[NL80211_ATTR_TID_CONFIG],
			    rem_conf) अणु
		ret = nla_parse_nested(attrs, NL80211_TID_CONFIG_ATTR_MAX,
				       tid, शून्य, शून्य);

		अगर (ret)
			जाओ bad_tid_conf;

		ret = parse_tid_conf(rdev, attrs, dev,
				     &tid_config->tid_conf[conf_idx],
				     info, tid_config->peer);
		अगर (ret)
			जाओ bad_tid_conf;

		conf_idx++;
	पूर्ण

	ret = rdev_set_tid_config(rdev, dev, tid_config);

bad_tid_conf:
	kमुक्त(tid_config);
	वापस ret;
पूर्ण

#घोषणा NL80211_FLAG_NEED_WIPHY		0x01
#घोषणा NL80211_FLAG_NEED_NETDEV	0x02
#घोषणा NL80211_FLAG_NEED_RTNL		0x04
#घोषणा NL80211_FLAG_CHECK_NETDEV_UP	0x08
#घोषणा NL80211_FLAG_NEED_NETDEV_UP	(NL80211_FLAG_NEED_NETDEV |\
					 NL80211_FLAG_CHECK_NETDEV_UP)
#घोषणा NL80211_FLAG_NEED_WDEV		0x10
/* If a netdev is associated, it must be UP, P2P must be started */
#घोषणा NL80211_FLAG_NEED_WDEV_UP	(NL80211_FLAG_NEED_WDEV |\
					 NL80211_FLAG_CHECK_NETDEV_UP)
#घोषणा NL80211_FLAG_CLEAR_SKB		0x20
#घोषणा NL80211_FLAG_NO_WIPHY_MTX	0x40

अटल पूर्णांक nl80211_pre_करोit(स्थिर काष्ठा genl_ops *ops, काष्ठा sk_buff *skb,
			    काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = शून्य;
	काष्ठा wireless_dev *wdev;
	काष्ठा net_device *dev;

	rtnl_lock();
	अगर (ops->पूर्णांकernal_flags & NL80211_FLAG_NEED_WIPHY) अणु
		rdev = cfg80211_get_dev_from_info(genl_info_net(info), info);
		अगर (IS_ERR(rdev)) अणु
			rtnl_unlock();
			वापस PTR_ERR(rdev);
		पूर्ण
		info->user_ptr[0] = rdev;
	पूर्ण अन्यथा अगर (ops->पूर्णांकernal_flags & NL80211_FLAG_NEED_NETDEV ||
		   ops->पूर्णांकernal_flags & NL80211_FLAG_NEED_WDEV) अणु
		wdev = __cfg80211_wdev_from_attrs(शून्य, genl_info_net(info),
						  info->attrs);
		अगर (IS_ERR(wdev)) अणु
			rtnl_unlock();
			वापस PTR_ERR(wdev);
		पूर्ण

		dev = wdev->netdev;
		rdev = wiphy_to_rdev(wdev->wiphy);

		अगर (ops->पूर्णांकernal_flags & NL80211_FLAG_NEED_NETDEV) अणु
			अगर (!dev) अणु
				rtnl_unlock();
				वापस -EINVAL;
			पूर्ण

			info->user_ptr[1] = dev;
		पूर्ण अन्यथा अणु
			info->user_ptr[1] = wdev;
		पूर्ण

		अगर (ops->पूर्णांकernal_flags & NL80211_FLAG_CHECK_NETDEV_UP &&
		    !wdev_running(wdev)) अणु
			rtnl_unlock();
			वापस -ENETDOWN;
		पूर्ण

		अगर (dev)
			dev_hold(dev);

		info->user_ptr[0] = rdev;
	पूर्ण

	अगर (rdev && !(ops->पूर्णांकernal_flags & NL80211_FLAG_NO_WIPHY_MTX)) अणु
		wiphy_lock(&rdev->wiphy);
		/* we keep the mutex locked until post_करोit */
		__release(&rdev->wiphy.mtx);
	पूर्ण
	अगर (!(ops->पूर्णांकernal_flags & NL80211_FLAG_NEED_RTNL))
		rtnl_unlock();

	वापस 0;
पूर्ण

अटल व्योम nl80211_post_करोit(स्थिर काष्ठा genl_ops *ops, काष्ठा sk_buff *skb,
			      काष्ठा genl_info *info)
अणु
	अगर (info->user_ptr[1]) अणु
		अगर (ops->पूर्णांकernal_flags & NL80211_FLAG_NEED_WDEV) अणु
			काष्ठा wireless_dev *wdev = info->user_ptr[1];

			अगर (wdev->netdev)
				dev_put(wdev->netdev);
		पूर्ण अन्यथा अणु
			dev_put(info->user_ptr[1]);
		पूर्ण
	पूर्ण

	अगर (info->user_ptr[0] &&
	    !(ops->पूर्णांकernal_flags & NL80211_FLAG_NO_WIPHY_MTX)) अणु
		काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];

		/* we kept the mutex locked since pre_करोit */
		__acquire(&rdev->wiphy.mtx);
		wiphy_unlock(&rdev->wiphy);
	पूर्ण

	अगर (ops->पूर्णांकernal_flags & NL80211_FLAG_NEED_RTNL)
		rtnl_unlock();

	/* If needed, clear the netlink message payload from the SKB
	 * as it might contain key data that shouldn't stick around on
	 * the heap after the SKB is मुक्तd. The netlink message header
	 * is still needed क्रम further processing, so leave it पूर्णांकact.
	 */
	अगर (ops->पूर्णांकernal_flags & NL80211_FLAG_CLEAR_SKB) अणु
		काष्ठा nlmsghdr *nlh = nlmsg_hdr(skb);

		स_रखो(nlmsg_data(nlh), 0, nlmsg_len(nlh));
	पूर्ण
पूर्ण

अटल पूर्णांक nl80211_set_sar_sub_specs(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा cfg80211_sar_specs *sar_specs,
				     काष्ठा nlattr *spec[], पूर्णांक index)
अणु
	u32 range_index, i;

	अगर (!sar_specs || !spec)
		वापस -EINVAL;

	अगर (!spec[NL80211_SAR_ATTR_SPECS_POWER] ||
	    !spec[NL80211_SAR_ATTR_SPECS_RANGE_INDEX])
		वापस -EINVAL;

	range_index = nla_get_u32(spec[NL80211_SAR_ATTR_SPECS_RANGE_INDEX]);

	/* check अगर range_index exceeds num_freq_ranges */
	अगर (range_index >= rdev->wiphy.sar_capa->num_freq_ranges)
		वापस -EINVAL;

	/* check अगर range_index duplicates */
	क्रम (i = 0; i < index; i++) अणु
		अगर (sar_specs->sub_specs[i].freq_range_index == range_index)
			वापस -EINVAL;
	पूर्ण

	sar_specs->sub_specs[index].घातer =
		nla_get_s32(spec[NL80211_SAR_ATTR_SPECS_POWER]);

	sar_specs->sub_specs[index].freq_range_index = range_index;

	वापस 0;
पूर्ण

अटल पूर्णांक nl80211_set_sar_specs(काष्ठा sk_buff *skb, काष्ठा genl_info *info)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = info->user_ptr[0];
	काष्ठा nlattr *spec[NL80211_SAR_ATTR_SPECS_MAX + 1];
	काष्ठा nlattr *tb[NL80211_SAR_ATTR_MAX + 1];
	काष्ठा cfg80211_sar_specs *sar_spec;
	क्रमागत nl80211_sar_type type;
	काष्ठा nlattr *spec_list;
	u32 specs;
	पूर्णांक rem, err;

	अगर (!rdev->wiphy.sar_capa || !rdev->ops->set_sar_specs)
		वापस -EOPNOTSUPP;

	अगर (!info->attrs[NL80211_ATTR_SAR_SPEC])
		वापस -EINVAL;

	nla_parse_nested(tb, NL80211_SAR_ATTR_MAX,
			 info->attrs[NL80211_ATTR_SAR_SPEC],
			 शून्य, शून्य);

	अगर (!tb[NL80211_SAR_ATTR_TYPE] || !tb[NL80211_SAR_ATTR_SPECS])
		वापस -EINVAL;

	type = nla_get_u32(tb[NL80211_SAR_ATTR_TYPE]);
	अगर (type != rdev->wiphy.sar_capa->type)
		वापस -EINVAL;

	specs = 0;
	nla_क्रम_each_nested(spec_list, tb[NL80211_SAR_ATTR_SPECS], rem)
		specs++;

	अगर (specs > rdev->wiphy.sar_capa->num_freq_ranges)
		वापस -EINVAL;

	sar_spec = kzalloc(माप(*sar_spec) +
			   specs * माप(काष्ठा cfg80211_sar_sub_specs),
			   GFP_KERNEL);
	अगर (!sar_spec)
		वापस -ENOMEM;

	sar_spec->type = type;
	specs = 0;
	nla_क्रम_each_nested(spec_list, tb[NL80211_SAR_ATTR_SPECS], rem) अणु
		nla_parse_nested(spec, NL80211_SAR_ATTR_SPECS_MAX,
				 spec_list, शून्य, शून्य);

		चयन (type) अणु
		हाल NL80211_SAR_TYPE_POWER:
			अगर (nl80211_set_sar_sub_specs(rdev, sar_spec,
						      spec, specs)) अणु
				err = -EINVAL;
				जाओ error;
			पूर्ण
			अवरोध;
		शेष:
			err = -EINVAL;
			जाओ error;
		पूर्ण
		specs++;
	पूर्ण

	sar_spec->num_sub_specs = specs;

	rdev->cur_cmd_info = info;
	err = rdev_set_sar_specs(rdev, sar_spec);
	rdev->cur_cmd_info = शून्य;
error:
	kमुक्त(sar_spec);
	वापस err;
पूर्ण

अटल स्थिर काष्ठा genl_ops nl80211_ops[] = अणु
	अणु
		.cmd = NL80211_CMD_GET_WIPHY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_wiphy,
		.dumpit = nl80211_dump_wiphy,
		.करोne = nl80211_dump_wiphy_करोne,
		/* can be retrieved by unprivileged users */
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा genl_small_ops nl80211_small_ops[] = अणु
	अणु
		.cmd = NL80211_CMD_SET_WIPHY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_wiphy,
		.flags = GENL_UNS_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_पूर्णांकerface,
		.dumpit = nl80211_dump_पूर्णांकerface,
		/* can be retrieved by unprivileged users */
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_पूर्णांकerface,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV |
				  NL80211_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_NEW_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_new_पूर्णांकerface,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY |
				  NL80211_FLAG_NEED_RTNL |
				  /* we take the wiphy mutex later ourselves */
				  NL80211_FLAG_NO_WIPHY_MTX,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEL_INTERFACE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_del_पूर्णांकerface,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV |
				  NL80211_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_KEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_key,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_KEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_key,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_NEW_KEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_new_key,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEL_KEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_del_key,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_BEACON,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_UNS_ADMIN_PERM,
		.करोit = nl80211_set_beacon,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_START_AP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_UNS_ADMIN_PERM,
		.करोit = nl80211_start_ap,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_STOP_AP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.flags = GENL_UNS_ADMIN_PERM,
		.करोit = nl80211_stop_ap,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_STATION,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_station,
		.dumpit = nl80211_dump_station,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_STATION,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_station,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_NEW_STATION,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_new_station,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEL_STATION,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_del_station,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_MPATH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_mpath,
		.dumpit = nl80211_dump_mpath,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_MPP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_mpp,
		.dumpit = nl80211_dump_mpp,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_MPATH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_mpath,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_NEW_MPATH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_new_mpath,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEL_MPATH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_del_mpath,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_BSS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_bss,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_REG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_reg_करो,
		.dumpit = nl80211_get_reg_dump,
		.पूर्णांकernal_flags = 0,
		/* can be retrieved by unprivileged users */
	पूर्ण,
#अगर_घोषित CONFIG_CFG80211_CRDA_SUPPORT
	अणु
		.cmd = NL80211_CMD_SET_REG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_reg,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = 0,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.cmd = NL80211_CMD_REQ_SET_REG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_req_set_reg,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_RELOAD_REGDB,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_reload_regdb,
		.flags = GENL_ADMIN_PERM,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_MESH_CONFIG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_mesh_config,
		/* can be retrieved by unprivileged users */
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_MESH_CONFIG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_update_mesh_config,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_TRIGGER_SCAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_trigger_scan,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_ABORT_SCAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_पात_scan,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_SCAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit = nl80211_dump_scan,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_START_SCHED_SCAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_start_sched_scan,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_STOP_SCHED_SCAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_stop_sched_scan,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_AUTHENTICATE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_authenticate,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  0 |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_ASSOCIATE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_associate,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  0 |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEAUTHENTICATE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_deauthenticate,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DISASSOCIATE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_disassociate,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_JOIN_IBSS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_join_ibss,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_LEAVE_IBSS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_leave_ibss,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
#अगर_घोषित CONFIG_NL80211_TESTMODE
	अणु
		.cmd = NL80211_CMD_TESTMODE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_tesपंचांगode_करो,
		.dumpit = nl80211_tesपंचांगode_dump,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.cmd = NL80211_CMD_CONNECT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_connect,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  0 |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_UPDATE_CONNECT_PARAMS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_update_connect_params,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  0 |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DISCONNECT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_disconnect,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_WIPHY_NETNS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_wiphy_netns,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY |
				  NL80211_FLAG_NEED_RTNL |
				  NL80211_FLAG_NO_WIPHY_MTX,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_SURVEY,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.dumpit = nl80211_dump_survey,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_PMKSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_setdel_pmksa,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  0 |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEL_PMKSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_setdel_pmksa,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_FLUSH_PMKSA,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_flush_pmksa,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_REMAIN_ON_CHANNEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_reमुख्य_on_channel,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_CANCEL_REMAIN_ON_CHANNEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_cancel_reमुख्य_on_channel,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_TX_BITRATE_MASK,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_tx_bitrate_mask,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_REGISTER_FRAME,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_रेजिस्टर_mgmt,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_FRAME,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_tx_mgmt,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_FRAME_WAIT_CANCEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_tx_mgmt_cancel_रुको,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_POWER_SAVE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_घातer_save,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_POWER_SAVE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_घातer_save,
		/* can be retrieved by unprivileged users */
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_CQM,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_cqm,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_CHANNEL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_channel,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_JOIN_MESH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_join_mesh,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_LEAVE_MESH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_leave_mesh,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_JOIN_OCB,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_join_ocb,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_LEAVE_OCB,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_leave_ocb,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
#अगर_घोषित CONFIG_PM
	अणु
		.cmd = NL80211_CMD_GET_WOWLAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_wowlan,
		/* can be retrieved by unprivileged users */
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_WOWLAN,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_wowlan,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY,
	पूर्ण,
#पूर्ण_अगर
	अणु
		.cmd = NL80211_CMD_SET_REKEY_OFFLOAD,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_rekey_data,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  0 |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_TDLS_MGMT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_tdls_mgmt,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_TDLS_OPER,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_tdls_oper,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_UNEXPECTED_FRAME,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_रेजिस्टर_unexpected_frame,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_PROBE_CLIENT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_probe_client,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_REGISTER_BEACONS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_रेजिस्टर_beacons,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_NOACK_MAP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_noack_map,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_START_P2P_DEVICE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_start_p2p_device,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV |
				  NL80211_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_STOP_P2P_DEVICE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_stop_p2p_device,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP |
				  NL80211_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_START_न_अंक,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_start_nan,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV |
				  NL80211_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_STOP_न_अंक,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_stop_nan,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP |
				  NL80211_FLAG_NEED_RTNL,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_ADD_न_अंक_FUNCTION,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_nan_add_func,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEL_न_अंक_FUNCTION,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_nan_del_func,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_CHANGE_न_अंक_CONFIG,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_nan_change_config,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_MCAST_RATE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_mcast_rate,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_MAC_ACL,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_mac_acl,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_RADAR_DETECT,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_start_radar_detection,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_PROTOCOL_FEATURES,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_protocol_features,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_UPDATE_FT_IES,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_update_ft_ies,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_CRIT_PROTOCOL_START,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_crit_protocol_start,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_CRIT_PROTOCOL_STOP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_crit_protocol_stop,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_COALESCE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_coalesce,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_COALESCE,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_coalesce,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_CHANNEL_SWITCH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_channel_चयन,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_VENDOR,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_venकरोr_cmd,
		.dumpit = nl80211_venकरोr_cmd_dump,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY |
				  0 |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_QOS_MAP,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_qos_map,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_ADD_TX_TS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_add_tx_ts,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEL_TX_TS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_del_tx_ts,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_TDLS_CHANNEL_SWITCH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_tdls_channel_चयन,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_TDLS_CANCEL_CHANNEL_SWITCH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_tdls_cancel_channel_चयन,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_MULTICAST_TO_UNICAST,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_multicast_to_unicast,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_PMK,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_pmk,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP |
				  0 |
				  NL80211_FLAG_CLEAR_SKB,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_DEL_PMK,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_del_pmk,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_EXTERNAL_AUTH,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_बाह्यal_auth,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_CONTROL_PORT_FRAME,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_tx_control_port,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_GET_FTM_RESPONDER_STATS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_get_fपंचांग_responder_stats,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_PEER_MEASUREMENT_START,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_pmsr_start,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_NOTIFY_RADAR,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_notअगरy_radar_detection,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_UPDATE_OWE_INFO,
		.करोit = nl80211_update_owe_info,
		.flags = GENL_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_PROBE_MESH_LINK,
		.करोit = nl80211_probe_mesh_link,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV_UP,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_TID_CONFIG,
		.करोit = nl80211_set_tid_config,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_NETDEV,
	पूर्ण,
	अणु
		.cmd = NL80211_CMD_SET_SAR_SPECS,
		.validate = GENL_DONT_VALIDATE_STRICT | GENL_DONT_VALIDATE_DUMP,
		.करोit = nl80211_set_sar_specs,
		.flags = GENL_UNS_ADMIN_PERM,
		.पूर्णांकernal_flags = NL80211_FLAG_NEED_WIPHY |
				  NL80211_FLAG_NEED_RTNL,
	पूर्ण,
पूर्ण;

अटल काष्ठा genl_family nl80211_fam __ro_after_init = अणु
	.name = NL80211_GENL_NAME,	/* have users key off the name instead */
	.hdrsize = 0,			/* no निजी header */
	.version = 1,			/* no particular meaning now */
	.maxattr = NL80211_ATTR_MAX,
	.policy = nl80211_policy,
	.netnsok = true,
	.pre_करोit = nl80211_pre_करोit,
	.post_करोit = nl80211_post_करोit,
	.module = THIS_MODULE,
	.ops = nl80211_ops,
	.n_ops = ARRAY_SIZE(nl80211_ops),
	.small_ops = nl80211_small_ops,
	.n_small_ops = ARRAY_SIZE(nl80211_small_ops),
	.mcgrps = nl80211_mcgrps,
	.n_mcgrps = ARRAY_SIZE(nl80211_mcgrps),
	.parallel_ops = true,
पूर्ण;

/* notअगरication functions */

व्योम nl80211_notअगरy_wiphy(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  क्रमागत nl80211_commands cmd)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा nl80211_dump_wiphy_state state = अणुपूर्ण;

	WARN_ON(cmd != NL80211_CMD_NEW_WIPHY &&
		cmd != NL80211_CMD_DEL_WIPHY);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	अगर (nl80211_send_wiphy(rdev, cmd, msg, 0, 0, 0, &state) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

व्योम nl80211_notअगरy_अगरace(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा wireless_dev *wdev,
				क्रमागत nl80211_commands cmd)
अणु
	काष्ठा sk_buff *msg;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	अगर (nl80211_send_अगरace(msg, 0, 0, 0, rdev, wdev, cmd) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_CONFIG, GFP_KERNEL);
पूर्ण

अटल पूर्णांक nl80211_add_scan_req(काष्ठा sk_buff *msg,
				काष्ठा cfg80211_रेजिस्टरed_device *rdev)
अणु
	काष्ठा cfg80211_scan_request *req = rdev->scan_req;
	काष्ठा nlattr *nest;
	पूर्णांक i;
	काष्ठा cfg80211_scan_info *info;

	अगर (WARN_ON(!req))
		वापस 0;

	nest = nla_nest_start_noflag(msg, NL80211_ATTR_SCAN_SSIDS);
	अगर (!nest)
		जाओ nla_put_failure;
	क्रम (i = 0; i < req->n_ssids; i++) अणु
		अगर (nla_put(msg, i, req->ssids[i].ssid_len, req->ssids[i].ssid))
			जाओ nla_put_failure;
	पूर्ण
	nla_nest_end(msg, nest);

	अगर (req->flags & NL80211_SCAN_FLAG_FREQ_KHZ) अणु
		nest = nla_nest_start(msg, NL80211_ATTR_SCAN_FREQ_KHZ);
		अगर (!nest)
			जाओ nla_put_failure;
		क्रम (i = 0; i < req->n_channels; i++) अणु
			अगर (nla_put_u32(msg, i,
				   ieee80211_channel_to_khz(req->channels[i])))
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(msg, nest);
	पूर्ण अन्यथा अणु
		nest = nla_nest_start_noflag(msg,
					     NL80211_ATTR_SCAN_FREQUENCIES);
		अगर (!nest)
			जाओ nla_put_failure;
		क्रम (i = 0; i < req->n_channels; i++) अणु
			अगर (nla_put_u32(msg, i, req->channels[i]->center_freq))
				जाओ nla_put_failure;
		पूर्ण
		nla_nest_end(msg, nest);
	पूर्ण

	अगर (req->ie &&
	    nla_put(msg, NL80211_ATTR_IE, req->ie_len, req->ie))
		जाओ nla_put_failure;

	अगर (req->flags &&
	    nla_put_u32(msg, NL80211_ATTR_SCAN_FLAGS, req->flags))
		जाओ nla_put_failure;

	info = rdev->पूर्णांक_scan_req ? &rdev->पूर्णांक_scan_req->info :
		&rdev->scan_req->info;
	अगर (info->scan_start_tsf &&
	    (nla_put_u64_64bit(msg, NL80211_ATTR_SCAN_START_TIME_TSF,
			       info->scan_start_tsf, NL80211_BSS_PAD) ||
	     nla_put(msg, NL80211_ATTR_SCAN_START_TIME_TSF_BSSID, ETH_ALEN,
		     info->tsf_bssid)))
		जाओ nla_put_failure;

	वापस 0;
 nla_put_failure:
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक nl80211_prep_scan_msg(काष्ठा sk_buff *msg,
				 काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा wireless_dev *wdev,
				 u32 portid, u32 seq, पूर्णांक flags,
				 u32 cmd)
अणु
	व्योम *hdr;

	hdr = nl80211hdr_put(msg, portid, seq, flags, cmd);
	अगर (!hdr)
		वापस -1;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    (wdev->netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
					 wdev->netdev->अगरindex)) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	/* ignore errors and send incomplete event anyway */
	nl80211_add_scan_req(msg, rdev);

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

अटल पूर्णांक
nl80211_prep_sched_scan_msg(काष्ठा sk_buff *msg,
			    काष्ठा cfg80211_sched_scan_request *req, u32 cmd)
अणु
	व्योम *hdr;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd);
	अगर (!hdr)
		वापस -1;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY,
			wiphy_to_rdev(req->wiphy)->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, req->dev->अगरindex) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, req->reqid,
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	वापस 0;

 nla_put_failure:
	genlmsg_cancel(msg, hdr);
	वापस -EMSGSIZE;
पूर्ण

व्योम nl80211_send_scan_start(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			     काष्ठा wireless_dev *wdev)
अणु
	काष्ठा sk_buff *msg;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	अगर (nl80211_prep_scan_msg(msg, rdev, wdev, 0, 0, 0,
				  NL80211_CMD_TRIGGER_SCAN) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_SCAN, GFP_KERNEL);
पूर्ण

काष्ठा sk_buff *nl80211_build_scan_msg(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				       काष्ठा wireless_dev *wdev, bool पातed)
अणु
	काष्ठा sk_buff *msg;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस शून्य;

	अगर (nl80211_prep_scan_msg(msg, rdev, wdev, 0, 0, 0,
				  पातed ? NL80211_CMD_SCAN_ABORTED :
					    NL80211_CMD_NEW_SCAN_RESULTS) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस शून्य;
	पूर्ण

	वापस msg;
पूर्ण

/* send message created by nl80211_build_scan_msg() */
व्योम nl80211_send_scan_msg(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा sk_buff *msg)
अणु
	अगर (!msg)
		वापस;

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_SCAN, GFP_KERNEL);
पूर्ण

व्योम nl80211_send_sched_scan(काष्ठा cfg80211_sched_scan_request *req, u32 cmd)
अणु
	काष्ठा sk_buff *msg;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	अगर (nl80211_prep_sched_scan_msg(msg, req, cmd) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(req->wiphy), msg, 0,
				NL80211_MCGRP_SCAN, GFP_KERNEL);
पूर्ण

अटल bool nl80211_reg_change_event_fill(काष्ठा sk_buff *msg,
					  काष्ठा regulatory_request *request)
अणु
	/* Userspace can always count this one always being set */
	अगर (nla_put_u8(msg, NL80211_ATTR_REG_INITIATOR, request->initiator))
		जाओ nla_put_failure;

	अगर (request->alpha2[0] == '0' && request->alpha2[1] == '0') अणु
		अगर (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_WORLD))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अगर (request->alpha2[0] == '9' && request->alpha2[1] == '9') अणु
		अगर (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_CUSTOM_WORLD))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अगर ((request->alpha2[0] == '9' && request->alpha2[1] == '8') ||
		   request->पूर्णांकersect) अणु
		अगर (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_INTERSECTION))
			जाओ nla_put_failure;
	पूर्ण अन्यथा अणु
		अगर (nla_put_u8(msg, NL80211_ATTR_REG_TYPE,
			       NL80211_REGDOM_TYPE_COUNTRY) ||
		    nla_put_string(msg, NL80211_ATTR_REG_ALPHA2,
				   request->alpha2))
			जाओ nla_put_failure;
	पूर्ण

	अगर (request->wiphy_idx != WIPHY_IDX_INVALID) अणु
		काष्ठा wiphy *wiphy = wiphy_idx_to_wiphy(request->wiphy_idx);

		अगर (wiphy &&
		    nla_put_u32(msg, NL80211_ATTR_WIPHY, request->wiphy_idx))
			जाओ nla_put_failure;

		अगर (wiphy &&
		    wiphy->regulatory_flags & REGULATORY_WIPHY_SELF_MANAGED &&
		    nla_put_flag(msg, NL80211_ATTR_WIPHY_SELF_MANAGED_REG))
			जाओ nla_put_failure;
	पूर्ण

	वापस true;

nla_put_failure:
	वापस false;
पूर्ण

/*
 * This can happen on global regulatory changes or device specअगरic settings
 * based on custom regulatory करोमुख्यs.
 */
व्योम nl80211_common_reg_change_event(क्रमागत nl80211_commands cmd_id,
				     काष्ठा regulatory_request *request)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd_id);
	अगर (!hdr)
		जाओ nla_put_failure;

	अगर (!nl80211_reg_change_event_fill(msg, request))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	rcu_पढ़ो_lock();
	genlmsg_multicast_allns(&nl80211_fam, msg, 0,
				NL80211_MCGRP_REGULATORY, GFP_ATOMIC);
	rcu_पढ़ो_unlock();

	वापस;

nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

अटल व्योम nl80211_send_mlme_event(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				    काष्ठा net_device *netdev,
				    स्थिर u8 *buf, माप_प्रकार len,
				    क्रमागत nl80211_commands cmd, gfp_t gfp,
				    पूर्णांक uapsd_queues, स्थिर u8 *req_ies,
				    माप_प्रकार req_ies_len, bool reconnect)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(100 + len + req_ies_len, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_FRAME, len, buf) ||
	    (req_ies &&
	     nla_put(msg, NL80211_ATTR_REQ_IE, req_ies_len, req_ies)))
		जाओ nla_put_failure;

	अगर (reconnect && nla_put_flag(msg, NL80211_ATTR_RECONNECT_REQUESTED))
		जाओ nla_put_failure;

	अगर (uapsd_queues >= 0) अणु
		काष्ठा nlattr *nla_wmm =
			nla_nest_start_noflag(msg, NL80211_ATTR_STA_WME);
		अगर (!nla_wmm)
			जाओ nla_put_failure;

		अगर (nla_put_u8(msg, NL80211_STA_WME_UAPSD_QUEUES,
			       uapsd_queues))
			जाओ nla_put_failure;

		nla_nest_end(msg, nla_wmm);
	पूर्ण

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम nl80211_send_rx_auth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			  काष्ठा net_device *netdev, स्थिर u8 *buf,
			  माप_प्रकार len, gfp_t gfp)
अणु
	nl80211_send_mlme_event(rdev, netdev, buf, len,
				NL80211_CMD_AUTHENTICATE, gfp, -1, शून्य, 0,
				false);
पूर्ण

व्योम nl80211_send_rx_assoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net_device *netdev, स्थिर u8 *buf,
			   माप_प्रकार len, gfp_t gfp, पूर्णांक uapsd_queues,
			   स्थिर u8 *req_ies, माप_प्रकार req_ies_len)
अणु
	nl80211_send_mlme_event(rdev, netdev, buf, len,
				NL80211_CMD_ASSOCIATE, gfp, uapsd_queues,
				req_ies, req_ies_len, false);
पूर्ण

व्योम nl80211_send_deauth(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *netdev, स्थिर u8 *buf,
			 माप_प्रकार len, bool reconnect, gfp_t gfp)
अणु
	nl80211_send_mlme_event(rdev, netdev, buf, len,
				NL80211_CMD_DEAUTHENTICATE, gfp, -1, शून्य, 0,
				reconnect);
पूर्ण

व्योम nl80211_send_disassoc(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			   काष्ठा net_device *netdev, स्थिर u8 *buf,
			   माप_प्रकार len, bool reconnect, gfp_t gfp)
अणु
	nl80211_send_mlme_event(rdev, netdev, buf, len,
				NL80211_CMD_DISASSOCIATE, gfp, -1, शून्य, 0,
				reconnect);
पूर्ण

व्योम cfg80211_rx_unprot_mlme_mgmt(काष्ठा net_device *dev, स्थिर u8 *buf,
				  माप_प्रकार len)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	स्थिर काष्ठा ieee80211_mgmt *mgmt = (व्योम *)buf;
	u32 cmd;

	अगर (WARN_ON(len < 2))
		वापस;

	अगर (ieee80211_is_deauth(mgmt->frame_control)) अणु
		cmd = NL80211_CMD_UNPROT_DEAUTHENTICATE;
	पूर्ण अन्यथा अगर (ieee80211_is_disassoc(mgmt->frame_control)) अणु
		cmd = NL80211_CMD_UNPROT_DISASSOCIATE;
	पूर्ण अन्यथा अगर (ieee80211_is_beacon(mgmt->frame_control)) अणु
		अगर (wdev->unprot_beacon_reported &&
		    elapsed_jअगरfies_msecs(wdev->unprot_beacon_reported) < 10000)
			वापस;
		cmd = NL80211_CMD_UNPROT_BEACON;
		wdev->unprot_beacon_reported = jअगरfies;
	पूर्ण अन्यथा अणु
		वापस;
	पूर्ण

	trace_cfg80211_rx_unprot_mlme_mgmt(dev, buf, len);
	nl80211_send_mlme_event(rdev, dev, buf, len, cmd, GFP_ATOMIC, -1,
				शून्य, 0, false);
पूर्ण
EXPORT_SYMBOL(cfg80211_rx_unprot_mlme_mgmt);

अटल व्योम nl80211_send_mlme_समयout(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				      काष्ठा net_device *netdev, पूर्णांक cmd,
				      स्थिर u8 *addr, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    nla_put_flag(msg, NL80211_ATTR_TIMED_OUT) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, addr))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम nl80211_send_auth_समयout(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *netdev, स्थिर u8 *addr,
			       gfp_t gfp)
अणु
	nl80211_send_mlme_समयout(rdev, netdev, NL80211_CMD_AUTHENTICATE,
				  addr, gfp);
पूर्ण

व्योम nl80211_send_assoc_समयout(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				काष्ठा net_device *netdev, स्थिर u8 *addr,
				gfp_t gfp)
अणु
	nl80211_send_mlme_समयout(rdev, netdev, NL80211_CMD_ASSOCIATE,
				  addr, gfp);
पूर्ण

व्योम nl80211_send_connect_result(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *netdev,
				 काष्ठा cfg80211_connect_resp_params *cr,
				 gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(100 + cr->req_ie_len + cr->resp_ie_len +
			cr->fils.kek_len + cr->fils.pmk_len +
			(cr->fils.pmkid ? WLAN_PMKID_LEN : 0), gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_CONNECT);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    (cr->bssid &&
	     nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, cr->bssid)) ||
	    nla_put_u16(msg, NL80211_ATTR_STATUS_CODE,
			cr->status < 0 ? WLAN_STATUS_UNSPECIFIED_FAILURE :
			cr->status) ||
	    (cr->status < 0 &&
	     (nla_put_flag(msg, NL80211_ATTR_TIMED_OUT) ||
	      nla_put_u32(msg, NL80211_ATTR_TIMEOUT_REASON,
			  cr->समयout_reason))) ||
	    (cr->req_ie &&
	     nla_put(msg, NL80211_ATTR_REQ_IE, cr->req_ie_len, cr->req_ie)) ||
	    (cr->resp_ie &&
	     nla_put(msg, NL80211_ATTR_RESP_IE, cr->resp_ie_len,
		     cr->resp_ie)) ||
	    (cr->fils.update_erp_next_seq_num &&
	     nla_put_u16(msg, NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM,
			 cr->fils.erp_next_seq_num)) ||
	    (cr->status == WLAN_STATUS_SUCCESS &&
	     ((cr->fils.kek &&
	       nla_put(msg, NL80211_ATTR_FILS_KEK, cr->fils.kek_len,
		       cr->fils.kek)) ||
	      (cr->fils.pmk &&
	       nla_put(msg, NL80211_ATTR_PMK, cr->fils.pmk_len, cr->fils.pmk)) ||
	      (cr->fils.pmkid &&
	       nla_put(msg, NL80211_ATTR_PMKID, WLAN_PMKID_LEN, cr->fils.pmkid)))))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम nl80211_send_roamed(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			 काष्ठा net_device *netdev,
			 काष्ठा cfg80211_roam_info *info, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	स्थिर u8 *bssid = info->bss ? info->bss->bssid : info->bssid;

	msg = nlmsg_new(100 + info->req_ie_len + info->resp_ie_len +
			info->fils.kek_len + info->fils.pmk_len +
			(info->fils.pmkid ? WLAN_PMKID_LEN : 0), gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_ROAM);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, bssid) ||
	    (info->req_ie &&
	     nla_put(msg, NL80211_ATTR_REQ_IE, info->req_ie_len,
		     info->req_ie)) ||
	    (info->resp_ie &&
	     nla_put(msg, NL80211_ATTR_RESP_IE, info->resp_ie_len,
		     info->resp_ie)) ||
	    (info->fils.update_erp_next_seq_num &&
	     nla_put_u16(msg, NL80211_ATTR_FILS_ERP_NEXT_SEQ_NUM,
			 info->fils.erp_next_seq_num)) ||
	    (info->fils.kek &&
	     nla_put(msg, NL80211_ATTR_FILS_KEK, info->fils.kek_len,
		     info->fils.kek)) ||
	    (info->fils.pmk &&
	     nla_put(msg, NL80211_ATTR_PMK, info->fils.pmk_len, info->fils.pmk)) ||
	    (info->fils.pmkid &&
	     nla_put(msg, NL80211_ATTR_PMKID, WLAN_PMKID_LEN, info->fils.pmkid)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम nl80211_send_port_authorized(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				  काष्ठा net_device *netdev, स्थिर u8 *bssid)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_PORT_AUTHORIZED);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, bssid))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, GFP_KERNEL);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम nl80211_send_disconnected(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *netdev, u16 reason,
			       स्थिर u8 *ie, माप_प्रकार ie_len, bool from_ap)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(100 + ie_len, GFP_KERNEL);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_DISCONNECT);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    (reason &&
	     nla_put_u16(msg, NL80211_ATTR_REASON_CODE, reason)) ||
	    (from_ap &&
	     nla_put_flag(msg, NL80211_ATTR_DISCONNECTED_BY_AP)) ||
	    (ie && nla_put(msg, NL80211_ATTR_IE, ie_len, ie)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, GFP_KERNEL);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम nl80211_send_ibss_bssid(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			     काष्ठा net_device *netdev, स्थिर u8 *bssid,
			     gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_JOIN_IBSS);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, bssid))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम cfg80211_notअगरy_new_peer_candidate(काष्ठा net_device *dev, स्थिर u8 *addr,
					स्थिर u8 *ie, u8 ie_len,
					पूर्णांक sig_dbm, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_MESH_POINT))
		वापस;

	trace_cfg80211_notअगरy_new_peer_candidate(dev, addr);

	msg = nlmsg_new(100 + ie_len, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_NEW_PEER_CANDIDATE);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, addr) ||
	    (ie_len && ie &&
	     nla_put(msg, NL80211_ATTR_IE, ie_len, ie)) ||
	    (sig_dbm &&
	     nla_put_u32(msg, NL80211_ATTR_RX_SIGNAL_DBM, sig_dbm)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_notअगरy_new_peer_candidate);

व्योम nl80211_michael_mic_failure(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				 काष्ठा net_device *netdev, स्थिर u8 *addr,
				 क्रमागत nl80211_key_type key_type, पूर्णांक key_id,
				 स्थिर u8 *tsc, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_MICHAEL_MIC_FAILURE);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    (addr && nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, addr)) ||
	    nla_put_u32(msg, NL80211_ATTR_KEY_TYPE, key_type) ||
	    (key_id != -1 &&
	     nla_put_u8(msg, NL80211_ATTR_KEY_IDX, key_id)) ||
	    (tsc && nla_put(msg, NL80211_ATTR_KEY_SEQ, 6, tsc)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम nl80211_send_beacon_hपूर्णांक_event(काष्ठा wiphy *wiphy,
				    काष्ठा ieee80211_channel *channel_beक्रमe,
				    काष्ठा ieee80211_channel *channel_after)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	काष्ठा nlattr *nl_freq;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_ATOMIC);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_REG_BEACON_HINT);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	/*
	 * Since we are applying the beacon hपूर्णांक to a wiphy we know its
	 * wiphy_idx is valid
	 */
	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, get_wiphy_idx(wiphy)))
		जाओ nla_put_failure;

	/* Beक्रमe */
	nl_freq = nla_nest_start_noflag(msg, NL80211_ATTR_FREQ_BEFORE);
	अगर (!nl_freq)
		जाओ nla_put_failure;

	अगर (nl80211_msg_put_channel(msg, wiphy, channel_beक्रमe, false))
		जाओ nla_put_failure;
	nla_nest_end(msg, nl_freq);

	/* After */
	nl_freq = nla_nest_start_noflag(msg, NL80211_ATTR_FREQ_AFTER);
	अगर (!nl_freq)
		जाओ nla_put_failure;

	अगर (nl80211_msg_put_channel(msg, wiphy, channel_after, false))
		जाओ nla_put_failure;
	nla_nest_end(msg, nl_freq);

	genlmsg_end(msg, hdr);

	rcu_पढ़ो_lock();
	genlmsg_multicast_allns(&nl80211_fam, msg, 0,
				NL80211_MCGRP_REGULATORY, GFP_ATOMIC);
	rcu_पढ़ो_unlock();

	वापस;

nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

अटल व्योम nl80211_send_reमुख्य_on_chan_event(
	पूर्णांक cmd, काष्ठा cfg80211_रेजिस्टरed_device *rdev,
	काष्ठा wireless_dev *wdev, u64 cookie,
	काष्ठा ieee80211_channel *chan,
	अचिन्हित पूर्णांक duration, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    (wdev->netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
					 wdev->netdev->अगरindex)) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD) ||
	    nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ, chan->center_freq) ||
	    nla_put_u32(msg, NL80211_ATTR_WIPHY_CHANNEL_TYPE,
			NL80211_CHAN_NO_HT) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	अगर (cmd == NL80211_CMD_REMAIN_ON_CHANNEL &&
	    nla_put_u32(msg, NL80211_ATTR_DURATION, duration))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम cfg80211_पढ़ोy_on_channel(काष्ठा wireless_dev *wdev, u64 cookie,
			       काष्ठा ieee80211_channel *chan,
			       अचिन्हित पूर्णांक duration, gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_पढ़ोy_on_channel(wdev, cookie, chan, duration);
	nl80211_send_reमुख्य_on_chan_event(NL80211_CMD_REMAIN_ON_CHANNEL,
					  rdev, wdev, cookie, chan,
					  duration, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_पढ़ोy_on_channel);

व्योम cfg80211_reमुख्य_on_channel_expired(काष्ठा wireless_dev *wdev, u64 cookie,
					काष्ठा ieee80211_channel *chan,
					gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_पढ़ोy_on_channel_expired(wdev, cookie, chan);
	nl80211_send_reमुख्य_on_chan_event(NL80211_CMD_CANCEL_REMAIN_ON_CHANNEL,
					  rdev, wdev, cookie, chan, 0, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_reमुख्य_on_channel_expired);

व्योम cfg80211_tx_mgmt_expired(काष्ठा wireless_dev *wdev, u64 cookie,
					काष्ठा ieee80211_channel *chan,
					gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_tx_mgmt_expired(wdev, cookie, chan);
	nl80211_send_reमुख्य_on_chan_event(NL80211_CMD_FRAME_WAIT_CANCEL,
					  rdev, wdev, cookie, chan, 0, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_tx_mgmt_expired);

व्योम cfg80211_new_sta(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
		      काष्ठा station_info *sinfo, gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = dev->ieee80211_ptr->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा sk_buff *msg;

	trace_cfg80211_new_sta(dev, mac_addr, sinfo);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	अगर (nl80211_send_station(msg, NL80211_CMD_NEW_STATION, 0, 0, 0,
				 rdev, dev, mac_addr, sinfo) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_new_sta);

व्योम cfg80211_del_sta_sinfo(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
			    काष्ठा station_info *sinfo, gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = dev->ieee80211_ptr->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा sk_buff *msg;
	काष्ठा station_info empty_sinfo = अणुपूर्ण;

	अगर (!sinfo)
		sinfo = &empty_sinfo;

	trace_cfg80211_del_sta(dev, mac_addr);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg) अणु
		cfg80211_sinfo_release_content(sinfo);
		वापस;
	पूर्ण

	अगर (nl80211_send_station(msg, NL80211_CMD_DEL_STATION, 0, 0, 0,
				 rdev, dev, mac_addr, sinfo) < 0) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_del_sta_sinfo);

व्योम cfg80211_conn_failed(काष्ठा net_device *dev, स्थिर u8 *mac_addr,
			  क्रमागत nl80211_connect_failed_reason reason,
			  gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = dev->ieee80211_ptr->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_GOODSIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_CONN_FAILED);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, mac_addr) ||
	    nla_put_u32(msg, NL80211_ATTR_CONN_FAILED_REASON, reason))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_conn_failed);

अटल bool __nl80211_unexpected_frame(काष्ठा net_device *dev, u8 cmd,
				       स्थिर u8 *addr, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	u32 nlportid = READ_ONCE(wdev->ap_unexpected_nlportid);

	अगर (!nlportid)
		वापस false;

	msg = nlmsg_new(100, gfp);
	अगर (!msg)
		वापस true;

	hdr = nl80211hdr_put(msg, 0, 0, 0, cmd);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस true;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, addr))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	genlmsg_unicast(wiphy_net(&rdev->wiphy), msg, nlportid);
	वापस true;

 nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस true;
पूर्ण

bool cfg80211_rx_spurious_frame(काष्ठा net_device *dev,
				स्थिर u8 *addr, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	bool ret;

	trace_cfg80211_rx_spurious_frame(dev, addr);

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_AP &&
		    wdev->अगरtype != NL80211_IFTYPE_P2P_GO)) अणु
		trace_cfg80211_वापस_bool(false);
		वापस false;
	पूर्ण
	ret = __nl80211_unexpected_frame(dev, NL80211_CMD_UNEXPECTED_FRAME,
					 addr, gfp);
	trace_cfg80211_वापस_bool(ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cfg80211_rx_spurious_frame);

bool cfg80211_rx_unexpected_4addr_frame(काष्ठा net_device *dev,
					स्थिर u8 *addr, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	bool ret;

	trace_cfg80211_rx_unexpected_4addr_frame(dev, addr);

	अगर (WARN_ON(wdev->अगरtype != NL80211_IFTYPE_AP &&
		    wdev->अगरtype != NL80211_IFTYPE_P2P_GO &&
		    wdev->अगरtype != NL80211_IFTYPE_AP_VLAN)) अणु
		trace_cfg80211_वापस_bool(false);
		वापस false;
	पूर्ण
	ret = __nl80211_unexpected_frame(dev,
					 NL80211_CMD_UNEXPECTED_4ADDR_FRAME,
					 addr, gfp);
	trace_cfg80211_वापस_bool(ret);
	वापस ret;
पूर्ण
EXPORT_SYMBOL(cfg80211_rx_unexpected_4addr_frame);

पूर्णांक nl80211_send_mgmt(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		      काष्ठा wireless_dev *wdev, u32 nlportid,
		      पूर्णांक freq, पूर्णांक sig_dbm,
		      स्थिर u8 *buf, माप_प्रकार len, u32 flags, gfp_t gfp)
अणु
	काष्ठा net_device *netdev = wdev->netdev;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(100 + len, gfp);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_FRAME);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOMEM;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    (netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
					netdev->अगरindex)) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD) ||
	    nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ, KHZ_TO_MHZ(freq)) ||
	    nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ_OFFSET, freq % 1000) ||
	    (sig_dbm &&
	     nla_put_u32(msg, NL80211_ATTR_RX_SIGNAL_DBM, sig_dbm)) ||
	    nla_put(msg, NL80211_ATTR_FRAME, len, buf) ||
	    (flags &&
	     nla_put_u32(msg, NL80211_ATTR_RXMGMT_FLAGS, flags)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	वापस genlmsg_unicast(wiphy_net(&rdev->wiphy), msg, nlportid);

 nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण

अटल व्योम nl80211_frame_tx_status(काष्ठा wireless_dev *wdev, u64 cookie,
				    स्थिर u8 *buf, माप_प्रकार len, bool ack,
				    gfp_t gfp, क्रमागत nl80211_commands command)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा net_device *netdev = wdev->netdev;
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	अगर (command == NL80211_CMD_FRAME_TX_STATUS)
		trace_cfg80211_mgmt_tx_status(wdev, cookie, ack);
	अन्यथा
		trace_cfg80211_control_port_tx_status(wdev, cookie, ack);

	msg = nlmsg_new(100 + len, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, command);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    (netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
				   netdev->अगरindex)) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD) ||
	    nla_put(msg, NL80211_ATTR_FRAME, len, buf) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
			      NL80211_ATTR_PAD) ||
	    (ack && nla_put_flag(msg, NL80211_ATTR_ACK)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम cfg80211_control_port_tx_status(काष्ठा wireless_dev *wdev, u64 cookie,
				     स्थिर u8 *buf, माप_प्रकार len, bool ack,
				     gfp_t gfp)
अणु
	nl80211_frame_tx_status(wdev, cookie, buf, len, ack, gfp,
				NL80211_CMD_CONTROL_PORT_FRAME_TX_STATUS);
पूर्ण
EXPORT_SYMBOL(cfg80211_control_port_tx_status);

व्योम cfg80211_mgmt_tx_status(काष्ठा wireless_dev *wdev, u64 cookie,
			     स्थिर u8 *buf, माप_प्रकार len, bool ack, gfp_t gfp)
अणु
	nl80211_frame_tx_status(wdev, cookie, buf, len, ack, gfp,
				NL80211_CMD_FRAME_TX_STATUS);
पूर्ण
EXPORT_SYMBOL(cfg80211_mgmt_tx_status);

अटल पूर्णांक __nl80211_rx_control_port(काष्ठा net_device *dev,
				     काष्ठा sk_buff *skb,
				     bool unencrypted, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा ethhdr *ehdr = eth_hdr(skb);
	स्थिर u8 *addr = ehdr->h_source;
	u16 proto = be16_to_cpu(skb->protocol);
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	काष्ठा nlattr *frame;

	u32 nlportid = READ_ONCE(wdev->conn_owner_nlportid);

	अगर (!nlportid)
		वापस -ENOENT;

	msg = nlmsg_new(100 + skb->len, gfp);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_CONTROL_PORT_FRAME);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस -ENOBUFS;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, addr) ||
	    nla_put_u16(msg, NL80211_ATTR_CONTROL_PORT_ETHERTYPE, proto) ||
	    (unencrypted && nla_put_flag(msg,
					 NL80211_ATTR_CONTROL_PORT_NO_ENCRYPT)))
		जाओ nla_put_failure;

	frame = nla_reserve(msg, NL80211_ATTR_FRAME, skb->len);
	अगर (!frame)
		जाओ nla_put_failure;

	skb_copy_bits(skb, 0, nla_data(frame), skb->len);
	genlmsg_end(msg, hdr);

	वापस genlmsg_unicast(wiphy_net(&rdev->wiphy), msg, nlportid);

 nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण

bool cfg80211_rx_control_port(काष्ठा net_device *dev,
			      काष्ठा sk_buff *skb, bool unencrypted)
अणु
	पूर्णांक ret;

	trace_cfg80211_rx_control_port(dev, skb, unencrypted);
	ret = __nl80211_rx_control_port(dev, skb, unencrypted, GFP_ATOMIC);
	trace_cfg80211_वापस_bool(ret == 0);
	वापस ret == 0;
पूर्ण
EXPORT_SYMBOL(cfg80211_rx_control_port);

अटल काष्ठा sk_buff *cfg80211_prepare_cqm(काष्ठा net_device *dev,
					    स्थिर अक्षर *mac, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा sk_buff *msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	व्योम **cb;

	अगर (!msg)
		वापस शून्य;

	cb = (व्योम **)msg->cb;

	cb[0] = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_NOTIFY_CQM);
	अगर (!cb[0]) अणु
		nlmsg_मुक्त(msg);
		वापस शून्य;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	अगर (mac && nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, mac))
		जाओ nla_put_failure;

	cb[1] = nla_nest_start_noflag(msg, NL80211_ATTR_CQM);
	अगर (!cb[1])
		जाओ nla_put_failure;

	cb[2] = rdev;

	वापस msg;
 nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस शून्य;
पूर्ण

अटल व्योम cfg80211_send_cqm(काष्ठा sk_buff *msg, gfp_t gfp)
अणु
	व्योम **cb = (व्योम **)msg->cb;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = cb[2];

	nla_nest_end(msg, cb[1]);
	genlmsg_end(msg, cb[0]);

	स_रखो(msg->cb, 0, माप(msg->cb));

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
पूर्ण

व्योम cfg80211_cqm_rssi_notअगरy(काष्ठा net_device *dev,
			      क्रमागत nl80211_cqm_rssi_threshold_event rssi_event,
			      s32 rssi_level, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);

	trace_cfg80211_cqm_rssi_notअगरy(dev, rssi_event, rssi_level);

	अगर (WARN_ON(rssi_event != NL80211_CQM_RSSI_THRESHOLD_EVENT_LOW &&
		    rssi_event != NL80211_CQM_RSSI_THRESHOLD_EVENT_HIGH))
		वापस;

	अगर (wdev->cqm_config) अणु
		wdev->cqm_config->last_rssi_event_value = rssi_level;

		cfg80211_cqm_rssi_update(rdev, dev);

		अगर (rssi_level == 0)
			rssi_level = wdev->cqm_config->last_rssi_event_value;
	पूर्ण

	msg = cfg80211_prepare_cqm(dev, शून्य, gfp);
	अगर (!msg)
		वापस;

	अगर (nla_put_u32(msg, NL80211_ATTR_CQM_RSSI_THRESHOLD_EVENT,
			rssi_event))
		जाओ nla_put_failure;

	अगर (rssi_level && nla_put_s32(msg, NL80211_ATTR_CQM_RSSI_LEVEL,
				      rssi_level))
		जाओ nla_put_failure;

	cfg80211_send_cqm(msg, gfp);

	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_cqm_rssi_notअगरy);

व्योम cfg80211_cqm_txe_notअगरy(काष्ठा net_device *dev,
			     स्थिर u8 *peer, u32 num_packets,
			     u32 rate, u32 पूर्णांकvl, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;

	msg = cfg80211_prepare_cqm(dev, peer, gfp);
	अगर (!msg)
		वापस;

	अगर (nla_put_u32(msg, NL80211_ATTR_CQM_TXE_PKTS, num_packets))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_CQM_TXE_RATE, rate))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_CQM_TXE_INTVL, पूर्णांकvl))
		जाओ nla_put_failure;

	cfg80211_send_cqm(msg, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_cqm_txe_notअगरy);

व्योम cfg80211_cqm_pktloss_notअगरy(काष्ठा net_device *dev,
				 स्थिर u8 *peer, u32 num_packets, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;

	trace_cfg80211_cqm_pktloss_notअगरy(dev, peer, num_packets);

	msg = cfg80211_prepare_cqm(dev, peer, gfp);
	अगर (!msg)
		वापस;

	अगर (nla_put_u32(msg, NL80211_ATTR_CQM_PKT_LOSS_EVENT, num_packets))
		जाओ nla_put_failure;

	cfg80211_send_cqm(msg, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_cqm_pktloss_notअगरy);

व्योम cfg80211_cqm_beacon_loss_notअगरy(काष्ठा net_device *dev, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;

	msg = cfg80211_prepare_cqm(dev, शून्य, gfp);
	अगर (!msg)
		वापस;

	अगर (nla_put_flag(msg, NL80211_ATTR_CQM_BEACON_LOSS_EVENT))
		जाओ nla_put_failure;

	cfg80211_send_cqm(msg, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_cqm_beacon_loss_notअगरy);

अटल व्योम nl80211_gtk_rekey_notअगरy(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा net_device *netdev, स्थिर u8 *bssid,
				     स्थिर u8 *replay_ctr, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा nlattr *rekey_attr;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_SET_REKEY_OFFLOAD);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, bssid))
		जाओ nla_put_failure;

	rekey_attr = nla_nest_start_noflag(msg, NL80211_ATTR_REKEY_DATA);
	अगर (!rekey_attr)
		जाओ nla_put_failure;

	अगर (nla_put(msg, NL80211_REKEY_DATA_REPLAY_CTR,
		    NL80211_REPLAY_CTR_LEN, replay_ctr))
		जाओ nla_put_failure;

	nla_nest_end(msg, rekey_attr);

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम cfg80211_gtk_rekey_notअगरy(काष्ठा net_device *dev, स्थिर u8 *bssid,
			       स्थिर u8 *replay_ctr, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_gtk_rekey_notअगरy(dev, bssid);
	nl80211_gtk_rekey_notअगरy(rdev, dev, bssid, replay_ctr, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_gtk_rekey_notअगरy);

अटल व्योम
nl80211_pmksa_candidate_notअगरy(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
			       काष्ठा net_device *netdev, पूर्णांक index,
			       स्थिर u8 *bssid, bool preauth, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा nlattr *attr;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_PMKSA_CANDIDATE);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex))
		जाओ nla_put_failure;

	attr = nla_nest_start_noflag(msg, NL80211_ATTR_PMKSA_CANDIDATE);
	अगर (!attr)
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_PMKSA_CANDIDATE_INDEX, index) ||
	    nla_put(msg, NL80211_PMKSA_CANDIDATE_BSSID, ETH_ALEN, bssid) ||
	    (preauth &&
	     nla_put_flag(msg, NL80211_PMKSA_CANDIDATE_PREAUTH)))
		जाओ nla_put_failure;

	nla_nest_end(msg, attr);

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम cfg80211_pmksa_candidate_notअगरy(काष्ठा net_device *dev, पूर्णांक index,
				     स्थिर u8 *bssid, bool preauth, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_pmksa_candidate_notअगरy(dev, index, bssid, preauth);
	nl80211_pmksa_candidate_notअगरy(rdev, dev, index, bssid, preauth, gfp);
पूर्ण
EXPORT_SYMBOL(cfg80211_pmksa_candidate_notअगरy);

अटल व्योम nl80211_ch_चयन_notअगरy(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
				     काष्ठा net_device *netdev,
				     काष्ठा cfg80211_chan_def *chandef,
				     gfp_t gfp,
				     क्रमागत nl80211_commands notअगर,
				     u8 count, bool quiet)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, notअगर);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex))
		जाओ nla_put_failure;

	अगर (nl80211_send_chandef(msg, chandef))
		जाओ nla_put_failure;

	अगर (notअगर == NL80211_CMD_CH_SWITCH_STARTED_NOTIFY) अणु
		अगर (nla_put_u32(msg, NL80211_ATTR_CH_SWITCH_COUNT, count))
			जाओ nla_put_failure;
		अगर (quiet &&
		    nla_put_flag(msg, NL80211_ATTR_CH_SWITCH_BLOCK_TX))
			जाओ nla_put_failure;
	पूर्ण

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम cfg80211_ch_चयन_notअगरy(काष्ठा net_device *dev,
			       काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	ASSERT_WDEV_LOCK(wdev);

	trace_cfg80211_ch_चयन_notअगरy(dev, chandef);

	wdev->chandef = *chandef;
	wdev->preset_chandef = *chandef;

	अगर (wdev->अगरtype == NL80211_IFTYPE_STATION &&
	    !WARN_ON(!wdev->current_bss))
		cfg80211_update_assoc_bss_entry(wdev, chandef->chan);

	cfg80211_sched_dfs_chan_update(rdev);

	nl80211_ch_चयन_notअगरy(rdev, dev, chandef, GFP_KERNEL,
				 NL80211_CMD_CH_SWITCH_NOTIFY, 0, false);
पूर्ण
EXPORT_SYMBOL(cfg80211_ch_चयन_notअगरy);

व्योम cfg80211_ch_चयन_started_notअगरy(काष्ठा net_device *dev,
				       काष्ठा cfg80211_chan_def *chandef,
				       u8 count, bool quiet)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);

	trace_cfg80211_ch_चयन_started_notअगरy(dev, chandef);

	nl80211_ch_चयन_notअगरy(rdev, dev, chandef, GFP_KERNEL,
				 NL80211_CMD_CH_SWITCH_STARTED_NOTIFY,
				 count, quiet);
पूर्ण
EXPORT_SYMBOL(cfg80211_ch_चयन_started_notअगरy);

व्योम
nl80211_radar_notअगरy(काष्ठा cfg80211_रेजिस्टरed_device *rdev,
		     स्थिर काष्ठा cfg80211_chan_def *chandef,
		     क्रमागत nl80211_radar_event event,
		     काष्ठा net_device *netdev, gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_RADAR_DETECT);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx))
		जाओ nla_put_failure;

	/* NOP and radar events करोn't need a netdev parameter */
	अगर (netdev) अणु
		काष्ठा wireless_dev *wdev = netdev->ieee80211_ptr;

		अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
		    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
				      NL80211_ATTR_PAD))
			जाओ nla_put_failure;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_RADAR_EVENT, event))
		जाओ nla_put_failure;

	अगर (nl80211_send_chandef(msg, chandef))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण

व्योम cfg80211_sta_opmode_change_notअगरy(काष्ठा net_device *dev, स्थिर u8 *mac,
				       काष्ठा sta_opmode_info *sta_opmode,
				       gfp_t gfp)
अणु
	काष्ठा sk_buff *msg;
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	व्योम *hdr;

	अगर (WARN_ON(!mac))
		वापस;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_STA_OPMODE_CHANGED);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx))
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex))
		जाओ nla_put_failure;

	अगर (nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, mac))
		जाओ nla_put_failure;

	अगर ((sta_opmode->changed & STA_OPMODE_SMPS_MODE_CHANGED) &&
	    nla_put_u8(msg, NL80211_ATTR_SMPS_MODE, sta_opmode->smps_mode))
		जाओ nla_put_failure;

	अगर ((sta_opmode->changed & STA_OPMODE_MAX_BW_CHANGED) &&
	    nla_put_u32(msg, NL80211_ATTR_CHANNEL_WIDTH, sta_opmode->bw))
		जाओ nla_put_failure;

	अगर ((sta_opmode->changed & STA_OPMODE_N_SS_CHANGED) &&
	    nla_put_u8(msg, NL80211_ATTR_NSS, sta_opmode->rx_nss))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);

	वापस;

nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_sta_opmode_change_notअगरy);

व्योम cfg80211_probe_status(काष्ठा net_device *dev, स्थिर u8 *addr,
			   u64 cookie, bool acked, s32 ack_संकेत,
			   bool is_valid_ack_संकेत, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	trace_cfg80211_probe_status(dev, addr, cookie, acked);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);

	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_PROBE_CLIENT);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, addr) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_COOKIE, cookie,
			      NL80211_ATTR_PAD) ||
	    (acked && nla_put_flag(msg, NL80211_ATTR_ACK)) ||
	    (is_valid_ack_संकेत && nla_put_s32(msg, NL80211_ATTR_ACK_SIGNAL,
						ack_संकेत)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_probe_status);

व्योम cfg80211_report_obss_beacon_khz(काष्ठा wiphy *wiphy, स्थिर u8 *frame,
				     माप_प्रकार len, पूर्णांक freq, पूर्णांक sig_dbm)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	काष्ठा cfg80211_beacon_registration *reg;

	trace_cfg80211_report_obss_beacon(wiphy, frame, len, freq, sig_dbm);

	spin_lock_bh(&rdev->beacon_registrations_lock);
	list_क्रम_each_entry(reg, &rdev->beacon_registrations, list) अणु
		msg = nlmsg_new(len + 100, GFP_ATOMIC);
		अगर (!msg) अणु
			spin_unlock_bh(&rdev->beacon_registrations_lock);
			वापस;
		पूर्ण

		hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_FRAME);
		अगर (!hdr)
			जाओ nla_put_failure;

		अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
		    (freq &&
		     (nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ,
				  KHZ_TO_MHZ(freq)) ||
		      nla_put_u32(msg, NL80211_ATTR_WIPHY_FREQ_OFFSET,
				  freq % 1000))) ||
		    (sig_dbm &&
		     nla_put_u32(msg, NL80211_ATTR_RX_SIGNAL_DBM, sig_dbm)) ||
		    nla_put(msg, NL80211_ATTR_FRAME, len, frame))
			जाओ nla_put_failure;

		genlmsg_end(msg, hdr);

		genlmsg_unicast(wiphy_net(&rdev->wiphy), msg, reg->nlportid);
	पूर्ण
	spin_unlock_bh(&rdev->beacon_registrations_lock);
	वापस;

 nla_put_failure:
	spin_unlock_bh(&rdev->beacon_registrations_lock);
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_report_obss_beacon_khz);

#अगर_घोषित CONFIG_PM
अटल पूर्णांक cfg80211_net_detect_results(काष्ठा sk_buff *msg,
				       काष्ठा cfg80211_wowlan_wakeup *wakeup)
अणु
	काष्ठा cfg80211_wowlan_nd_info *nd = wakeup->net_detect;
	काष्ठा nlattr *nl_results, *nl_match, *nl_freqs;
	पूर्णांक i, j;

	nl_results = nla_nest_start_noflag(msg,
					   NL80211_WOWLAN_TRIG_NET_DETECT_RESULTS);
	अगर (!nl_results)
		वापस -EMSGSIZE;

	क्रम (i = 0; i < nd->n_matches; i++) अणु
		काष्ठा cfg80211_wowlan_nd_match *match = nd->matches[i];

		nl_match = nla_nest_start_noflag(msg, i);
		अगर (!nl_match)
			अवरोध;

		/* The SSID attribute is optional in nl80211, but क्रम
		 * simplicity reasons it's always present in the
		 * cfg80211 काष्ठाure.  If a driver can't pass the
		 * SSID, that needs to be changed.  A zero length SSID
		 * is still a valid SSID (wildcard), so it cannot be
		 * used क्रम this purpose.
		 */
		अगर (nla_put(msg, NL80211_ATTR_SSID, match->ssid.ssid_len,
			    match->ssid.ssid)) अणु
			nla_nest_cancel(msg, nl_match);
			जाओ out;
		पूर्ण

		अगर (match->n_channels) अणु
			nl_freqs = nla_nest_start_noflag(msg,
							 NL80211_ATTR_SCAN_FREQUENCIES);
			अगर (!nl_freqs) अणु
				nla_nest_cancel(msg, nl_match);
				जाओ out;
			पूर्ण

			क्रम (j = 0; j < match->n_channels; j++) अणु
				अगर (nla_put_u32(msg, j, match->channels[j])) अणु
					nla_nest_cancel(msg, nl_freqs);
					nla_nest_cancel(msg, nl_match);
					जाओ out;
				पूर्ण
			पूर्ण

			nla_nest_end(msg, nl_freqs);
		पूर्ण

		nla_nest_end(msg, nl_match);
	पूर्ण

out:
	nla_nest_end(msg, nl_results);
	वापस 0;
पूर्ण

व्योम cfg80211_report_wowlan_wakeup(काष्ठा wireless_dev *wdev,
				   काष्ठा cfg80211_wowlan_wakeup *wakeup,
				   gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	पूर्णांक size = 200;

	trace_cfg80211_report_wowlan_wakeup(wdev->wiphy, wdev, wakeup);

	अगर (wakeup)
		size += wakeup->packet_present_len;

	msg = nlmsg_new(size, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_SET_WOWLAN);
	अगर (!hdr)
		जाओ मुक्त_msg;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ मुक्त_msg;

	अगर (wdev->netdev && nla_put_u32(msg, NL80211_ATTR_IFINDEX,
					wdev->netdev->अगरindex))
		जाओ मुक्त_msg;

	अगर (wakeup) अणु
		काष्ठा nlattr *reasons;

		reasons = nla_nest_start_noflag(msg,
						NL80211_ATTR_WOWLAN_TRIGGERS);
		अगर (!reasons)
			जाओ मुक्त_msg;

		अगर (wakeup->disconnect &&
		    nla_put_flag(msg, NL80211_WOWLAN_TRIG_DISCONNECT))
			जाओ मुक्त_msg;
		अगर (wakeup->magic_pkt &&
		    nla_put_flag(msg, NL80211_WOWLAN_TRIG_MAGIC_PKT))
			जाओ मुक्त_msg;
		अगर (wakeup->gtk_rekey_failure &&
		    nla_put_flag(msg, NL80211_WOWLAN_TRIG_GTK_REKEY_FAILURE))
			जाओ मुक्त_msg;
		अगर (wakeup->eap_identity_req &&
		    nla_put_flag(msg, NL80211_WOWLAN_TRIG_EAP_IDENT_REQUEST))
			जाओ मुक्त_msg;
		अगर (wakeup->four_way_handshake &&
		    nla_put_flag(msg, NL80211_WOWLAN_TRIG_4WAY_HANDSHAKE))
			जाओ मुक्त_msg;
		अगर (wakeup->rfसमाप्त_release &&
		    nla_put_flag(msg, NL80211_WOWLAN_TRIG_RFKILL_RELEASE))
			जाओ मुक्त_msg;

		अगर (wakeup->pattern_idx >= 0 &&
		    nla_put_u32(msg, NL80211_WOWLAN_TRIG_PKT_PATTERN,
				wakeup->pattern_idx))
			जाओ मुक्त_msg;

		अगर (wakeup->tcp_match &&
		    nla_put_flag(msg, NL80211_WOWLAN_TRIG_WAKEUP_TCP_MATCH))
			जाओ मुक्त_msg;

		अगर (wakeup->tcp_connlost &&
		    nla_put_flag(msg, NL80211_WOWLAN_TRIG_WAKEUP_TCP_CONNLOST))
			जाओ मुक्त_msg;

		अगर (wakeup->tcp_nomoretokens &&
		    nla_put_flag(msg,
				 NL80211_WOWLAN_TRIG_WAKEUP_TCP_NOMORETOKENS))
			जाओ मुक्त_msg;

		अगर (wakeup->packet) अणु
			u32 pkt_attr = NL80211_WOWLAN_TRIG_WAKEUP_PKT_80211;
			u32 len_attr = NL80211_WOWLAN_TRIG_WAKEUP_PKT_80211_LEN;

			अगर (!wakeup->packet_80211) अणु
				pkt_attr =
					NL80211_WOWLAN_TRIG_WAKEUP_PKT_8023;
				len_attr =
					NL80211_WOWLAN_TRIG_WAKEUP_PKT_8023_LEN;
			पूर्ण

			अगर (wakeup->packet_len &&
			    nla_put_u32(msg, len_attr, wakeup->packet_len))
				जाओ मुक्त_msg;

			अगर (nla_put(msg, pkt_attr, wakeup->packet_present_len,
				    wakeup->packet))
				जाओ मुक्त_msg;
		पूर्ण

		अगर (wakeup->net_detect &&
		    cfg80211_net_detect_results(msg, wakeup))
				जाओ मुक्त_msg;

		nla_nest_end(msg, reasons);
	पूर्ण

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 मुक्त_msg:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_report_wowlan_wakeup);
#पूर्ण_अगर

व्योम cfg80211_tdls_oper_request(काष्ठा net_device *dev, स्थिर u8 *peer,
				क्रमागत nl80211_tdls_operation oper,
				u16 reason_code, gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	trace_cfg80211_tdls_oper_request(wdev->wiphy, dev, peer, oper,
					 reason_code);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_TDLS_OPER);
	अगर (!hdr) अणु
		nlmsg_मुक्त(msg);
		वापस;
	पूर्ण

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put_u8(msg, NL80211_ATTR_TDLS_OPERATION, oper) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, peer) ||
	    (reason_code > 0 &&
	     nla_put_u16(msg, NL80211_ATTR_REASON_CODE, reason_code)))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_tdls_oper_request);

अटल पूर्णांक nl80211_netlink_notअगरy(काष्ठा notअगरier_block * nb,
				  अचिन्हित दीर्घ state,
				  व्योम *_notअगरy)
अणु
	काष्ठा netlink_notअगरy *notअगरy = _notअगरy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा wireless_dev *wdev;
	काष्ठा cfg80211_beacon_registration *reg, *पंचांगp;

	अगर (state != NETLINK_URELEASE || notअगरy->protocol != NETLINK_GENERIC)
		वापस NOTIFY_DONE;

	rcu_पढ़ो_lock();

	list_क्रम_each_entry_rcu(rdev, &cfg80211_rdev_list, list) अणु
		काष्ठा cfg80211_sched_scan_request *sched_scan_req;

		list_क्रम_each_entry_rcu(sched_scan_req,
					&rdev->sched_scan_req_list,
					list) अणु
			अगर (sched_scan_req->owner_nlportid == notअगरy->portid) अणु
				sched_scan_req->nl_owner_dead = true;
				schedule_work(&rdev->sched_scan_stop_wk);
			पूर्ण
		पूर्ण

		list_क्रम_each_entry_rcu(wdev, &rdev->wiphy.wdev_list, list) अणु
			cfg80211_mlme_unरेजिस्टर_socket(wdev, notअगरy->portid);

			अगर (wdev->owner_nlportid == notअगरy->portid) अणु
				wdev->nl_owner_dead = true;
				schedule_work(&rdev->destroy_work);
			पूर्ण अन्यथा अगर (wdev->conn_owner_nlportid == notअगरy->portid) अणु
				schedule_work(&wdev->disconnect_wk);
			पूर्ण

			cfg80211_release_pmsr(wdev, notअगरy->portid);
		पूर्ण

		spin_lock_bh(&rdev->beacon_registrations_lock);
		list_क्रम_each_entry_safe(reg, पंचांगp, &rdev->beacon_registrations,
					 list) अणु
			अगर (reg->nlportid == notअगरy->portid) अणु
				list_del(&reg->list);
				kमुक्त(reg);
				अवरोध;
			पूर्ण
		पूर्ण
		spin_unlock_bh(&rdev->beacon_registrations_lock);
	पूर्ण

	rcu_पढ़ो_unlock();

	/*
	 * It is possible that the user space process that is controlling the
	 * inकरोor setting disappeared, so notअगरy the regulatory core.
	 */
	regulatory_netlink_notअगरy(notअगरy->portid);
	वापस NOTIFY_OK;
पूर्ण

अटल काष्ठा notअगरier_block nl80211_netlink_notअगरier = अणु
	.notअगरier_call = nl80211_netlink_notअगरy,
पूर्ण;

व्योम cfg80211_ft_event(काष्ठा net_device *netdev,
		       काष्ठा cfg80211_ft_event_params *ft_event)
अणु
	काष्ठा wiphy *wiphy = netdev->ieee80211_ptr->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	trace_cfg80211_ft_event(wiphy, netdev, ft_event);

	अगर (!ft_event->target_ap)
		वापस;

	msg = nlmsg_new(100 + ft_event->ies_len + ft_event->ric_ies_len,
			GFP_KERNEL);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_FT_EVENT);
	अगर (!hdr)
		जाओ out;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, ft_event->target_ap))
		जाओ out;

	अगर (ft_event->ies &&
	    nla_put(msg, NL80211_ATTR_IE, ft_event->ies_len, ft_event->ies))
		जाओ out;
	अगर (ft_event->ric_ies &&
	    nla_put(msg, NL80211_ATTR_IE_RIC, ft_event->ric_ies_len,
		    ft_event->ric_ies))
		जाओ out;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, GFP_KERNEL);
	वापस;
 out:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_ft_event);

व्योम cfg80211_crit_proto_stopped(काष्ठा wireless_dev *wdev, gfp_t gfp)
अणु
	काष्ठा cfg80211_रेजिस्टरed_device *rdev;
	काष्ठा sk_buff *msg;
	व्योम *hdr;
	u32 nlportid;

	rdev = wiphy_to_rdev(wdev->wiphy);
	अगर (!rdev->crit_proto_nlportid)
		वापस;

	nlportid = rdev->crit_proto_nlportid;
	rdev->crit_proto_nlportid = 0;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_CRIT_PROTOCOL_STOP);
	अगर (!hdr)
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_unicast(wiphy_net(&rdev->wiphy), msg, nlportid);
	वापस;

 nla_put_failure:
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_crit_proto_stopped);

व्योम nl80211_send_ap_stopped(काष्ठा wireless_dev *wdev)
अणु
	काष्ठा wiphy *wiphy = wdev->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_STOP_AP);
	अगर (!hdr)
		जाओ out;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, wdev->netdev->अगरindex) ||
	    nla_put_u64_64bit(msg, NL80211_ATTR_WDEV, wdev_id(wdev),
			      NL80211_ATTR_PAD))
		जाओ out;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(wiphy), msg, 0,
				NL80211_MCGRP_MLME, GFP_KERNEL);
	वापस;
 out:
	nlmsg_मुक्त(msg);
पूर्ण

पूर्णांक cfg80211_बाह्यal_auth_request(काष्ठा net_device *dev,
				   काष्ठा cfg80211_बाह्यal_auth_params *params,
				   gfp_t gfp)
अणु
	काष्ठा wireless_dev *wdev = dev->ieee80211_ptr;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wdev->wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	अगर (!wdev->conn_owner_nlportid)
		वापस -EINVAL;

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस -ENOMEM;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_EXTERNAL_AUTH);
	अगर (!hdr)
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->अगरindex) ||
	    nla_put_u32(msg, NL80211_ATTR_AKM_SUITES, params->key_mgmt_suite) ||
	    nla_put_u32(msg, NL80211_ATTR_EXTERNAL_AUTH_ACTION,
			params->action) ||
	    nla_put(msg, NL80211_ATTR_BSSID, ETH_ALEN, params->bssid) ||
	    nla_put(msg, NL80211_ATTR_SSID, params->ssid.ssid_len,
		    params->ssid.ssid))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);
	genlmsg_unicast(wiphy_net(&rdev->wiphy), msg,
			wdev->conn_owner_nlportid);
	वापस 0;

 nla_put_failure:
	nlmsg_मुक्त(msg);
	वापस -ENOBUFS;
पूर्ण
EXPORT_SYMBOL(cfg80211_बाह्यal_auth_request);

व्योम cfg80211_update_owe_info_event(काष्ठा net_device *netdev,
				    काष्ठा cfg80211_update_owe_info *owe_info,
				    gfp_t gfp)
अणु
	काष्ठा wiphy *wiphy = netdev->ieee80211_ptr->wiphy;
	काष्ठा cfg80211_रेजिस्टरed_device *rdev = wiphy_to_rdev(wiphy);
	काष्ठा sk_buff *msg;
	व्योम *hdr;

	trace_cfg80211_update_owe_info_event(wiphy, netdev, owe_info);

	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, gfp);
	अगर (!msg)
		वापस;

	hdr = nl80211hdr_put(msg, 0, 0, 0, NL80211_CMD_UPDATE_OWE_INFO);
	अगर (!hdr)
		जाओ nla_put_failure;

	अगर (nla_put_u32(msg, NL80211_ATTR_WIPHY, rdev->wiphy_idx) ||
	    nla_put_u32(msg, NL80211_ATTR_IFINDEX, netdev->अगरindex) ||
	    nla_put(msg, NL80211_ATTR_MAC, ETH_ALEN, owe_info->peer))
		जाओ nla_put_failure;

	अगर (!owe_info->ie_len ||
	    nla_put(msg, NL80211_ATTR_IE, owe_info->ie_len, owe_info->ie))
		जाओ nla_put_failure;

	genlmsg_end(msg, hdr);

	genlmsg_multicast_netns(&nl80211_fam, wiphy_net(&rdev->wiphy), msg, 0,
				NL80211_MCGRP_MLME, gfp);
	वापस;

nla_put_failure:
	genlmsg_cancel(msg, hdr);
	nlmsg_मुक्त(msg);
पूर्ण
EXPORT_SYMBOL(cfg80211_update_owe_info_event);

/* initialisation/निकास functions */

पूर्णांक __init nl80211_init(व्योम)
अणु
	पूर्णांक err;

	err = genl_रेजिस्टर_family(&nl80211_fam);
	अगर (err)
		वापस err;

	err = netlink_रेजिस्टर_notअगरier(&nl80211_netlink_notअगरier);
	अगर (err)
		जाओ err_out;

	वापस 0;
 err_out:
	genl_unरेजिस्टर_family(&nl80211_fam);
	वापस err;
पूर्ण

व्योम nl80211_निकास(व्योम)
अणु
	netlink_unरेजिस्टर_notअगरier(&nl80211_netlink_notअगरier);
	genl_unरेजिस्टर_family(&nl80211_fam);
पूर्ण
