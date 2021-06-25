<शैली गुरु>
// SPDX-License-Identअगरier: (GPL-2.0 OR BSD-3-Clause)
/*
 * Copyright(c) 2018 Intel Corporation.
 *
 */
#समावेश "hfi.h"
#समावेश "trace.h"
#समावेश "qp.h"
#समावेश "opfn.h"

#घोषणा IB_BTHE_E                 BIT(IB_BTHE_E_SHIFT)

#घोषणा OPFN_CODE(code) BIT((code) - 1)
#घोषणा OPFN_MASK(code) OPFN_CODE(STL_VERBS_EXTD_##code)

काष्ठा hfi1_opfn_type अणु
	bool (*request)(काष्ठा rvt_qp *qp, u64 *data);
	bool (*response)(काष्ठा rvt_qp *qp, u64 *data);
	bool (*reply)(काष्ठा rvt_qp *qp, u64 data);
	व्योम (*error)(काष्ठा rvt_qp *qp);
पूर्ण;

अटल काष्ठा hfi1_opfn_type hfi1_opfn_handlers[STL_VERBS_EXTD_MAX] = अणु
	[STL_VERBS_EXTD_TID_RDMA] = अणु
		.request = tid_rdma_conn_req,
		.response = tid_rdma_conn_resp,
		.reply = tid_rdma_conn_reply,
		.error = tid_rdma_conn_error,
	पूर्ण,
पूर्ण;

अटल काष्ठा workqueue_काष्ठा *opfn_wq;

अटल व्योम opfn_schedule_conn_request(काष्ठा rvt_qp *qp);

अटल bool hfi1_opfn_extended(u32 bth1)
अणु
	वापस !!(bth1 & IB_BTHE_E);
पूर्ण

