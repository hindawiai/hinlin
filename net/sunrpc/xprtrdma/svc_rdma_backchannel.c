<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015-2018 Oracle.  All rights reserved.
 *
 * Support क्रम reverse-direction RPCs on RPC/RDMA (server-side).
 */

#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

/**
 * svc_rdma_handle_bc_reply - Process incoming backchannel Reply
 * @rqstp: resources क्रम handling the Reply
 * @rctxt: Received message
 *
 */
व्योम svc_rdma_handle_bc_reply(काष्ठा svc_rqst *rqstp,
			      काष्ठा svc_rdma_recv_ctxt *rctxt)
अणु
	काष्ठा svc_xprt *sxprt = rqstp->rq_xprt;
	काष्ठा rpc_xprt *xprt = sxprt->xpt_bc_xprt;
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	काष्ठा xdr_buf *rcvbuf = &rqstp->rq_arg;
	काष्ठा kvec *dst, *src = &rcvbuf->head[0];
	__be32 *rdma_resp = rctxt->rc_recv_buf;
	काष्ठा rpc_rqst *req;
	u32 credits;

	spin_lock(&xprt->queue_lock);
	req = xprt_lookup_rqst(xprt, *rdma_resp);
	अगर (!req)
		जाओ out_unlock;

	dst = &req->rq_निजी_buf.head[0];
	स_नकल(&req->rq_निजी_buf, &req->rq_rcv_buf, माप(काष्ठा xdr_buf));
	अगर (dst->iov_len < src->iov_len)
		जाओ out_unlock;
	स_नकल(dst->iov_base, src->iov_base, src->iov_len);
	xprt_pin_rqst(req);
	spin_unlock(&xprt->queue_lock);

	credits = be32_to_cpup(rdma_resp + 2);
	अगर (credits == 0)
		credits = 1;	/* करोn't deadlock */
	अन्यथा अगर (credits > r_xprt->rx_buf.rb_bc_max_requests)
		credits = r_xprt->rx_buf.rb_bc_max_requests;
	spin_lock(&xprt->transport_lock);
	xprt->cwnd = credits << RPC_CWNDSHIFT;
	spin_unlock(&xprt->transport_lock);

	spin_lock(&xprt->queue_lock);
	xprt_complete_rqst(req->rq_task, rcvbuf->len);
	xprt_unpin_rqst(req);
	rcvbuf->len = 0;

out_unlock:
	spin_unlock(&xprt->queue_lock);
पूर्ण

/* Send a reverse-direction RPC Call.
 *
 * Caller holds the connection's mutex and has alपढ़ोy marshaled
 * the RPC/RDMA request.
 *
 * This is similar to svc_rdma_send_reply_msg, but takes a काष्ठा
 * rpc_rqst instead, करोes not support chunks, and aव्योमs blocking
 * memory allocation.
 *
 * XXX: There is still an opportunity to block in svc_rdma_send()
 * अगर there are no SQ entries to post the Send. This may occur अगर
 * the adapter has a small maximum SQ depth.
 */
अटल पूर्णांक svc_rdma_bc_sendto(काष्ठा svcxprt_rdma *rdma,
			      काष्ठा rpc_rqst *rqst,
			      काष्ठा svc_rdma_send_ctxt *sctxt)
अणु
	काष्ठा svc_rdma_recv_ctxt *rctxt;
	पूर्णांक ret;

	rctxt = svc_rdma_recv_ctxt_get(rdma);
	अगर (!rctxt)
		वापस -EIO;

	ret = svc_rdma_map_reply_msg(rdma, sctxt, rctxt, &rqst->rq_snd_buf);
	svc_rdma_recv_ctxt_put(rdma, rctxt);
	अगर (ret < 0)
		वापस -EIO;

	/* Bump page refcnt so Send completion करोesn't release
	 * the rq_buffer beक्रमe all retransmits are complete.
	 */
	get_page(virt_to_page(rqst->rq_buffer));
	sctxt->sc_send_wr.opcode = IB_WR_SEND;
	ret = svc_rdma_send(rdma, sctxt);
	अगर (ret < 0)
		वापस ret;

	ret = रुको_क्रम_completion_समाप्तable(&sctxt->sc_करोne);
	svc_rdma_send_ctxt_put(rdma, sctxt);
	वापस ret;
