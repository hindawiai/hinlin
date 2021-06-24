<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * This file is part of wl1271
 *
 * Copyright (C) 2008-2010 Nokia Corporation
 */

#समावेश <linux/module.h>
#समावेश <linux/mod_devicetable.h>
#समावेश <linux/platक्रमm_device.h>

#समावेश <linux/err.h>

#समावेश "../wlcore/wlcore.h"
#समावेश "../wlcore/debug.h"
#समावेश "../wlcore/io.h"
#समावेश "../wlcore/acx.h"
#समावेश "../wlcore/tx.h"
#समावेश "../wlcore/rx.h"
#समावेश "../wlcore/boot.h"

#समावेश "wl12xx.h"
#समावेश "reg.h"
#समावेश "cmd.h"
#समावेश "acx.h"
#समावेश "scan.h"
#समावेश "event.h"
#समावेश "debugfs.h"
#समावेश "conf.h"

अटल अक्षर *fref_param;
अटल अक्षर *tcxo_param;

अटल काष्ठा wlcore_conf wl12xx_conf = अणु
	.sg = अणु
		.params = अणु
			[WL12XX_CONF_SG_ACL_BT_MASTER_MIN_BR] = 10,
			[WL12XX_CONF_SG_ACL_BT_MASTER_MAX_BR] = 180,
			[WL12XX_CONF_SG_ACL_BT_SLAVE_MIN_BR] = 10,
			[WL12XX_CONF_SG_ACL_BT_SLAVE_MAX_BR] = 180,
			[WL12XX_CONF_SG_ACL_BT_MASTER_MIN_EDR] = 10,
			[WL12XX_CONF_SG_ACL_BT_MASTER_MAX_EDR] = 80,
			[WL12XX_CONF_SG_ACL_BT_SLAVE_MIN_EDR] = 10,
			[WL12XX_CONF_SG_ACL_BT_SLAVE_MAX_EDR] = 80,
			[WL12XX_CONF_SG_ACL_WLAN_PS_MASTER_BR] = 8,
			[WL12XX_CONF_SG_ACL_WLAN_PS_SLAVE_BR] = 8,
			[WL12XX_CONF_SG_ACL_WLAN_PS_MASTER_EDR] = 20,
			[WL12XX_CONF_SG_ACL_WLAN_PS_SLAVE_EDR] = 20,
			[WL12XX_CONF_SG_ACL_WLAN_ACTIVE_MASTER_MIN_BR] = 20,
			[WL12XX_CONF_SG_ACL_WLAN_ACTIVE_MASTER_MAX_BR] = 35,
			[WL12XX_CONF_SG_ACL_WLAN_ACTIVE_SLAVE_MIN_BR] = 16,
			[WL12XX_CONF_SG_ACL_WLAN_ACTIVE_SLAVE_MAX_BR] = 35,
			[WL12XX_CONF_SG_ACL_WLAN_ACTIVE_MASTER_MIN_EDR] = 32,
			[WL12XX_CONF_SG_ACL_WLAN_ACTIVE_MASTER_MAX_EDR] = 50,
			[WL12XX_CONF_SG_ACL_WLAN_ACTIVE_SLAVE_MIN_EDR] = 28,
			[WL12XX_CONF_SG_ACL_WLAN_ACTIVE_SLAVE_MAX_EDR] = 50,
			[WL12XX_CONF_SG_ACL_ACTIVE_SCAN_WLAN_BR] = 10,
			[WL12XX_CONF_SG_ACL_ACTIVE_SCAN_WLAN_EDR] = 20,
			[WL12XX_CONF_SG_ACL_PASSIVE_SCAN_BT_BR] = 75,
			[WL12XX_CONF_SG_ACL_PASSIVE_SCAN_WLAN_BR] = 15,
			[WL12XX_CONF_SG_ACL_PASSIVE_SCAN_BT_EDR] = 27,
			[WL12XX_CONF_SG_ACL_PASSIVE_SCAN_WLAN_EDR] = 17,
			/* active scan params */
			[WL12XX_CONF_SG_AUTO_SCAN_PROBE_REQ] = 170,
			[WL12XX_CONF_SG_ACTIVE_SCAN_DURATION_FACTOR_HV3] = 50,
			[WL12XX_CONF_SG_ACTIVE_SCAN_DURATION_FACTOR_A2DP] = 100,
			/* passive scan params */
			[WL12XX_CONF_SG_PASSIVE_SCAN_DUR_FACTOR_A2DP_BR] = 800,
			[WL12XX_CONF_SG_PASSIVE_SCAN_DUR_FACTOR_A2DP_EDR] = 200,
			[WL12XX_CONF_SG_PASSIVE_SCAN_DUR_FACTOR_HV3] = 200,
			/* passive scan in dual antenna params */
			[WL12XX_CONF_SG_CONSECUTIVE_HV3_IN_PASSIVE_SCAN] = 0,
			[WL12XX_CONF_SG_BCN_HV3_COLL_THR_IN_PASSIVE_SCAN] = 0,
			[WL12XX_CONF_SG_TX_RX_PROTECT_BW_IN_PASSIVE_SCAN] = 0,
			/* general params */
			[WL12XX_CONF_SG_STA_FORCE_PS_IN_BT_SCO] = 1,
			[WL12XX_CONF_SG_ANTENNA_CONFIGURATION] = 0,
			[WL12XX_CONF_SG_BEACON_MISS_PERCENT] = 60,
			[WL12XX_CONF_SG_DHCP_TIME] = 5000,
			[WL12XX_CONF_SG_RXT] = 1200,
			[WL12XX_CONF_SG_TXT] = 1000,
			[WL12XX_CONF_SG_ADAPTIVE_RXT_TXT] = 1,
			[WL12XX_CONF_SG_GENERAL_USAGE_BIT_MAP] = 3,
			[WL12XX_CONF_SG_HV3_MAX_SERVED] = 6,
			[WL12XX_CONF_SG_PS_POLL_TIMEOUT] = 10,
			[WL12XX_CONF_SG_UPSD_TIMEOUT] = 10,
			[WL12XX_CONF_SG_CONSECUTIVE_CTS_THRESHOLD] = 2,
			[WL12XX_CONF_SG_STA_RX_WINDOW_AFTER_DTIM] = 5,
			[WL12XX_CONF_SG_STA_CONNECTION_PROTECTION_TIME] = 30,
			/* AP params */
			[WL12XX_CONF_AP_BEACON_MISS_TX] = 3,
			[WL12XX_CONF_AP_RX_WINDOW_AFTER_BEACON] = 10,
			[WL12XX_CONF_AP_BEACON_WINDOW_INTERVAL] = 2,
			[WL12XX_CONF_AP_CONNECTION_PROTECTION_TIME] = 0,
			[WL12XX_CONF_AP_BT_ACL_VAL_BT_SERVE_TIME] = 25,
			[WL12XX_CONF_AP_BT_ACL_VAL_WL_SERVE_TIME] = 25,
			/* CTS Diluting params */
			[WL12XX_CONF_SG_CTS_DILUTED_BAD_RX_PACKETS_TH] = 0,
			[WL12XX_CONF_SG_CTS_CHOP_IN_DUAL_ANT_SCO_MASTER] = 0,
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
		.tx_compl_समयout            = 700,
		.tx_compl_threshold          = 4,
		.basic_rate                  = CONF_HW_BIT_RATE_1MBPS,
		.basic_rate_5                = CONF_HW_BIT_RATE_6MBPS,
		.पंचांगpl_लघु_retry_limit      = 10,
		.पंचांगpl_दीर्घ_retry_limit       = 10,
		.tx_watchकरोg_समयout         = 5000,
		.slow_link_thold             = 3,
		.fast_link_thold             = 10,
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
	पूर्ण,
	.ht = अणु
		.rx_ba_win_size = 8,
		.tx_ba_win_size = 64,
		.inactivity_समयout = 10000,
		.tx_ba_tid_biपंचांगap = CONF_TX_BA_ENABLED_TID_BITMAP,
	पूर्ण,
	/*
	 * Memory config क्रम wl127x chips is given in the
	 * wl12xx_शेष_priv_conf काष्ठा. The below configuration is
	 * क्रम wl128x chips.
	 */
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
		.m_भागider_fref_set_2         = 148,	    /* शेष */
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
		.mem_blocks                   = 2,
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

अटल काष्ठा wl12xx_priv_conf wl12xx_शेष_priv_conf = अणु
	.rf = अणु
		.tx_per_channel_घातer_compensation_2 = अणु
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		पूर्ण,
		.tx_per_channel_घातer_compensation_5 = अणु
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
			0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
		पूर्ण,
	पूर्ण,
	.mem_wl127x = अणु
		.num_stations                 = 1,
		.ssid_profiles                = 1,
		.rx_block_num                 = 70,
		.tx_min_block_num             = 40,
		.dynamic_memory               = 1,
		.min_req_tx_blocks            = 100,
		.min_req_rx_blocks            = 22,
		.tx_min                       = 27,
	पूर्ण,

पूर्ण;

#घोषणा WL12XX_TX_HW_BLOCK_SPARE_DEFAULT        1
#घोषणा WL12XX_TX_HW_BLOCK_GEM_SPARE            2
#घोषणा WL12XX_TX_HW_BLOCK_SIZE                 252

