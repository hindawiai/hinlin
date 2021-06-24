<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2016-2018 Oracle.  All rights reserved.
 *
 * Use the core R/W API to move RPC-over-RDMA Read and Write chunks.
 */

#समावेश <rdma/rw.h>

#समावेश <linux/sunrpc/xdr.h>
#समावेश <linux/sunrpc/rpc_rdma.h>
#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

अटल व्योम svc_rdma_ग_लिखो_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);
अटल व्योम svc_rdma_wc_पढ़ो_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc);

/* Each R/W context contains state क्रम one chain of RDMA Read or
 * Write Work Requests.
 *
 * Each WR chain handles a single contiguous server-side buffer,
 * because scatterlist entries after the first have to start on
 * page alignment. xdr_buf iovecs cannot guarantee alignment.
 *
 * Each WR chain handles only one R_key. Each RPC-over-RDMA segment
 * from a client may contain a unique R_key, so each WR chain moves
 * up to one segment at a समय.
 *
 * The scatterlist makes this data काष्ठाure over 4KB in size. To
 * make it less likely to fail, and to handle the allocation क्रम
 * smaller I/O requests without disabling bottom-halves, these
 * contexts are created on demand, but cached and reused until the
 * controlling svcxprt_rdma is destroyed.
 */
काष्ठा svc_rdma_rw_ctxt अणु
	काष्ठा list_head	rw_list;
	काष्ठा rdma_rw_ctx	rw_ctx;
	अचिन्हित पूर्णांक		rw_nents;
	काष्ठा sg_table		rw_sg_table;
	काष्ठा scatterlist	rw_first_sgl[];
पूर्ण;

अटल अंतरभूत काष्ठा svc_rdma_rw_ctxt *
svc_rdma_next_ctxt(काष्ठा list_head *list)
अणु
	वापस list_first_entry_or_null(list, काष्ठा svc_rdma_rw_ctxt,
					rw_list);
पूर्ण

अटल काष्ठा svc_rdma_rw_ctxt *
svc_rdma_get_rw_ctxt(काष्ठा svcxprt_rdma *rdma, अचिन्हित पूर्णांक sges)
अणु
	काष्ठा svc_rdma_rw_ctxt *ctxt;

	spin_lock(&rdma->sc_rw_ctxt_lock);

	ctxt = svc_rdma_next_ctxt(&rdma->sc_rw_ctxts);
	अगर (ctxt) अणु
		list_del(&ctxt->rw_list);
		spin_unlock(&rdma->sc_rw_ctxt_lock);
	पूर्ण अन्यथा अणु
		spin_unlock(&rdma->sc_rw_ctxt_lock);
		ctxt = kदो_स्मृति(काष्ठा_size(ctxt, rw_first_sgl, SG_CHUNK_SIZE),
			       GFP_KERNEL);
		अगर (!ctxt)
			जाओ out_noctx;
		INIT_LIST_HEAD(&ctxt->rw_list);
	पूर्ण

	ctxt->rw_sg_table.sgl = ctxt->rw_first_sgl;
	अगर (sg_alloc_table_chained(&ctxt->rw_sg_table, sges,
				   ctxt->rw_sg_table.sgl,
				   SG_CHUNK_SIZE))
		जाओ out_मुक्त;
	वापस ctxt;

out_मुक्त:
	kमुक्त(ctxt);
out_noctx:
	trace_svcrdma_no_rwctx_err(rdma, sges);
	वापस शून्य;
पूर्ण

अटल व्योम svc_rdma_put_rw_ctxt(काष्ठा svcxprt_rdma *rdma,
				 काष्ठा svc_rdma_rw_ctxt *ctxt)
अणु
	sg_मुक्त_table_chained(&ctxt->rw_sg_table, SG_CHUNK_SIZE);

	spin_lock(&rdma->sc_rw_ctxt_lock);
	list_add(&ctxt->rw_list, &rdma->sc_rw_ctxts);
	spin_unlock(&rdma->sc_rw_ctxt_lock);
पूर्ण

/**
 * svc_rdma_destroy_rw_ctxts - Free accumulated R/W contexts
 * @rdma: transport about to be destroyed
 *
 */
