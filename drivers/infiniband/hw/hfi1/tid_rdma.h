<शैली गुरु>
/* SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause) */
/*
 * Copyright(c) 2018 Intel Corporation.
 *
 */
#अगर_अघोषित HFI1_TID_RDMA_H
#घोषणा HFI1_TID_RDMA_H

#समावेश <linux/circ_buf.h>
#समावेश "common.h"

/* Add a convenience helper */
#घोषणा CIRC_ADD(val, add, size) (((val) + (add)) & ((size) - 1))
#घोषणा CIRC_NEXT(val, size) CIRC_ADD(val, 1, size)
#घोषणा CIRC_PREV(val, size) CIRC_ADD(val, -1, size)

#घोषणा TID_RDMA_MIN_SEGMENT_SIZE       BIT(18)   /* 256 KiB (क्रम now) */
#घोषणा TID_RDMA_MAX_SEGMENT_SIZE       BIT(18)   /* 256 KiB (क्रम now) */
#घोषणा TID_RDMA_MAX_PAGES              (BIT(18) >> PAGE_SHIFT)
#घोषणा TID_RDMA_SEGMENT_SHIFT		18

/*
 * Bit definitions क्रम priv->s_flags.
 * These bit flags overload the bit flags defined क्रम the QP's s_flags.
 * Due to the fact that these bit fields are used only क्रम the QP priv
 * s_flags, there are no collisions.
 *
 * HFI1_S_TID_WAIT_INTERLCK - QP is रुकोing क्रम requester पूर्णांकerlock
 * HFI1_R_TID_WAIT_INTERLCK - QP is रुकोing क्रम responder पूर्णांकerlock
 */
#घोषणा HFI1_S_TID_BUSY_SET       BIT(0)
/* BIT(1) reserved क्रम RVT_S_BUSY. */
#घोषणा HFI1_R_TID_RSC_TIMER      BIT(2)
/* BIT(3) reserved क्रम RVT_S_RESP_PENDING. */
/* BIT(4) reserved क्रम RVT_S_ACK_PENDING. */
#घोषणा HFI1_S_TID_WAIT_INTERLCK  BIT(5)
#घोषणा HFI1_R_TID_WAIT_INTERLCK  BIT(6)
/* BIT(7) - BIT(15) reserved क्रम RVT_S_WAIT_*. */
/* BIT(16) reserved क्रम RVT_S_SEND_ONE */
#घोषणा HFI1_S_TID_RETRY_TIMER    BIT(17)
/* BIT(18) reserved क्रम RVT_S_ECN. */
#घोषणा HFI1_R_TID_SW_PSN         BIT(19)
/* BIT(26) reserved क्रम HFI1_S_WAIT_HALT */
/* BIT(27) reserved क्रम HFI1_S_WAIT_TID_RESP */
/* BIT(28) reserved क्रम HFI1_S_WAIT_TID_SPACE */

/*
 * Unlike regular IB RDMA VERBS, which करो not require an entry
 * in the s_ack_queue, TID RDMA WRITE requests करो because they
 * generate responses.
 * Thereक्रमe, the s_ack_queue needs to be extended by a certain
 * amount. The key poपूर्णांक is that the queue needs to be extended
 * without letting the "user" know so they user करोesn't end up
 * using these extra entries.
 */
#घोषणा HFI1_TID_RDMA_WRITE_CNT 8

काष्ठा tid_rdma_params अणु
	काष्ठा rcu_head rcu_head;
	u32 qp;
	u32 max_len;
	u16 jkey;
	u8 max_पढ़ो;
	u8 max_ग_लिखो;
	u8 समयout;
	u8 urg;
	u8 version;
पूर्ण;

काष्ठा tid_rdma_qp_params अणु
	काष्ठा work_काष्ठा trigger_work;
	काष्ठा tid_rdma_params local;
	काष्ठा tid_rdma_params __rcu *remote;
पूर्ण;

