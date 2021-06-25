<शैली गुरु>
/* bnx2fc_स्थिरants.h: QLogic Linux FCoE offload driver.
 * Handles operations such as session offload/upload etc, and manages
 * session resources such as connection id and qp resources.
 *
 * Copyright (c) 2008-2013 Broadcom Corporation
 * Copyright (c) 2014-2016 QLogic Corporation
 * Copyright (c) 2016-2017 Cavium Inc.
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 */

#अगर_अघोषित __BNX2FC_CONSTANTS_H_
#घोषणा __BNX2FC_CONSTANTS_H_

/**
 * This file defines HSI स्थिरants क्रम the FCoE flows
 */

/* Current FCoE HSI version number composed of two fields (16 bit) */
/* Implies on a change broken previous HSI */
#घोषणा FCOE_HSI_MAJOR_VERSION (2)
/* Implies on a change which करोes not broken previous HSI */
#घोषणा FCOE_HSI_MINOR_VERSION (1)

/* KWQ/KCQ FCoE layer code */
#घोषणा FCOE_KWQE_LAYER_CODE   (7)

/* KWQ (kernel work queue) request op codes */
#घोषणा FCOE_KWQE_OPCODE_INIT1			(0)
#घोषणा FCOE_KWQE_OPCODE_INIT2			(1)
#घोषणा FCOE_KWQE_OPCODE_INIT3			(2)
#घोषणा FCOE_KWQE_OPCODE_OFFLOAD_CONN1	(3)
#घोषणा FCOE_KWQE_OPCODE_OFFLOAD_CONN2	(4)
#घोषणा FCOE_KWQE_OPCODE_OFFLOAD_CONN3	(5)
#घोषणा FCOE_KWQE_OPCODE_OFFLOAD_CONN4	(6)
#घोषणा FCOE_KWQE_OPCODE_ENABLE_CONN	(7)
#घोषणा FCOE_KWQE_OPCODE_DISABLE_CONN	(8)
#घोषणा FCOE_KWQE_OPCODE_DESTROY_CONN	(9)
#घोषणा FCOE_KWQE_OPCODE_DESTROY		(10)
#घोषणा FCOE_KWQE_OPCODE_STAT			(11)

/* KCQ (kernel completion queue) response op codes */
#घोषणा FCOE_KCQE_OPCODE_INIT_FUNC				(0x10)
#घोषणा FCOE_KCQE_OPCODE_DESTROY_FUNC			(0x11)
#घोषणा FCOE_KCQE_OPCODE_STAT_FUNC				(0x12)
#घोषणा FCOE_KCQE_OPCODE_OFFLOAD_CONN			(0x15)
#घोषणा FCOE_KCQE_OPCODE_ENABLE_CONN			(0x16)
#घोषणा FCOE_KCQE_OPCODE_DISABLE_CONN			(0x17)
#घोषणा FCOE_KCQE_OPCODE_DESTROY_CONN			(0x18)
#घोषणा FCOE_KCQE_OPCODE_CQ_EVENT_NOTIFICATION  (0x20)
#घोषणा FCOE_KCQE_OPCODE_FCOE_ERROR				(0x21)

/* KCQ (kernel completion queue) completion status */
#घोषणा FCOE_KCQE_COMPLETION_STATUS_SUCCESS				(0x0)
#घोषणा FCOE_KCQE_COMPLETION_STATUS_ERROR				(0x1)
#घोषणा FCOE_KCQE_COMPLETION_STATUS_INVALID_OPCODE		(0x2)
#घोषणा FCOE_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAILURE	(0x3)
#घोषणा FCOE_KCQE_COMPLETION_STATUS_CTX_FREE_FAILURE	(0x4)
#घोषणा FCOE_KCQE_COMPLETION_STATUS_NIC_ERROR			(0x5)
#घोषणा FCOE_KCQE_COMPLETION_STATUS_WRONG_HSI_VERSION   (0x6)
#घोषणा FCOE_KCQE_COMPLETION_STATUS_PARITY_ERROR	(0x81)

/* CQE type */
#घोषणा FCOE_PENDING_CQE_TYPE			0
#घोषणा FCOE_UNSOLIC_CQE_TYPE			1

/* Unsolicited CQE type */
#घोषणा FCOE_UNSOLICITED_FRAME_CQE_TYPE			0
#घोषणा FCOE_ERROR_DETECTION_CQE_TYPE			1
#घोषणा FCOE_WARNING_DETECTION_CQE_TYPE			2

/* E_D_TOV समयr resolution in ms */
#घोषणा FCOE_E_D_TOV_TIMER_RESOLUTION_MS (20)

/* E_D_TOV समयr resolution क्रम SDM (4 micro) */
#घोषणा FCOE_E_D_TOV_SDM_TIMER_RESOLUTION				\
	(FCOE_E_D_TOV_TIMER_RESOLUTION_MS * 1000 / 4)

