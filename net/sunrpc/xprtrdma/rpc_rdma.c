<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0 OR BSD-3-Clause
/*
 * Copyright (c) 2014-2020, Oracle and/or its affiliates.
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
 * rpc_rdma.c
 *
 * This file contains the guts of the RPC RDMA protocol, and
 * करोes marshaling/unmarshaling, etc. It is also where पूर्णांकerfacing
 * to the Linux RPC framework lives.
 */

#समावेश <linux/highस्मृति.स>

#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_TRANS
#पूर्ण_अगर

/* Returns size of largest RPC-over-RDMA header in a Call message
 *
 * The largest Call header contains a full-size Read list and a
 * minimal Reply chunk.
 */
अटल अचिन्हित पूर्णांक rpcrdma_max_call_header_size(अचिन्हित पूर्णांक maxsegs)
अणु
	अचिन्हित पूर्णांक size;

	/* Fixed header fields and list discriminators */
	size = RPCRDMA_HDRLEN_MIN;

	/* Maximum Read list size */
	size += maxsegs * rpcrdma_पढ़ोchunk_maxsz * माप(__be32);

	/* Minimal Read chunk size */
	size += माप(__be32);	/* segment count */
	size += rpcrdma_segment_maxsz * माप(__be32);
	size += माप(__be32);	/* list discriminator */

	वापस size;
पूर्ण

/* Returns size of largest RPC-over-RDMA header in a Reply message
 *
 * There is only one Write list or one Reply chunk per Reply
 * message.  The larger list is the Write list.
 */
अटल अचिन्हित पूर्णांक rpcrdma_max_reply_header_size(अचिन्हित पूर्णांक maxsegs)
अणु
	अचिन्हित पूर्णांक size;

	/* Fixed header fields and list discriminators */
	size = RPCRDMA_HDRLEN_MIN;

	/* Maximum Write list size */
	size += माप(__be32);		/* segment count */
	size += maxsegs * rpcrdma_segment_maxsz * माप(__be32);
	size += माप(__be32);	/* list discriminator */

	वापस size;
पूर्ण

/**
 * rpcrdma_set_max_header_sizes - Initialize अंतरभूत payload sizes
 * @ep: endpoपूर्णांक to initialize
 *
 * The max_अंतरभूत fields contain the maximum size of an RPC message
 * so the marshaling code करोesn't have to repeat this calculation
 * क्रम every RPC.
 */
व्योम rpcrdma_set_max_header_sizes(काष्ठा rpcrdma_ep *ep)
अणु
	अचिन्हित पूर्णांक maxsegs = ep->re_max_rdma_segs;

	ep->re_max_अंतरभूत_send =
		ep->re_अंतरभूत_send - rpcrdma_max_call_header_size(maxsegs);
	ep->re_max_अंतरभूत_recv =
		ep->re_अंतरभूत_recv - rpcrdma_max_reply_header_size(maxsegs);
पूर्ण

/* The client can send a request अंतरभूत as दीर्घ as the RPCRDMA header
 * plus the RPC call fit under the transport's अंतरभूत limit. If the
 * combined call message size exceeds that limit, the client must use
 * a Read chunk क्रम this operation.
 *
 * A Read chunk is also required अगर sending the RPC call अंतरभूत would
 * exceed this device's max_sge limit.
 */
अटल bool rpcrdma_args_अंतरभूत(काष्ठा rpcrdma_xprt *r_xprt,
				काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा xdr_buf *xdr = &rqst->rq_snd_buf;
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	अचिन्हित पूर्णांक count, reमुख्यing, offset;

	अगर (xdr->len > ep->re_max_अंतरभूत_send)
		वापस false;

	अगर (xdr->page_len) अणु
		reमुख्यing = xdr->page_len;
		offset = offset_in_page(xdr->page_base);
		count = RPCRDMA_MIN_SEND_SGES;
		जबतक (reमुख्यing) अणु
			reमुख्यing -= min_t(अचिन्हित पूर्णांक,
					   PAGE_SIZE - offset, reमुख्यing);
			offset = 0;
			अगर (++count > ep->re_attr.cap.max_send_sge)
				वापस false;
		पूर्ण
	पूर्ण

	वापस true;
पूर्ण

/* The client can't know how large the actual reply will be. Thus it
 * plans क्रम the largest possible reply क्रम that particular ULP
 * operation. If the maximum combined reply message size exceeds that
 * limit, the client must provide a ग_लिखो list or a reply chunk क्रम
 * this request.
 */
अटल bool rpcrdma_results_अंतरभूत(काष्ठा rpcrdma_xprt *r_xprt,
				   काष्ठा rpc_rqst *rqst)
अणु
	वापस rqst->rq_rcv_buf.buflen <= r_xprt->rx_ep->re_max_अंतरभूत_recv;
पूर्ण

/* The client is required to provide a Reply chunk अगर the maximum
 * size of the non-payload part of the RPC Reply is larger than
 * the अंतरभूत threshold.
 */
अटल bool
rpcrdma_nonpayload_अंतरभूत(स्थिर काष्ठा rpcrdma_xprt *r_xprt,
			  स्थिर काष्ठा rpc_rqst *rqst)
अणु
	स्थिर काष्ठा xdr_buf *buf = &rqst->rq_rcv_buf;

	वापस (buf->head[0].iov_len + buf->tail[0].iov_len) <
		r_xprt->rx_ep->re_max_अंतरभूत_recv;
पूर्ण

/* ACL likes to be lazy in allocating pages. For TCP, these
 * pages can be allocated during receive processing. Not true
 * क्रम RDMA, which must always provision receive buffers
 * up front.
 */
अटल noअंतरभूत पूर्णांक
rpcrdma_alloc_sparse_pages(काष्ठा xdr_buf *buf)
अणु
	काष्ठा page **ppages;
	पूर्णांक len;

	len = buf->page_len;
	ppages = buf->pages + (buf->page_base >> PAGE_SHIFT);
	जबतक (len > 0) अणु
		अगर (!*ppages)
			*ppages = alloc_page(GFP_NOWAIT | __GFP_NOWARN);
		अगर (!*ppages)
			वापस -ENOBUFS;
		ppages++;
		len -= PAGE_SIZE;
	पूर्ण

	वापस 0;
पूर्ण

/* Convert @vec to a single SGL element.
 *
 * Returns poपूर्णांकer to next available SGE, and bumps the total number
 * of SGEs consumed.
 */
अटल काष्ठा rpcrdma_mr_seg *
rpcrdma_convert_kvec(काष्ठा kvec *vec, काष्ठा rpcrdma_mr_seg *seg,
		     अचिन्हित पूर्णांक *n)
अणु
	seg->mr_page = virt_to_page(vec->iov_base);
	seg->mr_offset = offset_in_page(vec->iov_base);
	seg->mr_len = vec->iov_len;
	++seg;
	++(*n);
	वापस seg;
पूर्ण

/* Convert @xdrbuf पूर्णांकo SGEs no larger than a page each. As they
 * are रेजिस्टरed, these SGEs are then coalesced पूर्णांकo RDMA segments
 * when the selected memreg mode supports it.
 *
 * Returns positive number of SGEs consumed, or a negative त्रुटि_सं.
 */

अटल पूर्णांक
rpcrdma_convert_iovs(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा xdr_buf *xdrbuf,
		     अचिन्हित पूर्णांक pos, क्रमागत rpcrdma_chunktype type,
		     काष्ठा rpcrdma_mr_seg *seg)
अणु
	अचिन्हित दीर्घ page_base;
	अचिन्हित पूर्णांक len, n;
	काष्ठा page **ppages;

	n = 0;
	अगर (pos == 0)
		seg = rpcrdma_convert_kvec(&xdrbuf->head[0], seg, &n);

	len = xdrbuf->page_len;
	ppages = xdrbuf->pages + (xdrbuf->page_base >> PAGE_SHIFT);
	page_base = offset_in_page(xdrbuf->page_base);
	जबतक (len) अणु
		seg->mr_page = *ppages;
		seg->mr_offset = page_base;
		seg->mr_len = min_t(u32, PAGE_SIZE - page_base, len);
		len -= seg->mr_len;
		++ppages;
		++seg;
		++n;
		page_base = 0;
	पूर्ण

	अगर (type == rpcrdma_पढ़ोch)
		जाओ out;

	/* When encoding a Write chunk, some servers need to see an
	 * extra segment क्रम non-XDR-aligned Write chunks. The upper
	 * layer provides space in the tail iovec that may be used
	 * क्रम this purpose.
	 */
	अगर (type == rpcrdma_ग_लिखोch && r_xprt->rx_ep->re_implicit_roundup)
		जाओ out;

	अगर (xdrbuf->tail[0].iov_len)
		rpcrdma_convert_kvec(&xdrbuf->tail[0], seg, &n);

out:
	अगर (unlikely(n > RPCRDMA_MAX_SEGS))
		वापस -EIO;
	वापस n;
पूर्ण

अटल पूर्णांक
encode_rdma_segment(काष्ठा xdr_stream *xdr, काष्ठा rpcrdma_mr *mr)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 4 * माप(*p));
	अगर (unlikely(!p))
		वापस -EMSGSIZE;

	xdr_encode_rdma_segment(p, mr->mr_handle, mr->mr_length, mr->mr_offset);
	वापस 0;
