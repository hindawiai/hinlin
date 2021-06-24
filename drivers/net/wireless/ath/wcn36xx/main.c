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

#समावेश <linux/module.h>
#समावेश <linux/firmware.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/of_address.h>
#समावेश <linux/of_device.h>
#समावेश <linux/of_irq.h>
#समावेश <linux/rpmsg.h>
#समावेश <linux/soc/qcom/smem_state.h>
#समावेश <linux/soc/qcom/wcnss_ctrl.h>
#समावेश "wcn36xx.h"
#समावेश "testmode.h"

अचिन्हित पूर्णांक wcn36xx_dbg_mask;
module_param_named(debug_mask, wcn36xx_dbg_mask, uपूर्णांक, 0644);
MODULE_PARM_DESC(debug_mask, "Debugging mask");

#घोषणा CHAN2G(_freq, _idx) अणु \
	.band = NL80211_BAND_2GHZ, \
	.center_freq = (_freq), \
	.hw_value = (_idx), \
	.max_घातer = 25, \
पूर्ण

#घोषणा CHAN5G(_freq, _idx, _phy_val) अणु \
	.band = NL80211_BAND_5GHZ, \
	.center_freq = (_freq), \
	.hw_value = (_phy_val) << HW_VALUE_PHY_SHIFT | HW_VALUE_CHANNEL(_idx), \
	.max_घातer = 25, \
पूर्ण

/* The wcn firmware expects channel values to matching
 * their mnemonic values. So use these क्रम .hw_value. */
अटल काष्ठा ieee80211_channel wcn_2ghz_channels[] = अणु
	CHAN2G(2412, 1), /* Channel 1 */
	CHAN2G(2417, 2), /* Channel 2 */
	CHAN2G(2422, 3), /* Channel 3 */
	CHAN2G(2427, 4), /* Channel 4 */
	CHAN2G(2432, 5), /* Channel 5 */
	CHAN2G(2437, 6), /* Channel 6 */
	CHAN2G(2442, 7), /* Channel 7 */
	CHAN2G(2447, 8), /* Channel 8 */
	CHAN2G(2452, 9), /* Channel 9 */
	CHAN2G(2457, 10), /* Channel 10 */
	CHAN2G(2462, 11), /* Channel 11 */
	CHAN2G(2467, 12), /* Channel 12 */
	CHAN2G(2472, 13), /* Channel 13 */
	CHAN2G(2484, 14)  /* Channel 14 */

पूर्ण;

अटल काष्ठा ieee80211_channel wcn_5ghz_channels[] = अणु
	CHAN5G(5180, 36, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW),
	CHAN5G(5200, 40, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW),
	CHAN5G(5220, 44, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH),
	CHAN5G(5240, 48, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5260, 52, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW),
	CHAN5G(5280, 56, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW),
	CHAN5G(5300, 60, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH),
	CHAN5G(5320, 64, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5500, 100, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW),
	CHAN5G(5520, 104, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW),
	CHAN5G(5540, 108, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH),
	CHAN5G(5560, 112, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5580, 116, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW),
	CHAN5G(5600, 120, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW),
	CHAN5G(5620, 124, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH),
	CHAN5G(5640, 128, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5660, 132, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW),
	CHAN5G(5700, 140, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH),
	CHAN5G(5745, 149, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_LOW),
	CHAN5G(5765, 153, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_LOW),
	CHAN5G(5785, 157, PHY_QUADRUPLE_CHANNEL_20MHZ_LOW_40MHZ_HIGH),
	CHAN5G(5805, 161, PHY_QUADRUPLE_CHANNEL_20MHZ_HIGH_40MHZ_HIGH),
	CHAN5G(5825, 165, 0)
पूर्ण;

#घोषणा RATE(_bitrate, _hw_rate, _flags) अणु \
	.bitrate        = (_bitrate),                   \
	.flags          = (_flags),                     \
	.hw_value       = (_hw_rate),                   \
	.hw_value_लघु = (_hw_rate)  \
पूर्ण

