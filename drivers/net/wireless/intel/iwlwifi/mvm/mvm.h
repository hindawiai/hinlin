<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __IWL_MVM_H__
#घोषणा __IWL_MVM_H__

#समावेश <linux/list.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/leds.h>
#समावेश <linux/in6.h>

#अगर_घोषित CONFIG_THERMAL
#समावेश <linux/thermal.h>
#पूर्ण_अगर

#समावेश "iwl-op-mode.h"
#समावेश "iwl-trans.h"
#समावेश "fw/notif-wait.h"
#समावेश "iwl-eeprom-parse.h"
#समावेश "fw/file.h"
#समावेश "iwl-config.h"
#समावेश "sta.h"
#समावेश "fw-api.h"
#समावेश "constants.h"
#समावेश "fw/runtime.h"
#समावेश "fw/dbg.h"
#समावेश "fw/acpi.h"
#समावेश "iwl-nvm-parse.h"

#समावेश <linux/average.h>

#घोषणा IWL_MVM_MAX_ADDRESSES		5
/* RSSI offset क्रम WkP */
#घोषणा IWL_RSSI_OFFSET 50
#घोषणा IWL_MVM_MISSED_BEACONS_THRESHOLD 8
#घोषणा IWL_MVM_MISSED_BEACONS_THRESHOLD_LONG 16

/* A TimeUnit is 1024 microsecond */
#घोषणा MSEC_TO_TU(_msec)	(_msec*1000/1024)

/* For GO, this value represents the number of TUs beक्रमe CSA "beacon
 * 0" TBTT when the CSA समय-event needs to be scheduled to start.  It
 * must be big enough to ensure that we चयन in समय.
 */
#घोषणा IWL_MVM_CHANNEL_SWITCH_TIME_GO		40

/* For client, this value represents the number of TUs beक्रमe CSA
 * "beacon 1" TBTT, instead.  This is because we करोn't know when the
 * GO/AP will be in the new channel, so we चयन early enough.
 */
#घोषणा IWL_MVM_CHANNEL_SWITCH_TIME_CLIENT	10

/*
 * This value (in TUs) is used to fine tune the CSA NoA end समय which should
 * be just beक्रमe "beacon 0" TBTT.
 */
#घोषणा IWL_MVM_CHANNEL_SWITCH_MARGIN 4

/*
 * Number of beacons to transmit on a new channel until we unblock tx to
 * the stations, even अगर we didn't identअगरy them on a new channel
 */
#घोषणा IWL_MVM_CS_UNBLOCK_TX_TIMEOUT 3

/* offchannel queue towards mac80211 */
#घोषणा IWL_MVM_OFFCHANNEL_QUEUE 0

बाह्य स्थिर काष्ठा ieee80211_ops iwl_mvm_hw_ops;

/**
 * काष्ठा iwl_mvm_mod_params - module parameters क्रम iwlmvm
 * @init_dbg: अगर true, then the NIC won't be stopped अगर the INIT fw निश्चितed.
 *	We will रेजिस्टर to mac80211 to have tesपंचांगode working. The NIC must not
 *	be up'ed after the INIT fw निश्चितed. This is useful to be able to use
 *	proprietary tools over tesपंचांगode to debug the INIT fw.
 * @घातer_scheme: one of क्रमागत iwl_घातer_scheme
 */
काष्ठा iwl_mvm_mod_params अणु
	bool init_dbg;
	पूर्णांक घातer_scheme;
पूर्ण;
बाह्य काष्ठा iwl_mvm_mod_params iwlmvm_mod_params;

काष्ठा iwl_mvm_phy_ctxt अणु
	u16 id;
	u16 color;
	u32 ref;

	क्रमागत nl80211_chan_width width;

	/*
	 * TODO: This should probably be हटाओd. Currently here only क्रम rate
	 * scaling algorithm
	 */
	काष्ठा ieee80211_channel *channel;
पूर्ण;

काष्ठा iwl_mvm_समय_event_data अणु
	काष्ठा ieee80211_vअगर *vअगर;
	काष्ठा list_head list;
	अचिन्हित दीर्घ end_jअगरfies;
	u32 duration;
	bool running;
	u32 uid;

	/*
	 * The access to the 'id' field must be करोne when the
	 * mvm->समय_event_lock is held, as it value is used to indicate
	 * अगर the te is in the समय event list or not (when id == TE_MAX)
	 */
	u32 id;
पूर्ण;

 /* Power management */

/**
 * क्रमागत iwl_घातer_scheme
 * @IWL_POWER_LEVEL_CAM - Continuously Active Mode
 * @IWL_POWER_LEVEL_BPS - Balanced Power Save (शेष)
 * @IWL_POWER_LEVEL_LP  - Low Power
 */
क्रमागत iwl_घातer_scheme अणु
	IWL_POWER_SCHEME_CAM = 1,
	IWL_POWER_SCHEME_BPS,
	IWL_POWER_SCHEME_LP
पूर्ण;

#घोषणा IWL_CONN_MAX_LISTEN_INTERVAL	10
#घोषणा IWL_UAPSD_MAX_SP		IEEE80211_WMM_IE_STA_QOSINFO_SP_ALL

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
क्रमागत iwl_dbgfs_pm_mask अणु
	MVM_DEBUGFS_PM_KEEP_ALIVE = BIT(0),
	MVM_DEBUGFS_PM_SKIP_OVER_DTIM = BIT(1),
	MVM_DEBUGFS_PM_SKIP_DTIM_PERIODS = BIT(2),
	MVM_DEBUGFS_PM_RX_DATA_TIMEOUT = BIT(3),
	MVM_DEBUGFS_PM_TX_DATA_TIMEOUT = BIT(4),
	MVM_DEBUGFS_PM_LPRX_ENA = BIT(6),
	MVM_DEBUGFS_PM_LPRX_RSSI_THRESHOLD = BIT(7),
	MVM_DEBUGFS_PM_SNOOZE_ENABLE = BIT(8),
	MVM_DEBUGFS_PM_UAPSD_MISBEHAVING = BIT(9),
	MVM_DEBUGFS_PM_USE_PS_POLL = BIT(10),
पूर्ण;

काष्ठा iwl_dbgfs_pm अणु
	u16 keep_alive_seconds;
	u32 rx_data_समयout;
	u32 tx_data_समयout;
	bool skip_over_dtim;
	u8 skip_dtim_periods;
	bool lprx_ena;
	u32 lprx_rssi_threshold;
	bool snooze_ena;
	bool uapsd_misbehaving;
	bool use_ps_poll;
	पूर्णांक mask;
पूर्ण;

/* beacon filtering */

क्रमागत iwl_dbgfs_bf_mask अणु
	MVM_DEBUGFS_BF_ENERGY_DELTA = BIT(0),
	MVM_DEBUGFS_BF_ROAMING_ENERGY_DELTA = BIT(1),
	MVM_DEBUGFS_BF_ROAMING_STATE = BIT(2),
	MVM_DEBUGFS_BF_TEMP_THRESHOLD = BIT(3),
	MVM_DEBUGFS_BF_TEMP_FAST_FILTER = BIT(4),
	MVM_DEBUGFS_BF_TEMP_SLOW_FILTER = BIT(5),
	MVM_DEBUGFS_BF_ENABLE_BEACON_FILTER = BIT(6),
	MVM_DEBUGFS_BF_DEBUG_FLAG = BIT(7),
	MVM_DEBUGFS_BF_ESCAPE_TIMER = BIT(8),
	MVM_DEBUGFS_BA_ESCAPE_TIMER = BIT(9),
	MVM_DEBUGFS_BA_ENABLE_BEACON_ABORT = BIT(10),
पूर्ण;

काष्ठा iwl_dbgfs_bf अणु
	u32 bf_energy_delta;
	u32 bf_roaming_energy_delta;
	u32 bf_roaming_state;
	u32 bf_temp_threshold;
	u32 bf_temp_fast_filter;
	u32 bf_temp_slow_filter;
	u32 bf_enable_beacon_filter;
	u32 bf_debug_flag;
	u32 bf_escape_समयr;
	u32 ba_escape_समयr;
	u32 ba_enable_beacon_पात;
	पूर्णांक mask;
पूर्ण;
#पूर्ण_अगर

क्रमागत iwl_mvm_smps_type_request अणु
	IWL_MVM_SMPS_REQ_BT_COEX,
	IWL_MVM_SMPS_REQ_TT,
	IWL_MVM_SMPS_REQ_PROT,
	NUM_IWL_MVM_SMPS_REQ,
पूर्ण;

क्रमागत iwl_bt_क्रमce_ant_mode अणु
	BT_FORCE_ANT_DIS = 0,
	BT_FORCE_ANT_AUTO,
	BT_FORCE_ANT_BT,
	BT_FORCE_ANT_WIFI,

	BT_FORCE_ANT_MAX,
पूर्ण;

/**
 * काष्ठा iwl_mvm_low_latency_क्रमce - low latency क्रमce mode set by debugfs
 * @LOW_LATENCY_FORCE_UNSET: unset क्रमce mode
 * @LOW_LATENCY_FORCE_ON: क्रम low latency on
 * @LOW_LATENCY_FORCE_OFF: क्रम low latency off
 * @NUM_LOW_LATENCY_FORCE: max num of modes
 */
क्रमागत iwl_mvm_low_latency_क्रमce अणु
	LOW_LATENCY_FORCE_UNSET,
	LOW_LATENCY_FORCE_ON,
	LOW_LATENCY_FORCE_OFF,
	NUM_LOW_LATENCY_FORCE
पूर्ण;

/**
* काष्ठा iwl_mvm_low_latency_cause - low latency set causes
* @LOW_LATENCY_TRAFFIC: indicates low latency traffic was detected
* @LOW_LATENCY_DEBUGFS: low latency mode set from debugfs
* @LOW_LATENCY_VCMD: low latency mode set from venकरोr command
* @LOW_LATENCY_VIF_TYPE: low latency mode set because of vअगर type (ap)
* @LOW_LATENCY_DEBUGFS_FORCE_ENABLE: indicate that क्रमce mode is enabled
*	the actual set/unset is करोne with LOW_LATENCY_DEBUGFS_FORCE
* @LOW_LATENCY_DEBUGFS_FORCE: low latency क्रमce mode from debugfs
*	set this with LOW_LATENCY_DEBUGFS_FORCE_ENABLE flag
*	in low_latency.
*/
क्रमागत iwl_mvm_low_latency_cause अणु
	LOW_LATENCY_TRAFFIC = BIT(0),
	LOW_LATENCY_DEBUGFS = BIT(1),
	LOW_LATENCY_VCMD = BIT(2),
	LOW_LATENCY_VIF_TYPE = BIT(3),
	LOW_LATENCY_DEBUGFS_FORCE_ENABLE = BIT(4),
	LOW_LATENCY_DEBUGFS_FORCE = BIT(5),
पूर्ण;

/**
* काष्ठा iwl_mvm_vअगर_bf_data - beacon filtering related data
* @bf_enabled: indicates अगर beacon filtering is enabled
* @ba_enabled: indicated अगर beacon पात is enabled
* @ave_beacon_संकेत: average beacon संकेत
* @last_cqm_event: rssi of the last cqm event
* @bt_coex_min_thold: minimum threshold क्रम BT coex
* @bt_coex_max_thold: maximum threshold क्रम BT coex
* @last_bt_coex_event: rssi of the last BT coex event
*/
काष्ठा iwl_mvm_vअगर_bf_data अणु
	bool bf_enabled;
	bool ba_enabled;
	पूर्णांक ave_beacon_संकेत;
	पूर्णांक last_cqm_event;
	पूर्णांक bt_coex_min_thold;
	पूर्णांक bt_coex_max_thold;
	पूर्णांक last_bt_coex_event;
पूर्ण;

/**
 * काष्ठा iwl_probe_resp_data - data क्रम NoA/CSA updates
 * @rcu_head: used क्रम मुक्तing the data on update
 * @notअगर: notअगरication data
 * @noa_len: length of NoA attribute, calculated from the notअगरication
 */
काष्ठा iwl_probe_resp_data अणु
	काष्ठा rcu_head rcu_head;
	काष्ठा iwl_probe_resp_data_notअगर notअगर;
	पूर्णांक noa_len;
पूर्ण;

