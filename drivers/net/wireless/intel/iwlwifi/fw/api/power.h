<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2014 Intel Mobile Communications GmbH
 * Copyright (C) 2015-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_घातer_h__
#घोषणा __iwl_fw_api_घातer_h__

/* Power Management Commands, Responses, Notअगरications */

/**
 * क्रमागत iwl_ltr_config_flags - masks क्रम LTR config command flags
 * @LTR_CFG_FLAG_FEATURE_ENABLE: Feature operational status
 * @LTR_CFG_FLAG_HW_DIS_ON_SHADOW_REG_ACCESS: allow LTR change on shaकरोw
 *	memory access
 * @LTR_CFG_FLAG_HW_EN_SHRT_WR_THROUGH: allow LTR msg send on ANY LTR
 *	reg change
 * @LTR_CFG_FLAG_HW_DIS_ON_D0_2_D3: allow LTR msg send on transition from
 *	D0 to D3
 * @LTR_CFG_FLAG_SW_SET_SHORT: fixed अटल लघु LTR रेजिस्टर
 * @LTR_CFG_FLAG_SW_SET_LONG: fixed अटल लघु LONG रेजिस्टर
 * @LTR_CFG_FLAG_DENIE_C10_ON_PD: allow going पूर्णांकo C10 on PD
 * @LTR_CFG_FLAG_UPDATE_VALUES: update config values and लघु
 *	idle समयout
 */
क्रमागत iwl_ltr_config_flags अणु
	LTR_CFG_FLAG_FEATURE_ENABLE = BIT(0),
	LTR_CFG_FLAG_HW_DIS_ON_SHADOW_REG_ACCESS = BIT(1),
	LTR_CFG_FLAG_HW_EN_SHRT_WR_THROUGH = BIT(2),
	LTR_CFG_FLAG_HW_DIS_ON_D0_2_D3 = BIT(3),
	LTR_CFG_FLAG_SW_SET_SHORT = BIT(4),
	LTR_CFG_FLAG_SW_SET_LONG = BIT(5),
	LTR_CFG_FLAG_DENIE_C10_ON_PD = BIT(6),
	LTR_CFG_FLAG_UPDATE_VALUES = BIT(7),
पूर्ण;

/**
 * काष्ठा iwl_ltr_config_cmd_v1 - configures the LTR
 * @flags: See &क्रमागत iwl_ltr_config_flags
 * @अटल_दीर्घ: अटल LTR Long रेजिस्टर value.
 * @अटल_लघु: अटल LTR Short रेजिस्टर value.
 */
काष्ठा iwl_ltr_config_cmd_v1 अणु
	__le32 flags;
	__le32 अटल_दीर्घ;
	__le32 अटल_लघु;
पूर्ण __packed; /* LTR_CAPABLE_API_S_VER_1 */

#घोषणा LTR_VALID_STATES_NUM 4

/**
 * काष्ठा iwl_ltr_config_cmd - configures the LTR
 * @flags: See &क्रमागत iwl_ltr_config_flags
 * @अटल_दीर्घ: अटल LTR Long रेजिस्टर value.
 * @अटल_लघु: अटल LTR Short रेजिस्टर value.
 * @ltr_cfg_values: LTR parameters table values (in usec) in folowing order:
 *	TX, RX, Short Idle, Long Idle. Used only अगर %LTR_CFG_FLAG_UPDATE_VALUES
 *	is set.
 * @ltr_लघु_idle_समयout: LTR Short Idle समयout (in usec). Used only अगर
 *	%LTR_CFG_FLAG_UPDATE_VALUES is set.
 */
काष्ठा iwl_ltr_config_cmd अणु
	__le32 flags;
	__le32 अटल_दीर्घ;
	__le32 अटल_लघु;
	__le32 ltr_cfg_values[LTR_VALID_STATES_NUM];
	__le32 ltr_लघु_idle_समयout;
पूर्ण __packed; /* LTR_CAPABLE_API_S_VER_2 */

/* Radio LP RX Energy Threshold measured in dBm */
#घोषणा POWER_LPRX_RSSI_THRESHOLD	75
#घोषणा POWER_LPRX_RSSI_THRESHOLD_MAX	94
#घोषणा POWER_LPRX_RSSI_THRESHOLD_MIN	30

