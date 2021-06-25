<शैली गुरु>
/*
 * Broadcom NetXtreme-E RoCE driver.
 *
 * Copyright (c) 2016 - 2017, Broadcom. All rights reserved.  The term
 * Broadcom refers to Broadcom Limited and/or its subsidiaries.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * BSD license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary क्रमm must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the करोcumentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS''
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS
 * BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 * SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
 * BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
 * OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
 * IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Description: Fast Path Operators (header)
 */

#अगर_अघोषित __BNXT_QPLIB_FP_H__
#घोषणा __BNXT_QPLIB_FP_H__

/* Few helper काष्ठाures temporarily defined here
 * should get rid of these when roce_hsi.h is updated
 * in original code base
 */
काष्ठा sq_ud_ext_hdr अणु
	__le32 dst_qp;
	__le32 avid;
	__le64 rsvd;
पूर्ण;

काष्ठा sq_raw_ext_hdr अणु
	__le32 cfa_meta;
	__le32 rsvd0;
	__le64 rsvd1;
पूर्ण;

काष्ठा sq_rdma_ext_hdr अणु
	__le64 remote_va;
	__le32 remote_key;
	__le32 rsvd;
पूर्ण;

काष्ठा sq_atomic_ext_hdr अणु
	__le64 swap_data;
	__le64 cmp_data;
पूर्ण;

काष्ठा sq_fr_pmr_ext_hdr अणु
	__le64 pblptr;
	__le64 va;
पूर्ण;

काष्ठा sq_bind_ext_hdr अणु
	__le64 va;
	__le32 length_lo;
	__le32 length_hi;
पूर्ण;

काष्ठा rq_ext_hdr अणु
	__le64 rsvd1;
	__le64 rsvd2;
पूर्ण;

/* Helper काष्ठाures end */

काष्ठा bnxt_qplib_srq अणु
	काष्ठा bnxt_qplib_pd		*pd;
	काष्ठा bnxt_qplib_dpi		*dpi;
	काष्ठा bnxt_qplib_db_info	dbinfo;
	u64				srq_handle;
	u32				id;
	u16				wqe_size;
	u32				max_wqe;
	u32				max_sge;
	u32				threshold;
	bool				arm_req;
	काष्ठा bnxt_qplib_cq		*cq;
	काष्ठा bnxt_qplib_hwq		hwq;
	काष्ठा bnxt_qplib_swq		*swq;
	पूर्णांक				start_idx;
	पूर्णांक				last_idx;
	काष्ठा bnxt_qplib_sg_info	sg_info;
	u16				eventq_hw_ring_id;
	spinlock_t			lock; /* protect SRQE link list */
पूर्ण;

काष्ठा bnxt_qplib_sge अणु
	u64				addr;
	u32				lkey;
	u32				size;
पूर्ण;

#घोषणा BNXT_QPLIB_QP_MAX_SGL	6
काष्ठा bnxt_qplib_swq अणु
	u64				wr_id;
	पूर्णांक				next_idx;
	u8				type;
	u8				flags;
	u32				start_psn;
	u32				next_psn;
	u32				slot_idx;
	u8				slots;
	काष्ठा sq_psn_search		*psn_search;
	काष्ठा sq_psn_search_ext	*psn_ext;
पूर्ण;

काष्ठा bnxt_qplib_swqe अणु
	/* General */
#घोषणा	BNXT_QPLIB_FENCE_WRID	0x46454E43	/* "FENC" */
	u64				wr_id;
	u8				reqs_type;
	u8				type;
