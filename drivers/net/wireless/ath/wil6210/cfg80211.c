<शैली गुरु>
// SPDX-License-Identअगरier: ISC
/*
 * Copyright (c) 2012-2017 Qualcomm Atheros, Inc.
 * Copyright (c) 2018-2019, The Linux Foundation. All rights reserved.
 */

#समावेश <linux/etherdevice.h>
#समावेश <linux/moduleparam.h>
#समावेश <net/netlink.h>
#समावेश <net/cfg80211.h>
#समावेश "wil6210.h"
#समावेश "wmi.h"
#समावेश "fw.h"

#घोषणा WIL_MAX_ROC_DURATION_MS 5000

#घोषणा WIL_EDMG_CHANNEL_9_SUBCHANNELS	(BIT(0) | BIT(1))
#घोषणा WIL_EDMG_CHANNEL_10_SUBCHANNELS	(BIT(1) | BIT(2))
#घोषणा WIL_EDMG_CHANNEL_11_SUBCHANNELS	(BIT(2) | BIT(3))

/* WIL_EDMG_BW_CONFIGURATION define the allowed channel bandwidth
 * configurations as defined by IEEE 802.11 section 9.4.2.251, Table 13.
 * The value 5 allowing CB1 and CB2 of adjacent channels.
 */
#घोषणा WIL_EDMG_BW_CONFIGURATION 5

/* WIL_EDMG_CHANNELS is a biपंचांगap that indicates the 2.16 GHz channel(s) that
 * are allowed to be used क्रम EDMG transmissions in the BSS as defined by
 * IEEE 802.11 section 9.4.2.251.
 */
#घोषणा WIL_EDMG_CHANNELS (BIT(0) | BIT(1) | BIT(2) | BIT(3))

bool disable_ap_sme;
module_param(disable_ap_sme, bool, 0444);
MODULE_PARM_DESC(disable_ap_sme, " let user space handle AP mode SME");

#अगर_घोषित CONFIG_PM
अटल काष्ठा wiphy_wowlan_support wil_wowlan_support = अणु
	.flags = WIPHY_WOWLAN_ANY | WIPHY_WOWLAN_DISCONNECT,
पूर्ण;
#पूर्ण_अगर

#घोषणा CHAN60G(_channel, _flags) अणु				\
	.band			= NL80211_BAND_60GHZ,		\
	.center_freq		= 56160 + (2160 * (_channel)),	\
	.hw_value		= (_channel),			\
	.flags			= (_flags),			\
	.max_antenna_gain	= 0,				\
	.max_घातer		= 40,				\
पूर्ण

अटल काष्ठा ieee80211_channel wil_60ghz_channels[] = अणु
	CHAN60G(1, 0),
	CHAN60G(2, 0),
	CHAN60G(3, 0),
	CHAN60G(4, 0),
पूर्ण;

/* Rx channel bonding mode */
क्रमागत wil_rx_cb_mode अणु
	WIL_RX_CB_MODE_DMG,
	WIL_RX_CB_MODE_EDMG,
	WIL_RX_CB_MODE_WIDE,
पूर्ण;

अटल पूर्णांक wil_rx_cb_mode_to_n_bonded(u8 cb_mode)
अणु
	चयन (cb_mode) अणु
	हाल WIL_RX_CB_MODE_DMG:
	हाल WIL_RX_CB_MODE_EDMG:
		वापस 1;
	हाल WIL_RX_CB_MODE_WIDE:
		वापस 2;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल पूर्णांक wil_tx_cb_mode_to_n_bonded(u8 cb_mode)
अणु
	चयन (cb_mode) अणु
	हाल WMI_TX_MODE_DMG:
	हाल WMI_TX_MODE_EDMG_CB1:
		वापस 1;
	हाल WMI_TX_MODE_EDMG_CB2:
		वापस 2;
	शेष:
		वापस 1;
	पूर्ण
पूर्ण

अटल व्योम
wil_memdup_ie(u8 **pdst, माप_प्रकार *pdst_len, स्थिर u8 *src, माप_प्रकार src_len)
अणु
	kमुक्त(*pdst);
	*pdst = शून्य;
	*pdst_len = 0;
	अगर (src_len > 0) अणु
		*pdst = kmemdup(src, src_len, GFP_KERNEL);
		अगर (*pdst)
			*pdst_len = src_len;
	पूर्ण
पूर्ण

अटल पूर्णांक wil_num_supported_channels(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक num_channels = ARRAY_SIZE(wil_60ghz_channels);

	अगर (!test_bit(WMI_FW_CAPABILITY_CHANNEL_4, wil->fw_capabilities))
		num_channels--;

	वापस num_channels;
पूर्ण

व्योम update_supported_bands(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);

	wil_dbg_misc(wil, "update supported bands");

	wiphy->bands[NL80211_BAND_60GHZ]->n_channels =
						wil_num_supported_channels(wil);

	अगर (test_bit(WMI_FW_CAPABILITY_CHANNEL_BONDING, wil->fw_capabilities)) अणु
		wiphy->bands[NL80211_BAND_60GHZ]->edmg_cap.channels =
							WIL_EDMG_CHANNELS;
		wiphy->bands[NL80211_BAND_60GHZ]->edmg_cap.bw_config =
						      WIL_EDMG_BW_CONFIGURATION;
	पूर्ण
पूर्ण

/* Venकरोr id to be used in venकरोr specअगरic command and events
 * to user space.
 * NOTE: The authoritative place क्रम definition of QCA_NL80211_VENDOR_ID,
 * venकरोr subcmd definitions prefixed with QCA_NL80211_VENDOR_SUBCMD, and
 * qca_wlan_venकरोr_attr is खोलो source file src/common/qca-venकरोr.h in
 * git://w1.fi/srv/git/hostap.git; the values here are just a copy of that
 */

#घोषणा QCA_NL80211_VENDOR_ID	0x001374

#घोषणा WIL_MAX_RF_SECTORS (128)
#घोषणा WIL_CID_ALL (0xff)

क्रमागत qca_wlan_venकरोr_attr_rf_sector अणु
	QCA_ATTR_MAC_ADDR = 6,
	QCA_ATTR_PAD = 13,
	QCA_ATTR_TSF = 29,
	QCA_ATTR_DMG_RF_SECTOR_INDEX = 30,
	QCA_ATTR_DMG_RF_SECTOR_TYPE = 31,
	QCA_ATTR_DMG_RF_MODULE_MASK = 32,
	QCA_ATTR_DMG_RF_SECTOR_CFG = 33,
	QCA_ATTR_DMG_RF_SECTOR_MAX,
पूर्ण;

क्रमागत qca_wlan_venकरोr_attr_dmg_rf_sector_type अणु
	QCA_ATTR_DMG_RF_SECTOR_TYPE_RX,
	QCA_ATTR_DMG_RF_SECTOR_TYPE_TX,
	QCA_ATTR_DMG_RF_SECTOR_TYPE_MAX
पूर्ण;

क्रमागत qca_wlan_venकरोr_attr_dmg_rf_sector_cfg अणु
	QCA_ATTR_DMG_RF_SECTOR_CFG_INVALID = 0,
	QCA_ATTR_DMG_RF_SECTOR_CFG_MODULE_INDEX,
	QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE0,
	QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE1,
	QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE2,
	QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_HI,
	QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_LO,
	QCA_ATTR_DMG_RF_SECTOR_CFG_DTYPE_X16,

	/* keep last */
	QCA_ATTR_DMG_RF_SECTOR_CFG_AFTER_LAST,
	QCA_ATTR_DMG_RF_SECTOR_CFG_MAX =
	QCA_ATTR_DMG_RF_SECTOR_CFG_AFTER_LAST - 1
पूर्ण;

अटल स्थिर काष्ठा
nla_policy wil_rf_sector_policy[QCA_ATTR_DMG_RF_SECTOR_MAX + 1] = अणु
	[QCA_ATTR_MAC_ADDR] = अणु .len = ETH_ALEN पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_INDEX] = अणु .type = NLA_U16 पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_TYPE] = अणु .type = NLA_U8 पूर्ण,
	[QCA_ATTR_DMG_RF_MODULE_MASK] = अणु .type = NLA_U32 पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_CFG] = अणु .type = NLA_NESTED पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा
nla_policy wil_rf_sector_cfg_policy[QCA_ATTR_DMG_RF_SECTOR_CFG_MAX + 1] = अणु
	[QCA_ATTR_DMG_RF_SECTOR_CFG_MODULE_INDEX] = अणु .type = NLA_U8 पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE0] = अणु .type = NLA_U32 पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE1] = अणु .type = NLA_U32 पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE2] = अणु .type = NLA_U32 पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_HI] = अणु .type = NLA_U32 पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_LO] = अणु .type = NLA_U32 पूर्ण,
	[QCA_ATTR_DMG_RF_SECTOR_CFG_DTYPE_X16] = अणु .type = NLA_U32 पूर्ण,
पूर्ण;

क्रमागत qca_nl80211_venकरोr_subcmds अणु
	QCA_NL80211_VENDOR_SUBCMD_DMG_RF_GET_SECTOR_CFG = 139,
	QCA_NL80211_VENDOR_SUBCMD_DMG_RF_SET_SECTOR_CFG = 140,
	QCA_NL80211_VENDOR_SUBCMD_DMG_RF_GET_SELECTED_SECTOR = 141,
	QCA_NL80211_VENDOR_SUBCMD_DMG_RF_SET_SELECTED_SECTOR = 142,
पूर्ण;

अटल पूर्णांक wil_rf_sector_get_cfg(काष्ठा wiphy *wiphy,
				 काष्ठा wireless_dev *wdev,
				 स्थिर व्योम *data, पूर्णांक data_len);
अटल पूर्णांक wil_rf_sector_set_cfg(काष्ठा wiphy *wiphy,
				 काष्ठा wireless_dev *wdev,
				 स्थिर व्योम *data, पूर्णांक data_len);
अटल पूर्णांक wil_rf_sector_get_selected(काष्ठा wiphy *wiphy,
				      काष्ठा wireless_dev *wdev,
				      स्थिर व्योम *data, पूर्णांक data_len);
अटल पूर्णांक wil_rf_sector_set_selected(काष्ठा wiphy *wiphy,
				      काष्ठा wireless_dev *wdev,
				      स्थिर व्योम *data, पूर्णांक data_len);

/* venकरोr specअगरic commands */
अटल स्थिर काष्ठा wiphy_venकरोr_command wil_nl80211_venकरोr_commands[] = अणु
	अणु
		.info.venकरोr_id = QCA_NL80211_VENDOR_ID,
		.info.subcmd = QCA_NL80211_VENDOR_SUBCMD_DMG_RF_GET_SECTOR_CFG,
		.flags = WIPHY_VENDOR_CMD_NEED_WDEV |
			 WIPHY_VENDOR_CMD_NEED_RUNNING,
		.policy = wil_rf_sector_policy,
		.करोit = wil_rf_sector_get_cfg
	पूर्ण,
	अणु
		.info.venकरोr_id = QCA_NL80211_VENDOR_ID,
		.info.subcmd = QCA_NL80211_VENDOR_SUBCMD_DMG_RF_SET_SECTOR_CFG,
		.flags = WIPHY_VENDOR_CMD_NEED_WDEV |
			 WIPHY_VENDOR_CMD_NEED_RUNNING,
		.policy = wil_rf_sector_policy,
		.करोit = wil_rf_sector_set_cfg
	पूर्ण,
	अणु
		.info.venकरोr_id = QCA_NL80211_VENDOR_ID,
		.info.subcmd =
			QCA_NL80211_VENDOR_SUBCMD_DMG_RF_GET_SELECTED_SECTOR,
		.flags = WIPHY_VENDOR_CMD_NEED_WDEV |
			 WIPHY_VENDOR_CMD_NEED_RUNNING,
		.policy = wil_rf_sector_policy,
		.करोit = wil_rf_sector_get_selected
	पूर्ण,
	अणु
		.info.venकरोr_id = QCA_NL80211_VENDOR_ID,
		.info.subcmd =
			QCA_NL80211_VENDOR_SUBCMD_DMG_RF_SET_SELECTED_SECTOR,
		.flags = WIPHY_VENDOR_CMD_NEED_WDEV |
			 WIPHY_VENDOR_CMD_NEED_RUNNING,
		.policy = wil_rf_sector_policy,
		.करोit = wil_rf_sector_set_selected
	पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_supported_band wil_band_60ghz = अणु
	.channels = wil_60ghz_channels,
	.n_channels = ARRAY_SIZE(wil_60ghz_channels),
	.ht_cap = अणु
		.ht_supported = true,
		.cap = 0, /* TODO */
		.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K, /* TODO */
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_8, /* TODO */
		.mcs = अणु
				/* MCS 1..12 - SC PHY */
			.rx_mask = अणु0xfe, 0x1fपूर्ण, /* 1..12 */
			.tx_params = IEEE80211_HT_MCS_TX_DEFINED, /* TODO */
		पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_txrx_stypes
wil_mgmt_stypes[NUM_NL80211_IFTYPES] = अणु
	[NL80211_IFTYPE_STATION] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_AP] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4) |
		BIT(IEEE80211_STYPE_ASSOC_RESP >> 4) |
		BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		BIT(IEEE80211_STYPE_AUTH >> 4) |
		BIT(IEEE80211_STYPE_REASSOC_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4) |
		BIT(IEEE80211_STYPE_ASSOC_REQ >> 4) |
		BIT(IEEE80211_STYPE_DISASSOC >> 4) |
		BIT(IEEE80211_STYPE_AUTH >> 4) |
		BIT(IEEE80211_STYPE_DEAUTH >> 4) |
		BIT(IEEE80211_STYPE_REASSOC_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_CLIENT] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_GO] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
	[NL80211_IFTYPE_P2P_DEVICE] = अणु
		.tx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_RESP >> 4),
		.rx = BIT(IEEE80211_STYPE_ACTION >> 4) |
		BIT(IEEE80211_STYPE_PROBE_REQ >> 4)
	पूर्ण,
पूर्ण;

अटल स्थिर u32 wil_cipher_suites[] = अणु
	WLAN_CIPHER_SUITE_GCMP,
पूर्ण;

अटल स्थिर अक्षर * स्थिर key_usage_str[] = अणु
	[WMI_KEY_USE_PAIRWISE]	= "PTK",
	[WMI_KEY_USE_RX_GROUP]	= "RX_GTK",
	[WMI_KEY_USE_TX_GROUP]	= "TX_GTK",
	[WMI_KEY_USE_STORE_PTK]	= "STORE_PTK",
	[WMI_KEY_USE_APPLY_PTK]	= "APPLY_PTK",
पूर्ण;

पूर्णांक wil_अगरtype_nl2wmi(क्रमागत nl80211_अगरtype type)
अणु
	अटल स्थिर काष्ठा अणु
		क्रमागत nl80211_अगरtype nl;
		क्रमागत wmi_network_type wmi;
	पूर्ण __nl2wmi[] = अणु
		अणुNL80211_IFTYPE_ADHOC,		WMI_NETTYPE_ADHOCपूर्ण,
		अणुNL80211_IFTYPE_STATION,	WMI_NETTYPE_INFRAपूर्ण,
		अणुNL80211_IFTYPE_AP,		WMI_NETTYPE_APपूर्ण,
		अणुNL80211_IFTYPE_P2P_CLIENT,	WMI_NETTYPE_P2Pपूर्ण,
		अणुNL80211_IFTYPE_P2P_GO,		WMI_NETTYPE_P2Pपूर्ण,
		अणुNL80211_IFTYPE_MONITOR,	WMI_NETTYPE_ADHOCपूर्ण, /* FIXME */
	पूर्ण;
	uपूर्णांक i;

	क्रम (i = 0; i < ARRAY_SIZE(__nl2wmi); i++) अणु
		अगर (__nl2wmi[i].nl == type)
			वापस __nl2wmi[i].wmi;
	पूर्ण

	वापस -EOPNOTSUPP;
पूर्ण

पूर्णांक wil_spec2wmi_ch(u8 spec_ch, u8 *wmi_ch)
अणु
	चयन (spec_ch) अणु
	हाल 1:
		*wmi_ch = WMI_CHANNEL_1;
		अवरोध;
	हाल 2:
		*wmi_ch = WMI_CHANNEL_2;
		अवरोध;
	हाल 3:
		*wmi_ch = WMI_CHANNEL_3;
		अवरोध;
	हाल 4:
		*wmi_ch = WMI_CHANNEL_4;
		अवरोध;
	हाल 5:
		*wmi_ch = WMI_CHANNEL_5;
		अवरोध;
	हाल 6:
		*wmi_ch = WMI_CHANNEL_6;
		अवरोध;
	हाल 9:
		*wmi_ch = WMI_CHANNEL_9;
		अवरोध;
	हाल 10:
		*wmi_ch = WMI_CHANNEL_10;
		अवरोध;
	हाल 11:
		*wmi_ch = WMI_CHANNEL_11;
		अवरोध;
	हाल 12:
		*wmi_ch = WMI_CHANNEL_12;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wil_wmi2spec_ch(u8 wmi_ch, u8 *spec_ch)
