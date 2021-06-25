<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2018 - 2020 Intel Corporation.
 *
 */

#समावेश "hfi.h"
#समावेश "qp.h"
#समावेश "rc.h"
#समावेश "verbs.h"
#समावेश "tid_rdma.h"
#समावेश "exp_rcv.h"
#समावेश "trace.h"

/**
 * DOC: TID RDMA READ protocol
 *
 * This is an end-to-end protocol at the hfi1 level between two nodes that
 * improves perक्रमmance by aव्योमing data copy on the requester side. It
 * converts a qualअगरied RDMA READ request पूर्णांकo a TID RDMA READ request on
 * the requester side and thereafter handles the request and response
 * dअगरferently. To be qualअगरied, the RDMA READ request should meet the
 * following:
 * -- The total data length should be greater than 256K;
 * -- The total data length should be a multiple of 4K page size;
 * -- Each local scatter-gather entry should be 4K page aligned;
 * -- Each local scatter-gather entry should be a multiple of 4K page size;
 */

#घोषणा RCV_TID_FLOW_TABLE_CTRL_FLOW_VALID_SMASK BIT_ULL(32)
#घोषणा RCV_TID_FLOW_TABLE_CTRL_HDR_SUPP_EN_SMASK BIT_ULL(33)
#घोषणा RCV_TID_FLOW_TABLE_CTRL_KEEP_AFTER_SEQ_ERR_SMASK BIT_ULL(34)
#घोषणा RCV_TID_FLOW_TABLE_CTRL_KEEP_ON_GEN_ERR_SMASK BIT_ULL(35)
#घोषणा RCV_TID_FLOW_TABLE_STATUS_SEQ_MISMATCH_SMASK BIT_ULL(37)
#घोषणा RCV_TID_FLOW_TABLE_STATUS_GEN_MISMATCH_SMASK BIT_ULL(38)

/* Maximum number of packets within a flow generation. */
#घोषणा MAX_TID_FLOW_PSN BIT(HFI1_KDETH_BTH_SEQ_SHIFT)

#घोषणा GENERATION_MASK 0xFFFFF

अटल u32 mask_generation(u32 a)
अणु
	वापस a & GENERATION_MASK;
पूर्ण

/* Reserved generation value to set to unused flows क्रम kernel contexts */
#घोषणा KERN_GENERATION_RESERVED mask_generation(U32_MAX)

/*
 * J_KEY क्रम kernel contexts when TID RDMA is used.
 * See generate_jkey() in hfi.h क्रम more inक्रमmation.
 */
#घोषणा TID_RDMA_JKEY                   32
#घोषणा HFI1_KERNEL_MIN_JKEY HFI1_ADMIN_JKEY_RANGE
#घोषणा HFI1_KERNEL_MAX_JKEY (2 * HFI1_ADMIN_JKEY_RANGE - 1)

/* Maximum number of segments in flight per QP request. */
#घोषणा TID_RDMA_MAX_READ_SEGS_PER_REQ  6
#घोषणा TID_RDMA_MAX_WRITE_SEGS_PER_REQ 4
#घोषणा MAX_REQ max_t(u16, TID_RDMA_MAX_READ_SEGS_PER_REQ, \
			TID_RDMA_MAX_WRITE_SEGS_PER_REQ)
#घोषणा MAX_FLOWS roundup_घात_of_two(MAX_REQ + 1)

#घोषणा MAX_EXPECTED_PAGES     (MAX_EXPECTED_BUFFER / PAGE_SIZE)

#घोषणा TID_RDMA_DESTQP_FLOW_SHIFT      11
#घोषणा TID_RDMA_DESTQP_FLOW_MASK       0x1f

#घोषणा TID_OPFN_QP_CTXT_MASK 0xff
#घोषणा TID_OPFN_QP_CTXT_SHIFT 56
#घोषणा TID_OPFN_QP_KDETH_MASK 0xff
#घोषणा TID_OPFN_QP_KDETH_SHIFT 48
#घोषणा TID_OPFN_MAX_LEN_MASK 0x7ff
#घोषणा TID_OPFN_MAX_LEN_SHIFT 37
#घोषणा TID_OPFN_TIMEOUT_MASK 0x1f
#घोषणा TID_OPFN_TIMEOUT_SHIFT 32
#घोषणा TID_OPFN_RESERVED_MASK 0x3f
#घोषणा TID_OPFN_RESERVED_SHIFT 26
#घोषणा TID_OPFN_URG_MASK 0x1
#घोषणा TID_OPFN_URG_SHIFT 25
#घोषणा TID_OPFN_VER_MASK 0x7
#घोषणा TID_OPFN_VER_SHIFT 22
#घोषणा TID_OPFN_JKEY_MASK 0x3f
#घोषणा TID_OPFN_JKEY_SHIFT 16
#घोषणा TID_OPFN_MAX_READ_MASK 0x3f
#घोषणा TID_OPFN_MAX_READ_SHIFT 10
#घोषणा TID_OPFN_MAX_WRITE_MASK 0x3f
#घोषणा TID_OPFN_MAX_WRITE_SHIFT 4

/*
 * OPFN TID layout
 *
 * 63               47               31               15
 * NNNNNNNNKKKKKKKK MMMMMMMMMMMTTTTT DDDDDDUVVVJJJJJJ RRRRRRWWWWWWCCCC
 * 3210987654321098 7654321098765432 1098765432109876 5432109876543210
 * N - the context Number
 * K - the Kdeth_qp
 * M - Max_len
 * T - Timeout
 * D - reserveD
 * V - version
 * U - Urg capable
 * J - Jkey
 * R - max_Read
 * W - max_Write
 * C - Capcode
 */

अटल व्योम tid_rdma_trigger_resume(काष्ठा work_काष्ठा *work);
अटल व्योम hfi1_kern_exp_rcv_मुक्त_flows(काष्ठा tid_rdma_request *req);
अटल पूर्णांक hfi1_kern_exp_rcv_alloc_flows(काष्ठा tid_rdma_request *req,
					 gfp_t gfp);
अटल व्योम hfi1_init_trdma_req(काष्ठा rvt_qp *qp,
				काष्ठा tid_rdma_request *req);
अटल व्योम hfi1_tid_ग_लिखो_alloc_resources(काष्ठा rvt_qp *qp, bool पूर्णांकr_ctx);
अटल व्योम hfi1_tid_समयout(काष्ठा समयr_list *t);
अटल व्योम hfi1_add_tid_reap_समयr(काष्ठा rvt_qp *qp);
अटल व्योम hfi1_mod_tid_reap_समयr(काष्ठा rvt_qp *qp);
अटल व्योम hfi1_mod_tid_retry_समयr(काष्ठा rvt_qp *qp);
अटल पूर्णांक hfi1_stop_tid_retry_समयr(काष्ठा rvt_qp *qp);
अटल व्योम hfi1_tid_retry_समयout(काष्ठा समयr_list *t);
अटल पूर्णांक make_tid_rdma_ack(काष्ठा rvt_qp *qp,
			     काष्ठा ib_other_headers *ohdr,
			     काष्ठा hfi1_pkt_state *ps);
अटल व्योम hfi1_करो_tid_send(काष्ठा rvt_qp *qp);
अटल u32 पढ़ो_r_next_psn(काष्ठा hfi1_devdata *dd, u8 ctxt, u8 fidx);
अटल व्योम tid_rdma_rcv_err(काष्ठा hfi1_packet *packet,
			     काष्ठा ib_other_headers *ohdr,
			     काष्ठा rvt_qp *qp, u32 psn, पूर्णांक dअगरf, bool fecn);
अटल व्योम update_r_next_psn_fecn(काष्ठा hfi1_packet *packet,
				   काष्ठा hfi1_qp_priv *priv,
				   काष्ठा hfi1_ctxtdata *rcd,
				   काष्ठा tid_rdma_flow *flow,
				   bool fecn);

अटल व्योम validate_r_tid_ack(काष्ठा hfi1_qp_priv *priv)
अणु
	अगर (priv->r_tid_ack == HFI1_QP_WQE_INVALID)
		priv->r_tid_ack = priv->r_tid_tail;
पूर्ण