/**
 * क्रमागत iwl_घातer_flags - masks क्रम घातer table command flags
 * @POWER_FLAGS_POWER_SAVE_ENA_MSK: '1' Allow to save घातer by turning off
 *		receiver and transmitter. '0' - करोes not allow.
 * @POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK: '0' Driver disables घातer management,
 *		'1' Driver enables PM (use rest of parameters)
 * @POWER_FLAGS_SKIP_OVER_DTIM_MSK: '0' PM have to walk up every DTIM,
 *		'1' PM could sleep over DTIM till listen Interval.
 * @POWER_FLAGS_SNOOZE_ENA_MSK: Enable snoozing only अगर uAPSD is enabled and all
 *		access categories are both delivery and trigger enabled.
 * @POWER_FLAGS_BT_SCO_ENA: Enable BT SCO coex only अगर uAPSD and
 *		PBW Snoozing enabled
 * @POWER_FLAGS_ADVANCE_PM_ENA_MSK: Advanced PM (uAPSD) enable mask
 * @POWER_FLAGS_LPRX_ENA_MSK: Low Power RX enable.
 * @POWER_FLAGS_UAPSD_MISBEHAVING_ENA_MSK: AP/GO's uAPSD misbehaving
 *		detection enablement
*/
क्रमागत iwl_घातer_flags अणु
	POWER_FLAGS_POWER_SAVE_ENA_MSK		= BIT(0),
	POWER_FLAGS_POWER_MANAGEMENT_ENA_MSK	= BIT(1),
	POWER_FLAGS_SKIP_OVER_DTIM_MSK		= BIT(2),
	POWER_FLAGS_SNOOZE_ENA_MSK		= BIT(5),
	POWER_FLAGS_BT_SCO_ENA			= BIT(8),
	POWER_FLAGS_ADVANCE_PM_ENA_MSK		= BIT(9),
	POWER_FLAGS_LPRX_ENA_MSK		= BIT(11),
	POWER_FLAGS_UAPSD_MISBEHAVING_ENA_MSK	= BIT(12),
पूर्ण;

#घोषणा IWL_POWER_VEC_SIZE 5

/**
 * काष्ठा iwl_घातertable_cmd - legacy घातer command. Beside old API support this
 *	is used also with a new	घातer API क्रम device wide घातer settings.
 * POWER_TABLE_CMD = 0x77 (command, has simple generic response)
 *
 * @flags:		Power table command flags from POWER_FLAGS_*
 * @keep_alive_seconds: Keep alive period in seconds. Default - 25 sec.
 *			Minimum allowed:- 3 * DTIM. Keep alive period must be
 *			set regardless of घातer scheme or current घातer state.
 *			FW use this value also when PM is disabled.
 * @debug_flags:	debug flags
 * @rx_data_समयout:    Minimum समय (usec) from last Rx packet क्रम AM to
 *			PSM transition - legacy PM
 * @tx_data_समयout:    Minimum समय (usec) from last Tx packet क्रम AM to
 *			PSM transition - legacy PM
 * @sleep_पूर्णांकerval:	not in use
 * @skip_dtim_periods:	Number of DTIM periods to skip अगर Skip over DTIM flag
 *			is set. For example, अगर it is required to skip over
 *			one DTIM, this value need to be set to 2 (DTIM periods).
 * @lprx_rssi_threshold: Signal strength up to which LP RX can be enabled.
 *			Default: 80dbm
 */
काष्ठा iwl_घातertable_cmd अणु
	/* PM_POWER_TABLE_CMD_API_S_VER_6 */
	__le16 flags;
	u8 keep_alive_seconds;
	u8 debug_flags;
	__le32 rx_data_समयout;
	__le32 tx_data_समयout;
	__le32 sleep_पूर्णांकerval[IWL_POWER_VEC_SIZE];
	__le32 skip_dtim_periods;
	__le32 lprx_rssi_threshold;
पूर्ण __packed;

/**
 * क्रमागत iwl_device_घातer_flags - masks क्रम device घातer command flags
 * @DEVICE_POWER_FLAGS_POWER_SAVE_ENA_MSK:
 *	'1' Allow to save घातer by turning off
 *	receiver and transmitter. '0' - करोes not allow.
 * @DEVICE_POWER_FLAGS_ALLOW_MEM_RETENTION_MSK:
 *	Device Retention indication, '1' indicate retention is enabled.
 * @DEVICE_POWER_FLAGS_32K_CLK_VALID_MSK:
 *	32Khz बाह्यal slow घड़ी valid indication, '1' indicate cloack is
 *	valid.
*/
क्रमागत iwl_device_घातer_flags अणु
	DEVICE_POWER_FLAGS_POWER_SAVE_ENA_MSK		= BIT(0),
	DEVICE_POWER_FLAGS_ALLOW_MEM_RETENTION_MSK	= BIT(1),
	DEVICE_POWER_FLAGS_32K_CLK_VALID_MSK		= BIT(12),
