<शैली गुरु>
/*
 * Copyright (c) 2009-2010 Chelsio, Inc. All rights reserved.
 *
 * This software is available to you under a choice of one of two
 * licenses.  You may choose to be licensed under the terms of the GNU
 * General Public License (GPL) Version 2, available from the file
 * COPYING in the मुख्य directory of this source tree, or the
 * OpenIB.org BSD license below:
 *
 *     Redistribution and use in source and binary क्रमms, with or
 *     without modअगरication, are permitted provided that the following
 *     conditions are met:
 *
 *      - Redistributions of source code must retain the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer.
 *
 *      - Redistributions in binary क्रमm must reproduce the above
 *	  copyright notice, this list of conditions and the following
 *	  disclaimer in the करोcumentation and/or other materials
 *	  provided with the distribution.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
 * BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
 * ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

#समावेश <rdma/uverbs_ioctl.h>

#समावेश "iw_cxgb4.h"

अटल व्योम destroy_cq(काष्ठा c4iw_rdev *rdev, काष्ठा t4_cq *cq,
		       काष्ठा c4iw_dev_ucontext *uctx, काष्ठा sk_buff *skb,
		       काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	काष्ठा fw_ri_res_wr *res_wr;
	काष्ठा fw_ri_res *res;
	पूर्णांक wr_len;

	wr_len = माप(*res_wr) + माप(*res);
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, 0);

	res_wr = __skb_put_zero(skb, wr_len);
	res_wr->op_nres = cpu_to_be32(
			FW_WR_OP_V(FW_RI_RES_WR) |
			FW_RI_RES_WR_NRES_V(1) |
			FW_WR_COMPL_F);
	res_wr->len16_pkd = cpu_to_be32(DIV_ROUND_UP(wr_len, 16));
	res_wr->cookie = (uपूर्णांकptr_t)wr_रुकोp;
	res = res_wr->res;
	res->u.cq.restype = FW_RI_RES_TYPE_CQ;
	res->u.cq.op = FW_RI_RES_OP_RESET;
	res->u.cq.iqid = cpu_to_be32(cq->cqid);

	c4iw_init_wr_रुको(wr_रुकोp);
	c4iw_ref_send_रुको(rdev, skb, wr_रुकोp, 0, 0, __func__);

	kमुक्त(cq->sw_queue);
	dma_मुक्त_coherent(&(rdev->lldi.pdev->dev),
			  cq->memsize, cq->queue,
			  dma_unmap_addr(cq, mapping));
	c4iw_put_cqid(rdev, cq->cqid, uctx);
पूर्ण

अटल पूर्णांक create_cq(काष्ठा c4iw_rdev *rdev, काष्ठा t4_cq *cq,
		     काष्ठा c4iw_dev_ucontext *uctx,
		     काष्ठा c4iw_wr_रुको *wr_रुकोp)
अणु
	काष्ठा fw_ri_res_wr *res_wr;
	काष्ठा fw_ri_res *res;
	पूर्णांक wr_len;
	पूर्णांक user = (uctx != &rdev->uctx);
	पूर्णांक ret;
	काष्ठा sk_buff *skb;
	काष्ठा c4iw_ucontext *ucontext = शून्य;

	अगर (user)
		ucontext = container_of(uctx, काष्ठा c4iw_ucontext, uctx);

	cq->cqid = c4iw_get_cqid(rdev, uctx);
	अगर (!cq->cqid) अणु
		ret = -ENOMEM;
		जाओ err1;
	पूर्ण

	अगर (!user) अणु
		cq->sw_queue = kzalloc(cq->memsize, GFP_KERNEL);
		अगर (!cq->sw_queue) अणु
			ret = -ENOMEM;
			जाओ err2;
		पूर्ण
	पूर्ण
	cq->queue = dma_alloc_coherent(&rdev->lldi.pdev->dev, cq->memsize,
				       &cq->dma_addr, GFP_KERNEL);
	अगर (!cq->queue) अणु
		ret = -ENOMEM;
		जाओ err3;
	पूर्ण
	dma_unmap_addr_set(cq, mapping, cq->dma_addr);

	अगर (user && ucontext->is_32b_cqe) अणु
		cq->qp_errp = &((काष्ठा t4_status_page *)
		((u8 *)cq->queue + (cq->size - 1) *
		 (माप(*cq->queue) / 2)))->qp_err;
	पूर्ण अन्यथा अणु
		cq->qp_errp = &((काष्ठा t4_status_page *)
		((u8 *)cq->queue + (cq->size - 1) *
		 माप(*cq->queue)))->qp_err;
	पूर्ण

	/* build fw_ri_res_wr */
	wr_len = माप(*res_wr) + माप(*res);

	skb = alloc_skb(wr_len, GFP_KERNEL);
	अगर (!skb) अणु
		ret = -ENOMEM;
		जाओ err4;
	पूर्ण
	set_wr_txq(skb, CPL_PRIORITY_CONTROL, 0);

	res_wr = __skb_put_zero(skb, wr_len);
	res_wr->op_nres = cpu_to_be32(
			FW_WR_OP_V(FW_RI_RES_WR) |
			FW_RI_RES_WR_NRES_V(1) |
			FW_WR_COMPL_F);
	res_wr->len16_pkd = cpu_to_be32(DIV_ROUND_UP(wr_len, 16));
	res_wr->cookie = (uपूर्णांकptr_t)wr_रुकोp;
	res = res_wr->res;
	res->u.cq.restype = FW_RI_RES_TYPE_CQ;
	res->u.cq.op = FW_RI_RES_OP_WRITE;
	res->u.cq.iqid = cpu_to_be32(cq->cqid);
	res->u.cq.iqandst_to_iqandstindex = cpu_to_be32(
			FW_RI_RES_WR_IQANUS_V(0) |
			FW_RI_RES_WR_IQANUD_V(1) |
			FW_RI_RES_WR_IQANDST_F |
			FW_RI_RES_WR_IQANDSTINDEX_V(
				rdev->lldi.ciq_ids[cq->vector]));
	res->u.cq.iqdroprss_to_iqesize = cpu_to_be16(
			FW_RI_RES_WR_IQDROPRSS_F |
			FW_RI_RES_WR_IQPCIECH_V(2) |
			FW_RI_RES_WR_IQINTCNTTHRESH_V(0) |
			FW_RI_RES_WR_IQO_F |
			((user && ucontext->is_32b_cqe) ?
			 FW_RI_RES_WR_IQESIZE_V(1) :
			 FW_RI_RES_WR_IQESIZE_V(2)));
	res->u.cq.iqsize = cpu_to_be16(cq->size);
	res->u.cq.iqaddr = cpu_to_be64(cq->dma_addr);

	c4iw_init_wr_रुको(wr_रुकोp);
	ret = c4iw_ref_send_रुको(rdev, skb, wr_रुकोp, 0, 0, __func__);
	अगर (ret)
		जाओ err4;

	cq->gen = 1;
	cq->gts = rdev->lldi.gts_reg;
	cq->rdev = rdev;

	cq->bar2_va = c4iw_bar2_addrs(rdev, cq->cqid, CXGB4_BAR2_QTYPE_INGRESS,
				      &cq->bar2_qid,
				      user ? &cq->bar2_pa : शून्य);
	अगर (user && !cq->bar2_pa) अणु
		pr_warn("%s: cqid %u not in BAR2 range\n",
			pci_name(rdev->lldi.pdev), cq->cqid);
		ret = -EINVAL;
		जाओ err4;
	पूर्ण
	वापस 0;