अटल काष्ठा ieee80211_rate wcn_2ghz_rates[] = अणु
	RATE(10, HW_RATE_INDEX_1MBPS, 0),
	RATE(20, HW_RATE_INDEX_2MBPS, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(55, HW_RATE_INDEX_5_5MBPS, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(110, HW_RATE_INDEX_11MBPS, IEEE80211_RATE_SHORT_PREAMBLE),
	RATE(60, HW_RATE_INDEX_6MBPS, 0),
	RATE(90, HW_RATE_INDEX_9MBPS, 0),
	RATE(120, HW_RATE_INDEX_12MBPS, 0),
	RATE(180, HW_RATE_INDEX_18MBPS, 0),
	RATE(240, HW_RATE_INDEX_24MBPS, 0),
	RATE(360, HW_RATE_INDEX_36MBPS, 0),
	RATE(480, HW_RATE_INDEX_48MBPS, 0),
	RATE(540, HW_RATE_INDEX_54MBPS, 0)
पूर्ण;

अटल काष्ठा ieee80211_rate wcn_5ghz_rates[] = अणु
	RATE(60, HW_RATE_INDEX_6MBPS, 0),
	RATE(90, HW_RATE_INDEX_9MBPS, 0),
	RATE(120, HW_RATE_INDEX_12MBPS, 0),
	RATE(180, HW_RATE_INDEX_18MBPS, 0),
	RATE(240, HW_RATE_INDEX_24MBPS, 0),
	RATE(360, HW_RATE_INDEX_36MBPS, 0),
	RATE(480, HW_RATE_INDEX_48MBPS, 0),
	RATE(540, HW_RATE_INDEX_54MBPS, 0)
पूर्ण;

अटल काष्ठा ieee80211_supported_band wcn_band_2ghz = अणु
	.channels	= wcn_2ghz_channels,
	.n_channels	= ARRAY_SIZE(wcn_2ghz_channels),
	.bitrates	= wcn_2ghz_rates,
	.n_bitrates	= ARRAY_SIZE(wcn_2ghz_rates),
	.ht_cap		= अणु
		.cap =	IEEE80211_HT_CAP_GRN_FLD |
			IEEE80211_HT_CAP_SGI_20 |
			IEEE80211_HT_CAP_DSSSCCK40 |
			IEEE80211_HT_CAP_LSIG_TXOP_PROT,
		.ht_supported = true,
		.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
		.mcs = अणु
			.rx_mask = अणु 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण,
			.rx_highest = cpu_to_le16(72),
			.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण
	पूर्ण
पूर्ण;

अटल काष्ठा ieee80211_supported_band wcn_band_5ghz = अणु
	.channels	= wcn_5ghz_channels,
	.n_channels	= ARRAY_SIZE(wcn_5ghz_channels),
	.bitrates	= wcn_5ghz_rates,
	.n_bitrates	= ARRAY_SIZE(wcn_5ghz_rates),
	.ht_cap		= अणु
		.cap =	IEEE80211_HT_CAP_GRN_FLD |
			IEEE80211_HT_CAP_SGI_20 |
			IEEE80211_HT_CAP_DSSSCCK40 |
			IEEE80211_HT_CAP_LSIG_TXOP_PROT |
			IEEE80211_HT_CAP_SGI_40 |
			IEEE80211_HT_CAP_SUP_WIDTH_20_40,
		.ht_supported = true,
		.ampdu_factor = IEEE80211_HT_MAX_AMPDU_64K,
		.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
		.mcs = अणु
			.rx_mask = अणु 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण,
			.rx_highest = cpu_to_le16(150),
			.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण
	पूर्ण
पूर्ण;

#अगर_घोषित CONFIG_PM

अटल स्थिर काष्ठा wiphy_wowlan_support wowlan_support = अणु
	.flags = WIPHY_WOWLAN_ANY
पूर्ण;

#पूर्ण_अगर

अटल अंतरभूत u8 get_sta_index(काष्ठा ieee80211_vअगर *vअगर,
			       काष्ठा wcn36xx_sta *sta_priv)
अणु
	वापस NL80211_IFTYPE_STATION == vअगर->type ?
	       sta_priv->bss_sta_index :
	       sta_priv->sta_index;
पूर्ण

अटल स्थिर अक्षर * स्थिर wcn36xx_caps_names[] = अणु
	"MCC",				/* 0 */
	"P2P",				/* 1 */
	"DOT11AC",			/* 2 */
	"SLM_SESSIONIZATION",		/* 3 */
	"DOT11AC_OPMODE",		/* 4 */
	"SAP32STA",			/* 5 */
	"TDLS",				/* 6 */
	"P2P_GO_NOA_DECOUPLE_INIT_SCAN",/* 7 */
	"WLANACTIVE_OFFLOAD",		/* 8 */
	"BEACON_OFFLOAD",		/* 9 */
	"SCAN_OFFLOAD",			/* 10 */
	"ROAM_OFFLOAD",			/* 11 */
	"BCN_MISS_OFFLOAD",		/* 12 */
	"STA_POWERSAVE",		/* 13 */
	"STA_ADVANCED_PWRSAVE",		/* 14 */
	"AP_UAPSD",			/* 15 */
	"AP_DFS",			/* 16 */
	"BLOCKACK",			/* 17 */
	"PHY_ERR",			/* 18 */
	"BCN_FILTER",			/* 19 */
	"RTT",				/* 20 */
	"RATECTRL",			/* 21 */
	"WOW",				/* 22 */
	"WLAN_ROAM_SCAN_OFFLOAD",	/* 23 */
	"SPECULATIVE_PS_POLL",		/* 24 */
	"SCAN_SCH",			/* 25 */
	"IBSS_HEARTBEAT_OFFLOAD",	/* 26 */
	"WLAN_SCAN_OFFLOAD",		/* 27 */
	"WLAN_PERIODIC_TX_PTRN",	/* 28 */
	"ADVANCE_TDLS",			/* 29 */
	"BATCH_SCAN",			/* 30 */
	"FW_IN_TX_PATH",		/* 31 */
	"EXTENDED_NSOFFLOAD_SLOT",	/* 32 */
	"CH_SWITCH_V1",			/* 33 */
	"HT40_OBSS_SCAN",		/* 34 */
	"UPDATE_CHANNEL_LIST",		/* 35 */
	"WLAN_MCADDR_FLT",		/* 36 */
	"WLAN_CH144",			/* 37 */
	"NAN",				/* 38 */
	"TDLS_SCAN_COEXISTENCE",	/* 39 */
	"LINK_LAYER_STATS_MEAS",	/* 40 */
	"MU_MIMO",			/* 41 */
	"EXTENDED_SCAN",		/* 42 */
	"DYNAMIC_WMM_PS",		/* 43 */
	"MAC_SPOOFED_SCAN",		/* 44 */
	"BMU_ERROR_GENERIC_RECOVERY",	/* 45 */
	"DISA",				/* 46 */
	"FW_STATS",			/* 47 */
	"WPS_PRBRSP_TMPL",		/* 48 */
	"BCN_IE_FLT_DELTA",		/* 49 */
	"TDLS_OFF_CHANNEL",		/* 51 */
	"RTT3",				/* 52 */
	"MGMT_FRAME_LOGGING",		/* 53 */
	"ENHANCED_TXBD_COMPLETION",	/* 54 */
	"LOGGING_ENHANCEMENT",		/* 55 */
	"EXT_SCAN_ENHANCED",		/* 56 */
	"MEMORY_DUMP_SUPPORTED",	/* 57 */
	"PER_PKT_STATS_SUPPORTED",	/* 58 */
	"EXT_LL_STAT",			/* 60 */
	"WIFI_CONFIG",			/* 61 */
	"ANTENNA_DIVERSITY_SELECTION",	/* 62 */
पूर्ण;

अटल स्थिर अक्षर *wcn36xx_get_cap_name(क्रमागत place_holder_in_cap_biपंचांगap x)
अणु
	अगर (x >= ARRAY_SIZE(wcn36xx_caps_names))
		वापस "UNKNOWN";
	वापस wcn36xx_caps_names[x];
पूर्ण

अटल व्योम wcn36xx_feat_caps_info(काष्ठा wcn36xx *wcn)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < MAX_FEATURE_SUPPORTED; i++) अणु
		अगर (get_feat_caps(wcn->fw_feat_caps, i))
			wcn36xx_dbg(WCN36XX_DBG_MAC, "FW Cap %s\n", wcn36xx_get_cap_name(i));
	पूर्ण
पूर्ण

अटल पूर्णांक wcn36xx_start(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	पूर्णांक ret;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac start\n");

	/* SMD initialization */
	ret = wcn36xx_smd_खोलो(wcn);
	अगर (ret) अणु
		wcn36xx_err("Failed to open smd channel: %d\n", ret);
		जाओ out_err;
	पूर्ण

	/* Allocate memory pools क्रम Mgmt BD headers and Data BD headers */
	ret = wcn36xx_dxe_allocate_mem_pools(wcn);
	अगर (ret) अणु
		wcn36xx_err("Failed to alloc DXE mempool: %d\n", ret);
		जाओ out_smd_बंद;
	पूर्ण

	ret = wcn36xx_dxe_alloc_ctl_blks(wcn);
	अगर (ret) अणु
		wcn36xx_err("Failed to alloc DXE ctl blocks: %d\n", ret);
		जाओ out_मुक्त_dxe_pool;
	पूर्ण

	wcn->hal_buf = kदो_स्मृति(WCN36XX_HAL_BUF_SIZE, GFP_KERNEL);
	अगर (!wcn->hal_buf) अणु
		wcn36xx_err("Failed to allocate smd buf\n");
		ret = -ENOMEM;
		जाओ out_मुक्त_dxe_ctl;
	पूर्ण

	ret = wcn36xx_smd_load_nv(wcn);
	अगर (ret) अणु
		wcn36xx_err("Failed to push NV to chip\n");
		जाओ out_मुक्त_smd_buf;
	पूर्ण

	ret = wcn36xx_smd_start(wcn);
	अगर (ret) अणु
		wcn36xx_err("Failed to start chip\n");
		जाओ out_मुक्त_smd_buf;
	पूर्ण

	अगर (!wcn36xx_is_fw_version(wcn, 1, 2, 2, 24)) अणु
		ret = wcn36xx_smd_feature_caps_exchange(wcn);
		अगर (ret)
			wcn36xx_warn("Exchange feature caps failed\n");
		अन्यथा
			wcn36xx_feat_caps_info(wcn);
	पूर्ण

	/* DMA channel initialization */
	ret = wcn36xx_dxe_init(wcn);
	अगर (ret) अणु
		wcn36xx_err("DXE init failed\n");
		जाओ out_smd_stop;
	पूर्ण

	wcn36xx_debugfs_init(wcn);

	INIT_LIST_HEAD(&wcn->vअगर_list);
	spin_lock_init(&wcn->dxe_lock);

	वापस 0;

out_smd_stop:
	wcn36xx_smd_stop(wcn);
out_मुक्त_smd_buf:
	kमुक्त(wcn->hal_buf);
out_मुक्त_dxe_ctl:
	wcn36xx_dxe_मुक्त_ctl_blks(wcn);
out_मुक्त_dxe_pool:
	wcn36xx_dxe_मुक्त_mem_pools(wcn);
out_smd_बंद:
	wcn36xx_smd_बंद(wcn);
out_err:
	वापस ret;
पूर्ण

अटल व्योम wcn36xx_stop(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac stop\n");

	mutex_lock(&wcn->scan_lock);
	अगर (wcn->scan_req) अणु
		काष्ठा cfg80211_scan_info scan_info = अणु
			.पातed = true,
		पूर्ण;

		ieee80211_scan_completed(wcn->hw, &scan_info);
	पूर्ण
	wcn->scan_req = शून्य;
	mutex_unlock(&wcn->scan_lock);

	wcn36xx_debugfs_निकास(wcn);
	wcn36xx_smd_stop(wcn);
	wcn36xx_dxe_deinit(wcn);
	wcn36xx_smd_बंद(wcn);

	wcn36xx_dxe_मुक्त_mem_pools(wcn);
	wcn36xx_dxe_मुक्त_ctl_blks(wcn);

	kमुक्त(wcn->hal_buf);
पूर्ण

अटल व्योम wcn36xx_change_ps(काष्ठा wcn36xx *wcn, bool enable)
अणु
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	काष्ठा wcn36xx_vअगर *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &wcn->vअगर_list, list) अणु
		vअगर = wcn36xx_priv_to_vअगर(पंचांगp);
		अगर (enable && !wcn->sw_scan) अणु
			अगर (vअगर->bss_conf.ps) /* ps allowed ? */
				wcn36xx_pmc_enter_bmps_state(wcn, vअगर);
		पूर्ण अन्यथा अणु
			wcn36xx_pmc_निकास_bmps_state(wcn, vअगर);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम wcn36xx_change_opchannel(काष्ठा wcn36xx *wcn, पूर्णांक ch)
अणु
	काष्ठा ieee80211_vअगर *vअगर = शून्य;
	काष्ठा wcn36xx_vअगर *पंचांगp;

	list_क्रम_each_entry(पंचांगp, &wcn->vअगर_list, list) अणु
		vअगर = wcn36xx_priv_to_vअगर(पंचांगp);
		wcn36xx_smd_चयन_channel(wcn, vअगर, ch);
	पूर्ण
पूर्ण

अटल पूर्णांक wcn36xx_config(काष्ठा ieee80211_hw *hw, u32 changed)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac config changed 0x%08x\n", changed);

	mutex_lock(&wcn->conf_mutex);

	अगर (changed & IEEE80211_CONF_CHANGE_CHANNEL) अणु
		पूर्णांक ch = WCN36XX_HW_CHANNEL(wcn);
		wcn36xx_dbg(WCN36XX_DBG_MAC, "wcn36xx_config channel switch=%d\n",
			    ch);

		अगर (wcn->sw_scan_opchannel == ch) अणु
			/* If channel is the initial operating channel, we may
			 * want to receive/transmit regular data packets, then
			 * simply stop the scan session and निकास PS mode.
			 */
			wcn36xx_smd_finish_scan(wcn, HAL_SYS_MODE_SCAN,
						wcn->sw_scan_vअगर);
		पूर्ण अन्यथा अगर (wcn->sw_scan) अणु
			/* A scan is ongoing, करो not change the operating
			 * channel, but start a scan session on the channel.
			 */
			wcn36xx_smd_init_scan(wcn, HAL_SYS_MODE_SCAN,
					      wcn->sw_scan_vअगर);
			wcn36xx_smd_start_scan(wcn, ch);
		पूर्ण अन्यथा अणु
			wcn36xx_change_opchannel(wcn, ch);
		पूर्ण
	पूर्ण

	अगर (changed & IEEE80211_CONF_CHANGE_PS)
		wcn36xx_change_ps(wcn, hw->conf.flags & IEEE80211_CONF_PS);

	mutex_unlock(&wcn->conf_mutex);

	वापस 0;
पूर्ण

अटल व्योम wcn36xx_configure_filter(काष्ठा ieee80211_hw *hw,
				     अचिन्हित पूर्णांक changed,
				     अचिन्हित पूर्णांक *total, u64 multicast)
अणु
	काष्ठा wcn36xx_hal_rcv_flt_mc_addr_list_type *fp;
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_vअगर *पंचांगp;
	काष्ठा ieee80211_vअगर *vअगर = शून्य;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac configure filter\n");

	mutex_lock(&wcn->conf_mutex);

	*total &= FIF_ALLMULTI;

	fp = (व्योम *)(अचिन्हित दीर्घ)multicast;
	list_क्रम_each_entry(पंचांगp, &wcn->vअगर_list, list) अणु
		vअगर = wcn36xx_priv_to_vअगर(पंचांगp);

		/* FW handles MC filtering only when connected as STA */
		अगर (*total & FIF_ALLMULTI)
			wcn36xx_smd_set_mc_list(wcn, vअगर, शून्य);
		अन्यथा अगर (NL80211_IFTYPE_STATION == vअगर->type && पंचांगp->sta_assoc)
			wcn36xx_smd_set_mc_list(wcn, vअगर, fp);
	पूर्ण

	mutex_unlock(&wcn->conf_mutex);
	kमुक्त(fp);
पूर्ण

अटल u64 wcn36xx_prepare_multicast(काष्ठा ieee80211_hw *hw,
				     काष्ठा netdev_hw_addr_list *mc_list)
अणु
	काष्ठा wcn36xx_hal_rcv_flt_mc_addr_list_type *fp;
	काष्ठा netdev_hw_addr *ha;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac prepare multicast list\n");
	fp = kzalloc(माप(*fp), GFP_ATOMIC);
	अगर (!fp) अणु
		wcn36xx_err("Out of memory setting filters.\n");
		वापस 0;
	पूर्ण

	fp->mc_addr_count = 0;
	/* update multicast filtering parameters */
	अगर (netdev_hw_addr_list_count(mc_list) <=
	    WCN36XX_HAL_MAX_NUM_MULTICAST_ADDRESS) अणु
		netdev_hw_addr_list_क्रम_each(ha, mc_list) अणु
			स_नकल(fp->mc_addr[fp->mc_addr_count],
					ha->addr, ETH_ALEN);
			fp->mc_addr_count++;
		पूर्ण
	पूर्ण

	वापस (u64)(अचिन्हित दीर्घ)fp;
पूर्ण

अटल व्योम wcn36xx_tx(काष्ठा ieee80211_hw *hw,
		       काष्ठा ieee80211_tx_control *control,
		       काष्ठा sk_buff *skb)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_sta *sta_priv = शून्य;

	अगर (control->sta)
		sta_priv = wcn36xx_sta_to_priv(control->sta);

	अगर (wcn36xx_start_tx(wcn, sta_priv, skb))
		ieee80211_मुक्त_txskb(wcn->hw, skb);
पूर्ण

अटल पूर्णांक wcn36xx_set_key(काष्ठा ieee80211_hw *hw, क्रमागत set_key_cmd cmd,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta,
			   काष्ठा ieee80211_key_conf *key_conf)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	काष्ठा wcn36xx_sta *sta_priv = sta ? wcn36xx_sta_to_priv(sta) : शून्य;
	पूर्णांक ret = 0;
	u8 key[WLAN_MAX_KEY_LEN];

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac80211 set key\n");
	wcn36xx_dbg(WCN36XX_DBG_MAC, "Key: cmd=0x%x algo:0x%x, id:%d, len:%d flags 0x%x\n",
		    cmd, key_conf->cipher, key_conf->keyidx,
		    key_conf->keylen, key_conf->flags);
	wcn36xx_dbg_dump(WCN36XX_DBG_MAC, "KEY: ",
			 key_conf->key,
			 key_conf->keylen);

	mutex_lock(&wcn->conf_mutex);

	चयन (key_conf->cipher) अणु
	हाल WLAN_CIPHER_SUITE_WEP40:
		vअगर_priv->encrypt_type = WCN36XX_HAL_ED_WEP40;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_WEP104:
		vअगर_priv->encrypt_type = WCN36XX_HAL_ED_WEP104;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_CCMP:
		vअगर_priv->encrypt_type = WCN36XX_HAL_ED_CCMP;
		अवरोध;
	हाल WLAN_CIPHER_SUITE_TKIP:
		vअगर_priv->encrypt_type = WCN36XX_HAL_ED_TKIP;
		अवरोध;
	शेष:
		wcn36xx_err("Unsupported key type 0x%x\n",
			      key_conf->cipher);
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

	चयन (cmd) अणु
	हाल SET_KEY:
		अगर (WCN36XX_HAL_ED_TKIP == vअगर_priv->encrypt_type) अणु
			/*
			 * Supplicant is sending key in the wrong order:
			 * Temporal Key (16 b) - TX MIC (8 b) - RX MIC (8 b)
			 * but HW expects it to be in the order as described in
			 * IEEE 802.11 spec (see chapter 11.7) like this:
			 * Temporal Key (16 b) - RX MIC (8 b) - TX MIC (8 b)
			 */
			स_नकल(key, key_conf->key, 16);
			स_नकल(key + 16, key_conf->key + 24, 8);
			स_नकल(key + 24, key_conf->key + 16, 8);
		पूर्ण अन्यथा अणु
			स_नकल(key, key_conf->key, key_conf->keylen);
		पूर्ण

		अगर (IEEE80211_KEY_FLAG_PAIRWISE & key_conf->flags) अणु
			sta_priv->is_data_encrypted = true;
			/* Reconfigure bss with encrypt_type */
			अगर (NL80211_IFTYPE_STATION == vअगर->type)
				wcn36xx_smd_config_bss(wcn,
						       vअगर,
						       sta,
						       sta->addr,
						       true);

			wcn36xx_smd_set_stakey(wcn,
				vअगर_priv->encrypt_type,
				key_conf->keyidx,
				key_conf->keylen,
				key,
				get_sta_index(vअगर, sta_priv));
		पूर्ण अन्यथा अणु
			wcn36xx_smd_set_bsskey(wcn,
				vअगर_priv->encrypt_type,
				vअगर_priv->bss_index,
				key_conf->keyidx,
				key_conf->keylen,
				key);

			अगर ((WLAN_CIPHER_SUITE_WEP40 == key_conf->cipher) ||
			    (WLAN_CIPHER_SUITE_WEP104 == key_conf->cipher)) अणु
				list_क्रम_each_entry(sta_priv,
						    &vअगर_priv->sta_list, list) अणु
					sta_priv->is_data_encrypted = true;
					wcn36xx_smd_set_stakey(wcn,
						vअगर_priv->encrypt_type,
						key_conf->keyidx,
						key_conf->keylen,
						key,
						get_sta_index(vअगर, sta_priv));
				पूर्ण
			पूर्ण
		पूर्ण
		/* FIXME: Only enable bmps support when encryption is enabled.
		 * For any reasons, when connected to खोलो/no-security BSS,
		 * the wcn36xx controller in bmps mode करोes not क्रमward
		 * 'wake-up' beacons despite AP sends DTIM with station AID.
		 * It could be due to a firmware issue or to the way driver
		 * configure the station.
		 */
		अगर (vअगर->type == NL80211_IFTYPE_STATION)
			vअगर_priv->allow_bmps = true;
		अवरोध;
	हाल DISABLE_KEY:
		अगर (!(IEEE80211_KEY_FLAG_PAIRWISE & key_conf->flags)) अणु
			अगर (vअगर_priv->bss_index != WCN36XX_HAL_BSS_INVALID_IDX)
				wcn36xx_smd_हटाओ_bsskey(wcn,
					vअगर_priv->encrypt_type,
					vअगर_priv->bss_index,
					key_conf->keyidx);

			vअगर_priv->encrypt_type = WCN36XX_HAL_ED_NONE;
		पूर्ण अन्यथा अणु
			sta_priv->is_data_encrypted = false;
			/* करो not हटाओ key अगर disassociated */
			अगर (sta_priv->aid)
				wcn36xx_smd_हटाओ_stakey(wcn,
					vअगर_priv->encrypt_type,
					key_conf->keyidx,
					get_sta_index(vअगर, sta_priv));
		पूर्ण
		अवरोध;
	शेष:
		wcn36xx_err("Unsupported key cmd 0x%x\n", cmd);
		ret = -EOPNOTSUPP;
		जाओ out;
	पूर्ण

out:
	mutex_unlock(&wcn->conf_mutex);

	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_hw_scan(काष्ठा ieee80211_hw *hw,
			   काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_scan_request *hw_req)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	पूर्णांक i;

	अगर (!get_feat_caps(wcn->fw_feat_caps, SCAN_OFFLOAD)) अणु
		/* fallback to mac80211 software scan */
		वापस 1;
	पूर्ण

	/* For unknown reason, the hardware offloaded scan only works with
	 * 2.4Ghz channels, fallback to software scan in other हालs.
	 */
	क्रम (i = 0; i < hw_req->req.n_channels; i++) अणु
		अगर (hw_req->req.channels[i]->band != NL80211_BAND_2GHZ)
			वापस 1;
	पूर्ण

	mutex_lock(&wcn->scan_lock);
	अगर (wcn->scan_req) अणु
		mutex_unlock(&wcn->scan_lock);
		वापस -EBUSY;
	पूर्ण

	wcn->scan_पातed = false;
	wcn->scan_req = &hw_req->req;

	mutex_unlock(&wcn->scan_lock);

	वापस wcn36xx_smd_start_hw_scan(wcn, vअगर, &hw_req->req);
पूर्ण

अटल व्योम wcn36xx_cancel_hw_scan(काष्ठा ieee80211_hw *hw,
				   काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;

	mutex_lock(&wcn->scan_lock);
	wcn->scan_पातed = true;
	mutex_unlock(&wcn->scan_lock);

	अगर (get_feat_caps(wcn->fw_feat_caps, SCAN_OFFLOAD)) अणु
		/* ieee80211_scan_completed will be called on FW scan
		 * indication */
		wcn36xx_smd_stop_hw_scan(wcn);
	पूर्ण
पूर्ण

अटल व्योम wcn36xx_sw_scan_start(काष्ठा ieee80211_hw *hw,
				  काष्ठा ieee80211_vअगर *vअगर,
				  स्थिर u8 *mac_addr)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);

	wcn->sw_scan = true;
	wcn->sw_scan_vअगर = vअगर;
	अगर (vअगर_priv->sta_assoc)
		wcn->sw_scan_opchannel = WCN36XX_HW_CHANNEL(wcn);
	अन्यथा
		wcn->sw_scan_opchannel = 0;
पूर्ण

अटल व्योम wcn36xx_sw_scan_complete(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;

	/* ensure that any scan session is finished */
	wcn36xx_smd_finish_scan(wcn, HAL_SYS_MODE_SCAN, wcn->sw_scan_vअगर);
	wcn->sw_scan = false;
	wcn->sw_scan_opchannel = 0;
पूर्ण

अटल व्योम wcn36xx_update_allowed_rates(काष्ठा ieee80211_sta *sta,
					 क्रमागत nl80211_band band)
अणु
	पूर्णांक i, size;
	u16 *rates_table;
	काष्ठा wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);
	u32 rates = sta->supp_rates[band];

	स_रखो(&sta_priv->supported_rates, 0,
		माप(sta_priv->supported_rates));
	sta_priv->supported_rates.op_rate_mode = STA_11n;

	size = ARRAY_SIZE(sta_priv->supported_rates.dsss_rates);
	rates_table = sta_priv->supported_rates.dsss_rates;
	अगर (band == NL80211_BAND_2GHZ) अणु
		क्रम (i = 0; i < size; i++) अणु
			अगर (rates & 0x01) अणु
				rates_table[i] = wcn_2ghz_rates[i].hw_value;
				rates = rates >> 1;
			पूर्ण
		पूर्ण
	पूर्ण

	size = ARRAY_SIZE(sta_priv->supported_rates.ofdm_rates);
	rates_table = sta_priv->supported_rates.ofdm_rates;
	क्रम (i = 0; i < size; i++) अणु
		अगर (rates & 0x01) अणु
			rates_table[i] = wcn_5ghz_rates[i].hw_value;
			rates = rates >> 1;
		पूर्ण
	पूर्ण

	अगर (sta->ht_cap.ht_supported) अणु
		BUILD_BUG_ON(माप(sta->ht_cap.mcs.rx_mask) >
			माप(sta_priv->supported_rates.supported_mcs_set));
		स_नकल(sta_priv->supported_rates.supported_mcs_set,
		       sta->ht_cap.mcs.rx_mask,
		       माप(sta->ht_cap.mcs.rx_mask));
	पूर्ण

	अगर (sta->vht_cap.vht_supported) अणु
		sta_priv->supported_rates.op_rate_mode = STA_11ac;
		sta_priv->supported_rates.vht_rx_mcs_map =
				sta->vht_cap.vht_mcs.rx_mcs_map;
		sta_priv->supported_rates.vht_tx_mcs_map =
				sta->vht_cap.vht_mcs.tx_mcs_map;
	पूर्ण
पूर्ण

व्योम wcn36xx_set_शेष_rates(काष्ठा wcn36xx_hal_supported_rates *rates)
अणु
	u16 ofdm_rates[WCN36XX_HAL_NUM_OFDM_RATES] = अणु
		HW_RATE_INDEX_6MBPS,
		HW_RATE_INDEX_9MBPS,
		HW_RATE_INDEX_12MBPS,
		HW_RATE_INDEX_18MBPS,
		HW_RATE_INDEX_24MBPS,
		HW_RATE_INDEX_36MBPS,
		HW_RATE_INDEX_48MBPS,
		HW_RATE_INDEX_54MBPS
	पूर्ण;
	u16 dsss_rates[WCN36XX_HAL_NUM_DSSS_RATES] = अणु
		HW_RATE_INDEX_1MBPS,
		HW_RATE_INDEX_2MBPS,
		HW_RATE_INDEX_5_5MBPS,
		HW_RATE_INDEX_11MBPS
	पूर्ण;

	rates->op_rate_mode = STA_11n;
	स_नकल(rates->dsss_rates, dsss_rates,
		माप(*dsss_rates) * WCN36XX_HAL_NUM_DSSS_RATES);
	स_नकल(rates->ofdm_rates, ofdm_rates,
		माप(*ofdm_rates) * WCN36XX_HAL_NUM_OFDM_RATES);
	rates->supported_mcs_set[0] = 0xFF;
पूर्ण

व्योम wcn36xx_set_शेष_rates_v1(काष्ठा wcn36xx_hal_supported_rates_v1 *rates)
अणु
	rates->op_rate_mode = STA_11ac;
	rates->vht_rx_mcs_map = IEEE80211_VHT_MCS_SUPPORT_0_9;
	rates->vht_tx_mcs_map = IEEE80211_VHT_MCS_SUPPORT_0_9;
पूर्ण

अटल व्योम wcn36xx_bss_info_changed(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर,
				     काष्ठा ieee80211_bss_conf *bss_conf,
				     u32 changed)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा sk_buff *skb = शून्य;
	u16 tim_off, tim_len;
	क्रमागत wcn36xx_hal_link_state link_state;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss info changed vif %p changed 0x%08x\n",
		    vअगर, changed);

	mutex_lock(&wcn->conf_mutex);

	अगर (changed & BSS_CHANGED_BEACON_INFO) अणु
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed dtim period %d\n",
			    bss_conf->dtim_period);

		vअगर_priv->dtim_period = bss_conf->dtim_period;
	पूर्ण

	अगर (changed & BSS_CHANGED_BSSID) अणु
		wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss changed_bssid %pM\n",
			    bss_conf->bssid);

		अगर (!is_zero_ether_addr(bss_conf->bssid)) अणु
			vअगर_priv->is_joining = true;
			vअगर_priv->bss_index = WCN36XX_HAL_BSS_INVALID_IDX;
			wcn36xx_smd_set_link_st(wcn, bss_conf->bssid, vअगर->addr,
						WCN36XX_HAL_LINK_PREASSOC_STATE);
			wcn36xx_smd_join(wcn, bss_conf->bssid,
					 vअगर->addr, WCN36XX_HW_CHANNEL(wcn));
			wcn36xx_smd_config_bss(wcn, vअगर, शून्य,
					       bss_conf->bssid, false);
		पूर्ण अन्यथा अणु
			vअगर_priv->is_joining = false;
			wcn36xx_smd_delete_bss(wcn, vअगर);
			wcn36xx_smd_set_link_st(wcn, bss_conf->bssid, vअगर->addr,
						WCN36XX_HAL_LINK_IDLE_STATE);
			vअगर_priv->encrypt_type = WCN36XX_HAL_ED_NONE;
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_SSID) अणु
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed ssid\n");
		wcn36xx_dbg_dump(WCN36XX_DBG_MAC, "ssid ",
				 bss_conf->ssid, bss_conf->ssid_len);

		vअगर_priv->ssid.length = bss_conf->ssid_len;
		स_नकल(&vअगर_priv->ssid.ssid,
		       bss_conf->ssid,
		       bss_conf->ssid_len);
	पूर्ण

	अगर (changed & BSS_CHANGED_ASSOC) अणु
		vअगर_priv->is_joining = false;
		अगर (bss_conf->assoc) अणु
			काष्ठा ieee80211_sta *sta;
			काष्ठा wcn36xx_sta *sta_priv;

			wcn36xx_dbg(WCN36XX_DBG_MAC,
				    "mac assoc bss %pM vif %pM AID=%d\n",
				     bss_conf->bssid,
				     vअगर->addr,
				     bss_conf->aid);

			vअगर_priv->sta_assoc = true;

			/*
			 * Holding conf_mutex ensures mutal exclusion with
			 * wcn36xx_sta_हटाओ() and as such ensures that sta
			 * won't be freed while we're operating on it. As such
			 * we करो not need to hold the rcu_पढ़ो_lock().
			 */
			sta = ieee80211_find_sta(vअगर, bss_conf->bssid);
			अगर (!sta) अणु
				wcn36xx_err("sta %pM is not found\n",
					      bss_conf->bssid);
				जाओ out;
			पूर्ण
			sta_priv = wcn36xx_sta_to_priv(sta);

			wcn36xx_update_allowed_rates(sta, WCN36XX_BAND(wcn));

			wcn36xx_smd_set_link_st(wcn, bss_conf->bssid,
				vअगर->addr,
				WCN36XX_HAL_LINK_POSTASSOC_STATE);
			wcn36xx_smd_config_bss(wcn, vअगर, sta,
					       bss_conf->bssid,
					       true);
			sta_priv->aid = bss_conf->aid;
			/*
			 * config_sta must be called from  because this is the
			 * place where AID is available.
			 */
			wcn36xx_smd_config_sta(wcn, vअगर, sta);
			wcn36xx_enable_keep_alive_null_packet(wcn, vअगर);
		पूर्ण अन्यथा अणु
			wcn36xx_dbg(WCN36XX_DBG_MAC,
				    "disassociated bss %pM vif %pM AID=%d\n",
				    bss_conf->bssid,
				    vअगर->addr,
				    bss_conf->aid);
			vअगर_priv->sta_assoc = false;
			vअगर_priv->allow_bmps = false;
			wcn36xx_smd_set_link_st(wcn,
						bss_conf->bssid,
						vअगर->addr,
						WCN36XX_HAL_LINK_IDLE_STATE);
		पूर्ण
	पूर्ण

	अगर (changed & BSS_CHANGED_AP_PROBE_RESP) अणु
		wcn36xx_dbg(WCN36XX_DBG_MAC, "mac bss changed ap probe resp\n");
		skb = ieee80211_proberesp_get(hw, vअगर);
		अगर (!skb) अणु
			wcn36xx_err("failed to alloc probereq skb\n");
			जाओ out;
		पूर्ण

		wcn36xx_smd_update_proberesp_पंचांगpl(wcn, vअगर, skb);
		dev_kमुक्त_skb(skb);
	पूर्ण

	अगर (changed & BSS_CHANGED_BEACON_ENABLED ||
	    changed & BSS_CHANGED_BEACON) अणु
		wcn36xx_dbg(WCN36XX_DBG_MAC,
			    "mac bss changed beacon enabled %d\n",
			    bss_conf->enable_beacon);

		अगर (bss_conf->enable_beacon) अणु
			vअगर_priv->dtim_period = bss_conf->dtim_period;
			vअगर_priv->bss_index = WCN36XX_HAL_BSS_INVALID_IDX;
			wcn36xx_smd_config_bss(wcn, vअगर, शून्य,
					       vअगर->addr, false);
			skb = ieee80211_beacon_get_tim(hw, vअगर, &tim_off,
						       &tim_len);
			अगर (!skb) अणु
				wcn36xx_err("failed to alloc beacon skb\n");
				जाओ out;
			पूर्ण
			wcn36xx_smd_send_beacon(wcn, vअगर, skb, tim_off, 0);
			dev_kमुक्त_skb(skb);

			अगर (vअगर->type == NL80211_IFTYPE_ADHOC ||
			    vअगर->type == NL80211_IFTYPE_MESH_POINT)
				link_state = WCN36XX_HAL_LINK_IBSS_STATE;
			अन्यथा
				link_state = WCN36XX_HAL_LINK_AP_STATE;

			wcn36xx_smd_set_link_st(wcn, vअगर->addr, vअगर->addr,
						link_state);
		पूर्ण अन्यथा अणु
			wcn36xx_smd_delete_bss(wcn, vअगर);
			wcn36xx_smd_set_link_st(wcn, vअगर->addr, vअगर->addr,
						WCN36XX_HAL_LINK_IDLE_STATE);
		पूर्ण
	पूर्ण
