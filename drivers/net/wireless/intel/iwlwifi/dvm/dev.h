<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/******************************************************************************
 *
 * Copyright(c) 2003 - 2014, 2020 Intel Corporation. All rights reserved.
 *
 * Contact Inक्रमmation:
 *  Intel Linux Wireless <linuxwअगरi@पूर्णांकel.com>
 * Intel Corporation, 5200 N.E. Elam Young Parkway, Hillsboro, OR 97124-6497
 *
 *****************************************************************************/
/*
 * Please use this file (dev.h) क्रम driver implementation definitions.
 * Please use commands.h क्रम uCode API definitions.
 */

#अगर_अघोषित __iwl_dev_h__
#घोषणा __iwl_dev_h__

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/kernel.h>
#समावेश <linux/रुको.h>
#समावेश <linux/leds.h>
#समावेश <linux/slab.h>
#समावेश <linux/mutex.h>

#समावेश "fw/img.h"
#समावेश "iwl-eeprom-parse.h"
#समावेश "iwl-csr.h"
#समावेश "iwl-debug.h"
#समावेश "iwl-agn-hw.h"
#समावेश "iwl-op-mode.h"
#समावेश "fw/notif-wait.h"
#समावेश "iwl-trans.h"

#समावेश "led.h"
#समावेश "power.h"
#समावेश "rs.h"
#समावेश "tt.h"

/* CT-KILL स्थिरants */
#घोषणा CT_KILL_THRESHOLD_LEGACY   110 /* in Celsius */
#घोषणा CT_KILL_THRESHOLD	   114 /* in Celsius */
#घोषणा CT_KILL_EXIT_THRESHOLD     95  /* in Celsius */

/* Default noise level to report when noise measurement is not available.
 *   This may be because we're:
 *   1)  Not associated  no beacon statistics being sent to driver)
 *   2)  Scanning (noise measurement करोes not apply to associated channel)
 * Use शेष noise value of -127 ... this is below the range of measurable
 *   Rx dBm क्रम all agn devices, so it can indicate "unmeasurable" to user.
 *   Also, -127 works better than 0 when averaging frames with/without
 *   noise info (e.g. averaging might be करोne in app); measured dBm values are
 *   always negative ... using a negative value as the शेष keeps all
 *   averages within an s8's (used in some apps) range of negative values. */
#घोषणा IWL_NOISE_MEAS_NOT_AVAILABLE (-127)

/*
 * RTS threshold here is total size [2347] minus 4 FCS bytes
 * Per spec:
 *   a value of 0 means RTS on all data/management packets
 *   a value > max MSDU size means no RTS
 * अन्यथा RTS क्रम data/management frames where MPDU is larger
 *   than RTS value.
 */
#घोषणा DEFAULT_RTS_THRESHOLD     2347U
#घोषणा MIN_RTS_THRESHOLD         0U
#घोषणा MAX_RTS_THRESHOLD         2347U
#घोषणा MAX_MSDU_SIZE		  2304U
#घोषणा MAX_MPDU_SIZE		  2346U
#घोषणा DEFAULT_BEACON_INTERVAL   200U
#घोषणा	DEFAULT_SHORT_RETRY_LIMIT 7U
#घोषणा	DEFAULT_LONG_RETRY_LIMIT  4U

#घोषणा IWL_NUM_SCAN_RATES         (2)


#घोषणा IEEE80211_DATA_LEN              2304
#घोषणा IEEE80211_4ADDR_LEN             30
#घोषणा IEEE80211_HLEN                  (IEEE80211_4ADDR_LEN)
#घोषणा IEEE80211_FRAME_LEN             (IEEE80211_DATA_LEN + IEEE80211_HLEN)

#घोषणा SUP_RATE_11A_MAX_NUM_CHANNELS  8
#घोषणा SUP_RATE_11B_MAX_NUM_CHANNELS  4
#घोषणा SUP_RATE_11G_MAX_NUM_CHANNELS  12

#घोषणा IWL_SUPPORTED_RATES_IE_LEN         8

#घोषणा IWL_INVALID_RATE     0xFF
#घोषणा IWL_INVALID_VALUE    -1

जोड़ iwl_ht_rate_supp अणु
	u16 rates;
	काष्ठा अणु
		u8 siso_rate;
		u8 mimo_rate;
	पूर्ण;
पूर्ण;

काष्ठा iwl_ht_config अणु
	bool single_chain_sufficient;
	क्रमागत ieee80211_smps_mode smps; /* current smps mode */
पूर्ण;

/* QoS काष्ठाures */
काष्ठा iwl_qos_info अणु
	पूर्णांक qos_active;
	काष्ठा iwl_qosparam_cmd def_qos_parm;
