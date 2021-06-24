<शैली गुरु>
/* SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB */
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#अगर_अघोषित RXE_VERBS_H
#घोषणा RXE_VERBS_H

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/workqueue.h>
#समावेश <rdma/rdma_user_rxe.h>
#समावेश "rxe_pool.h"
#समावेश "rxe_task.h"
#समावेश "rxe_hw_counters.h"

अटल अंतरभूत पूर्णांक pkey_match(u16 key1, u16 key2)
अणु
	वापस (((key1 & 0x7fff) != 0) &&
		((key1 & 0x7fff) == (key2 & 0x7fff)) &&
		((key1 & 0x8000) || (key2 & 0x8000))) ? 1 : 0;
पूर्ण

/* Return >0 अगर psn_a > psn_b
 *	   0 अगर psn_a == psn_b
 *	  <0 अगर psn_a < psn_b
 */
अटल अंतरभूत पूर्णांक psn_compare(u32 psn_a, u32 psn_b)
अणु
	s32 dअगरf;

	dअगरf = (psn_a - psn_b) << 8;
	वापस dअगरf;
पूर्ण

काष्ठा rxe_ucontext अणु
	काष्ठा ib_ucontext ibuc;
	काष्ठा rxe_pool_entry	pelem;
पूर्ण;

काष्ठा rxe_pd अणु
	काष्ठा ib_pd            ibpd;
	काष्ठा rxe_pool_entry	pelem;
पूर्ण;

काष्ठा rxe_ah अणु
	काष्ठा ib_ah		ibah;
	काष्ठा rxe_pool_entry	pelem;
	काष्ठा rxe_pd		*pd;
	काष्ठा rxe_av		av;
पूर्ण;

काष्ठा rxe_cqe अणु
	जोड़ अणु
		काष्ठा ib_wc		ibwc;
		काष्ठा ib_uverbs_wc	uibwc;
	पूर्ण;
पूर्ण;

काष्ठा rxe_cq अणु
	काष्ठा ib_cq		ibcq;
	काष्ठा rxe_pool_entry	pelem;
	काष्ठा rxe_queue	*queue;
	spinlock_t		cq_lock;
	u8			notअगरy;
	bool			is_dying;
	पूर्णांक			is_user;
	काष्ठा tasklet_काष्ठा	comp_task;
पूर्ण;

क्रमागत wqe_state अणु
	wqe_state_posted,
	wqe_state_processing,
	wqe_state_pending,
	wqe_state_करोne,
	wqe_state_error,
पूर्ण;

काष्ठा rxe_sq अणु
	पूर्णांक			max_wr;
	पूर्णांक			max_sge;
	पूर्णांक			max_अंतरभूत;
	spinlock_t		sq_lock; /* guard queue */
	काष्ठा rxe_queue	*queue;
पूर्ण;

काष्ठा rxe_rq अणु
	पूर्णांक			max_wr;
	पूर्णांक			max_sge;
	spinlock_t		producer_lock; /* guard queue producer */
	spinlock_t		consumer_lock; /* guard queue consumer */
	काष्ठा rxe_queue	*queue;
पूर्ण;

काष्ठा rxe_srq अणु
	काष्ठा ib_srq		ibsrq;
	काष्ठा rxe_pool_entry	pelem;
	काष्ठा rxe_pd		*pd;
	काष्ठा rxe_rq		rq;
	u32			srq_num;

	पूर्णांक			limit;
	पूर्णांक			error;
पूर्ण;

क्रमागत rxe_qp_state अणु
	QP_STATE_RESET,
	QP_STATE_INIT,
	QP_STATE_READY,
	QP_STATE_DRAIN,		/* req only */
	QP_STATE_DRAINED,	/* req only */
	QP_STATE_ERROR
पूर्ण;

