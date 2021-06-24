<शैली गुरु>
/*
 * Copyright (c) 2013 Eugene Krasnikov <k.eugene.e@gmail.com>
 *
 * Permission to use, copy, modअगरy, and/or distribute this software क्रम any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY
 * SPECIAL, सूचीECT, INसूचीECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION
 * OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
 * CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/etherdevice.h>
#समावेश <linux/firmware.h>
#समावेश <linux/bitops.h>
#समावेश <linux/rpmsg.h>
#समावेश "smd.h"

काष्ठा wcn36xx_cfg_val अणु
	u32 cfg_id;
	u32 value;
पूर्ण;

#घोषणा WCN36XX_CFG_VAL(id, val) \
अणु \
	.cfg_id = WCN36XX_HAL_CFG_ ## id, \
	.value = val \
पूर्ण

अटल काष्ठा wcn36xx_cfg_val wcn36xx_cfg_vals[] = अणु
	WCN36XX_CFG_VAL(CURRENT_TX_ANTENNA, 1),
	WCN36XX_CFG_VAL(CURRENT_RX_ANTENNA, 1),
	WCN36XX_CFG_VAL(LOW_GAIN_OVERRIDE, 0),
	WCN36XX_CFG_VAL(POWER_STATE_PER_CHAIN, 785),
	WCN36XX_CFG_VAL(CAL_PERIOD, 5),
	WCN36XX_CFG_VAL(CAL_CONTROL, 1),
	WCN36XX_CFG_VAL(PROXIMITY, 0),
	WCN36XX_CFG_VAL(NETWORK_DENSITY, 3),
	WCN36XX_CFG_VAL(MAX_MEDIUM_TIME, 6000),
	WCN36XX_CFG_VAL(MAX_MPDUS_IN_AMPDU, 64),
	WCN36XX_CFG_VAL(RTS_THRESHOLD, 2347),
	WCN36XX_CFG_VAL(SHORT_RETRY_LIMIT, 15),
	WCN36XX_CFG_VAL(LONG_RETRY_LIMIT, 15),
	WCN36XX_CFG_VAL(FRAGMENTATION_THRESHOLD, 8000),
	WCN36XX_CFG_VAL(DYNAMIC_THRESHOLD_ZERO, 5),
	WCN36XX_CFG_VAL(DYNAMIC_THRESHOLD_ONE, 10),
	WCN36XX_CFG_VAL(DYNAMIC_THRESHOLD_TWO, 15),
	WCN36XX_CFG_VAL(FIXED_RATE, 0),
	WCN36XX_CFG_VAL(RETRYRATE_POLICY, 4),
	WCN36XX_CFG_VAL(RETRYRATE_SECONDARY, 0),
	WCN36XX_CFG_VAL(RETRYRATE_TERTIARY, 0),
	WCN36XX_CFG_VAL(FORCE_POLICY_PROTECTION, 5),
	WCN36XX_CFG_VAL(FIXED_RATE_MULTICAST_24GHZ, 1),
	WCN36XX_CFG_VAL(FIXED_RATE_MULTICAST_5GHZ, 5),
	WCN36XX_CFG_VAL(DEFAULT_RATE_INDEX_5GHZ, 5),
	WCN36XX_CFG_VAL(MAX_BA_SESSIONS, 40),
	WCN36XX_CFG_VAL(PS_DATA_INACTIVITY_TIMEOUT, 200),
	WCN36XX_CFG_VAL(PS_ENABLE_BCN_FILTER, 1),
	WCN36XX_CFG_VAL(PS_ENABLE_RSSI_MONITOR, 1),
	WCN36XX_CFG_VAL(NUM_BEACON_PER_RSSI_AVERAGE, 20),
	WCN36XX_CFG_VAL(STATS_PERIOD, 10),
	WCN36XX_CFG_VAL(CFP_MAX_DURATION, 30000),
	WCN36XX_CFG_VAL(FRAME_TRANS_ENABLED, 0),
	WCN36XX_CFG_VAL(BA_THRESHOLD_HIGH, 128),
	WCN36XX_CFG_VAL(MAX_BA_BUFFERS, 2560),
	WCN36XX_CFG_VAL(DYNAMIC_PS_POLL_VALUE, 0),
	WCN36XX_CFG_VAL(TX_PWR_CTRL_ENABLE, 1),
	WCN36XX_CFG_VAL(ENABLE_CLOSE_LOOP, 1),
	WCN36XX_CFG_VAL(ENABLE_LPWR_IMG_TRANSITION, 0),
	WCN36XX_CFG_VAL(BTC_STATIC_LEN_LE_BT, 120000),
	WCN36XX_CFG_VAL(BTC_STATIC_LEN_LE_WLAN, 30000),
	WCN36XX_CFG_VAL(MAX_ASSOC_LIMIT, 10),
	WCN36XX_CFG_VAL(ENABLE_MCC_ADAPTIVE_SCHEDULER, 0),
	WCN36XX_CFG_VAL(ENABLE_DYNAMIC_RA_START_RATE, 133), /* MCS 5 */
	WCN36XX_CFG_VAL(LINK_FAIL_TX_CNT, 1000),
पूर्ण;

अटल काष्ठा wcn36xx_cfg_val wcn3680_cfg_vals[] = अणु
	WCN36XX_CFG_VAL(CURRENT_TX_ANTENNA, 1),
	WCN36XX_CFG_VAL(CURRENT_RX_ANTENNA, 1),
	WCN36XX_CFG_VAL(LOW_GAIN_OVERRIDE, 0),
	WCN36XX_CFG_VAL(POWER_STATE_PER_CHAIN, 785),
	WCN36XX_CFG_VAL(CAL_PERIOD, 5),
	WCN36XX_CFG_VAL(CAL_CONTROL, 1),
	WCN36XX_CFG_VAL(PROXIMITY, 0),
	WCN36XX_CFG_VAL(NETWORK_DENSITY, 3),
	WCN36XX_CFG_VAL(MAX_MEDIUM_TIME, 4096),
	WCN36XX_CFG_VAL(MAX_MPDUS_IN_AMPDU, 64),
	WCN36XX_CFG_VAL(RTS_THRESHOLD, 2347),
	WCN36XX_CFG_VAL(SHORT_RETRY_LIMIT, 15),
	WCN36XX_CFG_VAL(LONG_RETRY_LIMIT, 15),
	WCN36XX_CFG_VAL(FRAGMENTATION_THRESHOLD, 8000),
	WCN36XX_CFG_VAL(DYNAMIC_THRESHOLD_ZERO, 5),
	WCN36XX_CFG_VAL(DYNAMIC_THRESHOLD_ONE, 10),
	WCN36XX_CFG_VAL(DYNAMIC_THRESHOLD_TWO, 15),
	WCN36XX_CFG_VAL(FIXED_RATE, 0),
	WCN36XX_CFG_VAL(RETRYRATE_POLICY, 4),
	WCN36XX_CFG_VAL(RETRYRATE_SECONDARY, 0),
	WCN36XX_CFG_VAL(RETRYRATE_TERTIARY, 0),
	WCN36XX_CFG_VAL(FORCE_POLICY_PROTECTION, 5),
	WCN36XX_CFG_VAL(FIXED_RATE_MULTICAST_24GHZ, 1),
	WCN36XX_CFG_VAL(FIXED_RATE_MULTICAST_5GHZ, 5),
	WCN36XX_CFG_VAL(DEFAULT_RATE_INDEX_24GHZ, 1),
	WCN36XX_CFG_VAL(DEFAULT_RATE_INDEX_5GHZ, 5),
	WCN36XX_CFG_VAL(MAX_BA_SESSIONS, 40),
	WCN36XX_CFG_VAL(PS_DATA_INACTIVITY_TIMEOUT, 200),
	WCN36XX_CFG_VAL(PS_ENABLE_BCN_FILTER, 1),
	WCN36XX_CFG_VAL(PS_ENABLE_RSSI_MONITOR, 1),
	WCN36XX_CFG_VAL(NUM_BEACON_PER_RSSI_AVERAGE, 20),
	WCN36XX_CFG_VAL(STATS_PERIOD, 10),
	WCN36XX_CFG_VAL(CFP_MAX_DURATION, 30000),
	WCN36XX_CFG_VAL(FRAME_TRANS_ENABLED, 0),
	WCN36XX_CFG_VAL(BA_THRESHOLD_HIGH, 128),
	WCN36XX_CFG_VAL(MAX_BA_BUFFERS, 2560),
	WCN36XX_CFG_VAL(DYNAMIC_PS_POLL_VALUE, 0),
	WCN36XX_CFG_VAL(TX_PWR_CTRL_ENABLE, 1),
	WCN36XX_CFG_VAL(ENABLE_CLOSE_LOOP, 1),
	WCN36XX_CFG_VAL(ENABLE_LPWR_IMG_TRANSITION, 0),
	WCN36XX_CFG_VAL(BTC_STATIC_LEN_LE_BT, 120000),
	WCN36XX_CFG_VAL(BTC_STATIC_LEN_LE_WLAN, 30000),
	WCN36XX_CFG_VAL(MAX_ASSOC_LIMIT, 10),
	WCN36XX_CFG_VAL(ENABLE_MCC_ADAPTIVE_SCHEDULER, 0),
	WCN36XX_CFG_VAL(TDLS_PUAPSD_MASK, 0),
	WCN36XX_CFG_VAL(TDLS_PUAPSD_BUFFER_STA_CAPABLE, 1),
	WCN36XX_CFG_VAL(TDLS_PUAPSD_INACTIVITY_TIME, 0),
	WCN36XX_CFG_VAL(TDLS_PUAPSD_RX_FRAME_THRESHOLD, 10),
	WCN36XX_CFG_VAL(TDLS_OFF_CHANNEL_CAPABLE, 1),
	WCN36XX_CFG_VAL(ENABLE_ADAPTIVE_RX_DRAIN, 1),
	WCN36XX_CFG_VAL(FLEXCONNECT_POWER_FACTOR, 0),
	WCN36XX_CFG_VAL(ANTENNA_DIVERSITY, 3),
	WCN36XX_CFG_VAL(ATH_DISABLE, 0),
	WCN36XX_CFG_VAL(BTC_STATIC_OPP_WLAN_ACTIVE_WLAN_LEN, 60000),
	WCN36XX_CFG_VAL(BTC_STATIC_OPP_WLAN_ACTIVE_BT_LEN, 90000),
	WCN36XX_CFG_VAL(BTC_SAP_STATIC_OPP_ACTIVE_WLAN_LEN, 30000),
	WCN36XX_CFG_VAL(BTC_SAP_STATIC_OPP_ACTIVE_BT_LEN, 30000),
	WCN36XX_CFG_VAL(ASD_PROBE_INTERVAL, 50),
	WCN36XX_CFG_VAL(ASD_TRIGGER_THRESHOLD, -60),
	WCN36XX_CFG_VAL(ASD_RTT_RSSI_HYST_THRESHOLD, 3),
	WCN36XX_CFG_VAL(BTC_CTS2S_ON_STA_DURING_SCO, 0),
	WCN36XX_CFG_VAL(RA_FILTER_ENABLE, 0),
	WCN36XX_CFG_VAL(RA_RATE_LIMIT_INTERVAL, 60),
	WCN36XX_CFG_VAL(BTC_FATAL_HID_NSNIFF_BLK, 2),
	WCN36XX_CFG_VAL(BTC_CRITICAL_HID_NSNIFF_BLK, 1),
	WCN36XX_CFG_VAL(BTC_DYN_A2DP_TX_QUEUE_THOLD, 0),
	WCN36XX_CFG_VAL(BTC_DYN_OPP_TX_QUEUE_THOLD, 1),
	WCN36XX_CFG_VAL(MAX_UAPSD_CONSEC_SP, 10),
	WCN36XX_CFG_VAL(MAX_UAPSD_CONSEC_RX_CNT, 50),
	WCN36XX_CFG_VAL(MAX_UAPSD_CONSEC_TX_CNT, 50),
	WCN36XX_CFG_VAL(MAX_UAPSD_CONSEC_TX_CNT_MEAS_WINDOW, 500),
	WCN36XX_CFG_VAL(MAX_UAPSD_CONSEC_RX_CNT_MEAS_WINDOW, 500),
	WCN36XX_CFG_VAL(MAX_PSPOLL_IN_WMM_UAPSD_PS_MODE, 0),
	WCN36XX_CFG_VAL(MAX_UAPSD_INACTIVITY_INTERVALS, 10),
	WCN36XX_CFG_VAL(ENABLE_DYNAMIC_WMMPS, 1),
	WCN36XX_CFG_VAL(BURST_MODE_BE_TXOP_VALUE, 0),
	WCN36XX_CFG_VAL(ENABLE_DYNAMIC_RA_START_RATE, 136),
	WCN36XX_CFG_VAL(BTC_FAST_WLAN_CONN_PREF, 1),
	WCN36XX_CFG_VAL(ENABLE_RTSCTS_HTVHT, 0),
	WCN36XX_CFG_VAL(BTC_STATIC_OPP_WLAN_IDLE_WLAN_LEN, 30000),
	WCN36XX_CFG_VAL(BTC_STATIC_OPP_WLAN_IDLE_BT_LEN, 120000),
	WCN36XX_CFG_VAL(LINK_FAIL_TX_CNT, 1000),
	WCN36XX_CFG_VAL(TOGGLE_ARP_BDRATES, 0),
	WCN36XX_CFG_VAL(OPTIMIZE_CA_EVENT, 0),
	WCN36XX_CFG_VAL(EXT_SCAN_CONC_MODE, 0),
	WCN36XX_CFG_VAL(BAR_WAKEUP_HOST_DISABLE, 0),
	WCN36XX_CFG_VAL(SAR_BOFFSET_CORRECTION_ENABLE, 0),
	WCN36XX_CFG_VAL(BTC_DISABLE_WLAN_LINK_CRITICAL, 5),
	WCN36XX_CFG_VAL(DISABLE_SCAN_DURING_SCO, 2),
	WCN36XX_CFG_VAL(CONS_BCNMISS_COUNT, 0),
	WCN36XX_CFG_VAL(UNITS_OF_BCN_WAIT_TIME, 0),
	WCN36XX_CFG_VAL(TRIGGER_शून्यFRAME_BEFORE_HB, 0),
	WCN36XX_CFG_VAL(ENABLE_POWERSAVE_OFFLOAD, 0),