पूर्ण

अटल पूर्णांक
encode_पढ़ो_segment(काष्ठा xdr_stream *xdr, काष्ठा rpcrdma_mr *mr,
		    u32 position)
अणु
	__be32 *p;

	p = xdr_reserve_space(xdr, 6 * माप(*p));
	अगर (unlikely(!p))
		वापस -EMSGSIZE;

	*p++ = xdr_one;			/* Item present */
	xdr_encode_पढ़ो_segment(p, position, mr->mr_handle, mr->mr_length,
				mr->mr_offset);
	वापस 0;
पूर्ण

अटल काष्ठा rpcrdma_mr_seg *rpcrdma_mr_prepare(काष्ठा rpcrdma_xprt *r_xprt,
						 काष्ठा rpcrdma_req *req,
						 काष्ठा rpcrdma_mr_seg *seg,
						 पूर्णांक nsegs, bool writing,
						 काष्ठा rpcrdma_mr **mr)
अणु
	*mr = rpcrdma_mr_pop(&req->rl_मुक्त_mrs);
	अगर (!*mr) अणु
		*mr = rpcrdma_mr_get(r_xprt);
		अगर (!*mr)
			जाओ out_geपंचांगr_err;
		(*mr)->mr_req = req;
	पूर्ण

	rpcrdma_mr_push(*mr, &req->rl_रेजिस्टरed);
	वापस frwr_map(r_xprt, seg, nsegs, writing, req->rl_slot.rq_xid, *mr);

out_geपंचांगr_err:
	trace_xprtrdma_nomrs_err(r_xprt, req);
	xprt_रुको_क्रम_buffer_space(&r_xprt->rx_xprt);
	rpcrdma_mrs_refresh(r_xprt);
	वापस ERR_PTR(-EAGAIN);
पूर्ण

/* Register and XDR encode the Read list. Supports encoding a list of पढ़ो
 * segments that beदीर्घ to a single पढ़ो chunk.
 *
 * Encoding key क्रम single-list chunks (HLOO = Handle32 Length32 Offset64):
 *
 *  Read chunklist (a linked list):
 *   N elements, position P (same P क्रम all chunks of same arg!):
 *    1 - PHLOO - 1 - PHLOO - ... - 1 - PHLOO - 0
 *
 * Returns zero on success, or a negative त्रुटि_सं अगर a failure occurred.
 * @xdr is advanced to the next position in the stream.
 *
 * Only a single @pos value is currently supported.
 */
अटल पूर्णांक rpcrdma_encode_पढ़ो_list(काष्ठा rpcrdma_xprt *r_xprt,
				    काष्ठा rpcrdma_req *req,
				    काष्ठा rpc_rqst *rqst,
				    क्रमागत rpcrdma_chunktype rtype)
अणु
	काष्ठा xdr_stream *xdr = &req->rl_stream;
	काष्ठा rpcrdma_mr_seg *seg;
	काष्ठा rpcrdma_mr *mr;
	अचिन्हित पूर्णांक pos;
	पूर्णांक nsegs;

	अगर (rtype == rpcrdma_noch_pullup || rtype == rpcrdma_noch_mapped)
		जाओ करोne;

	pos = rqst->rq_snd_buf.head[0].iov_len;
	अगर (rtype == rpcrdma_aपढ़ोch)
		pos = 0;
	seg = req->rl_segments;
	nsegs = rpcrdma_convert_iovs(r_xprt, &rqst->rq_snd_buf, pos,
				     rtype, seg);
	अगर (nsegs < 0)
		वापस nsegs;

	करो अणु
		seg = rpcrdma_mr_prepare(r_xprt, req, seg, nsegs, false, &mr);
		अगर (IS_ERR(seg))
			वापस PTR_ERR(seg);

		अगर (encode_पढ़ो_segment(xdr, mr, pos) < 0)
			वापस -EMSGSIZE;

		trace_xprtrdma_chunk_पढ़ो(rqst->rq_task, pos, mr, nsegs);
		r_xprt->rx_stats.पढ़ो_chunk_count++;
		nsegs -= mr->mr_nents;
	पूर्ण जबतक (nsegs);

करोne:
	अगर (xdr_stream_encode_item_असलent(xdr) < 0)
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

/* Register and XDR encode the Write list. Supports encoding a list
 * containing one array of plain segments that beदीर्घ to a single
 * ग_लिखो chunk.
 *
 * Encoding key क्रम single-list chunks (HLOO = Handle32 Length32 Offset64):
 *
 *  Write chunklist (a list of (one) counted array):
 *   N elements:
 *    1 - N - HLOO - HLOO - ... - HLOO - 0
 *
 * Returns zero on success, or a negative त्रुटि_सं अगर a failure occurred.
 * @xdr is advanced to the next position in the stream.
 *
 * Only a single Write chunk is currently supported.
 */
अटल पूर्णांक rpcrdma_encode_ग_लिखो_list(काष्ठा rpcrdma_xprt *r_xprt,
				     काष्ठा rpcrdma_req *req,
				     काष्ठा rpc_rqst *rqst,
				     क्रमागत rpcrdma_chunktype wtype)
