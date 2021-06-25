<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_sta_h__
#घोषणा __iwl_fw_api_sta_h__

/**
 * क्रमागत iwl_sta_flags - flags क्रम the ADD_STA host command
 * @STA_FLG_REDUCED_TX_PWR_CTRL: reduced TX घातer (control frames)
 * @STA_FLG_REDUCED_TX_PWR_DATA: reduced TX घातer (data frames)
 * @STA_FLG_DISABLE_TX: set अगर TX should be disabled
 * @STA_FLG_PS: set अगर STA is in Power Save
 * @STA_FLG_DRAIN_FLOW: drain flow
 * @STA_FLG_PAN: STA is क्रम PAN पूर्णांकerface
 * @STA_FLG_CLASS_AUTH: station is authenticated
 * @STA_FLG_CLASS_ASSOC: station is associated
 * @STA_FLG_RTS_MIMO_PROT: station requires RTS MIMO protection (dynamic SMPS)
 * @STA_FLG_MAX_AGG_SIZE_MSK: maximal size क्रम A-MPDU (mask)
 * @STA_FLG_MAX_AGG_SIZE_SHIFT: maximal size क्रम A-MPDU (bit shअगरt)
 * @STA_FLG_MAX_AGG_SIZE_8K: maximal size क्रम A-MPDU (8k supported)
 * @STA_FLG_MAX_AGG_SIZE_16K: maximal size क्रम A-MPDU (16k supported)
 * @STA_FLG_MAX_AGG_SIZE_32K: maximal size क्रम A-MPDU (32k supported)
 * @STA_FLG_MAX_AGG_SIZE_64K: maximal size क्रम A-MPDU (64k supported)
 * @STA_FLG_MAX_AGG_SIZE_128K: maximal size क्रम A-MPDU (128k supported)
 * @STA_FLG_MAX_AGG_SIZE_256K: maximal size क्रम A-MPDU (256k supported)
 * @STA_FLG_MAX_AGG_SIZE_512K: maximal size क्रम A-MPDU (512k supported)
 * @STA_FLG_MAX_AGG_SIZE_1024K: maximal size क्रम A-MPDU (1024k supported)
 * @STA_FLG_AGG_MPDU_DENS_MSK: maximal MPDU density क्रम Tx aggregation
 * @STA_FLG_FAT_EN_MSK: support क्रम channel width (क्रम Tx). This flag is
 *	initialised by driver and can be updated by fw upon reception of
 *	action frames that can change the channel width. When cleared the fw
 *	will send all the frames in 20MHz even when FAT channel is requested.
 * @STA_FLG_FAT_EN_20MHZ: no wide channels are supported, only 20 MHz
 * @STA_FLG_FAT_EN_40MHZ: wide channels up to 40 MHz supported
 * @STA_FLG_FAT_EN_80MHZ: wide channels up to 80 MHz supported
 * @STA_FLG_FAT_EN_160MHZ: wide channels up to 160 MHz supported
 * @STA_FLG_MIMO_EN_MSK: support क्रम MIMO. This flag is initialised by the
 *	driver and can be updated by fw upon reception of action frames.
 * @STA_FLG_MIMO_EN_SISO: no support क्रम MIMO
 * @STA_FLG_MIMO_EN_MIMO2: 2 streams supported
 * @STA_FLG_MIMO_EN_MIMO3: 3 streams supported
 * @STA_FLG_AGG_MPDU_DENS_MSK: A-MPDU density (mask)
 * @STA_FLG_AGG_MPDU_DENS_SHIFT: A-MPDU density (bit shअगरt)
 * @STA_FLG_AGG_MPDU_DENS_2US: A-MPDU density (2 usec gap)
 * @STA_FLG_AGG_MPDU_DENS_4US: A-MPDU density (4 usec gap)
 * @STA_FLG_AGG_MPDU_DENS_8US: A-MPDU density (8 usec gap)
 * @STA_FLG_AGG_MPDU_DENS_16US: A-MPDU density (16 usec gap)
 */