/**
 * काष्ठा iwl_mvm_vअगर - data per Virtual Interface, it is a MAC context
 * @id: between 0 and 3
 * @color: to solve races upon MAC addition and removal
 * @ap_sta_id: the sta_id of the AP - valid only अगर VIF type is STA
 * @bssid: BSSID क्रम this (client) पूर्णांकerface
 * @associated: indicates that we're currently associated, used only क्रम
 *	managing the firmware state in iwl_mvm_bss_info_changed_station()
 * @ap_assoc_sta_count: count of stations associated to us - valid only
 *	अगर VIF type is AP
 * @uploaded: indicates the MAC context has been added to the device
 * @ap_ibss_active: indicates that AP/IBSS is configured and that the पूर्णांकerface
 *	should get quota etc.
 * @pm_enabled - Indicate अगर MAC घातer management is allowed
 * @monitor_active: indicates that monitor context is configured, and that the
 *	पूर्णांकerface should get quota etc.
 * @low_latency: bit flags क्रम low latency
 *	see क्रमागत &iwl_mvm_low_latency_cause क्रम causes.
 * @low_latency_actual: boolean, indicates low latency is set,
 *	as a result from low_latency bit flags and takes क्रमce पूर्णांकo account.
 * @ps_disabled: indicates that this पूर्णांकerface requires PS to be disabled
 * @queue_params: QoS params क्रम this MAC
 * @bcast_sta: station used क्रम broadcast packets. Used by the following
 *  vअगरs: P2P_DEVICE, GO and AP.
 * @beacon_skb: the skb used to hold the AP/GO beacon ढाँचा
 * @smps_requests: the SMPS requests of dअगरferent parts of the driver,
 *	combined on update to yield the overall request to mac80211.
 * @beacon_stats: beacon statistics, containing the # of received beacons,
 *	# of received beacons accumulated over FW restart, and the current
 *	average संकेत of beacons retrieved from the firmware
 * @csa_failed: CSA failed to schedule समय event, report an error later
 * @features: hw features active क्रम this vअगर
 * @probe_resp_data: data from FW notअगरication to store NOA and CSA related
 *	data to be inserted पूर्णांकo probe response.
 */
काष्ठा iwl_mvm_vअगर अणु
	काष्ठा iwl_mvm *mvm;
	u16 id;
	u16 color;
	u8 ap_sta_id;

	u8 bssid[ETH_ALEN];
	bool associated;
	u8 ap_assoc_sta_count;

	u16 cab_queue;

	bool uploaded;
	bool ap_ibss_active;
	bool pm_enabled;
	bool monitor_active;
	u8 low_latency: 6;
	u8 low_latency_actual: 1;
	bool ps_disabled;
	काष्ठा iwl_mvm_vअगर_bf_data bf_data;

	काष्ठा अणु
		u32 num_beacons, accu_num_beacons;
		u8 avg_संकेत;
	पूर्ण beacon_stats;

	u32 ap_beacon_समय;

	क्रमागत iwl_tsf_id tsf_id;

	/*
	 * QoS data from mac80211, need to store this here
	 * as mac80211 has a separate callback but we need
	 * to have the data क्रम the MAC context
	 */
	काष्ठा ieee80211_tx_queue_params queue_params[IEEE80211_NUM_ACS];
	काष्ठा iwl_mvm_समय_event_data समय_event_data;
	काष्ठा iwl_mvm_समय_event_data hs_समय_event_data;

	काष्ठा iwl_mvm_पूर्णांक_sta bcast_sta;
	काष्ठा iwl_mvm_पूर्णांक_sta mcast_sta;

	/*
	 * Asचिन्हित जबतक mac80211 has the पूर्णांकerface in a channel context,
	 * or, क्रम P2P Device, जबतक it exists.
	 */
	काष्ठा iwl_mvm_phy_ctxt *phy_ctxt;

#अगर_घोषित CONFIG_PM
	/* WoWLAN GTK rekey data */
	काष्ठा अणु
		u8 kck[NL80211_KCK_EXT_LEN];
		u8 kek[NL80211_KEK_EXT_LEN];
		माप_प्रकार kek_len;
		माप_प्रकार kck_len;
		u32 akm;
		__le64 replay_ctr;
		bool valid;
	पूर्ण rekey_data;

	पूर्णांक tx_key_idx;

	bool seqno_valid;
	u16 seqno;
#पूर्ण_अगर

#अगर IS_ENABLED(CONFIG_IPV6)
	/* IPv6 addresses क्रम WoWLAN */
	काष्ठा in6_addr target_ipv6_addrs[IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_MAX];
	अचिन्हित दीर्घ tentative_addrs[BITS_TO_LONGS(IWL_PROTO_OFFLOAD_NUM_IPV6_ADDRS_MAX)];
	पूर्णांक num_target_ipv6_addrs;
#पूर्ण_अगर

#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	काष्ठा dentry *dbgfs_dir;
	काष्ठा dentry *dbgfs_slink;
	काष्ठा iwl_dbgfs_pm dbgfs_pm;
	काष्ठा iwl_dbgfs_bf dbgfs_bf;
	काष्ठा iwl_mac_घातer_cmd mac_pwr_cmd;
	पूर्णांक dbgfs_quota_min;
#पूर्ण_अगर

	क्रमागत ieee80211_smps_mode smps_requests[NUM_IWL_MVM_SMPS_REQ];

	/* FW identअगरied misbehaving AP */
	u8 uapsd_misbehaving_bssid[ETH_ALEN];

	काष्ठा delayed_work uapsd_nonagg_detected_wk;

	/* Indicates that CSA countकरोwn may be started */
	bool csa_countकरोwn;
	bool csa_failed;
	u16 csa_target_freq;
	u16 csa_count;
	u16 csa_misbehave;
	काष्ठा delayed_work csa_work;

	/* Indicates that we are रुकोing क्रम a beacon on a new channel */
	bool csa_bcn_pending;

	/* TCP Checksum Offload */
	netdev_features_t features;

	काष्ठा iwl_probe_resp_data __rcu *probe_resp_data;

	/* we can only have 2 GTK + 2 IGTK active at a समय */
	काष्ठा ieee80211_key_conf *ap_early_keys[4];

	/* 26-tone RU OFDMA transmissions should be blocked */
	bool he_ru_2mhz_block;

	काष्ठा अणु
		काष्ठा ieee80211_key_conf __rcu *keys[2];
	पूर्ण bcn_prot;
पूर्ण;

अटल अंतरभूत काष्ठा iwl_mvm_vअगर *
iwl_mvm_vअगर_from_mac80211(काष्ठा ieee80211_vअगर *vअगर)
अणु
	अगर (!vअगर)
		वापस शून्य;
	वापस (व्योम *)vअगर->drv_priv;
पूर्ण

बाह्य स्थिर u8 tid_to_mac80211_ac[];

#घोषणा IWL_MVM_SCAN_STOPPING_SHIFT	8

क्रमागत iwl_scan_status अणु
	IWL_MVM_SCAN_REGULAR		= BIT(0),
	IWL_MVM_SCAN_SCHED		= BIT(1),
	IWL_MVM_SCAN_NETDETECT		= BIT(2),

	IWL_MVM_SCAN_STOPPING_REGULAR	= BIT(8),
	IWL_MVM_SCAN_STOPPING_SCHED	= BIT(9),
	IWL_MVM_SCAN_STOPPING_NETDETECT	= BIT(10),

	IWL_MVM_SCAN_REGULAR_MASK	= IWL_MVM_SCAN_REGULAR |
					  IWL_MVM_SCAN_STOPPING_REGULAR,
	IWL_MVM_SCAN_SCHED_MASK		= IWL_MVM_SCAN_SCHED |
					  IWL_MVM_SCAN_STOPPING_SCHED,
	IWL_MVM_SCAN_NETDETECT_MASK	= IWL_MVM_SCAN_NETDETECT |
					  IWL_MVM_SCAN_STOPPING_NETDETECT,

	IWL_MVM_SCAN_STOPPING_MASK	= 0xff << IWL_MVM_SCAN_STOPPING_SHIFT,
	IWL_MVM_SCAN_MASK		= 0xff,
पूर्ण;

क्रमागत iwl_mvm_scan_type अणु
	IWL_SCAN_TYPE_NOT_SET,
	IWL_SCAN_TYPE_UNASSOC,
	IWL_SCAN_TYPE_WILD,
	IWL_SCAN_TYPE_MILD,
	IWL_SCAN_TYPE_FRAGMENTED,
	IWL_SCAN_TYPE_FAST_BALANCE,
पूर्ण;

क्रमागत iwl_mvm_sched_scan_pass_all_states अणु
	SCHED_SCAN_PASS_ALL_DISABLED,
	SCHED_SCAN_PASS_ALL_ENABLED,
	SCHED_SCAN_PASS_ALL_FOUND,
पूर्ण;

/**
 * काष्ठा iwl_mvm_tt_mgnt - Thermal Throttling Management काष्ठाure
 * @ct_समाप्त_निकास: worker to निकास thermal समाप्त
 * @dynamic_smps: Is thermal throttling enabled dynamic_smps?
 * @tx_backoff: The current thremal throttling tx backoff in uSec.
 * @min_backoff: The minimal tx backoff due to घातer restrictions
 * @params: Parameters to configure the thermal throttling algorithm.
 * @throttle: Is thermal throttling is active?
 */
काष्ठा iwl_mvm_tt_mgmt अणु
	काष्ठा delayed_work ct_समाप्त_निकास;
	bool dynamic_smps;
	u32 tx_backoff;
	u32 min_backoff;
	काष्ठा iwl_tt_params params;
	bool throttle;
पूर्ण;

#अगर_घोषित CONFIG_THERMAL
/**
 *काष्ठा iwl_mvm_thermal_device - thermal zone related data
 * @temp_trips: temperature thresholds क्रम report
 * @fw_trips_index: keep indexes to original array - temp_trips
 * @tzone: thermal zone device data
*/
काष्ठा iwl_mvm_thermal_device अणु
	s16 temp_trips[IWL_MAX_DTS_TRIPS];
	u8 fw_trips_index[IWL_MAX_DTS_TRIPS];
	काष्ठा thermal_zone_device *tzone;
पूर्ण;

/*
 * काष्ठा iwl_mvm_cooling_device
 * @cur_state: current state
 * @cdev: काष्ठा thermal cooling device
 */
काष्ठा iwl_mvm_cooling_device अणु
	u32 cur_state;
	काष्ठा thermal_cooling_device *cdev;
पूर्ण;
#पूर्ण_अगर

#घोषणा IWL_MVM_NUM_LAST_FRAMES_UCODE_RATES 8

काष्ठा iwl_mvm_frame_stats अणु
	u32 legacy_frames;
	u32 ht_frames;
	u32 vht_frames;
	u32 bw_20_frames;
	u32 bw_40_frames;
	u32 bw_80_frames;
	u32 bw_160_frames;
	u32 sgi_frames;
	u32 ngi_frames;
	u32 siso_frames;
	u32 mimo2_frames;
	u32 agg_frames;
	u32 ampdu_count;
	u32 success_frames;
	u32 fail_frames;
	u32 last_rates[IWL_MVM_NUM_LAST_FRAMES_UCODE_RATES];
	पूर्णांक last_frame_idx;
पूर्ण;

#घोषणा IWL_MVM_DEBUG_SET_TEMPERATURE_DISABLE 0xff
#घोषणा IWL_MVM_DEBUG_SET_TEMPERATURE_MIN -100
#घोषणा IWL_MVM_DEBUG_SET_TEMPERATURE_MAX 200

क्रमागत iwl_mvm_tdls_cs_state अणु
	IWL_MVM_TDLS_SW_IDLE = 0,
	IWL_MVM_TDLS_SW_REQ_SENT,
	IWL_MVM_TDLS_SW_RESP_RCVD,
	IWL_MVM_TDLS_SW_REQ_RCVD,
	IWL_MVM_TDLS_SW_ACTIVE,
पूर्ण;

क्रमागत iwl_mvm_traffic_load अणु
	IWL_MVM_TRAFFIC_LOW,
	IWL_MVM_TRAFFIC_MEDIUM,
	IWL_MVM_TRAFFIC_HIGH,
पूर्ण;

DECLARE_EWMA(rate, 16, 16)