पूर्ण;

अटल पूर्णांक put_cfg_tlv_u32(काष्ठा wcn36xx *wcn, माप_प्रकार *len, u32 id, u32 value)
अणु
	काष्ठा wcn36xx_hal_cfg *entry;
	u32 *val;

	अगर (*len + माप(*entry) + माप(u32) >= WCN36XX_HAL_BUF_SIZE) अणु
		wcn36xx_err("Not enough room for TLV entry\n");
		वापस -ENOMEM;
	पूर्ण

	entry = (काष्ठा wcn36xx_hal_cfg *) (wcn->hal_buf + *len);
	entry->id = id;
	entry->len = माप(u32);
	entry->pad_bytes = 0;
	entry->reserve = 0;

	val = (u32 *) (entry + 1);
	*val = value;

	*len += माप(*entry) + माप(u32);

	वापस 0;
पूर्ण

अटल व्योम wcn36xx_smd_set_bss_nw_type(काष्ठा wcn36xx *wcn,
		काष्ठा ieee80211_sta *sta,
		काष्ठा wcn36xx_hal_config_bss_params *bss_params)
अणु
	अगर (NL80211_BAND_5GHZ == WCN36XX_BAND(wcn))
		bss_params->nw_type = WCN36XX_HAL_11A_NW_TYPE;
	अन्यथा अगर (sta && sta->ht_cap.ht_supported)
		bss_params->nw_type = WCN36XX_HAL_11N_NW_TYPE;
	अन्यथा अगर (sta && (sta->supp_rates[NL80211_BAND_2GHZ] & 0x7f))
		bss_params->nw_type = WCN36XX_HAL_11G_NW_TYPE;
	अन्यथा
		bss_params->nw_type = WCN36XX_HAL_11B_NW_TYPE;
पूर्ण

अटल अंतरभूत u8 is_cap_supported(अचिन्हित दीर्घ caps, अचिन्हित दीर्घ flag)
अणु
	वापस caps & flag ? 1 : 0;
पूर्ण

अटल व्योम wcn36xx_smd_set_bss_ht_params(काष्ठा ieee80211_vअगर *vअगर,
		काष्ठा ieee80211_sta *sta,
		काष्ठा wcn36xx_hal_config_bss_params *bss_params)
अणु
	अगर (sta && sta->ht_cap.ht_supported) अणु
		अचिन्हित दीर्घ caps = sta->ht_cap.cap;
		bss_params->ht = sta->ht_cap.ht_supported;
		bss_params->tx_channel_width_set = is_cap_supported(caps,
			IEEE80211_HT_CAP_SUP_WIDTH_20_40);
		bss_params->lsig_tx_op_protection_full_support =
			is_cap_supported(caps,
					 IEEE80211_HT_CAP_LSIG_TXOP_PROT);

		bss_params->ht_oper_mode = vअगर->bss_conf.ht_operation_mode;
		bss_params->lln_non_gf_coexist =
			!!(vअगर->bss_conf.ht_operation_mode &
			   IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT);
		/* IEEE80211_HT_STBC_PARAM_DUAL_CTS_PROT */
		bss_params->dual_cts_protection = 0;
		/* IEEE80211_HT_OP_MODE_PROTECTION_20MHZ */
		bss_params->ht20_coexist = 0;
	पूर्ण
पूर्ण

अटल व्योम
wcn36xx_smd_set_bss_vht_params(काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा ieee80211_sta *sta,
			       काष्ठा wcn36xx_hal_config_bss_params_v1 *bss)
अणु
	अगर (sta && sta->vht_cap.vht_supported)
		bss->vht_capable = 1;
पूर्ण

अटल व्योम wcn36xx_smd_set_sta_ht_params(काष्ठा ieee80211_sta *sta,
		काष्ठा wcn36xx_hal_config_sta_params *sta_params)
अणु
	अगर (sta->ht_cap.ht_supported) अणु
		अचिन्हित दीर्घ caps = sta->ht_cap.cap;
		sta_params->ht_capable = sta->ht_cap.ht_supported;
		sta_params->tx_channel_width_set = is_cap_supported(caps,
			IEEE80211_HT_CAP_SUP_WIDTH_20_40);
		sta_params->lsig_txop_protection = is_cap_supported(caps,
			IEEE80211_HT_CAP_LSIG_TXOP_PROT);

		sta_params->max_ampdu_size = sta->ht_cap.ampdu_factor;
		sta_params->max_ampdu_density = sta->ht_cap.ampdu_density;
		sta_params->max_amsdu_size = is_cap_supported(caps,
			IEEE80211_HT_CAP_MAX_AMSDU);
		sta_params->sgi_20Mhz = is_cap_supported(caps,
			IEEE80211_HT_CAP_SGI_20);
		sta_params->sgi_40mhz =	is_cap_supported(caps,
			IEEE80211_HT_CAP_SGI_40);
		sta_params->green_field_capable = is_cap_supported(caps,
			IEEE80211_HT_CAP_GRN_FLD);
		sta_params->delayed_ba_support = is_cap_supported(caps,
			IEEE80211_HT_CAP_DELAY_BA);
		sta_params->dsss_cck_mode_40mhz = is_cap_supported(caps,
			IEEE80211_HT_CAP_DSSSCCK40);
	पूर्ण
पूर्ण

अटल व्योम wcn36xx_smd_set_sta_vht_params(काष्ठा wcn36xx *wcn,
		काष्ठा ieee80211_sta *sta,
		काष्ठा wcn36xx_hal_config_sta_params_v1 *sta_params)
अणु
	अगर (sta->vht_cap.vht_supported) अणु
		अचिन्हित दीर्घ caps = sta->vht_cap.cap;

		sta_params->vht_capable = sta->vht_cap.vht_supported;
		sta_params->vht_ldpc_enabled =
			is_cap_supported(caps, IEEE80211_VHT_CAP_RXLDPC);
		अगर (get_feat_caps(wcn->fw_feat_caps, MU_MIMO)) अणु
			sta_params->vht_tx_mu_beamक्रमmee_capable =
				is_cap_supported(caps, IEEE80211_VHT_CAP_MU_BEAMFORMER_CAPABLE);
			अगर (sta_params->vht_tx_mu_beamक्रमmee_capable)
			       sta_params->vht_tx_bf_enabled = 1;
		पूर्ण अन्यथा अणु
			sta_params->vht_tx_mu_beamक्रमmee_capable = 0;
		पूर्ण
		sta_params->vht_tx_channel_width_set = 0;
	पूर्ण
पूर्ण

अटल व्योम wcn36xx_smd_set_sta_ht_ldpc_params(काष्ठा ieee80211_sta *sta,
		काष्ठा wcn36xx_hal_config_sta_params_v1 *sta_params)
अणु
	अगर (sta->ht_cap.ht_supported) अणु
		sta_params->ht_ldpc_enabled =
			is_cap_supported(sta->ht_cap.cap, IEEE80211_HT_CAP_LDPC_CODING);
	पूर्ण
पूर्ण

अटल व्योम wcn36xx_smd_set_sta_शेष_ht_params(
		काष्ठा wcn36xx_hal_config_sta_params *sta_params)
अणु
	sta_params->ht_capable = 1;
	sta_params->tx_channel_width_set = 1;
	sta_params->lsig_txop_protection = 1;
	sta_params->max_ampdu_size = 3;
	sta_params->max_ampdu_density = 5;
	sta_params->max_amsdu_size = 0;
	sta_params->sgi_20Mhz = 1;
	sta_params->sgi_40mhz = 1;
	sta_params->green_field_capable = 1;
	sta_params->delayed_ba_support = 0;
	sta_params->dsss_cck_mode_40mhz = 1;
पूर्ण

अटल व्योम wcn36xx_smd_set_sta_शेष_vht_params(काष्ठा wcn36xx *wcn,
		काष्ठा wcn36xx_hal_config_sta_params_v1 *sta_params)
अणु
	अगर (wcn->rf_id == RF_IRIS_WCN3680) अणु
		sta_params->vht_capable = 1;
		sta_params->vht_tx_mu_beamक्रमmee_capable = 1;
	पूर्ण अन्यथा अणु
		sta_params->vht_capable = 0;
		sta_params->vht_tx_mu_beamक्रमmee_capable = 0;
	पूर्ण

	sta_params->vht_ldpc_enabled = 0;
	sta_params->vht_tx_channel_width_set = 0;
	sta_params->vht_tx_bf_enabled = 0;
पूर्ण

अटल व्योम wcn36xx_smd_set_sta_शेष_ht_ldpc_params(काष्ठा wcn36xx *wcn,
		काष्ठा wcn36xx_hal_config_sta_params_v1 *sta_params)
अणु
	अगर (wcn->rf_id == RF_IRIS_WCN3680)
		sta_params->ht_ldpc_enabled = 1;
	अन्यथा
		sta_params->ht_ldpc_enabled = 0;
पूर्ण

अटल व्योम wcn36xx_smd_set_sta_params(काष्ठा wcn36xx *wcn,
		काष्ठा ieee80211_vअगर *vअगर,
		काष्ठा ieee80211_sta *sta,
		काष्ठा wcn36xx_hal_config_sta_params *sta_params)
अणु
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	काष्ठा wcn36xx_sta *sta_priv = शून्य;
	अगर (vअगर->type == NL80211_IFTYPE_ADHOC ||
	    vअगर->type == NL80211_IFTYPE_AP ||
	    vअगर->type == NL80211_IFTYPE_MESH_POINT) अणु
		sta_params->type = 1;
		sta_params->sta_index = WCN36XX_HAL_STA_INVALID_IDX;
	पूर्ण अन्यथा अणु
		sta_params->type = 0;
		sta_params->sta_index = vअगर_priv->self_sta_index;
	पूर्ण

	sta_params->listen_पूर्णांकerval = WCN36XX_LISTEN_INTERVAL(wcn);

	/*
	 * In STA mode ieee80211_sta contains bssid and ieee80211_vअगर
	 * contains our mac address. In  AP mode we are bssid so vअगर
	 * contains bssid and ieee80211_sta contains mac.
	 */
	अगर (NL80211_IFTYPE_STATION == vअगर->type)
		स_नकल(&sta_params->mac, vअगर->addr, ETH_ALEN);
	अन्यथा
		स_नकल(&sta_params->bssid, vअगर->addr, ETH_ALEN);

	sta_params->encrypt_type = vअगर_priv->encrypt_type;
	sta_params->लघु_preamble_supported = true;

	sta_params->rअगरs_mode = 0;
	sta_params->rmf = 0;
	sta_params->action = 0;
	sta_params->uapsd = 0;
	sta_params->mimo_ps = WCN36XX_HAL_HT_MIMO_PS_STATIC;
	sta_params->max_ampdu_duration = 0;
	sta_params->bssid_index = vअगर_priv->bss_index;
	sta_params->p2p = 0;

	अगर (sta) अणु
		sta_priv = wcn36xx_sta_to_priv(sta);
		अगर (NL80211_IFTYPE_STATION == vअगर->type)
			स_नकल(&sta_params->bssid, sta->addr, ETH_ALEN);
		अन्यथा
			स_नकल(&sta_params->mac, sta->addr, ETH_ALEN);
		sta_params->wmm_enabled = sta->wme;
		sta_params->max_sp_len = sta->max_sp;
		sta_params->aid = sta_priv->aid;
		wcn36xx_smd_set_sta_ht_params(sta, sta_params);
		स_नकल(&sta_params->supported_rates, &sta_priv->supported_rates,
			माप(काष्ठा wcn36xx_hal_supported_rates));
	पूर्ण अन्यथा अणु
		wcn36xx_set_शेष_rates((काष्ठा wcn36xx_hal_supported_rates *)
					  &sta_params->supported_rates);
		wcn36xx_smd_set_sta_शेष_ht_params(sta_params);
	पूर्ण
पूर्ण