out:

	mutex_unlock(&wcn->conf_mutex);
पूर्ण

/* this is required when using IEEE80211_HW_HAS_RATE_CONTROL */
अटल पूर्णांक wcn36xx_set_rts_threshold(काष्ठा ieee80211_hw *hw, u32 value)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac set RTS threshold %d\n", value);

	mutex_lock(&wcn->conf_mutex);
	wcn36xx_smd_update_cfg(wcn, WCN36XX_HAL_CFG_RTS_THRESHOLD, value);
	mutex_unlock(&wcn->conf_mutex);

	वापस 0;
पूर्ण

अटल व्योम wcn36xx_हटाओ_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac remove interface vif %p\n", vअगर);

	mutex_lock(&wcn->conf_mutex);

	list_del(&vअगर_priv->list);
	wcn36xx_smd_delete_sta_self(wcn, vअगर->addr);

	mutex_unlock(&wcn->conf_mutex);
पूर्ण

अटल पूर्णांक wcn36xx_add_पूर्णांकerface(काष्ठा ieee80211_hw *hw,
				 काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac add interface vif %p type %d\n",
		    vअगर, vअगर->type);

	अगर (!(NL80211_IFTYPE_STATION == vअगर->type ||
	      NL80211_IFTYPE_AP == vअगर->type ||
	      NL80211_IFTYPE_ADHOC == vअगर->type ||
	      NL80211_IFTYPE_MESH_POINT == vअगर->type)) अणु
		wcn36xx_warn("Unsupported interface type requested: %d\n",
			     vअगर->type);
		वापस -EOPNOTSUPP;
	पूर्ण

	mutex_lock(&wcn->conf_mutex);

	vअगर_priv->bss_index = WCN36XX_HAL_BSS_INVALID_IDX;
	INIT_LIST_HEAD(&vअगर_priv->sta_list);
	list_add(&vअगर_priv->list, &wcn->vअगर_list);
	wcn36xx_smd_add_sta_self(wcn, vअगर);

	mutex_unlock(&wcn->conf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_sta_add(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_vअगर *vअगर_priv = wcn36xx_vअगर_to_priv(vअगर);
	काष्ठा wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);
	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac sta add vif %p sta %pM\n",
		    vअगर, sta->addr);

	mutex_lock(&wcn->conf_mutex);

	spin_lock_init(&sta_priv->ampdu_lock);
	sta_priv->vअगर = vअगर_priv;
	list_add(&sta_priv->list, &vअगर_priv->sta_list);

	/*
	 * For STA mode HW will be configured on BSS_CHANGED_ASSOC because
	 * at this stage AID is not available yet.
	 */
	अगर (NL80211_IFTYPE_STATION != vअगर->type) अणु
		wcn36xx_update_allowed_rates(sta, WCN36XX_BAND(wcn));
		sta_priv->aid = sta->aid;
		wcn36xx_smd_config_sta(wcn, vअगर, sta);
	पूर्ण

	mutex_unlock(&wcn->conf_mutex);

	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_sta_हटाओ(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा ieee80211_sta *sta)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(sta);

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac sta remove vif %p sta %pM index %d\n",
		    vअगर, sta->addr, sta_priv->sta_index);

	mutex_lock(&wcn->conf_mutex);

	list_del(&sta_priv->list);
	wcn36xx_smd_delete_sta(wcn, sta_priv->sta_index);
	sta_priv->vअगर = शून्य;

	mutex_unlock(&wcn->conf_mutex);

	वापस 0;
