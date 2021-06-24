<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_scan_h__
#घोषणा __iwl_fw_api_scan_h__

/* Scan Commands, Responses, Notअगरications */

/* Max number of IEs क्रम direct SSID scans in a command */
#घोषणा PROBE_OPTION_MAX		20

#घोषणा SCAN_SHORT_SSID_MAX_SIZE        8
#घोषणा SCAN_BSSID_MAX_SIZE             16

/**
 * काष्ठा iwl_ssid_ie - directed scan network inक्रमmation element
 *
 * Up to 20 of these may appear in REPLY_SCAN_CMD,
 * selected by "type" bit field in काष्ठा iwl_scan_channel;
 * each channel may select dअगरferent ssids from among the 20 entries.
 * SSID IEs get transmitted in reverse order of entry.
 *
 * @id: element ID
 * @len: element length
 * @ssid: element (SSID) data
 */
काष्ठा iwl_ssid_ie अणु
	u8 id;
	u8 len;
	u8 ssid[IEEE80211_MAX_SSID_LEN];
पूर्ण __packed; /* SCAN_सूचीECT_SSID_IE_API_S_VER_1 */

/* scan offload */
#घोषणा IWL_SCAN_MAX_BLACKLIST_LEN	64
#घोषणा IWL_SCAN_SHORT_BLACKLIST_LEN	16
#घोषणा IWL_SCAN_MAX_PROखाताS		11
#घोषणा IWL_SCAN_MAX_PROखाताS_V2	8
#घोषणा SCAN_OFFLOAD_PROBE_REQ_SIZE	512
#घोषणा SCAN_NUM_BAND_PROBE_DATA_V_1	2
#घोषणा SCAN_NUM_BAND_PROBE_DATA_V_2	3

/* Default watchकरोg (in MS) क्रम scheduled scan iteration */
#घोषणा IWL_SCHED_SCAN_WATCHDOG cpu_to_le16(15000)

#घोषणा IWL_GOOD_CRC_TH_DEFAULT cpu_to_le16(1)
#घोषणा CAN_ABORT_STATUS 1

#घोषणा IWL_FULL_SCAN_MULTIPLIER 5
#घोषणा IWL_FAST_SCHED_SCAN_ITERATIONS 3
#घोषणा IWL_MAX_SCHED_SCAN_PLANS 2

क्रमागत scan_framework_client अणु
	SCAN_CLIENT_SCHED_SCAN		= BIT(0),
	SCAN_CLIENT_NETDETECT		= BIT(1),
	SCAN_CLIENT_ASSET_TRACKING	= BIT(2),
पूर्ण;

/**
 * काष्ठा iwl_scan_offload_blocklist - SCAN_OFFLOAD_BLACKLIST_S
 * @ssid:		MAC address to filter out
 * @reported_rssi:	AP rssi reported to the host
 * @client_biपंचांगap: clients ignore this entry  - क्रमागत scan_framework_client
 */
काष्ठा iwl_scan_offload_blocklist अणु
	u8 ssid[ETH_ALEN];
	u8 reported_rssi;
	u8 client_biपंचांगap;
पूर्ण __packed;

क्रमागत iwl_scan_offload_network_type अणु
	IWL_NETWORK_TYPE_BSS	= 1,
	IWL_NETWORK_TYPE_IBSS	= 2,
	IWL_NETWORK_TYPE_ANY	= 3,
पूर्ण;

क्रमागत iwl_scan_offload_band_selection अणु
	IWL_SCAN_OFFLOAD_SELECT_2_4	= 0x4,
	IWL_SCAN_OFFLOAD_SELECT_5_2	= 0x8,
	IWL_SCAN_OFFLOAD_SELECT_ANY	= 0xc,
पूर्ण;

/**
 * काष्ठा iwl_scan_offload_profile - SCAN_OFFLOAD_PROखाता_S
 * @ssid_index:		index to ssid list in fixed part
 * @unicast_cipher:	encryption algorithm to match - biपंचांगap
 * @auth_alg:		authentication algorithm to match - biपंचांगap
 * @network_type:	क्रमागत iwl_scan_offload_network_type
 * @band_selection:	क्रमागत iwl_scan_offload_band_selection
 * @client_biपंचांगap:	clients रुकोing क्रम match - क्रमागत scan_framework_client
 * @reserved:		reserved
 */
काष्ठा iwl_scan_offload_profile अणु
	u8 ssid_index;
	u8 unicast_cipher;
	u8 auth_alg;
	u8 network_type;
	u8 band_selection;
	u8 client_biपंचांगap;
	u8 reserved[2];
पूर्ण __packed;

/**
 * काष्ठा iwl_scan_offload_profile_cfg_data
 * @blocklist_len:	length of blocklist
 * @num_profiles:	num of profiles in the list
 * @match_notअगरy:	clients रुकोing क्रम match found notअगरication
 * @pass_match:		clients रुकोing क्रम the results
 * @active_clients:	active clients biपंचांगap - क्रमागत scan_framework_client
 * @any_beacon_notअगरy:	clients रुकोing क्रम match notअगरication without match
 * @reserved:		reserved
 */
काष्ठा iwl_scan_offload_profile_cfg_data अणु
	u8 blocklist_len;
	u8 num_profiles;
	u8 match_notअगरy;
	u8 pass_match;
	u8 active_clients;
	u8 any_beacon_notअगरy;
	u8 reserved[2];
पूर्ण __packed;

/**
 * काष्ठा iwl_scan_offload_profile_cfg
 * @profiles:	profiles to search क्रम match
 * @data:	the rest of the data क्रम profile_cfg
 */
काष्ठा iwl_scan_offload_profile_cfg_v1 अणु
	काष्ठा iwl_scan_offload_profile profiles[IWL_SCAN_MAX_PROखाताS];
	काष्ठा iwl_scan_offload_profile_cfg_data data;
पूर्ण __packed; /* SCAN_OFFLOAD_PROखाताS_CFG_API_S_VER_1-2*/

/**
 * काष्ठा iwl_scan_offload_profile_cfg
 * @profiles:	profiles to search क्रम match
 * @data:	the rest of the data क्रम profile_cfg
 */
काष्ठा iwl_scan_offload_profile_cfg अणु
	काष्ठा iwl_scan_offload_profile profiles[IWL_SCAN_MAX_PROखाताS_V2];
	काष्ठा iwl_scan_offload_profile_cfg_data data;
पूर्ण __packed; /* SCAN_OFFLOAD_PROखाताS_CFG_API_S_VER_3*/

/**
 * काष्ठा iwl_scan_schedule_lmac - schedule of scan offload
 * @delay:		delay between iterations, in seconds.
 * @iterations:		num of scan iterations
 * @full_scan_mul:	number of partial scans beक्रमe each full scan
 */
काष्ठा iwl_scan_schedule_lmac अणु
	__le16 delay;
	u8 iterations;
	u8 full_scan_mul;
पूर्ण __packed; /* SCAN_SCHEDULE_API_S */

क्रमागत iwl_scan_offload_complete_status अणु
	IWL_SCAN_OFFLOAD_COMPLETED	= 1,
	IWL_SCAN_OFFLOAD_ABORTED	= 2,
पूर्ण;

क्रमागत iwl_scan_ebs_status अणु
	IWL_SCAN_EBS_SUCCESS,
	IWL_SCAN_EBS_FAILED,
	IWL_SCAN_EBS_CHAN_NOT_FOUND,
	IWL_SCAN_EBS_INACTIVE,
पूर्ण;