अटल पूर्णांक wcn36xx_smd_send_and_रुको(काष्ठा wcn36xx *wcn, माप_प्रकार len)
अणु
	पूर्णांक ret;
	अचिन्हित दीर्घ start;
	काष्ठा wcn36xx_hal_msg_header *hdr =
		(काष्ठा wcn36xx_hal_msg_header *)wcn->hal_buf;
	u16 req_type = hdr->msg_type;

	wcn36xx_dbg_dump(WCN36XX_DBG_SMD_DUMP, "HAL >>> ", wcn->hal_buf, len);

	init_completion(&wcn->hal_rsp_compl);
	start = jअगरfies;
	ret = rpmsg_send(wcn->smd_channel, wcn->hal_buf, len);
	अगर (ret) अणु
		wcn36xx_err("HAL TX failed for req %d\n", req_type);
		जाओ out;
	पूर्ण
	अगर (रुको_क्रम_completion_समयout(&wcn->hal_rsp_compl,
		msecs_to_jअगरfies(HAL_MSG_TIMEOUT)) <= 0) अणु
		wcn36xx_err("Timeout! No SMD response to req %d in %dms\n",
			    req_type, HAL_MSG_TIMEOUT);
		ret = -ETIME;
		जाओ out;
	पूर्ण
	wcn36xx_dbg(WCN36XX_DBG_SMD,
		    "SMD command (req %d, rsp %d) completed in %dms\n",
		    req_type, hdr->msg_type,
		    jअगरfies_to_msecs(jअगरfies - start));
out:
	वापस ret;
पूर्ण

अटल व्योम init_hal_msg(काष्ठा wcn36xx_hal_msg_header *hdr,
			 क्रमागत wcn36xx_hal_host_msg_type msg_type,
			 माप_प्रकार msg_size)
अणु
	स_रखो(hdr, 0, msg_size + माप(*hdr));
	hdr->msg_type = msg_type;
	hdr->msg_version = WCN36XX_HAL_MSG_VERSION0;
	hdr->len = msg_size + माप(*hdr);
पूर्ण

#घोषणा __INIT_HAL_MSG(msg_body, type, version) \
	करो अणु								\
		स_रखो(&msg_body, 0, माप(msg_body));			\
		msg_body.header.msg_type = type;			\
		msg_body.header.msg_version = version;			\
		msg_body.header.len = माप(msg_body);			\
	पूर्ण जबतक (0)							\

#घोषणा INIT_HAL_MSG(msg_body, type)	\
	__INIT_HAL_MSG(msg_body, type, WCN36XX_HAL_MSG_VERSION0)

#घोषणा INIT_HAL_MSG_V1(msg_body, type) \
	__INIT_HAL_MSG(msg_body, type, WCN36XX_HAL_MSG_VERSION1)

#घोषणा INIT_HAL_PTT_MSG(p_msg_body, ppt_msg_len) \
	करो अणु \
		स_रखो(p_msg_body, 0, माप(*p_msg_body) + ppt_msg_len); \
		p_msg_body->header.msg_type = WCN36XX_HAL_PROCESS_PTT_REQ; \
		p_msg_body->header.msg_version = WCN36XX_HAL_MSG_VERSION0; \
		p_msg_body->header.len = माप(*p_msg_body) + ppt_msg_len; \
	पूर्ण जबतक (0)

#घोषणा PREPARE_HAL_BUF(send_buf, msg_body) \
	करो अणु							\
		स_रखो(send_buf, 0, msg_body.header.len);	\
		स_नकल(send_buf, &msg_body, माप(msg_body));	\
	पूर्ण जबतक (0)						\

#घोषणा PREPARE_HAL_PTT_MSG_BUF(send_buf, p_msg_body) \
	करो अणु							\
		स_नकल(send_buf, p_msg_body, p_msg_body->header.len); \
	पूर्ण जबतक (0)

अटल पूर्णांक wcn36xx_smd_rsp_status_check(व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wcn36xx_fw_msg_status_rsp *rsp;

	अगर (len < माप(काष्ठा wcn36xx_hal_msg_header) +
	    माप(काष्ठा wcn36xx_fw_msg_status_rsp))
		वापस -EIO;

	rsp = (काष्ठा wcn36xx_fw_msg_status_rsp *)
		(buf + माप(काष्ठा wcn36xx_hal_msg_header));

	अगर (WCN36XX_FW_MSG_RESULT_SUCCESS != rsp->status)
		वापस rsp->status;

	वापस 0;
पूर्ण

पूर्णांक wcn36xx_smd_load_nv(काष्ठा wcn36xx *wcn)
अणु
	काष्ठा nv_data *nv_d;
	काष्ठा wcn36xx_hal_nv_img_करोwnload_req_msg msg_body;
	पूर्णांक fw_bytes_left;
	पूर्णांक ret;
	u16 fm_offset = 0;

	अगर (!wcn->nv) अणु
		ret = request_firmware(&wcn->nv, WLAN_NV_खाता, wcn->dev);
		अगर (ret) अणु
			wcn36xx_err("Failed to load nv file %s: %d\n",
				      WLAN_NV_खाता, ret);
			जाओ out;
		पूर्ण
	पूर्ण

	nv_d = (काष्ठा nv_data *)wcn->nv->data;
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_DOWNLOAD_NV_REQ);

	msg_body.header.len += WCN36XX_NV_FRAGMENT_SIZE;

	msg_body.frag_number = 0;
	/* hal_buf must be रक्षित with  mutex */
	mutex_lock(&wcn->hal_mutex);

	करो अणु
		fw_bytes_left = wcn->nv->size - fm_offset - 4;
		अगर (fw_bytes_left > WCN36XX_NV_FRAGMENT_SIZE) अणु
			msg_body.last_fragment = 0;
			msg_body.nv_img_buffer_size = WCN36XX_NV_FRAGMENT_SIZE;
		पूर्ण अन्यथा अणु
			msg_body.last_fragment = 1;
			msg_body.nv_img_buffer_size = fw_bytes_left;

			/* Do not क्रमget update general message len */
			msg_body.header.len = माप(msg_body) + fw_bytes_left;

		पूर्ण

		/* Add load NV request message header */
		स_नकल(wcn->hal_buf, &msg_body,	माप(msg_body));

		/* Add NV body itself */
		स_नकल(wcn->hal_buf + माप(msg_body),
		       &nv_d->table + fm_offset,
		       msg_body.nv_img_buffer_size);

		ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
		अगर (ret)
			जाओ out_unlock;
		ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf,
						   wcn->hal_rsp_len);
		अगर (ret) अणु
			wcn36xx_err("hal_load_nv response failed err=%d\n",
				    ret);
			जाओ out_unlock;
		पूर्ण
		msg_body.frag_number++;
		fm_offset += WCN36XX_NV_FRAGMENT_SIZE;

	पूर्ण जबतक (msg_body.last_fragment != 1);

out_unlock:
	mutex_unlock(&wcn->hal_mutex);
out:	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_start_rsp(काष्ठा wcn36xx *wcn, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_mac_start_rsp_msg *rsp;

	अगर (len < माप(*rsp))
		वापस -EIO;

	rsp = (काष्ठा wcn36xx_hal_mac_start_rsp_msg *)buf;

	अगर (WCN36XX_FW_MSG_RESULT_SUCCESS != rsp->start_rsp_params.status)
		वापस -EIO;

	स_नकल(wcn->crm_version, rsp->start_rsp_params.crm_version,
	       WCN36XX_HAL_VERSION_LENGTH);
	स_नकल(wcn->wlan_version, rsp->start_rsp_params.wlan_version,
	       WCN36XX_HAL_VERSION_LENGTH);

	/* null terminate the strings, just in हाल */
	wcn->crm_version[WCN36XX_HAL_VERSION_LENGTH] = '\0';
	wcn->wlan_version[WCN36XX_HAL_VERSION_LENGTH] = '\0';

	wcn->fw_revision = rsp->start_rsp_params.version.revision;
	wcn->fw_version = rsp->start_rsp_params.version.version;
	wcn->fw_minor = rsp->start_rsp_params.version.minor;
	wcn->fw_major = rsp->start_rsp_params.version.major;

	अगर (wcn->first_boot) अणु
		wcn->first_boot = false;
		wcn36xx_info("firmware WLAN version '%s' and CRM version '%s'\n",
			     wcn->wlan_version, wcn->crm_version);

		wcn36xx_info("firmware API %u.%u.%u.%u, %u stations, %u bssids\n",
			     wcn->fw_major, wcn->fw_minor,
			     wcn->fw_version, wcn->fw_revision,
			     rsp->start_rsp_params.stations,
			     rsp->start_rsp_params.bssids);
	पूर्ण
	वापस 0;
पूर्ण

पूर्णांक wcn36xx_smd_start(काष्ठा wcn36xx *wcn)
अणु
	काष्ठा wcn36xx_hal_mac_start_req_msg msg_body, *body;
	पूर्णांक ret;
	पूर्णांक i;
	माप_प्रकार len;
	पूर्णांक cfg_elements;
	अटल काष्ठा wcn36xx_cfg_val *cfg_vals;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_START_REQ);

	msg_body.params.type = DRIVER_TYPE_PRODUCTION;
	msg_body.params.len = 0;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	body = (काष्ठा wcn36xx_hal_mac_start_req_msg *)wcn->hal_buf;
	len = body->header.len;

	अगर (wcn->rf_id == RF_IRIS_WCN3680) अणु
		cfg_vals = wcn3680_cfg_vals;
		cfg_elements = ARRAY_SIZE(wcn3680_cfg_vals);
	पूर्ण अन्यथा अणु
		cfg_vals = wcn36xx_cfg_vals;
		cfg_elements = ARRAY_SIZE(wcn36xx_cfg_vals);
	पूर्ण

	क्रम (i = 0; i < cfg_elements; i++) अणु
		ret = put_cfg_tlv_u32(wcn, &len, cfg_vals[i].cfg_id,
				      cfg_vals[i].value);
		अगर (ret)
			जाओ out;
	पूर्ण
	body->header.len = len;
	body->params.len = len - माप(*body);

	wcn36xx_dbg(WCN36XX_DBG_HAL, "hal start type %d\n",
		    msg_body.params.type);

	ret = wcn36xx_smd_send_and_रुको(wcn, body->header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_start failed\n");
		जाओ out;
	पूर्ण

	ret = wcn36xx_smd_start_rsp(wcn, wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_start response failed err=%d\n", ret);
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_stop(काष्ठा wcn36xx *wcn)
अणु
	काष्ठा wcn36xx_hal_mac_stop_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_STOP_REQ);

	msg_body.stop_req_params.reason = HAL_STOP_TYPE_RF_KILL;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_stop failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_stop response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_init_scan(काष्ठा wcn36xx *wcn, क्रमागत wcn36xx_hal_sys_mode mode,
			  काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	काष्ठा wcn36xx_hal_init_scan_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_INIT_SCAN_REQ);

	msg_body.mode = mode;
	अगर (vअगर_priv->bss_index != WCN36XX_HAL_BSS_INVALID_IDX) अणु
		/* Notअगरy BSSID with null DATA packet */
		msg_body.frame_type = 2;
		msg_body.notअगरy = 1;
		msg_body.scan_entry.bss_index[0] = vअगर_priv->bss_index;
		msg_body.scan_entry.active_bss_count = 1;
	पूर्ण

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL, "hal init scan mode %d\n", msg_body.mode);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_init_scan failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_init_scan response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_start_scan(काष्ठा wcn36xx *wcn, u8 scan_channel)
अणु
	काष्ठा wcn36xx_hal_start_scan_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_START_SCAN_REQ);

	msg_body.scan_channel = scan_channel;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL, "hal start scan channel %d\n",
		    msg_body.scan_channel);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_start_scan failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_start_scan response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_end_scan(काष्ठा wcn36xx *wcn, u8 scan_channel)
अणु
	काष्ठा wcn36xx_hal_end_scan_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_END_SCAN_REQ);

	msg_body.scan_channel = scan_channel;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL, "hal end scan channel %d\n",
		    msg_body.scan_channel);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_end_scan failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_end_scan response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_finish_scan(काष्ठा wcn36xx *wcn,
			    क्रमागत wcn36xx_hal_sys_mode mode,
			    काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	काष्ठा wcn36xx_hal_finish_scan_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_FINISH_SCAN_REQ);

	msg_body.mode = mode;
	msg_body.oper_channel = WCN36XX_HW_CHANNEL(wcn);
	अगर (vअगर_priv->bss_index != WCN36XX_HAL_BSS_INVALID_IDX) अणु
		/* Notअगरy BSSID with null data packet */
		msg_body.notअगरy = 1;
		msg_body.frame_type = 2;
		msg_body.scan_entry.bss_index[0] = vअगर_priv->bss_index;
		msg_body.scan_entry.active_bss_count = 1;
	पूर्ण

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL, "hal finish scan mode %d\n",
		    msg_body.mode);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_finish_scan failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_finish_scan response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_start_hw_scan(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा cfg80211_scan_request *req)
