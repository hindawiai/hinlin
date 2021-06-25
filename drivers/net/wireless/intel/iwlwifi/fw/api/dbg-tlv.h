<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause */
/*
 * Copyright (C) 2018-2020 Intel Corporation
 */
#अगर_अघोषित __iwl_fw_dbg_tlv_h__
#घोषणा __iwl_fw_dbg_tlv_h__

#समावेश <linux/bitops.h>

#घोषणा IWL_FW_INI_MAX_REGION_ID		64
#घोषणा IWL_FW_INI_MAX_NAME			32
#घोषणा IWL_FW_INI_MAX_CFG_NAME			64
#घोषणा IWL_FW_INI_DOMAIN_ALWAYS_ON		0

/**
 * काष्ठा iwl_fw_ini_hcmd
 *
 * @id: the debug configuration command type क्रम instance: 0xf6 / 0xf5 / DHC
 * @group: the desired cmd group
 * @reserved: to align to FW काष्ठा
 * @data: all of the relevant command data to be sent
 */
काष्ठा iwl_fw_ini_hcmd अणु
	u8 id;
	u8 group;
	__le16 reserved;
	u8 data[0];
पूर्ण __packed; /* FW_DEBUG_TLV_HCMD_DATA_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_header - Common Header क्रम all ini debug TLV's काष्ठाures
 *
 * @version: TLV version
 * @करोमुख्य: करोमुख्य of the TLV. One of &क्रमागत iwl_fw_ini_dbg_करोमुख्य
 * @data: TLV data
 */
काष्ठा iwl_fw_ini_header अणु
	__le32 version;
	__le32 करोमुख्य;
	u8 data[];
पूर्ण __packed; /* FW_TLV_DEBUG_HEADER_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_region_dev_addr - Configuration to पढ़ो device addresses
 *
 * @size: size of each memory chunk
 * @offset: offset to add to the base address of each chunk
 */
काष्ठा iwl_fw_ini_region_dev_addr अणु
	__le32 size;
	__le32 offset;
पूर्ण __packed; /* FW_TLV_DEBUG_DEVICE_ADDR_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_region_fअगरos - Configuration to पढ़ो Tx/Rx fअगरos
 *
 * @fid: fअगरos ids array. Used to determine what fअगरos to collect
 * @hdr_only: अगर non zero, collect only the रेजिस्टरs
 * @offset: offset to add to the रेजिस्टरs addresses
 */
काष्ठा iwl_fw_ini_region_fअगरos अणु
	__le32 fid[2];
	__le32 hdr_only;
	__le32 offset;
पूर्ण __packed; /* FW_TLV_DEBUG_REGION_FIFOS_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_region_err_table - error table region data
 *
 * Configuration to पढ़ो Umac/Lmac error table
 *
 * @version: version of the error table
 * @base_addr: base address of the error table
 * @size: size of the error table
 * @offset: offset to add to &base_addr
 */
काष्ठा iwl_fw_ini_region_err_table अणु
	__le32 version;
	__le32 base_addr;
	__le32 size;
	__le32 offset;
पूर्ण __packed; /* FW_TLV_DEBUG_REGION_ERROR_TABLE_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_region_special_device_memory - special device memory
 *
 * Configuration to पढ़ो a special memory
 *
 * @type: type of the special memory
 * @version: version of the special memory
 * @base_addr: base address of the error table
 * @size: size of the error table
 * @offset: offset to add to &base_addr
 */
काष्ठा iwl_fw_ini_region_special_device_memory अणु
	__le16 type;
	__le16 version;
	__le32 base_addr;
	__le32 size;
	__le32 offset;
पूर्ण __packed; /* FW_TLV_DEBUG_REGION_SPECIAL_DEVICE_ADDR_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_region_पूर्णांकernal_buffer - पूर्णांकernal buffer region data
 *
 * Configuration to पढ़ो पूर्णांकernal monitor buffer
 *
 * @alloc_id: allocation id one of &क्रमागत iwl_fw_ini_allocation_id
 * @base_addr: पूर्णांकernal buffer base address
 * @size: size पूर्णांकernal buffer size
 */
काष्ठा iwl_fw_ini_region_पूर्णांकernal_buffer अणु
	__le32 alloc_id;
	__le32 base_addr;
	__le32 size;
