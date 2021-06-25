<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2015-2018 Oracle. All rights reserved.
 * Copyright (c) 2014 Open Grid Computing, Inc. All rights reserved.
 * Copyright (c) 2005-2007 Network Appliance, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the BSD-type
 * license below:
 *
 * Redistribution and use in source and binary क्रमms, with or without
 * modअगरication, are permitted provided that the following conditions
 * are met:
 *
 *      Redistributions of source code must retain the above copyright
 *      notice, this list of conditions and the following disclaimer.
 *
 *      Redistributions in binary क्रमm must reproduce the above
 *      copyright notice, this list of conditions and the following
 *      disclaimer in the करोcumentation and/or other materials provided
 *      with the distribution.
 *
 *      Neither the name of the Network Appliance, Inc. nor the names of
 *      its contributors may be used to enकरोrse or promote products
 *      derived from this software without specअगरic prior written
 *      permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY सूचीECT, INसूचीECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * Author: Tom Tucker <tom@खोलोgridcomputing.com>
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/sched.h>
#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <linux/workqueue.h>
#समावेश <linux/export.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>
#समावेश <rdma/rw.h>

#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/debug.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

#घोषणा RPCDBG_FACILITY	RPCDBG_SVCXPRT

अटल काष्ठा svcxprt_rdma *svc_rdma_create_xprt(काष्ठा svc_serv *serv,
						 काष्ठा net *net);
अटल काष्ठा svc_xprt *svc_rdma_create(काष्ठा svc_serv *serv,
					काष्ठा net *net,
					काष्ठा sockaddr *sa, पूर्णांक salen,
					पूर्णांक flags);
अटल काष्ठा svc_xprt *svc_rdma_accept(काष्ठा svc_xprt *xprt);
अटल व्योम svc_rdma_detach(काष्ठा svc_xprt *xprt);
अटल व्योम svc_rdma_मुक्त(काष्ठा svc_xprt *xprt);
अटल पूर्णांक svc_rdma_has_wspace(काष्ठा svc_xprt *xprt);
अटल व्योम svc_rdma_secure_port(काष्ठा svc_rqst *);
अटल व्योम svc_rdma_समाप्त_temp_xprt(काष्ठा svc_xprt *);

अटल स्थिर काष्ठा svc_xprt_ops svc_rdma_ops = अणु
	.xpo_create = svc_rdma_create,
	.xpo_recvfrom = svc_rdma_recvfrom,
	.xpo_sendto = svc_rdma_sendto,
	.xpo_result_payload = svc_rdma_result_payload,
	.xpo_release_rqst = svc_rdma_release_rqst,
	.xpo_detach = svc_rdma_detach,
	.xpo_मुक्त = svc_rdma_मुक्त,
	.xpo_has_wspace = svc_rdma_has_wspace,
	.xpo_accept = svc_rdma_accept,
	.xpo_secure_port = svc_rdma_secure_port,
	.xpo_समाप्त_temp_xprt = svc_rdma_समाप्त_temp_xprt,
पूर्ण;

काष्ठा svc_xprt_class svc_rdma_class = अणु
	.xcl_name = "rdma",
	.xcl_owner = THIS_MODULE,
	.xcl_ops = &svc_rdma_ops,
	.xcl_max_payload = RPCSVC_MAXPAYLOAD_RDMA,
	.xcl_ident = XPRT_TRANSPORT_RDMA,
पूर्ण;

/* QP event handler */
अटल व्योम qp_event_handler(काष्ठा ib_event *event, व्योम *context)
अणु
	काष्ठा svc_xprt *xprt = context;

	trace_svcrdma_qp_error(event, (काष्ठा sockaddr *)&xprt->xpt_remote);
	चयन (event->event) अणु
	/* These are considered benign events */
	हाल IB_EVENT_PATH_MIG:
	हाल IB_EVENT_COMM_EST:
	हाल IB_EVENT_SQ_DRAINED:
	हाल IB_EVENT_QP_LAST_WQE_REACHED:
		अवरोध;

	/* These are considered fatal events */
	हाल IB_EVENT_PATH_MIG_ERR:
	हाल IB_EVENT_QP_FATAL:
	हाल IB_EVENT_QP_REQ_ERR:
	हाल IB_EVENT_QP_ACCESS_ERR:
	हाल IB_EVENT_DEVICE_FATAL:
	शेष:
		svc_xprt_deferred_बंद(xprt);
		अवरोध;
	पूर्ण