अणु
	चयन (wmi_ch) अणु
	हाल WMI_CHANNEL_1:
		*spec_ch = 1;
		अवरोध;
	हाल WMI_CHANNEL_2:
		*spec_ch = 2;
		अवरोध;
	हाल WMI_CHANNEL_3:
		*spec_ch = 3;
		अवरोध;
	हाल WMI_CHANNEL_4:
		*spec_ch = 4;
		अवरोध;
	हाल WMI_CHANNEL_5:
		*spec_ch = 5;
		अवरोध;
	हाल WMI_CHANNEL_6:
		*spec_ch = 6;
		अवरोध;
	हाल WMI_CHANNEL_9:
		*spec_ch = 9;
		अवरोध;
	हाल WMI_CHANNEL_10:
		*spec_ch = 10;
		अवरोध;
	हाल WMI_CHANNEL_11:
		*spec_ch = 11;
		अवरोध;
	हाल WMI_CHANNEL_12:
		*spec_ch = 12;
		अवरोध;
	शेष:
		वापस -EINVAL;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wil_cid_fill_sinfo(काष्ठा wil6210_vअगर *vअगर, पूर्णांक cid,
		       काष्ठा station_info *sinfo)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wmi_notअगरy_req_cmd cmd = अणु
		.cid = cid,
		.पूर्णांकerval_usec = 0,
	पूर्ण;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_notअगरy_req_करोne_event evt;
	पूर्ण __packed reply;
	काष्ठा wil_net_stats *stats = &wil->sta[cid].stats;
	पूर्णांक rc;
	u8 tx_mcs, rx_mcs;
	u8 tx_rate_flag = RATE_INFO_FLAGS_DMG;
	u8 rx_rate_flag = RATE_INFO_FLAGS_DMG;

	स_रखो(&reply, 0, माप(reply));

	rc = wmi_call(wil, WMI_NOTIFY_REQ_CMDID, vअगर->mid, &cmd, माप(cmd),
		      WMI_NOTIFY_REQ_DONE_EVENTID, &reply, माप(reply),
		      WIL_WMI_CALL_GENERAL_TO_MS);
	अगर (rc)
		वापस rc;

	tx_mcs = le16_to_cpu(reply.evt.bf_mcs);

	wil_dbg_wmi(wil, "Link status for CID %d MID %d: {\n"
		    "  MCS %s TSF 0x%016llx\n"
		    "  BF status 0x%08x RSSI %d SQI %d%%\n"
		    "  Tx Tpt %d goodput %d Rx goodput %d\n"
		    "  Sectors(rx:tx) my %d:%d peer %d:%d\n"
		    "  Tx mode %d}\n",
		    cid, vअगर->mid, WIL_EXTENDED_MCS_CHECK(tx_mcs),
		    le64_to_cpu(reply.evt.tsf), reply.evt.status,
		    reply.evt.rssi,
		    reply.evt.sqi,
		    le32_to_cpu(reply.evt.tx_tpt),
		    le32_to_cpu(reply.evt.tx_goodput),
		    le32_to_cpu(reply.evt.rx_goodput),
		    le16_to_cpu(reply.evt.my_rx_sector),
		    le16_to_cpu(reply.evt.my_tx_sector),
		    le16_to_cpu(reply.evt.other_rx_sector),
		    le16_to_cpu(reply.evt.other_tx_sector),
		    reply.evt.tx_mode);

	sinfo->generation = wil->sinfo_gen;

	sinfo->filled = BIT_ULL(NL80211_STA_INFO_RX_BYTES) |
			BIT_ULL(NL80211_STA_INFO_TX_BYTES) |
			BIT_ULL(NL80211_STA_INFO_RX_PACKETS) |
			BIT_ULL(NL80211_STA_INFO_TX_PACKETS) |
			BIT_ULL(NL80211_STA_INFO_RX_BITRATE) |
			BIT_ULL(NL80211_STA_INFO_TX_BITRATE) |
			BIT_ULL(NL80211_STA_INFO_RX_DROP_MISC) |
			BIT_ULL(NL80211_STA_INFO_TX_FAILED);

	अगर (wil->use_enhanced_dma_hw && reply.evt.tx_mode != WMI_TX_MODE_DMG) अणु
		tx_rate_flag = RATE_INFO_FLAGS_EDMG;
		rx_rate_flag = RATE_INFO_FLAGS_EDMG;
	पूर्ण

	rx_mcs = stats->last_mcs_rx;

	/* check extended MCS (12.1) and convert it पूर्णांकo
	 * base MCS (7) + EXTENDED_SC_DMG flag
	 */
	अगर (tx_mcs == WIL_EXTENDED_MCS_26) अणु
		tx_rate_flag = RATE_INFO_FLAGS_EXTENDED_SC_DMG;
		tx_mcs = WIL_BASE_MCS_FOR_EXTENDED_26;
	पूर्ण
	अगर (rx_mcs == WIL_EXTENDED_MCS_26) अणु
		rx_rate_flag = RATE_INFO_FLAGS_EXTENDED_SC_DMG;
		rx_mcs = WIL_BASE_MCS_FOR_EXTENDED_26;
	पूर्ण

	sinfo->txrate.flags = tx_rate_flag;
	sinfo->rxrate.flags = rx_rate_flag;
	sinfo->txrate.mcs = tx_mcs;
	sinfo->rxrate.mcs = rx_mcs;

	sinfo->txrate.n_bonded_ch =
				  wil_tx_cb_mode_to_n_bonded(reply.evt.tx_mode);
	sinfo->rxrate.n_bonded_ch =
			     wil_rx_cb_mode_to_n_bonded(stats->last_cb_mode_rx);
	sinfo->rx_bytes = stats->rx_bytes;
	sinfo->rx_packets = stats->rx_packets;
	sinfo->rx_dropped_misc = stats->rx_dropped;
	sinfo->tx_bytes = stats->tx_bytes;
	sinfo->tx_packets = stats->tx_packets;
	sinfo->tx_failed = stats->tx_errors;

	अगर (test_bit(wil_vअगर_fwconnected, vअगर->status)) अणु
		sinfo->filled |= BIT_ULL(NL80211_STA_INFO_SIGNAL);
		अगर (test_bit(WMI_FW_CAPABILITY_RSSI_REPORTING,
			     wil->fw_capabilities))
			sinfo->संकेत = reply.evt.rssi;
		अन्यथा
			sinfo->संकेत = reply.evt.sqi;
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_get_station(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *ndev,
				    स्थिर u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	पूर्णांक rc;

	पूर्णांक cid = wil_find_cid(wil, vअगर->mid, mac);

	wil_dbg_misc(wil, "get_station: %pM CID %d MID %d\n", mac, cid,
		     vअगर->mid);
	अगर (!wil_cid_valid(wil, cid))
		वापस -ENOENT;

	rc = wil_cid_fill_sinfo(vअगर, cid, sinfo);

	वापस rc;
पूर्ण

/*
 * Find @idx-th active STA क्रम specअगरic MID क्रम station dump.
 */
पूर्णांक wil_find_cid_by_idx(काष्ठा wil6210_priv *wil, u8 mid, पूर्णांक idx)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
		अगर (wil->sta[i].status == wil_sta_unused)
			जारी;
		अगर (wil->sta[i].mid != mid)
			जारी;
		अगर (idx == 0)
			वापस i;
		idx--;
	पूर्ण

	वापस -ENOENT;
पूर्ण

अटल पूर्णांक wil_cfg80211_dump_station(काष्ठा wiphy *wiphy,
				     काष्ठा net_device *dev, पूर्णांक idx,
				     u8 *mac, काष्ठा station_info *sinfo)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	पूर्णांक rc;
	पूर्णांक cid = wil_find_cid_by_idx(wil, vअगर->mid, idx);

	अगर (!wil_cid_valid(wil, cid))
		वापस -ENOENT;

	ether_addr_copy(mac, wil->sta[cid].addr);
	wil_dbg_misc(wil, "dump_station: %pM CID %d MID %d\n", mac, cid,
		     vअगर->mid);

	rc = wil_cid_fill_sinfo(vअगर, cid, sinfo);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_start_p2p_device(काष्ठा wiphy *wiphy,
					 काष्ठा wireless_dev *wdev)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil_dbg_misc(wil, "start_p2p_device: entered\n");
	wil->p2p_dev_started = 1;
	वापस 0;
पूर्ण

अटल व्योम wil_cfg80211_stop_p2p_device(काष्ठा wiphy *wiphy,
					 काष्ठा wireless_dev *wdev)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);

	अगर (!wil->p2p_dev_started)
		वापस;

	wil_dbg_misc(wil, "stop_p2p_device: entered\n");
	mutex_lock(&wil->mutex);
	mutex_lock(&wil->vअगर_mutex);
	wil_p2p_stop_radio_operations(wil);
	wil->p2p_dev_started = 0;
	mutex_unlock(&wil->vअगर_mutex);
	mutex_unlock(&wil->mutex);
पूर्ण

अटल पूर्णांक wil_cfg80211_validate_add_अगरace(काष्ठा wil6210_priv *wil,
					   क्रमागत nl80211_अगरtype new_type)
अणु
	पूर्णांक i;
	काष्ठा wireless_dev *wdev;
	काष्ठा अगरace_combination_params params = अणु
		.num_dअगरferent_channels = 1,
	पूर्ण;

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		अगर (wil->vअगरs[i]) अणु
			wdev = vअगर_to_wdev(wil->vअगरs[i]);
			params.अगरtype_num[wdev->अगरtype]++;
		पूर्ण
	पूर्ण
	params.अगरtype_num[new_type]++;
	वापस cfg80211_check_combinations(wil->wiphy, &params);
पूर्ण

अटल पूर्णांक wil_cfg80211_validate_change_अगरace(काष्ठा wil6210_priv *wil,
					      काष्ठा wil6210_vअगर *vअगर,
					      क्रमागत nl80211_अगरtype new_type)
अणु
	पूर्णांक i, ret = 0;
	काष्ठा wireless_dev *wdev;
	काष्ठा अगरace_combination_params params = अणु
		.num_dअगरferent_channels = 1,
	पूर्ण;
	bool check_combos = false;

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		काष्ठा wil6210_vअगर *vअगर_pos = wil->vअगरs[i];

		अगर (vअगर_pos && vअगर != vअगर_pos) अणु
			wdev = vअगर_to_wdev(vअगर_pos);
			params.अगरtype_num[wdev->अगरtype]++;
			check_combos = true;
		पूर्ण
	पूर्ण

	अगर (check_combos) अणु
		params.अगरtype_num[new_type]++;
		ret = cfg80211_check_combinations(wil->wiphy, &params);
	पूर्ण
	वापस ret;
पूर्ण

अटल काष्ठा wireless_dev *
wil_cfg80211_add_अगरace(काष्ठा wiphy *wiphy, स्थिर अक्षर *name,
		       अचिन्हित अक्षर name_assign_type,
		       क्रमागत nl80211_अगरtype type,
		       काष्ठा vअगर_params *params)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा net_device *ndev_मुख्य = wil->मुख्य_ndev, *ndev;
	काष्ठा wil6210_vअगर *vअगर;
	काष्ठा wireless_dev *p2p_wdev, *wdev;
	पूर्णांक rc;

	wil_dbg_misc(wil, "add_iface, type %d\n", type);

	/* P2P device is not a real भव पूर्णांकerface, it is a management-only
	 * पूर्णांकerface that shares the मुख्य पूर्णांकerface.
	 * Skip concurrency checks here.
	 */
	अगर (type == NL80211_IFTYPE_P2P_DEVICE) अणु
		अगर (wil->p2p_wdev) अणु
			wil_err(wil, "P2P_DEVICE interface already created\n");
			वापस ERR_PTR(-EINVAL);
		पूर्ण

		p2p_wdev = kzalloc(माप(*p2p_wdev), GFP_KERNEL);
		अगर (!p2p_wdev)
			वापस ERR_PTR(-ENOMEM);

		p2p_wdev->अगरtype = type;
		p2p_wdev->wiphy = wiphy;
		/* use our primary ethernet address */
		ether_addr_copy(p2p_wdev->address, ndev_मुख्य->perm_addr);

		wil->p2p_wdev = p2p_wdev;

		वापस p2p_wdev;
	पूर्ण

	अगर (!wil->wiphy->n_अगरace_combinations) अणु
		wil_err(wil, "virtual interfaces not supported\n");
		वापस ERR_PTR(-EINVAL);
	पूर्ण

	rc = wil_cfg80211_validate_add_अगरace(wil, type);
	अगर (rc) अणु
		wil_err(wil, "iface validation failed, err=%d\n", rc);
		वापस ERR_PTR(rc);
	पूर्ण

	vअगर = wil_vअगर_alloc(wil, name, name_assign_type, type);
	अगर (IS_ERR(vअगर))
		वापस ERR_CAST(vअगर);

	ndev = vअगर_to_ndev(vअगर);
	ether_addr_copy(ndev->perm_addr, ndev_मुख्य->perm_addr);
	अगर (is_valid_ether_addr(params->macaddr)) अणु
		ether_addr_copy(ndev->dev_addr, params->macaddr);
	पूर्ण अन्यथा अणु
		ether_addr_copy(ndev->dev_addr, ndev_मुख्य->perm_addr);
		ndev->dev_addr[0] = (ndev->dev_addr[0] ^ (1 << vअगर->mid)) |
			0x2; /* locally administered */
	पूर्ण
	wdev = vअगर_to_wdev(vअगर);
	ether_addr_copy(wdev->address, ndev->dev_addr);

	rc = wil_vअगर_add(wil, vअगर);
	अगर (rc)
		जाओ out;

	wil_info(wil, "added VIF, mid %d iftype %d MAC %pM\n",
		 vअगर->mid, type, wdev->address);
	वापस wdev;
out:
	wil_vअगर_मुक्त(vअगर);
	वापस ERR_PTR(rc);
पूर्ण

पूर्णांक wil_vअगर_prepare_stop(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	काष्ठा net_device *ndev;
	पूर्णांक rc;

	अगर (wdev->अगरtype != NL80211_IFTYPE_AP)
		वापस 0;

	ndev = vअगर_to_ndev(vअगर);
	अगर (netअगर_carrier_ok(ndev)) अणु
		rc = wmi_pcp_stop(vअगर);
		अगर (rc) अणु
			wil_info(wil, "failed to stop AP, status %d\n",
				 rc);
			/* जारी */
		पूर्ण
		wil_bcast_fini(vअगर);
		netअगर_carrier_off(ndev);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wil_cfg80211_del_अगरace(काष्ठा wiphy *wiphy,
				  काष्ठा wireless_dev *wdev)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);
	पूर्णांक rc;

	wil_dbg_misc(wil, "del_iface\n");

	अगर (wdev->अगरtype == NL80211_IFTYPE_P2P_DEVICE) अणु
		अगर (wdev != wil->p2p_wdev) अणु
			wil_err(wil, "delete of incorrect interface 0x%p\n",
				wdev);
			वापस -EINVAL;
		पूर्ण

		wil_cfg80211_stop_p2p_device(wiphy, wdev);
		wil_p2p_wdev_मुक्त(wil);
		वापस 0;
	पूर्ण

	अगर (vअगर->mid == 0) अणु
		wil_err(wil, "cannot remove the main interface\n");
		वापस -EINVAL;
	पूर्ण

	rc = wil_vअगर_prepare_stop(vअगर);
	अगर (rc)
		जाओ out;

	wil_info(wil, "deleted VIF, mid %d iftype %d MAC %pM\n",
		 vअगर->mid, wdev->अगरtype, wdev->address);

	wil_vअगर_हटाओ(wil, vअगर->mid);
out:
	वापस rc;
पूर्ण

अटल bool wil_is_safe_चयन(क्रमागत nl80211_अगरtype from,
			       क्रमागत nl80211_अगरtype to)
अणु
	अगर (from == NL80211_IFTYPE_STATION &&
	    to == NL80211_IFTYPE_P2P_CLIENT)
		वापस true;

	वापस false;
पूर्ण

