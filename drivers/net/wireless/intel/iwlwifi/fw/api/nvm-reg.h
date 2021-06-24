<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2012-2014, 2018-2021 Intel Corporation
 * Copyright (C) 2013-2015 Intel Mobile Communications GmbH
 * Copyright (C) 2016-2017 Intel Deutschland GmbH
 */
#अगर_अघोषित __iwl_fw_api_nvm_reg_h__
#घोषणा __iwl_fw_api_nvm_reg_h__

/**
 * क्रमागत iwl_regulatory_and_nvm_subcmd_ids - regulatory/NVM commands
 */
क्रमागत iwl_regulatory_and_nvm_subcmd_ids अणु
	/**
	 * @NVM_ACCESS_COMPLETE: &काष्ठा iwl_nvm_access_complete_cmd
	 */
	NVM_ACCESS_COMPLETE = 0x0,

	/**
	 * @LARI_CONFIG_CHANGE: &काष्ठा iwl_lari_config_change_cmd
	 */
	LARI_CONFIG_CHANGE = 0x1,

	/**
	 * @NVM_GET_INFO:
	 * Command is &काष्ठा iwl_nvm_get_info,
	 * response is &काष्ठा iwl_nvm_get_info_rsp
	 */
	NVM_GET_INFO = 0x2,

	/**
	 * @TAS_CONFIG: &काष्ठा iwl_tas_config_cmd
	 */
	TAS_CONFIG = 0x3,

	/**
	 * @PNVM_INIT_COMPLETE_NTFY: &काष्ठा iwl_pnvm_init_complete_ntfy
	 */
	PNVM_INIT_COMPLETE_NTFY = 0xFE,
पूर्ण;

/**
 * क्रमागत iwl_nvm_access_op - NVM access opcode
 * @IWL_NVM_READ: पढ़ो NVM
 * @IWL_NVM_WRITE: ग_लिखो NVM
 */
क्रमागत iwl_nvm_access_op अणु
	IWL_NVM_READ	= 0,
	IWL_NVM_WRITE	= 1,
पूर्ण;

/**
 * क्रमागत iwl_nvm_access_target - target of the NVM_ACCESS_CMD
 * @NVM_ACCESS_TARGET_CACHE: access the cache
 * @NVM_ACCESS_TARGET_OTP: access the OTP
 * @NVM_ACCESS_TARGET_EEPROM: access the EEPROM
 */
क्रमागत iwl_nvm_access_target अणु
	NVM_ACCESS_TARGET_CACHE = 0,
	NVM_ACCESS_TARGET_OTP = 1,
	NVM_ACCESS_TARGET_EEPROM = 2,
पूर्ण;

/**
 * क्रमागत iwl_nvm_section_type - section types क्रम NVM_ACCESS_CMD
 * @NVM_SECTION_TYPE_SW: software section
 * @NVM_SECTION_TYPE_REGULATORY: regulatory section
 * @NVM_SECTION_TYPE_CALIBRATION: calibration section
 * @NVM_SECTION_TYPE_PRODUCTION: production section
 * @NVM_SECTION_TYPE_REGULATORY_SDP: regulatory section used by 3168 series
 * @NVM_SECTION_TYPE_MAC_OVERRIDE: MAC override section
 * @NVM_SECTION_TYPE_PHY_SKU: PHY SKU section
 * @NVM_MAX_NUM_SECTIONS: number of sections
 */
क्रमागत iwl_nvm_section_type अणु
	NVM_SECTION_TYPE_SW = 1,
	NVM_SECTION_TYPE_REGULATORY = 3,
	NVM_SECTION_TYPE_CALIBRATION = 4,
	NVM_SECTION_TYPE_PRODUCTION = 5,
	NVM_SECTION_TYPE_REGULATORY_SDP = 8,
	NVM_SECTION_TYPE_MAC_OVERRIDE = 11,
	NVM_SECTION_TYPE_PHY_SKU = 12,
	NVM_MAX_NUM_SECTIONS = 13,
