<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl18xx
 *
 * Copyright (C) 2011 Texas Instruments
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>
#समावेश <linux/ip.h>
#समावेश <linux/firmware.h>
#समावेश <linux/etherdevice.h>
#समावेश <linux/irq.h>

#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/io.h"
#समावेश "../wlcore/acx.h"
#समावेश "../wlcore/tx.h"
#समावेश "../wlcore/rx.h"
#समावेश "../wlcore/boot.h"

#समावेश "reg.h"
#समावेश "conf.h"
#समावेश "cmd.h"
#समावेश "acx.h"
#समावेश "tx.h"
#समावेश "wl18xx.h"
#समावेश "io.h"
#समावेश "scan.h"
#समावेश "event.h"
#समावेश "debugfs.h"

#घोषणा WL18XX_RX_CHECKSUM_MASK      0x40

अटल अक्षर *ht_mode_param = शून्य;
अटल अक्षर *board_type_param = शून्य;
अटल bool checksum_param = false;
अटल पूर्णांक num_rx_desc_param = -1;

/* phy paramters */
अटल पूर्णांक dc2dc_param = -1;
अटल पूर्णांक n_antennas_2_param = -1;
अटल पूर्णांक n_antennas_5_param = -1;
अटल पूर्णांक low_band_component_param = -1;
अटल पूर्णांक low_band_component_type_param = -1;
अटल पूर्णांक high_band_component_param = -1;
अटल पूर्णांक high_band_component_type_param = -1;
अटल पूर्णांक pwr_limit_reference_11_abg_param = -1;

अटल स्थिर u8 wl18xx_rate_to_idx_2ghz[] = अणु
	/* MCS rates are used only with 11n */
	15,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS15 */
	14,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS14 */
	13,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS13 */
	12,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS12 */
	11,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS11 */
	10,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS10 */
	9,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS9 */
	8,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS8 */
	7,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS7 */
	6,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS6 */
	5,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS5 */
	4,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS4 */
	3,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS3 */
	2,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS2 */
	1,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS1 */
	0,                             /* WL18XX_CONF_HW_RXTX_RATE_MCS0 */

	11,                            /* WL18XX_CONF_HW_RXTX_RATE_54   */
	10,                            /* WL18XX_CONF_HW_RXTX_RATE_48   */
	9,                             /* WL18XX_CONF_HW_RXTX_RATE_36   */
	8,                             /* WL18XX_CONF_HW_RXTX_RATE_24   */

	/* TI-specअगरic rate */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL18XX_CONF_HW_RXTX_RATE_22   */

	7,                             /* WL18XX_CONF_HW_RXTX_RATE_18   */
	6,                             /* WL18XX_CONF_HW_RXTX_RATE_12   */
	3,                             /* WL18XX_CONF_HW_RXTX_RATE_11   */
	5,                             /* WL18XX_CONF_HW_RXTX_RATE_9    */
	4,                             /* WL18XX_CONF_HW_RXTX_RATE_6    */
	2,                             /* WL18XX_CONF_HW_RXTX_RATE_5_5  */
	1,                             /* WL18XX_CONF_HW_RXTX_RATE_2    */
	0                              /* WL18XX_CONF_HW_RXTX_RATE_1    */
पूर्ण;

अटल स्थिर u8 wl18xx_rate_to_idx_5ghz[] = अणु
	/* MCS rates are used only with 11n */
	15,                           /* WL18XX_CONF_HW_RXTX_RATE_MCS15 */
	14,                           /* WL18XX_CONF_HW_RXTX_RATE_MCS14 */
	13,                           /* WL18XX_CONF_HW_RXTX_RATE_MCS13 */
	12,                           /* WL18XX_CONF_HW_RXTX_RATE_MCS12 */
	11,                           /* WL18XX_CONF_HW_RXTX_RATE_MCS11 */
	10,                           /* WL18XX_CONF_HW_RXTX_RATE_MCS10 */
	9,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS9 */
	8,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS8 */
	7,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS7 */
	6,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS6 */
	5,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS5 */
	4,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS4 */
	3,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS3 */
	2,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS2 */
	1,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS1 */
	0,                            /* WL18XX_CONF_HW_RXTX_RATE_MCS0 */

	7,                             /* WL18XX_CONF_HW_RXTX_RATE_54   */
	6,                             /* WL18XX_CONF_HW_RXTX_RATE_48   */
	5,                             /* WL18XX_CONF_HW_RXTX_RATE_36   */
	4,                             /* WL18XX_CONF_HW_RXTX_RATE_24   */

	/* TI-specअगरic rate */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL18XX_CONF_HW_RXTX_RATE_22   */

	3,                             /* WL18XX_CONF_HW_RXTX_RATE_18   */
	2,                             /* WL18XX_CONF_HW_RXTX_RATE_12   */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL18XX_CONF_HW_RXTX_RATE_11   */
	1,                             /* WL18XX_CONF_HW_RXTX_RATE_9    */
	0,                             /* WL18XX_CONF_HW_RXTX_RATE_6    */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL18XX_CONF_HW_RXTX_RATE_5_5  */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL18XX_CONF_HW_RXTX_RATE_2    */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL18XX_CONF_HW_RXTX_RATE_1    */
पूर्ण;

अटल स्थिर u8 *wl18xx_band_rate_to_idx[] = अणु
	[NL80211_BAND_2GHZ] = wl18xx_rate_to_idx_2ghz,
	[NL80211_BAND_5GHZ] = wl18xx_rate_to_idx_5ghz
पूर्ण;

क्रमागत wl18xx_hw_rates अणु
	WL18XX_CONF_HW_RXTX_RATE_MCS15 = 0,
	WL18XX_CONF_HW_RXTX_RATE_MCS14,
	WL18XX_CONF_HW_RXTX_RATE_MCS13,
	WL18XX_CONF_HW_RXTX_RATE_MCS12,
	WL18XX_CONF_HW_RXTX_RATE_MCS11,
	WL18XX_CONF_HW_RXTX_RATE_MCS10,
	WL18XX_CONF_HW_RXTX_RATE_MCS9,
	WL18XX_CONF_HW_RXTX_RATE_MCS8,
	WL18XX_CONF_HW_RXTX_RATE_MCS7,
	WL18XX_CONF_HW_RXTX_RATE_MCS6,
	WL18XX_CONF_HW_RXTX_RATE_MCS5,
	WL18XX_CONF_HW_RXTX_RATE_MCS4,
	WL18XX_CONF_HW_RXTX_RATE_MCS3,
	WL18XX_CONF_HW_RXTX_RATE_MCS2,
	WL18XX_CONF_HW_RXTX_RATE_MCS1,
	WL18XX_CONF_HW_RXTX_RATE_MCS0,
	WL18XX_CONF_HW_RXTX_RATE_54,
	WL18XX_CONF_HW_RXTX_RATE_48,
	WL18XX_CONF_HW_RXTX_RATE_36,
	WL18XX_CONF_HW_RXTX_RATE_24,
	WL18XX_CONF_HW_RXTX_RATE_22,
	WL18XX_CONF_HW_RXTX_RATE_18,
	WL18XX_CONF_HW_RXTX_RATE_12,
	WL18XX_CONF_HW_RXTX_RATE_11,
	WL18XX_CONF_HW_RXTX_RATE_9,
	WL18XX_CONF_HW_RXTX_RATE_6,
	WL18XX_CONF_HW_RXTX_RATE_5_5,
	WL18XX_CONF_HW_RXTX_RATE_2,
	WL18XX_CONF_HW_RXTX_RATE_1,
	WL18XX_CONF_HW_RXTX_RATE_MAX,
पूर्ण;