अटल पूर्णांक wil_cfg80211_change_अगरace(काष्ठा wiphy *wiphy,
				     काष्ठा net_device *ndev,
				     क्रमागत nl80211_अगरtype type,
				     काष्ठा vअगर_params *params)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	पूर्णांक rc;
	bool fw_reset = false;

	wil_dbg_misc(wil, "change_iface: type=%d\n", type);

	अगर (wiphy->n_अगरace_combinations) अणु
		rc = wil_cfg80211_validate_change_अगरace(wil, vअगर, type);
		अगर (rc) अणु
			wil_err(wil, "iface validation failed, err=%d\n", rc);
			वापस rc;
		पूर्ण
	पूर्ण

	/* करो not reset FW when there are active VIFs,
	 * because it can cause signअगरicant disruption
	 */
	अगर (!wil_has_other_active_अगरaces(wil, ndev, true, false) &&
	    netअगर_running(ndev) && !wil_is_recovery_blocked(wil) &&
	    !wil_is_safe_चयन(wdev->अगरtype, type)) अणु
		wil_dbg_misc(wil, "interface is up. resetting...\n");
		mutex_lock(&wil->mutex);
		__wil_करोwn(wil);
		rc = __wil_up(wil);
		mutex_unlock(&wil->mutex);

		अगर (rc)
			वापस rc;
		fw_reset = true;
	पूर्ण

	चयन (type) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_AP:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_GO:
		अवरोध;
	हाल NL80211_IFTYPE_MONITOR:
		अगर (params->flags)
			wil->monitor_flags = params->flags;
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (vअगर->mid != 0 && wil_has_active_अगरaces(wil, true, false)) अणु
		अगर (!fw_reset)
			wil_vअगर_prepare_stop(vअगर);
		rc = wmi_port_delete(wil, vअगर->mid);
		अगर (rc)
			वापस rc;
		rc = wmi_port_allocate(wil, vअगर->mid, ndev->dev_addr, type);
		अगर (rc)
			वापस rc;
	पूर्ण

	wdev->अगरtype = type;
	वापस 0;
पूर्ण

अटल पूर्णांक wil_cfg80211_scan(काष्ठा wiphy *wiphy,
			     काष्ठा cfg80211_scan_request *request)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wireless_dev *wdev = request->wdev;
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);
	काष्ठा अणु
		काष्ठा wmi_start_scan_cmd cmd;
		u16 chnl[4];
	पूर्ण __packed cmd;
	uपूर्णांक i, n;
	पूर्णांक rc;

	wil_dbg_misc(wil, "scan: wdev=0x%p iftype=%d\n", wdev, wdev->अगरtype);

	/* scan is supported on client पूर्णांकerfaces and on AP पूर्णांकerface */
	चयन (wdev->अगरtype) अणु
	हाल NL80211_IFTYPE_STATION:
	हाल NL80211_IFTYPE_P2P_CLIENT:
	हाल NL80211_IFTYPE_P2P_DEVICE:
	हाल NL80211_IFTYPE_AP:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	/* FW करोn't support scan after connection attempt */
	अगर (test_bit(wil_status_करोntscan, wil->status)) अणु
		wil_err(wil, "Can't scan now\n");
		वापस -EBUSY;
	पूर्ण

	mutex_lock(&wil->mutex);

	mutex_lock(&wil->vअगर_mutex);
	अगर (vअगर->scan_request || vअगर->p2p.discovery_started) अणु
		wil_err(wil, "Already scanning\n");
		mutex_unlock(&wil->vअगर_mutex);
		rc = -EAGAIN;
		जाओ out;
	पूर्ण
	mutex_unlock(&wil->vअगर_mutex);

	अगर (wdev->अगरtype == NL80211_IFTYPE_P2P_DEVICE) अणु
		अगर (!wil->p2p_dev_started) अणु
			wil_err(wil, "P2P search requested on stopped P2P device\n");
			rc = -EIO;
			जाओ out;
		पूर्ण
		/* social scan on P2P_DEVICE is handled as p2p search */
		अगर (wil_p2p_is_social_scan(request)) अणु
			vअगर->scan_request = request;
			अगर (vअगर->mid == 0)
				wil->radio_wdev = wdev;
			rc = wil_p2p_search(vअगर, request);
			अगर (rc) अणु
				अगर (vअगर->mid == 0)
					wil->radio_wdev =
						wil->मुख्य_ndev->ieee80211_ptr;
				vअगर->scan_request = शून्य;
			पूर्ण
			जाओ out;
		पूर्ण
	पूर्ण

	(व्योम)wil_p2p_stop_discovery(vअगर);

	wil_dbg_misc(wil, "Start scan_request 0x%p\n", request);
	wil_dbg_misc(wil, "SSID count: %d", request->n_ssids);

	क्रम (i = 0; i < request->n_ssids; i++) अणु
		wil_dbg_misc(wil, "SSID[%d]", i);
		wil_hex_dump_misc("SSID ", DUMP_PREFIX_OFFSET, 16, 1,
				  request->ssids[i].ssid,
				  request->ssids[i].ssid_len, true);
	पूर्ण

	अगर (request->n_ssids)
		rc = wmi_set_ssid(vअगर, request->ssids[0].ssid_len,
				  request->ssids[0].ssid);
	अन्यथा
		rc = wmi_set_ssid(vअगर, 0, शून्य);

	अगर (rc) अणु
		wil_err(wil, "set SSID for scan request failed: %d\n", rc);
		जाओ out;
	पूर्ण

	vअगर->scan_request = request;
	mod_समयr(&vअगर->scan_समयr, jअगरfies + WIL6210_SCAN_TO);

	स_रखो(&cmd, 0, माप(cmd));
	cmd.cmd.scan_type = WMI_ACTIVE_SCAN;
	cmd.cmd.num_channels = 0;
	n = min(request->n_channels, 4U);
	क्रम (i = 0; i < n; i++) अणु
		पूर्णांक ch = request->channels[i]->hw_value;

		अगर (ch == 0) अणु
			wil_err(wil,
				"Scan requested for unknown frequency %dMhz\n",
				request->channels[i]->center_freq);
			जारी;
		पूर्ण
		/* 0-based channel indexes */
		cmd.cmd.channel_list[cmd.cmd.num_channels++].channel = ch - 1;
		wil_dbg_misc(wil, "Scan for ch %d  : %d MHz\n", ch,
			     request->channels[i]->center_freq);
	पूर्ण

	अगर (request->ie_len)
		wil_hex_dump_misc("Scan IE ", DUMP_PREFIX_OFFSET, 16, 1,
				  request->ie, request->ie_len, true);
	अन्यथा
		wil_dbg_misc(wil, "Scan has no IE's\n");

	rc = wmi_set_ie(vअगर, WMI_FRAME_PROBE_REQ,
			request->ie_len, request->ie);
	अगर (rc)
		जाओ out_restore;

	अगर (wil->discovery_mode && cmd.cmd.scan_type == WMI_ACTIVE_SCAN) अणु
		cmd.cmd.discovery_mode = 1;
		wil_dbg_misc(wil, "active scan with discovery_mode=1\n");
	पूर्ण

	अगर (vअगर->mid == 0)
		wil->radio_wdev = wdev;
	rc = wmi_send(wil, WMI_START_SCAN_CMDID, vअगर->mid,
		      &cmd, माप(cmd.cmd) +
		      cmd.cmd.num_channels * माप(cmd.cmd.channel_list[0]));

out_restore:
	अगर (rc) अणु
		del_समयr_sync(&vअगर->scan_समयr);
		अगर (vअगर->mid == 0)
			wil->radio_wdev = wil->मुख्य_ndev->ieee80211_ptr;
		vअगर->scan_request = शून्य;
	पूर्ण
out:
	mutex_unlock(&wil->mutex);
	वापस rc;
पूर्ण

अटल व्योम wil_cfg80211_पात_scan(काष्ठा wiphy *wiphy,
				    काष्ठा wireless_dev *wdev)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);

	wil_dbg_misc(wil, "wdev=0x%p iftype=%d\n", wdev, wdev->अगरtype);

	mutex_lock(&wil->mutex);
	mutex_lock(&wil->vअगर_mutex);

	अगर (!vअगर->scan_request)
		जाओ out;

	अगर (wdev != vअगर->scan_request->wdev) अणु
		wil_dbg_misc(wil, "abort scan was called on the wrong iface\n");
		जाओ out;
	पूर्ण

	अगर (wdev == wil->p2p_wdev && wil->radio_wdev == wil->p2p_wdev)
		wil_p2p_stop_radio_operations(wil);
	अन्यथा
		wil_पात_scan(vअगर, true);

out:
	mutex_unlock(&wil->vअगर_mutex);
	mutex_unlock(&wil->mutex);
पूर्ण

अटल व्योम wil_prपूर्णांक_crypto(काष्ठा wil6210_priv *wil,
			     काष्ठा cfg80211_crypto_settings *c)
अणु
	पूर्णांक i, n;

	wil_dbg_misc(wil, "WPA versions: 0x%08x cipher group 0x%08x\n",
		     c->wpa_versions, c->cipher_group);
	wil_dbg_misc(wil, "Pairwise ciphers [%d] {\n", c->n_ciphers_pairwise);
	n = min_t(पूर्णांक, c->n_ciphers_pairwise, ARRAY_SIZE(c->ciphers_pairwise));
	क्रम (i = 0; i < n; i++)
		wil_dbg_misc(wil, "  [%d] = 0x%08x\n", i,
			     c->ciphers_pairwise[i]);
	wil_dbg_misc(wil, "}\n");
	wil_dbg_misc(wil, "AKM suites [%d] {\n", c->n_akm_suites);
	n = min_t(पूर्णांक, c->n_akm_suites, ARRAY_SIZE(c->akm_suites));
	क्रम (i = 0; i < n; i++)
		wil_dbg_misc(wil, "  [%d] = 0x%08x\n", i,
			     c->akm_suites[i]);
	wil_dbg_misc(wil, "}\n");
	wil_dbg_misc(wil, "Control port : %d, eth_type 0x%04x no_encrypt %d\n",
		     c->control_port, be16_to_cpu(c->control_port_ethertype),
		     c->control_port_no_encrypt);
पूर्ण

अटल स्थिर अक्षर *
wil_get_auth_type_name(क्रमागत nl80211_auth_type auth_type)
अणु
	चयन (auth_type) अणु
	हाल NL80211_AUTHTYPE_OPEN_SYSTEM:
		वापस "OPEN_SYSTEM";
	हाल NL80211_AUTHTYPE_SHARED_KEY:
		वापस "SHARED_KEY";
	हाल NL80211_AUTHTYPE_FT:
		वापस "FT";
	हाल NL80211_AUTHTYPE_NETWORK_EAP:
		वापस "NETWORK_EAP";
	हाल NL80211_AUTHTYPE_SAE:
		वापस "SAE";
	हाल NL80211_AUTHTYPE_AUTOMATIC:
		वापस "AUTOMATIC";
	शेष:
		वापस "unknown";
	पूर्ण
पूर्ण
अटल व्योम wil_prपूर्णांक_connect_params(काष्ठा wil6210_priv *wil,
				     काष्ठा cfg80211_connect_params *sme)
अणु
	wil_info(wil, "Connecting to:\n");
	अगर (sme->channel) अणु
		wil_info(wil, "  Channel: %d freq %d\n",
			 sme->channel->hw_value, sme->channel->center_freq);
	पूर्ण
	अगर (sme->bssid)
		wil_info(wil, "  BSSID: %pM\n", sme->bssid);
	अगर (sme->ssid)
		prपूर्णांक_hex_dump(KERN_INFO, "  SSID: ", DUMP_PREFIX_OFFSET,
			       16, 1, sme->ssid, sme->ssid_len, true);
	अगर (sme->prev_bssid)
		wil_info(wil, "  Previous BSSID=%pM\n", sme->prev_bssid);
	wil_info(wil, "  Auth Type: %s\n",
		 wil_get_auth_type_name(sme->auth_type));
	wil_info(wil, "  Privacy: %s\n", sme->privacy ? "secure" : "open");
	wil_info(wil, "  PBSS: %d\n", sme->pbss);
	wil_prपूर्णांक_crypto(wil, &sme->crypto);
पूर्ण