काष्ठा iwl_mvm_tcm_mac अणु
	काष्ठा अणु
		u32 pkts[IEEE80211_NUM_ACS];
		u32 airसमय;
	पूर्ण tx;
	काष्ठा अणु
		u32 pkts[IEEE80211_NUM_ACS];
		u32 airसमय;
		u32 last_ampdu_ref;
	पूर्ण rx;
	काष्ठा अणु
		/* track AP's transfer in client mode */
		u64 rx_bytes;
		काष्ठा ewma_rate rate;
		bool detected;
	पूर्ण uapsd_nonagg_detect;
	bool खोलोed_rx_ba_sessions;
पूर्ण;

काष्ठा iwl_mvm_tcm अणु
	काष्ठा delayed_work work;
	spinlock_t lock; /* used when समय elapsed */
	अचिन्हित दीर्घ ts; /* बारtamp when period ends */
	अचिन्हित दीर्घ ll_ts;
	अचिन्हित दीर्घ uapsd_nonagg_ts;
	bool छोड़ोd;
	काष्ठा iwl_mvm_tcm_mac data[NUM_MAC_INDEX_DRIVER];
	काष्ठा अणु
		u32 elapsed; /* milliseconds क्रम this TCM period */
		u32 airसमय[NUM_MAC_INDEX_DRIVER];
		क्रमागत iwl_mvm_traffic_load load[NUM_MAC_INDEX_DRIVER];
		क्रमागत iwl_mvm_traffic_load band_load[NUM_NL80211_BANDS];
		क्रमागत iwl_mvm_traffic_load global_load;
		bool low_latency[NUM_MAC_INDEX_DRIVER];
		bool change[NUM_MAC_INDEX_DRIVER];
	पूर्ण result;
पूर्ण;

/**
 * काष्ठा iwl_mvm_reorder_buffer - per ra/tid/queue reorder buffer
 * @head_sn: reorder winकरोw head sn
 * @num_stored: number of mpdus stored in the buffer
 * @buf_size: the reorder buffer size as set by the last addba request
 * @queue: queue of this reorder buffer
 * @last_amsdu: track last ASMDU SN क्रम duplication detection
 * @last_sub_index: track ASMDU sub frame index क्रम duplication detection
 * @reorder_समयr: समयr क्रम frames are in the reorder buffer. For AMSDU
 *	it is the समय of last received sub-frame
 * @हटाओd: prevent समयr re-arming
 * @valid: reordering is valid क्रम this queue
 * @lock: protect reorder buffer पूर्णांकernal state
 * @mvm: mvm poपूर्णांकer, needed क्रम frame समयr context
 * @consec_oldsn_drops: consecutive drops due to old SN
 * @consec_oldsn_ampdu_gp2: A-MPDU GP2 बारtamp to track
 *	when to apply old SN consecutive drop workaround
 * @consec_oldsn_prev_drop: track whether or not an MPDU
 *	that was single/part of the previous A-MPDU was
 *	dropped due to old SN
 */
काष्ठा iwl_mvm_reorder_buffer अणु
	u16 head_sn;
	u16 num_stored;
	u16 buf_size;
	पूर्णांक queue;
	u16 last_amsdu;
	u8 last_sub_index;
	काष्ठा समयr_list reorder_समयr;
	bool हटाओd;
	bool valid;
	spinlock_t lock;
	काष्ठा iwl_mvm *mvm;
	अचिन्हित पूर्णांक consec_oldsn_drops;
	u32 consec_oldsn_ampdu_gp2;
	अचिन्हित पूर्णांक consec_oldsn_prev_drop:1;
पूर्ण ____cacheline_aligned_in_smp;

/**
 * काष्ठा _iwl_mvm_reorder_buf_entry - reorder buffer entry per-queue/per-seqno
 * @frames: list of skbs stored
 * @reorder_समय: समय the packet was stored in the reorder buffer
 */
काष्ठा _iwl_mvm_reorder_buf_entry अणु
	काष्ठा sk_buff_head frames;
	अचिन्हित दीर्घ reorder_समय;
पूर्ण;

/* make this indirection to get the aligned thing */
काष्ठा iwl_mvm_reorder_buf_entry अणु
	काष्ठा _iwl_mvm_reorder_buf_entry e;
पूर्ण
#अगर_अघोषित __CHECKER__
/* sparse करोesn't like this स्थिरruct: "bad integer constant expression" */
__aligned(roundup_घात_of_two(माप(काष्ठा _iwl_mvm_reorder_buf_entry)))
#पूर्ण_अगर
;

/**
 * काष्ठा iwl_mvm_baid_data - BA session data
 * @sta_id: station id
 * @tid: tid of the session
 * @baid baid of the session
 * @समयout: the समयout set in the addba request
 * @entries_per_queue: # of buffers per queue, this actually माला_लो
 *	aligned up to aव्योम cache line sharing between queues
 * @last_rx: last rx jअगरfies, updated only अगर समयout passed from last update
 * @session_समयr: समयr to check अगर BA session expired, runs at 2 * समयout
 * @mvm: mvm poपूर्णांकer, needed क्रम समयr context
 * @reorder_buf: reorder buffer, allocated per queue
 * @reorder_buf_data: data
 */
काष्ठा iwl_mvm_baid_data अणु
	काष्ठा rcu_head rcu_head;
	u8 sta_id;
	u8 tid;
	u8 baid;
	u16 समयout;
	u16 entries_per_queue;
	अचिन्हित दीर्घ last_rx;
	काष्ठा समयr_list session_समयr;
	काष्ठा iwl_mvm_baid_data __rcu **rcu_ptr;
	काष्ठा iwl_mvm *mvm;
	काष्ठा iwl_mvm_reorder_buffer reorder_buf[IWL_MAX_RX_HW_QUEUES];
	काष्ठा iwl_mvm_reorder_buf_entry entries[];
पूर्ण;

अटल अंतरभूत काष्ठा iwl_mvm_baid_data *
iwl_mvm_baid_data_from_reorder_buf(काष्ठा iwl_mvm_reorder_buffer *buf)
अणु
	वापस (व्योम *)((u8 *)buf -
			दुरत्व(काष्ठा iwl_mvm_baid_data, reorder_buf) -
			माप(*buf) * buf->queue);
पूर्ण

/*
 * क्रमागत iwl_mvm_queue_status - queue status
 * @IWL_MVM_QUEUE_FREE: the queue is not allocated nor reserved
 *	Basically, this means that this queue can be used क्रम any purpose
 * @IWL_MVM_QUEUE_RESERVED: queue is reserved but not yet in use
 *	This is the state of a queue that has been dedicated क्रम some RATID
 *	(agg'd or not), but that hasn't yet gone through the actual enablement
 *	of iwl_mvm_enable_txq(), and thereक्रमe no traffic can go through it yet.
 *	Note that in this state there is no requirement to alपढ़ोy know what TID
 *	should be used with this queue, it is just marked as a queue that will
 *	be used, and shouldn't be allocated to anyone अन्यथा.
 * @IWL_MVM_QUEUE_READY: queue is पढ़ोy to be used
 *	This is the state of a queue that has been fully configured (including
 *	SCD poपूर्णांकers, etc), has a specअगरic RA/TID asचिन्हित to it, and can be
 *	used to send traffic.
 * @IWL_MVM_QUEUE_SHARED: queue is shared, or in a process of becoming shared
 *	This is a state in which a single queue serves more than one TID, all of
 *	which are not aggregated. Note that the queue is only associated to one
 *	RA.
 */
क्रमागत iwl_mvm_queue_status अणु
	IWL_MVM_QUEUE_FREE,
	IWL_MVM_QUEUE_RESERVED,
	IWL_MVM_QUEUE_READY,
	IWL_MVM_QUEUE_SHARED,
पूर्ण;

#घोषणा IWL_MVM_DQA_QUEUE_TIMEOUT	(5 * HZ)
#घोषणा IWL_MVM_INVALID_QUEUE		0xFFFF

#घोषणा IWL_MVM_NUM_CIPHERS             10


काष्ठा iwl_mvm_txq अणु
	काष्ठा list_head list;
	u16 txq_id;
	atomic_t tx_request;
	bool stopped;
पूर्ण;

अटल अंतरभूत काष्ठा iwl_mvm_txq *
iwl_mvm_txq_from_mac80211(काष्ठा ieee80211_txq *txq)
अणु
	वापस (व्योम *)txq->drv_priv;
पूर्ण

अटल अंतरभूत काष्ठा iwl_mvm_txq *
iwl_mvm_txq_from_tid(काष्ठा ieee80211_sta *sta, u8 tid)
अणु
	अगर (tid == IWL_MAX_TID_COUNT)
		tid = IEEE80211_NUM_TIDS;

	वापस (व्योम *)sta->txq[tid]->drv_priv;
पूर्ण

/**
 * काष्ठा iwl_mvm_tvqm_txq_info - maps TVQM hw queue to tid
 *
 * @sta_id: sta id
 * @txq_tid: txq tid
 */
काष्ठा iwl_mvm_tvqm_txq_info अणु
	u8 sta_id;
	u8 txq_tid;
पूर्ण;

काष्ठा iwl_mvm_dqa_txq_info अणु
	u8 ra_sta_id; /* The RA this queue is mapped to, अगर exists */
	bool reserved; /* Is this the TXQ reserved क्रम a STA */
	u8 mac80211_ac; /* The mac80211 AC this queue is mapped to */
	u8 txq_tid; /* The TID "owner" of this queue*/
	u16 tid_biपंचांगap; /* Biपंचांगap of the TIDs mapped to this queue */
	/* Timestamp क्रम inactivation per TID of this queue */
	अचिन्हित दीर्घ last_frame_समय[IWL_MAX_TID_COUNT + 1];
	क्रमागत iwl_mvm_queue_status status;
पूर्ण;

काष्ठा iwl_mvm अणु
	/* क्रम logger access */
	काष्ठा device *dev;

	काष्ठा iwl_trans *trans;
	स्थिर काष्ठा iwl_fw *fw;
	स्थिर काष्ठा iwl_cfg *cfg;
	काष्ठा iwl_phy_db *phy_db;
	काष्ठा ieee80211_hw *hw;

	/* क्रम protecting access to iwl_mvm */
	काष्ठा mutex mutex;
	काष्ठा list_head async_handlers_list;
	spinlock_t async_handlers_lock;
	काष्ठा work_काष्ठा async_handlers_wk;

	काष्ठा work_काष्ठा roc_करोne_wk;

	अचिन्हित दीर्घ init_status;

	अचिन्हित दीर्घ status;

	u32 queue_sync_cookie;
	अचिन्हित दीर्घ queue_sync_state;
	/*
	 * क्रम beacon filtering -
	 * currently only one पूर्णांकerface can be supported
	 */
	काष्ठा iwl_mvm_vअगर *bf_allowed_vअगर;

	bool hw_रेजिस्टरed;
	bool rfसमाप्त_safe_init_करोne;

	u8 cca_40mhz_workaround;

	u32 ampdu_ref;
	bool ampdu_toggle;

	काष्ठा iwl_notअगर_रुको_data notअगर_रुको;

	जोड़ अणु
		काष्ठा mvm_statistics_rx_v3 rx_stats_v3;
		काष्ठा mvm_statistics_rx rx_stats;
	पूर्ण;

	काष्ठा अणु
		u64 rx_समय;
		u64 tx_समय;
		u64 on_समय_rf;
		u64 on_समय_scan;
	पूर्ण radio_stats, accu_radio_stats;

	काष्ठा list_head add_stream_txqs;
	जोड़ अणु
		काष्ठा iwl_mvm_dqa_txq_info queue_info[IWL_MAX_HW_QUEUES];
		काष्ठा iwl_mvm_tvqm_txq_info tvqm_info[IWL_MAX_TVQM_QUEUES];
	पूर्ण;
	काष्ठा work_काष्ठा add_stream_wk; /* To add streams to queues */

	स्थिर अक्षर *nvm_file_name;
	काष्ठा iwl_nvm_data *nvm_data;
	/* NVM sections */
	काष्ठा iwl_nvm_section nvm_sections[NVM_MAX_NUM_SECTIONS];

	काष्ठा iwl_fw_runसमय fwrt;

	/* EEPROM MAC addresses */
	काष्ठा mac_address addresses[IWL_MVM_MAX_ADDRESSES];

	/* data related to data path */
	काष्ठा iwl_rx_phy_info last_phy_info;
	काष्ठा ieee80211_sta __rcu *fw_id_to_mac_id[IWL_MVM_STATION_COUNT_MAX];
	u8 rx_ba_sessions;

	/* configured by mac80211 */
	u32 rts_threshold;

	/* Scan status, cmd (pre-allocated) and auxiliary station */
	अचिन्हित पूर्णांक scan_status;
	व्योम *scan_cmd;
	काष्ठा iwl_mcast_filter_cmd *mcast_filter_cmd;
	/* For CDB this is low band scan type, क्रम non-CDB - type. */
	क्रमागत iwl_mvm_scan_type scan_type;
	क्रमागत iwl_mvm_scan_type hb_scan_type;

	क्रमागत iwl_mvm_sched_scan_pass_all_states sched_scan_pass_all;
	काष्ठा delayed_work scan_समयout_dwork;

	/* max number of simultaneous scans the FW supports */
	अचिन्हित पूर्णांक max_scans;

	/* UMAC scan tracking */
	u32 scan_uid_status[IWL_MVM_MAX_UMAC_SCANS];

	/* start समय of last scan in TSF of the mac that requested the scan */
	u64 scan_start;

	/* the vअगर that requested the current scan */
	काष्ठा iwl_mvm_vअगर *scan_vअगर;

	/* rx chain antennas set through debugfs क्रम the scan command */
	u8 scan_rx_ant;

