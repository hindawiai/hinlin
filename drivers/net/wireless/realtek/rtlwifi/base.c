<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/* Copyright(c) 2009-2012  Realtek Corporation.*/

#समावेश "wifi.h"
#समावेश "rc.h"
#समावेश "base.h"
#समावेश "efuse.h"
#समावेश "cam.h"
#समावेश "ps.h"
#समावेश "regd.h"
#समावेश "pci.h"
#समावेश <linux/ip.h>
#समावेश <linux/module.h>
#समावेश <linux/udp.h>

/*
 *NOTICE!!!: This file will be very big, we should
 *keep it clear under following roles:
 *
 *This file include following parts, so, अगर you add new
 *functions पूर्णांकo this file, please check which part it
 *should includes. or check अगर you should add new part
 *क्रम this file:
 *
 *1) mac80211 init functions
 *2) tx inक्रमmation functions
 *3) functions called by core.c
 *4) wq & समयr callback functions
 *5) frame process functions
 *6) IOT functions
 *7) sysfs functions
 *8) vअगर functions
 *9) ...
 */

/*********************************************************
 *
 * mac80211 init functions
 *
 *********************************************************/
अटल काष्ठा ieee80211_channel rtl_channeltable_2g[] = अणु
	अणु.center_freq = 2412, .hw_value = 1,पूर्ण,
	अणु.center_freq = 2417, .hw_value = 2,पूर्ण,
	अणु.center_freq = 2422, .hw_value = 3,पूर्ण,
	अणु.center_freq = 2427, .hw_value = 4,पूर्ण,
	अणु.center_freq = 2432, .hw_value = 5,पूर्ण,
	अणु.center_freq = 2437, .hw_value = 6,पूर्ण,
	अणु.center_freq = 2442, .hw_value = 7,पूर्ण,
	अणु.center_freq = 2447, .hw_value = 8,पूर्ण,
	अणु.center_freq = 2452, .hw_value = 9,पूर्ण,
	अणु.center_freq = 2457, .hw_value = 10,पूर्ण,
	अणु.center_freq = 2462, .hw_value = 11,पूर्ण,
	अणु.center_freq = 2467, .hw_value = 12,पूर्ण,
	अणु.center_freq = 2472, .hw_value = 13,पूर्ण,
	अणु.center_freq = 2484, .hw_value = 14,पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_channel rtl_channeltable_5g[] = अणु
	अणु.center_freq = 5180, .hw_value = 36,पूर्ण,
	अणु.center_freq = 5200, .hw_value = 40,पूर्ण,
	अणु.center_freq = 5220, .hw_value = 44,पूर्ण,
	अणु.center_freq = 5240, .hw_value = 48,पूर्ण,
	अणु.center_freq = 5260, .hw_value = 52,पूर्ण,
	अणु.center_freq = 5280, .hw_value = 56,पूर्ण,
	अणु.center_freq = 5300, .hw_value = 60,पूर्ण,
	अणु.center_freq = 5320, .hw_value = 64,पूर्ण,
	अणु.center_freq = 5500, .hw_value = 100,पूर्ण,
	अणु.center_freq = 5520, .hw_value = 104,पूर्ण,
	अणु.center_freq = 5540, .hw_value = 108,पूर्ण,
	अणु.center_freq = 5560, .hw_value = 112,पूर्ण,
	अणु.center_freq = 5580, .hw_value = 116,पूर्ण,
	अणु.center_freq = 5600, .hw_value = 120,पूर्ण,
	अणु.center_freq = 5620, .hw_value = 124,पूर्ण,
	अणु.center_freq = 5640, .hw_value = 128,पूर्ण,
	अणु.center_freq = 5660, .hw_value = 132,पूर्ण,
	अणु.center_freq = 5680, .hw_value = 136,पूर्ण,
	अणु.center_freq = 5700, .hw_value = 140,पूर्ण,
	अणु.center_freq = 5745, .hw_value = 149,पूर्ण,
	अणु.center_freq = 5765, .hw_value = 153,पूर्ण,
	अणु.center_freq = 5785, .hw_value = 157,पूर्ण,
	अणु.center_freq = 5805, .hw_value = 161,पूर्ण,
	अणु.center_freq = 5825, .hw_value = 165,पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_rate rtl_ratetable_2g[] = अणु
	अणु.bitrate = 10, .hw_value = 0x00,पूर्ण,
	अणु.bitrate = 20, .hw_value = 0x01,पूर्ण,
	अणु.bitrate = 55, .hw_value = 0x02,पूर्ण,
	अणु.bitrate = 110, .hw_value = 0x03,पूर्ण,
	अणु.bitrate = 60, .hw_value = 0x04,पूर्ण,
	अणु.bitrate = 90, .hw_value = 0x05,पूर्ण,
	अणु.bitrate = 120, .hw_value = 0x06,पूर्ण,
	अणु.bitrate = 180, .hw_value = 0x07,पूर्ण,
	अणु.bitrate = 240, .hw_value = 0x08,पूर्ण,
	अणु.bitrate = 360, .hw_value = 0x09,पूर्ण,
	अणु.bitrate = 480, .hw_value = 0x0a,पूर्ण,
	अणु.bitrate = 540, .hw_value = 0x0b,पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_rate rtl_ratetable_5g[] = अणु
	अणु.bitrate = 60, .hw_value = 0x04,पूर्ण,
	अणु.bitrate = 90, .hw_value = 0x05,पूर्ण,
	अणु.bitrate = 120, .hw_value = 0x06,पूर्ण,
	अणु.bitrate = 180, .hw_value = 0x07,पूर्ण,
	अणु.bitrate = 240, .hw_value = 0x08,पूर्ण,
	अणु.bitrate = 360, .hw_value = 0x09,पूर्ण,
	अणु.bitrate = 480, .hw_value = 0x0a,पूर्ण,
	अणु.bitrate = 540, .hw_value = 0x0b,पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_supported_band rtl_band_2ghz = अणु
	.band = NL80211_BAND_2GHZ,

	.channels = rtl_channeltable_2g,
	.n_channels = ARRAY_SIZE(rtl_channeltable_2g),

	.bitrates = rtl_ratetable_2g,
	.n_bitrates = ARRAY_SIZE(rtl_ratetable_2g),

	.ht_cap = अणु0पूर्ण,
पूर्ण;

अटल काष्ठा ieee80211_supported_band rtl_band_5ghz = अणु
	.band = NL80211_BAND_5GHZ,

	.channels = rtl_channeltable_5g,
	.n_channels = ARRAY_SIZE(rtl_channeltable_5g),

	.bitrates = rtl_ratetable_5g,
	.n_bitrates = ARRAY_SIZE(rtl_ratetable_5g),

	.ht_cap = अणु0पूर्ण,
पूर्ण;

अटल स्थिर u8 tid_to_ac[] = अणु
	2, /* IEEE80211_AC_BE */
	3, /* IEEE80211_AC_BK */
	3, /* IEEE80211_AC_BK */
	2, /* IEEE80211_AC_BE */
	1, /* IEEE80211_AC_VI */
	1, /* IEEE80211_AC_VI */
	0, /* IEEE80211_AC_VO */
	0, /* IEEE80211_AC_VO */
पूर्ण;

u8 rtl_tid_to_ac(u8 tid)
अणु
	वापस tid_to_ac[tid];
पूर्ण
EXPORT_SYMBOL_GPL(rtl_tid_to_ac);

अटल व्योम _rtl_init_hw_ht_capab(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_sta_ht_cap *ht_cap)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);

	ht_cap->ht_supported = true;
	ht_cap->cap = IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
	    IEEE80211_HT_CAP_SGI_40 |
	    IEEE80211_HT_CAP_SGI_20 |
	    IEEE80211_HT_CAP_DSSSCCK40 | IEEE80211_HT_CAP_MAX_AMSDU;

	अगर (rtlpriv->rtlhal.disable_amsdu_8k)
		ht_cap->cap &= ~IEEE80211_HT_CAP_MAX_AMSDU;

	/*
	 *Maximum length of AMPDU that the STA can receive.
	 *Length = 2 ^ (13 + max_ampdu_length_exp) - 1 (octets)
	 */
	ht_cap->ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K;

	/*Minimum MPDU start spacing , */
	ht_cap->ampdu_density = IEEE80211_HT_MPDU_DENSITY_16;

	ht_cap->mcs.tx_params = IEEE80211_HT_MCS_TX_DEFINED;

	/*hw->wiphy->bands[NL80211_BAND_2GHZ]
	 *base on ant_num
	 *rx_mask: RX mask
	 *अगर rx_ant = 1 rx_mask[0]= 0xff;==>MCS0-MCS7
	 *अगर rx_ant = 2 rx_mask[1]= 0xff;==>MCS8-MCS15
	 *अगर rx_ant >= 3 rx_mask[2]= 0xff;
	 *अगर BW_40 rx_mask[4]= 0x01;
	 *highest supported RX rate
	 */
	अगर (rtlpriv->dm.supp_phymode_चयन) अणु
		pr_info("Support phy mode switch\n");

		ht_cap->mcs.rx_mask[0] = 0xFF;
		ht_cap->mcs.rx_mask[1] = 0xFF;
		ht_cap->mcs.rx_mask[4] = 0x01;

		ht_cap->mcs.rx_highest = cpu_to_le16(MAX_BIT_RATE_40MHZ_MCS15);
	पूर्ण अन्यथा अणु
		अगर (get_rf_type(rtlphy) == RF_1T2R ||
		    get_rf_type(rtlphy) == RF_2T2R) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG,
				"1T2R or 2T2R\n");
			ht_cap->mcs.rx_mask[0] = 0xFF;
			ht_cap->mcs.rx_mask[1] = 0xFF;
			ht_cap->mcs.rx_mask[4] = 0x01;

			ht_cap->mcs.rx_highest =
				 cpu_to_le16(MAX_BIT_RATE_40MHZ_MCS15);
		पूर्ण अन्यथा अगर (get_rf_type(rtlphy) == RF_1T1R) अणु
			rtl_dbg(rtlpriv, COMP_INIT, DBG_DMESG, "1T1R\n");

			ht_cap->mcs.rx_mask[0] = 0xFF;
			ht_cap->mcs.rx_mask[1] = 0x00;
			ht_cap->mcs.rx_mask[4] = 0x01;

			ht_cap->mcs.rx_highest =
				 cpu_to_le16(MAX_BIT_RATE_40MHZ_MCS7);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम _rtl_init_hw_vht_capab(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_sta_vht_cap *vht_cap)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);

	अगर (!(rtlpriv->cfg->spec_ver & RTL_SPEC_SUPPORT_VHT))
		वापस;

	अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8812AE ||
	    rtlhal->hw_type == HARDWARE_TYPE_RTL8822BE) अणु
		u16 mcs_map;

		vht_cap->vht_supported = true;
		vht_cap->cap =
			IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 |
			IEEE80211_VHT_CAP_SHORT_GI_80 |
			IEEE80211_VHT_CAP_TXSTBC |
			IEEE80211_VHT_CAP_RXSTBC_1 |
			IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
			IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
			IEEE80211_VHT_CAP_HTC_VHT |
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK |
			IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN |
			IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN |
			0;

		mcs_map = IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 |
			IEEE80211_VHT_MCS_SUPPORT_0_9 << 2 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 4 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 6 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 8 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 10 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 12 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 14;

		vht_cap->vht_mcs.rx_mcs_map = cpu_to_le16(mcs_map);
		vht_cap->vht_mcs.rx_highest =
			cpu_to_le16(MAX_BIT_RATE_SHORT_GI_2NSS_80MHZ_MCS9);
		vht_cap->vht_mcs.tx_mcs_map = cpu_to_le16(mcs_map);
		vht_cap->vht_mcs.tx_highest =
			cpu_to_le16(MAX_BIT_RATE_SHORT_GI_2NSS_80MHZ_MCS9);
	पूर्ण अन्यथा अगर (rtlhal->hw_type == HARDWARE_TYPE_RTL8821AE) अणु
		u16 mcs_map;

		vht_cap->vht_supported = true;
		vht_cap->cap =
			IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_11454 |
			IEEE80211_VHT_CAP_SHORT_GI_80 |
			IEEE80211_VHT_CAP_TXSTBC |
			IEEE80211_VHT_CAP_RXSTBC_1 |
			IEEE80211_VHT_CAP_SU_BEAMFORMER_CAPABLE |
			IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
			IEEE80211_VHT_CAP_HTC_VHT |
			IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_MASK |
			IEEE80211_VHT_CAP_RX_ANTENNA_PATTERN |
			IEEE80211_VHT_CAP_TX_ANTENNA_PATTERN |
			0;

		mcs_map = IEEE80211_VHT_MCS_SUPPORT_0_9 << 0 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 2 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 4 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 6 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 8 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 10 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 12 |
			IEEE80211_VHT_MCS_NOT_SUPPORTED << 14;

		vht_cap->vht_mcs.rx_mcs_map = cpu_to_le16(mcs_map);
		vht_cap->vht_mcs.rx_highest =
			cpu_to_le16(MAX_BIT_RATE_SHORT_GI_1NSS_80MHZ_MCS9);
		vht_cap->vht_mcs.tx_mcs_map = cpu_to_le16(mcs_map);
		vht_cap->vht_mcs.tx_highest =
			cpu_to_le16(MAX_BIT_RATE_SHORT_GI_1NSS_80MHZ_MCS9);
	पूर्ण
पूर्ण