अटल व्योम tid_rdma_schedule_ack(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	priv->s_flags |= RVT_S_ACK_PENDING;
	hfi1_schedule_tid_send(qp);
पूर्ण

अटल व्योम tid_rdma_trigger_ack(काष्ठा rvt_qp *qp)
अणु
	validate_r_tid_ack(qp->priv);
	tid_rdma_schedule_ack(qp);
पूर्ण

अटल u64 tid_rdma_opfn_encode(काष्ठा tid_rdma_params *p)
अणु
	वापस
		(((u64)p->qp & TID_OPFN_QP_CTXT_MASK) <<
			TID_OPFN_QP_CTXT_SHIFT) |
		((((u64)p->qp >> 16) & TID_OPFN_QP_KDETH_MASK) <<
			TID_OPFN_QP_KDETH_SHIFT) |
		(((u64)((p->max_len >> PAGE_SHIFT) - 1) &
			TID_OPFN_MAX_LEN_MASK) << TID_OPFN_MAX_LEN_SHIFT) |
		(((u64)p->समयout & TID_OPFN_TIMEOUT_MASK) <<
			TID_OPFN_TIMEOUT_SHIFT) |
		(((u64)p->urg & TID_OPFN_URG_MASK) << TID_OPFN_URG_SHIFT) |
		(((u64)p->jkey & TID_OPFN_JKEY_MASK) << TID_OPFN_JKEY_SHIFT) |
		(((u64)p->max_पढ़ो & TID_OPFN_MAX_READ_MASK) <<
			TID_OPFN_MAX_READ_SHIFT) |
		(((u64)p->max_ग_लिखो & TID_OPFN_MAX_WRITE_MASK) <<
			TID_OPFN_MAX_WRITE_SHIFT);
पूर्ण

अटल व्योम tid_rdma_opfn_decode(काष्ठा tid_rdma_params *p, u64 data)
अणु
	p->max_len = (((data >> TID_OPFN_MAX_LEN_SHIFT) &
		TID_OPFN_MAX_LEN_MASK) + 1) << PAGE_SHIFT;
	p->jkey = (data >> TID_OPFN_JKEY_SHIFT) & TID_OPFN_JKEY_MASK;
	p->max_ग_लिखो = (data >> TID_OPFN_MAX_WRITE_SHIFT) &
		TID_OPFN_MAX_WRITE_MASK;
	p->max_पढ़ो = (data >> TID_OPFN_MAX_READ_SHIFT) &
		TID_OPFN_MAX_READ_MASK;
	p->qp =
		((((data >> TID_OPFN_QP_KDETH_SHIFT) & TID_OPFN_QP_KDETH_MASK)
			<< 16) |
		((data >> TID_OPFN_QP_CTXT_SHIFT) & TID_OPFN_QP_CTXT_MASK));
	p->urg = (data >> TID_OPFN_URG_SHIFT) & TID_OPFN_URG_MASK;
	p->समयout = (data >> TID_OPFN_TIMEOUT_SHIFT) & TID_OPFN_TIMEOUT_MASK;
पूर्ण

व्योम tid_rdma_opfn_init(काष्ठा rvt_qp *qp, काष्ठा tid_rdma_params *p)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	p->qp = (RVT_KDETH_QP_PREFIX << 16) | priv->rcd->ctxt;
	p->max_len = TID_RDMA_MAX_SEGMENT_SIZE;
	p->jkey = priv->rcd->jkey;
	p->max_पढ़ो = TID_RDMA_MAX_READ_SEGS_PER_REQ;
	p->max_ग_लिखो = TID_RDMA_MAX_WRITE_SEGS_PER_REQ;
	p->समयout = qp->समयout;
	p->urg = is_urg_masked(priv->rcd);
पूर्ण

bool tid_rdma_conn_req(काष्ठा rvt_qp *qp, u64 *data)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	*data = tid_rdma_opfn_encode(&priv->tid_rdma.local);
	वापस true;
पूर्ण

bool tid_rdma_conn_reply(काष्ठा rvt_qp *qp, u64 data)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा tid_rdma_params *remote, *old;
	bool ret = true;

	old = rcu_dereference_रक्षित(priv->tid_rdma.remote,
					lockdep_is_held(&priv->opfn.lock));
	data &= ~0xfULL;
	/*
	 * If data passed in is zero, वापस true so as not to जारी the
	 * negotiation process
	 */
	अगर (!data || !HFI1_CAP_IS_KSET(TID_RDMA))
		जाओ null;
	/*
	 * If kzalloc fails, वापस false. This will result in:
	 * * at the requester a new OPFN request being generated to retry
	 *   the negotiation
	 * * at the responder, 0 being वापसed to the requester so as to
	 *   disable TID RDMA at both the requester and the responder
	 */
	remote = kzalloc(माप(*remote), GFP_ATOMIC);
	अगर (!remote) अणु
		ret = false;
		जाओ null;
	पूर्ण

	tid_rdma_opfn_decode(remote, data);
	priv->tid_समयr_समयout_jअगरfies =
		usecs_to_jअगरfies((((4096UL * (1UL << remote->समयout)) /
				   1000UL) << 3) * 7);
	trace_hfi1_opfn_param(qp, 0, &priv->tid_rdma.local);
	trace_hfi1_opfn_param(qp, 1, remote);
	rcu_assign_poपूर्णांकer(priv->tid_rdma.remote, remote);
	/*
	 * A TID RDMA READ request's segment size is not equal to
	 * remote->max_len only when the request's data length is smaller
	 * than remote->max_len. In that हाल, there will be only one segment.
	 * Thereक्रमe, when priv->pkts_ps is used to calculate req->cur_seg
	 * during retry, it will lead to req->cur_seg = 0, which is exactly
	 * what is expected.
	 */
	priv->pkts_ps = (u16)rvt_भाग_mtu(qp, remote->max_len);
	priv->समयout_shअगरt = ilog2(priv->pkts_ps - 1) + 1;
	जाओ मुक्त;
null:
	RCU_INIT_POINTER(priv->tid_rdma.remote, शून्य);
	priv->समयout_shअगरt = 0;
मुक्त:
	अगर (old)
		kमुक्त_rcu(old, rcu_head);
	वापस ret;
पूर्ण

bool tid_rdma_conn_resp(काष्ठा rvt_qp *qp, u64 *data)
अणु
	bool ret;

	ret = tid_rdma_conn_reply(qp, *data);
	*data = 0;
	/*
	 * If tid_rdma_conn_reply() वापसs error, set *data as 0 to indicate
	 * TID RDMA could not be enabled. This will result in TID RDMA being
	 * disabled at the requester too.
	 */
	अगर (ret)
		(व्योम)tid_rdma_conn_req(qp, data);
	वापस ret;
पूर्ण

व्योम tid_rdma_conn_error(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा tid_rdma_params *old;

	old = rcu_dereference_रक्षित(priv->tid_rdma.remote,
					lockdep_is_held(&priv->opfn.lock));
	RCU_INIT_POINTER(priv->tid_rdma.remote, शून्य);
	अगर (old)
		kमुक्त_rcu(old, rcu_head);
पूर्ण

/* This is called at context initialization समय */
पूर्णांक hfi1_kern_exp_rcv_init(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक reinit)
अणु
	अगर (reinit)
		वापस 0;

	BUILD_BUG_ON(TID_RDMA_JKEY < HFI1_KERNEL_MIN_JKEY);
	BUILD_BUG_ON(TID_RDMA_JKEY > HFI1_KERNEL_MAX_JKEY);
	rcd->jkey = TID_RDMA_JKEY;
	hfi1_set_ctxt_jkey(rcd->dd, rcd, rcd->jkey);
	वापस hfi1_alloc_ctxt_rcv_groups(rcd);
पूर्ण

/**
 * qp_to_rcd - determine the receive context used by a qp
 * @rdi: rvt dev काष्ठा
 * @qp: the qp
 *
 * This routine वापसs the receive context associated
 * with a a qp's qpn.
 *
 * Returns the context.
 */
अटल काष्ठा hfi1_ctxtdata *qp_to_rcd(काष्ठा rvt_dev_info *rdi,
				       काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_ibdev *verbs_dev = container_of(rdi,
						    काष्ठा hfi1_ibdev,
						    rdi);
	काष्ठा hfi1_devdata *dd = container_of(verbs_dev,
					       काष्ठा hfi1_devdata,
					       verbs_dev);
	अचिन्हित पूर्णांक ctxt;

	अगर (qp->ibqp.qp_num == 0)
		ctxt = 0;
	अन्यथा
		ctxt = hfi1_get_qp_map(dd, qp->ibqp.qp_num >> dd->qos_shअगरt);
	वापस dd->rcd[ctxt];
पूर्ण

पूर्णांक hfi1_qp_priv_init(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp,
		      काष्ठा ib_qp_init_attr *init_attr)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	पूर्णांक i, ret;

	qpriv->rcd = qp_to_rcd(rdi, qp);

	spin_lock_init(&qpriv->opfn.lock);
	INIT_WORK(&qpriv->opfn.opfn_work, opfn_send_conn_request);
	INIT_WORK(&qpriv->tid_rdma.trigger_work, tid_rdma_trigger_resume);
	qpriv->flow_state.psn = 0;
	qpriv->flow_state.index = RXE_NUM_TID_FLOWS;
	qpriv->flow_state.last_index = RXE_NUM_TID_FLOWS;
	qpriv->flow_state.generation = KERN_GENERATION_RESERVED;
	qpriv->s_state = TID_OP(WRITE_RESP);
	qpriv->s_tid_cur = HFI1_QP_WQE_INVALID;
	qpriv->s_tid_head = HFI1_QP_WQE_INVALID;
	qpriv->s_tid_tail = HFI1_QP_WQE_INVALID;
	qpriv->rnr_nak_state = TID_RNR_NAK_INIT;
	qpriv->r_tid_head = HFI1_QP_WQE_INVALID;
	qpriv->r_tid_tail = HFI1_QP_WQE_INVALID;
	qpriv->r_tid_ack = HFI1_QP_WQE_INVALID;
	qpriv->r_tid_alloc = HFI1_QP_WQE_INVALID;
	atomic_set(&qpriv->n_requests, 0);
	atomic_set(&qpriv->n_tid_requests, 0);
	समयr_setup(&qpriv->s_tid_समयr, hfi1_tid_समयout, 0);
	समयr_setup(&qpriv->s_tid_retry_समयr, hfi1_tid_retry_समयout, 0);
	INIT_LIST_HEAD(&qpriv->tid_रुको);

	अगर (init_attr->qp_type == IB_QPT_RC && HFI1_CAP_IS_KSET(TID_RDMA)) अणु
		काष्ठा hfi1_devdata *dd = qpriv->rcd->dd;

		qpriv->pages = kzalloc_node(TID_RDMA_MAX_PAGES *
						माप(*qpriv->pages),
					    GFP_KERNEL, dd->node);
		अगर (!qpriv->pages)
			वापस -ENOMEM;
		क्रम (i = 0; i < qp->s_size; i++) अणु
			काष्ठा hfi1_swqe_priv *priv;
			काष्ठा rvt_swqe *wqe = rvt_get_swqe_ptr(qp, i);

			priv = kzalloc_node(माप(*priv), GFP_KERNEL,
					    dd->node);
			अगर (!priv)
				वापस -ENOMEM;

			hfi1_init_trdma_req(qp, &priv->tid_req);
			priv->tid_req.e.swqe = wqe;
			wqe->priv = priv;
		पूर्ण
		क्रम (i = 0; i < rvt_max_atomic(rdi); i++) अणु
			काष्ठा hfi1_ack_priv *priv;

			priv = kzalloc_node(माप(*priv), GFP_KERNEL,
					    dd->node);
			अगर (!priv)
				वापस -ENOMEM;

			hfi1_init_trdma_req(qp, &priv->tid_req);
			priv->tid_req.e.ack = &qp->s_ack_queue[i];

			ret = hfi1_kern_exp_rcv_alloc_flows(&priv->tid_req,
							    GFP_KERNEL);
			अगर (ret) अणु
				kमुक्त(priv);
				वापस ret;
			पूर्ण
			qp->s_ack_queue[i].priv = priv;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

व्योम hfi1_qp_priv_tid_मुक्त(काष्ठा rvt_dev_info *rdi, काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा rvt_swqe *wqe;
	u32 i;

	अगर (qp->ibqp.qp_type == IB_QPT_RC && HFI1_CAP_IS_KSET(TID_RDMA)) अणु
		क्रम (i = 0; i < qp->s_size; i++) अणु
			wqe = rvt_get_swqe_ptr(qp, i);
			kमुक्त(wqe->priv);
			wqe->priv = शून्य;
		पूर्ण
		क्रम (i = 0; i < rvt_max_atomic(rdi); i++) अणु
			काष्ठा hfi1_ack_priv *priv = qp->s_ack_queue[i].priv;

			अगर (priv)
				hfi1_kern_exp_rcv_मुक्त_flows(&priv->tid_req);
			kमुक्त(priv);
			qp->s_ack_queue[i].priv = शून्य;
		पूर्ण
		cancel_work_sync(&qpriv->opfn.opfn_work);
		kमुक्त(qpriv->pages);
		qpriv->pages = शून्य;
	पूर्ण
पूर्ण

/* Flow and tid रुकोer functions */
/**
 * DOC: lock ordering
 *
 * There are two locks involved with the queuing
 * routines: the qp s_lock and the exp_lock.
 *
 * Since the tid space allocation is called from
 * the send engine, the qp s_lock is alपढ़ोy held.
 *
 * The allocation routines will get the exp_lock.
 *
 * The first_qp() call is provided to allow the head of
 * the rcd रुको queue to be fetched under the exp_lock and
 * followed by a drop of the exp_lock.
 *
 * Any qp in the रुको list will have the qp reference count held
 * to hold the qp in memory.
 */

/*
 * वापस head of rcd रुको list
 *
 * Must hold the exp_lock.
 *
 * Get a reference to the QP to hold the QP in memory.
 *
 * The caller must release the reference when the local
 * is no दीर्घer being used.
 */
अटल काष्ठा rvt_qp *first_qp(काष्ठा hfi1_ctxtdata *rcd,
			       काष्ठा tid_queue *queue)
	__must_hold(&rcd->exp_lock)
अणु
	काष्ठा hfi1_qp_priv *priv;

	lockdep_निश्चित_held(&rcd->exp_lock);
	priv = list_first_entry_or_null(&queue->queue_head,
					काष्ठा hfi1_qp_priv,
					tid_रुको);
	अगर (!priv)
		वापस शून्य;
	rvt_get_qp(priv->owner);
	वापस priv->owner;
पूर्ण

/**
 * kernel_tid_रुकोers - determine rcd रुको
 * @rcd: the receive context
 * @queue: the queue to operate on
 * @qp: the head of the qp being processed
 *
 * This routine will वापस false IFF
 * the list is शून्य or the head of the
 * list is the indicated qp.
 *
 * Must hold the qp s_lock and the exp_lock.
 *
 * Return:
 * false अगर either of the conditions below are satisfied:
 * 1. The list is empty or
 * 2. The indicated qp is at the head of the list and the
 *    HFI1_S_WAIT_TID_SPACE bit is set in qp->s_flags.
 * true is वापसed otherwise.
 */
अटल bool kernel_tid_रुकोers(काष्ठा hfi1_ctxtdata *rcd,
			       काष्ठा tid_queue *queue, काष्ठा rvt_qp *qp)
	__must_hold(&rcd->exp_lock) __must_hold(&qp->s_lock)
अणु
	काष्ठा rvt_qp *fqp;
	bool ret = true;

	lockdep_निश्चित_held(&qp->s_lock);
	lockdep_निश्चित_held(&rcd->exp_lock);
	fqp = first_qp(rcd, queue);
	अगर (!fqp || (fqp == qp && (qp->s_flags & HFI1_S_WAIT_TID_SPACE)))
		ret = false;
	rvt_put_qp(fqp);
	वापस ret;
पूर्ण

/**
 * dequeue_tid_रुकोer - dequeue the qp from the list
 * @rcd: the receive context
 * @queue: the queue to operate on
 * @qp: the qp to हटाओ the रुको list
 *
 * This routine हटाओs the indicated qp from the
 * रुको list अगर it is there.
 *
 * This should be करोne after the hardware flow and
 * tid array resources have been allocated.
 *
 * Must hold the qp s_lock and the rcd exp_lock.
 *
 * It assumes the s_lock to protect the s_flags
 * field and to reliably test the HFI1_S_WAIT_TID_SPACE flag.
 */
अटल व्योम dequeue_tid_रुकोer(काष्ठा hfi1_ctxtdata *rcd,
			       काष्ठा tid_queue *queue, काष्ठा rvt_qp *qp)
	__must_hold(&rcd->exp_lock) __must_hold(&qp->s_lock)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	lockdep_निश्चित_held(&qp->s_lock);
	lockdep_निश्चित_held(&rcd->exp_lock);
	अगर (list_empty(&priv->tid_रुको))
		वापस;
	list_del_init(&priv->tid_रुको);
	qp->s_flags &= ~HFI1_S_WAIT_TID_SPACE;
	queue->dequeue++;
	rvt_put_qp(qp);
पूर्ण

/**
 * queue_qp_क्रम_tid_रुको - suspend QP on tid space
 * @rcd: the receive context
 * @queue: the queue to operate on
 * @qp: the qp
 *
 * The qp is inserted at the tail of the rcd
 * रुको queue and the HFI1_S_WAIT_TID_SPACE s_flag is set.
 *
 * Must hold the qp s_lock and the exp_lock.
 */
अटल व्योम queue_qp_क्रम_tid_रुको(काष्ठा hfi1_ctxtdata *rcd,
				  काष्ठा tid_queue *queue, काष्ठा rvt_qp *qp)
	__must_hold(&rcd->exp_lock) __must_hold(&qp->s_lock)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	lockdep_निश्चित_held(&qp->s_lock);
	lockdep_निश्चित_held(&rcd->exp_lock);
	अगर (list_empty(&priv->tid_रुको)) अणु
		qp->s_flags |= HFI1_S_WAIT_TID_SPACE;
		list_add_tail(&priv->tid_रुको, &queue->queue_head);
		priv->tid_enqueue = ++queue->enqueue;
		rcd->dd->verbs_dev.n_tidरुको++;
		trace_hfi1_qpsleep(qp, HFI1_S_WAIT_TID_SPACE);
		rvt_get_qp(qp);
	पूर्ण
पूर्ण

/**
 * __trigger_tid_रुकोer - trigger tid रुकोer
 * @qp: the qp
 *
 * This is a निजी entrance to schedule the qp
 * assuming the caller is holding the qp->s_lock.
 */
अटल व्योम __trigger_tid_रुकोer(काष्ठा rvt_qp *qp)
	__must_hold(&qp->s_lock)
अणु
	lockdep_निश्चित_held(&qp->s_lock);
	अगर (!(qp->s_flags & HFI1_S_WAIT_TID_SPACE))
		वापस;
	trace_hfi1_qpwakeup(qp, HFI1_S_WAIT_TID_SPACE);
	hfi1_schedule_send(qp);
पूर्ण

/**
 * tid_rdma_schedule_tid_wakeup - schedule wakeup क्रम a qp
 * @qp: the qp
 *
 * trigger a schedule or a रुकोing qp in a deadlock
 * safe manner.  The qp reference is held prior
 * to this call via first_qp().
 *
 * If the qp trigger was alपढ़ोy scheduled (!rval)
 * the the reference is dropped, otherwise the resume
 * or the destroy cancel will dispatch the reference.
 */
अटल व्योम tid_rdma_schedule_tid_wakeup(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा hfi1_pportdata *ppd;
	काष्ठा hfi1_devdata *dd;
	bool rval;

	अगर (!qp)
		वापस;

	priv = qp->priv;
	ibp = to_iport(qp->ibqp.device, qp->port_num);
	ppd = ppd_from_ibp(ibp);
	dd = dd_from_ibdev(qp->ibqp.device);

	rval = queue_work_on(priv->s_sde ?
			     priv->s_sde->cpu :
			     cpumask_first(cpumask_of_node(dd->node)),
			     ppd->hfi1_wq,
			     &priv->tid_rdma.trigger_work);
	अगर (!rval)
		rvt_put_qp(qp);
पूर्ण

/**
 * tid_rdma_trigger_resume - field a trigger work request
 * @work: the work item
 *
 * Complete the off qp trigger processing by directly
 * calling the progress routine.
 */
अटल व्योम tid_rdma_trigger_resume(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा tid_rdma_qp_params *tr;
	काष्ठा hfi1_qp_priv *priv;
	काष्ठा rvt_qp *qp;

	tr = container_of(work, काष्ठा tid_rdma_qp_params, trigger_work);
	priv = container_of(tr, काष्ठा hfi1_qp_priv, tid_rdma);
	qp = priv->owner;
	spin_lock_irq(&qp->s_lock);
	अगर (qp->s_flags & HFI1_S_WAIT_TID_SPACE) अणु
		spin_unlock_irq(&qp->s_lock);
		hfi1_करो_send(priv->owner, true);
	पूर्ण अन्यथा अणु
		spin_unlock_irq(&qp->s_lock);
	पूर्ण
	rvt_put_qp(qp);
पूर्ण

/*
 * tid_rdma_flush_रुको - unwind any tid space रुको
 *
 * This is called when resetting a qp to
 * allow a destroy or reset to get rid
 * of any tid space linkage and reference counts.
 */
अटल व्योम _tid_rdma_flush_रुको(काष्ठा rvt_qp *qp, काष्ठा tid_queue *queue)
	__must_hold(&qp->s_lock)
अणु
	काष्ठा hfi1_qp_priv *priv;

	अगर (!qp)
		वापस;
	lockdep_निश्चित_held(&qp->s_lock);
	priv = qp->priv;
	qp->s_flags &= ~HFI1_S_WAIT_TID_SPACE;
	spin_lock(&priv->rcd->exp_lock);
	अगर (!list_empty(&priv->tid_रुको)) अणु
		list_del_init(&priv->tid_रुको);
		qp->s_flags &= ~HFI1_S_WAIT_TID_SPACE;
		queue->dequeue++;
		rvt_put_qp(qp);
	पूर्ण
	spin_unlock(&priv->rcd->exp_lock);
पूर्ण

व्योम hfi1_tid_rdma_flush_रुको(काष्ठा rvt_qp *qp)
	__must_hold(&qp->s_lock)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	_tid_rdma_flush_रुको(qp, &priv->rcd->flow_queue);
	_tid_rdma_flush_रुको(qp, &priv->rcd->rarr_queue);
पूर्ण

/* Flow functions */
/**
 * kern_reserve_flow - allocate a hardware flow
 * @rcd: the context to use क्रम allocation
 * @last: the index of the preferred flow. Use RXE_NUM_TID_FLOWS to
 *         signअगरy "don't care".
 *
 * Use a bit mask based allocation to reserve a hardware
 * flow क्रम use in receiving KDETH data packets. If a preferred flow is
 * specअगरied the function will attempt to reserve that flow again, अगर
 * available.
 *
 * The exp_lock must be held.
 *
 * Return:
 * On success: a value postive value between 0 and RXE_NUM_TID_FLOWS - 1
 * On failure: -EAGAIN
 */
अटल पूर्णांक kern_reserve_flow(काष्ठा hfi1_ctxtdata *rcd, पूर्णांक last)
	__must_hold(&rcd->exp_lock)
अणु
	पूर्णांक nr;

	/* Attempt to reserve the preferred flow index */
	अगर (last >= 0 && last < RXE_NUM_TID_FLOWS &&
	    !test_and_set_bit(last, &rcd->flow_mask))
		वापस last;

	nr = ffz(rcd->flow_mask);
	BUILD_BUG_ON(RXE_NUM_TID_FLOWS >=
		     (माप(rcd->flow_mask) * BITS_PER_BYTE));
	अगर (nr > (RXE_NUM_TID_FLOWS - 1))
		वापस -EAGAIN;
	set_bit(nr, &rcd->flow_mask);
	वापस nr;
पूर्ण

अटल व्योम kern_set_hw_flow(काष्ठा hfi1_ctxtdata *rcd, u32 generation,
			     u32 flow_idx)
अणु
	u64 reg;

	reg = ((u64)generation << HFI1_KDETH_BTH_SEQ_SHIFT) |
		RCV_TID_FLOW_TABLE_CTRL_FLOW_VALID_SMASK |
		RCV_TID_FLOW_TABLE_CTRL_KEEP_AFTER_SEQ_ERR_SMASK |
		RCV_TID_FLOW_TABLE_CTRL_KEEP_ON_GEN_ERR_SMASK |
		RCV_TID_FLOW_TABLE_STATUS_SEQ_MISMATCH_SMASK |
		RCV_TID_FLOW_TABLE_STATUS_GEN_MISMATCH_SMASK;

	अगर (generation != KERN_GENERATION_RESERVED)
		reg |= RCV_TID_FLOW_TABLE_CTRL_HDR_SUPP_EN_SMASK;

	ग_लिखो_uctxt_csr(rcd->dd, rcd->ctxt,
			RCV_TID_FLOW_TABLE + 8 * flow_idx, reg);
पूर्ण

अटल u32 kern_setup_hw_flow(काष्ठा hfi1_ctxtdata *rcd, u32 flow_idx)
	__must_hold(&rcd->exp_lock)
अणु
	u32 generation = rcd->flows[flow_idx].generation;

	kern_set_hw_flow(rcd, generation, flow_idx);
	वापस generation;
पूर्ण

अटल u32 kern_flow_generation_next(u32 gen)
अणु
	u32 generation = mask_generation(gen + 1);

	अगर (generation == KERN_GENERATION_RESERVED)
		generation = mask_generation(generation + 1);
	वापस generation;
पूर्ण

अटल व्योम kern_clear_hw_flow(काष्ठा hfi1_ctxtdata *rcd, u32 flow_idx)
	__must_hold(&rcd->exp_lock)
अणु
	rcd->flows[flow_idx].generation =
		kern_flow_generation_next(rcd->flows[flow_idx].generation);
	kern_set_hw_flow(rcd, KERN_GENERATION_RESERVED, flow_idx);
पूर्ण

पूर्णांक hfi1_kern_setup_hw_flow(काष्ठा hfi1_ctxtdata *rcd, काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *qpriv = (काष्ठा hfi1_qp_priv *)qp->priv;
	काष्ठा tid_flow_state *fs = &qpriv->flow_state;
	काष्ठा rvt_qp *fqp;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	/* The QP alपढ़ोy has an allocated flow */
	अगर (fs->index != RXE_NUM_TID_FLOWS)
		वापस ret;

	spin_lock_irqsave(&rcd->exp_lock, flags);
	अगर (kernel_tid_रुकोers(rcd, &rcd->flow_queue, qp))
		जाओ queue;

	ret = kern_reserve_flow(rcd, fs->last_index);
	अगर (ret < 0)
		जाओ queue;
	fs->index = ret;
	fs->last_index = fs->index;

	/* Generation received in a RESYNC overrides शेष flow generation */
	अगर (fs->generation != KERN_GENERATION_RESERVED)
		rcd->flows[fs->index].generation = fs->generation;
	fs->generation = kern_setup_hw_flow(rcd, fs->index);
	fs->psn = 0;
	dequeue_tid_रुकोer(rcd, &rcd->flow_queue, qp);
	/* get head beक्रमe dropping lock */
	fqp = first_qp(rcd, &rcd->flow_queue);
	spin_unlock_irqrestore(&rcd->exp_lock, flags);

	tid_rdma_schedule_tid_wakeup(fqp);
	वापस 0;
queue:
	queue_qp_क्रम_tid_रुको(rcd, &rcd->flow_queue, qp);
	spin_unlock_irqrestore(&rcd->exp_lock, flags);
	वापस -EAGAIN;
पूर्ण

व्योम hfi1_kern_clear_hw_flow(काष्ठा hfi1_ctxtdata *rcd, काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *qpriv = (काष्ठा hfi1_qp_priv *)qp->priv;
	काष्ठा tid_flow_state *fs = &qpriv->flow_state;
	काष्ठा rvt_qp *fqp;
	अचिन्हित दीर्घ flags;

	अगर (fs->index >= RXE_NUM_TID_FLOWS)
		वापस;
	spin_lock_irqsave(&rcd->exp_lock, flags);
	kern_clear_hw_flow(rcd, fs->index);
	clear_bit(fs->index, &rcd->flow_mask);
	fs->index = RXE_NUM_TID_FLOWS;
	fs->psn = 0;
	fs->generation = KERN_GENERATION_RESERVED;

	/* get head beक्रमe dropping lock */
	fqp = first_qp(rcd, &rcd->flow_queue);
	spin_unlock_irqrestore(&rcd->exp_lock, flags);

	अगर (fqp == qp) अणु
		__trigger_tid_रुकोer(fqp);
		rvt_put_qp(fqp);
	पूर्ण अन्यथा अणु
		tid_rdma_schedule_tid_wakeup(fqp);
	पूर्ण
पूर्ण

व्योम hfi1_kern_init_ctxt_generations(काष्ठा hfi1_ctxtdata *rcd)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < RXE_NUM_TID_FLOWS; i++) अणु
		rcd->flows[i].generation = mask_generation(pअक्रमom_u32());
		kern_set_hw_flow(rcd, KERN_GENERATION_RESERVED, i);
	पूर्ण
पूर्ण

/* TID allocation functions */
अटल u8 trdma_pset_order(काष्ठा tid_rdma_pageset *s)
अणु
	u8 count = s->count;

	वापस ilog2(count) + 1;
पूर्ण

/**
 * tid_rdma_find_phys_blocks_4k - get groups base on mr info
 * @flow: overall info क्रम a TID RDMA segment
 * @pages: poपूर्णांकer to an array of page काष्ठाs
 * @npages: number of pages
 * @list: page set array to वापस
 *
 * This routine वापसs the number of groups associated with
 * the current sge inक्रमmation.  This implementation is based
 * on the expected receive find_phys_blocks() adjusted to
 * use the MR inक्रमmation vs. the pfn.
 *
 * Return:
 * the number of RcvArray entries
 */
अटल u32 tid_rdma_find_phys_blocks_4k(काष्ठा tid_rdma_flow *flow,
					काष्ठा page **pages,
					u32 npages,
					काष्ठा tid_rdma_pageset *list)
अणु
	u32 pagecount, pageidx, setcount = 0, i;
	व्योम *vaddr, *this_vaddr;

	अगर (!npages)
		वापस 0;

	/*
	 * Look क्रम sets of physically contiguous pages in the user buffer.
	 * This will allow us to optimize Expected RcvArray entry usage by
	 * using the bigger supported sizes.
	 */
	vaddr = page_address(pages[0]);
	trace_hfi1_tid_flow_page(flow->req->qp, flow, 0, 0, 0, vaddr);
	क्रम (pageidx = 0, pagecount = 1, i = 1; i <= npages; i++) अणु
		this_vaddr = i < npages ? page_address(pages[i]) : शून्य;
		trace_hfi1_tid_flow_page(flow->req->qp, flow, i, 0, 0,
					 this_vaddr);
		/*
		 * If the vaddr's are not sequential, pages are not physically
		 * contiguous.
		 */
		अगर (this_vaddr != (vaddr + PAGE_SIZE)) अणु
			/*
			 * At this poपूर्णांक we have to loop over the set of
			 * physically contiguous pages and अवरोध them करोwn it
			 * sizes supported by the HW.
			 * There are two मुख्य स्थिरraपूर्णांकs:
			 *     1. The max buffer size is MAX_EXPECTED_BUFFER.
			 *        If the total set size is bigger than that
			 *        program only a MAX_EXPECTED_BUFFER chunk.
			 *     2. The buffer size has to be a घातer of two. If
			 *        it is not, round करोwn to the बंदs घातer of
			 *        2 and program that size.
			 */
			जबतक (pagecount) अणु
				पूर्णांक maxpages = pagecount;
				u32 bufsize = pagecount * PAGE_SIZE;

				अगर (bufsize > MAX_EXPECTED_BUFFER)
					maxpages =
						MAX_EXPECTED_BUFFER >>
						PAGE_SHIFT;
				अन्यथा अगर (!is_घातer_of_2(bufsize))
					maxpages =
						roundकरोwn_घात_of_two(bufsize) >>
						PAGE_SHIFT;

				list[setcount].idx = pageidx;
				list[setcount].count = maxpages;
				trace_hfi1_tid_pageset(flow->req->qp, setcount,
						       list[setcount].idx,
						       list[setcount].count);
				pagecount -= maxpages;
				pageidx += maxpages;
				setcount++;
			पूर्ण
			pageidx = i;
			pagecount = 1;
			vaddr = this_vaddr;
		पूर्ण अन्यथा अणु
			vaddr += PAGE_SIZE;
			pagecount++;
		पूर्ण
	पूर्ण
	/* insure we always वापस an even number of sets */
	अगर (setcount & 1)
		list[setcount++].count = 0;
	वापस setcount;
पूर्ण

/**
 * tid_flush_pages - dump out pages पूर्णांकo pagesets
 * @list: list of pagesets
 * @idx: poपूर्णांकer to current page index
 * @pages: number of pages to dump
 * @sets: current number of pagesset
 *
 * This routine flushes out accumuated pages.
 *
 * To insure an even number of sets the
 * code may add a filler.
 *
 * This can happen with when pages is not
 * a घातer of 2 or pages is a घातer of 2
 * less than the maximum pages.
 *
 * Return:
 * The new number of sets
 */

अटल u32 tid_flush_pages(काष्ठा tid_rdma_pageset *list,
			   u32 *idx, u32 pages, u32 sets)
अणु
	जबतक (pages) अणु
		u32 maxpages = pages;

		अगर (maxpages > MAX_EXPECTED_PAGES)
			maxpages = MAX_EXPECTED_PAGES;
		अन्यथा अगर (!is_घातer_of_2(maxpages))
			maxpages = roundकरोwn_घात_of_two(maxpages);
		list[sets].idx = *idx;
		list[sets++].count = maxpages;
		*idx += maxpages;
		pages -= maxpages;
	पूर्ण
	/* might need a filler */
	अगर (sets & 1)
		list[sets++].count = 0;
	वापस sets;
पूर्ण

/**
 * tid_rdma_find_phys_blocks_8k - get groups base on mr info
 * @flow: overall info क्रम a TID RDMA segment
 * @pages: poपूर्णांकer to an array of page काष्ठाs
 * @npages: number of pages
 * @list: page set array to वापस
 *
 * This routine parses an array of pages to compute pagesets
 * in an 8k compatible way.
 *
 * pages are tested two at a समय, i, i + 1 क्रम contiguous
 * pages and i - 1 and i contiguous pages.
 *
 * If any condition is false, any accumlated pages are flushed and
 * v0,v1 are emitted as separate PAGE_SIZE pagesets
 *
 * Otherwise, the current 8k is totaled क्रम a future flush.
 *
 * Return:
 * The number of pagesets
 * list set with the वापसed number of pagesets
 *
 */
अटल u32 tid_rdma_find_phys_blocks_8k(काष्ठा tid_rdma_flow *flow,
					काष्ठा page **pages,
					u32 npages,
					काष्ठा tid_rdma_pageset *list)
अणु
	u32 idx, sets = 0, i;
	u32 pagecnt = 0;
	व्योम *v0, *v1, *vm1;

	अगर (!npages)
		वापस 0;
	क्रम (idx = 0, i = 0, vm1 = शून्य; i < npages; i += 2) अणु
		/* get a new v0 */
		v0 = page_address(pages[i]);
		trace_hfi1_tid_flow_page(flow->req->qp, flow, i, 1, 0, v0);
		v1 = i + 1 < npages ?
				page_address(pages[i + 1]) : शून्य;
		trace_hfi1_tid_flow_page(flow->req->qp, flow, i, 1, 1, v1);
		/* compare i, i + 1 vaddr */
		अगर (v1 != (v0 + PAGE_SIZE)) अणु
			/* flush out pages */
			sets = tid_flush_pages(list, &idx, pagecnt, sets);
			/* output v0,v1 as two pagesets */
			list[sets].idx = idx++;
			list[sets++].count = 1;
			अगर (v1) अणु
				list[sets].count = 1;
				list[sets++].idx = idx++;
			पूर्ण अन्यथा अणु
				list[sets++].count = 0;
			पूर्ण
			vm1 = शून्य;
			pagecnt = 0;
			जारी;
		पूर्ण
		/* i,i+1 consecutive, look at i-1,i */
		अगर (vm1 && v0 != (vm1 + PAGE_SIZE)) अणु
			/* flush out pages */
			sets = tid_flush_pages(list, &idx, pagecnt, sets);
			pagecnt = 0;
		पूर्ण
		/* pages will always be a multiple of 8k */
		pagecnt += 2;
		/* save i-1 */
		vm1 = v1;
		/* move to next pair */
	पूर्ण
	/* dump residual pages at end */
	sets = tid_flush_pages(list, &idx, npages - idx, sets);
	/* by design cannot be odd sets */
	WARN_ON(sets & 1);
	वापस sets;
पूर्ण

/*
 * Find pages क्रम one segment of a sge array represented by @ss. The function
 * करोes not check the sge, the sge must have been checked क्रम alignment with a
 * prior call to hfi1_kern_trdma_ok. Other sge checking is करोne as part of
 * rvt_lkey_ok and rvt_rkey_ok. Also, the function only modअगरies the local sge
 * copy मुख्यtained in @ss->sge, the original sge is not modअगरied.
 *
 * Unlike IB RDMA WRITE, we can't decrement ss->num_sge here because we are not
 * releasing the MR reference count at the same समय. Otherwise, we'll "leak"
 * references to the MR. This dअगरference requires that we keep track of progress
 * पूर्णांकo the sg_list. This is करोne by the cur_seg cursor in the tid_rdma_request
 * काष्ठाure.
 */
अटल u32 kern_find_pages(काष्ठा tid_rdma_flow *flow,
			   काष्ठा page **pages,
			   काष्ठा rvt_sge_state *ss, bool *last)
अणु
	काष्ठा tid_rdma_request *req = flow->req;
	काष्ठा rvt_sge *sge = &ss->sge;
	u32 length = flow->req->seg_len;
	u32 len = PAGE_SIZE;
	u32 i = 0;

	जबतक (length && req->isge < ss->num_sge) अणु
		pages[i++] = virt_to_page(sge->vaddr);

		sge->vaddr += len;
		sge->length -= len;
		sge->sge_length -= len;
		अगर (!sge->sge_length) अणु
			अगर (++req->isge < ss->num_sge)
				*sge = ss->sg_list[req->isge - 1];
		पूर्ण अन्यथा अगर (sge->length == 0 && sge->mr->lkey) अणु
			अगर (++sge->n >= RVT_SEGSZ) अणु
				++sge->m;
				sge->n = 0;
			पूर्ण
			sge->vaddr = sge->mr->map[sge->m]->segs[sge->n].vaddr;
			sge->length = sge->mr->map[sge->m]->segs[sge->n].length;
		पूर्ण
		length -= len;
	पूर्ण

	flow->length = flow->req->seg_len - length;
	*last = req->isge == ss->num_sge ? false : true;
	वापस i;
पूर्ण

अटल व्योम dma_unmap_flow(काष्ठा tid_rdma_flow *flow)
अणु
	काष्ठा hfi1_devdata *dd;
	पूर्णांक i;
	काष्ठा tid_rdma_pageset *pset;

	dd = flow->req->rcd->dd;
	क्रम (i = 0, pset = &flow->pagesets[0]; i < flow->npagesets;
			i++, pset++) अणु
		अगर (pset->count && pset->addr) अणु
			dma_unmap_page(&dd->pcidev->dev,
				       pset->addr,
				       PAGE_SIZE * pset->count,
				       DMA_FROM_DEVICE);
			pset->mapped = 0;
		पूर्ण
	पूर्ण
पूर्ण

अटल पूर्णांक dma_map_flow(काष्ठा tid_rdma_flow *flow, काष्ठा page **pages)
अणु
	पूर्णांक i;
	काष्ठा hfi1_devdata *dd = flow->req->rcd->dd;
	काष्ठा tid_rdma_pageset *pset;

	क्रम (i = 0, pset = &flow->pagesets[0]; i < flow->npagesets;
			i++, pset++) अणु
		अगर (pset->count) अणु
			pset->addr = dma_map_page(&dd->pcidev->dev,
						  pages[pset->idx],
						  0,
						  PAGE_SIZE * pset->count,
						  DMA_FROM_DEVICE);

			अगर (dma_mapping_error(&dd->pcidev->dev, pset->addr)) अणु
				dma_unmap_flow(flow);
				वापस -ENOMEM;
			पूर्ण
			pset->mapped = 1;
		पूर्ण
	पूर्ण
	वापस 0;
पूर्ण

अटल अंतरभूत bool dma_mapped(काष्ठा tid_rdma_flow *flow)
अणु
	वापस !!flow->pagesets[0].mapped;
पूर्ण

/*
 * Get pages poपूर्णांकers and identअगरy contiguous physical memory chunks क्रम a
 * segment. All segments are of length flow->req->seg_len.
 */
अटल पूर्णांक kern_get_phys_blocks(काष्ठा tid_rdma_flow *flow,
				काष्ठा page **pages,
				काष्ठा rvt_sge_state *ss, bool *last)
अणु
	u8 npages;

	/* Reuse previously computed pagesets, अगर any */
	अगर (flow->npagesets) अणु
		trace_hfi1_tid_flow_alloc(flow->req->qp, flow->req->setup_head,
					  flow);
		अगर (!dma_mapped(flow))
			वापस dma_map_flow(flow, pages);
		वापस 0;
	पूर्ण

	npages = kern_find_pages(flow, pages, ss, last);

	अगर (flow->req->qp->pmtu == क्रमागत_to_mtu(OPA_MTU_4096))
		flow->npagesets =
			tid_rdma_find_phys_blocks_4k(flow, pages, npages,
						     flow->pagesets);
	अन्यथा
		flow->npagesets =
			tid_rdma_find_phys_blocks_8k(flow, pages, npages,
						     flow->pagesets);

	वापस dma_map_flow(flow, pages);
पूर्ण

अटल अंतरभूत व्योम kern_add_tid_node(काष्ठा tid_rdma_flow *flow,
				     काष्ठा hfi1_ctxtdata *rcd, अक्षर *s,
				     काष्ठा tid_group *grp, u8 cnt)
अणु
	काष्ठा kern_tid_node *node = &flow->tnode[flow->tnode_cnt++];

	WARN_ON_ONCE(flow->tnode_cnt >=
		     (TID_RDMA_MAX_SEGMENT_SIZE >> PAGE_SHIFT));
	अगर (WARN_ON_ONCE(cnt & 1))
		dd_dev_err(rcd->dd,
			   "unexpected odd allocation cnt %u map 0x%x used %u",
			   cnt, grp->map, grp->used);

	node->grp = grp;
	node->map = grp->map;
	node->cnt = cnt;
	trace_hfi1_tid_node_add(flow->req->qp, s, flow->tnode_cnt - 1,
				grp->base, grp->map, grp->used, cnt);
पूर्ण

/*
 * Try to allocate pageset_count TID's from TID groups क्रम a context
 *
 * This function allocates TID's without moving groups between lists or
 * modअगरying grp->map. This is करोne as follows, being cogizant of the lists
 * between which the TID groups will move:
 * 1. First allocate complete groups of 8 TID's since this is more efficient,
 *    these groups will move from group->full without affecting used
 * 2. If more TID's are needed allocate from used (will move from used->full or
 *    stay in used)
 * 3. If we still करोn't have the required number of TID's go back and look again
 *    at a complete group (will move from group->used)
 */
अटल पूर्णांक kern_alloc_tids(काष्ठा tid_rdma_flow *flow)
अणु
	काष्ठा hfi1_ctxtdata *rcd = flow->req->rcd;
	काष्ठा hfi1_devdata *dd = rcd->dd;
	u32 ngroups, pageidx = 0;
	काष्ठा tid_group *group = शून्य, *used;
	u8 use;

	flow->tnode_cnt = 0;
	ngroups = flow->npagesets / dd->rcv_entries.group_size;
	अगर (!ngroups)
		जाओ used_list;

	/* First look at complete groups */
	list_क्रम_each_entry(group,  &rcd->tid_group_list.list, list) अणु
		kern_add_tid_node(flow, rcd, "complete groups", group,
				  group->size);

		pageidx += group->size;
		अगर (!--ngroups)
			अवरोध;
	पूर्ण

	अगर (pageidx >= flow->npagesets)
		जाओ ok;

used_list:
	/* Now look at partially used groups */
	list_क्रम_each_entry(used, &rcd->tid_used_list.list, list) अणु
		use = min_t(u32, flow->npagesets - pageidx,
			    used->size - used->used);
		kern_add_tid_node(flow, rcd, "used groups", used, use);

		pageidx += use;
		अगर (pageidx >= flow->npagesets)
			जाओ ok;
	पूर्ण

	/*
	 * Look again at a complete group, continuing from where we left.
	 * However, अगर we are at the head, we have reached the end of the
	 * complete groups list from the first loop above
	 */
	अगर (group && &group->list == &rcd->tid_group_list.list)
		जाओ bail_eagain;
	group = list_prepare_entry(group, &rcd->tid_group_list.list,
				   list);
	अगर (list_is_last(&group->list, &rcd->tid_group_list.list))
		जाओ bail_eagain;
	group = list_next_entry(group, list);
	use = min_t(u32, flow->npagesets - pageidx, group->size);
	kern_add_tid_node(flow, rcd, "complete continue", group, use);
	pageidx += use;
	अगर (pageidx >= flow->npagesets)
		जाओ ok;
bail_eagain:
	trace_hfi1_msg_alloc_tids(flow->req->qp, " insufficient tids: needed ",
				  (u64)flow->npagesets);
	वापस -EAGAIN;
ok:
	वापस 0;
पूर्ण

अटल व्योम kern_program_rcv_group(काष्ठा tid_rdma_flow *flow, पूर्णांक grp_num,
				   u32 *pset_idx)
अणु
	काष्ठा hfi1_ctxtdata *rcd = flow->req->rcd;
	काष्ठा hfi1_devdata *dd = rcd->dd;
	काष्ठा kern_tid_node *node = &flow->tnode[grp_num];
	काष्ठा tid_group *grp = node->grp;
	काष्ठा tid_rdma_pageset *pset;
	u32 pmtu_pg = flow->req->qp->pmtu >> PAGE_SHIFT;
	u32 rcventry, npages = 0, pair = 0, tidctrl;
	u8 i, cnt = 0;

	क्रम (i = 0; i < grp->size; i++) अणु
		rcventry = grp->base + i;

		अगर (node->map & BIT(i) || cnt >= node->cnt) अणु
			rcv_array_wc_fill(dd, rcventry);
			जारी;
		पूर्ण
		pset = &flow->pagesets[(*pset_idx)++];
		अगर (pset->count) अणु
			hfi1_put_tid(dd, rcventry, PT_EXPECTED,
				     pset->addr, trdma_pset_order(pset));
		पूर्ण अन्यथा अणु
			hfi1_put_tid(dd, rcventry, PT_INVALID, 0, 0);
		पूर्ण
		npages += pset->count;

		rcventry -= rcd->expected_base;
		tidctrl = pair ? 0x3 : rcventry & 0x1 ? 0x2 : 0x1;
		/*
		 * A single TID entry will be used to use a rcvarr pair (with
		 * tidctrl 0x3), अगर ALL these are true (a) the bit pos is even
		 * (b) the group map shows current and the next bits as मुक्त
		 * indicating two consecutive rcvarry entries are available (c)
		 * we actually need 2 more entries
		 */
		pair = !(i & 0x1) && !((node->map >> i) & 0x3) &&
			node->cnt >= cnt + 2;
		अगर (!pair) अणु
			अगर (!pset->count)
				tidctrl = 0x1;
			flow->tid_entry[flow->tidcnt++] =
				EXP_TID_SET(IDX, rcventry >> 1) |
				EXP_TID_SET(CTRL, tidctrl) |
				EXP_TID_SET(LEN, npages);
			trace_hfi1_tid_entry_alloc(/* entry */
			   flow->req->qp, flow->tidcnt - 1,
			   flow->tid_entry[flow->tidcnt - 1]);

			/* Efficient DIV_ROUND_UP(npages, pmtu_pg) */
			flow->npkts += (npages + pmtu_pg - 1) >> ilog2(pmtu_pg);
			npages = 0;
		पूर्ण

		अगर (grp->used == grp->size - 1)
			tid_group_move(grp, &rcd->tid_used_list,
				       &rcd->tid_full_list);
		अन्यथा अगर (!grp->used)
			tid_group_move(grp, &rcd->tid_group_list,
				       &rcd->tid_used_list);

		grp->used++;
		grp->map |= BIT(i);
		cnt++;
	पूर्ण
पूर्ण

अटल व्योम kern_unprogram_rcv_group(काष्ठा tid_rdma_flow *flow, पूर्णांक grp_num)
अणु
	काष्ठा hfi1_ctxtdata *rcd = flow->req->rcd;
	काष्ठा hfi1_devdata *dd = rcd->dd;
	काष्ठा kern_tid_node *node = &flow->tnode[grp_num];
	काष्ठा tid_group *grp = node->grp;
	u32 rcventry;
	u8 i, cnt = 0;

	क्रम (i = 0; i < grp->size; i++) अणु
		rcventry = grp->base + i;

		अगर (node->map & BIT(i) || cnt >= node->cnt) अणु
			rcv_array_wc_fill(dd, rcventry);
			जारी;
		पूर्ण

		hfi1_put_tid(dd, rcventry, PT_INVALID, 0, 0);

		grp->used--;
		grp->map &= ~BIT(i);
		cnt++;

		अगर (grp->used == grp->size - 1)
			tid_group_move(grp, &rcd->tid_full_list,
				       &rcd->tid_used_list);
		अन्यथा अगर (!grp->used)
			tid_group_move(grp, &rcd->tid_used_list,
				       &rcd->tid_group_list);
	पूर्ण
	अगर (WARN_ON_ONCE(cnt & 1)) अणु
		काष्ठा hfi1_ctxtdata *rcd = flow->req->rcd;
		काष्ठा hfi1_devdata *dd = rcd->dd;

		dd_dev_err(dd, "unexpected odd free cnt %u map 0x%x used %u",
			   cnt, grp->map, grp->used);
	पूर्ण
पूर्ण

अटल व्योम kern_program_rcvarray(काष्ठा tid_rdma_flow *flow)
अणु
	u32 pset_idx = 0;
	पूर्णांक i;

	flow->npkts = 0;
	flow->tidcnt = 0;
	क्रम (i = 0; i < flow->tnode_cnt; i++)
		kern_program_rcv_group(flow, i, &pset_idx);
	trace_hfi1_tid_flow_alloc(flow->req->qp, flow->req->setup_head, flow);
पूर्ण

/**
 * hfi1_kern_exp_rcv_setup() - setup TID's and flow क्रम one segment of a
 * TID RDMA request
 *
 * @req: TID RDMA request क्रम which the segment/flow is being set up
 * @ss: sge state, मुख्यtains state across successive segments of a sge
 * @last: set to true after the last sge segment has been processed
 *
 * This function
 * (1) finds a मुक्त flow entry in the flow circular buffer
 * (2) finds pages and continuous physical chunks स्थिरituing one segment
 *     of an sge
 * (3) allocates TID group entries क्रम those chunks
 * (4) programs rcvarray entries in the hardware corresponding to those
 *     TID's
 * (5) computes a tidarray with क्रमmatted TID entries which can be sent
 *     to the sender
 * (6) Reserves and programs HW flows.
 * (7) It also manages queing the QP when TID/flow resources are not
 *     available.
 *
 * @req poपूर्णांकs to काष्ठा tid_rdma_request of which the segments are a part. The
 * function uses qp, rcd and seg_len members of @req. In the असलence of errors,
 * req->flow_idx is the index of the flow which has been prepared in this
 * invocation of function call. With flow = &req->flows[req->flow_idx],
 * flow->tid_entry contains the TID array which the sender can use क्रम TID RDMA
 * sends and flow->npkts contains number of packets required to send the
 * segment.
 *
 * hfi1_check_sge_align should be called prior to calling this function and अगर
 * it संकेतs error TID RDMA cannot be used क्रम this sge and this function
 * should not be called.
 *
 * For the queuing, caller must hold the flow->req->qp s_lock from the send
 * engine and the function will procure the exp_lock.
 *
 * Return:
 * The function वापसs -EAGAIN अगर sufficient number of TID/flow resources to
 * map the segment could not be allocated. In this हाल the function should be
 * called again with previous arguments to retry the TID allocation. There are
 * no other error वापसs. The function वापसs 0 on success.
 */
पूर्णांक hfi1_kern_exp_rcv_setup(काष्ठा tid_rdma_request *req,
			    काष्ठा rvt_sge_state *ss, bool *last)
	__must_hold(&req->qp->s_lock)
अणु
	काष्ठा tid_rdma_flow *flow = &req->flows[req->setup_head];
	काष्ठा hfi1_ctxtdata *rcd = req->rcd;
	काष्ठा hfi1_qp_priv *qpriv = req->qp->priv;
	अचिन्हित दीर्घ flags;
	काष्ठा rvt_qp *fqp;
	u16 clear_tail = req->clear_tail;

	lockdep_निश्चित_held(&req->qp->s_lock);
	/*
	 * We वापस error अगर either (a) we करोn't have space in the flow
	 * circular buffer, or (b) we alपढ़ोy have max entries in the buffer.
	 * Max entries depend on the type of request we are processing and the
	 * negotiated TID RDMA parameters.
	 */
	अगर (!CIRC_SPACE(req->setup_head, clear_tail, MAX_FLOWS) ||
	    CIRC_CNT(req->setup_head, clear_tail, MAX_FLOWS) >=
	    req->n_flows)
		वापस -EINVAL;

	/*
	 * Get pages, identअगरy contiguous physical memory chunks क्रम the segment
	 * If we can not determine a DMA address mapping we will treat it just
	 * like अगर we ran out of space above.
	 */
	अगर (kern_get_phys_blocks(flow, qpriv->pages, ss, last)) अणु
		hfi1_रुको_kmem(flow->req->qp);
		वापस -ENOMEM;
	पूर्ण

	spin_lock_irqsave(&rcd->exp_lock, flags);
	अगर (kernel_tid_रुकोers(rcd, &rcd->rarr_queue, flow->req->qp))
		जाओ queue;

	/*
	 * At this poपूर्णांक we know the number of pagesets and hence the number of
	 * TID's to map the segment. Allocate the TID's from the TID groups. If
	 * we cannot allocate the required number we निकास and try again later
	 */
	अगर (kern_alloc_tids(flow))
		जाओ queue;
	/*
	 * Finally program the TID entries with the pagesets, compute the
	 * tidarray and enable the HW flow
	 */
	kern_program_rcvarray(flow);

	/*
	 * Setup the flow state with relevant inक्रमmation.
	 * This inक्रमmation is used क्रम tracking the sequence of data packets
	 * क्रम the segment.
	 * The flow is setup here as this is the most accurate समय and place
	 * to करो so. Doing at a later समय runs the risk of the flow data in
	 * qpriv getting out of sync.
	 */
	स_रखो(&flow->flow_state, 0x0, माप(flow->flow_state));
	flow->idx = qpriv->flow_state.index;
	flow->flow_state.generation = qpriv->flow_state.generation;
	flow->flow_state.spsn = qpriv->flow_state.psn;
	flow->flow_state.lpsn = flow->flow_state.spsn + flow->npkts - 1;
	flow->flow_state.r_next_psn =
		full_flow_psn(flow, flow->flow_state.spsn);
	qpriv->flow_state.psn += flow->npkts;

	dequeue_tid_रुकोer(rcd, &rcd->rarr_queue, flow->req->qp);
	/* get head beक्रमe dropping lock */
	fqp = first_qp(rcd, &rcd->rarr_queue);
	spin_unlock_irqrestore(&rcd->exp_lock, flags);
	tid_rdma_schedule_tid_wakeup(fqp);

	req->setup_head = (req->setup_head + 1) & (MAX_FLOWS - 1);
	वापस 0;
queue:
	queue_qp_क्रम_tid_रुको(rcd, &rcd->rarr_queue, flow->req->qp);
	spin_unlock_irqrestore(&rcd->exp_lock, flags);
	वापस -EAGAIN;
पूर्ण

अटल व्योम hfi1_tid_rdma_reset_flow(काष्ठा tid_rdma_flow *flow)
अणु
	flow->npagesets = 0;
पूर्ण

/*
 * This function is called after one segment has been successfully sent to
 * release the flow and TID HW/SW resources क्रम that segment. The segments क्रम a
 * TID RDMA request are setup and cleared in FIFO order which is managed using a
 * circular buffer.
 */
पूर्णांक hfi1_kern_exp_rcv_clear(काष्ठा tid_rdma_request *req)
	__must_hold(&req->qp->s_lock)
अणु
	काष्ठा tid_rdma_flow *flow = &req->flows[req->clear_tail];
	काष्ठा hfi1_ctxtdata *rcd = req->rcd;
	अचिन्हित दीर्घ flags;
	पूर्णांक i;
	काष्ठा rvt_qp *fqp;

	lockdep_निश्चित_held(&req->qp->s_lock);
	/* Exit अगर we have nothing in the flow circular buffer */
	अगर (!CIRC_CNT(req->setup_head, req->clear_tail, MAX_FLOWS))
		वापस -EINVAL;

	spin_lock_irqsave(&rcd->exp_lock, flags);

	क्रम (i = 0; i < flow->tnode_cnt; i++)
		kern_unprogram_rcv_group(flow, i);
	/* To prevent द्विगुन unprogramming */
	flow->tnode_cnt = 0;
	/* get head beक्रमe dropping lock */
	fqp = first_qp(rcd, &rcd->rarr_queue);
	spin_unlock_irqrestore(&rcd->exp_lock, flags);

	dma_unmap_flow(flow);

	hfi1_tid_rdma_reset_flow(flow);
	req->clear_tail = (req->clear_tail + 1) & (MAX_FLOWS - 1);

	अगर (fqp == req->qp) अणु
		__trigger_tid_रुकोer(fqp);
		rvt_put_qp(fqp);
	पूर्ण अन्यथा अणु
		tid_rdma_schedule_tid_wakeup(fqp);
	पूर्ण

	वापस 0;
पूर्ण

/*
 * This function is called to release all the tid entries क्रम
 * a request.
 */
व्योम hfi1_kern_exp_rcv_clear_all(काष्ठा tid_rdma_request *req)
	__must_hold(&req->qp->s_lock)
अणु
	/* Use memory barrier क्रम proper ordering */
	जबतक (CIRC_CNT(req->setup_head, req->clear_tail, MAX_FLOWS)) अणु
		अगर (hfi1_kern_exp_rcv_clear(req))
			अवरोध;
	पूर्ण
पूर्ण

/**
 * hfi1_kern_exp_rcv_मुक्त_flows - मुक्त priviously allocated flow inक्रमmation
 * @req: the tid rdma request to be cleaned
 */
अटल व्योम hfi1_kern_exp_rcv_मुक्त_flows(काष्ठा tid_rdma_request *req)
अणु
	kमुक्त(req->flows);
	req->flows = शून्य;
पूर्ण

/**
 * __trdma_clean_swqe - clean up क्रम large sized QPs
 * @qp: the queue patch
 * @wqe: the send wqe
 */
व्योम __trdma_clean_swqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe)
अणु
	काष्ठा hfi1_swqe_priv *p = wqe->priv;

	hfi1_kern_exp_rcv_मुक्त_flows(&p->tid_req);
पूर्ण

/*
 * This can be called at QP create समय or in the data path.
 */
अटल पूर्णांक hfi1_kern_exp_rcv_alloc_flows(काष्ठा tid_rdma_request *req,
					 gfp_t gfp)
अणु
	काष्ठा tid_rdma_flow *flows;
	पूर्णांक i;

	अगर (likely(req->flows))
		वापस 0;
	flows = kदो_स्मृति_node(MAX_FLOWS * माप(*flows), gfp,
			     req->rcd->numa_id);
	अगर (!flows)
		वापस -ENOMEM;
	/* mini init */
	क्रम (i = 0; i < MAX_FLOWS; i++) अणु
		flows[i].req = req;
		flows[i].npagesets = 0;
		flows[i].pagesets[0].mapped =  0;
		flows[i].resync_npkts = 0;
	पूर्ण
	req->flows = flows;
	वापस 0;
पूर्ण

अटल व्योम hfi1_init_trdma_req(काष्ठा rvt_qp *qp,
				काष्ठा tid_rdma_request *req)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;

	/*
	 * Initialize various TID RDMA request variables.
	 * These variables are "static", which is why they
	 * can be pre-initialized here beक्रमe the WRs has
	 * even been submitted.
	 * However, non-शून्य values क्रम these variables करो not
	 * imply that this WQE has been enabled क्रम TID RDMA.
	 * Drivers should check the WQE's opcode to determine
	 * अगर a request is a TID RDMA one or not.
	 */
	req->qp = qp;
	req->rcd = qpriv->rcd;
पूर्ण

u64 hfi1_access_sw_tid_रुको(स्थिर काष्ठा cntr_entry *entry,
			    व्योम *context, पूर्णांक vl, पूर्णांक mode, u64 data)
अणु
	काष्ठा hfi1_devdata *dd = context;

	वापस dd->verbs_dev.n_tidरुको;
पूर्ण

अटल काष्ठा tid_rdma_flow *find_flow_ib(काष्ठा tid_rdma_request *req,
					  u32 psn, u16 *fidx)
अणु
	u16 head, tail;
	काष्ठा tid_rdma_flow *flow;

	head = req->setup_head;
	tail = req->clear_tail;
	क्रम ( ; CIRC_CNT(head, tail, MAX_FLOWS);
	     tail = CIRC_NEXT(tail, MAX_FLOWS)) अणु
		flow = &req->flows[tail];
		अगर (cmp_psn(psn, flow->flow_state.ib_spsn) >= 0 &&
		    cmp_psn(psn, flow->flow_state.ib_lpsn) <= 0) अणु
			अगर (fidx)
				*fidx = tail;
			वापस flow;
		पूर्ण
	पूर्ण
	वापस शून्य;
पूर्ण

/* TID RDMA READ functions */
u32 hfi1_build_tid_rdma_पढ़ो_packet(काष्ठा rvt_swqe *wqe,
				    काष्ठा ib_other_headers *ohdr, u32 *bth1,
				    u32 *bth2, u32 *len)
अणु
	काष्ठा tid_rdma_request *req = wqe_to_tid_req(wqe);
	काष्ठा tid_rdma_flow *flow = &req->flows[req->flow_idx];
	काष्ठा rvt_qp *qp = req->qp;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा hfi1_swqe_priv *wpriv = wqe->priv;
	काष्ठा tid_rdma_पढ़ो_req *rreq = &ohdr->u.tid_rdma.r_req;
	काष्ठा tid_rdma_params *remote;
	u32 req_len = 0;
	व्योम *req_addr = शून्य;

	/* This is the IB psn used to send the request */
	*bth2 = mask_psn(flow->flow_state.ib_spsn + flow->pkt);
	trace_hfi1_tid_flow_build_पढ़ो_pkt(qp, req->flow_idx, flow);

	/* TID Entries क्रम TID RDMA READ payload */
	req_addr = &flow->tid_entry[flow->tid_idx];
	req_len = माप(*flow->tid_entry) *
			(flow->tidcnt - flow->tid_idx);

	स_रखो(&ohdr->u.tid_rdma.r_req, 0, माप(ohdr->u.tid_rdma.r_req));
	wpriv->ss.sge.vaddr = req_addr;
	wpriv->ss.sge.sge_length = req_len;
	wpriv->ss.sge.length = wpriv->ss.sge.sge_length;
	/*
	 * We can safely zero these out. Since the first SGE covers the
	 * entire packet, nothing अन्यथा should even look at the MR.
	 */
	wpriv->ss.sge.mr = शून्य;
	wpriv->ss.sge.m = 0;
	wpriv->ss.sge.n = 0;

	wpriv->ss.sg_list = शून्य;
	wpriv->ss.total_len = wpriv->ss.sge.sge_length;
	wpriv->ss.num_sge = 1;

	/* Conकाष्ठा the TID RDMA READ REQ packet header */
	rcu_पढ़ो_lock();
	remote = rcu_dereference(qpriv->tid_rdma.remote);

	KDETH_RESET(rreq->kdeth0, KVER, 0x1);
	KDETH_RESET(rreq->kdeth1, JKEY, remote->jkey);
	rreq->reth.vaddr = cpu_to_be64(wqe->rdma_wr.remote_addr +
			   req->cur_seg * req->seg_len + flow->sent);
	rreq->reth.rkey = cpu_to_be32(wqe->rdma_wr.rkey);
	rreq->reth.length = cpu_to_be32(*len);
	rreq->tid_flow_psn =
		cpu_to_be32((flow->flow_state.generation <<
			     HFI1_KDETH_BTH_SEQ_SHIFT) |
			    ((flow->flow_state.spsn + flow->pkt) &
			     HFI1_KDETH_BTH_SEQ_MASK));
	rreq->tid_flow_qp =
		cpu_to_be32(qpriv->tid_rdma.local.qp |
			    ((flow->idx & TID_RDMA_DESTQP_FLOW_MASK) <<
			     TID_RDMA_DESTQP_FLOW_SHIFT) |
			    qpriv->rcd->ctxt);
	rreq->verbs_qp = cpu_to_be32(qp->remote_qpn);
	*bth1 &= ~RVT_QPN_MASK;
	*bth1 |= remote->qp;
	*bth2 |= IB_BTH_REQ_ACK;
	rcu_पढ़ो_unlock();

	/* We are करोne with this segment */
	flow->sent += *len;
	req->cur_seg++;
	qp->s_state = TID_OP(READ_REQ);
	req->ack_pending++;
	req->flow_idx = (req->flow_idx + 1) & (MAX_FLOWS - 1);
	qpriv->pending_tid_r_segs++;
	qp->s_num_rd_atomic++;

	/* Set the TID RDMA READ request payload size */
	*len = req_len;

	वापस माप(ohdr->u.tid_rdma.r_req) / माप(u32);
पूर्ण

/*
 * @len: contains the data length to पढ़ो upon entry and the पढ़ो request
 *       payload length upon निकास.
 */
u32 hfi1_build_tid_rdma_पढ़ो_req(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
				 काष्ठा ib_other_headers *ohdr, u32 *bth1,
				 u32 *bth2, u32 *len)
	__must_hold(&qp->s_lock)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_rdma_request *req = wqe_to_tid_req(wqe);
	काष्ठा tid_rdma_flow *flow = शून्य;
	u32 hdwords = 0;
	bool last;
	bool retry = true;
	u32 npkts = rvt_भाग_round_up_mtu(qp, *len);

	trace_hfi1_tid_req_build_पढ़ो_req(qp, 0, wqe->wr.opcode, wqe->psn,
					  wqe->lpsn, req);
	/*
	 * Check sync conditions. Make sure that there are no pending
	 * segments beक्रमe मुक्तing the flow.
	 */
sync_check:
	अगर (req->state == TID_REQUEST_SYNC) अणु
		अगर (qpriv->pending_tid_r_segs)
			जाओ करोne;

		hfi1_kern_clear_hw_flow(req->rcd, qp);
		qpriv->s_flags &= ~HFI1_R_TID_SW_PSN;
		req->state = TID_REQUEST_ACTIVE;
	पूर्ण

	/*
	 * If the request क्रम this segment is resent, the tid resources should
	 * have been allocated beक्रमe. In this हाल, req->flow_idx should
	 * fall behind req->setup_head.
	 */
	अगर (req->flow_idx == req->setup_head) अणु
		retry = false;
		अगर (req->state == TID_REQUEST_RESEND) अणु
			/*
			 * This is the first new segment क्रम a request whose
			 * earlier segments have been re-sent. We need to
			 * set up the sge poपूर्णांकer correctly.
			 */
			restart_sge(&qp->s_sge, wqe, req->s_next_psn,
				    qp->pmtu);
			req->isge = 0;
			req->state = TID_REQUEST_ACTIVE;
		पूर्ण

		/*
		 * Check sync. The last PSN of each generation is reserved क्रम
		 * RESYNC.
		 */
		अगर ((qpriv->flow_state.psn + npkts) > MAX_TID_FLOW_PSN - 1) अणु
			req->state = TID_REQUEST_SYNC;
			जाओ sync_check;
		पूर्ण

		/* Allocate the flow अगर not yet */
		अगर (hfi1_kern_setup_hw_flow(qpriv->rcd, qp))
			जाओ करोne;

		/*
		 * The following call will advance req->setup_head after
		 * allocating the tid entries.
		 */
		अगर (hfi1_kern_exp_rcv_setup(req, &qp->s_sge, &last)) अणु
			req->state = TID_REQUEST_QUEUED;

			/*
			 * We करोn't have resources क्रम this segment. The QP has
			 * alपढ़ोy been queued.
			 */
			जाओ करोne;
		पूर्ण
	पूर्ण

	/* req->flow_idx should only be one slot behind req->setup_head */
	flow = &req->flows[req->flow_idx];
	flow->pkt = 0;
	flow->tid_idx = 0;
	flow->sent = 0;
	अगर (!retry) अणु
		/* Set the first and last IB PSN क्रम the flow in use.*/
		flow->flow_state.ib_spsn = req->s_next_psn;
		flow->flow_state.ib_lpsn =
			flow->flow_state.ib_spsn + flow->npkts - 1;
	पूर्ण

	/* Calculate the next segment start psn.*/
	req->s_next_psn += flow->npkts;

	/* Build the packet header */
	hdwords = hfi1_build_tid_rdma_पढ़ो_packet(wqe, ohdr, bth1, bth2, len);
करोne:
	वापस hdwords;
पूर्ण

/*
 * Validate and accept the TID RDMA READ request parameters.
 * Return 0 अगर the request is accepted successfully;
 * Return 1 otherwise.
 */
अटल पूर्णांक tid_rdma_rcv_पढ़ो_request(काष्ठा rvt_qp *qp,
				     काष्ठा rvt_ack_entry *e,
				     काष्ठा hfi1_packet *packet,
				     काष्ठा ib_other_headers *ohdr,
				     u32 bth0, u32 psn, u64 vaddr, u32 len)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;
	u32 flow_psn, i, tidlen = 0, pktlen, tlen;

	req = ack_to_tid_req(e);

	/* Validate the payload first */
	flow = &req->flows[req->setup_head];

	/* payload length = packet length - (header length + ICRC length) */
	pktlen = packet->tlen - (packet->hlen + 4);
	अगर (pktlen > माप(flow->tid_entry))
		वापस 1;
	स_नकल(flow->tid_entry, packet->ebuf, pktlen);
	flow->tidcnt = pktlen / माप(*flow->tid_entry);

	/*
	 * Walk the TID_ENTRY list to make sure we have enough space क्रम a
	 * complete segment. Also calculate the number of required packets.
	 */
	flow->npkts = rvt_भाग_round_up_mtu(qp, len);
	क्रम (i = 0; i < flow->tidcnt; i++) अणु
		trace_hfi1_tid_entry_rcv_पढ़ो_req(qp, i,
						  flow->tid_entry[i]);
		tlen = EXP_TID_GET(flow->tid_entry[i], LEN);
		अगर (!tlen)
			वापस 1;

		/*
		 * For tid pair (tidctr == 3), the buffer size of the pair
		 * should be the sum of the buffer size described by each
		 * tid entry. However, only the first entry needs to be
		 * specअगरied in the request (see WFR HAS Section 8.5.7.1).
		 */
		tidlen += tlen;
	पूर्ण
	अगर (tidlen * PAGE_SIZE < len)
		वापस 1;

	/* Empty the flow array */
	req->clear_tail = req->setup_head;
	flow->pkt = 0;
	flow->tid_idx = 0;
	flow->tid_offset = 0;
	flow->sent = 0;
	flow->tid_qpn = be32_to_cpu(ohdr->u.tid_rdma.r_req.tid_flow_qp);
	flow->idx = (flow->tid_qpn >> TID_RDMA_DESTQP_FLOW_SHIFT) &
		    TID_RDMA_DESTQP_FLOW_MASK;
	flow_psn = mask_psn(be32_to_cpu(ohdr->u.tid_rdma.r_req.tid_flow_psn));
	flow->flow_state.generation = flow_psn >> HFI1_KDETH_BTH_SEQ_SHIFT;
	flow->flow_state.spsn = flow_psn & HFI1_KDETH_BTH_SEQ_MASK;
	flow->length = len;

	flow->flow_state.lpsn = flow->flow_state.spsn +
		flow->npkts - 1;
	flow->flow_state.ib_spsn = psn;
	flow->flow_state.ib_lpsn = flow->flow_state.ib_spsn + flow->npkts - 1;

	trace_hfi1_tid_flow_rcv_पढ़ो_req(qp, req->setup_head, flow);
	/* Set the initial flow index to the current flow. */
	req->flow_idx = req->setup_head;

	/* advance circular buffer head */
	req->setup_head = (req->setup_head + 1) & (MAX_FLOWS - 1);

	/*
	 * Compute last PSN क्रम request.
	 */
	e->opcode = (bth0 >> 24) & 0xff;
	e->psn = psn;
	e->lpsn = psn + flow->npkts - 1;
	e->sent = 0;

	req->n_flows = qpriv->tid_rdma.local.max_पढ़ो;
	req->state = TID_REQUEST_ACTIVE;
	req->cur_seg = 0;
	req->comp_seg = 0;
	req->ack_seg = 0;
	req->isge = 0;
	req->seg_len = qpriv->tid_rdma.local.max_len;
	req->total_len = len;
	req->total_segs = 1;
	req->r_flow_psn = e->psn;

	trace_hfi1_tid_req_rcv_पढ़ो_req(qp, 0, e->opcode, e->psn, e->lpsn,
					req);
	वापस 0;
पूर्ण

अटल पूर्णांक tid_rdma_rcv_error(काष्ठा hfi1_packet *packet,
			      काष्ठा ib_other_headers *ohdr,
			      काष्ठा rvt_qp *qp, u32 psn, पूर्णांक dअगरf)
अणु
	काष्ठा hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा hfi1_ctxtdata *rcd = ((काष्ठा hfi1_qp_priv *)qp->priv)->rcd;
	काष्ठा hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा rvt_ack_entry *e;
	काष्ठा tid_rdma_request *req;
	अचिन्हित दीर्घ flags;
	u8 prev;
	bool old_req;

	trace_hfi1_rsp_tid_rcv_error(qp, psn);
	trace_hfi1_tid_rdma_rcv_err(qp, 0, psn, dअगरf);
	अगर (dअगरf > 0) अणु
		/* sequence error */
		अगर (!qp->r_nak_state) अणु
			ibp->rvp.n_rc_seqnak++;
			qp->r_nak_state = IB_NAK_PSN_ERROR;
			qp->r_ack_psn = qp->r_psn;
			rc_defered_ack(rcd, qp);
		पूर्ण
		जाओ करोne;
	पूर्ण

	ibp->rvp.n_rc_dupreq++;

	spin_lock_irqsave(&qp->s_lock, flags);
	e = find_prev_entry(qp, psn, &prev, शून्य, &old_req);
	अगर (!e || (e->opcode != TID_OP(READ_REQ) &&
		   e->opcode != TID_OP(WRITE_REQ)))
		जाओ unlock;

	req = ack_to_tid_req(e);
	req->r_flow_psn = psn;
	trace_hfi1_tid_req_rcv_err(qp, 0, e->opcode, e->psn, e->lpsn, req);
	अगर (e->opcode == TID_OP(READ_REQ)) अणु
		काष्ठा ib_reth *reth;
		u32 len;
		u32 rkey;
		u64 vaddr;
		पूर्णांक ok;
		u32 bth0;

		reth = &ohdr->u.tid_rdma.r_req.reth;
		/*
		 * The requester always restarts from the start of the original
		 * request.
		 */
		len = be32_to_cpu(reth->length);
		अगर (psn != e->psn || len != req->total_len)
			जाओ unlock;

		release_rdma_sge_mr(e);

		rkey = be32_to_cpu(reth->rkey);
		vaddr = get_ib_reth_vaddr(reth);

		qp->r_len = len;
		ok = rvt_rkey_ok(qp, &e->rdma_sge, len, vaddr, rkey,
				 IB_ACCESS_REMOTE_READ);
		अगर (unlikely(!ok))
			जाओ unlock;

		/*
		 * If all the response packets क्रम the current request have
		 * been sent out and this request is complete (old_request
		 * == false) and the TID flow may be unusable (the
		 * req->clear_tail is advanced). However, when an earlier
		 * request is received, this request will not be complete any
		 * more (qp->s_tail_ack_queue is moved back, see below).
		 * Consequently, we need to update the TID flow info everyसमय
		 * a duplicate request is received.
		 */
		bth0 = be32_to_cpu(ohdr->bth[0]);
		अगर (tid_rdma_rcv_पढ़ो_request(qp, e, packet, ohdr, bth0, psn,
					      vaddr, len))
			जाओ unlock;

		/*
		 * True अगर the request is alपढ़ोy scheduled (between
		 * qp->s_tail_ack_queue and qp->r_head_ack_queue);
		 */
		अगर (old_req)
			जाओ unlock;
	पूर्ण अन्यथा अणु
		काष्ठा flow_state *ख_स्थितिe;
		bool schedule = false;
		u8 i;

		अगर (req->state == TID_REQUEST_RESEND) अणु
			req->state = TID_REQUEST_RESEND_ACTIVE;
		पूर्ण अन्यथा अगर (req->state == TID_REQUEST_INIT_RESEND) अणु
			req->state = TID_REQUEST_INIT;
			schedule = true;
		पूर्ण

		/*
		 * True अगर the request is alपढ़ोy scheduled (between
		 * qp->s_tail_ack_queue and qp->r_head_ack_queue).
		 * Also, करोn't change requests, which are at the SYNC
		 * poपूर्णांक and haven't generated any responses yet.
		 * There is nothing to retransmit क्रम them yet.
		 */
		अगर (old_req || req->state == TID_REQUEST_INIT ||
		    (req->state == TID_REQUEST_SYNC && !req->cur_seg)) अणु
			क्रम (i = prev + 1; ; i++) अणु
				अगर (i > rvt_size_atomic(&dev->rdi))
					i = 0;
				अगर (i == qp->r_head_ack_queue)
					अवरोध;
				e = &qp->s_ack_queue[i];
				req = ack_to_tid_req(e);
				अगर (e->opcode == TID_OP(WRITE_REQ) &&
				    req->state == TID_REQUEST_INIT)
					req->state = TID_REQUEST_INIT_RESEND;
			पूर्ण
			/*
			 * If the state of the request has been changed,
			 * the first leg needs to get scheduled in order to
			 * pick up the change. Otherwise, normal response
			 * processing should take care of it.
			 */
			अगर (!schedule)
				जाओ unlock;
		पूर्ण

		/*
		 * If there is no more allocated segment, just schedule the qp
		 * without changing any state.
		 */
		अगर (req->clear_tail == req->setup_head)
			जाओ schedule;
		/*
		 * If this request has sent responses क्रम segments, which have
		 * not received data yet (flow_idx != clear_tail), the flow_idx
		 * poपूर्णांकer needs to be adjusted so the same responses can be
		 * re-sent.
		 */
		अगर (CIRC_CNT(req->flow_idx, req->clear_tail, MAX_FLOWS)) अणु
			ख_स्थितिe = &req->flows[req->clear_tail].flow_state;
			qpriv->pending_tid_w_segs -=
				CIRC_CNT(req->flow_idx, req->clear_tail,
					 MAX_FLOWS);
			req->flow_idx =
				CIRC_ADD(req->clear_tail,
					 delta_psn(psn, ख_स्थितिe->resp_ib_psn),
					 MAX_FLOWS);
			qpriv->pending_tid_w_segs +=
				delta_psn(psn, ख_स्थितिe->resp_ib_psn);
			/*
			 * When flow_idx == setup_head, we've gotten a duplicate
			 * request क्रम a segment, which has not been allocated
			 * yet. In that हाल, करोn't adjust this request.
			 * However, we still want to go through the loop below
			 * to adjust all subsequent requests.
			 */
			अगर (CIRC_CNT(req->setup_head, req->flow_idx,
				     MAX_FLOWS)) अणु
				req->cur_seg = delta_psn(psn, e->psn);
				req->state = TID_REQUEST_RESEND_ACTIVE;
			पूर्ण
		पूर्ण

		क्रम (i = prev + 1; ; i++) अणु
			/*
			 * Look at everything up to and including
			 * s_tail_ack_queue
			 */
			अगर (i > rvt_size_atomic(&dev->rdi))
				i = 0;
			अगर (i == qp->r_head_ack_queue)
				अवरोध;
			e = &qp->s_ack_queue[i];
			req = ack_to_tid_req(e);
			trace_hfi1_tid_req_rcv_err(qp, 0, e->opcode, e->psn,
						   e->lpsn, req);
			अगर (e->opcode != TID_OP(WRITE_REQ) ||
			    req->cur_seg == req->comp_seg ||
			    req->state == TID_REQUEST_INIT ||
			    req->state == TID_REQUEST_INIT_RESEND) अणु
				अगर (req->state == TID_REQUEST_INIT)
					req->state = TID_REQUEST_INIT_RESEND;
				जारी;
			पूर्ण
			qpriv->pending_tid_w_segs -=
				CIRC_CNT(req->flow_idx,
					 req->clear_tail,
					 MAX_FLOWS);
			req->flow_idx = req->clear_tail;
			req->state = TID_REQUEST_RESEND;
			req->cur_seg = req->comp_seg;
		पूर्ण
		qpriv->s_flags &= ~HFI1_R_TID_WAIT_INTERLCK;
	पूर्ण
	/* Re-process old requests.*/
	अगर (qp->s_acked_ack_queue == qp->s_tail_ack_queue)
		qp->s_acked_ack_queue = prev;
	qp->s_tail_ack_queue = prev;
	/*
	 * Since the qp->s_tail_ack_queue is modअगरied, the
	 * qp->s_ack_state must be changed to re-initialize
	 * qp->s_ack_rdma_sge; Otherwise, we will end up in
	 * wrong memory region.
	 */
	qp->s_ack_state = OP(ACKNOWLEDGE);
schedule:
	/*
	 * It's possible to receive a retry psn that is earlier than an RNRNAK
	 * psn. In this हाल, the rnrnak state should be cleared.
	 */
	अगर (qpriv->rnr_nak_state) अणु
		qp->s_nak_state = 0;
		qpriv->rnr_nak_state = TID_RNR_NAK_INIT;
		qp->r_psn = e->lpsn + 1;
		hfi1_tid_ग_लिखो_alloc_resources(qp, true);
	पूर्ण

	qp->r_state = e->opcode;
	qp->r_nak_state = 0;
	qp->s_flags |= RVT_S_RESP_PENDING;
	hfi1_schedule_send(qp);
unlock:
	spin_unlock_irqrestore(&qp->s_lock, flags);
करोne:
	वापस 1;
पूर्ण

व्योम hfi1_rc_rcv_tid_rdma_पढ़ो_req(काष्ठा hfi1_packet *packet)
अणु
	/* HANDLER FOR TID RDMA READ REQUEST packet (Responder side)*/

	/*
	 * 1. Verअगरy TID RDMA READ REQ as per IB_OPCODE_RC_RDMA_READ
	 *    (see hfi1_rc_rcv())
	 * 2. Put TID RDMA READ REQ पूर्णांकo the response queueu (s_ack_queue)
	 *     - Setup काष्ठा tid_rdma_req with request info
	 *     - Initialize काष्ठा tid_rdma_flow info;
	 *     - Copy TID entries;
	 * 3. Set the qp->s_ack_state.
	 * 4. Set RVT_S_RESP_PENDING in s_flags.
	 * 5. Kick the send engine (hfi1_schedule_send())
	 */
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	काष्ठा rvt_ack_entry *e;
	अचिन्हित दीर्घ flags;
	काष्ठा ib_reth *reth;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	u32 bth0, psn, len, rkey;
	bool fecn;
	u8 next;
	u64 vaddr;
	पूर्णांक dअगरf;
	u8 nack_state = IB_NAK_INVALID_REQUEST;

	bth0 = be32_to_cpu(ohdr->bth[0]);
	अगर (hfi1_ruc_check_hdr(ibp, packet))
		वापस;

	fecn = process_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdr->bth[2]));
	trace_hfi1_rsp_rcv_tid_पढ़ो_req(qp, psn);

	अगर (qp->state == IB_QPS_RTR && !(qp->r_flags & RVT_R_COMM_EST))
		rvt_comm_est(qp);

	अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_READ)))
		जाओ nack_inv;

	reth = &ohdr->u.tid_rdma.r_req.reth;
	vaddr = be64_to_cpu(reth->vaddr);
	len = be32_to_cpu(reth->length);
	/* The length needs to be in multiples of PAGE_SIZE */
	अगर (!len || len & ~PAGE_MASK || len > qpriv->tid_rdma.local.max_len)
		जाओ nack_inv;

	dअगरf = delta_psn(psn, qp->r_psn);
	अगर (unlikely(dअगरf)) अणु
		tid_rdma_rcv_err(packet, ohdr, qp, psn, dअगरf, fecn);
		वापस;
	पूर्ण

	/* We've verअगरied the request, insert it पूर्णांकo the ack queue. */
	next = qp->r_head_ack_queue + 1;
	अगर (next > rvt_size_atomic(ib_to_rvt(qp->ibqp.device)))
		next = 0;
	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (unlikely(next == qp->s_tail_ack_queue)) अणु
		अगर (!qp->s_ack_queue[next].sent) अणु
			nack_state = IB_NAK_REMOTE_OPERATIONAL_ERROR;
			जाओ nack_inv_unlock;
		पूर्ण
		update_ack_queue(qp, next);
	पूर्ण
	e = &qp->s_ack_queue[qp->r_head_ack_queue];
	release_rdma_sge_mr(e);

	rkey = be32_to_cpu(reth->rkey);
	qp->r_len = len;

	अगर (unlikely(!rvt_rkey_ok(qp, &e->rdma_sge, qp->r_len, vaddr,
				  rkey, IB_ACCESS_REMOTE_READ)))
		जाओ nack_acc;

	/* Accept the request parameters */
	अगर (tid_rdma_rcv_पढ़ो_request(qp, e, packet, ohdr, bth0, psn, vaddr,
				      len))
		जाओ nack_inv_unlock;

	qp->r_state = e->opcode;
	qp->r_nak_state = 0;
	/*
	 * We need to increment the MSN here instead of when we
	 * finish sending the result since a duplicate request would
	 * increment it more than once.
	 */
	qp->r_msn++;
	qp->r_psn += e->lpsn - e->psn + 1;

	qp->r_head_ack_queue = next;

	/*
	 * For all requests other than TID WRITE which are added to the ack
	 * queue, qpriv->r_tid_alloc follows qp->r_head_ack_queue. It is ok to
	 * करो this because of पूर्णांकerlocks between these and TID WRITE
	 * requests. The same change has also been made in hfi1_rc_rcv().
	 */
	qpriv->r_tid_alloc = qp->r_head_ack_queue;

	/* Schedule the send tasklet. */
	qp->s_flags |= RVT_S_RESP_PENDING;
	अगर (fecn)
		qp->s_flags |= RVT_S_ECN;
	hfi1_schedule_send(qp);

	spin_unlock_irqrestore(&qp->s_lock, flags);
	वापस;

nack_inv_unlock:
	spin_unlock_irqrestore(&qp->s_lock, flags);
nack_inv:
	rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
	qp->r_nak_state = nack_state;
	qp->r_ack_psn = qp->r_psn;
	/* Queue NAK क्रम later */
	rc_defered_ack(rcd, qp);
	वापस;
nack_acc:
	spin_unlock_irqrestore(&qp->s_lock, flags);
	rvt_rc_error(qp, IB_WC_LOC_PROT_ERR);
	qp->r_nak_state = IB_NAK_REMOTE_ACCESS_ERROR;
	qp->r_ack_psn = qp->r_psn;
पूर्ण

u32 hfi1_build_tid_rdma_पढ़ो_resp(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e,
				  काष्ठा ib_other_headers *ohdr, u32 *bth0,
				  u32 *bth1, u32 *bth2, u32 *len, bool *last)
अणु
	काष्ठा hfi1_ack_priv *epriv = e->priv;
	काष्ठा tid_rdma_request *req = &epriv->tid_req;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_rdma_flow *flow = &req->flows[req->clear_tail];
	u32 tidentry = flow->tid_entry[flow->tid_idx];
	u32 tidlen = EXP_TID_GET(tidentry, LEN) << PAGE_SHIFT;
	काष्ठा tid_rdma_पढ़ो_resp *resp = &ohdr->u.tid_rdma.r_rsp;
	u32 next_offset, om = KDETH_OM_LARGE;
	bool last_pkt;
	u32 hdwords = 0;
	काष्ठा tid_rdma_params *remote;

	*len = min_t(u32, qp->pmtu, tidlen - flow->tid_offset);
	flow->sent += *len;
	next_offset = flow->tid_offset + *len;
	last_pkt = (flow->sent >= flow->length);

	trace_hfi1_tid_entry_build_पढ़ो_resp(qp, flow->tid_idx, tidentry);
	trace_hfi1_tid_flow_build_पढ़ो_resp(qp, req->clear_tail, flow);

	rcu_पढ़ो_lock();
	remote = rcu_dereference(qpriv->tid_rdma.remote);
	अगर (!remote) अणु
		rcu_पढ़ो_unlock();
		जाओ करोne;
	पूर्ण
	KDETH_RESET(resp->kdeth0, KVER, 0x1);
	KDETH_SET(resp->kdeth0, SH, !last_pkt);
	KDETH_SET(resp->kdeth0, INTR, !!(!last_pkt && remote->urg));
	KDETH_SET(resp->kdeth0, TIDCTRL, EXP_TID_GET(tidentry, CTRL));
	KDETH_SET(resp->kdeth0, TID, EXP_TID_GET(tidentry, IDX));
	KDETH_SET(resp->kdeth0, OM, om == KDETH_OM_LARGE);
	KDETH_SET(resp->kdeth0, OFFSET, flow->tid_offset / om);
	KDETH_RESET(resp->kdeth1, JKEY, remote->jkey);
	resp->verbs_qp = cpu_to_be32(qp->remote_qpn);
	rcu_पढ़ो_unlock();

	resp->aeth = rvt_compute_aeth(qp);
	resp->verbs_psn = cpu_to_be32(mask_psn(flow->flow_state.ib_spsn +
					       flow->pkt));

	*bth0 = TID_OP(READ_RESP) << 24;
	*bth1 = flow->tid_qpn;
	*bth2 = mask_psn(((flow->flow_state.spsn + flow->pkt++) &
			  HFI1_KDETH_BTH_SEQ_MASK) |
			 (flow->flow_state.generation <<
			  HFI1_KDETH_BTH_SEQ_SHIFT));
	*last = last_pkt;
	अगर (last_pkt)
		/* Advance to next flow */
		req->clear_tail = (req->clear_tail + 1) &
				  (MAX_FLOWS - 1);

	अगर (next_offset >= tidlen) अणु
		flow->tid_offset = 0;
		flow->tid_idx++;
	पूर्ण अन्यथा अणु
		flow->tid_offset = next_offset;
	पूर्ण

	hdwords = माप(ohdr->u.tid_rdma.r_rsp) / माप(u32);

करोne:
	वापस hdwords;
पूर्ण

अटल अंतरभूत काष्ठा tid_rdma_request *
find_tid_request(काष्ठा rvt_qp *qp, u32 psn, क्रमागत ib_wr_opcode opcode)
	__must_hold(&qp->s_lock)
अणु
	काष्ठा rvt_swqe *wqe;
	काष्ठा tid_rdma_request *req = शून्य;
	u32 i, end;

	end = qp->s_cur + 1;
	अगर (end == qp->s_size)
		end = 0;
	क्रम (i = qp->s_acked; i != end;) अणु
		wqe = rvt_get_swqe_ptr(qp, i);
		अगर (cmp_psn(psn, wqe->psn) >= 0 &&
		    cmp_psn(psn, wqe->lpsn) <= 0) अणु
			अगर (wqe->wr.opcode == opcode)
				req = wqe_to_tid_req(wqe);
			अवरोध;
		पूर्ण
		अगर (++i == qp->s_size)
			i = 0;
	पूर्ण

	वापस req;
पूर्ण

व्योम hfi1_rc_rcv_tid_rdma_पढ़ो_resp(काष्ठा hfi1_packet *packet)
अणु
	/* HANDLER FOR TID RDMA READ RESPONSE packet (Requestor side */

	/*
	 * 1. Find matching SWQE
	 * 2. Check that the entire segment has been पढ़ो.
	 * 3. Remove HFI1_S_WAIT_TID_RESP from s_flags.
	 * 4. Free the TID flow resources.
	 * 5. Kick the send engine (hfi1_schedule_send())
	 */
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;
	u32 opcode, aeth;
	bool fecn;
	अचिन्हित दीर्घ flags;
	u32 kpsn, ipsn;

	trace_hfi1_sender_rcv_tid_पढ़ो_resp(qp);
	fecn = process_ecn(qp, packet);
	kpsn = mask_psn(be32_to_cpu(ohdr->bth[2]));
	aeth = be32_to_cpu(ohdr->u.tid_rdma.r_rsp.aeth);
	opcode = (be32_to_cpu(ohdr->bth[0]) >> 24) & 0xff;

	spin_lock_irqsave(&qp->s_lock, flags);
	ipsn = mask_psn(be32_to_cpu(ohdr->u.tid_rdma.r_rsp.verbs_psn));
	req = find_tid_request(qp, ipsn, IB_WR_TID_RDMA_READ);
	अगर (unlikely(!req))
		जाओ ack_op_err;

	flow = &req->flows[req->clear_tail];
	/* When header suppression is disabled */
	अगर (cmp_psn(ipsn, flow->flow_state.ib_lpsn)) अणु
		update_r_next_psn_fecn(packet, priv, rcd, flow, fecn);

		अगर (cmp_psn(kpsn, flow->flow_state.r_next_psn))
			जाओ ack_करोne;
		flow->flow_state.r_next_psn = mask_psn(kpsn + 1);
		/*
		 * Copy the payload to destination buffer अगर this packet is
		 * delivered as an eager packet due to RSM rule and FECN.
		 * The RSM rule selects FECN bit in BTH and SH bit in
		 * KDETH header and thereक्रमe will not match the last
		 * packet of each segment that has SH bit cleared.
		 */
		अगर (fecn && packet->etype == RHF_RCV_TYPE_EAGER) अणु
			काष्ठा rvt_sge_state ss;
			u32 len;
			u32 tlen = packet->tlen;
			u16 hdrsize = packet->hlen;
			u8 pad = packet->pad;
			u8 extra_bytes = pad + packet->extra_byte +
				(SIZE_OF_CRC << 2);
			u32 pmtu = qp->pmtu;

			अगर (unlikely(tlen != (hdrsize + pmtu + extra_bytes)))
				जाओ ack_op_err;
			len = restart_sge(&ss, req->e.swqe, ipsn, pmtu);
			अगर (unlikely(len < pmtu))
				जाओ ack_op_err;
			rvt_copy_sge(qp, &ss, packet->payload, pmtu, false,
				     false);
			/* Raise the sw sequence check flag क्रम next packet */
			priv->s_flags |= HFI1_R_TID_SW_PSN;
		पूर्ण

		जाओ ack_करोne;
	पूर्ण
	flow->flow_state.r_next_psn = mask_psn(kpsn + 1);
	req->ack_pending--;
	priv->pending_tid_r_segs--;
	qp->s_num_rd_atomic--;
	अगर ((qp->s_flags & RVT_S_WAIT_FENCE) &&
	    !qp->s_num_rd_atomic) अणु
		qp->s_flags &= ~(RVT_S_WAIT_FENCE |
				 RVT_S_WAIT_ACK);
		hfi1_schedule_send(qp);
	पूर्ण
	अगर (qp->s_flags & RVT_S_WAIT_RDMAR) अणु
		qp->s_flags &= ~(RVT_S_WAIT_RDMAR | RVT_S_WAIT_ACK);
		hfi1_schedule_send(qp);
	पूर्ण

	trace_hfi1_ack(qp, ipsn);
	trace_hfi1_tid_req_rcv_पढ़ो_resp(qp, 0, req->e.swqe->wr.opcode,
					 req->e.swqe->psn, req->e.swqe->lpsn,
					 req);
	trace_hfi1_tid_flow_rcv_पढ़ो_resp(qp, req->clear_tail, flow);

	/* Release the tid resources */
	hfi1_kern_exp_rcv_clear(req);

	अगर (!करो_rc_ack(qp, aeth, ipsn, opcode, 0, rcd))
		जाओ ack_करोne;

	/* If not करोne yet, build next पढ़ो request */
	अगर (++req->comp_seg >= req->total_segs) अणु
		priv->tid_r_comp++;
		req->state = TID_REQUEST_COMPLETE;
	पूर्ण

	/*
	 * Clear the hw flow under two conditions:
	 * 1. This request is a sync poपूर्णांक and it is complete;
	 * 2. Current request is completed and there are no more requests.
	 */
	अगर ((req->state == TID_REQUEST_SYNC &&
	     req->comp_seg == req->cur_seg) ||
	    priv->tid_r_comp == priv->tid_r_reqs) अणु
		hfi1_kern_clear_hw_flow(priv->rcd, qp);
		priv->s_flags &= ~HFI1_R_TID_SW_PSN;
		अगर (req->state == TID_REQUEST_SYNC)
			req->state = TID_REQUEST_ACTIVE;
	पूर्ण

	hfi1_schedule_send(qp);
	जाओ ack_करोne;

ack_op_err:
	/*
	 * The test indicates that the send engine has finished its cleanup
	 * after sending the request and it's now safe to put the QP पूर्णांकo error
	 * state. However, अगर the wqe queue is empty (qp->s_acked == qp->s_tail
	 * == qp->s_head), it would be unsafe to complete the wqe poपूर्णांकed by
	 * qp->s_acked here. Putting the qp पूर्णांकo error state will safely flush
	 * all reमुख्यing requests.
	 */
	अगर (qp->s_last == qp->s_acked)
		rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);