पूर्ण;

/**
 * काष्ठा iwl_device_घातer_cmd - device wide घातer command.
 * DEVICE_POWER_CMD = 0x77 (command, has simple generic response)
 *
 * @flags:	Power table command flags from &क्रमागत iwl_device_घातer_flags
 * @reserved: reserved (padding)
 */
काष्ठा iwl_device_घातer_cmd अणु
	/* PM_POWER_TABLE_CMD_API_S_VER_6 */
	__le16 flags;
	__le16 reserved;
पूर्ण __packed;

/**
 * काष्ठा iwl_mac_घातer_cmd - New घातer command containing uAPSD support
 * MAC_PM_POWER_TABLE = 0xA9 (command, has simple generic response)
 * @id_and_color:	MAC contex identअगरier, &क्रमागत iwl_ctxt_id_and_color
 * @flags:		Power table command flags from POWER_FLAGS_*
 * @keep_alive_seconds:	Keep alive period in seconds. Default - 25 sec.
 *			Minimum allowed:- 3 * DTIM. Keep alive period must be
 *			set regardless of घातer scheme or current घातer state.
 *			FW use this value also when PM is disabled.
 * @rx_data_समयout:    Minimum समय (usec) from last Rx packet क्रम AM to
 *			PSM transition - legacy PM
 * @tx_data_समयout:    Minimum समय (usec) from last Tx packet क्रम AM to
 *			PSM transition - legacy PM
 * @skip_dtim_periods:	Number of DTIM periods to skip अगर Skip over DTIM flag
 *			is set. For example, अगर it is required to skip over
 *			one DTIM, this value need to be set to 2 (DTIM periods).
 * @rx_data_समयout_uapsd: Minimum समय (usec) from last Rx packet क्रम AM to
 *			PSM transition - uAPSD
 * @tx_data_समयout_uapsd: Minimum समय (usec) from last Tx packet क्रम AM to
 *			PSM transition - uAPSD
 * @lprx_rssi_threshold: Signal strength up to which LP RX can be enabled.
 *			Default: 80dbm
 * @snooze_पूर्णांकerval:	Maximum समय between attempts to retrieve buffered data
 *			from the AP [msec]
 * @snooze_winकरोw:	A winकरोw of समय in which PBW snoozing insures that all
 *			packets received. It is also the minimum समय from last
 *			received unicast RX packet, beक्रमe client stops snoozing
 *			क्रम data. [msec]
 * @snooze_step:	TBD
 * @qndp_tid:		TID client shall use क्रम uAPSD QNDP triggers
 * @uapsd_ac_flags:	Set trigger-enabled and delivery-enabled indication क्रम
 *			each corresponding AC.
 *			Use IEEE80211_WMM_IE_STA_QOSINFO_AC* क्रम correct values.
 * @uapsd_max_sp:	Use IEEE80211_WMM_IE_STA_QOSINFO_SP_* क्रम correct
 *			values.
 * @heavy_tx_thld_packets:	TX threshold measured in number of packets
 * @heavy_rx_thld_packets:	RX threshold measured in number of packets
 * @heavy_tx_thld_percentage:	TX threshold measured in load's percentage
 * @heavy_rx_thld_percentage:	RX threshold measured in load's percentage
 * @limited_ps_threshold: (unused)
 * @reserved: reserved (padding)
 */
काष्ठा iwl_mac_घातer_cmd अणु
	/* CONTEXT_DESC_API_T_VER_1 */
	__le32 id_and_color;

	/* CLIENT_PM_POWER_TABLE_S_VER_1 */
	__le16 flags;
	__le16 keep_alive_seconds;
	__le32 rx_data_समयout;
	__le32 tx_data_समयout;
	__le32 rx_data_समयout_uapsd;
	__le32 tx_data_समयout_uapsd;
	u8 lprx_rssi_threshold;
	u8 skip_dtim_periods;
	__le16 snooze_पूर्णांकerval;
	__le16 snooze_winकरोw;
	u8 snooze_step;
	u8 qndp_tid;
	u8 uapsd_ac_flags;
	u8 uapsd_max_sp;
	u8 heavy_tx_thld_packets;
	u8 heavy_rx_thld_packets;
	u8 heavy_tx_thld_percentage;
	u8 heavy_rx_thld_percentage;
	u8 limited_ps_threshold;
	u8 reserved;