err4:
	dma_मुक्त_coherent(&rdev->lldi.pdev->dev, cq->memsize, cq->queue,
			  dma_unmap_addr(cq, mapping));
err3:
	kमुक्त(cq->sw_queue);
err2:
	c4iw_put_cqid(rdev, cq->cqid, uctx);
err1:
	वापस ret;
पूर्ण

अटल व्योम insert_recv_cqe(काष्ठा t4_wq *wq, काष्ठा t4_cq *cq, u32 srqidx)
अणु
	काष्ठा t4_cqe cqe;

	pr_debug("wq %p cq %p sw_cidx %u sw_pidx %u\n",
		 wq, cq, cq->sw_cidx, cq->sw_pidx);
	स_रखो(&cqe, 0, माप(cqe));
	cqe.header = cpu_to_be32(CQE_STATUS_V(T4_ERR_SWFLUSH) |
				 CQE_OPCODE_V(FW_RI_SEND) |
				 CQE_TYPE_V(0) |
				 CQE_SWCQE_V(1) |
				 CQE_QPID_V(wq->sq.qid));
	cqe.bits_type_ts = cpu_to_be64(CQE_GENBIT_V((u64)cq->gen));
	अगर (srqidx)
		cqe.u.srcqe.असल_rqe_idx = cpu_to_be32(srqidx);
	cq->sw_queue[cq->sw_pidx] = cqe;
	t4_swcq_produce(cq);
पूर्ण

पूर्णांक c4iw_flush_rq(काष्ठा t4_wq *wq, काष्ठा t4_cq *cq, पूर्णांक count)
अणु
	पूर्णांक flushed = 0;
	पूर्णांक in_use = wq->rq.in_use - count;

	pr_debug("wq %p cq %p rq.in_use %u skip count %u\n",
		 wq, cq, wq->rq.in_use, count);
	जबतक (in_use--) अणु
		insert_recv_cqe(wq, cq, 0);
		flushed++;
	पूर्ण
	वापस flushed;
पूर्ण

अटल व्योम insert_sq_cqe(काष्ठा t4_wq *wq, काष्ठा t4_cq *cq,
			  काष्ठा t4_swsqe *swcqe)
अणु
	काष्ठा t4_cqe cqe;

	pr_debug("wq %p cq %p sw_cidx %u sw_pidx %u\n",
		 wq, cq, cq->sw_cidx, cq->sw_pidx);
	स_रखो(&cqe, 0, माप(cqe));
	cqe.header = cpu_to_be32(CQE_STATUS_V(T4_ERR_SWFLUSH) |
				 CQE_OPCODE_V(swcqe->opcode) |
				 CQE_TYPE_V(1) |
				 CQE_SWCQE_V(1) |
				 CQE_QPID_V(wq->sq.qid));
	CQE_WRID_SQ_IDX(&cqe) = swcqe->idx;
	cqe.bits_type_ts = cpu_to_be64(CQE_GENBIT_V((u64)cq->gen));
	cq->sw_queue[cq->sw_pidx] = cqe;
	t4_swcq_produce(cq);
पूर्ण

अटल व्योम advance_oldest_पढ़ो(काष्ठा t4_wq *wq);

पूर्णांक c4iw_flush_sq(काष्ठा c4iw_qp *qhp)
अणु
	पूर्णांक flushed = 0;
	काष्ठा t4_wq *wq = &qhp->wq;
	काष्ठा c4iw_cq *chp = to_c4iw_cq(qhp->ibqp.send_cq);
	काष्ठा t4_cq *cq = &chp->cq;
	पूर्णांक idx;
	काष्ठा t4_swsqe *swsqe;

	अगर (wq->sq.flush_cidx == -1)
		wq->sq.flush_cidx = wq->sq.cidx;
	idx = wq->sq.flush_cidx;
	जबतक (idx != wq->sq.pidx) अणु
		swsqe = &wq->sq.sw_sq[idx];
		swsqe->flushed = 1;
		insert_sq_cqe(wq, cq, swsqe);
		अगर (wq->sq.oldest_पढ़ो == swsqe) अणु
			advance_oldest_पढ़ो(wq);
		पूर्ण
		flushed++;
		अगर (++idx == wq->sq.size)
			idx = 0;
	पूर्ण
	wq->sq.flush_cidx += flushed;
	अगर (wq->sq.flush_cidx >= wq->sq.size)
		wq->sq.flush_cidx -= wq->sq.size;
	वापस flushed;
पूर्ण

अटल व्योम flush_completed_wrs(काष्ठा t4_wq *wq, काष्ठा t4_cq *cq)
अणु
	काष्ठा t4_swsqe *swsqe;
	पूर्णांक cidx;

	अगर (wq->sq.flush_cidx == -1)
		wq->sq.flush_cidx = wq->sq.cidx;
	cidx = wq->sq.flush_cidx;

	जबतक (cidx != wq->sq.pidx) अणु
		swsqe = &wq->sq.sw_sq[cidx];
		अगर (!swsqe->संकेतed) अणु
			अगर (++cidx == wq->sq.size)
				cidx = 0;
		पूर्ण अन्यथा अगर (swsqe->complete) अणु

			/*
			 * Insert this completed cqe पूर्णांकo the swcq.
			 */
			pr_debug("moving cqe into swcq sq idx %u cq idx %u\n",
				 cidx, cq->sw_pidx);
			swsqe->cqe.header |= htonl(CQE_SWCQE_V(1));
			cq->sw_queue[cq->sw_pidx] = swsqe->cqe;
			t4_swcq_produce(cq);
			swsqe->flushed = 1;
			अगर (++cidx == wq->sq.size)
				cidx = 0;
			wq->sq.flush_cidx = cidx;
		पूर्ण अन्यथा
			अवरोध;
	पूर्ण
