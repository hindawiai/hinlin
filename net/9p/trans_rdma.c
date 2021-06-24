<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0-only
/*
 * linux/fs/9p/trans_rdma.c
 *
 * RDMA transport layer based on the trans_fd.c implementation.
 *
 *  Copyright (C) 2008 by Tom Tucker <tom@खोलोgridcomputing.com>
 *  Copyright (C) 2006 by Russ Cox <rsc@swtch.com>
 *  Copyright (C) 2004-2005 by Latchesar Ionkov <lucho@ionkov.net>
 *  Copyright (C) 2004-2008 by Eric Van Hensbergen <ericvh@gmail.com>
 *  Copyright (C) 1997-2002 by Ron Minnich <rminnich@sarnoff.com>
 */

#घोषणा pr_fmt(fmt) KBUILD_MODNAME ": " fmt

#समावेश <linux/in.h>
#समावेश <linux/module.h>
#समावेश <linux/net.h>
#समावेश <linux/ipv6.h>
#समावेश <linux/kthपढ़ो.h>
#समावेश <linux/त्रुटिसं.स>
#समावेश <linux/kernel.h>
#समावेश <linux/un.h>
#समावेश <linux/uaccess.h>
#समावेश <linux/inet.h>
#समावेश <linux/idr.h>
#समावेश <linux/file.h>
#समावेश <linux/parser.h>
#समावेश <linux/semaphore.h>
#समावेश <linux/slab.h>
#समावेश <linux/seq_file.h>
#समावेश <net/9p/9p.h>
#समावेश <net/9p/client.h>
#समावेश <net/9p/transport.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>

#घोषणा P9_PORT			5640
#घोषणा P9_RDMA_SQ_DEPTH	32
#घोषणा P9_RDMA_RQ_DEPTH	32
#घोषणा P9_RDMA_SEND_SGE	4
#घोषणा P9_RDMA_RECV_SGE	4
#घोषणा P9_RDMA_IRD		0
#घोषणा P9_RDMA_ORD		0
#घोषणा P9_RDMA_TIMEOUT		30000		/* 30 seconds */
#घोषणा P9_RDMA_MAXSIZE		(1024*1024)	/* 1MB */

/**
 * काष्ठा p9_trans_rdma - RDMA transport instance
 *
 * @state: tracks the transport state machine क्रम connection setup and tear करोwn
 * @cm_id: The RDMA CM ID
 * @pd: Protection Doमुख्य poपूर्णांकer
 * @qp: Queue Pair poपूर्णांकer
 * @cq: Completion Queue poपूर्णांकer
 * @समयout: Number of uSecs to रुको क्रम connection management events
 * @privport: Whether a privileged port may be used
 * @port: The port to use
 * @sq_depth: The depth of the Send Queue
 * @sq_sem: Semaphore क्रम the SQ
 * @rq_depth: The depth of the Receive Queue.
 * @rq_sem: Semaphore क्रम the RQ
 * @excess_rc : Amount of posted Receive Contexts without a pending request.
 *		See rdma_request()
 * @addr: The remote peer's address
 * @req_lock: Protects the active request list
 * @cm_करोne: Completion event क्रम connection management tracking
 */
काष्ठा p9_trans_rdma अणु
	क्रमागत अणु
		P9_RDMA_INIT,
		P9_RDMA_ADDR_RESOLVED,
		P9_RDMA_ROUTE_RESOLVED,
		P9_RDMA_CONNECTED,
		P9_RDMA_FLUSHING,
		P9_RDMA_CLOSING,
		P9_RDMA_CLOSED,
	पूर्ण state;
	काष्ठा rdma_cm_id *cm_id;
	काष्ठा ib_pd *pd;
	काष्ठा ib_qp *qp;
	काष्ठा ib_cq *cq;
	दीर्घ समयout;
	bool privport;
	u16 port;
	पूर्णांक sq_depth;
	काष्ठा semaphore sq_sem;
	पूर्णांक rq_depth;
	काष्ठा semaphore rq_sem;
	atomic_t excess_rc;
	काष्ठा sockaddr_in addr;
	spinlock_t req_lock;

	काष्ठा completion cm_करोne;
पूर्ण;

काष्ठा p9_rdma_req;