पूर्ण __packed;

/*
 * काष्ठा iwl_uapsd_misbehaving_ap_notअगर - FW sends this notअगरication when
 * associated AP is identअगरied as improperly implementing uAPSD protocol.
 * PSM_UAPSD_AP_MISBEHAVING_NOTIFICATION = 0x78
 * @sta_id: index of station in uCode's station table - associated AP ID in
 *	    this context.
 */
काष्ठा iwl_uapsd_misbehaving_ap_notअगर अणु
	__le32 sta_id;
	u8 mac_id;
	u8 reserved[3];
पूर्ण __packed;

/**
 * काष्ठा iwl_reduce_tx_घातer_cmd - TX घातer reduction command
 * REDUCE_TX_POWER_CMD = 0x9f
 * @flags: (reserved क्रम future implementation)
 * @mac_context_id: id of the mac ctx क्रम which we are reducing TX घातer.
 * @pwr_restriction: TX घातer restriction in dBms.
 */
काष्ठा iwl_reduce_tx_घातer_cmd अणु
	u8 flags;
	u8 mac_context_id;
	__le16 pwr_restriction;
पूर्ण __packed; /* TX_REDUCED_POWER_API_S_VER_1 */

क्रमागत iwl_dev_tx_घातer_cmd_mode अणु
	IWL_TX_POWER_MODE_SET_MAC = 0,
	IWL_TX_POWER_MODE_SET_DEVICE = 1,
	IWL_TX_POWER_MODE_SET_CHAINS = 2,
	IWL_TX_POWER_MODE_SET_ACK = 3,
	IWL_TX_POWER_MODE_SET_SAR_TIMER = 4,
	IWL_TX_POWER_MODE_SET_SAR_TIMER_DEFAULT_TABLE = 5,
पूर्ण; /* TX_POWER_REDUCED_FLAGS_TYPE_API_E_VER_5 */;

#घोषणा IWL_NUM_CHAIN_TABLES	1
#घोषणा IWL_NUM_CHAIN_TABLES_V2	2
#घोषणा IWL_NUM_CHAIN_LIMITS	2
#घोषणा IWL_NUM_SUB_BANDS_V1	5
#घोषणा IWL_NUM_SUB_BANDS_V2	11

/**
 * काष्ठा iwl_dev_tx_घातer_common - Common part of the TX घातer reduction cmd
 * @set_mode: see &क्रमागत iwl_dev_tx_घातer_cmd_mode
 * @mac_context_id: id of the mac ctx क्रम which we are reducing TX घातer.
 * @pwr_restriction: TX घातer restriction in 1/8 dBms.
 * @dev_24: device TX घातer restriction in 1/8 dBms
 * @dev_52_low: device TX घातer restriction upper band - low
 * @dev_52_high: device TX घातer restriction upper band - high
 */
काष्ठा iwl_dev_tx_घातer_common अणु
	__le32 set_mode;
	__le32 mac_context_id;
	__le16 pwr_restriction;
	__le16 dev_24;
	__le16 dev_52_low;
	__le16 dev_52_high;
पूर्ण;

/**
 * काष्ठा iwl_dev_tx_घातer_cmd_v3 - TX घातer reduction command version 3
 * @per_chain: per chain restrictions
 */
काष्ठा iwl_dev_tx_घातer_cmd_v3 अणु
	__le16 per_chain[IWL_NUM_CHAIN_TABLES][IWL_NUM_CHAIN_LIMITS][IWL_NUM_SUB_BANDS_V1];
पूर्ण __packed; /* TX_REDUCED_POWER_API_S_VER_3 */

#घोषणा IWL_DEV_MAX_TX_POWER 0x7FFF

/**
 * काष्ठा iwl_dev_tx_घातer_cmd_v4 - TX घातer reduction command version 4
 * @per_chain: per chain restrictions
 * @enable_ack_reduction: enable or disable बंद range ack TX घातer
 *	reduction.
 * @reserved: reserved (padding)
 */
