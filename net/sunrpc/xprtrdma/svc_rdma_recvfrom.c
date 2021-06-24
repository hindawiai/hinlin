<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2016-2018 Oracle. All rights reserved.
 * Copyright (c) 2014 Open Grid Computing, Inc. All rights reserved.
 * Copyright (c) 2005-2006 Network Appliance, Inc. All rights reserved.
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

/* Operation
 *
 * The मुख्य entry poपूर्णांक is svc_rdma_recvfrom. This is called from
 * svc_recv when the transport indicates there is incoming data to
 * be पढ़ो. "Data Ready" is संकेतed when an RDMA Receive completes,
 * or when a set of RDMA Reads complete.
 *
 * An svc_rqst is passed in. This काष्ठाure contains an array of
 * मुक्त pages (rq_pages) that will contain the incoming RPC message.
 *
 * Short messages are moved directly पूर्णांकo svc_rqst::rq_arg, and
 * the RPC Call is पढ़ोy to be processed by the Upper Layer.
 * svc_rdma_recvfrom वापसs the length of the RPC Call message,
 * completing the reception of the RPC Call.
 *
 * However, when an incoming message has Read chunks,
 * svc_rdma_recvfrom must post RDMA Reads to pull the RPC Call's
 * data payload from the client. svc_rdma_recvfrom sets up the
 * RDMA Reads using pages in svc_rqst::rq_pages, which are
 * transferred to an svc_rdma_recv_ctxt क्रम the duration of the
 * I/O. svc_rdma_recvfrom then वापसs zero, since the RPC message
 * is still not yet पढ़ोy.
 *
 * When the Read chunk payloads have become available on the
 * server, "Data Ready" is उठाओd again, and svc_recv calls
 * svc_rdma_recvfrom again. This second call may use a dअगरferent
 * svc_rqst than the first one, thus any inक्रमmation that needs
 * to be preserved across these two calls is kept in an
 * svc_rdma_recv_ctxt.
 *
 * The second call to svc_rdma_recvfrom perक्रमms final assembly
 * of the RPC Call message, using the RDMA Read sink pages kept in
 * the svc_rdma_recv_ctxt. The xdr_buf is copied from the
 * svc_rdma_recv_ctxt to the second svc_rqst. The second call वापसs
 * the length of the completed RPC Call message.
 *
 * Page Management
 *
 * Pages under I/O must be transferred from the first svc_rqst to an
 * svc_rdma_recv_ctxt beक्रमe the first svc_rdma_recvfrom call वापसs.
 *
 * The first svc_rqst supplies pages क्रम RDMA Reads. These are moved
 * from rqstp::rq_pages पूर्णांकo ctxt::pages. The consumed elements of
 * the rq_pages array are set to शून्य and refilled with the first
 * svc_rdma_recvfrom call वापसs.
 *
 * During the second svc_rdma_recvfrom call, RDMA Read sink pages
 * are transferred from the svc_rdma_recv_ctxt to the second svc_rqst.
 */

#समावेश <linux/slab.h>
#समावेश <linux/spinlock.h>
#समावेश <यंत्र/unaligned.h>
#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>

#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/debug.h>
#समावेश <linux/sunrpc/rpc_rdma.h>
#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

अटल व्योम svc_rdma_wc_receive(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);

अटल अंतरभूत काष्ठा svc_rdma_recv_ctxt *
svc_rdma_next_recv_ctxt(काष्ठा list_head *list)
अणु
	वापस list_first_entry_or_null(list, काष्ठा svc_rdma_recv_ctxt,
					rc_list);
पूर्ण

अटल व्योम svc_rdma_recv_cid_init(काष्ठा svcxprt_rdma *rdma,
				   काष्ठा rpc_rdma_cid *cid)
अणु
	cid->ci_queue_id = rdma->sc_rq_cq->res.id;
	cid->ci_completion_id = atomic_inc_वापस(&rdma->sc_completion_ids);
पूर्ण