अणु
	काष्ठा xdr_stream *xdr = &req->rl_stream;
	काष्ठा rpcrdma_mr_seg *seg;
	काष्ठा rpcrdma_mr *mr;
	पूर्णांक nsegs, nchunks;
	__be32 *segcount;

	अगर (wtype != rpcrdma_ग_लिखोch)
		जाओ करोne;

	seg = req->rl_segments;
	nsegs = rpcrdma_convert_iovs(r_xprt, &rqst->rq_rcv_buf,
				     rqst->rq_rcv_buf.head[0].iov_len,
				     wtype, seg);
	अगर (nsegs < 0)
		वापस nsegs;

	अगर (xdr_stream_encode_item_present(xdr) < 0)
		वापस -EMSGSIZE;
	segcount = xdr_reserve_space(xdr, माप(*segcount));
	अगर (unlikely(!segcount))
		वापस -EMSGSIZE;
	/* Actual value encoded below */

	nchunks = 0;
	करो अणु
		seg = rpcrdma_mr_prepare(r_xprt, req, seg, nsegs, true, &mr);
		अगर (IS_ERR(seg))
			वापस PTR_ERR(seg);

		अगर (encode_rdma_segment(xdr, mr) < 0)
			वापस -EMSGSIZE;

		trace_xprtrdma_chunk_ग_लिखो(rqst->rq_task, mr, nsegs);
		r_xprt->rx_stats.ग_लिखो_chunk_count++;
		r_xprt->rx_stats.total_rdma_request += mr->mr_length;
		nchunks++;
		nsegs -= mr->mr_nents;
	पूर्ण जबतक (nsegs);

	/* Update count of segments in this Write chunk */
	*segcount = cpu_to_be32(nchunks);

करोne:
	अगर (xdr_stream_encode_item_असलent(xdr) < 0)
		वापस -EMSGSIZE;
	वापस 0;
पूर्ण

/* Register and XDR encode the Reply chunk. Supports encoding an array
 * of plain segments that beदीर्घ to a single ग_लिखो (reply) chunk.
 *
 * Encoding key क्रम single-list chunks (HLOO = Handle32 Length32 Offset64):
 *
 *  Reply chunk (a counted array):
 *   N elements:
 *    1 - N - HLOO - HLOO - ... - HLOO
 *
 * Returns zero on success, or a negative त्रुटि_सं अगर a failure occurred.
 * @xdr is advanced to the next position in the stream.
 */
अटल पूर्णांक rpcrdma_encode_reply_chunk(काष्ठा rpcrdma_xprt *r_xprt,
				      काष्ठा rpcrdma_req *req,
				      काष्ठा rpc_rqst *rqst,
				      क्रमागत rpcrdma_chunktype wtype)
अणु
	काष्ठा xdr_stream *xdr = &req->rl_stream;
	काष्ठा rpcrdma_mr_seg *seg;
	काष्ठा rpcrdma_mr *mr;
	पूर्णांक nsegs, nchunks;
	__be32 *segcount;

	अगर (wtype != rpcrdma_replych) अणु
		अगर (xdr_stream_encode_item_असलent(xdr) < 0)
			वापस -EMSGSIZE;
		वापस 0;
	पूर्ण

	seg = req->rl_segments;
	nsegs = rpcrdma_convert_iovs(r_xprt, &rqst->rq_rcv_buf, 0, wtype, seg);
	अगर (nsegs < 0)
		वापस nsegs;

	अगर (xdr_stream_encode_item_present(xdr) < 0)
		वापस -EMSGSIZE;
	segcount = xdr_reserve_space(xdr, माप(*segcount));
	अगर (unlikely(!segcount))
		वापस -EMSGSIZE;
	/* Actual value encoded below */

	nchunks = 0;
	करो अणु
		seg = rpcrdma_mr_prepare(r_xprt, req, seg, nsegs, true, &mr);
		अगर (IS_ERR(seg))
			वापस PTR_ERR(seg);

		अगर (encode_rdma_segment(xdr, mr) < 0)
			वापस -EMSGSIZE;

		trace_xprtrdma_chunk_reply(rqst->rq_task, mr, nsegs);
		r_xprt->rx_stats.reply_chunk_count++;
		r_xprt->rx_stats.total_rdma_request += mr->mr_length;
		nchunks++;
		nsegs -= mr->mr_nents;
	पूर्ण जबतक (nsegs);

	/* Update count of segments in the Reply chunk */
	*segcount = cpu_to_be32(nchunks);

	वापस 0;
पूर्ण

अटल व्योम rpcrdma_sendctx_करोne(काष्ठा kref *kref)
अणु
	काष्ठा rpcrdma_req *req =
		container_of(kref, काष्ठा rpcrdma_req, rl_kref);
	काष्ठा rpcrdma_rep *rep = req->rl_reply;

	rpcrdma_complete_rqst(rep);
	rep->rr_rxprt->rx_stats.reply_रुकोs_क्रम_send++;
पूर्ण

/**
 * rpcrdma_sendctx_unmap - DMA-unmap Send buffer
 * @sc: sendctx containing SGEs to unmap
 *
 */
व्योम rpcrdma_sendctx_unmap(काष्ठा rpcrdma_sendctx *sc)
अणु
	काष्ठा rpcrdma_regbuf *rb = sc->sc_req->rl_sendbuf;
	काष्ठा ib_sge *sge;

	अगर (!sc->sc_unmap_count)
		वापस;

	/* The first two SGEs contain the transport header and
	 * the अंतरभूत buffer. These are always left mapped so
	 * they can be cheaply re-used.
	 */
	क्रम (sge = &sc->sc_sges[2]; sc->sc_unmap_count;
	     ++sge, --sc->sc_unmap_count)
		ib_dma_unmap_page(rdmab_device(rb), sge->addr, sge->length,
				  DMA_TO_DEVICE);

	kref_put(&sc->sc_req->rl_kref, rpcrdma_sendctx_करोne);
पूर्ण

/* Prepare an SGE क्रम the RPC-over-RDMA transport header.
 */
अटल व्योम rpcrdma_prepare_hdr_sge(काष्ठा rpcrdma_xprt *r_xprt,
				    काष्ठा rpcrdma_req *req, u32 len)
अणु
	काष्ठा rpcrdma_sendctx *sc = req->rl_sendctx;
	काष्ठा rpcrdma_regbuf *rb = req->rl_rdmabuf;
	काष्ठा ib_sge *sge = &sc->sc_sges[req->rl_wr.num_sge++];

	sge->addr = rdmab_addr(rb);
	sge->length = len;
	sge->lkey = rdmab_lkey(rb);

	ib_dma_sync_single_क्रम_device(rdmab_device(rb), sge->addr, sge->length,
				      DMA_TO_DEVICE);
पूर्ण

/* The head iovec is straightक्रमward, as it is usually alपढ़ोy
 * DMA-mapped. Sync the content that has changed.
 */