अणु
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	काष्ठा wcn36xx_hal_start_scan_offload_req_msg *msg_body;
	पूर्णांक ret, i;

	अगर (req->ie_len > WCN36XX_MAX_SCAN_IE_LEN)
		वापस -EINVAL;

	mutex_lock(&wcn->hal_mutex);
	msg_body = kzalloc(माप(*msg_body), GFP_KERNEL);
	अगर (!msg_body) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	INIT_HAL_MSG((*msg_body), WCN36XX_HAL_START_SCAN_OFFLOAD_REQ);

	msg_body->scan_type = WCN36XX_HAL_SCAN_TYPE_ACTIVE;
	msg_body->min_ch_समय = 30;
	msg_body->max_ch_समय = 100;
	msg_body->scan_hidden = 1;
	स_नकल(msg_body->mac, vअगर->addr, ETH_ALEN);
	msg_body->bss_type = vअगर_priv->bss_type;
	msg_body->p2p_search = vअगर->p2p;

	msg_body->num_ssid = min_t(u8, req->n_ssids, ARRAY_SIZE(msg_body->ssids));
	क्रम (i = 0; i < msg_body->num_ssid; i++) अणु
		msg_body->ssids[i].length = min_t(u8, req->ssids[i].ssid_len,
						माप(msg_body->ssids[i].ssid));
		स_नकल(msg_body->ssids[i].ssid, req->ssids[i].ssid,
		       msg_body->ssids[i].length);
	पूर्ण

	msg_body->num_channel = min_t(u8, req->n_channels,
				     माप(msg_body->channels));
	क्रम (i = 0; i < msg_body->num_channel; i++) अणु
		msg_body->channels[i] =
			HW_VALUE_CHANNEL(req->channels[i]->hw_value);
	पूर्ण

	msg_body->header.len -= WCN36XX_MAX_SCAN_IE_LEN;

	अगर (req->ie_len > 0) अणु
		msg_body->ie_len = req->ie_len;
		msg_body->header.len += req->ie_len;
		स_नकल(msg_body->ie, req->ie, req->ie_len);
	पूर्ण

	PREPARE_HAL_BUF(wcn->hal_buf, (*msg_body));

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal start hw-scan (channels: %u; ssids: %u; p2p: %s)\n",
		    msg_body->num_channel, msg_body->num_ssid,
		    msg_body->p2p_search ? "yes" : "no");

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body->header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_start_scan_offload failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_start_scan_offload response failed err=%d\n",
			    ret);
		जाओ out;
	पूर्ण
out:
	kमुक्त(msg_body);
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_stop_hw_scan(काष्ठा wcn36xx *wcn)
अणु
	काष्ठा wcn36xx_hal_stop_scan_offload_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_STOP_SCAN_OFFLOAD_REQ);
	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL, "hal stop hw-scan\n");

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_stop_scan_offload failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_stop_scan_offload response failed err=%d\n",
			    ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_चयन_channel_rsp(व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_चयन_channel_rsp_msg *rsp;
	पूर्णांक ret;

	ret = wcn36xx_smd_rsp_status_check(buf, len);
	अगर (ret)
		वापस ret;
	rsp = (काष्ठा wcn36xx_hal_चयन_channel_rsp_msg *)buf;
	wcn36xx_dbg(WCN36XX_DBG_HAL, "channel switched to: %d, status: %d\n",
		    rsp->channel_number, rsp->status);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_चयन_channel(काष्ठा wcn36xx *wcn,
			       काष्ठा ieee80211_vअगर *vअगर, पूर्णांक ch)
अणु
	काष्ठा wcn36xx_hal_चयन_channel_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_CH_SWITCH_REQ);

	msg_body.channel_number = (u8)ch;
	msg_body.tx_mgmt_घातer = 0xbf;
	msg_body.max_tx_घातer = 0xbf;
	स_नकल(msg_body.self_sta_mac_addr, vअगर->addr, ETH_ALEN);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_switch_channel failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_चयन_channel_rsp(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_switch_channel response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_process_ptt_msg_rsp(व्योम *buf, माप_प्रकार len,
					   व्योम **p_ptt_rsp_msg)
अणु
	काष्ठा wcn36xx_hal_process_ptt_msg_rsp_msg *rsp;
	पूर्णांक ret;

	ret = wcn36xx_smd_rsp_status_check(buf, len);
	अगर (ret)
		वापस ret;

	rsp = (काष्ठा wcn36xx_hal_process_ptt_msg_rsp_msg *)buf;

	wcn36xx_dbg(WCN36XX_DBG_HAL, "process ptt msg responded with length %d\n",
		    rsp->header.len);
	wcn36xx_dbg_dump(WCN36XX_DBG_HAL_DUMP, "HAL_PTT_MSG_RSP:", rsp->ptt_msg,
			 rsp->header.len - माप(rsp->ptt_msg_resp_status));

	अगर (rsp->header.len > 0) अणु
		*p_ptt_rsp_msg = kmemdup(rsp->ptt_msg, rsp->header.len,
					 GFP_ATOMIC);
		अगर (!*p_ptt_rsp_msg)
			वापस -ENOMEM;
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_process_ptt_msg(काष्ठा wcn36xx *wcn,
				काष्ठा ieee80211_vअगर *vअगर, व्योम *ptt_msg, माप_प्रकार len,
		व्योम **ptt_rsp_msg)
अणु
	काष्ठा wcn36xx_hal_process_ptt_msg_req_msg *p_msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	p_msg_body = kदो_स्मृति(
		माप(काष्ठा wcn36xx_hal_process_ptt_msg_req_msg) + len,
		GFP_ATOMIC);
	अगर (!p_msg_body) अणु
		ret = -ENOMEM;
		जाओ out_nomem;
	पूर्ण
	INIT_HAL_PTT_MSG(p_msg_body, len);

	स_नकल(&p_msg_body->ptt_msg, ptt_msg, len);

	PREPARE_HAL_PTT_MSG_BUF(wcn->hal_buf, p_msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, p_msg_body->header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_process_ptt_msg failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_process_ptt_msg_rsp(wcn->hal_buf, wcn->hal_rsp_len,
					      ptt_rsp_msg);
	अगर (ret) अणु
		wcn36xx_err("process_ptt_msg response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	kमुक्त(p_msg_body);
out_nomem:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_update_scan_params_rsp(व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_update_scan_params_resp *rsp;

	rsp = (काष्ठा wcn36xx_hal_update_scan_params_resp *)buf;

	/* Remove the PNO version bit */
	rsp->status &= (~(WCN36XX_FW_MSG_PNO_VERSION_MASK));

	अगर (WCN36XX_FW_MSG_RESULT_SUCCESS != rsp->status) अणु
		wcn36xx_warn("error response from update scan\n");
		वापस rsp->status;
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wcn36xx_smd_update_scan_params(काष्ठा wcn36xx *wcn,
				   u8 *channels, माप_प्रकार channel_count)
अणु
	काष्ठा wcn36xx_hal_update_scan_params_req_ex msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_UPDATE_SCAN_PARAM_REQ);

	msg_body.करोt11d_enabled	= false;
	msg_body.करोt11d_resolved = true;

	msg_body.channel_count = channel_count;
	स_नकल(msg_body.channels, channels, channel_count);
	msg_body.active_min_ch_समय = 60;
	msg_body.active_max_ch_समय = 120;
	msg_body.passive_min_ch_समय = 60;
	msg_body.passive_max_ch_समय = 110;
	msg_body.state = PHY_SINGLE_CHANNEL_CENTERED;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal update scan params channel_count %d\n",
		    msg_body.channel_count);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_update_scan_params failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_update_scan_params_rsp(wcn->hal_buf,
						 wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_update_scan_params response failed err=%d\n",
			    ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_add_sta_self_rsp(काष्ठा wcn36xx *wcn,
					काष्ठा ieee80211_vअगर *vअगर,
					व्योम *buf,
					माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_add_sta_self_rsp_msg *rsp;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);

	अगर (len < माप(*rsp))
		वापस -EINVAL;

	rsp = (काष्ठा wcn36xx_hal_add_sta_self_rsp_msg *)buf;

	अगर (rsp->status != WCN36XX_FW_MSG_RESULT_SUCCESS) अणु
		wcn36xx_warn("hal add sta self failure: %d\n",
			     rsp->status);
		वापस rsp->status;
	पूर्ण

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal add sta self status %d self_sta_index %d dpu_index %d\n",
		    rsp->status, rsp->self_sta_index, rsp->dpu_index);

	vअगर_priv->self_sta_index = rsp->self_sta_index;
	vअगर_priv->self_dpu_desc_index = rsp->dpu_index;

	वापस 0;
पूर्ण

पूर्णांक wcn36xx_smd_add_sta_self(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx_hal_add_sta_self_req msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_ADD_STA_SELF_REQ);

	स_नकल(&msg_body.self_addr, vअगर->addr, ETH_ALEN);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal add sta self self_addr %pM status %d\n",
		    msg_body.self_addr, msg_body.status);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_add_sta_self failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_add_sta_self_rsp(wcn,
					   vअगर,
					   wcn->hal_buf,
					   wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_add_sta_self response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_delete_sta_self(काष्ठा wcn36xx *wcn, u8 *addr)
अणु
	काष्ठा wcn36xx_hal_del_sta_self_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_DEL_STA_SELF_REQ);

	स_नकल(&msg_body.self_addr, addr, ETH_ALEN);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_delete_sta_self failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_delete_sta_self response failed err=%d\n",
			    ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_delete_sta(काष्ठा wcn36xx *wcn, u8 sta_index)
अणु
	काष्ठा wcn36xx_hal_delete_sta_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_DELETE_STA_REQ);

	msg_body.sta_index = sta_index;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal delete sta sta_index %d\n",
		    msg_body.sta_index);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_delete_sta failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_delete_sta response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_join_rsp(व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_join_rsp_msg *rsp;

	अगर (wcn36xx_smd_rsp_status_check(buf, len))
		वापस -EIO;

	rsp = (काष्ठा wcn36xx_hal_join_rsp_msg *)buf;

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal rsp join status %d tx_mgmt_power %d\n",
		    rsp->status, rsp->tx_mgmt_घातer);

	वापस 0;
पूर्ण

पूर्णांक wcn36xx_smd_join(काष्ठा wcn36xx *wcn, स्थिर u8 *bssid, u8 *vअगर, u8 ch)
अणु
	काष्ठा wcn36xx_hal_join_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_JOIN_REQ);

	स_नकल(&msg_body.bssid, bssid, ETH_ALEN);
	स_नकल(&msg_body.self_sta_mac_addr, vअगर, ETH_ALEN);
	msg_body.channel = ch;

	अगर (conf_is_ht40_minus(&wcn->hw->conf))
		msg_body.secondary_channel_offset =
			PHY_DOUBLE_CHANNEL_HIGH_PRIMARY;
	अन्यथा अगर (conf_is_ht40_plus(&wcn->hw->conf))
		msg_body.secondary_channel_offset =
			PHY_DOUBLE_CHANNEL_LOW_PRIMARY;
	अन्यथा
		msg_body.secondary_channel_offset =
			PHY_SINGLE_CHANNEL_CENTERED;

	msg_body.link_state = WCN36XX_HAL_LINK_PREASSOC_STATE;

	msg_body.max_tx_घातer = 0xbf;
	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal join req bssid %pM self_sta_mac_addr %pM channel %d link_state %d\n",
		    msg_body.bssid, msg_body.self_sta_mac_addr,
		    msg_body.channel, msg_body.link_state);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_join failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_join_rsp(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_join response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_set_link_st(काष्ठा wcn36xx *wcn, स्थिर u8 *bssid,
			    स्थिर u8 *sta_mac,
			    क्रमागत wcn36xx_hal_link_state state)
अणु
	काष्ठा wcn36xx_hal_set_link_state_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SET_LINK_ST_REQ);

	स_नकल(&msg_body.bssid, bssid, ETH_ALEN);
	स_नकल(&msg_body.self_mac_addr, sta_mac, ETH_ALEN);
	msg_body.state = state;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal set link state bssid %pM self_mac_addr %pM state %d\n",
		    msg_body.bssid, msg_body.self_mac_addr, msg_body.state);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_set_link_st failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_set_link_st response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल व्योम wcn36xx_smd_convert_sta_to_v1(काष्ठा wcn36xx *wcn,
			स्थिर काष्ठा wcn36xx_hal_config_sta_params *orig,
			काष्ठा wcn36xx_hal_config_sta_params_v1 *v1)
अणु
	/* convert orig to v1 क्रमmat */
	स_नकल(&v1->bssid, orig->bssid, ETH_ALEN);
	स_नकल(&v1->mac, orig->mac, ETH_ALEN);
	v1->aid = orig->aid;
	v1->type = orig->type;
	v1->लघु_preamble_supported = orig->लघु_preamble_supported;
	v1->listen_पूर्णांकerval = orig->listen_पूर्णांकerval;
	v1->wmm_enabled = orig->wmm_enabled;
	v1->ht_capable = orig->ht_capable;
	v1->tx_channel_width_set = orig->tx_channel_width_set;
	v1->rअगरs_mode = orig->rअगरs_mode;
	v1->lsig_txop_protection = orig->lsig_txop_protection;
	v1->max_ampdu_size = orig->max_ampdu_size;
	v1->max_ampdu_density = orig->max_ampdu_density;
	v1->sgi_40mhz = orig->sgi_40mhz;
	v1->sgi_20Mhz = orig->sgi_20Mhz;
	v1->rmf = orig->rmf;
	v1->encrypt_type = orig->encrypt_type;
	v1->action = orig->action;
	v1->uapsd = orig->uapsd;
	v1->max_sp_len = orig->max_sp_len;
	v1->green_field_capable = orig->green_field_capable;
	v1->mimo_ps = orig->mimo_ps;
	v1->delayed_ba_support = orig->delayed_ba_support;
	v1->max_ampdu_duration = orig->max_ampdu_duration;
	v1->dsss_cck_mode_40mhz = orig->dsss_cck_mode_40mhz;
	स_नकल(&v1->supported_rates, &orig->supported_rates,
	       माप(orig->supported_rates));
	v1->sta_index = orig->sta_index;
	v1->bssid_index = orig->bssid_index;
	v1->p2p = orig->p2p;