क्रमागत iwl_sta_flags अणु
	STA_FLG_REDUCED_TX_PWR_CTRL	= BIT(3),
	STA_FLG_REDUCED_TX_PWR_DATA	= BIT(6),

	STA_FLG_DISABLE_TX		= BIT(4),

	STA_FLG_PS			= BIT(8),
	STA_FLG_DRAIN_FLOW		= BIT(12),
	STA_FLG_PAN			= BIT(13),
	STA_FLG_CLASS_AUTH		= BIT(14),
	STA_FLG_CLASS_ASSOC		= BIT(15),
	STA_FLG_RTS_MIMO_PROT		= BIT(17),

	STA_FLG_MAX_AGG_SIZE_SHIFT	= 19,
	STA_FLG_MAX_AGG_SIZE_8K		= (0 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_16K	= (1 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_32K	= (2 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_64K	= (3 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_128K	= (4 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_256K	= (5 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_512K	= (6 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_1024K	= (7 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_2M		= (8 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_4M		= (9 << STA_FLG_MAX_AGG_SIZE_SHIFT),
	STA_FLG_MAX_AGG_SIZE_MSK	= (0xf << STA_FLG_MAX_AGG_SIZE_SHIFT),

	STA_FLG_AGG_MPDU_DENS_SHIFT	= 23,
	STA_FLG_AGG_MPDU_DENS_2US	= (4 << STA_FLG_AGG_MPDU_DENS_SHIFT),
	STA_FLG_AGG_MPDU_DENS_4US	= (5 << STA_FLG_AGG_MPDU_DENS_SHIFT),
	STA_FLG_AGG_MPDU_DENS_8US	= (6 << STA_FLG_AGG_MPDU_DENS_SHIFT),
	STA_FLG_AGG_MPDU_DENS_16US	= (7 << STA_FLG_AGG_MPDU_DENS_SHIFT),
	STA_FLG_AGG_MPDU_DENS_MSK	= (7 << STA_FLG_AGG_MPDU_DENS_SHIFT),

	STA_FLG_FAT_EN_20MHZ		= (0 << 26),
	STA_FLG_FAT_EN_40MHZ		= (1 << 26),
	STA_FLG_FAT_EN_80MHZ		= (2 << 26),
	STA_FLG_FAT_EN_160MHZ		= (3 << 26),
	STA_FLG_FAT_EN_MSK		= (3 << 26),

	STA_FLG_MIMO_EN_SISO		= (0 << 28),
	STA_FLG_MIMO_EN_MIMO2		= (1 << 28),
	STA_FLG_MIMO_EN_MIMO3		= (2 << 28),
	STA_FLG_MIMO_EN_MSK		= (3 << 28),
पूर्ण;

/**
 * क्रमागत iwl_sta_key_flag - key flags क्रम the ADD_STA host command
 * @STA_KEY_FLG_NO_ENC: no encryption
 * @STA_KEY_FLG_WEP: WEP encryption algorithm
 * @STA_KEY_FLG_CCM: CCMP encryption algorithm
 * @STA_KEY_FLG_TKIP: TKIP encryption algorithm
 * @STA_KEY_FLG_EXT: extended cipher algorithm (depends on the FW support)
 * @STA_KEY_FLG_GCMP: GCMP encryption algorithm
 * @STA_KEY_FLG_CMAC: CMAC encryption algorithm
 * @STA_KEY_FLG_ENC_UNKNOWN: unknown encryption algorithm
 * @STA_KEY_FLG_EN_MSK: mask क्रम encryption algorithmi value
 * @STA_KEY_FLG_WEP_KEY_MAP: wep is either a group key (0 - legacy WEP) or from
 *	station info array (1 - n 1X mode)
 * @STA_KEY_FLG_KEYID_MSK: the index of the key
 * @STA_KEY_FLG_KEYID_POS: key index bit position
 * @STA_KEY_NOT_VALID: key is invalid
 * @STA_KEY_FLG_WEP_13BYTES: set क्रम 13 bytes WEP key
 * @STA_KEY_FLG_KEY_32BYTES: क्रम non-wep key set क्रम 32 bytes key
 * @STA_KEY_MULTICAST: set क्रम multical key
 * @STA_KEY_MFP: key is used क्रम Management Frame Protection
 */
क्रमागत iwl_sta_key_flag अणु
	STA_KEY_FLG_NO_ENC		= (0 << 0),
	STA_KEY_FLG_WEP			= (1 << 0),
	STA_KEY_FLG_CCM			= (2 << 0),
	STA_KEY_FLG_TKIP		= (3 << 0),
	STA_KEY_FLG_EXT			= (4 << 0),
	STA_KEY_FLG_GCMP		= (5 << 0),
	STA_KEY_FLG_CMAC		= (6 << 0),
	STA_KEY_FLG_ENC_UNKNOWN		= (7 << 0),
	STA_KEY_FLG_EN_MSK		= (7 << 0),

	STA_KEY_FLG_WEP_KEY_MAP		= BIT(3),
	STA_KEY_FLG_KEYID_POS		 = 8,
	STA_KEY_FLG_KEYID_MSK		= (3 << STA_KEY_FLG_KEYID_POS),
	STA_KEY_NOT_VALID		= BIT(11),
	STA_KEY_FLG_WEP_13BYTES		= BIT(12),
	STA_KEY_FLG_KEY_32BYTES		= BIT(12),
	STA_KEY_MULTICAST		= BIT(14),
	STA_KEY_MFP			= BIT(15),
पूर्ण;

/**
 * क्रमागत iwl_sta_modअगरy_flag - indicate to the fw what flag are being changed
 * @STA_MODIFY_QUEUE_REMOVAL: this command हटाओs a queue
 * @STA_MODIFY_TID_DISABLE_TX: this command modअगरies %tid_disable_tx
 * @STA_MODIFY_UAPSD_ACS: this command modअगरies %uapsd_acs
 * @STA_MODIFY_ADD_BA_TID: this command modअगरies %add_immediate_ba_tid
 * @STA_MODIFY_REMOVE_BA_TID: this command modअगरies %हटाओ_immediate_ba_tid
 * @STA_MODIFY_SLEEPING_STA_TX_COUNT: this command modअगरies %sleep_tx_count
 * @STA_MODIFY_PROT_TH: modअगरy RTS threshold
 * @STA_MODIFY_QUEUES: modअगरy the queues used by this station
 */
क्रमागत iwl_sta_modअगरy_flag अणु
	STA_MODIFY_QUEUE_REMOVAL		= BIT(0),
	STA_MODIFY_TID_DISABLE_TX		= BIT(1),
	STA_MODIFY_UAPSD_ACS			= BIT(2),
	STA_MODIFY_ADD_BA_TID			= BIT(3),
	STA_MODIFY_REMOVE_BA_TID		= BIT(4),
	STA_MODIFY_SLEEPING_STA_TX_COUNT	= BIT(5),
	STA_MODIFY_PROT_TH			= BIT(6),
	STA_MODIFY_QUEUES			= BIT(7),
पूर्ण;

/**
 * क्रमागत iwl_sta_mode - station command mode
 * @STA_MODE_ADD: add new station
 * @STA_MODE_MODIFY: modअगरy the station
 */
क्रमागत iwl_sta_mode अणु
	STA_MODE_ADD	= 0,
	STA_MODE_MODIFY	= 1,
पूर्ण;

/**
 * क्रमागत iwl_sta_sleep_flag - type of sleep of the station
 * @STA_SLEEP_STATE_AWAKE: station is awake
 * @STA_SLEEP_STATE_PS_POLL: station is PS-polling
 * @STA_SLEEP_STATE_UAPSD: station uses U-APSD
 * @STA_SLEEP_STATE_MOREDATA: set more-data bit on
 *	(last) released frame
 */
क्रमागत iwl_sta_sleep_flag अणु
	STA_SLEEP_STATE_AWAKE		= 0,
	STA_SLEEP_STATE_PS_POLL		= BIT(0),
	STA_SLEEP_STATE_UAPSD		= BIT(1),
	STA_SLEEP_STATE_MOREDATA	= BIT(2),
पूर्ण;

#घोषणा STA_KEY_MAX_NUM (16)
#घोषणा STA_KEY_IDX_INVALID (0xff)
#घोषणा STA_KEY_MAX_DATA_KEY_NUM (4)
#घोषणा IWL_MAX_GLOBAL_KEYS (4)
#घोषणा STA_KEY_LEN_WEP40 (5)
#घोषणा STA_KEY_LEN_WEP104 (13)

#घोषणा IWL_ADD_STA_STATUS_MASK		0xFF
#घोषणा IWL_ADD_STA_BAID_VALID_MASK	0x8000
#घोषणा IWL_ADD_STA_BAID_MASK		0x7F00
#घोषणा IWL_ADD_STA_BAID_SHIFT		8

/**
 * काष्ठा iwl_mvm_add_sta_cmd_v7 - Add/modअगरy a station in the fw's sta table.
 * ( REPLY_ADD_STA = 0x18 )
 * @add_modअगरy: see &क्रमागत iwl_sta_mode
 * @awake_acs: ACs to transmit data on जबतक station is sleeping (क्रम U-APSD)
 * @tid_disable_tx: is tid BIT(tid) enabled क्रम Tx. Clear BIT(x) to enable
 *	AMPDU क्रम tid x. Set %STA_MODIFY_TID_DISABLE_TX to change this field.
 * @mac_id_n_color: the Mac context this station beदीर्घs to,
 *	see &क्रमागत iwl_ctxt_id_and_color
 * @addr: station's MAC address
 * @reserved2: reserved
 * @sta_id: index of station in uCode's station table
 * @modअगरy_mask: from &क्रमागत iwl_sta_modअगरy_flag, selects what to change
 * @reserved3: reserved
 * @station_flags: look at &क्रमागत iwl_sta_flags
 * @station_flags_msk: what of %station_flags have changed,
 *	also &क्रमागत iwl_sta_flags
 * @add_immediate_ba_tid: tid क्रम which to add block-ack support (Rx)
 *	Set %STA_MODIFY_ADD_BA_TID to use this field, and also set
 *	add_immediate_ba_ssn.
 * @हटाओ_immediate_ba_tid: tid क्रम which to हटाओ block-ack support (Rx)
 *	Set %STA_MODIFY_REMOVE_BA_TID to use this field
 * @add_immediate_ba_ssn: ssn क्रम the Rx block-ack session. Used together with
 *	add_immediate_ba_tid.
 * @sleep_tx_count: number of packets to transmit to station even though it is
 *	asleep. Used to synchronise PS-poll and u-APSD responses जबतक ucode
 *	keeps track of STA sleep state.
 * @sleep_state_flags: Look at &क्रमागत iwl_sta_sleep_flag.
 * @assoc_id: assoc_id to be sent in VHT PLCP (9-bit), क्रम grp use 0, क्रम AP
 *	mac-addr.
 * @beamक्रमm_flags: beam क्रमming controls
 * @tfd_queue_msk: tfd queues used by this station
 *
 * The device contains an पूर्णांकernal table of per-station inक्रमmation, with info
 * on security keys, aggregation parameters, and Tx rates क्रम initial Tx
 * attempt and any retries (set by REPLY_TX_LINK_QUALITY_CMD).
 *
 * ADD_STA sets up the table entry क्रम one station, either creating a new
 * entry, or modअगरying a pre-existing one.
 */
काष्ठा iwl_mvm_add_sta_cmd_v7 अणु
	u8 add_modअगरy;
	u8 awake_acs;
	__le16 tid_disable_tx;
	__le32 mac_id_n_color;
	u8 addr[ETH_ALEN];	/* _STA_ID_MODIFY_INFO_API_S_VER_1 */
	__le16 reserved2;
	u8 sta_id;
	u8 modअगरy_mask;
	__le16 reserved3;
	__le32 station_flags;
	__le32 station_flags_msk;
	u8 add_immediate_ba_tid;
	u8 हटाओ_immediate_ba_tid;
	__le16 add_immediate_ba_ssn;
	__le16 sleep_tx_count;
	__le16 sleep_state_flags;
	__le16 assoc_id;
	__le16 beamक्रमm_flags;
	__le32 tfd_queue_msk;
पूर्ण __packed; /* ADD_STA_CMD_API_S_VER_7 */

/**
 * क्रमागत iwl_sta_type - FW station types
 * ( REPLY_ADD_STA = 0x18 )
 * @IWL_STA_LINK: Link station - normal RX and TX traffic.
 * @IWL_STA_GENERAL_PURPOSE: General purpose. In AP mode used क्रम beacons
 *	and probe responses.
 * @IWL_STA_MULTICAST: multicast traffic,
 * @IWL_STA_TDLS_LINK: TDLS link station
 * @IWL_STA_AUX_ACTIVITY: auxilary station (scan, ROC and so on).
 */
क्रमागत iwl_sta_type अणु
	IWL_STA_LINK,
	IWL_STA_GENERAL_PURPOSE,
	IWL_STA_MULTICAST,
	IWL_STA_TDLS_LINK,
	IWL_STA_AUX_ACTIVITY,
पूर्ण;

/**
 * काष्ठा iwl_mvm_add_sta_cmd - Add/modअगरy a station in the fw's sta table.
 * ( REPLY_ADD_STA = 0x18 )
 * @add_modअगरy: see &क्रमागत iwl_sta_mode
 * @awake_acs: ACs to transmit data on जबतक station is sleeping (क्रम U-APSD)
 * @tid_disable_tx: is tid BIT(tid) enabled क्रम Tx. Clear BIT(x) to enable
 *	AMPDU क्रम tid x. Set %STA_MODIFY_TID_DISABLE_TX to change this field.
 * @mac_id_n_color: the Mac context this station beदीर्घs to,
 *	see &क्रमागत iwl_ctxt_id_and_color
 * @addr: station's MAC address
 * @reserved2: reserved
 * @sta_id: index of station in uCode's station table
 * @modअगरy_mask: from &क्रमागत iwl_sta_modअगरy_flag, selects what to change
 * @reserved3: reserved
 * @station_flags: look at &क्रमागत iwl_sta_flags
 * @station_flags_msk: what of %station_flags have changed,
 *	also &क्रमागत iwl_sta_flags
 * @add_immediate_ba_tid: tid क्रम which to add block-ack support (Rx)
 *	Set %STA_MODIFY_ADD_BA_TID to use this field, and also set
 *	add_immediate_ba_ssn.
 * @हटाओ_immediate_ba_tid: tid क्रम which to हटाओ block-ack support (Rx)
 *	Set %STA_MODIFY_REMOVE_BA_TID to use this field
 * @add_immediate_ba_ssn: ssn क्रम the Rx block-ack session. Used together with
 *	add_immediate_ba_tid.
 * @sleep_tx_count: number of packets to transmit to station even though it is
 *	asleep. Used to synchronise PS-poll and u-APSD responses जबतक ucode
 *	keeps track of STA sleep state.
 * @station_type: type of this station. See &क्रमागत iwl_sta_type.
 * @sleep_state_flags: Look at &क्रमागत iwl_sta_sleep_flag.
 * @assoc_id: assoc_id to be sent in VHT PLCP (9-bit), क्रम grp use 0, क्रम AP
 *	mac-addr.
 * @beamक्रमm_flags: beam क्रमming controls
 * @tfd_queue_msk: tfd queues used by this station.
 *	Obselete क्रम new TX API (9 and above).
 * @rx_ba_winकरोw: aggregation winकरोw size
 * @sp_length: the size of the SP in actual number of frames
 * @uapsd_acs:  4 LS bits are trigger enabled ACs, 4 MS bits are the deliver
 *	enabled ACs.
 *
 * The device contains an पूर्णांकernal table of per-station inक्रमmation, with info
 * on security keys, aggregation parameters, and Tx rates क्रम initial Tx
 * attempt and any retries (set by REPLY_TX_LINK_QUALITY_CMD).
 *
 * ADD_STA sets up the table entry क्रम one station, either creating a new
 * entry, or modअगरying a pre-existing one.
 */
काष्ठा iwl_mvm_add_sta_cmd अणु
	u8 add_modअगरy;
	u8 awake_acs;
	__le16 tid_disable_tx;
	__le32 mac_id_n_color;  /* can be used क्रम lmac id when using cmd v12 */
	u8 addr[ETH_ALEN];	/* _STA_ID_MODIFY_INFO_API_S_VER_1 */
	__le16 reserved2;
	u8 sta_id;
	u8 modअगरy_mask;
	__le16 reserved3;
	__le32 station_flags;
	__le32 station_flags_msk;
	u8 add_immediate_ba_tid;
	u8 हटाओ_immediate_ba_tid;
	__le16 add_immediate_ba_ssn;
	__le16 sleep_tx_count;
	u8 sleep_state_flags;
	u8 station_type;
	__le16 assoc_id;
	__le16 beamक्रमm_flags;
	__le32 tfd_queue_msk;
	__le16 rx_ba_winकरोw;
	u8 sp_length;
	u8 uapsd_acs;
पूर्ण __packed; /* ADD_STA_CMD_API_S_VER_10 */

/**
 * काष्ठा iwl_mvm_add_sta_key_common - add/modअगरy sta key common part
 * ( REPLY_ADD_STA_KEY = 0x17 )
 * @sta_id: index of station in uCode's station table
 * @key_offset: key offset in key storage
 * @key_flags: type &क्रमागत iwl_sta_key_flag
 * @key: key material data
 * @rx_secur_seq_cnt: RX security sequence counter क्रम the key
 */
काष्ठा iwl_mvm_add_sta_key_common अणु
	u8 sta_id;
	u8 key_offset;
	__le16 key_flags;
	u8 key[32];
	u8 rx_secur_seq_cnt[16];
पूर्ण __packed;

/**
 * काष्ठा iwl_mvm_add_sta_key_cmd_v1 - add/modअगरy sta key
 * @common: see &काष्ठा iwl_mvm_add_sta_key_common
 * @tkip_rx_tsc_byte2: TSC[2] क्रम key mix ph1 detection
 * @reserved: reserved
 * @tkip_rx_ttak: 10-byte unicast TKIP TTAK क्रम Rx
 */
काष्ठा iwl_mvm_add_sta_key_cmd_v1 अणु
	काष्ठा iwl_mvm_add_sta_key_common common;
	u8 tkip_rx_tsc_byte2;
	u8 reserved;
	__le16 tkip_rx_ttak[5];
पूर्ण __packed; /* ADD_MODIFY_STA_KEY_API_S_VER_1 */

/**
 * काष्ठा iwl_mvm_add_sta_key_cmd - add/modअगरy sta key
 * @common: see &काष्ठा iwl_mvm_add_sta_key_common
 * @rx_mic_key: TKIP RX unicast or multicast key
 * @tx_mic_key: TKIP TX key
 * @transmit_seq_cnt: TSC, transmit packet number
 */
काष्ठा iwl_mvm_add_sta_key_cmd अणु
	काष्ठा iwl_mvm_add_sta_key_common common;
	__le64 rx_mic_key;
	__le64 tx_mic_key;
	__le64 transmit_seq_cnt;
पूर्ण __packed; /* ADD_MODIFY_STA_KEY_API_S_VER_2 */

/**
 * क्रमागत iwl_mvm_add_sta_rsp_status - status in the response to ADD_STA command
 * @ADD_STA_SUCCESS: operation was executed successfully
 * @ADD_STA_STATIONS_OVERLOAD: no room left in the fw's station table
 * @ADD_STA_IMMEDIATE_BA_FAILURE: can't add Rx block ack session
 * @ADD_STA_MODIFY_NON_EXISTING_STA: driver requested to modअगरy a station that
 *	करोesn't exist.
 */
क्रमागत iwl_mvm_add_sta_rsp_status अणु
	ADD_STA_SUCCESS			= 0x1,
	ADD_STA_STATIONS_OVERLOAD	= 0x2,
	ADD_STA_IMMEDIATE_BA_FAILURE	= 0x4,
	ADD_STA_MODIFY_NON_EXISTING_STA	= 0x8,
पूर्ण;

/**
 * काष्ठा iwl_mvm_rm_sta_cmd - Add / modअगरy a station in the fw's station table
 * ( REMOVE_STA = 0x19 )
 * @sta_id: the station id of the station to be हटाओd
 * @reserved: reserved
 */
काष्ठा iwl_mvm_rm_sta_cmd अणु
	u8 sta_id;
	u8 reserved[3];
पूर्ण __packed; /* REMOVE_STA_CMD_API_S_VER_2 */

/**
 * काष्ठा iwl_mvm_mgmt_mcast_key_cmd_v1
 * ( MGMT_MCAST_KEY = 0x1f )
 * @ctrl_flags: &क्रमागत iwl_sta_key_flag
 * @igtk: IGTK key material
 * @k1: unused
 * @k2: unused
 * @sta_id: station ID that support IGTK
 * @key_id: key ID
 * @receive_seq_cnt: initial RSC/PN needed क्रम replay check
 */
काष्ठा iwl_mvm_mgmt_mcast_key_cmd_v1 अणु
	__le32 ctrl_flags;
	u8 igtk[16];
	u8 k1[16];
	u8 k2[16];
	__le32 key_id;
	__le32 sta_id;
	__le64 receive_seq_cnt;
पूर्ण __packed; /* SEC_MGMT_MULTICAST_KEY_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_mvm_mgmt_mcast_key_cmd
 * ( MGMT_MCAST_KEY = 0x1f )
 * @ctrl_flags: &क्रमागत iwl_sta_key_flag
 * @igtk: IGTK master key
 * @sta_id: station ID that support IGTK
 * @key_id: key ID
 * @receive_seq_cnt: initial RSC/PN needed क्रम replay check
 */
काष्ठा iwl_mvm_mgmt_mcast_key_cmd अणु
	__le32 ctrl_flags;
	u8 igtk[32];
	__le32 key_id;
	__le32 sta_id;
	__le64 receive_seq_cnt;
पूर्ण __packed; /* SEC_MGMT_MULTICAST_KEY_CMD_API_S_VER_2 */

काष्ठा iwl_mvm_wep_key अणु
	u8 key_index;
	u8 key_offset;
	__le16 reserved1;
	u8 key_size;
	u8 reserved2[3];
	u8 key[16];
पूर्ण __packed;

काष्ठा iwl_mvm_wep_key_cmd अणु
	__le32 mac_id_n_color;
	u8 num_keys;
	u8 decryption_type;
	u8 flags;
	u8 reserved;
	काष्ठा iwl_mvm_wep_key wep_key[0];
पूर्ण __packed; /* SEC_CURR_WEP_KEY_CMD_API_S_VER_2 */

/**
 * काष्ठा iwl_mvm_eosp_notअगरication - EOSP notअगरication from firmware
 * @reमुख्य_frame_count: # of frames reमुख्यing, non-zero अगर SP was cut
 *	लघु by GO असलence
 * @sta_id: station ID
 */
काष्ठा iwl_mvm_eosp_notअगरication अणु
	__le32 reमुख्य_frame_count;
	__le32 sta_id;
पूर्ण __packed; /* UAPSD_EOSP_NTFY_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_sta_h__ */
