<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-or-later */
/*
 * Universal Flash Storage Host controller driver
 * Copyright (C) 2011-2013 Samsung India Software Operations
 *
 * Authors:
 *	Santosh Yaraganavi <santosh.sy@samsung.com>
 *	Vinayak Holikatti <h.vinayak@samsung.com>
 */

#अगर_अघोषित _UFSHCI_H
#घोषणा _UFSHCI_H

क्रमागत अणु
	TASK_REQ_UPIU_SIZE_DWORDS	= 8,
	TASK_RSP_UPIU_SIZE_DWORDS	= 8,
	ALIGNED_UPIU_SIZE		= 512,
पूर्ण;

/* UFSHCI Registers */
क्रमागत अणु
	REG_CONTROLLER_CAPABILITIES		= 0x00,
	REG_UFS_VERSION				= 0x08,
	REG_CONTROLLER_DEV_ID			= 0x10,
	REG_CONTROLLER_PROD_ID			= 0x14,
	REG_AUTO_HIBERNATE_IDLE_TIMER		= 0x18,
	REG_INTERRUPT_STATUS			= 0x20,
	REG_INTERRUPT_ENABLE			= 0x24,
	REG_CONTROLLER_STATUS			= 0x30,
	REG_CONTROLLER_ENABLE			= 0x34,
	REG_UIC_ERROR_CODE_PHY_ADAPTER_LAYER	= 0x38,
	REG_UIC_ERROR_CODE_DATA_LINK_LAYER	= 0x3C,
	REG_UIC_ERROR_CODE_NETWORK_LAYER	= 0x40,
	REG_UIC_ERROR_CODE_TRANSPORT_LAYER	= 0x44,
	REG_UIC_ERROR_CODE_DME			= 0x48,
	REG_UTP_TRANSFER_REQ_INT_AGG_CONTROL	= 0x4C,
	REG_UTP_TRANSFER_REQ_LIST_BASE_L	= 0x50,
	REG_UTP_TRANSFER_REQ_LIST_BASE_H	= 0x54,
	REG_UTP_TRANSFER_REQ_DOOR_BELL		= 0x58,
	REG_UTP_TRANSFER_REQ_LIST_CLEAR		= 0x5C,
	REG_UTP_TRANSFER_REQ_LIST_RUN_STOP	= 0x60,
	REG_UTP_TASK_REQ_LIST_BASE_L		= 0x70,
	REG_UTP_TASK_REQ_LIST_BASE_H		= 0x74,
	REG_UTP_TASK_REQ_DOOR_BELL		= 0x78,
	REG_UTP_TASK_REQ_LIST_CLEAR		= 0x7C,
	REG_UTP_TASK_REQ_LIST_RUN_STOP		= 0x80,
	REG_UIC_COMMAND				= 0x90,
	REG_UIC_COMMAND_ARG_1			= 0x94,
	REG_UIC_COMMAND_ARG_2			= 0x98,
	REG_UIC_COMMAND_ARG_3			= 0x9C,

	UFSHCI_REG_SPACE_SIZE			= 0xA0,

	REG_UFS_CCAP				= 0x100,
	REG_UFS_CRYPTOCAP			= 0x104,

	UFSHCI_CRYPTO_REG_SPACE_SIZE		= 0x400,
पूर्ण;

/* Controller capability masks */
क्रमागत अणु
	MASK_TRANSFER_REQUESTS_SLOTS		= 0x0000001F,
	MASK_TASK_MANAGEMENT_REQUEST_SLOTS	= 0x00070000,
	MASK_AUTO_HIBERN8_SUPPORT		= 0x00800000,
	MASK_64_ADDRESSING_SUPPORT		= 0x01000000,
	MASK_OUT_OF_ORDER_DATA_DELIVERY_SUPPORT	= 0x02000000,
	MASK_UIC_DME_TEST_MODE_SUPPORT		= 0x04000000,
	MASK_CRYPTO_SUPPORT			= 0x10000000,
पूर्ण;

#घोषणा UFS_MASK(mask, offset)		((mask) << (offset))

/* UFS Version 08h */
#घोषणा MINOR_VERSION_NUM_MASK		UFS_MASK(0xFFFF, 0)
#घोषणा MAJOR_VERSION_NUM_MASK		UFS_MASK(0xFFFF, 16)