अटल काष्ठा wlcore_conf wl18xx_conf = अणु
	.sg = अणु
		.params = अणु
			[WL18XX_CONF_SG_PARAM_0] = 0,
			/* Configuration Parameters */
			[WL18XX_CONF_SG_ANTENNA_CONFIGURATION] = 0,
			[WL18XX_CONF_SG_ZIGBEE_COEX] = 0,
			[WL18XX_CONF_SG_TIME_SYNC] = 0,
			[WL18XX_CONF_SG_PARAM_4] = 0,
			[WL18XX_CONF_SG_PARAM_5] = 0,
			[WL18XX_CONF_SG_PARAM_6] = 0,
			[WL18XX_CONF_SG_PARAM_7] = 0,
			[WL18XX_CONF_SG_PARAM_8] = 0,
			[WL18XX_CONF_SG_PARAM_9] = 0,
			[WL18XX_CONF_SG_PARAM_10] = 0,
			[WL18XX_CONF_SG_PARAM_11] = 0,
			[WL18XX_CONF_SG_PARAM_12] = 0,
			[WL18XX_CONF_SG_PARAM_13] = 0,
			[WL18XX_CONF_SG_PARAM_14] = 0,
			[WL18XX_CONF_SG_PARAM_15] = 0,
			[WL18XX_CONF_SG_PARAM_16] = 0,
			[WL18XX_CONF_SG_PARAM_17] = 0,
			[WL18XX_CONF_SG_PARAM_18] = 0,
			[WL18XX_CONF_SG_PARAM_19] = 0,
			[WL18XX_CONF_SG_PARAM_20] = 0,
			[WL18XX_CONF_SG_PARAM_21] = 0,
			[WL18XX_CONF_SG_PARAM_22] = 0,
			[WL18XX_CONF_SG_PARAM_23] = 0,
			[WL18XX_CONF_SG_PARAM_24] = 0,
			[WL18XX_CONF_SG_PARAM_25] = 0,
			/* Active Scan Parameters */
			[WL18XX_CONF_SG_AUTO_SCAN_PROBE_REQ] = 170,
			[WL18XX_CONF_SG_ACTIVE_SCAN_DURATION_FACTOR_HV3] = 50,
			[WL18XX_CONF_SG_PARAM_28] = 0,
			/* Passive Scan Parameters */
			[WL18XX_CONF_SG_PARAM_29] = 0,
			[WL18XX_CONF_SG_PARAM_30] = 0,
			[WL18XX_CONF_SG_PASSIVE_SCAN_DURATION_FACTOR_HV3] = 200,
			/* Passive Scan in Dual Antenna Parameters */
			[WL18XX_CONF_SG_CONSECUTIVE_HV3_IN_PASSIVE_SCAN] = 0,
			[WL18XX_CONF_SG_BEACON_HV3_COLL_TH_IN_PASSIVE_SCAN] = 0,
			[WL18XX_CONF_SG_TX_RX_PROTECT_BW_IN_PASSIVE_SCAN] = 0,
			/* General Parameters */
			[WL18XX_CONF_SG_STA_FORCE_PS_IN_BT_SCO] = 1,
			[WL18XX_CONF_SG_PARAM_36] = 0,
			[WL18XX_CONF_SG_BEACON_MISS_PERCENT] = 60,
			[WL18XX_CONF_SG_PARAM_38] = 0,
			[WL18XX_CONF_SG_RXT] = 1200,
			[WL18XX_CONF_SG_UNUSED] = 0,
			[WL18XX_CONF_SG_ADAPTIVE_RXT_TXT] = 1,
			[WL18XX_CONF_SG_GENERAL_USAGE_BIT_MAP] = 3,
			[WL18XX_CONF_SG_HV3_MAX_SERVED] = 6,
			[WL18XX_CONF_SG_PARAM_44] = 0,
			[WL18XX_CONF_SG_PARAM_45] = 0,
			[WL18XX_CONF_SG_CONSECUTIVE_CTS_THRESHOLD] = 2,
			[WL18XX_CONF_SG_GEMINI_PARAM_47] = 0,
			[WL18XX_CONF_SG_STA_CONNECTION_PROTECTION_TIME] = 0,
			/* AP Parameters */
			[WL18XX_CONF_SG_AP_BEACON_MISS_TX] = 3,
			[WL18XX_CONF_SG_PARAM_50] = 0,
			[WL18XX_CONF_SG_AP_BEACON_WINDOW_INTERVAL] = 2,
			[WL18XX_CONF_SG_AP_CONNECTION_PROTECTION_TIME] = 30,
			[WL18XX_CONF_SG_PARAM_53] = 0,
			[WL18XX_CONF_SG_PARAM_54] = 0,
			/* CTS Diluting Parameters */
			[WL18XX_CONF_SG_CTS_DILUTED_BAD_RX_PACKETS_TH] = 0,
			[WL18XX_CONF_SG_CTS_CHOP_IN_DUAL_ANT_SCO_MASTER] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_1] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_2] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_3] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_4] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_5] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_6] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_7] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_8] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_9] = 0,
			[WL18XX_CONF_SG_TEMP_PARAM_10] = 0,
		पूर्ण,
		.state = CONF_SG_PROTECTIVE,
	पूर्ण,
	.rx = अणु
		.rx_msdu_lअगरe_समय           = 512000,
		.packet_detection_threshold  = 0,
		.ps_poll_समयout             = 15,
		.upsd_समयout                = 15,
		.rts_threshold               = IEEE80211_MAX_RTS_THRESHOLD,
		.rx_cca_threshold            = 0,
		.irq_blk_threshold           = 0xFFFF,
		.irq_pkt_threshold           = 0,
		.irq_समयout                 = 600,
		.queue_type                  = CONF_RX_QUEUE_TYPE_LOW_PRIORITY,
	पूर्ण,
	.tx = अणु
		.tx_energy_detection         = 0,
		.sta_rc_conf                 = अणु
			.enabled_rates       = 0,
			.लघु_retry_limit   = 10,
			.दीर्घ_retry_limit    = 10,
			.aflags              = 0,
		पूर्ण,
		.ac_conf_count               = 4,
		.ac_conf                     = अणु
			[CONF_TX_AC_BE] = अणु
				.ac          = CONF_TX_AC_BE,
				.cw_min      = 15,
				.cw_max      = 63,
				.aअगरsn       = 3,
				.tx_op_limit = 0,
			पूर्ण,
			[CONF_TX_AC_BK] = अणु
				.ac          = CONF_TX_AC_BK,
				.cw_min      = 15,
				.cw_max      = 63,
				.aअगरsn       = 7,
				.tx_op_limit = 0,
			पूर्ण,
			[CONF_TX_AC_VI] = अणु
				.ac          = CONF_TX_AC_VI,
				.cw_min      = 15,
				.cw_max      = 63,
				.aअगरsn       = CONF_TX_AIFS_PIFS,
				.tx_op_limit = 3008,
			पूर्ण,
			[CONF_TX_AC_VO] = अणु
				.ac          = CONF_TX_AC_VO,
				.cw_min      = 15,
				.cw_max      = 63,
				.aअगरsn       = CONF_TX_AIFS_PIFS,
				.tx_op_limit = 1504,
			पूर्ण,
		पूर्ण,
		.max_tx_retries = 100,
		.ap_aging_period = 300,
		.tid_conf_count = 4,
		.tid_conf = अणु
			[CONF_TX_AC_BE] = अणु
				.queue_id    = CONF_TX_AC_BE,
				.channel_type = CONF_CHANNEL_TYPE_EDCF,
				.tsid        = CONF_TX_AC_BE,
				.ps_scheme   = CONF_PS_SCHEME_LEGACY,
				.ack_policy  = CONF_ACK_POLICY_LEGACY,
				.apsd_conf   = अणु0, 0पूर्ण,
			पूर्ण,
			[CONF_TX_AC_BK] = अणु
				.queue_id    = CONF_TX_AC_BK,
				.channel_type = CONF_CHANNEL_TYPE_EDCF,
				.tsid        = CONF_TX_AC_BK,
				.ps_scheme   = CONF_PS_SCHEME_LEGACY,
				.ack_policy  = CONF_ACK_POLICY_LEGACY,
				.apsd_conf   = अणु0, 0पूर्ण,
			पूर्ण,
			[CONF_TX_AC_VI] = अणु
				.queue_id    = CONF_TX_AC_VI,
				.channel_type = CONF_CHANNEL_TYPE_EDCF,
				.tsid        = CONF_TX_AC_VI,
				.ps_scheme   = CONF_PS_SCHEME_LEGACY,
				.ack_policy  = CONF_ACK_POLICY_LEGACY,
				.apsd_conf   = अणु0, 0पूर्ण,
			पूर्ण,
			[CONF_TX_AC_VO] = अणु
				.queue_id    = CONF_TX_AC_VO,
				.channel_type = CONF_CHANNEL_TYPE_EDCF,
				.tsid        = CONF_TX_AC_VO,
				.ps_scheme   = CONF_PS_SCHEME_LEGACY,
				.ack_policy  = CONF_ACK_POLICY_LEGACY,
				.apsd_conf   = अणु0, 0पूर्ण,
			पूर्ण,
		पूर्ण,
		.frag_threshold              = IEEE80211_MAX_FRAG_THRESHOLD,
		.tx_compl_समयout            = 350,
		.tx_compl_threshold          = 10,
		.basic_rate                  = CONF_HW_BIT_RATE_1MBPS,
		.basic_rate_5                = CONF_HW_BIT_RATE_6MBPS,
		.पंचांगpl_लघु_retry_limit      = 10,
		.पंचांगpl_दीर्घ_retry_limit       = 10,
		.tx_watchकरोg_समयout         = 5000,
		.slow_link_thold             = 3,
		.fast_link_thold             = 30,
	पूर्ण,
	.conn = अणु
		.wake_up_event               = CONF_WAKE_UP_EVENT_DTIM,
		.listen_पूर्णांकerval             = 1,
		.suspend_wake_up_event       = CONF_WAKE_UP_EVENT_N_DTIM,
		.suspend_listen_पूर्णांकerval     = 3,
		.bcn_filt_mode               = CONF_BCN_FILT_MODE_ENABLED,
		.bcn_filt_ie_count           = 3,
		.bcn_filt_ie = अणु
			[0] = अणु
				.ie          = WLAN_EID_CHANNEL_SWITCH,
				.rule        = CONF_BCN_RULE_PASS_ON_APPEARANCE,
			पूर्ण,
			[1] = अणु
				.ie          = WLAN_EID_HT_OPERATION,
				.rule        = CONF_BCN_RULE_PASS_ON_CHANGE,
			पूर्ण,
			[2] = अणु
				.ie	     = WLAN_EID_ERP_INFO,
				.rule	     = CONF_BCN_RULE_PASS_ON_CHANGE,
			पूर्ण,
		पूर्ण,
		.synch_fail_thold            = 12,
		.bss_lose_समयout            = 400,
		.beacon_rx_समयout           = 10000,
		.broadcast_समयout           = 20000,
		.rx_broadcast_in_ps          = 1,
		.ps_poll_threshold           = 10,
		.bet_enable                  = CONF_BET_MODE_ENABLE,
		.bet_max_consecutive         = 50,
		.psm_entry_retries           = 8,
		.psm_निकास_retries            = 16,
		.psm_entry_nullfunc_retries  = 3,
		.dynamic_ps_समयout          = 1500,
		.क्रमced_ps                   = false,
		.keep_alive_पूर्णांकerval         = 55000,
		.max_listen_पूर्णांकerval         = 20,
		.sta_sleep_auth              = WL1271_PSM_ILLEGAL,
		.suspend_rx_ba_activity      = 0,
	पूर्ण,
	.itrim = अणु
		.enable = false,
		.समयout = 50000,
	पूर्ण,
	.pm_config = अणु
		.host_clk_settling_समय = 5000,
		.host_fast_wakeup_support = CONF_FAST_WAKEUP_DISABLE,
	पूर्ण,
	.roam_trigger = अणु
		.trigger_pacing               = 1,
		.avg_weight_rssi_beacon       = 20,
		.avg_weight_rssi_data         = 10,
		.avg_weight_snr_beacon        = 20,
		.avg_weight_snr_data          = 10,
	पूर्ण,
	.scan = अणु
		.min_dwell_समय_active        = 7500,
		.max_dwell_समय_active        = 30000,
		.min_dwell_समय_active_दीर्घ   = 25000,
		.max_dwell_समय_active_दीर्घ   = 50000,
		.dwell_समय_passive           = 100000,
		.dwell_समय_dfs               = 150000,
		.num_probe_reqs               = 2,
		.split_scan_समयout           = 50000,
	पूर्ण,
	.sched_scan = अणु
		/*
		 * Values are in TU/1000 but since sched scan FW command
		 * params are in TUs rounding up may occur.
		 */
		.base_dwell_समय		= 7500,
		.max_dwell_समय_delta		= 22500,
		/* based on 250bits per probe @1Mbps */
		.dwell_समय_delta_per_probe	= 2000,
		/* based on 250bits per probe @6Mbps (plus a bit more) */
		.dwell_समय_delta_per_probe_5	= 350,
		.dwell_समय_passive		= 100000,
		.dwell_समय_dfs			= 150000,
		.num_probe_reqs			= 2,
		.rssi_threshold			= -90,
		.snr_threshold			= 0,
		.num_लघु_पूर्णांकervals		= SCAN_MAX_SHORT_INTERVALS,
		.दीर्घ_पूर्णांकerval			= 30000,
	पूर्ण,
	.ht = अणु
		.rx_ba_win_size = 32,
		.tx_ba_win_size = 64,
		.inactivity_समयout = 10000,
		.tx_ba_tid_biपंचांगap = CONF_TX_BA_ENABLED_TID_BITMAP,
	पूर्ण,
	.mem = अणु
		.num_stations                 = 1,
		.ssid_profiles                = 1,
		.rx_block_num                 = 40,
		.tx_min_block_num             = 40,
		.dynamic_memory               = 1,
		.min_req_tx_blocks            = 45,
		.min_req_rx_blocks            = 22,
		.tx_min                       = 27,
	पूर्ण,
	.fm_coex = अणु
		.enable                       = true,
		.swallow_period               = 5,
		.n_भागider_fref_set_1         = 0xff,       /* शेष */
		.n_भागider_fref_set_2         = 12,
		.m_भागider_fref_set_1         = 0xffff,
		.m_भागider_fref_set_2         = 148,        /* शेष */
		.coex_pll_stabilization_समय  = 0xffffffff, /* शेष */
		.lकरो_stabilization_समय       = 0xffff,     /* शेष */
		.fm_disturbed_band_margin     = 0xff,       /* शेष */
		.swallow_clk_dअगरf             = 0xff,       /* शेष */
	पूर्ण,
	.rx_streaming = अणु
		.duration                      = 150,
		.queues                        = 0x1,
		.पूर्णांकerval                      = 20,
		.always                        = 0,
	पूर्ण,
	.fwlog = अणु
		.mode                         = WL12XX_FWLOG_CONTINUOUS,
		.mem_blocks                   = 0,
		.severity                     = 0,
		.बारtamp                    = WL12XX_FWLOG_TIMESTAMP_DISABLED,
		.output                       = WL12XX_FWLOG_OUTPUT_DBG_PINS,
		.threshold                    = 0,
	पूर्ण,
	.rate = अणु
		.rate_retry_score = 32000,
		.per_add = 8192,
		.per_th1 = 2048,
		.per_th2 = 4096,
		.max_per = 8100,
		.inverse_curiosity_factor = 5,
		.tx_fail_low_th = 4,
		.tx_fail_high_th = 10,
		.per_alpha_shअगरt = 4,
		.per_add_shअगरt = 13,
		.per_beta1_shअगरt = 10,
		.per_beta2_shअगरt = 8,
		.rate_check_up = 2,
		.rate_check_करोwn = 12,
		.rate_retry_policy = अणु
			0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00,
		पूर्ण,
	पूर्ण,
	.hangover = अणु
		.recover_समय               = 0,
		.hangover_period            = 20,
		.dynamic_mode               = 1,
		.early_termination_mode     = 1,
		.max_period                 = 20,
		.min_period                 = 1,
		.increase_delta             = 1,
		.decrease_delta             = 2,
		.quiet_समय                 = 4,
		.increase_समय              = 1,
		.winकरोw_size                = 16,
	पूर्ण,
	.recovery = अणु
		.bug_on_recovery	    = 0,
		.no_recovery		    = 0,
	पूर्ण,