अटल काष्ठा svc_rdma_recv_ctxt *
svc_rdma_recv_ctxt_alloc(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_recv_ctxt *ctxt;
	dma_addr_t addr;
	व्योम *buffer;

	ctxt = kदो_स्मृति(माप(*ctxt), GFP_KERNEL);
	अगर (!ctxt)
		जाओ fail0;
	buffer = kदो_स्मृति(rdma->sc_max_req_size, GFP_KERNEL);
	अगर (!buffer)
		जाओ fail1;
	addr = ib_dma_map_single(rdma->sc_pd->device, buffer,
				 rdma->sc_max_req_size, DMA_FROM_DEVICE);
	अगर (ib_dma_mapping_error(rdma->sc_pd->device, addr))
		जाओ fail2;

	svc_rdma_recv_cid_init(rdma, &ctxt->rc_cid);
	pcl_init(&ctxt->rc_call_pcl);
	pcl_init(&ctxt->rc_पढ़ो_pcl);
	pcl_init(&ctxt->rc_ग_लिखो_pcl);
	pcl_init(&ctxt->rc_reply_pcl);

	ctxt->rc_recv_wr.next = शून्य;
	ctxt->rc_recv_wr.wr_cqe = &ctxt->rc_cqe;
	ctxt->rc_recv_wr.sg_list = &ctxt->rc_recv_sge;
	ctxt->rc_recv_wr.num_sge = 1;
	ctxt->rc_cqe.करोne = svc_rdma_wc_receive;
	ctxt->rc_recv_sge.addr = addr;
	ctxt->rc_recv_sge.length = rdma->sc_max_req_size;
	ctxt->rc_recv_sge.lkey = rdma->sc_pd->local_dma_lkey;
	ctxt->rc_recv_buf = buffer;
	ctxt->rc_temp = false;
	वापस ctxt;

fail2:
	kमुक्त(buffer);
fail1:
	kमुक्त(ctxt);
fail0:
	वापस शून्य;
पूर्ण

अटल व्योम svc_rdma_recv_ctxt_destroy(काष्ठा svcxprt_rdma *rdma,
				       काष्ठा svc_rdma_recv_ctxt *ctxt)
अणु
	ib_dma_unmap_single(rdma->sc_pd->device, ctxt->rc_recv_sge.addr,
			    ctxt->rc_recv_sge.length, DMA_FROM_DEVICE);
	kमुक्त(ctxt->rc_recv_buf);
	kमुक्त(ctxt);
पूर्ण

/**
 * svc_rdma_recv_ctxts_destroy - Release all recv_ctxt's क्रम an xprt
 * @rdma: svcxprt_rdma being torn करोwn
 *
 */
व्योम svc_rdma_recv_ctxts_destroy(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_recv_ctxt *ctxt;
	काष्ठा llist_node *node;

	जबतक ((node = llist_del_first(&rdma->sc_recv_ctxts))) अणु
		ctxt = llist_entry(node, काष्ठा svc_rdma_recv_ctxt, rc_node);
		svc_rdma_recv_ctxt_destroy(rdma, ctxt);
	पूर्ण
पूर्ण

/**
 * svc_rdma_recv_ctxt_get - Allocate a recv_ctxt
 * @rdma: controlling svcxprt_rdma
 *
 * Returns a recv_ctxt or (rarely) शून्य अगर none are available.
 */
काष्ठा svc_rdma_recv_ctxt *svc_rdma_recv_ctxt_get(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_recv_ctxt *ctxt;
	काष्ठा llist_node *node;

	node = llist_del_first(&rdma->sc_recv_ctxts);
	अगर (!node)
		जाओ out_empty;
	ctxt = llist_entry(node, काष्ठा svc_rdma_recv_ctxt, rc_node);

out:
	ctxt->rc_page_count = 0;
	वापस ctxt;

out_empty:
	ctxt = svc_rdma_recv_ctxt_alloc(rdma);
	अगर (!ctxt)
		वापस शून्य;
	जाओ out;
पूर्ण

/**
 * svc_rdma_recv_ctxt_put - Return recv_ctxt to मुक्त list
 * @rdma: controlling svcxprt_rdma
 * @ctxt: object to वापस to the मुक्त list
 *
 */
व्योम svc_rdma_recv_ctxt_put(काष्ठा svcxprt_rdma *rdma,
			    काष्ठा svc_rdma_recv_ctxt *ctxt)
अणु
	pcl_मुक्त(&ctxt->rc_call_pcl);
	pcl_मुक्त(&ctxt->rc_पढ़ो_pcl);
	pcl_मुक्त(&ctxt->rc_ग_लिखो_pcl);
	pcl_मुक्त(&ctxt->rc_reply_pcl);

	अगर (!ctxt->rc_temp)
		llist_add(&ctxt->rc_node, &rdma->sc_recv_ctxts);
	अन्यथा
		svc_rdma_recv_ctxt_destroy(rdma, ctxt);
पूर्ण

/**
 * svc_rdma_release_rqst - Release transport-specअगरic per-rqst resources
 * @rqstp: svc_rqst being released
 *
 * Ensure that the recv_ctxt is released whether or not a Reply
 * was sent. For example, the client could बंद the connection,
 * or svc_process could drop an RPC, beक्रमe the Reply is sent.
 */
व्योम svc_rdma_release_rqst(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_rdma_recv_ctxt *ctxt = rqstp->rq_xprt_ctxt;
	काष्ठा svc_xprt *xprt = rqstp->rq_xprt;
	काष्ठा svcxprt_rdma *rdma =
		container_of(xprt, काष्ठा svcxprt_rdma, sc_xprt);

	rqstp->rq_xprt_ctxt = शून्य;
	अगर (ctxt)
		svc_rdma_recv_ctxt_put(rdma, ctxt);
पूर्ण

अटल bool svc_rdma_refresh_recvs(काष्ठा svcxprt_rdma *rdma,
				   अचिन्हित पूर्णांक wanted, bool temp)
अणु
	स्थिर काष्ठा ib_recv_wr *bad_wr = शून्य;
	काष्ठा svc_rdma_recv_ctxt *ctxt;
	काष्ठा ib_recv_wr *recv_chain;
	पूर्णांक ret;

	अगर (test_bit(XPT_CLOSE, &rdma->sc_xprt.xpt_flags))
		वापस false;

	recv_chain = शून्य;
	जबतक (wanted--) अणु
		ctxt = svc_rdma_recv_ctxt_get(rdma);
		अगर (!ctxt)
			अवरोध;

		trace_svcrdma_post_recv(ctxt);
		ctxt->rc_temp = temp;
		ctxt->rc_recv_wr.next = recv_chain;
		recv_chain = &ctxt->rc_recv_wr;
		rdma->sc_pending_recvs++;
	पूर्ण
	अगर (!recv_chain)
		वापस false;

	ret = ib_post_recv(rdma->sc_qp, recv_chain, &bad_wr);
	अगर (ret)
		जाओ err_मुक्त;
	वापस true;

err_मुक्त:
	trace_svcrdma_rq_post_err(rdma, ret);
	जबतक (bad_wr) अणु
		ctxt = container_of(bad_wr, काष्ठा svc_rdma_recv_ctxt,
				    rc_recv_wr);
		bad_wr = bad_wr->next;
		svc_rdma_recv_ctxt_put(rdma, ctxt);
	पूर्ण
	/* Since we're destroying the xprt, no need to reset
	 * sc_pending_recvs. */
	वापस false;
पूर्ण

/**
 * svc_rdma_post_recvs - Post initial set of Recv WRs
 * @rdma: fresh svcxprt_rdma
 *
 * Returns true अगर successful, otherwise false.
 */
bool svc_rdma_post_recvs(काष्ठा svcxprt_rdma *rdma)
अणु
	वापस svc_rdma_refresh_recvs(rdma, rdma->sc_max_requests, true);
पूर्ण

/**
 * svc_rdma_wc_receive - Invoked by RDMA provider क्रम each polled Receive WC
 * @cq: Completion Queue context
 * @wc: Work Completion object
 *
 */
अटल व्योम svc_rdma_wc_receive(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा svcxprt_rdma *rdma = cq->cq_context;
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा svc_rdma_recv_ctxt *ctxt;

	rdma->sc_pending_recvs--;

	/* WARNING: Only wc->wr_cqe and wc->status are reliable */
	ctxt = container_of(cqe, काष्ठा svc_rdma_recv_ctxt, rc_cqe);

	trace_svcrdma_wc_receive(wc, &ctxt->rc_cid);
	अगर (wc->status != IB_WC_SUCCESS)
		जाओ flushed;

	/* If receive posting fails, the connection is about to be
	 * lost anyway. The server will not be able to send a reply
	 * क्रम this RPC, and the client will retransmit this RPC
	 * anyway when it reconnects.
	 *
	 * Thereक्रमe we drop the Receive, even अगर status was SUCCESS
	 * to reduce the likelihood of replayed requests once the
	 * client reconnects.
	 */
	अगर (rdma->sc_pending_recvs < rdma->sc_max_requests)
		अगर (!svc_rdma_refresh_recvs(rdma, rdma->sc_recv_batch, false))
			जाओ flushed;

	/* All wc fields are now known to be valid */
	ctxt->rc_byte_len = wc->byte_len;

	spin_lock(&rdma->sc_rq_dto_lock);
	list_add_tail(&ctxt->rc_list, &rdma->sc_rq_dto_q);
	/* Note the unlock pairs with the smp_rmb in svc_xprt_पढ़ोy: */
	set_bit(XPT_DATA, &rdma->sc_xprt.xpt_flags);
	spin_unlock(&rdma->sc_rq_dto_lock);
	अगर (!test_bit(RDMAXPRT_CONN_PENDING, &rdma->sc_flags))
		svc_xprt_enqueue(&rdma->sc_xprt);
	वापस;

flushed:
	svc_rdma_recv_ctxt_put(rdma, ctxt);
	svc_xprt_deferred_बंद(&rdma->sc_xprt);
पूर्ण

/**
 * svc_rdma_flush_recv_queues - Drain pending Receive work
 * @rdma: svcxprt_rdma being shut करोwn
 *
 */
व्योम svc_rdma_flush_recv_queues(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_recv_ctxt *ctxt;

	जबतक ((ctxt = svc_rdma_next_recv_ctxt(&rdma->sc_rq_dto_q))) अणु
		list_del(&ctxt->rc_list);
		svc_rdma_recv_ctxt_put(rdma, ctxt);
	पूर्ण
पूर्ण

अटल व्योम svc_rdma_build_arg_xdr(काष्ठा svc_rqst *rqstp,
				   काष्ठा svc_rdma_recv_ctxt *ctxt)
अणु
	काष्ठा xdr_buf *arg = &rqstp->rq_arg;

	arg->head[0].iov_base = ctxt->rc_recv_buf;
	arg->head[0].iov_len = ctxt->rc_byte_len;
	arg->tail[0].iov_base = शून्य;
	arg->tail[0].iov_len = 0;
	arg->page_len = 0;
	arg->page_base = 0;
	arg->buflen = ctxt->rc_byte_len;
	arg->len = ctxt->rc_byte_len;
पूर्ण

/**
 * xdr_count_पढ़ो_segments - Count number of Read segments in Read list
 * @rctxt: Ingress receive context
 * @p: Start of an un-decoded Read list
 *
 * Beक्रमe allocating anything, ensure the ingress Read list is safe
 * to use.
 *
 * The segment count is limited to how many segments can fit in the
 * transport header without overflowing the buffer. That's about 40
 * Read segments क्रम a 1KB अंतरभूत threshold.
 *
 * Return values:
 *   %true: Read list is valid. @rctxt's xdr_stream is updated to poपूर्णांक
 *	    to the first byte past the Read list. rc_पढ़ो_pcl and
 *	    rc_call_pcl cl_count fields are set to the number of
 *	    Read segments in the list.
 *  %false: Read list is corrupt. @rctxt's xdr_stream is left in an
 *	    unknown state.
 */
अटल bool xdr_count_पढ़ो_segments(काष्ठा svc_rdma_recv_ctxt *rctxt, __be32 *p)
अणु
	rctxt->rc_call_pcl.cl_count = 0;
	rctxt->rc_पढ़ो_pcl.cl_count = 0;
	जबतक (xdr_item_is_present(p)) अणु
		u32 position, handle, length;
		u64 offset;

		p = xdr_अंतरभूत_decode(&rctxt->rc_stream,
				      rpcrdma_पढ़ोseg_maxsz * माप(*p));
		अगर (!p)
			वापस false;

		xdr_decode_पढ़ो_segment(p, &position, &handle,
					    &length, &offset);
		अगर (position) अणु
			अगर (position & 3)
				वापस false;
			++rctxt->rc_पढ़ो_pcl.cl_count;
		पूर्ण अन्यथा अणु
			++rctxt->rc_call_pcl.cl_count;
		पूर्ण

		p = xdr_अंतरभूत_decode(&rctxt->rc_stream, माप(*p));
		अगर (!p)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Sanity check the Read list.
 *
 * Sanity checks:
 * - Read list करोes not overflow Receive buffer.
 * - Chunk size limited by largest NFS data payload.
 *
 * Return values:
 *   %true: Read list is valid. @rctxt's xdr_stream is updated
 *	    to poपूर्णांक to the first byte past the Read list.
 *  %false: Read list is corrupt. @rctxt's xdr_stream is left
 *	    in an unknown state.
 */
अटल bool xdr_check_पढ़ो_list(काष्ठा svc_rdma_recv_ctxt *rctxt)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(&rctxt->rc_stream, माप(*p));
	अगर (!p)
		वापस false;
	अगर (!xdr_count_पढ़ो_segments(rctxt, p))
		वापस false;
	अगर (!pcl_alloc_call(rctxt, p))
		वापस false;
	वापस pcl_alloc_पढ़ो(rctxt, p);
पूर्ण

अटल bool xdr_check_ग_लिखो_chunk(काष्ठा svc_rdma_recv_ctxt *rctxt)
अणु
	u32 segcount;
	__be32 *p;

	अगर (xdr_stream_decode_u32(&rctxt->rc_stream, &segcount))
		वापस false;

	/* A bogus segcount causes this buffer overflow check to fail. */
	p = xdr_अंतरभूत_decode(&rctxt->rc_stream,
			      segcount * rpcrdma_segment_maxsz * माप(*p));
	वापस p != शून्य;
पूर्ण

/**
 * xdr_count_ग_लिखो_chunks - Count number of Write chunks in Write list
 * @rctxt: Received header and decoding state
 * @p: start of an un-decoded Write list
 *
 * Beक्रमe allocating anything, ensure the ingress Write list is
 * safe to use.
 *
 * Return values:
 *       %true: Write list is valid. @rctxt's xdr_stream is updated
 *		to poपूर्णांक to the first byte past the Write list, and
 *		the number of Write chunks is in rc_ग_लिखो_pcl.cl_count.
 *      %false: Write list is corrupt. @rctxt's xdr_stream is left
 *		in an indeterminate state.
 */
अटल bool xdr_count_ग_लिखो_chunks(काष्ठा svc_rdma_recv_ctxt *rctxt, __be32 *p)
अणु
	rctxt->rc_ग_लिखो_pcl.cl_count = 0;
	जबतक (xdr_item_is_present(p)) अणु
		अगर (!xdr_check_ग_लिखो_chunk(rctxt))
			वापस false;
		++rctxt->rc_ग_लिखो_pcl.cl_count;
		p = xdr_अंतरभूत_decode(&rctxt->rc_stream, माप(*p));
		अगर (!p)
			वापस false;
	पूर्ण
	वापस true;
पूर्ण

/* Sanity check the Write list.
 *
 * Implementation limits:
 * - This implementation currently supports only one Write chunk.
 *
 * Sanity checks:
 * - Write list करोes not overflow Receive buffer.
 * - Chunk size limited by largest NFS data payload.
 *
 * Return values:
 *       %true: Write list is valid. @rctxt's xdr_stream is updated
 *		to poपूर्णांक to the first byte past the Write list.
 *      %false: Write list is corrupt. @rctxt's xdr_stream is left
 *		in an unknown state.
 */
अटल bool xdr_check_ग_लिखो_list(काष्ठा svc_rdma_recv_ctxt *rctxt)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(&rctxt->rc_stream, माप(*p));
	अगर (!p)
		वापस false;
	अगर (!xdr_count_ग_लिखो_chunks(rctxt, p))
		वापस false;
	अगर (!pcl_alloc_ग_लिखो(rctxt, &rctxt->rc_ग_लिखो_pcl, p))
		वापस false;

	rctxt->rc_cur_result_payload = pcl_first_chunk(&rctxt->rc_ग_लिखो_pcl);
	वापस true;
पूर्ण

/* Sanity check the Reply chunk.
 *
 * Sanity checks:
 * - Reply chunk करोes not overflow Receive buffer.
 * - Chunk size limited by largest NFS data payload.
 *
 * Return values:
 *       %true: Reply chunk is valid. @rctxt's xdr_stream is updated
 *		to poपूर्णांक to the first byte past the Reply chunk.
 *      %false: Reply chunk is corrupt. @rctxt's xdr_stream is left
 *		in an unknown state.
 */
अटल bool xdr_check_reply_chunk(काष्ठा svc_rdma_recv_ctxt *rctxt)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(&rctxt->rc_stream, माप(*p));
	अगर (!p)
		वापस false;

	अगर (!xdr_item_is_present(p))
		वापस true;
	अगर (!xdr_check_ग_लिखो_chunk(rctxt))
		वापस false;

	rctxt->rc_reply_pcl.cl_count = 1;
	वापस pcl_alloc_ग_लिखो(rctxt, &rctxt->rc_reply_pcl, p);
पूर्ण

/* RPC-over-RDMA Version One निजी extension: Remote Invalidation.
 * Responder's choice: requester संकेतs it can handle Send With
 * Invalidate, and responder chooses one R_key to invalidate.
 *
 * If there is exactly one distinct R_key in the received transport
 * header, set rc_inv_rkey to that R_key. Otherwise, set it to zero.
 */
अटल व्योम svc_rdma_get_inv_rkey(काष्ठा svcxprt_rdma *rdma,
				  काष्ठा svc_rdma_recv_ctxt *ctxt)
अणु
	काष्ठा svc_rdma_segment *segment;
	काष्ठा svc_rdma_chunk *chunk;
	u32 inv_rkey;

	ctxt->rc_inv_rkey = 0;

	अगर (!rdma->sc_snd_w_inv)
		वापस;

	inv_rkey = 0;
	pcl_क्रम_each_chunk(chunk, &ctxt->rc_call_pcl) अणु
		pcl_क्रम_each_segment(segment, chunk) अणु
			अगर (inv_rkey == 0)
				inv_rkey = segment->rs_handle;
			अन्यथा अगर (inv_rkey != segment->rs_handle)
				वापस;
		पूर्ण
	पूर्ण
	pcl_क्रम_each_chunk(chunk, &ctxt->rc_पढ़ो_pcl) अणु
		pcl_क्रम_each_segment(segment, chunk) अणु
			अगर (inv_rkey == 0)
				inv_rkey = segment->rs_handle;
			अन्यथा अगर (inv_rkey != segment->rs_handle)
				वापस;
		पूर्ण
	पूर्ण
	pcl_क्रम_each_chunk(chunk, &ctxt->rc_ग_लिखो_pcl) अणु
		pcl_क्रम_each_segment(segment, chunk) अणु
			अगर (inv_rkey == 0)
				inv_rkey = segment->rs_handle;
			अन्यथा अगर (inv_rkey != segment->rs_handle)
				वापस;
		पूर्ण
	पूर्ण
	pcl_क्रम_each_chunk(chunk, &ctxt->rc_reply_pcl) अणु
		pcl_क्रम_each_segment(segment, chunk) अणु
			अगर (inv_rkey == 0)
				inv_rkey = segment->rs_handle;
			अन्यथा अगर (inv_rkey != segment->rs_handle)
				वापस;
		पूर्ण
	पूर्ण
	ctxt->rc_inv_rkey = inv_rkey;
पूर्ण

/**
 * svc_rdma_xdr_decode_req - Decode the transport header
 * @rq_arg: xdr_buf containing ingress RPC/RDMA message
 * @rctxt: state of decoding
 *
 * On entry, xdr->head[0].iov_base poपूर्णांकs to first byte of the
 * RPC-over-RDMA transport header.
 *
 * On successful निकास, head[0] poपूर्णांकs to first byte past the
 * RPC-over-RDMA header. For RDMA_MSG, this is the RPC message.
 *
 * The length of the RPC-over-RDMA header is वापसed.
 *
 * Assumptions:
 * - The transport header is entirely contained in the head iovec.
 */
अटल पूर्णांक svc_rdma_xdr_decode_req(काष्ठा xdr_buf *rq_arg,
				   काष्ठा svc_rdma_recv_ctxt *rctxt)
अणु
	__be32 *p, *rdma_argp;
	अचिन्हित पूर्णांक hdr_len;

	rdma_argp = rq_arg->head[0].iov_base;
	xdr_init_decode(&rctxt->rc_stream, rq_arg, rdma_argp, शून्य);

	p = xdr_अंतरभूत_decode(&rctxt->rc_stream,
			      rpcrdma_fixed_maxsz * माप(*p));
	अगर (unlikely(!p))
		जाओ out_लघु;
	p++;
	अगर (*p != rpcrdma_version)
		जाओ out_version;
	p += 2;
	rctxt->rc_msgtype = *p;
	चयन (rctxt->rc_msgtype) अणु
	हाल rdma_msg:
		अवरोध;
	हाल rdma_nomsg:
		अवरोध;
	हाल rdma_करोne:
		जाओ out_drop;
	हाल rdma_error:
		जाओ out_drop;
	शेष:
		जाओ out_proc;
	पूर्ण

	अगर (!xdr_check_पढ़ो_list(rctxt))
		जाओ out_inval;
	अगर (!xdr_check_ग_लिखो_list(rctxt))
		जाओ out_inval;
	अगर (!xdr_check_reply_chunk(rctxt))
		जाओ out_inval;

	rq_arg->head[0].iov_base = rctxt->rc_stream.p;
	hdr_len = xdr_stream_pos(&rctxt->rc_stream);
	rq_arg->head[0].iov_len -= hdr_len;
	rq_arg->len -= hdr_len;
	trace_svcrdma_decode_rqst(rctxt, rdma_argp, hdr_len);
	वापस hdr_len;

out_लघु:
	trace_svcrdma_decode_लघु_err(rctxt, rq_arg->len);
	वापस -EINVAL;

out_version:
	trace_svcrdma_decode_badvers_err(rctxt, rdma_argp);
	वापस -EPROTONOSUPPORT;

out_drop:
	trace_svcrdma_decode_drop_err(rctxt, rdma_argp);
	वापस 0;

out_proc:
	trace_svcrdma_decode_badproc_err(rctxt, rdma_argp);
	वापस -EINVAL;

out_inval:
	trace_svcrdma_decode_parse_err(rctxt, rdma_argp);
	वापस -EINVAL;
पूर्ण

अटल व्योम svc_rdma_send_error(काष्ठा svcxprt_rdma *rdma,
				काष्ठा svc_rdma_recv_ctxt *rctxt,
				पूर्णांक status)
अणु
	काष्ठा svc_rdma_send_ctxt *sctxt;

	sctxt = svc_rdma_send_ctxt_get(rdma);
	अगर (!sctxt)
		वापस;
	svc_rdma_send_error_msg(rdma, sctxt, rctxt, status);
पूर्ण

/* By convention, backchannel calls arrive via rdma_msg type
 * messages, and never populate the chunk lists. This makes
 * the RPC/RDMA header small and fixed in size, so it is
 * straightक्रमward to check the RPC header's direction field.
 */
अटल bool svc_rdma_is_reverse_direction_reply(काष्ठा svc_xprt *xprt,
						काष्ठा svc_rdma_recv_ctxt *rctxt)
अणु
	__be32 *p = rctxt->rc_recv_buf;

	अगर (!xprt->xpt_bc_xprt)
		वापस false;

	अगर (rctxt->rc_msgtype != rdma_msg)
		वापस false;

	अगर (!pcl_is_empty(&rctxt->rc_call_pcl))
		वापस false;
	अगर (!pcl_is_empty(&rctxt->rc_पढ़ो_pcl))
		वापस false;
	अगर (!pcl_is_empty(&rctxt->rc_ग_लिखो_pcl))
		वापस false;
	अगर (!pcl_is_empty(&rctxt->rc_reply_pcl))
		वापस false;

	/* RPC call direction */
	अगर (*(p + 8) == cpu_to_be32(RPC_CALL))
		वापस false;

	वापस true;
पूर्ण

/**
 * svc_rdma_recvfrom - Receive an RPC call
 * @rqstp: request काष्ठाure पूर्णांकo which to receive an RPC Call
 *
 * Returns:
 *	The positive number of bytes in the RPC Call message,
 *	%0 अगर there were no Calls पढ़ोy to वापस,
 *	%-EINVAL अगर the Read chunk data is too large,
 *	%-ENOMEM अगर rdma_rw context pool was exhausted,
 *	%-ENOTCONN अगर posting failed (connection is lost),
 *	%-EIO अगर rdma_rw initialization failed (DMA mapping, etc).
 *
 * Called in a loop when XPT_DATA is set. XPT_DATA is cleared only
 * when there are no reमुख्यing ctxt's to process.
 *
 * The next ctxt is हटाओd from the "receive" lists.
 *
 * - If the ctxt completes a Read, then finish assembling the Call
 *   message and वापस the number of bytes in the message.
 *
 * - If the ctxt completes a Receive, then स्थिरruct the Call
 *   message from the contents of the Receive buffer.
 *
 *   - If there are no Read chunks in this message, then finish
 *     assembling the Call message and वापस the number of bytes
 *     in the message.
 *
 *   - If there are Read chunks in this message, post Read WRs to
 *     pull that payload and वापस 0.
 */
पूर्णांक svc_rdma_recvfrom(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_xprt *xprt = rqstp->rq_xprt;
	काष्ठा svcxprt_rdma *rdma_xprt =
		container_of(xprt, काष्ठा svcxprt_rdma, sc_xprt);
	काष्ठा svc_rdma_recv_ctxt *ctxt;
	पूर्णांक ret;

	rqstp->rq_xprt_ctxt = शून्य;

	ctxt = शून्य;
	spin_lock(&rdma_xprt->sc_rq_dto_lock);
	ctxt = svc_rdma_next_recv_ctxt(&rdma_xprt->sc_rq_dto_q);
	अगर (ctxt)
		list_del(&ctxt->rc_list);
	अन्यथा
		/* No new incoming requests, terminate the loop */
		clear_bit(XPT_DATA, &xprt->xpt_flags);
	spin_unlock(&rdma_xprt->sc_rq_dto_lock);

	/* Unblock the transport क्रम the next receive */
	svc_xprt_received(xprt);
	अगर (!ctxt)
		वापस 0;

	percpu_counter_inc(&svcrdma_stat_recv);
	ib_dma_sync_single_क्रम_cpu(rdma_xprt->sc_pd->device,
				   ctxt->rc_recv_sge.addr, ctxt->rc_byte_len,
				   DMA_FROM_DEVICE);
	svc_rdma_build_arg_xdr(rqstp, ctxt);

	/* Prevent svc_xprt_release from releasing pages in rq_pages
	 * अगर we वापस 0 or an error.
	 */
	rqstp->rq_respages = rqstp->rq_pages;
	rqstp->rq_next_page = rqstp->rq_respages;

	ret = svc_rdma_xdr_decode_req(&rqstp->rq_arg, ctxt);
	अगर (ret < 0)
		जाओ out_err;
	अगर (ret == 0)
		जाओ out_drop;
	rqstp->rq_xprt_hlen = ret;

	अगर (svc_rdma_is_reverse_direction_reply(xprt, ctxt))
		जाओ out_backchannel;

	svc_rdma_get_inv_rkey(rdma_xprt, ctxt);

	अगर (!pcl_is_empty(&ctxt->rc_पढ़ो_pcl) ||
	    !pcl_is_empty(&ctxt->rc_call_pcl)) अणु
		ret = svc_rdma_process_पढ़ो_list(rdma_xprt, rqstp, ctxt);
		अगर (ret < 0)
			जाओ out_पढ़ोfail;
	पूर्ण

	rqstp->rq_xprt_ctxt = ctxt;
	rqstp->rq_prot = IPPROTO_MAX;
	svc_xprt_copy_addrs(rqstp, xprt);
	वापस rqstp->rq_arg.len;

out_err:
	svc_rdma_send_error(rdma_xprt, ctxt, ret);
	svc_rdma_recv_ctxt_put(rdma_xprt, ctxt);
	वापस 0;

out_पढ़ोfail:
	अगर (ret == -EINVAL)
		svc_rdma_send_error(rdma_xprt, ctxt, ret);
	svc_rdma_recv_ctxt_put(rdma_xprt, ctxt);
	वापस ret;

out_backchannel:
	svc_rdma_handle_bc_reply(rqstp, ctxt);
out_drop:
	svc_rdma_recv_ctxt_put(rdma_xprt, ctxt);
	वापस 0;
पूर्ण