पूर्ण;

/**
 * काष्ठा iwl_nvm_access_cmd - Request the device to send an NVM section
 * @op_code: &क्रमागत iwl_nvm_access_op
 * @target: &क्रमागत iwl_nvm_access_target
 * @type: &क्रमागत iwl_nvm_section_type
 * @offset: offset in bytes पूर्णांकo the section
 * @length: in bytes, to पढ़ो/ग_लिखो
 * @data: अगर ग_लिखो operation, the data to ग_लिखो. On पढ़ो its empty
 */
काष्ठा iwl_nvm_access_cmd अणु
	u8 op_code;
	u8 target;
	__le16 type;
	__le16 offset;
	__le16 length;
	u8 data[];
पूर्ण __packed; /* NVM_ACCESS_CMD_API_S_VER_2 */

/**
 * काष्ठा iwl_nvm_access_resp_ver2 - response to NVM_ACCESS_CMD
 * @offset: offset in bytes पूर्णांकo the section
 * @length: in bytes, either how much was written or पढ़ो
 * @type: NVM_SECTION_TYPE_*
 * @status: 0 क्रम success, fail otherwise
 * @data: अगर पढ़ो operation, the data वापसed. Empty on ग_लिखो.
 */
काष्ठा iwl_nvm_access_resp अणु
	__le16 offset;
	__le16 length;
	__le16 type;
	__le16 status;
	u8 data[];
पूर्ण __packed; /* NVM_ACCESS_CMD_RESP_API_S_VER_2 */

/*
 * काष्ठा iwl_nvm_get_info - request to get NVM data
 */
काष्ठा iwl_nvm_get_info अणु
	__le32 reserved;
पूर्ण __packed; /* REGULATORY_NVM_GET_INFO_CMD_API_S_VER_1 */

/**
 * क्रमागत iwl_nvm_info_general_flags - flags in NVM_GET_INFO resp
 * @NVM_GENERAL_FLAGS_EMPTY_OTP: 1 अगर OTP is empty
 */
क्रमागत iwl_nvm_info_general_flags अणु
	NVM_GENERAL_FLAGS_EMPTY_OTP	= BIT(0),
पूर्ण;

/**
 * काष्ठा iwl_nvm_get_info_general - general NVM data
 * @flags: bit 0: 1 - empty, 0 - non-empty
 * @nvm_version: nvm version
 * @board_type: board type
 * @n_hw_addrs: number of reserved MAC addresses
 */
काष्ठा iwl_nvm_get_info_general अणु
	__le32 flags;
	__le16 nvm_version;
	u8 board_type;
	u8 n_hw_addrs;
पूर्ण __packed; /* REGULATORY_NVM_GET_INFO_GENERAL_S_VER_2 */

/**
 * क्रमागत iwl_nvm_mac_sku_flags - flags in &iwl_nvm_get_info_sku
 * @NVM_MAC_SKU_FLAGS_BAND_2_4_ENABLED: true अगर 2.4 band enabled
 * @NVM_MAC_SKU_FLAGS_BAND_5_2_ENABLED: true अगर 5.2 band enabled
 * @NVM_MAC_SKU_FLAGS_802_11N_ENABLED: true अगर 11n enabled
 * @NVM_MAC_SKU_FLAGS_802_11AC_ENABLED: true अगर 11ac enabled
 * @NVM_MAC_SKU_FLAGS_MIMO_DISABLED: true अगर MIMO disabled
 * @NVM_MAC_SKU_FLAGS_WAPI_ENABLED: true अगर WAPI enabled
 * @NVM_MAC_SKU_FLAGS_REG_CHECK_ENABLED: true अगर regulatory checker enabled
 * @NVM_MAC_SKU_FLAGS_API_LOCK_ENABLED: true अगर API lock enabled
 */