पूर्ण

अटल व्योम create_पढ़ो_req_cqe(काष्ठा t4_wq *wq, काष्ठा t4_cqe *hw_cqe,
		काष्ठा t4_cqe *पढ़ो_cqe)
अणु
	पढ़ो_cqe->u.scqe.cidx = wq->sq.oldest_पढ़ो->idx;
	पढ़ो_cqe->len = htonl(wq->sq.oldest_पढ़ो->पढ़ो_len);
	पढ़ो_cqe->header = htonl(CQE_QPID_V(CQE_QPID(hw_cqe)) |
			CQE_SWCQE_V(SW_CQE(hw_cqe)) |
			CQE_OPCODE_V(FW_RI_READ_REQ) |
			CQE_TYPE_V(1));
	पढ़ो_cqe->bits_type_ts = hw_cqe->bits_type_ts;
पूर्ण

अटल व्योम advance_oldest_पढ़ो(काष्ठा t4_wq *wq)
अणु

	u32 rptr = wq->sq.oldest_पढ़ो - wq->sq.sw_sq + 1;

	अगर (rptr == wq->sq.size)
		rptr = 0;
	जबतक (rptr != wq->sq.pidx) अणु
		wq->sq.oldest_पढ़ो = &wq->sq.sw_sq[rptr];

		अगर (wq->sq.oldest_पढ़ो->opcode == FW_RI_READ_REQ)
			वापस;
		अगर (++rptr == wq->sq.size)
			rptr = 0;
	पूर्ण
	wq->sq.oldest_पढ़ो = शून्य;
पूर्ण

/*
 * Move all CQEs from the HWCQ पूर्णांकo the SWCQ.
 * Deal with out-of-order and/or completions that complete
 * prior unसंकेतled WRs.
 */
व्योम c4iw_flush_hw_cq(काष्ठा c4iw_cq *chp, काष्ठा c4iw_qp *flush_qhp)
अणु
	काष्ठा t4_cqe *hw_cqe, *swcqe, पढ़ो_cqe;
	काष्ठा c4iw_qp *qhp;
	काष्ठा t4_swsqe *swsqe;
	पूर्णांक ret;

	pr_debug("cqid 0x%x\n", chp->cq.cqid);
	ret = t4_next_hw_cqe(&chp->cq, &hw_cqe);

	/*
	 * This logic is similar to poll_cq(), but not quite the same
	 * unक्रमtunately.  Need to move pertinent HW CQEs to the SW CQ but
	 * also करो any translation magic that poll_cq() normally करोes.
	 */
	जबतक (!ret) अणु
		qhp = get_qhp(chp->rhp, CQE_QPID(hw_cqe));

		/*
		 * drop CQEs with no associated QP
		 */
		अगर (qhp == शून्य)
			जाओ next_cqe;

		अगर (flush_qhp != qhp) अणु
			spin_lock(&qhp->lock);

			अगर (qhp->wq.flushed == 1)
				जाओ next_cqe;
		पूर्ण

		अगर (CQE_OPCODE(hw_cqe) == FW_RI_TERMINATE)
			जाओ next_cqe;

		अगर (CQE_OPCODE(hw_cqe) == FW_RI_READ_RESP) अणु

			/* If we have reached here because of async
			 * event or other error, and have egress error
			 * then drop
			 */
			अगर (CQE_TYPE(hw_cqe) == 1)
				जाओ next_cqe;

			/* drop peer2peer RTR पढ़ोs.
			 */
			अगर (CQE_WRID_STAG(hw_cqe) == 1)
				जाओ next_cqe;

			/*
			 * Eat completions क्रम unसंकेतed पढ़ो WRs.
			 */
			अगर (!qhp->wq.sq.oldest_पढ़ो->संकेतed) अणु
				advance_oldest_पढ़ो(&qhp->wq);
				जाओ next_cqe;
			पूर्ण

			/*
			 * Don't ग_लिखो to the HWCQ, create a new पढ़ो req CQE
			 * in local memory and move it पूर्णांकo the swcq.
			 */
			create_पढ़ो_req_cqe(&qhp->wq, hw_cqe, &पढ़ो_cqe);
			hw_cqe = &पढ़ो_cqe;
			advance_oldest_पढ़ो(&qhp->wq);
		पूर्ण

		/* अगर its a SQ completion, then करो the magic to move all the
		 * unसंकेतed and now in-order completions पूर्णांकo the swcq.
		 */
		अगर (SQ_TYPE(hw_cqe)) अणु
			swsqe = &qhp->wq.sq.sw_sq[CQE_WRID_SQ_IDX(hw_cqe)];
			swsqe->cqe = *hw_cqe;
			swsqe->complete = 1;
			flush_completed_wrs(&qhp->wq, &chp->cq);
		पूर्ण अन्यथा अणु
			swcqe = &chp->cq.sw_queue[chp->cq.sw_pidx];
			*swcqe = *hw_cqe;
			swcqe->header |= cpu_to_be32(CQE_SWCQE_V(1));
			t4_swcq_produce(&chp->cq);
		पूर्ण
next_cqe:
		t4_hwcq_consume(&chp->cq);
		ret = t4_next_hw_cqe(&chp->cq, &hw_cqe);
		अगर (qhp && flush_qhp != qhp)
			spin_unlock(&qhp->lock);
	पूर्ण
पूर्ण

अटल पूर्णांक cqe_completes_wr(काष्ठा t4_cqe *cqe, काष्ठा t4_wq *wq)
अणु
	अगर (DRAIN_CQE(cqe)) अणु
		WARN_ONCE(1, "Unexpected DRAIN CQE qp id %u!\n", wq->sq.qid);
		वापस 0;
	पूर्ण

	अगर (CQE_OPCODE(cqe) == FW_RI_TERMINATE)
		वापस 0;

	अगर ((CQE_OPCODE(cqe) == FW_RI_RDMA_WRITE) && RQ_TYPE(cqe))
		वापस 0;

	अगर ((CQE_OPCODE(cqe) == FW_RI_READ_RESP) && SQ_TYPE(cqe))
		वापस 0;

	अगर (CQE_SEND_OPCODE(cqe) && RQ_TYPE(cqe) && t4_rq_empty(wq))
		वापस 0;
	वापस 1;
