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

#अगर_अघोषित _UFS_H
#घोषणा _UFS_H

#समावेश <linux/mutex.h>
#समावेश <linux/types.h>
#समावेश <uapi/scsi/scsi_bsg_ufs.h>

#घोषणा GENERAL_UPIU_REQUEST_SIZE (माप(काष्ठा utp_upiu_req))
#घोषणा QUERY_DESC_MAX_SIZE       255
#घोषणा QUERY_DESC_MIN_SIZE       2
#घोषणा QUERY_DESC_HDR_SIZE       2
#घोषणा QUERY_OSF_SIZE            (GENERAL_UPIU_REQUEST_SIZE - \
					(माप(काष्ठा utp_upiu_header)))
#घोषणा UFS_SENSE_SIZE	18

#घोषणा UPIU_HEADER_DWORD(byte3, byte2, byte1, byte0)\
			cpu_to_be32((byte3 << 24) | (byte2 << 16) |\
			 (byte1 << 8) | (byte0))
/*
 * UFS device may have standard LUs and LUN id could be from 0x00 to
 * 0x7F. Standard LUs use "Peripheral Device Addressing Format".
 * UFS device may also have the Well Known LUs (also referred as W-LU)
 * which again could be from 0x00 to 0x7F. For W-LUs, device only use
 * the "Extended Addressing Format" which means the W-LUNs would be
 * from 0xc100 (SCSI_W_LUN_BASE) onwards.
 * This means max. LUN number reported from UFS device could be 0xC17F.
 */
#घोषणा UFS_UPIU_MAX_UNIT_NUM_ID	0x7F
#घोषणा UFS_MAX_LUNS		(SCSI_W_LUN_BASE + UFS_UPIU_MAX_UNIT_NUM_ID)
#घोषणा UFS_UPIU_WLUN_ID	(1 << 7)
#घोषणा UFS_RPMB_UNIT		0xC4

/* WriteBooster buffer is available only क्रम the logical unit from 0 to 7 */
#घोषणा UFS_UPIU_MAX_WB_LUN_ID	8

/* Well known logical unit id in LUN field of UPIU */
क्रमागत अणु
	UFS_UPIU_REPORT_LUNS_WLUN	= 0x81,
	UFS_UPIU_UFS_DEVICE_WLUN	= 0xD0,
	UFS_UPIU_BOOT_WLUN		= 0xB0,
	UFS_UPIU_RPMB_WLUN		= 0xC4,
पूर्ण;

/*
 * UFS Protocol Inक्रमmation Unit related definitions
 */

/* Task management functions */
क्रमागत अणु
	UFS_ABORT_TASK		= 0x01,
	UFS_ABORT_TASK_SET	= 0x02,
	UFS_CLEAR_TASK_SET	= 0x04,
	UFS_LOGICAL_RESET	= 0x08,
	UFS_QUERY_TASK		= 0x80,
	UFS_QUERY_TASK_SET	= 0x81,
पूर्ण;

/* UTP UPIU Transaction Codes Initiator to Target */
क्रमागत अणु
	UPIU_TRANSACTION_NOP_OUT	= 0x00,
	UPIU_TRANSACTION_COMMAND	= 0x01,
	UPIU_TRANSACTION_DATA_OUT	= 0x02,
	UPIU_TRANSACTION_TASK_REQ	= 0x04,
	UPIU_TRANSACTION_QUERY_REQ	= 0x16,
पूर्ण;

/* UTP UPIU Transaction Codes Target to Initiator */
क्रमागत अणु
	UPIU_TRANSACTION_NOP_IN		= 0x20,
	UPIU_TRANSACTION_RESPONSE	= 0x21,
	UPIU_TRANSACTION_DATA_IN	= 0x22,
	UPIU_TRANSACTION_TASK_RSP	= 0x24,
	UPIU_TRANSACTION_READY_XFER	= 0x31,
	UPIU_TRANSACTION_QUERY_RSP	= 0x36,
	UPIU_TRANSACTION_REJECT_UPIU	= 0x3F,
पूर्ण;

/* UPIU Read/Write flags */
क्रमागत अणु
	UPIU_CMD_FLAGS_NONE	= 0x00,
	UPIU_CMD_FLAGS_WRITE	= 0x20,
	UPIU_CMD_FLAGS_READ	= 0x40,