क्रमागत iwl_nvm_mac_sku_flags अणु
	NVM_MAC_SKU_FLAGS_BAND_2_4_ENABLED	= BIT(0),
	NVM_MAC_SKU_FLAGS_BAND_5_2_ENABLED	= BIT(1),
	NVM_MAC_SKU_FLAGS_802_11N_ENABLED	= BIT(2),
	NVM_MAC_SKU_FLAGS_802_11AC_ENABLED	= BIT(3),
	/**
	 * @NVM_MAC_SKU_FLAGS_802_11AX_ENABLED: true अगर 11ax enabled
	 */
	NVM_MAC_SKU_FLAGS_802_11AX_ENABLED	= BIT(4),
	NVM_MAC_SKU_FLAGS_MIMO_DISABLED		= BIT(5),
	NVM_MAC_SKU_FLAGS_WAPI_ENABLED		= BIT(8),
	NVM_MAC_SKU_FLAGS_REG_CHECK_ENABLED	= BIT(14),
	NVM_MAC_SKU_FLAGS_API_LOCK_ENABLED	= BIT(15),
पूर्ण;

/**
 * काष्ठा iwl_nvm_get_info_sku - mac inक्रमmation
 * @mac_sku_flags: flags क्रम SKU, see &क्रमागत iwl_nvm_mac_sku_flags
 */
काष्ठा iwl_nvm_get_info_sku अणु
	__le32 mac_sku_flags;
पूर्ण __packed; /* REGULATORY_NVM_GET_INFO_MAC_SKU_SECTION_S_VER_2 */

/**
 * काष्ठा iwl_nvm_get_info_phy - phy inक्रमmation
 * @tx_chains: BIT 0 chain A, BIT 1 chain B
 * @rx_chains: BIT 0 chain A, BIT 1 chain B
 */
काष्ठा iwl_nvm_get_info_phy अणु
	__le32 tx_chains;
	__le32 rx_chains;
पूर्ण __packed; /* REGULATORY_NVM_GET_INFO_PHY_SKU_SECTION_S_VER_1 */

#घोषणा IWL_NUM_CHANNELS_V1	51
#घोषणा IWL_NUM_CHANNELS	110

/**
 * काष्ठा iwl_nvm_get_info_regulatory - regulatory inक्रमmation
 * @lar_enabled: is LAR enabled
 * @channel_profile: regulatory data of this channel
 * @reserved: reserved
 */
काष्ठा iwl_nvm_get_info_regulatory_v1 अणु
	__le32 lar_enabled;
	__le16 channel_profile[IWL_NUM_CHANNELS_V1];
	__le16 reserved;
पूर्ण __packed; /* REGULATORY_NVM_GET_INFO_REGULATORY_S_VER_1 */

/**
 * काष्ठा iwl_nvm_get_info_regulatory - regulatory inक्रमmation
 * @lar_enabled: is LAR enabled
 * @n_channels: number of valid channels in the array
 * @channel_profile: regulatory data of this channel
 */
काष्ठा iwl_nvm_get_info_regulatory अणु
	__le32 lar_enabled;
	__le32 n_channels;
	__le32 channel_profile[IWL_NUM_CHANNELS];
पूर्ण __packed; /* REGULATORY_NVM_GET_INFO_REGULATORY_S_VER_2 */

/**
 * काष्ठा iwl_nvm_get_info_rsp_v3 - response to get NVM data
 * @general: general NVM data
 * @mac_sku: data relating to MAC sku
 * @phy_sku: data relating to PHY sku
 * @regulatory: regulatory data
 */
काष्ठा iwl_nvm_get_info_rsp_v3 अणु
	काष्ठा iwl_nvm_get_info_general general;
	काष्ठा iwl_nvm_get_info_sku mac_sku;
	काष्ठा iwl_nvm_get_info_phy phy_sku;
	काष्ठा iwl_nvm_get_info_regulatory_v1 regulatory;
पूर्ण __packed; /* REGULATORY_NVM_GET_INFO_RSP_API_S_VER_3 */