अटल व्योम _rtl_init_mac80211(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtlpriv);
	काष्ठा rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा ieee80211_supported_band *sband;

	अगर (rtlhal->macphymode == SINGLEMAC_SINGLEPHY &&
	    rtlhal->bandset == BAND_ON_BOTH) अणु
		/* 1: 2.4 G bands */
		/* <1> use  mac->bands as mem क्रम hw->wiphy->bands */
		sband = &(rtlmac->bands[NL80211_BAND_2GHZ]);

		/* <2> set hw->wiphy->bands[NL80211_BAND_2GHZ]
		 * to शेष value(1T1R) */
		स_नकल(&(rtlmac->bands[NL80211_BAND_2GHZ]), &rtl_band_2ghz,
				माप(काष्ठा ieee80211_supported_band));

		/* <3> init ht cap base on ant_num */
		_rtl_init_hw_ht_capab(hw, &sband->ht_cap);

		/* <4> set mac->sband to wiphy->sband */
		hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;

		/* 2: 5 G bands */
		/* <1> use  mac->bands as mem क्रम hw->wiphy->bands */
		sband = &(rtlmac->bands[NL80211_BAND_5GHZ]);

		/* <2> set hw->wiphy->bands[NL80211_BAND_5GHZ]
		 * to शेष value(1T1R) */
		स_नकल(&(rtlmac->bands[NL80211_BAND_5GHZ]), &rtl_band_5ghz,
				माप(काष्ठा ieee80211_supported_band));

		/* <3> init ht cap base on ant_num */
		_rtl_init_hw_ht_capab(hw, &sband->ht_cap);

		_rtl_init_hw_vht_capab(hw, &sband->vht_cap);
		/* <4> set mac->sband to wiphy->sband */
		hw->wiphy->bands[NL80211_BAND_5GHZ] = sband;
	पूर्ण अन्यथा अणु
		अगर (rtlhal->current_bandtype == BAND_ON_2_4G) अणु
			/* <1> use  mac->bands as mem क्रम hw->wiphy->bands */
			sband = &(rtlmac->bands[NL80211_BAND_2GHZ]);

			/* <2> set hw->wiphy->bands[NL80211_BAND_2GHZ]
			 * to शेष value(1T1R) */
			स_नकल(&(rtlmac->bands[NL80211_BAND_2GHZ]),
			       &rtl_band_2ghz,
			       माप(काष्ठा ieee80211_supported_band));

			/* <3> init ht cap base on ant_num */
			_rtl_init_hw_ht_capab(hw, &sband->ht_cap);

			/* <4> set mac->sband to wiphy->sband */
			hw->wiphy->bands[NL80211_BAND_2GHZ] = sband;
		पूर्ण अन्यथा अगर (rtlhal->current_bandtype == BAND_ON_5G) अणु
			/* <1> use  mac->bands as mem क्रम hw->wiphy->bands */
			sband = &(rtlmac->bands[NL80211_BAND_5GHZ]);

			/* <2> set hw->wiphy->bands[NL80211_BAND_5GHZ]
			 * to शेष value(1T1R) */
			स_नकल(&(rtlmac->bands[NL80211_BAND_5GHZ]),
			       &rtl_band_5ghz,
			       माप(काष्ठा ieee80211_supported_band));

			/* <3> init ht cap base on ant_num */
			_rtl_init_hw_ht_capab(hw, &sband->ht_cap);

			_rtl_init_hw_vht_capab(hw, &sband->vht_cap);
			/* <4> set mac->sband to wiphy->sband */
			hw->wiphy->bands[NL80211_BAND_5GHZ] = sband;
		पूर्ण अन्यथा अणु
			pr_err("Err BAND %d\n",
			       rtlhal->current_bandtype);
		पूर्ण
	पूर्ण
	/* <5> set hw caps */
	ieee80211_hw_set(hw, SIGNAL_DBM);
	ieee80211_hw_set(hw, RX_INCLUDES_FCS);
	ieee80211_hw_set(hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(hw, MFP_CAPABLE);
	ieee80211_hw_set(hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(hw, SUPPORTS_AMSDU_IN_AMPDU);
	ieee80211_hw_set(hw, SUPPORT_FAST_XMIT);

	/* swlps or hwlps has been set in dअगरf chip in init_sw_vars */
	अगर (rtlpriv->psc.swctrl_lps) अणु
		ieee80211_hw_set(hw, SUPPORTS_PS);
		ieee80211_hw_set(hw, PS_शून्यFUNC_STACK);
	पूर्ण
	अगर (rtlpriv->psc.fwctrl_lps) अणु
		ieee80211_hw_set(hw, SUPPORTS_PS);
		ieee80211_hw_set(hw, SUPPORTS_DYNAMIC_PS);
	पूर्ण
	hw->wiphy->पूर्णांकerface_modes =
	    BIT(NL80211_IFTYPE_AP) |
	    BIT(NL80211_IFTYPE_STATION) |
	    BIT(NL80211_IFTYPE_ADHOC) |
	    BIT(NL80211_IFTYPE_MESH_POINT) |
	    BIT(NL80211_IFTYPE_P2P_CLIENT) |
	    BIT(NL80211_IFTYPE_P2P_GO);
	hw->wiphy->flags |= WIPHY_FLAG_IBSS_RSN;

	hw->wiphy->flags |= WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL;

	hw->wiphy->rts_threshold = 2347;

	hw->queues = AC_MAX;
	hw->extra_tx_headroom = RTL_TX_HEADER_SIZE;

	/* TODO: Correct this value क्रम our hw */
	hw->max_listen_पूर्णांकerval = MAX_LISTEN_INTERVAL;
	hw->max_rate_tries = MAX_RATE_TRIES;
	/* hw->max_rates = 1; */
	hw->sta_data_size = माप(काष्ठा rtl_sta_info);

/* wowlan is not supported by kernel अगर CONFIG_PM is not defined */
#अगर_घोषित CONFIG_PM
	अगर (rtlpriv->psc.wo_wlan_mode) अणु
		अगर (rtlpriv->psc.wo_wlan_mode & WAKE_ON_MAGIC_PACKET)
			rtlpriv->wowlan.flags = WIPHY_WOWLAN_MAGIC_PKT;
		अगर (rtlpriv->psc.wo_wlan_mode & WAKE_ON_PATTERN_MATCH) अणु
			rtlpriv->wowlan.n_patterns =
				MAX_SUPPORT_WOL_PATTERN_NUM;
			rtlpriv->wowlan.pattern_min_len = MIN_WOL_PATTERN_SIZE;
			rtlpriv->wowlan.pattern_max_len = MAX_WOL_PATTERN_SIZE;
		पूर्ण
		hw->wiphy->wowlan = &rtlpriv->wowlan;
	पूर्ण
#पूर्ण_अगर

	/* <6> mac address */
	अगर (is_valid_ether_addr(rtlefuse->dev_addr)) अणु
		SET_IEEE80211_PERM_ADDR(hw, rtlefuse->dev_addr);
	पूर्ण अन्यथा अणु
		u8 rtlmac1[] = अणु 0x00, 0xe0, 0x4c, 0x81, 0x92, 0x00 पूर्ण;

		get_अक्रमom_bytes((rtlmac1 + (ETH_ALEN - 1)), 1);
		SET_IEEE80211_PERM_ADDR(hw, rtlmac1);
	पूर्ण
पूर्ण

अटल व्योम rtl_watchकरोg_wq_callback(काष्ठा work_काष्ठा *work);
अटल व्योम rtl_fwevt_wq_callback(काष्ठा work_काष्ठा *work);
अटल व्योम rtl_c2hcmd_wq_callback(काष्ठा work_काष्ठा *work);

अटल पूर्णांक _rtl_init_deferred_work(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा workqueue_काष्ठा *wq;

	wq = alloc_workqueue("%s", 0, 0, rtlpriv->cfg->name);
	अगर (!wq)
		वापस -ENOMEM;

	/* <1> समयr */
	समयr_setup(&rtlpriv->works.watchकरोg_समयr,
		    rtl_watch_करोg_समयr_callback, 0);
	समयr_setup(&rtlpriv->works.dualmac_easyconcurrent_retryसमयr,
		    rtl_easy_concurrent_retryसमयr_callback, 0);
	/* <2> work queue */
	rtlpriv->works.hw = hw;
	rtlpriv->works.rtl_wq = wq;

	INIT_DELAYED_WORK(&rtlpriv->works.watchकरोg_wq,
			  rtl_watchकरोg_wq_callback);
	INIT_DELAYED_WORK(&rtlpriv->works.ips_nic_off_wq,
			  rtl_ips_nic_off_wq_callback);
	INIT_DELAYED_WORK(&rtlpriv->works.ps_work, rtl_swlps_wq_callback);
	INIT_DELAYED_WORK(&rtlpriv->works.ps_rfon_wq,
			  rtl_swlps_rfon_wq_callback);
	INIT_DELAYED_WORK(&rtlpriv->works.fwevt_wq, rtl_fwevt_wq_callback);
	INIT_DELAYED_WORK(&rtlpriv->works.c2hcmd_wq, rtl_c2hcmd_wq_callback);
	वापस 0;
पूर्ण

व्योम rtl_deinit_deferred_work(काष्ठा ieee80211_hw *hw, bool ips_wq)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	del_समयr_sync(&rtlpriv->works.watchकरोg_समयr);

	cancel_delayed_work_sync(&rtlpriv->works.watchकरोg_wq);
	अगर (ips_wq)
		cancel_delayed_work(&rtlpriv->works.ips_nic_off_wq);
	अन्यथा
		cancel_delayed_work_sync(&rtlpriv->works.ips_nic_off_wq);
	cancel_delayed_work_sync(&rtlpriv->works.ps_work);
	cancel_delayed_work_sync(&rtlpriv->works.ps_rfon_wq);
	cancel_delayed_work_sync(&rtlpriv->works.fwevt_wq);
	cancel_delayed_work_sync(&rtlpriv->works.c2hcmd_wq);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_deinit_deferred_work);

व्योम rtl_init_rfसमाप्त(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	bool radio_state;
	bool blocked;
	u8 valid = 0;

	/*set init state to on */
	rtlpriv->rfसमाप्त.rfसमाप्त_state = true;
	wiphy_rfसमाप्त_set_hw_state(hw->wiphy, 0);

	radio_state = rtlpriv->cfg->ops->radio_onoff_checking(hw, &valid);

	अगर (valid) अणु
		pr_info("rtlwifi: wireless switch is %s\n",
			rtlpriv->rfसमाप्त.rfसमाप्त_state ? "on" : "off");

		rtlpriv->rfसमाप्त.rfसमाप्त_state = radio_state;

		blocked = rtlpriv->rfसमाप्त.rfसमाप्त_state != 1;
		wiphy_rfसमाप्त_set_hw_state(hw->wiphy, blocked);
	पूर्ण

	wiphy_rfसमाप्त_start_polling(hw->wiphy);
पूर्ण
EXPORT_SYMBOL(rtl_init_rfसमाप्त);

व्योम rtl_deinit_rfसमाप्त(काष्ठा ieee80211_hw *hw)
अणु
	wiphy_rfसमाप्त_stop_polling(hw->wiphy);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_deinit_rfसमाप्त);

पूर्णांक rtl_init_core(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));

	/* <1> init mac80211 */
	_rtl_init_mac80211(hw);
	rtlmac->hw = hw;

	/* <2> rate control रेजिस्टर */
	hw->rate_control_algorithm = "rtl_rc";

	/*
	 * <3> init CRDA must come after init
	 * mac80211 hw  in _rtl_init_mac80211.
	 */
	अगर (rtl_regd_init(hw, rtl_reg_notअगरier)) अणु
		pr_err("REGD init failed\n");
		वापस 1;
	पूर्ण

	/* <4> locks */
	mutex_init(&rtlpriv->locks.conf_mutex);
	mutex_init(&rtlpriv->locks.ips_mutex);
	mutex_init(&rtlpriv->locks.lps_mutex);
	spin_lock_init(&rtlpriv->locks.irq_th_lock);
	spin_lock_init(&rtlpriv->locks.h2c_lock);
	spin_lock_init(&rtlpriv->locks.rf_ps_lock);
	spin_lock_init(&rtlpriv->locks.rf_lock);
	spin_lock_init(&rtlpriv->locks.रुकोq_lock);
	spin_lock_init(&rtlpriv->locks.entry_list_lock);
	spin_lock_init(&rtlpriv->locks.scan_list_lock);
	spin_lock_init(&rtlpriv->locks.cck_and_rw_pagea_lock);
	spin_lock_init(&rtlpriv->locks.fw_ps_lock);
	spin_lock_init(&rtlpriv->locks.iqk_lock);
	/* <5> init list */
	INIT_LIST_HEAD(&rtlpriv->entry_list);
	INIT_LIST_HEAD(&rtlpriv->scan_list.list);
	skb_queue_head_init(&rtlpriv->tx_report.queue);
	skb_queue_head_init(&rtlpriv->c2hcmd_queue);

	rtlmac->link_state = MAC80211_NOLINK;

	/* <6> init deferred work */
	वापस _rtl_init_deferred_work(hw);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_init_core);

अटल व्योम rtl_मुक्त_entries_from_scan_list(काष्ठा ieee80211_hw *hw);
अटल व्योम rtl_मुक्त_entries_from_ack_queue(काष्ठा ieee80211_hw *hw,
					    bool समयout);

व्योम rtl_deinit_core(काष्ठा ieee80211_hw *hw)
अणु
	rtl_c2hcmd_launcher(hw, 0);
	rtl_मुक्त_entries_from_scan_list(hw);
	rtl_मुक्त_entries_from_ack_queue(hw, false);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_deinit_core);

