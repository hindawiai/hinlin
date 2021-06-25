<शैली गुरु>
/*
 * Copyright (c) 2016 Hisilicon Limited.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *        copyright notice, this list of conditions and the following
 *        disclaimer in the करोcumentation and/or other materials
 *        provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#अगर_अघोषित _HNS_ROCE_HW_V1_H
#घोषणा _HNS_ROCE_HW_V1_H

#घोषणा CQ_STATE_VALID					2

#घोषणा HNS_ROCE_V1_MAX_PD_NUM				0x8000
#घोषणा HNS_ROCE_V1_MAX_CQ_NUM				0x10000
#घोषणा HNS_ROCE_V1_MAX_CQE_NUM				0x8000

#घोषणा HNS_ROCE_V1_MAX_QP_NUM				0x40000
#घोषणा HNS_ROCE_V1_MAX_WQE_NUM				0x4000

#घोषणा HNS_ROCE_V1_MAX_MTPT_NUM			0x80000

#घोषणा HNS_ROCE_V1_MAX_MTT_SEGS			0x100000

#घोषणा HNS_ROCE_V1_MAX_QP_INIT_RDMA			128
#घोषणा HNS_ROCE_V1_MAX_QP_DEST_RDMA			128

#घोषणा HNS_ROCE_V1_MAX_SQ_DESC_SZ			64
#घोषणा HNS_ROCE_V1_MAX_RQ_DESC_SZ			64
#घोषणा HNS_ROCE_V1_SG_NUM				2
#घोषणा HNS_ROCE_V1_INLINE_SIZE				32

#घोषणा HNS_ROCE_V1_UAR_NUM				256
#घोषणा HNS_ROCE_V1_PHY_UAR_NUM				8

#घोषणा HNS_ROCE_V1_GID_NUM				16
#घोषणा HNS_ROCE_V1_RESV_QP				8

#घोषणा HNS_ROCE_V1_MAX_IRQ_NUM				34
#घोषणा HNS_ROCE_V1_COMP_VEC_NUM			32
#घोषणा HNS_ROCE_V1_AEQE_VEC_NUM			1
#घोषणा HNS_ROCE_V1_ABNORMAL_VEC_NUM			1

#घोषणा HNS_ROCE_V1_COMP_EQE_NUM			0x8000
#घोषणा HNS_ROCE_V1_ASYNC_EQE_NUM			0x400

#घोषणा HNS_ROCE_V1_QPC_SIZE				256
#घोषणा HNS_ROCE_V1_IRRL_ENTRY_SIZE			8
#घोषणा HNS_ROCE_V1_CQC_ENTRY_SIZE			64
#घोषणा HNS_ROCE_V1_MTPT_ENTRY_SIZE			64
#घोषणा HNS_ROCE_V1_MTT_ENTRY_SIZE			64

#घोषणा HNS_ROCE_V1_CQE_SIZE				32
#घोषणा HNS_ROCE_V1_PAGE_SIZE_SUPPORT			0xFFFFF000

#घोषणा HNS_ROCE_V1_TABLE_CHUNK_SIZE			(1 << 17)

#घोषणा HNS_ROCE_V1_EXT_RAQ_WF				8
#घोषणा HNS_ROCE_V1_RAQ_ENTRY				64
#घोषणा HNS_ROCE_V1_RAQ_DEPTH				32768
#घोषणा HNS_ROCE_V1_RAQ_SIZE	(HNS_ROCE_V1_RAQ_ENTRY * HNS_ROCE_V1_RAQ_DEPTH)

#घोषणा HNS_ROCE_V1_SDB_DEPTH				0x400
#घोषणा HNS_ROCE_V1_ODB_DEPTH				0x400

#घोषणा HNS_ROCE_V1_DB_RSVD				0x80

#घोषणा HNS_ROCE_V1_SDB_ALEPT				HNS_ROCE_V1_DB_RSVD
#घोषणा HNS_ROCE_V1_SDB_ALFUL	(HNS_ROCE_V1_SDB_DEPTH - HNS_ROCE_V1_DB_RSVD)
#घोषणा HNS_ROCE_V1_ODB_ALEPT				HNS_ROCE_V1_DB_RSVD
#घोषणा HNS_ROCE_V1_ODB_ALFUL	(HNS_ROCE_V1_ODB_DEPTH - HNS_ROCE_V1_DB_RSVD)

#घोषणा HNS_ROCE_V1_EXT_SDB_DEPTH			0x4000
#घोषणा HNS_ROCE_V1_EXT_ODB_DEPTH			0x4000
#घोषणा HNS_ROCE_V1_EXT_SDB_ENTRY			16
#घोषणा HNS_ROCE_V1_EXT_ODB_ENTRY			16
#घोषणा HNS_ROCE_V1_EXT_SDB_SIZE  \
	(HNS_ROCE_V1_EXT_SDB_DEPTH * HNS_ROCE_V1_EXT_SDB_ENTRY)
#घोषणा HNS_ROCE_V1_EXT_ODB_SIZE  \
	(HNS_ROCE_V1_EXT_ODB_DEPTH * HNS_ROCE_V1_EXT_ODB_ENTRY)

#घोषणा HNS_ROCE_V1_EXT_SDB_ALEPT			HNS_ROCE_V1_DB_RSVD
#घोषणा HNS_ROCE_V1_EXT_SDB_ALFUL  \
	(HNS_ROCE_V1_EXT_SDB_DEPTH - HNS_ROCE_V1_DB_RSVD)
#घोषणा HNS_ROCE_V1_EXT_ODB_ALEPT			HNS_ROCE_V1_DB_RSVD
#घोषणा HNS_ROCE_V1_EXT_ODB_ALFUL	\
	(HNS_ROCE_V1_EXT_ODB_DEPTH - HNS_ROCE_V1_DB_RSVD)

#घोषणा HNS_ROCE_V1_FREE_MR_TIMEOUT_MSECS		50000
#घोषणा HNS_ROCE_V1_RECREATE_LP_QP_TIMEOUT_MSECS	10000
#घोषणा HNS_ROCE_V1_FREE_MR_WAIT_VALUE			5
#घोषणा HNS_ROCE_V1_RECREATE_LP_QP_WAIT_VALUE		20

#घोषणा HNS_ROCE_BT_RSV_BUF_SIZE			(1 << 17)

#घोषणा HNS_ROCE_V1_TPTR_ENTRY_SIZE			2
#घोषणा HNS_ROCE_V1_TPTR_BUF_SIZE	\
	(HNS_ROCE_V1_TPTR_ENTRY_SIZE * HNS_ROCE_V1_MAX_CQ_NUM)

#घोषणा HNS_ROCE_ODB_POLL_MODE				0

#घोषणा HNS_ROCE_SDB_NORMAL_MODE			0
#घोषणा HNS_ROCE_SDB_EXTEND_MODE			1

#घोषणा HNS_ROCE_ODB_EXTEND_MODE			1

#घोषणा KEY_VALID					0x02

#घोषणा HNS_ROCE_CQE_QPN_MASK				0x3ffff
#घोषणा HNS_ROCE_CQE_STATUS_MASK			0x1f
#घोषणा HNS_ROCE_CQE_OPCODE_MASK			0xf

#घोषणा HNS_ROCE_CQE_SUCCESS				0x00
#घोषणा HNS_ROCE_CQE_SYNDROME_LOCAL_LENGTH_ERR		0x01
#घोषणा HNS_ROCE_CQE_SYNDROME_LOCAL_QP_OP_ERR		0x02
#घोषणा HNS_ROCE_CQE_SYNDROME_LOCAL_PROT_ERR		0x03
#घोषणा HNS_ROCE_CQE_SYNDROME_WR_FLUSH_ERR		0x04
#घोषणा HNS_ROCE_CQE_SYNDROME_MEM_MANAGE_OPERATE_ERR	0x05
#घोषणा HNS_ROCE_CQE_SYNDROME_BAD_RESP_ERR		0x06
#घोषणा HNS_ROCE_CQE_SYNDROME_LOCAL_ACCESS_ERR		0x07
#घोषणा HNS_ROCE_CQE_SYNDROME_REMOTE_INVAL_REQ_ERR	0x08
#घोषणा HNS_ROCE_CQE_SYNDROME_REMOTE_ACCESS_ERR		0x09
#घोषणा HNS_ROCE_CQE_SYNDROME_REMOTE_OP_ERR		0x0a
#घोषणा HNS_ROCE_CQE_SYNDROME_TRANSPORT_RETRY_EXC_ERR	0x0b
#घोषणा HNS_ROCE_CQE_SYNDROME_RNR_RETRY_EXC_ERR		0x0c

#घोषणा QP1C_CFGN_OFFSET				0x28
#घोषणा PHY_PORT_OFFSET					0x8
#घोषणा MTPT_IDX_SHIFT					16
#घोषणा ALL_PORT_VAL_OPEN				0x3f
#घोषणा POL_TIME_INTERVAL_VAL				0x80
#घोषणा SLEEP_TIME_INTERVAL				20
#घोषणा SQ_PSN_SHIFT					8
#घोषणा QKEY_VAL					0x80010000
#घोषणा SDB_INV_CNT_OFFSET				8

#घोषणा HNS_ROCE_CEQ_DEFAULT_INTERVAL			0x10
#घोषणा HNS_ROCE_CEQ_DEFAULT_BURST_NUM			0x10

#घोषणा HNS_ROCE_INT_MASK_DISABLE			0
#घोषणा HNS_ROCE_INT_MASK_ENABLE			1

#घोषणा CEQ_REG_OFFSET					0x18

#घोषणा HNS_ROCE_CEQE_CEQE_COMP_OWNER_S	0

#घोषणा HNS_ROCE_V1_CONS_IDX_M GENMASK(15, 0)

#घोषणा HNS_ROCE_CEQE_CEQE_COMP_CQN_S 16
#घोषणा HNS_ROCE_CEQE_CEQE_COMP_CQN_M GENMASK(31, 16)

#घोषणा HNS_ROCE_AEQE_U32_4_EVENT_TYPE_S 16
#घोषणा HNS_ROCE_AEQE_U32_4_EVENT_TYPE_M GENMASK(23, 16)

#घोषणा HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_S 24
#घोषणा HNS_ROCE_AEQE_U32_4_EVENT_SUB_TYPE_M GENMASK(30, 24)

#घोषणा HNS_ROCE_AEQE_U32_4_OWNER_S 31

#घोषणा HNS_ROCE_AEQE_EVENT_QP_EVENT_QP_QPN_S 0
#घोषणा HNS_ROCE_AEQE_EVENT_QP_EVENT_QP_QPN_M GENMASK(23, 0)

#घोषणा HNS_ROCE_AEQE_EVENT_QP_EVENT_PORT_NUM_S 25
#घोषणा HNS_ROCE_AEQE_EVENT_QP_EVENT_PORT_NUM_M GENMASK(27, 25)

#घोषणा HNS_ROCE_AEQE_EVENT_CQ_EVENT_CQ_CQN_S 0
#घोषणा HNS_ROCE_AEQE_EVENT_CQ_EVENT_CQ_CQN_M GENMASK(15, 0)

#घोषणा HNS_ROCE_AEQE_EVENT_CE_EVENT_CEQE_CEQN_S 0
#घोषणा HNS_ROCE_AEQE_EVENT_CE_EVENT_CEQE_CEQN_M GENMASK(4, 0)

/* Local Work Queue Catastrophic Error,SUBTYPE 0x5 */
क्रमागत अणु
	HNS_ROCE_LWQCE_QPC_ERROR = 1,
	HNS_ROCE_LWQCE_MTU_ERROR,
	HNS_ROCE_LWQCE_WQE_BA_ADDR_ERROR,
	HNS_ROCE_LWQCE_WQE_ADDR_ERROR,
	HNS_ROCE_LWQCE_SQ_WQE_SHIFT_ERROR,
	HNS_ROCE_LWQCE_SL_ERROR,
	HNS_ROCE_LWQCE_PORT_ERROR,