काष्ठा iwl_dev_tx_घातer_cmd_v4 अणु
	__le16 per_chain[IWL_NUM_CHAIN_TABLES][IWL_NUM_CHAIN_LIMITS][IWL_NUM_SUB_BANDS_V1];
	u8 enable_ack_reduction;
	u8 reserved[3];
पूर्ण __packed; /* TX_REDUCED_POWER_API_S_VER_4 */

/**
 * काष्ठा iwl_dev_tx_घातer_cmd_v5 - TX घातer reduction command version 5
 * @per_chain: per chain restrictions
 * @enable_ack_reduction: enable or disable बंद range ack TX घातer
 *	reduction.
 * @per_chain_restriction_changed: is per_chain_restriction has changed
 *	from last command. used अगर set_mode is
 *	IWL_TX_POWER_MODE_SET_SAR_TIMER.
 *	note: अगर not changed, the command is used क्रम keep alive only.
 * @reserved: reserved (padding)
 * @समयr_period: समयr in milliseconds. अगर expires FW will change to शेष
 *	BIOS values. relevant अगर setMode is IWL_TX_POWER_MODE_SET_SAR_TIMER
 */
काष्ठा iwl_dev_tx_घातer_cmd_v5 अणु
	__le16 per_chain[IWL_NUM_CHAIN_TABLES][IWL_NUM_CHAIN_LIMITS][IWL_NUM_SUB_BANDS_V1];
	u8 enable_ack_reduction;
	u8 per_chain_restriction_changed;
	u8 reserved[2];
	__le32 समयr_period;
पूर्ण __packed; /* TX_REDUCED_POWER_API_S_VER_5 */

/**
 * काष्ठा iwl_dev_tx_घातer_cmd_v5 - TX घातer reduction command version 5
 * @per_chain: per chain restrictions
 * @enable_ack_reduction: enable or disable बंद range ack TX घातer
 *	reduction.
 * @per_chain_restriction_changed: is per_chain_restriction has changed
 *	from last command. used अगर set_mode is
 *	IWL_TX_POWER_MODE_SET_SAR_TIMER.
 *	note: अगर not changed, the command is used क्रम keep alive only.
 * @reserved: reserved (padding)
 * @समयr_period: समयr in milliseconds. अगर expires FW will change to शेष
 *	BIOS values. relevant अगर setMode is IWL_TX_POWER_MODE_SET_SAR_TIMER
 */
काष्ठा iwl_dev_tx_घातer_cmd_v6 अणु
	__le16 per_chain[IWL_NUM_CHAIN_TABLES_V2][IWL_NUM_CHAIN_LIMITS][IWL_NUM_SUB_BANDS_V2];
	u8 enable_ack_reduction;
	u8 per_chain_restriction_changed;
	u8 reserved[2];
	__le32 समयr_period;
पूर्ण __packed; /* TX_REDUCED_POWER_API_S_VER_6 */

/**
 * काष्ठा iwl_dev_tx_घातer_cmd - TX घातer reduction command (multiversion)
 * @common: common part of the command
 * @v3: version 3 part of the command
 * @v4: version 4 part of the command
 * @v5: version 5 part of the command
 * @v6: version 6 part of the command
 */
काष्ठा iwl_dev_tx_घातer_cmd अणु
	काष्ठा iwl_dev_tx_घातer_common common;
	जोड़ अणु
		काष्ठा iwl_dev_tx_घातer_cmd_v3 v3;
		काष्ठा iwl_dev_tx_घातer_cmd_v4 v4;
		काष्ठा iwl_dev_tx_घातer_cmd_v5 v5;
		काष्ठा iwl_dev_tx_घातer_cmd_v6 v6;
	पूर्ण;
पूर्ण;

#घोषणा IWL_NUM_GEO_PROखाताS   3
#घोषणा IWL_NUM_BANDS_PER_CHAIN_V1 2
#घोषणा IWL_NUM_BANDS_PER_CHAIN_V2 3

/**
 * क्रमागत iwl_geo_per_chain_offset_operation - type of operation
 * @IWL_PER_CHAIN_OFFSET_SET_TABLES: send the tables from the host to the FW.
 * @IWL_PER_CHAIN_OFFSET_GET_CURRENT_TABLE: retrieve the last configured table.
 */
क्रमागत iwl_geo_per_chain_offset_operation अणु
	IWL_PER_CHAIN_OFFSET_SET_TABLES,
	IWL_PER_CHAIN_OFFSET_GET_CURRENT_TABLE,
पूर्ण;  /* GEO_TX_POWER_LIMIT FLAGS TYPE */

