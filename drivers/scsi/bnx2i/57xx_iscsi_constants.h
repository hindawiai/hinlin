<शैली गुरु>
/* 57xx_iscsi_स्थिरants.h: QLogic NetXtreme II iSCSI HSI
 *
 * Copyright (c) 2006 - 2013 Broadcom Corporation
 * Copyright (c) 2014, QLogic Corporation
 *
 * This program is मुक्त software; you can redistribute it and/or modअगरy
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation.
 *
 * Written by: Anil Veerabhadrappa (anilgv@broadcom.com)
 * Previously Maपूर्णांकained by: Eddie Wai (eddie.wai@broadcom.com)
 * Maपूर्णांकained by: QLogic-Storage-Upstream@qlogic.com
 */
#अगर_अघोषित __57XX_ISCSI_CONSTANTS_H_
#घोषणा __57XX_ISCSI_CONSTANTS_H_

/**
* This file defines HSI स्थिरants क्रम the iSCSI flows
*/

/* iSCSI request op codes */
#घोषणा ISCSI_OPCODE_CLEANUP_REQUEST    (7)

/* iSCSI response/messages op codes */
#घोषणा ISCSI_OPCODE_CLEANUP_RESPONSE 		(0x27)
#घोषणा ISCSI_OPCODE_NOPOUT_LOCAL_COMPLETION    (0)

/* iSCSI task types */
#घोषणा ISCSI_TASK_TYPE_READ    (0)
#घोषणा ISCSI_TASK_TYPE_WRITE   (1)
#घोषणा ISCSI_TASK_TYPE_MPATH   (2)

/* initial CQ sequence numbers */
#घोषणा ISCSI_INITIAL_SN    (1)

/* KWQ (kernel work queue) layer codes */
#घोषणा ISCSI_KWQE_LAYER_CODE   (6)

/* KWQ (kernel work queue) request op codes */
#घोषणा ISCSI_KWQE_OPCODE_OFFLOAD_CONN1 (0)
#घोषणा ISCSI_KWQE_OPCODE_OFFLOAD_CONN2 (1)
#घोषणा ISCSI_KWQE_OPCODE_UPDATE_CONN   (2)
#घोषणा ISCSI_KWQE_OPCODE_DESTROY_CONN  (3)
#घोषणा ISCSI_KWQE_OPCODE_INIT1         (4)
#घोषणा ISCSI_KWQE_OPCODE_INIT2         (5)

/* KCQ (kernel completion queue) response op codes */
#घोषणा ISCSI_KCQE_OPCODE_OFFLOAD_CONN  (0x10)
#घोषणा ISCSI_KCQE_OPCODE_UPDATE_CONN   (0x12)
#घोषणा ISCSI_KCQE_OPCODE_DESTROY_CONN  (0x13)
#घोषणा ISCSI_KCQE_OPCODE_INIT          (0x14)
#घोषणा ISCSI_KCQE_OPCODE_FW_CLEAN_TASK	(0x15)
#घोषणा ISCSI_KCQE_OPCODE_TCP_RESET     (0x16)
#घोषणा ISCSI_KCQE_OPCODE_TCP_SYN       (0x17)
#घोषणा ISCSI_KCQE_OPCODE_TCP_FIN       (0X18)
#घोषणा ISCSI_KCQE_OPCODE_TCP_ERROR     (0x19)
#घोषणा ISCSI_KCQE_OPCODE_CQ_EVENT_NOTIFICATION (0x20)
#घोषणा ISCSI_KCQE_OPCODE_ISCSI_ERROR   (0x21)

/* KCQ (kernel completion queue) completion status */
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_SUCCESS                            (0x0)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_INVALID_OPCODE                     (0x1)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_CTX_ALLOC_FAILURE                  (0x2)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_CTX_FREE_FAILURE                   (0x3)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_NIC_ERROR                          (0x4)

#घोषणा ISCSI_KCQE_COMPLETION_STATUS_HDR_DIG_ERR                        (0x5)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_DATA_DIG_ERR                       (0x6)

#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_UNEXPECTED_OPCODE     (0xa)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_OPCODE                (0xb)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_AHS_LEN               (0xc)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_ITT                   (0xd)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_STATSN                (0xe)