पूर्ण;

/* UPIU Task Attributes */
क्रमागत अणु
	UPIU_TASK_ATTR_SIMPLE	= 0x00,
	UPIU_TASK_ATTR_ORDERED	= 0x01,
	UPIU_TASK_ATTR_HEADQ	= 0x02,
	UPIU_TASK_ATTR_ACA	= 0x03,
पूर्ण;

/* UPIU Query request function */
क्रमागत अणु
	UPIU_QUERY_FUNC_STANDARD_READ_REQUEST           = 0x01,
	UPIU_QUERY_FUNC_STANDARD_WRITE_REQUEST          = 0x81,
पूर्ण;

/* Flag idn क्रम Query Requests*/
क्रमागत flag_idn अणु
	QUERY_FLAG_IDN_FDEVICEINIT			= 0x01,
	QUERY_FLAG_IDN_PERMANENT_WPE			= 0x02,
	QUERY_FLAG_IDN_PWR_ON_WPE			= 0x03,
	QUERY_FLAG_IDN_BKOPS_EN				= 0x04,
	QUERY_FLAG_IDN_LIFE_SPAN_MODE_ENABLE		= 0x05,
	QUERY_FLAG_IDN_PURGE_ENABLE			= 0x06,
	QUERY_FLAG_IDN_RESERVED2			= 0x07,
	QUERY_FLAG_IDN_FPHYRESOURCEREMOVAL		= 0x08,
	QUERY_FLAG_IDN_BUSY_RTC				= 0x09,
	QUERY_FLAG_IDN_RESERVED3			= 0x0A,
	QUERY_FLAG_IDN_PERMANENTLY_DISABLE_FW_UPDATE	= 0x0B,
	QUERY_FLAG_IDN_WB_EN                            = 0x0E,
	QUERY_FLAG_IDN_WB_BUFF_FLUSH_EN                 = 0x0F,
	QUERY_FLAG_IDN_WB_BUFF_FLUSH_DURING_HIBERN8     = 0x10,
पूर्ण;

/* Attribute idn क्रम Query requests */
क्रमागत attr_idn अणु
	QUERY_ATTR_IDN_BOOT_LU_EN		= 0x00,
	QUERY_ATTR_IDN_RESERVED			= 0x01,
	QUERY_ATTR_IDN_POWER_MODE		= 0x02,
	QUERY_ATTR_IDN_ACTIVE_ICC_LVL		= 0x03,
	QUERY_ATTR_IDN_OOO_DATA_EN		= 0x04,
	QUERY_ATTR_IDN_BKOPS_STATUS		= 0x05,
	QUERY_ATTR_IDN_PURGE_STATUS		= 0x06,
	QUERY_ATTR_IDN_MAX_DATA_IN		= 0x07,
	QUERY_ATTR_IDN_MAX_DATA_OUT		= 0x08,
	QUERY_ATTR_IDN_DYN_CAP_NEEDED		= 0x09,
	QUERY_ATTR_IDN_REF_CLK_FREQ		= 0x0A,
	QUERY_ATTR_IDN_CONF_DESC_LOCK		= 0x0B,
	QUERY_ATTR_IDN_MAX_NUM_OF_RTT		= 0x0C,
	QUERY_ATTR_IDN_EE_CONTROL		= 0x0D,
	QUERY_ATTR_IDN_EE_STATUS		= 0x0E,
	QUERY_ATTR_IDN_SECONDS_PASSED		= 0x0F,
	QUERY_ATTR_IDN_CNTX_CONF		= 0x10,
	QUERY_ATTR_IDN_CORR_PRG_BLK_NUM		= 0x11,
	QUERY_ATTR_IDN_RESERVED2		= 0x12,
	QUERY_ATTR_IDN_RESERVED3		= 0x13,
	QUERY_ATTR_IDN_FFU_STATUS		= 0x14,
	QUERY_ATTR_IDN_PSA_STATE		= 0x15,
	QUERY_ATTR_IDN_PSA_DATA_SIZE		= 0x16,
	QUERY_ATTR_IDN_REF_CLK_GATING_WAIT_TIME	= 0x17,
	QUERY_ATTR_IDN_WB_FLUSH_STATUS	        = 0x1C,
	QUERY_ATTR_IDN_AVAIL_WB_BUFF_SIZE       = 0x1D,
	QUERY_ATTR_IDN_WB_BUFF_LIFE_TIME_EST    = 0x1E,
	QUERY_ATTR_IDN_CURR_WB_BUFF_SIZE        = 0x1F,