#अगर_घोषित CONFIG_IWLWIFI_BCAST_FILTERING
	/* broadcast filters to configure क्रम each associated station */
	स्थिर काष्ठा iwl_fw_bcast_filter *bcast_filters;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	काष्ठा अणु
		bool override;
		काष्ठा iwl_bcast_filter_cmd cmd;
	पूर्ण dbgfs_bcast_filtering;
#पूर्ण_अगर
#पूर्ण_अगर

	/* Internal station */
	काष्ठा iwl_mvm_पूर्णांक_sta aux_sta;
	काष्ठा iwl_mvm_पूर्णांक_sta snअगर_sta;

	bool last_ebs_successful;

	u8 scan_last_antenna_idx; /* to toggle TX between antennas */
	u8 mgmt_last_antenna_idx;

	/* last smart fअगरo state that was successfully sent to firmware */
	क्रमागत iwl_sf_state sf_state;

	/*
	 * Leave this poपूर्णांकer outside the अगरdef below so that it can be
	 * asचिन्हित without अगरdef in the source code.
	 */
	काष्ठा dentry *debugfs_dir;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	u32 dbgfs_sram_offset, dbgfs_sram_len;
	u32 dbgfs_prph_reg_addr;
	bool disable_घातer_off;
	bool disable_घातer_off_d3;
	bool beacon_inject_active;

	bool scan_iter_notअगर_enabled;

	काष्ठा debugfs_blob_wrapper nvm_hw_blob;
	काष्ठा debugfs_blob_wrapper nvm_sw_blob;
	काष्ठा debugfs_blob_wrapper nvm_calib_blob;
	काष्ठा debugfs_blob_wrapper nvm_prod_blob;
	काष्ठा debugfs_blob_wrapper nvm_phy_sku_blob;
	काष्ठा debugfs_blob_wrapper nvm_reg_blob;

	काष्ठा iwl_mvm_frame_stats drv_rx_stats;
	spinlock_t drv_stats_lock;
	u16 dbgfs_rx_phyinfo;
#पूर्ण_अगर

	काष्ठा iwl_mvm_phy_ctxt phy_ctxts[NUM_PHY_CTX];

	काष्ठा list_head समय_event_list;
	spinlock_t समय_event_lock;

	/*
	 * A biपंचांगap indicating the index of the key in use. The firmware
	 * can hold 16 keys at most. Reflect this fact.
	 */
	अचिन्हित दीर्घ fw_key_table[BITS_TO_LONGS(STA_KEY_MAX_NUM)];
	u8 fw_key_deleted[STA_KEY_MAX_NUM];

	u8 vअगर_count;
	काष्ठा ieee80211_vअगर __rcu *vअगर_id_to_mac[NUM_MAC_INDEX_DRIVER];

	/* -1 क्रम always, 0 क्रम never, >0 क्रम that many बार */
	s8 fw_restart;
	u8 *error_recovery_buf;

#अगर_घोषित CONFIG_IWLWIFI_LEDS
	काष्ठा led_classdev led;
#पूर्ण_अगर

	काष्ठा ieee80211_vअगर *p2p_device_vअगर;

#अगर_घोषित CONFIG_PM
	काष्ठा wiphy_wowlan_support wowlan;
	पूर्णांक gtk_ivlen, gtk_icvlen, ptk_ivlen, ptk_icvlen;

	/* sched scan settings क्रम net detect */
	काष्ठा ieee80211_scan_ies nd_ies;
	काष्ठा cfg80211_match_set *nd_match_sets;
	पूर्णांक n_nd_match_sets;
	काष्ठा ieee80211_channel **nd_channels;
	पूर्णांक n_nd_channels;
	bool net_detect;
	u8 offload_tid;
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
	bool d3_wake_sysनिश्चित;
	bool d3_test_active;
	u32 d3_test_pme_ptr;
	काष्ठा ieee80211_vअगर *keep_vअगर;
	u32 last_netdetect_scans; /* no. of scans in the last net-detect wake */
#पूर्ण_अगर
#पूर्ण_अगर

	रुको_queue_head_t rx_sync_रुकोq;

	/* BT-Coex */
	काष्ठा iwl_bt_coex_profile_notअगर last_bt_notअगर;
	काष्ठा iwl_bt_coex_ci_cmd last_bt_ci_cmd;

	u8 bt_tx_prio;
	क्रमागत iwl_bt_क्रमce_ant_mode bt_क्रमce_ant_mode;

	/* Aux ROC */
	काष्ठा list_head aux_roc_te_list;

	/* Thermal Throttling and CTसमाप्त */
	काष्ठा iwl_mvm_tt_mgmt thermal_throttle;
#अगर_घोषित CONFIG_THERMAL
	काष्ठा iwl_mvm_thermal_device tz_device;
	काष्ठा iwl_mvm_cooling_device cooling_dev;
#पूर्ण_अगर

	s32 temperature;	/* Celsius */
	/*
	 * Debug option to set the NIC temperature. This option makes the
	 * driver think this is the actual NIC temperature, and ignore the
	 * real temperature that is received from the fw
	 */
	bool temperature_test;  /* Debug test temperature is enabled */

	अचिन्हित दीर्घ bt_coex_last_tcm_ts;
	काष्ठा iwl_mvm_tcm tcm;

	u8 uapsd_noagg_bssid_ग_लिखो_idx;
	काष्ठा mac_address uapsd_noagg_bssids[IWL_MVM_UAPSD_NOAGG_BSSIDS_NUM]
		__aligned(2);

	काष्ठा iwl_समय_quota_cmd last_quota_cmd;

#अगर_घोषित CONFIG_NL80211_TESTMODE
	u32 noa_duration;
	काष्ठा ieee80211_vअगर *noa_vअगर;
#पूर्ण_अगर

	/* Tx queues */
	u16 aux_queue;
	u16 snअगर_queue;
	u16 probe_queue;
	u16 p2p_dev_queue;

	/* Indicate अगर device घातer save is allowed */
	u8 ps_disabled; /* u8 instead of bool to ease debugfs_create_* usage */
	/* Indicate अगर 32Khz बाह्यal घड़ी is valid */
	u32 ext_घड़ी_valid;

	काष्ठा ieee80211_vअगर __rcu *csa_vअगर;
	काष्ठा ieee80211_vअगर __rcu *csa_tx_blocked_vअगर;
	u8 csa_tx_block_bcn_समयout;

	/* प्रणाली समय of last beacon (क्रम AP/GO पूर्णांकerface) */
	u32 ap_last_beacon_gp2;

	/* indicates that we transmitted the last beacon */
	bool ibss_manager;

	bool lar_regकरोm_set;
	क्रमागत iwl_mcc_source mcc_src;

	/* TDLS channel चयन data */
	काष्ठा अणु
		काष्ठा delayed_work dwork;
		क्रमागत iwl_mvm_tdls_cs_state state;

		/*
		 * Current cs sta - might be dअगरferent from periodic cs peer
		 * station. Value is meaningless when the cs-state is idle.
		 */
		u8 cur_sta_id;

		/* TDLS periodic channel-चयन peer */
		काष्ठा अणु
			u8 sta_id;
			u8 op_class;
			bool initiator; /* are we the link initiator */
			काष्ठा cfg80211_chan_def chandef;
			काष्ठा sk_buff *skb; /* ch sw ढाँचा */
			u32 ch_sw_पंचांग_ie;

			/* बारtamp of last ch-sw request sent (GP2 समय) */
			u32 sent_बारtamp;
		पूर्ण peer;
	पूर्ण tdls_cs;


	u32 ciphers[IWL_MVM_NUM_CIPHERS];
	काष्ठा ieee80211_cipher_scheme cs[IWL_UCODE_MAX_CS];

	काष्ठा cfg80211_fपंचांग_responder_stats fपंचांग_resp_stats;
	काष्ठा अणु
		काष्ठा cfg80211_pmsr_request *req;
		काष्ठा wireless_dev *req_wdev;
		काष्ठा list_head loc_list;
		पूर्णांक responses[IWL_MVM_TOF_MAX_APS];
		काष्ठा अणु
			काष्ठा list_head resp;
		पूर्ण smooth;
		काष्ठा list_head pasn_list;
	पूर्ण fपंचांग_initiator;

	काष्ठा list_head resp_pasn_list;

	काष्ठा अणु
		u8 d0i3_resp;
		u8 range_resp;
	पूर्ण cmd_ver;

	काष्ठा ieee80211_vअगर *nan_vअगर;
#घोषणा IWL_MAX_BAID	32
	काष्ठा iwl_mvm_baid_data __rcu *baid_map[IWL_MAX_BAID];

	/*
	 * Drop beacons from other APs in AP mode when there are no connected
	 * clients.
	 */
	bool drop_bcn_ap_mode;

	काष्ठा delayed_work cs_tx_unblock_dwork;

	/* करोes a monitor vअगर exist (only one can exist hence bool) */
	bool monitor_on;

	/* snअगरfer data to include in radiotap */
	__le16 cur_aid;
	u8 cur_bssid[ETH_ALEN];

	अचिन्हित दीर्घ last_6ghz_passive_scan_jअगरfies;
	अचिन्हित दीर्घ last_reset_or_resume_समय_jअगरfies;
पूर्ण;

/* Extract MVM priv from op_mode and _hw */
#घोषणा IWL_OP_MODE_GET_MVM(_iwl_op_mode)		\
	((काष्ठा iwl_mvm *)(_iwl_op_mode)->op_mode_specअगरic)

#घोषणा IWL_MAC80211_GET_MVM(_hw)			\
	IWL_OP_MODE_GET_MVM((काष्ठा iwl_op_mode *)((_hw)->priv))

/**
 * क्रमागत iwl_mvm_status - MVM status bits
 * @IWL_MVM_STATUS_HW_RFKILL: HW RF-समाप्त is निश्चितed
 * @IWL_MVM_STATUS_HW_CTKILL: CT-समाप्त is active
 * @IWL_MVM_STATUS_ROC_RUNNING: reमुख्य-on-channel is running
 * @IWL_MVM_STATUS_HW_RESTART_REQUESTED: HW restart was requested
 * @IWL_MVM_STATUS_IN_HW_RESTART: HW restart is active
 * @IWL_MVM_STATUS_ROC_AUX_RUNNING: AUX reमुख्य-on-channel is running
 * @IWL_MVM_STATUS_FIRMWARE_RUNNING: firmware is running
 * @IWL_MVM_STATUS_NEED_FLUSH_P2P: need to flush P2P bcast STA
 * @IWL_MVM_STATUS_IN_D3: in D3 (or at least about to go पूर्णांकo it)
 */
क्रमागत iwl_mvm_status अणु
	IWL_MVM_STATUS_HW_RFKILL,
	IWL_MVM_STATUS_HW_CTKILL,
	IWL_MVM_STATUS_ROC_RUNNING,
	IWL_MVM_STATUS_HW_RESTART_REQUESTED,
	IWL_MVM_STATUS_IN_HW_RESTART,
	IWL_MVM_STATUS_ROC_AUX_RUNNING,
	IWL_MVM_STATUS_FIRMWARE_RUNNING,
	IWL_MVM_STATUS_NEED_FLUSH_P2P,
	IWL_MVM_STATUS_IN_D3,
