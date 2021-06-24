<शैली गुरु>
/* QLogic qedr NIC Driver
 * Copyright (c) 2015-2016  QLogic Corporation
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
 *        disclaimer in the करोcumentation and /or other materials
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
#अगर_अघोषित __QED_HSI_RDMA__
#घोषणा __QED_HSI_RDMA__

#समावेश <linux/qed/rdma_common.h>

/* rdma completion notअगरication queue element */
काष्ठा rdma_cnqe अणु
	काष्ठा regpair	cq_handle;
पूर्ण;

काष्ठा rdma_cqe_responder अणु
	काष्ठा regpair srq_wr_id;
	काष्ठा regpair qp_handle;
	__le32 imm_data_or_inv_r_Key;
	__le32 length;
	__le32 imm_data_hi;
	__le16 rq_cons_or_srq_id;
	u8 flags;
#घोषणा RDMA_CQE_RESPONDER_TOGGLE_BIT_MASK  0x1
#घोषणा RDMA_CQE_RESPONDER_TOGGLE_BIT_SHIFT 0
#घोषणा RDMA_CQE_RESPONDER_TYPE_MASK        0x3
#घोषणा RDMA_CQE_RESPONDER_TYPE_SHIFT       1
#घोषणा RDMA_CQE_RESPONDER_INV_FLG_MASK     0x1
#घोषणा RDMA_CQE_RESPONDER_INV_FLG_SHIFT    3
#घोषणा RDMA_CQE_RESPONDER_IMM_FLG_MASK     0x1
#घोषणा RDMA_CQE_RESPONDER_IMM_FLG_SHIFT    4
#घोषणा RDMA_CQE_RESPONDER_RDMA_FLG_MASK    0x1
#घोषणा RDMA_CQE_RESPONDER_RDMA_FLG_SHIFT   5
#घोषणा RDMA_CQE_RESPONDER_RESERVED2_MASK   0x3
#घोषणा RDMA_CQE_RESPONDER_RESERVED2_SHIFT  6
	u8 status;
पूर्ण;

काष्ठा rdma_cqe_requester अणु
	__le16 sq_cons;
	__le16 reserved0;
	__le32 reserved1;
	काष्ठा regpair qp_handle;
	काष्ठा regpair reserved2;
	__le32 reserved3;
	__le16 reserved4;
	u8 flags;
#घोषणा RDMA_CQE_REQUESTER_TOGGLE_BIT_MASK  0x1
#घोषणा RDMA_CQE_REQUESTER_TOGGLE_BIT_SHIFT 0
#घोषणा RDMA_CQE_REQUESTER_TYPE_MASK        0x3
#घोषणा RDMA_CQE_REQUESTER_TYPE_SHIFT       1
#घोषणा RDMA_CQE_REQUESTER_RESERVED5_MASK   0x1F
#घोषणा RDMA_CQE_REQUESTER_RESERVED5_SHIFT  3
	u8 status;
पूर्ण;

काष्ठा rdma_cqe_common अणु
	काष्ठा regpair reserved0;
	काष्ठा regpair qp_handle;
	__le16 reserved1[7];
	u8 flags;
#घोषणा RDMA_CQE_COMMON_TOGGLE_BIT_MASK  0x1
#घोषणा RDMA_CQE_COMMON_TOGGLE_BIT_SHIFT 0
#घोषणा RDMA_CQE_COMMON_TYPE_MASK        0x3
#घोषणा RDMA_CQE_COMMON_TYPE_SHIFT       1
#घोषणा RDMA_CQE_COMMON_RESERVED2_MASK   0x1F
#घोषणा RDMA_CQE_COMMON_RESERVED2_SHIFT  3
	u8 status;
पूर्ण;

/* rdma completion queue element */
जोड़ rdma_cqe अणु
	काष्ठा rdma_cqe_responder resp;
	काष्ठा rdma_cqe_requester req;
	काष्ठा rdma_cqe_common cmn;
पूर्ण;

/* * CQE requester status क्रमागतeration */
क्रमागत rdma_cqe_requester_status_क्रमागत अणु
	RDMA_CQE_REQ_STS_OK,
	RDMA_CQE_REQ_STS_BAD_RESPONSE_ERR,
	RDMA_CQE_REQ_STS_LOCAL_LENGTH_ERR,
	RDMA_CQE_REQ_STS_LOCAL_QP_OPERATION_ERR,
	RDMA_CQE_REQ_STS_LOCAL_PROTECTION_ERR,
	RDMA_CQE_REQ_STS_MEMORY_MGT_OPERATION_ERR,
	RDMA_CQE_REQ_STS_REMOTE_INVALID_REQUEST_ERR,
	RDMA_CQE_REQ_STS_REMOTE_ACCESS_ERR,
	RDMA_CQE_REQ_STS_REMOTE_OPERATION_ERR,
	RDMA_CQE_REQ_STS_RNR_NAK_RETRY_CNT_ERR,
	RDMA_CQE_REQ_STS_TRANSPORT_RETRY_CNT_ERR,
	RDMA_CQE_REQ_STS_WORK_REQUEST_FLUSHED_ERR,
	RDMA_CQE_REQ_STS_XRC_VOILATION_ERR,
	RDMA_CQE_REQ_STS_संक_त्रुटि,
	MAX_RDMA_CQE_REQUESTER_STATUS_ENUM
पूर्ण;

/* CQE responder status क्रमागतeration */
क्रमागत rdma_cqe_responder_status_क्रमागत अणु
	RDMA_CQE_RESP_STS_OK,
	RDMA_CQE_RESP_STS_LOCAL_ACCESS_ERR,
	RDMA_CQE_RESP_STS_LOCAL_LENGTH_ERR,
	RDMA_CQE_RESP_STS_LOCAL_QP_OPERATION_ERR,
	RDMA_CQE_RESP_STS_LOCAL_PROTECTION_ERR,
	RDMA_CQE_RESP_STS_MEMORY_MGT_OPERATION_ERR,
	RDMA_CQE_RESP_STS_REMOTE_INVALID_REQUEST_ERR,
	RDMA_CQE_RESP_STS_WORK_REQUEST_FLUSHED_ERR,
	MAX_RDMA_CQE_RESPONDER_STATUS_ENUM