/*
 * Controller UFSHCI version
 * - 2.x and newer use the following scheme:
 *   major << 8 + minor << 4
 * - 1.x has been converted to match this in
 *   ufshcd_get_ufs_version()
 */
अटल अंतरभूत u32 ufshci_version(u32 major, u32 minor)
अणु
	वापस (major << 8) + (minor << 4);
पूर्ण

/*
 * HCDDID - Host Controller Identअगरication Descriptor
 *	  - Device ID and Device Class 10h
 */
#घोषणा DEVICE_CLASS	UFS_MASK(0xFFFF, 0)
#घोषणा DEVICE_ID	UFS_MASK(0xFF, 24)

/*
 * HCPMID - Host Controller Identअगरication Descriptor
 *	  - Product/Manufacturer ID  14h
 */
#घोषणा MANUFACTURE_ID_MASK	UFS_MASK(0xFFFF, 0)
#घोषणा PRODUCT_ID_MASK		UFS_MASK(0xFFFF, 16)

/* AHIT - Auto-Hibernate Idle Timer */
#घोषणा UFSHCI_AHIBERN8_TIMER_MASK		GENMASK(9, 0)
#घोषणा UFSHCI_AHIBERN8_SCALE_MASK		GENMASK(12, 10)
#घोषणा UFSHCI_AHIBERN8_SCALE_FACTOR		10
#घोषणा UFSHCI_AHIBERN8_MAX			(1023 * 100000)

/*
 * IS - Interrupt Status - 20h
 */
#घोषणा UTP_TRANSFER_REQ_COMPL			0x1
#घोषणा UIC_DME_END_PT_RESET			0x2
#घोषणा UIC_ERROR				0x4
#घोषणा UIC_TEST_MODE				0x8
#घोषणा UIC_POWER_MODE				0x10
#घोषणा UIC_HIBERNATE_EXIT			0x20
#घोषणा UIC_HIBERNATE_ENTER			0x40
#घोषणा UIC_LINK_LOST				0x80
#घोषणा UIC_LINK_STARTUP			0x100
#घोषणा UTP_TASK_REQ_COMPL			0x200
#घोषणा UIC_COMMAND_COMPL			0x400
#घोषणा DEVICE_FATAL_ERROR			0x800
#घोषणा CONTROLLER_FATAL_ERROR			0x10000
#घोषणा SYSTEM_BUS_FATAL_ERROR			0x20000
#घोषणा CRYPTO_ENGINE_FATAL_ERROR		0x40000

#घोषणा UFSHCD_UIC_HIBERN8_MASK	(UIC_HIBERNATE_ENTER |\
				UIC_HIBERNATE_EXIT)

#घोषणा UFSHCD_UIC_PWR_MASK	(UFSHCD_UIC_HIBERN8_MASK |\
				UIC_POWER_MODE)

#घोषणा UFSHCD_UIC_MASK		(UIC_COMMAND_COMPL | UFSHCD_UIC_PWR_MASK)

#घोषणा UFSHCD_ERROR_MASK	(UIC_ERROR |\
				DEVICE_FATAL_ERROR |\
				CONTROLLER_FATAL_ERROR |\
				SYSTEM_BUS_FATAL_ERROR |\
				CRYPTO_ENGINE_FATAL_ERROR)

#घोषणा INT_FATAL_ERRORS	(DEVICE_FATAL_ERROR |\
				CONTROLLER_FATAL_ERROR |\
				SYSTEM_BUS_FATAL_ERROR |\
				CRYPTO_ENGINE_FATAL_ERROR)

/* HCS - Host Controller Status 30h */
#घोषणा DEVICE_PRESENT				0x1
#घोषणा UTP_TRANSFER_REQ_LIST_READY		0x2
#घोषणा UTP_TASK_REQ_LIST_READY			0x4
#घोषणा UIC_COMMAND_READY			0x8
#घोषणा HOST_ERROR_INDICATOR			0x10
#घोषणा DEVICE_ERROR_INDICATOR			0x20
#घोषणा UIC_POWER_MODE_CHANGE_REQ_STATUS_MASK	UFS_MASK(0x7, 8)

#घोषणा UFSHCD_STATUS_READY	(UTP_TRANSFER_REQ_LIST_READY |\
				UTP_TASK_REQ_LIST_READY |\
				UIC_COMMAND_READY)