पूर्ण

अटल व्योम
wcn36xx_smd_set_sta_params_v1(काष्ठा wcn36xx *wcn,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta,
			      काष्ठा wcn36xx_hal_config_sta_params_v1 *sta_par)
अणु
	काष्ठा wcn36xx_sta *sta_priv = शून्य;
	काष्ठा wcn36xx_hal_config_sta_params sta_par_v0;

	wcn36xx_smd_set_sta_params(wcn, vअगर, sta, &sta_par_v0);
	wcn36xx_smd_convert_sta_to_v1(wcn, &sta_par_v0, sta_par);

	अगर (sta) अणु
		sta_priv = wcn36xx_sta_to_priv(sta);
		wcn36xx_smd_set_sta_vht_params(wcn, sta, sta_par);
		wcn36xx_smd_set_sta_ht_ldpc_params(sta, sta_par);
		स_नकल(&sta_par->supported_rates, &sta_priv->supported_rates,
		       माप(sta_par->supported_rates));
	पूर्ण अन्यथा अणु
		wcn36xx_set_शेष_rates_v1(&sta_par->supported_rates);
		wcn36xx_smd_set_sta_शेष_vht_params(wcn, sta_par);
		wcn36xx_smd_set_sta_शेष_ht_ldpc_params(wcn, sta_par);
	पूर्ण
पूर्ण

अटल पूर्णांक wcn36xx_smd_config_sta_rsp(काष्ठा wcn36xx *wcn,
				      काष्ठा ieee80211_sta *sta,
				      व्योम *buf,
				      माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_config_sta_rsp_msg *rsp;
	काष्ठा config_sta_rsp_params *params;
	काष्ठा wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);

	अगर (len < माप(*rsp))
		वापस -EINVAL;

	rsp = (काष्ठा wcn36xx_hal_config_sta_rsp_msg *)buf;
	params = &rsp->params;

	अगर (params->status != WCN36XX_FW_MSG_RESULT_SUCCESS) अणु
		wcn36xx_warn("hal config sta response failure: %d\n",
			     params->status);
		वापस -EIO;
	पूर्ण

	sta_priv->sta_index = params->sta_index;
	sta_priv->dpu_desc_index = params->dpu_index;
	sta_priv->ucast_dpu_sign = params->uc_ucast_sig;

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal config sta rsp status %d sta_index %d bssid_index %d uc_ucast_sig %d p2p %d\n",
		    params->status, params->sta_index, params->bssid_index,
		    params->uc_ucast_sig, params->p2p);

	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_smd_config_sta_v1(काष्ठा wcn36xx *wcn,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wcn36xx_hal_config_sta_req_msg_v1 msg_body;
	काष्ठा wcn36xx_hal_config_sta_params_v1 *sta_params;

	अगर (wcn->rf_id == RF_IRIS_WCN3680) अणु
		INIT_HAL_MSG_V1(msg_body, WCN36XX_HAL_CONFIG_STA_REQ);
	पूर्ण अन्यथा अणु
		INIT_HAL_MSG(msg_body, WCN36XX_HAL_CONFIG_STA_REQ);
		msg_body.header.len -= WCN36XX_DIFF_STA_PARAMS_V1_NOVHT;
	पूर्ण

	sta_params = &msg_body.sta_params;

	wcn36xx_smd_set_sta_params_v1(wcn, vअगर, sta, sta_params);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal config sta v1 action %d sta_index %d bssid_index %d bssid %pM type %d mac %pM aid %d\n",
		    sta_params->action, sta_params->sta_index, sta_params->bssid_index,
		    sta_params->bssid, sta_params->type, sta_params->mac, sta_params->aid);

	वापस wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
पूर्ण

अटल पूर्णांक wcn36xx_smd_config_sta_v0(काष्ठा wcn36xx *wcn,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wcn36xx_hal_config_sta_req_msg msg;
	काष्ठा wcn36xx_hal_config_sta_params *sta_params;

	INIT_HAL_MSG(msg, WCN36XX_HAL_CONFIG_STA_REQ);

	sta_params = &msg.sta_params;

	wcn36xx_smd_set_sta_params(wcn, vअगर, sta, sta_params);

	PREPARE_HAL_BUF(wcn->hal_buf, msg);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal config sta action %d sta_index %d bssid_index %d bssid %pM type %d mac %pM aid %d\n",
		    sta_params->action, sta_params->sta_index,
		    sta_params->bssid_index, sta_params->bssid,
		    sta_params->type, sta_params->mac, sta_params->aid);

	वापस wcn36xx_smd_send_and_रुको(wcn, msg.header.len);
पूर्ण

पूर्णांक wcn36xx_smd_config_sta(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta)
अणु
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);

	अगर (!wcn36xx_is_fw_version(wcn, 1, 2, 2, 24))
		ret = wcn36xx_smd_config_sta_v1(wcn, vअगर, sta);
	अन्यथा
		ret = wcn36xx_smd_config_sta_v0(wcn, vअगर, sta);

	अगर (ret) अणु
		wcn36xx_err("Sending hal_config_sta failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_config_sta_rsp(wcn,
					 sta,
					 wcn->hal_buf,
					 wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_config_sta response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल व्योम wcn36xx_smd_set_bss_params(काष्ठा wcn36xx *wcn,
				       काष्ठा ieee80211_vअगर *vअगर,
				       काष्ठा ieee80211_sta *sta,
				       स्थिर u8 *bssid,
				       bool update,
				       काष्ठा wcn36xx_hal_config_bss_params *bss)
अणु
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);

	WARN_ON(is_zero_ether_addr(bssid));

	स_नकल(&bss->bssid, bssid, ETH_ALEN);

	स_नकल(bss->self_mac_addr, vअगर->addr, ETH_ALEN);

	अगर (vअगर->type == NL80211_IFTYPE_STATION) अणु
		bss->bss_type = WCN36XX_HAL_INFRASTRUCTURE_MODE;

		/* STA */
		bss->oper_mode = 1;
		bss->wcn36xx_hal_persona = WCN36XX_HAL_STA_MODE;
	पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_AP ||
		   vअगर->type == NL80211_IFTYPE_MESH_POINT) अणु
		bss->bss_type = WCN36XX_HAL_INFRA_AP_MODE;

		/* AP */
		bss->oper_mode = 0;
		bss->wcn36xx_hal_persona = WCN36XX_HAL_STA_SAP_MODE;
	पूर्ण अन्यथा अगर (vअगर->type == NL80211_IFTYPE_ADHOC) अणु
		bss->bss_type = WCN36XX_HAL_IBSS_MODE;

		/* STA */
		bss->oper_mode = 1;
	पूर्ण अन्यथा अणु
		wcn36xx_warn("Unknown type for bss config: %d\n", vअगर->type);
	पूर्ण

	अगर (vअगर->type == NL80211_IFTYPE_STATION)
		wcn36xx_smd_set_bss_nw_type(wcn, sta, bss);
	अन्यथा
		bss->nw_type = WCN36XX_HAL_11N_NW_TYPE;

	bss->लघु_slot_समय_supported = vअगर->bss_conf.use_लघु_slot;
	bss->lla_coexist = 0;
	bss->llb_coexist = 0;
	bss->llg_coexist = 0;
	bss->rअगरs_mode = 0;
	bss->beacon_पूर्णांकerval = vअगर->bss_conf.beacon_पूर्णांक;
	bss->dtim_period = vअगर_priv->dtim_period;

	wcn36xx_smd_set_bss_ht_params(vअगर, sta, bss);

	bss->oper_channel = WCN36XX_HW_CHANNEL(wcn);

	अगर (conf_is_ht40_minus(&wcn->hw->conf))
		bss->ext_channel = IEEE80211_HT_PARAM_CHA_SEC_BELOW;
	अन्यथा अगर (conf_is_ht40_plus(&wcn->hw->conf))
		bss->ext_channel = IEEE80211_HT_PARAM_CHA_SEC_ABOVE;
	अन्यथा
		bss->ext_channel = IEEE80211_HT_PARAM_CHA_SEC_NONE;

	bss->reserved = 0;

	/* wcn->ssid is only valid in AP and IBSS mode */
	bss->ssid.length = vअगर_priv->ssid.length;
	स_नकल(bss->ssid.ssid, vअगर_priv->ssid.ssid, vअगर_priv->ssid.length);

	bss->obss_prot_enabled = 0;
	bss->rmf = 0;
	bss->max_probe_resp_retry_limit = 0;
	bss->hidden_ssid = vअगर->bss_conf.hidden_ssid;
	bss->proxy_probe_resp = 0;
	bss->edca_params_valid = 0;

	/* FIXME: set acbe, acbk, acvi and acvo */

	bss->ext_set_sta_key_param_valid = 0;

	/* FIXME: set ext_set_sta_key_param */

	bss->spectrum_mgt_enable = 0;
	bss->tx_mgmt_घातer = 0;
	bss->max_tx_घातer = WCN36XX_MAX_POWER(wcn);
	bss->action = update;

	vअगर_priv->bss_type = bss->bss_type;
पूर्ण

अटल पूर्णांक wcn36xx_smd_config_bss_v1(काष्ठा wcn36xx *wcn,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta_80211,
				     स्थिर u8 *bssid,
				     bool update)
अणु
	काष्ठा wcn36xx_hal_config_bss_req_msg_v1 *msg_body;
	काष्ठा wcn36xx_hal_config_bss_params_v1 *bss;
	काष्ठा wcn36xx_hal_config_bss_params bss_v0;
	काष्ठा wcn36xx_hal_config_sta_params_v1 *sta;
	काष्ठा cfg80211_chan_def *chandef;
	पूर्णांक ret;

	msg_body = kzalloc(माप(*msg_body), GFP_KERNEL);
	अगर (!msg_body)
		वापस -ENOMEM;

	अगर (wcn->rf_id == RF_IRIS_WCN3680) अणु
		INIT_HAL_MSG_V1((*msg_body), WCN36XX_HAL_CONFIG_BSS_REQ);
	पूर्ण अन्यथा अणु
		INIT_HAL_MSG((*msg_body), WCN36XX_HAL_CONFIG_BSS_REQ);
		msg_body->header.len -= WCN36XX_DIFF_BSS_PARAMS_V1_NOVHT;
	पूर्ण

	bss = &msg_body->bss_params;
	sta = &bss->sta;

	स_रखो(&bss_v0, 0x00, माप(bss_v0));
	wcn36xx_smd_set_bss_params(wcn, vअगर, sta_80211, bssid, update, &bss_v0);
	wcn36xx_smd_set_sta_params_v1(wcn, vअगर, sta_80211, sta);

	/* convert orig to v1 */
	स_नकल(bss->bssid, &bss_v0.bssid, ETH_ALEN);
	स_नकल(bss->self_mac_addr, &bss_v0.self_mac_addr, ETH_ALEN);

	bss->bss_type = bss_v0.bss_type;
	bss->oper_mode = bss_v0.oper_mode;
	bss->nw_type = bss_v0.nw_type;

	bss->लघु_slot_समय_supported =
		bss_v0.लघु_slot_समय_supported;
	bss->lla_coexist = bss_v0.lla_coexist;
	bss->llb_coexist = bss_v0.llb_coexist;
	bss->llg_coexist = bss_v0.llg_coexist;
	bss->ht20_coexist = bss_v0.ht20_coexist;
	bss->lln_non_gf_coexist = bss_v0.lln_non_gf_coexist;

	bss->lsig_tx_op_protection_full_support =
		bss_v0.lsig_tx_op_protection_full_support;
	bss->rअगरs_mode = bss_v0.rअगरs_mode;
	bss->beacon_पूर्णांकerval = bss_v0.beacon_पूर्णांकerval;
	bss->dtim_period = bss_v0.dtim_period;
	bss->tx_channel_width_set = bss_v0.tx_channel_width_set;
	bss->oper_channel = bss_v0.oper_channel;

	अगर (wcn->hw->conf.chandef.width == NL80211_CHAN_WIDTH_80) अणु
		chandef = &wcn->hw->conf.chandef;
		bss->ext_channel = HW_VALUE_PHY(chandef->chan->hw_value);
	पूर्ण अन्यथा अणु
		bss->ext_channel = bss_v0.ext_channel;
	पूर्ण

	bss->reserved = bss_v0.reserved;

	स_नकल(&bss->ssid, &bss_v0.ssid,
	       माप(bss_v0.ssid));

	bss->action = bss_v0.action;
	bss->rateset = bss_v0.rateset;
	bss->ht = bss_v0.ht;
	bss->obss_prot_enabled = bss_v0.obss_prot_enabled;
	bss->rmf = bss_v0.rmf;
	bss->ht_oper_mode = bss_v0.ht_oper_mode;
	bss->dual_cts_protection = bss_v0.dual_cts_protection;

	bss->max_probe_resp_retry_limit =
		bss_v0.max_probe_resp_retry_limit;
	bss->hidden_ssid = bss_v0.hidden_ssid;
	bss->proxy_probe_resp =	bss_v0.proxy_probe_resp;
	bss->edca_params_valid = bss_v0.edca_params_valid;

	स_नकल(&bss->acbe, &bss_v0.acbe,
	       माप(bss_v0.acbe));
	स_नकल(&bss->acbk, &bss_v0.acbk,
	       माप(bss_v0.acbk));
	स_नकल(&bss->acvi, &bss_v0.acvi,
	       माप(bss_v0.acvi));
	स_नकल(&bss->acvo, &bss_v0.acvo,
	       माप(bss_v0.acvo));

	bss->ext_set_sta_key_param_valid =
		bss_v0.ext_set_sta_key_param_valid;

	स_नकल(&bss->ext_set_sta_key_param,
	       &bss_v0.ext_set_sta_key_param,
	       माप(bss_v0.acvo));

	bss->wcn36xx_hal_persona = bss_v0.wcn36xx_hal_persona;
	bss->spectrum_mgt_enable = bss_v0.spectrum_mgt_enable;
	bss->tx_mgmt_घातer = bss_v0.tx_mgmt_घातer;
	bss->max_tx_घातer = bss_v0.max_tx_घातer;

	wcn36xx_smd_set_bss_vht_params(vअगर, sta_80211, bss);

	PREPARE_HAL_BUF(wcn->hal_buf, (*msg_body));

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal config bss v1 bssid %pM self_mac_addr %pM bss_type %d oper_mode %d nw_type %d\n",
		    bss->bssid, bss->self_mac_addr, bss->bss_type,
		    bss->oper_mode, bss->nw_type);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "- sta bssid %pM action %d sta_index %d bssid_index %d aid %d type %d mac %pM\n",
		    sta->bssid, sta->action, sta->sta_index,
		    sta->bssid_index, sta->aid, sta->type, sta->mac);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body->header.len);
	kमुक्त(msg_body);

	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_config_bss_v0(काष्ठा wcn36xx *wcn,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_sta *sta,
				     स्थिर u8 *bssid,
				     bool update)
