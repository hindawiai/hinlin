<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 */
/*
 * Copyright (c) 2012 - 2018 Microchip Technology Inc., and its subsidiaries.
 * All rights reserved.
 */

#अगर_अघोषित WILC_FW_H
#घोषणा WILC_FW_H

#समावेश <linux/ieee80211.h>

#घोषणा WILC_MAX_NUM_STA			9
#घोषणा WILC_MAX_RATES_SUPPORTED		12
#घोषणा WILC_MAX_NUM_PMKIDS			16
#घोषणा WILC_MAX_NUM_SCANNED_CH			14

काष्ठा wilc_assoc_resp अणु
	__le16 capab_info;
	__le16 status_code;
	__le16 aid;
पूर्ण __packed;

काष्ठा wilc_pmkid अणु
	u8 bssid[ETH_ALEN];
	u8 pmkid[WLAN_PMKID_LEN];
पूर्ण __packed;

काष्ठा wilc_pmkid_attr अणु
	u8 numpmkid;
	काष्ठा wilc_pmkid pmkidlist[WILC_MAX_NUM_PMKIDS];
पूर्ण __packed;

काष्ठा wilc_reg_frame अणु
	u8 reg;
	u8 reg_id;
	__le16 frame_type;
पूर्ण __packed;

काष्ठा wilc_drv_handler अणु
	__le32 handler;
	u8 mode;
पूर्ण __packed;

काष्ठा wilc_wep_key अणु
	u8 index;
	u8 key_len;
	u8 key[];
पूर्ण __packed;

काष्ठा wilc_sta_wpa_ptk अणु
	u8 mac_addr[ETH_ALEN];
	u8 key_len;
	u8 key[];
पूर्ण __packed;

काष्ठा wilc_ap_wpa_ptk अणु
	u8 mac_addr[ETH_ALEN];
	u8 index;
	u8 key_len;
	u8 key[];
पूर्ण __packed;

काष्ठा wilc_gtk_key अणु
	u8 mac_addr[ETH_ALEN];
	u8 rsc[8];
	u8 index;
	u8 key_len;
	u8 key[];
पूर्ण __packed;

काष्ठा wilc_op_mode अणु
	__le32 mode;
पूर्ण __packed;

काष्ठा wilc_noa_opp_enable अणु
	u8 ct_winकरोw;
	u8 cnt;
	__le32 duration;
	__le32 पूर्णांकerval;
	__le32 start_समय;
पूर्ण __packed;

काष्ठा wilc_noa_opp_disable अणु
	u8 cnt;
	__le32 duration;
	__le32 पूर्णांकerval;
	__le32 start_समय;
पूर्ण __packed;

काष्ठा wilc_join_bss_param अणु
	अक्षर ssid[IEEE80211_MAX_SSID_LEN];
	u8 ssid_terminator;
	u8 bss_type;
	u8 ch;
	__le16 cap_info;
	u8 sa[ETH_ALEN];
	u8 bssid[ETH_ALEN];
	__le16 beacon_period;
	u8 dtim_period;
	u8 supp_rates[WILC_MAX_RATES_SUPPORTED + 1];
	u8 wmm_cap;
	u8 uapsd_cap;
	u8 ht_capable;
	u8 rsn_found;
	u8 rsn_grp_policy;
	u8 mode_802_11i;
	u8 p_suites[3];
	u8 akm_suites[3];
	u8 rsn_cap[2];
	u8 noa_enabled;
	__le32 tsf_lo;
	u8 idx;
	u8 opp_enabled;
	जोड़ अणु
		काष्ठा wilc_noa_opp_disable opp_dis;
		काष्ठा wilc_noa_opp_enable opp_en;
	पूर्ण;
पूर्ण __packed;
#पूर्ण_अगर