ack_करोne:
	spin_unlock_irqrestore(&qp->s_lock, flags);
पूर्ण

व्योम hfi1_kern_पढ़ो_tid_flow_मुक्त(काष्ठा rvt_qp *qp)
	__must_hold(&qp->s_lock)
अणु
	u32 n = qp->s_acked;
	काष्ठा rvt_swqe *wqe;
	काष्ठा tid_rdma_request *req;
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	lockdep_निश्चित_held(&qp->s_lock);
	/* Free any TID entries */
	जबतक (n != qp->s_tail) अणु
		wqe = rvt_get_swqe_ptr(qp, n);
		अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ) अणु
			req = wqe_to_tid_req(wqe);
			hfi1_kern_exp_rcv_clear_all(req);
		पूर्ण

		अगर (++n == qp->s_size)
			n = 0;
	पूर्ण
	/* Free flow */
	hfi1_kern_clear_hw_flow(priv->rcd, qp);
पूर्ण

अटल bool tid_rdma_tid_err(काष्ठा hfi1_packet *packet, u8 rcv_type)
अणु
	काष्ठा rvt_qp *qp = packet->qp;

	अगर (rcv_type >= RHF_RCV_TYPE_IB)
		जाओ करोne;

	spin_lock(&qp->s_lock);

	/*
	 * We've ran out of space in the eager buffer.
	 * Eagerly received KDETH packets which require space in the
	 * Eager buffer (packet that have payload) are TID RDMA WRITE
	 * response packets. In this हाल, we have to re-transmit the
	 * TID RDMA WRITE request.
	 */
	अगर (rcv_type == RHF_RCV_TYPE_EAGER) अणु
		hfi1_restart_rc(qp, qp->s_last_psn + 1, 1);
		hfi1_schedule_send(qp);
	पूर्ण

	/* Since no payload is delivered, just drop the packet */
	spin_unlock(&qp->s_lock);