पूर्ण

#अगर_घोषित CONFIG_PM

अटल पूर्णांक wcn36xx_suspend(काष्ठा ieee80211_hw *hw, काष्ठा cfg80211_wowlan *wow)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac suspend\n");

	flush_workqueue(wcn->hal_ind_wq);
	wcn36xx_smd_set_घातer_params(wcn, true);
	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_resume(काष्ठा ieee80211_hw *hw)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac resume\n");

	flush_workqueue(wcn->hal_ind_wq);
	wcn36xx_smd_set_घातer_params(wcn, false);
	वापस 0;
पूर्ण

#पूर्ण_अगर

अटल पूर्णांक wcn36xx_ampdu_action(काष्ठा ieee80211_hw *hw,
		    काष्ठा ieee80211_vअगर *vअगर,
		    काष्ठा ieee80211_ampdu_params *params)
अणु
	काष्ठा wcn36xx *wcn = hw->priv;
	काष्ठा wcn36xx_sta *sta_priv = wcn36xx_sta_to_priv(params->sta);
	काष्ठा ieee80211_sta *sta = params->sta;
	क्रमागत ieee80211_ampdu_mlme_action action = params->action;
	u16 tid = params->tid;
	u16 *ssn = &params->ssn;
	पूर्णांक ret = 0;
	u8 session;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "mac ampdu action action %d tid %d\n",
		    action, tid);

	mutex_lock(&wcn->conf_mutex);

	चयन (action) अणु
	हाल IEEE80211_AMPDU_RX_START:
		sta_priv->tid = tid;
		session = wcn36xx_smd_add_ba_session(wcn, sta, tid, ssn, 0,
						     get_sta_index(vअगर, sta_priv));
		wcn36xx_smd_add_ba(wcn, session);
		wcn36xx_smd_trigger_ba(wcn, get_sta_index(vअगर, sta_priv), tid,
				       session);
		अवरोध;
	हाल IEEE80211_AMPDU_RX_STOP:
		wcn36xx_smd_del_ba(wcn, tid, 0, get_sta_index(vअगर, sta_priv));
		अवरोध;
	हाल IEEE80211_AMPDU_TX_START:
		spin_lock_bh(&sta_priv->ampdu_lock);
		sta_priv->ampdu_state[tid] = WCN36XX_AMPDU_START;
		spin_unlock_bh(&sta_priv->ampdu_lock);

		ret = IEEE80211_AMPDU_TX_START_IMMEDIATE;
		अवरोध;
	हाल IEEE80211_AMPDU_TX_OPERATIONAL:
		spin_lock_bh(&sta_priv->ampdu_lock);
		sta_priv->ampdu_state[tid] = WCN36XX_AMPDU_OPERATIONAL;
		spin_unlock_bh(&sta_priv->ampdu_lock);

		wcn36xx_smd_add_ba_session(wcn, sta, tid, ssn, 1,
			get_sta_index(vअगर, sta_priv));
		अवरोध;
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH:
	हाल IEEE80211_AMPDU_TX_STOP_FLUSH_CONT:
	हाल IEEE80211_AMPDU_TX_STOP_CONT:
		spin_lock_bh(&sta_priv->ampdu_lock);
		sta_priv->ampdu_state[tid] = WCN36XX_AMPDU_NONE;
		spin_unlock_bh(&sta_priv->ampdu_lock);

		wcn36xx_smd_del_ba(wcn, tid, 1, get_sta_index(vअगर, sta_priv));
		ieee80211_stop_tx_ba_cb_irqsafe(vअगर, sta->addr, tid);
		अवरोध;
	शेष:
		wcn36xx_err("Unknown AMPDU action\n");
	पूर्ण

	mutex_unlock(&wcn->conf_mutex);

	वापस ret;