/**
 * काष्ठा iwl_scan_req_tx_cmd - SCAN_REQ_TX_CMD_API_S
 * @tx_flags: combination of TX_CMD_FLG_*
 * @rate_n_flags: rate क्रम *all* Tx attempts, अगर TX_CMD_FLG_STA_RATE_MSK is
 *	cleared. Combination of RATE_MCS_*
 * @sta_id: index of destination station in FW station table
 * @reserved: क्रम alignment and future use
 */
काष्ठा iwl_scan_req_tx_cmd अणु
	__le32 tx_flags;
	__le32 rate_n_flags;
	u8 sta_id;
	u8 reserved[3];
पूर्ण __packed;

क्रमागत iwl_scan_channel_flags_lmac अणु
	IWL_UNIFIED_SCAN_CHANNEL_FULL		= BIT(27),
	IWL_UNIFIED_SCAN_CHANNEL_PARTIAL	= BIT(28),
पूर्ण;

/**
 * काष्ठा iwl_scan_channel_cfg_lmac - SCAN_CHANNEL_CFG_S_VER2
 * @flags:		bits 1-20: directed scan to i'th ssid
 *			other bits &क्रमागत iwl_scan_channel_flags_lmac
 * @channel_num:	channel number 1-13 etc
 * @iter_count:		scan iteration on this channel
 * @iter_पूर्णांकerval:	पूर्णांकerval in seconds between iterations on one channel
 */
काष्ठा iwl_scan_channel_cfg_lmac अणु
	__le32 flags;
	__le16 channel_num;
	__le16 iter_count;
	__le32 iter_पूर्णांकerval;
पूर्ण __packed;

/*
 * काष्ठा iwl_scan_probe_segment - PROBE_SEGMENT_API_S_VER_1
 * @offset: offset in the data block
 * @len: length of the segment
 */
काष्ठा iwl_scan_probe_segment अणु
	__le16 offset;
	__le16 len;
पूर्ण __packed;

/* iwl_scan_probe_req - PROBE_REQUEST_FRAME_API_S_VER_2
 * @mac_header: first (and common) part of the probe
 * @band_data: band specअगरic data
 * @common_data: last (and common) part of the probe
 * @buf: raw data block
 */
काष्ठा iwl_scan_probe_req_v1 अणु
	काष्ठा iwl_scan_probe_segment mac_header;
	काष्ठा iwl_scan_probe_segment band_data[SCAN_NUM_BAND_PROBE_DATA_V_1];
	काष्ठा iwl_scan_probe_segment common_data;
	u8 buf[SCAN_OFFLOAD_PROBE_REQ_SIZE];
पूर्ण __packed;

/* iwl_scan_probe_req - PROBE_REQUEST_FRAME_API_S_VER_v2
 * @mac_header: first (and common) part of the probe
 * @band_data: band specअगरic data
 * @common_data: last (and common) part of the probe
 * @buf: raw data block
 */
काष्ठा iwl_scan_probe_req अणु
	काष्ठा iwl_scan_probe_segment mac_header;
	काष्ठा iwl_scan_probe_segment band_data[SCAN_NUM_BAND_PROBE_DATA_V_2];
	काष्ठा iwl_scan_probe_segment common_data;
	u8 buf[SCAN_OFFLOAD_PROBE_REQ_SIZE];
पूर्ण __packed;

क्रमागत iwl_scan_channel_flags अणु
	IWL_SCAN_CHANNEL_FLAG_EBS		= BIT(0),
	IWL_SCAN_CHANNEL_FLAG_EBS_ACCURATE	= BIT(1),
	IWL_SCAN_CHANNEL_FLAG_CACHE_ADD		= BIT(2),
	IWL_SCAN_CHANNEL_FLAG_EBS_FRAG		= BIT(3),
	IWL_SCAN_CHANNEL_FLAG_FORCE_EBS         = BIT(4),
	IWL_SCAN_CHANNEL_FLAG_ENABLE_CHAN_ORDER = BIT(5),
	IWL_SCAN_CHANNEL_FLAG_6G_PSC_NO_FILTER  = BIT(6),
पूर्ण;

/* काष्ठा iwl_scan_channel_opt - CHANNEL_OPTIMIZATION_API_S
 * @flags: क्रमागत iwl_scan_channel_flags
 * @non_ebs_ratio: defines the ratio of number of scan iterations where EBS is
 *	involved.
 *	1 - EBS is disabled.
 *	2 - every second scan will be full scan(and so on).
 */
काष्ठा iwl_scan_channel_opt अणु
	__le16 flags;
	__le16 non_ebs_ratio;
पूर्ण __packed;

/**
 * क्रमागत iwl_mvm_lmac_scan_flags - LMAC scan flags
 * @IWL_MVM_LMAC_SCAN_FLAG_PASS_ALL: pass all beacons and probe responses
 *	without filtering.
 * @IWL_MVM_LMAC_SCAN_FLAG_PASSIVE: क्रमce passive scan on all channels
 * @IWL_MVM_LMAC_SCAN_FLAG_PRE_CONNECTION: single channel scan
 * @IWL_MVM_LMAC_SCAN_FLAG_ITER_COMPLETE: send iteration complete notअगरication
 * @IWL_MVM_LMAC_SCAN_FLAG_MULTIPLE_SSIDS: multiple SSID matching
 * @IWL_MVM_LMAC_SCAN_FLAG_FRAGMENTED: all passive scans will be fragmented
 * @IWL_MVM_LMAC_SCAN_FLAGS_RRM_ENABLED: insert WFA venकरोr-specअगरic TPC report
 *	and DS parameter set IEs पूर्णांकo probe requests.
 * @IWL_MVM_LMAC_SCAN_FLAG_EXTENDED_DWELL: use extended dwell समय on channels
 *	1, 6 and 11.
 * @IWL_MVM_LMAC_SCAN_FLAG_MATCH: Send match found notअगरication on matches
 */
क्रमागत iwl_mvm_lmac_scan_flags अणु
	IWL_MVM_LMAC_SCAN_FLAG_PASS_ALL		= BIT(0),
	IWL_MVM_LMAC_SCAN_FLAG_PASSIVE		= BIT(1),
	IWL_MVM_LMAC_SCAN_FLAG_PRE_CONNECTION	= BIT(2),
	IWL_MVM_LMAC_SCAN_FLAG_ITER_COMPLETE	= BIT(3),
	IWL_MVM_LMAC_SCAN_FLAG_MULTIPLE_SSIDS	= BIT(4),
	IWL_MVM_LMAC_SCAN_FLAG_FRAGMENTED	= BIT(5),
	IWL_MVM_LMAC_SCAN_FLAGS_RRM_ENABLED	= BIT(6),
	IWL_MVM_LMAC_SCAN_FLAG_EXTENDED_DWELL	= BIT(7),
	IWL_MVM_LMAC_SCAN_FLAG_MATCH		= BIT(9),
पूर्ण;

क्रमागत iwl_scan_priority अणु
	IWL_SCAN_PRIORITY_LOW,
	IWL_SCAN_PRIORITY_MEDIUM,
	IWL_SCAN_PRIORITY_HIGH,
पूर्ण;

क्रमागत iwl_scan_priority_ext अणु
	IWL_SCAN_PRIORITY_EXT_0_LOWEST,
	IWL_SCAN_PRIORITY_EXT_1,
	IWL_SCAN_PRIORITY_EXT_2,
	IWL_SCAN_PRIORITY_EXT_3,
	IWL_SCAN_PRIORITY_EXT_4,
	IWL_SCAN_PRIORITY_EXT_5,
	IWL_SCAN_PRIORITY_EXT_6,
	IWL_SCAN_PRIORITY_EXT_7_HIGHEST,