पूर्ण;

/* Keep track of completed init configuration */
क्रमागत iwl_mvm_init_status अणु
	IWL_MVM_INIT_STATUS_THERMAL_INIT_COMPLETE = BIT(0),
	IWL_MVM_INIT_STATUS_LEDS_INIT_COMPLETE = BIT(1),
पूर्ण;

अटल अंतरभूत bool iwl_mvm_is_radio_समाप्तed(काष्ठा iwl_mvm *mvm)
अणु
	वापस test_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status) ||
	       test_bit(IWL_MVM_STATUS_HW_CTKILL, &mvm->status);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_radio_hw_समाप्तed(काष्ठा iwl_mvm *mvm)
अणु
	वापस test_bit(IWL_MVM_STATUS_HW_RFKILL, &mvm->status);
पूर्ण

अटल अंतरभूत bool iwl_mvm_firmware_running(काष्ठा iwl_mvm *mvm)
अणु
	वापस test_bit(IWL_MVM_STATUS_FIRMWARE_RUNNING, &mvm->status);
पूर्ण

/* Must be called with rcu_पढ़ो_lock() held and it can only be
 * released when mvmsta is not needed anymore.
 */
अटल अंतरभूत काष्ठा iwl_mvm_sta *
iwl_mvm_sta_from_staid_rcu(काष्ठा iwl_mvm *mvm, u8 sta_id)
अणु
	काष्ठा ieee80211_sta *sta;

	अगर (sta_id >= mvm->fw->ucode_capa.num_stations)
		वापस शून्य;

	sta = rcu_dereference(mvm->fw_id_to_mac_id[sta_id]);

	/* This can happen अगर the station has been हटाओd right now */
	अगर (IS_ERR_OR_शून्य(sta))
		वापस शून्य;

	वापस iwl_mvm_sta_from_mac80211(sta);
पूर्ण

अटल अंतरभूत काष्ठा iwl_mvm_sta *
iwl_mvm_sta_from_staid_रक्षित(काष्ठा iwl_mvm *mvm, u8 sta_id)
अणु
	काष्ठा ieee80211_sta *sta;

	अगर (sta_id >= mvm->fw->ucode_capa.num_stations)
		वापस शून्य;

	sta = rcu_dereference_रक्षित(mvm->fw_id_to_mac_id[sta_id],
					lockdep_is_held(&mvm->mutex));

	/* This can happen अगर the station has been हटाओd right now */
	अगर (IS_ERR_OR_शून्य(sta))
		वापस शून्य;

	वापस iwl_mvm_sta_from_mac80211(sta);
पूर्ण

अटल अंतरभूत काष्ठा ieee80211_vअगर *
iwl_mvm_rcu_dereference_vअगर_id(काष्ठा iwl_mvm *mvm, u8 vअगर_id, bool rcu)
अणु
	अगर (WARN_ON(vअगर_id >= ARRAY_SIZE(mvm->vअगर_id_to_mac)))
		वापस शून्य;

	अगर (rcu)
		वापस rcu_dereference(mvm->vअगर_id_to_mac[vअगर_id]);

	वापस rcu_dereference_रक्षित(mvm->vअगर_id_to_mac[vअगर_id],
					 lockdep_is_held(&mvm->mutex));
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_adaptive_dwell_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_ADAPTIVE_DWELL);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_adaptive_dwell_v2_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_ADAPTIVE_DWELL_V2);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_adwell_hb_ap_num_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_ADWELL_HB_DEF_N_AP);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_oce_supported(काष्ठा iwl_mvm *mvm)
अणु
	/* OCE should never be enabled क्रम LMAC scan FWs */
	वापस fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_OCE);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_frag_ebs_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa, IWL_UCODE_TLV_API_FRAG_EBS);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_लघु_beacon_notअगर_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_SHORT_BEACON_NOTIF);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_dqa_data_queue(काष्ठा iwl_mvm *mvm, u8 queue)
अणु
	वापस (queue >= IWL_MVM_DQA_MIN_DATA_QUEUE) &&
	       (queue <= IWL_MVM_DQA_MAX_DATA_QUEUE);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_dqa_mgmt_queue(काष्ठा iwl_mvm *mvm, u8 queue)
अणु
	वापस (queue >= IWL_MVM_DQA_MIN_MGMT_QUEUE) &&
	       (queue <= IWL_MVM_DQA_MAX_MGMT_QUEUE);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_lar_supported(काष्ठा iwl_mvm *mvm)
अणु
	bool nvm_lar = mvm->nvm_data->lar_enabled;
	bool tlv_lar = fw_has_capa(&mvm->fw->ucode_capa,
				   IWL_UCODE_TLV_CAPA_LAR_SUPPORT);

	/*
	 * Enable LAR only अगर it is supported by the FW (TLV) &&
	 * enabled in the NVM
	 */
	अगर (mvm->cfg->nvm_type == IWL_NVM_EXT)
		वापस nvm_lar && tlv_lar;
	अन्यथा
		वापस tlv_lar;
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_wअगरi_mcc_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_WIFI_MCC_UPDATE) ||
	       fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_LAR_MULTI_MCC);
पूर्ण

अटल अंतरभूत bool iwl_mvm_bt_is_rrc_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_BT_COEX_RRC) &&
		IWL_MVM_BT_COEX_RRC;
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_csum_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_CSUM_SUPPORT) &&
               !IWL_MVM_HW_CSUM_DISABLE;
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_mplut_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_BT_MPLUT_SUPPORT) &&
		IWL_MVM_BT_COEX_MPLUT;
पूर्ण

अटल अंतरभूत
bool iwl_mvm_is_p2p_scm_uapsd_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_P2P_SCM_UAPSD) &&
		!(iwlwअगरi_mod_params.uapsd_disable &
		  IWL_DISABLE_UAPSD_P2P_CLIENT);
पूर्ण

अटल अंतरभूत bool iwl_mvm_has_new_rx_api(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_MULTI_QUEUE_RX_SUPPORT);
पूर्ण

अटल अंतरभूत bool iwl_mvm_has_new_tx_api(काष्ठा iwl_mvm *mvm)
अणु
	/* TODO - replace with TLV once defined */
	वापस mvm->trans->trans_cfg->use_tfh;
पूर्ण

अटल अंतरभूत bool iwl_mvm_has_unअगरied_ucode(काष्ठा iwl_mvm *mvm)
अणु
	/* TODO - better define this */
	वापस mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000;
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_cdb_supported(काष्ठा iwl_mvm *mvm)
अणु
	/*
	 * TODO:
	 * The issue of how to determine CDB APIs and usage is still not fully
	 * defined.
	 * There is a compilation क्रम CDB and non-CDB FW, but there may
	 * be also runसमय check.
	 * For now there is a TLV क्रम checking compilation mode, but a
	 * runसमय check will also have to be here - once defined.
	 */
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_CDB_SUPPORT);
पूर्ण

अटल अंतरभूत bool iwl_mvm_cdb_scan_api(काष्ठा iwl_mvm *mvm)
अणु
	/*
	 * TODO: should this be the same as iwl_mvm_is_cdb_supported()?
	 * but then there's a little bit of code in scan that won't make
	 * any sense...
	 */
	वापस mvm->trans->trans_cfg->device_family >= IWL_DEVICE_FAMILY_22000;
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_scan_ext_chan_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_SCAN_EXT_CHAN_VER);
पूर्ण


अटल अंतरभूत bool iwl_mvm_is_reduced_config_scan_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_REDUCED_SCAN_CONFIG);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_band_in_rx_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_API_BAND_IN_RX_DATA);
पूर्ण

अटल अंतरभूत bool iwl_mvm_has_new_rx_stats_api(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_NEW_RX_STATS);
पूर्ण

अटल अंतरभूत bool iwl_mvm_has_quota_low_latency(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_api(&mvm->fw->ucode_capa,
			  IWL_UCODE_TLV_API_QUOTA_LOW_LATENCY);
पूर्ण

अटल अंतरभूत bool iwl_mvm_has_tlc_offload(स्थिर काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_TLC_OFFLOAD);
पूर्ण

अटल अंतरभूत काष्ठा agg_tx_status *
iwl_mvm_get_agg_status(काष्ठा iwl_mvm *mvm, व्योम *tx_resp)
अणु
	अगर (iwl_mvm_has_new_tx_api(mvm))
		वापस &((काष्ठा iwl_mvm_tx_resp *)tx_resp)->status;
	अन्यथा
		वापस ((काष्ठा iwl_mvm_tx_resp_v3 *)tx_resp)->status;
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_tt_in_fw(काष्ठा iwl_mvm *mvm)
अणु
	/* these two TLV are redundant since the responsibility to CT-समाप्त by
	 * FW happens only after we send at least one command of
	 * temperature THs report.
	 */
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_CT_KILL_BY_FW) &&
	       fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_TEMP_THS_REPORT_SUPPORT);
पूर्ण

अटल अंतरभूत bool iwl_mvm_is_ctdp_supported(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_CTDP_SUPPORT);
पूर्ण

बाह्य स्थिर u8 iwl_mvm_ac_to_tx_fअगरo[];
बाह्य स्थिर u8 iwl_mvm_ac_to_gen2_tx_fअगरo[];

अटल अंतरभूत u8 iwl_mvm_mac_ac_to_tx_fअगरo(काष्ठा iwl_mvm *mvm,
					   क्रमागत ieee80211_ac_numbers ac)
अणु
	वापस iwl_mvm_has_new_tx_api(mvm) ?
		iwl_mvm_ac_to_gen2_tx_fअगरo[ac] : iwl_mvm_ac_to_tx_fअगरo[ac];
पूर्ण

काष्ठा iwl_rate_info अणु
	u8 plcp;	/* uCode API:  IWL_RATE_6M_PLCP, etc. */
	u8 plcp_siso;	/* uCode API:  IWL_RATE_SISO_6M_PLCP, etc. */
	u8 plcp_mimo2;	/* uCode API:  IWL_RATE_MIMO2_6M_PLCP, etc. */
	u8 plcp_mimo3;  /* uCode API:  IWL_RATE_MIMO3_6M_PLCP, etc. */
	u8 ieee;	/* MAC header:  IWL_RATE_6M_IEEE, etc. */
पूर्ण;

व्योम __iwl_mvm_mac_stop(काष्ठा iwl_mvm *mvm);
पूर्णांक __iwl_mvm_mac_start(काष्ठा iwl_mvm *mvm);

/******************
 * MVM Methods
 ******************/
/* uCode */
पूर्णांक iwl_run_init_mvm_ucode(काष्ठा iwl_mvm *mvm);

/* Utils */
पूर्णांक iwl_mvm_legacy_rate_to_mac80211_idx(u32 rate_n_flags,
					क्रमागत nl80211_band band);
व्योम iwl_mvm_hwrate_to_tx_rate(u32 rate_n_flags,
			       क्रमागत nl80211_band band,
			       काष्ठा ieee80211_tx_rate *r);
u8 iwl_mvm_mac80211_idx_to_hwrate(पूर्णांक rate_idx);
u8 iwl_mvm_mac80211_ac_to_ucode_ac(क्रमागत ieee80211_ac_numbers ac);
व्योम iwl_mvm_dump_nic_error_log(काष्ठा iwl_mvm *mvm);
u8 first_antenna(u8 mask);
u8 iwl_mvm_next_antenna(काष्ठा iwl_mvm *mvm, u8 valid, u8 last_idx);
व्योम iwl_mvm_get_sync_समय(काष्ठा iwl_mvm *mvm, u32 *gp2, u64 *bootसमय);
u32 iwl_mvm_get_sysसमय(काष्ठा iwl_mvm *mvm);

/* Tx / Host Commands */
पूर्णांक __must_check iwl_mvm_send_cmd(काष्ठा iwl_mvm *mvm,
				  काष्ठा iwl_host_cmd *cmd);
पूर्णांक __must_check iwl_mvm_send_cmd_pdu(काष्ठा iwl_mvm *mvm, u32 id,
				      u32 flags, u16 len, स्थिर व्योम *data);