करोne:
	वापस true;
पूर्ण

अटल व्योम restart_tid_rdma_पढ़ो_req(काष्ठा hfi1_ctxtdata *rcd,
				      काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe)
अणु
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;

	/* Start from the right segment */
	qp->r_flags |= RVT_R_RDMAR_SEQ;
	req = wqe_to_tid_req(wqe);
	flow = &req->flows[req->clear_tail];
	hfi1_restart_rc(qp, flow->flow_state.ib_spsn, 0);
	अगर (list_empty(&qp->rspरुको)) अणु
		qp->r_flags |= RVT_R_RSP_SEND;
		rvt_get_qp(qp);
		list_add_tail(&qp->rspरुको, &rcd->qp_रुको_list);
	पूर्ण
पूर्ण

/*
 * Handle the KDETH eflags क्रम TID RDMA READ response.
 *
 * Return true अगर the last packet क्रम a segment has been received and it is
 * समय to process the response normally; otherwise, वापस true.
 *
 * The caller must hold the packet->qp->r_lock and the rcu_पढ़ो_lock.
 */
अटल bool handle_पढ़ो_kdeth_eflags(काष्ठा hfi1_ctxtdata *rcd,
				     काष्ठा hfi1_packet *packet, u8 rcv_type,
				     u8 rte, u32 psn, u32 ibpsn)
	__must_hold(&packet->qp->r_lock) __must_hold(RCU)
अणु
	काष्ठा hfi1_pportdata *ppd = rcd->ppd;
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा hfi1_ibport *ibp;
	काष्ठा rvt_swqe *wqe;
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;
	u32 ack_psn;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	bool ret = true;
	पूर्णांक dअगरf = 0;
	u32 fpsn;

	lockdep_निश्चित_held(&qp->r_lock);
	trace_hfi1_rsp_पढ़ो_kdeth_eflags(qp, ibpsn);
	trace_hfi1_sender_पढ़ो_kdeth_eflags(qp);
	trace_hfi1_tid_पढ़ो_sender_kdeth_eflags(qp, 0);
	spin_lock(&qp->s_lock);
	/* If the psn is out of valid range, drop the packet */
	अगर (cmp_psn(ibpsn, qp->s_last_psn) < 0 ||
	    cmp_psn(ibpsn, qp->s_psn) > 0)
		जाओ s_unlock;

	/*
	 * Note that NAKs implicitly ACK outstanding SEND and RDMA ग_लिखो
	 * requests and implicitly NAK RDMA पढ़ो and atomic requests issued
	 * beक्रमe the NAK'ed request.
	 */
	ack_psn = ibpsn - 1;
	wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
	ibp = to_iport(qp->ibqp.device, qp->port_num);

	/* Complete WQEs that the PSN finishes. */
	जबतक ((पूर्णांक)delta_psn(ack_psn, wqe->lpsn) >= 0) अणु
		/*
		 * If this request is a RDMA पढ़ो or atomic, and the NACK is
		 * क्रम a later operation, this NACK NAKs the RDMA पढ़ो or
		 * atomic.
		 */
		अगर (wqe->wr.opcode == IB_WR_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_TID_RDMA_READ ||
		    wqe->wr.opcode == IB_WR_ATOMIC_CMP_AND_SWP ||
		    wqe->wr.opcode == IB_WR_ATOMIC_FETCH_AND_ADD) अणु
			/* Retry this request. */
			अगर (!(qp->r_flags & RVT_R_RDMAR_SEQ)) अणु
				qp->r_flags |= RVT_R_RDMAR_SEQ;
				अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ) अणु
					restart_tid_rdma_पढ़ो_req(rcd, qp,
								  wqe);
				पूर्ण अन्यथा अणु
					hfi1_restart_rc(qp, qp->s_last_psn + 1,
							0);
					अगर (list_empty(&qp->rspरुको)) अणु
						qp->r_flags |= RVT_R_RSP_SEND;
						rvt_get_qp(qp);
						list_add_tail(/* रुको */
						   &qp->rspरुको,
						   &rcd->qp_रुको_list);
					पूर्ण
				पूर्ण
			पूर्ण
			/*
			 * No need to process the NAK since we are
			 * restarting an earlier request.
			 */
			अवरोध;
		पूर्ण

		wqe = करो_rc_completion(qp, wqe, ibp);
		अगर (qp->s_acked == qp->s_tail)
			जाओ s_unlock;
	पूर्ण

	अगर (qp->s_acked == qp->s_tail)
		जाओ s_unlock;

	/* Handle the eflags क्रम the request */
	अगर (wqe->wr.opcode != IB_WR_TID_RDMA_READ)
		जाओ s_unlock;

	req = wqe_to_tid_req(wqe);
	trace_hfi1_tid_req_पढ़ो_kdeth_eflags(qp, 0, wqe->wr.opcode, wqe->psn,
					     wqe->lpsn, req);
	चयन (rcv_type) अणु
	हाल RHF_RCV_TYPE_EXPECTED:
		चयन (rte) अणु
		हाल RHF_RTE_EXPECTED_FLOW_SEQ_ERR:
			/*
			 * On the first occurrence of a Flow Sequence error,
			 * the flag TID_FLOW_SW_PSN is set.
			 *
			 * After that, the flow is *not* reprogrammed and the
			 * protocol falls back to SW PSN checking. This is करोne
			 * to prevent continuous Flow Sequence errors क्रम any
			 * packets that could be still in the fabric.
			 */
			flow = &req->flows[req->clear_tail];
			trace_hfi1_tid_flow_पढ़ो_kdeth_eflags(qp,
							      req->clear_tail,
							      flow);
			अगर (priv->s_flags & HFI1_R_TID_SW_PSN) अणु
				dअगरf = cmp_psn(psn,
					       flow->flow_state.r_next_psn);
				अगर (dअगरf > 0) अणु
					/* Drop the packet.*/
					जाओ s_unlock;
				पूर्ण अन्यथा अगर (dअगरf < 0) अणु
					/*
					 * If a response packet क्रम a restarted
					 * request has come back, reset the
					 * restart flag.
					 */
					अगर (qp->r_flags & RVT_R_RDMAR_SEQ)
						qp->r_flags &=
							~RVT_R_RDMAR_SEQ;

					/* Drop the packet.*/
					जाओ s_unlock;
				पूर्ण

				/*
				 * If SW PSN verअगरication is successful and
				 * this is the last packet in the segment, tell
				 * the caller to process it as a normal packet.
				 */
				fpsn = full_flow_psn(flow,
						     flow->flow_state.lpsn);
				अगर (cmp_psn(fpsn, psn) == 0) अणु
					ret = false;
					अगर (qp->r_flags & RVT_R_RDMAR_SEQ)
						qp->r_flags &=
							~RVT_R_RDMAR_SEQ;
				पूर्ण
				flow->flow_state.r_next_psn =
					mask_psn(psn + 1);
			पूर्ण अन्यथा अणु
				u32 last_psn;

				last_psn = पढ़ो_r_next_psn(dd, rcd->ctxt,
							   flow->idx);
				flow->flow_state.r_next_psn = last_psn;
				priv->s_flags |= HFI1_R_TID_SW_PSN;
				/*
				 * If no request has been restarted yet,
				 * restart the current one.
				 */
				अगर (!(qp->r_flags & RVT_R_RDMAR_SEQ))
					restart_tid_rdma_पढ़ो_req(rcd, qp,
								  wqe);
			पूर्ण

			अवरोध;

		हाल RHF_RTE_EXPECTED_FLOW_GEN_ERR:
			/*
			 * Since the TID flow is able to ride through
			 * generation mismatch, drop this stale packet.
			 */
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल RHF_RCV_TYPE_ERROR:
		चयन (rte) अणु
		हाल RHF_RTE_ERROR_OP_CODE_ERR:
		हाल RHF_RTE_ERROR_KHDR_MIN_LEN_ERR:
		हाल RHF_RTE_ERROR_KHDR_HCRC_ERR:
		हाल RHF_RTE_ERROR_KHDR_KVER_ERR:
		हाल RHF_RTE_ERROR_CONTEXT_ERR:
		हाल RHF_RTE_ERROR_KHDR_TID_ERR:
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
s_unlock:
	spin_unlock(&qp->s_lock);
	वापस ret;
