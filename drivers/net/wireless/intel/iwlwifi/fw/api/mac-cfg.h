<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2019 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_mac_cfg_h__
#घोषणा __iwl_fw_api_mac_cfg_h__

/**
 * क्रमागत iwl_mac_conf_subcmd_ids - mac configuration command IDs
 */
क्रमागत iwl_mac_conf_subcmd_ids अणु
	/**
	 * @LOW_LATENCY_CMD: &काष्ठा iwl_mac_low_latency_cmd
	 */
	LOW_LATENCY_CMD = 0x3,
	/**
	 * @CHANNEL_SWITCH_TIME_EVENT_CMD: &काष्ठा iwl_chan_चयन_te_cmd
	 */
	CHANNEL_SWITCH_TIME_EVENT_CMD = 0x4,
	/**
	 * @MISSED_VAP_NOTIF: &काष्ठा iwl_missed_vap_notअगर
	 */
	MISSED_VAP_NOTIF = 0xFA,
	/**
	 * @SESSION_PROTECTION_CMD: &काष्ठा iwl_mvm_session_prot_cmd
	 */
	SESSION_PROTECTION_CMD = 0x5,

	/**
	 * @SESSION_PROTECTION_NOTIF: &काष्ठा iwl_mvm_session_prot_notअगर
	 */
	SESSION_PROTECTION_NOTIF = 0xFB,

	/**
	 * @PROBE_RESPONSE_DATA_NOTIF: &काष्ठा iwl_probe_resp_data_notअगर
	 */
	PROBE_RESPONSE_DATA_NOTIF = 0xFC,

	/**
	 * @CHANNEL_SWITCH_NOA_NOTIF: &काष्ठा iwl_channel_चयन_noa_notअगर
	 */
	CHANNEL_SWITCH_NOA_NOTIF = 0xFF,
पूर्ण;

#घोषणा IWL_P2P_NOA_DESC_COUNT	(2)

/**
 * काष्ठा iwl_p2p_noa_attr - NOA attr contained in probe resp FW notअगरication
 *
 * @id: attribute id
 * @len_low: length low half
 * @len_high: length high half
 * @idx: instance of NoA timing
 * @ctwin: GO's ct winकरोw and pwer save capability
 * @desc: NoA descriptor
 * @reserved: reserved क्रम alignment purposes
 */
काष्ठा iwl_p2p_noa_attr अणु
	u8 id;
	u8 len_low;
	u8 len_high;
	u8 idx;
	u8 ctwin;
	काष्ठा ieee80211_p2p_noa_desc desc[IWL_P2P_NOA_DESC_COUNT];
	u8 reserved;
पूर्ण __packed;

#घोषणा IWL_PROBE_RESP_DATA_NO_CSA (0xff)

/**
 * काष्ठा iwl_probe_resp_data_notअगर - notअगरication with NOA and CSA counter
 *
 * @mac_id: the mac which should send the probe response
 * @noa_active: notअगरies अगर the noa attribute should be handled
 * @noa_attr: P2P NOA attribute
 * @csa_counter: current csa counter
 * @reserved: reserved क्रम alignment purposes
 */
काष्ठा iwl_probe_resp_data_notअगर अणु
	__le32 mac_id;
	__le32 noa_active;
	काष्ठा iwl_p2p_noa_attr noa_attr;
	u8 csa_counter;
	u8 reserved[3];
पूर्ण __packed; /* PROBE_RESPONSE_DATA_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_missed_vap_notअगर - notअगरication of missing vap detection
 *
 * @mac_id: the mac क्रम which the ucode sends the notअगरication क्रम
 * @num_beacon_पूर्णांकervals_elapsed: beacons elpased with no vap profile inside
 * @profile_periodicity: beacons period to have our profile inside
 * @reserved: reserved क्रम alignment purposes
 */
काष्ठा iwl_missed_vap_notअगर अणु
	__le32 mac_id;
	u8 num_beacon_पूर्णांकervals_elapsed;
	u8 profile_periodicity;
	u8 reserved[2];
पूर्ण __packed; /* MISSED_VAP_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_channel_चयन_noa_notअगर - Channel चयन NOA notअगरication
 *
 * @id_and_color: ID and color of the MAC
 */
काष्ठा iwl_channel_चयन_noa_notअगर अणु
	__le32 id_and_color;
पूर्ण __packed; /* CHANNEL_SWITCH_START_NTFY_API_S_VER_1 */

/**
 * काष्ठा iwl_chan_चयन_te_cmd - Channel Switch Time Event command
 *
 * @mac_id: MAC ID क्रम channel चयन
 * @action: action to perक्रमm, one of FW_CTXT_ACTION_*
 * @tsf: beacon tsf
 * @cs_count: channel चयन count from CSA/eCSA IE
 * @cs_delayed_bcn_count: अगर set to N (!= 0) GO/AP can delay N beacon पूर्णांकervals
 *	at the new channel after the channel चयन, otherwise (N == 0) expect
 *	beacon right after the channel चयन.
 * @cs_mode: 1 - quiet, 0 - otherwise
 * @reserved: reserved क्रम alignment purposes
 */
काष्ठा iwl_chan_चयन_te_cmd अणु
	__le32 mac_id;
	__le32 action;
	__le32 tsf;
	u8 cs_count;
	u8 cs_delayed_bcn_count;
	u8 cs_mode;
	u8 reserved;
पूर्ण __packed; /* MAC_CHANNEL_SWITCH_TIME_EVENT_S_VER_2 */

/**
 * काष्ठा iwl_mac_low_latency_cmd - set/clear mac to 'low-latency mode'
 *
 * @mac_id: MAC ID to whom to apply the low-latency configurations
 * @low_latency_rx: 1/0 to set/clear Rx low latency direction
 * @low_latency_tx: 1/0 to set/clear Tx low latency direction
 * @reserved: reserved क्रम alignment purposes
 */
काष्ठा iwl_mac_low_latency_cmd अणु
	__le32 mac_id;
	u8 low_latency_rx;
	u8 low_latency_tx;
	__le16 reserved;
पूर्ण __packed; /* MAC_LOW_LATENCY_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_mac_cfg_h__ */