पूर्ण;

/**
 * क्रमागत iwl_agg_state
 *
 * The state machine of the BA agreement establishment / tear करोwn.
 * These states relate to a specअगरic RA / TID.
 *
 * @IWL_AGG_OFF: aggregation is not used
 * @IWL_AGG_STARTING: aggregation are starting (between start and oper)
 * @IWL_AGG_ON: aggregation session is up
 * @IWL_EMPTYING_HW_QUEUE_ADDBA: establishing a BA session - रुकोing क्रम the
 *	HW queue to be empty from packets क्रम this RA /TID.
 * @IWL_EMPTYING_HW_QUEUE_DELBA: tearing करोwn a BA session - रुकोing क्रम the
 *	HW queue to be empty from packets क्रम this RA /TID.
 */
क्रमागत iwl_agg_state अणु
	IWL_AGG_OFF = 0,
	IWL_AGG_STARTING,
	IWL_AGG_ON,
	IWL_EMPTYING_HW_QUEUE_ADDBA,
	IWL_EMPTYING_HW_QUEUE_DELBA,
पूर्ण;

/**
 * काष्ठा iwl_ht_agg - aggregation state machine

 * This काष्ठाs holds the states क्रम the BA agreement establishment and tear
 * करोwn. It also holds the state during the BA session itself. This काष्ठा is
 * duplicated क्रम each RA / TID.

 * @rate_n_flags: Rate at which Tx was attempted. Holds the data between the
 *	Tx response (REPLY_TX), and the block ack notअगरication
 *	(REPLY_COMPRESSED_BA).
 * @state: state of the BA agreement establishment / tear करोwn.
 * @txq_id: Tx queue used by the BA session
 * @ssn: the first packet to be sent in AGG HW queue in Tx AGG start flow, or
 *	the first packet to be sent in legacy HW queue in Tx AGG stop flow.
 *	Basically when next_reclaimed reaches ssn, we can tell mac80211 that
 *	we are पढ़ोy to finish the Tx AGG stop / start flow.
 * @रुको_क्रम_ba: Expect block-ack beक्रमe next Tx reply
 */
काष्ठा iwl_ht_agg अणु
	u32 rate_n_flags;
	क्रमागत iwl_agg_state state;
	u16 txq_id;
	u16 ssn;
	bool रुको_क्रम_ba;
पूर्ण;

/**
 * काष्ठा iwl_tid_data - one क्रम each RA / TID

 * This काष्ठाs holds the states क्रम each RA / TID.

 * @seq_number: the next WiFi sequence number to use
 * @next_reclaimed: the WiFi sequence number of the next packet to be acked.
 *	This is basically (last acked packet++).
 * @agg: aggregation state machine
 */
काष्ठा iwl_tid_data अणु
	u16 seq_number;
	u16 next_reclaimed;
	काष्ठा iwl_ht_agg agg;
पूर्ण;

/*
 * Structure should be accessed with sta_lock held. When station addition
 * is in progress (IWL_STA_UCODE_INPROGRESS) it is possible to access only
 * the commands (iwl_addsta_cmd and iwl_link_quality_cmd) without sta_lock
 * held.
 */
काष्ठा iwl_station_entry अणु
	काष्ठा iwl_addsta_cmd sta;
	u8 used, ctxid;
	काष्ठा iwl_link_quality_cmd *lq;
पूर्ण;

/*
 * iwl_station_priv: Driver's निजी station inक्रमmation
 *
 * When mac80211 creates a station it reserves some space (hw->sta_data_size)
 * in the काष्ठाure क्रम use by driver. This काष्ठाure is places in that
 * space.
 */
काष्ठा iwl_station_priv अणु
	काष्ठा iwl_rxon_context *ctx;
	काष्ठा iwl_lq_sta lq_sta;
	atomic_t pending_frames;
	bool client;
	bool asleep;
	u8 max_agg_bufsize;
	u8 sta_id;
पूर्ण;

/**
 * काष्ठा iwl_vअगर_priv - driver's निजी per-पूर्णांकerface inक्रमmation
 *
 * When mac80211 allocates a भव पूर्णांकerface, it can allocate
 * space क्रम us to put data पूर्णांकo.
 */
काष्ठा iwl_vअगर_priv अणु
	काष्ठा iwl_rxon_context *ctx;
	u8 ibss_bssid_sta_id;
पूर्ण;