#घोषणा BNXT_QPLIB_SWQE_TYPE_SEND			0
#घोषणा BNXT_QPLIB_SWQE_TYPE_SEND_WITH_IMM		1
#घोषणा BNXT_QPLIB_SWQE_TYPE_SEND_WITH_INV		2
#घोषणा BNXT_QPLIB_SWQE_TYPE_RDMA_WRITE			4
#घोषणा BNXT_QPLIB_SWQE_TYPE_RDMA_WRITE_WITH_IMM	5
#घोषणा BNXT_QPLIB_SWQE_TYPE_RDMA_READ			6
#घोषणा BNXT_QPLIB_SWQE_TYPE_ATOMIC_CMP_AND_SWP		8
#घोषणा BNXT_QPLIB_SWQE_TYPE_ATOMIC_FETCH_AND_ADD	11
#घोषणा BNXT_QPLIB_SWQE_TYPE_LOCAL_INV			12
#घोषणा BNXT_QPLIB_SWQE_TYPE_FAST_REG_MR		13
#घोषणा BNXT_QPLIB_SWQE_TYPE_REG_MR			13
#घोषणा BNXT_QPLIB_SWQE_TYPE_BIND_MW			14
#घोषणा BNXT_QPLIB_SWQE_TYPE_RECV			128
#घोषणा BNXT_QPLIB_SWQE_TYPE_RECV_RDMA_IMM		129
	u8				flags;
#घोषणा BNXT_QPLIB_SWQE_FLAGS_SIGNAL_COMP		BIT(0)
#घोषणा BNXT_QPLIB_SWQE_FLAGS_RD_ATOMIC_FENCE		BIT(1)
#घोषणा BNXT_QPLIB_SWQE_FLAGS_UC_FENCE			BIT(2)
#घोषणा BNXT_QPLIB_SWQE_FLAGS_SOLICIT_EVENT		BIT(3)
#घोषणा BNXT_QPLIB_SWQE_FLAGS_INLINE			BIT(4)
	काष्ठा bnxt_qplib_sge		sg_list[BNXT_QPLIB_QP_MAX_SGL];
	पूर्णांक				num_sge;
	/* Max अंतरभूत data is 96 bytes */
	u32				अंतरभूत_len;
#घोषणा BNXT_QPLIB_SWQE_MAX_INLINE_LENGTH		96
	u8		अंतरभूत_data[BNXT_QPLIB_SWQE_MAX_INLINE_LENGTH];

	जोड़ अणु
		/* Send, with imm, inval key */
		काष्ठा अणु
			जोड़ अणु
				__be32	imm_data;
				u32	inv_key;
			पूर्ण;
			u32		q_key;
			u32		dst_qp;
			u16		avid;
		पूर्ण send;

		/* Send Raw Ethernet and QP1 */
		काष्ठा अणु
			u16		lflags;
			u16		cfa_action;
			u32		cfa_meta;
		पूर्ण rawqp1;

		/* RDMA ग_लिखो, with imm, पढ़ो */
		काष्ठा अणु
			जोड़ अणु
				__be32	imm_data;
				u32	inv_key;
			पूर्ण;
			u64		remote_va;
			u32		r_key;
		पूर्ण rdma;

		/* Atomic cmp/swap, fetch/add */
		काष्ठा अणु
			u64		remote_va;
			u32		r_key;
			u64		swap_data;
			u64		cmp_data;
		पूर्ण atomic;

		/* Local Invalidate */
		काष्ठा अणु
			u32		inv_l_key;
		पूर्ण local_inv;

		/* FR-PMR */
		काष्ठा अणु
			u8		access_cntl;
			u8		pg_sz_log;
			bool		zero_based;
			u32		l_key;
			u32		length;
			u8		pbl_pg_sz_log;
#घोषणा BNXT_QPLIB_SWQE_PAGE_SIZE_4K			0
#घोषणा BNXT_QPLIB_SWQE_PAGE_SIZE_8K			1
#घोषणा BNXT_QPLIB_SWQE_PAGE_SIZE_64K			4
#घोषणा BNXT_QPLIB_SWQE_PAGE_SIZE_256K			6
#घोषणा BNXT_QPLIB_SWQE_PAGE_SIZE_1M			8
#घोषणा BNXT_QPLIB_SWQE_PAGE_SIZE_2M			9
#घोषणा BNXT_QPLIB_SWQE_PAGE_SIZE_4M			10
#घोषणा BNXT_QPLIB_SWQE_PAGE_SIZE_1G			18
			u8		levels;
#घोषणा PAGE_SHIFT_4K	12
			__le64		*pbl_ptr;
			dma_addr_t	pbl_dma_ptr;
			u64		*page_list;
			u16		page_list_len;
			u64		va;
		पूर्ण frmr;

		/* Bind */
		काष्ठा अणु
			u8		access_cntl;