पूर्ण

अटल काष्ठा svcxprt_rdma *svc_rdma_create_xprt(काष्ठा svc_serv *serv,
						 काष्ठा net *net)
अणु
	काष्ठा svcxprt_rdma *cma_xprt = kzalloc(माप *cma_xprt, GFP_KERNEL);

	अगर (!cma_xprt) अणु
		dprपूर्णांकk("svcrdma: failed to create new transport\n");
		वापस शून्य;
	पूर्ण
	svc_xprt_init(net, &svc_rdma_class, &cma_xprt->sc_xprt, serv);
	INIT_LIST_HEAD(&cma_xprt->sc_accept_q);
	INIT_LIST_HEAD(&cma_xprt->sc_rq_dto_q);
	INIT_LIST_HEAD(&cma_xprt->sc_send_ctxts);
	init_llist_head(&cma_xprt->sc_recv_ctxts);
	INIT_LIST_HEAD(&cma_xprt->sc_rw_ctxts);
	init_रुकोqueue_head(&cma_xprt->sc_send_रुको);

	spin_lock_init(&cma_xprt->sc_lock);
	spin_lock_init(&cma_xprt->sc_rq_dto_lock);
	spin_lock_init(&cma_xprt->sc_send_lock);
	spin_lock_init(&cma_xprt->sc_rw_ctxt_lock);

	/*
	 * Note that this implies that the underlying transport support
	 * has some क्रमm of congestion control (see RFC 7530 section 3.1
	 * paragraph 2). For now, we assume that all supported RDMA
	 * transports are suitable here.
	 */
	set_bit(XPT_CONG_CTRL, &cma_xprt->sc_xprt.xpt_flags);

	वापस cma_xprt;
पूर्ण

अटल व्योम
svc_rdma_parse_connect_निजी(काष्ठा svcxprt_rdma *newxprt,
			       काष्ठा rdma_conn_param *param)
अणु
	स्थिर काष्ठा rpcrdma_connect_निजी *pmsg = param->निजी_data;

	अगर (pmsg &&
	    pmsg->cp_magic == rpcrdma_cmp_magic &&
	    pmsg->cp_version == RPCRDMA_CMP_VERSION) अणु
		newxprt->sc_snd_w_inv = pmsg->cp_flags &
					RPCRDMA_CMP_F_SND_W_INV_OK;

		dprपूर्णांकk("svcrdma: client send_size %u, recv_size %u "
			"remote inv %ssupported\n",
			rpcrdma_decode_buffer_size(pmsg->cp_send_size),
			rpcrdma_decode_buffer_size(pmsg->cp_recv_size),
			newxprt->sc_snd_w_inv ? "" : "un");
	पूर्ण
पूर्ण

/*
 * This function handles the CONNECT_REQUEST event on a listening
 * endpoपूर्णांक. It is passed the cma_id क्रम the _new_ connection. The context in
 * this cma_id is inherited from the listening cma_id and is the svc_xprt
 * काष्ठाure क्रम the listening endpoपूर्णांक.
 *
 * This function creates a new xprt क्रम the new connection and enqueues it on
 * the accept queue क्रम the listent xprt. When the listen thपढ़ो is kicked, it
 * will call the recvfrom method on the listen xprt which will accept the new
 * connection.
 */
अटल व्योम handle_connect_req(काष्ठा rdma_cm_id *new_cma_id,
			       काष्ठा rdma_conn_param *param)