/**
 * काष्ठा p9_rdma_context - Keeps track of in-process WR
 *
 * @cqe: completion queue entry
 * @busa: Bus address to unmap when the WR completes
 * @req: Keeps track of requests (send)
 * @rc: Keepts track of replies (receive)
 */
काष्ठा p9_rdma_context अणु
	काष्ठा ib_cqe cqe;
	dma_addr_t busa;
	जोड़ अणु
		काष्ठा p9_req_t *req;
		काष्ठा p9_fcall rc;
	पूर्ण;
पूर्ण;

/**
 * काष्ठा p9_rdma_opts - Collection of mount options
 * @port: port of connection
 * @privport: Whether a privileged port may be used
 * @sq_depth: The requested depth of the SQ. This really करोesn't need
 * to be any deeper than the number of thपढ़ोs used in the client
 * @rq_depth: The depth of the RQ. Should be greater than or equal to SQ depth
 * @समयout: Time to रुको in msecs क्रम CM events
 */
काष्ठा p9_rdma_opts अणु
	लघु port;
	bool privport;
	पूर्णांक sq_depth;
	पूर्णांक rq_depth;
	दीर्घ समयout;
पूर्ण;

/*
 * Option Parsing (code inspired by NFS code)
 */
क्रमागत अणु
	/* Options that take पूर्णांकeger arguments */
	Opt_port, Opt_rq_depth, Opt_sq_depth, Opt_समयout,
	/* Options that take no argument */
	Opt_privport,
	Opt_err,
पूर्ण;

अटल match_table_t tokens = अणु
	अणुOpt_port, "port=%u"पूर्ण,
	अणुOpt_sq_depth, "sq=%u"पूर्ण,
	अणुOpt_rq_depth, "rq=%u"पूर्ण,
	अणुOpt_समयout, "timeout=%u"पूर्ण,
	अणुOpt_privport, "privport"पूर्ण,
	अणुOpt_err, शून्यपूर्ण,
पूर्ण;

अटल पूर्णांक p9_rdma_show_options(काष्ठा seq_file *m, काष्ठा p9_client *clnt)
अणु
	काष्ठा p9_trans_rdma *rdma = clnt->trans;

	अगर (rdma->port != P9_PORT)
		seq_म_लिखो(m, ",port=%u", rdma->port);
	अगर (rdma->sq_depth != P9_RDMA_SQ_DEPTH)
		seq_म_लिखो(m, ",sq=%u", rdma->sq_depth);
	अगर (rdma->rq_depth != P9_RDMA_RQ_DEPTH)
		seq_म_लिखो(m, ",rq=%u", rdma->rq_depth);
	अगर (rdma->समयout != P9_RDMA_TIMEOUT)
		seq_म_लिखो(m, ",timeout=%lu", rdma->समयout);
	अगर (rdma->privport)
		seq_माला_दो(m, ",privport");
	वापस 0;
पूर्ण

/**
 * parse_opts - parse mount options पूर्णांकo rdma options काष्ठाure
 * @params: options string passed from mount
 * @opts: rdma transport-specअगरic काष्ठाure to parse options पूर्णांकo
 *
 * Returns 0 upon success, -ERRNO upon failure
 */
अटल पूर्णांक parse_opts(अक्षर *params, काष्ठा p9_rdma_opts *opts)
अणु
	अक्षर *p;
	substring_t args[MAX_OPT_ARGS];
	पूर्णांक option;
	अक्षर *options, *पंचांगp_options;

	opts->port = P9_PORT;
	opts->sq_depth = P9_RDMA_SQ_DEPTH;
	opts->rq_depth = P9_RDMA_RQ_DEPTH;
	opts->समयout = P9_RDMA_TIMEOUT;
	opts->privport = false;

	अगर (!params)
		वापस 0;

	पंचांगp_options = kstrdup(params, GFP_KERNEL);
	अगर (!पंचांगp_options) अणु
		p9_debug(P9_DEBUG_ERROR,
			 "failed to allocate copy of option string\n");
		वापस -ENOMEM;
	पूर्ण
	options = पंचांगp_options;

	जबतक ((p = strsep(&options, ",")) != शून्य) अणु
		पूर्णांक token;
		पूर्णांक r;
		अगर (!*p)
			जारी;
		token = match_token(p, tokens, args);
		अगर ((token != Opt_err) && (token != Opt_privport)) अणु
			r = match_पूर्णांक(&args[0], &option);
			अगर (r < 0) अणु
				p9_debug(P9_DEBUG_ERROR,
					 "integer field, but no integer?\n");
				जारी;
			पूर्ण
		पूर्ण
		चयन (token) अणु
		हाल Opt_port:
			opts->port = option;
			अवरोध;
		हाल Opt_sq_depth:
			opts->sq_depth = option;
			अवरोध;
		हाल Opt_rq_depth:
			opts->rq_depth = option;
			अवरोध;
		हाल Opt_समयout:
			opts->समयout = option;
			अवरोध;
		हाल Opt_privport:
			opts->privport = true;
			अवरोध;
		शेष:
			जारी;
		पूर्ण
	पूर्ण
	/* RQ must be at least as large as the SQ */
	opts->rq_depth = max(opts->rq_depth, opts->sq_depth);
	kमुक्त(पंचांगp_options);
	वापस 0;