पूर्ण;

/**
 * काष्ठा iwl_scan_req_lmac - SCAN_REQUEST_CMD_API_S_VER_1
 * @reserved1: क्रम alignment and future use
 * @n_channels: num of channels to scan
 * @active_dwell: dwell समय क्रम active channels
 * @passive_dwell: dwell समय क्रम passive channels
 * @fragmented_dwell: dwell समय क्रम fragmented passive scan
 * @extended_dwell: dwell समय क्रम channels 1, 6 and 11 (in certain हालs)
 * @reserved2: क्रम alignment and future use
 * @rx_chain_select: PHY_RX_CHAIN_* flags
 * @scan_flags: &क्रमागत iwl_mvm_lmac_scan_flags
 * @max_out_समय: max समय (in TU) to be out of associated channel
 * @suspend_समय: छोड़ो scan this दीर्घ (TUs) when वापसing to service channel
 * @flags: RXON flags
 * @filter_flags: RXON filter
 * @tx_cmd: tx command क्रम active scan; क्रम 2GHz and क्रम 5GHz
 * @direct_scan: list of SSIDs क्रम directed active scan
 * @scan_prio: क्रमागत iwl_scan_priority
 * @iter_num: number of scan iterations
 * @delay: delay in seconds beक्रमe first iteration
 * @schedule: two scheduling plans. The first one is finite, the second one can
 *	be infinite.
 * @channel_opt: channel optimization options, क्रम full and partial scan
 * @data: channel configuration and probe request packet.
 */
काष्ठा iwl_scan_req_lmac अणु
	/* SCAN_REQUEST_FIXED_PART_API_S_VER_7 */
	__le32 reserved1;
	u8 n_channels;
	u8 active_dwell;
	u8 passive_dwell;
	u8 fragmented_dwell;
	u8 extended_dwell;
	u8 reserved2;
	__le16 rx_chain_select;
	__le32 scan_flags;
	__le32 max_out_समय;
	__le32 suspend_समय;
	/* RX_ON_FLAGS_API_S_VER_1 */
	__le32 flags;
	__le32 filter_flags;
	काष्ठा iwl_scan_req_tx_cmd tx_cmd[2];
	काष्ठा iwl_ssid_ie direct_scan[PROBE_OPTION_MAX];
	__le32 scan_prio;
	/* SCAN_REQ_PERIODIC_PARAMS_API_S */
	__le32 iter_num;
	__le32 delay;
	काष्ठा iwl_scan_schedule_lmac schedule[IWL_MAX_SCHED_SCAN_PLANS];
	काष्ठा iwl_scan_channel_opt channel_opt[2];
	u8 data[];
पूर्ण __packed;

/**
 * काष्ठा iwl_scan_results_notअगर - scan results क्रम one channel -
 *	SCAN_RESULT_NTF_API_S_VER_3
 * @channel: which channel the results are from
 * @band: 0 क्रम 5.2 GHz, 1 क्रम 2.4 GHz
 * @probe_status: SCAN_PROBE_STATUS_*, indicates success of probe request
 * @num_probe_not_sent: # of request that weren't sent due to not enough समय
 * @duration: duration spent in channel, in usecs
 */
काष्ठा iwl_scan_results_notअगर अणु
	u8 channel;
	u8 band;
	u8 probe_status;
	u8 num_probe_not_sent;
	__le32 duration;
पूर्ण __packed;

/**
 * काष्ठा iwl_lmac_scan_complete_notअगर - notअगरies end of scanning (all channels)
 *	SCAN_COMPLETE_NTF_API_S_VER_3
 * @scanned_channels: number of channels scanned (and number of valid results)
 * @status: one of SCAN_COMP_STATUS_*
 * @bt_status: BT on/off status
 * @last_channel: last channel that was scanned
 * @tsf_low: TSF समयr (lower half) in usecs
 * @tsf_high: TSF समयr (higher half) in usecs
 * @results: an array of scan results, only "scanned_channels" of them are valid
 */
काष्ठा iwl_lmac_scan_complete_notअगर अणु
	u8 scanned_channels;
	u8 status;
	u8 bt_status;
	u8 last_channel;
	__le32 tsf_low;
	__le32 tsf_high;
	काष्ठा iwl_scan_results_notअगर results[];
पूर्ण __packed;

/**
 * काष्ठा iwl_scan_offload_complete - PERIODIC_SCAN_COMPLETE_NTF_API_S_VER_2
 * @last_schedule_line: last schedule line executed (fast or regular)
 * @last_schedule_iteration: last scan iteration executed beक्रमe scan पात
 * @status: &क्रमागत iwl_scan_offload_complete_status
 * @ebs_status: EBS success status &क्रमागत iwl_scan_ebs_status
 * @समय_after_last_iter: समय in seconds elapsed after last iteration
 * @reserved: reserved
 */
काष्ठा iwl_periodic_scan_complete अणु
	u8 last_schedule_line;
	u8 last_schedule_iteration;
	u8 status;
	u8 ebs_status;
	__le32 समय_after_last_iter;
	__le32 reserved;
पूर्ण __packed;

/* UMAC Scan API */

/* The maximum of either of these cannot exceed 8, because we use an
 * 8-bit mask (see IWL_MVM_SCAN_MASK in mvm.h).
 */
#घोषणा IWL_MVM_MAX_UMAC_SCANS 4
#घोषणा IWL_MVM_MAX_LMAC_SCANS 1

क्रमागत scan_config_flags अणु
	SCAN_CONFIG_FLAG_ACTIVATE			= BIT(0),
	SCAN_CONFIG_FLAG_DEACTIVATE			= BIT(1),
	SCAN_CONFIG_FLAG_FORBID_CHUB_REQS		= BIT(2),
	SCAN_CONFIG_FLAG_ALLOW_CHUB_REQS		= BIT(3),
	SCAN_CONFIG_FLAG_SET_TX_CHAINS			= BIT(8),
	SCAN_CONFIG_FLAG_SET_RX_CHAINS			= BIT(9),
	SCAN_CONFIG_FLAG_SET_AUX_STA_ID			= BIT(10),
	SCAN_CONFIG_FLAG_SET_ALL_TIMES			= BIT(11),
	SCAN_CONFIG_FLAG_SET_EFFECTIVE_TIMES		= BIT(12),
	SCAN_CONFIG_FLAG_SET_CHANNEL_FLAGS		= BIT(13),
	SCAN_CONFIG_FLAG_SET_LEGACY_RATES		= BIT(14),
	SCAN_CONFIG_FLAG_SET_MAC_ADDR			= BIT(15),
	SCAN_CONFIG_FLAG_SET_FRAGMENTED			= BIT(16),
	SCAN_CONFIG_FLAG_CLEAR_FRAGMENTED		= BIT(17),
	SCAN_CONFIG_FLAG_SET_CAM_MODE			= BIT(18),
	SCAN_CONFIG_FLAG_CLEAR_CAM_MODE			= BIT(19),
	SCAN_CONFIG_FLAG_SET_PROMISC_MODE		= BIT(20),
	SCAN_CONFIG_FLAG_CLEAR_PROMISC_MODE		= BIT(21),
	SCAN_CONFIG_FLAG_SET_LMAC2_FRAGMENTED		= BIT(22),
	SCAN_CONFIG_FLAG_CLEAR_LMAC2_FRAGMENTED		= BIT(23),

	/* Bits 26-31 are क्रम num of channels in channel_array */