/* REC समयr resolution in ms */
#घोषणा FCOE_REC_TIMER_RESOLUTION_MS (20)

/* REC समयr resolution क्रम SDM (4 micro) */
#घोषणा FCOE_REC_SDM_TIMER_RESOLUTION (FCOE_REC_TIMER_RESOLUTION_MS * 1000 / 4)

/* E_D_TOV समयr शेष wraparound value (2 sec) in 20 ms resolution */
#घोषणा FCOE_E_D_TOV_DEFAULT_WRAPAROUND_VAL			\
			(2000 / FCOE_E_D_TOV_TIMER_RESOLUTION_MS)

/* REC_TOV समयr शेष wraparound value (3 sec) in 20 ms resolution */
#घोषणा FCOE_REC_TOV_DEFAULT_WRAPAROUND_VAL			\
			(3000 / FCOE_REC_TIMER_RESOLUTION_MS)

#घोषणा FCOE_NUM_OF_TIMER_TASKS  (8 * 1024)

#घोषणा FCOE_NUM_OF_CACHED_TASKS_TIMER (8)

/* Task context स्थिरants */
/******** Remove FCP_CMD ग_लिखो tce sleep ***********************/
/* In हाल समयr services are required then shall be updated by Xstorm after
 * start processing the task. In हाल no समयr facilities are required then the
 * driver would initialize the state to this value
 *
#घोषणा	FCOE_TASK_TX_STATE_NORMAL				0
 * After driver has initialize the task in हाल समयr services required *
#घोषणा	FCOE_TASK_TX_STATE_INIT					1
******** Remove FCP_CMD ग_लिखो tce sleep ***********************/
/* After driver has initialize the task in हाल समयr services required */
#घोषणा	FCOE_TASK_TX_STATE_INIT					0
/* In हाल समयr services are required then shall be updated by Xstorm after
 * start processing the task. In हाल no समयr facilities are required then the
 * driver would initialize the state to this value
 */
#घोषणा	FCOE_TASK_TX_STATE_NORMAL				1
/* Task is under पात procedure. Updated in order to stop processing of
 * pending WQEs on this task
 */
#घोषणा	FCOE_TASK_TX_STATE_ABORT				2
/* For E_D_T_TOV समयr expiration in Xstorm (Class 2 only) */
#घोषणा	FCOE_TASK_TX_STATE_ERROR				3
/* For REC_TOV समयr expiration indication received from Xstorm */
#घोषणा	FCOE_TASK_TX_STATE_WARNING				4
/* For completed unsolicited task */
#घोषणा	FCOE_TASK_TX_STATE_UNSOLICITED_COMPLETED		5
/* For exchange cleanup request task */
#घोषणा	FCOE_TASK_TX_STATE_EXCHANGE_CLEANUP			6
/* For sequence cleanup request task */
#घोषणा	FCOE_TASK_TX_STATE_SEQUENCE_CLEANUP			7
/* For completion the ABTS task. */
#घोषणा	FCOE_TASK_TX_STATE_ABTS_TX				8

#घोषणा	FCOE_TASK_RX_STATE_NORMAL				0
#घोषणा	FCOE_TASK_RX_STATE_COMPLETED				1
/* Obsolete: Intermediate completion (middle path with local completion) */
#घोषणा	FCOE_TASK_RX_STATE_INTER_COMP				2
/* For REC_TOV समयr expiration indication received from Xstorm */
#घोषणा	FCOE_TASK_RX_STATE_WARNING				3
/* For E_D_T_TOV समयr expiration in Ustorm */
#घोषणा	FCOE_TASK_RX_STATE_ERROR				4
/* FW only: First visit at rx-path, part of the abts round trip */
#घोषणा	FCOE_TASK_RX_STATE_ABTS_IN_PROCESS			5
/* FW only: Second visit at rx-path, after ABTS frame transmitted */
#घोषणा	FCOE_TASK_RX_STATE_ABTS_TRANSMITTED			6
/* Special completion indication in हाल of task was पातed. */
#घोषणा FCOE_TASK_RX_STATE_ABTS_COMPLETED			7
/* FW only: First visit at rx-path, part of the cleanup round trip */
#घोषणा	FCOE_TASK_RX_STATE_EXCHANGE_CLEANUP_IN_PROCESS		8
/* FW only: Special completion indication in हाल of task was cleaned. */
#घोषणा FCOE_TASK_RX_STATE_EXCHANGE_CLEANUP_COMPLETED		9
/* Not in used: Special completion indication (in task requested the exchange
 * cleanup) in हाल cleaned task is in non-valid.
 */