व्योम rtl_init_rx_config(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	rtlpriv->cfg->ops->get_hw_reg(hw, HW_VAR_RCR, (u8 *) (&mac->rx_conf));
पूर्ण
EXPORT_SYMBOL_GPL(rtl_init_rx_config);

/*********************************************************
 *
 * tx inक्रमmation functions
 *
 *********************************************************/
अटल व्योम _rtl_qurey_लघुpreamble_mode(काष्ठा ieee80211_hw *hw,
					  काष्ठा rtl_tcb_desc *tcb_desc,
					  काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 rate_flag = info->control.rates[0].flags;

	tcb_desc->use_लघुpreamble = false;

	/* 1M can only use Long Preamble. 11B spec */
	अगर (tcb_desc->hw_rate == rtlpriv->cfg->maps[RTL_RC_CCK_RATE1M])
		वापस;
	अन्यथा अगर (rate_flag & IEEE80211_TX_RC_USE_SHORT_PREAMBLE)
		tcb_desc->use_लघुpreamble = true;

	वापस;
पूर्ण

अटल व्योम _rtl_query_लघुgi(काष्ठा ieee80211_hw *hw,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा rtl_tcb_desc *tcb_desc,
			       काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	u8 rate_flag = info->control.rates[0].flags;
	u8 sgi_40 = 0, sgi_20 = 0, bw_40 = 0;
	u8 sgi_80 = 0, bw_80 = 0;

	tcb_desc->use_लघुgi = false;

	अगर (sta == शून्य)
		वापस;

	sgi_40 = sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_40;
	sgi_20 = sta->ht_cap.cap & IEEE80211_HT_CAP_SGI_20;
	sgi_80 = sta->vht_cap.cap & IEEE80211_VHT_CAP_SHORT_GI_80;

	अगर ((!sta->ht_cap.ht_supported) && (!sta->vht_cap.vht_supported))
		वापस;

	अगर (!sgi_40 && !sgi_20)
		वापस;

	अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
		bw_40 = mac->bw_40;
		bw_80 = mac->bw_80;
	पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
		 mac->opmode == NL80211_IFTYPE_ADHOC ||
		 mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		bw_40 = sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40;
		bw_80 = sta->vht_cap.vht_supported;
	पूर्ण

	अगर (bw_80) अणु
		अगर (sgi_80)
			tcb_desc->use_लघुgi = true;
		अन्यथा
			tcb_desc->use_लघुgi = false;
	पूर्ण अन्यथा अणु
		अगर (bw_40 && sgi_40)
			tcb_desc->use_लघुgi = true;
		अन्यथा अगर (!bw_40 && sgi_20)
			tcb_desc->use_लघुgi = true;
	पूर्ण

	अगर (!(rate_flag & IEEE80211_TX_RC_SHORT_GI))
		tcb_desc->use_लघुgi = false;
पूर्ण

अटल व्योम _rtl_query_protection_mode(काष्ठा ieee80211_hw *hw,
				       काष्ठा rtl_tcb_desc *tcb_desc,
				       काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 rate_flag = info->control.rates[0].flags;

	/* Common Settings */
	tcb_desc->rts_stbc = false;
	tcb_desc->cts_enable = false;
	tcb_desc->rts_sc = 0;
	tcb_desc->rts_bw = false;
	tcb_desc->rts_use_लघुpreamble = false;
	tcb_desc->rts_use_लघुgi = false;

	अगर (rate_flag & IEEE80211_TX_RC_USE_CTS_PROTECT) अणु
		/* Use CTS-to-SELF in protection mode. */
		tcb_desc->rts_enable = true;
		tcb_desc->cts_enable = true;
		tcb_desc->rts_rate = rtlpriv->cfg->maps[RTL_RC_OFDM_RATE24M];
	पूर्ण अन्यथा अगर (rate_flag & IEEE80211_TX_RC_USE_RTS_CTS) अणु
		/* Use RTS-CTS in protection mode. */
		tcb_desc->rts_enable = true;
		tcb_desc->rts_rate = rtlpriv->cfg->maps[RTL_RC_OFDM_RATE24M];
	पूर्ण
पूर्ण

u8 rtl_mrate_idx_to_arfr_id(काष्ठा ieee80211_hw *hw, u8 rate_index,
			    क्रमागत wireless_mode wirelessmode)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 ret = 0;

	चयन (rate_index) अणु
	हाल RATR_INX_WIRELESS_NGB:
		अगर (rtlphy->rf_type == RF_1T1R)
			ret = RATEID_IDX_BGN_40M_1SS;
		अन्यथा
			ret = RATEID_IDX_BGN_40M_2SS;
		; अवरोध;
	हाल RATR_INX_WIRELESS_N:
	हाल RATR_INX_WIRELESS_NG:
		अगर (rtlphy->rf_type == RF_1T1R)
			ret = RATEID_IDX_GN_N1SS;
		अन्यथा
			ret = RATEID_IDX_GN_N2SS;
		; अवरोध;
	हाल RATR_INX_WIRELESS_NB:
		अगर (rtlphy->rf_type == RF_1T1R)
			ret = RATEID_IDX_BGN_20M_1SS_BN;
		अन्यथा
			ret = RATEID_IDX_BGN_20M_2SS_BN;
		; अवरोध;
	हाल RATR_INX_WIRELESS_GB:
		ret = RATEID_IDX_BG;
		अवरोध;
	हाल RATR_INX_WIRELESS_G:
		ret = RATEID_IDX_G;
		अवरोध;
	हाल RATR_INX_WIRELESS_B:
		ret = RATEID_IDX_B;
		अवरोध;
	हाल RATR_INX_WIRELESS_MC:
		अगर (wirelessmode == WIRELESS_MODE_B ||
		    wirelessmode == WIRELESS_MODE_G ||
		    wirelessmode == WIRELESS_MODE_N_24G ||
		    wirelessmode == WIRELESS_MODE_AC_24G)
			ret = RATEID_IDX_BG;
		अन्यथा
			ret = RATEID_IDX_G;
		अवरोध;
	हाल RATR_INX_WIRELESS_AC_5N:
		अगर (rtlphy->rf_type == RF_1T1R)
			ret = RATEID_IDX_VHT_1SS;
		अन्यथा
			ret = RATEID_IDX_VHT_2SS;
		अवरोध;
	हाल RATR_INX_WIRELESS_AC_24N:
		अगर (rtlphy->current_chan_bw == HT_CHANNEL_WIDTH_80) अणु
			अगर (rtlphy->rf_type == RF_1T1R)
				ret = RATEID_IDX_VHT_1SS;
			अन्यथा
				ret = RATEID_IDX_VHT_2SS;
		पूर्ण अन्यथा अणु
			अगर (rtlphy->rf_type == RF_1T1R)
				ret = RATEID_IDX_MIX1;
			अन्यथा
				ret = RATEID_IDX_MIX2;
		पूर्ण
		अवरोध;
	शेष:
		ret = RATEID_IDX_BGN_40M_2SS;
		अवरोध;
	पूर्ण
	वापस ret;
पूर्ण
EXPORT_SYMBOL(rtl_mrate_idx_to_arfr_id);

अटल व्योम _rtl_txrate_selecपंचांगode(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_sta *sta,
				   काष्ठा rtl_tcb_desc *tcb_desc)
अणु
#घोषणा SET_RATE_ID(rate_id)					\
	(अणुtypeof(rate_id) _id = rate_id;			\
	  ((rtlpriv->cfg->spec_ver & RTL_SPEC_NEW_RATEID) ?	\
		rtl_mrate_idx_to_arfr_id(hw, _id,		\
			(sta_entry ? sta_entry->wireless_mode :	\
			 WIRELESS_MODE_G)) :			\
		_id); पूर्ण)

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u8 ratr_index = SET_RATE_ID(RATR_INX_WIRELESS_MC);

	अगर (sta) अणु
		sta_entry = (काष्ठा rtl_sta_info *) sta->drv_priv;
		ratr_index = sta_entry->ratr_index;
	पूर्ण
	अगर (!tcb_desc->disable_ratefallback || !tcb_desc->use_driver_rate) अणु
		अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
			tcb_desc->ratr_index = 0;
		पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_ADHOC ||
				mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
			अगर (tcb_desc->multicast || tcb_desc->broadcast) अणु
				tcb_desc->hw_rate =
				    rtlpriv->cfg->maps[RTL_RC_CCK_RATE2M];
				tcb_desc->use_driver_rate = 1;
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_MC);
			पूर्ण अन्यथा अणु
				tcb_desc->ratr_index = ratr_index;
			पूर्ण
		पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP) अणु
			tcb_desc->ratr_index = ratr_index;
		पूर्ण
	पूर्ण

	अगर (rtlpriv->dm.useramask) अणु
		tcb_desc->ratr_index = ratr_index;
		/* TODO we will dअगरferentiate adhoc and station future  */
		अगर (mac->opmode == NL80211_IFTYPE_STATION ||
		    mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
			tcb_desc->mac_id = 0;

			अगर (sta &&
			    (rtlpriv->cfg->spec_ver & RTL_SPEC_NEW_RATEID))
				;	/* use sta_entry->ratr_index */
			अन्यथा अगर (mac->mode == WIRELESS_MODE_AC_5G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_AC_5N);
			अन्यथा अगर (mac->mode == WIRELESS_MODE_AC_24G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_AC_24N);
			अन्यथा अगर (mac->mode == WIRELESS_MODE_N_24G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_NGB);
			अन्यथा अगर (mac->mode == WIRELESS_MODE_N_5G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_NG);
			अन्यथा अगर (mac->mode & WIRELESS_MODE_G)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_GB);
			अन्यथा अगर (mac->mode & WIRELESS_MODE_B)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_B);
			अन्यथा अगर (mac->mode & WIRELESS_MODE_A)
				tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_G);

		पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_AP ||
			mac->opmode == NL80211_IFTYPE_ADHOC) अणु
			अगर (शून्य != sta) अणु
				अगर (sta->aid > 0)
					tcb_desc->mac_id = sta->aid + 1;
				अन्यथा
					tcb_desc->mac_id = 1;
			पूर्ण अन्यथा अणु
				tcb_desc->mac_id = 0;
			पूर्ण
		पूर्ण
	पूर्ण
#अघोषित SET_RATE_ID
पूर्ण

अटल व्योम _rtl_query_bandwidth_mode(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_sta *sta,
				      काष्ठा rtl_tcb_desc *tcb_desc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));

	tcb_desc->packet_bw = false;
	अगर (!sta)
		वापस;
	अगर (mac->opmode == NL80211_IFTYPE_AP ||
	    mac->opmode == NL80211_IFTYPE_ADHOC ||
	    mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
		अगर (!(sta->ht_cap.ht_supported) ||
		    !(sta->ht_cap.cap & IEEE80211_HT_CAP_SUP_WIDTH_20_40))
			वापस;
	पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
		अगर (!mac->bw_40 || !(sta->ht_cap.ht_supported))
			वापस;
	पूर्ण
	अगर (tcb_desc->multicast || tcb_desc->broadcast)
		वापस;

	/*use legency rate, shall use 20MHz */
	अगर (tcb_desc->hw_rate <= rtlpriv->cfg->maps[RTL_RC_OFDM_RATE54M])
		वापस;

	tcb_desc->packet_bw = HT_CHANNEL_WIDTH_20_40;

	अगर (rtlpriv->cfg->spec_ver & RTL_SPEC_SUPPORT_VHT) अणु
		अगर (mac->opmode == NL80211_IFTYPE_AP ||
		    mac->opmode == NL80211_IFTYPE_ADHOC ||
		    mac->opmode == NL80211_IFTYPE_MESH_POINT) अणु
			अगर (!(sta->vht_cap.vht_supported))
				वापस;
		पूर्ण अन्यथा अगर (mac->opmode == NL80211_IFTYPE_STATION) अणु
			अगर (!mac->bw_80 ||
			    !(sta->vht_cap.vht_supported))
				वापस;
		पूर्ण
		अगर (tcb_desc->hw_rate <=
			rtlpriv->cfg->maps[RTL_RC_HT_RATEMCS15])
			वापस;
		tcb_desc->packet_bw = HT_CHANNEL_WIDTH_80;
	पूर्ण
पूर्ण

अटल u8 _rtl_get_vht_highest_n_rate(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &(rtlpriv->phy);
	u8 hw_rate;
	u16 tx_mcs_map = le16_to_cpu(sta->vht_cap.vht_mcs.tx_mcs_map);

	अगर ((get_rf_type(rtlphy) == RF_2T2R) &&
	    (tx_mcs_map & 0x000c) != 0x000c) अणु
		अगर ((tx_mcs_map & 0x000c) >> 2 ==
			IEEE80211_VHT_MCS_SUPPORT_0_7)
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_2SS_MCS7];
		अन्यथा अगर ((tx_mcs_map  & 0x000c) >> 2 ==
			IEEE80211_VHT_MCS_SUPPORT_0_8)
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_2SS_MCS8];
		अन्यथा
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_2SS_MCS9];
	पूर्ण अन्यथा अणु
		अगर ((tx_mcs_map  & 0x0003) ==
			IEEE80211_VHT_MCS_SUPPORT_0_7)
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS7];
		अन्यथा अगर ((tx_mcs_map  & 0x0003) ==
			IEEE80211_VHT_MCS_SUPPORT_0_8)
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS8];
		अन्यथा
			hw_rate =
			rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS9];
	पूर्ण

	वापस hw_rate;
पूर्ण