पूर्ण __packed; /* FW_TLV_DEBUG_REGION_INTERNAL_BUFFER_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_region_tlv - region TLV
 *
 * Configures parameters क्रम region data collection
 *
 * @hdr: debug header
 * @id: region id. Max id is &IWL_FW_INI_MAX_REGION_ID
 * @type: region type. One of &क्रमागत iwl_fw_ini_region_type
 * @name: region name
 * @dev_addr: device address configuration. Used by
 *	&IWL_FW_INI_REGION_DEVICE_MEMORY, &IWL_FW_INI_REGION_PERIPHERY_MAC,
 *	&IWL_FW_INI_REGION_PERIPHERY_PHY, &IWL_FW_INI_REGION_PERIPHERY_AUX,
 *	&IWL_FW_INI_REGION_PAGING, &IWL_FW_INI_REGION_CSR,
 *	&IWL_FW_INI_REGION_DRAM_IMR and &IWL_FW_INI_REGION_PCI_IOSF_CONFIG
 * @fअगरos: fअगरos configuration. Used by &IWL_FW_INI_REGION_TXF and
 *	&IWL_FW_INI_REGION_RXF
 * @err_table: error table configuration. Used by
 *	IWL_FW_INI_REGION_LMAC_ERROR_TABLE and
 *	IWL_FW_INI_REGION_UMAC_ERROR_TABLE
 * @पूर्णांकernal_buffer: पूर्णांकernal monitor buffer configuration. Used by
 *	&IWL_FW_INI_REGION_INTERNAL_BUFFER
 * @dram_alloc_id: dram allocation id. One of &क्रमागत iwl_fw_ini_allocation_id.
 *	Used by &IWL_FW_INI_REGION_DRAM_BUFFER
 * @tlv_mask: tlv collection mask. Used by &IWL_FW_INI_REGION_TLV
 * @addrs: array of addresses attached to the end of the region tlv
 */
काष्ठा iwl_fw_ini_region_tlv अणु
	काष्ठा iwl_fw_ini_header hdr;
	__le32 id;
	__le32 type;
	u8 name[IWL_FW_INI_MAX_NAME];
	जोड़ अणु
		काष्ठा iwl_fw_ini_region_dev_addr dev_addr;
		काष्ठा iwl_fw_ini_region_fअगरos fअगरos;
		काष्ठा iwl_fw_ini_region_err_table err_table;
		काष्ठा iwl_fw_ini_region_पूर्णांकernal_buffer पूर्णांकernal_buffer;
		काष्ठा iwl_fw_ini_region_special_device_memory special_mem;
		__le32 dram_alloc_id;
		__le32 tlv_mask;
	पूर्ण; /* FW_TLV_DEBUG_REGION_CONF_PARAMS_API_U_VER_1 */
	__le32 addrs[];
पूर्ण __packed; /* FW_TLV_DEBUG_REGION_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_debug_info_tlv
 *
 * debug configuration name क्रम a specअगरic image
 *
 * @hdr: debug header
 * @image_type: image type
 * @debug_cfg_name: debug configuration name
 */
काष्ठा iwl_fw_ini_debug_info_tlv अणु
	काष्ठा iwl_fw_ini_header hdr;
	__le32 image_type;
	u8 debug_cfg_name[IWL_FW_INI_MAX_CFG_NAME];
पूर्ण __packed; /* FW_TLV_DEBUG_INFO_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_allocation_tlv - Allocates DRAM buffers
 *
 * @hdr: debug header
 * @alloc_id: allocation id. One of &क्रमागत iwl_fw_ini_allocation_id
 * @buf_location: buffer location. One of &क्रमागत iwl_fw_ini_buffer_location
 * @req_size: requested buffer size
 * @max_frags_num: maximum number of fragments
 * @min_size: minimum buffer size
 */
काष्ठा iwl_fw_ini_allocation_tlv अणु
	काष्ठा iwl_fw_ini_header hdr;
	__le32 alloc_id;
	__le32 buf_location;
	__le32 req_size;
	__le32 max_frags_num;
	__le32 min_size;
पूर्ण __packed; /* FW_TLV_DEBUG_BUFFER_ALLOCATION_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_trigger_tlv - trigger TLV
 *
 * Trigger that upon firing, determines what regions to collect
 *
 * @hdr: debug header
 * @समय_poपूर्णांक: समय poपूर्णांक. One of &क्रमागत iwl_fw_ini_समय_poपूर्णांक
 * @trigger_reason: trigger reason
 * @apply_policy: uses &क्रमागत iwl_fw_ini_trigger_apply_policy
 * @dump_delay: delay from trigger fire to dump, in usec
 * @occurrences: max trigger fire occurrences allowed
 * @reserved: unused
 * @ignore_consec: ignore consecutive triggers, in usec
 * @reset_fw: अगर non zero, will reset and reload the FW
 * @multi_dut: initiate debug dump data on several DUTs
 * @regions_mask: mask of regions to collect
 * @data: trigger data
 */