पूर्ण;

/* CQE type क्रमागतeration */
क्रमागत rdma_cqe_type अणु
	RDMA_CQE_TYPE_REQUESTER,
	RDMA_CQE_TYPE_RESPONDER_RQ,
	RDMA_CQE_TYPE_RESPONDER_SRQ,
	RDMA_CQE_TYPE_RESPONDER_XRC_SRQ,
	RDMA_CQE_TYPE_INVALID,
	MAX_RDMA_CQE_TYPE
पूर्ण;

काष्ठा rdma_sq_sge अणु
	__le32 length;
	काष्ठा regpair	addr;
	__le32 l_key;
पूर्ण;

काष्ठा rdma_rq_sge अणु
	काष्ठा regpair addr;
	__le32 length;
	__le32 flags;
#घोषणा RDMA_RQ_SGE_L_KEY_LO_MASK   0x3FFFFFF
#घोषणा RDMA_RQ_SGE_L_KEY_LO_SHIFT  0
#घोषणा RDMA_RQ_SGE_NUM_SGES_MASK   0x7
#घोषणा RDMA_RQ_SGE_NUM_SGES_SHIFT  26
#घोषणा RDMA_RQ_SGE_L_KEY_HI_MASK   0x7
#घोषणा RDMA_RQ_SGE_L_KEY_HI_SHIFT  29
पूर्ण;

काष्ठा rdma_srq_wqe_header अणु
	काष्ठा regpair wr_id;
	u8 num_sges /* number of SGEs in WQE */;
	u8 reserved2[7];
पूर्ण;

काष्ठा rdma_srq_sge अणु
	काष्ठा regpair addr;
	__le32 length;
	__le32 l_key;
पूर्ण;

जोड़ rdma_srq_elm अणु
	काष्ठा rdma_srq_wqe_header header;
	काष्ठा rdma_srq_sge sge;
पूर्ण;

/* Rdma करोorbell data क्रम flags update */
काष्ठा rdma_pwm_flags_data अणु
	__le16 icid; /* पूर्णांकernal CID */
	u8 agg_flags; /* aggregative flags */
	u8 reserved;
पूर्ण;

/* Rdma करोorbell data क्रम SQ and RQ */
काष्ठा rdma_pwm_val16_data अणु
	__le16 icid;
	__le16 value;
पूर्ण;

जोड़ rdma_pwm_val16_data_जोड़ अणु
	काष्ठा rdma_pwm_val16_data as_काष्ठा;
	__le32 as_dword;
पूर्ण;

/* Rdma करोorbell data क्रम CQ */
काष्ठा rdma_pwm_val32_data अणु
	__le16 icid;
	u8 agg_flags;
	u8 params;
#घोषणा RDMA_PWM_VAL32_DATA_AGG_CMD_MASK		0x3
#घोषणा RDMA_PWM_VAL32_DATA_AGG_CMD_SHIFT		0
#घोषणा RDMA_PWM_VAL32_DATA_BYPASS_EN_MASK		0x1
#घोषणा RDMA_PWM_VAL32_DATA_BYPASS_EN_SHIFT		2
#घोषणा RDMA_PWM_VAL32_DATA_CONN_TYPE_IS_IWARP_MASK	0x1
#घोषणा RDMA_PWM_VAL32_DATA_CONN_TYPE_IS_IWARP_SHIFT	3
#घोषणा RDMA_PWM_VAL32_DATA_SET_16B_VAL_MASK		0x1
#घोषणा RDMA_PWM_VAL32_DATA_SET_16B_VAL_SHIFT		4
#घोषणा RDMA_PWM_VAL32_DATA_RESERVED_MASK		0x7
#घोषणा RDMA_PWM_VAL32_DATA_RESERVED_SHIFT		5
	__le32 value;
पूर्ण;

/* DIF Block size options */
क्रमागत rdma_dअगर_block_size अणु
	RDMA_DIF_BLOCK_512 = 0,
	RDMA_DIF_BLOCK_4096 = 1,
	MAX_RDMA_DIF_BLOCK_SIZE
पूर्ण;

/* DIF CRC initial value */
क्रमागत rdma_dअगर_crc_seed अणु
	RDMA_DIF_CRC_SEED_0000 = 0,
	RDMA_DIF_CRC_SEED_FFFF = 1,
	MAX_RDMA_DIF_CRC_SEED
पूर्ण;

/* RDMA DIF Error Result Structure */
काष्ठा rdma_dअगर_error_result अणु
	__le32 error_पूर्णांकervals;
	__le32 dअगर_error_1st_पूर्णांकerval;
	u8 flags;
#घोषणा RDMA_DIF_ERROR_RESULT_DIF_ERROR_TYPE_CRC_MASK      0x1
#घोषणा RDMA_DIF_ERROR_RESULT_DIF_ERROR_TYPE_CRC_SHIFT     0
#घोषणा RDMA_DIF_ERROR_RESULT_DIF_ERROR_TYPE_APP_TAG_MASK  0x1
#घोषणा RDMA_DIF_ERROR_RESULT_DIF_ERROR_TYPE_APP_TAG_SHIFT 1
#घोषणा RDMA_DIF_ERROR_RESULT_DIF_ERROR_TYPE_REF_TAG_MASK  0x1
#घोषणा RDMA_DIF_ERROR_RESULT_DIF_ERROR_TYPE_REF_TAG_SHIFT 2
#घोषणा RDMA_DIF_ERROR_RESULT_RESERVED0_MASK               0xF
#घोषणा RDMA_DIF_ERROR_RESULT_RESERVED0_SHIFT              3
#घोषणा RDMA_DIF_ERROR_RESULT_TOGGLE_BIT_MASK              0x1
#घोषणा RDMA_DIF_ERROR_RESULT_TOGGLE_BIT_SHIFT             7
	u8 reserved1[55];
