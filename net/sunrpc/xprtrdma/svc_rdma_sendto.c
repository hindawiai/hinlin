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
 * The मुख्य entry poपूर्णांक is svc_rdma_sendto. This is called by the
 * RPC server when an RPC Reply is पढ़ोy to be transmitted to a client.
 *
 * The passed-in svc_rqst contains a काष्ठा xdr_buf which holds an
 * XDR-encoded RPC Reply message. sendto must स्थिरruct the RPC-over-RDMA
 * transport header, post all Write WRs needed क्रम this Reply, then post
 * a Send WR conveying the transport header and the RPC message itself to
 * the client.
 *
 * svc_rdma_sendto must fully transmit the Reply beक्रमe वापसing, as
 * the svc_rqst will be recycled as soon as sendto वापसs. Reमुख्यing
 * resources referred to by the svc_rqst are also recycled at that समय.
 * Thereक्रमe any resources that must reमुख्य दीर्घer must be detached
 * from the svc_rqst and released later.
 *
 * Page Management
 *
 * The I/O that perक्रमms Reply transmission is asynchronous, and may
 * complete well after sendto वापसs. Thus pages under I/O must be
 * हटाओd from the svc_rqst beक्रमe sendto वापसs.
 *
 * The logic here depends on Send Queue and completion ordering. Since
 * the Send WR is always posted last, it will always complete last. Thus
 * when it completes, it is guaranteed that all previous Write WRs have
 * also completed.
 *
 * Write WRs are स्थिरructed and posted. Each Write segment माला_लो its own
 * svc_rdma_rw_ctxt, allowing the Write completion handler to find and
 * DMA-unmap the pages under I/O क्रम that Write segment. The Write
 * completion handler करोes not release any pages.
 *
 * When the Send WR is स्थिरructed, it also माला_लो its own svc_rdma_send_ctxt.
 * The ownership of all of the Reply's pages are transferred पूर्णांकo that
 * ctxt, the Send WR is posted, and sendto वापसs.
 *
 * The svc_rdma_send_ctxt is presented when the Send WR completes. The
 * Send completion handler finally releases the Reply's pages.
 *
 * This mechanism also assumes that completions on the transport's Send
 * Completion Queue करो not run in parallel. Otherwise a Write completion
 * and Send completion running at the same समय could release pages that
 * are still DMA-mapped.
 *
 * Error Handling
 *
 * - If the Send WR is posted successfully, it will either complete
 *   successfully, or get flushed. Either way, the Send completion
 *   handler releases the Reply's pages.
 * - If the Send WR cannot be not posted, the क्रमward path releases
 *   the Reply's pages.
 *
 * This handles the हाल, without the use of page reference counting,
 * where two dअगरferent Write segments send portions of the same page.
 */

#समावेश <linux/spinlock.h>
#समावेश <यंत्र/unaligned.h>

#समावेश <rdma/ib_verbs.h>
#समावेश <rdma/rdma_cm.h>

#समावेश <linux/sunrpc/debug.h>
#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

अटल व्योम svc_rdma_wc_send(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);

अटल अंतरभूत काष्ठा svc_rdma_send_ctxt *
svc_rdma_next_send_ctxt(काष्ठा list_head *list)
अणु
	वापस list_first_entry_or_null(list, काष्ठा svc_rdma_send_ctxt,
					sc_list);
पूर्ण

अटल व्योम svc_rdma_send_cid_init(काष्ठा svcxprt_rdma *rdma,
				   काष्ठा rpc_rdma_cid *cid)
अणु
	cid->ci_queue_id = rdma->sc_sq_cq->res.id;
	cid->ci_completion_id = atomic_inc_वापस(&rdma->sc_completion_ids);
पूर्ण

