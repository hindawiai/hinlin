<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR Linux-OpenIB
/*
 * Copyright (c) 2016 Mellanox Technologies Ltd. All rights reserved.
 * Copyright (c) 2015 System Fabric Works, Inc. All rights reserved.
 */

#समावेश <linux/skbuff.h>
#समावेश <linux/delay.h>
#समावेश <linux/sched.h>
#समावेश <linux/vदो_स्मृति.h>
#समावेश <rdma/uverbs_ioctl.h>

#समावेश "rxe.h"
#समावेश "rxe_loc.h"
#समावेश "rxe_queue.h"
#समावेश "rxe_task.h"

अटल पूर्णांक rxe_qp_chk_cap(काष्ठा rxe_dev *rxe, काष्ठा ib_qp_cap *cap,
			  पूर्णांक has_srq)
अणु
	अगर (cap->max_send_wr > rxe->attr.max_qp_wr) अणु
		pr_warn("invalid send wr = %d > %d\n",
			cap->max_send_wr, rxe->attr.max_qp_wr);
		जाओ err1;
	पूर्ण

	अगर (cap->max_send_sge > rxe->attr.max_send_sge) अणु
		pr_warn("invalid send sge = %d > %d\n",
			cap->max_send_sge, rxe->attr.max_send_sge);
		जाओ err1;
	पूर्ण

	अगर (!has_srq) अणु
		अगर (cap->max_recv_wr > rxe->attr.max_qp_wr) अणु
			pr_warn("invalid recv wr = %d > %d\n",
				cap->max_recv_wr, rxe->attr.max_qp_wr);
			जाओ err1;
		पूर्ण

		अगर (cap->max_recv_sge > rxe->attr.max_recv_sge) अणु
			pr_warn("invalid recv sge = %d > %d\n",
				cap->max_recv_sge, rxe->attr.max_recv_sge);
			जाओ err1;
		पूर्ण
	पूर्ण

	अगर (cap->max_अंतरभूत_data > rxe->max_अंतरभूत_data) अणु
		pr_warn("invalid max inline data = %d > %d\n",
			cap->max_अंतरभूत_data, rxe->max_अंतरभूत_data);
		जाओ err1;
	पूर्ण

	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

पूर्णांक rxe_qp_chk_init(काष्ठा rxe_dev *rxe, काष्ठा ib_qp_init_attr *init)
अणु
	काष्ठा ib_qp_cap *cap = &init->cap;
	काष्ठा rxe_port *port;
	पूर्णांक port_num = init->port_num;

	चयन (init->qp_type) अणु
	हाल IB_QPT_SMI:
	हाल IB_QPT_GSI:
	हाल IB_QPT_RC:
	हाल IB_QPT_UC:
	हाल IB_QPT_UD:
		अवरोध;
	शेष:
		वापस -EOPNOTSUPP;
	पूर्ण

	अगर (!init->recv_cq || !init->send_cq) अणु
		pr_warn("missing cq\n");
		जाओ err1;
	पूर्ण

	अगर (rxe_qp_chk_cap(rxe, cap, !!init->srq))
		जाओ err1;

	अगर (init->qp_type == IB_QPT_SMI || init->qp_type == IB_QPT_GSI) अणु
		अगर (!rdma_is_port_valid(&rxe->ib_dev, port_num)) अणु
			pr_warn("invalid port = %d\n", port_num);
			जाओ err1;
		पूर्ण

		port = &rxe->port;

		अगर (init->qp_type == IB_QPT_SMI && port->qp_smi_index) अणु
			pr_warn("SMI QP exists for port %d\n", port_num);
			जाओ err1;
		पूर्ण

		अगर (init->qp_type == IB_QPT_GSI && port->qp_gsi_index) अणु
			pr_warn("GSI QP exists for port %d\n", port_num);
			जाओ err1;
		पूर्ण
	पूर्ण

	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