अटल u8 _rtl_get_highest_n_rate(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_phy *rtlphy = &rtlpriv->phy;
	u8 hw_rate;

	अगर (get_rf_type(rtlphy) == RF_2T2R &&
	    sta->ht_cap.mcs.rx_mask[1] != 0)
		hw_rate = rtlpriv->cfg->maps[RTL_RC_HT_RATEMCS15];
	अन्यथा
		hw_rate = rtlpriv->cfg->maps[RTL_RC_HT_RATEMCS7];

	वापस hw_rate;
पूर्ण

/* mac80211's rate_idx is like this:
 *
 * 2.4G band:rx_status->band == NL80211_BAND_2GHZ
 *
 * B/G rate:
 * (rx_status->flag & RX_FLAG_HT) = 0,
 * DESC_RATE1M-->DESC_RATE54M ==> idx is 0-->11,
 *
 * N rate:
 * (rx_status->flag & RX_FLAG_HT) = 1,
 * DESC_RATEMCS0-->DESC_RATEMCS15 ==> idx is 0-->15
 *
 * 5G band:rx_status->band == NL80211_BAND_5GHZ
 * A rate:
 * (rx_status->flag & RX_FLAG_HT) = 0,
 * DESC_RATE6M-->DESC_RATE54M ==> idx is 0-->7,
 *
 * N rate:
 * (rx_status->flag & RX_FLAG_HT) = 1,
 * DESC_RATEMCS0-->DESC_RATEMCS15 ==> idx is 0-->15
 *
 * VHT rates:
 * DESC_RATEVHT1SS_MCS0-->DESC_RATEVHT1SS_MCS9 ==> idx is 0-->9
 * DESC_RATEVHT2SS_MCS0-->DESC_RATEVHT2SS_MCS9 ==> idx is 0-->9
 */
पूर्णांक rtlwअगरi_rate_mapping(काष्ठा ieee80211_hw *hw, bool isht, bool isvht,
			 u8 desc_rate)
अणु
	पूर्णांक rate_idx;

	अगर (isvht) अणु
		चयन (desc_rate) अणु
		हाल DESC_RATEVHT1SS_MCS0:
			rate_idx = 0;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS1:
			rate_idx = 1;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS2:
			rate_idx = 2;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS3:
			rate_idx = 3;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS4:
			rate_idx = 4;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS5:
			rate_idx = 5;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS6:
			rate_idx = 6;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS7:
			rate_idx = 7;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS8:
			rate_idx = 8;
			अवरोध;
		हाल DESC_RATEVHT1SS_MCS9:
			rate_idx = 9;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS0:
			rate_idx = 0;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS1:
			rate_idx = 1;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS2:
			rate_idx = 2;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS3:
			rate_idx = 3;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS4:
			rate_idx = 4;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS5:
			rate_idx = 5;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS6:
			rate_idx = 6;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS7:
			rate_idx = 7;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS8:
			rate_idx = 8;
			अवरोध;
		हाल DESC_RATEVHT2SS_MCS9:
			rate_idx = 9;
			अवरोध;
		शेष:
			rate_idx = 0;
			अवरोध;
		पूर्ण
		वापस rate_idx;
	पूर्ण
	अगर (false == isht) अणु
		अगर (NL80211_BAND_2GHZ == hw->conf.chandef.chan->band) अणु
			चयन (desc_rate) अणु
			हाल DESC_RATE1M:
				rate_idx = 0;
				अवरोध;
			हाल DESC_RATE2M:
				rate_idx = 1;
				अवरोध;
			हाल DESC_RATE5_5M:
				rate_idx = 2;
				अवरोध;
			हाल DESC_RATE11M:
				rate_idx = 3;
				अवरोध;
			हाल DESC_RATE6M:
				rate_idx = 4;
				अवरोध;
			हाल DESC_RATE9M:
				rate_idx = 5;
				अवरोध;
			हाल DESC_RATE12M:
				rate_idx = 6;
				अवरोध;
			हाल DESC_RATE18M:
				rate_idx = 7;
				अवरोध;
			हाल DESC_RATE24M:
				rate_idx = 8;
				अवरोध;
			हाल DESC_RATE36M:
				rate_idx = 9;
				अवरोध;
			हाल DESC_RATE48M:
				rate_idx = 10;
				अवरोध;
			हाल DESC_RATE54M:
				rate_idx = 11;
				अवरोध;
			शेष:
				rate_idx = 0;
				अवरोध;
			पूर्ण
		पूर्ण अन्यथा अणु
			चयन (desc_rate) अणु
			हाल DESC_RATE6M:
				rate_idx = 0;
				अवरोध;
			हाल DESC_RATE9M:
				rate_idx = 1;
				अवरोध;
			हाल DESC_RATE12M:
				rate_idx = 2;
				अवरोध;
			हाल DESC_RATE18M:
				rate_idx = 3;
				अवरोध;
			हाल DESC_RATE24M:
				rate_idx = 4;
				अवरोध;
			हाल DESC_RATE36M:
				rate_idx = 5;
				अवरोध;
			हाल DESC_RATE48M:
				rate_idx = 6;
				अवरोध;
			हाल DESC_RATE54M:
				rate_idx = 7;
				अवरोध;
			शेष:
				rate_idx = 0;
				अवरोध;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (desc_rate) अणु
		हाल DESC_RATEMCS0:
			rate_idx = 0;
			अवरोध;
		हाल DESC_RATEMCS1:
			rate_idx = 1;
			अवरोध;
		हाल DESC_RATEMCS2:
			rate_idx = 2;
			अवरोध;
		हाल DESC_RATEMCS3:
			rate_idx = 3;
			अवरोध;
		हाल DESC_RATEMCS4:
			rate_idx = 4;
			अवरोध;
		हाल DESC_RATEMCS5:
			rate_idx = 5;
			अवरोध;
		हाल DESC_RATEMCS6:
			rate_idx = 6;
			अवरोध;
		हाल DESC_RATEMCS7:
			rate_idx = 7;
			अवरोध;
		हाल DESC_RATEMCS8:
			rate_idx = 8;
			अवरोध;
		हाल DESC_RATEMCS9:
			rate_idx = 9;
			अवरोध;
		हाल DESC_RATEMCS10:
			rate_idx = 10;
			अवरोध;
		हाल DESC_RATEMCS11:
			rate_idx = 11;
			अवरोध;
		हाल DESC_RATEMCS12:
			rate_idx = 12;
			अवरोध;
		हाल DESC_RATEMCS13:
			rate_idx = 13;
			अवरोध;
		हाल DESC_RATEMCS14:
			rate_idx = 14;
			अवरोध;
		हाल DESC_RATEMCS15:
			rate_idx = 15;
			अवरोध;
		शेष:
			rate_idx = 0;
			अवरोध;
		पूर्ण
	पूर्ण
	वापस rate_idx;
पूर्ण
EXPORT_SYMBOL(rtlwअगरi_rate_mapping);

अटल u8 _rtl_get_tx_hw_rate(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_tx_info *info)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_tx_rate *r = &info->status.rates[0];
	काष्ठा ieee80211_rate *txrate;
	u8 hw_value = 0x0;

	अगर (r->flags & IEEE80211_TX_RC_MCS) अणु
		/* HT MCS0-15 */
		hw_value = rtlpriv->cfg->maps[RTL_RC_HT_RATEMCS15] - 15 +
			   r->idx;
	पूर्ण अन्यथा अगर (r->flags & IEEE80211_TX_RC_VHT_MCS) अणु
		/* VHT MCS0-9, NSS */
		अगर (ieee80211_rate_get_vht_nss(r) == 2)
			hw_value = rtlpriv->cfg->maps[RTL_RC_VHT_RATE_2SS_MCS9];
		अन्यथा
			hw_value = rtlpriv->cfg->maps[RTL_RC_VHT_RATE_1SS_MCS9];

		hw_value = hw_value - 9 + ieee80211_rate_get_vht_mcs(r);
	पूर्ण अन्यथा अणु
		/* legacy */
		txrate = ieee80211_get_tx_rate(hw, info);

		अगर (txrate)
			hw_value = txrate->hw_value;
	पूर्ण

	/* check 5G band */
	अगर (rtlpriv->rtlhal.current_bandtype == BAND_ON_5G &&
	    hw_value < rtlpriv->cfg->maps[RTL_RC_OFDM_RATE6M])
		hw_value = rtlpriv->cfg->maps[RTL_RC_OFDM_RATE6M];

	वापस hw_value;
पूर्ण

व्योम rtl_get_tcb_desc(काष्ठा ieee80211_hw *hw,
		      काष्ठा ieee80211_tx_info *info,
		      काष्ठा ieee80211_sta *sta,
		      काष्ठा sk_buff *skb, काष्ठा rtl_tcb_desc *tcb_desc)
अणु
#घोषणा SET_RATE_ID(rate_id)					\
	(अणुtypeof(rate_id) _id = rate_id;			\
	  ((rtlpriv->cfg->spec_ver & RTL_SPEC_NEW_RATEID) ?	\
		rtl_mrate_idx_to_arfr_id(hw, _id,		\
			(sta_entry ? sta_entry->wireless_mode :	\
			 WIRELESS_MODE_G)) :			\
		_id); पूर्ण)

	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *rtlmac = rtl_mac(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr = rtl_get_hdr(skb);
	काष्ठा rtl_sta_info *sta_entry =
		(sta ? (काष्ठा rtl_sta_info *)sta->drv_priv : शून्य);

	__le16 fc = rtl_get_fc(skb);

	tcb_desc->hw_rate = _rtl_get_tx_hw_rate(hw, info);

	अगर (rtl_is_tx_report_skb(hw, skb))
		tcb_desc->use_spe_rpt = 1;

	अगर (ieee80211_is_data(fc)) अणु
		/*
		 *we set data rate INX 0
		 *in rtl_rc.c   अगर skb is special data or
		 *mgt which need low data rate.
		 */

		/*
		 *So tcb_desc->hw_rate is just used क्रम
		 *special data and mgt frames
		 */
		अगर (info->control.rates[0].idx == 0 ||
				ieee80211_is_nullfunc(fc)) अणु
			tcb_desc->use_driver_rate = true;
			tcb_desc->ratr_index =
					SET_RATE_ID(RATR_INX_WIRELESS_MC);

			tcb_desc->disable_ratefallback = 1;
		पूर्ण अन्यथा अणु
			/*
			 *because hw will nerver use hw_rate
			 *when tcb_desc->use_driver_rate = false
			 *so we never set highest N rate here,
			 *and N rate will all be controlled by FW
			 *when tcb_desc->use_driver_rate = false
			 */
			अगर (sta && sta->vht_cap.vht_supported) अणु
				tcb_desc->hw_rate =
				_rtl_get_vht_highest_n_rate(hw, sta);
			पूर्ण अन्यथा अणु
				अगर (sta && sta->ht_cap.ht_supported) अणु
					tcb_desc->hw_rate =
						_rtl_get_highest_n_rate(hw, sta);
				पूर्ण अन्यथा अणु
					अगर (rtlmac->mode == WIRELESS_MODE_B) अणु
						tcb_desc->hw_rate =
						    rtlpriv->cfg->maps[RTL_RC_CCK_RATE11M];
					पूर्ण अन्यथा अणु
						tcb_desc->hw_rate =
						    rtlpriv->cfg->maps[RTL_RC_OFDM_RATE54M];
					पूर्ण
				पूर्ण
			पूर्ण
		पूर्ण

		अगर (is_multicast_ether_addr(hdr->addr1))
			tcb_desc->multicast = 1;
		अन्यथा अगर (is_broadcast_ether_addr(hdr->addr1))
			tcb_desc->broadcast = 1;

		_rtl_txrate_selecपंचांगode(hw, sta, tcb_desc);
		_rtl_query_bandwidth_mode(hw, sta, tcb_desc);
		_rtl_qurey_लघुpreamble_mode(hw, tcb_desc, info);
		_rtl_query_लघुgi(hw, sta, tcb_desc, info);
		_rtl_query_protection_mode(hw, tcb_desc, info);
	पूर्ण अन्यथा अणु
		tcb_desc->use_driver_rate = true;
		tcb_desc->ratr_index = SET_RATE_ID(RATR_INX_WIRELESS_MC);
		tcb_desc->disable_ratefallback = 1;
		tcb_desc->mac_id = 0;
		tcb_desc->packet_bw = false;
	पूर्ण
#अघोषित SET_RATE_ID
पूर्ण
EXPORT_SYMBOL(rtl_get_tcb_desc);

bool rtl_tx_mgmt_proc(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	__le16 fc = rtl_get_fc(skb);

	अगर (rtlpriv->dm.supp_phymode_चयन &&
	    mac->link_state < MAC80211_LINKED &&
	    (ieee80211_is_auth(fc) || ieee80211_is_probe_req(fc))) अणु
		अगर (rtlpriv->cfg->ops->chk_चयन_dmdp)
			rtlpriv->cfg->ops->chk_चयन_dmdp(hw);
	पूर्ण
	अगर (ieee80211_is_auth(fc)) अणु
		rtl_dbg(rtlpriv, COMP_SEND, DBG_DMESG, "MAC80211_LINKING\n");

		mac->link_state = MAC80211_LINKING;
		/* Dul mac */
		rtlpriv->phy.need_iqk = true;

	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_tx_mgmt_proc);

काष्ठा sk_buff *rtl_make_del_ba(काष्ठा ieee80211_hw *hw, u8 *sa,
				u8 *bssid, u16 tid);

अटल व्योम process_agg_start(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_hdr *hdr, u16 tid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_rx_status rx_status = अणु 0 पूर्ण;
	काष्ठा sk_buff *skb_delba = शून्य;

	skb_delba = rtl_make_del_ba(hw, hdr->addr2, hdr->addr3, tid);
	अगर (skb_delba) अणु
		rx_status.freq = hw->conf.chandef.chan->center_freq;
		rx_status.band = hw->conf.chandef.chan->band;
		rx_status.flag |= RX_FLAG_DECRYPTED;
		rx_status.flag |= RX_FLAG_MACTIME_START;
		rx_status.rate_idx = 0;
		rx_status.संकेत = 50 + 10;
		स_नकल(IEEE80211_SKB_RXCB(skb_delba),
		       &rx_status, माप(rx_status));
		RT_PRINT_DATA(rtlpriv, COMP_INIT, DBG_DMESG,
			      "fake del\n",
			      skb_delba->data,
			      skb_delba->len);
		ieee80211_rx_irqsafe(hw, skb_delba);
	पूर्ण
पूर्ण

bool rtl_action_proc(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb, u8 is_tx)
अणु
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr = rtl_get_hdr(skb);
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	__le16 fc = rtl_get_fc(skb);
	u8 *act = (u8 *)(((u8 *)skb->data + MAC80211_3ADDR_LEN));
	u8 category;

	अगर (!ieee80211_is_action(fc))
		वापस true;

	category = *act;
	act++;
	चयन (category) अणु
	हाल ACT_CAT_BA:
		चयन (*act) अणु
		हाल ACT_ADDBAREQ:
			अगर (mac->act_scanning)
				वापस false;

			rtl_dbg(rtlpriv, (COMP_SEND | COMP_RECV), DBG_DMESG,
				"%s ACT_ADDBAREQ From :%pM\n",
				is_tx ? "Tx" : "Rx", hdr->addr2);
			RT_PRINT_DATA(rtlpriv, COMP_INIT, DBG_DMESG, "req\n",
				skb->data, skb->len);
			अगर (!is_tx) अणु
				काष्ठा ieee80211_sta *sta = शून्य;
				काष्ठा rtl_sta_info *sta_entry = शून्य;
				काष्ठा rtl_tid_data *tid_data;
				काष्ठा ieee80211_mgmt *mgmt = (व्योम *)skb->data;
				u16 capab = 0, tid = 0;

				rcu_पढ़ो_lock();
				sta = rtl_find_sta(hw, hdr->addr3);
				अगर (sta == शून्य) अणु
					rtl_dbg(rtlpriv, COMP_SEND | COMP_RECV,
						DBG_DMESG, "sta is NULL\n");
					rcu_पढ़ो_unlock();
					वापस true;
				पूर्ण

				sta_entry =
					(काष्ठा rtl_sta_info *)sta->drv_priv;
				अगर (!sta_entry) अणु
					rcu_पढ़ो_unlock();
					वापस true;
				पूर्ण
				capab =
				  le16_to_cpu(mgmt->u.action.u.addba_req.capab);
				tid = (capab &
				       IEEE80211_ADDBA_PARAM_TID_MASK) >> 2;
				अगर (tid >= MAX_TID_COUNT) अणु
					rcu_पढ़ो_unlock();
					वापस true;
				पूर्ण
				tid_data = &sta_entry->tids[tid];
				अगर (tid_data->agg.rx_agg_state ==
				    RTL_RX_AGG_START)
					process_agg_start(hw, hdr, tid);
				rcu_पढ़ो_unlock();
			पूर्ण
			अवरोध;
		हाल ACT_ADDBARSP:
			rtl_dbg(rtlpriv, (COMP_SEND | COMP_RECV), DBG_DMESG,
				"%s ACT_ADDBARSP From :%pM\n",
				is_tx ? "Tx" : "Rx", hdr->addr2);
			अवरोध;
		हाल ACT_DELBA:
			rtl_dbg(rtlpriv, (COMP_SEND | COMP_RECV), DBG_DMESG,
				"ACT_ADDBADEL From :%pM\n", hdr->addr2);
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	वापस true;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_action_proc);

अटल व्योम setup_special_tx(काष्ठा rtl_priv *rtlpriv, काष्ठा rtl_ps_ctl *ppsc,
			     पूर्णांक type)
अणु
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;

	rtlpriv->ra.is_special_data = true;
	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_special_packet_notअगरy(
					rtlpriv, type);
	rtl_lps_leave(hw, false);
	ppsc->last_delaylps_stamp_jअगरfies = jअगरfies;
पूर्ण

अटल स्थिर u8 *rtl_skb_ether_type_ptr(काष्ठा ieee80211_hw *hw,
					काष्ठा sk_buff *skb, bool is_enc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	u8 mac_hdr_len = ieee80211_get_hdrlen_from_skb(skb);
	u8 encrypt_header_len = 0;
	u8 offset;

	चयन (rtlpriv->sec.pairwise_enc_algorithm) अणु
	हाल WEP40_ENCRYPTION:
	हाल WEP104_ENCRYPTION:
		encrypt_header_len = 4;/*WEP_IV_LEN*/
		अवरोध;
	हाल TKIP_ENCRYPTION:
		encrypt_header_len = 8;/*TKIP_IV_LEN*/
		अवरोध;
	हाल AESCCMP_ENCRYPTION:
		encrypt_header_len = 8;/*CCMP_HDR_LEN;*/
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	offset = mac_hdr_len + SNAP_SIZE;
	अगर (is_enc)
		offset += encrypt_header_len;

	वापस skb->data + offset;
पूर्ण

/*should call beक्रमe software enc*/
u8 rtl_is_special_data(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb, u8 is_tx,
		       bool is_enc)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	__le16 fc = rtl_get_fc(skb);
	u16 ether_type;
	स्थिर u8 *ether_type_ptr;
	स्थिर काष्ठा iphdr *ip;

	अगर (!ieee80211_is_data(fc))
		जाओ end;

	ether_type_ptr = rtl_skb_ether_type_ptr(hw, skb, is_enc);
	ether_type = be16_to_cpup((__be16 *)ether_type_ptr);

	अगर (ETH_P_IP == ether_type) अणु
		ip = (काष्ठा iphdr *)((u8 *)ether_type_ptr +
		     PROTOC_TYPE_SIZE);
		अगर (IPPROTO_UDP == ip->protocol) अणु
			काष्ठा udphdr *udp = (काष्ठा udphdr *)((u8 *)ip +
							       (ip->ihl << 2));
			अगर (((((u8 *)udp)[1] == 68) &&
			     (((u8 *)udp)[3] == 67)) ||
			    ((((u8 *)udp)[1] == 67) &&
			     (((u8 *)udp)[3] == 68))) अणु
				/* 68 : UDP BOOTP client
				 * 67 : UDP BOOTP server
				 */
				rtl_dbg(rtlpriv, (COMP_SEND | COMP_RECV),
					DBG_DMESG, "dhcp %s !!\n",
					(is_tx) ? "Tx" : "Rx");

				अगर (is_tx)
					setup_special_tx(rtlpriv, ppsc,
							 PACKET_DHCP);

				वापस true;
			पूर्ण
		पूर्ण
	पूर्ण अन्यथा अगर (ETH_P_ARP == ether_type) अणु
		अगर (is_tx)
			setup_special_tx(rtlpriv, ppsc, PACKET_ARP);

		वापस true;
	पूर्ण अन्यथा अगर (ETH_P_PAE == ether_type) अणु
		/* EAPOL is seens as in-4way */
		rtlpriv->btcoexist.btc_info.in_4way = true;
		rtlpriv->btcoexist.btc_info.in_4way_ts = jअगरfies;

		rtl_dbg(rtlpriv, (COMP_SEND | COMP_RECV), DBG_DMESG,
			"802.1X %s EAPOL pkt!!\n", (is_tx) ? "Tx" : "Rx");

		अगर (is_tx) अणु
			rtlpriv->ra.is_special_data = true;
			rtl_lps_leave(hw, false);
			ppsc->last_delaylps_stamp_jअगरfies = jअगरfies;

			setup_special_tx(rtlpriv, ppsc, PACKET_EAPOL);
		पूर्ण

		वापस true;
	पूर्ण अन्यथा अगर (ETH_P_IPV6 == ether_type) अणु
		/* TODO: Handle any IPv6 हालs that need special handling.
		 * For now, always वापस false
		 */
		जाओ end;
	पूर्ण

end:
	rtlpriv->ra.is_special_data = false;
	वापस false;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_is_special_data);

व्योम rtl_tx_ackqueue(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_tx_report *tx_report = &rtlpriv->tx_report;

	__skb_queue_tail(&tx_report->queue, skb);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_tx_ackqueue);

अटल व्योम rtl_tx_status(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb,
			  bool ack)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_tx_info *info;

	info = IEEE80211_SKB_CB(skb);
	ieee80211_tx_info_clear_status(info);
	अगर (ack) अणु
		rtl_dbg(rtlpriv, COMP_TX_REPORT, DBG_LOUD,
			"tx report: ack\n");
		info->flags |= IEEE80211_TX_STAT_ACK;
	पूर्ण अन्यथा अणु
		rtl_dbg(rtlpriv, COMP_TX_REPORT, DBG_LOUD,
			"tx report: not ack\n");
		info->flags &= ~IEEE80211_TX_STAT_ACK;
	पूर्ण
	ieee80211_tx_status_irqsafe(hw, skb);
पूर्ण

bool rtl_is_tx_report_skb(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	u16 ether_type;
	स्थिर u8 *ether_type_ptr;
	__le16 fc = rtl_get_fc(skb);

	ether_type_ptr = rtl_skb_ether_type_ptr(hw, skb, true);
	ether_type = be16_to_cpup((__be16 *)ether_type_ptr);

	अगर (ether_type == ETH_P_PAE || ieee80211_is_nullfunc(fc))
		वापस true;

	वापस false;
पूर्ण

अटल u16 rtl_get_tx_report_sn(काष्ठा ieee80211_hw *hw,
				काष्ठा rtlwअगरi_tx_info *tx_info)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_tx_report *tx_report = &rtlpriv->tx_report;
	u16 sn;

	/* SW_DEFINE[11:8] are reserved (driver fills zeros)
	 * SW_DEFINE[7:2] are used by driver
	 * SW_DEFINE[1:0] are reserved क्रम firmware (driver fills zeros)
	 */
	sn = (atomic_inc_वापस(&tx_report->sn) & 0x003F) << 2;

	tx_report->last_sent_sn = sn;
	tx_report->last_sent_समय = jअगरfies;
	tx_info->sn = sn;
	tx_info->send_समय = tx_report->last_sent_समय;
	rtl_dbg(rtlpriv, COMP_TX_REPORT, DBG_DMESG,
		"Send TX-Report sn=0x%X\n", sn);

	वापस sn;
पूर्ण

व्योम rtl_set_tx_report(काष्ठा rtl_tcb_desc *ptcb_desc, u8 *pdesc,
		       काष्ठा ieee80211_hw *hw, काष्ठा rtlwअगरi_tx_info *tx_info)
अणु
	अगर (ptcb_desc->use_spe_rpt) अणु
		u16 sn = rtl_get_tx_report_sn(hw, tx_info);

		SET_TX_DESC_SPE_RPT(pdesc, 1);
		SET_TX_DESC_SW_DEFINE(pdesc, sn);
	पूर्ण
पूर्ण
EXPORT_SYMBOL_GPL(rtl_set_tx_report);

व्योम rtl_tx_report_handler(काष्ठा ieee80211_hw *hw, u8 *पंचांगp_buf, u8 c2h_cmd_len)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_tx_report *tx_report = &rtlpriv->tx_report;
	काष्ठा rtlwअगरi_tx_info *tx_info;
	काष्ठा sk_buff_head *queue = &tx_report->queue;
	काष्ठा sk_buff *skb;
	u16 sn;
	u8 st, retry;

	अगर (rtlpriv->cfg->spec_ver & RTL_SPEC_EXT_C2H) अणु
		sn = GET_TX_REPORT_SN_V2(पंचांगp_buf);
		st = GET_TX_REPORT_ST_V2(पंचांगp_buf);
		retry = GET_TX_REPORT_RETRY_V2(पंचांगp_buf);
	पूर्ण अन्यथा अणु
		sn = GET_TX_REPORT_SN_V1(पंचांगp_buf);
		st = GET_TX_REPORT_ST_V1(पंचांगp_buf);
		retry = GET_TX_REPORT_RETRY_V1(पंचांगp_buf);
	पूर्ण

	tx_report->last_recv_sn = sn;

	skb_queue_walk(queue, skb) अणु
		tx_info = rtl_tx_skb_cb_info(skb);
		अगर (tx_info->sn == sn) अणु
			skb_unlink(skb, queue);
			rtl_tx_status(hw, skb, st == 0);
			अवरोध;
		पूर्ण
	पूर्ण
	rtl_dbg(rtlpriv, COMP_TX_REPORT, DBG_DMESG,
		"Recv TX-Report st=0x%02X sn=0x%X retry=0x%X\n",
		st, sn, retry);
पूर्ण
EXPORT_SYMBOL_GPL(rtl_tx_report_handler);

bool rtl_check_tx_report_acked(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_tx_report *tx_report = &rtlpriv->tx_report;

	अगर (tx_report->last_sent_sn == tx_report->last_recv_sn)
		वापस true;

	अगर (समय_beक्रमe(tx_report->last_sent_समय + 3 * HZ, jअगरfies)) अणु
		rtl_dbg(rtlpriv, COMP_TX_REPORT, DBG_WARNING,
			"Check TX-Report timeout!! s_sn=0x%X r_sn=0x%X\n",
			tx_report->last_sent_sn, tx_report->last_recv_sn);
		वापस true;	/* 3 sec. (समयout) seen as acked */
	पूर्ण

	वापस false;
पूर्ण

व्योम rtl_रुको_tx_report_acked(काष्ठा ieee80211_hw *hw, u32 रुको_ms)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	पूर्णांक i;

	क्रम (i = 0; i < रुको_ms; i++) अणु
		अगर (rtl_check_tx_report_acked(hw))
			अवरोध;
		usleep_range(1000, 2000);
		rtl_dbg(rtlpriv, COMP_SEC, DBG_DMESG,
			"Wait 1ms (%d/%d) to disable key.\n", i, रुको_ms);
	पूर्ण
पूर्ण

u32 rtl_get_hal_edca_param(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर,
			   क्रमागत wireless_mode wirelessmode,
			   काष्ठा ieee80211_tx_queue_params *param)
अणु
	u32 reg = 0;
	u8 sअगरsसमय = 10;
	u8 slotसमय = 20;

	/* AIFS = AIFSN * slot समय + SIFS */
	चयन (wirelessmode) अणु
	हाल WIRELESS_MODE_A:
	हाल WIRELESS_MODE_N_24G:
	हाल WIRELESS_MODE_N_5G:
	हाल WIRELESS_MODE_AC_5G:
	हाल WIRELESS_MODE_AC_24G:
		sअगरsसमय = 16;
		slotसमय = 9;
		अवरोध;
	हाल WIRELESS_MODE_G:
		slotसमय = (vअगर->bss_conf.use_लघु_slot ? 9 : 20);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

	reg |= (param->txop & 0x7FF) << 16;
	reg |= (fls(param->cw_max) & 0xF) << 12;
	reg |= (fls(param->cw_min) & 0xF) << 8;
	reg |= (param->aअगरs & 0x0F) * slotसमय + sअगरsसमय;

	वापस reg;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_get_hal_edca_param);

/*********************************************************
 *
 * functions called by core.c
 *
 *********************************************************/
पूर्णांक rtl_tx_agg_start(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		     काष्ठा ieee80211_sta *sta, u16 tid, u16 *ssn)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_tid_data *tid_data;
	काष्ठा rtl_sta_info *sta_entry = शून्य;

	अगर (sta == शून्य)
		वापस -EINVAL;

	अगर (unlikely(tid >= MAX_TID_COUNT))
		वापस -EINVAL;

	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
	अगर (!sta_entry)
		वापस -ENXIO;
	tid_data = &sta_entry->tids[tid];

	rtl_dbg(rtlpriv, COMP_SEND, DBG_DMESG,
		"on ra = %pM tid = %d seq:%d\n", sta->addr, tid,
		*ssn);

	tid_data->agg.agg_state = RTL_AGG_START;

	वापस IEEE80211_AMPDU_TX_START_IMMEDIATE;
पूर्ण

पूर्णांक rtl_tx_agg_stop(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_sta_info *sta_entry = शून्य;

	अगर (sta == शून्य)
		वापस -EINVAL;

	rtl_dbg(rtlpriv, COMP_SEND, DBG_DMESG,
		"on ra = %pM tid = %d\n", sta->addr, tid);

	अगर (unlikely(tid >= MAX_TID_COUNT))
		वापस -EINVAL;

	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
	sta_entry->tids[tid].agg.agg_state = RTL_AGG_STOP;

	ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
	वापस 0;
पूर्ण

पूर्णांक rtl_rx_agg_start(काष्ठा ieee80211_hw *hw,
		     काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_tid_data *tid_data;
	काष्ठा rtl_sta_info *sta_entry = शून्य;
	u8 reject_agg;

	अगर (sta == शून्य)
		वापस -EINVAL;

	अगर (unlikely(tid >= MAX_TID_COUNT))
		वापस -EINVAL;

	अगर (rtlpriv->cfg->ops->get_btc_status()) अणु
		rtlpriv->btcoexist.btc_ops->btc_get_ampdu_cfg(rtlpriv,
							      &reject_agg,
							      शून्य, शून्य);
		अगर (reject_agg)
			वापस -EINVAL;
	पूर्ण

	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
	अगर (!sta_entry)
		वापस -ENXIO;
	tid_data = &sta_entry->tids[tid];

	rtl_dbg(rtlpriv, COMP_RECV, DBG_DMESG,
		"on ra = %pM tid = %d\n", sta->addr, tid);

	tid_data->agg.rx_agg_state = RTL_RX_AGG_START;
	वापस 0;
पूर्ण

पूर्णांक rtl_rx_agg_stop(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_sta_info *sta_entry = शून्य;

	अगर (sta == शून्य)
		वापस -EINVAL;

	rtl_dbg(rtlpriv, COMP_SEND, DBG_DMESG,
		"on ra = %pM tid = %d\n", sta->addr, tid);

	अगर (unlikely(tid >= MAX_TID_COUNT))
		वापस -EINVAL;

	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
	sta_entry->tids[tid].agg.rx_agg_state = RTL_RX_AGG_STOP;

	वापस 0;
पूर्ण

पूर्णांक rtl_tx_agg_oper(काष्ठा ieee80211_hw *hw,
		काष्ठा ieee80211_sta *sta, u16 tid)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_sta_info *sta_entry = शून्य;

	अगर (sta == शून्य)
		वापस -EINVAL;

	rtl_dbg(rtlpriv, COMP_SEND, DBG_DMESG,
		"on ra = %pM tid = %d\n", sta->addr, tid);

	अगर (unlikely(tid >= MAX_TID_COUNT))
		वापस -EINVAL;

	sta_entry = (काष्ठा rtl_sta_info *)sta->drv_priv;
	sta_entry->tids[tid].agg.agg_state = RTL_AGG_OPERATIONAL;

	वापस 0;
पूर्ण

व्योम rtl_rx_ampdu_apply(काष्ठा rtl_priv *rtlpriv)
अणु
	काष्ठा rtl_btc_ops *btc_ops = rtlpriv->btcoexist.btc_ops;
	u8 reject_agg = 0, ctrl_agg_size = 0, agg_size = 0;

	अगर (rtlpriv->cfg->ops->get_btc_status())
		btc_ops->btc_get_ampdu_cfg(rtlpriv, &reject_agg,
					   &ctrl_agg_size, &agg_size);

	rtl_dbg(rtlpriv, COMP_BT_COEXIST, DBG_DMESG,
		"Set RX AMPDU: coex - reject=%d, ctrl_agg_size=%d, size=%d",
		reject_agg, ctrl_agg_size, agg_size);

	rtlpriv->hw->max_rx_aggregation_subframes =
		(ctrl_agg_size ? agg_size : IEEE80211_MAX_AMPDU_BUF_HT);
पूर्ण
EXPORT_SYMBOL(rtl_rx_ampdu_apply);

/*********************************************************
 *
 * wq & समयr callback functions
 *
 *********************************************************/
/* this function is used क्रम roaming */
व्योम rtl_beacon_statistic(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;

	अगर (rtlpriv->mac80211.opmode != NL80211_IFTYPE_STATION)
		वापस;

	अगर (rtlpriv->mac80211.link_state < MAC80211_LINKED)
		वापस;

	/* check अगर this really is a beacon */
	अगर (!ieee80211_is_beacon(hdr->frame_control) &&
	    !ieee80211_is_probe_resp(hdr->frame_control))
		वापस;

	/* min. beacon length + FCS_LEN */
	अगर (skb->len <= 40 + FCS_LEN)
		वापस;

	/* and only beacons from the associated BSSID, please */
	अगर (!ether_addr_equal(hdr->addr3, rtlpriv->mac80211.bssid))
		वापस;

	rtlpriv->link_info.bcn_rx_inperiod++;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_beacon_statistic);

अटल व्योम rtl_मुक्त_entries_from_scan_list(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_bssid_entry *entry, *next;

	list_क्रम_each_entry_safe(entry, next, &rtlpriv->scan_list.list, list) अणु
		list_del(&entry->list);
		kमुक्त(entry);
		rtlpriv->scan_list.num--;
	पूर्ण
पूर्ण

अटल व्योम rtl_मुक्त_entries_from_ack_queue(काष्ठा ieee80211_hw *hw,
					    bool chk_समयout)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_tx_report *tx_report = &rtlpriv->tx_report;
	काष्ठा sk_buff_head *queue = &tx_report->queue;
	काष्ठा sk_buff *skb, *पंचांगp;
	काष्ठा rtlwअगरi_tx_info *tx_info;

	skb_queue_walk_safe(queue, skb, पंचांगp) अणु
		tx_info = rtl_tx_skb_cb_info(skb);
		अगर (chk_समयout &&
		    समय_after(tx_info->send_समय + HZ, jअगरfies))
			जारी;
		skb_unlink(skb, queue);
		rtl_tx_status(hw, skb, false);
	पूर्ण
पूर्ण

व्योम rtl_scan_list_expire(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_bssid_entry *entry, *next;
	अचिन्हित दीर्घ flags;

	spin_lock_irqsave(&rtlpriv->locks.scan_list_lock, flags);

	list_क्रम_each_entry_safe(entry, next, &rtlpriv->scan_list.list, list) अणु
		/* 180 seconds */
		अगर (jअगरfies_to_msecs(jअगरfies - entry->age) < 180000)
			जारी;

		list_del(&entry->list);
		rtlpriv->scan_list.num--;

		rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
			"BSSID=%pM is expire in scan list (total=%d)\n",
			entry->bssid, rtlpriv->scan_list.num);
		kमुक्त(entry);
	पूर्ण

	spin_unlock_irqrestore(&rtlpriv->locks.scan_list_lock, flags);

	rtlpriv->btcoexist.btc_info.ap_num = rtlpriv->scan_list.num;
पूर्ण

व्योम rtl_collect_scan_list(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा ieee80211_hdr *hdr = (काष्ठा ieee80211_hdr *)skb->data;
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	अचिन्हित दीर्घ flags;

	काष्ठा rtl_bssid_entry *entry;
	bool entry_found = false;

	/* check अगर it is scanning */
	अगर (!mac->act_scanning)
		वापस;

	/* check अगर this really is a beacon */
	अगर (!ieee80211_is_beacon(hdr->frame_control) &&
	    !ieee80211_is_probe_resp(hdr->frame_control))
		वापस;

	spin_lock_irqsave(&rtlpriv->locks.scan_list_lock, flags);

	list_क्रम_each_entry(entry, &rtlpriv->scan_list.list, list) अणु
		अगर (स_भेद(entry->bssid, hdr->addr3, ETH_ALEN) == 0) अणु
			list_del_init(&entry->list);
			entry_found = true;
			rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
				"Update BSSID=%pM to scan list (total=%d)\n",
				hdr->addr3, rtlpriv->scan_list.num);
			अवरोध;
		पूर्ण
	पूर्ण

	अगर (!entry_found) अणु
		entry = kदो_स्मृति(माप(*entry), GFP_ATOMIC);

		अगर (!entry)
			जाओ label_err;

		स_नकल(entry->bssid, hdr->addr3, ETH_ALEN);
		rtlpriv->scan_list.num++;

		rtl_dbg(rtlpriv, COMP_SCAN, DBG_LOUD,
			"Add BSSID=%pM to scan list (total=%d)\n",
			hdr->addr3, rtlpriv->scan_list.num);
	पूर्ण

	entry->age = jअगरfies;

	list_add_tail(&entry->list, &rtlpriv->scan_list.list);

label_err:
	spin_unlock_irqrestore(&rtlpriv->locks.scan_list_lock, flags);
पूर्ण
EXPORT_SYMBOL(rtl_collect_scan_list);

अटल व्योम rtl_watchकरोg_wq_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks = container_of(work, काष्ठा rtl_works,
						  watchकरोg_wq.work);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	bool busytraffic = false;
	bool tx_busy_traffic = false;
	bool rx_busy_traffic = false;
	bool higher_busytraffic = false;
	bool higher_busyrxtraffic = false;
	u8 idx, tid;
	u32 rx_cnt_inp4eriod = 0;
	u32 tx_cnt_inp4eriod = 0;
	u32 aver_rx_cnt_inperiod = 0;
	u32 aver_tx_cnt_inperiod = 0;
	u32 aver_tidtx_inperiod[MAX_TID_COUNT] = अणु0पूर्ण;
	u32 tidtx_inp4eriod[MAX_TID_COUNT] = अणु0पूर्ण;

	अगर (is_hal_stop(rtlhal))
		वापस;

	/* <1> Determine अगर action frame is allowed */
	अगर (mac->link_state > MAC80211_NOLINK) अणु
		अगर (mac->cnt_after_linked < 20)
			mac->cnt_after_linked++;
	पूर्ण अन्यथा अणु
		mac->cnt_after_linked = 0;
	पूर्ण

	/* <2> to check अगर traffic busy, अगर
	 * busytraffic we करोn't change channel
	 */
	अगर (mac->link_state >= MAC80211_LINKED) अणु
		/* (1) get aver_rx_cnt_inperiod & aver_tx_cnt_inperiod */
		क्रम (idx = 0; idx <= 2; idx++) अणु
			rtlpriv->link_info.num_rx_in4period[idx] =
			    rtlpriv->link_info.num_rx_in4period[idx + 1];
			rtlpriv->link_info.num_tx_in4period[idx] =
			    rtlpriv->link_info.num_tx_in4period[idx + 1];
		पूर्ण
		rtlpriv->link_info.num_rx_in4period[3] =
		    rtlpriv->link_info.num_rx_inperiod;
		rtlpriv->link_info.num_tx_in4period[3] =
		    rtlpriv->link_info.num_tx_inperiod;
		क्रम (idx = 0; idx <= 3; idx++) अणु
			rx_cnt_inp4eriod +=
			    rtlpriv->link_info.num_rx_in4period[idx];
			tx_cnt_inp4eriod +=
			    rtlpriv->link_info.num_tx_in4period[idx];
		पूर्ण
		aver_rx_cnt_inperiod = rx_cnt_inp4eriod / 4;
		aver_tx_cnt_inperiod = tx_cnt_inp4eriod / 4;

		/* (2) check traffic busy */
		अगर (aver_rx_cnt_inperiod > 100 || aver_tx_cnt_inperiod > 100) अणु
			busytraffic = true;
			अगर (aver_rx_cnt_inperiod > aver_tx_cnt_inperiod)
				rx_busy_traffic = true;
			अन्यथा
				tx_busy_traffic = false;
		पूर्ण

		/* Higher Tx/Rx data. */
		अगर (aver_rx_cnt_inperiod > 4000 ||
		    aver_tx_cnt_inperiod > 4000) अणु
			higher_busytraffic = true;

			/* Extremely high Rx data. */
			अगर (aver_rx_cnt_inperiod > 5000)
				higher_busyrxtraffic = true;
		पूर्ण

		/* check every tid's tx traffic */
		क्रम (tid = 0; tid <= 7; tid++) अणु
			क्रम (idx = 0; idx <= 2; idx++)
				rtlpriv->link_info.tidtx_in4period[tid][idx] =
					rtlpriv->link_info.tidtx_in4period[tid]
					[idx + 1];
			rtlpriv->link_info.tidtx_in4period[tid][3] =
				rtlpriv->link_info.tidtx_inperiod[tid];

			क्रम (idx = 0; idx <= 3; idx++)
				tidtx_inp4eriod[tid] +=
				   rtlpriv->link_info.tidtx_in4period[tid][idx];
			aver_tidtx_inperiod[tid] = tidtx_inp4eriod[tid] / 4;
			अगर (aver_tidtx_inperiod[tid] > 5000)
				rtlpriv->link_info.higher_busytxtraffic[tid] =
									true;
			अन्यथा
				rtlpriv->link_info.higher_busytxtraffic[tid] =
									false;
		पूर्ण

		/* PS is controlled by coex. */
		अगर (rtlpriv->cfg->ops->get_btc_status() &&
		    rtlpriv->btcoexist.btc_ops->btc_is_bt_ctrl_lps(rtlpriv))
			जाओ label_lps_करोne;

		अगर (rtlpriv->link_info.num_rx_inperiod +
		      rtlpriv->link_info.num_tx_inperiod > 8 ||
		    rtlpriv->link_info.num_rx_inperiod > 2)
			rtl_lps_leave(hw, true);
		अन्यथा
			rtl_lps_enter(hw, true);

label_lps_करोne:
		;
	पूर्ण

	क्रम (tid = 0; tid <= 7; tid++)
		rtlpriv->link_info.tidtx_inperiod[tid] = 0;

	rtlpriv->link_info.busytraffic = busytraffic;
	rtlpriv->link_info.higher_busytraffic = higher_busytraffic;
	rtlpriv->link_info.rx_busy_traffic = rx_busy_traffic;
	rtlpriv->link_info.tx_busy_traffic = tx_busy_traffic;
	rtlpriv->link_info.higher_busyrxtraffic = higher_busyrxtraffic;

	rtlpriv->stats.txbytesunicast_inperiod =
		rtlpriv->stats.txbytesunicast -
		rtlpriv->stats.txbytesunicast_last;
	rtlpriv->stats.rxbytesunicast_inperiod =
		rtlpriv->stats.rxbytesunicast -
		rtlpriv->stats.rxbytesunicast_last;
	rtlpriv->stats.txbytesunicast_last = rtlpriv->stats.txbytesunicast;
	rtlpriv->stats.rxbytesunicast_last = rtlpriv->stats.rxbytesunicast;

	rtlpriv->stats.txbytesunicast_inperiod_tp =
		(u32)(rtlpriv->stats.txbytesunicast_inperiod * 8 / 2 /
		1024 / 1024);
	rtlpriv->stats.rxbytesunicast_inperiod_tp =
		(u32)(rtlpriv->stats.rxbytesunicast_inperiod * 8 / 2 /
		1024 / 1024);

	/* <3> DM */
	अगर (!rtlpriv->cfg->mod_params->disable_watchकरोg)
		rtlpriv->cfg->ops->dm_watchकरोg(hw);

	/* <4> roaming */
	अगर (mac->link_state == MAC80211_LINKED &&
	    mac->opmode == NL80211_IFTYPE_STATION) अणु
		अगर ((rtlpriv->link_info.bcn_rx_inperiod +
		    rtlpriv->link_info.num_rx_inperiod) == 0) अणु
			rtlpriv->link_info.roam_बार++;
			rtl_dbg(rtlpriv, COMP_ERR, DBG_DMESG,
				"AP off for %d s\n",
				(rtlpriv->link_info.roam_बार * 2));

			/* अगर we can't recv beacon क्रम 10s,
			 * we should reconnect this AP
			 */
			अगर (rtlpriv->link_info.roam_बार >= 5) अणु
				pr_err("AP off, try to reconnect now\n");
				rtlpriv->link_info.roam_बार = 0;
				ieee80211_connection_loss(
					rtlpriv->mac80211.vअगर);
			पूर्ण
		पूर्ण अन्यथा अणु
			rtlpriv->link_info.roam_बार = 0;
		पूर्ण
	पूर्ण

	अगर (rtlpriv->cfg->ops->get_btc_status())
		rtlpriv->btcoexist.btc_ops->btc_periodical(rtlpriv);

	अगर (rtlpriv->btcoexist.btc_info.in_4way) अणु
		अगर (समय_after(jअगरfies, rtlpriv->btcoexist.btc_info.in_4way_ts +
			       msecs_to_jअगरfies(IN_4WAY_TIMEOUT_TIME)))
			rtlpriv->btcoexist.btc_info.in_4way = false;
	पूर्ण

	rtlpriv->link_info.num_rx_inperiod = 0;
	rtlpriv->link_info.num_tx_inperiod = 0;
	rtlpriv->link_info.bcn_rx_inperiod = 0;

	/* <6> scan list */
	rtl_scan_list_expire(hw);

	/* <7> check ack queue */
	rtl_मुक्त_entries_from_ack_queue(hw, true);
पूर्ण

व्योम rtl_watch_करोg_समयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा rtl_priv *rtlpriv = from_समयr(rtlpriv, t, works.watchकरोg_समयr);

	queue_delayed_work(rtlpriv->works.rtl_wq,
			   &rtlpriv->works.watchकरोg_wq, 0);

	mod_समयr(&rtlpriv->works.watchकरोg_समयr,
		  jअगरfies + MSECS(RTL_WATCH_DOG_TIME));
पूर्ण

अटल व्योम rtl_fwevt_wq_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks = container_of(work, काष्ठा rtl_works,
						  fwevt_wq.work);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	rtlpriv->cfg->ops->c2h_command_handle(hw);
पूर्ण

अटल व्योम rtl_c2h_content_parsing(काष्ठा ieee80211_hw *hw,
				    काष्ठा sk_buff *skb);

अटल bool rtl_c2h_fast_cmd(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	u8 cmd_id = GET_C2H_CMD_ID(skb->data);

	चयन (cmd_id) अणु
	हाल C2H_BT_MP:
		वापस true;
	शेष:
		अवरोध;
	पूर्ण

	वापस false;
पूर्ण

व्योम rtl_c2hcmd_enqueue(काष्ठा ieee80211_hw *hw, काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);

	अगर (rtl_c2h_fast_cmd(hw, skb)) अणु
		rtl_c2h_content_parsing(hw, skb);
		kमुक्त_skb(skb);
		वापस;
	पूर्ण

	/* enqueue */
	skb_queue_tail(&rtlpriv->c2hcmd_queue, skb);

	/* wake up wq */
	queue_delayed_work(rtlpriv->works.rtl_wq, &rtlpriv->works.c2hcmd_wq, 0);
पूर्ण
EXPORT_SYMBOL(rtl_c2hcmd_enqueue);

अटल व्योम rtl_c2h_content_parsing(काष्ठा ieee80211_hw *hw,
				    काष्ठा sk_buff *skb)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal_ops *hal_ops = rtlpriv->cfg->ops;
	स्थिर काष्ठा rtl_btc_ops *btc_ops = rtlpriv->btcoexist.btc_ops;
	u8 cmd_id, cmd_len;
	u8 *cmd_buf = शून्य;

	cmd_id = GET_C2H_CMD_ID(skb->data);
	cmd_len = skb->len - C2H_DATA_OFFSET;
	cmd_buf = GET_C2H_DATA_PTR(skb->data);

	चयन (cmd_id) अणु
	हाल C2H_DBG:
		rtl_dbg(rtlpriv, COMP_FW, DBG_LOUD, "[C2H], C2H_DBG!!\n");
		अवरोध;
	हाल C2H_TXBF:
		rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
			"[C2H], C2H_TXBF!!\n");
		अवरोध;
	हाल C2H_TX_REPORT:
		rtl_tx_report_handler(hw, cmd_buf, cmd_len);
		अवरोध;
	हाल C2H_RA_RPT:
		अगर (hal_ops->c2h_ra_report_handler)
			hal_ops->c2h_ra_report_handler(hw, cmd_buf, cmd_len);
		अवरोध;
	हाल C2H_BT_INFO:
		rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
			"[C2H], C2H_BT_INFO!!\n");
		अगर (rtlpriv->cfg->ops->get_btc_status())
			btc_ops->btc_btinfo_notअगरy(rtlpriv, cmd_buf, cmd_len);
		अवरोध;
	हाल C2H_BT_MP:
		rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
			"[C2H], C2H_BT_MP!!\n");
		अगर (rtlpriv->cfg->ops->get_btc_status())
			btc_ops->btc_bपंचांगpinfo_notअगरy(rtlpriv, cmd_buf, cmd_len);
		अवरोध;
	शेष:
		rtl_dbg(rtlpriv, COMP_FW, DBG_TRACE,
			"[C2H], Unknown packet!! cmd_id(%#X)!\n", cmd_id);
		अवरोध;
	पूर्ण
पूर्ण

व्योम rtl_c2hcmd_launcher(काष्ठा ieee80211_hw *hw, पूर्णांक exec)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा sk_buff *skb;
	पूर्णांक i;

	क्रम (i = 0; i < 200; i++) अणु
		/* dequeue a task */
		skb = skb_dequeue(&rtlpriv->c2hcmd_queue);

		/* करो it */
		अगर (!skb)
			अवरोध;

		rtl_dbg(rtlpriv, COMP_FW, DBG_DMESG, "C2H rx_desc_shift=%d\n",
			*((u8 *)skb->cb));
		RT_PRINT_DATA(rtlpriv, COMP_FW, DBG_DMESG,
			      "C2H data: ", skb->data, skb->len);

		अगर (exec)
			rtl_c2h_content_parsing(hw, skb);

		/* मुक्त */
		dev_kमुक्त_skb_any(skb);
	पूर्ण
पूर्ण

अटल व्योम rtl_c2hcmd_wq_callback(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rtl_works *rtlworks = container_of(work, काष्ठा rtl_works,
						  c2hcmd_wq.work);
	काष्ठा ieee80211_hw *hw = rtlworks->hw;

	rtl_c2hcmd_launcher(hw, 1);
पूर्ण

व्योम rtl_easy_concurrent_retryसमयr_callback(काष्ठा समयr_list *t)
अणु
	काष्ठा rtl_priv *rtlpriv =
		from_समयr(rtlpriv, t, works.dualmac_easyconcurrent_retryसमयr);
	काष्ठा ieee80211_hw *hw = rtlpriv->hw;
	काष्ठा rtl_priv *buddy_priv = rtlpriv->buddy_priv;

	अगर (buddy_priv == शून्य)
		वापस;

	rtlpriv->cfg->ops->dualmac_easy_concurrent(hw);
पूर्ण

/*********************************************************
 *
 * frame process functions
 *
 *********************************************************/
u8 *rtl_find_ie(u8 *data, अचिन्हित पूर्णांक len, u8 ie)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)data;
	u8 *pos, *end;

	pos = (u8 *)mgmt->u.beacon.variable;
	end = data + len;
	जबतक (pos < end) अणु
		अगर (pos + 2 + pos[1] > end)
			वापस शून्य;

		अगर (pos[0] == ie)
			वापस pos;

		pos += 2 + pos[1];
	पूर्ण
	वापस शून्य;
पूर्ण

/* when we use 2 rx ants we send IEEE80211_SMPS_OFF */
/* when we use 1 rx ant we send IEEE80211_SMPS_STATIC */
अटल काष्ठा sk_buff *rtl_make_smps_action(काष्ठा ieee80211_hw *hw,
				     क्रमागत ieee80211_smps_mode smps,
				     u8 *da, u8 *bssid)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *action_frame;

	/* 27 = header + category + action + smps mode */
	skb = dev_alloc_skb(27 + hw->extra_tx_headroom);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, hw->extra_tx_headroom);
	action_frame = skb_put_zero(skb, 27);
	स_नकल(action_frame->da, da, ETH_ALEN);
	स_नकल(action_frame->sa, rtlefuse->dev_addr, ETH_ALEN);
	स_नकल(action_frame->bssid, bssid, ETH_ALEN);
	action_frame->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						  IEEE80211_STYPE_ACTION);
	action_frame->u.action.category = WLAN_CATEGORY_HT;
	action_frame->u.action.u.ht_smps.action = WLAN_HT_ACTION_SMPS;
	चयन (smps) अणु
	हाल IEEE80211_SMPS_AUTOMATIC:/* 0 */
	हाल IEEE80211_SMPS_NUM_MODES:/* 4 */
		WARN_ON(1);
		fallthrough;
	हाल IEEE80211_SMPS_OFF:/* 1 */ /*MIMO_PS_NOLIMIT*/
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_DISABLED;/* 0 */
		अवरोध;
	हाल IEEE80211_SMPS_STATIC:/* 2 */ /*MIMO_PS_STATIC*/
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_STATIC;/* 1 */
		अवरोध;
	हाल IEEE80211_SMPS_DYNAMIC:/* 3 */ /*MIMO_PS_DYNAMIC*/
		action_frame->u.action.u.ht_smps.smps_control =
				WLAN_HT_SMPS_CONTROL_DYNAMIC;/* 3 */
		अवरोध;
	पूर्ण

	वापस skb;
पूर्ण

पूर्णांक rtl_send_smps_action(काष्ठा ieee80211_hw *hw,
			 काष्ठा ieee80211_sta *sta,
			 क्रमागत ieee80211_smps_mode smps)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	काष्ठा rtl_ps_ctl *ppsc = rtl_psc(rtl_priv(hw));
	काष्ठा sk_buff *skb = शून्य;
	काष्ठा rtl_tcb_desc tcb_desc;
	u8 bssid[ETH_ALEN] = अणु0पूर्ण;

	स_रखो(&tcb_desc, 0, माप(काष्ठा rtl_tcb_desc));

	अगर (rtlpriv->mac80211.act_scanning)
		जाओ err_मुक्त;

	अगर (!sta)
		जाओ err_मुक्त;

	अगर (unlikely(is_hal_stop(rtlhal) || ppsc->rfpwr_state != ERFON))
		जाओ err_मुक्त;

	अगर (!test_bit(RTL_STATUS_INTERFACE_START, &rtlpriv->status))
		जाओ err_मुक्त;

	अगर (rtlpriv->mac80211.opmode == NL80211_IFTYPE_AP)
		स_नकल(bssid, rtlpriv->efuse.dev_addr, ETH_ALEN);
	अन्यथा
		स_नकल(bssid, rtlpriv->mac80211.bssid, ETH_ALEN);

	skb = rtl_make_smps_action(hw, smps, sta->addr, bssid);
	/* this is a type = mgmt * stype = action frame */
	अगर (skb) अणु
		काष्ठा ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
		काष्ठा rtl_sta_info *sta_entry =
			(काष्ठा rtl_sta_info *) sta->drv_priv;
		sta_entry->mimo_ps = smps;
		/* rtlpriv->cfg->ops->update_rate_tbl(hw, sta, 0, true); */

		info->control.rates[0].idx = 0;
		info->band = hw->conf.chandef.chan->band;
		rtlpriv->पूर्णांकf_ops->adapter_tx(hw, sta, skb, &tcb_desc);
	पूर्ण
	वापस 1;

err_मुक्त:
	वापस 0;
पूर्ण
EXPORT_SYMBOL(rtl_send_smps_action);

व्योम rtl_phy_scan_operation_backup(काष्ठा ieee80211_hw *hw, u8 operation)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_hal *rtlhal = rtl_hal(rtl_priv(hw));
	क्रमागत io_type iotype;

	अगर (!is_hal_stop(rtlhal)) अणु
		चयन (operation) अणु
		हाल SCAN_OPT_BACKUP:
			iotype = IO_CMD_PAUSE_DM_BY_SCAN;
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_IO_CMD,
						      (u8 *)&iotype);
			अवरोध;
		हाल SCAN_OPT_RESTORE:
			iotype = IO_CMD_RESUME_DM_BY_SCAN;
			rtlpriv->cfg->ops->set_hw_reg(hw,
						      HW_VAR_IO_CMD,
						      (u8 *)&iotype);
			अवरोध;
		शेष:
			pr_err("Unknown Scan Backup operation.\n");
			अवरोध;
		पूर्ण
	पूर्ण
पूर्ण
EXPORT_SYMBOL(rtl_phy_scan_operation_backup);

/* because mac80211 have issues when can receive del ba
 * so here we just make a fake del_ba अगर we receive a ba_req
 * but rx_agg was खोलोed to let mac80211 release some ba
 * related resources, so please this del_ba क्रम tx
 */
काष्ठा sk_buff *rtl_make_del_ba(काष्ठा ieee80211_hw *hw,
				u8 *sa, u8 *bssid, u16 tid)
अणु
	काष्ठा rtl_efuse *rtlefuse = rtl_efuse(rtl_priv(hw));
	काष्ठा sk_buff *skb;
	काष्ठा ieee80211_mgmt *action_frame;
	u16 params;

	/* 27 = header + category + action + smps mode */
	skb = dev_alloc_skb(34 + hw->extra_tx_headroom);
	अगर (!skb)
		वापस शून्य;

	skb_reserve(skb, hw->extra_tx_headroom);
	action_frame = skb_put_zero(skb, 34);
	स_नकल(action_frame->sa, sa, ETH_ALEN);
	स_नकल(action_frame->da, rtlefuse->dev_addr, ETH_ALEN);
	स_नकल(action_frame->bssid, bssid, ETH_ALEN);
	action_frame->frame_control = cpu_to_le16(IEEE80211_FTYPE_MGMT |
						  IEEE80211_STYPE_ACTION);
	action_frame->u.action.category = WLAN_CATEGORY_BACK;
	action_frame->u.action.u.delba.action_code = WLAN_ACTION_DELBA;
	params = (u16)(1 << 11);	/* bit 11 initiator */
	params |= (u16)(tid << 12);	/* bit 15:12 TID number */

	action_frame->u.action.u.delba.params = cpu_to_le16(params);
	action_frame->u.action.u.delba.reason_code =
		cpu_to_le16(WLAN_REASON_QSTA_TIMEOUT);

	वापस skb;
पूर्ण

/*********************************************************
 *
 * IOT functions
 *
 *********************************************************/
अटल bool rtl_chk_venकरोr_ouisub(काष्ठा ieee80211_hw *hw,
				  काष्ठा octet_string venकरोr_ie)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	bool matched = false;
	अटल u8 athcap_1[] = अणु 0x00, 0x03, 0x7F पूर्ण;
	अटल u8 athcap_2[] = अणु 0x00, 0x13, 0x74 पूर्ण;
	अटल u8 broadcap_1[] = अणु 0x00, 0x10, 0x18 पूर्ण;
	अटल u8 broadcap_2[] = अणु 0x00, 0x0a, 0xf7 पूर्ण;
	अटल u8 broadcap_3[] = अणु 0x00, 0x05, 0xb5 पूर्ण;
	अटल u8 racap[] = अणु 0x00, 0x0c, 0x43 पूर्ण;
	अटल u8 ciscocap[] = अणु 0x00, 0x40, 0x96 पूर्ण;
	अटल u8 marvcap[] = अणु 0x00, 0x50, 0x43 पूर्ण;

	अगर (स_भेद(venकरोr_ie.octet, athcap_1, 3) == 0 ||
		स_भेद(venकरोr_ie.octet, athcap_2, 3) == 0) अणु
		rtlpriv->mac80211.venकरोr = PEER_ATH;
		matched = true;
	पूर्ण अन्यथा अगर (स_भेद(venकरोr_ie.octet, broadcap_1, 3) == 0 ||
		स_भेद(venकरोr_ie.octet, broadcap_2, 3) == 0 ||
		स_भेद(venकरोr_ie.octet, broadcap_3, 3) == 0) अणु
		rtlpriv->mac80211.venकरोr = PEER_BROAD;
		matched = true;
	पूर्ण अन्यथा अगर (स_भेद(venकरोr_ie.octet, racap, 3) == 0) अणु
		rtlpriv->mac80211.venकरोr = PEER_RAL;
		matched = true;
	पूर्ण अन्यथा अगर (स_भेद(venकरोr_ie.octet, ciscocap, 3) == 0) अणु
		rtlpriv->mac80211.venकरोr = PEER_CISCO;
		matched = true;
	पूर्ण अन्यथा अगर (स_भेद(venकरोr_ie.octet, marvcap, 3) == 0) अणु
		rtlpriv->mac80211.venकरोr = PEER_MARV;
		matched = true;
	पूर्ण

	वापस matched;
पूर्ण

अटल bool rtl_find_221_ie(काष्ठा ieee80211_hw *hw, u8 *data,
		अचिन्हित पूर्णांक len)
अणु
	काष्ठा ieee80211_mgmt *mgmt = (व्योम *)data;
	काष्ठा octet_string venकरोr_ie;
	u8 *pos, *end;

	pos = (u8 *)mgmt->u.beacon.variable;
	end = data + len;
	जबतक (pos < end) अणु
		अगर (pos[0] == 221) अणु
			venकरोr_ie.length = pos[1];
			venकरोr_ie.octet = &pos[2];
			अगर (rtl_chk_venकरोr_ouisub(hw, venकरोr_ie))
				वापस true;
		पूर्ण

		अगर (pos + 2 + pos[1] > end)
			वापस false;

		pos += 2 + pos[1];
	पूर्ण
	वापस false;
पूर्ण

व्योम rtl_recognize_peer(काष्ठा ieee80211_hw *hw, u8 *data, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rtl_priv *rtlpriv = rtl_priv(hw);
	काष्ठा rtl_mac *mac = rtl_mac(rtl_priv(hw));
	काष्ठा ieee80211_hdr *hdr = (व्योम *)data;
	u32 venकरोr = PEER_UNKNOWN;

	अटल u8 ap3_1[3] = अणु 0x00, 0x14, 0xbf पूर्ण;
	अटल u8 ap3_2[3] = अणु 0x00, 0x1a, 0x70 पूर्ण;
	अटल u8 ap3_3[3] = अणु 0x00, 0x1d, 0x7e पूर्ण;
	अटल u8 ap4_1[3] = अणु 0x00, 0x90, 0xcc पूर्ण;
	अटल u8 ap4_2[3] = अणु 0x00, 0x0e, 0x2e पूर्ण;
	अटल u8 ap4_3[3] = अणु 0x00, 0x18, 0x02 पूर्ण;
	अटल u8 ap4_4[3] = अणु 0x00, 0x17, 0x3f पूर्ण;
	अटल u8 ap4_5[3] = अणु 0x00, 0x1c, 0xdf पूर्ण;
	अटल u8 ap5_1[3] = अणु 0x00, 0x1c, 0xf0 पूर्ण;
	अटल u8 ap5_2[3] = अणु 0x00, 0x21, 0x91 पूर्ण;
	अटल u8 ap5_3[3] = अणु 0x00, 0x24, 0x01 पूर्ण;
	अटल u8 ap5_4[3] = अणु 0x00, 0x15, 0xe9 पूर्ण;
	अटल u8 ap5_5[3] = अणु 0x00, 0x17, 0x9A पूर्ण;
	अटल u8 ap5_6[3] = अणु 0x00, 0x18, 0xE7 पूर्ण;
	अटल u8 ap6_1[3] = अणु 0x00, 0x17, 0x94 पूर्ण;
	अटल u8 ap7_1[3] = अणु 0x00, 0x14, 0xa4 पूर्ण;

	अगर (mac->opmode != NL80211_IFTYPE_STATION)
		वापस;

	अगर (mac->link_state == MAC80211_NOLINK) अणु
		mac->venकरोr = PEER_UNKNOWN;
		वापस;
	पूर्ण

	अगर (mac->cnt_after_linked > 2)
		वापस;

	/* check अगर this really is a beacon */
	अगर (!ieee80211_is_beacon(hdr->frame_control))
		वापस;

	/* min. beacon length + FCS_LEN */
	अगर (len <= 40 + FCS_LEN)
		वापस;

	/* and only beacons from the associated BSSID, please */
	अगर (!ether_addr_equal_64bits(hdr->addr3, rtlpriv->mac80211.bssid))
		वापस;

	अगर (rtl_find_221_ie(hw, data, len))
		venकरोr = mac->venकरोr;

	अगर ((स_भेद(mac->bssid, ap5_1, 3) == 0) ||
		(स_भेद(mac->bssid, ap5_2, 3) == 0) ||
		(स_भेद(mac->bssid, ap5_3, 3) == 0) ||
		(स_भेद(mac->bssid, ap5_4, 3) == 0) ||
		(स_भेद(mac->bssid, ap5_5, 3) == 0) ||
		(स_भेद(mac->bssid, ap5_6, 3) == 0) ||
		venकरोr == PEER_ATH) अणु
		venकरोr = PEER_ATH;
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD, "=>ath find\n");
	पूर्ण अन्यथा अगर ((स_भेद(mac->bssid, ap4_4, 3) == 0) ||
		(स_भेद(mac->bssid, ap4_5, 3) == 0) ||
		(स_भेद(mac->bssid, ap4_1, 3) == 0) ||
		(स_भेद(mac->bssid, ap4_2, 3) == 0) ||
		(स_भेद(mac->bssid, ap4_3, 3) == 0) ||
		venकरोr == PEER_RAL) अणु
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD, "=>ral find\n");
		venकरोr = PEER_RAL;
	पूर्ण अन्यथा अगर (स_भेद(mac->bssid, ap6_1, 3) == 0 ||
		venकरोr == PEER_CISCO) अणु
		venकरोr = PEER_CISCO;
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD, "=>cisco find\n");
	पूर्ण अन्यथा अगर ((स_भेद(mac->bssid, ap3_1, 3) == 0) ||
		(स_भेद(mac->bssid, ap3_2, 3) == 0) ||
		(स_भेद(mac->bssid, ap3_3, 3) == 0) ||
		venकरोr == PEER_BROAD) अणु
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD, "=>broad find\n");
		venकरोr = PEER_BROAD;
	पूर्ण अन्यथा अगर (स_भेद(mac->bssid, ap7_1, 3) == 0 ||
		venकरोr == PEER_MARV) अणु
		venकरोr = PEER_MARV;
		rtl_dbg(rtlpriv, COMP_MAC80211, DBG_LOUD, "=>marv find\n");
	पूर्ण

	mac->venकरोr = venकरोr;