#घोषणा BNXT_QPLIB_BIND_SWQE_ACCESS_LOCAL_WRITE		BIT(0)
#घोषणा BNXT_QPLIB_BIND_SWQE_ACCESS_REMOTE_READ		BIT(1)
#घोषणा BNXT_QPLIB_BIND_SWQE_ACCESS_REMOTE_WRITE	BIT(2)
#घोषणा BNXT_QPLIB_BIND_SWQE_ACCESS_REMOTE_ATOMIC	BIT(3)
#घोषणा BNXT_QPLIB_BIND_SWQE_ACCESS_WINDOW_BIND		BIT(4)
			bool		zero_based;
			u8		mw_type;
			u32		parent_l_key;
			u32		r_key;
			u64		va;
			u32		length;
		पूर्ण bind;
	पूर्ण;
पूर्ण;

काष्ठा bnxt_qplib_q अणु
	काष्ठा bnxt_qplib_hwq		hwq;
	काष्ठा bnxt_qplib_swq		*swq;
	काष्ठा bnxt_qplib_db_info	dbinfo;
	काष्ठा bnxt_qplib_sg_info	sg_info;
	u32				max_wqe;
	u16				wqe_size;
	u16				q_full_delta;
	u16				max_sge;
	u32				psn;
	bool				condition;
	bool				single;
	bool				send_phantom;
	u32				phantom_wqe_cnt;
	u32				phantom_cqe_cnt;
	u32				next_cq_cons;
	bool				flushed;
	u32				swq_start;
	u32				swq_last;
पूर्ण;

काष्ठा bnxt_qplib_qp अणु
	काष्ठा bnxt_qplib_pd		*pd;
	काष्ठा bnxt_qplib_dpi		*dpi;
	काष्ठा bnxt_qplib_chip_ctx	*cctx;
	u64				qp_handle;
#घोषणा BNXT_QPLIB_QP_ID_INVALID        0xFFFFFFFF
	u32				id;
	u8				type;
	u8				sig_type;
	u8				wqe_mode;
	u8				state;
	u8				cur_qp_state;
	u64				modअगरy_flags;
	u32				max_अंतरभूत_data;
	u32				mtu;
	u8				path_mtu;
	bool				en_sqd_async_notअगरy;
	u16				pkey_index;
	u32				qkey;
	u32				dest_qp_id;
	u8				access;
	u8				समयout;
	u8				retry_cnt;
	u8				rnr_retry;
	u64				wqe_cnt;
	u32				min_rnr_समयr;
	u32				max_rd_atomic;
	u32				max_dest_rd_atomic;
	u32				dest_qpn;
	u8				smac[6];
	u16				vlan_id;
	u8				nw_type;
	काष्ठा bnxt_qplib_ah		ah;

#घोषणा BTH_PSN_MASK			((1 << 24) - 1)
	/* SQ */
	काष्ठा bnxt_qplib_q		sq;
	/* RQ */
	काष्ठा bnxt_qplib_q		rq;
	/* SRQ */
	काष्ठा bnxt_qplib_srq		*srq;
	/* CQ */
	काष्ठा bnxt_qplib_cq		*scq;
	काष्ठा bnxt_qplib_cq		*rcq;
	/* IRRQ and ORRQ */
	काष्ठा bnxt_qplib_hwq		irrq;
	काष्ठा bnxt_qplib_hwq		orrq;
	/* Header buffer क्रम QP1 */
	पूर्णांक				sq_hdr_buf_size;
	पूर्णांक				rq_hdr_buf_size;
/*
 * Buffer space क्रम ETH(14), IP or GRH(40), UDP header(8)
 * and ib_bth + ib_deth (20).
 * Max required is 82 when RoCE V2 is enabled
 */
#घोषणा BNXT_QPLIB_MAX_QP1_SQ_HDR_SIZE_V2	86
	/* Ethernet header	=  14 */
	/* ib_grh		=  40 (provided by MAD) */
	/* ib_bth + ib_deth	=  20 */
	/* MAD			= 256 (provided by MAD) */
	/* iCRC			=   4 */