अटल पूर्णांक alloc_rd_atomic_resources(काष्ठा rxe_qp *qp, अचिन्हित पूर्णांक n)
अणु
	qp->resp.res_head = 0;
	qp->resp.res_tail = 0;
	qp->resp.resources = kसुस्मृति(n, माप(काष्ठा resp_res), GFP_KERNEL);

	अगर (!qp->resp.resources)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

अटल व्योम मुक्त_rd_atomic_resources(काष्ठा rxe_qp *qp)
अणु
	अगर (qp->resp.resources) अणु
		पूर्णांक i;

		क्रम (i = 0; i < qp->attr.max_dest_rd_atomic; i++) अणु
			काष्ठा resp_res *res = &qp->resp.resources[i];

			मुक्त_rd_atomic_resource(qp, res);
		पूर्ण
		kमुक्त(qp->resp.resources);
		qp->resp.resources = शून्य;
	पूर्ण
पूर्ण

व्योम मुक्त_rd_atomic_resource(काष्ठा rxe_qp *qp, काष्ठा resp_res *res)
अणु
	अगर (res->type == RXE_ATOMIC_MASK) अणु
		rxe_drop_ref(qp);
		kमुक्त_skb(res->atomic.skb);
	पूर्ण अन्यथा अगर (res->type == RXE_READ_MASK) अणु
		अगर (res->पढ़ो.mr)
			rxe_drop_ref(res->पढ़ो.mr);
	पूर्ण
	res->type = 0;
पूर्ण

अटल व्योम cleanup_rd_atomic_resources(काष्ठा rxe_qp *qp)
अणु
	पूर्णांक i;
	काष्ठा resp_res *res;

	अगर (qp->resp.resources) अणु
		क्रम (i = 0; i < qp->attr.max_dest_rd_atomic; i++) अणु
			res = &qp->resp.resources[i];
			मुक्त_rd_atomic_resource(qp, res);
		पूर्ण
	पूर्ण
पूर्ण

अटल व्योम rxe_qp_init_misc(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
			     काष्ठा ib_qp_init_attr *init)
अणु
	काष्ठा rxe_port *port;
	u32 qpn;

	qp->sq_sig_type		= init->sq_sig_type;
	qp->attr.path_mtu	= 1;
	qp->mtu			= ib_mtu_क्रमागत_to_पूर्णांक(qp->attr.path_mtu);

	qpn			= qp->pelem.index;
	port			= &rxe->port;

	चयन (init->qp_type) अणु
	हाल IB_QPT_SMI:
		qp->ibqp.qp_num		= 0;
		port->qp_smi_index	= qpn;
		qp->attr.port_num	= init->port_num;
		अवरोध;

	हाल IB_QPT_GSI:
		qp->ibqp.qp_num		= 1;
		port->qp_gsi_index	= qpn;
		qp->attr.port_num	= init->port_num;
		अवरोध;

	शेष:
		qp->ibqp.qp_num		= qpn;
		अवरोध;
	पूर्ण

	INIT_LIST_HEAD(&qp->grp_list);

	skb_queue_head_init(&qp->send_pkts);

	spin_lock_init(&qp->grp_lock);
	spin_lock_init(&qp->state_lock);

	atomic_set(&qp->ssn, 0);
	atomic_set(&qp->skb_out, 0);
पूर्ण

अटल पूर्णांक rxe_qp_init_req(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
			   काष्ठा ib_qp_init_attr *init, काष्ठा ib_udata *udata,
			   काष्ठा rxe_create_qp_resp __user *uresp)