पूर्ण

bool hfi1_handle_kdeth_eflags(काष्ठा hfi1_ctxtdata *rcd,
			      काष्ठा hfi1_pportdata *ppd,
			      काष्ठा hfi1_packet *packet)
अणु
	काष्ठा hfi1_ibport *ibp = &ppd->ibport_data;
	काष्ठा hfi1_devdata *dd = ppd->dd;
	काष्ठा rvt_dev_info *rdi = &dd->verbs_dev.rdi;
	u8 rcv_type = rhf_rcv_type(packet->rhf);
	u8 rte = rhf_rcv_type_err(packet->rhf);
	काष्ठा ib_header *hdr = packet->hdr;
	काष्ठा ib_other_headers *ohdr = शून्य;
	पूर्णांक lnh = be16_to_cpu(hdr->lrh[0]) & 3;
	u16 lid  = be16_to_cpu(hdr->lrh[1]);
	u8 opcode;
	u32 qp_num, psn, ibpsn;
	काष्ठा rvt_qp *qp;
	काष्ठा hfi1_qp_priv *qpriv;
	अचिन्हित दीर्घ flags;
	bool ret = true;
	काष्ठा rvt_ack_entry *e;
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;
	पूर्णांक dअगरf = 0;

	trace_hfi1_msg_handle_kdeth_eflags(शून्य, "Kdeth error: rhf ",
					   packet->rhf);
	अगर (packet->rhf & RHF_ICRC_ERR)
		वापस ret;

	packet->ohdr = &hdr->u.oth;
	ohdr = packet->ohdr;
	trace_input_ibhdr(rcd->dd, packet, !!(rhf_dc_info(packet->rhf)));

	/* Get the destination QP number. */
	qp_num = be32_to_cpu(ohdr->u.tid_rdma.r_rsp.verbs_qp) &
		RVT_QPN_MASK;
	अगर (lid >= be16_to_cpu(IB_MULTICAST_LID_BASE))
		जाओ drop;

	psn = mask_psn(be32_to_cpu(ohdr->bth[2]));
	opcode = (be32_to_cpu(ohdr->bth[0]) >> 24) & 0xff;

	rcu_पढ़ो_lock();
	qp = rvt_lookup_qpn(rdi, &ibp->rvp, qp_num);
	अगर (!qp)
		जाओ rcu_unlock;

	packet->qp = qp;

	/* Check क्रम valid receive state. */
	spin_lock_irqsave(&qp->r_lock, flags);
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK)) अणु
		ibp->rvp.n_pkt_drops++;
		जाओ r_unlock;
	पूर्ण

	अगर (packet->rhf & RHF_TID_ERR) अणु
		/* For TIDERR and RC QPs preemptively schedule a NAK */
		u32 tlen = rhf_pkt_len(packet->rhf); /* in bytes */

		/* Sanity check packet */
		अगर (tlen < 24)
			जाओ r_unlock;

		/*
		 * Check क्रम GRH. We should never get packets with GRH in this
		 * path.
		 */
		अगर (lnh == HFI1_LRH_GRH)
			जाओ r_unlock;

		अगर (tid_rdma_tid_err(packet, rcv_type))
			जाओ r_unlock;
	पूर्ण

	/* handle TID RDMA READ */
	अगर (opcode == TID_OP(READ_RESP)) अणु
		ibpsn = be32_to_cpu(ohdr->u.tid_rdma.r_rsp.verbs_psn);
		ibpsn = mask_psn(ibpsn);
		ret = handle_पढ़ो_kdeth_eflags(rcd, packet, rcv_type, rte, psn,
					       ibpsn);
		जाओ r_unlock;
	पूर्ण

	/*
	 * qp->s_tail_ack_queue poपूर्णांकs to the rvt_ack_entry currently being
	 * processed. These a completed sequentially so we can be sure that
	 * the poपूर्णांकer will not change until the entire request has completed.
	 */
	spin_lock(&qp->s_lock);
	qpriv = qp->priv;
	अगर (qpriv->r_tid_tail == HFI1_QP_WQE_INVALID ||
	    qpriv->r_tid_tail == qpriv->r_tid_head)
		जाओ unlock;
	e = &qp->s_ack_queue[qpriv->r_tid_tail];
	अगर (e->opcode != TID_OP(WRITE_REQ))
		जाओ unlock;
	req = ack_to_tid_req(e);
	अगर (req->comp_seg == req->cur_seg)
		जाओ unlock;
	flow = &req->flows[req->clear_tail];
	trace_hfi1_eflags_err_ग_लिखो(qp, rcv_type, rte, psn);
	trace_hfi1_rsp_handle_kdeth_eflags(qp, psn);
	trace_hfi1_tid_ग_लिखो_rsp_handle_kdeth_eflags(qp);
	trace_hfi1_tid_req_handle_kdeth_eflags(qp, 0, e->opcode, e->psn,
					       e->lpsn, req);
	trace_hfi1_tid_flow_handle_kdeth_eflags(qp, req->clear_tail, flow);

	चयन (rcv_type) अणु
	हाल RHF_RCV_TYPE_EXPECTED:
		चयन (rte) अणु
		हाल RHF_RTE_EXPECTED_FLOW_SEQ_ERR:
			अगर (!(qpriv->s_flags & HFI1_R_TID_SW_PSN)) अणु
				qpriv->s_flags |= HFI1_R_TID_SW_PSN;
				flow->flow_state.r_next_psn =
					पढ़ो_r_next_psn(dd, rcd->ctxt,
							flow->idx);
				qpriv->r_next_psn_kdeth =
					flow->flow_state.r_next_psn;
				जाओ nak_psn;
			पूर्ण अन्यथा अणु
				/*
				 * If the received PSN करोes not match the next
				 * expected PSN, NAK the packet.
				 * However, only करो that अगर we know that the a
				 * NAK has alपढ़ोy been sent. Otherwise, this
				 * mismatch could be due to packets that were
				 * alपढ़ोy in flight.
				 */
				dअगरf = cmp_psn(psn,
					       flow->flow_state.r_next_psn);
				अगर (dअगरf > 0)
					जाओ nak_psn;
				अन्यथा अगर (dअगरf < 0)
					अवरोध;

				qpriv->s_nak_state = 0;
				/*
				 * If SW PSN verअगरication is successful and this
				 * is the last packet in the segment, tell the
				 * caller to process it as a normal packet.
				 */
				अगर (psn == full_flow_psn(flow,
							 flow->flow_state.lpsn))
					ret = false;
				flow->flow_state.r_next_psn =
					mask_psn(psn + 1);
				qpriv->r_next_psn_kdeth =
					flow->flow_state.r_next_psn;
			पूर्ण
			अवरोध;

		हाल RHF_RTE_EXPECTED_FLOW_GEN_ERR:
			जाओ nak_psn;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	हाल RHF_RCV_TYPE_ERROR:
		चयन (rte) अणु
		हाल RHF_RTE_ERROR_OP_CODE_ERR:
		हाल RHF_RTE_ERROR_KHDR_MIN_LEN_ERR:
		हाल RHF_RTE_ERROR_KHDR_HCRC_ERR:
		हाल RHF_RTE_ERROR_KHDR_KVER_ERR:
		हाल RHF_RTE_ERROR_CONTEXT_ERR:
		हाल RHF_RTE_ERROR_KHDR_TID_ERR:
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण

unlock:
	spin_unlock(&qp->s_lock);
r_unlock:
	spin_unlock_irqrestore(&qp->r_lock, flags);
rcu_unlock:
	rcu_पढ़ो_unlock();
drop:
	वापस ret;
nak_psn:
	ibp->rvp.n_rc_seqnak++;
	अगर (!qpriv->s_nak_state) अणु
		qpriv->s_nak_state = IB_NAK_PSN_ERROR;
		/* We are NAK'ing the next expected PSN */
		qpriv->s_nak_psn = mask_psn(flow->flow_state.r_next_psn);
		tid_rdma_trigger_ack(qp);
	पूर्ण
	जाओ unlock;
पूर्ण

/*
 * "Rewind" the TID request inक्रमmation.
 * This means that we reset the state back to ACTIVE,
 * find the proper flow, set the flow index to that flow,
 * and reset the flow inक्रमmation.
 */
व्योम hfi1_tid_rdma_restart_req(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
			       u32 *bth2)
अणु
	काष्ठा tid_rdma_request *req = wqe_to_tid_req(wqe);
	काष्ठा tid_rdma_flow *flow;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	पूर्णांक dअगरf, delta_pkts;
	u32 tididx = 0, i;
	u16 fidx;

	अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ) अणु
		*bth2 = mask_psn(qp->s_psn);
		flow = find_flow_ib(req, *bth2, &fidx);
		अगर (!flow) अणु
			trace_hfi1_msg_tid_restart_req(/* msg */
			   qp, "!!!!!! Could not find flow to restart: bth2 ",
			   (u64)*bth2);
			trace_hfi1_tid_req_restart_req(qp, 0, wqe->wr.opcode,
						       wqe->psn, wqe->lpsn,
						       req);
			वापस;
		पूर्ण
	पूर्ण अन्यथा अणु
		fidx = req->acked_tail;
		flow = &req->flows[fidx];
		*bth2 = mask_psn(req->r_ack_psn);
	पूर्ण

	अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ)
		delta_pkts = delta_psn(*bth2, flow->flow_state.ib_spsn);
	अन्यथा
		delta_pkts = delta_psn(*bth2,
				       full_flow_psn(flow,
						     flow->flow_state.spsn));

	trace_hfi1_tid_flow_restart_req(qp, fidx, flow);
	dअगरf = delta_pkts + flow->resync_npkts;

	flow->sent = 0;
	flow->pkt = 0;
	flow->tid_idx = 0;
	flow->tid_offset = 0;
	अगर (dअगरf) अणु
		क्रम (tididx = 0; tididx < flow->tidcnt; tididx++) अणु
			u32 tidentry = flow->tid_entry[tididx], tidlen,
				tidnpkts, npkts;

			flow->tid_offset = 0;
			tidlen = EXP_TID_GET(tidentry, LEN) * PAGE_SIZE;
			tidnpkts = rvt_भाग_round_up_mtu(qp, tidlen);
			npkts = min_t(u32, dअगरf, tidnpkts);
			flow->pkt += npkts;
			flow->sent += (npkts == tidnpkts ? tidlen :
				       npkts * qp->pmtu);
			flow->tid_offset += npkts * qp->pmtu;
			dअगरf -= npkts;
			अगर (!dअगरf)
				अवरोध;
		पूर्ण
	पूर्ण
	अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE) अणु
		rvt_skip_sge(&qpriv->tid_ss, (req->cur_seg * req->seg_len) +
			     flow->sent, 0);
		/*
		 * Packet PSN is based on flow_state.spsn + flow->pkt. However,
		 * during a RESYNC, the generation is incremented and the
		 * sequence is reset to 0. Since we've adjusted the npkts in the
		 * flow and the SGE has been sufficiently advanced, we have to
		 * adjust flow->pkt in order to calculate the correct PSN.
		 */
		flow->pkt -= flow->resync_npkts;
	पूर्ण

	अगर (flow->tid_offset ==
	    EXP_TID_GET(flow->tid_entry[tididx], LEN) * PAGE_SIZE) अणु
		tididx++;
		flow->tid_offset = 0;
	पूर्ण
	flow->tid_idx = tididx;
	अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ)
		/* Move flow_idx to correct index */
		req->flow_idx = fidx;
	अन्यथा
		req->clear_tail = fidx;

	trace_hfi1_tid_flow_restart_req(qp, fidx, flow);
	trace_hfi1_tid_req_restart_req(qp, 0, wqe->wr.opcode, wqe->psn,
				       wqe->lpsn, req);
	req->state = TID_REQUEST_ACTIVE;
	अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE) अणु
		/* Reset all the flows that we are going to resend */
		fidx = CIRC_NEXT(fidx, MAX_FLOWS);
		i = qpriv->s_tid_tail;
		करो अणु
			क्रम (; CIRC_CNT(req->setup_head, fidx, MAX_FLOWS);
			      fidx = CIRC_NEXT(fidx, MAX_FLOWS)) अणु
				req->flows[fidx].sent = 0;
				req->flows[fidx].pkt = 0;
				req->flows[fidx].tid_idx = 0;
				req->flows[fidx].tid_offset = 0;
				req->flows[fidx].resync_npkts = 0;
			पूर्ण
			अगर (i == qpriv->s_tid_cur)
				अवरोध;
			करो अणु
				i = (++i == qp->s_size ? 0 : i);
				wqe = rvt_get_swqe_ptr(qp, i);
			पूर्ण जबतक (wqe->wr.opcode != IB_WR_TID_RDMA_WRITE);
			req = wqe_to_tid_req(wqe);
			req->cur_seg = req->ack_seg;
			fidx = req->acked_tail;
			/* Pull req->clear_tail back */
			req->clear_tail = fidx;
		पूर्ण जबतक (1);
	पूर्ण
पूर्ण

व्योम hfi1_qp_kern_exp_rcv_clear_all(काष्ठा rvt_qp *qp)
अणु
	पूर्णांक i, ret;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_flow_state *fs;

	अगर (qp->ibqp.qp_type != IB_QPT_RC || !HFI1_CAP_IS_KSET(TID_RDMA))
		वापस;

	/*
	 * First, clear the flow to help prevent any delayed packets from
	 * being delivered.
	 */
	fs = &qpriv->flow_state;
	अगर (fs->index != RXE_NUM_TID_FLOWS)
		hfi1_kern_clear_hw_flow(qpriv->rcd, qp);

	क्रम (i = qp->s_acked; i != qp->s_head;) अणु
		काष्ठा rvt_swqe *wqe = rvt_get_swqe_ptr(qp, i);

		अगर (++i == qp->s_size)
			i = 0;
		/* Free only locally allocated TID entries */
		अगर (wqe->wr.opcode != IB_WR_TID_RDMA_READ)
			जारी;
		करो अणु
			काष्ठा hfi1_swqe_priv *priv = wqe->priv;

			ret = hfi1_kern_exp_rcv_clear(&priv->tid_req);
		पूर्ण जबतक (!ret);
	पूर्ण
	क्रम (i = qp->s_acked_ack_queue; i != qp->r_head_ack_queue;) अणु
		काष्ठा rvt_ack_entry *e = &qp->s_ack_queue[i];

		अगर (++i == rvt_max_atomic(ib_to_rvt(qp->ibqp.device)))
			i = 0;
		/* Free only locally allocated TID entries */
		अगर (e->opcode != TID_OP(WRITE_REQ))
			जारी;
		करो अणु
			काष्ठा hfi1_ack_priv *priv = e->priv;

			ret = hfi1_kern_exp_rcv_clear(&priv->tid_req);
		पूर्ण जबतक (!ret);
	पूर्ण
पूर्ण

bool hfi1_tid_rdma_wqe_पूर्णांकerlock(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe)
अणु
	काष्ठा rvt_swqe *prev;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	u32 s_prev;
	काष्ठा tid_rdma_request *req;

	s_prev = (qp->s_cur == 0 ? qp->s_size : qp->s_cur) - 1;
	prev = rvt_get_swqe_ptr(qp, s_prev);

	चयन (wqe->wr.opcode) अणु
	हाल IB_WR_SEND:
	हाल IB_WR_SEND_WITH_IMM:
	हाल IB_WR_SEND_WITH_INV:
	हाल IB_WR_ATOMIC_CMP_AND_SWP:
	हाल IB_WR_ATOMIC_FETCH_AND_ADD:
	हाल IB_WR_RDMA_WRITE:
	हाल IB_WR_RDMA_WRITE_WITH_IMM:
		चयन (prev->wr.opcode) अणु
		हाल IB_WR_TID_RDMA_WRITE:
			req = wqe_to_tid_req(prev);
			अगर (req->ack_seg != req->total_segs)
				जाओ पूर्णांकerlock;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	हाल IB_WR_RDMA_READ:
		अगर (prev->wr.opcode != IB_WR_TID_RDMA_WRITE)
			अवरोध;
		fallthrough;
	हाल IB_WR_TID_RDMA_READ:
		चयन (prev->wr.opcode) अणु
		हाल IB_WR_RDMA_READ:
			अगर (qp->s_acked != qp->s_cur)
				जाओ पूर्णांकerlock;
			अवरोध;
		हाल IB_WR_TID_RDMA_WRITE:
			req = wqe_to_tid_req(prev);
			अगर (req->ack_seg != req->total_segs)
				जाओ पूर्णांकerlock;
			अवरोध;
		शेष:
			अवरोध;
		पूर्ण
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस false;

पूर्णांकerlock:
	priv->s_flags |= HFI1_S_TID_WAIT_INTERLCK;
	वापस true;
पूर्ण

/* Does @sge meet the alignment requirements क्रम tid rdma? */
अटल अंतरभूत bool hfi1_check_sge_align(काष्ठा rvt_qp *qp,
					काष्ठा rvt_sge *sge, पूर्णांक num_sge)
अणु
	पूर्णांक i;

	क्रम (i = 0; i < num_sge; i++, sge++) अणु
		trace_hfi1_sge_check_align(qp, i, sge);
		अगर ((u64)sge->vaddr & ~PAGE_MASK ||
		    sge->sge_length & ~PAGE_MASK)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

व्योम setup_tid_rdma_wqe(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe)
अणु
	काष्ठा hfi1_qp_priv *qpriv = (काष्ठा hfi1_qp_priv *)qp->priv;
	काष्ठा hfi1_swqe_priv *priv = wqe->priv;
	काष्ठा tid_rdma_params *remote;
	क्रमागत ib_wr_opcode new_opcode;
	bool करो_tid_rdma = false;
	काष्ठा hfi1_pportdata *ppd = qpriv->rcd->ppd;

	अगर ((rdma_ah_get_dlid(&qp->remote_ah_attr) & ~((1 << ppd->lmc) - 1)) ==
				ppd->lid)
		वापस;
	अगर (qpriv->hdr_type != HFI1_PKT_TYPE_9B)
		वापस;

	rcu_पढ़ो_lock();
	remote = rcu_dereference(qpriv->tid_rdma.remote);
	/*
	 * If TID RDMA is disabled by the negotiation, करोn't
	 * use it.
	 */
	अगर (!remote)
		जाओ निकास;

	अगर (wqe->wr.opcode == IB_WR_RDMA_READ) अणु
		अगर (hfi1_check_sge_align(qp, &wqe->sg_list[0],
					 wqe->wr.num_sge)) अणु
			new_opcode = IB_WR_TID_RDMA_READ;
			करो_tid_rdma = true;
		पूर्ण
	पूर्ण अन्यथा अगर (wqe->wr.opcode == IB_WR_RDMA_WRITE) अणु
		/*
		 * TID RDMA is enabled क्रम this RDMA WRITE request अगरf:
		 *   1. The remote address is page-aligned,
		 *   2. The length is larger than the minimum segment size,
		 *   3. The length is page-multiple.
		 */
		अगर (!(wqe->rdma_wr.remote_addr & ~PAGE_MASK) &&
		    !(wqe->length & ~PAGE_MASK)) अणु
			new_opcode = IB_WR_TID_RDMA_WRITE;
			करो_tid_rdma = true;
		पूर्ण
	पूर्ण

	अगर (करो_tid_rdma) अणु
		अगर (hfi1_kern_exp_rcv_alloc_flows(&priv->tid_req, GFP_ATOMIC))
			जाओ निकास;
		wqe->wr.opcode = new_opcode;
		priv->tid_req.seg_len =
			min_t(u32, remote->max_len, wqe->length);
		priv->tid_req.total_segs =
			DIV_ROUND_UP(wqe->length, priv->tid_req.seg_len);
		/* Compute the last PSN of the request */
		wqe->lpsn = wqe->psn;
		अगर (wqe->wr.opcode == IB_WR_TID_RDMA_READ) अणु
			priv->tid_req.n_flows = remote->max_पढ़ो;
			qpriv->tid_r_reqs++;
			wqe->lpsn += rvt_भाग_round_up_mtu(qp, wqe->length) - 1;
		पूर्ण अन्यथा अणु
			wqe->lpsn += priv->tid_req.total_segs - 1;
			atomic_inc(&qpriv->n_requests);
		पूर्ण

		priv->tid_req.cur_seg = 0;
		priv->tid_req.comp_seg = 0;
		priv->tid_req.ack_seg = 0;
		priv->tid_req.state = TID_REQUEST_INACTIVE;
		/*
		 * Reset acked_tail.
		 * TID RDMA READ करोes not have ACKs so it करोes not
		 * update the poपूर्णांकer. We have to reset it so TID RDMA
		 * WRITE करोes not get confused.
		 */
		priv->tid_req.acked_tail = priv->tid_req.setup_head;
		trace_hfi1_tid_req_setup_tid_wqe(qp, 1, wqe->wr.opcode,
						 wqe->psn, wqe->lpsn,
						 &priv->tid_req);
	पूर्ण
निकास:
	rcu_पढ़ो_unlock();
पूर्ण

/* TID RDMA WRITE functions */

u32 hfi1_build_tid_rdma_ग_लिखो_req(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
				  काष्ठा ib_other_headers *ohdr,
				  u32 *bth1, u32 *bth2, u32 *len)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_rdma_request *req = wqe_to_tid_req(wqe);
	काष्ठा tid_rdma_params *remote;

	rcu_पढ़ो_lock();
	remote = rcu_dereference(qpriv->tid_rdma.remote);
	/*
	 * Set the number of flow to be used based on negotiated
	 * parameters.
	 */
	req->n_flows = remote->max_ग_लिखो;
	req->state = TID_REQUEST_ACTIVE;

	KDETH_RESET(ohdr->u.tid_rdma.w_req.kdeth0, KVER, 0x1);
	KDETH_RESET(ohdr->u.tid_rdma.w_req.kdeth1, JKEY, remote->jkey);
	ohdr->u.tid_rdma.w_req.reth.vaddr =
		cpu_to_be64(wqe->rdma_wr.remote_addr + (wqe->length - *len));
	ohdr->u.tid_rdma.w_req.reth.rkey =
		cpu_to_be32(wqe->rdma_wr.rkey);
	ohdr->u.tid_rdma.w_req.reth.length = cpu_to_be32(*len);
	ohdr->u.tid_rdma.w_req.verbs_qp = cpu_to_be32(qp->remote_qpn);
	*bth1 &= ~RVT_QPN_MASK;
	*bth1 |= remote->qp;
	qp->s_state = TID_OP(WRITE_REQ);
	qp->s_flags |= HFI1_S_WAIT_TID_RESP;
	*bth2 |= IB_BTH_REQ_ACK;
	*len = 0;

	rcu_पढ़ो_unlock();
	वापस माप(ohdr->u.tid_rdma.w_req) / माप(u32);
पूर्ण

अटल u32 hfi1_compute_tid_rdma_flow_wt(काष्ठा rvt_qp *qp)
अणु
	/*
	 * Heuristic क्रम computing the RNR समयout when रुकोing on the flow
	 * queue. Rather than a computationaly expensive exact estimate of when
	 * a flow will be available, we assume that अगर a QP is at position N in
	 * the flow queue it has to रुको approximately (N + 1) * (number of
	 * segments between two sync poपूर्णांकs). The rationale क्रम this is that
	 * flows are released and recycled at each sync poपूर्णांक.
	 */
	वापस (MAX_TID_FLOW_PSN * qp->pmtu) >> TID_RDMA_SEGMENT_SHIFT;
पूर्ण

अटल u32 position_in_queue(काष्ठा hfi1_qp_priv *qpriv,
			     काष्ठा tid_queue *queue)
अणु
	वापस qpriv->tid_enqueue - queue->dequeue;
पूर्ण

/*
 * @qp: poपूर्णांकs to rvt_qp context.
 * @to_seg: desired RNR समयout in segments.
 * Return: index of the next highest समयout in the ib_hfi1_rnr_table[]
 */
अटल u32 hfi1_compute_tid_rnr_समयout(काष्ठा rvt_qp *qp, u32 to_seg)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	u64 समयout;
	u32 bytes_per_us;
	u8 i;

	bytes_per_us = active_egress_rate(qpriv->rcd->ppd) / 8;
	समयout = (to_seg * TID_RDMA_MAX_SEGMENT_SIZE) / bytes_per_us;
	/*
	 * Find the next highest value in the RNR table to the required
	 * समयout. This gives the responder some padding.
	 */
	क्रम (i = 1; i <= IB_AETH_CREDIT_MASK; i++)
		अगर (rvt_rnr_tbl_to_usec(i) >= समयout)
			वापस i;
	वापस 0;
पूर्ण

/*
 * Central place क्रम resource allocation at TID ग_लिखो responder,
 * is called from ग_लिखो_req and ग_लिखो_data पूर्णांकerrupt handlers as
 * well as the send thपढ़ो when a queued QP is scheduled क्रम
 * resource allocation.
 *
 * Iterates over (a) segments of a request and then (b) queued requests
 * themselves to allocate resources क्रम up to local->max_ग_लिखो
 * segments across multiple requests. Stop allocating when we
 * hit a sync poपूर्णांक, resume allocating after data packets at
 * sync poपूर्णांक have been received.
 *
 * Resource allocation and sending of responses is decoupled. The
 * request/segment which are being allocated and sent are as follows.
 * Resources are allocated क्रम:
 *     [request: qpriv->r_tid_alloc, segment: req->alloc_seg]
 * The send thपढ़ो sends:
 *     [request: qp->s_tail_ack_queue, segment:req->cur_seg]
 */
अटल व्योम hfi1_tid_ग_लिखो_alloc_resources(काष्ठा rvt_qp *qp, bool पूर्णांकr_ctx)
अणु
	काष्ठा tid_rdma_request *req;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा hfi1_ctxtdata *rcd = qpriv->rcd;
	काष्ठा tid_rdma_params *local = &qpriv->tid_rdma.local;
	काष्ठा rvt_ack_entry *e;
	u32 npkts, to_seg;
	bool last;
	पूर्णांक ret = 0;

	lockdep_निश्चित_held(&qp->s_lock);

	जबतक (1) अणु
		trace_hfi1_rsp_tid_ग_लिखो_alloc_res(qp, 0);
		trace_hfi1_tid_ग_लिखो_rsp_alloc_res(qp);
		/*
		 * Don't allocate more segments अगर a RNR NAK has alपढ़ोy been
		 * scheduled to aव्योम messing up qp->r_psn: the RNR NAK will
		 * be sent only when all allocated segments have been sent.
		 * However, अगर more segments are allocated beक्रमe that, TID RDMA
		 * WRITE RESP packets will be sent out क्रम these new segments
		 * beक्रमe the RNR NAK packet. When the requester receives the
		 * RNR NAK packet, it will restart with qp->s_last_psn + 1,
		 * which करोes not match qp->r_psn and will be dropped.
		 * Consequently, the requester will exhaust its retries and
		 * put the qp पूर्णांकo error state.
		 */
		अगर (qpriv->rnr_nak_state == TID_RNR_NAK_SEND)
			अवरोध;

		/* No requests left to process */
		अगर (qpriv->r_tid_alloc == qpriv->r_tid_head) अणु
			/* If all data has been received, clear the flow */
			अगर (qpriv->flow_state.index < RXE_NUM_TID_FLOWS &&
			    !qpriv->alloc_w_segs) अणु
				hfi1_kern_clear_hw_flow(rcd, qp);
				qpriv->s_flags &= ~HFI1_R_TID_SW_PSN;
			पूर्ण
			अवरोध;
		पूर्ण

		e = &qp->s_ack_queue[qpriv->r_tid_alloc];
		अगर (e->opcode != TID_OP(WRITE_REQ))
			जाओ next_req;
		req = ack_to_tid_req(e);
		trace_hfi1_tid_req_ग_लिखो_alloc_res(qp, 0, e->opcode, e->psn,
						   e->lpsn, req);
		/* Finished allocating क्रम all segments of this request */
		अगर (req->alloc_seg >= req->total_segs)
			जाओ next_req;

		/* Can allocate only a maximum of local->max_ग_लिखो क्रम a QP */
		अगर (qpriv->alloc_w_segs >= local->max_ग_लिखो)
			अवरोध;

		/* Don't allocate at a sync poपूर्णांक with data packets pending */
		अगर (qpriv->sync_pt && qpriv->alloc_w_segs)
			अवरोध;

		/* All data received at the sync poपूर्णांक, जारी */
		अगर (qpriv->sync_pt && !qpriv->alloc_w_segs) अणु
			hfi1_kern_clear_hw_flow(rcd, qp);
			qpriv->sync_pt = false;
			qpriv->s_flags &= ~HFI1_R_TID_SW_PSN;
		पूर्ण

		/* Allocate flow अगर we करोn't have one */
		अगर (qpriv->flow_state.index >= RXE_NUM_TID_FLOWS) अणु
			ret = hfi1_kern_setup_hw_flow(qpriv->rcd, qp);
			अगर (ret) अणु
				to_seg = hfi1_compute_tid_rdma_flow_wt(qp) *
					position_in_queue(qpriv,
							  &rcd->flow_queue);
				अवरोध;
			पूर्ण
		पूर्ण

		npkts = rvt_भाग_round_up_mtu(qp, req->seg_len);

		/*
		 * We are at a sync poपूर्णांक अगर we run out of KDETH PSN space.
		 * Last PSN of every generation is reserved क्रम RESYNC.
		 */
		अगर (qpriv->flow_state.psn + npkts > MAX_TID_FLOW_PSN - 1) अणु
			qpriv->sync_pt = true;
			अवरोध;
		पूर्ण

		/*
		 * If overtaking req->acked_tail, send an RNR NAK. Because the
		 * QP is not queued in this हाल, and the issue can only be
		 * caused by a delay in scheduling the second leg which we
		 * cannot estimate, we use a rather arbitrary RNR समयout of
		 * (MAX_FLOWS / 2) segments
		 */
		अगर (!CIRC_SPACE(req->setup_head, req->acked_tail,
				MAX_FLOWS)) अणु
			ret = -EAGAIN;
			to_seg = MAX_FLOWS >> 1;
			tid_rdma_trigger_ack(qp);
			अवरोध;
		पूर्ण

		/* Try to allocate rcv array / TID entries */
		ret = hfi1_kern_exp_rcv_setup(req, &req->ss, &last);
		अगर (ret == -EAGAIN)
			to_seg = position_in_queue(qpriv, &rcd->rarr_queue);
		अगर (ret)
			अवरोध;

		qpriv->alloc_w_segs++;
		req->alloc_seg++;
		जारी;