#घोषणा BNXT_QPLIB_MAX_QP1_RQ_ETH_HDR_SIZE	14
#घोषणा BNXT_QPLIB_MAX_QP1_RQ_HDR_SIZE_V2	512
#घोषणा BNXT_QPLIB_MAX_GRH_HDR_SIZE_IPV4	20
#घोषणा BNXT_QPLIB_MAX_GRH_HDR_SIZE_IPV6	40
#घोषणा BNXT_QPLIB_MAX_QP1_RQ_BDETH_HDR_SIZE	20
	व्योम				*sq_hdr_buf;
	dma_addr_t			sq_hdr_buf_map;
	व्योम				*rq_hdr_buf;
	dma_addr_t			rq_hdr_buf_map;
	काष्ठा list_head		sq_flush;
	काष्ठा list_head		rq_flush;
पूर्ण;

#घोषणा BNXT_QPLIB_MAX_CQE_ENTRY_SIZE	माप(काष्ठा cq_base)

#घोषणा CQE_CNT_PER_PG		(PAGE_SIZE / BNXT_QPLIB_MAX_CQE_ENTRY_SIZE)
#घोषणा CQE_MAX_IDX_PER_PG	(CQE_CNT_PER_PG - 1)
#घोषणा CQE_PG(x)		(((x) & ~CQE_MAX_IDX_PER_PG) / CQE_CNT_PER_PG)
#घोषणा CQE_IDX(x)		((x) & CQE_MAX_IDX_PER_PG)

#घोषणा ROCE_CQE_CMP_V			0
#घोषणा CQE_CMP_VALID(hdr, raw_cons, cp_bit)			\
	(!!((hdr)->cqe_type_toggle & CQ_BASE_TOGGLE) ==		\
	   !((raw_cons) & (cp_bit)))

अटल अंतरभूत bool bnxt_qplib_queue_full(काष्ठा bnxt_qplib_q *que,
					 u8 slots)
अणु
	काष्ठा bnxt_qplib_hwq *hwq;
	पूर्णांक avail;

	hwq = &que->hwq;
	/* False full is possible, retrying post-send makes sense */
	avail = hwq->cons - hwq->prod;
	अगर (hwq->cons <= hwq->prod)
		avail += hwq->depth;
	वापस avail <= slots;
पूर्ण

काष्ठा bnxt_qplib_cqe अणु
	u8				status;
	u8				type;
	u8				opcode;
	u32				length;
	u16				cfa_meta;
	u64				wr_id;
	जोड़ अणु
		__be32			immdata;
		u32			invrkey;
	पूर्ण;
	u64				qp_handle;
	u64				mr_handle;
	u16				flags;
	u8				smac[6];
	u32				src_qp;
	u16				raweth_qp1_flags;
	u16				raweth_qp1_errors;
	u16				raweth_qp1_cfa_code;
	u32				raweth_qp1_flags2;
	u32				raweth_qp1_metadata;
	u8				raweth_qp1_payload_offset;
	u16				pkey_index;
पूर्ण;

#घोषणा BNXT_QPLIB_QUEUE_START_PERIOD		0x01
काष्ठा bnxt_qplib_cq अणु
	काष्ठा bnxt_qplib_dpi		*dpi;
	काष्ठा bnxt_qplib_db_info	dbinfo;
	u32				max_wqe;
	u32				id;
	u16				count;
	u16				period;
	काष्ठा bnxt_qplib_hwq		hwq;
	u32				cnq_hw_ring_id;
	काष्ठा bnxt_qplib_nq		*nq;
	bool				resize_in_progress;
	काष्ठा bnxt_qplib_sg_info	sg_info;
	u64				cq_handle;

#घोषणा CQ_RESIZE_WAIT_TIME_MS		500
	अचिन्हित दीर्घ			flags;
#घोषणा CQ_FLAGS_RESIZE_IN_PROG		1
	रुको_queue_head_t		रुकोq;
	काष्ठा list_head		sqf_head, rqf_head;
	atomic_t			arm_state;
	spinlock_t			compl_lock; /* synch CQ handlers */