पूर्ण

/* Server-side transport endpoपूर्णांक wants a whole page क्रम its send
 * buffer. The client RPC code स्थिरructs the RPC header in this
 * buffer beक्रमe it invokes ->send_request.
 */
अटल पूर्णांक
xprt_rdma_bc_allocate(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *rqst = task->tk_rqstp;
	माप_प्रकार size = rqst->rq_callsize;
	काष्ठा page *page;

	अगर (size > PAGE_SIZE) अणु
		WARN_ONCE(1, "svcrdma: large bc buffer request (size %zu)\n",
			  size);
		वापस -EINVAL;
	पूर्ण

	page = alloc_page(RPCRDMA_DEF_GFP);
	अगर (!page)
		वापस -ENOMEM;
	rqst->rq_buffer = page_address(page);

	rqst->rq_rbuffer = kदो_स्मृति(rqst->rq_rcvsize, RPCRDMA_DEF_GFP);
	अगर (!rqst->rq_rbuffer) अणु
		put_page(page);
		वापस -ENOMEM;
	पूर्ण
	वापस 0;
पूर्ण

अटल व्योम
xprt_rdma_bc_मुक्त(काष्ठा rpc_task *task)
अणु
	काष्ठा rpc_rqst *rqst = task->tk_rqstp;

	put_page(virt_to_page(rqst->rq_buffer));
	kमुक्त(rqst->rq_rbuffer);
पूर्ण

अटल पूर्णांक
rpcrdma_bc_send_request(काष्ठा svcxprt_rdma *rdma, काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा rpc_xprt *xprt = rqst->rq_xprt;
	काष्ठा rpcrdma_xprt *r_xprt = rpcx_to_rdmax(xprt);
	काष्ठा svc_rdma_send_ctxt *ctxt;
	__be32 *p;
	पूर्णांक rc;

	ctxt = svc_rdma_send_ctxt_get(rdma);
	अगर (!ctxt)
		जाओ drop_connection;

	p = xdr_reserve_space(&ctxt->sc_stream, RPCRDMA_HDRLEN_MIN);
	अगर (!p)
		जाओ put_ctxt;
	*p++ = rqst->rq_xid;
	*p++ = rpcrdma_version;
	*p++ = cpu_to_be32(r_xprt->rx_buf.rb_bc_max_requests);
	*p++ = rdma_msg;
	*p++ = xdr_zero;
	*p++ = xdr_zero;
	*p   = xdr_zero;

	rqst->rq_xसमय = kसमय_get();
	rc = svc_rdma_bc_sendto(rdma, rqst, ctxt);
	अगर (rc)
		जाओ put_ctxt;
	वापस 0;

put_ctxt:
	svc_rdma_send_ctxt_put(rdma, ctxt);

drop_connection:
	वापस -ENOTCONN;
पूर्ण

/**
 * xprt_rdma_bc_send_request - Send a reverse-direction Call
 * @rqst: rpc_rqst containing Call message to be sent
 *
 * Return values:
 *   %0 अगर the message was sent successfully
 *   %ENOTCONN अगर the message was not sent
 */
अटल पूर्णांक xprt_rdma_bc_send_request(काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा svc_xprt *sxprt = rqst->rq_xprt->bc_xprt;
	काष्ठा svcxprt_rdma *rdma =
		container_of(sxprt, काष्ठा svcxprt_rdma, sc_xprt);
	पूर्णांक ret;

	अगर (test_bit(XPT_DEAD, &sxprt->xpt_flags))
		वापस -ENOTCONN;

	ret = rpcrdma_bc_send_request(rdma, rqst);
	अगर (ret == -ENOTCONN)
		svc_बंद_xprt(sxprt);
	वापस ret;
पूर्ण

अटल व्योम
xprt_rdma_bc_बंद(काष्ठा rpc_xprt *xprt)
अणु
	xprt_disconnect_करोne(xprt);
	xprt->cwnd = RPC_CWNDSHIFT;
पूर्ण

अटल व्योम
xprt_rdma_bc_put(काष्ठा rpc_xprt *xprt)
अणु
	xprt_rdma_मुक्त_addresses(xprt);
	xprt_मुक्त(xprt);
पूर्ण

अटल स्थिर काष्ठा rpc_xprt_ops xprt_rdma_bc_procs = अणु
	.reserve_xprt		= xprt_reserve_xprt_cong,
	.release_xprt		= xprt_release_xprt_cong,
	.alloc_slot		= xprt_alloc_slot,
	.मुक्त_slot		= xprt_मुक्त_slot,
	.release_request	= xprt_release_rqst_cong,
	.buf_alloc		= xprt_rdma_bc_allocate,
	.buf_मुक्त		= xprt_rdma_bc_मुक्त,
	.send_request		= xprt_rdma_bc_send_request,
	.रुको_क्रम_reply_request	= xprt_रुको_क्रम_reply_request_def,
	.बंद			= xprt_rdma_bc_बंद,
	.destroy		= xprt_rdma_bc_put,
	.prपूर्णांक_stats		= xprt_rdma_prपूर्णांक_stats
पूर्ण;

अटल स्थिर काष्ठा rpc_समयout xprt_rdma_bc_समयout = अणु
	.to_initval = 60 * HZ,
	.to_maxval = 60 * HZ,
पूर्ण;

/* It shouldn't matter अगर the number of backchannel session slots
 * करोesn't match the number of RPC/RDMA credits. That just means
 * one or the other will have extra slots that aren't used.
 */
अटल काष्ठा rpc_xprt *
xprt_setup_rdma_bc(काष्ठा xprt_create *args)
अणु
	काष्ठा rpc_xprt *xprt;
	काष्ठा rpcrdma_xprt *new_xprt;

	अगर (args->addrlen > माप(xprt->addr))
		वापस ERR_PTR(-EBADF);

	xprt = xprt_alloc(args->net, माप(*new_xprt),
			  RPCRDMA_MAX_BC_REQUESTS,
			  RPCRDMA_MAX_BC_REQUESTS);
	अगर (!xprt)
		वापस ERR_PTR(-ENOMEM);

	xprt->समयout = &xprt_rdma_bc_समयout;
	xprt_set_bound(xprt);
	xprt_set_connected(xprt);
	xprt->bind_समयout = 0;
	xprt->reestablish_समयout = 0;
	xprt->idle_समयout = 0;

	xprt->prot = XPRT_TRANSPORT_BC_RDMA;
	xprt->ops = &xprt_rdma_bc_procs;

	स_नकल(&xprt->addr, args->dstaddr, args->addrlen);
	xprt->addrlen = args->addrlen;
	xprt_rdma_क्रमmat_addresses(xprt, (काष्ठा sockaddr *)&xprt->addr);
	xprt->resvport = 0;

	xprt->max_payload = xprt_rdma_max_अंतरभूत_पढ़ो;

	new_xprt = rpcx_to_rdmax(xprt);
	new_xprt->rx_buf.rb_bc_max_requests = xprt->max_reqs;

	xprt_get(xprt);
	args->bc_xprt->xpt_bc_xprt = xprt;
	xprt->bc_xprt = args->bc_xprt;

	/* Final put क्रम backchannel xprt is in __svc_rdma_मुक्त */
	xprt_get(xprt);
	वापस xprt;
पूर्ण

काष्ठा xprt_class xprt_rdma_bc = अणु
	.list			= LIST_HEAD_INIT(xprt_rdma_bc.list),
	.name			= "rdma backchannel",
	.owner			= THIS_MODULE,
	.ident			= XPRT_TRANSPORT_BC_RDMA,
	.setup			= xprt_setup_rdma_bc,
पूर्ण;