पूर्ण

व्योम c4iw_count_rcqes(काष्ठा t4_cq *cq, काष्ठा t4_wq *wq, पूर्णांक *count)
अणु
	काष्ठा t4_cqe *cqe;
	u32 ptr;

	*count = 0;
	pr_debug("count zero %d\n", *count);
	ptr = cq->sw_cidx;
	जबतक (ptr != cq->sw_pidx) अणु
		cqe = &cq->sw_queue[ptr];
		अगर (RQ_TYPE(cqe) && (CQE_OPCODE(cqe) != FW_RI_READ_RESP) &&
		    (CQE_QPID(cqe) == wq->sq.qid) && cqe_completes_wr(cqe, wq))
			(*count)++;
		अगर (++ptr == cq->size)
			ptr = 0;
	पूर्ण
	pr_debug("cq %p count %d\n", cq, *count);
पूर्ण

अटल व्योम post_pending_srq_wrs(काष्ठा t4_srq *srq)
अणु
	काष्ठा t4_srq_pending_wr *pwr;
	u16 idx = 0;

	जबतक (srq->pending_in_use) अणु
		pwr = &srq->pending_wrs[srq->pending_cidx];
		srq->sw_rq[srq->pidx].wr_id = pwr->wr_id;
		srq->sw_rq[srq->pidx].valid = 1;

		pr_debug("%s posting pending cidx %u pidx %u wq_pidx %u in_use %u rq_size %u wr_id %llx\n",
			 __func__,
			 srq->cidx, srq->pidx, srq->wq_pidx,
			 srq->in_use, srq->size,
			 (अचिन्हित दीर्घ दीर्घ)pwr->wr_id);

		c4iw_copy_wr_to_srq(srq, &pwr->wqe, pwr->len16);
		t4_srq_consume_pending_wr(srq);
		t4_srq_produce(srq, pwr->len16);
		idx += DIV_ROUND_UP(pwr->len16 * 16, T4_EQ_ENTRY_SIZE);
	पूर्ण

	अगर (idx) अणु
		t4_ring_srq_db(srq, idx, pwr->len16, &pwr->wqe);
		srq->queue[srq->size].status.host_wq_pidx =
			srq->wq_pidx;
	पूर्ण
पूर्ण

अटल u64 reap_srq_cqe(काष्ठा t4_cqe *hw_cqe, काष्ठा t4_srq *srq)
अणु
	पूर्णांक rel_idx = CQE_ABS_RQE_IDX(hw_cqe) - srq->rqt_असल_idx;
	u64 wr_id;

	srq->sw_rq[rel_idx].valid = 0;
	wr_id = srq->sw_rq[rel_idx].wr_id;

	अगर (rel_idx == srq->cidx) अणु
		pr_debug("%s in order cqe rel_idx %u cidx %u pidx %u wq_pidx %u in_use %u rq_size %u wr_id %llx\n",
			 __func__, rel_idx, srq->cidx, srq->pidx,
			 srq->wq_pidx, srq->in_use, srq->size,
			 (अचिन्हित दीर्घ दीर्घ)srq->sw_rq[rel_idx].wr_id);
		t4_srq_consume(srq);
		जबतक (srq->ooo_count && !srq->sw_rq[srq->cidx].valid) अणु
			pr_debug("%s eat ooo cidx %u pidx %u wq_pidx %u in_use %u rq_size %u ooo_count %u wr_id %llx\n",
				 __func__, srq->cidx, srq->pidx,
				 srq->wq_pidx, srq->in_use,
				 srq->size, srq->ooo_count,
				 (अचिन्हित दीर्घ दीर्घ)
				 srq->sw_rq[srq->cidx].wr_id);
			t4_srq_consume_ooo(srq);
		पूर्ण
		अगर (srq->ooo_count == 0 && srq->pending_in_use)
			post_pending_srq_wrs(srq);
	पूर्ण अन्यथा अणु
		pr_debug("%s ooo cqe rel_idx %u cidx %u pidx %u wq_pidx %u in_use %u rq_size %u ooo_count %u wr_id %llx\n",
			 __func__, rel_idx, srq->cidx,
			 srq->pidx, srq->wq_pidx,
			 srq->in_use, srq->size,
			 srq->ooo_count,
			 (अचिन्हित दीर्घ दीर्घ)srq->sw_rq[rel_idx].wr_id);
		t4_srq_produce_ooo(srq);
	पूर्ण
	वापस wr_id;
पूर्ण

/*
 * poll_cq
 *
 * Caller must:
 *     check the validity of the first CQE,
 *     supply the wq assicated with the qpid.
 *
 * credit: cq credit to वापस to sge.
 * cqe_flushed: 1 अगरf the CQE is flushed.
 * cqe: copy of the polled CQE.
 *
 * वापस value:
 *    0		    CQE वापसed ok.
 *    -EAGAIN       CQE skipped, try again.
 *    -EOVERFLOW    CQ overflow detected.
 */
अटल पूर्णांक poll_cq(काष्ठा t4_wq *wq, काष्ठा t4_cq *cq, काष्ठा t4_cqe *cqe,
		   u8 *cqe_flushed, u64 *cookie, u32 *credit,
		   काष्ठा t4_srq *srq)