अटल पूर्णांक wil_ft_connect(काष्ठा wiphy *wiphy,
			  काष्ठा net_device *ndev,
			  काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wmi_ft_auth_cmd auth_cmd;
	पूर्णांक rc;

	अगर (!test_bit(WMI_FW_CAPABILITY_FT_ROAMING, wil->fw_capabilities)) अणु
		wil_err(wil, "FT: FW does not support FT roaming\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!sme->prev_bssid) अणु
		wil_err(wil, "FT: prev_bssid was not set\n");
		वापस -EINVAL;
	पूर्ण

	अगर (ether_addr_equal(sme->prev_bssid, sme->bssid)) अणु
		wil_err(wil, "FT: can not roam to same AP\n");
		वापस -EINVAL;
	पूर्ण

	अगर (!test_bit(wil_vअगर_fwconnected, vअगर->status)) अणु
		wil_err(wil, "FT: roam while not connected\n");
		वापस -EINVAL;
	पूर्ण

	अगर (vअगर->privacy != sme->privacy) अणु
		wil_err(wil, "FT: privacy mismatch, current (%d) roam (%d)\n",
			vअगर->privacy, sme->privacy);
		वापस -EINVAL;
	पूर्ण

	अगर (sme->pbss) अणु
		wil_err(wil, "FT: roam is not valid for PBSS\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&auth_cmd, 0, माप(auth_cmd));
	auth_cmd.channel = sme->channel->hw_value - 1;
	ether_addr_copy(auth_cmd.bssid, sme->bssid);

	wil_info(wil, "FT: roaming\n");

	set_bit(wil_vअगर_ft_roam, vअगर->status);
	rc = wmi_send(wil, WMI_FT_AUTH_CMDID, vअगर->mid,
		      &auth_cmd, माप(auth_cmd));
	अगर (rc == 0)
		mod_समयr(&vअगर->connect_समयr,
			  jअगरfies + msecs_to_jअगरfies(5000));
	अन्यथा
		clear_bit(wil_vअगर_ft_roam, vअगर->status);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_get_wmi_edmg_channel(काष्ठा wil6210_priv *wil, u8 edmg_bw_config,
				    u8 edmg_channels, u8 *wmi_ch)
अणु
	अगर (!edmg_bw_config) अणु
		*wmi_ch = 0;
		वापस 0;
	पूर्ण अन्यथा अगर (edmg_bw_config == WIL_EDMG_BW_CONFIGURATION) अणु
		/* convert from edmg channel biपंचांगap पूर्णांकo edmg channel number */
		चयन (edmg_channels) अणु
		हाल WIL_EDMG_CHANNEL_9_SUBCHANNELS:
			वापस wil_spec2wmi_ch(9, wmi_ch);
		हाल WIL_EDMG_CHANNEL_10_SUBCHANNELS:
			वापस wil_spec2wmi_ch(10, wmi_ch);
		हाल WIL_EDMG_CHANNEL_11_SUBCHANNELS:
			वापस wil_spec2wmi_ch(11, wmi_ch);
		शेष:
			wil_err(wil, "Unsupported edmg channel bitmap 0x%x\n",
				edmg_channels);
			वापस -EINVAL;
		पूर्ण
	पूर्ण अन्यथा अणु
		wil_err(wil, "Unsupported EDMG BW configuration %d\n",
			edmg_bw_config);
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक wil_cfg80211_connect(काष्ठा wiphy *wiphy,
				काष्ठा net_device *ndev,
				काष्ठा cfg80211_connect_params *sme)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा cfg80211_bss *bss;
	काष्ठा wmi_connect_cmd conn;
	स्थिर u8 *ssid_eid;
	स्थिर u8 *rsn_eid;
	पूर्णांक ch;
	पूर्णांक rc = 0;
	bool is_ft_roam = false;
	u8 network_type;
	क्रमागत ieee80211_bss_type bss_type = IEEE80211_BSS_TYPE_ESS;

	wil_dbg_misc(wil, "connect, mid=%d\n", vअगर->mid);
	wil_prपूर्णांक_connect_params(wil, sme);

	अगर (sme->auth_type == NL80211_AUTHTYPE_FT)
		is_ft_roam = true;
	अगर (sme->auth_type == NL80211_AUTHTYPE_AUTOMATIC &&
	    test_bit(wil_vअगर_fwconnected, vअगर->status))
		is_ft_roam = true;

	अगर (!is_ft_roam)
		अगर (test_bit(wil_vअगर_fwconnecting, vअगर->status) ||
		    test_bit(wil_vअगर_fwconnected, vअगर->status))
			वापस -EALREADY;

	अगर (sme->ie_len > WMI_MAX_IE_LEN) अणु
		wil_err(wil, "IE too large (%td bytes)\n", sme->ie_len);
		वापस -दुस्फल;
	पूर्ण

	rsn_eid = sme->ie ?
			cfg80211_find_ie(WLAN_EID_RSN, sme->ie, sme->ie_len) :
			शून्य;
	अगर (sme->privacy && !rsn_eid) अणु
		wil_info(wil, "WSC connection\n");
		अगर (is_ft_roam) अणु
			wil_err(wil, "No WSC with FT roam\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (sme->pbss)
		bss_type = IEEE80211_BSS_TYPE_PBSS;

	bss = cfg80211_get_bss(wiphy, sme->channel, sme->bssid,
			       sme->ssid, sme->ssid_len,
			       bss_type, IEEE80211_PRIVACY_ANY);
	अगर (!bss) अणु
		wil_err(wil, "Unable to find BSS\n");
		वापस -ENOENT;
	पूर्ण

	ssid_eid = ieee80211_bss_get_ie(bss, WLAN_EID_SSID);
	अगर (!ssid_eid) अणु
		wil_err(wil, "No SSID\n");
		rc = -ENOENT;
		जाओ out;
	पूर्ण
	vअगर->privacy = sme->privacy;
	vअगर->pbss = sme->pbss;

	rc = wmi_set_ie(vअगर, WMI_FRAME_ASSOC_REQ, sme->ie_len, sme->ie);
	अगर (rc)
		जाओ out;

	चयन (bss->capability & WLAN_CAPABILITY_DMG_TYPE_MASK) अणु
	हाल WLAN_CAPABILITY_DMG_TYPE_AP:
		network_type = WMI_NETTYPE_INFRA;
		अवरोध;
	हाल WLAN_CAPABILITY_DMG_TYPE_PBSS:
		network_type = WMI_NETTYPE_P2P;
		अवरोध;
	शेष:
		wil_err(wil, "Unsupported BSS type, capability= 0x%04x\n",
			bss->capability);
		rc = -EINVAL;
		जाओ out;
	पूर्ण

	ch = bss->channel->hw_value;
	अगर (ch == 0) अणु
		wil_err(wil, "BSS at unknown frequency %dMhz\n",
			bss->channel->center_freq);
		rc = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	अगर (is_ft_roam) अणु
		अगर (network_type != WMI_NETTYPE_INFRA) अणु
			wil_err(wil, "FT: Unsupported BSS type, capability= 0x%04x\n",
				bss->capability);
			rc = -EINVAL;
			जाओ out;
		पूर्ण
		rc = wil_ft_connect(wiphy, ndev, sme);
		अगर (rc == 0)
			vअगर->bss = bss;
		जाओ out;
	पूर्ण

	अगर (vअगर->privacy) अणु
		/* For secure assoc, हटाओ old keys */
		rc = wmi_del_cipher_key(vअगर, 0, bss->bssid,
					WMI_KEY_USE_PAIRWISE);
		अगर (rc) अणु
			wil_err(wil, "WMI_DELETE_CIPHER_KEY_CMD(PTK) failed\n");
			जाओ out;
		पूर्ण
		rc = wmi_del_cipher_key(vअगर, 0, bss->bssid,
					WMI_KEY_USE_RX_GROUP);
		अगर (rc) अणु
			wil_err(wil, "WMI_DELETE_CIPHER_KEY_CMD(GTK) failed\n");
			जाओ out;
		पूर्ण
	पूर्ण

	/* WMI_CONNECT_CMD */
	स_रखो(&conn, 0, माप(conn));
	conn.network_type = network_type;
	अगर (vअगर->privacy) अणु
		अगर (rsn_eid) अणु /* regular secure connection */
			conn.करोt11_auth_mode = WMI_AUTH11_SHARED;
			conn.auth_mode = WMI_AUTH_WPA2_PSK;
			conn.pairwise_crypto_type = WMI_CRYPT_AES_GCMP;
			conn.pairwise_crypto_len = 16;
			conn.group_crypto_type = WMI_CRYPT_AES_GCMP;
			conn.group_crypto_len = 16;
		पूर्ण अन्यथा अणु /* WSC */
			conn.करोt11_auth_mode = WMI_AUTH11_WSC;
			conn.auth_mode = WMI_AUTH_NONE;
		पूर्ण
	पूर्ण अन्यथा अणु /* insecure connection */
		conn.करोt11_auth_mode = WMI_AUTH11_OPEN;
		conn.auth_mode = WMI_AUTH_NONE;
	पूर्ण

	conn.ssid_len = min_t(u8, ssid_eid[1], 32);
	स_नकल(conn.ssid, ssid_eid+2, conn.ssid_len);
	conn.channel = ch - 1;

	rc = wil_get_wmi_edmg_channel(wil, sme->edmg.bw_config,
				      sme->edmg.channels, &conn.edmg_channel);
	अगर (rc < 0)
		वापस rc;

	ether_addr_copy(conn.bssid, bss->bssid);
	ether_addr_copy(conn.dst_mac, bss->bssid);

	set_bit(wil_vअगर_fwconnecting, vअगर->status);

	rc = wmi_send(wil, WMI_CONNECT_CMDID, vअगर->mid, &conn, माप(conn));
	अगर (rc == 0) अणु
		netअगर_carrier_on(ndev);
		अगर (!wil_has_other_active_अगरaces(wil, ndev, false, true))
			wil6210_bus_request(wil, WIL_MAX_BUS_REQUEST_KBPS);
		vअगर->bss = bss;
		/* Connect can take lots of समय */
		mod_समयr(&vअगर->connect_समयr,
			  jअगरfies + msecs_to_jअगरfies(5000));
	पूर्ण अन्यथा अणु
		clear_bit(wil_vअगर_fwconnecting, vअगर->status);
	पूर्ण

 out:
	cfg80211_put_bss(wiphy, bss);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_disconnect(काष्ठा wiphy *wiphy,
				   काष्ठा net_device *ndev,
				   u16 reason_code)
अणु
	पूर्णांक rc;
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);

	wil_dbg_misc(wil, "disconnect: reason=%d, mid=%d\n",
		     reason_code, vअगर->mid);

	अगर (!(test_bit(wil_vअगर_fwconnecting, vअगर->status) ||
	      test_bit(wil_vअगर_fwconnected, vअगर->status))) अणु
		wil_err(wil, "Disconnect was called while disconnected\n");
		वापस 0;
	पूर्ण

	vअगर->locally_generated_disc = true;
	rc = wmi_call(wil, WMI_DISCONNECT_CMDID, vअगर->mid, शून्य, 0,
		      WMI_DISCONNECT_EVENTID, शून्य, 0,
		      WIL6210_DISCONNECT_TO_MS);
	अगर (rc)
		wil_err(wil, "disconnect error %d\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_set_wiphy_params(काष्ठा wiphy *wiphy, u32 changed)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	पूर्णांक rc;

	/* these parameters are explicitly not supported */
	अगर (changed & (WIPHY_PARAM_RETRY_LONG |
		       WIPHY_PARAM_FRAG_THRESHOLD |
		       WIPHY_PARAM_RTS_THRESHOLD))
		वापस -ENOTSUPP;

	अगर (changed & WIPHY_PARAM_RETRY_SHORT) अणु
		rc = wmi_set_mgmt_retry(wil, wiphy->retry_लघु);
		अगर (rc)
			वापस rc;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wil_cfg80211_mgmt_tx(काष्ठा wiphy *wiphy, काष्ठा wireless_dev *wdev,
			 काष्ठा cfg80211_mgmt_tx_params *params,
			 u64 *cookie)
अणु
	स्थिर u8 *buf = params->buf;
	माप_प्रकार len = params->len;
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);
	पूर्णांक rc;
	bool tx_status;

	wil_dbg_misc(wil, "mgmt_tx: channel %d offchan %d, wait %d\n",
		     params->chan ? params->chan->hw_value : -1,
		     params->offchan,
		     params->रुको);

	/* Note, currently we support the "wait" parameter only on AP mode.
	 * In other modes, user-space must call reमुख्य_on_channel beक्रमe
	 * mgmt_tx or listen on a channel other than active one.
	 */

	अगर (params->chan && params->chan->hw_value == 0) अणु
		wil_err(wil, "invalid channel\n");
		वापस -EINVAL;
	पूर्ण

	अगर (wdev->अगरtype != NL80211_IFTYPE_AP) अणु
		wil_dbg_misc(wil,
			     "send WMI_SW_TX_REQ_CMDID on non-AP interfaces\n");
		rc = wmi_mgmt_tx(vअगर, buf, len);
		जाओ out;
	पूर्ण

	अगर (!params->chan || params->chan->hw_value == vअगर->channel) अणु
		wil_dbg_misc(wil,
			     "send WMI_SW_TX_REQ_CMDID for on-channel\n");
		rc = wmi_mgmt_tx(vअगर, buf, len);
		जाओ out;
	पूर्ण

	अगर (params->offchan == 0) अणु
		wil_err(wil,
			"invalid channel params: current %d requested %d, off-channel not allowed\n",
			vअगर->channel, params->chan->hw_value);
		वापस -EBUSY;
	पूर्ण

	/* use the wmi_mgmt_tx_ext only on AP mode and off-channel */
	rc = wmi_mgmt_tx_ext(vअगर, buf, len, params->chan->hw_value,
			     params->रुको);

out:
	/* when the sent packet was not acked by receiver(ACK=0), rc will
	 * be -EAGAIN. In this हाल this function needs to वापस success,
	 * the ACK=0 will be reflected in tx_status.
	 */
	tx_status = (rc == 0);
	rc = (rc == -EAGAIN) ? 0 : rc;
	cfg80211_mgmt_tx_status(wdev, cookie ? *cookie : 0, buf, len,
				tx_status, GFP_KERNEL);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_set_channel(काष्ठा wiphy *wiphy,
				    काष्ठा cfg80211_chan_def *chandef)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil->monitor_chandef = *chandef;

	वापस 0;
पूर्ण

अटल क्रमागत wmi_key_usage wil_detect_key_usage(काष्ठा wireless_dev *wdev,
					       bool pairwise)
अणु
	काष्ठा wil6210_priv *wil = wdev_to_wil(wdev);
	क्रमागत wmi_key_usage rc;

	अगर (pairwise) अणु
		rc = WMI_KEY_USE_PAIRWISE;
	पूर्ण अन्यथा अणु
		चयन (wdev->अगरtype) अणु
		हाल NL80211_IFTYPE_STATION:
		हाल NL80211_IFTYPE_P2P_CLIENT:
			rc = WMI_KEY_USE_RX_GROUP;
			अवरोध;
		हाल NL80211_IFTYPE_AP:
		हाल NL80211_IFTYPE_P2P_GO:
			rc = WMI_KEY_USE_TX_GROUP;
			अवरोध;
		शेष:
			/* TODO: Rx GTK or Tx GTK? */
			wil_err(wil, "Can't determine GTK type\n");
			rc = WMI_KEY_USE_RX_GROUP;
			अवरोध;
		पूर्ण
	पूर्ण
	wil_dbg_misc(wil, "detect_key_usage: -> %s\n", key_usage_str[rc]);

	वापस rc;
पूर्ण

अटल काष्ठा wil_sta_info *
wil_find_sta_by_key_usage(काष्ठा wil6210_priv *wil, u8 mid,
			  क्रमागत wmi_key_usage key_usage, स्थिर u8 *mac_addr)
अणु
	पूर्णांक cid = -EINVAL;

	अगर (key_usage == WMI_KEY_USE_TX_GROUP)
		वापस शून्य; /* not needed */

	/* supplicant provides Rx group key in STA mode with शून्य MAC address */
	अगर (mac_addr)
		cid = wil_find_cid(wil, mid, mac_addr);
	अन्यथा अगर (key_usage == WMI_KEY_USE_RX_GROUP)
		cid = wil_find_cid_by_idx(wil, mid, 0);
	अगर (cid < 0) अणु
		wil_err(wil, "No CID for %pM %s\n", mac_addr,
			key_usage_str[key_usage]);
		वापस ERR_PTR(cid);
	पूर्ण

	वापस &wil->sta[cid];
पूर्ण

व्योम wil_set_crypto_rx(u8 key_index, क्रमागत wmi_key_usage key_usage,
		       काष्ठा wil_sta_info *cs,
		       काष्ठा key_params *params)
अणु
	काष्ठा wil_tid_crypto_rx_single *cc;
	पूर्णांक tid;

	अगर (!cs)
		वापस;

	चयन (key_usage) अणु
	हाल WMI_KEY_USE_STORE_PTK:
	हाल WMI_KEY_USE_PAIRWISE:
		क्रम (tid = 0; tid < WIL_STA_TID_NUM; tid++) अणु
			cc = &cs->tid_crypto_rx[tid].key_id[key_index];
			अगर (params->seq)
				स_नकल(cc->pn, params->seq,
				       IEEE80211_GCMP_PN_LEN);
			अन्यथा
				स_रखो(cc->pn, 0, IEEE80211_GCMP_PN_LEN);
			cc->key_set = true;
		पूर्ण
		अवरोध;
	हाल WMI_KEY_USE_RX_GROUP:
		cc = &cs->group_crypto_rx.key_id[key_index];
		अगर (params->seq)
			स_नकल(cc->pn, params->seq, IEEE80211_GCMP_PN_LEN);
		अन्यथा
			स_रखो(cc->pn, 0, IEEE80211_GCMP_PN_LEN);
		cc->key_set = true;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल व्योम wil_del_rx_key(u8 key_index, क्रमागत wmi_key_usage key_usage,
			   काष्ठा wil_sta_info *cs)
अणु
	काष्ठा wil_tid_crypto_rx_single *cc;
	पूर्णांक tid;

	अगर (!cs)
		वापस;

	चयन (key_usage) अणु
	हाल WMI_KEY_USE_PAIRWISE:
		क्रम (tid = 0; tid < WIL_STA_TID_NUM; tid++) अणु
			cc = &cs->tid_crypto_rx[tid].key_id[key_index];
			cc->key_set = false;
		पूर्ण
		अवरोध;
	हाल WMI_KEY_USE_RX_GROUP:
		cc = &cs->group_crypto_rx.key_id[key_index];
		cc->key_set = false;
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
पूर्ण

अटल पूर्णांक wil_cfg80211_add_key(काष्ठा wiphy *wiphy,
				काष्ठा net_device *ndev,
				u8 key_index, bool pairwise,
				स्थिर u8 *mac_addr,
				काष्ठा key_params *params)
अणु
	पूर्णांक rc;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	क्रमागत wmi_key_usage key_usage = wil_detect_key_usage(wdev, pairwise);
	काष्ठा wil_sta_info *cs = wil_find_sta_by_key_usage(wil, vअगर->mid,
							    key_usage,
							    mac_addr);

	अगर (!params) अणु
		wil_err(wil, "NULL params\n");
		वापस -EINVAL;
	पूर्ण

	wil_dbg_misc(wil, "add_key: %pM %s[%d] PN %*phN\n",
		     mac_addr, key_usage_str[key_usage], key_index,
		     params->seq_len, params->seq);

	अगर (IS_ERR(cs)) अणु
		/* in FT, sta info may not be available as add_key may be
		 * sent by host beक्रमe FW sends WMI_CONNECT_EVENT
		 */
		अगर (!test_bit(wil_vअगर_ft_roam, vअगर->status)) अणु
			wil_err(wil, "Not connected, %pM %s[%d] PN %*phN\n",
				mac_addr, key_usage_str[key_usage], key_index,
				params->seq_len, params->seq);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (!IS_ERR(cs))
		wil_del_rx_key(key_index, key_usage, cs);

	अगर (params->seq && params->seq_len != IEEE80211_GCMP_PN_LEN) अणु
		wil_err(wil,
			"Wrong PN len %d, %pM %s[%d] PN %*phN\n",
			params->seq_len, mac_addr,
			key_usage_str[key_usage], key_index,
			params->seq_len, params->seq);
		वापस -EINVAL;
	पूर्ण

	spin_lock_bh(&wil->eap_lock);
	अगर (pairwise && wdev->अगरtype == NL80211_IFTYPE_STATION &&
	    (vअगर->ptk_rekey_state == WIL_REKEY_M3_RECEIVED ||
	     vअगर->ptk_rekey_state == WIL_REKEY_WAIT_M4_SENT)) अणु
		key_usage = WMI_KEY_USE_STORE_PTK;
		vअगर->ptk_rekey_state = WIL_REKEY_WAIT_M4_SENT;
		wil_dbg_misc(wil, "Store EAPOL key\n");
	पूर्ण
	spin_unlock_bh(&wil->eap_lock);

	rc = wmi_add_cipher_key(vअगर, key_index, mac_addr, params->key_len,
				params->key, key_usage);
	अगर (!rc && !IS_ERR(cs)) अणु
		/* update local storage used क्रम AP recovery */
		अगर (key_usage == WMI_KEY_USE_TX_GROUP && params->key &&
		    params->key_len <= WMI_MAX_KEY_LEN) अणु
			vअगर->gtk_index = key_index;
			स_नकल(vअगर->gtk, params->key, params->key_len);
			vअगर->gtk_len = params->key_len;
		पूर्ण
		/* in FT set crypto will take place upon receiving
		 * WMI_RING_EN_EVENTID event
		 */
		wil_set_crypto_rx(key_index, key_usage, cs, params);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_del_key(काष्ठा wiphy *wiphy,
				काष्ठा net_device *ndev,
				u8 key_index, bool pairwise,
				स्थिर u8 *mac_addr)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wireless_dev *wdev = vअगर_to_wdev(vअगर);
	क्रमागत wmi_key_usage key_usage = wil_detect_key_usage(wdev, pairwise);
	काष्ठा wil_sta_info *cs = wil_find_sta_by_key_usage(wil, vअगर->mid,
							    key_usage,
							    mac_addr);

	wil_dbg_misc(wil, "del_key: %pM %s[%d]\n", mac_addr,
		     key_usage_str[key_usage], key_index);

	अगर (IS_ERR(cs))
		wil_info(wil, "Not connected, %pM %s[%d]\n",
			 mac_addr, key_usage_str[key_usage], key_index);

	अगर (!IS_ERR_OR_शून्य(cs))
		wil_del_rx_key(key_index, key_usage, cs);

	वापस wmi_del_cipher_key(vअगर, key_index, mac_addr, key_usage);
पूर्ण

/* Need to be present or wiphy_new() will WARN */
अटल पूर्णांक wil_cfg80211_set_शेष_key(काष्ठा wiphy *wiphy,
					काष्ठा net_device *ndev,
					u8 key_index, bool unicast,
					bool multicast)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil_dbg_misc(wil, "set_default_key: entered\n");
	वापस 0;
पूर्ण

अटल पूर्णांक wil_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
				 काष्ठा wireless_dev *wdev,
				 काष्ठा ieee80211_channel *chan,
				 अचिन्हित पूर्णांक duration,
				 u64 *cookie)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	पूर्णांक rc;

	wil_dbg_misc(wil,
		     "remain_on_channel: center_freq=%d, duration=%d iftype=%d\n",
		     chan->center_freq, duration, wdev->अगरtype);

	rc = wil_p2p_listen(wil, wdev, duration, chan, cookie);
	वापस rc;
पूर्ण

अटल पूर्णांक wil_cancel_reमुख्य_on_channel(काष्ठा wiphy *wiphy,
					काष्ठा wireless_dev *wdev,
					u64 cookie)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);

	wil_dbg_misc(wil, "cancel_remain_on_channel\n");

	वापस wil_p2p_cancel_listen(vअगर, cookie);
पूर्ण

/*
 * find a specअगरic IE in a list of IEs
 * वापस a poपूर्णांकer to the beginning of IE in the list
 * or शून्य अगर not found
 */
अटल स्थिर u8 *_wil_cfg80211_find_ie(स्थिर u8 *ies, u16 ies_len, स्थिर u8 *ie,
				       u16 ie_len)
अणु
	काष्ठा ieee80211_venकरोr_ie *vie;
	u32 oui;

	/* IE tag at offset 0, length at offset 1 */
	अगर (ie_len < 2 || 2 + ie[1] > ie_len)
		वापस शून्य;

	अगर (ie[0] != WLAN_EID_VENDOR_SPECIFIC)
		वापस cfg80211_find_ie(ie[0], ies, ies_len);

	/* make sure there is room क्रम 3 bytes OUI + 1 byte OUI type */
	अगर (ie[1] < 4)
		वापस शून्य;
	vie = (काष्ठा ieee80211_venकरोr_ie *)ie;
	oui = vie->oui[0] << 16 | vie->oui[1] << 8 | vie->oui[2];
	वापस cfg80211_find_venकरोr_ie(oui, vie->oui_type, ies,
				       ies_len);
पूर्ण

/*
 * merge the IEs in two lists पूर्णांकo a single list.
 * करो not include IEs from the second list which exist in the first list.
 * add only venकरोr specअगरic IEs from second list to keep
 * the merged list sorted (since venकरोr-specअगरic IE has the
 * highest tag number)
 * caller must मुक्त the allocated memory क्रम merged IEs
 */
अटल पूर्णांक _wil_cfg80211_merge_extra_ies(स्थिर u8 *ies1, u16 ies1_len,
					 स्थिर u8 *ies2, u16 ies2_len,
					 u8 **merged_ies, u16 *merged_len)
अणु
	u8 *buf, *dpos;
	स्थिर u8 *spos;

	अगर (!ies1)
		ies1_len = 0;

	अगर (!ies2)
		ies2_len = 0;

	अगर (ies1_len == 0 && ies2_len == 0) अणु
		*merged_ies = शून्य;
		*merged_len = 0;
		वापस 0;
	पूर्ण

	buf = kदो_स्मृति(ies1_len + ies2_len, GFP_KERNEL);
	अगर (!buf)
		वापस -ENOMEM;
	अगर (ies1)
		स_नकल(buf, ies1, ies1_len);
	dpos = buf + ies1_len;
	spos = ies2;
	जबतक (spos && (spos + 1 < ies2 + ies2_len)) अणु
		/* IE tag at offset 0, length at offset 1 */
		u16 ielen = 2 + spos[1];

		अगर (spos + ielen > ies2 + ies2_len)
			अवरोध;
		अगर (spos[0] == WLAN_EID_VENDOR_SPECIFIC &&
		    (!ies1 || !_wil_cfg80211_find_ie(ies1, ies1_len,
						     spos, ielen))) अणु
			स_नकल(dpos, spos, ielen);
			dpos += ielen;
		पूर्ण
		spos += ielen;
	पूर्ण

	*merged_ies = buf;
	*merged_len = dpos - buf;
	वापस 0;
पूर्ण

अटल व्योम wil_prपूर्णांक_bcon_data(काष्ठा cfg80211_beacon_data *b)
अणु
	wil_hex_dump_misc("head     ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->head, b->head_len, true);
	wil_hex_dump_misc("tail     ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->tail, b->tail_len, true);
	wil_hex_dump_misc("BCON IE  ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->beacon_ies, b->beacon_ies_len, true);
	wil_hex_dump_misc("PROBE    ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->probe_resp, b->probe_resp_len, true);
	wil_hex_dump_misc("PROBE IE ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->proberesp_ies, b->proberesp_ies_len, true);
	wil_hex_dump_misc("ASSOC IE ", DUMP_PREFIX_OFFSET, 16, 1,
			  b->assocresp_ies, b->assocresp_ies_len, true);
पूर्ण

/* पूर्णांकernal functions क्रम device reset and starting AP */
अटल u8 *
_wil_cfg80211_get_proberesp_ies(स्थिर u8 *proberesp, u16 proberesp_len,
				u16 *ies_len)
अणु
	u8 *ies = शून्य;

	अगर (proberesp) अणु
		काष्ठा ieee80211_mgmt *f =
			(काष्ठा ieee80211_mgmt *)proberesp;
		माप_प्रकार hlen = दुरत्व(काष्ठा ieee80211_mgmt,
				       u.probe_resp.variable);

		ies = f->u.probe_resp.variable;
		अगर (ies_len)
			*ies_len = proberesp_len - hlen;
	पूर्ण

	वापस ies;
पूर्ण

अटल पूर्णांक _wil_cfg80211_set_ies(काष्ठा wil6210_vअगर *vअगर,
				 काष्ठा cfg80211_beacon_data *bcon)
अणु
	पूर्णांक rc;
	u16 len = 0, proberesp_len = 0;
	u8 *ies = शून्य, *proberesp;

	/* update local storage used क्रम AP recovery */
	wil_memdup_ie(&vअगर->proberesp, &vअगर->proberesp_len, bcon->probe_resp,
		      bcon->probe_resp_len);
	wil_memdup_ie(&vअगर->proberesp_ies, &vअगर->proberesp_ies_len,
		      bcon->proberesp_ies, bcon->proberesp_ies_len);
	wil_memdup_ie(&vअगर->assocresp_ies, &vअगर->assocresp_ies_len,
		      bcon->assocresp_ies, bcon->assocresp_ies_len);

	proberesp = _wil_cfg80211_get_proberesp_ies(bcon->probe_resp,
						    bcon->probe_resp_len,
						    &proberesp_len);
	rc = _wil_cfg80211_merge_extra_ies(proberesp,
					   proberesp_len,
					   bcon->proberesp_ies,
					   bcon->proberesp_ies_len,
					   &ies, &len);

	अगर (rc)
		जाओ out;

	rc = wmi_set_ie(vअगर, WMI_FRAME_PROBE_RESP, len, ies);
	अगर (rc)
		जाओ out;

	अगर (bcon->assocresp_ies)
		rc = wmi_set_ie(vअगर, WMI_FRAME_ASSOC_RESP,
				bcon->assocresp_ies_len, bcon->assocresp_ies);
	अन्यथा
		rc = wmi_set_ie(vअगर, WMI_FRAME_ASSOC_RESP, len, ies);
#अगर 0 /* to use beacon IE's, हटाओ this #अगर 0 */
	अगर (rc)
		जाओ out;

	rc = wmi_set_ie(vअगर, WMI_FRAME_BEACON,
			bcon->tail_len, bcon->tail);
#पूर्ण_अगर
out:
	kमुक्त(ies);
	वापस rc;
पूर्ण

अटल पूर्णांक _wil_cfg80211_start_ap(काष्ठा wiphy *wiphy,
				  काष्ठा net_device *ndev,
				  स्थिर u8 *ssid, माप_प्रकार ssid_len, u32 privacy,
				  पूर्णांक bi, u8 chan, u8 wmi_edmg_channel,
				  काष्ठा cfg80211_beacon_data *bcon,
				  u8 hidden_ssid, u32 pbss)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	पूर्णांक rc;
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	u8 wmi_nettype = wil_अगरtype_nl2wmi(wdev->अगरtype);
	u8 is_go = (wdev->अगरtype == NL80211_IFTYPE_P2P_GO);
	u16 proberesp_len = 0;
	u8 *proberesp;
	bool ft = false;

	अगर (pbss)
		wmi_nettype = WMI_NETTYPE_P2P;

	wil_dbg_misc(wil, "start_ap: mid=%d, is_go=%d\n", vअगर->mid, is_go);
	अगर (is_go && !pbss) अणु
		wil_err(wil, "P2P GO must be in PBSS\n");
		वापस -ENOTSUPP;
	पूर्ण

	wil_set_recovery_state(wil, fw_recovery_idle);

	proberesp = _wil_cfg80211_get_proberesp_ies(bcon->probe_resp,
						    bcon->probe_resp_len,
						    &proberesp_len);
	/* check that the probe response IEs has a MDE */
	अगर ((proberesp && proberesp_len > 0 &&
	     cfg80211_find_ie(WLAN_EID_MOBILITY_DOMAIN,
			      proberesp,
			      proberesp_len)))
		ft = true;

	अगर (ft) अणु
		अगर (!test_bit(WMI_FW_CAPABILITY_FT_ROAMING,
			      wil->fw_capabilities)) अणु
			wil_err(wil, "FW does not support FT roaming\n");
			वापस -ENOTSUPP;
		पूर्ण
		set_bit(wil_vअगर_ft_roam, vअगर->status);
	पूर्ण

	mutex_lock(&wil->mutex);

	अगर (!wil_has_other_active_अगरaces(wil, ndev, true, false)) अणु
		__wil_करोwn(wil);
		rc = __wil_up(wil);
		अगर (rc)
			जाओ out;
	पूर्ण

	rc = wmi_set_ssid(vअगर, ssid_len, ssid);
	अगर (rc)
		जाओ out;

	rc = _wil_cfg80211_set_ies(vअगर, bcon);
	अगर (rc)
		जाओ out;

	vअगर->privacy = privacy;
	vअगर->channel = chan;
	vअगर->wmi_edmg_channel = wmi_edmg_channel;
	vअगर->hidden_ssid = hidden_ssid;
	vअगर->pbss = pbss;
	vअगर->bi = bi;
	स_नकल(vअगर->ssid, ssid, ssid_len);
	vअगर->ssid_len = ssid_len;

	netअगर_carrier_on(ndev);
	अगर (!wil_has_other_active_अगरaces(wil, ndev, false, true))
		wil6210_bus_request(wil, WIL_MAX_BUS_REQUEST_KBPS);

	rc = wmi_pcp_start(vअगर, bi, wmi_nettype, chan, wmi_edmg_channel,
			   hidden_ssid, is_go);
	अगर (rc)
		जाओ err_pcp_start;

	rc = wil_bcast_init(vअगर);
	अगर (rc)
		जाओ err_bcast;

	जाओ out; /* success */

err_bcast:
	wmi_pcp_stop(vअगर);
err_pcp_start:
	netअगर_carrier_off(ndev);
	अगर (!wil_has_other_active_अगरaces(wil, ndev, false, true))
		wil6210_bus_request(wil, WIL_DEFAULT_BUS_REQUEST_KBPS);
out:
	mutex_unlock(&wil->mutex);
	वापस rc;
पूर्ण

व्योम wil_cfg80211_ap_recovery(काष्ठा wil6210_priv *wil)
अणु
	पूर्णांक rc, i;
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);

	क्रम (i = 0; i < GET_MAX_VIFS(wil); i++) अणु
		काष्ठा wil6210_vअगर *vअगर = wil->vअगरs[i];
		काष्ठा net_device *ndev;
		काष्ठा cfg80211_beacon_data bcon = अणुपूर्ण;
		काष्ठा key_params key_params = अणुपूर्ण;

		अगर (!vअगर || vअगर->ssid_len == 0)
			जारी;

		ndev = vअगर_to_ndev(vअगर);
		bcon.proberesp_ies = vअगर->proberesp_ies;
		bcon.assocresp_ies = vअगर->assocresp_ies;
		bcon.probe_resp = vअगर->proberesp;
		bcon.proberesp_ies_len = vअगर->proberesp_ies_len;
		bcon.assocresp_ies_len = vअगर->assocresp_ies_len;
		bcon.probe_resp_len = vअगर->proberesp_len;

		wil_info(wil,
			 "AP (vif %d) recovery: privacy %d, bi %d, channel %d, hidden %d, pbss %d\n",
			 i, vअगर->privacy, vअगर->bi, vअगर->channel,
			 vअगर->hidden_ssid, vअगर->pbss);
		wil_hex_dump_misc("SSID ", DUMP_PREFIX_OFFSET, 16, 1,
				  vअगर->ssid, vअगर->ssid_len, true);
		rc = _wil_cfg80211_start_ap(wiphy, ndev,
					    vअगर->ssid, vअगर->ssid_len,
					    vअगर->privacy, vअगर->bi,
					    vअगर->channel,
					    vअगर->wmi_edmg_channel, &bcon,
					    vअगर->hidden_ssid, vअगर->pbss);
		अगर (rc) अणु
			wil_err(wil, "vif %d recovery failed (%d)\n", i, rc);
			जारी;
		पूर्ण

		अगर (!vअगर->privacy || vअगर->gtk_len == 0)
			जारी;

		key_params.key = vअगर->gtk;
		key_params.key_len = vअगर->gtk_len;
		key_params.seq_len = IEEE80211_GCMP_PN_LEN;
		rc = wil_cfg80211_add_key(wiphy, ndev, vअगर->gtk_index, false,
					  शून्य, &key_params);
		अगर (rc)
			wil_err(wil, "vif %d recovery add key failed (%d)\n",
				i, rc);
	पूर्ण
पूर्ण

अटल पूर्णांक wil_cfg80211_change_beacon(काष्ठा wiphy *wiphy,
				      काष्ठा net_device *ndev,
				      काष्ठा cfg80211_beacon_data *bcon)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wireless_dev *wdev = ndev->ieee80211_ptr;
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	पूर्णांक rc;
	u32 privacy = 0;

	wil_dbg_misc(wil, "change_beacon, mid=%d\n", vअगर->mid);
	wil_prपूर्णांक_bcon_data(bcon);

	अगर (bcon->tail &&
	    cfg80211_find_ie(WLAN_EID_RSN, bcon->tail,
			     bcon->tail_len))
		privacy = 1;

	स_नकल(vअगर->ssid, wdev->ssid, wdev->ssid_len);
	vअगर->ssid_len = wdev->ssid_len;

	/* in हाल privacy has changed, need to restart the AP */
	अगर (vअगर->privacy != privacy) अणु
		wil_dbg_misc(wil, "privacy changed %d=>%d. Restarting AP\n",
			     vअगर->privacy, privacy);

		rc = _wil_cfg80211_start_ap(wiphy, ndev, vअगर->ssid,
					    vअगर->ssid_len, privacy,
					    wdev->beacon_पूर्णांकerval,
					    vअगर->channel,
					    vअगर->wmi_edmg_channel, bcon,
					    vअगर->hidden_ssid,
					    vअगर->pbss);
	पूर्ण अन्यथा अणु
		rc = _wil_cfg80211_set_ies(vअगर, bcon);
	पूर्ण

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_start_ap(काष्ठा wiphy *wiphy,
				 काष्ठा net_device *ndev,
				 काष्ठा cfg80211_ap_settings *info)
अणु
	पूर्णांक rc;
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा ieee80211_channel *channel = info->chandef.chan;
	काष्ठा cfg80211_beacon_data *bcon = &info->beacon;
	काष्ठा cfg80211_crypto_settings *crypto = &info->crypto;
	u8 wmi_edmg_channel;
	u8 hidden_ssid;

	wil_dbg_misc(wil, "start_ap\n");

	rc = wil_get_wmi_edmg_channel(wil, info->chandef.edmg.bw_config,
				      info->chandef.edmg.channels,
				      &wmi_edmg_channel);
	अगर (rc < 0)
		वापस rc;

	अगर (!channel) अणु
		wil_err(wil, "AP: No channel???\n");
		वापस -EINVAL;
	पूर्ण

	चयन (info->hidden_ssid) अणु
	हाल NL80211_HIDDEN_SSID_NOT_IN_USE:
		hidden_ssid = WMI_HIDDEN_SSID_DISABLED;
		अवरोध;

	हाल NL80211_HIDDEN_SSID_ZERO_LEN:
		hidden_ssid = WMI_HIDDEN_SSID_SEND_EMPTY;
		अवरोध;

	हाल NL80211_HIDDEN_SSID_ZERO_CONTENTS:
		hidden_ssid = WMI_HIDDEN_SSID_CLEAR;
		अवरोध;

	शेष:
		wil_err(wil, "AP: Invalid hidden SSID %d\n", info->hidden_ssid);
		वापस -EOPNOTSUPP;
	पूर्ण
	wil_dbg_misc(wil, "AP on Channel %d %d MHz, %s\n", channel->hw_value,
		     channel->center_freq, info->privacy ? "secure" : "open");
	wil_dbg_misc(wil, "Privacy: %d auth_type %d\n",
		     info->privacy, info->auth_type);
	wil_dbg_misc(wil, "Hidden SSID mode: %d\n",
		     info->hidden_ssid);
	wil_dbg_misc(wil, "BI %d DTIM %d\n", info->beacon_पूर्णांकerval,
		     info->dtim_period);
	wil_dbg_misc(wil, "PBSS %d\n", info->pbss);
	wil_hex_dump_misc("SSID ", DUMP_PREFIX_OFFSET, 16, 1,
			  info->ssid, info->ssid_len, true);
	wil_prपूर्णांक_bcon_data(bcon);
	wil_prपूर्णांक_crypto(wil, crypto);

	rc = _wil_cfg80211_start_ap(wiphy, ndev,
				    info->ssid, info->ssid_len, info->privacy,
				    info->beacon_पूर्णांकerval, channel->hw_value,
				    wmi_edmg_channel, bcon, hidden_ssid,
				    info->pbss);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_stop_ap(काष्ठा wiphy *wiphy,
				काष्ठा net_device *ndev)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(ndev);
	bool last;

	wil_dbg_misc(wil, "stop_ap, mid=%d\n", vअगर->mid);

	netअगर_carrier_off(ndev);
	last = !wil_has_other_active_अगरaces(wil, ndev, false, true);
	अगर (last) अणु
		wil6210_bus_request(wil, WIL_DEFAULT_BUS_REQUEST_KBPS);
		wil_set_recovery_state(wil, fw_recovery_idle);
		set_bit(wil_status_resetting, wil->status);
	पूर्ण

	mutex_lock(&wil->mutex);

	wmi_pcp_stop(vअगर);
	clear_bit(wil_vअगर_ft_roam, vअगर->status);
	vअगर->ssid_len = 0;
	wil_memdup_ie(&vअगर->proberesp, &vअगर->proberesp_len, शून्य, 0);
	wil_memdup_ie(&vअगर->proberesp_ies, &vअगर->proberesp_ies_len, शून्य, 0);
	wil_memdup_ie(&vअगर->assocresp_ies, &vअगर->assocresp_ies_len, शून्य, 0);
	स_रखो(vअगर->gtk, 0, WMI_MAX_KEY_LEN);
	vअगर->gtk_len = 0;

	अगर (last)
		__wil_करोwn(wil);
	अन्यथा
		wil_bcast_fini(vअगर);

	mutex_unlock(&wil->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक wil_cfg80211_add_station(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *dev,
				    स्थिर u8 *mac,
				    काष्ठा station_parameters *params)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil_dbg_misc(wil, "add station %pM aid %d mid %d mask 0x%x set 0x%x\n",
		     mac, params->aid, vअगर->mid,
		     params->sta_flags_mask, params->sta_flags_set);

	अगर (!disable_ap_sme) अणु
		wil_err(wil, "not supported with AP SME enabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (params->aid > WIL_MAX_DMG_AID) अणु
		wil_err(wil, "invalid aid\n");
		वापस -EINVAL;
	पूर्ण

	वापस wmi_new_sta(vअगर, mac, params->aid);
पूर्ण

अटल पूर्णांक wil_cfg80211_del_station(काष्ठा wiphy *wiphy,
				    काष्ठा net_device *dev,
				    काष्ठा station_del_parameters *params)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil_dbg_misc(wil, "del_station: %pM, reason=%d mid=%d\n",
		     params->mac, params->reason_code, vअगर->mid);

	mutex_lock(&wil->mutex);
	wil6210_disconnect(vअगर, params->mac, params->reason_code);
	mutex_unlock(&wil->mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक wil_cfg80211_change_station(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *dev,
				       स्थिर u8 *mac,
				       काष्ठा station_parameters *params)
अणु
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	पूर्णांक authorize;
	पूर्णांक cid, i;
	काष्ठा wil_ring_tx_data *txdata = शून्य;

	wil_dbg_misc(wil, "change station %pM mask 0x%x set 0x%x mid %d\n",
		     mac, params->sta_flags_mask, params->sta_flags_set,
		     vअगर->mid);

	अगर (!disable_ap_sme) अणु
		wil_dbg_misc(wil, "not supported with AP SME enabled\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!(params->sta_flags_mask & BIT(NL80211_STA_FLAG_AUTHORIZED)))
		वापस 0;

	cid = wil_find_cid(wil, vअगर->mid, mac);
	अगर (cid < 0) अणु
		wil_err(wil, "station not found\n");
		वापस -ENOLINK;
	पूर्ण

	क्रम (i = 0; i < ARRAY_SIZE(wil->ring2cid_tid); i++)
		अगर (wil->ring2cid_tid[i][0] == cid) अणु
			txdata = &wil->ring_tx_data[i];
			अवरोध;
		पूर्ण

	अगर (!txdata) अणु
		wil_err(wil, "ring data not found\n");
		वापस -ENOLINK;
	पूर्ण

	authorize = params->sta_flags_set & BIT(NL80211_STA_FLAG_AUTHORIZED);
	txdata->करोt1x_खोलो = authorize ? 1 : 0;
	wil_dbg_misc(wil, "cid %d ring %d authorize %d\n", cid, i,
		     txdata->करोt1x_खोलो);

	वापस 0;
पूर्ण

/* probe_client handling */
अटल व्योम wil_probe_client_handle(काष्ठा wil6210_priv *wil,
				    काष्ठा wil6210_vअगर *vअगर,
				    काष्ठा wil_probe_client_req *req)
अणु
	काष्ठा net_device *ndev = vअगर_to_ndev(vअगर);
	काष्ठा wil_sta_info *sta = &wil->sta[req->cid];
	/* assume STA is alive अगर it is still connected,
	 * अन्यथा FW will disconnect it
	 */
	bool alive = (sta->status == wil_sta_connected);

	cfg80211_probe_status(ndev, sta->addr, req->cookie, alive,
			      0, false, GFP_KERNEL);
पूर्ण

अटल काष्ठा list_head *next_probe_client(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा list_head *ret = शून्य;

	mutex_lock(&vअगर->probe_client_mutex);

	अगर (!list_empty(&vअगर->probe_client_pending)) अणु
		ret = vअगर->probe_client_pending.next;
		list_del(ret);
	पूर्ण

	mutex_unlock(&vअगर->probe_client_mutex);

	वापस ret;
पूर्ण

व्योम wil_probe_client_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wil6210_vअगर *vअगर = container_of(work, काष्ठा wil6210_vअगर,
					       probe_client_worker);
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);
	काष्ठा wil_probe_client_req *req;
	काष्ठा list_head *lh;

	जबतक ((lh = next_probe_client(vअगर)) != शून्य) अणु
		req = list_entry(lh, काष्ठा wil_probe_client_req, list);

		wil_probe_client_handle(wil, vअगर, req);
		kमुक्त(req);
	पूर्ण
पूर्ण

व्योम wil_probe_client_flush(काष्ठा wil6210_vअगर *vअगर)
अणु
	काष्ठा wil_probe_client_req *req, *t;
	काष्ठा wil6210_priv *wil = vअगर_to_wil(vअगर);

	wil_dbg_misc(wil, "probe_client_flush\n");

	mutex_lock(&vअगर->probe_client_mutex);

	list_क्रम_each_entry_safe(req, t, &vअगर->probe_client_pending, list) अणु
		list_del(&req->list);
		kमुक्त(req);
	पूर्ण

	mutex_unlock(&vअगर->probe_client_mutex);
पूर्ण

अटल पूर्णांक wil_cfg80211_probe_client(काष्ठा wiphy *wiphy,
				     काष्ठा net_device *dev,
				     स्थिर u8 *peer, u64 *cookie)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);
	काष्ठा wil_probe_client_req *req;
	पूर्णांक cid = wil_find_cid(wil, vअगर->mid, peer);

	wil_dbg_misc(wil, "probe_client: %pM => CID %d MID %d\n",
		     peer, cid, vअगर->mid);

	अगर (cid < 0)
		वापस -ENOLINK;

	req = kzalloc(माप(*req), GFP_KERNEL);
	अगर (!req)
		वापस -ENOMEM;

	req->cid = cid;
	req->cookie = cid;

	mutex_lock(&vअगर->probe_client_mutex);
	list_add_tail(&req->list, &vअगर->probe_client_pending);
	mutex_unlock(&vअगर->probe_client_mutex);

	*cookie = req->cookie;
	queue_work(wil->wq_service, &vअगर->probe_client_worker);
	वापस 0;
पूर्ण

अटल पूर्णांक wil_cfg80211_change_bss(काष्ठा wiphy *wiphy,
				   काष्ठा net_device *dev,
				   काष्ठा bss_parameters *params)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);

	अगर (params->ap_isolate >= 0) अणु
		wil_dbg_misc(wil, "change_bss: ap_isolate MID %d, %d => %d\n",
			     vअगर->mid, vअगर->ap_isolate, params->ap_isolate);
		vअगर->ap_isolate = params->ap_isolate;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wil_cfg80211_set_घातer_mgmt(काष्ठा wiphy *wiphy,
				       काष्ठा net_device *dev,
				       bool enabled, पूर्णांक समयout)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	क्रमागत wmi_ps_profile_type ps_profile;

	wil_dbg_misc(wil, "enabled=%d, timeout=%d\n",
		     enabled, समयout);

	अगर (enabled)
		ps_profile = WMI_PS_PROखाता_TYPE_DEFAULT;
	अन्यथा
		ps_profile = WMI_PS_PROखाता_TYPE_PS_DISABLED;

	वापस wil_ps_update(wil, ps_profile);
पूर्ण

अटल पूर्णांक wil_cfg80211_suspend(काष्ठा wiphy *wiphy,
				काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	पूर्णांक rc;

	/* Setting the wakeup trigger based on wow is TBD */

	अगर (test_bit(wil_status_suspended, wil->status)) अणु
		wil_dbg_pm(wil, "trying to suspend while suspended\n");
		वापस 0;
	पूर्ण

	rc = wil_can_suspend(wil, false);
	अगर (rc)
		जाओ out;

	wil_dbg_pm(wil, "suspending\n");

	mutex_lock(&wil->mutex);
	mutex_lock(&wil->vअगर_mutex);
	wil_p2p_stop_radio_operations(wil);
	wil_पात_scan_all_vअगरs(wil, true);
	mutex_unlock(&wil->vअगर_mutex);
	mutex_unlock(&wil->mutex);

out:
	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_resume(काष्ठा wiphy *wiphy)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);

	wil_dbg_pm(wil, "resuming\n");

	वापस 0;
पूर्ण

अटल पूर्णांक
wil_cfg80211_sched_scan_start(काष्ठा wiphy *wiphy,
			      काष्ठा net_device *dev,
			      काष्ठा cfg80211_sched_scan_request *request)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);
	पूर्णांक i, rc;

	अगर (vअगर->mid != 0)
		वापस -EOPNOTSUPP;

	wil_dbg_misc(wil,
		     "sched scan start: n_ssids %d, ie_len %zu, flags 0x%x\n",
		     request->n_ssids, request->ie_len, request->flags);
	क्रम (i = 0; i < request->n_ssids; i++) अणु
		wil_dbg_misc(wil, "SSID[%d]:", i);
		wil_hex_dump_misc("SSID ", DUMP_PREFIX_OFFSET, 16, 1,
				  request->ssids[i].ssid,
				  request->ssids[i].ssid_len, true);
	पूर्ण
	wil_dbg_misc(wil, "channels:");
	क्रम (i = 0; i < request->n_channels; i++)
		wil_dbg_misc(wil, " %d%s", request->channels[i]->hw_value,
			     i == request->n_channels - 1 ? "\n" : "");
	wil_dbg_misc(wil, "n_match_sets %d, min_rssi_thold %d, delay %d\n",
		     request->n_match_sets, request->min_rssi_thold,
		     request->delay);
	क्रम (i = 0; i < request->n_match_sets; i++) अणु
		काष्ठा cfg80211_match_set *ms = &request->match_sets[i];

		wil_dbg_misc(wil, "MATCHSET[%d]: rssi_thold %d\n",
			     i, ms->rssi_thold);
		wil_hex_dump_misc("SSID ", DUMP_PREFIX_OFFSET, 16, 1,
				  ms->ssid.ssid,
				  ms->ssid.ssid_len, true);
	पूर्ण
	wil_dbg_misc(wil, "n_scan_plans %d\n", request->n_scan_plans);
	क्रम (i = 0; i < request->n_scan_plans; i++) अणु
		काष्ठा cfg80211_sched_scan_plan *sp = &request->scan_plans[i];

		wil_dbg_misc(wil, "SCAN PLAN[%d]: interval %d iterations %d\n",
			     i, sp->पूर्णांकerval, sp->iterations);
	पूर्ण

	rc = wmi_set_ie(vअगर, WMI_FRAME_PROBE_REQ,
			request->ie_len, request->ie);
	अगर (rc)
		वापस rc;
	वापस wmi_start_sched_scan(wil, request);
पूर्ण

अटल पूर्णांक
wil_cfg80211_sched_scan_stop(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			     u64 reqid)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);
	पूर्णांक rc;

	अगर (vअगर->mid != 0)
		वापस -EOPNOTSUPP;

	rc = wmi_stop_sched_scan(wil);
	/* device would वापस error अगर it thinks PNO is alपढ़ोy stopped.
	 * ignore the वापस code so user space and driver माला_लो back in-sync
	 */
	wil_dbg_misc(wil, "sched scan stopped (%d)\n", rc);

	वापस 0;
पूर्ण

अटल पूर्णांक
wil_cfg80211_update_ft_ies(काष्ठा wiphy *wiphy, काष्ठा net_device *dev,
			   काष्ठा cfg80211_update_ft_ies_params *ftie)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	काष्ठा wil6210_vअगर *vअगर = ndev_to_vअगर(dev);
	काष्ठा cfg80211_bss *bss;
	काष्ठा wmi_ft_reassoc_cmd reassoc;
	पूर्णांक rc = 0;

	wil_dbg_misc(wil, "update ft ies, mid=%d\n", vअगर->mid);
	wil_hex_dump_misc("FT IE ", DUMP_PREFIX_OFFSET, 16, 1,
			  ftie->ie, ftie->ie_len, true);

	अगर (!test_bit(WMI_FW_CAPABILITY_FT_ROAMING, wil->fw_capabilities)) अणु
		wil_err(wil, "FW does not support FT roaming\n");
		वापस -EOPNOTSUPP;
	पूर्ण

	rc = wmi_update_ft_ies(vअगर, ftie->ie_len, ftie->ie);
	अगर (rc)
		वापस rc;

	अगर (!test_bit(wil_vअगर_ft_roam, vअगर->status))
		/* vअगर is not roaming */
		वापस 0;

	/* wil_vअगर_ft_roam is set. wil_cfg80211_update_ft_ies is used as
	 * a trigger क्रम reassoc
	 */

	bss = vअगर->bss;
	अगर (!bss) अणु
		wil_err(wil, "FT: bss is NULL\n");
		वापस -EINVAL;
	पूर्ण

	स_रखो(&reassoc, 0, माप(reassoc));
	ether_addr_copy(reassoc.bssid, bss->bssid);

	rc = wmi_send(wil, WMI_FT_REASSOC_CMDID, vअगर->mid,
		      &reassoc, माप(reassoc));
	अगर (rc)
		wil_err(wil, "FT: reassoc failed (%d)\n", rc);

	वापस rc;
पूर्ण

अटल पूर्णांक wil_cfg80211_set_multicast_to_unicast(काष्ठा wiphy *wiphy,
						 काष्ठा net_device *dev,
						 स्थिर bool enabled)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);

	अगर (wil->multicast_to_unicast == enabled)
		वापस 0;

	wil_info(wil, "set multicast to unicast, enabled=%d\n", enabled);
	wil->multicast_to_unicast = enabled;

	वापस 0;
पूर्ण

अटल पूर्णांक wil_cfg80211_set_cqm_rssi_config(काष्ठा wiphy *wiphy,
					    काष्ठा net_device *dev,
					    s32 rssi_thold, u32 rssi_hyst)
अणु
	काष्ठा wil6210_priv *wil = wiphy_to_wil(wiphy);
	पूर्णांक rc;

	wil->cqm_rssi_thold = rssi_thold;

	rc = wmi_set_cqm_rssi_config(wil, rssi_thold, rssi_hyst);
	अगर (rc)
		/* reset stored value upon failure */
		wil->cqm_rssi_thold = 0;

	वापस rc;
पूर्ण

अटल स्थिर काष्ठा cfg80211_ops wil_cfg80211_ops = अणु
	.add_भव_पूर्णांकf = wil_cfg80211_add_अगरace,
	.del_भव_पूर्णांकf = wil_cfg80211_del_अगरace,
	.scan = wil_cfg80211_scan,
	.पात_scan = wil_cfg80211_पात_scan,
	.connect = wil_cfg80211_connect,
	.disconnect = wil_cfg80211_disconnect,
	.set_wiphy_params = wil_cfg80211_set_wiphy_params,
	.change_भव_पूर्णांकf = wil_cfg80211_change_अगरace,
	.get_station = wil_cfg80211_get_station,
	.dump_station = wil_cfg80211_dump_station,
	.reमुख्य_on_channel = wil_reमुख्य_on_channel,
	.cancel_reमुख्य_on_channel = wil_cancel_reमुख्य_on_channel,
	.mgmt_tx = wil_cfg80211_mgmt_tx,
	.set_monitor_channel = wil_cfg80211_set_channel,
	.add_key = wil_cfg80211_add_key,
	.del_key = wil_cfg80211_del_key,
	.set_शेष_key = wil_cfg80211_set_शेष_key,
	/* AP mode */
	.change_beacon = wil_cfg80211_change_beacon,
	.start_ap = wil_cfg80211_start_ap,
	.stop_ap = wil_cfg80211_stop_ap,
	.add_station = wil_cfg80211_add_station,
	.del_station = wil_cfg80211_del_station,
	.change_station = wil_cfg80211_change_station,
	.probe_client = wil_cfg80211_probe_client,
	.change_bss = wil_cfg80211_change_bss,
	/* P2P device */
	.start_p2p_device = wil_cfg80211_start_p2p_device,
	.stop_p2p_device = wil_cfg80211_stop_p2p_device,
	.set_घातer_mgmt = wil_cfg80211_set_घातer_mgmt,
	.set_cqm_rssi_config = wil_cfg80211_set_cqm_rssi_config,
	.suspend = wil_cfg80211_suspend,
	.resume = wil_cfg80211_resume,
	.sched_scan_start = wil_cfg80211_sched_scan_start,
	.sched_scan_stop = wil_cfg80211_sched_scan_stop,
	.update_ft_ies = wil_cfg80211_update_ft_ies,
	.set_multicast_to_unicast = wil_cfg80211_set_multicast_to_unicast,
पूर्ण;

अटल व्योम wil_wiphy_init(काष्ठा wiphy *wiphy)
अणु
	wiphy->max_scan_ssids = 1;
	wiphy->max_scan_ie_len = WMI_MAX_IE_LEN;
	wiphy->max_reमुख्य_on_channel_duration = WIL_MAX_ROC_DURATION_MS;
	wiphy->max_num_pmkids = 0 /* TODO: */;
	wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
				 BIT(NL80211_IFTYPE_AP) |
				 BIT(NL80211_IFTYPE_P2P_CLIENT) |
				 BIT(NL80211_IFTYPE_P2P_GO) |
				 BIT(NL80211_IFTYPE_P2P_DEVICE) |
				 BIT(NL80211_IFTYPE_MONITOR);
	wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL |
			WIPHY_FLAG_AP_PROBE_RESP_OFFLOAD |
			WIPHY_FLAG_PS_ON_BY_DEFAULT;
	अगर (!disable_ap_sme)
		wiphy->flags |= WIPHY_FLAG_HAVE_AP_SME;
	dev_dbg(wiphy_dev(wiphy), "%s : flags = 0x%08x\n",
		__func__, wiphy->flags);
	wiphy->probe_resp_offload =
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS |
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_WPS2 |
		NL80211_PROBE_RESP_OFFLOAD_SUPPORT_P2P;

	wiphy->bands[NL80211_BAND_60GHZ] = &wil_band_60ghz;

	/* may change after पढ़ोing FW capabilities */
	wiphy->संकेत_type = CFG80211_SIGNAL_TYPE_UNSPEC;

	wiphy->cipher_suites = wil_cipher_suites;
	wiphy->n_cipher_suites = ARRAY_SIZE(wil_cipher_suites);
	wiphy->mgmt_stypes = wil_mgmt_stypes;
	wiphy->features |= NL80211_FEATURE_SK_TX_STATUS;

	wiphy->n_venकरोr_commands = ARRAY_SIZE(wil_nl80211_venकरोr_commands);
	wiphy->venकरोr_commands = wil_nl80211_venकरोr_commands;

#अगर_घोषित CONFIG_PM
	wiphy->wowlan = &wil_wowlan_support;
#पूर्ण_अगर
पूर्ण

पूर्णांक wil_cfg80211_अगरace_combinations_from_fw(
	काष्ठा wil6210_priv *wil, स्थिर काष्ठा wil_fw_record_concurrency *conc)
अणु
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);
	u32 total_limits = 0;
	u16 n_combos;
	स्थिर काष्ठा wil_fw_concurrency_combo *combo;
	स्थिर काष्ठा wil_fw_concurrency_limit *limit;
	काष्ठा ieee80211_अगरace_combination *अगरace_combinations;
	काष्ठा ieee80211_अगरace_limit *अगरace_limit;
	पूर्णांक i, j;

	अगर (wiphy->अगरace_combinations) अणु
		wil_dbg_misc(wil, "iface_combinations already set, skipping\n");
		वापस 0;
	पूर्ण

	combo = conc->combos;
	n_combos = le16_to_cpu(conc->n_combos);
	क्रम (i = 0; i < n_combos; i++) अणु
		total_limits += combo->n_limits;
		limit = combo->limits + combo->n_limits;
		combo = (काष्ठा wil_fw_concurrency_combo *)limit;
	पूर्ण

	अगरace_combinations =
		kzalloc(n_combos * माप(काष्ठा ieee80211_अगरace_combination) +
			total_limits * माप(काष्ठा ieee80211_अगरace_limit),
			GFP_KERNEL);
	अगर (!अगरace_combinations)
		वापस -ENOMEM;
	अगरace_limit = (काष्ठा ieee80211_अगरace_limit *)(अगरace_combinations +
						       n_combos);
	combo = conc->combos;
	क्रम (i = 0; i < n_combos; i++) अणु
		अगरace_combinations[i].max_पूर्णांकerfaces = combo->max_पूर्णांकerfaces;
		अगरace_combinations[i].num_dअगरferent_channels =
			combo->n_dअगरf_channels;
		अगरace_combinations[i].beacon_पूर्णांक_infra_match =
			combo->same_bi;
		अगरace_combinations[i].n_limits = combo->n_limits;
		wil_dbg_misc(wil,
			     "iface_combination %d: max_if %d, num_ch %d, bi_match %d\n",
			     i, अगरace_combinations[i].max_पूर्णांकerfaces,
			     अगरace_combinations[i].num_dअगरferent_channels,
			     अगरace_combinations[i].beacon_पूर्णांक_infra_match);
		limit = combo->limits;
		क्रम (j = 0; j < combo->n_limits; j++) अणु
			अगरace_limit[j].max = le16_to_cpu(limit[j].max);
			अगरace_limit[j].types = le16_to_cpu(limit[j].types);
			wil_dbg_misc(wil,
				     "limit %d: max %d types 0x%x\n", j,
				     अगरace_limit[j].max, अगरace_limit[j].types);
		पूर्ण
		अगरace_combinations[i].limits = अगरace_limit;
		अगरace_limit += combo->n_limits;
		limit += combo->n_limits;
		combo = (काष्ठा wil_fw_concurrency_combo *)limit;
	पूर्ण

	wil_dbg_misc(wil, "multiple VIFs supported, n_mids %d\n", conc->n_mids);
	wil->max_vअगरs = conc->n_mids + 1; /* including मुख्य पूर्णांकerface */
	अगर (wil->max_vअगरs > WIL_MAX_VIFS) अणु
		wil_info(wil, "limited number of VIFs supported(%d, FW %d)\n",
			 WIL_MAX_VIFS, wil->max_vअगरs);
		wil->max_vअगरs = WIL_MAX_VIFS;
	पूर्ण
	wiphy->n_अगरace_combinations = n_combos;
	wiphy->अगरace_combinations = अगरace_combinations;
	वापस 0;
पूर्ण

काष्ठा wil6210_priv *wil_cfg80211_init(काष्ठा device *dev)
अणु
	काष्ठा wiphy *wiphy;
	काष्ठा wil6210_priv *wil;
	काष्ठा ieee80211_channel *ch;

	dev_dbg(dev, "%s()\n", __func__);

	/* Note: the wireless_dev काष्ठाure is no दीर्घer allocated here.
	 * Instead, it is allocated as part of the net_device काष्ठाure
	 * क्रम मुख्य पूर्णांकerface and each VIF.
	 */
	wiphy = wiphy_new(&wil_cfg80211_ops, माप(काष्ठा wil6210_priv));
	अगर (!wiphy)
		वापस ERR_PTR(-ENOMEM);

	set_wiphy_dev(wiphy, dev);
	wil_wiphy_init(wiphy);

	wil = wiphy_to_wil(wiphy);
	wil->wiphy = wiphy;

	/* शेष monitor channel */
	ch = wiphy->bands[NL80211_BAND_60GHZ]->channels;
	cfg80211_chandef_create(&wil->monitor_chandef, ch, NL80211_CHAN_NO_HT);

	वापस wil;
पूर्ण

व्योम wil_cfg80211_deinit(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wiphy *wiphy = wil_to_wiphy(wil);

	dev_dbg(wil_to_dev(wil), "%s()\n", __func__);

	अगर (!wiphy)
		वापस;

	kमुक्त(wiphy->अगरace_combinations);
	wiphy->अगरace_combinations = शून्य;

	wiphy_मुक्त(wiphy);
	/* करो not access wil6210_priv after वापसing from here */
पूर्ण

व्योम wil_p2p_wdev_मुक्त(काष्ठा wil6210_priv *wil)
अणु
	काष्ठा wireless_dev *p2p_wdev;

	mutex_lock(&wil->vअगर_mutex);
	p2p_wdev = wil->p2p_wdev;
	wil->p2p_wdev = शून्य;
	wil->radio_wdev = wil->मुख्य_ndev->ieee80211_ptr;
	mutex_unlock(&wil->vअगर_mutex);
	अगर (p2p_wdev) अणु
		wiphy_lock(wil->wiphy);
		cfg80211_unरेजिस्टर_wdev(p2p_wdev);
		wiphy_unlock(wil->wiphy);
		kमुक्त(p2p_wdev);
	पूर्ण
पूर्ण

अटल पूर्णांक wil_rf_sector_status_to_rc(u8 status)
अणु
	चयन (status) अणु
	हाल WMI_RF_SECTOR_STATUS_SUCCESS:
		वापस 0;
	हाल WMI_RF_SECTOR_STATUS_BAD_PARAMETERS_ERROR:
		वापस -EINVAL;
	हाल WMI_RF_SECTOR_STATUS_BUSY_ERROR:
		वापस -EAGAIN;
	हाल WMI_RF_SECTOR_STATUS_NOT_SUPPORTED_ERROR:
		वापस -EOPNOTSUPP;
	शेष:
		वापस -EINVAL;
	पूर्ण
पूर्ण

अटल पूर्णांक wil_rf_sector_get_cfg(काष्ठा wiphy *wiphy,
				 काष्ठा wireless_dev *wdev,
				 स्थिर व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा wil6210_priv *wil = wdev_to_wil(wdev);
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);
	पूर्णांक rc;
	काष्ठा nlattr *tb[QCA_ATTR_DMG_RF_SECTOR_MAX + 1];
	u16 sector_index;
	u8 sector_type;
	u32 rf_modules_vec;
	काष्ठा wmi_get_rf_sector_params_cmd cmd;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_get_rf_sector_params_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_RF_SECTOR_STATUS_NOT_SUPPORTED_ERRORपूर्ण,
	पूर्ण;
	काष्ठा sk_buff *msg;
	काष्ठा nlattr *nl_cfgs, *nl_cfg;
	u32 i;
	काष्ठा wmi_rf_sector_info *si;

	अगर (!test_bit(WMI_FW_CAPABILITY_RF_SECTORS, wil->fw_capabilities))
		वापस -EOPNOTSUPP;

	rc = nla_parse_deprecated(tb, QCA_ATTR_DMG_RF_SECTOR_MAX, data,
				  data_len, wil_rf_sector_policy, शून्य);
	अगर (rc) अणु
		wil_err(wil, "Invalid rf sector ATTR\n");
		वापस rc;
	पूर्ण

	अगर (!tb[QCA_ATTR_DMG_RF_SECTOR_INDEX] ||
	    !tb[QCA_ATTR_DMG_RF_SECTOR_TYPE] ||
	    !tb[QCA_ATTR_DMG_RF_MODULE_MASK]) अणु
		wil_err(wil, "Invalid rf sector spec\n");
		वापस -EINVAL;
	पूर्ण

	sector_index = nla_get_u16(
		tb[QCA_ATTR_DMG_RF_SECTOR_INDEX]);
	अगर (sector_index >= WIL_MAX_RF_SECTORS) अणु
		wil_err(wil, "Invalid sector index %d\n", sector_index);
		वापस -EINVAL;
	पूर्ण

	sector_type = nla_get_u8(tb[QCA_ATTR_DMG_RF_SECTOR_TYPE]);
	अगर (sector_type >= QCA_ATTR_DMG_RF_SECTOR_TYPE_MAX) अणु
		wil_err(wil, "Invalid sector type %d\n", sector_type);
		वापस -EINVAL;
	पूर्ण

	rf_modules_vec = nla_get_u32(
		tb[QCA_ATTR_DMG_RF_MODULE_MASK]);
	अगर (rf_modules_vec >= BIT(WMI_MAX_RF_MODULES_NUM)) अणु
		wil_err(wil, "Invalid rf module mask 0x%x\n", rf_modules_vec);
		वापस -EINVAL;
	पूर्ण

	cmd.sector_idx = cpu_to_le16(sector_index);
	cmd.sector_type = sector_type;
	cmd.rf_modules_vec = rf_modules_vec & 0xFF;
	rc = wmi_call(wil, WMI_GET_RF_SECTOR_PARAMS_CMDID, vअगर->mid,
		      &cmd, माप(cmd), WMI_GET_RF_SECTOR_PARAMS_DONE_EVENTID,
		      &reply, माप(reply),
		      500);
	अगर (rc)
		वापस rc;
	अगर (reply.evt.status) अणु
		wil_err(wil, "get rf sector cfg failed with status %d\n",
			reply.evt.status);
		वापस wil_rf_sector_status_to_rc(reply.evt.status);
	पूर्ण

	msg = cfg80211_venकरोr_cmd_alloc_reply_skb(
		wiphy, 64 * WMI_MAX_RF_MODULES_NUM);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nla_put_u64_64bit(msg, QCA_ATTR_TSF,
			      le64_to_cpu(reply.evt.tsf),
			      QCA_ATTR_PAD))
		जाओ nla_put_failure;

	nl_cfgs = nla_nest_start_noflag(msg, QCA_ATTR_DMG_RF_SECTOR_CFG);
	अगर (!nl_cfgs)
		जाओ nla_put_failure;
	क्रम (i = 0; i < WMI_MAX_RF_MODULES_NUM; i++) अणु
		अगर (!(rf_modules_vec & BIT(i)))
			जारी;
		nl_cfg = nla_nest_start_noflag(msg, i);
		अगर (!nl_cfg)
			जाओ nla_put_failure;
		si = &reply.evt.sectors_info[i];
		अगर (nla_put_u8(msg, QCA_ATTR_DMG_RF_SECTOR_CFG_MODULE_INDEX,
			       i) ||
		    nla_put_u32(msg, QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE0,
				le32_to_cpu(si->etype0)) ||
		    nla_put_u32(msg, QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE1,
				le32_to_cpu(si->etype1)) ||
		    nla_put_u32(msg, QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE2,
				le32_to_cpu(si->etype2)) ||
		    nla_put_u32(msg, QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_HI,
				le32_to_cpu(si->psh_hi)) ||
		    nla_put_u32(msg, QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_LO,
				le32_to_cpu(si->psh_lo)) ||
		    nla_put_u32(msg, QCA_ATTR_DMG_RF_SECTOR_CFG_DTYPE_X16,
				le32_to_cpu(si->dtype_swch_off)))
			जाओ nla_put_failure;
		nla_nest_end(msg, nl_cfg);
	पूर्ण

	nla_nest_end(msg, nl_cfgs);
	rc = cfg80211_venकरोr_cmd_reply(msg);
	वापस rc;
nla_put_failure:
	kमुक्त_skb(msg);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक wil_rf_sector_set_cfg(काष्ठा wiphy *wiphy,
				 काष्ठा wireless_dev *wdev,
				 स्थिर व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा wil6210_priv *wil = wdev_to_wil(wdev);
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);
	पूर्णांक rc, पंचांगp;
	काष्ठा nlattr *tb[QCA_ATTR_DMG_RF_SECTOR_MAX + 1];
	काष्ठा nlattr *tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_MAX + 1];
	u16 sector_index, rf_module_index;
	u8 sector_type;
	u32 rf_modules_vec = 0;
	काष्ठा wmi_set_rf_sector_params_cmd cmd;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_set_rf_sector_params_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_RF_SECTOR_STATUS_NOT_SUPPORTED_ERRORपूर्ण,
	पूर्ण;
	काष्ठा nlattr *nl_cfg;
	काष्ठा wmi_rf_sector_info *si;

	अगर (!test_bit(WMI_FW_CAPABILITY_RF_SECTORS, wil->fw_capabilities))
		वापस -EOPNOTSUPP;

	rc = nla_parse_deprecated(tb, QCA_ATTR_DMG_RF_SECTOR_MAX, data,
				  data_len, wil_rf_sector_policy, शून्य);
	अगर (rc) अणु
		wil_err(wil, "Invalid rf sector ATTR\n");
		वापस rc;
	पूर्ण

	अगर (!tb[QCA_ATTR_DMG_RF_SECTOR_INDEX] ||
	    !tb[QCA_ATTR_DMG_RF_SECTOR_TYPE] ||
	    !tb[QCA_ATTR_DMG_RF_SECTOR_CFG]) अणु
		wil_err(wil, "Invalid rf sector spec\n");
		वापस -EINVAL;
	पूर्ण

	sector_index = nla_get_u16(
		tb[QCA_ATTR_DMG_RF_SECTOR_INDEX]);
	अगर (sector_index >= WIL_MAX_RF_SECTORS) अणु
		wil_err(wil, "Invalid sector index %d\n", sector_index);
		वापस -EINVAL;
	पूर्ण

	sector_type = nla_get_u8(tb[QCA_ATTR_DMG_RF_SECTOR_TYPE]);
	अगर (sector_type >= QCA_ATTR_DMG_RF_SECTOR_TYPE_MAX) अणु
		wil_err(wil, "Invalid sector type %d\n", sector_type);
		वापस -EINVAL;
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));

	cmd.sector_idx = cpu_to_le16(sector_index);
	cmd.sector_type = sector_type;
	nla_क्रम_each_nested(nl_cfg, tb[QCA_ATTR_DMG_RF_SECTOR_CFG],
			    पंचांगp) अणु
		rc = nla_parse_nested_deprecated(tb2,
						 QCA_ATTR_DMG_RF_SECTOR_CFG_MAX,
						 nl_cfg,
						 wil_rf_sector_cfg_policy,
						 शून्य);
		अगर (rc) अणु
			wil_err(wil, "invalid sector cfg\n");
			वापस -EINVAL;
		पूर्ण

		अगर (!tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_MODULE_INDEX] ||
		    !tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE0] ||
		    !tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE1] ||
		    !tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE2] ||
		    !tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_HI] ||
		    !tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_LO] ||
		    !tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_DTYPE_X16]) अणु
			wil_err(wil, "missing cfg params\n");
			वापस -EINVAL;
		पूर्ण

		rf_module_index = nla_get_u8(
			tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_MODULE_INDEX]);
		अगर (rf_module_index >= WMI_MAX_RF_MODULES_NUM) अणु
			wil_err(wil, "invalid RF module index %d\n",
				rf_module_index);
			वापस -EINVAL;
		पूर्ण
		rf_modules_vec |= BIT(rf_module_index);
		si = &cmd.sectors_info[rf_module_index];
		si->etype0 = cpu_to_le32(nla_get_u32(
			tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE0]));
		si->etype1 = cpu_to_le32(nla_get_u32(
			tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE1]));
		si->etype2 = cpu_to_le32(nla_get_u32(
			tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_ETYPE2]));
		si->psh_hi = cpu_to_le32(nla_get_u32(
			tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_HI]));
		si->psh_lo = cpu_to_le32(nla_get_u32(
			tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_PSH_LO]));
		si->dtype_swch_off = cpu_to_le32(nla_get_u32(
			tb2[QCA_ATTR_DMG_RF_SECTOR_CFG_DTYPE_X16]));
	पूर्ण

	cmd.rf_modules_vec = rf_modules_vec & 0xFF;
	rc = wmi_call(wil, WMI_SET_RF_SECTOR_PARAMS_CMDID, vअगर->mid,
		      &cmd, माप(cmd), WMI_SET_RF_SECTOR_PARAMS_DONE_EVENTID,
		      &reply, माप(reply),
		      500);
	अगर (rc)
		वापस rc;
	वापस wil_rf_sector_status_to_rc(reply.evt.status);