पूर्ण

अटल पूर्णांक
p9_cm_event_handler(काष्ठा rdma_cm_id *id, काष्ठा rdma_cm_event *event)
अणु
	काष्ठा p9_client *c = id->context;
	काष्ठा p9_trans_rdma *rdma = c->trans;
	चयन (event->event) अणु
	हाल RDMA_CM_EVENT_ADDR_RESOLVED:
		BUG_ON(rdma->state != P9_RDMA_INIT);
		rdma->state = P9_RDMA_ADDR_RESOLVED;
		अवरोध;

	हाल RDMA_CM_EVENT_ROUTE_RESOLVED:
		BUG_ON(rdma->state != P9_RDMA_ADDR_RESOLVED);
		rdma->state = P9_RDMA_ROUTE_RESOLVED;
		अवरोध;

	हाल RDMA_CM_EVENT_ESTABLISHED:
		BUG_ON(rdma->state != P9_RDMA_ROUTE_RESOLVED);
		rdma->state = P9_RDMA_CONNECTED;
		अवरोध;

	हाल RDMA_CM_EVENT_DISCONNECTED:
		अगर (rdma)
			rdma->state = P9_RDMA_CLOSED;
		c->status = Disconnected;
		अवरोध;

	हाल RDMA_CM_EVENT_TIMEWAIT_EXIT:
		अवरोध;

	हाल RDMA_CM_EVENT_ADDR_CHANGE:
	हाल RDMA_CM_EVENT_ROUTE_ERROR:
	हाल RDMA_CM_EVENT_DEVICE_REMOVAL:
	हाल RDMA_CM_EVENT_MULTICAST_JOIN:
	हाल RDMA_CM_EVENT_MULTICAST_ERROR:
	हाल RDMA_CM_EVENT_REJECTED:
	हाल RDMA_CM_EVENT_CONNECT_REQUEST:
	हाल RDMA_CM_EVENT_CONNECT_RESPONSE:
	हाल RDMA_CM_EVENT_CONNECT_ERROR:
	हाल RDMA_CM_EVENT_ADDR_ERROR:
	हाल RDMA_CM_EVENT_UNREACHABLE:
		c->status = Disconnected;
		rdma_disconnect(rdma->cm_id);
		अवरोध;
	शेष:
		BUG();
	पूर्ण
	complete(&rdma->cm_करोne);
	वापस 0;
पूर्ण

अटल व्योम
recv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा p9_client *client = cq->cq_context;
	काष्ठा p9_trans_rdma *rdma = client->trans;
	काष्ठा p9_rdma_context *c =
		container_of(wc->wr_cqe, काष्ठा p9_rdma_context, cqe);
	काष्ठा p9_req_t *req;
	पूर्णांक err = 0;
	पूर्णांक16_t tag;

	req = शून्य;
	ib_dma_unmap_single(rdma->cm_id->device, c->busa, client->msize,
							 DMA_FROM_DEVICE);

	अगर (wc->status != IB_WC_SUCCESS)
		जाओ err_out;

	c->rc.size = wc->byte_len;
	err = p9_parse_header(&c->rc, शून्य, शून्य, &tag, 1);
	अगर (err)
		जाओ err_out;

	req = p9_tag_lookup(client, tag);
	अगर (!req)
		जाओ err_out;

	/* Check that we have not yet received a reply क्रम this request.
	 */
	अगर (unlikely(req->rc.sdata)) अणु
		pr_err("Duplicate reply for request %d", tag);
		जाओ err_out;
	पूर्ण

	req->rc.size = c->rc.size;
	req->rc.sdata = c->rc.sdata;
	p9_client_cb(client, req, REQ_STATUS_RCVD);

 out:
	up(&rdma->rq_sem);
	kमुक्त(c);
	वापस;

 err_out:
	p9_debug(P9_DEBUG_ERROR, "req %p err %d status %d\n",
			req, err, wc->status);
	rdma->state = P9_RDMA_FLUSHING;
	client->status = Disconnected;
	जाओ out;