#घोषणा SCAN_CONFIG_N_CHANNELS(n) ((n) << 26)
पूर्ण;

क्रमागत scan_config_rates अणु
	/* OFDM basic rates */
	SCAN_CONFIG_RATE_6M	= BIT(0),
	SCAN_CONFIG_RATE_9M	= BIT(1),
	SCAN_CONFIG_RATE_12M	= BIT(2),
	SCAN_CONFIG_RATE_18M	= BIT(3),
	SCAN_CONFIG_RATE_24M	= BIT(4),
	SCAN_CONFIG_RATE_36M	= BIT(5),
	SCAN_CONFIG_RATE_48M	= BIT(6),
	SCAN_CONFIG_RATE_54M	= BIT(7),
	/* CCK basic rates */
	SCAN_CONFIG_RATE_1M	= BIT(8),
	SCAN_CONFIG_RATE_2M	= BIT(9),
	SCAN_CONFIG_RATE_5M	= BIT(10),
	SCAN_CONFIG_RATE_11M	= BIT(11),

	/* Bits 16-27 are क्रम supported rates */
#घोषणा SCAN_CONFIG_SUPPORTED_RATE(rate)	((rate) << 16)
पूर्ण;

क्रमागत iwl_channel_flags अणु
	IWL_CHANNEL_FLAG_EBS				= BIT(0),
	IWL_CHANNEL_FLAG_ACCURATE_EBS			= BIT(1),
	IWL_CHANNEL_FLAG_EBS_ADD			= BIT(2),
	IWL_CHANNEL_FLAG_PRE_SCAN_PASSIVE2ACTIVE	= BIT(3),
पूर्ण;

क्रमागत iwl_uhb_chan_cfg_flags अणु
	IWL_UHB_CHAN_CFG_FLAG_UNSOLICITED_PROBE_RES = BIT(24),
	IWL_UHB_CHAN_CFG_FLAG_PSC_CHAN_NO_LISTEN    = BIT(25),
	IWL_UHB_CHAN_CFG_FLAG_FORCE_PASSIVE         = BIT(26),
पूर्ण;
/**
 * काष्ठा iwl_scan_dwell
 * @active:		शेष dwell समय क्रम active scan
 * @passive:		शेष dwell समय क्रम passive scan
 * @fragmented:		शेष dwell समय क्रम fragmented scan
 * @extended:		शेष dwell समय क्रम channels 1, 6 and 11
 */
काष्ठा iwl_scan_dwell अणु
	u8 active;
	u8 passive;
	u8 fragmented;
	u8 extended;
पूर्ण __packed;

/**
 * काष्ठा iwl_scan_config_v1
 * @flags:			क्रमागत scan_config_flags
 * @tx_chains:			valid_tx antenna - ANT_* definitions
 * @rx_chains:			valid_rx antenna - ANT_* definitions
 * @legacy_rates:		शेष legacy rates - क्रमागत scan_config_rates
 * @out_of_channel_समय:	शेष max out of serving channel समय
 * @suspend_समय:		शेष max suspend समय
 * @dwell:			dwells क्रम the scan
 * @mac_addr:			शेष mac address to be used in probes
 * @bcast_sta_id:		the index of the station in the fw
 * @channel_flags:		शेष channel flags - क्रमागत iwl_channel_flags
 *				scan_config_channel_flag
 * @channel_array:		शेष supported channels
 */
काष्ठा iwl_scan_config_v1 अणु
	__le32 flags;
	__le32 tx_chains;
	__le32 rx_chains;
	__le32 legacy_rates;
	__le32 out_of_channel_समय;
	__le32 suspend_समय;
	काष्ठा iwl_scan_dwell dwell;
	u8 mac_addr[ETH_ALEN];
	u8 bcast_sta_id;
	u8 channel_flags;
	u8 channel_array[];
पूर्ण __packed; /* SCAN_CONFIG_DB_CMD_API_S */

#घोषणा SCAN_TWO_LMACS 2
#घोषणा SCAN_LB_LMAC_IDX 0
#घोषणा SCAN_HB_LMAC_IDX 1

काष्ठा iwl_scan_config_v2 अणु
	__le32 flags;
	__le32 tx_chains;
	__le32 rx_chains;
	__le32 legacy_rates;
	__le32 out_of_channel_समय[SCAN_TWO_LMACS];
	__le32 suspend_समय[SCAN_TWO_LMACS];
	काष्ठा iwl_scan_dwell dwell;
	u8 mac_addr[ETH_ALEN];
	u8 bcast_sta_id;
	u8 channel_flags;
	u8 channel_array[];
पूर्ण __packed; /* SCAN_CONFIG_DB_CMD_API_S_2 */

/**
 * काष्ठा iwl_scan_config
 * @enable_cam_mode: whether to enable CAM mode.
 * @enable_promiscouos_mode: whether to enable promiscouos mode
 * @bcast_sta_id: the index of the station in the fw. Deprecated starting with
 *     API version 5.
 * @reserved: reserved
 * @tx_chains: valid_tx antenna - ANT_* definitions
 * @rx_chains: valid_rx antenna - ANT_* definitions
 */
काष्ठा iwl_scan_config अणु
	u8 enable_cam_mode;
	u8 enable_promiscouos_mode;
	u8 bcast_sta_id;
	u8 reserved;
	__le32 tx_chains;
	__le32 rx_chains;
पूर्ण __packed; /* SCAN_CONFIG_DB_CMD_API_S_5 */

/**
 * क्रमागत iwl_umac_scan_flags - UMAC scan flags
 * @IWL_UMAC_SCAN_FLAG_PREEMPTIVE: scan process triggered by this scan request
 *	can be preempted by other scan requests with higher priority.
 *	The low priority scan will be resumed when the higher proirity scan is
 *	completed.
 * @IWL_UMAC_SCAN_FLAG_START_NOTIF: notअगरication will be sent to the driver
 *	when scan starts.
 */
क्रमागत iwl_umac_scan_flags अणु
	IWL_UMAC_SCAN_FLAG_PREEMPTIVE		= BIT(0),
	IWL_UMAC_SCAN_FLAG_START_NOTIF		= BIT(1),
पूर्ण;

क्रमागत iwl_umac_scan_uid_offsets अणु
	IWL_UMAC_SCAN_UID_TYPE_OFFSET		= 0,
	IWL_UMAC_SCAN_UID_SEQ_OFFSET		= 8,
पूर्ण;

क्रमागत iwl_umac_scan_general_flags अणु
	IWL_UMAC_SCAN_GEN_FLAGS_PERIODIC		= BIT(0),
	IWL_UMAC_SCAN_GEN_FLAGS_OVER_BT			= BIT(1),
	IWL_UMAC_SCAN_GEN_FLAGS_PASS_ALL		= BIT(2),
	IWL_UMAC_SCAN_GEN_FLAGS_PASSIVE			= BIT(3),
	IWL_UMAC_SCAN_GEN_FLAGS_PRE_CONNECT		= BIT(4),
	IWL_UMAC_SCAN_GEN_FLAGS_ITER_COMPLETE		= BIT(5),
	IWL_UMAC_SCAN_GEN_FLAGS_MULTIPLE_SSID		= BIT(6),
	IWL_UMAC_SCAN_GEN_FLAGS_FRAGMENTED		= BIT(7),
	IWL_UMAC_SCAN_GEN_FLAGS_RRM_ENABLED		= BIT(8),
	IWL_UMAC_SCAN_GEN_FLAGS_MATCH			= BIT(9),
	IWL_UMAC_SCAN_GEN_FLAGS_EXTENDED_DWELL		= BIT(10),
	/* Extended dwell is obselete when adaptive dwell is used, making this
	 * bit reusable. Hence, probe request defer is used only when adaptive
	 * dwell is supported. */
	IWL_UMAC_SCAN_GEN_FLAGS_PROB_REQ_DEFER_SUPP	= BIT(10),
	IWL_UMAC_SCAN_GEN_FLAGS_LMAC2_FRAGMENTED	= BIT(11),
	IWL_UMAC_SCAN_GEN_FLAGS_ADAPTIVE_DWELL		= BIT(13),
	IWL_UMAC_SCAN_GEN_FLAGS_MAX_CHNL_TIME		= BIT(14),
	IWL_UMAC_SCAN_GEN_FLAGS_PROB_REQ_HIGH_TX_RATE	= BIT(15),