अणु
	काष्ठा svcxprt_rdma *listen_xprt = new_cma_id->context;
	काष्ठा svcxprt_rdma *newxprt;
	काष्ठा sockaddr *sa;

	/* Create a new transport */
	newxprt = svc_rdma_create_xprt(listen_xprt->sc_xprt.xpt_server,
				       listen_xprt->sc_xprt.xpt_net);
	अगर (!newxprt)
		वापस;
	newxprt->sc_cm_id = new_cma_id;
	new_cma_id->context = newxprt;
	svc_rdma_parse_connect_निजी(newxprt, param);

	/* Save client advertised inbound पढ़ो limit क्रम use later in accept. */
	newxprt->sc_ord = param->initiator_depth;

	sa = (काष्ठा sockaddr *)&newxprt->sc_cm_id->route.addr.dst_addr;
	newxprt->sc_xprt.xpt_remotelen = svc_addr_len(sa);
	स_नकल(&newxprt->sc_xprt.xpt_remote, sa,
	       newxprt->sc_xprt.xpt_remotelen);
	snम_लिखो(newxprt->sc_xprt.xpt_remotebuf,
		 माप(newxprt->sc_xprt.xpt_remotebuf) - 1, "%pISc", sa);

	/* The remote port is arbitrary and not under the control of the
	 * client ULP. Set it to a fixed value so that the DRC जारीs
	 * to be effective after a reconnect.
	 */
	rpc_set_port((काष्ठा sockaddr *)&newxprt->sc_xprt.xpt_remote, 0);

	sa = (काष्ठा sockaddr *)&newxprt->sc_cm_id->route.addr.src_addr;
	svc_xprt_set_local(&newxprt->sc_xprt, sa, svc_addr_len(sa));

	/*
	 * Enqueue the new transport on the accept queue of the listening
	 * transport
	 */
	spin_lock(&listen_xprt->sc_lock);
	list_add_tail(&newxprt->sc_accept_q, &listen_xprt->sc_accept_q);
	spin_unlock(&listen_xprt->sc_lock);

	set_bit(XPT_CONN, &listen_xprt->sc_xprt.xpt_flags);
	svc_xprt_enqueue(&listen_xprt->sc_xprt);
पूर्ण

/**
 * svc_rdma_listen_handler - Handle CM events generated on a listening endpoपूर्णांक
 * @cma_id: the server's listener rdma_cm_id
 * @event: details of the event
 *
 * Return values:
 *     %0: Do not destroy @cma_id
 *     %1: Destroy @cma_id (never वापसed here)
 *
 * NB: There is never a DEVICE_REMOVAL event क्रम INADDR_ANY listeners.
 */
अटल पूर्णांक svc_rdma_listen_handler(काष्ठा rdma_cm_id *cma_id,
				   काष्ठा rdma_cm_event *event)
अणु
	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_CONNECT_REQUEST:
		handle_connect_req(cma_id, &event->param.conn);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/**
 * svc_rdma_cma_handler - Handle CM events on client connections
 * @cma_id: the server's listener rdma_cm_id
 * @event: details of the event
 *
 * Return values:
 *     %0: Do not destroy @cma_id
 *     %1: Destroy @cma_id (never वापसed here)
 */
अटल पूर्णांक svc_rdma_cma_handler(काष्ठा rdma_cm_id *cma_id,
				काष्ठा rdma_cm_event *event)
अणु
	काष्ठा svcxprt_rdma *rdma = cma_id->context;
	काष्ठा svc_xprt *xprt = &rdma->sc_xprt;

	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_ESTABLISHED:
		clear_bit(RDMAXPRT_CONN_PENDING, &rdma->sc_flags);

		/* Handle any requests that were received जबतक
		 * CONN_PENDING was set. */
		svc_xprt_enqueue(xprt);
		अवरोध;
	हाल RDMA_CM_EVENT_DISCONNECTED:
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		svc_xprt_deferred_बंद(xprt);
		अवरोध;
	शेष:
		अवरोध;
	पूर्ण
	वापस 0;