पूर्ण

अटल व्योम
send_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा p9_client *client = cq->cq_context;
	काष्ठा p9_trans_rdma *rdma = client->trans;
	काष्ठा p9_rdma_context *c =
		container_of(wc->wr_cqe, काष्ठा p9_rdma_context, cqe);

	ib_dma_unmap_single(rdma->cm_id->device,
			    c->busa, c->req->tc.size,
			    DMA_TO_DEVICE);
	up(&rdma->sq_sem);
	p9_req_put(c->req);
	kमुक्त(c);
पूर्ण

अटल व्योम qp_event_handler(काष्ठा ib_event *event, व्योम *context)
अणु
	p9_debug(P9_DEBUG_ERROR, "QP event %d context %p\n",
		 event->event, context);
पूर्ण

अटल व्योम rdma_destroy_trans(काष्ठा p9_trans_rdma *rdma)
अणु
	अगर (!rdma)
		वापस;

	अगर (rdma->qp && !IS_ERR(rdma->qp))
		ib_destroy_qp(rdma->qp);

	अगर (rdma->pd && !IS_ERR(rdma->pd))
		ib_dealloc_pd(rdma->pd);

	अगर (rdma->cq && !IS_ERR(rdma->cq))
		ib_मुक्त_cq(rdma->cq);

	अगर (rdma->cm_id && !IS_ERR(rdma->cm_id))
		rdma_destroy_id(rdma->cm_id);

	kमुक्त(rdma);
पूर्ण

अटल पूर्णांक
post_recv(काष्ठा p9_client *client, काष्ठा p9_rdma_context *c)
अणु
	काष्ठा p9_trans_rdma *rdma = client->trans;
	काष्ठा ib_recv_wr wr;
	काष्ठा ib_sge sge;

	c->busa = ib_dma_map_single(rdma->cm_id->device,
				    c->rc.sdata, client->msize,
				    DMA_FROM_DEVICE);
	अगर (ib_dma_mapping_error(rdma->cm_id->device, c->busa))
		जाओ error;

	c->cqe.करोne = recv_करोne;

	sge.addr = c->busa;
	sge.length = client->msize;
	sge.lkey = rdma->pd->local_dma_lkey;

	wr.next = शून्य;
	wr.wr_cqe = &c->cqe;
	wr.sg_list = &sge;
	wr.num_sge = 1;
	वापस ib_post_recv(rdma->qp, &wr, शून्य);

 error:
	p9_debug(P9_DEBUG_ERROR, "EIO\n");
	वापस -EIO;
पूर्ण