अटल bool rpcrdma_prepare_head_iov(काष्ठा rpcrdma_xprt *r_xprt,
				     काष्ठा rpcrdma_req *req, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rpcrdma_sendctx *sc = req->rl_sendctx;
	काष्ठा ib_sge *sge = &sc->sc_sges[req->rl_wr.num_sge++];
	काष्ठा rpcrdma_regbuf *rb = req->rl_sendbuf;

	अगर (!rpcrdma_regbuf_dma_map(r_xprt, rb))
		वापस false;

	sge->addr = rdmab_addr(rb);
	sge->length = len;
	sge->lkey = rdmab_lkey(rb);

	ib_dma_sync_single_क्रम_device(rdmab_device(rb), sge->addr, sge->length,
				      DMA_TO_DEVICE);
	वापस true;
पूर्ण

/* If there is a page list present, DMA map and prepare an
 * SGE क्रम each page to be sent.
 */
अटल bool rpcrdma_prepare_pagelist(काष्ठा rpcrdma_req *req,
				     काष्ठा xdr_buf *xdr)
अणु
	काष्ठा rpcrdma_sendctx *sc = req->rl_sendctx;
	काष्ठा rpcrdma_regbuf *rb = req->rl_sendbuf;
	अचिन्हित पूर्णांक page_base, len, reमुख्यing;
	काष्ठा page **ppages;
	काष्ठा ib_sge *sge;

	ppages = xdr->pages + (xdr->page_base >> PAGE_SHIFT);
	page_base = offset_in_page(xdr->page_base);
	reमुख्यing = xdr->page_len;
	जबतक (reमुख्यing) अणु
		sge = &sc->sc_sges[req->rl_wr.num_sge++];
		len = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - page_base, reमुख्यing);
		sge->addr = ib_dma_map_page(rdmab_device(rb), *ppages,
					    page_base, len, DMA_TO_DEVICE);
		अगर (ib_dma_mapping_error(rdmab_device(rb), sge->addr))
			जाओ out_mapping_err;

		sge->length = len;
		sge->lkey = rdmab_lkey(rb);

		sc->sc_unmap_count++;
		ppages++;
		reमुख्यing -= len;
		page_base = 0;
	पूर्ण

	वापस true;

out_mapping_err:
	trace_xprtrdma_dma_maperr(sge->addr);
	वापस false;
पूर्ण

/* The tail iovec may include an XDR pad क्रम the page list,
 * as well as additional content, and may not reside in the
 * same page as the head iovec.
 */
अटल bool rpcrdma_prepare_tail_iov(काष्ठा rpcrdma_req *req,
				     काष्ठा xdr_buf *xdr,
				     अचिन्हित पूर्णांक page_base, अचिन्हित पूर्णांक len)
अणु
	काष्ठा rpcrdma_sendctx *sc = req->rl_sendctx;
	काष्ठा ib_sge *sge = &sc->sc_sges[req->rl_wr.num_sge++];
	काष्ठा rpcrdma_regbuf *rb = req->rl_sendbuf;
	काष्ठा page *page = virt_to_page(xdr->tail[0].iov_base);

	sge->addr = ib_dma_map_page(rdmab_device(rb), page, page_base, len,
				    DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(rdmab_device(rb), sge->addr))
		जाओ out_mapping_err;

	sge->length = len;
	sge->lkey = rdmab_lkey(rb);
	++sc->sc_unmap_count;
	वापस true;

out_mapping_err:
	trace_xprtrdma_dma_maperr(sge->addr);
	वापस false;
पूर्ण

/* Copy the tail to the end of the head buffer.
 */
अटल व्योम rpcrdma_pullup_tail_iov(काष्ठा rpcrdma_xprt *r_xprt,
				    काष्ठा rpcrdma_req *req,
				    काष्ठा xdr_buf *xdr)
अणु
	अचिन्हित अक्षर *dst;

	dst = (अचिन्हित अक्षर *)xdr->head[0].iov_base;
	dst += xdr->head[0].iov_len + xdr->page_len;
	स_हटाओ(dst, xdr->tail[0].iov_base, xdr->tail[0].iov_len);
	r_xprt->rx_stats.pullup_copy_count += xdr->tail[0].iov_len;
पूर्ण

/* Copy pagelist content पूर्णांकo the head buffer.
 */
अटल व्योम rpcrdma_pullup_pagelist(काष्ठा rpcrdma_xprt *r_xprt,
				    काष्ठा rpcrdma_req *req,
				    काष्ठा xdr_buf *xdr)
अणु
	अचिन्हित पूर्णांक len, page_base, reमुख्यing;
	काष्ठा page **ppages;
	अचिन्हित अक्षर *src, *dst;

	dst = (अचिन्हित अक्षर *)xdr->head[0].iov_base;
	dst += xdr->head[0].iov_len;
	ppages = xdr->pages + (xdr->page_base >> PAGE_SHIFT);
	page_base = offset_in_page(xdr->page_base);
	reमुख्यing = xdr->page_len;
	जबतक (reमुख्यing) अणु
		src = page_address(*ppages);
		src += page_base;
		len = min_t(अचिन्हित पूर्णांक, PAGE_SIZE - page_base, reमुख्यing);
		स_नकल(dst, src, len);
		r_xprt->rx_stats.pullup_copy_count += len;

		ppages++;
		dst += len;
		reमुख्यing -= len;
		page_base = 0;
	पूर्ण
पूर्ण

/* Copy the contents of @xdr पूर्णांकo @rl_sendbuf and DMA sync it.
 * When the head, pagelist, and tail are small, a pull-up copy
 * is considerably less costly than DMA mapping the components
 * of @xdr.
 *
 * Assumptions:
 *  - the caller has alपढ़ोy verअगरied that the total length
 *    of the RPC Call body will fit पूर्णांकo @rl_sendbuf.
 */
अटल bool rpcrdma_prepare_noch_pullup(काष्ठा rpcrdma_xprt *r_xprt,
					काष्ठा rpcrdma_req *req,
					काष्ठा xdr_buf *xdr)
अणु
	अगर (unlikely(xdr->tail[0].iov_len))
		rpcrdma_pullup_tail_iov(r_xprt, req, xdr);

	अगर (unlikely(xdr->page_len))
		rpcrdma_pullup_pagelist(r_xprt, req, xdr);

	/* The whole RPC message resides in the head iovec now */
	वापस rpcrdma_prepare_head_iov(r_xprt, req, xdr->len);
पूर्ण

अटल bool rpcrdma_prepare_noch_mapped(काष्ठा rpcrdma_xprt *r_xprt,
					काष्ठा rpcrdma_req *req,
					काष्ठा xdr_buf *xdr)
अणु
	काष्ठा kvec *tail = &xdr->tail[0];

	अगर (!rpcrdma_prepare_head_iov(r_xprt, req, xdr->head[0].iov_len))
		वापस false;
	अगर (xdr->page_len)
		अगर (!rpcrdma_prepare_pagelist(req, xdr))
			वापस false;
	अगर (tail->iov_len)
		अगर (!rpcrdma_prepare_tail_iov(req, xdr,
					      offset_in_page(tail->iov_base),
					      tail->iov_len))
			वापस false;

	अगर (req->rl_sendctx->sc_unmap_count)
		kref_get(&req->rl_kref);
	वापस true;
पूर्ण