/**
 * काष्ठा iwl_nvm_get_info_rsp - response to get NVM data
 * @general: general NVM data
 * @mac_sku: data relating to MAC sku
 * @phy_sku: data relating to PHY sku
 * @regulatory: regulatory data
 */
काष्ठा iwl_nvm_get_info_rsp अणु
	काष्ठा iwl_nvm_get_info_general general;
	काष्ठा iwl_nvm_get_info_sku mac_sku;
	काष्ठा iwl_nvm_get_info_phy phy_sku;
	काष्ठा iwl_nvm_get_info_regulatory regulatory;
पूर्ण __packed; /* REGULATORY_NVM_GET_INFO_RSP_API_S_VER_4 */

/**
 * काष्ठा iwl_nvm_access_complete_cmd - NVM_ACCESS commands are completed
 * @reserved: reserved
 */
काष्ठा iwl_nvm_access_complete_cmd अणु
	__le32 reserved;
पूर्ण __packed; /* NVM_ACCESS_COMPLETE_CMD_API_S_VER_1 */

/**
 * काष्ठा iwl_mcc_update_cmd - Request the device to update geographic
 * regulatory profile according to the given MCC (Mobile Country Code).
 * The MCC is two letter-code, ascii upper हाल[A-Z] or '00' क्रम world करोमुख्य.
 * 'ZZ' MCC will be used to चयन to NVM शेष profile; in this हाल, the
 * MCC in the cmd response will be the relevant MCC in the NVM.
 * @mcc: given mobile country code
 * @source_id: the source from where we got the MCC, see iwl_mcc_source
 * @reserved: reserved क्रम alignment
 * @key: पूर्णांकegrity key क्रम MCC API OEM testing
 * @reserved2: reserved
 */
काष्ठा iwl_mcc_update_cmd अणु
	__le16 mcc;
	u8 source_id;
	u8 reserved;
	__le32 key;
	u8 reserved2[20];
पूर्ण __packed; /* LAR_UPDATE_MCC_CMD_API_S_VER_2 */

/**
 * क्रमागत iwl_geo_inक्रमmation - geographic inक्रमmation.
 * @GEO_NO_INFO: no special info क्रम this geo profile.
 * @GEO_WMM_ETSI_5GHZ_INFO: this geo profile limits the WMM params
 *	क्रम the 5 GHz band.
 */
क्रमागत iwl_geo_inक्रमmation अणु
	GEO_NO_INFO =			0,
	GEO_WMM_ETSI_5GHZ_INFO =	BIT(0),
पूर्ण;

/**
 * काष्ठा iwl_mcc_update_resp_v3 - response to MCC_UPDATE_CMD.
 * Contains the new channel control profile map, अगर changed, and the new MCC
 * (mobile country code).
 * The new MCC may be dअगरferent than what was requested in MCC_UPDATE_CMD.
 * @status: see &क्रमागत iwl_mcc_update_status
 * @mcc: the new applied MCC
 * @cap: capabilities क्रम all channels which matches the MCC
 * @source_id: the MCC source, see iwl_mcc_source
 * @समय: समय elapsed from the MCC test start (in units of 30 seconds)
 * @geo_info: geographic specअगरic profile inक्रमmation
 *	see &क्रमागत iwl_geo_inक्रमmation.
 * @n_channels: number of channels in @channels_data.
 * @channels: channel control data map, DWORD क्रम each channel. Only the first
 *	16bits are used.
 */
काष्ठा iwl_mcc_update_resp_v3 अणु
	__le32 status;
	__le16 mcc;
	u8 cap;
	u8 source_id;
	__le16 समय;
	__le16 geo_info;
	__le32 n_channels;
	__le32 channels[];
पूर्ण __packed; /* LAR_UPDATE_MCC_CMD_RESP_S_VER_3 */