काष्ठा iwl_sensitivity_ranges अणु
	u16 min_nrg_cck;

	u16 nrg_th_cck;
	u16 nrg_th_ofdm;

	u16 स्वतः_corr_min_ofdm;
	u16 स्वतः_corr_min_ofdm_mrc;
	u16 स्वतः_corr_min_ofdm_x1;
	u16 स्वतः_corr_min_ofdm_mrc_x1;

	u16 स्वतः_corr_max_ofdm;
	u16 स्वतः_corr_max_ofdm_mrc;
	u16 स्वतः_corr_max_ofdm_x1;
	u16 स्वतः_corr_max_ofdm_mrc_x1;

	u16 स्वतः_corr_max_cck;
	u16 स्वतः_corr_max_cck_mrc;
	u16 स्वतः_corr_min_cck;
	u16 स्वतः_corr_min_cck_mrc;

	u16 barker_corr_th_min;
	u16 barker_corr_th_min_mrc;
	u16 nrg_th_cca;
पूर्ण;

/******************************************************************************
 *
 * Functions implemented in core module which are क्रमward declared here
 * क्रम use by iwl-[4-5].c
 *
 * NOTE:  The implementation of these functions are not hardware specअगरic
 * which is why they are in the core module files.
 *
 * Naming convention --
 * iwl_         <-- Is part of iwlwअगरi
 * iwlXXXX_     <-- Hardware specअगरic (implemented in iwl-XXXX.c क्रम XXXX)
 *
 ****************************************************************************/
व्योम iwl_update_chain_flags(काष्ठा iwl_priv *priv);
बाह्य स्थिर u8 iwl_bcast_addr[ETH_ALEN];

#घोषणा IWL_OPERATION_MODE_AUTO     0
#घोषणा IWL_OPERATION_MODE_HT_ONLY  1
#घोषणा IWL_OPERATION_MODE_MIXED    2
#घोषणा IWL_OPERATION_MODE_20MHZ    3

#घोषणा TX_POWER_IWL_ILLEGAL_VOLTAGE -10000

/* Sensitivity and chain noise calibration */
#घोषणा INITIALIZATION_VALUE		0xFFFF
#घोषणा IWL_CAL_NUM_BEACONS		16
#घोषणा MAXIMUM_ALLOWED_PATHLOSS	15

#घोषणा CHAIN_NOISE_MAX_DELTA_GAIN_CODE 3

#घोषणा MAX_FA_OFDM  50
#घोषणा MIN_FA_OFDM  5
#घोषणा MAX_FA_CCK   50
#घोषणा MIN_FA_CCK   5

#घोषणा AUTO_CORR_STEP_OFDM       1

#घोषणा AUTO_CORR_STEP_CCK     3
#घोषणा AUTO_CORR_MAX_TH_CCK   160

#घोषणा NRG_DIFF               2
#घोषणा NRG_STEP_CCK           2
#घोषणा NRG_MARGIN             8
#घोषणा MAX_NUMBER_CCK_NO_FA 100

#घोषणा AUTO_CORR_CCK_MIN_VAL_DEF    (125)

#घोषणा CHAIN_A             0
#घोषणा CHAIN_B             1
#घोषणा CHAIN_C             2
#घोषणा CHAIN_NOISE_DELTA_GAIN_INIT_VAL 4
#घोषणा ALL_BAND_FILTER			0xFF00
#घोषणा IN_BAND_FILTER			0xFF
#घोषणा MIN_AVERAGE_NOISE_MAX_VALUE	0xFFFFFFFF

#घोषणा NRG_NUM_PREV_STAT_L     20
#घोषणा NUM_RX_CHAINS           3

क्रमागत iwlagn_false_alarm_state अणु
	IWL_FA_TOO_MANY = 0,
	IWL_FA_TOO_FEW = 1,
	IWL_FA_GOOD_RANGE = 2,
पूर्ण;

क्रमागत iwlagn_chain_noise_state अणु
	IWL_CHAIN_NOISE_ALIVE = 0,  /* must be 0 */
	IWL_CHAIN_NOISE_ACCUMULATE,
	IWL_CHAIN_NOISE_CALIBRATED,
	IWL_CHAIN_NOISE_DONE,
पूर्ण;

/* Sensitivity calib data */
काष्ठा iwl_sensitivity_data अणु
	u32 स्वतः_corr_ofdm;
	u32 स्वतः_corr_ofdm_mrc;
	u32 स्वतः_corr_ofdm_x1;
	u32 स्वतः_corr_ofdm_mrc_x1;
	u32 स्वतः_corr_cck;
	u32 स्वतः_corr_cck_mrc;

	u32 last_bad_plcp_cnt_ofdm;
	u32 last_fa_cnt_ofdm;
	u32 last_bad_plcp_cnt_cck;
	u32 last_fa_cnt_cck;

	u32 nrg_curr_state;
	u32 nrg_prev_state;
	u32 nrg_value[10];
	u8  nrg_silence_rssi[NRG_NUM_PREV_STAT_L];
	u32 nrg_silence_ref;
	u32 nrg_energy_idx;
	u32 nrg_silence_idx;
	u32 nrg_th_cck;
	s32 nrg_स्वतः_corr_silence_dअगरf;
	u32 num_in_cck_no_fa;
	u32 nrg_th_ofdm;

	u16 barker_corr_th_min;
	u16 barker_corr_th_min_mrc;
	u16 nrg_th_cca;