next_req:
		/* Begin processing the next request */
		अगर (++qpriv->r_tid_alloc >
		    rvt_size_atomic(ib_to_rvt(qp->ibqp.device)))
			qpriv->r_tid_alloc = 0;
	पूर्ण

	/*
	 * Schedule an RNR NAK to be sent अगर (a) flow or rcv array allocation
	 * has failed (b) we are called from the rcv handler पूर्णांकerrupt context
	 * (c) an RNR NAK has not alपढ़ोy been scheduled
	 */
	अगर (ret == -EAGAIN && पूर्णांकr_ctx && !qp->r_nak_state)
		जाओ send_rnr_nak;

	वापस;

send_rnr_nak:
	lockdep_निश्चित_held(&qp->r_lock);

	/* Set r_nak_state to prevent unrelated events from generating NAK's */
	qp->r_nak_state = hfi1_compute_tid_rnr_समयout(qp, to_seg) | IB_RNR_NAK;

	/* Pull back r_psn to the segment being RNR NAK'd */
	qp->r_psn = e->psn + req->alloc_seg;
	qp->r_ack_psn = qp->r_psn;
	/*
	 * Pull back r_head_ack_queue to the ack entry following the request
	 * being RNR NAK'd. This allows resources to be allocated to the request
	 * अगर the queued QP is scheduled.
	 */
	qp->r_head_ack_queue = qpriv->r_tid_alloc + 1;
	अगर (qp->r_head_ack_queue > rvt_size_atomic(ib_to_rvt(qp->ibqp.device)))
		qp->r_head_ack_queue = 0;
	qpriv->r_tid_head = qp->r_head_ack_queue;
	/*
	 * These send side fields are used in make_rc_ack(). They are set in
	 * hfi1_send_rc_ack() but must be set here beक्रमe dropping qp->s_lock
	 * क्रम consistency
	 */
	qp->s_nak_state = qp->r_nak_state;
	qp->s_ack_psn = qp->r_ack_psn;
	/*
	 * Clear the ACK PENDING flag to prevent unwanted ACK because we
	 * have modअगरied qp->s_ack_psn here.
	 */
	qp->s_flags &= ~(RVT_S_ACK_PENDING);

	trace_hfi1_rsp_tid_ग_लिखो_alloc_res(qp, qp->r_psn);
	/*
	 * qpriv->rnr_nak_state is used to determine when the scheduled RNR NAK
	 * has actually been sent. qp->s_flags RVT_S_ACK_PENDING bit cannot be
	 * used क्रम this because qp->s_lock is dropped beक्रमe calling
	 * hfi1_send_rc_ack() leading to inconsistency between the receive
	 * पूर्णांकerrupt handlers and the send thपढ़ो in make_rc_ack()
	 */
	qpriv->rnr_nak_state = TID_RNR_NAK_SEND;

	/*
	 * Schedule RNR NAK to be sent. RNR NAK's are scheduled from the receive
	 * पूर्णांकerrupt handlers but will be sent from the send engine behind any
	 * previous responses that may have been scheduled
	 */
	rc_defered_ack(rcd, qp);
पूर्ण

व्योम hfi1_rc_rcv_tid_rdma_ग_लिखो_req(काष्ठा hfi1_packet *packet)
अणु
	/* HANDLER FOR TID RDMA WRITE REQUEST packet (Responder side)*/

	/*
	 * 1. Verअगरy TID RDMA WRITE REQ as per IB_OPCODE_RC_RDMA_WRITE_FIRST
	 *    (see hfi1_rc_rcv())
	 *     - Don't allow 0-length requests.
	 * 2. Put TID RDMA WRITE REQ पूर्णांकo the response queueu (s_ack_queue)
	 *     - Setup काष्ठा tid_rdma_req with request info
	 *     - Prepare काष्ठा tid_rdma_flow array?
	 * 3. Set the qp->s_ack_state as state diagram in design करोc.
	 * 4. Set RVT_S_RESP_PENDING in s_flags.
	 * 5. Kick the send engine (hfi1_schedule_send())
	 */
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_ibport *ibp = to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	काष्ठा rvt_ack_entry *e;
	अचिन्हित दीर्घ flags;
	काष्ठा ib_reth *reth;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_rdma_request *req;
	u32 bth0, psn, len, rkey, num_segs;
	bool fecn;
	u8 next;
	u64 vaddr;
	पूर्णांक dअगरf;

	bth0 = be32_to_cpu(ohdr->bth[0]);
	अगर (hfi1_ruc_check_hdr(ibp, packet))
		वापस;

	fecn = process_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdr->bth[2]));
	trace_hfi1_rsp_rcv_tid_ग_लिखो_req(qp, psn);

	अगर (qp->state == IB_QPS_RTR && !(qp->r_flags & RVT_R_COMM_EST))
		rvt_comm_est(qp);

	अगर (unlikely(!(qp->qp_access_flags & IB_ACCESS_REMOTE_WRITE)))
		जाओ nack_inv;

	reth = &ohdr->u.tid_rdma.w_req.reth;
	vaddr = be64_to_cpu(reth->vaddr);
	len = be32_to_cpu(reth->length);

	num_segs = DIV_ROUND_UP(len, qpriv->tid_rdma.local.max_len);
	dअगरf = delta_psn(psn, qp->r_psn);
	अगर (unlikely(dअगरf)) अणु
		tid_rdma_rcv_err(packet, ohdr, qp, psn, dअगरf, fecn);
		वापस;
	पूर्ण

	/*
	 * The resent request which was previously RNR NAK'd is inserted at the
	 * location of the original request, which is one entry behind
	 * r_head_ack_queue
	 */
	अगर (qpriv->rnr_nak_state)
		qp->r_head_ack_queue = qp->r_head_ack_queue ?
			qp->r_head_ack_queue - 1 :
			rvt_size_atomic(ib_to_rvt(qp->ibqp.device));

	/* We've verअगरied the request, insert it पूर्णांकo the ack queue. */
	next = qp->r_head_ack_queue + 1;
	अगर (next > rvt_size_atomic(ib_to_rvt(qp->ibqp.device)))
		next = 0;
	spin_lock_irqsave(&qp->s_lock, flags);
	अगर (unlikely(next == qp->s_acked_ack_queue)) अणु
		अगर (!qp->s_ack_queue[next].sent)
			जाओ nack_inv_unlock;
		update_ack_queue(qp, next);
	पूर्ण
	e = &qp->s_ack_queue[qp->r_head_ack_queue];
	req = ack_to_tid_req(e);

	/* Bring previously RNR NAK'd request back to lअगरe */
	अगर (qpriv->rnr_nak_state) अणु
		qp->r_nak_state = 0;
		qp->s_nak_state = 0;
		qpriv->rnr_nak_state = TID_RNR_NAK_INIT;
		qp->r_psn = e->lpsn + 1;
		req->state = TID_REQUEST_INIT;
		जाओ update_head;
	पूर्ण

	release_rdma_sge_mr(e);

	/* The length needs to be in multiples of PAGE_SIZE */
	अगर (!len || len & ~PAGE_MASK)
		जाओ nack_inv_unlock;

	rkey = be32_to_cpu(reth->rkey);
	qp->r_len = len;

	अगर (e->opcode == TID_OP(WRITE_REQ) &&
	    (req->setup_head != req->clear_tail ||
	     req->clear_tail != req->acked_tail))
		जाओ nack_inv_unlock;

	अगर (unlikely(!rvt_rkey_ok(qp, &e->rdma_sge, qp->r_len, vaddr,
				  rkey, IB_ACCESS_REMOTE_WRITE)))
		जाओ nack_acc;

	qp->r_psn += num_segs - 1;

	e->opcode = (bth0 >> 24) & 0xff;
	e->psn = psn;
	e->lpsn = qp->r_psn;
	e->sent = 0;

	req->n_flows = min_t(u16, num_segs, qpriv->tid_rdma.local.max_ग_लिखो);
	req->state = TID_REQUEST_INIT;
	req->cur_seg = 0;
	req->comp_seg = 0;
	req->ack_seg = 0;
	req->alloc_seg = 0;
	req->isge = 0;
	req->seg_len = qpriv->tid_rdma.local.max_len;
	req->total_len = len;
	req->total_segs = num_segs;
	req->r_flow_psn = e->psn;
	req->ss.sge = e->rdma_sge;
	req->ss.num_sge = 1;

	req->flow_idx = req->setup_head;
	req->clear_tail = req->setup_head;
	req->acked_tail = req->setup_head;

	qp->r_state = e->opcode;
	qp->r_nak_state = 0;
	/*
	 * We need to increment the MSN here instead of when we
	 * finish sending the result since a duplicate request would
	 * increment it more than once.
	 */
	qp->r_msn++;
	qp->r_psn++;

	trace_hfi1_tid_req_rcv_ग_लिखो_req(qp, 0, e->opcode, e->psn, e->lpsn,
					 req);

	अगर (qpriv->r_tid_tail == HFI1_QP_WQE_INVALID) अणु
		qpriv->r_tid_tail = qp->r_head_ack_queue;
	पूर्ण अन्यथा अगर (qpriv->r_tid_tail == qpriv->r_tid_head) अणु
		काष्ठा tid_rdma_request *ptr;

		e = &qp->s_ack_queue[qpriv->r_tid_tail];
		ptr = ack_to_tid_req(e);

		अगर (e->opcode != TID_OP(WRITE_REQ) ||
		    ptr->comp_seg == ptr->total_segs) अणु
			अगर (qpriv->r_tid_tail == qpriv->r_tid_ack)
				qpriv->r_tid_ack = qp->r_head_ack_queue;
			qpriv->r_tid_tail = qp->r_head_ack_queue;
		पूर्ण
	पूर्ण
update_head:
	qp->r_head_ack_queue = next;
	qpriv->r_tid_head = qp->r_head_ack_queue;

	hfi1_tid_ग_लिखो_alloc_resources(qp, true);
	trace_hfi1_tid_ग_लिखो_rsp_rcv_req(qp);

	/* Schedule the send tasklet. */
	qp->s_flags |= RVT_S_RESP_PENDING;
	अगर (fecn)
		qp->s_flags |= RVT_S_ECN;
	hfi1_schedule_send(qp);

	spin_unlock_irqrestore(&qp->s_lock, flags);
	वापस;

nack_inv_unlock:
	spin_unlock_irqrestore(&qp->s_lock, flags);
nack_inv:
	rvt_rc_error(qp, IB_WC_LOC_QP_OP_ERR);
	qp->r_nak_state = IB_NAK_INVALID_REQUEST;
	qp->r_ack_psn = qp->r_psn;
	/* Queue NAK क्रम later */
	rc_defered_ack(rcd, qp);
	वापस;
nack_acc:
	spin_unlock_irqrestore(&qp->s_lock, flags);
	rvt_rc_error(qp, IB_WC_LOC_PROT_ERR);
	qp->r_nak_state = IB_NAK_REMOTE_ACCESS_ERROR;
	qp->r_ack_psn = qp->r_psn;
पूर्ण

u32 hfi1_build_tid_rdma_ग_लिखो_resp(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e,
				   काष्ठा ib_other_headers *ohdr, u32 *bth1,
				   u32 bth2, u32 *len,
				   काष्ठा rvt_sge_state **ss)
अणु
	काष्ठा hfi1_ack_priv *epriv = e->priv;
	काष्ठा tid_rdma_request *req = &epriv->tid_req;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_rdma_flow *flow = शून्य;
	u32 resp_len = 0, hdwords = 0;
	व्योम *resp_addr = शून्य;
	काष्ठा tid_rdma_params *remote;

	trace_hfi1_tid_req_build_ग_लिखो_resp(qp, 0, e->opcode, e->psn, e->lpsn,
					    req);
	trace_hfi1_tid_ग_लिखो_rsp_build_resp(qp);
	trace_hfi1_rsp_build_tid_ग_लिखो_resp(qp, bth2);
	flow = &req->flows[req->flow_idx];
	चयन (req->state) अणु
	शेष:
		/*
		 * Try to allocate resources here in हाल QP was queued and was
		 * later scheduled when resources became available
		 */
		hfi1_tid_ग_लिखो_alloc_resources(qp, false);

		/* We've alपढ़ोy sent everything which is पढ़ोy */
		अगर (req->cur_seg >= req->alloc_seg)
			जाओ करोne;

		/*
		 * Resources can be asचिन्हित but responses cannot be sent in
		 * rnr_nak state, till the resent request is received
		 */
		अगर (qpriv->rnr_nak_state == TID_RNR_NAK_SENT)
			जाओ करोne;

		req->state = TID_REQUEST_ACTIVE;
		trace_hfi1_tid_flow_build_ग_लिखो_resp(qp, req->flow_idx, flow);
		req->flow_idx = CIRC_NEXT(req->flow_idx, MAX_FLOWS);
		hfi1_add_tid_reap_समयr(qp);
		अवरोध;

	हाल TID_REQUEST_RESEND_ACTIVE:
	हाल TID_REQUEST_RESEND:
		trace_hfi1_tid_flow_build_ग_लिखो_resp(qp, req->flow_idx, flow);
		req->flow_idx = CIRC_NEXT(req->flow_idx, MAX_FLOWS);
		अगर (!CIRC_CNT(req->setup_head, req->flow_idx, MAX_FLOWS))
			req->state = TID_REQUEST_ACTIVE;

		hfi1_mod_tid_reap_समयr(qp);
		अवरोध;
	पूर्ण
	flow->flow_state.resp_ib_psn = bth2;
	resp_addr = (व्योम *)flow->tid_entry;
	resp_len = माप(*flow->tid_entry) * flow->tidcnt;
	req->cur_seg++;

	स_रखो(&ohdr->u.tid_rdma.w_rsp, 0, माप(ohdr->u.tid_rdma.w_rsp));
	epriv->ss.sge.vaddr = resp_addr;
	epriv->ss.sge.sge_length = resp_len;
	epriv->ss.sge.length = epriv->ss.sge.sge_length;
	/*
	 * We can safely zero these out. Since the first SGE covers the
	 * entire packet, nothing अन्यथा should even look at the MR.
	 */
	epriv->ss.sge.mr = शून्य;
	epriv->ss.sge.m = 0;
	epriv->ss.sge.n = 0;

	epriv->ss.sg_list = शून्य;
	epriv->ss.total_len = epriv->ss.sge.sge_length;
	epriv->ss.num_sge = 1;

	*ss = &epriv->ss;
	*len = epriv->ss.total_len;

	/* Conकाष्ठा the TID RDMA WRITE RESP packet header */
	rcu_पढ़ो_lock();
	remote = rcu_dereference(qpriv->tid_rdma.remote);

	KDETH_RESET(ohdr->u.tid_rdma.w_rsp.kdeth0, KVER, 0x1);
	KDETH_RESET(ohdr->u.tid_rdma.w_rsp.kdeth1, JKEY, remote->jkey);
	ohdr->u.tid_rdma.w_rsp.aeth = rvt_compute_aeth(qp);
	ohdr->u.tid_rdma.w_rsp.tid_flow_psn =
		cpu_to_be32((flow->flow_state.generation <<
			     HFI1_KDETH_BTH_SEQ_SHIFT) |
			    (flow->flow_state.spsn &
			     HFI1_KDETH_BTH_SEQ_MASK));
	ohdr->u.tid_rdma.w_rsp.tid_flow_qp =
		cpu_to_be32(qpriv->tid_rdma.local.qp |
			    ((flow->idx & TID_RDMA_DESTQP_FLOW_MASK) <<
			     TID_RDMA_DESTQP_FLOW_SHIFT) |
			    qpriv->rcd->ctxt);
	ohdr->u.tid_rdma.w_rsp.verbs_qp = cpu_to_be32(qp->remote_qpn);
	*bth1 = remote->qp;
	rcu_पढ़ो_unlock();
	hdwords = माप(ohdr->u.tid_rdma.w_rsp) / माप(u32);
	qpriv->pending_tid_w_segs++;
करोne:
	वापस hdwords;
पूर्ण

अटल व्योम hfi1_add_tid_reap_समयr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;

	lockdep_निश्चित_held(&qp->s_lock);
	अगर (!(qpriv->s_flags & HFI1_R_TID_RSC_TIMER)) अणु
		qpriv->s_flags |= HFI1_R_TID_RSC_TIMER;
		qpriv->s_tid_समयr.expires = jअगरfies +
			qpriv->tid_समयr_समयout_jअगरfies;
		add_समयr(&qpriv->s_tid_समयr);
	पूर्ण
पूर्ण

अटल व्योम hfi1_mod_tid_reap_समयr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;

	lockdep_निश्चित_held(&qp->s_lock);
	qpriv->s_flags |= HFI1_R_TID_RSC_TIMER;
	mod_समयr(&qpriv->s_tid_समयr, jअगरfies +
		  qpriv->tid_समयr_समयout_jअगरfies);
पूर्ण

अटल पूर्णांक hfi1_stop_tid_reap_समयr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	पूर्णांक rval = 0;

	lockdep_निश्चित_held(&qp->s_lock);
	अगर (qpriv->s_flags & HFI1_R_TID_RSC_TIMER) अणु
		rval = del_समयr(&qpriv->s_tid_समयr);
		qpriv->s_flags &= ~HFI1_R_TID_RSC_TIMER;
	पूर्ण
	वापस rval;
पूर्ण

व्योम hfi1_del_tid_reap_समयr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;

	del_समयr_sync(&qpriv->s_tid_समयr);
	qpriv->s_flags &= ~HFI1_R_TID_RSC_TIMER;
पूर्ण

अटल व्योम hfi1_tid_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा hfi1_qp_priv *qpriv = from_समयr(qpriv, t, s_tid_समयr);
	काष्ठा rvt_qp *qp = qpriv->owner;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(qp->ibqp.device);
	अचिन्हित दीर्घ flags;
	u32 i;

	spin_lock_irqsave(&qp->r_lock, flags);
	spin_lock(&qp->s_lock);
	अगर (qpriv->s_flags & HFI1_R_TID_RSC_TIMER) अणु
		dd_dev_warn(dd_from_ibdev(qp->ibqp.device), "[QP%u] %s %d\n",
			    qp->ibqp.qp_num, __func__, __LINE__);
		trace_hfi1_msg_tid_समयout(/* msg */
			qp, "resource timeout = ",
			(u64)qpriv->tid_समयr_समयout_jअगरfies);
		hfi1_stop_tid_reap_समयr(qp);
		/*
		 * Go though the entire ack queue and clear any outstanding
		 * HW flow and RcvArray resources.
		 */
		hfi1_kern_clear_hw_flow(qpriv->rcd, qp);
		क्रम (i = 0; i < rvt_max_atomic(rdi); i++) अणु
			काष्ठा tid_rdma_request *req =
				ack_to_tid_req(&qp->s_ack_queue[i]);

			hfi1_kern_exp_rcv_clear_all(req);
		पूर्ण
		spin_unlock(&qp->s_lock);
		अगर (qp->ibqp.event_handler) अणु
			काष्ठा ib_event ev;

			ev.device = qp->ibqp.device;
			ev.element.qp = &qp->ibqp;
			ev.event = IB_EVENT_QP_FATAL;
			qp->ibqp.event_handler(&ev, qp->ibqp.qp_context);
		पूर्ण
		rvt_rc_error(qp, IB_WC_RESP_TIMEOUT_ERR);
		जाओ unlock_r_lock;
	पूर्ण
	spin_unlock(&qp->s_lock);
unlock_r_lock:
	spin_unlock_irqrestore(&qp->r_lock, flags);
पूर्ण

व्योम hfi1_rc_rcv_tid_rdma_ग_लिखो_resp(काष्ठा hfi1_packet *packet)
अणु
	/* HANDLER FOR TID RDMA WRITE RESPONSE packet (Requestor side */

	/*
	 * 1. Find matching SWQE
	 * 2. Check that TIDENTRY array has enough space क्रम a complete
	 *    segment. If not, put QP in error state.
	 * 3. Save response data in काष्ठा tid_rdma_req and काष्ठा tid_rdma_flow
	 * 4. Remove HFI1_S_WAIT_TID_RESP from s_flags.
	 * 5. Set qp->s_state
	 * 6. Kick the send engine (hfi1_schedule_send())
	 */
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा hfi1_ctxtdata *rcd = packet->rcd;
	काष्ठा rvt_swqe *wqe;
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;
	क्रमागत ib_wc_status status;
	u32 opcode, aeth, psn, flow_psn, i, tidlen = 0, pktlen;
	bool fecn;
	अचिन्हित दीर्घ flags;

	fecn = process_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdr->bth[2]));
	aeth = be32_to_cpu(ohdr->u.tid_rdma.w_rsp.aeth);
	opcode = (be32_to_cpu(ohdr->bth[0]) >> 24) & 0xff;

	spin_lock_irqsave(&qp->s_lock, flags);

	/* Ignore invalid responses */
	अगर (cmp_psn(psn, qp->s_next_psn) >= 0)
		जाओ ack_करोne;

	/* Ignore duplicate responses. */
	अगर (unlikely(cmp_psn(psn, qp->s_last_psn) <= 0))
		जाओ ack_करोne;

	अगर (unlikely(qp->s_acked == qp->s_tail))
		जाओ ack_करोne;

	/*
	 * If we are रुकोing क्रम a particular packet sequence number
	 * due to a request being resent, check क्रम it. Otherwise,
	 * ensure that we haven't missed anything.
	 */
	अगर (qp->r_flags & RVT_R_RDMAR_SEQ) अणु
		अगर (cmp_psn(psn, qp->s_last_psn + 1) != 0)
			जाओ ack_करोne;
		qp->r_flags &= ~RVT_R_RDMAR_SEQ;
	पूर्ण

	wqe = rvt_get_swqe_ptr(qp, qpriv->s_tid_cur);
	अगर (unlikely(wqe->wr.opcode != IB_WR_TID_RDMA_WRITE))
		जाओ ack_op_err;

	req = wqe_to_tid_req(wqe);
	/*
	 * If we've lost ACKs and our acked_tail poपूर्णांकer is too far
	 * behind, करोn't overग_लिखो segments. Just drop the packet and
	 * let the reliability protocol take care of it.
	 */
	अगर (!CIRC_SPACE(req->setup_head, req->acked_tail, MAX_FLOWS))
		जाओ ack_करोne;

	/*
	 * The call to करो_rc_ack() should be last in the chain of
	 * packet checks because it will end up updating the QP state.
	 * Thereक्रमe, anything that would prevent the packet from
	 * being accepted as a successful response should be prior
	 * to it.
	 */
	अगर (!करो_rc_ack(qp, aeth, psn, opcode, 0, rcd))
		जाओ ack_करोne;

	trace_hfi1_ack(qp, psn);

	flow = &req->flows[req->setup_head];
	flow->pkt = 0;
	flow->tid_idx = 0;
	flow->tid_offset = 0;
	flow->sent = 0;
	flow->resync_npkts = 0;
	flow->tid_qpn = be32_to_cpu(ohdr->u.tid_rdma.w_rsp.tid_flow_qp);
	flow->idx = (flow->tid_qpn >> TID_RDMA_DESTQP_FLOW_SHIFT) &
		TID_RDMA_DESTQP_FLOW_MASK;
	flow_psn = mask_psn(be32_to_cpu(ohdr->u.tid_rdma.w_rsp.tid_flow_psn));
	flow->flow_state.generation = flow_psn >> HFI1_KDETH_BTH_SEQ_SHIFT;
	flow->flow_state.spsn = flow_psn & HFI1_KDETH_BTH_SEQ_MASK;
	flow->flow_state.resp_ib_psn = psn;
	flow->length = min_t(u32, req->seg_len,
			     (wqe->length - (req->comp_seg * req->seg_len)));

	flow->npkts = rvt_भाग_round_up_mtu(qp, flow->length);
	flow->flow_state.lpsn = flow->flow_state.spsn +
		flow->npkts - 1;
	/* payload length = packet length - (header length + ICRC length) */
	pktlen = packet->tlen - (packet->hlen + 4);
	अगर (pktlen > माप(flow->tid_entry)) अणु
		status = IB_WC_LOC_LEN_ERR;
		जाओ ack_err;
	पूर्ण
	स_नकल(flow->tid_entry, packet->ebuf, pktlen);
	flow->tidcnt = pktlen / माप(*flow->tid_entry);
	trace_hfi1_tid_flow_rcv_ग_लिखो_resp(qp, req->setup_head, flow);

	req->comp_seg++;
	trace_hfi1_tid_ग_लिखो_sender_rcv_resp(qp, 0);
	/*
	 * Walk the TID_ENTRY list to make sure we have enough space क्रम a
	 * complete segment.
	 */
	क्रम (i = 0; i < flow->tidcnt; i++) अणु
		trace_hfi1_tid_entry_rcv_ग_लिखो_resp(/* entry */
			qp, i, flow->tid_entry[i]);
		अगर (!EXP_TID_GET(flow->tid_entry[i], LEN)) अणु
			status = IB_WC_LOC_LEN_ERR;
			जाओ ack_err;
		पूर्ण
		tidlen += EXP_TID_GET(flow->tid_entry[i], LEN);
	पूर्ण
	अगर (tidlen * PAGE_SIZE < flow->length) अणु
		status = IB_WC_LOC_LEN_ERR;
		जाओ ack_err;
	पूर्ण

	trace_hfi1_tid_req_rcv_ग_लिखो_resp(qp, 0, wqe->wr.opcode, wqe->psn,
					  wqe->lpsn, req);
	/*
	 * If this is the first response क्रम this request, set the initial
	 * flow index to the current flow.
	 */
	अगर (!cmp_psn(psn, wqe->psn)) अणु
		req->r_last_acked = mask_psn(wqe->psn - 1);
		/* Set acked flow index to head index */
		req->acked_tail = req->setup_head;
	पूर्ण

	/* advance circular buffer head */
	req->setup_head = CIRC_NEXT(req->setup_head, MAX_FLOWS);
	req->state = TID_REQUEST_ACTIVE;

	/*
	 * If all responses क्रम this TID RDMA WRITE request have been received
	 * advance the poपूर्णांकer to the next one.
	 * Since TID RDMA requests could be mixed in with regular IB requests,
	 * they might not appear sequentially in the queue. Thereक्रमe, the
	 * next request needs to be "found".
	 */
	अगर (qpriv->s_tid_cur != qpriv->s_tid_head &&
	    req->comp_seg == req->total_segs) अणु
		क्रम (i = qpriv->s_tid_cur + 1; ; i++) अणु
			अगर (i == qp->s_size)
				i = 0;
			wqe = rvt_get_swqe_ptr(qp, i);
			अगर (i == qpriv->s_tid_head)
				अवरोध;
			अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE)
				अवरोध;
		पूर्ण
		qpriv->s_tid_cur = i;
	पूर्ण
	qp->s_flags &= ~HFI1_S_WAIT_TID_RESP;
	hfi1_schedule_tid_send(qp);
	जाओ ack_करोne;

