<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0-only */
/*
 *  QLogic FCoE Offload Driver
 *  Copyright (c) 2016-2018 Cavium Inc.
 */
#अगर_अघोषित __QEDF_HSI__
#घोषणा __QEDF_HSI__
/*
 * Add include to common target
 */
#समावेश <linux/qed/common_hsi.h>

/*
 * Add include to common storage target
 */
#समावेश <linux/qed/storage_common.h>

/*
 * Add include to common fcoe target क्रम both eCore and protocol driver
 */
#समावेश <linux/qed/fcoe_common.h>


/*
 * FCoE CQ element ABTS inक्रमmation
 */
काष्ठा fcoe_abts_info अणु
	u8 r_ctl /* R_CTL in the ABTS response frame */;
	u8 reserved0;
	__le16 rx_id;
	__le32 reserved2[2];
	__le32 fc_payload[3] /* ABTS FC payload response frame */;
पूर्ण;


/*
 * FCoE class type
 */
क्रमागत fcoe_class_type अणु
	FCOE_TASK_CLASS_TYPE_3,
	FCOE_TASK_CLASS_TYPE_2,
	MAX_FCOE_CLASS_TYPE
पूर्ण;


/*
 * FCoE CMDQ element control inक्रमmation
 */
काष्ठा fcoe_cmdqe_control अणु
	__le16 conn_id;
	u8 num_additional_cmdqes;
	u8 cmdType;
	/* true क्रम ABTS request cmdqe. used in Target mode */
#घोषणा FCOE_CMDQE_CONTROL_ABTSREQCMD_MASK  0x1
#घोषणा FCOE_CMDQE_CONTROL_ABTSREQCMD_SHIFT 0
#घोषणा FCOE_CMDQE_CONTROL_RESERVED1_MASK   0x7F
#घोषणा FCOE_CMDQE_CONTROL_RESERVED1_SHIFT  1
	u8 reserved2[4];
पूर्ण;

/*
 * FCoE control + payload CMDQ element
 */
काष्ठा fcoe_cmdqe अणु
	काष्ठा fcoe_cmdqe_control hdr;
	u8 fc_header[24];
	__le32 fcp_cmd_payload[8];
पूर्ण;



/*
 * FCP RSP flags
 */
काष्ठा fcoe_fcp_rsp_flags अणु
	u8 flags;
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RSP_LEN_VALID_MASK  0x1
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RSP_LEN_VALID_SHIFT 0
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_SNS_LEN_VALID_MASK  0x1
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_SNS_LEN_VALID_SHIFT 1
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_OVER_MASK     0x1
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_OVER_SHIFT    2
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_UNDER_MASK    0x1
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_RESID_UNDER_SHIFT   3
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_CONF_REQ_MASK       0x1
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_CONF_REQ_SHIFT      4
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_BIDI_FLAGS_MASK     0x7
#घोषणा FCOE_FCP_RSP_FLAGS_FCP_BIDI_FLAGS_SHIFT    5
पूर्ण;

/*
 * FCoE CQ element response inक्रमmation
 */
काष्ठा fcoe_cqe_rsp_info अणु
	काष्ठा fcoe_fcp_rsp_flags rsp_flags;
	u8 scsi_status_code;
	__le16 retry_delay_समयr;
	__le32 fcp_resid;
	__le32 fcp_sns_len;
	__le32 fcp_rsp_len;
	__le16 rx_id;
	u8 fw_error_flags;
#घोषणा FCOE_CQE_RSP_INFO_FW_UNDERRUN_MASK  0x1 /* FW detected underrun */
#घोषणा FCOE_CQE_RSP_INFO_FW_UNDERRUN_SHIFT 0
#घोषणा FCOE_CQE_RSP_INFO_RESREVED_MASK     0x7F
#घोषणा FCOE_CQE_RSP_INFO_RESREVED_SHIFT    1
	u8 reserved;
	__le32 fw_residual /* Residual bytes calculated by FW */;
पूर्ण;

/*
 * FCoE CQ element Target completion inक्रमmation
 */
काष्ठा fcoe_cqe_target_info अणु
	__le16 rx_id;
	__le16 reserved0;
	__le32 reserved1[5];
पूर्ण;

/*
 * FCoE error/warning reporting entry
 */