काष्ठा iwl_fw_ini_trigger_tlv अणु
	काष्ठा iwl_fw_ini_header hdr;
	__le32 समय_poपूर्णांक;
	__le32 trigger_reason;
	__le32 apply_policy;
	__le32 dump_delay;
	__le32 occurrences;
	__le32 reserved;
	__le32 ignore_consec;
	__le32 reset_fw;
	__le32 multi_dut;
	__le64 regions_mask;
	__le32 data[];
पूर्ण __packed; /* FW_TLV_DEBUG_TRIGGER_API_S_VER_1 */

/**
 * काष्ठा iwl_fw_ini_hcmd_tlv - Generic Host command pass through TLV
 *
 * @hdr: debug header
 * @समय_poपूर्णांक: समय poपूर्णांक. One of &क्रमागत iwl_fw_ini_समय_poपूर्णांक
 * @period_msec: पूर्णांकerval at which the hcmd will be sent to the FW.
 *	Measured in msec (0 = one समय command)
 * @hcmd: a variable length host-command to be sent to apply the configuration
 */
काष्ठा iwl_fw_ini_hcmd_tlv अणु
	काष्ठा iwl_fw_ini_header hdr;
	__le32 समय_poपूर्णांक;
	__le32 period_msec;
	काष्ठा iwl_fw_ini_hcmd hcmd;
पूर्ण __packed; /* FW_TLV_DEBUG_HCMD_API_S_VER_1 */

/**
 * क्रमागत iwl_fw_ini_allocation_id
 *
 * @IWL_FW_INI_ALLOCATION_INVALID: invalid
 * @IWL_FW_INI_ALLOCATION_ID_DBGC1: allocation meant क्रम DBGC1 configuration
 * @IWL_FW_INI_ALLOCATION_ID_DBGC2: allocation meant क्रम DBGC2 configuration
 * @IWL_FW_INI_ALLOCATION_ID_DBGC3: allocation meant क्रम DBGC3 configuration
 * @IWL_FW_INI_ALLOCATION_ID_INTERNAL: allocation meant क्रम Intreanl SMEM in D3
 * @IWL_FW_INI_ALLOCATION_NUM: number of allocation ids
*/
क्रमागत iwl_fw_ini_allocation_id अणु
	IWL_FW_INI_ALLOCATION_INVALID,
	IWL_FW_INI_ALLOCATION_ID_DBGC1,
	IWL_FW_INI_ALLOCATION_ID_DBGC2,
	IWL_FW_INI_ALLOCATION_ID_DBGC3,
	IWL_FW_INI_ALLOCATION_ID_INTERNAL,
	IWL_FW_INI_ALLOCATION_NUM,
पूर्ण; /* FW_DEBUG_TLV_ALLOCATION_ID_E_VER_1 */

/**
 * क्रमागत iwl_fw_ini_buffer_location
 *
 * @IWL_FW_INI_LOCATION_INVALID: invalid
 * @IWL_FW_INI_LOCATION_SRAM_PATH: SRAM location
 * @IWL_FW_INI_LOCATION_DRAM_PATH: DRAM location
 * @IWL_FW_INI_LOCATION_NPK_PATH: NPK location
 */
क्रमागत iwl_fw_ini_buffer_location अणु
	IWL_FW_INI_LOCATION_INVALID,
	IWL_FW_INI_LOCATION_SRAM_PATH,
	IWL_FW_INI_LOCATION_DRAM_PATH,
	IWL_FW_INI_LOCATION_NPK_PATH,
	IWL_FW_INI_LOCATION_NUM,
पूर्ण; /* FW_DEBUG_TLV_BUFFER_LOCATION_E_VER_1 */