पूर्ण;

अटल काष्ठा wl18xx_priv_conf wl18xx_शेष_priv_conf = अणु
	.ht = अणु
		.mode				= HT_MODE_WIDE,
	पूर्ण,
	.phy = अणु
		.phy_standalone			= 0x00,
		.primary_घड़ी_setting_समय	= 0x05,
		.घड़ी_valid_on_wake_up		= 0x00,
		.secondary_घड़ी_setting_समय	= 0x05,
		.board_type 			= BOARD_TYPE_HDK_18XX,
		.स्वतः_detect			= 0x00,
		.dedicated_fem			= FEM_NONE,
		.low_band_component		= COMPONENT_3_WAY_SWITCH,
		.low_band_component_type	= 0x05,
		.high_band_component		= COMPONENT_2_WAY_SWITCH,
		.high_band_component_type	= 0x09,
		.tcxo_lकरो_voltage		= 0x00,
		.xtal_itrim_val			= 0x04,
		.srf_state			= 0x00,
		.io_configuration		= 0x01,
		.sdio_configuration		= 0x00,
		.settings			= 0x00,
		.enable_clpc			= 0x00,
		.enable_tx_low_pwr_on_siso_rdl	= 0x00,
		.rx_profile			= 0x00,
		.pwr_limit_reference_11_abg	= 0x64,
		.per_chan_pwr_limit_arr_11abg	= अणु
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
			0xff, 0xff, 0xff, 0xff, 0xff, 0xff पूर्ण,
		.pwr_limit_reference_11p	= 0x64,
		.per_chan_bo_mode_11_abg	= अणु 0x00, 0x00, 0x00, 0x00,
						    0x00, 0x00, 0x00, 0x00,
						    0x00, 0x00, 0x00, 0x00,
						    0x00 पूर्ण,
		.per_chan_bo_mode_11_p		= अणु 0x00, 0x00, 0x00, 0x00 पूर्ण,
		.per_chan_pwr_limit_arr_11p	= अणु 0xff, 0xff, 0xff, 0xff,
						    0xff, 0xff, 0xff पूर्ण,
		.psat				= 0,
		.बाह्यal_pa_dc2dc		= 0,
		.number_of_assembled_ant2_4	= 2,
		.number_of_assembled_ant5	= 1,
		.low_घातer_val			= 0xff,
		.med_घातer_val			= 0xff,
		.high_घातer_val			= 0xff,
		.low_घातer_val_2nd		= 0xff,
		.med_घातer_val_2nd		= 0xff,
		.high_घातer_val_2nd		= 0xff,
		.tx_rf_margin			= 1,
	पूर्ण,
	.ap_sleep = अणु               /* disabled by शेष */
		.idle_duty_cycle        = 0,
		.connected_duty_cycle   = 0,
		.max_stations_thresh    = 0,
		.idle_conn_thresh       = 0,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wlcore_partition_set wl18xx_ptable[PART_TABLE_LEN] = अणु
	[PART_TOP_PRCM_ELP_SOC] = अणु
		.mem  = अणु .start = 0x00A00000, .size  = 0x00012000 पूर्ण,
		.reg  = अणु .start = 0x00807000, .size  = 0x00005000 पूर्ण,
		.mem2 = अणु .start = 0x00800000, .size  = 0x0000B000 पूर्ण,
		.mem3 = अणु .start = 0x00401594, .size  = 0x00001020 पूर्ण,
	पूर्ण,
	[PART_DOWN] = अणु
		.mem  = अणु .start = 0x00000000, .size  = 0x00014000 पूर्ण,
		.reg  = अणु .start = 0x00810000, .size  = 0x0000BFFF पूर्ण,
		.mem2 = अणु .start = 0x00000000, .size  = 0x00000000 पूर्ण,
		.mem3 = अणु .start = 0x00000000, .size  = 0x00000000 पूर्ण,
	पूर्ण,
	[PART_BOOT] = अणु
		.mem  = अणु .start = 0x00700000, .size = 0x0000030c पूर्ण,
		.reg  = अणु .start = 0x00802000, .size = 0x00014578 पूर्ण,
		.mem2 = अणु .start = 0x00B00404, .size = 0x00001000 पूर्ण,
		.mem3 = अणु .start = 0x00C00000, .size = 0x00000400 पूर्ण,
	पूर्ण,
	[PART_WORK] = अणु
		.mem  = अणु .start = 0x00800000, .size  = 0x000050FC पूर्ण,
		.reg  = अणु .start = 0x00B00404, .size  = 0x00001000 पूर्ण,
		.mem2 = अणु .start = 0x00C00000, .size  = 0x00000400 पूर्ण,
		.mem3 = अणु .start = 0x00401594, .size  = 0x00001020 पूर्ण,
	पूर्ण,
	[PART_PHY_INIT] = अणु
		.mem  = अणु .start = WL18XX_PHY_INIT_MEM_ADDR,
			  .size  = WL18XX_PHY_INIT_MEM_SIZE पूर्ण,
		.reg  = अणु .start = 0x00000000, .size = 0x00000000 पूर्ण,
		.mem2 = अणु .start = 0x00000000, .size = 0x00000000 पूर्ण,
		.mem3 = अणु .start = 0x00000000, .size = 0x00000000 पूर्ण,
	पूर्ण,
पूर्ण;

अटल स्थिर पूर्णांक wl18xx_rtable[REG_TABLE_LEN] = अणु
	[REG_ECPU_CONTROL]		= WL18XX_REG_ECPU_CONTROL,
	[REG_INTERRUPT_NO_CLEAR]	= WL18XX_REG_INTERRUPT_NO_CLEAR,
	[REG_INTERRUPT_ACK]		= WL18XX_REG_INTERRUPT_ACK,
	[REG_COMMAND_MAILBOX_PTR]	= WL18XX_REG_COMMAND_MAILBOX_PTR,
	[REG_EVENT_MAILBOX_PTR]		= WL18XX_REG_EVENT_MAILBOX_PTR,
	[REG_INTERRUPT_TRIG]		= WL18XX_REG_INTERRUPT_TRIG_H,
	[REG_INTERRUPT_MASK]		= WL18XX_REG_INTERRUPT_MASK,
	[REG_PC_ON_RECOVERY]		= WL18XX_SCR_PAD4,
	[REG_CHIP_ID_B]			= WL18XX_REG_CHIP_ID_B,
	[REG_CMD_MBOX_ADDRESS]		= WL18XX_CMD_MBOX_ADDRESS,

	/* data access memory addresses, used with partition translation */
	[REG_SLV_MEM_DATA]		= WL18XX_SLV_MEM_DATA,
	[REG_SLV_REG_DATA]		= WL18XX_SLV_REG_DATA,

	/* raw data access memory addresses */
	[REG_RAW_FW_STATUS_ADDR]	= WL18XX_FW_STATUS_ADDR,
पूर्ण;

अटल स्थिर काष्ठा wl18xx_clk_cfg wl18xx_clk_table_coex[NUM_CLOCK_CONFIGS] = अणु
	[CLOCK_CONFIG_16_2_M]	= अणु 8,  121, 0, 0, false पूर्ण,
	[CLOCK_CONFIG_16_368_M]	= अणु 8,  120, 0, 0, false पूर्ण,
	[CLOCK_CONFIG_16_8_M]	= अणु 8,  117, 0, 0, false पूर्ण,
	[CLOCK_CONFIG_19_2_M]	= अणु 10, 128, 0, 0, false पूर्ण,
	[CLOCK_CONFIG_26_M]	= अणु 11, 104, 0, 0, false पूर्ण,
	[CLOCK_CONFIG_32_736_M]	= अणु 8,  120, 0, 0, false पूर्ण,
	[CLOCK_CONFIG_33_6_M]	= अणु 8,  117, 0, 0, false पूर्ण,
	[CLOCK_CONFIG_38_468_M]	= अणु 10, 128, 0, 0, false पूर्ण,
	[CLOCK_CONFIG_52_M]	= अणु 11, 104, 0, 0, false पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wl18xx_clk_cfg wl18xx_clk_table[NUM_CLOCK_CONFIGS] = अणु
	[CLOCK_CONFIG_16_2_M]	= अणु 7,  104,  801, 4,  true पूर्ण,
	[CLOCK_CONFIG_16_368_M]	= अणु 9,  132, 3751, 4,  true पूर्ण,
	[CLOCK_CONFIG_16_8_M]	= अणु 7,  100,    0, 0, false पूर्ण,
	[CLOCK_CONFIG_19_2_M]	= अणु 8,  100,    0, 0, false पूर्ण,
	[CLOCK_CONFIG_26_M]	= अणु 13, 120,    0, 0, false पूर्ण,
	[CLOCK_CONFIG_32_736_M]	= अणु 9,  132, 3751, 4,  true पूर्ण,
	[CLOCK_CONFIG_33_6_M]	= अणु 7,  100,    0, 0, false पूर्ण,
	[CLOCK_CONFIG_38_468_M]	= अणु 8,  100,    0, 0, false पूर्ण,
	[CLOCK_CONFIG_52_M]	= अणु 13, 120,    0, 0, false पूर्ण,
पूर्ण;

/* TODO: maybe move to a new header file? */
#घोषणा WL18XX_FW_NAME "ti-connectivity/wl18xx-fw-4.bin"