काष्ठा fcoe_err_report_entry अणु
	__le32 err_warn_biपंचांगap_lo /* Error biपंचांगap lower 32 bits */;
	__le32 err_warn_biपंचांगap_hi /* Error biपंचांगap higher 32 bits */;
	/* Buffer offset the beginning of the Sequence last transmitted */
	__le32 tx_buf_off;
	/* Buffer offset from the beginning of the Sequence last received */
	__le32 rx_buf_off;
	__le16 rx_id /* RX_ID of the associated task */;
	__le16 reserved1;
	__le32 reserved2;
पूर्ण;

/*
 * FCoE CQ element middle path inक्रमmation
 */
काष्ठा fcoe_cqe_midpath_info अणु
	__le32 data_placement_size;
	__le16 rx_id;
	__le16 reserved0;
	__le32 reserved1[4];
पूर्ण;

/*
 * FCoE CQ element unsolicited inक्रमmation
 */
काष्ठा fcoe_unsolic_info अणु
	/* BD inक्रमmation: Physical address and opaque data */
	काष्ठा scsi_bd bd_info;
	__le16 conn_id /* Connection ID the frame is associated to */;
	__le16 pkt_len /* Packet length */;
	u8 reserved1[4];
पूर्ण;

/*
 * FCoE warning reporting entry
 */
काष्ठा fcoe_warning_report_entry अणु
	/* BD inक्रमmation: Physical address and opaque data */
	काष्ठा scsi_bd bd_info;
	/* Buffer offset the beginning of the Sequence last transmitted */
	__le32 buf_off;
	__le16 rx_id /* RX_ID of the associated task */;
	__le16 reserved1;
पूर्ण;

/*
 * FCoE CQ element inक्रमmation
 */
जोड़ fcoe_cqe_info अणु
	काष्ठा fcoe_cqe_rsp_info rsp_info /* Response completion inक्रमmation */;
	/* Target completion inक्रमmation */
	काष्ठा fcoe_cqe_target_info target_info;
	/* Error completion inक्रमmation */
	काष्ठा fcoe_err_report_entry err_info;
	काष्ठा fcoe_abts_info abts_info /* ABTS completion inक्रमmation */;
	/* Middle path completion inक्रमmation */
	काष्ठा fcoe_cqe_midpath_info midpath_info;
	/* Unsolicited packet completion inक्रमmation */
	काष्ठा fcoe_unsolic_info unsolic_info;
	/* Warning completion inक्रमmation (Rec Tov expiration) */
	काष्ठा fcoe_warning_report_entry warn_info;
पूर्ण;

/*
 * FCoE CQ element
 */
काष्ठा fcoe_cqe अणु
	__le32 cqe_data;
	/* The task identअगरier (OX_ID) to be completed */
#घोषणा FCOE_CQE_TASK_ID_MASK    0xFFFF
#घोषणा FCOE_CQE_TASK_ID_SHIFT   0
	/*
	 * The CQE type: 0x0 Indicating on a pending work request completion.
	 * 0x1 - Indicating on an unsolicited event notअगरication. use क्रमागत
	 * fcoe_cqe_type  (use क्रमागत fcoe_cqe_type)
	 */
#घोषणा FCOE_CQE_CQE_TYPE_MASK   0xF
#घोषणा FCOE_CQE_CQE_TYPE_SHIFT  16
#घोषणा FCOE_CQE_RESERVED0_MASK  0xFFF
#घोषणा FCOE_CQE_RESERVED0_SHIFT 20
	__le16 reserved1;
	__le16 fw_cq_prod;
	जोड़ fcoe_cqe_info cqe_info;
पूर्ण;

/*
 * FCoE CQE type
 */
क्रमागत fcoe_cqe_type अणु
	/* solicited response on a R/W or middle-path SQE */
	FCOE_GOOD_COMPLETION_CQE_TYPE,
	FCOE_UNSOLIC_CQE_TYPE /* unsolicited packet, RQ consumed */,
	FCOE_ERROR_DETECTION_CQE_TYPE /* समयr expiration, validation error */,
	FCOE_WARNING_CQE_TYPE /* rec_tov or rr_tov समयr expiration */,
	FCOE_EXCH_CLEANUP_CQE_TYPE /* task cleanup completed */,
	FCOE_ABTS_CQE_TYPE /* ABTS received and task cleaned */,
	FCOE_DUMMY_CQE_TYPE /* just increment SQ CONS */,
	/* Task was completed wight after sending a pkt to the target */
	FCOE_LOCAL_COMP_CQE_TYPE,
	MAX_FCOE_CQE_TYPE
पूर्ण;

/*
 * FCoE fast path error codes
 */
