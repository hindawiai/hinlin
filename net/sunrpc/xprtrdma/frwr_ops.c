<शैली गुरु>
// SPDX-License-Identअगरier: GPL-2.0
/*
 * Copyright (c) 2015, 2017 Oracle.  All rights reserved.
 * Copyright (c) 2003-2007 Network Appliance, Inc. All rights reserved.
 */

/* Lightweight memory registration using Fast Registration Work
 * Requests (FRWR).
 *
 * FRWR features ordered asynchronous registration and invalidation
 * of arbitrarily-sized memory regions. This is the fastest and safest
 * but most complex memory registration mode.
 */

/* Normal operation
 *
 * A Memory Region is prepared क्रम RDMA Read or Write using a FAST_REG
 * Work Request (frwr_map). When the RDMA operation is finished, this
 * Memory Region is invalidated using a LOCAL_INV Work Request
 * (frwr_unmap_async and frwr_unmap_sync).
 *
 * Typically FAST_REG Work Requests are not संकेतed, and neither are
 * RDMA Send Work Requests (with the exception of संकेतing occasionally
 * to prevent provider work queue overflows). This greatly reduces HCA
 * पूर्णांकerrupt workload.
 */

/* Transport recovery
 *
 * frwr_map and frwr_unmap_* cannot run at the same समय the transport
 * connect worker is running. The connect worker holds the transport
 * send lock, just as ->send_request करोes. This prevents frwr_map and
 * the connect worker from running concurrently. When a connection is
 * बंदd, the Receive completion queue is drained beक्रमe the allowing
 * the connect worker to get control. This prevents frwr_unmap and the
 * connect worker from running concurrently.
 *
 * When the underlying transport disconnects, MRs that are in flight
 * are flushed and are likely unusable. Thus all MRs are destroyed.
 * New MRs are created on demand.
 */

#समावेश <linux/sunrpc/svc_rdma.h>

#समावेश "xprt_rdma.h"
#समावेश <trace/events/rpcrdma.h>

#अगर IS_ENABLED(CONFIG_SUNRPC_DEBUG)
# define RPCDBG_FACILITY	RPCDBG_TRANS
#पूर्ण_अगर

अटल व्योम frwr_cid_init(काष्ठा rpcrdma_ep *ep,
			  काष्ठा rpcrdma_mr *mr)
अणु
	काष्ठा rpc_rdma_cid *cid = &mr->mr_cid;

	cid->ci_queue_id = ep->re_attr.send_cq->res.id;
	cid->ci_completion_id = mr->mr_ibmr->res.id;
पूर्ण

अटल व्योम frwr_mr_unmap(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_mr *mr)
अणु
	अगर (mr->mr_device) अणु
		trace_xprtrdma_mr_unmap(mr);
		ib_dma_unmap_sg(mr->mr_device, mr->mr_sg, mr->mr_nents,
				mr->mr_dir);
		mr->mr_device = शून्य;
	पूर्ण
पूर्ण

/**
 * frwr_mr_release - Destroy one MR
 * @mr: MR allocated by frwr_mr_init
 *
 */
व्योम frwr_mr_release(काष्ठा rpcrdma_mr *mr)
अणु
	पूर्णांक rc;

	frwr_mr_unmap(mr->mr_xprt, mr);

	rc = ib_dereg_mr(mr->mr_ibmr);
	अगर (rc)
		trace_xprtrdma_frwr_dereg(mr, rc);
	kमुक्त(mr->mr_sg);
	kमुक्त(mr);
पूर्ण

अटल व्योम frwr_mr_put(काष्ठा rpcrdma_mr *mr)
अणु
	frwr_mr_unmap(mr->mr_xprt, mr);

	/* The MR is वापसed to the req's MR मुक्त list instead
	 * of to the xprt's MR मुक्त list. No spinlock is needed.
	 */
	rpcrdma_mr_push(mr, &mr->mr_req->rl_मुक्त_mrs);
पूर्ण