पूर्ण;

/* Local Access Violation Work Queue Error,SUBTYPE 0x7 */
क्रमागत अणु
	HNS_ROCE_LAVWQE_R_KEY_VIOLATION = 1,
	HNS_ROCE_LAVWQE_LENGTH_ERROR,
	HNS_ROCE_LAVWQE_VA_ERROR,
	HNS_ROCE_LAVWQE_PD_ERROR,
	HNS_ROCE_LAVWQE_RW_ACC_ERROR,
	HNS_ROCE_LAVWQE_KEY_STATE_ERROR,
	HNS_ROCE_LAVWQE_MR_OPERATION_ERROR,
पूर्ण;

/* DOORBELL overflow subtype */
क्रमागत अणु
	HNS_ROCE_DB_SUBTYPE_SDB_OVF = 1,
	HNS_ROCE_DB_SUBTYPE_SDB_ALM_OVF,
	HNS_ROCE_DB_SUBTYPE_ODB_OVF,
	HNS_ROCE_DB_SUBTYPE_ODB_ALM_OVF,
	HNS_ROCE_DB_SUBTYPE_SDB_ALM_EMP,
	HNS_ROCE_DB_SUBTYPE_ODB_ALM_EMP,
पूर्ण;

क्रमागत अणु
	/* RQ&SRQ related operations */
	HNS_ROCE_OPCODE_SEND_DATA_RECEIVE = 0x06,
	HNS_ROCE_OPCODE_RDMA_WITH_IMM_RECEIVE,
पूर्ण;

क्रमागत अणु
	HNS_ROCE_PORT_DOWN = 0,
	HNS_ROCE_PORT_UP,
पूर्ण;

काष्ठा hns_roce_cq_context अणु
	__le32 cqc_byte_4;
	__le32 cq_bt_l;
	__le32 cqc_byte_12;
	__le32 cur_cqe_ba0_l;
	__le32 cqc_byte_20;
	__le32 cqe_tptr_addr_l;
	__le32 cur_cqe_ba1_l;
	__le32 cqc_byte_32;
पूर्ण;