क्रमागत अणु
	PWR_OK		= 0x0,
	PWR_LOCAL	= 0x01,
	PWR_REMOTE	= 0x02,
	PWR_BUSY	= 0x03,
	PWR_ERROR_CAP	= 0x04,
	PWR_FATAL_ERROR	= 0x05,
पूर्ण;

/* HCE - Host Controller Enable 34h */
#घोषणा CONTROLLER_ENABLE	0x1
#घोषणा CONTROLLER_DISABLE	0x0
#घोषणा CRYPTO_GENERAL_ENABLE	0x2

/* UECPA - Host UIC Error Code PHY Adapter Layer 38h */
#घोषणा UIC_PHY_ADAPTER_LAYER_ERROR			0x80000000
#घोषणा UIC_PHY_ADAPTER_LAYER_ERROR_CODE_MASK		0x1F
#घोषणा UIC_PHY_ADAPTER_LAYER_LANE_ERR_MASK		0xF
#घोषणा UIC_PHY_ADAPTER_LAYER_GENERIC_ERROR		0x10

/* UECDL - Host UIC Error Code Data Link Layer 3Ch */
#घोषणा UIC_DATA_LINK_LAYER_ERROR		0x80000000
#घोषणा UIC_DATA_LINK_LAYER_ERROR_CODE_MASK	0xFFFF
#घोषणा UIC_DATA_LINK_LAYER_ERROR_TCX_REP_TIMER_EXP	0x2
#घोषणा UIC_DATA_LINK_LAYER_ERROR_AFCX_REQ_TIMER_EXP	0x4
#घोषणा UIC_DATA_LINK_LAYER_ERROR_FCX_PRO_TIMER_EXP	0x8
#घोषणा UIC_DATA_LINK_LAYER_ERROR_RX_BUF_OF	0x20
#घोषणा UIC_DATA_LINK_LAYER_ERROR_PA_INIT	0x2000
#घोषणा UIC_DATA_LINK_LAYER_ERROR_NAC_RECEIVED	0x0001
#घोषणा UIC_DATA_LINK_LAYER_ERROR_TCx_REPLAY_TIMEOUT 0x0002

/* UECN - Host UIC Error Code Network Layer 40h */
#घोषणा UIC_NETWORK_LAYER_ERROR			0x80000000
#घोषणा UIC_NETWORK_LAYER_ERROR_CODE_MASK	0x7
#घोषणा UIC_NETWORK_UNSUPPORTED_HEADER_TYPE	0x1
#घोषणा UIC_NETWORK_BAD_DEVICEID_ENC		0x2
#घोषणा UIC_NETWORK_LHDR_TRAP_PACKET_DROPPING	0x4

/* UECT - Host UIC Error Code Transport Layer 44h */
#घोषणा UIC_TRANSPORT_LAYER_ERROR		0x80000000
#घोषणा UIC_TRANSPORT_LAYER_ERROR_CODE_MASK	0x7F
#घोषणा UIC_TRANSPORT_UNSUPPORTED_HEADER_TYPE	0x1
#घोषणा UIC_TRANSPORT_UNKNOWN_CPORTID		0x2
#घोषणा UIC_TRANSPORT_NO_CONNECTION_RX		0x4
#घोषणा UIC_TRANSPORT_CONTROLLED_SEGMENT_DROPPING	0x8
#घोषणा UIC_TRANSPORT_BAD_TC			0x10
#घोषणा UIC_TRANSPORT_E2E_CREDIT_OVERFOW	0x20
#घोषणा UIC_TRANSPORT_SAFETY_VALUE_DROPPING	0x40

/* UECDME - Host UIC Error Code DME 48h */
#घोषणा UIC_DME_ERROR			0x80000000
#घोषणा UIC_DME_ERROR_CODE_MASK		0x1

/* UTRIACR - Interrupt Aggregation control रेजिस्टर - 0x4Ch */
#घोषणा INT_AGGR_TIMEOUT_VAL_MASK		0xFF
#घोषणा INT_AGGR_COUNTER_THRESHOLD_MASK		UFS_MASK(0x1F, 8)
#घोषणा INT_AGGR_COUNTER_AND_TIMER_RESET	0x10000
#घोषणा INT_AGGR_STATUS_BIT			0x100000
#घोषणा INT_AGGR_PARAM_WRITE			0x1000000
#घोषणा INT_AGGR_ENABLE				0x80000000