पूर्णांक __must_check iwl_mvm_send_cmd_status(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_host_cmd *cmd,
					 u32 *status);
पूर्णांक __must_check iwl_mvm_send_cmd_pdu_status(काष्ठा iwl_mvm *mvm, u32 id,
					     u16 len, स्थिर व्योम *data,
					     u32 *status);
पूर्णांक iwl_mvm_tx_skb_sta(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
		       काष्ठा ieee80211_sta *sta);
पूर्णांक iwl_mvm_tx_skb_non_sta(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb);
व्योम iwl_mvm_set_tx_cmd(काष्ठा iwl_mvm *mvm, काष्ठा sk_buff *skb,
			काष्ठा iwl_tx_cmd *tx_cmd,
			काष्ठा ieee80211_tx_info *info, u8 sta_id);
व्योम iwl_mvm_set_tx_cmd_rate(काष्ठा iwl_mvm *mvm, काष्ठा iwl_tx_cmd *tx_cmd,
			    काष्ठा ieee80211_tx_info *info,
			    काष्ठा ieee80211_sta *sta, __le16 fc);
व्योम iwl_mvm_mac_itxq_xmit(काष्ठा ieee80211_hw *hw, काष्ठा ieee80211_txq *txq);
अचिन्हित पूर्णांक iwl_mvm_max_amsdu_size(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_sta *sta,
				    अचिन्हित पूर्णांक tid);

#अगर_घोषित CONFIG_IWLWIFI_DEBUG
स्थिर अक्षर *iwl_mvm_get_tx_fail_reason(u32 status);
#अन्यथा
अटल अंतरभूत स्थिर अक्षर *iwl_mvm_get_tx_fail_reason(u32 status) अणु वापस ""; पूर्ण
#पूर्ण_अगर
पूर्णांक iwl_mvm_flush_tx_path(काष्ठा iwl_mvm *mvm, u32 tfd_msk);
पूर्णांक iwl_mvm_flush_sta(काष्ठा iwl_mvm *mvm, व्योम *sta, bool पूर्णांकernal);
पूर्णांक iwl_mvm_flush_sta_tids(काष्ठा iwl_mvm *mvm, u32 sta_id, u16 tids);

व्योम iwl_mvm_async_handlers_purge(काष्ठा iwl_mvm *mvm);

अटल अंतरभूत व्योम iwl_mvm_set_tx_cmd_ccmp(काष्ठा ieee80211_tx_info *info,
					   काष्ठा iwl_tx_cmd *tx_cmd)
अणु
	काष्ठा ieee80211_key_conf *keyconf = info->control.hw_key;

	tx_cmd->sec_ctl = TX_CMD_SEC_CCM;
	स_नकल(tx_cmd->key, keyconf->key, keyconf->keylen);
पूर्ण

अटल अंतरभूत व्योम iwl_mvm_रुको_क्रम_async_handlers(काष्ठा iwl_mvm *mvm)
अणु
	flush_work(&mvm->async_handlers_wk);
पूर्ण

/* Statistics */
व्योम iwl_mvm_handle_rx_statistics(काष्ठा iwl_mvm *mvm,
				  काष्ठा iwl_rx_packet *pkt);
व्योम iwl_mvm_rx_statistics(काष्ठा iwl_mvm *mvm,
			   काष्ठा iwl_rx_cmd_buffer *rxb);
पूर्णांक iwl_mvm_request_statistics(काष्ठा iwl_mvm *mvm, bool clear);
व्योम iwl_mvm_accu_radio_stats(काष्ठा iwl_mvm *mvm);