ack_op_err:
	status = IB_WC_LOC_QP_OP_ERR;
ack_err:
	rvt_error_qp(qp, status);
ack_करोne:
	अगर (fecn)
		qp->s_flags |= RVT_S_ECN;
	spin_unlock_irqrestore(&qp->s_lock, flags);
पूर्ण

bool hfi1_build_tid_rdma_packet(काष्ठा rvt_swqe *wqe,
				काष्ठा ib_other_headers *ohdr,
				u32 *bth1, u32 *bth2, u32 *len)
अणु
	काष्ठा tid_rdma_request *req = wqe_to_tid_req(wqe);
	काष्ठा tid_rdma_flow *flow = &req->flows[req->clear_tail];
	काष्ठा tid_rdma_params *remote;
	काष्ठा rvt_qp *qp = req->qp;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	u32 tidentry = flow->tid_entry[flow->tid_idx];
	u32 tidlen = EXP_TID_GET(tidentry, LEN) << PAGE_SHIFT;
	काष्ठा tid_rdma_ग_लिखो_data *wd = &ohdr->u.tid_rdma.w_data;
	u32 next_offset, om = KDETH_OM_LARGE;
	bool last_pkt;

	अगर (!tidlen) अणु
		hfi1_trdma_send_complete(qp, wqe, IB_WC_REM_INV_RD_REQ_ERR);
		rvt_error_qp(qp, IB_WC_REM_INV_RD_REQ_ERR);
	पूर्ण

	*len = min_t(u32, qp->pmtu, tidlen - flow->tid_offset);
	flow->sent += *len;
	next_offset = flow->tid_offset + *len;
	last_pkt = (flow->tid_idx == (flow->tidcnt - 1) &&
		    next_offset >= tidlen) || (flow->sent >= flow->length);
	trace_hfi1_tid_entry_build_ग_लिखो_data(qp, flow->tid_idx, tidentry);
	trace_hfi1_tid_flow_build_ग_लिखो_data(qp, req->clear_tail, flow);

	rcu_पढ़ो_lock();
	remote = rcu_dereference(qpriv->tid_rdma.remote);
	KDETH_RESET(wd->kdeth0, KVER, 0x1);
	KDETH_SET(wd->kdeth0, SH, !last_pkt);
	KDETH_SET(wd->kdeth0, INTR, !!(!last_pkt && remote->urg));
	KDETH_SET(wd->kdeth0, TIDCTRL, EXP_TID_GET(tidentry, CTRL));
	KDETH_SET(wd->kdeth0, TID, EXP_TID_GET(tidentry, IDX));
	KDETH_SET(wd->kdeth0, OM, om == KDETH_OM_LARGE);
	KDETH_SET(wd->kdeth0, OFFSET, flow->tid_offset / om);
	KDETH_RESET(wd->kdeth1, JKEY, remote->jkey);
	wd->verbs_qp = cpu_to_be32(qp->remote_qpn);
	rcu_पढ़ो_unlock();

	*bth1 = flow->tid_qpn;
	*bth2 = mask_psn(((flow->flow_state.spsn + flow->pkt++) &
			 HFI1_KDETH_BTH_SEQ_MASK) |
			 (flow->flow_state.generation <<
			  HFI1_KDETH_BTH_SEQ_SHIFT));
	अगर (last_pkt) अणु
		/* PSNs are zero-based, so +1 to count number of packets */
		अगर (flow->flow_state.lpsn + 1 +
		    rvt_भाग_round_up_mtu(qp, req->seg_len) >
		    MAX_TID_FLOW_PSN)
			req->state = TID_REQUEST_SYNC;
		*bth2 |= IB_BTH_REQ_ACK;
	पूर्ण

	अगर (next_offset >= tidlen) अणु
		flow->tid_offset = 0;
		flow->tid_idx++;
	पूर्ण अन्यथा अणु
		flow->tid_offset = next_offset;
	पूर्ण
	वापस last_pkt;
पूर्ण

व्योम hfi1_rc_rcv_tid_rdma_ग_लिखो_data(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_ctxtdata *rcd = priv->rcd;
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	काष्ठा rvt_ack_entry *e;
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;
	काष्ठा hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	अचिन्हित दीर्घ flags;
	u32 psn, next;
	u8 opcode;
	bool fecn;

	fecn = process_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdr->bth[2]));
	opcode = (be32_to_cpu(ohdr->bth[0]) >> 24) & 0xff;

	/*
	 * All error handling should be करोne by now. If we are here, the packet
	 * is either good or been accepted by the error handler.
	 */
	spin_lock_irqsave(&qp->s_lock, flags);
	e = &qp->s_ack_queue[priv->r_tid_tail];
	req = ack_to_tid_req(e);
	flow = &req->flows[req->clear_tail];
	अगर (cmp_psn(psn, full_flow_psn(flow, flow->flow_state.lpsn))) अणु
		update_r_next_psn_fecn(packet, priv, rcd, flow, fecn);

		अगर (cmp_psn(psn, flow->flow_state.r_next_psn))
			जाओ send_nak;

		flow->flow_state.r_next_psn = mask_psn(psn + 1);
		/*
		 * Copy the payload to destination buffer अगर this packet is
		 * delivered as an eager packet due to RSM rule and FECN.
		 * The RSM rule selects FECN bit in BTH and SH bit in
		 * KDETH header and thereक्रमe will not match the last
		 * packet of each segment that has SH bit cleared.
		 */
		अगर (fecn && packet->etype == RHF_RCV_TYPE_EAGER) अणु
			काष्ठा rvt_sge_state ss;
			u32 len;
			u32 tlen = packet->tlen;
			u16 hdrsize = packet->hlen;
			u8 pad = packet->pad;
			u8 extra_bytes = pad + packet->extra_byte +
				(SIZE_OF_CRC << 2);
			u32 pmtu = qp->pmtu;

			अगर (unlikely(tlen != (hdrsize + pmtu + extra_bytes)))
				जाओ send_nak;
			len = req->comp_seg * req->seg_len;
			len += delta_psn(psn,
				full_flow_psn(flow, flow->flow_state.spsn)) *
				pmtu;
			अगर (unlikely(req->total_len - len < pmtu))
				जाओ send_nak;

			/*
			 * The e->rdma_sge field is set when TID RDMA WRITE REQ
			 * is first received and is never modअगरied thereafter.
			 */
			ss.sge = e->rdma_sge;
			ss.sg_list = शून्य;
			ss.num_sge = 1;
			ss.total_len = req->total_len;
			rvt_skip_sge(&ss, len, false);
			rvt_copy_sge(qp, &ss, packet->payload, pmtu, false,
				     false);
			/* Raise the sw sequence check flag क्रम next packet */
			priv->r_next_psn_kdeth = mask_psn(psn + 1);
			priv->s_flags |= HFI1_R_TID_SW_PSN;
		पूर्ण
		जाओ निकास;
	पूर्ण
	flow->flow_state.r_next_psn = mask_psn(psn + 1);
	hfi1_kern_exp_rcv_clear(req);
	priv->alloc_w_segs--;
	rcd->flows[flow->idx].psn = psn & HFI1_KDETH_BTH_SEQ_MASK;
	req->comp_seg++;
	priv->s_nak_state = 0;

	/*
	 * Release the flow अगर one of the following conditions has been met:
	 *  - The request has reached a sync poपूर्णांक AND all outstanding
	 *    segments have been completed, or
	 *  - The entire request is complete and there are no more requests
	 *    (of any kind) in the queue.
	 */
	trace_hfi1_rsp_rcv_tid_ग_लिखो_data(qp, psn);
	trace_hfi1_tid_req_rcv_ग_लिखो_data(qp, 0, e->opcode, e->psn, e->lpsn,
					  req);
	trace_hfi1_tid_ग_लिखो_rsp_rcv_data(qp);
	validate_r_tid_ack(priv);

	अगर (opcode == TID_OP(WRITE_DATA_LAST)) अणु
		release_rdma_sge_mr(e);
		क्रम (next = priv->r_tid_tail + 1; ; next++) अणु
			अगर (next > rvt_size_atomic(&dev->rdi))
				next = 0;
			अगर (next == priv->r_tid_head)
				अवरोध;
			e = &qp->s_ack_queue[next];
			अगर (e->opcode == TID_OP(WRITE_REQ))
				अवरोध;
		पूर्ण
		priv->r_tid_tail = next;
		अगर (++qp->s_acked_ack_queue > rvt_size_atomic(&dev->rdi))
			qp->s_acked_ack_queue = 0;
	पूर्ण

	hfi1_tid_ग_लिखो_alloc_resources(qp, true);

	/*
	 * If we need to generate more responses, schedule the
	 * send engine.
	 */
	अगर (req->cur_seg < req->total_segs ||
	    qp->s_tail_ack_queue != qp->r_head_ack_queue) अणु
		qp->s_flags |= RVT_S_RESP_PENDING;
		hfi1_schedule_send(qp);
	पूर्ण

	priv->pending_tid_w_segs--;
	अगर (priv->s_flags & HFI1_R_TID_RSC_TIMER) अणु
		अगर (priv->pending_tid_w_segs)
			hfi1_mod_tid_reap_समयr(req->qp);
		अन्यथा
			hfi1_stop_tid_reap_समयr(req->qp);
	पूर्ण

करोne:
	tid_rdma_schedule_ack(qp);
निकास:
	priv->r_next_psn_kdeth = flow->flow_state.r_next_psn;
	अगर (fecn)
		qp->s_flags |= RVT_S_ECN;
	spin_unlock_irqrestore(&qp->s_lock, flags);
	वापस;

send_nak:
	अगर (!priv->s_nak_state) अणु
		priv->s_nak_state = IB_NAK_PSN_ERROR;
		priv->s_nak_psn = flow->flow_state.r_next_psn;
		tid_rdma_trigger_ack(qp);
	पूर्ण
	जाओ करोne;
पूर्ण

अटल bool hfi1_tid_rdma_is_resync_psn(u32 psn)
अणु
	वापस (bool)((psn & HFI1_KDETH_BTH_SEQ_MASK) ==
		      HFI1_KDETH_BTH_SEQ_MASK);
पूर्ण

u32 hfi1_build_tid_rdma_ग_लिखो_ack(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e,
				  काष्ठा ib_other_headers *ohdr, u16 अगरlow,
				  u32 *bth1, u32 *bth2)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_flow_state *fs = &qpriv->flow_state;
	काष्ठा tid_rdma_request *req = ack_to_tid_req(e);
	काष्ठा tid_rdma_flow *flow = &req->flows[अगरlow];
	काष्ठा tid_rdma_params *remote;

	rcu_पढ़ो_lock();
	remote = rcu_dereference(qpriv->tid_rdma.remote);
	KDETH_RESET(ohdr->u.tid_rdma.ack.kdeth1, JKEY, remote->jkey);
	ohdr->u.tid_rdma.ack.verbs_qp = cpu_to_be32(qp->remote_qpn);
	*bth1 = remote->qp;
	rcu_पढ़ो_unlock();

	अगर (qpriv->resync) अणु
		*bth2 = mask_psn((fs->generation <<
				  HFI1_KDETH_BTH_SEQ_SHIFT) - 1);
		ohdr->u.tid_rdma.ack.aeth = rvt_compute_aeth(qp);
	पूर्ण अन्यथा अगर (qpriv->s_nak_state) अणु
		*bth2 = mask_psn(qpriv->s_nak_psn);
		ohdr->u.tid_rdma.ack.aeth =
			cpu_to_be32((qp->r_msn & IB_MSN_MASK) |
				    (qpriv->s_nak_state <<
				     IB_AETH_CREDIT_SHIFT));
	पूर्ण अन्यथा अणु
		*bth2 = full_flow_psn(flow, flow->flow_state.lpsn);
		ohdr->u.tid_rdma.ack.aeth = rvt_compute_aeth(qp);
	पूर्ण
	KDETH_RESET(ohdr->u.tid_rdma.ack.kdeth0, KVER, 0x1);
	ohdr->u.tid_rdma.ack.tid_flow_qp =
		cpu_to_be32(qpriv->tid_rdma.local.qp |
			    ((flow->idx & TID_RDMA_DESTQP_FLOW_MASK) <<
			     TID_RDMA_DESTQP_FLOW_SHIFT) |
			    qpriv->rcd->ctxt);

	ohdr->u.tid_rdma.ack.tid_flow_psn = 0;
	ohdr->u.tid_rdma.ack.verbs_psn =
		cpu_to_be32(flow->flow_state.resp_ib_psn);

	अगर (qpriv->resync) अणु
		/*
		 * If the PSN beक्रमe the current expect KDETH PSN is the
		 * RESYNC PSN, then we never received a good TID RDMA WRITE
		 * DATA packet after a previous RESYNC.
		 * In this हाल, the next expected KDETH PSN stays the same.
		 */
		अगर (hfi1_tid_rdma_is_resync_psn(qpriv->r_next_psn_kdeth - 1)) अणु
			ohdr->u.tid_rdma.ack.tid_flow_psn =
				cpu_to_be32(qpriv->r_next_psn_kdeth_save);
		पूर्ण अन्यथा अणु
			/*
			 * Because the KDETH PSNs jump during a RESYNC, it's
			 * not possible to infer (or compute) the previous value
			 * of r_next_psn_kdeth in the हाल of back-to-back
			 * RESYNC packets. Thereक्रमe, we save it.
			 */
			qpriv->r_next_psn_kdeth_save =
				qpriv->r_next_psn_kdeth - 1;
			ohdr->u.tid_rdma.ack.tid_flow_psn =
				cpu_to_be32(qpriv->r_next_psn_kdeth_save);
			qpriv->r_next_psn_kdeth = mask_psn(*bth2 + 1);
		पूर्ण
		qpriv->resync = false;
	पूर्ण

	वापस माप(ohdr->u.tid_rdma.ack) / माप(u32);
पूर्ण

व्योम hfi1_rc_rcv_tid_rdma_ack(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा rvt_swqe *wqe;
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;
	u32 aeth, psn, req_psn, ack_psn, flpsn, resync_psn, ack_kpsn;
	अचिन्हित दीर्घ flags;
	u16 fidx;

	trace_hfi1_tid_ग_लिखो_sender_rcv_tid_ack(qp, 0);
	process_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdr->bth[2]));
	aeth = be32_to_cpu(ohdr->u.tid_rdma.ack.aeth);
	req_psn = mask_psn(be32_to_cpu(ohdr->u.tid_rdma.ack.verbs_psn));
	resync_psn = mask_psn(be32_to_cpu(ohdr->u.tid_rdma.ack.tid_flow_psn));

	spin_lock_irqsave(&qp->s_lock, flags);
	trace_hfi1_rcv_tid_ack(qp, aeth, psn, req_psn, resync_psn);

	/* If we are रुकोing क्रम an ACK to RESYNC, drop any other packets */
	अगर ((qp->s_flags & HFI1_S_WAIT_HALT) &&
	    cmp_psn(psn, qpriv->s_resync_psn))
		जाओ ack_op_err;

	ack_psn = req_psn;
	अगर (hfi1_tid_rdma_is_resync_psn(psn))
		ack_kpsn = resync_psn;
	अन्यथा
		ack_kpsn = psn;
	अगर (aeth >> 29) अणु
		ack_psn--;
		ack_kpsn--;
	पूर्ण

	अगर (unlikely(qp->s_acked == qp->s_tail))
		जाओ ack_op_err;

	wqe = rvt_get_swqe_ptr(qp, qp->s_acked);

	अगर (wqe->wr.opcode != IB_WR_TID_RDMA_WRITE)
		जाओ ack_op_err;

	req = wqe_to_tid_req(wqe);
	trace_hfi1_tid_req_rcv_tid_ack(qp, 0, wqe->wr.opcode, wqe->psn,
				       wqe->lpsn, req);
	flow = &req->flows[req->acked_tail];
	trace_hfi1_tid_flow_rcv_tid_ack(qp, req->acked_tail, flow);

	/* Drop stale ACK/NAK */
	अगर (cmp_psn(psn, full_flow_psn(flow, flow->flow_state.spsn)) < 0 ||
	    cmp_psn(req_psn, flow->flow_state.resp_ib_psn) < 0)
		जाओ ack_op_err;

	जबतक (cmp_psn(ack_kpsn,
		       full_flow_psn(flow, flow->flow_state.lpsn)) >= 0 &&
	       req->ack_seg < req->cur_seg) अणु
		req->ack_seg++;
		/* advance acked segment poपूर्णांकer */
		req->acked_tail = CIRC_NEXT(req->acked_tail, MAX_FLOWS);
		req->r_last_acked = flow->flow_state.resp_ib_psn;
		trace_hfi1_tid_req_rcv_tid_ack(qp, 0, wqe->wr.opcode, wqe->psn,
					       wqe->lpsn, req);
		अगर (req->ack_seg == req->total_segs) अणु
			req->state = TID_REQUEST_COMPLETE;
			wqe = करो_rc_completion(qp, wqe,
					       to_iport(qp->ibqp.device,
							qp->port_num));
			trace_hfi1_sender_rcv_tid_ack(qp);
			atomic_dec(&qpriv->n_tid_requests);
			अगर (qp->s_acked == qp->s_tail)
				अवरोध;
			अगर (wqe->wr.opcode != IB_WR_TID_RDMA_WRITE)
				अवरोध;
			req = wqe_to_tid_req(wqe);
		पूर्ण
		flow = &req->flows[req->acked_tail];
		trace_hfi1_tid_flow_rcv_tid_ack(qp, req->acked_tail, flow);
	पूर्ण

	trace_hfi1_tid_req_rcv_tid_ack(qp, 0, wqe->wr.opcode, wqe->psn,
				       wqe->lpsn, req);
	चयन (aeth >> 29) अणु
	हाल 0:         /* ACK */
		अगर (qpriv->s_flags & RVT_S_WAIT_ACK)
			qpriv->s_flags &= ~RVT_S_WAIT_ACK;
		अगर (!hfi1_tid_rdma_is_resync_psn(psn)) अणु
			/* Check अगर there is any pending TID ACK */
			अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE &&
			    req->ack_seg < req->cur_seg)
				hfi1_mod_tid_retry_समयr(qp);
			अन्यथा
				hfi1_stop_tid_retry_समयr(qp);
			hfi1_schedule_send(qp);
		पूर्ण अन्यथा अणु
			u32 spsn, fpsn, last_acked, generation;
			काष्ठा tid_rdma_request *rptr;

			/* ACK(RESYNC) */
			hfi1_stop_tid_retry_समयr(qp);
			/* Allow new requests (see hfi1_make_tid_rdma_pkt) */
			qp->s_flags &= ~HFI1_S_WAIT_HALT;
			/*
			 * Clear RVT_S_SEND_ONE flag in हाल that the TID RDMA
			 * ACK is received after the TID retry समयr is fired
			 * again. In this हाल, करो not send any more TID
			 * RESYNC request or रुको क्रम any more TID ACK packet.
			 */
			qpriv->s_flags &= ~RVT_S_SEND_ONE;
			hfi1_schedule_send(qp);

			अगर ((qp->s_acked == qpriv->s_tid_tail &&
			     req->ack_seg == req->total_segs) ||
			    qp->s_acked == qp->s_tail) अणु
				qpriv->s_state = TID_OP(WRITE_DATA_LAST);
				जाओ करोne;
			पूर्ण

			अगर (req->ack_seg == req->comp_seg) अणु
				qpriv->s_state = TID_OP(WRITE_DATA);
				जाओ करोne;
			पूर्ण

			/*
			 * The PSN to start with is the next PSN after the
			 * RESYNC PSN.
			 */
			psn = mask_psn(psn + 1);
			generation = psn >> HFI1_KDETH_BTH_SEQ_SHIFT;
			spsn = 0;

			/*
			 * Update to the correct WQE when we get an ACK(RESYNC)
			 * in the middle of a request.
			 */
			अगर (delta_psn(ack_psn, wqe->lpsn))
				wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
			req = wqe_to_tid_req(wqe);
			flow = &req->flows[req->acked_tail];
			/*
			 * RESYNC re-numbers the PSN ranges of all reमुख्यing
			 * segments. Also, PSN's start from 0 in the middle of a
			 * segment and the first segment size is less than the
			 * शेष number of packets. flow->resync_npkts is used
			 * to track the number of packets from the start of the
			 * real segment to the poपूर्णांक of 0 PSN after the RESYNC
			 * in order to later correctly शुरुआत the SGE.
			 */
			fpsn = full_flow_psn(flow, flow->flow_state.spsn);
			req->r_ack_psn = psn;
			/*
			 * If resync_psn poपूर्णांकs to the last flow PSN क्रम a
			 * segment and the new segment (likely from a new
			 * request) starts with a new generation number, we
			 * need to adjust resync_psn accordingly.
			 */
			अगर (flow->flow_state.generation !=
			    (resync_psn >> HFI1_KDETH_BTH_SEQ_SHIFT))
				resync_psn = mask_psn(fpsn - 1);
			flow->resync_npkts +=
				delta_psn(mask_psn(resync_psn + 1), fpsn);
			/*
			 * Rक्रमागतber all packet sequence number ranges
			 * based on the new generation.
			 */
			last_acked = qp->s_acked;
			rptr = req;
			जबतक (1) अणु
				/* start from last acked segment */
				क्रम (fidx = rptr->acked_tail;
				     CIRC_CNT(rptr->setup_head, fidx,
					      MAX_FLOWS);
				     fidx = CIRC_NEXT(fidx, MAX_FLOWS)) अणु
					u32 lpsn;
					u32 gen;

					flow = &rptr->flows[fidx];
					gen = flow->flow_state.generation;
					अगर (WARN_ON(gen == generation &&
						    flow->flow_state.spsn !=
						     spsn))
						जारी;
					lpsn = flow->flow_state.lpsn;
					lpsn = full_flow_psn(flow, lpsn);
					flow->npkts =
						delta_psn(lpsn,
							  mask_psn(resync_psn)
							  );
					flow->flow_state.generation =
						generation;
					flow->flow_state.spsn = spsn;
					flow->flow_state.lpsn =
						flow->flow_state.spsn +
						flow->npkts - 1;
					flow->pkt = 0;
					spsn += flow->npkts;
					resync_psn += flow->npkts;
					trace_hfi1_tid_flow_rcv_tid_ack(qp,
									fidx,
									flow);
				पूर्ण
				अगर (++last_acked == qpriv->s_tid_cur + 1)
					अवरोध;
				अगर (last_acked == qp->s_size)
					last_acked = 0;
				wqe = rvt_get_swqe_ptr(qp, last_acked);
				rptr = wqe_to_tid_req(wqe);
			पूर्ण
			req->cur_seg = req->ack_seg;
			qpriv->s_tid_tail = qp->s_acked;
			qpriv->s_state = TID_OP(WRITE_REQ);
			hfi1_schedule_tid_send(qp);
		पूर्ण
करोne:
		qpriv->s_retry = qp->s_retry_cnt;
		अवरोध;

	हाल 3:         /* NAK */
		hfi1_stop_tid_retry_समयr(qp);
		चयन ((aeth >> IB_AETH_CREDIT_SHIFT) &
			IB_AETH_CREDIT_MASK) अणु
		हाल 0: /* PSN sequence error */
			अगर (!req->flows)
				अवरोध;
			flow = &req->flows[req->acked_tail];
			flpsn = full_flow_psn(flow, flow->flow_state.lpsn);
			अगर (cmp_psn(psn, flpsn) > 0)
				अवरोध;
			trace_hfi1_tid_flow_rcv_tid_ack(qp, req->acked_tail,
							flow);
			req->r_ack_psn = mask_psn(be32_to_cpu(ohdr->bth[2]));
			req->cur_seg = req->ack_seg;
			qpriv->s_tid_tail = qp->s_acked;
			qpriv->s_state = TID_OP(WRITE_REQ);
			qpriv->s_retry = qp->s_retry_cnt;
			hfi1_schedule_tid_send(qp);
			अवरोध;

		शेष:
			अवरोध;
		पूर्ण
		अवरोध;

	शेष:
		अवरोध;
	पूर्ण

ack_op_err:
	spin_unlock_irqrestore(&qp->s_lock, flags);
पूर्ण

व्योम hfi1_add_tid_retry_समयr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_qp *ibqp = &qp->ibqp;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);

	lockdep_निश्चित_held(&qp->s_lock);
	अगर (!(priv->s_flags & HFI1_S_TID_RETRY_TIMER)) अणु
		priv->s_flags |= HFI1_S_TID_RETRY_TIMER;
		priv->s_tid_retry_समयr.expires = jअगरfies +
			priv->tid_retry_समयout_jअगरfies + rdi->busy_jअगरfies;
		add_समयr(&priv->s_tid_retry_समयr);
	पूर्ण
पूर्ण

अटल व्योम hfi1_mod_tid_retry_समयr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_qp *ibqp = &qp->ibqp;
	काष्ठा rvt_dev_info *rdi = ib_to_rvt(ibqp->device);

	lockdep_निश्चित_held(&qp->s_lock);
	priv->s_flags |= HFI1_S_TID_RETRY_TIMER;
	mod_समयr(&priv->s_tid_retry_समयr, jअगरfies +
		  priv->tid_retry_समयout_jअगरfies + rdi->busy_jअगरfies);
पूर्ण

अटल पूर्णांक hfi1_stop_tid_retry_समयr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	पूर्णांक rval = 0;

	lockdep_निश्चित_held(&qp->s_lock);
	अगर (priv->s_flags & HFI1_S_TID_RETRY_TIMER) अणु
		rval = del_समयr(&priv->s_tid_retry_समयr);
		priv->s_flags &= ~HFI1_S_TID_RETRY_TIMER;
	पूर्ण
	वापस rval;
पूर्ण