अटल पूर्णांक wl18xx_identअगरy_chip(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret = 0;

	चयन (wl->chip.id) अणु
	हाल CHIP_ID_185x_PG20:
		wl1271_debug(DEBUG_BOOT, "chip id 0x%x (185x PG20)",
				 wl->chip.id);
		wl->sr_fw_name = WL18XX_FW_NAME;
		/* wl18xx uses the same firmware क्रम PLT */
		wl->plt_fw_name = WL18XX_FW_NAME;
		wl->quirks |= WLCORE_QUIRK_RX_BLOCKSIZE_ALIGN |
			      WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN |
			      WLCORE_QUIRK_NO_SCHED_SCAN_WHILE_CONN |
			      WLCORE_QUIRK_TX_PAD_LAST_FRAME |
			      WLCORE_QUIRK_REGDOMAIN_CONF |
			      WLCORE_QUIRK_DUAL_PROBE_TMPL;

		wlcore_set_min_fw_ver(wl, WL18XX_CHIP_VER,
				      WL18XX_IFTYPE_VER,  WL18XX_MAJOR_VER,
				      WL18XX_SUBTYPE_VER, WL18XX_MINOR_VER,
				      /* there's no separate multi-role FW */
				      0, 0, 0, 0);
		अवरोध;
	हाल CHIP_ID_185x_PG10:
		wl1271_warning("chip id 0x%x (185x PG10) is deprecated",
			       wl->chip.id);
		ret = -ENODEV;
		जाओ out;

	शेष:
		wl1271_warning("unsupported chip id: 0x%x", wl->chip.id);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	wl->fw_mem_block_size = 272;
	wl->fwlog_end = 0x40000000;

	wl->scan_templ_id_2_4 = CMD_TEMPL_CFG_PROBE_REQ_2_4;
	wl->scan_templ_id_5 = CMD_TEMPL_CFG_PROBE_REQ_5;
	wl->sched_scan_templ_id_2_4 = CMD_TEMPL_PROBE_REQ_2_4_PERIODIC;
	wl->sched_scan_templ_id_5 = CMD_TEMPL_PROBE_REQ_5_PERIODIC;
	wl->max_channels_5 = WL18XX_MAX_CHANNELS_5GHZ;
	wl->ba_rx_session_count_max = WL18XX_RX_BA_MAX_SESSIONS;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_set_clk(काष्ठा wl1271 *wl)
अणु
	u16 clk_freq;
	पूर्णांक ret;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_TOP_PRCM_ELP_SOC]);
	अगर (ret < 0)
		जाओ out;

	/* TODO: PG2: apparently we need to पढ़ो the clk type */

	ret = wl18xx_top_reg_पढ़ो(wl, PRIMARY_CLK_DETECT, &clk_freq);
	अगर (ret < 0)
		जाओ out;

	wl1271_debug(DEBUG_BOOT, "clock freq %d (%d, %d, %d, %d, %s)", clk_freq,
		     wl18xx_clk_table[clk_freq].n, wl18xx_clk_table[clk_freq].m,
		     wl18xx_clk_table[clk_freq].p, wl18xx_clk_table[clk_freq].q,
		     wl18xx_clk_table[clk_freq].swallow ? "swallow" : "spit");

	/* coex PLL configuration */
	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_COEX_PLL_N,
				   wl18xx_clk_table_coex[clk_freq].n);
	अगर (ret < 0)
		जाओ out;

	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_COEX_PLL_M,
				   wl18xx_clk_table_coex[clk_freq].m);
	अगर (ret < 0)
		जाओ out;

	/* bypass the swallowing logic */
	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_COEX_PLL_SWALLOW_EN,
				   PLLSH_COEX_PLL_SWALLOW_EN_VAL1);
	अगर (ret < 0)
		जाओ out;

	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WCS_PLL_N,
				   wl18xx_clk_table[clk_freq].n);
	अगर (ret < 0)
		जाओ out;

	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WCS_PLL_M,
				   wl18xx_clk_table[clk_freq].m);
	अगर (ret < 0)
		जाओ out;

	अगर (wl18xx_clk_table[clk_freq].swallow) अणु
		/* first the 16 lower bits */
		ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WCS_PLL_Q_FACTOR_CFG_1,
					   wl18xx_clk_table[clk_freq].q &
					   PLLSH_WCS_PLL_Q_FACTOR_CFG_1_MASK);
		अगर (ret < 0)
			जाओ out;

		/* then the 16 higher bits, masked out */
		ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WCS_PLL_Q_FACTOR_CFG_2,
					(wl18xx_clk_table[clk_freq].q >> 16) &
					PLLSH_WCS_PLL_Q_FACTOR_CFG_2_MASK);
		अगर (ret < 0)
			जाओ out;

		/* first the 16 lower bits */
		ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WCS_PLL_P_FACTOR_CFG_1,
					   wl18xx_clk_table[clk_freq].p &
					   PLLSH_WCS_PLL_P_FACTOR_CFG_1_MASK);
		अगर (ret < 0)
			जाओ out;

		/* then the 16 higher bits, masked out */
		ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WCS_PLL_P_FACTOR_CFG_2,
					(wl18xx_clk_table[clk_freq].p >> 16) &
					PLLSH_WCS_PLL_P_FACTOR_CFG_2_MASK);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WCS_PLL_SWALLOW_EN,
					   PLLSH_WCS_PLL_SWALLOW_EN_VAL2);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* choose WCS PLL */
	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WL_PLL_SEL,
				   PLLSH_WL_PLL_SEL_WCS_PLL);
	अगर (ret < 0)
		जाओ out;

	/* enable both PLLs */
	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WL_PLL_EN, PLLSH_WL_PLL_EN_VAL1);
	अगर (ret < 0)
		जाओ out;

	udelay(1000);

	/* disable coex PLL */
	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_WL_PLL_EN, PLLSH_WL_PLL_EN_VAL2);
	अगर (ret < 0)
		जाओ out;

	/* reset the swallowing logic */
	ret = wl18xx_top_reg_ग_लिखो(wl, PLLSH_COEX_PLL_SWALLOW_EN,
				   PLLSH_COEX_PLL_SWALLOW_EN_VAL2);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_boot_soft_reset(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	/* disable Rx/Tx */
	ret = wlcore_ग_लिखो32(wl, WL18XX_ENABLE, 0x0);
	अगर (ret < 0)
		जाओ out;

	/* disable स्वतः calibration on start*/
	ret = wlcore_ग_लिखो32(wl, WL18XX_SPARE_A2, 0xffff);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_pre_boot(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wl18xx_set_clk(wl);
	अगर (ret < 0)
		जाओ out;

	/* Continue the ELP wake up sequence */
	ret = wlcore_ग_लिखो32(wl, WL18XX_WELP_ARM_COMMAND, WELP_ARM_COMMAND_VAL);
	अगर (ret < 0)
		जाओ out;

	udelay(500);

	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);
	अगर (ret < 0)
		जाओ out;

	/* Disable पूर्णांकerrupts */
	ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_MASK, WL1271_ACX_INTR_ALL);
	अगर (ret < 0)
		जाओ out;

	ret = wl18xx_boot_soft_reset(wl);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_pre_upload(काष्ठा wl1271 *wl)
अणु
	u32 पंचांगp;
	पूर्णांक ret;
	u16 irq_invert;

	BUILD_BUG_ON(माप(काष्ठा wl18xx_mac_and_phy_params) >
		WL18XX_PHY_INIT_MEM_SIZE);

	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);
	अगर (ret < 0)
		जाओ out;

	/* TODO: check अगर this is all needed */
	ret = wlcore_ग_लिखो32(wl, WL18XX_EEPROMLESS_IND, WL18XX_EEPROMLESS_IND);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_पढ़ो_reg(wl, REG_CHIP_ID_B, &पंचांगp);
	अगर (ret < 0)
		जाओ out;

	wl1271_debug(DEBUG_BOOT, "chip id 0x%x", पंचांगp);

	ret = wlcore_पढ़ो32(wl, WL18XX_SCR_PAD2, &पंचांगp);
	अगर (ret < 0)
		जाओ out;

	/*
	 * Workaround क्रम FDSP code RAM corruption (needed क्रम PG2.1
	 * and newer; क्रम older chips it's a NOP).  Change FDSP घड़ी
	 * settings so that it's muxed to the ATGP घड़ी instead of
	 * its own घड़ी.
	 */

	ret = wlcore_set_partition(wl, &wl->ptable[PART_PHY_INIT]);
	अगर (ret < 0)
		जाओ out;

	/* disable FDSP घड़ी */
	ret = wlcore_ग_लिखो32(wl, WL18XX_PHY_FPGA_SPARE_1,
			     MEM_FDSP_CLK_120_DISABLE);
	अगर (ret < 0)
		जाओ out;

	/* set ATPG घड़ी toward FDSP Code RAM rather than its own घड़ी */
	ret = wlcore_ग_लिखो32(wl, WL18XX_PHY_FPGA_SPARE_1,
			     MEM_FDSP_CODERAM_FUNC_CLK_SEL);
	अगर (ret < 0)
		जाओ out;

	/* re-enable FDSP घड़ी */
	ret = wlcore_ग_लिखो32(wl, WL18XX_PHY_FPGA_SPARE_1,
			     MEM_FDSP_CLK_120_ENABLE);
	अगर (ret < 0)
		जाओ out;

	ret = irq_get_trigger_type(wl->irq);
	अगर ((ret == IRQ_TYPE_LEVEL_LOW) || (ret == IRQ_TYPE_EDGE_FALLING)) अणु
		wl1271_info("using inverted interrupt logic: %d", ret);
		ret = wlcore_set_partition(wl,
					   &wl->ptable[PART_TOP_PRCM_ELP_SOC]);
		अगर (ret < 0)
			जाओ out;

		ret = wl18xx_top_reg_पढ़ो(wl, TOP_FN0_CCCR_REG_32, &irq_invert);
		अगर (ret < 0)
			जाओ out;

		irq_invert |= BIT(1);
		ret = wl18xx_top_reg_ग_लिखो(wl, TOP_FN0_CCCR_REG_32, irq_invert);
		अगर (ret < 0)
			जाओ out;

		ret = wlcore_set_partition(wl, &wl->ptable[PART_PHY_INIT]);
	पूर्ण

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_set_mac_and_phy(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl18xx_priv *priv = wl->priv;
	काष्ठा wl18xx_mac_and_phy_params *params;
	पूर्णांक ret;

	params = kmemdup(&priv->conf.phy, माप(*params), GFP_KERNEL);
	अगर (!params) अणु
		ret = -ENOMEM;
		जाओ out;
	पूर्ण

	ret = wlcore_set_partition(wl, &wl->ptable[PART_PHY_INIT]);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_ग_लिखो(wl, WL18XX_PHY_INIT_MEM_ADDR, params,
			   माप(*params), false);

out:
	kमुक्त(params);
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_enable_पूर्णांकerrupts(काष्ठा wl1271 *wl)
अणु
	u32 event_mask, पूर्णांकr_mask;
	पूर्णांक ret;

	event_mask = WL18XX_ACX_EVENTS_VECTOR;
	पूर्णांकr_mask = WL18XX_INTR_MASK;

	ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_MASK, event_mask);
	अगर (ret < 0)
		जाओ out;

	wlcore_enable_पूर्णांकerrupts(wl);

	ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_MASK,
			       WL1271_ACX_INTR_ALL & ~पूर्णांकr_mask);
	अगर (ret < 0)
		जाओ disable_पूर्णांकerrupts;

	वापस ret;