अणु
	पूर्णांक err;
	पूर्णांक wqe_size;

	err = sock_create_kern(&init_net, AF_INET, SOCK_DGRAM, 0, &qp->sk);
	अगर (err < 0)
		वापस err;
	qp->sk->sk->sk_user_data = qp;

	/* pick a source UDP port number क्रम this QP based on
	 * the source QPN. this spपढ़ोs traffic क्रम dअगरferent QPs
	 * across dअगरferent NIC RX queues (जबतक using a single
	 * flow क्रम a given QP to मुख्यtain packet order).
	 * the port number must be in the Dynamic Ports range
	 * (0xc000 - 0xffff).
	 */
	qp->src_port = RXE_ROCE_V2_SPORT +
		(hash_32_generic(qp_num(qp), 14) & 0x3fff);
	qp->sq.max_wr		= init->cap.max_send_wr;

	/* These caps are limited by rxe_qp_chk_cap() करोne by the caller */
	wqe_size = max_t(पूर्णांक, init->cap.max_send_sge * माप(काष्ठा ib_sge),
			 init->cap.max_अंतरभूत_data);
	qp->sq.max_sge = init->cap.max_send_sge =
		wqe_size / माप(काष्ठा ib_sge);
	qp->sq.max_अंतरभूत = init->cap.max_अंतरभूत_data = wqe_size;
	wqe_size += माप(काष्ठा rxe_send_wqe);

	qp->sq.queue = rxe_queue_init(rxe, &qp->sq.max_wr, wqe_size);
	अगर (!qp->sq.queue)
		वापस -ENOMEM;

	err = करो_mmap_info(rxe, uresp ? &uresp->sq_mi : शून्य, udata,
			   qp->sq.queue->buf, qp->sq.queue->buf_size,
			   &qp->sq.queue->ip);

	अगर (err) अणु
		vमुक्त(qp->sq.queue->buf);
		kमुक्त(qp->sq.queue);
		qp->sq.queue = शून्य;
		वापस err;
	पूर्ण

	qp->req.wqe_index	= producer_index(qp->sq.queue);
	qp->req.state		= QP_STATE_RESET;
	qp->req.opcode		= -1;
	qp->comp.opcode		= -1;

	spin_lock_init(&qp->sq.sq_lock);
	skb_queue_head_init(&qp->req_pkts);

	rxe_init_task(rxe, &qp->req.task, qp,
		      rxe_requester, "req");
	rxe_init_task(rxe, &qp->comp.task, qp,
		      rxe_completer, "comp");

	qp->qp_समयout_jअगरfies = 0; /* Can't be set क्रम UD/UC in modअगरy_qp */
	अगर (init->qp_type == IB_QPT_RC) अणु
		समयr_setup(&qp->rnr_nak_समयr, rnr_nak_समयr, 0);
		समयr_setup(&qp->retrans_समयr, retransmit_समयr, 0);
	पूर्ण
	वापस 0;
पूर्ण

अटल पूर्णांक rxe_qp_init_resp(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
			    काष्ठा ib_qp_init_attr *init,
			    काष्ठा ib_udata *udata,
			    काष्ठा rxe_create_qp_resp __user *uresp)
अणु
	पूर्णांक err;
	पूर्णांक wqe_size;

	अगर (!qp->srq) अणु
		qp->rq.max_wr		= init->cap.max_recv_wr;
		qp->rq.max_sge		= init->cap.max_recv_sge;

		wqe_size = rcv_wqe_size(qp->rq.max_sge);

		pr_debug("qp#%d max_wr = %d, max_sge = %d, wqe_size = %d\n",
			 qp_num(qp), qp->rq.max_wr, qp->rq.max_sge, wqe_size);

		qp->rq.queue = rxe_queue_init(rxe,
					      &qp->rq.max_wr,
					      wqe_size);
		अगर (!qp->rq.queue)
			वापस -ENOMEM;

		err = करो_mmap_info(rxe, uresp ? &uresp->rq_mi : शून्य, udata,
				   qp->rq.queue->buf, qp->rq.queue->buf_size,
				   &qp->rq.queue->ip);
		अगर (err) अणु
			vमुक्त(qp->rq.queue->buf);
			kमुक्त(qp->rq.queue);
			qp->rq.queue = शून्य;
			वापस err;
		पूर्ण
	पूर्ण

	spin_lock_init(&qp->rq.producer_lock);
	spin_lock_init(&qp->rq.consumer_lock);

	skb_queue_head_init(&qp->resp_pkts);

	rxe_init_task(rxe, &qp->resp.task, qp,
		      rxe_responder, "resp");

	qp->resp.opcode		= OPCODE_NONE;
	qp->resp.msn		= 0;
	qp->resp.state		= QP_STATE_RESET;

	वापस 0;