अटल bool rpcrdma_prepare_पढ़ोch(काष्ठा rpcrdma_xprt *r_xprt,
				   काष्ठा rpcrdma_req *req,
				   काष्ठा xdr_buf *xdr)
अणु
	अगर (!rpcrdma_prepare_head_iov(r_xprt, req, xdr->head[0].iov_len))
		वापस false;

	/* If there is a Read chunk, the page list is being handled
	 * via explicit RDMA, and thus is skipped here.
	 */

	/* Do not include the tail अगर it is only an XDR pad */
	अगर (xdr->tail[0].iov_len > 3) अणु
		अचिन्हित पूर्णांक page_base, len;

		/* If the content in the page list is an odd length,
		 * xdr_ग_लिखो_pages() adds a pad at the beginning of
		 * the tail iovec. Force the tail's non-pad content to
		 * land at the next XDR position in the Send message.
		 */
		page_base = offset_in_page(xdr->tail[0].iov_base);
		len = xdr->tail[0].iov_len;
		page_base += len & 3;
		len -= len & 3;
		अगर (!rpcrdma_prepare_tail_iov(req, xdr, page_base, len))
			वापस false;
		kref_get(&req->rl_kref);
	पूर्ण

	वापस true;
पूर्ण

/**
 * rpcrdma_prepare_send_sges - Conकाष्ठा SGEs क्रम a Send WR
 * @r_xprt: controlling transport
 * @req: context of RPC Call being marshalled
 * @hdrlen: size of transport header, in bytes
 * @xdr: xdr_buf containing RPC Call
 * @rtype: chunk type being encoded
 *
 * Returns 0 on success; otherwise a negative त्रुटि_सं is वापसed.
 */
अंतरभूत पूर्णांक rpcrdma_prepare_send_sges(काष्ठा rpcrdma_xprt *r_xprt,
				     काष्ठा rpcrdma_req *req, u32 hdrlen,
				     काष्ठा xdr_buf *xdr,
				     क्रमागत rpcrdma_chunktype rtype)
अणु
	पूर्णांक ret;

	ret = -EAGAIN;
	req->rl_sendctx = rpcrdma_sendctx_get_locked(r_xprt);
	अगर (!req->rl_sendctx)
		जाओ out_nosc;
	req->rl_sendctx->sc_unmap_count = 0;
	req->rl_sendctx->sc_req = req;
	kref_init(&req->rl_kref);
	req->rl_wr.wr_cqe = &req->rl_sendctx->sc_cqe;
	req->rl_wr.sg_list = req->rl_sendctx->sc_sges;
	req->rl_wr.num_sge = 0;
	req->rl_wr.opcode = IB_WR_SEND;

	rpcrdma_prepare_hdr_sge(r_xprt, req, hdrlen);

	ret = -EIO;
	चयन (rtype) अणु
	हाल rpcrdma_noch_pullup:
		अगर (!rpcrdma_prepare_noch_pullup(r_xprt, req, xdr))
			जाओ out_unmap;
		अवरोध;
	हाल rpcrdma_noch_mapped:
		अगर (!rpcrdma_prepare_noch_mapped(r_xprt, req, xdr))
			जाओ out_unmap;
		अवरोध;
	हाल rpcrdma_पढ़ोch:
		अगर (!rpcrdma_prepare_पढ़ोch(r_xprt, req, xdr))
			जाओ out_unmap;
		अवरोध;
	हाल rpcrdma_aपढ़ोch:
		अवरोध;
	शेष:
		जाओ out_unmap;
	पूर्ण

	वापस 0;

out_unmap:
	rpcrdma_sendctx_unmap(req->rl_sendctx);
out_nosc:
	trace_xprtrdma_prepsend_failed(&req->rl_slot, ret);
	वापस ret;
पूर्ण

/**
 * rpcrdma_marshal_req - Marshal and send one RPC request
 * @r_xprt: controlling transport
 * @rqst: RPC request to be marshaled
 *
 * For the RPC in "rqst", this function:
 *  - Chooses the transfer mode (eg., RDMA_MSG or RDMA_NOMSG)
 *  - Registers Read, Write, and Reply chunks
 *  - Conकाष्ठाs the transport header
 *  - Posts a Send WR to send the transport header and request
 *
 * Returns:
 *	%0 अगर the RPC was sent successfully,
 *	%-ENOTCONN अगर the connection was lost,
 *	%-EAGAIN अगर the caller should call again with the same arguments,
 *	%-ENOBUFS अगर the caller should call again after a delay,
 *	%-EMSGSIZE अगर the transport header is too small,
 *	%-EIO अगर a permanent problem occurred जबतक marshaling.
 */