अणु
	पूर्णांक ret = 0;
	काष्ठा t4_cqe *hw_cqe, पढ़ो_cqe;

	*cqe_flushed = 0;
	*credit = 0;
	ret = t4_next_cqe(cq, &hw_cqe);
	अगर (ret)
		वापस ret;

	pr_debug("CQE OVF %u qpid 0x%0x genbit %u type %u status 0x%0x opcode 0x%0x len 0x%0x wrid_hi_stag 0x%x wrid_low_msn 0x%x\n",
		 CQE_OVFBIT(hw_cqe), CQE_QPID(hw_cqe),
		 CQE_GENBIT(hw_cqe), CQE_TYPE(hw_cqe), CQE_STATUS(hw_cqe),
		 CQE_OPCODE(hw_cqe), CQE_LEN(hw_cqe), CQE_WRID_HI(hw_cqe),
		 CQE_WRID_LOW(hw_cqe));

	/*
	 * skip cqe's not affiliated with a QP.
	 */
	अगर (wq == शून्य) अणु
		ret = -EAGAIN;
		जाओ skip_cqe;
	पूर्ण

	/*
	* skip hw cqe's अगर the wq is flushed.
	*/
	अगर (wq->flushed && !SW_CQE(hw_cqe)) अणु
		ret = -EAGAIN;
		जाओ skip_cqe;
	पूर्ण

	/*
	 * skip TERMINATE cqes...
	 */
	अगर (CQE_OPCODE(hw_cqe) == FW_RI_TERMINATE) अणु
		ret = -EAGAIN;
		जाओ skip_cqe;
	पूर्ण

	/*
	 * Special cqe क्रम drain WR completions...
	 */
	अगर (DRAIN_CQE(hw_cqe)) अणु
		*cookie = CQE_DRAIN_COOKIE(hw_cqe);
		*cqe = *hw_cqe;
		जाओ skip_cqe;
	पूर्ण

	/*
	 * Gotta tweak READ completions:
	 *	1) the cqe करोesn't contain the sq_wptr from the wr.
	 *	2) opcode not reflected from the wr.
	 *	3) पढ़ो_len not reflected from the wr.
	 *	4) cq_type is RQ_TYPE not SQ_TYPE.
	 */
	अगर (RQ_TYPE(hw_cqe) && (CQE_OPCODE(hw_cqe) == FW_RI_READ_RESP)) अणु

		/* If we have reached here because of async
		 * event or other error, and have egress error
		 * then drop
		 */
		अगर (CQE_TYPE(hw_cqe) == 1) अणु
			अगर (CQE_STATUS(hw_cqe))
				t4_set_wq_in_error(wq, 0);
			ret = -EAGAIN;
			जाओ skip_cqe;
		पूर्ण

		/* If this is an unsolicited पढ़ो response, then the पढ़ो
		 * was generated by the kernel driver as part of peer-2-peer
		 * connection setup.  So ignore the completion.
		 */
		अगर (CQE_WRID_STAG(hw_cqe) == 1) अणु
			अगर (CQE_STATUS(hw_cqe))
				t4_set_wq_in_error(wq, 0);
			ret = -EAGAIN;
			जाओ skip_cqe;
		पूर्ण

		/*
		 * Eat completions क्रम unसंकेतed पढ़ो WRs.
		 */
		अगर (!wq->sq.oldest_पढ़ो->संकेतed) अणु
			advance_oldest_पढ़ो(wq);
			ret = -EAGAIN;
			जाओ skip_cqe;
		पूर्ण

		/*
		 * Don't ग_लिखो to the HWCQ, so create a new पढ़ो req CQE
		 * in local memory.
		 */
		create_पढ़ो_req_cqe(wq, hw_cqe, &पढ़ो_cqe);
		hw_cqe = &पढ़ो_cqe;
		advance_oldest_पढ़ो(wq);
	पूर्ण

	अगर (CQE_STATUS(hw_cqe) || t4_wq_in_error(wq)) अणु
		*cqe_flushed = (CQE_STATUS(hw_cqe) == T4_ERR_SWFLUSH);
		t4_set_wq_in_error(wq, 0);
	पूर्ण

	/*
	 * RECV completion.
	 */
	अगर (RQ_TYPE(hw_cqe)) अणु

		/*
		 * HW only validates 4 bits of MSN.  So we must validate that
		 * the MSN in the SEND is the next expected MSN.  If its not,
		 * then we complete this with T4_ERR_MSN and mark the wq in
		 * error.
		 */
		अगर (unlikely(!CQE_STATUS(hw_cqe) &&
			     CQE_WRID_MSN(hw_cqe) != wq->rq.msn)) अणु
			t4_set_wq_in_error(wq, 0);
			hw_cqe->header |= cpu_to_be32(CQE_STATUS_V(T4_ERR_MSN));
		पूर्ण
		जाओ proc_cqe;
	पूर्ण

	/*
	 * If we get here its a send completion.
	 *
	 * Handle out of order completion. These get stuffed
	 * in the SW SQ. Then the SW SQ is walked to move any
	 * now in-order completions पूर्णांकo the SW CQ.  This handles
	 * 2 हालs:
	 *	1) reaping unसंकेतed WRs when the first subsequent
	 *	   संकेतed WR is completed.
	 *	2) out of order पढ़ो completions.
	 */
	अगर (!SW_CQE(hw_cqe) && (CQE_WRID_SQ_IDX(hw_cqe) != wq->sq.cidx)) अणु
		काष्ठा t4_swsqe *swsqe;

		pr_debug("out of order completion going in sw_sq at idx %u\n",
			 CQE_WRID_SQ_IDX(hw_cqe));
		swsqe = &wq->sq.sw_sq[CQE_WRID_SQ_IDX(hw_cqe)];
		swsqe->cqe = *hw_cqe;
		swsqe->complete = 1;
		ret = -EAGAIN;
		जाओ flush_wq;
	पूर्ण

proc_cqe:
	*cqe = *hw_cqe;

	/*
	 * Reap the associated WR(s) that are मुक्तd up with this
	 * completion.
	 */
	अगर (SQ_TYPE(hw_cqe)) अणु
		पूर्णांक idx = CQE_WRID_SQ_IDX(hw_cqe);

		/*
		* Account क्रम any unसंकेतed completions completed by
		* this संकेतed completion.  In this हाल, cidx poपूर्णांकs
		* to the first unसंकेतed one, and idx poपूर्णांकs to the
		* संकेतed one.  So adjust in_use based on this delta.
		* अगर this is not completing any अचिन्हित wrs, then the
		* delta will be 0. Handle wrapping also!
		*/
		अगर (idx < wq->sq.cidx)
			wq->sq.in_use -= wq->sq.size + idx - wq->sq.cidx;
		अन्यथा
			wq->sq.in_use -= idx - wq->sq.cidx;

		wq->sq.cidx = (uपूर्णांक16_t)idx;
		pr_debug("completing sq idx %u\n", wq->sq.cidx);
		*cookie = wq->sq.sw_sq[wq->sq.cidx].wr_id;
		अगर (c4iw_wr_log)
			c4iw_log_wr_stats(wq, hw_cqe);
		t4_sq_consume(wq);
	पूर्ण अन्यथा अणु
		अगर (!srq) अणु
			pr_debug("completing rq idx %u\n", wq->rq.cidx);
			*cookie = wq->rq.sw_rq[wq->rq.cidx].wr_id;
			अगर (c4iw_wr_log)
				c4iw_log_wr_stats(wq, hw_cqe);
			t4_rq_consume(wq);
		पूर्ण अन्यथा अणु
			*cookie = reap_srq_cqe(hw_cqe, srq);
		पूर्ण
		wq->rq.msn++;
		जाओ skip_cqe;
	पूर्ण