/**
 * काष्ठा iwl_mcc_update_resp - response to MCC_UPDATE_CMD.
 * Contains the new channel control profile map, अगर changed, and the new MCC
 * (mobile country code).
 * The new MCC may be dअगरferent than what was requested in MCC_UPDATE_CMD.
 * @status: see &क्रमागत iwl_mcc_update_status
 * @mcc: the new applied MCC
 * @cap: capabilities क्रम all channels which matches the MCC
 * @समय: समय elapsed from the MCC test start (in units of 30 seconds)
 * @geo_info: geographic specअगरic profile inक्रमmation
 *	see &क्रमागत iwl_geo_inक्रमmation.
 * @source_id: the MCC source, see iwl_mcc_source
 * @reserved: क्रम four bytes alignment.
 * @n_channels: number of channels in @channels_data.
 * @channels: channel control data map, DWORD क्रम each channel. Only the first
 *	16bits are used.
 */
काष्ठा iwl_mcc_update_resp अणु
	__le32 status;
	__le16 mcc;
	__le16 cap;
	__le16 समय;
	__le16 geo_info;
	u8 source_id;
	u8 reserved[3];
	__le32 n_channels;
	__le32 channels[];
पूर्ण __packed; /* LAR_UPDATE_MCC_CMD_RESP_S_VER_4 */

/**
 * काष्ठा iwl_mcc_chub_notअगर - chub notअगरies of mcc change
 * (MCC_CHUB_UPDATE_CMD = 0xc9)
 * The Chub (Communication Hub, CommsHUB) is a HW component that connects to
 * the cellular and connectivity cores that माला_लो updates of the mcc, and
 * notअगरies the ucode directly of any mcc change.
 * The ucode requests the driver to request the device to update geographic
 * regulatory  profile according to the given MCC (Mobile Country Code).
 * The MCC is two letter-code, ascii upper हाल[A-Z] or '00' क्रम world करोमुख्य.
 * 'ZZ' MCC will be used to चयन to NVM शेष profile; in this हाल, the
 * MCC in the cmd response will be the relevant MCC in the NVM.
 * @mcc: given mobile country code
 * @source_id: identity of the change originator, see iwl_mcc_source
 * @reserved1: reserved क्रम alignment
 */
काष्ठा iwl_mcc_chub_notअगर अणु
	__le16 mcc;
	u8 source_id;
	u8 reserved1;
पूर्ण __packed; /* LAR_MCC_NOTIFY_S */

क्रमागत iwl_mcc_update_status अणु
	MCC_RESP_NEW_CHAN_PROखाता,
	MCC_RESP_SAME_CHAN_PROखाता,
	MCC_RESP_INVALID,
	MCC_RESP_NVM_DISABLED,
	MCC_RESP_ILLEGAL,
	MCC_RESP_LOW_PRIORITY,
	MCC_RESP_TEST_MODE_ACTIVE,
	MCC_RESP_TEST_MODE_NOT_ACTIVE,
	MCC_RESP_TEST_MODE_DENIAL_OF_SERVICE,
पूर्ण;

क्रमागत iwl_mcc_source अणु
	MCC_SOURCE_OLD_FW = 0,
	MCC_SOURCE_ME = 1,
	MCC_SOURCE_BIOS = 2,
	MCC_SOURCE_3G_LTE_HOST = 3,
	MCC_SOURCE_3G_LTE_DEVICE = 4,
	MCC_SOURCE_WIFI = 5,
	MCC_SOURCE_RESERVED = 6,
	MCC_SOURCE_DEFAULT = 7,
	MCC_SOURCE_UNINITIALIZED = 8,
	MCC_SOURCE_MCC_API = 9,
	MCC_SOURCE_GET_CURRENT = 0x10,
	MCC_SOURCE_GETTING_MCC_TEST_MODE = 0x11,
पूर्ण;

#घोषणा IWL_TAS_BLACK_LIST_MAX 16
/**
 * काष्ठा iwl_tas_config_cmd - configures the TAS
 * @block_list_size: size of relevant field in block_list_array
 * @block_list_array: block list countries (without TAS)
 */