अटल व्योम opfn_conn_request(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा ib_atomic_wr wr;
	u16 mask, capcode;
	काष्ठा hfi1_opfn_type *extd;
	u64 data;
	अचिन्हित दीर्घ flags;
	पूर्णांक ret = 0;

	trace_hfi1_opfn_state_conn_request(qp);
	spin_lock_irqsave(&priv->opfn.lock, flags);
	/*
	 * Exit अगर the extended bit is not set, or अगर nothing is requested, or
	 * अगर we have completed all requests, or अगर a previous request is in
	 * progress
	 */
	अगर (!priv->opfn.extended || !priv->opfn.requested ||
	    priv->opfn.requested == priv->opfn.completed || priv->opfn.curr)
		जाओ करोne;

	mask = priv->opfn.requested & ~priv->opfn.completed;
	capcode = ilog2(mask & ~(mask - 1)) + 1;
	अगर (capcode >= STL_VERBS_EXTD_MAX) अणु
		priv->opfn.completed |= OPFN_CODE(capcode);
		जाओ करोne;
	पूर्ण

	extd = &hfi1_opfn_handlers[capcode];
	अगर (!extd || !extd->request || !extd->request(qp, &data)) अणु
		/*
		 * Either there is no handler क्रम this capability or the request
		 * packet could not be generated. Either way, mark it as करोne so
		 * we करोn't keep attempting to complete it.
		 */
		priv->opfn.completed |= OPFN_CODE(capcode);
		जाओ करोne;
	पूर्ण

	trace_hfi1_opfn_data_conn_request(qp, capcode, data);
	data = (data & ~0xf) | capcode;

	स_रखो(&wr, 0, माप(wr));
	wr.wr.opcode = IB_WR_OPFN;
	wr.remote_addr = HFI1_VERBS_E_ATOMIC_VADDR;
	wr.compare_add = data;

	priv->opfn.curr = capcode;	/* A new request is now in progress */
	/* Drop opfn.lock beक्रमe calling ib_post_send() */
	spin_unlock_irqrestore(&priv->opfn.lock, flags);

	ret = ib_post_send(&qp->ibqp, &wr.wr, शून्य);
	अगर (ret)
		जाओ err;
	trace_hfi1_opfn_state_conn_request(qp);
	वापस;
err:
	trace_hfi1_msg_opfn_conn_request(qp, "ib_ost_send failed: ret = ",
					 (u64)ret);
	spin_lock_irqsave(&priv->opfn.lock, flags);
	/*
	 * In हाल of an unexpected error वापस from ib_post_send
	 * clear opfn.curr and reschedule to try again
	 */
	priv->opfn.curr = STL_VERBS_EXTD_NONE;
	opfn_schedule_conn_request(qp);
करोne:
	spin_unlock_irqrestore(&priv->opfn.lock, flags);
पूर्ण

व्योम opfn_send_conn_request(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा hfi1_opfn_data *od;
	काष्ठा hfi1_qp_priv *qpriv;

	od = container_of(work, काष्ठा hfi1_opfn_data, opfn_work);
	qpriv = container_of(od, काष्ठा hfi1_qp_priv, opfn);

	opfn_conn_request(qpriv->owner);
पूर्ण

/*
 * When QP s_lock is held in the caller, the OPFN request must be scheduled
 * to a dअगरferent workqueue to aव्योम द्विगुन locking QP s_lock in call to
 * ib_post_send in opfn_conn_request
 */
अटल व्योम opfn_schedule_conn_request(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	trace_hfi1_opfn_state_sched_conn_request(qp);
	queue_work(opfn_wq, &priv->opfn.opfn_work);
पूर्ण

व्योम opfn_conn_response(काष्ठा rvt_qp *qp, काष्ठा rvt_ack_entry *e,
			काष्ठा ib_atomic_eth *ateth)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	u64 data = be64_to_cpu(ateth->compare_data);
	काष्ठा hfi1_opfn_type *extd;
	u8 capcode;
	अचिन्हित दीर्घ flags;

	trace_hfi1_opfn_state_conn_response(qp);
	capcode = data & 0xf;
	trace_hfi1_opfn_data_conn_response(qp, capcode, data);
	अगर (!capcode || capcode >= STL_VERBS_EXTD_MAX)
		वापस;

	extd = &hfi1_opfn_handlers[capcode];

	अगर (!extd || !extd->response) अणु
		e->atomic_data = capcode;
		वापस;
	पूर्ण

	spin_lock_irqsave(&priv->opfn.lock, flags);
	अगर (priv->opfn.completed & OPFN_CODE(capcode)) अणु
		/*
		 * We are receiving a request क्रम a feature that has alपढ़ोy
		 * been negotiated. This may mean that the other side has reset
		 */
		priv->opfn.completed &= ~OPFN_CODE(capcode);
		अगर (extd->error)
			extd->error(qp);
	पूर्ण

	अगर (extd->response(qp, &data))
		priv->opfn.completed |= OPFN_CODE(capcode);
	e->atomic_data = (data & ~0xf) | capcode;
	trace_hfi1_opfn_state_conn_response(qp);
	spin_unlock_irqrestore(&priv->opfn.lock, flags);
पूर्ण

व्योम opfn_conn_reply(काष्ठा rvt_qp *qp, u64 data)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_opfn_type *extd;
	u8 capcode;
	अचिन्हित दीर्घ flags;

	trace_hfi1_opfn_state_conn_reply(qp);
	capcode = data & 0xf;
	trace_hfi1_opfn_data_conn_reply(qp, capcode, data);
	अगर (!capcode || capcode >= STL_VERBS_EXTD_MAX)
		वापस;

	spin_lock_irqsave(&priv->opfn.lock, flags);
	/*
	 * Either there is no previous request or the reply is not क्रम the
	 * current request
	 */
	अगर (!priv->opfn.curr || capcode != priv->opfn.curr)
		जाओ करोne;

	extd = &hfi1_opfn_handlers[capcode];

	अगर (!extd || !extd->reply)
		जाओ clear;

	अगर (extd->reply(qp, data))
		priv->opfn.completed |= OPFN_CODE(capcode);
clear:
	/*
	 * Clear opfn.curr to indicate that the previous request is no दीर्घer in
	 * progress
	 */
	priv->opfn.curr = STL_VERBS_EXTD_NONE;
	trace_hfi1_opfn_state_conn_reply(qp);
करोne:
	spin_unlock_irqrestore(&priv->opfn.lock, flags);
पूर्ण

व्योम opfn_conn_error(काष्ठा rvt_qp *qp)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	काष्ठा hfi1_opfn_type *extd = शून्य;
	अचिन्हित दीर्घ flags;
	u16 capcode;

	trace_hfi1_opfn_state_conn_error(qp);
	trace_hfi1_msg_opfn_conn_error(qp, "error. qp state ", (u64)qp->state);
	/*
	 * The QP has gone पूर्णांकo the Error state. We have to invalidate all
	 * negotiated feature, including the one in progress (अगर any). The RC
	 * QP handling will clean the WQE क्रम the connection request.
	 */
	spin_lock_irqsave(&priv->opfn.lock, flags);
	जबतक (priv->opfn.completed) अणु
		capcode = priv->opfn.completed & ~(priv->opfn.completed - 1);
		extd = &hfi1_opfn_handlers[ilog2(capcode) + 1];
		अगर (extd->error)
			extd->error(qp);
		priv->opfn.completed &= ~OPFN_CODE(capcode);
	पूर्ण
	priv->opfn.extended = 0;
	priv->opfn.requested = 0;
	priv->opfn.curr = STL_VERBS_EXTD_NONE;
	spin_unlock_irqrestore(&priv->opfn.lock, flags);
पूर्ण

व्योम opfn_qp_init(काष्ठा rvt_qp *qp, काष्ठा ib_qp_attr *attr, पूर्णांक attr_mask)
अणु
	काष्ठा ib_qp *ibqp = &qp->ibqp;
	काष्ठा hfi1_qp_priv *priv = qp->priv;
	अचिन्हित दीर्घ flags;

	अगर (attr_mask & IB_QP_RETRY_CNT)
		priv->s_retry = attr->retry_cnt;

	spin_lock_irqsave(&priv->opfn.lock, flags);
	अगर (ibqp->qp_type == IB_QPT_RC && HFI1_CAP_IS_KSET(TID_RDMA)) अणु
		काष्ठा tid_rdma_params *local = &priv->tid_rdma.local;

		अगर (attr_mask & IB_QP_TIMEOUT)
			priv->tid_retry_समयout_jअगरfies = qp->समयout_jअगरfies;
		अगर (qp->pmtu == क्रमागत_to_mtu(OPA_MTU_4096) ||
		    qp->pmtu == क्रमागत_to_mtu(OPA_MTU_8192)) अणु
			tid_rdma_opfn_init(qp, local);
			/*
			 * We only want to set the OPFN requested bit when the
			 * QP transitions to RTS.
			 */
			अगर (attr_mask & IB_QP_STATE &&
			    attr->qp_state == IB_QPS_RTS) अणु
				priv->opfn.requested |= OPFN_MASK(TID_RDMA);
				/*
				 * If the QP is transitioning to RTS and the
				 * opfn.completed क्रम TID RDMA has alपढ़ोy been
				 * set, the QP is being moved *back* पूर्णांकo RTS.
				 * We can now renegotiate the TID RDMA
				 * parameters.
				 */
				अगर (priv->opfn.completed &
				    OPFN_MASK(TID_RDMA)) अणु
					priv->opfn.completed &=
						~OPFN_MASK(TID_RDMA);
					/*
					 * Since the opfn.completed bit was
					 * alपढ़ोy set, it is safe to assume
					 * that the opfn.extended is also set.
					 */
					opfn_schedule_conn_request(qp);
				पूर्ण
			पूर्ण
		पूर्ण अन्यथा अणु
			स_रखो(local, 0, माप(*local));
		पूर्ण
	पूर्ण
	spin_unlock_irqrestore(&priv->opfn.lock, flags);
पूर्ण

व्योम opfn_trigger_conn_request(काष्ठा rvt_qp *qp, u32 bth1)
अणु
	काष्ठा hfi1_qp_priv *priv = qp->priv;

	अगर (!priv->opfn.extended && hfi1_opfn_extended(bth1) &&
	    HFI1_CAP_IS_KSET(OPFN)) अणु
		priv->opfn.extended = 1;
		अगर (qp->state == IB_QPS_RTS)
			opfn_conn_request(qp);
	पूर्ण
पूर्ण

पूर्णांक opfn_init(व्योम)
अणु
	opfn_wq = alloc_workqueue("hfi_opfn",
				  WQ_SYSFS | WQ_HIGHPRI | WQ_CPU_INTENSIVE |
				  WQ_MEM_RECLAIM,
				  HFI1_MAX_ACTIVE_WORKQUEUE_ENTRIES);
	अगर (!opfn_wq)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

व्योम opfn_निकास(व्योम)
अणु
	अगर (opfn_wq) अणु
		destroy_workqueue(opfn_wq);
		opfn_wq = शून्य;
	पूर्ण
पूर्ण