/* frwr_reset - Place MRs back on the मुक्त list
 * @req: request to reset
 *
 * Used after a failed marshal. For FRWR, this means the MRs
 * करोn't have to be fully released and recreated.
 *
 * NB: This is safe only as दीर्घ as none of @req's MRs are
 * involved with an ongoing asynchronous FAST_REG or LOCAL_INV
 * Work Request.
 */
व्योम frwr_reset(काष्ठा rpcrdma_req *req)
अणु
	काष्ठा rpcrdma_mr *mr;

	जबतक ((mr = rpcrdma_mr_pop(&req->rl_रेजिस्टरed)))
		frwr_mr_put(mr);
पूर्ण

/**
 * frwr_mr_init - Initialize one MR
 * @r_xprt: controlling transport instance
 * @mr: generic MR to prepare क्रम FRWR
 *
 * Returns zero अगर successful. Otherwise a negative त्रुटि_सं
 * is वापसed.
 */
पूर्णांक frwr_mr_init(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_mr *mr)
अणु
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	अचिन्हित पूर्णांक depth = ep->re_max_fr_depth;
	काष्ठा scatterlist *sg;
	काष्ठा ib_mr *frmr;
	पूर्णांक rc;

	frmr = ib_alloc_mr(ep->re_pd, ep->re_mrtype, depth);
	अगर (IS_ERR(frmr))
		जाओ out_mr_err;

	sg = kदो_स्मृति_array(depth, माप(*sg), GFP_NOFS);
	अगर (!sg)
		जाओ out_list_err;

	mr->mr_xprt = r_xprt;
	mr->mr_ibmr = frmr;
	mr->mr_device = शून्य;
	INIT_LIST_HEAD(&mr->mr_list);
	init_completion(&mr->mr_linv_करोne);
	frwr_cid_init(ep, mr);

	sg_init_table(sg, depth);
	mr->mr_sg = sg;
	वापस 0;

out_mr_err:
	rc = PTR_ERR(frmr);
	trace_xprtrdma_frwr_alloc(mr, rc);
	वापस rc;

out_list_err:
	ib_dereg_mr(frmr);
	वापस -ENOMEM;
पूर्ण

/**
 * frwr_query_device - Prepare a transport क्रम use with FRWR
 * @ep: endpoपूर्णांक to fill in
 * @device: RDMA device to query
 *
 * On success, sets:
 *	ep->re_attr
 *	ep->re_max_requests
 *	ep->re_max_rdma_segs
 *	ep->re_max_fr_depth
 *	ep->re_mrtype
 *
 * Return values:
 *   On success, वापसs zero.
 *   %-EINVAL - the device करोes not support FRWR memory registration
 *   %-ENOMEM - the device is not sufficiently capable क्रम NFS/RDMA
 */