/* Locking Notes:
 * QP can move to error state from modअगरy_qp, async error event or error
 * CQE as part of poll_cq. When QP is moved to error state, it माला_लो added
 * to two flush lists, one each क्रम SQ and RQ.
 * Each flush list is रक्षित by qplib_cq->flush_lock. Both scq and rcq
 * flush_locks should be acquired when QP is moved to error. The control path
 * operations(modअगरy_qp and async error events) are synchronized with poll_cq
 * using upper level CQ locks (bnxt_re_cq->cq_lock) of both SCQ and RCQ.
 * The qplib_cq->flush_lock is required to synchronize two instances of poll_cq
 * of the same QP जबतक manipulating the flush list.
 */
	spinlock_t			flush_lock; /* QP flush management */
	u16				cnq_events;
पूर्ण;

#घोषणा BNXT_QPLIB_MAX_IRRQE_ENTRY_SIZE	माप(काष्ठा xrrq_irrq)
#घोषणा BNXT_QPLIB_MAX_ORRQE_ENTRY_SIZE	माप(काष्ठा xrrq_orrq)
#घोषणा IRD_LIMIT_TO_IRRQ_SLOTS(x)	(2 * (x) + 2)
#घोषणा IRRQ_SLOTS_TO_IRD_LIMIT(s)	(((s) >> 1) - 1)
#घोषणा ORD_LIMIT_TO_ORRQ_SLOTS(x)	((x) + 1)
#घोषणा ORRQ_SLOTS_TO_ORD_LIMIT(s)	((s) - 1)

#घोषणा BNXT_QPLIB_MAX_NQE_ENTRY_SIZE	माप(काष्ठा nq_base)

#घोषणा NQE_CNT_PER_PG		(PAGE_SIZE / BNXT_QPLIB_MAX_NQE_ENTRY_SIZE)
#घोषणा NQE_MAX_IDX_PER_PG	(NQE_CNT_PER_PG - 1)
#घोषणा NQE_PG(x)		(((x) & ~NQE_MAX_IDX_PER_PG) / NQE_CNT_PER_PG)
#घोषणा NQE_IDX(x)		((x) & NQE_MAX_IDX_PER_PG)

#घोषणा NQE_CMP_VALID(hdr, raw_cons, cp_bit)			\
	(!!(le32_to_cpu((hdr)->info63_v[0]) & NQ_BASE_V) ==	\
	   !((raw_cons) & (cp_bit)))

#घोषणा BNXT_QPLIB_NQE_MAX_CNT		(128 * 1024)

#घोषणा NQ_CONS_PCI_BAR_REGION		2
#घोषणा NQ_DB_KEY_CP			(0x2 << CMPL_DOORBELL_KEY_SFT)
#घोषणा NQ_DB_IDX_VALID			CMPL_DOORBELL_IDX_VALID
#घोषणा NQ_DB_IRQ_DIS			CMPL_DOORBELL_MASK
#घोषणा NQ_DB_CP_FLAGS_REARM		(NQ_DB_KEY_CP |		\
					 NQ_DB_IDX_VALID)
#घोषणा NQ_DB_CP_FLAGS			(NQ_DB_KEY_CP    |	\
					 NQ_DB_IDX_VALID |	\
					 NQ_DB_IRQ_DIS)

काष्ठा bnxt_qplib_nq_db अणु
	काष्ठा bnxt_qplib_reg_desc	reg;
	काष्ठा bnxt_qplib_db_info	dbinfo;
पूर्ण;

प्रकार पूर्णांक (*cqn_handler_t)(काष्ठा bnxt_qplib_nq *nq,
		काष्ठा bnxt_qplib_cq *cq);
प्रकार पूर्णांक (*srqn_handler_t)(काष्ठा bnxt_qplib_nq *nq,
		काष्ठा bnxt_qplib_srq *srq, u8 event);

काष्ठा bnxt_qplib_nq अणु
	काष्ठा pci_dev			*pdev;
	काष्ठा bnxt_qplib_res		*res;
	अक्षर				name[32];
	काष्ठा bnxt_qplib_hwq		hwq;
	काष्ठा bnxt_qplib_nq_db		nq_db;
	u16				ring_id;
	पूर्णांक				msix_vec;
	cpumask_t			mask;
	काष्ठा tasklet_काष्ठा		nq_tasklet;
	bool				requested;
	पूर्णांक				budget;

	cqn_handler_t			cqn_handler;
	srqn_handler_t			srqn_handler;
	काष्ठा workqueue_काष्ठा		*cqn_wq;