पूर्ण

अटल स्थिर काष्ठा ieee80211_ops wcn36xx_ops = अणु
	.start			= wcn36xx_start,
	.stop			= wcn36xx_stop,
	.add_पूर्णांकerface		= wcn36xx_add_पूर्णांकerface,
	.हटाओ_पूर्णांकerface	= wcn36xx_हटाओ_पूर्णांकerface,
#अगर_घोषित CONFIG_PM
	.suspend		= wcn36xx_suspend,
	.resume			= wcn36xx_resume,
#पूर्ण_अगर
	.config			= wcn36xx_config,
	.prepare_multicast	= wcn36xx_prepare_multicast,
	.configure_filter       = wcn36xx_configure_filter,
	.tx			= wcn36xx_tx,
	.set_key		= wcn36xx_set_key,
	.hw_scan		= wcn36xx_hw_scan,
	.cancel_hw_scan		= wcn36xx_cancel_hw_scan,
	.sw_scan_start		= wcn36xx_sw_scan_start,
	.sw_scan_complete	= wcn36xx_sw_scan_complete,
	.bss_info_changed	= wcn36xx_bss_info_changed,
	.set_rts_threshold	= wcn36xx_set_rts_threshold,
	.sta_add		= wcn36xx_sta_add,
	.sta_हटाओ		= wcn36xx_sta_हटाओ,
	.ampdu_action		= wcn36xx_ampdu_action,

	CFG80211_TESTMODE_CMD(wcn36xx_पंचांग_cmd)