पूर्ण

अटल पूर्णांक wil_rf_sector_get_selected(काष्ठा wiphy *wiphy,
				      काष्ठा wireless_dev *wdev,
				      स्थिर व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा wil6210_priv *wil = wdev_to_wil(wdev);
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);
	पूर्णांक rc;
	काष्ठा nlattr *tb[QCA_ATTR_DMG_RF_SECTOR_MAX + 1];
	u8 sector_type, mac_addr[ETH_ALEN];
	पूर्णांक cid = 0;
	काष्ठा wmi_get_selected_rf_sector_index_cmd cmd;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_get_selected_rf_sector_index_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_RF_SECTOR_STATUS_NOT_SUPPORTED_ERRORपूर्ण,
	पूर्ण;
	काष्ठा sk_buff *msg;

	अगर (!test_bit(WMI_FW_CAPABILITY_RF_SECTORS, wil->fw_capabilities))
		वापस -EOPNOTSUPP;

	rc = nla_parse_deprecated(tb, QCA_ATTR_DMG_RF_SECTOR_MAX, data,
				  data_len, wil_rf_sector_policy, शून्य);
	अगर (rc) अणु
		wil_err(wil, "Invalid rf sector ATTR\n");
		वापस rc;
	पूर्ण

	अगर (!tb[QCA_ATTR_DMG_RF_SECTOR_TYPE]) अणु
		wil_err(wil, "Invalid rf sector spec\n");
		वापस -EINVAL;
	पूर्ण
	sector_type = nla_get_u8(tb[QCA_ATTR_DMG_RF_SECTOR_TYPE]);
	अगर (sector_type >= QCA_ATTR_DMG_RF_SECTOR_TYPE_MAX) अणु
		wil_err(wil, "Invalid sector type %d\n", sector_type);
		वापस -EINVAL;
	पूर्ण

	अगर (tb[QCA_ATTR_MAC_ADDR]) अणु
		ether_addr_copy(mac_addr, nla_data(tb[QCA_ATTR_MAC_ADDR]));
		cid = wil_find_cid(wil, vअगर->mid, mac_addr);
		अगर (cid < 0) अणु
			wil_err(wil, "invalid MAC address %pM\n", mac_addr);
			वापस -ENOENT;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (test_bit(wil_vअगर_fwconnected, vअगर->status)) अणु
			wil_err(wil, "must specify MAC address when connected\n");
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	स_रखो(&cmd, 0, माप(cmd));
	cmd.cid = (u8)cid;
	cmd.sector_type = sector_type;
	rc = wmi_call(wil, WMI_GET_SELECTED_RF_SECTOR_INDEX_CMDID, vअगर->mid,
		      &cmd, माप(cmd),
		      WMI_GET_SELECTED_RF_SECTOR_INDEX_DONE_EVENTID,
		      &reply, माप(reply),
		      500);
	अगर (rc)
		वापस rc;
	अगर (reply.evt.status) अणु
		wil_err(wil, "get rf selected sector cfg failed with status %d\n",
			reply.evt.status);
		वापस wil_rf_sector_status_to_rc(reply.evt.status);
	पूर्ण

	msg = cfg80211_venकरोr_cmd_alloc_reply_skb(
		wiphy, 64 * WMI_MAX_RF_MODULES_NUM);
	अगर (!msg)
		वापस -ENOMEM;

	अगर (nla_put_u64_64bit(msg, QCA_ATTR_TSF,
			      le64_to_cpu(reply.evt.tsf),
			      QCA_ATTR_PAD) ||
	    nla_put_u16(msg, QCA_ATTR_DMG_RF_SECTOR_INDEX,
			le16_to_cpu(reply.evt.sector_idx)))
		जाओ nla_put_failure;

	rc = cfg80211_venकरोr_cmd_reply(msg);
	वापस rc;