क्रमागत fcoe_fp_error_warning_code अणु
	FCOE_ERROR_CODE_XFER_OOO_RO /* XFER error codes */,
	FCOE_ERROR_CODE_XFER_RO_NOT_ALIGNED,
	FCOE_ERROR_CODE_XFER_शून्य_BURST_LEN,
	FCOE_ERROR_CODE_XFER_RO_GREATER_THAN_DATA2TRNS,
	FCOE_ERROR_CODE_XFER_INVALID_PAYLOAD_SIZE,
	FCOE_ERROR_CODE_XFER_TASK_TYPE_NOT_WRITE,
	FCOE_ERROR_CODE_XFER_PEND_XFER_SET,
	FCOE_ERROR_CODE_XFER_OPENED_SEQ,
	FCOE_ERROR_CODE_XFER_FCTL,
	FCOE_ERROR_CODE_FCP_RSP_BIDI_FLAGS_SET /* FCP RSP error codes */,
	FCOE_ERROR_CODE_FCP_RSP_INVALID_LENGTH_FIELD,
	FCOE_ERROR_CODE_FCP_RSP_INVALID_SNS_FIELD,
	FCOE_ERROR_CODE_FCP_RSP_INVALID_PAYLOAD_SIZE,
	FCOE_ERROR_CODE_FCP_RSP_PEND_XFER_SET,
	FCOE_ERROR_CODE_FCP_RSP_OPENED_SEQ,
	FCOE_ERROR_CODE_FCP_RSP_FCTL,
	FCOE_ERROR_CODE_FCP_RSP_LAST_SEQ_RESET,
	FCOE_ERROR_CODE_FCP_RSP_CONF_REQ_NOT_SUPPORTED_YET,
	FCOE_ERROR_CODE_DATA_OOO_RO /* FCP DATA error codes */,
	FCOE_ERROR_CODE_DATA_EXCEEDS_DEFINED_MAX_FRAME_SIZE,
	FCOE_ERROR_CODE_DATA_EXCEEDS_DATA2TRNS,
	FCOE_ERROR_CODE_DATA_SOFI3_SEQ_ACTIVE_SET,
	FCOE_ERROR_CODE_DATA_SOFN_SEQ_ACTIVE_RESET,
	FCOE_ERROR_CODE_DATA_खातापूर्णN_END_SEQ_SET,
	FCOE_ERROR_CODE_DATA_खातापूर्णT_END_SEQ_RESET,
	FCOE_ERROR_CODE_DATA_TASK_TYPE_NOT_READ,
	FCOE_ERROR_CODE_DATA_FCTL_INITIATIR,
	FCOE_ERROR_CODE_MIDPATH_INVALID_TYPE /* Middle path error codes */,
	FCOE_ERROR_CODE_MIDPATH_SOFI3_SEQ_ACTIVE_SET,
	FCOE_ERROR_CODE_MIDPATH_SOFN_SEQ_ACTIVE_RESET,
	FCOE_ERROR_CODE_MIDPATH_खातापूर्णN_END_SEQ_SET,
	FCOE_ERROR_CODE_MIDPATH_खातापूर्णT_END_SEQ_RESET,
	FCOE_ERROR_CODE_MIDPATH_REPLY_FCTL,
	FCOE_ERROR_CODE_MIDPATH_INVALID_REPLY,
	FCOE_ERROR_CODE_MIDPATH_ELS_REPLY_RCTL,
	FCOE_ERROR_CODE_COMMON_MIDDLE_FRAME_WITH_PAD /* Common error codes */,
	FCOE_ERROR_CODE_COMMON_SEQ_INIT_IN_TCE,
	FCOE_ERROR_CODE_COMMON_FC_HDR_RX_ID_MISMATCH,
	FCOE_ERROR_CODE_COMMON_INCORRECT_SEQ_CNT,
	FCOE_ERROR_CODE_COMMON_DATA_FC_HDR_FCP_TYPE_MISMATCH,
	FCOE_ERROR_CODE_COMMON_DATA_NO_MORE_SGES,
	FCOE_ERROR_CODE_COMMON_OPTIONAL_FC_HDR,
	FCOE_ERROR_CODE_COMMON_READ_TCE_OX_ID_TOO_BIG,
	FCOE_ERROR_CODE_COMMON_DATA_WAS_NOT_TRANSMITTED,
	FCOE_ERROR_CODE_COMMON_TASK_DDF_RCTL_INFO_FIELD,
	FCOE_ERROR_CODE_COMMON_TASK_INVALID_RCTL,
	FCOE_ERROR_CODE_COMMON_TASK_RCTL_GENERAL_MISMATCH,
	FCOE_ERROR_CODE_E_D_TOV_TIMER_EXPIRATION /* Timer error codes */,
	FCOE_WARNING_CODE_REC_TOV_TIMER_EXPIRATION /* Timer error codes */,
	FCOE_ERROR_CODE_RR_TOV_TIMER_EXPIRATION /* Timer error codes */,
	/* ABTSrsp pckt arrived unexpected */
	FCOE_ERROR_CODE_ABTS_REPLY_UNEXPECTED,
	FCOE_ERROR_CODE_TARGET_MODE_FCP_RSP,
	FCOE_ERROR_CODE_TARGET_MODE_FCP_XFER,
	FCOE_ERROR_CODE_TARGET_MODE_DATA_TASK_TYPE_NOT_WRITE,
	FCOE_ERROR_CODE_DATA_FCTL_TARGET,
	FCOE_ERROR_CODE_TARGET_DATA_SIZE_NO_MATCH_XFER,
	FCOE_ERROR_CODE_TARGET_DIF_CRC_CHECKSUM_ERROR,
	FCOE_ERROR_CODE_TARGET_DIF_REF_TAG_ERROR,
	FCOE_ERROR_CODE_TARGET_DIF_APP_TAG_ERROR,
	MAX_FCOE_FP_ERROR_WARNING_CODE