अणु
	काष्ठा wcn36xx_hal_config_bss_req_msg *msg;
	काष्ठा wcn36xx_hal_config_bss_params *bss;
	काष्ठा wcn36xx_hal_config_sta_params *sta_params;
	पूर्णांक ret;

	msg = kzalloc(माप(*msg), GFP_KERNEL);
	अगर (!msg)
		वापस -ENOMEM;

	INIT_HAL_MSG((*msg), WCN36XX_HAL_CONFIG_BSS_REQ);

	bss = &msg->bss_params;
	sta_params = &bss->sta;

	wcn36xx_smd_set_bss_params(wcn, vअगर, sta, bssid, update, bss);
	wcn36xx_smd_set_sta_params(wcn, vअगर, sta, sta_params);

	PREPARE_HAL_BUF(wcn->hal_buf, (*msg));

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal config bss bssid %pM self_mac_addr %pM bss_type %d oper_mode %d nw_type %d\n",
		    bss->bssid, bss->self_mac_addr, bss->bss_type,
		    bss->oper_mode, bss->nw_type);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "- sta bssid %pM action %d sta_index %d bssid_index %d aid %d type %d mac %pM\n",
		    sta_params->bssid, sta_params->action,
		    sta_params->sta_index, sta_params->bssid_index,
		    sta_params->aid, sta_params->type,
		    sta_params->mac);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg->header.len);
	kमुक्त(msg);

	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_config_bss_rsp(काष्ठा wcn36xx *wcn,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_sta *sta,
				      व्योम *buf,
				      माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_config_bss_rsp_msg *rsp;
	काष्ठा wcn36xx_hal_config_bss_rsp_params *params;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);

	अगर (len < माप(*rsp))
		वापस -EINVAL;

	rsp = (काष्ठा wcn36xx_hal_config_bss_rsp_msg *)buf;
	params = &rsp->bss_rsp_params;

	अगर (params->status != WCN36XX_FW_MSG_RESULT_SUCCESS) अणु
		wcn36xx_warn("hal config bss response failure: %d\n",
			     params->status);
		वापस -EIO;
	पूर्ण

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal config bss rsp status %d bss_idx %d dpu_desc_index %d"
		    " sta_idx %d self_idx %d bcast_idx %d mac %pM"
		    " power %d ucast_dpu_signature %d\n",
		    params->status, params->bss_index, params->dpu_desc_index,
		    params->bss_sta_index, params->bss_self_sta_index,
		    params->bss_bcast_sta_idx, params->mac,
		    params->tx_mgmt_घातer, params->ucast_dpu_signature);

	vअगर_priv->bss_index = params->bss_index;

	अगर (sta) अणु
		काष्ठा wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);
		sta_priv->bss_sta_index = params->bss_sta_index;
		sta_priv->bss_dpu_desc_index = params->dpu_desc_index;
	पूर्ण

	vअगर_priv->self_ucast_dpu_sign = params->ucast_dpu_signature;

	वापस 0;
पूर्ण

पूर्णांक wcn36xx_smd_config_bss(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta, स्थिर u8 *bssid,
			   bool update)
अणु
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);

	अगर (!wcn36xx_is_fw_version(wcn, 1, 2, 2, 24))
		ret = wcn36xx_smd_config_bss_v1(wcn, vअगर, sta, bssid, update);
	अन्यथा
		ret = wcn36xx_smd_config_bss_v0(wcn, vअगर, sta, bssid, update);

	अगर (ret) अणु
		wcn36xx_err("Sending hal_config_bss failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_config_bss_rsp(wcn,
					 vअगर,
					 sta,
					 wcn->hal_buf,
					 wcn->hal_rsp_len);
	अगर (ret)
		wcn36xx_err("hal_config_bss response failed err=%d\n", ret);

out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_delete_bss(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx_hal_delete_bss_req_msg msg_body;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	पूर्णांक ret = 0;

	mutex_lock(&wcn->hal_mutex);

	अगर (vअगर_priv->bss_index == WCN36XX_HAL_BSS_INVALID_IDX)
		जाओ out;

	INIT_HAL_MSG(msg_body, WCN36XX_HAL_DELETE_BSS_REQ);

	msg_body.bss_index = vअगर_priv->bss_index;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL, "hal delete bss %d\n", msg_body.bss_index);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_delete_bss failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_delete_bss response failed err=%d\n", ret);
		जाओ out;
	पूर्ण

	vअगर_priv->bss_index = WCN36XX_HAL_BSS_INVALID_IDX;
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_send_beacon(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा sk_buff *skb_beacon, u16 tim_off,
			    u16 p2p_off)
अणु
	काष्ठा wcn36xx_hal_send_beacon_req_msg msg_body;
	पूर्णांक ret, pad, pvm_len;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SEND_BEACON_REQ);

	pvm_len = skb_beacon->data[tim_off + 1] - 3;
	pad = TIM_MIN_PVM_SIZE - pvm_len;

	/* Padding is irrelevant to mesh mode since tim_off is always 0. */
	अगर (vअगर->type == NL80211_IFTYPE_MESH_POINT)
		pad = 0;

	msg_body.beacon_length = skb_beacon->len + pad;
	/* TODO need to find out why + 6 is needed */
	msg_body.beacon_length6 = msg_body.beacon_length + 6;

	अगर (msg_body.beacon_length > BEACON_TEMPLATE_SIZE) अणु
		wcn36xx_err("Beacon is too big: beacon size=%d\n",
			      msg_body.beacon_length);
		ret = -ENOMEM;
		जाओ out;
	पूर्ण
	स_नकल(msg_body.beacon, skb_beacon->data, skb_beacon->len);
	स_नकल(msg_body.bssid, vअगर->addr, ETH_ALEN);

	अगर (pad > 0) अणु
		/*
		 * The wcn36xx FW has a fixed size क्रम the PVM in the TIM. If
		 * given the beacon ढाँचा from mac80211 with a PVM लघुer
		 * than the FW expectes it will overग_लिखो the data after the
		 * TIM.
		 */
		wcn36xx_dbg(WCN36XX_DBG_HAL, "Pad TIM PVM. %d bytes at %d\n",
			    pad, pvm_len);
		स_हटाओ(&msg_body.beacon[tim_off + 5 + pvm_len + pad],
			&msg_body.beacon[tim_off + 5 + pvm_len],
			skb_beacon->len - (tim_off + 5 + pvm_len));
		स_रखो(&msg_body.beacon[tim_off + 5 + pvm_len], 0, pad);
		msg_body.beacon[tim_off + 1] += pad;
	पूर्ण

	/* TODO need to find out why this is needed? */
	अगर (vअगर->type == NL80211_IFTYPE_MESH_POINT)
		/* mesh beacon करोn't need this, so push further करोwn */
		msg_body.tim_ie_offset = 256;
	अन्यथा
		msg_body.tim_ie_offset = tim_off+4;
	msg_body.p2p_ie_offset = p2p_off;
	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal send beacon beacon_length %d\n",
		    msg_body.beacon_length);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_send_beacon failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_send_beacon response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_update_proberesp_पंचांगpl(काष्ठा wcn36xx *wcn,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा sk_buff *skb)
अणु
	काष्ठा wcn36xx_hal_send_probe_resp_req_msg msg;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg, WCN36XX_HAL_UPDATE_PROBE_RSP_TEMPLATE_REQ);

	अगर (skb->len > BEACON_TEMPLATE_SIZE) अणु
		wcn36xx_warn("probe response template is too big: %d\n",
			     skb->len);
		ret = -E2BIG;
		जाओ out;
	पूर्ण

	msg.probe_resp_ढाँचा_len = skb->len;
	स_नकल(&msg.probe_resp_ढाँचा, skb->data, skb->len);

	स_नकल(msg.bssid, vअगर->addr, ETH_ALEN);

	PREPARE_HAL_BUF(wcn->hal_buf, msg);

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "hal update probe rsp len %d bssid %pM\n",
		    msg.probe_resp_ढाँचा_len, msg.bssid);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_update_proberesp_tmpl failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_update_proberesp_tmpl response failed err=%d\n",
			    ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_set_stakey(काष्ठा wcn36xx *wcn,
			   क्रमागत ani_ed_type enc_type,
			   u8 keyidx,
			   u8 keylen,
			   u8 *key,
			   u8 sta_index)
अणु
	काष्ठा wcn36xx_hal_set_sta_key_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SET_STAKEY_REQ);

	msg_body.set_sta_key_params.sta_index = sta_index;
	msg_body.set_sta_key_params.enc_type = enc_type;

	अगर (enc_type == WCN36XX_HAL_ED_WEP104 ||
	    enc_type == WCN36XX_HAL_ED_WEP40) अणु
		/* Use bss key क्रम wep (अटल) */
		msg_body.set_sta_key_params.def_wep_idx = keyidx;
		msg_body.set_sta_key_params.wep_type = 0;
	पूर्ण अन्यथा अणु
		msg_body.set_sta_key_params.key[0].id = keyidx;
		msg_body.set_sta_key_params.key[0].unicast = 1;
		msg_body.set_sta_key_params.key[0].direction = WCN36XX_HAL_TX_RX;
		msg_body.set_sta_key_params.key[0].pae_role = 0;
		msg_body.set_sta_key_params.key[0].length = keylen;
		स_नकल(msg_body.set_sta_key_params.key[0].key, key, keylen);
	पूर्ण

	msg_body.set_sta_key_params.single_tid_rc = 1;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_set_stakey failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_set_stakey response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_set_bsskey(काष्ठा wcn36xx *wcn,
			   क्रमागत ani_ed_type enc_type,
			   u8 bssidx,
			   u8 keyidx,
			   u8 keylen,
			   u8 *key)
अणु
	काष्ठा wcn36xx_hal_set_bss_key_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SET_BSSKEY_REQ);
	msg_body.bss_idx = bssidx;
	msg_body.enc_type = enc_type;
	msg_body.num_keys = 1;
	msg_body.keys[0].id = keyidx;
	msg_body.keys[0].unicast = 0;
	msg_body.keys[0].direction = WCN36XX_HAL_RX_ONLY;
	msg_body.keys[0].pae_role = 0;
	msg_body.keys[0].length = keylen;
	स_नकल(msg_body.keys[0].key, key, keylen);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_set_bsskey failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_set_bsskey response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_हटाओ_stakey(काष्ठा wcn36xx *wcn,
			      क्रमागत ani_ed_type enc_type,
			      u8 keyidx,
			      u8 sta_index)
अणु
	काष्ठा wcn36xx_hal_हटाओ_sta_key_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_RMV_STAKEY_REQ);

	msg_body.sta_idx = sta_index;
	msg_body.enc_type = enc_type;
	msg_body.key_id = keyidx;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_remove_stakey failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_remove_stakey response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_हटाओ_bsskey(काष्ठा wcn36xx *wcn,
			      क्रमागत ani_ed_type enc_type,
			      u8 bssidx,
			      u8 keyidx)