#घोषणा CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_S 0
#घोषणा CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_M   \
	(((1UL << 2) - 1) << CQ_CONTEXT_CQC_BYTE_4_CQC_STATE_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_4_CQN_S 16
#घोषणा CQ_CONTEXT_CQC_BYTE_4_CQN_M   \
	(((1UL << 16) - 1) << CQ_CONTEXT_CQC_BYTE_4_CQN_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_S 0
#घोषणा CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_M   \
	(((1UL << 17) - 1) << CQ_CONTEXT_CQC_BYTE_12_CQ_BT_H_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_S 20
#घोषणा CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_M   \
	(((1UL << 4) - 1) << CQ_CONTEXT_CQC_BYTE_12_CQ_CQE_SHIFT_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_12_CEQN_S 24
#घोषणा CQ_CONTEXT_CQC_BYTE_12_CEQN_M   \
	(((1UL << 5) - 1) << CQ_CONTEXT_CQC_BYTE_12_CEQN_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_S 0
#घोषणा CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_M   \
	(((1UL << 5) - 1) << CQ_CONTEXT_CQC_BYTE_20_CUR_CQE_BA0_H_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_S 16
#घोषणा CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_M   \
	(((1UL << 16) - 1) << CQ_CONTEXT_CQC_BYTE_20_CQ_CUR_INDEX_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_S 8
#घोषणा CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_M   \
	(((1UL << 5) - 1) << CQ_CONTEXT_CQC_BYTE_20_CQE_TPTR_ADDR_H_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_S 0
#घोषणा CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_M   \
	(((1UL << 5) - 1) << CQ_CONTEXT_CQC_BYTE_32_CUR_CQE_BA1_H_S)

#घोषणा CQ_CONTEXT_CQC_BYTE_32_SE_FLAG_S 9

#घोषणा CQ_CONTEXT_CQC_BYTE_32_CE_FLAG_S 8
#घोषणा CQ_CONTEXT_CQC_BYTE_32_NOTIFICATION_FLAG_S 14
#घोषणा CQ_CQNTEXT_CQC_BYTE_32_TYPE_OF_COMPLETION_NOTIFICATION_S 15

#घोषणा CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_S 16
#घोषणा CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_M   \
	(((1UL << 16) - 1) << CQ_CONTEXT_CQC_BYTE_32_CQ_CONS_IDX_S)

काष्ठा hns_roce_cqe अणु
	__le32 cqe_byte_4;
	जोड़ अणु
		__le32 r_key;
		__le32 immediate_data;
	पूर्ण;
	__le32 byte_cnt;
	__le32 cqe_byte_16;
	__le32 cqe_byte_20;
	__le32 s_mac_l;
	__le32 cqe_byte_28;
	__le32 reserved;
पूर्ण;

#घोषणा CQE_BYTE_4_OWNER_S 7
#घोषणा CQE_BYTE_4_SQ_RQ_FLAG_S 14

#घोषणा CQE_BYTE_4_STATUS_OF_THE_OPERATION_S 8
#घोषणा CQE_BYTE_4_STATUS_OF_THE_OPERATION_M   \
	(((1UL << 5) - 1) << CQE_BYTE_4_STATUS_OF_THE_OPERATION_S)

#घोषणा CQE_BYTE_4_WQE_INDEX_S 16
#घोषणा CQE_BYTE_4_WQE_INDEX_M	(((1UL << 14) - 1) << CQE_BYTE_4_WQE_INDEX_S)

#घोषणा CQE_BYTE_4_OPERATION_TYPE_S 0
#घोषणा CQE_BYTE_4_OPERATION_TYPE_M   \
	(((1UL << 4) - 1) << CQE_BYTE_4_OPERATION_TYPE_S)

#घोषणा CQE_BYTE_4_IMM_INDICATOR_S 15

#घोषणा CQE_BYTE_16_LOCAL_QPN_S 0
#घोषणा CQE_BYTE_16_LOCAL_QPN_M	(((1UL << 24) - 1) << CQE_BYTE_16_LOCAL_QPN_S)

#घोषणा CQE_BYTE_20_PORT_NUM_S 26
#घोषणा CQE_BYTE_20_PORT_NUM_M	(((1UL << 3) - 1) << CQE_BYTE_20_PORT_NUM_S)

#घोषणा CQE_BYTE_20_SL_S 24
#घोषणा CQE_BYTE_20_SL_M	(((1UL << 2) - 1) << CQE_BYTE_20_SL_S)

#घोषणा CQE_BYTE_20_REMOTE_QPN_S 0
#घोषणा CQE_BYTE_20_REMOTE_QPN_M   \
	(((1UL << 24) - 1) << CQE_BYTE_20_REMOTE_QPN_S)

#घोषणा CQE_BYTE_20_GRH_PRESENT_S 29

#घोषणा CQE_BYTE_28_P_KEY_IDX_S 16
#घोषणा CQE_BYTE_28_P_KEY_IDX_M	(((1UL << 16) - 1) << CQE_BYTE_28_P_KEY_IDX_S)

#घोषणा CQ_DB_REQ_NOT_SOL	0
#घोषणा CQ_DB_REQ_NOT		(1 << 16)

काष्ठा hns_roce_v1_mpt_entry अणु
	__le32  mpt_byte_4;
	__le32  pbl_addr_l;
	__le32  mpt_byte_12;
	__le32  virt_addr_l;
	__le32  virt_addr_h;
	__le32  length;
	__le32  mpt_byte_28;
	__le32  pa0_l;
	__le32  mpt_byte_36;
	__le32  mpt_byte_40;
	__le32  mpt_byte_44;
	__le32  mpt_byte_48;
	__le32  pa4_l;
	__le32  mpt_byte_56;
	__le32  mpt_byte_60;
	__le32  mpt_byte_64;
पूर्ण;

#घोषणा MPT_BYTE_4_KEY_STATE_S 0
#घोषणा MPT_BYTE_4_KEY_STATE_M	(((1UL << 2) - 1) << MPT_BYTE_4_KEY_STATE_S)

#घोषणा MPT_BYTE_4_KEY_S 8
#घोषणा MPT_BYTE_4_KEY_M	(((1UL << 8) - 1) << MPT_BYTE_4_KEY_S)

#घोषणा MPT_BYTE_4_PAGE_SIZE_S 16
#घोषणा MPT_BYTE_4_PAGE_SIZE_M	(((1UL << 2) - 1) << MPT_BYTE_4_PAGE_SIZE_S)

#घोषणा MPT_BYTE_4_MW_TYPE_S 20

#घोषणा MPT_BYTE_4_MW_BIND_ENABLE_S 21

#घोषणा MPT_BYTE_4_OWN_S 22

#घोषणा MPT_BYTE_4_MEMORY_LOCATION_TYPE_S 24
#घोषणा MPT_BYTE_4_MEMORY_LOCATION_TYPE_M   \
	(((1UL << 2) - 1) << MPT_BYTE_4_MEMORY_LOCATION_TYPE_S)

#घोषणा MPT_BYTE_4_REMOTE_ATOMIC_S 26
#घोषणा MPT_BYTE_4_LOCAL_WRITE_S 27
#घोषणा MPT_BYTE_4_REMOTE_WRITE_S 28
#घोषणा MPT_BYTE_4_REMOTE_READ_S 29
#घोषणा MPT_BYTE_4_REMOTE_INVAL_ENABLE_S 30
#घोषणा MPT_BYTE_4_ADDRESS_TYPE_S 31

#घोषणा MPT_BYTE_12_PBL_ADDR_H_S 0
#घोषणा MPT_BYTE_12_PBL_ADDR_H_M   \
	(((1UL << 17) - 1) << MPT_BYTE_12_PBL_ADDR_H_S)

#घोषणा MPT_BYTE_12_MW_BIND_COUNTER_S 17
#घोषणा MPT_BYTE_12_MW_BIND_COUNTER_M   \
	(((1UL << 15) - 1) << MPT_BYTE_12_MW_BIND_COUNTER_S)

#घोषणा MPT_BYTE_28_PD_S 0
#घोषणा MPT_BYTE_28_PD_M	(((1UL << 16) - 1) << MPT_BYTE_28_PD_S)

#घोषणा MPT_BYTE_28_L_KEY_IDX_L_S 16
#घोषणा MPT_BYTE_28_L_KEY_IDX_L_M   \
	(((1UL << 16) - 1) << MPT_BYTE_28_L_KEY_IDX_L_S)

#घोषणा MPT_BYTE_36_PA0_H_S 0
#घोषणा MPT_BYTE_36_PA0_H_M	(((1UL << 5) - 1) << MPT_BYTE_36_PA0_H_S)

#घोषणा MPT_BYTE_36_PA1_L_S 8
#घोषणा MPT_BYTE_36_PA1_L_M	(((1UL << 24) - 1) << MPT_BYTE_36_PA1_L_S)

#घोषणा MPT_BYTE_40_PA1_H_S 0
#घोषणा MPT_BYTE_40_PA1_H_M	(((1UL << 13) - 1) << MPT_BYTE_40_PA1_H_S)

#घोषणा MPT_BYTE_40_PA2_L_S 16
#घोषणा MPT_BYTE_40_PA2_L_M	(((1UL << 16) - 1) << MPT_BYTE_40_PA2_L_S)

#घोषणा MPT_BYTE_44_PA2_H_S 0
#घोषणा MPT_BYTE_44_PA2_H_M	(((1UL << 21) - 1) << MPT_BYTE_44_PA2_H_S)

#घोषणा MPT_BYTE_44_PA3_L_S 24
#घोषणा MPT_BYTE_44_PA3_L_M	(((1UL << 8) - 1) << MPT_BYTE_44_PA3_L_S)

#घोषणा MPT_BYTE_48_PA3_H_S 0
#घोषणा MPT_BYTE_48_PA3_H_M	(((1UL << 29) - 1) << MPT_BYTE_48_PA3_H_S)

#घोषणा MPT_BYTE_56_PA4_H_S 0
#घोषणा MPT_BYTE_56_PA4_H_M	(((1UL << 5) - 1) << MPT_BYTE_56_PA4_H_S)

#घोषणा MPT_BYTE_56_PA5_L_S 8
#घोषणा MPT_BYTE_56_PA5_L_M	(((1UL << 24) - 1) << MPT_BYTE_56_PA5_L_S)

#घोषणा MPT_BYTE_60_PA5_H_S 0
#घोषणा MPT_BYTE_60_PA5_H_M	(((1UL << 13) - 1) << MPT_BYTE_60_PA5_H_S)

#घोषणा MPT_BYTE_60_PA6_L_S 16
#घोषणा MPT_BYTE_60_PA6_L_M	(((1UL << 16) - 1) << MPT_BYTE_60_PA6_L_S)

#घोषणा MPT_BYTE_64_PA6_H_S 0
#घोषणा MPT_BYTE_64_PA6_H_M	(((1UL << 21) - 1) << MPT_BYTE_64_PA6_H_S)

#घोषणा MPT_BYTE_64_L_KEY_IDX_H_S 24
#घोषणा MPT_BYTE_64_L_KEY_IDX_H_M   \
	(((1UL << 8) - 1) << MPT_BYTE_64_L_KEY_IDX_H_S)

काष्ठा hns_roce_wqe_ctrl_seg अणु
	__le32 sgl_pa_h;
	__le32 flag;
	जोड़ अणु
		__be32 imm_data;
		__le32 inv_key;
	पूर्ण;
	__le32 msg_length;
पूर्ण;

काष्ठा hns_roce_wqe_data_seg अणु
	__le64    addr;
	__le32    lkey;
	__le32    len;
पूर्ण;

काष्ठा hns_roce_wqe_raddr_seg अणु
	__le32 rkey;
	__le32 len; /* reserved */
	__le64 raddr;
पूर्ण;

काष्ठा hns_roce_rq_wqe_ctrl अणु
	__le32 rwqe_byte_4;
	__le32 rocee_sgl_ba_l;
	__le32 rwqe_byte_12;
	__le32 reserved[5];
पूर्ण;

#घोषणा RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_S 16
#घोषणा RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_M   \
	(((1UL << 6) - 1) << RQ_WQE_CTRL_RWQE_BYTE_12_RWQE_SGE_NUM_S)

#घोषणा HNS_ROCE_QP_DESTROY_TIMEOUT_MSECS	10000

#घोषणा GID_LEN					16

काष्ठा hns_roce_ud_send_wqe अणु
	__le32 dmac_h;
	__le32 u32_8;
	__le32 immediate_data;

	__le32 u32_16;
	जोड़ अणु
		अचिन्हित अक्षर dgid[GID_LEN];
		काष्ठा अणु
			__le32 u32_20;
			__le32 u32_24;
			__le32 u32_28;
			__le32 u32_32;
		पूर्ण;
	पूर्ण;

	__le32 u32_36;
	__le32 u32_40;

	__le32 va0_l;
	__le32 va0_h;
	__le32 l_key0;

	__le32 va1_l;
	__le32 va1_h;
	__le32 l_key1;
पूर्ण;

#घोषणा UD_SEND_WQE_U32_4_DMAC_0_S 0
#घोषणा UD_SEND_WQE_U32_4_DMAC_0_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_4_DMAC_0_S)

#घोषणा UD_SEND_WQE_U32_4_DMAC_1_S 8
#घोषणा UD_SEND_WQE_U32_4_DMAC_1_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_4_DMAC_1_S)

#घोषणा UD_SEND_WQE_U32_4_DMAC_2_S 16
#घोषणा UD_SEND_WQE_U32_4_DMAC_2_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_4_DMAC_2_S)

#घोषणा UD_SEND_WQE_U32_4_DMAC_3_S 24
#घोषणा UD_SEND_WQE_U32_4_DMAC_3_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_4_DMAC_3_S)

#घोषणा UD_SEND_WQE_U32_8_DMAC_4_S 0
#घोषणा UD_SEND_WQE_U32_8_DMAC_4_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_8_DMAC_4_S)

#घोषणा UD_SEND_WQE_U32_8_DMAC_5_S 8
#घोषणा UD_SEND_WQE_U32_8_DMAC_5_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_8_DMAC_5_S)

#घोषणा UD_SEND_WQE_U32_8_LOOPBACK_INDICATOR_S 22

#घोषणा UD_SEND_WQE_U32_8_OPERATION_TYPE_S 16
#घोषणा UD_SEND_WQE_U32_8_OPERATION_TYPE_M   \
	(((1UL << 4) - 1) << UD_SEND_WQE_U32_8_OPERATION_TYPE_S)

#घोषणा UD_SEND_WQE_U32_8_NUMBER_OF_DATA_SEG_S 24
#घोषणा UD_SEND_WQE_U32_8_NUMBER_OF_DATA_SEG_M   \
	(((1UL << 6) - 1) << UD_SEND_WQE_U32_8_NUMBER_OF_DATA_SEG_S)

#घोषणा UD_SEND_WQE_U32_8_SEND_GL_ROUTING_HDR_FLAG_S 31

#घोषणा UD_SEND_WQE_U32_16_DEST_QP_S 0
#घोषणा UD_SEND_WQE_U32_16_DEST_QP_M   \
	(((1UL << 24) - 1) << UD_SEND_WQE_U32_16_DEST_QP_S)

#घोषणा UD_SEND_WQE_U32_16_MAX_STATIC_RATE_S 24
#घोषणा UD_SEND_WQE_U32_16_MAX_STATIC_RATE_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_16_MAX_STATIC_RATE_S)

#घोषणा UD_SEND_WQE_U32_36_FLOW_LABEL_S 0
#घोषणा UD_SEND_WQE_U32_36_FLOW_LABEL_M   \
	(((1UL << 20) - 1) << UD_SEND_WQE_U32_36_FLOW_LABEL_S)

#घोषणा UD_SEND_WQE_U32_36_PRIORITY_S 20
#घोषणा UD_SEND_WQE_U32_36_PRIORITY_M   \
	(((1UL << 4) - 1) << UD_SEND_WQE_U32_36_PRIORITY_S)

#घोषणा UD_SEND_WQE_U32_36_SGID_INDEX_S 24
#घोषणा UD_SEND_WQE_U32_36_SGID_INDEX_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_36_SGID_INDEX_S)

#घोषणा UD_SEND_WQE_U32_40_HOP_LIMIT_S 0
#घोषणा UD_SEND_WQE_U32_40_HOP_LIMIT_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_40_HOP_LIMIT_S)

#घोषणा UD_SEND_WQE_U32_40_TRAFFIC_CLASS_S 8
#घोषणा UD_SEND_WQE_U32_40_TRAFFIC_CLASS_M   \
	(((1UL << 8) - 1) << UD_SEND_WQE_U32_40_TRAFFIC_CLASS_S)

काष्ठा hns_roce_sqp_context अणु
	__le32 qp1c_bytes_4;
	__le32 sq_rq_bt_l;
	__le32 qp1c_bytes_12;
	__le32 qp1c_bytes_16;
	__le32 qp1c_bytes_20;
	__le32 cur_rq_wqe_ba_l;
	__le32 qp1c_bytes_28;
	__le32 qp1c_bytes_32;
	__le32 cur_sq_wqe_ba_l;
	__le32 qp1c_bytes_40;
पूर्ण;

#घोषणा QP1C_BYTES_4_QP_STATE_S 0
#घोषणा QP1C_BYTES_4_QP_STATE_M   \
	(((1UL << 3) - 1) << QP1C_BYTES_4_QP_STATE_S)

#घोषणा QP1C_BYTES_4_SQ_WQE_SHIFT_S 8
#घोषणा QP1C_BYTES_4_SQ_WQE_SHIFT_M   \
	(((1UL << 4) - 1) << QP1C_BYTES_4_SQ_WQE_SHIFT_S)

#घोषणा QP1C_BYTES_4_RQ_WQE_SHIFT_S 12
#घोषणा QP1C_BYTES_4_RQ_WQE_SHIFT_M   \
	(((1UL << 4) - 1) << QP1C_BYTES_4_RQ_WQE_SHIFT_S)

#घोषणा QP1C_BYTES_4_PD_S 16
#घोषणा QP1C_BYTES_4_PD_M	(((1UL << 16) - 1) << QP1C_BYTES_4_PD_S)

#घोषणा QP1C_BYTES_12_SQ_RQ_BT_H_S 0
#घोषणा QP1C_BYTES_12_SQ_RQ_BT_H_M   \
	(((1UL << 17) - 1) << QP1C_BYTES_12_SQ_RQ_BT_H_S)

#घोषणा QP1C_BYTES_16_RQ_HEAD_S 0
#घोषणा QP1C_BYTES_16_RQ_HEAD_M	(((1UL << 15) - 1) << QP1C_BYTES_16_RQ_HEAD_S)

#घोषणा QP1C_BYTES_16_PORT_NUM_S 16
#घोषणा QP1C_BYTES_16_PORT_NUM_M   \
	(((1UL << 3) - 1) << QP1C_BYTES_16_PORT_NUM_S)

#घोषणा QP1C_BYTES_16_SIGNALING_TYPE_S 27
#घोषणा QP1C_BYTES_16_LOCAL_ENABLE_E2E_CREDIT_S 28
#घोषणा QP1C_BYTES_16_RQ_BA_FLG_S 29
#घोषणा QP1C_BYTES_16_SQ_BA_FLG_S 30
#घोषणा QP1C_BYTES_16_QP1_ERR_S 31

#घोषणा QP1C_BYTES_20_SQ_HEAD_S 0
#घोषणा QP1C_BYTES_20_SQ_HEAD_M	(((1UL << 15) - 1) << QP1C_BYTES_20_SQ_HEAD_S)

#घोषणा QP1C_BYTES_20_PKEY_IDX_S 16
#घोषणा QP1C_BYTES_20_PKEY_IDX_M   \
	(((1UL << 16) - 1) << QP1C_BYTES_20_PKEY_IDX_S)

#घोषणा QP1C_BYTES_28_CUR_RQ_WQE_BA_H_S 0
#घोषणा QP1C_BYTES_28_CUR_RQ_WQE_BA_H_M   \
	(((1UL << 5) - 1) << QP1C_BYTES_28_CUR_RQ_WQE_BA_H_S)

#घोषणा QP1C_BYTES_28_RQ_CUR_IDX_S 16
#घोषणा QP1C_BYTES_28_RQ_CUR_IDX_M   \
	(((1UL << 15) - 1) << QP1C_BYTES_28_RQ_CUR_IDX_S)

#घोषणा QP1C_BYTES_32_TX_CQ_NUM_S 0
#घोषणा QP1C_BYTES_32_TX_CQ_NUM_M   \
	(((1UL << 16) - 1) << QP1C_BYTES_32_TX_CQ_NUM_S)

#घोषणा QP1C_BYTES_32_RX_CQ_NUM_S 16
#घोषणा QP1C_BYTES_32_RX_CQ_NUM_M   \
	(((1UL << 16) - 1) << QP1C_BYTES_32_RX_CQ_NUM_S)

#घोषणा QP1C_BYTES_40_CUR_SQ_WQE_BA_H_S 0
#घोषणा QP1C_BYTES_40_CUR_SQ_WQE_BA_H_M   \
	(((1UL << 5) - 1) << QP1C_BYTES_40_CUR_SQ_WQE_BA_H_S)

#घोषणा QP1C_BYTES_40_SQ_CUR_IDX_S 16
#घोषणा QP1C_BYTES_40_SQ_CUR_IDX_M   \
	(((1UL << 15) - 1) << QP1C_BYTES_40_SQ_CUR_IDX_S)

#घोषणा HNS_ROCE_WQE_INLINE		(1UL<<31)
#घोषणा HNS_ROCE_WQE_SE			(1UL<<30)

#घोषणा HNS_ROCE_WQE_SGE_NUM_BIT	24
#घोषणा HNS_ROCE_WQE_IMM		(1UL<<23)
#घोषणा HNS_ROCE_WQE_FENCE		(1UL<<21)
#घोषणा HNS_ROCE_WQE_CQ_NOTIFY		(1UL<<20)

#घोषणा HNS_ROCE_WQE_OPCODE_SEND	(0<<16)
#घोषणा HNS_ROCE_WQE_OPCODE_RDMA_READ	(1<<16)
#घोषणा HNS_ROCE_WQE_OPCODE_RDMA_WRITE	(2<<16)
#घोषणा HNS_ROCE_WQE_OPCODE_LOCAL_INV	(4<<16)
#घोषणा HNS_ROCE_WQE_OPCODE_UD_SEND	(7<<16)
#घोषणा HNS_ROCE_WQE_OPCODE_MASK	(15<<16)

काष्ठा hns_roce_qp_context अणु
	__le32 qpc_bytes_4;
	__le32 qpc_bytes_8;
	__le32 qpc_bytes_12;
	__le32 qpc_bytes_16;
	__le32 sq_rq_bt_l;
	__le32 qpc_bytes_24;
	__le32 irrl_ba_l;
	__le32 qpc_bytes_32;
	__le32 qpc_bytes_36;
	__le32 dmac_l;
	__le32 qpc_bytes_44;
	__le32 qpc_bytes_48;
	u8     dgid[16];
	__le32 qpc_bytes_68;
	__le32 cur_rq_wqe_ba_l;
	__le32 qpc_bytes_76;
	__le32 rx_rnr_समय;
	__le32 qpc_bytes_84;
	__le32 qpc_bytes_88;
	जोड़ अणु
		__le32 rx_sge_len;
		__le32 dma_length;
	पूर्ण;
	जोड़ अणु
		__le32 rx_sge_num;
		__le32 rx_send_pktn;
		__le32 r_key;
	पूर्ण;
	__le32 va_l;
	__le32 va_h;
	__le32 qpc_bytes_108;
	__le32 qpc_bytes_112;
	__le32 rx_cur_sq_wqe_ba_l;
	__le32 qpc_bytes_120;
	__le32 qpc_bytes_124;
	__le32 qpc_bytes_128;
	__le32 qpc_bytes_132;
	__le32 qpc_bytes_136;
	__le32 qpc_bytes_140;
	__le32 qpc_bytes_144;
	__le32 qpc_bytes_148;
	जोड़ अणु
		__le32 rnr_retry;
		__le32 ack_समय;
	पूर्ण;
	__le32 qpc_bytes_156;
	__le32 pkt_use_len;
	__le32 qpc_bytes_164;
	__le32 qpc_bytes_168;
	जोड़ अणु
		__le32 sge_use_len;
		__le32 pa_use_len;
	पूर्ण;
	__le32 qpc_bytes_176;
	__le32 qpc_bytes_180;
	__le32 tx_cur_sq_wqe_ba_l;
	__le32 qpc_bytes_188;
	__le32 rvd21;
पूर्ण;

#घोषणा QP_CONTEXT_QPC_BYTES_4_TRANSPORT_SERVICE_TYPE_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_4_TRANSPORT_SERVICE_TYPE_M   \
	(((1UL << 3) - 1) << QP_CONTEXT_QPC_BYTES_4_TRANSPORT_SERVICE_TYPE_S)

#घोषणा QP_CONTEXT_QPC_BYTE_4_ENABLE_FPMR_S 3
#घोषणा QP_CONTEXT_QPC_BYTE_4_RDMA_READ_ENABLE_S 4
#घोषणा QP_CONTEXT_QPC_BYTE_4_RDMA_WRITE_ENABLE_S 5
#घोषणा QP_CONTEXT_QPC_BYTE_4_ATOMIC_OPERATION_ENABLE_S 6
#घोषणा QP_CONTEXT_QPC_BYTE_4_RDMAR_USE_S 7

#घोषणा QP_CONTEXT_QPC_BYTES_4_SQ_WQE_SHIFT_S 8
#घोषणा QP_CONTEXT_QPC_BYTES_4_SQ_WQE_SHIFT_M   \
	(((1UL << 4) - 1) << QP_CONTEXT_QPC_BYTES_4_SQ_WQE_SHIFT_S)

#घोषणा QP_CONTEXT_QPC_BYTES_4_RQ_WQE_SHIFT_S 12
#घोषणा QP_CONTEXT_QPC_BYTES_4_RQ_WQE_SHIFT_M   \
	(((1UL << 4) - 1) << QP_CONTEXT_QPC_BYTES_4_RQ_WQE_SHIFT_S)

#घोषणा QP_CONTEXT_QPC_BYTES_4_PD_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_4_PD_M   \
	(((1UL << 16) - 1) << QP_CONTEXT_QPC_BYTES_4_PD_S)

#घोषणा QP_CONTEXT_QPC_BYTES_8_TX_COMPLETION_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_8_TX_COMPLETION_M   \
	(((1UL << 16) - 1) << QP_CONTEXT_QPC_BYTES_8_TX_COMPLETION_S)

#घोषणा QP_CONTEXT_QPC_BYTES_8_RX_COMPLETION_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_8_RX_COMPLETION_M   \
	(((1UL << 16) - 1) << QP_CONTEXT_QPC_BYTES_8_RX_COMPLETION_S)

#घोषणा QP_CONTEXT_QPC_BYTES_12_SRQ_NUMBER_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_12_SRQ_NUMBER_M   \
	(((1UL << 16) - 1) << QP_CONTEXT_QPC_BYTES_12_SRQ_NUMBER_S)

#घोषणा QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_M   \
	(((1UL << 16) - 1) << QP_CONTEXT_QPC_BYTES_12_P_KEY_INDEX_S)

#घोषणा QP_CONTEXT_QPC_BYTES_16_QP_NUM_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_16_QP_NUM_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_16_QP_NUM_S)

#घोषणा QP_CONTEXT_QPC_BYTES_24_SQ_RQ_BT_H_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_24_SQ_RQ_BT_H_M   \
	(((1UL << 17) - 1) << QP_CONTEXT_QPC_BYTES_24_SQ_RQ_BT_H_S)

#घोषणा QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_S 18
#घोषणा QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_M   \
	(((1UL << 5) - 1) << QP_CONTEXT_QPC_BYTES_24_MINIMUM_RNR_NAK_TIMER_S)

#घोषणा QP_CONTEXT_QPC_BYTE_24_REMOTE_ENABLE_E2E_CREDITS_S 23

#घोषणा QP_CONTEXT_QPC_BYTES_32_IRRL_BA_H_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_32_IRRL_BA_H_M   \
	(((1UL << 17) - 1) << QP_CONTEXT_QPC_BYTES_32_IRRL_BA_H_S)

#घोषणा QP_CONTEXT_QPC_BYTES_32_MIG_STATE_S 18
#घोषणा QP_CONTEXT_QPC_BYTES_32_MIG_STATE_M   \
	(((1UL << 2) - 1) << QP_CONTEXT_QPC_BYTES_32_MIG_STATE_S)

#घोषणा QP_CONTEXT_QPC_BYTE_32_LOCAL_ENABLE_E2E_CREDITS_S 20
#घोषणा QP_CONTEXT_QPC_BYTE_32_SIGNALING_TYPE_S 21
#घोषणा QP_CONTEXT_QPC_BYTE_32_LOOPBACK_INDICATOR_S 22
#घोषणा QP_CONTEXT_QPC_BYTE_32_GLOBAL_HEADER_S 23

#घोषणा QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_32_RESPONDER_RESOURCES_S)

#घोषणा QP_CONTEXT_QPC_BYTES_36_DEST_QP_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_36_DEST_QP_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_36_DEST_QP_S)

#घोषणा QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_36_SGID_INDEX_S)

#घोषणा QP_CONTEXT_QPC_BYTES_44_DMAC_H_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_44_DMAC_H_M   \
	(((1UL << 16) - 1) << QP_CONTEXT_QPC_BYTES_44_DMAC_H_S)

#घोषणा QP_CONTEXT_QPC_BYTES_44_MAXIMUM_STATIC_RATE_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_44_MAXIMUM_STATIC_RATE_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_44_MAXIMUM_STATIC_RATE_S)

#घोषणा QP_CONTEXT_QPC_BYTES_44_HOPLMT_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_44_HOPLMT_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_44_HOPLMT_S)

#घोषणा QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_M   \
	(((1UL << 20) - 1) << QP_CONTEXT_QPC_BYTES_48_FLOWLABEL_S)

#घोषणा QP_CONTEXT_QPC_BYTES_48_TCLASS_S 20
#घोषणा QP_CONTEXT_QPC_BYTES_48_TCLASS_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_48_TCLASS_S)

#घोषणा QP_CONTEXT_QPC_BYTES_48_MTU_S 28
#घोषणा QP_CONTEXT_QPC_BYTES_48_MTU_M   \
	(((1UL << 4) - 1) << QP_CONTEXT_QPC_BYTES_48_MTU_S)

#घोषणा QP_CONTEXT_QPC_BYTES_68_RQ_HEAD_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_68_RQ_HEAD_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_68_RQ_HEAD_S)

#घोषणा QP_CONTEXT_QPC_BYTES_68_RQ_CUR_INDEX_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_68_RQ_CUR_INDEX_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_68_RQ_CUR_INDEX_S)

#घोषणा QP_CONTEXT_QPC_BYTES_76_CUR_RQ_WQE_BA_H_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_76_CUR_RQ_WQE_BA_H_M   \
	(((1UL << 5) - 1) << QP_CONTEXT_QPC_BYTES_76_CUR_RQ_WQE_BA_H_S)

#घोषणा QP_CONTEXT_QPC_BYTES_76_RX_REQ_MSN_S 8
#घोषणा QP_CONTEXT_QPC_BYTES_76_RX_REQ_MSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_76_RX_REQ_MSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_84_LAST_ACK_PSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_84_LAST_ACK_PSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_84_LAST_ACK_PSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_84_TRRL_HEAD_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_84_TRRL_HEAD_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_84_TRRL_HEAD_S)

#घोषणा QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_88_RX_REQ_EPSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_88_RX_REQ_PSN_ERR_FLAG_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_88_RX_LAST_OPCODE_FLG_S 25

#घोषणा QP_CONTEXT_QPC_BYTES_88_RQ_REQ_LAST_OPERATION_TYPE_S 26
#घोषणा QP_CONTEXT_QPC_BYTES_88_RQ_REQ_LAST_OPERATION_TYPE_M   \
	(((1UL << 2) - 1) << \
	QP_CONTEXT_QPC_BYTES_88_RQ_REQ_LAST_OPERATION_TYPE_S)

#घोषणा QP_CONTEXT_QPC_BYTES_88_RQ_REQ_RDMA_WR_FLAG_S 29
#घोषणा QP_CONTEXT_QPC_BYTES_88_RQ_REQ_RDMA_WR_FLAG_M   \
	(((1UL << 2) - 1) << QP_CONTEXT_QPC_BYTES_88_RQ_REQ_RDMA_WR_FLAG_S)

#घोषणा QP_CONTEXT_QPC_BYTES_108_TRRL_SDB_PSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_108_TRRL_SDB_PSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_108_TRRL_SDB_PSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_108_TRRL_SDB_PSN_FLG_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_108_TRRL_TDB_PSN_FLG_S 25

#घोषणा QP_CONTEXT_QPC_BYTES_112_TRRL_TDB_PSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_112_TRRL_TDB_PSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_112_TRRL_TDB_PSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_112_TRRL_TAIL_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_112_TRRL_TAIL_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_112_TRRL_TAIL_S)

#घोषणा QP_CONTEXT_QPC_BYTES_120_RX_CUR_SQ_WQE_BA_H_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_120_RX_CUR_SQ_WQE_BA_H_M   \
	(((1UL << 5) - 1) << QP_CONTEXT_QPC_BYTES_120_RX_CUR_SQ_WQE_BA_H_S)

#घोषणा QP_CONTEXT_QPC_BYTES_124_RX_ACK_MSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_124_RX_ACK_MSN_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_124_RX_ACK_MSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_124_IRRL_MSG_IDX_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_124_IRRL_MSG_IDX_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_124_IRRL_MSG_IDX_S)

#घोषणा QP_CONTEXT_QPC_BYTES_128_RX_ACK_EPSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_128_RX_ACK_EPSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_128_RX_ACK_EPSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_128_RX_ACK_PSN_ERR_FLG_S 24

#घोषणा QP_CONTEXT_QPC_BYTES_128_ACK_LAST_OPERATION_TYPE_S 25
#घोषणा QP_CONTEXT_QPC_BYTES_128_ACK_LAST_OPERATION_TYPE_M   \
	(((1UL << 2) - 1) << QP_CONTEXT_QPC_BYTES_128_ACK_LAST_OPERATION_TYPE_S)

#घोषणा QP_CONTEXT_QPC_BYTES_128_IRRL_PSN_VLD_FLG_S 27

#घोषणा QP_CONTEXT_QPC_BYTES_132_IRRL_PSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_132_IRRL_PSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_132_IRRL_PSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_132_IRRL_TAIL_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_132_IRRL_TAIL_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_132_IRRL_TAIL_S)

#घोषणा QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_PSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_PSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_PSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_FPKT_PSN_L_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_FPKT_PSN_L_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_136_RETRY_MSG_FPKT_PSN_L_S)

#घोषणा QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_FPKT_PSN_H_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_FPKT_PSN_H_M   \
	(((1UL << 16) - 1) << QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_FPKT_PSN_H_S)

#घोषणा QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_MSN_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_MSN_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_140_RETRY_MSG_MSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_140_RNR_RETRY_FLG_S 31

#घोषणा QP_CONTEXT_QPC_BYTES_144_QP_STATE_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_144_QP_STATE_M   \
	(((1UL << 3) - 1) << QP_CONTEXT_QPC_BYTES_144_QP_STATE_S)

#घोषणा QP_CONTEXT_QPC_BYTES_148_CHECK_FLAG_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_148_CHECK_FLAG_M   \
	(((1UL << 2) - 1) << QP_CONTEXT_QPC_BYTES_148_CHECK_FLAG_S)

#घोषणा QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_S 2
#घोषणा QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_M   \
	(((1UL << 3) - 1) << QP_CONTEXT_QPC_BYTES_148_RETRY_COUNT_S)

#घोषणा QP_CONTEXT_QPC_BYTES_148_RNR_RETRY_COUNT_S 5
#घोषणा QP_CONTEXT_QPC_BYTES_148_RNR_RETRY_COUNT_M   \
	(((1UL << 3) - 1) << QP_CONTEXT_QPC_BYTES_148_RNR_RETRY_COUNT_S)

#घोषणा QP_CONTEXT_QPC_BYTES_148_LSN_S 8
#घोषणा QP_CONTEXT_QPC_BYTES_148_LSN_M   \
	(((1UL << 16) - 1) << QP_CONTEXT_QPC_BYTES_148_LSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_156_RETRY_COUNT_INIT_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_156_RETRY_COUNT_INIT_M   \
	(((1UL << 3) - 1) << QP_CONTEXT_QPC_BYTES_156_RETRY_COUNT_INIT_S)

#घोषणा QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_S 3
#घोषणा QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_M   \
	(((1UL << 5) - 1) << QP_CONTEXT_QPC_BYTES_156_ACK_TIMEOUT_S)

#घोषणा QP_CONTEXT_QPC_BYTES_156_RNR_RETRY_COUNT_INIT_S 8
#घोषणा QP_CONTEXT_QPC_BYTES_156_RNR_RETRY_COUNT_INIT_M   \
	(((1UL << 3) - 1) << QP_CONTEXT_QPC_BYTES_156_RNR_RETRY_COUNT_INIT_S)

#घोषणा QP_CONTEXT_QPC_BYTES_156_PORT_NUM_S 11
#घोषणा QP_CONTEXT_QPC_BYTES_156_PORT_NUM_M   \
	(((1UL << 3) - 1) << QP_CONTEXT_QPC_BYTES_156_PORT_NUM_S)

#घोषणा QP_CONTEXT_QPC_BYTES_156_SL_S 14
#घोषणा QP_CONTEXT_QPC_BYTES_156_SL_M   \
	(((1UL << 2) - 1) << QP_CONTEXT_QPC_BYTES_156_SL_S)

#घोषणा QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_156_INITIATOR_DEPTH_S)

#घोषणा QP_CONTEXT_QPC_BYTES_156_ACK_REQ_IND_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_156_ACK_REQ_IND_M   \
	(((1UL << 2) - 1) << QP_CONTEXT_QPC_BYTES_156_ACK_REQ_IND_S)

#घोषणा QP_CONTEXT_QPC_BYTES_164_SQ_PSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_164_SQ_PSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_164_SQ_PSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_164_IRRL_HEAD_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_164_IRRL_HEAD_M   \
	(((1UL << 8) - 1) << QP_CONTEXT_QPC_BYTES_164_IRRL_HEAD_S)

#घोषणा QP_CONTEXT_QPC_BYTES_168_RETRY_SQ_PSN_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_168_RETRY_SQ_PSN_M   \
	(((1UL << 24) - 1) << QP_CONTEXT_QPC_BYTES_168_RETRY_SQ_PSN_S)

#घोषणा QP_CONTEXT_QPC_BYTES_168_SGE_USE_FLA_S 24
#घोषणा QP_CONTEXT_QPC_BYTES_168_SGE_USE_FLA_M   \
	(((1UL << 2) - 1) << QP_CONTEXT_QPC_BYTES_168_SGE_USE_FLA_S)

#घोषणा QP_CONTEXT_QPC_BYTES_168_DB_TYPE_S 26
#घोषणा QP_CONTEXT_QPC_BYTES_168_DB_TYPE_M   \
	(((1UL << 2) - 1) << QP_CONTEXT_QPC_BYTES_168_DB_TYPE_S)

#घोषणा QP_CONTEXT_QPC_BYTES_168_MSG_LP_IND_S 28
#घोषणा QP_CONTEXT_QPC_BYTES_168_CSDB_LP_IND_S 29
#घोषणा QP_CONTEXT_QPC_BYTES_168_QP_ERR_FLG_S 30

#घोषणा QP_CONTEXT_QPC_BYTES_176_DB_CUR_INDEX_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_176_DB_CUR_INDEX_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_176_DB_CUR_INDEX_S)

#घोषणा QP_CONTEXT_QPC_BYTES_176_RETRY_DB_CUR_INDEX_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_176_RETRY_DB_CUR_INDEX_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_176_RETRY_DB_CUR_INDEX_S)

#घोषणा QP_CONTEXT_QPC_BYTES_180_SQ_HEAD_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_180_SQ_HEAD_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_180_SQ_HEAD_S)

#घोषणा QP_CONTEXT_QPC_BYTES_180_SQ_CUR_INDEX_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_180_SQ_CUR_INDEX_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_180_SQ_CUR_INDEX_S)

#घोषणा QP_CONTEXT_QPC_BYTES_188_TX_CUR_SQ_WQE_BA_H_S 0
#घोषणा QP_CONTEXT_QPC_BYTES_188_TX_CUR_SQ_WQE_BA_H_M   \
	(((1UL << 5) - 1) << QP_CONTEXT_QPC_BYTES_188_TX_CUR_SQ_WQE_BA_H_S)

#घोषणा QP_CONTEXT_QPC_BYTES_188_PKT_RETRY_FLG_S 8

#घोषणा QP_CONTEXT_QPC_BYTES_188_TX_RETRY_CUR_INDEX_S 16
#घोषणा QP_CONTEXT_QPC_BYTES_188_TX_RETRY_CUR_INDEX_M   \
	(((1UL << 15) - 1) << QP_CONTEXT_QPC_BYTES_188_TX_RETRY_CUR_INDEX_S)

#घोषणा STATUS_MASK		0xff
#घोषणा GO_BIT_TIMEOUT_MSECS	10000
#घोषणा HCR_STATUS_OFFSET	0x18
#घोषणा HCR_GO_BIT		15

काष्ठा hns_roce_rq_db अणु
	__le32    u32_4;
	__le32    u32_8;
पूर्ण;

#घोषणा RQ_DOORBELL_U32_4_RQ_HEAD_S 0
#घोषणा RQ_DOORBELL_U32_4_RQ_HEAD_M   \
	(((1UL << 15) - 1) << RQ_DOORBELL_U32_4_RQ_HEAD_S)

#घोषणा RQ_DOORBELL_U32_8_QPN_S 0
#घोषणा RQ_DOORBELL_U32_8_QPN_M   (((1UL << 24) - 1) << RQ_DOORBELL_U32_8_QPN_S)

#घोषणा RQ_DOORBELL_U32_8_CMD_S 28
#घोषणा RQ_DOORBELL_U32_8_CMD_M   (((1UL << 3) - 1) << RQ_DOORBELL_U32_8_CMD_S)

#घोषणा RQ_DOORBELL_U32_8_HW_SYNC_S 31

काष्ठा hns_roce_sq_db अणु
	__le32    u32_4;
	__le32    u32_8;
पूर्ण;

#घोषणा SQ_DOORBELL_U32_4_SQ_HEAD_S 0
#घोषणा SQ_DOORBELL_U32_4_SQ_HEAD_M   \
	(((1UL << 15) - 1) << SQ_DOORBELL_U32_4_SQ_HEAD_S)

#घोषणा SQ_DOORBELL_U32_4_SL_S 16
#घोषणा SQ_DOORBELL_U32_4_SL_M   \
	(((1UL << 2) - 1) << SQ_DOORBELL_U32_4_SL_S)

#घोषणा SQ_DOORBELL_U32_4_PORT_S 18
#घोषणा SQ_DOORBELL_U32_4_PORT_M  (((1UL << 3) - 1) << SQ_DOORBELL_U32_4_PORT_S)

#घोषणा SQ_DOORBELL_U32_8_QPN_S 0
#घोषणा SQ_DOORBELL_U32_8_QPN_M   (((1UL << 24) - 1) << SQ_DOORBELL_U32_8_QPN_S)

#घोषणा SQ_DOORBELL_HW_SYNC_S 31

काष्ठा hns_roce_ext_db अणु
	पूर्णांक esdb_dep;
	पूर्णांक eodb_dep;
	काष्ठा hns_roce_buf_list *sdb_buf_list;
	काष्ठा hns_roce_buf_list *odb_buf_list;
पूर्ण;

काष्ठा hns_roce_db_table अणु
	पूर्णांक  sdb_ext_mod;
	पूर्णांक  odb_ext_mod;
	काष्ठा hns_roce_ext_db *ext_db;
पूर्ण;

काष्ठा hns_roce_bt_table अणु
	काष्ठा hns_roce_buf_list qpc_buf;
	काष्ठा hns_roce_buf_list mtpt_buf;
	काष्ठा hns_roce_buf_list cqc_buf;
पूर्ण;

काष्ठा hns_roce_tptr_table अणु
	काष्ठा hns_roce_buf_list tptr_buf;
पूर्ण;

काष्ठा hns_roce_qp_work अणु
	काष्ठा	work_काष्ठा work;
	काष्ठा	ib_device *ib_dev;
	काष्ठा	hns_roce_qp *qp;
	u32	db_रुको_stage;
	u32	sdb_issue_ptr;
	u32	sdb_inv_cnt;
	u32	sche_cnt;
पूर्ण;

काष्ठा hns_roce_mr_मुक्त_work अणु
	काष्ठा	work_काष्ठा work;
	काष्ठा	ib_device *ib_dev;
	काष्ठा	completion *comp;
	पूर्णांक	comp_flag;
	व्योम	*mr;
पूर्ण;

काष्ठा hns_roce_recreate_lp_qp_work अणु
	काष्ठा	work_काष्ठा work;
	काष्ठा	ib_device *ib_dev;
	काष्ठा	completion *comp;
	पूर्णांक	comp_flag;
पूर्ण;

काष्ठा hns_roce_मुक्त_mr अणु
	काष्ठा workqueue_काष्ठा *मुक्त_mr_wq;
	काष्ठा hns_roce_qp *mr_मुक्त_qp[HNS_ROCE_V1_RESV_QP];
	काष्ठा hns_roce_cq *mr_मुक्त_cq;
	काष्ठा hns_roce_pd *mr_मुक्त_pd;
पूर्ण;

काष्ठा hns_roce_v1_priv अणु
	काष्ठा hns_roce_db_table  db_table;
	काष्ठा hns_roce_raq_table raq_table;
	काष्ठा hns_roce_bt_table  bt_table;
	काष्ठा hns_roce_tptr_table tptr_table;
	काष्ठा hns_roce_मुक्त_mr मुक्त_mr;
पूर्ण;

पूर्णांक hns_dsaf_roce_reset(काष्ठा fwnode_handle *dsaf_fwnode, bool dereset);
पूर्णांक hns_roce_v1_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc);
पूर्णांक hns_roce_v1_destroy_qp(काष्ठा ib_qp *ibqp, काष्ठा ib_udata *udata);

#पूर्ण_अगर