flush_wq:
	/*
	 * Flush any completed cqes that are now in-order.
	 */
	flush_completed_wrs(wq, cq);

skip_cqe:
	अगर (SW_CQE(hw_cqe)) अणु
		pr_debug("cq %p cqid 0x%x skip sw cqe cidx %u\n",
			 cq, cq->cqid, cq->sw_cidx);
		t4_swcq_consume(cq);
	पूर्ण अन्यथा अणु
		pr_debug("cq %p cqid 0x%x skip hw cqe cidx %u\n",
			 cq, cq->cqid, cq->cidx);
		t4_hwcq_consume(cq);
	पूर्ण
	वापस ret;
पूर्ण

अटल पूर्णांक __c4iw_poll_cq_one(काष्ठा c4iw_cq *chp, काष्ठा c4iw_qp *qhp,
			      काष्ठा ib_wc *wc, काष्ठा c4iw_srq *srq)
अणु
	काष्ठा t4_cqe cqe;
	काष्ठा t4_wq *wq = qhp ? &qhp->wq : शून्य;
	u32 credit = 0;
	u8 cqe_flushed;
	u64 cookie = 0;
	पूर्णांक ret;

	ret = poll_cq(wq, &(chp->cq), &cqe, &cqe_flushed, &cookie, &credit,
		      srq ? &srq->wq : शून्य);
	अगर (ret)
		जाओ out;

	wc->wr_id = cookie;
	wc->qp = qhp ? &qhp->ibqp : शून्य;
	wc->venकरोr_err = CQE_STATUS(&cqe);
	wc->wc_flags = 0;

	/*
	 * Simulate a SRQ_LIMIT_REACHED HW notअगरication अगर required.
	 */
	अगर (srq && !(srq->flags & T4_SRQ_LIMIT_SUPPORT) && srq->armed &&
	    srq->wq.in_use < srq->srq_limit)
		c4iw_dispatch_srq_limit_reached_event(srq);

	pr_debug("qpid 0x%x type %d opcode %d status 0x%x len %u wrid hi 0x%x lo 0x%x cookie 0x%llx\n",
		 CQE_QPID(&cqe),
		 CQE_TYPE(&cqe), CQE_OPCODE(&cqe),
		 CQE_STATUS(&cqe), CQE_LEN(&cqe),
		 CQE_WRID_HI(&cqe), CQE_WRID_LOW(&cqe),
		 (अचिन्हित दीर्घ दीर्घ)cookie);

	अगर (CQE_TYPE(&cqe) == 0) अणु
		अगर (!CQE_STATUS(&cqe))
			wc->byte_len = CQE_LEN(&cqe);
		अन्यथा
			wc->byte_len = 0;

		चयन (CQE_OPCODE(&cqe)) अणु
		हाल FW_RI_SEND:
			wc->opcode = IB_WC_RECV;
			अवरोध;
		हाल FW_RI_SEND_WITH_INV:
		हाल FW_RI_SEND_WITH_SE_INV:
			wc->opcode = IB_WC_RECV;
			wc->ex.invalidate_rkey = CQE_WRID_STAG(&cqe);
			wc->wc_flags |= IB_WC_WITH_INVALIDATE;
			c4iw_invalidate_mr(qhp->rhp, wc->ex.invalidate_rkey);
			अवरोध;
		हाल FW_RI_WRITE_IMMEDIATE:
			wc->opcode = IB_WC_RECV_RDMA_WITH_IMM;
			wc->ex.imm_data = CQE_IMM_DATA(&cqe);
			wc->wc_flags |= IB_WC_WITH_IMM;
			अवरोध;
		शेष:
			pr_err("Unexpected opcode %d in the CQE received for QPID=0x%0x\n",
			       CQE_OPCODE(&cqe), CQE_QPID(&cqe));
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण अन्यथा अणु
		चयन (CQE_OPCODE(&cqe)) अणु
		हाल FW_RI_WRITE_IMMEDIATE:
		हाल FW_RI_RDMA_WRITE:
			wc->opcode = IB_WC_RDMA_WRITE;
			अवरोध;
		हाल FW_RI_READ_REQ:
			wc->opcode = IB_WC_RDMA_READ;
			wc->byte_len = CQE_LEN(&cqe);
			अवरोध;
		हाल FW_RI_SEND_WITH_INV:
		हाल FW_RI_SEND_WITH_SE_INV:
			wc->opcode = IB_WC_SEND;
			wc->wc_flags |= IB_WC_WITH_INVALIDATE;
			अवरोध;
		हाल FW_RI_SEND:
		हाल FW_RI_SEND_WITH_SE:
			wc->opcode = IB_WC_SEND;
			अवरोध;

		हाल FW_RI_LOCAL_INV:
			wc->opcode = IB_WC_LOCAL_INV;
			अवरोध;
		हाल FW_RI_FAST_REGISTER:
			wc->opcode = IB_WC_REG_MR;

			/* Invalidate the MR अगर the fastreg failed */
			अगर (CQE_STATUS(&cqe) != T4_ERR_SUCCESS)
				c4iw_invalidate_mr(qhp->rhp,
						   CQE_WRID_FR_STAG(&cqe));
			अवरोध;
		शेष:
			pr_err("Unexpected opcode %d in the CQE received for QPID=0x%0x\n",
			       CQE_OPCODE(&cqe), CQE_QPID(&cqe));
			ret = -EINVAL;
			जाओ out;
		पूर्ण
	पूर्ण

	अगर (cqe_flushed)
		wc->status = IB_WC_WR_FLUSH_ERR;
	अन्यथा अणु

		चयन (CQE_STATUS(&cqe)) अणु
		हाल T4_ERR_SUCCESS:
			wc->status = IB_WC_SUCCESS;
			अवरोध;
		हाल T4_ERR_STAG:
			wc->status = IB_WC_LOC_ACCESS_ERR;
			अवरोध;
		हाल T4_ERR_PDID:
			wc->status = IB_WC_LOC_PROT_ERR;
			अवरोध;
		हाल T4_ERR_QPID:
		हाल T4_ERR_ACCESS:
			wc->status = IB_WC_LOC_ACCESS_ERR;
			अवरोध;
		हाल T4_ERR_WRAP:
			wc->status = IB_WC_GENERAL_ERR;
			अवरोध;
		हाल T4_ERR_BOUND:
			wc->status = IB_WC_LOC_LEN_ERR;
			अवरोध;
		हाल T4_ERR_INVALIDATE_SHARED_MR:
		हाल T4_ERR_INVALIDATE_MR_WITH_MW_BOUND:
			wc->status = IB_WC_MW_BIND_ERR;
			अवरोध;
		हाल T4_ERR_CRC:
		हाल T4_ERR_MARKER:
		हाल T4_ERR_PDU_LEN_ERR:
		हाल T4_ERR_OUT_OF_RQE:
		हाल T4_ERR_DDP_VERSION:
		हाल T4_ERR_RDMA_VERSION:
		हाल T4_ERR_DDP_QUEUE_NUM:
		हाल T4_ERR_MSN:
		हाल T4_ERR_TBIT:
		हाल T4_ERR_MO:
		हाल T4_ERR_MSN_RANGE:
		हाल T4_ERR_IRD_OVERFLOW:
		हाल T4_ERR_OPCODE:
		हाल T4_ERR_INTERNAL_ERR:
			wc->status = IB_WC_FATAL_ERR;
			अवरोध;
		हाल T4_ERR_SWFLUSH:
			wc->status = IB_WC_WR_FLUSH_ERR;
			अवरोध;
		शेष:
			pr_err("Unexpected cqe_status 0x%x for QPID=0x%0x\n",
			       CQE_STATUS(&cqe), CQE_QPID(&cqe));
			wc->status = IB_WC_FATAL_ERR;
		पूर्ण
	पूर्ण