#घोषणा FCOE_TASK_RX_STATE_ABORT_CLEANUP_COMPLETED		10
/* Special completion indication (in task requested the sequence cleanup) in
 * हाल cleaned task was alपढ़ोy वापसed to normal.
 */
#घोषणा FCOE_TASK_RX_STATE_IGNORED_SEQUENCE_CLEANUP		11


#घोषणा	FCOE_TASK_TYPE_WRITE			0
#घोषणा	FCOE_TASK_TYPE_READ				1
#घोषणा	FCOE_TASK_TYPE_MIDPATH			2
#घोषणा	FCOE_TASK_TYPE_UNSOLICITED		3
#घोषणा	FCOE_TASK_TYPE_ABTS				4
#घोषणा	FCOE_TASK_TYPE_EXCHANGE_CLEANUP	5
#घोषणा	FCOE_TASK_TYPE_SEQUENCE_CLEANUP	6

#घोषणा FCOE_TASK_DEV_TYPE_DISK			0
#घोषणा FCOE_TASK_DEV_TYPE_TAPE			1

#घोषणा FCOE_TASK_CLASS_TYPE_3			0
#घोषणा FCOE_TASK_CLASS_TYPE_2			1

/* FCoE/FC packet fields  */
#घोषणा	FCOE_ETH_TYPE					0x8906

/* FCoE maximum elements in hash table */
#घोषणा FCOE_MAX_ELEMENTS_IN_HASH_TABLE_ROW	8

/* FCoE half of the elements in hash table */
#घोषणा FCOE_HALF_ELEMENTS_IN_HASH_TABLE_ROW			\
			(FCOE_MAX_ELEMENTS_IN_HASH_TABLE_ROW / 2)

/* FcoE number of cached T2 entries */
#घोषणा T_FCOE_NUMBER_OF_CACHED_T2_ENTRIES (4)

/* FCoE maximum elements in hash table */
#घोषणा FCOE_HASH_TBL_CHUNK_SIZE	16384

/* Everest FCoE connection type */
#घोषणा B577XX_FCOE_CONNECTION_TYPE		4

/* FCoE number of rows (in log). This number derives
 * from the maximum connections supported which is 2048.
 * TBA: Need a dअगरferent स्थिरant क्रम E2
 */
#घोषणा FCOE_MAX_NUM_SESSIONS_LOG		11

#घोषणा FC_ABTS_REPLY_MAX_PAYLOAD_LEN	12

/* Error codes क्रम Error Reporting in slow path flows */
#घोषणा FCOE_SLOW_PATH_ERROR_CODE_TOO_MANY_FUNCS			0
#घोषणा FCOE_SLOW_PATH_ERROR_CODE_NO_LICENSE				1

/* Error codes क्रम Error Reporting in fast path flows
 * XFER error codes
 */
#घोषणा FCOE_ERROR_CODE_XFER_OOO_RO					0
#घोषणा FCOE_ERROR_CODE_XFER_RO_NOT_ALIGNED				1
#घोषणा FCOE_ERROR_CODE_XFER_शून्य_BURST_LEN				2
#घोषणा FCOE_ERROR_CODE_XFER_RO_GREATER_THAN_DATA2TRNS			3
#घोषणा FCOE_ERROR_CODE_XFER_INVALID_PAYLOAD_SIZE			4
#घोषणा FCOE_ERROR_CODE_XFER_TASK_TYPE_NOT_WRITE			5
#घोषणा FCOE_ERROR_CODE_XFER_PEND_XFER_SET				6
#घोषणा FCOE_ERROR_CODE_XFER_OPENED_SEQ					7
#घोषणा FCOE_ERROR_CODE_XFER_FCTL					8

/* FCP RSP error codes */
#घोषणा FCOE_ERROR_CODE_FCP_RSP_BIDI_FLAGS_SET				9
#घोषणा FCOE_ERROR_CODE_FCP_RSP_UNDERFLOW				10
#घोषणा FCOE_ERROR_CODE_FCP_RSP_OVERFLOW				11
#घोषणा FCOE_ERROR_CODE_FCP_RSP_INVALID_LENGTH_FIELD			12
#घोषणा FCOE_ERROR_CODE_FCP_RSP_INVALID_SNS_FIELD			13
#घोषणा FCOE_ERROR_CODE_FCP_RSP_INVALID_PAYLOAD_SIZE			14
#घोषणा FCOE_ERROR_CODE_FCP_RSP_PEND_XFER_SET				15
#घोषणा FCOE_ERROR_CODE_FCP_RSP_OPENED_SEQ				16
#घोषणा FCOE_ERROR_CODE_FCP_RSP_FCTL					17
#घोषणा FCOE_ERROR_CODE_FCP_RSP_LAST_SEQ_RESET				18
#घोषणा FCOE_ERROR_CODE_FCP_RSP_CONF_REQ_NOT_SUPPORTED_YET		19