/* Track state क्रम each hardware flow */
काष्ठा tid_flow_state अणु
	u32 generation;
	u32 psn;
	u8 index;
	u8 last_index;
पूर्ण;

क्रमागत tid_rdma_req_state अणु
	TID_REQUEST_INACTIVE = 0,
	TID_REQUEST_INIT,
	TID_REQUEST_INIT_RESEND,
	TID_REQUEST_ACTIVE,
	TID_REQUEST_RESEND,
	TID_REQUEST_RESEND_ACTIVE,
	TID_REQUEST_QUEUED,
	TID_REQUEST_SYNC,
	TID_REQUEST_RNR_NAK,
	TID_REQUEST_COMPLETE,
पूर्ण;

काष्ठा tid_rdma_request अणु
	काष्ठा rvt_qp *qp;
	काष्ठा hfi1_ctxtdata *rcd;
	जोड़ अणु
		काष्ठा rvt_swqe *swqe;
		काष्ठा rvt_ack_entry *ack;
	पूर्ण e;

	काष्ठा tid_rdma_flow *flows;	/* array of tid flows */
	काष्ठा rvt_sge_state ss; /* SGE state क्रम TID RDMA requests */
	u16 n_flows;		/* size of the flow buffer winकरोw */
	u16 setup_head;		/* flow index we are setting up */
	u16 clear_tail;		/* flow index we are clearing */
	u16 flow_idx;		/* flow index most recently set up */
	u16 acked_tail;

	u32 seg_len;
	u32 total_len;
	u32 r_ack_psn;          /* next expected ack PSN */
	u32 r_flow_psn;         /* IB PSN of next segment start */
	u32 r_last_acked;       /* IB PSN of last ACK'ed packet */
	u32 s_next_psn;		/* IB PSN of next segment start क्रम पढ़ो */

	u32 total_segs;		/* segments required to complete a request */
	u32 cur_seg;		/* index of current segment */
	u32 comp_seg;           /* index of last completed segment */
	u32 ack_seg;            /* index of last ack'ed segment */
	u32 alloc_seg;          /* index of next segment to be allocated */
	u32 isge;		/* index of "current" sge */
	u32 ack_pending;        /* num acks pending क्रम this request */

	क्रमागत tid_rdma_req_state state;
पूर्ण;

/*
 * When header suppression is used, PSNs associated with a "flow" are
 * relevant (and not the PSNs मुख्यtained by verbs). Track per-flow
 * PSNs here क्रम a TID RDMA segment.
 *
 */
काष्ठा flow_state अणु
	u32 flags;
	u32 resp_ib_psn;     /* The IB PSN of the response क्रम this flow */
	u32 generation;      /* generation of flow */
	u32 spsn;            /* starting PSN in TID space */
	u32 lpsn;            /* last PSN in TID space */
	u32 r_next_psn;      /* next PSN to be received (in TID space) */

	/* For tid rdma पढ़ो */
	u32 ib_spsn;         /* starting PSN in Verbs space */
	u32 ib_lpsn;         /* last PSn in Verbs space */
पूर्ण;

काष्ठा tid_rdma_pageset अणु
	dma_addr_t addr : 48; /* Only needed क्रम the first page */
	u8 idx: 8;
	u8 count : 7;
	u8 mapped: 1;
पूर्ण;

/**
 * kern_tid_node - used क्रम managing TID's in TID groups
 *
 * @grp_idx: rcd relative index to tid_group
 * @map: grp->map captured prior to programming this TID group in HW
 * @cnt: Only @cnt of available group entries are actually programmed
 */
काष्ठा kern_tid_node अणु
	काष्ठा tid_group *grp;
	u8 map;
	u8 cnt;
पूर्ण;