पूर्णांक
rpcrdma_marshal_req(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा rpcrdma_req *req = rpcr_to_rdmar(rqst);
	काष्ठा xdr_stream *xdr = &req->rl_stream;
	क्रमागत rpcrdma_chunktype rtype, wtype;
	काष्ठा xdr_buf *buf = &rqst->rq_snd_buf;
	bool ddp_allowed;
	__be32 *p;
	पूर्णांक ret;

	अगर (unlikely(rqst->rq_rcv_buf.flags & XDRBUF_SPARSE_PAGES)) अणु
		ret = rpcrdma_alloc_sparse_pages(&rqst->rq_rcv_buf);
		अगर (ret)
			वापस ret;
	पूर्ण

	rpcrdma_set_xdrlen(&req->rl_hdrbuf, 0);
	xdr_init_encode(xdr, &req->rl_hdrbuf, rdmab_data(req->rl_rdmabuf),
			rqst);

	/* Fixed header fields */
	ret = -EMSGSIZE;
	p = xdr_reserve_space(xdr, 4 * माप(*p));
	अगर (!p)
		जाओ out_err;
	*p++ = rqst->rq_xid;
	*p++ = rpcrdma_version;
	*p++ = r_xprt->rx_buf.rb_max_requests;

	/* When the ULP employs a GSS flavor that guarantees पूर्णांकegrity
	 * or privacy, direct data placement of inभागidual data items
	 * is not allowed.
	 */
	ddp_allowed = !test_bit(RPCAUTH_AUTH_DATATOUCH,
				&rqst->rq_cred->cr_auth->au_flags);

	/*
	 * Chunks needed क्रम results?
	 *
	 * o If the expected result is under the अंतरभूत threshold, all ops
	 *   वापस as अंतरभूत.
	 * o Large पढ़ो ops वापस data as ग_लिखो chunk(s), header as
	 *   अंतरभूत.
	 * o Large non-पढ़ो ops वापस as a single reply chunk.
	 */
	अगर (rpcrdma_results_अंतरभूत(r_xprt, rqst))
		wtype = rpcrdma_noch;
	अन्यथा अगर ((ddp_allowed && rqst->rq_rcv_buf.flags & XDRBUF_READ) &&
		 rpcrdma_nonpayload_अंतरभूत(r_xprt, rqst))
		wtype = rpcrdma_ग_लिखोch;
	अन्यथा
		wtype = rpcrdma_replych;

	/*
	 * Chunks needed क्रम arguments?
	 *
	 * o If the total request is under the अंतरभूत threshold, all ops
	 *   are sent as अंतरभूत.
	 * o Large ग_लिखो ops transmit data as पढ़ो chunk(s), header as
	 *   अंतरभूत.
	 * o Large non-ग_लिखो ops are sent with the entire message as a
	 *   single पढ़ो chunk (protocol 0-position special हाल).
	 *
	 * This assumes that the upper layer करोes not present a request
	 * that both has a data payload, and whose non-data arguments
	 * by themselves are larger than the अंतरभूत threshold.
	 */
	अगर (rpcrdma_args_अंतरभूत(r_xprt, rqst)) अणु
		*p++ = rdma_msg;
		rtype = buf->len < rdmab_length(req->rl_sendbuf) ?
			rpcrdma_noch_pullup : rpcrdma_noch_mapped;
	पूर्ण अन्यथा अगर (ddp_allowed && buf->flags & XDRBUF_WRITE) अणु
		*p++ = rdma_msg;
		rtype = rpcrdma_पढ़ोch;
	पूर्ण अन्यथा अणु
		r_xprt->rx_stats.nomsg_call_count++;
		*p++ = rdma_nomsg;
		rtype = rpcrdma_aपढ़ोch;
	पूर्ण

	/* This implementation supports the following combinations
	 * of chunk lists in one RPC-over-RDMA Call message:
	 *
	 *   - Read list
	 *   - Write list
	 *   - Reply chunk
	 *   - Read list + Reply chunk
	 *
	 * It might not yet support the following combinations:
	 *
	 *   - Read list + Write list
	 *
	 * It करोes not support the following combinations:
	 *
	 *   - Write list + Reply chunk
	 *   - Read list + Write list + Reply chunk
	 *
	 * This implementation supports only a single chunk in each
	 * Read or Write list. Thus क्रम example the client cannot
	 * send a Call message with a Position Zero Read chunk and a
	 * regular Read chunk at the same समय.
	 */
	ret = rpcrdma_encode_पढ़ो_list(r_xprt, req, rqst, rtype);
	अगर (ret)
		जाओ out_err;
	ret = rpcrdma_encode_ग_लिखो_list(r_xprt, req, rqst, wtype);
	अगर (ret)
		जाओ out_err;
	ret = rpcrdma_encode_reply_chunk(r_xprt, req, rqst, wtype);
	अगर (ret)
		जाओ out_err;

	ret = rpcrdma_prepare_send_sges(r_xprt, req, req->rl_hdrbuf.len,
					buf, rtype);
	अगर (ret)
		जाओ out_err;

	trace_xprtrdma_marshal(req, rtype, wtype);
	वापस 0;

out_err:
	trace_xprtrdma_marshal_failed(rqst, ret);
	r_xprt->rx_stats.failed_marshal_count++;
	frwr_reset(req);
	वापस ret;
पूर्ण

अटल व्योम __rpcrdma_update_cwnd_locked(काष्ठा rpc_xprt *xprt,
					 काष्ठा rpcrdma_buffer *buf,
					 u32 grant)
अणु
	buf->rb_credits = grant;
	xprt->cwnd = grant << RPC_CWNDSHIFT;
पूर्ण

अटल व्योम rpcrdma_update_cwnd(काष्ठा rpcrdma_xprt *r_xprt, u32 grant)
अणु
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;

	spin_lock(&xprt->transport_lock);
	__rpcrdma_update_cwnd_locked(xprt, &r_xprt->rx_buf, grant);
	spin_unlock(&xprt->transport_lock);
पूर्ण

/**
 * rpcrdma_reset_cwnd - Reset the xprt's congestion winकरोw
 * @r_xprt: controlling transport instance
 *
 * Prepare @r_xprt क्रम the next connection by reinitializing
 * its credit grant to one (see RFC 8166, Section 3.3.3).
 */
व्योम rpcrdma_reset_cwnd(काष्ठा rpcrdma_xprt *r_xprt)
अणु
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;

	spin_lock(&xprt->transport_lock);
	xprt->cong = 0;
	__rpcrdma_update_cwnd_locked(xprt, &r_xprt->rx_buf, 1);
	spin_unlock(&xprt->transport_lock);
पूर्ण

/**
 * rpcrdma_अंतरभूत_fixup - Scatter अंतरभूत received data पूर्णांकo rqst's iovecs
 * @rqst: controlling RPC request
 * @srcp: poपूर्णांकs to RPC message payload in receive buffer
 * @copy_len: reमुख्यing length of receive buffer content
 * @pad: Write chunk pad bytes needed (zero क्रम pure अंतरभूत)
 *
 * The upper layer has set the maximum number of bytes it can
 * receive in each component of rq_rcv_buf. These values are set in
 * the head.iov_len, page_len, tail.iov_len, and buflen fields.
 *
 * Unlike the TCP equivalent (xdr_partial_copy_from_skb), in
 * many हालs this function simply updates iov_base poपूर्णांकers in
 * rq_rcv_buf to poपूर्णांक directly to the received reply data, to
 * aव्योम copying reply data.
 *
 * Returns the count of bytes which had to be memcopied.
 */
अटल अचिन्हित दीर्घ
rpcrdma_अंतरभूत_fixup(काष्ठा rpc_rqst *rqst, अक्षर *srcp, पूर्णांक copy_len, पूर्णांक pad)
अणु
	अचिन्हित दीर्घ fixup_copy_count;
	पूर्णांक i, npages, curlen;
	अक्षर *destp;
	काष्ठा page **ppages;
	पूर्णांक page_base;

	/* The head iovec is redirected to the RPC reply message
	 * in the receive buffer, to aव्योम a memcopy.
	 */
	rqst->rq_rcv_buf.head[0].iov_base = srcp;
	rqst->rq_निजी_buf.head[0].iov_base = srcp;

	/* The contents of the receive buffer that follow
	 * head.iov_len bytes are copied पूर्णांकo the page list.
	 */
	curlen = rqst->rq_rcv_buf.head[0].iov_len;
	अगर (curlen > copy_len)
		curlen = copy_len;
	srcp += curlen;
	copy_len -= curlen;

	ppages = rqst->rq_rcv_buf.pages +
		(rqst->rq_rcv_buf.page_base >> PAGE_SHIFT);
	page_base = offset_in_page(rqst->rq_rcv_buf.page_base);
	fixup_copy_count = 0;
	अगर (copy_len && rqst->rq_rcv_buf.page_len) अणु
		पूर्णांक pagelist_len;

		pagelist_len = rqst->rq_rcv_buf.page_len;
		अगर (pagelist_len > copy_len)
			pagelist_len = copy_len;
		npages = PAGE_ALIGN(page_base + pagelist_len) >> PAGE_SHIFT;
		क्रम (i = 0; i < npages; i++) अणु
			curlen = PAGE_SIZE - page_base;
			अगर (curlen > pagelist_len)
				curlen = pagelist_len;

			destp = kmap_atomic(ppages[i]);
			स_नकल(destp + page_base, srcp, curlen);
			flush_dcache_page(ppages[i]);
			kunmap_atomic(destp);
			srcp += curlen;
			copy_len -= curlen;
			fixup_copy_count += curlen;
			pagelist_len -= curlen;
			अगर (!pagelist_len)
				अवरोध;
			page_base = 0;
		पूर्ण

		/* Implicit padding क्रम the last segment in a Write
		 * chunk is inserted अंतरभूत at the front of the tail
		 * iovec. The upper layer ignores the content of
		 * the pad. Simply ensure अंतरभूत content in the tail
		 * that follows the Write chunk is properly aligned.
		 */
		अगर (pad)
			srcp -= pad;
	पूर्ण

	/* The tail iovec is redirected to the reमुख्यing data
	 * in the receive buffer, to aव्योम a memcopy.
	 */
	अगर (copy_len || pad) अणु
		rqst->rq_rcv_buf.tail[0].iov_base = srcp;
		rqst->rq_निजी_buf.tail[0].iov_base = srcp;
	पूर्ण

	अगर (fixup_copy_count)
		trace_xprtrdma_fixup(rqst, fixup_copy_count);
	वापस fixup_copy_count;
पूर्ण

/* By convention, backchannel calls arrive via rdma_msg type
 * messages, and never populate the chunk lists. This makes
 * the RPC/RDMA header small and fixed in size, so it is
 * straightक्रमward to check the RPC header's direction field.
 */
अटल bool
rpcrdma_is_bcall(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_rep *rep)
#अगर defined(CONFIG_SUNRPC_BACKCHANNEL)
अणु
	काष्ठा xdr_stream *xdr = &rep->rr_stream;
	__be32 *p;

	अगर (rep->rr_proc != rdma_msg)
		वापस false;

	/* Peek at stream contents without advancing. */
	p = xdr_अंतरभूत_decode(xdr, 0);

	/* Chunk lists */
	अगर (xdr_item_is_present(p++))
		वापस false;
	अगर (xdr_item_is_present(p++))
		वापस false;
	अगर (xdr_item_is_present(p++))
		वापस false;

	/* RPC header */
	अगर (*p++ != rep->rr_xid)
		वापस false;
	अगर (*p != cpu_to_be32(RPC_CALL))
		वापस false;

	/* Now that we are sure this is a backchannel call,
	 * advance to the RPC header.
	 */
	p = xdr_अंतरभूत_decode(xdr, 3 * माप(*p));
	अगर (unlikely(!p))
		वापस true;

	rpcrdma_bc_receive_call(r_xprt, rep);
	वापस true;
पूर्ण
#अन्यथा	/* CONFIG_SUNRPC_BACKCHANNEL */
अणु
	वापस false;
पूर्ण
#पूर्ण_अगर	/* CONFIG_SUNRPC_BACKCHANNEL */

अटल पूर्णांक decode_rdma_segment(काष्ठा xdr_stream *xdr, u32 *length)
अणु
	u32 handle;
	u64 offset;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, 4 * माप(*p));
	अगर (unlikely(!p))
		वापस -EIO;

	xdr_decode_rdma_segment(p, &handle, length, &offset);
	trace_xprtrdma_decode_seg(handle, *length, offset);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_ग_लिखो_chunk(काष्ठा xdr_stream *xdr, u32 *length)