पूर्ण;

/* DIF IO direction */
क्रमागत rdma_dअगर_io_direction_flg अणु
	RDMA_DIF_सूची_RX = 0,
	RDMA_DIF_सूची_TX = 1,
	MAX_RDMA_DIF_IO_सूचीECTION_FLG
पूर्ण;

काष्ठा rdma_dअगर_params अणु
	__le32 base_ref_tag;
	__le16 app_tag;
	__le16 app_tag_mask;
	__le16 runt_crc_value;
	__le16 flags;
#घोषणा RDMA_DIF_PARAMS_IO_सूचीECTION_FLG_MASK    0x1
#घोषणा RDMA_DIF_PARAMS_IO_सूचीECTION_FLG_SHIFT   0
#घोषणा RDMA_DIF_PARAMS_BLOCK_SIZE_MASK          0x1
#घोषणा RDMA_DIF_PARAMS_BLOCK_SIZE_SHIFT         1
#घोषणा RDMA_DIF_PARAMS_RUNT_VALID_FLG_MASK      0x1
#घोषणा RDMA_DIF_PARAMS_RUNT_VALID_FLG_SHIFT     2
#घोषणा RDMA_DIF_PARAMS_VALIDATE_CRC_GUARD_MASK  0x1
#घोषणा RDMA_DIF_PARAMS_VALIDATE_CRC_GUARD_SHIFT 3
#घोषणा RDMA_DIF_PARAMS_VALIDATE_REF_TAG_MASK    0x1
#घोषणा RDMA_DIF_PARAMS_VALIDATE_REF_TAG_SHIFT   4
#घोषणा RDMA_DIF_PARAMS_VALIDATE_APP_TAG_MASK    0x1
#घोषणा RDMA_DIF_PARAMS_VALIDATE_APP_TAG_SHIFT   5
#घोषणा RDMA_DIF_PARAMS_CRC_SEED_MASK            0x1
#घोषणा RDMA_DIF_PARAMS_CRC_SEED_SHIFT           6
#घोषणा RDMA_DIF_PARAMS_RX_REF_TAG_CONST_MASK    0x1
#घोषणा RDMA_DIF_PARAMS_RX_REF_TAG_CONST_SHIFT   7
#घोषणा RDMA_DIF_PARAMS_BLOCK_GUARD_TYPE_MASK    0x1
#घोषणा RDMA_DIF_PARAMS_BLOCK_GUARD_TYPE_SHIFT   8
#घोषणा RDMA_DIF_PARAMS_APP_ESCAPE_MASK          0x1
#घोषणा RDMA_DIF_PARAMS_APP_ESCAPE_SHIFT         9
#घोषणा RDMA_DIF_PARAMS_REF_ESCAPE_MASK          0x1
#घोषणा RDMA_DIF_PARAMS_REF_ESCAPE_SHIFT         10
#घोषणा RDMA_DIF_PARAMS_RESERVED4_MASK           0x1F
#घोषणा RDMA_DIF_PARAMS_RESERVED4_SHIFT          11
	__le32 reserved5;
पूर्ण;


काष्ठा rdma_sq_atomic_wqe अणु
	__le32 reserved1;
	__le32 length;
	__le32 xrc_srq;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_ATOMIC_WQE_COMP_FLG_MASK         0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_COMP_FLG_SHIFT        0
#घोषणा RDMA_SQ_ATOMIC_WQE_RD_FENCE_FLG_MASK     0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_RD_FENCE_FLG_SHIFT    1
#घोषणा RDMA_SQ_ATOMIC_WQE_INV_FENCE_FLG_MASK    0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_INV_FENCE_FLG_SHIFT   2
#घोषणा RDMA_SQ_ATOMIC_WQE_SE_FLG_MASK           0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_SE_FLG_SHIFT          3
#घोषणा RDMA_SQ_ATOMIC_WQE_INLINE_FLG_MASK       0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_INLINE_FLG_SHIFT      4
#घोषणा RDMA_SQ_ATOMIC_WQE_DIF_ON_HOST_FLG_MASK  0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_DIF_ON_HOST_FLG_SHIFT 5
#घोषणा RDMA_SQ_ATOMIC_WQE_RESERVED0_MASK        0x3
#घोषणा RDMA_SQ_ATOMIC_WQE_RESERVED0_SHIFT       6
	u8 wqe_size;
	u8 prev_wqe_size;
	काष्ठा regpair remote_va;
	__le32 r_key;
	__le32 reserved2;
	काष्ठा regpair cmp_data;
	काष्ठा regpair swap_data;
पूर्ण;

/* First element (16 bytes) of atomic wqe */
काष्ठा rdma_sq_atomic_wqe_1st अणु
	__le32 reserved1;
	__le32 length;
	__le32 xrc_srq;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_COMP_FLG_MASK       0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_COMP_FLG_SHIFT      0
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_RD_FENCE_FLG_MASK   0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_RD_FENCE_FLG_SHIFT  1
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_INV_FENCE_FLG_MASK  0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_INV_FENCE_FLG_SHIFT 2
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_SE_FLG_MASK         0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_SE_FLG_SHIFT        3
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_INLINE_FLG_MASK     0x1
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_INLINE_FLG_SHIFT    4
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_RESERVED0_MASK      0x7
#घोषणा RDMA_SQ_ATOMIC_WQE_1ST_RESERVED0_SHIFT     5
	u8 wqe_size;
	u8 prev_wqe_size;