पूर्ण;

अटल व्योम
wcn36xx_set_ieee80211_vht_caps(काष्ठा ieee80211_sta_vht_cap *vht_cap)
अणु
	vht_cap->vht_supported = true;

	vht_cap->cap = (IEEE80211_VHT_CAP_MAX_MPDU_LENGTH_3895 |
			IEEE80211_VHT_CAP_SHORT_GI_80 |
			IEEE80211_VHT_CAP_RXSTBC_1 |
			IEEE80211_VHT_CAP_SU_BEAMFORMEE_CAPABLE |
			IEEE80211_VHT_CAP_MU_BEAMFORMEE_CAPABLE |
			3 << IEEE80211_VHT_CAP_BEAMFORMEE_STS_SHIFT |
			7 << IEEE80211_VHT_CAP_MAX_A_MPDU_LENGTH_EXPONENT_SHIFT);

	vht_cap->vht_mcs.rx_mcs_map =
		cpu_to_le16(IEEE80211_VHT_MCS_SUPPORT_0_9 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 2 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 4 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 6 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 8 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 10 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 12 |
			    IEEE80211_VHT_MCS_NOT_SUPPORTED << 14);

	vht_cap->vht_mcs.rx_highest = cpu_to_le16(433);
	vht_cap->vht_mcs.tx_highest = vht_cap->vht_mcs.rx_highest;

	vht_cap->vht_mcs.tx_mcs_map = vht_cap->vht_mcs.rx_mcs_map;