पूर्ण;

/* Descriptor idn क्रम Query requests */
क्रमागत desc_idn अणु
	QUERY_DESC_IDN_DEVICE		= 0x0,
	QUERY_DESC_IDN_CONFIGURATION	= 0x1,
	QUERY_DESC_IDN_UNIT		= 0x2,
	QUERY_DESC_IDN_RFU_0		= 0x3,
	QUERY_DESC_IDN_INTERCONNECT	= 0x4,
	QUERY_DESC_IDN_STRING		= 0x5,
	QUERY_DESC_IDN_RFU_1		= 0x6,
	QUERY_DESC_IDN_GEOMETRY		= 0x7,
	QUERY_DESC_IDN_POWER		= 0x8,
	QUERY_DESC_IDN_HEALTH           = 0x9,
	QUERY_DESC_IDN_MAX,
पूर्ण;

क्रमागत desc_header_offset अणु
	QUERY_DESC_LENGTH_OFFSET	= 0x00,
	QUERY_DESC_DESC_TYPE_OFFSET	= 0x01,
पूर्ण;

/* Unit descriptor parameters offsets in bytes*/
क्रमागत unit_desc_param अणु
	UNIT_DESC_PARAM_LEN			= 0x0,
	UNIT_DESC_PARAM_TYPE			= 0x1,
	UNIT_DESC_PARAM_UNIT_INDEX		= 0x2,
	UNIT_DESC_PARAM_LU_ENABLE		= 0x3,
	UNIT_DESC_PARAM_BOOT_LUN_ID		= 0x4,
	UNIT_DESC_PARAM_LU_WR_PROTECT		= 0x5,
	UNIT_DESC_PARAM_LU_Q_DEPTH		= 0x6,
	UNIT_DESC_PARAM_PSA_SENSITIVE		= 0x7,
	UNIT_DESC_PARAM_MEM_TYPE		= 0x8,
	UNIT_DESC_PARAM_DATA_RELIABILITY	= 0x9,
	UNIT_DESC_PARAM_LOGICAL_BLK_SIZE	= 0xA,
	UNIT_DESC_PARAM_LOGICAL_BLK_COUNT	= 0xB,
	UNIT_DESC_PARAM_ERASE_BLK_SIZE		= 0x13,
	UNIT_DESC_PARAM_PROVISIONING_TYPE	= 0x17,
	UNIT_DESC_PARAM_PHY_MEM_RSRC_CNT	= 0x18,
	UNIT_DESC_PARAM_CTX_CAPABILITIES	= 0x20,
	UNIT_DESC_PARAM_LARGE_UNIT_SIZE_M1	= 0x22,
	UNIT_DESC_PARAM_WB_BUF_ALLOC_UNITS	= 0x29,
पूर्ण;