/* Response */
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_EXP_DATASN            (0xf)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_PEND_R2T              (0x10)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DATA_SEG_LEN_IS_ZERO  (0x2c)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DATA_SEG_LEN_TOO_BIG  (0x2d)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_0                 (0x11)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_1                 (0x12)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_2                 (0x13)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_3                 (0x14)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_4                 (0x15)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_5                 (0x16)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_O_U_6                 (0x17)

/* Data-In */
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_REMAIN_RCV_LEN        (0x18)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_MAX_RCV_PDU_LEN       (0x19)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_F_BIT_ZERO            (0x1a)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_TTT_NOT_RSRV          (0x1b)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DATASN                (0x1c)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_REMAIN_BURST_LEN      (0x1d)

/* R2T */
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_BUFFER_OFF            (0x1f)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_LUN                   (0x20)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_R2TSN                 (0x21)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DESIRED_DATA_TRNS_LEN_0 (0x22)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DESIRED_DATA_TRNS_LEN_1 (0x23)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_PEND_R2T_EXCEED       (0x24)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_TTT_IS_RSRV           (0x25)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_MAX_BURST_LEN         (0x26)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_DATA_SEG_LEN_NOT_ZERO (0x27)

/* TMF */
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_REJECT_PDU_LEN        (0x28)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_ASYNC_PDU_LEN         (0x29)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_NOPIN_PDU_LEN         (0x2a)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PROTOCOL_ERR_PEND_R2T_IN_CLEANUP   (0x2b)

/* IP/TCP processing errors: */
#घोषणा ISCI_KCQE_COMPLETION_STATUS_TCP_ERROR_IP_FRAGMENT               (0x40)
#घोषणा ISCI_KCQE_COMPLETION_STATUS_TCP_ERROR_IP_OPTIONS                (0x41)
#घोषणा ISCI_KCQE_COMPLETION_STATUS_TCP_ERROR_URGENT_FLAG               (0x42)
#घोषणा ISCI_KCQE_COMPLETION_STATUS_TCP_ERROR_MAX_RTRANS                (0x43)

/* iSCSI licensing errors */
/* general iSCSI license not installed */
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_ISCSI_NOT_SUPPORTED                (0x50)
/* additional LOM specअगरic iSCSI license not installed */
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_LOM_ISCSI_NOT_ENABLED              (0x51)

#घोषणा ISCSI_KCQE_COMPLETION_STATUS_CID_BUSY				(0x80)
#घोषणा ISCSI_KCQE_COMPLETION_STATUS_PARITY_ERR                         (0x81)

/* SQ/RQ/CQ DB काष्ठाure sizes */
#घोषणा ISCSI_SQ_DB_SIZE    (16)
#घोषणा ISCSI_RQ_DB_SIZE    (64)
#घोषणा ISCSI_CQ_DB_SIZE    (80)

#घोषणा ISCSI_SQN_TO_NOTIFY_NOT_VALID                                   0xFFFF

/* Page size codes (क्रम flags field in connection offload request) */
#घोषणा ISCSI_PAGE_SIZE_256     (0)
#घोषणा ISCSI_PAGE_SIZE_512     (1)
#घोषणा ISCSI_PAGE_SIZE_1K      (2)
#घोषणा ISCSI_PAGE_SIZE_2K      (3)
#घोषणा ISCSI_PAGE_SIZE_4K      (4)
#घोषणा ISCSI_PAGE_SIZE_8K      (5)
#घोषणा ISCSI_PAGE_SIZE_16K     (6)
#घोषणा ISCSI_PAGE_SIZE_32K     (7)
#घोषणा ISCSI_PAGE_SIZE_64K     (8)
#घोषणा ISCSI_PAGE_SIZE_128K    (9)
#घोषणा ISCSI_PAGE_SIZE_256K    (10)
#घोषणा ISCSI_PAGE_SIZE_512K    (11)
#घोषणा ISCSI_PAGE_SIZE_1M      (12)
#घोषणा ISCSI_PAGE_SIZE_2M      (13)
#घोषणा ISCSI_PAGE_SIZE_4M      (14)
#घोषणा ISCSI_PAGE_SIZE_8M      (15)

/* Iscsi PDU related defines */
#घोषणा ISCSI_HEADER_SIZE   (48)
#घोषणा ISCSI_DIGEST_SHIFT  (2)
#घोषणा ISCSI_DIGEST_SIZE   (4)

#घोषणा B577XX_ISCSI_CONNECTION_TYPE    3

#पूर्ण_अगर /*__57XX_ISCSI_CONSTANTS_H_ */