पूर्ण

अटल पूर्णांक wcn36xx_init_ieee80211(काष्ठा wcn36xx *wcn)
अणु
	अटल स्थिर u32 cipher_suites[] = अणु
		WLAN_CIPHER_SUITE_WEP40,
		WLAN_CIPHER_SUITE_WEP104,
		WLAN_CIPHER_SUITE_TKIP,
		WLAN_CIPHER_SUITE_CCMP,
	पूर्ण;

	ieee80211_hw_set(wcn->hw, TIMING_BEACON_ONLY);
	ieee80211_hw_set(wcn->hw, AMPDU_AGGREGATION);
	ieee80211_hw_set(wcn->hw, SUPPORTS_PS);
	ieee80211_hw_set(wcn->hw, SIGNAL_DBM);
	ieee80211_hw_set(wcn->hw, HAS_RATE_CONTROL);
	ieee80211_hw_set(wcn->hw, SINGLE_SCAN_ON_ALL_BANDS);
	ieee80211_hw_set(wcn->hw, REPORTS_TX_ACK_STATUS);
	ieee80211_hw_set(wcn->hw, CONNECTION_MONITOR);

	wcn->hw->wiphy->पूर्णांकerface_modes = BIT(NL80211_IFTYPE_STATION) |
		BIT(NL80211_IFTYPE_AP) |
		BIT(NL80211_IFTYPE_ADHOC) |
		BIT(NL80211_IFTYPE_MESH_POINT);

	wcn->hw->wiphy->bands[NL80211_BAND_2GHZ] = &wcn_band_2ghz;
	अगर (wcn->rf_id != RF_IRIS_WCN3620)
		wcn->hw->wiphy->bands[NL80211_BAND_5GHZ] = &wcn_band_5ghz;

	अगर (wcn->rf_id == RF_IRIS_WCN3680)
		wcn36xx_set_ieee80211_vht_caps(&wcn_band_5ghz.vht_cap);

	wcn->hw->wiphy->max_scan_ssids = WCN36XX_MAX_SCAN_SSIDS;
	wcn->hw->wiphy->max_scan_ie_len = WCN36XX_MAX_SCAN_IE_LEN;

	wcn->hw->wiphy->cipher_suites = cipher_suites;
	wcn->hw->wiphy->n_cipher_suites = ARRAY_SIZE(cipher_suites);

#अगर_घोषित CONFIG_PM
	wcn->hw->wiphy->wowlan = &wowlan_support;
#पूर्ण_अगर

	wcn->hw->max_listen_पूर्णांकerval = 200;

	wcn->hw->queues = 4;

	SET_IEEE80211_DEV(wcn->hw, wcn->dev);

	wcn->hw->sta_data_size = माप(काष्ठा wcn36xx_sta);
	wcn->hw->vअगर_data_size = माप(काष्ठा wcn36xx_vअगर);

	wiphy_ext_feature_set(wcn->hw->wiphy,
			      NL80211_EXT_FEATURE_CQM_RSSI_LIST);

	वापस 0;
पूर्ण