पूर्ण;

/**
 * क्रमागत iwl_umac_scan_general_flags2 - UMAC scan general flags #2
 * @IWL_UMAC_SCAN_GEN_FLAGS2_NOTIF_PER_CHNL: Whether to send a complete
 *	notअगरication per channel or not.
 * @IWL_UMAC_SCAN_GEN_FLAGS2_ALLOW_CHNL_REORDER: Whether to allow channel
 *	reorder optimization or not.
 */
क्रमागत iwl_umac_scan_general_flags2 अणु
	IWL_UMAC_SCAN_GEN_FLAGS2_NOTIF_PER_CHNL		= BIT(0),
	IWL_UMAC_SCAN_GEN_FLAGS2_ALLOW_CHNL_REORDER	= BIT(1),
पूर्ण;

/**
 * क्रमागत iwl_umac_scan_general_flags_v2 - UMAC scan general flags version 2
 *
 * The FW flags were reordered and hence the driver पूर्णांकroduce version 2
 *
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_PERIODIC: periodic or scheduled
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_PASS_ALL: pass all probe responses and beacons
 *                                       during scan iterations
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_NTFY_ITER_COMPLETE: send complete notअगरication
 *      on every iteration instead of only once after the last iteration
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_FRAGMENTED_LMAC1: fragmented scan LMAC1
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_FRAGMENTED_LMAC2: fragmented scan LMAC2
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_MATCH: करोes this scan check क्रम profile matching
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_USE_ALL_RX_CHAINS: use all valid chains क्रम RX
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_ADAPTIVE_DWELL: works with adaptive dwell
 *                                             क्रम active channel
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_PREEMPTIVE: can be preempted by other requests
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_NTF_START: send notअगरication of scan start
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_MULTI_SSID: matching on multiple SSIDs
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_FORCE_PASSIVE: all the channels scanned
 *                                           as passive
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_TRIGGER_UHB_SCAN: at the end of 2.4GHz and
 *		5.2Ghz bands scan, trigger scan on 6GHz band to discover
 *		the reported collocated APs
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_6GHZ_PASSIVE_SCAN: at the end of 2.4GHz and 5GHz
 *      bands scan, अगर not APs were discovered, allow scan to conitnue and scan
 *      6GHz PSC channels in order to discover country inक्रमmation.
 * @IWL_UMAC_SCAN_GEN_FLAGS_V2_6GHZ_PASSIVE_SCAN_FILTER_IN: in हाल
 *      &IWL_UMAC_SCAN_GEN_FLAGS_V2_6GHZ_PASSIVE_SCAN is enabled and scan is
 *      activated over 6GHz PSC channels, filter in beacons and probe responses.
 */
क्रमागत iwl_umac_scan_general_flags_v2 अणु
	IWL_UMAC_SCAN_GEN_FLAGS_V2_PERIODIC             = BIT(0),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_PASS_ALL             = BIT(1),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_NTFY_ITER_COMPLETE   = BIT(2),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_FRAGMENTED_LMAC1     = BIT(3),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_FRAGMENTED_LMAC2     = BIT(4),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_MATCH                = BIT(5),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_USE_ALL_RX_CHAINS    = BIT(6),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_ADAPTIVE_DWELL       = BIT(7),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_PREEMPTIVE           = BIT(8),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_NTF_START            = BIT(9),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_MULTI_SSID           = BIT(10),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_FORCE_PASSIVE        = BIT(11),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_TRIGGER_UHB_SCAN     = BIT(12),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_6GHZ_PASSIVE_SCAN    = BIT(13),
	IWL_UMAC_SCAN_GEN_FLAGS_V2_6GHZ_PASSIVE_SCAN_FILTER_IN = BIT(14),
पूर्ण;

/**
 * काष्ठा iwl_scan_channel_cfg_umac
 * @flags:		biपंचांगap - 0-19:	directed scan to i'th ssid.
 * @channel_num:	channel number 1-13 etc.
 * @band:		band of channel: 0 क्रम 2GHz, 1 क्रम 5GHz
 * @iter_count:		repetition count क्रम the channel.
 * @iter_पूर्णांकerval:	पूर्णांकerval between two scan iterations on one channel.
 */
काष्ठा  iwl_scan_channel_cfg_umac अणु
	__le32 flags;
	/* Both versions are of the same size, so use a जोड़ without adjusting
	 * the command size later
	 */
	जोड़ अणु
		काष्ठा अणु
			u8 channel_num;
			u8 iter_count;
			__le16 iter_पूर्णांकerval;
		पूर्ण v1;  /* SCAN_CHANNEL_CONFIG_API_S_VER_1 */
		काष्ठा अणु
			u8 channel_num;
			u8 band;
			u8 iter_count;
			u8 iter_पूर्णांकerval;
		 पूर्ण v2; /* SCAN_CHANNEL_CONFIG_API_S_VER_2
			* SCAN_CHANNEL_CONFIG_API_S_VER_3
			* SCAN_CHANNEL_CONFIG_API_S_VER_4
			*/
	पूर्ण;
पूर्ण __packed;

/**
 * काष्ठा iwl_scan_umac_schedule
 * @पूर्णांकerval: पूर्णांकerval in seconds between scan iterations
 * @iter_count: num of scan iterations क्रम schedule plan, 0xff क्रम infinite loop
 * @reserved: क्रम alignment and future use
 */
काष्ठा iwl_scan_umac_schedule अणु
	__le16 पूर्णांकerval;
	u8 iter_count;
	u8 reserved;
पूर्ण __packed; /* SCAN_SCHED_PARAM_API_S_VER_1 */

काष्ठा iwl_scan_req_umac_tail_v1 अणु
	/* SCAN_PERIODIC_PARAMS_API_S_VER_1 */
	काष्ठा iwl_scan_umac_schedule schedule[IWL_MAX_SCHED_SCAN_PLANS];
	__le16 delay;
	__le16 reserved;
	/* SCAN_PROBE_PARAMS_API_S_VER_1 */
	काष्ठा iwl_scan_probe_req_v1 preq;
	काष्ठा iwl_ssid_ie direct_scan[PROBE_OPTION_MAX];
पूर्ण __packed;

/**
 * काष्ठा iwl_scan_req_umac_tail - the rest of the UMAC scan request command
 *      parameters following channels configuration array.
 * @schedule: two scheduling plans.
 * @delay: delay in TUs beक्रमe starting the first scan iteration
 * @reserved: क्रम future use and alignment
 * @preq: probe request with IEs blocks
 * @direct_scan: list of SSIDs क्रम directed active scan
 */