out:
	वापस ret;
पूर्ण

/*
 * Get one cq entry from c4iw and map it to खोलोib.
 *
 * Returns:
 *	0			cqe वापसed
 *	-ENODATA		EMPTY;
 *	-EAGAIN			caller must try again
 *	any other -त्रुटि_सं	fatal error
 */
अटल पूर्णांक c4iw_poll_cq_one(काष्ठा c4iw_cq *chp, काष्ठा ib_wc *wc)
अणु
	काष्ठा c4iw_srq *srq = शून्य;
	काष्ठा c4iw_qp *qhp = शून्य;
	काष्ठा t4_cqe *rd_cqe;
	पूर्णांक ret;

	ret = t4_next_cqe(&chp->cq, &rd_cqe);

	अगर (ret)
		वापस ret;

	qhp = get_qhp(chp->rhp, CQE_QPID(rd_cqe));
	अगर (qhp) अणु
		spin_lock(&qhp->lock);
		srq = qhp->srq;
		अगर (srq)
			spin_lock(&srq->lock);
		ret = __c4iw_poll_cq_one(chp, qhp, wc, srq);
		spin_unlock(&qhp->lock);
		अगर (srq)
			spin_unlock(&srq->lock);
	पूर्ण अन्यथा अणु
		ret = __c4iw_poll_cq_one(chp, शून्य, wc, शून्य);
	पूर्ण
	वापस ret;
पूर्ण

पूर्णांक c4iw_poll_cq(काष्ठा ib_cq *ibcq, पूर्णांक num_entries, काष्ठा ib_wc *wc)
अणु
	काष्ठा c4iw_cq *chp;
	अचिन्हित दीर्घ flags;
	पूर्णांक npolled;
	पूर्णांक err = 0;

	chp = to_c4iw_cq(ibcq);

	spin_lock_irqsave(&chp->lock, flags);
	क्रम (npolled = 0; npolled < num_entries; ++npolled) अणु
		करो अणु
			err = c4iw_poll_cq_one(chp, wc + npolled);
		पूर्ण जबतक (err == -EAGAIN);
		अगर (err)
			अवरोध;
	पूर्ण
	spin_unlock_irqrestore(&chp->lock, flags);
	वापस !err || err == -ENODATA ? npolled : err;
पूर्ण

पूर्णांक c4iw_destroy_cq(काष्ठा ib_cq *ib_cq, काष्ठा ib_udata *udata)
अणु
	काष्ठा c4iw_cq *chp;
	काष्ठा c4iw_ucontext *ucontext;

	pr_debug("ib_cq %p\n", ib_cq);
	chp = to_c4iw_cq(ib_cq);

	xa_erase_irq(&chp->rhp->cqs, chp->cq.cqid);
	atomic_dec(&chp->refcnt);
	रुको_event(chp->रुको, !atomic_पढ़ो(&chp->refcnt));

	ucontext = rdma_udata_to_drv_context(udata, काष्ठा c4iw_ucontext,
					     ibucontext);
	destroy_cq(&chp->rhp->rdev, &chp->cq,
		   ucontext ? &ucontext->uctx : &chp->cq.rdev->uctx,
		   chp->destroy_skb, chp->wr_रुकोp);
	c4iw_put_wr_रुको(chp->wr_रुकोp);
	वापस 0;
पूर्ण

पूर्णांक c4iw_create_cq(काष्ठा ib_cq *ibcq, स्थिर काष्ठा ib_cq_init_attr *attr,
		   काष्ठा ib_udata *udata)