पूर्णांक frwr_query_device(काष्ठा rpcrdma_ep *ep, स्थिर काष्ठा ib_device *device)
अणु
	स्थिर काष्ठा ib_device_attr *attrs = &device->attrs;
	पूर्णांक max_qp_wr, depth, delta;
	अचिन्हित पूर्णांक max_sge;

	अगर (!(attrs->device_cap_flags & IB_DEVICE_MEM_MGT_EXTENSIONS) ||
	    attrs->max_fast_reg_page_list_len == 0) अणु
		pr_err("rpcrdma: 'frwr' mode is not supported by device %s\n",
		       device->name);
		वापस -EINVAL;
	पूर्ण

	max_sge = min_t(अचिन्हित पूर्णांक, attrs->max_send_sge,
			RPCRDMA_MAX_SEND_SGES);
	अगर (max_sge < RPCRDMA_MIN_SEND_SGES) अणु
		pr_err("rpcrdma: HCA provides only %u send SGEs\n", max_sge);
		वापस -ENOMEM;
	पूर्ण
	ep->re_attr.cap.max_send_sge = max_sge;
	ep->re_attr.cap.max_recv_sge = 1;

	ep->re_mrtype = IB_MR_TYPE_MEM_REG;
	अगर (attrs->device_cap_flags & IB_DEVICE_SG_GAPS_REG)
		ep->re_mrtype = IB_MR_TYPE_SG_GAPS;

	/* Quirk: Some devices advertise a large max_fast_reg_page_list_len
	 * capability, but perक्रमm optimally when the MRs are not larger
	 * than a page.
	 */
	अगर (attrs->max_sge_rd > RPCRDMA_MAX_HDR_SEGS)
		ep->re_max_fr_depth = attrs->max_sge_rd;
	अन्यथा
		ep->re_max_fr_depth = attrs->max_fast_reg_page_list_len;
	अगर (ep->re_max_fr_depth > RPCRDMA_MAX_DATA_SEGS)
		ep->re_max_fr_depth = RPCRDMA_MAX_DATA_SEGS;

	/* Add room क्रम frwr रेजिस्टर and invalidate WRs.
	 * 1. FRWR reg WR क्रम head
	 * 2. FRWR invalidate WR क्रम head
	 * 3. N FRWR reg WRs क्रम pagelist
	 * 4. N FRWR invalidate WRs क्रम pagelist
	 * 5. FRWR reg WR क्रम tail
	 * 6. FRWR invalidate WR क्रम tail
	 * 7. The RDMA_SEND WR
	 */
	depth = 7;

	/* Calculate N अगर the device max FRWR depth is smaller than
	 * RPCRDMA_MAX_DATA_SEGS.
	 */
	अगर (ep->re_max_fr_depth < RPCRDMA_MAX_DATA_SEGS) अणु
		delta = RPCRDMA_MAX_DATA_SEGS - ep->re_max_fr_depth;
		करो अणु
			depth += 2; /* FRWR reg + invalidate */
			delta -= ep->re_max_fr_depth;
		पूर्ण जबतक (delta > 0);
	पूर्ण

	max_qp_wr = attrs->max_qp_wr;
	max_qp_wr -= RPCRDMA_BACKWARD_WRS;
	max_qp_wr -= 1;
	अगर (max_qp_wr < RPCRDMA_MIN_SLOT_TABLE)
		वापस -ENOMEM;
	अगर (ep->re_max_requests > max_qp_wr)
		ep->re_max_requests = max_qp_wr;
	ep->re_attr.cap.max_send_wr = ep->re_max_requests * depth;
	अगर (ep->re_attr.cap.max_send_wr > max_qp_wr) अणु
		ep->re_max_requests = max_qp_wr / depth;
		अगर (!ep->re_max_requests)
			वापस -ENOMEM;
		ep->re_attr.cap.max_send_wr = ep->re_max_requests * depth;
	पूर्ण
	ep->re_attr.cap.max_send_wr += RPCRDMA_BACKWARD_WRS;
	ep->re_attr.cap.max_send_wr += 1; /* क्रम ib_drain_sq */
	ep->re_attr.cap.max_recv_wr = ep->re_max_requests;
	ep->re_attr.cap.max_recv_wr += RPCRDMA_BACKWARD_WRS;
	ep->re_attr.cap.max_recv_wr += RPCRDMA_MAX_RECV_BATCH;
	ep->re_attr.cap.max_recv_wr += 1; /* क्रम ib_drain_rq */

	ep->re_max_rdma_segs =
		DIV_ROUND_UP(RPCRDMA_MAX_DATA_SEGS, ep->re_max_fr_depth);
	/* Reply chunks require segments क्रम head and tail buffers */
	ep->re_max_rdma_segs += 2;
	अगर (ep->re_max_rdma_segs > RPCRDMA_MAX_HDR_SEGS)
		ep->re_max_rdma_segs = RPCRDMA_MAX_HDR_SEGS;

	/* Ensure the underlying device is capable of conveying the
	 * largest r/wsize NFS will ask क्रम. This guarantees that
	 * failing over from one RDMA device to another will not
	 * अवरोध NFS I/O.
	 */
	अगर ((ep->re_max_rdma_segs * ep->re_max_fr_depth) < RPCRDMA_MAX_SEGS)
		वापस -ENOMEM;

	वापस 0;
