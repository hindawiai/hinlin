<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015-2020, Oracle and/or its affiliates.
 *
 * Support क्रम reverse-direction RPCs on RPC/RDMA.
 */

#समावेश <linux/sunrpc/xprt.h>
#समावेश <linux/sunrpc/svc.h>
#समावेश <linux/sunrpc/svc_xprt.h>
#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_TRANS
#पूर्ण_अगर

#अघोषित RPCRDMA_BACKCHANNEL_DEBUG

/**
 * xprt_rdma_bc_setup - Pre-allocate resources क्रम handling backchannel requests
 * @xprt: transport associated with these backchannel resources
 * @reqs: number of concurrent incoming requests to expect
 *
 * Returns 0 on success; otherwise a negative त्रुटि_सं
 */
पूर्णांक xprt_rdma_bc_setup(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक reqs)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);

	r_xprt->rx_buf.rb_bc_srv_max_requests = RPCRDMA_BACKWARD_WRS >> 1;
	trace_xprtrdma_cb_setup(r_xprt, reqs);
	वापस 0;
पूर्ण

/**
 * xprt_rdma_bc_maxpayload - Return maximum backchannel message size
 * @xprt: transport
 *
 * Returns maximum size, in bytes, of a backchannel message
 */
माप_प्रकार xprt_rdma_bc_maxpayload(काष्ठा rpc_xprt *xprt)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	माप_प्रकार maxmsg;

	maxmsg = min_t(अचिन्हित पूर्णांक, ep->re_अंतरभूत_send, ep->re_अंतरभूत_recv);
	maxmsg = min_t(अचिन्हित पूर्णांक, maxmsg, PAGE_SIZE);
	वापस maxmsg - RPCRDMA_HDRLEN_MIN;
पूर्ण

अचिन्हित पूर्णांक xprt_rdma_bc_max_slots(काष्ठा rpc_xprt *xprt)
अणु
	वापस RPCRDMA_BACKWARD_WRS >> 1;
पूर्ण