पूर्ण;

/* Second element (16 bytes) of atomic wqe */
काष्ठा rdma_sq_atomic_wqe_2nd अणु
	काष्ठा regpair remote_va;
	__le32 r_key;
	__le32 reserved2;
पूर्ण;

/* Third element (16 bytes) of atomic wqe */
काष्ठा rdma_sq_atomic_wqe_3rd अणु
	काष्ठा regpair cmp_data;
	काष्ठा regpair swap_data;
पूर्ण;

काष्ठा rdma_sq_bind_wqe अणु
	काष्ठा regpair addr;
	__le32 l_key;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_BIND_WQE_COMP_FLG_MASK       0x1
#घोषणा RDMA_SQ_BIND_WQE_COMP_FLG_SHIFT      0
#घोषणा RDMA_SQ_BIND_WQE_RD_FENCE_FLG_MASK   0x1
#घोषणा RDMA_SQ_BIND_WQE_RD_FENCE_FLG_SHIFT  1
#घोषणा RDMA_SQ_BIND_WQE_INV_FENCE_FLG_MASK  0x1
#घोषणा RDMA_SQ_BIND_WQE_INV_FENCE_FLG_SHIFT 2
#घोषणा RDMA_SQ_BIND_WQE_SE_FLG_MASK         0x1
#घोषणा RDMA_SQ_BIND_WQE_SE_FLG_SHIFT        3
#घोषणा RDMA_SQ_BIND_WQE_INLINE_FLG_MASK     0x1
#घोषणा RDMA_SQ_BIND_WQE_INLINE_FLG_SHIFT    4
#घोषणा RDMA_SQ_BIND_WQE_DIF_ON_HOST_FLG_MASK  0x1
#घोषणा RDMA_SQ_BIND_WQE_DIF_ON_HOST_FLG_SHIFT 5
#घोषणा RDMA_SQ_BIND_WQE_RESERVED0_MASK      0x3
#घोषणा RDMA_SQ_BIND_WQE_RESERVED0_SHIFT     6
	u8 wqe_size;
	u8 prev_wqe_size;
	u8 bind_ctrl;
#घोषणा RDMA_SQ_BIND_WQE_ZERO_BASED_MASK     0x1
#घोषणा RDMA_SQ_BIND_WQE_ZERO_BASED_SHIFT    0
#घोषणा RDMA_SQ_BIND_WQE_RESERVED1_MASK        0x7F
#घोषणा RDMA_SQ_BIND_WQE_RESERVED1_SHIFT       1
	u8 access_ctrl;
#घोषणा RDMA_SQ_BIND_WQE_REMOTE_READ_MASK    0x1
#घोषणा RDMA_SQ_BIND_WQE_REMOTE_READ_SHIFT   0
#घोषणा RDMA_SQ_BIND_WQE_REMOTE_WRITE_MASK   0x1
#घोषणा RDMA_SQ_BIND_WQE_REMOTE_WRITE_SHIFT  1
#घोषणा RDMA_SQ_BIND_WQE_ENABLE_ATOMIC_MASK  0x1
#घोषणा RDMA_SQ_BIND_WQE_ENABLE_ATOMIC_SHIFT 2
#घोषणा RDMA_SQ_BIND_WQE_LOCAL_READ_MASK     0x1
#घोषणा RDMA_SQ_BIND_WQE_LOCAL_READ_SHIFT    3
#घोषणा RDMA_SQ_BIND_WQE_LOCAL_WRITE_MASK    0x1
#घोषणा RDMA_SQ_BIND_WQE_LOCAL_WRITE_SHIFT   4
#घोषणा RDMA_SQ_BIND_WQE_RESERVED2_MASK      0x7
#घोषणा RDMA_SQ_BIND_WQE_RESERVED2_SHIFT     5
	u8 reserved3;
	u8 length_hi;
	__le32 length_lo;
	__le32 parent_l_key;
	__le32 reserved4;
	काष्ठा rdma_dअगर_params dअगर_params;
पूर्ण;

/* First element (16 bytes) of bind wqe */
काष्ठा rdma_sq_bind_wqe_1st अणु
	काष्ठा regpair addr;
	__le32 l_key;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_BIND_WQE_1ST_COMP_FLG_MASK       0x1
#घोषणा RDMA_SQ_BIND_WQE_1ST_COMP_FLG_SHIFT      0
#घोषणा RDMA_SQ_BIND_WQE_1ST_RD_FENCE_FLG_MASK   0x1
#घोषणा RDMA_SQ_BIND_WQE_1ST_RD_FENCE_FLG_SHIFT  1
#घोषणा RDMA_SQ_BIND_WQE_1ST_INV_FENCE_FLG_MASK  0x1
#घोषणा RDMA_SQ_BIND_WQE_1ST_INV_FENCE_FLG_SHIFT 2
#घोषणा RDMA_SQ_BIND_WQE_1ST_SE_FLG_MASK         0x1
#घोषणा RDMA_SQ_BIND_WQE_1ST_SE_FLG_SHIFT        3
#घोषणा RDMA_SQ_BIND_WQE_1ST_INLINE_FLG_MASK     0x1
#घोषणा RDMA_SQ_BIND_WQE_1ST_INLINE_FLG_SHIFT    4
#घोषणा RDMA_SQ_BIND_WQE_1ST_RESERVED0_MASK      0x7
#घोषणा RDMA_SQ_BIND_WQE_1ST_RESERVED0_SHIFT     5
	u8 wqe_size;
	u8 prev_wqe_size;
पूर्ण;

/* Second element (16 bytes) of bind wqe */
काष्ठा rdma_sq_bind_wqe_2nd अणु
	u8 bind_ctrl;