पूर्ण;


/*
 * FCoE RESPQ element
 */
काष्ठा fcoe_respqe अणु
	__le16 ox_id /* OX_ID that is located in the FCP_RSP FC header */;
	__le16 rx_id /* RX_ID that is located in the FCP_RSP FC header */;
	__le32 additional_info;
/* PARAM that is located in the FCP_RSP FC header */
#घोषणा FCOE_RESPQE_PARAM_MASK            0xFFFFFF
#घोषणा FCOE_RESPQE_PARAM_SHIFT           0
/* Indication whther its Target-स्वतः-rsp mode or not */
#घोषणा FCOE_RESPQE_TARGET_AUTO_RSP_MASK  0xFF
#घोषणा FCOE_RESPQE_TARGET_AUTO_RSP_SHIFT 24
पूर्ण;


/*
 * FCoE slow path error codes
 */
क्रमागत fcoe_sp_error_code अणु
	/* Error codes क्रम Error Reporting in slow path flows */
	FCOE_ERROR_CODE_SLOW_PATH_TOO_MANY_FUNCS,
	FCOE_ERROR_SLOW_PATH_CODE_NO_LICENSE,
	MAX_FCOE_SP_ERROR_CODE
पूर्ण;

/*
 * FCoE task TX state
 */
क्रमागत fcoe_task_tx_state अणु
	/* Initiate state after driver has initialized the task */
	FCOE_TASK_TX_STATE_NORMAL,
	/* Updated by TX path after complete transmitting unsolicited packet */
	FCOE_TASK_TX_STATE_UNSOLICITED_COMPLETED,
	/*
	 * Updated by TX path after start processing the task requesting the
	 * cleanup/पात operation
	 */
	FCOE_TASK_TX_STATE_CLEAN_REQ,
	FCOE_TASK_TX_STATE_ABTS /* Updated by TX path during पात procedure */,
	/* Updated by TX path during exchange cleanup procedure */
	FCOE_TASK_TX_STATE_EXCLEANUP,
	/*
	 * Updated by TX path during exchange cleanup continuation task
	 * procedure
	 */
	FCOE_TASK_TX_STATE_EXCLEANUP_TARGET_WRITE_CONT,
	/* Updated by TX path during exchange cleanup first xfer procedure */
	FCOE_TASK_TX_STATE_EXCLEANUP_TARGET_WRITE,
	/* Updated by TX path during exchange cleanup पढ़ो task in Target */
	FCOE_TASK_TX_STATE_EXCLEANUP_TARGET_READ_OR_RSP,
	/* Updated by TX path during target exchange cleanup procedure */
	FCOE_TASK_TX_STATE_EXCLEANUP_TARGET_WRITE_LAST_CYCLE,
	/* Updated by TX path during sequence recovery procedure */
	FCOE_TASK_TX_STATE_SEQRECOVERY,
	MAX_FCOE_TASK_TX_STATE
पूर्ण;

#पूर्ण_अगर /* __QEDF_HSI__ */