अणु
	काष्ठा wcn36xx_hal_हटाओ_bss_key_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_RMV_BSSKEY_REQ);
	msg_body.bss_idx = bssidx;
	msg_body.enc_type = enc_type;
	msg_body.key_id = keyidx;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_remove_bsskey failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_remove_bsskey response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_enter_bmps(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx_hal_enter_bmps_req_msg msg_body;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_ENTER_BMPS_REQ);

	msg_body.bss_index = vअगर_priv->bss_index;
	msg_body.tbtt = vअगर->bss_conf.sync_tsf;
	msg_body.dtim_period = vअगर_priv->dtim_period;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_enter_bmps failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_enter_bmps response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_निकास_bmps(काष्ठा wcn36xx *wcn, काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx_hal_निकास_bmps_req_msg msg_body;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_EXIT_BMPS_REQ);

	msg_body.bss_index = vअगर_priv->bss_index;
	msg_body.send_data_null = 1;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_exit_bmps failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_exit_bmps response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_set_घातer_params(काष्ठा wcn36xx *wcn, bool ignore_dtim)
अणु
	काष्ठा wcn36xx_hal_set_घातer_params_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_SET_POWER_PARAMS_REQ);

	/*
	 * When host is करोwn ignore every second dtim
	 */
	अगर (ignore_dtim) अणु
		msg_body.ignore_dtim = 1;
		msg_body.dtim_period = 2;
	पूर्ण
	msg_body.listen_पूर्णांकerval = WCN36XX_LISTEN_INTERVAL(wcn);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_set_power_params failed\n");
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

/* Notice: This function should be called after associated, or अन्यथा it
 * will be invalid
 */
पूर्णांक wcn36xx_smd_keep_alive_req(काष्ठा wcn36xx *wcn,
			       काष्ठा ieee80211_vअगर *vअगर,
			       पूर्णांक packet_type)
अणु
	काष्ठा wcn36xx_hal_keep_alive_req_msg msg_body;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_KEEP_ALIVE_REQ);

	अगर (packet_type == WCN36XX_HAL_KEEP_ALIVE_शून्य_PKT) अणु
		msg_body.bss_index = vअगर_priv->bss_index;
		msg_body.packet_type = WCN36XX_HAL_KEEP_ALIVE_शून्य_PKT;
		msg_body.समय_period = WCN36XX_KEEP_ALIVE_TIME_PERIOD;
	पूर्ण अन्यथा अगर (packet_type == WCN36XX_HAL_KEEP_ALIVE_UNSOLICIT_ARP_RSP) अणु
		/* TODO: it also support ARP response type */
	पूर्ण अन्यथा अणु
		wcn36xx_warn("unknown keep alive packet type %d\n", packet_type);
		ret = -EINVAL;
		जाओ out;
	पूर्ण

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_keep_alive failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_keep_alive response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_dump_cmd_req(काष्ठा wcn36xx *wcn, u32 arg1, u32 arg2,
			     u32 arg3, u32 arg4, u32 arg5)
अणु
	काष्ठा wcn36xx_hal_dump_cmd_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_DUMP_COMMAND_REQ);

	msg_body.arg1 = arg1;
	msg_body.arg2 = arg2;
	msg_body.arg3 = arg3;
	msg_body.arg4 = arg4;
	msg_body.arg5 = arg5;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_dump_cmd failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_dump_cmd response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

व्योम set_feat_caps(u32 *biपंचांगap, क्रमागत place_holder_in_cap_biपंचांगap cap)
अणु
	पूर्णांक arr_idx, bit_idx;

	अगर (cap < 0 || cap > 127) अणु
		wcn36xx_warn("error cap idx %d\n", cap);
		वापस;
	पूर्ण

	arr_idx = cap / 32;
	bit_idx = cap % 32;
	biपंचांगap[arr_idx] |= (1 << bit_idx);
पूर्ण

पूर्णांक get_feat_caps(u32 *biपंचांगap, क्रमागत place_holder_in_cap_biपंचांगap cap)
अणु
	पूर्णांक arr_idx, bit_idx;

	अगर (cap < 0 || cap > 127) अणु
		wcn36xx_warn("error cap idx %d\n", cap);
		वापस -EINVAL;
	पूर्ण

	arr_idx = cap / 32;
	bit_idx = cap % 32;

	वापस (biपंचांगap[arr_idx] & (1 << bit_idx)) ? 1 : 0;
पूर्ण

व्योम clear_feat_caps(u32 *biपंचांगap, क्रमागत place_holder_in_cap_biपंचांगap cap)
अणु
	पूर्णांक arr_idx, bit_idx;

	अगर (cap < 0 || cap > 127) अणु
		wcn36xx_warn("error cap idx %d\n", cap);
		वापस;
	पूर्ण

	arr_idx = cap / 32;
	bit_idx = cap % 32;
	biपंचांगap[arr_idx] &= ~(1 << bit_idx);
पूर्ण

पूर्णांक wcn36xx_smd_feature_caps_exchange(काष्ठा wcn36xx *wcn)
अणु
	काष्ठा wcn36xx_hal_feat_caps_msg msg_body, *rsp;
	पूर्णांक ret, i;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_FEATURE_CAPS_EXCHANGE_REQ);

	set_feat_caps(msg_body.feat_caps, STA_POWERSAVE);
	अगर (wcn->rf_id == RF_IRIS_WCN3680)
		set_feat_caps(msg_body.feat_caps, DOT11AC);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_feature_caps_exchange failed\n");
		जाओ out;
	पूर्ण
	अगर (wcn->hal_rsp_len != माप(*rsp)) अणु
		wcn36xx_err("Invalid hal_feature_caps_exchange response");
		जाओ out;
	पूर्ण

	rsp = (काष्ठा wcn36xx_hal_feat_caps_msg *) wcn->hal_buf;

	क्रम (i = 0; i < WCN36XX_HAL_CAPS_SIZE; i++)
		wcn->fw_feat_caps[i] = rsp->feat_caps[i];
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_add_ba_session_rsp(व्योम *buf, पूर्णांक len, u8 *session)
अणु
	काष्ठा wcn36xx_hal_add_ba_session_rsp_msg *rsp;

	अगर (len < माप(*rsp))
		वापस -EINVAL;

	rsp = (काष्ठा wcn36xx_hal_add_ba_session_rsp_msg *)buf;
	अगर (rsp->status != WCN36XX_FW_MSG_RESULT_SUCCESS)
		वापस rsp->status;

	*session = rsp->ba_session_id;

	वापस 0;
पूर्ण

पूर्णांक wcn36xx_smd_add_ba_session(काष्ठा wcn36xx *wcn,
		काष्ठा ieee80211_sta *sta,
		u16 tid,
		u16 *ssn,
		u8 direction,
		u8 sta_index)
अणु
	काष्ठा wcn36xx_hal_add_ba_session_req_msg msg_body;
	u8 session_id;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_ADD_BA_SESSION_REQ);

	msg_body.sta_index = sta_index;
	स_नकल(&msg_body.mac_addr, sta->addr, ETH_ALEN);
	msg_body.dialog_token = 0x10;
	msg_body.tid = tid;

	/* Immediate BA because Delayed BA is not supported */
	msg_body.policy = 1;
	msg_body.buffer_size = WCN36XX_AGGR_BUFFER_SIZE;
	msg_body.समयout = 0;
	अगर (ssn)
		msg_body.ssn = *ssn;
	msg_body.direction = direction;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_add_ba_session failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_add_ba_session_rsp(wcn->hal_buf, wcn->hal_rsp_len,
					     &session_id);
	अगर (ret) अणु
		wcn36xx_err("hal_add_ba_session response failed err=%d\n", ret);
		जाओ out;
	पूर्ण

	ret = session_id;
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_add_ba(काष्ठा wcn36xx *wcn, u8 session_id)
अणु
	काष्ठा wcn36xx_hal_add_ba_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_ADD_BA_REQ);

	msg_body.session_id = session_id;
	msg_body.win_size = WCN36XX_AGGR_BUFFER_SIZE;

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_add_ba failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_add_ba response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_del_ba(काष्ठा wcn36xx *wcn, u16 tid, u8 direction, u8 sta_index)
अणु
	काष्ठा wcn36xx_hal_del_ba_req_msg msg_body;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_DEL_BA_REQ);

	msg_body.sta_index = sta_index;
	msg_body.tid = tid;
	msg_body.direction = direction;
	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_del_ba failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_del_ba response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_trigger_ba_rsp(व्योम *buf, पूर्णांक len)
अणु
	काष्ठा wcn36xx_hal_trigger_ba_rsp_msg *rsp;

	अगर (len < माप(*rsp))
		वापस -EINVAL;

	rsp = (काष्ठा wcn36xx_hal_trigger_ba_rsp_msg *) buf;
	वापस rsp->status;
पूर्ण