#घोषणा RDMA_SQ_BIND_WQE_2ND_ZERO_BASED_MASK     0x1
#घोषणा RDMA_SQ_BIND_WQE_2ND_ZERO_BASED_SHIFT    0
#घोषणा RDMA_SQ_BIND_WQE_2ND_RESERVED1_MASK      0x7F
#घोषणा RDMA_SQ_BIND_WQE_2ND_RESERVED1_SHIFT     1
	u8 access_ctrl;
#घोषणा RDMA_SQ_BIND_WQE_2ND_REMOTE_READ_MASK    0x1
#घोषणा RDMA_SQ_BIND_WQE_2ND_REMOTE_READ_SHIFT   0
#घोषणा RDMA_SQ_BIND_WQE_2ND_REMOTE_WRITE_MASK   0x1
#घोषणा RDMA_SQ_BIND_WQE_2ND_REMOTE_WRITE_SHIFT  1
#घोषणा RDMA_SQ_BIND_WQE_2ND_ENABLE_ATOMIC_MASK  0x1
#घोषणा RDMA_SQ_BIND_WQE_2ND_ENABLE_ATOMIC_SHIFT 2
#घोषणा RDMA_SQ_BIND_WQE_2ND_LOCAL_READ_MASK     0x1
#घोषणा RDMA_SQ_BIND_WQE_2ND_LOCAL_READ_SHIFT    3
#घोषणा RDMA_SQ_BIND_WQE_2ND_LOCAL_WRITE_MASK    0x1
#घोषणा RDMA_SQ_BIND_WQE_2ND_LOCAL_WRITE_SHIFT   4
#घोषणा RDMA_SQ_BIND_WQE_2ND_RESERVED2_MASK      0x7
#घोषणा RDMA_SQ_BIND_WQE_2ND_RESERVED2_SHIFT     5
	u8 reserved3;
	u8 length_hi;
	__le32 length_lo;
	__le32 parent_l_key;
	__le32 reserved4;
पूर्ण;

/* Third element (16 bytes) of bind wqe */
काष्ठा rdma_sq_bind_wqe_3rd अणु
	काष्ठा rdma_dअगर_params dअगर_params;
पूर्ण;

/* Structure with only the SQ WQE common
 * fields. Size is of one SQ element (16B)
 */
काष्ठा rdma_sq_common_wqe अणु
	__le32 reserved1[3];
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_COMMON_WQE_COMP_FLG_MASK       0x1
#घोषणा RDMA_SQ_COMMON_WQE_COMP_FLG_SHIFT      0
#घोषणा RDMA_SQ_COMMON_WQE_RD_FENCE_FLG_MASK   0x1
#घोषणा RDMA_SQ_COMMON_WQE_RD_FENCE_FLG_SHIFT  1
#घोषणा RDMA_SQ_COMMON_WQE_INV_FENCE_FLG_MASK  0x1
#घोषणा RDMA_SQ_COMMON_WQE_INV_FENCE_FLG_SHIFT 2
#घोषणा RDMA_SQ_COMMON_WQE_SE_FLG_MASK         0x1
#घोषणा RDMA_SQ_COMMON_WQE_SE_FLG_SHIFT        3
#घोषणा RDMA_SQ_COMMON_WQE_INLINE_FLG_MASK     0x1
#घोषणा RDMA_SQ_COMMON_WQE_INLINE_FLG_SHIFT    4
#घोषणा RDMA_SQ_COMMON_WQE_RESERVED0_MASK      0x7
#घोषणा RDMA_SQ_COMMON_WQE_RESERVED0_SHIFT     5
	u8 wqe_size;
	u8 prev_wqe_size;
पूर्ण;

काष्ठा rdma_sq_fmr_wqe अणु
	काष्ठा regpair addr;
	__le32 l_key;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_FMR_WQE_COMP_FLG_MASK                0x1
#घोषणा RDMA_SQ_FMR_WQE_COMP_FLG_SHIFT               0
#घोषणा RDMA_SQ_FMR_WQE_RD_FENCE_FLG_MASK            0x1
#घोषणा RDMA_SQ_FMR_WQE_RD_FENCE_FLG_SHIFT           1
#घोषणा RDMA_SQ_FMR_WQE_INV_FENCE_FLG_MASK           0x1
#घोषणा RDMA_SQ_FMR_WQE_INV_FENCE_FLG_SHIFT          2
#घोषणा RDMA_SQ_FMR_WQE_SE_FLG_MASK                  0x1
#घोषणा RDMA_SQ_FMR_WQE_SE_FLG_SHIFT                 3
#घोषणा RDMA_SQ_FMR_WQE_INLINE_FLG_MASK              0x1
#घोषणा RDMA_SQ_FMR_WQE_INLINE_FLG_SHIFT             4
#घोषणा RDMA_SQ_FMR_WQE_DIF_ON_HOST_FLG_MASK         0x1
#घोषणा RDMA_SQ_FMR_WQE_DIF_ON_HOST_FLG_SHIFT        5
#घोषणा RDMA_SQ_FMR_WQE_RESERVED0_MASK               0x3
#घोषणा RDMA_SQ_FMR_WQE_RESERVED0_SHIFT              6
	u8 wqe_size;
	u8 prev_wqe_size;
	u8 fmr_ctrl;
#घोषणा RDMA_SQ_FMR_WQE_PAGE_SIZE_LOG_MASK           0x1F
#घोषणा RDMA_SQ_FMR_WQE_PAGE_SIZE_LOG_SHIFT          0
#घोषणा RDMA_SQ_FMR_WQE_ZERO_BASED_MASK              0x1
#घोषणा RDMA_SQ_FMR_WQE_ZERO_BASED_SHIFT             5
#घोषणा RDMA_SQ_FMR_WQE_BIND_EN_MASK                 0x1
#घोषणा RDMA_SQ_FMR_WQE_BIND_EN_SHIFT                6
#घोषणा RDMA_SQ_FMR_WQE_RESERVED1_MASK               0x1
#घोषणा RDMA_SQ_FMR_WQE_RESERVED1_SHIFT              7
	u8 access_ctrl;