व्योम svc_rdma_destroy_rw_ctxts(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_rw_ctxt *ctxt;

	जबतक ((ctxt = svc_rdma_next_ctxt(&rdma->sc_rw_ctxts)) != शून्य) अणु
		list_del(&ctxt->rw_list);
		kमुक्त(ctxt);
	पूर्ण
पूर्ण

/**
 * svc_rdma_rw_ctx_init - Prepare a R/W context क्रम I/O
 * @rdma: controlling transport instance
 * @ctxt: R/W context to prepare
 * @offset: RDMA offset
 * @handle: RDMA tag/handle
 * @direction: I/O direction
 *
 * Returns on success, the number of WQEs that will be needed
 * on the workqueue, or a negative त्रुटि_सं.
 */
अटल पूर्णांक svc_rdma_rw_ctx_init(काष्ठा svcxprt_rdma *rdma,
				काष्ठा svc_rdma_rw_ctxt *ctxt,
				u64 offset, u32 handle,
				क्रमागत dma_data_direction direction)
अणु
	पूर्णांक ret;

	ret = rdma_rw_ctx_init(&ctxt->rw_ctx, rdma->sc_qp, rdma->sc_port_num,
			       ctxt->rw_sg_table.sgl, ctxt->rw_nents,
			       0, offset, handle, direction);
	अगर (unlikely(ret < 0)) अणु
		svc_rdma_put_rw_ctxt(rdma, ctxt);
		trace_svcrdma_dma_map_rw_err(rdma, ctxt->rw_nents, ret);
	पूर्ण
	वापस ret;
पूर्ण

/* A chunk context tracks all I/O क्रम moving one Read or Write
 * chunk. This is a set of rdma_rw's that handle data movement
 * क्रम all segments of one chunk.
 *
 * These are small, acquired with a single allocator call, and
 * no more than one is needed per chunk. They are allocated on
 * demand, and not cached.
 */
काष्ठा svc_rdma_chunk_ctxt अणु
	काष्ठा rpc_rdma_cid	cc_cid;
	काष्ठा ib_cqe		cc_cqe;
	काष्ठा svcxprt_rdma	*cc_rdma;
	काष्ठा list_head	cc_rwctxts;
	पूर्णांक			cc_sqecount;
	क्रमागत ib_wc_status	cc_status;
	काष्ठा completion	cc_करोne;
पूर्ण;

अटल व्योम svc_rdma_cc_cid_init(काष्ठा svcxprt_rdma *rdma,
				 काष्ठा rpc_rdma_cid *cid)
अणु
	cid->ci_queue_id = rdma->sc_sq_cq->res.id;
	cid->ci_completion_id = atomic_inc_वापस(&rdma->sc_completion_ids);
पूर्ण

अटल व्योम svc_rdma_cc_init(काष्ठा svcxprt_rdma *rdma,
			     काष्ठा svc_rdma_chunk_ctxt *cc)
अणु
	svc_rdma_cc_cid_init(rdma, &cc->cc_cid);
	cc->cc_rdma = rdma;

	INIT_LIST_HEAD(&cc->cc_rwctxts);
	cc->cc_sqecount = 0;
पूर्ण

अटल व्योम svc_rdma_cc_release(काष्ठा svc_rdma_chunk_ctxt *cc,
				क्रमागत dma_data_direction dir)
अणु
	काष्ठा svcxprt_rdma *rdma = cc->cc_rdma;
	काष्ठा svc_rdma_rw_ctxt *ctxt;

	जबतक ((ctxt = svc_rdma_next_ctxt(&cc->cc_rwctxts)) != शून्य) अणु
		list_del(&ctxt->rw_list);

		rdma_rw_ctx_destroy(&ctxt->rw_ctx, rdma->sc_qp,
				    rdma->sc_port_num, ctxt->rw_sg_table.sgl,
				    ctxt->rw_nents, dir);
		svc_rdma_put_rw_ctxt(rdma, ctxt);
	पूर्ण
पूर्ण

/* State क्रम sending a Write or Reply chunk.
 *  - Tracks progress of writing one chunk over all its segments
 *  - Stores arguments क्रम the SGL स्थिरructor functions
 */
काष्ठा svc_rdma_ग_लिखो_info अणु
	स्थिर काष्ठा svc_rdma_chunk	*wi_chunk;

	/* ग_लिखो state of this chunk */
	अचिन्हित पूर्णांक		wi_seg_off;
	अचिन्हित पूर्णांक		wi_seg_no;

	/* SGL स्थिरructor arguments */
	स्थिर काष्ठा xdr_buf	*wi_xdr;
	अचिन्हित अक्षर		*wi_base;
	अचिन्हित पूर्णांक		wi_next_off;

	काष्ठा svc_rdma_chunk_ctxt	wi_cc;
पूर्ण;

अटल काष्ठा svc_rdma_ग_लिखो_info *
svc_rdma_ग_लिखो_info_alloc(काष्ठा svcxprt_rdma *rdma,
			  स्थिर काष्ठा svc_rdma_chunk *chunk)
अणु
	काष्ठा svc_rdma_ग_लिखो_info *info;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस info;

	info->wi_chunk = chunk;
	info->wi_seg_off = 0;
	info->wi_seg_no = 0;
	svc_rdma_cc_init(rdma, &info->wi_cc);
	info->wi_cc.cc_cqe.करोne = svc_rdma_ग_लिखो_करोne;
	वापस info;
पूर्ण

अटल व्योम svc_rdma_ग_लिखो_info_मुक्त(काष्ठा svc_rdma_ग_लिखो_info *info)
अणु
	svc_rdma_cc_release(&info->wi_cc, DMA_TO_DEVICE);
	kमुक्त(info);
पूर्ण

/**
 * svc_rdma_ग_लिखो_करोne - Write chunk completion
 * @cq: controlling Completion Queue
 * @wc: Work Completion
 *
 * Pages under I/O are मुक्तd by a subsequent Send completion.
 */
अटल व्योम svc_rdma_ग_लिखो_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा svc_rdma_chunk_ctxt *cc =
			container_of(cqe, काष्ठा svc_rdma_chunk_ctxt, cc_cqe);
	काष्ठा svcxprt_rdma *rdma = cc->cc_rdma;
	काष्ठा svc_rdma_ग_लिखो_info *info =
			container_of(cc, काष्ठा svc_rdma_ग_लिखो_info, wi_cc);

	trace_svcrdma_wc_ग_लिखो(wc, &cc->cc_cid);

	atomic_add(cc->cc_sqecount, &rdma->sc_sq_avail);
	wake_up(&rdma->sc_send_रुको);

	अगर (unlikely(wc->status != IB_WC_SUCCESS))
		svc_xprt_deferred_बंद(&rdma->sc_xprt);

	svc_rdma_ग_लिखो_info_मुक्त(info);
पूर्ण

/* State क्रम pulling a Read chunk.
 */
काष्ठा svc_rdma_पढ़ो_info अणु
	काष्ठा svc_rqst			*ri_rqst;
	काष्ठा svc_rdma_recv_ctxt	*ri_पढ़ोctxt;
	अचिन्हित पूर्णांक			ri_pageno;
	अचिन्हित पूर्णांक			ri_pageoff;
	अचिन्हित पूर्णांक			ri_totalbytes;

	काष्ठा svc_rdma_chunk_ctxt	ri_cc;
पूर्ण;

अटल काष्ठा svc_rdma_पढ़ो_info *
svc_rdma_पढ़ो_info_alloc(काष्ठा svcxprt_rdma *rdma)
अणु
	काष्ठा svc_rdma_पढ़ो_info *info;

	info = kदो_स्मृति(माप(*info), GFP_KERNEL);
	अगर (!info)
		वापस info;

	svc_rdma_cc_init(rdma, &info->ri_cc);
	info->ri_cc.cc_cqe.करोne = svc_rdma_wc_पढ़ो_करोne;
	वापस info;
पूर्ण

अटल व्योम svc_rdma_पढ़ो_info_मुक्त(काष्ठा svc_rdma_पढ़ो_info *info)
अणु
	svc_rdma_cc_release(&info->ri_cc, DMA_FROM_DEVICE);
	kमुक्त(info);
पूर्ण

/**
 * svc_rdma_wc_पढ़ो_करोne - Handle completion of an RDMA Read ctx
 * @cq: controlling Completion Queue
 * @wc: Work Completion
 *
 */
अटल व्योम svc_rdma_wc_पढ़ो_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा svc_rdma_chunk_ctxt *cc =
			container_of(cqe, काष्ठा svc_rdma_chunk_ctxt, cc_cqe);
	काष्ठा svcxprt_rdma *rdma = cc->cc_rdma;

	trace_svcrdma_wc_पढ़ो(wc, &cc->cc_cid);

	atomic_add(cc->cc_sqecount, &rdma->sc_sq_avail);
	wake_up(&rdma->sc_send_रुको);

	cc->cc_status = wc->status;
	complete(&cc->cc_करोne);
	वापस;
पूर्ण

/* This function sleeps when the transport's Send Queue is congested.
 *
 * Assumptions:
 * - If ib_post_send() succeeds, only one completion is expected,
 *   even अगर one or more WRs are flushed. This is true when posting
 *   an rdma_rw_ctx or when posting a single संकेतed WR.
 */
अटल पूर्णांक svc_rdma_post_chunk_ctxt(काष्ठा svc_rdma_chunk_ctxt *cc)
अणु
	काष्ठा svcxprt_rdma *rdma = cc->cc_rdma;
	काष्ठा ib_send_wr *first_wr;
	स्थिर काष्ठा ib_send_wr *bad_wr;
	काष्ठा list_head *पंचांगp;
	काष्ठा ib_cqe *cqe;
	पूर्णांक ret;

	अगर (cc->cc_sqecount > rdma->sc_sq_depth)
		वापस -EINVAL;

	first_wr = शून्य;
	cqe = &cc->cc_cqe;
	list_क्रम_each(पंचांगp, &cc->cc_rwctxts) अणु
		काष्ठा svc_rdma_rw_ctxt *ctxt;

		ctxt = list_entry(पंचांगp, काष्ठा svc_rdma_rw_ctxt, rw_list);
		first_wr = rdma_rw_ctx_wrs(&ctxt->rw_ctx, rdma->sc_qp,
					   rdma->sc_port_num, cqe, first_wr);
		cqe = शून्य;
	पूर्ण

	करो अणु
		अगर (atomic_sub_वापस(cc->cc_sqecount,
				      &rdma->sc_sq_avail) > 0) अणु
			ret = ib_post_send(rdma->sc_qp, first_wr, &bad_wr);
			अगर (ret)
				अवरोध;
			वापस 0;
		पूर्ण

		percpu_counter_inc(&svcrdma_stat_sq_starve);
		trace_svcrdma_sq_full(rdma);
		atomic_add(cc->cc_sqecount, &rdma->sc_sq_avail);
		रुको_event(rdma->sc_send_रुको,
			   atomic_पढ़ो(&rdma->sc_sq_avail) > cc->cc_sqecount);
		trace_svcrdma_sq_retry(rdma);
	पूर्ण जबतक (1);

	trace_svcrdma_sq_post_err(rdma, ret);
	svc_xprt_deferred_बंद(&rdma->sc_xprt);

	/* If even one was posted, there will be a completion. */
	अगर (bad_wr != first_wr)
		वापस 0;

	atomic_add(cc->cc_sqecount, &rdma->sc_sq_avail);
	wake_up(&rdma->sc_send_रुको);
	वापस -ENOTCONN;
पूर्ण

/* Build and DMA-map an SGL that covers one kvec in an xdr_buf
 */
अटल व्योम svc_rdma_vec_to_sg(काष्ठा svc_rdma_ग_लिखो_info *info,
			       अचिन्हित पूर्णांक len,
			       काष्ठा svc_rdma_rw_ctxt *ctxt)
अणु
	काष्ठा scatterlist *sg = ctxt->rw_sg_table.sgl;

	sg_set_buf(&sg[0], info->wi_base, len);
	info->wi_base += len;

	ctxt->rw_nents = 1;
पूर्ण

/* Build and DMA-map an SGL that covers part of an xdr_buf's pagelist.
 */
अटल व्योम svc_rdma_pagelist_to_sg(काष्ठा svc_rdma_ग_लिखो_info *info,
				    अचिन्हित पूर्णांक reमुख्यing,
				    काष्ठा svc_rdma_rw_ctxt *ctxt)
अणु
	अचिन्हित पूर्णांक sge_no, sge_bytes, page_off, page_no;
	स्थिर काष्ठा xdr_buf *xdr = info->wi_xdr;
	काष्ठा scatterlist *sg;
	काष्ठा page **page;

	page_off = info->wi_next_off + xdr->page_base;
	page_no = page_off >> PAGE_SHIFT;
	page_off = offset_in_page(page_off);
	page = xdr->pages + page_no;
	info->wi_next_off += reमुख्यing;
	sg = ctxt->rw_sg_table.sgl;
	sge_no = 0;
	करो अणु
		sge_bytes = min_t(अचिन्हित पूर्णांक, reमुख्यing,
				  PAGE_SIZE - page_off);
		sg_set_page(sg, *page, sge_bytes, page_off);

		reमुख्यing -= sge_bytes;
		sg = sg_next(sg);
		page_off = 0;
		sge_no++;
		page++;
	पूर्ण जबतक (reमुख्यing);

	ctxt->rw_nents = sge_no;
पूर्ण

/* Conकाष्ठा RDMA Write WRs to send a portion of an xdr_buf containing
 * an RPC Reply.
 */
अटल पूर्णांक
svc_rdma_build_ग_लिखोs(काष्ठा svc_rdma_ग_लिखो_info *info,
		      व्योम (*स्थिरructor)(काष्ठा svc_rdma_ग_लिखो_info *info,
					  अचिन्हित पूर्णांक len,
					  काष्ठा svc_rdma_rw_ctxt *ctxt),
		      अचिन्हित पूर्णांक reमुख्यing)
अणु
	काष्ठा svc_rdma_chunk_ctxt *cc = &info->wi_cc;
	काष्ठा svcxprt_rdma *rdma = cc->cc_rdma;
	स्थिर काष्ठा svc_rdma_segment *seg;
	काष्ठा svc_rdma_rw_ctxt *ctxt;
	पूर्णांक ret;

	करो अणु
		अचिन्हित पूर्णांक ग_लिखो_len;
		u64 offset;

		seg = &info->wi_chunk->ch_segments[info->wi_seg_no];
		अगर (!seg)
			जाओ out_overflow;

		ग_लिखो_len = min(reमुख्यing, seg->rs_length - info->wi_seg_off);
		अगर (!ग_लिखो_len)
			जाओ out_overflow;
		ctxt = svc_rdma_get_rw_ctxt(rdma,
					    (ग_लिखो_len >> PAGE_SHIFT) + 2);
		अगर (!ctxt)
			वापस -ENOMEM;

		स्थिरructor(info, ग_लिखो_len, ctxt);
		offset = seg->rs_offset + info->wi_seg_off;
		ret = svc_rdma_rw_ctx_init(rdma, ctxt, offset, seg->rs_handle,
					   DMA_TO_DEVICE);
		अगर (ret < 0)
			वापस -EIO;
		percpu_counter_inc(&svcrdma_stat_ग_लिखो);

		list_add(&ctxt->rw_list, &cc->cc_rwctxts);
		cc->cc_sqecount += ret;
		अगर (ग_लिखो_len == seg->rs_length - info->wi_seg_off) अणु
			info->wi_seg_no++;
			info->wi_seg_off = 0;
		पूर्ण अन्यथा अणु
			info->wi_seg_off += ग_लिखो_len;
		पूर्ण
		reमुख्यing -= ग_लिखो_len;
	पूर्ण जबतक (reमुख्यing);

	वापस 0;

out_overflow:
	trace_svcrdma_small_wrch_err(rdma, reमुख्यing, info->wi_seg_no,
				     info->wi_chunk->ch_segcount);
	वापस -E2BIG;
पूर्ण

/**
 * svc_rdma_iov_ग_लिखो - Conकाष्ठा RDMA Writes from an iov
 * @info: poपूर्णांकer to ग_लिखो arguments
 * @iov: kvec to ग_लिखो
 *
 * Returns:
 *   On succes, वापसs zero
 *   %-E2BIG अगर the client-provided Write chunk is too small
 *   %-ENOMEM अगर a resource has been exhausted
 *   %-EIO अगर an rdma-rw error occurred
 */
अटल पूर्णांक svc_rdma_iov_ग_लिखो(काष्ठा svc_rdma_ग_लिखो_info *info,
			      स्थिर काष्ठा kvec *iov)
अणु
	info->wi_base = iov->iov_base;
	वापस svc_rdma_build_ग_लिखोs(info, svc_rdma_vec_to_sg,
				     iov->iov_len);
पूर्ण

/**
 * svc_rdma_pages_ग_लिखो - Conकाष्ठा RDMA Writes from pages
 * @info: poपूर्णांकer to ग_लिखो arguments
 * @xdr: xdr_buf with pages to ग_लिखो
 * @offset: offset पूर्णांकo the content of @xdr
 * @length: number of bytes to ग_लिखो
 *
 * Returns:
 *   On succes, वापसs zero
 *   %-E2BIG अगर the client-provided Write chunk is too small
 *   %-ENOMEM अगर a resource has been exhausted
 *   %-EIO अगर an rdma-rw error occurred
 */
अटल पूर्णांक svc_rdma_pages_ग_लिखो(काष्ठा svc_rdma_ग_लिखो_info *info,
				स्थिर काष्ठा xdr_buf *xdr,
				अचिन्हित पूर्णांक offset,
				अचिन्हित दीर्घ length)
अणु
	info->wi_xdr = xdr;
	info->wi_next_off = offset - xdr->head[0].iov_len;
	वापस svc_rdma_build_ग_लिखोs(info, svc_rdma_pagelist_to_sg,
				     length);
पूर्ण

/**
 * svc_rdma_xb_ग_लिखो - Conकाष्ठा RDMA Writes to ग_लिखो an xdr_buf
 * @xdr: xdr_buf to ग_लिखो
 * @data: poपूर्णांकer to ग_लिखो arguments
 *
 * Returns:
 *   On succes, वापसs zero
 *   %-E2BIG अगर the client-provided Write chunk is too small
 *   %-ENOMEM अगर a resource has been exhausted
 *   %-EIO अगर an rdma-rw error occurred
 */
अटल पूर्णांक svc_rdma_xb_ग_लिखो(स्थिर काष्ठा xdr_buf *xdr, व्योम *data)
अणु
	काष्ठा svc_rdma_ग_लिखो_info *info = data;
	पूर्णांक ret;

	अगर (xdr->head[0].iov_len) अणु
		ret = svc_rdma_iov_ग_लिखो(info, &xdr->head[0]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (xdr->page_len) अणु
		ret = svc_rdma_pages_ग_लिखो(info, xdr, xdr->head[0].iov_len,
					   xdr->page_len);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	अगर (xdr->tail[0].iov_len) अणु
		ret = svc_rdma_iov_ग_लिखो(info, &xdr->tail[0]);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	वापस xdr->len;
पूर्ण

/**
 * svc_rdma_send_ग_लिखो_chunk - Write all segments in a Write chunk
 * @rdma: controlling RDMA transport
 * @chunk: Write chunk provided by the client
 * @xdr: xdr_buf containing the data payload
 *
 * Returns a non-negative number of bytes the chunk consumed, or
 *	%-E2BIG अगर the payload was larger than the Write chunk,
 *	%-EINVAL अगर client provided too many segments,
 *	%-ENOMEM अगर rdma_rw context pool was exhausted,
 *	%-ENOTCONN अगर posting failed (connection is lost),
 *	%-EIO अगर rdma_rw initialization failed (DMA mapping, etc).
 */
पूर्णांक svc_rdma_send_ग_लिखो_chunk(काष्ठा svcxprt_rdma *rdma,
			      स्थिर काष्ठा svc_rdma_chunk *chunk,
			      स्थिर काष्ठा xdr_buf *xdr)
अणु
	काष्ठा svc_rdma_ग_लिखो_info *info;
	काष्ठा svc_rdma_chunk_ctxt *cc;
	पूर्णांक ret;

	info = svc_rdma_ग_लिखो_info_alloc(rdma, chunk);
	अगर (!info)
		वापस -ENOMEM;
	cc = &info->wi_cc;

	ret = svc_rdma_xb_ग_लिखो(xdr, info);
	अगर (ret != xdr->len)
		जाओ out_err;

	trace_svcrdma_post_ग_लिखो_chunk(&cc->cc_cid, cc->cc_sqecount);
	ret = svc_rdma_post_chunk_ctxt(cc);
	अगर (ret < 0)
		जाओ out_err;
	वापस xdr->len;

out_err:
	svc_rdma_ग_लिखो_info_मुक्त(info);
	वापस ret;
पूर्ण

/**
 * svc_rdma_send_reply_chunk - Write all segments in the Reply chunk
 * @rdma: controlling RDMA transport
 * @rctxt: Write and Reply chunks from client
 * @xdr: xdr_buf containing an RPC Reply
 *
 * Returns a non-negative number of bytes the chunk consumed, or
 *	%-E2BIG अगर the payload was larger than the Reply chunk,
 *	%-EINVAL अगर client provided too many segments,
 *	%-ENOMEM अगर rdma_rw context pool was exhausted,
 *	%-ENOTCONN अगर posting failed (connection is lost),
 *	%-EIO अगर rdma_rw initialization failed (DMA mapping, etc).
 */
पूर्णांक svc_rdma_send_reply_chunk(काष्ठा svcxprt_rdma *rdma,
			      स्थिर काष्ठा svc_rdma_recv_ctxt *rctxt,
			      स्थिर काष्ठा xdr_buf *xdr)
अणु
	काष्ठा svc_rdma_ग_लिखो_info *info;
	काष्ठा svc_rdma_chunk_ctxt *cc;
	काष्ठा svc_rdma_chunk *chunk;
	पूर्णांक ret;

	अगर (pcl_is_empty(&rctxt->rc_reply_pcl))
		वापस 0;

	chunk = pcl_first_chunk(&rctxt->rc_reply_pcl);
	info = svc_rdma_ग_लिखो_info_alloc(rdma, chunk);
	अगर (!info)
		वापस -ENOMEM;
	cc = &info->wi_cc;

	ret = pcl_process_nonpayloads(&rctxt->rc_ग_लिखो_pcl, xdr,
				      svc_rdma_xb_ग_लिखो, info);
	अगर (ret < 0)
		जाओ out_err;

	trace_svcrdma_post_reply_chunk(&cc->cc_cid, cc->cc_sqecount);
	ret = svc_rdma_post_chunk_ctxt(cc);
	अगर (ret < 0)
		जाओ out_err;

	वापस xdr->len;

out_err:
	svc_rdma_ग_लिखो_info_मुक्त(info);
	वापस ret;
पूर्ण

/**
 * svc_rdma_build_पढ़ो_segment - Build RDMA Read WQEs to pull one RDMA segment
 * @info: context क्रम ongoing I/O
 * @segment: co-ordinates of remote memory to be पढ़ो
 *
 * Returns:
 *   %0: the Read WR chain was स्थिरructed successfully
 *   %-EINVAL: there were not enough rq_pages to finish
 *   %-ENOMEM: allocating a local resources failed
 *   %-EIO: a DMA mapping error occurred
 */
अटल पूर्णांक svc_rdma_build_पढ़ो_segment(काष्ठा svc_rdma_पढ़ो_info *info,
				       स्थिर काष्ठा svc_rdma_segment *segment)
अणु
	काष्ठा svc_rdma_recv_ctxt *head = info->ri_पढ़ोctxt;
	काष्ठा svc_rdma_chunk_ctxt *cc = &info->ri_cc;
	काष्ठा svc_rqst *rqstp = info->ri_rqst;
	अचिन्हित पूर्णांक sge_no, seg_len, len;
	काष्ठा svc_rdma_rw_ctxt *ctxt;
	काष्ठा scatterlist *sg;
	पूर्णांक ret;

	len = segment->rs_length;
	sge_no = PAGE_ALIGN(info->ri_pageoff + len) >> PAGE_SHIFT;
	ctxt = svc_rdma_get_rw_ctxt(cc->cc_rdma, sge_no);
	अगर (!ctxt)
		वापस -ENOMEM;
	ctxt->rw_nents = sge_no;

	sg = ctxt->rw_sg_table.sgl;
	क्रम (sge_no = 0; sge_no < ctxt->rw_nents; sge_no++) अणु
		seg_len = min_t(अचिन्हित पूर्णांक, len,
				PAGE_SIZE - info->ri_pageoff);

		अगर (!info->ri_pageoff)
			head->rc_page_count++;

		sg_set_page(sg, rqstp->rq_pages[info->ri_pageno],
			    seg_len, info->ri_pageoff);
		sg = sg_next(sg);

		info->ri_pageoff += seg_len;
		अगर (info->ri_pageoff == PAGE_SIZE) अणु
			info->ri_pageno++;
			info->ri_pageoff = 0;
		पूर्ण
		len -= seg_len;

		/* Safety check */
		अगर (len &&
		    &rqstp->rq_pages[info->ri_pageno + 1] > rqstp->rq_page_end)
			जाओ out_overrun;
	पूर्ण

	ret = svc_rdma_rw_ctx_init(cc->cc_rdma, ctxt, segment->rs_offset,
				   segment->rs_handle, DMA_FROM_DEVICE);
	अगर (ret < 0)
		वापस -EIO;
	percpu_counter_inc(&svcrdma_stat_पढ़ो);

	list_add(&ctxt->rw_list, &cc->cc_rwctxts);
	cc->cc_sqecount += ret;
	वापस 0;

out_overrun:
	trace_svcrdma_page_overrun_err(cc->cc_rdma, rqstp, info->ri_pageno);
	वापस -EINVAL;
पूर्ण

/**
 * svc_rdma_build_पढ़ो_chunk - Build RDMA Read WQEs to pull one RDMA chunk
 * @info: context क्रम ongoing I/O
 * @chunk: Read chunk to pull
 *
 * Return values:
 *   %0: the Read WR chain was स्थिरructed successfully
 *   %-EINVAL: there were not enough resources to finish
 *   %-ENOMEM: allocating a local resources failed
 *   %-EIO: a DMA mapping error occurred
 */
अटल पूर्णांक svc_rdma_build_पढ़ो_chunk(काष्ठा svc_rdma_पढ़ो_info *info,
				     स्थिर काष्ठा svc_rdma_chunk *chunk)
अणु
	स्थिर काष्ठा svc_rdma_segment *segment;
	पूर्णांक ret;

	ret = -EINVAL;
	pcl_क्रम_each_segment(segment, chunk) अणु
		ret = svc_rdma_build_पढ़ो_segment(info, segment);
		अगर (ret < 0)
			अवरोध;
		info->ri_totalbytes += segment->rs_length;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * svc_rdma_copy_अंतरभूत_range - Copy part of the अंतरभूत content पूर्णांकo pages
 * @info: context क्रम RDMA Reads
 * @offset: offset पूर्णांकo the Receive buffer of region to copy
 * @reमुख्यing: length of region to copy
 *
 * Take a page at a समय from rqstp->rq_pages and copy the अंतरभूत
 * content from the Receive buffer पूर्णांकo that page. Update
 * info->ri_pageno and info->ri_pageoff so that the next RDMA Read
 * result will land contiguously with the copied content.
 *
 * Return values:
 *   %0: Inline content was successfully copied
 *   %-EINVAL: offset or length was incorrect
 */
अटल पूर्णांक svc_rdma_copy_अंतरभूत_range(काष्ठा svc_rdma_पढ़ो_info *info,
				      अचिन्हित पूर्णांक offset,
				      अचिन्हित पूर्णांक reमुख्यing)
अणु
	काष्ठा svc_rdma_recv_ctxt *head = info->ri_पढ़ोctxt;
	अचिन्हित अक्षर *dst, *src = head->rc_recv_buf;
	काष्ठा svc_rqst *rqstp = info->ri_rqst;
	अचिन्हित पूर्णांक page_no, numpages;

	numpages = PAGE_ALIGN(info->ri_pageoff + reमुख्यing) >> PAGE_SHIFT;
	क्रम (page_no = 0; page_no < numpages; page_no++) अणु
		अचिन्हित पूर्णांक page_len;

		page_len = min_t(अचिन्हित पूर्णांक, reमुख्यing,
				 PAGE_SIZE - info->ri_pageoff);

		अगर (!info->ri_pageoff)
			head->rc_page_count++;

		dst = page_address(rqstp->rq_pages[info->ri_pageno]);
		स_नकल(dst + info->ri_pageno, src + offset, page_len);

		info->ri_totalbytes += page_len;
		info->ri_pageoff += page_len;
		अगर (info->ri_pageoff == PAGE_SIZE) अणु
			info->ri_pageno++;
			info->ri_pageoff = 0;
		पूर्ण
		reमुख्यing -= page_len;
		offset += page_len;
	पूर्ण

	वापस -EINVAL;
पूर्ण

/**
 * svc_rdma_पढ़ो_multiple_chunks - Conकाष्ठा RDMA Reads to pull data item Read chunks
 * @info: context क्रम RDMA Reads
 *
 * The chunk data lands in rqstp->rq_arg as a series of contiguous pages,
 * like an incoming TCP call.
 *
 * Return values:
 *   %0: RDMA Read WQEs were successfully built
 *   %-EINVAL: client provided too many chunks or segments,
 *   %-ENOMEM: rdma_rw context pool was exhausted,
 *   %-ENOTCONN: posting failed (connection is lost),
 *   %-EIO: rdma_rw initialization failed (DMA mapping, etc).
 */
अटल noअंतरभूत पूर्णांक svc_rdma_पढ़ो_multiple_chunks(काष्ठा svc_rdma_पढ़ो_info *info)
अणु
	काष्ठा svc_rdma_recv_ctxt *head = info->ri_पढ़ोctxt;
	स्थिर काष्ठा svc_rdma_pcl *pcl = &head->rc_पढ़ो_pcl;
	काष्ठा xdr_buf *buf = &info->ri_rqst->rq_arg;
	काष्ठा svc_rdma_chunk *chunk, *next;
	अचिन्हित पूर्णांक start, length;
	पूर्णांक ret;

	start = 0;
	chunk = pcl_first_chunk(pcl);
	length = chunk->ch_position;
	ret = svc_rdma_copy_अंतरभूत_range(info, start, length);
	अगर (ret < 0)
		वापस ret;

	pcl_क्रम_each_chunk(chunk, pcl) अणु
		ret = svc_rdma_build_पढ़ो_chunk(info, chunk);
		अगर (ret < 0)
			वापस ret;

		next = pcl_next_chunk(pcl, chunk);
		अगर (!next)
			अवरोध;

		start += length;
		length = next->ch_position - info->ri_totalbytes;
		ret = svc_rdma_copy_अंतरभूत_range(info, start, length);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	start += length;
	length = head->rc_byte_len - start;
	ret = svc_rdma_copy_अंतरभूत_range(info, start, length);
	अगर (ret < 0)
		वापस ret;

	buf->len += info->ri_totalbytes;
	buf->buflen += info->ri_totalbytes;

	buf->head[0].iov_base = page_address(info->ri_rqst->rq_pages[0]);
	buf->head[0].iov_len = min_t(माप_प्रकार, PAGE_SIZE, info->ri_totalbytes);
	buf->pages = &info->ri_rqst->rq_pages[1];
	buf->page_len = info->ri_totalbytes - buf->head[0].iov_len;
	वापस 0;
पूर्ण

/**
 * svc_rdma_पढ़ो_data_item - Conकाष्ठा RDMA Reads to pull data item Read chunks
 * @info: context क्रम RDMA Reads
 *
 * The chunk data lands in the page list of rqstp->rq_arg.pages.
 *
 * Currently NFSD करोes not look at the rqstp->rq_arg.tail[0] kvec.
 * Thereक्रमe, XDR round-up of the Read chunk and trailing
 * अंतरभूत content must both be added at the end of the pagelist.
 *
 * Return values:
 *   %0: RDMA Read WQEs were successfully built
 *   %-EINVAL: client provided too many chunks or segments,
 *   %-ENOMEM: rdma_rw context pool was exhausted,
 *   %-ENOTCONN: posting failed (connection is lost),
 *   %-EIO: rdma_rw initialization failed (DMA mapping, etc).
 */
अटल पूर्णांक svc_rdma_पढ़ो_data_item(काष्ठा svc_rdma_पढ़ो_info *info)
अणु
	काष्ठा svc_rdma_recv_ctxt *head = info->ri_पढ़ोctxt;
	काष्ठा xdr_buf *buf = &info->ri_rqst->rq_arg;
	काष्ठा svc_rdma_chunk *chunk;
	अचिन्हित पूर्णांक length;
	पूर्णांक ret;

	chunk = pcl_first_chunk(&head->rc_पढ़ो_pcl);
	ret = svc_rdma_build_पढ़ो_chunk(info, chunk);
	अगर (ret < 0)
		जाओ out;

	/* Split the Receive buffer between the head and tail
	 * buffers at Read chunk's position. XDR roundup of the
	 * chunk is not included in either the pagelist or in
	 * the tail.
	 */
	buf->tail[0].iov_base = buf->head[0].iov_base + chunk->ch_position;
	buf->tail[0].iov_len = buf->head[0].iov_len - chunk->ch_position;
	buf->head[0].iov_len = chunk->ch_position;

	/* Read chunk may need XDR roundup (see RFC 8166, s. 3.4.5.2).
	 *
	 * If the client alपढ़ोy rounded up the chunk length, the
	 * length करोes not change. Otherwise, the length of the page
	 * list is increased to include XDR round-up.
	 *
	 * Currently these chunks always start at page offset 0,
	 * thus the rounded-up length never crosses a page boundary.
	 */
	buf->pages = &info->ri_rqst->rq_pages[0];
	length = xdr_align_size(chunk->ch_length);
	buf->page_len = length;
	buf->len += length;
	buf->buflen += length;

out:
	वापस ret;
पूर्ण

/**
 * svc_rdma_पढ़ो_chunk_range - Build RDMA Read WQEs क्रम portion of a chunk
 * @info: context क्रम RDMA Reads
 * @chunk: parsed Call chunk to pull
 * @offset: offset of region to pull
 * @length: length of region to pull
 *
 * Return values:
 *   %0: RDMA Read WQEs were successfully built
 *   %-EINVAL: there were not enough resources to finish
 *   %-ENOMEM: rdma_rw context pool was exhausted,
 *   %-ENOTCONN: posting failed (connection is lost),
 *   %-EIO: rdma_rw initialization failed (DMA mapping, etc).
 */
अटल पूर्णांक svc_rdma_पढ़ो_chunk_range(काष्ठा svc_rdma_पढ़ो_info *info,
				     स्थिर काष्ठा svc_rdma_chunk *chunk,
				     अचिन्हित पूर्णांक offset, अचिन्हित पूर्णांक length)
अणु
	स्थिर काष्ठा svc_rdma_segment *segment;
	पूर्णांक ret;

	ret = -EINVAL;
	pcl_क्रम_each_segment(segment, chunk) अणु
		काष्ठा svc_rdma_segment dummy;

		अगर (offset > segment->rs_length) अणु
			offset -= segment->rs_length;
			जारी;
		पूर्ण

		dummy.rs_handle = segment->rs_handle;
		dummy.rs_length = min_t(u32, length, segment->rs_length) - offset;
		dummy.rs_offset = segment->rs_offset + offset;

		ret = svc_rdma_build_पढ़ो_segment(info, &dummy);
		अगर (ret < 0)
			अवरोध;

		info->ri_totalbytes += dummy.rs_length;
		length -= dummy.rs_length;
		offset = 0;
	पूर्ण
	वापस ret;
पूर्ण

/**
 * svc_rdma_पढ़ो_call_chunk - Build RDMA Read WQEs to pull a Long Message
 * @info: context क्रम RDMA Reads
 *
 * Return values:
 *   %0: RDMA Read WQEs were successfully built
 *   %-EINVAL: there were not enough resources to finish
 *   %-ENOMEM: rdma_rw context pool was exhausted,
 *   %-ENOTCONN: posting failed (connection is lost),
 *   %-EIO: rdma_rw initialization failed (DMA mapping, etc).
 */
अटल पूर्णांक svc_rdma_पढ़ो_call_chunk(काष्ठा svc_rdma_पढ़ो_info *info)
अणु
	काष्ठा svc_rdma_recv_ctxt *head = info->ri_पढ़ोctxt;
	स्थिर काष्ठा svc_rdma_chunk *call_chunk =
			pcl_first_chunk(&head->rc_call_pcl);
	स्थिर काष्ठा svc_rdma_pcl *pcl = &head->rc_पढ़ो_pcl;
	काष्ठा svc_rdma_chunk *chunk, *next;
	अचिन्हित पूर्णांक start, length;
	पूर्णांक ret;

	अगर (pcl_is_empty(pcl))
		वापस svc_rdma_build_पढ़ो_chunk(info, call_chunk);

	start = 0;
	chunk = pcl_first_chunk(pcl);
	length = chunk->ch_position;
	ret = svc_rdma_पढ़ो_chunk_range(info, call_chunk, start, length);
	अगर (ret < 0)
		वापस ret;

	pcl_क्रम_each_chunk(chunk, pcl) अणु
		ret = svc_rdma_build_पढ़ो_chunk(info, chunk);
		अगर (ret < 0)
			वापस ret;

		next = pcl_next_chunk(pcl, chunk);
		अगर (!next)
			अवरोध;

		start += length;
		length = next->ch_position - info->ri_totalbytes;
		ret = svc_rdma_पढ़ो_chunk_range(info, call_chunk,
						start, length);
		अगर (ret < 0)
			वापस ret;
	पूर्ण

	start += length;
	length = call_chunk->ch_length - start;
	वापस svc_rdma_पढ़ो_chunk_range(info, call_chunk, start, length);
पूर्ण

/**
 * svc_rdma_पढ़ो_special - Build RDMA Read WQEs to pull a Long Message
 * @info: context क्रम RDMA Reads
 *
 * The start of the data lands in the first page just after the
 * Transport header, and the rest lands in rqstp->rq_arg.pages.
 *
 * Assumptions:
 *	- A PZRC is never sent in an RDMA_MSG message, though it's
 *	  allowed by spec.
 *
 * Return values:
 *   %0: RDMA Read WQEs were successfully built
 *   %-EINVAL: client provided too many chunks or segments,
 *   %-ENOMEM: rdma_rw context pool was exhausted,
 *   %-ENOTCONN: posting failed (connection is lost),
 *   %-EIO: rdma_rw initialization failed (DMA mapping, etc).
 */
अटल noअंतरभूत पूर्णांक svc_rdma_पढ़ो_special(काष्ठा svc_rdma_पढ़ो_info *info)
अणु
	काष्ठा xdr_buf *buf = &info->ri_rqst->rq_arg;
	पूर्णांक ret;

	ret = svc_rdma_पढ़ो_call_chunk(info);
	अगर (ret < 0)
		जाओ out;

	buf->len += info->ri_totalbytes;
	buf->buflen += info->ri_totalbytes;

	buf->head[0].iov_base = page_address(info->ri_rqst->rq_pages[0]);
	buf->head[0].iov_len = min_t(माप_प्रकार, PAGE_SIZE, info->ri_totalbytes);
	buf->pages = &info->ri_rqst->rq_pages[1];
	buf->page_len = info->ri_totalbytes - buf->head[0].iov_len;

out:
	वापस ret;
पूर्ण

/**
 * svc_rdma_process_पढ़ो_list - Pull list of Read chunks from the client
 * @rdma: controlling RDMA transport
 * @rqstp: set of pages to use as Read sink buffers
 * @head: pages under I/O collect here
 *
 * The RPC/RDMA protocol assumes that the upper layer's XDR decoders
 * pull each Read chunk as they decode an incoming RPC message.
 *
 * On Linux, however, the server needs to have a fully-स्थिरructed RPC
 * message in rqstp->rq_arg when there is a positive वापस code from
 * ->xpo_recvfrom. So the Read list is safety-checked immediately when
 * it is received, then here the whole Read list is pulled all at once.
 * The ingress RPC message is fully reस्थिरructed once all associated
 * RDMA Reads have completed.
 *
 * Return values:
 *   %1: all needed RDMA Reads were posted successfully,
 *   %-EINVAL: client provided too many chunks or segments,
 *   %-ENOMEM: rdma_rw context pool was exhausted,
 *   %-ENOTCONN: posting failed (connection is lost),
 *   %-EIO: rdma_rw initialization failed (DMA mapping, etc).
 */
पूर्णांक svc_rdma_process_पढ़ो_list(काष्ठा svcxprt_rdma *rdma,
			       काष्ठा svc_rqst *rqstp,
			       काष्ठा svc_rdma_recv_ctxt *head)
अणु
	काष्ठा svc_rdma_पढ़ो_info *info;
	काष्ठा svc_rdma_chunk_ctxt *cc;
	पूर्णांक ret;

	info = svc_rdma_पढ़ो_info_alloc(rdma);
	अगर (!info)
		वापस -ENOMEM;
	cc = &info->ri_cc;
	info->ri_rqst = rqstp;
	info->ri_पढ़ोctxt = head;
	info->ri_pageno = 0;
	info->ri_pageoff = 0;
	info->ri_totalbytes = 0;

	अगर (pcl_is_empty(&head->rc_call_pcl)) अणु
		अगर (head->rc_पढ़ो_pcl.cl_count == 1)
			ret = svc_rdma_पढ़ो_data_item(info);
		अन्यथा
			ret = svc_rdma_पढ़ो_multiple_chunks(info);
	पूर्ण अन्यथा
		ret = svc_rdma_पढ़ो_special(info);
	अगर (ret < 0)
		जाओ out_err;

	trace_svcrdma_post_पढ़ो_chunk(&cc->cc_cid, cc->cc_sqecount);
	init_completion(&cc->cc_करोne);
	ret = svc_rdma_post_chunk_ctxt(cc);
	अगर (ret < 0)
		जाओ out_err;

	ret = 1;
	रुको_क्रम_completion(&cc->cc_करोne);
	अगर (cc->cc_status != IB_WC_SUCCESS)
		ret = -EIO;

	/* rq_respages starts after the last arg page */
	rqstp->rq_respages = &rqstp->rq_pages[head->rc_page_count];
	rqstp->rq_next_page = rqstp->rq_respages + 1;

	/* Ensure svc_rdma_recv_ctxt_put() करोes not try to release pages */
	head->rc_page_count = 0;

out_err:
	svc_rdma_पढ़ो_info_मुक्त(info);
	वापस ret;
पूर्ण