पूर्ण;

/* Chain noise (dअगरferential Rx gain) calib data */
काष्ठा iwl_chain_noise_data अणु
	u32 active_chains;
	u32 chain_noise_a;
	u32 chain_noise_b;
	u32 chain_noise_c;
	u32 chain_संकेत_a;
	u32 chain_संकेत_b;
	u32 chain_संकेत_c;
	u16 beacon_count;
	u8 disconn_array[NUM_RX_CHAINS];
	u8 delta_gain_code[NUM_RX_CHAINS];
	u8 radio_ग_लिखो;
	u8 state;
पूर्ण;

क्रमागत अणु
	MEASUREMENT_READY = (1 << 0),
	MEASUREMENT_ACTIVE = (1 << 1),
पूर्ण;

/* reply_tx_statistics (क्रम _agn devices) */
काष्ठा reply_tx_error_statistics अणु
	u32 pp_delay;
	u32 pp_few_bytes;
	u32 pp_bt_prio;
	u32 pp_quiet_period;
	u32 pp_calc_ttak;
	u32 पूर्णांक_crossed_retry;
	u32 लघु_limit;
	u32 दीर्घ_limit;
	u32 fअगरo_underrun;
	u32 drain_flow;
	u32 rfसमाप्त_flush;
	u32 lअगरe_expire;
	u32 dest_ps;
	u32 host_पात;
	u32 bt_retry;
	u32 sta_invalid;
	u32 frag_drop;
	u32 tid_disable;
	u32 fअगरo_flush;
	u32 insuff_cf_poll;
	u32 fail_hw_drop;
	u32 sta_color_mismatch;
	u32 unknown;
पूर्ण;

/* reply_agg_tx_statistics (क्रम _agn devices) */
काष्ठा reply_agg_tx_error_statistics अणु
	u32 underrun;
	u32 bt_prio;
	u32 few_bytes;
	u32 पात;
	u32 last_sent_ttl;
	u32 last_sent_try;
	u32 last_sent_bt_समाप्त;
	u32 scd_query;
	u32 bad_crc32;
	u32 response;
	u32 dump_tx;
	u32 delay_tx;
	u32 unknown;
पूर्ण;

/*
 * schedule the समयr to wake up every UCODE_TRACE_PERIOD milliseconds
 * to perक्रमm continuous uCode event logging operation अगर enabled
 */
#घोषणा UCODE_TRACE_PERIOD (10)

/*
 * iwl_event_log: current uCode event log position
 *
 * @ucode_trace: enable/disable ucode continuous trace समयr
 * @num_wraps: how many बार the event buffer wraps
 * @next_entry:  the entry just beक्रमe the next one that uCode would fill
 * @non_wraps_count: counter क्रम no wrap detected when dump ucode events
 * @wraps_once_count: counter क्रम wrap once detected when dump ucode events
 * @wraps_more_count: counter क्रम wrap more than once detected
 *		      when dump ucode events
 */
काष्ठा iwl_event_log अणु
	bool ucode_trace;
	u32 num_wraps;
	u32 next_entry;
	पूर्णांक non_wraps_count;
	पूर्णांक wraps_once_count;
	पूर्णांक wraps_more_count;
पूर्ण;

#घोषणा IWL_DELAY_NEXT_FORCE_RF_RESET  (HZ*3)

/* BT Antenna Coupling Threshold (dB) */
#घोषणा IWL_BT_ANTENNA_COUPLING_THRESHOLD	(35)

/* Firmware reload counter and Timestamp */
#घोषणा IWL_MIN_RELOAD_DURATION		1000 /* 1000 ms */
#घोषणा IWL_MAX_CONTINUE_RELOAD_CNT	4


काष्ठा iwl_rf_reset अणु
	पूर्णांक reset_request_count;
	पूर्णांक reset_success_count;
	पूर्णांक reset_reject_count;
	अचिन्हित दीर्घ last_reset_jअगरfies;
पूर्ण;

क्रमागत iwl_rxon_context_id अणु
	IWL_RXON_CTX_BSS,
	IWL_RXON_CTX_PAN,

	NUM_IWL_RXON_CTX
पूर्ण;