disable_पूर्णांकerrupts:
	wlcore_disable_पूर्णांकerrupts(wl);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_boot(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wl18xx_pre_boot(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl18xx_pre_upload(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_boot_upload_firmware(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl18xx_set_mac_and_phy(wl);
	अगर (ret < 0)
		जाओ out;

	wl->event_mask = BSS_LOSS_EVENT_ID |
		SCAN_COMPLETE_EVENT_ID |
		RADAR_DETECTED_EVENT_ID |
		RSSI_SNR_TRIGGER_0_EVENT_ID |
		PERIODIC_SCAN_COMPLETE_EVENT_ID |
		PERIODIC_SCAN_REPORT_EVENT_ID |
		DUMMY_PACKET_EVENT_ID |
		PEER_REMOVE_COMPLETE_EVENT_ID |
		BA_SESSION_RX_CONSTRAINT_EVENT_ID |
		REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID |
		INACTIVE_STA_EVENT_ID |
		CHANNEL_SWITCH_COMPLETE_EVENT_ID |
		DFS_CHANNELS_CONFIG_COMPLETE_EVENT |
		SMART_CONFIG_SYNC_EVENT_ID |
		SMART_CONFIG_DECODE_EVENT_ID |
		TIME_SYNC_EVENT_ID |
		FW_LOGGER_INDICATION |
		RX_BA_WIN_SIZE_CHANGE_EVENT_ID;

	wl->ap_event_mask = MAX_TX_FAILURE_EVENT_ID;

	ret = wlcore_boot_run_firmware(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl18xx_enable_पूर्णांकerrupts(wl);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_trigger_cmd(काष्ठा wl1271 *wl, पूर्णांक cmd_box_addr,
			       व्योम *buf, माप_प्रकार len)
अणु
	काष्ठा wl18xx_priv *priv = wl->priv;

	स_नकल(priv->cmd_buf, buf, len);
	स_रखो(priv->cmd_buf + len, 0, WL18XX_CMD_MAX_SIZE - len);

	वापस wlcore_ग_लिखो(wl, cmd_box_addr, priv->cmd_buf,
			    WL18XX_CMD_MAX_SIZE, false);
पूर्ण

अटल पूर्णांक wl18xx_ack_event(काष्ठा wl1271 *wl)
अणु
	वापस wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_TRIG,
				WL18XX_INTR_TRIG_EVENT_ACK);
पूर्ण

अटल u32 wl18xx_calc_tx_blocks(काष्ठा wl1271 *wl, u32 len, u32 spare_blks)
अणु
	u32 blk_size = WL18XX_TX_HW_BLOCK_SIZE;
	वापस (len + blk_size - 1) / blk_size + spare_blks;
पूर्ण

अटल व्योम
wl18xx_set_tx_desc_blocks(काष्ठा wl1271 *wl, काष्ठा wl1271_tx_hw_descr *desc,
			  u32 blks, u32 spare_blks)
अणु
	desc->wl18xx_mem.total_mem_blocks = blks;
पूर्ण

अटल व्योम
wl18xx_set_tx_desc_data_len(काष्ठा wl1271 *wl, काष्ठा wl1271_tx_hw_descr *desc,
			    काष्ठा sk_buff *skb)
अणु
	desc->length = cpu_to_le16(skb->len);

	/* अगर only the last frame is to be padded, we unset this bit on Tx */
	अगर (wl->quirks & WLCORE_QUIRK_TX_PAD_LAST_FRAME)
		desc->wl18xx_mem.ctrl = WL18XX_TX_CTRL_NOT_PADDED;
	अन्यथा
		desc->wl18xx_mem.ctrl = 0;

	wl1271_debug(DEBUG_TX, "tx_fill_hdr: hlid: %d "
		     "len: %d life: %d mem: %d", desc->hlid,
		     le16_to_cpu(desc->length),
		     le16_to_cpu(desc->lअगरe_समय),
		     desc->wl18xx_mem.total_mem_blocks);
पूर्ण

अटल क्रमागत wl_rx_buf_align
wl18xx_get_rx_buf_align(काष्ठा wl1271 *wl, u32 rx_desc)
अणु
	अगर (rx_desc & RX_BUF_PADDED_PAYLOAD)
		वापस WLCORE_RX_BUF_PADDED;

	वापस WLCORE_RX_BUF_ALIGNED;
पूर्ण

अटल u32 wl18xx_get_rx_packet_len(काष्ठा wl1271 *wl, व्योम *rx_data,
				    u32 data_len)
अणु
	काष्ठा wl1271_rx_descriptor *desc = rx_data;

	/* invalid packet */
	अगर (data_len < माप(*desc))
		वापस 0;

	वापस data_len - माप(*desc);
पूर्ण

अटल व्योम wl18xx_tx_immediate_completion(काष्ठा wl1271 *wl)
अणु
	wl18xx_tx_immediate_complete(wl);
पूर्ण

अटल पूर्णांक wl18xx_set_host_cfg_biपंचांगap(काष्ठा wl1271 *wl, u32 extra_mem_blk)
अणु
	पूर्णांक ret;
	u32 sdio_align_size = 0;
	u32 host_cfg_biपंचांगap = HOST_IF_CFG_RX_FIFO_ENABLE |
			      HOST_IF_CFG_ADD_RX_ALIGNMENT;

	/* Enable Tx SDIO padding */
	अगर (wl->quirks & WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN) अणु
		host_cfg_biपंचांगap |= HOST_IF_CFG_TX_PAD_TO_SDIO_BLK;
		sdio_align_size = WL12XX_BUS_BLOCK_SIZE;
	पूर्ण

	/* Enable Rx SDIO padding */
	अगर (wl->quirks & WLCORE_QUIRK_RX_BLOCKSIZE_ALIGN) अणु
		host_cfg_biपंचांगap |= HOST_IF_CFG_RX_PAD_TO_SDIO_BLK;
		sdio_align_size = WL12XX_BUS_BLOCK_SIZE;
	पूर्ण

	ret = wl18xx_acx_host_अगर_cfg_biपंचांगap(wl, host_cfg_biपंचांगap,
					    sdio_align_size, extra_mem_blk,
					    WL18XX_HOST_IF_LEN_SIZE_FIELD);
	अगर (ret < 0)
		वापस ret;

	वापस 0;
पूर्ण

अटल पूर्णांक wl18xx_hw_init(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;
	काष्ठा wl18xx_priv *priv = wl->priv;

	/* (re)init निजी काष्ठाures. Relevant on recovery as well. */
	priv->last_fw_rls_idx = 0;
	priv->extra_spare_key_count = 0;

	/* set the शेष amount of spare blocks in the biपंचांगap */
	ret = wl18xx_set_host_cfg_biपंचांगap(wl, WL18XX_TX_HW_BLOCK_SPARE);
	अगर (ret < 0)
		वापस ret;

	/* set the dynamic fw traces biपंचांगap */
	ret = wl18xx_acx_dynamic_fw_traces(wl);
	अगर (ret < 0)
		वापस ret;

	अगर (checksum_param) अणु
		ret = wl18xx_acx_set_checksum_state(wl);
		अगर (ret != 0)
			वापस ret;
	पूर्ण

	वापस ret;
पूर्ण

अटल व्योम wl18xx_convert_fw_status(काष्ठा wl1271 *wl, व्योम *raw_fw_status,
				     काष्ठा wl_fw_status *fw_status)
अणु
	काष्ठा wl18xx_fw_status *पूर्णांक_fw_status = raw_fw_status;

	fw_status->पूर्णांकr = le32_to_cpu(पूर्णांक_fw_status->पूर्णांकr);
	fw_status->fw_rx_counter = पूर्णांक_fw_status->fw_rx_counter;
	fw_status->drv_rx_counter = पूर्णांक_fw_status->drv_rx_counter;
	fw_status->tx_results_counter = पूर्णांक_fw_status->tx_results_counter;
	fw_status->rx_pkt_descs = पूर्णांक_fw_status->rx_pkt_descs;

	fw_status->fw_स_स्थानीय = le32_to_cpu(पूर्णांक_fw_status->fw_स_स्थानीय);
	fw_status->link_ps_biपंचांगap = le32_to_cpu(पूर्णांक_fw_status->link_ps_biपंचांगap);
	fw_status->link_fast_biपंचांगap =
			le32_to_cpu(पूर्णांक_fw_status->link_fast_biपंचांगap);
	fw_status->total_released_blks =
			le32_to_cpu(पूर्णांक_fw_status->total_released_blks);
	fw_status->tx_total = le32_to_cpu(पूर्णांक_fw_status->tx_total);

	fw_status->counters.tx_released_pkts =
			पूर्णांक_fw_status->counters.tx_released_pkts;
	fw_status->counters.tx_lnk_मुक्त_pkts =
			पूर्णांक_fw_status->counters.tx_lnk_मुक्त_pkts;
	fw_status->counters.tx_voice_released_blks =
			पूर्णांक_fw_status->counters.tx_voice_released_blks;
	fw_status->counters.tx_last_rate =
			पूर्णांक_fw_status->counters.tx_last_rate;
	fw_status->counters.tx_last_rate_mbps =
			पूर्णांक_fw_status->counters.tx_last_rate_mbps;
	fw_status->counters.hlid =
			पूर्णांक_fw_status->counters.hlid;

	fw_status->log_start_addr = le32_to_cpu(पूर्णांक_fw_status->log_start_addr);

	fw_status->priv = &पूर्णांक_fw_status->priv;
पूर्ण

अटल व्योम wl18xx_set_tx_desc_csum(काष्ठा wl1271 *wl,
				    काष्ठा wl1271_tx_hw_descr *desc,
				    काष्ठा sk_buff *skb)
अणु
	u32 ip_hdr_offset;
	काष्ठा iphdr *ip_hdr;

	अगर (!checksum_param) अणु
		desc->wl18xx_checksum_data = 0;
		वापस;
	पूर्ण

	अगर (skb->ip_summed != CHECKSUM_PARTIAL) अणु
		desc->wl18xx_checksum_data = 0;
		वापस;
	पूर्ण

	ip_hdr_offset = skb_network_header(skb) - skb_mac_header(skb);
	अगर (WARN_ON(ip_hdr_offset >= (1<<7))) अणु
		desc->wl18xx_checksum_data = 0;
		वापस;
	पूर्ण

	desc->wl18xx_checksum_data = ip_hdr_offset << 1;

	/* FW is पूर्णांकerested only in the LSB of the protocol  TCP=0 UDP=1 */
	ip_hdr = (व्योम *)skb_network_header(skb);
	desc->wl18xx_checksum_data |= (ip_hdr->protocol & 0x01);
पूर्ण

अटल व्योम wl18xx_set_rx_csum(काष्ठा wl1271 *wl,
			       काष्ठा wl1271_rx_descriptor *desc,
			       काष्ठा sk_buff *skb)
अणु
	अगर (desc->status & WL18XX_RX_CHECKSUM_MASK)
		skb->ip_summed = CHECKSUM_UNNECESSARY;
पूर्ण

अटल bool wl18xx_is_mimo_supported(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl18xx_priv *priv = wl->priv;

	/* only support MIMO with multiple antennas, and when SISO
	 * is not क्रमced through config
	 */
	वापस (priv->conf.phy.number_of_assembled_ant2_4 >= 2) &&
	       (priv->conf.ht.mode != HT_MODE_WIDE) &&
	       (priv->conf.ht.mode != HT_MODE_SISO20);
पूर्ण

/*
 * TODO: instead of having these two functions to get the rate mask,
 * we should modअगरy the wlvअगर->rate_set instead
 */
अटल u32 wl18xx_sta_get_ap_rate_mask(काष्ठा wl1271 *wl,
				       काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	u32 hw_rate_set = wlvअगर->rate_set;

	अगर (wlvअगर->channel_type == NL80211_CHAN_HT40MINUS ||
	    wlvअगर->channel_type == NL80211_CHAN_HT40PLUS) अणु
		wl1271_debug(DEBUG_ACX, "using wide channel rate mask");
		hw_rate_set |= CONF_TX_RATE_USE_WIDE_CHAN;

		/* we करोn't support MIMO in wide-channel mode */
		hw_rate_set &= ~CONF_TX_MIMO_RATES;
	पूर्ण अन्यथा अगर (wl18xx_is_mimo_supported(wl)) अणु
		wl1271_debug(DEBUG_ACX, "using MIMO channel rate mask");
		hw_rate_set |= CONF_TX_MIMO_RATES;
	पूर्ण

	वापस hw_rate_set;
पूर्ण

अटल u32 wl18xx_ap_get_mimo_wide_rate_mask(काष्ठा wl1271 *wl,
					     काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	अगर (wlvअगर->channel_type == NL80211_CHAN_HT40MINUS ||
	    wlvअगर->channel_type == NL80211_CHAN_HT40PLUS) अणु
		wl1271_debug(DEBUG_ACX, "using wide channel rate mask");

		/* sanity check - we करोn't support this */
		अगर (WARN_ON(wlvअगर->band != NL80211_BAND_5GHZ))
			वापस 0;

		वापस CONF_TX_RATE_USE_WIDE_CHAN;
	पूर्ण अन्यथा अगर (wl18xx_is_mimo_supported(wl) &&
		   wlvअगर->band == NL80211_BAND_2GHZ) अणु
		wl1271_debug(DEBUG_ACX, "using MIMO rate mask");
		/*
		 * we करोn't care about HT channel here - if a peer doesn't
		 * support MIMO, we won't enable it in its rates
		 */
		वापस CONF_TX_MIMO_RATES;
	पूर्ण अन्यथा अणु
		वापस 0;
	पूर्ण
पूर्ण

अटल स्थिर अक्षर *wl18xx_rdl_name(क्रमागत wl18xx_rdl_num rdl_num)
अणु
	चयन (rdl_num) अणु
	हाल RDL_1_HP:
		वापस "183xH";
	हाल RDL_2_SP:
		वापस "183x or 180x";
	हाल RDL_3_HP:
		वापस "187xH";
	हाल RDL_4_SP:
		वापस "187x";
	हाल RDL_5_SP:
		वापस "RDL11 - Not Supported";
	हाल RDL_6_SP:
		वापस "180xD";
	हाल RDL_7_SP:
		वापस "RDL13 - Not Supported (1893Q)";
	हाल RDL_8_SP:
		वापस "18xxQ";
	हाल RDL_NONE:
		वापस "UNTRIMMED";
	शेष:
		वापस "UNKNOWN";
	पूर्ण
पूर्ण

अटल पूर्णांक wl18xx_get_pg_ver(काष्ठा wl1271 *wl, s8 *ver)
अणु
	u32 fuse;
	s8 rom = 0, metal = 0, pg_ver = 0, rdl_ver = 0, package_type = 0;
	पूर्णांक ret;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_TOP_PRCM_ELP_SOC]);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_पढ़ो32(wl, WL18XX_REG_FUSE_DATA_2_3, &fuse);
	अगर (ret < 0)
		जाओ out;

	package_type = (fuse >> WL18XX_PACKAGE_TYPE_OFFSET) & 1;

	ret = wlcore_पढ़ो32(wl, WL18XX_REG_FUSE_DATA_1_3, &fuse);
	अगर (ret < 0)
		जाओ out;

	pg_ver = (fuse & WL18XX_PG_VER_MASK) >> WL18XX_PG_VER_OFFSET;
	rom = (fuse & WL18XX_ROM_VER_MASK) >> WL18XX_ROM_VER_OFFSET;

	अगर ((rom <= 0xE) && (package_type == WL18XX_PACKAGE_TYPE_WSP))
		metal = (fuse & WL18XX_METAL_VER_MASK) >>
			WL18XX_METAL_VER_OFFSET;
	अन्यथा
		metal = (fuse & WL18XX_NEW_METAL_VER_MASK) >>
			WL18XX_NEW_METAL_VER_OFFSET;

	ret = wlcore_पढ़ो32(wl, WL18XX_REG_FUSE_DATA_2_3, &fuse);
	अगर (ret < 0)
		जाओ out;

	rdl_ver = (fuse & WL18XX_RDL_VER_MASK) >> WL18XX_RDL_VER_OFFSET;

	wl1271_info("wl18xx HW: %s, PG %d.%d (ROM 0x%x)",
		    wl18xx_rdl_name(rdl_ver), pg_ver, metal, rom);

	अगर (ver)
		*ver = pg_ver;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_BOOT]);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_load_conf_file(काष्ठा device *dev, काष्ठा wlcore_conf *conf,
				 काष्ठा wl18xx_priv_conf *priv_conf,
				 स्थिर अक्षर *file)
अणु
	काष्ठा wlcore_conf_file *conf_file;
	स्थिर काष्ठा firmware *fw;
	पूर्णांक ret;

	ret = request_firmware(&fw, file, dev);
	अगर (ret < 0) अणु
		wl1271_error("could not get configuration binary %s: %d",
			     file, ret);
		वापस ret;
	पूर्ण

	अगर (fw->size != WL18XX_CONF_SIZE) अणु
		wl1271_error("%s configuration binary size is wrong, expected %zu got %zu",
			     file, WL18XX_CONF_SIZE, fw->size);
		ret = -EINVAL;
		जाओ out_release;
	पूर्ण

	conf_file = (काष्ठा wlcore_conf_file *) fw->data;

	अगर (conf_file->header.magic != cpu_to_le32(WL18XX_CONF_MAGIC)) अणु
		wl1271_error("configuration binary file magic number mismatch, "
			     "expected 0x%0x got 0x%0x", WL18XX_CONF_MAGIC,
			     conf_file->header.magic);
		ret = -EINVAL;
		जाओ out_release;
	पूर्ण

	अगर (conf_file->header.version != cpu_to_le32(WL18XX_CONF_VERSION)) अणु
		wl1271_error("configuration binary file version not supported, "
			     "expected 0x%08x got 0x%08x",
			     WL18XX_CONF_VERSION, conf_file->header.version);
		ret = -EINVAL;
		जाओ out_release;
	पूर्ण

	स_नकल(conf, &conf_file->core, माप(*conf));
	स_नकल(priv_conf, &conf_file->priv, माप(*priv_conf));

out_release:
	release_firmware(fw);
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_conf_init(काष्ठा wl1271 *wl, काष्ठा device *dev)
अणु
	काष्ठा platक्रमm_device *pdev = wl->pdev;
	काष्ठा wlcore_platdev_data *pdata = dev_get_platdata(&pdev->dev);
	काष्ठा wl18xx_priv *priv = wl->priv;

	अगर (wl18xx_load_conf_file(dev, &wl->conf, &priv->conf,
				  pdata->family->cfg_name) < 0) अणु
		wl1271_warning("falling back to default config");

		/* apply driver शेष configuration */
		स_नकल(&wl->conf, &wl18xx_conf, माप(wl->conf));
		/* apply शेष निजी configuration */
		स_नकल(&priv->conf, &wl18xx_शेष_priv_conf,
		       माप(priv->conf));
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl18xx_plt_init(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	/* calibrator based स्वतः/fem detect not supported क्रम 18xx */
	अगर (wl->plt_mode == PLT_FEM_DETECT) अणु
		wl1271_error("wl18xx_plt_init: PLT FEM_DETECT not supported");
		वापस -EINVAL;
	पूर्ण

	ret = wlcore_ग_लिखो32(wl, WL18XX_SCR_PAD8, WL18XX_SCR_PAD8_PLT);
	अगर (ret < 0)
		वापस ret;

	वापस wl->ops->boot(wl);
पूर्ण

अटल पूर्णांक wl18xx_get_mac(काष्ठा wl1271 *wl)
अणु
	u32 mac1, mac2;
	पूर्णांक ret;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_TOP_PRCM_ELP_SOC]);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_पढ़ो32(wl, WL18XX_REG_FUSE_BD_ADDR_1, &mac1);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_पढ़ो32(wl, WL18XX_REG_FUSE_BD_ADDR_2, &mac2);
	अगर (ret < 0)
		जाओ out;

	/* these are the two parts of the BD_ADDR */
	wl->fuse_oui_addr = ((mac2 & 0xffff) << 8) +
		((mac1 & 0xff000000) >> 24);
	wl->fuse_nic_addr = (mac1 & 0xffffff);

	अगर (!wl->fuse_oui_addr && !wl->fuse_nic_addr) अणु
		u8 mac[ETH_ALEN];

		eth_अक्रमom_addr(mac);

		wl->fuse_oui_addr = (mac[0] << 16) + (mac[1] << 8) + mac[2];
		wl->fuse_nic_addr = (mac[3] << 16) + (mac[4] << 8) + mac[5];
		wl1271_warning("MAC address from fuse not available, using random locally administered addresses.");
	पूर्ण

	ret = wlcore_set_partition(wl, &wl->ptable[PART_DOWN]);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl18xx_handle_अटल_data(काष्ठा wl1271 *wl,
				     काष्ठा wl1271_अटल_data *अटल_data)
अणु
	काष्ठा wl18xx_अटल_data_priv *अटल_data_priv =
		(काष्ठा wl18xx_अटल_data_priv *) अटल_data->priv;

	म_नकलन(wl->chip.phy_fw_ver_str, अटल_data_priv->phy_version,
		माप(wl->chip.phy_fw_ver_str));

	/* make sure the string is शून्य-terminated */
	wl->chip.phy_fw_ver_str[माप(wl->chip.phy_fw_ver_str) - 1] = '\0';

	wl1271_info("PHY firmware version: %s", अटल_data_priv->phy_version);

	वापस 0;
पूर्ण

अटल पूर्णांक wl18xx_get_spare_blocks(काष्ठा wl1271 *wl, bool is_gem)
अणु
	काष्ठा wl18xx_priv *priv = wl->priv;

	/* If we have keys requiring extra spare, indulge them */
	अगर (priv->extra_spare_key_count)
		वापस WL18XX_TX_HW_EXTRA_BLOCK_SPARE;

	वापस WL18XX_TX_HW_BLOCK_SPARE;
पूर्ण

अटल पूर्णांक wl18xx_set_key(काष्ठा wl1271 *wl, क्रमागत set_key_cmd cmd,
			  काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key_conf)
अणु
	काष्ठा wl18xx_priv *priv = wl->priv;
	bool change_spare = false, special_enc;
	पूर्णांक ret;

	wl1271_debug(DEBUG_CRYPT, "extra spare keys before: %d",
		     priv->extra_spare_key_count);

	special_enc = key_conf->cipher == WL1271_CIPHER_SUITE_GEM ||
		      key_conf->cipher == WLAN_CIPHER_SUITE_TKIP;

	ret = wlcore_set_key(wl, cmd, vअगर, sta, key_conf);
	अगर (ret < 0)
		जाओ out;

	/*
	 * when adding the first or removing the last GEM/TKIP key,
	 * we have to adjust the number of spare blocks.
	 */
	अगर (special_enc) अणु
		अगर (cmd == SET_KEY) अणु
			/* first key */
			change_spare = (priv->extra_spare_key_count == 0);
			priv->extra_spare_key_count++;
		पूर्ण अन्यथा अगर (cmd == DISABLE_KEY) अणु
			/* last key */
			change_spare = (priv->extra_spare_key_count == 1);
			priv->extra_spare_key_count--;
		पूर्ण
	पूर्ण

	wl1271_debug(DEBUG_CRYPT, "extra spare keys after: %d",
		     priv->extra_spare_key_count);

	अगर (!change_spare)
		जाओ out;

	/* key is now set, change the spare blocks */
	अगर (priv->extra_spare_key_count)
		ret = wl18xx_set_host_cfg_biपंचांगap(wl,
					WL18XX_TX_HW_EXTRA_BLOCK_SPARE);
	अन्यथा
		ret = wl18xx_set_host_cfg_biपंचांगap(wl,
					WL18XX_TX_HW_BLOCK_SPARE);

out:
	वापस ret;
पूर्ण

अटल u32 wl18xx_pre_pkt_send(काष्ठा wl1271 *wl,
			       u32 buf_offset, u32 last_len)
अणु
	अगर (wl->quirks & WLCORE_QUIRK_TX_PAD_LAST_FRAME) अणु
		काष्ठा wl1271_tx_hw_descr *last_desc;

		/* get the last TX HW descriptor written to the aggr buf */
		last_desc = (काष्ठा wl1271_tx_hw_descr *)(wl->aggr_buf +
							buf_offset - last_len);

		/* the last frame is padded up to an SDIO block */
		last_desc->wl18xx_mem.ctrl &= ~WL18XX_TX_CTRL_NOT_PADDED;
		वापस ALIGN(buf_offset, WL12XX_BUS_BLOCK_SIZE);
	पूर्ण

	/* no modअगरications */
	वापस buf_offset;
पूर्ण

अटल व्योम wl18xx_sta_rc_update(काष्ठा wl1271 *wl,
				 काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	bool wide = wlvअगर->rc_update_bw >= IEEE80211_STA_RX_BW_40;

	wl1271_debug(DEBUG_MAC80211, "mac80211 sta_rc_update wide %d", wide);

	/* sanity */
	अगर (WARN_ON(wlvअगर->bss_type != BSS_TYPE_STA_BSS))
		वापस;

	/* ignore the change beक्रमe association */
	अगर (!test_bit(WLVIF_FLAG_STA_ASSOCIATED, &wlvअगर->flags))
		वापस;

	/*
	 * If we started out as wide, we can change the operation mode. If we
	 * thought this was a 20mhz AP, we have to reconnect
	 */
	अगर (wlvअगर->sta.role_chan_type == NL80211_CHAN_HT40MINUS ||
	    wlvअगर->sta.role_chan_type == NL80211_CHAN_HT40PLUS)
		wl18xx_acx_peer_ht_operation_mode(wl, wlvअगर->sta.hlid, wide);
	अन्यथा
		ieee80211_connection_loss(wl12xx_wlvअगर_to_vअगर(wlvअगर));
पूर्ण

अटल पूर्णांक wl18xx_set_peer_cap(काष्ठा wl1271 *wl,
			       काष्ठा ieee80211_sta_ht_cap *ht_cap,
			       bool allow_ht_operation,
			       u32 rate_set, u8 hlid)
अणु
	वापस wl18xx_acx_set_peer_cap(wl, ht_cap, allow_ht_operation,
				       rate_set, hlid);
पूर्ण

अटल bool wl18xx_lnk_high_prio(काष्ठा wl1271 *wl, u8 hlid,
				 काष्ठा wl1271_link *lnk)
अणु
	u8 thold;
	काष्ठा wl18xx_fw_status_priv *status_priv =
		(काष्ठा wl18xx_fw_status_priv *)wl->fw_status->priv;
	अचिन्हित दीर्घ suspend_biपंचांगap;

	/* अगर we करोn't have the link map yet, assume they all low prio */
	अगर (!status_priv)
		वापस false;

	/* suspended links are never high priority */
	suspend_biपंचांगap = le32_to_cpu(status_priv->link_suspend_biपंचांगap);
	अगर (test_bit(hlid, &suspend_biपंचांगap))
		वापस false;

	/* the priority thresholds are taken from FW */
	अगर (test_bit(hlid, &wl->fw_fast_lnk_map) &&
	    !test_bit(hlid, &wl->ap_fw_ps_map))
		thold = status_priv->tx_fast_link_prio_threshold;
	अन्यथा
		thold = status_priv->tx_slow_link_prio_threshold;

	वापस lnk->allocated_pkts < thold;
पूर्ण

अटल bool wl18xx_lnk_low_prio(काष्ठा wl1271 *wl, u8 hlid,
				काष्ठा wl1271_link *lnk)
अणु
	u8 thold;
	काष्ठा wl18xx_fw_status_priv *status_priv =
		(काष्ठा wl18xx_fw_status_priv *)wl->fw_status->priv;
	अचिन्हित दीर्घ suspend_biपंचांगap;

	/* अगर we करोn't have the link map yet, assume they all low prio */
	अगर (!status_priv)
		वापस true;

	suspend_biपंचांगap = le32_to_cpu(status_priv->link_suspend_biपंचांगap);
	अगर (test_bit(hlid, &suspend_biपंचांगap))
		thold = status_priv->tx_suspend_threshold;
	अन्यथा अगर (test_bit(hlid, &wl->fw_fast_lnk_map) &&
		 !test_bit(hlid, &wl->ap_fw_ps_map))
		thold = status_priv->tx_fast_stop_threshold;
	अन्यथा
		thold = status_priv->tx_slow_stop_threshold;

	वापस lnk->allocated_pkts < thold;
पूर्ण

अटल u32 wl18xx_convert_hwaddr(काष्ठा wl1271 *wl, u32 hwaddr)
अणु
	वापस hwaddr & ~0x80000000;
पूर्ण

अटल पूर्णांक wl18xx_setup(काष्ठा wl1271 *wl);

अटल काष्ठा wlcore_ops wl18xx_ops = अणु
	.setup		= wl18xx_setup,
	.identअगरy_chip	= wl18xx_identअगरy_chip,
	.boot		= wl18xx_boot,
	.plt_init	= wl18xx_plt_init,
	.trigger_cmd	= wl18xx_trigger_cmd,
	.ack_event	= wl18xx_ack_event,
	.रुको_क्रम_event	= wl18xx_रुको_क्रम_event,
	.process_mailbox_events = wl18xx_process_mailbox_events,
	.calc_tx_blocks = wl18xx_calc_tx_blocks,
	.set_tx_desc_blocks = wl18xx_set_tx_desc_blocks,
	.set_tx_desc_data_len = wl18xx_set_tx_desc_data_len,
	.get_rx_buf_align = wl18xx_get_rx_buf_align,
	.get_rx_packet_len = wl18xx_get_rx_packet_len,
	.tx_immediate_compl = wl18xx_tx_immediate_completion,
	.tx_delayed_compl = शून्य,
	.hw_init	= wl18xx_hw_init,
	.convert_fw_status = wl18xx_convert_fw_status,
	.set_tx_desc_csum = wl18xx_set_tx_desc_csum,
	.get_pg_ver	= wl18xx_get_pg_ver,
	.set_rx_csum = wl18xx_set_rx_csum,
	.sta_get_ap_rate_mask = wl18xx_sta_get_ap_rate_mask,
	.ap_get_mimo_wide_rate_mask = wl18xx_ap_get_mimo_wide_rate_mask,
	.get_mac	= wl18xx_get_mac,
	.debugfs_init	= wl18xx_debugfs_add_files,
	.scan_start	= wl18xx_scan_start,
	.scan_stop	= wl18xx_scan_stop,
	.sched_scan_start	= wl18xx_sched_scan_start,
	.sched_scan_stop	= wl18xx_scan_sched_scan_stop,
	.handle_अटल_data	= wl18xx_handle_अटल_data,
	.get_spare_blocks = wl18xx_get_spare_blocks,
	.set_key	= wl18xx_set_key,
	.channel_चयन	= wl18xx_cmd_channel_चयन,
	.pre_pkt_send	= wl18xx_pre_pkt_send,
	.sta_rc_update	= wl18xx_sta_rc_update,
	.set_peer_cap	= wl18xx_set_peer_cap,
	.convert_hwaddr = wl18xx_convert_hwaddr,
	.lnk_high_prio	= wl18xx_lnk_high_prio,
	.lnk_low_prio	= wl18xx_lnk_low_prio,
	.smart_config_start = wl18xx_cmd_smart_config_start,
	.smart_config_stop  = wl18xx_cmd_smart_config_stop,
	.smart_config_set_group_key = wl18xx_cmd_smart_config_set_group_key,
	.पूर्णांकerrupt_notअगरy = wl18xx_acx_पूर्णांकerrupt_notअगरy_config,
	.rx_ba_filter	= wl18xx_acx_rx_ba_filter,
	.ap_sleep	= wl18xx_acx_ap_sleep,
	.set_cac	= wl18xx_cmd_set_cac,
	.dfs_master_restart	= wl18xx_cmd_dfs_master_restart,
पूर्ण;

/* HT cap appropriate क्रम wide channels in 2Ghz */
अटल काष्ठा ieee80211_sta_ht_cap wl18xx_siso40_ht_cap_2ghz = अणु
	.cap = IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40 |
	       IEEE80211_HT_CAP_SUP_WIDTH_20_40 | IEEE80211_HT_CAP_DSSSCCK40 |
	       IEEE80211_HT_CAP_GRN_FLD,
	.ht_supported = true,
	.ampdu_factor = IEEE80211_HT_MAX_AMPDU_16K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.mcs = अणु
		.rx_mask = अणु 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण,
		.rx_highest = cpu_to_le16(150),
		.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
पूर्ण;

/* HT cap appropriate क्रम wide channels in 5Ghz */
अटल काष्ठा ieee80211_sta_ht_cap wl18xx_siso40_ht_cap_5ghz = अणु
	.cap = IEEE80211_HT_CAP_SGI_20 | IEEE80211_HT_CAP_SGI_40 |
	       IEEE80211_HT_CAP_SUP_WIDTH_20_40 |
	       IEEE80211_HT_CAP_GRN_FLD,
	.ht_supported = true,
	.ampdu_factor = IEEE80211_HT_MAX_AMPDU_16K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.mcs = अणु
		.rx_mask = अणु 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण,
		.rx_highest = cpu_to_le16(150),
		.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
पूर्ण;

/* HT cap appropriate क्रम SISO 20 */
अटल काष्ठा ieee80211_sta_ht_cap wl18xx_siso20_ht_cap = अणु
	.cap = IEEE80211_HT_CAP_SGI_20 |
	       IEEE80211_HT_CAP_GRN_FLD,
	.ht_supported = true,
	.ampdu_factor = IEEE80211_HT_MAX_AMPDU_16K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.mcs = अणु
		.rx_mask = अणु 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण,
		.rx_highest = cpu_to_le16(72),
		.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
पूर्ण;

/* HT cap appropriate क्रम MIMO rates in 20mhz channel */
अटल काष्ठा ieee80211_sta_ht_cap wl18xx_mimo_ht_cap_2ghz = अणु
	.cap = IEEE80211_HT_CAP_SGI_20 |
	       IEEE80211_HT_CAP_GRN_FLD,
	.ht_supported = true,
	.ampdu_factor = IEEE80211_HT_MAX_AMPDU_16K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_16,
	.mcs = अणु
		.rx_mask = अणु 0xff, 0xff, 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण,
		.rx_highest = cpu_to_le16(144),
		.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit wl18xx_अगरace_limits[] = अणु
	अणु
		.max = 2,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
	अणु
		.max = 1,
		.types =   BIT(NL80211_IFTYPE_AP)
			 | BIT(NL80211_IFTYPE_P2P_GO)
			 | BIT(NL80211_IFTYPE_P2P_CLIENT)
#अगर_घोषित CONFIG_MAC80211_MESH
			 | BIT(NL80211_IFTYPE_MESH_POINT)
#पूर्ण_अगर
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_P2P_DEVICE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit wl18xx_अगरace_ap_limits[] = अणु
	अणु
		.max = 2,
		.types = BIT(NL80211_IFTYPE_AP),
	पूर्ण,
#अगर_घोषित CONFIG_MAC80211_MESH
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_MESH_POINT),
	पूर्ण,
#पूर्ण_अगर
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_P2P_DEVICE),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination
wl18xx_अगरace_combinations[] = अणु
	अणु
		.max_पूर्णांकerfaces = 3,
		.limits = wl18xx_अगरace_limits,
		.n_limits = ARRAY_SIZE(wl18xx_अगरace_limits),
		.num_dअगरferent_channels = 2,
	पूर्ण,
	अणु
		.max_पूर्णांकerfaces = 2,
		.limits = wl18xx_अगरace_ap_limits,
		.n_limits = ARRAY_SIZE(wl18xx_अगरace_ap_limits),
		.num_dअगरferent_channels = 1,
		.radar_detect_widths =	BIT(NL80211_CHAN_NO_HT) |
					BIT(NL80211_CHAN_HT20) |
					BIT(NL80211_CHAN_HT40MINUS) |
					BIT(NL80211_CHAN_HT40PLUS),
	पूर्ण
पूर्ण;

अटल पूर्णांक wl18xx_setup(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl18xx_priv *priv = wl->priv;
	पूर्णांक ret;

	BUILD_BUG_ON(WL18XX_MAX_LINKS > WLCORE_MAX_LINKS);
	BUILD_BUG_ON(WL18XX_MAX_AP_STATIONS > WL18XX_MAX_LINKS);
	BUILD_BUG_ON(WL18XX_CONF_SG_PARAMS_MAX > WLCORE_CONF_SG_PARAMS_MAX);

	wl->rtable = wl18xx_rtable;
	wl->num_tx_desc = WL18XX_NUM_TX_DESCRIPTORS;
	wl->num_rx_desc = WL18XX_NUM_RX_DESCRIPTORS;
	wl->num_links = WL18XX_MAX_LINKS;
	wl->max_ap_stations = WL18XX_MAX_AP_STATIONS;
	wl->अगरace_combinations = wl18xx_अगरace_combinations;
	wl->n_अगरace_combinations = ARRAY_SIZE(wl18xx_अगरace_combinations);
	wl->num_mac_addr = WL18XX_NUM_MAC_ADDRESSES;
	wl->band_rate_to_idx = wl18xx_band_rate_to_idx;
	wl->hw_tx_rate_tbl_size = WL18XX_CONF_HW_RXTX_RATE_MAX;
	wl->hw_min_ht_rate = WL18XX_CONF_HW_RXTX_RATE_MCS0;
	wl->fw_status_len = माप(काष्ठा wl18xx_fw_status);
	wl->fw_status_priv_len = माप(काष्ठा wl18xx_fw_status_priv);
	wl->stats.fw_stats_len = माप(काष्ठा wl18xx_acx_statistics);
	wl->अटल_data_priv_len = माप(काष्ठा wl18xx_अटल_data_priv);

	अगर (num_rx_desc_param != -1)
		wl->num_rx_desc = num_rx_desc_param;

	ret = wl18xx_conf_init(wl, wl->dev);
	अगर (ret < 0)
		वापस ret;

	/* If the module param is set, update it in conf */
	अगर (board_type_param) अणु
		अगर (!म_भेद(board_type_param, "fpga")) अणु
			priv->conf.phy.board_type = BOARD_TYPE_FPGA_18XX;
		पूर्ण अन्यथा अगर (!म_भेद(board_type_param, "hdk")) अणु
			priv->conf.phy.board_type = BOARD_TYPE_HDK_18XX;
		पूर्ण अन्यथा अगर (!म_भेद(board_type_param, "dvp")) अणु
			priv->conf.phy.board_type = BOARD_TYPE_DVP_18XX;
		पूर्ण अन्यथा अगर (!म_भेद(board_type_param, "evb")) अणु
			priv->conf.phy.board_type = BOARD_TYPE_EVB_18XX;
		पूर्ण अन्यथा अगर (!म_भेद(board_type_param, "com8")) अणु
			priv->conf.phy.board_type = BOARD_TYPE_COM8_18XX;
		पूर्ण अन्यथा अणु
			wl1271_error("invalid board type '%s'",
				board_type_param);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (priv->conf.phy.board_type >= NUM_BOARD_TYPES) अणु
		wl1271_error("invalid board type '%d'",
			priv->conf.phy.board_type);
		वापस -EINVAL;
	पूर्ण

	अगर (low_band_component_param != -1)
		priv->conf.phy.low_band_component = low_band_component_param;
	अगर (low_band_component_type_param != -1)
		priv->conf.phy.low_band_component_type =
			low_band_component_type_param;
	अगर (high_band_component_param != -1)
		priv->conf.phy.high_band_component = high_band_component_param;
	अगर (high_band_component_type_param != -1)
		priv->conf.phy.high_band_component_type =
			high_band_component_type_param;
	अगर (pwr_limit_reference_11_abg_param != -1)
		priv->conf.phy.pwr_limit_reference_11_abg =
			pwr_limit_reference_11_abg_param;
	अगर (n_antennas_2_param != -1)
		priv->conf.phy.number_of_assembled_ant2_4 = n_antennas_2_param;
	अगर (n_antennas_5_param != -1)
		priv->conf.phy.number_of_assembled_ant5 = n_antennas_5_param;
	अगर (dc2dc_param != -1)
		priv->conf.phy.बाह्यal_pa_dc2dc = dc2dc_param;

	अगर (ht_mode_param) अणु
		अगर (!म_भेद(ht_mode_param, "default"))
			priv->conf.ht.mode = HT_MODE_DEFAULT;
		अन्यथा अगर (!म_भेद(ht_mode_param, "wide"))
			priv->conf.ht.mode = HT_MODE_WIDE;
		अन्यथा अगर (!म_भेद(ht_mode_param, "siso20"))
			priv->conf.ht.mode = HT_MODE_SISO20;
		अन्यथा अणु
			wl1271_error("invalid ht_mode '%s'", ht_mode_param);
			वापस -EINVAL;
		पूर्ण
	पूर्ण

	अगर (priv->conf.ht.mode == HT_MODE_DEFAULT) अणु
		/*
		 * Only support mimo with multiple antennas. Fall back to
		 * siso40.
		 */
		अगर (wl18xx_is_mimo_supported(wl))
			wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ,
					  &wl18xx_mimo_ht_cap_2ghz);
		अन्यथा
			wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ,
					  &wl18xx_siso40_ht_cap_2ghz);

		/* 5Ghz is always wide */
		wlcore_set_ht_cap(wl, NL80211_BAND_5GHZ,
				  &wl18xx_siso40_ht_cap_5ghz);
	पूर्ण अन्यथा अगर (priv->conf.ht.mode == HT_MODE_WIDE) अणु
		wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ,
				  &wl18xx_siso40_ht_cap_2ghz);
		wlcore_set_ht_cap(wl, NL80211_BAND_5GHZ,
				  &wl18xx_siso40_ht_cap_5ghz);
	पूर्ण अन्यथा अगर (priv->conf.ht.mode == HT_MODE_SISO20) अणु
		wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ,
				  &wl18xx_siso20_ht_cap);
		wlcore_set_ht_cap(wl, NL80211_BAND_5GHZ,
				  &wl18xx_siso20_ht_cap);
	पूर्ण

	अगर (!checksum_param) अणु
		wl18xx_ops.set_rx_csum = शून्य;
		wl18xx_ops.init_vअगर = शून्य;
	पूर्ण

	/* Enable 11a Band only अगर we have 5G antennas */
	wl->enable_11a = (priv->conf.phy.number_of_assembled_ant5 != 0);

	वापस 0;