/* Device descriptor parameters offsets in bytes*/
क्रमागत device_desc_param अणु
	DEVICE_DESC_PARAM_LEN			= 0x0,
	DEVICE_DESC_PARAM_TYPE			= 0x1,
	DEVICE_DESC_PARAM_DEVICE_TYPE		= 0x2,
	DEVICE_DESC_PARAM_DEVICE_CLASS		= 0x3,
	DEVICE_DESC_PARAM_DEVICE_SUB_CLASS	= 0x4,
	DEVICE_DESC_PARAM_PRTCL			= 0x5,
	DEVICE_DESC_PARAM_NUM_LU		= 0x6,
	DEVICE_DESC_PARAM_NUM_WLU		= 0x7,
	DEVICE_DESC_PARAM_BOOT_ENBL		= 0x8,
	DEVICE_DESC_PARAM_DESC_ACCSS_ENBL	= 0x9,
	DEVICE_DESC_PARAM_INIT_PWR_MODE		= 0xA,
	DEVICE_DESC_PARAM_HIGH_PR_LUN		= 0xB,
	DEVICE_DESC_PARAM_SEC_RMV_TYPE		= 0xC,
	DEVICE_DESC_PARAM_SEC_LU		= 0xD,
	DEVICE_DESC_PARAM_BKOP_TERM_LT		= 0xE,
	DEVICE_DESC_PARAM_ACTVE_ICC_LVL		= 0xF,
	DEVICE_DESC_PARAM_SPEC_VER		= 0x10,
	DEVICE_DESC_PARAM_MANF_DATE		= 0x12,
	DEVICE_DESC_PARAM_MANF_NAME		= 0x14,
	DEVICE_DESC_PARAM_PRDCT_NAME		= 0x15,
	DEVICE_DESC_PARAM_SN			= 0x16,
	DEVICE_DESC_PARAM_OEM_ID		= 0x17,
	DEVICE_DESC_PARAM_MANF_ID		= 0x18,
	DEVICE_DESC_PARAM_UD_OFFSET		= 0x1A,
	DEVICE_DESC_PARAM_UD_LEN		= 0x1B,
	DEVICE_DESC_PARAM_RTT_CAP		= 0x1C,
	DEVICE_DESC_PARAM_FRQ_RTC		= 0x1D,
	DEVICE_DESC_PARAM_UFS_FEAT		= 0x1F,
	DEVICE_DESC_PARAM_FFU_TMT		= 0x20,
	DEVICE_DESC_PARAM_Q_DPTH		= 0x21,
	DEVICE_DESC_PARAM_DEV_VER		= 0x22,
	DEVICE_DESC_PARAM_NUM_SEC_WPA		= 0x24,
	DEVICE_DESC_PARAM_PSA_MAX_DATA		= 0x25,
	DEVICE_DESC_PARAM_PSA_TMT		= 0x29,
	DEVICE_DESC_PARAM_PRDCT_REV		= 0x2A,
	DEVICE_DESC_PARAM_EXT_UFS_FEATURE_SUP	= 0x4F,
	DEVICE_DESC_PARAM_WB_PRESRV_USRSPC_EN	= 0x53,
	DEVICE_DESC_PARAM_WB_TYPE		= 0x54,
	DEVICE_DESC_PARAM_WB_SHARED_ALLOC_UNITS = 0x55,
पूर्ण;

/* Interconnect descriptor parameters offsets in bytes*/
क्रमागत पूर्णांकerconnect_desc_param अणु
	INTERCONNECT_DESC_PARAM_LEN		= 0x0,
	INTERCONNECT_DESC_PARAM_TYPE		= 0x1,
	INTERCONNECT_DESC_PARAM_UNIPRO_VER	= 0x2,
	INTERCONNECT_DESC_PARAM_MPHY_VER	= 0x4,
पूर्ण;