/* extend beacon समय क्रमmat bit shअगरting  */
/*
 * क्रम _agn devices
 * bits 31:22 - extended
 * bits 21:0  - पूर्णांकerval
 */
#घोषणा IWLAGN_EXT_BEACON_TIME_POS	22

काष्ठा iwl_rxon_context अणु
	काष्ठा ieee80211_vअगर *vअगर;

	u8 mcast_queue;
	u8 ac_to_queue[IEEE80211_NUM_ACS];
	u8 ac_to_fअगरo[IEEE80211_NUM_ACS];

	/*
	 * We could use the vअगर to indicate active, but we
	 * also need it to be active during disabling when
	 * we alपढ़ोy हटाओd the vअगर क्रम type setting.
	 */
	bool always_active, is_active;

	bool ht_need_multiple_chains;

	क्रमागत iwl_rxon_context_id ctxid;

	u32 पूर्णांकerface_modes, exclusive_पूर्णांकerface_modes;
	u8 unused_devtype, ap_devtype, ibss_devtype, station_devtype;

	/*
	 * We declare this स्थिर so it can only be
	 * changed via explicit cast within the
	 * routines that actually update the physical
	 * hardware.
	 */
	स्थिर काष्ठा iwl_rxon_cmd active;
	काष्ठा iwl_rxon_cmd staging;

	काष्ठा iwl_rxon_समय_cmd timing;

	काष्ठा iwl_qos_info qos_data;

	u8 bcast_sta_id, ap_sta_id;

	u8 rxon_cmd, rxon_assoc_cmd, rxon_timing_cmd;
	u8 qos_cmd;
	u8 wep_key_cmd;

	काष्ठा iwl_wep_key wep_keys[WEP_KEYS_MAX];
	u8 key_mapping_keys;

	__le32 station_flags;

	पूर्णांक beacon_पूर्णांक;

	काष्ठा अणु
		bool non_gf_sta_present;
		u8 protection;
		bool enabled, is_40mhz;
		u8 extension_chan_offset;
	पूर्ण ht;
पूर्ण;

क्रमागत iwl_scan_type अणु
	IWL_SCAN_NORMAL,
	IWL_SCAN_RADIO_RESET,
पूर्ण;

/**
 * काष्ठा iwl_hw_params
 *
 * Holds the module parameters
 *
 * @tx_chains_num: Number of TX chains
 * @rx_chains_num: Number of RX chains
 * @ct_समाप्त_threshold: temperature threshold - in hw dependent unit
 * @ct_समाप्त_निकास_threshold: when to reeable the device - in hw dependent unit
 *	relevant क्रम 1000, 6000 and up
 * @काष्ठा iwl_sensitivity_ranges: range of sensitivity values
 * @use_rts_क्रम_aggregation: use rts/cts protection क्रम HT traffic
 */
काष्ठा iwl_hw_params अणु
	u8  tx_chains_num;
	u8  rx_chains_num;
	bool use_rts_क्रम_aggregation;
	u32 ct_समाप्त_threshold;
	u32 ct_समाप्त_निकास_threshold;

	स्थिर काष्ठा iwl_sensitivity_ranges *sens;
पूर्ण;

/**
 * काष्ठा iwl_dvm_bt_params - DVM specअगरic BT (coex) parameters
 * @advanced_bt_coexist: support advanced bt coexist
 * @bt_init_traffic_load: specअगरy initial bt traffic load
 * @bt_prio_boost: शेष bt priority boost value
 * @agg_समय_limit: maximum number of uSec in aggregation
 * @bt_sco_disable: uCode should not response to BT in SCO/ESCO mode
 */
काष्ठा iwl_dvm_bt_params अणु
	bool advanced_bt_coexist;
	u8 bt_init_traffic_load;
	u32 bt_prio_boost;
	u16 agg_समय_limit;
	bool bt_sco_disable;
	bool bt_session_2;
पूर्ण;

/**
 * काष्ठा iwl_dvm_cfg - DVM firmware specअगरic device configuration
 * @set_hw_params: set hardware parameters
 * @set_channel_चयन: send channel चयन command
 * @nic_config: apply device specअगरic configuration
 * @temperature: पढ़ो temperature
 * @adv_thermal_throttle: support advance thermal throttle
 * @support_ct_समाप्त_निकास: support ct समाप्त निकास condition
 * @plcp_delta_threshold: plcp error rate threshold used to trigger
 *	radio tuning when there is a high receiving plcp error rate
 * @chain_noise_scale: शेष chain noise scale used क्रम gain computation
 * @hd_v2: v2 of enhanced sensitivity value, used क्रम 2000 series and up
 * @no_idle_support: करो not support idle mode
 * @bt_params: poपूर्णांकer to BT parameters
 * @need_temp_offset_calib: need to perक्रमm temperature offset calibration
 * @no_xtal_calib: some devices करो not need crystal calibration data,
 *	करोn't send it to those
 * @temp_offset_v2: support v2 of temperature offset calibration
 * @adv_pm: advanced घातer management
 */