अणु
	u32 segcount, seglength;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, माप(*p));
	अगर (unlikely(!p))
		वापस -EIO;

	*length = 0;
	segcount = be32_to_cpup(p);
	जबतक (segcount--) अणु
		अगर (decode_rdma_segment(xdr, &seglength))
			वापस -EIO;
		*length += seglength;
	पूर्ण

	वापस 0;
पूर्ण

/* In RPC-over-RDMA Version One replies, a Read list is never
 * expected. This decoder is a stub that वापसs an error अगर
 * a Read list is present.
 */
अटल पूर्णांक decode_पढ़ो_list(काष्ठा xdr_stream *xdr)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, माप(*p));
	अगर (unlikely(!p))
		वापस -EIO;
	अगर (unlikely(xdr_item_is_present(p)))
		वापस -EIO;
	वापस 0;
पूर्ण

/* Supports only one Write chunk in the Write list
 */
अटल पूर्णांक decode_ग_लिखो_list(काष्ठा xdr_stream *xdr, u32 *length)
अणु
	u32 chunklen;
	bool first;
	__be32 *p;

	*length = 0;
	first = true;
	करो अणु
		p = xdr_अंतरभूत_decode(xdr, माप(*p));
		अगर (unlikely(!p))
			वापस -EIO;
		अगर (xdr_item_is_असलent(p))
			अवरोध;
		अगर (!first)
			वापस -EIO;

		अगर (decode_ग_लिखो_chunk(xdr, &chunklen))
			वापस -EIO;
		*length += chunklen;
		first = false;
	पूर्ण जबतक (true);
	वापस 0;
पूर्ण

अटल पूर्णांक decode_reply_chunk(काष्ठा xdr_stream *xdr, u32 *length)
अणु
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, माप(*p));
	अगर (unlikely(!p))
		वापस -EIO;

	*length = 0;
	अगर (xdr_item_is_present(p))
		अगर (decode_ग_लिखो_chunk(xdr, length))
			वापस -EIO;
	वापस 0;
पूर्ण