/* Overall info क्रम a TID RDMA segment */
काष्ठा tid_rdma_flow अणु
	/*
	 * While a TID RDMA segment is being transferred, it uses a QP number
	 * from the "KDETH section of QP numbers" (which is dअगरferent from the
	 * QP number that originated the request). Bits 11-15 of these QP
	 * numbers identअगरy the "TID flow" क्रम the segment.
	 */
	काष्ठा flow_state flow_state;
	काष्ठा tid_rdma_request *req;
	u32 tid_qpn;
	u32 tid_offset;
	u32 length;
	u32 sent;
	u8 tnode_cnt;
	u8 tidcnt;
	u8 tid_idx;
	u8 idx;
	u8 npagesets;
	u8 npkts;
	u8 pkt;
	u8 resync_npkts;
	काष्ठा kern_tid_node tnode[TID_RDMA_MAX_PAGES];
	काष्ठा tid_rdma_pageset pagesets[TID_RDMA_MAX_PAGES];
	u32 tid_entry[TID_RDMA_MAX_PAGES];
पूर्ण;

क्रमागत tid_rnr_nak_state अणु
	TID_RNR_NAK_INIT = 0,
	TID_RNR_NAK_SEND,
	TID_RNR_NAK_SENT,
पूर्ण;

bool tid_rdma_conn_req(काष्ठा rvt_qp *qp, u64 *data);
bool tid_rdma_conn_reply(काष्ठा rvt_qp *qp, u64 data);
bool tid_rdma_conn_resp(काष्ठा rvt_qp *qp, u64 *data);
व्योम tid_rdma_conn_error(काष्ठा rvt_qp *qp);
व्योम tid_rdma_opfn_init(काष्ठा rvt_qp *qp, काष्ठा tid_rdma_params *p);

पूर्णांक hfi1_kern_exp_rcv_init(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक reinit);
पूर्णांक hfi1_kern_exp_rcv_setup(काष्ठा tid_rdma_request *req,
			    काष्ठा rvt_sge_state *ss, bool *last);
पूर्णांक hfi1_kern_exp_rcv_clear(काष्ठा tid_rdma_request *req);
व्योम hfi1_kern_exp_rcv_clear_all(काष्ठा tid_rdma_request *req);
व्योम __trdma_clean_swqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe);

/**
 * trdma_clean_swqe - clean flows क्रम swqe अगर large send queue
 * @qp: the qp
 * @wqe: the send wqe
 */
अटल अंतरभूत व्योम trdma_clean_swqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe)
अणु
	अगर (!wqe->priv)
		वापस;
	__trdma_clean_swqe(qp, wqe);
पूर्ण

व्योम hfi1_kern_पढ़ो_tid_flow_मुक्त(काष्ठा rvt_qp *qp);

पूर्णांक hfi1_qp_priv_init(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
		      काष्ठा ib_qp_init_attr *init_attr);
व्योम hfi1_qp_priv_tid_मुक्त(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp);

व्योम hfi1_tid_rdma_flush_रुको(काष्ठा rvt_qp *qp);

पूर्णांक hfi1_kern_setup_hw_flow(काष्ठा hfi1_ctxtdata *rcd, काष्ठा rvt_qp *qp);
व्योम hfi1_kern_clear_hw_flow(काष्ठा hfi1_ctxtdata *rcd, काष्ठा rvt_qp *qp);
व्योम hfi1_kern_init_ctxt_generations(काष्ठा hfi1_ctxtdata *rcd);

काष्ठा cntr_entry;
u64 hfi1_access_sw_tid_रुको(स्थिर काष्ठा cntr_entry *entry,
			    व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data);

u32 hfi1_build_tid_rdma_पढ़ो_packet(काष्ठा rvt_swqe *wqe,
				    काष्ठा ib_other_headers *ohdr,
				    u32 *bth1, u32 *bth2, u32 *len);
u32 hfi1_build_tid_rdma_पढ़ो_req(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
				 काष्ठा ib_other_headers *ohdr, u32 *bth1,
				 u32 *bth2, u32 *len);