अटल काष्ठा svc_rdma_send_ctxt *
svc_rdma_send_ctxt_alloc(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_send_ctxt *ctxt;
	dma_addr_t addr;
	व्योम *buffer;
	माप_प्रकार size;
	पूर्णांक i;

	size = माप(*ctxt);
	size += rdma->sc_max_send_sges * माप(काष्ठा ib_sge);
	ctxt = kदो_स्मृति(size, GFP_KERNEL);
	अगर (!ctxt)
		जाओ fail0;
	buffer = kदो_स्मृति(rdma->sc_max_req_size, GFP_KERNEL);
	अगर (!buffer)
		जाओ fail1;
	addr = ib_dma_map_single(rdma->sc_pd->device, buffer,
				 rdma->sc_max_req_size, DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(rdma->sc_pd->device, addr))
		जाओ fail2;

	svc_rdma_send_cid_init(rdma, &ctxt->sc_cid);

	ctxt->sc_send_wr.next = शून्य;
	ctxt->sc_send_wr.wr_cqe = &ctxt->sc_cqe;
	ctxt->sc_send_wr.sg_list = ctxt->sc_sges;
	ctxt->sc_send_wr.send_flags = IB_SEND_SIGNALED;
	init_completion(&ctxt->sc_करोne);
	ctxt->sc_cqe.करोne = svc_rdma_wc_send;
	ctxt->sc_xprt_buf = buffer;
	xdr_buf_init(&ctxt->sc_hdrbuf, ctxt->sc_xprt_buf,
		     rdma->sc_max_req_size);
	ctxt->sc_sges[0].addr = addr;

	क्रम (i = 0; i < rdma->sc_max_send_sges; i++)
		ctxt->sc_sges[i].lkey = rdma->sc_pd->local_dma_lkey;
	वापस ctxt;

fail2:
	kमुक्त(buffer);
fail1:
	kमुक्त(ctxt);
fail0:
	वापस शून्य;
पूर्ण

/**
 * svc_rdma_send_ctxts_destroy - Release all send_ctxt's क्रम an xprt
 * @rdma: svcxprt_rdma being torn करोwn
 *
 */
व्योम svc_rdma_send_ctxts_destroy(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_send_ctxt *ctxt;

	जबतक ((ctxt = svc_rdma_next_send_ctxt(&rdma->sc_send_ctxts))) अणु
		list_del(&ctxt->sc_list);
		ib_dma_unmap_single(rdma->sc_pd->device,
				    ctxt->sc_sges[0].addr,
				    rdma->sc_max_req_size,
				    DMA_TO_DEVICE);
		kमुक्त(ctxt->sc_xprt_buf);
		kमुक्त(ctxt);
	पूर्ण
पूर्ण

/**
 * svc_rdma_send_ctxt_get - Get a मुक्त send_ctxt
 * @rdma: controlling svcxprt_rdma
 *
 * Returns a पढ़ोy-to-use send_ctxt, or शून्य अगर none are
 * available and a fresh one cannot be allocated.
 */
काष्ठा svc_rdma_send_ctxt *svc_rdma_send_ctxt_get(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_send_ctxt *ctxt;

	spin_lock(&rdma->sc_send_lock);
	ctxt = svc_rdma_next_send_ctxt(&rdma->sc_send_ctxts);
	अगर (!ctxt)
		जाओ out_empty;
	list_del(&ctxt->sc_list);
	spin_unlock(&rdma->sc_send_lock);

out:
	rpcrdma_set_xdrlen(&ctxt->sc_hdrbuf, 0);
	xdr_init_encode(&ctxt->sc_stream, &ctxt->sc_hdrbuf,
			ctxt->sc_xprt_buf, शून्य);

	ctxt->sc_send_wr.num_sge = 0;
	ctxt->sc_cur_sge_no = 0;
	वापस ctxt;

out_empty:
	spin_unlock(&rdma->sc_send_lock);
	ctxt = svc_rdma_send_ctxt_alloc(rdma);
	अगर (!ctxt)
		वापस शून्य;
	जाओ out;
पूर्ण

/**
 * svc_rdma_send_ctxt_put - Return send_ctxt to मुक्त list
 * @rdma: controlling svcxprt_rdma
 * @ctxt: object to वापस to the मुक्त list
 */
व्योम svc_rdma_send_ctxt_put(काष्ठा svcxprt_rdma *rdma,
			    काष्ठा svc_rdma_send_ctxt *ctxt)
अणु
	काष्ठा ib_device *device = rdma->sc_cm_id->device;
	अचिन्हित पूर्णांक i;

	/* The first SGE contains the transport header, which
	 * reमुख्यs mapped until @ctxt is destroyed.
	 */
	क्रम (i = 1; i < ctxt->sc_send_wr.num_sge; i++) अणु
		ib_dma_unmap_page(device,
				  ctxt->sc_sges[i].addr,
				  ctxt->sc_sges[i].length,
				  DMA_TO_DEVICE);
		trace_svcrdma_dma_unmap_page(rdma,
					     ctxt->sc_sges[i].addr,
					     ctxt->sc_sges[i].length);
	पूर्ण

	spin_lock(&rdma->sc_send_lock);
	list_add(&ctxt->sc_list, &rdma->sc_send_ctxts);
	spin_unlock(&rdma->sc_send_lock);
पूर्ण

/**
 * svc_rdma_wc_send - Invoked by RDMA provider क्रम each polled Send WC
 * @cq: Completion Queue context
 * @wc: Work Completion object
 *
 * NB: The svc_xprt/svcxprt_rdma is pinned whenever it's possible that
 * the Send completion handler could be running.
 */
अटल व्योम svc_rdma_wc_send(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा svcxprt_rdma *rdma = cq->cq_context;
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा svc_rdma_send_ctxt *ctxt =
		container_of(cqe, काष्ठा svc_rdma_send_ctxt, sc_cqe);

	trace_svcrdma_wc_send(wc, &ctxt->sc_cid);

	complete(&ctxt->sc_करोne);

	atomic_inc(&rdma->sc_sq_avail);
	wake_up(&rdma->sc_send_रुको);

	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		svc_xprt_deferred_बंद(&rdma->sc_xprt);
पूर्ण

/**
 * svc_rdma_send - Post a single Send WR
 * @rdma: transport on which to post the WR
 * @ctxt: send ctxt with a Send WR पढ़ोy to post
 *
 * Returns zero अगर the Send WR was posted successfully. Otherwise, a
 * negative त्रुटि_सं is वापसed.
 */
पूर्णांक svc_rdma_send(काष्ठा svcxprt_rdma *rdma, काष्ठा svc_rdma_send_ctxt *ctxt)
अणु
	काष्ठा ib_send_wr *wr = &ctxt->sc_send_wr;
	पूर्णांक ret;

	reinit_completion(&ctxt->sc_करोne);

	/* Sync the transport header buffer */
	ib_dma_sync_single_क्रम_device(rdma->sc_pd->device,
				      wr->sg_list[0].addr,
				      wr->sg_list[0].length,
				      DMA_TO_DEVICE);

	/* If the SQ is full, रुको until an SQ entry is available */
	जबतक (1) अणु
		अगर ((atomic_dec_वापस(&rdma->sc_sq_avail) < 0)) अणु
			percpu_counter_inc(&svcrdma_stat_sq_starve);
			trace_svcrdma_sq_full(rdma);
			atomic_inc(&rdma->sc_sq_avail);
			रुको_event(rdma->sc_send_रुको,
				   atomic_पढ़ो(&rdma->sc_sq_avail) > 1);
			अगर (test_bit(XPT_CLOSE, &rdma->sc_xprt.xpt_flags))
				वापस -ENOTCONN;
			trace_svcrdma_sq_retry(rdma);
			जारी;
		पूर्ण

		trace_svcrdma_post_send(ctxt);
		ret = ib_post_send(rdma->sc_qp, wr, शून्य);
		अगर (ret)
			अवरोध;
		वापस 0;
	पूर्ण

	trace_svcrdma_sq_post_err(rdma, ret);
	svc_xprt_deferred_बंद(&rdma->sc_xprt);
	wake_up(&rdma->sc_send_रुको);
	वापस ret;
पूर्ण

/**
 * svc_rdma_encode_पढ़ो_list - Encode RPC Reply's Read chunk list
 * @sctxt: Send context क्रम the RPC Reply
 *
 * Return values:
 *   On success, वापसs length in bytes of the Reply XDR buffer
 *   that was consumed by the Reply Read list
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल sमाप_प्रकार svc_rdma_encode_पढ़ो_list(काष्ठा svc_rdma_send_ctxt *sctxt)
अणु
	/* RPC-over-RDMA version 1 replies never have a Read list. */
	वापस xdr_stream_encode_item_असलent(&sctxt->sc_stream);
पूर्ण

/**
 * svc_rdma_encode_ग_लिखो_segment - Encode one Write segment
 * @sctxt: Send context क्रम the RPC Reply
 * @chunk: Write chunk to push
 * @reमुख्यing: reमुख्यing bytes of the payload left in the Write chunk
 * @segno: which segment in the chunk
 *
 * Return values:
 *   On success, वापसs length in bytes of the Reply XDR buffer
 *   that was consumed by the Write segment, and updates @reमुख्यing
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल sमाप_प्रकार svc_rdma_encode_ग_लिखो_segment(काष्ठा svc_rdma_send_ctxt *sctxt,
					     स्थिर काष्ठा svc_rdma_chunk *chunk,
					     u32 *reमुख्यing, अचिन्हित पूर्णांक segno)
अणु
	स्थिर काष्ठा svc_rdma_segment *segment = &chunk->ch_segments[segno];
	स्थिर माप_प्रकार len = rpcrdma_segment_maxsz * माप(__be32);
	u32 length;
	__be32 *p;

	p = xdr_reserve_space(&sctxt->sc_stream, len);
	अगर (!p)
		वापस -EMSGSIZE;

	length = min_t(u32, *reमुख्यing, segment->rs_length);
	*reमुख्यing -= length;
	xdr_encode_rdma_segment(p, segment->rs_handle, length,
				segment->rs_offset);
	trace_svcrdma_encode_wseg(sctxt, segno, segment->rs_handle, length,
				  segment->rs_offset);
	वापस len;
पूर्ण

/**
 * svc_rdma_encode_ग_लिखो_chunk - Encode one Write chunk
 * @sctxt: Send context क्रम the RPC Reply
 * @chunk: Write chunk to push
 *
 * Copy a Write chunk from the Call transport header to the
 * Reply transport header. Update each segment's length field
 * to reflect the number of bytes written in that segment.
 *
 * Return values:
 *   On success, वापसs length in bytes of the Reply XDR buffer
 *   that was consumed by the Write chunk
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल sमाप_प्रकार svc_rdma_encode_ग_लिखो_chunk(काष्ठा svc_rdma_send_ctxt *sctxt,
					   स्थिर काष्ठा svc_rdma_chunk *chunk)
अणु
	u32 reमुख्यing = chunk->ch_payload_length;
	अचिन्हित पूर्णांक segno;
	sमाप_प्रकार len, ret;

	len = 0;
	ret = xdr_stream_encode_item_present(&sctxt->sc_stream);
	अगर (ret < 0)
		वापस ret;
	len += ret;

	ret = xdr_stream_encode_u32(&sctxt->sc_stream, chunk->ch_segcount);
	अगर (ret < 0)
		वापस ret;
	len += ret;

	क्रम (segno = 0; segno < chunk->ch_segcount; segno++) अणु
		ret = svc_rdma_encode_ग_लिखो_segment(sctxt, chunk, &reमुख्यing, segno);
		अगर (ret < 0)
			वापस ret;
		len += ret;
	पूर्ण

	वापस len;
पूर्ण

/**
 * svc_rdma_encode_ग_लिखो_list - Encode RPC Reply's Write chunk list
 * @rctxt: Reply context with inक्रमmation about the RPC Call
 * @sctxt: Send context क्रम the RPC Reply
 *
 * Return values:
 *   On success, वापसs length in bytes of the Reply XDR buffer
 *   that was consumed by the Reply's Write list
 *   %-EMSGSIZE on XDR buffer overflow
 */
अटल sमाप_प्रकार svc_rdma_encode_ग_लिखो_list(काष्ठा svc_rdma_recv_ctxt *rctxt,
					  काष्ठा svc_rdma_send_ctxt *sctxt)
अणु
	काष्ठा svc_rdma_chunk *chunk;
	sमाप_प्रकार len, ret;

	len = 0;
	pcl_क्रम_each_chunk(chunk, &rctxt->rc_ग_लिखो_pcl) अणु
		ret = svc_rdma_encode_ग_लिखो_chunk(sctxt, chunk);
		अगर (ret < 0)
			वापस ret;
		len += ret;
	पूर्ण

	/* Terminate the Write list */
	ret = xdr_stream_encode_item_असलent(&sctxt->sc_stream);
	अगर (ret < 0)
		वापस ret;

	वापस len + ret;
पूर्ण

/**
 * svc_rdma_encode_reply_chunk - Encode RPC Reply's Reply chunk
 * @rctxt: Reply context with inक्रमmation about the RPC Call
 * @sctxt: Send context क्रम the RPC Reply
 * @length: size in bytes of the payload in the Reply chunk
 *
 * Return values:
 *   On success, वापसs length in bytes of the Reply XDR buffer
 *   that was consumed by the Reply's Reply chunk
 *   %-EMSGSIZE on XDR buffer overflow
 *   %-E2BIG अगर the RPC message is larger than the Reply chunk
 */
अटल sमाप_प्रकार
svc_rdma_encode_reply_chunk(काष्ठा svc_rdma_recv_ctxt *rctxt,
			    काष्ठा svc_rdma_send_ctxt *sctxt,
			    अचिन्हित पूर्णांक length)
अणु
	काष्ठा svc_rdma_chunk *chunk;

	अगर (pcl_is_empty(&rctxt->rc_reply_pcl))
		वापस xdr_stream_encode_item_असलent(&sctxt->sc_stream);

	chunk = pcl_first_chunk(&rctxt->rc_reply_pcl);
	अगर (length > chunk->ch_length)
		वापस -E2BIG;

	chunk->ch_payload_length = length;
	वापस svc_rdma_encode_ग_लिखो_chunk(sctxt, chunk);
पूर्ण

काष्ठा svc_rdma_map_data अणु
	काष्ठा svcxprt_rdma		*md_rdma;
	काष्ठा svc_rdma_send_ctxt	*md_ctxt;
पूर्ण;

/**
 * svc_rdma_page_dma_map - DMA map one page
 * @data: poपूर्णांकer to arguments
 * @page: काष्ठा page to DMA map
 * @offset: offset पूर्णांकo the page
 * @len: number of bytes to map
 *
 * Returns:
 *   %0 अगर DMA mapping was successful
 *   %-EIO अगर the page cannot be DMA mapped
 */
अटल पूर्णांक svc_rdma_page_dma_map(व्योम *data, काष्ठा page *page,
				 अचिन्हित दीर्घ offset, अचिन्हित पूर्णांक len)
अणु
	काष्ठा svc_rdma_map_data *args = data;
	काष्ठा svcxprt_rdma *rdma = args->md_rdma;
	काष्ठा svc_rdma_send_ctxt *ctxt = args->md_ctxt;
	काष्ठा ib_device *dev = rdma->sc_cm_id->device;
	dma_addr_t dma_addr;

	++ctxt->sc_cur_sge_no;

	dma_addr = ib_dma_map_page(dev, page, offset, len, DMA_TO_DEVICE);
	अगर (ib_dma_mapping_error(dev, dma_addr))
		जाओ out_maperr;

	trace_svcrdma_dma_map_page(rdma, dma_addr, len);
	ctxt->sc_sges[ctxt->sc_cur_sge_no].addr = dma_addr;
	ctxt->sc_sges[ctxt->sc_cur_sge_no].length = len;
	ctxt->sc_send_wr.num_sge++;
	वापस 0;

out_maperr:
	trace_svcrdma_dma_map_err(rdma, dma_addr, len);
	वापस -EIO;
पूर्ण

/**
 * svc_rdma_iov_dma_map - DMA map an iovec
 * @data: poपूर्णांकer to arguments
 * @iov: kvec to DMA map
 *
 * ib_dma_map_page() is used here because svc_rdma_dma_unmap()
 * handles DMA-unmap and it uses ib_dma_unmap_page() exclusively.
 *
 * Returns:
 *   %0 अगर DMA mapping was successful
 *   %-EIO अगर the iovec cannot be DMA mapped
 */
अटल पूर्णांक svc_rdma_iov_dma_map(व्योम *data, स्थिर काष्ठा kvec *iov)
अणु
	अगर (!iov->iov_len)
		वापस 0;
	वापस svc_rdma_page_dma_map(data, virt_to_page(iov->iov_base),
				     offset_in_page(iov->iov_base),
				     iov->iov_len);
पूर्ण

/**
 * svc_rdma_xb_dma_map - DMA map all segments of an xdr_buf
 * @xdr: xdr_buf containing portion of an RPC message to transmit
 * @data: poपूर्णांकer to arguments
 *
 * Returns:
 *   %0 अगर DMA mapping was successful
 *   %-EIO अगर DMA mapping failed
 *
 * On failure, any DMA mappings that have been alपढ़ोy करोne must be
 * unmapped by the caller.
 */
अटल पूर्णांक svc_rdma_xb_dma_map(स्थिर काष्ठा xdr_buf *xdr, व्योम *data)
अणु
	अचिन्हित पूर्णांक len, reमुख्यing;
	अचिन्हित दीर्घ pageoff;
	काष्ठा page **ppages;
	पूर्णांक ret;

	ret = svc_rdma_iov_dma_map(data, &xdr->head[0]);
	अगर (ret < 0)
		वापस ret;

	ppages = xdr->pages + (xdr->page_base >> PAGE_SHIFT);
	pageoff = offset_in_page(xdr->page_base);
	reमुख्यing = xdr->page_len;
	जबतक (reमुख्यing) अणु
		len = min_t(u32, PAGE_SIZE - pageoff, reमुख्यing);

		ret = svc_rdma_page_dma_map(data, *ppages++, pageoff, len);
		अगर (ret < 0)
			वापस ret;

		reमुख्यing -= len;
		pageoff = 0;
	पूर्ण

	ret = svc_rdma_iov_dma_map(data, &xdr->tail[0]);
	अगर (ret < 0)
		वापस ret;

	वापस xdr->len;
पूर्ण

काष्ठा svc_rdma_pullup_data अणु
	u8		*pd_dest;
	अचिन्हित पूर्णांक	pd_length;
	अचिन्हित पूर्णांक	pd_num_sges;
पूर्ण;

/**
 * svc_rdma_xb_count_sges - Count how many SGEs will be needed
 * @xdr: xdr_buf containing portion of an RPC message to transmit
 * @data: poपूर्णांकer to arguments
 *
 * Returns:
 *   Number of SGEs needed to Send the contents of @xdr अंतरभूत
 */
अटल पूर्णांक svc_rdma_xb_count_sges(स्थिर काष्ठा xdr_buf *xdr,
				  व्योम *data)
अणु
	काष्ठा svc_rdma_pullup_data *args = data;
	अचिन्हित पूर्णांक reमुख्यing;
	अचिन्हित दीर्घ offset;

	अगर (xdr->head[0].iov_len)
		++args->pd_num_sges;

	offset = offset_in_page(xdr->page_base);
	reमुख्यing = xdr->page_len;
	जबतक (reमुख्यing) अणु
		++args->pd_num_sges;
		reमुख्यing -= min_t(u32, PAGE_SIZE - offset, reमुख्यing);
		offset = 0;
	पूर्ण

	अगर (xdr->tail[0].iov_len)
		++args->pd_num_sges;

	args->pd_length += xdr->len;
	वापस 0;
पूर्ण

/**
 * svc_rdma_pull_up_needed - Determine whether to use pull-up
 * @rdma: controlling transport
 * @sctxt: send_ctxt क्रम the Send WR
 * @rctxt: Write and Reply chunks provided by client
 * @xdr: xdr_buf containing RPC message to transmit
 *
 * Returns:
 *   %true अगर pull-up must be used
 *   %false otherwise
 */
अटल bool svc_rdma_pull_up_needed(स्थिर काष्ठा svcxprt_rdma *rdma,
				    स्थिर काष्ठा svc_rdma_send_ctxt *sctxt,
				    स्थिर काष्ठा svc_rdma_recv_ctxt *rctxt,
				    स्थिर काष्ठा xdr_buf *xdr)
अणु
	/* Resources needed क्रम the transport header */
	काष्ठा svc_rdma_pullup_data args = अणु
		.pd_length	= sctxt->sc_hdrbuf.len,
		.pd_num_sges	= 1,
	पूर्ण;
	पूर्णांक ret;

	ret = pcl_process_nonpayloads(&rctxt->rc_ग_लिखो_pcl, xdr,
				      svc_rdma_xb_count_sges, &args);
	अगर (ret < 0)
		वापस false;

	अगर (args.pd_length < RPCRDMA_PULLUP_THRESH)
		वापस true;
	वापस args.pd_num_sges >= rdma->sc_max_send_sges;
पूर्ण

/**
 * svc_rdma_xb_linearize - Copy region of xdr_buf to flat buffer
 * @xdr: xdr_buf containing portion of an RPC message to copy
 * @data: poपूर्णांकer to arguments
 *
 * Returns:
 *   Always zero.
 */
अटल पूर्णांक svc_rdma_xb_linearize(स्थिर काष्ठा xdr_buf *xdr,
				 व्योम *data)
अणु
	काष्ठा svc_rdma_pullup_data *args = data;
	अचिन्हित पूर्णांक len, reमुख्यing;
	अचिन्हित दीर्घ pageoff;
	काष्ठा page **ppages;

	अगर (xdr->head[0].iov_len) अणु
		स_नकल(args->pd_dest, xdr->head[0].iov_base, xdr->head[0].iov_len);
		args->pd_dest += xdr->head[0].iov_len;
	पूर्ण

	ppages = xdr->pages + (xdr->page_base >> PAGE_SHIFT);
	pageoff = offset_in_page(xdr->page_base);
	reमुख्यing = xdr->page_len;
	जबतक (reमुख्यing) अणु
		len = min_t(u32, PAGE_SIZE - pageoff, reमुख्यing);
		स_नकल(args->pd_dest, page_address(*ppages) + pageoff, len);
		reमुख्यing -= len;
		args->pd_dest += len;
		pageoff = 0;
		ppages++;
	पूर्ण

	अगर (xdr->tail[0].iov_len) अणु
		स_नकल(args->pd_dest, xdr->tail[0].iov_base, xdr->tail[0].iov_len);
		args->pd_dest += xdr->tail[0].iov_len;
	पूर्ण

	args->pd_length += xdr->len;
	वापस 0;
पूर्ण

/**
 * svc_rdma_pull_up_reply_msg - Copy Reply पूर्णांकo a single buffer
 * @rdma: controlling transport
 * @sctxt: send_ctxt क्रम the Send WR; xprt hdr is alपढ़ोy prepared
 * @rctxt: Write and Reply chunks provided by client
 * @xdr: prepared xdr_buf containing RPC message
 *
 * The device is not capable of sending the reply directly.
 * Assemble the elements of @xdr पूर्णांकo the transport header buffer.
 *
 * Assumptions:
 *  pull_up_needed has determined that @xdr will fit in the buffer.
 *
 * Returns:
 *   %0 अगर pull-up was successful
 *   %-EMSGSIZE अगर a buffer manipulation problem occurred
 */
अटल पूर्णांक svc_rdma_pull_up_reply_msg(स्थिर काष्ठा svcxprt_rdma *rdma,
				      काष्ठा svc_rdma_send_ctxt *sctxt,
				      स्थिर काष्ठा svc_rdma_recv_ctxt *rctxt,
				      स्थिर काष्ठा xdr_buf *xdr)
अणु
	काष्ठा svc_rdma_pullup_data args = अणु
		.pd_dest	= sctxt->sc_xprt_buf + sctxt->sc_hdrbuf.len,
	पूर्ण;
	पूर्णांक ret;

	ret = pcl_process_nonpayloads(&rctxt->rc_ग_लिखो_pcl, xdr,
				      svc_rdma_xb_linearize, &args);
	अगर (ret < 0)
		वापस ret;

	sctxt->sc_sges[0].length = sctxt->sc_hdrbuf.len + args.pd_length;
	trace_svcrdma_send_pullup(sctxt, args.pd_length);
	वापस 0;
पूर्ण

/* svc_rdma_map_reply_msg - DMA map the buffer holding RPC message
 * @rdma: controlling transport
 * @sctxt: send_ctxt क्रम the Send WR
 * @rctxt: Write and Reply chunks provided by client
 * @xdr: prepared xdr_buf containing RPC message
 *
 * Returns:
 *   %0 अगर DMA mapping was successful.
 *   %-EMSGSIZE अगर a buffer manipulation problem occurred
 *   %-EIO अगर DMA mapping failed
 *
 * The Send WR's num_sge field is set in all हालs.
 */
पूर्णांक svc_rdma_map_reply_msg(काष्ठा svcxprt_rdma *rdma,
			   काष्ठा svc_rdma_send_ctxt *sctxt,
			   स्थिर काष्ठा svc_rdma_recv_ctxt *rctxt,
			   स्थिर काष्ठा xdr_buf *xdr)
अणु
	काष्ठा svc_rdma_map_data args = अणु
		.md_rdma	= rdma,
		.md_ctxt	= sctxt,
	पूर्ण;

	/* Set up the (persistently-mapped) transport header SGE. */
	sctxt->sc_send_wr.num_sge = 1;
	sctxt->sc_sges[0].length = sctxt->sc_hdrbuf.len;

	/* If there is a Reply chunk, nothing follows the transport
	 * header, and we're करोne here.
	 */
	अगर (!pcl_is_empty(&rctxt->rc_reply_pcl))
		वापस 0;

	/* For pull-up, svc_rdma_send() will sync the transport header.
	 * No additional DMA mapping is necessary.
	 */
	अगर (svc_rdma_pull_up_needed(rdma, sctxt, rctxt, xdr))
		वापस svc_rdma_pull_up_reply_msg(rdma, sctxt, rctxt, xdr);

	वापस pcl_process_nonpayloads(&rctxt->rc_ग_लिखो_pcl, xdr,
				       svc_rdma_xb_dma_map, &args);
पूर्ण

/* Prepare the portion of the RPC Reply that will be transmitted
 * via RDMA Send. The RPC-over-RDMA transport header is prepared
 * in sc_sges[0], and the RPC xdr_buf is prepared in following sges.
 *
 * Depending on whether a Write list or Reply chunk is present,
 * the server may send all, a portion of, or none of the xdr_buf.
 * In the latter हाल, only the transport header (sc_sges[0]) is
 * transmitted.
 *
 * RDMA Send is the last step of transmitting an RPC reply. Pages
 * involved in the earlier RDMA Writes are here transferred out
 * of the rqstp and पूर्णांकo the sctxt's page array. These pages are
 * DMA unmapped by each Write completion, but the subsequent Send
 * completion finally releases these pages.
 *
 * Assumptions:
 * - The Reply's transport header will never be larger than a page.
 */
अटल पूर्णांक svc_rdma_send_reply_msg(काष्ठा svcxprt_rdma *rdma,
				   काष्ठा svc_rdma_send_ctxt *sctxt,
				   स्थिर काष्ठा svc_rdma_recv_ctxt *rctxt,
				   काष्ठा svc_rqst *rqstp)
अणु
	पूर्णांक ret;

	ret = svc_rdma_map_reply_msg(rdma, sctxt, rctxt, &rqstp->rq_res);
	अगर (ret < 0)
		वापस ret;

	अगर (rctxt->rc_inv_rkey) अणु
		sctxt->sc_send_wr.opcode = IB_WR_SEND_WITH_INV;
		sctxt->sc_send_wr.ex.invalidate_rkey = rctxt->rc_inv_rkey;
	पूर्ण अन्यथा अणु
		sctxt->sc_send_wr.opcode = IB_WR_SEND;
	पूर्ण

	ret = svc_rdma_send(rdma, sctxt);
	अगर (ret < 0)
		वापस ret;

	ret = रुको_क्रम_completion_समाप्तable(&sctxt->sc_करोne);
	svc_rdma_send_ctxt_put(rdma, sctxt);
	वापस ret;
पूर्ण

/**
 * svc_rdma_send_error_msg - Send an RPC/RDMA v1 error response
 * @rdma: controlling transport context
 * @sctxt: Send context क्रम the response
 * @rctxt: Receive context क्रम incoming bad message
 * @status: negative त्रुटि_सं indicating error that occurred
 *
 * Given the client-provided Read, Write, and Reply chunks, the
 * server was not able to parse the Call or क्रमm a complete Reply.
 * Return an RDMA_ERROR message so the client can retire the RPC
 * transaction.
 *
 * The caller करोes not have to release @sctxt. It is released by
 * Send completion, or by this function on error.
 */
व्योम svc_rdma_send_error_msg(काष्ठा svcxprt_rdma *rdma,
			     काष्ठा svc_rdma_send_ctxt *sctxt,
			     काष्ठा svc_rdma_recv_ctxt *rctxt,
			     पूर्णांक status)
अणु
	__be32 *rdma_argp = rctxt->rc_recv_buf;
	__be32 *p;

	rpcrdma_set_xdrlen(&sctxt->sc_hdrbuf, 0);
	xdr_init_encode(&sctxt->sc_stream, &sctxt->sc_hdrbuf,
			sctxt->sc_xprt_buf, शून्य);

	p = xdr_reserve_space(&sctxt->sc_stream,
			      rpcrdma_fixed_maxsz * माप(*p));
	अगर (!p)
		जाओ put_ctxt;

	*p++ = *rdma_argp;
	*p++ = *(rdma_argp + 1);
	*p++ = rdma->sc_fc_credits;
	*p = rdma_error;

	चयन (status) अणु
	हाल -EPROTONOSUPPORT:
		p = xdr_reserve_space(&sctxt->sc_stream, 3 * माप(*p));
		अगर (!p)
			जाओ put_ctxt;

		*p++ = err_vers;
		*p++ = rpcrdma_version;
		*p = rpcrdma_version;
		trace_svcrdma_err_vers(*rdma_argp);
		अवरोध;
	शेष:
		p = xdr_reserve_space(&sctxt->sc_stream, माप(*p));
		अगर (!p)
			जाओ put_ctxt;

		*p = err_chunk;
		trace_svcrdma_err_chunk(*rdma_argp);
	पूर्ण

	/* Remote Invalidation is skipped क्रम simplicity. */
	sctxt->sc_send_wr.num_sge = 1;
	sctxt->sc_send_wr.opcode = IB_WR_SEND;
	sctxt->sc_sges[0].length = sctxt->sc_hdrbuf.len;
	अगर (svc_rdma_send(rdma, sctxt))
		जाओ put_ctxt;

	रुको_क्रम_completion_समाप्तable(&sctxt->sc_करोne);

put_ctxt:
	svc_rdma_send_ctxt_put(rdma, sctxt);
पूर्ण

/**
 * svc_rdma_sendto - Transmit an RPC reply
 * @rqstp: processed RPC request, reply XDR alपढ़ोy in ::rq_res
 *
 * Any resources still associated with @rqstp are released upon वापस.
 * If no reply message was possible, the connection is बंदd.
 *
 * Returns:
 *	%0 अगर an RPC reply has been successfully posted,
 *	%-ENOMEM अगर a resource लघुage occurred (connection is lost),
 *	%-ENOTCONN अगर posting failed (connection is lost).
 */
पूर्णांक svc_rdma_sendto(काष्ठा svc_rqst *rqstp)
अणु
	काष्ठा svc_xprt *xprt = rqstp->rq_xprt;
	काष्ठा svcxprt_rdma *rdma =
		container_of(xprt, काष्ठा svcxprt_rdma, sc_xprt);
	काष्ठा svc_rdma_recv_ctxt *rctxt = rqstp->rq_xprt_ctxt;
	__be32 *rdma_argp = rctxt->rc_recv_buf;
	काष्ठा svc_rdma_send_ctxt *sctxt;
	अचिन्हित पूर्णांक rc_size;
	__be32 *p;
	पूर्णांक ret;

	ret = -ENOTCONN;
	अगर (svc_xprt_is_dead(xprt))
		जाओ drop_connection;

	ret = -ENOMEM;
	sctxt = svc_rdma_send_ctxt_get(rdma);
	अगर (!sctxt)
		जाओ drop_connection;

	ret = -EMSGSIZE;
	p = xdr_reserve_space(&sctxt->sc_stream,
			      rpcrdma_fixed_maxsz * माप(*p));
	अगर (!p)
		जाओ put_ctxt;

	ret = svc_rdma_send_reply_chunk(rdma, rctxt, &rqstp->rq_res);
	अगर (ret < 0)
		जाओ reply_chunk;
	rc_size = ret;

	*p++ = *rdma_argp;
	*p++ = *(rdma_argp + 1);
	*p++ = rdma->sc_fc_credits;
	*p = pcl_is_empty(&rctxt->rc_reply_pcl) ? rdma_msg : rdma_nomsg;

	ret = svc_rdma_encode_पढ़ो_list(sctxt);
	अगर (ret < 0)
		जाओ put_ctxt;
	ret = svc_rdma_encode_ग_लिखो_list(rctxt, sctxt);
	अगर (ret < 0)
		जाओ put_ctxt;
	ret = svc_rdma_encode_reply_chunk(rctxt, sctxt, rc_size);
	अगर (ret < 0)
		जाओ put_ctxt;

	ret = svc_rdma_send_reply_msg(rdma, sctxt, rctxt, rqstp);
	अगर (ret < 0)
		जाओ put_ctxt;

	/* Prevent svc_xprt_release() from releasing the page backing
	 * rq_res.head[0].iov_base. It's no दीर्घer being accessed by
	 * the I/O device. */
	rqstp->rq_respages++;
	वापस 0;

reply_chunk:
	अगर (ret != -E2BIG && ret != -EINVAL)
		जाओ put_ctxt;

	svc_rdma_send_error_msg(rdma, sctxt, rctxt, ret);
	वापस 0;

put_ctxt:
	svc_rdma_send_ctxt_put(rdma, sctxt);
drop_connection:
	trace_svcrdma_send_err(rqstp, ret);
	svc_xprt_deferred_बंद(&rdma->sc_xprt);
	वापस -ENOTCONN;
पूर्ण

/**
 * svc_rdma_result_payload - special processing क्रम a result payload
 * @rqstp: svc_rqst to operate on
 * @offset: payload's byte offset in @xdr
 * @length: size of payload, in bytes
 *
 * Return values:
 *   %0 अगर successful or nothing needed to be करोne
 *   %-EMSGSIZE on XDR buffer overflow
 *   %-E2BIG अगर the payload was larger than the Write chunk
 *   %-EINVAL अगर client provided too many segments
 *   %-ENOMEM अगर rdma_rw context pool was exhausted
 *   %-ENOTCONN अगर posting failed (connection is lost)
 *   %-EIO अगर rdma_rw initialization failed (DMA mapping, etc)
 */
पूर्णांक svc_rdma_result_payload(काष्ठा svc_rqst *rqstp, अचिन्हित पूर्णांक offset,
			    अचिन्हित पूर्णांक length)
अणु
	काष्ठा svc_rdma_recv_ctxt *rctxt = rqstp->rq_xprt_ctxt;
	काष्ठा svc_rdma_chunk *chunk;
	काष्ठा svcxprt_rdma *rdma;
	काष्ठा xdr_buf subbuf;
	पूर्णांक ret;

	chunk = rctxt->rc_cur_result_payload;
	अगर (!length || !chunk)
		वापस 0;
	rctxt->rc_cur_result_payload =
		pcl_next_chunk(&rctxt->rc_ग_लिखो_pcl, chunk);
	अगर (length > chunk->ch_length)
		वापस -E2BIG;

	chunk->ch_position = offset;
	chunk->ch_payload_length = length;

	अगर (xdr_buf_subsegment(&rqstp->rq_res, &subbuf, offset, length))
		वापस -EMSGSIZE;

	rdma = container_of(rqstp->rq_xprt, काष्ठा svcxprt_rdma, sc_xprt);
	ret = svc_rdma_send_ग_लिखो_chunk(rdma, chunk, &subbuf);
	अगर (ret < 0)
		वापस ret;
	वापस 0;
पूर्ण
