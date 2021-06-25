<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018, 2020 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_alive_h__
#घोषणा __iwl_fw_api_alive_h__

/* alive response is_valid values */
#घोषणा ALIVE_RESP_UCODE_OK	BIT(0)
#घोषणा ALIVE_RESP_RFKILL	BIT(1)

/* alive response ver_type values */
क्रमागत अणु
	FW_TYPE_HW = 0,
	FW_TYPE_PROT = 1,
	FW_TYPE_AP = 2,
	FW_TYPE_WOWLAN = 3,
	FW_TYPE_TIMING = 4,
	FW_TYPE_WIPAN = 5
पूर्ण;

/* alive response ver_subtype values */
क्रमागत अणु
	FW_SUBTYPE_FULL_FEATURE = 0,
	FW_SUBTYPE_BOOTSRAP = 1, /* Not valid */
	FW_SUBTYPE_REDUCED = 2,
	FW_SUBTYPE_ALIVE_ONLY = 3,
	FW_SUBTYPE_WOWLAN = 4,
	FW_SUBTYPE_AP_SUBTYPE = 5,
	FW_SUBTYPE_WIPAN = 6,
	FW_SUBTYPE_INITIALIZE = 9
पूर्ण;

#घोषणा IWL_ALIVE_STATUS_ERR 0xDEAD
#घोषणा IWL_ALIVE_STATUS_OK 0xCAFE

#घोषणा IWL_ALIVE_FLG_RFKILL	BIT(0)

काष्ठा iwl_lmac_debug_addrs अणु
	__le32 error_event_table_ptr;	/* SRAM address क्रम error log */
	__le32 log_event_table_ptr;	/* SRAM address क्रम LMAC event log */
	__le32 cpu_रेजिस्टर_ptr;
	__le32 dbgm_config_ptr;
	__le32 alive_counter_ptr;
	__le32 scd_base_ptr;		/* SRAM address क्रम SCD */
	__le32 st_fwrd_addr;		/* poपूर्णांकer to Store and क्रमward */
	__le32 st_fwrd_size;
पूर्ण __packed; /* UCODE_DEBUG_ADDRS_API_S_VER_2 */

काष्ठा iwl_lmac_alive अणु
	__le32 ucode_major;
	__le32 ucode_minor;
	u8 ver_subtype;
	u8 ver_type;
	u8 mac;
	u8 opt;
	__le32 बारtamp;
	काष्ठा iwl_lmac_debug_addrs dbg_ptrs;
पूर्ण __packed; /* UCODE_ALIVE_NTFY_API_S_VER_3 */

काष्ठा iwl_umac_debug_addrs अणु
	__le32 error_info_addr;		/* SRAM address क्रम UMAC error log */
	__le32 dbg_prपूर्णांक_buff_addr;
पूर्ण __packed; /* UMAC_DEBUG_ADDRS_API_S_VER_1 */

काष्ठा iwl_umac_alive अणु
	__le32 umac_major;		/* UMAC version: major */
	__le32 umac_minor;		/* UMAC version: minor */
	काष्ठा iwl_umac_debug_addrs dbg_ptrs;
पूर्ण __packed; /* UMAC_ALIVE_DATA_API_S_VER_2 */

काष्ठा iwl_sku_id अणु
	__le32 data[3];
पूर्ण __packed; /* SKU_ID_API_S_VER_1 */

काष्ठा iwl_alive_ntf_v3 अणु
	__le16 status;
	__le16 flags;
	काष्ठा iwl_lmac_alive lmac_data;
	काष्ठा iwl_umac_alive umac_data;
पूर्ण __packed; /* UCODE_ALIVE_NTFY_API_S_VER_3 */

काष्ठा iwl_alive_ntf_v4 अणु
	__le16 status;
	__le16 flags;
	काष्ठा iwl_lmac_alive lmac_data[2];
	काष्ठा iwl_umac_alive umac_data;
पूर्ण __packed; /* UCODE_ALIVE_NTFY_API_S_VER_4 */

काष्ठा iwl_alive_ntf_v5 अणु
	__le16 status;
	__le16 flags;
	काष्ठा iwl_lmac_alive lmac_data[2];
	काष्ठा iwl_umac_alive umac_data;
	काष्ठा iwl_sku_id sku_id;
पूर्ण __packed; /* UCODE_ALIVE_NTFY_API_S_VER_5 */

/**
 * क्रमागत iwl_extended_cfg_flag - commands driver may send beक्रमe
 *	finishing init flow
 * @IWL_INIT_DEBUG_CFG: driver is going to send debug config command
 * @IWL_INIT_NVM: driver is going to send NVM_ACCESS commands
 * @IWL_INIT_PHY: driver is going to send PHY_DB commands
 */
क्रमागत iwl_extended_cfg_flags अणु
	IWL_INIT_DEBUG_CFG,
	IWL_INIT_NVM,
	IWL_INIT_PHY,
पूर्ण;

/**
 * काष्ठा iwl_extended_cfg_cmd - mark what commands ucode should रुको क्रम
 * beक्रमe finishing init flows
 * @init_flags: values from iwl_extended_cfg_flags
 */
काष्ठा iwl_init_extended_cfg_cmd अणु
	__le32 init_flags;
पूर्ण __packed; /* INIT_EXTENDED_CFG_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_radio_version_notअगर - inक्रमmation on the radio version
 * ( RADIO_VERSION_NOTIFICATION = 0x68 )
 * @radio_flavor: radio flavor
 * @radio_step: radio version step
 * @radio_dash: radio version dash
 */
काष्ठा iwl_radio_version_notअगर अणु
	__le32 radio_flavor;
	__le32 radio_step;
	__le32 radio_dash;
पूर्ण __packed; /* RADIO_VERSION_NOTOFICATION_S_VER_1 */

क्रमागत iwl_card_state_flags अणु
	CARD_ENABLED		= 0x00,
	HW_CARD_DISABLED	= 0x01,
	SW_CARD_DISABLED	= 0x02,
	CT_KILL_CARD_DISABLED	= 0x04,
	HALT_CARD_DISABLED	= 0x08,
	CARD_DISABLED_MSK	= 0x0f,
	CARD_IS_RX_ON		= 0x10,
पूर्ण;

/**
 * काष्ठा iwl_radio_version_notअगर - inक्रमmation on the card state
 * ( CARD_STATE_NOTIFICATION = 0xa1 )
 * @flags: &क्रमागत iwl_card_state_flags
 */
काष्ठा iwl_card_state_notअगर अणु
	__le32 flags;
पूर्ण __packed; /* CARD_STATE_NTFY_API_S_VER_1 */

/**
 * क्रमागत iwl_error_recovery_flags - flags क्रम error recovery cmd
 * @ERROR_RECOVERY_UPDATE_DB: update db from blob sent
 * @ERROR_RECOVERY_END_OF_RECOVERY: end of recovery
 */
क्रमागत iwl_error_recovery_flags अणु
	ERROR_RECOVERY_UPDATE_DB = BIT(0),
	ERROR_RECOVERY_END_OF_RECOVERY = BIT(1),
पूर्ण;

/**
 * काष्ठा iwl_fw_error_recovery_cmd - recovery cmd sent upon निश्चित
 * @flags: &क्रमागत iwl_error_recovery_flags
 * @buf_size: db buffer size in bytes
 */
काष्ठा iwl_fw_error_recovery_cmd अणु
	__le32 flags;
	__le32 buf_size;
पूर्ण __packed; /* ERROR_RECOVERY_CMD_HDR_API_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_alive_h__ */