/**
 * क्रमागत iwl_fw_ini_region_type
 *
 * @IWL_FW_INI_REGION_INVALID: invalid
 * @IWL_FW_INI_REGION_TLV: uCode and debug TLVs
 * @IWL_FW_INI_REGION_INTERNAL_BUFFER: monitor SMEM buffer
 * @IWL_FW_INI_REGION_DRAM_BUFFER: monitor DRAM buffer
 * @IWL_FW_INI_REGION_TXF: TX fअगरos
 * @IWL_FW_INI_REGION_RXF: RX fअगरo
 * @IWL_FW_INI_REGION_LMAC_ERROR_TABLE: lmac error table
 * @IWL_FW_INI_REGION_UMAC_ERROR_TABLE: umac error table
 * @IWL_FW_INI_REGION_RSP_OR_NOTIF: FW response or notअगरication data
 * @IWL_FW_INI_REGION_DEVICE_MEMORY: device पूर्णांकernal memory
 * @IWL_FW_INI_REGION_PERIPHERY_MAC: periphery रेजिस्टरs of MAC
 * @IWL_FW_INI_REGION_PERIPHERY_PHY: periphery रेजिस्टरs of PHY
 * @IWL_FW_INI_REGION_PERIPHERY_AUX: periphery रेजिस्टरs of AUX
 * @IWL_FW_INI_REGION_PAGING: paging memory
 * @IWL_FW_INI_REGION_CSR: CSR रेजिस्टरs
 * @IWL_FW_INI_REGION_DRAM_IMR: IMR memory
 * @IWL_FW_INI_REGION_PCI_IOSF_CONFIG: PCI/IOSF config
 * @IWL_FW_INI_REGION_SPECIAL_DEVICE_MEMORY: special device memory
 * @IWL_FW_INI_REGION_NUM: number of region types
 */
क्रमागत iwl_fw_ini_region_type अणु
	IWL_FW_INI_REGION_INVALID,
	IWL_FW_INI_REGION_TLV,
	IWL_FW_INI_REGION_INTERNAL_BUFFER,
	IWL_FW_INI_REGION_DRAM_BUFFER,
	IWL_FW_INI_REGION_TXF,
	IWL_FW_INI_REGION_RXF,
	IWL_FW_INI_REGION_LMAC_ERROR_TABLE,
	IWL_FW_INI_REGION_UMAC_ERROR_TABLE,
	IWL_FW_INI_REGION_RSP_OR_NOTIF,
	IWL_FW_INI_REGION_DEVICE_MEMORY,
	IWL_FW_INI_REGION_PERIPHERY_MAC,
	IWL_FW_INI_REGION_PERIPHERY_PHY,
	IWL_FW_INI_REGION_PERIPHERY_AUX,
	IWL_FW_INI_REGION_PAGING,
	IWL_FW_INI_REGION_CSR,
	IWL_FW_INI_REGION_DRAM_IMR,
	IWL_FW_INI_REGION_PCI_IOSF_CONFIG,
	IWL_FW_INI_REGION_SPECIAL_DEVICE_MEMORY,
	IWL_FW_INI_REGION_NUM
पूर्ण; /* FW_TLV_DEBUG_REGION_TYPE_API_E */

/**
 * क्रमागत iwl_fw_ini_समय_poपूर्णांक
 *
 * Hard coded समय poपूर्णांकs in which the driver can send hcmd or perक्रमm dump
 * collection
 *
 * @IWL_FW_INI_TIME_POINT_EARLY: pre loading the FW
 * @IWL_FW_INI_TIME_POINT_AFTER_ALIVE: first cmd from host after alive notअगर
 * @IWL_FW_INI_TIME_POINT_POST_INIT: last cmd in series of init sequence
 * @IWL_FW_INI_TIME_POINT_FW_ASSERT: FW निश्चित
 * @IWL_FW_INI_TIME_POINT_FW_HW_ERROR: FW HW error
 * @IWL_FW_INI_TIME_POINT_FW_TFD_Q_HANG: TFD queue hang
 * @IWL_FW_INI_TIME_POINT_FW_DHC_NOTIFICATION: DHC cmd response and notअगर
 * @IWL_FW_INI_TIME_POINT_FW_RSP_OR_NOTIF: FW response or notअगरication.
 *	data field holds id and group
 * @IWL_FW_INI_TIME_POINT_USER_TRIGGER: user trigger समय poपूर्णांक
 * @IWL_FW_INI_TIME_POINT_PERIODIC: periodic समयpoपूर्णांक that fires in स्थिरant
 *	पूर्णांकervals. data field holds the पूर्णांकerval समय in msec
 * @IWL_FW_INI_TIME_POINT_RESERVED: reserved
 * @IWL_FW_INI_TIME_POINT_HOST_ASSERT: Unused
 * @IWL_FW_INI_TIME_POINT_HOST_ALIVE_TIMEOUT: alive समयout
 * @IWL_FW_INI_TIME_POINT_HOST_DEVICE_ENABLE: device enable
 * @IWL_FW_INI_TIME_POINT_HOST_DEVICE_DISABLE: device disable
 * @IWL_FW_INI_TIME_POINT_HOST_D3_START: D3 start
 * @IWL_FW_INI_TIME_POINT_HOST_D3_END: D3 end
 * @IWL_FW_INI_TIME_POINT_MISSED_BEACONS: missed beacons
 * @IWL_FW_INI_TIME_POINT_ASSOC_FAILED: association failure
 * @IWL_FW_INI_TIME_POINT_TX_FAILED: Tx frame failed
 * @IWL_FW_INI_TIME_POINT_TX_WFD_ACTION_FRAME_FAILED: wअगरi direct action
 *	frame failed
 * @IWL_FW_INI_TIME_POINT_TX_LATENCY_THRESHOLD: Tx latency threshold
 * @IWL_FW_INI_TIME_POINT_HANG_OCCURRED: hang occurred
 * @IWL_FW_INI_TIME_POINT_EAPOL_FAILED: EAPOL failed
 * @IWL_FW_INI_TIME_POINT_FAKE_TX: fake Tx
 * @IWL_FW_INI_TIME_POINT_DEASSOC: de association
 * @IWL_FW_INI_TIME_POINT_NUM: number of समय poपूर्णांकs
 */