#घोषणा RDMA_SQ_FMR_WQE_REMOTE_READ_MASK             0x1
#घोषणा RDMA_SQ_FMR_WQE_REMOTE_READ_SHIFT            0
#घोषणा RDMA_SQ_FMR_WQE_REMOTE_WRITE_MASK            0x1
#घोषणा RDMA_SQ_FMR_WQE_REMOTE_WRITE_SHIFT           1
#घोषणा RDMA_SQ_FMR_WQE_ENABLE_ATOMIC_MASK           0x1
#घोषणा RDMA_SQ_FMR_WQE_ENABLE_ATOMIC_SHIFT          2
#घोषणा RDMA_SQ_FMR_WQE_LOCAL_READ_MASK              0x1
#घोषणा RDMA_SQ_FMR_WQE_LOCAL_READ_SHIFT             3
#घोषणा RDMA_SQ_FMR_WQE_LOCAL_WRITE_MASK             0x1
#घोषणा RDMA_SQ_FMR_WQE_LOCAL_WRITE_SHIFT            4
#घोषणा RDMA_SQ_FMR_WQE_RESERVED2_MASK               0x7
#घोषणा RDMA_SQ_FMR_WQE_RESERVED2_SHIFT              5
	u8 reserved3;
	u8 length_hi;
	__le32 length_lo;
	काष्ठा regpair pbl_addr;
पूर्ण;

/* First element (16 bytes) of fmr wqe */
काष्ठा rdma_sq_fmr_wqe_1st अणु
	काष्ठा regpair addr;
	__le32 l_key;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_FMR_WQE_1ST_COMP_FLG_MASK         0x1
#घोषणा RDMA_SQ_FMR_WQE_1ST_COMP_FLG_SHIFT        0
#घोषणा RDMA_SQ_FMR_WQE_1ST_RD_FENCE_FLG_MASK     0x1
#घोषणा RDMA_SQ_FMR_WQE_1ST_RD_FENCE_FLG_SHIFT    1
#घोषणा RDMA_SQ_FMR_WQE_1ST_INV_FENCE_FLG_MASK    0x1
#घोषणा RDMA_SQ_FMR_WQE_1ST_INV_FENCE_FLG_SHIFT   2
#घोषणा RDMA_SQ_FMR_WQE_1ST_SE_FLG_MASK           0x1
#घोषणा RDMA_SQ_FMR_WQE_1ST_SE_FLG_SHIFT          3
#घोषणा RDMA_SQ_FMR_WQE_1ST_INLINE_FLG_MASK       0x1
#घोषणा RDMA_SQ_FMR_WQE_1ST_INLINE_FLG_SHIFT      4
#घोषणा RDMA_SQ_FMR_WQE_1ST_DIF_ON_HOST_FLG_MASK  0x1
#घोषणा RDMA_SQ_FMR_WQE_1ST_DIF_ON_HOST_FLG_SHIFT 5
#घोषणा RDMA_SQ_FMR_WQE_1ST_RESERVED0_MASK        0x3
#घोषणा RDMA_SQ_FMR_WQE_1ST_RESERVED0_SHIFT       6
	u8 wqe_size;
	u8 prev_wqe_size;
पूर्ण;

/* Second element (16 bytes) of fmr wqe */
काष्ठा rdma_sq_fmr_wqe_2nd अणु
	u8 fmr_ctrl;
#घोषणा RDMA_SQ_FMR_WQE_2ND_PAGE_SIZE_LOG_MASK  0x1F
#घोषणा RDMA_SQ_FMR_WQE_2ND_PAGE_SIZE_LOG_SHIFT 0
#घोषणा RDMA_SQ_FMR_WQE_2ND_ZERO_BASED_MASK     0x1
#घोषणा RDMA_SQ_FMR_WQE_2ND_ZERO_BASED_SHIFT    5
#घोषणा RDMA_SQ_FMR_WQE_2ND_BIND_EN_MASK        0x1
#घोषणा RDMA_SQ_FMR_WQE_2ND_BIND_EN_SHIFT       6
#घोषणा RDMA_SQ_FMR_WQE_2ND_RESERVED1_MASK      0x1
#घोषणा RDMA_SQ_FMR_WQE_2ND_RESERVED1_SHIFT     7
	u8 access_ctrl;
#घोषणा RDMA_SQ_FMR_WQE_2ND_REMOTE_READ_MASK    0x1
#घोषणा RDMA_SQ_FMR_WQE_2ND_REMOTE_READ_SHIFT   0
#घोषणा RDMA_SQ_FMR_WQE_2ND_REMOTE_WRITE_MASK   0x1
#घोषणा RDMA_SQ_FMR_WQE_2ND_REMOTE_WRITE_SHIFT  1
#घोषणा RDMA_SQ_FMR_WQE_2ND_ENABLE_ATOMIC_MASK  0x1
#घोषणा RDMA_SQ_FMR_WQE_2ND_ENABLE_ATOMIC_SHIFT 2
#घोषणा RDMA_SQ_FMR_WQE_2ND_LOCAL_READ_MASK     0x1
#घोषणा RDMA_SQ_FMR_WQE_2ND_LOCAL_READ_SHIFT    3
#घोषणा RDMA_SQ_FMR_WQE_2ND_LOCAL_WRITE_MASK    0x1
#घोषणा RDMA_SQ_FMR_WQE_2ND_LOCAL_WRITE_SHIFT   4
#घोषणा RDMA_SQ_FMR_WQE_2ND_RESERVED2_MASK      0x7
#घोषणा RDMA_SQ_FMR_WQE_2ND_RESERVED2_SHIFT     5
	u8 reserved3;
	u8 length_hi;
	__le32 length_lo;
	काष्ठा regpair pbl_addr;