पूर्ण
EXPORT_SYMBOL_GPL(rtl_recognize_peer);

MODULE_AUTHOR("lizhaoming	<chaoming_li@realsil.com.cn>");
MODULE_AUTHOR("Realtek WlanFAE	<wlanfae@realtek.com>");
MODULE_AUTHOR("Larry Finger	<Larry.FInger@lwfinger.net>");
MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Realtek 802.11n PCI wireless core");

काष्ठा rtl_global_var rtl_global_var = अणुपूर्ण;
EXPORT_SYMBOL_GPL(rtl_global_var);

अटल पूर्णांक __init rtl_core_module_init(व्योम)
अणु
	BUILD_BUG_ON(TX_PWR_BY_RATE_NUM_RATE < TX_PWR_BY_RATE_NUM_SECTION);
	BUILD_BUG_ON(MAX_RATE_SECTION_NUM != MAX_RATE_SECTION);
	BUILD_BUG_ON(MAX_BASE_NUM_IN_PHY_REG_PG_24G != MAX_RATE_SECTION);
	BUILD_BUG_ON(MAX_BASE_NUM_IN_PHY_REG_PG_5G != (MAX_RATE_SECTION - 1));

	अगर (rtl_rate_control_रेजिस्टर())
		pr_err("rtl: Unable to register rtl_rc, use default RC !!\n");

	/* add debugfs */
	rtl_debugfs_add_topdir();

	/* init some global vars */
	INIT_LIST_HEAD(&rtl_global_var.glb_priv_list);
	spin_lock_init(&rtl_global_var.glb_list_lock);

	वापस 0;
पूर्ण

अटल व्योम __निकास rtl_core_module_निकास(व्योम)
अणु
	/*RC*/
	rtl_rate_control_unरेजिस्टर();

	/* हटाओ debugfs */
	rtl_debugfs_हटाओ_topdir();
पूर्ण

module_init(rtl_core_module_init);
module_निकास(rtl_core_module_निकास);