/**
 * काष्ठा iwl_per_chain_offset - embedded काष्ठा क्रम GEO_TX_POWER_LIMIT.
 * @max_tx_घातer: maximum allowed tx घातer.
 * @chain_a: tx घातer offset क्रम chain a.
 * @chain_b: tx घातer offset क्रम chain b.
 */
काष्ठा iwl_per_chain_offset अणु
	__le16 max_tx_घातer;
	u8 chain_a;
	u8 chain_b;
पूर्ण __packed; /* PER_CHAIN_LIMIT_OFFSET_PER_CHAIN_S_VER_1 */

/**
 * काष्ठा iwl_geo_tx_घातer_profile_cmd_v1 - काष्ठा क्रम GEO_TX_POWER_LIMIT cmd.
 * @ops: operations, value from &क्रमागत iwl_geo_per_chain_offset_operation
 * @table: offset profile per band.
 */
काष्ठा iwl_geo_tx_घातer_profiles_cmd_v1 अणु
	__le32 ops;
	काष्ठा iwl_per_chain_offset table[IWL_NUM_GEO_PROखाताS][IWL_NUM_BANDS_PER_CHAIN_V1];
पूर्ण __packed; /* GEO_TX_POWER_LIMIT_VER_1 */

/**
 * काष्ठा iwl_geo_tx_घातer_profile_cmd_v2 - काष्ठा क्रम GEO_TX_POWER_LIMIT cmd.
 * @ops: operations, value from &क्रमागत iwl_geo_per_chain_offset_operation
 * @table: offset profile per band.
 * @table_revision: BIOS table revision.
 */
काष्ठा iwl_geo_tx_घातer_profiles_cmd_v2 अणु
	__le32 ops;
	काष्ठा iwl_per_chain_offset table[IWL_NUM_GEO_PROखाताS][IWL_NUM_BANDS_PER_CHAIN_V1];
	__le32 table_revision;
पूर्ण __packed; /* GEO_TX_POWER_LIMIT_VER_2 */

/**
 * काष्ठा iwl_geo_tx_घातer_profile_cmd_v3 - काष्ठा क्रम GEO_TX_POWER_LIMIT cmd.
 * @ops: operations, value from &क्रमागत iwl_geo_per_chain_offset_operation
 * @table: offset profile per band.
 * @table_revision: BIOS table revision.
 */
काष्ठा iwl_geo_tx_घातer_profiles_cmd_v3 अणु
	__le32 ops;
	काष्ठा iwl_per_chain_offset table[IWL_NUM_GEO_PROखाताS][IWL_NUM_BANDS_PER_CHAIN_V2];
	__le32 table_revision;
पूर्ण __packed; /* GEO_TX_POWER_LIMIT_VER_3 */

जोड़ iwl_geo_tx_घातer_profiles_cmd अणु
	काष्ठा iwl_geo_tx_घातer_profiles_cmd_v1 v1;
	काष्ठा iwl_geo_tx_घातer_profiles_cmd_v2 v2;
	काष्ठा iwl_geo_tx_घातer_profiles_cmd_v3 v3;
पूर्ण;

/**
 * काष्ठा iwl_geo_tx_घातer_profiles_resp -  response to GEO_TX_POWER_LIMIT cmd
 * @profile_idx: current geo profile in use
 */
काष्ठा iwl_geo_tx_घातer_profiles_resp अणु
	__le32 profile_idx;
पूर्ण __packed; /* GEO_TX_POWER_LIMIT_RESP */

/**
 * जोड़ iwl_ppag_table_cmd - जोड़ क्रम all versions of PPAG command
 * @v1: version 1
 * @v2: version 2
 *
 * @flags: bit 0 - indicates enablement of PPAG क्रम ETSI
 *         bit 1 - indicates enablement of PPAG क्रम CHINA BIOS
 *         bit 1 can be used only in v3 (identical to v2)
 * @gain: table of antenna gain values per chain and sub-band
 * @reserved: reserved
 */
जोड़ iwl_ppag_table_cmd अणु
	काष्ठा अणु
		__le32 flags;
		s8 gain[IWL_NUM_CHAIN_LIMITS][IWL_NUM_SUB_BANDS_V1];
		s8 reserved[2];
	पूर्ण v1;
	काष्ठा अणु
		__le32 flags;
		s8 gain[IWL_NUM_CHAIN_LIMITS][IWL_NUM_SUB_BANDS_V2];
		s8 reserved[2];
	पूर्ण v2;
