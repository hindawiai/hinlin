<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 WITH Linux-syscall-note) or BSD-3-Clause */

/* Authors: Bernard Metzler <bmt@zurich.ibm.com> */
/* Copyright (c) 2008-2019, IBM Corporation */

#अगर_अघोषित _SIW_USER_H
#घोषणा _SIW_USER_H

#समावेश <linux/types.h>

#घोषणा SIW_NODE_DESC_COMMON "Software iWARP stack"
#घोषणा SIW_ABI_VERSION 1
#घोषणा SIW_MAX_SGE 6
#घोषणा SIW_UOBJ_MAX_KEY 0x08FFFF
#घोषणा SIW_INVAL_UOBJ_KEY (SIW_UOBJ_MAX_KEY + 1)

काष्ठा siw_uresp_create_cq अणु
	__u32 cq_id;
	__u32 num_cqe;
	__aligned_u64 cq_key;
पूर्ण;

काष्ठा siw_uresp_create_qp अणु
	__u32 qp_id;
	__u32 num_sqe;
	__u32 num_rqe;
	__u32 pad;
	__aligned_u64 sq_key;
	__aligned_u64 rq_key;
पूर्ण;

काष्ठा siw_ureq_reg_mr अणु
	__u8 stag_key;
	__u8 reserved[3];
	__u32 pad;
पूर्ण;

काष्ठा siw_uresp_reg_mr अणु
	__u32 stag;
	__u32 pad;
पूर्ण;

काष्ठा siw_uresp_create_srq अणु
	__u32 num_rqe;
	__u32 pad;
	__aligned_u64 srq_key;
पूर्ण;

काष्ठा siw_uresp_alloc_ctx अणु
	__u32 dev_id;
	__u32 pad;
पूर्ण;

क्रमागत siw_opcode अणु
	SIW_OP_WRITE,
	SIW_OP_READ,
	SIW_OP_READ_LOCAL_INV,
	SIW_OP_SEND,
	SIW_OP_SEND_WITH_IMM,
	SIW_OP_SEND_REMOTE_INV,

	/* Unsupported */
	SIW_OP_FETCH_AND_ADD,
	SIW_OP_COMP_AND_SWAP,

	SIW_OP_RECEIVE,
	/* provider पूर्णांकernal SQE */
	SIW_OP_READ_RESPONSE,
	/*
	 * below opcodes valid क्रम
	 * in-kernel clients only
	 */
	SIW_OP_INVAL_STAG,
	SIW_OP_REG_MR,
	SIW_NUM_OPCODES
पूर्ण;

/* Keep it same as ibv_sge to allow क्रम स_नकल */
काष्ठा siw_sge अणु
	__aligned_u64 laddr;
	__u32 length;
	__u32 lkey;
पूर्ण;

/*
 * Inline data are kept within the work request itself occupying
 * the space of sge[1] .. sge[n]. Thereक्रमe, अंतरभूत data cannot be
 * supported अगर SIW_MAX_SGE is below 2 elements.
 */
#घोषणा SIW_MAX_INLINE (माप(काष्ठा siw_sge) * (SIW_MAX_SGE - 1))

#अगर SIW_MAX_SGE < 2
#त्रुटि "SIW_MAX_SGE must be at least 2"
#पूर्ण_अगर

क्रमागत siw_wqe_flags अणु
	SIW_WQE_VALID = 1,
	SIW_WQE_INLINE = (1 << 1),
	SIW_WQE_SIGNALLED = (1 << 2),
	SIW_WQE_SOLICITED = (1 << 3),
	SIW_WQE_READ_FENCE = (1 << 4),
	SIW_WQE_REM_INVAL = (1 << 5),
	SIW_WQE_COMPLETED = (1 << 6)
पूर्ण;

/* Send Queue Element */
काष्ठा siw_sqe अणु
	__aligned_u64 id;
	__u16 flags;
	__u8 num_sge;
	/* Contains क्रमागत siw_opcode values */
	__u8 opcode;
	__u32 rkey;
	जोड़ अणु
		__aligned_u64 raddr;
		__aligned_u64 base_mr;
	पूर्ण;
	जोड़ अणु
		काष्ठा siw_sge sge[SIW_MAX_SGE];
		__aligned_u64 access;
	पूर्ण;
पूर्ण;

/* Receive Queue Element */
काष्ठा siw_rqe अणु
	__aligned_u64 id;
	__u16 flags;
	__u8 num_sge;
	/*
	 * only used by kernel driver,
	 * ignored अगर set by user
	 */
	__u8 opcode;
	__u32 unused;
	काष्ठा siw_sge sge[SIW_MAX_SGE];
पूर्ण;

क्रमागत siw_notअगरy_flags अणु
	SIW_NOTIFY_NOT = (0),
	SIW_NOTIFY_SOLICITED = (1 << 0),
	SIW_NOTIFY_NEXT_COMPLETION = (1 << 1),
	SIW_NOTIFY_MISSED_EVENTS = (1 << 2),
	SIW_NOTIFY_ALL = SIW_NOTIFY_SOLICITED | SIW_NOTIFY_NEXT_COMPLETION |
			 SIW_NOTIFY_MISSED_EVENTS
पूर्ण;

क्रमागत siw_wc_status अणु
	SIW_WC_SUCCESS,
	SIW_WC_LOC_LEN_ERR,
	SIW_WC_LOC_PROT_ERR,
	SIW_WC_LOC_QP_OP_ERR,
	SIW_WC_WR_FLUSH_ERR,
	SIW_WC_BAD_RESP_ERR,
	SIW_WC_LOC_ACCESS_ERR,
	SIW_WC_REM_ACCESS_ERR,
	SIW_WC_REM_INV_REQ_ERR,
	SIW_WC_GENERAL_ERR,
	SIW_NUM_WC_STATUS
पूर्ण;

काष्ठा siw_cqe अणु
	__aligned_u64 id;
	__u8 flags;
	__u8 opcode;
	__u16 status;
	__u32 bytes;
	जोड़ अणु
		__aligned_u64 imm_data;
		__u32 inval_stag;
	पूर्ण;
	/* QP number or QP poपूर्णांकer */
	जोड़ अणु
		काष्ठा ib_qp *base_qp;
		__aligned_u64 qp_id;
	पूर्ण;
पूर्ण;

/*
 * Shared काष्ठाure between user and kernel
 * to control CQ arming.
 */
काष्ठा siw_cq_ctrl अणु
	__u32 flags;
	__u32 pad;
पूर्ण;
#पूर्ण_अगर