अटल पूर्णांक wcn36xx_platक्रमm_get_resources(काष्ठा wcn36xx *wcn,
					  काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा device_node *mmio_node;
	काष्ठा device_node *iris_node;
	काष्ठा resource *res;
	पूर्णांक index;
	पूर्णांक ret;

	/* Set TX IRQ */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "tx");
	अगर (!res) अणु
		wcn36xx_err("failed to get tx_irq\n");
		वापस -ENOENT;
	पूर्ण
	wcn->tx_irq = res->start;

	/* Set RX IRQ */
	res = platक्रमm_get_resource_byname(pdev, IORESOURCE_IRQ, "rx");
	अगर (!res) अणु
		wcn36xx_err("failed to get rx_irq\n");
		वापस -ENOENT;
	पूर्ण
	wcn->rx_irq = res->start;

	/* Acquire SMSM tx enable handle */
	wcn->tx_enable_state = qcom_smem_state_get(&pdev->dev,
			"tx-enable", &wcn->tx_enable_state_bit);
	अगर (IS_ERR(wcn->tx_enable_state)) अणु
		wcn36xx_err("failed to get tx-enable state\n");
		वापस PTR_ERR(wcn->tx_enable_state);
	पूर्ण

	/* Acquire SMSM tx rings empty handle */
	wcn->tx_rings_empty_state = qcom_smem_state_get(&pdev->dev,
			"tx-rings-empty", &wcn->tx_rings_empty_state_bit);
	अगर (IS_ERR(wcn->tx_rings_empty_state)) अणु
		wcn36xx_err("failed to get tx-rings-empty state\n");
		वापस PTR_ERR(wcn->tx_rings_empty_state);
	पूर्ण

	mmio_node = of_parse_phandle(pdev->dev.parent->of_node, "qcom,mmio", 0);
	अगर (!mmio_node) अणु
		wcn36xx_err("failed to acquire qcom,mmio reference\n");
		वापस -EINVAL;
	पूर्ण

	wcn->is_pronto = !!of_device_is_compatible(mmio_node, "qcom,pronto");

	/* Map the CCU memory */
	index = of_property_match_string(mmio_node, "reg-names", "ccu");
	wcn->ccu_base = of_iomap(mmio_node, index);
	अगर (!wcn->ccu_base) अणु
		wcn36xx_err("failed to map ccu memory\n");
		ret = -ENOMEM;
		जाओ put_mmio_node;
	पूर्ण

	/* Map the DXE memory */
	index = of_property_match_string(mmio_node, "reg-names", "dxe");
	wcn->dxe_base = of_iomap(mmio_node, index);
	अगर (!wcn->dxe_base) अणु
		wcn36xx_err("failed to map dxe memory\n");
		ret = -ENOMEM;
		जाओ unmap_ccu;
	पूर्ण

	/* External RF module */
	iris_node = of_get_child_by_name(mmio_node, "iris");
	अगर (iris_node) अणु
		अगर (of_device_is_compatible(iris_node, "qcom,wcn3620"))
			wcn->rf_id = RF_IRIS_WCN3620;
		अगर (of_device_is_compatible(iris_node, "qcom,wcn3680"))
			wcn->rf_id = RF_IRIS_WCN3680;
		of_node_put(iris_node);
	पूर्ण

	of_node_put(mmio_node);
	वापस 0;

unmap_ccu:
	iounmap(wcn->ccu_base);
put_mmio_node:
	of_node_put(mmio_node);
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ieee80211_hw *hw;
	काष्ठा wcn36xx *wcn;
	व्योम *wcnss;
	पूर्णांक ret;
	स्थिर u8 *addr;

	wcn36xx_dbg(WCN36XX_DBG_MAC, "platform probe\n");

	wcnss = dev_get_drvdata(pdev->dev.parent);

	hw = ieee80211_alloc_hw(माप(काष्ठा wcn36xx), &wcn36xx_ops);
	अगर (!hw) अणु
		wcn36xx_err("failed to alloc hw\n");
		ret = -ENOMEM;
		जाओ out_err;
	पूर्ण
	platक्रमm_set_drvdata(pdev, hw);
	wcn = hw->priv;
	wcn->hw = hw;
	wcn->dev = &pdev->dev;
	wcn->first_boot = true;
	mutex_init(&wcn->conf_mutex);
	mutex_init(&wcn->hal_mutex);
	mutex_init(&wcn->scan_lock);

	ret = dma_set_mask_and_coherent(wcn->dev, DMA_BIT_MASK(32));
	अगर (ret < 0) अणु
		wcn36xx_err("failed to set DMA mask: %d\n", ret);
		जाओ out_wq;
	पूर्ण

	wcn->smd_channel = qcom_wcnss_खोलो_channel(wcnss, "WLAN_CTRL", wcn36xx_smd_rsp_process, hw);
	अगर (IS_ERR(wcn->smd_channel)) अणु
		wcn36xx_err("failed to open WLAN_CTRL channel\n");
		ret = PTR_ERR(wcn->smd_channel);
		जाओ out_wq;
	पूर्ण

	addr = of_get_property(pdev->dev.of_node, "local-mac-address", &ret);
	अगर (addr && ret != ETH_ALEN) अणु
		wcn36xx_err("invalid local-mac-address\n");
		ret = -EINVAL;
		जाओ out_destroy_ept;
	पूर्ण अन्यथा अगर (addr) अणु
		wcn36xx_info("mac address: %pM\n", addr);
		SET_IEEE80211_PERM_ADDR(wcn->hw, addr);
	पूर्ण

	ret = wcn36xx_platक्रमm_get_resources(wcn, pdev);
	अगर (ret)
		जाओ out_destroy_ept;

	wcn36xx_init_ieee80211(wcn);
	ret = ieee80211_रेजिस्टर_hw(wcn->hw);
	अगर (ret)
		जाओ out_unmap;

	वापस 0;

out_unmap:
	iounmap(wcn->ccu_base);
	iounmap(wcn->dxe_base);
out_destroy_ept:
	rpmsg_destroy_ept(wcn->smd_channel);
out_wq:
	ieee80211_मुक्त_hw(hw);
out_err:
	वापस ret;
पूर्ण

अटल पूर्णांक wcn36xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा ieee80211_hw *hw = platक्रमm_get_drvdata(pdev);
	काष्ठा wcn36xx *wcn = hw->priv;
	wcn36xx_dbg(WCN36XX_DBG_MAC, "platform remove\n");

	release_firmware(wcn->nv);

	ieee80211_unरेजिस्टर_hw(hw);

	qcom_smem_state_put(wcn->tx_enable_state);
	qcom_smem_state_put(wcn->tx_rings_empty_state);

	rpmsg_destroy_ept(wcn->smd_channel);

	iounmap(wcn->dxe_base);
	iounmap(wcn->ccu_base);

	mutex_destroy(&wcn->hal_mutex);
	ieee80211_मुक्त_hw(hw);

	वापस 0;
पूर्ण

अटल स्थिर काष्ठा of_device_id wcn36xx_of_match[] = अणु
	अणु .compatible = "qcom,wcnss-wlan" पूर्ण,
	अणुपूर्ण
पूर्ण;
MODULE_DEVICE_TABLE(of, wcn36xx_of_match);

अटल काष्ठा platक्रमm_driver wcn36xx_driver = अणु
	.probe      = wcn36xx_probe,
	.हटाओ     = wcn36xx_हटाओ,
	.driver         = अणु
		.name   = "wcn36xx",
		.of_match_table = wcn36xx_of_match,
	पूर्ण,
पूर्ण;

module_platक्रमm_driver(wcn36xx_driver);

MODULE_LICENSE("Dual BSD/GPL");
MODULE_AUTHOR("Eugene Krasnikov k.eugene.e@gmail.com");
MODULE_FIRMWARE(WLAN_NV_खाता);