व्योम hfi1_rc_rcv_tid_rdma_पढ़ो_req(काष्ठा hfi1_packet *packet);
u32 hfi1_build_tid_rdma_पढ़ो_resp(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e,
				  काष्ठा ib_other_headers *ohdr, u32 *bth0,
				  u32 *bth1, u32 *bth2, u32 *len, bool *last);
व्योम hfi1_rc_rcv_tid_rdma_पढ़ो_resp(काष्ठा hfi1_packet *packet);
bool hfi1_handle_kdeth_eflags(काष्ठा hfi1_ctxtdata *rcd,
			      काष्ठा hfi1_pportdata *ppd,
			      काष्ठा hfi1_packet *packet);
व्योम hfi1_tid_rdma_restart_req(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
			       u32 *bth2);
व्योम hfi1_qp_kern_exp_rcv_clear_all(काष्ठा rvt_qp *qp);
bool hfi1_tid_rdma_wqe_पूर्णांकerlock(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe);

व्योम setup_tid_rdma_wqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe);
अटल अंतरभूत व्योम hfi1_setup_tid_rdma_wqe(काष्ठा rvt_qp *qp,
					   काष्ठा rvt_swqe *wqe)
अणु
	अगर (wqe->priv &&
	    (wqe->wr.opcode == IB_WR_RDMA_READ ||
	     wqe->wr.opcode == IB_WR_RDMA_WRITE) &&
	    wqe->length >= TID_RDMA_MIN_SEGMENT_SIZE)
		setup_tid_rdma_wqe(qp, wqe);
पूर्ण

u32 hfi1_build_tid_rdma_ग_लिखो_req(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
				  काष्ठा ib_other_headers *ohdr,
				  u32 *bth1, u32 *bth2, u32 *len);

व्योम hfi1_rc_rcv_tid_rdma_ग_लिखो_req(काष्ठा hfi1_packet *packet);

u32 hfi1_build_tid_rdma_ग_लिखो_resp(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e,
				   काष्ठा ib_other_headers *ohdr, u32 *bth1,
				   u32 bth2, u32 *len,
				   काष्ठा rvt_sge_state **ss);

व्योम hfi1_del_tid_reap_समयr(काष्ठा rvt_qp *qp);

व्योम hfi1_rc_rcv_tid_rdma_ग_लिखो_resp(काष्ठा hfi1_packet *packet);

bool hfi1_build_tid_rdma_packet(काष्ठा rvt_swqe *wqe,
				काष्ठा ib_other_headers *ohdr,
				u32 *bth1, u32 *bth2, u32 *len);

व्योम hfi1_rc_rcv_tid_rdma_ग_लिखो_data(काष्ठा hfi1_packet *packet);

u32 hfi1_build_tid_rdma_ग_लिखो_ack(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e,
				  काष्ठा ib_other_headers *ohdr, u16 अगरlow,
				  u32 *bth1, u32 *bth2);

व्योम hfi1_rc_rcv_tid_rdma_ack(काष्ठा hfi1_packet *packet);

व्योम hfi1_add_tid_retry_समयr(काष्ठा rvt_qp *qp);
व्योम hfi1_del_tid_retry_समयr(काष्ठा rvt_qp *qp);

u32 hfi1_build_tid_rdma_resync(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
			       काष्ठा ib_other_headers *ohdr, u32 *bth1,
			       u32 *bth2, u16 fidx);

व्योम hfi1_rc_rcv_tid_rdma_resync(काष्ठा hfi1_packet *packet);

काष्ठा hfi1_pkt_state;
पूर्णांक hfi1_make_tid_rdma_pkt(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps);

व्योम _hfi1_करो_tid_send(काष्ठा work_काष्ठा *work);

bool hfi1_schedule_tid_send(काष्ठा rvt_qp *qp);

bool hfi1_tid_rdma_ack_पूर्णांकerlock(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e);

#पूर्ण_अगर /* HFI1_TID_RDMA_H */