पूर्ण

अटल पूर्णांक wl18xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wl1271 *wl;
	काष्ठा ieee80211_hw *hw;
	पूर्णांक ret;

	hw = wlcore_alloc_hw(माप(काष्ठा wl18xx_priv),
			     WL18XX_AGGR_BUFFER_SIZE,
			     माप(काष्ठा wl18xx_event_mailbox));
	अगर (IS_ERR(hw)) अणु
		wl1271_error("can't allocate hw");
		ret = PTR_ERR(hw);
		जाओ out;
	पूर्ण

	wl = hw->priv;
	wl->ops = &wl18xx_ops;
	wl->ptable = wl18xx_ptable;
	ret = wlcore_probe(wl, pdev);
	अगर (ret)
		जाओ out_मुक्त;

	वापस ret;

out_मुक्त:
	wlcore_मुक्त_hw(wl);
out:
	वापस ret;
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id wl18xx_id_table[] = अणु
	अणु "wl18xx", 0 पूर्ण,
	अणु  पूर्ण /* Terminating Entry */
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, wl18xx_id_table);

अटल काष्ठा platक्रमm_driver wl18xx_driver = अणु
	.probe		= wl18xx_probe,
	.हटाओ		= wlcore_हटाओ,
	.id_table	= wl18xx_id_table,
	.driver = अणु
		.name	= "wl18xx_driver",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(wl18xx_driver);