nla_put_failure:
	kमुक्त_skb(msg);
	वापस -ENOBUFS;
पूर्ण

अटल पूर्णांक wil_rf_sector_wmi_set_selected(काष्ठा wil6210_priv *wil,
					  u8 mid, u16 sector_index,
					  u8 sector_type, u8 cid)
अणु
	काष्ठा wmi_set_selected_rf_sector_index_cmd cmd;
	काष्ठा अणु
		काष्ठा wmi_cmd_hdr wmi;
		काष्ठा wmi_set_selected_rf_sector_index_करोne_event evt;
	पूर्ण __packed reply = अणु
		.evt = अणु.status = WMI_RF_SECTOR_STATUS_NOT_SUPPORTED_ERRORपूर्ण,
	पूर्ण;
	पूर्णांक rc;

	स_रखो(&cmd, 0, माप(cmd));
	cmd.sector_idx = cpu_to_le16(sector_index);
	cmd.sector_type = sector_type;
	cmd.cid = (u8)cid;
	rc = wmi_call(wil, WMI_SET_SELECTED_RF_SECTOR_INDEX_CMDID, mid,
		      &cmd, माप(cmd),
		      WMI_SET_SELECTED_RF_SECTOR_INDEX_DONE_EVENTID,
		      &reply, माप(reply),
		      500);
	अगर (rc)
		वापस rc;
	वापस wil_rf_sector_status_to_rc(reply.evt.status);