/* UTRLRSR - UTP Transfer Request Run-Stop Register 60h */
#घोषणा UTP_TRANSFER_REQ_LIST_RUN_STOP_BIT	0x1

/* UTMRLRSR - UTP Task Management Request Run-Stop Register 80h */
#घोषणा UTP_TASK_REQ_LIST_RUN_STOP_BIT		0x1

/* UICCMD - UIC Command */
#घोषणा COMMAND_OPCODE_MASK		0xFF
#घोषणा GEN_SELECTOR_INDEX_MASK		0xFFFF

#घोषणा MIB_ATTRIBUTE_MASK		UFS_MASK(0xFFFF, 16)
#घोषणा RESET_LEVEL			0xFF

#घोषणा ATTR_SET_TYPE_MASK		UFS_MASK(0xFF, 16)
#घोषणा CONFIG_RESULT_CODE_MASK		0xFF
#घोषणा GENERIC_ERROR_CODE_MASK		0xFF

/* GenSelectorIndex calculation macros क्रम M-PHY attributes */
#घोषणा UIC_ARG_MPHY_TX_GEN_SEL_INDEX(lane) (lane)
#घोषणा UIC_ARG_MPHY_RX_GEN_SEL_INDEX(lane) (PA_MAXDATALANES + (lane))

#घोषणा UIC_ARG_MIB_SEL(attr, sel)	((((attr) & 0xFFFF) << 16) |\
					 ((sel) & 0xFFFF))
#घोषणा UIC_ARG_MIB(attr)		UIC_ARG_MIB_SEL(attr, 0)
#घोषणा UIC_ARG_ATTR_TYPE(t)		(((t) & 0xFF) << 16)
#घोषणा UIC_GET_ATTR_ID(v)		(((v) >> 16) & 0xFFFF)

/* Link Status*/
क्रमागत link_status अणु
	UFSHCD_LINK_IS_DOWN	= 1,
	UFSHCD_LINK_IS_UP	= 2,
पूर्ण;

/* UIC Commands */
क्रमागत uic_cmd_dme अणु
	UIC_CMD_DME_GET			= 0x01,
	UIC_CMD_DME_SET			= 0x02,
	UIC_CMD_DME_PEER_GET		= 0x03,
	UIC_CMD_DME_PEER_SET		= 0x04,
	UIC_CMD_DME_POWERON		= 0x10,
	UIC_CMD_DME_POWEROFF		= 0x11,
	UIC_CMD_DME_ENABLE		= 0x12,
	UIC_CMD_DME_RESET		= 0x14,
	UIC_CMD_DME_END_PT_RST		= 0x15,
	UIC_CMD_DME_LINK_STARTUP	= 0x16,
	UIC_CMD_DME_HIBER_ENTER		= 0x17,
	UIC_CMD_DME_HIBER_EXIT		= 0x18,
	UIC_CMD_DME_TEST_MODE		= 0x1A,
पूर्ण;

/* UIC Config result code / Generic error code */
क्रमागत अणु
	UIC_CMD_RESULT_SUCCESS			= 0x00,
	UIC_CMD_RESULT_INVALID_ATTR		= 0x01,
	UIC_CMD_RESULT_FAILURE			= 0x01,
	UIC_CMD_RESULT_INVALID_ATTR_VALUE	= 0x02,
	UIC_CMD_RESULT_READ_ONLY_ATTR		= 0x03,
	UIC_CMD_RESULT_WRITE_ONLY_ATTR		= 0x04,
	UIC_CMD_RESULT_BAD_INDEX		= 0x05,
	UIC_CMD_RESULT_LOCKED_ATTR		= 0x06,
	UIC_CMD_RESULT_BAD_TEST_FEATURE_INDEX	= 0x07,
	UIC_CMD_RESULT_PEER_COMM_FAILURE	= 0x08,
	UIC_CMD_RESULT_BUSY			= 0x09,
	UIC_CMD_RESULT_DME_FAILURE		= 0x0A,
पूर्ण;

#घोषणा MASK_UIC_COMMAND_RESULT			0xFF

#घोषणा INT_AGGR_COUNTER_THLD_VAL(c)	(((c) & 0x1F) << 8)
#घोषणा INT_AGGR_TIMEOUT_VAL(t)		(((t) & 0xFF) << 0)