पूर्ण

/* called by the create qp verb */
पूर्णांक rxe_qp_from_init(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp, काष्ठा rxe_pd *pd,
		     काष्ठा ib_qp_init_attr *init,
		     काष्ठा rxe_create_qp_resp __user *uresp,
		     काष्ठा ib_pd *ibpd,
		     काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;
	काष्ठा rxe_cq *rcq = to_rcq(init->recv_cq);
	काष्ठा rxe_cq *scq = to_rcq(init->send_cq);
	काष्ठा rxe_srq *srq = init->srq ? to_rsrq(init->srq) : शून्य;

	rxe_add_ref(pd);
	rxe_add_ref(rcq);
	rxe_add_ref(scq);
	अगर (srq)
		rxe_add_ref(srq);

	qp->pd			= pd;
	qp->rcq			= rcq;
	qp->scq			= scq;
	qp->srq			= srq;

	rxe_qp_init_misc(rxe, qp, init);

	err = rxe_qp_init_req(rxe, qp, init, udata, uresp);
	अगर (err)
		जाओ err1;

	err = rxe_qp_init_resp(rxe, qp, init, udata, uresp);
	अगर (err)
		जाओ err2;

	qp->attr.qp_state = IB_QPS_RESET;
	qp->valid = 1;

	वापस 0;

err2:
	rxe_queue_cleanup(qp->sq.queue);
err1:
	qp->pd = शून्य;
	qp->rcq = शून्य;
	qp->scq = शून्य;
	qp->srq = शून्य;

	अगर (srq)
		rxe_drop_ref(srq);
	rxe_drop_ref(scq);
	rxe_drop_ref(rcq);
	rxe_drop_ref(pd);

	वापस err;
पूर्ण

/* called by the query qp verb */
पूर्णांक rxe_qp_to_init(काष्ठा rxe_qp *qp, काष्ठा ib_qp_init_attr *init)
अणु
	init->event_handler		= qp->ibqp.event_handler;
	init->qp_context		= qp->ibqp.qp_context;
	init->send_cq			= qp->ibqp.send_cq;
	init->recv_cq			= qp->ibqp.recv_cq;
	init->srq			= qp->ibqp.srq;

	init->cap.max_send_wr		= qp->sq.max_wr;
	init->cap.max_send_sge		= qp->sq.max_sge;
	init->cap.max_अंतरभूत_data	= qp->sq.max_अंतरभूत;

	अगर (!qp->srq) अणु
		init->cap.max_recv_wr		= qp->rq.max_wr;
		init->cap.max_recv_sge		= qp->rq.max_sge;
	पूर्ण

	init->sq_sig_type		= qp->sq_sig_type;

	init->qp_type			= qp->ibqp.qp_type;
	init->port_num			= 1;

	वापस 0;
पूर्ण

/* called by the modअगरy qp verb, this routine checks all the parameters beक्रमe
 * making any changes
 */
पूर्णांक rxe_qp_chk_attr(काष्ठा rxe_dev *rxe, काष्ठा rxe_qp *qp,
		    काष्ठा ib_qp_attr *attr, पूर्णांक mask)
अणु
	क्रमागत ib_qp_state cur_state = (mask & IB_QP_CUR_STATE) ?
					attr->cur_qp_state : qp->attr.qp_state;
	क्रमागत ib_qp_state new_state = (mask & IB_QP_STATE) ?
					attr->qp_state : cur_state;

	अगर (!ib_modअगरy_qp_is_ok(cur_state, new_state, qp_type(qp), mask)) अणु
		pr_warn("invalid mask or state for qp\n");
		जाओ err1;
	पूर्ण

	अगर (mask & IB_QP_STATE) अणु
		अगर (cur_state == IB_QPS_SQD) अणु
			अगर (qp->req.state == QP_STATE_DRAIN &&
			    new_state != IB_QPS_ERR)
				जाओ err1;
		पूर्ण
	पूर्ण

	अगर (mask & IB_QP_PORT) अणु
		अगर (!rdma_is_port_valid(&rxe->ib_dev, attr->port_num)) अणु
			pr_warn("invalid port %d\n", attr->port_num);
			जाओ err1;
		पूर्ण
	पूर्ण

	अगर (mask & IB_QP_CAP && rxe_qp_chk_cap(rxe, &attr->cap, !!qp->srq))
		जाओ err1;

	अगर (mask & IB_QP_AV && rxe_av_chk_attr(rxe, &attr->ah_attr))
		जाओ err1;

	अगर (mask & IB_QP_ALT_PATH) अणु
		अगर (rxe_av_chk_attr(rxe, &attr->alt_ah_attr))
			जाओ err1;
		अगर (!rdma_is_port_valid(&rxe->ib_dev, attr->alt_port_num))  अणु
			pr_warn("invalid alt port %d\n", attr->alt_port_num);
			जाओ err1;
		पूर्ण
		अगर (attr->alt_समयout > 31) अणु
			pr_warn("invalid QP alt timeout %d > 31\n",
				attr->alt_समयout);
			जाओ err1;
		पूर्ण
	पूर्ण

	अगर (mask & IB_QP_PATH_MTU) अणु
		काष्ठा rxe_port *port = &rxe->port;

		क्रमागत ib_mtu max_mtu = port->attr.max_mtu;
		क्रमागत ib_mtu mtu = attr->path_mtu;

		अगर (mtu > max_mtu) अणु
			pr_debug("invalid mtu (%d) > (%d)\n",
				 ib_mtu_क्रमागत_to_पूर्णांक(mtu),
				 ib_mtu_क्रमागत_to_पूर्णांक(max_mtu));
			जाओ err1;
		पूर्ण
	पूर्ण

	अगर (mask & IB_QP_MAX_QP_RD_ATOMIC) अणु
		अगर (attr->max_rd_atomic > rxe->attr.max_qp_rd_atom) अणु
			pr_warn("invalid max_rd_atomic %d > %d\n",
				attr->max_rd_atomic,
				rxe->attr.max_qp_rd_atom);
			जाओ err1;
		पूर्ण
	पूर्ण

	अगर (mask & IB_QP_TIMEOUT) अणु
		अगर (attr->समयout > 31) अणु
			pr_warn("invalid QP timeout %d > 31\n",
				attr->समयout);
			जाओ err1;
		पूर्ण
	पूर्ण

	वापस 0;

err1:
	वापस -EINVAL;
पूर्ण

/* move the qp to the reset state */
अटल व्योम rxe_qp_reset(काष्ठा rxe_qp *qp)
अणु
	/* stop tasks from running */
	rxe_disable_task(&qp->resp.task);

	/* stop request/comp */
	अगर (qp->sq.queue) अणु
		अगर (qp_type(qp) == IB_QPT_RC)
			rxe_disable_task(&qp->comp.task);
		rxe_disable_task(&qp->req.task);
	पूर्ण

	/* move qp to the reset state */
	qp->req.state = QP_STATE_RESET;
	qp->resp.state = QP_STATE_RESET;

	/* let state machines reset themselves drain work and packet queues
	 * etc.
	 */
	__rxe_करो_task(&qp->resp.task);

	अगर (qp->sq.queue) अणु
		__rxe_करो_task(&qp->comp.task);
		__rxe_करो_task(&qp->req.task);
		rxe_queue_reset(qp->sq.queue);
	पूर्ण

	/* cleanup attributes */
	atomic_set(&qp->ssn, 0);
	qp->req.opcode = -1;
	qp->req.need_retry = 0;
	qp->req.noack_pkts = 0;
	qp->resp.msn = 0;
	qp->resp.opcode = -1;
	qp->resp.drop_msg = 0;
	qp->resp.जाओ_error = 0;
	qp->resp.sent_psn_nak = 0;

	अगर (qp->resp.mr) अणु
		rxe_drop_ref(qp->resp.mr);
		qp->resp.mr = शून्य;
	पूर्ण

	cleanup_rd_atomic_resources(qp);

	/* reenable tasks */
	rxe_enable_task(&qp->resp.task);

	अगर (qp->sq.queue) अणु
		अगर (qp_type(qp) == IB_QPT_RC)
			rxe_enable_task(&qp->comp.task);

		rxe_enable_task(&qp->req.task);
	पूर्ण
पूर्ण

/* drain the send queue */
अटल व्योम rxe_qp_drain(काष्ठा rxe_qp *qp)
अणु
	अगर (qp->sq.queue) अणु
		अगर (qp->req.state != QP_STATE_DRAINED) अणु
			qp->req.state = QP_STATE_DRAIN;
			अगर (qp_type(qp) == IB_QPT_RC)
				rxe_run_task(&qp->comp.task, 1);
			अन्यथा
				__rxe_करो_task(&qp->comp.task);
			rxe_run_task(&qp->req.task, 1);
		पूर्ण
	पूर्ण
पूर्ण

/* move the qp to the error state */
व्योम rxe_qp_error(काष्ठा rxe_qp *qp)
अणु
	qp->req.state = QP_STATE_ERROR;
	qp->resp.state = QP_STATE_ERROR;
	qp->attr.qp_state = IB_QPS_ERR;

	/* drain work and packet queues */
	rxe_run_task(&qp->resp.task, 1);

	अगर (qp_type(qp) == IB_QPT_RC)
		rxe_run_task(&qp->comp.task, 1);
	अन्यथा
		__rxe_करो_task(&qp->comp.task);
	rxe_run_task(&qp->req.task, 1);
पूर्ण

/* called by the modअगरy qp verb */
पूर्णांक rxe_qp_from_attr(काष्ठा rxe_qp *qp, काष्ठा ib_qp_attr *attr, पूर्णांक mask,
		     काष्ठा ib_udata *udata)
अणु
	पूर्णांक err;

	अगर (mask & IB_QP_MAX_QP_RD_ATOMIC) अणु
		पूर्णांक max_rd_atomic = attr->max_rd_atomic ?
			roundup_घात_of_two(attr->max_rd_atomic) : 0;

		qp->attr.max_rd_atomic = max_rd_atomic;
		atomic_set(&qp->req.rd_atomic, max_rd_atomic);
	पूर्ण

	अगर (mask & IB_QP_MAX_DEST_RD_ATOMIC) अणु
		पूर्णांक max_dest_rd_atomic = attr->max_dest_rd_atomic ?
			roundup_घात_of_two(attr->max_dest_rd_atomic) : 0;

		qp->attr.max_dest_rd_atomic = max_dest_rd_atomic;

		मुक्त_rd_atomic_resources(qp);

		err = alloc_rd_atomic_resources(qp, max_dest_rd_atomic);
		अगर (err)
			वापस err;
	पूर्ण

	अगर (mask & IB_QP_CUR_STATE)
		qp->attr.cur_qp_state = attr->qp_state;

	अगर (mask & IB_QP_EN_SQD_ASYNC_NOTIFY)
		qp->attr.en_sqd_async_notअगरy = attr->en_sqd_async_notअगरy;

	अगर (mask & IB_QP_ACCESS_FLAGS)
		qp->attr.qp_access_flags = attr->qp_access_flags;

	अगर (mask & IB_QP_PKEY_INDEX)
		qp->attr.pkey_index = attr->pkey_index;

	अगर (mask & IB_QP_PORT)
		qp->attr.port_num = attr->port_num;

	अगर (mask & IB_QP_QKEY)
		qp->attr.qkey = attr->qkey;

	अगर (mask & IB_QP_AV)
		rxe_init_av(&attr->ah_attr, &qp->pri_av);

	अगर (mask & IB_QP_ALT_PATH) अणु
		rxe_init_av(&attr->alt_ah_attr, &qp->alt_av);
		qp->attr.alt_port_num = attr->alt_port_num;
		qp->attr.alt_pkey_index = attr->alt_pkey_index;
		qp->attr.alt_समयout = attr->alt_समयout;
	पूर्ण

	अगर (mask & IB_QP_PATH_MTU) अणु
		qp->attr.path_mtu = attr->path_mtu;
		qp->mtu = ib_mtu_क्रमागत_to_पूर्णांक(attr->path_mtu);
	पूर्ण

	अगर (mask & IB_QP_TIMEOUT) अणु
		qp->attr.समयout = attr->समयout;
		अगर (attr->समयout == 0) अणु
			qp->qp_समयout_jअगरfies = 0;
		पूर्ण अन्यथा अणु
			/* According to the spec, समयout = 4.096 * 2 ^ attr->समयout [us] */
			पूर्णांक j = nsecs_to_jअगरfies(4096ULL << attr->समयout);

			qp->qp_समयout_jअगरfies = j ? j : 1;
		पूर्ण
	पूर्ण

	अगर (mask & IB_QP_RETRY_CNT) अणु
		qp->attr.retry_cnt = attr->retry_cnt;
		qp->comp.retry_cnt = attr->retry_cnt;
		pr_debug("qp#%d set retry count = %d\n", qp_num(qp),
			 attr->retry_cnt);
	पूर्ण

	अगर (mask & IB_QP_RNR_RETRY) अणु
		qp->attr.rnr_retry = attr->rnr_retry;
		qp->comp.rnr_retry = attr->rnr_retry;
		pr_debug("qp#%d set rnr retry count = %d\n", qp_num(qp),
			 attr->rnr_retry);
	पूर्ण

	अगर (mask & IB_QP_RQ_PSN) अणु
		qp->attr.rq_psn = (attr->rq_psn & BTH_PSN_MASK);
		qp->resp.psn = qp->attr.rq_psn;
		pr_debug("qp#%d set resp psn = 0x%x\n", qp_num(qp),
			 qp->resp.psn);
	पूर्ण

	अगर (mask & IB_QP_MIN_RNR_TIMER) अणु
		qp->attr.min_rnr_समयr = attr->min_rnr_समयr;
		pr_debug("qp#%d set min rnr timer = 0x%x\n", qp_num(qp),
			 attr->min_rnr_समयr);
	पूर्ण

	अगर (mask & IB_QP_SQ_PSN) अणु
		qp->attr.sq_psn = (attr->sq_psn & BTH_PSN_MASK);
		qp->req.psn = qp->attr.sq_psn;
		qp->comp.psn = qp->attr.sq_psn;
		pr_debug("qp#%d set req psn = 0x%x\n", qp_num(qp), qp->req.psn);
	पूर्ण

	अगर (mask & IB_QP_PATH_MIG_STATE)
		qp->attr.path_mig_state = attr->path_mig_state;

	अगर (mask & IB_QP_DEST_QPN)
		qp->attr.dest_qp_num = attr->dest_qp_num;

	अगर (mask & IB_QP_STATE) अणु
		qp->attr.qp_state = attr->qp_state;

		चयन (attr->qp_state) अणु
		हाल IB_QPS_RESET:
			pr_debug("qp#%d state -> RESET\n", qp_num(qp));
			rxe_qp_reset(qp);
			अवरोध;

		हाल IB_QPS_INIT:
			pr_debug("qp#%d state -> INIT\n", qp_num(qp));
			qp->req.state = QP_STATE_INIT;
			qp->resp.state = QP_STATE_INIT;
			अवरोध;

		हाल IB_QPS_RTR:
			pr_debug("qp#%d state -> RTR\n", qp_num(qp));
			qp->resp.state = QP_STATE_READY;
			अवरोध;

		हाल IB_QPS_RTS:
			pr_debug("qp#%d state -> RTS\n", qp_num(qp));
			qp->req.state = QP_STATE_READY;
			अवरोध;

		हाल IB_QPS_SQD:
			pr_debug("qp#%d state -> SQD\n", qp_num(qp));
			rxe_qp_drain(qp);
			अवरोध;

		हाल IB_QPS_SQE:
			pr_warn("qp#%d state -> SQE !!?\n", qp_num(qp));
			/* Not possible from modअगरy_qp. */
			अवरोध;

		हाल IB_QPS_ERR:
			pr_debug("qp#%d state -> ERR\n", qp_num(qp));
			rxe_qp_error(qp);
			अवरोध;
		पूर्ण
	पूर्ण

	वापस 0;
पूर्ण

/* called by the query qp verb */
पूर्णांक rxe_qp_to_attr(काष्ठा rxe_qp *qp, काष्ठा ib_qp_attr *attr, पूर्णांक mask)
अणु
	*attr = qp->attr;

	attr->rq_psn				= qp->resp.psn;
	attr->sq_psn				= qp->req.psn;

	attr->cap.max_send_wr			= qp->sq.max_wr;
	attr->cap.max_send_sge			= qp->sq.max_sge;
	attr->cap.max_अंतरभूत_data		= qp->sq.max_अंतरभूत;

	अगर (!qp->srq) अणु
		attr->cap.max_recv_wr		= qp->rq.max_wr;
		attr->cap.max_recv_sge		= qp->rq.max_sge;
	पूर्ण

	rxe_av_to_attr(&qp->pri_av, &attr->ah_attr);
	rxe_av_to_attr(&qp->alt_av, &attr->alt_ah_attr);

	अगर (qp->req.state == QP_STATE_DRAIN) अणु
		attr->sq_draining = 1;
		/* applications that get this state
		 * typically spin on it. yield the
		 * processor
		 */
		cond_resched();
	पूर्ण अन्यथा अणु
		attr->sq_draining = 0;
	पूर्ण

	pr_debug("attr->sq_draining = %d\n", attr->sq_draining);

	वापस 0;
पूर्ण

/* called by the destroy qp verb */
व्योम rxe_qp_destroy(काष्ठा rxe_qp *qp)
अणु
	qp->valid = 0;
	qp->qp_समयout_jअगरfies = 0;
	rxe_cleanup_task(&qp->resp.task);

	अगर (qp_type(qp) == IB_QPT_RC) अणु
		del_समयr_sync(&qp->retrans_समयr);
		del_समयr_sync(&qp->rnr_nak_समयr);
	पूर्ण

	rxe_cleanup_task(&qp->req.task);
	rxe_cleanup_task(&qp->comp.task);

	/* flush out any receive wr's or pending requests */
	__rxe_करो_task(&qp->req.task);
	अगर (qp->sq.queue) अणु
		__rxe_करो_task(&qp->comp.task);
		__rxe_करो_task(&qp->req.task);
	पूर्ण
पूर्ण

/* called when the last reference to the qp is dropped */
अटल व्योम rxe_qp_करो_cleanup(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rxe_qp *qp = container_of(work, typeof(*qp), cleanup_work.work);

	rxe_drop_all_mcast_groups(qp);

	अगर (qp->sq.queue)
		rxe_queue_cleanup(qp->sq.queue);

	अगर (qp->srq)
		rxe_drop_ref(qp->srq);

	अगर (qp->rq.queue)
		rxe_queue_cleanup(qp->rq.queue);

	अगर (qp->scq)
		rxe_drop_ref(qp->scq);
	अगर (qp->rcq)
		rxe_drop_ref(qp->rcq);
	अगर (qp->pd)
		rxe_drop_ref(qp->pd);

	अगर (qp->resp.mr) अणु
		rxe_drop_ref(qp->resp.mr);
		qp->resp.mr = शून्य;
	पूर्ण

	अगर (qp_type(qp) == IB_QPT_RC)
		sk_dst_reset(qp->sk->sk);

	मुक्त_rd_atomic_resources(qp);

	kernel_sock_shutकरोwn(qp->sk, SHUT_RDWR);
	sock_release(qp->sk);
पूर्ण

/* called when the last reference to the qp is dropped */
व्योम rxe_qp_cleanup(काष्ठा rxe_pool_entry *arg)
अणु
	काष्ठा rxe_qp *qp = container_of(arg, typeof(*qp), pelem);

	execute_in_process_context(rxe_qp_करो_cleanup, &qp->cleanup_work);
पूर्ण