पूर्ण __packed;

/**
 * काष्ठा iwl_beacon_filter_cmd
 * REPLY_BEACON_FILTERING_CMD = 0xd2 (command)
 * @bf_energy_delta: Used क्रम RSSI filtering, अगर in 'normal' state. Send beacon
 *      to driver अगर delta in Energy values calculated क्रम this and last
 *      passed beacon is greater than this threshold. Zero value means that
 *      the Energy change is ignored क्रम beacon filtering, and beacon will
 *      not be क्रमced to be sent to driver regardless of this delta. Typical
 *      energy delta 5dB.
 * @bf_roaming_energy_delta: Used क्रम RSSI filtering, अगर in 'roaming' state.
 *      Send beacon to driver अगर delta in Energy values calculated क्रम this
 *      and last passed beacon is greater than this threshold. Zero value
 *      means that the Energy change is ignored क्रम beacon filtering जबतक in
 *      Roaming state, typical energy delta 1dB.
 * @bf_roaming_state: Used क्रम RSSI filtering. If असलolute Energy values
 *      calculated क्रम current beacon is less than the threshold, use
 *      Roaming Energy Delta Threshold, otherwise use normal Energy Delta
 *      Threshold. Typical energy threshold is -72dBm.
 * @bf_temp_threshold: This threshold determines the type of temperature
 *	filtering (Slow or Fast) that is selected (Units are in Celsuis):
 *	If the current temperature is above this threshold - Fast filter
 *	will be used, If the current temperature is below this threshold -
 *	Slow filter will be used.
 * @bf_temp_fast_filter: Send Beacon to driver अगर delta in temperature values
 *      calculated क्रम this and the last passed beacon is greater than this
 *      threshold. Zero value means that the temperature change is ignored क्रम
 *      beacon filtering; beacons will not be  क्रमced to be sent to driver
 *      regardless of whether its temerature has been changed.
 * @bf_temp_slow_filter: Send Beacon to driver अगर delta in temperature values
 *      calculated क्रम this and the last passed beacon is greater than this
 *      threshold. Zero value means that the temperature change is ignored क्रम
 *      beacon filtering; beacons will not be क्रमced to be sent to driver
 *      regardless of whether its temerature has been changed.
 * @bf_enable_beacon_filter: 1, beacon filtering is enabled; 0, disabled.
 * @bf_debug_flag: beacon filtering debug configuration
 * @bf_escape_समयr: Send beacons to to driver अगर no beacons were passed
 *      क्रम a specअगरic period of समय. Units: Beacons.
 * @ba_escape_समयr: Fully receive and parse beacon अगर no beacons were passed
 *      क्रम a दीर्घer period of समय then this escape-समयout. Units: Beacons.
 * @ba_enable_beacon_पात: 1, beacon पात is enabled; 0, disabled.
 * @bf_threshold_असलolute_low: See below.
 * @bf_threshold_असलolute_high: Send Beacon to driver अगर Energy value calculated
 *      क्रम this beacon crossed this असलolute threshold. For the 'Increase'
 *      direction the bf_energy_असलolute_low[i] is used. For the 'Decrease'
 *      direction the bf_energy_असलolute_high[i] is used. Zero value means
 *      that this specअगरic threshold is ignored क्रम beacon filtering, and
 *      beacon will not be क्रमced to be sent to driver due to this setting.
 */
काष्ठा iwl_beacon_filter_cmd अणु
	__le32 bf_energy_delta;
	__le32 bf_roaming_energy_delta;
	__le32 bf_roaming_state;
	__le32 bf_temp_threshold;
	__le32 bf_temp_fast_filter;
	__le32 bf_temp_slow_filter;
	__le32 bf_enable_beacon_filter;
	__le32 bf_debug_flag;
	__le32 bf_escape_समयr;
	__le32 ba_escape_समयr;
	__le32 ba_enable_beacon_पात;
	__le32 bf_threshold_असलolute_low[2];
	__le32 bf_threshold_असलolute_high[2];
पूर्ण __packed; /* BEACON_FILTER_CONFIG_API_S_VER_4 */

/* Beacon filtering and beacon पात */
#घोषणा IWL_BF_ENERGY_DELTA_DEFAULT 5
#घोषणा IWL_BF_ENERGY_DELTA_D0I3 20
#घोषणा IWL_BF_ENERGY_DELTA_MAX 255
#घोषणा IWL_BF_ENERGY_DELTA_MIN 0