/* Interrupt disable masks */
क्रमागत अणु
	/* Interrupt disable mask क्रम UFSHCI v1.0 */
	INTERRUPT_MASK_ALL_VER_10	= 0x30FFF,
	INTERRUPT_MASK_RW_VER_10	= 0x30000,

	/* Interrupt disable mask क्रम UFSHCI v1.1 */
	INTERRUPT_MASK_ALL_VER_11	= 0x31FFF,

	/* Interrupt disable mask क्रम UFSHCI v2.1 */
	INTERRUPT_MASK_ALL_VER_21	= 0x71FFF,
पूर्ण;

/* CCAP - Crypto Capability 100h */
जोड़ ufs_crypto_capabilities अणु
	__le32 reg_val;
	काष्ठा अणु
		u8 num_crypto_cap;
		u8 config_count;
		u8 reserved;
		u8 config_array_ptr;
	पूर्ण;
पूर्ण;

क्रमागत ufs_crypto_key_size अणु
	UFS_CRYPTO_KEY_SIZE_INVALID	= 0x0,
	UFS_CRYPTO_KEY_SIZE_128		= 0x1,
	UFS_CRYPTO_KEY_SIZE_192		= 0x2,
	UFS_CRYPTO_KEY_SIZE_256		= 0x3,
	UFS_CRYPTO_KEY_SIZE_512		= 0x4,
पूर्ण;

क्रमागत ufs_crypto_alg अणु
	UFS_CRYPTO_ALG_AES_XTS			= 0x0,
	UFS_CRYPTO_ALG_BITLOCKER_AES_CBC	= 0x1,
	UFS_CRYPTO_ALG_AES_ECB			= 0x2,
	UFS_CRYPTO_ALG_ESSIV_AES_CBC		= 0x3,
पूर्ण;

/* x-CRYPTOCAP - Crypto Capability X */
जोड़ ufs_crypto_cap_entry अणु
	__le32 reg_val;
	काष्ठा अणु
		u8 algorithm_id;
		u8 sdus_mask; /* Supported data unit size mask */
		u8 key_size;
		u8 reserved;
	पूर्ण;
पूर्ण;

#घोषणा UFS_CRYPTO_CONFIGURATION_ENABLE (1 << 7)
#घोषणा UFS_CRYPTO_KEY_MAX_SIZE 64
/* x-CRYPTOCFG - Crypto Configuration X */
जोड़ ufs_crypto_cfg_entry अणु
	__le32 reg_val[32];
	काष्ठा अणु
		u8 crypto_key[UFS_CRYPTO_KEY_MAX_SIZE];
		u8 data_unit_size;
		u8 crypto_cap_idx;
		u8 reserved_1;
		u8 config_enable;
		u8 reserved_multi_host;
		u8 reserved_2;
		u8 vsb[2];
		u8 reserved_3[56];
	पूर्ण;
पूर्ण;

/*
 * Request Descriptor Definitions
 */

/* Transfer request command type */
क्रमागत अणु
	UTP_CMD_TYPE_SCSI		= 0x0,
	UTP_CMD_TYPE_UFS		= 0x1,
	UTP_CMD_TYPE_DEV_MANAGE		= 0x2,
पूर्ण;

/* To accommodate UFS2.0 required Command type */
क्रमागत अणु
	UTP_CMD_TYPE_UFS_STORAGE	= 0x1,
पूर्ण;

क्रमागत अणु
	UTP_SCSI_COMMAND		= 0x00000000,
	UTP_NATIVE_UFS_COMMAND		= 0x10000000,
	UTP_DEVICE_MANAGEMENT_FUNCTION	= 0x20000000,
	UTP_REQ_DESC_INT_CMD		= 0x01000000,
	UTP_REQ_DESC_CRYPTO_ENABLE_CMD	= 0x00800000,
पूर्ण;

/* UTP Transfer Request Data Direction (DD) */
क्रमागत अणु
	UTP_NO_DATA_TRANSFER	= 0x00000000,
	UTP_HOST_TO_DEVICE	= 0x02000000,
	UTP_DEVICE_TO_HOST	= 0x04000000,
पूर्ण;

