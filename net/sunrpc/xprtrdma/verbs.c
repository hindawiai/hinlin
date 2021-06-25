<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2014-2017 Oracle.  All rights reserved.
 * Copyright (c) 2003-2007 Network Appliance, Inc. All rights reserved.
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
 */

/*
 * verbs.c
 *
 * Encapsulates the major functions managing:
 *  o adapters
 *  o endpoपूर्णांकs
 *  o connections
 *  o buffer memory
 */

#समावेश <linux/पूर्णांकerrupt.h>
#समावेश <linux/slab.h>
#समावेश <linux/sunrpc/addr.h>
#समावेश <linux/sunrpc/svc_rdma.h>
#समावेश <linux/log2.h>

#समावेश <यंत्र-generic/barrier.h>
#समावेश <यंत्र/bitops.h>

#समावेश <rdma/ib_cm.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

/*
 * Globals/Macros
 */

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_TRANS
#पूर्ण_अगर

/*
 * पूर्णांकernal functions
 */
अटल पूर्णांक rpcrdma_sendctxs_create(काष्ठा rpcrdma_xprt *r_xprt);
अटल व्योम rpcrdma_sendctxs_destroy(काष्ठा rpcrdma_xprt *r_xprt);
अटल व्योम rpcrdma_sendctx_put_locked(काष्ठा rpcrdma_xprt *r_xprt,
				       काष्ठा rpcrdma_sendctx *sc);
अटल पूर्णांक rpcrdma_reqs_setup(काष्ठा rpcrdma_xprt *r_xprt);
अटल व्योम rpcrdma_reqs_reset(काष्ठा rpcrdma_xprt *r_xprt);
अटल व्योम rpcrdma_rep_destroy(काष्ठा rpcrdma_rep *rep);
अटल व्योम rpcrdma_reps_unmap(काष्ठा rpcrdma_xprt *r_xprt);
अटल व्योम rpcrdma_mrs_create(काष्ठा rpcrdma_xprt *r_xprt);
अटल व्योम rpcrdma_mrs_destroy(काष्ठा rpcrdma_xprt *r_xprt);
अटल व्योम rpcrdma_ep_get(काष्ठा rpcrdma_ep *ep);
अटल पूर्णांक rpcrdma_ep_put(काष्ठा rpcrdma_ep *ep);
अटल काष्ठा rpcrdma_regbuf *
rpcrdma_regbuf_alloc(माप_प्रकार size, क्रमागत dma_data_direction direction,
		     gfp_t flags);
अटल व्योम rpcrdma_regbuf_dma_unmap(काष्ठा rpcrdma_regbuf *rb);
अटल व्योम rpcrdma_regbuf_मुक्त(काष्ठा rpcrdma_regbuf *rb);

/* Wait क्रम outstanding transport work to finish. ib_drain_qp
 * handles the drains in the wrong order क्रम us, so खोलो code
 * them here.
 */