अटल स्थिर u8 wl12xx_rate_to_idx_2ghz[] = अणु
	/* MCS rates are used only with 11n */
	7,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS7_SGI */
	7,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS7 */
	6,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS6 */
	5,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS5 */
	4,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS4 */
	3,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS3 */
	2,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS2 */
	1,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS1 */
	0,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS0 */

	11,                            /* WL12XX_CONF_HW_RXTX_RATE_54   */
	10,                            /* WL12XX_CONF_HW_RXTX_RATE_48   */
	9,                             /* WL12XX_CONF_HW_RXTX_RATE_36   */
	8,                             /* WL12XX_CONF_HW_RXTX_RATE_24   */

	/* TI-specअगरic rate */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL12XX_CONF_HW_RXTX_RATE_22   */

	7,                             /* WL12XX_CONF_HW_RXTX_RATE_18   */
	6,                             /* WL12XX_CONF_HW_RXTX_RATE_12   */
	3,                             /* WL12XX_CONF_HW_RXTX_RATE_11   */
	5,                             /* WL12XX_CONF_HW_RXTX_RATE_9    */
	4,                             /* WL12XX_CONF_HW_RXTX_RATE_6    */
	2,                             /* WL12XX_CONF_HW_RXTX_RATE_5_5  */
	1,                             /* WL12XX_CONF_HW_RXTX_RATE_2    */
	0                              /* WL12XX_CONF_HW_RXTX_RATE_1    */
पूर्ण;

अटल स्थिर u8 wl12xx_rate_to_idx_5ghz[] = अणु
	/* MCS rates are used only with 11n */
	7,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS7_SGI */
	7,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS7 */
	6,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS6 */
	5,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS5 */
	4,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS4 */
	3,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS3 */
	2,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS2 */
	1,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS1 */
	0,                             /* WL12XX_CONF_HW_RXTX_RATE_MCS0 */

	7,                             /* WL12XX_CONF_HW_RXTX_RATE_54   */
	6,                             /* WL12XX_CONF_HW_RXTX_RATE_48   */
	5,                             /* WL12XX_CONF_HW_RXTX_RATE_36   */
	4,                             /* WL12XX_CONF_HW_RXTX_RATE_24   */

	/* TI-specअगरic rate */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL12XX_CONF_HW_RXTX_RATE_22   */

	3,                             /* WL12XX_CONF_HW_RXTX_RATE_18   */
	2,                             /* WL12XX_CONF_HW_RXTX_RATE_12   */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL12XX_CONF_HW_RXTX_RATE_11   */
	1,                             /* WL12XX_CONF_HW_RXTX_RATE_9    */
	0,                             /* WL12XX_CONF_HW_RXTX_RATE_6    */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL12XX_CONF_HW_RXTX_RATE_5_5  */
	CONF_HW_RXTX_RATE_UNSUPPORTED, /* WL12XX_CONF_HW_RXTX_RATE_2    */
	CONF_HW_RXTX_RATE_UNSUPPORTED  /* WL12XX_CONF_HW_RXTX_RATE_1    */
पूर्ण;

अटल स्थिर u8 *wl12xx_band_rate_to_idx[] = अणु
	[NL80211_BAND_2GHZ] = wl12xx_rate_to_idx_2ghz,
	[NL80211_BAND_5GHZ] = wl12xx_rate_to_idx_5ghz
पूर्ण;

क्रमागत wl12xx_hw_rates अणु
	WL12XX_CONF_HW_RXTX_RATE_MCS7_SGI = 0,
	WL12XX_CONF_HW_RXTX_RATE_MCS7,
	WL12XX_CONF_HW_RXTX_RATE_MCS6,
	WL12XX_CONF_HW_RXTX_RATE_MCS5,
	WL12XX_CONF_HW_RXTX_RATE_MCS4,
	WL12XX_CONF_HW_RXTX_RATE_MCS3,
	WL12XX_CONF_HW_RXTX_RATE_MCS2,
	WL12XX_CONF_HW_RXTX_RATE_MCS1,
	WL12XX_CONF_HW_RXTX_RATE_MCS0,
	WL12XX_CONF_HW_RXTX_RATE_54,
	WL12XX_CONF_HW_RXTX_RATE_48,
	WL12XX_CONF_HW_RXTX_RATE_36,
	WL12XX_CONF_HW_RXTX_RATE_24,
	WL12XX_CONF_HW_RXTX_RATE_22,
	WL12XX_CONF_HW_RXTX_RATE_18,
	WL12XX_CONF_HW_RXTX_RATE_12,
	WL12XX_CONF_HW_RXTX_RATE_11,
	WL12XX_CONF_HW_RXTX_RATE_9,
	WL12XX_CONF_HW_RXTX_RATE_6,
	WL12XX_CONF_HW_RXTX_RATE_5_5,
	WL12XX_CONF_HW_RXTX_RATE_2,
	WL12XX_CONF_HW_RXTX_RATE_1,
	WL12XX_CONF_HW_RXTX_RATE_MAX,
पूर्ण;

अटल काष्ठा wlcore_partition_set wl12xx_ptable[PART_TABLE_LEN] = अणु
	[PART_DOWN] = अणु
		.mem = अणु
			.start = 0x00000000,
			.size  = 0x000177c0
		पूर्ण,
		.reg = अणु
			.start = REGISTERS_BASE,
			.size  = 0x00008800
		पूर्ण,
		.mem2 = अणु
			.start = 0x00000000,
			.size  = 0x00000000
		पूर्ण,
		.mem3 = अणु
			.start = 0x00000000,
			.size  = 0x00000000
		पूर्ण,
	पूर्ण,

	[PART_BOOT] = अणु /* in wl12xx we can use a mix of work and करोwn
			 * partition here */
		.mem = अणु
			.start = 0x00040000,
			.size  = 0x00014fc0
		पूर्ण,
		.reg = अणु
			.start = REGISTERS_BASE,
			.size  = 0x00008800
		पूर्ण,
		.mem2 = अणु
			.start = 0x00000000,
			.size  = 0x00000000
		पूर्ण,
		.mem3 = अणु
			.start = 0x00000000,
			.size  = 0x00000000
		पूर्ण,
	पूर्ण,

	[PART_WORK] = अणु
		.mem = अणु
			.start = 0x00040000,
			.size  = 0x00014fc0
		पूर्ण,
		.reg = अणु
			.start = REGISTERS_BASE,
			.size  = 0x0000a000
		पूर्ण,
		.mem2 = अणु
			.start = 0x003004f8,
			.size  = 0x00000004
		पूर्ण,
		.mem3 = अणु
			.start = 0x00000000,
			.size  = 0x00040404
		पूर्ण,
	पूर्ण,

	[PART_DRPW] = अणु
		.mem = अणु
			.start = 0x00040000,
			.size  = 0x00014fc0
		पूर्ण,
		.reg = अणु
			.start = DRPW_BASE,
			.size  = 0x00006000
		पूर्ण,
		.mem2 = अणु
			.start = 0x00000000,
			.size  = 0x00000000
		पूर्ण,
		.mem3 = अणु
			.start = 0x00000000,
			.size  = 0x00000000
		पूर्ण
	पूर्ण
पूर्ण;

अटल स्थिर पूर्णांक wl12xx_rtable[REG_TABLE_LEN] = अणु
	[REG_ECPU_CONTROL]		= WL12XX_REG_ECPU_CONTROL,
	[REG_INTERRUPT_NO_CLEAR]	= WL12XX_REG_INTERRUPT_NO_CLEAR,
	[REG_INTERRUPT_ACK]		= WL12XX_REG_INTERRUPT_ACK,
	[REG_COMMAND_MAILBOX_PTR]	= WL12XX_REG_COMMAND_MAILBOX_PTR,
	[REG_EVENT_MAILBOX_PTR]		= WL12XX_REG_EVENT_MAILBOX_PTR,
	[REG_INTERRUPT_TRIG]		= WL12XX_REG_INTERRUPT_TRIG,
	[REG_INTERRUPT_MASK]		= WL12XX_REG_INTERRUPT_MASK,
	[REG_PC_ON_RECOVERY]		= WL12XX_SCR_PAD4,
	[REG_CHIP_ID_B]			= WL12XX_CHIP_ID_B,
	[REG_CMD_MBOX_ADDRESS]		= WL12XX_CMD_MBOX_ADDRESS,

	/* data access memory addresses, used with partition translation */
	[REG_SLV_MEM_DATA]		= WL1271_SLV_MEM_DATA,
	[REG_SLV_REG_DATA]		= WL1271_SLV_REG_DATA,

	/* raw data access memory addresses */
	[REG_RAW_FW_STATUS_ADDR]	= FW_STATUS_ADDR,
पूर्ण;

/* TODO: maybe move to a new header file? */
#घोषणा WL127X_FW_NAME_MULTI	"ti-connectivity/wl127x-fw-5-mr.bin"
#घोषणा WL127X_FW_NAME_SINGLE	"ti-connectivity/wl127x-fw-5-sr.bin"
#घोषणा WL127X_PLT_FW_NAME	"ti-connectivity/wl127x-fw-5-plt.bin"

#घोषणा WL128X_FW_NAME_MULTI	"ti-connectivity/wl128x-fw-5-mr.bin"
#घोषणा WL128X_FW_NAME_SINGLE	"ti-connectivity/wl128x-fw-5-sr.bin"
#घोषणा WL128X_PLT_FW_NAME	"ti-connectivity/wl128x-fw-5-plt.bin"