पूर्ण

/**
 * frwr_map - Register a memory region
 * @r_xprt: controlling transport
 * @seg: memory region co-ordinates
 * @nsegs: number of segments reमुख्यing
 * @writing: true when RDMA Write will be used
 * @xid: XID of RPC using the रेजिस्टरed memory
 * @mr: MR to fill in
 *
 * Prepare a REG_MR Work Request to रेजिस्टर a memory region
 * क्रम remote access via RDMA READ or RDMA WRITE.
 *
 * Returns the next segment or a negative त्रुटि_सं poपूर्णांकer.
 * On success, @mr is filled in.
 */
काष्ठा rpcrdma_mr_seg *frwr_map(काष्ठा rpcrdma_xprt *r_xprt,
				काष्ठा rpcrdma_mr_seg *seg,
				पूर्णांक nsegs, bool writing, __be32 xid,
				काष्ठा rpcrdma_mr *mr)
अणु
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	काष्ठा ib_reg_wr *reg_wr;
	पूर्णांक i, n, dma_nents;
	काष्ठा ib_mr *ibmr;
	u8 key;

	अगर (nsegs > ep->re_max_fr_depth)
		nsegs = ep->re_max_fr_depth;
	क्रम (i = 0; i < nsegs;) अणु
		sg_set_page(&mr->mr_sg[i], seg->mr_page,
			    seg->mr_len, seg->mr_offset);

		++seg;
		++i;
		अगर (ep->re_mrtype == IB_MR_TYPE_SG_GAPS)
			जारी;
		अगर ((i < nsegs && seg->mr_offset) ||
		    offset_in_page((seg-1)->mr_offset + (seg-1)->mr_len))
			अवरोध;
	पूर्ण
	mr->mr_dir = rpcrdma_data_dir(writing);
	mr->mr_nents = i;

	dma_nents = ib_dma_map_sg(ep->re_id->device, mr->mr_sg, mr->mr_nents,
				  mr->mr_dir);
	अगर (!dma_nents)
		जाओ out_dmamap_err;
	mr->mr_device = ep->re_id->device;

	ibmr = mr->mr_ibmr;
	n = ib_map_mr_sg(ibmr, mr->mr_sg, dma_nents, शून्य, PAGE_SIZE);
	अगर (n != dma_nents)
		जाओ out_mapmr_err;

	ibmr->iova &= 0x00000000ffffffff;
	ibmr->iova |= ((u64)be32_to_cpu(xid)) << 32;
	key = (u8)(ibmr->rkey & 0x000000FF);
	ib_update_fast_reg_key(ibmr, ++key);

	reg_wr = &mr->mr_regwr;
	reg_wr->mr = ibmr;
	reg_wr->key = ibmr->rkey;
	reg_wr->access = writing ?
			 IB_ACCESS_REMOTE_WRITE | IB_ACCESS_LOCAL_WRITE :
			 IB_ACCESS_REMOTE_READ;

	mr->mr_handle = ibmr->rkey;
	mr->mr_length = ibmr->length;
	mr->mr_offset = ibmr->iova;
	trace_xprtrdma_mr_map(mr);

	वापस seg;

out_dmamap_err:
	trace_xprtrdma_frwr_sgerr(mr, i);
	वापस ERR_PTR(-EIO);

out_mapmr_err:
	trace_xprtrdma_frwr_maperr(mr, n);
	वापस ERR_PTR(-EIO);
पूर्ण

/**
 * frwr_wc_fastreg - Invoked by RDMA provider क्रम a flushed FastReg WC
 * @cq: completion queue
 * @wc: WCE क्रम a completed FastReg WR
 *
 * Each flushed MR माला_लो destroyed after the QP has drained.
 */