पूर्ण

/*
 * Create a listening RDMA service endpoपूर्णांक.
 */
अटल काष्ठा svc_xprt *svc_rdma_create(काष्ठा svc_serv *serv,
					काष्ठा net *net,
					काष्ठा sockaddr *sa, पूर्णांक salen,
					पूर्णांक flags)
अणु
	काष्ठा rdma_cm_id *listen_id;
	काष्ठा svcxprt_rdma *cma_xprt;
	पूर्णांक ret;

	अगर (sa->sa_family != AF_INET && sa->sa_family != AF_INET6)
		वापस ERR_PTR(-EAFNOSUPPORT);
	cma_xprt = svc_rdma_create_xprt(serv, net);
	अगर (!cma_xprt)
		वापस ERR_PTR(-ENOMEM);
	set_bit(XPT_LISTENER, &cma_xprt->sc_xprt.xpt_flags);
	म_नकल(cma_xprt->sc_xprt.xpt_remotebuf, "listener");

	listen_id = rdma_create_id(net, svc_rdma_listen_handler, cma_xprt,
				   RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(listen_id)) अणु
		ret = PTR_ERR(listen_id);
		जाओ err0;
	पूर्ण

	/* Allow both IPv4 and IPv6 sockets to bind a single port
	 * at the same समय.
	 */
#अगर IS_ENABLED(CONFIG_IPV6)
	ret = rdma_set_afonly(listen_id, 1);
	अगर (ret)
		जाओ err1;
#पूर्ण_अगर
	ret = rdma_bind_addr(listen_id, sa);
	अगर (ret)
		जाओ err1;
	cma_xprt->sc_cm_id = listen_id;

	ret = rdma_listen(listen_id, RPCRDMA_LISTEN_BACKLOG);
	अगर (ret)
		जाओ err1;

	/*
	 * We need to use the address from the cm_id in हाल the
	 * caller specअगरied 0 क्रम the port number.
	 */
	sa = (काष्ठा sockaddr *)&cma_xprt->sc_cm_id->route.addr.src_addr;
	svc_xprt_set_local(&cma_xprt->sc_xprt, sa, salen);

	वापस &cma_xprt->sc_xprt;

 err1:
	rdma_destroy_id(listen_id);
 err0:
	kमुक्त(cma_xprt);
	वापस ERR_PTR(ret);
पूर्ण

/*
 * This is the xpo_recvfrom function क्रम listening endpoपूर्णांकs. Its
 * purpose is to accept incoming connections. The CMA callback handler
 * has alपढ़ोy created a new transport and attached it to the new CMA
 * ID.
 *
 * There is a queue of pending connections hung on the listening
 * transport. This queue contains the new svc_xprt काष्ठाure. This
 * function takes svc_xprt काष्ठाures off the accept_q and completes
 * the connection.
 */