अटल पूर्णांक rdma_request(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	काष्ठा p9_trans_rdma *rdma = client->trans;
	काष्ठा ib_send_wr wr;
	काष्ठा ib_sge sge;
	पूर्णांक err = 0;
	अचिन्हित दीर्घ flags;
	काष्ठा p9_rdma_context *c = शून्य;
	काष्ठा p9_rdma_context *rpl_context = शून्य;

	/* When an error occurs between posting the recv and the send,
	 * there will be a receive context posted without a pending request.
	 * Since there is no way to "un-post" it, we remember it and skip
	 * post_recv() क्रम the next request.
	 * So here,
	 * see अगर we are this `next request' and need to असलorb an excess rc.
	 * If yes, then drop and मुक्त our own, and करो not recv_post().
	 **/
	अगर (unlikely(atomic_पढ़ो(&rdma->excess_rc) > 0)) अणु
		अगर ((atomic_sub_वापस(1, &rdma->excess_rc) >= 0)) अणु
			/* Got one! */
			p9_fcall_fini(&req->rc);
			req->rc.sdata = शून्य;
			जाओ करोnt_need_post_recv;
		पूर्ण अन्यथा अणु
			/* We raced and lost. */
			atomic_inc(&rdma->excess_rc);
		पूर्ण
	पूर्ण

	/* Allocate an fcall क्रम the reply */
	rpl_context = kदो_स्मृति(माप *rpl_context, GFP_NOFS);
	अगर (!rpl_context) अणु
		err = -ENOMEM;
		जाओ recv_error;
	पूर्ण
	rpl_context->rc.sdata = req->rc.sdata;

	/*
	 * Post a receive buffer क्रम this request. We need to ensure
	 * there is a reply buffer available क्रम every outstanding
	 * request. A flushed request can result in no reply क्रम an
	 * outstanding request, so we must keep a count to aव्योम
	 * overflowing the RQ.
	 */
	अगर (करोwn_पूर्णांकerruptible(&rdma->rq_sem)) अणु
		err = -EINTR;
		जाओ recv_error;
	पूर्ण

	err = post_recv(client, rpl_context);
	अगर (err) अणु
		p9_debug(P9_DEBUG_ERROR, "POST RECV failed: %d\n", err);
		जाओ recv_error;
	पूर्ण
	/* हटाओ posted receive buffer from request काष्ठाure */
	req->rc.sdata = शून्य;

करोnt_need_post_recv:
	/* Post the request */
	c = kदो_स्मृति(माप *c, GFP_NOFS);
	अगर (!c) अणु
		err = -ENOMEM;
		जाओ send_error;
	पूर्ण
	c->req = req;

	c->busa = ib_dma_map_single(rdma->cm_id->device,
				    c->req->tc.sdata, c->req->tc.size,
				    DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(rdma->cm_id->device, c->busa)) अणु
		err = -EIO;
		जाओ send_error;
	पूर्ण

	c->cqe.करोne = send_करोne;

	sge.addr = c->busa;
	sge.length = c->req->tc.size;
	sge.lkey = rdma->pd->local_dma_lkey;

	wr.next = शून्य;
	wr.wr_cqe = &c->cqe;
	wr.opcode = IB_WR_SEND;
	wr.send_flags = IB_SEND_SIGNALED;
	wr.sg_list = &sge;
	wr.num_sge = 1;

	अगर (करोwn_पूर्णांकerruptible(&rdma->sq_sem)) अणु
		err = -EINTR;
		जाओ send_error;
	पूर्ण

	/* Mark request as `sent' *beक्रमe* we actually send it,
	 * because करोing अगर after could erase the REQ_STATUS_RCVD
	 * status in हाल of a very fast reply.
	 */
	req->status = REQ_STATUS_SENT;
	err = ib_post_send(rdma->qp, &wr, शून्य);
	अगर (err)
		जाओ send_error;

	/* Success */
	वापस 0;

 /* Handle errors that happened during or जबतक preparing the send: */
 send_error:
	req->status = REQ_STATUS_ERROR;
	kमुक्त(c);
	p9_debug(P9_DEBUG_ERROR, "Error %d in rdma_request()\n", err);

	/* Ach.
	 *  We did recv_post(), but not send. We have one recv_post in excess.
	 */
	atomic_inc(&rdma->excess_rc);
	वापस err;

 /* Handle errors that happened during or जबतक preparing post_recv(): */
 recv_error:
	kमुक्त(rpl_context);
	spin_lock_irqsave(&rdma->req_lock, flags);
	अगर (err != -EINTR && rdma->state < P9_RDMA_CLOSING) अणु
		rdma->state = P9_RDMA_CLOSING;
		spin_unlock_irqrestore(&rdma->req_lock, flags);
		rdma_disconnect(rdma->cm_id);
	पूर्ण अन्यथा
		spin_unlock_irqrestore(&rdma->req_lock, flags);
	वापस err;
पूर्ण

अटल व्योम rdma_बंद(काष्ठा p9_client *client)
अणु
	काष्ठा p9_trans_rdma *rdma;

	अगर (!client)
		वापस;

	rdma = client->trans;
	अगर (!rdma)
		वापस;

	client->status = Disconnected;
	rdma_disconnect(rdma->cm_id);
	rdma_destroy_trans(rdma);
पूर्ण

/**
 * alloc_rdma - Allocate and initialize the rdma transport काष्ठाure
 * @opts: Mount options काष्ठाure
 */
अटल काष्ठा p9_trans_rdma *alloc_rdma(काष्ठा p9_rdma_opts *opts)
अणु
	काष्ठा p9_trans_rdma *rdma;

	rdma = kzalloc(माप(काष्ठा p9_trans_rdma), GFP_KERNEL);
	अगर (!rdma)
		वापस शून्य;

	rdma->port = opts->port;
	rdma->privport = opts->privport;
	rdma->sq_depth = opts->sq_depth;
	rdma->rq_depth = opts->rq_depth;
	rdma->समयout = opts->समयout;
	spin_lock_init(&rdma->req_lock);
	init_completion(&rdma->cm_करोne);
	sema_init(&rdma->sq_sem, rdma->sq_depth);
	sema_init(&rdma->rq_sem, rdma->rq_depth);
	atomic_set(&rdma->excess_rc, 0);

	वापस rdma;
पूर्ण

अटल पूर्णांक rdma_cancel(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	/* Nothing to करो here.
	 * We will take care of it (अगर we have to) in rdma_cancelled()
	 */
	वापस 1;
पूर्ण

/* A request has been fully flushed without a reply.
 * That means we have posted one buffer in excess.
 */
अटल पूर्णांक rdma_cancelled(काष्ठा p9_client *client, काष्ठा p9_req_t *req)
अणु
	काष्ठा p9_trans_rdma *rdma = client->trans;
	atomic_inc(&rdma->excess_rc);
	वापस 0;
पूर्ण

अटल पूर्णांक p9_rdma_bind_privport(काष्ठा p9_trans_rdma *rdma)
अणु
	काष्ठा sockaddr_in cl = अणु
		.sin_family = AF_INET,
		.sin_addr.s_addr = htonl(INADDR_ANY),
	पूर्ण;
	पूर्णांक port, err = -EINVAL;

	क्रम (port = P9_DEF_MAX_RESVPORT; port >= P9_DEF_MIN_RESVPORT; port--) अणु
		cl.sin_port = htons((uलघु)port);
		err = rdma_bind_addr(rdma->cm_id, (काष्ठा sockaddr *)&cl);
		अगर (err != -EADDRINUSE)
			अवरोध;
	पूर्ण
	वापस err;
पूर्ण

/**
 * rdma_create_trans - Transport method क्रम creating a transport instance
 * @client: client instance
 * @addr: IP address string
 * @args: Mount options string
 */
अटल पूर्णांक
rdma_create_trans(काष्ठा p9_client *client, स्थिर अक्षर *addr, अक्षर *args)
अणु
	पूर्णांक err;
	काष्ठा p9_rdma_opts opts;
	काष्ठा p9_trans_rdma *rdma;
	काष्ठा rdma_conn_param conn_param;
	काष्ठा ib_qp_init_attr qp_attr;

	अगर (addr == शून्य)
		वापस -EINVAL;

	/* Parse the transport specअगरic mount options */
	err = parse_opts(args, &opts);
	अगर (err < 0)
		वापस err;

	/* Create and initialize the RDMA transport काष्ठाure */
	rdma = alloc_rdma(&opts);
	अगर (!rdma)
		वापस -ENOMEM;

	/* Create the RDMA CM ID */
	rdma->cm_id = rdma_create_id(&init_net, p9_cm_event_handler, client,
				     RDMA_PS_TCP, IB_QPT_RC);
	अगर (IS_ERR(rdma->cm_id))
		जाओ error;

	/* Associate the client with the transport */
	client->trans = rdma;

	/* Bind to a privileged port अगर we need to */
	अगर (opts.privport) अणु
		err = p9_rdma_bind_privport(rdma);
		अगर (err < 0) अणु
			pr_err("%s (%d): problem binding to privport: %d\n",
			       __func__, task_pid_nr(current), -err);
			जाओ error;
		पूर्ण
	पूर्ण

	/* Resolve the server's address */
	rdma->addr.sin_family = AF_INET;
	rdma->addr.sin_addr.s_addr = in_aton(addr);
	rdma->addr.sin_port = htons(opts.port);
	err = rdma_resolve_addr(rdma->cm_id, शून्य,
				(काष्ठा sockaddr *)&rdma->addr,
				rdma->समयout);
	अगर (err)
		जाओ error;
	err = रुको_क्रम_completion_पूर्णांकerruptible(&rdma->cm_करोne);
	अगर (err || (rdma->state != P9_RDMA_ADDR_RESOLVED))
		जाओ error;

	/* Resolve the route to the server */
	err = rdma_resolve_route(rdma->cm_id, rdma->समयout);
	अगर (err)
		जाओ error;
	err = रुको_क्रम_completion_पूर्णांकerruptible(&rdma->cm_करोne);
	अगर (err || (rdma->state != P9_RDMA_ROUTE_RESOLVED))
		जाओ error;

	/* Create the Completion Queue */
	rdma->cq = ib_alloc_cq_any(rdma->cm_id->device, client,
				   opts.sq_depth + opts.rq_depth + 1,
				   IB_POLL_SOFTIRQ);
	अगर (IS_ERR(rdma->cq))
		जाओ error;

	/* Create the Protection Doमुख्य */
	rdma->pd = ib_alloc_pd(rdma->cm_id->device, 0);
	अगर (IS_ERR(rdma->pd))
		जाओ error;

	/* Create the Queue Pair */
	स_रखो(&qp_attr, 0, माप qp_attr);
	qp_attr.event_handler = qp_event_handler;
	qp_attr.qp_context = client;
	qp_attr.cap.max_send_wr = opts.sq_depth;
	qp_attr.cap.max_recv_wr = opts.rq_depth;
	qp_attr.cap.max_send_sge = P9_RDMA_SEND_SGE;
	qp_attr.cap.max_recv_sge = P9_RDMA_RECV_SGE;
	qp_attr.sq_sig_type = IB_SIGNAL_REQ_WR;
	qp_attr.qp_type = IB_QPT_RC;
	qp_attr.send_cq = rdma->cq;
	qp_attr.recv_cq = rdma->cq;
	err = rdma_create_qp(rdma->cm_id, rdma->pd, &qp_attr);
	अगर (err)
		जाओ error;
	rdma->qp = rdma->cm_id->qp;

	/* Request a connection */
	स_रखो(&conn_param, 0, माप(conn_param));
	conn_param.निजी_data = शून्य;
	conn_param.निजी_data_len = 0;
	conn_param.responder_resources = P9_RDMA_IRD;
	conn_param.initiator_depth = P9_RDMA_ORD;
	err = rdma_connect(rdma->cm_id, &conn_param);
	अगर (err)
		जाओ error;
	err = रुको_क्रम_completion_पूर्णांकerruptible(&rdma->cm_करोne);
	अगर (err || (rdma->state != P9_RDMA_CONNECTED))
		जाओ error;

	client->status = Connected;

	वापस 0;

error:
	rdma_destroy_trans(rdma);
	वापस -ENOTCONN;
पूर्ण

अटल काष्ठा p9_trans_module p9_rdma_trans = अणु
	.name = "rdma",
	.maxsize = P9_RDMA_MAXSIZE,
	.def = 0,
	.owner = THIS_MODULE,
	.create = rdma_create_trans,
	.बंद = rdma_बंद,
	.request = rdma_request,
	.cancel = rdma_cancel,
	.cancelled = rdma_cancelled,
	.show_options = p9_rdma_show_options,
पूर्ण;

/**
 * p9_trans_rdma_init - Register the 9P RDMA transport driver
 */
अटल पूर्णांक __init p9_trans_rdma_init(व्योम)
अणु
	v9fs_रेजिस्टर_trans(&p9_rdma_trans);
	वापस 0;
पूर्ण

अटल व्योम __निकास p9_trans_rdma_निकास(व्योम)
अणु
	v9fs_unरेजिस्टर_trans(&p9_rdma_trans);
पूर्ण

module_init(p9_trans_rdma_init);
module_निकास(p9_trans_rdma_निकास);

MODULE_AUTHOR("Tom Tucker <tom@opengridcomputing.com>");
MODULE_DESCRIPTION("RDMA Transport for 9P");
MODULE_LICENSE("Dual BSD/GPL");