काष्ठा iwl_dvm_cfg अणु
	व्योम (*set_hw_params)(काष्ठा iwl_priv *priv);
	पूर्णांक (*set_channel_चयन)(काष्ठा iwl_priv *priv,
				  काष्ठा ieee80211_channel_चयन *ch_चयन);
	व्योम (*nic_config)(काष्ठा iwl_priv *priv);
	व्योम (*temperature)(काष्ठा iwl_priv *priv);

	स्थिर काष्ठा iwl_dvm_bt_params *bt_params;
	s32 chain_noise_scale;
	u8 plcp_delta_threshold;
	bool adv_thermal_throttle;
	bool support_ct_समाप्त_निकास;
	bool hd_v2;
	bool no_idle_support;
	bool need_temp_offset_calib;
	bool no_xtal_calib;
	bool temp_offset_v2;
	bool adv_pm;
पूर्ण;

काष्ठा iwl_wipan_noa_data अणु
	काष्ठा rcu_head rcu_head;
	u32 length;
	u8 data[];
पूर्ण;

/* Calibration disabling bit mask */
क्रमागत अणु
	IWL_CALIB_ENABLE_ALL			= 0,

	IWL_SENSITIVITY_CALIB_DISABLED		= BIT(0),
	IWL_CHAIN_NOISE_CALIB_DISABLED		= BIT(1),
	IWL_TX_POWER_CALIB_DISABLED		= BIT(2),

	IWL_CALIB_DISABLE_ALL			= 0xFFFFFFFF,
पूर्ण;

#घोषणा IWL_OP_MODE_GET_DVM(_iwl_op_mode) \
	((काष्ठा iwl_priv *) ((_iwl_op_mode)->op_mode_specअगरic))

#घोषणा IWL_MAC80211_GET_DVM(_hw) \
	((काष्ठा iwl_priv *) ((काष्ठा iwl_op_mode *) \
	(_hw)->priv)->op_mode_specअगरic)

काष्ठा iwl_priv अणु

	काष्ठा iwl_trans *trans;
	काष्ठा device *dev;		/* क्रम debug prपूर्णांकs only */
	स्थिर काष्ठा iwl_cfg *cfg;
	स्थिर काष्ठा iwl_fw *fw;
	स्थिर काष्ठा iwl_dvm_cfg *lib;
	अचिन्हित दीर्घ status;

	spinlock_t sta_lock;
	काष्ठा mutex mutex;

	अचिन्हित दीर्घ transport_queue_stop;
	bool passive_no_rx;