/* Geometry descriptor parameters offsets in bytes*/
क्रमागत geometry_desc_param अणु
	GEOMETRY_DESC_PARAM_LEN			= 0x0,
	GEOMETRY_DESC_PARAM_TYPE		= 0x1,
	GEOMETRY_DESC_PARAM_DEV_CAP		= 0x4,
	GEOMETRY_DESC_PARAM_MAX_NUM_LUN		= 0xC,
	GEOMETRY_DESC_PARAM_SEG_SIZE		= 0xD,
	GEOMETRY_DESC_PARAM_ALLOC_UNIT_SIZE	= 0x11,
	GEOMETRY_DESC_PARAM_MIN_BLK_SIZE	= 0x12,
	GEOMETRY_DESC_PARAM_OPT_RD_BLK_SIZE	= 0x13,
	GEOMETRY_DESC_PARAM_OPT_WR_BLK_SIZE	= 0x14,
	GEOMETRY_DESC_PARAM_MAX_IN_BUF_SIZE	= 0x15,
	GEOMETRY_DESC_PARAM_MAX_OUT_BUF_SIZE	= 0x16,
	GEOMETRY_DESC_PARAM_RPMB_RW_SIZE	= 0x17,
	GEOMETRY_DESC_PARAM_DYN_CAP_RSRC_PLC	= 0x18,
	GEOMETRY_DESC_PARAM_DATA_ORDER		= 0x19,
	GEOMETRY_DESC_PARAM_MAX_NUM_CTX		= 0x1A,
	GEOMETRY_DESC_PARAM_TAG_UNIT_SIZE	= 0x1B,
	GEOMETRY_DESC_PARAM_TAG_RSRC_SIZE	= 0x1C,
	GEOMETRY_DESC_PARAM_SEC_RM_TYPES	= 0x1D,
	GEOMETRY_DESC_PARAM_MEM_TYPES		= 0x1E,
	GEOMETRY_DESC_PARAM_SCM_MAX_NUM_UNITS	= 0x20,
	GEOMETRY_DESC_PARAM_SCM_CAP_ADJ_FCTR	= 0x24,
	GEOMETRY_DESC_PARAM_NPM_MAX_NUM_UNITS	= 0x26,
	GEOMETRY_DESC_PARAM_NPM_CAP_ADJ_FCTR	= 0x2A,
	GEOMETRY_DESC_PARAM_ENM1_MAX_NUM_UNITS	= 0x2C,
	GEOMETRY_DESC_PARAM_ENM1_CAP_ADJ_FCTR	= 0x30,
	GEOMETRY_DESC_PARAM_ENM2_MAX_NUM_UNITS	= 0x32,
	GEOMETRY_DESC_PARAM_ENM2_CAP_ADJ_FCTR	= 0x36,
	GEOMETRY_DESC_PARAM_ENM3_MAX_NUM_UNITS	= 0x38,
	GEOMETRY_DESC_PARAM_ENM3_CAP_ADJ_FCTR	= 0x3C,
	GEOMETRY_DESC_PARAM_ENM4_MAX_NUM_UNITS	= 0x3E,
	GEOMETRY_DESC_PARAM_ENM4_CAP_ADJ_FCTR	= 0x42,
	GEOMETRY_DESC_PARAM_OPT_LOG_BLK_SIZE	= 0x44,
	GEOMETRY_DESC_PARAM_WB_MAX_ALLOC_UNITS	= 0x4F,
	GEOMETRY_DESC_PARAM_WB_MAX_WB_LUNS	= 0x53,
	GEOMETRY_DESC_PARAM_WB_BUFF_CAP_ADJ	= 0x54,
	GEOMETRY_DESC_PARAM_WB_SUP_RED_TYPE	= 0x55,
	GEOMETRY_DESC_PARAM_WB_SUP_WB_TYPE	= 0x56,
पूर्ण;

/* Health descriptor parameters offsets in bytes*/
क्रमागत health_desc_param अणु
	HEALTH_DESC_PARAM_LEN			= 0x0,
	HEALTH_DESC_PARAM_TYPE			= 0x1,
	HEALTH_DESC_PARAM_EOL_INFO		= 0x2,
	HEALTH_DESC_PARAM_LIFE_TIME_EST_A	= 0x3,
	HEALTH_DESC_PARAM_LIFE_TIME_EST_B	= 0x4,
पूर्ण;

/* WriteBooster buffer mode */
क्रमागत अणु
	WB_BUF_MODE_LU_DEDICATED	= 0x0,
	WB_BUF_MODE_SHARED		= 0x1,
पूर्ण;

/*
 * Logical Unit Write Protect
 * 00h: LU not ग_लिखो रक्षित
 * 01h: LU ग_लिखो रक्षित when fPowerOnWPEn =1
 * 02h: LU permanently ग_लिखो रक्षित when fPermanentWPEn =1
 */
क्रमागत ufs_lu_wp_type अणु
	UFS_LU_NO_WP		= 0x00,
	UFS_LU_POWER_ON_WP	= 0x01,
	UFS_LU_PERM_WP		= 0x02,
पूर्ण;

/* bActiveICCLevel parameter current units */
क्रमागत अणु
	UFSHCD_न_अंकO_AMP		= 0,
	UFSHCD_MICRO_AMP	= 1,
	UFSHCD_MILI_AMP		= 2,
	UFSHCD_AMP		= 3,
पूर्ण;

/* Possible values क्रम dExtendedUFSFeaturesSupport */
क्रमागत अणु
	UFS_DEV_WRITE_BOOSTER_SUP	= BIT(8),