काष्ठा rxe_req_info अणु
	क्रमागत rxe_qp_state	state;
	पूर्णांक			wqe_index;
	u32			psn;
	पूर्णांक			opcode;
	atomic_t		rd_atomic;
	पूर्णांक			रुको_fence;
	पूर्णांक			need_rd_atomic;
	पूर्णांक			रुको_psn;
	पूर्णांक			need_retry;
	पूर्णांक			noack_pkts;
	काष्ठा rxe_task		task;
पूर्ण;

काष्ठा rxe_comp_info अणु
	u32			psn;
	पूर्णांक			opcode;
	पूर्णांक			समयout;
	पूर्णांक			समयout_retry;
	पूर्णांक			started_retry;
	u32			retry_cnt;
	u32			rnr_retry;
	काष्ठा rxe_task		task;
पूर्ण;

क्रमागत rdaपंचांग_res_state अणु
	rdaपंचांग_res_state_next,
	rdaपंचांग_res_state_new,
	rdaपंचांग_res_state_replay,
पूर्ण;

काष्ठा resp_res अणु
	पूर्णांक			type;
	पूर्णांक			replay;
	u32			first_psn;
	u32			last_psn;
	u32			cur_psn;
	क्रमागत rdaपंचांग_res_state	state;

	जोड़ अणु
		काष्ठा अणु
			काष्ठा sk_buff	*skb;
		पूर्ण atomic;
		काष्ठा अणु
			काष्ठा rxe_mr	*mr;
			u64		va_org;
			u32		rkey;
			u32		length;
			u64		va;
			u32		resid;
		पूर्ण पढ़ो;
	पूर्ण;
पूर्ण;

काष्ठा rxe_resp_info अणु
	क्रमागत rxe_qp_state	state;
	u32			msn;
	u32			psn;
	u32			ack_psn;
	पूर्णांक			opcode;
	पूर्णांक			drop_msg;
	पूर्णांक			जाओ_error;
	पूर्णांक			sent_psn_nak;
	क्रमागत ib_wc_status	status;
	u8			aeth_syndrome;

	/* Receive only */
	काष्ठा rxe_recv_wqe	*wqe;

	/* RDMA पढ़ो / atomic only */
	u64			va;
	काष्ठा rxe_mr		*mr;
	u32			resid;
	u32			rkey;
	u32			length;
	u64			atomic_orig;

	/* SRQ only */
	काष्ठा अणु
		काष्ठा rxe_recv_wqe	wqe;
		काष्ठा ib_sge		sge[RXE_MAX_SGE];
	पूर्ण srq_wqe;

	/* Responder resources. It's a circular list where the oldest
	 * resource is dropped first.
	 */
	काष्ठा resp_res		*resources;
	अचिन्हित पूर्णांक		res_head;
	अचिन्हित पूर्णांक		res_tail;
	काष्ठा resp_res		*res;
	काष्ठा rxe_task		task;
पूर्ण;

काष्ठा rxe_qp अणु
	काष्ठा rxe_pool_entry	pelem;
	काष्ठा ib_qp		ibqp;
	काष्ठा ib_qp_attr	attr;
	अचिन्हित पूर्णांक		valid;
	अचिन्हित पूर्णांक		mtu;
	पूर्णांक			is_user;

	काष्ठा rxe_pd		*pd;
	काष्ठा rxe_srq		*srq;
	काष्ठा rxe_cq		*scq;
	काष्ठा rxe_cq		*rcq;

	क्रमागत ib_sig_type	sq_sig_type;

	काष्ठा rxe_sq		sq;
	काष्ठा rxe_rq		rq;

	काष्ठा socket		*sk;
	u32			dst_cookie;
	u16			src_port;

	काष्ठा rxe_av		pri_av;
	काष्ठा rxe_av		alt_av;

	/* list of mcast groups qp has joined (क्रम cleanup) */
	काष्ठा list_head	grp_list;
	spinlock_t		grp_lock; /* guard grp_list */

	काष्ठा sk_buff_head	req_pkts;
	काष्ठा sk_buff_head	resp_pkts;
	काष्ठा sk_buff_head	send_pkts;

	काष्ठा rxe_req_info	req;
	काष्ठा rxe_comp_info	comp;
	काष्ठा rxe_resp_info	resp;

	atomic_t		ssn;
	atomic_t		skb_out;
	पूर्णांक			need_req_skb;

	/* Timer क्रम retranmitting packet when ACKs have been lost. RC
	 * only. The requester sets it when it is not alपढ़ोy
	 * started. The responder resets it whenever an ack is
	 * received.
	 */
	काष्ठा समयr_list retrans_समयr;
	u64 qp_समयout_jअगरfies;

	/* Timer क्रम handling RNR NAKS. */
	काष्ठा समयr_list rnr_nak_समयr;

	spinlock_t		state_lock; /* guard requester and completer */

	काष्ठा execute_work	cleanup_work;