#घोषणा IWL_INVALID_MAC80211_QUEUE	0xff
	u8 queue_to_mac80211[IWL_MAX_HW_QUEUES];
	atomic_t queue_stop_count[IWL_MAX_HW_QUEUES];

	अचिन्हित दीर्घ agg_q_alloc[BITS_TO_LONGS(IWL_MAX_HW_QUEUES)];

	/* ieee device used by generic ieee processing code */
	काष्ठा ieee80211_hw *hw;

	काष्ठा napi_काष्ठा *napi;

	काष्ठा list_head calib_results;

	काष्ठा workqueue_काष्ठा *workqueue;

	काष्ठा iwl_hw_params hw_params;

	क्रमागत nl80211_band band;
	u8 valid_contexts;

	व्योम (*rx_handlers[REPLY_MAX])(काष्ठा iwl_priv *priv,
				       काष्ठा iwl_rx_cmd_buffer *rxb);

	काष्ठा iwl_notअगर_रुको_data notअगर_रुको;

	/* spectrum measurement report caching */
	काष्ठा iwl_spectrum_notअगरication measure_report;
	u8 measurement_status;

	/* ucode beacon समय */
	u32 ucode_beacon_समय;
	पूर्णांक missed_beacon_threshold;

	/* track IBSS manager (last beacon) status */
	u32 ibss_manager;

	/* jअगरfies when last recovery from statistics was perक्रमmed */
	अचिन्हित दीर्घ rx_statistics_jअगरfies;

	/*counters */
	u32 rx_handlers_stats[REPLY_MAX];

	/* rf reset */
	काष्ठा iwl_rf_reset rf_reset;

	/* firmware reload counter and बारtamp */
	अचिन्हित दीर्घ reload_jअगरfies;
	पूर्णांक reload_count;
	bool ucode_loaded;

	u8 plcp_delta_threshold;

	/* thermal calibration */
	s32 temperature;	/* Celsius */
	s32 last_temperature;

	काष्ठा iwl_wipan_noa_data __rcu *noa_data;

	/* Scan related variables */
	अचिन्हित दीर्घ scan_start;
	अचिन्हित दीर्घ scan_start_tsf;
	व्योम *scan_cmd;
	क्रमागत nl80211_band scan_band;
	काष्ठा cfg80211_scan_request *scan_request;
	काष्ठा ieee80211_vअगर *scan_vअगर;
	क्रमागत iwl_scan_type scan_type;
	u8 scan_tx_ant[NUM_NL80211_BANDS];
	u8 mgmt_tx_ant;

	/* max number of station keys */
	u8 sta_key_max_num;

	bool new_scan_threshold_behaviour;

	bool wowlan;

	/* EEPROM MAC addresses */
	काष्ठा mac_address addresses[2];

	काष्ठा iwl_rxon_context contexts[NUM_IWL_RXON_CTX];

	__le16 चयन_channel;

	u8 start_calib;
	काष्ठा iwl_sensitivity_data sensitivity_data;
	काष्ठा iwl_chain_noise_data chain_noise_data;
	__le16 sensitivity_tbl[HD_TABLE_SIZE];
	__le16 enhance_sensitivity_tbl[ENHANCE_HD_TABLE_ENTRIES];

	काष्ठा iwl_ht_config current_ht_config;

	/* Rate scaling data */
	u8 retry_rate;

	पूर्णांक activity_समयr_active;

	काष्ठा iwl_घातer_mgr घातer_data;
	काष्ठा iwl_tt_mgmt thermal_throttle;

	/* station table variables */
	पूर्णांक num_stations;
	काष्ठा iwl_station_entry stations[IWLAGN_STATION_COUNT];
	अचिन्हित दीर्घ ucode_key_table;
	काष्ठा iwl_tid_data tid_data[IWLAGN_STATION_COUNT][IWL_MAX_TID_COUNT];
	atomic_t num_aux_in_flight;

	u8 mac80211_रेजिस्टरed;

	/* Indication अगर ieee80211_ops->खोलो has been called */
	u8 is_खोलो;

	क्रमागत nl80211_अगरtype iw_mode;

	/* Last Rx'd beacon बारtamp */
	u64 बारtamp;

	काष्ठा अणु
		__le32 flag;
		काष्ठा statistics_general_common common;
		काष्ठा statistics_rx_non_phy rx_non_phy;
		काष्ठा statistics_rx_phy rx_ofdm;
		काष्ठा statistics_rx_ht_phy rx_ofdm_ht;
		काष्ठा statistics_rx_phy rx_cck;
		काष्ठा statistics_tx tx;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
		काष्ठा statistics_bt_activity bt_activity;
		__le32 num_bt_समाप्तs, accum_num_bt_समाप्तs;
#पूर्ण_अगर
		spinlock_t lock;
	पूर्ण statistics;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	काष्ठा अणु
		काष्ठा statistics_general_common common;
		काष्ठा statistics_rx_non_phy rx_non_phy;
		काष्ठा statistics_rx_phy rx_ofdm;
		काष्ठा statistics_rx_ht_phy rx_ofdm_ht;
		काष्ठा statistics_rx_phy rx_cck;
		काष्ठा statistics_tx tx;
		काष्ठा statistics_bt_activity bt_activity;
	पूर्ण accum_stats, delta_stats, max_delta_stats;