पूर्ण;

#घोषणा POWER_DESC_MAX_ACTV_ICC_LVLS		16

/* Attribute  bActiveICCLevel parameter bit masks definitions */
#घोषणा ATTR_ICC_LVL_UNIT_OFFSET	14
#घोषणा ATTR_ICC_LVL_UNIT_MASK		(0x3 << ATTR_ICC_LVL_UNIT_OFFSET)
#घोषणा ATTR_ICC_LVL_VALUE_MASK		0x3FF

/* Power descriptor parameters offsets in bytes */
क्रमागत घातer_desc_param_offset अणु
	PWR_DESC_LEN			= 0x0,
	PWR_DESC_TYPE			= 0x1,
	PWR_DESC_ACTIVE_LVLS_VCC_0	= 0x2,
	PWR_DESC_ACTIVE_LVLS_VCCQ_0	= 0x22,
	PWR_DESC_ACTIVE_LVLS_VCCQ2_0	= 0x42,
पूर्ण;

/* Exception event mask values */
क्रमागत अणु
	MASK_EE_STATUS			= 0xFFFF,
	MASK_EE_DYNCAP_EVENT		= BIT(0),
	MASK_EE_SYSPOOL_EVENT		= BIT(1),
	MASK_EE_URGENT_BKOPS		= BIT(2),
	MASK_EE_TOO_HIGH_TEMP		= BIT(3),
	MASK_EE_TOO_LOW_TEMP		= BIT(4),
	MASK_EE_WRITEBOOSTER_EVENT	= BIT(5),
	MASK_EE_PERFORMANCE_THROTTLING	= BIT(6),
पूर्ण;

/* Background operation status */
क्रमागत bkops_status अणु
	BKOPS_STATUS_NO_OP               = 0x0,
	BKOPS_STATUS_NON_CRITICAL        = 0x1,
	BKOPS_STATUS_PERF_IMPACT         = 0x2,
	BKOPS_STATUS_CRITICAL            = 0x3,
	BKOPS_STATUS_MAX		 = BKOPS_STATUS_CRITICAL,
पूर्ण;

/* UTP QUERY Transaction Specअगरic Fields OpCode */
क्रमागत query_opcode अणु
	UPIU_QUERY_OPCODE_NOP		= 0x0,
	UPIU_QUERY_OPCODE_READ_DESC	= 0x1,
	UPIU_QUERY_OPCODE_WRITE_DESC	= 0x2,
	UPIU_QUERY_OPCODE_READ_ATTR	= 0x3,
	UPIU_QUERY_OPCODE_WRITE_ATTR	= 0x4,
	UPIU_QUERY_OPCODE_READ_FLAG	= 0x5,
	UPIU_QUERY_OPCODE_SET_FLAG	= 0x6,
	UPIU_QUERY_OPCODE_CLEAR_FLAG	= 0x7,
	UPIU_QUERY_OPCODE_TOGGLE_FLAG	= 0x8,
पूर्ण;

/* bRefClkFreq attribute values */
क्रमागत ufs_ref_clk_freq अणु
	REF_CLK_FREQ_19_2_MHZ	= 0,
	REF_CLK_FREQ_26_MHZ	= 1,
	REF_CLK_FREQ_38_4_MHZ	= 2,
	REF_CLK_FREQ_52_MHZ	= 3,
	REF_CLK_FREQ_INVAL	= -1,
पूर्ण;

काष्ठा ufs_ref_clk अणु
	अचिन्हित दीर्घ freq_hz;
	क्रमागत ufs_ref_clk_freq val;
पूर्ण;

/* Query response result code */
क्रमागत अणु
	QUERY_RESULT_SUCCESS                    = 0x00,
	QUERY_RESULT_NOT_READABLE               = 0xF6,
	QUERY_RESULT_NOT_WRITEABLE              = 0xF7,
	QUERY_RESULT_ALREADY_WRITTEN            = 0xF8,
	QUERY_RESULT_INVALID_LENGTH             = 0xF9,
	QUERY_RESULT_INVALID_VALUE              = 0xFA,
	QUERY_RESULT_INVALID_SELECTOR           = 0xFB,
	QUERY_RESULT_INVALID_INDEX              = 0xFC,
	QUERY_RESULT_INVALID_IDN                = 0xFD,
	QUERY_RESULT_INVALID_OPCODE             = 0xFE,
	QUERY_RESULT_GENERAL_FAILURE            = 0xFF,