व्योम hfi1_del_tid_retry_समयr(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	del_समयr_sync(&priv->s_tid_retry_समयr);
	priv->s_flags &= ~HFI1_S_TID_RETRY_TIMER;
पूर्ण

अटल व्योम hfi1_tid_retry_समयout(काष्ठा समयr_list *t)
अणु
	काष्ठा hfi1_qp_priv *priv = from_समयr(priv, t, s_tid_retry_समयr);
	काष्ठा rvt_qp *qp = priv->owner;
	काष्ठा rvt_swqe *wqe;
	अचिन्हित दीर्घ flags;
	काष्ठा tid_rdma_request *req;

	spin_lock_irqsave(&qp->r_lock, flags);
	spin_lock(&qp->s_lock);
	trace_hfi1_tid_ग_लिखो_sender_retry_समयout(qp, 0);
	अगर (priv->s_flags & HFI1_S_TID_RETRY_TIMER) अणु
		hfi1_stop_tid_retry_समयr(qp);
		अगर (!priv->s_retry) अणु
			trace_hfi1_msg_tid_retry_समयout(/* msg */
				qp,
				"Exhausted retries. Tid retry timeout = ",
				(u64)priv->tid_retry_समयout_jअगरfies);

			wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
			hfi1_trdma_send_complete(qp, wqe, IB_WC_RETRY_EXC_ERR);
			rvt_error_qp(qp, IB_WC_WR_FLUSH_ERR);
		पूर्ण अन्यथा अणु
			wqe = rvt_get_swqe_ptr(qp, qp->s_acked);
			req = wqe_to_tid_req(wqe);
			trace_hfi1_tid_req_tid_retry_समयout(/* req */
			   qp, 0, wqe->wr.opcode, wqe->psn, wqe->lpsn, req);

			priv->s_flags &= ~RVT_S_WAIT_ACK;
			/* Only send one packet (the RESYNC) */
			priv->s_flags |= RVT_S_SEND_ONE;
			/*
			 * No additional request shall be made by this QP until
			 * the RESYNC has been complete.
			 */
			qp->s_flags |= HFI1_S_WAIT_HALT;
			priv->s_state = TID_OP(RESYNC);
			priv->s_retry--;
			hfi1_schedule_tid_send(qp);
		पूर्ण
	पूर्ण
	spin_unlock(&qp->s_lock);
	spin_unlock_irqrestore(&qp->r_lock, flags);
पूर्ण

u32 hfi1_build_tid_rdma_resync(काष्ठा rvt_qp *qp, काष्ठा rvt_swqe *wqe,
			       काष्ठा ib_other_headers *ohdr, u32 *bth1,
			       u32 *bth2, u16 fidx)
अणु
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा tid_rdma_params *remote;
	काष्ठा tid_rdma_request *req = wqe_to_tid_req(wqe);
	काष्ठा tid_rdma_flow *flow = &req->flows[fidx];
	u32 generation;

	rcu_पढ़ो_lock();
	remote = rcu_dereference(qpriv->tid_rdma.remote);
	KDETH_RESET(ohdr->u.tid_rdma.ack.kdeth1, JKEY, remote->jkey);
	ohdr->u.tid_rdma.ack.verbs_qp = cpu_to_be32(qp->remote_qpn);
	*bth1 = remote->qp;
	rcu_पढ़ो_unlock();

	generation = kern_flow_generation_next(flow->flow_state.generation);
	*bth2 = mask_psn((generation << HFI1_KDETH_BTH_SEQ_SHIFT) - 1);
	qpriv->s_resync_psn = *bth2;
	*bth2 |= IB_BTH_REQ_ACK;
	KDETH_RESET(ohdr->u.tid_rdma.ack.kdeth0, KVER, 0x1);

	वापस माप(ohdr->u.tid_rdma.resync) / माप(u32);
पूर्ण

व्योम hfi1_rc_rcv_tid_rdma_resync(काष्ठा hfi1_packet *packet)
अणु
	काष्ठा ib_other_headers *ohdr = packet->ohdr;
	काष्ठा rvt_qp *qp = packet->qp;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा hfi1_ctxtdata *rcd = qpriv->rcd;
	काष्ठा hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	काष्ठा rvt_ack_entry *e;
	काष्ठा tid_rdma_request *req;
	काष्ठा tid_rdma_flow *flow;
	काष्ठा tid_flow_state *fs = &qpriv->flow_state;
	u32 psn, generation, idx, gen_next;
	bool fecn;
	अचिन्हित दीर्घ flags;

	fecn = process_ecn(qp, packet);
	psn = mask_psn(be32_to_cpu(ohdr->bth[2]));

	generation = mask_psn(psn + 1) >> HFI1_KDETH_BTH_SEQ_SHIFT;
	spin_lock_irqsave(&qp->s_lock, flags);

	gen_next = (fs->generation == KERN_GENERATION_RESERVED) ?
		generation : kern_flow_generation_next(fs->generation);
	/*
	 * RESYNC packet contains the "next" generation and can only be
	 * from the current or previous generations
	 */
	अगर (generation != mask_generation(gen_next - 1) &&
	    generation != gen_next)
		जाओ bail;
	/* Alपढ़ोy processing a resync */
	अगर (qpriv->resync)
		जाओ bail;

	spin_lock(&rcd->exp_lock);
	अगर (fs->index >= RXE_NUM_TID_FLOWS) अणु
		/*
		 * If we करोn't have a flow, save the generation so it can be
		 * applied when a new flow is allocated
		 */
		fs->generation = generation;
	पूर्ण अन्यथा अणु
		/* Reprogram the QP flow with new generation */
		rcd->flows[fs->index].generation = generation;
		fs->generation = kern_setup_hw_flow(rcd, fs->index);
	पूर्ण
	fs->psn = 0;
	/*
	 * Disable SW PSN checking since a RESYNC is equivalent to a
	 * sync poपूर्णांक and the flow has/will be reprogrammed
	 */
	qpriv->s_flags &= ~HFI1_R_TID_SW_PSN;
	trace_hfi1_tid_ग_लिखो_rsp_rcv_resync(qp);

	/*
	 * Reset all TID flow inक्रमmation with the new generation.
	 * This is करोne क्रम all requests and segments after the
	 * last received segment
	 */
	क्रम (idx = qpriv->r_tid_tail; ; idx++) अणु
		u16 flow_idx;

		अगर (idx > rvt_size_atomic(&dev->rdi))
			idx = 0;
		e = &qp->s_ack_queue[idx];
		अगर (e->opcode == TID_OP(WRITE_REQ)) अणु
			req = ack_to_tid_req(e);
			trace_hfi1_tid_req_rcv_resync(qp, 0, e->opcode, e->psn,
						      e->lpsn, req);

			/* start from last unacked segment */
			क्रम (flow_idx = req->clear_tail;
			     CIRC_CNT(req->setup_head, flow_idx,
				      MAX_FLOWS);
			     flow_idx = CIRC_NEXT(flow_idx, MAX_FLOWS)) अणु
				u32 lpsn;
				u32 next;

				flow = &req->flows[flow_idx];
				lpsn = full_flow_psn(flow,
						     flow->flow_state.lpsn);
				next = flow->flow_state.r_next_psn;
				flow->npkts = delta_psn(lpsn, next - 1);
				flow->flow_state.generation = fs->generation;
				flow->flow_state.spsn = fs->psn;
				flow->flow_state.lpsn =
					flow->flow_state.spsn + flow->npkts - 1;
				flow->flow_state.r_next_psn =
					full_flow_psn(flow,
						      flow->flow_state.spsn);
				fs->psn += flow->npkts;
				trace_hfi1_tid_flow_rcv_resync(qp, flow_idx,
							       flow);
			पूर्ण
		पूर्ण
		अगर (idx == qp->s_tail_ack_queue)
			अवरोध;
	पूर्ण

	spin_unlock(&rcd->exp_lock);
	qpriv->resync = true;
	/* RESYNC request always माला_लो a TID RDMA ACK. */
	qpriv->s_nak_state = 0;
	tid_rdma_trigger_ack(qp);
bail:
	अगर (fecn)
		qp->s_flags |= RVT_S_ECN;
	spin_unlock_irqrestore(&qp->s_lock, flags);
पूर्ण

/*
 * Call this function when the last TID RDMA WRITE DATA packet क्रम a request
 * is built.
 */
अटल व्योम update_tid_tail(काष्ठा rvt_qp *qp)
	__must_hold(&qp->s_lock)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	u32 i;
	काष्ठा rvt_swqe *wqe;

	lockdep_निश्चित_held(&qp->s_lock);
	/* Can't move beyond s_tid_cur */
	अगर (priv->s_tid_tail == priv->s_tid_cur)
		वापस;
	क्रम (i = priv->s_tid_tail + 1; ; i++) अणु
		अगर (i == qp->s_size)
			i = 0;

		अगर (i == priv->s_tid_cur)
			अवरोध;
		wqe = rvt_get_swqe_ptr(qp, i);
		अगर (wqe->wr.opcode == IB_WR_TID_RDMA_WRITE)
			अवरोध;
	पूर्ण
	priv->s_tid_tail = i;
	priv->s_state = TID_OP(WRITE_RESP);
पूर्ण

पूर्णांक hfi1_make_tid_rdma_pkt(काष्ठा rvt_qp *qp, काष्ठा hfi1_pkt_state *ps)
	__must_hold(&qp->s_lock)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा rvt_swqe *wqe;
	u32 bth1 = 0, bth2 = 0, hwords = 5, len, middle = 0;
	काष्ठा ib_other_headers *ohdr;
	काष्ठा rvt_sge_state *ss = &qp->s_sge;
	काष्ठा rvt_ack_entry *e = &qp->s_ack_queue[qp->s_tail_ack_queue];
	काष्ठा tid_rdma_request *req = ack_to_tid_req(e);
	bool last = false;
	u8 opcode = TID_OP(WRITE_DATA);

	lockdep_निश्चित_held(&qp->s_lock);
	trace_hfi1_tid_ग_लिखो_sender_make_tid_pkt(qp, 0);
	/*
	 * Prioritize the sending of the requests and responses over the
	 * sending of the TID RDMA data packets.
	 */
	अगर (((atomic_पढ़ो(&priv->n_tid_requests) < HFI1_TID_RDMA_WRITE_CNT) &&
	     atomic_पढ़ो(&priv->n_requests) &&
	     !(qp->s_flags & (RVT_S_BUSY | RVT_S_WAIT_ACK |
			     HFI1_S_ANY_WAIT_IO))) ||
	    (e->opcode == TID_OP(WRITE_REQ) && req->cur_seg < req->alloc_seg &&
	     !(qp->s_flags & (RVT_S_BUSY | HFI1_S_ANY_WAIT_IO)))) अणु
		काष्ठा ioरुको_work *iowork;

		iowork = ioरुको_get_ib_work(&priv->s_ioरुको);
		ps->s_txreq = get_रुकोing_verbs_txreq(iowork);
		अगर (ps->s_txreq || hfi1_make_rc_req(qp, ps)) अणु
			priv->s_flags |= HFI1_S_TID_BUSY_SET;
			वापस 1;
		पूर्ण
	पूर्ण

	ps->s_txreq = get_txreq(ps->dev, qp);
	अगर (!ps->s_txreq)
		जाओ bail_no_tx;

	ohdr = &ps->s_txreq->phdr.hdr.ibh.u.oth;

	अगर ((priv->s_flags & RVT_S_ACK_PENDING) &&
	    make_tid_rdma_ack(qp, ohdr, ps))
		वापस 1;

	/*
	 * Bail out अगर we can't send data.
	 * Be reminded that this check must been करोne after the call to
	 * make_tid_rdma_ack() because the responding QP could be in
	 * RTR state where it can send TID RDMA ACK, not TID RDMA WRITE DATA.
	 */
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_SEND_OK))
		जाओ bail;

	अगर (priv->s_flags & RVT_S_WAIT_ACK)
		जाओ bail;

	/* Check whether there is anything to करो. */
	अगर (priv->s_tid_tail == HFI1_QP_WQE_INVALID)
		जाओ bail;
	wqe = rvt_get_swqe_ptr(qp, priv->s_tid_tail);
	req = wqe_to_tid_req(wqe);
	trace_hfi1_tid_req_make_tid_pkt(qp, 0, wqe->wr.opcode, wqe->psn,
					wqe->lpsn, req);
	चयन (priv->s_state) अणु
	हाल TID_OP(WRITE_REQ):
	हाल TID_OP(WRITE_RESP):
		priv->tid_ss.sge = wqe->sg_list[0];
		priv->tid_ss.sg_list = wqe->sg_list + 1;
		priv->tid_ss.num_sge = wqe->wr.num_sge;
		priv->tid_ss.total_len = wqe->length;

		अगर (priv->s_state == TID_OP(WRITE_REQ))
			hfi1_tid_rdma_restart_req(qp, wqe, &bth2);
		priv->s_state = TID_OP(WRITE_DATA);
		fallthrough;

	हाल TID_OP(WRITE_DATA):
		/*
		 * 1. Check whether TID RDMA WRITE RESP available.
		 * 2. If no:
		 *    2.1 If have more segments and no TID RDMA WRITE RESP,
		 *        set HFI1_S_WAIT_TID_RESP
		 *    2.2 Return indicating no progress made.
		 * 3. If yes:
		 *    3.1 Build TID RDMA WRITE DATA packet.
		 *    3.2 If last packet in segment:
		 *        3.2.1 Change KDETH header bits
		 *        3.2.2 Advance RESP poपूर्णांकers.
		 *    3.3 Return indicating progress made.
		 */
		trace_hfi1_sender_make_tid_pkt(qp);
		trace_hfi1_tid_ग_लिखो_sender_make_tid_pkt(qp, 0);
		wqe = rvt_get_swqe_ptr(qp, priv->s_tid_tail);
		req = wqe_to_tid_req(wqe);
		len = wqe->length;

		अगर (!req->comp_seg || req->cur_seg == req->comp_seg)
			जाओ bail;

		trace_hfi1_tid_req_make_tid_pkt(qp, 0, wqe->wr.opcode,
						wqe->psn, wqe->lpsn, req);
		last = hfi1_build_tid_rdma_packet(wqe, ohdr, &bth1, &bth2,
						  &len);

		अगर (last) अणु
			/* move poपूर्णांकer to next flow */
			req->clear_tail = CIRC_NEXT(req->clear_tail,
						    MAX_FLOWS);
			अगर (++req->cur_seg < req->total_segs) अणु
				अगर (!CIRC_CNT(req->setup_head, req->clear_tail,
					      MAX_FLOWS))
					qp->s_flags |= HFI1_S_WAIT_TID_RESP;
			पूर्ण अन्यथा अणु
				priv->s_state = TID_OP(WRITE_DATA_LAST);
				opcode = TID_OP(WRITE_DATA_LAST);

				/* Advance the s_tid_tail now */
				update_tid_tail(qp);
			पूर्ण
		पूर्ण
		hwords += माप(ohdr->u.tid_rdma.w_data) / माप(u32);
		ss = &priv->tid_ss;
		अवरोध;

	हाल TID_OP(RESYNC):
		trace_hfi1_sender_make_tid_pkt(qp);
		/* Use generation from the most recently received response */
		wqe = rvt_get_swqe_ptr(qp, priv->s_tid_cur);
		req = wqe_to_tid_req(wqe);
		/* If no responses क्रम this WQE look at the previous one */
		अगर (!req->comp_seg) अणु
			wqe = rvt_get_swqe_ptr(qp,
					       (!priv->s_tid_cur ? qp->s_size :
						priv->s_tid_cur) - 1);
			req = wqe_to_tid_req(wqe);
		पूर्ण
		hwords += hfi1_build_tid_rdma_resync(qp, wqe, ohdr, &bth1,
						     &bth2,
						     CIRC_PREV(req->setup_head,
							       MAX_FLOWS));
		ss = शून्य;
		len = 0;
		opcode = TID_OP(RESYNC);
		अवरोध;

	शेष:
		जाओ bail;
	पूर्ण
	अगर (priv->s_flags & RVT_S_SEND_ONE) अणु
		priv->s_flags &= ~RVT_S_SEND_ONE;
		priv->s_flags |= RVT_S_WAIT_ACK;
		bth2 |= IB_BTH_REQ_ACK;
	पूर्ण
	qp->s_len -= len;
	ps->s_txreq->hdr_dwords = hwords;
	ps->s_txreq->sde = priv->s_sde;
	ps->s_txreq->ss = ss;
	ps->s_txreq->s_cur_size = len;
	hfi1_make_ruc_header(qp, ohdr, (opcode << 24), bth1, bth2,
			     middle, ps);
	वापस 1;
bail:
	hfi1_put_txreq(ps->s_txreq);
bail_no_tx:
	ps->s_txreq = शून्य;
	priv->s_flags &= ~RVT_S_BUSY;
	/*
	 * If we didn't get a txreq, the QP will be woken up later to try
	 * again, set the flags to the the wake up which work item to wake
	 * up.
	 * (A better algorithm should be found to करो this and generalize the
	 * sleep/wakeup flags.)
	 */
	ioरुको_set_flag(&priv->s_ioरुको, IOWAIT_PENDING_TID);
	वापस 0;
पूर्ण

अटल पूर्णांक make_tid_rdma_ack(काष्ठा rvt_qp *qp,
			     काष्ठा ib_other_headers *ohdr,
			     काष्ठा hfi1_pkt_state *ps)
अणु
	काष्ठा rvt_ack_entry *e;
	काष्ठा hfi1_qp_priv *qpriv = qp->priv;
	काष्ठा hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	u32 hwords, next;
	u32 len = 0;
	u32 bth1 = 0, bth2 = 0;
	पूर्णांक middle = 0;
	u16 flow;
	काष्ठा tid_rdma_request *req, *nreq;

	trace_hfi1_tid_ग_लिखो_rsp_make_tid_ack(qp);
	/* Don't send an ACK if we aren't supposed to. */
	अगर (!(ib_rvt_state_ops[qp->state] & RVT_PROCESS_RECV_OK))
		जाओ bail;

	/* header size in 32-bit words LRH+BTH = (8+12)/4. */
	hwords = 5;

	e = &qp->s_ack_queue[qpriv->r_tid_ack];
	req = ack_to_tid_req(e);
	/*
	 * In the RESYNC हाल, we are exactly one segment past the
	 * previously sent ack or at the previously sent NAK. So to send
	 * the resync ack, we go back one segment (which might be part of
	 * the previous request) and let the करो-जबतक loop execute again.
	 * The advantage of executing the करो-जबतक loop is that any data
	 * received after the previous ack is स्वतःmatically acked in the
	 * RESYNC ack. It turns out that क्रम the करो-जबतक loop we only need
	 * to pull back qpriv->r_tid_ack, not the segment
	 * indices/counters. The scheme works even अगर the previous request
	 * was not a TID WRITE request.
	 */
	अगर (qpriv->resync) अणु
		अगर (!req->ack_seg || req->ack_seg == req->total_segs)
			qpriv->r_tid_ack = !qpriv->r_tid_ack ?
				rvt_size_atomic(&dev->rdi) :
				qpriv->r_tid_ack - 1;
		e = &qp->s_ack_queue[qpriv->r_tid_ack];
		req = ack_to_tid_req(e);
	पूर्ण

	trace_hfi1_rsp_make_tid_ack(qp, e->psn);
	trace_hfi1_tid_req_make_tid_ack(qp, 0, e->opcode, e->psn, e->lpsn,
					req);
	/*
	 * If we've sent all the ACKs that we can, we are करोne
	 * until we get more segments...
	 */
	अगर (!qpriv->s_nak_state && !qpriv->resync &&
	    req->ack_seg == req->comp_seg)
		जाओ bail;

	करो अणु
		/*
		 * To deal with coalesced ACKs, the acked_tail poपूर्णांकer
		 * पूर्णांकo the flow array is used. The distance between it
		 * and the clear_tail is the number of flows that are
		 * being ACK'ed.
		 */
		req->ack_seg +=
			/* Get up-to-date value */
			CIRC_CNT(req->clear_tail, req->acked_tail,
				 MAX_FLOWS);
		/* Advance acked index */
		req->acked_tail = req->clear_tail;

		/*
		 * req->clear_tail poपूर्णांकs to the segment currently being
		 * received. So, when sending an ACK, the previous
		 * segment is being ACK'ed.
		 */
		flow = CIRC_PREV(req->acked_tail, MAX_FLOWS);
		अगर (req->ack_seg != req->total_segs)
			अवरोध;
		req->state = TID_REQUEST_COMPLETE;

		next = qpriv->r_tid_ack + 1;
		अगर (next > rvt_size_atomic(&dev->rdi))
			next = 0;
		qpriv->r_tid_ack = next;
		अगर (qp->s_ack_queue[next].opcode != TID_OP(WRITE_REQ))
			अवरोध;
		nreq = ack_to_tid_req(&qp->s_ack_queue[next]);
		अगर (!nreq->comp_seg || nreq->ack_seg == nreq->comp_seg)
			अवरोध;

		/* Move to the next ack entry now */
		e = &qp->s_ack_queue[qpriv->r_tid_ack];
		req = ack_to_tid_req(e);
	पूर्ण जबतक (1);

	/*
	 * At this poपूर्णांक qpriv->r_tid_ack == qpriv->r_tid_tail but e and
	 * req could be poपूर्णांकing at the previous ack queue entry
	 */
	अगर (qpriv->s_nak_state ||
	    (qpriv->resync &&
	     !hfi1_tid_rdma_is_resync_psn(qpriv->r_next_psn_kdeth - 1) &&
	     (cmp_psn(qpriv->r_next_psn_kdeth - 1,
		      full_flow_psn(&req->flows[flow],
				    req->flows[flow].flow_state.lpsn)) > 0))) अणु
		/*
		 * A NAK will implicitly acknowledge all previous TID RDMA
		 * requests. Thereक्रमe, we NAK with the req->acked_tail
		 * segment क्रम the request at qpriv->r_tid_ack (same at
		 * this poपूर्णांक as the req->clear_tail segment क्रम the
		 * qpriv->r_tid_tail request)
		 */
		e = &qp->s_ack_queue[qpriv->r_tid_ack];
		req = ack_to_tid_req(e);
		flow = req->acked_tail;
	पूर्ण अन्यथा अगर (req->ack_seg == req->total_segs &&
		   qpriv->s_flags & HFI1_R_TID_WAIT_INTERLCK)
		qpriv->s_flags &= ~HFI1_R_TID_WAIT_INTERLCK;

	trace_hfi1_tid_ग_लिखो_rsp_make_tid_ack(qp);
	trace_hfi1_tid_req_make_tid_ack(qp, 0, e->opcode, e->psn, e->lpsn,
					req);
	hwords += hfi1_build_tid_rdma_ग_लिखो_ack(qp, e, ohdr, flow, &bth1,
						&bth2);
	len = 0;
	qpriv->s_flags &= ~RVT_S_ACK_PENDING;
	ps->s_txreq->hdr_dwords = hwords;
	ps->s_txreq->sde = qpriv->s_sde;
	ps->s_txreq->s_cur_size = len;
	ps->s_txreq->ss = शून्य;
	hfi1_make_ruc_header(qp, ohdr, (TID_OP(ACK) << 24), bth1, bth2, middle,
			     ps);
	ps->s_txreq->txreq.flags |= SDMA_TXREQ_F_VIP;
	वापस 1;
bail:
	/*
	 * Ensure s_rdma_ack_cnt changes are committed prior to resetting
	 * RVT_S_RESP_PENDING
	 */
	smp_wmb();
	qpriv->s_flags &= ~RVT_S_ACK_PENDING;
	वापस 0;
पूर्ण

अटल पूर्णांक hfi1_send_tid_ok(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	वापस !(priv->s_flags & RVT_S_BUSY ||
		 qp->s_flags & HFI1_S_ANY_WAIT_IO) &&
		(verbs_txreq_queued(ioरुको_get_tid_work(&priv->s_ioरुको)) ||
		 (priv->s_flags & RVT_S_RESP_PENDING) ||
		 !(qp->s_flags & HFI1_S_ANY_TID_WAIT_SEND));
पूर्ण

व्योम _hfi1_करो_tid_send(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा ioरुको_work *w = container_of(work, काष्ठा ioरुको_work, iowork);
	काष्ठा rvt_qp *qp = ioरुको_to_qp(w->iow);

	hfi1_करो_tid_send(qp);
पूर्ण

अटल व्योम hfi1_करो_tid_send(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_pkt_state ps;
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	ps.dev = to_idev(qp->ibqp.device);
	ps.ibp = to_iport(qp->ibqp.device, qp->port_num);
	ps.ppd = ppd_from_ibp(ps.ibp);
	ps.रुको = ioरुको_get_tid_work(&priv->s_ioरुको);
	ps.in_thपढ़ो = false;
	ps.समयout_पूर्णांक = qp->समयout_jअगरfies / 8;

	trace_hfi1_rc_करो_tid_send(qp, false);
	spin_lock_irqsave(&qp->s_lock, ps.flags);

	/* Return अगर we are alपढ़ोy busy processing a work request. */
	अगर (!hfi1_send_tid_ok(qp)) अणु
		अगर (qp->s_flags & HFI1_S_ANY_WAIT_IO)
			ioरुको_set_flag(&priv->s_ioरुको, IOWAIT_PENDING_TID);
		spin_unlock_irqrestore(&qp->s_lock, ps.flags);
		वापस;
	पूर्ण

	priv->s_flags |= RVT_S_BUSY;

	ps.समयout = jअगरfies + ps.समयout_पूर्णांक;
	ps.cpu = priv->s_sde ? priv->s_sde->cpu :
		cpumask_first(cpumask_of_node(ps.ppd->dd->node));
	ps.pkts_sent = false;

	/* insure a pre-built packet is handled  */
	ps.s_txreq = get_रुकोing_verbs_txreq(ps.रुको);
	करो अणु
		/* Check क्रम a स्थिरructed packet to be sent. */
		अगर (ps.s_txreq) अणु
			अगर (priv->s_flags & HFI1_S_TID_BUSY_SET) अणु
				qp->s_flags |= RVT_S_BUSY;
				ps.रुको = ioरुको_get_ib_work(&priv->s_ioरुको);
			पूर्ण
			spin_unlock_irqrestore(&qp->s_lock, ps.flags);

			/*
			 * If the packet cannot be sent now, वापस and
			 * the send tasklet will be woken up later.
			 */
			अगर (hfi1_verbs_send(qp, &ps))
				वापस;

			/* allow other tasks to run */
			अगर (hfi1_schedule_send_yield(qp, &ps, true))
				वापस;

			spin_lock_irqsave(&qp->s_lock, ps.flags);
			अगर (priv->s_flags & HFI1_S_TID_BUSY_SET) अणु
				qp->s_flags &= ~RVT_S_BUSY;
				priv->s_flags &= ~HFI1_S_TID_BUSY_SET;
				ps.रुको = ioरुको_get_tid_work(&priv->s_ioरुको);
				अगर (ioरुको_flag_set(&priv->s_ioरुको,
						    IOWAIT_PENDING_IB))
					hfi1_schedule_send(qp);
			पूर्ण
		पूर्ण
	पूर्ण जबतक (hfi1_make_tid_rdma_pkt(qp, &ps));
	ioरुको_starve_clear(ps.pkts_sent, &priv->s_ioरुको);
	spin_unlock_irqrestore(&qp->s_lock, ps.flags);
पूर्ण

अटल bool _hfi1_schedule_tid_send(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_ibport *ibp =
		to_iport(qp->ibqp.device, qp->port_num);
	काष्ठा hfi1_pportdata *ppd = ppd_from_ibp(ibp);
	काष्ठा hfi1_devdata *dd = ppd->dd;

	अगर ((dd->flags & HFI1_SHUTDOWN))
		वापस true;

	वापस ioरुको_tid_schedule(&priv->s_ioरुको, ppd->hfi1_wq,
				   priv->s_sde ?
				   priv->s_sde->cpu :
				   cpumask_first(cpumask_of_node(dd->node)));
पूर्ण

/**
 * hfi1_schedule_tid_send - schedule progress on TID RDMA state machine
 * @qp: the QP
 *
 * This schedules qp progress on the TID RDMA state machine. Caller
 * should hold the s_lock.
 * Unlike hfi1_schedule_send(), this cannot use hfi1_send_ok() because
 * the two state machines can step on each other with respect to the
 * RVT_S_BUSY flag.
 * Thereक्रमe, a modअगरied test is used.
 * @वापस true अगर the second leg is scheduled;
 *  false अगर the second leg is not scheduled.
 */
bool hfi1_schedule_tid_send(काष्ठा rvt_qp *qp)
अणु
	lockdep_निश्चित_held(&qp->s_lock);
	अगर (hfi1_send_tid_ok(qp)) अणु
		/*
		 * The following call वापसs true अगर the qp is not on the
		 * queue and false अगर the qp is alपढ़ोy on the queue beक्रमe
		 * this call. Either way, the qp will be on the queue when the
		 * call वापसs.
		 */
		_hfi1_schedule_tid_send(qp);
		वापस true;
	पूर्ण
	अगर (qp->s_flags & HFI1_S_ANY_WAIT_IO)
		ioरुको_set_flag(&((काष्ठा hfi1_qp_priv *)qp->priv)->s_ioरुको,
				IOWAIT_PENDING_TID);
	वापस false;
पूर्ण

bool hfi1_tid_rdma_ack_पूर्णांकerlock(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e)
अणु
	काष्ठा rvt_ack_entry *prev;
	काष्ठा tid_rdma_request *req;
	काष्ठा hfi1_ibdev *dev = to_idev(qp->ibqp.device);
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	u32 s_prev;

	s_prev = qp->s_tail_ack_queue == 0 ? rvt_size_atomic(&dev->rdi) :
		(qp->s_tail_ack_queue - 1);
	prev = &qp->s_ack_queue[s_prev];

	अगर ((e->opcode == TID_OP(READ_REQ) ||
	     e->opcode == OP(RDMA_READ_REQUEST)) &&
	    prev->opcode == TID_OP(WRITE_REQ)) अणु
		req = ack_to_tid_req(prev);
		अगर (req->ack_seg != req->total_segs) अणु
			priv->s_flags |= HFI1_R_TID_WAIT_INTERLCK;
			वापस true;
		पूर्ण
	पूर्ण
	वापस false;
पूर्ण

अटल u32 पढ़ो_r_next_psn(काष्ठा hfi1_devdata *dd, u8 ctxt, u8 fidx)
अणु
	u64 reg;

	/*
	 * The only sane way to get the amount of
	 * progress is to पढ़ो the HW flow state.
	 */
	reg = पढ़ो_uctxt_csr(dd, ctxt, RCV_TID_FLOW_TABLE + (8 * fidx));
	वापस mask_psn(reg);
पूर्ण

अटल व्योम tid_rdma_rcv_err(काष्ठा hfi1_packet *packet,
			     काष्ठा ib_other_headers *ohdr,
			     काष्ठा rvt_qp *qp, u32 psn, पूर्णांक dअगरf, bool fecn)
अणु
	अचिन्हित दीर्घ flags;

	tid_rdma_rcv_error(packet, ohdr, qp, psn, dअगरf);
	अगर (fecn) अणु
		spin_lock_irqsave(&qp->s_lock, flags);
		qp->s_flags |= RVT_S_ECN;
		spin_unlock_irqrestore(&qp->s_lock, flags);
	पूर्ण
पूर्ण

अटल व्योम update_r_next_psn_fecn(काष्ठा hfi1_packet *packet,
				   काष्ठा hfi1_qp_priv *priv,
				   काष्ठा hfi1_ctxtdata *rcd,
				   काष्ठा tid_rdma_flow *flow,
				   bool fecn)
अणु
	/*
	 * If a start/middle packet is delivered here due to
	 * RSM rule and FECN, we need to update the r_next_psn.
	 */
	अगर (fecn && packet->etype == RHF_RCV_TYPE_EAGER &&
	    !(priv->s_flags & HFI1_R_TID_SW_PSN)) अणु
		काष्ठा hfi1_devdata *dd = rcd->dd;

		flow->flow_state.r_next_psn =
			पढ़ो_r_next_psn(dd, rcd->ctxt, flow->idx);
	पूर्ण
पूर्ण