क्रमागत iwl_fw_ini_समय_poपूर्णांक अणु
	IWL_FW_INI_TIME_POINT_INVALID,
	IWL_FW_INI_TIME_POINT_EARLY,
	IWL_FW_INI_TIME_POINT_AFTER_ALIVE,
	IWL_FW_INI_TIME_POINT_POST_INIT,
	IWL_FW_INI_TIME_POINT_FW_ASSERT,
	IWL_FW_INI_TIME_POINT_FW_HW_ERROR,
	IWL_FW_INI_TIME_POINT_FW_TFD_Q_HANG,
	IWL_FW_INI_TIME_POINT_FW_DHC_NOTIFICATION,
	IWL_FW_INI_TIME_POINT_FW_RSP_OR_NOTIF,
	IWL_FW_INI_TIME_POINT_USER_TRIGGER,
	IWL_FW_INI_TIME_POINT_PERIODIC,
	IWL_FW_INI_TIME_POINT_RESERVED,
	IWL_FW_INI_TIME_POINT_HOST_ASSERT,
	IWL_FW_INI_TIME_POINT_HOST_ALIVE_TIMEOUT,
	IWL_FW_INI_TIME_POINT_HOST_DEVICE_ENABLE,
	IWL_FW_INI_TIME_POINT_HOST_DEVICE_DISABLE,
	IWL_FW_INI_TIME_POINT_HOST_D3_START,
	IWL_FW_INI_TIME_POINT_HOST_D3_END,
	IWL_FW_INI_TIME_POINT_MISSED_BEACONS,
	IWL_FW_INI_TIME_POINT_ASSOC_FAILED,
	IWL_FW_INI_TIME_POINT_TX_FAILED,
	IWL_FW_INI_TIME_POINT_TX_WFD_ACTION_FRAME_FAILED,
	IWL_FW_INI_TIME_POINT_TX_LATENCY_THRESHOLD,
	IWL_FW_INI_TIME_POINT_HANG_OCCURRED,
	IWL_FW_INI_TIME_POINT_EAPOL_FAILED,
	IWL_FW_INI_TIME_POINT_FAKE_TX,
	IWL_FW_INI_TIME_POINT_DEASSOC,
	IWL_FW_INI_TIME_POINT_NUM,
पूर्ण; /* FW_TLV_DEBUG_TIME_POINT_API_E */

/**
 * क्रमागत iwl_fw_ini_trigger_apply_policy - Determines how to apply triggers
 *
 * @IWL_FW_INI_APPLY_POLICY_MATCH_TIME_POINT: match by समय poपूर्णांक
 * @IWL_FW_INI_APPLY_POLICY_MATCH_DATA: match by trigger data
 * @IWL_FW_INI_APPLY_POLICY_OVERRIDE_REGIONS: override regions mask.
 *	Append otherwise
 * @IWL_FW_INI_APPLY_POLICY_OVERRIDE_CFG: override trigger configuration
 * @IWL_FW_INI_APPLY_POLICY_OVERRIDE_DATA: override trigger data.
 *	Append otherwise
 */
क्रमागत iwl_fw_ini_trigger_apply_policy अणु
	IWL_FW_INI_APPLY_POLICY_MATCH_TIME_POINT	= BIT(0),
	IWL_FW_INI_APPLY_POLICY_MATCH_DATA		= BIT(1),
	IWL_FW_INI_APPLY_POLICY_OVERRIDE_REGIONS	= BIT(8),
	IWL_FW_INI_APPLY_POLICY_OVERRIDE_CFG		= BIT(9),
	IWL_FW_INI_APPLY_POLICY_OVERRIDE_DATA		= BIT(10),
पूर्ण;
#पूर्ण_अगर