पूर्ण;

/* UTP Transfer Request Command Type (CT) */
क्रमागत अणु
	UPIU_COMMAND_SET_TYPE_SCSI	= 0x0,
	UPIU_COMMAND_SET_TYPE_UFS	= 0x1,
	UPIU_COMMAND_SET_TYPE_QUERY	= 0x2,
पूर्ण;

/* UTP Transfer Request Command Offset */
#घोषणा UPIU_COMMAND_TYPE_OFFSET	28

/* Offset of the response code in the UPIU header */
#घोषणा UPIU_RSP_CODE_OFFSET		8

क्रमागत अणु
	MASK_SCSI_STATUS		= 0xFF,
	MASK_TASK_RESPONSE              = 0xFF00,
	MASK_RSP_UPIU_RESULT            = 0xFFFF,
	MASK_QUERY_DATA_SEG_LEN         = 0xFFFF,
	MASK_RSP_UPIU_DATA_SEG_LEN	= 0xFFFF,
	MASK_RSP_EXCEPTION_EVENT        = 0x10000,
	MASK_TM_SERVICE_RESP		= 0xFF,
	MASK_TM_FUNC			= 0xFF,
पूर्ण;

/* Task management service response */
क्रमागत अणु
	UPIU_TASK_MANAGEMENT_FUNC_COMPL		= 0x00,
	UPIU_TASK_MANAGEMENT_FUNC_NOT_SUPPORTED = 0x04,
	UPIU_TASK_MANAGEMENT_FUNC_SUCCEEDED	= 0x08,
	UPIU_TASK_MANAGEMENT_FUNC_FAILED	= 0x05,
	UPIU_INCORRECT_LOGICAL_UNIT_NO		= 0x09,
पूर्ण;

/* UFS device घातer modes */
क्रमागत ufs_dev_pwr_mode अणु
	UFS_ACTIVE_PWR_MODE	= 1,
	UFS_SLEEP_PWR_MODE	= 2,
	UFS_POWERDOWN_PWR_MODE	= 3,
	UFS_DEEPSLEEP_PWR_MODE	= 4,
पूर्ण;

#घोषणा UFS_WB_BUF_REMAIN_PERCENT(val) ((val) / 10)

/**
 * काष्ठा utp_cmd_rsp - Response UPIU काष्ठाure
 * @residual_transfer_count: Residual transfer count DW-3
 * @reserved: Reserved द्विगुन words DW-4 to DW-7
 * @sense_data_len: Sense data length DW-8 U16
 * @sense_data: Sense data field DW-8 to DW-12
 */
काष्ठा utp_cmd_rsp अणु
	__be32 residual_transfer_count;
	__be32 reserved[4];
	__be16 sense_data_len;
	u8 sense_data[UFS_SENSE_SIZE];
पूर्ण;

/**
 * काष्ठा utp_upiu_rsp - general upiu response काष्ठाure
 * @header: UPIU header काष्ठाure DW-0 to DW-2
 * @sr: fields काष्ठाure क्रम scsi command DW-3 to DW-12
 * @qr: fields काष्ठाure क्रम query request DW-3 to DW-7
 */
काष्ठा utp_upiu_rsp अणु
	काष्ठा utp_upiu_header header;
	जोड़ अणु
		काष्ठा utp_cmd_rsp sr;
		काष्ठा utp_upiu_query qr;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा ufs_query_req - parameters क्रम building a query request
 * @query_func: UPIU header query function
 * @upiu_req: the query request data
 */
काष्ठा ufs_query_req अणु
	u8 query_func;
	काष्ठा utp_upiu_query upiu_req;
पूर्ण;

/**
 * काष्ठा ufs_query_resp - UPIU QUERY
 * @response: device response code
 * @upiu_res: query response data
 */
काष्ठा ufs_query_res अणु
	u8 response;
	काष्ठा utp_upiu_query upiu_res;
पूर्ण;