पूर्ण

अटल पूर्णांक wil_rf_sector_set_selected(काष्ठा wiphy *wiphy,
				      काष्ठा wireless_dev *wdev,
				      स्थिर व्योम *data, पूर्णांक data_len)
अणु
	काष्ठा wil6210_priv *wil = wdev_to_wil(wdev);
	काष्ठा wil6210_vअगर *vअगर = wdev_to_vअगर(wil, wdev);
	पूर्णांक rc;
	काष्ठा nlattr *tb[QCA_ATTR_DMG_RF_SECTOR_MAX + 1];
	u16 sector_index;
	u8 sector_type, mac_addr[ETH_ALEN], i;
	पूर्णांक cid = 0;

	अगर (!test_bit(WMI_FW_CAPABILITY_RF_SECTORS, wil->fw_capabilities))
		वापस -EOPNOTSUPP;

	rc = nla_parse_deprecated(tb, QCA_ATTR_DMG_RF_SECTOR_MAX, data,
				  data_len, wil_rf_sector_policy, शून्य);
	अगर (rc) अणु
		wil_err(wil, "Invalid rf sector ATTR\n");
		वापस rc;
	पूर्ण

	अगर (!tb[QCA_ATTR_DMG_RF_SECTOR_INDEX] ||
	    !tb[QCA_ATTR_DMG_RF_SECTOR_TYPE]) अणु
		wil_err(wil, "Invalid rf sector spec\n");
		वापस -EINVAL;
	पूर्ण

	sector_index = nla_get_u16(
		tb[QCA_ATTR_DMG_RF_SECTOR_INDEX]);
	अगर (sector_index >= WIL_MAX_RF_SECTORS &&
	    sector_index != WMI_INVALID_RF_SECTOR_INDEX) अणु
		wil_err(wil, "Invalid sector index %d\n", sector_index);
		वापस -EINVAL;
	पूर्ण

	sector_type = nla_get_u8(tb[QCA_ATTR_DMG_RF_SECTOR_TYPE]);
	अगर (sector_type >= QCA_ATTR_DMG_RF_SECTOR_TYPE_MAX) अणु
		wil_err(wil, "Invalid sector type %d\n", sector_type);
		वापस -EINVAL;
	पूर्ण

	अगर (tb[QCA_ATTR_MAC_ADDR]) अणु
		ether_addr_copy(mac_addr, nla_data(tb[QCA_ATTR_MAC_ADDR]));
		अगर (!is_broadcast_ether_addr(mac_addr)) अणु
			cid = wil_find_cid(wil, vअगर->mid, mac_addr);
			अगर (cid < 0) अणु
				wil_err(wil, "invalid MAC address %pM\n",
					mac_addr);
				वापस -ENOENT;
			पूर्ण
		पूर्ण अन्यथा अणु
			अगर (sector_index != WMI_INVALID_RF_SECTOR_INDEX) अणु
				wil_err(wil, "broadcast MAC valid only with unlocking\n");
				वापस -EINVAL;
			पूर्ण
			cid = -1;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (test_bit(wil_vअगर_fwconnected, vअगर->status)) अणु
			wil_err(wil, "must specify MAC address when connected\n");
			वापस -EINVAL;
		पूर्ण
		/* otherwise, using cid=0 क्रम unassociated station */
	पूर्ण

	अगर (cid >= 0) अणु
		rc = wil_rf_sector_wmi_set_selected(wil, vअगर->mid, sector_index,
						    sector_type, cid);
	पूर्ण अन्यथा अणु
		/* unlock all cids */
		rc = wil_rf_sector_wmi_set_selected(
			wil, vअगर->mid, WMI_INVALID_RF_SECTOR_INDEX,
			sector_type, WIL_CID_ALL);
		अगर (rc == -EINVAL) अणु
			क्रम (i = 0; i < wil->max_assoc_sta; i++) अणु
				अगर (wil->sta[i].mid != vअगर->mid)
					जारी;
				rc = wil_rf_sector_wmi_set_selected(
					wil, vअगर->mid,
					WMI_INVALID_RF_SECTOR_INDEX,
					sector_type, i);
				/* the FW will silently ignore and वापस
				 * success क्रम unused cid, so पात the loop
				 * on any other error
				 */
				अगर (rc) अणु
					wil_err(wil, "unlock cid %d failed with status %d\n",
						i, rc);
					अवरोध;
				पूर्ण
			पूर्ण
		पूर्ण
	पूर्ण

	वापस rc;
पूर्ण