अटल पूर्णांक wl127x_prepare_पढ़ो(काष्ठा wl1271 *wl, u32 rx_desc, u32 len)
अणु
	पूर्णांक ret;

	अगर (wl->chip.id != CHIP_ID_128X_PG20) अणु
		काष्ठा wl1271_acx_mem_map *wl_mem_map = wl->target_mem_map;
		काष्ठा wl12xx_priv *priv = wl->priv;

		/*
		 * Choose the block we want to पढ़ो
		 * For aggregated packets, only the first memory block
		 * should be retrieved. The FW takes care of the rest.
		 */
		u32 mem_block = rx_desc & RX_MEM_BLOCK_MASK;

		priv->rx_mem_addr->addr = (mem_block << 8) +
			le32_to_cpu(wl_mem_map->packet_memory_pool_start);

		priv->rx_mem_addr->addr_extra = priv->rx_mem_addr->addr + 4;

		ret = wlcore_ग_लिखो(wl, WL1271_SLV_REG_DATA, priv->rx_mem_addr,
				   माप(*priv->rx_mem_addr), false);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस 0;
पूर्ण

अटल पूर्णांक wl12xx_identअगरy_chip(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret = 0;

	चयन (wl->chip.id) अणु
	हाल CHIP_ID_127X_PG10:
		wl1271_warning("chip id 0x%x (1271 PG10) support is obsolete",
			       wl->chip.id);

		wl->quirks |= WLCORE_QUIRK_LEGACY_NVS |
			      WLCORE_QUIRK_DUAL_PROBE_TMPL |
			      WLCORE_QUIRK_TKIP_HEADER_SPACE |
			      WLCORE_QUIRK_AP_ZERO_SESSION_ID;
		wl->sr_fw_name = WL127X_FW_NAME_SINGLE;
		wl->mr_fw_name = WL127X_FW_NAME_MULTI;
		स_नकल(&wl->conf.mem, &wl12xx_शेष_priv_conf.mem_wl127x,
		       माप(wl->conf.mem));

		/* पढ़ो data preparation is only needed by wl127x */
		wl->ops->prepare_पढ़ो = wl127x_prepare_पढ़ो;

		wlcore_set_min_fw_ver(wl, WL127X_CHIP_VER,
			      WL127X_IFTYPE_SR_VER,  WL127X_MAJOR_SR_VER,
			      WL127X_SUBTYPE_SR_VER, WL127X_MINOR_SR_VER,
			      WL127X_IFTYPE_MR_VER,  WL127X_MAJOR_MR_VER,
			      WL127X_SUBTYPE_MR_VER, WL127X_MINOR_MR_VER);
		अवरोध;

	हाल CHIP_ID_127X_PG20:
		wl1271_debug(DEBUG_BOOT, "chip id 0x%x (1271 PG20)",
			     wl->chip.id);

		wl->quirks |= WLCORE_QUIRK_LEGACY_NVS |
			      WLCORE_QUIRK_DUAL_PROBE_TMPL |
			      WLCORE_QUIRK_TKIP_HEADER_SPACE |
			      WLCORE_QUIRK_AP_ZERO_SESSION_ID;
		wl->plt_fw_name = WL127X_PLT_FW_NAME;
		wl->sr_fw_name = WL127X_FW_NAME_SINGLE;
		wl->mr_fw_name = WL127X_FW_NAME_MULTI;
		स_नकल(&wl->conf.mem, &wl12xx_शेष_priv_conf.mem_wl127x,
		       माप(wl->conf.mem));

		/* पढ़ो data preparation is only needed by wl127x */
		wl->ops->prepare_पढ़ो = wl127x_prepare_पढ़ो;

		wlcore_set_min_fw_ver(wl, WL127X_CHIP_VER,
			      WL127X_IFTYPE_SR_VER,  WL127X_MAJOR_SR_VER,
			      WL127X_SUBTYPE_SR_VER, WL127X_MINOR_SR_VER,
			      WL127X_IFTYPE_MR_VER,  WL127X_MAJOR_MR_VER,
			      WL127X_SUBTYPE_MR_VER, WL127X_MINOR_MR_VER);
		अवरोध;

	हाल CHIP_ID_128X_PG20:
		wl1271_debug(DEBUG_BOOT, "chip id 0x%x (1283 PG20)",
			     wl->chip.id);
		wl->plt_fw_name = WL128X_PLT_FW_NAME;
		wl->sr_fw_name = WL128X_FW_NAME_SINGLE;
		wl->mr_fw_name = WL128X_FW_NAME_MULTI;

		/* wl128x requires TX blocksize alignment */
		wl->quirks |= WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN |
			      WLCORE_QUIRK_DUAL_PROBE_TMPL |
			      WLCORE_QUIRK_TKIP_HEADER_SPACE |
			      WLCORE_QUIRK_AP_ZERO_SESSION_ID;

		wlcore_set_min_fw_ver(wl, WL128X_CHIP_VER,
			      WL128X_IFTYPE_SR_VER,  WL128X_MAJOR_SR_VER,
			      WL128X_SUBTYPE_SR_VER, WL128X_MINOR_SR_VER,
			      WL128X_IFTYPE_MR_VER,  WL128X_MAJOR_MR_VER,
			      WL128X_SUBTYPE_MR_VER, WL128X_MINOR_MR_VER);
		अवरोध;
	हाल CHIP_ID_128X_PG10:
	शेष:
		wl1271_warning("unsupported chip id: 0x%x", wl->chip.id);
		ret = -ENODEV;
		जाओ out;
	पूर्ण

	wl->fw_mem_block_size = 256;
	wl->fwlog_end = 0x2000000;

	/* common settings */
	wl->scan_templ_id_2_4 = CMD_TEMPL_APP_PROBE_REQ_2_4_LEGACY;
	wl->scan_templ_id_5 = CMD_TEMPL_APP_PROBE_REQ_5_LEGACY;
	wl->sched_scan_templ_id_2_4 = CMD_TEMPL_CFG_PROBE_REQ_2_4;
	wl->sched_scan_templ_id_5 = CMD_TEMPL_CFG_PROBE_REQ_5;
	wl->max_channels_5 = WL12XX_MAX_CHANNELS_5GHZ;
	wl->ba_rx_session_count_max = WL12XX_RX_BA_MAX_SESSIONS;
out:
	वापस ret;
पूर्ण

अटल पूर्णांक __must_check wl12xx_top_reg_ग_लिखो(काष्ठा wl1271 *wl, पूर्णांक addr,
					     u16 val)
अणु
	पूर्णांक ret;

	/* ग_लिखो address >> 1 + 0x30000 to OCP_POR_CTR */
	addr = (addr >> 1) + 0x30000;
	ret = wlcore_ग_लिखो32(wl, WL12XX_OCP_POR_CTR, addr);
	अगर (ret < 0)
		जाओ out;

	/* ग_लिखो value to OCP_POR_WDATA */
	ret = wlcore_ग_लिखो32(wl, WL12XX_OCP_DATA_WRITE, val);
	अगर (ret < 0)
		जाओ out;

	/* ग_लिखो 1 to OCP_CMD */
	ret = wlcore_ग_लिखो32(wl, WL12XX_OCP_CMD, OCP_CMD_WRITE);
	अगर (ret < 0)
		जाओ out;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक __must_check wl12xx_top_reg_पढ़ो(काष्ठा wl1271 *wl, पूर्णांक addr,
					    u16 *out)
अणु
	u32 val;
	पूर्णांक समयout = OCP_CMD_LOOP;
	पूर्णांक ret;

	/* ग_लिखो address >> 1 + 0x30000 to OCP_POR_CTR */
	addr = (addr >> 1) + 0x30000;
	ret = wlcore_ग_लिखो32(wl, WL12XX_OCP_POR_CTR, addr);
	अगर (ret < 0)
		वापस ret;

	/* ग_लिखो 2 to OCP_CMD */
	ret = wlcore_ग_लिखो32(wl, WL12XX_OCP_CMD, OCP_CMD_READ);
	अगर (ret < 0)
		वापस ret;

	/* poll क्रम data पढ़ोy */
	करो अणु
		ret = wlcore_पढ़ो32(wl, WL12XX_OCP_DATA_READ, &val);
		अगर (ret < 0)
			वापस ret;
	पूर्ण जबतक (!(val & OCP_READY_MASK) && --समयout);

	अगर (!समयout) अणु
		wl1271_warning("Top register access timed out.");
		वापस -ETIMEDOUT;
	पूर्ण

	/* check data status and वापस अगर OK */
	अगर ((val & OCP_STATUS_MASK) != OCP_STATUS_OK) अणु
		wl1271_warning("Top register access returned error.");
		वापस -EIO;
	पूर्ण

	अगर (out)
		*out = val & 0xffff;

	वापस 0;
पूर्ण

अटल पूर्णांक wl128x_चयन_tcxo_to_fref(काष्ठा wl1271 *wl)
अणु
	u16 spare_reg;
	पूर्णांक ret;

	/* Mask bits [2] & [8:4] in the sys_clk_cfg रेजिस्टर */
	ret = wl12xx_top_reg_पढ़ो(wl, WL_SPARE_REG, &spare_reg);
	अगर (ret < 0)
		वापस ret;

	अगर (spare_reg == 0xFFFF)
		वापस -EFAULT;
	spare_reg |= (BIT(3) | BIT(5) | BIT(6));
	ret = wl12xx_top_reg_ग_लिखो(wl, WL_SPARE_REG, spare_reg);
	अगर (ret < 0)
		वापस ret;

	/* Enable FREF_CLK_REQ & mux MCS and coex PLLs to FREF */
	ret = wl12xx_top_reg_ग_लिखो(wl, SYS_CLK_CFG_REG,
				   WL_CLK_REQ_TYPE_PG2 | MCS_PLL_CLK_SEL_FREF);
	अगर (ret < 0)
		वापस ret;

	/* Delay execution क्रम 15msec, to let the HW settle */
	mdelay(15);

	वापस 0;
पूर्ण

अटल bool wl128x_is_tcxo_valid(काष्ठा wl1271 *wl)
अणु
	u16 tcxo_detection;
	पूर्णांक ret;

	ret = wl12xx_top_reg_पढ़ो(wl, TCXO_CLK_DETECT_REG, &tcxo_detection);
	अगर (ret < 0)
		वापस false;

	अगर (tcxo_detection & TCXO_DET_FAILED)
		वापस false;

	वापस true;
पूर्ण

अटल bool wl128x_is_fref_valid(काष्ठा wl1271 *wl)
अणु
	u16 fref_detection;
	पूर्णांक ret;

	ret = wl12xx_top_reg_पढ़ो(wl, FREF_CLK_DETECT_REG, &fref_detection);
	अगर (ret < 0)
		वापस false;

	अगर (fref_detection & FREF_CLK_DETECT_FAIL)
		वापस false;

	वापस true;
पूर्ण

अटल पूर्णांक wl128x_manually_configure_mcs_pll(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wl12xx_top_reg_ग_लिखो(wl, MCS_PLL_M_REG, MCS_PLL_M_REG_VAL);
	अगर (ret < 0)
		जाओ out;

	ret = wl12xx_top_reg_ग_लिखो(wl, MCS_PLL_N_REG, MCS_PLL_N_REG_VAL);
	अगर (ret < 0)
		जाओ out;

	ret = wl12xx_top_reg_ग_लिखो(wl, MCS_PLL_CONFIG_REG,
				   MCS_PLL_CONFIG_REG_VAL);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl128x_configure_mcs_pll(काष्ठा wl1271 *wl, पूर्णांक clk)
अणु
	u16 spare_reg;
	u16 pll_config;
	u8 input_freq;
	काष्ठा wl12xx_priv *priv = wl->priv;
	पूर्णांक ret;

	/* Mask bits [3:1] in the sys_clk_cfg रेजिस्टर */
	ret = wl12xx_top_reg_पढ़ो(wl, WL_SPARE_REG, &spare_reg);
	अगर (ret < 0)
		वापस ret;

	अगर (spare_reg == 0xFFFF)
		वापस -EFAULT;
	spare_reg |= BIT(2);
	ret = wl12xx_top_reg_ग_लिखो(wl, WL_SPARE_REG, spare_reg);
	अगर (ret < 0)
		वापस ret;

	/* Handle special हालs of the TCXO घड़ी */
	अगर (priv->tcxo_घड़ी == WL12XX_TCXOCLOCK_16_8 ||
	    priv->tcxo_घड़ी == WL12XX_TCXOCLOCK_33_6)
		वापस wl128x_manually_configure_mcs_pll(wl);

	/* Set the input frequency according to the selected घड़ी source */
	input_freq = (clk & 1) + 1;

	ret = wl12xx_top_reg_पढ़ो(wl, MCS_PLL_CONFIG_REG, &pll_config);
	अगर (ret < 0)
		वापस ret;

	अगर (pll_config == 0xFFFF)
		वापस -EFAULT;
	pll_config |= (input_freq << MCS_SEL_IN_FREQ_SHIFT);
	pll_config |= MCS_PLL_ENABLE_HP;
	ret = wl12xx_top_reg_ग_लिखो(wl, MCS_PLL_CONFIG_REG, pll_config);

	वापस ret;
पूर्ण

/*
 * WL128x has two घड़ीs input - TCXO and FREF.
 * TCXO is the मुख्य घड़ी of the device, जबतक FREF is used to sync
 * between the GPS and the cellular modem.
 * In हालs where TCXO is 32.736MHz or 16.368MHz, the FREF will be used
 * as the WLAN/BT मुख्य घड़ी.
 */
अटल पूर्णांक wl128x_boot_clk(काष्ठा wl1271 *wl, पूर्णांक *selected_घड़ी)
अणु
	काष्ठा wl12xx_priv *priv = wl->priv;
	u16 sys_clk_cfg;
	पूर्णांक ret;

	/* For XTAL-only modes, FREF will be used after चयनing from TCXO */
	अगर (priv->ref_घड़ी == WL12XX_REFCLOCK_26_XTAL ||
	    priv->ref_घड़ी == WL12XX_REFCLOCK_38_XTAL) अणु
		अगर (!wl128x_चयन_tcxo_to_fref(wl))
			वापस -EINVAL;
		जाओ fref_clk;
	पूर्ण

	/* Query the HW, to determine which घड़ी source we should use */
	ret = wl12xx_top_reg_पढ़ो(wl, SYS_CLK_CFG_REG, &sys_clk_cfg);
	अगर (ret < 0)
		वापस ret;

	अगर (sys_clk_cfg == 0xFFFF)
		वापस -EINVAL;
	अगर (sys_clk_cfg & PRCM_CM_EN_MUX_WLAN_FREF)
		जाओ fref_clk;

	/* If TCXO is either 32.736MHz or 16.368MHz, चयन to FREF */
	अगर (priv->tcxo_घड़ी == WL12XX_TCXOCLOCK_16_368 ||
	    priv->tcxo_घड़ी == WL12XX_TCXOCLOCK_32_736) अणु
		अगर (!wl128x_चयन_tcxo_to_fref(wl))
			वापस -EINVAL;
		जाओ fref_clk;
	पूर्ण

	/* TCXO घड़ी is selected */
	अगर (!wl128x_is_tcxo_valid(wl))
		वापस -EINVAL;
	*selected_घड़ी = priv->tcxo_घड़ी;
	जाओ config_mcs_pll;

fref_clk:
	/* FREF घड़ी is selected */
	अगर (!wl128x_is_fref_valid(wl))
		वापस -EINVAL;
	*selected_घड़ी = priv->ref_घड़ी;

config_mcs_pll:
	वापस wl128x_configure_mcs_pll(wl, *selected_घड़ी);
पूर्ण

अटल पूर्णांक wl127x_boot_clk(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_priv *priv = wl->priv;
	u32 छोड़ो;
	u32 clk;
	पूर्णांक ret;

	अगर (WL127X_PG_GET_MAJOR(wl->hw_pg_ver) < 3)
		wl->quirks |= WLCORE_QUIRK_END_OF_TRANSACTION;

	अगर (priv->ref_घड़ी == CONF_REF_CLK_19_2_E ||
	    priv->ref_घड़ी == CONF_REF_CLK_38_4_E ||
	    priv->ref_घड़ी == CONF_REF_CLK_38_4_M_XTAL)
		/* ref clk: 19.2/38.4/38.4-XTAL */
		clk = 0x3;
	अन्यथा अगर (priv->ref_घड़ी == CONF_REF_CLK_26_E ||
		 priv->ref_घड़ी == CONF_REF_CLK_26_M_XTAL ||
		 priv->ref_घड़ी == CONF_REF_CLK_52_E)
		/* ref clk: 26/52 */
		clk = 0x5;
	अन्यथा
		वापस -EINVAL;

	अगर (priv->ref_घड़ी != CONF_REF_CLK_19_2_E) अणु
		u16 val;
		/* Set घड़ी type (खोलो drain) */
		ret = wl12xx_top_reg_पढ़ो(wl, OCP_REG_CLK_TYPE, &val);
		अगर (ret < 0)
			जाओ out;

		val &= FREF_CLK_TYPE_BITS;
		ret = wl12xx_top_reg_ग_लिखो(wl, OCP_REG_CLK_TYPE, val);
		अगर (ret < 0)
			जाओ out;

		/* Set घड़ी pull mode (no pull) */
		ret = wl12xx_top_reg_पढ़ो(wl, OCP_REG_CLK_PULL, &val);
		अगर (ret < 0)
			जाओ out;

		val |= NO_PULL;
		ret = wl12xx_top_reg_ग_लिखो(wl, OCP_REG_CLK_PULL, val);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		u16 val;
		/* Set घड़ी polarity */
		ret = wl12xx_top_reg_पढ़ो(wl, OCP_REG_CLK_POLARITY, &val);
		अगर (ret < 0)
			जाओ out;

		val &= FREF_CLK_POLARITY_BITS;
		val |= CLK_REQ_OUTN_SEL;
		ret = wl12xx_top_reg_ग_लिखो(wl, OCP_REG_CLK_POLARITY, val);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	ret = wlcore_ग_लिखो32(wl, WL12XX_PLL_PARAMETERS, clk);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_पढ़ो32(wl, WL12XX_PLL_PARAMETERS, &छोड़ो);
	अगर (ret < 0)
		जाओ out;

	wl1271_debug(DEBUG_BOOT, "pause1 0x%x", छोड़ो);

	छोड़ो &= ~(WU_COUNTER_PAUSE_VAL);
	छोड़ो |= WU_COUNTER_PAUSE_VAL;
	ret = wlcore_ग_लिखो32(wl, WL12XX_WU_COUNTER_PAUSE, छोड़ो);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl1271_boot_soft_reset(काष्ठा wl1271 *wl)
अणु
	अचिन्हित दीर्घ समयout;
	u32 boot_data;
	पूर्णांक ret = 0;

	/* perक्रमm soft reset */
	ret = wlcore_ग_लिखो32(wl, WL12XX_SLV_SOFT_RESET, ACX_SLV_SOFT_RESET_BIT);
	अगर (ret < 0)
		जाओ out;

	/* SOFT_RESET is self clearing */
	समयout = jअगरfies + usecs_to_jअगरfies(SOFT_RESET_MAX_TIME);
	जबतक (1) अणु
		ret = wlcore_पढ़ो32(wl, WL12XX_SLV_SOFT_RESET, &boot_data);
		अगर (ret < 0)
			जाओ out;

		wl1271_debug(DEBUG_BOOT, "soft reset bootdata 0x%x", boot_data);
		अगर ((boot_data & ACX_SLV_SOFT_RESET_BIT) == 0)
			अवरोध;

		अगर (समय_after(jअगरfies, समयout)) अणु
			/* 1.2 check pWhalBus->uSelfClearTime अगर the
			 * समयout was reached */
			wl1271_error("soft reset timeout");
			वापस -1;
		पूर्ण

		udelay(SOFT_RESET_STALL_TIME);
	पूर्ण

	/* disable Rx/Tx */
	ret = wlcore_ग_लिखो32(wl, WL12XX_ENABLE, 0x0);
	अगर (ret < 0)
		जाओ out;

	/* disable स्वतः calibration on start*/
	ret = wlcore_ग_लिखो32(wl, WL12XX_SPARE_A2, 0xffff);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_pre_boot(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_priv *priv = wl->priv;
	पूर्णांक ret = 0;
	u32 clk;
	पूर्णांक selected_घड़ी = -1;

	अगर (wl->chip.id == CHIP_ID_128X_PG20) अणु
		ret = wl128x_boot_clk(wl, &selected_घड़ी);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = wl127x_boot_clk(wl);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* Continue the ELP wake up sequence */
	ret = wlcore_ग_लिखो32(wl, WL12XX_WELP_ARM_COMMAND, WELP_ARM_COMMAND_VAL);
	अगर (ret < 0)
		जाओ out;

	udelay(500);

	ret = wlcore_set_partition(wl, &wl->ptable[PART_DRPW]);
	अगर (ret < 0)
		जाओ out;

	/* Read-modअगरy-ग_लिखो DRPW_SCRATCH_START रेजिस्टर (see next state)
	   to be used by DRPw FW. The RTRIM value will be added by the FW
	   beक्रमe taking DRPw out of reset */

	ret = wlcore_पढ़ो32(wl, WL12XX_DRPW_SCRATCH_START, &clk);
	अगर (ret < 0)
		जाओ out;

	wl1271_debug(DEBUG_BOOT, "clk2 0x%x", clk);

	अगर (wl->chip.id == CHIP_ID_128X_PG20)
		clk |= ((selected_घड़ी & 0x3) << 1) << 4;
	अन्यथा
		clk |= (priv->ref_घड़ी << 1) << 4;

	ret = wlcore_ग_लिखो32(wl, WL12XX_DRPW_SCRATCH_START, clk);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_WORK]);
	अगर (ret < 0)
		जाओ out;

	/* Disable पूर्णांकerrupts */
	ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_MASK, WL1271_ACX_INTR_ALL);
	अगर (ret < 0)
		जाओ out;

	ret = wl1271_boot_soft_reset(wl);
	अगर (ret < 0)
		जाओ out;

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_pre_upload(काष्ठा wl1271 *wl)
अणु
	u32 पंचांगp;
	u16 polarity;
	पूर्णांक ret;

	/* ग_लिखो firmware's last address (ie. it's length) to
	 * ACX_EEPROMLESS_IND_REG */
	wl1271_debug(DEBUG_BOOT, "ACX_EEPROMLESS_IND_REG");

	ret = wlcore_ग_लिखो32(wl, WL12XX_EEPROMLESS_IND, WL12XX_EEPROMLESS_IND);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_पढ़ो_reg(wl, REG_CHIP_ID_B, &पंचांगp);
	अगर (ret < 0)
		जाओ out;

	wl1271_debug(DEBUG_BOOT, "chip id 0x%x", पंचांगp);

	/* 6. पढ़ो the EEPROM parameters */
	ret = wlcore_पढ़ो32(wl, WL12XX_SCR_PAD2, &पंचांगp);
	अगर (ret < 0)
		जाओ out;

	/* WL1271: The reference driver skips steps 7 to 10 (jumps directly
	 * to upload_fw) */

	अगर (wl->chip.id == CHIP_ID_128X_PG20) अणु
		ret = wl12xx_top_reg_ग_लिखो(wl, SDIO_IO_DS, HCI_IO_DS_6MA);
		अगर (ret < 0)
			जाओ out;
	पूर्ण

	/* polarity must be set beक्रमe the firmware is loaded */
	ret = wl12xx_top_reg_पढ़ो(wl, OCP_REG_POLARITY, &polarity);
	अगर (ret < 0)
		जाओ out;

	/* We use HIGH polarity, so unset the LOW bit */
	polarity &= ~POLARITY_LOW;
	ret = wl12xx_top_reg_ग_लिखो(wl, OCP_REG_POLARITY, polarity);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_enable_पूर्णांकerrupts(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_MASK,
			       WL12XX_ACX_ALL_EVENTS_VECTOR);
	अगर (ret < 0)
		जाओ out;

	wlcore_enable_पूर्णांकerrupts(wl);
	ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_MASK,
			       WL1271_ACX_INTR_ALL & ~(WL12XX_INTR_MASK));
	अगर (ret < 0)
		जाओ disable_पूर्णांकerrupts;

	ret = wlcore_ग_लिखो32(wl, WL12XX_HI_CFG, HI_CFG_DEF_VAL);
	अगर (ret < 0)
		जाओ disable_पूर्णांकerrupts;

	वापस ret;