अटल पूर्णांक rpcrdma_bc_marshal_reply(काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(rqst->rq_xprt);
	काष्ठा rpcrdma_req *req = rpcr_to_rdmar(rqst);
	__be32 *p;

	rpcrdma_set_xdrlen(&req->rl_hdrbuf, 0);
	xdr_init_encode(&req->rl_stream, &req->rl_hdrbuf,
			rdmab_data(req->rl_rdmabuf), rqst);

	p = xdr_reserve_space(&req->rl_stream, 28);
	अगर (unlikely(!p))
		वापस -EIO;
	*p++ = rqst->rq_xid;
	*p++ = rpcrdma_version;
	*p++ = cpu_to_be32(r_xprt->rx_buf.rb_bc_srv_max_requests);
	*p++ = rdma_msg;
	*p++ = xdr_zero;
	*p++ = xdr_zero;
	*p = xdr_zero;

	अगर (rpcrdma_prepare_send_sges(r_xprt, req, RPCRDMA_HDRLEN_MIN,
				      &rqst->rq_snd_buf, rpcrdma_noch_pullup))
		वापस -EIO;

	trace_xprtrdma_cb_reply(r_xprt, rqst);
	वापस 0;
पूर्ण

/**
 * xprt_rdma_bc_send_reply - marshal and send a backchannel reply
 * @rqst: RPC rqst with a backchannel RPC reply in rq_snd_buf
 *
 * Caller holds the transport's ग_लिखो lock.
 *
 * Returns:
 *	%0 अगर the RPC message has been sent
 *	%-ENOTCONN अगर the caller should reconnect and call again
 *	%-EIO अगर a permanent error occurred and the request was not
 *		sent. Do not try to send this message again.
 */
पूर्णांक xprt_rdma_bc_send_reply(काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा rpc_xprt *xprt = rqst->rq_xprt;
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	काष्ठा rpcrdma_req *req = rpcr_to_rdmar(rqst);
	पूर्णांक rc;

	अगर (!xprt_connected(xprt))
		वापस -ENOTCONN;

	अगर (!xprt_request_get_cong(xprt, rqst))
		वापस -EBADSLT;

	rc = rpcrdma_bc_marshal_reply(rqst);
	अगर (rc < 0)
		जाओ failed_marshal;

	अगर (rpcrdma_post_sends(r_xprt, req))
		जाओ drop_connection;
	वापस 0;

failed_marshal:
	अगर (rc != -ENOTCONN)
		वापस rc;
drop_connection:
	xprt_rdma_बंद(xprt);
	वापस -ENOTCONN;
पूर्ण

/**
 * xprt_rdma_bc_destroy - Release resources क्रम handling backchannel requests
 * @xprt: transport associated with these backchannel resources
 * @reqs: number of incoming requests to destroy; ignored
 */
व्योम xprt_rdma_bc_destroy(काष्ठा rpc_xprt *xprt, अचिन्हित पूर्णांक reqs)
अणु
	काष्ठा rpc_rqst *rqst, *पंचांगp;

	spin_lock(&xprt->bc_pa_lock);
	list_क्रम_each_entry_safe(rqst, पंचांगp, &xprt->bc_pa_list, rq_bc_pa_list) अणु
		list_del(&rqst->rq_bc_pa_list);
		spin_unlock(&xprt->bc_pa_lock);

		rpcrdma_req_destroy(rpcr_to_rdmar(rqst));

		spin_lock(&xprt->bc_pa_lock);
	पूर्ण
	spin_unlock(&xprt->bc_pa_lock);
पूर्ण

/**
 * xprt_rdma_bc_मुक्त_rqst - Release a backchannel rqst
 * @rqst: request to release
 */
व्योम xprt_rdma_bc_मुक्त_rqst(काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा rpcrdma_req *req = rpcr_to_rdmar(rqst);
	काष्ठा rpcrdma_rep *rep = req->rl_reply;
	काष्ठा rpc_xprt *xprt = rqst->rq_xprt;
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);

	rpcrdma_rep_put(&r_xprt->rx_buf, rep);
	req->rl_reply = शून्य;

	spin_lock(&xprt->bc_pa_lock);
	list_add_tail(&rqst->rq_bc_pa_list, &xprt->bc_pa_list);
	spin_unlock(&xprt->bc_pa_lock);
	xprt_put(xprt);
पूर्ण

अटल काष्ठा rpc_rqst *rpcrdma_bc_rqst_get(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;
	काष्ठा rpcrdma_req *req;
	काष्ठा rpc_rqst *rqst;
	माप_प्रकार size;

	spin_lock(&xprt->bc_pa_lock);
	rqst = list_first_entry_or_null(&xprt->bc_pa_list, काष्ठा rpc_rqst,
					rq_bc_pa_list);
	अगर (!rqst)
		जाओ create_req;
	list_del(&rqst->rq_bc_pa_list);
	spin_unlock(&xprt->bc_pa_lock);
	वापस rqst;

create_req:
	spin_unlock(&xprt->bc_pa_lock);

	/* Set a limit to prevent a remote from overrunning our resources.
	 */
	अगर (xprt->bc_alloc_count >= RPCRDMA_BACKWARD_WRS)
		वापस शून्य;

	size = min_t(माप_प्रकार, r_xprt->rx_ep->re_अंतरभूत_recv, PAGE_SIZE);
	req = rpcrdma_req_create(r_xprt, size, GFP_KERNEL);
	अगर (!req)
		वापस शून्य;
	अगर (rpcrdma_req_setup(r_xprt, req)) अणु
		rpcrdma_req_destroy(req);
		वापस शून्य;
	पूर्ण

	xprt->bc_alloc_count++;
	rqst = &req->rl_slot;
	rqst->rq_xprt = xprt;
	__set_bit(RPC_BC_PA_IN_USE, &rqst->rq_bc_pa_state);
	xdr_buf_init(&rqst->rq_snd_buf, rdmab_data(req->rl_sendbuf), size);
	वापस rqst;
पूर्ण

/**
 * rpcrdma_bc_receive_call - Handle a reverse-direction Call
 * @r_xprt: transport receiving the call
 * @rep: receive buffer containing the call
 *
 * Operational assumptions:
 *    o Backchannel credits are ignored, just as the NFS server
 *      क्रमechannel currently करोes
 *    o The ULP manages a replay cache (eg, NFSv4.1 sessions).
 *      No replay detection is करोne at the transport level
 */
व्योम rpcrdma_bc_receive_call(काष्ठा rpcrdma_xprt *r_xprt,
			     काष्ठा rpcrdma_rep *rep)
अणु
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;
	काष्ठा svc_serv *bc_serv;
	काष्ठा rpcrdma_req *req;
	काष्ठा rpc_rqst *rqst;
	काष्ठा xdr_buf *buf;
	माप_प्रकार size;
	__be32 *p;

	p = xdr_अंतरभूत_decode(&rep->rr_stream, 0);
	size = xdr_stream_reमुख्यing(&rep->rr_stream);

#अगर_घोषित RPCRDMA_BACKCHANNEL_DEBUG
	pr_info("RPC:       %s: callback XID %08x, length=%u\n",
		__func__, be32_to_cpup(p), size);
	pr_info("RPC:       %s: %*ph\n", __func__, size, p);
#पूर्ण_अगर

	rqst = rpcrdma_bc_rqst_get(r_xprt);
	अगर (!rqst)
		जाओ out_overflow;

	rqst->rq_reply_bytes_recvd = 0;
	rqst->rq_xid = *p;

	rqst->rq_निजी_buf.len = size;

	buf = &rqst->rq_rcv_buf;
	स_रखो(buf, 0, माप(*buf));
	buf->head[0].iov_base = p;
	buf->head[0].iov_len = size;
	buf->len = size;

	/* The receive buffer has to be hooked to the rpcrdma_req
	 * so that it is not released जबतक the req is poपूर्णांकing
	 * to its buffer, and so that it can be reposted after
	 * the Upper Layer is करोne decoding it.
	 */
	req = rpcr_to_rdmar(rqst);
	req->rl_reply = rep;
	trace_xprtrdma_cb_call(r_xprt, rqst);

	/* Queue rqst क्रम ULP's callback service */
	bc_serv = xprt->bc_serv;
	xprt_get(xprt);
	spin_lock(&bc_serv->sv_cb_lock);
	list_add(&rqst->rq_bc_list, &bc_serv->sv_cb_list);
	spin_unlock(&bc_serv->sv_cb_lock);

	wake_up(&bc_serv->sv_cb_रुकोq);

	r_xprt->rx_stats.bcall_count++;
	वापस;

out_overflow:
	pr_warn("RPC/RDMA backchannel overflow\n");
	xprt_क्रमce_disconnect(xprt);
	/* This receive buffer माला_लो reposted स्वतःmatically
	 * when the connection is re-established.
	 */
	वापस;
पूर्ण