/* FCP DATA error codes */
#घोषणा FCOE_ERROR_CODE_DATA_OOO_RO					20
#घोषणा FCOE_ERROR_CODE_DATA_EXCEEDS_DEFINED_MAX_FRAME_SIZE		21
#घोषणा FCOE_ERROR_CODE_DATA_EXCEEDS_DATA2TRNS				22
#घोषणा FCOE_ERROR_CODE_DATA_SOFI3_SEQ_ACTIVE_SET			23
#घोषणा FCOE_ERROR_CODE_DATA_SOFN_SEQ_ACTIVE_RESET			24
#घोषणा FCOE_ERROR_CODE_DATA_खातापूर्णN_END_SEQ_SET				25
#घोषणा FCOE_ERROR_CODE_DATA_खातापूर्णT_END_SEQ_RESET				26
#घोषणा FCOE_ERROR_CODE_DATA_TASK_TYPE_NOT_READ				27
#घोषणा FCOE_ERROR_CODE_DATA_FCTL					28

/* Middle path error codes */
#घोषणा FCOE_ERROR_CODE_MIDPATH_INVALID_TYPE				29
#घोषणा FCOE_ERROR_CODE_MIDPATH_SOFI3_SEQ_ACTIVE_SET			30
#घोषणा FCOE_ERROR_CODE_MIDPATH_SOFN_SEQ_ACTIVE_RESET			31
#घोषणा FCOE_ERROR_CODE_MIDPATH_खातापूर्णN_END_SEQ_SET			32
#घोषणा FCOE_ERROR_CODE_MIDPATH_खातापूर्णT_END_SEQ_RESET			33
#घोषणा FCOE_ERROR_CODE_MIDPATH_REPLY_FCTL				34
#घोषणा FCOE_ERROR_CODE_MIDPATH_INVALID_REPLY				35
#घोषणा FCOE_ERROR_CODE_MIDPATH_ELS_REPLY_RCTL				36

/* ABTS error codes */
#घोषणा FCOE_ERROR_CODE_ABTS_REPLY_F_CTL				37
#घोषणा FCOE_ERROR_CODE_ABTS_REPLY_DDF_RCTL_FIELD			38
#घोषणा FCOE_ERROR_CODE_ABTS_REPLY_INVALID_BLS_RCTL			39
#घोषणा FCOE_ERROR_CODE_ABTS_REPLY_INVALID_RCTL				40
#घोषणा FCOE_ERROR_CODE_ABTS_REPLY_RCTL_GENERAL_MISMATCH		41

/* Common error codes */
#घोषणा FCOE_ERROR_CODE_COMMON_MIDDLE_FRAME_WITH_PAD			42
#घोषणा FCOE_ERROR_CODE_COMMON_SEQ_INIT_IN_TCE				43
#घोषणा FCOE_ERROR_CODE_COMMON_FC_HDR_RX_ID_MISMATCH			44
#घोषणा FCOE_ERROR_CODE_COMMON_INCORRECT_SEQ_CNT			45
#घोषणा FCOE_ERROR_CODE_COMMON_DATA_FC_HDR_FCP_TYPE_MISMATCH		46
#घोषणा FCOE_ERROR_CODE_COMMON_DATA_NO_MORE_SGES			47
#घोषणा FCOE_ERROR_CODE_COMMON_OPTIONAL_FC_HDR				48
#घोषणा FCOE_ERROR_CODE_COMMON_READ_TCE_OX_ID_TOO_BIG			49
#घोषणा FCOE_ERROR_CODE_COMMON_DATA_WAS_NOT_TRANSMITTED			50

/* Unsolicited Rx error codes */
#घोषणा FCOE_ERROR_CODE_UNSOLICITED_TYPE_NOT_ELS			51
#घोषणा FCOE_ERROR_CODE_UNSOLICITED_TYPE_NOT_BLS			52
#घोषणा FCOE_ERROR_CODE_UNSOLICITED_FCTL_ELS				53
#घोषणा FCOE_ERROR_CODE_UNSOLICITED_FCTL_BLS				54
#घोषणा FCOE_ERROR_CODE_UNSOLICITED_R_CTL				55

#घोषणा FCOE_ERROR_CODE_RW_TASK_DDF_RCTL_INFO_FIELD			56
#घोषणा FCOE_ERROR_CODE_RW_TASK_INVALID_RCTL				57
#घोषणा FCOE_ERROR_CODE_RW_TASK_RCTL_GENERAL_MISMATCH			58

/* Timer error codes */
#घोषणा FCOE_ERROR_CODE_E_D_TOV_TIMER_EXPIRATION			60
#घोषणा FCOE_ERROR_CODE_REC_TOV_TIMER_EXPIRATION			61


#पूर्ण_अगर /* BNX2FC_CONSTANTS_H_ */