पूर्ण;


काष्ठा rdma_sq_local_inv_wqe अणु
	काष्ठा regpair reserved;
	__le32 inv_l_key;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_LOCAL_INV_WQE_COMP_FLG_MASK         0x1
#घोषणा RDMA_SQ_LOCAL_INV_WQE_COMP_FLG_SHIFT        0
#घोषणा RDMA_SQ_LOCAL_INV_WQE_RD_FENCE_FLG_MASK     0x1
#घोषणा RDMA_SQ_LOCAL_INV_WQE_RD_FENCE_FLG_SHIFT    1
#घोषणा RDMA_SQ_LOCAL_INV_WQE_INV_FENCE_FLG_MASK    0x1
#घोषणा RDMA_SQ_LOCAL_INV_WQE_INV_FENCE_FLG_SHIFT   2
#घोषणा RDMA_SQ_LOCAL_INV_WQE_SE_FLG_MASK           0x1
#घोषणा RDMA_SQ_LOCAL_INV_WQE_SE_FLG_SHIFT          3
#घोषणा RDMA_SQ_LOCAL_INV_WQE_INLINE_FLG_MASK       0x1
#घोषणा RDMA_SQ_LOCAL_INV_WQE_INLINE_FLG_SHIFT      4
#घोषणा RDMA_SQ_LOCAL_INV_WQE_DIF_ON_HOST_FLG_MASK  0x1
#घोषणा RDMA_SQ_LOCAL_INV_WQE_DIF_ON_HOST_FLG_SHIFT 5
#घोषणा RDMA_SQ_LOCAL_INV_WQE_RESERVED0_MASK        0x3
#घोषणा RDMA_SQ_LOCAL_INV_WQE_RESERVED0_SHIFT       6
	u8 wqe_size;
	u8 prev_wqe_size;
पूर्ण;

काष्ठा rdma_sq_rdma_wqe अणु
	__le32 imm_data;
	__le32 length;
	__le32 xrc_srq;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_RDMA_WQE_COMP_FLG_MASK		0x1
#घोषणा RDMA_SQ_RDMA_WQE_COMP_FLG_SHIFT		0
#घोषणा RDMA_SQ_RDMA_WQE_RD_FENCE_FLG_MASK	0x1
#घोषणा RDMA_SQ_RDMA_WQE_RD_FENCE_FLG_SHIFT	1
#घोषणा RDMA_SQ_RDMA_WQE_INV_FENCE_FLG_MASK	0x1
#घोषणा RDMA_SQ_RDMA_WQE_INV_FENCE_FLG_SHIFT	2
#घोषणा RDMA_SQ_RDMA_WQE_SE_FLG_MASK		0x1
#घोषणा RDMA_SQ_RDMA_WQE_SE_FLG_SHIFT		3
#घोषणा RDMA_SQ_RDMA_WQE_INLINE_FLG_MASK	0x1
#घोषणा RDMA_SQ_RDMA_WQE_INLINE_FLG_SHIFT	4
#घोषणा RDMA_SQ_RDMA_WQE_DIF_ON_HOST_FLG_MASK	0x1
#घोषणा RDMA_SQ_RDMA_WQE_DIF_ON_HOST_FLG_SHIFT	5
#घोषणा RDMA_SQ_RDMA_WQE_READ_INV_FLG_MASK	0x1
#घोषणा RDMA_SQ_RDMA_WQE_READ_INV_FLG_SHIFT	6
#घोषणा RDMA_SQ_RDMA_WQE_RESERVED1_MASK        0x1
#घोषणा RDMA_SQ_RDMA_WQE_RESERVED1_SHIFT       7
	u8 wqe_size;
	u8 prev_wqe_size;
	काष्ठा regpair remote_va;
	__le32 r_key;
	u8 dअगर_flags;
#घोषणा RDMA_SQ_RDMA_WQE_DIF_BLOCK_SIZE_MASK            0x1
#घोषणा RDMA_SQ_RDMA_WQE_DIF_BLOCK_SIZE_SHIFT           0
#घोषणा RDMA_SQ_RDMA_WQE_RESERVED2_MASK        0x7F
#घोषणा RDMA_SQ_RDMA_WQE_RESERVED2_SHIFT       1
	u8 reserved3[3];
पूर्ण;

/* First element (16 bytes) of rdma wqe */
काष्ठा rdma_sq_rdma_wqe_1st अणु
	__le32 imm_data;
	__le32 length;
	__le32 xrc_srq;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_RDMA_WQE_1ST_COMP_FLG_MASK         0x1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_COMP_FLG_SHIFT        0
#घोषणा RDMA_SQ_RDMA_WQE_1ST_RD_FENCE_FLG_MASK     0x1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_RD_FENCE_FLG_SHIFT    1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_INV_FENCE_FLG_MASK    0x1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_INV_FENCE_FLG_SHIFT   2
#घोषणा RDMA_SQ_RDMA_WQE_1ST_SE_FLG_MASK           0x1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_SE_FLG_SHIFT          3
#घोषणा RDMA_SQ_RDMA_WQE_1ST_INLINE_FLG_MASK       0x1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_INLINE_FLG_SHIFT      4
#घोषणा RDMA_SQ_RDMA_WQE_1ST_DIF_ON_HOST_FLG_MASK  0x1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_DIF_ON_HOST_FLG_SHIFT 5
#घोषणा RDMA_SQ_RDMA_WQE_1ST_READ_INV_FLG_MASK     0x1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_READ_INV_FLG_SHIFT    6
#घोषणा RDMA_SQ_RDMA_WQE_1ST_RESERVED0_MASK        0x1
#घोषणा RDMA_SQ_RDMA_WQE_1ST_RESERVED0_SHIFT       7
	u8 wqe_size;
	u8 prev_wqe_size;
पूर्ण;