disable_पूर्णांकerrupts:
	wlcore_disable_पूर्णांकerrupts(wl);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_boot(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wl12xx_pre_boot(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_boot_upload_nvs(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl12xx_pre_upload(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_boot_upload_firmware(wl);
	अगर (ret < 0)
		जाओ out;

	wl->event_mask = BSS_LOSE_EVENT_ID |
		REGAINED_BSS_EVENT_ID |
		SCAN_COMPLETE_EVENT_ID |
		ROLE_STOP_COMPLETE_EVENT_ID |
		RSSI_SNR_TRIGGER_0_EVENT_ID |
		PSPOLL_DELIVERY_FAILURE_EVENT_ID |
		SOFT_GEMINI_SENSE_EVENT_ID |
		PERIODIC_SCAN_REPORT_EVENT_ID |
		PERIODIC_SCAN_COMPLETE_EVENT_ID |
		DUMMY_PACKET_EVENT_ID |
		PEER_REMOVE_COMPLETE_EVENT_ID |
		BA_SESSION_RX_CONSTRAINT_EVENT_ID |
		REMAIN_ON_CHANNEL_COMPLETE_EVENT_ID |
		INACTIVE_STA_EVENT_ID |
		CHANNEL_SWITCH_COMPLETE_EVENT_ID;

	wl->ap_event_mask = MAX_TX_RETRY_EVENT_ID;

	ret = wlcore_boot_run_firmware(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl12xx_enable_पूर्णांकerrupts(wl);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_trigger_cmd(काष्ठा wl1271 *wl, पूर्णांक cmd_box_addr,
			       व्योम *buf, माप_प्रकार len)
अणु
	पूर्णांक ret;

	ret = wlcore_ग_लिखो(wl, cmd_box_addr, buf, len, false);
	अगर (ret < 0)
		वापस ret;

	ret = wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_TRIG, WL12XX_INTR_TRIG_CMD);

	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_ack_event(काष्ठा wl1271 *wl)
अणु
	वापस wlcore_ग_लिखो_reg(wl, REG_INTERRUPT_TRIG,
				WL12XX_INTR_TRIG_EVENT_ACK);
पूर्ण

अटल u32 wl12xx_calc_tx_blocks(काष्ठा wl1271 *wl, u32 len, u32 spare_blks)
अणु
	u32 blk_size = WL12XX_TX_HW_BLOCK_SIZE;
	u32 align_len = wlcore_calc_packet_alignment(wl, len);

	वापस (align_len + blk_size - 1) / blk_size + spare_blks;
पूर्ण

अटल व्योम
wl12xx_set_tx_desc_blocks(काष्ठा wl1271 *wl, काष्ठा wl1271_tx_hw_descr *desc,
			  u32 blks, u32 spare_blks)
अणु
	अगर (wl->chip.id == CHIP_ID_128X_PG20) अणु
		desc->wl128x_mem.total_mem_blocks = blks;
	पूर्ण अन्यथा अणु
		desc->wl127x_mem.extra_blocks = spare_blks;
		desc->wl127x_mem.total_mem_blocks = blks;
	पूर्ण
पूर्ण

अटल व्योम
wl12xx_set_tx_desc_data_len(काष्ठा wl1271 *wl, काष्ठा wl1271_tx_hw_descr *desc,
			    काष्ठा sk_buff *skb)
अणु
	u32 aligned_len = wlcore_calc_packet_alignment(wl, skb->len);

	अगर (wl->chip.id == CHIP_ID_128X_PG20) अणु
		desc->wl128x_mem.extra_bytes = aligned_len - skb->len;
		desc->length = cpu_to_le16(aligned_len >> 2);

		wl1271_debug(DEBUG_TX,
			     "tx_fill_hdr: hlid: %d len: %d life: %d mem: %d extra: %d",
			     desc->hlid,
			     le16_to_cpu(desc->length),
			     le16_to_cpu(desc->lअगरe_समय),
			     desc->wl128x_mem.total_mem_blocks,
			     desc->wl128x_mem.extra_bytes);
	पूर्ण अन्यथा अणु
		/* calculate number of padding bytes */
		पूर्णांक pad = aligned_len - skb->len;
		desc->tx_attr |=
			cpu_to_le16(pad << TX_HW_ATTR_OFST_LAST_WORD_PAD);

		/* Store the aligned length in terms of words */
		desc->length = cpu_to_le16(aligned_len >> 2);

		wl1271_debug(DEBUG_TX,
			     "tx_fill_hdr: pad: %d hlid: %d len: %d life: %d mem: %d",
			     pad, desc->hlid,
			     le16_to_cpu(desc->length),
			     le16_to_cpu(desc->lअगरe_समय),
			     desc->wl127x_mem.total_mem_blocks);
	पूर्ण
पूर्ण

अटल क्रमागत wl_rx_buf_align
wl12xx_get_rx_buf_align(काष्ठा wl1271 *wl, u32 rx_desc)
अणु
	अगर (rx_desc & RX_BUF_UNALIGNED_PAYLOAD)
		वापस WLCORE_RX_BUF_UNALIGNED;

	वापस WLCORE_RX_BUF_ALIGNED;
पूर्ण

अटल u32 wl12xx_get_rx_packet_len(काष्ठा wl1271 *wl, व्योम *rx_data,
				    u32 data_len)
अणु
	काष्ठा wl1271_rx_descriptor *desc = rx_data;

	/* invalid packet */
	अगर (data_len < माप(*desc) ||
	    data_len < माप(*desc) + desc->pad_len)
		वापस 0;

	वापस data_len - माप(*desc) - desc->pad_len;
पूर्ण

अटल पूर्णांक wl12xx_tx_delayed_compl(काष्ठा wl1271 *wl)
अणु
	अगर (wl->fw_status->tx_results_counter ==
	    (wl->tx_results_count & 0xff))
		वापस 0;

	वापस wlcore_tx_complete(wl);
पूर्ण

अटल पूर्णांक wl12xx_hw_init(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	अगर (wl->chip.id == CHIP_ID_128X_PG20) अणु
		u32 host_cfg_biपंचांगap = HOST_IF_CFG_RX_FIFO_ENABLE;

		ret = wl128x_cmd_general_parms(wl);
		अगर (ret < 0)
			जाओ out;

		/*
		 * If we are in calibrator based स्वतः detect then we got the FEM nr
		 * in wl->fem_manuf. No need to जारी further
		 */
		अगर (wl->plt_mode == PLT_FEM_DETECT)
			जाओ out;

		ret = wl128x_cmd_radio_parms(wl);
		अगर (ret < 0)
			जाओ out;

		अगर (wl->quirks & WLCORE_QUIRK_TX_BLOCKSIZE_ALIGN)
			/* Enable SDIO padding */
			host_cfg_biपंचांगap |= HOST_IF_CFG_TX_PAD_TO_SDIO_BLK;

		/* Must be beक्रमe wl1271_acx_init_mem_config() */
		ret = wl1271_acx_host_अगर_cfg_biपंचांगap(wl, host_cfg_biपंचांगap);
		अगर (ret < 0)
			जाओ out;
	पूर्ण अन्यथा अणु
		ret = wl1271_cmd_general_parms(wl);
		अगर (ret < 0)
			जाओ out;

		/*
		 * If we are in calibrator based स्वतः detect then we got the FEM nr
		 * in wl->fem_manuf. No need to जारी further
		 */
		अगर (wl->plt_mode == PLT_FEM_DETECT)
			जाओ out;

		ret = wl1271_cmd_radio_parms(wl);
		अगर (ret < 0)
			जाओ out;
		ret = wl1271_cmd_ext_radio_parms(wl);
		अगर (ret < 0)
			जाओ out;
	पूर्ण
out:
	वापस ret;
पूर्ण

अटल व्योम wl12xx_convert_fw_status(काष्ठा wl1271 *wl, व्योम *raw_fw_status,
				     काष्ठा wl_fw_status *fw_status)
अणु
	काष्ठा wl12xx_fw_status *पूर्णांक_fw_status = raw_fw_status;

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

	fw_status->log_start_addr = le32_to_cpu(पूर्णांक_fw_status->log_start_addr);
पूर्ण

अटल u32 wl12xx_sta_get_ap_rate_mask(काष्ठा wl1271 *wl,
				       काष्ठा wl12xx_vअगर *wlvअगर)
अणु
	वापस wlvअगर->rate_set;
पूर्ण

अटल व्योम wl12xx_conf_init(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_priv *priv = wl->priv;

	/* apply driver शेष configuration */
	स_नकल(&wl->conf, &wl12xx_conf, माप(wl12xx_conf));

	/* apply शेष निजी configuration */
	स_नकल(&priv->conf, &wl12xx_शेष_priv_conf, माप(priv->conf));
पूर्ण

अटल bool wl12xx_mac_in_fuse(काष्ठा wl1271 *wl)
अणु
	bool supported = false;
	u8 major, minor;

	अगर (wl->chip.id == CHIP_ID_128X_PG20) अणु
		major = WL128X_PG_GET_MAJOR(wl->hw_pg_ver);
		minor = WL128X_PG_GET_MINOR(wl->hw_pg_ver);

		/* in wl128x we have the MAC address अगर the PG is >= (2, 1) */
		अगर (major > 2 || (major == 2 && minor >= 1))
			supported = true;
	पूर्ण अन्यथा अणु
		major = WL127X_PG_GET_MAJOR(wl->hw_pg_ver);
		minor = WL127X_PG_GET_MINOR(wl->hw_pg_ver);

		/* in wl127x we have the MAC address अगर the PG is >= (3, 1) */
		अगर (major == 3 && minor >= 1)
			supported = true;
	पूर्ण

	wl1271_debug(DEBUG_PROBE,
		     "PG Ver major = %d minor = %d, MAC %s present",
		     major, minor, supported ? "is" : "is not");

	वापस supported;
पूर्ण

अटल पूर्णांक wl12xx_get_fuse_mac(काष्ठा wl1271 *wl)
अणु
	u32 mac1, mac2;
	पूर्णांक ret;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_DRPW]);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_पढ़ो32(wl, WL12XX_REG_FUSE_BD_ADDR_1, &mac1);
	अगर (ret < 0)
		जाओ out;

	ret = wlcore_पढ़ो32(wl, WL12XX_REG_FUSE_BD_ADDR_2, &mac2);
	अगर (ret < 0)
		जाओ out;

	/* these are the two parts of the BD_ADDR */
	wl->fuse_oui_addr = ((mac2 & 0xffff) << 8) +
		((mac1 & 0xff000000) >> 24);
	wl->fuse_nic_addr = mac1 & 0xffffff;

	ret = wlcore_set_partition(wl, &wl->ptable[PART_DOWN]);

out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_get_pg_ver(काष्ठा wl1271 *wl, s8 *ver)
अणु
	u16 die_info;
	पूर्णांक ret;

	अगर (wl->chip.id == CHIP_ID_128X_PG20)
		ret = wl12xx_top_reg_पढ़ो(wl, WL128X_REG_FUSE_DATA_2_1,
					  &die_info);
	अन्यथा
		ret = wl12xx_top_reg_पढ़ो(wl, WL127X_REG_FUSE_DATA_2_1,
					  &die_info);

	अगर (ret >= 0 && ver)
		*ver = (s8)((die_info & PG_VER_MASK) >> PG_VER_OFFSET);

	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_get_mac(काष्ठा wl1271 *wl)
अणु
	अगर (wl12xx_mac_in_fuse(wl))
		वापस wl12xx_get_fuse_mac(wl);

	वापस 0;
पूर्ण

अटल व्योम wl12xx_set_tx_desc_csum(काष्ठा wl1271 *wl,
				    काष्ठा wl1271_tx_hw_descr *desc,
				    काष्ठा sk_buff *skb)
अणु
	desc->wl12xx_reserved = 0;
पूर्ण

अटल पूर्णांक wl12xx_plt_init(काष्ठा wl1271 *wl)
अणु
	पूर्णांक ret;

	ret = wl->ops->boot(wl);
	अगर (ret < 0)
		जाओ out;

	ret = wl->ops->hw_init(wl);
	अगर (ret < 0)
		जाओ out_irq_disable;

	/*
	 * If we are in calibrator based स्वतः detect then we got the FEM nr
	 * in wl->fem_manuf. No need to जारी further
	 */
	अगर (wl->plt_mode == PLT_FEM_DETECT)
		जाओ out;

	ret = wl1271_acx_init_mem_config(wl);
	अगर (ret < 0)
		जाओ out_irq_disable;

	ret = wl12xx_acx_mem_cfg(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* Enable data path */
	ret = wl1271_cmd_data_path(wl, 1);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* Configure क्रम CAM घातer saving (ie. always active) */
	ret = wl1271_acx_sleep_auth(wl, WL1271_PSM_CAM);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	/* configure PM */
	ret = wl1271_acx_pm_config(wl);
	अगर (ret < 0)
		जाओ out_मुक्त_memmap;

	जाओ out;

out_मुक्त_memmap:
	kमुक्त(wl->target_mem_map);
	wl->target_mem_map = शून्य;

out_irq_disable:
	mutex_unlock(&wl->mutex);
	/* Unlocking the mutex in the middle of handling is
	   inherently unsafe. In this हाल we deem it safe to करो,
	   because we need to let any possibly pending IRQ out of
	   the प्रणाली (and जबतक we are WL1271_STATE_OFF the IRQ
	   work function will not करो anything.) Also, any other
	   possible concurrent operations will fail due to the
	   current state, hence the wl1271 काष्ठा should be safe. */
	wlcore_disable_पूर्णांकerrupts(wl);
	mutex_lock(&wl->mutex);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_get_spare_blocks(काष्ठा wl1271 *wl, bool is_gem)
अणु
	अगर (is_gem)
		वापस WL12XX_TX_HW_BLOCK_GEM_SPARE;

	वापस WL12XX_TX_HW_BLOCK_SPARE_DEFAULT;
पूर्ण

अटल पूर्णांक wl12xx_set_key(काष्ठा wl1271 *wl, क्रमागत set_key_cmd cmd,
			  काष्ठा ieee80211_vअगर *vअगर,
			  काष्ठा ieee80211_sta *sta,
			  काष्ठा ieee80211_key_conf *key_conf)
अणु
	वापस wlcore_set_key(wl, cmd, vअगर, sta, key_conf);
पूर्ण

अटल पूर्णांक wl12xx_set_peer_cap(काष्ठा wl1271 *wl,
			       काष्ठा ieee80211_sta_ht_cap *ht_cap,
			       bool allow_ht_operation,
			       u32 rate_set, u8 hlid)
अणु
	वापस wl1271_acx_set_ht_capabilities(wl, ht_cap, allow_ht_operation,
					      hlid);
पूर्ण

अटल bool wl12xx_lnk_high_prio(काष्ठा wl1271 *wl, u8 hlid,
				 काष्ठा wl1271_link *lnk)
अणु
	u8 thold;

	अगर (test_bit(hlid, &wl->fw_fast_lnk_map))
		thold = wl->conf.tx.fast_link_thold;
	अन्यथा
		thold = wl->conf.tx.slow_link_thold;

	वापस lnk->allocated_pkts < thold;
पूर्ण

अटल bool wl12xx_lnk_low_prio(काष्ठा wl1271 *wl, u8 hlid,
				काष्ठा wl1271_link *lnk)
अणु
	/* any link is good क्रम low priority */
	वापस true;
पूर्ण

अटल u32 wl12xx_convert_hwaddr(काष्ठा wl1271 *wl, u32 hwaddr)
अणु
	वापस hwaddr << 5;
पूर्ण

अटल पूर्णांक wl12xx_setup(काष्ठा wl1271 *wl);

अटल काष्ठा wlcore_ops wl12xx_ops = अणु
	.setup			= wl12xx_setup,
	.identअगरy_chip		= wl12xx_identअगरy_chip,
	.boot			= wl12xx_boot,
	.plt_init		= wl12xx_plt_init,
	.trigger_cmd		= wl12xx_trigger_cmd,
	.ack_event		= wl12xx_ack_event,
	.रुको_क्रम_event		= wl12xx_रुको_क्रम_event,
	.process_mailbox_events	= wl12xx_process_mailbox_events,
	.calc_tx_blocks		= wl12xx_calc_tx_blocks,
	.set_tx_desc_blocks	= wl12xx_set_tx_desc_blocks,
	.set_tx_desc_data_len	= wl12xx_set_tx_desc_data_len,
	.get_rx_buf_align	= wl12xx_get_rx_buf_align,
	.get_rx_packet_len	= wl12xx_get_rx_packet_len,
	.tx_immediate_compl	= शून्य,
	.tx_delayed_compl	= wl12xx_tx_delayed_compl,
	.hw_init		= wl12xx_hw_init,
	.init_vअगर		= शून्य,
	.convert_fw_status	= wl12xx_convert_fw_status,
	.sta_get_ap_rate_mask	= wl12xx_sta_get_ap_rate_mask,
	.get_pg_ver		= wl12xx_get_pg_ver,
	.get_mac		= wl12xx_get_mac,
	.set_tx_desc_csum	= wl12xx_set_tx_desc_csum,
	.set_rx_csum		= शून्य,
	.ap_get_mimo_wide_rate_mask = शून्य,
	.debugfs_init		= wl12xx_debugfs_add_files,
	.scan_start		= wl12xx_scan_start,
	.scan_stop		= wl12xx_scan_stop,
	.sched_scan_start	= wl12xx_sched_scan_start,
	.sched_scan_stop	= wl12xx_scan_sched_scan_stop,
	.get_spare_blocks	= wl12xx_get_spare_blocks,
	.set_key		= wl12xx_set_key,
	.channel_चयन		= wl12xx_cmd_channel_चयन,
	.pre_pkt_send		= शून्य,
	.set_peer_cap		= wl12xx_set_peer_cap,
	.convert_hwaddr		= wl12xx_convert_hwaddr,
	.lnk_high_prio		= wl12xx_lnk_high_prio,
	.lnk_low_prio		= wl12xx_lnk_low_prio,
	.पूर्णांकerrupt_notअगरy	= शून्य,
	.rx_ba_filter		= शून्य,
	.ap_sleep		= शून्य,
पूर्ण;

अटल काष्ठा ieee80211_sta_ht_cap wl12xx_ht_cap = अणु
	.cap = IEEE80211_HT_CAP_GRN_FLD | IEEE80211_HT_CAP_SGI_20 |
	       (1 << IEEE80211_HT_CAP_RX_STBC_SHIFT),
	.ht_supported = true,
	.ampdu_factor = IEEE80211_HT_MAX_AMPDU_8K,
	.ampdu_density = IEEE80211_HT_MPDU_DENSITY_8,
	.mcs = अणु
		.rx_mask = अणु 0xff, 0, 0, 0, 0, 0, 0, 0, 0, 0, पूर्ण,
		.rx_highest = cpu_to_le16(72),
		.tx_params = IEEE80211_HT_MCS_TX_DEFINED,
		पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_limit wl12xx_अगरace_limits[] = अणु
	अणु
		.max = 3,
		.types = BIT(NL80211_IFTYPE_STATION),
	पूर्ण,
	अणु
		.max = 1,
		.types = BIT(NL80211_IFTYPE_AP) |
			 BIT(NL80211_IFTYPE_P2P_GO) |
			 BIT(NL80211_IFTYPE_P2P_CLIENT),
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा ieee80211_अगरace_combination
wl12xx_अगरace_combinations[] = अणु
	अणु
		.max_पूर्णांकerfaces = 3,
		.limits = wl12xx_अगरace_limits,
		.n_limits = ARRAY_SIZE(wl12xx_अगरace_limits),
		.num_dअगरferent_channels = 1,
	पूर्ण,
पूर्ण;

अटल स्थिर काष्ठा wl12xx_घड़ी wl12xx_refघड़ी_प्रकारable[] = अणु
	अणु 19200000,	false,	WL12XX_REFCLOCK_19	पूर्ण,
	अणु 26000000,	false,	WL12XX_REFCLOCK_26	पूर्ण,
	अणु 26000000,	true,	WL12XX_REFCLOCK_26_XTAL	पूर्ण,
	अणु 38400000,	false,	WL12XX_REFCLOCK_38	पूर्ण,
	अणु 38400000,	true,	WL12XX_REFCLOCK_38_XTAL	पूर्ण,
	अणु 52000000,	false,	WL12XX_REFCLOCK_52	पूर्ण,
	अणु 0,		false,	0 पूर्ण
पूर्ण;

अटल स्थिर काष्ठा wl12xx_घड़ी wl12xx_tcxoघड़ी_प्रकारable[] = अणु
	अणु 16368000,	true,	WL12XX_TCXOCLOCK_16_368	पूर्ण,
	अणु 16800000,	true,	WL12XX_TCXOCLOCK_16_8	पूर्ण,
	अणु 19200000,	true,	WL12XX_TCXOCLOCK_19_2	पूर्ण,
	अणु 26000000,	true,	WL12XX_TCXOCLOCK_26	पूर्ण,
	अणु 32736000,	true,	WL12XX_TCXOCLOCK_32_736	पूर्ण,
	अणु 33600000,	true,	WL12XX_TCXOCLOCK_33_6	पूर्ण,
	अणु 38400000,	true,	WL12XX_TCXOCLOCK_38_4	पूर्ण,
	अणु 52000000,	true,	WL12XX_TCXOCLOCK_52	पूर्ण,
	अणु 0,		false,	0 पूर्ण
पूर्ण;

अटल पूर्णांक wl12xx_get_घड़ी_idx(स्थिर काष्ठा wl12xx_घड़ी *table,
				u32 freq, bool xtal)
अणु
	पूर्णांक i;

	क्रम (i = 0; table[i].freq != 0; i++)
		अगर ((table[i].freq == freq) && (table[i].xtal == xtal))
			वापस table[i].hw_idx;

	वापस -EINVAL;
पूर्ण

अटल पूर्णांक wl12xx_setup(काष्ठा wl1271 *wl)
अणु
	काष्ठा wl12xx_priv *priv = wl->priv;
	काष्ठा wlcore_platdev_data *pdev_data = dev_get_platdata(&wl->pdev->dev);

	BUILD_BUG_ON(WL12XX_MAX_LINKS > WLCORE_MAX_LINKS);
	BUILD_BUG_ON(WL12XX_MAX_AP_STATIONS > WL12XX_MAX_LINKS);
	BUILD_BUG_ON(WL12XX_CONF_SG_PARAMS_MAX > WLCORE_CONF_SG_PARAMS_MAX);

	wl->rtable = wl12xx_rtable;
	wl->num_tx_desc = WL12XX_NUM_TX_DESCRIPTORS;
	wl->num_rx_desc = WL12XX_NUM_RX_DESCRIPTORS;
	wl->num_links = WL12XX_MAX_LINKS;
	wl->max_ap_stations = WL12XX_MAX_AP_STATIONS;
	wl->अगरace_combinations = wl12xx_अगरace_combinations;
	wl->n_अगरace_combinations = ARRAY_SIZE(wl12xx_अगरace_combinations);
	wl->num_mac_addr = WL12XX_NUM_MAC_ADDRESSES;
	wl->band_rate_to_idx = wl12xx_band_rate_to_idx;
	wl->hw_tx_rate_tbl_size = WL12XX_CONF_HW_RXTX_RATE_MAX;
	wl->hw_min_ht_rate = WL12XX_CONF_HW_RXTX_RATE_MCS0;
	wl->fw_status_len = माप(काष्ठा wl12xx_fw_status);
	wl->fw_status_priv_len = 0;
	wl->stats.fw_stats_len = माप(काष्ठा wl12xx_acx_statistics);
	wl->ofdm_only_ap = true;
	wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ, &wl12xx_ht_cap);
	wlcore_set_ht_cap(wl, NL80211_BAND_5GHZ, &wl12xx_ht_cap);
	wl12xx_conf_init(wl);

	अगर (!fref_param) अणु
		priv->ref_घड़ी = wl12xx_get_घड़ी_idx(wl12xx_refघड़ी_प्रकारable,
						pdev_data->ref_घड़ी_freq,
						pdev_data->ref_घड़ी_xtal);
		अगर (priv->ref_घड़ी < 0) अणु
			wl1271_error("Invalid ref_clock frequency (%d Hz, %s)",
				     pdev_data->ref_घड़ी_freq,
				     pdev_data->ref_घड़ी_xtal ?
				     "XTAL" : "not XTAL");

			वापस priv->ref_घड़ी;
		पूर्ण
	पूर्ण अन्यथा अणु
		अगर (!म_भेद(fref_param, "19.2"))
			priv->ref_घड़ी = WL12XX_REFCLOCK_19;
		अन्यथा अगर (!म_भेद(fref_param, "26"))
			priv->ref_घड़ी = WL12XX_REFCLOCK_26;
		अन्यथा अगर (!म_भेद(fref_param, "26x"))
			priv->ref_घड़ी = WL12XX_REFCLOCK_26_XTAL;
		अन्यथा अगर (!म_भेद(fref_param, "38.4"))
			priv->ref_घड़ी = WL12XX_REFCLOCK_38;
		अन्यथा अगर (!म_भेद(fref_param, "38.4x"))
			priv->ref_घड़ी = WL12XX_REFCLOCK_38_XTAL;
		अन्यथा अगर (!म_भेद(fref_param, "52"))
			priv->ref_घड़ी = WL12XX_REFCLOCK_52;
		अन्यथा
			wl1271_error("Invalid fref parameter %s", fref_param);
	पूर्ण

	अगर (!tcxo_param && pdev_data->tcxo_घड़ी_freq) अणु
		priv->tcxo_घड़ी = wl12xx_get_घड़ी_idx(wl12xx_tcxoघड़ी_प्रकारable,
						pdev_data->tcxo_घड़ी_freq,
						true);
		अगर (priv->tcxo_घड़ी < 0) अणु
			wl1271_error("Invalid tcxo_clock frequency (%d Hz)",
				     pdev_data->tcxo_घड़ी_freq);

			वापस priv->tcxo_घड़ी;
		पूर्ण
	पूर्ण अन्यथा अगर (tcxo_param) अणु
		अगर (!म_भेद(tcxo_param, "19.2"))
			priv->tcxo_घड़ी = WL12XX_TCXOCLOCK_19_2;
		अन्यथा अगर (!म_भेद(tcxo_param, "26"))
			priv->tcxo_घड़ी = WL12XX_TCXOCLOCK_26;
		अन्यथा अगर (!म_भेद(tcxo_param, "38.4"))
			priv->tcxo_घड़ी = WL12XX_TCXOCLOCK_38_4;
		अन्यथा अगर (!म_भेद(tcxo_param, "52"))
			priv->tcxo_घड़ी = WL12XX_TCXOCLOCK_52;
		अन्यथा अगर (!म_भेद(tcxo_param, "16.368"))
			priv->tcxo_घड़ी = WL12XX_TCXOCLOCK_16_368;
		अन्यथा अगर (!म_भेद(tcxo_param, "32.736"))
			priv->tcxo_घड़ी = WL12XX_TCXOCLOCK_32_736;
		अन्यथा अगर (!म_भेद(tcxo_param, "16.8"))
			priv->tcxo_घड़ी = WL12XX_TCXOCLOCK_16_8;
		अन्यथा अगर (!म_भेद(tcxo_param, "33.6"))
			priv->tcxo_घड़ी = WL12XX_TCXOCLOCK_33_6;
		अन्यथा
			wl1271_error("Invalid tcxo parameter %s", tcxo_param);
	पूर्ण

	priv->rx_mem_addr = kदो_स्मृति(माप(*priv->rx_mem_addr), GFP_KERNEL);
	अगर (!priv->rx_mem_addr)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल पूर्णांक wl12xx_probe(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wl1271 *wl;
	काष्ठा ieee80211_hw *hw;
	पूर्णांक ret;

	hw = wlcore_alloc_hw(माप(काष्ठा wl12xx_priv),
			     WL12XX_AGGR_BUFFER_SIZE,
			     माप(काष्ठा wl12xx_event_mailbox));
	अगर (IS_ERR(hw)) अणु
		wl1271_error("can't allocate hw");
		ret = PTR_ERR(hw);
		जाओ out;
	पूर्ण

	wl = hw->priv;
	wl->ops = &wl12xx_ops;
	wl->ptable = wl12xx_ptable;
	ret = wlcore_probe(wl, pdev);
	अगर (ret)
		जाओ out_मुक्त;

	वापस ret;

out_मुक्त:
	wlcore_मुक्त_hw(wl);
out:
	वापस ret;
पूर्ण

अटल पूर्णांक wl12xx_हटाओ(काष्ठा platक्रमm_device *pdev)
अणु
	काष्ठा wl1271 *wl = platक्रमm_get_drvdata(pdev);
	काष्ठा wl12xx_priv *priv;

	अगर (!wl)
		जाओ out;
	priv = wl->priv;

	kमुक्त(priv->rx_mem_addr);

out:
	वापस wlcore_हटाओ(pdev);
पूर्ण

अटल स्थिर काष्ठा platक्रमm_device_id wl12xx_id_table[] = अणु
	अणु "wl12xx", 0 पूर्ण,
	अणु  पूर्ण /* Terminating Entry */
पूर्ण;
MODULE_DEVICE_TABLE(platक्रमm, wl12xx_id_table);

अटल काष्ठा platक्रमm_driver wl12xx_driver = अणु
	.probe		= wl12xx_probe,
	.हटाओ		= wl12xx_हटाओ,
	.id_table	= wl12xx_id_table,
	.driver = अणु
		.name	= "wl12xx_driver",
	पूर्ण
पूर्ण;

module_platक्रमm_driver(wl12xx_driver);

module_param_named(fref, fref_param, अक्षरp, 0);
MODULE_PARM_DESC(fref, "FREF clock: 19.2, 26, 26x, 38.4, 38.4x, 52");

module_param_named(tcxo, tcxo_param, अक्षरp, 0);
MODULE_PARM_DESC(tcxo,
		 "TCXO clock: 19.2, 26, 38.4, 52, 16.368, 32.736, 16.8, 33.6");

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("Luciano Coelho <coelho@ti.com>");
MODULE_FIRMWARE(WL127X_FW_NAME_SINGLE);
MODULE_FIRMWARE(WL127X_FW_NAME_MULTI);
MODULE_FIRMWARE(WL127X_PLT_FW_NAME);
MODULE_FIRMWARE(WL128X_FW_NAME_SINGLE);
MODULE_FIRMWARE(WL128X_FW_NAME_MULTI);
MODULE_FIRMWARE(WL128X_PLT_FW_NAME);