काष्ठा iwl_scan_req_umac_tail_v2 अणु
	/* SCAN_PERIODIC_PARAMS_API_S_VER_1 */
	काष्ठा iwl_scan_umac_schedule schedule[IWL_MAX_SCHED_SCAN_PLANS];
	__le16 delay;
	__le16 reserved;
	/* SCAN_PROBE_PARAMS_API_S_VER_2 */
	काष्ठा iwl_scan_probe_req preq;
	काष्ठा iwl_ssid_ie direct_scan[PROBE_OPTION_MAX];
पूर्ण __packed;

/**
 * काष्ठा iwl_scan_umac_chan_param
 * @flags: channel flags &क्रमागत iwl_scan_channel_flags
 * @count: num of channels in scan request
 * @reserved: क्रम future use and alignment
 */
काष्ठा iwl_scan_umac_chan_param अणु
	u8 flags;
	u8 count;
	__le16 reserved;
पूर्ण __packed; /*SCAN_CHANNEL_PARAMS_API_S_VER_1 */

/**
 * काष्ठा iwl_scan_req_umac
 * @flags: &क्रमागत iwl_umac_scan_flags
 * @uid: scan id, &क्रमागत iwl_umac_scan_uid_offsets
 * @ooc_priority: out of channel priority - &क्रमागत iwl_scan_priority
 * @general_flags: &क्रमागत iwl_umac_scan_general_flags
 * @scan_start_mac_id: report the scan start TSF समय according to this mac TSF
 * @extended_dwell: dwell समय क्रम channels 1, 6 and 11
 * @active_dwell: dwell समय क्रम active scan per LMAC
 * @passive_dwell: dwell समय क्रम passive scan per LMAC
 * @fragmented_dwell: dwell समय क्रम fragmented passive scan
 * @adwell_शेष_n_aps: क्रम adaptive dwell the शेष number of APs
 *	per channel
 * @adwell_शेष_n_aps_social: क्रम adaptive dwell the शेष
 *	number of APs per social (1,6,11) channel
 * @general_flags2: &क्रमागत iwl_umac_scan_general_flags2
 * @adwell_max_budget: क्रम adaptive dwell the maximal budget of TU to be added
 *	to total scan समय
 * @max_out_समय: max out of serving channel समय, per LMAC - क्रम CDB there
 *	are 2 LMACs
 * @suspend_समय: max suspend समय, per LMAC - क्रम CDB there are 2 LMACs
 * @scan_priority: scan पूर्णांकernal prioritization &क्रमागत iwl_scan_priority
 * @num_of_fragments: Number of fragments needed क्रम full coverage per band.
 *	Relevant only क्रम fragmented scan.
 * @channel: &काष्ठा iwl_scan_umac_chan_param
 * @reserved: क्रम future use and alignment
 * @reserved3: क्रम future use and alignment
 * @data: &काष्ठा iwl_scan_channel_cfg_umac and
 *	&काष्ठा iwl_scan_req_umac_tail
 */
काष्ठा iwl_scan_req_umac अणु
	__le32 flags;
	__le32 uid;
	__le32 ooc_priority;
	__le16 general_flags;
	u8 reserved;
	u8 scan_start_mac_id;
	जोड़ अणु
		काष्ठा अणु
			u8 extended_dwell;
			u8 active_dwell;
			u8 passive_dwell;
			u8 fragmented_dwell;
			__le32 max_out_समय;
			__le32 suspend_समय;
			__le32 scan_priority;
			काष्ठा iwl_scan_umac_chan_param channel;
			u8 data[];
		पूर्ण v1; /* SCAN_REQUEST_CMD_UMAC_API_S_VER_1 */
		काष्ठा अणु
			u8 extended_dwell;
			u8 active_dwell;
			u8 passive_dwell;
			u8 fragmented_dwell;
			__le32 max_out_समय[SCAN_TWO_LMACS];
			__le32 suspend_समय[SCAN_TWO_LMACS];
			__le32 scan_priority;
			काष्ठा iwl_scan_umac_chan_param channel;
			u8 data[];
		पूर्ण v6; /* SCAN_REQUEST_CMD_UMAC_API_S_VER_6 */
		काष्ठा अणु
			u8 active_dwell;
			u8 passive_dwell;
			u8 fragmented_dwell;
			u8 adwell_शेष_n_aps;
			u8 adwell_शेष_n_aps_social;
			u8 reserved3;
			__le16 adwell_max_budget;
			__le32 max_out_समय[SCAN_TWO_LMACS];
			__le32 suspend_समय[SCAN_TWO_LMACS];
			__le32 scan_priority;
			काष्ठा iwl_scan_umac_chan_param channel;
			u8 data[];
		पूर्ण v7; /* SCAN_REQUEST_CMD_UMAC_API_S_VER_7 */
		काष्ठा अणु
			u8 active_dwell[SCAN_TWO_LMACS];
			u8 reserved2;
			u8 adwell_शेष_n_aps;
			u8 adwell_शेष_n_aps_social;
			u8 general_flags2;
			__le16 adwell_max_budget;
			__le32 max_out_समय[SCAN_TWO_LMACS];
			__le32 suspend_समय[SCAN_TWO_LMACS];
			__le32 scan_priority;
			u8 passive_dwell[SCAN_TWO_LMACS];
			u8 num_of_fragments[SCAN_TWO_LMACS];
			काष्ठा iwl_scan_umac_chan_param channel;
			u8 data[];
		पूर्ण v8; /* SCAN_REQUEST_CMD_UMAC_API_S_VER_8 */
		काष्ठा अणु
			u8 active_dwell[SCAN_TWO_LMACS];
			u8 adwell_शेष_hb_n_aps;
			u8 adwell_शेष_lb_n_aps;
			u8 adwell_शेष_n_aps_social;
			u8 general_flags2;
			__le16 adwell_max_budget;
			__le32 max_out_समय[SCAN_TWO_LMACS];
			__le32 suspend_समय[SCAN_TWO_LMACS];
			__le32 scan_priority;
			u8 passive_dwell[SCAN_TWO_LMACS];
			u8 num_of_fragments[SCAN_TWO_LMACS];
			काष्ठा iwl_scan_umac_chan_param channel;
			u8 data[];
		पूर्ण v9; /* SCAN_REQUEST_CMD_UMAC_API_S_VER_9 */
	पूर्ण;
पूर्ण __packed;

#घोषणा IWL_SCAN_REQ_UMAC_SIZE_V8 माप(काष्ठा iwl_scan_req_umac)
#घोषणा IWL_SCAN_REQ_UMAC_SIZE_V7 48
#घोषणा IWL_SCAN_REQ_UMAC_SIZE_V6 44
#घोषणा IWL_SCAN_REQ_UMAC_SIZE_V1 36

/**
 * काष्ठा iwl_scan_probe_params_v3
 * @preq: scan probe request params
 * @ssid_num: number of valid SSIDs in direct scan array
 * @लघु_ssid_num: number of valid लघु SSIDs in लघु ssid array
 * @bssid_num: number of valid bssid in bssids array
 * @reserved: reserved
 * @direct_scan: list of ssids
 * @लघु_ssid: array of लघु ssids
 * @bssid_array: array of bssids
 */
काष्ठा iwl_scan_probe_params_v3 अणु
	काष्ठा iwl_scan_probe_req preq;
	u8 ssid_num;
	u8 लघु_ssid_num;
	u8 bssid_num;
	u8 reserved;
	काष्ठा iwl_ssid_ie direct_scan[PROBE_OPTION_MAX];
	__le32 लघु_ssid[SCAN_SHORT_SSID_MAX_SIZE];
	u8 bssid_array[ETH_ALEN][SCAN_BSSID_MAX_SIZE];