अटल व्योम frwr_wc_fastreg(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा rpcrdma_mr *mr = container_of(cqe, काष्ठा rpcrdma_mr, mr_cqe);

	/* WARNING: Only wr_cqe and status are reliable at this poपूर्णांक */
	trace_xprtrdma_wc_fastreg(wc, &mr->mr_cid);

	rpcrdma_flush_disconnect(cq->cq_context, wc);
पूर्ण

/**
 * frwr_send - post Send WRs containing the RPC Call message
 * @r_xprt: controlling transport instance
 * @req: prepared RPC Call
 *
 * For FRWR, chain any FastReg WRs to the Send WR. Only a
 * single ib_post_send call is needed to रेजिस्टर memory
 * and then post the Send WR.
 *
 * Returns the वापस code from ib_post_send.
 *
 * Caller must hold the transport send lock to ensure that the
 * poपूर्णांकers to the transport's rdma_cm_id and QP are stable.
 */
पूर्णांक frwr_send(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req)
अणु
	काष्ठा ib_send_wr *post_wr, *send_wr = &req->rl_wr;
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	काष्ठा rpcrdma_mr *mr;
	अचिन्हित पूर्णांक num_wrs;

	num_wrs = 1;
	post_wr = send_wr;
	list_क्रम_each_entry(mr, &req->rl_रेजिस्टरed, mr_list) अणु
		trace_xprtrdma_mr_fastreg(mr);

		mr->mr_cqe.करोne = frwr_wc_fastreg;
		mr->mr_regwr.wr.next = post_wr;
		mr->mr_regwr.wr.wr_cqe = &mr->mr_cqe;
		mr->mr_regwr.wr.num_sge = 0;
		mr->mr_regwr.wr.opcode = IB_WR_REG_MR;
		mr->mr_regwr.wr.send_flags = 0;
		post_wr = &mr->mr_regwr.wr;
		++num_wrs;
	पूर्ण

	अगर ((kref_पढ़ो(&req->rl_kref) > 1) || num_wrs > ep->re_send_count) अणु
		send_wr->send_flags |= IB_SEND_SIGNALED;
		ep->re_send_count = min_t(अचिन्हित पूर्णांक, ep->re_send_batch,
					  num_wrs - ep->re_send_count);
	पूर्ण अन्यथा अणु
		send_wr->send_flags &= ~IB_SEND_SIGNALED;
		ep->re_send_count -= num_wrs;
	पूर्ण

	trace_xprtrdma_post_send(req);
	वापस ib_post_send(ep->re_id->qp, post_wr, शून्य);
पूर्ण

/**
 * frwr_reminv - handle a remotely invalidated mr on the @mrs list
 * @rep: Received reply
 * @mrs: list of MRs to check
 *
 */
व्योम frwr_reminv(काष्ठा rpcrdma_rep *rep, काष्ठा list_head *mrs)
अणु
	काष्ठा rpcrdma_mr *mr;

	list_क्रम_each_entry(mr, mrs, mr_list)
		अगर (mr->mr_handle == rep->rr_inv_rkey) अणु
			list_del_init(&mr->mr_list);
			trace_xprtrdma_mr_reminv(mr);
			frwr_mr_put(mr);
			अवरोध;	/* only one invalidated MR per RPC */
		पूर्ण
पूर्ण

अटल व्योम frwr_mr_करोne(काष्ठा ib_wc *wc, काष्ठा rpcrdma_mr *mr)
अणु
	अगर (likely(wc->status == IB_WC_SUCCESS))
		frwr_mr_put(mr);
पूर्ण

/**
 * frwr_wc_localinv - Invoked by RDMA provider क्रम a LOCAL_INV WC
 * @cq: completion queue
 * @wc: WCE क्रम a completed LocalInv WR
 *
 */
अटल व्योम frwr_wc_localinv(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा rpcrdma_mr *mr = container_of(cqe, काष्ठा rpcrdma_mr, mr_cqe);

	/* WARNING: Only wr_cqe and status are reliable at this poपूर्णांक */
	trace_xprtrdma_wc_li(wc, &mr->mr_cid);
	frwr_mr_करोne(wc, mr);

	rpcrdma_flush_disconnect(cq->cq_context, wc);
पूर्ण

/**
 * frwr_wc_localinv_wake - Invoked by RDMA provider क्रम a LOCAL_INV WC
 * @cq: completion queue
 * @wc: WCE क्रम a completed LocalInv WR
 *
 * Awaken anyone रुकोing क्रम an MR to finish being fenced.
 */
अटल व्योम frwr_wc_localinv_wake(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा rpcrdma_mr *mr = container_of(cqe, काष्ठा rpcrdma_mr, mr_cqe);

	/* WARNING: Only wr_cqe and status are reliable at this poपूर्णांक */
	trace_xprtrdma_wc_li_wake(wc, &mr->mr_cid);
	frwr_mr_करोne(wc, mr);
	complete(&mr->mr_linv_करोne);

	rpcrdma_flush_disconnect(cq->cq_context, wc);
पूर्ण

/**
 * frwr_unmap_sync - invalidate memory regions that were रेजिस्टरed क्रम @req
 * @r_xprt: controlling transport instance
 * @req: rpcrdma_req with a non-empty list of MRs to process
 *
 * Sleeps until it is safe क्रम the host CPU to access the previously mapped
 * memory regions. This guarantees that रेजिस्टरed MRs are properly fenced
 * from the server beक्रमe the RPC consumer accesses the data in them. It
 * also ensures proper Send flow control: waking the next RPC रुकोs until
 * this RPC has relinquished all its Send Queue entries.
 */
व्योम frwr_unmap_sync(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req)
अणु
	काष्ठा ib_send_wr *first, **prev, *last;
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	स्थिर काष्ठा ib_send_wr *bad_wr;
	काष्ठा rpcrdma_mr *mr;
	पूर्णांक rc;

	/* ORDER: Invalidate all of the MRs first
	 *
	 * Chain the LOCAL_INV Work Requests and post them with
	 * a single ib_post_send() call.
	 */
	prev = &first;
	जबतक ((mr = rpcrdma_mr_pop(&req->rl_रेजिस्टरed))) अणु

		trace_xprtrdma_mr_localinv(mr);
		r_xprt->rx_stats.local_inv_needed++;

		last = &mr->mr_invwr;
		last->next = शून्य;
		last->wr_cqe = &mr->mr_cqe;
		last->sg_list = शून्य;
		last->num_sge = 0;
		last->opcode = IB_WR_LOCAL_INV;
		last->send_flags = IB_SEND_SIGNALED;
		last->ex.invalidate_rkey = mr->mr_handle;

		last->wr_cqe->करोne = frwr_wc_localinv;

		*prev = last;
		prev = &last->next;
	पूर्ण
	mr = container_of(last, काष्ठा rpcrdma_mr, mr_invwr);

	/* Strong send queue ordering guarantees that when the
	 * last WR in the chain completes, all WRs in the chain
	 * are complete.
	 */
	last->wr_cqe->करोne = frwr_wc_localinv_wake;
	reinit_completion(&mr->mr_linv_करोne);

	/* Transport disconnect drains the receive CQ beक्रमe it
	 * replaces the QP. The RPC reply handler won't call us
	 * unless re_id->qp is a valid poपूर्णांकer.
	 */
	bad_wr = शून्य;
	rc = ib_post_send(ep->re_id->qp, first, &bad_wr);

	/* The final LOCAL_INV WR in the chain is supposed to
	 * करो the wake. If it was never posted, the wake will
	 * not happen, so करोn't रुको in that हाल.
	 */
	अगर (bad_wr != first)
		रुको_क्रम_completion(&mr->mr_linv_करोne);
	अगर (!rc)
		वापस;

	/* On error, the MRs get destroyed once the QP has drained. */
	trace_xprtrdma_post_linv_err(req, rc);
पूर्ण

/**
 * frwr_wc_localinv_करोne - Invoked by RDMA provider क्रम a संकेतed LOCAL_INV WC
 * @cq:	completion queue
 * @wc:	WCE क्रम a completed LocalInv WR
 *
 */
अटल व्योम frwr_wc_localinv_करोne(काष्ठा ib_cq *cq, काष्ठा ib_wc *wc)
अणु
	काष्ठा ib_cqe *cqe = wc->wr_cqe;
	काष्ठा rpcrdma_mr *mr = container_of(cqe, काष्ठा rpcrdma_mr, mr_cqe);
	काष्ठा rpcrdma_rep *rep;

	/* WARNING: Only wr_cqe and status are reliable at this poपूर्णांक */
	trace_xprtrdma_wc_li_करोne(wc, &mr->mr_cid);

	/* Ensure that @rep is generated beक्रमe the MR is released */
	rep = mr->mr_req->rl_reply;
	smp_rmb();

	अगर (wc->status != IB_WC_SUCCESS) अणु
		अगर (rep)
			rpcrdma_unpin_rqst(rep);
		rpcrdma_flush_disconnect(cq->cq_context, wc);
		वापस;
	पूर्ण
	frwr_mr_put(mr);
	rpcrdma_complete_rqst(rep);
पूर्ण

/**
 * frwr_unmap_async - invalidate memory regions that were रेजिस्टरed क्रम @req
 * @r_xprt: controlling transport instance
 * @req: rpcrdma_req with a non-empty list of MRs to process
 *
 * This guarantees that रेजिस्टरed MRs are properly fenced from the
 * server beक्रमe the RPC consumer accesses the data in them. It also
 * ensures proper Send flow control: waking the next RPC रुकोs until
 * this RPC has relinquished all its Send Queue entries.
 */
व्योम frwr_unmap_async(काष्ठा rpcrdma_xprt *r_xprt, काष्ठा rpcrdma_req *req)
अणु
	काष्ठा ib_send_wr *first, *last, **prev;
	काष्ठा rpcrdma_ep *ep = r_xprt->rx_ep;
	काष्ठा rpcrdma_mr *mr;
	पूर्णांक rc;

	/* Chain the LOCAL_INV Work Requests and post them with
	 * a single ib_post_send() call.
	 */
	prev = &first;
	जबतक ((mr = rpcrdma_mr_pop(&req->rl_रेजिस्टरed))) अणु

		trace_xprtrdma_mr_localinv(mr);
		r_xprt->rx_stats.local_inv_needed++;

		last = &mr->mr_invwr;
		last->next = शून्य;
		last->wr_cqe = &mr->mr_cqe;
		last->sg_list = शून्य;
		last->num_sge = 0;
		last->opcode = IB_WR_LOCAL_INV;
		last->send_flags = IB_SEND_SIGNALED;
		last->ex.invalidate_rkey = mr->mr_handle;

		last->wr_cqe->करोne = frwr_wc_localinv;

		*prev = last;
		prev = &last->next;
	पूर्ण

	/* Strong send queue ordering guarantees that when the
	 * last WR in the chain completes, all WRs in the chain
	 * are complete. The last completion will wake up the
	 * RPC रुकोer.
	 */
	last->wr_cqe->करोne = frwr_wc_localinv_करोne;

	/* Transport disconnect drains the receive CQ beक्रमe it
	 * replaces the QP. The RPC reply handler won't call us
	 * unless re_id->qp is a valid poपूर्णांकer.
	 */
	rc = ib_post_send(ep->re_id->qp, first, शून्य);
	अगर (!rc)
		वापस;

	/* On error, the MRs get destroyed once the QP has drained. */
	trace_xprtrdma_post_linv_err(req, rc);

	/* The final LOCAL_INV WR in the chain is supposed to
	 * करो the wake. If it was never posted, the wake करोes
	 * not happen. Unpin the rqst in preparation क्रम its
	 * retransmission.
	 */
	rpcrdma_unpin_rqst(req->rl_reply);
पूर्ण