पूर्ण;

क्रमागत rxe_mr_state अणु
	RXE_MR_STATE_ZOMBIE,
	RXE_MR_STATE_INVALID,
	RXE_MR_STATE_FREE,
	RXE_MR_STATE_VALID,
पूर्ण;

क्रमागत rxe_mr_type अणु
	RXE_MR_TYPE_NONE,
	RXE_MR_TYPE_DMA,
	RXE_MR_TYPE_MR,
	RXE_MR_TYPE_MW,
पूर्ण;

#घोषणा RXE_BUF_PER_MAP		(PAGE_SIZE / माप(काष्ठा rxe_phys_buf))

काष्ठा rxe_phys_buf अणु
	u64      addr;
	u64      size;
पूर्ण;

काष्ठा rxe_map अणु
	काष्ठा rxe_phys_buf	buf[RXE_BUF_PER_MAP];
पूर्ण;

काष्ठा rxe_mr अणु
	काष्ठा rxe_pool_entry	pelem;
	काष्ठा ib_mr		ibmr;

	काष्ठा ib_umem		*umem;

	क्रमागत rxe_mr_state	state;
	क्रमागत rxe_mr_type	type;
	u64			va;
	u64			iova;
	माप_प्रकार			length;
	u32			offset;
	पूर्णांक			access;

	पूर्णांक			page_shअगरt;
	पूर्णांक			page_mask;
	पूर्णांक			map_shअगरt;
	पूर्णांक			map_mask;

	u32			num_buf;
	u32			nbuf;

	u32			max_buf;
	u32			num_map;

	काष्ठा rxe_map		**map;
पूर्ण;

क्रमागत rxe_mw_state अणु
	RXE_MW_STATE_INVALID = RXE_MR_STATE_INVALID,
	RXE_MW_STATE_FREE = RXE_MR_STATE_FREE,
	RXE_MW_STATE_VALID = RXE_MR_STATE_VALID,
पूर्ण;

काष्ठा rxe_mw अणु
	काष्ठा ib_mw ibmw;
	काष्ठा rxe_pool_entry pelem;
पूर्ण;

काष्ठा rxe_mc_grp अणु
	काष्ठा rxe_pool_entry	pelem;
	spinlock_t		mcg_lock; /* guard group */
	काष्ठा rxe_dev		*rxe;
	काष्ठा list_head	qp_list;
	जोड़ ib_gid		mgid;
	पूर्णांक			num_qp;
	u32			qkey;
	u16			pkey;
पूर्ण;

काष्ठा rxe_mc_elem अणु
	काष्ठा rxe_pool_entry	pelem;
	काष्ठा list_head	qp_list;
	काष्ठा list_head	grp_list;
	काष्ठा rxe_qp		*qp;
	काष्ठा rxe_mc_grp	*grp;
पूर्ण;

काष्ठा rxe_port अणु
	काष्ठा ib_port_attr	attr;
	__be64			port_guid;
	__be64			subnet_prefix;
	spinlock_t		port_lock; /* guard port */
	अचिन्हित पूर्णांक		mtu_cap;
	/* special QPs */
	u32			qp_smi_index;
	u32			qp_gsi_index;