पूर्ण __packed; /* SCAN_PROBE_PARAMS_API_S_VER_3 */

/**
 * काष्ठा iwl_scan_probe_params_v4
 * @preq: scan probe request params
 * @लघु_ssid_num: number of valid लघु SSIDs in लघु ssid array
 * @bssid_num: number of valid bssid in bssids array
 * @reserved: reserved
 * @direct_scan: list of ssids
 * @लघु_ssid: array of लघु ssids
 * @bssid_array: array of bssids
 */
काष्ठा iwl_scan_probe_params_v4 अणु
	काष्ठा iwl_scan_probe_req preq;
	u8 लघु_ssid_num;
	u8 bssid_num;
	__le16 reserved;
	काष्ठा iwl_ssid_ie direct_scan[PROBE_OPTION_MAX];
	__le32 लघु_ssid[SCAN_SHORT_SSID_MAX_SIZE];
	u8 bssid_array[ETH_ALEN][SCAN_BSSID_MAX_SIZE];
पूर्ण __packed; /* SCAN_PROBE_PARAMS_API_S_VER_4 */

#घोषणा SCAN_MAX_NUM_CHANS_V3 67

/**
 * काष्ठा iwl_scan_channel_params_v4
 * @flags: channel flags &क्रमागत iwl_scan_channel_flags
 * @count: num of channels in scan request
 * @num_of_aps_override: override the number of APs the FW uses to calculate
 *	dwell समय when adaptive dwell is used
 * @reserved: क्रम future use and alignment
 * @channel_config: array of explicit channel configurations
 *                  क्रम 2.4Ghz and 5.2Ghz bands
 * @adwell_ch_override_biपंचांगap: when using adaptive dwell, override the number
 *	of APs value with &num_of_aps_override क्रम the channel.
 *	To cast channel to index, use &iwl_mvm_scan_ch_and_band_to_idx
 */
काष्ठा iwl_scan_channel_params_v4 अणु
	u8 flags;
	u8 count;
	u8 num_of_aps_override;
	u8 reserved;
	काष्ठा iwl_scan_channel_cfg_umac channel_config[SCAN_MAX_NUM_CHANS_V3];
	u8 adwell_ch_override_biपंचांगap[16];
पूर्ण __packed; /* SCAN_CHANNEL_PARAMS_API_S_VER_4 also
	       SCAN_CHANNEL_PARAMS_API_S_VER_5 */

/**
 * काष्ठा iwl_scan_channel_params_v6
 * @flags: channel flags &क्रमागत iwl_scan_channel_flags
 * @count: num of channels in scan request
 * @n_aps_override: override the number of APs the FW uses to calculate dwell
 *	समय when adaptive dwell is used.
 *	Channel k will use n_aps_override[i] when BIT(20 + i) is set in
 *	channel_config[k].flags
 * @channel_config: array of explicit channel configurations
 *                  क्रम 2.4Ghz and 5.2Ghz bands
 */
काष्ठा iwl_scan_channel_params_v6 अणु
	u8 flags;
	u8 count;
	u8 n_aps_override[2];
	काष्ठा iwl_scan_channel_cfg_umac channel_config[SCAN_MAX_NUM_CHANS_V3];
पूर्ण __packed; /* SCAN_CHANNEL_PARAMS_API_S_VER_6 */

/**
 * काष्ठा iwl_scan_general_params_v10
 * @flags: &क्रमागत iwl_umac_scan_flags
 * @reserved: reserved क्रम future
 * @scan_start_mac_id: report the scan start TSF समय according to this mac TSF
 * @active_dwell: dwell समय क्रम active scan per LMAC
 * @adwell_शेष_2g: adaptive dwell शेष number of APs
 *                        क्रम 2.4GHz channel
 * @adwell_शेष_5g: adaptive dwell शेष number of APs
 *                        क्रम 5GHz channels
 * @adwell_शेष_social_chn: adaptive dwell शेष number of
 *                             APs per social channel
 * @reserved1: reserved क्रम future
 * @adwell_max_budget: the maximal number of TUs that adaptive dwell
 *                     can add to the total scan समय
 * @max_out_of_समय: max out of serving channel समय, per LMAC
 * @suspend_समय: max suspend समय, per LMAC
 * @scan_priority: priority of the request
 * @passive_dwell: जारीs dwell समय क्रम passive channel
 *                 (without adaptive dwell)
 * @num_of_fragments: number of fragments needed क्रम full fragmented
 *                    scan coverage.
 */
काष्ठा iwl_scan_general_params_v10 अणु
	__le16 flags;
	u8 reserved;
	u8 scan_start_mac_id;
	u8 active_dwell[SCAN_TWO_LMACS];
	u8 adwell_शेष_2g;
	u8 adwell_शेष_5g;
	u8 adwell_शेष_social_chn;
	u8 reserved1;
	__le16 adwell_max_budget;
	__le32 max_out_of_समय[SCAN_TWO_LMACS];
	__le32 suspend_समय[SCAN_TWO_LMACS];
	__le32 scan_priority;
	u8 passive_dwell[SCAN_TWO_LMACS];
	u8 num_of_fragments[SCAN_TWO_LMACS];
पूर्ण __packed; /* SCAN_GENERAL_PARAMS_API_S_VER_10 */

/**
 * काष्ठा iwl_scan_periodic_parms_v1
 * @schedule: can scheduling parameter
 * @delay: initial delay of the periodic scan in seconds
 * @reserved: reserved क्रम future
 */
काष्ठा iwl_scan_periodic_parms_v1 अणु
	काष्ठा iwl_scan_umac_schedule schedule[IWL_MAX_SCHED_SCAN_PLANS];
	__le16 delay;
	__le16 reserved;
पूर्ण __packed; /* SCAN_PERIODIC_PARAMS_API_S_VER_1 */

/**
 * काष्ठा iwl_scan_req_params_v12
 * @general_params: &काष्ठा iwl_scan_general_params_v10
 * @channel_params: &काष्ठा iwl_scan_channel_params_v4
 * @periodic_params: &काष्ठा iwl_scan_periodic_parms_v1
 * @probe_params: &काष्ठा iwl_scan_probe_params_v3
 */
काष्ठा iwl_scan_req_params_v12 अणु
	काष्ठा iwl_scan_general_params_v10 general_params;
	काष्ठा iwl_scan_channel_params_v4 channel_params;
	काष्ठा iwl_scan_periodic_parms_v1 periodic_params;
	काष्ठा iwl_scan_probe_params_v3 probe_params;
पूर्ण __packed; /* SCAN_REQUEST_PARAMS_API_S_VER_12 */

/**
 * काष्ठा iwl_scan_req_params_v14
 * @general_params: &काष्ठा iwl_scan_general_params_v10
 * @channel_params: &काष्ठा iwl_scan_channel_params_v6
 * @periodic_params: &काष्ठा iwl_scan_periodic_parms_v1
 * @probe_params: &काष्ठा iwl_scan_probe_params_v4
 */
काष्ठा iwl_scan_req_params_v14 अणु
	काष्ठा iwl_scan_general_params_v10 general_params;
	काष्ठा iwl_scan_channel_params_v6 channel_params;
	काष्ठा iwl_scan_periodic_parms_v1 periodic_params;
	काष्ठा iwl_scan_probe_params_v4 probe_params;
पूर्ण __packed; /* SCAN_REQUEST_PARAMS_API_S_VER_14 */