/* NVM */
पूर्णांक iwl_nvm_init(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_load_nvm_to_nic(काष्ठा iwl_mvm *mvm);

अटल अंतरभूत u8 iwl_mvm_get_valid_tx_ant(काष्ठा iwl_mvm *mvm)
अणु
	वापस mvm->nvm_data && mvm->nvm_data->valid_tx_ant ?
	       mvm->fw->valid_tx_ant & mvm->nvm_data->valid_tx_ant :
	       mvm->fw->valid_tx_ant;
पूर्ण

अटल अंतरभूत u8 iwl_mvm_get_valid_rx_ant(काष्ठा iwl_mvm *mvm)
अणु
	वापस mvm->nvm_data && mvm->nvm_data->valid_rx_ant ?
	       mvm->fw->valid_rx_ant & mvm->nvm_data->valid_rx_ant :
	       mvm->fw->valid_rx_ant;
पूर्ण

अटल अंतरभूत व्योम iwl_mvm_toggle_tx_ant(काष्ठा iwl_mvm *mvm, u8 *ant)
अणु
	*ant = iwl_mvm_next_antenna(mvm, iwl_mvm_get_valid_tx_ant(mvm), *ant);
पूर्ण

अटल अंतरभूत u32 iwl_mvm_get_phy_config(काष्ठा iwl_mvm *mvm)
अणु
	u32 phy_config = ~(FW_PHY_CFG_TX_CHAIN |
			   FW_PHY_CFG_RX_CHAIN);
	u32 valid_rx_ant = iwl_mvm_get_valid_rx_ant(mvm);
	u32 valid_tx_ant = iwl_mvm_get_valid_tx_ant(mvm);

	phy_config |= valid_tx_ant << FW_PHY_CFG_TX_CHAIN_POS |
		      valid_rx_ant << FW_PHY_CFG_RX_CHAIN_POS;

	वापस mvm->fw->phy_config & phy_config;
पूर्ण

पूर्णांक iwl_mvm_up(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_load_d3_fw(काष्ठा iwl_mvm *mvm);

पूर्णांक iwl_mvm_mac_setup_रेजिस्टर(काष्ठा iwl_mvm *mvm);
bool iwl_mvm_bcast_filter_build_cmd(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_bcast_filter_cmd *cmd);

/*
 * FW notअगरications / CMD responses handlers
 * Convention: iwl_mvm_rx_<NAME OF THE CMD>
 */
व्योम iwl_mvm_rx_mq(काष्ठा iwl_op_mode *op_mode,
		   काष्ठा napi_काष्ठा *napi,
		   काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_rx_phy_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_rx_mpdu(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
			काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_mpdu_mq(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
			काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue);
व्योम iwl_mvm_rx_monitor_no_data(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
				काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue);
व्योम iwl_mvm_rx_frame_release(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
			      काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue);
व्योम iwl_mvm_rx_bar_frame_release(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
				  काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue);
व्योम iwl_mvm_rx_queue_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा napi_काष्ठा *napi,
			    काष्ठा iwl_rx_cmd_buffer *rxb, पूर्णांक queue);
व्योम iwl_mvm_rx_tx_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_mfu_निश्चित_dump_notअगर(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_send_recovery_cmd(काष्ठा iwl_mvm *mvm, u32 flags);
व्योम iwl_mvm_rx_ba_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_ant_coupling_notअगर(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_fw_error(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_card_state_notअगर(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_mfuart_notअगर(काष्ठा iwl_mvm *mvm,
			     काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_shared_mem_cfg_notअगर(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_rx_cmd_buffer *rxb);

/* MVM PHY */
पूर्णांक iwl_mvm_phy_ctxt_add(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_phy_ctxt *ctxt,
			 काष्ठा cfg80211_chan_def *chandef,
			 u8 chains_अटल, u8 chains_dynamic);
पूर्णांक iwl_mvm_phy_ctxt_changed(काष्ठा iwl_mvm *mvm, काष्ठा iwl_mvm_phy_ctxt *ctxt,
			     काष्ठा cfg80211_chan_def *chandef,
			     u8 chains_अटल, u8 chains_dynamic);
व्योम iwl_mvm_phy_ctxt_ref(काष्ठा iwl_mvm *mvm,
			  काष्ठा iwl_mvm_phy_ctxt *ctxt);
व्योम iwl_mvm_phy_ctxt_unref(काष्ठा iwl_mvm *mvm,
			    काष्ठा iwl_mvm_phy_ctxt *ctxt);
पूर्णांक iwl_mvm_phy_ctx_count(काष्ठा iwl_mvm *mvm);
u8 iwl_mvm_get_channel_width(काष्ठा cfg80211_chan_def *chandef);
u8 iwl_mvm_get_ctrl_pos(काष्ठा cfg80211_chan_def *chandef);

/* MAC (भव पूर्णांकerface) programming */
पूर्णांक iwl_mvm_mac_ctxt_init(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_mac_ctxt_add(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_mac_ctxt_changed(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     bool क्रमce_assoc_off, स्थिर u8 *bssid_override);
पूर्णांक iwl_mvm_mac_ctxt_हटाओ(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_mac_ctxt_beacon_changed(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_mac_ctxt_send_beacon(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 काष्ठा sk_buff *beacon);
पूर्णांक iwl_mvm_mac_ctxt_send_beacon_cmd(काष्ठा iwl_mvm *mvm,
				     काष्ठा sk_buff *beacon,
				     व्योम *data, पूर्णांक len);
u8 iwl_mvm_mac_ctxt_get_lowest_rate(काष्ठा ieee80211_tx_info *info,
				    काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_mac_ctxt_set_tim(काष्ठा iwl_mvm *mvm,
			      __le32 *tim_index, __le32 *tim_size,
			      u8 *beacon, u32 frame_size);
व्योम iwl_mvm_rx_beacon_notअगर(काष्ठा iwl_mvm *mvm,
			     काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_missed_beacons_notअगर(काष्ठा iwl_mvm *mvm,
				     काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_stored_beacon_notअगर(काष्ठा iwl_mvm *mvm,
				    काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_mu_mimo_grp_notअगर(काष्ठा iwl_mvm *mvm,
			       काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_sta_pm_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_winकरोw_status_notअगर(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_mac_ctxt_recalc_tsf_id(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_probe_resp_data_notअगर(काष्ठा iwl_mvm *mvm,
				   काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_missed_vap_notअगर(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_channel_चयन_noa_notअगर(काष्ठा iwl_mvm *mvm,
				      काष्ठा iwl_rx_cmd_buffer *rxb);
/* Bindings */
पूर्णांक iwl_mvm_binding_add_vअगर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_binding_हटाओ_vअगर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);

/* Quota management */
अटल अंतरभूत माप_प्रकार iwl_mvm_quota_cmd_size(काष्ठा iwl_mvm *mvm)
अणु
	वापस iwl_mvm_has_quota_low_latency(mvm) ?
		माप(काष्ठा iwl_समय_quota_cmd) :
		माप(काष्ठा iwl_समय_quota_cmd_v1);
पूर्ण

अटल अंतरभूत काष्ठा iwl_समय_quota_data
*iwl_mvm_quota_cmd_get_quota(काष्ठा iwl_mvm *mvm,
			     काष्ठा iwl_समय_quota_cmd *cmd,
			     पूर्णांक i)
अणु
	काष्ठा iwl_समय_quota_data_v1 *quotas;

	अगर (iwl_mvm_has_quota_low_latency(mvm))
		वापस &cmd->quotas[i];

	quotas = (काष्ठा iwl_समय_quota_data_v1 *)cmd->quotas;
	वापस (काष्ठा iwl_समय_quota_data *)&quotas[i];
पूर्ण

पूर्णांक iwl_mvm_update_quotas(काष्ठा iwl_mvm *mvm, bool क्रमce_upload,
			  काष्ठा ieee80211_vअगर *disabled_vअगर);

/* Scanning */
पूर्णांक iwl_mvm_reg_scan_start(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			   काष्ठा cfg80211_scan_request *req,
			   काष्ठा ieee80211_scan_ies *ies);
पूर्णांक iwl_mvm_scan_size(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_scan_stop(काष्ठा iwl_mvm *mvm, पूर्णांक type, bool notअगरy);
पूर्णांक iwl_mvm_max_scan_ie_len(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_report_scan_पातed(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_scan_समयout_wk(काष्ठा work_काष्ठा *work);

/* Scheduled scan */
व्योम iwl_mvm_rx_lmac_scan_complete_notअगर(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_lmac_scan_iter_complete_notअगर(काष्ठा iwl_mvm *mvm,
					      काष्ठा iwl_rx_cmd_buffer *rxb);
पूर्णांक iwl_mvm_sched_scan_start(काष्ठा iwl_mvm *mvm,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा cfg80211_sched_scan_request *req,
			     काष्ठा ieee80211_scan_ies *ies,
			     पूर्णांक type);
व्योम iwl_mvm_rx_scan_match_found(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb);

/* UMAC scan */
पूर्णांक iwl_mvm_config_scan(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_rx_umac_scan_complete_notअगर(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_rx_umac_scan_iter_complete_notअगर(काष्ठा iwl_mvm *mvm,
					      काष्ठा iwl_rx_cmd_buffer *rxb);

/* MVM debugfs */
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
व्योम iwl_mvm_dbgfs_रेजिस्टर(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_vअगर_dbgfs_रेजिस्टर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_vअगर_dbgfs_clean(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
#अन्यथा
अटल अंतरभूत व्योम iwl_mvm_dbgfs_रेजिस्टर(काष्ठा iwl_mvm *mvm)
अणु
पूर्ण
अटल अंतरभूत व्योम
iwl_mvm_vअगर_dbgfs_रेजिस्टर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
पूर्ण
अटल अंतरभूत व्योम
iwl_mvm_vअगर_dbgfs_clean(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
पूर्ण
#पूर्ण_अगर /* CONFIG_IWLWIFI_DEBUGFS */

/* rate scaling */
पूर्णांक iwl_mvm_send_lq_cmd(काष्ठा iwl_mvm *mvm, काष्ठा iwl_lq_cmd *lq);
व्योम iwl_mvm_update_frame_stats(काष्ठा iwl_mvm *mvm, u32 rate, bool agg);
पूर्णांक rs_pretty_prपूर्णांक_rate(अक्षर *buf, पूर्णांक bufsz, स्थिर u32 rate);
व्योम rs_update_last_rssi(काष्ठा iwl_mvm *mvm,
			 काष्ठा iwl_mvm_sta *mvmsta,
			 काष्ठा ieee80211_rx_status *rx_status);

/* घातer management */
पूर्णांक iwl_mvm_घातer_update_device(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_घातer_update_mac(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_घातer_update_ps(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_घातer_mac_dbgfs_पढ़ो(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				 अक्षर *buf, पूर्णांक bufsz);

व्योम iwl_mvm_घातer_vअगर_assoc(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_घातer_uapsd_misbehaving_ap_notअगर(काष्ठा iwl_mvm *mvm,
					      काष्ठा iwl_rx_cmd_buffer *rxb);

#अगर_घोषित CONFIG_IWLWIFI_LEDS
पूर्णांक iwl_mvm_leds_init(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_leds_निकास(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_leds_sync(काष्ठा iwl_mvm *mvm);
#अन्यथा
अटल अंतरभूत पूर्णांक iwl_mvm_leds_init(काष्ठा iwl_mvm *mvm)
अणु
	वापस 0;
पूर्ण
अटल अंतरभूत व्योम iwl_mvm_leds_निकास(काष्ठा iwl_mvm *mvm)
अणु
पूर्ण
अटल अंतरभूत व्योम iwl_mvm_leds_sync(काष्ठा iwl_mvm *mvm)
अणु
पूर्ण
#पूर्ण_अगर

/* D3 (WoWLAN, NetDetect) */
पूर्णांक iwl_mvm_suspend(काष्ठा ieee80211_hw *hw, काष्ठा cfg80211_wowlan *wowlan);
पूर्णांक iwl_mvm_resume(काष्ठा ieee80211_hw *hw);
व्योम iwl_mvm_set_wakeup(काष्ठा ieee80211_hw *hw, bool enabled);
व्योम iwl_mvm_set_rekey_data(काष्ठा ieee80211_hw *hw,
			    काष्ठा ieee80211_vअगर *vअगर,
			    काष्ठा cfg80211_gtk_rekey_data *data);
व्योम iwl_mvm_ipv6_addr_change(काष्ठा ieee80211_hw *hw,
			      काष्ठा ieee80211_vअगर *vअगर,
			      काष्ठा inet6_dev *idev);
व्योम iwl_mvm_set_शेष_unicast_key(काष्ठा ieee80211_hw *hw,
				     काष्ठा ieee80211_vअगर *vअगर, पूर्णांक idx);
बाह्य स्थिर काष्ठा file_operations iwl_dbgfs_d3_test_ops;
काष्ठा iwl_wowlan_status *iwl_mvm_send_wowlan_get_status(काष्ठा iwl_mvm *mvm);
#अगर_घोषित CONFIG_PM
व्योम iwl_mvm_set_last_nonqos_seq(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर);
#अन्यथा
अटल अंतरभूत व्योम
iwl_mvm_set_last_nonqos_seq(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर)
अणु
पूर्ण
#पूर्ण_अगर
व्योम iwl_mvm_set_wowlan_qos_seq(काष्ठा iwl_mvm_sta *mvm_ap_sta,
				काष्ठा iwl_wowlan_config_cmd *cmd);
पूर्णांक iwl_mvm_send_proto_offload(काष्ठा iwl_mvm *mvm,
			       काष्ठा ieee80211_vअगर *vअगर,
			       bool disable_offloading,
			       bool offload_ns,
			       u32 cmd_flags);

/* BT Coex */
पूर्णांक iwl_mvm_send_bt_init_conf(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_rx_bt_coex_notअगर(काष्ठा iwl_mvm *mvm,
			      काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_bt_rssi_event(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			   क्रमागत ieee80211_rssi_event_data);
व्योम iwl_mvm_bt_coex_vअगर_change(काष्ठा iwl_mvm *mvm);
u16 iwl_mvm_coex_agg_समय_limit(काष्ठा iwl_mvm *mvm,
				काष्ठा ieee80211_sta *sta);
bool iwl_mvm_bt_coex_is_mimo_allowed(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_sta *sta);
bool iwl_mvm_bt_coex_is_ant_avail(काष्ठा iwl_mvm *mvm, u8 ant);
bool iwl_mvm_bt_coex_is_shared_ant_avail(काष्ठा iwl_mvm *mvm);
bool iwl_mvm_bt_coex_is_tpc_allowed(काष्ठा iwl_mvm *mvm,
				    क्रमागत nl80211_band band);
u8 iwl_mvm_bt_coex_get_single_ant_msk(काष्ठा iwl_mvm *mvm, u8 enabled_ants);
u8 iwl_mvm_bt_coex_tx_prio(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_hdr *hdr,
			   काष्ठा ieee80211_tx_info *info, u8 ac);

/* beacon filtering */
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
व्योम
iwl_mvm_beacon_filter_debugfs_parameters(काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा iwl_beacon_filter_cmd *cmd);
#अन्यथा
अटल अंतरभूत व्योम
iwl_mvm_beacon_filter_debugfs_parameters(काष्ठा ieee80211_vअगर *vअगर,
					 काष्ठा iwl_beacon_filter_cmd *cmd)
अणुपूर्ण
#पूर्ण_अगर
पूर्णांक iwl_mvm_enable_beacon_filter(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर,
				 u32 flags);
पूर्णांक iwl_mvm_disable_beacon_filter(काष्ठा iwl_mvm *mvm,
				  काष्ठा ieee80211_vअगर *vअगर,
				  u32 flags);
/* SMPS */
व्योम iwl_mvm_update_smps(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
				क्रमागत iwl_mvm_smps_type_request req_type,
				क्रमागत ieee80211_smps_mode smps_request);
bool iwl_mvm_rx_भागersity_allowed(काष्ठा iwl_mvm *mvm);

/* Low latency */
पूर्णांक iwl_mvm_update_low_latency(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			      bool low_latency,
			      क्रमागत iwl_mvm_low_latency_cause cause);
/* get SystemLowLatencyMode - only needed क्रम beacon threshold? */
bool iwl_mvm_low_latency(काष्ठा iwl_mvm *mvm);
bool iwl_mvm_low_latency_band(काष्ठा iwl_mvm *mvm, क्रमागत nl80211_band band);
व्योम iwl_mvm_send_low_latency_cmd(काष्ठा iwl_mvm *mvm, bool low_latency,
				  u16 mac_id);

/* get VMACLowLatencyMode */
अटल अंतरभूत bool iwl_mvm_vअगर_low_latency(काष्ठा iwl_mvm_vअगर *mvmvअगर)
अणु
	/*
	 * should this consider associated/active/... state?
	 *
	 * Normally low-latency should only be active on पूर्णांकerfaces
	 * that are active, but at least with debugfs it can also be
	 * enabled on पूर्णांकerfaces that aren't active. However, when
	 * पूर्णांकerface aren't active then they aren't added पूर्णांकo the
	 * binding, so this has no real impact. For now, just वापस
	 * the current desired low-latency state.
	 */
	वापस mvmvअगर->low_latency_actual;
पूर्ण

अटल अंतरभूत
व्योम iwl_mvm_vअगर_set_low_latency(काष्ठा iwl_mvm_vअगर *mvmvअगर, bool set,
				 क्रमागत iwl_mvm_low_latency_cause cause)
अणु
	u8 new_state;

	अगर (set)
		mvmvअगर->low_latency |= cause;
	अन्यथा
		mvmvअगर->low_latency &= ~cause;

	/*
	 * अगर LOW_LATENCY_DEBUGFS_FORCE_ENABLE is enabled no changes are
	 * allowed to actual mode.
	 */
	अगर (mvmvअगर->low_latency & LOW_LATENCY_DEBUGFS_FORCE_ENABLE &&
	    cause != LOW_LATENCY_DEBUGFS_FORCE_ENABLE)
		वापस;

	अगर (cause == LOW_LATENCY_DEBUGFS_FORCE_ENABLE && set)
		/*
		 * We enter क्रमce state
		 */
		new_state = !!(mvmvअगर->low_latency &
			       LOW_LATENCY_DEBUGFS_FORCE);
	अन्यथा
		/*
		 * Check अगर any other one set low latency
		 */
		new_state = !!(mvmvअगर->low_latency &
				  ~(LOW_LATENCY_DEBUGFS_FORCE_ENABLE |
				    LOW_LATENCY_DEBUGFS_FORCE));

	mvmvअगर->low_latency_actual = new_state;
पूर्ण

/* Return a biपंचांगask with all the hw supported queues, except क्रम the
 * command queue, which can't be flushed.
 */
अटल अंतरभूत u32 iwl_mvm_flushable_queues(काष्ठा iwl_mvm *mvm)
अणु
	वापस ((BIT(mvm->trans->trans_cfg->base_params->num_of_queues) - 1) &
		~BIT(IWL_MVM_DQA_CMD_QUEUE));
पूर्ण

व्योम iwl_mvm_stop_device(काष्ठा iwl_mvm *mvm);

/* Re-configure the SCD क्रम a queue that has alपढ़ोy been configured */
पूर्णांक iwl_mvm_reconfig_scd(काष्ठा iwl_mvm *mvm, पूर्णांक queue, पूर्णांक fअगरo, पूर्णांक sta_id,
			 पूर्णांक tid, पूर्णांक frame_limit, u16 ssn);

/* Thermal management and CT-समाप्त */
व्योम iwl_mvm_tt_tx_backoff(काष्ठा iwl_mvm *mvm, u32 backoff);
व्योम iwl_mvm_temp_notअगर(काष्ठा iwl_mvm *mvm,
			काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_tt_handler(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_thermal_initialize(काष्ठा iwl_mvm *mvm, u32 min_backoff);
व्योम iwl_mvm_thermal_निकास(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_set_hw_ctसमाप्त_state(काष्ठा iwl_mvm *mvm, bool state);
पूर्णांक iwl_mvm_get_temp(काष्ठा iwl_mvm *mvm, s32 *temp);
व्योम iwl_mvm_ct_समाप्त_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_enter_ctसमाप्त(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_send_temp_report_ths_cmd(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_ctdp_command(काष्ठा iwl_mvm *mvm, u32 op, u32 budget);

/* Location Aware Regulatory */
काष्ठा iwl_mcc_update_resp *
iwl_mvm_update_mcc(काष्ठा iwl_mvm *mvm, स्थिर अक्षर *alpha2,
		   क्रमागत iwl_mcc_source src_id);
पूर्णांक iwl_mvm_init_mcc(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_rx_chub_update_mcc(काष्ठा iwl_mvm *mvm,
				काष्ठा iwl_rx_cmd_buffer *rxb);
काष्ठा ieee80211_regकरोमुख्य *iwl_mvm_get_regकरोमुख्य(काष्ठा wiphy *wiphy,
						  स्थिर अक्षर *alpha2,
						  क्रमागत iwl_mcc_source src_id,
						  bool *changed);
काष्ठा ieee80211_regकरोमुख्य *iwl_mvm_get_current_regकरोमुख्य(काष्ठा iwl_mvm *mvm,
							  bool *changed);
पूर्णांक iwl_mvm_init_fw_regd(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_update_changed_regकरोm(काष्ठा iwl_mvm *mvm);

/* smart fअगरo */
पूर्णांक iwl_mvm_sf_update(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
		      bool added_vअगर);

/* FTM responder */
पूर्णांक iwl_mvm_fपंचांग_start_responder(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_fपंचांग_restart_responder(काष्ठा iwl_mvm *mvm,
				   काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_fपंचांग_responder_stats(काष्ठा iwl_mvm *mvm,
				 काष्ठा iwl_rx_cmd_buffer *rxb);
पूर्णांक iwl_mvm_fपंचांग_resp_हटाओ_pasn_sta(काष्ठा iwl_mvm *mvm,
				     काष्ठा ieee80211_vअगर *vअगर, u8 *addr);
पूर्णांक iwl_mvm_fपंचांग_respoder_add_pasn_sta(काष्ठा iwl_mvm *mvm,
				      काष्ठा ieee80211_vअगर *vअगर,
				      u8 *addr, u32 cipher, u8 *tk, u32 tk_len,
				      u8 *hltk, u32 hltk_len);
व्योम iwl_mvm_fपंचांग_responder_clear(काष्ठा iwl_mvm *mvm,
				 काष्ठा ieee80211_vअगर *vअगर);

/* FTM initiator */
व्योम iwl_mvm_fपंचांग_restart(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_fपंचांग_range_resp(काष्ठा iwl_mvm *mvm,
			    काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_fपंचांग_lc_notअगर(काष्ठा iwl_mvm *mvm,
			  काष्ठा iwl_rx_cmd_buffer *rxb);
पूर्णांक iwl_mvm_fपंचांग_start(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
		      काष्ठा cfg80211_pmsr_request *request);
व्योम iwl_mvm_fपंचांग_पात(काष्ठा iwl_mvm *mvm, काष्ठा cfg80211_pmsr_request *req);
व्योम iwl_mvm_fपंचांग_initiator_smooth_config(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_fपंचांग_initiator_smooth_stop(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_fपंचांग_add_pasn_sta(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     u8 *addr, u32 cipher, u8 *tk, u32 tk_len,
			     u8 *hltk, u32 hltk_len);
व्योम iwl_mvm_fपंचांग_हटाओ_pasn_sta(काष्ठा iwl_mvm *mvm, u8 *addr);

/* TDLS */

/*
 * We use TID 4 (VI) as a FW-used-only TID when TDLS connections are present.
 * This TID is marked as used vs the AP and all connected TDLS peers.
 */
#घोषणा IWL_MVM_TDLS_FW_TID 4

पूर्णांक iwl_mvm_tdls_sta_count(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_tearकरोwn_tdls_peers(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_recalc_tdls_state(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			       bool sta_added);
व्योम iwl_mvm_mac_mgd_protect_tdls_discover(काष्ठा ieee80211_hw *hw,
					   काष्ठा ieee80211_vअगर *vअगर);
पूर्णांक iwl_mvm_tdls_channel_चयन(काष्ठा ieee80211_hw *hw,
				काष्ठा ieee80211_vअगर *vअगर,
				काष्ठा ieee80211_sta *sta, u8 oper_class,
				काष्ठा cfg80211_chan_def *chandef,
				काष्ठा sk_buff *पंचांगpl_skb, u32 ch_sw_पंचांग_ie);
व्योम iwl_mvm_tdls_recv_channel_चयन(काष्ठा ieee80211_hw *hw,
				      काष्ठा ieee80211_vअगर *vअगर,
				      काष्ठा ieee80211_tdls_ch_sw_params *params);
व्योम iwl_mvm_tdls_cancel_channel_चयन(काष्ठा ieee80211_hw *hw,
					काष्ठा ieee80211_vअगर *vअगर,
					काष्ठा ieee80211_sta *sta);
व्योम iwl_mvm_rx_tdls_notअगर(काष्ठा iwl_mvm *mvm, काष्ठा iwl_rx_cmd_buffer *rxb);
व्योम iwl_mvm_tdls_ch_चयन_work(काष्ठा work_काष्ठा *work);

व्योम iwl_mvm_sync_rx_queues_पूर्णांकernal(काष्ठा iwl_mvm *mvm,
				     क्रमागत iwl_mvm_rxq_notअगर_type type,
				     bool sync,
				     स्थिर व्योम *data, u32 size);
व्योम iwl_mvm_reorder_समयr_expired(काष्ठा समयr_list *t);
काष्ठा ieee80211_vअगर *iwl_mvm_get_bss_vअगर(काष्ठा iwl_mvm *mvm);
काष्ठा ieee80211_vअगर *iwl_mvm_get_vअगर_by_macid(काष्ठा iwl_mvm *mvm, u32 macid);
bool iwl_mvm_is_vअगर_assoc(काष्ठा iwl_mvm *mvm);

#घोषणा MVM_TCM_PERIOD_MSEC 500
#घोषणा MVM_TCM_PERIOD (HZ * MVM_TCM_PERIOD_MSEC / 1000)
#घोषणा MVM_LL_PERIOD (10 * HZ)
व्योम iwl_mvm_tcm_work(काष्ठा work_काष्ठा *work);
व्योम iwl_mvm_recalc_tcm(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_छोड़ो_tcm(काष्ठा iwl_mvm *mvm, bool with_cancel);
व्योम iwl_mvm_resume_tcm(काष्ठा iwl_mvm *mvm);
व्योम iwl_mvm_tcm_add_vअगर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
व्योम iwl_mvm_tcm_rm_vअगर(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर);
u8 iwl_mvm_tcm_load_percentage(u32 airसमय, u32 elapsed);

व्योम iwl_mvm_nic_restart(काष्ठा iwl_mvm *mvm, bool fw_error);
अचिन्हित पूर्णांक iwl_mvm_get_wd_समयout(काष्ठा iwl_mvm *mvm,
				    काष्ठा ieee80211_vअगर *vअगर,
				    bool tdls, bool cmd_q);
व्योम iwl_mvm_connection_loss(काष्ठा iwl_mvm *mvm, काष्ठा ieee80211_vअगर *vअगर,
			     स्थिर अक्षर *errmsg);
व्योम iwl_mvm_event_frame_समयout_callback(काष्ठा iwl_mvm *mvm,
					  काष्ठा ieee80211_vअगर *vअगर,
					  स्थिर काष्ठा ieee80211_sta *sta,
					  u16 tid);

पूर्णांक iwl_mvm_sar_select_profile(काष्ठा iwl_mvm *mvm, पूर्णांक prof_a, पूर्णांक prof_b);
पूर्णांक iwl_mvm_get_sar_geo_profile(काष्ठा iwl_mvm *mvm);
पूर्णांक iwl_mvm_ppag_send_cmd(काष्ठा iwl_mvm *mvm);
#अगर_घोषित CONFIG_IWLWIFI_DEBUGFS
व्योम iwl_mvm_sta_add_debugfs(काष्ठा ieee80211_hw *hw,
			     काष्ठा ieee80211_vअगर *vअगर,
			     काष्ठा ieee80211_sta *sta,
			     काष्ठा dentry *dir);
#पूर्ण_अगर

पूर्णांक iwl_rfi_send_config_cmd(काष्ठा iwl_mvm *mvm,
			    काष्ठा iwl_rfi_lut_entry *rfi_table);
काष्ठा iwl_rfi_freq_table_resp_cmd *iwl_rfi_get_freq_table(काष्ठा iwl_mvm *mvm);

अटल अंतरभूत u8 iwl_mvm_phy_band_from_nl80211(क्रमागत nl80211_band band)
अणु
	चयन (band) अणु
	हाल NL80211_BAND_2GHZ:
		वापस PHY_BAND_24;
	हाल NL80211_BAND_5GHZ:
		वापस PHY_BAND_5;
	हाल NL80211_BAND_6GHZ:
		वापस PHY_BAND_6;
	शेष:
		WARN_ONCE(1, "Unsupported band (%u)\n", band);
		वापस PHY_BAND_5;
	पूर्ण
पूर्ण

/* Channel info utils */
अटल अंतरभूत bool iwl_mvm_has_ultra_hb_channel(काष्ठा iwl_mvm *mvm)
अणु
	वापस fw_has_capa(&mvm->fw->ucode_capa,
			   IWL_UCODE_TLV_CAPA_ULTRA_HB_CHANNELS);
पूर्ण

अटल अंतरभूत व्योम *iwl_mvm_chan_info_cmd_tail(काष्ठा iwl_mvm *mvm,
					       काष्ठा iwl_fw_channel_info *ci)
अणु
	वापस (u8 *)ci + (iwl_mvm_has_ultra_hb_channel(mvm) ?
			   माप(काष्ठा iwl_fw_channel_info) :
			   माप(काष्ठा iwl_fw_channel_info_v1));
पूर्ण

अटल अंतरभूत माप_प्रकार iwl_mvm_chan_info_padding(काष्ठा iwl_mvm *mvm)
अणु
	वापस iwl_mvm_has_ultra_hb_channel(mvm) ? 0 :
		माप(काष्ठा iwl_fw_channel_info) -
		माप(काष्ठा iwl_fw_channel_info_v1);
पूर्ण

अटल अंतरभूत व्योम iwl_mvm_set_chan_info(काष्ठा iwl_mvm *mvm,
					 काष्ठा iwl_fw_channel_info *ci,
					 u32 chan, u8 band, u8 width,
					 u8 ctrl_pos)
अणु
	अगर (iwl_mvm_has_ultra_hb_channel(mvm)) अणु
		ci->channel = cpu_to_le32(chan);
		ci->band = band;
		ci->width = width;
		ci->ctrl_pos = ctrl_pos;
	पूर्ण अन्यथा अणु
		काष्ठा iwl_fw_channel_info_v1 *ci_v1 =
					(काष्ठा iwl_fw_channel_info_v1 *)ci;

		ci_v1->channel = chan;
		ci_v1->band = band;
		ci_v1->width = width;
		ci_v1->ctrl_pos = ctrl_pos;
	पूर्ण
पूर्ण

अटल अंतरभूत व्योम
iwl_mvm_set_chan_info_chandef(काष्ठा iwl_mvm *mvm,
			      काष्ठा iwl_fw_channel_info *ci,
			      काष्ठा cfg80211_chan_def *chandef)
अणु
	क्रमागत nl80211_band band = chandef->chan->band;

	iwl_mvm_set_chan_info(mvm, ci, chandef->chan->hw_value,
			      iwl_mvm_phy_band_from_nl80211(band),
			      iwl_mvm_get_channel_width(chandef),
			      iwl_mvm_get_ctrl_pos(chandef));
पूर्ण

अटल अंतरभूत पूर्णांक iwl_umac_scan_get_max_profiles(स्थिर काष्ठा iwl_fw *fw)
अणु
	u8 ver = iwl_fw_lookup_cmd_ver(fw, IWL_ALWAYS_LONG_GROUP,
				       SCAN_OFFLOAD_UPDATE_PROखाताS_CMD,
				       IWL_FW_CMD_VER_UNKNOWN);
	वापस (ver == IWL_FW_CMD_VER_UNKNOWN || ver < 3) ?
		IWL_SCAN_MAX_PROखाताS : IWL_SCAN_MAX_PROखाताS_V2;
पूर्ण

अटल अंतरभूत
क्रमागत iwl_location_cipher iwl_mvm_cipher_to_location_cipher(u32 cipher)
अणु
	चयन (cipher) अणु
	हाल WLAN_CIPHER_SUITE_CCMP:
		वापस IWL_LOCATION_CIPHER_CCMP_128;
	हाल WLAN_CIPHER_SUITE_GCMP:
		वापस IWL_LOCATION_CIPHER_GCMP_128;
	हाल WLAN_CIPHER_SUITE_GCMP_256:
		वापस IWL_LOCATION_CIPHER_GCMP_256;
	शेष:
		वापस IWL_LOCATION_CIPHER_INVALID;
	पूर्ण
पूर्ण
#पूर्ण_अगर /* __IWL_MVM_H__ */