अटल व्योम rpcrdma_xprt_drain(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	काष्ठा rdma_cm_id *id = ep->re_id;

	/* Wait क्रम rpcrdma_post_recvs() to leave its critical
	 * section.
	 */
	अगर (atomic_inc_वापस(&ep->re_receiving) > 1)
		रुको_क्रम_completion(&ep->re_करोne);

	/* Flush Receives, then रुको क्रम deferred Reply work
	 * to complete.
	 */
	ib_drain_rq(id->qp);

	/* Deferred Reply processing might have scheduled
	 * local invalidations.
	 */
	ib_drain_sq(id->qp);

	rpcrdma_ep_put(ep);
पूर्ण

/* Ensure xprt_क्रमce_disconnect() is invoked exactly once when a
 * connection is बंदd or lost. (The important thing is it needs
 * to be invoked "at least" once).
 */
अटल व्योम rpcrdma_क्रमce_disconnect(काष्ठा rpcrdma_ep *ep)
अणु
	अगर (atomic_add_unless(&ep->re_क्रमce_disconnect, 1, 1))
		xprt_क्रमce_disconnect(ep->re_xprt);
पूर्ण

/**
 * rpcrdma_flush_disconnect - Disconnect on flushed completion
 * @r_xprt: transport to disconnect
 * @wc: work completion entry
 *
 * Must be called in process context.
 */
व्योम rpcrdma_flush_disconnect(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा ib_wc *wc)
अणु
	अगर (wc->status != IB_WC_SUCCESS)
		rpcrdma_क्रमce_disconnect(r_xprt->rx_ep);
पूर्ण

/**
 * rpcrdma_wc_send - Invoked by RDMA provider क्रम each polled Send WC
 * @cq:	completion queue
 * @wc:	WCE क्रम a completed Send WR
 *
 */
अटल व्योम rpcrdma_wc_send(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा rpcrdma_sendctx *sc =
		container_of(cqe, काष्ठा rpcrdma_sendctx, sc_cqe);
	काष्ठा rpcrdma_xprt *r_xprt = cq->cq_context;

	/* WARNING: Only wr_cqe and status are reliable at this poपूर्णांक */
	trace_xprtrdma_wc_send(wc, &sc->sc_cid);
	rpcrdma_sendctx_put_locked(r_xprt, sc);
	rpcrdma_flush_disconnect(r_xprt, wc);
पूर्ण

/**
 * rpcrdma_wc_receive - Invoked by RDMA provider क्रम each polled Receive WC
 * @cq:	completion queue
 * @wc:	WCE क्रम a completed Receive WR
 *
 */
अटल व्योम rpcrdma_wc_receive(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा rpcrdma_rep *rep = container_of(cqe, काष्ठा rpcrdma_rep,
					       rr_cqe);
	काष्ठा rpcrdma_xprt *r_xprt = cq->cq_context;

	/* WARNING: Only wr_cqe and status are reliable at this poपूर्णांक */
	trace_xprtrdma_wc_receive(wc, &rep->rr_cid);
	--r_xprt->rx_ep->re_receive_count;
	अगर (wc->status != IB_WC_SUCCESS)
		जाओ out_flushed;

	/* status == SUCCESS means all fields in wc are trustworthy */
	rpcrdma_set_xdrlen(&rep->rr_hdrbuf, wc->byte_len);
	rep->rr_wc_flags = wc->wc_flags;
	rep->rr_inv_rkey = wc->ex.invalidate_rkey;

	ib_dma_sync_single_क्रम_cpu(rdmab_device(rep->rr_rdmabuf),
				   rdmab_addr(rep->rr_rdmabuf),
				   wc->byte_len, DMA_FROM_DEVICE);

	rpcrdma_reply_handler(rep);
	वापस;

out_flushed:
	rpcrdma_flush_disconnect(r_xprt, wc);
	rpcrdma_rep_put(&r_xprt->rx_buf, rep);
पूर्ण

अटल व्योम rpcrdma_update_cm_निजी(काष्ठा rpcrdma_ep *ep,
				      काष्ठा rdma_conn_param *param)
अणु
	स्थिर काष्ठा rpcrdma_connect_निजी *pmsg = param->निजी_data;
	अचिन्हित पूर्णांक rsize, wsize;

	/* Default settings क्रम RPC-over-RDMA Version One */
	ep->re_implicit_roundup = xprt_rdma_pad_optimize;
	rsize = RPCRDMA_V1_DEF_INLINE_SIZE;
	wsize = RPCRDMA_V1_DEF_INLINE_SIZE;

	अगर (pmsg &&
	    pmsg->cp_magic == rpcrdma_cmp_magic &&
	    pmsg->cp_version == RPCRDMA_CMP_VERSION) अणु
		ep->re_implicit_roundup = true;
		rsize = rpcrdma_decode_buffer_size(pmsg->cp_send_size);
		wsize = rpcrdma_decode_buffer_size(pmsg->cp_recv_size);
	पूर्ण

	अगर (rsize < ep->re_अंतरभूत_recv)
		ep->re_अंतरभूत_recv = rsize;
	अगर (wsize < ep->re_अंतरभूत_send)
		ep->re_अंतरभूत_send = wsize;

	rpcrdma_set_max_header_sizes(ep);
पूर्ण

/**
 * rpcrdma_cm_event_handler - Handle RDMA CM events
 * @id: rdma_cm_id on which an event has occurred
 * @event: details of the event
 *
 * Called with @id's mutex held. Returns 1 अगर caller should
 * destroy @id, otherwise 0.
 */
अटल पूर्णांक
rpcrdma_cm_event_handler(काष्ठा rdma_cm_id *id, काष्ठा rdma_cm_event *event)
अणु
	काष्ठा sockaddr *sap = (काष्ठा sockaddr *)&id->route.addr.dst_addr;
	काष्ठा rpcrdma_ep *ep = id->context;

	might_sleep();

	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_ADDR_RESOLVED:
	हाल RDMA_CM_EVENT_ROUTE_RESOLVED:
		ep->re_async_rc = 0;
		complete(&ep->re_करोne);
		वापस 0;
	हाल RDMA_CM_EVENT_ADDR_ERROR:
		ep->re_async_rc = -EPROTO;
		complete(&ep->re_करोne);
		वापस 0;
	हाल RDMA_CM_EVENT_ROUTE_ERROR:
		ep->re_async_rc = -ENETUNREACH;
		complete(&ep->re_करोne);
		वापस 0;
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
		pr_info("rpcrdma: removing device %s for %pISpc\n",
			ep->re_id->device->name, sap);
		fallthrough;
	हाल RDMA_CM_EVENT_ADDR_CHANGE:
		ep->re_connect_status = -ENODEV;
		जाओ disconnected;
	हाल RDMA_CM_EVENT_ESTABLISHED:
		rpcrdma_ep_get(ep);
		ep->re_connect_status = 1;
		rpcrdma_update_cm_निजी(ep, &event->param.conn);
		trace_xprtrdma_अंतरभूत_thresh(ep);
		wake_up_all(&ep->re_connect_रुको);
		अवरोध;
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
		ep->re_connect_status = -ENOTCONN;
		जाओ wake_connect_worker;
	हाल RDMA_CM_EVENT_UNREACHABLE:
		ep->re_connect_status = -ENETUNREACH;
		जाओ wake_connect_worker;
	हाल RDMA_CM_EVENT_REJECTED:
		dprपूर्णांकk("rpcrdma: connection to %pISpc rejected: %s\n",
			sap, rdma_reject_msg(id, event->status));
		ep->re_connect_status = -ECONNREFUSED;
		अगर (event->status == IB_CM_REJ_STALE_CONN)
			ep->re_connect_status = -ENOTCONN;
wake_connect_worker:
		wake_up_all(&ep->re_connect_रुको);
		वापस 0;
	हाल RDMA_CM_EVENT_DISCONNECTED:
		ep->re_connect_status = -ECONNABORTED;
disconnected:
		rpcrdma_क्रमce_disconnect(ep);
		वापस rpcrdma_ep_put(ep);
	शेष:
		अवरोध;
	पूर्ण

	dprपूर्णांकk("RPC:       %s: %pISpc on %s/frwr: %s\n", __func__, sap,
		ep->re_id->device->name, rdma_event_msg(event->event));
	वापस 0;
पूर्ण

अटल काष्ठा rdma_cm_id *rpcrdma_create_id(काष्ठा rpcrdma_xprt *r_xprt,
					    काष्ठा rpcrdma_ep *ep)
अणु
	अचिन्हित दीर्घ wसमयout = msecs_to_jअगरfies(RDMA_RESOLVE_TIMEOUT) + 1;
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;
	काष्ठा rdma_cm_id *id;
	पूर्णांक rc;

	init_completion(&ep->re_करोne);

	id = rdma_create_id(xprt->xprt_net, rpcrdma_cm_event_handler, ep,
			    RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(id))
		वापस id;

	ep->re_async_rc = -ETIMEDOUT;
	rc = rdma_resolve_addr(id, शून्य, (काष्ठा sockaddr *)&xprt->addr,
			       RDMA_RESOLVE_TIMEOUT);
	अगर (rc)
		जाओ out;
	rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ep->re_करोne, wसमयout);
	अगर (rc < 0)
		जाओ out;

	rc = ep->re_async_rc;
	अगर (rc)
		जाओ out;

	ep->re_async_rc = -ETIMEDOUT;
	rc = rdma_resolve_route(id, RDMA_RESOLVE_TIMEOUT);
	अगर (rc)
		जाओ out;
	rc = रुको_क्रम_completion_पूर्णांकerruptible_समयout(&ep->re_करोne, wसमयout);
	अगर (rc < 0)
		जाओ out;
	rc = ep->re_async_rc;
	अगर (rc)
		जाओ out;

	वापस id;

out:
	rdma_destroy_id(id);
	वापस ERR_PTR(rc);
पूर्ण

अटल व्योम rpcrdma_ep_destroy(काष्ठा kref *kref)
अणु
	काष्ठा rpcrdma_ep *ep = container_of(kref, काष्ठा rpcrdma_ep, re_kref);

	अगर (ep->re_id->qp) अणु
		rdma_destroy_qp(ep->re_id);
		ep->re_id->qp = शून्य;
	पूर्ण

	अगर (ep->re_attr.recv_cq)
		ib_मुक्त_cq(ep->re_attr.recv_cq);
	ep->re_attr.recv_cq = शून्य;
	अगर (ep->re_attr.send_cq)
		ib_मुक्त_cq(ep->re_attr.send_cq);
	ep->re_attr.send_cq = शून्य;

	अगर (ep->re_pd)
		ib_dealloc_pd(ep->re_pd);
	ep->re_pd = शून्य;

	kमुक्त(ep);
	module_put(THIS_MODULE);
पूर्ण

अटल noअंतरभूत व्योम rpcrdma_ep_get(काष्ठा rpcrdma_ep *ep)
अणु
	kref_get(&ep->re_kref);
पूर्ण

/* Returns:
 *     %0 अगर @ep still has a positive kref count, or
 *     %1 अगर @ep was destroyed successfully.
 */
अटल noअंतरभूत पूर्णांक rpcrdma_ep_put(काष्ठा rpcrdma_ep *ep)
अणु
	वापस kref_put(&ep->re_kref, rpcrdma_ep_destroy);
पूर्ण

अटल पूर्णांक rpcrdma_ep_create(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_connect_निजी *pmsg;
	काष्ठा ib_device *device;
	काष्ठा rdma_cm_id *id;
	काष्ठा rpcrdma_ep *ep;
	पूर्णांक rc;

	ep = kzalloc(माप(*ep), GFP_NOFS);
	अगर (!ep)
		वापस -ENOTCONN;
	ep->re_xprt = &r_xprt->rx_xprt;
	kref_init(&ep->re_kref);

	id = rpcrdma_create_id(r_xprt, ep);
	अगर (IS_ERR(id)) अणु
		kमुक्त(ep);
		वापस PTR_ERR(id);
	पूर्ण
	__module_get(THIS_MODULE);
	device = id->device;
	ep->re_id = id;
	reinit_completion(&ep->re_करोne);

	ep->re_max_requests = r_xprt->rx_xprt.max_reqs;
	ep->re_अंतरभूत_send = xprt_rdma_max_अंतरभूत_ग_लिखो;
	ep->re_अंतरभूत_recv = xprt_rdma_max_अंतरभूत_पढ़ो;
	rc = frwr_query_device(ep, device);
	अगर (rc)
		जाओ out_destroy;

	r_xprt->rx_buf.rb_max_requests = cpu_to_be32(ep->re_max_requests);

	ep->re_attr.srq = शून्य;
	ep->re_attr.cap.max_अंतरभूत_data = 0;
	ep->re_attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	ep->re_attr.qp_type = IB_QPT_RC;
	ep->re_attr.port_num = ~0;

	dprपूर्णांकk("RPC:       %s: requested max: dtos: send %d recv %d; "
		"iovs: send %d recv %d\n",
		__func__,
		ep->re_attr.cap.max_send_wr,
		ep->re_attr.cap.max_recv_wr,
		ep->re_attr.cap.max_send_sge,
		ep->re_attr.cap.max_recv_sge);

	ep->re_send_batch = ep->re_max_requests >> 3;
	ep->re_send_count = ep->re_send_batch;
	init_रुकोqueue_head(&ep->re_connect_रुको);

	ep->re_attr.send_cq = ib_alloc_cq_any(device, r_xprt,
					      ep->re_attr.cap.max_send_wr,
					      IB_POLL_WORKQUEUE);
	अगर (IS_ERR(ep->re_attr.send_cq)) अणु
		rc = PTR_ERR(ep->re_attr.send_cq);
		जाओ out_destroy;
	पूर्ण

	ep->re_attr.recv_cq = ib_alloc_cq_any(device, r_xprt,
					      ep->re_attr.cap.max_recv_wr,
					      IB_POLL_WORKQUEUE);
	अगर (IS_ERR(ep->re_attr.recv_cq)) अणु
		rc = PTR_ERR(ep->re_attr.recv_cq);
		जाओ out_destroy;
	पूर्ण
	ep->re_receive_count = 0;

	/* Initialize cma parameters */
	स_रखो(&ep->re_remote_cma, 0, माप(ep->re_remote_cma));

	/* Prepare RDMA-CM निजी message */
	pmsg = &ep->re_cm_निजी;
	pmsg->cp_magic = rpcrdma_cmp_magic;
	pmsg->cp_version = RPCRDMA_CMP_VERSION;
	pmsg->cp_flags |= RPCRDMA_CMP_F_SND_W_INV_OK;
	pmsg->cp_send_size = rpcrdma_encode_buffer_size(ep->re_अंतरभूत_send);
	pmsg->cp_recv_size = rpcrdma_encode_buffer_size(ep->re_अंतरभूत_recv);
	ep->re_remote_cma.निजी_data = pmsg;
	ep->re_remote_cma.निजी_data_len = माप(*pmsg);

	/* Client offers RDMA Read but करोes not initiate */
	ep->re_remote_cma.initiator_depth = 0;
	ep->re_remote_cma.responder_resources =
		min_t(पूर्णांक, U8_MAX, device->attrs.max_qp_rd_atom);

	/* Limit transport retries so client can detect server
	 * GID changes quickly. RPC layer handles re-establishing
	 * transport connection and retransmission.
	 */
	ep->re_remote_cma.retry_count = 6;

	/* RPC-over-RDMA handles its own flow control. In addition,
	 * make all RNR NAKs visible so we know that RPC-over-RDMA
	 * flow control is working correctly (no NAKs should be seen).
	 */
	ep->re_remote_cma.flow_control = 0;
	ep->re_remote_cma.rnr_retry_count = 0;

	ep->re_pd = ib_alloc_pd(device, 0);
	अगर (IS_ERR(ep->re_pd)) अणु
		rc = PTR_ERR(ep->re_pd);
		जाओ out_destroy;
	पूर्ण

	rc = rdma_create_qp(id, ep->re_pd, &ep->re_attr);
	अगर (rc)
		जाओ out_destroy;

	r_xprt->rx_ep = ep;
	वापस 0;

out_destroy:
	rpcrdma_ep_put(ep);
	rdma_destroy_id(id);
	वापस rc;
पूर्ण

/**
 * rpcrdma_xprt_connect - Connect an unconnected transport
 * @r_xprt: controlling transport instance
 *
 * Returns 0 on success or a negative त्रुटि_सं.
 */
पूर्णांक rpcrdma_xprt_connect(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;
	काष्ठा rpcrdma_ep *ep;
	पूर्णांक rc;

	rc = rpcrdma_ep_create(r_xprt);
	अगर (rc)
		वापस rc;
	ep = r_xprt->rx_ep;

	xprt_clear_connected(xprt);
	rpcrdma_reset_cwnd(r_xprt);

	/* Bump the ep's reference count जबतक there are
	 * outstanding Receives.
	 */
	rpcrdma_ep_get(ep);
	rpcrdma_post_recvs(r_xprt, 1, true);

	rc = rdma_connect(ep->re_id, &ep->re_remote_cma);
	अगर (rc)
		जाओ out;

	अगर (xprt->reestablish_समयout < RPCRDMA_INIT_REEST_TO)
		xprt->reestablish_समयout = RPCRDMA_INIT_REEST_TO;
	रुको_event_पूर्णांकerruptible(ep->re_connect_रुको,
				 ep->re_connect_status != 0);
	अगर (ep->re_connect_status <= 0) अणु
		rc = ep->re_connect_status;
		जाओ out;
	पूर्ण

	rc = rpcrdma_sendctxs_create(r_xprt);
	अगर (rc) अणु
		rc = -ENOTCONN;
		जाओ out;
	पूर्ण

	rc = rpcrdma_reqs_setup(r_xprt);
	अगर (rc) अणु
		rc = -ENOTCONN;
		जाओ out;
	पूर्ण
	rpcrdma_mrs_create(r_xprt);

out:
	trace_xprtrdma_connect(r_xprt, rc);
	वापस rc;
पूर्ण

/**
 * rpcrdma_xprt_disconnect - Disconnect underlying transport
 * @r_xprt: controlling transport instance
 *
 * Caller serializes. Either the transport send lock is held,
 * or we're being called to destroy the transport.
 *
 * On वापस, @r_xprt is completely भागested of all hardware
 * resources and prepared क्रम the next ->connect operation.
 */
व्योम rpcrdma_xprt_disconnect(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	काष्ठा rdma_cm_id *id;
	पूर्णांक rc;

	अगर (!ep)
		वापस;

	id = ep->re_id;
	rc = rdma_disconnect(id);
	trace_xprtrdma_disconnect(r_xprt, rc);

	rpcrdma_xprt_drain(r_xprt);
	rpcrdma_reps_unmap(r_xprt);
	rpcrdma_reqs_reset(r_xprt);
	rpcrdma_mrs_destroy(r_xprt);
	rpcrdma_sendctxs_destroy(r_xprt);

	अगर (rpcrdma_ep_put(ep))
		rdma_destroy_id(id);

	r_xprt->rx_ep = शून्य;
पूर्ण

/* Fixed-size circular FIFO queue. This implementation is रुको-मुक्त and
 * lock-मुक्त.
 *
 * Consumer is the code path that posts Sends. This path dequeues a
 * sendctx क्रम use by a Send operation. Multiple consumer thपढ़ोs
 * are serialized by the RPC transport lock, which allows only one
 * ->send_request call at a समय.
 *
 * Producer is the code path that handles Send completions. This path
 * enqueues a sendctx that has been completed. Multiple producer
 * thपढ़ोs are serialized by the ib_poll_cq() function.
 */

/* rpcrdma_sendctxs_destroy() assumes caller has alपढ़ोy quiesced
 * queue activity, and rpcrdma_xprt_drain has flushed all reमुख्यing
 * Send requests.
 */
अटल व्योम rpcrdma_sendctxs_destroy(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	अचिन्हित दीर्घ i;

	अगर (!buf->rb_sc_ctxs)
		वापस;
	क्रम (i = 0; i <= buf->rb_sc_last; i++)
		kमुक्त(buf->rb_sc_ctxs[i]);
	kमुक्त(buf->rb_sc_ctxs);
	buf->rb_sc_ctxs = शून्य;
पूर्ण

अटल काष्ठा rpcrdma_sendctx *rpcrdma_sendctx_create(काष्ठा rpcrdma_ep *ep)
अणु
	काष्ठा rpcrdma_sendctx *sc;

	sc = kzalloc(काष्ठा_size(sc, sc_sges, ep->re_attr.cap.max_send_sge),
		     GFP_KERNEL);
	अगर (!sc)
		वापस शून्य;

	sc->sc_cqe.करोne = rpcrdma_wc_send;
	sc->sc_cid.ci_queue_id = ep->re_attr.send_cq->res.id;
	sc->sc_cid.ci_completion_id =
		atomic_inc_वापस(&ep->re_completion_ids);
	वापस sc;
पूर्ण

अटल पूर्णांक rpcrdma_sendctxs_create(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_sendctx *sc;
	अचिन्हित दीर्घ i;

	/* Maximum number of concurrent outstanding Send WRs. Capping
	 * the circular queue size stops Send Queue overflow by causing
	 * the ->send_request call to fail temporarily beक्रमe too many
	 * Sends are posted.
	 */
	i = r_xprt->rx_ep->re_max_requests + RPCRDMA_MAX_BC_REQUESTS;
	buf->rb_sc_ctxs = kसुस्मृति(i, माप(sc), GFP_KERNEL);
	अगर (!buf->rb_sc_ctxs)
		वापस -ENOMEM;

	buf->rb_sc_last = i - 1;
	क्रम (i = 0; i <= buf->rb_sc_last; i++) अणु
		sc = rpcrdma_sendctx_create(r_xprt->rx_ep);
		अगर (!sc)
			वापस -ENOMEM;

		buf->rb_sc_ctxs[i] = sc;
	पूर्ण

	buf->rb_sc_head = 0;
	buf->rb_sc_tail = 0;
	वापस 0;
पूर्ण

/* The sendctx queue is not guaranteed to have a size that is a
 * घातer of two, thus the helpers in circ_buf.h cannot be used.
 * The other option is to use modulus (%), which can be expensive.
 */
अटल अचिन्हित दीर्घ rpcrdma_sendctx_next(काष्ठा rpcrdma_buffer *buf,
					  अचिन्हित दीर्घ item)
अणु
	वापस likely(item < buf->rb_sc_last) ? item + 1 : 0;
पूर्ण

/**
 * rpcrdma_sendctx_get_locked - Acquire a send context
 * @r_xprt: controlling transport instance
 *
 * Returns poपूर्णांकer to a मुक्त send completion context; or शून्य अगर
 * the queue is empty.
 *
 * Usage: Called to acquire an SGE array beक्रमe preparing a Send WR.
 *
 * The caller serializes calls to this function (per transport), and
 * provides an effective memory barrier that flushes the new value
 * of rb_sc_head.
 */
काष्ठा rpcrdma_sendctx *rpcrdma_sendctx_get_locked(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_sendctx *sc;
	अचिन्हित दीर्घ next_head;

	next_head = rpcrdma_sendctx_next(buf, buf->rb_sc_head);

	अगर (next_head == READ_ONCE(buf->rb_sc_tail))
		जाओ out_emptyq;

	/* ORDER: item must be accessed _beक्रमe_ head is updated */
	sc = buf->rb_sc_ctxs[next_head];

	/* Releasing the lock in the caller acts as a memory
	 * barrier that flushes rb_sc_head.
	 */
	buf->rb_sc_head = next_head;

	वापस sc;

out_emptyq:
	/* The queue is "empty" अगर there have not been enough Send
	 * completions recently. This is a sign the Send Queue is
	 * backing up. Cause the caller to छोड़ो and try again.
	 */
	xprt_रुको_क्रम_buffer_space(&r_xprt->rx_xprt);
	r_xprt->rx_stats.empty_sendctx_q++;
	वापस शून्य;
पूर्ण

/**
 * rpcrdma_sendctx_put_locked - Release a send context
 * @r_xprt: controlling transport instance
 * @sc: send context to release
 *
 * Usage: Called from Send completion to वापस a sendctxt
 * to the queue.
 *
 * The caller serializes calls to this function (per transport).
 */
अटल व्योम rpcrdma_sendctx_put_locked(काष्ठा rpcrdma_xprt *r_xprt,
				       काष्ठा rpcrdma_sendctx *sc)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	अचिन्हित दीर्घ next_tail;

	/* Unmap SGEs of previously completed but unसंकेतed
	 * Sends by walking up the queue until @sc is found.
	 */
	next_tail = buf->rb_sc_tail;
	करो अणु
		next_tail = rpcrdma_sendctx_next(buf, next_tail);

		/* ORDER: item must be accessed _beक्रमe_ tail is updated */
		rpcrdma_sendctx_unmap(buf->rb_sc_ctxs[next_tail]);

	पूर्ण जबतक (buf->rb_sc_ctxs[next_tail] != sc);

	/* Paired with READ_ONCE */
	smp_store_release(&buf->rb_sc_tail, next_tail);

	xprt_ग_लिखो_space(&r_xprt->rx_xprt);
पूर्ण

अटल व्योम
rpcrdma_mrs_create(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	अचिन्हित पूर्णांक count;

	क्रम (count = 0; count < ep->re_max_rdma_segs; count++) अणु
		काष्ठा rpcrdma_mr *mr;
		पूर्णांक rc;

		mr = kzalloc(माप(*mr), GFP_NOFS);
		अगर (!mr)
			अवरोध;

		rc = frwr_mr_init(r_xprt, mr);
		अगर (rc) अणु
			kमुक्त(mr);
			अवरोध;
		पूर्ण

		spin_lock(&buf->rb_lock);
		rpcrdma_mr_push(mr, &buf->rb_mrs);
		list_add(&mr->mr_all, &buf->rb_all_mrs);
		spin_unlock(&buf->rb_lock);
	पूर्ण

	r_xprt->rx_stats.mrs_allocated += count;
	trace_xprtrdma_createmrs(r_xprt, count);
पूर्ण

अटल व्योम
rpcrdma_mr_refresh_worker(काष्ठा work_काष्ठा *work)
अणु
	काष्ठा rpcrdma_buffer *buf = container_of(work, काष्ठा rpcrdma_buffer,
						  rb_refresh_worker);
	काष्ठा rpcrdma_xprt *r_xprt = container_of(buf, काष्ठा rpcrdma_xprt,
						   rx_buf);

	rpcrdma_mrs_create(r_xprt);
	xprt_ग_लिखो_space(&r_xprt->rx_xprt);
पूर्ण

/**
 * rpcrdma_mrs_refresh - Wake the MR refresh worker
 * @r_xprt: controlling transport instance
 *
 */
व्योम rpcrdma_mrs_refresh(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;

	/* If there is no underlying connection, it's no use
	 * to wake the refresh worker.
	 */
	अगर (ep->re_connect_status == 1) अणु
		/* The work is scheduled on a WQ_MEM_RECLAIM
		 * workqueue in order to prevent MR allocation
		 * from recursing पूर्णांकo NFS during direct reclaim.
		 */
		queue_work(xprtiod_workqueue, &buf->rb_refresh_worker);
	पूर्ण
पूर्ण

/**
 * rpcrdma_req_create - Allocate an rpcrdma_req object
 * @r_xprt: controlling r_xprt
 * @size: initial size, in bytes, of send and receive buffers
 * @flags: GFP flags passed to memory allocators
 *
 * Returns an allocated and fully initialized rpcrdma_req or शून्य.
 */
काष्ठा rpcrdma_req *rpcrdma_req_create(काष्ठा rpcrdma_xprt *r_xprt, माप_प्रकार size,
				       gfp_t flags)
अणु
	काष्ठा rpcrdma_buffer *buffer = &r_xprt->rx_buf;
	काष्ठा rpcrdma_req *req;

	req = kzalloc(माप(*req), flags);
	अगर (req == शून्य)
		जाओ out1;

	req->rl_sendbuf = rpcrdma_regbuf_alloc(size, DMA_TO_DEVICE, flags);
	अगर (!req->rl_sendbuf)
		जाओ out2;

	req->rl_recvbuf = rpcrdma_regbuf_alloc(size, DMA_NONE, flags);
	अगर (!req->rl_recvbuf)
		जाओ out3;

	INIT_LIST_HEAD(&req->rl_मुक्त_mrs);
	INIT_LIST_HEAD(&req->rl_रेजिस्टरed);
	spin_lock(&buffer->rb_lock);
	list_add(&req->rl_all, &buffer->rb_allreqs);
	spin_unlock(&buffer->rb_lock);
	वापस req;

out3:
	kमुक्त(req->rl_sendbuf);
out2:
	kमुक्त(req);
out1:
	वापस शून्य;
पूर्ण

/**
 * rpcrdma_req_setup - Per-connection instance setup of an rpcrdma_req object
 * @r_xprt: controlling transport instance
 * @req: rpcrdma_req object to set up
 *
 * Returns zero on success, and a negative त्रुटि_सं on failure.
 */
पूर्णांक rpcrdma_req_setup(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req)
अणु
	काष्ठा rpcrdma_regbuf *rb;
	माप_प्रकार maxhdrsize;

	/* Compute maximum header buffer size in bytes */
	maxhdrsize = rpcrdma_fixed_maxsz + 3 +
		     r_xprt->rx_ep->re_max_rdma_segs * rpcrdma_पढ़ोchunk_maxsz;
	maxhdrsize *= माप(__be32);
	rb = rpcrdma_regbuf_alloc(__roundup_घात_of_two(maxhdrsize),
				  DMA_TO_DEVICE, GFP_KERNEL);
	अगर (!rb)
		जाओ out;

	अगर (!__rpcrdma_regbuf_dma_map(r_xprt, rb))
		जाओ out_मुक्त;

	req->rl_rdmabuf = rb;
	xdr_buf_init(&req->rl_hdrbuf, rdmab_data(rb), rdmab_length(rb));
	वापस 0;

out_मुक्त:
	rpcrdma_regbuf_मुक्त(rb);
out:
	वापस -ENOMEM;
पूर्ण

/* ASSUMPTION: the rb_allreqs list is stable क्रम the duration,
 * and thus can be walked without holding rb_lock. Eg. the
 * caller is holding the transport send lock to exclude
 * device removal or disconnection.
 */
अटल पूर्णांक rpcrdma_reqs_setup(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_req *req;
	पूर्णांक rc;

	list_क्रम_each_entry(req, &buf->rb_allreqs, rl_all) अणु
		rc = rpcrdma_req_setup(r_xprt, req);
		अगर (rc)
			वापस rc;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम rpcrdma_req_reset(काष्ठा rpcrdma_req *req)
अणु
	/* Credits are valid क्रम only one connection */
	req->rl_slot.rq_cong = 0;

	rpcrdma_regbuf_मुक्त(req->rl_rdmabuf);
	req->rl_rdmabuf = शून्य;

	rpcrdma_regbuf_dma_unmap(req->rl_sendbuf);
	rpcrdma_regbuf_dma_unmap(req->rl_recvbuf);

	frwr_reset(req);
पूर्ण

/* ASSUMPTION: the rb_allreqs list is stable क्रम the duration,
 * and thus can be walked without holding rb_lock. Eg. the
 * caller is holding the transport send lock to exclude
 * device removal or disconnection.
 */
अटल व्योम rpcrdma_reqs_reset(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_req *req;

	list_क्रम_each_entry(req, &buf->rb_allreqs, rl_all)
		rpcrdma_req_reset(req);
पूर्ण

अटल noअंतरभूत
काष्ठा rpcrdma_rep *rpcrdma_rep_create(काष्ठा rpcrdma_xprt *r_xprt,
				       bool temp)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_rep *rep;

	rep = kzalloc(माप(*rep), GFP_KERNEL);
	अगर (rep == शून्य)
		जाओ out;

	rep->rr_rdmabuf = rpcrdma_regbuf_alloc(r_xprt->rx_ep->re_अंतरभूत_recv,
					       DMA_FROM_DEVICE, GFP_KERNEL);
	अगर (!rep->rr_rdmabuf)
		जाओ out_मुक्त;

	अगर (!rpcrdma_regbuf_dma_map(r_xprt, rep->rr_rdmabuf))
		जाओ out_मुक्त_regbuf;

	rep->rr_cid.ci_completion_id =
		atomic_inc_वापस(&r_xprt->rx_ep->re_completion_ids);

	xdr_buf_init(&rep->rr_hdrbuf, rdmab_data(rep->rr_rdmabuf),
		     rdmab_length(rep->rr_rdmabuf));
	rep->rr_cqe.करोne = rpcrdma_wc_receive;
	rep->rr_rxprt = r_xprt;
	rep->rr_recv_wr.next = शून्य;
	rep->rr_recv_wr.wr_cqe = &rep->rr_cqe;
	rep->rr_recv_wr.sg_list = &rep->rr_rdmabuf->rg_iov;
	rep->rr_recv_wr.num_sge = 1;
	rep->rr_temp = temp;

	spin_lock(&buf->rb_lock);
	list_add(&rep->rr_all, &buf->rb_all_reps);
	spin_unlock(&buf->rb_lock);
	वापस rep;

out_मुक्त_regbuf:
	rpcrdma_regbuf_मुक्त(rep->rr_rdmabuf);
out_मुक्त:
	kमुक्त(rep);
out:
	वापस शून्य;
पूर्ण

अटल व्योम rpcrdma_rep_मुक्त(काष्ठा rpcrdma_rep *rep)
अणु
	rpcrdma_regbuf_मुक्त(rep->rr_rdmabuf);
	kमुक्त(rep);
पूर्ण

अटल व्योम rpcrdma_rep_destroy(काष्ठा rpcrdma_rep *rep)
अणु
	काष्ठा rpcrdma_buffer *buf = &rep->rr_rxprt->rx_buf;

	spin_lock(&buf->rb_lock);
	list_del(&rep->rr_all);
	spin_unlock(&buf->rb_lock);

	rpcrdma_rep_मुक्त(rep);
पूर्ण

अटल काष्ठा rpcrdma_rep *rpcrdma_rep_get_locked(काष्ठा rpcrdma_buffer *buf)
अणु
	काष्ठा llist_node *node;

	/* Calls to llist_del_first are required to be serialized */
	node = llist_del_first(&buf->rb_मुक्त_reps);
	अगर (!node)
		वापस शून्य;
	वापस llist_entry(node, काष्ठा rpcrdma_rep, rr_node);
पूर्ण

/**
 * rpcrdma_rep_put - Release rpcrdma_rep back to मुक्त list
 * @buf: buffer pool
 * @rep: rep to release
 *
 */
व्योम rpcrdma_rep_put(काष्ठा rpcrdma_buffer *buf, काष्ठा rpcrdma_rep *rep)
अणु
	llist_add(&rep->rr_node, &buf->rb_मुक्त_reps);
पूर्ण

/* Caller must ensure the QP is quiescent (RQ is drained) beक्रमe
 * invoking this function, to guarantee rb_all_reps is not
 * changing.
 */
अटल व्योम rpcrdma_reps_unmap(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_rep *rep;

	list_क्रम_each_entry(rep, &buf->rb_all_reps, rr_all) अणु
		rpcrdma_regbuf_dma_unmap(rep->rr_rdmabuf);
		rep->rr_temp = true;	/* Mark this rep क्रम deकाष्ठाion */
	पूर्ण
पूर्ण

अटल व्योम rpcrdma_reps_destroy(काष्ठा rpcrdma_buffer *buf)
अणु
	काष्ठा rpcrdma_rep *rep;

	spin_lock(&buf->rb_lock);
	जबतक ((rep = list_first_entry_or_null(&buf->rb_all_reps,
					       काष्ठा rpcrdma_rep,
					       rr_all)) != शून्य) अणु
		list_del(&rep->rr_all);
		spin_unlock(&buf->rb_lock);

		rpcrdma_rep_मुक्त(rep);

		spin_lock(&buf->rb_lock);
	पूर्ण
	spin_unlock(&buf->rb_lock);
पूर्ण

/**
 * rpcrdma_buffer_create - Create initial set of req/rep objects
 * @r_xprt: transport instance to (re)initialize
 *
 * Returns zero on success, otherwise a negative त्रुटि_सं.
 */
पूर्णांक rpcrdma_buffer_create(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	पूर्णांक i, rc;

	buf->rb_bc_srv_max_requests = 0;
	spin_lock_init(&buf->rb_lock);
	INIT_LIST_HEAD(&buf->rb_mrs);
	INIT_LIST_HEAD(&buf->rb_all_mrs);
	INIT_WORK(&buf->rb_refresh_worker, rpcrdma_mr_refresh_worker);

	INIT_LIST_HEAD(&buf->rb_send_bufs);
	INIT_LIST_HEAD(&buf->rb_allreqs);
	INIT_LIST_HEAD(&buf->rb_all_reps);

	rc = -ENOMEM;
	क्रम (i = 0; i < r_xprt->rx_xprt.max_reqs; i++) अणु
		काष्ठा rpcrdma_req *req;

		req = rpcrdma_req_create(r_xprt, RPCRDMA_V1_DEF_INLINE_SIZE * 2,
					 GFP_KERNEL);
		अगर (!req)
			जाओ out;
		list_add(&req->rl_list, &buf->rb_send_bufs);
	पूर्ण

	init_llist_head(&buf->rb_मुक्त_reps);

	वापस 0;
out:
	rpcrdma_buffer_destroy(buf);
	वापस rc;
पूर्ण

/**
 * rpcrdma_req_destroy - Destroy an rpcrdma_req object
 * @req: unused object to be destroyed
 *
 * Relies on caller holding the transport send lock to protect
 * removing req->rl_all from buf->rb_all_reqs safely.
 */
व्योम rpcrdma_req_destroy(काष्ठा rpcrdma_req *req)
अणु
	काष्ठा rpcrdma_mr *mr;

	list_del(&req->rl_all);

	जबतक ((mr = rpcrdma_mr_pop(&req->rl_मुक्त_mrs))) अणु
		काष्ठा rpcrdma_buffer *buf = &mr->mr_xprt->rx_buf;

		spin_lock(&buf->rb_lock);
		list_del(&mr->mr_all);
		spin_unlock(&buf->rb_lock);

		frwr_mr_release(mr);
	पूर्ण

	rpcrdma_regbuf_मुक्त(req->rl_recvbuf);
	rpcrdma_regbuf_मुक्त(req->rl_sendbuf);
	rpcrdma_regbuf_मुक्त(req->rl_rdmabuf);
	kमुक्त(req);
पूर्ण

/**
 * rpcrdma_mrs_destroy - Release all of a transport's MRs
 * @r_xprt: controlling transport instance
 *
 * Relies on caller holding the transport send lock to protect
 * removing mr->mr_list from req->rl_मुक्त_mrs safely.
 */
अटल व्योम rpcrdma_mrs_destroy(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_mr *mr;

	cancel_work_sync(&buf->rb_refresh_worker);

	spin_lock(&buf->rb_lock);
	जबतक ((mr = list_first_entry_or_null(&buf->rb_all_mrs,
					      काष्ठा rpcrdma_mr,
					      mr_all)) != शून्य) अणु
		list_del(&mr->mr_list);
		list_del(&mr->mr_all);
		spin_unlock(&buf->rb_lock);

		frwr_mr_release(mr);

		spin_lock(&buf->rb_lock);
	पूर्ण
	spin_unlock(&buf->rb_lock);
पूर्ण

/**
 * rpcrdma_buffer_destroy - Release all hw resources
 * @buf: root control block क्रम resources
 *
 * ORDERING: relies on a prior rpcrdma_xprt_drain :
 * - No more Send or Receive completions can occur
 * - All MRs, reps, and reqs are वापसed to their मुक्त lists
 */
व्योम
rpcrdma_buffer_destroy(काष्ठा rpcrdma_buffer *buf)
अणु
	rpcrdma_reps_destroy(buf);

	जबतक (!list_empty(&buf->rb_send_bufs)) अणु
		काष्ठा rpcrdma_req *req;

		req = list_first_entry(&buf->rb_send_bufs,
				       काष्ठा rpcrdma_req, rl_list);
		list_del(&req->rl_list);
		rpcrdma_req_destroy(req);
	पूर्ण
पूर्ण

/**
 * rpcrdma_mr_get - Allocate an rpcrdma_mr object
 * @r_xprt: controlling transport
 *
 * Returns an initialized rpcrdma_mr or शून्य अगर no मुक्त
 * rpcrdma_mr objects are available.
 */
काष्ठा rpcrdma_mr *
rpcrdma_mr_get(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_mr *mr;

	spin_lock(&buf->rb_lock);
	mr = rpcrdma_mr_pop(&buf->rb_mrs);
	spin_unlock(&buf->rb_lock);
	वापस mr;
पूर्ण

/**
 * rpcrdma_reply_put - Put reply buffers back पूर्णांकo pool
 * @buffers: buffer pool
 * @req: object to वापस
 *
 */
व्योम rpcrdma_reply_put(काष्ठा rpcrdma_buffer *buffers, काष्ठा rpcrdma_req *req)
अणु
	अगर (req->rl_reply) अणु
		rpcrdma_rep_put(buffers, req->rl_reply);
		req->rl_reply = शून्य;
	पूर्ण
पूर्ण

/**
 * rpcrdma_buffer_get - Get a request buffer
 * @buffers: Buffer pool from which to obtain a buffer
 *
 * Returns a fresh rpcrdma_req, or शून्य अगर none are available.
 */
काष्ठा rpcrdma_req *
rpcrdma_buffer_get(काष्ठा rpcrdma_buffer *buffers)
अणु
	काष्ठा rpcrdma_req *req;

	spin_lock(&buffers->rb_lock);
	req = list_first_entry_or_null(&buffers->rb_send_bufs,
				       काष्ठा rpcrdma_req, rl_list);
	अगर (req)
		list_del_init(&req->rl_list);
	spin_unlock(&buffers->rb_lock);
	वापस req;
पूर्ण

/**
 * rpcrdma_buffer_put - Put request/reply buffers back पूर्णांकo pool
 * @buffers: buffer pool
 * @req: object to वापस
 *
 */
व्योम rpcrdma_buffer_put(काष्ठा rpcrdma_buffer *buffers, काष्ठा rpcrdma_req *req)
अणु
	rpcrdma_reply_put(buffers, req);

	spin_lock(&buffers->rb_lock);
	list_add(&req->rl_list, &buffers->rb_send_bufs);
	spin_unlock(&buffers->rb_lock);
पूर्ण

/* Returns a poपूर्णांकer to a rpcrdma_regbuf object, or शून्य.
 *
 * xprtrdma uses a regbuf क्रम posting an outgoing RDMA SEND, or क्रम
 * receiving the payload of RDMA RECV operations. During Long Calls
 * or Replies they may be रेजिस्टरed बाह्यally via frwr_map.
 */
अटल काष्ठा rpcrdma_regbuf *
rpcrdma_regbuf_alloc(माप_प्रकार size, क्रमागत dma_data_direction direction,
		     gfp_t flags)
अणु
	काष्ठा rpcrdma_regbuf *rb;

	rb = kदो_स्मृति(माप(*rb), flags);
	अगर (!rb)
		वापस शून्य;
	rb->rg_data = kदो_स्मृति(size, flags);
	अगर (!rb->rg_data) अणु
		kमुक्त(rb);
		वापस शून्य;
	पूर्ण

	rb->rg_device = शून्य;
	rb->rg_direction = direction;
	rb->rg_iov.length = size;
	वापस rb;
पूर्ण

/**
 * rpcrdma_regbuf_पुनः_स्मृति - re-allocate a SEND/RECV buffer
 * @rb: regbuf to पुनः_स्मृतिate
 * @size: size of buffer to be allocated, in bytes
 * @flags: GFP flags
 *
 * Returns true अगर पुनः_स्मृतिation was successful. If false is
 * वापसed, @rb is left untouched.
 */
bool rpcrdma_regbuf_पुनः_स्मृति(काष्ठा rpcrdma_regbuf *rb, माप_प्रकार size, gfp_t flags)
अणु
	व्योम *buf;

	buf = kदो_स्मृति(size, flags);
	अगर (!buf)
		वापस false;

	rpcrdma_regbuf_dma_unmap(rb);
	kमुक्त(rb->rg_data);

	rb->rg_data = buf;
	rb->rg_iov.length = size;
	वापस true;
पूर्ण

/**
 * __rpcrdma_regbuf_dma_map - DMA-map a regbuf
 * @r_xprt: controlling transport instance
 * @rb: regbuf to be mapped
 *
 * Returns true अगर the buffer is now DMA mapped to @r_xprt's device
 */
bool __rpcrdma_regbuf_dma_map(काष्ठा rpcrdma_xprt *r_xprt,
			      काष्ठा rpcrdma_regbuf *rb)
अणु
	काष्ठा ib_device *device = r_xprt->rx_ep->re_id->device;

	अगर (rb->rg_direction == DMA_NONE)
		वापस false;

	rb->rg_iov.addr = ib_dma_map_single(device, rdmab_data(rb),
					    rdmab_length(rb), rb->rg_direction);
	अगर (ib_dma_mapping_error(device, rdmab_addr(rb))) अणु
		trace_xprtrdma_dma_maperr(rdmab_addr(rb));
		वापस false;
	पूर्ण

	rb->rg_device = device;
	rb->rg_iov.lkey = r_xprt->rx_ep->re_pd->local_dma_lkey;
	वापस true;
पूर्ण

अटल व्योम rpcrdma_regbuf_dma_unmap(काष्ठा rpcrdma_regbuf *rb)
अणु
	अगर (!rb)
		वापस;

	अगर (!rpcrdma_regbuf_is_mapped(rb))
		वापस;

	ib_dma_unmap_single(rb->rg_device, rdmab_addr(rb), rdmab_length(rb),
			    rb->rg_direction);
	rb->rg_device = शून्य;
पूर्ण

अटल व्योम rpcrdma_regbuf_मुक्त(काष्ठा rpcrdma_regbuf *rb)
अणु
	rpcrdma_regbuf_dma_unmap(rb);
	अगर (rb)
		kमुक्त(rb->rg_data);
	kमुक्त(rb);
पूर्ण

/**
 * rpcrdma_post_sends - Post WRs to a transport's Send Queue
 * @r_xprt: controlling transport instance
 * @req: rpcrdma_req containing the Send WR to post
 *
 * Returns 0 अगर the post was successful, otherwise -ENOTCONN
 * is वापसed.
 */
पूर्णांक rpcrdma_post_sends(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req)
अणु
	अगर (frwr_send(r_xprt, req))
		वापस -ENOTCONN;
	वापस 0;
पूर्ण

/**
 * rpcrdma_post_recvs - Refill the Receive Queue
 * @r_xprt: controlling transport instance
 * @needed: current credit grant
 * @temp: mark Receive buffers to be deleted after one use
 *
 */
व्योम rpcrdma_post_recvs(काष्ठा rpcrdma_xprt *r_xprt, पूर्णांक needed, bool temp)
अणु
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	काष्ठा ib_recv_wr *wr, *bad_wr;
	काष्ठा rpcrdma_rep *rep;
	पूर्णांक count, rc;

	rc = 0;
	count = 0;

	अगर (likely(ep->re_receive_count > needed))
		जाओ out;
	needed -= ep->re_receive_count;
	अगर (!temp)
		needed += RPCRDMA_MAX_RECV_BATCH;

	अगर (atomic_inc_वापस(&ep->re_receiving) > 1)
		जाओ out;

	/* fast path: all needed reps can be found on the मुक्त list */
	wr = शून्य;
	जबतक (needed) अणु
		rep = rpcrdma_rep_get_locked(buf);
		अगर (rep && rep->rr_temp) अणु
			rpcrdma_rep_destroy(rep);
			जारी;
		पूर्ण
		अगर (!rep)
			rep = rpcrdma_rep_create(r_xprt, temp);
		अगर (!rep)
			अवरोध;

		rep->rr_cid.ci_queue_id = ep->re_attr.recv_cq->res.id;
		trace_xprtrdma_post_recv(rep);
		rep->rr_recv_wr.next = wr;
		wr = &rep->rr_recv_wr;
		--needed;
		++count;
	पूर्ण
	अगर (!wr)
		जाओ out;

	rc = ib_post_recv(ep->re_id->qp, wr,
			  (स्थिर काष्ठा ib_recv_wr **)&bad_wr);
	अगर (atomic_dec_वापस(&ep->re_receiving) > 0)
		complete(&ep->re_करोne);

out:
	trace_xprtrdma_post_recvs(r_xprt, count, rc);
	अगर (rc) अणु
		क्रम (wr = bad_wr; wr;) अणु
			काष्ठा rpcrdma_rep *rep;

			rep = container_of(wr, काष्ठा rpcrdma_rep, rr_recv_wr);
			wr = wr->next;
			rpcrdma_rep_put(buf, rep);
			--count;
		पूर्ण
	पूर्ण
	ep->re_receive_count += count;
	वापस;
पूर्ण