/**
 * काष्ठा iwl_scan_req_umac_v12
 * @uid: scan id, &क्रमागत iwl_umac_scan_uid_offsets
 * @ooc_priority: out of channel priority - &क्रमागत iwl_scan_priority
 * @scan_params: scan parameters
 */
काष्ठा iwl_scan_req_umac_v12 अणु
	__le32 uid;
	__le32 ooc_priority;
	काष्ठा iwl_scan_req_params_v12 scan_params;
पूर्ण __packed; /* SCAN_REQUEST_CMD_UMAC_API_S_VER_12 */

/**
 * काष्ठा iwl_scan_req_umac_v14
 * @uid: scan id, &क्रमागत iwl_umac_scan_uid_offsets
 * @ooc_priority: out of channel priority - &क्रमागत iwl_scan_priority
 * @scan_params: scan parameters
 */
काष्ठा iwl_scan_req_umac_v14 अणु
	__le32 uid;
	__le32 ooc_priority;
	काष्ठा iwl_scan_req_params_v14 scan_params;
पूर्ण __packed; /* SCAN_REQUEST_CMD_UMAC_API_S_VER_14 */

/**
 * काष्ठा iwl_umac_scan_पात
 * @uid: scan id, &क्रमागत iwl_umac_scan_uid_offsets
 * @flags: reserved
 */
काष्ठा iwl_umac_scan_पात अणु
	__le32 uid;
	__le32 flags;
पूर्ण __packed; /* SCAN_ABORT_CMD_UMAC_API_S_VER_1 */

/**
 * काष्ठा iwl_umac_scan_complete
 * @uid: scan id, &क्रमागत iwl_umac_scan_uid_offsets
 * @last_schedule: last scheduling line
 * @last_iter: last scan iteration number
 * @status: &क्रमागत iwl_scan_offload_complete_status
 * @ebs_status: &क्रमागत iwl_scan_ebs_status
 * @समय_from_last_iter: समय elapsed from last iteration
 * @reserved: क्रम future use
 */
काष्ठा iwl_umac_scan_complete अणु
	__le32 uid;
	u8 last_schedule;
	u8 last_iter;
	u8 status;
	u8 ebs_status;
	__le32 समय_from_last_iter;
	__le32 reserved;
पूर्ण __packed; /* SCAN_COMPLETE_NTF_UMAC_API_S_VER_1 */

#घोषणा SCAN_OFFLOAD_MATCHING_CHANNELS_LEN_V1 5
#घोषणा SCAN_OFFLOAD_MATCHING_CHANNELS_LEN    7

/**
 * काष्ठा iwl_scan_offload_profile_match_v1 - match inक्रमmation
 * @bssid: matched bssid
 * @reserved: reserved
 * @channel: channel where the match occurred
 * @energy: energy
 * @matching_feature: feature matches
 * @matching_channels: biपंचांगap of channels that matched, referencing
 *	the channels passed in the scan offload request.
 */
काष्ठा iwl_scan_offload_profile_match_v1 अणु
	u8 bssid[ETH_ALEN];
	__le16 reserved;
	u8 channel;
	u8 energy;
	u8 matching_feature;
	u8 matching_channels[SCAN_OFFLOAD_MATCHING_CHANNELS_LEN_V1];
पूर्ण __packed; /* SCAN_OFFLOAD_PROखाता_MATCH_RESULTS_S_VER_1 */

/**
 * काष्ठा iwl_scan_offload_profiles_query_v1 - match results query response
 * @matched_profiles: biपंचांगap of matched profiles, referencing the
 *	matches passed in the scan offload request
 * @last_scan_age: age of the last offloaded scan
 * @n_scans_करोne: number of offloaded scans करोne
 * @gp2_d0u: GP2 when D0U occurred
 * @gp2_invoked: GP2 when scan offload was invoked
 * @resume_जबतक_scanning: not used
 * @self_recovery: obsolete
 * @reserved: reserved
 * @matches: array of match inक्रमmation, one क्रम each match
 */
काष्ठा iwl_scan_offload_profiles_query_v1 अणु
	__le32 matched_profiles;
	__le32 last_scan_age;
	__le32 n_scans_करोne;
	__le32 gp2_d0u;
	__le32 gp2_invoked;
	u8 resume_जबतक_scanning;
	u8 self_recovery;
	__le16 reserved;
	काष्ठा iwl_scan_offload_profile_match_v1 matches[0];
पूर्ण __packed; /* SCAN_OFFLOAD_PROखाताS_QUERY_RSP_S_VER_2 */

/**
 * काष्ठा iwl_scan_offload_profile_match - match inक्रमmation
 * @bssid: matched bssid
 * @reserved: reserved
 * @channel: channel where the match occurred
 * @energy: energy
 * @matching_feature: feature matches
 * @matching_channels: biपंचांगap of channels that matched, referencing
 *	the channels passed in the scan offload request.
 */
काष्ठा iwl_scan_offload_profile_match अणु
	u8 bssid[ETH_ALEN];
	__le16 reserved;
	u8 channel;
	u8 energy;
	u8 matching_feature;
	u8 matching_channels[SCAN_OFFLOAD_MATCHING_CHANNELS_LEN];
पूर्ण __packed; /* SCAN_OFFLOAD_PROखाता_MATCH_RESULTS_S_VER_2 */

/**
 * काष्ठा iwl_scan_offload_profiles_query - match results query response
 * @matched_profiles: biपंचांगap of matched profiles, referencing the
 *	matches passed in the scan offload request
 * @last_scan_age: age of the last offloaded scan
 * @n_scans_करोne: number of offloaded scans करोne
 * @gp2_d0u: GP2 when D0U occurred
 * @gp2_invoked: GP2 when scan offload was invoked
 * @resume_जबतक_scanning: not used
 * @self_recovery: obsolete
 * @reserved: reserved
 * @matches: array of match inक्रमmation, one क्रम each match
 */
काष्ठा iwl_scan_offload_profiles_query अणु
	__le32 matched_profiles;
	__le32 last_scan_age;
	__le32 n_scans_करोne;
	__le32 gp2_d0u;
	__le32 gp2_invoked;
	u8 resume_जबतक_scanning;
	u8 self_recovery;
	__le16 reserved;
	काष्ठा iwl_scan_offload_profile_match matches[0];
पूर्ण __packed; /* SCAN_OFFLOAD_PROखाताS_QUERY_RSP_S_VER_3 */

/**
 * काष्ठा iwl_umac_scan_iter_complete_notअगर - notअगरies end of scanning iteration
 * @uid: scan id, &क्रमागत iwl_umac_scan_uid_offsets
 * @scanned_channels: number of channels scanned and number of valid elements in
 *	results array
 * @status: one of SCAN_COMP_STATUS_*
 * @bt_status: BT on/off status
 * @last_channel: last channel that was scanned
 * @start_tsf: TSF समयr in usecs of the scan start समय क्रम the mac specअगरied
 *	in &काष्ठा iwl_scan_req_umac.
 * @results: array of scan results, length in @scanned_channels
 */
काष्ठा iwl_umac_scan_iter_complete_notअगर अणु
	__le32 uid;
	u8 scanned_channels;
	u8 status;
	u8 bt_status;
	u8 last_channel;
	__le64 start_tsf;
	काष्ठा iwl_scan_results_notअगर results[];
पूर्ण __packed; /* SCAN_ITER_COMPLETE_NTF_UMAC_API_S_VER_2 */

#पूर्ण_अगर /* __iwl_fw_api_scan_h__ */