काष्ठा iwl_tas_config_cmd अणु
	__le32 block_list_size;
	__le32 block_list_array[IWL_TAS_BLACK_LIST_MAX];
पूर्ण __packed; /* TAS_CONFIG_CMD_API_S_VER_2 */

/**
 * क्रमागत iwl_lari_configs - bit masks क्रम the various LARI config operations
 * @LARI_CONFIG_DISABLE_11AC_UKRAINE_MSK: disable 11ac in ukraine
 * @LARI_CONFIG_CHANGE_ETSI_TO_PASSIVE_MSK: ETSI 5.8GHz SRD passive scan
 * @LARI_CONFIG_CHANGE_ETSI_TO_DISABLED_MSK: ETSI 5.8GHz SRD disabled
 * @LARI_CONFIG_ENABLE_5G2_IN_INDONESIA_MSK: enable 5.15/5.35GHz bands in
 * 	Inकरोnesia
 */
क्रमागत iwl_lari_config_masks अणु
	LARI_CONFIG_DISABLE_11AC_UKRAINE_MSK		= BIT(0),
	LARI_CONFIG_CHANGE_ETSI_TO_PASSIVE_MSK		= BIT(1),
	LARI_CONFIG_CHANGE_ETSI_TO_DISABLED_MSK		= BIT(2),
	LARI_CONFIG_ENABLE_5G2_IN_INDONESIA_MSK		= BIT(3),
पूर्ण;

#घोषणा IWL_11AX_UKRAINE_MASK 3
#घोषणा IWL_11AX_UKRAINE_SHIFT 8

/**
 * काष्ठा iwl_lari_config_change_cmd_v1 - change LARI configuration
 * @config_biपंचांगap: bit map of the config commands. each bit will trigger a
 * dअगरferent predefined FW config operation
 */
काष्ठा iwl_lari_config_change_cmd_v1 अणु
	__le32 config_biपंचांगap;
पूर्ण __packed; /* LARI_CHANGE_CONF_CMD_S_VER_1 */

/**
 * काष्ठा iwl_lari_config_change_cmd_v2 - change LARI configuration
 * @config_biपंचांगap: bit map of the config commands. each bit will trigger a
 * dअगरferent predefined FW config operation
 * @oem_uhb_allow_biपंचांगap: biपंचांगap of UHB enabled MCC sets
 */
काष्ठा iwl_lari_config_change_cmd_v2 अणु
	__le32 config_biपंचांगap;
	__le32 oem_uhb_allow_biपंचांगap;
पूर्ण __packed; /* LARI_CHANGE_CONF_CMD_S_VER_2 */

/**
 * काष्ठा iwl_lari_config_change_cmd_v3 - change LARI configuration
 * @config_biपंचांगap: bit map of the config commands. each bit will trigger a
 * dअगरferent predefined FW config operation
 * @oem_uhb_allow_biपंचांगap: biपंचांगap of UHB enabled MCC sets
 * @oem_11ax_allow_biपंचांगap: biपंचांगap of 11ax allowed MCCs.
 * For each supported country, a pair of regulatory override bit and 11ax mode exist
 * in the bit field.
 */
काष्ठा iwl_lari_config_change_cmd_v3 अणु
	__le32 config_biपंचांगap;
	__le32 oem_uhb_allow_biपंचांगap;
	__le32 oem_11ax_allow_biपंचांगap;
पूर्ण __packed; /* LARI_CHANGE_CONF_CMD_S_VER_3 */

/**
 * काष्ठा iwl_pnvm_init_complete_ntfy - PNVM initialization complete
 * @status: PNVM image loading status
 */
काष्ठा iwl_pnvm_init_complete_ntfy अणु
	__le32 status;
पूर्ण __packed; /* PNVM_INIT_COMPLETE_NTFY_S_VER_1 */

#पूर्ण_अगर /* __iwl_fw_api_nvm_reg_h__ */