पूर्ण;

काष्ठा rxe_dev अणु
	काष्ठा ib_device	ib_dev;
	काष्ठा ib_device_attr	attr;
	पूर्णांक			max_ucontext;
	पूर्णांक			max_अंतरभूत_data;
	काष्ठा mutex	usdev_lock;

	काष्ठा net_device	*ndev;

	पूर्णांक			xmit_errors;

	काष्ठा rxe_pool		uc_pool;
	काष्ठा rxe_pool		pd_pool;
	काष्ठा rxe_pool		ah_pool;
	काष्ठा rxe_pool		srq_pool;
	काष्ठा rxe_pool		qp_pool;
	काष्ठा rxe_pool		cq_pool;
	काष्ठा rxe_pool		mr_pool;
	काष्ठा rxe_pool		mw_pool;
	काष्ठा rxe_pool		mc_grp_pool;
	काष्ठा rxe_pool		mc_elem_pool;

	spinlock_t		pending_lock; /* guard pending_mmaps */
	काष्ठा list_head	pending_mmaps;

	spinlock_t		mmap_offset_lock; /* guard mmap_offset */
	u64			mmap_offset;

	atomic64_t		stats_counters[RXE_NUM_OF_COUNTERS];

	काष्ठा rxe_port		port;
	काष्ठा crypto_shash	*tfm;
पूर्ण;

अटल अंतरभूत व्योम rxe_counter_inc(काष्ठा rxe_dev *rxe, क्रमागत rxe_counters index)
अणु
	atomic64_inc(&rxe->stats_counters[index]);
पूर्ण

अटल अंतरभूत काष्ठा rxe_dev *to_rdev(काष्ठा ib_device *dev)
अणु
	वापस dev ? container_of(dev, काष्ठा rxe_dev, ib_dev) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_ucontext *to_ruc(काष्ठा ib_ucontext *uc)
अणु
	वापस uc ? container_of(uc, काष्ठा rxe_ucontext, ibuc) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_pd *to_rpd(काष्ठा ib_pd *pd)
अणु
	वापस pd ? container_of(pd, काष्ठा rxe_pd, ibpd) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_ah *to_rah(काष्ठा ib_ah *ah)
अणु
	वापस ah ? container_of(ah, काष्ठा rxe_ah, ibah) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_srq *to_rsrq(काष्ठा ib_srq *srq)
अणु
	वापस srq ? container_of(srq, काष्ठा rxe_srq, ibsrq) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_qp *to_rqp(काष्ठा ib_qp *qp)
अणु
	वापस qp ? container_of(qp, काष्ठा rxe_qp, ibqp) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_cq *to_rcq(काष्ठा ib_cq *cq)
अणु
	वापस cq ? container_of(cq, काष्ठा rxe_cq, ibcq) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_mr *to_rmr(काष्ठा ib_mr *mr)
अणु
	वापस mr ? container_of(mr, काष्ठा rxe_mr, ibmr) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_mw *to_rmw(काष्ठा ib_mw *mw)
अणु
	वापस mw ? container_of(mw, काष्ठा rxe_mw, ibmw) : शून्य;
पूर्ण

अटल अंतरभूत काष्ठा rxe_pd *mr_pd(काष्ठा rxe_mr *mr)
अणु
	वापस to_rpd(mr->ibmr.pd);
पूर्ण

अटल अंतरभूत u32 mr_lkey(काष्ठा rxe_mr *mr)
अणु
	वापस mr->ibmr.lkey;
पूर्ण

अटल अंतरभूत u32 mr_rkey(काष्ठा rxe_mr *mr)
अणु
	वापस mr->ibmr.rkey;
पूर्ण

पूर्णांक rxe_रेजिस्टर_device(काष्ठा rxe_dev *rxe, स्थिर अक्षर *ibdev_name);

व्योम rxe_mc_cleanup(काष्ठा rxe_pool_entry *arg);

#पूर्ण_अगर /* RXE_VERBS_H */