/* Second element (16 bytes) of rdma wqe */
काष्ठा rdma_sq_rdma_wqe_2nd अणु
	काष्ठा regpair remote_va;
	__le32 r_key;
	u8 dअगर_flags;
#घोषणा RDMA_SQ_RDMA_WQE_2ND_DIF_BLOCK_SIZE_MASK         0x1
#घोषणा RDMA_SQ_RDMA_WQE_2ND_DIF_BLOCK_SIZE_SHIFT        0
#घोषणा RDMA_SQ_RDMA_WQE_2ND_DIF_FIRST_SEGMENT_FLG_MASK  0x1
#घोषणा RDMA_SQ_RDMA_WQE_2ND_DIF_FIRST_SEGMENT_FLG_SHIFT 1
#घोषणा RDMA_SQ_RDMA_WQE_2ND_DIF_LAST_SEGMENT_FLG_MASK   0x1
#घोषणा RDMA_SQ_RDMA_WQE_2ND_DIF_LAST_SEGMENT_FLG_SHIFT  2
#घोषणा RDMA_SQ_RDMA_WQE_2ND_RESERVED1_MASK              0x1F
#घोषणा RDMA_SQ_RDMA_WQE_2ND_RESERVED1_SHIFT             3
	u8 reserved2[3];
पूर्ण;

/* SQ WQE req type क्रमागतeration */
क्रमागत rdma_sq_req_type अणु
	RDMA_SQ_REQ_TYPE_SEND,
	RDMA_SQ_REQ_TYPE_SEND_WITH_IMM,
	RDMA_SQ_REQ_TYPE_SEND_WITH_INVALIDATE,
	RDMA_SQ_REQ_TYPE_RDMA_WR,
	RDMA_SQ_REQ_TYPE_RDMA_WR_WITH_IMM,
	RDMA_SQ_REQ_TYPE_RDMA_RD,
	RDMA_SQ_REQ_TYPE_ATOMIC_CMP_AND_SWAP,
	RDMA_SQ_REQ_TYPE_ATOMIC_ADD,
	RDMA_SQ_REQ_TYPE_LOCAL_INVALIDATE,
	RDMA_SQ_REQ_TYPE_FAST_MR,
	RDMA_SQ_REQ_TYPE_BIND,
	RDMA_SQ_REQ_TYPE_INVALID,
	MAX_RDMA_SQ_REQ_TYPE
पूर्ण;

काष्ठा rdma_sq_send_wqe अणु
	__le32 inv_key_or_imm_data;
	__le32 length;
	__le32 xrc_srq;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_SEND_WQE_COMP_FLG_MASK         0x1
#घोषणा RDMA_SQ_SEND_WQE_COMP_FLG_SHIFT        0
#घोषणा RDMA_SQ_SEND_WQE_RD_FENCE_FLG_MASK     0x1
#घोषणा RDMA_SQ_SEND_WQE_RD_FENCE_FLG_SHIFT    1
#घोषणा RDMA_SQ_SEND_WQE_INV_FENCE_FLG_MASK    0x1
#घोषणा RDMA_SQ_SEND_WQE_INV_FENCE_FLG_SHIFT   2
#घोषणा RDMA_SQ_SEND_WQE_SE_FLG_MASK           0x1
#घोषणा RDMA_SQ_SEND_WQE_SE_FLG_SHIFT          3
#घोषणा RDMA_SQ_SEND_WQE_INLINE_FLG_MASK       0x1
#घोषणा RDMA_SQ_SEND_WQE_INLINE_FLG_SHIFT      4
#घोषणा RDMA_SQ_SEND_WQE_DIF_ON_HOST_FLG_MASK  0x1
#घोषणा RDMA_SQ_SEND_WQE_DIF_ON_HOST_FLG_SHIFT 5
#घोषणा RDMA_SQ_SEND_WQE_RESERVED0_MASK        0x3
#घोषणा RDMA_SQ_SEND_WQE_RESERVED0_SHIFT       6
	u8 wqe_size;
	u8 prev_wqe_size;
	__le32 reserved1[4];
पूर्ण;

काष्ठा rdma_sq_send_wqe_1st अणु
	__le32 inv_key_or_imm_data;
	__le32 length;
	__le32 xrc_srq;
	u8 req_type;
	u8 flags;
#घोषणा RDMA_SQ_SEND_WQE_1ST_COMP_FLG_MASK       0x1
#घोषणा RDMA_SQ_SEND_WQE_1ST_COMP_FLG_SHIFT      0
#घोषणा RDMA_SQ_SEND_WQE_1ST_RD_FENCE_FLG_MASK   0x1
#घोषणा RDMA_SQ_SEND_WQE_1ST_RD_FENCE_FLG_SHIFT  1
#घोषणा RDMA_SQ_SEND_WQE_1ST_INV_FENCE_FLG_MASK  0x1
#घोषणा RDMA_SQ_SEND_WQE_1ST_INV_FENCE_FLG_SHIFT 2
#घोषणा RDMA_SQ_SEND_WQE_1ST_SE_FLG_MASK         0x1
#घोषणा RDMA_SQ_SEND_WQE_1ST_SE_FLG_SHIFT        3
#घोषणा RDMA_SQ_SEND_WQE_1ST_INLINE_FLG_MASK     0x1
#घोषणा RDMA_SQ_SEND_WQE_1ST_INLINE_FLG_SHIFT    4
#घोषणा RDMA_SQ_SEND_WQE_1ST_RESERVED0_MASK      0x7
#घोषणा RDMA_SQ_SEND_WQE_1ST_RESERVED0_SHIFT     5
	u8 wqe_size;
	u8 prev_wqe_size;
पूर्ण;

काष्ठा rdma_sq_send_wqe_2st अणु
	__le32 reserved1[4];
पूर्ण;

#पूर्ण_अगर /* __QED_HSI_RDMA__ */