पूर्णांक wcn36xx_smd_trigger_ba(काष्ठा wcn36xx *wcn, u8 sta_index, u16 tid, u8 session_id)
अणु
	काष्ठा wcn36xx_hal_trigger_ba_req_msg msg_body;
	काष्ठा wcn36xx_hal_trigger_ba_req_candidate *candidate;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_TRIGGER_BA_REQ);

	msg_body.session_id = session_id;
	msg_body.candidate_cnt = 1;
	msg_body.header.len += माप(*candidate);
	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	candidate = (काष्ठा wcn36xx_hal_trigger_ba_req_candidate *)
		(wcn->hal_buf + माप(msg_body));
	candidate->sta_index = sta_index;
	candidate->tid_biपंचांगap = 1 << tid;

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body.header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_trigger_ba failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_trigger_ba_rsp(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_trigger_ba response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_smd_tx_compl_ind(काष्ठा wcn36xx *wcn, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_tx_compl_ind_msg *rsp = buf;

	अगर (len != माप(*rsp)) अणु
		wcn36xx_warn("Bad TX complete indication\n");
		वापस -EIO;
	पूर्ण

	wcn36xx_dxe_tx_ack_ind(wcn, rsp->status);

	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_smd_hw_scan_ind(काष्ठा wcn36xx *wcn, व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_scan_offload_ind *rsp = buf;
	काष्ठा cfg80211_scan_info scan_info = अणुपूर्ण;

	अगर (len != माप(*rsp)) अणु
		wcn36xx_warn("Corrupted delete scan indication\n");
		वापस -EIO;
	पूर्ण

	wcn36xx_dbg(WCN36XX_DBG_HAL, "scan indication (type %x)\n", rsp->type);

	चयन (rsp->type) अणु
	हाल WCN36XX_HAL_SCAN_IND_FAILED:
	हाल WCN36XX_HAL_SCAN_IND_DEQUEUED:
		scan_info.पातed = true;
		fallthrough;
	हाल WCN36XX_HAL_SCAN_IND_COMPLETED:
		mutex_lock(&wcn->scan_lock);
		wcn->scan_req = शून्य;
		अगर (wcn->scan_पातed)
			scan_info.पातed = true;
		mutex_unlock(&wcn->scan_lock);
		ieee80211_scan_completed(wcn->hw, &scan_info);
		अवरोध;
	हाल WCN36XX_HAL_SCAN_IND_STARTED:
	हाल WCN36XX_HAL_SCAN_IND_FOREIGN_CHANNEL:
	हाल WCN36XX_HAL_SCAN_IND_PREEMPTED:
	हाल WCN36XX_HAL_SCAN_IND_RESTARTED:
		अवरोध;
	शेष:
		wcn36xx_warn("Unknown scan indication type %x\n", rsp->type);
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_smd_missed_beacon_ind(काष्ठा wcn36xx *wcn,
					 व्योम *buf,
					 माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_missed_beacon_ind_msg *rsp = buf;
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	काष्ठा wcn36xx_vअगर *पंचांगp;

	/* Old FW करोes not have bss index */
	अगर (wcn36xx_is_fw_version(wcn, 1, 2, 2, 24)) अणु
		list_क्रम_each_entry(पंचांगp, &wcn->vअगर_list, list) अणु
			wcn36xx_dbg(WCN36XX_DBG_HAL, "beacon missed bss_index %d\n",
				    पंचांगp->bss_index);
			vअगर = wcn36xx_priv_to_vअगर(पंचांगp);
			ieee80211_connection_loss(vअगर);
		पूर्ण
		वापस 0;
	पूर्ण

	अगर (len != माप(*rsp)) अणु
		wcn36xx_warn("Corrupted missed beacon indication\n");
		वापस -EIO;
	पूर्ण

	list_क्रम_each_entry(पंचांगp, &wcn->vअगर_list, list) अणु
		अगर (पंचांगp->bss_index == rsp->bss_index) अणु
			wcn36xx_dbg(WCN36XX_DBG_HAL, "beacon missed bss_index %d\n",
				    rsp->bss_index);
			vअगर = wcn36xx_priv_to_vअगर(पंचांगp);
			ieee80211_connection_loss(vअगर);
			वापस 0;
		पूर्ण
	पूर्ण

	wcn36xx_warn("BSS index %d not found\n", rsp->bss_index);
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक wcn36xx_smd_delete_sta_context_ind(काष्ठा wcn36xx *wcn,
					      व्योम *buf,
					      माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_delete_sta_context_ind_msg *rsp = buf;
	काष्ठा wcn36xx_vअगर *पंचांगp;
	काष्ठा ieee80211_sta *sta;

	अगर (len != माप(*rsp)) अणु
		wcn36xx_warn("Corrupted delete sta indication\n");
		वापस -EIO;
	पूर्ण

	wcn36xx_dbg(WCN36XX_DBG_HAL, "delete station indication %pM index %d\n",
		    rsp->addr2, rsp->sta_id);

	list_क्रम_each_entry(पंचांगp, &wcn->vअगर_list, list) अणु
		rcu_पढ़ो_lock();
		sta = ieee80211_find_sta(wcn36xx_priv_to_vअगर(पंचांगp), rsp->addr2);
		अगर (sta)
			ieee80211_report_low_ack(sta, 0);
		rcu_पढ़ो_unlock();
		अगर (sta)
			वापस 0;
	पूर्ण

	wcn36xx_warn("STA with addr %pM and index %d not found\n",
		     rsp->addr2,
		     rsp->sta_id);
	वापस -ENOENT;
पूर्ण

अटल पूर्णांक wcn36xx_smd_prपूर्णांक_reg_info_ind(काष्ठा wcn36xx *wcn,
					  व्योम *buf,
					  माप_प्रकार len)
अणु
	काष्ठा wcn36xx_hal_prपूर्णांक_reg_info_ind *rsp = buf;
	पूर्णांक i;

	अगर (len < माप(*rsp)) अणु
		wcn36xx_warn("Corrupted print reg info indication\n");
		वापस -EIO;
	पूर्ण

	wcn36xx_dbg(WCN36XX_DBG_HAL,
		    "reginfo indication, scenario: 0x%x reason: 0x%x\n",
		    rsp->scenario, rsp->reason);

	क्रम (i = 0; i < rsp->count; i++) अणु
		wcn36xx_dbg(WCN36XX_DBG_HAL, "\t0x%x: 0x%x\n",
			    rsp->regs[i].addr, rsp->regs[i].value);
	पूर्ण

	वापस 0;
पूर्ण

पूर्णांक wcn36xx_smd_update_cfg(काष्ठा wcn36xx *wcn, u32 cfg_id, u32 value)
अणु
	काष्ठा wcn36xx_hal_update_cfg_req_msg msg_body, *body;
	माप_प्रकार len;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);
	INIT_HAL_MSG(msg_body, WCN36XX_HAL_UPDATE_CFG_REQ);

	PREPARE_HAL_BUF(wcn->hal_buf, msg_body);

	body = (काष्ठा wcn36xx_hal_update_cfg_req_msg *) wcn->hal_buf;
	len = msg_body.header.len;

	put_cfg_tlv_u32(wcn, &len, cfg_id, value);
	body->header.len = len;
	body->len = len - माप(*body);

	ret = wcn36xx_smd_send_and_रुको(wcn, body->header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending hal_update_cfg failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("hal_update_cfg response failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_set_mc_list(काष्ठा wcn36xx *wcn,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा wcn36xx_hal_rcv_flt_mc_addr_list_type *fp)
अणु
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	काष्ठा wcn36xx_hal_rcv_flt_pkt_set_mc_list_req_msg *msg_body = शून्य;
	पूर्णांक ret;

	mutex_lock(&wcn->hal_mutex);

	msg_body = (काष्ठा wcn36xx_hal_rcv_flt_pkt_set_mc_list_req_msg *)
		   wcn->hal_buf;
	init_hal_msg(&msg_body->header, WCN36XX_HAL_8023_MULTICAST_LIST_REQ,
		     माप(msg_body->mc_addr_list));

	/* An empty list means all mc traffic will be received */
	अगर (fp)
		स_नकल(&msg_body->mc_addr_list, fp,
		       माप(msg_body->mc_addr_list));
	अन्यथा
		msg_body->mc_addr_list.mc_addr_count = 0;

	msg_body->mc_addr_list.bss_index = vअगर_priv->bss_index;

	ret = wcn36xx_smd_send_and_रुको(wcn, msg_body->header.len);
	अगर (ret) अणु
		wcn36xx_err("Sending HAL_8023_MULTICAST_LIST failed\n");
		जाओ out;
	पूर्ण
	ret = wcn36xx_smd_rsp_status_check(wcn->hal_buf, wcn->hal_rsp_len);
	अगर (ret) अणु
		wcn36xx_err("HAL_8023_MULTICAST_LIST rsp failed err=%d\n", ret);
		जाओ out;
	पूर्ण
out:
	mutex_unlock(&wcn->hal_mutex);
	वापस ret;
पूर्ण

पूर्णांक wcn36xx_smd_rsp_process(काष्ठा rpmsg_device *rpdev,
			    व्योम *buf, पूर्णांक len, व्योम *priv, u32 addr)
अणु
	स्थिर काष्ठा wcn36xx_hal_msg_header *msg_header = buf;
	काष्ठा ieee80211_hw *hw = priv;
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_hal_ind_msg *msg_ind;
	wcn36xx_dbg_dump(WCN36XX_DBG_SMD_DUMP, "SMD <<< ", buf, len);

	चयन (msg_header->msg_type) अणु
	हाल WCN36XX_HAL_START_RSP:
	हाल WCN36XX_HAL_CONFIG_STA_RSP:
	हाल WCN36XX_HAL_CONFIG_BSS_RSP:
	हाल WCN36XX_HAL_ADD_STA_SELF_RSP:
	हाल WCN36XX_HAL_STOP_RSP:
	हाल WCN36XX_HAL_DEL_STA_SELF_RSP:
	हाल WCN36XX_HAL_DELETE_STA_RSP:
	हाल WCN36XX_HAL_INIT_SCAN_RSP:
	हाल WCN36XX_HAL_START_SCAN_RSP:
	हाल WCN36XX_HAL_END_SCAN_RSP:
	हाल WCN36XX_HAL_FINISH_SCAN_RSP:
	हाल WCN36XX_HAL_DOWNLOAD_NV_RSP:
	हाल WCN36XX_HAL_DELETE_BSS_RSP:
	हाल WCN36XX_HAL_SEND_BEACON_RSP:
	हाल WCN36XX_HAL_SET_LINK_ST_RSP:
	हाल WCN36XX_HAL_UPDATE_PROBE_RSP_TEMPLATE_RSP:
	हाल WCN36XX_HAL_SET_BSSKEY_RSP:
	हाल WCN36XX_HAL_SET_STAKEY_RSP:
	हाल WCN36XX_HAL_RMV_STAKEY_RSP:
	हाल WCN36XX_HAL_RMV_BSSKEY_RSP:
	हाल WCN36XX_HAL_ENTER_BMPS_RSP:
	हाल WCN36XX_HAL_SET_POWER_PARAMS_RSP:
	हाल WCN36XX_HAL_EXIT_BMPS_RSP:
	हाल WCN36XX_HAL_KEEP_ALIVE_RSP:
	हाल WCN36XX_HAL_DUMP_COMMAND_RSP:
	हाल WCN36XX_HAL_ADD_BA_SESSION_RSP:
	हाल WCN36XX_HAL_ADD_BA_RSP:
	हाल WCN36XX_HAL_DEL_BA_RSP:
	हाल WCN36XX_HAL_TRIGGER_BA_RSP:
	हाल WCN36XX_HAL_UPDATE_CFG_RSP:
	हाल WCN36XX_HAL_JOIN_RSP:
	हाल WCN36XX_HAL_UPDATE_SCAN_PARAM_RSP:
	हाल WCN36XX_HAL_CH_SWITCH_RSP:
	हाल WCN36XX_HAL_PROCESS_PTT_RSP:
	हाल WCN36XX_HAL_FEATURE_CAPS_EXCHANGE_RSP:
	हाल WCN36XX_HAL_8023_MULTICAST_LIST_RSP:
	हाल WCN36XX_HAL_START_SCAN_OFFLOAD_RSP:
	हाल WCN36XX_HAL_STOP_SCAN_OFFLOAD_RSP:
		स_नकल(wcn->hal_buf, buf, len);
		wcn->hal_rsp_len = len;
		complete(&wcn->hal_rsp_compl);
		अवरोध;

	हाल WCN36XX_HAL_COEX_IND:
	हाल WCN36XX_HAL_AVOID_FREQ_RANGE_IND:
	हाल WCN36XX_HAL_DEL_BA_IND:
	हाल WCN36XX_HAL_OTA_TX_COMPL_IND:
	हाल WCN36XX_HAL_MISSED_BEACON_IND:
	हाल WCN36XX_HAL_DELETE_STA_CONTEXT_IND:
	हाल WCN36XX_HAL_PRINT_REG_INFO_IND:
	हाल WCN36XX_HAL_SCAN_OFFLOAD_IND:
		msg_ind = kदो_स्मृति(माप(*msg_ind) + len, GFP_ATOMIC);
		अगर (!msg_ind) अणु
			wcn36xx_err("Run out of memory while handling SMD_EVENT (%d)\n",
				    msg_header->msg_type);
			वापस -ENOMEM;
		पूर्ण

		msg_ind->msg_len = len;
		स_नकल(msg_ind->msg, buf, len);

		spin_lock(&wcn->hal_ind_lock);
		list_add_tail(&msg_ind->list, &wcn->hal_ind_queue);
		queue_work(wcn->hal_ind_wq, &wcn->hal_ind_work);
		spin_unlock(&wcn->hal_ind_lock);
		wcn36xx_dbg(WCN36XX_DBG_HAL, "indication arrived\n");
		अवरोध;
	शेष:
		wcn36xx_err("SMD_EVENT (%d) not supported\n",
			      msg_header->msg_type);
	पूर्ण

	वापस 0;
पूर्ण

अटल व्योम wcn36xx_ind_smd_work(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा wcn36xx *wcn =
		container_of(work, काष्ठा wcn36xx, hal_ind_work);

	क्रम (;;) अणु
		काष्ठा wcn36xx_hal_msg_header *msg_header;
		काष्ठा wcn36xx_hal_ind_msg *hal_ind_msg;
		अचिन्हित दीर्घ flags;

		spin_lock_irqsave(&wcn->hal_ind_lock, flags);

		अगर (list_empty(&wcn->hal_ind_queue)) अणु
			spin_unlock_irqrestore(&wcn->hal_ind_lock, flags);
			वापस;
		पूर्ण

		hal_ind_msg = list_first_entry(&wcn->hal_ind_queue,
					       काष्ठा wcn36xx_hal_ind_msg,
					       list);
		list_del(&hal_ind_msg->list);
		spin_unlock_irqrestore(&wcn->hal_ind_lock, flags);

		msg_header = (काष्ठा wcn36xx_hal_msg_header *)hal_ind_msg->msg;

		चयन (msg_header->msg_type) अणु
		हाल WCN36XX_HAL_COEX_IND:
		हाल WCN36XX_HAL_DEL_BA_IND:
		हाल WCN36XX_HAL_AVOID_FREQ_RANGE_IND:
			अवरोध;
		हाल WCN36XX_HAL_OTA_TX_COMPL_IND:
			wcn36xx_smd_tx_compl_ind(wcn,
						 hal_ind_msg->msg,
						 hal_ind_msg->msg_len);
			अवरोध;
		हाल WCN36XX_HAL_MISSED_BEACON_IND:
			wcn36xx_smd_missed_beacon_ind(wcn,
						      hal_ind_msg->msg,
						      hal_ind_msg->msg_len);
			अवरोध;
		हाल WCN36XX_HAL_DELETE_STA_CONTEXT_IND:
			wcn36xx_smd_delete_sta_context_ind(wcn,
							   hal_ind_msg->msg,
							   hal_ind_msg->msg_len);
			अवरोध;
		हाल WCN36XX_HAL_PRINT_REG_INFO_IND:
			wcn36xx_smd_prपूर्णांक_reg_info_ind(wcn,
						       hal_ind_msg->msg,
						       hal_ind_msg->msg_len);
			अवरोध;
		हाल WCN36XX_HAL_SCAN_OFFLOAD_IND:
			wcn36xx_smd_hw_scan_ind(wcn, hal_ind_msg->msg,
						hal_ind_msg->msg_len);
			अवरोध;
		शेष:
			wcn36xx_err("SMD_EVENT (%d) not supported\n",
				    msg_header->msg_type);
		पूर्ण

		kमुक्त(hal_ind_msg);
	पूर्ण
पूर्ण

पूर्णांक wcn36xx_smd_खोलो(काष्ठा wcn36xx *wcn)
अणु
	wcn->hal_ind_wq = create_मुक्तzable_workqueue("wcn36xx_smd_ind");
	अगर (!wcn->hal_ind_wq)
		वापस -ENOMEM;

	INIT_WORK(&wcn->hal_ind_work, wcn36xx_ind_smd_work);
	INIT_LIST_HEAD(&wcn->hal_ind_queue);
	spin_lock_init(&wcn->hal_ind_lock);

	वापस 0;
पूर्ण

व्योम wcn36xx_smd_बंद(काष्ठा wcn36xx *wcn)
अणु
	काष्ठा wcn36xx_hal_ind_msg *msg, *पंचांगp;

	cancel_work_sync(&wcn->hal_ind_work);
	destroy_workqueue(wcn->hal_ind_wq);

	list_क्रम_each_entry_safe(msg, पंचांगp, &wcn->hal_ind_queue, list)
		kमुक्त(msg);
पूर्ण