अणु
	काष्ठा ib_device *ibdev = ibcq->device;
	पूर्णांक entries = attr->cqe;
	पूर्णांक vector = attr->comp_vector;
	काष्ठा c4iw_dev *rhp = to_c4iw_dev(ibcq->device);
	काष्ठा c4iw_cq *chp = to_c4iw_cq(ibcq);
	काष्ठा c4iw_create_cq ucmd;
	काष्ठा c4iw_create_cq_resp uresp;
	पूर्णांक ret, wr_len;
	माप_प्रकार memsize, hwentries;
	काष्ठा c4iw_mm_entry *mm, *mm2;
	काष्ठा c4iw_ucontext *ucontext = rdma_udata_to_drv_context(
		udata, काष्ठा c4iw_ucontext, ibucontext);

	pr_debug("ib_dev %p entries %d\n", ibdev, entries);
	अगर (attr->flags)
		वापस -EOPNOTSUPP;

	अगर (entries < 1 || entries > ibdev->attrs.max_cqe)
		वापस -EINVAL;

	अगर (vector >= rhp->rdev.lldi.nciq)
		वापस -EINVAL;

	अगर (udata) अणु
		अगर (udata->inlen < माप(ucmd))
			ucontext->is_32b_cqe = 1;
	पूर्ण

	chp->wr_रुकोp = c4iw_alloc_wr_रुको(GFP_KERNEL);
	अगर (!chp->wr_रुकोp) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_chp;
	पूर्ण
	c4iw_init_wr_रुको(chp->wr_रुकोp);

	wr_len = माप(काष्ठा fw_ri_res_wr) + माप(काष्ठा fw_ri_res);
	chp->destroy_skb = alloc_skb(wr_len, GFP_KERNEL);
	अगर (!chp->destroy_skb) अणु
		ret = -ENOMEM;
		जाओ err_मुक्त_wr_रुको;
	पूर्ण

	/* account क्रम the status page. */
	entries++;

	/* IQ needs one extra entry to dअगरferentiate full vs empty. */
	entries++;

	/*
	 * entries must be multiple of 16 क्रम HW.
	 */
	entries = roundup(entries, 16);

	/*
	 * Make actual HW queue 2x to aव्योम cdix_inc overflows.
	 */
	hwentries = min(entries * 2, rhp->rdev.hw_queue.t4_max_iq_size);

	/*
	 * Make HW queue at least 64 entries so GTS updates aren't too
	 * frequent.
	 */
	अगर (hwentries < 64)
		hwentries = 64;

	memsize = hwentries * ((ucontext && ucontext->is_32b_cqe) ?
			(माप(*chp->cq.queue) / 2) : माप(*chp->cq.queue));

	/*
	 * memsize must be a multiple of the page size अगर its a user cq.
	 */
	अगर (udata)
		memsize = roundup(memsize, PAGE_SIZE);

	chp->cq.size = hwentries;
	chp->cq.memsize = memsize;
	chp->cq.vector = vector;

	ret = create_cq(&rhp->rdev, &chp->cq,
			ucontext ? &ucontext->uctx : &rhp->rdev.uctx,
			chp->wr_रुकोp);
	अगर (ret)
		जाओ err_मुक्त_skb;

	chp->rhp = rhp;
	chp->cq.size--;				/* status page */
	chp->ibcq.cqe = entries - 2;
	spin_lock_init(&chp->lock);
	spin_lock_init(&chp->comp_handler_lock);
	atomic_set(&chp->refcnt, 1);
	init_रुकोqueue_head(&chp->रुको);
	ret = xa_insert_irq(&rhp->cqs, chp->cq.cqid, chp, GFP_KERNEL);
	अगर (ret)
		जाओ err_destroy_cq;

	अगर (ucontext) अणु
		ret = -ENOMEM;
		mm = kदो_स्मृति(माप(*mm), GFP_KERNEL);
		अगर (!mm)
			जाओ err_हटाओ_handle;
		mm2 = kदो_स्मृति(माप(*mm2), GFP_KERNEL);
		अगर (!mm2)
			जाओ err_मुक्त_mm;

		स_रखो(&uresp, 0, माप(uresp));
		uresp.qid_mask = rhp->rdev.cqmask;
		uresp.cqid = chp->cq.cqid;
		uresp.size = chp->cq.size;
		uresp.memsize = chp->cq.memsize;
		spin_lock(&ucontext->mmap_lock);
		uresp.key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		uresp.gts_key = ucontext->key;
		ucontext->key += PAGE_SIZE;
		/* communicate to the userspace that
		 * kernel driver supports 64B CQE
		 */
		uresp.flags |= C4IW_64B_CQE;

		spin_unlock(&ucontext->mmap_lock);
		ret = ib_copy_to_udata(udata, &uresp,
				       ucontext->is_32b_cqe ?
				       माप(uresp) - माप(uresp.flags) :
				       माप(uresp));
		अगर (ret)
			जाओ err_मुक्त_mm2;

		mm->key = uresp.key;
		mm->addr = virt_to_phys(chp->cq.queue);
		mm->len = chp->cq.memsize;
		insert_mmap(ucontext, mm);

		mm2->key = uresp.gts_key;
		mm2->addr = chp->cq.bar2_pa;
		mm2->len = PAGE_SIZE;
		insert_mmap(ucontext, mm2);
	पूर्ण

	pr_debug("cqid 0x%0x chp %p size %u memsize %zu, dma_addr %pad\n",
		 chp->cq.cqid, chp, chp->cq.size, chp->cq.memsize,
		 &chp->cq.dma_addr);
	वापस 0;
err_मुक्त_mm2:
	kमुक्त(mm2);
err_मुक्त_mm:
	kमुक्त(mm);
err_हटाओ_handle:
	xa_erase_irq(&rhp->cqs, chp->cq.cqid);
err_destroy_cq:
	destroy_cq(&chp->rhp->rdev, &chp->cq,
		   ucontext ? &ucontext->uctx : &rhp->rdev.uctx,
		   chp->destroy_skb, chp->wr_रुकोp);
err_मुक्त_skb:
	kमुक्त_skb(chp->destroy_skb);
err_मुक्त_wr_रुको:
	c4iw_put_wr_रुको(chp->wr_रुकोp);
err_मुक्त_chp:
	वापस ret;
पूर्ण

पूर्णांक c4iw_arm_cq(काष्ठा ib_cq *ibcq, क्रमागत ib_cq_notअगरy_flags flags)
अणु
	काष्ठा c4iw_cq *chp;
	पूर्णांक ret = 0;
	अचिन्हित दीर्घ flag;

	chp = to_c4iw_cq(ibcq);
	spin_lock_irqsave(&chp->lock, flag);
	t4_arm_cq(&chp->cq,
		  (flags & IB_CQ_SOLICITED_MASK) == IB_CQ_SOLICITED);
	अगर (flags & IB_CQ_REPORT_MISSED_EVENTS)
		ret = t4_cq_notempty(&chp->cq);
	spin_unlock_irqrestore(&chp->lock, flag);
	वापस ret;
पूर्ण

व्योम c4iw_flush_srqidx(काष्ठा c4iw_qp *qhp, u32 srqidx)
अणु
	काष्ठा c4iw_cq *rchp = to_c4iw_cq(qhp->ibqp.recv_cq);
	अचिन्हित दीर्घ flag;

	/* locking heirarchy: cq lock first, then qp lock. */
	spin_lock_irqsave(&rchp->lock, flag);
	spin_lock(&qhp->lock);

	/* create a SRQ RECV CQE क्रम srqidx */
	insert_recv_cqe(&qhp->wq, &rchp->cq, srqidx);

	spin_unlock(&qhp->lock);
	spin_unlock_irqrestore(&rchp->lock, flag);
पूर्ण