पूर्ण;

काष्ठा bnxt_qplib_nq_work अणु
	काष्ठा work_काष्ठा      work;
	काष्ठा bnxt_qplib_nq    *nq;
	काष्ठा bnxt_qplib_cq    *cq;
पूर्ण;

व्योम bnxt_qplib_nq_stop_irq(काष्ठा bnxt_qplib_nq *nq, bool समाप्त);
व्योम bnxt_qplib_disable_nq(काष्ठा bnxt_qplib_nq *nq);
पूर्णांक bnxt_qplib_nq_start_irq(काष्ठा bnxt_qplib_nq *nq, पूर्णांक nq_indx,
			    पूर्णांक msix_vector, bool need_init);
पूर्णांक bnxt_qplib_enable_nq(काष्ठा pci_dev *pdev, काष्ठा bnxt_qplib_nq *nq,
			 पूर्णांक nq_idx, पूर्णांक msix_vector, पूर्णांक bar_reg_offset,
			 cqn_handler_t cqn_handler,
			 srqn_handler_t srq_handler);
पूर्णांक bnxt_qplib_create_srq(काष्ठा bnxt_qplib_res *res,
			  काष्ठा bnxt_qplib_srq *srq);
पूर्णांक bnxt_qplib_modअगरy_srq(काष्ठा bnxt_qplib_res *res,
			  काष्ठा bnxt_qplib_srq *srq);
पूर्णांक bnxt_qplib_query_srq(काष्ठा bnxt_qplib_res *res,
			 काष्ठा bnxt_qplib_srq *srq);
व्योम bnxt_qplib_destroy_srq(काष्ठा bnxt_qplib_res *res,
			    काष्ठा bnxt_qplib_srq *srq);
पूर्णांक bnxt_qplib_post_srq_recv(काष्ठा bnxt_qplib_srq *srq,
			     काष्ठा bnxt_qplib_swqe *wqe);
पूर्णांक bnxt_qplib_create_qp1(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp);
पूर्णांक bnxt_qplib_create_qp(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp);
पूर्णांक bnxt_qplib_modअगरy_qp(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp);
पूर्णांक bnxt_qplib_query_qp(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp);
पूर्णांक bnxt_qplib_destroy_qp(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_qp *qp);
व्योम bnxt_qplib_clean_qp(काष्ठा bnxt_qplib_qp *qp);
व्योम bnxt_qplib_मुक्त_qp_res(काष्ठा bnxt_qplib_res *res,
			    काष्ठा bnxt_qplib_qp *qp);
व्योम *bnxt_qplib_get_qp1_sq_buf(काष्ठा bnxt_qplib_qp *qp,
				काष्ठा bnxt_qplib_sge *sge);
व्योम *bnxt_qplib_get_qp1_rq_buf(काष्ठा bnxt_qplib_qp *qp,
				काष्ठा bnxt_qplib_sge *sge);
u32 bnxt_qplib_get_rq_prod_index(काष्ठा bnxt_qplib_qp *qp);
dma_addr_t bnxt_qplib_get_qp_buf_from_index(काष्ठा bnxt_qplib_qp *qp,
					    u32 index);
व्योम bnxt_qplib_post_send_db(काष्ठा bnxt_qplib_qp *qp);
पूर्णांक bnxt_qplib_post_send(काष्ठा bnxt_qplib_qp *qp,
			 काष्ठा bnxt_qplib_swqe *wqe);
व्योम bnxt_qplib_post_recv_db(काष्ठा bnxt_qplib_qp *qp);
पूर्णांक bnxt_qplib_post_recv(काष्ठा bnxt_qplib_qp *qp,
			 काष्ठा bnxt_qplib_swqe *wqe);
पूर्णांक bnxt_qplib_create_cq(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_cq *cq);
पूर्णांक bnxt_qplib_destroy_cq(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_cq *cq);
पूर्णांक bnxt_qplib_poll_cq(काष्ठा bnxt_qplib_cq *cq, काष्ठा bnxt_qplib_cqe *cqe,
		       पूर्णांक num, काष्ठा bnxt_qplib_qp **qp);