#घोषणा IWL_BF_ROAMING_ENERGY_DELTA_DEFAULT 1
#घोषणा IWL_BF_ROAMING_ENERGY_DELTA_D0I3 20
#घोषणा IWL_BF_ROAMING_ENERGY_DELTA_MAX 255
#घोषणा IWL_BF_ROAMING_ENERGY_DELTA_MIN 0

#घोषणा IWL_BF_ROAMING_STATE_DEFAULT 72
#घोषणा IWL_BF_ROAMING_STATE_D0I3 72
#घोषणा IWL_BF_ROAMING_STATE_MAX 255
#घोषणा IWL_BF_ROAMING_STATE_MIN 0

#घोषणा IWL_BF_TEMP_THRESHOLD_DEFAULT 112
#घोषणा IWL_BF_TEMP_THRESHOLD_D0I3 112
#घोषणा IWL_BF_TEMP_THRESHOLD_MAX 255
#घोषणा IWL_BF_TEMP_THRESHOLD_MIN 0

#घोषणा IWL_BF_TEMP_FAST_FILTER_DEFAULT 1
#घोषणा IWL_BF_TEMP_FAST_FILTER_D0I3 1
#घोषणा IWL_BF_TEMP_FAST_FILTER_MAX 255
#घोषणा IWL_BF_TEMP_FAST_FILTER_MIN 0

#घोषणा IWL_BF_TEMP_SLOW_FILTER_DEFAULT 5
#घोषणा IWL_BF_TEMP_SLOW_FILTER_D0I3 20
#घोषणा IWL_BF_TEMP_SLOW_FILTER_MAX 255
#घोषणा IWL_BF_TEMP_SLOW_FILTER_MIN 0

#घोषणा IWL_BF_ENABLE_BEACON_FILTER_DEFAULT 1

#घोषणा IWL_BF_DEBUG_FLAG_DEFAULT 0
#घोषणा IWL_BF_DEBUG_FLAG_D0I3 0

#घोषणा IWL_BF_ESCAPE_TIMER_DEFAULT 0
#घोषणा IWL_BF_ESCAPE_TIMER_D0I3 0
#घोषणा IWL_BF_ESCAPE_TIMER_MAX 1024
#घोषणा IWL_BF_ESCAPE_TIMER_MIN 0

#घोषणा IWL_BA_ESCAPE_TIMER_DEFAULT 6
#घोषणा IWL_BA_ESCAPE_TIMER_D0I3 6
#घोषणा IWL_BA_ESCAPE_TIMER_D3 9
#घोषणा IWL_BA_ESCAPE_TIMER_MAX 1024
#घोषणा IWL_BA_ESCAPE_TIMER_MIN 0

#घोषणा IWL_BA_ENABLE_BEACON_ABORT_DEFAULT 1

#घोषणा IWL_BF_CMD_CONFIG(mode)					     \
	.bf_energy_delta = cpu_to_le32(IWL_BF_ENERGY_DELTA ## mode),	      \
	.bf_roaming_energy_delta =					      \
		cpu_to_le32(IWL_BF_ROAMING_ENERGY_DELTA ## mode),	      \
	.bf_roaming_state = cpu_to_le32(IWL_BF_ROAMING_STATE ## mode),	      \
	.bf_temp_threshold = cpu_to_le32(IWL_BF_TEMP_THRESHOLD ## mode),      \
	.bf_temp_fast_filter = cpu_to_le32(IWL_BF_TEMP_FAST_FILTER ## mode),  \
	.bf_temp_slow_filter = cpu_to_le32(IWL_BF_TEMP_SLOW_FILTER ## mode),  \
	.bf_debug_flag = cpu_to_le32(IWL_BF_DEBUG_FLAG ## mode),	      \
	.bf_escape_समयr = cpu_to_le32(IWL_BF_ESCAPE_TIMER ## mode),	      \
	.ba_escape_समयr = cpu_to_le32(IWL_BA_ESCAPE_TIMER ## mode)

#घोषणा IWL_BF_CMD_CONFIG_DEFAULTS IWL_BF_CMD_CONFIG(_DEFAULT)
#घोषणा IWL_BF_CMD_CONFIG_D0I3 IWL_BF_CMD_CONFIG(_D0I3)
#पूर्ण_अगर /* __iwl_fw_api_घातer_h__ */