/* Overall command status values */
क्रमागत अणु
	OCS_SUCCESS			= 0x0,
	OCS_INVALID_CMD_TABLE_ATTR	= 0x1,
	OCS_INVALID_PRDT_ATTR		= 0x2,
	OCS_MISMATCH_DATA_BUF_SIZE	= 0x3,
	OCS_MISMATCH_RESP_UPIU_SIZE	= 0x4,
	OCS_PEER_COMM_FAILURE		= 0x5,
	OCS_ABORTED			= 0x6,
	OCS_FATAL_ERROR			= 0x7,
	OCS_DEVICE_FATAL_ERROR		= 0x8,
	OCS_INVALID_CRYPTO_CONFIG	= 0x9,
	OCS_GENERAL_CRYPTO_ERROR	= 0xA,
	OCS_INVALID_COMMAND_STATUS	= 0x0F,
	MASK_OCS			= 0x0F,
पूर्ण;

/* The maximum length of the data byte count field in the PRDT is 256KB */
#घोषणा PRDT_DATA_BYTE_COUNT_MAX	(256 * 1024)
/* The granularity of the data byte count field in the PRDT is 32-bit */
#घोषणा PRDT_DATA_BYTE_COUNT_PAD	4

/**
 * काष्ठा ufshcd_sg_entry - UFSHCI PRD Entry
 * @base_addr: Lower 32bit physical address DW-0
 * @upper_addr: Upper 32bit physical address DW-1
 * @reserved: Reserved क्रम future use DW-2
 * @size: size of physical segment DW-3
 */
काष्ठा ufshcd_sg_entry अणु
	__le32    base_addr;
	__le32    upper_addr;
	__le32    reserved;
	__le32    size;
पूर्ण;

/**
 * काष्ठा utp_transfer_cmd_desc - UFS Command Descriptor काष्ठाure
 * @command_upiu: Command UPIU Frame address
 * @response_upiu: Response UPIU Frame address
 * @prd_table: Physical Region Descriptor
 */
काष्ठा utp_transfer_cmd_desc अणु
	u8 command_upiu[ALIGNED_UPIU_SIZE];
	u8 response_upiu[ALIGNED_UPIU_SIZE];
	काष्ठा ufshcd_sg_entry    prd_table[SG_ALL];
पूर्ण;

/**
 * काष्ठा request_desc_header - Descriptor Header common to both UTRD and UTMRD
 * @dword0: Descriptor Header DW0
 * @dword1: Descriptor Header DW1
 * @dword2: Descriptor Header DW2
 * @dword3: Descriptor Header DW3
 */
काष्ठा request_desc_header अणु
	__le32 dword_0;
	__le32 dword_1;
	__le32 dword_2;
	__le32 dword_3;
पूर्ण;

/**
 * काष्ठा utp_transfer_req_desc - UTRD काष्ठाure
 * @header: UTRD header DW-0 to DW-3
 * @command_desc_base_addr_lo: UCD base address low DW-4
 * @command_desc_base_addr_hi: UCD base address high DW-5
 * @response_upiu_length: response UPIU length DW-6
 * @response_upiu_offset: response UPIU offset DW-6
 * @prd_table_length: Physical region descriptor length DW-7
 * @prd_table_offset: Physical region descriptor offset DW-7
 */
काष्ठा utp_transfer_req_desc अणु

	/* DW 0-3 */
	काष्ठा request_desc_header header;

	/* DW 4-5*/
	__le32  command_desc_base_addr_lo;
	__le32  command_desc_base_addr_hi;

	/* DW 6 */
	__le16  response_upiu_length;
	__le16  response_upiu_offset;

	/* DW 7 */
	__le16  prd_table_length;
	__le16  prd_table_offset;
पूर्ण;

/*
 * UTMRD काष्ठाure.
 */
काष्ठा utp_task_req_desc अणु
	/* DW 0-3 */
	काष्ठा request_desc_header header;

	/* DW 4-11 - Task request UPIU काष्ठाure */
	काष्ठा अणु
		काष्ठा utp_upiu_header	req_header;
		__be32			input_param1;
		__be32			input_param2;
		__be32			input_param3;
		__be32			__reserved1[2];
	पूर्ण upiu_req;

	/* DW 12-19 - Task Management Response UPIU काष्ठाure */
	काष्ठा अणु
		काष्ठा utp_upiu_header	rsp_header;
		__be32			output_param1;
		__be32			output_param2;
		__be32			__reserved2[3];
	पूर्ण upiu_rsp;
पूर्ण;

#पूर्ण_अगर /* End of Header */