bool bnxt_qplib_is_cq_empty(काष्ठा bnxt_qplib_cq *cq);
व्योम bnxt_qplib_req_notअगरy_cq(काष्ठा bnxt_qplib_cq *cq, u32 arm_type);
व्योम bnxt_qplib_मुक्त_nq(काष्ठा bnxt_qplib_nq *nq);
पूर्णांक bnxt_qplib_alloc_nq(काष्ठा bnxt_qplib_res *res, काष्ठा bnxt_qplib_nq *nq);
व्योम bnxt_qplib_add_flush_qp(काष्ठा bnxt_qplib_qp *qp);
व्योम bnxt_qplib_acquire_cq_locks(काष्ठा bnxt_qplib_qp *qp,
				 अचिन्हित दीर्घ *flags);
व्योम bnxt_qplib_release_cq_locks(काष्ठा bnxt_qplib_qp *qp,
				 अचिन्हित दीर्घ *flags);
पूर्णांक bnxt_qplib_process_flush_list(काष्ठा bnxt_qplib_cq *cq,
				  काष्ठा bnxt_qplib_cqe *cqe,
				  पूर्णांक num_cqes);
व्योम bnxt_qplib_flush_cqn_wq(काष्ठा bnxt_qplib_qp *qp);

अटल अंतरभूत व्योम *bnxt_qplib_get_swqe(काष्ठा bnxt_qplib_q *que, u32 *swq_idx)
अणु
	u32 idx;

	idx = que->swq_start;
	अगर (swq_idx)
		*swq_idx = idx;
	वापस &que->swq[idx];
पूर्ण

अटल अंतरभूत व्योम bnxt_qplib_swq_mod_start(काष्ठा bnxt_qplib_q *que, u32 idx)
अणु
	que->swq_start = que->swq[idx].next_idx;
पूर्ण

अटल अंतरभूत u32 bnxt_qplib_get_depth(काष्ठा bnxt_qplib_q *que)
अणु
	वापस (que->wqe_size * que->max_wqe) / माप(काष्ठा sq_sge);
पूर्ण

अटल अंतरभूत u32 bnxt_qplib_set_sq_size(काष्ठा bnxt_qplib_q *que, u8 wqe_mode)
अणु
	वापस (wqe_mode == BNXT_QPLIB_WQE_MODE_STATIC) ?
		que->max_wqe : bnxt_qplib_get_depth(que);
पूर्ण

अटल अंतरभूत u32 bnxt_qplib_set_sq_max_slot(u8 wqe_mode)
अणु
	वापस (wqe_mode == BNXT_QPLIB_WQE_MODE_STATIC) ?
		माप(काष्ठा sq_send) / माप(काष्ठा sq_sge) : 1;
पूर्ण

अटल अंतरभूत u32 bnxt_qplib_set_rq_max_slot(u32 wqe_size)
अणु
	वापस (wqe_size / माप(काष्ठा sq_sge));
पूर्ण

अटल अंतरभूत u16 __xlate_qfd(u16 delta, u16 wqe_bytes)
अणु
	/* For Cu/Wh delta = 128, stride = 16, wqe_bytes = 128
	 * For Gen-p5 B/C mode delta = 0, stride = 16, wqe_bytes = 128.
	 * For Gen-p5 delta = 0, stride = 16, 32 <= wqe_bytes <= 512.
	 * when 8916 is disabled.
	 */
	वापस (delta * wqe_bytes) / माप(काष्ठा sq_sge);
पूर्ण

अटल अंतरभूत u16 bnxt_qplib_calc_ilsize(काष्ठा bnxt_qplib_swqe *wqe, u16 max)
अणु
	u16 size = 0;
	पूर्णांक indx;

	क्रम (indx = 0; indx < wqe->num_sge; indx++)
		size += wqe->sg_list[indx].size;
	अगर (size > max)
		size = max;

	वापस size;
पूर्ण
#पूर्ण_अगर /* __BNXT_QPLIB_FP_H__ */