module_param_named(ht_mode, ht_mode_param, अक्षरp, 0400);
MODULE_PARM_DESC(ht_mode, "Force HT mode: wide or siso20");

module_param_named(board_type, board_type_param, अक्षरp, 0400);
MODULE_PARM_DESC(board_type, "Board type: fpga, hdk (default), evb, com8 or "
		 "dvp");

module_param_named(checksum, checksum_param, bool, 0400);
MODULE_PARM_DESC(checksum, "Enable TCP checksum: boolean (defaults to false)");

module_param_named(dc2dc, dc2dc_param, पूर्णांक, 0400);
MODULE_PARM_DESC(dc2dc, "External DC2DC: u8 (defaults to 0)");

module_param_named(n_antennas_2, n_antennas_2_param, पूर्णांक, 0400);
MODULE_PARM_DESC(n_antennas_2,
		 "Number of installed 2.4GHz antennas: 1 (default) or 2");

module_param_named(n_antennas_5, n_antennas_5_param, पूर्णांक, 0400);
MODULE_PARM_DESC(n_antennas_5,
		 "Number of installed 5GHz antennas: 1 (default) or 2");

module_param_named(low_band_component, low_band_component_param, पूर्णांक, 0400);
MODULE_PARM_DESC(low_band_component, "Low band component: u8 "
		 "(default is 0x01)");

module_param_named(low_band_component_type, low_band_component_type_param,
		   पूर्णांक, 0400);
MODULE_PARM_DESC(low_band_component_type, "Low band component type: u8 "
		 "(default is 0x05 or 0x06 depending on the board_type)");

module_param_named(high_band_component, high_band_component_param, पूर्णांक, 0400);
MODULE_PARM_DESC(high_band_component, "High band component: u8, "
		 "(default is 0x01)");

module_param_named(high_band_component_type, high_band_component_type_param,
		   पूर्णांक, 0400);
MODULE_PARM_DESC(high_band_component_type, "High band component type: u8 "
		 "(default is 0x09)");

module_param_named(pwr_limit_reference_11_abg,
		   pwr_limit_reference_11_abg_param, पूर्णांक, 0400);
MODULE_PARM_DESC(pwr_limit_reference_11_abg, "Power limit reference: u8 "
		 "(default is 0xc8)");

module_param_named(num_rx_desc, num_rx_desc_param, पूर्णांक, 0400);
MODULE_PARM_DESC(num_rx_desc_param,
		 "Number of Rx descriptors: u8 (default is 32)");

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Luciano Coelho <coelho@ti.com>");
MODULE_FIRMWARE(WL18XX_FW_NAME);