#पूर्ण_अगर

	/*
	 * reporting the number of tids has AGG on. 0 means
	 * no AGGREGATION
	 */
	u8 agg_tids_count;

	काष्ठा iwl_rx_phy_res last_phy_res;
	u32 ampdu_ref;
	bool last_phy_res_valid;

	/*
	 * chain noise reset and gain commands are the
	 * two extra calibration commands follows the standard
	 * phy calibration commands
	 */
	u8 phy_calib_chain_noise_reset_cmd;
	u8 phy_calib_chain_noise_gain_cmd;

	/* counts reply_tx error */
	काष्ठा reply_tx_error_statistics reply_tx_stats;
	काष्ठा reply_agg_tx_error_statistics reply_agg_tx_stats;

	/* bt coex */
	u8 bt_enable_flag;
	u8 bt_status;
	u8 bt_traffic_load, last_bt_traffic_load;
	bool bt_ch_announce;
	bool bt_full_concurrent;
	__le32 समाप्त_ack_mask;
	__le32 समाप्त_cts_mask;
	__le16 bt_valid;
	bool reduced_txघातer;
	u16 bt_on_thresh;
	u16 bt_duration;
	u16 dynamic_frag_thresh;
	u8 bt_ci_compliance;
	काष्ठा work_काष्ठा bt_traffic_change_work;
	bool bt_enable_pspoll;
	काष्ठा iwl_rxon_context *cur_rssi_ctx;
	bool bt_is_sco;

	काष्ठा work_काष्ठा restart;
	काष्ठा work_काष्ठा scan_completed;
	काष्ठा work_काष्ठा पात_scan;

	काष्ठा work_काष्ठा beacon_update;
	काष्ठा iwl_rxon_context *beacon_ctx;
	काष्ठा sk_buff *beacon_skb;
	व्योम *beacon_cmd;

	काष्ठा work_काष्ठा tt_work;
	काष्ठा work_काष्ठा ct_enter;
	काष्ठा work_काष्ठा ct_निकास;
	काष्ठा work_काष्ठा start_पूर्णांकernal_scan;
	काष्ठा work_काष्ठा tx_flush;
	काष्ठा work_काष्ठा bt_full_concurrency;
	काष्ठा work_काष्ठा bt_runसमय_config;

	काष्ठा delayed_work scan_check;

	/* TX Power settings */
	s8 tx_घातer_user_lmt;
	s8 tx_घातer_next;

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	/* debugfs */
	काष्ठा dentry *debugfs_dir;
	u32 dbgfs_sram_offset, dbgfs_sram_len;
	bool disable_ht40;
	व्योम *wowlan_sram;
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUGFS */

	काष्ठा iwl_nvm_data *nvm_data;
	/* eeprom blob क्रम debugfs */
	u8 *eeprom_blob;
	माप_प्रकार eeprom_blob_size;

	काष्ठा work_काष्ठा txघातer_work;
	u32 calib_disabled;
	काष्ठा work_काष्ठा run_समय_calib_work;
	काष्ठा समयr_list statistics_periodic;
	काष्ठा समयr_list ucode_trace;

	काष्ठा iwl_event_log event_log;

#अगर_घोषित CONFIG_IWLWIFI_LEDS
	काष्ठा led_classdev led;
	अचिन्हित दीर्घ blink_on, blink_off;
	bool led_रेजिस्टरed;
#पूर्ण_अगर

	/* WoWLAN GTK rekey data */
	u8 kck[NL80211_KCK_LEN], kek[NL80211_KEK_LEN];
	__le64 replay_ctr;
	__le16 last_seq_ctl;
	bool have_rekey_data;
#अगर_घोषित CONFIG_PM_SLEEP
	काष्ठा wiphy_wowlan_support wowlan_support;
#पूर्ण_अगर

	/* device_poपूर्णांकers: poपूर्णांकers to ucode event tables */
	काष्ठा अणु
		u32 error_event_table;
		u32 log_event_table;
	पूर्ण device_poपूर्णांकers;

	/* indicator of loaded ucode image */
	क्रमागत iwl_ucode_type cur_ucode;
पूर्ण; /*iwl_priv */

अटल अंतरभूत काष्ठा iwl_rxon_context *
iwl_rxon_ctx_from_vअगर(काष्ठा ieee80211_vअगर *vअगर)
अणु
	काष्ठा iwl_vअगर_priv *vअगर_priv = (व्योम *)vअगर->drv_priv;

	वापस vअगर_priv->ctx;
पूर्ण

#घोषणा क्रम_each_context(priv, ctx)				\
	क्रम (ctx = &priv->contexts[IWL_RXON_CTX_BSS];		\
	     ctx < &priv->contexts[NUM_IWL_RXON_CTX]; ctx++)	\
		अगर (priv->valid_contexts & BIT(ctx->ctxid))

अटल अंतरभूत पूर्णांक iwl_is_associated_ctx(काष्ठा iwl_rxon_context *ctx)
अणु
	वापस (ctx->active.filter_flags & RXON_FILTER_ASSOC_MSK) ? 1 : 0;
पूर्ण

अटल अंतरभूत पूर्णांक iwl_is_associated(काष्ठा iwl_priv *priv,
				    क्रमागत iwl_rxon_context_id ctxid)
अणु
	वापस iwl_is_associated_ctx(&priv->contexts[ctxid]);
पूर्ण

अटल अंतरभूत पूर्णांक iwl_is_any_associated(काष्ठा iwl_priv *priv)
अणु
	काष्ठा iwl_rxon_context *ctx;
	क्रम_each_context(priv, ctx)
		अगर (iwl_is_associated_ctx(ctx))
			वापस true;
	वापस false;
पूर्ण

#पूर्ण_अगर				/* __iwl_dev_h__ */