#घोषणा UFS_VREG_VCC_MIN_UV	   2700000 /* uV */
#घोषणा UFS_VREG_VCC_MAX_UV	   3600000 /* uV */
#घोषणा UFS_VREG_VCC_1P8_MIN_UV    1700000 /* uV */
#घोषणा UFS_VREG_VCC_1P8_MAX_UV    1950000 /* uV */
#घोषणा UFS_VREG_VCCQ_MIN_UV	   1140000 /* uV */
#घोषणा UFS_VREG_VCCQ_MAX_UV	   1260000 /* uV */
#घोषणा UFS_VREG_VCCQ2_MIN_UV	   1700000 /* uV */
#घोषणा UFS_VREG_VCCQ2_MAX_UV	   1950000 /* uV */

/*
 * VCCQ & VCCQ2 current requirement when UFS device is in sleep state
 * and link is in Hibern8 state.
 */
#घोषणा UFS_VREG_LPM_LOAD_UA	1000 /* uA */

काष्ठा ufs_vreg अणु
	काष्ठा regulator *reg;
	स्थिर अक्षर *name;
	bool always_on;
	bool enabled;
	पूर्णांक min_uV;
	पूर्णांक max_uV;
	पूर्णांक max_uA;
पूर्ण;

काष्ठा ufs_vreg_info अणु
	काष्ठा ufs_vreg *vcc;
	काष्ठा ufs_vreg *vccq;
	काष्ठा ufs_vreg *vccq2;
	काष्ठा ufs_vreg *vdd_hba;
पूर्ण;

काष्ठा ufs_dev_info अणु
	bool	f_घातer_on_wp_en;
	/* Keeps inक्रमmation अगर any of the LU is घातer on ग_लिखो रक्षित */
	bool	is_lu_घातer_on_wp;
	/* Maximum number of general LU supported by the UFS device */
	u8	max_lu_supported;
	u16	wmanufacturerid;
	/*UFS device Product Name */
	u8	*model;
	u16	wspecversion;
	u32	clk_gating_रुको_us;

	/* UFS WB related flags */
	bool    wb_enabled;
	bool    wb_buf_flush_enabled;
	u8	wb_dedicated_lu;
	u8      wb_buffer_type;

	bool	b_rpm_dev_flush_capable;
	u8	b_presrv_uspc_en;
पूर्ण;

/*
 * This क्रमागत is used in string mapping in include/trace/events/ufs.h.
 */
क्रमागत ufs_trace_str_t अणु
	UFS_CMD_SEND, UFS_CMD_COMP, UFS_DEV_COMP,
	UFS_QUERY_SEND, UFS_QUERY_COMP, UFS_QUERY_ERR,
	UFS_TM_SEND, UFS_TM_COMP, UFS_TM_ERR
पूर्ण;

/*
 * Transaction Specअगरic Fields (TSF) type in the UPIU package, this क्रमागत is
 * used in include/trace/events/ufs.h क्रम UFS command trace.
 */
क्रमागत ufs_trace_tsf_t अणु
	UFS_TSF_CDB, UFS_TSF_OSF, UFS_TSF_TM_INPUT, UFS_TSF_TM_OUTPUT
पूर्ण;

/**
 * ufs_is_valid_unit_desc_lun - checks अगर the given LUN has a unit descriptor
 * @dev_info: poपूर्णांकer of instance of काष्ठा ufs_dev_info
 * @lun: LU number to check
 * @वापस: true अगर the lun has a matching unit descriptor, false otherwise
 */
अटल अंतरभूत bool ufs_is_valid_unit_desc_lun(काष्ठा ufs_dev_info *dev_info,
		u8 lun, u8 param_offset)
अणु
	अगर (!dev_info || !dev_info->max_lu_supported) अणु
		pr_err("Max General LU supported by UFS isn't initialized\n");
		वापस false;
	पूर्ण
	/* WB is available only क्रम the logical unit from 0 to 7 */
	अगर (param_offset == UNIT_DESC_PARAM_WB_BUF_ALLOC_UNITS)
		वापस lun < UFS_UPIU_MAX_WB_LUN_ID;
	वापस lun == UFS_UPIU_RPMB_WLUN || (lun < dev_info->max_lu_supported);
पूर्ण

#पूर्ण_अगर /* End of Header */