अटल काष्ठा svc_xprt *svc_rdma_accept(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svcxprt_rdma *listen_rdma;
	काष्ठा svcxprt_rdma *newxprt = शून्य;
	काष्ठा rdma_conn_param conn_param;
	काष्ठा rpcrdma_connect_निजी pmsg;
	काष्ठा ib_qp_init_attr qp_attr;
	अचिन्हित पूर्णांक ctxts, rq_depth;
	काष्ठा ib_device *dev;
	पूर्णांक ret = 0;
	RPC_IFDEBUG(काष्ठा sockaddr *sap);

	listen_rdma = container_of(xprt, काष्ठा svcxprt_rdma, sc_xprt);
	clear_bit(XPT_CONN, &xprt->xpt_flags);
	/* Get the next entry off the accept list */
	spin_lock(&listen_rdma->sc_lock);
	अगर (!list_empty(&listen_rdma->sc_accept_q)) अणु
		newxprt = list_entry(listen_rdma->sc_accept_q.next,
				     काष्ठा svcxprt_rdma, sc_accept_q);
		list_del_init(&newxprt->sc_accept_q);
	पूर्ण
	अगर (!list_empty(&listen_rdma->sc_accept_q))
		set_bit(XPT_CONN, &listen_rdma->sc_xprt.xpt_flags);
	spin_unlock(&listen_rdma->sc_lock);
	अगर (!newxprt)
		वापस शून्य;

	dev = newxprt->sc_cm_id->device;
	newxprt->sc_port_num = newxprt->sc_cm_id->port_num;

	/* Qualअगरy the transport resource शेषs with the
	 * capabilities of this particular device */
	/* Transport header, head iovec, tail iovec */
	newxprt->sc_max_send_sges = 3;
	/* Add one SGE per page list entry */
	newxprt->sc_max_send_sges += (svcrdma_max_req_size / PAGE_SIZE) + 1;
	अगर (newxprt->sc_max_send_sges > dev->attrs.max_send_sge)
		newxprt->sc_max_send_sges = dev->attrs.max_send_sge;
	newxprt->sc_max_req_size = svcrdma_max_req_size;
	newxprt->sc_max_requests = svcrdma_max_requests;
	newxprt->sc_max_bc_requests = svcrdma_max_bc_requests;
	newxprt->sc_recv_batch = RPCRDMA_MAX_RECV_BATCH;
	rq_depth = newxprt->sc_max_requests + newxprt->sc_max_bc_requests +
		   newxprt->sc_recv_batch;
	अगर (rq_depth > dev->attrs.max_qp_wr) अणु
		pr_warn("svcrdma: reducing receive depth to %d\n",
			dev->attrs.max_qp_wr);
		rq_depth = dev->attrs.max_qp_wr;
		newxprt->sc_recv_batch = 1;
		newxprt->sc_max_requests = rq_depth - 2;
		newxprt->sc_max_bc_requests = 2;
	पूर्ण
	newxprt->sc_fc_credits = cpu_to_be32(newxprt->sc_max_requests);
	ctxts = rdma_rw_mr_factor(dev, newxprt->sc_port_num, RPCSVC_MAXPAGES);
	ctxts *= newxprt->sc_max_requests;
	newxprt->sc_sq_depth = rq_depth + ctxts;
	अगर (newxprt->sc_sq_depth > dev->attrs.max_qp_wr) अणु
		pr_warn("svcrdma: reducing send depth to %d\n",
			dev->attrs.max_qp_wr);
		newxprt->sc_sq_depth = dev->attrs.max_qp_wr;
	पूर्ण
	atomic_set(&newxprt->sc_sq_avail, newxprt->sc_sq_depth);

	newxprt->sc_pd = ib_alloc_pd(dev, 0);
	अगर (IS_ERR(newxprt->sc_pd)) अणु
		trace_svcrdma_pd_err(newxprt, PTR_ERR(newxprt->sc_pd));
		जाओ errout;
	पूर्ण
	newxprt->sc_sq_cq = ib_alloc_cq_any(dev, newxprt, newxprt->sc_sq_depth,
					    IB_POLL_WORKQUEUE);
	अगर (IS_ERR(newxprt->sc_sq_cq))
		जाओ errout;
	newxprt->sc_rq_cq =
		ib_alloc_cq_any(dev, newxprt, rq_depth, IB_POLL_WORKQUEUE);
	अगर (IS_ERR(newxprt->sc_rq_cq))
		जाओ errout;

	स_रखो(&qp_attr, 0, माप qp_attr);
	qp_attr.event_handler = qp_event_handler;
	qp_attr.qp_context = &newxprt->sc_xprt;
	qp_attr.port_num = newxprt->sc_port_num;
	qp_attr.cap.max_rdma_ctxs = ctxts;
	qp_attr.cap.max_send_wr = newxprt->sc_sq_depth - ctxts;
	qp_attr.cap.max_recv_wr = rq_depth;
	qp_attr.cap.max_send_sge = newxprt->sc_max_send_sges;
	qp_attr.cap.max_recv_sge = 1;
	qp_attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	qp_attr.qp_type = IB_QPT_RC;
	qp_attr.send_cq = newxprt->sc_sq_cq;
	qp_attr.recv_cq = newxprt->sc_rq_cq;
	dprपूर्णांकk("svcrdma: newxprt->sc_cm_id=%p, newxprt->sc_pd=%p\n",
		newxprt->sc_cm_id, newxprt->sc_pd);
	dprपूर्णांकk("    cap.max_send_wr = %d, cap.max_recv_wr = %d\n",
		qp_attr.cap.max_send_wr, qp_attr.cap.max_recv_wr);
	dprपूर्णांकk("    cap.max_send_sge = %d, cap.max_recv_sge = %d\n",
		qp_attr.cap.max_send_sge, qp_attr.cap.max_recv_sge);

	ret = rdma_create_qp(newxprt->sc_cm_id, newxprt->sc_pd, &qp_attr);
	अगर (ret) अणु
		trace_svcrdma_qp_err(newxprt, ret);
		जाओ errout;
	पूर्ण
	newxprt->sc_qp = newxprt->sc_cm_id->qp;

	अगर (!(dev->attrs.device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS))
		newxprt->sc_snd_w_inv = false;
	अगर (!rdma_protocol_iwarp(dev, newxprt->sc_port_num) &&
	    !rdma_ib_or_roce(dev, newxprt->sc_port_num)) अणु
		trace_svcrdma_fabric_err(newxprt, -EINVAL);
		जाओ errout;
	पूर्ण

	अगर (!svc_rdma_post_recvs(newxprt))
		जाओ errout;

	/* Conकाष्ठा RDMA-CM निजी message */
	pmsg.cp_magic = rpcrdma_cmp_magic;
	pmsg.cp_version = RPCRDMA_CMP_VERSION;
	pmsg.cp_flags = 0;
	pmsg.cp_send_size = pmsg.cp_recv_size =
		rpcrdma_encode_buffer_size(newxprt->sc_max_req_size);

	/* Accept Connection */
	set_bit(RDMAXPRT_CONN_PENDING, &newxprt->sc_flags);
	स_रखो(&conn_param, 0, माप conn_param);
	conn_param.responder_resources = 0;
	conn_param.initiator_depth = min_t(पूर्णांक, newxprt->sc_ord,
					   dev->attrs.max_qp_init_rd_atom);
	अगर (!conn_param.initiator_depth) अणु
		ret = -EINVAL;
		trace_svcrdma_initdepth_err(newxprt, ret);
		जाओ errout;
	पूर्ण
	conn_param.निजी_data = &pmsg;
	conn_param.निजी_data_len = माप(pmsg);
	rdma_lock_handler(newxprt->sc_cm_id);
	newxprt->sc_cm_id->event_handler = svc_rdma_cma_handler;
	ret = rdma_accept(newxprt->sc_cm_id, &conn_param);
	rdma_unlock_handler(newxprt->sc_cm_id);
	अगर (ret) अणु
		trace_svcrdma_accept_err(newxprt, ret);
		जाओ errout;
	पूर्ण

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
	dprपूर्णांकk("svcrdma: new connection %p accepted:\n", newxprt);
	sap = (काष्ठा sockaddr *)&newxprt->sc_cm_id->route.addr.src_addr;
	dprपूर्णांकk("    local address   : %pIS:%u\n", sap, rpc_get_port(sap));
	sap = (काष्ठा sockaddr *)&newxprt->sc_cm_id->route.addr.dst_addr;
	dprपूर्णांकk("    remote address  : %pIS:%u\n", sap, rpc_get_port(sap));
	dprपूर्णांकk("    max_sge         : %d\n", newxprt->sc_max_send_sges);
	dprपूर्णांकk("    sq_depth        : %d\n", newxprt->sc_sq_depth);
	dprपूर्णांकk("    rdma_rw_ctxs    : %d\n", ctxts);
	dprपूर्णांकk("    max_requests    : %d\n", newxprt->sc_max_requests);
	dprपूर्णांकk("    ord             : %d\n", conn_param.initiator_depth);
#पूर्ण_अगर

	वापस &newxprt->sc_xprt;

 errout:
	/* Take a reference in हाल the DTO handler runs */
	svc_xprt_get(&newxprt->sc_xprt);
	अगर (newxprt->sc_qp && !IS_ERR(newxprt->sc_qp))
		ib_destroy_qp(newxprt->sc_qp);
	rdma_destroy_id(newxprt->sc_cm_id);
	/* This call to put will destroy the transport */
	svc_xprt_put(&newxprt->sc_xprt);
	वापस शून्य;
पूर्ण

अटल व्योम svc_rdma_detach(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svcxprt_rdma *rdma =
		container_of(xprt, काष्ठा svcxprt_rdma, sc_xprt);

	rdma_disconnect(rdma->sc_cm_id);
पूर्ण

अटल व्योम __svc_rdma_मुक्त(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा svcxprt_rdma *rdma =
		container_of(work, काष्ठा svcxprt_rdma, sc_work);
	काष्ठा svc_xprt *xprt = &rdma->sc_xprt;

	/* This blocks until the Completion Queues are empty */
	अगर (rdma->sc_qp && !IS_ERR(rdma->sc_qp))
		ib_drain_qp(rdma->sc_qp);

	svc_rdma_flush_recv_queues(rdma);

	/* Final put of backchannel client transport */
	अगर (xprt->xpt_bc_xprt) अणु
		xprt_put(xprt->xpt_bc_xprt);
		xprt->xpt_bc_xprt = शून्य;
	पूर्ण

	svc_rdma_destroy_rw_ctxts(rdma);
	svc_rdma_send_ctxts_destroy(rdma);
	svc_rdma_recv_ctxts_destroy(rdma);

	/* Destroy the QP अगर present (not a listener) */
	अगर (rdma->sc_qp && !IS_ERR(rdma->sc_qp))
		ib_destroy_qp(rdma->sc_qp);

	अगर (rdma->sc_sq_cq && !IS_ERR(rdma->sc_sq_cq))
		ib_मुक्त_cq(rdma->sc_sq_cq);

	अगर (rdma->sc_rq_cq && !IS_ERR(rdma->sc_rq_cq))
		ib_मुक्त_cq(rdma->sc_rq_cq);

	अगर (rdma->sc_pd && !IS_ERR(rdma->sc_pd))
		ib_dealloc_pd(rdma->sc_pd);

	/* Destroy the CM ID */
	rdma_destroy_id(rdma->sc_cm_id);

	kमुक्त(rdma);
पूर्ण

अटल व्योम svc_rdma_मुक्त(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svcxprt_rdma *rdma =
		container_of(xprt, काष्ठा svcxprt_rdma, sc_xprt);

	INIT_WORK(&rdma->sc_work, __svc_rdma_मुक्त);
	schedule_work(&rdma->sc_work);
पूर्ण

अटल पूर्णांक svc_rdma_has_wspace(काष्ठा svc_xprt *xprt)
अणु
	काष्ठा svcxprt_rdma *rdma =
		container_of(xprt, काष्ठा svcxprt_rdma, sc_xprt);

	/*
	 * If there are alपढ़ोy रुकोers on the SQ,
	 * वापस false.
	 */
	अगर (रुकोqueue_active(&rdma->sc_send_रुको))
		वापस 0;

	/* Otherwise वापस true. */
	वापस 1;
पूर्ण

अटल व्योम svc_rdma_secure_port(काष्ठा svc_rqst *rqstp)
अणु
	set_bit(RQ_SECURE, &rqstp->rq_flags);
पूर्ण

अटल व्योम svc_rdma_समाप्त_temp_xprt(काष्ठा svc_xprt *xprt)
अणु
पूर्ण