अटल पूर्णांक
rpcrdma_decode_msg(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_rep *rep,
		   काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा xdr_stream *xdr = &rep->rr_stream;
	u32 ग_लिखोlist, replychunk, rpclen;
	अक्षर *base;

	/* Decode the chunk lists */
	अगर (decode_पढ़ो_list(xdr))
		वापस -EIO;
	अगर (decode_ग_लिखो_list(xdr, &ग_लिखोlist))
		वापस -EIO;
	अगर (decode_reply_chunk(xdr, &replychunk))
		वापस -EIO;

	/* RDMA_MSG sanity checks */
	अगर (unlikely(replychunk))
		वापस -EIO;

	/* Build the RPC reply's Payload stream in rqst->rq_rcv_buf */
	base = (अक्षर *)xdr_अंतरभूत_decode(xdr, 0);
	rpclen = xdr_stream_reमुख्यing(xdr);
	r_xprt->rx_stats.fixup_copy_count +=
		rpcrdma_अंतरभूत_fixup(rqst, base, rpclen, ग_लिखोlist & 3);

	r_xprt->rx_stats.total_rdma_reply += ग_लिखोlist;
	वापस rpclen + xdr_align_size(ग_लिखोlist);
पूर्ण

अटल noअंतरभूत पूर्णांक
rpcrdma_decode_nomsg(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_rep *rep)
अणु
	काष्ठा xdr_stream *xdr = &rep->rr_stream;
	u32 ग_लिखोlist, replychunk;

	/* Decode the chunk lists */
	अगर (decode_पढ़ो_list(xdr))
		वापस -EIO;
	अगर (decode_ग_लिखो_list(xdr, &ग_लिखोlist))
		वापस -EIO;
	अगर (decode_reply_chunk(xdr, &replychunk))
		वापस -EIO;

	/* RDMA_NOMSG sanity checks */
	अगर (unlikely(ग_लिखोlist))
		वापस -EIO;
	अगर (unlikely(!replychunk))
		वापस -EIO;

	/* Reply chunk buffer alपढ़ोy is the reply vector */
	r_xprt->rx_stats.total_rdma_reply += replychunk;
	वापस replychunk;
पूर्ण

अटल noअंतरभूत पूर्णांक
rpcrdma_decode_error(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_rep *rep,
		     काष्ठा rpc_rqst *rqst)
अणु
	काष्ठा xdr_stream *xdr = &rep->rr_stream;
	__be32 *p;

	p = xdr_अंतरभूत_decode(xdr, माप(*p));
	अगर (unlikely(!p))
		वापस -EIO;

	चयन (*p) अणु
	हाल err_vers:
		p = xdr_अंतरभूत_decode(xdr, 2 * माप(*p));
		अगर (!p)
			अवरोध;
		trace_xprtrdma_err_vers(rqst, p, p + 1);
		अवरोध;
	हाल err_chunk:
		trace_xprtrdma_err_chunk(rqst);
		अवरोध;
	शेष:
		trace_xprtrdma_err_unrecognized(rqst, p);
	पूर्ण

	वापस -EIO;
पूर्ण

/**
 * rpcrdma_unpin_rqst - Release rqst without completing it
 * @rep: RPC/RDMA Receive context
 *
 * This is करोne when a connection is lost so that a Reply
 * can be dropped and its matching Call can be subsequently
 * retransmitted on a new connection.
 */
व्योम rpcrdma_unpin_rqst(काष्ठा rpcrdma_rep *rep)
अणु
	काष्ठा rpc_xprt *xprt = &rep->rr_rxprt->rx_xprt;
	काष्ठा rpc_rqst *rqst = rep->rr_rqst;
	काष्ठा rpcrdma_req *req = rpcr_to_rdmar(rqst);

	req->rl_reply = शून्य;
	rep->rr_rqst = शून्य;

	spin_lock(&xprt->queue_lock);
	xprt_unpin_rqst(rqst);
	spin_unlock(&xprt->queue_lock);
पूर्ण

/**
 * rpcrdma_complete_rqst - Pass completed rqst back to RPC
 * @rep: RPC/RDMA Receive context
 *
 * Reस्थिरruct the RPC reply and complete the transaction
 * जबतक @rqst is still pinned to ensure the rep, rqst, and
 * rq_task poपूर्णांकers reमुख्य stable.
 */
व्योम rpcrdma_complete_rqst(काष्ठा rpcrdma_rep *rep)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rep->rr_rxprt;
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;
	काष्ठा rpc_rqst *rqst = rep->rr_rqst;
	पूर्णांक status;

	चयन (rep->rr_proc) अणु
	हाल rdma_msg:
		status = rpcrdma_decode_msg(r_xprt, rep, rqst);
		अवरोध;
	हाल rdma_nomsg:
		status = rpcrdma_decode_nomsg(r_xprt, rep);
		अवरोध;
	हाल rdma_error:
		status = rpcrdma_decode_error(r_xprt, rep, rqst);
		अवरोध;
	शेष:
		status = -EIO;
	पूर्ण
	अगर (status < 0)
		जाओ out_badheader;

out:
	spin_lock(&xprt->queue_lock);
	xprt_complete_rqst(rqst->rq_task, status);
	xprt_unpin_rqst(rqst);
	spin_unlock(&xprt->queue_lock);
	वापस;

out_badheader:
	trace_xprtrdma_reply_hdr_err(rep);
	r_xprt->rx_stats.bad_reply_count++;
	rqst->rq_task->tk_status = status;
	status = 0;
	जाओ out;
पूर्ण

अटल व्योम rpcrdma_reply_करोne(काष्ठा kref *kref)
अणु
	काष्ठा rpcrdma_req *req =
		container_of(kref, काष्ठा rpcrdma_req, rl_kref);

	rpcrdma_complete_rqst(req->rl_reply);
पूर्ण

/**
 * rpcrdma_reply_handler - Process received RPC/RDMA messages
 * @rep: Incoming rpcrdma_rep object to process
 *
 * Errors must result in the RPC task either being awakened, or
 * allowed to समयout, to discover the errors at that समय.
 */
व्योम rpcrdma_reply_handler(काष्ठा rpcrdma_rep *rep)
अणु
	काष्ठा rpcrdma_xprt *r_xprt = rep->rr_rxprt;
	काष्ठा rpc_xprt *xprt = &r_xprt->rx_xprt;
	काष्ठा rpcrdma_buffer *buf = &r_xprt->rx_buf;
	काष्ठा rpcrdma_req *req;
	काष्ठा rpc_rqst *rqst;
	u32 credits;
	__be32 *p;

	/* Any data means we had a useful conversation, so
	 * then we करोn't need to delay the next reconnect.
	 */
	अगर (xprt->reestablish_समयout)
		xprt->reestablish_समयout = 0;

	/* Fixed transport header fields */
	xdr_init_decode(&rep->rr_stream, &rep->rr_hdrbuf,
			rep->rr_hdrbuf.head[0].iov_base, शून्य);
	p = xdr_अंतरभूत_decode(&rep->rr_stream, 4 * माप(*p));
	अगर (unlikely(!p))
		जाओ out_लघुreply;
	rep->rr_xid = *p++;
	rep->rr_vers = *p++;
	credits = be32_to_cpu(*p++);
	rep->rr_proc = *p++;

	अगर (rep->rr_vers != rpcrdma_version)
		जाओ out_badversion;

	अगर (rpcrdma_is_bcall(r_xprt, rep))
		वापस;

	/* Match incoming rpcrdma_rep to an rpcrdma_req to
	 * get context क्रम handling any incoming chunks.
	 */
	spin_lock(&xprt->queue_lock);
	rqst = xprt_lookup_rqst(xprt, rep->rr_xid);
	अगर (!rqst)
		जाओ out_norqst;
	xprt_pin_rqst(rqst);
	spin_unlock(&xprt->queue_lock);

	अगर (credits == 0)
		credits = 1;	/* करोn't deadlock */
	अन्यथा अगर (credits > r_xprt->rx_ep->re_max_requests)
		credits = r_xprt->rx_ep->re_max_requests;
	rpcrdma_post_recvs(r_xprt, credits + (buf->rb_bc_srv_max_requests << 1),
			   false);
	अगर (buf->rb_credits != credits)
		rpcrdma_update_cwnd(r_xprt, credits);

	req = rpcr_to_rdmar(rqst);
	अगर (unlikely(req->rl_reply))
		rpcrdma_rep_put(buf, req->rl_reply);
	req->rl_reply = rep;
	rep->rr_rqst = rqst;

	trace_xprtrdma_reply(rqst->rq_task, rep, credits);

	अगर (rep->rr_wc_flags & IB_WC_WITH_INVALIDATE)
		frwr_reminv(rep, &req->rl_रेजिस्टरed);
	अगर (!list_empty(&req->rl_रेजिस्टरed))
		frwr_unmap_async(r_xprt, req);
		/* LocalInv completion will complete the RPC */
	अन्यथा
		kref_put(&req->rl_kref, rpcrdma_reply_करोne);
	वापस;

out_badversion:
	trace_xprtrdma_reply_vers_err(rep);
	जाओ out;

out_norqst:
	spin_unlock(&xprt->queue_lock);
	trace_xprtrdma_reply_rqst_err(rep);
	जाओ out;

out_लघुreply:
	trace_xprtrdma_reply_लघु_err(rep);

out:
	rpcrdma_rep_put(buf, rep);
पूर्ण
