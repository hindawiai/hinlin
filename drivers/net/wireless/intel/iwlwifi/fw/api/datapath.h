<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_datapath_h__
#घोषणा __iwl_fw_api_datapath_h__

/**
 * क्रमागत iwl_data_path_subcmd_ids - data path group commands
 */
क्रमागत iwl_data_path_subcmd_ids अणु
	/**
	 * @DQA_ENABLE_CMD: &काष्ठा iwl_dqa_enable_cmd
	 */
	DQA_ENABLE_CMD = 0x0,

	/**
	 * @UPDATE_MU_GROUPS_CMD: &काष्ठा iwl_mu_group_mgmt_cmd
	 */
	UPDATE_MU_GROUPS_CMD = 0x1,

	/**
	 * @TRIGGER_RX_QUEUES_NOTIF_CMD: &काष्ठा iwl_rxq_sync_cmd
	 */
	TRIGGER_RX_QUEUES_NOTIF_CMD = 0x2,

	/**
	 * @STA_HE_CTXT_CMD: &काष्ठा iwl_he_sta_context_cmd
	 */
	STA_HE_CTXT_CMD = 0x7,

	/**
	 * @RFH_QUEUE_CONFIG_CMD: &काष्ठा iwl_rfh_queue_config
	 */
	RFH_QUEUE_CONFIG_CMD = 0xD,

	/**
	 * @TLC_MNG_CONFIG_CMD: &काष्ठा iwl_tlc_config_cmd
	 */
	TLC_MNG_CONFIG_CMD = 0xF,

	/**
	 * @HE_AIR_SNIFFER_CONFIG_CMD: &काष्ठा iwl_he_monitor_cmd
	 */
	HE_AIR_SNIFFER_CONFIG_CMD = 0x13,

	/**
	 * @CHEST_COLLECTOR_FILTER_CONFIG_CMD: Configure the CSI
	 *	matrix collection, uses &काष्ठा iwl_channel_estimation_cfg
	 */
	CHEST_COLLECTOR_FILTER_CONFIG_CMD = 0x14,

	/**
	 * @MONITOR_NOTIF: Datapath monitoring notअगरication, using
	 *	&काष्ठा iwl_datapath_monitor_notअगर
	 */
	MONITOR_NOTIF = 0xF4,

	/**
	 * @RX_NO_DATA_NOTIF: &काष्ठा iwl_rx_no_data
	 */
	RX_NO_DATA_NOTIF = 0xF5,

	/**
	 * @TLC_MNG_UPDATE_NOTIF: &काष्ठा iwl_tlc_update_notअगर
	 */
	TLC_MNG_UPDATE_NOTIF = 0xF7,

	/**
	 * @STA_PM_NOTIF: &काष्ठा iwl_mvm_pm_state_notअगरication
	 */
	STA_PM_NOTIF = 0xFD,

	/**
	 * @MU_GROUP_MGMT_NOTIF: &काष्ठा iwl_mu_group_mgmt_notअगर
	 */
	MU_GROUP_MGMT_NOTIF = 0xFE,

	/**
	 * @RX_QUEUES_NOTIFICATION: &काष्ठा iwl_rxq_sync_notअगरication
	 */
	RX_QUEUES_NOTIFICATION = 0xFF,
पूर्ण;

/**
 * काष्ठा iwl_mu_group_mgmt_cmd - VHT MU-MIMO group configuration
 *
 * @reserved: reserved
 * @membership_status: a biपंचांगap of MU groups
 * @user_position:the position of station in a group. If the station is in the
 *	group then bits (group * 2) is the position -1
 */
काष्ठा iwl_mu_group_mgmt_cmd अणु
	__le32 reserved;
	__le32 membership_status[2];
	__le32 user_position[4];
पूर्ण __packed; /* MU_GROUP_ID_MNG_TABLE_API_S_VER_1 */

/**
 * काष्ठा iwl_mu_group_mgmt_notअगर - VHT MU-MIMO group id notअगरication
 *
 * @membership_status: a biपंचांगap of MU groups
 * @user_position: the position of station in a group. If the station is in the
 *	group then bits (group * 2) is the position -1
 */
काष्ठा iwl_mu_group_mgmt_notअगर अणु
	__le32 membership_status[2];
	__le32 user_position[4];
पूर्ण __packed; /* MU_GROUP_MNG_NTFY_API_S_VER_1 */

क्रमागत iwl_channel_estimation_flags अणु
	IWL_CHANNEL_ESTIMATION_ENABLE	= BIT(0),
	IWL_CHANNEL_ESTIMATION_TIMER	= BIT(1),
	IWL_CHANNEL_ESTIMATION_COUNTER	= BIT(2),
पूर्ण;

/**
 * काष्ठा iwl_channel_estimation_cfg - channel estimation reporting config
 */
काष्ठा iwl_channel_estimation_cfg अणु
	/**
	 * @flags: flags, see &क्रमागत iwl_channel_estimation_flags
	 */
	__le32 flags;
	/**
	 * @समयr: अगर enabled via flags, स्वतःmatically disable after this many
	 *	microseconds
	 */
	__le32 समयr;
	/**
	 * @count: अगर enabled via flags, स्वतःmatically disable after this many
	 *	frames with channel estimation matrix were captured
	 */
	__le32 count;
	/**
	 * @rate_n_flags_mask: only try to record the channel estimation matrix
	 *	अगर the rate_n_flags value क्रम the received frame (let's call
	 *	that rx_rnf) matches the mask/value given here like this:
	 *	(rx_rnf & rate_n_flags_mask) == rate_n_flags_val.
	 */
	__le32 rate_n_flags_mask;
	/**
	 * @rate_n_flags_val: see @rate_n_flags_mask
	 */
	__le32 rate_n_flags_val;
	/**
	 * @reserved: reserved (क्रम alignment)
	 */
	__le32 reserved;
	/**
	 * @frame_types: biपंचांगap of frame types to capture, the received frame's
	 *	subtype|type takes 6 bits in the frame and the corresponding bit
	 *	in this field must be set to 1 to capture channel estimation क्रम
	 *	that frame type. Set to all-ones to enable capturing क्रम all
	 *	frame types.
	 */
	__le64 frame_types;
पूर्ण __packed; /* CHEST_COLLECTOR_FILTER_CMD_API_S_VER_1 */

क्रमागत iwl_datapath_monitor_notअगर_type अणु
	IWL_DP_MON_NOTIF_TYPE_EXT_CCA,
पूर्ण;

काष्ठा iwl_datapath_monitor_notअगर अणु
	__le32 type;
	u8 mac_id;
	u8 reserved[3];
पूर्ण __packed; /* MONITOR_NTF_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_datapath_h__ */
